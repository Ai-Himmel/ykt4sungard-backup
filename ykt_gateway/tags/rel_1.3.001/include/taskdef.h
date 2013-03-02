#ifndef _KSG_TASK_DEF_H_
#define _KSG_TASK_DEF_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <cassert>
#include <string>
#include <sstream>
#include <map>
#include "ksgexception.h"
#include <ace/OS.h>


#ifdef _MSC_VER
#pragma warning (disable : 4290)
#endif

#ifdef WIN32
#define WIN32_CALL_CONVERTION _cdecl
#else
#define WIN32_CALL_CONVERTION 
#endif

// ״̬���е���
#define KSG_SCHEDULER_STATUS  "status"
// ��ѯ,FIFO ��Ȩ����
#define KSG_SCHEDULER_ROBIN_WEIGHT "robinweight"

class KSGTaskParams
{
private:
	//<! ����������
	typedef std::map<std::string,std::string> KeyValueMap;
	//<! ������
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
/// Task �ඨ��
//<! ָ�����ȼ�
typedef enum {  ptNormal = 0,ptReal,ptPreempt } TaskPriority;
//! ָ������
/*!
  \brief ָ����󣬲�֧�����л�
  */
template<class DevNode>
class KSGTask
{
public:

private:
	typedef DevNode DeviceNodeType;
	//<! ���� ID �ţ��ɺ�̨Ӧ�÷���������
	int _taskId;
	//<! �����
	int _taskCode;
	//<! ����ָ������
	std::string _content;
	//<! ����ָ��ִ�еķ�������
	std::string _record;
	//<! ָ��ִ�еķ�����
	int _returncode;
	//<! ָ��ִ�з�����Ϣ
	std::string _returnMsg;
	//<! ָ��ִ�е��豸����
	DeviceNodeType* _device;
	//<! ָ�����ȼ�
	TaskPriority _priority;
	//<! ָ�����ݲ���
	KSGTaskParams _params;
	bool _bParsed;
	//<! ָ���Ƿ���ҪӦ��
	bool _needResponse;

	KSGTaskResponse _response;
public:
	//<! ִ��ָ������Ӿ��
	ACE_HANDLE _handle;
	//<! ��ȡָ�� ID ��
	inline int GetTaskId()const
	{
		return _taskId;
	}
	//! ��ȡָ��ִ����
	inline int GetTaskCode() const
	{
		return _taskCode;
	}
	inline void SetDeviceNode(DeviceNodeType* dev)
	{
		_device = dev;
	}
	//! ��ȡָ���Ӧ���豸�ڵ�
	inline DeviceNodeType* GetDeviceNode()
	{
		return _device;
	}
	//! ��ȡָ������
	const std::string& GetTaskContent() const
	{
		return _content;
	}
	//! constructor
	/*
	   \brief ��ָ��ID>0,ʱΪ��̨��ָ��,��ָ��ID<=0ʱΪǰ�û��Զ����ɵ�ָ��
	   */
	KSGTask(int taskId,int code,const std::string& content)
		:_taskId(taskId),_taskCode(code),_content(content)
		,_record(""),_returncode(0),_device(NULL),_priority(ptNormal)
		,_bParsed(false),_needResponse(false)
		{
			//assert(_taskId > 0);
		}
	//! copy constructor
	KSGTask(const KSGTask& rhs)
	{
		_taskCode = rhs._taskCode;
		_content = rhs._content;
		_record = rhs._record;
		_returncode = rhs._returncode;
		_device = rhs._device;
	}
	~KSGTask()
	{}
	//! operator = 
	KSGTask& operator=(const KSGTask& rhs)
	{
		_taskCode = rhs._taskCode;
		_content = rhs._content;
		_record = rhs._record;
		_returncode = rhs._returncode;
		_device = rhs._device;
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
};


ACE_Time_Value KSGGetTaskTimeoutIntval();

#endif // _KSG_TASK_DEF_H_

