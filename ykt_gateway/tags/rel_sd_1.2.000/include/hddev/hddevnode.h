#ifndef _KSG_HD_DEVNODE_H_
#define _KSG_HD_DEVNODE_H_

#ifdef _MSC_VER
# pragma once
#endif

#include "deviceinterface.h"
#include "scheduler.h"
#include "hddev/hddef.h"
#include "F8583.h"
#include "taskcode.h"
#include "999dev/999devtype.h"
#include "proactor_def.h"

namespace HDDEV
{
	
	//! ���POS���豸
	class HDPosDevice : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(HDPosDevice)
	protected:
		virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	public:
		HDPosDevice():KSGDevice(KSG_HD_POS_DEV)
		{}
		virtual bool Accept(BaseVisitor& guest);
	};
	//! ���CCU�豸
	class HDCCUDevice : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(HDCCUDevice)
	protected:
		virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
		virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ();
	public:
		HDCCUDevice():KSGDevice(KSG_HD_SERVER_DEV)
		{}
		virtual bool Accept(BaseVisitor& guest);
	};
	//! ����ֵ���豸
	class HDAddPosDevice : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(HDAddPosDevice)
	protected:
		virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	public:
		HDAddPosDevice():KSGDevice(KSG_HD_ADD_POS_DEV)
		{}
		virtual bool Accept(BaseVisitor& guest);
		
	};

	//! ���ɼ��Уϣӻ�������ˮ
	class IHDCollectSerial : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDCollectSerial)
	private:
		int CollectRecord(HD8583STRUCT& record);
	public:
		IHDCollectSerial():KSGDeviceInterface(TK_COLLSERIAL_TASK)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	private:
	};
	//! �ɼ�����豸����
	class IHDCollectHeardbeat : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDCollectHeardbeat)
	public:
		IHDCollectHeardbeat():KSGDeviceInterface(TK_HEARTBEAT_TASK)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! ��ʧ��
	class IHDAddBlackCard : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDAddBlackCard)
	public:
		IHDAddBlackCard():KSGDeviceInterface(TK_ADD_BLACKCARD)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! ��ҿ�
	class IHDDelBlackCard : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDDelBlackCard)
	public:
		IHDDelBlackCard():KSGDeviceInterface(TK_DEL_BLACKCARD)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! �����豸������
	class IHDSetCardPrivileges :public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDSetCardPrivileges)
	public:
		IHDSetCardPrivileges():KSGDeviceInterface(TK_SET_CARD_PRIVILEGE)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! �����豸�����
	class IHDSetFeeRate : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDSetFeeRate)
	public:
		IHDSetFeeRate():KSGDeviceInterface(TK_SET_FEE_RATE)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! ����POS����ˮ
	class IHDCollPosHisSerial : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDCollPosHisSerial)
	public:
		IHDCollPosHisSerial():KSGDeviceInterface(TK_COLL_HIS_SERIAL)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	//! ����豸��ʼ����
	class HDDeviceLoader : public KSGDeviceLoader
	{
	private:
		void SetupDevice(KSGDeviceManager* manager,KSGDeviceNode* node);
		void SetupDeviceGroup(KSGDeviceNode* node);
		void SetupDeviceNoticeTask(KSGDeviceNode* node);
	public:
		int LoadDevice(KSGDeviceManager* manager);
		int Finish(KSGDeviceManager* manager);
	};

	//! ����豸�ӿڳ�ʼ����
	class HDDevInterfaceLoader : public KSGDeviceInterfaceLoader
	{
	public:
		virtual int LoadInterface(KSGDeviceManager *manager);
	};
	//! ���ҵ����ʼ����
	class HDTaskExecutorLoader : public TaskExecutorLoader
	{
	public:
		int LoadExecutor();
	};

	//<! ���� ��� �豸����
	typedef KSGDeviceInterfaceFactory
	<
	TYPELIST_4(DevAbstractObject,HDDeviceLoader,HDDevInterfaceLoader,HDTaskExecutorLoader)
	>::Result KSGHDDevInterfaceFactory;
	//! �����������
	class HDCCUListenScheduler : public KSGScheduler
	{
		DECLARE_FACTORY_CREATOR(HDCCUListenScheduler)
	private:
	public:
		HDCCUListenScheduler();
		virtual ~HDCCUListenScheduler();
		virtual void Run();
	protected:
		void StartListen();
		virtual KSGScheduler& GetObserverable()
		{
			return *this;
		}
	};
}

#endif // _KSG_HD_DEVNODE_H_

