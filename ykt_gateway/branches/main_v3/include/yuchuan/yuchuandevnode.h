#ifndef _YUCHUANDEVNODE_H_
#define _YUCHUANDEVNODE_H_

#include "ksglobal.h"
#include "scheduler.h"
#include "taskcode.h"
#include "999dev/999devtype.h"
#include "deviceinterface.h"
#include <boost/shared_ptr.hpp>
#include <ace/Thread_Mutex.h>
#include "bit_endian.h"

#ifdef HAS_YUCHUAN_SUPPORT

DECLARE_NAMESPACE_BEGIN(YUCHUAN)

//! 汉军设备初始化类
class YC_DeviceLoader : public KSGDeviceLoader
{
private:
	void SetupDeviceGroup(KSGDeviceNode* node);
public:
	int LoadDevice(KSGDeviceManager* manager);
	int Finish(KSGDeviceManager* manager);
};

//! 汉军设备接口初始化类
class YC_DevInterfaceLoader : public KSGDeviceInterfaceLoader
{
public:
	virtual int LoadInterface(KSGDeviceManager *manager);
};
//! 汉军业务层初始化类
class YC_TaskExecutorLoader : public TaskExecutorLoader
{
public:
	virtual int LoadExecutor();
};

//<! 定义 汉军 设备工厂
typedef KSGDeviceInterfaceFactory
<
TYPELIST_4(DevAbstractObject,YC_DeviceLoader,YC_DevInterfaceLoader,YC_TaskExecutorLoader)
>::Result KSG_YC_DevInterfaceFactory;

//!
class YC_485_Server_Device : public KSGDevice
{
	DECLARE_FACTORY_CREATOR(YC_485_Server_Device)
protected:
	virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw();
public:
	YC_485_Server_Device():KSGDevice(KSG_485_SERVER)
	{}
	virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
};
//!
class YC_Water_Device : public KSGDevice
{
	DECLARE_FACTORY_CREATOR(YC_Water_Device)
protected:
	virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw();
public:
	YC_Water_Device():KSGDevice(KSG_WATER_DEV)
	{}
	virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
};

//////////////////////////////////////////////////////////////////////////
class YCCollectSerialInterface : public KSGDeviceInterface
{
public:
	YCCollectSerialInterface():KSGDeviceInterface(TK_COLLSERIAL_TASK)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};

class YCDownBlackCardInterface:public KSGDeviceInterface
{
public:
	YCDownBlackCardInterface():KSGDeviceInterface(TK_BATCH_DL_BLKCARD)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};

class YCCollectHisSerial : public KSGDeviceInterface
{
public:
	YCCollectHisSerial():KSGDeviceInterface(TK_COLL_HIS_SERIAL)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};

DECLARE_NAMESPACE_END(YUCHUAN);

#endif // HAS_YUCHUAN_SUPPORT
#endif // _YUCHUANDEVNODE_H_
