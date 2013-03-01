#include "CIniFile.h"
#include "DRTPHelper.h"
#include "gwdef.h"
#include "netutil.h"

#define STR_COPY(d,s) strncpy(d,s,sizeof((d)) - 1);

static int gs_errno = 0;
static char gs_errmsg[512] = "";

typedef struct _tagSvrInfo
{
	int svrid;					// ������ID��
	char ip[16];				// ����IP��ַ
	char mac[18];				// ����MAC��ַ
	char dyn_key[33];			// ���浽������̬��Կ

	char drtp_ip[16];			// drtp��IP��ַ
	int	 drtp_port;				// drtp���Ӷ˿�
	int	 drtp_mainfunc;			// drtp�����ܺ�
	int	 drtp_request;			// ��������
	unsigned long tick_count;   // ǩ������
}SvrInfo_t;

#define TICK_INTERVAL	1000

#define TEST_TICK_CNT(svr) \
{ unsigned long _tick = svr.tick_count;svr.tick_count = GetTickCount();\
if(svr.tick_count - _tick < TICK_INTERVAL) { gs_errno = KE_REQUEST_INTERVAL; return -1;} \
}

static SvrInfo_t gs_svr_info;

struct _tagErrMsgTable
{
	int code;
	const char* msg;
}gs_errmsg_tbl[] = 
{
	{KE_SUCCESS,"�ɹ�"},
	{KE_PERMISSION_DENY,"�������¼,����IP��MAC��ַ��Ϣ����ȷ"},
	{KE_CONNECT_ERROR,"�������ӵ�Ӧ�÷�����,�����������"},
	{KE_REQ_FUNC_NOT_EXISTS,"�����ܺŲ�����"},
	{KE_QUERY_ERROR,"��ѯʧ��, ���ܷ�����æ"},
	{KE_NOT_LOGIN,"����ʧ��,��Ҫ���µ�¼"},
	{KE_READ_LOCAL_MAC,"��ȡ����MAC��ַ����"},
	{KE_CARD_NO_EXIST,"ָ���Ŀ�������"},
	{KE_REQUEST_INTERVAL,"����Ƶ��̫��"},
	{-1,NULL}
};

#define DRTP_RT_NO_FUNCTION 9998

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
	gs_errno = 0;
	memset(gs_errmsg,0,sizeof gs_errmsg);
}

BOOL WINAPI DllMain(HANDLE, DWORD, LPVOID)
{
	gw_init_errcode();
	DrtpInit(&gs_errno,gs_errmsg);
	memset(&gs_svr_info,0,sizeof gs_svr_info);
	return TRUE;
}


int WINAPI KLogin()
{
	gw_init_errcode();
	TEST_TICK_CNT(gs_svr_info)
	// ��ȡ��������
	if(gw_read_local_conf(&gs_svr_info))
	{
		gs_errno = KE_UNKNOWN_ERR;
		return gs_errno;
	}
	// ��÷�������Ϣ
	if(gw_get_server_info(&gs_svr_info))
	{
		gs_errno = KE_READ_LOCAL_MAC;
		return gs_errno;
	}
	CDRTPHelper drtp(gs_svr_info.drtp_ip,gs_svr_info.drtp_port,gs_svr_info.drtp_mainfunc);
	ST_PACK* data;
	drtp.SetRequestHeader(950001);
	drtp.AddField(F_SCUST_LIMIT,gs_svr_info.ip);
	drtp.AddField(F_SCUST_LIMIT2,gs_svr_info.mac);
	if(drtp.Connect())
	{
		gs_errno = KE_CONNECT_ERROR;
	}
	else if(drtp.SendRequest(3000))
	{
		gs_errno = KE_CONNECT_ERROR;
	}
	else if(drtp.GetReturnCode())
	{
		gs_errno = KE_QUERY_ERROR;
		STR_COPY(gs_errmsg,drtp.GetReturnMsg().c_str());
	}
	else if(drtp.HasMoreRecord())
	{
		data = drtp.GetNextRecord();
		STR_COPY(gs_svr_info.dyn_key,data->scust_limit);
		gs_svr_info.svrid = data->lvol0;
	}
	else
	{
		gs_errno = KE_PERMISSION_DENY;
	}	
	return gs_errno;
}

void gw_parse_drpt_return_code(int code)
{
	switch(code)
	{
	case DRTP_RT_NO_FUNCTION:
		gs_errno = KE_REQ_FUNC_NOT_EXISTS;
		break;
	case 9999:
		gs_errno = KE_QUERY_ERROR;
		break;
	default:
		gs_errno = KE_UNKNOWN_ERR;
		break;
	}
}

int WINAPI KGetErrorNo()
{
	return gs_errno;
}

void WINAPI KGetErrorMsg(char msg[512])
{
	int i = 0;
	if(strlen(gs_errmsg) > 0)
	{
		strcpy(msg,gs_errmsg);
		return;
	}
	while(gs_errmsg_tbl[i].msg != NULL)
	{
		if(gs_errmsg_tbl[i].code == gs_errno)
		{
			strcpy(msg,gs_errmsg_tbl[i].msg);
			return;
		}
		++i;
	}
	strcpy(msg,"δ֪����");
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
	gw_init_errcode();
	TEST_TICK_CNT(gs_svr_info)
	if(gs_svr_info.svrid == 0)
	{
		gs_errno = KE_NOT_LOGIN;
		return gs_errno;
	}
	CDRTPHelper drtp(gs_svr_info.drtp_ip,gs_svr_info.drtp_port,gs_svr_info.drtp_mainfunc);
	ST_PACK* data;
	drtp.SetRequestHeader(gs_svr_info.drtp_request);
	drtp.AddField(F_LCERT_CODE,gs_svr_info.svrid);
	drtp.AddField(F_SCUST_LIMIT,gs_svr_info.dyn_key);
	drtp.AddField(F_SDATE0,phyid);
	drtp.AddField(F_SNAME,cardno);
	drtp.AddField(F_SNAME2,stuempno);
	
	if(drtp.Connect())
	{
		gs_errno = KE_CONNECT_ERROR;
	}
	else if(drtp.SendRequest(3000))
	{
		gs_errno = KE_CONNECT_ERROR;
	}
	else if(drtp.GetReturnCode()) 
	{
		gw_parse_drpt_return_code(drtp.GetReturnCode());
		sprintf(gs_errmsg,"%d:%s",drtp.GetReturnCode(),drtp.GetReturnMsg().c_str());
	}
	else if(drtp.HasMoreRecord())
	{
		data = drtp.GetNextRecord();
		tCard->cardid = data->lvol0;
		STR_COPY(tCard->name,data->snote);
		STR_COPY(tCard->cardno,data->sname);
		STR_COPY(tCard->stuemp_no,data->sname2);
		STR_COPY(tCard->phyid,data->sdate0);

		// �û���Ϣ
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
		gs_errno = KE_QUERY_ERROR;
	}
	return gs_errno;
}

int API_EXPORT KGetLossOfSthByStuempNo(const char stuempno[21], const char password[7], int validate_pwd)
{
	gw_init_errcode();
	TEST_TICK_CNT(gs_svr_info)
	if (gs_svr_info.svrid == 0)
	{
		gs_errno = KE_NOT_LOGIN;
		return gs_errno;
	}
	CDRTPHelper drtp(gs_svr_info.drtp_ip, gs_svr_info.drtp_port, gs_svr_info.drtp_mainfunc);
	ST_PACK *data;
	drtp.SetRequestHeader(847195);				// ������ʧ
	drtp.AddField(F_LCERT_CODE, gs_svr_info.svrid);
	drtp.AddField(F_SCUST_LIMIT, gs_svr_info.dyn_key);
	drtp.AddField(F_SCUST_AUTH, stuempno);
	drtp.AddField(F_SPHONE, password);
	drtp.AddField(F_LVOL12, validate_pwd);
	if (drtp.Connect())
	{
		gs_errno == KE_CONNECT_ERROR;
	}
	else if (drtp.SendRequest(3000))
	{
		gs_errno == KE_CONNECT_ERROR;
	}
	else if (drtp.GetReturnCode())
	{
		gw_parse_drpt_return_code(drtp.GetReturnCode());
		sprintf(gs_errmsg, "%d%s", drtp.GetReturnCode, drtp.GetReturnMsg().c_str());
	}
	return gs_errno;
}
