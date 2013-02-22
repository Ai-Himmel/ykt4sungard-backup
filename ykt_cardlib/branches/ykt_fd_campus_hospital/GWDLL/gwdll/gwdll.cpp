#include "CIniFile.h"
#include "DRTPHelper.h"
#include "gwdef.h"
#include "netutil.h"
#include <stdio.h>
#include <stdlib.h>


#define STR_COPY(d,s) strncpy(d,s,sizeof((d)) - 1);

#ifndef TLS_BUFFER_LEN
#define TLS_BUFFER_LEN 512
#endif 
#define TLS_ERRCODE_LEN 12
//static char gs_errmsg[512] = "";
static DWORD gdwTlsIndex;

typedef struct _tagSvrInfo
{
	int svrid;					// 服务器ID号
	char ip[16];				// 本机IP地址
	char mac[18];				// 本机MAC地址
	char dyn_key[33];			// 保存到本机动态密钥

	char drtp_ip[16];			// drtp的IP地址
	int	 drtp_port;				// drtp连接端口
	int	 drtp_mainfunc;			// drtp主功能号
	int	 drtp_request;			// 发送请求
	unsigned long tick_count;   // 签到计数
}SvrInfo_t;

#define TICK_INTERVAL	1000

#define TEST_TICK_CNT(svr) \
do{ unsigned long _tick = svr.tick_count;svr.tick_count = GetTickCount();\
if(svr.tick_count - _tick < TICK_INTERVAL) { gw_set_errcode(KE_REQUEST_INTERVAL); return -1;} \
}while(0)

static SvrInfo_t gs_svr_info;

struct _tagErrMsgTable
{
	int code;
	const char* msg;
}gs_errmsg_tbl[] = 
{
	{KE_SUCCESS,"成功"},
	{KE_PERMISSION_DENY,"不允许登录,可能IP与MAC地址信息不正确"},
	{KE_CONNECT_ERROR,"不能连接到应用服务器,可能网络故障"},
	{KE_REQ_FUNC_NOT_EXISTS,"请求功能号不存在"},
	{KE_QUERY_ERROR,"查询失败, 可能服务器忙"},
	{KE_NOT_LOGIN,"检验失败,需要重新登录"},
	{KE_READ_LOCAL_MAC,"读取本机MAC地址错误"},
	{KE_CARD_NO_EXIST,"指定的卡不存在"},
	{KE_REQUEST_INTERVAL,"请求频率太快"},
	{-1,NULL}
};

#define DRTP_RT_NO_FUNCTION 9998

CDRTPHelper getSerialDrtp;

static int gw_get_server_info(SvrInfo_t* svr)
{
	std::string mac;
	std::vector<std::string> ip_list;
	std::vector<std::string>::const_iterator i;
	KSGNetUtil::GetLocalIP(ip_list);
	for(i = ip_list.begin();i != ip_list.end();++i)
	{
		if(*i == svr->ip)
			break;
	}
	if(ip_list.end() == i)
		return -1;

	if(KSGNetUtil::GetMacByIP(svr->ip,mac))
	{
		return -1;
	}
	strncpy(svr->mac,mac.c_str(),sizeof(svr->mac));
	return 0;
}

static int gw_read_local_conf(SvrInfo_t* svr)
{
	char fullpath[1128] = "";
	int len = GetModuleFileName(NULL,fullpath,1024);
	if(len <= 0)
	{	
		return -1;
	}
	fullpath[len] = '\0';
	char* pos = strrchr(fullpath,'\\');
	if(pos)
		strcpy(pos,"\\gwdll.ini");
	else
		return -1;
	//strcat(fullpath,"gwdll.ini");

	CCIniFile inifile(fullpath);
	std::string tmp = inifile.ReadString("SVR","IP","");
	if(tmp.length() == 0)
		return -1;
	STR_COPY(svr->drtp_ip,tmp.c_str());

	svr->drtp_port = inifile.ReadInteger("SVR","PORT",0);
	if(svr->drtp_port == 0)
		return -1;
	svr->drtp_mainfunc = inifile.ReadInteger("SVR","FUNC",0);
	if(svr->drtp_mainfunc == 0)
		return -1;

	tmp = inifile.ReadString("LOCAL","IP","");
	if(tmp.length() == 0)
		return -1;
	STR_COPY(svr->ip,tmp.c_str());

	svr->drtp_request = inifile.ReadInteger("SVR","REQUEST",-1);
	if(svr->drtp_request <= 1)
		return -1;
	return 0;
}

static void gw_init_errcode()
{
	LPVOID lpBuffer;
	lpBuffer = TlsGetValue(gdwTlsIndex);
	if(lpBuffer)
	{
		memset(lpBuffer,0,TLS_BUFFER_LEN);
		TlsSetValue(gdwTlsIndex,lpBuffer);
	}
}

static void gw_set_errcode(int code)
{
	LPVOID lpBuffer;
	lpBuffer = TlsGetValue(gdwTlsIndex);
	if(lpBuffer)
	{
		memset(lpBuffer,0,TLS_ERRCODE_LEN);
		sprintf((char*)lpBuffer,"%d",code);
		TlsSetValue(gdwTlsIndex,lpBuffer);
	}
}

static void gw_get_err_msg(char msg[512])
{
	LPVOID lpBuffer;
	char * p;
	lpBuffer = TlsGetValue(gdwTlsIndex);
	if(lpBuffer)
	{
		p = (char*)lpBuffer;
		strcpy(msg,p+TLS_ERRCODE_LEN);
	}
}

static void gw_set_err_msg(const char* msg)
{
	LPVOID lpBuffer;
	char * p;
	lpBuffer = TlsGetValue(gdwTlsIndex);
	if(lpBuffer)
	{
		p = (char*)lpBuffer;
		strncpy(p+TLS_ERRCODE_LEN,msg,TLS_BUFFER_LEN-TLS_ERRCODE_LEN-1);
	}
}
BOOL WINAPI DllMain(HANDLE hDLLHandle, DWORD nReason, LPVOID Reserved)
{
	LPVOID lpBuffer;
	int err_code;
	char err_msg[512] = "";
	switch(nReason)
	{
	case DLL_PROCESS_ATTACH:
		DrtpInit(&err_code,err_msg);
		memset(&gs_svr_info,0,sizeof gs_svr_info);
		gdwTlsIndex = TlsAlloc();
		lpBuffer = LocalAlloc(LPTR,TLS_BUFFER_LEN);
		TlsSetValue(gdwTlsIndex,lpBuffer);
		gw_init_errcode();
		break;
	case DLL_PROCESS_DETACH:
		TlsFree(gdwTlsIndex);
		break;
	case DLL_THREAD_ATTACH:
		lpBuffer = LocalAlloc(LPTR,TLS_BUFFER_LEN);
		TlsSetValue(gdwTlsIndex,lpBuffer);
		gw_init_errcode();
		break;
	case DLL_THREAD_DETACH:
		lpBuffer = TlsGetValue(gdwTlsIndex);
		LocalFree((HLOCAL)lpBuffer);
		break;
	default:
		break;
	}
	return TRUE;
}


int WINAPI KLogin()
{
	gw_init_errcode();
	TEST_TICK_CNT(gs_svr_info);
	// 读取本地配置
	if(gw_read_local_conf(&gs_svr_info))
	{
		gw_set_errcode(KE_UNKNOWN_ERR);
		return KGetErrorNo();
	}
	// 获得服务器信息
	if(gw_get_server_info(&gs_svr_info))
	{
		gw_set_errcode(KE_READ_LOCAL_MAC);
		return KGetErrorNo();
	}
	CDRTPHelper drtp(gs_svr_info.drtp_ip,gs_svr_info.drtp_port,gs_svr_info.drtp_mainfunc, 0);
	ST_PACK* data;
	drtp.SetRequestHeader(950001);
	drtp.AddField(F_SCUST_LIMIT,gs_svr_info.ip);
	drtp.AddField(F_SCUST_LIMIT2,gs_svr_info.mac);
	if(drtp.Connect())
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.SendRequest(3000))
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.GetReturnCode())
	{
		gw_set_errcode(KE_QUERY_ERROR);
		//STR_COPY(gs_errmsg,drtp.GetReturnMsg().c_str());
	}
	else if(drtp.HasMoreRecord())
	{
		data = drtp.GetNextRecord();
		STR_COPY(gs_svr_info.dyn_key,data->scust_limit);
		gs_svr_info.svrid = data->lvol0;
	}
	else
	{
		gw_set_errcode(KE_PERMISSION_DENY);
	}	
	return KGetErrorNo();
}

void gw_parse_drpt_return_code(int code)
{
	switch(code)
	{
	case DRTP_RT_NO_FUNCTION:
		gw_set_errcode(KE_REQ_FUNC_NOT_EXISTS);
		break;
	case 9999:
		gw_set_errcode(KE_QUERY_ERROR);
		break;
	default:
		gw_set_errcode(KE_UNKNOWN_ERR);
		break;
	}
}

int WINAPI KGetErrorNo()
{
	LPVOID lpBuffer;
	char buf[TLS_ERRCODE_LEN] = "";
	int code = -1;
	lpBuffer = TlsGetValue(gdwTlsIndex);
	if(lpBuffer)
	{
		memcpy(buf,lpBuffer,TLS_ERRCODE_LEN-1);
		code = strtoul((char*)buf,NULL,10);
	}
	return code;
}

void WINAPI KGetErrorMsg(char msg[512])
{
	int i = 0;
	memset(msg,0,512);
	gw_get_err_msg(msg);
	if(strlen(msg) > 0)
	{
		return;
	}
	int code = KGetErrorNo();
	while(gs_errmsg_tbl[i].msg != NULL)
	{
		if(gs_errmsg_tbl[i].code == code)
		{
			strcpy(msg,gs_errmsg_tbl[i].msg);
			return;
		}
		++i;
	}
	strcpy(msg,"未知错误");
}


int WINAPI KGetCardInfoByPhyId(const char phyid[9],CardInfo_t* tCard)
{
	return -1;
}
int WINAPI KGetCardInfoByCardNo(const char cardno[21],CardInfo_t* tCard)
{
	return -1;
}
int WINAPI KGetCardInfoByStuempNo(const char stuempno[21],CardInfo_t* tCard)
{
	return -1;
}

int API_EXPORT KGetCardInfo(const char phyid[9],const char cardno[21]
							,const char stuempno[21],CardInfo_t* tCard)
{
	char msg[512] = "";
	gw_init_errcode();
	TEST_TICK_CNT(gs_svr_info);
	if(gs_svr_info.svrid == 0)
	{
		gw_set_errcode(KE_NOT_LOGIN);
		return KGetErrorNo();
	}
	CDRTPHelper drtp(gs_svr_info.drtp_ip,gs_svr_info.drtp_port,gs_svr_info.drtp_mainfunc, 0);
	ST_PACK* data;
	drtp.SetRequestHeader(gs_svr_info.drtp_request);
	drtp.AddField(F_LCERT_CODE,gs_svr_info.svrid);
	drtp.AddField(F_SCUST_LIMIT,gs_svr_info.dyn_key);
	drtp.AddField(F_SDATE0,phyid);
	drtp.AddField(F_SNAME,cardno);
	drtp.AddField(F_SNAME2,stuempno);
	
	if(drtp.Connect())
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.SendRequest(3000))
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.GetReturnCode()) 
	{
		gw_parse_drpt_return_code(drtp.GetReturnCode());
		sprintf(msg,"%d:%s",drtp.GetReturnCode(),drtp.GetReturnMsg().c_str());
		gw_set_err_msg(msg);
	}
	else if(drtp.HasMoreRecord())
	{
		data = drtp.GetNextRecord();
		tCard->cardid = data->lvol0;
		STR_COPY(tCard->name,data->snote);
		STR_COPY(tCard->cardno,data->sname);
		STR_COPY(tCard->stuemp_no,data->sname2);
		STR_COPY(tCard->phyid,data->sdate0);

		// 用户信息
		tCard->sex = data->lvol1;
		STR_COPY(tCard->deptno,data->sorder0);
		STR_COPY(tCard->deptname,data->semail);
		
		tCard->cut_type = data->lvol2;
		STR_COPY(tCard->cut_name,data->semail2);

		tCard->card_type_id = data->lvol3;
		STR_COPY(tCard->card_type_name,data->scert_no);
	}
	else
	{
		gw_set_errcode(KE_QUERY_ERROR);
	}
	return KGetErrorNo();
}

int API_EXPORT KGetLossOfSthByStuempNo(const char stuempno[21], const char password[7], int validate_pwd)
{
	char msg[512] = "";
	gw_init_errcode();
	TEST_TICK_CNT(gs_svr_info);
	if (gs_svr_info.svrid == 0)
	{
		gw_set_errcode(KE_NOT_LOGIN);
		return KGetErrorNo();
	}
	CDRTPHelper drtp(gs_svr_info.drtp_ip, gs_svr_info.drtp_port, gs_svr_info.drtp_mainfunc, 0);
	drtp.SetRequestHeader(847195);				// 名单挂失
	drtp.AddField(F_LCERT_CODE, gs_svr_info.svrid);
	drtp.AddField(F_SCUST_LIMIT, gs_svr_info.dyn_key);
	drtp.AddField(F_SCUST_AUTH, stuempno);
	drtp.AddField(F_SPHONE, password);
	drtp.AddField(F_LVOL12, validate_pwd);
	if (drtp.Connect())
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if (drtp.SendRequest(3000))
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if (drtp.GetReturnCode())
	{
		gw_parse_drpt_return_code(drtp.GetReturnCode());
		sprintf(msg, "%d:%s", drtp.GetReturnCode, drtp.GetReturnMsg().c_str());
		gw_set_err_msg(msg);
	}
	return KGetErrorNo();
}

int API_EXPORT KSaveRecord(const SerialRecord_t * serial)
{
	char msg[512] = "";
	gw_init_errcode();
	if (gs_svr_info.svrid == 0)
	{
		gw_set_errcode(KE_NOT_LOGIN);
		return KGetErrorNo();
	}
	CDRTPHelper drtp(gs_svr_info.drtp_ip, gs_svr_info.drtp_port, gs_svr_info.drtp_mainfunc, 0);

	drtp.SetRequestHeader(950082,1);				// 名单挂失
	drtp.AddField(F_LCERT_CODE, gs_svr_info.svrid);
	drtp.AddField(F_SCUST_LIMIT, gs_svr_info.dyn_key);
	drtp.AddField(F_SEMP,serial->sys_id);
	drtp.AddField(F_SNATION_CODE,serial->event_code);
	drtp.AddField(F_SCERT_ADDR,serial->event_des);
	drtp.AddField(F_SCARD0,serial->card_no);
	drtp.AddField(F_SCARD1,serial->card_no2);
	drtp.AddField(F_SNAME,serial->phy_card);
	drtp.AddField(F_SNAME2,serial->device_id);
	drtp.AddField(F_SBANK_ACC,serial->device_name);
	drtp.AddField(F_SBANK_ACC2,serial->device_name2);
	drtp.AddField(F_SEMP_PWD,serial->pwd1);
	drtp.AddField(F_SEMP_PWD2,serial->pwd2);
	drtp.AddField(F_SDATE0,serial->tx_date);
	drtp.AddField(F_SDATE1,serial->tx_date1);
	drtp.AddField(F_STIME0,serial->tx_time);
	drtp.AddField(F_STIME1,serial->tx_time1);
	drtp.AddField(F_LSAFE_LEVEL,serial->card_id);
	drtp.AddField(F_LVOL1,serial->lvol1);
	drtp.AddField(F_LVOL2,serial->lvol2);
	drtp.AddField(F_LVOL3,serial->lvol3);
	drtp.AddField(F_LVOL4,serial->lvol4);
	drtp.AddField(F_LVOL5,serial->lvol5);
	drtp.AddField(F_DAMT1,serial->amt1);
	drtp.AddField(F_DAMT2,serial->amt2);
	drtp.AddField(F_DAMT3,serial->amt3);
	drtp.AddField(F_DAMT4,serial->amt4);
	drtp.AddField(F_DAMT5,serial->amt5);

	if (drtp.Connect())
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if (drtp.SendRequest(3000))
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if (drtp.GetReturnCode())
	{
		gw_parse_drpt_return_code(drtp.GetReturnCode());
		sprintf(msg, "%d:%s", drtp.GetReturnCode, drtp.GetReturnMsg().c_str());
		gw_set_err_msg(msg);
	}
	return KGetErrorNo();
}

int API_EXPORT KSendRequest(int req_no,SerialRecord_t* request,SerialRecord_t* response)
{
	char msg[512] = "";
	gw_init_errcode();
	if (gs_svr_info.svrid == 0)
	{
		gw_set_errcode(KE_NOT_LOGIN);
		return KGetErrorNo();
	}
	CDRTPHelper drtp(gs_svr_info.drtp_ip, gs_svr_info.drtp_port, gs_svr_info.drtp_mainfunc, 0);
	
	drtp.SetRequestHeader(950010,1);				// 
	drtp.AddField(F_LSERIAL0,req_no);				// 
	drtp.AddField(F_LCERT_CODE, gs_svr_info.svrid);
	drtp.AddField(F_SCUST_LIMIT, gs_svr_info.dyn_key);
	drtp.AddField(F_SEMP,request->sys_id);
	drtp.AddField(F_SNATION_CODE,request->event_code);
	drtp.AddField(F_SCERT_ADDR,request->event_des);
	drtp.AddField(F_SCARD0,request->card_no);
	drtp.AddField(F_SCARD1,request->card_no2);
	drtp.AddField(F_SNAME,request->phy_card);
	drtp.AddField(F_SNAME2,request->device_id);
	drtp.AddField(F_SBANK_ACC,request->device_name);
	drtp.AddField(F_SBANK_ACC2,request->device_name2);
	drtp.AddField(F_SEMP_PWD,request->pwd1);
	drtp.AddField(F_SEMP_PWD2,request->pwd2);
	drtp.AddField(F_SDATE0,request->tx_date);
	drtp.AddField(F_SDATE1,request->tx_date1);
	drtp.AddField(F_STIME0,request->tx_time);
	drtp.AddField(F_STIME1,request->tx_time1);
	drtp.AddField(F_LSAFE_LEVEL,request->card_id);
	drtp.AddField(F_LVOL1,request->lvol1);
	drtp.AddField(F_LVOL2,request->lvol2);
	drtp.AddField(F_LVOL3,request->lvol3);
	drtp.AddField(F_LVOL4,request->lvol4);
	drtp.AddField(F_LVOL5,request->lvol5);
	drtp.AddField(F_DAMT1,request->amt1);
	drtp.AddField(F_DAMT2,request->amt2);
	drtp.AddField(F_DAMT3,request->amt3);
	drtp.AddField(F_DAMT4,request->amt4);
	drtp.AddField(F_DAMT5,request->amt5);

	if (drtp.Connect())
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if (drtp.SendRequest(3000))
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if (drtp.GetReturnCode())
	{
		gw_parse_drpt_return_code(drtp.GetReturnCode());
		sprintf(msg, "%d:%s", drtp.GetReturnCode(), drtp.GetReturnMsg().c_str());
		gw_set_err_msg(msg);
	}
	else
	{
		ST_PACK * data;
		if(drtp.HasMoreRecord())
		{
			data = drtp.GetNextRecord();
			STR_COPY(response->sys_id,data->semp);
			STR_COPY(response->event_code,data->snation_code);
			STR_COPY(response->event_des,data->scert_addr);
			STR_COPY(response->card_no,data->scard0);
			STR_COPY(response->card_no2,data->scard1);
			STR_COPY(response->phy_card,data->sname);
			STR_COPY(response->device_id,data->sname2);
			STR_COPY(response->device_name,data->sbank_acc);
			STR_COPY(response->device_name2,data->sbank_acc2);
			STR_COPY(response->pwd1,data->semp_pwd);
			STR_COPY(response->pwd2,data->semp_pwd2);
			STR_COPY(response->tx_date,data->sdate0);
			STR_COPY(response->tx_date1,data->sdate1);
			STR_COPY(response->tx_time,data->stime0);
			STR_COPY(response->tx_time1,data->stime1);
			response->card_id = data->lsafe_level;
			response->lvol1 = data->lvol1;
			response->lvol2 = data->lvol2;
			response->lvol3 = data->lvol3;
			response->lvol4 = data->lvol4;
			response->lvol5 = data->lvol5;
			response->amt1 = data->damt1;
			response->amt2 = data->damt2;
			response->amt3 = data->damt3;
			response->amt4 = data->damt4;
			response->amt5 = data->damt5;
			return 0;
		}
		else
		{
			gw_set_errcode(KE_QUERY_ERROR);
		}
	}
	return KGetErrorNo();
}

int WINAPI KInitLocal()
{
	gw_init_errcode();
	TEST_TICK_CNT(gs_svr_info);
	// 读取本地配置
	if(gw_read_local_conf(&gs_svr_info))
	{
		gw_set_errcode(KE_UNKNOWN_ERR);
		return KGetErrorNo();
	}
	// 获得服务器信息
	if(gw_get_server_info(&gs_svr_info))
	{
		gw_set_errcode(KE_READ_LOCAL_MAC);
		return KGetErrorNo();
	}
	return 0;
}

int API_EXPORT KCustomerInfo(const char szStuempNo[21], CustomerInfo *CutInfo)
{
	char msg[512] = "";
	char szDeptNo[11] = "";
	int ret = 0;
	gw_init_errcode();

	CDRTPHelper drtp(gs_svr_info.drtp_ip, gs_svr_info.drtp_port, gs_svr_info.drtp_mainfunc, 0);
	ST_PACK* data;
	drtp.SetRequestHeader(841605, 1);
	//	drtp.AddField(F_LCERT_CODE, gs_svr_info.svrid);
	//	drtp.AddField(F_SCUST_LIMIT, gs_svr_info.dyn_key);
	drtp.AddField(F_SCUST_AUTH2, szStuempNo);

	if(drtp.Connect())
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.SendRequest(3000))
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.GetReturnCode()) 
	{
		gw_parse_drpt_return_code(drtp.GetReturnCode());
		sprintf(msg,"%d:%s",drtp.GetReturnCode(),drtp.GetReturnMsg().c_str());
		gw_set_err_msg(msg);
	}
	else if(drtp.HasMoreRecord())
	{
		data = drtp.GetNextRecord();
		// 客户信息
		STR_COPY(CutInfo->szName,data->sname);
		STR_COPY(CutInfo->szStuempNo,data->scust_auth2);
		STR_COPY(CutInfo->szSex,data->smarket_code);
		STR_COPY(CutInfo->szManId,data->scust_auth);
		STR_COPY(szDeptNo,data->scust_no);
		CutInfo->nCustomerId = data->lvol1;
		STR_COPY(CutInfo->szTel,data->sphone);
		STR_COPY(CutInfo->szClassDeptName,data->scard1);
		if (KGetDeptNameFromDeptNo(szDeptNo, CutInfo->szClassDeptName))
			STR_COPY(CutInfo->szClassDeptName,"");

		if (ret = KGetMendFeeTypeFromCutId(CutInfo->nCustomerId, &(CutInfo->nMendFeeType)))
			return ret;

		return 0;
	}
	else
	{
		gw_set_errcode(KE_QUERY_ERROR);
	}
	return KGetErrorNo();
}

int API_EXPORT KGetCurBalance(const char szStuempNo[21], double *dCurBalance)
{
	//char msg[512] = "";
	gw_init_errcode();

	CDRTPHelper drtp(gs_svr_info.drtp_ip, gs_svr_info.drtp_port, gs_svr_info.drtp_mainfunc, 0);
	ST_PACK* data;
	drtp.SetRequestHeader(847170, 1);
	drtp.AddField(F_SCUST_AUTH, szStuempNo);

	if(drtp.Connect())
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.SendRequest(3000))
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.GetReturnCode()) 
	{
		gw_parse_drpt_return_code(drtp.GetReturnCode());
		sprintf(msg,"%d:%s",drtp.GetReturnCode(),drtp.GetReturnMsg().c_str());
		gw_set_err_msg(msg);
	}
	else if(drtp.HasMoreRecord())
	{
		data = drtp.GetNextRecord();
		// 客户信息
		*dCurBalance = data->damt4;
		return 0;
	}
	else
	{
		gw_set_errcode(KE_QUERY_ERROR);
	}
	return KGetErrorNo();
}

//int API_EXPORT KGetTradeSerial(int nDeviceId, TradeSerial Serial[], int *nNextFlag, int nInputFlag, const char szSerialYear[5], const char szSerialMonth[3], const char szBeginDay[3], const char szEndDay[3])
int API_EXPORT KGetTradeSerial(int nDeviceId, TradeSerial Serial[], int *nNextFlag, int nInputFlag, char szBeginDate[11], char szEndDate[11])
{
	char msg[512] = "";
	int nStrPos = 0;
	int nCount = 0;
	BOOL bHasRecordFlag = FALSE;
	/*
	nStrPos = sprintf(szBeginDate, "%s", szSerialYear);
	nStrPos += sprintf(szBeginDate + nStrPos, "%s", szSerialMonth);
	sprintf(szBeginDate + nStrPos, "%s", szBeginDay);

	nStrPos = sprintf(szEndDate, "%s", szSerialYear);
	nStrPos += sprintf(szEndDate + nStrPos, "%s", szSerialMonth);
	sprintf(szEndDate + nStrPos, "%s", szEndDay);
	*/

	gw_init_errcode();
	
//	CDRTPHelper drtp(gs_svr_info.drtp_ip, gs_svr_info.drtp_port, gs_svr_info.drtp_mainfunc, 0);
	ST_PACK* data;
	getSerialDrtp.GlobalHelper(gs_svr_info.drtp_ip, gs_svr_info.drtp_port, gs_svr_info.drtp_mainfunc, 0);
	
	if (nInputFlag == -999)
	{
		getSerialDrtp.SetRequestHeader(847171, 1);
		getSerialDrtp.AddField(F_LVOL5, nDeviceId);
		getSerialDrtp.AddField(F_SCUST_NO, szBeginDate);
		getSerialDrtp.AddField(F_SCUST_NO2, szEndDate);
		
		if (getSerialDrtp.Connect())
		{
			gw_set_errcode(KE_CONNECT_ERROR);
			return KGetErrorNo();
		}
		
		if (getSerialDrtp.SendRequest(3000))
		{
			gw_set_errcode(KE_CONNECT_ERROR);
			return KGetErrorNo();
		}
	    
		if (getSerialDrtp.GetReturnCode())
		{
			gw_parse_drpt_return_code(getSerialDrtp.GetReturnCode());
			sprintf(msg,"%d:%s",getSerialDrtp.GetReturnCode(),getSerialDrtp.GetReturnMsg().c_str());
			gw_set_err_msg(msg);
			return KGetErrorNo();
		}
	}
	
	if (nInputFlag == 1)
	{
		if (getSerialDrtp.Connect())
		{
			gw_set_errcode(KE_CONNECT_ERROR);
			return KGetErrorNo();
		}
	}
	/*
	if (getSerialDrtp.Connect())
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if (getSerialDrtp.SendRequest(3000))
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if (getSerialDrtp.GetReturnCode()) 
	{
		gw_parse_drpt_return_code(getSerialDrtp.GetReturnCode());
		sprintf(msg,"%d:%s",getSerialDrtp.GetReturnCode(),getSerialDrtp.GetReturnMsg().c_str());
		gw_set_err_msg(msg);
	}
	*/
	if (nInputFlag == -999 || nInputFlag == 1)
	{	
		bHasRecordFlag = getSerialDrtp.HasMoreRecord();

		while (bHasRecordFlag)
		{
			data = getSerialDrtp.GetNextRecord();
			// 流水信息
			Serial[nCount].nSerialNo = data->lvol0;
			Serial[nCount].nOtherSerialNo = data->lvol1;
			Serial[nCount].nSerialType = data->lvol2;
			Serial[nCount].nSerialState = data->lvol3;
			STR_COPY(Serial[nCount].szOperateDate,data->sorder1);
			STR_COPY(Serial[nCount].szOperateTime,data->sdate1);
			STR_COPY(Serial[nCount].szCollectDate,data->sorder2);
			STR_COPY(Serial[nCount].szCollectTime,data->sdate2);
			STR_COPY(Serial[nCount].szEnteractDate,data->sserial0);
			STR_COPY(Serial[nCount].szEnteractTime,data->sdate3);
			Serial[nCount].nMainDeviceId = data->lvol4;
			Serial[nCount].nDeviceId = data->lvol5;
			STR_COPY(Serial[nCount].szDevphy999Id,data->semp_no);
			STR_COPY(Serial[nCount].szShowId,data->sserial1);
			Serial[nCount].nCardId = data->lvol6;
			Serial[nCount].nPurseId = data->lvol7;
			Serial[nCount].nTradeCount = data->lvol8;
			Serial[nCount].dTradeFee = data->damt0;
			Serial[nCount].dInBalance = data->damt1;
			Serial[nCount].dOutBalance = data->damt2;
			Serial[nCount].dDepositFee = data->damt3;
			Serial[nCount].dInFee = data->damt4;
			Serial[nCount].dCostFee = data->damt5;
			Serial[nCount].dBoardFee = data->damt6;
			Serial[nCount].nCoustomerId = data->lvol9;
			STR_COPY(Serial[nCount].szOperCode,data->sserial2);
			STR_COPY(Serial[nCount].szOutAccountId,data->sstation0);
			STR_COPY(Serial[nCount].szInAccountId,data->sstation1);
			Serial[nCount].nSysId = data->lvol10;
			Serial[nCount].nTmark = data->lvol12;
			Serial[nCount].nErrCode = data->lsafe_level2;
			Serial[nCount].nReviseSerialNo = data->lwithdraw_flag;
			nCount++;
			bHasRecordFlag = getSerialDrtp.HasMoreRecord();	
			if (nCount % 15 == 0)
			{
				break;
			}	
		}
		*nNextFlag = getSerialDrtp.GetNextPacketFlag();	
		return 0;		
	}
	else if (nInputFlag == 0)
	{
		return 0;
	}
	else
	{
		gw_set_errcode(KE_QUERY_ERROR);
	}

	return KGetErrorNo();
}

int API_EXPORT KGetDeptNameFromDeptNo(const char szClassDeptNo[10 + 1], char szClassDeptName[150 + 1])
{
	char msg[512] = "";
	gw_init_errcode();

	CDRTPHelper drtp(gs_svr_info.drtp_ip, gs_svr_info.drtp_port, gs_svr_info.drtp_mainfunc, 0);
	ST_PACK* data;
	drtp.SetRequestHeader(842004, 1);
	drtp.AddField(F_SCUST_NO, szClassDeptNo);

	if(drtp.Connect())
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.SendRequest(3000))
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.GetReturnCode()) 
	{
		gw_parse_drpt_return_code(drtp.GetReturnCode());
		sprintf(msg,"%d:%s",drtp.GetReturnCode(),drtp.GetReturnMsg().c_str());
		gw_set_err_msg(msg);
	}
	else if(drtp.HasMoreRecord())
	{
		data = drtp.GetNextRecord();
		// 客户信息
//		STR_COPY(szClassDeptName,data->ssectypes);
		strncpy(szClassDeptName, data->ssectypes, sizeof(BYTE) * 150);
		return 0;
	}
	else
	{
		gw_set_errcode(KE_QUERY_ERROR);
	}
	return KGetErrorNo();
}

int API_EXPORT KGetMendFeeTypeFromCutId(int nCustomerId, int *nMendFeeType)
{
	char msg[512] = "";
	gw_init_errcode();

	CDRTPHelper drtp(gs_svr_info.drtp_ip, gs_svr_info.drtp_port, gs_svr_info.drtp_mainfunc, 0);
	ST_PACK* data;
	drtp.SetRequestHeader(848007, 1);
	drtp.AddField(F_LVOL2, nCustomerId);

	if(drtp.Connect())
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.SendRequest(3000))
	{
		gw_set_errcode(KE_CONNECT_ERROR);
	}
	else if(drtp.GetReturnCode()) 
	{
		gw_parse_drpt_return_code(drtp.GetReturnCode());
		sprintf(msg,"%d:%s",drtp.GetReturnCode(),drtp.GetReturnMsg().c_str());
		gw_set_err_msg(msg);
	}
	else if(drtp.HasMoreRecord())
	{
		data = drtp.GetNextRecord();
		*nMendFeeType = data->lvol6;
		return 0;
	}
	else
	{
		gw_set_errcode(KE_QUERY_ERROR);
	}
	return KGetErrorNo();
}