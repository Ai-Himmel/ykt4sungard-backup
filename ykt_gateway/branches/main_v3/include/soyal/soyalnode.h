#ifndef _KSG_SOYALNODE_H_
#define _KSG_SOYALNODE_H_

#ifdef _MSC_VER
# pragma once
#endif

#include "deviceinterface.h"
#include "scheduler.h"
#include "taskcode.h"
#include "proactor_def.h"
#include "CIniFile.h"
#include "ksglobal.h"
#include "ksgateway.h"

#define KSG_SY_716E "8001"
#define KSG_SY_721H "9000"

#define SOYAL_EVENT_CODE_END 0xFFFFFFFF
#define SOYAL_EVENT_CODE_BASE  20000

#define TASK_CODE_DOWNLOAD_CARD 930118

namespace SOYALDEV
{
	//! soyal �������豸
	class SOYALDevice : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(SOYALDevice)
	protected:
		virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
		virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ();
	public:
		SOYALDevice():KSGDevice(KSG_SY_716E)
		{}
		virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
	};
	
	class SOYALReader : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(SOYALReader)
	protected:
		virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
		virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ();
	public:
		SOYALReader():KSGDevice(KSG_SY_721H)
		{}
		virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
	};
	// ���ؿ���
	class ID_SOYAL_DL_Card : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_DL_Card():KSGDeviceInterface(TASK_CODE_DOWNLOAD_CARD)
		{}
		int success_download(int list_id,int device_id);
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	// �ɼ���ˮ
	class ID_SOYAL_CollectData : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_CollectData():KSGDeviceInterface(TK_COLLSERIAL_TASK)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	// ����ʱ����
	class ID_SOYAL_DL_Week : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_DL_Week():KSGDeviceInterface(TK_DOOR_DL_WEEK)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
		TimeSec GetTimeSect(std::string time_str);
	};
	
	// Զ�̿���
	class ID_SOYAL_Ctrl_Door : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_Ctrl_Door():KSGDeviceInterface(TK_CTRL_DOOR_OPEN)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	// �´��豸ʱ��
	class ID_SOYAL_DL_Timer : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_DL_Timer():KSGDeviceInterface(TK_DL_TIMER)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
		void GetDatetime(std::string datetime_str,Datetime_str &datetime);
	};

	// �ϴ��豸ʱ��
	class ID_SOYAL_UL_Timer : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_UL_Timer():KSGDeviceInterface(TK_UL_TIMER)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	
	//! soyal�Ž�ʼ����
	class SOYALDeviceLoader : public KSGDeviceLoader
	{
	private:
		void SetupDeviceGroup(KSGDeviceNode* node);
	public:
		int LoadDevice(KSGDeviceManager* manager);
		int Finish(KSGDeviceManager* manager);
	};

	//! soyal�Ž��ӿڳ�ʼ����
	class SOYALDevInterfaceLoader : public KSGDeviceInterfaceLoader
	{
	public:
		virtual int LoadInterface(KSGDeviceManager *manager);
	};
	//! soyalҵ����ʼ����
	class SOYALTaskExecutorLoader : public TaskExecutorLoader
	{
	public:
		int LoadExecutor();
	};

	//<! ���� soyal �豸����
	typedef KSGDeviceInterfaceFactory
		<
		TYPELIST_4(DevAbstractObject,SOYALDeviceLoader,SOYALDevInterfaceLoader,SOYALTaskExecutorLoader)
		>::Result KSGSOYALDevInterfaceFactory;
}

#endif // _KSG_SOYALNODE_H_

