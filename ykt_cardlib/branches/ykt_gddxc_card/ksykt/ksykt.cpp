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
对应卡状态
*/
// 正常
#define ACC_FLAG_OK '0'
//
#define ACC_FLAG_SET '1'
#define ACC_FLAG_LOGOUT '2'

typedef struct
{
	int device_id;	// 设备ID
	int sys_id;		// 子系统号
	unsigned short term_no;	// 终端机号
	ULONG maxjnl;		// 终端流水号
	int purse_no;		// 终端交易钱包号
	int day_trade_limit; // 日交易累计限额
	int trade_limit_per_cnt; // 单次交易限额
	int flag;				// 标志
	int is_online;			// 是否联机
	char oper_code[11];		// 操作员
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
// CardDll 相关函数
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


// 设备列表
static sys_devices_t g_devices;
// 主功能号
#if 0
static int g_main_func = 9000;
#else 
static int g_main_func = 6000;
#endif

// 串口是否打开
static int g_com_open = 0;
// 工作密钥
static char g_workkey[33] = "";
static unsigned char g_hex_workhey[8] = "";
// 路径
static char g_module_path[1024] = "";
// 部门代码
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
//取错误信息
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
		g_logger.writelog("加载 carddll 失败");
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
	g_logger.writelog("加载 carddll 成功");

	strcpy(dll_path, g_module_path);
	strcat(dll_path, "desdll.dll");
	if ((g_des_module = LoadLibrary("desdll.dll")) == NULL)
	{
		g_logger.writelog("加载 desdll 失败");
		return -1;
	}
	LOAD_DLLFUNC(g_des_module, encrypt_des);
	LOAD_DLLFUNC(g_des_module, dencrypt_des);
	LOAD_DLLFUNC(g_des_module, encrypt_work_key);

	g_logger.writelog("加载 desdll 成功");
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
		da = (unsigned char)(crc / 256);			/* 以8位二进制数的形式暂存CRC的高8位 */
		crc <<= 8;						/* 左移8位，相当于CRC的低8位乘以 */
		b = pBuf[charcnt];				// 新移进来的字节值
		crc ^= crc16_tab[da ^ b];		/* 高8位和当前字节相加后再查表求CRC ，再加上以前的CRC */
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
	// 打开日志文件
	if (g_logger.openlog(log_path))
		return false;
	char xpack_path[1024] = "";
	strcpy(xpack_path, g_module_path);
	strcat(xpack_path, "cpack.dat");
	g_logger.writelog("加载 xpack [%s]", xpack_path);
	KS_YKT_Clt::set_xpack_path(xpack_path);
	if (do_load_carddll())
		return false;
	if (!load_dept_code_def())
	{
		g_logger.writelog("加载部门代码表失败");
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

// 检查
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
		SetLastErr(-1000, "系统初始化错误IP[%s]Port[%d]MainFunc[%d]", IP, port, g_main_func);
		return FALSE;
	}
	port = 4000;
	/////////////////// wenjian add////////////////////////////////////////////////////////
#if 0
//	if(port>8000)

	TerminalNo = 10;
#endif
	//////////////////////////////////////////////////////////////////////////
	g_logger.writelog("系统注册,参数IP[%s]Port[%d]MainFunc[%d]term[%d]", IP, port, g_main_func, TerminalNo);
	if (!KS_YKT_Clt::Initialize(IP, port, g_main_func))
	{
		SetLastErr(-1001, "初始化drtp错误IP[%s]Port[%d]MainFunc[%d]", IP, port, g_main_func);
		return FALSE;
	}
	idx = do_find_dev_by_termno(TerminalNo);
	clt.SetIntFieldByName("lcert_code", SysCode);
	clt.SetIntFieldByName("lvol0", TerminalNo);
	if (!clt.SendRequest(FUNC_ENROLL, 10000))
	{
		clt.GetReturnMsg(errmsg);
		SetLastErr(-1002, "发送请求849001失败IP[%s]Port[%d]MainFunc[%d][%s]"
		           , IP, port, g_main_func, errmsg);
		return FALSE;
	}
	ret_code = clt.GetReturnCode();
	if (ret_code)
	{
		SetLastErr(-1003, "发送请求849001返回失败IP[%s]Port[%d]MainFunc[%d]retcode[%d]", IP, port, g_main_func, ret_code);
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
		// 联机
		g_devices.devices[idx].is_online = DEV_TERM_ONLINE;
		// 检查允许消费开关
		int consume_flag = 0;
		clt.GetIntFieldByName("lvol5", &consume_flag);
		if (consume_flag)
		{
			g_devices.devices[idx].flag |= DEV_FLAG_CONSUM;
		}
		*MaxJnl = g_devices.devices[idx].maxjnl;
		*ProxyOffline = false;
		// 保存 hex 密钥(密文)
		str2hex(g_workkey, 16, g_hex_workhey);
		if (Load_WorkKey(g_workkey))
		{
			SetLastErr(-1004, "发送请求849001返回成功，但是装载工作密钥失败");
			return FALSE;
		}
		g_logger.writelog("签到成功,termno[%d],serialno[%d]", g_devices.devices[idx].device_id
		                  , g_devices.devices[idx].maxjnl);
		return TRUE;
	}
	else
	{
		SetLastErr(-1005, "发送请求849001返回无记录");
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
		g_logger.writelog("打开读卡器成功！");
		return ERR_OK;
	}
	g_logger.writelog("打开读卡器失败！");
	return ERR_FAIL;
}

BOOL CALLAPI TA_CRClose(void)
{
	if (g_com_open)
	{
		g_com_open = 0;
		if (CloseMF())
			return FALSE;
		g_logger.writelog("关闭读卡器成功！");
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
		//SetLastErr(ERR_TA_READCARD,"读卡序列号失败");
		return ERR_TA_READCARD;
	}

	ret = do_convert_card_phyno(serial_no, CardNo);
	if (ret)
		return ERR_TA_READCARD;
	g_logger.writelog("读取卡序列号[%d]", *CardNo);
	return ERR_OK;
}

int CALLAPI TA_ReadCardSimple(AccountMsg * pAccMsg)
{
	g_logger.writelog("调用 TA_ReadCardSimple 函数");
	TEST_COM_OPEN;
	int ret;
	TPublishCard2 card;
	memset(&card, 0, sizeof card);

	ret = ReadCardInfo2(&card);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读卡失败！");
		return ERR_TA_READCARD;
	}
	int cardid = atoi((char*)card.CardNo);
	if (cardid <= 0)
		return ERR_TA_READCARD;
	// TODO : 物理卡号格式
	ret = TA_FastGetCardNo(&(pAccMsg->CardNo));
	if (ret != ERR_OK)
	{
		SetLastErr(ret, "读卡物理ID失败");
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
	g_logger.writelog("读取卡号成功,cut[%d]balance[%d]", card.cut_id, pAccMsg->Balance);
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
		SetLastErr(ERR_COMM_FAIL, "请求后台功能[%d]失败", FUNC_QUERY_USER_INFO);
		return ERR_COMM_FAIL;
	}
	if (clt.GetReturnCode())
	{
		SetLastErr(ERR_FAIL, "请求后台功能[%d]错误,返回[%d]", FUNC_QUERY_USER_INFO
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
	SetLastErr(ERR_FAIL, "请求后台功能[%d]无返回数据", FUNC_QUERY_USER_INFO);
	return -1;
}

int CALLAPI TA_CheckWL (unsigned int AccountNo , unsigned int CardNo , bool CheckID = true)
{
	g_logger.writelog("调用 TA_CheckWL 函数");
	TEST_SYS_INIT;
	int ret;
	AccountMsg acc;
	char serial_no[9] = "";
	if (AccountNo <= 0)
	{
		SetLastErr(ERR_TA_CARDNO, "输入帐号不能为空！");
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
		SetLastErr(ERR_COMM_FAIL, "请求[%d]失败", 847173);
		return ERR_COMM_FAIL;
	}
	else if (clt.GetReturnCode())
	{
		SetLastErr(ERR_COMM_FAIL, "请求[%d]失败,ret[%d]", 847173, clt.GetReturnCode());
		return ERR_FAIL;
	}
	if (clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		char state_id[5] = "";
		GET_PACK_STR(clt, "sbank_code", state_id);
		g_logger.writelog("查询系统卡状态");
		do_card_state_to_flag(state_id, acc.Flag, '2');
		ret = ERR_OK;
	}
	return ret;
}

int CALLAPI TA_ReadCard(AccountMsg *pAccMsg, bool CheckID = true , bool CheckSub = false)
{
	g_logger.writelog("调用 TA_ReadCard 函数");
	AccountMsg acc;
	int ret;
	memset(&acc, 0, sizeof acc);
	TEST_COM_OPEN;
	TPublishCard2 card;
	memset(&card, 0, sizeof card);

	ret = ReadCardInfo2(&card);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读卡信息失败！ret[%d]", ret);
		return ERR_TA_READCARD;
	}
	int cardid = atoi((char*)card.CardNo);
	if (cardid <= 0)
	{
		SetLastErr(ERR_TA_READCARD, "读取交易卡号失败!");
		return ERR_TA_READCARD;
	}
	// TODO : 物理卡号格式
	ret = TA_FastGetCardNo(&(acc.CardNo));
	if (ret != ERR_OK)
	{
		SetLastErr(ret, "读卡物理ID失败");
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
		SetLastErr(ERR_COMM_FAIL, "请求[%d]失败", 847173);
		return ERR_COMM_FAIL;
	}
	else if (clt.GetReturnCode())
	{
		SetLastErr(ERR_COMM_FAIL, "请求[%d]失败,ret[%d]", 847173, clt.GetReturnCode());
		return ERR_FAIL;
	}
	if (clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		char state_id[5] = "";
		GET_PACK_STR(clt,"sbank_code",state_id);
		g_logger.writelog("查询系统卡状态cardid[%d]",cardid);
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
	//g_logger.writelog("读取卡信息 cut [%d] [%s] ",pAccMsg->AccountNo,pAccMsg->Password);
	return ret;
}
//int CALLAPI TA_Charge(char *pCardCharg, bool IsVerfy, short TimeOut=10)

int CALLAPI TA_Consume(CardConsume *pCardCons, bool IsVerfy, short TimeOut = 10)
{
	g_logger.writelog("调用  TA_Consume ");
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


	//g_logger.writelog("调用  TA_Consume 判断参数合法性");
	TimeOut = (TimeOut > 0 && TimeOut < 30) ? TimeOut : 10;
	TimeOut *= 1000;

	if (pCardCons->TranAmt >= 0)
	{
		return ERR_TA_TRANAMT;
	}

	term_idx = do_find_dev_by_termno(pCardCons->TerminalNo);
	if (term_idx < 0)
	{
		SetLastErr(ERR_TRN_STATION, "终端未授权");
		return ERR_TRN_STATION;
	}

	if ((g_devices.devices[term_idx].flag & DEV_FLAG_CONSUM) == 0)
	{
		SetLastErr(ERR_TRN_STATION, "终端不允许消费!");
		return ERR_TRN_STATION;
	}
	if ((g_devices.devices[term_idx].is_online & DEV_TERM_ONLINE) == 0)
	{
		SetLastErr(ERR_TRN_STATION, "脱机设备，不允许实时交易!请使用脱机交易!");
		return ERR_TRN_STATION;
	}
	if ((pCardCons->TranAmt* -1) >= g_devices.devices[term_idx].trade_limit_per_cnt)
	{
		if (strlen(pCardCons->PassWord) == 0)
		{
			SetLastErr(ERR_TA_EXCEED_QUOTA, "单次消费金额超过限制");
			return ERR_TA_EXCEED_QUOTA;
		}
	}
	if (pCardCons->TranJnl < g_devices.devices[term_idx].maxjnl)
	{
		SetLastErr(ERR_TA_PARA, "消费终端流水号不正确,输入值[%d]", pCardCons->TranJnl);
		return ERR_TA_PARA;
	}
	ret = ReadCardNO(&card_id);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读取卡号失败!");
		return ERR_TA_READCARD;
	}
	ret = ReadSerial((unsigned char*)card_serial_no);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读取卡号物理ID号失败!");
		return ERR_TA_READCARD;
	}
	memset(&purse_info, 0, sizeof purse_info);
	ret = SMT_GetPacketInfo(g_devices.devices[term_idx].purse_no, &purse_info);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读卡钱包失败");
		return ERR_TA_READCARD;
	}
	if (purse_info.bala + pCardCons->TranAmt < 0)
	{
		return ERR_TA_TRANAMT;
	}
	// 比较日期
	do_get_date_time(now_date, now_time);
	sprintf(last_trade_date, "20%02d%02d%02d", purse_info.date / 10000 % 100
	        , purse_info.date / 100 % 100, purse_info.date % 100);
	if (strcmp(last_trade_date, now_date) == 0)
	{
		if (purse_info.daybala - pCardCons->TranAmt > g_devices.devices[term_idx].day_trade_limit)
		{
			if (strlen(pCardCons->PassWord) == 0)
			{
				SetLastErr(ERR_TA_EXCEED_QUOTA, "日累计金额超过限制");
				return ERR_TA_EXCEED_QUOTA;
			}
		}
	}

	KS_YKT_Clt clt;
	// 请求交易
	clt.SetIntFieldByName("lcert_code", 240202);
	// 交易卡号
	clt.SetIntFieldByName("lvol0", card_id);
	// 卡使用次数
	clt.SetIntFieldByName("lvol1", purse_info.total_cnt);
	// 钱包号
	clt.SetIntFieldByName("lvol2", g_devices.devices[term_idx].purse_no);
	// 子系统号
	clt.SetIntFieldByName("lvol3", g_devices.devices[term_idx].sys_id);
	// 设备ID
	clt.SetIntFieldByName("lvol4", g_devices.devices[term_idx].device_id);
	// 终端流水号
	clt.SetIntFieldByName("lvol5", pCardCons->TranJnl);
	// 入卡值
	clt.SetDoubleFieldByName("damt0", purse_info.bala / 100.0);
	// 交易金额
	clt.SetDoubleFieldByName("damt1", (pCardCons->TranAmt * -1) / 100.0);
	// 操作员
	clt.SetStringFieldByName("scust_no", g_devices.devices[term_idx].oper_code);
	// 密码
	clt.SetStringFieldByName("semp_pwd", pCardCons->PassWord);
	// 物理卡号
	clt.SetStringFieldByName("sdate1", card_serial_no);
	// 交易日期
	clt.SetStringFieldByName("sdate0", now_date);
	clt.SetStringFieldByName("stime0", now_time);
	// 摘要
	//clt.SetStringFieldByName("vsmess",pCardCons->Abstract);

	if (!clt.SendRequest(FUNC_CONSUME, TimeOut))
	{
		SetLastErr(ERR_FAIL, "请求交易失败,[%d]", FUNC_CONSUME);
		ret = ERR_FAIL;
	}
	pCardCons->RetCode = clt.GetReturnCode();
	if (clt.GetReturnCode())
	{
		clt.GetReturnMsg(err_msg);
		SetLastErr(ERR_FAIL, "请求交易失败,[%d],终端流水号[%d]返回码[%d][%s]"
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
			SetLastErr(ERR_TA_READCARD, "请求后台交易返回写卡失败!");
			return ERR_TA_READCARD;
		}
		int retries = 3;
		ret = ERR_FAIL;
		while (retries-- > 0)
		{
			if (curr_card_id != card_id)
			{
				SetLastErr(ERR_TA_NOT_SAMECARD, "消费写卡卡号不一致,后台流水号[%d]", trade_serial);
				return ERR_TA_NOT_SAMECARD;
			}
			ret = SMT_PacketSetMoney(g_devices.devices[term_idx].purse_no, out_money);
			if (!ret)
				break;
		}
		if (ret)
		{
			g_logger.writelog("消费写卡失败,后台流水号[%d]", trade_serial);
			return ERR_TA_WRITECARD;
		}
		clt.ResetHandler();
		// 请求交易
		clt.SetIntFieldByName("lcert_code", 240202);
		// 交易卡号
		clt.SetIntFieldByName("lvol0", card_id);
		// 卡使用次数
		clt.SetIntFieldByName("lvol1", purse_info.time_cnt);
		// 钱包号
		clt.SetIntFieldByName("lvol2", g_devices.devices[term_idx].purse_no);
		// 子系统号
		clt.SetIntFieldByName("lvol3", g_devices.devices[term_idx].sys_id);
		// 设备ID
		clt.SetIntFieldByName("lvol4", g_devices.devices[term_idx].device_id);
		// 终端流水号
		clt.SetIntFieldByName("lvol5", pCardCons->TranJnl);
		// 入卡值
		clt.SetDoubleFieldByName("damt0", purse_info.bala / 100.0);
		// 交易金额
		clt.SetDoubleFieldByName("damt1", (pCardCons->TranAmt * -1) / 100.0);
		// 操作员
		clt.SetStringFieldByName("scust_no", g_devices.devices[term_idx].oper_code);
		// 密码
		clt.SetStringFieldByName("semp_pwd", pCardCons->PassWord);
		// 后台流水号
		clt.SetIntFieldByName("lvol6", trade_serial);
		// 交易日期
		clt.SetStringFieldByName("sdate0", now_date);
		clt.SetStringFieldByName("stime0", now_time);
		if (clt.SendRequest(FUNC_CONSUME_CONFIRM))
		{
			if (!clt.GetReturnCode())
			{
				pCardCons->TranAmt = trade_money;
				pCardCons->BackJnl = trade_serial;
				pCardCons->CardBalance = out_money;
				g_logger.writelog("交易成功，金额[%d]分,卡余额[%d], 后台流水号[%d]", trade_money
				                  , out_money, trade_serial);
				// 休眠卡
				//HaltCard();
				return ERR_OK;
			}
			g_logger.writelog("交易失败，[%d ]返回[%d],", FUNC_CONSUME_CONFIRM, clt.GetReturnCode());
			pCardCons->RetCode = clt.GetReturnCode();
		}
		else
			SetLastErr(ERR_FAIL, "交易确认失败");
	}
	SetLastErr(ERR_FAIL, "消费交易失败");
	return ERR_FAIL;

}
// 精确查询客户信息
int CALLAPI TA_InqAcc(AccountMsg * pAccMsg, short TimeOut = 10)
{
	g_logger.writelog("调用  TA_InqAcc ");
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
		SetLastErr(ERR_TA_PARA, "调用参数错误");
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
		SetLastErr(ERR_COMM_FAIL, "发送请求失败[%d][%s]", FUNC_QUERY_USER_INFO, errmsg);
		return ERR_COMM_FAIL;
	}
	if (clt.GetReturnCode())
	{
		clt.GetReturnMsg(errmsg);
		SetLastErr(ERR_FAIL, "发送请求失败[%d],返回失败[%d][%s]"
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
		g_logger.writelog("查询客户信息cutid[%d]", pAccMsg->AccountNo);
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
// 模糊查询信息
int CALLAPI TA_HazyInqAcc(AccountMsg *pAccMsg, int *RecNum , char *FileName
                          , short TimeOut = 10)
{
	g_logger.writelog("调用  TA_HazyInqAcc ");
	/*
	if(FileName == NULL || strlen(FileName) == 0)
	{
		SetLastErr(ERR_TA_PARA,"输入文件名不正确!");
		return ERR_TA_PARA;
	}
	*/
	do_get_current_time(FileName);
	char full_path[1024] = "";
	sprintf(full_path, "%sRecvTemp\\", g_module_path);
	if (do_create_dir(full_path))
	{
		SetLastErr(ERR_FAIL, "创建目录失败[%s]", full_path);
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
		// 删除文件
		if (unlink(FileName) == -1)
			return ERR_DEL_FAIL;
	}
	if ((fp = fopen(full_path, "wb+")) == NULL)
	{
		SetLastErr(ERR_REFUSE, "打开文件失败");
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
			SetLastErr(ret, "查询[%d]返回错误[%d]", FUNC_QUERY_USER_INFO,
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
				// 写入文件
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
	g_logger.writelog("查询人员信息返回[%d],返回记录数[%d]", ret, rec_cnt);
	return ret;
}

int CALLAPI TA_DownControlFile(short timeOut = 10)
{
	g_logger.writelog("调用  TA_DownControlFile ");
	char full_path[1024] = "";
	char temp[] = "dummy";
	FILE *fp;
	strcpy(full_path, g_module_path);
	strcat(full_path, "ControlFile\\");
	if (do_create_dir(full_path))
	{
		g_logger.writelog("创建目录失败[%s]", full_path);
		return ERR_COMM_FAIL;
	}
	strcat(full_path, "Control.bin");
	if (do_check_file_exists(full_path))
	{
		return 1;
	}
	if ((fp = fopen(full_path, "w+")) == NULL)
	{
		SetLastErr(ERR_COMM_FAIL, "创建 Control.bin 文件失败");
		return ERR_COMM_FAIL;
	}
	fwrite(temp, strlen(temp), 1, fp);
	fclose(fp);
	return 1;
}

BOOL CALLAPI TA_ExtractConFile(const int readrec , const char * fn)
{
	g_logger.writelog("调用 TA_ExtractConFile 函数 rec[%d]", readrec);
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
		g_logger.writelog("创建 ControlFile 目录失败!");
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
	case OFFSET_T_DEPARTMENT:	/* 部门组织表 */
		dict_no = 3001;
		break;
	case OFFSET_T_PID:			/* 身份代码表 */
		dict_no = 3000;
		break;
	case OFFSET_T_IDTYPE:		/* 证件类型表 */
		dict_no = 87;
		break;
	case OFFSET_T_PEOPLE:		/* 民族表 */
		dict_no = 2001;
		break;
	case OFFSET_T_NATION:		/* 国籍表 */
		dict_no = 89;
		break;
	case OFFSET_T_ZZMM:			/* 政治面貌 */
		break;
	case OFFSET_SCHOOLCODE:		/* 0:学校代码SchoolCode*/
	case OFFSET_T_AREA:			/* 校/厂区代码表 */
		dict_no = -27;
		break;
	case OFFSET_T_SS_YUAN:		/* 宿舍（苑/栋 */
	case OFFSET_T_WHCD:			/* 文化程度 */
	case OFFSET_T_CARDTYPE:     /* 卡样管理表 */
	case OFFSET_T_JSZC:			/* 技术职称 */
	case OFFSET_T_XZZW:			/* 行政职务 */

	case OFFSET_SUBJECT:		/* 1:日报字典Subject*/
	case OFFSET_FEE:			/* 2:操作费用设定表fee*/
	case OFFSET_CONFIGINFO:		/* 3:各种代码字典ConfigInfo*/
	case OFFSET_BRANCH:			/* 4:商户部门表branch*/
	case OFFSET_CSZD:			/* 5:系统参数cszd*/
	case OFFSET_TRCD:			/* 6:事件代码表trcd*/
	case OFFSET_MESSAGE:		/* 7:系统信息表message*/
	default:
		return FALSE;
	}
	if (dict_no == -1)
		return FALSE;

	clt.SetIntFieldByName("lcert_code", dict_no);
	clt.SetStringFieldByName("scust_auth", g_devices.devices[0].oper_code);
	if (!clt.SendRequest(FUNC_READ_DICT, 20000))
	{
		SetLastErr(ERR_FAIL, "请求功能失败,供能号[%d]", FUNC_READ_DICT);
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
		case OFFSET_T_DEPARTMENT:	/* 部门组织表 */
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
		case OFFSET_T_IDTYPE:		/* 证件类型表 */
			dict_no = 87;
			memset(&idtype, 0, sizeof idtype);
			src2des(idtype.idtype_code, dict_value);
			src2des(idtype.idtype_name, dict_caption);
			src2des(idtype.idtype_easycode, idtype.idtype_code);
			pdata = &idtype;
			data_len = sizeof(idtype);
			fprintf(fp, "%s,%s,%s\n", idtype.idtype_code, idtype.idtype_name, idtype.idtype_easycode);
			break;
		case OFFSET_T_PEOPLE:		/* 民族表 */
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
		case OFFSET_T_NATION:		/* 国籍表 */
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
		case OFFSET_T_AREA:			/* 校/厂区代码表 */
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
		case OFFSET_T_PID:			/* 身份代码表 */
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
		case OFFSET_T_ZZMM:			/* 政治面貌 */
		case OFFSET_T_SS_YUAN:		/* 宿舍（苑/栋 */
		case OFFSET_T_WHCD:			/* 文化程度 */
		case OFFSET_T_CARDTYPE:     /* 卡样管理表 */
		case OFFSET_T_JSZC:			/* 技术职称 */
		case OFFSET_T_XZZW:			/* 行政职务 */
		case OFFSET_SUBJECT:		/* 1:日报字典Subject*/
		case OFFSET_FEE:			/* 2:操作费用设定表fee*/
		case OFFSET_CONFIGINFO:		/* 3:各种代码字典ConfigInfo*/
		case OFFSET_BRANCH:			/* 4:商户部门表branch*/
		case OFFSET_CSZD:			/* 5:系统参数cszd*/
		case OFFSET_TRCD:			/* 6:事件代码表trcd*/
		case OFFSET_MESSAGE:		/* 7:系统信息表message*/
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
	g_logger.writelog("调用 TA_CardLost 函数");
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
		SetLastErr(ERR_FAIL, "挂失失败，返回[%d]", clt.GetReturnCode());
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
			// 需要增补
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
	g_logger.writelog("调用 TA_Refund 函数");
	return ERR_FAIL;
}

int CALLAPI TA_CardOpen(CardOperating *pCardOper, short TimeOut = 10)
{
	g_logger.writelog("调用 TA_CardOpen 函数");
	return ERR_OK;
}
int CALLAPI TA_CardClose(CardOperating *pCardOper, short TimeOut = 10)
{
	g_logger.writelog("调用 TA_CardClose 函数");
	return ERR_OK;
}
int CALLAPI TA_PermitID(CardOperating *pCardOper, short TimeOut = 10)
{
	g_logger.writelog("调用 TA_PermitID 函数");
	return ERR_OK;
}
int CALLAPI TA_ProhibitID(CardOperating *pCardOper, short TimeOut = 10)
{
	g_logger.writelog("调用 TA_ProhibitID 函数");
	return ERR_OK;
}

int CALLAPI TA_InqTranFlow(InqTranFlow *pInqTranFlow, short TimeOut = 10)
{
	g_logger.writelog("调用 TA_InqTranFlow 函数");
	return ERR_FAIL;
}
int CALLAPI TA_HazyInqAccEx(AccountMsg *pAccMsg, int *RecNum , char *FileName, short TimeOut = 10)
{
	g_logger.writelog("调用 TA_HazyInqAccEx 函数");
	return ERR_FAIL;
}
int CALLAPI TA_InqAccEx(AccountMsgEx * pAccMsg, short TimeOut = 10)
{
	g_logger.writelog("调用 TA_InqAccEx 函数");
	return ERR_FAIL;
}
int CALLAPI TA_InqAccByDeptClass(char *DeptCode, char *InYear, int *RecNum , char *FileName , short TimeOut = 10)
{
	g_logger.writelog("调用 TA_InqAccByDeptClass 函数");
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
	SetLastErr(ERR_FAIL, "函数 TA_UpJournal 不支持");
	return ERR_FAIL;
}


int _stdcall TA_InqOpenFlow(InqOpenFlow *pInqOpenFlow, short TimeOut)
{
	SetLastErr(ERR_FAIL, "函数 TA_InqOpenFlow 不支持");
	return ERR_FAIL;
}
int _stdcall TA_Dsql_ORecord(const char *Dsql ,
                             int * nReturn ,
                             short timeOut)
{
	SetLastErr(ERR_FAIL, "函数 TA_Dsql_ORecord 不支持");
	return ERR_FAIL;
}

int _stdcall TA_Dsql_QRecord(const char *Dsql ,
                             int * nReturn ,
                             short timeOut)
{
	SetLastErr(ERR_FAIL, "函数 TA_Dsql_QRecord 不支持");
	return ERR_FAIL;
}

int WINAPI TA_BussComm(char* sendBuf,
                       int sendLen,
                       char * recvBuf,
                       int *recvLen,
                       char priority,
                       short timeOut = 10)
{
	g_logger.writelog("调用 TA_BussComm 函数");
	strncpy(recvBuf, sendBuf, sendLen);
	*recvLen = sendLen;
	return ERR_OK;
}

int __stdcall NC_BussComm()
{
	g_logger.writelog("调用 NC_BussComm 函数");
	return ERR_FAIL;
}

int __stdcall NC_UpLoadFile()
{
	g_logger.writelog("调用 NC_UpLoadFile 函数");
	return ERR_FAIL;
}

int __stdcall NC_DownLoadFile()
{
	g_logger.writelog("调用 NC_DownLoadFile 函数");
	return ERR_FAIL;
}

int WINAPI NC_DownControlFile(char * IP, short port, short timeOut)
{
	g_logger.writelog("调用 NC_DownControlFile 函数");
	return ERR_FAIL;
}

int __stdcall DSQL_Query_File()
{
	g_logger.writelog("调用 DSQL_Query_File 函数");
	return ERR_FAIL;
}

int __stdcall DSQL_Query_Record()
{
	g_logger.writelog("调用 DSQL_Query_Record 函数");
	return ERR_FAIL;
}

int __stdcall DSQL_Oper_Record()
{
	g_logger.writelog("调用 DSQL_Oper_Record 函数");
	return ERR_FAIL;
}

int __stdcall G_GetAPIPath()
{
	g_logger.writelog("调用 G_GetAPIPath 函数");
	return ERR_FAIL;
}

int __stdcall G_Chg_NodeID()
{
	g_logger.writelog("调用 G_Chg_NodeID 函数");
	return ERR_FAIL;
}

int __stdcall EC_GetCfg()
{
	g_logger.writelog("调用 EC_GetCfg 函数");
	return ERR_FAIL;
}

int __stdcall G_PW_Encrypt()
{
	g_logger.writelog("调用 G_PW_Encrypt 函数");
	return ERR_FAIL;
}

int __stdcall G_PW_Decrypt()
{
	g_logger.writelog("调用 G_PW_Decrypt 函数");
	return ERR_FAIL;
}

int __stdcall NC_DownPhotoFile()
{
	g_logger.writelog("调用 NC_DownPhotoFile 函数");
	return ERR_FAIL;
}

//////////////////////////////////////////////////////////////////////////
// 增加广州大学城 脱机使用的接口
/*
 \brief 脱机授权读卡器使用
 \param sysid - 读卡器所属的
 \param termid - 读卡器分配的设备ID号
 \param maxjnl - 设备初始流水号
 \return 返回 0 表示成功, 失败返回错误码
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
		g_logger.writelog("读取授权卡失败，返回[%d]", ret);
		return ERR_READ_AUTH_CARD;
	}

	if (auth_flag & KS_ACR_AUTH_TERM)
	{
		g_logger.writelog("终端允许认证");
		term_flag |= DEV_FLAG_LOGIN;
	}
	if (auth_flag & KS_ACR_CONSUME_TERM)
	{
		g_logger.writelog("终端允许消费");
		term_flag |= DEV_FLAG_CONSUM | DEV_FLAG_LOGIN;
	}

	if (auth_flag & KS_ACR_ADD_MONEY_TERM)
	{
		g_logger.writelog("终端允许充值");
		term_flag |= DEV_FLAG_ADD_MONEY | DEV_FLAG_LOGIN;
	}
	if (term_flag == 0)
	{
		g_logger.writelog("此授权卡无权限");
		return ERR_AUTHCARD_RIGHT;
	}

	g_devices.devices[idx].device_id = 0;
	g_devices.devices[idx].maxjnl = 1;
	//hex2dec(g_workkey,auth_key,8);
	g_devices.devices[idx].purse_no = 1;
	// 限制次消费限额
	g_devices.devices[idx].trade_limit_per_cnt = 3000;
	g_devices.devices[idx].day_trade_limit = 5000;
	src2des(g_devices.devices[idx].oper_code, "system");

	g_devices.devices[idx].term_no = 0;
	g_devices.devices[idx].device_id = termid;
	g_devices.devices[idx].sys_id = sysid;
	g_devices.devices[idx].flag = term_flag;
	// 脱机
	g_devices.devices[idx].is_online = DEV_TERM_OFFLINE;

	//*maxjnl = g_devices.devices[idx].maxjnl;
	g_devices.devices[idx].maxjnl = maxjnl;
	memcpy(g_hex_workhey, auth_key, sizeof g_hex_workhey);
	encrypt_work_key(auth_key, g_hex_workhey);

	if (SetCardMainKey(auth_key))
	{
		SetLastErr(ERR_AUTH_FAILED, "装载工作密钥失败");
		return ERR_AUTH_FAILED;
	}
	ControlBuzzer();
	g_logger.writelog("授权终端脱机使用");
	return 0;
}

#pragma  pack(1)
struct KS_Consume_Record
{
	/*
	流水文件格式	长度(字符)
	交易日期			8
	交易时间			6
	终端号				4		unsigned short
	子系统号			8		int
	交易流水号			8		int
	交易卡号			8		int
	入卡值				8		int
	金额				8		int 消费为正，冲正为负
	卡交易次数			4		unsigned short
	交易标志			2		byte

	总长度 64 个字符
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
		SetLastErr(ERR_NO_FILE, "记录流水失败，文件无法访问!");
		return ERR_NO_FILE;
	}
	// 将文件指针定位到结尾
	if (fseek(record_file_, 0L, SEEK_END))
	{
		SetLastErr(ERR_FILESTAT, "定位流水文件失败！");
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
		g_logger.writelog("记录流水，长度[%d]", buf_len);

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
			SetLastErr(ERR_FAIL, "写流水文件失败[%s]", file_path_);
			return ERR_FAIL;
		}
	}
	while (written_len < enc_len);
	// 更新流水文件长度
	rec_file_len_ += written_len;
	g_logger.writelog("记录流水，交易日期[%s]时间[%s]卡号[%d]金额[%d]"
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
			// 不足补字节
			memset(temp + left_len, (unsigned char)pad_len, pad_len);
		}
		else
		{
			memcpy(temp, buf + offset, s_block_len_);
		}
		ret = encrypt_des(g_hex_workhey, 8, temp, s_block_len_, enc_buf + offset);
		if (ret)
		{
			SetLastErr(ERR_ENCRYPT_ERR, "加密数据块错误,ret[%d]", ret);
			return ERR_ENCRYPT_ERR;
		}
		offset += s_block_len_;
	}
	while (offset < len);
	if (offset % s_block_len_ != 0)
	{
		SetLastErr(ERR_ENCRYPT_ERR, "加密数据块错误,加密后长度[%d]不正确", offset);
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
			SetLastErr(ERR_DECRYPT_ERR, "加密数据块错误,ret[%d]", ret);
			return ERR_DECRYPT_ERR;
		}
		offset += s_block_len_;
	}
	while (offset < len);

	if (offset % s_block_len_ != 0)
	{
		SetLastErr(ERR_DECRYPT_ERR, "解密数据块错误,解密后长度[%d]不正确", offset);
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
		SetLastErr(ERR_NO_FILE, "记录流水失败，文件无法访问!");
		return ERR_NO_FILE;
	}

	offset = enc_len * read_idx_;
	if (offset >= rec_file_len_)
	{
		return ERR_READ_EOF;
	}
	if (offset + enc_len > rec_file_len_)
	{
		// 文件不完整
		g_logger.writelog("流水文件[%s]不完整!");
		return ERR_READ_EOF;
	}
	if (fseek(record_file_, offset, SEEK_SET))
	{
		SetLastErr(ERR_FILESTAT, "定位流水文件失败！");
		return ERR_FILESTAT;
	}
	if (feof(record_file_))
	{
		return ERR_READ_EOF;
	}
	// 读取数据
	do
	{
		int rlen = fread(enc_record + read_len, 1, enc_len - read_len, record_file_);
		if (rlen > 0)
			read_len += rlen;
		else if (rlen <= 0)
		{
			SetLastErr(ERR_FAIL, "读流水文件失败[%s]", file_path_);
			return ERR_FAIL;
		}
	}
	while (read_len < enc_len);
	/*
	if(fread(enc_record,enc_len,1,record_file_) != 1)
	{
		SetLastErr(ERR_FAIL,"读流水文件失败[%s]",file_path_);
		return ERR_FAIL;
	}
	*/
	// 解密
	ret = decode_buf(enc_record, enc_len, record_buf, &buf_len);
	if (ret)
	{
		return ret;
	}
	// 校验 crc
	crc = GenerateCRC16((unsigned char*)record_buf, s_record_len_ - 4);
	sprintf(temp, "%04X", crc);
	if (strncmp(temp, record_buf + s_record_len_ -4, 4) != 0)
	{
		SetLastErr(ERR_SERIAL_CRC, "读取流水，校验 CRC 错误");
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
 \brief 脱机消费接口
 \param pCardCons - 消费参数，定义同 TA_Consume
 \param RecFile - 输出参数，记录流水保存的文件名(完整路径，1024 个字节)
 \return 返回 0 表示成功， 错误返回错误码
 */
int __stdcall KS_Offline_Consume(CardConsume *pCardCons, char *RecFile)
{
	g_logger.writelog("调用  KS_Offline_Consume ");
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
		SetLastErr(ERR_TRN_STATION,"终端未授权");
		return ERR_TRN_STATION;
	}
	*/
	term_idx = 0;

	if ((g_devices.devices[term_idx].flag & DEV_FLAG_CONSUM) == 0)
	{
		SetLastErr(ERR_TRN_STATION, "终端不允许消费!");
		return ERR_TRN_STATION;
	}
	if ((g_devices.devices[term_idx].is_online & DEV_TERM_OFFLINE) == 0)
	{
		SetLastErr(ERR_TRN_STATION, "脱机设备，不允许实时交易!请使用脱机交易!");
		return ERR_TRN_STATION;
	}
	if ((pCardCons->TranAmt* -1) >= g_devices.devices[term_idx].trade_limit_per_cnt)
	{
		if (strlen(pCardCons->PassWord) == 0)
		{
			SetLastErr(ERR_TA_EXCEED_QUOTA, "单次消费金额超过限制");
			return ERR_TA_EXCEED_QUOTA;
		}
	}
	if (pCardCons->TranJnl < g_devices.devices[term_idx].maxjnl)
	{
		SetLastErr(ERR_TA_PARA, "消费终端流水号不正确,输入值[%d]", pCardCons->TranJnl);
		return ERR_TA_PARA;
	}
	ret = ReadCardNO(&card_id);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读取卡号失败!");
		return ERR_TA_READCARD;
	}
	ret = ReadSerial((unsigned char*)card_serial_no);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读取卡号物理ID号失败!");
		return ERR_TA_READCARD;
	}
	memset(&purse_info, 0, sizeof purse_info);
	ret = SMT_GetPacketInfo(g_devices.devices[term_idx].purse_no, &purse_info);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读卡钱包失败,purse[%d]", g_devices.devices[term_idx].purse_no);
		return ERR_TA_READCARD;
	}
	if (purse_info.bala + pCardCons->TranAmt < 0)
	{
		return ERR_TA_TRANAMT;
	}
	// 比较日期
	do_get_date_time(now_date, now_time);
	sprintf(last_trade_date, "20%02d%02d%02d", purse_info.date / 10000 % 100
	        , purse_info.date / 100 % 100, purse_info.date % 100);
	if (strcmp(last_trade_date, now_date) == 0)
	{
		if (purse_info.daybala - pCardCons->TranAmt > g_devices.devices[term_idx].day_trade_limit)
		{
			if (strlen(pCardCons->PassWord) == 0)
			{
				SetLastErr(ERR_TA_EXCEED_QUOTA, "日累计金额超过限制");
				return ERR_TA_EXCEED_QUOTA;
			}
		}
	}

	/// 开始交易，记录流水文件


	sprintf(serial_file_path, "%sserial", g_module_path);
	if (do_create_dir(serial_file_path))
	{
		SetLastErr(ERR_REFUSE, "创建目录失败[%s]", serial_file_path);
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
	// 尝试加密
	ret = rec_writter.write_record(&record, 1);
	if (ret)
	{
		SetLastErr(ret, "测试流水失败");
		return ret;
	}
	int curr_card_id;
	ret = ReadCardNO(&curr_card_id);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "返回写卡失败!");
		return ERR_TA_READCARD;
	}
	int retries = 3;
	ret = ERR_FAIL;
	// 计算出卡值
	out_money = purse_info.bala + pCardCons->TranAmt;
	while (retries-- > 0)
	{
		if (curr_card_id != card_id)
		{
			SetLastErr(ERR_TA_NOT_SAMECARD, "消费写卡卡号不一致,后台流水号[%d]", record.serial_no);
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
		g_logger.writelog("消费写卡失败,后台流水号[%d]", record.serial_no);
		return ERR_TA_WRITECARD;
	}
	// 保存记录文件
	ret = rec_writter.write_record(&record, 0);
	if (ret)
	{
		SetLastErr(ret, "记录流水失败,tx_date[%s],tx_time[%s],card_id[%d],inbala[%d],amount[%d]"
		           , record.tx_date, record.tx_time, record.card_id, record.in_balance, record.trade_amount);
		return ret;
	}
	strcpy(RecFile, serial_file_path);
	return 0;
}
/*
 \breif 上传脱机消费流水, 指定流水日期程序通过在 serial 目录下查找 rec_YYYYMMDD.log 的
 流水文件上传流水，上传完成后将 rec_YYYYMMDD.log 文件重命名为 rec_YYYYMMDD.log.采集时间戳
 \param serial_date 流水日期
 \param serial_cnt - 输入输出参数，输入时当>0 表示从第 serial_cnt 条上传, 输出表示上传成功的流水条数
 \return 返回 0 表示成功 ，错误返回错误码
 */
int __stdcall KS_Upload_SerialRecord(const char *serial_date, int *serial_cnt)
{
	g_logger.writelog("调用 KS_Upload_SerialRecord 功能函数");
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
		SetLastErr(ERR_NO_FILE, "流水文件不存在[%s]", serial_file_path);
		return ERR_NO_FILE;
	}
	{
		// 对象结束后关闭文件
		KS_Record_File rec_reader(serial_file_path);
		do
		{
			memset(&record, 0, sizeof record);
			ret = rec_reader.read_record(&record);
			if (ret)
			{
				// 文件读取成功
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
			// 请求交易
			clt.SetIntFieldByName("lcert_code", 240202);
			// 交易卡号
			clt.SetIntFieldByName("lvol0", record.card_id);
			// 卡使用次数
			clt.SetIntFieldByName("lvol1", record.trade_count);
			// 钱包号
			clt.SetIntFieldByName("lvol2", g_devices.devices[term_idx].purse_no);
			// 子系统号
			clt.SetIntFieldByName("lvol3", g_devices.devices[term_idx].sys_id);
			// 设备ID
			clt.SetIntFieldByName("lvol4", g_devices.devices[term_idx].device_id);
			// 终端流水号
			clt.SetIntFieldByName("lvol5", record.serial_no);
			// 入卡值
			clt.SetDoubleFieldByName("damt0", record.in_balance / 100.0);
			// 交易金额
			clt.SetDoubleFieldByName("damt1", record.trade_amount / 100.0);
			// 操作员
			clt.SetStringFieldByName("scust_no", g_devices.devices[term_idx].oper_code);
			// 密码
			clt.SetStringFieldByName("semp_pwd", "");
			// 物理卡号
			clt.SetStringFieldByName("sdate1", "");
			// 交易日期
			clt.SetStringFieldByName("sdate0", record.tx_date);
			clt.SetStringFieldByName("stime0", record.tx_time);
			g_logger.writelog("上传流水serial[%d]card[%d]date[%s]time[%s]", record.serial_no, record.card_id
			                  , record.tx_date, record.tx_time);
			// 摘要
			//clt.SetStringFieldByName("vsmess",pCardCons->Abstract);

			if (!clt.SendRequest(FUNC_CONSUME, time_out))
			{
				SetLastErr(ERR_FAIL, "请求交易失败,[%d]", FUNC_CONSUME);
				ret = ERR_FAIL;
			}
			//	pCardCons->RetCode = clt.GetReturnCode();
			if (clt.GetReturnCode())
			{
				clt.GetReturnMsg(err_msg);
				SetLastErr(ERR_FAIL, "请求交易失败,[%d],终端流水号[%d]返回码[%d][%s]"
				           , FUNC_CONSUME, record.serial_no, clt.GetReturnCode(), err_msg);
				return ERR_FAIL;
			}
			if (clt.HasMoreRecord())
			{
				clt.GetNextPackage();
				int trade_serial;
				double out_amt, trade_amt;
				clt.GetIntFieldByName("lvol0", &trade_serial);
				// 成功返回
				clt.GetIntFieldByName("lvol0", &trade_serial);
				clt.GetDoubleFieldByName("damt0", &out_amt);
				clt.GetDoubleFieldByName("damt1", &trade_amt);
				out_money = (int)d4u5(out_amt * 100.0);
				trade_money = (int)d4u5(trade_amt * 100.0);
				clt.ResetHandler();
				// 请求交易
				clt.SetIntFieldByName("lcert_code", 240202);
				// 交易卡号
				clt.SetIntFieldByName("lvol0", record.card_id);
				// 卡使用次数
				clt.SetIntFieldByName("lvol1", record.trade_count);
				// 钱包号
				clt.SetIntFieldByName("lvol2", g_devices.devices[term_idx].purse_no);
				// 子系统号
				clt.SetIntFieldByName("lvol3", g_devices.devices[term_idx].sys_id);
				// 设备ID
				clt.SetIntFieldByName("lvol4", g_devices.devices[term_idx].device_id);
				// 终端流水号
				clt.SetIntFieldByName("lvol5", record.serial_no);
				// 入卡值
				clt.SetDoubleFieldByName("damt0", record.in_balance / 100.0);
				// 交易金额
				clt.SetDoubleFieldByName("damt1", record.trade_amount / 100.0);
				// 操作员
				clt.SetStringFieldByName("scust_no", g_devices.devices[term_idx].oper_code);
				// 密码
				clt.SetStringFieldByName("semp_pwd", "");
				// 后台流水号
				clt.SetIntFieldByName("lvol6", trade_serial);
				// 交易日期
				clt.SetStringFieldByName("sdate0", record.tx_date);
				clt.SetStringFieldByName("stime0", record.tx_time);
				if (clt.SendRequest(FUNC_CONSUME_CONFIRM))
				{
					if (!clt.GetReturnCode())
					{
						g_logger.writelog("交易成功，金额[%d]分,卡余额[%d], 后台流水号[%d]", trade_money
						                  , out_money, trade_serial);
						// 休眠卡
						//HaltCard();
						ret = 0;
						rec_cnt++;
					}
					else
					{
						g_logger.writelog("交易失败，[%d ]返回[%d],", FUNC_CONSUME_CONFIRM, clt.GetReturnCode());
						ret = ERR_FAIL;
					}
				}
				else
					SetLastErr(ERR_FAIL, "交易确认失败");
			}
			else
			{
				SetLastErr(ERR_FAIL, "消费交易失败");
				ret = ERR_FAIL;
			}
		}
		while (!ret);
	}
	// 文件重命名
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
			SetLastErr(ERR_REFUSE, "备份流水失败，流水文件[%s]", serial_file_path);
			ret = ERR_REFUSE;
		}
	}
	*serial_cnt = rec_cnt;
	return ret;
}
/*
  \brief 修改主功能号
  \param funcno 主功能号
 */
void __stdcall KS_Set_MainFunc(int funcno)
{
	g_logger.writelog("调用 KS_Set_MainFunc , 更新主功能号为 %d", funcno);
	g_main_func = funcno;
}

/*
 \brief 给卡加钱
 \param amount - 金额, 必须是正数,单位为分, 最大金额不超过 100000 分
 \param bala - 输出参数, 充值成功后卡余额
 \return 返回 0 表示成功 , 失败返回错误码
 */
static int __stdcall KS_Card_Add_Money(int amount, int *bala)
{
	g_logger.writelog("调用 KS_Card_Add_Money 接口");
	TEST_COM_OPEN;
	int idx = 0;
	int card_id, ret, out_money;
	char card_serial_no[9] = "";
	MONEY_PACK_INFO purse_info;

	if (g_devices.devices[idx].flag | DEV_FLAG_ADD_MONEY)
	{
		SetLastErr(ERR_TRN_STATION, "终端无权充值");
		return ERR_TRN_STATION;
	}
	if (amount < 0 || amount > 100000)
	{
		SetLastErr(ERR_TA_TRANAMT, "输入金额超限!");
		return ERR_TA_TRANAMT;
	}

	card_id = 0;
	ret = ReadCardNO(&card_id);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读取卡号失败!");
		return ERR_TA_READCARD;
	}
	ret = ReadSerial((unsigned char*)card_serial_no);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读取卡号物理ID号失败!");
		return ERR_TA_READCARD;
	}
	memset(&purse_info, 0, sizeof purse_info);
	ret = SMT_GetPacketInfo(g_devices.devices[idx].purse_no, &purse_info);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "读卡钱包失败,purse[%d]", g_devices.devices[idx].purse_no);
		return ERR_TA_READCARD;
	}

	// 计算出卡值
	out_money = purse_info.bala + amount;

	int curr_card_id;
	ret = ReadCardNO(&curr_card_id);
	if (ret)
	{
		SetLastErr(ERR_TA_READCARD, "返回写卡失败!");
		return ERR_TA_READCARD;
	}
	int retries = 3;
	ret = ERR_FAIL;

	while (retries-- > 0)
	{
		if (curr_card_id != card_id)
		{
			SetLastErr(ERR_TA_NOT_SAMECARD, "充值写卡卡号不一致");
			return ERR_TA_NOT_SAMECARD;
		}
		ret = SMT_PacketSetMoney(g_devices.devices[idx].purse_no, out_money);
		if (!ret)
		{
			g_logger.writelog("充值成功,cardid[%d],bala[%d],amount[%d]", card_id
			                  , out_money, amount);
			*bala = out_money;
			return 0;
		}
	}
	if (ret)
	{
		g_logger.writelog("充值写卡失败");
		ret = ERR_TA_WRITECARD;
	}
	return ret;
}

void __stdcall KS_Sleep_Card()
{
	HaltCard();
}