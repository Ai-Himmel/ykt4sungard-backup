/***************************************************************************************************/
/* 功能........实现对汇多硬件的操作                                                                   
/* 函数........打开串口, 加载密钥, 读取数据，写入数据(第几个扇区, 第几块), 蜂鸣, 关闭串口, 报错信息                                                            */
/* 作者........李翔
/* 日期........2006/13/07
/***************************************************************************************************/
#include "Stdafx.h"
#include "stdlib.h"
#include "Comm.h"

#pragma  pack(1)
typedef struct _LOOPPURSEINFO
{
	DWORD RemainMoney;// 电子钱包余额
	WORD DealTimes;// 卡片交易流水号
	BYTE DealYear; //交易日期
	BYTE DealMonth; 
	BYTE DealDay;
	BYTE DealHour;
	BYTE DealMin;
	BYTE DealTimes_CurTime; // 累计交易次数(当前时间段内)
	BYTE DealTimes_CurDay;// 累计交易次数(当日内)
} LOOPPURSEINFO,*LPLOOPPURSEINFO;

typedef struct 
{
	int bala;
	int daybala;
	int total_cnt;
	int day_cnt;
	int time_cnt;
	int date;	//yyyymmdd
	int time;	//hhmmss
}MONEY_PACK_INFO;

typedef struct
{
	char cardtype;
	int termid;
	int remain;
	BYTE oldSerialNo[4];
}WATER_PACK_INFO;

#define WATER_AUTH_CARD 1
#define WATER_COMMON_CARD 2
#define WATER_CLEAR_CARD 3
#define WATER_NEW_CARD 4
#define WATER_FIXED_CARD 5

#pragma  pack()

static unsigned char s_water_common_card[2] = {0xF9,0x9E};
static unsigned char s_water_clear_card[2] = {0xF9,0x9C};
static unsigned char s_water_new_card[2] = {0xF9,0x9D};
static unsigned char s_water_auth_card[2] = {0xF9,0x9F};

static struct version_info 
{
	char ks_ver_no[20];
	char ks_ver_dcb[80];
}version_info = {"v1.0.0.0", "银达RC500读卡器动态库"};

//授权标志
int nAutoFlag = 0;
unsigned char UCWORKINGKEY[256]="";
char g_ErrMsg[1024]="";
int g_ErrCode=-1;

// 明华设备需要的底层硬件
unsigned char ucWorkKey[256];
unsigned char g_sInitWorkKey[256]="AE2C843443345394138464444";
unsigned char g_ucWORKINGKEY[256]="";
int icdev=NULL;
//HANDLE g_hCom=NULL;
#define DEF_DLLFUNC(r,n,p) \
	typedef r (__stdcall* lp_##n) p

#define DCLR_DLLFUNC(n) \
	static lp_##n n = NULL

#define LOAD_DLLFUNC(h,n)  do{ \
	n = (lp_##n)GetProcAddress(h,#n); if(!n) return -1; }while(0)

DEF_DLLFUNC(unsigned char, RC500_232_init,(int nport, int nbaud));
DEF_DLLFUNC(unsigned char, RC500_232_request,(unsigned char mode, unsigned short &tagtype));
DEF_DLLFUNC(unsigned char, RC500_232_anticoll,(unsigned char bcnt,unsigned long &snr));
DEF_DLLFUNC(unsigned char, RC500_232_select,(unsigned long snr,unsigned char &size));
DEF_DLLFUNC(unsigned char, RC500_232_authentication,(unsigned char mode,unsigned char secnr));
DEF_DLLFUNC(unsigned char, RC500_232_authkey,(unsigned char mode,unsigned char secnr,unsigned char *key));
DEF_DLLFUNC(unsigned char, RC500_232_halt,(void));
DEF_DLLFUNC(unsigned char, RC500_232_read,(unsigned char addr,unsigned char *data));
DEF_DLLFUNC(unsigned char, RC500_232_write,(unsigned char addr,unsigned char *data));
DEF_DLLFUNC(unsigned char, RC500_232_load_key,(unsigned char mode,unsigned char secnr,unsigned char *key));
DEF_DLLFUNC(unsigned char, RC500_232_reset,(unsigned char msec));
DEF_DLLFUNC(unsigned char, RC500_232_close,(void));
DEF_DLLFUNC(unsigned char, RC500_232_config,(void));
DEF_DLLFUNC(void, RC500_232_exit,(void));
DEF_DLLFUNC(unsigned char, RC500_232_alarm,(unsigned char contrl,unsigned char opentm,unsigned char closetm,unsigned char repcnt));


HINSTANCE					hDLL = NULL;

DCLR_DLLFUNC(RC500_232_init);
DCLR_DLLFUNC(RC500_232_request);
DCLR_DLLFUNC(RC500_232_anticoll);
DCLR_DLLFUNC(RC500_232_select);
DCLR_DLLFUNC(RC500_232_authentication);
DCLR_DLLFUNC(RC500_232_authkey);
DCLR_DLLFUNC(RC500_232_halt);
DCLR_DLLFUNC(RC500_232_read);
DCLR_DLLFUNC(RC500_232_write);
DCLR_DLLFUNC(RC500_232_load_key);
DCLR_DLLFUNC(RC500_232_reset);
DCLR_DLLFUNC(RC500_232_close);
DCLR_DLLFUNC(RC500_232_config);
DCLR_DLLFUNC(RC500_232_alarm);
DCLR_DLLFUNC(RC500_232_exit);


//////////////////////////////////////////////////////////////////////////
void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
	int k=0;
	for(i=0;i<dec_len;i++)
	{
		k=sDec[i];
		sprintf(&sHex[2*i],"%02X",k);
	}
}
void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}
int dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		lch=sDecStr[2*i]-'0';
		hch=sDecStr[2*i+1]-'0';
		lch=lch<<4;
		hch=hch&0x0F;
		lch=lch&0xF0;
		sBcdStr[i]=hch|lch;
	}
	return 0;
}
int  bcd2dec(unsigned char *sBcdStr,int bcd_len,char *sDecStr)
{	
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		hch=(sBcdStr[i]&0x0F);
		lch=(sBcdStr[i]&0xF0);
		lch=lch>>4;
		sDecStr[2*i]=lch+'0';
		sDecStr[2*i+1]=hch+'0';
	}
	return 0;
}

//设置错误信息
void _stdcall SetLastErrMsg(int err_code,char* format, ...)
{
	va_list arglist; 
	char buffer[1024]=""; 
	va_start (arglist,format); 
	vsprintf(buffer, format, arglist); 
	va_end (arglist); 
	strcpy(g_ErrMsg,buffer);
	g_ErrCode=err_code;
}
//取错误信息
void _stdcall SMT_GetLastErr(int* pErrCode,char *Msg)
{
	*pErrCode=g_ErrCode;
	strcpy(Msg,g_ErrMsg);
}
//////////////////////////////////////////////////////////////////////////
// 
static unsigned char add_2(unsigned char add1, unsigned char add2)
{
	unsigned char ad1, ad2, sum;
	ad1 = add1;
	ad2 = add2;
	sum = (ad1 + ad2) % 0x100;
	return sum;
}

static void dess_ming(unsigned char key[4],unsigned char Source[4],unsigned char dest[4])
{
	unsigned char x0, x1, x2, x3, y0, y1, y2, y3, m, n, add1, add2;
	x0 = key[0];
	x1 = key[1];
	x2 = key[2];
	x3 = key[3];
	y0 = Source[0];
	y1 = Source[1];
	y2 = Source[2];
	y3 = Source[3];
	m = x0 ^ x1;
	add1 = m;
	add2 = y2;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x1;
	n = add_2(add1, add2);
	add1 = n;
	add2 = y3;
	n = add_2(add1, add2);
	m = m ^ y0;
	n = n ^ y1;
	y0 = m;
	y1 = n;
	add1 = m;
	add2 = x1 ^ x2;
	m = add_2(add1, add2);
	add1 = x1;
	add2 = x2;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y2;
	n = n ^ y3;
	y2 = m;
	y3 = n;
	add1 = y1;
	add2 = x2 ^ x3;
	m = add_2(add1, add2);
	add1 = x2;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = y0;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = m;
	add2 = x0 ^ x3;
	m = add_2(add1, add2); 
	add1 = x0;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	add1 = y3;
	add2 = x0 ^ x3;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = y2;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	add1 = m;
	add2 = x2 ^ x3;
	m = add_2(add1, add2);
	add1 = x2;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = y1;
	add2 = x1 ^ x2;
	m = add_2(add1, add2);
	add1 = x1;
	add2 = x2;
	add1 = add_2(add1, add2);
	add2 = y0;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = m;
	add2 = x0 ^ x1;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x1;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	dest[0] = y0;
	dest[1]= y1;
	dest[2] = y2;
	dest[3] = y3;
}

static int gen_extra_keyA(unsigned char* key,unsigned char* text,unsigned char* keyA)
{
	unsigned int i;
	unsigned char sPlain[9] = "";
	unsigned char workKey[4] = "";
	memcpy(workKey,key,sizeof(workKey));
	for(i = 0;i < 4;++i)
	{
		sPlain[i] = text[i];
		sPlain[i+4] = ~text[i];
	}
	dess_ming(workKey,sPlain,keyA);
	dess_ming(workKey,sPlain+4,keyA+4);
	return 0;
}
static int do_load_function()
{
	LOAD_DLLFUNC(hDLL,RC500_232_init);
	LOAD_DLLFUNC(hDLL,RC500_232_request);
	LOAD_DLLFUNC(hDLL,RC500_232_anticoll);
	LOAD_DLLFUNC(hDLL,RC500_232_select);
	LOAD_DLLFUNC(hDLL,RC500_232_authentication);
	LOAD_DLLFUNC(hDLL,RC500_232_authkey);
	LOAD_DLLFUNC(hDLL,RC500_232_halt);
	LOAD_DLLFUNC(hDLL,RC500_232_read);
	LOAD_DLLFUNC(hDLL,RC500_232_write);
	LOAD_DLLFUNC(hDLL,RC500_232_load_key);
	LOAD_DLLFUNC(hDLL,RC500_232_reset);
	LOAD_DLLFUNC(hDLL,RC500_232_close);
	LOAD_DLLFUNC(hDLL,RC500_232_config);
	LOAD_DLLFUNC(hDLL,RC500_232_alarm);
	LOAD_DLLFUNC(hDLL,RC500_232_exit);
	return 0;
}

//*************获取错误代码函数*********************
int _stdcall GetMFLastErr()
{
	return ErrorCode;
}

int _stdcall MF_ReadSeriesNo(unsigned char *serial)
{
	unsigned char ret = 0;                                         // 设备标识符
	unsigned short cardmode = 2;                           // 卡的模式  
	unsigned char size=0;                                // ??大小
	unsigned long cardid = 0;                            // 卡的id号
	char bufCardId[10] = "";

	// 重新放卡
	ret = RC500_232_request(1,cardmode);               // 1表示ALL模式, 一次可以对多张卡的操作, 成功返回为0
	if(ret != 0)
	{
		return -2;
	}

	ret= RC500_232_anticoll(0,cardid);                 // 获取卡的序列号(第三个参数cardid), request指令之后应立即调用anticoll，除非卡的序列号已知, 成功返回为0
	if(ret)
	{
		return ret;
	}
	memcpy(serial, (unsigned char*)&cardid, sizeof cardid);
	return 0;                                           // 成功则返回0
}

//1、检查用户卡是否在感应区
int _stdcall SMT_RequestCardExist(unsigned char ucSerialNo[4],unsigned char ucType[1])
{
	unsigned char Buf[20] = "";
	int ret;
	unsigned char size = 0;
	unsigned long serialNo = 0;
	ret = MF_ReadSeriesNo(Buf);
	if(ret != 0)
	{
		SetLastErrMsg(ret, "读取卡序列号失败");
		return ret;
	}
	ret= RC500_232_anticoll(0, serialNo);
	if(ret != 0)
	{
		SetLastErrMsg(ret, "读卡器感应区没有卡");
		return -2;
	}
	ret = RC500_232_select(serialNo, size);
	if(ret)
	{
		SetLastErrMsg(ret, "选卡失败!");
		return ret;
	}
	if (ret == 0)							   // 正常返回为0 
	{
		memcpy(ucSerialNo,Buf,4);
		memcpy(ucType, &size, 1);
		return 0;
	}
	return -1;
}


int SMT_LoadDll()
{
	if (hDLL)
	{
		return 0;
	}
	hDLL = LoadLibrary("RC500_232.dll");
	if (!hDLL)
	{
		::AfxMessageBox("动态库RC500_232.dll加载失败!");
		return -1;
	}
	if(do_load_function())
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
		return -2;
	}
	return 0;
}

int _stdcall SMT_ControlBuzzer()
{
	int ret = 0;
	if (!icdev)
	{
		SetLastErrMsg(-1, "串口%d未打开", icdev);
		return -1;
	}
	ret = RC500_232_alarm(0,10,10,1);
	return 0;
}

int _stdcall SMT_Login_With_UserKey(int sector, unsigned char *Buffer, int PaDSelect)
{
	// 0代表keyA, 1代表keyB
	int  ret;
	unsigned char _mode = (PaDSelect == 1)? 4 : 0;
	unsigned char _sector = sector;
	unsigned long ucSerialNo = 0;
	unsigned char size = 0;
	unsigned int tagtype = 2;

	/*
	ret = dc_request(icdev, 1, &tagtype);	
	if(ret)
	{
		SetLastErrMsg(ret, "读卡器感应区没有卡");
		return -2;
	}
	ret= dc_anticoll(icdev,0,&ucSerialNo);
	if(ret != 0)
	{
		SetLastErrMsg(ret, "读卡器感应区没有卡");
		return -2;
	}
	ret = dc_select(icdev, ucSerialNo, &size);
	if(ret)
	{
		SetLastErrMsg(ret, "选卡失败!");
		return ret;
	}		
	ret = dc_load_key(icdev, _mode, _sector, Buffer);           // 重新修改的
	if (ret != 0)
	{
		SetLastErrMsg(ret, "装载密码失败!");
		return -3;
	}
	ret = dc_authentication(icdev, _mode, _sector); 
	if (ret != 0)
	{
		SetLastErrMsg(ret, "验证密钥失败!");
		return -4; 
	}
	*/
	ret = RC500_232_authkey( _mode, _sector,Buffer); 
	if (ret != 0)
	{
		SetLastErrMsg(ret, "验证密钥失败!");
		return -4; 
	}
	return 0;
}

int _stdcall SMT_ConnectMF280(int port, int baud)
{
	int ret=0;
	ret = SMT_LoadDll();
	if(ret)
		return ret;
	ret = RC500_232_init(port, baud);
	if(ret)
	{
		SetLastErrMsg(-1, "打开串口%d失败", port);
		return int(port);
	}
	SMT_ControlBuzzer();
	icdev = 1;
	return 0;
}

int _stdcall SMT_CloseMF280()
{
	int ret=0;
	//if(icdev)
	RC500_232_exit();
	/*
	if (ret)
	{
		SetLastErrMsg(ret, "关闭串口失败");
		return -2;
	}
	*/
	icdev = 0;
	return 0;
}

int _stdcall SMT_WriteBlock(int Sector,int BlockNo,unsigned char *BlockBuf)
{
	int ret;
	unsigned char ucBlock=0;
	unsigned char ucBlockBuf[20]="";
	unsigned long ulSerial=0;

	memcpy(ucBlockBuf,BlockBuf,16);

	if (Sector <= 31)
		ucBlock=Sector*4+BlockNo;

	if (Sector > 31)
		ucBlock = 32 * 4 + (Sector - 32) * 16 + BlockNo;	

	ret=RC500_232_write(ucBlock,ucBlockBuf);
	if(ret)
	{
		return -6;
	}
	return 0;
}

int _stdcall SMT_ReadBlock(int Sector,int BlockNo,unsigned char *BlockBuf)
{
	int ret=-1;
	unsigned char ucBlock=0;
	unsigned char ucBlockBuf[20];
	unsigned long ulSerial=0;

	memset(ucBlockBuf,0,sizeof(ucBlockBuf));

	if (Sector <= 31)
		ucBlock=Sector*4+BlockNo;

	if (Sector > 31)
		ucBlock = 32 * 4 + (Sector - 32) * 16 + BlockNo;

	ret = RC500_232_read(ucBlock, ucBlockBuf);
	if(ret)
	{
		SetLastErrMsg(ret, "读卡内数据错!");
		return -5;
	}
	memcpy(BlockBuf,ucBlockBuf,16);
	return 0;
}

int _stdcall SMT_SleepCard()
{
	int ret;
	ret = RC500_232_halt();
	if (ret)
	{
		SetLastErrMsg(ret, "休眠卡失败!");
		return -7;
	}
	return 0;
}

int _stdcall SMT_GetDllVersion(char *ks_ver_no, char *ks_ver_dcb)
{
	if (strlen(strcpy(ks_ver_no, version_info.ks_ver_no)) == 0)
		return -1;

	if (strlen(strcpy(ks_ver_dcb, version_info.ks_ver_dcb)) == 0)
		return -1;

	return 0;
}
