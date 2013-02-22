#include "StdAfx.h"
#include "CIniFile.h"
#include "DRTPHelper.h"
#include "netutil.h"
#include "ReadCardInfo.h"
#include "ReadCardInfoDlg.h"

#define  STR_COPY(d, s) strncpy(d, s, sizeof((d)) - 1)

static int gs_errno = 0;
static char gs_errmsg[512] = "";
// д���ľ�̬��Կ, ���͵���������û�ȡ���ݵ���Կ
static char StaticSendPwd[32] = "";		

typedef struct _tagSvrInfo
{
	int svrid;					// ������ID��
	char ip[16];				// ����IP��ַ
	char mac[18];				// ����MAC��ַ
	char dyn_key[33];			// ���浽�����Ķ�̬��Կ 
	char drtp_ip[16];			// drtp��IP��ַ
	int drtp_port;				// drtp���Ӷ˿�
	int	drtp_mainfunc;			// drtp�����ܺ�
	int drtp_request;			// ��������
	unsigned long tick_count;   // ǩ������
}SvrInfo_s;

#define TICK_INTERVAL  1000

#define TEST_TICK_CNT(svr) \
{unsigned long _tick = svr.tick_count;svr.tick_count = GetTickCount();\
if(svr.tick_count - _tick < TICK_INTERVAL){gs_errno = KE_REQUEST_INTERVAL; return -1}\
}

static SvrInfo_s gs_svr_info;

struct _tagErrMsgTable
{
	int code;
	const char* msg;
}gs_errmsg_tbl[] = 
{
	{KE_SUCCESS, "�ɹ�"},
	{KE_PERMISSION_DENY, "�������½, ����IP��Ϣ��MAC��ַ��Ϣ����ȷ"},
	{KE_CONNECT_ERROR, "�������ӵ�Ӧ�÷�����,�����������"},
	{KE_QUERY_ERROR, "��ѯʧ��, ���ܷ�����æ"},
	{KE_NOT_LOGIN, "����ʧ��, ��Ҫ���µ�½"},
	{KE_READ_LOCAL_MAC, "��ȡ����MAC��ַ����"},
	{KE_CARD_NO_EXIST, "ָ���Ŀ�������"},
	{KE_REQUEST_INTERVAL, "����Ƶ��̫��"},
	{-1, NULL}
};

#define DRTP_RT_NO_FUNCTION 9998

// ��ȡ��������Ϣ
static int gw_get_server_info(SvrInfo_s *svr)
{
	std::string mac;
	std::vector<std::string> ip_list;
	std::vector<std::string>::const_iterator i;
	KSGNetUtil::GetLocalIP(ip_list);
/*
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
*/
	return 0;
}

// ��ȡ��������
static int gw_read_local_conf(SvrInfo_s *svr)
{
	char fullpath[1128] = "";
	int len = GetModuleFileName(NULL, fullpath, 1024);
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
	memset(gs_errmsg, 0, sizeof(gs_errmsg));
}

// ��ô�����
int KGetErrorNo()
{
	return gs_errno;
}

// ��ȡ������Ϣ
void KGetErrorMsg(char msg[512])
{
	int i = 0;
	if (strlen(gs_errmsg) > 0)
	{
		strcpy(msg, gs_errmsg);
		return;
	}
	while (gs_errmsg_tbl[i].msg != NULL)
	{
		if (gs_errmsg_tbl[i].code == gs_errno)
		{
			strcpy(msg, gs_errmsg_tbl[i].msg);
			return;
		}
		++i;
	}
	strcpy(msg, "δ֪����");
}

// ͨ���������Լ���Կ��ȡѧ����
int KGetStuempNoByPhyid(const char phyid[9], char stuemp_no[21])
{
	gw_init_errcode();
	/*
	if (gs_svr_info.svrid == 0)
	{
		gs_errno = KE_NOT_LOGIN;
		return gs_errno;
	}
	*/
	CDRTPHelper drtp(gs_svr_info.drtp_ip,gs_svr_info.drtp_port,gs_svr_info.drtp_mainfunc);
	ST_PACK *data;
	drtp.SetRequestHeader(gs_svr_info.drtp_request);
	//drtp.AddField(F_LCERT_CODE, gs_svr_info.svrid);
	drtp.AddField(F_SCUST_LIMIT, gs_svr_info.dyn_key);
	drtp.AddField(F_SDATE0, phyid);
	if (drtp.Connect())
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
	else if (drtp.HasMoreRecord()) 
	{
		data = drtp.GetNextRecord();
		strncpy(stuemp_no, data->sname2, sizeof(data->sname2) - 1);
	}
	else
	{
		gs_errno = KE_QUERY_ERROR;
	}
	return gs_errno;
}

// ʹ�������Ų�ѯ����Ϣ
int KGetCardInfoByPhyId(const char phyid[9], CardInfo_t* tCard)
{
	int ret = 0;
	gw_init_errcode();

	CDRTPHelper drtp(gs_svr_info.drtp_ip,gs_svr_info.drtp_port,gs_svr_info.drtp_mainfunc);
	ST_PACK* data;
	drtp.SetRequestHeader(847173, 1);
	//	drtp.AddField(F_LCERT_CODE, gs_svr_info.svrid);
	//	drtp.AddField(F_SCUST_LIMIT, gs_svr_info.dyn_key);
	drtp.AddField(F_SBANK_ACC, phyid);

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
		// �ͻ���Ϣ
		STR_COPY(tCard->card_state, data->sbank_code);
		return 0;
	}
	else
	{
		gs_errno = KE_QUERY_ERROR;
	}

	return gs_errno;
}

int KGetCardInfoByDealCardId(int card_id, CardInfo_t* tCard)
{
	int ret = 0;
	gw_init_errcode();
	
	CDRTPHelper drtp(gs_svr_info.drtp_ip,gs_svr_info.drtp_port,gs_svr_info.drtp_mainfunc);
	ST_PACK* data;
	drtp.SetRequestHeader(847173, 1);
	//	drtp.AddField(F_LCERT_CODE, gs_svr_info.svrid);
	//	drtp.AddField(F_SCUST_LIMIT, gs_svr_info.dyn_key);
	drtp.AddField(F_LVOL0, card_id);
	
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
		// �ͻ���Ϣ
		STR_COPY(tCard->card_state, data->sbank_code);
		return 0;
	}
	else
	{
		gs_errno = KE_QUERY_ERROR;
	}
	
	return gs_errno;
}

// δ��ʵ��
int KGetCardInfoByCardNo(const char cardno[21],CardInfo_t* tCard)
{
	return -1;
}

// δ��ʵ��
int KGetCardInfoByStuempNo(const char stuempno[21],CardInfo_t* tCard)
{
	return -1;
}

// ��ʼ��ͨ����Ϣ�ʹ�����Ϣ
BOOL KInitFunc()
{
	gw_init_errcode();
	DrtpInit(&gs_errno, gs_errmsg);
	memset(&gs_svr_info, 0, sizeof(gs_svr_info));
	// ��������һ����Կ
	strcpy(StaticSendPwd, "4343232323231111");
	return TRUE;
}

// �ӷ�������ȡ��Կ
int KRecPwdFromSvr()
{
	gw_init_errcode();
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
	/*
	if (gs_svr_info.svrid == 0)
	{
		gs_errno = KE_NOT_LOGIN;
		return gs_errno;
	}
	*/
	CDRTPHelper drtp(gs_svr_info.drtp_ip,gs_svr_info.drtp_port,gs_svr_info.drtp_mainfunc);
	ST_PACK *data;
	drtp.SetRequestHeader(950006);
	drtp.AddField(F_SCUST_LIMIT, StaticSendPwd);
	drtp.AddField(F_SPHONE, gs_svr_info.ip);
	drtp.AddField(F_SPHONE2, gs_svr_info.mac);
	drtp.AddField(F_LCERT_CODE, 0);
	drtp.AddField(F_LVOL0, 2006);
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
	else if (drtp.HasMoreRecord())
	{
		data = drtp.GetNextRecord();
		STR_COPY(gs_svr_info.dyn_key, data->scard0);
		//////////////////////////////////////////////////////////////////////////
		// ������Կ�Ա�ӿ������ȡ��Ϣ	
		Load_WorkKey(gs_svr_info.dyn_key);
		//////////////////////////////////////////////////////////////////////////
	//	gs_svr_info.svrid = data->lvol0;
	}
	else
	{
		gs_errno = KE_QUERY_ERROR;
	}
	return gs_errno;
}




















