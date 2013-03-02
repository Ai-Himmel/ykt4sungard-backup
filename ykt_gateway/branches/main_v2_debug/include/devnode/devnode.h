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


//! Loop �豸
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


//! loop �豸�ڵ�
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
//<! ���� LOOP �豸����
typedef KSGDeviceInterfaceFactory
<
TYPELIST_4(DevAbstractObject,KSGLoopDeviceLoader,KSGLoopDevInterLoader,KSGLoopExecutorLoader)
>::Result KSGLoopDevInterfaceFactory;

////////////////////////////////////////////////////////////////////
// �豸�ӿڶ���
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
	// ���� LOOP �豸����
	/* ���´����������ֽڶ���ʹ�õ� */
#ifndef WIN32
#ifndef __GNUC__
#define __PACKED__
#else	// __GNUC__
#define __PACKED__	__attribute__ ((packed))
#endif	// __GNUC__
#else	// WIN32
#define __PACKED__ 
#endif	// WIN32

	// ���µĶ���İ����ֽڶ���
#if defined(WIN32) || defined(__GNUC__)
#pragma pack(push,1)
#else
#pragma options align=packed
#endif

	//{{{ ���Ľṹ
	struct KSG_GW_PACK_t
	{
		int length;					// ���ݶγ���
		int func_no;					// ���ܺ�
		int pack_index;					// ������� �� 0 ��ʼ
		long retcode;					// ������Ӧ��
		int next_pack;					// ������ݰ����������Ϊ 0 ��ʾû�к�̰�
		char enc_type;					// �����㷨��0 ��ʾ�޼���,1 ��ʾ128λAES
		char padded;					// ����Ǽ��ܣ���ʾ�Ƿ񱻲�λ��1:�� 0:����
		unsigned char CRC[16];				// CRC У�����
		char data[1];					// ���ݶΣ����ݶε������Ǽ��ܵ�
	}__PACKED__;
	//}}}

#if defined(WIN32) || defined(__GNUC__)
#pragma pack()
#else
#pragma options align=reset
#endif
	//! Loop ���� handler
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
	//! Loop �ӿڶ���
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
	//! Loop �����߳�
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
// ҵ�����
#define KSG_LI_INTERNAL_ERROR	99999

	// ������
#define KSG_ENC_TYPE_NONE	0
	// ʹ�� AES 128 �㷨����
#define KSG_ENC_TYPE_AES128 1

}
#endif // _DEVNODE_H_
