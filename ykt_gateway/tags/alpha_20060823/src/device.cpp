#include "stdafx.h"
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
	return _devtype->Accept(guest);
}

//////////////////////////////////////////////////////////////////////////
// KSGDevice
int KSGDevice::ExecuteTask(DeviceNodeType* node,Task* task)
{
	// 检查是否支持指令
	DI * devintr = FindDevInterface(task->GetTaskCode());
	if(!devintr)
	{
		throw TaskNotSupportedException();
	}
	//
	int ret;
	ACE_HANDLE handler;
	// 先检查 handler 是否可用
	if(node->GetState() == KSGDeviceNode::dsOffline)
	{
		ret = create_handler(node,&handler);
	}
	else if((ret = find_handler(node,&handler)))
	{
		// 尝试连接
		ret = create_handler(node,&handler);
		if(ret)
		{
			// 连接失败
			node->SetState(KSGDeviceNode::dsOffline);
		}
	}
	if(ret)
	{
		return TASK_ERR_CONNECT;
	}
	
	// 执行指令
	ret = devintr->ExecuteTask(node,task);
	if(ret)
	{
		// 如果指令执行超时
		if(ret == TASK_ERR_TIMEOUT)
		{
			// 尝试重新连接
			if(create_handler(node,&handler))
			{
				// 重连失败
				node->SetState(KSGDeviceNode::dsError);
			}
		}
	}
	return ret;
}
int KSGDevice::create_handler(KSGDeviceNode*node,ACE_HANDLE* handler)
{
	ACE_HANDLE oldhandler;
	int ret;
	ret = make_handler(node,handler);
	if(ret == 0)
	{
		ret = find_handler(node,&oldhandler);
		if(ret == 0)
		{
			close_handler(node,oldhandler);
		}
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
	DeviceHandleMap::iterator i = _handlers.find(node);
	if(i != _handlers.end())
	{
		* handler = i->second;
		return 0;
	}
	if(node->GetParent() && node->GetParent()->GetDevice())
	{
		return node->GetParent()->GetDevice()->find_handler(node->GetParent(),handler);
	}
	return -1;
}

int KSGDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ()
{
	if(node)
	{
		DeviceHandleMap::iterator i = _handlers.find(node);
		if(i != _handlers.end())
		{
			_handlers.erase(i);
		}
	}
	return 0;
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
}

void KSGDevice::save_handler(KSGDeviceNode* node,ACE_HANDLE handler)
{
	DeviceHandleMap::iterator i = _handlers.find(node);
	if(i != _handlers.end())
	{
		//close_handler(i->second);
	}
	_handlers.insert(DeviceHandleMap::value_type(node,handler));
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
KSGDevice* KSGDeviceManager::FindDeviceType(NormalDeviceType devtype)
{
	KSGDevice* dev = NULL;
	try
	{
		KSG_GET_DEVICE_OBJECT(_gateway->GetConfig()->_devType,devtype,dev);
	}
	catch (KSGException& )
	{
		// 
	}
	return dev;
}
KSGDeviceNode* KSGDeviceManager::NewDevice(
	int did, 
	KSGDeviceNode *parent, 
	const std::string& phyid,
	NormalDeviceType devtype)
{
	KSGDevice* dev = FindDeviceType(devtype);
	if(!dev)
	{
		throw DevTypeNotExists();
	}
	return NewDevice(did,parent,phyid,dev);	
}

KSGDeviceNode* KSGDeviceManager::NewDevice(
	int did,
	int parentId,
	const std::string& phyid,
	NormalDeviceType devtype)
{
	KSGDeviceNode* ret = FindDevice(did);
	if(ret)
		throw DeviceIdAlreadyExists();
	KSGDevice* dev = FindDeviceType(devtype);
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
	KSGDevice* dev = FindDeviceType(KSG_LOOP_DEV_TYPE);
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

