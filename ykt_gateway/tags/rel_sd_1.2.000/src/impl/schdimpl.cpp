#include "stdafx.h"
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
				// 没有资源	
				KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
				continue;
			}
			ACE_DEBUG((LM_DEBUG,"开始接收指令..."));
			if(obj->Connect())
			{
				// 连接失败
				KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
				continue;
			}
			obj->SetRequestHeader(KsgGetGateway()->GetConfig()->_taskRecvFuncNo);
			obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
			obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
			if(obj->SendRequest(1000))
			{
				// 发送指令失败
				ACE_DEBUG((LM_ERROR,"接收指令超时"));
				KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
				ACE_DEBUG((LM_DEBUG,"接收指令超时等待结束!"));
				continue;
			}
			Notify();
			if(obj->HasMoreRecord())
			{
				ST_PACK * data = obj->GetNextRecord();
				// 下载指令
				ACE_DEBUG((LM_DEBUG,"下载指令，ID[%d]func[%d]",data->lvol1
					,data->lvol2));
				int devid = data->lvol3;
				if(devid == 0 || devid == 1)
				{
					devid = KSGDeviceNode::LoopDeviceId;
				}
				// 生成指令
				TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->NewTask(data->lvol1
					,data->lvol2,data->vsvarstr0);
				// 设置指令的优先级
				task->SetPriority(static_cast<TaskPriority>(data->lvol3));
				// 查找设备
				KSGateway::DeviceNodeType* dev = KsgGetGateway()->GetDeviceManager()->FindDevice(devid);
				if(dev == NULL)
				{
					ACE_DEBUG((LM_ERROR,"指令无对应的设备[%d]",data->lvol3));
				}
				else
				{
					// 设备当前状态为错误
					if(dev->GetState() == KSGateway::DeviceNodeType::dsError)
					{
						// TODO : 应答执行指令超时
						// 直接收取下一条指令
						continue;
					}
					task->SetDeviceNode(dev);
					KsgGetGateway()->GetTaskQueue()->AddTask(task);
				}
				ACE_DEBUG((LM_DEBUG,"下载指令完成"));
			}
			else
			{
				// 如果没有指令可以接收,等待5000ms
				ACE_DEBUG((LM_DEBUG,"没有指令接收进入等待状态"));
				KSGThreadUtil::Sleep(5000);
				continue;
			}
			// 通知所有的 observer
		}
		catch(TaskAlreadyExistsException& )
		{
			// 指令已存在,可能还没有执行完成
			ACE_DEBUG((LM_NOTICE,"指令已经在队列中等待执行了!"));
		}
		catch(TaskQueueExceedException&)
		{
			// 指令队列已经满了
			ACE_DEBUG((LM_NOTICE,"指令队列已满!"));
		}
		catch(std::exception& ex)
		{
			ACE_DEBUG((LM_ERROR,"接收指令线程处理异常!"));
		}
		KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
		ACE_DEBUG((LM_DEBUG,"等待指令结束"));
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
			// 每 3 分钟采集一次心跳
			KSGThreadUtil::Sleep(1000 * 60 * 3);
			//KSGThreadUtil::Sleep(5000);
		}
		catch(std::exception& ex)
		{
			// 
			ACE_DEBUG((LM_DEBUG,"采集心跳任务异常[%s]",ex.what()));
		}
	}
}

void KSGTaskCollHeartBeat::CollHeartBeatVisitor::Visit(KSGDeviceNode &node)
{
	if(node.GetState() == KSGDeviceNode::dsError)
		return;
	if(!node.Accept(*this))
		return;
	int taskid = KsgGetGateway()->GetTaskManager()->GenTaskId();
	std::stringstream buf;
	buf<<"<devphyid>"<<node.GetPhyId()<<"</devphyid>";
	TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->NewTask(taskid,TK_HEARTBEAT_TASK
		,buf.str());
	task->SetPriority(ptNormal);
	task->SetDeviceNode(&node);
	KsgGetGateway()->GetTaskQueue()->AddTask(task);
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
			// 每 3 秒采集一次流水
			KSGThreadUtil::Sleep(3000);
		}
		catch(std::exception& ex)
		{
			// 
			ACE_DEBUG((LM_DEBUG,"采集流水任务异常[%s]",ex.what()));
		}
	}
}

void KSGTaskCollectSerial::CollectSerialVisitor::Visit(KSGDeviceNode& node)
{
	if(node.GetState() == KSGDeviceNode::dsError)
		return;
	if(!node.Accept(*this))
		return;
	int taskid = KsgGetGateway()->GetTaskManager()->GenTaskId();
	std::stringstream buf;
	buf<<"<devphyid>"<<node.GetPhyId()<<"</devphyid>";
	TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->NewTask(taskid,TK_COLLSERIAL_TASK
		,buf.str());
	task->SetPriority(ptNormal);
	task->SetDeviceNode(&node);
	KsgGetGateway()->GetTaskQueue()->AddTask(task);
	return;
}