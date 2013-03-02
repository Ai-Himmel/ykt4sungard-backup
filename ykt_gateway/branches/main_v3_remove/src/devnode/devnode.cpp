
#include "ksgateway.h"
#include "devnode/devnode.h"
#include "taskcode.h"
#include <ace/Reactor.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/DLL_Manager.h>
#include <ace/DLL.h>
#include "osutil.h"
#include "task_scheduler.h"

using namespace LOOPDEV;

KSG_REG_FACTORY_INTERFACE(KSG_LOOP_DEV,KSGLoopDevInterfaceFactory);

KSG_REG_DEVICE_OBJECT(KSG_LOOP_DEV,KSG_LOOP_DEV_TYPE,KSGLoopDevice);

// 注册设备接口
/*
KSG_REG_DEV_INTERFACE(KSG_LOOP_DEV,TK_HEARTBEAT_TASK,DevHeartBeat);
KSG_REG_DEV_INTERFACE(KSG_LOOP_DEV,TK_RESTART_GATEWAY,DevRestartServer);
*/

//////////////////////////////////////////////////////////////////////////
//
bool KSGLoopDevice::Accept(BaseVisitor& guest)
{
	return false;
}
int KSGLoopDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	*handler = (ACE_HANDLE*)1;
	return 0;
}
int KSGLoopDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler)
{
	return 0;
}
//////////////////////////////////////////////////////////////////////////
// KSGLoopDeviceLoader

int KSGLoopDeviceLoader::LoadDevice(KSGDeviceManager* manager)
{
	// 加载 Loop 设备
	return manager->SetupLoopDevice();
}

int KSGLoopDeviceLoader::Finish(KSGDeviceManager* manager)
{
	// 将 LOOP 设备作为一个线程运行
	KSGDeviceNode *node = manager->FindDevice(KSGDeviceNode::LoopDeviceId);
	if(!node)
		return -1;
	/*
	int grpid = KsgGetGateway()->GetTaskQueue()->AddDevices(node);
	KSGTaskQueueManager::TaskGroupType* grp = KsgGetGateway()->GetTaskQueue()->
		GetDeviceGroup(grpid);
	KsgGetGateway()->GetDeviceGroupScheduler()->AddNewDeviceGroup(grp);
	*/
	KSG_Task_Queue *queue = Task_Queue_Pool::instance()->add_initial_queue(KSG_SCHEDULER_STATUS);
	if(queue)
	{
		return queue->load_all_device(node);
	}
	return -1;
}
////////////////////////////////////////////////////////////////////////
// KSGLoopDevInterLoader
int KSGLoopDevInterLoader::LoadInterface(KSGDeviceManager *manager)
{
	try
	{
		//KSG_ADD_DEVICE_INTERFACE(KSG_LOOP_DEV,KSG_LOOP_DEV_TYPE,DevHeartBeat);
		//KSG_ADD_DEVICE_INTERFACE(KSG_LOOP_DEV,KSG_LOOP_DEV_TYPE,DevRestartServer);
		KSG_ADD_DEVICE_INTERFACE(KSG_LOOP_DEV,KSG_LOOP_DEV_TYPE,DevSetCartState);
		return 0;
	}
	catch(KSGException& )
	{
		return -1;
	}
}

///////////////////////////////////////////////////////////////////////
// 设备接口定义
int DevHeartBeat::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	if(task->GetDeviceNode() != node)
		return -1;
	// TODO : 采集计算机CPU使用率,内存使用率,硬盘使用率
	return 0;
}

int DevRestartServer::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	if(task->GetDeviceNode() != node)
		return -1;
	KsgGetGateway()->restart();
	return 0;
}

int DevSetCartState::ExecuteTask(KSGDeviceNode *node,Task *task)
{
	int cardno = task->GetParams().GetParamIntVal(XML_KEY_CARDID);
	int add_del_sign = task->GetParams().GetParamIntVal(XML_KEY_ADDDELSIGN);
	int ret = hd_loadCardState.update_card_state(cardno,add_del_sign);
	if(ret < 0)
		return -1;
	return 0;
}

namespace LOOPDEV
{
	KSG_ADD_SCHD_CLASS(KSG_SCHD_LOOP_SVR,KSGLoopDeviceListenScheduler);

	DevHeartBeat::DevHeartBeat():KSGDeviceInterface(TK_HEARTBEAT_TASK)
	{}

	DevRestartServer::DevRestartServer():KSGDeviceInterface(TK_RESTART_GATEWAY)
	{}
	DevSetCartState::DevSetCartState():KSGDeviceInterface(930005)
	{}

	///////////////////////////////////////////////////////////////////
	/// 定义 LOOP 设备服务
	typedef ACE_Acceptor<LoopDeviceSvcHandler,ACE_SOCK_ACCEPTOR> LoopSvrAcceptor;

	LoopDeviceSvcHandler::LoopDeviceSvcHandler()
	{
		// empty
	}
	LoopDeviceSvcHandler::~LoopDeviceSvcHandler()
	{
		//empty
	}

	int LoopDeviceSvcHandler::open(void* param)
	{
		if(KSGLoopDeviceListenScheduler::_s_LoopReactor.register_handler(this,READ_MASK))
		{
			return -1;
		}
		ACE_DEBUG((LM_DEBUG,"收到请求数据包"));
		return 0;
	}
	int LoopDeviceSvcHandler::RecvData(ACE_HANDLE hd)
	{
		ACE_Message_Block * mb;
		ACE_NEW_RETURN(mb,ACE_Message_Block(MAX_BUFLEN),-1);
		if(ACE::recv_n(hd,mb->wr_ptr(),sizeof(int))<= 0)
		{
			ACE_DEBUG((LM_ERROR,"接收请求包失败"));
			return -1;
		}
		mb->wr_ptr(sizeof(int));
		KSG_GW_PACK_t req;
		ACE_OS::memset(&req,0,sizeof req);
		ACE_OS::memcpy(&req,mb->rd_ptr(),sizeof(int));
		ACE_INT32 readlen;
		req.length = ntohl(req.length);
		int remain = sizeof(KSG_GW_PACK_t) - sizeof(int) 
			- sizeof(char[1]) + req.length;
		if(remain >= MAX_BUFLEN)
		{
			ACE_ERROR((LM_ERROR,"接收数据包长度越界[%d]",req.length));
		}
		else if((readlen = peer().recv_n(mb->wr_ptr(),remain)) != remain)
		{
			ACE_ERROR((LM_ERROR,"接收数据不完整!"));
		}
		else
		{
			mb->wr_ptr(readlen);
			if(this->putq(mb) == -1)
			{
				ACE_DEBUG((LM_ERROR,"保存到消息队列失败"));
			}
			else
			{
				ACE_DEBUG((LM_DEBUG,"接收到完成数据包"));
				return 0;
			}
		}
		if(mb) mb->release();
		return -1;
	}
	int LoopDeviceSvcHandler::handle_input(ACE_HANDLE fd)
	{
		int ret;
		ret = RecvData(peer().get_handle());
		if(ret == 0)
		{
			ACE_DEBUG((LM_DEBUG,"接收到完成数据包"));
			_shutdown_ref = 1;
			KSGLoopDeviceListenScheduler::_s_LoopReactor.remove_handler(this,READ_MASK|DONT_CALL);
			activate(THR_NEW_LWP|THR_JOINABLE,1);
			return 0;
		}
		return -1;
	}

	int LoopDeviceSvcHandler::handle_output(ACE_HANDLE fd)
	{
		return 0;
	}

	int LoopDeviceSvcHandler::handle_close(ACE_HANDLE fd,ACE_Reactor_Mask mask)
	{
		safe_close();
		return 0;
	}

	int LoopDeviceSvcHandler::UnPackData(KSG_GW_PACK_t* pack)
	{
		ACE_ASSERT(pack != NULL);
		ACE_DEBUG((LM_DEBUG,"开始解压数据包..."));
		pack->length = ntohl(pack->length);
		pack->func_no = ntohl(pack->func_no);
		pack->next_pack = ntohl(pack->next_pack);
		pack->pack_index = ntohl(pack->pack_index);
		unsigned char md5[16] = "";
		if(pack->length>0)
		{
			if(pack->enc_type == KSG_ENC_TYPE_AES128)
			{
				// TODO: 使用 ACE 算法解密 , 控制必须使用加密传输
			}
			ACE_DEBUG((LM_DEBUG,"校验数据包,包长度[%d]",pack->length));
			KSGCryptUtil::CalcMD5((const unsigned char*)pack->data,pack->length,md5);
			if(ACE_OS::memcmp(md5,pack->CRC,sizeof md5))
			{
				ACE_DEBUG((LM_ERROR,"接收数据包校验错误!"));
				return -1;
			}
		}
		return 0;
	}
	int LoopDeviceSvcHandler::PackData(KSG_GW_PACK_t* resp,request_pack* pack)
	{
		resp->length = htonl(pack->outdatalen);
		resp->next_pack = htonl(resp->next_pack);
		resp->pack_index = htonl(1);
		resp->func_no = htonl(resp->func_no);
		resp->retcode = htonl(resp->retcode);
		resp->padded = 0;
		if(pack->outdatalen > 0)
		{
			ACE_OS::memcpy(resp->data,pack->outdata,pack->outdatalen);
			KSGCryptUtil::CalcMD5((const unsigned char*)resp->data,
				pack->outdatalen,resp->CRC);
			// TODO : 增加 ACE 算法
			resp->enc_type = KSG_ENC_TYPE_AES128;
			// 重新计算长度
		}
		return 0;
	}
	int LoopDeviceSvcHandler::SendResponse(int return_code,KSG_GW_PACK_t* req,
		request_pack* pack)
	{
		KSG_GW_PACK_t *resp;
		int packlen = sizeof(KSG_GW_PACK_t) - sizeof(char[1]);
		if(pack->outdatalen > 0)
			packlen += pack->outdatalen;
		else
			packlen += sizeof(char[1]);
		ACE_DEBUG((LM_DEBUG,"发送答应包长度%d[%d]",sizeof(KSG_GW_PACK_t),packlen));

		if((resp = (KSG_GW_PACK_t*)ACE_OS::malloc(packlen)) == NULL)
		{
			ACE_DEBUG((LM_ERROR,"发送应答失败,申请内存不成功"));
			return -1;
		}
		memset(resp,0,sizeof(KSG_GW_PACK_t));
		if(return_code)
		{
			resp->retcode = return_code;
		}
		else
			resp->retcode = 0;
		resp->func_no = req->func_no;
		resp->next_pack = req->next_pack;
		resp->pack_index = req->pack_index;
		if(PackData(resp,pack))
		{
			ACE_DEBUG((LM_ERROR,"生成应答数据包失败"));
			return -1;
		}
		ACE_Time_Value tv(3);
		if(peer().send_n((char*)resp,packlen,&tv)!=packlen)
		{
			ACE_ERROR_RETURN((LM_ERROR,"发送应答数据包失败"),-1);
		}
		return 0;
	}
	int LoopDeviceSvcHandler::RecvRequest(int *pRet,KSG_GW_PACK_t* gw_pack)
	{
		KSG_GW_PACK_t* req;
		request_pack* pack;
		int ret;
		ACE_Message_Block * mb = NULL;
		ACE_Time_Value tv(5);
		tv += ACE_OS::gettimeofday();
		ret = this->getq(mb,&tv);
		ACE_ASSERT((ret != -1));
		ACE_DEBUG((LM_DEBUG,"处理业务请求"));
		if(!mb)
		{
			ACE_DEBUG((LM_ERROR,"未从消息队列中获取数据包[%d]",ret));
			return -1;
		}
		req = (KSG_GW_PACK_t*)mb->rd_ptr();
		if(UnPackData(req))
		{
			ACE_DEBUG((LM_DEBUG,"解压数据包失败"));
			return -1;
		}
		memcpy(gw_pack,req,sizeof(KSG_GW_PACK_t));
		ret = -1;
		ACE_DEBUG((LM_DEBUG,"处理第[%d]个数据包,后续包标志[%d]",req->pack_index
			,req->next_pack));
		
		if((pack = (request_pack*)ACE_OS::malloc(sizeof(request_pack))) == NULL)
		{
			ACE_ERROR_RETURN((LM_ERROR,"申请内存失败"),-1);
		}
		try
		{
			ACE_OS::memset(pack,0,sizeof pack);
			pack->datalen = req->length;
			memcpy(pack->data,req->data,pack->datalen);
			*pRet = KSGLoopDeviceListenScheduler::_s_interface.ProcessRequest(
				req->func_no,pack);
			if(pack->outdatalen >= sizeof(pack->outdata))
			{
				ACE_DEBUG((LM_ERROR,"业务层返回数据包错误"));
				*pRet = KSG_LI_INTERNAL_ERROR;
			}
			else if(*pRet != 0)
			{
				pack->outdata[pack->outdatalen] = 0;
				ACE_DEBUG((LM_DEBUG,"处理请求失败[%d][%s]",*pRet,pack->outdata));
			}
			// 应答
			if(SendResponse(*pRet,req,pack))
			{
				ACE_DEBUG((LM_ERROR,"发送应答数据包失败"));
			}
			else
				ret = 0;
		}
		catch(...)
		{
			ACE_DEBUG((LM_ERROR,"请求处理异常!!!"));
			//
		}
		mb->release();
		ACE_OS::free(pack);
		return ret;
	}
	void LoopDeviceSvcHandler::safe_close()
	{
		bool needed = false;
		_mutex.acquire();
		_shutdown_ref--;
		if(!_shutdown_ref)
			needed = true;
		_mutex.release();
		if(needed)
		{
			delete this;
		}
	}
	int LoopDeviceSvcHandler::svc()
	{
		KSG_GW_PACK_t pack;
		int ret;
		do
		{
			ACE_OS::memset(&pack,0,sizeof pack);
			if(RecvRequest(&ret,&pack))
			{
				ACE_DEBUG((LM_ERROR,"处理请求失败!"));
				break;
			}
			// 处理结果成功,并且有后续包
			if(!ret && pack.next_pack)
			{
				ACE_Time_Value tv(3);
				while((ret = ACE::handle_read_ready(peer().get_handle(),&tv)) <= 0)
				{
					if(ret != EWOULDBLOCK)
						break;
				}
				if(RecvData(peer().get_handle()))
				{
					ACE_DEBUG((LM_ERROR," 接收后续数据包失败"));
					break;
				}
			}
			else
				break;
		}while(1);
		peer().close();
		return 0;
	}

	//////////////////////////////////////////////////////////////////////
	//
	int LocalInterface::LoadDLLFunc()
	{
		if(_dll.open(ACE_DLL_PREFIX ACE_TEXT("gwloop")))
			return -1;
		LOAD_DLL_FUNC(&_dll,Initialize);
		LOAD_DLL_FUNC(&_dll,Uninitialize);
		LOAD_DLL_FUNC(&_dll,ProcessRequest);
		return 0;
	}
	LocalInterface::~LocalInterface()
	{
		_dll.close();
	}
	//////////////////////////////////////////////////////////////////////
	// Loop 服务线程
	ACE_Reactor KSGLoopDeviceListenScheduler::_s_LoopReactor;
	LocalInterface KSGLoopDeviceListenScheduler::_s_interface;

	KSGLoopDeviceListenScheduler::KSGLoopDeviceListenScheduler()
		:KSGScheduler(KSG_SCHD_LOOP_SVR)
	{
		//empty
	}
	KSGLoopDeviceListenScheduler::~KSGLoopDeviceListenScheduler()
	{
		// empty 
	}

	void KSGLoopDeviceListenScheduler::Run()
	{
		int ret;
		_s_LoopReactor.owner(ACE_OS::thr_self());
		LoopSvrAcceptor acceptor;
		if(_s_interface.LoadDLLFunc())
		{
			ACE_DEBUG((LM_ERROR,"加载本地设备接口失败"));
			return;
		}
		
		int port = 9001;
#ifndef _DEBUG
		// TODO: 正式环境从后台中读取参数
		ACE_DEBUG((LM_NOTICE,"请设置侦听端口"));

#endif
		if(acceptor.open(ACE_INET_Addr(port),&_s_LoopReactor))
		{
			ACE_DEBUG((LM_ERROR,"Loop设备侦听失败，端口[%d]",port));
		}
		else if((ret = _s_interface.Initialize()))
		{
			ACE_DEBUG((LM_ERROR,"初始化Loop接口失败,返回错误[%d]",ret));
		}
		else
		{
			ACE_DEBUG((LM_INFO,"Loop设备开始侦听,线程号[%d]",ACE_OS::thr_self()));
			try
			{
				while(true)
				{
					ACE_Time_Value tv(5);
					_s_LoopReactor.handle_events(tv);
					Notify();
					if(IsTerminated())
					{
						while(!_s_LoopReactor.reactor_event_loop_done())
							_s_LoopReactor.end_reactor_event_loop();
						break;
					}
				}
				ACE_DEBUG((LM_NOTICE,"停止本地侦听服务"));
				if(_s_interface.Uninitialize())
				{
					ACE_DEBUG((LM_ERROR,"调用Loop设备接口释放资源失败!"));
				}
				ACE_DEBUG((LM_INFO,"Loop设备服务线程结束"));
			}
			catch(...)
			{
				// 捕获所有异常
				ACE_DEBUG((LM_NOTICE,"Loop设备服务线程执行异常"));
			}
		}
	}
}
