#include "ksykt.h"
#include "yktclt.h"
#include "ksykt_def.h"
#include "carddll_def.h"
#include "logfile.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <list>
#include <fstream>
#include <string>
#include <time.h>

#define MAX_DEVICE_COUNT 30

#define DEV_FLAG_LOGIN 0x01
#define DEV_FLAG_CONSUM 0x02
#define DEV_FLAG_ADD_MONEY 0x04

#define DEV_TERM_ONLINE 0x01
#define DEV_TERM_OFFLINE 0x02

#define FUNC_ENROLL 849001
#define FUNC_QUERY_USER_INFO 849002
#define FUNC_LOST_CARD 847318
#define FUNC_CONSUME 847316
#define FUNC_CONSUME_CONFIRM 847317
#define FUNC_READ_CARD 847173
#define FUNC_READ_CUST_INFO 841605
#define FUNC_READ_ACCOUNT 847170
#define FUNC_READ_DICT 820502

/*
��Ӧ��״̬
*/
// ����
#define ACC_FLAG_OK '0'
//
#define ACC_FLAG_SET '1'
#define ACC_FLAG_LOGOUT '2'

typedef struct
{
	int device_id;	// �豸ID
	int sys_id;		// ��ϵͳ��
	unsigned short term_no;	// �ն˻���
	ULONG maxjnl;		// �ն���ˮ��
	int purse_no;		// �ն˽���Ǯ����
	int day_trade_limit; // �ս����ۼ��޶�
	int trade_limit_per_cnt; // ���ν����޶�
	int flag;				// ��־
	int is_online;			// �Ƿ�����
	char oper_code[11];		// ����Ա
}conn_dev_conf_t;

typedef struct
{
	int device_count;
	conn_dev_conf_t devices[MAX_DEVICE_COUNT];
}sys_devices_t;

typedef struct
{
	int dept_id;
	char dept_code[4];
}dept_id_code_t;

typedef std::list<dept_id_code_t> DEPT_ID_CODE_LIST_TYPE;

DCLR_DLLFUNC(int, encrypt_des, (unsigned char* key, long keylen, unsigned char *data, short datalen, unsigned char *Des_result));
DCLR_DLLFUNC(int, dencrypt_des, (unsigned char* key, long keylen, unsigned char *data, short datalen, unsigned char *Des_result));
DCLR_DLLFUNC(int, encrypt_work_key, (unsigned char* text, unsigned char* mtext));
// CardDll ��غ���
DEF_DLLFUNC(ConnectMF);
DEF_DLLFUNC(CloseMF);
DEF_DLLFUNC(Load_WorkKey);
DEF_DLLFUNC(ReadCardInfo);
DEF_DLLFUNC(ReadSerial);
DEF_DLLFUNC(SMT_ReadPacketInfo);
DEF_DLLFUNC(ReadCardNO);
DEF_DLLFUNC(SMT_PacketSetMoney);
DEF_DLLFUNC(ControlBuzzer);
DEF_DLLFUNC(SMT_GetPacketInfo);
DEF_DLLFUNC(encrypt_des);
DEF_DLLFUNC(dencrypt_des);
DEF_DLLFUNC(Load_Dll);
DEF_DLLFUNC(ReadCardPwd);
DEF_DLLFUNC(HaltCard);
DEF_DLLFUNC(ReadCardInfo2);
DEF_DLLFUNC(SetCardMainKey);
DEF_DLLFUNC(SMT_ReadAuthorWorkKeyAndFlag);
DEF_DLLFUNC(encrypt_work_key);


// �豸�б�
static sys_devices_t g_devices;
// �����ܺ�
#if 0
static int g_main_func = 9000;
#else 
static int g_main_func = 6000;
#endif

// �����Ƿ��
static int g_com_open = 0;
// ������Կ
static char g_workkey[33] = "";
static unsigned char g_hex_workhey[8] = "";
// ·��
static char g_module_path[1024] = "";
// ���Ŵ���
static DEPT_ID_CODE_LIST_TYPE g_dept_code;
// log
static KSYkt_Log_Writer g_logger("ksykt");

static HINSTANCE g_carddll_module = NULL;
static HINSTANCE g_des_module = NULL;

static char g_ErrMsg[1024] = "";
static int g_ErrCode = 0;
static void SetLastErr(int err_code, char* format, ...)
{
	va_list arglist;
	char buffer[1024] = "";
	va_start (arglist, format);
	vsprintf(buffer, format, arglist);
	va_end (arglist);
	strcpy(g_ErrMsg, buffer);
	g_ErrCode = err_code;
	g_logger.writelog("Error[%d] %s", g_ErrCode, g_ErrMsg);
}
//ȡ������Ϣ
void CALLAPI GetLastErr(int* pErrCode, char *ErrMsg)
{
	*pErrCode = g_ErrCode;
	strcpy(ErrMsg, g_ErrMsg);
}

static int do_load_carddll()
{
	char dll_path[1024] = "";
	strcpy(dll_path, g_module_path);
	strcat(dll_path, "CardDLL.dll");
	if ((g_carddll_module = LoadLibrary(dll_path)) == NULL)
	{
		g_logger.writelog("���� carddll ʧ��");
		return -1;
	}
	LOAD_DLLFUNC(g_carddll_module, ConnectMF);
	LOAD_DLLFUNC(g_carddll_module, CloseMF);
	LOAD_DLLFUNC(g_carddll_module, Load_WorkKey);
	LOAD_DLLFUNC(g_carddll_module, ReadCardInfo);
	LOAD_DLLFUNC(g_carddll_module, ReadSerial);
	LOAD_DLLFUNC(g_carddll_module, SMT_ReadPacketInfo);
	LOAD_DLLFUNC(g_carddll_module, ReadCardNO);
	LOAD_DLLFUNC(g_carddll_module, SMT_PacketSetMoney);
	LOAD_DLLFUNC(g_carddll_module, ControlBuzzer);
	LOAD_DLLFUNC(g_carddll_module, SMT_GetPacketInfo);
	LOAD_DLLFUNC(g_carddll_module, Load_Dll);
	LOAD_DLLFUNC(g_carddll_module, ReadCardPwd);
	LOAD_DLLFUNC(g_carddll_module, ReadCardInfo2);
	LOAD_DLLFUNC(g_carddll_module, SetCardMainKey);
	LOAD_DLLFUNC(g_carddll_module, SMT_ReadAuthorWorkKeyAndFlag);
	LOAD_DLLFUNC(g_carddll_module, HaltCard);
	Load_Dll();
	g_logger.writelog("���� carddll �ɹ�");

	strcpy(dll_path, g_module_path);
	strcat(dll_path, "desdll.dll");
	if ((g_des_module = LoadLibrary("desdll.dll")) == NULL)
	{
		g_logger.writelog("���� desdll ʧ��");
		return -1;
	}
	LOAD_DLLFUNC(g_des_module, encrypt_des);
	LOAD_DLLFUNC(g_des_module, dencrypt_des);
	LOAD_DLLFUNC(g_des_module, encrypt_work_key);

	g_logger.writelog("���� desdll �ɹ�");
	return 0;
}

typedef unsigned short uint16;

static const unsigned int  crc16_tab[256] =
{
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
	0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
	0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
	0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
	0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
	0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
	0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
	0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
	0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
	0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
	0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
	0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
	0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
	0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
	0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
	0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
	0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
	0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
	0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
	0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
	0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
	0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
	0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

uint16  GenerateCRC16(const unsigned char *pBuf, uint16 len)
{
	uint16 crc;
	unsigned char b, da;
	uint16 charcnt;

	crc = 0;
	charcnt = 0;
	while (len--)
	{
		da = (unsigned char)(crc / 256);			/* ��8λ������������ʽ�ݴ�CRC�ĸ�8λ */
		crc <<= 8;						/* ����8λ���൱��CRC�ĵ�8λ���� */
		b = pBuf[charcnt];				// ���ƽ������ֽ�ֵ
		crc ^= crc16_tab[da ^ b];		/* ��8λ�͵�ǰ�ֽ���Ӻ��ٲ����CRC ���ټ�����ǰ��CRC */
		charcnt++;
	}

	return crc;
}

static bool load_dept_code_def()
{
	std::string dept_file_name(g_module_path);
	dept_file_name += "deptcode.txt";
	std::ifstream dept_file(dept_file_name.c_str(), std::ios_base::in);
	std::string line;
	while (!dept_file.eof())
	{
		std::getline(dept_file, line);
		if (line.length() == 0)
			continue;
		int pos = line.find(',');
		if (pos > 0)
		{
			dept_id_code_t dept;
			memset(&dept, 0, sizeof dept);
			strncpy(dept.dept_code, line.substr(0, pos).c_str(), sizeof(dept.dept_code) - 1);
			dept.dept_id = atoi(line.substr(pos + 1).c_str());
			g_dept_code.push_back(dept);
		}
	}
	return true;
}

void do_get_current_time(char time_str[15])
{
	time_t curr;
	struct tm curr_tm;
	time(&curr);
	curr_tm = *localtime(&curr);
	sprintf(time_str, "%.04d%.02d%.02d%.02d%.02d%.02d", curr_tm.tm_year + 1900
	        , curr_tm.tm_mon + 1, curr_tm.tm_mday, curr_tm.tm_hour
	        , curr_tm.tm_min, curr_tm.tm_sec);

}

static int do_dept_code2id(const char *dept, int *dept_id)
{
	DEPT_ID_CODE_LIST_TYPE::const_iterator i;
	for (i = g_dept_code.begin();i != g_dept_code.end();++i)
	{
		dept_id_code_t t = *i;
		if (strcmp(t.dept_code, dept) == 0)
		{
			*dept_id = t.dept_id;
			return 0;
		}
	}
	return -1;
}

static int do_dept_id2code(int dept_id, char *dept)
{
	DEPT_ID_CODE_LIST_TYPE::const_iterator i;
	for (i = g_dept_code.begin();i != g_dept_code.end();++i)
	{
		dept_id_code_t t = *i;
		if (t.dept_id == dept_id)
		{
			strncpy(dept, t.dept_code, sizeof(t.dept_code) - 1);
			return 0;
		}
	}
	return -1;

}

static int do_create_dir(const char *dir_path)
{
	DWORD ret = GetFileAttributes(dir_path);
	if ( ret == INVALID_FILE_ATTRIBUTES )
	{
		if (!CreateDirectory(dir_path, NULL))
			return -1;
	}
	return 0;
}

static bool do_sys_init()
{
	memset(&g_devices, 0, sizeof g_devices);
	g_com_open = 0;
	memset(g_workkey, 0, sizeof g_workkey);
	DWORD len = GetModuleFileName(NULL, g_module_path, sizeof(g_module_path) - 1);

	char *pos = strrchr(g_module_path, '\\');
	len = pos - g_module_path + 1;
	g_module_path[len] = '\0';
	char log_path[1204] = "";
	sprintf(log_path, "%slogs\\", g_module_path);
	DWORD ret = GetFileAttributes(log_path);
	if ( ret == INVALID_FILE_ATTRIBUTES )
	{
		if (!CreateDirectory(log_path, NULL))
			return false;
	}
	// ����־�ļ�
	if (g_logger.openlog(log_path))
		return false;
	char xpack_path[1024] = "";
	strcpy(xpack_path, g_module_path);
	strcat(xpack_path, "cpack.dat");
	g_logger.writelog("���� xpack [%s]", xpack_path);
	KS_YKT_Clt::set_xpack_path(xpack_path);
	if (do_load_carddll())
		return false;
	if (!load_dept_code_def())
	{
		g_logger.writelog("���ز��Ŵ����ʧ��");
	}
	return true;
}

static void do_get_date_time(char date_str[9], char time_str[7])
{
	SYSTEMTIME st;
	memset(&st, 0, sizeof st);
	GetLocalTime(&st);
	sprintf(date_str, "%04u%02u%02u", st.wYear, st.wMonth, st.wDay);
	sprintf(time_str, "%02u%02u%02u", st.wHour, st.wMinute, st.wSecond);
}

static double d4u5(double in_data, int precision = 2)
{
	char format_str[20] = "";
	char value_str[40] = "";
	sprintf(format_str, "%%20.%df", precision);
	sprintf(value_str, format_str, in_data);
	return atof(value_str);
}

static void str2hex(const char *src, int len, unsigned char *hex)
{
	int i;
	for (i = 0;i < len;i += 2)
	{
		char temp[3] = "";
		strncpy(temp, src + i, 2);
		hex[i/2] = (unsigned char)strtoul(temp, NULL, 16);
	}

}
static bool g_sys_init = do_sys_init();

#define TEST_SYS_INIT do { \
		if(!g_sys_init) return ERR_TA_NOT_INIT; }while(0)

#define TEST_COM_OPEN do { \
		if(!g_com_open) return ERR_TA_CARDREADER; }while(0)

#define TEST_TERM_LOGIN do {\
		if((g_devices.devices[0].flag & DEV_FLAG_LOGIN)==0) return ERR_TA_NOT_INIT; }while(0)

#define src2des(d,s) do { \
		strncpy((char*)(d),(const char*)(s),sizeof(d)-1);}while(0)


#define PAD_STR(s) do {\
		int i = strlen(s); \
		for(;i < sizeof(s) - 1;++i) s[i] = ' ';	}while(0)

#define INIT_STR(s) do { memset(s,' ',sizeof(s)-1); s[sizeof(s)-1]='\0';}while(0)

#define _STR_CONVERT(b,l,v,t) do  \
		{ char tmp[12] = ""; strncpy(tmp,b,l); v=(##t)strtol((const char*)tmp,NULL,16); } while(0)

#define STR2INT(b,v) _STR_CONVERT(b,8,v,int)

#define STR2SHORT(b,v) _STR_CONVERT(b,4,v,short)

#define STR2BYTE(b,v) _STR_CONVERT(b,2,v,unsigned char)


static int do_find_dev_by_termno(int termno)
{
	int i;
	for (i = 0;i < g_devices.device_count;i++)
	{
		if (g_devices.devices[i].term_no == termno)
		{
			return i;
		}
	}
	return -1;
}

static int do_find_dev_by_devid(int devid)
{
	int i;
	for (i = 0;i < g_devices.device_count;i++)
	{
		if (g_devices.devices[i].device_id == devid)
		{
			return i;
		}
	}
	return -1;
}

static int do_convert_card_phyno(const unsigned char *phyno, unsigned int *dec_no)
{
	char tmp_str[20] = "";
	int i, j;
	unsigned int no;
	for (i = 0, j = 0;i < 4;i++)
	{
		//memcpy(reverse_phyno+(3-i)*2,phyno+i*2,2);
		//reverse_phyno[3-i] = phyno[i]
		j += sprintf(tmp_str + j, "%02X", phyno[3-i]);
	}
	//reverse_phyno[4] = '\0';
	//sprintf(tmp_str,"%02X%02X%02X%02X",reverse_phyno[0])
	no = strtoul((const char*)tmp_str, NULL, 16);
	if (no > 0)
	{
		*dec_no = no;
		return 0;
	}
	return -1;
}

static int do_convert_card_phyno_str(const char *phyno, unsigned int *dec_no)
{
	char reverse_phyno[9] = "";
	int i, j;
	unsigned int no, out_no;
	unsigned char *p;
	no = strtoul(phyno, NULL, 16);
	p = (unsigned char *) & no;
	for (i = 0, j = 0;i < 4;++i)
	{
		j += sprintf(reverse_phyno + j, "%02X", p[i]);
	}
	out_no = strtoul(reverse_phyno, NULL, 16);
	if (out_no > 0)
	{
		*dec_no = out_no;
		return 0;
	}
	return -1;
}

static int do_convert_card_dec_phyno(unsigned int dec_no, char *phyno)
{
	char reverse_phyno[9] = "";
	sprintf(reverse_phyno, "%08X", dec_no);
	int i;
	for (i = 0;i < 4;++i)
	{
		strncpy(phyno + i*2, reverse_phyno + (3 - i)*2, 2);
	}
	return 0;
}

static void do_card_state_to_flag(char state_id[5], char flag[16], char enableid)
{
	if (state_id[0] == '2')
		flag[1] = ACC_FLAG_LOGOUT;
	if (state_id[1] == '1')
		flag[2] = ACC_FLAG_SET;
	if (state_id[2] == '1' )
		flag[3] = ACC_FLAG_SET;
	flag[7] = ACC_FLAG_SET;
	flag[9] = (enableid == '2') ? ACC_FLAG_SET : ACC_FLAG_OK;
}

// ���
static bool do_check_file_exists(const char *FileName)
{
	FILE *fp;
	if ((fp = fopen(FileName, "r")) == NULL)
	{
		return false;
	}
	fclose(fp);
	return true;
}

BOOL CALLAPI Is_Init_OK()
{
	return (g_sys_init) ? TRUE : FALSE;
}

BOOL CALLAPI TA_Init(char *IP , short port , unsigned short SysCode,
                     unsigned short TerminalNo, bool *ProxyOffline, ULONG *MaxJnl)
{
	int ret_code, idx;
	KS_YKT_Clt clt;
	char errmsg[1024] = "";
	if (!g_sys_init)
	{
		SetLastErr(-1000, "ϵͳ��ʼ������IP[%s]Port[%d]MainFunc[%d]", IP, port, g_main_func);
		return FALSE;
	}
	port = 4000;
	/////////////////// wenjian add////////////////////////////////////////////////////////
#if 0
//	if(port>8000)

	TerminalNo = 10;
#endif
	//////////////////////////////////////////////////////////////////////////
	g_logger.writelog("ϵͳע��,����IP[%s]Port[%d]MainFunc[%d]term[%d]", IP, port, g_main_func, TerminalNo);
	if (!KS_YKT_Clt::Initialize(IP, port, g_main_func))
	{
		SetLastErr(-1001, "��ʼ��drtp����IP[%s]Port[%d]MainFunc[%d]", IP, port, g_main_func);
		return FALSE;
	}
	idx = do_find_dev_by_termno(TerminalNo);
	clt.SetIntFieldByName("lcert_code", SysCode);
	clt.SetIntFieldByName("lvol0", TerminalNo);
	if (!clt.SendRequest(FUNC_ENROLL, 10000))
	{
		clt.GetReturnMsg(errmsg);
		SetLastErr(-1002, "��������849001ʧ��IP[%s]Port[%d]MainFunc[%d][%s]"
		           , IP, port, g_main_func, errmsg);
		return FALSE;
	}
	ret_code = clt.GetReturnCode();
	if (ret_code)
	{
		SetLastErr(-1003, "��������849001����ʧ��IP[%s]Port[%d]MainFunc[%d]retcode[%d]", IP, port, g_main_func, ret_code);
		return FALSE;
	}
	if (clt.HasMoreRecord())
	{
		clt.GetNextPackage();
#if 0
		if (idx == -1)
		{
			if (g_devices.device_count >= MAX_DEVICE_COUNT)
				return FALSE;
			idx = g_devices.device_count++;
		}
#else
		idx = 0;
		g_devices.device_count = 1;
#endif
		clt.GetIntFieldByName("lvol0", &(g_devices.devices[idx].device_id));
		clt.GetIntFieldByName("lvol1", (int*)&(g_devices.devices[idx].maxjnl));
		//g_devices.devices[idx].maxjnl = 1000;
		GET_PACK_STR(clt, "scust_limit", g_workkey);
		clt.GetIntFieldByName("lvol2", &(g_devices.devices[idx].purse_no));
		clt.GetIntFieldByName("lvol3", &(g_devices.devices[idx].trade_limit_per_cnt));
		clt.GetIntFieldByName("lvol4", &(g_devices.devices[idx].day_trade_limit));
		GET_PACK_STR(clt, "scust_no", g_devices.devices[idx].oper_code);
		if (strlen(g_devices.devices[idx].oper_code) == 0)
		{
			strcpy(g_devices.devices[idx].oper_code, "system");
		}

		g_devices.devices[idx].term_no = TerminalNo;
		g_devices.devices[idx].sys_id = SysCode;
		g_devices.devices[idx].flag = DEV_FLAG_LOGIN;
		// ����
		g_devices.devices[idx].is_online = DEV_TERM_ONLINE;
		// ����������ѿ���
		int consume_flag = 0;
		clt.GetIntFieldByName("lvol5", &consume_flag);
		if (consume_flag)
		{
			g_devices.devices[idx].flag |= DEV_FLAG_CONSUM;
		}
		*MaxJnl = g_devices.devices[idx].maxjnl;
		*ProxyOffline = false;
		// ���� hex ��Կ(����)
		str2hex(g_workkey, 16, g_hex_workhey);
		if (Load_WorkKey(g_workkey))
		{
			SetLastErr(-1004, "��������849001���سɹ�������װ�ع�����Կʧ��");
			return FALSE;
		}
		g_logger.writelog("ǩ���ɹ�,termno[%d],serialno[%d]", g_devices.devices[idx].device_id
		                  , g_devices.devices[idx].maxjnl);
		return TRUE;
	}
	else
	{
		SetLastErr(-1005, "��������849001�����޼�¼");
		return FALSE;
	}

}

int CALLAPI TA_CRInit(char CardReaderType, int port, long Baud_Rate)
{
	//TEST_SYS_INIT;
	if (g_com_open)
	{
		return ERR_OK;
	}
	int ret;
	if (CardReaderType == 0)
	{
		ret = ConnectMF(100, Baud_Rate);
	}
	else
	{
		ret = ConnectMF(port + 1, Baud_Rate);
	}
	if (!ret)
	{
		g_com_open = 1;
		g_logger.writelog("�򿪶������ɹ���");
		return ERR_OK;
	}
	g_logger.writelog("�򿪶�����ʧ�ܣ�");
	return ERR_FAIL;
}

BOOL CALLAPI TA_CRClose(void)
{
	if (g_com_open)
	{
		g_com_open = 0;
		if (CloseMF())
			return FALSE;
		g_logger.writelog("�رն������ɹ���");
		return TRUE;
	}
	return TRUE;
}

int CALLAPI TA_FastGetCardNo(unsigned int *CardNo)
{
	TEST_COM_OPEN;
	int ret;
	unsigned char serial_no[8];
	ret = ReadSerial(serial_no);
	if (ret)
	{
		//SetLastErr(ERR_TA_READCARD,"�������к�ʧ��");
		return ERR_TA_READCARD;
	}

	ret = do_convert_card_phyno(serial_no, CardNo);
	if (ret)
		return ERR_TA_READCARD;
	g_logger.writelog("��ȡ�����к�[%d]", *CardNo);
	return ERR_OK;
}

int CALLAPI TA_ReadCardSimple(AccountMsg * pAccMsg)
{
	g_logger.writelog("���� TA_ReadCardSimple ����");
	TEST_COM_OPEN;
	int ret;
	TPublishCard2 card;
	memset(&card, 0, sizeof card);

	ret = ReadCardInfo2(&card);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "����ʧ�ܣ�");
		return ERR_TA_READCARD;
	}
	int cardid = atoi((char*)card.CardNo);
	if (cardid <= 0)
		return ERR_TA_READCARD;
	// TODO : �����Ÿ�ʽ
	ret = TA_FastGetCardNo(&(pAccMsg->CardNo));
	if (ret != ERR_OK)
	{
		SetLastErr(ret, "��������IDʧ��");
		return ret;
	}

	pAccMsg->AccountNo = card.cut_id;
	src2des(pAccMsg->Name, card.ucName);
	pAccMsg->Balance = card.Money;
	src2des(pAccMsg->SexNo, card.ucSexNo);
	src2des(pAccMsg->StudentCode, card.ucCardNo);
	//src2des(pAccMsg->IDNo, card.ucCertificateNo);
	src2des(pAccMsg->IDCard, card.ucCertificateNo);
	src2des(pAccMsg->ExpireDate, card.DeadLineDate + 2);
	src2des(pAccMsg->Password, card.ucPwd);
	src2des(pAccMsg->DeptCode, card.ucDepartmentNo);
	memset(pAccMsg->Flag, '0', sizeof(pAccMsg->Flag) - 1);
	pAccMsg->IsOpenInSys = 1;
	g_logger.writelog("��ȡ���ųɹ�,cut[%d]balance[%d]", card.cut_id, pAccMsg->Balance);
	return ERR_OK;
}

static int do_read_card_from_db(AccountMsg *pAccMsg)
{
	char card_phyno[9] = "";
	AccountMsg acc;
	KS_YKT_Clt clt;
	memcpy(&acc, pAccMsg, sizeof acc);
	clt.SetIntFieldByName("lvol1", pAccMsg->AccountNo);
	do_convert_card_dec_phyno(pAccMsg->CardNo, card_phyno);
	clt.SetStringFieldByName("sdate0", card_phyno);
	if (!clt.SendRequest(FUNC_QUERY_USER_INFO))
	{
		SetLastErr(ERR_COMM_FAIL, "�����̨����[%d]ʧ��", FUNC_QUERY_USER_INFO);
		return ERR_COMM_FAIL;
	}
	if (clt.GetReturnCode())
	{
		SetLastErr(ERR_FAIL, "�����̨����[%d]����,����[%d]", FUNC_QUERY_USER_INFO
		           , clt.GetReturnCode());
		return ERR_FAIL;
	}

	//memset(&acc,0,sizeof acc);
	if (clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		double bala_amt = 0.0;
		char invalid_date[9] = "";
		char state_id[5] = "";
		char id_status[2] = "";
		int card_id;

		GET_PACK_STR(clt, "semail", acc.Name);
		GET_PACK_STR(clt, "smarket_code", acc.SexNo);
		GET_PACK_STR(clt, "scust_no", acc.DeptCode);
		clt.GetIntFieldByName("lvol1", (int*)&(acc.AccountNo));
		clt.GetDoubleFieldByName("damt0", &bala_amt);
		acc.Balance = (int)d4u5(bala_amt * 100, 0);
		GET_PACK_STR(clt, "scust_auth2", acc.StudentCode);
		GET_PACK_STR(clt, "sroom_no", acc.PID);
		GET_PACK_STR(clt, "sdate0", card_phyno);
		clt.GetIntFieldByName("lvol6", &card_id);
		if (card_id > 0)
		{
			if (strlen(card_phyno) != 8)
				return -1;
		}
		else
			return -1;
		do_convert_card_phyno_str(card_phyno, &(acc.CardNo));
		GET_PACK_STR(clt, "scust_no2", invalid_date);
		strcpy(acc.ExpireDate, invalid_date + 2);
		GET_PACK_STR(clt, "sdate2", state_id);
		GET_PACK_STR(clt, "sstatus1", id_status);
		do_card_state_to_flag(state_id, acc.Flag, id_status[0]);
		*pAccMsg = acc;
		return 0;
	}
	SetLastErr(ERR_FAIL, "�����̨����[%d]�޷�������", FUNC_QUERY_USER_INFO);
	return -1;
}

int CALLAPI TA_CheckWL (unsigned int AccountNo , unsigned int CardNo , bool CheckID = true)
{
	g_logger.writelog("���� TA_CheckWL ����");
	TEST_SYS_INIT;
	int ret;
	AccountMsg acc;
	char serial_no[9] = "";
	if (AccountNo <= 0)
	{
		SetLastErr(ERR_TA_CARDNO, "�����ʺŲ���Ϊ�գ�");
		return ERR_TA_CARDNO;
	}
	acc.AccountNo = AccountNo;
	acc.CardNo = CardNo;
	memset(&acc, 0, sizeof acc);

	KS_YKT_Clt clt;
	char card_phyno[9] = "";
	char acc_no[21] = "";
	do_convert_card_dec_phyno(CardNo, card_phyno);
	clt.SetStringFieldByName("sbank_acc", card_phyno);
	sprintf(acc_no, "%d", AccountNo);
	clt.SetStringFieldByName("sholder_ac_no", acc_no);
	if (!clt.SendRequest(847173, 1000))
	{
		SetLastErr(ERR_COMM_FAIL, "����[%d]ʧ��", 847173);
		return ERR_COMM_FAIL;
	}
	else if (clt.GetReturnCode())
	{
		SetLastErr(ERR_COMM_FAIL, "����[%d]ʧ��,ret[%d]", 847173, clt.GetReturnCode());
		return ERR_FAIL;
	}
	if (clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		char state_id[5] = "";
		GET_PACK_STR(clt, "sbank_code", state_id);
		g_logger.writelog("��ѯϵͳ��״̬");
		do_card_state_to_flag(state_id, acc.Flag, '2');
		ret = ERR_OK;
	}
	return ret;
}

int CALLAPI TA_ReadCard(AccountMsg *pAccMsg, bool CheckID = true , bool CheckSub = false)
{
	g_logger.writelog("���� TA_ReadCard ����");
	AccountMsg acc;
	int ret;
	memset(&acc, 0, sizeof acc);
	TEST_COM_OPEN;
	TPublishCard2 card;
	memset(&card, 0, sizeof card);

	ret = ReadCardInfo2(&card);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "������Ϣʧ�ܣ�ret[%d]", ret);
		return ERR_TA_READCARD;
	}
	int cardid = atoi((char*)card.CardNo);
	if (cardid <= 0)
	{
		SetLastErr(ERR_TA_READCARD, "��ȡ���׿���ʧ��!");
		return ERR_TA_READCARD;
	}
	// TODO : �����Ÿ�ʽ
	ret = TA_FastGetCardNo(&(acc.CardNo));
	if (ret != ERR_OK)
	{
		SetLastErr(ret, "��������IDʧ��");
		return ret;
	}

	acc.AccountNo = card.cut_id;
	src2des(acc.Name, card.ucName);
	acc.Balance = card.Money;
	src2des(acc.SexNo, card.ucSexNo);
	src2des(acc.StudentCode, card.ucCardNo);
	src2des(acc.IDCard, card.ucCertificateNo);
	src2des(acc.ExpireDate, card.DeadLineDate + 2);
	src2des(acc.Password, card.ucPwd);
	src2des(acc.DeptCode, card.ucDepartmentNo);
	acc.IsOpenInSys = 1;
	memset(acc.Flag, '0', sizeof(acc.Flag) - 1);
	//if (CheckID)
	//{
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lvol0", cardid);
	if (!clt.SendRequest(847173, 1000))
	{
		SetLastErr(ERR_COMM_FAIL, "����[%d]ʧ��", 847173);
		return ERR_COMM_FAIL;
	}
	else if (clt.GetReturnCode())
	{
		SetLastErr(ERR_COMM_FAIL, "����[%d]ʧ��,ret[%d]", 847173, clt.GetReturnCode());
		return ERR_FAIL;
	}
	if (clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		char state_id[5] = "";
		GET_PACK_STR(clt,"sbank_code",state_id);
		g_logger.writelog("��ѯϵͳ��״̬cardid[%d]",cardid);
		do_card_state_to_flag(state_id, acc.Flag, '2');
		if( acc.Flag[1] == ACC_FLAG_LOGOUT )
			ret = ERR_TA_NOREC;
		else if(acc.Flag[2] == '1')
			ret = ERR_TA_LOST_CARD;
		else if(acc.Flag[3] == '1')
			ret = ERR_TA_FREEZE_CARD;
		else
			ret = ERR_OK;
	}
	else
		return ERR_NET_CONNECT;
	//}
	memcpy(pAccMsg, &acc, sizeof acc);
	//g_logger.writelog("��ȡ����Ϣ cut [%d] [%s] ",pAccMsg->AccountNo,pAccMsg->Password);
	return ret;
}
//int CALLAPI TA_Charge(char *pCardCharg, bool IsVerfy, short TimeOut=10)

int CALLAPI TA_Consume(CardConsume *pCardCons, bool IsVerfy, short TimeOut = 10)
{
	g_logger.writelog("����  TA_Consume ");
	TEST_TERM_LOGIN;
	TEST_COM_OPEN;
	int ret, term_idx;
	int card_id;
	int trade_serial = 0;
	double trade_amt, out_amt;
	int trade_money, out_money;
	char now_date[9] = "";
	char now_time[7] = "";
	char last_trade_date[9] = "";
	char card_serial_no[9] = "";
	char err_msg[512] = "";
	//AccountMsg acc;
	MONEY_PACK_INFO purse_info;


	//g_logger.writelog("����  TA_Consume �жϲ����Ϸ���");
	TimeOut = (TimeOut > 0 && TimeOut < 30) ? TimeOut : 10;
	TimeOut *= 1000;

	if (pCardCons->TranAmt >= 0)
	{
		return ERR_TA_TRANAMT;
	}

	term_idx = do_find_dev_by_termno(pCardCons->TerminalNo);
	if (term_idx < 0)
	{
		SetLastErr(ERR_TRN_STATION, "�ն�δ��Ȩ");
		return ERR_TRN_STATION;
	}

	if ((g_devices.devices[term_idx].flag & DEV_FLAG_CONSUM) == 0)
	{
		SetLastErr(ERR_TRN_STATION, "�ն˲���������!");
		return ERR_TRN_STATION;
	}
	if ((g_devices.devices[term_idx].is_online & DEV_TERM_ONLINE) == 0)
	{
		SetLastErr(ERR_TRN_STATION, "�ѻ��豸��������ʵʱ����!��ʹ���ѻ�����!");
		return ERR_TRN_STATION;
	}
	if ((pCardCons->TranAmt* -1) >= g_devices.devices[term_idx].trade_limit_per_cnt)
	{
		if (strlen(pCardCons->PassWord) == 0)
		{
			SetLastErr(ERR_TA_EXCEED_QUOTA, "�������ѽ�������");
			return ERR_TA_EXCEED_QUOTA;
		}
	}
	if (pCardCons->TranJnl < g_devices.devices[term_idx].maxjnl)
	{
		SetLastErr(ERR_TA_PARA, "�����ն���ˮ�Ų���ȷ,����ֵ[%d]", pCardCons->TranJnl);
		return ERR_TA_PARA;
	}
	ret = ReadCardNO(&card_id);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "��ȡ����ʧ��!");
		return ERR_TA_READCARD;
	}
	ret = ReadSerial((unsigned char*)card_serial_no);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "��ȡ��������ID��ʧ��!");
		return ERR_TA_READCARD;
	}
	memset(&purse_info, 0, sizeof purse_info);
	ret = SMT_GetPacketInfo(g_devices.devices[term_idx].purse_no, &purse_info);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "����Ǯ��ʧ��");
		return ERR_TA_READCARD;
	}
	if (purse_info.bala + pCardCons->TranAmt < 0)
	{
		return ERR_TA_TRANAMT;
	}
	// �Ƚ�����
	do_get_date_time(now_date, now_time);
	sprintf(last_trade_date, "20%02d%02d%02d", purse_info.date / 10000 % 100
	        , purse_info.date / 100 % 100, purse_info.date % 100);
	if (strcmp(last_trade_date, now_date) == 0)
	{
		if (purse_info.daybala - pCardCons->TranAmt > g_devices.devices[term_idx].day_trade_limit)
		{
			if (strlen(pCardCons->PassWord) == 0)
			{
				SetLastErr(ERR_TA_EXCEED_QUOTA, "���ۼƽ�������");
				return ERR_TA_EXCEED_QUOTA;
			}
		}
	}

	KS_YKT_Clt clt;
	// ������
	clt.SetIntFieldByName("lcert_code", 240202);
	// ���׿���
	clt.SetIntFieldByName("lvol0", card_id);
	// ��ʹ�ô���
	clt.SetIntFieldByName("lvol1", purse_info.total_cnt);
	// Ǯ����
	clt.SetIntFieldByName("lvol2", g_devices.devices[term_idx].purse_no);
	// ��ϵͳ��
	clt.SetIntFieldByName("lvol3", g_devices.devices[term_idx].sys_id);
	// �豸ID
	clt.SetIntFieldByName("lvol4", g_devices.devices[term_idx].device_id);
	// �ն���ˮ��
	clt.SetIntFieldByName("lvol5", pCardCons->TranJnl);
	// �뿨ֵ
	clt.SetDoubleFieldByName("damt0", purse_info.bala / 100.0);
	// ���׽��
	clt.SetDoubleFieldByName("damt1", (pCardCons->TranAmt * -1) / 100.0);
	// ����Ա
	clt.SetStringFieldByName("scust_no", g_devices.devices[term_idx].oper_code);
	// ����
	clt.SetStringFieldByName("semp_pwd", pCardCons->PassWord);
	// ������
	clt.SetStringFieldByName("sdate1", card_serial_no);
	// ��������
	clt.SetStringFieldByName("sdate0", now_date);
	clt.SetStringFieldByName("stime0", now_time);
	// ժҪ
	//clt.SetStringFieldByName("vsmess",pCardCons->Abstract);

	if (!clt.SendRequest(FUNC_CONSUME, TimeOut))
	{
		SetLastErr(ERR_FAIL, "������ʧ��,[%d]", FUNC_CONSUME);
		ret = ERR_FAIL;
	}
	pCardCons->RetCode = clt.GetReturnCode();
	if (clt.GetReturnCode())
	{
		clt.GetReturnMsg(err_msg);
		SetLastErr(ERR_FAIL, "������ʧ��,[%d],�ն���ˮ��[%d]������[%d][%s]"
		           , FUNC_CONSUME, pCardCons->TranJnl, clt.GetReturnCode(), err_msg);
		return ERR_FAIL;
	}
	if (clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		clt.GetIntFieldByName("lvol0", &trade_serial);
		clt.GetDoubleFieldByName("damt0", &out_amt);
		clt.GetDoubleFieldByName("damt1", &trade_amt);
		out_money = (int)d4u5(out_amt * 100.0);
		trade_money = (int)d4u5(trade_amt * 100.0);

		int curr_card_id;
		ret = ReadCardNO(&curr_card_id);
		if (ret)
		{
			SetLastErr(ERR_TA_READCARD, "�����̨���׷���д��ʧ��!");
			return ERR_TA_READCARD;
		}
		int retries = 3;
		ret = ERR_FAIL;
		while (retries-- > 0)
		{
			if (curr_card_id != card_id)
			{
				SetLastErr(ERR_TA_NOT_SAMECARD, "����д�����Ų�һ��,��̨��ˮ��[%d]", trade_serial);
				return ERR_TA_NOT_SAMECARD;
			}
			ret = SMT_PacketSetMoney(g_devices.devices[term_idx].purse_no, out_money);
			if (!ret)
				break;
		}
		if (ret)
		{
			g_logger.writelog("����д��ʧ��,��̨��ˮ��[%d]", trade_serial);
			return ERR_TA_WRITECARD;
		}
		clt.ResetHandler();
		// ������
		clt.SetIntFieldByName("lcert_code", 240202);
		// ���׿���
		clt.SetIntFieldByName("lvol0", card_id);
		// ��ʹ�ô���
		clt.SetIntFieldByName("lvol1", purse_info.time_cnt);
		// Ǯ����
		clt.SetIntFieldByName("lvol2", g_devices.devices[term_idx].purse_no);
		// ��ϵͳ��
		clt.SetIntFieldByName("lvol3", g_devices.devices[term_idx].sys_id);
		// �豸ID
		clt.SetIntFieldByName("lvol4", g_devices.devices[term_idx].device_id);
		// �ն���ˮ��
		clt.SetIntFieldByName("lvol5", pCardCons->TranJnl);
		// �뿨ֵ
		clt.SetDoubleFieldByName("damt0", purse_info.bala / 100.0);
		// ���׽��
		clt.SetDoubleFieldByName("damt1", (pCardCons->TranAmt * -1) / 100.0);
		// ����Ա
		clt.SetStringFieldByName("scust_no", g_devices.devices[term_idx].oper_code);
		// ����
		clt.SetStringFieldByName("semp_pwd", pCardCons->PassWord);
		// ��̨��ˮ��
		clt.SetIntFieldByName("lvol6", trade_serial);
		// ��������
		clt.SetStringFieldByName("sdate0", now_date);
		clt.SetStringFieldByName("stime0", now_time);
		if (clt.SendRequest(FUNC_CONSUME_CONFIRM))
		{
			if (!clt.GetReturnCode())
			{
				pCardCons->TranAmt = trade_money;
				pCardCons->BackJnl = trade_serial;
				pCardCons->CardBalance = out_money;
				g_logger.writelog("���׳ɹ������[%d]��,�����[%d], ��̨��ˮ��[%d]", trade_money
				                  , out_money, trade_serial);
				// ���߿�
				//HaltCard();
				return ERR_OK;
			}
			g_logger.writelog("����ʧ�ܣ�[%d ]����[%d],", FUNC_CONSUME_CONFIRM, clt.GetReturnCode());
			pCardCons->RetCode = clt.GetReturnCode();
		}
		else
			SetLastErr(ERR_FAIL, "����ȷ��ʧ��");
	}
	SetLastErr(ERR_FAIL, "���ѽ���ʧ��");
	return ERR_FAIL;

}
// ��ȷ��ѯ�ͻ���Ϣ
int CALLAPI TA_InqAcc(AccountMsg * pAccMsg, short TimeOut = 10)
{
	g_logger.writelog("����  TA_InqAcc ");
	TEST_SYS_INIT;
	char errmsg[512] = "";
	AccountMsg ret_acc, acc;
	int ret;
	char card_phyno[9] = "";
	TimeOut = (TimeOut > 0 && TimeOut <= 60) ?  TimeOut : 10;
	TimeOut *= 1000;
	KS_YKT_Clt clt;

	if (pAccMsg->AccountNo <= 0 && pAccMsg->CardNo <= 0 && strlen(pAccMsg->StudentCode) == 0
	        && strlen(pAccMsg->IDCard) == 0)
	{
		SetLastErr(ERR_TA_PARA, "���ò�������");
		return ERR_TA_PARA;
	}


	clt.SetIntFieldByName("lvol1", pAccMsg->AccountNo);
	if (pAccMsg->CardNo > 0)
	{
		do_convert_card_dec_phyno(pAccMsg->CardNo, card_phyno);
		clt.SetStringFieldByName("sdate0", card_phyno);
	}
	clt.SetStringFieldByName("scust_auth2", pAccMsg->StudentCode);
	clt.SetStringFieldByName("scert_no", pAccMsg->IDCard);
	if (!clt.SendRequest(FUNC_QUERY_USER_INFO))
	{
		clt.GetReturnMsg(errmsg);
		SetLastErr(ERR_COMM_FAIL, "��������ʧ��[%d][%s]", FUNC_QUERY_USER_INFO, errmsg);
		return ERR_COMM_FAIL;
	}
	if (clt.GetReturnCode())
	{
		clt.GetReturnMsg(errmsg);
		SetLastErr(ERR_FAIL, "��������ʧ��[%d],����ʧ��[%d][%s]"
		           , FUNC_QUERY_USER_INFO, clt.GetReturnCode(), errmsg);
		return ERR_FAIL;
	}
	ret = ERR_FAIL;
	memset(&ret_acc, 0, sizeof ret_acc);
	while (clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		double bala_amt = 0.0;
		char invalid_date[9] = "";
		char state_id[5] = "";
		char id_status[2] = "";
		int card_id;
		int school_id = 0;
		char school_code[5] = "";
		char dept_code[30] = "";
		memset(&acc, 0, sizeof acc);
		GET_PACK_STR(clt, "semail", acc.Name);
		GET_PACK_STR(clt, "smarket_code", acc.SexNo);

		//GET_PACK_STR(clt,"scust_no",acc.DeptCode);
		clt.GetIntFieldByName("lvol2", &school_id);
		do_dept_id2code(school_id, school_code);
		GET_PACK_STR(clt, "sphone", dept_code);
		sprintf(acc.DeptCode, "%s%s", school_code, dept_code);
		PAD_STR(acc.DeptCode);


		clt.GetIntFieldByName("lvol1", (int*)&(acc.AccountNo));
		clt.GetDoubleFieldByName("damt0", &bala_amt);
		acc.Balance = (int)d4u5(bala_amt * 100, 0);
		GET_PACK_STR(clt, "scust_auth2", acc.StudentCode);
		GET_PACK_STR(clt, "sroom_no", acc.PID);
		GET_PACK_STR(clt, "sdate0", card_phyno);
		GET_PACK_STR(clt, "scert_no", acc.IDCard);
		clt.GetIntFieldByName("lvol6", &card_id);
		if (card_id > 0)
		{
			if (strlen(card_phyno) != 8)
				continue;
		}
		else
			continue;
		do_convert_card_phyno_str(card_phyno, &(acc.CardNo));
		GET_PACK_STR(clt, "scust_no2", invalid_date);
		strcpy(acc.ExpireDate, invalid_date + 2);
		GET_PACK_STR(clt, "sdate2", state_id);
		GET_PACK_STR(clt, "sstatus1", id_status);
		memset(acc.Flag, '0', sizeof(acc.Flag) - 1);
		do_card_state_to_flag(state_id, acc.Flag, id_status[0]);
		if (ret_acc.AccountNo == 0)
			ret_acc = acc;
		else if (ret_acc.AccountNo == acc.AccountNo)
		{
			if (state_id[1] == '0' && state_id[2] == '0'
			        && state_id[0] == '1')
			{
				ret_acc = acc;
			}
		}
		else
			break;
	}
	if (ret_acc.AccountNo > 0)
	{
		*pAccMsg = ret_acc;
		g_logger.writelog("��ѯ�ͻ���Ϣcutid[%d]", pAccMsg->AccountNo);
		if( ret_acc.Flag[1] == ACC_FLAG_LOGOUT )
			ret = ERR_TA_NOREC;
		else if(ret_acc.Flag[2] == '1')
			ret = ERR_TA_LOST_CARD;
		else if(ret_acc.Flag[3] == '1')
			ret = ERR_TA_FREEZE_CARD;
		else
			ret = ERR_OK;
	}
	return ret;
}
// ģ����ѯ��Ϣ
int CALLAPI TA_HazyInqAcc(AccountMsg *pAccMsg, int *RecNum , char *FileName
                          , short TimeOut = 10)
{
	g_logger.writelog("����  TA_HazyInqAcc ");
	/*
	if(FileName == NULL || strlen(FileName) == 0)
	{
		SetLastErr(ERR_TA_PARA,"�����ļ�������ȷ!");
		return ERR_TA_PARA;
	}
	*/
	do_get_current_time(FileName);
	char full_path[1024] = "";
	sprintf(full_path, "%sRecvTemp\\", g_module_path);
	if (do_create_dir(full_path))
	{
		SetLastErr(ERR_FAIL, "����Ŀ¼ʧ��[%s]", full_path);
		return ERR_FAIL;
	}
	strcat(full_path, FileName);
	TimeOut = (TimeOut > 0 && TimeOut <= 80) ? TimeOut : 30;
	TimeOut *= 1000;
	int rec_cnt = 0;
	FILE *fp;
	int ret;

	if (do_check_file_exists(full_path))
	{
		// ɾ���ļ�
		if (unlink(FileName) == -1)
			return ERR_DEL_FAIL;
	}
	if ((fp = fopen(full_path, "wb+")) == NULL)
	{
		SetLastErr(ERR_REFUSE, "���ļ�ʧ��");
		return ERR_REFUSE;
	}
	ret = ERR_COMM_FAIL;
	KS_YKT_Clt clt;
	clt.SetStringFieldByName("semail", pAccMsg->Name);
	if (strlen(pAccMsg->DeptCode) == 3)
	{
		int dept_id;
		ret = do_dept_code2id(pAccMsg->DeptCode, &dept_id);
		if (!ret)
		{
			clt.SetIntFieldByName("lvol0", dept_id);
		}
		else
			clt.SetStringFieldByName("scust_no", pAccMsg->DeptCode);
	}
	else
		clt.SetStringFieldByName("scust_no", pAccMsg->DeptCode);
	clt.SetStringFieldByName("smarket_code", pAccMsg->SexNo);
	clt.SetStringFieldByName("scust_auth2", pAccMsg->StudentCode);
	if (clt.SendRequest(FUNC_QUERY_USER_INFO, TimeOut))
	{
		if (clt.GetReturnCode())
		{
			ret = ERR_FAIL;
			SetLastErr(ret, "��ѯ[%d]���ش���[%d]", FUNC_QUERY_USER_INFO,
			           clt.GetReturnCode());
		}
		else
		{
			HazyInqAccMsg acc;
			ret = ERR_OK;
			while (clt.HasMoreRecord())
			{
				clt.GetNextPackage();
				double bala_amt = 0.0;
				char invalid_date[9] = "";
				char state_id[5] = "";
				char id_status[2] = "";
				char card_phyno[9] = "";
				int card_id;
				int school_id = 0;
				char school_code[4] = "";
				char dept_code[15] = "";
				memset(&acc, 0, sizeof acc);

				GET_PACK_STR(clt, "semail", acc.Name);
				PAD_STR(acc.Name);

				GET_PACK_STR(clt, "smarket_code", acc.SexNo);
				PAD_STR(acc.SexNo);

				clt.GetIntFieldByName("lvol2", &school_id);
				do_dept_id2code(school_id, school_code);
				GET_PACK_STR(clt, "sphone", dept_code);
				sprintf(acc.DeptCode, "%s%s", school_code, dept_code);
				PAD_STR(acc.DeptCode);

				clt.GetIntFieldByName("lvol1", (int*)&(acc.AccountNo));
				clt.GetDoubleFieldByName("damt0", &bala_amt);
				acc.Balance = (int)d4u5(bala_amt * 100, 0);

				GET_PACK_STR(clt, "scust_auth2", acc.StudentCode);
				PAD_STR(acc.StudentCode);

				GET_PACK_STR(clt, "sroom_no", acc.PID);
				PAD_STR(acc.PID);

				GET_PACK_STR(clt, "scert_no", acc.IDCard);

				GET_PACK_STR(clt, "sdate0", card_phyno);
				clt.GetIntFieldByName("lvol6", &card_id);
				if (card_id > 0)
				{
					if (strlen(card_phyno) != 8)
						continue;
				}
				else
					continue;
				do_convert_card_phyno_str(card_phyno, &(acc.CardNo));
				GET_PACK_STR(clt, "scust_no2", invalid_date);
				strcpy(acc.ExpireDate, invalid_date + 2);
				GET_PACK_STR(clt, "sdate2", state_id);
				GET_PACK_STR(clt, "sstatus1", id_status);
				GET_PACK_STR(clt, "scert_no", acc.IDCard);
				PAD_STR(acc.IDCard);
				PAD_STR(acc.IDNo);
				memset(acc.Flag, '0', sizeof(acc.Flag) - 1);
				do_card_state_to_flag(state_id, acc.Flag, id_status[0]);
				// д���ļ�
				if (fwrite(&acc, sizeof(acc), 1, fp) < 1)
				{
					ret = ERR_REFUSE;
					break;
				}
				rec_cnt++;
			}
		}
	}
	if (fp)
	{
		fclose(fp);
	}
	*RecNum = rec_cnt;
	g_logger.writelog("��ѯ��Ա��Ϣ����[%d],���ؼ�¼��[%d]", ret, rec_cnt);
	return ret;
}

int CALLAPI TA_DownControlFile(short timeOut = 10)
{
	g_logger.writelog("����  TA_DownControlFile ");
	char full_path[1024] = "";
	char temp[] = "dummy";
	FILE *fp;
	strcpy(full_path, g_module_path);
	strcat(full_path, "ControlFile\\");
	if (do_create_dir(full_path))
	{
		g_logger.writelog("����Ŀ¼ʧ��[%s]", full_path);
		return ERR_COMM_FAIL;
	}
	strcat(full_path, "Control.bin");
	if (do_check_file_exists(full_path))
	{
		return 1;
	}
	if ((fp = fopen(full_path, "w+")) == NULL)
	{
		SetLastErr(ERR_COMM_FAIL, "���� Control.bin �ļ�ʧ��");
		return ERR_COMM_FAIL;
	}
	fwrite(temp, strlen(temp), 1, fp);
	fclose(fp);
	return 1;
}

BOOL CALLAPI TA_ExtractConFile(const int readrec , const char * fn)
{
	g_logger.writelog("���� TA_ExtractConFile ���� rec[%d]", readrec);
	int ret, rec_cnt;
	int dict_no = -1;
	void *pdata;
	int data_len;
	FILE *fp;
	char full_path[1024] = "";
	if (fn == NULL)
		return FALSE;
	strcpy(full_path, g_module_path);
	strcat(full_path, "ControlFile\\");
	if (do_create_dir(full_path))
	{
		g_logger.writelog("���� ControlFile Ŀ¼ʧ��!");
		return FALSE;
	}
	strcat(full_path, fn);
	if (do_check_file_exists(full_path))
	{
		if (unlink(full_path) == -1)
			return FALSE;
	}
	KS_YKT_Clt clt;
	switch (readrec)
	{
	case OFFSET_T_DEPARTMENT:	/* ������֯�� */
		dict_no = 3001;
		break;
	case OFFSET_T_PID:			/* ��ݴ���� */
		dict_no = 3000;
		break;
	case OFFSET_T_IDTYPE:		/* ֤�����ͱ� */
		dict_no = 87;
		break;
	case OFFSET_T_PEOPLE:		/* ����� */
		dict_no = 2001;
		break;
	case OFFSET_T_NATION:		/* ������ */
		dict_no = 89;
		break;
	case OFFSET_T_ZZMM:			/* ������ò */
		break;
	case OFFSET_SCHOOLCODE:		/* 0:ѧУ����SchoolCode*/
	case OFFSET_T_AREA:			/* У/��������� */
		dict_no = -27;
		break;
	case OFFSET_T_SS_YUAN:		/* ���ᣨԷ/�� */
	case OFFSET_T_WHCD:			/* �Ļ��̶� */
	case OFFSET_T_CARDTYPE:     /* ��������� */
	case OFFSET_T_JSZC:			/* ����ְ�� */
	case OFFSET_T_XZZW:			/* ����ְ�� */

	case OFFSET_SUBJECT:		/* 1:�ձ��ֵ�Subject*/
	case OFFSET_FEE:			/* 2:���������趨��fee*/
	case OFFSET_CONFIGINFO:		/* 3:���ִ����ֵ�ConfigInfo*/
	case OFFSET_BRANCH:			/* 4:�̻����ű�branch*/
	case OFFSET_CSZD:			/* 5:ϵͳ����cszd*/
	case OFFSET_TRCD:			/* 6:�¼������trcd*/
	case OFFSET_MESSAGE:		/* 7:ϵͳ��Ϣ��message*/
	default:
		return FALSE;
	}
	if (dict_no == -1)
		return FALSE;

	clt.SetIntFieldByName("lcert_code", dict_no);
	clt.SetStringFieldByName("scust_auth", g_devices.devices[0].oper_code);
	if (!clt.SendRequest(FUNC_READ_DICT, 20000))
	{
		SetLastErr(ERR_FAIL, "������ʧ��,���ܺ�[%d]", FUNC_READ_DICT);
		return FALSE;
	}

	if ((fp = fopen(full_path, "wb+")) == NULL)
		return FALSE;
	rec_cnt = 0;
	ret = TRUE;
	while (clt.HasMoreRecord())
	{
		t_idtype idtype;
		t_department dept;
		t_people people;
		t_nation nation;
		t_area area;
		t_pid pid;
		int area_id;


		int ret_dict_no;
		char dict_value[31] = "";
		char dict_caption[41] = "";

		clt.GetNextPackage();
		clt.GetIntFieldByName("lcert_code", &ret_dict_no);
		GET_PACK_STR(clt, "sname", dict_value);
		GET_PACK_STR(clt, "sall_name", dict_caption);
		switch (readrec)
		{
		case OFFSET_T_DEPARTMENT:	/* ������֯�� */
			memset(&dept, 0, sizeof dept);
			strncpy(dept.area_code, dict_value, 3);
			if (strlen(dict_value) > 3)
				src2des(dept.dept_code, dict_value + 3);
			else
				src2des(dept.dept_code, dict_value);
			dept.dept_level = strlen(dept.dept_code) / 3;
			PAD_STR(dept.dept_code);
			src2des(dept.dept_name, dict_caption);
			//src2des(dept.dept_easycode,dept.area_code);
			dept.dept_type = 1;
			dept.dept_flag = 1;
			strcpy(dept.dept_opercode, "000");
			dict_no = -22;
			pdata = &dept;
			data_len = sizeof(dept);
			fprintf(fp, "%s,%s,%s,%d,%s,%d,%d,%s,%s\r\n", dept.dept_code
			        , dept.dept_name, dept.area_code, dept.dept_level, dept.dept_easycode, dept.dept_type
			        , dept.dept_flag, dept.dept_desc, dept.dept_opercode);
			break;
		case OFFSET_T_IDTYPE:		/* ֤�����ͱ� */
			dict_no = 87;
			memset(&idtype, 0, sizeof idtype);
			src2des(idtype.idtype_code, dict_value);
			src2des(idtype.idtype_name, dict_caption);
			src2des(idtype.idtype_easycode, idtype.idtype_code);
			pdata = &idtype;
			data_len = sizeof(idtype);
			fprintf(fp, "%s,%s,%s\n", idtype.idtype_code, idtype.idtype_name, idtype.idtype_easycode);
			break;
		case OFFSET_T_PEOPLE:		/* ����� */
			dict_no = 2001;
			memset(&people, 0, sizeof people);
			src2des(people.people_code, dict_value);
			src2des(people.people_name, dict_caption);
			src2des(people.people_easycode, people.people_code);
			pdata = &people;
			data_len = sizeof(people);
			fprintf(fp, "%s,%s,%s,%d\r\n", people.people_code, people.people_name, people.people_easycode
			        , people.people_flag);
			break;
		case OFFSET_T_NATION:		/* ������ */
			dict_no = 89;
			memset(&nation, 0, sizeof nation);
			src2des(nation.nation_code, dict_value);
			src2des(nation.nation_name, dict_caption);
			src2des(nation.nation_easycode, nation.nation_code);
			pdata = &nation;
			data_len = sizeof(nation);
			fprintf(fp, "%s,%s,%s,%d\r\n", nation.nation_code, nation.nation_name, nation.nation_easycode
			        , nation.nation_flag);
			break;
		case OFFSET_SCHOOLCODE:
		case OFFSET_T_AREA:			/* У/��������� */
			dict_no = -27;
			memset(&area, 0, sizeof area);
			area_id = atoi(dict_value);
			do_dept_id2code(area_id, area.area_code);
			src2des(area.area_name, dict_caption);
			src2des(area.area_easycode, area.area_code);
			pdata = &area;
			data_len = sizeof(area);
			fprintf(fp, "%s,%s,%s\r\n", area.area_code, area.area_name, area.area_easycode);
			break;
		case OFFSET_T_PID:			/* ��ݴ���� */
			dict_no = 3000;
			memset(&pid, 0, sizeof pid);
			strncpy(pid.area_code, dict_value, 3);
			if (strlen(dict_value) > 3)
				src2des(pid.pid_code, dict_value + 3);
			else
				src2des(pid.pid_code, dict_value);
			src2des(pid.pid_name, dict_caption);
			PAD_STR(pid.pid_cardtypeno);
			strcpy(pid.pid_opercode, "000");
			//src2des(pid.pid_easycode,pid.pid_code);
			fprintf(fp, "%s,%c,%s,%s,%s,%s,%s,%s,%d\r\n", pid.pid_code, '1', pid.area_code
			        , pid.pid_name, pid.pid_easycode, "1", pid.pid_opercode, pid.pid_cardtypeno, pid.pid_zkl);
			break;
		case OFFSET_T_ZZMM:			/* ������ò */
		case OFFSET_T_SS_YUAN:		/* ���ᣨԷ/�� */
		case OFFSET_T_WHCD:			/* �Ļ��̶� */
		case OFFSET_T_CARDTYPE:     /* ��������� */
		case OFFSET_T_JSZC:			/* ����ְ�� */
		case OFFSET_T_XZZW:			/* ����ְ�� */
		case OFFSET_SUBJECT:		/* 1:�ձ��ֵ�Subject*/
		case OFFSET_FEE:			/* 2:���������趨��fee*/
		case OFFSET_CONFIGINFO:		/* 3:���ִ����ֵ�ConfigInfo*/
		case OFFSET_BRANCH:			/* 4:�̻����ű�branch*/
		case OFFSET_CSZD:			/* 5:ϵͳ����cszd*/
		case OFFSET_TRCD:			/* 6:�¼������trcd*/
		case OFFSET_MESSAGE:		/* 7:ϵͳ��Ϣ��message*/
		default:
			ret = FALSE;
			break;
		}
	}
	if (fp)
	{
		fclose(fp);
	}
	return ret;
}

int CALLAPI TA_CardLost(CardOperating *pCardOper, short TimeOut = 10)
{
	g_logger.writelog("���� TA_CardLost ����");
	TEST_SYS_INIT;
	if (pCardOper->AccountNo <= 0)
		return ERR_TA_PARA;
	if (strlen(pCardOper->inqPassword) <= 0)
		return ERR_TA_PARA;
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lvol0", pCardOper->AccountNo);
	clt.SetIntFieldByName("lvol1", 0);
	clt.SetIntFieldByName("lvol2", 0);
	clt.SetStringFieldByName("semp_pwd", pCardOper->inqPassword);
	clt.SetStringFieldByName("sstatus0", "1");
	clt.SetStringFieldByName("scust_limit", g_devices.devices[0].oper_code);
	clt.SetIntFieldByName("lvol6", g_devices.devices[0].device_id);
	clt.SetIntFieldByName("lvol7", g_devices.devices[0].device_id);
	if (clt.SendRequest(FUNC_LOST_CARD))
	{
		return ERR_FAIL;
	}
	pCardOper->RetCode = clt.GetReturnCode();
	if (clt.GetReturnCode())
	{
		SetLastErr(ERR_FAIL, "��ʧʧ�ܣ�����[%d]", clt.GetReturnCode());
		return ERR_FAIL;
	}
	else
		return ERR_OK;
}

int CALLAPI TA_CRBeep(unsigned int BeepMSecond)
{
	ControlBuzzer();
	return ERR_OK;
}

short CALLAPI TA_DesEncrypt(const void *InBuf, long InLen, void *OutBuf, void *pKey)
{
	int ret, out_len;
	unsigned char *pin = (unsigned char*)InBuf;
	unsigned char *pout = (unsigned char*)OutBuf;
	unsigned char temp[8];
	int offset = 0;
	out_len = 0;
	for (;offset < InLen;offset += 8)
	{
		if (InLen - offset < 8)
		{
			// ��Ҫ����
			int pad_len = 8 - (InLen - offset);
			memcpy(temp, pin + offset, InLen - offset);
			memset(temp + 8 - pad_len, pad_len, pad_len);
			ret = encrypt_des((unsigned char*)pKey, 8, temp, 8, pout + offset);
		}
		else
			ret = encrypt_des((unsigned char*)pKey, 8, pin + offset, 8, pout + offset);
		if (!ret)
			return -1;
		out_len += 8;
	}
	return out_len;
}

void CALLAPI TA_DesDecrypt(const void *InBuf, long InLen, void *OutBuf, void *pKey)
{
	unsigned char *pin = (unsigned char*)InBuf;
	unsigned char *pout = (unsigned char*)OutBuf;
	int ret, offset;
	if (InLen % 8 != 0)
		return;

	for (offset = 0;offset < InLen;offset += 8)
	{
		ret = dencrypt_des((unsigned char*)pKey, 8, pin + offset, 8, pout + offset);
		if (ret)
			return;
	}
}

int CALLAPI TA_Refund (CardConsume *pCardCons, short TimeOut = 10)
{
	g_logger.writelog("���� TA_Refund ����");
	return ERR_FAIL;
}

int CALLAPI TA_CardOpen(CardOperating *pCardOper, short TimeOut = 10)
{
	g_logger.writelog("���� TA_CardOpen ����");
	return ERR_OK;
}
int CALLAPI TA_CardClose(CardOperating *pCardOper, short TimeOut = 10)
{
	g_logger.writelog("���� TA_CardClose ����");
	return ERR_OK;
}
int CALLAPI TA_PermitID(CardOperating *pCardOper, short TimeOut = 10)
{
	g_logger.writelog("���� TA_PermitID ����");
	return ERR_OK;
}
int CALLAPI TA_ProhibitID(CardOperating *pCardOper, short TimeOut = 10)
{
	g_logger.writelog("���� TA_ProhibitID ����");
	return ERR_OK;
}

int CALLAPI TA_InqTranFlow(InqTranFlow *pInqTranFlow, short TimeOut = 10)
{
	g_logger.writelog("���� TA_InqTranFlow ����");
	return ERR_FAIL;
}
int CALLAPI TA_HazyInqAccEx(AccountMsg *pAccMsg, int *RecNum , char *FileName, short TimeOut = 10)
{
	g_logger.writelog("���� TA_HazyInqAccEx ����");
	return ERR_FAIL;
}
int CALLAPI TA_InqAccEx(AccountMsgEx * pAccMsg, short TimeOut = 10)
{
	g_logger.writelog("���� TA_InqAccEx ����");
	return ERR_FAIL;
}
int CALLAPI TA_InqAccByDeptClass(char *DeptCode, char *InYear, int *RecNum , char *FileName , short TimeOut = 10)
{
	g_logger.writelog("���� TA_InqAccByDeptClass ����");
	return ERR_FAIL;
}
int CALLAPI TA_InqAccByPIDInYear(char *PID, char *InYear, int *RecNum , char *FileName , short TimeOut = 10)
{
	return ERR_FAIL;
}
int  CALLAPI TA_DownPhotoFile(char * IDNo , char *PhotoFn, short Timeout = 10)
{
	return ERR_FAIL;
}
int CALLAPI TA_UpLoadFile(char *fn , short timeOut = 10)
{
	return ERR_FAIL;
}
int CALLAPI TA_DownLoadFile(char *fn , short timeOut = 5)
{
	return ERR_FAIL;
}
//wenjian add

//int CALLAPI TA_Charge(CardCharge *pCardCharg, bool IsVerfy, short TimeOut=10)
int CALLAPI TA_Charge(char *pCardCharg, bool IsVerfy, short TimeOut = 10)
{
	g_logger.writelog("Begin Call TA_Charge!");
	return ERR_FAIL;
}

int CALLAPI TA_UpJournal(const char *FileName, int reccount , short TimeOut)
{
	SetLastErr(ERR_FAIL, "���� TA_UpJournal ��֧��");
	return ERR_FAIL;
}


int _stdcall TA_InqOpenFlow(InqOpenFlow *pInqOpenFlow, short TimeOut)
{
	SetLastErr(ERR_FAIL, "���� TA_InqOpenFlow ��֧��");
	return ERR_FAIL;
}
int _stdcall TA_Dsql_ORecord(const char *Dsql ,
                             int * nReturn ,
                             short timeOut)
{
	SetLastErr(ERR_FAIL, "���� TA_Dsql_ORecord ��֧��");
	return ERR_FAIL;
}

int _stdcall TA_Dsql_QRecord(const char *Dsql ,
                             int * nReturn ,
                             short timeOut)
{
	SetLastErr(ERR_FAIL, "���� TA_Dsql_QRecord ��֧��");
	return ERR_FAIL;
}

int WINAPI TA_BussComm(char* sendBuf,
                       int sendLen,
                       char * recvBuf,
                       int *recvLen,
                       char priority,
                       short timeOut = 10)
{
	g_logger.writelog("���� TA_BussComm ����");
	strncpy(recvBuf, sendBuf, sendLen);
	*recvLen = sendLen;
	return ERR_OK;
}

int __stdcall NC_BussComm()
{
	g_logger.writelog("���� NC_BussComm ����");
	return ERR_FAIL;
}

int __stdcall NC_UpLoadFile()
{
	g_logger.writelog("���� NC_UpLoadFile ����");
	return ERR_FAIL;
}

int __stdcall NC_DownLoadFile()
{
	g_logger.writelog("���� NC_DownLoadFile ����");
	return ERR_FAIL;
}

int WINAPI NC_DownControlFile(char * IP, short port, short timeOut)
{
	g_logger.writelog("���� NC_DownControlFile ����");
	return ERR_FAIL;
}

int __stdcall DSQL_Query_File()
{
	g_logger.writelog("���� DSQL_Query_File ����");
	return ERR_FAIL;
}

int __stdcall DSQL_Query_Record()
{
	g_logger.writelog("���� DSQL_Query_Record ����");
	return ERR_FAIL;
}

int __stdcall DSQL_Oper_Record()
{
	g_logger.writelog("���� DSQL_Oper_Record ����");
	return ERR_FAIL;
}

int __stdcall G_GetAPIPath()
{
	g_logger.writelog("���� G_GetAPIPath ����");
	return ERR_FAIL;
}

int __stdcall G_Chg_NodeID()
{
	g_logger.writelog("���� G_Chg_NodeID ����");
	return ERR_FAIL;
}

int __stdcall EC_GetCfg()
{
	g_logger.writelog("���� EC_GetCfg ����");
	return ERR_FAIL;
}

int __stdcall G_PW_Encrypt()
{
	g_logger.writelog("���� G_PW_Encrypt ����");
	return ERR_FAIL;
}

int __stdcall G_PW_Decrypt()
{
	g_logger.writelog("���� G_PW_Decrypt ����");
	return ERR_FAIL;
}

int __stdcall NC_DownPhotoFile()
{
	g_logger.writelog("���� NC_DownPhotoFile ����");
	return ERR_FAIL;
}

//////////////////////////////////////////////////////////////////////////
// ���ӹ��ݴ�ѧ�� �ѻ�ʹ�õĽӿ�
/*
 \brief �ѻ���Ȩ������ʹ��
 \param sysid - ������������
 \param termid - ������������豸ID��
 \param maxjnl - �豸��ʼ��ˮ��
 \return ���� 0 ��ʾ�ɹ�, ʧ�ܷ��ش�����
 */
int __stdcall KSG_Offline_Auth(int sysid, short termid, unsigned long maxjnl)
{
	TEST_COM_OPEN;
	int ret;
	BYTE auth_key[8];
	BYTE auth_flag;
	int idx = 0;
	int term_flag = 0;

	if (sysid < 0 || termid < 0 || termid > 65535)
		return ERR_FAIL;

	memset(&auth_key, 0, sizeof auth_key);
	ret = SMT_ReadAuthorWorkKeyAndFlag(auth_key, &auth_flag);
	if (ret)
	{
		g_logger.writelog("��ȡ��Ȩ��ʧ�ܣ�����[%d]", ret);
		return ERR_READ_AUTH_CARD;
	}

	if (auth_flag & KS_ACR_AUTH_TERM)
	{
		g_logger.writelog("�ն�������֤");
		term_flag |= DEV_FLAG_LOGIN;
	}
	if (auth_flag & KS_ACR_CONSUME_TERM)
	{
		g_logger.writelog("�ն���������");
		term_flag |= DEV_FLAG_CONSUM | DEV_FLAG_LOGIN;
	}

	if (auth_flag & KS_ACR_ADD_MONEY_TERM)
	{
		g_logger.writelog("�ն������ֵ");
		term_flag |= DEV_FLAG_ADD_MONEY | DEV_FLAG_LOGIN;
	}
	if (term_flag == 0)
	{
		g_logger.writelog("����Ȩ����Ȩ��");
		return ERR_AUTHCARD_RIGHT;
	}

	g_devices.devices[idx].device_id = 0;
	g_devices.devices[idx].maxjnl = 1;
	//hex2dec(g_workkey,auth_key,8);
	g_devices.devices[idx].purse_no = 1;
	// ���ƴ������޶�
	g_devices.devices[idx].trade_limit_per_cnt = 3000;
	g_devices.devices[idx].day_trade_limit = 5000;
	src2des(g_devices.devices[idx].oper_code, "system");

	g_devices.devices[idx].term_no = 0;
	g_devices.devices[idx].device_id = termid;
	g_devices.devices[idx].sys_id = sysid;
	g_devices.devices[idx].flag = term_flag;
	// �ѻ�
	g_devices.devices[idx].is_online = DEV_TERM_OFFLINE;

	//*maxjnl = g_devices.devices[idx].maxjnl;
	g_devices.devices[idx].maxjnl = maxjnl;
	memcpy(g_hex_workhey, auth_key, sizeof g_hex_workhey);
	encrypt_work_key(auth_key, g_hex_workhey);

	if (SetCardMainKey(auth_key))
	{
		SetLastErr(ERR_AUTH_FAILED, "װ�ع�����Կʧ��");
		return ERR_AUTH_FAILED;
	}
	ControlBuzzer();
	g_logger.writelog("��Ȩ�ն��ѻ�ʹ��");
	return 0;
}

#pragma  pack(1)
struct KS_Consume_Record
{
	/*
	��ˮ�ļ���ʽ	����(�ַ�)
	��������			8
	����ʱ��			6
	�ն˺�				4		unsigned short
	��ϵͳ��			8		int
	������ˮ��			8		int
	���׿���			8		int
	�뿨ֵ				8		int
	���				8		int ����Ϊ��������Ϊ��
	�����״���			4		unsigned short
	���ױ�־			2		byte

	�ܳ��� 64 ���ַ�
	CRC					4		byte
	*/
	char tx_date[9];
	char tx_time[7];
	unsigned short termid;
	int  sysid;
	int  serial_no;
	int  card_id;
	int  in_balance;
	int  trade_amount;
	unsigned short trade_count;
	unsigned char flag;
};

#pragma  pack()

class KS_Record_File
{
private:
	char file_path_[1025];
	int read_idx_;
	int write_idx_;
	int file_offset_;
	FILE *record_file_;
	size_t rec_file_len_;
	const static int s_block_len_;
	const static int s_record_len_;
	int encode_buf(const char *buf, int len, unsigned char *enc_buf, int *enc_len);
	int decode_buf(const unsigned char *dec_buf, int len, char *buf, int *buf_len);
public:
	KS_Record_File(const char *file_path);
	~KS_Record_File();
	int write_record(const KS_Consume_Record *record, int is_test);
	int read_record(KS_Consume_Record *record);
	int record_index() const;
};

const int KS_Record_File::s_block_len_ = 8;
const int KS_Record_File::s_record_len_ = 68;

KS_Record_File::KS_Record_File(const char *file_path)
		: read_idx_(0), write_idx_(0), file_offset_(0), record_file_(NULL), rec_file_len_(0)
{
	src2des(file_path_, file_path);
	record_file_ = fopen(file_path_, "ab+");
	if (record_file_)
	{
		if (fseek(record_file_, 0L, SEEK_END) == 0)
		{
			rec_file_len_ = ftell(record_file_);
		}
	}
}
KS_Record_File::~KS_Record_File()
{
	if (record_file_)
	{
		fclose(record_file_);
	}
}

int KS_Record_File::record_index() const
{
	return read_idx_;
}

int KS_Record_File::write_record(const KS_Consume_Record *record, int is_test)
{
	//
	int ret;
	uint16 crc = 0;
	if (!record_file_)
	{
		SetLastErr(ERR_NO_FILE, "��¼��ˮʧ�ܣ��ļ��޷�����!");
		return ERR_NO_FILE;
	}
	// ���ļ�ָ�붨λ����β
	if (fseek(record_file_, 0L, SEEK_END))
	{
		SetLastErr(ERR_FILESTAT, "��λ��ˮ�ļ�ʧ�ܣ�");
		return ERR_FILESTAT;
	}
	char record_buf[256] = "";
	unsigned char enc_record[256] = "";
	int buf_len, written_len, enc_len;
	buf_len = sprintf(record_buf, "%s%s%04X%08X%08X%08X%08X%08X%04X%02X"
	                  , record->tx_date, record->tx_time, record->termid, record->sysid
	                  , record->serial_no, record->card_id, record->in_balance
	                  , record->trade_amount, record->trade_count, record->flag);

	crc = GenerateCRC16((unsigned char*)record_buf, buf_len);

	buf_len += sprintf(record_buf + buf_len, "%04X", crc);
	if (!is_test)
		g_logger.writelog("��¼��ˮ������[%d]", buf_len);

	ret = encode_buf(record_buf, buf_len, enc_record, &enc_len);
	if (ret)
	{
		return ret;
	}

	if (is_test)
		return 0;

	written_len = 0;
	do
	{
		int wlen = fwrite(enc_record + written_len, 1, enc_len - written_len, record_file_);
		if (wlen > 0)
			written_len += wlen;
		else if (wlen < 0)
		{
			SetLastErr(ERR_FAIL, "д��ˮ�ļ�ʧ��[%s]", file_path_);
			return ERR_FAIL;
		}
	}
	while (written_len < enc_len);
	// ������ˮ�ļ�����
	rec_file_len_ += written_len;
	g_logger.writelog("��¼��ˮ����������[%s]ʱ��[%s]����[%d]���[%d]"
	                  , record->tx_date, record->tx_time, record->card_id, record->trade_amount);
	return 0;
}

int KS_Record_File::encode_buf(const char *buf, int len
                               , unsigned char *enc_buf, int *enc_len)
{
	unsigned char temp[s_block_len_];
	int offset, ret;
	offset = 0;
	do
	{
		if (len - offset < s_block_len_)
		{
			int left_len = len - offset;
			int pad_len = s_block_len_ - left_len;
			memcpy(temp, buf + offset, left_len);
			// ���㲹�ֽ�
			memset(temp + left_len, (unsigned char)pad_len, pad_len);
		}
		else
		{
			memcpy(temp, buf + offset, s_block_len_);
		}
		ret = encrypt_des(g_hex_workhey, 8, temp, s_block_len_, enc_buf + offset);
		if (ret)
		{
			SetLastErr(ERR_ENCRYPT_ERR, "�������ݿ����,ret[%d]", ret);
			return ERR_ENCRYPT_ERR;
		}
		offset += s_block_len_;
	}
	while (offset < len);
	if (offset % s_block_len_ != 0)
	{
		SetLastErr(ERR_ENCRYPT_ERR, "�������ݿ����,���ܺ󳤶�[%d]����ȷ", offset);
		return ERR_ENCRYPT_ERR;
	}
	*enc_len = offset;
	return 0;
}

int KS_Record_File::decode_buf(const unsigned char *dec_buf, int len
                               , char *buf, int *buf_len)
{
	unsigned char temp[s_block_len_];
	int offset, ret;
	offset = 0;
	do
	{
		memcpy(temp, dec_buf + offset, s_block_len_);
		ret = dencrypt_des(g_hex_workhey, 8, temp, s_block_len_, (unsigned char*)buf + offset);
		if (ret)
		{
			SetLastErr(ERR_DECRYPT_ERR, "�������ݿ����,ret[%d]", ret);
			return ERR_DECRYPT_ERR;
		}
		offset += s_block_len_;
	}
	while (offset < len);

	if (offset % s_block_len_ != 0)
	{
		SetLastErr(ERR_DECRYPT_ERR, "�������ݿ����,���ܺ󳤶�[%d]����ȷ", offset);
		return ERR_DECRYPT_ERR;
	}
	*buf_len = offset;
	return 0;
}

int KS_Record_File::read_record(KS_Consume_Record *record)
{

	unsigned char enc_record[256];
	char record_buf[256] = "";
	char temp[6] = "";
	uint16 crc;
	int ret, buf_len;
	int offset = 0;
	int read_len = 0;
	int enc_len = (8 - s_record_len_ % 8) + s_record_len_;
	memset(enc_record, 0, sizeof enc_record);
	memset(record_buf, 0, sizeof record_buf);
	KS_Consume_Record this_rec;
	if (!record_file_)
	{
		SetLastErr(ERR_NO_FILE, "��¼��ˮʧ�ܣ��ļ��޷�����!");
		return ERR_NO_FILE;
	}

	offset = enc_len * read_idx_;
	if (offset >= rec_file_len_)
	{
		return ERR_READ_EOF;
	}
	if (offset + enc_len > rec_file_len_)
	{
		// �ļ�������
		g_logger.writelog("��ˮ�ļ�[%s]������!");
		return ERR_READ_EOF;
	}
	if (fseek(record_file_, offset, SEEK_SET))
	{
		SetLastErr(ERR_FILESTAT, "��λ��ˮ�ļ�ʧ�ܣ�");
		return ERR_FILESTAT;
	}
	if (feof(record_file_))
	{
		return ERR_READ_EOF;
	}
	// ��ȡ����
	do
	{
		int rlen = fread(enc_record + read_len, 1, enc_len - read_len, record_file_);
		if (rlen > 0)
			read_len += rlen;
		else if (rlen <= 0)
		{
			SetLastErr(ERR_FAIL, "����ˮ�ļ�ʧ��[%s]", file_path_);
			return ERR_FAIL;
		}
	}
	while (read_len < enc_len);
	/*
	if(fread(enc_record,enc_len,1,record_file_) != 1)
	{
		SetLastErr(ERR_FAIL,"����ˮ�ļ�ʧ��[%s]",file_path_);
		return ERR_FAIL;
	}
	*/
	// ����
	ret = decode_buf(enc_record, enc_len, record_buf, &buf_len);
	if (ret)
	{
		return ret;
	}
	// У�� crc
	crc = GenerateCRC16((unsigned char*)record_buf, s_record_len_ - 4);
	sprintf(temp, "%04X", crc);
	if (strncmp(temp, record_buf + s_record_len_ -4, 4) != 0)
	{
		SetLastErr(ERR_SERIAL_CRC, "��ȡ��ˮ��У�� CRC ����");
		return ERR_SERIAL_CRC;
	}
	memset(&this_rec, 0, sizeof this_rec);
	src2des(this_rec.tx_date, record_buf);
	src2des(this_rec.tx_time, record_buf + 8);
	STR2SHORT(record_buf + 14, this_rec.termid);
	STR2INT(record_buf + 18, this_rec.sysid);
	STR2INT(record_buf + 26, this_rec.serial_no);
	STR2INT(record_buf + 34, this_rec.card_id);
	STR2INT(record_buf + 42, this_rec.in_balance);
	STR2INT(record_buf + 50, this_rec.trade_amount);
	STR2SHORT(record_buf + 58, this_rec.trade_count);
	STR2BYTE(record_buf + 62, this_rec.flag);
	memcpy(record, &this_rec, sizeof(KS_Consume_Record));
	read_idx_++;
	return 0;
}

/*
 \brief �ѻ����ѽӿ�
 \param pCardCons - ���Ѳ���������ͬ TA_Consume
 \param RecFile - �����������¼��ˮ������ļ���(����·����1024 ���ֽ�)
 \return ���� 0 ��ʾ�ɹ��� ���󷵻ش�����
 */
int __stdcall KS_Offline_Consume(CardConsume *pCardCons, char *RecFile)
{
	g_logger.writelog("����  KS_Offline_Consume ");
	TEST_TERM_LOGIN;
	TEST_COM_OPEN;
	int ret, term_idx;
	int card_id;
	int trade_serial = 0;
	//double trade_amt,out_amt;
	int trade_money, out_money;
	char now_date[9] = "";
	char now_time[7] = "";
	char last_trade_date[9] = "";
	char card_serial_no[9] = "";
	//char err_msg[512] = "";
	char serial_file_path[1025] = "";
	//AccountMsg acc;
	MONEY_PACK_INFO purse_info;


	if (pCardCons->TranAmt >= 0)
	{
		return ERR_TA_TRANAMT;
	}
	/*
	term_idx = do_find_dev_by_termno(pCardCons->TerminalNo);
	if(term_idx<0)
	{
		SetLastErr(ERR_TRN_STATION,"�ն�δ��Ȩ");
		return ERR_TRN_STATION;
	}
	*/
	term_idx = 0;

	if ((g_devices.devices[term_idx].flag & DEV_FLAG_CONSUM) == 0)
	{
		SetLastErr(ERR_TRN_STATION, "�ն˲���������!");
		return ERR_TRN_STATION;
	}
	if ((g_devices.devices[term_idx].is_online & DEV_TERM_OFFLINE) == 0)
	{
		SetLastErr(ERR_TRN_STATION, "�ѻ��豸��������ʵʱ����!��ʹ���ѻ�����!");
		return ERR_TRN_STATION;
	}
	if ((pCardCons->TranAmt* -1) >= g_devices.devices[term_idx].trade_limit_per_cnt)
	{
		if (strlen(pCardCons->PassWord) == 0)
		{
			SetLastErr(ERR_TA_EXCEED_QUOTA, "�������ѽ�������");
			return ERR_TA_EXCEED_QUOTA;
		}
	}
	if (pCardCons->TranJnl < g_devices.devices[term_idx].maxjnl)
	{
		SetLastErr(ERR_TA_PARA, "�����ն���ˮ�Ų���ȷ,����ֵ[%d]", pCardCons->TranJnl);
		return ERR_TA_PARA;
	}
	ret = ReadCardNO(&card_id);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "��ȡ����ʧ��!");
		return ERR_TA_READCARD;
	}
	ret = ReadSerial((unsigned char*)card_serial_no);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "��ȡ��������ID��ʧ��!");
		return ERR_TA_READCARD;
	}
	memset(&purse_info, 0, sizeof purse_info);
	ret = SMT_GetPacketInfo(g_devices.devices[term_idx].purse_no, &purse_info);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "����Ǯ��ʧ��,purse[%d]", g_devices.devices[term_idx].purse_no);
		return ERR_TA_READCARD;
	}
	if (purse_info.bala + pCardCons->TranAmt < 0)
	{
		return ERR_TA_TRANAMT;
	}
	// �Ƚ�����
	do_get_date_time(now_date, now_time);
	sprintf(last_trade_date, "20%02d%02d%02d", purse_info.date / 10000 % 100
	        , purse_info.date / 100 % 100, purse_info.date % 100);
	if (strcmp(last_trade_date, now_date) == 0)
	{
		if (purse_info.daybala - pCardCons->TranAmt > g_devices.devices[term_idx].day_trade_limit)
		{
			if (strlen(pCardCons->PassWord) == 0)
			{
				SetLastErr(ERR_TA_EXCEED_QUOTA, "���ۼƽ�������");
				return ERR_TA_EXCEED_QUOTA;
			}
		}
	}

	/// ��ʼ���ף���¼��ˮ�ļ�


	sprintf(serial_file_path, "%sserial", g_module_path);
	if (do_create_dir(serial_file_path))
	{
		SetLastErr(ERR_REFUSE, "����Ŀ¼ʧ��[%s]", serial_file_path);
		return ERR_REFUSE;
	}
	sprintf(serial_file_path, "%sserial\\rec_%s.log", g_module_path, now_date);

	KS_Record_File rec_writter(serial_file_path);
	KS_Consume_Record record;
	memset(&record, 0, sizeof record);
	src2des(record.tx_date, now_date);
	src2des(record.tx_time, now_time);
	record.serial_no = pCardCons->TranJnl;
	record.card_id = card_id;
	record.sysid = g_devices.devices[term_idx].sys_id;
	record.termid = g_devices.devices[term_idx].device_id;
	record.in_balance = purse_info.bala;
	record.trade_amount = pCardCons->TranAmt * -1;
	record.trade_count = purse_info.total_cnt;
	record.flag = 1;
	// ���Լ���
	ret = rec_writter.write_record(&record, 1);
	if (ret)
	{
		SetLastErr(ret, "������ˮʧ��");
		return ret;
	}
	int curr_card_id;
	ret = ReadCardNO(&curr_card_id);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "����д��ʧ��!");
		return ERR_TA_READCARD;
	}
	int retries = 3;
	ret = ERR_FAIL;
	// �������ֵ
	out_money = purse_info.bala + pCardCons->TranAmt;
	while (retries-- > 0)
	{
		if (curr_card_id != card_id)
		{
			SetLastErr(ERR_TA_NOT_SAMECARD, "����д�����Ų�һ��,��̨��ˮ��[%d]", record.serial_no);
			return ERR_TA_NOT_SAMECARD;
		}
		ret = SMT_PacketSetMoney(g_devices.devices[term_idx].purse_no, out_money);
		if (!ret)
		{
			pCardCons->CardBalance = out_money;
			break;
		}
	}
	if (ret)
	{
		g_logger.writelog("����д��ʧ��,��̨��ˮ��[%d]", record.serial_no);
		return ERR_TA_WRITECARD;
	}
	// �����¼�ļ�
	ret = rec_writter.write_record(&record, 0);
	if (ret)
	{
		SetLastErr(ret, "��¼��ˮʧ��,tx_date[%s],tx_time[%s],card_id[%d],inbala[%d],amount[%d]"
		           , record.tx_date, record.tx_time, record.card_id, record.in_balance, record.trade_amount);
		return ret;
	}
	strcpy(RecFile, serial_file_path);
	return 0;
}
/*
 \breif �ϴ��ѻ�������ˮ, ָ����ˮ���ڳ���ͨ���� serial Ŀ¼�²��� rec_YYYYMMDD.log ��
 ��ˮ�ļ��ϴ���ˮ���ϴ���ɺ� rec_YYYYMMDD.log �ļ�������Ϊ rec_YYYYMMDD.log.�ɼ�ʱ���
 \param serial_date ��ˮ����
 \param serial_cnt - �����������������ʱ��>0 ��ʾ�ӵ� serial_cnt ���ϴ�, �����ʾ�ϴ��ɹ�����ˮ����
 \return ���� 0 ��ʾ�ɹ� �����󷵻ش�����
 */
int __stdcall KS_Upload_SerialRecord(const char *serial_date, int *serial_cnt)
{
	g_logger.writelog("���� KS_Upload_SerialRecord ���ܺ���");
#ifndef _DEBUG
	TEST_SYS_INIT;
#endif
	char serial_file_path[1025];
	int rec_cnt = 0;
	int ret, trade_money, out_money;
	int term_idx = 0;
	int time_out = 2000;
	char err_msg[512] = "";
	KS_Consume_Record record;
	//sprintf(serial_file_path,"%sserial\\rec_%s.log",g_module_path,"20071114");
	sprintf(serial_file_path, "%sserial\\rec_%s.log", g_module_path, serial_date);
	if (!do_check_file_exists(serial_file_path))
	{
		SetLastErr(ERR_NO_FILE, "��ˮ�ļ�������[%s]", serial_file_path);
		return ERR_NO_FILE;
	}
	{
		// ���������ر��ļ�
		KS_Record_File rec_reader(serial_file_path);
		do
		{
			memset(&record, 0, sizeof record);
			ret = rec_reader.read_record(&record);
			if (ret)
			{
				// �ļ���ȡ�ɹ�
				if (ERR_READ_EOF == ret)
					ret = 0;
				break;
			}
			if (rec_cnt < *serial_cnt)
			{
				rec_cnt++;
				continue;
			}
			//ret = 0;

			KS_YKT_Clt clt;
			clt.ResetHandler();
			// ������
			clt.SetIntFieldByName("lcert_code", 240202);
			// ���׿���
			clt.SetIntFieldByName("lvol0", record.card_id);
			// ��ʹ�ô���
			clt.SetIntFieldByName("lvol1", record.trade_count);
			// Ǯ����
			clt.SetIntFieldByName("lvol2", g_devices.devices[term_idx].purse_no);
			// ��ϵͳ��
			clt.SetIntFieldByName("lvol3", g_devices.devices[term_idx].sys_id);
			// �豸ID
			clt.SetIntFieldByName("lvol4", g_devices.devices[term_idx].device_id);
			// �ն���ˮ��
			clt.SetIntFieldByName("lvol5", record.serial_no);
			// �뿨ֵ
			clt.SetDoubleFieldByName("damt0", record.in_balance / 100.0);
			// ���׽��
			clt.SetDoubleFieldByName("damt1", record.trade_amount / 100.0);
			// ����Ա
			clt.SetStringFieldByName("scust_no", g_devices.devices[term_idx].oper_code);
			// ����
			clt.SetStringFieldByName("semp_pwd", "");
			// ������
			clt.SetStringFieldByName("sdate1", "");
			// ��������
			clt.SetStringFieldByName("sdate0", record.tx_date);
			clt.SetStringFieldByName("stime0", record.tx_time);
			g_logger.writelog("�ϴ���ˮserial[%d]card[%d]date[%s]time[%s]", record.serial_no, record.card_id
			                  , record.tx_date, record.tx_time);
			// ժҪ
			//clt.SetStringFieldByName("vsmess",pCardCons->Abstract);

			if (!clt.SendRequest(FUNC_CONSUME, time_out))
			{
				SetLastErr(ERR_FAIL, "������ʧ��,[%d]", FUNC_CONSUME);
				ret = ERR_FAIL;
			}
			//	pCardCons->RetCode = clt.GetReturnCode();
			if (clt.GetReturnCode())
			{
				clt.GetReturnMsg(err_msg);
				SetLastErr(ERR_FAIL, "������ʧ��,[%d],�ն���ˮ��[%d]������[%d][%s]"
				           , FUNC_CONSUME, record.serial_no, clt.GetReturnCode(), err_msg);
				return ERR_FAIL;
			}
			if (clt.HasMoreRecord())
			{
				clt.GetNextPackage();
				int trade_serial;
				double out_amt, trade_amt;
				clt.GetIntFieldByName("lvol0", &trade_serial);
				// �ɹ�����
				clt.GetIntFieldByName("lvol0", &trade_serial);
				clt.GetDoubleFieldByName("damt0", &out_amt);
				clt.GetDoubleFieldByName("damt1", &trade_amt);
				out_money = (int)d4u5(out_amt * 100.0);
				trade_money = (int)d4u5(trade_amt * 100.0);
				clt.ResetHandler();
				// ������
				clt.SetIntFieldByName("lcert_code", 240202);
				// ���׿���
				clt.SetIntFieldByName("lvol0", record.card_id);
				// ��ʹ�ô���
				clt.SetIntFieldByName("lvol1", record.trade_count);
				// Ǯ����
				clt.SetIntFieldByName("lvol2", g_devices.devices[term_idx].purse_no);
				// ��ϵͳ��
				clt.SetIntFieldByName("lvol3", g_devices.devices[term_idx].sys_id);
				// �豸ID
				clt.SetIntFieldByName("lvol4", g_devices.devices[term_idx].device_id);
				// �ն���ˮ��
				clt.SetIntFieldByName("lvol5", record.serial_no);
				// �뿨ֵ
				clt.SetDoubleFieldByName("damt0", record.in_balance / 100.0);
				// ���׽��
				clt.SetDoubleFieldByName("damt1", record.trade_amount / 100.0);
				// ����Ա
				clt.SetStringFieldByName("scust_no", g_devices.devices[term_idx].oper_code);
				// ����
				clt.SetStringFieldByName("semp_pwd", "");
				// ��̨��ˮ��
				clt.SetIntFieldByName("lvol6", trade_serial);
				// ��������
				clt.SetStringFieldByName("sdate0", record.tx_date);
				clt.SetStringFieldByName("stime0", record.tx_time);
				if (clt.SendRequest(FUNC_CONSUME_CONFIRM))
				{
					if (!clt.GetReturnCode())
					{
						g_logger.writelog("���׳ɹ������[%d]��,�����[%d], ��̨��ˮ��[%d]", trade_money
						                  , out_money, trade_serial);
						// ���߿�
						//HaltCard();
						ret = 0;
						rec_cnt++;
					}
					else
					{
						g_logger.writelog("����ʧ�ܣ�[%d ]����[%d],", FUNC_CONSUME_CONFIRM, clt.GetReturnCode());
						ret = ERR_FAIL;
					}
				}
				else
					SetLastErr(ERR_FAIL, "����ȷ��ʧ��");
			}
			else
			{
				SetLastErr(ERR_FAIL, "���ѽ���ʧ��");
				ret = ERR_FAIL;
			}
		}
		while (!ret);
	}
	// �ļ�������
	if (!ret)
	{
		char date_str[9] = "";
		char time_str[7] = "";
		char new_file_path[1025] = "";
		do
		{
			memset(new_file_path, 0, sizeof new_file_path);
			strcpy(new_file_path, serial_file_path);
			do_get_date_time(date_str, time_str);
			strcat(new_file_path, ".");
			strcat(new_file_path, date_str);
			strcat(new_file_path, time_str);
			if (do_check_file_exists(new_file_path))
			{
				Sleep(1000);
			}
			else
				break;
		}
		while (1);
		if (rename(serial_file_path, new_file_path))
		{
			SetLastErr(ERR_REFUSE, "������ˮʧ�ܣ���ˮ�ļ�[%s]", serial_file_path);
			ret = ERR_REFUSE;
		}
	}
	*serial_cnt = rec_cnt;
	return ret;
}
/*
  \brief �޸������ܺ�
  \param funcno �����ܺ�
 */
void __stdcall KS_Set_MainFunc(int funcno)
{
	g_logger.writelog("���� KS_Set_MainFunc , ���������ܺ�Ϊ %d", funcno);
	g_main_func = funcno;
}

/*
 \brief ������Ǯ
 \param amount - ���, ����������,��λΪ��, �������� 100000 ��
 \param bala - �������, ��ֵ�ɹ������
 \return ���� 0 ��ʾ�ɹ� , ʧ�ܷ��ش�����
 */
static int __stdcall KS_Card_Add_Money(int amount, int *bala)
{
	g_logger.writelog("���� KS_Card_Add_Money �ӿ�");
	TEST_COM_OPEN;
	int idx = 0;
	int card_id, ret, out_money;
	char card_serial_no[9] = "";
	MONEY_PACK_INFO purse_info;

	if (g_devices.devices[idx].flag | DEV_FLAG_ADD_MONEY)
	{
		SetLastErr(ERR_TRN_STATION, "�ն���Ȩ��ֵ");
		return ERR_TRN_STATION;
	}
	if (amount < 0 || amount > 100000)
	{
		SetLastErr(ERR_TA_TRANAMT, "�������!");
		return ERR_TA_TRANAMT;
	}

	card_id = 0;
	ret = ReadCardNO(&card_id);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "��ȡ����ʧ��!");
		return ERR_TA_READCARD;
	}
	ret = ReadSerial((unsigned char*)card_serial_no);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "��ȡ��������ID��ʧ��!");
		return ERR_TA_READCARD;
	}
	memset(&purse_info, 0, sizeof purse_info);
	ret = SMT_GetPacketInfo(g_devices.devices[idx].purse_no, &purse_info);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "����Ǯ��ʧ��,purse[%d]", g_devices.devices[idx].purse_no);
		return ERR_TA_READCARD;
	}

	// �������ֵ
	out_money = purse_info.bala + amount;

	int curr_card_id;
	ret = ReadCardNO(&curr_card_id);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "����д��ʧ��!");
		return ERR_TA_READCARD;
	}
	int retries = 3;
	ret = ERR_FAIL;

	while (retries-- > 0)
	{
		if (curr_card_id != card_id)
		{
			SetLastErr(ERR_TA_NOT_SAMECARD, "��ֵд�����Ų�һ��");
			return ERR_TA_NOT_SAMECARD;
		}
		ret = SMT_PacketSetMoney(g_devices.devices[idx].purse_no, out_money);
		if (!ret)
		{
			g_logger.writelog("��ֵ�ɹ�,cardid[%d],bala[%d],amount[%d]", card_id
			                  , out_money, amount);
			*bala = out_money;
			return 0;
		}
	}
	if (ret)
	{
		g_logger.writelog("��ֵд��ʧ��");
		ret = ERR_TA_WRITECARD;
	}
	return ret;
}

void __stdcall KS_Sleep_Card()
{
	HaltCard();
}