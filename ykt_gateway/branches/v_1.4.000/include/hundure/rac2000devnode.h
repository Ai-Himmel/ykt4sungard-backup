#ifndef _RAC2000DEVNODE_H_
#define _RAC2000DEVNODE_H_

#ifdef _MSC_VER
# pragma once
#endif

#include "deviceinterface.h"
#include "hundure/hundure_def.h"
#include "taskcode.h"
#include "999dev/999devtype.h"
#include "proactor_def.h"


namespace HUNDURE
{
#define RAC_RIGHT_DOOR1 0x0
#define RAC_RIGHT_DOOR2 (0x01 << 1)
#define RAC_RIGHT_CHECK_WEEK (0x01 << 3)
#define RAC_RIGHT_CHECK_HOLIDAY (0x01 << 2)

	class HNDR_RAC2000_Base : public HNDR_Device_Base
	{
	protected:
		virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
		virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ();
	public:
		HNDR_RAC2000_Base(NormalDeviceType devtype):HNDR_Device_Base(devtype)
		{}
	};

	class HNDR_RAC2000P : public HNDR_RAC2000_Base
	{
		DECLARE_FACTORY_CREATOR(HNDR_RAC2000P)
	public:
		HNDR_RAC2000P():HNDR_RAC2000_Base(HUNDURE_RAC2000P)
		{}
	};

	class HNDR_RAC2000G : public HNDR_RAC2000_Base
	{
		DECLARE_FACTORY_CREATOR(HNDR_RAC2000G)
	public:
		HNDR_RAC2000G():HNDR_RAC2000_Base(HUNDURE_RAC2000G)
		{}
	};
	
	//////////////////////////////////////////////////////////////
	// 定义设备接口
	//<! RAC2000P 下载名单接口(增加删除名单)
	class ID_HNDR_RACP_DLUL_Card : public KSGDeviceInterface
	{
	public:
		ID_HNDR_RACP_DLUL_Card():KSGDeviceInterface(TK_DOOR_DL_CARD)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//<! RAC2000G 下载名单接口(增加删除名单)
	/*
	class ID_HNDR_RACG_DLUL_Card : public KSGDeviceInterface
	{
	public:
		ID_HNDR_RACG_DLUL_Card():KSGDeviceInterface(TK_DOOR_DL_CARD)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	*/
	//<! RAC2000P/G 下载时间段接口
	class ID_HNDR_RAC_DL_Timesect : public KSGDeviceInterface
	{
	public:
		ID_HNDR_RAC_DL_Timesect():KSGDeviceInterface(TK_DOOR_DL_TIME_SECT)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//<! RAC2000P/G 下载时间周接口
	class ID_HNDR_RAC_DL_Week : public KSGDeviceInterface
	{
	public:
		ID_HNDR_RAC_DL_Week():KSGDeviceInterface(TK_DOOR_DL_WEEK)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//<! RAC2000P/G 下载节假日接口
	class ID_HNDR_RAC_DL_Holiday : public KSGDeviceInterface
	{
	public:
		ID_HNDR_RAC_DL_Holiday():KSGDeviceInterface(TK_DOOR_DL_HOLIDAY)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	//<! RAC2000P/G 采集事件
	class ID_HNDR_RAC2000_UL_Event : public KSGDeviceInterface
	{
	private:
		int upload_event_to_server(KSGDeviceNode *node,stPollList *poll_list
			,int record,int zipped);
	public:
		ID_HNDR_RAC2000_UL_Event():KSGDeviceInterface(TK_COLLSERIAL_TASK)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//<! RAC2000P/G 挂失
	class ID_HNDR_RAC2000_Loss_Card : public KSGDeviceInterface
	{
	public:
		ID_HNDR_RAC2000_Loss_Card():KSGDeviceInterface(TK_ADD_BLACKCARD)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//<! RAC2000P/G 挂失
	class ID_HNDR_RAC2000_Unloss_Card : public KSGDeviceInterface
	{
	public:
		ID_HNDR_RAC2000_Unloss_Card():KSGDeviceInterface(TK_DEL_BLACKCARD)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
};

#endif // _RAC2000DEVNODE_H_
