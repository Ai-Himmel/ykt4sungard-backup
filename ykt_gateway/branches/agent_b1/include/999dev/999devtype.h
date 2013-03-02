#ifndef _999DEVTYPE_H_
#define _999DEVTYPE_H_

#include "deviceinterface.h"

#define KSG_999_DEV_POS	"0226"
#define KSG_999_DEV_SERVER "5301"
#define KSG_999_DEV_JSB "0121"
#define KSG_999_DEV_ADDPOS "0201"

namespace DEV999
{

	class Pos999Device : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(Pos999Device)
	public:
		Pos999Device():KSGDevice(KSG_999_DEV_POS)
		{

		}
		virtual ~Pos999Device()
		{}
		bool Accept(BaseVisitor& guest)
		{ return false; }
	};
	/*
	class Pos999TCPDevice : public KSGDevice
	{
	public:
		Pos999TCPDevice:KSGDevice()
		{}
	};
	*/
	class JSB999Device : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(JSB999Device)
	public:
		JSB999Device():KSGDevice(KSG_999_DEV_JSB)
		{

		}
		virtual ~JSB999Device(){}
		bool Accept(BaseVisitor& guest)
		{ return false; }
	};

	class Server999Device: public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(Server999Device)
	public:
		Server999Device():KSGDevice(KSG_999_DEV_SERVER)
		{

		}
		virtual ~Server999Device(){}
		bool Accept(BaseVisitor& guest)
		{ return false; }
	};

	class AddPos999Device: public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(AddPos999Device)
	public:
		AddPos999Device():KSGDevice(KSG_999_DEV_ADDPOS)
		{

		}
		virtual ~AddPos999Device(){}
		bool Accept(BaseVisitor& guest)
		{ return false; }
	};

	//////////////////////////////////////////////////////////////////////////
	// 999 device factory
	class KSG999DeviceObject : public DevAbstractObject
	{

	};
	class KSG999DeviceLoader : public KSGDeviceLoader
	{
	private:
		void SetDeviceStruct(KSGDeviceManager* manager,KSGDeviceNode* node);
		void SetRunningQueue(KSGDeviceNode* node);
	public:
		int LoadDevice(KSGDeviceManager* manager);
		int Finish(KSGDeviceManager* manager);
	};
	class KSG999DevInterLoader : public KSGDeviceInterfaceLoader
	{
	public:
		virtual ~KSG999DevInterLoader(){}
		virtual int LoadInterface(KSGDeviceManager *manager);
	};
	class KSG999ExecutorLoader : public TaskExecutorLoader
	{
	public:
		int LoadExecutor()
		{
			return -1;
		}

	};
	//<! 定义 999 设备工厂
	typedef KSGDeviceInterfaceFactory
	<
		TYPELIST_4(KSG999DeviceObject,KSG999DeviceLoader,KSG999DevInterLoader,KSG999ExecutorLoader)
	>::Result KSG999DevInterfaceFactory;
};
#endif // _999DEVTYPE_H_

