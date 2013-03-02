#ifndef _KSG_SCHDIMPL_H_
#define _KSG_SCHDIMPL_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "scheduler.h"
#include "ksgateway.h"
#include "visitor.h"
#include "device.h"


//! 获取指令调度线程
class KSGTaskReceiverScheduler :public KSGScheduler
{
	DECLARE_FACTORY_CREATOR(KSGTaskReceiverScheduler)
public:
	KSGTaskReceiverScheduler():KSGScheduler(KSG_SCHD_RECV_TASK)
	{
	}
	~KSGTaskReceiverScheduler(){}
	virtual void Run();
protected:
	virtual KSGScheduler& GetObserverable()
	{
		return *this;
	}
};

class KSGTaskCollHeartBeat : public KSGScheduler
{
	DECLARE_FACTORY_CREATOR(KSGTaskCollHeartBeat)
public:
	class CollHeartBeatVisitor :public BaseVisitor, public DefaultDeviceVisitor
	{
	public:
		virtual void Visit(KSGDeviceNode& node);
	};
private:
	CollHeartBeatVisitor _visitor;
	inline void NewHeartBeatTask(KSGDeviceNode* node)
	{
		_visitor.Visit(*node);
	}
public:
	KSGTaskCollHeartBeat():KSGScheduler(KSG_SCHD_COLL_HEARTBEAT){}
	virtual ~KSGTaskCollHeartBeat(){}
	virtual void Run();
protected:
	virtual KSGScheduler& GetObserverable()
	{
		return *this;
	}
};

class KSGTaskCollectSerial : public KSGScheduler
{
	DECLARE_FACTORY_CREATOR(KSGTaskCollectSerial)
public:
	class CollectSerialVisitor : public BaseVisitor,public DefaultDeviceVisitor
	{
	public:
		virtual void Visit(KSGDeviceNode& node);
	};
	KSGTaskCollectSerial():KSGScheduler(KSG_SCHD_COLL_SERIAL)
	{}
	virtual ~KSGTaskCollectSerial()
	{}

	virtual void Run();
private:
	CollectSerialVisitor _visitor;
	inline void NewCollSerialTask(KSGDeviceNode* node)
	{
		_visitor.Visit(*node);
	}
protected:
	virtual KSGScheduler& GetObserverable()
	{
		return *this;
	}

};
#endif // _KSG_SCHDIMPL_H_
