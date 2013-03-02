#ifndef _HUNDURE_GCU3_H_
#define _HUNDURE_GCU3_H_

#ifdef _MSC_VER
# pragma once
#endif
#include "deviceinterface.h"
#include "hundure/hundure_def.h"
#include "taskcode.h"
#include "999dev/999devtype.h"
#include "proactor_def.h"
#include "hundure/GCU3.h"

#ifdef HAS_GCU_SUPPORT
DECLARE_NAMESPACE_BEGIN(HUNDURE)

class HNDR_GCU3 : public HNDR_Device_Base
{
	DECLARE_FACTORY_CREATOR(HNDR_GCU3)
protected:
	virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ();
public:
	HNDR_GCU3():HNDR_Device_Base(HUNDURE_GCU3)
	{}
};

/////////////////////////////////////////////////////////////////
// 设备指令接口

class ID_HNDR_GCU_DL_Timesect : public KSGDeviceInterface
{
private:
	std::string get_day_time(const KSGTaskParams &param,const char *param_name);
public:
	ID_HNDR_GCU_DL_Timesect():KSGDeviceInterface(TK_DOOR_DL_TIME_SECT)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};

class ID_HNDR_GCU_DL_Week : public KSGDeviceInterface
{
private:
	int get_week_day(const KSGTaskParams &param,const char *param_name);
public:
	ID_HNDR_GCU_DL_Week():KSGDeviceInterface(TK_DOOR_DL_WEEK)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};
class ID_HNDR_GCU_DL_Holiday : public KSGDeviceInterface
{
public:
	ID_HNDR_GCU_DL_Holiday():KSGDeviceInterface(TK_DOOR_DL_HOLIDAY)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};
class ID_HNDR_GCU_Batch_DL_Card : public KSGDeviceInterface
{
	int success_download(int custid,int device_id);
public:
	ID_HNDR_GCU_Batch_DL_Card():KSGDeviceInterface(TASK_CODE_BATCH_DOWNLOAD)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};

// 批量下载卡名单
class ID_HNDR_GCU_Batch_DL_Card2 : public KSGDeviceInterface
{
	int success_download(int list_id,int device_id);
public:
	ID_HNDR_GCU_Batch_DL_Card2():KSGDeviceInterface(TASK_CODE_BATCH_DOWNLOAD)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};
class ID_HNDR_GCU_DL_Card : public KSGDeviceInterface
{
public:
	ID_HNDR_GCU_DL_Card():KSGDeviceInterface(TK_DOOR_DL_CARD)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};
class ID_HNDR_GCU_UL_Event : public KSGDeviceInterface
{
private:
	int upload_event_to_server(KSGDeviceNode *node,stPollList_GCU *poll_list
		,int recv_record);
public:
	ID_HNDR_GCU_UL_Event():KSGDeviceInterface(TK_COLLSERIAL_TASK)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};

class ID_HNDR_GCU_UL_Timer : public KSGDeviceInterface
{
public:
	ID_HNDR_GCU_UL_Timer():KSGDeviceInterface(TK_UL_TIMER)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};

class ID_HNDR_GCU_DL_Timer : public KSGDeviceInterface
{
public:
	ID_HNDR_GCU_DL_Timer():KSGDeviceInterface(TK_DL_TIMER)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};

class ID_HNDR_GCU_Ctrl_Door : public KSGDeviceInterface
{
public:
	ID_HNDR_GCU_Ctrl_Door():KSGDeviceInterface(TK_CTRL_DOOR_OPEN)
	{}
	int ExecuteTask(KSGDeviceNode* node,Task* task);
};

DECLARE_NAMESPACE_END(HUNDURE);
#endif  // HAS_GCU_SUPPORT

#endif // _HUNDURE_GCU3_H_
