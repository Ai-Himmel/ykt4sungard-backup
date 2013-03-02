#ifndef _KSG_EXECIMPL_H_
#define _KSG_EXECIMPL_H_

#include "executor.h"
#include "deviceinterface.h"

class AddBlackCardExec : public KSGTaskExecutor
{
public:
	DECLARE_FACTORY_CREATOR(AddBlackCardExec)

	AddBlackCardExec()
	{}
	virtual int ExecuteTask(CDRTPHelper* drtp,TaskPointerType task);
};

class DoorDLTimesectExec : public KSGTaskExecutor
{
public:
	DECLARE_FACTORY_CREATOR(DoorDLTimesectExec)
	DoorDLTimesectExec()
	{}
	virtual int ExecuteTask(CDRTPHelper* drtp,TaskPointerType task);
};

class DoorDLWeekExec : public KSGTaskExecutor
{
public:
	DECLARE_FACTORY_CREATOR(DoorDLWeekExec)
	DoorDLWeekExec()
	{}
	virtual int ExecuteTask(CDRTPHelper* drtp,TaskPointerType task);
};

class DoorDLHolidayExec : public KSGTaskExecutor
{
public:
	DECLARE_FACTORY_CREATOR(DoorDLHolidayExec)
	DoorDLHolidayExec()
	{}
	virtual int ExecuteTask(CDRTPHelper* drtp,TaskPointerType task);
};

class DoorDLCardExec : public KSGTaskExecutor
{
public:
	DECLARE_FACTORY_CREATOR(DoorDLCardExec)
	DoorDLCardExec()
	{}
	virtual int ExecuteTask(CDRTPHelper* drtp,TaskPointerType task);
};

class TimerDLULExec : public KSGTaskExecutor
{
public:
	DECLARE_FACTORY_CREATOR(TimerDLULExec)
	TimerDLULExec()
	{}
	virtual int ExecuteTask(CDRTPHelper* drtp,TaskPointerType task);
};
#endif // _KSG_EXECIMPL_H_

