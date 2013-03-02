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
	//! soyal 控制器设备
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
	// 下载卡号
	class ID_SOYAL_DL_Card : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_DL_Card():KSGDeviceInterface(TASK_CODE_DOWNLOAD_CARD)
		{}
		int success_download(int list_id,int device_id);
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	// 采集流水
	class ID_SOYAL_CollectData : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_CollectData():KSGDeviceInterface(TK_COLLSERIAL_TASK)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	// 下载时间周
	class ID_SOYAL_DL_Week : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_DL_Week():KSGDeviceInterface(TK_DOOR_DL_WEEK)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
		TimeSec GetTimeSect(std::string time_str);
	};
	
	// 远程开门
	class ID_SOYAL_Ctrl_Door : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_Ctrl_Door():KSGDeviceInterface(TK_CTRL_DOOR_OPEN)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	// 下传设备时钟
	class ID_SOYAL_DL_Timer : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_DL_Timer():KSGDeviceInterface(TK_DL_TIMER)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
		void GetDatetime(std::string datetime_str,Datetime_str &datetime);
	};

	// 上传设备时钟
	class ID_SOYAL_UL_Timer : public KSGDeviceInterface
	{
	public:
		ID_SOYAL_UL_Timer():KSGDeviceInterface(TK_UL_TIMER)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	
	//! soyal门禁始化类
	class SOYALDeviceLoader : public KSGDeviceLoader
	{
	private:
		void SetupDeviceGroup(KSGDeviceNode* node);
	public:
		int LoadDevice(KSGDeviceManager* manager);
		int Finish(KSGDeviceManager* manager);
	};

	//! soyal门禁接口初始化类
	class SOYALDevInterfaceLoader : public KSGDeviceInterfaceLoader
	{
	public:
		virtual int LoadInterface(KSGDeviceManager *manager);
	};
	//! soyal业务层初始化类
	class SOYALTaskExecutorLoader : public TaskExecutorLoader
	{
	public:
		int LoadExecutor();
	};

	//<! 定义 soyal 设备工厂
	typedef KSGDeviceInterfaceFactory
		<
		TYPELIST_4(DevAbstractObject,SOYALDeviceLoader,SOYALDevInterfaceLoader,SOYALTaskExecutorLoader)
		>::Result KSGSOYALDevInterfaceFactory;
}

#endif // _KSG_SOYALNODE_H_

