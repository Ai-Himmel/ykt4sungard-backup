/***************************************************************************************************/
/* ����........ʵ�ֶԻ��Ӳ���Ĳ���                                                                   
/* ����........�򿪴���, ������Կ, ��ȡ���ݣ�д������(�ڼ�������, �ڼ���), ����, �رմ���, ������Ϣ                                                            */
/* ����........����
/* ����........2006/13/07
/***************************************************************************************************/

#include "stdafx.h"
#include "stdlib.h"
#include "Comm.h"

#pragma  pack(1)
typedef struct _LOOPPURSEINFO
{
		DWORD RemainMoney;// ����Ǯ�����
		WORD DealTimes;// ��Ƭ������ˮ��
		BYTE DealYear; //��������
		BYTE DealMonth; 
		BYTE DealDay;
		BYTE DealHour;
		BYTE DealMin;
		BYTE DealTimes_CurTime; // �ۼƽ��״���(��ǰʱ�����)
		BYTE DealTimes_CurDay;// �ۼƽ��״���(������)
} LOOPPURSEINFO,*LPLOOPPURSEINFO;

#define SELECT_IDEL_MODE 0x00
#define SELECT_ALL_MODE 0x01
static int ModeFlag = 0;

#pragma  pack()

struct t_CardStruct
{
	unsigned long card_sn;
	int request_mode;
};

static struct t_CardStruct tCardStct = {0, 1};					// ALL MODE
static unsigned long g_ucSerialNo = -1;
static unsigned char g_size = 0;

static unsigned char s_water_common_card[2] = {0xF9,0x9E};
static unsigned char s_water_clear_card[2] = {0xF9,0x9C};
static unsigned char s_water_new_card[2] = {0xF9,0x9D};
static unsigned char s_water_auth_card[2] = {0xF9,0x9F};

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

typedef int (__stdcall* lp_dc_init)(int port,long baud);
typedef int (__stdcall* lp_dc_card)(int icdev,unsigned char _Mode,unsigned long *_Snr);
typedef int (__stdcall* lp_dc_load_key)(int icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
typedef int (__stdcall* lp_dc_authentication)(int icdev,unsigned char _Mode,unsigned char _SecNr);
typedef int (__stdcall* lp_dc_read)(int icdev,unsigned char _Adr,unsigned char *_Data);
typedef int (__stdcall* lp_dc_write)(int icdev,unsigned char _Adr,unsigned char *_Data);
typedef int (__stdcall* lp_dc_halt)(int icdev);
typedef int (__stdcall* lp_dc_exit)(int icdev);
typedef int (__stdcall* lp_dc_beep)(int icdev,unsigned short _Msec);
typedef int (__stdcall* lp_dc_anticoll)(int icdev,unsigned char _Bcnt,unsigned long *_Snr);
typedef int (__stdcall* lp_dc_request)(int icdev,unsigned char _Mode,unsigned int *TagType);
typedef int (__stdcall* lp_dc_select)(int icdev,unsigned long _Snr,unsigned char *_Size);
typedef int (__stdcall* lp_dc_authentication_2)(int icdev, unsigned char _Mode, unsigned char KeyNr, unsigned char Adr);


HINSTANCE				hDLL = NULL;
lp_dc_init				dc_init=NULL;
lp_dc_card				dc_card=NULL;
lp_dc_load_key			dc_load_key=NULL;
lp_dc_authentication	dc_authentication=NULL;
lp_dc_authentication_2	dc_authentication_2=NULL;
lp_dc_read				dc_read=NULL;
lp_dc_write				dc_write=NULL;
lp_dc_halt				dc_halt=NULL;
lp_dc_exit				dc_exit=NULL;
lp_dc_beep				dc_beep=NULL;
lp_dc_anticoll			dc_anticoll=NULL;
lp_dc_request			dc_request=NULL;
lp_dc_select			dc_select=NULL;
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

int _stdcall SMT_SelectMode(int Select_Mode)
{
	int ret;
	unsigned int tagtype = 2;	
	if (Select_Mode == SELECT_IDEL_MODE)
	{
		if (g_ucSerialNo == tCardStct.card_sn)
		{
			/*
			ret= rf_anticoll(icdev, 0, &g_ucSerialNo);
			if(ret != 0)
			{
				SetLastErrMsg(ret, "��������Ӧ��û�п�");
				return -2;
			}
			tCardStct.card_sn = g_ucSerialNo;
			*/
			return 0;
		}
		else
		{
			ret = dc_request(icdev, SELECT_IDEL_MODE, &tagtype);	
			if(ret)
			{
				SetLastErrMsg(ret, "��������Ӧ��û�п�");
				return -2;
			}
			ret= dc_anticoll(icdev, 0, &g_ucSerialNo);
			if(ret != 0)
			{
				SetLastErrMsg(ret, "��������Ӧ��û�п�");
				return -2;
			}
			ret = dc_select(icdev, g_ucSerialNo, &g_size);
			if(ret)
			{
				SetLastErrMsg(ret, "ѡ��ʧ��!");
				return ret;
			}
			tCardStct.card_sn = g_ucSerialNo;
			return 0;
		}
	}
	else if (Select_Mode == SELECT_ALL_MODE)
	{
		ret = dc_request(icdev, SELECT_ALL_MODE, &tagtype);	
		if(ret)
		{
			SetLastErrMsg(ret, "��������Ӧ��û�п�");
			return -2;
		}
		ret= dc_anticoll(icdev, 0, &g_ucSerialNo);
		if(ret != 0)
		{
			SetLastErrMsg(ret, "��������Ӧ��û�п�");
			return -2;
		}
		ret = dc_select(icdev, g_ucSerialNo, &g_size);
		if(ret)
		{
			SetLastErrMsg(ret, "ѡ��ʧ��!");
			return ret;
		}
		return 0;
	}
	else
	{
		return 0;
	}
}

int _stdcall MF_ReadSeriesNo(unsigned char *serial)
{
	int ret = 0;                                         // �豸��ʶ��
	unsigned int cardmode = 2;                           // ����ģʽ  
	unsigned char size = 0;                                // ??��С
	unsigned long cardid = 0;                            // ����id��
	char bufCardId[10] = "";
	SMT_SelectMode(tCardStct.request_mode);
	// ���·ſ�
	/*
	ret = rf_request(icdev, tCardStct.request_mode, &cardmode);  // 1��ʾALLģʽ, һ�ο��ԶԶ��ſ��Ĳ���, �ɹ�����Ϊ0
	if(ret != 0)
	{
		return -2;
	}
	
	ret= rf_anticoll(icdev,0,&cardid);                 // ��ȡ�������к�(����������cardid), requestָ��֮��Ӧ��������anticoll�����ǿ������к���֪, �ɹ�����Ϊ0
	if(ret)
	{
		return ret;
	}
	*/
	// �����ַ����������к�
	unsigned char tempSerialNo[5] = "";
	ltoa(g_ucSerialNo, bufCardId, 16);
	hex2dec(bufCardId, tempSerialNo, 16);
	for (int i = 0; i < 4; i++)
	{
		serial[i] = tempSerialNo[4 - i -1];
	}
//	if(serial)                                          // ��ַ�Ѿ�����
//		*serial = cardid;                                    
	return 0;                                           // �ɹ��򷵻�0
}

//1������û����Ƿ��ڸ�Ӧ��
int _stdcall SMT_RequestCardExist(unsigned char ucSerialNo[4],unsigned char ucType[1])
{
	unsigned char Buf[20] = "";
	int ret;
//	unsigned char size = 0;
	unsigned long serialNo = 0;
//	ret = Rf_GetSerial(Buf);                   // ����TRUEΪ1
	ret = MF_ReadSeriesNo(Buf);
	if(ret != 0)
	{
		SetLastErrMsg(ret, "��ȡ�����к�ʧ��");
		return ret;
	}
//	����Ķ��Ƚϴ�, ���������ݾ�Ȼ���ڿ�����
	/*
	ret= rf_anticoll(icdev, 0, &serialNo);
	if(ret != 0)
	{
		SetLastErrMsg(ret, "��������Ӧ��û�п�");
		return -2;
	}
	*/
	/*
	ret = rf_select(icdev, g_ucSerialNo, &size);
	if(ret)
	{
		SetLastErrMsg(ret, "ѡ��ʧ��!");
		return ret;
	}
	*/
	if (ret == 0)							   // ��������Ϊ0 
	{
		memcpy(ucSerialNo,Buf,4);
//		memcpy(ucType,Buf+4,1);
		memcpy(ucType, &g_size, 1);
		return 0;
	}
	return -1;
}

// �����豸��Ҫ�ĵ���Ӳ���豸�ĺ���
int SMT_LoadDll()
{
	if (hDLL)
	{
		return 0;
	}
	hDLL = LoadLibrary("dcrf32.dll");
	if (!hDLL)
	{
		::AfxMessageBox("��̬�����ʧ��!");
		return -1;
	}
	dc_init			  = (lp_dc_init)GetProcAddress(hDLL,"dc_init");
	dc_card	          = (lp_dc_card)GetProcAddress(hDLL,"dc_card");
	dc_load_key       = (lp_dc_load_key)GetProcAddress(hDLL,"dc_load_key");
	dc_authentication = (lp_dc_authentication)GetProcAddress(hDLL,"dc_authentication");
	dc_read	 	      = (lp_dc_read)GetProcAddress(hDLL,"dc_read");
	dc_write		  = (lp_dc_write)GetProcAddress(hDLL,"dc_write");
	dc_halt		      = (lp_dc_halt)GetProcAddress(hDLL,"dc_halt");
	dc_exit		      = (lp_dc_exit)GetProcAddress(hDLL,"dc_exit");
	dc_beep		      = (lp_dc_beep)GetProcAddress(hDLL,"dc_beep");
	dc_anticoll	      = (lp_dc_anticoll)GetProcAddress(hDLL,"dc_anticoll");
	dc_request	      = (lp_dc_request)GetProcAddress(hDLL,"dc_request");
	dc_select         = (lp_dc_select)GetProcAddress(hDLL,"dc_select");
	dc_authentication_2 = (lp_dc_authentication_2)GetProcAddress(hDLL, "dc_authentication_2");
	if ((!dc_init) ||
		(!dc_card) ||
		(!dc_load_key) ||
		(!dc_authentication) ||
		(!dc_read) ||
		(!dc_write)||
		(!dc_halt)||
		(!dc_exit)||
		(!dc_beep)||
		(!dc_anticoll)||
		(!dc_request)||
		(!dc_select) ||
		(!dc_authentication_2)
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
	ret = dc_beep(icdev, 10);
	return 0;
}

int _stdcall SMT_Login_With_UserKey(int sector, unsigned char *Buffer, int PaDSelect)
{
// 0����keyA, 1����keyB
	int  ret;
	
	unsigned char _mode = (PaDSelect == 1)? 4 : 0;
	unsigned char _sector = sector;
// 	char bufMode[2] = "";
// 	char bufSector[2] = "";
//	int i;
//	unsigned char ucRawData[256],ucRawDataTmp[4],ucDesData[256],ucKeyA[20];
	unsigned char size = 0;
	unsigned long serialNo = 0;
//	unsigned char ucBuf[4];
//	char ucTmp[9];
// 	itoa(sector, bufMode, 10);
// 	itoa(PaDSelect, bufSector, 10);
// 	hex2dec(bufMode, _mode, 2);
// 	hex2dec(bufSector, _sector, 2);
	SMT_SelectMode(tCardStct.request_mode);
//	ret= rf_anticoll(icdev, 0, &serialNo);
	/*
	ret = rf_select(icdev, g_ucSerialNo, &size);
	if(ret)
	{
		SetLastErrMsg(ret, "ѡ��ʧ��!");
		return ret;
	}
	*/
	ret = dc_load_key(icdev, _mode, _sector, Buffer);           // �����޸ĵ�
	if (ret != 0)
	{
		SetLastErrMsg(ret, "װ������ʧ��!");
		return -3;
	}
	ret = dc_authentication(icdev, _mode, _sector); 
	if (ret != 0)
	{
		SetLastErrMsg(ret, "��֤��Կʧ��!");
		return -4; 
	}
	return 0;
}

int _stdcall SMT_ConnectMF280(int port, int baud)
{
	int ret = 0;
//	port -=1;				
	ret = SMT_LoadDll();
	if(ret)
		return ret;
	port = 100;
	icdev = dc_init(port, baud);
	if(icdev < 0)
	{
		SetLastErrMsg(-1, "�򿪴���%dʧ��", icdev);
		return int(icdev);
	}
	return 0;
}

int _stdcall SMT_CloseMF280()
{
	int ret=0;
// 	ret = SMT_LoadDll();
// 	if(ret) {return ret;}
	ret=dc_exit(icdev);
	if (ret)
	{
		SetLastErrMsg(ret, "�رմ���ʧ��");
		return -2;
	}
	return 0;
}

int _stdcall SMT_WriteBlock(int Sector,int BlockNo,unsigned char *BlockBuf)
{
	int ret;
	unsigned char ucBlock=0;
	unsigned char ucBlockBuf[20]="";
	unsigned long ulSerial=0;

	memcpy(ucBlockBuf,BlockBuf,16);
	ucBlock=Sector*4+BlockNo;

	ret=dc_write(icdev,ucBlock,ucBlockBuf);
	if(ret)
	{
	//	rf_halt(icdev);
	//	rf_exit(icdev);
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
	ucBlock=Sector*4+BlockNo;
	ret=dc_read(icdev,ucBlock,ucBlockBuf);
	if(ret)
	{
		SetLastErrMsg(ret, "���������ݴ�!");
		return -5;
	}
	memcpy(BlockBuf,ucBlockBuf,16);
	return 0;
}

// ���߿�Ƭ
// û����������ṩ
int _stdcall SMT_SleepCard()
{
	int ret;
	ret = dc_halt(icdev);
	if (ret)
	{
		return -8;
	}
	if (tCardStct.request_mode == 0)
	{
		g_ucSerialNo = -2;					// �������ֵ���ܸ�tCardStct��card_snһ��
	}
	return 0;
}

