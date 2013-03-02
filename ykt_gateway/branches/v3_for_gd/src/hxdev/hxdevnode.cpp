/**
* V1.2 修改了设备节点 toplogic 初始化功能
*/

#include "hxdev/hxdevnode.h"
#include "ksgateway.h"
#include "netutil.h"
#include "xutils/xstring.h"
#include "task_scheduler.h"
#include "impl/schdimpl.h"
#include "osutil.h"
#include "execimpl.h"
#include <ace/Test_and_Set.h>
#include <ace/Null_Mutex.h>
#include <ace/SOCK_Connector.h>
#include <ace/OS.h>
#include "pubfunc.h"
#include <curl/curl.h>

//#pragma comment(lib,"SetTimedll.lib")

#define KSG_HX_DEV	"haoxing"

using namespace HXDEV;


// 对昊星设备的支持

//#undef KSG_HX_DEV_SUPPORT

#ifdef KSG_HX_DEV_SUPPORT


// 注册昊星设备类型工厂
KSG_REG_FACTORY_INTERFACE(KSG_HX_DEV,KSGHXDevInterfaceFactory);

// 注册昊星设备类型
KSG_REG_DEVICE_OBJECT(KSG_HX_DEV,KSG_HX_KQ_DEV,HXKqDevice);

/// 注册昊星设备接口
/*
KSG_REG_DEV_INTERFACE(KSG_HX_DEV,TK_COLLDATA_TASK,IHDCollectData);
*/

#endif // KSG_HX_DEV_SUPPORT


bool HXKqDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
//	if(typeid(guest) == typeid(KSGTaskCollHeartBeat::CollHeartBeatVisitor))
//	return true;

	if(typeid(guest) == typeid(KSGTaskCollectSerial::CollectSerialVisitor))
		return true;

	return false;
}

int HXKqDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	if(!node)
		return -1;
	*handler = ACE_HANDLE(node->GetDevId());
	return 0;
}

int HXKqDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ()
{
	return 0;
}


//////////////////////////////////////////////////////////////////////
// HDDeviceLoader
int HXDeviceLoader::Finish(KSGDeviceManager* manager)
{
	KSGDeviceManager::DeviceList * devs = manager->GetDevices();
	//std::for_each(devs->begin(),devs->end(),
	//	boost::bind(&HDDeviceLoader::SetupDeviceNoticeTask,this,_1));
	// 设置指令队列的分组
	try
	{
		manager->Traseval(boost::bind(&HXDeviceLoader::SetupDeviceGroup,this,_1));
	}
	catch(KSGException&)
	{
		return -1;
	}
	return 0;
}

int HXDeviceLoader::LoadDevice(KSGDeviceManager* manager)
{
	ACE_DEBUG((LM_INFO,"开始加载昊星设备..."));
	try
	{
		// modified by 汤成  2006-12-31
		// 修改 : 将设备节点 toplogic 的初始化工作交给外层框架来完成
		// 设置设备的物理结构关系
		/*
		std::for_each(devs->begin(),devs->end(),
		boost::bind(&HDDeviceLoader::SetupDevice,this,manager,_1));
		*/
	}
	catch(...)
	{
	}
	return 0;
}

void HXDeviceLoader::SetupDeviceGroup(KSGDeviceNode* node)
{
	if(node->get_vendor() != KSG_HX_DEV)
		return;
	node->connect_module(KSGDeviceNode::cm_long_conn);
	// 不需要设置 loop device ,
	if(node->GetDeviceType() == KSG_HX_KQ_DEV)
	{
		KSG_Task_Queue *queue = Task_Queue_Pool::instance()->add_initial_queue(KSG_SCHEDULER_STATUS);
		if(queue)
		{
			// 增加所有设备
			if(queue->load_all_device(node))
			{
				ACE_DEBUG((LM_INFO,"加载设备失败！"));
				throw KSGException();
			}
		}
		else
		{
			ACE_DEBUG((LM_WARNING,"设备无法创建任务队列,dev[%d]",node->GetDevId()));
		}
	}
}
//////////////////////////////////////////////////////////////////////
// HXDevInterfaceLoader
int HXDevInterfaceLoader::LoadInterface(KSGDeviceManager *manager)
{
	try
	{
		ACE_DEBUG((LM_INFO,"加载昊星设备接口........."));
		// 为设备类型增加接口
		KSG_ADD_DEVICE_INTERFACE(KSG_HX_DEV,KSG_HX_KQ_DEV,IHXCollectData);		

		return 0;
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"加载昊星设备接口失败.........."));
		return -1;
	}
}

int HXTaskExecutorLoader::LoadExecutor()
{
	// 注册指令执行处理接口
	return 0;
}
//////////////////////////////////////////////////////////////////////
//

int IHXCollectData::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret;
	std::vector<KQINFO> vecKqInfo;

	if(!bDllLoad)
	{
		ACE_DEBUG((LM_ERROR,"动态库[SetTimedll.dll]未加载"));
		return TASK_ERR_COMMON;
	}

	KSGDevice* device = node->GetDevice();
	if(!device)
		return TASK_ERR_COMMON;

	int termID = node->GetTermId();

	FileParse m_fileParse(termID);
	std::string ip = node->GetDevAddr().GetConnect();
	if (ip.length() < 7)
	{
		ACE_DEBUG((LM_ERROR,"获取考勤机IP[%s]错误",ip));
		return TASK_ERR_COMMON;
	}

	std::map<std::string,std::string> EqmMap;
	std::map<std::string,std::string>::iterator mapIter;
	int eqmNo = 0;
	
	CCIniFile IniFile(config_path);
	IniFile.ReadSectionValues("EqmNO",EqmMap);

	//是否已经添加考勤机
	for (mapIter = EqmMap.begin();mapIter != EqmMap.end();mapIter++)
	{
		eqmNo = (atoi)(mapIter->second.c_str());
		if (eqmNo == termID)
			goto label;
	}
	//设置ip
	for(int i = 0,off = 0;i<4;i++)
	{
		int npos = ip.find(".",off);
		std::string pstr = ip.substr(off,npos-off).c_str();
		kqMsg[i] = atoi(pstr.c_str());
		off = npos+1;
	}
	kqMsg[4] = 10;				//时间间隔
	kqMsg[5] = 2;				//图片规格中等
	kqMsg[6] = termID;			//机号
	if(addEqm(kqMsg) != 1)
	{
		ACE_DEBUG((LM_ERROR,"添加考勤机[%d]失败",termID));
		return TASK_ERR_COMMON;
	}

label:	
	ret = dataRtn((char*)ip.c_str());
	if(ret == 0)
	{
		ACE_DEBUG((LM_ERROR,"从机号[%d],IP[%s]采集数据失败",termID,ip.c_str()));
		return TASK_ERR_COMMON;
	}
	if (ret == 2)
	{
		ACE_DEBUG((LM_ERROR,"机号[%d],IP[%s]无数据",termID,ip.c_str()));
		return TASK_ERR_COMMON;
	}
	if (ret == 3)
	{
		ACE_DEBUG((LM_ERROR,"机号[%d],IP[%s]数据被中断",termID,ip.c_str()));
		return TASK_ERR_COMMON;
	}
	if (ret == -1)
	{
		ACE_DEBUG((LM_ERROR,"机号[%d],IP[%s]端口占用",termID,ip.c_str()));
		return TASK_ERR_COMMON;
	}
	
	ret = m_fileParse.getKqInfo(vecKqInfo);
	if(ret != 0)
	{
		ACE_DEBUG((LM_ERROR,"解析考勤文件出错"));
		return TASK_ERR_COMMON;
	}
	
	m_fileParse.writeLog(vecKqInfo);

	DRTPPoolType::SmartObject obj;
	try
	{
		obj = KsgGetDrtpPool()->Alloc();
	}
	catch (NoneResourceException& )
	{
		// 没有资源	
		ACE_DEBUG((LM_ERROR,"申请DRTP连接失败！"));
		return TASK_ERR_EXECUTE;
	}	

	unsigned long phyCardNo = 0;
	char phyNo[9] = "";
	std::vector<KQINFO>::iterator iter;
	for (iter = vecKqInfo.begin();iter != vecKqInfo.end();iter++ )
	{
		if(obj->Connect())
		{
			// 连接失败
			return TASK_ERR_EXECUTE;
		}
		phyCardNo = atol(iter->phyCardID);
		sprintf(phyNo,"%08X",phyCardNo);

		obj->SetRequestHeader(930203);		
		obj->AddField(F_SDATE1,phyNo);
		obj->AddField(F_SDATE0,iter->date);
		obj->AddField(F_STIME0,iter->time);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);	//sys_id
		obj->AddField(F_SEMP_NO,153);										//tx_mark
		obj->AddField(F_LVOL5,node->GetDevId());							//deviceID
		if(!obj->SendRequest(5000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"添加考勤信息失败[%d]错误码[%d]"
					,node->GetDevId(),obj->GetReturnCode()));
			}
		}
	}

	return TASK_SUCCESS;
}

