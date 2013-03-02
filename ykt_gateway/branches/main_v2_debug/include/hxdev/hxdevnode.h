#ifndef _KSG_HX_DEVNODE_H_
#define _KSG_HX_DEVNODE_H_

#ifdef _MSC_VER
# pragma once
#endif

#include "deviceinterface.h"
#include "scheduler.h"
#include "taskcode.h"
#include "proactor_def.h"
#include "hxdev/hxkqinfo.h"
#include "CIniFile.h"
#include "ksglobal.h"
#include "ksgateway.h"

#define KSG_HX_KQ_DEV "0121"

namespace HXDEV
{

	//! 昊星考勤机设备
	class HXKqDevice : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(HXKqDevice)
	protected:
		virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
		virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ();
	public:
		HXKqDevice():KSGDevice(KSG_HX_KQ_DEV)
		{}
		virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
	};
	
	typedef int (__stdcall* lp_AddNewEqm)(BYTE * msg);   //昊星添加考勤机接口
	typedef int (__stdcall* lp_DataRtn)(char *desIP);    //昊星数据采集接口
	//! 昊星考勤机数据采集
	class IHXCollectData : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHXCollectData)

	public:
		IHXCollectData():KSGDeviceInterface(TK_COLLSERIAL_TASK),bDllLoad(false)
		{
			hDLL = LoadLibrary("SetTimedll.dll");
			if(!hDLL)
			{
				ACE_DEBUG((LM_ERROR,"装载动态库SetTimedll.dll失败"));
				return;
			}

			addEqm = (lp_AddNewEqm)GetProcAddress(hDLL,"AddNewEqm");
			dataRtn	= (lp_DataRtn)GetProcAddress(hDLL,"DataRtn");

			if(!addEqm || !dataRtn)
			{
				ACE_DEBUG((LM_ERROR,"动态获取函数地址错误"));
				return;
			}

			sprintf(config_path,"%s\\eqminfo.ini",KsgGetGateway()->GetConfig()->_basedir.c_str());
			memset(kqMsg,0,sizeof(kqMsg));
			bDllLoad = true;	
		}
		~IHXCollectData()
		{
			if(bDllLoad)
				FreeLibrary(hDLL);
		}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	private:
		HINSTANCE	hDLL;
		lp_AddNewEqm addEqm;
		lp_DataRtn dataRtn;
		BOOL bDllLoad;
		BYTE kqMsg[12];
		char config_path[MAX_PATH];
	};
	
	//! 昊星设备初始化类
	class HXDeviceLoader : public KSGDeviceLoader
	{
	private:
		void SetupDeviceGroup(KSGDeviceNode* node);
	public:
		int LoadDevice(KSGDeviceManager* manager);
		int Finish(KSGDeviceManager* manager);
	};

	//! 昊星设备接口初始化类
	class HXDevInterfaceLoader : public KSGDeviceInterfaceLoader
	{
	public:
		virtual int LoadInterface(KSGDeviceManager *manager);
	};
	//! 昊星业务层初始化类
	class HXTaskExecutorLoader : public TaskExecutorLoader
	{
	public:
		int LoadExecutor();
	};

	//<! 定义 昊星 设备工厂
	typedef KSGDeviceInterfaceFactory
		<
		TYPELIST_4(DevAbstractObject,HXDeviceLoader,HXDevInterfaceLoader,HXTaskExecutorLoader)
		>::Result KSGHXDevInterfaceFactory;
}

#endif // _KSG_HX_DEVNODE_H_

