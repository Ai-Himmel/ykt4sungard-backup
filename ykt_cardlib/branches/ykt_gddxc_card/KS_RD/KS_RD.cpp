/***************************************************************************************************/
/* ����........ʵ�ֶԻ��Ӳ���Ĳ���                                                                   
/* ����........�򿪴���, ������Կ, ��ȡ���ݣ�д������(�ڼ�������, �ڼ���), ����, �رմ���, ������Ϣ                                                            */
/* ����........����
/* ����........2006/13/07
/***************************************************************************************************/

#include "stdafx.h"
#include "stdlib.h"
#include "Comm.h"

static struct version_info 
{
	char ks_ver_no[20];
	char ks_ver_dcb[80];
}version_info = {"v1.0.0.0", "���������"};

//��Ȩ��־
int nAutoFlag = 0;
unsigned char UCWORKINGKEY[256]="";
char g_ErrMsg[1024]="";
int g_ErrCode=-1;

// �����豸��Ҫ�ĵײ�Ӳ��
unsigned char ucWorkKey[256];
unsigned char g_sInitWorkKey[256]="AE2C843443345394138464444";
unsigned char g_ucWORKINGKEY[256]="";
int icdev = 0;
//HANDLE g_hCom=NULL;
// typedef HANDLE (__stdcall* lp_rf_init)(__int16 port,long baud);
// typedef int (__stdcall* lp_rf_card)(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr);
// typedef int (__stdcall* lp_rf_load_key)(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
// typedef int (__stdcall* lp_rf_authentication)(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr);
// typedef int (__stdcall* lp_rf_read)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
// typedef int (__stdcall* lp_rf_write)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
// typedef int (__stdcall* lp_rf_halt)(HANDLE icdev);
// typedef int (__stdcall* lp_rf_exit)(HANDLE icdev);
// typedef int (__stdcall* lp_rf_beep)(HANDLE icdev,unsigned short _Msec);
// typedef int (__stdcall* lp_rf_anticoll)(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr);
// typedef int (__stdcall* lp_rf_request)(HANDLE icdev,unsigned char _Mode,unsigned int *TagType);
// typedef int (__stdcall* lp_rf_select)(HANDLE icdev,unsigned long _Snr,unsigned char *_Size);
// typedef int (__stdcall* lp_rf_authentication_2)(HANDLE icdev, unsigned char _Mode, unsigned char KeyNr, unsigned char Adr);
typedef int  (CALLBACK* lp_rf_init)(int port,long baud);
typedef void (CALLBACK* lp_rf_exit)(int icdev);
typedef int	 (CALLBACK* lp_rf_card)(int icdev,unsigned char _Mode,unsigned long *_Snr);
typedef int	 (CALLBACK* lp_rf_anticoll)(int icdev,unsigned char _Bcnt,unsigned long *_Snr);
typedef int  (CALLBACK* lp_rf_load_key)(int icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
typedef int  (CALLBACK* lp_rf_load_key_hex)(int icdev,unsigned char _Mode,unsigned char _SecNr,char *_NKey);
typedef int  (CALLBACK* lp_rf_halt)(int icdev);
typedef int  (CALLBACK* lp_rf_read)(int icdev,unsigned char _Adr,unsigned char *_Data);
typedef int  (CALLBACK* lp_rf_read_hex)(int icdev,unsigned char _Adr,unsigned char *_Data);
typedef int  (CALLBACK* lp_rf_write)(int icdev,unsigned char _Adr,unsigned char *_Data);
typedef int  (CALLBACK* lp_rf_write_hex)(int icdev,unsigned char _Adr,unsigned char *_Data);
typedef int  (CALLBACK* lp_rf_request)(int icdev,unsigned char _Mode,unsigned int *TagType);
typedef int  (CALLBACK* lp_rf_select)(int icdev,unsigned long _Snr,unsigned char *_Size);
typedef int  (CALLBACK* lp_rf_authentication)(int icdev,unsigned char _Mode,unsigned char _SecNr);
typedef int  (CALLBACK* lp_rf_beep)(int icdev,unsigned int _Msec);
typedef int  (CALLBACK* lp_rf_select)(int icdev,unsigned long _Snr,unsigned char *_Size);
typedef int  (CALLBACK* lp_rf_check_write)(int icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char *_data);

HINSTANCE				hDLL = NULL;
lp_rf_init				rf_init=NULL;
lp_rf_card				rf_card=NULL;
lp_rf_load_key			rf_load_key=NULL;
lp_rf_authentication	rf_authentication=NULL;
lp_rf_read				rf_read=NULL;
lp_rf_write				rf_write=NULL;
lp_rf_halt				rf_halt=NULL;
lp_rf_exit				rf_exit=NULL;
lp_rf_beep				rf_beep=NULL;
lp_rf_anticoll			rf_anticoll=NULL;
lp_rf_request			rf_request=NULL;
lp_rf_select			rf_select=NULL;
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

//���ô�����Ϣ
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
//ȡ������Ϣ
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
//*************��ȡ������뺯��*********************
int _stdcall GetMFLastErr()
{
	return ErrorCode;
}

int _stdcall MF_ReadSeriesNo(unsigned char *serial)
{
	int ret = 0;                                         // �豸��ʶ��
	unsigned int cardmode = 2;                           // ����ģʽ  
	unsigned char size=0;                                // ??��С
	unsigned long cardid = 0;                            // ����id��
	char bufCardId[10] = "";
	ret = rf_request(icdev,1,&cardmode);               // 1��ʾALLģʽ, һ�ο��ԶԶ��ſ��Ĳ���, �ɹ�����Ϊ0
	if(ret != 0)
	{
		return -2;
	}
	
	ret= rf_anticoll(icdev,0,&cardid);                 // ��ȡ�������к�(����������cardid), requestָ��֮��Ӧ��������anticoll�����ǿ������к���֪, �ɹ�����Ϊ0
	if(ret)
	{
		return ret;
	}
	// �����ַ����������к�
	memcpy(serial, (unsigned char*)&cardid, sizeof cardid);
	return 0;                                           
}

//1������û����Ƿ��ڸ�Ӧ��
int _stdcall SMT_RequestCardExist(unsigned char ucSerialNo[4],unsigned char ucType[1])
{
	unsigned char Buf[20] = "";
	int ret;
	unsigned char size = 0;
	unsigned long serialNo = 0;
	ret = MF_ReadSeriesNo(Buf);
	if(ret != 0)
	{
		SetLastErrMsg(ret, "��ȡ�����к�ʧ��");
		return ret;
	}

	ret= rf_anticoll(icdev, 0, &serialNo);
	if(ret != 0)
	{
		SetLastErrMsg(ret, "��������Ӧ��û�п�");
		return -2;
	}
	ret = rf_select(icdev, serialNo, &size);
	if(ret)
	{
		SetLastErrMsg(ret, "ѡ��ʧ��!");
		return ret;
	}
	if (ret == 0)							   // ��������Ϊ0 
	{
		memcpy(ucSerialNo,Buf,4);
//		memcpy(ucType,Buf+4,1);
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
	hDLL = LoadLibrary("RfReader.dll");
	if (!hDLL)
	{
		::AfxMessageBox("��̬��RfReader.dll����ʧ��!");
		return -1;
	}
	rf_init			  = (lp_rf_init)GetProcAddress(hDLL,"rf_init");
	rf_card	          = (lp_rf_card)GetProcAddress(hDLL,"rf_card");
	rf_load_key       = (lp_rf_load_key)GetProcAddress(hDLL,"rf_load_key");
	rf_authentication = (lp_rf_authentication)GetProcAddress(hDLL,"rf_authentication");
	rf_read	 	      = (lp_rf_read)GetProcAddress(hDLL,"rf_read");
	rf_write		  = (lp_rf_write)GetProcAddress(hDLL,"rf_write");
	rf_halt		      = (lp_rf_halt)GetProcAddress(hDLL,"rf_halt");
	rf_exit		      = (lp_rf_exit)GetProcAddress(hDLL,"rf_exit");
	rf_beep		      = (lp_rf_beep)GetProcAddress(hDLL,"rf_beep");
	rf_anticoll	      = (lp_rf_anticoll)GetProcAddress(hDLL,"rf_anticoll");
	rf_request	      = (lp_rf_request)GetProcAddress(hDLL,"rf_request");
	rf_select         = (lp_rf_select)GetProcAddress(hDLL,"rf_select");
	if ((!rf_init) ||
		(!rf_card) ||
		(!rf_load_key) ||
		(!rf_authentication) ||
		(!rf_read) ||
		(!rf_write)||
		(!rf_halt)||
		(!rf_exit)||
		(!rf_beep)||
		(!rf_anticoll)||
		(!rf_request)||
		(!rf_select) 
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
	int ret = 0;
	if (!icdev)
	{
		SetLastErrMsg(-1, "����%dδ��", icdev);
		return -1;
	}
	ret = rf_beep(icdev, 10);
	return 0;
}

int _stdcall SMT_Login_With_UserKey(int sector, unsigned char *Buffer, int PaDSelect)
{
// 0����keyA, 1����keyB
	int  ret;	
	unsigned char _mode = (PaDSelect == 1)? 4 : 0;
	unsigned char _sector = sector;
	unsigned long ucSerialNo = 0;
	unsigned char size = 0;
	unsigned int tagtype = 2;
	ret = rf_request(icdev, 1, &tagtype);	
	if(ret)
    {
		SetLastErrMsg(ret, "��������Ӧ��û�п�");
		return -2;
    }
	ret= rf_anticoll(icdev,0,&ucSerialNo);
	if(ret != 0)
	{
		SetLastErrMsg(ret, "��������Ӧ��û�п�");
		return -2;
	}
	ret = rf_select(icdev, ucSerialNo, &size);
	if(ret)
	{
		SetLastErrMsg(ret, "ѡ��ʧ��!");
		return ret;
	}	
	ret = rf_load_key(icdev, _mode, _sector, Buffer);           // �����޸ĵ�
	if (ret != 0)
	{
		SetLastErrMsg(ret, "װ������ʧ��!");
		return -3;
	}
	ret = rf_authentication(icdev, _mode, _sector); 
	if (ret != 0)
	{
		SetLastErrMsg(ret, "��֤��Կʧ��!");
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
	icdev = rf_init(port, baud);
	if(icdev < 0)
	{
		SetLastErrMsg(-1, "�򿪴���%dʧ��", icdev);
		return int(icdev);
	}
	SMT_ControlBuzzer();
	return 0;
}

int _stdcall SMT_CloseMF280()
{
	int ret = 0;
	rf_exit(icdev);
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
		ucBlock = Sector * 4 + BlockNo;
	
	if (Sector > 31)
		ucBlock = 32 * 4 + (Sector - 32) * 16 + BlockNo;
	
	ret=rf_write(icdev,ucBlock,ucBlockBuf);
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
		ucBlock = Sector * 4 + BlockNo;
	
	if (Sector > 31)
		ucBlock = 32 * 4 + (Sector - 32) * 16 + BlockNo;
	
	ret=rf_read(icdev,ucBlock,ucBlockBuf);
	if(ret)
	{
		SetLastErrMsg(ret, "���������ݴ�!");
		return -5;
	}
	memcpy(BlockBuf,ucBlockBuf,16);
	return 0;
}

// ���߿�Ƭ
int _stdcall SMT_SleepCard()
{
	int ret = -1;
	ret = rf_halt(icdev);
	if (ret)
	{
		SetLastErrMsg(ret, "����ʧ��!");
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