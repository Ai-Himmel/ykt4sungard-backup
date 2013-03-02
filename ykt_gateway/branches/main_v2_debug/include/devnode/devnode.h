#ifndef _DEVNODE_H_
#define _DEVNODE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "ksglobal.h"
#include "taskdef.h"
#include "device.h"
#include "taskqueue.h"
#include "thread.h"
#include "deviceinterface.h"
#include <xutils/xsingleton.h>
#include <iostream>
#include <ace/SOCK_Stream.h>
#include <ace/Svc_Handler.h>
#include <ace/Reactor.h>
#include "osutil.h"
#include "localinterface.h"
#include <ace/DLL.h>


//! Loop 设备
class KSGLoopDevice: public KSGDevice
{
	DECLARE_FACTORY_CREATOR(KSGLoopDevice)
protected:
	virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw();
public:
	KSGLoopDevice():KSGDevice(KSG_LOOP_DEV_TYPE)
	{}
	bool Accept(BaseVisitor& guest);
};


//! loop 设备节点
class KSGLoopDeviceNode : public KSGDeviceNode
{
private:
	std::string _ip;
	std::string _mac;
public:
	KSGLoopDeviceNode(KSGDevice* devtype)
		:KSGDeviceNode(LoopDeviceId,NullParentDevId,devtype)
	{}
	virtual ~KSGLoopDeviceNode()
	{}
};

class KSGLoopDeviceLoader : public KSGDeviceLoader
{
public:
	int LoadDevice(KSGDeviceManager* manager);
	int Finish(KSGDeviceManager* manager);
};

class KSGLoopDevInterLoader : public KSGDeviceInterfaceLoader
{
public:
	virtual ~KSGLoopDevInterLoader(){}
	virtual int LoadInterface(KSGDeviceManager* manager);
};

class KSGLoopExecutorLoader : public TaskExecutorLoader
{

};
//<! 定义 LOOP 设备工厂
typedef KSGDeviceInterfaceFactory
<
TYPELIST_4(DevAbstractObject,KSGLoopDeviceLoader,KSGLoopDevInterLoader,KSGLoopExecutorLoader)
>::Result KSGLoopDevInterfaceFactory;

////////////////////////////////////////////////////////////////////
// 设备接口定义
namespace LOOPDEV 
{
	class DevHeartBeat : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(DevHeartBeat)
	public:
		DevHeartBeat();
		virtual ~DevHeartBeat(){}
		virtual int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	class DevRestartServer : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(DevRestartServer)
	public:
		DevRestartServer();
		virtual ~DevRestartServer(){}
		virtual int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	class DevSetCartState : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(DevSetCartState)
	public:
		DevSetCartState();
		virtual ~DevSetCartState(){}
		virtual int ExecuteTask(KSGDeviceNode *node,Task *task);
	};
	
	////////////////////////////////////////////////////////////////////
	// 定义 LOOP 设备服务
	/* 以下代码是用来字节对齐使用的 */
#ifndef WIN32
#ifndef __GNUC__
#define __PACKED__
#else	// __GNUC__
#define __PACKED__	__attribute__ ((packed))
#endif	// __GNUC__
#else	// WIN32
#define __PACKED__ 
#endif	// WIN32

	// 以下的定义的包会字节对齐
#if defined(WIN32) || defined(__GNUC__)
#pragma pack(push,1)
#else
#pragma options align=packed
#endif

	//{{{ 报文结构
	struct KSG_GW_PACK_t
	{
		int length;					// 数据段长度
		int func_no;					// 功能号
		int pack_index;					// 包的序号 从 0 开始
		long retcode;					// 返回响应码
		int next_pack;					// 后继数据包数量，如果为 0 表示没有后继包
		char enc_type;					// 加密算法，0 表示无加密,1 表示128位AES
		char padded;					// 如果是加密，表示是否被补位，1:是 0:不是
		unsigned char CRC[16];				// CRC 校验代码
		char data[1];					// 数据段，数据段的内容是加密的
	}__PACKED__;
	//}}}

#if defined(WIN32) || defined(__GNUC__)
#pragma pack()
#else
#pragma options align=reset
#endif
	//! Loop 服务 handler
	class LoopDeviceSvcHandler : public ACE_Svc_Handler<ACE_SOCK_STREAM,ACE_MT_SYNCH>
	{
	private:
		int _shutdown_ref;
		ACE_Thread_Mutex _mutex;
		int UnPackData(KSG_GW_PACK_t* pack);
		int PackData(KSG_GW_PACK_t* resp,request_pack* pack);
		int SendResponse(int return_code,KSG_GW_PACK_t* req,request_pack* pack);
		int RecvRequest(int *pRet,KSG_GW_PACK_t* pack);
		int RecvData(ACE_HANDLE hd);
		void safe_close();
		static const int MAX_BUFLEN = 8192;
		virtual ~LoopDeviceSvcHandler();
	public:
		LoopDeviceSvcHandler();
		int open(void*);
		int handle_input(ACE_HANDLE fd);
		int handle_output(ACE_HANDLE fd);
		int handle_close(ACE_HANDLE fd,ACE_Reactor_Mask mask);
		int svc(void);
	};
	//! Loop 接口定义
	class LocalInterface 
	{
	private:
		ACE_DLL _dll;
	public:
		DECLARE_DLL_FUNC(int,Initialize,());
		DECLARE_DLL_FUNC(int,Uninitialize,());
		DECLARE_DLL_FUNC(int,ProcessRequest,(int request_no,request_pack * pack));

		DEFINE_DLL_FUNC(Initialize);
		DEFINE_DLL_FUNC(Uninitialize);
		DEFINE_DLL_FUNC(ProcessRequest);
		
		int LoadDLLFunc();
		~LocalInterface();
	};
	//! Loop 服务线程
#if 0
	class KSGLoopDeviceListenScheduler : public KSGScheduler
	{
		DECLARE_FACTORY_CREATOR(KSGLoopDeviceListenScheduler)
	private:
		static ACE_Reactor _s_LoopReactor;
		static LocalInterface _s_interface;
		friend class LoopDeviceSvcHandler;
	public:
		KSGLoopDeviceListenScheduler();
		virtual ~KSGLoopDeviceListenScheduler();
		virtual void Run();
	protected:
		virtual KSGScheduler& GetObserverable()
		{
			return *this;
		}
	};
#endif
// 业务错误
#define KSG_LI_INTERNAL_ERROR	99999

	// 不加密
#define KSG_ENC_TYPE_NONE	0
	// 使用 AES 128 算法加密
#define KSG_ENC_TYPE_AES128 1

}
#endif // _DEVNODE_H_
