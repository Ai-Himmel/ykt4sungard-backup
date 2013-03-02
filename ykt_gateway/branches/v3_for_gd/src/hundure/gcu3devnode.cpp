#include "hundure/gcu3devnode.h"
#include "hundure/hundure_def.h"
#include "xutils/xstring.h"
#include "ksgateway.h"
#include "osutil.h"
#include "pubfunc.h"

#ifdef HAS_GCU_SUPPORT
#include "hundure/GCU3.h"
#include "hundure/ReaderL.h"
#ifdef WIN32
#ifdef _DEBUG
#pragma message("auto like gcu3 library")
#pragma comment(lib,"gcu3_d.lib")
#else
#pragma message("auto like gcu3 library")
#pragma comment(lib,"gcu3.lib")
#endif // _DEBUG
#endif // WIN32

DECLARE_NAMESPACE_BEGIN(HUNDURE)

#define GCU_TABLE_TIMESECT_BEGIN 24819
#define GCU_TIMESECT_LEN 32
#define GCU_WEEK_LEN 7
#define GCU_TABLE_WEEK_BEGIN 23041
#define GCU_TABLE_HOLIDAY_BEGIN 0
#define GCU_TABLE_HOLIDAY_DEFINE_BEGIN 3841
#define GCU_HOLIDAY_DATE_MAX 100
#define GCU_MAX_DOOR_COUNT 30

static const int g_gcu_default_timeout = 1500;
static HNDR_Err_Define_t g_hndr_gcu_err[] = {
	{0,"成功"},
	{1001,"主机响应错误码,错误码存放于参数iReturnCode中。"},
	{1002,"Socket读写错误或者串口读写错误，执行异步读写的时候发生错误。"},
	{1003,"主机返回的数据长度错误，长度太短。"},
	{1004,"传入的句柄无效，hComm为无效值。"},
	{1005,"主机响应封包结束字符错误。"},
	{1006,"主机响应封包CRC-16检查错误。"},
	{1007,"主机不支持此Function。"},
	{1008,"主机对下层设备进行R/W读写时出现错误。"},
	{1009,"传送出去的数据长度超出最大的允许长度。"},
	{1025,"执行异步读写的时候出现超时错误，超过等待时间(iTimeout)。"},
	{2225,"执行异步读写的时候，没有接收到任何数据。"},
	{-1,NULL}
};

static HNDR_Err_Define_t g_hndr_gcu_device_err[] = {
	{0x0001,"数据长度与合法卡长度不符"},
	{0x0002,"合法卡长度不符"},
	{0x0003,"已超过可容纳的笔数"},
	{0x0005,"系统参数设定值错误"},
	{0x0006,"卡号不存在"},
	{0x0007,"设定数据长度过长"},
	{0x0008,"读取数据长度过长"},
	{0x0009,"数据长度不符"},
	{0x000A,"装置无响应"},
	{0x000B,"装置响应数据错误"},
	{0x000C,"写入装置数据过长"},
	{0x000F,"输入数据错误"},
	{0x0011,"已超过可联机数量"},
	{0x0013,"主机写入FLASH失败"},
	{0x0014,"装置响应错误ERROR"},
	{0x0015,"装置响应错误BCCERROR"},
	{0x0016,"装置响应错误CMDERROR"},
	{-1,NULL}
};

static void gcu_get_errmsg(int errcode,char msg[512],HNDR_Err_Define_t *err_define)
{
	int i = 0;
	while(g_hndr_gcu_err[i].err_msg != NULL)
	{
		if(errcode == err_define[i].err_code)
		{
			ACE_OS::strcpy(msg,err_define[i].err_msg);
			return;
		}
		i++;
	}
	ACE_OS::strcpy(msg,"未知错误");
}

static void gcu_get_return_errmsg(int errcode,char msg[512])
{
	gcu_get_errmsg(errcode,msg,g_hndr_gcu_err);
}

static void gcu_get_device_errmsg(int errcode,char msg[512])
{
	gcu_get_errmsg(errcode,msg,g_hndr_gcu_device_err);
}
typedef struct {
	int addr;
	const unsigned char *in_buf;
	size_t len;
}gcu_matrix_data_t;

static int gcu_encode_matrix_table(const unsigned char* in_buf,size_t len
								   ,unsigned short begin_addr,unsigned char *buf,size_t *out_len)
{
	if(len > 100)
		return 1;
	buf[0] = static_cast<unsigned char>(len);
	*out_len = 1;
	for (size_t i = 0;i < len; ++i,++begin_addr)
	{
		SHORT_2_BUF_LE(begin_addr,&buf[*out_len]);
		*out_len += 2;
		buf[*out_len] = static_cast<unsigned char>(in_buf[i]);
		(*out_len)++;
	}
	return 0;
}
static int gcu_encode_matrix_table_v(gcu_matrix_data_t *tbl_v,int count
									 ,unsigned char *out_buf,int *out_len)
{
	ssize_t recv_len = 1;
	ssize_t total_len = 0;
	out_buf[0] = 0;
	for(int idx = 0;idx < count; ++idx)
	{
		gcu_matrix_data_t * data = &tbl_v[idx];
		if(total_len > 100)
			return 1;
		total_len += data->len;
		int begin_addr = data->addr;
		for (ssize_t i = 0;i < data->len; ++i,++begin_addr)
		{
			SHORT_2_BUF_LE(begin_addr,&out_buf[recv_len]);
			recv_len += 2;
			out_buf[recv_len] = static_cast<unsigned char>(data->in_buf[i]);
			recv_len++;
			out_buf[0] += 1;
		}
	}
	*out_len = recv_len;
	return 0;
}

static void gcu_get_curr_year_bcd(unsigned char *year_bcd)
{
	struct tm *curr_tm;
	time_t curr_tv;
	ACE_OS::time(&curr_tv);
	curr_tm = ACE_OS::gmtime(&curr_tv);
	char tmp[5] = "";
	ACE_OS::snprintf(tmp,5,"%.04d",curr_tm->tm_year + 1900);
	xutil::StringUtil::Str2BCD(tmp+2,2,year_bcd);
}

int HNDR_GCU3::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	KSGDeviceURL url = node->GetDevAddr();
	int ret;
	HNDR_HANDLE hd;
	if(url.GetConnType() == KSGDeviceURL::DevConnType::dctCOM)
	{
		// com
		char com[5] = "";
		sprintf(com,"COM%d",url.GetPort());
		int rate = HUNDURE_RAC_BAND_RATE;
		ret = hsGCUOpenChannel(&hd,com,rate);
	}
	else
	{
		/*
		std::string ip = node->GetDevAddr().GetConnect();
		int port = node->GetDevAddr().GetPort();
		ret = hsGCUOpenChannel(&hd,ip.c_str(),port);
		*/
		return 1;
	}
	if(ret == E_HNDR_PARAM_ERR)
	{
		ACE_DEBUG((LM_ERROR,"设备参数不正确,返回码[%d]",ret));
		return -1;
	}
	else if(ret == E_HNDR_FAILED)
	{
		ACE_DEBUG((LM_ERROR,"连接设备失败,dev[%d]",node->GetDevId()));
		node->SetState(KSGDeviceNode::dsOffline);
		return -1;
	}
	else if(ret == E_HNDR_SUCCESS)
	{
		*handler = (ACE_HANDLE)hd;
		return 0;
	}
	else
	{
		ACE_DEBUG((LM_ERROR,"连接设备失败,dev[%d],未知错误",node->GetDevId()));
		node->SetState(KSGDeviceNode::dsOffline);
		return -1;
	}
}
int HNDR_GCU3::close_handler(KSGDeviceNode* node,ACE_HANDLE handler)
{
	KSGDeviceURL url = node->GetDevAddr();
	if(url.GetConnType() != KSGDeviceURL::DevConnType::dctCOM)
		return 1;
	HNDR_HANDLE hd = (HNDR_HANDLE)handler;
	int ret;
	ret = hsGCUCloseChannel(hd);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"关闭设备连接错误,dev[%d]ret[%d]"
			,node->GetDevId(),ret));
		return -1;
	}
	return 0;
}
//////////////////////////////////////////////////////////////
// 接口定义
std::string ID_HNDR_GCU_DL_Timesect::get_day_time(const KSGTaskParams &param
												  ,const char *param_name)
{
	std::string param_value("");
	try
	{
		param_value = param.GetParam(param_name);
		// 过滤不合法的时间
		if(param_value.length() != 8)
			param_value = "";
	}
	catch (...)
	{
	}
	return param_value;
}
int ID_HNDR_GCU_DL_Timesect::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int seqno,ret;
	try
	{
		seqno = task->GetParams().GetParamIntVal(XML_KEY_SEQNO);
	}
	catch (...)
	{
		return TASK_ERR_PARAM;
	}
	std::string day_time("");
	day_time += get_day_time(task->GetParams(),XML_KEY_DOORTIME1);
	day_time += get_day_time(task->GetParams(),XML_KEY_DOORTIME2);
	day_time += get_day_time(task->GetParams(),XML_KEY_DOORTIME3);
	day_time += get_day_time(task->GetParams(),XML_KEY_DOORTIME4);
	day_time += get_day_time(task->GetParams(),XML_KEY_DOORTIME5);
	day_time += get_day_time(task->GetParams(),XML_KEY_DOORTIME6);
	day_time += get_day_time(task->GetParams(),XML_KEY_DOORTIME7);
	day_time += get_day_time(task->GetParams(),XML_KEY_DOORTIME8);
	int day_time_len = day_time.length();
	if(day_time_len == 0 || seqno < 0)
		return TASK_ERR_PARAM;
	// 时区从 1 开始
	seqno++;

	HNDR_HANDLE hd = (HNDR_HANDLE)task->_handle;
	int begin_addr = GCU_TABLE_TIMESECT_BEGIN + seqno * GCU_TIMESECT_LEN;
	unsigned char bcd_daytime[33] = "";
	unsigned char matrix_tbl[512] = "";
	size_t matrix_len;
	// 如果不足 8 个时间段, 补 FFFF
	/*
	if(day_time.length() < 8 * 8)
		day_time += "FFFF";
	*/
	xutil::StringUtil::Str2BCD(day_time.c_str(),day_time.length(),bcd_daytime);
	day_time_len /= 2;
	if(day_time_len < 4 * 8)
	{
		bcd_daytime[day_time_len++] = 0xFF;
		bcd_daytime[day_time_len++] = 0xFF;
	}

	ret = gcu_encode_matrix_table(bcd_daytime,day_time_len,begin_addr
		,matrix_tbl,&matrix_len);
	if(ret || matrix_len > 4*8*3+1 || matrix_len <= 0)
		return TASK_ERR_PARAM;

	KSGDeviceNode *task_node = task->GetDeviceNode();
	ACE_ASSERT(task_node != NULL);
	KSGDeviceNode *task_parent = task_node->GetParent();
	ACE_ASSERT(task_parent != NULL);
	int gcu_errcode = 0;
	ret = hsGCUMatrixWriteTable(hd,task_parent->GetTermId(),matrix_tbl
		,(int)matrix_len,&gcu_errcode,g_gcu_default_timeout);
	char errmsg[512] = "";
	KSGTaskResponse &resp = task->GetResponse();
	if(ret)
	{
		gcu_get_return_errmsg(ret,errmsg);
		ACE_DEBUG((LM_ERROR,"下传设备时间段错误,ret[%d][%s]"
			,ret,errmsg));
		if(gcu_errcode > 0)
		{
			gcu_get_return_errmsg(gcu_errcode,errmsg);
			resp.AddField(KEY_TASK_ERR_MSG,errmsg);
		}
		if(ret)
			return HNDR_errcode_2_task_err(ret);
	}
	resp.AddField(XML_KEY_SEQNO,--seqno);
	resp.AddField(XML_KEY_MAJOR_DEV,task_node->GetParent()->GetDevId());
	resp.AddField(XML_KEY_MINOR_DEV,-1);
	// 表示设置的是时间段组
	resp.AddField(XML_KEY_FTFLAG,1);
	return TASK_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
//
int ID_HNDR_GCU_Batch_DL_Card::success_download(int custid,int device_id)
{
	DRTPPoolType::SmartObject drtp = KsgGetDrtpPool()->Alloc();
	if(!drtp)
		return TASK_ERR_EXECUTE;
	drtp->SetRequestHeader(HUNDURE_DEVICE_CARDLIST);
	drtp->AddField(F_LVOL11,1); // for update
	drtp->AddField(F_LVOL0,device_id);
	drtp->AddField(F_LVOL1,custid);
	drtp->AddField(F_LVOL2,2); // RAC 批量下载名单
	if(drtp->SendRequest(2000))
	{
		if(drtp->GetReturnCode())
			ACE_DEBUG((LM_ERROR,"更新人员名单失败[%d]",drtp->GetReturnCode()));
		return TASK_ERR_EXECUTE;
	}
	return TASK_SUCCESS;
}

int ID_HNDR_GCU_Batch_DL_Card::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	static const int max_cardlist_count = 500;
	struct_CardFormat this_card[max_cardlist_count];
	ACE_OS::memset(this_card,0,sizeof(struct_CardFormat) * max_cardlist_count);
	HNDR_HANDLE hd = (HNDR_HANDLE)task->_handle;
	int ret,door_idx,i,retries;
	int custid;
	std::string phyno;

	//ACE_DEBUG((LM_DEBUG,"下载门禁人员名单[%s]",phyno.c_str()));
	KSGDeviceNode *task_node = task->GetDeviceNode();
	ACE_ASSERT(task_node != NULL);

	// 机号
	int nodeid = node->GetTermId();
	

	//ACE_DEBUG((LM_INFO,"下载门禁人员名单系统卡号[%s],下传卡号[%s]",phyno.c_str(),phyno_dec.c_str()));
	int gcu_errcode;
	char errmsg[512] = "";
	KSGTaskResponse &resp = task->GetResponse();
	
	{
		door_idx = 0;
		DRTPPoolType::SmartObject drtp = KsgGetDrtpPool()->Alloc();
		if(!drtp)
			return TASK_ERR_EXECUTE;
		drtp->SetRequestHeader(HUNDURE_DEVICE_CARDLIST);
		drtp->AddField(F_LVOL0,task_node->GetDevId());
		drtp->AddField(F_LVOL1,0);
		drtp->AddField(F_LVOL2,3);
		if(drtp->SendRequest(5000))
		{
			if(drtp->GetReturnCode())
				ACE_DEBUG((LM_ERROR,"查询人员名单失败[%d]",drtp->GetReturnCode()));
			return TASK_ERR_EXECUTE;
		}
		//ACE_DEBUG((LM_DEBUG,"xxxxx下载门禁人员名单[%s]",phyno_dec.c_str()));
		while(drtp->HasMoreRecord() && door_idx < max_cardlist_count)
		{
			ST_PACK *data = drtp->GetNextRecord();

			std::string phyno_dec;
			phyno = data->sdate0;
			// 如果是 wiegand 读卡器
			if(task_node->card_type() == KSGDeviceNode::ct_wiegand)
			{
				char temp[15] = "";
				KsgCardID_M1_2_WG(phyno.c_str(),temp,10);
				phyno_dec = temp;
			}
			else
			{
				if(HNDR_convert_cardphy_hex2dec(phyno,phyno_dec))
					return TASK_ERR_PARAM;
			}
			if(strcmp(phyno_dec.c_str(),this_card[door_idx].cCardNo) !=0)
			{
				door_idx++;
				// 一般卡
				this_card[door_idx].iType = 0x81;
				this_card[door_idx].iCompressed = 0;
				this_card[door_idx].iLimitDate = 1;
				this_card[door_idx].iPassLen = 4;
				// 物理卡号
				ACE_OS::strcpy(this_card[door_idx].cCardNo,phyno_dec.c_str());
				this_card[door_idx].iCardLen = ACE_OS::strlen(this_card[door_idx].cCardNo);
				this_card[door_idx].iDisplayID = data->lvol3; // 借用保存客户号
				
			}
			int door_no = data->lvol2;
			int weekno = data->lvol0;
			this_card[door_idx].iHoliday = data->lvol1 + 1;
			if(door_no>=0 && door_no < GCU_MAX_DOOR_COUNT && data->lvol4 < 8) // 删除的名单不需要下载
			{
				this_card[door_idx].cTimeZone[door_no] = static_cast<char>(weekno+1);
				this_card[door_idx].iDoors++;
			}
		}
	}
	for(i = 1;i <= door_idx; ++i)
	{
		retries = 3;
		custid = this_card[i].iDisplayID;
		this_card[i].iDisplayID = 0;
		while(retries-->0)
		{		
			KSGThreadUtil::Sleep(50);
			char temp[17];
			if(this_card[i].iDoors > 0)
			{
				//ACE_DEBUG((LM_DEBUG,"xxxx增加卡[%s]",phyno_dec.c_str()));
				ACE_OS::memset(temp,0,sizeof temp);
				for (int j = 0;j < sizeof(temp)-1;++j)
				{
					temp[j] = this_card[i].cTimeZone[j] + 0x30;
				}
				this_card[i].iDoors = task_node->get_port_count(); // 对应 GCU 的门数
				ret = hsGCUInsertMultiUserRecord(hd,task_node->GetTermId(),1,&this_card[i]
					,&gcu_errcode,g_gcu_default_timeout);
				
				ACE_DEBUG((LM_INFO,"下载GCU名单GCU[%d:%d]phyno[%s]week[%s],ret[%d]"
					,task_node->GetDevId(),task_node->GetTermId(),this_card[i].cCardNo,temp,ret));
			}
			else
			{
				//ACE_DEBUG((LM_DEBUG,"xxxx删除卡[%s]",phyno_dec.c_str()));
				ret = hsGCUDeleteUserRecord(hd,task_node->GetTermId(),0
					,this_card[i].cCardNo,&gcu_errcode,g_gcu_default_timeout);
				ACE_DEBUG((LM_INFO,"删除GCU名单GCU[%d:%d]phyno[%s]ret[%d]"
					,task_node->GetDevId(),task_node->GetTermId(),this_card[i].cCardNo,ret));
				// 卡号不存在
				if(gcu_errcode == 0x06)
					ret = 0;
			}
			if(!ret)
				break;
		}
		if(ret)
		{
			gcu_get_return_errmsg(ret,errmsg);
			ACE_DEBUG((LM_ERROR,"下传卡名单错误,ret[%d][%s]"
				,ret,errmsg));
			if(gcu_errcode > 0)
			{
				gcu_get_device_errmsg(gcu_errcode,errmsg);
				ACE_DEBUG((LM_ERROR,"下传卡名单错误，GCU返回[%d][%s]",gcu_errcode,errmsg));
				resp.AddField(KEY_TASK_ERR_MSG,errmsg);
			}
			ACE_DEBUG((LM_ERROR,"下传卡名单错误，返回[%d]",ret));
			return HNDR_errcode_2_task_err(ret);
		}
		if(success_download(custid,task_node->GetDevId()))
		{
			ACE_DEBUG((LM_ERROR,"下载名单成功，应答系统失败，dev[%d],custid[%d]",task_node->GetDevId(),custid));
			return TASK_ERR_EXECUTE;
		}
		ACE_DEBUG((LM_INFO,"下传名单成功 GCU[%d]卡号[%s]",task_node->GetDevId(),this_card[i].cCardNo));
	}
	return TASK_SUCCESS;
}
////////////////////////
int ID_HNDR_GCU_DL_Card::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	HNDR_HANDLE hd = (HNDR_HANDLE)task->_handle;
	int weekno,holiday,flag,ret;
	int custid;
	std::string phyno = task->GetParams().GetParam(XML_KEY_CARDPHY);
	try
	{
		flag = task->GetParams().GetParamIntVal(XML_KEY_FTFLAG);
		//if(flag != 0)
		//{
		custid = task->GetParams().GetParamIntVal(XML_KEY_CUSTID);
		weekno = task->GetParams().GetParamIntVal(XML_KEY_WEEKNO);
		holiday = task->GetParams().GetParamIntVal(XML_KEY_HOLIDAY);
		//}
	}
	catch (...)
	{
		return TASK_ERR_PARAM;
	}
	
	if(phyno.length() != 8 || flag < 0 || flag > 1)
	{
		return TASK_ERR_PARAM;
	}
	//ACE_DEBUG((LM_DEBUG,"下载门禁人员名单[%s]",phyno.c_str()));
	KSGDeviceNode *task_node = task->GetDeviceNode();
	ACE_ASSERT(task_node != NULL);
	KSGDeviceNode *task_parent = task_node->GetParent();
	ACE_ASSERT(task_parent != NULL);
	// 机号
	int nodeid = node->GetTermId();
	std::string phyno_dec;
	// 如果是 wiegand 读卡器
	if(task_parent->card_type() == KSGDeviceNode::ct_wiegand)
	{
		char temp[15] = "";
		KsgCardID_M1_2_WG(phyno.c_str(),temp,10);
		phyno_dec = temp;
	}
	else
	{
		if(HNDR_convert_cardphy_hex2dec(phyno,phyno_dec))
			return TASK_ERR_PARAM;
	}
	
	ACE_DEBUG((LM_INFO,"下载门禁人员名单系统卡号[%s],下传卡号[%s]",phyno.c_str(),phyno_dec.c_str()));
	int gcu_errcode;
	char errmsg[512] = "";
	KSGTaskResponse &resp = task->GetResponse();
	//if(flag != 0)
	//{
	struct_CardFormat this_card;
	ACE_OS::memset(&this_card,0,sizeof this_card);
	ACE_OS::strcpy(this_card.cCardNo,phyno_dec.c_str());
	this_card.iCompressed = 0;
	this_card.iLimitDate = 1;
	this_card.iPassLen = 4;
	this_card.iCardLen = phyno_dec.length();
	// 一般卡
	this_card.iType = 0x81;
	if(weekno < 0 || custid <= 0)
	{
		return TASK_ERR_PARAM;
	}
	if(holiday == -1)
		this_card.iHoliday = 0;
	else
		this_card.iHoliday = holiday+1;
	DRTPPoolType::SmartObject drtp = KsgGetDrtpPool()->Alloc();
	if(!drtp)
		return TASK_ERR_EXECUTE;
	drtp->SetRequestHeader(HUNDURE_DEVICE_CARDLIST);
	drtp->AddField(F_LVOL0,task_parent->GetDevId());
	drtp->AddField(F_LVOL1,custid);
	drtp->AddField(F_LVOL2,1);
	drtp->AddField(F_SDATE0,phyno.c_str());
	if(drtp->SendRequest(1000))
	{
		if(drtp->GetReturnCode())
			ACE_DEBUG((LM_ERROR,"查询人员名单失败[%d][%s]",drtp->GetReturnCode()
			,drtp->GetReturnMsg().c_str()));
		return TASK_ERR_EXECUTE;
	}
	//ACE_DEBUG((LM_DEBUG,"xxxxx下载门禁人员名单[%s]",phyno_dec.c_str()));
	ACE_OS::memset(this_card.cTimeZone,0x00,sizeof(this_card.cTimeZone));
	while(drtp->HasMoreRecord() && this_card.iDoors < GCU_MAX_DOOR_COUNT)
	{
		ST_PACK *data = drtp->GetNextRecord();
		int door_idx = data->lvol2;
		int weekno = data->lvol0;
		//this_card.iHoliday = data->lvol1 + 1;
		if(door_idx>=0 && door_idx < GCU_MAX_DOOR_COUNT)
		{
			this_card.cTimeZone[door_idx] = static_cast<char>(weekno+1);
			this_card.iDoors++;
		}
	}

	if(this_card.iDoors > 0)
	{
		//ACE_DEBUG((LM_DEBUG,"xxxx增加卡[%s]",phyno_dec.c_str()));
		this_card.iDoors = task_parent->get_port_count();
		ret = hsGCUInsertMultiUserRecord(hd,task_parent->GetTermId(),1,&this_card
			,&gcu_errcode,g_gcu_default_timeout);
	}
	else
	{
		//ACE_DEBUG((LM_DEBUG,"xxxx删除卡[%s]",phyno_dec.c_str()));
		ret = hsGCUDeleteUserRecord(hd,task_parent->GetTermId(),0
			,phyno_dec.c_str(),&gcu_errcode,g_gcu_default_timeout);
		// 卡号不存在
		if(gcu_errcode == 0x06)
			ret = 0;
	}

	if(ret)
	{
		gcu_get_return_errmsg(ret,errmsg);
		ACE_DEBUG((LM_ERROR,"下传卡名单错误,ret[%d][%s]"
			,ret,errmsg));
		if(gcu_errcode > 0)
		{
			gcu_get_device_errmsg(gcu_errcode,errmsg);
			ACE_DEBUG((LM_ERROR,"下传卡名单错误，GCU返回[%d][%s]",gcu_errcode,errmsg));
			resp.AddField(KEY_TASK_ERR_MSG,errmsg);
		}
		if(ret)
		{
			ACE_DEBUG((LM_ERROR,"下传卡名单错误，返回[%d]",ret));
			return HNDR_errcode_2_task_err(ret);
		}
	}
	ACE_DEBUG((LM_INFO,"下传名单成功 GCU[%d]卡号[%s]",task_parent->GetDevId(),phyno_dec.c_str()));
	return TASK_SUCCESS;
}
////////////////////////
int ID_HNDR_GCU_DL_Holiday::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	HNDR_HANDLE hd = static_cast<HNDR_HANDLE>(task->_handle);
	int seqno,holiday_id,ret,h_idx;
	try
	{
		seqno = task->GetParams().GetParamIntVal(XML_KEY_SEQNO);
		holiday_id = task->GetParams().GetParamIntVal(XML_KEY_HOLIDAY);
	}
	catch (...)
	{
		return TASK_ERR_PARAM;
	}

	KSGDeviceNode *task_node = task->GetDeviceNode();
	ACE_ASSERT(task_node != NULL);
	KSGDeviceNode *task_parent = task_node->GetParent();
	ACE_ASSERT(task_parent != NULL);
	DRTPPoolType::SmartObject drtp = KsgGetDrtpPool()->Alloc();
	if(!drtp)
		return TASK_ERR_EXECUTE;
	drtp->SetRequestHeader(HUNDURE_HOLIDAY_FUNC_NO);
	drtp->AddField(F_LVOL2,holiday_id);
	drtp->AddField(F_LVOL0,task_parent->GetDevId());
	drtp->AddField(F_LVOL1,-1);
	drtp->AddField(F_LVOL3,1);
	if(drtp->SendRequest(2000))
	{
		if(drtp->GetReturnCode())
			ACE_DEBUG((LM_ERROR,"查询节假日失败[%d]",drtp->GetReturnCode()));
		return TASK_ERR_EXECUTE;
	}
	unsigned char data_buf[3*GCU_HOLIDAY_DATE_MAX];
	memset(data_buf,0xFF,sizeof data_buf);
	int i = 0;
	while(drtp->HasMoreRecord() && i < GCU_HOLIDAY_DATE_MAX)
	{
		ST_PACK *data = drtp->GetNextRecord();
		xutil::StringUtil::Str2BCD(data->sdate0+4,4,&data_buf[i*3]);
		data_buf[i*3+2] = static_cast<unsigned char>(data->lvol0+1);
		i++;
	}
	int data_len = i*3;
	// 没有数据,返回成功
	if(data_len == 0)
		goto L_END;
	int gcu_errcode;
	char errmsg[512] = "";
	KSGTaskResponse &resp = task->GetResponse();
	h_idx = seqno++;
	unsigned int start_addr = GCU_TABLE_HOLIDAY_DEFINE_BEGIN 
		+ h_idx * sizeof(data_buf);
	int send_len = 3 * 30;
	for (int i = 0;i < sizeof data_buf;i+=send_len)
	{
		ret = hsGCUWriteTable(hd,task_parent->GetTermId(),start_addr+i
			,data_buf+i,send_len,&gcu_errcode,g_gcu_default_timeout);
		if(ret)
			break;
	}

	if(ret)
	{
		gcu_get_return_errmsg(ret,errmsg);
		ACE_DEBUG((LM_ERROR,"下传设备时间段错误,ret[%d][%s]"
			,ret,errmsg));
		if(gcu_errcode > 0)
		{
			gcu_get_device_errmsg(gcu_errcode,errmsg);
			resp.AddField(KEY_TASK_ERR_MSG,errmsg);
		}
		return TASK_ERR_EXECUTE;
	}
	unsigned char curr_year;
	gcu_get_curr_year_bcd(&curr_year);
	ACE_OS::memset(data_buf,0,sizeof data_buf);
	unsigned char tmp[2*GCU_MAX_DOOR_COUNT];
	//tmp[0] = static_cast<unsigned char>(seqno);
	ACE_OS::memset(tmp,h_idx,sizeof tmp);
	start_addr = GCU_TABLE_HOLIDAY_BEGIN + 1 + GCU_MAX_DOOR_COUNT * (seqno-1) * 2;
	gcu_matrix_data_t data_v[2] = {
		{GCU_TABLE_HOLIDAY_BEGIN,&curr_year,1},
		{start_addr,tmp,sizeof(tmp)}
	};
	ret = gcu_encode_matrix_table_v(data_v,2,data_buf,&data_len);
	if(ret)
		return TASK_ERR_EXECUTE;
	ret = hsGCUMatrixWriteTable(hd,task_parent->GetTermId(),data_buf,data_len
		,&gcu_errcode,g_gcu_default_timeout);
	if(ret)
	{
		gcu_get_return_errmsg(ret,errmsg);
		ACE_DEBUG((LM_ERROR,"下传设备节假日,ret[%d][%s]"
			,ret,errmsg));
		if(gcu_errcode > 0)
		{
			gcu_get_device_errmsg(gcu_errcode,errmsg);
			resp.AddField(KEY_TASK_ERR_MSG,errmsg);
		}
		if(ret)
			return HNDR_errcode_2_task_err(ret);
	}
L_END:
	resp.AddField(XML_KEY_MAJOR_DEV,task_parent->GetDevId());
	resp.AddField(XML_KEY_MINOR_DEV,-1);
	resp.AddField(XML_KEY_SEQNO,--seqno);
	return TASK_SUCCESS;
}
////////////////////////
int ID_HNDR_GCU_DL_Week::get_week_day(const KSGTaskParams &param,const char* param_name)
{
	try
	{
		int ret = param.GetParamIntVal(param_name);
		return ret;
	}
	catch (...)
	{
		return -1;
	}
}
int ID_HNDR_GCU_DL_Week::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret,seqno;
	try
	{
		seqno = task->GetParams().GetParamIntVal(XML_KEY_SEQNO);
	}
	catch (...)
	{
		return TASK_ERR_PARAM;
	}
	int day1_id,day2_id,day3_id,day4_id,day5_id,day6_id,day7_id;
	day1_id = get_week_day(task->GetParams(),XML_KEY_WEEK_DAY1);
	day2_id = get_week_day(task->GetParams(),XML_KEY_WEEK_DAY2);
	day3_id = get_week_day(task->GetParams(),XML_KEY_WEEK_DAY3);
	day4_id = get_week_day(task->GetParams(),XML_KEY_WEEK_DAY4);
	day5_id = get_week_day(task->GetParams(),XML_KEY_WEEK_DAY5);
	day6_id = get_week_day(task->GetParams(),XML_KEY_WEEK_DAY6);
	day7_id = get_week_day(task->GetParams(),XML_KEY_WEEK_DAY7);
	seqno;
	HNDR_HANDLE hd = (HNDR_HANDLE)task->_handle;
	int begin_addr = GCU_TABLE_WEEK_BEGIN + seqno * GCU_WEEK_LEN;
	unsigned char week_def[7];
	week_def[0] = static_cast<unsigned char>(day1_id+1);
	week_def[1] = static_cast<unsigned char>(day2_id+1);
	week_def[2] = static_cast<unsigned char>(day3_id+1);
	week_def[3] = static_cast<unsigned char>(day4_id+1);
	week_def[4] = static_cast<unsigned char>(day5_id+1);
	week_def[5] = static_cast<unsigned char>(day6_id+1);
	week_def[6] = static_cast<unsigned char>(day7_id+1);
	unsigned char matrix_tbl[512] = "";
	size_t matrix_len;
	ret = gcu_encode_matrix_table(week_def,sizeof week_def,begin_addr
		,matrix_tbl,&matrix_len);
	if(ret || matrix_len > 7*3+1 || matrix_len <= 0)
		return TASK_ERR_PARAM;
	KSGDeviceNode *task_node = task->GetDeviceNode();
	ACE_ASSERT(task_node != NULL);
	KSGDeviceNode *task_parent = task_node->GetParent();
	ACE_ASSERT(task_parent != NULL);
	int gcu_errcode = 0;
	ret = hsGCUMatrixWriteTable(hd,task_parent->GetTermId(),matrix_tbl,(int)matrix_len
		,&gcu_errcode,g_gcu_default_timeout);
	char errmsg[512] = "";
	KSGTaskResponse &resp = task->GetResponse();
	if(ret)
	{
		gcu_get_return_errmsg(ret,errmsg);
		ACE_DEBUG((LM_ERROR,"下传设备时间段错误,ret[%d][%s]"
			,ret,errmsg));
		if(gcu_errcode > 0)
		{
			gcu_get_return_errmsg(gcu_errcode,errmsg);
			resp.AddField(KEY_TASK_ERR_MSG,errmsg);
		}
		if(ret)
			return HNDR_errcode_2_task_err(ret);
	}

	resp.AddField(XML_KEY_SEQNO,seqno);
	resp.AddField(XML_KEY_MAJOR_DEV,task_node->GetParent()->GetDevId());
	resp.AddField(XML_KEY_MINOR_DEV,-1);
	return TASK_SUCCESS;
}

int ID_HNDR_GCU_UL_Event::upload_event_to_server(KSGDeviceNode *node
												 ,stPollList_GCU *poll_list,int recv_record)
{
	int success,retries;
	DRTPPoolType::SmartObject drtp = KsgGetDrtpPool()->Alloc();
	if(!drtp)
		return 0;
	for(success = 0; success < recv_record;++success)
	{
		char phy_no[9] = "";
		std::string hex_str;
		if(ACE_OS::strlen(poll_list[success].cCard) > 0)
		{
			if(HNDR_convert_cardphy_dec2hex(poll_list[success].cCard,hex_str))
			{
				ACE_DEBUG((LM_ERROR,"收到的卡号错误"));
				continue;
			}
			//xutil::StringUtil::revert_str(hex_str.c_str(),8,phy_no);
			ACE_OS::strncpy(phy_no,hex_str.c_str(),8);
			ACE_DEBUG((LM_DEBUG,"采集门禁事件，卡号dec[%s],hex[%s]"
				,poll_list[success].cCard,hex_str.c_str()));
		}
		drtp->SetRequestHeader(HUNDURE_EVENT_FUNC_NO);
		drtp->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		drtp->AddField(F_SEMP_NO,poll_list[success].cStatusCode);
		ACE_DEBUG((LM_DEBUG,"采集门禁事件，卡号dec[%s],hex[%s]event[%s]"
			,poll_list[success].cCard,hex_str.c_str(),poll_list[success].cStatusCode));
		drtp->AddField(F_SDATE1,phy_no);
		char date_str[15] = "";
		HNDR_convert_event_datetime(poll_list[success].cDateTime,date_str);
		int device_id = ACE_OS::atoi(poll_list[success].cDeviceID);

		drtp->AddField(F_LVOL1,device_id);
		drtp->AddField(F_LVOL2,node->GetDevId());
		drtp->AddField(F_SDATE0,date_str,8);
		drtp->AddField(F_STIME0,&date_str[8],6);
		retries = 3;
		do
		{
			if(drtp->Connect())
				continue;
			if(drtp->SendRequest(500))
				continue;
			if(drtp->GetReturnCode())
			{
				ACE_DEBUG((LM_DEBUG,"保存 GCU 事件失败，返回[%d: %s]",
					drtp->GetReturnCode(),drtp->GetReturnMsg().c_str()));
				continue;
			}
			break;
		}while(--retries>0);
		if(retries <= 0)
			return success;
	}
	return success;
}

int ID_HNDR_GCU_UL_Event::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	HNDR_HANDLE hd = (HNDR_HANDLE)task->_handle;
	HNDR_Device_Base *gcu_base;
	stPollList_GCU poll_list[256];
	ACE_OS::memset(poll_list,0,sizeof poll_list);
	int ret;
	KSGDeviceNode *task_node = task->GetDeviceNode();
	gcu_base = dynamic_cast<HNDR_Device_Base*>(task_node->GetDevice());
	if(!gcu_base)
		return TASK_ERR_PARAM;
	
	int collect_rows=0;
	// 最多只 poll 3 次
	int exec_times = 3;
	while(exec_times-->0)
	{
		int last_record = gcu_base->get_last_poll_record(task_node);
		int recv_record = 0;
		int success = 0;
		int gcu_err = 0;
		
		ret = hsGCUPolling(hd,task_node->GetTermId(),last_record,poll_list,&recv_record
			,0,0,&gcu_err,g_gcu_default_timeout);
		if(!ret)
		{
			success = upload_event_to_server(task_node,poll_list,recv_record);
		}
		if(ret || success == 0)
		{
			gcu_base->update_poll_status(task_node,HNDR_Device_Base::psFailed,0);
			break;
		}
		else
		{
			ACE_DEBUG((LM_DEBUG,"采集汉军 GCU [%d] 事件[%d] 条",task_node->GetDevId(),success));
			gcu_base->update_poll_status(task_node,HNDR_Device_Base::psSuccess,success);
			collect_rows+=success;
		}
	}
	task->SetNeedResponse(false);
	if(collect_rows == 0)
	{
		if(ret == 1010)
			return TASK_SUCCESS;
		if(ret)
			return HNDR_errcode_2_task_err(ret);
	}
	return TASK_SUCCESS;
}

int ID_HNDR_GCU_DL_Timer::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	HNDR_HANDLE hd = (HNDR_HANDLE)task->_handle;
	int errcode,ret;
	char errmsg[512] = "";
	KSGDeviceNode *task_node = task->GetDeviceNode();
	ACE_ASSERT(task_node != NULL);
	KSGDeviceNode *task_parent = task_node->GetParent();
	ACE_ASSERT(task_parent != NULL);
	std::string now_clock;
	KSGOSUtil::GetTimestamp(now_clock);
	char date_buf[10]="";
	char time_buf[7]="";
	sprintf(date_buf,"20%s",now_clock.substr(0,6).c_str());
	sprintf(time_buf,"%s",now_clock.substr(6).c_str());
	time_t now = ACE_OS::gettimeofday().sec();
	struct tm* tv = ACE_OS::localtime(&now);
	date_buf[8] = static_cast<char>(tv->tm_wday)+'0';

	KSGTaskResponse &resp = task->GetResponse();

	ret = hsGCUWriteTime(hd,task_node->GetTermId(),date_buf,time_buf,&errcode
		,g_gcu_default_timeout);
	
	if(ret)
	{
		if(errcode > 0)
		{
			gcu_get_return_errmsg(errcode,errmsg);
			resp.AddField(KEY_TASK_ERR_MSG,errmsg);
		}
		if(ret)
			return HNDR_errcode_2_task_err(ret);
	}

	return TASK_SUCCESS;
}

int ID_HNDR_GCU_UL_Timer::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	HNDR_HANDLE hd = (HNDR_HANDLE)task->_handle;
	int errcode,ret;
	char errmsg[512] = "";
	KSGDeviceNode *task_node = task->GetDeviceNode();
	ACE_ASSERT(task_node != NULL);
	KSGDeviceNode *task_parent = task_node->GetParent();
	ACE_ASSERT(task_parent != NULL);
	std::string now_clock;
	KSGOSUtil::GetTimestamp(now_clock);
	char date_buf[15]="";
	char time_buf[10]="";
	char date_time_buf[15] = "";

	KSGTaskResponse &resp = task->GetResponse();

	ret = hsGCUReadTime(hd,task_node->GetTermId(),date_buf,time_buf,&errcode
		,g_gcu_default_timeout);

	if(ret)
	{
		if(errcode > 0)
		{
			gcu_get_return_errmsg(errcode,errmsg);
			resp.AddField(KEY_TASK_ERR_MSG,errmsg);
		}
		if(ret)
			return HNDR_errcode_2_task_err(ret);
	}
	ACE_OS::strncpy(date_time_buf,date_buf,4);
	ACE_OS::strncpy(date_time_buf+4,date_buf+5,2);
	ACE_OS::strncpy(date_time_buf+6,date_buf+8,2);
	ACE_OS::strncpy(date_time_buf+8,time_buf,2);
	ACE_OS::strncpy(date_time_buf+10,time_buf+3,2);
	ACE_OS::strncpy(date_time_buf+12,time_buf+6,2);
	resp.AddField(XML_KEY_CLOCK,date_time_buf);
	return TASK_SUCCESS;
}

int ID_HNDR_GCU_Ctrl_Door::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int flag;
	try
	{
		flag = task->GetParams().GetParamIntVal(XML_KEY_FTFLAG);
	}
	catch (...)
	{
		return TASK_ERR_PARAM;
	}
	HNDR_HANDLE hd = (HNDR_HANDLE)task->_handle;
	int errcode,ret;
	char errmsg[512] = "";
	KSGDeviceNode *task_node = task->GetDeviceNode();
	ACE_ASSERT(task_node != NULL);
	KSGDeviceNode *task_parent = task_node->GetParent();
	ACE_ASSERT(task_parent != NULL);

	KSGTaskResponse &resp = task->GetResponse();

	ret = hrWriteDoorRelay(hd,task_parent->GetTermId()
		,task_node->GetTermId(),0x00,flag,&errcode,g_gcu_default_timeout);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"开门失败!!door devid[%d]",task_node->GetTermId()));
		if(errcode > 0)
		{
			gcu_get_return_errmsg(errcode,errmsg);
			resp.AddField(KEY_TASK_ERR_MSG,errmsg);
		}
		if(ret)
			return HNDR_errcode_2_task_err(ret);
	}
	else
		ACE_DEBUG((LM_INFO,"开门成功!!door devid[%d]",task_node->GetTermId()));
	return TASK_SUCCESS;
}
DECLARE_NAMESPACE_END(HUNDURE);

#endif // HAS_GCU_SUPPORT
