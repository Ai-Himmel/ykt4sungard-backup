// kscard.cpp : Defines the initialization routines for the DLL.
//
#include "kscard.h"
#include "global.h"
#include <vector>
#include <string>
#include <windows.h>
#include "mystring.h"
#include "des.h"
#include "yktclt.h"
#include "logfile.h"
#include "global_func.h"
#include "interface.h"
#include "ksdevice.h"
#include "kslicense.h"
#include "kscardtype.h"
#include "version.h"
#include <assert.h>
#include <fstream>
using namespace std;

#define GET_CARDTYPE_RET(c,r) do { c = CardTypeManager::instance()->getLastCardType(); if(c==NULL) return (r); }while(0)
#define GET_CARDTYPE(c) GET_CARDTYPE_RET(c,KS_REQUESTCARD)
#define GET_CARDTYPE_NORET(c) do { c = CardTypeManager::instance()->getLastCardType(); if(c==NULL) return; }while(0)

#define TRACE_FUNC(x) do { g_szErrMsg[0] = 0; g_nErrCode = 0; }while(0); \
	DCLR_LOGMSG(x)

char PROGVERSION[]="KSCARD V" KSCARD_VERSION;
char PROGBUILD[]=__DATE__;

ks_cardlib_license g_license;

#pragma comment (lib, "bccclt.lib")

//KSYkt_Log_Writer g_logger("kscard");
static KSYkt_Log_Writer* logger = KSYkt_Log_Writer::make_instance("kscard");
char g_global_path[1024];
char g_cpack_path[1024];
char g_config_path[1024];

std::string g_card_read_right;
std::string g_card_write_right;

CardReaderManager g_ReaderManager;

//ofstream log("mylog1.txt");

#define MAIN_READER g_ReaderManager.getReaderByIdx(0)
#define SECOND_READER g_ReaderManager.getReaderByIdx(1)
#define MAIN_READER_PARA(p) do { p = g_ReaderManager.getReaderParaByNo(1); }while(0)
#define SECOND_READER_PARA(p) do { p = g_ReaderManager.getReaderParaByNo(2); }while(0)

static ks_cardtype_base* getCardTypeByType(unsigned int b)
{
	ks_cardtype_base *c;
	c = CardTypeManager::instance()->getCardType(b);
	return c;
}

//#define CALL_READER_FUNC(idx,func,z,r) do { r= g_ReaderManager.getReaderByIdx(idx)->#func z; }while(0)

//////////////////////////////////////////////////////////////////////////
// mifare one card
static BYTE CARD_INIT_KEY[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

static int do_check_file_exists(const char *file_path)
{
	HANDLE h;
	if((h = CreateFile(file_path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))==INVALID_HANDLE_VALUE)
		return -1;
	CloseHandle(h);
	return 0;
}

static int do_init_log()
{
	
	char path[1025];
	memset(path,0,sizeof path);
	memset(g_global_path,0,sizeof g_global_path);
	GetModuleFileName(NULL,path,1024);
	char * p = strrchr(path,'\\');
	if(p)
	{
		*p = '\0';
	}
	memcpy(g_global_path,path,strlen(path));
	sprintf(path,"%s\\logs",g_global_path);
	KSYkt_Log_Writer::instance()->openlog(path);

	// cpack
	sprintf(path,"%s\\cpack.dat",g_global_path);
	if(do_check_file_exists(path))
	{
		GetSystemDirectory(path,1024);
		strcat(path,"\\cpack.dat");
		if(!do_check_file_exists(path))
		{
			strcpy(g_cpack_path,path);
		}
	}
	else
	{
		strcpy(g_cpack_path,path);
	}

	// config 
	sprintf(path,"%s\\kscard.ini",g_global_path);
	if(do_check_file_exists(path))
	{
		GetSystemDirectory(path,1024);
		sprintf(g_config_path,"%s\\kscard.ini",path);
		if(!do_check_file_exists(g_config_path))
		{
			strcpy(g_config_path,path);
		}
		else
			memset(g_config_path,0,sizeof g_config_path);
	}
	else
	{
		strcpy(g_config_path,g_global_path);
	}
	
	return 0;
}

static int g_init_log = do_init_log();


/////////////////////////////////////////////////////////////////////////////
// The one and only CkscardApp object


//HANDLE				g_nHandle=NULL;

ST_CARDMAINKEY   g_MainKey;
ST_CARDMAINKEY   g_CloneKey;
static char g_szReadBuf[FIELDMAXNUM];
static char g_szWriteBuf[FIELDMAXNUM];
vector<ST_CARDTABLEINDEX>  g_VsCardInfo;
vector<ST_READCARDINFO>      g_VsReadCardInfo;
vector<ST_WRITECARDINFO>     g_VsWriteCardInfo;
//CKsCard gKsCard;

static char g_szErrMsg[512];
static short  g_nErrCode=0; 


unsigned int g_cardtype;

static void do_getcurrent_datetime(char *sDate,char *sTime)
{
	time_t curr;
	struct tm curr_tm;
	time(&curr);
	curr_tm = *localtime(&curr);
	sprintf(sDate,"%.04d%.02d%.02d",curr_tm.tm_year+1900
		,curr_tm.tm_mon+1,curr_tm.tm_mday);

	sprintf(sTime,"%.02d%.02d%.02d",curr_tm.tm_hour
		,curr_tm.tm_min,curr_tm.tm_sec);

}
void __stdcall ks_setlasterr(char *errmsg,int errcode)
{
	g_nErrCode=errcode;
	if(0==g_nErrCode)
		g_nErrCode=-1;
	if(strlen(errmsg)>0)
	strcpy(g_szErrMsg,errmsg);
	else
		strcpy(g_szErrMsg,"未知错误");
	//sprintf(g_szErrMsg,"%s,Err:%04X",errmsg,g_nErrCode);
	KS_Log_Tracer::instance()->SetTraceFile("kscard.cpp",0);
	KS_Log_Tracer::instance()->TraceMsg(g_szErrMsg);
}
char* __stdcall ks_geterrmsg(char *errmsg)
{
	if(g_nErrCode)
	{
		KS_Log_Tracer::instance()->GetLastMsg(g_szErrMsg);
		if(errmsg)
			strcpy(errmsg,g_szErrMsg);
		return g_szErrMsg;
	}
	else
	{
		memset(g_szErrMsg,0,sizeof(g_szErrMsg));
		return g_szErrMsg;
	}
}

int __stdcall ks_savekeys()
{
	TRACE_FUNC("ks_savekeys");
	int nRet=0;
	if(ks_checkloadkeys()!=1)
	{
		ks_setlasterr("密钥未装载",-1);
		return -1;
	}
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	ks_cardtype_base *c = CardTypeManager::instance()->getCardType(0x0400);
	nRet=c->SaveKeys();
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
		return nRet;
	}
	return 0;
	
}
int __stdcall ks_reset(int msec)
{
	//if(g_MainReader.reset(&g_ReaderPara,msec))
	/*
	ks_cardtype_base *c = CardTypeManager::instance()->getLastCardType();
	// TODO : add reset
	{
		ks_setlasterr("串口未打开",-1);
		return -1;
	}
	*/
	return 0;
}
void __stdcall ks_getversioninfo(char *version,char *builddate,char *desc)
{
	//CTime time = CTime::GetCurrentTime();
	//CString cs=time.Format("%Y%m%d");
	strcpy(version,PROGVERSION);
	strcpy(builddate,PROGBUILD);
	//strcpy(desc,"this is a demo version");
}
/*int  dc_init(int port,long baud);
功 能：初始化通讯口
参 数：port：取值为0～19时，表示串口1～20；为100时，表示USB口通讯，此时波特率无效。
baud：为通讯波特率9600～115200
返 回：成功则返回串口标识符>0，失败返回负值，见错误代码表
例：int icdev;
icdev=dc_init(0,9600);//初始化串口1，波特率9600*/
int __stdcall ks_init()
{
	static int isInit = 0;
	TRACE_FUNC("ks_init");
	TRACE2_LOG(("启动kscard ver[%s][%s]",PROGVERSION,PROGBUILD));
	if(isInit == 0)
	{
		if(load_interface_layer(g_config_path))
		{
			ks_setlasterr("load_interface_layer失败",-1);
			free_interface_layer();
			return -1;
		}
		isInit = 1;
	}
	return 0;
}
int __stdcall ks_openport(int port,int band)
{
	TRACE_FUNC("ks_openport");
	int ret=0;
	size_t i;
	ks_cardtype_base *c;
	ret = g_ReaderManager.openPort(1,port,band);
	if(ret)
	{
		ks_setlasterr("打开读卡器端口错误");
		return ret;
	}
	TRACE_LOG("打开读卡器成功");
	return 0;
}
/*int dc_exit(int icdev);
功 能：关闭端口
参 数：icdev：通讯设备标识符
返 回：成功返回0
例：dc_exit(icdev);*/
int __stdcall ks_closeport()
{
	int i;
	TRACE_FUNC("ks_closeport");
	g_ReaderManager.closePort();
	TRACE_LOG("关闭读卡器");
	return 0;
	
}

/*int ks_beep(unsigned int _Msec);
功 能：蜂鸣
unsigned int _Msec：蜂鸣时间，单位是10毫秒
返 回：成功则返回 0
例：int st;
st=ks_beep(10);            鸣叫100毫秒*/
void __stdcall ks_beep()
{
	g_ReaderManager.beep();
}
void __stdcall ks_beeperr()
{
	g_ReaderManager.beeperr();
}
/*
int ks_setcpu4sam(int SAMID);
说明：设置要操作的SAM卡座 

unsigned char SAMID --- 设置要操作的卡座号,0x0c为附卡座，0x0d 0x0e 0x0f各为SAM1 SAM2 SAM3 

返回：<0 错误。其绝对值为错误号

=0 成功
*/
/*
说明：设置读写器将要对哪一种卡操作，读写器上电缺省的时候是对TYPEA操作。
	参数说明：HANDLE icdev dc_init返回的设备描述符；
	cardtype：当为'A'的时候表示设置读写器，'B'表示对TYPE B操作
		返回：成功则返回 0；
		
			举例:
			int st;
			st= ks_setcardtype ('B');//设置对TYPE B卡操作
*/
int __stdcall ks_setcardtype(int cardtype)
{
	//return  dc_config_card(g_nHandle,cardtype);//设置对TYPE B卡操作
	/*
	ks_device_op_t *op = g_ReaderManager.getReaderByType(ks_cardtype_base::RT_USERCARD);
	ks_reader_dev_t *para = op->getdev
	return op->config_card(para,(KS_CPUCARD_TYPE)cardtype);
	*/
	return -1;
}
/*int ks_halt();
  功 能：中止对该卡操作
  参 数：icdev：通讯设备标识符
 返 回：成功则返回0
 例：st=dc_halt(icdev);
 说明：使用dc_card()函数时，有个_Mode参数，如果_Mode=0则在对卡进行操作完毕后，执行ks_halt();则该卡进入HALT模式，则必须把卡移开感应区再进来才能寻得这张卡。
*/

int __stdcall  ks_halt()
{
	TRACE_FUNC("ks_halt");
	ks_cardtype_base *c;
	GET_CARDTYPE_RET(c,0);
	ks_device_op_t *op = c->GetDevice(ks_cardtype_base::RT_USERCARD);
	ks_reader_dev_t *para = c->GetDevicePara(ks_cardtype_base::RT_USERCARD);
	return op->halt(para);
}
/*
int dc_card(int icdev,unsigned char _Mode,unsigned long *_Snr);
功 能：寻卡，能返回在工作区域内某张卡的序列号(该函数包含了dc_request,dc_anticoll,dc_select的整体功能)						
						参 数：icdev：通讯设备标识符						
						_Mode：寻卡模式mode_card						
						_Snr：返回的卡序列号						
						返 回：成功则返回 0						
						例：int st;
*/
/*
static int do_request_card(char *sCardPhyID,KS_CARD_TYPE t)
{
	if(g_MainReader.request_card(&g_ReaderPara,sCardPhyID,t))
		return -1;
	memcpy(g_cardinfo.phyid,sCardPhyID,8);
	memset(g_cardinfo.sect_login,0,sizeof g_cardinfo.sect_login);
	return 0;

}
*/

int __stdcall ks_select_reader()
{
	return 0;
}
//寻卡
int __stdcall ks_card(char *sCardPhyID)
{
	TRACE_FUNC("ks_card");
	int ret;
	char msg[512]="";
	ret = CardTypeManager::instance()->requestCard(sCardPhyID);
	if(ret)
	{
		ks_cardtype_base *c= CardTypeManager::instance()->getLastCardType();
		if(c != NULL)
		{
			c->GetLastErrMsg(msg);
			if(!strlen(msg))
				CardTypeManager::instance()->getErrorMsg(msg,"寻卡失败");
			ks_setlasterr(msg);
		}
		else
		{
			char errmsg[256]={0};
			CardTypeManager::instance()->getErrorMsg(errmsg,"寻卡失败");
			ks_setlasterr(errmsg);
		}
	}
	return ret;
}

int __stdcall ks_mf_card(char *sCardPhyID)
{
	TRACE_FUNC("ks_mf_card");
	ks_setlasterr("不支持该函数调用");
	return -1;
}
/*
__int16 dc_pro_reset(HANDLE ICDev,unsigned char *rlen, unsigned char *rbuff)
说明：卡上电复位函数,仅针对于TYPE A 卡
调用：int ICDev ---- dc_init 函数返回的端口标识符
unsigned char *rlen ---- 返回复位信息的长度
unsigned char * rbuff ---- 存放返回的复位信息
返回： <0 错误。其绝对值为错误号
=0 成功。
举例：st=dc_pro_reset(ICDev,rlen,DataBuffer)*/
//卡复位
int __stdcall ks_resetpro(unsigned char *rlen, unsigned char *rbuff)
{
	TRACE_FUNC("ks_resetpro");
	ks_cardtype_base *c = CardTypeManager::instance()->getLastCardType();
	ks_device_op_t *op = c->GetDevice(ks_cardtype_base::RT_USERCARD);
	ks_reader_dev_t *para = c->GetDevicePara(ks_cardtype_base::RT_USERCARD);
	return op->cpucard_poweron(para,KS_CPUCARD,rlen,rbuff);
}

int __stdcall ks_setcpupara4sam(int SAMID)
{
	TRACE_FUNC("ks_setcpupara4sam");
	int nRet=0;
	ks_reader_dev_t *para;
	para = g_ReaderManager.getPSAMReaderPara();
	para->cpuport = SAMID;
	//ks_device_op_t *op = g_ReaderManager.getReaderByType(ks_cardtype_base::RT_PSAM);
	ks_psamcard_base *p = CardTypeManager::instance()->getPSAMCardType();
	if(p == NULL)
		return -1;
	TRACE2_LOG(("设置SAM卡座no[%d]",para->cpuport));
	p->SetSAMPara(para);
	return 0;
}
int __stdcall ks_setcpupara(int SAMID)
{
	TRACE_FUNC("ks_setcpupara");
	int nRet=0;
	ks_cardtype_base *c = CardTypeManager::instance()->getLastCardType();
	if(NULL==c)
	{
		ks_setlasterr("设置卡座失败,没有找到对应的卡类型");	
		return -1;
	}
	ks_device_op_t *op = c->GetDevice(ks_cardtype_base::RT_USERCARD);
	ks_reader_dev_t *para = c->GetDevicePara(ks_cardtype_base::RT_USERCARD);
	para->cpuport = SAMID;

	nRet=op->cpucard_setpara(para);
	if(nRet)
	{
		ks_setlasterr(op->GetErrMsg(NULL));
		return nRet;
	}
	return 0;
}
int __stdcall ks_cpureset4sam(unsigned char *rlen, unsigned char *rbuff)
{
	TRACE_FUNC("ks_cpureset4sam");
	int ret=0;
	ks_psamcard_base *c = CardTypeManager::instance()->getPSAMCardType();
	if(NULL==c)
	{
		ks_setlasterr("设置卡座失败,没有找到对应的卡类型");	
		return -1;
	}
	ret=c->ResetPSAM();
	if(ret)
	{
		ks_setlasterr("SAM卡座上电复位错误",ret);
		return ret;
	}
	return 0;
}
int __stdcall ks_samcpureset()
{
	TRACE_FUNC("ks_samcpureset");
	int ret=0;
	unsigned char rlen[2]={0};
	unsigned char rbuff[256]={0};
	ret=ks_cpureset4sam(rlen,rbuff);
	if(ret)
	{
		ks_setlasterr("SAM卡座上电复位错误",ret);
		return ret;
	}
	return 0;
}
/*
__int16 dc_pro_command(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff,unsigned char tt)
说明：应用协议数据单元信息交换函数。该函数已封装T=CL操作
调用：int ICDev ----dc_init 函数返回的端口标识符
unsigned char slen ---- 发送的信息长度
unsigned char * sbuff ---- 存放要发送的信息
unsigned char *rlen ---- 返回信息的长度
unsigned char * rbuff ---- 存放返回的信息
unsigned char tt---- 延迟时间，单位为：10ms
*/
int __stdcall ks_cpuapdu4hex(const char *szCmd,unsigned char nCmdlen,unsigned char* sRespData,unsigned char &nRespLen )
{
	TRACE_FUNC("ks_cpuapdu4hex");
	int nRet=0;
	ks_cpu_cmd_t cmd;
	byte ucSendData[256];
	int nSendLen;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ks_device_op_t *op = c->GetDevice(ks_cardtype_base::RT_USERCARD);
	ks_reader_dev_t *para = c->GetDevicePara(ks_cardtype_base::RT_USERCARD);

	hex2dec(szCmd,nCmdlen,ucSendData,nSendLen);
	
	memset(&cmd,0,sizeof cmd);
	cmd.cmd_type = 0;
	cmd.send_len = nSendLen;
	cmd.send_buf = ucSendData;
	cmd.recv_buf = sRespData;
	nRet = op->cpucard_cmd(para,&cmd,KS_CPUCARD);
	if(nRet)
	{
		char szErrMsg[600];
		sprintf(szErrMsg,"执行CPU卡指令错误[%s]ret[%d]",szCmd,nRet);
		ks_setlasterr(szErrMsg,cmd.cmd_retcode);
		return cmd.cmd_retcode;
	}
	nRespLen = cmd.recv_len - 2;
	return 0;

}
//CPU卡直通指令
int __stdcall ks_cpuapdu( unsigned char *sSendData, unsigned char nSendLen, 
								   unsigned char* sRespData,unsigned char &nRespLen )
{
	TRACE_FUNC("ks_cpuapdu");
	int nRet=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ks_device_op_t *op = c->GetDevice(ks_cardtype_base::RT_USERCARD);
	ks_reader_dev_t *para = c->GetDevicePara(ks_cardtype_base::RT_USERCARD);

	ks_cpu_cmd_t cmd;
	
	memset(&cmd,0,sizeof cmd);
	cmd.cmd_type = 0;
	cmd.send_len = nSendLen;
	cmd.send_buf = sSendData;
	cmd.recv_buf = sRespData;
	nRet = op->cpucard_cmd(para,&cmd,KS_CPUCARD);
	if(nRet)
	{
		char szCmd[512]={0};
		dec2hex(cmd.send_buf,cmd.send_len,szCmd);
		char szErrMsg[600];
		sprintf(szErrMsg,"执行CPU卡指令错误[%s]ret[%d]",szCmd,nRet);
		ks_setlasterr(szErrMsg,cmd.cmd_retcode);
		return cmd.cmd_retcode;
	}
	nRespLen = cmd.recv_len - 2;
	return 0;
}
/*
__int16 dc_cpuapdu(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff)

说明：CPU卡APDU（应用协议数据单元）信息交换函数。该函数封装了T=0和T=1操作 

调用：int ICDev ----dc_init 函数返回的端口标识符

unsigned char *slen ---- 发送的信息长度

unsigned char * sbuff ---- 存放要发送的信息

unsigned char *rlen ---- 返回信息的长度

unsigned char * rbuff ---- 存放返回的信息

返回： <0 错误。其绝对值为错误号

=0 成功。
*/

//SAM卡直通指令
int __stdcall ks_cpuapdu4sam( unsigned char *sSendData, unsigned char nSendLen, 
								   unsigned char* sRespData,unsigned char &nRespLen )
{
	TRACE_FUNC("ks_cpuapdu4sam");
	int nRet=0;
	ks_reader_dev_t *para = g_ReaderManager.getPSAMReaderPara();
	ks_device_op_t *op = g_ReaderManager.getReaderByType(ks_cardtype_base::RT_PSAM);

	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof cmd);
	cmd.cmd_type = 0;
	cmd.send_len = nSendLen;
	cmd.send_buf = sSendData;
	cmd.recv_buf = sRespData;
	nRet = op->cpucard_cmd(para,&cmd,KS_PSAM);
	if(nRet)
	{
		char szCmd[512]={0};
		dec2hex(cmd.send_buf,cmd.send_len,szCmd);
		char szErrMsg[600];
		sprintf(szErrMsg,"执行SAM卡指令错误[%s]ret[%d]",szCmd,nRet);
		ks_setlasterr(szErrMsg,cmd.cmd_retcode);
		return cmd.cmd_retcode;
	}
	nRespLen = cmd.recv_len - 2;
	return 0;
}
int __stdcall ks_cpuapdu4sam_hex(const char *sSendData, unsigned char nSendLen, 
								   unsigned char* ucRespData,unsigned char &nRespLen )
{
	TRACE_FUNC("ks_cpuapdu4sam_hex");
	int nRet=0;
	ks_cpu_cmd_t cmd;
	byte ucSendData[256];
	int nSendDataLen;

	ks_reader_dev_t *para = g_ReaderManager.getPSAMReaderPara();
	ks_device_op_t *op = g_ReaderManager.getReaderByType(ks_cardtype_base::RT_PSAM);

	hex2dec(sSendData,nSendLen,ucSendData,nSendDataLen);
	memset(&cmd,0,sizeof cmd);
	cmd.cmd_type = 0;
	cmd.send_len = nSendDataLen;
	cmd.send_buf = ucSendData;
	cmd.recv_buf = ucRespData;
	nRet = op->cpucard_cmd(para,&cmd,KS_PSAM);
	if(nRet)
	{
		char szErrMsg[600];
		sprintf(szErrMsg,"执行SAM卡指令错误[%s]ret[%d]",sSendData,nRet);
		ks_setlasterr(szErrMsg,cmd.cmd_retcode);
		return cmd.cmd_retcode;
	}
	nRespLen = cmd.recv_len - 2;
	return 0;
}

int __stdcall ks_cpureset(unsigned char *rlen, unsigned char *rbuff)
{
	TRACE_FUNC("ks_cpureset");
	ks_reader_dev_t *para = g_ReaderManager.getPSAMReaderPara();
	ks_device_op_t *op = g_ReaderManager.getReaderByType(ks_cardtype_base::RT_PSAM);

	int nRet= op->cpucard_poweron(para,KS_PSAM,rlen,rbuff);
	if(nRet)
	{
		ks_setlasterr("SAM卡上电复位错误",nRet);
		return nRet;
	}
	return 0;
}

int __stdcall ks_publishkeycard(unsigned char* sMasterKey, char* sPin )
{
	TRACE_FUNC("ks_publilshkeycard");
	int ret=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ret=c->PublishKeyCard(sMasterKey,sPin);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;
}
int __stdcall ks_loadkeys4clone(const char sKeyCardPin[7])
{
	TRACE_FUNC("ks_loadkeys4clone");
	int ret=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ret=c->LoadKeys4Clone(sKeyCardPin);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;
}
int __stdcall ks_checkloadclonekeys()
{
	TRACE_FUNC("ks_checkloadclonekeys");
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	return c->IsLoadCloneKeys();
}
//克隆密钥卡
int __stdcall ks_clonekeycard(const char sCloneCardPin[7])
{
	TRACE_FUNC("ks_clonekeycard");
	int ret=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ret=c->CloneKeyCard(sCloneCardPin);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;
	
}
int __stdcall ks_setmifare1key(const char sWorkKey[17])
{
	//ks_cardtype_base *c = CardTypeManager::instance()->getLastCardType();
	TRACE_FUNC("ks_setmifare1key");
	int i;
	for(i = 0;i < CardTypeManager::instance()->getCardTypeCount();++i)
	{
		ks_cardtype_base *c = CardTypeManager::instance()->getCardTypeByIdx(i);
		c->SetMifare1Key(sWorkKey);
	}
	TRACE_LOG("更新M1卡密钥");
	return 0;
}
int __stdcall ks_publishpsamcard(ST_PSAMCARD* PSAMCard)
{
	TRACE_FUNC("ks_publishpsamcard");
	int ret=0;
	ks_psamcard_base *c = CardTypeManager::instance()->getPSAMCardType();
	ret=c->PublishPSAMCard(PSAMCard);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;

}

int  ReadBinaryFile4Sam(byte ucSFI,   byte ucOffset,byte ucLength,byte *ucData)
{	
	TRACE_FUNC("ReadBinaryFile4Sam");
	char	szCmd[256];
	byte	nResLen=0;
	sprintf(szCmd,"00B0%02X%02X%02X",0x80+ucSFI,ucOffset,ucLength);	
	return ks_cpuapdu4sam_hex(szCmd,strlen(szCmd),ucData,nResLen);
}

int __stdcall ks_readpsamcard(ST_PSAMCARD* PSAMCard)
{	
	TRACE_FUNC("ks_readpsamcard");
	int ret=0;
	ks_psamcard_base *c = CardTypeManager::instance()->getPSAMCardType();
	ret=c->ReadPSAMCard(PSAMCard);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	TRACE2_LOG(("PSAM No[%s]",PSAMCard->sTermID));
	return 0;
}
//回收PSAM卡
int __stdcall ks_recyclepsamcard()
{
	TRACE_FUNC("ks_recyclepsamcard");
	int ret=0;
	ks_psamcard_base *c = CardTypeManager::instance()->getPSAMCardType();
	ret=c->RecyclePSAMCard();
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;

}

//使用方式
int __stdcall ks_recycleusercard()
{
	TRACE_FUNC("ks_recycleusercard");
	int nRet;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	nRet=c->RestoreFactorySettings();
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	return 0;
}


// 回收卡
int __stdcall ks_refineusercard(int nUseFlag,const char *szCardShowNo)
{
	TRACE_FUNC("ks_refineusercard");
	int nRet=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	nRet=c->RestoreFactorySettings();
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	// TODO : 处理卡号
	nRet=ks_publishusercard("",szCardShowNo);
	if(nRet)
	{
		TRACE2_LOG(("ks_publishusercard ret=%X",nRet));
		return nRet;
	}
	
	return 0;
}
//回收密钥卡
int __stdcall ks_recyclekeycard()
{
	TRACE_FUNC("ks_recyclekeycard");
	int ret=0;
	ks_cardtype_base *c = CardTypeManager::instance()->getCardType(0x0400);
	ret=c->RecycleKeyCard();
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;
}

/*	函数功能：
	在认证PIN通过后，才可以根据相应序号获取相应的应用密钥，序号对应关系如下：
	1--消费密钥1
	2--消费密钥2
	3--圈存密钥1
	4--圈存密钥2
	5--TAC密钥1
	6--TAC密钥2
	7--PIN解锁密钥
	8--重装PIN密钥
	9--维护密钥
	10--主控密钥
	函数原型：int ks_Get_Key (int nKeySerial,char* sPin char* sKey)
	入口参数：
	int    nKeySerial  -密钥序号
	char* sPin          -6个数字字符的个人密码
	出口参数：
	char* sKey  	  -16字密钥
	函数返回： 
	0 --成功，其它值-错误(PBOC错误码)
	可以将密钥获取后存于数据库中（最好加密钥保存)
*/
//int __stdcall ks_getkey (int nKeySerial,char* sPin, char* sKey)
int __stdcall ks_loadcardkeys(const char *sKeyCardPwd)
{
	TRACE_FUNC("ks_loadcardkeys");
	int ret=0;
	int i;
	ks_cardtype_base *c = CardTypeManager::instance()->getCardType(0x0400);
	ret=c->LoadKeysFromKeyCard(sKeyCardPwd);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	memset(c->cardtype_buff,0,16);
	for(i = 0;i < CardTypeManager::instance()->getCardTypeCount();++i)
	{
		ks_cardtype_base *b = CardTypeManager::instance()->getCardTypeByIdx(i);
		if(b != c)
		{
			c->SetKeyCard(b);
		}
	}
	return 0;
}
void __stdcall ks_unloadcardkeys()
{
	TRACE_FUNC("ks_unloadcardkeys");
	memset(&g_MainKey,0,sizeof(g_MainKey));
}
int __stdcall ks_checkloadkeys()
{
	TRACE_FUNC("ks_checkloadkeys");
	ks_cardtype_base *c = CardTypeManager::instance()->getCardType(0x0400);
	return c->IsLoadKeys();
}

int __stdcall ks_publishusercard(const char *sCardPhyID,const char *sShowCardNo)
{
	TRACE_FUNC("ks_publishusercard");
	int ret=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ret=c->InitUserCard(sShowCardNo);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	
	return 0;
}
int __stdcall ks_format_mfcard(const char *sCardPhyID,const char *sShowCardNo)
{
	TRACE_FUNC("ks_format_mfcard");
	return -1;
}


/*
	用户卡洗卡
	函数原型：int ks_init_card_UserCard(ST_CARDMAINKEY sStrKey,
		char *sAppid,
		char  *sShowCard,
		int nWalletDetailCount)
	入口参数：
		char * sAppid	-卡片用户序列号 (20个字符)
		char*sShowCard	-显示卡号  (10个字符)
		int nWalletDetailCount -钱包明细最大值
	出口参数：
	无
	函数返回:
	0 --成功，其它值-错误(PBOC错误码)
*/
int __stdcall ks_initcard4user(ST_CARDMAINKEY StrKey,char *sAppid,char  *sShowCard,int nWalletDetailCount)
{
	TRACE_FUNC("ks_initcard4user");
	return 0;
}
/*
	1.4.1.2.	PSAM卡洗卡
	函数原型：int ks_init_card_PSAMCard(char *sAppid,
	char *  sTerminalNo)
	入口参数：
	char *  sAppid- PSAM序列号
	char *  sTerminalNo -终端机编号
	出口参数：
	无
	函数返回： 
	0 --成功，其它值-错误(PBOC错误码)
	待处理的问题：3条密钥(消费、维护、主控，通过结构体ST_CARDMAINKEY传入）
*/
int __stdcall ks_initcard4psam(ST_CARDMAINKEY StrKey,char *sAppid, char* sTerminalNo)
{	
	TRACE_FUNC("ks_initcard4psam");
	return 0;
}
//设置读模式
void __stdcall ks_setfieldreadmode(int fieldid)
{
	TRACE_FUNC("ks_setfieldreadmode");
	if(g_card_read_right.at(fieldid) != '1')
		return;
	ks_cardtype_base *c;
	GET_CARDTYPE_NORET(c);
	c->SetFieldReadMode(fieldid);
}
//设置写模式
void __stdcall ks_setfieldwritemode(int FieldID)
{
	TRACE_FUNC("ks_setfieldwritemode");
	if(g_card_write_right.at(FieldID) != '1')
		return;
	ks_cardtype_base *c;
	GET_CARDTYPE_NORET(c);
	c->SetFieldWriteMode(FieldID);		
}
//设置读写模式
void __stdcall ks_setfieldallmode(int FieldID)
{
	TRACE_FUNC("ks_setfieldallmode");
	if(g_card_read_right.at(FieldID) != '1')
		return;
	if(g_card_write_right.at(FieldID) != '1')
		return;
	ks_cardtype_base *c;
	GET_CARDTYPE_NORET(c);
	c->SetFieldAllMode(FieldID);		
}
//清除读模式
void __stdcall ks_clearfieldreadmode(int FieldID)
{
	TRACE_FUNC("ks_clearfieldreadmode");
	ks_cardtype_base *c;
	GET_CARDTYPE_NORET(c);
	c->ClearFieldReadMode(FieldID);
}
//清除写模式
void __stdcall ks_clearfieldwritemode(int FieldID)
{
	TRACE_FUNC("ks_clearfieldwritemode");
	ks_cardtype_base *c;
	GET_CARDTYPE_NORET(c);
	c->ClearFieldWriteMode(FieldID);
}
//清除所有模式
void __stdcall ks_clearfieldallmode(int FieldID)
{
	TRACE_FUNC("ks_clearfieldallmode");
	ks_cardtype_base *c;
	GET_CARDTYPE_NORET(c);
	c->ClearFieldAllMode(FieldID);
}
/*1.5.3.	清除所有卡操作控制码
函数原型：int ks_clear_all_oper_mask(int mode)
入口参数：
int 	mode - 读卡/写卡模式,0表示读卡,1表示写卡,2全部
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
//清除所有字段的读模式
void __stdcall ks_clearallfieldreadmode()
{
	TRACE_FUNC("ks_clearallfieldreadmode");
	ks_cardtype_base *c;
	GET_CARDTYPE_NORET(c);
	c->ClearAllFieldReadMode();
}
//清除所有字段的写模式
void __stdcall ks_clearallfieldwritemode()
{
	TRACE_FUNC("ks_clearallfieldwritemode");
	ks_cardtype_base *c;
	GET_CARDTYPE_NORET(c);
	c->ClearAllFieldWriteMode();
}
//清除所有字段的读写模式
void __stdcall ks_clearallfieldallmode()
{
	TRACE_FUNC("ks_clearallfieldallmode");
	g_nErrCode=0;
	g_szErrMsg[0]=0;
	ks_cardtype_base *c;
	GET_CARDTYPE_NORET(c);
	c->ClearAllFieldAllMode();
}
/*1.5.5.	获取卡信息字段
	函数原型：int ks_get_card_data(int mask,char *data)
	入口参数：
	int mask - 读/写卡操作对应卡属性索引，见索引表	
	无
	出口参数：
	int data - 卡属性值
	函数返回： 
	0 --成功，其它见错误码表
*/
int __stdcall ks_getfieldval(int fieldID,char *fieldval)
{	
	TRACE_FUNC("ks_getfieldval");
	int ret=0;
	if(g_card_read_right.at(fieldID) != '1')
	{
		char msg[128];
		sprintf(msg,"无该属性的读取权限idx[%d]",fieldID);
		ks_setlasterr(msg);
		return -1;
	}
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ret=c->GetFieldVal(fieldID,fieldval);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;
	
}

/*1.5.6.	设置写字段数据
函数原型：int ks_set_card_data(int mask,const char *data)
入口参数：
int mask - 读/写卡操作对应卡属性索引，见索引表	
int data - 卡属性值
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_setfieldval(int fieldID,const char *fieldval)
{
	TRACE_FUNC("ks_setfieldval");
	int ret=0;
	if(g_card_write_right.at(fieldID) != '1')
	{
		char msg[128];
		sprintf(msg,"无该属性的写权限idx[%d]",fieldID);
		ks_setlasterr(msg);
		return -1;
	}
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ret=c->SetFieldVal(fieldID,fieldval);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;

}
//state  0-正常 1锁定 2冻结  3挂失 4注销 5过期
int __stdcall ks_modifystatus(int state)
{
	TRACE_FUNC("ks_modifystatus");
	return 0;
}
//校验密码
int __stdcall ks_verifypasswd(const char *sCardPhyID,const char *cardpasswd,int& iIsPass)
{
	TRACE_FUNC("ks_verifypasswd");
	int nRet=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	nRet=c->VerifyCardPasswd(sCardPhyID,cardpasswd,iIsPass);
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	return 0;
}
int __stdcall ks_readpasswd()
{
	TRACE_FUNC("ks_readpasswd");
	ks_setlasterr("ks_readpasswd函数已删除");
	return -1;
}
//重置密码
int __stdcall ks_resetpasswd(const char *cardphyid,const char *newpwd)
{	
	TRACE_FUNC("ks_resetpasswd");
	int nRet=0;
	char szCardPhyID[17]={0};
	if(strlen(newpwd)!=6)
	{
		ks_setlasterr("密码长度错误",-1);
		return -1;
	}
	ks_setfieldwritemode(CF_CARDPWD);
	ks_setfieldval(CF_CARDPWD,newpwd);
	nRet=ks_writecard();
	if(nRet)
	{
		return nRet;
	}
	return 0;
}

//修改密码
int __stdcall ks_modifypasswd(const char oldpwd[7],const char newpwd[7])
{
	TRACE_FUNC("ks_modifypasswd");
	ks_setlasterr("ks_modifypasswd函数已删除");
	return -1;
}
int __stdcall ks_readcard()
{
	TRACE_FUNC("ks_readcard");
	int ret=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ret=c->ReadCard();
	if(ret)
	{
		//ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;
}
//对于7+1卡,读cpu区域cardtype=0,读mifare1区域cardtype=1,全部读cardtype=2
int __stdcall ks_readcard2(int cardtype)
{
	TRACE_FUNC("ks_readcard2");
	int ret=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ret=c->ReadCard(cardtype);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;
}
/*1.5.7.	写卡信息
函数原型：int ks_write_card ()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_writecard (const char *sCardPhyID)
{
	TRACE_FUNC("ks_writecard");
	int nRet=0;
	ks_cardtype_base *c = CardTypeManager::instance()->getLastCardType(false);
	if(c == NULL)
	{
		ks_setlasterr("未读取到卡片",-1);
		return -1;
	}
	nRet=c->WriteCard();
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
	}
	c->ClearAllFieldWriteMode();
	return nRet;
}

/*1.5.8.	验证口令
函数原型：int ks_verify_pin(char pin[7])
入口参数：
char pin[7]  -6个数字字符的个人PIN
出口参数：
无
函数返回： 
0 --成功，其它见错误码表
*/
int __stdcall ks_verifypin(char pin[7])
{
	TRACE_FUNC("ks_verifypin");
	int nRet=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	nRet=c->SelectADF();
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	nRet=c->VerifyPin(pin);
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	///////////////////////test  test test test test ////////////////////
	string sCmd;
	unsigned char ucRespData[256]={0};
	unsigned char ucRespLen=0;
	//sCmd = "80D439001539F0F0AA33FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"; //外部认证密钥
	  sCmd = "80D43F01153FF0020200FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";	 //圈存密钥
	nRet=c->Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	ks_beep();
	//////////////////////////////////////////////////////////////////////////
	return 0;
}
/*
int __stdcall ks_test(char pin[7])
{
	int nRet=0;
	ks_cardtype_base *c = CardTypeManager::instance()->getLastCardType();
	nRet=c->SelectADF();
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	nRet=c->VerifyPin(pin);
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	///////////////////////test  test test test test ////////////////////
	string sCmd;
	unsigned char ucRespData[256]={0};
	unsigned char ucRespLen=0;
	//sCmd = "80D439001539F0F0AA33FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"; //外部认证密钥
	sCmd = "80D43F01153FF0020200FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";	 //圈存密钥
	nRet=c->Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	ks_beep();
	//////////////////////////////////////////////////////////////////////////
	return 0;
}
*/

/*1.5.9.	卡片锁定
函数原型：int ks_card_block()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表
说明：卡片永久锁定*/
int __stdcall ks_cardblock()
{
	TRACE_FUNC("ks_cardblock");
	return 0;
}

/*1.5.10.	应用锁定
函数原型：int ks_lockapp()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_lockapp()
{
	TRACE_FUNC("ks_lockapp");
	return 0;	
}
/*1.5.11.	应用解锁
函数原型：int ks_unlock_application()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_unlockapp()
{
	TRACE_FUNC("ks_unlockapp");
	return 0;
}

//获取错误信息
//char * __stdcall ks_geterrmsg( int nErrCode,char *sErrInfo )
//{
//	return m_Reader.Get_ErrorInfo( nErrCode,sErrInfo );
//}
int __stdcall GetRandomNum(byte *uRandomNum,char *sRandomNum)
{
	TRACE_FUNC("GetRandomNum");
	int nRet;
	int nCmdLen;
	byte ucCmd[16];
	byte ucResp[128];
	byte ucRespLen;
	memcpy(ucCmd,"\x00\x84\x00\x00\x04",5);
	nCmdLen=5;
	if( (nRet=ks_cpuapdu(ucCmd,nCmdLen,ucResp,ucRespLen))!=0 )
	{
		return nRet;
	}	
	if(uRandomNum)
		memcpy(uRandomNum,ucResp,8);
	if(sRandomNum)
		dec2hex(ucResp,8,sRandomNum);
	return 0;
}

//用于计算MAC 手工和PSAM 
#if 0
int __stdcall ks_calcsafemac(const char* szCmdBuf,char *szMac)
{
	char szBuf[256];
	string sCmd,sMsg;
	int nCmdLen;
	byte uCmd[256];
	byte uRandom[8],uMac[9];
	char szRandom[17];
	int ret;
	ret=GetRandomNum(uRandom,szRandom);
	if(ret)
	{
		return ret;
	}
	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdBuf);
	memcpy(szBuf,szCmdBuf,nCmdBufLen);
	nCmdBufLen/=2;
	if( nCmdBufLen%8 )
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);
	else				 
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",16);		
	
	string sKey="14FED29EE124BB88A5400CA3040EB941";
	byte uDAMK[32];
	int nKeyLen=0;
	hex2dec(sKey.c_str(),sKey.size(),uDAMK,nKeyLen);
	hex2dec(szBuf,nCmdBufLen*2,uCmd,nCmdLen);
	ks_calcmac(uRandom,uDAMK,2,uCmd,nCmdLen,uMac);
	dec2hex(uMac,4,szMac);
	return 0;
}
#endif
int __stdcall ks_calcsafemac(const char* szCmdBuf,char *szMac)
{
	TRACE_FUNC("ks_calcsafemac");
	char szBuf[256];
	string sCmd,sMsg;
	int nCmdLen;
	byte uCmd[256];
	byte uRandom[8],uMac[9];
	char szRandom[17];
	int ret;
	ret=GetRandomNum(uRandom,szRandom);
	if(ret)
	{
		return ret;
	}
	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdBuf);
	memcpy(szBuf,szCmdBuf,nCmdBufLen);
	nCmdBufLen/=2;
	if( nCmdBufLen%8 )
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);
	else				 
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",16);		

	//string sKey="14FED29EE124BB88A5400CA3040EB941";
	string sKey="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	byte uDAMK[32];
	int nKeyLen=0;
	hex2dec(sKey.c_str(),sKey.size(),uDAMK,nKeyLen);
	hex2dec(szBuf,nCmdBufLen*2,uCmd,nCmdLen);
	ks_calcmac(uRandom,uDAMK,2,uCmd,nCmdLen,uMac);
	dec2hex(uMac,4,szMac);
	return 0;
}
//用PSAM卡计算DF03下的修改文件的MAC 
int __stdcall CalcDF03SafeMac4Sam(const char *szCardNo,const char *szCmdbuf,char *szMac)
{
	TRACE_FUNC("CalcDF03SafeMac4Sam");
	char szBuf[512];

	string sCmd,sMacData;
	vector<string> CmdVector;
	int ret;
	int nCmdLen;
	byte uCmd[256];
	byte uResp[256],nRespLen,rlen,rbuf[256];
	byte uRandom[16];
	char szRandom[17];
	ret=GetRandomNum(uRandom,szRandom);
	if(ret)
	{
		return ret;
	}
	sCmd="ATR";
	CmdVector.push_back(sCmd);

	sCmd="00a4000002df03";
	CmdVector.push_back(sCmd);
	
	sCmd="801A280108";
	sCmd+=szCardNo;
	if(strlen(szCardNo)==8)
		sCmd+="80000000";
	CmdVector.push_back(sCmd);
	
	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdbuf);
	memcpy(szBuf,szCmdbuf,nCmdBufLen);
	nCmdBufLen/=2;
	if( nCmdBufLen%8 )
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);
	else				 
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",16);		
	
	sMacData=szRandom;
	sMacData+=szBuf;

	int nMacDataLen=sMacData.size()/2;
	const char *pBuf=sMacData.c_str();
	int nBlockLen=0x30;
	if(nMacDataLen>nBlockLen)
	{
		sCmd="80FA0700";
		sCmd+=ltohex(nBlockLen);
		sCmd.append(pBuf,nBlockLen*2);
		CmdVector.push_back(sCmd);
		pBuf+=nBlockLen*2;
		nMacDataLen -= nBlockLen;
		if(nMacDataLen>nBlockLen)
		{
			sCmd="80FA0300";
			sCmd+=ltohex(nBlockLen);
			sCmd.append(pBuf,nBlockLen*2);
			CmdVector.push_back(sCmd);
			nMacDataLen -= nBlockLen;
			pBuf+=nBlockLen*2;
		}
		sCmd="80FA0100";
		sCmd+=ltohex(nMacDataLen);
		sCmd.append(pBuf,nMacDataLen*2);
		CmdVector.push_back(sCmd);
	}
	else
	{
		sCmd="80FA0500";
		sCmd+=ltohex(nMacDataLen);
		sCmd+=sMacData;
		CmdVector.push_back(sCmd);
	}
	sCmd="00C0000004";
	CmdVector.push_back(sCmd);
	
	for(int i=0;i<CmdVector.size();i++)
	{
		sCmd=CmdVector[i];
		if("ATR"==sCmd)
		{
			ret=ks_cpureset4sam(&rlen,rbuf);
			if(ret)
			{
				return ret;
			}
			continue;
		}
		string_replace(sCmd," ","");
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
		ret=ks_cpuapdu4sam(uCmd,nCmdLen,uResp,nRespLen);
		if(ret)
		{
			//sMsg=sCmd+":"+ltohex(ret);
			//MessageBox(NULL,sMsg.c_str(),"",MB_OK);
			return ret;
		}
	}
	dec2hex(uResp,4,szMac);
	return 0;
}
//充值
//计算MAC报文
int __stdcall ks_calcmac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,unsigned char *uMacData,int iMacDataLen,unsigned char *uMac)
{
	TRACE_FUNC("ks_calcmac");
	int i=0;
	des_context ctx;
	BYTE uTemp[16];
	// 初始化MAC计算初值 ==> temp
	memset(uTemp, 0, sizeof(uTemp));
	memcpy(uTemp, uRandom, 8 * sizeof(BYTE));
	// 格式化输入值: 填 "80 00 00 ...", 凑8字节长度 ==> buf
	int nBlock=0;
	if(iMacDataLen%8)
		nBlock = iMacDataLen/8 + 1; // 总块数
	else
		nBlock = iMacDataLen/8;
	byte* buf = new byte[nBlock*8+1];
	memset(buf, 0, nBlock*8*sizeof(byte));
	memcpy(buf, uMacData, iMacDataLen*sizeof(byte));
	buf[iMacDataLen] = 0x80;
	des_set_key(&ctx,uKey);
	for (i=0; i<nBlock; i++)
	{
		// temp .EOR. block[i] ==> temp
		for(int j=0; j<8; j++)
		{
			uTemp[j] ^= buf[i*8+j];
		}
		// temp ==> DES ==> temp
		des_encrypt(&ctx,uTemp,uTemp);
		if (nKeyLen==3)
		{
			des_set_key(&ctx,uKey+8);
			des_decrypt(&ctx,uTemp,uTemp);
			des_set_key(&ctx,uKey);
			des_encrypt(&ctx,uTemp,uTemp);
		}
	}
	delete []buf;
	
	if (nKeyLen == 2)
	{
		des_set_key(&ctx,uKey+8);
		des_decrypt(&ctx, uTemp,uTemp);
		des_set_key(&ctx,uKey);
		des_encrypt(&ctx,uTemp,uTemp);
	}
	// temp 左四位 ==> MAC
	memcpy(uMac, uTemp, 4 * sizeof(byte)); 
	return 0;
}
int __stdcall  ks_calctransmac(ST_TRANSPACK *transpack,char *sMac)
{
	TRACE_FUNC("ks_calctransmac");
	int nRet=0,nLen=0;
	int nSendLen=0;
	unsigned char ucRespLen=0;
	
	unsigned char nRespLen=0;
	char szMac[9]={0};
	//检查
	if(strlen(transpack->sCardPhyID)!=16)
	{
		if(strlen(transpack->sCardPhyID)==8)
		{
			strcat(transpack->sCardPhyID,"80000000");
		}
		else
		{
			ks_setlasterr("物理卡号长度错误",-1);
			TRACE2_LOG(("物理卡号[%s]长度错误",transpack->sCardPhyID));
		}
	}
	if(strlen(transpack->sTermno)!=12)
	{
		ks_setlasterr("终端编号长度错误",-1);
		TRACE2_LOG(("终端编号[%s]长度错误",transpack->sTermno));
		return -1;
	}
	if(strlen(transpack->sTransDate)!=8)
	{
		ks_setlasterr("交易日期长度错误",-1);
		TRACE2_LOG(("交易日期[%s]长度错误",transpack->sTransDate));
		return -1;
	}
	if(strlen(transpack->sTransTime)!=6)
	{
		ks_setlasterr("交易时间长度错误",-1);
		TRACE2_LOG(("交易时间[%s]长度错误",transpack->sTransDate));
		return -1;
	}
	if(transpack->nTransAmt==0)
	{
		ks_setlasterr("交易金额不能为0",-1);
		TRACE2_LOG((ks_geterrmsg(NULL)));
		return -1;

	}
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lsafe_level",transpack->nTransType); 	// 交易类型
	clt.SetIntFieldByName("lvol0",transpack->nCardNo); 				// 交易卡号
	clt.SetStringFieldByName("sstation1",transpack->sCardPhyID); 	// 物理卡号
	if(transpack->nTransType)
		clt.SetIntFieldByName("lvol6",transpack->nPayCardCnt); 			// 交易前次数
	else
		clt.SetIntFieldByName("lvol6",transpack->nDpsCardCnt); 			// 交易前次数

	clt.SetIntFieldByName("lvol7",transpack->nBefBalance); 			// 入卡值
	clt.SetDoubleFieldByName("lvol1",transpack->nTransAmt); 		// 金额(分)
	clt.SetStringFieldByName("sdate0",transpack->sTransDate);		//交易日期
	clt.SetStringFieldByName("stime0",transpack->sTransTime);		//交易时间
	clt.SetStringFieldByName("sstock_code",transpack->sRandom); 	// 随机数
	clt.SetStringFieldByName("sserial0",transpack->sTermno); 		// 终端号
	clt.SetIntFieldByName("lserial0",transpack->nTermSeqno); 		// 终端流水号
	clt.SetStringFieldByName("semp",transpack->sOperCode); 			// 操作员
	// 充值获取 mac2
	if(!clt.SendRequest(846313,5000))
	{
		// TODO : 可能是超时
		char szMsg[256]={0};
		char errmsg[256]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg,clt.GetReturnCode());
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		// 充值失败
		clt.GetReturnMsg(transpack->sErrMsg);
		TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,transpack->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

	//	clt.GetIntFieldByName("lserial1",(int*)&(transpack->nHostSeqno)); // 后台流水号
	//	clt.GetIntFieldByName("lvol0",&ret_data); // 交易卡号
		GET_PACK_STR(clt,"sstock_code2",szMac);
		strcpy(sMac,szMac);
	}
	else
	{
		TRACE2_LOG(("充值失败cardid[%d],ret[%X]",transpack->nCardNo,nRet));
		// 返回的数据有问题
		ks_setlasterr("主机返回无数据",-1);
		return -1;
	}
	return 0;
}
int __stdcall ks_calctransmac4sam(ST_TRANSPACK *transpack,char *sMac)
{
	TRACE_FUNC("ks_calctransmac4sam");
	string sCmd;
	unsigned char uCmd[256],uResp[256],nRespLen;
	unsigned char rbuf[256],rlen;
	int nCmdLen,ret;
	char temp[20]="";
	if(strlen(transpack->sCardPhyID)!=16)
	{
		if(strlen(transpack->sCardPhyID)==8)
		{
			strcat(transpack->sCardPhyID,"80000000");
		}
		else
		{
			ks_setlasterr("物理卡号长度错误",-1);
			TRACE2_LOG(("物理卡号[%s]长度错误",transpack->sCardPhyID));
		}
	}
	if(strlen(transpack->sTermno)!=12)
	{
		ks_setlasterr("终端编号长度错误",-1);
		TRACE2_LOG(("终端编号[%s]长度错误",transpack->sTermno));
		return -1;
	}
	if(strlen(transpack->sTransDate)!=8)
	{
		ks_setlasterr("交易日期长度错误",-1);
		TRACE2_LOG(("交易日期[%s]长度错误",transpack->sTransDate));
		return -1;
	}
	if(strlen(transpack->sTransTime)!=6)
	{
		ks_setlasterr("交易时间长度错误",-1);
		TRACE2_LOG(("交易时间[%s]长度错误",transpack->sTransDate));
		return -1;
	}
	if(transpack->nTransAmt==0)
	{
		ks_setlasterr("交易金额不能为0",-1);
		TRACE2_LOG((ks_geterrmsg(NULL)));
		return -1;
	}
	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		return ret;
	}
	sCmd = "00A4000002DF03";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
	ret=ks_cpuapdu4sam(uCmd,nCmdLen,uResp,nRespLen);
	if(ret)
	{
		//sMsg=sCmd+":"+ltohex(ret);
		//MessageBox(NULL,sMsg.c_str(),"",MB_OK);
		return ret;
	}
	memset(uCmd,0,sizeof uCmd);
	memset(uResp,0,sizeof uResp);
	sCmd = "807000001C";
	sCmd += transpack->sRandom;
	sprintf(temp,"%04X",transpack->nPayCardCnt);
	sCmd += temp;
	sprintf(temp,"%08X",transpack->nTransAmt);
	sCmd += temp;
	sCmd += "06";
	sCmd += transpack->sTransDate;
	sCmd += transpack->sTransTime;
	sCmd += "0100";
	//sprintf(temp,"%016d",transpack->nCardNo);
	//sCmd += temp;
	sCmd += transpack->sCardPhyID;
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
	ret=ks_cpuapdu4sam(uCmd,nCmdLen,uResp,nRespLen);
	if(ret)
	{
		return ret;
	}

	sCmd = "00C00000";
	sprintf(temp,"%02X",uResp[1]);
	sCmd += temp;
	memset(uCmd,0,sizeof uCmd);
	memset(uResp,0,sizeof uResp);
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
	ret=ks_cpuapdu4sam(uCmd,nCmdLen,uResp,nRespLen);
	if(ret)
	{
		return ret;
	}
	dec2hex(uResp+4,4,sMac);
	return 0;
}

int  __stdcall ks_addmoney(ST_TRANSPACK *deposit)
{
	TRACE_FUNC("ks_addmoney");
	string sCmd;
	int nRet=0,nLen=0;
	char sHexStr[256]={0};
	unsigned char ucRespData[256];
	int nSendLen=0;
	unsigned char ucRespLen=0;	
	char termno[13]={0};
	unsigned char sMac1[9]={0};
	char temp[256];
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	nRet=c->SelectADF();
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	nRet=c->VerifyPin(NULL);
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	sCmd="805000020B01";
	//交易金额
	//sprintf(sSendData+strlen(sSendData),"%02X%02X%02X%02X%012d",
	//	deposit->nTransAmt/256/256/256,
	//	deposit->nTransAmt/256/256,
	//	deposit->nTransAmt/256,
	//	deposit->nTransAmt%256,0);
	//终端号
	byte ucTransAmt[5]={0};
	lpad(deposit->sTermno,12,'0');
	memset(sHexStr,0,sizeof(sHexStr));
	set_4byte_int(ucTransAmt,deposit->nTransAmt);
	dec2hex(ucTransAmt,4,sHexStr);
	sCmd+=sHexStr;
	sCmd+=deposit->sTermno;
	//请求报文长度
	
	TRACE2_LOG(("init for load req[%s]",sCmd.c_str()));
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		ks_setlasterr("充值初始化失败",nRet);
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen,temp);
	TRACE2_LOG(("init for load resp[%s]",temp));
	char sMac2[9]={0};
	memset(sMac2,0,sizeof sMac2);
	//卡余额
	int nBefBal=get_4byte_int(ucRespData);
	//消费次数
	int nDptCnt=get_2byte_int(ucRespData+4);
	//取随机数
	dec2hex(ucRespData+8,4,deposit->sRandom);

	TRACE2_LOG(("random[%s]date[%s]time[%s]",deposit->sRandom,deposit->sTransDate,deposit->sTransTime));
	//充值次数
	deposit->nDpsCardCnt=nDptCnt;

	if(nBefBal != deposit->nBefBalance)
	{
		if(nBefBal == deposit->nAftBalance)
		{
			// 认为已经加钱成功了
			TRACE2_LOG(("交易已成功"));
			return 0;
		}
		ks_setlasterr("交易前余额与卡中不一致",-1);		
		return -1;
	}
	nRet=ks_calctransmac(deposit,sMac2);
	if(nRet)
	{
		TRACE2_LOG(("计算MAC2失败 ret=%X",nRet));
		return nRet;
	}
	// 发起写卡请求
	memset(ucRespData,0,sizeof ucRespData);
	sCmd="805200000B";
	sCmd.append(deposit->sTransDate,8);
	sCmd.append(deposit->sTransTime,6);
	sCmd.append(sMac2,8);
	TRACE2_LOG(("credit for load req[%s]",sCmd.c_str()));
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		TRACE2_LOG(("充值写卡失败 ret[%X]",deposit->nCardNo,nRet));
		deposit->nErrCode = nRet;
		ks_setlasterr("写卡失败",nRet);
		return nRet;
	}
	TRACE2_LOG(("充值成功cardid[%d],amount[%d],befbala[%d]aftbala[%d],serial[%d]",
		deposit->nCardNo,deposit->nTransAmt,deposit->nBefBalance,deposit->nAftBalance,deposit->nHostSeqno));
	return 0;	
}
int  __stdcall ks_paymoney(ST_TRANSPACK *payment)
{
	TRACE_FUNC("ks_paymoney");
	string sCmd;
	char sHexStr[256]="";
	int  nSendDataHexLen=0;
	unsigned char ucSendData[256]="";
	int  nSendDataLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;

	int nRet=0,nLen=0;
	char sMac1[9]={0};
	char temp[256]={0};
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	nRet=c->SelectADF();
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	sCmd="805001020B01";
	//交易金额
	byte ucTransAmt[5]={0};
	memset(sHexStr,0,sizeof(sHexStr));
	lpad(payment->sTermno,12,'0');
	set_4byte_int(ucTransAmt,payment->nTransAmt);
	dec2hex(ucTransAmt,4,sHexStr);
	sCmd+=sHexStr;
	sCmd+=payment->sTermno;
	//请求报文长度
	TRACE2_LOG(("init for payment req[%s]",sCmd.c_str()));
	memset(ucRespData, 0,sizeof(ucRespData));
	nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(nRet)
	{
		if(nRet==0x9302)
		ks_setlasterr("消费初始化失败",nRet);
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen+2,temp);
	TRACE2_LOG(("init for load resp[%s]",temp));
	//卡余额
	int nBefBal=get_4byte_int(ucRespData);
	//消费次数
	int nPayCnt=get_2byte_int(ucRespData+4);
	//取随机数
	dec2hex(ucRespData+11,4,payment->sRandom);

	if(nBefBal != payment->nBefBalance)
	{
		if(nBefBal == payment->nAftBalance)
		{
			// 认为已经加钱成功了
			TRACE2_LOG(("交易已成功"));
			return 0;
		}
		ks_setlasterr("交易前余额与卡中不一致",-1);		
		return -1;
	}
	payment->nPayCardCnt=nPayCnt;

	byte sDate[20],sTime[20];
	memset(sDate,0,sizeof sDate);
	memset(sTime,0,sizeof sTime);
#if 1
	// 计算MAC1
	nRet=ks_calctransmac(payment,sMac1);
	if(nRet)
	{
		TRACE2_LOG(("计算MAC错误,ret[%X]",nRet));
		return nRet;
	}
#else
	nRet =ks_calctransmac4sam(payment,sMac1);
	if(nRet)
	{
		TRACE2_LOG(("计算MAC错误,ret[%X]",nRet));
		return nRet;
	}
#endif
	// 发起写卡请求
	byte ucTermSeqno[5]={0};
	set_4byte_int(ucTermSeqno,payment->nTermSeqno);
	dec2hex(ucTermSeqno,4,sHexStr);
	sHexStr[8]=0;
	sCmd="805401000F";
	sCmd+=sHexStr;
	sCmd.append(payment->sTransDate,8);
	sCmd.append(payment->sTransTime,6);
	sCmd += sMac1;
	TRACE2_LOG(("debit for load req[%s]",sCmd.c_str()));
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		TRACE2_LOG(("扣款失败cardid[%d],ret[%X]",payment->nCardNo,nRet));
		payment->nErrCode = nRet;
		ks_setlasterr("消费写卡失败",nRet);
		return nRet;
	}
	TRACE2_LOG(("扣款成功cardid[%d],amount[%d],befbala[%d]aftbala[%d],serial[%d]",
		payment->nCardNo,payment->nTransAmt,payment->nBefBalance,payment->nAftBalance,payment->nHostSeqno));

	payment->nErrCode = 0;
	return 0;	
}
int __stdcall ks_encryptkey(unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen)
{
	TRACE_FUNC("ks_encryptkey");
	int i=0;
	des_context ctx;
	des3_context ctx3;
	// 格式化输入值: 填 "80 00 00 ...", 凑8字节长度 ==> buf
	int nBlock=0;
	if(iDataLen%8)
		nBlock = iDataLen/8 + 1; // 总块数
	else
		nBlock = iDataLen/8;
	BYTE* buf = new BYTE[nBlock*8];
	memset(buf, 0, nBlock*8*sizeof(BYTE));
	memcpy(buf, uData, iDataLen*sizeof(BYTE));
	buf[iDataLen] = 0x80;
	if(nKeyLen==2)
	{
		des3_set_2keys(&ctx3,uKey,uKey+8);
	}
	else
	{
		des_set_key(&ctx,uKey);
	}
	for (i=0; i<nBlock; i++)
	{
		// temp ==> DES ==> temp
		if (nKeyLen==2)
		{
			des3_encrypt(&ctx3,buf+i*8,uOutData+i*8);
		}
		else
		{
			des_encrypt(&ctx,buf+i*8,uOutData+i*8);
		}
	}
	delete []buf;
	iOutLen=nBlock*8;
	return 0;
}

int __stdcall ks_comminit(const char *svrip,int svrport,int svrfunc)
{
	TRACE_FUNC("ks_comminit");
	if(KS_YKT_Clt::Initialize(svrip,svrport,svrfunc))
	{
		char msg[512] = {0};
		KS_YKT_Clt::set_xpack_path(g_cpack_path);
		int nRet=CardTypeManager::instance()->initComm(svrip,svrport,svrfunc);
		if(nRet)
		{
			CardTypeManager::instance()->getErrorMsg(msg);
			ks_setlasterr(msg);
			return nRet;
		}
		int debug = 0;
		if(g_license.is_load_pubkey())
		{
			g_license.get_public_int_param("kscardlib.bcc.debug",&debug);
		}
		KS_YKT_Clt::SetDebug(debug);
		return 0;
	}
	ks_setlasterr("设置通讯参数失败",-1);
	return -1;
}
int __stdcall ks_deposit(ST_TRANSPACK *deposit,int must_online)
{
	TRACE_FUNC("ks_deposit");
	int nRet=0,nLen=0;
	int nSendLen=0x00;
	unsigned char nRespLen=0;
	int ret_data;
	

	// TODO : 暂时不支持脱机充值
	//if(!must_online)
	//	return -1;

	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	nRet=ks_readpsamtermno(deposit->sTermno,0);
	if(nRet)
	{
		return nRet;
	}
	TRACE2_LOG(("physical no[%s]",deposit->sCardPhyID));
	// 向后台发起充值请求
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lvol0",deposit->nCardNo); // 交易卡号
	clt.SetIntFieldByName("lvol6",deposit->nDpsCardCnt); // 交易前次数
	clt.SetStringFieldByName("sserial0",deposit->sTermno); // 终端号
	clt.SetIntFieldByName("lvol7",deposit->nBefBalance); // 入卡值
	clt.SetDoubleFieldByName("damt0",deposit->nTransAmt/100.0); // 金额
	clt.SetStringFieldByName("semp",deposit->sOperCode); // 操作员
	clt.SetStringFieldByName("sstation0",deposit->sCardPhyID); // 物理卡号
	clt.SetIntFieldByName("lvol9",deposit->nFundType); // 充值类型 1 现金充值
	clt.SetStringFieldByName("scust_auth2",deposit->sVoucherNo); // 

	// 充值请求
	if(must_online)
	{
		if(!clt.SendRequest(846312,5000))
		{
			// TODO : 可能是超时
			char szMsg[512]={0};
			char errmsg[512]={0};
			clt.GetReturnMsg(szMsg);
			sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
			ks_setlasterr(errmsg,clt.GetReturnCode());
			return -1;
		}
		if((nRet = clt.GetReturnCode())!=0)
		{
			// 充值失败
			clt.GetReturnMsg(deposit->sErrMsg);
			ks_setlasterr(deposit->sErrMsg,nRet);
			TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,deposit->sErrMsg));
			return nRet;
		}
		if(clt.HasMoreRecord())
		{
			clt.GetNextPackage();

			clt.GetIntFieldByName("lserial1",(int*)&(deposit->nHostSeqno)); // 后台流水号
			clt.GetIntFieldByName("lvol0",&ret_data); // 交易卡号
			if(ret_data != deposit->nCardNo)
			{
				// TODO: 有问题，要冲正
				return -2;
			}
			clt.GetIntFieldByName("lvol8",&(deposit->nAftBalance)); // 出卡值
			GET_PACK_STR(clt,"sdate0",deposit->sTransDate);
			GET_PACK_STR(clt,"stime0",deposit->sTransTime);
			GET_PACK_STR(clt,"vsmess",deposit->sErrMsg);
			// 实际交易金额
			ret_data = deposit->nAftBalance - deposit->nBefBalance;
			// 调用充值接口
			TRACE2_LOG((deposit->sErrMsg));
			// TODO : 写卡失败需要调用冲正接口
			nRet=c->AddMoney(deposit);
			if(nRet)
			{
				ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
				return nRet;
			}
		}
		else
		{
			// 返回的数据有问题
			return -1;
		}
	}
	else
	{
		deposit->nAftBalance = deposit->nBefBalance+deposit->nTransAmt;
		do_getcurrent_datetime(deposit->sTransDate,deposit->sTransTime);
		// TODO : 写卡失败需要调用冲正接口
		nRet=c->AddMoney(deposit);
		if(nRet)
		{
			ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
			return nRet;
		}
	}
	return 0;
}
//读PSAM卡终端编号
int __stdcall ks_readpsamtermno(char *termno,int need_request)
{
	TRACE_FUNC("ks_readpsamtermno");
	int ret=0;
	ks_psamcard_base *c = CardTypeManager::instance()->getPSAMCardType();
	ret=c->ReadPSAMTermno(termno);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),ret);
		return ret;
	}
	return 0;
}
//读PSAM卡终端交易流水号
int __stdcall ks_readpsamtermseqno(size_t& termseqno,int need_request)
{
	TRACE_FUNC("ks_readpsamtermseqno");
	string sCmd,sMsg;
	int ret(0);
	char szTermno[13]={0};
	byte rlen,rbuf[256];
	byte ucRespData[256]={0},ucRespLen(0);

	if(need_request)
	{
		ret=ks_cpureset4sam(&rlen,rbuf);
		if(ret)
		{
			return ret;
		}
	}
	sCmd="00a4000002df03";
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("选择目录DF03失败",-1);
		return ret;
	}
	memset(ucRespData,0,sizeof(ucRespData));	
	ret=ReadBinaryFile4Sam(0x19,0x00,4,ucRespData);
	if(ret)
	{
		ks_setlasterr("读PSAM卡0x18文件失败",ret);
		return ret;
	}	
	for(int i=0;i<4;i++)
	{
		if(ucRespData[i]==0xFF)
			ucRespData[i]=0;
	}
	termseqno=get_4byte_int(ucRespData);
	return 0;
}
//读卡器签到
int __stdcall ks_login(int termid,int& shopid,char shopname[61])
{
	TRACE_FUNC("ks_login");
	shopid=0;
	string sCmd;
	int nRet=0,nLen=0;	
	char sMsg[256];
	char mainkey[64] = "";
	/*
	if(!g_ReaderPara.devhd)
	{
		ks_setlasterr("读卡器通讯端口未打开",-1);
		return -1;
	}
	*/
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	char sTermno[13]={0};
	//读取PSAM卡的终端号
	nRet=ks_readpsamtermno(sTermno,1);
	if(nRet)
	{
		if(nRet != KS_NOTSUPPORT)
		return nRet;
	}
	KS_YKT_Clt clt;
	clt.SetStringFieldByName("sserial0",sTermno); 		//终端号
	clt.SetIntFieldByName("lwithdraw_flag",termid);		//终端编号
	// 支付交易
	if(!clt.SendRequest(850003,5000))
	{
		// TODO : 可能是超时
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(sMsg);
		// 充值失败
		ks_setlasterr(sMsg,nRet);
		TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,sMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		clt.GetIntFieldByName("lvol3",&shopid);
		clt.GetStringFieldByName("sall_name",shopname,60);
		clt.GetStringFieldByName("scust_limit",mainkey,60);
		// TODO : 兼容旧版本对于M1读写卡的功能
		//g_CardType->SetMifare1Key(mainkey);
		if(strlen(mainkey)>0)
		{
			ks_cardtype_base *c;
			int i;
			for(i = 0;i < CardTypeManager::instance()->getCardTypeCount();++i)
			{
				c = CardTypeManager::instance()->getCardTypeByIdx(i);
				c->SetMifare1Key(mainkey);
			}
			TRACE_LOG("设置M1密钥");
		}
		//TRACE2_LOG(("refno[%s]mac[%s]",payment->sRefno,payment->sMac));
	}
	else
	{
		// 返回的数据有问题
		TRACE2_LOG(("返回的数据有问题"));
		return -1;
	}
	return 0;
}
//读卡器签到
int __stdcall ks_usersignin(const char *user,const char* userpwd)
{
	int nRet=0;	
	char sMsg[256];
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	char sTermno[13]={0};
	//读取PSAM卡的终端号
	nRet=ks_readpsamtermno(sTermno,1);
	if(nRet)
	{
		return nRet;
	}
	KS_YKT_Clt clt;
	char szUser[33]={0};
	char szUserPwd[33]={0};
	strcpy(szUser,user);
	strcpy(szUserPwd,userpwd);
	clt.SetStringFieldByName("sserial0",sTermno); 		//PSAM卡终端编号
	//clt.SetIntFieldByName("lwithdraw_flag",termid);	//设备终端编号
	clt.SetStringFieldByName("semp_no",szUser);			//用户名
	clt.SetStringFieldByName("semp_pwd",szUserPwd);		//用户密码

	if(!clt.SendRequest(850004,5000))
	{
		// TODO : 可能是超时
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(sMsg);
		// 充值失败
		ks_setlasterr(sMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,sMsg));
		return nRet;
	}
	return 0;
}
//取服务器时钟
int  __stdcall ks_getsvrdatetime(char *svr_date,char *svr_time)
{
	TRACE_FUNC("ks_getsvrdatetime");
	int nRet=0;	

	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	KS_YKT_Clt clt;

	if(!clt.SendRequest(820522,5000))
	{
		// TODO : 可能是超时
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		char szErrMsg[256];
		clt.GetReturnMsg(szErrMsg);
		ks_setlasterr(szErrMsg,nRet);
		TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,szErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		if(svr_date!=NULL)
			clt.GetStringFieldByName("sdate0",svr_date,8);
		if(svr_time!=NULL)
			clt.GetStringFieldByName("stime0",svr_time,6);
	//	TRACE2_LOG(("svr_date[%s]svr_date[%s]",svr_date,svr_time));
	}
	else
	{
		TRACE2_LOG(("返回的数据有问题"));
		return -1;
	}
	return 0;	
}
//联机支付
int  __stdcall ks_payment(ST_TRANSPACK *payment,int must_online)
{
	TRACE_FUNC("ks_payment");
	int nRet=0;	
	
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	//TRACE2_LOG(("physical no[%s]",payment->sCardPhyID));
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	if(payment->nBefBalance<payment->nTransAmt)
	{
		ks_setlasterr("卡余额不足",-1);
		return -1;
	}
	nRet=ks_readpsamtermno(payment->sTermno,1);
	if(nRet)
	{
		return nRet;
	}
	nRet = c->InitForTrans(payment,ks_cardtype_base::TRNS_TYPE_PURCHASE);
	if(nRet)
		return nRet;
	if(must_online == 1)
	{
		// 向后台发起支付请求
		KS_YKT_Clt clt;
		payment->nPayType=10;
		payment->nTransType=1;
		clt.SetIntFieldByName("lbank_acc_type",1);					//模拟入账
		clt.SetIntFieldByName("lwithdraw_flag",payment->nTermID);	//终端号
		clt.SetIntFieldByName("lvol4",payment->nTermID);			//终端号
		clt.SetIntFieldByName("lcert_code",payment->nPayCode);		//支付代码
		clt.SetIntFieldByName("lserial0",payment->nTermSeqno);		//PSAM流水号
		clt.SetIntFieldByName("lvol0",payment->nCardNo); 			// 交易卡号
		clt.SetIntFieldByName("lvol6",payment->nPayCardCnt); 		// 交易前次数
		clt.SetStringFieldByName("sserial0",payment->sTermno); 		// 终端号
		clt.SetIntFieldByName("lvol7",payment->nBefBalance); 		// 入卡值
		clt.SetIntFieldByName("lvol1",payment->nTransAmt); 			// 金额
		clt.SetStringFieldByName("semp",payment->sOperCode); 		// 操作员
		clt.SetStringFieldByName("sstation1",payment->sCardPhyID); 	// 物理卡号
		clt.SetIntFieldByName("lvol9",payment->nFundType); 			//交易类型
		clt.SetStringFieldByName("stx_pwd",payment->sCardPwd); 		//卡密码
	//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo);// 
	//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
	//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
		clt.SetStringFieldByName("sstock_code",payment->sRandom);	// 随机数

		// 支付交易
		if(!clt.SendRequest(850005,10000))
		{
			// TODO : 可能是超时
			char szMsg[512]={0};
			char errmsg[512]={0};
			clt.GetReturnMsg(szMsg);
			sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
			ks_setlasterr(errmsg);
			return -1;
		}
		if((nRet = clt.GetReturnCode())!=0)
		{
			clt.GetReturnMsg(payment->sErrMsg);
			// 充值失败
			ks_setlasterr(payment->sErrMsg,nRet);
			TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
			return nRet;
		}
		if(clt.HasMoreRecord())
		{
			clt.GetNextPackage();
			clt.GetStringFieldByName("sphone3",payment->sRefNo,14);
			clt.GetStringFieldByName("saddr",payment->sMac,8);
			TRACE2_LOG(("refno[%s]mac[%s]",payment->sRefNo,payment->sMac));
		}
		else
		{
			// 返回的数据有问题
			TRACE2_LOG(("返回的数据有问题"));
			return -1;
		}
		//发起正式请求
		clt.SetIntFieldByName("lwithdraw_flag",payment->nTermID);	//终端号
		clt.SetIntFieldByName("lvol4",payment->nTermID);			//终端号
		clt.SetIntFieldByName("lcert_code",payment->nPayCode);		//支付代码
		clt.SetStringFieldByName("sphone3",payment->sRefNo);
		clt.SetStringFieldByName("saddr",payment->sMac);
		clt.SetIntFieldByName("lbank_acc_type",2);						//正式入账
		// 支付交易
		if(!clt.SendRequest(850005,10000))
		{
			// TODO : 可能是超时
			//重发一次
			if(!clt.SendRequest(850005,5000))
			{
				// TODO : 可能是超时
				char szMsg[512]={0};
				char errmsg[512]={0};
				clt.GetReturnMsg(szMsg);
				sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
				ks_setlasterr(errmsg);			
				return -1;
			}
		}
		if((nRet = clt.GetReturnCode())!=0)
		{
			clt.GetReturnMsg(payment->sErrMsg);
			// 充值失败
			ks_setlasterr(payment->sErrMsg,nRet);
			TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
			return nRet;
		}
		if(clt.HasMoreRecord())
		{
			clt.GetNextPackage();

	//		clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
			clt.GetIntFieldByName("lvol0",&payment->nCardNo);				// 交易卡号
			clt.GetIntFieldByName("lvol8",&payment->nAftBalance);		//交易后余额
			//clt.GetIntFieldByName("lsafe_level2",);					//小钱包余额
			clt.GetStringFieldByName("sdate3",payment->sTransDate,9);	// 交易日期
			clt.GetStringFieldByName("stime3",payment->sTransTime,7);	// 交易时间
		}
		else
		{
			TRACE2_LOG(("返回的数据有问题"));
			return -1;
		}
	}
	else
	{
		payment->nAftBalance = payment->nBefBalance-payment->nTransAmt;
		do_getcurrent_datetime(payment->sTransDate,payment->sTransTime);
	}
	// 发起写卡请求
	nRet=ks_setcardbal(payment);
	if(nRet)
	{
		TRACE2_LOG(("写卡失败 ret[%d]",nRet));
		return nRet;
	}
	return 0;	
}
//消费冲正
int  __stdcall ks_pay_reverse(ST_TRANSPACK *payment,int must_online)
{
	TRACE_FUNC("ks_pay_reverse");
	int nRet=0;	

	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	nRet=ks_readpsamtermno(payment->sTermno,1);
	if(nRet)
	{
		return nRet;
	}
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	//nRet=ks_readpsamtermseqno(payment->nTermSeqno,0);
	//if(nRet)
	//{
	//	return nRet;
	//}
	/*
	if((nRet=gKsCard.SelectSchoolPacketDir(ucRespData))!=0 )
		return nRet;	
	if( (nRet=gKsCard.SelectSchoolPacketDir(ucRespData))!=0 ) return nRet;	
	*/
	nRet = c->InitForTrans(payment,ks_cardtype_base::TRNS_TYPE_LOAD);
	if(nRet)
		return nRet;
	byte sDate[20],sTime[20];
	memset(sDate,0,sizeof sDate);
	memset(sTime,0,sizeof sTime);
	// 向后台发起支付请求
	KS_YKT_Clt clt;
	payment->nPayType=0;
	payment->nTransType=0;
	clt.SetIntFieldByName("lwithdraw_flag",payment->nTermID);	//终端号
	clt.SetIntFieldByName("lcert_code",payment->nPayCode);		//支付代码
	//	clt.SetIntFieldByName("lcert_code",payment->nPayType);	//支付类型
	clt.SetIntFieldByName("lserial0",payment->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",payment->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol5",payment->nDpsCardCnt); 		// 充值次数
	//clt.SetIntFieldByName("lvol6",payment->nPayCardCnt); 		// 消费次数
	clt.SetStringFieldByName("sserial0",payment->sTermno); 		// 终端号
	clt.SetIntFieldByName("lvol7",payment->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",payment->nTransAmt); 			// 金额
	clt.SetStringFieldByName("semp",payment->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",payment->sCardPhyID); 	// 物理卡号
	clt.SetIntFieldByName("lvol9",payment->nFundType); 			//交易类型
	//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo); 		// 
	//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
	//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
	clt.SetStringFieldByName("sphone3",payment->sRefNo);		//交易参考号
	clt.SetStringFieldByName("saddr",payment->sMac);			//MAC校验
	// 消费冲正
	if(!clt.SendRequest(846317,5000))
	{
		// TODO : 可能是超时
//		ks_setlasterr("与主机通讯超时",-1);
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		//		clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
//		clt.GetIntFieldByName("lvol0",&payment->nCardNo);			// 交易卡号
		clt.GetIntFieldByName("lvol8",&payment->nAftBalance);		//交易后余额
		//clt.GetIntFieldByName("lsafe_level2",);					//小钱包余额
		clt.GetStringFieldByName("sdate3",payment->sTransDate,9);	// 交易日期
		clt.GetStringFieldByName("stime3",payment->sTransTime,7);	// 交易时间
	}
	else
	{
		TRACE2_LOG(("返回的数据有问题"));
		return -1;
	}
	// 发起写卡请求
	nRet=ks_setcardbal(payment);
	if(nRet)
	{
		TRACE2_LOG(("写卡失败 ret[%d]",nRet));
		return nRet;
	}
	return 0;	
}
//消费冲正
int  __stdcall ks_paycancel(ST_TRANSPACK *payment)
{
	TRACE_FUNC("ks_paycancel");
	int nRet=0;	

	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	nRet=ks_readpsamtermno(payment->sTermno,1);
	if(nRet)
	{
		return nRet;
	}
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	//nRet=ks_readpsamtermseqno(payment->nTermSeqno,0);
	//if(nRet)
	//{
	//	return nRet;
	//}
	/*
	if((nRet=gKsCard.SelectSchoolPacketDir(ucRespData))!=0 )
		return nRet;	
	if( (nRet=gKsCard.SelectSchoolPacketDir(ucRespData))!=0 ) return nRet;	
	*/
	nRet = c->InitForTrans(payment,ks_cardtype_base::TRNS_TYPE_LOAD);
	if(nRet)
		return nRet;
	byte sDate[20],sTime[20];
	memset(sDate,0,sizeof sDate);
	memset(sTime,0,sizeof sTime);
	// 向后台发起支付请求
	KS_YKT_Clt clt;
	payment->nPayType=0;
	payment->nTransType=0;
	clt.SetIntFieldByName("lwithdraw_flag",payment->nTermID);	//终端号
	clt.SetIntFieldByName("lcert_code",payment->nPayCode);		//支付代码
	//	clt.SetIntFieldByName("lcert_code",payment->nPayType);	//支付类型
	clt.SetIntFieldByName("lserial0",payment->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",payment->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol5",payment->nDpsCardCnt); 		// 充值次数
	//clt.SetIntFieldByName("lvol6",payment->nPayCardCnt); 		// 消费次数
	clt.SetStringFieldByName("sserial0",payment->sTermno); 		// 终端号
	clt.SetIntFieldByName("lvol7",payment->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",payment->nTransAmt); 			// 金额
	clt.SetStringFieldByName("semp",payment->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",payment->sCardPhyID); 	// 物理卡号
	clt.SetIntFieldByName("lvol9",payment->nFundType); 			//交易类型
	//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo); 		// 
	//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
	//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
	clt.SetStringFieldByName("sphone3",payment->sRefNo);		//交易参考号
	clt.SetStringFieldByName("saddr",payment->sMac);			//MAC校验
	// 消费冲正
	if(!clt.SendRequest(846317,5000))
	{
		// TODO : 可能是超时
//		ks_setlasterr("与主机通讯超时",-1);
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		//		clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
//		clt.GetIntFieldByName("lvol0",&payment->nCardNo);			// 交易卡号
		clt.GetIntFieldByName("lvol8",&payment->nAftBalance);		//交易后余额
		//clt.GetIntFieldByName("lsafe_level2",);					//小钱包余额
		clt.GetStringFieldByName("sdate3",payment->sTransDate,9);	// 交易日期
		clt.GetStringFieldByName("stime3",payment->sTransTime,7);	// 交易时间
	}
	else
	{
		TRACE2_LOG(("返回的数据有问题"));
		return -1;
	}
	return 0;	
}
int  __stdcall  ks_setcardbal(ST_TRANSPACK *transpack)
{
	TRACE_FUNC("ks_setcardbal");
	int ret=0;
	transpack->nTransAmt=transpack->nAftBalance - transpack->nBefBalance;
	/*
	if(transpack->nTransAmt==0)
	{
		return 0;
	}
	*/
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		ks_beeperr();
		return -1;
	}
	if(strlen(transpack->sTransDate)!=8 || strlen(transpack->sTransTime) != 6)
	{
		ks_setlasterr("未设置交易日期和时间",-1);
		return -1;
	}
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	ret=ks_readpsamtermno(transpack->sTermno,0);
	if(ret)
	{
		ks_beeperr();
		return ret;
	}
	if(transpack->nTransAmt>0)
	{
		transpack->nTransType = 0;
		//ret=ks_addmoney(transpack);
		ret=c->AddMoney(transpack);
	}
	else 
	{
		transpack->nTransAmt = -transpack->nTransAmt;
		transpack->nTransType = 1;
		ret=c->PayMoney(transpack);
	}
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
		ks_beeperr();
		TRACE2_LOG(("交易失败RetryFlag[%d]GetProveFlag[%d]",transpack->cRetryFlag,transpack->cGetProveFlag));
		return ret;
	}
	TRACEMSG_LOG("写卡余额成功card["<<transpack->nCardNo<<"]money["<<transpack->nTransAmt
		<<"]dpscnt["<<transpack->nDpsCardCnt<<"]paycnt["<<transpack->nPayCardCnt<<"]["
		<<transpack->sTransDate<<transpack->sTransTime<<"]");
	return 0;
}
//联机交易
int __stdcall ks_getrefno(ST_TRANSPACK* payment)
{
	TRACE_FUNC("ks_getrefno");
	//1.获取交易参考号
	int nRet=0;
	char szRefno[17]={0};
	char szMac[9]={0};
	KS_YKT_Clt clt;
	payment->nPayType=10;
	payment->nTransType=1;
	//	clt.SetIntFieldByName("lwithdraw_flag",payment->termno);	//重点号
	clt.SetIntFieldByName("lcert_code",payment->nPayType);		//支付类型
	clt.SetIntFieldByName("lserial0",payment->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",payment->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol6",payment->nPayCardCnt); 		// 交易前次数
	clt.SetStringFieldByName("sserial0",payment->sTermno); 		// 终端号
	clt.SetIntFieldByName("lvol7",payment->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",payment->nTransAmt); 			// 金额
	clt.SetStringFieldByName("semp",payment->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",payment->sCardPhyID); 	// 物理卡号
	clt.SetIntFieldByName("lvol9",payment->nFundType); 			//交易类型
	//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo);// 
	//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
	//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
	clt.SetStringFieldByName("sstock_code",payment->sRandom); 			// 随机数

	// 支付交易
	if(!clt.SendRequest(850000,5000))
	{
		// TODO : 可能是超时
//		ks_setlasterr("与主机通讯超时",-1);
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

		//clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
		//clt.GetIntFieldByName("lvol0",&payment->nCardNo); // 交易卡号
		//clt.GetStringFieldByName("sdate0",payment->sTransDate,9); // 交易日期
		//clt.GetStringFieldByName("stime0",payment->sTransTime,7); // 交易时间
		clt.GetStringFieldByName("sphone3",szRefno,14);
		clt.GetStringFieldByName("saddr",szMac,8);
		/*
		clt.GetIntFieldByName("lvol8",&(paymen->nAftBalance)); // 出卡值
		*/
		//hex2dec(payment->sTransDate,8,sDate,nLen);
		//hex2dec(payment->sTransTime,6,sTime,nLen);
		//GET_PACK_STR(clt,"sstock_code2",sMac1);
		//TRACE2_LOG(("MAC1[%s]",sMac1));
	}
	else
	{
		// 返回的数据有问题
		return -1;
	}
	return 0;
}
//联机充值初始化
int  __stdcall ks_rechangeinit(ST_TRANSPACK *rechange)
{
	TRACE_FUNC("ks_rechangeinit");
	int nRet=0;	
	if(rechange->nErrCode)
	{
		if(rechange->nErrCode!=sizeof(ST_TRANSPACK))
		{
			ks_setlasterr("请求端发送包结构长度错误",-1);
			DEBUG_LOG(("请求端长度[%d]正确长度[%d]",rechange->nErrCode,sizeof(ST_TRANSPACK)));
			return -1;
		}
	}
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	//DEBUG_LOG(("physical no[%s]",payment->sCardPhyID));
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	nRet=ks_readpsamtermno(rechange->sTermno,1);
	if(nRet)
	{
		ks_setlasterr("读取PSAM卡错误",-1);
		return nRet;
	}
	nRet = c->InitForTrans(rechange,ks_cardtype_base::TRNS_TYPE_LOAD);
	if(nRet)
		return nRet;
	// 向后台发起充值请求
	KS_YKT_Clt clt;

	rechange->cRetryFlag=0;		
	rechange->nPayType=0;
	rechange->nTransType=0;
	clt.SetIntFieldByName("lbank_acc_type",1);					//模拟入账
	clt.SetIntFieldByName("lwithdraw_flag",rechange->nTermID);	//终端号
	clt.SetIntFieldByName("lcert_code",rechange->nPayCode);		//支付代码
	clt.SetIntFieldByName("lserial0",rechange->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",rechange->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol5",rechange->nDpsCardCnt); 		// 交易前充值次数
	clt.SetStringFieldByName("sserial0",rechange->sTermno); 	// PSAM卡终端编号
	clt.SetIntFieldByName("lvol7",rechange->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",rechange->nTransAmt); 			// 金额
	clt.SetStringFieldByName("semp",rechange->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",rechange->sCardPhyID); 	// 物理卡号
	clt.SetIntFieldByName("lvol9",rechange->nFundType); 			//交易类型
	clt.SetStringFieldByName("stx_pwd",rechange->sCardPwd); 		//卡密码
	//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo);// 
	//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
	//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
	clt.SetStringFieldByName("sstock_code",rechange->sRandom);	// 随机数

	// 支付交易
	if(!clt.SendRequest(850007,5000))
	{
		// TODO : 可能是超时
		//		ks_setlasterr("与主机通讯超时",-1);
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg);
		rechange->cRetryFlag=1;		
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(rechange->sErrMsg);
		// 充值失败
		ks_setlasterr(rechange->sErrMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,rechange->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		clt.GetStringFieldByName("sphone3",rechange->sRefNo,14);
		clt.GetStringFieldByName("saddr",rechange->sMac,8);
		clt.GetStringFieldByName("sdate3",rechange->sTransDate,9);	// 交易日期
		clt.GetStringFieldByName("stime3",rechange->sTransTime,7);	// 交易时间
		clt.GetIntFieldByName("lvol8",&(rechange->nAftBalance));		//出卡值
		TRACE2_LOG(("refno[%s]mac[%s]",rechange->sRefNo,rechange->sMac));
	}
	else
	{
		// 返回的数据有问题
		DEBUG_LOG(("返回的数据有问题"));
		return -1;
	}
	return 0;
}
//联机支付初始化
int  __stdcall ks_payinit(ST_TRANSPACK *payment)
{
	TRACE_FUNC("ks_payinit");
	int nRet=0;	
	if(payment->nErrCode)
	{
		if(payment->nErrCode!=sizeof(ST_TRANSPACK))
		{
			ks_setlasterr("请求端发送包结构长度错误",-1);
			TRACE2_LOG(("请求端长度[%d]正确长度[%d]",payment->nErrCode,sizeof(ST_TRANSPACK)));
			return -1;
		}
	}
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	//TRACE2_LOG(("physical no[%s]",payment->sCardPhyID));
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	if(payment->nBefBalance<payment->nTransAmt)
	{
		ks_setlasterr("卡余额不足",-1);
		return -1;
	}
	nRet=ks_readpsamtermno(payment->sTermno,1);
	if(nRet)
	{
		return nRet;
	}
	nRet = c->InitForTrans(payment,ks_cardtype_base::TRNS_TYPE_PURCHASE);
	if(nRet)
		return nRet;
	// 向后台发起支付请求
	KS_YKT_Clt clt;
	
	payment->cRetryFlag=0;		
	payment->nPayType=10;
	payment->nTransType=1;
	clt.SetIntFieldByName("lbank_acc_type",1);					//模拟入账
	clt.SetIntFieldByName("lwithdraw_flag",payment->nTermID);	//终端号
	clt.SetIntFieldByName("lvol4",payment->nTermID);			//终端号
	clt.SetIntFieldByName("lcert_code",payment->nPayCode);		//支付代码
	clt.SetIntFieldByName("lserial0",payment->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",payment->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol6",payment->nPayCardCnt); 		// 交易前次数
	clt.SetStringFieldByName("sserial0",payment->sTermno); 		// PSAM卡终端编号
	clt.SetIntFieldByName("lvol7",payment->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",payment->nTransAmt); 			// 金额
	clt.SetStringFieldByName("semp",payment->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",payment->sCardPhyID); 	// 物理卡号
	clt.SetIntFieldByName("lvol9",payment->nFundType); 			//交易类型
	clt.SetStringFieldByName("stx_pwd",payment->sCardPwd); 		//卡密码
//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo);// 
//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
	clt.SetStringFieldByName("sstock_code",payment->sRandom);	// 随机数

	// 支付交易
	if(!clt.SendRequest(850005,5000))
	{
		// TODO : 可能是超时
//		ks_setlasterr("与主机通讯超时",-1);
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg);
		payment->cRetryFlag=1;		
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		clt.GetStringFieldByName("sphone3",payment->sRefNo,14);
		clt.GetStringFieldByName("saddr",payment->sMac,8);
		clt.GetStringFieldByName("sdate3",payment->sTransDate,9);	// 交易日期
		clt.GetStringFieldByName("stime3",payment->sTransTime,7);	// 交易时间
		clt.GetIntFieldByName("lvol8",&(payment->nAftBalance));		//出卡值
		TRACE2_LOG(("refno[%s]mac[%s]",payment->sRefNo,payment->sMac));
	}
	else
	{
		// 返回的数据有问题
		TRACE2_LOG(("返回的数据有问题"));
		return -1;
	}
	return 0;
}
//联机充值
int  __stdcall ks_rechange(ST_TRANSPACK *rechange)
{
	TRACE_FUNC("ks_rechange");
	int nRet=0;	
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	rechange->cRetryFlag=0;		
	KS_YKT_Clt clt;
	//发起正式请求
//	clt.SetIntFieldByName("lwithdraw_flag",rechange->nTermID);	//终端号
	clt.SetIntFieldByName("lbank_acc_type",2);					//正式入账
	clt.SetStringFieldByName("sphone3",rechange->sRefNo);		//参考号
	clt.SetStringFieldByName("saddr",rechange->sMac);			//MAC
	clt.SetIntFieldByName("lserial0",rechange->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",rechange->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol5",rechange->nDpsCardCnt); 		// 交易前充值次数
	clt.SetStringFieldByName("sserial0",rechange->sTermno); 	// PSAM卡终端编号
	clt.SetIntFieldByName("lvol7",rechange->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",rechange->nTransAmt); 		// 金额
	clt.SetStringFieldByName("semp",rechange->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",rechange->sCardPhyID); // 物理卡号
	clt.SetIntFieldByName("lvol9",rechange->nFundType); 		//交易类型
	clt.SetStringFieldByName("stx_pwd",rechange->sCardPwd); 	//卡密码
	clt.SetStringFieldByName("sstock_code",rechange->sRandom);	// 随机数
	// 支付交易
	if(!clt.SendRequest(850007,5000))
	{
		// TODO : 可能是超时
		//	ks_setlasterr("与主机通讯超时",-1);
		//重发一次
		if(!clt.SendRequest(850007,5000))
		{
			// TODO : 可能是超时
			//		ks_setlasterr("与主机通讯失败,重新发送失败",-1);
			char szMsg[512]={0};
			char errmsg[512]={0};
			clt.GetReturnMsg(szMsg);
			sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
			ks_setlasterr(errmsg);
			return -1;
		}
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(rechange->sErrMsg);
		// 充值失败
		ks_setlasterr(rechange->sErrMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,rechange->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

		//		clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
		clt.GetIntFieldByName("lvol0",&rechange->nCardNo);				// 交易卡号
		clt.GetIntFieldByName("lvol8",&rechange->nAftBalance);			//交易后余额
		//clt.GetIntFieldByName("lsafe_level2",);						//小钱包余额
		clt.GetStringFieldByName("sdate3",rechange->sTransDate,9);		// 交易日期
		clt.GetStringFieldByName("stime3",rechange->sTransTime,7);		// 交易时间
	}
	else
	{
		DEBUG_LOG(("返回的数据有问题"));
		return -1;
	}
	return 0;	
}
//联机支付
int  __stdcall ks_pay(ST_TRANSPACK *payment)
{
	TRACE_FUNC("ks_pay");
	int nRet=0;	
	TRACE2_LOG(("支付码[%d]",payment->nPayCode));	
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	payment->cRetryFlag=0;		
	KS_YKT_Clt clt;
	//发起正式请求
	clt.SetIntFieldByName("lwithdraw_flag",payment->nTermID);	//终端号
	clt.SetIntFieldByName("lvol4",payment->nTermID);			//终端号
	clt.SetIntFieldByName("lcert_code",payment->nPayCode);		//支付代码
	clt.SetStringFieldByName("sphone3",payment->sRefNo);
	clt.SetStringFieldByName("saddr",payment->sMac);
	clt.SetIntFieldByName("lbank_acc_type",2);						//正式入账
	// 支付交易
	if(!clt.SendRequest(850005,5000))
	{
		// TODO : 可能是超时
	//	ks_setlasterr("与主机通讯超时",-1);
		//重发一次
		if(!clt.SendRequest(850005,5000))
		{
			// TODO : 可能是超时
	//		ks_setlasterr("与主机通讯失败,重新发送失败",-1);
			char szMsg[512]={0};
			char errmsg[512]={0};
			clt.GetReturnMsg(szMsg);
			sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
			ks_setlasterr(errmsg);
			return -1;
		}
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

//		clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
		clt.GetIntFieldByName("lvol0",&payment->nCardNo);				// 交易卡号
		clt.GetIntFieldByName("lvol8",&payment->nAftBalance);			//交易后余额
		//clt.GetIntFieldByName("lsafe_level2",);						//小钱包余额
		clt.GetStringFieldByName("sdate3",payment->sTransDate,9);		// 交易日期
		clt.GetStringFieldByName("stime3",payment->sTransTime,7);		// 交易时间
	}
	else
	{
		TRACE2_LOG(("返回的数据有问题"));
		return -1;
	}
	return 0;	
}
//当出现中途拔卡时，而用户没有重新放卡，需要调用本函数更新后台记录为写卡失败
int  __stdcall ks_dotransunprove(ST_TRANSPACK *transpack)
{
	TRACE_FUNC("ks_dotransunprove");
	int nRet=0;	
	
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	transpack->cRetryFlag=0;		
	KS_YKT_Clt clt;
	//发起正式请求
	clt.SetIntFieldByName("lwithdraw_flag",transpack->nTermID);	//终端号
	clt.SetStringFieldByName("semp",transpack->sOperCode);			//操作员号
	clt.SetIntFieldByName("lcert_code",transpack->nPayCode);	//支付代码
	clt.SetStringFieldByName("sphone3",transpack->sRefNo);
	clt.SetStringFieldByName("saddr",transpack->sMac);
	clt.SetIntFieldByName("lbank_acc_type",3);					//写卡失败
	// 支付交易
	if(!clt.SendRequest(850005,5000))
	{
		// TODO : 可能是超时
		//ks_setlasterr("与主机通讯超时",-1);
		//重发一次
		if(!clt.SendRequest(850005,5000))
		{
			// TODO : 可能是超时
			//ks_setlasterr("与主机通讯失败,重新发送失败",-1);
			char szMsg[512]={0};
			char errmsg[512]={0};
			clt.GetReturnMsg(szMsg);
			sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
			ks_setlasterr(errmsg);
			return -1;
		}
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(transpack->sErrMsg);
		// 充值失败
		ks_setlasterr(transpack->sErrMsg,nRet);
		TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,transpack->sErrMsg));
		return nRet;
	}
	TRACE_LOG("调用dotransunprove...");
	return 0;	
}
//取交易认证,1-充值 2消费 cardcnt 交易后消费或充值次数
int __stdcall ks_gettransprove(int transflag,short cardcnt)
{
	TRACE_FUNC("ks_gettransprove");
	int nRet=0;
	if(transflag<1||transflag>2)
	{
		ks_setlasterr("交易标志错误,提示:充值1消费2");
		return -1;
	}
	if(cardcnt<1)
	{
		ks_setlasterr("交易次数错误,提示:取交易成功后的次数");
		return -1;
	}
	char szCardPhyID[17]={0};
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	nRet=c->SelectADF();
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	nRet=c->GetTransProve(transflag,cardcnt,NULL,NULL);
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL),nRet);
		return nRet;
	}
	TRACE_LOG("获取TransProve...");
	return 0;
}
//读取交易明细文件（消费）
//1-4	交易日期(YYYYMMDD)
//5-7	交易时间(HHMMSS)
//8-8	交易类型
//9-14	终端机编号(PSAM卡中的终端号)
//15-18	终端交易序号(计算TAC用)
//19-22	交易前余额
//23-25	交易金额(包含搭伙费)
//26-28	搭伙费
//29-30	消费次数
//31-34	补写金额(加钱为正减钱为负)
//35-37	日累计消费金额
//38-39	商户号
//40	预留	(没有特征定义时为FF)

int ks_readpaydtl(int recordno,ST_PAYDTL *paydtl)
{
	TRACE_FUNC("ks_readpaydtl");
	unsigned char ucResp[256]={0};
	char  fieldvar[21]={0};
	unsigned char *buf= ucResp;
	memset(paydtl,0,sizeof(ST_PAYDTL));
	int nRet=0;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	nRet=c->SelectADF();
	if(nRet)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
		return nRet;
	}
	nRet=c->ReadRecordFile(0x01,recordno,40,ucResp);
	if(nRet)
	{
		//6A83 记录未找到
		if(nRet!=0x6A83)
			return nRet;
		else
			return 0;
	}
	paydtl->recordno=recordno;
	paydtl->exist=1;
	bcd2asc(buf,4,paydtl->transdate);//1-4	交易日期(YYYYMMDD)
	buf+=4;
	bcd2asc(buf,3,paydtl->transtime);//5-7	交易时间(HHMMSS)
	buf+=3;
	//paydtl->transtype=buf[0];			//8-8	交易类型
	buf+=1;
	char szBuf[13]={0};
	unsigned char swapbuf[6];
	swapbuf[5]=buf[0];
	swapbuf[4]=buf[1];
	swapbuf[3]=buf[2];
	swapbuf[2]=buf[3];
	swapbuf[1]=buf[4];
	swapbuf[0]=buf[5];
	bcd2asc(swapbuf,6,szBuf);				//9-14	终端机编号(PSAM卡中的终端号)
	//去掉前补0
	strcpy(paydtl->termno,szBuf);			
	buf+=6;
	paydtl->termsno = get_4byte_int(buf);//15-18	终端交易序号(计算TAC用)
	buf+=4;
	paydtl->cardbefbal =  get_4byte_int(buf);//19-22	交易前余额
	buf+=4;
	paydtl->transamt =  get_3byte_int(buf);//23-25	交易金额(包含搭伙费)
	buf+=3;
	paydtl->otherfee= get_3byte_int(buf);//26-28	搭伙费
	buf+=3;
	paydtl->paycnt = get_2byte_int(buf);//29-30	消费次数
	buf+=2;
	paydtl->extamt=get_4byte_int(buf);//31-34	补写金额(加钱为正减钱为负)
	buf+=4;
	buf+=3;								//35-37	日累计消费金额
	paydtl->shopid=get_2byte_int(buf); //38-39	商户号
	return 0;
}
int __stdcall ks_licence(const char *lisence,const char *pwd)
{
	TRACE_FUNC("ks_licence");
	int ret=ks_init();
	if(ret)
	{
		TRACE2_LOG(("ks_init err"));
		return ret;
	}
	if(strcmp("123456",pwd)==0)
		g_cardinfo.card_type = KS_FIXCARD;
	else if(strcmp("654321",pwd) == 0)
		g_cardinfo.card_type = KS_CPUCARD;
	else
		g_cardinfo.card_type = KS_MFCARD;
	//g_cardinfo.card_size = 16; // 1k 
	return 0;
}


//////////////////////////////////////////////////////////////////////////
// mifare key 相关函数
int ks_mf_login_card(int sectno)
{
	TRACE_FUNC("ks_mf_login_card");
	return 0;
}
int __stdcall CalcDF04Encrypt4Sam(const char *szCardNo,const char *szCmdbuf,char *szEncrypt)
{
	TRACE_FUNC("CalcDF04Encrypt4Sam");
	char szBuf[512];

	string sCmd,sMacData;
	vector<string> CmdVector;
	int ret;
	int nCmdLen;
	byte uCmd[256];
	byte uResp[256],nRespLen,rlen,rbuf[256];

	sCmd="ATR";
	CmdVector.push_back(sCmd);

	sCmd="00a4000002df04";
	CmdVector.push_back(sCmd);

	sCmd="801A270108";
	sCmd+=szCardNo;
	if(strlen(szCardNo)==8)
		sCmd+="80000000";
	CmdVector.push_back(sCmd);

	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdbuf);
	memcpy(szBuf,szCmdbuf,nCmdBufLen);
	nCmdBufLen/=2;
	if( nCmdBufLen%8 )
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);	

	sMacData=szBuf;

	int nMacDataLen=sMacData.size()/2;
	const char *pBuf=sMacData.c_str();
	int nBlockLen=0x30;
	if(nMacDataLen>nBlockLen)
	{
		sCmd="80FA0700";
		sCmd+=ltohex(nBlockLen);
		sCmd.append(pBuf,nBlockLen*2);
		CmdVector.push_back(sCmd);
		pBuf+=nBlockLen*2;
		nMacDataLen -= nBlockLen;
		if(nMacDataLen>nBlockLen)
		{
			sCmd="80FA0300";
			sCmd+=ltohex(nBlockLen);
			sCmd.append(pBuf,nBlockLen*2);
			CmdVector.push_back(sCmd);
			nMacDataLen -= nBlockLen;
			pBuf+=nBlockLen*2;
		}
		sCmd="80FA0100";
		sCmd+=ltohex(nMacDataLen);
		sCmd.append(pBuf,nMacDataLen*2);
		CmdVector.push_back(sCmd);
	}
	else
	{
		sCmd="80FA0000";
		sCmd+=ltohex(nMacDataLen);
		sCmd+=sMacData;
		CmdVector.push_back(sCmd);
	}
	sCmd="00C0000008";
	CmdVector.push_back(sCmd);

	for(int i=0;i<CmdVector.size();i++)
	{
		sCmd=CmdVector[i];
		if("ATR"==sCmd)
		{
			ret=ks_cpureset4sam(&rlen,rbuf);
			if(ret)
			{
				return ret;
			}
			continue;
		}
		string_replace(sCmd," ","");
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
		ret=ks_cpuapdu4sam(uCmd,nCmdLen,uResp,nRespLen);
		if(ret)
		{
			//sMsg=sCmd+":"+ltohex(ret);
			//MessageBox(NULL,sMsg.c_str(),"",MB_OK);
			return ret;
		}
	}
	dec2hex(uResp,8,szEncrypt);
	return 0;
}
int __stdcall ks_external_auth(const char *phyno)
{
	TRACE_FUNC("ks_external_auth");
	string sCmd;
	unsigned char ucCmd[512],ucRes[512];
	char random_num[64] = "";
	char encrypt_random[24] = "";
	int nCmdLen,nRet;
	unsigned char nResLen;
	sCmd = "00A4000002DF04";
	hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);
	nRet=ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
	if(nRet)
	{
		TRACE2_LOG(("选目录失败"));
		return -1;
	}
	sCmd = "0084000004";
	hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);
	nRet=ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
	if(nRet)
	{
		TRACE2_LOG(("去随机数失败"));
		return -1;
	}
	memset(random_num,'0',sizeof(random_num)-1);
	dec2hex(ucRes,nResLen,random_num);
	memset(random_num+8,'0',8);
	random_num[16]=0;
	nRet = CalcDF04Encrypt4Sam(phyno,random_num,encrypt_random);
	if(nRet)
	{
		TRACE2_LOG(("Calc DF04 Encrypt Err"));
		return -1;
	}
	sCmd = "0082000108";
	sCmd += encrypt_random;
	hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);
	nRet = ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
	if(nRet)
	{
		TRACE2_LOG(("External Auth Err[%X]",nRet));
		return -1;
	}
	return 0;
}


// 初始化后付费
int __stdcall ks_init_postpaid(ST_TRANSPACK *payment,int must_online)
{
	TRACE_FUNC("ks_init_postpaid");
	int nRet;
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}

	if(payment->nBefBalance<payment->nTransAmt)
	{
		ks_setlasterr("卡余额不足",-1);
		return -1;
	}
	nRet=ks_readpsamtermno(payment->sTermno,1);
	if(nRet)
	{
		return nRet;
	}
	nRet = c->InitForTrans(payment,ks_cardtype_base::TRNS_TYPE_PURCHASE);
	if(nRet)
	{
		TRACE2_LOG(("Init POSTPAID Err[%X]",nRet));
		return -1;
	}

	// 向后台发起支付请求
	KS_YKT_Clt clt;
	payment->nPayType=10;
	payment->nTransType=1;
	clt.SetIntFieldByName("lbank_acc_type",1);					//模拟入账
	clt.SetIntFieldByName("lwithdraw_flag",payment->nTermID);	//终端号
	clt.SetIntFieldByName("lvol4",payment->nTermID);			//终端号
	clt.SetIntFieldByName("lcert_code",payment->nPayCode);		//支付代码
	clt.SetIntFieldByName("lserial0",payment->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",payment->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol6",payment->nPayCardCnt); 		// 交易前次数
	clt.SetStringFieldByName("sserial0",payment->sTermno); 		// 终端号
	clt.SetIntFieldByName("lvol7",payment->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",payment->nTransAmt); 			// 金额
	clt.SetStringFieldByName("semp",payment->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",payment->sCardPhyID); 	// 物理卡号
	clt.SetIntFieldByName("lvol9",payment->nFundType); 			//交易类型
	clt.SetStringFieldByName("stx_pwd",payment->sCardPwd); 		//卡密码
//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo);// 
//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
	clt.SetStringFieldByName("sstock_code",payment->sRandom);	// 随机数

	// 支付交易
	if(!clt.SendRequest(850005,5000))
	{
		// TODO : 可能是超时
//		ks_setlasterr("与主机通讯超时",-1);
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		TRACE2_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		clt.GetStringFieldByName("sphone3",payment->sRefNo,14);
		clt.GetStringFieldByName("saddr",payment->sMac,8);
		clt.GetStringFieldByName("sdate3",payment->sTransDate,8);
		clt.GetStringFieldByName("stime3",payment->sTransTime,6);
		TRACE2_LOG(("refno[%s]mac[%s]",payment->sRefNo,payment->sMac));
		nRet =  c->InitForTrans(payment,ks_cardtype_base::TRNS_TYPE_POSTPAID);
		if(nRet)
		{
			TRACE2_LOG(("Init POSTPAID Err[%X]",nRet));
			return -1;
		}
	}
	else
	{
		// 返回的数据有问题
		TRACE2_LOG(("返回的数据有问题"));
		return -1;
	}
	return 0;
}
// 后付费扣款
int __stdcall ks_postpaid(ST_TRANSPACK *transpack,int must_online)
{
	TRACE_FUNC("ks_postpaid");
	return -1;
}

int __stdcall ks_cardtype()
{
	TRACE_FUNC("ks_cardtype");
	return CardTypeManager::instance()->getCardTypeCode();
}

//////////////////////////////////////////////////////////////////////////
// 小钱包水控相关函数
int __stdcall ks_water_publishcard(int watertype,ks_water_pack_t *pack)
{
	TRACE_FUNC("ks_water_publishcard");
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	int ret = c->water_publishcard(watertype,pack);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
	}
	return ret;
}
int __stdcall ks_water_recyclecard(int watertype)
{
	TRACE_FUNC("ks_water_recyclecard");
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	int ret = c->water_recyclecard(watertype);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
	}
	return ret;
}
int __stdcall ks_water_readmoney(int watertype,ks_water_pack_t *pack)
{
	TRACE_FUNC("ks_water_readmoney");
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	int ret = c->water_readmoney(watertype,pack);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
	}
	return ret;
}
int __stdcall ks_water_writemoney(int watertype,ks_water_pack_t *pack)
{
	TRACE_FUNC("ks_water_writemoney");
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	int ret = c->water_writemoney(watertype,pack);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
	}
	return ret;
}	


int __stdcall ks_water_publishparamcard(int watertype,ks_water_param_t *param)
{
	TRACE_FUNC("ks_water_publishparamcard");
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	int ret = c->water_publishparamcard(watertype,param);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
	}
	return ret;
}
int __stdcall ks_water_recycleparamcard(int watertype)
{
	TRACE_FUNC("ks_water_recycleparamcard");
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	int ret = c->water_recycleparamcard(watertype);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
	}
	return ret;
}
int __stdcall ks_water_readparamcard(int watertype,ks_water_param_t *param)
{
	TRACE_FUNC("ks_water_readparamcard");
	ks_cardtype_base *c = CardTypeManager::instance()->getLastCardType();
	int ret = c->water_read_paramcard(watertype,param);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
	}
	return ret;
}
int __stdcall ks_water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO *fee_rate)
{
	TRACE_FUNC("ks_water_publish_legacycard");
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	int ret = c->water_publish_legacycard(watertype,fee_rate);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
	}
	return ret;
}
int __stdcall ks_water_read_legacycard(int watertype,FEE_RATE_CARD_INFO *fee_rate)
{
	TRACE_FUNC("ks_water_read_legacycard");
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	int ret = c->water_read_legacycard(watertype,fee_rate);
	if(ret)
	{
		ks_setlasterr(c->GetLastErrMsg(NULL));
	}
	return ret;
}
int __stdcall ks_water_dump_legacycarddata(int watertype)
{
	TRACE_FUNC("ks_water_dump_legacycarddata");
	ks_cardtype_base *c;
	GET_CARDTYPE(c);
	c->DumpSectData(watertype);
	return 0;
}
int __stdcall ks_getcardstatus(int cardno,char *statuscode,char *statusinfo)
{
	TRACE_FUNC("ks_getcardstatus");
	int nRet=0;
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	// 向后台发起充值请求
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lvol0",cardno); // 交易卡号
	if(!clt.SendRequest(200000,5000))
	{
		// TODO : 可能是超时
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg,clt.GetReturnCode());
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		// 充值失败
		char szMsg[512];
		clt.GetReturnMsg(szMsg);
		ks_setlasterr(szMsg,nRet);
		return nRet;
	}
	clt.GetNextPackage();
	char szCardStatus[5]={0};
	char szStatusInfo[256]={0};
	GET_PACK_STR(clt,"sstatus0",szCardStatus);
	GET_PACK_STR(clt,"vsmess",szStatusInfo);
	*statuscode=szCardStatus[0];
	strcpy(statusinfo,szStatusInfo);
	return 0;
}