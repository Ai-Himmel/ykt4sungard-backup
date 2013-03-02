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

	//! ��ǿ��ڻ��豸
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
	
	typedef int (__stdcall* lp_AddNewEqm)(BYTE * msg);   //�����ӿ��ڻ��ӿ�
	typedef int (__stdcall* lp_DataRtn)(char *desIP);    //������ݲɼ��ӿ�
	//! ��ǿ��ڻ����ݲɼ�
	class IHXCollectData : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHXCollectData)

	public:
		IHXCollectData():KSGDeviceInterface(TK_COLLSERIAL_TASK),bDllLoad(false)
		{
			hDLL = LoadLibrary("SetTimedll.dll");
			if(!hDLL)
			{
				ACE_DEBUG((LM_ERROR,"װ�ض�̬��SetTimedll.dllʧ��"));
				return;
			}

			addEqm = (lp_AddNewEqm)GetProcAddress(hDLL,"AddNewEqm");
			dataRtn	= (lp_DataRtn)GetProcAddress(hDLL,"DataRtn");

			if(!addEqm || !dataRtn)
			{
				ACE_DEBUG((LM_ERROR,"��̬��ȡ������ַ����"));
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
	
	//! ����豸��ʼ����
	class HXDeviceLoader : public KSGDeviceLoader
	{
	private:
		void SetupDeviceGroup(KSGDeviceNode* node);
	public:
		int LoadDevice(KSGDeviceManager* manager);
		int Finish(KSGDeviceManager* manager);
	};

	//! ����豸�ӿڳ�ʼ����
	class HXDevInterfaceLoader : public KSGDeviceInterfaceLoader
	{
	public:
		virtual int LoadInterface(KSGDeviceManager *manager);
	};
	//! ���ҵ����ʼ����
	class HXTaskExecutorLoader : public TaskExecutorLoader
	{
	public:
		int LoadExecutor();
	};

	//<! ���� ��� �豸����
	typedef KSGDeviceInterfaceFactory
		<
		TYPELIST_4(DevAbstractObject,HXDeviceLoader,HXDevInterfaceLoader,HXTaskExecutorLoader)
		>::Result KSGHXDevInterfaceFactory;
}

#endif // _KSG_HX_DEVNODE_H_

