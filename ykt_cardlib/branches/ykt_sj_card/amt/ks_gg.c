#include "Gjk.h"
#include "ks_gg.h"

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
//////////////////////////////////////////////////////////////////////////

int Rc_OpenComm()
{
	return 0;
}

void Rc_CloseComm()
{
	return ;
}

//设置错误信息
void SetLastErrMsg(int err_code,char* format, ...)
{
	 char buffer[1024]="";
	 strcpy(g_err_msg, buffer);
	 g_err_code = err_code;
}
//取错误信息
void SMT_GetLastErr(int* pErrCode,char *Msg)
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
int GetMFLastErr()
{
	return g_err_code;
}

int MF_ReadSeriesNo(unsigned char *serial)
{
	int ret = 0;                                         // 设备标识

	if ((ret = Rc_CloseCard(COMM_DEVFD)) < 0) { return -10; }
	
    if ((ret = Rc_anticoll(COMM_DEVFD, ACTIVE_MODE, serial)) < 0 )
	{
		return -2;
	}

	return 0;                                           // 成功则返回0
}

int SMT_RequestCardExist(unsigned char ucSerialNo[4], unsigned char ucType[1])
{
	int ret = 0;
	unsigned char Buf[20] = "";
    ret = Rc_anticoll(COMM_DEVFD, ACTIVE_MODE, Buf);
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
	return 0;
}


int SMT_ControlBuzzer()
{
	return 0;
}

static int SMT_LoadLoginKey(unsigned char sector, unsigned char block)
{
	int ret = 0;
	unsigned char serial_no[20] = "";

  	if ((ret = Rc_CloseCard(COMM_DEVFD)) < 0) { return -10; }

//	if ((ret = func_ActiveCard(0, serial_no)) < 0) { return -11; }		// 0 表示ALL, 1表示IDEL模式
  	if ((ret = Rc_ActiveCard(COMM_DEVFD, ACTIVE_MODE, serial_no)) < 0) { return -11; }

    if ((ret = Rc_LoadPwd(COMM_DEVFD, g_mode, sector, g_login_key)) < 0) { return -12; }

  	if ((ret = Rc_ConfirmPwd(COMM_DEVFD, block, g_mode, serial_no)) < 0 ) { return -13; }

	return 0;
}

int SMT_Login_With_UserKey(int sector, unsigned char *Buffer, int PaDSelect)
{
	memcpy(g_login_key, Buffer, sizeof(g_login_key) - 1);
	g_mode = PaDSelect;

	return 0;
}

int SMT_ConnectMF280(int port, int baud)
{
	int ret = 0;

	ret = SMT_LoadDll();
	if (ret)
		return ret;
	
  	ret = Rc_OpenComm(port);
	if (ret < 0)
	{
		return ret;
	}

	return 0;
}

int SMT_CloseMF280()
{
    Rc_CloseComm();
	return 0;
}

int SMT_WriteBlock(int Sector, int BlockNo, unsigned char *BlockBuf)
{
	int ret = -1;
	unsigned char ucBlock = 0;
	unsigned char ucBlockBuf[20] = "";
	unsigned long ulSerial = 0;
	char err_msg[128] = "";
	
	memcpy(ucBlockBuf, BlockBuf, 16);

	if (Sector <= 31)
		ucBlock = Sector * 4 + BlockNo;

	if (Sector > 31)
		ucBlock = 32 * 4 + (Sector - 32) * 16 + BlockNo;

	if (ret = SMT_LoadLoginKey(Sector, ucBlock)) { return ret; }

	ret = Rc_WriteData(COMM_DEVFD, ucBlock, ucBlockBuf);
	if (ret < 0)
	{
	/*
		sprintf(err_msg, "write sector=[%d]--block=[%d] failed", Sector, ucBlock);
		printf_menu(1, 1, 1, err_msg);
		limit_getkey((unsigned long)15);
	*/
		return -6;
	}

	if ((ret = Rc_CloseCard(COMM_DEVFD)) < 0) { return -10; }
	
	return 0;
}

int SMT_ReadBlock(int Sector, int BlockNo, unsigned char *BlockBuf)
{
	int ret = -1;
	unsigned char ucBlock = 0;
	unsigned char ucBlockBuf[20] = "";
	char err_msg[128] = "";
	
	if (Sector <= 31)
		ucBlock = Sector * 4 + BlockNo;

	if (Sector > 31)
		ucBlock = 32 * 4 + (Sector - 32) * 16 + BlockNo;

	if (ret = SMT_LoadLoginKey(Sector, ucBlock)) { return ret; }

	ret = Rc_ReadData(COMM_DEVFD, ucBlock, ucBlockBuf);
	if (ret < 0)
	{
		return -5;
	}
	memcpy(BlockBuf, ucBlockBuf, 16);

//	if ((ret = Rc_CloseCard(COMM_DEVFD)) < 0) { return -10; }
	
	return 0;
}

// 休眠卡片
// 没有这个功能提供
int SMT_SleepCard()
{
	return 0;
}

int SMT_GetDllVersion(char *ks_ver_no, char *ks_ver_dcb)
{
	if (strlen(strcpy(ks_ver_no, version_info.ks_ver_no)) == 0)
		return -1;
	
	if (strlen(strcpy(ks_ver_dcb, version_info.ks_ver_dcb)) == 0)
		return -1;

	return 0;
}