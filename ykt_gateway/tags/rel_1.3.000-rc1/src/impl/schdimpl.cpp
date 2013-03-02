
#include "ksgateway.h"
#include "ksgexception.h"
#include "impl/schdimpl.h"
#include "taskdef.h"
#include "taskcode.h"
#include "taskqueue.h"
#include <ace/Log_Msg.h>


//////////////////////////////////////////////////////////////////////////
// KSGTaskReceiverScheduler

KSG_ADD_SCHD_CLASS(KSG_SCHD_RECV_TASK,KSGTaskReceiverScheduler);
KSG_ADD_SCHD_CLASS(KSG_SCHD_COLL_HEARTBEAT,KSGTaskCollHeartBeat);
KSG_ADD_SCHD_CLASS(KSG_SCHD_COLL_SERIAL,KSGTaskCollectSerial);
/**
 * ������еĲ�����Ҫ�����޸�
 */
void KSGTaskReceiverScheduler::Run()
{
	while(!IsTerminated())
	{
		try
		{
			DRTPPoolType::SmartObject obj;
			try
			{
				obj = KsgGetDrtpPool()->Alloc();
			}
			catch (NoneResourceException& )
			{
				// û����Դ	
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
			if(obj->SendRequest(1000))
			{
				// ����ָ��ʧ��
				ACE_DEBUG((LM_ERROR,"����ָ�ʱ"));
				KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
				ACE_DEBUG((LM_DEBUG,"����ָ�ʱ�ȴ�����!"));
				continue;
			}
			Notify();
			if(obj->HasMoreRecord())
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
				// ���� preemptive ָ��
				//ACE_DEBUG((LM_DEBUG,"����ָ�����"));
			}
			else
			{
				// ���û��ָ����Խ���,�ȴ�5000ms
				ACE_DEBUG((LM_DEBUG,"û��ָ����ս���ȴ�״̬"));
				KSGThreadUtil::Sleep(5000);
				continue;
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
			ACE_DEBUG((LM_ERROR,"����ָ���̴߳����쳣!"));
		}
		KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
		ACE_DEBUG((LM_DEBUG,"�ȴ�ָ�����"));
	}
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
	while(!IsTerminated())
	{
		try
		{
			KsgGetGateway()->GetDeviceManager()->Traseval(
				boost::bind(&KSGTaskCollectSerial::NewCollSerialTask,this,_1));
			Notify();
			// ÿ 500 ms �ɼ�һ����ˮ
			KSGThreadUtil::Sleep(3000);
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
		int taskid = KsgGetGateway()->GetTaskManager()->GenTaskId();
		std::stringstream buf;
		buf<<"<devphyid>"<<node.GetPhyId()<<"</devphyid>";
		TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->NewTask(taskid,TK_COLLSERIAL_TASK
																			   ,buf.str(),&node,ptNormal);
	}catch(KSGException& )
	{
		// ��������ʧ��
	}	
	return;
}

