#include "yuchuan/yuchuandevnode.h"
#include "ksgateway.h"
#include "osutil.h"
#include "pubfunc.h"
#include "ksglobal.h"
#include "task_scheduler.h"
#include "impl/schdimpl.h"
#include "yuchuan/yuchuandef.h"
#include "xutils/xstring.h"



DECLARE_NAMESPACE_BEGIN(YUCHUAN)

KSG_REG_FACTORY_INTERFACE(KSG_YUCHUAN_DEV,KSG_YC_DevInterfaceFactory);

// 注册设备类型
KSG_REG_DEVICE_OBJECT(KSG_YUCHUAN_DEV,KSG_485_SERVER,YC_485_Server_Device);
KSG_REG_DEVICE_OBJECT(KSG_YUCHUAN_DEV,KSG_WATER_DEV,YC_Water_Device);

//////////////////////////////////////////////////////////////////////////
// DLL function
DEF_DLLFUNC(OpenCommAuto);
DEF_DLLFUNC(CloseComm);
DEF_DLLFUNC(JS_GET_RECORD);
DEF_DLLFUNC(JS_SET_Black_Version);
DEF_DLLFUNC(JS_SET_Black);
DEF_DLLFUNC(JS_GetNodeTime);
DEF_DLLFUNC(JS_SET_ONE_Black);
DEF_DLLFUNC(JS_GET_Black_Version);
DEF_DLLFUNC(JS_GET_APPOINTED_RECORD);

static const int g_yc_timeout = 300;
//////////////////////////////////////////////////////////////////////////
// global function
static unsigned long EncodeDeviceId(const char *sn)
{
	return strtoul(sn,NULL,16);
}
static void DecodeDeviceId(unsigned long device_id,char *sn)
{
	sprintf(sn,"%08X",device_id);
}
static unsigned long YCDeviceId(const unsigned char *uid)
{
	unsigned long ret;
	BUF_2_INT_LE(ret,uid);
	return ret;
}
static int YCSaveRecord(const JS_RECORD &rec,const char *phyid)
{
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
		return TASK_ERR_EXECUTE;
	obj->SetRequestHeader(950031);
	obj->AddField(F_LVOL4,rec.Record_Number); // 流水号
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);

	//DecodeDeviceId(YCDeviceId(rec.DEV_UID),phyid);
	obj->AddField(F_SDATE1,phyid);
	obj->AddField(F_SPHONE3,phyid);
	obj->AddField(F_STX_PWD,"");

	obj->AddField(F_LBANK_ACC_TYPE2,0); // 科目收费
	obj->AddField(F_SBANK_CODE2,"AAAA");
	obj->AddField(F_LVOL6,rec.Used_purse - 1); // 钱包号
	obj->AddField(F_LVOL5,rec.User_NO); // 交易卡号
	obj->AddField(F_LVOL3,"system"); // 操作员号
	/*
	1. 消费时, 交易金额是 负值 , 管理费是 正值
	2. 充值时, 交易金额是 正值
	3. 消费冲正时, 交易金额是 正值 , 管理费是 正值
	4. 充值冲正时,交易金额是 负值
	*/
	obj->AddField(F_LVOL9,rec.User_Card_Value + rec.User_Used_Value); //入卡值 
	obj->AddField(F_LVOL10,rec.User_Card_Value); // 出卡值
	obj->AddField(F_LVOL8,rec.User_Used_Value); // 交易金额
	obj->AddField(F_LVOL7,rec.Used_Times); // 钱包水号号
	char dt_buf[12] = "";
	ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",rec.Used_Time[0],rec.Used_Time[1],rec.Used_Time[2]);
	obj->AddField(F_SPOST_CODE,dt_buf);
	ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",rec.Used_Time[3],rec.Used_Time[4],rec.Used_Time[5]);
	obj->AddField(F_SPOST_CODE2,dt_buf);
	int tx_mark = 153;

	if(rec.Used_Flag == 0x05)
		tx_mark = 2;
	obj->AddField(F_LVOL12,tx_mark);
	if(!obj->SendRequest(5000))
	{
		if(obj->GetReturnCode()==0)
		{
			// 上传流水成功
			ACE_DEBUG((LM_INFO,"上传流水,dev[%s],cardno[%d],outbala[%d],money[%d],count[%d]"
				,phyid,rec.User_NO,rec.User_Card_Value,rec.User_Used_Value,rec.Used_Times));
			return TASK_SUCCESS;
		}

	}
	return TASK_ERR_EXECUTE;
}
//////////////////////////////////////////////////////////////////////////
// YC_DeviceLoader
int YC_DeviceLoader::Finish(KSGDeviceManager* manager)
{
	KSGDeviceManager::DeviceList * devs = manager->GetDevices();
	try
	{
		manager->Traseval(boost::bind(&YC_DeviceLoader::SetupDeviceGroup,this,_1));
	}
	catch (KSGException &e)
	{
		KSG_DUMP_EXCEPTION(e);
		return -1;
	}
	return 0;
}
int YC_DeviceLoader::LoadDevice(KSGDeviceManager* manager)
{
	// 加载 DLL 动态库
	HMODULE h = NULL;
	if((h = LoadLibrary("YC_ISP.dll"))==NULL)
	{
		ACE_DEBUG((LM_ERROR,"加载宇川开发库YC_ISP.dll 失败"));
		return -1;
	}
	LOAD_DLLFUNC(h,OpenCommAuto);
	LOAD_DLLFUNC(h,CloseComm);
	LOAD_DLLFUNC(h,JS_GET_RECORD);
	LOAD_DLLFUNC(h,JS_SET_Black_Version);
	LOAD_DLLFUNC(h,JS_SET_Black);
	LOAD_DLLFUNC(h,JS_GetNodeTime);
	LOAD_DLLFUNC(h,JS_SET_ONE_Black);
	LOAD_DLLFUNC(h,JS_GET_Black_Version);
	LOAD_DLLFUNC(h,JS_GET_APPOINTED_RECORD);
	return 0;
}

void YC_DeviceLoader::SetupDeviceGroup(KSGDeviceNode* node)
{
	KSG_Task_Queue *queue = NULL;
	if(node->get_vendor() != KSG_YUCHUAN_DEV)
		return;
	node->connect_module(KSGDeviceNode::cm_long_conn);
	if(node->GetDeviceType() == KSG_485_SERVER)
	{
		queue = Task_Queue_Pool::instance()->add_initial_queue(KSG_SCHEDULER_STATUS);
	}
	else
	{
		node->set_param(DEV_BLKCOUNT,"3");
		return;
	}
	ACE_ASSERT(queue != NULL);
	// 无法加载设备
	if(queue->load_all_device(node))
	{
		ACE_DEBUG((LM_ERROR,"无法加载设备dev[%d]",node->GetDevId()));
		throw KSGException();
	}
	return;
}
//////////////////////////////////////////////////////////////////////////
// YC_DevInterfaceLoader
int YC_DevInterfaceLoader::LoadInterface(KSGDeviceManager *manager)
{
	try
	{

		KSG_ADD_DEVICE_INTERFACE(KSG_YUCHUAN_DEV,KSG_WATER_DEV,YCCollectSerialInterface);
		KSG_ADD_DEVICE_INTERFACE(KSG_YUCHUAN_DEV,KSG_WATER_DEV,YCDownBlackCardInterface);
		KSG_ADD_DEVICE_INTERFACE(KSG_YUCHUAN_DEV,KSG_WATER_DEV,YCCollectHisSerial);
		
	}
	catch (...)
	{
		//
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// YC_TaskExecutorLoader
int YC_TaskExecutorLoader::LoadExecutor()
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// YC_485_Server_Device
int YC_485_Server_Device::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	KSGDeviceURL url = node->GetDevAddr();
	int ret;
	if(url.GetConnType() != KSGDeviceURL::dctCOM)
	{
		return 1;
	}
	int addr = atoi(url.GetConnect().c_str());
	HANDLE h;
	h = OpenCommAuto(addr-1,19200);
	if(h == INVALID_HANDLE_VALUE)
	{
		ACE_DEBUG((LM_ERROR,"打开宇川设备连接失败,dev[%s]com[%d]",node->GetPhyId().c_str(),addr));
		return -1;
	}
	*handler = (ACE_HANDLE)h;
	return 0;
}
int YC_485_Server_Device::close_handler(KSGDeviceNode* node,ACE_HANDLE handler)
{
	if(handler != INVALID_HANDLE_VALUE)
		CloseComm((HANDLE)handler);
	return 0;
}
bool YC_485_Server_Device::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	return false;
}
//////////////////////////////////////////////////////////////////////////
// YC_Water_Device
int YC_Water_Device::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	return 1;
}
int YC_Water_Device::close_handler(KSGDeviceNode* node,ACE_HANDLE handler)
{
	return 1;
}
bool YC_Water_Device::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	// 下载黑名单
	if(typeid(guest) == typeid(KSGTaskDownloadBlackCard::DownloadBlackCardVisitor))
		return true;
	// 采集流水
	if(typeid(guest) == typeid(KSGTaskCollectSerial::CollectSerialVisitor))
		return true;

	// 采集状态
	if(typeid(guest)== typeid(KSGTaskCollDeviceState::CollDeviceState))
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
// YC device interface
int YCCollectSerialInterface::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret,retries;
	unsigned long serial_no,device_id;
	std::string v;
	char phyid[17];
	unsigned char dt[15];
	unsigned char sw;
	KSGDeviceNode *parent;
	JS_RECORD rec;
	// 获取设备流水号
	if(node->get_param("yc_serialno",v))
	{
		serial_no = 0xFFFFFFFF;
	}
	else
	{
		serial_no = strtoul(v.c_str(),NULL,10) + 1;
	}

	
	parent = node->GetParent();
	HANDLE h = (HANDLE)task->_handle;
	device_id = EncodeDeviceId(node->GetPhyId().c_str());

	/*
	每天定时校时
	*/
	ACE_DEBUG((LM_DEBUG,"采集设备[%s]下的水控流水",parent->get_name().c_str()));
	for(int i=0;i < 10;++i)
	{
		retries = 3;
		while(retries-->0)
		{
			ACE_OS::memset(&rec,0,sizeof rec);
			ACE_DEBUG((LM_INFO,"1采集设备流水dev[%s]",node->GetPhyId().c_str()));
			ret = JS_GET_RECORD(h,node->GetTermId(),serial_no,device_id,&sw,rec,1000);
			ACE_DEBUG((LM_INFO,"2采集设备流水dev[%s]",node->GetPhyId().c_str()));
			if(ret)
			{
				if(ret == Wrong_DEV_Err)
				{
					parent = node->GetParent();
					ACE_DEBUG((LM_ERROR,"采集宇川设备流水dev[%s]termid[%d]上级[%s]与实际不符，请检查!"
						,node->GetPhyId().c_str(),node->GetTermId(),parent->get_name().c_str()));
					return TASK_ERR_PARAM;
				}
				else if(ret != No_Record_Err)
				{
					ACE_DEBUG((LM_ERROR,"采集流水失败,dev[%s]ret[%d]",node->GetPhyId().c_str(),ret));
					continue;
				}
				// 没有记录了
				ACE_DEBUG((LM_DEBUG,"宇川[%s]无流水采集",node->GetPhyId().c_str()));
				node->update_time();
				return 0;
			}
			else break;
		}
		if(retries <= 0 && ret != 0)
			return TASK_ERR_EXECUTE;
		node->update_time();
		ret = YCSaveRecord(rec,node->GetPhyId().c_str());
		if(ret==TASK_SUCCESS)
		{
			sprintf(phyid,"%d",rec.Record_Number);
			node->set_param("yc_serialno",phyid);
			serial_no = rec.Record_Number+1;
			KSGThreadUtil::Sleep(100);
			continue;
		}
		return ret;
	}
	// 上传到服务器
	return 0;
}
int YCDownBlackCardInterface::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret,retries,i;
	unsigned long serial_no,device_id;
	char phyid[9];
	unsigned char black_data[256];
	unsigned char data[10];
	unsigned char ver_data[10];
	char cardid[512];
	char temp[3];
	memset(ver_data,0,sizeof ver_data);

	std::string cardid_str = task->GetParams().GetParam(XML_KEY_CARDID);
	std::string version = task->GetParams().GetParam(XML_KEY_VERNUM);
	int count = task->GetParams().GetParamIntVal(XML_KEY_FTFLAG);
	HANDLE h = (HANDLE)task->_handle;

	memcpy(cardid,cardid_str.c_str(),cardid_str.length());

	if(count <= 0)
		return TASK_ERR_PARAM;

	for(i=0;i<count;++i)
	{
		xutil::StringUtil::Str2Hex(cardid + i*10,data,10);
		if(data[0] == 0)
		{
			// 挂失
			black_data[i*4] = 0x55;
		}
		else
		{
			// 解挂
			black_data[i*4] = 0x03;
		}
		// 交易卡号 3 bytes
		//memcpy(black_data+i*4+1,data+2,3);
		black_data[i*4+1] = data[3];
		black_data[i*4+2] = data[2];
		black_data[i*4+3] = data[1];
	}
	device_id = EncodeDeviceId(node->GetPhyId().c_str());
	retries = 3;
	while(retries-->0)
	{
		ACE_DEBUG((LM_INFO,"1下载黑名单dev[%s]",node->GetPhyId().c_str()));
		ret = JS_SET_ONE_Black(h,node->GetTermId(),count,device_id,black_data,g_yc_timeout+400);
		ACE_DEBUG((LM_INFO,"2下载黑名单dev[%s]",node->GetPhyId().c_str()));
		if(ret)
		{
			if(ret == Wrong_DEV_Err)
			{
				ACE_DEBUG((LM_ERROR,"更新宇川设备黑名单dev[%s]termid[%d]与实际不符，请检查!"
					,node->GetPhyId().c_str(),node->GetTermId()));
				return TASK_ERR_PARAM;
			}
			else
			{
				ACE_DEBUG((LM_DEBUG,"更新宇川设备黑名单失败,dev[%s],ret[%d]",
					node->GetPhyId().c_str(),ret));
			}
			
		}
		else
		{
			//ACE_HEX_DUMP((LM_ERROR,(char *)black_data,count*4));
			break;
		}
		if(retries == 0)
		{
			if(Rev_Data_Err == ret)
			{
				ACE_DEBUG((LM_ERROR,"更新宇川设备黑名单超时,请检查设备dev[%s]",node->GetPhyId().c_str()));
				return TASK_ERR_TIMEOUT;
			}
			return TASK_ERR_EXECUTE;
		}
	}
	node->update_time();
	
	// 更新版本号
	retries = 3;
	//xutil::StringUtil::Str2Hex(version.c_str(),ver_data,6);
	/*
	memset(temp,0,sizeof temp);
	for(i = 0;i < 6; ++i)
	{
		memcpy(temp,version.c_str()+i*2,2);
		ver_data[i] = strtoul(temp,NULL,10);
	}
	*/
	xutil::StringUtil::Str2BCD(version.c_str(),12,ver_data);
	while(retries-->0)
	{
		ACE_DEBUG((LM_INFO,"1更新版本号dev[%s]",node->GetPhyId().c_str()));
		ret = JS_SET_Black_Version(h,node->GetTermId(),ver_data,device_id,g_yc_timeout);
		ACE_DEBUG((LM_INFO,"2更新版本号dev[%s]",node->GetPhyId().c_str()));
		if(ret)
		{
			if(ret == Wrong_DEV_Err)
			{
				ACE_DEBUG((LM_ERROR,"更新宇川设备黑名单版本dev[%s]termid[%d]与实际不符，请检查!"
					,node->GetPhyId().c_str(),node->GetTermId()));
				return TASK_ERR_PARAM;
			}
			else
			{
				ACE_DEBUG((LM_DEBUG,"更新宇川设备黑名单失败,dev[%s],ret[%d]",
					node->GetPhyId().c_str(),ret));
			}

		}
		else
		{
			/*
			unsigned char dev_ver[10]="";
			ret = JS_GET_Black_Version(h,node->GetTermId(),dev_ver,device_id,g_yc_timeout);
			if(ret)
			{
				//
			}
			*/
			//ACE_HEX_DUMP((LM_INFO,(char*)ver_data,6));
			break;
		}
		if(retries == 0)
		{
			if(Rev_Data_Err == ret)
			{
				ACE_DEBUG((LM_ERROR,"更新宇川设备黑名单超时,请检查设备dev[%s]",node->GetPhyId().c_str()));
				return TASK_ERR_TIMEOUT;
			}
			return TASK_ERR_EXECUTE;
		}
	}

	// 应答
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
	if(obj->Connect())
	{
		// 连接失败
		return TASK_ERR_EXECUTE;
	}
	obj->SetRequestHeader(930046);
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
	obj->AddField(F_LVOL5,node->GetDevId());
	obj->AddField(F_SSERIAL0,version.c_str());
	retries = 3;
	ret = TASK_ERR_EXECUTE;
	while(retries-- > 0)
	{
		if(obj->SendRequest(5000))
		{
			// 发送指令失败
			ACE_DEBUG((LM_DEBUG,"应答更新结果失败"));
		}
		else if(obj->GetReturnCode())
		{
			ACE_DEBUG((LM_ERROR,"更新黑名单库版本失败,dev[%s],ret[%d][%s]"
				,node->GetPhyId().c_str(),obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
		}
		else
		{
			ACE_DEBUG((LM_DEBUG,"更新设备黑名单版本成功id[%d][%s]"
				,node->GetDevId(),version.c_str()));
			ret = TASK_SUCCESS;
			break;
		}
	}
	node->update_time();
	ACE_DEBUG((LM_INFO,"下载宇川设备黑名单成功,dev[%s],ver[%s]"
		,node->GetPhyId().c_str(),version.c_str()));
	return 0;
}

int YCCollectHisSerial::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret = 0;
	unsigned long device_id;
	JS_RECORD rec;
	int retries,i;
	int start_no = task->GetParams().GetParamIntVal(XML_KEY_STARTNUM);
	int end_no = task->GetParams().GetParamIntVal(XML_KEY_ENDNUM);
	if(end_no < start_no || start_no < 0)
		return TASK_ERR_EXECUTE;
	HANDLE h = (HANDLE)task->_handle;
	device_id = EncodeDeviceId(node->GetPhyId().c_str());
	for(i=start_no;i<=end_no;++i)
	{
		retries = 3;
		while(retries-->0)
		{
			memset(&rec,0,sizeof rec);
			ret = JS_GET_APPOINTED_RECORD(h,node->GetTermId(),i,device_id,rec,g_yc_timeout);
			if(ret)
			{
				if(ret == Rev_Data_Err)
					continue;
				else if(ret == Wrong_DEV_Err)
				{
					ACE_DEBUG((LM_ERROR,"补采宇川设备流水dev[%s]termid[%d]与实际不符，请检查!"
						,node->GetPhyId().c_str(),node->GetTermId()));
					return TASK_ERR_PARAM;
				}
				else
				{
					// TODO : 判断无指定记录
					ACE_DEBUG((LM_ERROR,"补采宇川设备流水dev[%s]ret[%d]，请检查!"
						,node->GetPhyId().c_str(),ret));
					return TASK_ERR_EXECUTE;
				}
			}
			else
			{
				node->update_time();
				if(rec.Record_Number == 0xFFFFFFFF)
				{
					// 无此流水
					continue;
				}
				ret = YCSaveRecord(rec,node->GetPhyId().c_str());
				if(ret)
				{
					// 保存流水失败
					ACE_DEBUG((LM_ERROR,"补采宇川设备流水保存后台失败！"));
					return TASK_ERR_EXECUTE;
				}
				// 成功，采集下一条
				break; 
			}
		}
		
	}
	return 0;
}

DECLARE_NAMESPACE_END(YUCHUAN);