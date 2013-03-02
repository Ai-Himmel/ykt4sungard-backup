
#include "ksgateway.h"
#include "ksgexception.h"
#include "impl/schdimpl.h"
#include "taskdef.h"
#include "taskcode.h"
#include "taskqueue.h"
#include "bit_endian.h"
#include <ace/Log_Msg.h>
#include "osutil.h"


//////////////////////////////////////////////////////////////////////////
// KSGTaskReceiverScheduler

KSG_ADD_SCHD_CLASS(KSG_SCHD_RECV_TASK,KSGTaskReceiverScheduler);
KSG_ADD_SCHD_CLASS(KSG_SCHD_COLL_HEARTBEAT,KSGTaskCollHeartBeat);
KSG_ADD_SCHD_CLASS(KSG_SCHD_COLL_SERIAL,KSGTaskCollectSerial);
KSG_ADD_SCHD_CLASS(KSG_SCHD_BLKCARD,KSGTaskDownloadBlackCard);
KSG_ADD_SCHD_CLASS(KSG_SCHD_COLL_DEVSTATE,KSGTaskCollDeviceState);
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
				KSG_SLEEP(KsgGetGateway()->GetConfig()->_taskRecvIntval);
				continue;
			}
			ACE_DEBUG((LM_DEBUG,"��ʼ����ָ��..."));
			if(obj->Connect())
			{
				// ����ʧ��
				KSG_SLEEP(KsgGetGateway()->GetConfig()->_taskRecvIntval);
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
				KSG_SLEEP(KsgGetGateway()->GetConfig()->_taskRecvIntval);
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
				KSG_SLEEP(5000);
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
		KSG_SLEEP(KsgGetGateway()->GetConfig()->_taskRecvIntval);
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
			KSG_SLEEP(1000 * 60 * 3);
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
	KSG_SLEEP(10000);
	while(!IsTerminated())
	{
		try
		{
			KsgGetGateway()->GetDeviceManager()->Traseval(
				boost::bind(&KSGTaskCollectSerial::NewCollSerialTask,this,_1));
			Notify();
			//ACE_DEBUG((LM_INFO,"�ɼ���ˮ������������"));
			// �ɼ�һ����ˮ
			KSG_SLEEP(KsgGetGateway()->GetConfig()->_serialIntval);
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
		if(!task)
			ACE_DEBUG((LM_ERROR,"�ɼ��豸[%d] ��ˮ����ʧ��!",node.GetDevId()));
		else
		{
			ACE_DEBUG((LM_DEBUG,"�´�ɼ��豸[%d] ��ˮ������!",node.GetDevId()));
		}
	}catch(KSGException& )
	{
		// ��������ʧ��
	}	
	return;
}
//////////////////////////////////////////////////////////////////////////
// KSGTaskCollDeviceState
void KSGTaskCollDeviceState::Run()
{
	while(!IsTerminated())
	{
		try
		{
			_visitor.dev_start_ = 0;
			KsgGetGateway()->GetDeviceManager()->Traseval(
				boost::bind(&KSGTaskCollDeviceState::NewHeartBeatTask,this,_1));
			// ����ʣ�µ��豸״̬
			_visitor.send_state();
			Notify();
			// �ɼ�һ����ˮ
			//KsgGetGateway()->GetConfig()->_serialIntval * 50;
			ACE_DEBUG((LM_INFO,"�ɼ�һ������������"));
			KSG_SLEEP(KsgGetGateway()->GetConfig()->_heartbeat*10);
		}
		catch(std::exception& ex)
		{
			// 
			KSG_DUMP_EXCEPTION(ex);
			ACE_DEBUG((LM_DEBUG,"�ɼ��豸״̬�����쳣[%s]",ex.what()));
			KSG_SLEEP(KsgGetGateway()->GetConfig()->_heartbeat);
		}
	}
	ACE_DEBUG((LM_NOTICE,"�����߳��˳�"));
}

void KSGTaskCollDeviceState::CollDeviceState::encode_hd_sn(const char *long_sn,char *short_sn)
{	
	int i = 0;
	int j = 0;
	char temp[3] = "";
	char text[12] = "";
	ACE_OS::strcpy(text,long_sn);
	ACE_OS::strncpy(short_sn,text,4);
	ACE_OS::strncpy(temp,text+4,2);
	i = atoi(temp);
	if(i < 0 || i >15)
		return;
	ACE_OS::strncpy(temp,text+6,2);
	j = ACE_OS::atoi(temp);
	if(j < 0 || j > 15)
		return;
	ACE_OS::sprintf(short_sn+4,"%X%X",i,j);
	ACE_OS::strncat(short_sn+6,text+8,2);
	short_sn[8] = '\0';
}

void KSGTaskCollDeviceState::CollDeviceState::Visit(KSGDeviceNode& node)
{
	char devphy_no[9] = "";
	if(dev_start_ >= sizeof(dev_state_buf_))
	{
		// ��������
		if(send_state())
		{
			ACE_DEBUG((LM_ERROR,"��������ʧ��!"));
			return;
		}
		else
			dev_start_ = 0;
	}
	if(!node.Accept(*this))
		return;
	int state = 0;
	ACE_Time_Value now_time = ACE_OS::gettimeofday();
	now_time -= node.get_update_time();
	if(now_time.sec() > 60 * 8)
		state = 1;
	if(node.get_vendor() == KSG_HD_DEV)
	{
		encode_hd_sn(node.GetPhyId().c_str(),devphy_no);
	}
	else
		ACE_OS::strncpy(devphy_no,node.GetPhyId().c_str(),8);
	ACE_OS::sprintf(&dev_state_buf_[dev_start_],"%s%02X",devphy_no,state);
	dev_start_ += s_dev_state_len_;
}
int KSGTaskCollDeviceState::CollDeviceState::send_state()
{
	int i,j;
	if(dev_start_ == 0)
	{
		ACE_DEBUG((LM_INFO,"���豸״̬�ɼ�"));
		return 0;
	}
	static const int pack_max_len = 250; 
	char temp_buf[pack_max_len + 1] = "";
	int field_id[] = {F_VSMESS,F_VSVARSTR0,F_VSVARSTR1,F_VSVARSTR2,F_VSVARSTR3};
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
		return -1;
	obj->SetRequestHeader(930071);
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
	std::string now_time;
	char now_str[15] = "20";
	KSGOSUtil::GetTimestamp(now_time);
	ACE_OS::strncpy(now_str+2,now_time.c_str(),sizeof(now_str)-1);
	obj->AddField(F_SPHONE3,now_str);
	for (i = 0,j = 0;i < dev_start_ && i < s_dev_state_buf_len_; i+=pack_max_len,++j)
	{
		int len = (dev_start_ - i) > pack_max_len ? pack_max_len : (dev_start_-i);
		ACE_OS::memset(temp_buf,0,sizeof temp_buf);
		ACE_OS::strncpy(temp_buf,&dev_state_buf_[i],len);
		obj->AddField(field_id[j],temp_buf);
	}
	if(!obj->SendRequest(5000))
	{
		if(obj->GetReturnCode() == 0)
		{
			ACE_DEBUG((LM_INFO,"�ɼ������ɹ�"));
			return 0;
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"��ϵͳ֪ͨ�豸״̬ʧ��,ret[%d][%s]"
				,obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
		}
	}
	return -1;
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
			KSG_SLEEP(KsgGetGateway()->GetConfig()->_heartbeat);
		}
		catch(std::exception& ex)
		{
			// 
			KSG_DUMP_EXCEPTION(ex);
			ACE_DEBUG((LM_DEBUG,"���غ����������쳣[%s]",ex.what()));
			KSG_SLEEP(KsgGetGateway()->GetConfig()->_heartbeat);
		}
	}
	ACE_DEBUG((LM_NOTICE,"���������߳��˳�"));
}
