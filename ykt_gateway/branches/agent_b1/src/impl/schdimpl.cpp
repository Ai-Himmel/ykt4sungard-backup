
#include "ksgateway.h"
#include "ksgexception.h"
#include "impl/schdimpl.h"
#include "taskdef.h"
#include "taskcode.h"
#include "taskqueue.h"
#include "bit_endian.h"
#include <ace/Log_Msg.h>


//////////////////////////////////////////////////////////////////////////
// KSGTaskReceiverScheduler

KSG_ADD_SCHD_CLASS(KSG_SCHD_RECV_TASK,KSGTaskReceiverScheduler);
KSG_ADD_SCHD_CLASS(KSG_SCHD_COLL_HEARTBEAT,KSGTaskCollHeartBeat);
KSG_ADD_SCHD_CLASS(KSG_SCHD_COLL_SERIAL,KSGTaskCollectSerial);
KSG_ADD_SCHD_CLASS(KSG_SCHD_BLKCARD,KSGTaskDownloadBlackCard);
/**
 * ������еĲ�����Ҫ�����޸�
 */
void KSGTaskReceiverScheduler::Run()
{
	int count;
	while(!IsTerminated())
	{
		try
		{
			DRTPPoolType::SmartObject obj;
			obj = KsgGetDrtpPool()->Alloc();
			if(!obj)
			{
				ACE_DEBUG((LM_ERROR,"����DRTP����ʧ�ܣ�"));
				KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
				continue;
			}
			ACE_DEBUG((LM_DEBUG,"��ʼ����ָ��..."));
			if(obj->Connect())
			{
				// ����ʧ��
				KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
				continue;
			}
			obj->SetRequestHeader(KsgGetGateway()->GetConfig()->_taskRecvFuncNo);
			obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
			obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
			obj->AddField(F_LVOL1,KsgGetGateway()->GetConfig()->_get_task_count);
			if(obj->SendRequest(1000))
			{
				// ����ָ��ʧ��
				ACE_DEBUG((LM_ERROR,"����ָ�ʱ"));
				KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
				ACE_DEBUG((LM_DEBUG,"����ָ�ʱ�ȴ�����!"));
				continue;
			}
			Notify();
			count = 0;
			while(obj->HasMoreRecord())
			{
				ST_PACK * data = obj->GetNextRecord();
				// ����ָ��
				unsigned long taskid = data->lvol1;
				int funcid = data->lvol2;
				int devid = data->lvol3;
				TaskPriority priority = static_cast<TaskPriority>(data->lvol4);
				ACE_DEBUG((LM_DEBUG,"����ָ�ID[%d]func[%d]",taskid,funcid));
				if(devid == 0 || devid == 1)
				{
					devid = KSGDeviceNode::LoopDeviceId;
				}
				// �����豸
				KSGateway::DeviceNodeType* dev = KsgGetGateway()->GetDeviceManager()->FindDevice(devid);
				if(dev == NULL)
				{
					ACE_DEBUG((LM_ERROR,"ָ���޶�Ӧ���豸[%d]",devid));
					continue;
				}
				else
				{
					// �豸��ǰ״̬Ϊ����
					if(dev->GetState() == KSGateway::DeviceNodeType::dsError)
					{
						// TODO : Ӧ��ִ��ָ�ʱ
						ACE_DEBUG((LM_NOTICE,"�豸״̬����, ����ȡ��,dev[%d]taskid[%d]",devid,taskid));
						// ֱ����ȡ��һ��ָ��
						continue;
					}
				}
				// TODO: ����ϵͳ����ָ����Ҫ�ٽ��з���ϸ��
				// ����ָ��
				// ����ָ������ȼ�
				TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->NewTask(taskid
					,funcid,data->vsvarstr0,dev,priority);
				if(task->GetTaskId()==0)
				{
					ACE_DEBUG((LM_ERROR,"�����������ʧ��"));
					break;
				}
				// ���� preemptive ָ��
				//ACE_DEBUG((LM_DEBUG,"����ָ�����"));
				count++;
			}
			if(count < KsgGetGateway()->GetConfig()->_get_task_count)
			{
				// ���û��ָ����Խ���,�ȴ�5000ms
				ACE_DEBUG((LM_DEBUG,"û��ָ����ս���ȴ�״̬"));
				KSGThreadUtil::Sleep(5000);
			}
			// ֪ͨ���е� observer
		}
		catch(TaskAlreadyExistsException& )
		{
			// ָ���Ѵ���,���ܻ�û��ִ�����
			ACE_DEBUG((LM_NOTICE,"ָ���Ѿ��ڶ����еȴ�ִ����!"));
		}
		catch(TaskQueueExceedException&)
		{
			// ָ������Ѿ�����
			ACE_DEBUG((LM_NOTICE,"ָ���������!"));
		}
		catch(NullPointerException& )
		{
			ACE_DEBUG((LM_ERROR,"�豸δ��ȷ����"));
		}
		catch(std::exception& ex)
		{
			KSG_DUMP_EXCEPTION(ex);
			ACE_DEBUG((LM_ERROR,"����ָ���̴߳����쳣!"));
		}
		KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
		ACE_DEBUG((LM_DEBUG,"�ȴ�ָ�����"));
	}
	ACE_DEBUG((LM_NOTICE,"�ɼ���������߳��˳�"));
}
/////////////////////////////////////////////////////////////////////////
//
void KSGTaskCollHeartBeat::Run()
{
	while(!IsTerminated())
	{
		try
		{
			KsgGetGateway()->GetDeviceManager()->Traseval(
				boost::bind(&KSGTaskCollHeartBeat::NewHeartBeatTask,this,_1));
			Notify();
			// ÿ 3 ���Ӳɼ�һ������
			KSGThreadUtil::Sleep(1000 * 60 * 3);
			//KSGThreadUtil::Sleep(5000);
		}
		catch(std::exception& ex)
		{
			// 
			ACE_DEBUG((LM_DEBUG,"�ɼ����������쳣[%s]",ex.what()));
		}
	}
}

void KSGTaskCollHeartBeat::CollHeartBeatVisitor::Visit(KSGDeviceNode &node)
{
	if(node.GetState() == KSGDeviceNode::dsError)
		return;
	if(!node.Accept(*this))
		return;
	try
	{
	int taskid = KsgGetGateway()->GetTaskManager()->GenTaskId();
	std::stringstream buf;
	buf<<"<devphyid>"<<node.GetPhyId()<<"</devphyid>";
	TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->NewTask(taskid,TK_HEARTBEAT_TASK
		,buf.str(),&node,ptNormal);
	//task->SetPriority(ptNormal);
	//task->SetDeviceNode(&node);
	//KsgGetGateway()->GetTaskQueue()->AddTask(task);
	}
	catch(KSGException&)
	{
		ACE_DEBUG((LM_ERROR,"��������ʧ��"));
	}
	return;
}

///////////////////////////////////////////////////////////
///
void KSGTaskCollectSerial::Run()
{
	KSGThreadUtil::Sleep(10000);
	while(!IsTerminated())
	{
		try
		{
			KsgGetGateway()->GetDeviceManager()->Traseval(
				boost::bind(&KSGTaskCollectSerial::NewCollSerialTask,this,_1));
			Notify();
			// �ɼ�һ����ˮ
			KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_serialIntval);
		}
		catch(std::exception& ex)
		{
			// 
			ACE_DEBUG((LM_DEBUG,"�ɼ���ˮ�����쳣[%s]",ex.what()));
		}
	}
}

void KSGTaskCollectSerial::CollectSerialVisitor::Visit(KSGDeviceNode& node)
{
	if(node.GetState() == KSGDeviceNode::dsError)
		return;

	if(!node.Accept(*this))
		return;
	// ����豸�Ƿ���Ҫ�ɼ�����
	try
	{
		//int taskid = KsgGetGateway()->GetTaskManager()->GenTaskId();
		std::stringstream buf;
		buf<<"<devphyid>"<<node.GetPhyId()<<"</devphyid>";
		//TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->NewTask(taskid,TK_COLLSERIAL_TASK
		//																	   ,buf.str(),&node,ptNormal);
		TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->AddSysTask(TK_COLLSERIAL_TASK
																				   ,buf.str(),&node,ptNormal);
	}catch(KSGException& )
	{
		// ��������ʧ��
	}	
	return;
}

//////////////////////////////////////////////////////////////////////////
// ���غ���������
void KSGTaskDownloadBlackCard::DownloadBlackCardVisitor::Visit(KSGDeviceNode& node)
{
	//if(node.GetState() == KSGDeviceNode::dsError)
	//	return;
	dev_blkcard_info_t blk_info;
	if(!node.Accept(*this))
		return;
	DEV_BLKCARD_MAP_TYPE::const_iterator curr_iter = _dev_blkcard.find(node.GetDevId());
	if(curr_iter != _dev_blkcard.end())
	{
		blk_info = curr_iter->second;
		blk_info.sleep_times++;
		if(blk_info.last_cnt == 0)
		{
			_dev_blkcard[node.GetDevId()] = blk_info;
			int intval = KsgGetGateway()->GetConfig()->_heartbeatIntval;
			if(blk_info.sleep_times < intval)
				return;
		}
	}
	else
	{
		ACE_OS::memset(&blk_info,0,sizeof blk_info);
	}
	int count;
	char blk_buf[510];
	char max_vol[13] = "";
	static const int blk_card_cnt = 50;
	static const int card_len = 10;
	try
	{
		DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
		if(!obj)
		{
			return;
		}
		if(obj->Connect())
		{
			// ����ʧ��
			return;
		}
		obj->SetRequestHeader(950007);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
		obj->AddField(F_LVOL1,blk_card_cnt);
		obj->AddField(F_LVOL5,node.GetDevId());
		if(obj->SendRequest(5000))
		{
			// ����ָ��ʧ��
			KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
			ACE_DEBUG((LM_DEBUG,"����ָ�ʱ�ȴ�����!"));
			return;
		}
		if(obj->GetReturnCode())
		{
			ACE_DEBUG((LM_ERROR,"���غ�����ʧ�ܣ�����[%d][%s]",
				obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
			return;
		}
		count = 0;
		ACE_OS::memset(blk_buf,0,sizeof blk_buf);
		while(obj->HasMoreRecord() && count < blk_card_cnt)
		{
			ST_PACK * data = obj->GetNextRecord();
			// ����ָ��
			int flag = data->lvol3;
			int devid = data->lvol5;
			int cardid = data->lvol2;
			char curr_vol[13] = "";
			ACE_OS::strcpy(curr_vol,data->sname);
			if(ACE_OS::strncmp(curr_vol,max_vol,12)>0)
			{
				ACE_OS::strcpy(max_vol,curr_vol);
			}
			flag = (flag == 0) ? 0 : 1;
			unsigned char buf[10] = "";
			INT_2_BUF_LE(cardid,buf);
			ACE_OS::sprintf(blk_buf+count*card_len,"%02X%02X%02X%02X%02X",flag,buf[0],buf[1],buf[2],buf[3]);
			count++;
		}
		// ֪ͨ���е� observer
	}
	catch(std::exception &ex)
	{
		KSG_DUMP_EXCEPTION(ex);
		ACE_DEBUG((LM_ERROR,"���غ������̴߳����쳣!"));
		return;
	}
	/*
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"���غ������̷߳���δ֪�쳣!"));
		return;
	}
	*/
	blk_info.last_cnt = count;
	blk_info.sleep_times = 0;
	_dev_blkcard[node.GetDevId()] = blk_info;
	if(count == 0)
	{
		ACE_DEBUG((LM_INFO,"�豸[%d][%s]�������汾�Ѿ������µİ汾��"
			,node.GetDevId(),node.GetPhyId().c_str()));
		return;

	}
	// ����豸�Ƿ���Ҫ�ɼ�����
	try
	{
		//int taskid = KsgGetGateway()->GetTaskManager()->GenTaskId();
		std::stringstream buf;
		buf<<"<"
			<<XML_KEY_FTFLAG<<">"<<count<<"</"<<XML_KEY_FTFLAG<<"><"
			<<XML_KEY_VERNUM<<">"<<max_vol<<"</"<<XML_KEY_VERNUM<<"><"
			<<XML_KEY_CARDID<<">"<<blk_buf<<"</"<<XML_KEY_CARDID<<">";
		TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->AddSysTask(TK_BATCH_DL_BLKCARD
			,buf.str(),&node,ptNormal);
		if(task->GetTaskId() !=0 )
			ACE_DEBUG((LM_DEBUG,"�´��豸������,dev[%s]maxvol[%s]count[%d]"
				,node.GetPhyId().c_str(),max_vol,count));
		else
			ACE_DEBUG((LM_ERROR,"����ָ��ʧ�ܣ�"));
	}
	catch(TaskAlreadyExistsException& )
	{
		// ָ���Ѵ���,���ܻ�û��ִ�����
		ACE_DEBUG((LM_DEBUG,"���غ����������Ѿ��ڶ����еȴ�ִ����!dev[%s]",node.GetPhyId().c_str()));
	}
	catch(TaskQueueExceedException&)
	{
		// ָ������Ѿ�����
		ACE_DEBUG((LM_NOTICE,"ָ���������![%s]",node.GetPhyId().c_str()));
	}
	/*
	catch(...)
	{
		// ��������ʧ��
		//KSG_DUMP_EXCEPTION
		ACE_DEBUG((LM_ERROR,"д�����������ʧ��"));
	}	
	*/
	return;
}
void KSGTaskDownloadBlackCard::Run()
{
	while(!IsTerminated())
	{
		_collect_count = 0;
		try
		{
			KsgGetGateway()->GetDeviceManager()->Traseval(
				boost::bind(&KSGTaskDownloadBlackCard::NewDLBlkCardTask,this,_1));
			Notify();
			// �ɼ�һ����ˮ
			//KsgGetGateway()->GetConfig()->_serialIntval * 50;
			KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_heartbeat);
		}
		catch(std::exception& ex)
		{
			// 
			KSG_DUMP_EXCEPTION(ex);
			ACE_DEBUG((LM_DEBUG,"���غ����������쳣[%s]",ex.what()));
			KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_heartbeat);
		}
	}
	ACE_DEBUG((LM_NOTICE,"���������߳��߳��˳�"));
}
