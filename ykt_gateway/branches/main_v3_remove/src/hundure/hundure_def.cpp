#include "hundure/hundure_def.h"
#include "hundure/rac2000devnode.h"
#include "hundure/gcu3devnode.h"
#include "hundure/ncu3devnode.h"
#include "task_scheduler.h"
#include "execimpl.h"
#include "impl/schdimpl.h"

///////////////////////////////////////////////////////////////////
DECLARE_NAMESPACE_BEGIN(HUNDURE)

KSG_REG_FACTORY_INTERFACE(KSG_HUNDURE_DEV,KSG_HNDR_DevInterfaceFactory);

// 注册汇多设备类型
#ifdef HAS_RAC2000G_SUPPORT
KSG_REG_DEVICE_OBJECT(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,HNDR_RAC2000G);
#endif

#ifdef HAS_RAC2000P_SUPPORT
KSG_REG_DEVICE_OBJECT(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,HNDR_RAC2000P);
#endif 

#ifdef HAS_GCU_SUPPORT
KSG_REG_DEVICE_OBJECT(KSG_HUNDURE_DEV,HUNDURE_GCU3,HNDR_GCU3);
#endif

#ifdef HAS_NCU_SUPPORT
KSG_REG_DEVICE_OBJECT(KSG_HUNDURE_DEV,HUNDURE_NCU3,HNDR_NCU3);
#endif
///////////////////////////////////////////////////////////
int HNDR_convert_cardphy_hex2dec(const std::string &hex_str
								 ,std::string &dec_str)
{
	if(hex_str.length() != 8)
		return -1;
	unsigned long val = ACE_OS::strtoul(hex_str.c_str(),NULL,16);
	KSG_Memory_Util::revert_buffer((unsigned char*)&val,sizeof val);
	char tmp[20] = "";
	ACE_OS::sprintf(tmp,"%010lu",val);
	dec_str = tmp;
	return 0;
}

int HNDR_convert_cardphy_dec2hex(const std::string &dec_str 
								 ,std::string &hex_str)
{
	unsigned long val = ACE_OS::strtoul(dec_str.c_str(),NULL,10);
	KSG_Memory_Util::revert_buffer((unsigned char*)&val,sizeof val);
	char tmp[20] = "";
	ACE_OS::sprintf(tmp,"%08X",val);
	hex_str = tmp;
	return 0;
}
int HNDR_convert_cardphy_hex2zip(const std::string &hex_str
								   ,char zip_str[5])
{
	std::string dec_str;
	if(HNDR_convert_cardphy_hex2dec(hex_str,dec_str))
		return -1;
	int len;
	len = dec_str.length() >> 1;
	int i;
	for (i = 0;i < len;++i)
	{
		zip_str[i] = (dec_str[i*2] << 4) | (dec_str[i*2+1] & 0x0F);
	}
	if((len * 2) < dec_str.length())
	{
		zip_str[len] = (dec_str[len*2] << 4) | 0x0F;
		len++;
	}
	i = len;
	while(i < 5)
	{
		zip_str[i++] = 0xFF;
	}
	return 0;
}
int HNDR_convert_cardphy_zip2hex(const char zip_str[5]
								   ,std::string &hex_str)
{
	char tmp[20] = "";
	int i,j;
	for(i = 0,j = 0; i < 5;++i)
	{
		char hi = (zip_str[i] >> 4) & 0x0F;
		char lo = zip_str[i] & 0x0F;
		if(hi != 0x0F)
			tmp[j++] = hi;
		if(lo != 0x0F)
			tmp[j++] = lo;
	}
	std::string dec_str = tmp;
	return HNDR_convert_cardphy_dec2hex(dec_str,hex_str);
}
int HNDR_convert_event_datetime(const char *event_date
								,char *date_str,int maxlen)
{
	struct tm date_tm;
	ACE_OS::strptime(const_cast<char *>(event_date),"%Y/%m/%d %H:%M:%S",&date_tm);
	ACE_OS::strftime(date_str,maxlen,"%Y%m%d%H%M%S",&date_tm);
	return 0;
}

int HNDR_event_code_2_ks_event(const HNDR_Event_Code_Def_t *defs,int event_code)
{
	int i = 0;
	while(defs[i].hndr_event_code != HNDR_EVENT_CODE_END)
	{
		if(event_code == defs[i].hndr_event_code)
			return defs[i].ks_event_code;
		i++;
	}
	return HNDR_KS_EVENT_UNKNOWN;
}

int HNDR_errcode_2_task_err(int errcode)
{
	if(errcode)
		ACE_DEBUG((LM_INFO,"汉军设备执行任务返回码[%d]",errcode));
	switch(errcode)
	{
	case E_HNDR_TIMEOUT:
		//return TASK_ERR_TIMEOUT;
	// 需要重连
	// 执行超时
	case E_HNDR_SYNC_ERR:
		//return TASK_ERR_EXECUTE;
	//  执行错误
	case E_HNDR_PARAM_ERR:
	case E_HNDR_FAILED:
	case E_HNDR_INVALID_HANDLE:
		return TASK_INVALID_CONN;
	// return TASK_ERR_EXECUTE;
	// 执行成功
	case 1010: // polling 无数据
	case E_HNDR_SUCCESS:
		return TASK_SUCCESS;
	// 其他错误
	default:
		return TASK_ERR_EXECUTE;
	}
}
////////////////////////////////////////////////////////////
// HNDR_Door_Device
KSG_REG_DEVICE_OBJECT(KSG_HUNDURE_DEV,HUNDURE_DOOR,HNDR_Door_Device);

ACE_Thread_Mutex HNDR_Device_Base::_mutex;
ACE_Thread_Mutex HNDR_Device_Base::Poll_Status_t::_mutex;

int HNDR_Door_Device::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	return 1;
}
int HNDR_Door_Device::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw()
{
	return 1;
}

bool HNDR_Door_Device::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	return false;
}
KSG_REG_DEVICE_OBJECT(KSG_HUNDURE_DEV,HUNDURE_BF430,HNDR_BF430);
int HNDR_BF430::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	KSGDeviceNode *child = node->GetFirstChild();
	if(child)
	{
		KSGDeviceURL url = node->GetDevAddr();
		int ret;
		HNDR_HANDLE hd;
		if(url.GetConnType() != KSGDeviceURL::dctTCP)
		{
			return 1;
		}
		std::string ip = node->GetDevAddr().GetConnect();
		int port = node->GetDevAddr().GetPort();
		// 连接之前等待一段时间，保证连接效率
		KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_conn_interval);
#if defined HAS_RAC2000P_SUPPORT || defined HAS_RAC2000G_SUPPORT
		if(child->GetDeviceType() == HUNDURE_RAC2000P
			|| child->GetDeviceType() == HUNDURE_RAC2000G)
		{
			ret = hacOpenChannel(ip.c_str(),port,&hd);
			if(ret)
				hacCloseChannel(hd);
			goto L_FINISH;
		}
#endif
#ifdef HAS_GCU_SUPPORT
		if(child->GetDeviceType() == HUNDURE_GCU3)
		{
			ret = hsGCUOpenChannel(&hd,ip.c_str(),port);
			if(ret)
				hsGCUCloseChannel(&hd);
			goto L_FINISH;
		}
#endif
#ifdef HAS_NCU_SUPPORT
		if(child->GetDeviceType() == HUNDURE_NCU3)
		{
			ret = E_HNDR_FAILED;
			goto L_FINISH;
		}
#endif

L_FINISH:
		if(ret == E_HNDR_PARAM_ERR)
		{
			ACE_DEBUG((LM_ERROR,"设备参数不正确,返回码[%d]",ret));
			return -1;
		}
		else if(ret == E_HNDR_FAILED)
		{
			ACE_DEBUG((LM_ERROR,"连接汉军设备失败,dev[%d],ret[%d]",node->GetDevId(),ret));
			node->SetState(KSGDeviceNode::dsOffline);
			//KSGThreadUtil::Sleep(100);
			return -1;
		}
		else if(ret == E_HNDR_SUCCESS)
		{
			*handler = (ACE_HANDLE)hd;
			return 0;
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"连接汉军设备失败,dev[%d],未知错误,ret[%d]",node->GetDevId(),ret));
			node->SetState(KSGDeviceNode::dsOffline);
			return -1;
		}
	}
	else
		ACE_DEBUG((LM_NOTICE,"汉军设备参数错误，无法连接,dev[%d]",node->GetDevId()));
	return -1;
}
int HNDR_BF430::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ()
{
	KSGDeviceNode *child = node->GetFirstChild();
	if(child)
	{
		KSGDeviceURL url = node->GetDevAddr();
		int ret;
		HNDR_HANDLE hd = static_cast<HNDR_HANDLE>(handler);
		if(url.GetConnType() == KSGDeviceURL::dctCOM)
		{
			return 1;
		}

#if defined HAS_RAC2000P_SUPPORT || defined HAS_RAC2000G_SUPPORT
		if(child->GetDeviceType() == HUNDURE_RAC2000P
			|| child->GetDeviceType() == HUNDURE_RAC2000G)
		{
			ret = hacCloseChannel(hd);
			goto L_FINISH;
		}
#endif
#ifdef HAS_GCU_SUPPORT
		if(child->GetDeviceType() == HUNDURE_GCU3)
		{
			ret = hsGCUCloseChannel(hd);
			goto L_FINISH;
		}
#endif
#ifdef HAS_NCU_SUPPORT
		if(child->GetDeviceType() == HUNDURE_NCU3)
		{
			ret = E_HNDR_FAILED;
			goto L_FINISH;
		}
#endif

L_FINISH:
		if(ret)
		{
			ACE_DEBUG((LM_ERROR,"断开连接失败,dev[%d],未知错误,ret[%d]",node->GetDevId(),ret));
			return -1;
		}
		return 0;
	}
	return -1;
}
bool HNDR_BF430::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	return false;
}

HNDR_Device_Base::Poll_Status_Ptr_t HNDR_Device_Base::find_status_ptr(KSGDeviceNode* node)
{
	ACE_MT(ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_mutex,Poll_Status_Ptr_t()));
	Dev_Poll_Status_map_t::iterator i = _dev_poll_status.find(node);
	if(i!=_dev_poll_status.end())
		return i->second;
	else
	{
		Poll_Status_Ptr_t ptr(new Poll_Status_t);
		_dev_poll_status.insert(Dev_Poll_Status_map_t::value_type(node,ptr));
		return ptr;
	}
}

bool HNDR_Device_Base::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	if(typeid(guest) == typeid(KSGTaskDoorBatchDlCard::BatchDownloadCardVisitor))
		return true;
	if(typeid(guest) == typeid(KSGTaskCollectSerial::CollectSerialVisitor))
	{
		if(visitor != NULL)
		{
			Poll_Status_Ptr_t status = find_status_ptr(visitor);
			bool need = false;
			ACE_MT(ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,status->_mutex,false));
			time_t curr = ACE_OS::gettimeofday().sec();
			if(status->_last_record == 0 || status->_last_status == psFailed)
			{
				// once per 500ms 
				// 15s 
				int span = (status->_empty_times + 1);
				if(curr - status->_last_timetick >= span)
				{
					need = true;
					status->_last_timetick = curr;
				}
				// 90s 
				if(status->_empty_times>30)
					status->_empty_times = 0;
			}
			else
				need = true;
			return need;
		}
	}
	return false;
}

void HNDR_Device_Base::update_poll_status(KSGDeviceNode* node,int success,
										   int record_cnt)
{
	ACE_ASSERT(node != NULL);
	Poll_Status_Ptr_t status = find_status_ptr(node);
	ACE_MT(ACE_GUARD(ACE_Thread_Mutex,mon,status->_mutex));
	if(success == psSuccess)
	{
		status->_last_record = record_cnt;
		status->_last_status = psSuccess;
		status->_empty_times = 0;
	}
	else
	{
		status->_last_status = psFailed;
		status->_empty_times++;
	}
	status->_last_timetick = ACE_OS::gettimeofday().sec();
}

int HNDR_Device_Base::get_last_poll_record(KSGDeviceNode* node)
{
	Poll_Status_Ptr_t status = find_status_ptr(node);
	ACE_MT(ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_mutex,0));
	return status->_last_record;
}
//////////////////////////////////////////////////////////////////

void HNDR_DeviceLoader::SetupDeviceGroup(KSGDeviceNode* node)
{
	KSG_Task_Queue *queue = NULL;
	if(node->get_vendor() != KSG_HUNDURE_DEV)
		return;
	node->connect_module(KSGDeviceNode::cm_long_conn);
	if(node->GetDeviceType() == HUNDURE_BF430)
	{
		queue = Task_Queue_Pool::instance()->add_initial_queue(KSG_SCHEDULER_STATUS);
	}
	else if(node->GetDeviceType() == HUNDURE_GCU3
		|| node->GetDeviceType() == HUNDURE_RAC2000P
		|| node->GetDeviceType() == HUNDURE_RAC2000G
		|| node->GetDeviceType() == HUNDURE_NCU3)
	{
		if(node->GetParent()->GetDeviceType() == HUNDURE_BF430)
		{
			// 作为下级设备加载
			return;
		}
		queue = Task_Queue_Pool::instance()->add_initial_queue(KSG_SCHEDULER_STATUS);
	}
	else
		return;
	ACE_ASSERT(queue != NULL);
	// 无法加载设备
	if(queue->load_all_device(node))
	{
		ACE_DEBUG((LM_ERROR,"无法加载设备dev[%d]",node->GetDevId()));
		throw KSGException();
	}
	return;
}
int HNDR_DeviceLoader::Finish(KSGDeviceManager* manager)
{
	KSGDeviceManager::DeviceList * devs = manager->GetDevices();
	try
	{
		manager->Traseval(boost::bind(&HNDR_DeviceLoader::SetupDeviceGroup,this,_1));
	}
	catch (KSGException &e)
	{
		KSG_DUMP_EXCEPTION(e);
		return -1;
	}
	return 0;
}
int HNDR_DeviceLoader::LoadDevice(KSGDeviceManager* manager)
{
	return 0;
}

int HNDR_DevInterfaceLoader::LoadInterface(KSGDeviceManager *manager)
{
	try
	{
#ifdef HAS_RAC2000G_SUPPORT
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RACP_DLUL_Card);
		//KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RAC_DL_Timesect);
		//KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RAC_DL_Week);
		//KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RAC_DL_Holiday);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RAC2000_UL_Event);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RAC2000_UL_Timer);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RAC2000_DL_Timer);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RAC2000_Ctrl_Door_Open);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RACP_Batch_DL_Card);
		//KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RAC2000_Loss_Card);
		//KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000G,ID_HNDR_RAC2000_Unloss_Card);
#endif

#ifdef HAS_RAC2000P_SUPPORT
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RACP_DLUL_Card);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RAC_DL_Timesect);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RAC_DL_Week);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RAC_DL_Holiday);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RAC2000_UL_Event);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RAC2000_UL_Timer);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RAC2000_DL_Timer);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RAC2000_Ctrl_Door_Open);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RACP_Batch_DL_Card);
		//KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RAC2000_Loss_Card);
		//KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_RAC2000P,ID_HNDR_RAC2000_Unloss_Card);
#endif
#ifdef HAS_GCU_SUPPORT
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_GCU3,ID_HNDR_GCU_DL_Week);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_GCU3,ID_HNDR_GCU_DL_Holiday);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_GCU3,ID_HNDR_GCU_UL_Event);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_GCU3,ID_HNDR_GCU_DL_Card);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_GCU3,ID_HNDR_GCU_DL_Timesect);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_GCU3,ID_HNDR_GCU_DL_Timer);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_GCU3,ID_HNDR_GCU_UL_Timer);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_GCU3,ID_HNDR_GCU_Ctrl_Door);
		KSG_ADD_DEVICE_INTERFACE(KSG_HUNDURE_DEV,HUNDURE_GCU3,ID_HNDR_GCU_Batch_DL_Card);
#endif
	}
	catch (...)
	{
		//
	}
	return 0;
}

int HNDR_TaskExecutorLoader::LoadExecutor()
{
	/*
	KSG_REGISTER_TASK_EXECUTOR(TK_DOOR_DL_TIME_SECT,DoorDLTimesectExec);
	KSG_REGISTER_TASK_EXECUTOR(TK_DOOR_DL_WEEK,DoorDLWeekExec);
	KSG_REGISTER_TASK_EXECUTOR(TK_DOOR_DL_HOLIDAY,DoorDLHolidayExec);
	KSG_REGISTER_TASK_EXECUTOR(TK_DOOR_DL_CARD,DoorDLCardExec);
	KSG_REGISTER_TASK_EXECUTOR(TK_DL_TIMER,TimerDLULExec);
	KSG_REGISTER_TASK_EXECUTOR(TK_UL_TIMER,TimerDLULExec)
	*/
	return 0;
}

DECLARE_NAMESPACE_END(HUNDURE);
