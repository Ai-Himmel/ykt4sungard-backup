/**
 * V1.2 修改了设备节点 toplogic 初始化功能
 */

#include "hddev/hddevnode.h"
#include "hddev/hdsvr.h"
#include "ksgateway.h"
#include "netutil.h"
#include "xutils/xstring.h"
#include "task_scheduler.h"
#include "impl/schdimpl.h"
#include "osutil.h"
#include "execimpl.h"
#include <ace/Test_and_Set.h>
#include <ace/Null_Mutex.h>
#include <ace/SOCK_Connector.h>
#include <ace/OS.h>
#include "pubfunc.h"
#include <curl/curl.h>

using namespace HDDEV;


// 对汇多设备的支持

#ifdef KSG_HD_DEV_SUPPORT

// 注册CCU侦听调度线程
//KSG_ADD_SCHD_CLASS(KSG_SCHD_HD_TCP_SVR,HDCCUListenScheduler);
// 注册汇多设备类型工厂
KSG_REG_FACTORY_INTERFACE(KSG_HD_DEV,KSGHDDevInterfaceFactory);

// 注册汇多设备类型
KSG_REG_DEVICE_OBJECT(KSG_HD_DEV,KSG_HD_POS_DEV,HDPosDevice);
KSG_REG_DEVICE_OBJECT(KSG_HD_DEV,KSG_HD_SERVER_DEV,HDCCUDevice);
KSG_REG_DEVICE_OBJECT(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,HDAddPosDevice);
KSG_REG_DEVICE_OBJECT(KSG_HD_DEV,KSG_HD_PENSTOCK,HDPenStockDevice);
KSG_REG_DEVICE_OBJECT(KSG_HD_DEV,KSG_JSB_DEV,HDKQDevice);
KSG_REG_DEVICE_OBJECT(KSG_HD_DEV,KSG_READER_DEV,HDReaderDevice);
KSG_REG_DEVICE_OBJECT(KSG_HD_DEV,KSG_HD_KQ_CCU,HDKQCCUDevice);
KSG_REG_DEVICE_OBJECT(KSG_HD_DEV,"9003",HDGCUDevice);


/// 注册汇多设备接口
/*
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_COLLSERIAL_TASK,IHDCollectSerial);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_HEARTBEAT_TASK,IHDCollectHeardbeat);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_ADD_BLACKCARD,IHDAddBlackCard);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_DEL_BLACKCARD,IHDDelBlackCard);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_SET_CARD_PRIVILEGE,IHDSetCardPrivileges);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_SET_FEE_RATE,IHDSetFeeRate);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_COLL_HIS_SERIAL,IHDCollPosHisSerial);
*/

#endif // KSG_HD_DEV_SUPPORT

namespace HDDEV
{
	std::string hd_ccu_ftp_user_name = "hdhdhdhd";
	std::string hd_ccu_ftp_pswd = "11111111";
	std::string hd_ccu_ftp_port = "21";
};

bool HDCCUDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	if(typeid(guest) == typeid(KSGTaskCollHeartBeat::CollHeartBeatVisitor))
		return true;
	if(typeid(guest) == typeid(KSGTaskCollDeviceState::CollDeviceState))
		return true;
	return false;
}

int HDCCUDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	if(!node)
		return -1;
	std::string ip = node->GetDevAddr().GetConnect();
	int port = node->GetDevAddr().GetPort();
	ACE_INET_Addr addr(port,ip.c_str());
	ACE_SOCK_Connector conn;
	ACE_SOCK_Stream stream;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	int err_code;
	ACE_DEBUG((LM_TRACE,"开始连接汇多CCU，[%s][%s]",node->get_name().c_str(),ip.c_str()));
	if(conn.connect(stream,addr,&tv))
	{
		err_code = ACE_OS::last_error();
		// TODO: 返回连接的错误码
		if(EWOULDBLOCK == err_code)
		{
			ACE_DEBUG((LM_ERROR,"连接CCU失败"));
		}
		else if(EHOSTUNREACH == err_code || ENETUNREACH == err_code)
		{
			ACE_DEBUG((LM_ERROR,"无法连接设备主机"));
			node->SetState(KSGDeviceNode::dsError);
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"连接主机未知错误![%d][%s]ip[%s]"
				,err_code,ACE_OS::strerror(err_code),ip.c_str()));
		}
		// add by cash 释放 SOCKET 
		// 2007-01-29
		stream.close();
		return -1;
	}
	// 设置 handler 为 BLOCK 的
	// stream.disable(ACE_NONBLOCK);
	// 设置 linger 属性
	struct linger lg;
	ACE_OS::memset(&lg,0,sizeof lg);
	lg.l_onoff = 1;
	// 3s 
	lg.l_linger = 3;
	stream.set_option(SOL_SOCKET,SO_LINGER,&lg,sizeof lg);
	node->SetState(KSGDeviceNode::dsOnline);
	*handler = stream.get_handle();
	return 0;
}

int HDCCUDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ()
{
	try
	{
		ACE_Time_Value tv(0,500);
		// 一定要先调用 close_handler 否则会导致死锁
		//KSGDevice::close_handler(node,handler);
		/*
		int ret = ACE::handle_ready(handler,&tv,1,1,1);
		if( ret > 0)
		{
			ACE_OS::closesocket(handler);
		}
		else
		{
			// 如果出现异常,要如何关闭??
			ACE_DEBUG((LM_ERROR,"连接出现异常无法被关闭!..."));
		}
		*/
		ACE_OS::closesocket(handler);
		return 0;
	}
	catch(...)
	{
		// catch all
		ACE_DEBUG((LM_ERROR,"关闭CCU Handler 失败"));
		return -1;
	}
}

int HDGCUDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	if(!node)
		return -1;
	std::string ip = node->GetDevAddr().GetConnect();
	int port = node->GetDevAddr().GetPort();
	ACE_INET_Addr addr(port,ip.c_str());
	ACE_SOCK_Connector conn;
	ACE_SOCK_Stream stream;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	int err_code;
	ACE_DEBUG((LM_TRACE,"开始连接汇多GCU，[%s][%s]",node->get_name().c_str(),ip.c_str()));
	if(conn.connect(stream,addr,&tv))
	{
		err_code = ACE_OS::last_error();
		// TODO: 返回连接的错误码
		if(EWOULDBLOCK == err_code)
		{
			ACE_DEBUG((LM_ERROR,"连接GCU失败"));
		}
		else if(EHOSTUNREACH == err_code || ENETUNREACH == err_code)
		{
			ACE_DEBUG((LM_ERROR,"无法连接设备主机"));
			node->SetState(KSGDeviceNode::dsError);
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"连接 GCU 未知错误![%d][%s]ip[%s]"
				,err_code,ACE_OS::strerror(err_code),ip.c_str()));
		}
		// add by cash 释放 SOCKET 
		// 2007-01-29
		stream.close();
		return -1;
	}
	// 设置 handler 为 BLOCK 的
	// stream.disable(ACE_NONBLOCK);
	// 设置 linger 属性
	struct linger lg;
	ACE_OS::memset(&lg,0,sizeof lg);
	lg.l_onoff = 1;
	// 3s 
	lg.l_linger = 3;
	stream.set_option(SOL_SOCKET,SO_LINGER,&lg,sizeof lg);
	node->SetState(KSGDeviceNode::dsOnline);
	*handler = stream.get_handle();
	return 0;
}

int HDGCUDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler)
{
	try
	{
		ACE_OS::closesocket(handler);
		return 0;
	}
	catch(...)
	{
		// catch all
		ACE_DEBUG((LM_ERROR,"关闭GCU Handler 异常"));
		return -1;
	}
}
bool HDGCUDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	if(typeid(guest) == typeid(KSGTaskDoorBatchDlCard::BatchDownloadCardVisitor))
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
bool HDKQCCUDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	//if(typeid(guest) == typeid(KSGTaskCollHeartBeat::CollHeartBeatVisitor))
	//	return true;
	return false;
}

int HDKQCCUDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	if(!node)
		return -1;
	std::string ip = node->GetDevAddr().GetConnect();
	int port = node->GetDevAddr().GetPort();
	ACE_INET_Addr addr(port,ip.c_str());
	ACE_SOCK_Connector conn;
	ACE_SOCK_Stream stream;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	int err_code;
	if(conn.connect(stream,addr,&tv))
	{
		err_code = ACE_OS::last_error();
		// TODO: 返回连接的错误码
		if(EWOULDBLOCK == err_code)
		{
			ACE_DEBUG((LM_ERROR,"连接CCU失败"));
		}
		else if(EHOSTUNREACH == err_code || ENETUNREACH == err_code)
		{
			ACE_DEBUG((LM_ERROR,"无法连接设备主机"));
			node->SetState(KSGDeviceNode::dsError);
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"连接主机未知错误![%d][%s]ip[%s]"
				,err_code,ACE_OS::strerror(err_code),ip.c_str()));
		}
		// add by cash 释放 SOCKET 
		// 2007-01-29
		stream.close();
		return -1;
	}
	// 设置 handler 为 BLOCK 的
	// stream.disable(ACE_NONBLOCK);
	// 设置 linger 属性
	struct linger lg;
	ACE_OS::memset(&lg,0,sizeof lg);
	lg.l_onoff = 1;
	// 3s 
	lg.l_linger = 3;
	stream.set_option(SOL_SOCKET,SO_LINGER,&lg,sizeof lg);
	node->SetState(KSGDeviceNode::dsOnline);
	*handler = stream.get_handle();
	return 0;
}

int HDKQCCUDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ()
{
	try
	{
		ACE_Time_Value tv(0,500);
		// 一定要先调用 close_handler 否则会导致死锁
		ACE_OS::closesocket(handler);
		return 0;
	}
	catch(...)
	{
		// catch all
		ACE_DEBUG((LM_ERROR,"关闭CCU Handler 失败"));
		return -1;
	}
}

bool HDPosDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	/*
	if(typeid(guest) == typeid(KSGTaskCollHeartBeat::CollHeartBeatVisitor))
		return true;
	*/
	if(typeid(guest) == typeid(KSGTaskDownloadBlackCard::DownloadBlackCardVisitor))
	{
		if(visitor->owner_queue() && visitor->GetConnType() != KSGDeviceURL::dctModem)
			return true;
	}
	
	if(typeid(guest) == typeid(KSGTaskCollDeviceState::CollDeviceState))
		return true;
	
	//if(typeid(guest) == typeid(KSGTaskCollectSerial::CollectSerialVisitor))
	//	return true;
	return false;
}

int HDPosDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	if(!node)
		return -1;
	if(node->GetConnType() != KSGDeviceURL::dctTCP)
		return 1;
	std::string ip = node->GetDevAddr().GetConnect();
	int port = node->GetDevAddr().GetPort();
	ACE_INET_Addr addr(port,ip.c_str());
	ACE_SOCK_Connector conn;
	ACE_SOCK_Stream stream;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	int err_code;
	if(conn.connect(stream,addr,&tv))
	{
		err_code = ACE_OS::last_error();
		// TODO: 返回连接的错误码
		if(EWOULDBLOCK == err_code)
		{
			ACE_DEBUG((LM_ERROR,"连接CCU失败"));
		}
		else if(EHOSTUNREACH == err_code || ENETUNREACH == err_code)
		{
			ACE_DEBUG((LM_ERROR,"无法连接设备主机"));
			node->SetState(KSGDeviceNode::dsError);
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"连接主机未知错误![%d][%s]ip[%s]"
				,err_code,ACE_OS::strerror(err_code),ip.c_str()));
		}
		// add by cash 释放 SOCKET 
		// 2007-01-29
		stream.close();
		return -1;
	}
	// 设置 handler 为 BLOCK 的
	// stream.disable(ACE_NONBLOCK);
	// 设置 linger 属性
	struct linger lg;
	ACE_OS::memset(&lg,0,sizeof lg);
	lg.l_onoff = 1;
	// 3s 
	lg.l_linger = 3;
	stream.set_option(SOL_SOCKET,SO_LINGER,&lg,sizeof lg);
	node->SetState(KSGDeviceNode::dsOnline);
	*handler = stream.get_handle();
	return 0;
}

int HDPosDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ()
{
	try
	{
		ACE_Time_Value tv(0,500);
		ACE_OS::closesocket(handler);
		return 0;
	}
	catch(...)
	{
		// catch all
		ACE_DEBUG((LM_ERROR,"关闭CCU Handler 失败"));
		return -1;
	}
}

bool HDAddPosDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	/*
	if(typeid(guest) == typeid(KSGTaskCollHeartBeat::CollHeartBeatVisitor))
		return true;
	if(typeid(guest) == typeid(KSGTaskCollectSerial::CollectSerialVisitor))
		return true;
	*/
	if(typeid(guest) == typeid(KSGTaskCollDeviceState::CollDeviceState))
		return true;
	return false;
}

int HDAddPosDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	if(!node)
		return -1;
	// 如果是TCP协议
	if(node->GetConnType() != KSGDeviceURL::dctTCP)
		return 1;
	std::string ip = node->GetDevAddr().GetConnect();
	int port = node->GetDevAddr().GetPort();
	ACE_INET_Addr addr(port,ip.c_str());
	ACE_SOCK_Connector conn;
	ACE_SOCK_Stream stream;
	ACE_Time_Value tv(1);
	int err_code;
	if(conn.connect(stream,addr,&tv))
	{
		err_code = ACE_OS::last_error();
		// TODO: 返回连接的错误码
		if(EWOULDBLOCK == err_code)
		{
			ACE_DEBUG((LM_ERROR,"连接CCU失败"));
		}
		else if(EHOSTUNREACH == err_code || ENETUNREACH == err_code)
		{
			ACE_DEBUG((LM_ERROR,"无法连接设备主机"));
			node->SetState(KSGDeviceNode::dsError);
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"连接主机未知错误![%d][%s]"
				,err_code,ACE_OS::strerror(err_code)));
		}
		// add by cash 释放 SOCKET 
		// 2007-01-29
		stream.close();
		return -1;
	}
	// 设置 handler 为 BLOCK 的
	// stream.disable(ACE_NONBLOCK);
	// 设置 linger 属性
	struct linger lg;
	ACE_OS::memset(&lg,0,sizeof lg);
	lg.l_onoff = 1;
	// 3s 
	lg.l_linger = 3;
	stream.set_option(SOL_SOCKET,SO_LINGER,&lg,sizeof lg);
	node->SetState(KSGDeviceNode::dsOnline);
	*handler = stream.get_handle();
	return 0;
}
int HDAddPosDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw()
{
	if(node->GetConnType() != KSGDeviceURL::dctTCP)
		return 1;
	try
	{
		ACE_OS::closesocket(handler);
		return 0;
	}
	catch(...)
	{
		// catch all
		ACE_DEBUG((LM_ERROR,"关闭CCU Handler 失败"));
		return -1;
	}
}

int HDPenStockDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	return 1;
}
int HDPenStockDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw()
{
	return 1;
}
bool HDPenStockDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	if(typeid(guest) == typeid(KSGTaskCollDeviceState::CollDeviceState))
		return true;
	return false;
}

int HDKQDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	return 1;
}
int HDKQDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw()
{
	return 1;
}
bool HDKQDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	if(typeid(guest) == typeid(KSGTaskCollDeviceState::CollDeviceState))
		return true;
	return false;
}

int HDReaderDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	return 1;
}
int HDReaderDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw()
{
	return 1;
}
bool HDReaderDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	return false;
}

//////////////////////////////////////////////////////////////////////
// HDDeviceLoader
int HDDeviceLoader::Finish(KSGDeviceManager* manager)
{
	KSGDeviceManager::DeviceList * devs = manager->GetDevices();
	//std::for_each(devs->begin(),devs->end(),
	//	boost::bind(&HDDeviceLoader::SetupDeviceNoticeTask,this,_1));
	// 设置指令队列的分组
	try
	{
		manager->Traseval(boost::bind(&HDDeviceLoader::SetupDeviceGroup,this,_1));
	}
	catch(KSGException&)
	{
		return -1;
	}
	return 0;
}

int HDDeviceLoader::LoadDevice(KSGDeviceManager* manager)
{
	ACE_DEBUG((LM_DEBUG,"开始加载汇多设备..."));
	try
	{
		// modified by 汤成  2006-12-31
		// 修改 : 将设备节点 toplogic 的初始化工作交给外层框架来完成
		// 设置设备的物理结构关系
		/*
		std::for_each(devs->begin(),devs->end(),
			boost::bind(&HDDeviceLoader::SetupDevice,this,manager,_1));
		*/
	}
	catch(...)
	{
	}
	return 0;
}

void HDDeviceLoader::SetupDeviceGroup(KSGDeviceNode* node)
{
	if(node->get_vendor() != KSG_HD_DEV)
		return;
	node->connect_module(KSGDeviceNode::cm_long_conn);
	// modify by Cash , TCP 的POS机设置为短连接模式
	if(node->GetConnType() == KSGDeviceURL::dctTCP
		&& node->GetDeviceType() != KSG_HD_SERVER_DEV)
	{
		node->connect_module(KSGDeviceNode::cm_short_conn);
		ACE_DEBUG((LM_TRACE,"汇多设备[%d]是TCP设备",node->GetDevId()));
	}
	// 不需要设置 loop device ,
	if(node->GetDeviceType() == KSG_HD_SERVER_DEV
		|| node->GetConnType() == KSGDeviceURL::dctTCP)
	{
		KSG_Task_Queue *queue = Task_Queue_Pool::instance()->add_initial_queue(KSG_SCHEDULER_STATUS);
		if(queue)
		{
			// 增加所有设备
			if(queue->load_all_device(node))
				throw KSGException();
		}
		else
		{
			ACE_DEBUG((LM_WARNING,"设备无法创建任务队列,dev[%d]",node->GetDevId()));
		}
	}
}
//////////////////////////////////////////////////////////////////////
// HDDevInterfaceLoader
int HDDevInterfaceLoader::LoadInterface(KSGDeviceManager *manager)
{
	try
	{
		// 为设备类型增加接口
		// 注册POS机接口
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,IHDAddBlackCard);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,IHDDelBlackCard);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,IHDSetCardPrivileges);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,IHDSetFeeRate);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,IHDSetFeeRate2);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,IHDCollPosHisSerial);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,IHDDownloadConCode);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,IHDBatchDownloadBlkCard);
		
		// 注册充值机接口
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,IHDAddBlackCard);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,IHDDelBlackCard);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,IHDSetCardPrivileges);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,IHDCollPosHisSerial);
		// 注册CCU接口
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_SERVER_DEV,IHDDLSubsidyFile);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_SERVER_DEV,IHDCCUOnlineNotice);
		
		//注册水控机
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_PENSTOCK,IHDCtlPenStock);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_PENSTOCK,IHDCollPosHisSerial);

		return 0;
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"加载汇多设备接口失败.........."));
		return -1;
	}
}

int HDTaskExecutorLoader::LoadExecutor()
{
	// 注册指令执行处理接口
	return 0;
}
//////////////////////////////////////////////////////////////////////
//

int IHDCollectSerial::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	KSGDevice* device = node->GetDevice();
	if(!device)
		return TASK_ERR_COMMON;
	ACE_HANDLE handler = task->_handle;
	int ret;
	unsigned long termsn = 0;
	ACE_SOCK_Stream stream(handler);
	
	HD8583STRUCT req;

	KSGDeviceNode* task_node = task->GetDeviceNode();
	termsn = DecodeTermSN(task_node->GetPhyId().c_str());
	unsigned short address = GetDeviceAddress(task_node);
	req.Init();
	req.SetFieldValue(FIELD_TERMINALSN,termsn);
	req.SetFieldValue(FIELD_ADDRESS,address);
	req.SetFieldValue(FIELD_TERMINALID,(unsigned short)task_node->GetTermId());
	char rec_cnt = (char)10;
	req.SetFieldValue(FIELD_ADDITIONALDATA1,&rec_cnt,1);

	char buf[8184] = "";
	size_t32 packlen = PackRequestStruct(req,MT_COLLECT_SERIAL1,buf,sizeof buf,true);
	if( packlen <= 0)
	{
		return TASK_ERR_COMMON;
	}
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	if(HDSendBuffer(handler,buf,packlen,&tv) != 0)
	{
		return TASK_ERR_TIMEOUT;
	}
	packlen = HDRecvBuffer(handler,buf,sizeof buf,&tv);
	if( packlen <= 0)
	{
		return TASK_ERR_COMMON;
	}
	MESSAGETYPE msg_type;
	if(UnPackResponseStruct(req,&msg_type,buf,packlen)!=0)
	{
		//
		return TASK_ERR_COMMON;
	}
	if(req->ResponseCode != RC_SUCCESS)
	{
		return TASK_ERR_COMMON;
	}
	if(CollectRecord(req) == 0)
	{
		return 0;
	}

	return TASK_ERR_COMMON;
}

int IHDCollectSerial::CollectRecord(HD8583STRUCT& record)
{
	return -1;
}

int IHDCollectHeardbeat::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	KSGDevice * device = node->GetDevice();
	if(!device)
		return TASK_ERR_COMMON;
	ACE_HANDLE handler = task->_handle;
	int ret ;
	HD8583STRUCT req;
	KSGDeviceNode* task_node = task->GetDeviceNode();
	unsigned long termid = ACE_OS::strtoul(task_node->GetPhyId().c_str(),NULL,10);
	req.SetFieldValue(FIELD_TERMINALSN,termid);
	req.SetFieldValue(FIELD_ADDRESS,GetDeviceAddress(task_node));
	char buf[4096] = "";
	size_t32 packlen = PackRequestStruct(req,MT_REECHO2,buf,sizeof buf,false);
	if( packlen <= 0)
	{
		return TASK_ERR_COMMON;
	}
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	//if(HDSendBuffer(handler,buf,packlen,&tv) != 0)
	if(KSGNetUtil::send_buffer(handler,(unsigned char*)buf,packlen,&tv)!=0)
	{
		return TASK_ERR_TIMEOUT;
	}
	
	memset(buf,0,sizeof buf);
	packlen = HDRecvBuffer(handler,buf,sizeof buf,&tv);
	if(packlen <= 0)
	{
		return TASK_ERR_EXECUTE;
	}
	MESSAGETYPE msg_type;
	if(UnPackResponseStruct(req,&msg_type,buf,packlen)!=0)
	{
		ACE_DEBUG((LM_INFO,"回响测试失败![%s]",task_node->GetPhyId().c_str()));
		return TASK_ERR_EXECUTE;
	}
	task_node->SetState(KSGDeviceNode::dsOnline);
	task_node->update_time();
	ACE_DEBUG((LM_INFO,"回响测试成功![%u][%x]",termid,req->ResponseCode));
	return TASK_SUCCESS;
}
int IHDCCUOnlineNotice::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	MYDATETIMESTRUCT now;
	HD8583STRUCT req;
	char data[300];
	size_t packlen;
	int ret;
	MESSAGETYPE msg_type;
	ACE_HANDLE handle = task->_handle;
	KSGDeviceNode* task_node = task->GetDeviceNode();
	unsigned long termid = ACE_OS::strtoul(task_node->GetPhyId().c_str(),NULL,10);
	req.SetFieldValue(FIELD_TERMINALSN,termid);
	now = HDGetDataTime();
	req.SetFieldValue(FIELD_DATEANDTIME,(char*)&now,7);

	ACE_DEBUG((LM_DEBUG,"采集CCU心跳,dev[%s]",task_node->GetPhyId().c_str()));
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	if( (packlen = PackRequestStruct(req,MT_CCUONLINENOTICE2,data,sizeof data,false)) <= 0)
	{
		ret = TASK_ERR_TIMEOUT;
	}
	else if( HDSendBuffer(handle,data,packlen,&tv) != 0)
	{
		task_node->SetState(KSGDeviceNode::dsOffline);
		ret = TASK_ERR_TIMEOUT;
	}
	else 
	{
		tv = KSGGetTaskTimeoutIntval();
		if((packlen = HDRecvBuffer(handle,data,sizeof data,&tv)) <= 0)
		{
			task_node->SetState(KSGDeviceNode::dsOffline);
			ret = TASK_INVALID_CONN;
		}
		else if(UnPackResponseStruct(req,&msg_type,data,packlen))
		{
			task_node->SetState(KSGDeviceNode::dsOffline);
			ret = TASK_INVALID_CONN;
		}
		else if(req->ResponseCode != RC_SUCCESS)
		{
			ret = TASK_ERR_EXECUTE;
			// 认为脱机
			task_node->SetState(KSGDeviceNode::dsOffline);
		}
		else
		{
			task_node->SetState(KSGDeviceNode::dsOnline);
			task_node->update_time();
			ret = TASK_SUCCESS;
		}
	}
	task->SetNeedResponse(false);
	return ret;
}
/////////////////////////////////////////////////////////////////////////
// IHDAddBlackCard
int IHDAddBlackCard::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	HDDownloadBlkCard dl;
	return dl.DownloadBlackCard(ADD_BLK_LIST,node,task);
}

int IHDDelBlackCard::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	HDDownloadBlkCard dl;
	return dl.DownloadBlackCard(DEL_BLK_LIST,node,task);
}

int IHDBatchDownloadBlkCard::dowload_blkcard(KSGDeviceNode* node,Task* task,std::string &ret_ver)
{
	// 增加，删除黑名单
	int ret = TASK_ERR_COMMON;
	try
	{
		int result,i;
		task->SetNeedResponse(false);
		char data[300];
		char cardid[512];
		std::string cardid_str = task->GetParams().GetParam(XML_KEY_CARDID);
		std::string version = task->GetParams().GetParam(XML_KEY_VERNUM);
		int count = task->GetParams().GetParamIntVal(XML_KEY_FTFLAG);
		KSGDeviceNode* task_node = task->GetDeviceNode();
		unsigned short addr;
		if(count <= 0 || count > 50 || cardid_str.empty() || cardid_str.c_str() == NULL)
			return TASK_ERR_PARAM;
		if(cardid_str.length() < count * 10)
			return TASK_ERR_PARAM;
		memcpy(cardid,cardid_str.c_str(),cardid_str.length());
		addr = GetDeviceAddress(task->GetDeviceNode());
		// 准备发送名单报文
		HD8583STRUCT req;
		req.Init();
		req.SetFieldValue(FIELD_ADDRESS,addr); // 终端地址
		req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId()); // 终端机号
		unsigned long encode_ver = EncodeVersionNum(version.c_str()); // 压缩版本号
		ACE_DEBUG((LM_ERROR,"blk encodever[%d]",encode_ver));
		req.SetFieldValue(FIELD_VERSIONOFLIST,encode_ver);	// 黑名单版本号
		try
		{
			for(i = 0;i < count; ++i)
			{
				if(xutil::StringUtil::Str2Hex(cardid + i*10,(unsigned char*)data+i*5,10)==-1)
					return TASK_ERR_PARAM;
				data[i*5] = (data[i*5] == 0) ? ADD_BLK_LIST : DEL_BLK_LIST ;
			}
		}
		catch (...)
		{
			return TASK_ERR_PARAM;
		}

	
		ACE_HEX_DUMP((LM_TRACE,data,count*5));
		req.SetFieldValue(FIELD_ADDITIONALDATA2,data,count*5);  //  交易卡号
		data[0] = count; 
		req.SetFieldValue(FIELD_ADDITIONALDATA3,data,1); // 卡号条数
		ACE_OS::memset(data,0,sizeof data);
		ACE_HANDLE handler = ACE_INVALID_HANDLE;
		ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
		int recvlen = -1;
		size_t packlen;
		handler = task->_handle;
		ACE_DEBUG((LM_DEBUG,"下载设备[%s]黑名单，版本[%s]",node->get_name().c_str(),version.c_str()));
		// 压缩数据包
		if((packlen = PackRequestStruct(req,MT_UPDATELIST2,data,sizeof data,true)) == 0)
		{
			// 错误的数据包
			ret = TASK_ERR_COMMON;
			return ret;
		}
		ACE_HEX_DUMP((LM_DEBUG,data,packlen));
		// 等待时间

		if((result=HDSendBuffer(handler,data,packlen,&tv))) // 发送数据包
		{
			ACE_DEBUG((LM_ERROR,"发送黑明单返回失败，返回码[%d]",result));
			ret = TASK_ERR_TIMEOUT;
			return ret;
		}
		ACE_DEBUG((LM_DEBUG,"下载设备[%s]黑名单，等待设备应答",node->get_name().c_str()));
		int wait_time = 150;
		KSGThreadUtil::Sleep(wait_time);
		//ACE_DEBUG((LM_DEBUG,"下载设备[%s]黑名单，等待设备应答2",node->get_name().c_str()));
		tv = ACE_Time_Value(1,0);
		if((recvlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0) // 接收数据包
		{
			
			if(recvlen == -2)
				ret = TASK_INVALID_CONN;
			else
				ret = TASK_ERR_TIMEOUT;
		}
		else
		{
			HD8583STRUCT resp;
			MESSAGETYPE msg_type;
			if(recvlen < 17)
			{
				ACE_DEBUG((LM_ERROR,"下传黑名单设备应答错误dev[%s]",task_node->GetPhyId().c_str()));
				ret = TASK_ERR_TIMEOUT;
			}
			else if(UnPackResponseStruct(resp,&msg_type,data,recvlen)) // 解压数据包
			{
				ACE_DEBUG((LM_ERROR,"下传黑名单设备返回包不合法dev[%s]",task_node->GetPhyId().c_str()));
				ret = TASK_ERR_EXECUTE;
			}
			else if( (req->Address != resp->Address)
				|| (req->VerOfList != resp->VerOfList)) // 比较POS机应答给我的黑名单版本号
			{
				char ver[15] = "";
				ACE_DEBUG((LM_ERROR,"blk reqaddr[%d],resqaddr[%d],reqverlist[%d],respverlist[%d]",req->Address,resp->Address,req->VerOfList,resp->VerOfList));
				ACE_HEX_DUMP((LM_DEBUG,data,recvlen));
				DecodeVersionNum(resp->VerOfList,ver);
				ACE_DEBUG((LM_ERROR,"发送黑名单返回失败，返回码[%d]设备[%d][%s]版本号[%s]"
					,resp->ResponseCode,task_node->GetDevId(),task_node->get_name().c_str(),ver));
				if(resp->ResponseCode != 39)
				{

					ret = TASK_ERR_EXECUTE;
					return ret;
				}
				else
				{
					// 可能版本号已经被更新
					ACE_DEBUG((LM_INFO,"设备[%d][%s]设备版本号[%s],系统版本号[%s]"
						,task_node->GetDevId(),task_node->get_name().c_str(),ver,version.c_str()));
					ret = TASK_SUCCESS;
					task_node->update_time();
				}
			}
			else
				ret = TASK_SUCCESS;
			if(TASK_SUCCESS == ret)
			{
				// 成功后发送应答给后台
				ACE_DEBUG((LM_DEBUG,"下载设备[%s]黑名单，设备应答成功",node->get_name().c_str()));
				//KSGTaskResponse &tresp = task->GetResponse();
				//tresp.AddField(XML_KEY_CARDID,cardid);
				char version_str[14] = "";
				DecodeVersionNum(resp->VerOfList,version_str);
				//tresp.AddField(XML_KEY_VERNUM,version_str);
				//ACE_DEBUG((LM_INFO,"更新设备黑名单版本成功id[%d][%s]"
				//	,task_node->GetDevId(),version_str));
				ret_ver = version;
			}

		}
		return ret;
	}
	catch(KeyNotFoundException& )
	{
		return TASK_ERR_COMMON;
	}
	catch(...)
	{
		return TASK_ERR_COMMON;
	}
}
int IHDBatchDownloadBlkCard::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	std::string version;
	int ret = dowload_blkcard(node,task,version);
	if(ret == TASK_SUCCESS)
	{
		// 应答
		DRTPPoolType::SmartObject obj;
		try
		{
			obj = KsgGetDrtpPool()->Alloc();
		}
		catch (NoneResourceException& )
		{
			// 没有资源	
			ACE_DEBUG((LM_ERROR,"申请DRTP连接失败！"));
			return TASK_ERR_EXECUTE;
		}
		if(obj->Connect())
		{
			// 连接失败
			return TASK_ERR_EXECUTE;
		}
		obj->SetRequestHeader(930046);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
		obj->AddField(F_LVOL5,node->GetDevId());
		obj->AddField(F_SSERIAL0,version.c_str());
		int retries = 3;
		ret = TASK_ERR_EXECUTE;
		while(retries-- > 0)
		{
			if(obj->SendRequest(5000))
			{
				// 发送指令失败
				ACE_DEBUG((LM_DEBUG,"应答更新结果失败"));
			}
			else if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"更新黑名单库版本失败,dev[%s],ret[%d][%s]"
					,node->GetPhyId().c_str(),obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
			}
			else
			{
				ACE_DEBUG((LM_INFO,"更新设备黑名单版本成功id[%d][%s]"
					,node->GetDevId(),version.c_str()));
				ret = TASK_SUCCESS;
				node->update_time();
				break;
			}
		}
	}
	return ret;
}
int IHDSetCardPrivileges::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	std::string rights = task->GetParams().GetParam(XML_KEY_CARDRIGHTTYPE);
	int i,j;
	char right_buf[257] = "";
	/*
	for(j=i=0;i < rights.length() && i < sizeof(right_buf) - 1;++i)
	{
		if(rights.at(i) == '1')
			right_buf[j++] = i;
	}
	*/
	//ACE_DEBUG((LM_INFO,"right[%s]",rights.c_str()));
	for(i=0; i < rights.length(); i+=2)
	{
		char temp[3] = "";
		temp[0] = rights.at(i);
		temp[1] = rights.at(i+1);
		unsigned char t = (unsigned char)strtoul(temp,NULL,16);
		//ACE_DEBUG((LM_INFO,"parse data[%d]",t));
		for(j = 0;j < 8; ++j)
		{
			right_buf[1+i*4+j] = (((t >> (7 - j)) & 0x01) == 1) ? (1+i*4+j) : 0;
		}
	}
	//ACE_HEX_DUMP((LM_INFO,right_buf,256));
	KSGDeviceNode* task_node = task->GetDeviceNode();
	unsigned short addr = GetDeviceAddress(task_node);
	HD8583STRUCT req;
	req.SetFieldValue(FIELD_ADDRESS,addr);
	req.SetFieldValue(FIELD_ADDITIONALDATA2,right_buf,256);
	req.SetFieldValue(FIELD_TERMINALID,(short)task_node->GetTermId());
	char data[1024] = "";
	int packlen;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	MESSAGETYPE msg_type;
	ACE_HANDLE handler = task->_handle;
	int ret ;
	if( (packlen = PackRequestStruct(req,MT_AUTHGROUP2,data,sizeof data,true)) <= 0)
	{
		ret = TASK_ERR_TIMEOUT;
	}
	else if( HDSendBuffer(handler,data,packlen,&tv) != 0)
	{
		ret = TASK_ERR_TIMEOUT;
	}
	else 
	{
		//ACE_HEX_DUMP((LM_INFO,data,packlen));
		// 等待 50 ms 应答
		KSGThreadUtil::Sleep(50);
		tv = KSGGetTaskTimeoutIntval();
		if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
		{
			ret = TASK_ERR_TIMEOUT;
		}
		else if(UnPackResponseStruct(req,&msg_type,data,packlen))
		{
			ret = TASK_ERR_EXECUTE;
		}
		else if(req->ResponseCode != RC_SUCCESS)
		{
			ret = TASK_ERR_EXECUTE;
			ACE_DEBUG((LM_INFO,"更新设备分组权限失败!! id[%d]dev[%s]"
				,task_node->GetDevId(),task_node->GetPhyId().c_str()));
		}
		else
		{
			ACE_DEBUG((LM_INFO,"更新设备分组权限成功id[%d]dev[%s]"
				,task_node->GetDevId(),task_node->GetPhyId().c_str()));
			ret = TASK_SUCCESS;
		}
	}
	task->SetNeedResponse();
	return ret;
}

int HDSetFeeRate::do_set_fee_rate(KSGDeviceNode *node,KSGDeviceNode::Task *task,unsigned char *rate_buf,int len)
{
	int ret = 0;
	KSGDeviceNode* task_node = task->GetDeviceNode();
	unsigned short addr = GetDeviceAddress(task_node);
	HD8583STRUCT req;
	req.SetFieldValue(FIELD_ADDRESS,addr);
	req.SetFieldValue(FIELD_ADDITIONALDATA2,rate_buf,len);
	req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId());
	char data[1024] = "";
	int packlen;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	MESSAGETYPE msg_type;
	ACE_HANDLE handler = task->_handle;
	if( (packlen = PackRequestStruct(req,MT_SET_FEE_RATE2,data,sizeof data,true)) <= 0)
	{
		ACE_DEBUG((LM_ERROR,"搭伙费数据包错误!"));
		ret = TASK_ERR_EXECUTE;
	}
	else if( HDSendBuffer(handler,data,packlen,&tv) != 0)
	{
		ACE_DEBUG((LM_ERROR,"发送搭伙费数据失败!"));
		ret = TASK_ERR_TIMEOUT; 
	}
	else 
	{
		KSGThreadUtil::Sleep(200);
		tv = KSGGetTaskTimeoutIntval();
		if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
		{
			ret = TASK_ERR_TIMEOUT;
		}
		else if(UnPackResponseStruct(req,&msg_type,data,packlen))
		{
			ACE_DEBUG((LM_ERROR,"接收搭伙费数据不正确!"));
			ret = TASK_ERR_EXECUTE;
		}
		else if(req->ResponseCode != RC_SUCCESS)
		{
			ACE_DEBUG((LM_INFO,"更新设备搭伙费比率失败id[%d]dev[%s],返回码[%d]"
				,task_node->GetDevId(),task_node->GetPhyId().c_str(),req->ResponseCode));
			ret = TASK_ERR_EXECUTE;
		}
		else
		{
			ACE_DEBUG((LM_INFO,"更新设备搭伙费比率成功id[%d]dev[%s]"
				,task_node->GetDevId(),task_node->GetPhyId().c_str()));
			ret = TASK_SUCCESS;
		}
	}
	return ret;
}
int IHDSetFeeRate::ExecuteTask(KSGDeviceNode* node,Task* task)
{

	int ret = 0;
	HDSetFeeRate feerate;
	unsigned char right_buf[256];
	memset(right_buf,0,sizeof right_buf);
	KSGDeviceNode* task_node = task->GetDeviceNode();
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// 如果是充值交易
		obj->SetRequestHeader(950043);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
		obj->AddField(F_LVOL0,task_node->GetDevId());
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_INFO,"充值冲正交易失败,连接DRTP失败，重试!!!"));
			return 1;
		}
		// 发送请求
		if(!obj->SendRequest(3000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"下载设备搭伙费参数失败,dev[%d]ret[%d]",
					task_node->GetDevId(),obj->GetReturnCode()));
				return TASK_ERR_EXECUTE;
			}
			while(obj->HasMoreRecord())
			{
				ST_PACK *pack = obj->GetNextRecord();
				int feetype = pack->lvol1;
				int rate = pack->lvol2;
				if( feetype > 0 && feetype < sizeof right_buf)
					right_buf[feetype-1] = rate;
			}
		}
		else
			return TASK_ERR_TIMEOUT;
	}
	return feerate.do_set_fee_rate(node,task,right_buf,sizeof right_buf);
	
}

int IHDSetFeeRate2::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	HDSetFeeRate feerate;
	unsigned char rate_buf[256];
	char temp[3] = "";
	int i;
	std::string cardbuf = task->GetParams().GetParam(XML_KEY_CARDRIGHTTYPE);
	if(cardbuf.length()!=256*2)
		return TASK_ERR_PARAM;

	for(i=0;i<256;++i)
	{
		memcpy(temp,cardbuf.c_str()+i*2,2);
		rate_buf[i] = (unsigned char)strtoul(temp,NULL,16);
	}

	return feerate.do_set_fee_rate(node,task,rate_buf,sizeof rate_buf);
}

int IHDCtlPenStock::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	unsigned char ctlCmd = task->GetParams().GetParamIntVal(XML_KEY_PENSTOCKCMD);

	KSGDeviceNode* task_node = task->GetDeviceNode();
	unsigned long termsn  = ACE_OS::strtoul(task_node->GetPhyId().c_str(),NULL,10);
	unsigned short addr = GetDeviceAddress(task_node);
	HD8583STRUCT req;
	req.SetFieldValue(FIELD_TERMINALSN,termsn);
	req.SetFieldValue(FIELD_ADDRESS,addr);
	req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId());
	req.SetFieldValue(FIELD_ADDITIONALDATA2,&ctlCmd,1);
	char data[1024] = "";
	int packlen;
	int ret = 0;
	MESSAGETYPE msg_type;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	ACE_HANDLE handler = task->_handle;
	if( (packlen = PackRequestStruct(req,MT_CTRLPENSTOCK,data,sizeof data,true)) <= 0)
	{
		ret = TASK_ERR_EXECUTE;
	}
	else if( HDSendBuffer(handler,data,packlen,&tv) != 0)
	{
		ret = TASK_ERR_TIMEOUT; 
	}
	else 
	{
		KSGThreadUtil::Sleep(50);
		tv = KSGGetTaskTimeoutIntval();
		if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
		{
			ret = TASK_ERR_TIMEOUT;
		}
		else if(UnPackResponseStruct(req,&msg_type,data,packlen))
		{
			ret = TASK_ERR_EXECUTE;
		}
		else if(req->ResponseCode != RC_SUCCESS)
		{
			ACE_DEBUG((LM_INFO,"远程水阀控制失败id[%d]dev[%s],返回码[%d]"
				,task_node->GetDevId(),task_node->GetPhyId().c_str(),req->ResponseCode));
			ret = TASK_ERR_EXECUTE;
		}
		else
		{
			ACE_DEBUG((LM_INFO,"远程水阀控制成功id[%d]dev[%s]"
				,task_node->GetDevId(),task_node->GetPhyId().c_str()));
			ret = TASK_SUCCESS;
		}
	}
	return ret;

}

int IHDCollPosHisSerial::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	static const int record_per_req = 5;
	int ret = 0;
	unsigned char buf[5] = "";
	unsigned char recordbuf[9] = "";
	int start_no = task->GetParams().GetParamIntVal(XML_KEY_STARTNUM);
	int end_no = task->GetParams().GetParamIntVal(XML_KEY_ENDNUM);
	if(end_no < start_no || start_no < 0)
		return TASK_ERR_EXECUTE;
	int i,j;		
	KSGDeviceNode* task_node = task->GetDeviceNode();
	unsigned short addr = GetDeviceAddress(task_node);
	unsigned long termsn = ACE_OS::strtoul(task_node->GetPhyId().c_str(),NULL,10);
	HD8583STRUCT req;
	char data[1024] = "";
	int packlen;
	int index;
	for(index = 1,i = start_no;i <= end_no;i+=record_per_req,++index)
	{
		if(index > 1)
			KSGThreadUtil::Sleep(100);
		j = i + record_per_req;
		j = (j > end_no) ? (end_no + 1) : j;
		req.Init();
		req.SetFieldValue(FIELD_TERMINALSN,termsn);
		req.SetFieldValue(FIELD_ADDRESS,addr);
		req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId());
		buf[0] = j - i;
		req.SetFieldValue(FIELD_ADDITIONALDATA1,buf,1);
		//index = 1;  // 采集序号
		//INT_2_BUF_LE(index,buf);
		buf[0] = 1;
		req.SetFieldValue(FIELD_ADDITIONALDATA2,buf,sizeof(int));
		INT_2_BUF_LE(i,buf);
		ACE_OS::memcpy(recordbuf,buf,4);
		INT_2_BUF_LE(j,buf);
		ACE_OS::memcpy(recordbuf+4,buf,4);
		req.SetFieldValue(FIELD_ADDITIONALDATA3,recordbuf,8);
		ACE_OS::memset(data,0,sizeof data);
		ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
		tv += ACE_Time_Value(2);
		ACE_HANDLE handler = task->_handle;
		MESSAGETYPE msg_type;
		if( (packlen = PackRequestStruct(req,MT_COLLECT_SERIAL1,data,sizeof data,true)) <= 0)
		{
			ret = TASK_ERR_TIMEOUT;
		}
		else if( HDSendBuffer(handler,data,packlen,&tv) != 0)
		{
			ret = TASK_ERR_TIMEOUT;
		}
		else
		{
			KSGThreadUtil::Sleep(60 + 30 * (j-i));
			tv = ACE_Time_Value(2);
			if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
			{
				ACE_DEBUG((LM_ERROR,"补采流水超时！"));
				ret = TASK_INVALID_CONN;
			}
			else if(UnPackResponseStruct(req,&msg_type,data,packlen))
			{
				ACE_DEBUG((LM_ERROR,"补采流水数据包错误！"));
				ret = TASK_ERR_EXECUTE;
			}
			else if(req->ResponseCode != RC_SUCCESS
				//||ACE_OS::memcmp(req->AdditionalData2,buf,sizeof(int))
				)
			{
				// 如果不成功或者返回流水号不一致,认为失败
				ACE_DEBUG((LM_NOTICE,"补采POS机流水失败,dev[%s],serialno[%d]return[%d]"
					,task_node->GetPhyId().c_str(),i,req->ResponseCode));
				ret = TASK_ERR_EXECUTE;
			}
			else
			{
				unsigned char serial_buf[100] = "";
				int offset;
				HDRecordFileReader reader("",0);
				reader.bColHisSeri = true;
				int datalen = req->LenOfAdditionalData1;
				for(offset = 0;offset < datalen;
					offset+=HDRecordFileReader::RECORD_BUF_LEN)
				{
					if(offset + HDRecordFileReader::RECORD_BUF_LEN > datalen)
						break;
					ACE_OS::memcpy(serial_buf,req->AdditionalData1 + offset,HDRecordFileReader::RECORD_BUF_LEN);
					if(reader.SavePosRecord(serial_buf))
					{
						// 保存流水失败
						ret = TASK_ERR_EXECUTE;
						break;
					}
				}
				// 上传流水
				if(offset >= req->LenOfAdditionalData1)
				{
					ret = TASK_SUCCESS;
				}
			}
		}
		if(ret != TASK_SUCCESS)
			break;
	}
	return ret;
}

int IHDDownloadConCode::parse_time_buf(const char* time_str,int str_len,unsigned char *buf)
{
	int i;
	short hour,minute,total_minute;
	char tmp[3] = "";
	int len = str_len/4*4;
	if(len != str_len)
		return -1;
	for(i=0;i<len/4;++i)
	{
		strncpy(tmp,time_str+i*4,2);
		hour = atoi(tmp);
		strncpy(tmp,time_str+i*4+2,2);
		minute = atoi(tmp);
		total_minute = hour * 60 + minute;
		SHORT_2_BUF_LE(total_minute,buf+i*2);
	}
	return 0;
}
int IHDDownloadConCode::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	KSGDeviceNode *task_node = node;
	if(task->GetDeviceNode() != node)
	{
		task_node = task->GetDeviceNode();
	}
	std::string concode;
	try
	{
		concode = task->GetParams().GetParam(XML_KEY_CONCODE);
	}
	catch (...)
	{
		return TASK_ERR_PARAM;
	}
	int ret;
	unsigned char concode_buf[32]="";
	unsigned char tmp[2];
	int len = concode.length() - concode.length() % 2;
	len = (len > 32) ? 32 : len;

	ret = parse_time_buf(concode.c_str(),len,concode_buf);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"餐次时间段错误!"));
		return TASK_ERR_PARAM;
	}
	
	unsigned short addr = GetDeviceAddress(task_node);
	HD8583STRUCT req;
	unsigned long sn = ACE_OS::strtoul(task_node->GetPhyId().c_str(),NULL,10);
	tmp[0] = 0;
	req.SetFieldValue(FIELD_TERMINALSN,sn);
	req.SetFieldValue(FIELD_ADDRESS,addr);
	req.SetFieldValue(FIELD_ADDITIONALDATA1,tmp,1);
	req.SetFieldValue(FIELD_ADDITIONALDATA2,concode_buf,sizeof concode_buf);
	req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId());
	char data[1024] = "";
	int packlen;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	MESSAGETYPE msg_type;
	ACE_HANDLE handler = task->_handle;
	if( (packlen = PackRequestStruct(req,MT_SETCARDTIME2,data,sizeof data,true)) <= 0)
	{
		ret = TASK_ERR_EXECUTE;
	}
	else if( HDSendBuffer(handler,data,packlen,&tv) != 0)
	{
		ret = TASK_ERR_TIMEOUT;
	}
	else 
	{
		//ACE_HEX_DUMP((LM_INFO,data,packlen));
		KSGThreadUtil::Sleep(100);
		tv = KSGGetTaskTimeoutIntval();
		if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
		{
			ret = TASK_ERR_TIMEOUT;
		}
		else if(UnPackResponseStruct(req,&msg_type,data,packlen))
		{
			ret = TASK_ERR_EXECUTE;
		}
		else if(req->ResponseCode != RC_SUCCESS)
		{
			ret = TASK_ERR_EXECUTE;
		}
		else
			ret = TASK_SUCCESS;
	}
	return ret;
}
// 接收补助930077功能号时调用
int IHDDLSubsidyFile::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	KSGDeviceNode *task_node = node;
	if(task->GetDeviceNode() != node)
	{
		task_node = task->GetDeviceNode();
	}
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// 向后台请求补助名单
		obj->SetRequestHeader(849007);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_LVOL0,task_node->GetDevId());
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
			return TASK_ERR_EXECUTE;
		}
		// 发送流水
		if(!obj->SendRequest(3000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"查询补助名单失败[%d]错误码[%d]"
					,task_node->GetDevId(),obj->GetReturnCode()));
				return TASK_ERR_EXECUTE;
			}
			else
			{
				// 设置返回值
				HD_Subsidy_File_Gen gen;
				std::string data_file;
				ST_PACK *data = NULL;
				// 检查补助文件路径
				if(check_subsidy_dir(task_node->GetPhyId().c_str(),data_file))
				{
					ACE_DEBUG((LM_ERROR,"检查补助文件路径失败"));
					return TASK_ERR_EXECUTE;
				}
				data_file += "\\AllowanceFile.dat";
				if(obj->HasMoreRecord())
				{
					data = obj->GetNextRecord();
					// 创建补助文件
					if(gen.open_data_file(data_file.c_str(),data->lvol1))
					{
						ACE_DEBUG((LM_ERROR,"创建补助文件失败[%s]!",data_file.c_str()));
						return TASK_ERR_EXECUTE;
					}
				}
				// 写第一个包
				if(gen.put_one_pack(data))
				{
					ACE_DEBUG((LM_ERROR,"写入补助名单文件失败![%s]",data_file.c_str()));
					return TASK_ERR_EXECUTE;
				}
				// 取后续包并写文件
				while(obj->HasMoreRecord())
				{
					data = obj->GetNextRecord();
					// 生成补助文件
					if(gen.put_one_pack(data))
					{
						ACE_DEBUG((LM_ERROR,"写入补助名单文件失败![%s]",data_file.c_str()));
						return TASK_ERR_EXECUTE;
					}
				}
				// 补全文件
				gen.finish();
				// 准备 ftp 上传
				std::string ipstr = "ftp://" + node->GetDevAddr().GetConnect() + ":";
				ipstr += hd_ccu_ftp_port;
				//ipstr += "/AllowanceFile.dat";
				//std::string to_file(HDA_CCUPATH_RECORD);
				//to_file += "AllowanceFile.dat";
				ipstr += "/AllowanceFile.dat";
				ftp_upload_conf_t conf = {ipstr.c_str(),
				hd_ccu_ftp_user_name.c_str(),
				hd_ccu_ftp_pswd.c_str(),
				data_file.c_str(),5};
				if(KSGNetUtil::ftp_upload_file(&conf)) // FTP 上传文件
				{
					ACE_DEBUG((LM_ERROR,"上传补助名单失败!CCU[%s]",task_node->GetPhyId().c_str()));
					return TASK_ERR_EXECUTE;
				}
				ACE_DEBUG((LM_INFO,"下发补助成功!CCU[%s]",task_node->GetPhyId().c_str()));
				return TASK_SUCCESS;
			}
		}
	}
	return TASK_ERR_EXECUTE;
}

int IHDDLSubsidyFile::check_subsidy_dir(const char *phyno,std::string &out_path)
{
	std::string basepath = KsgGetGateway()->GetConfig()->_basedir;
	basepath = KSGOSUtil::JoinPath(basepath,"subsidy/");
	ACE_DIR* dir = ACE_OS::opendir(basepath.c_str());
	if(!dir)
	{
		if(ACE_OS::mkdir(basepath.c_str()))
		{
			ACE_DEBUG((LM_ERROR,"创建目录失败[%s]",basepath.c_str()));
			return -1;
		}
	}
	else
		ACE_OS::closedir(dir);
	basepath = KSGOSUtil::JoinPath(basepath,phyno);
	dir = ACE_OS::opendir(basepath.c_str());
	if(!dir)
	{
		if(ACE_OS::mkdir(basepath.c_str()))
		{
			ACE_DEBUG((LM_ERROR,"创建目录失败[%s]",basepath.c_str()));
			return -1;
		}
	}
	else 
		ACE_OS::closedir(dir);
	out_path = basepath;
	return 0;
}

ST_PACK HD_Subsidy_File_Gen::g_out_pack;
int HD_Subsidy_File_Gen::g_card_idx_range[] = {
	sizeof(HD_Subsidy_File_Gen::g_out_pack.usset0)-2,
	sizeof(HD_Subsidy_File_Gen::g_out_pack.usset0)-2,
	sizeof(HD_Subsidy_File_Gen::g_out_pack.usset0)-2,
	sizeof(HD_Subsidy_File_Gen::g_out_pack.usset0)-2,
	sizeof(HD_Subsidy_File_Gen::g_out_pack.usset0)-2,
	sizeof(HD_Subsidy_File_Gen::g_out_pack.usset0)-2,
	sizeof(HD_Subsidy_File_Gen::g_out_pack.usset0)-2,
	(sizeof(HD_Subsidy_File_Gen::g_out_pack.scusttypes) - 1),
	(sizeof(HD_Subsidy_File_Gen::g_out_pack.ssectypes) - 1),
	(sizeof(HD_Subsidy_File_Gen::g_out_pack.vsmess) - 2),
	(sizeof(HD_Subsidy_File_Gen::g_out_pack.vsmess) - 2),
	(sizeof(HD_Subsidy_File_Gen::g_out_pack.vsmess) - 2),
	(sizeof(HD_Subsidy_File_Gen::g_out_pack.vsmess) - 2),
	(sizeof(HD_Subsidy_File_Gen::g_out_pack.vsmess) - 2),
};

int HD_Subsidy_File_Gen::get_pack_index(int card_idx)
{
	int idx = (card_idx-1) / get_card_count_per_pack();
	return idx+1;
}

int HD_Subsidy_File_Gen::get_card_count_per_pack()
{
	int count,i;
	count = 0;
	for(i = 0;i < sizeof(g_card_idx_range)/sizeof(int);++i)
	{
		count += g_card_idx_range[i];
	}
	return count*4;
}



HD_Subsidy_File_Gen::~HD_Subsidy_File_Gen()
{
	if(_fp)
	{
		fclose(_fp);
		_fp = NULL;
	}
}

int HD_Subsidy_File_Gen::open_data_file(const char *file_path,int seqno)
{
	if(_fp)
	{
		ACE_OS::fclose(_fp);
		_fp = NULL;
		if(ACE_OS::unlink(file_path))
			return -1;
	}
	if((_fp = ACE_OS::fopen(file_path,"wb+")) == NULL)
		return -1;
	_pack_index = 0;
	ACE_OS::fseek(_fp,0L,SEEK_SET);
	unsigned short seq = static_cast<unsigned short>(seqno);
	if(ACE_OS::fwrite(&seq,sizeof(seq),1,_fp) != 1)
		return -1;
	return 0;
}

int HD_Subsidy_File_Gen::put_one_pack(ST_PACK * data)
{
	if(!_fp)
		return -1;
	if(write_buffer((const char*)data->usset0,98))
		return -1;
	if(write_buffer((const char*)data->usset1,98))
		return -1;
	if(write_buffer((const char*)data->usset2,98))
		return -1;
	if(write_buffer((const char*)data->usset3,98))
		return -1;
	if(write_buffer((const char*)data->usset4,98))
		return -1;
	if(write_buffer((const char*)data->usset5,98))
		return -1;
	if(write_buffer((const char*)data->usset6,98))
		return -1;
	if(write_buffer(data->scusttypes,200))
		return -1;
	if(write_buffer(data->ssectypes,200))
		return -1;
	if(write_buffer(data->vsmess,254))
		return -1;
	if(write_buffer(data->vsvarstr0,254))
		return -1;
	if(write_buffer(data->vsvarstr1,254))
		return -1;
	if(write_buffer(data->vsvarstr2,254))
		return -1;
	if(write_buffer(data->vsvarstr3,254))
		return -1;
	_pack_index++;
	return 0;
}

int HD_Subsidy_File_Gen::finish()
{
	if(!_fp)
		return -1;
	int last_card_count = MAX_CARD_COUNT - (_pack_index * get_card_count_per_pack());
	ssize_t last_pack = last_card_count / 8;
	ssize_t write_len = 0;
	ssize_t written_len = 0;
	ssize_t ret_len;
	unsigned char buf[1024];
	ACE_OS::memset(buf,0,sizeof buf);
	do 
	{
		write_len = ((last_pack - written_len) > 1024) ? 1024 : (last_pack - written_len);
		ret_len = ACE_OS::fwrite(buf,write_len,1,_fp);
		if(ret_len < 1)
		{
			if(ferror(_fp))
				return -1;
		}
		written_len += write_len;
	} while(written_len < last_pack);
	ACE_OS::fclose(_fp);
	_fp = NULL;
	return 0;
}

unsigned char HD_Subsidy_File_Gen::char_to_hex(char c)
{
	if(c >='0' && c <='9')
		return (c - '0');
	else if(c >='A' && c <= 'F')
		return (c - 'A' + 10);
	else if(c >= 'a' && c <= 'f' )
		return (c - 'a' + 10);
	else
		return 0;
}
int HD_Subsidy_File_Gen::write_buffer(const char *buffer,int buf_len)
{
	unsigned char tmp[512];
	size_t write_len;
	int i,len,count;
	len = buf_len/2;
	count = 0;
	do 
	{
		// add 2007-8-16
		// 需要初始化一下
		ACE_OS::memset(tmp,0,sizeof tmp);
		for(i = 0;count < len && i < sizeof(tmp) ;++i,++count)
		{
			tmp[i] = (char_to_hex(buffer[i*2]) << 4) |
				(char_to_hex(buffer[i*2+1]));
		}
		if(i > 0)
		{
			write_len = ACE_OS::fwrite(tmp,i,1,_fp);
			if(write_len < 1)
				return -1;
		}
	} while(count < len);
	return 0;
}
//////////////////////////////////////////////////////////////////////
// HDCCUListenScheduler
HDCCUListenScheduler::HDCCUListenScheduler():KSGScheduler(KSG_SCHD_HD_TCP_SVR)
{
}

HDCCUListenScheduler::~HDCCUListenScheduler()
{

}

void HDCCUListenScheduler::StartListen()
{
	std::string value;
	if(!KsgGetSystemParam(HD_CCU_FTP_USER,value))
	{
		hd_ccu_ftp_user_name = value;
	}
	
	if(!KsgGetSystemParam(HD_CCU_FTP_PSWD,value))
	{
		hd_ccu_ftp_pswd = value;
	}
	if(!KsgGetSystemParam(HD_CCU_FTP_PORT,value))
	{
		hd_ccu_ftp_port = value;
	}
	//ACE_DEBUG((LM_DEBUG,"FTP user[%s],pwd[%s],port[%s]"
	//	,hd_ccu_ftp_user_name.c_str(),hd_ccu_ftp_pswd.c_str()
	//	,hd_ccu_ftp_port.c_str()));
}
void HDCCUListenScheduler::Run()
{
	CCUSvrAcceptor acceptor;
	REACTOR::instance()->owner(ACE_OS::thr_self());
	// 端口从后台中读取
	std::string value;
	int port = 6001;
	if(KsgGetSystemParam(HD_SYSPARAM_LISTEN_PORT,value))
	{
		ACE_DEBUG((LM_INFO,"获取CCU侦听端口号失败,使用默认端口[%d]",port));
	}
	else
	{
		port = ACE_OS::atoi(value.c_str());
	}
	StartListen();
	if(acceptor.open(ACE_INET_Addr(port),REACTOR::instance()
		,0,1,0) == -1 )
	{
		int err = ACE_OS::last_error();
		ACE_DEBUG((LM_ERROR,"汇多CCU侦听服务启动失败[%d][%s]",err,
				   ACE_OS::strerror(err)));
		return;
	}
	// FIXME : 在这里初始化  curl 不太合理,需要改进
	curl_global_init(CURL_GLOBAL_DEFAULT);
	ACE_DEBUG((LM_INFO,"CCU侦听线程ThreadId[%d]端口[%d]\n",ACE_OS::thr_self(),port));
	int ret = 0;
	try
	{
		while(true)
		{
			ACE_Time_Value t(5,0);
			REACTOR::instance()->handle_events(t);
			Notify();
			if(IsTerminated())
			{
				// 可能在关闭请求时，系统正在处理
				while(!REACTOR::instance()->reactor_event_loop_done())
					REACTOR::instance()->end_reactor_event_loop();
				break;
			}
		}
	}
	catch(...)
	{
		// ignore all exception
	}
	curl_global_cleanup();
	acceptor.close();
}

//////////////////////////////////////////////////////////////////////////
// IHDBatchDownloadWhiteCard 批量下载白名单
int IHDBatchDownloadWhiteCard::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	KSGDeviceNode *task_node = node;
	if(task->GetDeviceNode() != node)
	{
		task_node = task->GetDeviceNode();
	}
	
	int ret;
	unsigned char concode_buf[32]="";
	unsigned char tmp[2];

	unsigned short addr = GetDeviceAddress(task_node);
	HD8583STRUCT req;
	unsigned long sn = ACE_OS::strtoul(task_node->GetPhyId().c_str(),NULL,10);
	tmp[0] = 0;
	req.SetFieldValue(FIELD_TERMINALSN,sn);
	req.SetFieldValue(FIELD_ADDRESS,addr);
	req.SetFieldValue(FIELD_ADDITIONALDATA1,tmp,1);
	req.SetFieldValue(FIELD_ADDITIONALDATA2,concode_buf,sizeof concode_buf);
	req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId());
	char data[1024] = "";
	int packlen;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	MESSAGETYPE msg_type;
	ACE_HANDLE handler = task->_handle;
	if( (packlen = PackRequestStruct(req,MT_SETCARDTIME2,data,sizeof data,true)) <= 0)
	{
		ret = TASK_ERR_EXECUTE;
	}
	else if( HDSendBuffer(handler,data,packlen,&tv) != 0)
	{
		ret = TASK_ERR_TIMEOUT;
	}
	else 
	{
		//ACE_HEX_DUMP((LM_INFO,data,packlen));
		KSGThreadUtil::Sleep(100);
		tv = KSGGetTaskTimeoutIntval();
		if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
		{
			ret = TASK_ERR_TIMEOUT;
		}
		else if(UnPackResponseStruct(req,&msg_type,data,packlen))
		{
			ret = TASK_ERR_EXECUTE;
		}
		else if(req->ResponseCode != RC_SUCCESS)
		{
			ret = TASK_ERR_EXECUTE;
		}
		else
			ret = TASK_SUCCESS;
	}
	return ret;
}
