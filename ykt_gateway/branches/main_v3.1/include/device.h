#ifndef _DEVICE_H_
#define _DEVICE_H_
/*! @file
*	ģ����:		һ��ͨͨ��ǰ�û�
*	�ļ���: 	device.h
*	�ļ�ʵ�ֹ���: �豸�ӿڶ���	
*	����:		����
*	�汾:		V1.0
*	��ע:	
*/
#ifdef _MSC_VER
#pragma once
#endif

#include "ksglobal.h"
#include "taskdef.h"
#include "ksgexception.h"
#include "visitor.h"
#include "factory.h"
#include <boost/function.hpp>
#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <algorithm>
#include <boost/throw_exception.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/shared_ptr.hpp>
#include <ace/Asynch_IO.h>
#include <ace/Thread_Mutex.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/Mutex.h>
#include <ace/Condition_Thread_Mutex.h>
#include <ace/Condition_T.h>
#include <ace/Atomic_Op_T.h>
#include <ace/Null_Mutex.h>

#define _LOOP_DEVICE_NODE_ID ~0UL

typedef std::string NormalDeviceType;
//! �豸��ַ
/*!
	�豸��ַ��Ϣ��ʽ����
		dev:(TCP|COM):�������//��ַ�������г������Ϊ 999 �� hd, ��ַ����ʾ����:
			�����豸:  �豸��ַ���@COM:���ں�, �� 001A@COM:1 ,��ʾ�ڴ���1 �ϵ��豸��
			�豸���Ϊ001A
		TCP/IP�豸: �豸��ַ���@IP:�˿�, �� 1034@192.168.0.1:10001 ��ʾ��IPΪ192.168.0.1��
		����ϣ��˿�Ϊ10001,�豸���Ϊ 1034
			һ�����������ӣ�999 �豸 dev:TCP:999//1@10.49.188.40:10001
			����豸��dev:COM:hd//1001@COM:1, dev:TCP:hd//1002@10.49.0.20:5000
*/
class KSGDeviceURL
{
public:
	typedef enum{
		dctCOM = 1,		// COM ����
		dctModem = 2, //moderm
		dctTCP = 3,	// TCP/IP ����
		dctSubLevel = 9 // �¼��豸
	}DevConnType;
private:
	std::string _url;
	std::string _devCode;
	std::string _conn;
	std::string _manufactor;
	DevConnType _connType;
	int _port;
public:
	static const int si_default_tpc_port = 10001;
	static const int si_default_com_port = 1;
	KSGDeviceURL()
	{}
	~KSGDeviceURL()
	{}
	//! ������ַ��Դ��
	/*
	\param url ��ַ��Դ��
	\return ��ַ��ȷ����0,ʧ�ܷ��� -1
	*/
	int ParseUrl(const std::string& url);
	inline std::string GetDevCode() const
	{
		return _devCode;
	}
	inline std::string GetConnect() const
	{
		return _conn;
	}
	inline int GetPort() const
	{
		return _port;
	}
	inline DevConnType GetConnType()const
	{
		return _connType;
	}
	inline std::string GetManufactor() const
	{
		return _manufactor;
	}

};

class KSGDevice;
class KSG_Task_Queue;
typedef Visitable<bool> DeviceNodeVisitable;
//! �豸�ڵ㣬���ڱ�ʾ��ʵϵͳ�е��豸
/*!
�豸�ڵ��ʾһ��������豸�����POS-A , POS-B ... ÿ���豸�ڵ���һ��Ψһ�ĵ�ַ��Ϣ��
�豸�ڵ��Ӧһ����KSGDevice, KSGDevice ��ʾϵͳ�е��豸���ͣ��Լ��豸Ӳ���ӿ�
*/
class KSGDeviceNode : public DeviceNodeVisitable
{
public:
	
	//! �豸����״̬��־
	enum {
		dsOffline = 1,	// �ѻ�
		dsOnline = 2,	// ����
		dsError = 4,	// ������
		dsHasRecord = 8, // �м�¼
		dsMemFull = 16, // �豸��¼��
	};
	typedef unsigned long DeviceState;

	typedef enum {
		cm_long_conn = 0,
		cm_short_conn = 1
	}Connect_Module;
	typedef enum {
		ct_mafiar_one = 0, //��Ƶ��
		ct_wiegand,
	}Card_Type;

	typedef KSGTask<KSGDeviceNode> Task;

	typedef ACE_Null_Mutex Device_Mutex_Type;
private:
	typedef KSGDeviceNode DeviceNodeType;
	typedef KSGDevice DeviceType;
	//typedef ACE_Atomic_Op_Ex<ACE_SYNCH_MUTEX,unsigned int> Times_Atomic_Op;
	typedef ACE_Atomic_Op_Ex<Device_Mutex_Type,unsigned int> Times_Atomic_Op;
	typedef std::map<std::string,std::string> Dev_Param_Value_Map;
	
	//<! �豸 ID ��
	int _devId;
	//<! �豸����ID��
	std::string _devphyid;
	//<! �豸����
	std::string _name;
	//<! �豸��������
	NormalDeviceType _vendor;
	//<! �豸����,һ��Ϊϵͳ��Ψһ�ĺ�
	int _termId;
	//<! ���豸,���û��Ϊ NULL
	int _devParentId;
	DeviceNodeType* _parent;
	//<! �豸����
	DeviceType* _devtype;
	//<! �豸��ַ��Ϣ
	KSGDeviceURL _url;
	//<! �豸����״̬
	DeviceState _state;
	//<! ��һ����������ʱ��
	long _lastHeartbeatTime;
	//<! �豸�������ö����־
	bool _frozen;
	//<! �豸�˿�����
	int _port_count;
	KSGDeviceNode* _firstChild;
	KSGDeviceNode* _nextSibling;
	//ACE_SYNCH_MUTEX _mutex;
	static Device_Mutex_Type _mutex;
	//<! �豸����
	Dev_Param_Value_Map _param_map;

	//<! ���Ӵ���
	Times_Atomic_Op _connect_times;
	//<! ʧ�����Ӵ���
	Times_Atomic_Op _err_connect_times;
	//<! ��һ������ʧ��ʱ��
	ACE_Atomic_Op_Ex<Device_Mutex_Type,ACE_Time_Value> _last_err_time;
	//<! ���һ�θ���״̬ʱ��
	ACE_Time_Value _last_update_time;
	//<! ��������
	Connect_Module _conn_module;
	//<! ʹ�ÿ�����
	Card_Type _card_type;
	//<! ������ TaskQueue
	KSG_Task_Queue *_owner_queue;
	void RemoveChild(KSGDeviceNode* node);

	friend class KSGDeviceManager;
	
	inline void SetPhyId(const std::string& phyid)
	{
		_devphyid = phyid;
	}

public:
	static const int NullParentDevId = 1;
	static const int LoopDeviceId = _LOOP_DEVICE_NODE_ID;
	//! constructor
	KSGDeviceNode(int did,DeviceNodeType* parent
				  ,DeviceType* devtype)
		:_devId(did),_parent(parent),_devtype(devtype),_frozen(false)
		 ,_state(dsOffline),_firstChild(NULL),_nextSibling(NULL),_termId(-1),
		 _owner_queue(NULL),_connect_times(_mutex,0),_err_connect_times(_mutex,0),
		 _last_err_time(_mutex,ACE_Time_Value::zero),_conn_module(cm_short_conn),
		 _last_update_time(ACE_Time_Value::zero)
	{
		assert(_devId > 0);
		assert(_devtype != NULL);
		if(_parent)
		{
			_devParentId = _parent->GetDevId();
			_parent->AddChild(this);
		}
	}
	KSGDeviceNode(int did,int parentId,DeviceType* devtype)
		:_devId(did),_devParentId(parentId),_parent(NULL),_devtype(devtype)
		,_frozen(false),_firstChild(NULL),_nextSibling(NULL),_termId(-1)
		,_connect_times(_mutex,0),_err_connect_times(_mutex,0),_owner_queue(NULL)
		,_last_err_time(_mutex,ACE_Time_Value::zero),_conn_module(cm_short_conn),
		 _last_update_time(ACE_Time_Value::zero)
	{
		// 
	}
	//! destructor
	virtual ~KSGDeviceNode()
	{}
	bool operator==(const KSGDeviceNode& rhs)
	{
		return _devId == rhs._devId;
	}
	KSGDeviceNode& operator=(const KSGDeviceNode& rhs)
	{
		_devId = rhs._devId;
		_parent = rhs._parent;
		_devtype = rhs._devtype;
		_frozen = rhs._frozen;
		_state = rhs._state;
	}
	//! ��ȡ�豸ID��
	/*!
	\return �豸 ID ��
	*/
	inline int GetDevId() const {return _devId;}

	inline int GetParentId() const {return _devParentId; }

	void SetParent(KSGDeviceNode* parent);

	inline void SetState(DeviceState s)
	{
		_state = s;
	}
	inline void SetStateBit(DeviceState s)
	{
		_state |= s;
	}
	inline DeviceState ClearStateBit(DeviceState s)
	{
		_state &= ~s;
		return _state;
	}
	inline void ClearState()
	{
		_state = 0;
	}
	inline DeviceState GetState() const
	{
		return _state;
	}
	//! �����豸��ַ
	/*
	\brief �����ַ�ַ�������ȷ,�׳� DeviceAddrUrlException �쳣
	\param url �豸��ַ�ַ���
	\throw DeviceAddrUrlException ��ַ�ַ�������ȷ
	\throw ConfigFrozenException �豸�����Ѿ�����
	*/
	inline void SetAddrUrl(const std::string & url)
	{
		if(_frozen)
			throw ConfigFrozenException();
		if(url.empty())
			return;
		if(_url.ParseUrl(url))
		{
			throw DeviceAddrUrlException();
		}
	}
	//! �����豸��������
	inline void Frozen()
	{
		_frozen = true;
	}
	//! ִ��ָ��
	/*!
	1. ����Լ��ܷ�ִ�����ִ�У�������Ծ�ִ���豸�ӿڵ�Ӳ���ӿڷ�����ִ��
	2. �������ִ�У�����Ƿ��и��豸�����û�и��豸������ʧ�� TASK_ERR_NOT_SUPPORT
	3. �и��豸�������豸ִ�к�ķ�����
	\param task ָ��
	\return ����ָ��ִ�н�����ɹ�����TASK_SUCCESS, 
	ʧ�ܷ��ش����룬��֧��ָ��� TASK_ERR_NOT_SUPPORT
	*/
	virtual int ExecuteTask(Task* task);
	//! �ж��豸��ǰ״̬���Ƿ����ִ��ָ��, Ĭ���豸ֻ�������ſ���ִ��
	/*
	\return true ��ǰ����ִ�У�false ����ִ��
	*/
	virtual inline bool CanExecTask() const
	{
		return (_state == dsOnline);
	}
	inline const KSGDeviceURL& GetDevAddr() const
	{
		return _url;
	}
	inline DeviceType* GetDevice() const
	{
		return _devtype;
	}
	inline NormalDeviceType GetDeviceType() const;
	inline KSGDeviceURL::DevConnType GetConnType() const
	{
		return _url.GetConnType();
	}
	inline void AddChild(KSGDeviceNode* child)
	{
		if(_firstChild)
		{
			child->_nextSibling = _firstChild;
		}
		_firstChild = child;
	}
	inline KSGDeviceNode* GetNextSibling() const
	{
		return _nextSibling;
	}
	inline KSGDeviceNode* GetFirstChild() const
	{
		return _firstChild;
	}
	inline KSGDeviceNode* GetParent() const
	{
		return _parent;
	}

	inline std::string GetPhyId() const
	{
		return _devphyid;
	}
	inline void SetTermId(int tid)
	{
		_termId = tid;
	}
	inline int GetTermId() const
	{
		return _termId;
	}

	inline void set_name(const std::string& name)
	{
		_name = name;
	}
	inline std::string get_name() const
	{
		return _name;
	}

	inline int get_port_count() const
	{
		return _port_count;
	}
	inline void set_port_count(int count)
	{
		_port_count = count;
	}

	inline void set_vendor(const NormalDeviceType& vendor)
	{
		_vendor = vendor;
	}

	inline NormalDeviceType get_vendor() const
	{
		return _vendor;
	}
	
	bool Accept(BaseVisitor& guest);

	KSG_Task_Queue *owner_queue(KSG_Task_Queue *q = NULL)
	{
		if(q)
		{
			_owner_queue = q;
		}
		return _owner_queue;
	}
	inline ACE_Time_Value last_err_time() const
	{
		return _last_err_time.value();
	}
	inline void connect_once(int success)
	{
		_connect_times++;
		if(!success)
		{
			_err_connect_times++;
			_last_err_time = ACE_OS::gettimeofday();
		}
	}
	inline unsigned int connect_times()const
	{
		return _connect_times.value();
	}
	inline unsigned int err_connect_times() const
	{
		return _err_connect_times.value();
	}
	inline Connect_Module connect_module() const
	{
		return _conn_module;
	}
	inline void connect_module(Connect_Module md)
	{
		_conn_module = md;
	}
	inline ACE_Time_Value get_update_time() const
	{
		return _last_update_time;
	}
	inline void update_time()
	{
		_last_update_time = ACE_OS::gettimeofday();
	}
	inline Card_Type card_type() const
	{
		return _card_type;
	}
	inline void card_type(Card_Type ct)
	{
		_card_type = ct;
	}
	inline void set_param(const std::string &n,const std::string &v)
	{
		Dev_Param_Value_Map::iterator i;
		i = _param_map.find(n);
		if(i != _param_map.end())
		{
			_param_map.erase(i);
		}
		_param_map.insert(Dev_Param_Value_Map::value_type(n,v));
	}
	inline int get_param(const std::string&n,std::string &v) const
	{
		Dev_Param_Value_Map::const_iterator i;
		i = _param_map.find(n);
		if(i == _param_map.end())
			return -1;
		v = i->second;
		return 0;
	}
	inline void clear_param(const std::string &n)
	{
		if(n.empty())
			_param_map.clear();
		else
		{
			_param_map.erase(n);
		}
	}

};

typedef Visitor<KSGDeviceNode,void> DefaultDeviceVisitor;
//! �豸
class KSGDeviceInterface
{
private:
	int _taskcode;
protected:
	typedef KSGDeviceNode::Task Task;
public:
	int GetTaskCode()const 
	{
		return _taskcode;
	}
	KSGDeviceInterface(int taskCode):_taskcode(taskCode)
	{}
	virtual ~KSGDeviceInterface()
	{}
	//! ִ��ָ��
	/*
	 \param node ִ��ָ����豸�ڵ�
	 \param task ָ�����ָ��
	 \return ���� 0 ��ʾִ�гɹ�, ִ��ʧ�ܷ��ش�����
	 */
	virtual int ExecuteTask(KSGDeviceNode* node,Task* task) = 0;
};

// typedef enum {dtServer,dtPos,dtJSB,dtAddPos,dtMobile} NormalDeviceType;

class KSGDevice  //: public DeviceNodeVisitable
{
private:
	//typedef KSGDeviceInterface DI;
	typedef boost::shared_ptr<KSGDeviceInterface> DI;
	typedef std::map<int,DI> DevIntrList;
	typedef KSGDeviceNode DeviceNodeType;
	typedef KSGTask<DeviceNodeType> Task;

	DevIntrList _devInterfaces;
	NormalDeviceType _devType;
	//! ���Ӿ�� hash ������
	typedef std::map<KSGDeviceNode*,ACE_HANDLE> DeviceHandleMap;
	//! ���Ӿ��
	DeviceHandleMap _handlers;
	//! ����ʹ�õ����Ӿ��
	DeviceHandleMap _used_handlers;
	ACE_Recursive_Thread_Mutex _handle_mutex;
	ACE_Thread_Mutex _handle_cond_mutex;
	ACE_Condition<ACE_Thread_Mutex> _handle_cond;
protected:
	void save_handler(KSGDeviceNode* node,ACE_HANDLE handler);
	virtual DI FindDevInterface(int task)
	{
		DevIntrList::iterator i = _devInterfaces.find(task);
		if(_devInterfaces.end() == i)
		{
			return DI();
		}
		return i->second;
	}
	void close_all_handler();
	//! ����һ���µ�����
	/*
	 \brief ����һ���µ�����
	 \param node Ҫ���ӵ��豸�ڵ�
	 \param handler [out]���Ӿ��
	 \return 0 �ɹ� ; -1 ��ʾ����ʧ��; 1 ��ʾ���ڵ㴴��
	 */
	int create_handler(KSGDeviceNode*node,ACE_HANDLE* handler);
	//! �ȴ����ӳɹ�
	/*
	 \brief �ȴ����ӱ��ͷ�
	 \param node �豸�ڵ�
	 \param handler [out] ���Ӿ��
	 \return 0 ��ʾ
	 */
	int wait_for_handler(KSGDeviceNode*node,ACE_HANDLE* handler);
	//! ����һ���豸�ڵ������Handler
	/*
	\param node ������豸����handler
	\param handler �������handler
	\return ����0��ʾ�����ɹ�, > 0 ��ʾ������ , <0 ��ʾ����ʧ��
	*/
	virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	//! �ر�һ�� handler
	/*
	\brief �ر�����
	\param node �豸�ڵ�
	\param handler ���� Handler
	\return 0 ��ʾ�رճɹ�, -1 ��ʾ�ر�ʧ��, 1 ��ʾ��֧�ֵ���
	*/
	virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw();
public:
	KSGDevice(const NormalDeviceType& devtype);
	virtual ~KSGDevice();
	NormalDeviceType GetDeviceType() const
	{
		return _devType;
	}
	bool AcceptTask(const Task* task)
	{
		DI devintr = FindDevInterface(task->GetTaskCode());
		return (devintr != NULL);
	}
	//! ִ��ָ��
	/*
	 \param node ִ��ָ����豸�ڵ�
	 \param task ָ�����
	 */
	int ExecuteTask(DeviceNodeType* node,Task* task);
	
	void AddInterface(KSGDeviceInterface *intr)
	{
		if(_devInterfaces.find(intr->GetTaskCode()) == _devInterfaces.end())
		{
			_devInterfaces[intr->GetTaskCode()] = DI(intr);
		}
		else
		{
			throw DevIntrDuplication();
		}
	}
	//! ����һ�� handler
	/*
	 \brief ����ָ���豸������
	 \param node �豸�ڵ�
	 \param handler [out]���Ӿ��
	 \return 0 ��ʾ��ȡ������, 1 ��ʾ��������ʹ�����޷���ȡ,-1 ��ʾ������
	 */
	virtual int find_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	//! �ͷ�����
	/*
	 \brief �ͷ�һ������ handler
	 \param node �豸�ڵ�
	 \param handler ���ӵ� handler
	 \param bfree �Ƿ�ͬʱ�ر�����
	 \return 0 ��ʾ�ͷųɹ�, -1 ��ʾ�ͷ�ʧ��
	 */
	virtual int release_handler(KSGDeviceNode* node,ACE_HANDLE* handler,bool bfree = false);
	
	virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
};

class KSGateway;

//! �豸�ڵ������
class KSGDeviceManager
{
public:
	//<! �豸�ڵ������
	typedef std::map<int,KSGDeviceNode*> DeviceMap;
	typedef std::vector<KSGDeviceNode*> DeviceList;
	typedef std::map<std::string,KSGDeviceNode*> DevPhyAddrMap;
private:
	//<! ���������
	typedef boost::object_pool<KSGDeviceNode> DeviceNodePoolType;
	//<! �豸�ڵ��б�
	DeviceMap _devices;
	DevPhyAddrMap _devPhyAddrs;
	DeviceList _devList;
	//<! �����
	DeviceNodePoolType _pool;
	KSGateway* _gateway;
	inline void SaveDevice(KSGDeviceNode* dev)
	{
		_devices.insert(DeviceMap::value_type(dev->GetDevId(),dev));
		_devPhyAddrs.insert(DevPhyAddrMap::value_type(dev->GetPhyId(),dev));
		_devList.push_back(dev);
	}
	void make_device_toplogic(KSGDeviceNode* dev);
public:
	//! constructor
	/*
	\param gateway KSǰ�û�
	*/
	KSGDeviceManager(KSGateway* gateway):_gateway(gateway)
	{}
	//! destructor
	~KSGDeviceManager();
	//! ��ʼ�� loop �豸
	int SetupLoopDevice();
	//! �������豸
	/*
	\param did �豸 ID ��
	\param parent ���豸�ڵ�ָ��
	\param devtype �豸����
	\throw DeviceIdAlreadyExists 
	*/
	KSGDeviceNode* NewDevice(
		int did,
		KSGDeviceNode* parent,
		const std::string& vendor,
		const std::string& phyid,
		NormalDeviceType devtype);
	//! �������豸
	/*
	\param did �豸ID��
	\param devtype �豸����
	\throw DeviceIdAlreadyExists 
	*/
	KSGDeviceNode* NewDevice(
		int did,
		int parentId,
		const std::string& vendor,
		const std::string& phyid,
		NormalDeviceType devtype);
	//! �������豸
	/*
	\param did �豸ID��
	\param parent ���豸�ڵ�ָ��
	\param devtype �豸���Ͷ���ָ��
	\throw DeviceIdAlreadyExists ��IDΪdid���豸�Ѿ����ڣ��׳��쳣
	*/
	KSGDeviceNode* NewDevice(
		int did,
		KSGDeviceNode* parent,
		const std::string& phyid,
		KSGDevice* devtype);
	//! �����豸ID�����豸�ڵ�
	/*
	\param did �豸ID��
	\return �����豸�ڵ��ָ�룬���û���ҵ����� NULL
	*/
	inline KSGDeviceNode* FindDevice(int did)
	{
		DeviceMap::const_iterator i = _devices.find(did);
		return (i != _devices.end()) ? i->second : NULL;
	}
	//! �����豸����ID�����豸�ڵ���Ϣ
	/*
	 \param phyid �豸����ID
	 \return �����豸�ڵ��ָ��,���û���ҵ����� NULL
	 */
	inline KSGDeviceNode* FindDevice(const std::string& phyid)
	{
		DevPhyAddrMap::const_iterator i = _devPhyAddrs.find(phyid);
		return (i != _devPhyAddrs.end()) ? i->second : NULL;
	}
	//! �ͷ��豸�ڵ�
	/*
	 \param node Ҫ�ͷŵ��豸�ڵ�
	 */
	inline void FreeDevice(KSGDeviceNode* node)
	{
		if(_pool.is_from(node))
		{
			_pool.free(node);
		}
		else
		{
			delete node;
		}
	}
	inline DeviceList* GetDevices() { return &_devList; }
	static bool SortDeviceParentId(KSGDeviceNode* lhs,KSGDeviceNode* rhs);
	KSGDevice* FindDeviceType(const std::string& vendor,NormalDeviceType devtype);
	inline size_t GetDeviceCount() const { return _devList.size(); }
	int Sort();
	void Clear();
	inline void Traseval(boost::function1<void,KSGDeviceNode*> func)
	{
		std::for_each(_devList.begin(),_devList.end(),func);
	}
};

typedef AbstractObject<int,KSGDeviceInterface> AbstractDevInterObject;

class KSGDeviceInterfaceLoader : public AbstractDevInterObject
{
protected:
	AbstractDevInterObject _interfaceObjects;
public:
	KSGDeviceInterfaceLoader(){}
	virtual ~KSGDeviceInterfaceLoader(){}
	virtual int LoadInterface(KSGDeviceManager* manager) = 0;
};

//! �豸���ؽӿڹ���
class KSGDeviceLoader
{
public:
	KSGDeviceLoader()
	{}
	virtual ~KSGDeviceLoader()
	{}
	//! ��ʼ������ʱ����,������ʵ��
	virtual int LoadDevice(KSGDeviceManager* manager) = 0;
	//! ���������豸��صĶ���ʼ�����(�����豸�ӿڳ�ʼ��),ϵͳ���øú���
	//  ������Ĺ���. �ýӿ�Ҳ����������ʵ��
	virtual int Finish(KSGDeviceManager* manager) = 0;
protected:
};


//////////////////////////////////////////////////////////////////////////
// 
inline NormalDeviceType KSGDeviceNode::GetDeviceType() const
{
	if(_devtype)
		return _devtype->GetDeviceType();
	return KSG_NULL_DEV_TYPE;
}

#endif	// _DEVICE_H_

