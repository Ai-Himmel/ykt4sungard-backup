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

//! 采集心跳任务
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

//! 采集流水任务
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

class KSGTaskDownloadBlackCard : public KSGScheduler
{
	DECLARE_FACTORY_CREATOR(KSGTaskDownloadBlackCard)
public:
	class DownloadBlackCardVisitor : public BaseVisitor,public DefaultDeviceVisitor
	{
	private:
		struct dev_blkcard_info_t
		{
			int last_cnt;
			int sleep_times;
		};
		typedef std::map<int,dev_blkcard_info_t> DEV_BLKCARD_MAP_TYPE;
		DEV_BLKCARD_MAP_TYPE _dev_blkcard;
	public:
		virtual void Visit(KSGDeviceNode& node);
	};
	KSGTaskDownloadBlackCard():KSGScheduler(KSG_SCHD_BLKCARD)
	{}
	virtual ~KSGTaskDownloadBlackCard()
	{}
	virtual void Run();
private:
	int _collect_count;
	DownloadBlackCardVisitor _visitor;
	inline void NewDLBlkCardTask(KSGDeviceNode* node)
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
