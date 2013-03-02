#ifndef _DEVICE_H_
#define _DEVICE_H_
/*! @file
*	模块名:		一卡通通用前置机
*	文件名: 	device.h
*	文件实现功能: 设备接口定义	
*	作者:		汤成
*	版本:		V1.0
*	备注:	
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
//! 设备地址
/*!
	设备地址信息格式如下
		dev:(TCP|COM):厂商类别//地址串，其中厂商类别为 999 或 hd, 地址串表示如下:
			串口设备:  设备地址编号@COM:串口号, 如 001A@COM:1 ,表示在串口1 上的设备，
			设备编号为001A
		TCP/IP设备: 设备地址编号@IP:端口, 如 1034@192.168.0.1:10001 表示在IP为192.168.0.1的
		结点上，端口为10001,设备编号为 1034
			一个完整的例子，999 设备 dev:TCP:999//1@10.49.188.40:10001
			汇多设备　dev:COM:hd//1001@COM:1, dev:TCP:hd//1002@10.49.0.20:5000
*/
class KSGDeviceURL
{
public:
	typedef enum{
		dctCOM = 1,		// COM 连接
		dctModem = 2, //moderm
		dctTCP = 3,	// TCP/IP 连接
		dctSubLevel = 9 // 下级设备
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
	//! 分析地址资源串
	/*
	\param url 地址资源串
	\return 地址正确返回0,失败返回 -1
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
//! 设备节点，用于表示真实系统中的设备
/*!
设备节点表示一个具体的设备，如果POS-A , POS-B ... 每个设备节点有一个唯一的地址信息；
设备节点对应一个　KSGDevice, KSGDevice 表示系统中的设备类型，以及设备硬件接口
*/
class KSGDeviceNode : public DeviceNodeVisitable
{
public:
	
	//! 设备运行状态标志
	enum {
		dsOffline = 1,	// 脱机
		dsOnline = 2,	// 联机
		dsError = 4,	// 不正常
		dsHasRecord = 8, // 有记录
		dsMemFull = 16, // 设备记录满
	};
	typedef unsigned long DeviceState;

	typedef enum {
		cm_long_conn = 0,
		cm_short_conn = 1
	}Connect_Module;
	typedef enum {
		ct_mafiar_one = 0, //射频卡
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
	
	//<! 设备 ID 号
	int _devId;
	//<! 设备物理ID号
	std::string _devphyid;
	//<! 设备名称
	std::string _name;
	//<! 设备厂商类型
	NormalDeviceType _vendor;
	//<! 设备机号,一般为系统中唯一的号
	int _termId;
	//<! 父设备,如果没有为 NULL
	int _devParentId;
	DeviceNodeType* _parent;
	//<! 设备类型
	DeviceType* _devtype;
	//<! 设备地址信息
	KSGDeviceURL _url;
	//<! 设备运行状态
	DeviceState _state;
	//<! 上一次心跳接收时间
	long _lastHeartbeatTime;
	//<! 设备参数配置冻结标志
	bool _frozen;
	//<! 设备端口总数
	int _port_count;
	KSGDeviceNode* _firstChild;
	KSGDeviceNode* _nextSibling;
	//ACE_SYNCH_MUTEX _mutex;
	static Device_Mutex_Type _mutex;
	//<! 设备参数
	Dev_Param_Value_Map _param_map;

	//<! 连接次数
	Times_Atomic_Op _connect_times;
	//<! 失败连接次数
	Times_Atomic_Op _err_connect_times;
	//<! 上一次连接失败时间
	ACE_Atomic_Op_Ex<Device_Mutex_Type,ACE_Time_Value> _last_err_time;
	//<! 最后一次更新状态时间
	ACE_Time_Value _last_update_time;
	//<! 连接属性
	Connect_Module _conn_module;
	//<! 使用卡类型
	Card_Type _card_type;
	//<! 所属的 TaskQueue
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
	//! 读取设备ID号
	/*!
	\return 设备 ID 号
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
	//! 设置设备地址
	/*
	\brief 如果地址字符串不正确,抛出 DeviceAddrUrlException 异常
	\param url 设备地址字符串
	\throw DeviceAddrUrlException 地址字符串不正确
	\throw ConfigFrozenException 设备配置已经冻结
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
	//! 冻结设备参数配置
	inline void Frozen()
	{
		_frozen = true;
	}
	//! 执行指令
	/*!
	1. 检查自己能否执行这个执行，如果可以就执行设备接口的硬件接口方法来执行
	2. 如果不能执行，检查是否有父设备，如果没有父设备，返回失败 TASK_ERR_NOT_SUPPORT
	3. 有父设备，返回设备执行后的返回码
	\param task 指令
	\return 返回指令执行结果，成功返回TASK_SUCCESS, 
	失败返回错误码，不支持指令返回 TASK_ERR_NOT_SUPPORT
	*/
	virtual int ExecuteTask(Task* task);
	//! 判断设备当前状态下是否可以执行指令, 默认设备只有联机才可以执行
	/*
	\return true 当前可以执行，false 不可执行
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
//! 设备
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
	//! 执行指令
	/*
	 \param node 执行指令的设备节点
	 \param task 指令对象指针
	 \return 返回 0 表示执行成功, 执行失败返回错误码
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
	//! 连接句柄 hash 表类型
	typedef std::map<KSGDeviceNode*,ACE_HANDLE> DeviceHandleMap;
	//! 连接句柄
	DeviceHandleMap _handlers;
	//! 正在使用的连接句柄
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
	//! 创建一个新的连接
	/*
	 \brief 创建一个新的连接
	 \param node 要连接的设备节点
	 \param handler [out]连接句柄
	 \return 0 成功 ; -1 表示创建失败; 1 表示父节点创建
	 */
	int create_handler(KSGDeviceNode*node,ACE_HANDLE* handler);
	//! 等待连接成功
	/*
	 \brief 等待连接被释放
	 \param node 设备节点
	 \param handler [out] 连接句柄
	 \return 0 表示
	 */
	int wait_for_handler(KSGDeviceNode*node,ACE_HANDLE* handler);
	//! 创建一个设备节点的连接Handler
	/*
	\param node 从这个设备创建handler
	\param handler 创建后的handler
	\return 返回0表示创建成功, > 0 表示不创建 , <0 表示创建失败
	*/
	virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	//! 关闭一个 handler
	/*
	\brief 关闭连接
	\param node 设备节点
	\param handler 连接 Handler
	\return 0 表示关闭成功, -1 表示关闭失败, 1 表示不支持调用
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
	//! 执行指令
	/*
	 \param node 执行指令的设备节点
	 \param task 指令对象
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
	//! 查找一个 handler
	/*
	 \brief 查找指令设备的连接
	 \param node 设备节点
	 \param handler [out]连接句柄
	 \return 0 表示获取到连接, 1 表示连接正在使用中无法获取,-1 表示无连接
	 */
	virtual int find_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	//! 释放连接
	/*
	 \brief 释放一个连接 handler
	 \param node 设备节点
	 \param handler 连接的 handler
	 \param bfree 是否同时关闭连接
	 \return 0 表示释放成功, -1 表示释放失败
	 */
	virtual int release_handler(KSGDeviceNode* node,ACE_HANDLE* handler,bool bfree = false);
	
	virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
};

class KSGateway;

//! 设备节点管理器
class KSGDeviceManager
{
public:
	//<! 设备节点表类型
	typedef std::map<int,KSGDeviceNode*> DeviceMap;
	typedef std::vector<KSGDeviceNode*> DeviceList;
	typedef std::map<std::string,KSGDeviceNode*> DevPhyAddrMap;
private:
	//<! 缓存池类型
	typedef boost::object_pool<KSGDeviceNode> DeviceNodePoolType;
	//<! 设备节点列表
	DeviceMap _devices;
	DevPhyAddrMap _devPhyAddrs;
	DeviceList _devList;
	//<! 缓存池
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
	\param gateway KS前置机
	*/
	KSGDeviceManager(KSGateway* gateway):_gateway(gateway)
	{}
	//! destructor
	~KSGDeviceManager();
	//! 初始化 loop 设备
	int SetupLoopDevice();
	//! 创建新设备
	/*
	\param did 设备 ID 号
	\param parent 父设备节点指针
	\param devtype 设备类型
	\throw DeviceIdAlreadyExists 
	*/
	KSGDeviceNode* NewDevice(
		int did,
		KSGDeviceNode* parent,
		const std::string& vendor,
		const std::string& phyid,
		NormalDeviceType devtype);
	//! 创建新设备
	/*
	\param did 设备ID号
	\param devtype 设备类型
	\throw DeviceIdAlreadyExists 
	*/
	KSGDeviceNode* NewDevice(
		int did,
		int parentId,
		const std::string& vendor,
		const std::string& phyid,
		NormalDeviceType devtype);
	//! 创建新设备
	/*
	\param did 设备ID号
	\param parent 父设备节点指针
	\param devtype 设备类型对象指针
	\throw DeviceIdAlreadyExists 当ID为did的设备已经存在，抛出异常
	*/
	KSGDeviceNode* NewDevice(
		int did,
		KSGDeviceNode* parent,
		const std::string& phyid,
		KSGDevice* devtype);
	//! 根据设备ID查找设备节点
	/*
	\param did 设备ID号
	\return 返回设备节点的指针，如果没有找到返回 NULL
	*/
	inline KSGDeviceNode* FindDevice(int did)
	{
		DeviceMap::const_iterator i = _devices.find(did);
		return (i != _devices.end()) ? i->second : NULL;
	}
	//! 根据设备物理ID查找设备节点信息
	/*
	 \param phyid 设备物理ID
	 \return 返回设备节点的指针,如果没有找到返回 NULL
	 */
	inline KSGDeviceNode* FindDevice(const std::string& phyid)
	{
		DevPhyAddrMap::const_iterator i = _devPhyAddrs.find(phyid);
		return (i != _devPhyAddrs.end()) ? i->second : NULL;
	}
	//! 释放设备节点
	/*
	 \param node 要释放的设备节点
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

//! 设备加载接口功能
class KSGDeviceLoader
{
public:
	KSGDeviceLoader()
	{}
	virtual ~KSGDeviceLoader()
	{}
	//! 初始化设置时调用,由子类实现
	virtual int LoadDevice(KSGDeviceManager* manager) = 0;
	//! 当所有与设备相关的都初始化完成(包括设备接口初始化),系统调用该函数
	//  完成最后的工作. 该接口也必须由子类实现
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

