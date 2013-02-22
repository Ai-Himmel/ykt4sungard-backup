/***************************************************************************************************/
/* 功能........实现对国光圈存机硬件的操作                                                                   
/* 函数........打开串口, 加载密钥, 读取数据，写入数据(第几个扇区, 第几块), 蜂鸣, 关闭串口, 报错信息                                                            */
/* 作者........李翔
/* 日期........2007/12/09
/***************************************************************************************************/

#include "stdafx.h"
#include "stdlib.h"

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

#pragma  pack()

static struct version_info 
{
	char ks_ver_no[20];
	char ks_ver_dcb[80];
}version_info = {"v1.0.0.0", "国光读卡器动态库"};

//授权标志
int nAutoFlag = 0;
char g_err_msg[1024] = "";
int g_err_code = -1;
int g_mode = 0;
static unsigned char g_login_key[7] = "";

// 国光设备需要的底层硬件
unsigned char g_sInitWorkKey[256]="AE2C843443345394138464444";
unsigned char g_ucWORKINGKEY[256]="";

int icdev = NULL;
typedef int (CALLBACK *LPfunc_OpenComm)(int port);
typedef int (CALLBACK *LPfunc_AntiColl)(unsigned char *cardno);
typedef void (CALLBACK *LPfunc_CloseComm)();
typedef int (CALLBACK *LPfunc_ActiveCard)(int ActiveMode, unsigned char *CardId);
typedef int (CALLBACK *LPfunc_CloseCard)();
typedef int (CALLBACK *LPfunc_Rc_LoadPwd)(int PwdMode, int SectorID, unsigned char *Pwd);
typedef int (CALLBACK *LPfunc_Rc_ConfirmPwd)(int BlockID, int PwdMode, unsigned char *CardId);
typedef int (CALLBACK *LPfunc_Rc_ReadData)(int BlockID, unsigned char *Data);
typedef int (CALLBACK *LPfunc_Rc_WriteData)(int BlockID, unsigned char *Data);

//////////////////////////////////////////////////////////////////////////
HINSTANCE hDLL = NULL;
LPfunc_OpenComm			func_OpenComm = NULL;
LPfunc_AntiColl			func_AntiColl = NULL;
LPfunc_CloseComm		func_CloseComm = NULL;
LPfunc_ActiveCard		func_ActiveCard = NULL;
LPfunc_CloseCard		func_CloseCard = NULL;
LPfunc_Rc_LoadPwd		func_Rc_LoadPwd = NULL;
LPfunc_Rc_ConfirmPwd	func_Rc_ConfirmPwd = NULL;
LPfunc_Rc_ReadData		func_Rc_ReadData = NULL;
LPfunc_Rc_WriteData		func_Rc_WriteData = NULL;
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
	 va_start (arglist, format); 
	 vsprintf(buffer, format, arglist); 
	 va_end (arglist); 
	 strcpy(g_err_msg, buffer);
	 g_err_code = err_code;
}
//取错误信息
void _stdcall SMT_GetLastErr(int* pErrCode,char *Msg)
{
	*pErrCode = g_err_code;
	strcpy(Msg, g_err_msg);
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
//*************获取错误代码函数*********************
int _stdcall GetMFLastErr()
{
	return g_err_code;
}

int _stdcall MF_ReadSeriesNo(unsigned char *serial)
{
	int ret = 0;                                         // 设备标识	
//	hex2dec((char*)buf_temp, serial, 4);

	if ((ret = func_AntiColl(serial)) < 0)				 // 直接反序了
	{
		return -2;
	}

	/*
	for (int i = 0; i < 2; i++)
	{
		unsigned char t = serial[i];
		serial[i] = serial[3 - i];
		serial[3 - i] = t;
	}
	*/                                  
	return 0;                                           // 成功则返回0
}

//1、检查用户卡是否在感应区
int _stdcall SMT_RequestCardExist(unsigned char ucSerialNo[4], unsigned char ucType[1])
{
	int ret = 0;
	unsigned char Buf[20] = "";
	ret = func_AntiColl(Buf);
	if (ret < 0)
	{
		return -2;
	}
	
	memcpy(ucSerialNo, Buf, 4);
	memcpy(ucType, Buf + 4, 1);

	return 0;
}

int SMT_LoadDll()
{
	if (hDLL)
	{
		return 0;
	}
	hDLL = LoadLibrary("IC_Card.dll");
	if (!hDLL)
	{
		::AfxMessageBox("动态库IC_Card.dll加载失败!");
		return -1;
	}
	func_OpenComm		= (LPfunc_OpenComm)GetProcAddress(hDLL, "func_OpenComm");
	func_CloseComm		= (LPfunc_CloseComm)GetProcAddress(hDLL, "func_CloseComm");
	func_AntiColl		= (LPfunc_AntiColl)GetProcAddress(hDLL, "func_AntiColl");
	func_ActiveCard		= (LPfunc_ActiveCard)GetProcAddress(hDLL, "func_ActiveCard");
	func_Rc_LoadPwd		= (LPfunc_Rc_LoadPwd)GetProcAddress(hDLL, "func_Rc_LoadPwd");
	func_Rc_ConfirmPwd	= (LPfunc_Rc_ConfirmPwd)GetProcAddress(hDLL, "func_Rc_ConfirmPwd");
	func_Rc_ReadData	= (LPfunc_Rc_ReadData)GetProcAddress(hDLL, "func_Rc_ReadData");
	func_Rc_WriteData	= (LPfunc_Rc_WriteData)GetProcAddress(hDLL, "func_Rc_WriteData");
	func_CloseCard		= (LPfunc_CloseCard)GetProcAddress(hDLL, "func_CloseCard");
	if (
		(!func_OpenComm)			||
		(!func_CloseComm)			||
		(!func_AntiColl)			||
		(!func_ActiveCard)			||
		(!func_Rc_LoadPwd)			||
		(!func_Rc_ConfirmPwd)		||
		(!func_Rc_ReadData)			||
		(!func_Rc_WriteData)		||
		(!func_CloseCard)
		)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
		return -2;
	}
	return 0;
}


int _stdcall SMT_ControlBuzzer()
{
	return 0;
}

static int SMT_LoadLoginKey(unsigned char sector,
							unsigned char block)
{
	int ret = 0;
	unsigned char serial_no[20] = "";
	/*
	char serial_no1[20] = "";

	::MessageBox(NULL, "程序挂起", "挂起", NULL);
	*/
	if ((ret = func_CloseCard()) < 0) { return -10; }
	
	/*
	char msg[13] = "";

	itoa(g_mode, msg, 10);
	::MessageBox(NULL, msg, "模式", NULL);
	
	itoa(sector, msg, 10);
	::MessageBox(NULL, msg, "扇区", NULL);

	itoa(block, msg, 10);
	::MessageBox(NULL, msg, "块号", NULL);
	*/

	if ((ret = func_ActiveCard(0, serial_no)) < 0) { return -11; }		// 0 表示ALL, 1表示IDEL模式
	
	/*
	dec2hex(serial_no, 4, serial_no1);
	MessageBox(NULL, serial_no1, "物理卡号", NULL);

	dec2hex(g_login_key, 6, serial_no1);
	MessageBox(NULL, serial_no1, "登录密钥", NULL);
	*/

	if ((ret = func_Rc_LoadPwd(g_mode, sector, g_login_key)) < 0) { return -12; }

	if ((ret = func_Rc_ConfirmPwd(block, g_mode, serial_no)) < 0) { return -13; }

	return 0;	
}

int _stdcall SMT_Login_With_UserKey(int sector, unsigned char *Buffer, int PaDSelect)
{
	//char msg[13] = "";
	
	/*
	itoa(PaDSelect, msg, 10);
	::MessageBox(NULL, msg, "模式", NULL);
	*/

	/*
	dec2hex(Buffer, 6, msg);
	::MessageBox(NULL, msg, "密钥", NULL);
	*/

	memcpy(g_login_key, Buffer, sizeof(g_login_key) - 1);
	g_mode = PaDSelect;
	
	return 0;
}

int _stdcall SMT_ConnectMF280(int port, int baud)
{
	int ret = 0;
	char msg[10] = "";
//	port -= 1; 
	ret = SMT_LoadDll();
	if (ret)
		return ret;

	ret = func_OpenComm(port);
	/*
	itoa(port, msg, 10);
	::MessageBox(NULL, msg, "串口端口", NULL);

	itoa(ret, msg, 10);
	::MessageBox(NULL, msg, "打开串口返回值", NULL);
	*/
	if (ret < 0)
	{
		return ret;
	}

	return 0;
}

int _stdcall SMT_CloseMF280()
{	
//	ret = func_CloseComm(icdev);
	/*
	if (ret)
	{
		return ret;
	}
	*/
	func_CloseComm();
	return 0;
}

int _stdcall SMT_WriteBlock(int Sector, int BlockNo, unsigned char *BlockBuf)
{
	int ret = -1;
	unsigned char ucBlock = 0;
	unsigned char ucBlockBuf[20] = "";
	unsigned long ulSerial = 0;

	memcpy(ucBlockBuf, BlockBuf, 16);

	if (Sector <= 31)
		ucBlock = Sector * 4 + BlockNo;

	if (Sector > 31)
		ucBlock = 32 * 4 + (Sector - 32) * 16 + BlockNo;

	if (ret = SMT_LoadLoginKey(Sector, ucBlock)) { return ret; }

	ret = func_Rc_WriteData(ucBlock, ucBlockBuf);
	if (ret < 0)
	{
		return -6;
	}
	return 0;
}

int _stdcall SMT_ReadBlock(int Sector, int BlockNo, unsigned char *BlockBuf)
{
	int ret = -1;
	unsigned char ucBlock = 0;
	unsigned char ucBlockBuf[20] = "";
	unsigned long ulSerial = 0;
	
	if (Sector <= 31)
		ucBlock = Sector * 4 + BlockNo;

	if (Sector > 31)
		ucBlock = 32 * 4 + (Sector - 32) * 16 + BlockNo;
/*
	char msg[13] = "";

	itoa(Sector, msg, 10);
	::MessageBox(NULL, msg, "扇区", NULL);

	itoa(ucBlock, msg, 10);
	::MessageBox(NULL, msg, "块号", NULL);
*/

	if (ret = SMT_LoadLoginKey(Sector, ucBlock)) { return ret; }

	ret = func_Rc_ReadData(ucBlock, ucBlockBuf);
	if (ret < 0)
	{
		return -5;
	}
	memcpy(BlockBuf, ucBlockBuf, 16);

	return 0;
}

// 休眠卡片
// 没有这个功能提供
int _stdcall SMT_SleepCard()
{
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