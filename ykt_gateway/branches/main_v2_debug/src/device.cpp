
#include "device.h"
#include "devnode/devnode.h"
#include "deviceinterface.h"
#include "ksgateway.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
// KSGDeviceURL
int KSGDeviceURL::ParseUrl(const std::string& url)
{
	// 分析
	std::string::size_type i,j;
	i = url.find("//");
	if(std::string::npos == i)
		return -1;
	std::string scheme = url.substr(0,i);
	std::string addr = url.substr(i+2);
	i = 0;
	j = scheme.find(':',i);
	if(std::string::npos == j)
		return -1;
	// 必须是dev:开始
	if(scheme.compare(0,j,"dev") != 0)
		return -1;
	i = ++j;
	j = scheme.find(':',i);
	if(std::string::npos == j)
		return -1;
	std::string conntype = scheme.substr(i,j - i);
	if("TCP" == conntype)
		_connType = dctTCP;
	else if("COM" == conntype)
		_connType = dctCOM;
	else if("MDM" == conntype)
		_connType = dctModem;
	else if("SUB" == conntype)
	{
		_connType = dctSubLevel;
	}
	else
		return -1;
	i = ++j;
	_manufactor = scheme.substr(i);
	if(_manufactor.length() == 0)
		return -1;
	
	i = addr.find_first_of('@');
	if(i == std::string::npos)
		return -1;
	_devCode = addr.substr(0,i);
	if(_connType == dctSubLevel)
		return 0;
	i++;
	j = addr.find(':',i);
	if(std::string::npos == j)
	{
		// 没有端口
		_conn = addr.substr(i);
		if(dctTCP == _connType)
			_port = si_default_tpc_port;
		else
			_port = si_default_com_port;
	}
	else
	{
		_conn = addr.substr(i,j-i);
		_port = atoi(addr.substr(j+1).c_str());
		if(_port == 0)
			return -1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// KSGDeviceNode
KSGDeviceNode::Device_Mutex_Type KSGDeviceNode::_mutex;

int KSGDeviceNode::ExecuteTask(Task* task)
{
	/*
	if(!CanExecTask())
	{
		return TASK_ERR_TIMEOUT;
	}
	*/
	if(!this->_devtype)
	{
		ACE_DEBUG((LM_INFO,"设备不能执行指令[%d][%d]",this->GetDevId()
			,task->GetTaskCode()));
		return -1;
	}
	if(!this->_devtype->AcceptTask(task))
	{
		if(_parent == this)
			return TASK_ERR_NOT_SUPPORT;
		if(_parent)
		{
			return _parent->ExecuteTask(task);
		}
		return TASK_ERR_NOT_SUPPORT;
	}
	return _devtype->ExecuteTask(this,task);
}

void KSGDeviceNode::SetParent(KSGDeviceNode* parent)
{
	if(_frozen)
		throw ConfigFrozenException();
	if(_parent)
	{
		_parent->RemoveChild(this);
	}
	if(parent)
	{
		_parent = parent;
		_devParentId = _parent->GetDevId();
		_parent->AddChild(this);
	}
	else
	{
		_parent = NULL;
		_devParentId = NullParentDevId;
	}
}

void KSGDeviceNode::RemoveChild(KSGDeviceNode* node)
{
	KSGDeviceNode ** q = &_firstChild;
	if(node->_parent != this)
		return;
	for(; (*q != NULL); q = &((*q)->_nextSibling))
	{
		if(*q == node)
		{
			*q = node->_nextSibling;
			node->_nextSibling = NULL;
			return;
		}
	}
}

bool KSGDeviceNode::Accept(BaseVisitor& guest)
{
	if(_devtype == NULL)
		return false;
	return _devtype->Accept(guest,this);
}


//////////////////////////////////////////////////////////////////////////
// KSGDevice
KSGDevice::KSGDevice(const NormalDeviceType& devtype)
//#ifdef WIN32
//:_devType(devtype),_handle_mutex(USYNC_PROCESS),_handle_cond(_handle_cond_mutex)
//#else
:_devType(devtype),_handle_cond(_handle_cond_mutex)
//#endif
{}
KSGDevice::~KSGDevice()
{
	close_all_handler();
}
int KSGDevice::ExecuteTask(DeviceNodeType* node,Task* task)
{
	// 检查是否支持指令
	bool free_conn = false;
	DI devintr = FindDevInterface(task->GetTaskCode());
	if(!devintr)
	{
		ACE_DEBUG((LM_ERROR,"设备不支持该指令..."));
		throw TaskNotSupportedException();
	}
	//
	int ret;
	ACE_HANDLE handler;
	ret = find_handler(node,&handler);
	if(ret)
	{
		//ACE_DEBUG((LM_ERROR,"连接指定设备失败!"));
		return TASK_ERR_CONNECT;
	}
	// 执行指令
	try
	{
		task->_handle = handler;
		ret = devintr->ExecuteTask(node,task);
	}
	catch(...)
	{
		// ignore
	}
	if(node->connect_module() == KSGDeviceNode::cm_short_conn)
	{
		free_conn = true;
	}
	else
	{
		// 如果指令执行不成功
		if(ret != TASK_SUCCESS)
		{
			if(ret == TASK_INVALID_CONN)
				free_conn = true;
			else
			{
				ACE_Time_Value tv(1);
				int res = ACE::handle_exception_ready(task->_handle,&tv);
				if(res >0)
				{
					// 如果发生异常，则重连
					free_conn = true;
				}
				else if(res == 0) // 超时
				{
					free_conn = true;
				}
				else // 返回错误
				{

				}
			}
		}
	}
	
	try
	{
		/*
		if(free_conn)
		{
			// 需要关闭连接， 目前发现 BF-430 必须等待 50ms 才能重新连接
			KSGThreadUtil::Sleep(100);
		}
		*/
		if(release_handler(node,&handler,free_conn))
		{
			ACE_DEBUG((LM_ERROR,"释放连接失败"));
		}
		/*
		else
		{
			// 如果关闭连接，需要等待 500
			if(free_conn)
				KSGThreadUtil::Sleep(500);
		}
		*/
	}
	catch (...)
	{
		ACE_DEBUG((LM_ERROR,"关闭连接异常!"));
	}
	return ret;
}
int KSGDevice::create_handler(KSGDeviceNode*node,ACE_HANDLE* handler)
{
	int ret;
	ret = make_handler(node,handler);
	if(ret == 0)
	{
		//ret = find_handler(node,&oldhandler);
		//if(ret == 0)
		//{
		//	close_handler(node,oldhandler);
		//}
		save_handler(node,*handler);
		return 0;
	}
	else if(ret > 0)
	{
		if(node->GetParent() && node->GetParent()->GetDevice())
			ret = node->GetParent()->GetDevice()->create_handler(node->GetParent(),handler);
		return ret;
	}
	else
	{
		return -1;
	}
}

int KSGDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	return 1;
}

int KSGDevice::find_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	// 申请资源锁
	int ret;
	int retries = 3;
	int need_wait;
	ACE_HANDLE new_handle = ACE_INVALID_HANDLE;
again:
	//ACE_DEBUG((LM_DEBUG,"申请连接资源"));
	{
		ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,mon,_handle_mutex,1);
		ret = -1;
		need_wait = 0;
		// 从连接表中查找
		DeviceHandleMap::iterator i = _handlers.find(node);
		if(i != _handlers.end())
		{
			// 如果有连接可用, 将连接从[连接表]中移到[已使用连接表]中
			*handler = i->second;
			_handlers.erase(i);
			_used_handlers.insert(DeviceHandleMap::value_type(node,*handler));
			//ACE_DEBUG((LM_DEBUG,"获取连接资源"));
			return 0;
		}
		else
		{
			i = _used_handlers.find(node);
			// 如果在[已使用连接表]中找到连接
			if(i != _used_handlers.end())
			{
				need_wait = 1;
			}
			//ACE_DEBUG((LM_ERROR,"无法找到 CCU 连接"));
		}
	}
	if(need_wait)
	{
		ACE_DEBUG((LM_TRACE,"等待连接资源..."));
		// 等待其它线程释放资源
		if(wait_for_handler(node,handler)==0)
		{
			ACE_DEBUG((LM_TRACE,"重新申请连接资源"));
			if(--retries > 0)
				goto again;
			return -1;
		}
		else
		{
			// 等待失败
			return 1;
		}
	}
	ret = make_handler(node,&new_handle);
	if(ret>0)
	{
		// 本设备节点不能创建连接,查找父设备
		//ACE_DEBUG((LM_DEBUG,"查找父设备连接"));
		if(node->GetParent() && node->GetParent()->GetDevice())
		{
			ret = node->GetParent()->GetDevice()->find_handler(node->GetParent(),handler);
		}
		else
			ret = -1;
	}
	else if(ret == 0)
	{
		// 创建新连接成功,重新获取连接
		ACE_DEBUG((LM_TRACE,"建立新连接..."));
		save_handler(node,new_handle);
		node->connect_once(1);
		goto again;
	}
	else
	{
		// 创建连接失败
		ACE_DEBUG((LM_ERROR,"无法连接到设备!!![%d]",node->GetDevId()));
		// 需要关闭连接， 目前发现 BF-430 必须等待 50ms 才能重新连接
		//KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_conn_interval);
		node->connect_once(0);
		ret = -1;
	}
	return ret;
}

int KSGDevice::wait_for_handler(KSGDeviceNode*node,ACE_HANDLE* handler)
{
	do 
	{
		//
		//_handle_cond_mutex.acquire();
		{
			ACE_DEBUG((LM_DEBUG,"等待设备连接句柄,dev[%d][%s]",node->GetDevId(),node->get_name().c_str()));
			ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_handle_cond_mutex,-1);
			ACE_Time_Value now(10);
			now += ACE_OS::gettimeofday();
			if(_handle_cond.wait(&now))
			{
				//_handle_cond_mutex.release();
				if(ACE_OS::last_error() == ETIME)
					continue;
				return -1;
			}
			else
			{
				//_handle_cond_mutex.release();
				return 0;
			}
		}
	} while(1);
	return -1;
}

int KSGDevice::release_handler(KSGDeviceNode* node,ACE_HANDLE* handler,bool bfree /*= false*/)
{
	int ret;
	int found = 0;

	//ACE_DEBUG((LM_DEBUG,"申请释放连接资源"));
	{
		ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,mon,_handle_mutex,-1);
		ret = -1;
		//ACE_DEBUG((LM_DEBUG,"释放连接资源"));
		DeviceHandleMap::iterator i = _used_handlers.find(node);
		if( i != _used_handlers.end())
		{
			found = 1;
			if(i->second == *handler)
			{
				// 将连接资源从[已使用连接表]中删除
				_used_handlers.erase(i);
				found = 2;
			}
		}
		else if( (i = _handlers.find(node)) != _handlers.end())
		{
			found = 1;
			if(i->second == *handler)
			{
				// 将连接资源从[可用连接表]中删除
				_handlers.erase(i);
				found = 2;
			}
		}
		if(found)
		{
			ret = 0;
			// 如果需要被释放, 或者 handler 不是已经打开的handler
			if(bfree || 1 == found)
			{
				ACE_DEBUG((LM_INFO,"关闭与设备的连接,dev[%d]",node->GetDevId()));
				// 关闭连接
				ret = close_handler(node,*handler);
				//if(bfree)
				//{
				// 需要关闭连接， 目前发现 BF-430 必须等待 50ms 才能重新连接
				//KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_conn_interval);
				//}
			}
			else
				_handlers.insert(DeviceHandleMap::value_type(node,*handler));
			// 通知其它等待的线程
			_handle_cond.signal();
		}
	}
	if(!found)
	{
		// 从父设备查找
		if(node->GetParent() && node->GetParent()->GetDevice())
		{
			return node->GetParent()->GetDevice()->release_handler(node->GetParent(),handler,bfree);
		}
		ACE_DEBUG((LM_TRACE,"释放的连接资源不正确"));
	}
	return ret;
}

int KSGDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ()
{
	return -1;
}

void KSGDevice::close_all_handler()
{
	DeviceHandleMap::iterator i ;
	for(i = _handlers.begin();i != _handlers.end();++i)
	{
		ACE_HANDLE handler = i->second;
		if(close_handler(NULL,handler))
		{
			ACE_DEBUG((LM_ERROR,"关闭handler失败"));
		}
	}
	_handlers.clear();
	for(i = _used_handlers.begin();i != _used_handlers.end();++i)
	{
		ACE_HANDLE handler = i->second;
		if(close_handler(NULL,handler))
		{
			ACE_DEBUG((LM_ERROR,"关闭handler失败"));
		}
	}
	_used_handlers.clear();
}

void KSGDevice::save_handler(KSGDeviceNode* node,ACE_HANDLE handler)
{
	{
		ACE_GUARD(ACE_Recursive_Thread_Mutex,mon,_handle_mutex);
		DeviceHandleMap::iterator i = _handlers.find(node);
		if(i != _handlers.end())
		{
			//close_handler(i->second);
			ACE_DEBUG((LM_NOTICE,"连接已经存在, 可以有未释放连接!!!"));
		}
		_handlers.insert(DeviceHandleMap::value_type(node,handler));
	}
	_handle_cond.signal();
}

bool KSGDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	return false;
}
//////////////////////////////////////////////////////////////////////////
// KSGDeviceManager
bool KSGDeviceManager::SortDeviceParentId(KSGDeviceNode* lhs,KSGDeviceNode* rhs)
{
	return (lhs->GetParentId() > rhs->GetParentId());
}

KSGDeviceManager::~KSGDeviceManager()
{
	Clear();
}
void KSGDeviceManager::Clear()
{
	DeviceList::iterator i;
	for (i = _devList.begin();i != _devList.end();++i)
	{
		KSGDeviceNode * node = *i;
		FreeDevice(node);
	}
	_devList.clear();
	_devices.clear();
}

void KSGDeviceManager::make_device_toplogic(KSGDeviceNode* node)
{
	int pnode_id = node->GetParentId();
	if(pnode_id == KSGDeviceNode::NullParentDevId)
		pnode_id = KSGDeviceNode::LoopDeviceId;

	KSGDeviceNode *pnode = FindDevice(pnode_id);
	if(!pnode)
	{
		ACE_DEBUG((LM_ERROR,"设备[%d][%s]无法找到上级节点",node->GetDevId(),node->get_name().c_str()));
	}
	else
	{

		node->SetParent(pnode);
	}
}

KSGDevice* KSGDeviceManager::FindDeviceType(const std::string& vendor,NormalDeviceType devtype)
{
	KSGDevice* dev = NULL;
	try
	{
		KSG_GET_DEVICE_OBJECT(vendor,devtype,dev);
	}
	catch (KSGException& ex )
	{
		// 
		KSG_DUMP_EXCEPTION(ex);
		ACE_DEBUG((LM_ERROR,"查找设备接口失败[%s][%s]",vendor.c_str(),devtype.c_str()));
	}
	return dev;
}
KSGDeviceNode* KSGDeviceManager::NewDevice(
	int did, 
	KSGDeviceNode *parent, 
	const std::string& vendor,
	const std::string& phyid,
	NormalDeviceType devtype)
{
	KSGDevice* dev = FindDeviceType(vendor,devtype);
	if(!dev)
	{
		throw DevTypeNotExists();
	}
	return NewDevice(did,parent,phyid,dev);	
}

KSGDeviceNode* KSGDeviceManager::NewDevice(
	int did,
	int parentId,
	const std::string& vendor,
	const std::string& phyid,
	NormalDeviceType devtype)
{
	KSGDeviceNode* ret = FindDevice(did);
	if(ret)
		throw DeviceIdAlreadyExists();
	KSGDevice* dev = FindDeviceType(vendor,devtype);
	ret = _pool.construct<int,int,KSGDevice*>(did,parentId,dev);
	ret->SetPhyId(phyid);
	SaveDevice(ret);
	return ret;
}

KSGDeviceNode* KSGDeviceManager::NewDevice(
	int did,
	KSGDeviceNode* parent,
	const std::string& phyid,
	KSGDevice* devtype)
{
	KSGDeviceNode* ret = FindDevice(did);
	if(ret)
		throw DeviceIdAlreadyExists();
	ret = _pool.construct(did,parent,devtype);
	ret->SetPhyId(phyid);
	SaveDevice(ret);
	return ret;
}

int KSGDeviceManager::SetupLoopDevice()
{
	int ret = -1;
	KSGDevice* dev = NULL;//= FindDeviceType(KSG_LOOP_DEV_TYPE);
	if(!dev)
	{
		// 从默认Loop设备中查找
		try
		{
			KSG_GET_DEVICE_OBJECT(KSG_LOOP_DEV,KSG_LOOP_DEV_TYPE,dev);
			if(!dev)
				return -1;
		}
		catch (KSGException& )
		{
			// 无法加载 loop 设备
			return -1;
		}
	}
	KSGDeviceNode* node = new KSGLoopDeviceNode(dev);
	SaveDevice(node);
	return 0;
}

int KSGDeviceManager::Sort()
{
	std::sort(_devList.begin(),_devList.end(),SortDeviceParentId);
	Traseval(boost::bind(&KSGDeviceManager::make_device_toplogic,this,_1));
	/*
	DeviceList::iterator i = _devList.begin();
	for(;i != _devList.end();++i)
	{
		KSGDeviceNode *node = *i;
		if(node)
		{
			if(node->owner_queue() == NULL && 
				(node->GetDevId() != KSGDeviceNode::LoopDeviceId
				&& node->GetParentId() != KSGDeviceNode::LoopDeviceId)
				)
			{
				ACE_DEBUG((LM_ERROR,"设备[%s][%s]未正确配置",node->GetPhyId().c_str()
					,node->get_name().c_str()));
				return -1;
			}
		}
		else
			return -1;
	}
	*/
	return 0;
}

