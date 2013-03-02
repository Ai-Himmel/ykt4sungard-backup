
#include "999dev/999devtype.h"
#include "ksglobal.h"
#include "deviceinterface.h"
#include "ksgexception.h"
#include "ksgateway.h"
#include <ace/Log_Msg.h>
#include <boost/thread/mutex.hpp>
#include <boost/throw_exception.hpp>
#include <boost/function.hpp>
#include <boost/functional.hpp>

using namespace DEV999;

#ifdef KSG_999_DEV_SUPPORT
KSG_REG_FACTORY_INTERFACE(KSG_999_DEV,KSG999DevInterfaceFactory);

KSG_REG_DEVICE_OBJECT(KSG_999_DEV,KSG_999_DEV_POS,Pos999Device);
KSG_REG_DEVICE_OBJECT(KSG_999_DEV,KSG_999_DEV_SERVER,Server999Device);
KSG_REG_DEVICE_OBJECT(KSG_999_DEV,KSG_999_DEV_JSB,JSB999Device);
KSG_REG_DEVICE_OBJECT(KSG_999_DEV,KSG_999_DEV_ADDPOS,AddPos999Device);
#endif // KSG_HD_DEV_SUPPORT
//////////////////////////////////////////////////////////////////////////
// KSG999DeviceLoader

int KSG999DeviceLoader::LoadDevice(KSGDeviceManager* manager)
{
	ACE_DEBUG((LM_DEBUG,"开始加载999设备..."));
	KSGDeviceManager::DeviceList * devs = manager->GetDevices();

	try
	{
		std::for_each(devs->begin(),devs->end(),
			boost::bind(&KSG999DeviceLoader::SetDeviceStruct,this,manager,_1));
		std::for_each(devs->begin(),devs->end(),
			boost::bind(&KSG999DeviceLoader::SetRunningQueue,this,_1));
	}
	catch (LoopDeviceNotExists& )
	{
		return -1;
	}
	return 0;
}

int KSG999DeviceLoader::Finish(KSGDeviceManager* manager)
{
	return 0;
}
void KSG999DeviceLoader::SetDeviceStruct(KSGDeviceManager* manager,KSGDeviceNode* node)
{
	int pid = node->GetParentId();
	KSGDeviceNode * pnode;
	if(KSGDeviceNode::NullParentDevId == pid)
	{
		// set for loop device
		pnode = manager->FindDevice(KSGDeviceNode::LoopDeviceId);
		if(!pnode)
		{
			ACE_DEBUG((LM_ERROR,"loop 设备不存在"));
			throw LoopDeviceNotExists();
		}
		node->SetParent(pnode);
		if(node->GetDeviceType() == KSG_999_DEV_SERVER
			|| node->GetDeviceType() == KSG_999_DEV_POS
			|| node->GetDeviceType() == KSG_999_DEV_JSB)
		{
			// 39 LPORT 或者 以太网设备
			// 将该设备与其所有的子设备增加到指令队列中
			//KsgGetGateway()->GetTaskQueue()->AddDevices(node);
		}
		return;
	}
	pnode = manager->FindDevice(pid);
	if(!pnode)
	{
		// 无法找到父节点的设备设置为 offline 状态
		node->SetState(KSGDeviceNode::dsOffline);
		ACE_DEBUG((LM_ERROR,"设备无法找到父设备节点[%d][%d]",node->GetDevId(),pid));
		return;
	}
	if(NULL == pnode->GetDevice() ||
		(pnode->GetDeviceType() != KSG_999_DEV_SERVER
		&&pnode->GetDeviceType() != KSG_LOOP_DEV_TYPE))
	{
		// 不是 LPORT 出错
		ACE_DEBUG((LM_ERROR,"上级设备[%d]不是LPORT",pnode->GetDevId()));
		return;
	}
	node->SetParent(pnode);
}

void KSG999DeviceLoader::SetRunningQueue(KSGDeviceNode* node)
{
	/*
	if(node->GetParentId() == KSGDeviceNode::LoopDeviceId)
	{
		KsgGetGateway()->GetTaskQueue()->AddDevices(node);
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////
//
int KSG999DevInterLoader::LoadInterface(KSGDeviceManager *manager)
{
	return 0;
}

