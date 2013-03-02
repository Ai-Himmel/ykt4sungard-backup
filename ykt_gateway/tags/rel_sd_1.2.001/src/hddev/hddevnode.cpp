#include "stdafx.h"
#include "hddev/hddevnode.h"
#include "hddev/hdsvr.h"
#include "ksgateway.h"
#include "impl/schdimpl.h"
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


/// 注册汇多设备接口
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_COLLSERIAL_TASK,IHDCollectSerial);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_HEARTBEAT_TASK,IHDCollectHeardbeat);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_ADD_BLACKCARD,IHDAddBlackCard);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_DEL_BLACKCARD,IHDDelBlackCard);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_SET_CARD_PRIVILEGE,IHDSetCardPrivileges);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_SET_FEE_RATE,IHDSetFeeRate);
KSG_REG_DEV_INTERFACE(KSG_HD_DEV,TK_COLL_HIS_SERIAL,IHDCollPosHisSerial);

#endif // KSG_HD_DEV_SUPPORT

namespace HDDEV
{
	std::string hd_ccu_ftp_user_name = "hdhdhdhd";
	std::string hd_ccu_ftp_pswd = "11111111";
	std::string hd_ccu_ftp_port = "21";
};

bool HDCCUDevice::Accept(BaseVisitor& guest)
{
	//if(typeid(guest) == typeid(KSGTaskCollHeartBeat::CollHeartBeatVisitor))
	//		return true;
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
bool HDPosDevice::Accept(BaseVisitor& guest)
{
	if(typeid(guest) == typeid(KSGTaskCollHeartBeat::CollHeartBeatVisitor))
		return true;
	if(typeid(guest) == typeid(KSGTaskCollectSerial::CollectSerialVisitor))
		return true;
	return false;
}

int HDPosDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	return 1;
}

bool HDAddPosDevice::Accept(BaseVisitor& guest)
{
	if(typeid(guest) == typeid(KSGTaskCollHeartBeat::CollHeartBeatVisitor))
		return true;
	if(typeid(guest) == typeid(KSGTaskCollectSerial::CollectSerialVisitor))
		return true;
	return false;
}

int HDAddPosDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	return 1;
}

//////////////////////////////////////////////////////////////////////
// HDDeviceLoader
int HDDeviceLoader::Finish(KSGDeviceManager* manager)
{
	KSGDeviceManager::DeviceList * devs = manager->GetDevices();
	//std::for_each(devs->begin(),devs->end(),
	//	boost::bind(&HDDeviceLoader::SetupDeviceNoticeTask,this,_1));
	return 0;
}
void HDDeviceLoader::SetupDeviceNoticeTask(KSGDeviceNode* node)
{
	
	if(node->GetDeviceType() != KSG_HD_POS_DEV)
		return;
	std::stringstream buf;
	buf<<"<devphyid>"<<node->GetPhyId()<<"</devphyid>";
	TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->AddSysTask(MT_REECHO2,buf.str(),node,ptReal);
	KsgGetGateway()->GetTaskQueue()->AddTask(task);
	return;
	
}
int HDDeviceLoader::LoadDevice(KSGDeviceManager* manager)
{
	ACE_DEBUG((LM_DEBUG,"开始加载汇多设备..."));
	KSGDeviceManager::DeviceList * devs = manager->GetDevices();
	try
	{
		// 设置设备的物理结构关系
		std::for_each(devs->begin(),devs->end(),
			boost::bind(&HDDeviceLoader::SetupDevice,this,manager,_1));
		// 设置指令队列的分组
		std::for_each(devs->begin(),devs->end(),
			boost::bind(&HDDeviceLoader::SetupDeviceGroup,this,_1));
	}
	catch(...)
	{
	}
	return 0;
}

void HDDeviceLoader::SetupDevice(KSGDeviceManager*manager, KSGDeviceNode* node)
{
	int pid = node->GetParentId();
	KSGDeviceNode * pnode;
	if(KSGDeviceNode::NullParentDevId == pid)
	{
		// 汇多设备暂时只有与CCU可以做为设备根结点
		if(node->GetDeviceType() != KSG_HD_SERVER_DEV)
			return;
		// set for loop device
		pnode = manager->FindDevice(KSGDeviceNode::LoopDeviceId);
		if(!pnode)
		{
			ACE_DEBUG((LM_ERROR,"loop 设备不存在"));
			throw LoopDeviceNotExists();
		}
		return;
	}
	pnode = manager->FindDevice(pid);
	if(!pnode)
	{
		// 无法找到父节点的设备设置为 error 状态
		node->SetState(KSGDeviceNode::dsError);
		ACE_DEBUG((LM_ERROR,"设备无法找到父设备节点[%d][%d]",node->GetDevId(),pid));
		return;
	}
	if(NULL == pnode->GetDevice() ||
		(pnode->GetDeviceType() != KSG_999_DEV_SERVER
		&&pnode->GetDeviceType() != KSG_LOOP_DEV_TYPE))
	{
		// 不是 LPORT 出错
		ACE_DEBUG((LM_ERROR,"上级设备[%d]不是LPORT",pnode->GetDevId()));
		return;
	}
	node->SetParent(pnode);
}

void HDDeviceLoader::SetupDeviceGroup(KSGDeviceNode* node)
{
	// 不需要设置 loop device ,
	if(node->GetDeviceType() == KSG_HD_SERVER_DEV)
	{
		int grpid = KsgGetGateway()->GetTaskQueue()->AddDevices(node);
		KSGTaskQueueManager::TaskGroupType* grp = KsgGetGateway()->GetTaskQueue()->
			GetDeviceGroup(grpid);
		KsgGetGateway()->GetDeviceGroupScheduler()->AddNewDeviceGroup(grp);
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
		//KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,TK_COLLSERIAL_TASK);
		//KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,TK_HEARTBEAT_TASK);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,TK_ADD_BLACKCARD);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,TK_DEL_BLACKCARD);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,TK_SET_CARD_PRIVILEGE);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,TK_SET_FEE_RATE);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_POS_DEV,TK_COLL_HIS_SERIAL);
		
		// 注册充值机接口
		//KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,TK_COLLSERIAL_TASK);
		//KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,TK_HEARTBEAT_TASK);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,TK_ADD_BLACKCARD);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,TK_DEL_BLACKCARD);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,TK_SET_CARD_PRIVILEGE);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,TK_SET_FEE_RATE);
		KSG_ADD_DEVICE_INTERFACE(KSG_HD_DEV,KSG_HD_ADD_POS_DEV,TK_COLL_HIS_SERIAL);

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
	KSG_REGISTER_TASK_EXECUTOR(TK_ADD_BLACKCARD,AddBlackCardExec);
	KSG_REGISTER_TASK_EXECUTOR(TK_DEL_BLACKCARD,AddBlackCardExec);
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
	if(HDSendBuffer(handler,buf,packlen,&tv) != 0)
	{
		return TASK_ERR_TIMEOUT;
	}
	
	memset(buf,0,sizeof buf);
	packlen = HDRecvBuffer(handler,buf,sizeof buf,&tv);
	if(packlen <= 0)
	{
		return TASK_ERR_CONNECT;
	}
	MESSAGETYPE msg_type;
	if(UnPackResponseStruct(req,&msg_type,buf,packlen)!=0)
	{
		ACE_DEBUG((LM_DEBUG,"回响测试失败"));
		return TASK_ERR_CONNECT;
	}
	task_node->SetState(KSGDeviceNode::dsOnline);
	ACE_DEBUG((LM_DEBUG,"回响测试成功![%u][%x]",termid,req->ResponseCode));
	return TASK_SUCCESS;
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

int IHDSetCardPrivileges::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	std::string rights = task->GetParams().GetParam(XML_KEY_CARDRIGHTTYPE);
	int i,j;
	char right_buf[257] = "";
	for(j=i=0;i < rights.length() && i < sizeof(right_buf) - 1;++i)
	{
		if(rights.at(i) == '1')
			right_buf[j++] = i;
	}
	KSGDeviceNode* task_node = task->GetDeviceNode();
	unsigned short addr = GetDeviceAddress(task_node);
	HD8583STRUCT req;
	req.SetFieldValue(FIELD_ADDRESS,addr);
	req.SetFieldValue(FIELD_ADDITIONALDATA2,right_buf,strlen(right_buf));
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
	else if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
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
	task->SetNeedResponse();
	return ret;
}

int IHDSetFeeRate::ExecuteTask(KSGDeviceNode* node,Task* task)
{
#define _BIT_LENGTH (sizeof(unsigned char) * 8)

	int ret = 0;
	int rate = task->GetParams().GetParamIntVal(XML_KEY_FEE);
	std::string cardlist = task->GetParams().GetParam(XML_KEY_CARDRIGHTTYPE);
	if(rate < 0 || rate >= 100)
		return TASK_ERR_EXECUTE;
	int i;
	char cardstr[100] = "";
	ACE_OS::strncpy(cardstr,cardlist.c_str(),sizeof cardstr);
	unsigned char right_buf[256] = "";
	char temp[3] = "";
	for(i = 0;i < 256 ;)
	{
		unsigned char bit;
		strncpy(temp,cardstr + (i / _BIT_LENGTH * 2),2);
		bit = (unsigned char)ACE_OS::strtoul(temp,NULL,16);
		for(int j = 0;j < _BIT_LENGTH;j++)
		{
			if(bit & (1 << (_BIT_LENGTH - j - 1)))
				right_buf[i] = (char)rate;
			i++;
		}
	}

	KSGDeviceNode* task_node = task->GetDeviceNode();
	unsigned short addr = GetDeviceAddress(task_node);
	HD8583STRUCT req;
	req.SetFieldValue(FIELD_ADDRESS,addr);
	req.SetFieldValue(FIELD_ADDITIONALDATA2,right_buf,sizeof right_buf);
	req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId());
	char data[1024] = "";
	int packlen;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	MESSAGETYPE msg_type;
	ACE_HANDLE handler = task->_handle;
	if( (packlen = PackRequestStruct(req,MT_SET_FEE_RATE2,data,sizeof data,true)) <= 0)
	{
		ret = TASK_ERR_EXECUTE;
	}
	else if( HDSendBuffer(handler,data,packlen,&tv) != 0)
	{
		ret = TASK_ERR_TIMEOUT; 
	}
	else if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
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
	return ret;
}

int IHDCollPosHisSerial::ExecuteTask(KSGDeviceNode* node,Task* task)
{

	int ret = 0;
	unsigned char buf[5] = "";
	unsigned char recordbuf[9] = "";
	int start_no = task->GetParams().GetParamIntVal(XML_KEY_STARTNUM);
	int end_no = task->GetParams().GetParamIntVal(XML_KEY_ENDNUM);
	if(end_no < start_no || start_no < 0)
		return TASK_ERR_EXECUTE;
	int i ;
	KSGDeviceNode* task_node = task->GetDeviceNode();
	unsigned short addr = GetDeviceAddress(task_node);
	unsigned long termsn = ACE_OS::strtoul(task_node->GetPhyId().c_str(),NULL,10);
	HD8583STRUCT req;
	char data[1024] = "";
	int packlen;
	int index;
	for(index = 1,i = start_no;i <= end_no;i++,++index)
	{
		req.Init();
		req.SetFieldValue(FIELD_TERMINALSN,termsn);
		req.SetFieldValue(FIELD_ADDRESS,addr);
		req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId());
		buf[0] = 1;
		req.SetFieldValue(FIELD_ADDITIONALDATA1,buf,1);
		INT_2_BUF(index,buf);
		req.SetFieldValue(FIELD_ADDITIONALDATA2,buf,sizeof(int));
		INT_2_BUF(i,buf);
		ACE_OS::memcpy(recordbuf,buf,4);
		INT_2_BUF((i+1),buf);
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
		else if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
		{
			ret = TASK_ERR_TIMEOUT;
		}
		else if(UnPackResponseStruct(req,&msg_type,data,packlen))
		{
			ret = TASK_ERR_EXECUTE;
		}
		else if(req->ResponseCode != RC_SUCCESS
			//||ACE_OS::memcmp(req->AdditionalData2,buf,sizeof(int))
			)
		{
			// 如果不成功或者返回流水号不一致,认为失败
			ret = TASK_ERR_EXECUTE;
		}
		else
		{
			unsigned char serial_buf[100] = "";
			int offset;
			HDRecordFileReader reader("");
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
			if(offset > req->LenOfAdditionalData1)
				ret = TASK_SUCCESS;
		}
		if(ret != TASK_SUCCESS)
			break;
	}
	return ret;
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
		ACE_DEBUG((LM_ERROR,"汇多CCU侦听服务启动失败\n"));
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

