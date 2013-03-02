
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
	ACE_DEBUG((LM_DEBUG,"��ʼ����999�豸..."));
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
			ACE_DEBUG((LM_ERROR,"loop �豸������"));
			throw LoopDeviceNotExists();
		}
		node->SetParent(pnode);
		if(node->GetDeviceType() == KSG_999_DEV_SERVER
			|| node->GetDeviceType() == KSG_999_DEV_POS
			|| node->GetDeviceType() == KSG_999_DEV_JSB)
		{
			// 39 LPORT ���� ��̫���豸
			// �����豸�������е����豸���ӵ�ָ�������
			//KsgGetGateway()->GetTaskQueue()->AddDevices(node);
		}
		return;
	}
	pnode = manager->FindDevice(pid);
	if(!pnode)
	{
		// �޷��ҵ����ڵ���豸����Ϊ offline ״̬
		node->SetState(KSGDeviceNode::dsOffline);
		ACE_DEBUG((LM_ERROR,"�豸�޷��ҵ����豸�ڵ�[%d][%d]",node->GetDevId(),pid));
		return;
	}
	if(NULL == pnode->GetDevice() ||
		(pnode->GetDeviceType() != KSG_999_DEV_SERVER
		&&pnode->GetDeviceType() != KSG_LOOP_DEV_TYPE))
	{
		// ���� LPORT ����
		ACE_DEBUG((LM_ERROR,"�ϼ��豸[%d]����LPORT",pnode->GetDevId()));
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

