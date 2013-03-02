#ifndef _KSG_TASK_DEF_H_
#define _KSG_TASK_DEF_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "ksglobal.h"
#include <cassert>
#include <string>
#include <sstream>
#include <map>
#include "ksgexception.h"
#include <ace/OS.h>
#include <ace/Log_Msg.h>


#ifdef _MSC_VER
#pragma warning (disable : 4290)
#endif

#ifdef WIN32
#define WIN32_CALL_CONVERTION _cdecl
#else
#define WIN32_CALL_CONVERTION 
#endif

// 状态队列调度
#define KSG_SCHEDULER_STATUS  "status"
// 轮询,FIFO 加权调度
#define KSG_SCHEDULER_ROBIN_WEIGHT "robinweight"

class KSGTaskParams
{
private:
	//<! 参数表类型
	typedef std::map<std::string,std::string> KeyValueMap;
	//<! 参数表
	KeyValueMap  _params;

	void PutParam(const std::string& key,const std::string& val);

	friend class KSG_Task_XML_Handler;
public:
	KSGTaskParams()
	{}
	~KSGTaskParams()
	{}
	int Parse(const std::string& str);
	std::string WIN32_CALL_CONVERTION GetParam(const std::string& key) const throw(KeyNotFoundException);
	int WIN32_CALL_CONVERTION GetParamIntVal(const std::string& key) const throw(KeyNotFoundException);
	double WIN32_CALL_CONVERTION GetParamDblVal(const std::string& key) const throw(KeyNotFoundException);
};

class KSGTaskResponse
{
private:
	typedef std::map<std::string,std::string> ValueType;
	ValueType _content;
public:
	KSGTaskResponse()
	{}
	~KSGTaskResponse()
	{}
	void AddField(const std::string& key,int value);
	void AddField(const std::string& key,unsigned int value);
	void AddField(const std::string& key,long value);
	void AddField(const std::string& key,unsigned long value);
	void AddField(const std::string& key,double value);
	void AddField(const std::string& key,const std::string& value);
	void AddField(const std::string& key,const char* value,size_t len);

	int GetFieldValue(const std::string& key,int& value)
	{
		std::string v;
		if(!GetFieldValue(key,v))
		{
			value = (int)ACE_OS::strtoul(v.c_str(),NULL,10);
			return 0;
		}
		return -1;
	}
	int GetFieldValue(const std::string& key,double& value)
	{
		std::string v;
		if(!GetFieldValue(key,v))
		{
			value = ACE_OS::strtod(v.c_str(),NULL);
			return 0;
		}
		return -1;
	}
	int GetFieldValue(const std::string& key,std::string& value)
	{
		value = "";
		ValueType::iterator i = _content.find(key);
		if(i != _content.end())
		{
			value = i->second;
			return 0;
		}
		return -1;
	}

};


//////////////////////////////////////////////////////////////
/// Task 类定义
//<! 指令优先级
typedef enum {  ptNormal = 0,ptReal,ptPreempt } TaskPriority;
//<! 指令方式
typedef enum { tt_poll = 0,tt_push = 1 } Task_Modal;
//! 指令任务
/*!
  \brief 指令对象，不支持序列化
  */
template<class DevNode>
class KSGTask
{
public:

private:
	typedef DevNode DeviceNodeType;
	//<! 任务 ID 号，由后台应用服务器生成
	int _taskId;
	//<! 任务号
	int _taskCode;
	//<! 任务指令内容
	std::string _content;
	//<! 保存指令执行的返回内容
	std::string _record;
	//<! 指令执行的返回码
	int _returncode;
	//<! 指令执行返回信息
	std::string _returnMsg;
	//<! 指令执行的设备对象
	DeviceNodeType* _device;
	//<! 指令优先级
	TaskPriority _priority;
	//<! 指令内容参数
	KSGTaskParams _params;
	bool _bParsed;
	//<! 指令是否需要应答
	bool _needResponse;
	//<! 指令执行次数
	int _exec_times;
	//<! 指令方式
	Task_Modal _task_modal;
	//<! 私有成员数据
	void * _private_data;

	KSGTaskResponse _response;
public:
	//<! 执行指令的连接句柄
	ACE_HANDLE _handle;
	//<! 获取指令 ID 号
	inline int GetTaskId()const
	{
		return _taskId;
	}
	//! 获取指令执行码
	inline int GetTaskCode() const
	{
		return _taskCode;
	}
	inline void SetDeviceNode(DeviceNodeType* dev)
	{
		_device = dev;
	}
	//! 获取指令对应的设备节点
	inline DeviceNodeType* GetDeviceNode()
	{
		return _device;
	}
	//! 获取指令内容
	const std::string& GetTaskContent() const
	{
		return _content;
	}
	//! constructor
	/*
	   \brief 当指令ID>0,时为后台的指令,当指令ID<=0时为前置机自动生成的指令
	   */
	KSGTask(int taskId,int code,const std::string& content)
		:_taskId(taskId),_taskCode(code),_content(content)
		,_record(""),_returncode(0),_device(NULL),_priority(ptNormal)
		,_bParsed(false),_needResponse(false),_exec_times(1),_task_modal(tt_poll)
		{}
	//! copy constructor
	KSGTask(const KSGTask& rhs)
	{
		_taskId = rhs._taskId;
		_taskCode = rhs._taskCode;
		_content = rhs._content;
		_record = rhs._record;
		_returncode = rhs._returncode;
		_device = rhs._device;
		_exec_times = rhs._exec_times;
		_priority = rhs._priority;
		_bParsed = rhs._bParsed;
		_needResponse = rhs._needResponse;
		_task_modal = rhs._task_modal;
	}
	//! 
	KSGTask()
		:_taskId(0),_taskCode(0),_content("")
		,_record(""),_returncode(0),_device(NULL),_priority(ptNormal)
		,_bParsed(false),_needResponse(false),_exec_times(0),_task_modal(tt_poll)
	{}
	~KSGTask()
	{
		ACE_DEBUG((LM_DEBUG,"释放指令id[%d]",_taskId));
	}
	//! operator = 
	KSGTask& operator=(const KSGTask& rhs)
	{
		_taskId = rhs._taskId;
		_taskCode = rhs._taskCode;
		_content = rhs._content;
		_record = rhs._record;
		_returncode = rhs._returncode;
		_device = rhs._device;
		_exec_times = rhs._exec_times;
		_priority = rhs._priority;
		_bParsed = rhs._bParsed;
		_needResponse = rhs._needResponse;
		_task_modal = rhs._task_modal;
		return *this;
	}
	//! operator == 
	bool operator==(const KSGTask& rhs)
	{
		return _taskId == rhs._taskId;
	}
	TaskPriority GetPriority() const
	{
		return _priority;
	}
	void SetPriority(TaskPriority proi)
	{
		_priority = proi;
	}
	const KSGTaskParams& GetParams()
	{
		if(!_bParsed)
		{
			std::string xml_content = "<?xml version='1.0'?><taskdef>" 
				+ _content + "</taskdef>";
			if(_content.length() > 0 && _params.Parse(xml_content) != 0)
			{
				throw KSGException();
			}
			_bParsed = true;
		}
		return _params;
	}
	void set_content(const std::string &content)
	{
		_content = content;
	}
	void SetNeedResponse(bool need = true)
	{
		_needResponse = need;
	}
	bool NeedResponse() const
	{
		return _needResponse;
	}
	KSGTaskResponse& GetResponse()
	{
		return _response;
	}
	int exec_times() const
	{
		return _exec_times;
	}
	void exec_times(int times)
	{
		_exec_times = times;
	}
	Task_Modal task_modal() const
	{
		return _task_modal;
	}
	void task_modal(Task_Modal modal)
	{
		_task_modal = modal;
	}

	void * private_data() const
	{
		return _private_data;
	}

	void private_data(void *arg)
	{
		_private_data = arg;
	}
};


ACE_Time_Value KSGGetTaskTimeoutIntval();

#endif // _KSG_TASK_DEF_H_

