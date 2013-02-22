/*=================================================================================
* ģ����:	    һ��ͨ���������ܶ�̬��
* �ļ���:		CardDLL.cpp 
* ����ļ�:     CardDLL.h
* �ļ�ʵ�ֹ���: �Կ����ܲ��� 
* ����:		    ���� 
* �汾:			---  
* ---------------------------------------------------------------------------------
* ��ע:          
* ---------------------------------------------------------------------------------
* �޸ļ�¼: 
* ����			 �汾			�޸���			�޸�����		 					
* 2006-9-25		 ---		    ����            ��ҵ��ģ��ͻ���ģ��ֿ�
* �޸ļ�¼: 
* ����			 �汾			�޸���			�޸�����		 					
* 2007-7-12		 1.1.000		����            ��ӹ��ݴ�ѧ��ר�п�Ƭ����
* �޸ļ�¼: 
* ����			 �汾			�޸���			�޸�����		 					
* 2007-8-04		 1.1.001		����            ��ӹ��ݴ�ѧ�Ƕ�дˮ����������
* �޸ļ�¼: 
* ����			 �汾			�޸���			�޸�����		 					
* 2007-8-09		 1.1.002		����            �޸Ĺ��ݴ�ѧ�Ƕ�дˮ����������BUG:
*												(1)�޸ĵ�һ�η��п��ɶ�ˮ������
*												(2)�޸ĵ�һ�η��п���дˮ������
*
* ����			 �汾			�޸���			�޸�����		 					
* 2007-8-10		 1.1.003		����            �޸ķ��п�BUG:
*												(1)���п�ʱǰ̨������ʾ���ſ�д��,
*												   ǰ̨�������ʾ�����򲻿�д��
*
* 2007-8-14		 1.1.003		����            �޸ķ��п�BUG:
*												(1)�޸�CardDll.cpp�д򿪴��ں���, 
*												   �������ض�̬����߼�����
*                                               (2)�޸�CardDll.cpp�м��ض�̬�⺯��, 
*                                                  �����������ε��ó����߼����������
*                                               (3)��ӳ�ʼ����Ȩ��д����־��0����						
*                                               (4)�޸ķ�����Ȩ����0��������־д�ҵ�����
*                                               (5)�޸�������Ȩ���������汾д�����ݵ�����
*                                               (6)�޸ĵ�¼��Ȩ����Կ��������, 
*                                                  ���������յ��³���down��������
*
* ����			 �汾			�޸���			�޸�����		 					
* 2007-8-17		 1.1.004		����            (1)SMT_ClearCard��ʱ���ж�33�����Ƿ�
*                                                  ��ʼ����δ�г�ʼ������մ�����
*
* ����			 �汾			�޸���			�޸�����		 					
* 2007-8-22		 1.1.005		����            (1)�޸�UpdateCardInfo����, ���Ӹ��½��׿���
*                                               (2)����SMT_UpdateMoneyAndTxCnt����,
*												   �޸Ľ��, ���״���, ���κ�
*
* ����			 �汾			�޸���			�޸�����		 					
* 2007-8-23		 1.1.005		����            (1)����SMT_UpdateSubsidy���� 
* =================================================================================
*/

#include "stdafx.h"
#include "CardDLL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <time.h>
#include <mbstring.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <set>

#define CARDDLL_VERSION "1.4.004-guangzhou"

int InitInstance();
int ifReadyOK();
//int isConnectMF = -1;    //�ж϶�д���Ƿ�ɹ���ʼ��
static int	ErrCode;
static char ErrMsg[256];

static int g_WaterCardType = 0;

// ������SMARTCOM411DXQ.dll
unsigned char SMT_UCWORKINGKEY[256]="";
int nAutoFlag = 0;

typedef std::map<int,double> CARD_MONEY_MAP;

typedef std::set<int> INT_SET_TYPE;
static INT_SET_TYPE g_init_sect_set;

CARD_MONEY_MAP g_cardmoney;
std::ofstream g_cardlogger;
//////////////////////////////////////////////////////////////////////////
// ��ʼ����
// ��ʼ��������
//#define SMARD_CARD_SECT_NO 32
static int smart_card_sect_no = 32;
// ��Ȩ��������
#define AUTH_CARD_SECT_NO 32
// ��Կ����
#define CARD_KEY_LEN 6
// ��ʼ����ʱд��Ŀ���λ
static BYTE CARD_NEW_CTRL_BIT[] = {0x7F,0x07,0x88,0x00};
// ����ʱ�Ŀ���λ
static BYTE CARD_INIT_CTRL_BIT[] = {0xFF,0x07,0x80,0x69};   // KEYA��KEYB������ͬȨ��(��д), Ĭ�ϳ�������µ�KEYB�˶���Ч
// �ϴ�14��������λ
static BYTE CARD_FOR14_CTRL_BIT[] = {0x78,0x77,0x88,0x00};	// KEYA��KEYB�ɶ���д
// PHILIP������
static BYTE PHILIPS_CARD_TYPE[] = {0x18,0};
// ��Կ���ڵĿ��
#define PASSWD_BLOCK_NUM 3
// ��Ȩ��Կ
static BYTE CARD_MAIN_KEY[9] = "";
// �жϴ����Ƿ��Ѿ���
static BOOL com_is_open = FALSE;


// �жϿ�����
#define BARE_CARD_TYPE 1
#define INIT_CARD_TYPE 2
#define UNRECOGNISE_CARD_TYPE 3

// ��ʼ���Ľ�ֵ
static BYTE CARD_INIT_KEY[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
// �ж��Ƿ��Ѷ���Ȩ��
static BOOL has_read_main_key = FALSE;
// ��Ȩ��־
static short AUTH_CARD_FLAG = -1;
static unsigned char s_water_common_card[2] = {0xF9,0x9E};
static unsigned char s_water_clear_card[2] = {0xF9,0x9C};
static unsigned char s_water_clear_card2[2] = {0xF9,0x9A};
static unsigned char s_water_new_card[2] = {0xF9,0x9D};
static unsigned char s_water_auth_card[2] = {0xF9,0x9F};

// ���ݴ�ѧ��ר�п�Ƭ��������
#define GZ_UNIVERSITY_TOWN 1			    // ͨ���궨�������ֺ����4k����
#define SMARD_CARD_SECT4K_NO 36				// ��4k������ʼ������
#define GZ_CARD_SECT 0						// ���ݴ�ѧ�Ǵӵ� 16 ����
#define GZ_SHUIKONG_SECT 33					// ���ݴ�ѧ��ˮ������
static int g_gz_card_end_sect = 40;			// ���ݴ�ѧ�ǳ�ʼ������������
#define PASSWD_BLOCK1_NUM 15				// 32����������ݿ鶼Ϊ16��
static char g_init_sect_map[40];            // ��ʼ��������
// ���ݴ�ѧ��ר��ˮ��ת�˵�¼��Կ
// ����ˮ����Կ
static unsigned char LOGIN_WATER_KEYA[7] = {0x33, 0x25, 0x26, 0xab, 0xcd, 0xef};   
static unsigned char LOGIN_WATER_KEYB[7] = {0x07, 0x64, 0x36, 0x01, 0x36, 0x00};
// ����ˮ����Կ
static unsigned char XT_LOGIN_WATER_KEYA[7] = {0x39,0x35,0x40,0x32,0x00,0x00};

// �Ϻ�����ѧˮ�ش���������
#define COLLECT_CARD_SECT_NO 32				// �ɼ�����Ч������ 

// ������Ȩ����Կʱ������
static BYTE AUTH_CARD_SEED[8] = "";

//////////////////////////////////////////////////////////////////////////
char bufSmartCom[512] = "";
char bufDesdll[512] = "";
char bufJdcdll[512] = "";
char pathBuf[512] = "";
char iniFilePathBuf[512] = "";

static size_t split_string(std::vector<std::string> &str_list,const std::string &str,char delimiter)
{
	size_t pos,next_pos;
	str_list.clear();
	pos = 0;
	while(1)
	{
		next_pos = str.find(delimiter,pos);
		if(next_pos == str.npos)
		{
			if(pos < str.size())
			{
				str_list.push_back(str.substr(pos,str.size()-pos));
			}
			break;
		}
		str_list.push_back(str.substr(pos,next_pos-pos));
		pos = next_pos+1;
	}
	return str_list.size();
}
static int do_load_list()
{
	std::string line;
	std::ifstream ifs;
	std::vector<std::string> tokens;

	g_cardlogger.open("watercardlog.txt",std::ofstream::out|std::ofstream::app);
	if(!g_cardlogger.good())
		return -1;

	ifs.open("watercard.lst",std::ifstream::in);
	
	if(!ifs.good())
		return -1;
	
	g_cardmoney.clear();
	while(!ifs.eof())
	{
		std::getline(ifs,line);
		if(split_string(tokens,line,',') < 2)
			continue;
		int card_id = atoi(tokens[0].c_str());
		double money = atof(tokens[1].c_str());
		g_cardmoney.insert(CARD_MONEY_MAP::value_type(card_id,money));
		//g_cardlogger<<"card["<<card_id<<"]money["<<money<<"]"<<std::endl;
	}
	return 0;
}

static void get_curr_datetime(char *datetime)
{
	time_t curr;
	struct tm * time_info;
	time(&curr);
	time_info = localtime(&curr);
	sprintf(datetime,"%04d%02d%02d%02d%02d",
		1900+time_info->tm_year,
		time_info->tm_mon+1,
		time_info->tm_mday,
		time_info->tm_hour,
		time_info->tm_min,
		time_info->tm_sec);
}
static int do_is_exists(int card_id,double *money)
{
	int ret;
	CARD_MONEY_MAP::const_iterator i;
	i = g_cardmoney.find(card_id);
	if(i == g_cardmoney.end())
		return -1;
	*money = i->second;
	return 0;
}

static void do_init_card_sect()
{
	int i;
	g_init_sect_set.clear();
	for(i = 0;i< 48;++i)
	{
		g_init_sect_set.insert(i);
	}
}
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	GetModuleFileName((HMODULE)hModule, iniFilePathBuf, sizeof(iniFilePathBuf));
 	GetIniFileFromDll(iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLL1", "", bufSmartCom, sizeof(bufSmartCom), iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLL2", "", bufDesdll, sizeof(bufDesdll), iniFilePathBuf);
    GetPrivateProfileString("LOADLIBRARY", "DLL3", "", bufJdcdll, sizeof(bufJdcdll), iniFilePathBuf);
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			do_init_card_sect();
			do_load_list();
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// ��ȡָ��Ŀ¼���ļ�
void GetIniFile(char *FilePathBuf)
{
	char pathBuf[512] = "";
	int len = GetModuleFileName(NULL, pathBuf, sizeof(pathBuf));
	if (len <= 0)
	{
		MessageBox(NULL, "Get Path Err!", "", NULL);
		return ;
	}
	char *p = pathBuf + len;
	while (p >= pathBuf)
	{
		if (*p == '\\')
		{
			break;
		}
		p--;
	}
	if (p > pathBuf)
	{
		*p = '\0';
	}

	if (!strnicmp(p - 4, "\\dll", 4))
	{
		p -= 4;
		*p = '\0';
	}
	strncat(pathBuf, "\\CardDll.ini", 13);
	strcpy(FilePathBuf, pathBuf);
}
//////////////////////////////////////////////////////////////////////////

// ͨ����̬��CardDll.dll���ini�ļ�·�� 
void GetIniFileFromDll(char *FilePathBuf)
{
	char *cpPose = NULL;
	if (cpPose = strrchr(FilePathBuf, '\\'))
		strcpy(cpPose + 1, "CardDll.ini");
	
	cpPose += sizeof("CardDll.ini") + 1;
	cpPose = '\0';
}

HINSTANCE hDLL = NULL;
typedef INT (CALLBACK* LPSMT_ConnectMF280)(int, int);
typedef INT (CALLBACK* LPSMT_ControlBuzzer)(void);
typedef INT (CALLBACK* LPSMT_CloseMF280)(void);	
typedef INT (CALLBACK* LPSMT_RequestCardExist)(unsigned char *,unsigned char *);
typedef INT (CALLBACK* LPSMT_SleepCard)();
typedef void (CALLBACK* LPSetLastErrMsg)(int err_code,char* format, ...);
typedef void (CALLBACK* LPGetMFLastErr)();
typedef INT	(CALLBACK* LPMF_ReadSeriesNo)(unsigned char *Buffer);
typedef INT (CALLBACK* LPSMT_ExeCommand)(unsigned char *Buffer,int Len);
typedef INT (CALLBACK* LPSMT_Login_With_UserKey)(int Sector, unsigned char *Buffer, int PaDSelect);
typedef INT (CALLBACK* LPSMT_WriteBlock)(int Sector,int BlockNo,unsigned char *BlockBuf);
typedef INT (CALLBACK* LPSMT_ReadBlock)(int Sector,int BlockNo, unsigned char *BlockBuf);
typedef void (CALLBACK* LPSMT_CopyWorkingKey)(unsigned char *SMT_UCWORKINGKEY);
typedef int (CALLBACK * LPSMT_GetHandle)();

LPSMT_ConnectMF280				SMT_ConnectMF280=NULL;
LPSMT_ControlBuzzer				SMT_ControlBuzzer=NULL;
LPSMT_CloseMF280				SMT_CloseMF280=NULL;
LPSMT_RequestCardExist			SMT_RequestCardExist=NULL;
LPSMT_GetHandle					SMT_GetHandle=NULL;

//Ǯ������
LPSMT_SleepCard		 SMT_SleepCard=NULL;

// ��½��
LPSMT_Login_With_UserKey SMT_Login_With_UserKey = NULL;

// ��ȡ���к�
LPMF_ReadSeriesNo MF_ReadSeriesNo = NULL;

// ��, д�����ݿ�
LPSMT_ReadBlock SMT_ReadBlock = NULL; 
LPSMT_WriteBlock SMT_WriteBlock = NULL;

// ���ó�����Ϣ
LPSetLastErrMsg SetLastErrMsg = NULL;
LPGetMFLastErr GetMFLastErr = NULL;

// ����ȫ���ַ���
LPSMT_CopyWorkingKey SMT_CopyWorkingKey = NULL;

// ��Կ���㺯��(������Desdll.dll)
HINSTANCE hDesDLL = NULL;
typedef long (CALLBACK* lpgen_user_card_keyA )(unsigned char *key,unsigned char *text,unsigned char *keyA);;
typedef long (CALLBACK* lpgen_user_card_keyB )(unsigned char *key,unsigned char *text,unsigned char *keyA);;
typedef INT  (CALLBACK* lpencrypt_work_key)(unsigned char* text,unsigned char* mtext);
typedef long (CALLBACK* lpgen_auth_card_keyA)(BYTE seed[8],BYTE key[6]);
typedef long (CALLBACK* lpgen_auth_card_keyB)(BYTE seed[8],BYTE key[6]);
typedef long (CALLBACK* lpdecrypt_work_key)(BYTE src_key[8],BYTE des_key[8]);
typedef long (CALLBACK* lpget_check_char)(BYTE buf[16]);
typedef int	 (CALLBACK* lpgen_card_ming_des)(unsigned char *text, unsigned char *user_key);
typedef int (CALLBACK * lpencrypt_elec_card_pwd)(int cut_id,const char seedkey[32],const char pwd[8],char mpwd[64]);
typedef int (CALLBACK* lpdecrypt_elec_card_pwd)(int cut_id,const char seedkey[32],const char mpwd[64],char pwd[8]);
lpgen_user_card_keyA	gen_user_card_keyA	= NULL;
lpgen_user_card_keyB	gen_user_card_keyB	= NULL;
lpencrypt_work_key      encrypt_work_key	= NULL; 
lpgen_auth_card_keyA	gen_auth_card_keyA	= NULL;
lpgen_auth_card_keyB	gen_auth_card_keyB	= NULL;
lpdecrypt_work_key		decrypt_work_key	= NULL;
lpget_check_char		get_check_char		= NULL;
lpgen_card_ming_des     gen_card_ming_des	= NULL;
lpencrypt_elec_card_pwd encrypt_elec_card_pwd = NULL;
lpdecrypt_elec_card_pwd decrypt_elec_card_pwd = NULL;

// ˮ���������ܽ��ܺ���(������JDyktCustomerCardDLL.dll)
HINSTANCE hJdcDLL = NULL;
typedef int (CALLBACK * LPEncodeData)(const unsigned long card_no, 
									  const unsigned long group_id,
									  const unsigned long customer_id,
									  const double price1,
									  const double price2,
									  const double price3,
									  const double balance,
									  unsigned char *data);

typedef int (CALLBACK * LPDecodeData)(unsigned char *data,
									  const unsigned long card_no, 
									  unsigned long *group_id,
									  unsigned long *customer_id,
									  double *price1,
									  double *price2,
									  double *price3,
									  double *balance
									  );
LPEncodeData EncodeData = NULL;
LPDecodeData DecodeData = NULL;

// ˮ�ؼ��ܺ���������
HINSTANCE hXTDLL = NULL;
typedef int (WINAPI *LPUserDataToCard)(unsigned long CardID,unsigned long OperationMoney,unsigned long RemnantMoney,
						  unsigned short flag,unsigned char * OldData,unsigned char *NewData);
typedef int (WINAPI *LPCardToUserData)(unsigned char *sourceData,unsigned long *CardID,unsigned long *OperationMoney,
									 unsigned long *RemnantMoney);
LPUserDataToCard UserDataToCard = NULL;
LPCardToUserData CardToUserData = NULL;


static void round_float(double *f, int bits) 
{
	static const int DECIMAL_BASE = 10;    
	unsigned int n,scale,m;    
	int i;
	scale = 1;
	for (i = 0; i < bits + 1;  i++)
	{
		scale *= DECIMAL_BASE;
	}

	n = (*f) * scale;
	//	n += 5;
	m = n % 10;
	if (m < 5)
		n = n - m;
	else
		n = n - m + 10;    

	*f = ((double)n / scale);
}

static int double_2_int(double f)
{
	double t;
	t = f;
	round_float(&t,0);
	return (int)t;
}
// ����KEYA
static void SMT_Cal_KeyA(unsigned char *key, unsigned char *ucSerialNo, unsigned char *ucKeyA)
{
	gen_user_card_keyA(key, ucSerialNo, ucKeyA);
}

// ����KEYB
static void SMT_Cal_KeyB(unsigned char *key, unsigned char *ucSerialNo, unsigned char *ucKeyB)
{
	gen_user_card_keyB(key, ucSerialNo, ucKeyB);	
}

//ʹ�ø�����Կ��ϵ��½��Ƭ
static int Login_Card_Keya(int sector)
{
	unsigned char ucSerialNo[10], ucKeyA[8];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	//1 --- ����KEYA
	if (SMARD_CARD_SECT4K_NO == sector)
		gen_card_ming_des(ucSerialNo, ucKeyA);
	else if (SMARD_CARD_SECT4K_NO - 3 == sector)
	{
		if(g_WaterCardType==0)
			memcpy(ucKeyA,XT_LOGIN_WATER_KEYA,sizeof(ucKeyA));
		else
			memcpy(ucKeyA, LOGIN_WATER_KEYA, sizeof(ucKeyA));
	}
	else
		SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	
	ret = SMT_Login_With_UserKey(sector, ucKeyA, 0);                       
	if (ret != 0)
	{
		return -2;//��Ƭ��½ʧ��
	}
	return 0;
}

//ʹ�ø�����Կ��ϵ��½��Ƭ
static int Login_Card_Keyb(int sector)
{
	unsigned char ucSerialNo[5], ucKeyB[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	//1 --- ����KEYB
	if(sector == 33)
		memcpy(ucKeyB,LOGIN_WATER_KEYB,6);
	else
		SMT_Cal_KeyB(SMT_UCWORKINGKEY, ucSerialNo, ucKeyB);
	ret = SMT_Login_With_UserKey(sector, ucKeyB, 1);                       
	if(ret != 0)
	{
		return -2;
	}
	return 0;
}

void SetErrMsg(int ecode,char *errmsg)
{
	ErrCode=ecode;;
	strcpy(ErrMsg,errmsg);
}

int __stdcall GetLastErrMsg(int ecode[1],char *errmsg)
{
	ecode[0]=ErrCode;
	strcpy(errmsg,ErrMsg);
	return 0;
}

int __stdcall dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len)
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

int __stdcall bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr)
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

//////////////////////////////////////////////////////////////////////////
// ������㺯��
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

// �ı����������unsigned char* �� char*
int  bcd2decA(unsigned char *sBcdStr, int bcd_len, char *sDecStr)
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
//////////////////////////////////////////////////////////////////////////

void __stdcall SetCardSectLength(const int card_sect_length)
{
	smart_card_sect_no = card_sect_length;
	return ;
}

int __stdcall ConnectMF(int com,int baud)
{
	int ret = 0;
	if (hDLL == NULL || hDesDLL == NULL || hJdcDLL == NULL)
	{
		ret = Load_Dll();
		if (ret)
			return -1;
	}
	
	if (com < 0)
	{
		com = 1;       //Ĭ�ϴ���1
	}
	
	if (baud < 1)
	{
		baud = 19200;  //Ĭ��19200
	}
	
	ret = SMT_ConnectMF280(com, baud);
	
	if (ret != 0)
	{
		return ret;
	}
	
	com_is_open = TRUE;
 	SMT_ControlBuzzer();
	return 0;
}

int __stdcall CloseMF(void)
{
	int ret = 0;
	ret = SMT_CloseMF280();
	if(ret)
	{
		SetErrMsg(ret,"�رմ���ʧ��");
		return ret;
	}
	return 0;
}

int __stdcall ControlBuzzer()
{
	SMT_ControlBuzzer();
	return 0;
}

int __stdcall SMT_GetCOMHandle()
{
	if(SMT_GetHandle!=NULL)
		return SMT_GetHandle();
}

int __stdcall HaltCard(void)
{
	int ret = 0;
	ret = SMT_SleepCard();
	if (ret)
	{
		SetErrMsg(ret, "���߿�ʧ��");
		return ret;
	}
	return 0;
}

//���п�
int __stdcall PublishCard(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	unsigned char phyid[9];
	BOOL bPersonalFlag=TRUE;
	BOOL bStateFlag=TRUE;
	BOOL bBankInfo=TRUE;
	BOOL bPacketFlag[8]={TRUE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE};
	int iCardNo[1];
	memset(ucBcdShowCardNo,0,sizeof(ucBcdShowCardNo));

	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	MF_ReadSeriesNo(phyid);
	ret = SMT_ClearCard();
	if(ret)
	{
		SetErrMsg(ret,"��ʼ��Ǯ������ʧ��");
		return ret;
	}

/*
	ret = SMT_ClearCard();
	if (ret)
	{
//		SetErrMsg(ret,"��ʽ����ʧ��");
		return ret;
	}
*/	
	ret = strlen((char*)pc->ShowCardNo);
	if (10 == ret)	
	{
		//ת��ΪBCD��
		dec2bcd(pc->ShowCardNo,ucBcdShowCardNo,5);
	}
	else
	{
		if (ret = SMT_ReadShowCardNo(ucBcdShowCardNo))
			return ret;
	}

	//ת��Ϊ����
	char sYear[3];
	char sMon[3];
	char sDay[3];
	
	memset(sYear,0,sizeof(sYear));
	memset(sMon,0,sizeof(sMon));
	memset(sDay,0,sizeof(sDay));

	memcpy(sYear,pc->DeadLineDate+2,2);
	memcpy(sMon,pc->DeadLineDate+4,2);
	memcpy(sDay,pc->DeadLineDate+6,2);
	
	ucDeadLineDate[0]=atoi(sYear);
	ucDeadLineDate[1]=atoi(sMon);
	ucDeadLineDate[2]=atoi(sDay);
	iCardNo[0]=atoi((char*)pc->CardNo);
	ucCardRightType[0]=pc->CardRightType;
	ret = SMT_WriteCardStateInfo(ucBcdShowCardNo,iCardNo,ucDeadLineDate,ucCardRightType);
	if(ret)
	{
		SetErrMsg(ret,"д��������Ϣʧ��");
		return ret;           //д������Ϣ����
	}
	
	//��ע,��ȱ��д���Ż�ѧ�ŵĽӿ�
	//д�ֿ���������Ϣ
	ret = SMT_WritePersonalInfo(pc->ucName,
								pc->ucDutyNo,
								pc->ucCertificateNo,
								pc->ucDepartmentNo,
								pc->ucIdentifyNo,
								pc->ucSexNo,
								pc->ucCardNo);
	if(ret)
	{
		SetErrMsg(ret,"д������Ϣʧ��");
		return ret;           //
	}
	ret=SMT_WriteLibraryNo(pc->ucLibraryNo);
	if(ret)
	{
		SetErrMsg(ret,"дͼ��֤��ʧ��");
		return ret;
	}
	ret=WriteCardPwd(pc->ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"д������ʧ��");
		return ret;
	}
	//Ԥ����
	
	unsigned short int PacketNo = 1;
	
	int Money;
	Money = pc->Money;
	ret = SMT_PacketSetMoney(PacketNo,Money);
	if(ret)
	{
		SetErrMsg(ret,"����Ǯ�����ʧ��");
		return ret;		
	}
	
	ret = SMT_WriteAreaCode(pc->area_code);
	if (ret)
	{
		SetErrMsg(ret,"����ԺУ����ʧ��");
		return ret;
	}	
	
	ret = SMT_WriteAppendCardInfo(pc->cut_id, pc->certificate_type, pc->people, pc->nationality, pc->open_card_flag, pc->card_version);
	if (ret)
	{
		SetErrMsg(ret,"���ø�����Ϣʧ��");
		return ret;
	}
	
	ret = SMT_WriteRegisterCardFlag(pc->pub_card_flag);
	if (ret)
	{
		SetErrMsg(ret,"���÷���ע���ʶ�ų���");
		return ret;
	}

	ret = SMT_WriteSerRegisterFlag(pc->ser_flag);
	if (ret)
	{
		SetErrMsg(ret,"���÷���ע���ʶ�ų���");
		return ret;
	}

	ret = SMT_WritePwdOpenFlag(pc->pwd_open_flag);
	if (ret)
	{
		SetErrMsg(ret,"�������뿪�س���");
		return ret;
	}

	//SMT_ControlBuzzer();
	return 0;
}

int ifReadyOK()
{
	int ret = 0;
	//����д���Ƿ���Ȩ
	ret = SMT_JudgeAutoFlag();
	if(ret!=1)
	{
		SetErrMsg(ret,"������δ��Ȩ");
		return ret;
	}
	//����û����Ƿ��ڸ�Ӧ��
	char ucSerialNo[9];
	char ucType[3];

	ret = RequestCard(ucSerialNo,ucType);
	if(ret)
	{
		return ret;
	}
	return 0;
}

int __stdcall ReaderAuthor(unsigned char *ucAuthorInfo)
{
	int ret = 0;
	unsigned char ucAuthor[9];
	memset(ucAuthor,0,sizeof(ucAuthor));
	memcpy(ucAuthor,ucAuthorInfo,8);
	//����д����Ȩ
	ret = SMT_AutoDll(ucAuthor);
	if(ret)
	{
		SetErrMsg(ret,"��������Ȩʧ��");
		return ret;
	}
    // ����ȫ�ֱ���workingkey
	SMT_ControlBuzzer();
	return 0;
}

int __stdcall RequestCard(char *ucSerialNo,char *ucType)
{

	int ret = 0;
	unsigned char SerialNo[4],Type[1];
	memset(SerialNo,0,4);
	memset(Type,0,1);

	//����û����Ƿ��ڸ�Ӧ��
	ret = SMT_RequestCardExist(SerialNo,Type);
	if(ret)
	{
		SetErrMsg(ret,"�����ڶ�������Ӧ��");
		return ret;
	}
	sprintf(ucSerialNo,"%02X%02X%02X%02X",
		SerialNo[0],
		SerialNo[1],
		SerialNo[2],
		SerialNo[3]);
	sprintf(ucType,"%02X",Type[0]);
	return 0;
}

// ��������: ��ȡ����״̬��Ϣ, 
// ��������: ����ͬ��
int __stdcall SMT_ReadCardStateInfo(unsigned char ucShowCardNo[5],
								   int nDealCardNo[1],
								   unsigned char ucDeadLineDate[3],
								   unsigned char ucCardRightType[1])
{
	int ret;
	unsigned char ucBuffer[16] = "";

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
#else	
	ret = Login_Card_Keya(1);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
	ret = SMT_ReadBlock(1,0,ucBuffer);
#endif
	if (ret != 0)
		return -6; //����ʧ��
	nDealCardNo[0] = ucBuffer[0] * 256 * 256 + ucBuffer[1] * 256 + ucBuffer[2];
	ucCardRightType[0] = ucBuffer[3];
	memcpy(ucDeadLineDate, ucBuffer + 4, 3);
	memcpy(ucShowCardNo, ucBuffer + 7, 5);
	return 0;
}

int __stdcall ReadCardInfo(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];		//�û���ʹ�ý�ֹ����
	unsigned char ucCardRightType[1];		//Ȩ��λ
	unsigned char phyid[9];
	int iCardNo[1];

	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	MF_ReadSeriesNo(phyid);
	ret = SMT_ReadCardStateInfo(ucBcdShowCardNo,iCardNo,ucDeadLineDate,ucCardRightType);
	if (ret !=0)
	{
		SetErrMsg(ret,"����������Ϣʧ��");
		return ret;    
	}
	bcd2dec(ucBcdShowCardNo,5,pc->ShowCardNo);
	//ת��hex���ڸ�ʽ��ʮ����
	sprintf((char*)pc->DeadLineDate,"20%02d%02d%02d",ucDeadLineDate[0],ucDeadLineDate[1],ucDeadLineDate[2]);
	sprintf((char*)pc->CardNo,"%d",iCardNo[0]);
	pc->CardRightType=ucCardRightType[0];
	ret = SMT_ReadPersonalInfo(pc->ucName,pc->ucDutyNo,pc->ucCertificateNo,pc->ucDepartmentNo,pc->ucIdentifyNo,pc->ucSexNo,pc->ucCardNo);
	if (ret !=0)
	{
		SetErrMsg(ret,"����������Ϣʧ��");
		return ret;     
	}
	ret=SMT_ReadLibraryNo(pc->ucLibraryNo);
	if(ret)
	{
		SetErrMsg(ret,"дͼ��֤��ʧ��");
		return ret;
	}

	ret = SMT_ReadAreaCode(pc->area_code);
	if (ret)
	{
		SetErrMsg(ret,"��ȡԺУ����ʧ��");
		return ret;
	}	
	
	ret = SMT_ReadAppendCardInfo(&(pc->cut_id), pc->certificate_type, pc->people, pc->nationality, pc->open_card_flag, pc->card_version);
	if (ret)
	{
		SetErrMsg(ret,"��ȡ������Ϣʧ��");
		return ret;
	}
	
	ret = SMT_ReadRegisterCardFlag(pc->pub_card_flag);
	if (ret)
	{
		SetErrMsg(ret,"��ȡ����ע���ʶ�ų���");
		return ret;
	}
	
	ret = SMT_ReadSerRegisterFlag(pc->ser_flag);
	if (ret)
	{
		SetErrMsg(ret,"��ȡ����ע���ʶ�ų���");
		return ret;
	}
	
	ret = SMT_ReadPwdOpenFlag(pc->pwd_open_flag);
	if (ret)
	{
		SetErrMsg(ret,"��ȡ���뿪�س���");
		return ret;
	}

	return 0;
}

int __stdcall ReadCardInfo2(TPublishCard2 *pc)
{
	int ret;
	unsigned char ucBuffer[16] = "";
	TPublishCard2 curr_card;
	unsigned char ucDeadLineDate[3] = "";
	int nPacketNo = 1;
	int sector;
	memset(&curr_card,0,sizeof curr_card);

	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
	if (ret != 0)	
		return ret;
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
	if (ret != 0)
		return -6; //����ʧ��
	
	sprintf((char*)curr_card.CardNo,"%d",
		(ucBuffer[0] * 256 * 256 + ucBuffer[1] * 256 + ucBuffer[2]));

	memcpy(ucDeadLineDate,ucBuffer+4,3);
	sprintf((char*)curr_card.DeadLineDate,"20%02d%02d%02d"
		,ucDeadLineDate[0],ucDeadLineDate[1],ucDeadLineDate[2]);
	//memcpy(curr_card.DeadLineDate,ucBuffer + 4, 3);

	memset(ucBuffer,0,sizeof ucBuffer);
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 1, ucBuffer);
	if(ret)
		return -6;
	
	bcd2dec(ucBuffer,3,curr_card.ucPwd);
	
	memset(ucBuffer,0,sizeof ucBuffer);
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
	if (ret != 0)
	{
		return -5;
	}
	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
	{
		return 1; //Ǯ��������ʹ��
	}
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������, �����32���Ժ��ǿ��

	unsigned char ucBuf1[16],ucBuf2[16];
	unsigned char ucCheck;

	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);

	if (ret != 0)
	{
		return -5;
	}
	int i;
	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	{
		curr_card.Money = ucBuf1[0] + ucBuf1[1] * 256 + ucBuf1[2] * 256 * 256;
		ret = 0;
	}
	else
	{
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
		if(ret != 0)
		{
			return -5;
		}
		ucCheck = 0;
		for (i = 0; i < 15; i++)
			ucCheck += ucBuf2[i];
		if (ucCheck == ucBuf2[15])
		{
			curr_card.Money = ucBuf2[0] + ucBuf2[1] * 256 + ucBuf2[2] * 256 * 256;
			ret = 0;
		}
		else
		{
			return  2;
		}
	}
	if(ret)
		return 2;


	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO);
	if (ret != 0)	
		return ret;

	memset(ucBuffer,0,sizeof ucBuffer);
	
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 1, ucBuffer);
	if (ret != 0)
		return -6; //����ʧ��


	memcpy(curr_card.ucCardNo, ucBuffer, 16);

	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 2, ucBuffer);
	if (ret != 0)	
		return -6;
	memcpy(curr_card.ucCardNo + 16, ucBuffer, 4);

	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 3, ucBuffer);
	if (ret != 0 )	
		return -6;
	memcpy(curr_card.ucName, ucBuffer, 8);
	//memcpy(ucDutyNo, ucBuffer + 8, 4);
	memcpy(curr_card.ucCertificateNo, ucBuffer + 12, 4);
	
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 4, ucBuffer);
	if (ret != 0)	
		return -6;
	memcpy(curr_card.ucCertificateNo + 4, ucBuffer, 16);

	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 5, ucBuffer);
	if (ret != 0)	
		return -6;
	memcpy(curr_card.ucDepartmentNo, ucBuffer, 10);
	memcpy(curr_card.ucIdentifyNo, ucBuffer + 10, 4);
	memcpy(curr_card.ucSexNo, ucBuffer + 14, 1);

	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO,6,ucBuffer);
	if (ret != 0)
		return -6;
	memcpy((char*)&(curr_card.cut_id),ucBuffer,4);
	memcpy(pc,&curr_card,sizeof curr_card);
	return 0;
}

//���¿���Ϣ
int __stdcall UpdateCardInfo(TPublishCard *CardInfo)
{
	int ret = 0;
	char card_id[9] = "";
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	unsigned char ucBcdShowCardNo[5];
	char sYear[3];
	char sMon[3];
	char sDay[3];
	
	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	//��ע,��ȱ��д���Ż�ѧ�ŵĽӿ�
	memset(sYear,0,sizeof(sYear));
	memset(sMon,0,sizeof(sMon));
	memset(sDay,0,sizeof(sDay));
	memset(ucBcdShowCardNo,0,sizeof(ucBcdShowCardNo));

	memcpy(sYear,CardInfo->DeadLineDate+2,2);
	memcpy(sMon,CardInfo->DeadLineDate+4,2);
	memcpy(sDay,CardInfo->DeadLineDate+6,2);
	
	ucDeadLineDate[0]=atoi(sYear);
	ucDeadLineDate[1]=atoi(sMon);
	ucDeadLineDate[2]=atoi(sDay);

	ret = SMT_ChangeDeadLineDate(ucDeadLineDate);					//�޸�ʹ�ý�ֹ���ڣ�8���ֽ�����(������)��ʽΪ��"yy-mm-dd"��
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸Ľ�ֹ����ʱ����");
		return ret;
	}
	ucCardRightType[0]=CardInfo->CardRightType;
	ret = SMT_ChangeCardRightType(ucCardRightType);					//�޸�ʹ��Ȩ�����ͣ�1--254��	
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸Ŀ�Ȩ������ʱ����");
		return ret;
	}
	ret = SMT_ChangeName(CardInfo->ucName);							
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸�����ʱ����");
		return ret;	
	}

	ret = SMT_ChangeDutyNo(CardInfo->ucDutyNo);						
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸�ְ�����ʱ����");
		return ret;
	}

	ret = SMT_ChangeCerificateNo(CardInfo->ucCertificateNo);		
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸�֤������ʱ����");
		return ret;	
	}

	ret = SMT_ChangeDepartmentNo(CardInfo->ucDepartmentNo);			
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸Ĳ��Ŵ���ʱ����");
		return ret;
	}

	ret = SMT_ChangeIdentifyNo(CardInfo->ucIdentifyNo);				
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸���ݴ���ʱ����");
		return ret;
	}

	ret = SMT_ChangeSexNo(CardInfo->ucSexNo);						
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸��Ա�ʱ����");
		return ret;
	}

	ret = SMT_ChangeCardNo(CardInfo->ucCardNo);				
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸�ѧ����ʱ����");
		return ret;
	}

	ret = SMT_WriteLibraryNo(CardInfo->ucLibraryNo);	
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸�ͼ��֤��ʱ����");
		return ret;
	}

	ret = strlen((char*)CardInfo->ShowCardNo);
	if( 10==ret )	
	{
		//ת��ΪBCD��
		dec2bcd(CardInfo->ShowCardNo,ucBcdShowCardNo,5);
		ret = SMT_ChangeShowCardNo(ucBcdShowCardNo);	
		if (ret != 0)
		{
			SetErrMsg(ret,"�޸���ʾ����ʱ����");
			return ret;
		}
	}
	
	memcpy(card_id, CardInfo->CardNo, sizeof(card_id) - 1);
	
	ret = SMT_ChangeDealCardNo(atoi(card_id));
	if (ret)
	{
		SetErrMsg(ret,"�޸Ľ��׿��Ŵ���");
		return ret;
	}
	
	ret = WriteCardPwd(CardInfo->ucPwd);
	if (ret)
	{
		SetErrMsg(ret,"д������ʧ��");
		return ret;
	}

	ret = SMT_WriteAreaCode(CardInfo->area_code);
	if (ret)
	{
		SetErrMsg(ret,"�޸�ԺУ����ʧ��");
		return ret;
	}	
	
	ret = SMT_WriteAppendCardInfo(CardInfo->cut_id, CardInfo->certificate_type, CardInfo->people, CardInfo->nationality, CardInfo->open_card_flag, CardInfo->card_version);
	if (ret)
	{
		SetErrMsg(ret,"�޸ĸ�����Ϣʧ��");
		return ret;
	}
	
	ret = SMT_WriteRegisterCardFlag(CardInfo->pub_card_flag);
	if (ret)
	{
		SetErrMsg(ret,"�޸ķ���ע���ʶ�ų���");
		return ret;
	}
	
	ret = SMT_WriteSerRegisterFlag(CardInfo->ser_flag);
	if (ret)
	{
		SetErrMsg(ret,"�޸ķ���ע���ʶ�ų���");
		return ret;
	}
	
	ret = SMT_WritePwdOpenFlag(CardInfo->pwd_open_flag);
	if (ret)
	{
		SetErrMsg(ret,"�޸����뿪�س���");
		return ret;
	}

	return 0;
}

int __stdcall ReadPacketInfo( LPLOOPPURSEINFO LoopPurseInfo )
{
	int ret = 0; 

	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	int nPacketNo = 1;
	
	//��ǰ�����ڴ淢�������ԭ����û��#pragma pack(1)
	memset(LoopPurseInfo,0,sizeof(LOOPPURSEINFO));  
	

	ret = SMT_ReadPacketInfo(nPacketNo,LoopPurseInfo);
	if (ret !=0)
	{
		SetErrMsg(ret,"������Ϣʧ��");
		return ret;
	}
	return ret;
}


int __stdcall ReadCardNO(int nCardNo[1])
{
	int ret;
	unsigned char ucBuffer[16];
	MF_ReadSeriesNo(ucBuffer);
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(1);
#endif
	if(ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
	ret = SMT_ReadBlock(1, 0, ucBuffer);
#endif
	if(ret != 0)	
		return ret;
	
	nCardNo[0] = ucBuffer[0] * 256 * 256 + ucBuffer[1] * 256 + ucBuffer[2];
	return 0;
}

int __stdcall WriteCardPwd(unsigned char pwd[6])
{
	int ret=0;
	unsigned char ucPwd[3];
	dec2bcd(pwd,ucPwd,3);
	ret=SMT_WritePersonalPassword(ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"д������ʧ��");
		return ret;
	}
	return 0;
}

int __stdcall ReadCardPwd(unsigned char pwd[6])
{
	int ret=0;
	unsigned char ucPwd[3];
	ret=SMT_ReadPersonalPassword(ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"��������ʧ��");
		return ret;
	}
	bcd2dec(ucPwd,3,pwd);
	return 0;
}

int __stdcall Load_Dll()
{
	if (NULL == hDLL)
	{
		hDLL = LoadLibrary(bufSmartCom);
		if (!hDLL)
		{
			return -1;
		}
		
		SMT_ConnectMF280		 = (LPSMT_ConnectMF280)GetProcAddress(hDLL,"SMT_ConnectMF280");
		SMT_ControlBuzzer        = (LPSMT_ControlBuzzer)GetProcAddress(hDLL,"SMT_ControlBuzzer");
		SMT_CloseMF280           = (LPSMT_CloseMF280)GetProcAddress(hDLL,"SMT_CloseMF280");
		SMT_RequestCardExist  	 = (LPSMT_RequestCardExist)GetProcAddress(hDLL,"SMT_RequestCardExist");
		SMT_SleepCard            = (LPSMT_SleepCard)GetProcAddress(hDLL,"SMT_SleepCard");
		MF_ReadSeriesNo          = (LPMF_ReadSeriesNo)GetProcAddress(hDLL, "MF_ReadSeriesNo");
		SMT_Login_With_UserKey   = (LPSMT_Login_With_UserKey)GetProcAddress(hDLL, "SMT_Login_With_UserKey");
		SMT_WriteBlock           = (LPSMT_WriteBlock)GetProcAddress(hDLL, "SMT_WriteBlock");
		SMT_ReadBlock            = (LPSMT_ReadBlock)GetProcAddress(hDLL, "SMT_ReadBlock");
		SetLastErrMsg            = (LPSetLastErrMsg)GetProcAddress(hDLL, "SetLastErrMsg");
		GetMFLastErr             = (LPGetMFLastErr)GetProcAddress(hDLL, "GetMFLastErr");
		if ((!SMT_ConnectMF280) ||
			(!SMT_ControlBuzzer) ||
			(!SMT_CloseMF280) ||
			(!SMT_WriteBlock)  ||
			(!SMT_ReadBlock)   ||
			(!MF_ReadSeriesNo) ||
			(!SMT_RequestCardExist) ||
			(!SMT_Login_With_UserKey) ||
			(!SMT_SleepCard)||
			(!SetLastErrMsg)||
			(!GetMFLastErr) 
			)
		{
			FreeLibrary(hDLL);
			hDLL = NULL;
			return -2;
		}
		SMT_GetHandle=(LPSMT_GetHandle)GetProcAddress(hDLL,"SMT_GetHandle");
	}
		
	if (NULL == hDesDLL)
	{
		// ����dessdll.dll��
		hDesDLL = LoadLibrary(bufDesdll);
		if (!hDesDLL)
		{
			return -1;
		}
		gen_user_card_keyA = (lpgen_user_card_keyA)GetProcAddress(hDesDLL,"gen_user_card_keyA");
		gen_user_card_keyB = (lpgen_user_card_keyB)GetProcAddress(hDesDLL,"gen_user_card_keyB");
		encrypt_work_key   = (lpencrypt_work_key)GetProcAddress(hDesDLL, "encrypt_work_key");
		gen_auth_card_keyA = (lpgen_auth_card_keyA)GetProcAddress(hDesDLL,"gen_auth_card_keyA");
		gen_auth_card_keyB = (lpgen_auth_card_keyB)GetProcAddress(hDesDLL,"gen_auth_card_keyB");
		decrypt_work_key   = (lpdecrypt_work_key)GetProcAddress(hDesDLL,"decrypt_work_key");
		get_check_char	   = (lpget_check_char)GetProcAddress(hDesDLL,"get_check_char");
		gen_card_ming_des  = (lpgen_card_ming_des)GetProcAddress(hDesDLL, "gen_card_ming_des");
		encrypt_elec_card_pwd = (lpencrypt_elec_card_pwd)GetProcAddress(hDesDLL,"encrypt_elec_card_pwd");
		decrypt_elec_card_pwd = (lpdecrypt_elec_card_pwd)GetProcAddress(hDesDLL,"decrypt_elec_card_pwd");
		if ((!gen_user_card_keyA) || 
			(!gen_user_card_keyB) ||
			(!encrypt_work_key)   ||
			(!gen_auth_card_keyA) ||
			(!gen_auth_card_keyB) ||
			(!decrypt_work_key)	  ||	
			(!get_check_char)     ||
			(!gen_card_ming_des)  ||
			(!encrypt_elec_card_pwd)||
			(!decrypt_elec_card_pwd)
			)
		{
			FreeLibrary(hDesDLL);
			hDesDLL = NULL;
			return -2;
		}
	}

	if (NULL == hJdcDLL)
	{
		// ����JDyktCustomerCardDLL.dll��, ���ݴ�ѧ��ˮ��ת��ר������
		hJdcDLL = LoadLibrary(bufJdcdll);
		if (!hJdcDLL)
		{
			return -1;
		}
		EncodeData = (LPEncodeData)GetProcAddress(hJdcDLL, "EncodeData");
		DecodeData = (LPDecodeData)GetProcAddress(hJdcDLL, "DecodeData");
		if (
			(!EncodeData) || 
			(!DecodeData)
			)
		{
			FreeLibrary(hJdcDLL);
			hJdcDLL = NULL;
			return -2;
		}
	}
	if(NULL == hXTDLL)
	{
		hXTDLL = LoadLibrary("XT_mf1dll.dll");
		if(!hXTDLL)
			return -1;
		CardToUserData = (LPCardToUserData)GetProcAddress(hXTDLL,"CardToUserData");
		UserDataToCard = (LPUserDataToCard)GetProcAddress(hXTDLL,"UserDataToCard");
		if(!CardToUserData
			|| !UserDataToCard)
		{
			FreeLibrary(hXTDLL);
			hXTDLL = NULL;
			return -2;
		}

	}
	memset(g_init_sect_map,0,sizeof g_init_sect_map);
	return 0;
}
/************************************************************************/
/*           ����ӵĺ����� �������ܺ���, ��Դ��SMARTCOM411DXQ          */
/************************************************************************/

// ascWorkKey����������Կ
// ��������: ������֤ 
// �����´�½���������豸, ���Ų���
int  _stdcall Load_WorkKey(char *ascWorkKey)
{
	//����������Կ
	int ret=0;
	int i=0;
	unsigned char ucCryptWorkKey[17];
	memset(SMT_UCWORKINGKEY, 0, sizeof(SMT_UCWORKINGKEY));
	hex2dec(ascWorkKey, ucCryptWorkKey, 8);
	encrypt_work_key(ucCryptWorkKey, SMT_UCWORKINGKEY);
	nAutoFlag = 1;
	return 0;
}

// ��������: �жϱ�־
// ��������: ��
int __stdcall SMT_JudgeAutoFlag()
//����ֵ��     0��δ��Ȩ     1����Ȩ
{
	return nAutoFlag;
}

// ��������: ������֤
// ��������: uckWorkingKey������Կ 
int __stdcall SMT_AutoDll(unsigned char *ucWorkingKey)
{
	int i;
	memcpy(SMT_UCWORKINGKEY, ucWorkingKey, 8);
	for(i=0;i<8;i++)
		SMT_UCWORKINGKEY[i+8] = ~ucWorkingKey[i];
	has_read_main_key = TRUE;
	nAutoFlag = 1;
	return 0;
}

// ��������: ��ȡ���к�
// ��������: ���к�����
int __stdcall ReadSerial(unsigned char *serial)
{
	return MF_ReadSeriesNo(serial);
}

// ��������: �����㿨
// ��������: bPersonalFlag(������Ϣ��־), bStateFlag(״̬��־), bBankInfo(�洢��Ϣ), bPacketFlag(����־)
int __stdcall SMT_CreateGreyCard(BOOL bPersonalFlag,BOOL bStateFlag, BOOL bBankInfo,BOOL bPacketFlag[8])
{
	unsigned char ucSerialNo[5];
	unsigned char ucKeyA[6],ucKeyB[6];
	unsigned char ucRawData[256],ucTmpRawData[16],ucDesData[256];
	
	int i,j,startSector=4;
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret <= 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	//1��ʹ�ó��������½��Ƭ  ǰ32������
	memset(ucKeyA,0xFF,6);
	memset(ucKeyB,0xFF,6);
	memset(ucRawData,0x00,16);
	for(i=0;i<32;i++)
	{
		ret = SMT_Login_With_UserKey(i,ucKeyA,0);
		if(ret != 0)
			return -2; //�ǳ�����
//		ret = SMT_Login_With_UserKey(i,ucKeyB,1);
//		if(ret != 0)
//			return -3; //�ǳ�����
		for(j=0;j<3;j++)
		{
			if(i==0&&j==0)
				continue;
			ret=SMT_WriteBlock(i,j,ucRawData);
			if(ret)
				return -4;
		}
	}
	//2������KEYA��KEYB����Ǯ������
	//1 --- ����KEYA
	//////////////////////////////////////////////////////
	SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	//����KEYB
	//////////////////////////////////////////////////////
	SMT_Cal_KeyB(SMT_UCWORKINGKEY, ucSerialNo, ucKeyB);
	///////////////////////////////////////////////////////
	memcpy(ucRawData,ucKeyA,6);
	ucRawData[6] = 0x7F;
	ucRawData[7] = 0x07;
	ucRawData[8] = 0x88;
	ucRawData[9] = 0x00;
	memcpy(ucRawData+10,ucKeyB,6);
	memset(ucDesData,0xFF,6);
	for(i=0;i<32;i++)
	{
		ret = SMT_Login_With_UserKey(i,ucDesData,0);
		if(ret != 0)
			return -5; //�ǳ�����
		memcpy(ucTmpRawData,ucRawData,16);
		ret = SMT_WriteBlock(i,3,ucTmpRawData);
		if(ret != 0)
			return -6; //��Ƭ����ʧ��
		ret = SMT_Login_With_UserKey(i,ucKeyA,0);
		if(ret)
			return -11;
	}
	//����Ǯ���� ��0��
	j = 0;
	for(i=0;i<8;i++)
	{
		if(bPacketFlag[i] == TRUE)
			ucRawData[j] = 0x00;
		else
			ucRawData[j] = 0xFF;
		j = j + 1;
		if(bPacketFlag[i] == TRUE)
		{
			ucRawData[j] = startSector;
			startSector+=1;
		}
		else
			ucRawData[j] = 0xFF;
		j=j+1;
	}
	//1 ʹ���û������½
	ret = SMT_Login_With_UserKey(3,ucKeyA,0);
	if(ret != 0)
		return -7;//ʹ���û�����KEYA���ܵ�½
	ret = SMT_WriteBlock(3,0,ucRawData);
	if(ret != 0)
		return -8;//�޷�д��
	memset(ucRawData,0xFF,16);
	for(i=0;i<8;i++)
	{
		if(bPacketFlag[i] == TRUE)
		{
			ucRawData[i] = startSector;
			startSector += 1;
		}
		else
			ucRawData[i] = 0xFF;
	}
	ret = SMT_WriteBlock(3,1,ucRawData);
	if(ret != 0)
		return -9;//�޷�д��
	memset(ucRawData,0xFF,16);  //20050305����
	ret = SMT_WriteBlock(3,2,ucRawData);
	if(ret != 0)
		return -10;//�޷�д��
	return 0;
}

// ��������: д�뿨��״̬��Ϣ 
// ��������: ucShowCardNo(�û���ʾ����), nDealCardNo(�û����׿���), 
// ucDeadLineDate(���Ľ�ֹ����), ucCardRightType(�û���ʹ������Ȩ��)
int __stdcall SMT_WriteCardStateInfo(unsigned char ucShowCardNo[5], 
						   int nDealCardNo[1], 
						   unsigned char ucDeadLineDate[3], 
						   unsigned char ucCardRightType[1])
{
	unsigned char ucSerialNo[5],ucRawData[256],ucKeyA[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	
#ifdef GZ_UNIVERSITY_TOWN
	//1 --- ����KEYB
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	//1 --- ����KEYA
	SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	ret = SMT_Login_With_UserKey(1, ucKeyA, 0);
#endif	
	if(ret != 0)
		return -2;//��Ƭ��½ʧ��
	//��0��������֯
	if(nDealCardNo[0] > 0x0FFFFF)
		return -3;//���׿��Ź���
	memset(ucRawData,0xFF,16);
	ucRawData[0] = nDealCardNo[0] / 256 / 256;
	ucRawData[1] = nDealCardNo[0] / 256;
	ucRawData[2] = nDealCardNo[0] % 256;
	ucRawData[3] = ucCardRightType[0];
	memcpy(ucRawData + 4, ucDeadLineDate, 3);
	memcpy(ucRawData + 7, ucShowCardNo, 5);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucRawData);		// 37�ȿ�0
#else
	ret = SMT_WriteBlock(1, 0, ucRawData);
#endif
	if(ret != 0)
		return -5; //д��ʧ��
	return 0;				
}

/*================================================================ 
* ��������    SMT_ReadShowCardNo
* ������      [out] (unsigned char ucShowCardNo[5])	��ʾ����
* ��������:   ��ȡ��ʾ����: 
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/ 
int __stdcall SMT_ReadShowCardNo(unsigned char ucShowCardNo[5])
{
	int ret;
	unsigned char ucBuffer[16];
	
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);	
#else
	ret = Login_Card_Keya(1);
#endif
	if(ret != 0)	
		return ret;
	
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
	ret = SMT_ReadBlock(1, 0, ucBuffer);
#endif
	if(ret != 0)
		return -6; //����ʧ��

	memcpy(ucShowCardNo, ucBuffer + 7, 5);
	return 0;
}

// ��������: �޸��û�����
// ��������: �û����� 
int __stdcall SMT_ChangeShowCardNo(unsigned char ucShowCardNo[5])
{
	int ret;
	unsigned char ucBuffer[16];

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);	
#else
	ret = Login_Card_Keya(1);
#endif
	if(ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
	ret = SMT_ReadBlock(1, 0, ucBuffer);
#endif
	if(ret != 0)
		return -6; //����ʧ��
	memcpy(ucBuffer + 7, ucShowCardNo, 5);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
	ret = SMT_WriteBlock(1, 0, ucBuffer);
#endif
	if(ret != 0)
		return -5; //д��ʧ��
	return 0;
}

// ��������: �޸Ľ��׿���
// ��������: ���׿���
int __stdcall SMT_ChangeDealCardNo(int nDealCardNo)
{
	int ret;
	unsigned char ucBuffer[16];

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);	
#else
	ret = Login_Card_Keya(1);
#endif
	if (ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
	ret = SMT_ReadBlock(1, 0, ucBuffer);
#endif
	if (ret != 0)
		return -6; //����ʧ��
	
	ucBuffer[0] = nDealCardNo / 256 / 256;
	ucBuffer[1] = nDealCardNo / 256;
	ucBuffer[2] = nDealCardNo % 256;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
	ret = SMT_WriteBlock(1, 0, ucBuffer);
#endif
	if (ret != 0)
		return -5; //д��ʧ��
	return 0;
}

// ��������: �޸Ŀ�Ƭʹ�ý�������
// ��������: ��ֹ����ʱ��
int __stdcall SMT_ChangeDeadLineDate(unsigned char ucDeadLineDate[3])
{
	int ret;
	unsigned char ucBuffer[16];

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(1);
#endif
	if(ret != 0)	
		return ret;
																
#ifdef GZ_UNIVERSITY_TOWN									
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 6, ucBuffer);			// 36������6��
#else
	ret = SMT_ReadBlock(1, 0, ucBuffer);
#endif
	if(ret != 0)
		return -6; //����ʧ��

memcpy(ucBuffer + 7, ucDeadLineDate, 3);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 6, ucBuffer);
#else
	ret = SMT_WriteBlock(1, 0, ucBuffer);
#endif
	if (ret != 0)
		return -5; //д��ʧ��

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);				// 37������0��
#else
//	ret = Login_Card_Keya(1);
	ret = 0;
#endif
	if(ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
//	ret = SMT_ReadBlock(1, 0, ucBuffer);
	ret = 0;
#endif
	if(ret != 0)
		return -6; //����ʧ��
	memcpy(ucBuffer + 4, ucDeadLineDate, 3);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
//	ret = SMT_WriteBlock(1, 0, ucBuffer);
	ret = 0;
#endif
	if (ret != 0)
		return -5; //д��ʧ��
	return 0;
}

// ��������: �޸Ŀ�ƬȨ������
// ��������: ��ƬȨ������
int __stdcall SMT_ChangeCardRightType (unsigned char ucCardRightType[1])
{
	int ret;
	unsigned char ucBuffer[16];

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(1);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
	ret = SMT_ReadBlock(1, 0, ucBuffer);
#endif
	if (ret != 0)
		return -6; //����ʧ��
	memcpy(ucBuffer + 3, ucCardRightType, 1);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucBuffer);
#else
	ret = SMT_WriteBlock(1, 0, ucBuffer);
#endif
	if(ret != 0)
		return -5; //д��ʧ��
	return 0;
}

// �������ã�д�뿨Ƭ������Ϣ
// ��������: ucName(����), ucDutyNo(ְ�����), ucCertificateNo(֤������)
// ucDepartmentNo(���ű��), ucIdentifyNo(��ݴ���), ucSexNo(�Ա�), ucCardNo(����)
int __stdcall SMT_WritePersonalInfo(unsigned char ucName[8],
									unsigned char ucDutyNo[4],
									unsigned char ucCertificateNo[20],
									unsigned char ucDepartmentNo[10],
									unsigned char ucIdentifyNo[4],
									unsigned char ucSexNo[1],
									unsigned char ucCardNo[20])
{
	int ret;
	unsigned char ucBuffer[16];
	//����ѧ�Ų���
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(0);
#endif
	if (ret != 0)	
		return ret;
	memcpy(ucBuffer, ucCardNo, 16);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 1, ucBuffer);
#else
	ret = SMT_WriteBlock(0,1,ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	memset(ucBuffer, 0xFF, 16);
	memcpy(ucBuffer, ucCardNo + 16, 4);

#ifdef GZ_UNIVERSITY_TOWN 
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 2, ucBuffer);
#else
	ret = SMT_WriteBlock(0, 2, ucBuffer);
#endif	
	if (ret != 0)	
		return -5;
	//��2����0�����
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(2);
#endif
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer, ucName, 8);
	memcpy(ucBuffer + 8, ucDutyNo, 4);
	memcpy(ucBuffer + 12, ucCertificateNo, 4);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 3, ucBuffer);
#else
	ret = SMT_WriteBlock(2, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	memcpy(ucBuffer, ucCertificateNo + 4, 16);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 4, ucBuffer);
#else
	ret = SMT_WriteBlock(2, 1, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	memcpy(ucBuffer, ucDepartmentNo, 10);
	memcpy(ucBuffer + 10, ucIdentifyNo, 4);
	memcpy(ucBuffer + 14, ucSexNo, 1);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 5, ucBuffer);
#else
	ret = SMT_WriteBlock(2, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	return 0;
}

// ��������: ��ȡ��Ƭ������Ϣ
// ��������: ������ʾ
int __stdcall SMT_ReadPersonalInfo(unsigned char ucName[8],
								   unsigned char ucDutyNo[4],
								   unsigned char ucCertificateNo[20],
								   unsigned char ucDepartmentNo[10],
								   unsigned char ucIdentifyNo[4],
								   unsigned char ucSexNo[1],
								   unsigned char ucCardNo[20])
{
	int ret;
	unsigned char ucBuffer[16];
	//����ѧ�Ų���
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(0);
#endif	
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 1, ucBuffer);
#else
	ret = SMT_ReadBlock(0, 1, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memcpy(ucCardNo, ucBuffer, 16);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 2, ucBuffer);
#else
	ret = SMT_ReadBlock(0, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memcpy(ucCardNo + 16, ucBuffer, 4);

#ifdef GZ_UNIVERSITY_TOWN
//	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO);
	ret = 0;
#else
	ret = Login_Card_Keya(2);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(2, 0, ucBuffer);
#endif
	if (ret != 0 )	
		return -6;
	memcpy(ucName, ucBuffer, 8);
	memcpy(ucDutyNo, ucBuffer + 8, 4);
	memcpy(ucCertificateNo, ucBuffer + 12, 4);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 4, ucBuffer);
#else
	ret = SMT_ReadBlock(2, 1, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memcpy(ucCertificateNo + 4, ucBuffer, 16);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 5, ucBuffer);
#else
	ret = SMT_ReadBlock(2, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memcpy(ucDepartmentNo, ucBuffer, 10);
	memcpy(ucIdentifyNo, ucBuffer + 10, 4);
	memcpy(ucSexNo, ucBuffer + 14, 1);
	return 0;
}

// ��������: �޸��û�����
// ��������: �û���
int __stdcall SMT_ChangeName(unsigned char ucName[8])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(2);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(2, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memcpy(ucBuffer, ucName, 8);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 3, ucBuffer);
#else
	ret = SMT_WriteBlock(2, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	return 0;
}

// ��������: �޸�ְ�����
// ��������: ְ����
int __stdcall SMT_ChangeDutyNo(unsigned char ucDutyNo[4])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(2);
#endif
	if(ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(2, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memcpy(ucBuffer + 8, ucDutyNo, 4);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 3, ucBuffer);
#else
	ret = SMT_WriteBlock(2, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	return 0;
}

// �������ã��޸�֤������
// ��������: ֤����
int __stdcall SMT_ChangeCerificateNo (unsigned char ucCertificateNo[20])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(2);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(2, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memcpy(ucBuffer + 12, ucCertificateNo, 4);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 3, ucBuffer);
#else
	ret = SMT_WriteBlock(2, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	memcpy(ucBuffer, ucCertificateNo + 4, 16);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 4, ucBuffer);
#else
	ret = SMT_WriteBlock(2, 1, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	return 0;
}

// ��������: �޸Ĳ��ű��
// ��������: ���ű��
int __stdcall SMT_ChangeDepartmentNo(unsigned char ucDepartmentNo[10])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(2);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 5, ucBuffer);
#else
	ret = SMT_ReadBlock(2, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memcpy(ucBuffer, ucDepartmentNo, 10);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 5, ucBuffer);
#else
	ret = SMT_WriteBlock(2, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	return 0;
}

// ��������: �޸���ݴ���
// ��������: ��ݴ���
int __stdcall SMT_ChangeIdentifyNo (unsigned char ucIdentifyNo[4])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(2);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 5, ucBuffer);
#else
	ret = SMT_ReadBlock(2, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memcpy(ucBuffer + 10, ucIdentifyNo, 4);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 5, ucBuffer);
#else
	ret = SMT_WriteBlock(2, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	return 0;
}

// ��������: �޸��Ա����
// ��������: �Ա����
int __stdcall SMT_ChangeSexNo (unsigned char ucSexNo[1])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(2);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 5, ucBuffer);
#else
	ret = SMT_ReadBlock(2, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memcpy(ucBuffer + 14, ucSexNo, 1);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 5, ucBuffer);
#else
	ret = SMT_WriteBlock(2, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	return 0;
}

// ��������: �޸�(ѧ����)
// ��������: ѧ����
int __stdcall SMT_ChangeCardNo(unsigned char ucCardNo[20])
{
	int ret;
	unsigned char ucBuffer[16];
	//����ѧ�Ų���
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = Login_Card_Keya(0);
#endif	
	if (ret != 0)	
		return ret;
	memcpy(ucBuffer, ucCardNo, 16);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 1, ucBuffer);
#else
	ret = SMT_WriteBlock(0, 1, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	memset(ucBuffer, 0xFF, 16);
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO,2,ucBuffer);
	if(ret != 0)
		return -7;
	memcpy(ucBuffer, ucCardNo + 16, 4);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 2, ucBuffer);
#else
	ret = SMT_WriteBlock(0, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	return 0;
}

// ��������: д���������
// ��������: ��������
int __stdcall SMT_WritePersonalPassword(unsigned char PersonalPsd[3])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(1);
#endif	
	if(ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 1,ucBuffer);
#else
	ret = SMT_ReadBlock(1, 1, ucBuffer);
#endif
	if (ret != 0)	
		return ret;
	memcpy(ucBuffer, PersonalPsd, 3);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 1, ucBuffer);
#else
	ret = SMT_WriteBlock(1, 1, ucBuffer);
#endif
	if (ret != 0)	
		return ret;
	return 0;
}

// ��������: ��ȡ��������
// ��������: ��������(3λ)
int __stdcall SMT_ReadPersonalPassword(unsigned char PersonalPsd[3])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(1);
#endif		
	if(ret != 0)	
		return ret;
	//memset(ucBuffer,0xFF,16);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 1,ucBuffer);
#else
	ret = SMT_ReadBlock(1,1,ucBuffer);
#endif
	if(ret != 0)	
		return -5;
	memcpy(PersonalPsd, ucBuffer, 3);
	return 0;
}

/*================================================================ 
* ��������    SMT_WritePwdOpenFlag
* ������      [in] (BYTE open_flag[2])���뿪�ر�־	
* ��������:   д�����뿪�ر�־
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_WritePwdOpenFlag(BYTE open_flag[2])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = 0;
#endif	
	if(ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 1,ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;
//	ucBuffer[3] = open_flag;
	memcpy(ucBuffer + 3, open_flag, 1);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 1, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;
	return 0;
}

/*================================================================ 
* ��������    SMT_ReadPwdOpenFlag
* ������      [out] (BYTE open_flag[2])��ȡ���뿪�ر�־	
* ��������:   ��ȡ���뿪�ر�־
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_ReadPwdOpenFlag(BYTE open_flag[2])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = 0;
#endif	
	if(ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 1,ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;
	
//	*open_flag = ucBuffer[3];
	memcpy(open_flag, ucBuffer + 3, 1);

	return 0;
}

// ��������: дͼ��֤��
// ��������: ͼ��֤��
int __stdcall SMT_WriteLibraryNo(unsigned char ucLibraryNo[13])
{
#ifdef GZ_UNIVERSITY_TOWN
	NULL;
#else
	int ret;
	unsigned char ucBuffer[16];	
	ret = Login_Card_Keya(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1,1,ucBuffer);
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer+3,ucLibraryNo,13);
	ret = SMT_WriteBlock(1,1,ucBuffer);
	if (ret != 0)	
		return ret;
#endif
	return 0;
}

// ��������: ��ͼ��֤��
// ��������: ͼ��֤��
int __stdcall SMT_ReadLibraryNo(unsigned char ucLibraryNo[13])
{
#ifdef GZ_UNIVERSITY_TOWN
	NULL;
#else
	int ret;
	unsigned char ucBuffer[16];
	
	ret = Login_Card_Keya(1);
	if(ret != 0)	
		return ret;
	//memset(ucBuffer,0xFF,16);
	ret = SMT_ReadBlock(1,1,ucBuffer);
	if(ret != 0)	
		return -5;
	memcpy(ucLibraryNo,ucBuffer+3,13);
#endif
	return 0;
}

// ��������: д���п���
// ��������: ���п���
int __stdcall SMT_WriteBankCardNo(unsigned char ucBankCardNo[10])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(1);
#endif	
	if (ret != 0)	
		return ret;
	memset(ucBuffer, 0xFF, 16);
	memcpy(ucBuffer, ucBankCardNo, 10);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 2, ucBuffer);
#else
	ret = SMT_WriteBlock(1, 2, ucBuffer);
#endif	
	if (ret != 0)	
		return -5;
	return 0;
}

// ��������: �����п���
// ��������: ���п���
int __stdcall SMT_ReadBankCardNo(unsigned char  ucBankCardNo[10])
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(1);
#endif
	if (ret != 0)	
		return ret;
	memset(ucBuffer, 0xFF, 16);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 2, ucBuffer);	
#else
	ret = SMT_ReadBlock(1, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	memcpy(ucBankCardNo, ucBuffer, 10);
	return 0;
}

// ��������: ��Ǯ����Ϣ
// ��������: nPacketNo(Ǯ����), LoopPurseInfo(����Ǯ����Ϣ)
int __stdcall SMT_ReadPacketInfo(int nPacketNo, LOOPPURSEINFO *LoopPurseInfo)   
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if(nPacketNo<1)
		return -1;
	MF_ReadSeriesNo(ucBuffer);
	//g_cardlogger<<"read SMT_ReadPacketInfo"<<std::endl;
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
	{
//		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:��¼3����ʧ��",__FILE__,__LINE__,ret);
		return ret;
	}
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3,0,ucBuffer);
#endif
	if (ret != 0)
	{
//		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:��3����ʧ��",__FILE__,__LINE__,ret);	
		return -5;
	}
	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
	{
//		SetLastErrMsg(1,"File:%s\nLine:%d\nError:%d\nMessage:Ǯ��%dδ��ͨ",__FILE__,__LINE__,ret,nPacketNo);	
		return 1; //Ǯ��������ʹ��
	}
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������, �����32���Ժ��ǿ��

#ifdef GZ_UNIVERSITY_TOWN
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif
	if (ret != 0)
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:��½��%d����ʧ��",__FILE__,__LINE__,ret,sector);	
		return ret;
	}

	unsigned char ucBuf1[16],ucBuf2[16];
	unsigned char ucCheck;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
	ret = SMT_ReadBlock(sector, 0, ucBuf1);
#endif
	if (ret != 0)
	{
//		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:����%d����ʧ��",__FILE__,__LINE__,ret,sector);	
		return -5;
	}
	int i;
	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	{
		LoopPurseInfo->RemainMoney = ucBuf1[0] + ucBuf1[1] * 256 + ucBuf1[2] * 256 * 256;
		LoopPurseInfo->DealTimes   = ucBuf1[3] * 256 + ucBuf1[4];
		LoopPurseInfo->DealYear    = ucBuf1[5];
		LoopPurseInfo->DealMonth   = ucBuf1[6];
		LoopPurseInfo->DealDay     = ucBuf1[7];
		LoopPurseInfo->DealHour    = ucBuf1[8];
		LoopPurseInfo->DealMin     = ucBuf1[9];
		LoopPurseInfo->DealTimes_CurTime = ucBuf1[0x0D];
		LoopPurseInfo->DealTimes_CurDay  = ucBuf1[0X0E];
		//g_cardlogger<<"read SMT_ReadPacketInfo success"<<std::endl;
		return 0;
	}
	else
	{
//		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:����%d����У��ʹ���,��ʼ����������",__FILE__,__LINE__,0,sector);	
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
#else
	ret = SMT_ReadBlock(sector, 2, ucBuf2);
#endif
		if(ret != 0)
		{
//			SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:����%d����ʧ��",__FILE__,__LINE__,ret,sector);	
			return -5;
		}
		ucCheck = 0;
		for (i = 0; i < 15; i++)
			ucCheck += ucBuf2[i];
		if (ucCheck == ucBuf2[15])
		{
			LoopPurseInfo->RemainMoney = ucBuf2[0] + ucBuf2[1] * 256 + ucBuf2[2] * 256 * 256;
			LoopPurseInfo->DealTimes   = ucBuf2[3] * 256 + ucBuf2[4];
			LoopPurseInfo->DealYear    = ucBuf2[5];
			LoopPurseInfo->DealMonth   = ucBuf2[6];
			LoopPurseInfo->DealDay     = ucBuf2[7];
			LoopPurseInfo->DealHour    = ucBuf2[8];
			LoopPurseInfo->DealMin     = ucBuf2[9];
			LoopPurseInfo->DealTimes_CurTime = ucBuf2[0x0D];
			LoopPurseInfo->DealTimes_CurDay  = ucBuf2[0X0E];
			g_cardlogger<<"read SMT_ReadPacketInfo success"<<std::endl;
			return 0;
		}
		else
		{
//			SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:����%d�������ݿ�У��ʹ���",__FILE__,__LINE__,ret,sector);	
			return 2;
		}
	}
	return 2;
}

// ��������: Ǯ������Ǯ
// ��������: nPacketNo(Ǯ����), nMoney(Ǯ����)��
// ˵��: ��������б䶯, ��ʱ���滻��Ϊ��API����ʽ
int __stdcall SMT_PacketAddMomey(int nPacketNo,int nMoney)
{
	int ret,sector;
	if (nPacketNo < 1)
		return -1;
	if (nMoney < 0)
		return -1;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif	
	if (ret != 0)	
		return -5;
	
	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
		return 1; //Ǯ��������ʹ��
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������, 32���Ժ��Ӧ���
#ifdef GZ_UNIVERSITY_TOWN
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif	
	if(ret != 0)
		return ret;
	unsigned char ucBuf1[16],ucBuf2[16],ucBufTmp[16];
	unsigned char ucCheck;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
	ret = SMT_ReadBlock(sector, 0, ucBuf1);
#endif
	if(ret != 0)	
		return -6;
	int i;
	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck +=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp,ucBuf1,sizeof(ucBufTmp));
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBufTmp);
#else
		ret = SMT_WriteBlock(sector, 2, ucBufTmp);
#endif
		if(ret != 0)	
			return -8;
		i = ucBuf1[0]+ucBuf1[1]*256+ucBuf1[2]*256*256;
		i = i + nMoney;
		ucBuf1[0] = i%256;
		ucBuf1[1] = i/256;
		ucBuf1[2] = i/256/256;
		i = ucBuf1[3]*256+ucBuf1[4];
		i = i + 1;
		ucBuf1[3] = i/256;
		ucBuf1[4] = i%256;
		SYSTEMTIME tm;
		GetLocalTime(&tm);
//		CTime tm = CTime::GetCurrentTime();                               �����޸Ĺ�
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf1[7])                                   // (tm.GetDay()!=ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
		ucBuf1[7] = (BYTE)tm.wDay;				// tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;				// tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
		ucBuf1[15]=0;	
		for (i = 0; i < 15; i++)	
			ucBuf1[15] += ucBuf1[i];

#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf1);
#endif	
		if (ret != 0)	
			return -8;
		return 0;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
#else
		ret = SMT_ReadBlock(sector, 2, ucBuf2);
#endif
		if (ret != 0)	
			return -9;
		ucCheck = 0;
		for (i = 0; i < 15; i++)	
			ucCheck += ucBuf2[i];
		if (ucCheck != ucBuf2[15])	
			return 2;
		i = ucBuf2[0] + ucBuf2[1] * 256 + ucBuf2[2] * 256 * 256;
		i = i + nMoney;
		ucBuf2[0] = i % 256;
		ucBuf2[1] = i / 256;
		ucBuf2[2] = i / 256 / 256;
		i = ucBuf2[3] * 256 + ucBuf2[4];
		i = i + 1;
		ucBuf2[3] = i / 256;
		ucBuf2[4] = i % 256;
//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf2[7])                                  // (tm.GetDay()!=ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
		ucBuf2[7] = (BYTE)tm.wDay;				// tm.GetDay();
		ucBuf2[8] = (BYTE)tm.wHour;				// tm.GetHour();
		ucBuf2[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
		ucBuf2[15]=0;	
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf2);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf2);
#endif
		if (ret != 0)	
			return -12;
	}
	return 0;
}

// ��������: Ǯ����Ǯ
// ��������: ������ʾ
int __stdcall SMT_PacketDelMomey(int nPacketNo,int nMoney)
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if (nPacketNo < 1)
		return -1;
	if (nMoney < 0)
		return -1;
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	
	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
		return 1; //Ǯ��������ʹ��
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������

#ifdef GZ_UNIVERSITY_TOWN
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif	
	if (ret != 0)
		return ret;
	unsigned char ucBuf1[16],ucBuf2[16],ucBufTmp[16];
	unsigned char ucCheck;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
	ret = SMT_ReadBlock(sector, 0, ucBuf1);
#endif
	if (ret != 0)	
		return -5;
	int i;
	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp, ucBuf1, sizeof(ucBufTmp));
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBufTmp);
#else
		ret = SMT_WriteBlock(sector, 2, ucBufTmp);
#endif
		if (ret != 0)	
			return -8;
		i = ucBuf1[0] + ucBuf1[1] * 256 + ucBuf1[2] * 256 * 256;
		if (i < nMoney)	
			return 3;
		i = i - nMoney;
		ucBuf1[0] = i%256;
		ucBuf1[1] = i/256;
		ucBuf1[2] = i/256/256;
		i = ucBuf1[3]*256+ucBuf1[4];
		i = i + 1;
		ucBuf1[3] = i/256;
		ucBuf1[4] = i%256;
//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf1[7])                                      //(tm.GetDay()!=ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);                           // tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)(tm.wMonth);                                 // tm.GetMonth();
		ucBuf1[7] = (BYTE)(tm.wDay);                                   // tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;                                    // tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;                                  // tm.GetMinute();
		ucBuf1[15]=0;	
		for (i = 0; i < 15; i++)	
			ucBuf1[15] += ucBuf1[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf1);
#endif
		if(ret != 0)	
			return -6;
		return 0;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
#else
		ret = SMT_ReadBlock(sector, 2, ucBuf2);
#endif
		if(ret != 0)	
			return -5;
		ucCheck = 0;
		for (i = 0; i < 15; i++)	
			ucCheck += ucBuf2[i];
		if(ucCheck != ucBuf2[15])	
			return 2;
		i = ucBuf2[0] + ucBuf2[1] * 256 + ucBuf2[2] * 256 * 256;
		if(i<nMoney)	
			return 3;
		i = i - nMoney;
		ucBuf2[0] = i%256;
		ucBuf2[1] = i/256;
		ucBuf2[2] = i/256/256;
		i = ucBuf2[3]*256+ucBuf2[4];
		i = i + 1;
		ucBuf2[3] = i/256;
		ucBuf2[4] = i%256;
	//	CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf2[7])                              // (tm.GetDay()!=ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);                   // tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)(tm.wMonth);                         // tm.GetMonth();
		ucBuf2[7] = (BYTE)(tm.wDay);                           // tm.GetDay();
		ucBuf2[8] = (BYTE)(tm.wHour);                          // tm.GetHour();
		ucBuf2[9] = (BYTE)(tm.wMinute);                        // tm.GetMinute();
		ucBuf2[15] = 0;	
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf2);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf2);
#endif
		if (ret != 0)	
			return -6;
		return 0;
	}
	return 0;
}


// ��������: �޸�Ǯ����Ϣ
// ��������: ������ʾ
int __stdcall SMT_PacketSetMoney(int nPacketNo,int nMoney)
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if (nPacketNo < 1)
		return -1;
	if (nMoney < 0)
		return -1;
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	
	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
		return 1; //Ǯ��������ʹ��
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������

#ifdef GZ_UNIVERSITY_TOWN
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif		
	if (ret != 0)
		return ret;
	unsigned char ucBuf1[16],ucBuf2[16],ucBufTmp[16];
	unsigned char ucCheck;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
	ret = SMT_ReadBlock(sector, 0, ucBuf1);
#endif
	if (ret != 0)	
		return -6;
	int i;
	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	{
		i = nMoney;
		ucBuf2[0] = i % 256;
		ucBuf2[1] = i / 256;
		ucBuf2[2] = i / 256 / 256;
		if(memcmp(ucBuf1,ucBuf2,3)==0)
			return 0;
		memcpy(ucBufTmp, ucBuf1, sizeof(ucBufTmp));
		// ����
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBufTmp);
#else
		ret = SMT_WriteBlock(sector, 2, ucBufTmp);
#endif
		if (ret != 0)	
			return -8;
		ucBuf1[0] = i % 256;
		ucBuf1[1] = i / 256;
		ucBuf1[2] = i / 256 / 256;
		i = ucBuf1[3] * 256 + ucBuf1[4];
		i = i + 1;
		ucBuf1[3] = i / 256;
		ucBuf1[4] = i % 256;
// 		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf1[7])									// (tm.GetDay()!=ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);                        // tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)tm.wMonth;								// tm.GetMonth();
		ucBuf1[7] = (BYTE)tm.wDay;									// tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;									// tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;								// tm.GetMinute();
		ucBuf1[15]=0;	
		for (i = 0; i < 15; i++)	
			ucBuf1[15] += ucBuf1[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf1);
#endif
		if(ret != 0)	
			return -8;
		return 0;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
#else
		ret = SMT_ReadBlock(sector, 2, ucBuf2);
#endif
		if(ret != 0)	
			return -9;
		ucCheck = 0;
		for(i=0;i<15;i++)	
			ucCheck+=ucBuf2[i];
		if(ucCheck != ucBuf2[15])	
			return 2;
		i = nMoney;
		ucBuf2[0] = i%256;
		ucBuf2[1] = i/256;
		ucBuf2[2] = i/256/256;
		i = ucBuf2[3]*256+ucBuf2[4];
		i = i + 1;
		ucBuf2[3] = i/256;
		ucBuf2[4] = i%256;
//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf2[7])                               // (tm.GetDay()!=ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);					// tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)tm.wMonth;							// tm.GetMonth();
		ucBuf2[7] = (BYTE)tm.wDay;								// tm.GetDay();
		ucBuf2[8] = (BYTE)tm.wHour;								// tm.GetHour();
		ucBuf2[9] = (BYTE)tm.wMinute;							// tm.GetMinute();
		ucBuf2[15]=0;	
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf2);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf2);
#endif
		if (ret != 0)	
			return -12;
	}
	return 0;
}

// �������ã�Ǯ������
// ��������: Ǯ����
int __stdcall SMT_PacketReset(int nPacketNo)
{
	int ret,sector;
	if (nPacketNo < 1)
		return -1;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -5;

	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
		return 1; //Ǯ��������ʹ��
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������
	
	memset(ucBuffer, 0, sizeof ucBuffer);
#ifdef GZ_UNIVERSITY_TOWN
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif	
	if (ret != 0)
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuffer);
#else
	ret = SMT_WriteBlock(sector, 0, ucBuffer);
#endif
	if (ret != 0)
		return ret;
	memset(ucBuffer, 0, sizeof ucBuffer);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuffer);
#else
	ret = SMT_WriteBlock(sector, 2, ucBuffer);
#endif
	return ret;
}

/*================================================================ 
* ��������    SMT_UpdateMoneyAndTxCnt
* ������      
*             [in] (int packet_no)					 Ǯ����
*             [in] (int money)						 ���¿����
*             [in] (int cnt)						 Ǯ�����״���
* ��������:   ���¿�Ǯ�����ͽ��״���
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_UpdateMoneyAndTxCnt(int packet_no, 
									  int money, 
									  int cnt, 
									  int batch_no)
{
	int ret = 0, 
		sector = 0;
	int i;
	bool main_packet_flag = false;
	bool backup_packet_flag = false;
	bool write_flag = false;
	unsigned char ucBuffer[16] = "";
	unsigned char packet_batch_no[3] = "";
	unsigned char subsidy_batch_no[3] = "";
	unsigned char ucBuf1[16], ucBuf2[16], ucBufTmp[16];
	unsigned char ucCheck;

	if (packet_no < 1)
		return -1;
	
	if (money < 0)
		return -1;
	
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
		return ret;
	
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -5;
	
	if (ucBuffer[(packet_no - 1) * 2] != 0x00)
		return 1; //Ǯ��������ʹ��
	
	sector = ucBuffer[(packet_no - 1) * 2 + 1]; //Ǯ����������

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1001;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);						// ��Ǯ������
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1002;

	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	{
		memcpy(packet_batch_no, ucBuf1 + 13, sizeof(packet_batch_no) - 1);			// Ǯ��������
		if (batch_no > packet_batch_no[0] * 256 + packet_batch_no[1])
			write_flag = true;
		
		main_packet_flag = true;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1003;
		
		ucCheck = 0;
		for (i = 0; i < 15; i++)
			ucCheck += ucBuf2[i];

		if (ucCheck == ucBuf2[15])
		{
			memcpy(packet_batch_no, ucBuf2 + 13, sizeof(packet_batch_no) - 1);		// Ǯ��������
			if (batch_no > packet_batch_no[0] * 256 +packet_batch_no[1])
				write_flag = true;

			backup_packet_flag = true;
		}
		else
			return 2;
	}

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 9, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1004;
	
	memcpy(subsidy_batch_no, ucBuffer + 3, sizeof(subsidy_batch_no) - 1);

	if (write_flag)
	{
		if (memcmp(subsidy_batch_no, packet_batch_no, sizeof(subsidy_batch_no) - 1) != 0)
		{
			memcpy(ucBuffer + 3, packet_batch_no, sizeof(packet_batch_no) - 1);
			
#ifdef GZ_UNIVERSITY_TOWN
			ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 9, ucBuffer);
#else
			ret = 0;
#endif
			if (ret != 0)	
				return -1005;
		}
		
		subsidy_batch_no[0] = batch_no >> 8 & 0xFF;
		subsidy_batch_no[1] = batch_no & 0xFF;
		
		memcpy(ucBuffer + 3, subsidy_batch_no, sizeof(subsidy_batch_no) - 1);
		
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 9, ucBuffer);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1006;
	}		
		
	if (main_packet_flag)
	{
		memcpy(ucBufTmp, ucBuf1, sizeof(ucBufTmp));
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBufTmp);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1005;
		i = money;
		ucBuf1[0] = i % 256;
		ucBuf1[1] = i / 256;
		ucBuf1[2] = i / 256 / 256;
		//		i = ucBuf1[3] * 256 + ucBuf1[4];
		//		i = i + 1;
		ucBuf1[3] = cnt / 256;
		ucBuf1[4] = cnt % 256;
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//		CTime tm = CTime::GetCurrentTime();                               �����޸Ĺ�
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf1[7])                                   // (tm.GetDay()!=ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
		ucBuf1[7] = (BYTE)tm.wDay;				// tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;				// tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
		if (write_flag)
		{
			ucBuf1[13] = subsidy_batch_no[0];		// �������κ�, ��λ��ǰ	
			ucBuf1[14] = subsidy_batch_no[1];		// �������κ�
		}
		ucBuf1[15] = 0;	
		for (i = 0; i < 15; i++)	
			ucBuf1[15] += ucBuf1[i];
		
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
		ret = 0;
#endif	
		if (ret != 0)	
			return -1007;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1008;
		
		if (!backup_packet_flag)
			return 2;
		
		i = money;
		ucBuf2[0] = i % 256;
		ucBuf2[1] = i / 256;
		ucBuf2[2] = i / 256 / 256;
		i = ucBuf2[3] * 256 + ucBuf2[4];
		//		i = i + 1;
		//		ucBuf2[3] = i / 256;
		//		ucBuf2[4] = i % 256;
		ucBuf2[3] = cnt / 256;
		ucBuf2[4] = cnt % 256;
		//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf2[7])                                  // (tm.GetDay()!=ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
		ucBuf2[7] = (BYTE)tm.wDay;				// tm.GetDay();
		ucBuf2[8] = (BYTE)tm.wHour;				// tm.GetHour();
		ucBuf2[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
		if (write_flag)
		{
			ucBuf2[13] = subsidy_batch_no[0];		// �������κ�, ��λ��ǰ	
			ucBuf2[14] = subsidy_batch_no[1];		// �������κ�
		}
		ucBuf2[15] = 0;	
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];

#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf2);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1009;
	}
	
	return 0;		
}

// д������Ϣ
int __stdcall SMT_WriteAssistInfo (int nBatchNo[1],int nMoney[1])
{
	return 0;
}

// ��ȡ������Ϣ
int __stdcall SMT_ReadAssisInfo(int nBatchNo[1],int nMoney[1],unsigned char ucBatchTime[5],unsigned char ucMacNo[4])
{
	return 0;
}

// ��������: ���úڿ����, ��ͷ���ַ��ڿ�Ϊ00, �׿�ΪFF
// ��������: ��
int __stdcall SMT_SetBlackCardFlag()
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
		return ret;
	memset(ucBuffer, 0xFF, 16);
	ucBuffer[0] = 0x00;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 5, ucBuffer);
#else
	ret = SMT_WriteBlock(3,2,ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	return 0;
}

// ��������: ������ͨ�����(�Ǻڿ�)
// ��������: ��
int __stdcall SMT_SetNormalFlag()
{
	int ret;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
		return ret;
//	CTime tm = CTime::GetCurrentTime();
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	unsigned char ucDateTime[20];
	unsigned char ucBcdDateTime[6];
	memset(ucDateTime, 0, sizeof(ucDateTime));
	memset(ucBcdDateTime, 0, sizeof(ucBcdDateTime));
//	sprintf((char*)ucDateTime,"%02d%02d%02d%02d%02d%02d",tm.GetYear()-2000,tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	sprintf((char*)ucDateTime, "%02d%02d%02d%02d%02d%02d", (BYTE)(tm.wYear - 2000), (BYTE)tm.wMonth, (BYTE)tm.wDay, (BYTE)tm.wHour, (BYTE)tm.wMinute, (BYTE)tm.wSecond);
	dec2bcd(ucDateTime, ucBcdDateTime, 6);
	memset(ucBuffer, 0xFF, 16);
	memcpy(ucBuffer + 1, ucBcdDateTime, 6);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 5, ucBuffer);
#else
	ret = SMT_WriteBlock(3, 2, ucBuffer);
#endif
	if(ret != 0)	
		return -6;
	return 0;
}

// ��������: �ɲ�ͬ�汾������ͨ���
// ��������: �汾��
int __stdcall SMT_SetNormalFlagByBlkVerion(char *blkversion)
{
	int ret;
	unsigned char ucBlkVer[12];
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
		return ret;
	if (strlen(blkversion) != 12)
	{
		return -1;	
	}
	dec2bcd((unsigned char*)blkversion,ucBlkVer,6);
	memset(ucBuffer,0xFF,16);
	memcpy(ucBuffer+1,ucBlkVer,6);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 5, ucBuffer);
#else
	ret = SMT_WriteBlock(3, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	return 0;
}

// ��������: �������Ϣ
// ��������: ��
int __stdcall SMT_ClearCard()

{
	int ret = 0;
#ifdef GZ_UNIVERSITY_TOWN
	int block = 0;
	unsigned char ucRawData[16] = "";
	unsigned char ucTempData[16] = "";
	
	memset(ucRawData, 0x00, sizeof(ucRawData));
	memset(ucTempData, 0x00, sizeof(ucTempData));
	
	if (SMT_Login_With_UserKey(SMARD_CARD_SECT4K_NO - 3, CARD_INIT_KEY, 0) != 0)
	{
		MF_ReadSeriesNo(ucRawData);
		if (ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO - 3))				// ˮ������ֻ����KEYA��д
			return ret;
		memset(ucRawData, 0x00, sizeof(ucRawData));
		for (block = 0; block < 15; block++)
		{
			if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO - 3, block, ucRawData))
				return ret;
		}
	}

	if (ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO))
		return ret;

	for (block = 1; block < 15; block++)
	{
		if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, block, ucRawData))
			return ret;
	}

	if (ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1))
		return ret;
	if (ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucRawData))
			return ret;
	
	memset(ucRawData, 0x00, 7);
	memset(ucRawData + 12, 0x00, 4);

	for (block = 0; block < 15; block++)
	{
		if ((3 == block) || (4 == block))
			continue;
		
		if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, block, ucTempData))
			return ret;
	}
	block = 9;
	memset(ucTempData, 0xFF, sizeof(ucTempData));
	ucTempData[0] = block;												// 1��Ǯ��������Ϣ��������

	if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 4, ucTempData))	
			return ret;

	if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucRawData))	// д����ʾ����
			return ret;
	
	if (ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucRawData))	// ��Ǯ������
		return ret;
	
	block = 6;															// ��һǮ���ڵ�6��
	memset(ucRawData, 0xFF, sizeof(ucRawData));
	for (int packet_num = 0; packet_num < 1; packet_num++)				// ֻ��1Ǯ������, 1Ǯ��������Ϣ�ڿ�12											// һ��8��Ǯ����Ĭ��ȫ����
	{
		ucRawData[packet_num * 2] = 0x00;
		ucRawData[packet_num * 2 + 1] = block + packet_num * 3;
	}
	
	if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucRawData))
			return ret;
	memset(ucRawData, 0x00, sizeof(ucRawData));
	ucRawData[0] = 0xFF;
	
	if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 5, ucRawData))	// д�ڿ���־�ͺ������汾��
		return ret;
#else
	unsigned char ucSerialNo[5];
	unsigned char ucKeyA[6];
	unsigned char ucRawData[256];
	
	int i,j,startSector=4;
	
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	//1��ʹ�ó��������½��Ƭ  ǰ32������
	SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	for(i=0;i<12;i++)
	{
		if(i==3)
			continue;
		ret = SMT_Login_With_UserKey(i,ucKeyA,0);
		if(ret != 0)
			return -2; //�ǳ�����
		for(j=0;j<3;j++)
		{
			if(i==0&&j==0)
				continue;
			if(i == 1 && j == 0)
			{
				//  ����ǵ�1������0�飬��ȡ��ʾ���ţ���Ҫɾ��������
				ret = SMT_ReadBlock(i,j,ucRawData);
				if(ret)
					return -3;
				// �������ʾ�����������������
				memset(ucRawData,0x00,7);
				memset(ucRawData+12,0x00,4);
			}
			else
			{
				memset(ucRawData,0x00,16);
			}
			ret=SMT_WriteBlock(i,j,ucRawData);
			if(ret)
				return -3;
		}
	}
	memset(ucRawData,0xFF,16);
	j = 0;
	for(i=0;i<4;i++)
	{
		ucRawData[j] = 0x00;							   // ���ĸ�Ǯ������
		j=j+1;
		ucRawData[j] = startSector;                        // ע��ֻ�ܸĵ��ĸ�
		startSector+=1;
		j=j+1;
	}
	//1 ʹ���û������½
	ret = SMT_Login_With_UserKey(3,ucKeyA,0);
	if(ret != 0)
		return -4;//ʹ���û�����KEYA���ܵ�½
	ret = SMT_WriteBlock(3,0,ucRawData);
	if(ret != 0)
		return -5;//�޷�д��
	memset(ucRawData,0xFF,16);

	for(i=0;i<4;i++)
	{
		ucRawData[i] = startSector;
		startSector += 1;
	}
	ret = SMT_WriteBlock(3,1,ucRawData);
	if(ret != 0)
		return -6;//�޷�д��
	memset(ucRawData,0x00,16);  //20050305����
	ucRawData[0] = 0xFF;		//��д���ϴ�汾
	ret = SMT_WriteBlock(3,2,ucRawData);
	if(ret != 0)
		return -7;//�޷�д��
#endif
	return 0;
}

/*================================================================ 
* ��������    SMT_ReadAreaCode
* ������      [out] (unsigned char area_code[3])
*             ѧУԺУ����, ����ѧУ��������, ���ѧУҲ������һ������
*			  �������ֵΪ256
* ��������:   ��ȡѧУԺУ����
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_ReadAreaCode(unsigned char area_code[3])
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 2, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -6;
	
	memcpy(area_code, ucBuffer + 4, 2);
	
	return 0;
}

/*================================================================ 
* ��������    SMT_WriteAreaCode
* ������      [in] (unsigned char area_code[3])
*             ѧУԺУ����, ����ѧУ��������, ���ѧУҲ������һ������
*			  �������ֵΪ256
* ��������:   д��ѧУԺУ����
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_WriteAreaCode(unsigned char area_code[3])
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 2, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -6;
	
	memcpy(ucBuffer + 4, area_code, 2);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 2, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)
		return -6;
	return 0;
}

/*================================================================ 
* ��������    SMT_WriteAppendCardInfo
* ������      [in] (int cut_id)�ͻ���
* ������      [in] (BYTE certificate_type[3])֤������
* ������      [in] (BYTE people[3])����
* ������      [in] (BYTE nationality[4])����
* ������      [in] (BYTE open_card_flag[2])������־, 0��ʾδ����, 1��ʶ����
* ������      [in] (BYTE card_version[2])�ƿ��汾          
* ��������:   д�뿨Ƭ������Ϣ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_WriteAppendCardInfo(int cut_id, 
									  BYTE certificate_type[3],
									  BYTE people[3], 
									  BYTE nationality[4],	   
									  BYTE open_card_flag[2],
									  BYTE card_version[2])
{
	unsigned char ucRawData[16] = "";
	int ret = 0;

#ifdef GZ_UNIVERSITY_TOWN
	//1 --- ����KEYB
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif	
	if (ret != 0)
		return -2;
	
	if ('\0' == certificate_type[1])
		certificate_type[0] = certificate_type[0] - 0x30;
	else
		certificate_type[0] = (certificate_type[0] - 0x30) * 10 + certificate_type[1] - 0x30;
		
	memcpy(ucRawData, &cut_id, 4);
	memcpy(ucRawData + 4, certificate_type, 1);
	memcpy(ucRawData + 5, people, 2);
	memcpy(ucRawData + 10, nationality, 3);
	memcpy(ucRawData + 13, &open_card_flag, 1);
	memcpy(ucRawData + 15, &card_version, 1);
	
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 6, ucRawData);		// 36�ȿ�6
#else
	ret = 0;
#endif
	if (ret != 0)
		return -5; //д��ʧ��
	return 0;				
}

/*================================================================ 
* ��������    SMT_ReadAppendCardInfo
* ������      [out] (int *cut_id)�ͻ���
* ������      [out] (BYTE certificate_type[3])֤������
* ������      [out] (BYTE people[3])����
* ������      [out] (BYTE nationality[4])����
* ������      [out] (BYTE open_card_flag[2])������־, 0��ʾδ����, 1��ʶ����
* ������      [out] (BYTE card_version[2])�ƿ��汾          
* ��������:   ��ȡ��Ƭ������Ϣ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_ReadAppendCardInfo(int *cut_id, 
									 BYTE certificate_type[3],
									 BYTE people[2], 
									 BYTE nationality[3],	   
									 BYTE open_card_flag[2],
									 BYTE card_version[2])
{
	unsigned char ucRawData[16] = "";
	int ret = 0;	
#ifdef GZ_UNIVERSITY_TOWN
	//1 --- ����KEYB
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif	
	if (ret != 0)
		return -2;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 6, ucRawData);		// 36�ȿ�6
#else
	ret = 0;
#endif
	if (ret != 0)
		return -5;

	memcpy(cut_id, ucRawData, 4);
	memcpy(certificate_type, ucRawData + 4, 1);
	memcpy(people, ucRawData + 5, 2);
	memcpy(nationality, ucRawData + 10, 3);
	memcpy(open_card_flag, ucRawData + 13, 1);
	memcpy(card_version, ucRawData + 15, 1);

	return 0;				
}

/*================================================================ 
* ��������    SMT_ReadCutId
* ������      [out] (int *cut_id)�ͻ���   
* ��������:   ��ȡ��Ƭ�ͻ���
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_ReadCutId(unsigned long *cut_id)
{
	unsigned char ucRawData[16] = "";
	int ret = 0;	
#ifdef GZ_UNIVERSITY_TOWN
	//1 --- ����KEYB
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif	
	if (ret != 0)
		return -2;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 6, ucRawData);		// 36�ȿ�6
#else
	ret = 0;
#endif
	if (ret != 0)
		return -5;

	memcpy(cut_id, ucRawData, 4);

	return 0;				
}

/*================================================================ 
* ��������    SMT_WriteRegisterCardFlag
* ������      [in] (unsigned char card_flag[11])����ע���ʶ
* ��������:   ����ʱд��ע���ʶ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_WriteRegisterCardFlag(unsigned char card_flag[11])
{
	int ret;
	unsigned char ucBuffer[16];
	memset(ucBuffer, 0, sizeof(ucBuffer));

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;

	memcpy(ucBuffer, card_flag, 10);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 7, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -5;
	return 0;
}

/*================================================================ 
* ��������    SMT_ReadRegisterCardFlag
* ������      [out] (unsigned char card_flag[11])����ע���ʶ
* ��������:   ��ȡ����ע���ʶ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_ReadRegisterCardFlag(unsigned char card_flag[11])
{
	int ret;
	unsigned char ucBuffer[16];
	memset(ucBuffer, 0, sizeof(ucBuffer));

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 7, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -5;
	memcpy(card_flag, ucBuffer, 10);

	return 0;
}

/*================================================================ 
* ��������    SMT_WriteSerRegisterFlag
* ������      [in] (unsigned char card_flag[10])����ע���ʶ
* ��������:   д�����ע���ʶ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_WriteSerRegisterFlag(unsigned char ser_flag[10])
{
	int ret;
	unsigned char ucBuffer[16];
	memset(ucBuffer, 0, sizeof(ucBuffer));

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;

	memcpy(ucBuffer, ser_flag, 10);
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 8, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -5;
	return 0;
}

/*================================================================ 
* ��������    SMT_ReadSerRegisterFlag
* ������      [out] (unsigned char card_flag[10])����ע���ʶ
* ��������:   ��ȡ����ע���ʶ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_ReadSerRegisterFlag(unsigned char ser_flag[10])
{
	int ret;
	unsigned char ucBuffer[16];
	memset(ucBuffer, 0, sizeof(ucBuffer));

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 8, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -5;
	memcpy(ser_flag, ucBuffer, 10);
	return 0;
}

/*================================================================ 
* ��������    SMT_WriteSubsidy
* ������      [in] (int money)		���
*             [in] (int batch_no)	���κ�
* ��������:   д������Ϣ: 
*             (1) ��ȡ��Ǯ��(A)�Ͳ���Ǯ�����κ�(B)
*			  (2) �ж�A���κź�B���κ��Ƿ����, 
*                 ��Ƚ���(3), ����A���κ�дB���κ�
*             (3) д����Ǯ�������κ�, ʧ���򷵻ش�����
*             (4) дǮ���������κ�, ʧ���򷵻ش�����
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_WriteSubsidy(int money, int batch_no)
{
	int ret = 0;
	int i;
	bool main_packet_flag = false;
	bool backup_packet_flag = false;
	unsigned char ucBuffer[16] = "";
	unsigned char packet_batch_no[3] = "";
	unsigned char subsidy_batch_no[3] = "";
	unsigned char ucBuf1[16], ucBuf2[16], ucBufTmp[16];
	unsigned char ucCheck;

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1001;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 6, ucBuf1);						// ��Ǯ������
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1002;

	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	{
		memcpy(packet_batch_no, ucBuf1 + 13, sizeof(packet_batch_no) - 1);			// Ǯ��������
		main_packet_flag = true;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 6 + 2, ucBuf2);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1003;
		
		ucCheck = 0;
		for (i = 0; i < 15; i++)
			ucCheck += ucBuf2[i];

		if (ucCheck == ucBuf2[15])
		{
			memcpy(packet_batch_no, ucBuf2 + 13, sizeof(packet_batch_no) - 1);		// Ǯ��������
			backup_packet_flag = true;
		}
		else
			return 2;
	}

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 9, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1004;
	
	memcpy(subsidy_batch_no, ucBuffer + 3, sizeof(subsidy_batch_no) - 1);
	
	if (memcmp(subsidy_batch_no, packet_batch_no, sizeof(subsidy_batch_no) - 1) != 0)
	{
//		memcpy(subsidy_batch_no, packet_batch_no, sizeof(subsidy_batch_no) - 1);
		memcpy(ucBuffer + 3, packet_batch_no, sizeof(packet_batch_no) - 1);

#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 9, ucBuffer);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1005;
	}

	subsidy_batch_no[0] = batch_no >> 8 & 0xFF;
	subsidy_batch_no[1] = batch_no & 0xFF;

	memcpy(ucBuffer + 3, subsidy_batch_no, sizeof(subsidy_batch_no) - 1);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 9, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1006;

	/*
	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	*/
	if (main_packet_flag)
	{
		memcpy(ucBufTmp, ucBuf1, sizeof(ucBufTmp));
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 6 + 2, ucBufTmp);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1005;
		i = money;
		ucBuf1[0] = i % 256;
		ucBuf1[1] = i / 256;
		ucBuf1[2] = i / 256 / 256;
		i = ucBuf1[3] * 256 + ucBuf1[4];
		i = i + 1;
		ucBuf1[3] = i/256;
		ucBuf1[4] = i%256;
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//		CTime tm = CTime::GetCurrentTime();                               �����޸Ĺ�
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf1[7])                                   // (tm.GetDay()!=ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
		ucBuf1[7] = (BYTE)tm.wDay;				// tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;				// tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
		ucBuf1[13] = subsidy_batch_no[0];		// �������κ�, ��λ��ǰ	
		ucBuf1[14] = subsidy_batch_no[1];		// �������κ�
		ucBuf1[15] = 0;	
		for (i = 0; i < 15; i++)	
			ucBuf1[15] += ucBuf1[i];
		
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 6, ucBuf1);
#else
		ret = 0;
#endif	
		if (ret != 0)	
			return -1007;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 6 + 2, ucBuf2);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1008;

		/*
		ucCheck = 0;
		for (i = 0; i < 15; i++)	
			ucCheck += ucBuf2[i];
		
		if (ucCheck != ucBuf2[15])
		*/
		if (!backup_packet_flag)
			return 2;
		
		i = money;
		ucBuf2[0] = i % 256;
		ucBuf2[1] = i / 256;
		ucBuf2[2] = i / 256 / 256;
		i = ucBuf2[3] * 256 + ucBuf2[4];
		i = i + 1;
		ucBuf2[3] = i / 256;
		ucBuf2[4] = i % 256;
		//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf2[7])                                  // (tm.GetDay()!=ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
		ucBuf2[7] = (BYTE)tm.wDay;				// tm.GetDay();
		ucBuf2[8] = (BYTE)tm.wHour;				// tm.GetHour();
		ucBuf2[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
		ucBuf2[13] = subsidy_batch_no[0];		// �������κ�, ��λ��ǰ	
		ucBuf2[14] = subsidy_batch_no[1];		// �������κ�
		ucBuf2[15]=0;	
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 6, ucBuf2);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1009;
	}
	
	return 0;	
}

/*================================================================ 
* ��������    SMT_ReadSubsidy
* ������      [in] (int *batch_no)	���κ�
* ��������:   ��������Ϣ: ��Ǯ���������κ�Ϊ׼              
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_ReadSubsidy(int *batch_no)
{
	int ret = 0;
	int i = 0;
	unsigned char check = 0;
	unsigned char buf_main[16] = "";
	unsigned char buf_backup[16] = "";
//	unsigned char packet_batch_no[3] = "";
	
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1001;
	
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 6, buf_main);			// ��Ǯ������
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1002;

	for (i = 0; i < 15; i++)
		check += buf_main[i];
	
	if (check == buf_main[15])
	{
//		memcpy(packet_batch_no, buf_main + 13, sizeof(packet_batch_no) - 1);
		*batch_no = buf_main[13] * 256 + buf_main[14];	// packet_batch_no[0] * 256 + packet_batch_no[1];
	}
	else	
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 8, buf_backup);			// 37��, ��8, ����Ǯ����
#else
		ret = 0;
#endif	
		if (ret != 0)	
			return ret;
		
		check = 0;
		for (i = 0; i < 15; i++)
			check += buf_backup[i];

		if (check == buf_backup[15])
		{
//			memcpy(packet_batch_no, buf_backup + 13, sizeof(packet_batch_no) - 1);
			*batch_no = buf_backup[13] * 256 + buf_backup[14];
		}
		else
			return 2;
	}
	return 0;
}

/*================================================================ 
* ��������    SMT_UpdateSubsidy
* ������      [in] (int batch_no)	���κ�
* ��������:   ���²�����Ϣ(����������κűȿ���С����£����򲻸���): 
*             (1) ��ȡ��Ǯ��(A)�Ͳ���Ǯ�����κ�(B)
*			  (2) �ж�A���κź�B���κ��Ƿ����, 
*                 ��Ƚ���(3), ����A���κ�дB���κ�
*             (3) д����Ǯ�������κ�, ʧ���򷵻ش�����
*             (4) дǮ���������κ�, ʧ���򷵻ش�����
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_UpdateSubsidy(int batch_no)
{
	int ret = 0;
	int i;
	bool main_packet_flag = false;
	bool backup_packet_flag = false;
	bool write_flag = false;
	unsigned char ucBuffer[16] = "";
	unsigned char packet_batch_no[3] = "";
	unsigned char subsidy_batch_no[3] = "";
	unsigned char ucBuf1[16], ucBuf2[16], ucBufTmp[16];
	unsigned char ucCheck;

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1001;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 6, ucBuf1);						// ��Ǯ������
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1002;

	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	{
		memcpy(packet_batch_no, ucBuf1 + 13, sizeof(packet_batch_no) - 1);			// Ǯ��������

		if (batch_no > packet_batch_no[0] * 256 + packet_batch_no[1])
			write_flag = true;
		
		main_packet_flag = true;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 8, ucBuf2);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1003;
		
		ucCheck = 0;
		for (i = 0; i < 15; i++)
			ucCheck += ucBuf2[i];

		if (ucCheck == ucBuf2[15])
		{
			memcpy(packet_batch_no, ucBuf2 + 13, sizeof(packet_batch_no) - 1);		// Ǯ��������
			if (batch_no > packet_batch_no[0] * 256 +packet_batch_no[1])
				write_flag = true;

			backup_packet_flag = true;
		}
		else
			return 2;
	}

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 9, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -1004;
	
	memcpy(subsidy_batch_no, ucBuffer + 3, sizeof(subsidy_batch_no) - 1);

	if (write_flag)
	{
		if (memcmp(subsidy_batch_no, packet_batch_no, sizeof(subsidy_batch_no) - 1) != 0)
		{
			memcpy(ucBuffer + 3, packet_batch_no, sizeof(packet_batch_no) - 1);
			
#ifdef GZ_UNIVERSITY_TOWN
			ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 9, ucBuffer);
#else
			ret = 0;
#endif
			if (ret != 0)	
				return -1005;
		}
		
		subsidy_batch_no[0] = batch_no >> 8 & 0xFF;
		subsidy_batch_no[1] = batch_no & 0xFF;
		
		memcpy(ucBuffer + 3, subsidy_batch_no, sizeof(subsidy_batch_no) - 1);
		
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 9, ucBuffer);
#else
		ret = 0;
#endif
		if (ret != 0)	
			return -1006;

		if (main_packet_flag)
		{
			memcpy(ucBufTmp, ucBuf1, sizeof(ucBufTmp));
#ifdef GZ_UNIVERSITY_TOWN
			ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 8, ucBufTmp);
#else
			ret = 0;
#endif
			if (ret != 0)	
				return -1005;

			SYSTEMTIME tm;
			GetLocalTime(&tm);
			//		CTime tm = CTime::GetCurrentTime();                               �����޸Ĺ�
			//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
			if (tm.wDay != ucBuf1[7])                                   // (tm.GetDay()!=ucBuf1[7])
			{
				ucBuf1[10] = 0;
				ucBuf1[11] = 0;
				ucBuf1[12] = 0;		
			}
			ucBuf1[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
			ucBuf1[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
			ucBuf1[7] = (BYTE)tm.wDay;				// tm.GetDay();
			ucBuf1[8] = (BYTE)tm.wHour;				// tm.GetHour();
			ucBuf1[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
			ucBuf1[13] = subsidy_batch_no[0];		// �������κ�, ��λ��ǰ	
			ucBuf1[14] = subsidy_batch_no[1];		// �������κ�	
			ucBuf1[15] = 0;	
			
			for (i = 0; i < 15; i++)	
				ucBuf1[15] += ucBuf1[i];
			
#ifdef GZ_UNIVERSITY_TOWN
			ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 6, ucBuf1);
#else
			ret = 0;
#endif	
			if (ret != 0)	
				return -1007;
		}
		else
		{
#ifdef GZ_UNIVERSITY_TOWN
			ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 8, ucBuf2);
#else
			ret = 0;
#endif
			if (ret != 0)	
				return -1008;
			
			if (!backup_packet_flag)
				return 2;
			
			//		CTime tm = CTime::GetCurrentTime();
			SYSTEMTIME tm;
			GetLocalTime(&tm);
			//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
			if (tm.wDay != ucBuf2[7])                                  // (tm.GetDay()!=ucBuf2[7])
			{
				ucBuf2[10] = 0;
				ucBuf2[11] = 0;
				ucBuf2[12] = 0;		
			}
			ucBuf2[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
			ucBuf2[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
			ucBuf2[7] = (BYTE)tm.wDay;				// tm.GetDay();
			ucBuf2[8] = (BYTE)tm.wHour;				// tm.GetHour();
			ucBuf2[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
			ucBuf2[13] = subsidy_batch_no[0];		// �������κ�, ��λ��ǰ	
			ucBuf2[14] = subsidy_batch_no[1];		// �������κ�
			ucBuf2[15] = 0;	
			
			for (i = 0; i < 15; i++)	
				ucBuf2[15] += ucBuf2[i];
			
#ifdef GZ_UNIVERSITY_TOWN
			ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 6, ucBuf2);
#else
			ret = 0;
#endif
			if (ret != 0)	
				return -1009;
		}
	}		
		
	return 0;
}

/*================================================================ 
* ��������    SMT_WriteCardTypeAndShopId
* ������      [in] (int card_type)				�̻�0-255������
*             [in] (int shop_id)				�̻���
* ��������:   д�����ͺ��̻���
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_WriteCardTypeAndShopId(int card_type, 
										 int shop_id)
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
//	unsigned char tmp_card_type[3] = "";

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;
	
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 2, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -5;
	
//	tmp_card_type[0] = (BYTE)card_type;
	memcpy(ucBuffer + 6, (BYTE*)&card_type, 1);
	memcpy(ucBuffer + 7, (BYTE*)&shop_id, 2);

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, 2, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -6;

	return 0;		
}

/*================================================================ 
* ��������    SMT_ReadCardTypeAndShopId
* ������      [in] (int *card_type)				�̻�������
*             [in] (int *shop_id)				�̻���
* ��������:   �������ͺ��̻���
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_ReadCardTypeAndShopId(int *card_type, 
										int *shop_id
										)
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";

#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return ret;
	
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 2, ucBuffer);
#else
	ret = 0;
#endif
	if (ret != 0)	
		return -5;
	
	memcpy((BYTE*)card_type, ucBuffer + 6, 1);
	memcpy((BYTE*)shop_id, ucBuffer + 7, 2);
	
	return 0;		
}

/*================================================================ 
* ��������    SMT_GZWriteWaterPacket
* ������      
*             [in] (const double price1)			 ����һ
*             [in] (const double price2)			 ���۶�
*             [in] (const double price3)			 ������
*             [in] (const double balance)			 ת�˽��
* ��������:   ���ݴ�ѧ��ר��дˮ��Ǯ��
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_GZWriteWaterPacket(
									 const double price1,
									 const double price2,
									 const double price3,
									 const double balance
									 )
{
	int ret = 0;
	unsigned char ucBuffer[17] = "";
	unsigned char ucSerialNo[5] = "";
	unsigned char sect_data[17] = "";
	unsigned char data[49] = "";
	unsigned char data1[49] = "";
	unsigned long physical_no = 0;
	unsigned long group_id = 0;
	unsigned long customer_id = 0;
	double price4 = 0;
	double price5 = 0;
	double price6 = 0;
	double balance1 = 0;
	int flag;

	if(price1 <= 0.000001 
		||price2 <= 0.000001
		||price3 <= 0.000001)
		return -1;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if (ret < 0)
		return -1;					// ��Ƭ���ڸ�Ӧ��

	physical_no = ucSerialNo[0] * 256 * 256 * 256 + ucSerialNo[1] * 256 * 256 + ucSerialNo[2] * 256 + ucSerialNo[3];
	
	/*
	if (0 == SMT_Login_With_UserKey(33, CARD_INIT_KEY, 0))
	{
		memcpy(sect_data, LOGIN_WATER_KEYA, CARD_KEY_LEN);
		memcpy(sect_data + CARD_KEY_LEN, CARD_INIT_CTRL_BIT, sizeof(CARD_INIT_CTRL_BIT));
		memcpy(sect_data + CARD_KEY_LEN + sizeof(CARD_INIT_CTRL_BIT), LOGIN_WATER_KEYB, CARD_KEY_LEN);
		if (ret = WriteCardData(33, PASSWD_BLOCK1_NUM, sect_data))
			return ret;
	}
	MF_ReadSeriesNo(ucSerialNo);
	*/
	
	ret = SMT_Login_With_UserKey(33, LOGIN_WATER_KEYA, 0);			// ˮ������ֻ��KEYA��¼                      
	if (ret != 0)
	{
		return -23;					// ��Ƭ��½ʧ��
	}
	
	if (ret = SMT_ReadBlock(33, 0, ucBuffer))
		return -3;
	
	memcpy(data, ucBuffer, sizeof(ucBuffer) - 1);
	
	if (ret = SMT_ReadBlock(33, 1, ucBuffer))
		return -4;
	
	memcpy(data + 16, ucBuffer, sizeof(ucBuffer) - 1);
	
	if (ret = SMT_ReadBlock(33, 2, ucBuffer))
		return -5;
	
	memcpy(data + 32, ucBuffer, sizeof(ucBuffer) - 1);
	
	flag = 0;
	if (0 == memcmp(data, data1, sizeof(data) - 1))
	{
		if (ret = SMT_ReadCutId(&customer_id))
			return ret;	
		flag = 1;
	}
	else
	{
		if (ret = DecodeData(data, physical_no, &group_id, &customer_id, &price4, &price5, &price6, &balance1))
		{
			if (ret = SMT_ReadCutId(&customer_id))
				return ret;	
			flag = 1;
		}
	}
	if(flag)
	{
		ret = SMT_Login_With_UserKey(33, LOGIN_WATER_KEYA, 0);			// ˮ������ֻ��KEYA��¼                      
		if (ret != 0)
		{
			return -6;					// ��Ƭ��½ʧ��
		}
	}
	
	memset(data, 0, sizeof(data));
	

	group_id = 1;

	if(balance < 0.00001 && balance1 < 0.000001)
	{
		// empty
	}
	else if(fabs(balance - balance1) < 0.00001 )
		return -10;
	//g_cardlogger<<"bala["<<balance<<"]["<<balance1<<"]water["<<price1<<","<<price2<<","<<price3<<"]"<<std::endl;
	if (ret = EncodeData(physical_no, group_id, customer_id, price1, price2, price3, balance, data))
		return ret;
	
	memcpy(ucBuffer, data, sizeof(ucBuffer) - 1);
	if (ret = SMT_WriteBlock(33, 0, ucBuffer))
		return -7;
	
	memcpy(ucBuffer, data + 16, sizeof(ucBuffer) - 1);
	if (ret = SMT_WriteBlock(33, 1, ucBuffer))
		return -8;
	
	memcpy(ucBuffer, data + 32, sizeof(ucBuffer) - 1);
	if (ret = SMT_WriteBlock(33, 2, ucBuffer))
		return -9;

	return 0;
}

/*================================================================ 
* ��������    SMT_GZReadWaterPacket
* ������    
*             [out] (unsigned long *group_id)			 ��ID��
*             [out] (unsigned long *customer_id)		 �ͻ���
*             [out] (double *price1)					 ����һ
*             [out] (double *price2)					 ���۶�
*             [out] (double *price3)					 ������
*             [out] (double *balance)					 ת�˽��
* ��������:   ���ݴ�ѧ��ר�ö�ˮ��Ǯ��
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_GZReadWaterPacket(
									double *price1,
									double *price2,
									double *price3,
									double *balance
									)
{
	int ret = 0;
	unsigned char ucBuffer[17] = "";
	unsigned char ucSerialNo[5] = "";
	unsigned char sect_data[17] = "";
	unsigned char data[49] = "";
	unsigned char data1[49] = "";
	unsigned long physical_no = 0;
	unsigned long group_id = 0;
	unsigned long customer_id = 0;

	ret = MF_ReadSeriesNo(ucSerialNo);
	if (ret < 0)
		return -1;					// ��Ƭ���ڸ�Ӧ��
	
	physical_no = ucSerialNo[0] * 256 * 256 * 256 + ucSerialNo[1] * 256 * 256 + ucSerialNo[2] * 256 + ucSerialNo[3];

	ret = SMT_Login_With_UserKey(33, LOGIN_WATER_KEYA, 0);                       
	if (ret != 0)
	{
		return -2;					// ��Ƭ��½ʧ��
	}
	
	if (ret = SMT_ReadBlock(33, 0, ucBuffer))
		return -3;
	
	memcpy(data, ucBuffer, sizeof(ucBuffer) - 1);

	if (ret = SMT_ReadBlock(33, 1, ucBuffer))
		return -4;
	
	memcpy(data + 16, ucBuffer, sizeof(ucBuffer) - 1);
	
	if (ret = SMT_ReadBlock(33, 2, ucBuffer))
		return -5;
	
	memcpy(data + 32, ucBuffer, sizeof(ucBuffer) - 1);
	
	if (0 == memcmp(data, data1, sizeof(data) - 1))
	{
		*price1 = 0;
		*price2 = 0;
		*price3 = 0;
		*balance = 0;
	}
	else
	{
		if (ret = DecodeData(data, physical_no, &group_id, &customer_id, price1, price2, price3, balance))
			return ret;
	}
	
	return 0;
}


// ��������: ��ȡ��֤�����
// ��������: flag(���λ��)
int __stdcall SMT_ReadAuthCardFlag(short * flag)
{
	int ret;
	unsigned char ucSerialNo[5]="";
	unsigned char ucInitKeyA[6]="",ucInitKeyB[6]="";	
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
	{
		return -1;//��Ƭ���ڸ�Ӧ��
	}
	memcpy(ucInitKeyA,ucSerialNo,4);
	//����7����
	sprintf((char*)&ucInitKeyA[4],"%02X",7);
	ret = SMT_Login_With_UserKey(7,ucInitKeyA,0);
	if(ret != 0)
		return -2; //�ǳ�����
	int  iWorkKeyAtBlockNo;
	int  iWorkKeyAtBlockStartPos;
	unsigned char ucAuthKeyA[6];
//	unsigned char ucAuthKeyB[6];
	unsigned char ucBuf1[16]="";
	ret = SMT_ReadBlock(7,1,ucBuf1);
	if(ret != 0)	
		return -3;	
//	memcpy(ucAuthKeyB,ucBuf1,6);
	iWorkKeyAtBlockNo=ucBuf1[6]-'0';
	iWorkKeyAtBlockStartPos=ucBuf1[7]-'0';

	unsigned char ucBuf2[16]="";
	unsigned char ucSector[3]="";
	int iWorkKeyAtSectorNo;
	//����15����
	sprintf((char*)&ucInitKeyA[4],"%02X",15);
	ret = SMT_Login_With_UserKey(15,ucInitKeyA,0);
	if(ret != 0)
		return -4; //�ǳ�����
	ret = SMT_ReadBlock(15,2,ucBuf2);
	if(ret != 0)	
		return -5;	
	//��������Կ����
	memset(ucSector,0,sizeof(ucSector));
	memcpy(ucSector,ucBuf2+14,2);
	iWorkKeyAtSectorNo=strtoul((char*)ucSector,NULL,16);
	memcpy(ucAuthKeyA,ucBuf2+8,6);
	ret = SMT_Login_With_UserKey(iWorkKeyAtSectorNo,ucAuthKeyA,0);
	if(ret != 0)
		return -6; //�ǳ�����
	unsigned char ucBuf3[256]="";
	memset(ucBuf3,0,sizeof(ucBuf3));
	ret = SMT_ReadBlock(iWorkKeyAtSectorNo,iWorkKeyAtBlockNo,ucBuf3);
	if(ret != 0)	
		return -7;
	*flag = (short)ucBuf3[iWorkKeyAtBlockStartPos+9];
	return 0;
}

// ��������: ��ȡ��֤��2
// ��������: ucWorkKey(������Կ), flag(���λ��)
int __stdcall SMT_ReadAuthCard2(unsigned char ucWorkKey[8],short * flag)
{
	int ret;
	unsigned char ucSerialNo[5]="";
	unsigned char ucInitKeyA[8]="",ucInitKeyB[8]="";
	//////////////////////////////////////////////////////////////////////////
	// ������
	ret = Load_Dll();
	if (ret != 0)
	{
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
	{
		return -1;//��Ƭ���ڸ�Ӧ��
	}
	memcpy(ucInitKeyA,ucSerialNo,4);
	//����7����
	sprintf((char*)&ucInitKeyA[4],"%02X",7);
	ret = SMT_Login_With_UserKey(7,ucInitKeyA,0);
	if(ret != 0)
		return -2; //�ǳ�����
	int  iWorkKeyAtBlockNo;
	int  iWorkKeyAtBlockStartPos;
	unsigned char ucAuthKeyA[6];
//	unsigned char ucAuthKeyB[6];
	unsigned char ucBuf1[16]="";
	ret = SMT_ReadBlock(7,1,ucBuf1);
	if(ret != 0)	
		return -3;	
//	memcpy(ucAuthKeyB,ucBuf1,6);
	iWorkKeyAtBlockNo=ucBuf1[6]-'0';
	iWorkKeyAtBlockStartPos=ucBuf1[7]-'0';

	unsigned char ucBuf2[16]="";
	unsigned char ucSector[3]="";
	int iWorkKeyAtSectorNo;
	//����15����
	sprintf((char*)&ucInitKeyA[4],"%02X",15);
	ret = SMT_Login_With_UserKey(15,ucInitKeyA,0);
	if(ret != 0)
		return -4; //�ǳ�����
	ret = SMT_ReadBlock(15,2,ucBuf2);
	if(ret != 0)	
		return -5;	
	//��������Կ����
	memset(ucSector,0,sizeof(ucSector));
	memcpy(ucSector,ucBuf2+14,2);
	iWorkKeyAtSectorNo=strtoul((char*)ucSector,NULL,16);
	memcpy(ucAuthKeyA,ucBuf2+8,6);
	ret = SMT_Login_With_UserKey(iWorkKeyAtSectorNo,ucAuthKeyA,0);
	if(ret != 0)
		return -6; //�ǳ�����
	unsigned char ucBuf3[256]="";
	memset(ucBuf3,0,sizeof(ucBuf3));
	ret = SMT_ReadBlock(iWorkKeyAtSectorNo,iWorkKeyAtBlockNo,ucBuf3);
	if(ret != 0)	
		return -7;	
	memcpy(ucWorkKey,ucBuf3+iWorkKeyAtBlockStartPos,8);
	*flag = (short)ucBuf3[iWorkKeyAtBlockStartPos+8];
	return 0;
}


// ��������: ��ȡ��֤��1
// ��������: ucWorkKey(������Կ)
int __stdcall SMT_ReadAuthCard(unsigned char ucWorkKey[8])
{
	int ret;
	unsigned char ucSerialNo[5]="";
	unsigned char ucInitKeyA[6]="",ucInitKeyB[6]="";	
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
	{
		return -1;//��Ƭ���ڸ�Ӧ��
	}
	memcpy(ucInitKeyA,ucSerialNo,4);
	//����7����
	sprintf((char*)&ucInitKeyA[4],"%02X",7);
	ret = SMT_Login_With_UserKey(7,ucInitKeyA,0);
	if(ret != 0)
		return -2; //�ǳ�����
	int  iWorkKeyAtBlockNo;
	int  iWorkKeyAtBlockStartPos;
	unsigned char ucAuthKeyA[6];
//	unsigned char ucAuthKeyB[6];
	unsigned char ucBuf1[16]="";
	ret = SMT_ReadBlock(7,1,ucBuf1);
	if(ret != 0)	
		return -3;	
//	memcpy(ucAuthKeyB,ucBuf1,6);
	iWorkKeyAtBlockNo=ucBuf1[6]-'0';
	iWorkKeyAtBlockStartPos=ucBuf1[7]-'0';

	unsigned char ucBuf2[16]="";
	unsigned char ucSector[3]="";
	int iWorkKeyAtSectorNo;
	//����15����
	sprintf((char*)&ucInitKeyA[4],"%02X",15);
	ret = SMT_Login_With_UserKey(15,ucInitKeyA,0);
	if(ret != 0)
		return -4; //�ǳ�����
	ret = SMT_ReadBlock(15,2,ucBuf2);
	if(ret != 0)	
		return -5;	
	//��������Կ����
	memset(ucSector,0,sizeof(ucSector));
	memcpy(ucSector,ucBuf2+14,2);
	iWorkKeyAtSectorNo=strtoul((char*)ucSector,NULL,16);
	memcpy(ucAuthKeyA,ucBuf2+8,6);
	/*
	{
		char szMsg[256]="";
		char keyA[17]="";
		sprintf(szMsg,"iWorkKeyAtSectorNo=%d",iWorkKeyAtSectorNo);
		::AfxMessageBox(szMsg);
		sprintf(szMsg,"iWorkKeyAtBlockNo=%d",iWorkKeyAtBlockNo);
		::AfxMessageBox(szMsg);
		sprintf(szMsg,"iWorkKeyAtBlockStartPos=%d",iWorkKeyAtBlockStartPos);
		::AfxMessageBox(szMsg);
		for(int i=0;i<6;i++)
			sprintf(&keyA[2*i],"%02X",ucAuthKeyA[i]);
		sprintf(szMsg,"ucAuthKeyA=%d",keyA);
		::AfxMessageBox(szMsg);
	}
	*/
	ret = SMT_Login_With_UserKey(iWorkKeyAtSectorNo,ucAuthKeyA,0);
	if(ret != 0)
		return -6; //�ǳ�����
	unsigned char ucBuf3[256]="";
	memset(ucBuf3,0,sizeof(ucBuf3));
	ret = SMT_ReadBlock(iWorkKeyAtSectorNo,iWorkKeyAtBlockNo,ucBuf3);
	if(ret != 0)	
		return -7;	
	memcpy(ucWorkKey,ucBuf3+iWorkKeyAtBlockStartPos,8);
	return 0;
}

// ��������: ��Ƭ����
// ��������: ��
int __stdcall SMT_ResetCard()
{
#ifdef GZ_UNIVERSITY_TOWN
	NULL;
#else
	unsigned char ucSerialNo[5];
	unsigned char ucKeyA[6],ucKeyB[6],ucInitKeyA[6],ucInitKeyB[6];
	unsigned char ucRawData[256],ucTmpRawData[16];
	int ret;
	int i;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
	{
//		MessageBox(NULL, "��Ƭ���ڸ�Ӧ��", NULL, MB_OK);
		return -1;//��Ƭ���ڸ�Ӧ��
	}
	//1 --- ����KEYA
	SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	//����KEYB
	SMT_Cal_KeyB(SMT_UCWORKINGKEY, ucSerialNo, ucKeyB);
	memset(ucRawData,0xFF,sizeof(ucRawData));
	memset(ucInitKeyA,0xFF,sizeof(ucInitKeyA));
	memset(ucInitKeyB,0,sizeof(ucInitKeyB));
//	ucRawData[6] = 0x7F;
//	ucRawData[7] = 0x07;
//	ucRawData[8] = 0x88;
//	ucRawData[9] = 0x00;

	ucRawData[6] = 0xFF;
	ucRawData[7] = 0x07;
	ucRawData[8] = 0x80;
	ucRawData[9] = 0x69;

	for(i=0;i<32;i++)
	{
		switch(1)
		{
		case 1:
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
//				MessageBox(NULL, "��Ƭ���ڸ�Ӧ��", NULL, MB_OK);
				return -1;//��Ƭ���ڸ�Ӧ��
			}
			ret = SMT_Login_With_UserKey(i,ucKeyB,1);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"ʹ�ü��ܺ�KeyB��¼��%d����ʧ��",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ü��ܺ�KeyBд��%d����ʧ��",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ü��ܺ�KeyBд��%d�����ɹ�",i);
					//AfxMessageBox(szMsg);

				}
			}
		case 2:
			if(ret==0)
				break;
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
				return -1;//��Ƭ���ڸ�Ӧ��
			}
			ret = SMT_Login_With_UserKey(i,ucKeyA,0);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"ʹ�ü��ܺ�KeyA��¼��%d����ʧ��",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ü��ܺ�KeyAд��%d����ʧ��",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ü��ܺ�KeyAд��%d�����ɹ�",i);
					//AfxMessageBox(szMsg);
				}
			}
		case 3:
			if(ret==0)
				break;
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
//				MessageBox(NULL, "��Ƭ���ڸ�Ӧ��", NULL, MB_OK);
				return -1;//��Ƭ���ڸ�Ӧ��
			}
			ret = SMT_Login_With_UserKey(i,ucInitKeyA,0);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"ʹ�ó���KeyA=0xFF��¼��%d����ʧ��",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ó���KeyA=0xFFд��%d����ʧ��",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ó���KeyA=0xFFд��%d�����ɹ�",i);
					//AfxMessageBox(szMsg);
				}
			}
		case 4:
			if(ret==0)
				break;
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
//				MessageBox(NULL, "��Ƭ���ڸ�Ӧ��", NULL, MB_OK);
				return -1;//��Ƭ���ڸ�Ӧ��
			}
			ret = SMT_Login_With_UserKey(i,ucInitKeyA,1);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"ʹ�ó���KeyB=0xFF��¼��%d����ʧ��",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ó���KeyB=0xFFд��%d����ʧ��",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ó���KeyB=0xFFд��%d�����ɹ�",i);
					//AfxMessageBox(szMsg);
				}
			}
			break;
		case 5:
			if(ret==0)
				break;
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
//				MessageBox(NULL, "��Ƭ���ڸ�Ӧ��", NULL, MB_OK);
				return -1;//��Ƭ���ڸ�Ӧ��
			}
			ret = SMT_Login_With_UserKey(i,ucInitKeyB,0);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"ʹ�ó���KeyA=0x00��¼��%d����ʧ��",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ��KeyA=0x00д��%d����ʧ��",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ó���KeyA=0x00д��%d�����ɹ�",i);
					//AfxMessageBox(szMsg);
				}
			}
		case 6:
			if(ret==0)
				break;
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
//				MessageBox(NULL, "��Ƭ���ڸ�Ӧ��", NULL, MB_OK);
				return -1;//��Ƭ���ڸ�Ӧ��
			}
			ret = SMT_Login_With_UserKey(i,ucInitKeyB,1);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"ʹ�ó���KeyB=0x00��¼��%d����ʧ��",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ó���KeyB=0x00д��%d����ʧ��",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"ʹ�ó���KeyB=0x00д��%d�����ɹ�",i);
					//AfxMessageBox(szMsg);
				}
			}
			break;
		default:
			break;
		}
		ret = MF_ReadSeriesNo(ucSerialNo);
		if(ret < 0)
		{
//			MessageBox(NULL, "��Ƭ���ڸ�Ӧ��", NULL, MB_OK);
			return -1;//��Ƭ���ڸ�Ӧ��
		}
		ret = SMT_Login_With_UserKey(i,ucInitKeyA,0);
		if(ret != 0)
		{
			char szMsg[256]="";
			sprintf(szMsg,"��ʼ����%d�����ɹ������µ�¼ʧ��",i);
//			MessageBox(NULL, szMsg, NULL, MB_OK);
			return -7; //�ǳ�����
		}
		else
		{
			//char szMsg[256]="";
			//sprintf(szMsg,"��ʼ����%d�����ɹ�",i);
			//AfxMessageBox(szMsg);
		}
	}
#endif
	return 0;
}


// ��������: ��������Ǯ����Ϣ
// ��������: Ǯ����
int __stdcall SMT_ResetPacketInfo(int nPacketNo)
{
	int ret,sector;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)
	{	
		return ret;
	}
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif
	if(ret != 0)
	{	
		return -5;
	}
	
	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
	{	
		return 1; //Ǯ��������ʹ��
	}
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������

#ifdef GZ_UNIVERSITY_TOWN
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif	
	if (ret != 0)
	{
		return ret;
	}
	unsigned char ucBuf1[16];

	memset(ucBuf1, 0, sizeof(ucBuf1));

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
	ret = SMT_WriteBlock(sector, 0, ucBuf1);
#endif
	if (ret != 0)	
	{	
		return -8;
	}
	memset(ucBuf1, 0, sizeof(ucBuf1));
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf1);
#else
	ret = SMT_WriteBlock(sector, 2, ucBuf1);
#endif
	if (ret != 0)	
	{
		return -8;
	}
	return 0;
}

// ��������: ���Ǯ����Ϣ
// ��������: nPacketNo(Ǯ����), pPcakInfo(Ǯ����Ϣָ��)
int __stdcall SMT_GetPacketInfo(int nPacketNo, MONEY_PACK_INFO *pPackInfo)
{
	int ret,sector;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
	{
//		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:��¼3����ʧ��",__FILE__,__LINE__,ret);
		return ret;
	}
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif
	if (ret != 0)
	{
//		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:��3����ʧ��",__FILE__,__LINE__,ret);	
		return -5;
	}
	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
	{
//		SetLastErrMsg(1,"File:%s\nLine:%d\nError:%d\nMessage:Ǯ��%dδ��ͨ",__FILE__,__LINE__,ret,nPacketNo);	
		return 1; //Ǯ��������ʹ��
	}
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������
#ifdef GZ_UNIVERSITY_TOWN
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif
	if (ret != 0)
	{
//		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:��½��%d����ʧ��",__FILE__,__LINE__,ret,sector);	
		return ret;
	}
	unsigned char ucBuf1[16],ucBuf2[16];
	unsigned char ucCheck;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
	ret = SMT_ReadBlock(sector, 0, ucBuf1);
#endif
	if (ret != 0)
	{
//		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:����%d����ʧ��",__FILE__,__LINE__,ret,sector);	
		return -5;
	}
	int i;
	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	{
		pPackInfo->bala		   = ucBuf1[0] + ucBuf1[1] * 256 + ucBuf1[2] * 256 * 256;
		pPackInfo->total_cnt   = ucBuf1[3] * 256 + ucBuf1[4];
		pPackInfo->date		   = (ucBuf1[5] + 2000) * 10000 + ucBuf1[6] * 100 + ucBuf1[7];
		pPackInfo->time        = ucBuf1[8] * 100 + ucBuf1[9];
		pPackInfo->daybala     = ucBuf1[10] + ucBuf1[11] * 256 + ucBuf1[12] * 256 * 256;
		pPackInfo->time_cnt    = ucBuf1[0X0D];
		pPackInfo->day_cnt     = ucBuf1[0X0E];
		return 0;
	}
	else
	{
//		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:����%d����У��ʹ���,��ʼ����������",__FILE__,__LINE__,0,sector);	
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
#else
		ret = SMT_ReadBlock(sector, 2, ucBuf2);
#endif				
		if (ret != 0)
		{
//			SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:����%d����ʧ��",__FILE__,__LINE__,ret,sector);	
			return -5;
		}
		ucCheck = 0;
		for (i = 0; i < 15; i++)
			ucCheck += ucBuf2[i];
		if (ucCheck == ucBuf2[15])
		{
			pPackInfo->bala			= ucBuf2[0] + ucBuf2[1] * 256 + ucBuf2[2] * 256 * 256;
			pPackInfo->total_cnt    = ucBuf2[3] * 256 + ucBuf2[4];
			pPackInfo->date			= (ucBuf2[5] + 2000) * 10000 + ucBuf2[6] * 100 + ucBuf2[7];
			pPackInfo->time			= ucBuf2[8] * 100 + ucBuf2[9];
			pPackInfo->daybala		= ucBuf2[10] + ucBuf2[11] * 256 + ucBuf2[12] * 256 * 256;
			pPackInfo->time_cnt		= ucBuf2[0X0D];
			pPackInfo->day_cnt		= ucBuf2[0X0E];
			return 0;
		}
		else
		{
//			SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:����%d�������ݿ�У��ʹ���",__FILE__,__LINE__,ret,sector);	
			return 2;
		}
	}
	return 2;
}


// ��������: ����Ǯ����Ϣ
// ��������: nPacketNo(Ǯ����), pPackInfo(Ǯ����Ϣָ��)
int __stdcall SMT_SetPacketInfo(int nPacketNo, MONEY_PACK_INFO *pPackInfo)
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if (nPacketNo < 1)
		return -1;
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)
	{
		return ret;
	}
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif
	if (ret != 0)
	{
		return -5;
	}
	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
	{
		return 1; //Ǯ��������ʹ��
	}
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������
#ifdef GZ_UNIVERSITY_TOWN
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif	
	if (ret != 0)
	{
		return ret;
	}
	unsigned char ucBuf1[16],ucBuf2[16],ucBufTmp[16];
	unsigned char ucCheck;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
	ret = SMT_ReadBlock(sector, 0, ucBuf1);
#endif
	if (ret != 0)
	{
		return -6;
	}
	int i;
	ucCheck = 0;
	for(i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp, ucBuf1, sizeof(ucBufTmp));
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBufTmp);
#else
		ret = SMT_WriteBlock(sector, 2, ucBufTmp);
#endif
		if (ret != 0)	
			return -8;
		if (pPackInfo->bala >= 0)
		{
			i = pPackInfo->bala;
			ucBuf1[0] = i % 256;
			ucBuf1[1] = i / 256;
			ucBuf1[2] = i / 256 / 256;
		}

		if (pPackInfo->total_cnt >= 0)
		{
			i = pPackInfo->total_cnt;
			ucBuf1[3] = i / 256;
			ucBuf1[4] = i % 256;
		}
		/*
		 *	date: -1 ���޸�,0-�޸�Ϊϵͳʱ��,>0-�޸�Ϊ����ʱ��
		 */
//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		if (0 == pPackInfo->date)
		{
			ucBuf1[5] = (BYTE)(tm.wYear - 2000); // tm.GetYear()-2000;
			ucBuf1[6] = (BYTE)(tm.wMonth);		 // tm.GetMonth();
			ucBuf1[7] = (BYTE)(tm.wDay);		 // tm.GetDay();
		}
		else if (pPackInfo->date > 20000000 && pPackInfo->date < 30000000)
		{
			int day  = pPackInfo->date % 100;
			int mon  = pPackInfo->date / 100 % 100;
			int year = pPackInfo->date / 10000 % 100;
		
			ucBuf1[5] = year;
			ucBuf1[6] = mon;
			ucBuf1[7] = day;
		}
		if (0 == pPackInfo->time)
		{
			ucBuf1[8] = (BYTE)tm.wHour;			 // tm.GetHour();
			ucBuf1[9] = (BYTE)tm.wMinute;		 // tm.GetMinute();
		}
		else if (pPackInfo->time > 0)
		{
			int hour = pPackInfo->time / 100;
			int minute = pPackInfo->time % 100;
			ucBuf1[8] = hour;
			ucBuf1[9] = minute;
		}

		if (pPackInfo->daybala >= 0)
		{
			i = pPackInfo->daybala;
			ucBuf1[10] = i % 256;
			ucBuf1[11] = i / 256;
			ucBuf1[12] = i / 256 / 256;
		}
		ucBuf1[15] = 0;
		for (i = 0; i < 15; i++)	
			ucBuf1[15] += ucBuf1[i];

#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf1);
#endif
		if (ret != 0)	
			return -8;
		return 0;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
#else
		ret = SMT_ReadBlock(sector, 2, ucBuf2);
#endif	
		if (ret != 0)	
			return -9;
		ucCheck = 0;
		for (i = 0; i < 15; i++)	
			ucCheck += ucBuf2[i];
		if (ucCheck != ucBuf2[15])	
			return 2;
		if (pPackInfo->bala >= 0)
		{
			i = pPackInfo->bala;
			ucBuf2[0] = i % 256;
			ucBuf2[1] = i / 256;
			ucBuf2[2] = i / 256 / 256;
		}
		
		if (pPackInfo->total_cnt >= 0)
		{
			i = pPackInfo->total_cnt;
			ucBuf2[3] = i / 256;
			ucBuf2[4] = i % 256;
		}
		/*
		 *	date: -1 ���޸�,0-�޸�Ϊϵͳʱ��,>0-�޸�Ϊ����ʱ��
		 */
//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		if (0 == pPackInfo->date)
		{
			ucBuf2[5] = (BYTE)tm.wYear;					// tm.GetYear()-2000;
			ucBuf2[6] = (BYTE)tm.wMonth;				// tm.GetMonth();
			ucBuf2[7] = (BYTE)tm.wDay;					// tm.GetDay();
		}
		else if (pPackInfo->date > 20000000 && pPackInfo->date < 30000000)
		{
			int day  = pPackInfo->date % 100;
			int mon  = pPackInfo->date / 100 % 100;
			int year = pPackInfo->date / 10000 % 100;
			
			ucBuf2[5] = year;
			ucBuf2[6] = mon;
			ucBuf2[7] = day;
		}
		if (0 == pPackInfo->time)
		{
			ucBuf2[8] = (BYTE)tm.wHour;					// tm.GetHour();
			ucBuf2[9] = (BYTE)tm.wMinute;				// tm.GetMinute();
		}
		else if (pPackInfo->time > 0)
		{
			int hour = pPackInfo->time / 100;
			int minute = pPackInfo->time % 100;
		
			ucBuf2[8] = hour;
			ucBuf2[9] = minute;
		}

		if (pPackInfo->daybala >= 0)
		{
			i = pPackInfo->daybala;
			ucBuf2[10] = i % 256;
			ucBuf2[11] = i / 256;
			ucBuf2[12] = i / 256 / 256;
		}
		ucBuf2[15] = 0;
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf2);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf2);
#endif
		if (ret != 0)	
			return -12;
	}
	return 0;
}

// ��������: ���ý��״���
// ��������: nPacketNo(Ǯ����), tx_cnt(���״�������)
int __stdcall SMT_SetTxCnt(int nPacketNo,int tx_cnt)
{
	int ret,sector;
	unsigned char ucBuffer[16]="";
	if (nPacketNo < 1)
		return -1;
	if (tx_cnt < 0)
		return -1;
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)
	{
		return ret;
	}
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif
	if (ret != 0)
	{
		return -5;
	}
	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
	{
		return 1; //Ǯ��������ʹ��
	}
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������
#ifdef GZ_UNIVERSITY_TOWN
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif
	if (ret != 0)
	{
		return ret;
	}
	unsigned char ucBuf1[16]="";
	unsigned char ucBuf2[16]="";
	unsigned char ucBufTmp[16]="";
	unsigned char ucCheck=0;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
	ret = SMT_ReadBlock(sector, 0, ucBuf1);
#endif
	if(ret != 0)
	{
		return -6;
	}
	int i;
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp,ucBuf1,sizeof(ucBufTmp));
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBufTmp);
#else
		ret = SMT_WriteBlock(sector, 2, ucBufTmp);
#endif
		if (ret != 0)	
			return -8;
		ucBuf1[3] = tx_cnt/256;
		ucBuf1[4] = tx_cnt%256;
		ucBuf1[15] = 0;
		for (i = 0; i < 15; i++)	
			ucBuf1[15] += ucBuf1[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf1);
#endif	
		if (ret != 0)	
			return -8;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
#else
		ret = SMT_ReadBlock(sector, 2, ucBuf2);
#endif
		if (ret != 0)	
			return -9;
		ucCheck = 0;
		for (i = 0; i < 15; i++)	
			ucCheck +=ucBuf2[i];
		if (ucCheck != ucBuf2[15])	
			return 2;
		ucBuf2[3] = tx_cnt/256;
		ucBuf2[4] = tx_cnt%256;
		ucBuf2[15]=0;
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf2);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf2);
#endif
		if(ret != 0)	
			return -10;
	}
	return 0;
}

// ��ȡ�������б�汾
int __stdcall SMT_ReadBlackNameListVersion(int *flag,char *version)
{
	int ret;
	unsigned char ucBuffer[16]="";
	char sVersion[13]="";
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
		return ret;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 5, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 2, ucBuffer);
#endif
	if (ret != 0)	
		return -6;
	if (0 == ucBuffer[0])
		*flag=1;
	else
		*flag=0;
	dec2hex(ucBuffer + 1, 6, sVersion);
	strcpy(version, sVersion);
	return 0;
}

int __stdcall GZDXC_check_card();
// ��ȡǮ�����
int __stdcall ReadBalance(int nPacketNo,int nBalance[1],int nCnt[1])
{
	/*
	char line[10]="";
	int ret,sector;
	unsigned char ucBuffer[16];
	MF_ReadSeriesNo(ucBuffer);
	g_cardlogger<<"read balance"<<std::endl;
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if(ret != 0)
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif
	if (ret != 0)
		return ret;
	
	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
		return 1; //Ǯ��������ʹ��


	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; // Ǯ����������, ����32�����Ժ�Ϊ���
#ifdef GZ_UNIVERSITY_TOWN
	if (sector < 6)							// �˴���ʾΪ���, 36�ȵ�һǮ��Ϊ��6
#else
	if (sector < 4)
#endif
	{
		return -1;
	}

#ifdef GZ_UNIVERSITY_TOWN
//	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif
	if (ret != 0)	
		return ret;
	unsigned char ucBuf1[16],ucBuf2[16];
	unsigned char ucCheck;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);				// 37��, ��6, ��Ǯ����
#else
	ret = SMT_ReadBlock(sector,0,ucBuf1);
#endif
	if(ret != 0)
		return ret;
	int i;
	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		nBalance[0] = ucBuf1[0] + ucBuf1[1] * 256 + ucBuf1[2] * 256 * 256;
		nCnt[0] = ucBuf1[3] * 256 + ucBuf1[4];
	}
	else 
	{
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);			// 37��, ��8, ����Ǯ����
#else
	ret = SMT_ReadBlock(sector, 2, ucBuf2);
#endif
		if (ret != 0)	
			return ret;
		ucCheck = 0;
		for (i = 0; i < 15; i++)
			ucCheck += ucBuf2[i];
		if (ucCheck == ucBuf2[15])
		{
			nBalance[0] = ucBuf2[0] + ucBuf2[1] * 256 + ucBuf2[2] * 256 * 256;
			nCnt[0] = ucBuf2[3] * 256 + ucBuf2[4];
			return 0;
		}
		else
		{
			return 2;
		}
	}
	// FIXME: ���ݴ�ѧ�ǣ���������ʱ������
	GZDXC_check_card();
	g_cardlogger<<"read balance success"<<std::endl;
	return 0;
	*/
	
	LOOPPURSEINFO info;
	int ret;

	ret = SMT_ReadPacketInfo(nPacketNo,&info);
	if(ret)
		return ret;
	nBalance[0] = info.RemainMoney;
	nCnt[0] = info.DealTimes;
	GZDXC_check_card();
	return 0;

}



///////////////////////////////////////////////////////////////////////////
//	��ʼ��������
//  2006-8-14
///////////////////////////////////////////////////////////////////////////

static BOOL Is_Com_open()
{
	return com_is_open;
}

static BOOL Read_Author_Key()
{
	if( TRUE == has_read_main_key)
	{
		return TRUE;
	}
	if( SMT_ReadAuthCard2(SMT_UCWORKINGKEY, &AUTH_CARD_FLAG) == 0 )
	{
		has_read_main_key = TRUE;
		SMT_AutoDll(SMT_UCWORKINGKEY);
		SMT_ControlBuzzer();
		return TRUE;
	}
	return FALSE;
}

/** 
 * @brief ʹ����Կ��¼������
 * 
 * @param sect - Ҫ��¼������
 * @param key - ��¼��Կ
 * @param flag - ��Կ��KEY-A����KEY-B
 * @param card_type - ������
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
static int LoginCardSect(long sect,BYTE * key,long flag,BYTE * card_type)
{
	//char msg[500] = "";
	BYTE tmp_card_id[5] = "";
	BYTE tmp_card_type[2] = "";
	// ����ϴε�¼���ɹ�������Ҫ���¼��һ�¿������ܼ�����¼
	static bool lastLoginSuccess = false;

	/*
#ifdef GZ_UNIVERSITY_TOWN 
	assert(sect >= SMARD_CARD_SECT4K_NO || sect < SMARD_CARD_SECT4K_NO + 2);
#else	
	assert(sect >= 0 || sect < smart_card_sect_no);
#endif
	*/

	if( !lastLoginSuccess )
	{
		if (SMT_RequestCardExist(tmp_card_id,tmp_card_type) !=0)
		{
			return -1;
		}
	}
	if( SMT_Login_With_UserKey(sect,key,flag) == 0 )
	{
		// ��¼�ɹ�
		lastLoginSuccess = true;
		//printf("Login card sect[%d] key [%s]",sect,key);
		//TRACE0(msg);
		return 0;
	}
	// ��¼ʧ��
	lastLoginSuccess = false;
	return -1;
}

static int LoginCardSect_2KEY(long sect,CardKeyData *key,BYTE * card_type,int card_flag = -1)
{
	BYTE tmp_card_id[5] = "";
	BYTE tmp_card_type[2] = "";
	int key_flag;
	// ����ϴε�¼���ɹ�������Ҫ���¼��һ�¿������ܼ�����¼
	static bool lastLoginSuccess = false;

	if(card_flag != -1)
	{
		key->flag = card_flag;
	}
	key_flag = key->flag;

	if(lastLoginSuccess==false)
	{
		if (SMT_RequestCardExist(tmp_card_id,tmp_card_type) !=0)
		{
			return -1;
		}
	}
	

	if( SMT_Login_With_UserKey(sect,key->key[key_flag],key_flag) == 0 )
	{
		// ��¼�ɹ�
		lastLoginSuccess = true;
		return 0;
	}
	/*
	key_flag = (key_flag == CARD_KEY_A) ? CARD_KEY_B : CARD_KEY_A;
	key->flag = key_flag;
	if( SMT_Login_With_UserKey(sect,key->key[key_flag],key_flag) == 0 )
	{
		// ��¼�ɹ�
		lastLoginSuccess = true;
		return 0;
	}
	*/
	// ��¼ʧ��
	lastLoginSuccess = false;
	return -1;
}
static int WriteCardBlock(int *err_code,PWriteDataFunc pFunc,LPProcessCallBack lpCallBack)
{
	BYTE card_id[9] = "";
	BYTE card_type[2] = "";
	BYTE card_key_a[10] = "";
	BYTE card_key_b[10] = ""; 

	BYTE card_key_c[10] = "";
	int valid_key_count = 0;
	int login_card_key;
	

	int current_key, old_key;
	int ret;
	BOOL login_sect_succ = FALSE;
	
	CardKeyData card_key[6];
	CardKeyData *write_key = NULL;
	
	int sect = 0;
	// �жϴ򿪴���
	if (!Is_Com_open())
	{
		*err_code = E_COM_NOT_OPEN;
		return -1;
	}
	// ��ȡ��Ȩ��Կ
	if( FALSE == Read_Author_Key())
	{
		*err_code = E_MAIN_KEY_ERROR;
		return -1;
	}
	// ��鿨�Ƿ����
	if ( SMT_RequestCardExist(card_id,card_type) != 0 )
	{
		*err_code = E_READ_CARD_ERROR;
		return -1;
	}

	// ���㿨�� keyA , keyB
	if( gen_user_card_keyA(SMT_UCWORKINGKEY,card_id
			,card_key_a) != 0 )
	{
		*err_code = E_GEN_CARD_KEY_A_ERROR;
		return -1;
	}

	if( gen_user_card_keyB(SMT_UCWORKINGKEY,card_id
			,card_key_b) != 0 )
	{
		*err_code = E_GEN_CARD_KEY_B_ERROR;
		return -1;
	}

	if (gen_card_ming_des(card_id ,card_key_c) != 0)					// 36, 38����д����keya
	{
		*err_code = E_GEN_CARD_KEY_A_ERROR;
		return -1;
	}	
	// ��ʼ�� key ������
	memset((void *)card_key,0,sizeof(card_key));

	card_key[valid_key_count].flag = CARD_KEY_A;
	// ����λ�ÿ�����Ϊ��ʼ����ʱ����޸Ĺ���KEYA 0
	memcpy(card_key[valid_key_count].key[CARD_KEY_A],CARD_INIT_KEY,sizeof(CARD_INIT_KEY));
	memcpy(card_key[valid_key_count].key[CARD_KEY_B],CARD_INIT_KEY,sizeof(CARD_INIT_KEY));
	memcpy(card_key[valid_key_count].ctrl_bit,CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
	valid_key_count++;

	// ��׼KEY 1
	card_key[valid_key_count].flag = CARD_KEY_B;
	memcpy(card_key[valid_key_count].key[CARD_KEY_A],card_key_a,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
	memcpy(card_key[valid_key_count].key[CARD_KEY_B],card_key_b,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
	memcpy(card_key[valid_key_count].ctrl_bit,CARD_NEW_CTRL_BIT,sizeof(CARD_NEW_CTRL_BIT));
	valid_key_count++;
	
	//����������Կ 2
	card_key[valid_key_count].flag = CARD_KEY_A;
	memcpy(card_key[valid_key_count].key[CARD_KEY_A],card_key_c,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
	memcpy(card_key[valid_key_count].key[CARD_KEY_B],card_key_b,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
	memcpy(card_key[valid_key_count].ctrl_bit,CARD_FOR14_CTRL_BIT,sizeof(card_key[valid_key_count].ctrl_bit));
	valid_key_count++;


	// ˮ��������Կ 3
	if(g_WaterCardType==0) 
	{
		// ����
		card_key[valid_key_count].flag = CARD_KEY_B;
		memcpy(card_key[valid_key_count].key[CARD_KEY_A],XT_LOGIN_WATER_KEYA,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].key[CARD_KEY_B],LOGIN_WATER_KEYB,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].ctrl_bit,CARD_NEW_CTRL_BIT,sizeof(CARD_NEW_CTRL_BIT));
	}
	else
	{
		// ����
		card_key[valid_key_count].flag = CARD_KEY_B;
		memcpy(card_key[valid_key_count].key[CARD_KEY_A],LOGIN_WATER_KEYA,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].key[CARD_KEY_B],LOGIN_WATER_KEYB,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].ctrl_bit,CARD_NEW_CTRL_BIT,sizeof(CARD_NEW_CTRL_BIT));
	}
	
	valid_key_count++;

	// ��׼KEY 4
	card_key[valid_key_count].flag = CARD_KEY_B;
	memcpy(card_key[valid_key_count].key[CARD_KEY_A],card_key_c,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
	memcpy(card_key[valid_key_count].key[CARD_KEY_B],card_key_b,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
	memcpy(card_key[valid_key_count].ctrl_bit,CARD_NEW_CTRL_BIT,sizeof(card_key[valid_key_count].ctrl_bit));
	valid_key_count++;

	// ˮ��������Կ 5, ��keyb ������ԿȨ��
	/*
	if(g_WaterCardType==0) 
	{
		// ����
		card_key[valid_key_count].flag = CARD_KEY_B;
		memcpy(card_key[valid_key_count].key[CARD_KEY_A],XT_LOGNI_WATER_KEYA,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].key[CARD_KEY_B],LOGIN_WATER_KEYB,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].ctrl_bit,CARD_NEW_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
	}
	else
	{
		// ����
		card_key[valid_key_count].flag = CARD_KEY_B;
		memcpy(card_key[valid_key_count].key[CARD_KEY_A],LOGIN_WATER_KEYA,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].key[CARD_KEY_B],LOGIN_WATER_KEYB,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].ctrl_bit,CARD_NEW_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
	}
	valid_key_count++;
	*/

	ret = 0;

	// �ٶ�һ�ο����һ�¿� ID
	/*
	BYTE card_id_2[9] = "";
	SMT_RequestCardExist(card_id_2,card_type);
	if( memcmp(card_id,card_id_2,4) != 0)
	{
		* err_code = E_READ_CARD_ERROR;
		return -1;
	}
	*/
	// ������Ե�¼�� key ������
	current_key = 0;

	/*
	���ݴ�ѧ��Ӧ���Ǵ� 16 ������ʼ��ʼ��
	0 ~ 15 ����Ϊ���ͨʹ��
	16 ~ 31 ����Ϊ�� 2K ��������ʹ��, ��Ҫ��ʽ��
	32 ~ 39 ����Ϊ�� 3~4k ������, �� 33 ����Ϊˮ��ʹ��, �� 36 ~ 38 ����Ϊһ��ͨʹ��
	*/

	for(sect = GZ_CARD_SECT; sect < g_gz_card_end_sect; ++sect)
	{
/*
#else
	for(sect = 33; sect < g_gz_card_end_sect; ++sect) // ��ɽ��ѧʹ�õ�
	{
#if 0
		if(sect != 33 && sect != 36 && sect != 37 && sect != 38)
			continue;
#else
		if(sect != 36 && sect != 37 && sect != 38)
			continue;
#endif
#endif
*/
	//for (sect = SMARD_CARD_SECT4K_NO - 3; sect < (SMARD_CARD_SECT4K_NO + 3); ++sect)
		if(g_init_sect_map[sect]==0)
			continue;
		if (sect == GZ_SHUIKONG_SECT)									// ˮ������ֻ����KEYA��д, KEYBУ����Ч								
		{
			//write_key = &card_key[3];
			write_key = &card_key[3];
			current_key = 1;
		}
		else if (SMARD_CARD_SECT4K_NO == sect
			|| (sect >= 16 && sect <=32) 
			|| sect == 34
			|| sect == 35)
		{
			write_key = &card_key[2]; 
			current_key = 0;
		}
		else if (SMARD_CARD_SECT4K_NO + 2 == sect)
		{
			write_key = &card_key[4];
			current_key = 4;
		}
		// �����������ñ�׼��Կ����
		//else if (SMARD_CARD_SECT4K_NO + 1 == sect)
		else
		{
			write_key = &card_key[1];
			//current_key = 1;
		}

		// ���ûص�����
		if( lpCallBack != NULL )
			lpCallBack(sect);
		// ���γ�ʼ��ÿ������
		old_key = current_key;
		login_sect_succ = FALSE;

		// ���ҿ��Ե�¼�� key 
		do
		{			
			/*
			if(current_key == 3 || current_key == 0)
				login_card_key = CARD_KEY_A; // ˮ��������Ҫ�� keya ��¼
			else
				login_card_key = CARD_KEY_B;
			*/
			login_card_key = card_key[current_key].flag;
			// �����¼�ɹ� ����ѭ��
			if( LoginCardSect_2KEY(sect,&card_key[current_key],card_type,login_card_key) == 0)
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key++;
			if ( current_key >= valid_key_count )
				current_key = 0;
			/*if (current_key == old_key)
				break;*/
		}while(current_key!=old_key);
		// �жϵ�ǰ�����Ƿ�ɹ���¼
		if (login_sect_succ == FALSE)
		{
			*err_code = E_CARD_LOGIN_ERROR;
			return -1;
		}
		// ����д���ص�����
		if( pFunc != NULL )
		{
			if( (ret = pFunc(sect, write_key,NULL, card_type,write_key)) != 0)
			{
				// д�����ɹ�
				*err_code = E_CARD_WRITE_ERROR;
				return ret;
			}
		}
	}
	return 0;
}

int WriteCardData(long sect,long block,BYTE * buf)
{
	assert(buf != NULL);
	return SMT_WriteBlock(sect,block,buf);
}

static int WriteInitNewCardData(long sect,CardKeyData * keya,CardKeyData *keyb
								,BYTE * card_type,CardKeyData * login_key)
{
	BYTE sect_data[17] = "";
	int password_block = 0;
	int ctrl_bit_len = sizeof(CARD_NEW_CTRL_BIT);
	// ��ʼ��д�������λ
	memset(sect_data,0,sizeof(sect_data));
	// key A
	memcpy(sect_data,keya->key[CARD_KEY_A],CARD_KEY_LEN);
	memcpy(sect_data+CARD_KEY_LEN,keya->ctrl_bit,ctrl_bit_len);
	// key B
	memcpy(sect_data+CARD_KEY_LEN+ctrl_bit_len,keya->key[CARD_KEY_B],CARD_KEY_LEN);
	/*
	// control bit
	if (sect == SMARD_CARD_SECT4K_NO) // 36 ����, keya ֻ��, keyb �ɶ���д
		memcpy(sect_data+CARD_KEY_LEN,CARD_FOR14_CTRL_BIT,sizeof(CARD_FOR14_CTRL_BIT));
	else if (GZ_SHUIKONG_SECT == sect)  // ˮ������ , ����ʱ�Ŀ���λ����
		memcpy(sect_data + CARD_KEY_LEN, CARD_INIT_CTRL_BIT, sizeof(CARD_NEW_CTRL_BIT));
	else // �������� , keya �ɶ�����д, keyb �ɶ���д���޸���Կ
		memcpy(sect_data+CARD_KEY_LEN,CARD_NEW_CTRL_BIT,sizeof(CARD_NEW_CTRL_BIT)); 
	*/
	
	
	// if(WriteCardData(sect,PASSWD_BLOCK_NUM,sect_data) == 0)
	// ǰ 32 д�������ڵ� 3 ��
	if(sect < 32)
		password_block = PASSWD_BLOCK_NUM;
	else // �� 8 ���������ڵ� 15 ��
		password_block = PASSWD_BLOCK1_NUM;

	if (0 == WriteCardData(sect,password_block,sect_data))
	{
		// д���ɹ��������Ƿ��ʼ���ɹ�
		// ����ʹ�� keyA ��¼
		// �޸�һ�� 20080804
		/*
		if(LoginCardSect(sect,keya->key[CARD_KEY_A]
			,CARD_KEY_A,card_type) != 0)
		{
			return -2;
		}
		*/
		// modify by ���� ����ٶȲ���¼ keyb ��
		// ����ʹ�� keyB ��¼
		/*
		if(LoginCardSect(sect,keyb->key
			,keyb->flag,card_type) != 0)
		{
			return -3;
		}
		*/
		return 0;
	}
	return -1;
}

int __stdcall InitNewCard(int * err_code,const char* showcardno
								   ,LPProcessCallBack lpCallBack)
{
	int ret = 0;
	if((ret = WriteCardBlock(err_code,WriteInitNewCardData,lpCallBack)) != 0)
	{
		//*err_code = E_CARD_WRITE_ERROR;
		return ret;
	}
	if(showcardno != NULL)
	{
		// ����BCD��
		unsigned char bcdshowcard[5] = "";
		for(int i = 0;i < 10;i+=2)
		{
			bcdshowcard[i/2] = (((showcardno[i] - '0') << 4) & 0xF0)
				| ((showcardno[i+1] - '0') & 0x0F);
		}
		// д��ʾ����
		if(SMT_ChangeShowCardNo(bcdshowcard) != 0)
		{
			return -1;
		}
	}
	SMT_ControlBuzzer();
	return 0;
}

int __stdcall ReadCardMainKey(BYTE * main_key,short wantFlag,
									   short * readFlag)
{
	int ret = -1;
	if( NULL == readFlag )
	{
		return -1;
	}
	if( TRUE == has_read_main_key 
		&& (AUTH_CARD_FLAG == wantFlag || -1 == wantFlag ))
	{
		return 0;
	}
	unsigned char work_key[9] = "";
	if( SMT_ReadAuthCard2(work_key,&AUTH_CARD_FLAG) == 0 )
	{
		if(AUTH_CARD_FLAG == wantFlag || -1 == wantFlag)
		{
			has_read_main_key = TRUE;
			ret = 0;
			SMT_AutoDll(work_key);
			SMT_ControlBuzzer();
			memcpy(main_key,work_key,sizeof(main_key));
			*readFlag = AUTH_CARD_FLAG;
		}
	}
	return ret;
}

int __stdcall ReadCardPhyID(BYTE card_id[4],BYTE card_type[2])
{
	return SMT_RequestCardExist(card_id,card_type);
}

/** 
 * @brief ���տ��Ļص�����
 * 
 * @param sect - ������
 * @param keya - KEYA
 * @param keyb - KEYB
 * @param card_type - ������
 * @param login_key - ��¼��Կ
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
static int WriteRefineCardData(long sect,CardKeyData * keya,CardKeyData * keyb
							   ,BYTE * card_type,CardKeyData * login_key)
{	
	BYTE sect_data[17] = "";
	int ret;
	// ��ʼ��д�������λ
	memset(sect_data,0,sizeof(sect_data));
	// key A, ��������ڻ��յ�ʱ��д��KEYA
	memcpy(sect_data,CARD_INIT_KEY,CARD_KEY_LEN);
	// control bit
	memcpy(sect_data+CARD_KEY_LEN,CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
	// key B
	memcpy(sect_data+CARD_KEY_LEN+sizeof(CARD_INIT_CTRL_BIT),CARD_INIT_KEY,CARD_KEY_LEN);
	// ����� ������ ��
//	memcmp(login_key->key,keyb->key,sizeof(keyb->key));
	bool ctrl_bit = false;
	//if(!memcmp(login_key->key,keyb->key,sizeof(keyb->key))
	//	&& card_type[0] == PHILIPS_CARD_TYPE[0])
	if(!memcmp(login_key->key[login_key->flag],
		login_key->key[CARD_KEY_B],sizeof(login_key->key[CARD_KEY_B]))
		&& card_type[0] == PHILIPS_CARD_TYPE[0])
	{
		// ������Keyb ��¼������Ϊ ������ ��
		ctrl_bit = true;
	}
	ret = -1;

	if(sect >= 32)
	{
		return WriteCardData(sect,PASSWD_BLOCK1_NUM,sect_data);
	}
	else
	{
		return WriteCardData(sect,PASSWD_BLOCK_NUM,sect_data);
	}
	
	
	/*
	// ����ʹ�� keyB ��¼
	if((LoginCardSect(sect,CARD_INIT_KEY
		,CARD_KEY_A,card_type) == 0) || ctrl_bit) // ���λ����Ҫ��һ��
	{
		ret = 0;
	}
	return ret;
	*/
	
}

int __stdcall RefineCard(int *err_code, LPProcessCallBack lpFunc)
{
	
	unsigned char phyid[9];
	MF_ReadSeriesNo(phyid);
	if(SMT_ClearCard() != 0)
	{
		*err_code = E_CARD_WRITE_ERROR;
		return -1;
	}
	
	if(WriteCardBlock(err_code, WriteRefineCardData, lpFunc) != 0)
	{
		*err_code = E_CARD_WRITE_ERROR;
		return -1;
	}
	SMT_ControlBuzzer();
	return 0;
}

int __stdcall ReadCardBlock(int startSect,int endSect
									 ,short block,LPGetBlockData lpFunc)
{
	BYTE card_id[9] = "";
	BYTE card_type[2] = "";
	BYTE card_key_a[10] = "";
	BYTE card_key_b[10] = "";
	int block_count;
	int valid_key_count = 0;

	BYTE card_key_c[10] = "";
	
	BYTE buf[16] = "";
	int current_key, old_key;
	BOOL login_sect_succ = FALSE;
	
	CardKeyData card_key[6];
	
	int sect = 0;
	// �жϴ򿪴���
	if (!Is_Com_open())
	{
		return -1;
	}
	// ��ȡ��Ȩ��Կ
	if( FALSE == Read_Author_Key())
	{
		return -1;
	}
	// ��鿨�Ƿ����
	if ( SMT_RequestCardExist(card_id,card_type) != 0 )
	{
		return -1;
	}

	// ���㿨�� keyA , keyB
	if( gen_user_card_keyA(SMT_UCWORKINGKEY,card_id
			,card_key_a) != 0 )
	{
		return -1;
	}
	if( gen_user_card_keyB(SMT_UCWORKINGKEY,card_id
			,card_key_b) != 0 )
	{
		return -1;
	}
	if (gen_card_ming_des(card_id ,card_key_c) != 0)					// 36, 38����д����keya
	{
		return -1;
	}
	// ��ʼ�� key ������
	memset((void *)card_key,0,sizeof(card_key));


	card_key[valid_key_count].flag = CARD_KEY_A;
	// ����λ�ÿ�����Ϊ��ʼ����ʱ����޸Ĺ���KEYA 0
	memcpy(card_key[valid_key_count].key[CARD_KEY_A],CARD_INIT_KEY,sizeof(CARD_INIT_KEY));
	memcpy(card_key[valid_key_count].key[CARD_KEY_B],CARD_INIT_KEY,sizeof(CARD_INIT_KEY));
	memcpy(card_key[valid_key_count].ctrl_bit,CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
	valid_key_count++;

	// ��׼KEY 1
	card_key[valid_key_count].flag = CARD_KEY_A;
	memcpy(card_key[valid_key_count].key[CARD_KEY_A],card_key_a,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
	memcpy(card_key[valid_key_count].key[CARD_KEY_B],card_key_b,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
	memcpy(card_key[valid_key_count].ctrl_bit,CARD_NEW_CTRL_BIT,sizeof(CARD_NEW_CTRL_BIT));
	valid_key_count++;

	//����������Կ 2
	card_key[valid_key_count].flag = CARD_KEY_A;
	memcpy(card_key[valid_key_count].key[CARD_KEY_A],card_key_c,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
	memcpy(card_key[valid_key_count].key[CARD_KEY_B],card_key_b,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
	memcpy(card_key[valid_key_count].ctrl_bit,CARD_NEW_CTRL_BIT,sizeof(CARD_NEW_CTRL_BIT));
	valid_key_count++;

	// ˮ��������Կ 3
	if(g_WaterCardType==0)
	{
		card_key[valid_key_count].flag = CARD_KEY_A;
		memcpy(card_key[valid_key_count].key[CARD_KEY_A],XT_LOGIN_WATER_KEYA,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].key[CARD_KEY_B],LOGIN_WATER_KEYB,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].ctrl_bit,CARD_NEW_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
		
	}
	else
	{
		card_key[valid_key_count].flag = CARD_KEY_A;
		memcpy(card_key[valid_key_count].key[CARD_KEY_A],LOGIN_WATER_KEYA,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].key[CARD_KEY_B],LOGIN_WATER_KEYB,sizeof(card_key[valid_key_count].key[CARD_KEY_A]));
		memcpy(card_key[valid_key_count].ctrl_bit,CARD_NEW_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
	}
	
	valid_key_count++;
	current_key = 1;
	// modify by ���� 
	for (sect = startSect; sect < endSect; ++sect)
	//for (sect = SMARD_CARD_SECT4K_NO - 3; sect < (SMARD_CARD_SECT4K_NO + 3); ++sect)
	{
		if (sect == GZ_SHUIKONG_SECT)									
		{
			current_key = 3;
		}
		else if ((SMARD_CARD_SECT4K_NO == sect) || (SMARD_CARD_SECT4K_NO + 2 == sect))
		{
			current_key = 2;
		}
		else //if (SMARD_CARD_SECT4K_NO + 1 == sect)
		{
			//current_key = 1;	
		}


		// ���γ�ʼ��ÿ������
		old_key = current_key;
		login_sect_succ = FALSE;
		// ���ҿ��Ե�¼�� key 
		do
		{
			//card_key[current_key].flag = CARD_KEY_A;
			// �����¼�ɹ� ����ѭ��
			if( LoginCardSect_2KEY(sect,&card_key[current_key],card_type,card_key[current_key].flag) == 0)
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key++;
			if( current_key >= valid_key_count )
				current_key = 0;
			/*if (current_key == old_key)
				break;*/
		}while(current_key != old_key);
		// �жϵ�ǰ�����Ƿ�ɹ���¼
		if (login_sect_succ == FALSE)
		{
			return -1;
		}
		// ��ȡ����������
		if(sect < 32)
			block_count = 4;
		else
			block_count = 16;
		for (int b = 0;b < block_count;++b)
		{
			if(block & (1 << b)
				|| (sect == 33 && b>=0 && b<=2))
			{
				memset(buf,0,sizeof(buf));
				if(SMT_ReadBlock(sect,b,buf) != 0)
				{
					return -1;
				}
				// ���ö����ص�����
				if( lpFunc != NULL )
				{
					lpFunc(sect,b,buf,
						card_key[current_key].key[card_key[current_key].flag],
						card_key[current_key].flag);	
				}
			}
		}	
	}
	return 0;
}

int __stdcall ResetAuthCard(int * err_code,LPProcessCallBack lpCallBack)
{
	BYTE card_id[9] = "";
	BYTE card_type[2] = "";
	BYTE card_key[7] = "";
	BYTE buf[17] = "";
	BYTE tmpBuf[17] = "";
	BYTE priKeyA[7] = "";
	BYTE priKeyB[7] = "";
	BYTE tmpSect[3] = "";
	char tmp[3] = "";
	short priBlock,priStartPos,priSect;
	unsigned short sect;

	if( !Is_Com_open() )
	{
		* err_code = E_COM_NOT_OPEN;
		return -1;
	}

	if(SMT_RequestCardExist(card_id,card_type) != 0)
	{
		* err_code = E_READ_CARD_ID_ERROR;
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	// ��ȡ 7 ����
	sect = 7;
	memset(card_key,0,sizeof(card_key));
	memcpy(card_key,card_id,sizeof(card_id));
	// �� ID Ϊ 4 λ
	sprintf((char*)card_key + 4,"%02X",sect);
	//memcpy(card_key+4,((char*)&sect)+1,1);
	//memcpy(card_key+5,((char*)&sect),1);
	
	// ��ȡ Key B
	if( LoginCardSect(sect,card_key,CARD_KEY_A,card_type) != 0)
	{
		//AfxMessageBox("��¼����ʧ�ܣ�");
		* err_code = E_CARD_LOGIN_ERROR;
		return -2;
	}
	if( SMT_ReadBlock(sect,1,buf) != 0)
	{
		//AfxMessageBox("��ȡ����ʧ�ܣ�");
		* err_code = E_CARD_WRITE_ERROR;
		return -3;
	}
	// key b
	memcpy(priKeyB,buf,CARD_KEY_LEN);
	// block
	priBlock = buf[6] - '0';
	if( priBlock < 0 || priBlock > 2)
	{
		//AfxMessageBox("���ݲ��Ϸ���");
		* err_code = E_INVALID_CARD;
		return -3;
	}
	// start pos
	// priStartPos = char2int((const char*)&buf[7],1,true);
	tmp[0] = buf[7];
	priStartPos = (short)strtoul(tmp,NULL,16);
	if( priStartPos < 0 || priStartPos > 10)
	{
		//AfxMessageBox("���ݲ��Ϸ���");
		* err_code = E_INVALID_CARD;
		return -3;
	}
	
	//////////////////////////////////////////////////////////////////////////
	// �� 15 ����
	sect = 15;
	memset(card_key,0,sizeof(card_key));
	memcpy(card_key,card_id,sizeof(card_id));
	// �� ID Ϊ 4 λ
	sprintf((char*)card_key + 4,"%02X",sect);
	// ��ȡ Key a
	if( LoginCardSect(sect,card_key,CARD_KEY_A,card_type) != 0)
	{
		//AfxMessageBox("��¼����ʧ�ܣ�");
		* err_code = E_CARD_LOGIN_ERROR;
		return -2;
	}
	if( SMT_ReadBlock(sect,2,buf) != 0)
	{
		//AfxMessageBox("��ȡ����ʧ�ܣ�");
		* err_code = E_CARD_WRITE_ERROR;
		return -3;
	}
	// key a
	strncpy((char*)priKeyA,(char*)buf+8,CARD_KEY_LEN);
	// private key section no
	priSect = (short)strtoul((char*)buf+14,NULL,16);
	//////////////////////////////////////////////////////////////////////////
	// ���ɳ�ʼ״̬
	memset((char*)buf,255,sizeof(buf) - 1);
	strncpy((char*)buf + sizeof(CARD_INIT_KEY),(char*)CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));

	if(lpCallBack)
		lpCallBack(0);
	bool isClear = false;
	// ������Կ����
	if(LoginCardSect(priSect,priKeyA,CARD_KEY_A,card_type) == 0)
	{
		memset(tmpBuf,0,sizeof(tmpBuf));
		
		if(SMT_WriteBlock(priSect,priBlock,tmpBuf) != 0)
		{
			isClear = false;
			goto L_TRY_KEY_B;
		}
		// д����λ����
		strncpy((char*)tmpBuf,(char*)buf,sizeof(tmpBuf));
		if(SMT_WriteBlock(priSect,3,tmpBuf) != 0)
		{
			// д��ʧ�ܣ�ʹ��Key B ����
			isClear = false;
		}
		else
			isClear = true;
		
	}
L_TRY_KEY_B:
	if(lpCallBack)
		lpCallBack(0);
	if(!isClear)
	{
		// �� key B ����
		if(LoginCardSect(priSect,priKeyB,CARD_KEY_B,card_type) == 0)
		{
			memset(tmpBuf,0,sizeof(tmpBuf));
			
			if(SMT_WriteBlock(priSect,priBlock,tmpBuf) != 0)
			{
			//	AfxMessageBox("д��������ʧ�ܣ�");
				*err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			// д����λ����
			strncpy((char*)tmpBuf,(char*)buf,sizeof(tmpBuf));
			if(SMT_WriteBlock(priSect,3,tmpBuf) != 0)
			{
				// key B Ҳ�޷�д��
				//AfxMessageBox("д��������ʧ�ܣ�");
				*err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			
		}
		else
		{
			// �޷��� key b ��¼��
		//	AfxMessageBox("��¼����ʧ�ܣ�");
			*err_code = E_CARD_LOGIN_ERROR;
			return -1;
		}
	}

	// �����Ƿ���ճɹ�
	if( LoginCardSect(priSect,CARD_INIT_KEY,CARD_KEY_A,card_type) != 0)
	{
		//AfxMessageBox("��������ʧ�ܣ�");
		*err_code = E_CARD_WRITE_ERROR;
		return -2;
	}
	char msg[128] = "";
	// ������������
	for(sect = 0;sect < AUTH_CARD_SECT_NO;++sect)
	{
		if(lpCallBack)
			lpCallBack(0);
		// ��Կ�������ó�ʼ��
		if( sect == priSect)
			continue;
		memset(card_key,0,sizeof(card_key));
		memcpy(card_key,card_id,sizeof(card_id));
		// �� ID Ϊ 4 λ
		sprintf((char*)(card_key+4),"%02X",sect);
		
		if( LoginCardSect(sect,card_key
				,CARD_KEY_A,card_type) == 0)
		{
			strncpy((char*)tmpBuf,(char*)buf,sizeof(tmpBuf));
			// ��¼�ɹ�
			// ���տ���λ
			if( SMT_WriteBlock(sect,3,tmpBuf) != 0)
			{
				sprintf(msg,"����[%d]����ʧ�ܣ�",sect);
				//AfxMessageBox(msg);
				*err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			// ��Key A ��¼����
			if( LoginCardSect(sect,CARD_INIT_KEY,CARD_KEY_A,card_type) != 0)
			{
				sprintf(msg,"���Ե�¼%d����ʧ�ܣ�",sect);
			//	AfxMessageBox(msg);	
				*err_code = E_CARD_LOGIN_ERROR;
				return -1;
			}
		}
		else if( LoginCardSect(sect,CARD_INIT_KEY,CARD_KEY_A,card_type) == 0)
		{
			// ʹ�� ��ʼ�� ��Կ���е�¼����
			sprintf(msg,"����%dʹ�ó�ʼ��Կ��¼�ɹ���\n�Ƿ�������գ�",sect);
		//	if(AfxMessageBox(msg,MB_OKCANCEL) == IDCANCEL)
			if (MessageBox(NULL, msg, "", MB_OKCANCEL) == IDCANCEL)
			{
				// �������������,�򷵻�
				*err_code = E_CARD_LOGIN_ERROR;
				return -2;
			}
		}
		else
		{
			sprintf(msg,"��¼����%d����ʧ��",sect);
			//AfxMessageBox(msg);
			*err_code = E_CARD_LOGIN_ERROR;
			return -2;
		}
	}
	return 0;
}

/** 
 * @brief ��ӿں��������¶�ȡ��Ȩ��
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */

int __stdcall ResetMainKey()
{
//	if( ReaderAuthor((char *)CARD_MAIN_KEY) == 0 )
	if( ReaderAuthor(CARD_MAIN_KEY) == 0 )	
	{
		SMT_AutoDll(CARD_MAIN_KEY);
		has_read_main_key = TRUE;
		return TRUE;
	}
	return FALSE;
}

/** 
 * @brief ��ʼ����Ȩ����ÿ��������Կ, �Ϻ���
 * 
 * @param card_id - ������ID��
 * @param card_type - ������
 * @param lpCallBack - �ص�����������ʱ���� ������ΪNULL
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
static int NewAuthCard_Init_Sect(BYTE card_id[4],BYTE card_type[2],
								 LPProcessCallBack lpCallBack)
{
	int sect;
	char msg[256] = "";
	BYTE buf[16] = "";
	BYTE card_key[6] = "";
	memcpy(card_key,card_id,sizeof(card_id));
	// ��ȡһ�ο�,�����û�ͬʱ�Ŷ��ſ�
	for(sect = 0;sect < AUTH_CARD_SECT_NO;++sect)
	{
		if(lpCallBack)
			lpCallBack(sect);
		// һ��Ҫʹ�ô�д
		sprintf((char*)card_key+4,"%02X",sect);

		//////////////////////////////////////////////////////////////////////////
		if( LoginCardSect(sect,CARD_INIT_KEY,CARD_KEY_A,card_type) != 0)
		{
			if(LoginCardSect(sect,card_key,CARD_KEY_B,card_type) != 0)
			{
				sprintf(msg,"��¼����%d����ʧ��",sect);
				return -1;
			}
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////
		memcpy(buf,card_key,sizeof(card_key));
		memcpy(buf+6,CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
		memcpy(buf+10,card_key,sizeof(card_key));
		// д������Ϣ
		SMT_WriteBlock(sect,3,buf);
		/*
		{
			sprintf(msg,"��ʼ����%d����ʧ��",sect);
			AfxMessageBox(msg);
			return -1;
		}
		*/
		if( LoginCardSect(sect,card_key,CARD_KEY_A,card_key) != 0)
		{
			sprintf(msg,"���Ե�%d������¼ʧ��!\nд����%d������Կʧ��!"
				,sect,sect);
			return -1;
		}
		//////////////////////////////////////////////////////////////////////////
	}
	return 0;
}

/** 
 * @brief ��ʼ����Ȩ����ÿ��������Կ, �ϴ�
 * 
 * @param card_id - ������ID��
 * @param card_type - ������
 * @param lpCallBack - �ص�����������ʱ���� ������ΪNULL
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
static int NewAuthCard_Init_Sect(BYTE card_id[4],BYTE card_type[2],
								 LPProcessCallBack lpCallBack, int pri_sect)
{
	int sect;
	int nWorkKeySector = 0;
	int ret = 0;
	char msg[256] = "";
	BYTE buf[16] = "";
	BYTE card_key[6] = "";
	memcpy(card_key,card_id,sizeof(card_id));
	// ��ȡһ�ο�,�����û�ͬʱ�Ŷ��ſ�
	for(sect = 0;sect < AUTH_CARD_SECT_NO;++sect)
	{
		if(lpCallBack)
			lpCallBack(sect);
		// һ��Ҫʹ�ô�д
		sprintf((char*)card_key+4,"%02X",sect);

		//////////////////////////////////////////////////////////////////////////
		if(LoginCardSect(sect, CARD_INIT_KEY, CARD_KEY_A, card_type) != 0)
		{
			if(LoginCardSect(sect, card_key, CARD_KEY_B, card_type) != 0)
			{	// ����һ�����ȵĻ���, ���7��������15���������˿��ͷϵ���, ��д7������15����
				if (sect == pri_sect)
				{
					if (SMT_LoginWorkKeySector(NULL, NULL, NULL, NULL))
					{
						ret = 10;		// �������ȵĻ��� 
					}
					else
					{
						ret = 11;		// �Ѿ���ʼ������
					}
					continue ;
				}
				else
				{
					sprintf(msg,"��¼����%d����ʧ��",sect);
					return -1;	
				}	
			}
			else
			{
				continue ; 
			}
		}
		//////////////////////////////////////////////////////////////////////////
		memcpy(buf,card_key,sizeof(card_key));
		memcpy(buf+6,CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
		memcpy(buf+10,card_key,sizeof(card_key));
		// д������Ϣ
		SMT_WriteBlock(sect, 3, buf);
		/*
		if ( LoginCardSect(sect,card_key,CARD_KEY_A,card_key) != 0 )
		{
			sprintf(msg,"���Ե�%d������¼ʧ��!\nд����%d������Կʧ��!"
				,sect,sect);
			MessageBox(NULL, msg, NULL, NULL);
			return -1;
		}
		*/
		if (LoginCardSect(sect,card_key,CARD_KEY_A,card_type) != 0)
		{
			// ��½�˹�����Կ����
			if (!SMT_LoginWorkKeySector(NULL, NULL, NULL, NULL))
			{
				sprintf(msg,"���Ե�%d������¼ʧ��!\nд����%d������Կʧ��!"
					,sect,sect);
				return -1;
			}
		}
		//////////////////////////////////////////////////////////////////////////
	}
	return ret;
}

/** 
 * @brief ������Ȩ��CRCУ��ֵ
 * 
 * @param keya - ��Ȩ����Կ����KEYA
 * @param keyb - ��Ȩ����Կ����KEYB
 * @param sect - ��Ȩ����Կ������
 * @param block - ��Ȩ����Կ���
 * @param pos -   ��Ȩ����Կ����ʼλ��
 * 
 * @return - ����CRCУ��ֵ 
 */
static long CalAuthCardCRC(BYTE keya[6],BYTE keyb[6],int sect,int block,int pos)
{
	BYTE buf[17] = "";
	long crc;
	int i;
	memcpy(buf,keyb,CARD_KEY_LEN);
	i = sprintf((char*)buf+CARD_KEY_LEN,"%c%c%02X",
		block+0x30,pos+0x30,sect);
	i += CARD_KEY_LEN;
	memcpy((char *)buf + i,keya,CARD_KEY_LEN);
	// ����У��λ
	crc = get_check_char(buf);
	return crc;
}

/** 
 * @brief ������Ȩ��������Կ����
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
static int ResetAuthCardKeySeed()
{
	int i;
	srand((unsigned)time( NULL ));
	for(i = 0;i < sizeof(AUTH_CARD_SEED);++i)
	{
		AUTH_CARD_SEED[i] = rand() % 255;
	}
	return 0;
}

/** 
 * @brief ��ӿں�����������Ȩ��
 * 
 * @param main_key - ��Ȩ��Կ
 * @param pri_sect - ��Ȩ��Կ��������
 * @param pri_block- ��Ȩ��Կ���ڿ��
 * @param pri_startpos - ��Ȩ��Կ��ʼλ��
 * @param flag - ��Ȩ�������־����־���ݼ���Ȩ���ṹ�ĵ�
 * @param lpCallBack - �ص�����������ʱ���ã�����ΪNULL
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
int __stdcall NewAuthCard(BYTE main_key[8],int pri_sect
								   ,int pri_block,int pri_startpos
								   ,int flag,LPProcessCallBack lpCallBack)
{
	// ������Ȩ��
	// modify by Cash 2005-8-8
	// Ϊ��Ȩ�������˱�־λ
	if((pri_sect == 7) || (pri_sect == 15 ) 
		|| (pri_sect == 30) || (pri_sect < 1)
		|| (pri_sect > 31)
		||(pri_block < 0) || (pri_block > 2)
		||(pri_startpos < 0) || (pri_startpos > 7))
	{
		return -1;
	}
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key[6] = "";
	BYTE buf[17] = "";
	long crc;
	short sect;
	if( SMT_RequestCardExist(card_id,card_type) != 0 )
	{
		return -1;
	}
	// ������Կ
	BYTE auth_key[8] = "";
	if( decrypt_work_key(main_key,auth_key) != 0)
	{
		return -1;
	}
	// ��ʼ����������
	if( NewAuthCard_Init_Sect(card_id,card_type,lpCallBack) != 0)
	{
		return -1;
	}
	ResetAuthCardKeySeed();
	BYTE auth_key_a[6] = "";
	BYTE auth_key_b[6] = "";
	if(gen_auth_card_keyA(AUTH_CARD_SEED,auth_key_a) != 0 )
	{
		return -2;
	}
	if(gen_auth_card_keyB(AUTH_CARD_SEED,auth_key_b) != 0)
	{
		return -2;
	}
	if( lpCallBack )
		lpCallBack(0);
	//////////////////////////////////////////////////////////////////////////
	// �� 7 ����
	sect = 7;
	memset(buf,0,sizeof(buf));
	memcpy(buf,auth_key_b,sizeof(auth_key_b));
	sprintf((char*)buf+6,"%01X",pri_block);
	//buf[6] = (char)pri_block;
	sprintf((char*)buf+7,"%01X",pri_startpos);
	//buf[7] = (char)pri_startpos;
	memcpy(card_key,card_id,sizeof(card_id));
	sprintf((char*)card_key+4,"%02X",sect);
	if(LoginCardSect(sect,card_key,CARD_KEY_A,card_type) !=0)
	{
		return -2;
	}
	if( SMT_WriteBlock(sect,1,buf) !=0 )
	{
		return -3;
	}
	if( lpCallBack )
		lpCallBack(0);
	//////////////////////////////////////////////////////////////////////////
	// �� 15 ����
	sect = 15;
	memset(buf,0,sizeof(buf));
	memcpy(buf+8,auth_key_a,sizeof(auth_key_a));
	sprintf((char*)buf+14,"%02X",pri_sect);
	
	memcpy(card_key,card_id,sizeof(card_id));
	sprintf((char*)card_key+4,"%02X",sect);
	
	if(LoginCardSect(sect,card_key,CARD_KEY_A,card_type) !=0)
	{
		return -2;
	}
	if( SMT_WriteBlock(sect,2,buf) !=0 )
	{
		return -3;
	}
	if( lpCallBack )
		lpCallBack(0);
	//////////////////////////////////////////////////////////////////////////
	// дУ��λ
	sect = 30;
	memset(buf,0,sizeof(buf));
	sprintf((char*)card_key+4,"%02X",sect);
	if(LoginCardSect(sect,card_key,CARD_KEY_A,card_type) !=0)
	{
		return -2;
	}
	crc = CalAuthCardCRC(auth_key_a,auth_key_b,pri_sect,pri_block,pri_startpos);
	buf[11] = (unsigned char)crc;
	if(SMT_WriteBlock(sect,0,buf) != 0)
	{
		MessageBox(NULL, "дУ��λʧ��", NULL, NULL);
	}
	//////////////////////////////////////////////////////////////////////////
	// �� pri_sect ����
	sect = pri_sect;
	memset(buf,0,sizeof(buf));
	memcpy(buf+pri_startpos,auth_key,sizeof(auth_key));
	// modify by Cash 2005-8-8
	// ���ӿ��Ʊ�־λ
	*(buf+pri_startpos+sizeof(auth_key)) = (BYTE)flag;
	sprintf((char*)card_key+4,"%02X",sect);
	// д��Կ
	if(LoginCardSect(sect,card_key,CARD_KEY_A,card_type) !=0)
	{
		return -2;
	}
	if( SMT_WriteBlock(sect,pri_block,buf) !=0 )
	{
		return -3;
	}
	// д����λ
	memset(buf,0,sizeof(buf));
	memcpy(buf,auth_key_a,sizeof(auth_key_a));
	memcpy(buf+sizeof(auth_key_a),CARD_INIT_CTRL_BIT,
		sizeof(CARD_INIT_CTRL_BIT));
	memcpy(buf+sizeof(auth_key_a)+sizeof(CARD_INIT_CTRL_BIT),
		auth_key_b,sizeof(auth_key_b));
	
	if( SMT_WriteBlock(sect,3,buf) != 0)
	{
		return -3;
	}	
	/*
	if( !Read_Author_Key() )
	{
		AfxMessageBox("��ʼ����Ȩ��ʧ�ܣ�");
		return -4;
	}
	*/
	return 0;
}

/** 
 * @brief ��ӿں�����ʹ����ԿΪ����Ȩ
 * 
 * @param main_key - ��Ȩ��Կ������Ϊ8�ֽ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
int __stdcall SetCardMainKey(BYTE main_key[8])
{
	if(!Is_Com_open())
	{
		return -1;
	}
	memcpy(CARD_MAIN_KEY,main_key,sizeof(CARD_MAIN_KEY));
	SMT_AutoDll(CARD_MAIN_KEY);
	SMT_ControlBuzzer();
	has_read_main_key = TRUE;
	return 0;
}

/** 
 * @brief ��ӿں�������⿨����--�㿨, ��ʼ�����Ŀ�, ����ʶ��Ŀ�
 * 
 * @param ��
 * 
 * @return - ����1��ʾ�㿨��2��ʾ��ʼ�����Ŀ�, 3��ʾ����ʶ��Ŀ�
 */

int __stdcall SMT_CheckForCard()
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key_b[7] = "";
	BYTE buf[16] = "";
	int current_key;
	BOOL login_sect_succ = FALSE;
	
	//CardKeyData card_key[2];
	int nFirstSect = 0;
	if (!Is_Com_open())
	{
		return -1;
	}
	if (FALSE == Read_Author_Key())
	{
		return -1;
	}
	if (SMT_RequestCardExist(card_id, card_type))
	{
		return -1;
	}

	if (gen_user_card_keyB(SMT_UCWORKINGKEY, card_id, card_key_b) != 0)
	{
		return -1;
	}

	if (0 == LoginCardSect(nFirstSect, CARD_INIT_KEY, CARD_KEY_A, card_type))
	{
		return BARE_CARD_TYPE;
	}
	current_key++;
	if (0 == LoginCardSect(nFirstSect, card_key_b, CARD_KEY_B, card_type))
	{
		return INIT_CARD_TYPE;
	}
	return UNRECOGNISE_CARD_TYPE;
}

/** 
 * @brief ��ӿں�������ֵƽ̨���Ǯ���û�
 * 
 * @param ucCardNo ѧ����, ucCardReadKey ��½��ֻ��KEY
 * 
 * @return - ����0��ʾ���ɹ�, ����-1��ʾǮ��������ʹ��, -2��ʾǮ��������, -3��ʾ��½����ʧ��, -4����������
 */
int __stdcall SMT_CheckForMoneyPacket()
{
	int ret = -100; 
	int sector = 0; 
	int	nPacketNo = 1;
	unsigned char ucBuffer[16] = "";
	unsigned char ucBuf1[16] = "",
				  ucBuf2[16] = "";
	unsigned char ucCheck = 0;
	int i;
	ret = Login_Card_Keya(3);
	if(ret != 0)	
		return -3;
	ret = SMT_ReadBlock(3, 0, ucBuffer);
	if(ret != 0)	
		return -4;
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
		return -1; // Ǯ��������ʹ��
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������
	ret = Login_Card_Keya(sector);
	if(ret != 0)
		return -3;
	ret = SMT_ReadBlock(sector, 0, ucBuf1);
	if(ret != 0)	
		return -2;	// �����ȡǮ������
	for(i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck != ucBuf1[15])
	{
		ret = SMT_ReadBlock(sector, 2, ucBuf2);	// ��ȡ����Ǯ��
		if(ret != 0)	
			return -2;  // �����ȡǮ������
		ucCheck = 0;
		for(i = 0; i < 15; i++)
		{
			ucCheck += ucBuf2[i];
		}
		if(ucCheck != ucBuf2[15])	
			return -2;	// ��ȡǮ����ʽ����
	}
	return 0;
}

/** 
 * @brief ��ӿں������ϴ�14����д��ѧ����
 * 
 * @param ucCardNoѧ����, ucCardWriteKey��½�Ŀ�дKEY
 * 
 * @return - ����0��ʾд����ȷ, �����ʾʧ��
 */
int __stdcall SMT_WriteCardNoFor14(unsigned char ucCardNo[20], unsigned char ucCardWriteKey[6])
{
	int ret = -5;
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	ret = MF_ReadSeriesNo(ucSerialNo);
	if (ret < 0)
	{
		return -1;	//��Ƭ���ڸ�Ӧ��
	}
	ret = SMT_Login_With_UserKey(14, ucCardWriteKey, 1);
	if (ret != 0)
	{
		return -2;	// ��Կ��½����
	}
	memcpy(ucBuffer, ucCardNo, 16);
	ret = SMT_WriteBlock(14, 1, ucBuffer);
	if (ret != 0)	
	{
		return -3;  // д���14����, 1���ѧ����ǰ16λ����
	}
	memset(ucBuffer, 0xFF, 16);
	memcpy(ucBuffer, ucCardNo + 16, 4);
	ret = SMT_WriteBlock(14, 2, ucBuffer);
	if(ret != 0)	
	{
		return -4;	// д���14����, 2���ѧ���ź�4λ����
	}
	return 0;
}

/** 
 * @brief ��ӿں������ϴ�14������ȡѧ����
 * 
 * @param ucCardNo ѧ����, ucCardReadKey ��½��ֻ��KEY
 * 
 * @return - ����0��ʾд����ȷ, �����ʾʧ��
 */
int __stdcall SMT_ReadCardNoFor14(unsigned char ucCardNo[20], unsigned char ucCardReadKey[6])
{
	int ret = -5;
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	ret = MF_ReadSeriesNo(ucSerialNo);
	if (ret < 0)
	{
		return -1;	//��Ƭ���ڸ�Ӧ��
	}
	ret = SMT_Login_With_UserKey(14, ucCardReadKey, 0);
	if (ret != 0)
	{
		return -2;	// ��Կ��½����
	}
	ret = SMT_ReadBlock(14, 1, ucBuffer);
	if (ret != 0)
	{
		return -3;	// ��ȡ���ݴ���
	}
	memcpy(ucCardNo, ucBuffer, 16);
	memset(ucBuffer, 0x00, 16);
	ret = SMT_ReadBlock(14, 2, ucBuffer);
	if (ret != 0)
	{
		return -4;	// ��ȡ���ݴ���
	}
	memcpy(ucCardNo + 16, ucBuffer, 4);
	return 0;
}

/************************************************************************/
/* ����Ȩ��������������                                                 */
/************************************************************************/
/** 
 * @brief ��ӿں������ϴ��·�����Ȩ��
 * 
 * @param main_key - ��Ȩ��Կ
 * @param pri_sect - ��Ȩ��Կ��������
 * @param pri_block- ��Ȩ��Կ���ڿ��
 * @param pri_startpos - ��Ȩ��Կ��ʼλ��
 * @param flag - ��Ȩ�������־����־���ݼ���Ȩ���ṹ�ĵ�
 * @param lpCallBack - �ص�����������ʱ���ã�����ΪNULL
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
int __stdcall InitNewAuthCard(BYTE main_key[8], BYTE flag, LPProcessCallBack lpCallBack)
{
	// �����еĻ�ȡ������Կ������, ����, ��ʼλ��д��. 27����, ��0, ��4���ֽڿ�ʼ
	// ��������Ȩ��
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key[6] = "";
	BYTE buf[17] = "";
	BYTE ucCryptWorkKey[17] = "";
	int ret = 0;
	long crc;
	short sect;
	int nPri_sect = 27;
	if(SMT_RequestCardExist(card_id,card_type) != 0)
	{
		return -1;
	}
	// ������Կ
	BYTE auth_key[8] = "";
//	BYTE auth_key[8] = {0x43, 0x44, 0x33, 0x45, 0x39, 0x41, 0x38, 0x46};
//	BYTE auth_key[8] = {0x8E, 0x8B, 0xFC, 0x8F, 0xF6, 0x8F, 0xF4, 0x88};
	ResetAuthCardKeySeed();
 	BYTE auth_key_a[6] = "";
 	BYTE auth_key_b[6] = "";
 	if( gen_auth_card_keyA(AUTH_CARD_SEED,auth_key_a) != 0 )
 	{
 		return -6;
 	}
 	if(gen_auth_card_keyB(AUTH_CARD_SEED,auth_key_b) != 0)
 	{
 		return -6;
 	}
	// ����������Կ
	encrypt_work_key(main_key, auth_key);

	// ��ʼ����������
	ret = NewAuthCard_Init_Sect(card_id, card_type, lpCallBack, nPri_sect);
	if (ret != 0 && ret != 10 && ret != 11)
	{
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	// �Ѿ���ʼ������
	if (11 == ret)
	{
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	if( lpCallBack )
		lpCallBack(0);
	
	//////////////////////////////////////////////////////////////////////////
	// �� 7 ����
	sect = 7;
	memset(buf, 0, sizeof(buf));
	memcpy(buf, auth_key_b, sizeof(auth_key_b));
	sprintf((char*)buf + 6, "%01X", 0);                  // ��0��
	//buf[6] = (char)pri_block;
	sprintf((char*)buf + 7, "%01X", 4);				     // ��4��λ��
	//buf[7] = (char)pri_startpos;
	memcpy(card_key, card_id, sizeof(card_id));
	sprintf((char*)card_key + 4, "%02X", sect);
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
		return -2;
	}
	if (SMT_WriteBlock(sect, 1, buf) != 0)
	{
		return -3;
	}
	if( lpCallBack )
		lpCallBack(0);
	//////////////////////////////////////////////////////////////////////////
	// �� 15 ����
	sect = 15;
	memset(buf, 0, sizeof(buf));
	memcpy(buf + 8, auth_key_a, sizeof(auth_key_a));
	sprintf((char*)buf + 14, "%02X", 27);
	
	memcpy(card_key, card_id, sizeof(card_id));
	sprintf((char*)card_key + 4, "%02X", sect);
	
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) !=0)
	{
		return -2;
	}
	if ( SMT_WriteBlock(sect, 2, buf) !=0 )
	{
		return -3;
	}
	if ( lpCallBack )
		lpCallBack(0);
	//////////////////////////////////////////////////////////////////////////
	// ��д������Կ����
	if (ret == 10)
	{
		goto L_END ;
	}
	//////////////////////////////////////////////////////////////////////////
	// дУ��λ
	sect = 30;
	memset(buf, 0, sizeof(buf));
	memcpy(card_key, card_id, sizeof(card_id));
	sprintf((char*)card_key + 4, "%02X", sect);
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) !=0)
	{
		return -2;
	}
	crc = CalAuthCardCRC(auth_key_a, auth_key_b, 27, 0, 4);
	buf[11] = (unsigned char)crc;
	if(SMT_WriteBlock(sect, 0, buf) != 0)
	{
		return -4;
	}
	//////////////////////////////////////////////////////////////////////////
	// �� pri_sect ����
	sect = 27;
	memset(buf, 0, sizeof(buf));
	memcpy(buf + 4, auth_key, sizeof(auth_key));
	// modify by Cash 2005-8-8
	// ���ӿ��Ʊ�־λ
	*(buf + 4 + sizeof(auth_key)) = flag;
	sprintf((char*)card_key + 4, "%02X", sect);
	// д��Կ
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
		return -2;
	}
	if (SMT_WriteBlock(sect, 0, buf) != 0)
	{
		return -3;
	}

	//////////////////////////////////////////////////////////////////////////
	// д����λ
	memset(buf, 0, sizeof(buf));
	memcpy(buf, auth_key_a, sizeof(auth_key_a));
	memcpy(buf + sizeof(auth_key_a), CARD_INIT_CTRL_BIT,
		sizeof(CARD_INIT_CTRL_BIT));
	memcpy(buf + sizeof(auth_key_a) + sizeof(CARD_INIT_CTRL_BIT),
		auth_key_b, sizeof(auth_key_b));
	
	if (SMT_WriteBlock(sect, 3, buf) != 0)
	{
		return -3;
	}

	//////////////////////////////////////////////////////////////////////////
	// ��0������2��Ҫ��ӿ���λ��־
	sect = 0;
	memset(buf, 0, sizeof(buf));
	memcpy(card_key, card_id, sizeof(card_id));
	sprintf((char*)card_key + 4, "%02X", sect);
	buf[11] = flag;
	
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) !=0)
	{
		return -2;
	}
	
	if (SMT_WriteBlock(sect, 2, buf) != 0)
	{
		return -3;
	}
	
L_END:
	return 0;
}

/** 
 * @brief ��ӿں�������������Ȩ������
 * 
 * @return - �ɹ�����0��ʧ�ܷ��ظ���
 */
int __stdcall ResetNewAuthCard(int * err_code, LPProcessCallBack lpCallBack)
{
	// ����������ʱд����
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key[7] = "";
	BYTE buf[17] = "";
	BYTE tmpBuf[17] = "";
	BYTE priKeyA[7] = "";
	BYTE priKeyB[7] = "";
	BYTE tmpSect[3] = "";
	char tmp[3] = "";
	short priBlock = -1, 
		  priStartPos = -1, 
		  priSect = -1;
	unsigned short sect;

	if( !Is_Com_open() )
	{
		* err_code = E_COM_NOT_OPEN;
		return -1;
	}

	if(SMT_RequestCardExist(card_id, card_type) != 0)
	{
		* err_code = E_READ_CARD_ID_ERROR;
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	// ��ȡ 7 ����
	sect = 7;
	memset(card_key, 0, sizeof(card_key));
	memcpy(card_key, card_id, sizeof(card_id));
	// �� ID Ϊ 4 λ
	sprintf((char*)card_key + 4, "%02X", sect);
	
	// ��ȡ Key B
	if( LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
		*err_code = E_CARD_LOGIN_ERROR;
		return -2;
	}
	if( SMT_ReadBlock(sect, 1, buf) != 0)
	{
//		MessageBox(NULL, "��ȡ����ʧ�ܣ�", "", NULL);
		* err_code = E_CARD_WRITE_ERROR;
		return -3;
	}
	// key b
	memcpy(priKeyB, buf, CARD_KEY_LEN);
	// block
	priBlock = buf[6] - '0';
	if( priBlock < 0 || priBlock > 2)
	{
//		MessageBox(NULL, "���ݲ��Ϸ���", "", NULL);
		* err_code = E_INVALID_CARD;
		return -3;
	}
	// start pos
	// priStartPos = char2int((const char*)&buf[7],1,true);
	tmp[0] = buf[7];
	priStartPos = (short)strtoul(tmp, NULL, 16);
	if( priStartPos < 0 || priStartPos > 10)
	{
//		MessageBox(NULL, "���ݲ��Ϸ���", "", NULL);
		* err_code = E_INVALID_CARD;
		return -3;
	}
	//////////////////////////////////////////////////////////////////////////
	// �� 15 ����
	sect = 15;
	memset(card_key, 0, sizeof(card_key));
	memcpy(card_key, card_id, sizeof(card_id));
	// �� ID Ϊ 4 λ
	sprintf((char*)card_key + 4, "%02X", sect);
	// ��ȡ Key a
	if( LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
//		MessageBox(NULL, "��¼����ʧ�ܣ�", "", NULL);
		* err_code = E_CARD_LOGIN_ERROR;
		return -2;
	}
	if( SMT_ReadBlock(sect, 2, buf) != 0)
	{
//		MessageBox(NULL, "��ȡ����ʧ�ܣ�", "", NULL);
		* err_code = E_CARD_WRITE_ERROR;
		return -3;
	}
	// key a
	strncpy((char*)priKeyA, (char*)buf + 8, CARD_KEY_LEN);
	// private key section no
	priSect = (short)strtoul((char*)buf + 14, NULL, 16);
	//////////////////////////////////////////////////////////////////////////
	// ���ɳ�ʼ״̬
	memset((char*)buf, 255, sizeof(buf) - 1);
	strncpy((char*)buf + sizeof(CARD_INIT_KEY), (char*)CARD_INIT_CTRL_BIT, sizeof(CARD_INIT_CTRL_BIT));
	
	if(lpCallBack)
		lpCallBack(0);
	bool isClear = false;
	// ������Կ����
	if(LoginCardSect(priSect, priKeyA, CARD_KEY_A, card_type) == 0)
	{
		memset(tmpBuf, 0, sizeof(tmpBuf));
		// ����Ȩ������Կ��������
		if(SMT_WriteBlock(priSect, priBlock, tmpBuf) != 0)
		{
			isClear = false;
			goto L_TRY_KEY_B;
		}
		// д����λ����
		strncpy((char*)tmpBuf, (char*)buf, sizeof(tmpBuf));
		if(SMT_WriteBlock(priSect, 3, tmpBuf) != 0)
		{
			// д��ʧ�ܣ�ʹ��Key B ����
			isClear = false;
		}
		else
			isClear = true;	
	}
L_TRY_KEY_B:
	if(lpCallBack)
		lpCallBack(0);
	if(!isClear)
	{
		// �� key B ����
		if (LoginCardSect(priSect, priKeyB, CARD_KEY_B, card_type) == 0)
		{
			memset(tmpBuf, 0, sizeof(tmpBuf));
			
			if (SMT_WriteBlock(priSect, priBlock, tmpBuf) != 0)
			{
//				MessageBox(NULL, "д��������ʧ�ܣ�", "", NULL);
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			// д����λ����
			strncpy((char*)tmpBuf, (char*)buf, sizeof(tmpBuf));
			if(SMT_WriteBlock(priSect, 3, tmpBuf) != 0)
			{
				// key B Ҳ�޷�д��
//				MessageBox(NULL, "д��������ʧ�ܣ�", "", NULL);
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			
		}
		else
		{
			// �޷��� key b ��¼��
//			MessageBox(NULL, "��¼����ʧ�ܣ�", "", NULL);
			*err_code = E_CARD_LOGIN_ERROR;
			return -1;
		}
	}

	// �����Ƿ���ճɹ�
	if( LoginCardSect(priSect, CARD_INIT_KEY, CARD_KEY_A, card_type) != 0)
	{
//		MessageBox(NULL, "��������ʧ�ܣ�", "", NULL);
		* err_code = E_CARD_WRITE_ERROR;
		return -2;
	}
	char msg[128] = "";
	// ��������ݵ�0, 1, 2����
	if (SMT_ClearAuthCard() != 0)
	{
		*err_code = E_CARD_WRITE_ERROR;
		return -2;
	}
	for(sect = 0; sect < AUTH_CARD_SECT_NO; ++sect)
	{
		if(lpCallBack)
			lpCallBack(0);
		// ��Կ�������ó�ʼ��
		if( sect == priSect)
			continue;
		memset(card_key, 0, sizeof(card_key));
		memcpy(card_key, card_id, sizeof(card_id));
		// �� ID Ϊ 4 λ
		sprintf((char*)(card_key + 4), "%02X", sect);
		
		if( LoginCardSect(sect, card_key
				,CARD_KEY_A, card_type) == 0)
		{
			strncpy((char*)tmpBuf, (char*)buf, sizeof(tmpBuf));
			// ��¼�ɹ�
			// ���տ���λ
			if( SMT_WriteBlock(sect, 3, tmpBuf) != 0)
			{
				sprintf(msg, "����[%d]����ʧ�ܣ�", sect);
//				MessageBox(NULL, msg, "", NULL);
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			// ��Key A ��¼����
			if( LoginCardSect(sect, CARD_INIT_KEY, CARD_KEY_A, card_type) != 0)
			{
				sprintf(msg, "���Ե�¼%d����ʧ�ܣ�", sect);
//				MessageBox(NULL, msg, "", NULL);
				* err_code = E_CARD_LOGIN_ERROR;
				return -1;
			}
		}
		else if( LoginCardSect(sect, CARD_INIT_KEY, CARD_KEY_A, card_type) == 0)
		{
			// ʹ�� ��ʼ�� ��Կ���е�¼����
			sprintf(msg,"����%dʹ�ó�ʼ��Կ��¼�ɹ���\n�Ƿ�������գ�",sect);
			if (MessageBox(NULL, msg, "", MB_OKCANCEL) == IDCANCEL)
			{
				// �������������,�򷵻�
				* err_code = E_CARD_LOGIN_ERROR;
				return -2;
			}
		}
		else
		{
			sprintf(msg,"��¼����%d����ʧ��",sect);
//			MessageBox(NULL, msg, "", NULL);
			* err_code = E_CARD_LOGIN_ERROR;
			return -2;
		}
	}
	SMT_ControlBuzzer();
	return 0;
}

// ��½��Ȩ������, ʹ��KEYA��½
static int Login_Auth_Card(int sector)
{
	unsigned char ucSerialNo[5] = "";
	unsigned char ucCard_key[6] = "";
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;	// ��Ƭ���ڸ�Ӧ��
	memcpy(ucCard_key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_key + 4, "%02X", sector);
	ret = SMT_Login_With_UserKey(sector, ucCard_key, 0);                     
	if(ret != 0)
	{
		return -2;	// ��Ƭ��½ʧ��
	}
	return 0;
}

// ������Ȩ��
int __stdcall PublishAuthCard(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	BOOL bPersonalFlag = TRUE;
	BOOL bStateFlag = TRUE;
	BOOL bBankInfo = TRUE;
	BOOL bPacketFlag[8] = {TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE};
	int iCardNo[1];
	memset(ucBcdShowCardNo, 0, sizeof(ucBcdShowCardNo));

/*
	ret = ifAuthorReadyOK();
	if (ret !=0)
		return ret;				// �����Ȩ���Ƿ��������½, ������Կ�ֳ�, �Ժ��н�����Ȩ������Կ��õ�½
*/
/*
	ret = SMT_ClearAuthCard();
	if(ret)
	{
		SetErrMsg(ret,"��ʽ����ʧ��");
		return ret;
	}
*/
	ret = strlen((char*)pc->ShowCardNo);
	if(10 == ret)	
	{
		//ת��ΪBCD��
		dec2bcd(pc->ShowCardNo,ucBcdShowCardNo,5);
	}
	//ת��Ϊ����
	char sYear[3];
	char sMon[3];
	char sDay[3];
	
	memset(sYear, 0, sizeof(sYear));
	memset(sMon, 0, sizeof(sMon));
	memset(sDay, 0, sizeof(sDay));

	memcpy(sYear, pc->DeadLineDate + 2, 2);
	memcpy(sMon, pc->DeadLineDate + 4, 2);
	memcpy(sDay, pc->DeadLineDate + 6, 2);
	
	ucDeadLineDate[0] = atoi(sYear);
	ucDeadLineDate[1] = atoi(sMon);
	ucDeadLineDate[2] = atoi(sDay);
	iCardNo[0] = atoi((char*)pc->CardNo);
	ucCardRightType[0] = pc->CardRightType;
	// дһ�����ĸ�����Ϣ, ���º�����������, ������
	ret = SMT_WriteAuthCardStateInfo(ucBcdShowCardNo, iCardNo, ucDeadLineDate, ucCardRightType); 
	if(ret)
	{
		SetErrMsg(ret,"д��������Ϣʧ��");
		return ret;           //д������Ϣ����
	}
	
	// д�ֶ�����������Ϣ, ���º�������, ������
	ret = SMT_WriteAuthPersonalInfo(pc->ucName,
									pc->ucDutyNo,
									pc->ucCertificateNo,
									pc->ucDepartmentNo,
									pc->ucIdentifyNo,
									pc->ucSexNo,
									pc->ucCardNo);
	if(ret)
	{
		SetErrMsg(ret,"д������Ϣʧ��");
		return ret;           //
	}
	ret = SMT_WriteAuthorNo(pc->ucLibraryNo);
	if (ret)
	{
		SetErrMsg(ret, "д����Ա��ʧ��");
		return ret;
	}
	ret = WriteAuthCardPwd(pc->ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"д������ʧ��");
		return ret;
	}
	ret = SMT_InitAuthBlackCardFlag();
	if (ret)
	{
		SetErrMsg(ret, "��ʼ���ڿ����ʧ��");
		return ret;
	}
	//Ԥ����
/*
	unsigned short int PacketNo = 1;
	int Money;
	Money = pc->Money;
	ret = SMT_PacketSetMoney(PacketNo,Money);
	if(ret)
	{
		SetErrMsg(ret,"����Ǯ�����ʧ��");
		return ret;		
	}
*/
	SMT_ControlBuzzer();		
	return 0;
}

int __stdcall SMT_ClearAuthCard()
{
	unsigned char ucSerialNo[5] = "";
	unsigned char ucRawData[256] = "";
	unsigned char ucCard_key[6] = "";
	int nSector, 
		nBlock, 
		startSector = 4;
	int ret = 0;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	memcpy(ucCard_key, ucSerialNo, sizeof(ucSerialNo));
	//1��ʹ�ó��������½��Ƭ  ǰ32������
	for(nSector = 0; nSector < 12; nSector++)
	{
		sprintf((char*)ucCard_key + 4, "%02X", nSector);
		if(nSector == 3)
			continue;
		ret = SMT_Login_With_UserKey(nSector, ucCard_key, 0);
		if(ret != 0)
			return -2; //�ǳ�����
		for(nBlock = 0; nBlock < 3; nBlock++)
		{
			if(nSector == 0 && nBlock == 0)
				continue;
			if(nSector == 1 && nBlock == 0)
			{
				//  ����ǵ�1������0�飬��ȡ��ʾ���ţ���Ҫɾ��������
				ret = SMT_ReadBlock(nSector, nBlock, ucRawData);
				if(ret)
					return -3;
				// �������ʾ�����������������
				memset(ucRawData, 0x00, 7);
				memset(ucRawData + 12, 0x00, 4);
			}
			else
			{
				memset(ucRawData, 0x00, 16);
			}
			ret = SMT_WriteBlock(nSector, nBlock, ucRawData);
			if(ret)
				return -3;
		}
	}
	memset(ucRawData,0xFF,16);
	nBlock = 0;
	for(nSector = 0; nSector < 4; nSector++)
	{
		// ʹ��1, 2, 3, 4��Ǯ������, ͬʱ��¼ʹ��Ǯ����������
		ucRawData[nBlock] = 0x00;
		nBlock++;
		ucRawData[nBlock] = startSector;                        // ע��ֻ�ܸĵ��ĸ�
		startSector += 1;
		nBlock++;
	}
	sprintf((char*)ucCard_key + 4, "%02X", 3);
	//1 ʹ���û������½
	ret = SMT_Login_With_UserKey(3, ucCard_key, 0);
	if(ret != 0)
		return -4;//ʹ���û�����KEYA���ܵ�½
	ret = SMT_WriteBlock(3, 0, ucRawData);
	if(ret != 0)
		return -5;//�޷�д��
	memset(ucRawData, 0xFF, 16);

	for(nSector = 0; nSector < 4; nSector++)
	{
		// 1, 2, 3, 4��Ǯ��������Ϣ���ڵ�����
		ucRawData[nSector] = startSector;
		startSector++;
	}
	ret = SMT_WriteBlock(3, 1, ucRawData);
	if(ret != 0)
		return -6;//�޷�д��
	// ���պ��ɺڿ�, ��ѧ���ź�����λҲ���
	memset(ucRawData, 0x00, 16);  
//	ucRawData[4] = 0xFF;
	sprintf((char*)ucCard_key + 4, "%02X", 0);
	ret = SMT_Login_With_UserKey(0, ucCard_key, 0);
	if(ret != 0)
		return -4;//ʹ���û�����KEYA���ܵ�½
	ret = SMT_WriteBlock(0, 2, ucRawData);
	if(ret != 0)
		return -7;//�޷�д��
	return 0;	
}

// ��������: ��ʼ��ʱ������Ȩ�����������, ��ͷ���ַ��ڿ�Ϊ00, �׿�ΪFF
// ��������: ��
int __stdcall SMT_InitAuthBlackCardFlag()
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	unsigned char ucCard_Key[6] = "";
	/*
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	memcpy(ucCard_Key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_Key + 4, "%02X", 0);
	ret = SMT_Login_With_UserKey(0, ucCard_Key, 0);
	*/
	ret = Login_Auth_Card(0);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(0, 2, ucBuffer);
	if (ret != 0)
		return ret;
	ucBuffer[4] = 0xFF;					// �׿�
	memset(ucBuffer + 5, 0x00, 6);		// ����6���ֽ���0 
	ret = SMT_WriteBlock(0, 2, ucBuffer);
	if(ret != 0)	
		return -6;
	return 0;
}

// ��������: ������Ȩ���������汾��, ��ͷ���ַ��ڿ�Ϊ00, �׿�ΪFF
// ��������: blkversion ��Ȩ���������汾
int __stdcall SMT_SetAuthNormalFlagByBlkVerion(char *auth_black_version)
{
	int ret;
	unsigned char ucBlkVer[12];
	unsigned char ucBuffer[16];
	ret = Login_Auth_Card(0);
	if (ret != 0)	
		return ret;
	if (strlen(auth_black_version) != 12)
	{
		return -1;	
	}
	dec2bcd((unsigned char*)auth_black_version, ucBlkVer, 6);
//	memset(ucBuffer, 0xFF, 16);
	if (ret = SMT_ReadBlock(0, 2, ucBuffer))
		return -3;

	memcpy(ucBuffer + 5, ucBlkVer, 6);
	ret = SMT_WriteBlock(0, 2, ucBuffer);
	if (ret != 0)	
		return -6;
	SMT_ControlBuzzer();
	return 0;
}

// ��������: д����Ȩ������Ա��������3���ֽ�, 6���ַ�
// ��������: ��Ȩ����������
int __stdcall SMT_WriteAuthPersonalPassword(unsigned char ucAuthPersonalPsd[3])
{
	int ret = 0;
	unsigned char ucBuffer[16];
	unsigned char ucSerialNo[5] = "";
	unsigned char ucCard_Key[6] = "";
	/*
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	memcpy(ucCard_Key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_Key + 4, "%02X", 1);
	ret = SMT_Login_With_UserKey(1, ucCard_Key, 0);
	*/
	ret = Login_Auth_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1, 1, ucBuffer);
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer, ucAuthPersonalPsd, 3);
	ret = SMT_WriteBlock(1, 1, ucBuffer);
	if(ret != 0)	
		return ret;
	return 0;
}

// ��������: д����Ȩ������Ա��������6���ַ�
// ��������: ��Ȩ����������
int __stdcall WriteAuthCardPwd(unsigned char ucAuthoPwd[6])
{
	int ret = 0;
	unsigned char ucPwd[3];
	dec2bcd(ucAuthoPwd, ucPwd, 3);
	ret = SMT_WriteAuthPersonalPassword(ucPwd);
	if(ret)
	{
		SetErrMsg(ret, "д������ʧ��");
		return ret;
	}
	return 0;
}

// ��������: д����Ȩ����״̬��Ϣ 
// ��������: ucShowCardNo(�û���ʾ����), nDealCardNo(�û����׿���), 
//			 ucDeadLineDate(���Ľ�ֹ����), ucCardRightType(�û���ʹ������Ȩ��)
int __stdcall SMT_WriteAuthCardStateInfo(unsigned char ucShowCardNo[5], 
										 int nDealCardNo[1], 
										 unsigned char ucDeadLineDate[3], 
										 unsigned char ucCardRightType[1])
{
	unsigned char ucCard_Key[6] = "";
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	int ret = 0;
	/*
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	memcpy(ucCard_Key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_Key + 4, "%02X", 1);
	ret = SMT_Login_With_UserKey(1, ucCard_Key, 0);
	*/
	ret = Login_Auth_Card(1);
	if(ret != 0)
		return -2;//��Ƭ��½ʧ��
	//��0��������֯
	if(nDealCardNo[0] > 0x0FFFFF)
		return -3;//���׿��Ź���
	memset(ucBuffer, 0xFF, 16);
	ucBuffer[0] = nDealCardNo[0] / 256 / 256;
	ucBuffer[1] = nDealCardNo[0] / 256;
	ucBuffer[2] = nDealCardNo[0] % 256;
	ucBuffer[3] = ucCardRightType[0];
	memcpy(ucBuffer + 4, ucDeadLineDate, 3);
	memcpy(ucBuffer + 7, ucShowCardNo, 5);
	ret = SMT_WriteBlock(1, 0, ucBuffer);
	if(ret != 0)
		return -5; //д��ʧ��
	return 0;							
}

// �������ã�д����Ȩ��Ƭ������Ϣ
// ��������: ucName(����), ucDutyNo(ְ�����), ucCertificateNo(֤������)
//			 ucDepartmentNo(���ű��), ucIdentifyNo(��ݴ���), ucSexNo(�Ա�), ucCardNo(ѧ����)
int __stdcall SMT_WriteAuthPersonalInfo(unsigned char ucName[8],
										unsigned char ucDutyNo[4],
										unsigned char ucCertificateNo[20],
										unsigned char ucDepartmentNo[10],
										unsigned char ucIdentifyNo[4],
										unsigned char ucSexNo[1],
										unsigned char ucCardNo[20])
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	unsigned char ucCard_Key[6] = "";
	/*
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	memcpy(ucCard_Key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_Key + 4, "%02X", 0);
	//����ѧ�Ų���
	ret = SMT_Login_With_UserKey(0, ucCard_Key, 0);
	*/
	ret = Login_Auth_Card(0);
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer, ucCardNo, 16);
	ret = SMT_WriteBlock(0, 1, ucBuffer);
	if(ret != 0)	
		return -5;
//	memset(ucBuffer, 0xFF, 16);
	if (ret = SMT_ReadBlock(0, 2, ucBuffer))
		return -4;
	memcpy(ucBuffer, ucCardNo + 16, 4);
	ret = SMT_WriteBlock(0, 2, ucBuffer);
	if (ret != 0)	
		return -5;

	//��2����0�����
	/*
	sprintf((char*)ucCard_Key + 4, "%02X", 2);
	ret = SMT_Login_With_UserKey(2, ucCard_Key, 0);
	*/
	ret = Login_Auth_Card(2);  
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer, ucName, 8);
	memcpy(ucBuffer + 8, ucDutyNo, 4);
	memcpy(ucBuffer + 12, ucCertificateNo, 4);
	ret = SMT_WriteBlock(2, 0, ucBuffer);
	if(ret != 0)	
		return -5;
	memcpy(ucBuffer,ucCertificateNo + 4, 16);
	ret = SMT_WriteBlock(2, 1, ucBuffer);
	if(ret != 0)	
		return -5;
	memcpy(ucBuffer, ucDepartmentNo, 10);
	memcpy(ucBuffer + 10, ucIdentifyNo, 4);
	memcpy(ucBuffer + 14, ucSexNo, 1);
	ret = SMT_WriteBlock(2, 2, ucBuffer);
	if(ret != 0)	
		return -5;
	return 0;
}

// ��������: д����Ա��10���ֽ�
// ��������: ����Ա��
int __stdcall SMT_WriteAuthorNo(unsigned char ucAuthorId[10])
{
	int ret;
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	unsigned char ucCard_Key[6] = "";
	/*
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	memcpy(ucCard_Key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_Key + 4, "%02X", 1);
	ret = SMT_Login_With_UserKey(1, ucCard_Key, 0);	
	*/
	ret = Login_Auth_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1, 1, ucBuffer);
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer + 3, ucAuthorId, 10);
	ret = SMT_WriteBlock(1, 1, ucBuffer);
	if(ret != 0)	
		return ret;
	return 0;
}

int __stdcall ReadAuthCardInfo(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];		//�û���ʹ�ý�ֹ����
	unsigned char ucCardRightType[1];		//Ȩ��λ
	int iCardNo[1];

	ret = SMT_ReadAuthCardStateInfo(ucBcdShowCardNo,iCardNo,ucDeadLineDate,ucCardRightType);
	if (ret !=0)
	{
		SetErrMsg(ret,"����������Ϣʧ��");
		return ret;    
	}
	bcd2dec(ucBcdShowCardNo,5,pc->ShowCardNo);
	//ת��hex���ڸ�ʽ��ʮ����
	sprintf((char*)pc->DeadLineDate,"20%02d%02d%02d",ucDeadLineDate[0],ucDeadLineDate[1],ucDeadLineDate[2]);
	sprintf((char*)pc->CardNo,"%d",iCardNo[0]);
	pc->CardRightType=ucCardRightType[0];
	ret = SMT_ReadAuthPersonalInfo(pc->ucName,pc->ucDutyNo,pc->ucCertificateNo,pc->ucDepartmentNo,pc->ucIdentifyNo,pc->ucSexNo,pc->ucCardNo);
	if (ret !=0)
	{
		SetErrMsg(ret,"����������Ϣʧ��");
		return ret;     
	}
	ret = SMT_ReadAuthPersonalPassword(pc->ucPwd);
	if (ret != 0)
	{
		SetErrMsg(ret, "��ȡ����Ա����ʧ��");
		return ret;
	}
	ret = SMT_ReadAuthorNo(pc->ucLibraryNo);
	if(ret)
	{
		SetErrMsg(ret,"дͼ��֤��ʧ��");
		return ret;
	}
	return 0;
}

// ��������: ��ȡ��Ȩ������Ա����
// ��������: ����Ա��������(6λ)
int __stdcall SMT_ReadAuthPersonalPassword(unsigned char PersonalPsd[6])
{
	int ret;
	unsigned char ucBuffer[16] = "";
	unsigned char ucTempPersonalPsd[16] = "";
	ret = Login_Auth_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1, 1, ucBuffer);
	if(ret != 0)	
		return -5;
	bcd2dec(ucBuffer, 3, ucTempPersonalPsd);
	memcpy(PersonalPsd, ucTempPersonalPsd, 6);
	return 0;
}

int __stdcall SMT_ReadAuthCardStateInfo(unsigned char ucShowCardNo[5],
										int nDealCardNo[1],
										unsigned char ucDeadLineDate[3],
										unsigned char ucCardRightType[1])
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	ret = Login_Auth_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1, 0, ucBuffer);
	if(ret != 0)
		return -6; //����ʧ��
	nDealCardNo[0] = ucBuffer[0]*256*256+ucBuffer[1]*256+ucBuffer[2];
	ucCardRightType[0] = ucBuffer[3];
	memcpy(ucDeadLineDate, ucBuffer + 4, 3);
	memcpy(ucShowCardNo, ucBuffer + 7, 5);
	return 0;
}

int __stdcall SMT_ReadAuthPersonalInfo(unsigned char ucName[8],
									   unsigned char ucDutyNo[4],
									   unsigned char ucCertificateNo[20],
									   unsigned char ucDepartmentNo[10],
									   unsigned char ucIdentifyNo[4],
									   unsigned char ucSexNo[1],
									   unsigned char ucCardNo[20])
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	//����ѧ�Ų���
	ret = Login_Auth_Card(0);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(0, 1, ucBuffer);
	if(ret != 0)	
		return -6;
	memcpy(ucCardNo, ucBuffer, 16);
	ret = SMT_ReadBlock(0, 2, ucBuffer);
	if(ret != 0)	
		return -6;
	memcpy(ucCardNo + 16, ucBuffer, 4);
	ret = Login_Auth_Card(2);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(2, 0, ucBuffer);
	if(ret != 0 )	
		return -6;
	memcpy(ucName, ucBuffer, 8);
	memcpy(ucDutyNo, ucBuffer + 8, 4);
	memcpy(ucCertificateNo, ucBuffer + 12, 4);
	ret = SMT_ReadBlock(2, 1, ucBuffer);
	if(ret != 0)	
		return -6;
	memcpy(ucCertificateNo + 4, ucBuffer, 16);
	ret = SMT_ReadBlock(2, 2, ucBuffer);
	if(ret != 0)	
		return -6;
	memcpy(ucDepartmentNo, ucBuffer, 10);
	memcpy(ucIdentifyNo, ucBuffer + 10, 4);
	memcpy(ucSexNo, ucBuffer + 14, 1);
	return 0;
}

// ��������: ��ȡ����Ա��10���ֽ�
// ��������: ����Ա��
int __stdcall SMT_ReadAuthorNo(unsigned char ucAuthorId[10])
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	ret = Login_Auth_Card(1);
	if(ret != 0)	
		return ret;
	//memset(ucBuffer,0xFF,16);
	ret = SMT_ReadBlock(1, 1, ucBuffer);
	if(ret != 0)
		return -5;
	memcpy(ucAuthorId, ucBuffer + 3, 10);
	return 0;
}

// ��ȡ��Ȩ���������б�汾
int __stdcall SMT_ReadAuthBlackNameListVersion(int *nflag, char *sVersion)
{
	int ret;
	unsigned char ucBuffer[16] = "";
	char sTempVersion[13] = "";
	ret = Login_Auth_Card(0);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(0, 2, ucBuffer);
	if(ret != 0)	
		return -6;
	if(0 == ucBuffer[0])
		*nflag = 1;		// �ڿ�
	else	
		*nflag = 0;		// �׿�
	dec2hex(ucBuffer + 1, 6, sTempVersion);
	strcpy(sVersion, sTempVersion);
	return 0;
}

int __stdcall ReadAuthCardBlock(int startSect, int endSect, short block, LPGetBlockData lpFunc)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key_a[7] = "";
	BYTE card_key_b[7] = "";
	BYTE buf[16] = "";
	int current_key, old_key;
	int nWorkKeySector = 0;
	BOOL login_sect_succ = FALSE;
	
	CardKeyData card_key[3];
	
	int sect = 0;
	// �жϴ򿪴���
	if (!Is_Com_open())
	{
		return -1;
	}
	// ��鿨�Ƿ����
	if ( SMT_RequestCardExist(card_id,card_type) != 0 )
	{
		return -1;
	}
	memcpy(card_key_a, card_id, sizeof(card_id));
	memcpy(card_key_b, card_id, sizeof(card_id));
	// ��ʼ�� key ������
	memset((void *)card_key,0,sizeof(card_key));
	card_key[0].flag = CARD_KEY_A;
	// ������Զ������պ��KEYA
	memcpy(card_key[0].key[CARD_KEY_A], CARD_INIT_KEY, sizeof(CARD_INIT_KEY));
	memcpy(card_key[0].key[CARD_KEY_B], CARD_INIT_KEY, sizeof(CARD_INIT_KEY));
	card_key[1].flag = CARD_KEY_A;
	// ������Ե�¼�� key ������
	current_key = 1;
	for(sect = startSect; sect < endSect + 1; ++sect)
	{
		
		sprintf((char*)card_key_a + 4, "%02X", sect);
		sprintf((char*)card_key_b + 4, "%02X", sect);
		memcpy(card_key[1].key[CARD_KEY_A], card_key_a, sizeof(card_key_a));
		memcpy(card_key[1].key[CARD_KEY_B], card_key_b, sizeof(card_key_b));
		// ���γ�ʼ��ÿ������
		old_key = current_key;
		login_sect_succ = FALSE;
		int key_idx = card_key[current_key].flag;
		// ���ҿ��Ե�¼�� key 
		while(TRUE)
		{
			// �����¼�ɹ� ����ѭ��
			if( LoginCardSect_2KEY(sect, &card_key[current_key], card_type) == 0)
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key++;
			if( current_key > 2 )
				current_key = 0;
			if (current_key == old_key)
			{	// ѭ����Կ��½����, �����ǲ�����Կ����
				if (SMT_LoginWorkKeySector(NULL, NULL, NULL, NULL) != 0)
				{
					login_sect_succ = FALSE;
				}
				else
				{
					login_sect_succ = TRUE;
				}
				break;
			}		
		}
		// �жϵ�ǰ�����Ƿ�ɹ���¼
		if (login_sect_succ == FALSE)
		{
			return -1;
		}
		// ��ȡ����������
		for(int b = 0;b < 4;++b)
		{
			if(block & (1 << b))
			{
				memset(buf, 0, sizeof(buf));
				if(SMT_ReadBlock(sect, b, buf) != 0)
				{
					return -1;
				}
				int key_idx = card_key[current_key].flag;
				// ���ö����ص�����
				if( lpFunc != NULL )
				{
					lpFunc(sect, b, buf,card_key[current_key].key[key_idx],key_idx);
				}
			}
		}
		
	}
	return 0;
}

int __stdcall SMT_LoginWorkKeySector(BYTE pri_key_a[6], BYTE pri_key_b[6], short *pri_sect, short *pri_block)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key[7] = "";
	BYTE buf[17] = "";
	BYTE tmpBuf[17] = "";
	BYTE priKeyA[7] = "";
	BYTE priKeyB[7] = "";
	BYTE tmpSect[3] = "";
	char tmp[3] = "";
	short priBlock, priStartPos, priSect;
	unsigned short sect;
	if (SMT_RequestCardExist(card_id, card_type) != 0)
	{
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	// ��ȡ 7 ����
	sect = 7;
	memset(card_key, 0, sizeof(card_key));
	memcpy(card_key, card_id, sizeof(card_id));
	// �� ID Ϊ 4 λ
	sprintf((char*)card_key + 4, "%02X", sect);
	
	// ��ȡ Key B
	if( LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
		return -2;
	}
	if( SMT_ReadBlock(sect, 1, buf) != 0)
	{
		return -3;
	}
	// key b
	memcpy(priKeyB, buf, CARD_KEY_LEN);
	// block
	priBlock = buf[6] - '0';
	if (priBlock < 0 || priBlock > 2)
	{
		return -3;
	}
	
	if (pri_block != NULL)
		*pri_block = priBlock;
	
	// start pos
	tmp[0] = buf[7];
	priStartPos = (short)strtoul(tmp, NULL, 16);
	if (priStartPos < 0 || priStartPos > 10)
	{
		return -3;
	}
	//////////////////////////////////////////////////////////////////////////
	// �� 15 ����
	sect = 15;
	memset(card_key, 0, sizeof(card_key));
	memcpy(card_key, card_id, sizeof(card_id));
	// �� ID Ϊ 4 λ
	sprintf((char*)card_key + 4, "%02X", sect);
	// ��ȡ Key a
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
		return -2;
	}
	if (SMT_ReadBlock(sect, 2, buf) != 0)
	{
		return -3;
	}
	// key a
	strncpy((char*)priKeyA, (char*)buf + 8, CARD_KEY_LEN);
	// private key section no
	priSect = (short)strtoul((char*)buf + 14, NULL, 16);
	if (LoginCardSect(priSect, priKeyA, CARD_KEY_A, card_type) != 0) 
//		|| LoginCardSect(priSect, priKeyB, CARD_KEY_B, card_type) != 0)
	{
		return -5;
	}

	if (pri_sect != NULL)
		*pri_sect = priSect;
	
	if (pri_key_a != NULL) 
		memcpy(pri_key_a, priKeyA, sizeof(priKeyA));
	
	if (pri_key_b != NULL)
		memcpy(pri_key_b, priKeyB, sizeof(priKeyB));

	return 0;	
}

int __stdcall SMT_ReadAuthorWorkKeyAndFlag(BYTE auth_work_key[8], BYTE *flag)
{
	BYTE priKeyA[7] = "";
	BYTE priKeyB[7] = "";
	short priSect = 0;
	short priBlock = 0;
	int ret = 0;
	BYTE buf[17] = "";

	if (ret = SMT_LoginWorkKeySector(priKeyA, priKeyB, &priSect, &priBlock))
		return ret;
	
	if (SMT_Login_With_UserKey(priSect, priKeyA, 0))
	{
		return -9;	// ��Ƭ��½ʧ��
	}

	if (SMT_ReadBlock(priSect, priBlock, buf) != 0)
	{
		return -10;
	}

	memcpy(auth_work_key, buf + 4, sizeof(BYTE) * 8);
	*flag = *(buf + 4 + sizeof(BYTE) * 8);
	return 0;
}

int __stdcall SMT_ModifyDeadLineDateAndFlag(BYTE DeadLineDate[8], BYTE flag)
{
	BYTE priKeyA[7] = "";
	BYTE priKeyB[7] = "";
	short priSect = 0;
	short priBlock = 0;
	int ret = 0;
	BYTE buf[17] = "";

	if (ret = SMT_LoginWorkKeySector(priKeyA, priKeyB, &priSect, &priBlock))
		return ret;

	if (SMT_Login_With_UserKey(priSect, priKeyA, 0))                     
		return -9;	// ��Ƭ��½ʧ��

	if (SMT_ReadBlock(priSect, 0, buf) != 0)
		return -10;

	*(buf + 4 + sizeof(BYTE) * 8) = flag;
	if (SMT_WriteBlock(priSect, priBlock, buf) != 0)
		return -11;
	
	//////////////////////////////////////////////////////////////////////////
	// д��ֹ����
	BYTE ucDeadLineDate[3] = "";
	BYTE ucBuffer[17] = "";
	char sYear[3];
	char sMon[3];
	char sDay[3];
	
	memset(sYear, 0, sizeof(sYear));
	memset(sMon, 0, sizeof(sMon));
	memset(sDay, 0, sizeof(sDay));

	memcpy(sYear, DeadLineDate + 2, 2);
	memcpy(sMon, DeadLineDate + 4, 2);
	memcpy(sDay, DeadLineDate + 6, 2);
	
	ucDeadLineDate[0] = atoi(sYear);
	ucDeadLineDate[1] = atoi(sMon);
	ucDeadLineDate[2] = atoi(sDay);
	
	ret = Login_Auth_Card(1);
	if(ret != 0)
		return -12;//��Ƭ��½ʧ��

	if (SMT_ReadBlock(1, 0, ucBuffer))
		return -13;

	memcpy(ucBuffer + 4, ucDeadLineDate, 3);
	if (SMT_WriteBlock(1, 0, ucBuffer))
		return -14;

	SMT_ControlBuzzer();
	return	0;
}

/************************************************************************/
/* �Ϻ�����ѧˮ�ضԽӷ������ÿ��Ͳɼ�������                           */
/************************************************************************/
/** 
 * @brief �Ϻ�����ѧ���ʿ��Ͳɼ�����½��Կ�㷨
 * 
 * @param Srn - ��Ƭ���к�
 * @param KeyA - ��½�ɼ���A��Կ
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
void GenerateKeyA(BYTE Srn[4],unsigned char KeyA[6])
{
	unsigned char i;	
	unsigned int BCC;

	BCC = 0;
	for(i=0;i<4;i++)
	BCC += Srn[i];

	memcpy(KeyA,Srn,4);
    KeyA[4] =(unsigned char)(BCC>>8);
	KeyA[5]	=(unsigned char)BCC;
    return;
}

static int WriteWaterCardBlock(int *err_code, PWriteDataFunc pFunc, LPProcessCallBack lpCallBack)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE buf[17] = "";
	long crc = 0;
	short sect = 0;
	int ret = 0;
	int current_key, old_key;
	BOOL login_sect_succ = FALSE;
	BYTE key_a[7] = "";
	BYTE key_b[7] = "";
	CardKeyData card_key[3];

	memset((void *)card_key, 0, sizeof card_key);
	if (!Is_Com_open())
	{
		*err_code = E_COM_NOT_OPEN;
		return -1;
	}
	
	if (SMT_RequestCardExist(card_id, card_type) != 0)
	{
		*err_code = E_READ_CARD_ERROR;
		return -1;
	}
	GenerateKeyA(card_id, key_a);
	memcpy(key_b, key_a, sizeof key_b);			// ��ʱKEYA��KEYBͬһ����Կ
	
	card_key[0].flag = CARD_KEY_A;
	
	memcpy(card_key[0].key[CARD_KEY_A],CARD_INIT_KEY,sizeof(CARD_INIT_KEY));
	memcpy(card_key[0].key[CARD_KEY_B],CARD_INIT_KEY,sizeof(CARD_INIT_KEY));

	card_key[1].flag = CARD_KEY_A;
	memcpy(card_key[1].key[CARD_KEY_A], key_a, sizeof key_a);
	memcpy(card_key[1].key[CARD_KEY_B], key_b, sizeof key_b);
	
	// �ٶ�һ�ο����һ�¿� ID
	memset(card_id, 0, sizeof card_id);
	if (SMT_RequestCardExist(card_id, card_type) != 0)
	{
		*err_code = E_READ_CARD_ERROR;
		return -1;
	}

	current_key = 0;
	for (sect = 0; sect < COLLECT_CARD_SECT_NO; sect++)
	{
		if (lpCallBack != NULL)
			lpCallBack(sect);
		old_key = current_key;
		login_sect_succ = FALSE;
		while (TRUE)
		{
			if (0 == LoginCardSect_2KEY(sect,&card_key[current_key],card_type,CARD_KEY_B))
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key--;
			if (current_key < 0)
				current_key = 2;
			if (current_key == old_key)
				break;
		}
		
		if (FALSE == login_sect_succ)
		{
			*err_code = E_CARD_LOGIN_ERROR;
			return -1;	
		}
		
		if (pFunc != NULL)
		{
			if ((ret = pFunc(sect, &card_key[1], NULL, card_type, &card_key[1])) != 0)
			{
				*err_code = E_CARD_WRITE_ERROR;
				return ret;
			}		
		}
	}
	return 0;
}

/** 
 * @brief �Ϻ�����ѧ��ʼ���������ÿ�
 * 
 * @param err_code - ���󷵻���
 * @param lpCallBack - �ص�����������ʱ���ã�����ΪNULL
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
int __stdcall InitNewFeeRateCard(int *err_code, LPProcessCallBack lpCallBack)
{
	int ret = 0;
	if (WriteWaterCardBlock(err_code, WriteInitNewCardData, lpCallBack) != 0)
	{
		return -1;
	}
	SMT_ControlBuzzer();
	return 0;
}

/** 
 * @brief �Ϻ�����ѧ��ʼ���ɼ���
 * 
 * @param err_code - ���󷵻���
 * @param lpCallBack - �ص�����������ʱ���ã�����ΪNULL
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
int __stdcall InitNewCollectionCard(int *err_code, LPProcessCallBack lpCallBack)
{
	/*
	BYTE test[5] = "";
	return SMT_ReadWaterCardFlag(test);
	*/
	int ret = 0;
	BYTE water_card_flag[5] = "LYCJ";
	if (WriteWaterCardBlock(err_code, WriteInitNewCardData, lpCallBack) != 0)
	{
		return -1;
	}
	if ((ret = SMT_WriteWaterCardFlag(water_card_flag)) != 0)
	{
		*err_code = ret;
		return -1;
	}
	SMT_ControlBuzzer();
	return 0;
}

/** 
 * @brief �Ϻ�����ѧ�ɼ�����������
 * 
 * @param err_code					- ���󷵻���
 * @param shop_id					- �̻�ID��, 4���ֽ�
 * @param shop_card_total_sum		- �̻������, 4���ֽ�
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
int __stdcall CollectionCardReceiveData(int *err_code, COLLECT_BALANCE collect_balance[90], int *collect_count)
{
	//////////////////////////////////////////////////////////////////////////
	/*
	Login_Collect_Card(1);
	BYTE buf_test[17] = {0x00, 0x0a, 0x61, 0x06, 0xaf, 0x23};
	if (SMT_WriteBlock(1, 0, buf_test))
	{
		return 0;
	}
	*/
	//////////////////////////////////////////////////////////////////////////
	int ret = 0;
	int sect = 0;
	int block = 1;
	int byte_length = 4;
	int offset = 0;
	int buf_offset = 0;
	int count = 0;
	BYTE buf[17] = "";
	BYTE cmp_buf[17] = "";
	BYTE buf_balance[5] = "";
	BYTE water_card_flag[5] = "LYCJ";
	Login_Collect_Card(sect);
	ret = SMT_ReadBlock(sect, block, buf);
	if (ret)
	{
		*err_code = ret;	
	}
	if (_mbsncmp(water_card_flag, buf, sizeof(water_card_flag) - 1))
	{
		*err_code = E_CARD_FLAG_ERROR;
	}
	memset(buf, 0, sizeof(buf) -1);
	block = 0;
	for (sect = 1; sect < 32; sect++)
	{
		Login_Collect_Card(sect);
		while (block < 2)
		{
			ret = SMT_ReadBlock(sect, block, buf);
			if (ret)
			{
				*err_code = ret;
			}
			
			if (0 == memcmp(buf, cmp_buf, sizeof(buf) - 1))
			{
				*collect_count = count;
				return 0;
			}

//			memcpy(collect_balance[count].devphy999_id, buf + buf_offset * 2, sizeof(BYTE) * byte_length);
			dec2hex(buf + buf_offset * 2, sizeof(BYTE) * byte_length, collect_balance[count].devphy999_id);	
			memcpy(buf_balance, buf + byte_length + buf_offset * 2, sizeof(BYTE) * byte_length);
			collect_balance[count].sum_balance = ((double)(buf_balance[3] * 256 * 256 * 256 + buf_balance[2] * 256 * 256 + buf_balance[1] * 256 + buf_balance[0]) / 100);
			offset += 4;
			buf_offset = 4;
			count++;
			
			if (memcmp(buf + 8, cmp_buf, sizeof(BYTE) * 8) == 0)
			{
				*collect_count = count;
				return 0;
			}
			
//			memcpy(collect_balance[count].devphy999_id, buf + buf_offset * 2, sizeof(BYTE) * byte_length);
			dec2hex(buf + buf_offset * 2, sizeof(BYTE) * byte_length, collect_balance[count].devphy999_id);
			memcpy(buf_balance, buf + byte_length + buf_offset * 2, sizeof(BYTE) * byte_length);
			collect_balance[count].sum_balance = ((double)(buf_balance[3] * 256 * 256 * 256 + buf_balance[2] * 256 * 256 + buf_balance[1] * 256 + buf_balance[0]) / 100);
			count++;
			/*
			memcpy(shop_id + offset, buf + buf_offset * 2, sizeof(BYTE) * byte_length);
			memcpy(shop_card_total_sum + offset, buf + byte_length + buf_offset * 2, sizeof(BYTE) * byte_length);
			offset += 4;
			buf_offset = 4;
			memcpy(shop_id + offset, buf + buf_offset * 2, sizeof(BYTE) * byte_length);
			memcpy(shop_card_total_sum + offset, buf + byte_length + buf_offset * 2, sizeof(BYTE) * byte_length);
			block++;
			*/
			block++;
			buf_offset = 0;
		}
		block = 0;
	}
	return 0;
}

/** 
 * @brief �Ϻ�����ѧ���ղɼ����ͷ������ÿ�
 * 
 * @param err_code - ���󷵻���
 * @param LPProcessCallBack - �ص�����������ʱ���ã�����ΪNULL
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
int __stdcall RefineWaterCard(int *err_code, LPProcessCallBack lpFunc)
{
	int ret = 0;
	if ((ret = SMT_ClearWaterCard()) != 0)
	{
		*err_code = ret;
		return -1;
	}

	if (WriteWaterCardBlock(err_code, WriteRefineCardData, lpFunc) != 0)
	{
		return -1;
	}
	SMT_ControlBuzzer();
	return 0;
}

int Login_Collect_Card(int sector)
{
	unsigned char ucSerialNo[5], ucKeyA[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	//1 --- ����KEYA
	GenerateKeyA(ucSerialNo, ucKeyA);
	ret = SMT_Login_With_UserKey(sector,ucKeyA,0);                       
	if(ret != 0)
	{
		return -2;//��Ƭ��½ʧ��
	}
	return 0;
}

int __stdcall SMT_ClearWaterCard()
{
	unsigned char ucSerialNo[5] = "";
	unsigned char ucKeyA[6] = "";
	unsigned char buf[16] = "";
	int ret = 0;
	int block = 0;
	//1��ʹ�ó��������½��Ƭ  ǰ16������
	for (int sect = 0; sect < COLLECT_CARD_SECT_NO; sect++)
	{
		if (Login_Collect_Card(sect) != 0)
		{
			return E_CARD_LOGIN_ERROR;
		}

		for (block = 0; block < 3; block++)
		{
			if (0 == sect && 0 == block)
				continue;

			ret = SMT_WriteBlock(sect, block, buf);
			if (ret)
			{
				return E_CARD_WRITE_ERROR;
			}
		}			
	}
	return 0;
}

int __stdcall SMT_WriteWaterCardFlag(BYTE water_card_flag[4])
{
	int sect = 0;
	int block = 1;
	BYTE buf[17] = "";
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	memcpy(buf, water_card_flag, sizeof(BYTE) * 4);
	if (SMT_WriteBlock(sect, block, buf) != 0)
	{	
		return E_CARD_WRITE_ERROR;
	}
	return 0;
}

int __stdcall ReadWaterCardBlock(int startSect,int endSect
									 ,short block,LPGetBlockData lpFunc)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE key_a[7] = "";
	BYTE key_b[7] = "";
	BYTE buf[16] = "";
	int current_key, old_key;
	BOOL login_sect_succ = FALSE;
	
	CardKeyData card_key[3];
	int sect = 0;

	// �жϴ򿪴���
	if (!Is_Com_open())
	{
		return -1;
	}

	// ��鿨�Ƿ����
	if (SMT_RequestCardExist(card_id,card_type) != 0)
	{
		return -1;
	}

	// ���㿨�� keyA , keyB
	GenerateKeyA(card_id, key_a);
	memcpy(key_b, key_a, sizeof key_b);

	memset((void *)card_key,0,sizeof(card_key));

	card_key[0].flag = CARD_KEY_A;
	// ������Զ������պ��KEYA
	memcpy(card_key[0].key[CARD_KEY_A], CARD_INIT_KEY, sizeof(CARD_INIT_KEY));
	memcpy(card_key[0].key[CARD_KEY_B], CARD_INIT_KEY, sizeof(CARD_INIT_KEY));

	card_key[1].flag = CARD_KEY_A;
	memcpy(card_key[1].key[CARD_KEY_A], key_a, sizeof key_a);
	memcpy(card_key[1].key[CARD_KEY_B], key_b, sizeof key_b);

	// ������Ե�¼�� key ������
	current_key = 1;
	for(sect = startSect; sect < endSect + 1; ++sect)
	{
		// ���γ�ʼ��ÿ������
		old_key = current_key;
		login_sect_succ = FALSE;
		// ���ҿ��Ե�¼�� key 
		while(TRUE)
		{
			// �����¼�ɹ� ����ѭ��
			if( LoginCardSect_2KEY(sect, &card_key[current_key], card_type) == 0)
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key++;
			if( current_key > 3 )
				current_key = 0;
			if (current_key == old_key)
				break;
		}
		// �жϵ�ǰ�����Ƿ�ɹ���¼
		if (login_sect_succ == FALSE)
		{
			return -1;
		}
		// ��ȡ����������
		for(int b = 0;b < 4;++b)
		{
			if(block & (1 << b))
			{
				memset(buf, 0, sizeof(buf));
				if (SMT_ReadBlock(sect, b, buf) != 0)
				{
					return -1;
				}
				// ���ö����ص�����
				if(lpFunc != NULL)
				{
					lpFunc(sect, b, buf,card_key[current_key].key[card_key[current_key].flag],
						card_key[current_key].flag);			
				}
			}
		}	
	}
	return 0;
}

/** 
 * @brief �Ϻ�����ѧ���з������ÿ�
 * 
 * @param -  fee_rate_card_info ���ʿ��ṹ
 * @return - �ɹ�����0��ʧ�ܷ��ش�����
 */
int __stdcall PublishFeeRateCard(FEE_RATE_CARD_INFO *fee_rate_card_info)
{
//	MessageBox(NULL, "���뷢�п�", NULL, NULL);
	int ret = 0;
	int sect = 0;
	int block = 1;
	int block_num = 0;
	short fee_rate_data_length = 0;
	BYTE buf[17] = "";
	BYTE right_type_bit[32] = "";
	BYTE check_crc = 0;
	BYTE auth_key[8] = "";
	char temp_work_key[32] = "";
	BYTE temp = 0;
	int offset = 0;
	int right_type_num = 0;
//	char test[4] = "";

	if (ret = SMT_ClearWaterCard())
	{
	//	return	ret; 
	}
	for (right_type_num = 0; right_type_num < 256; right_type_num++)
	{
		if (0 == fee_rate_card_info->fee_right_num[right_type_num].right_flag)
			continue;
		fee_rate_data_length += fee_rate_card_info->fee_right_num[right_type_num].right_num * 3 + 1;
	}

//	memcpy(&fee_rate_data_length, &(fee_rate_card_info->data_length), sizeof(fee_rate_card_info->data_length) - 1);
	BYTE fee_rate_data_buf[512] = "";
//	memcpy(fee_rate_data_buf, &fee_rate_data_length, sizeof(BYTE) * 2);
	fee_rate_data_buf[0] = fee_rate_data_length >> 8 & 0xff;
	fee_rate_data_buf[1] = fee_rate_data_length & 0xff;
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	// ��0����
	memcpy(buf, fee_rate_card_info->water_card_flag, offset += (sizeof(fee_rate_card_info->water_card_flag) -1));
//	memcpy(buf + offset, (void)fee_rate_card_info->packet_no, offset += sizeof(fee_rate_card_info->packet_no));
	buf[offset] = fee_rate_card_info->packet_num;
//	MessageBox(NULL, &fee_rate_card_info->packet_num, NULL, NULL);
	offset += sizeof(fee_rate_card_info->packet_num);
//	memset(buf + offset, 0xFF, 16 - offset);						ȫFF��check_crcԽ��
	for (int address = 0; address < 15; address++)
	{
		check_crc += buf[address];
	}
	buf[15] = check_crc;
	ret = SMT_WriteBlock(sect, block, buf);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;		
	}
	
	memset(buf, 0x00, sizeof(buf) -1);
//	MessageBox(NULL, (char*)fee_rate_card_info->main_work_key, NULL, NULL);
	dec2hex(fee_rate_card_info->main_work_key,8,temp_work_key);
	MessageBox(NULL, temp_work_key, NULL, NULL);
	encrypt_work_key(fee_rate_card_info->main_work_key, auth_key);
//	memcpy(buf, fee_rate_card_info->main_work_key, sizeof(fee_rate_card_info->main_work_key) - 1);
//	memcpy(buf + 8, fee_rate_card_info->packet_work_key, sizeof(fee_rate_card_info->packet_work_key) - 1);
	memcpy(buf, auth_key, sizeof(BYTE) * 8);				// 8�ֽ�д����
	dec2hex(fee_rate_card_info->packet_work_key,8,temp_work_key);
	MessageBox(NULL, temp_work_key, NULL, NULL);
	encrypt_work_key(fee_rate_card_info->packet_work_key, auth_key);
	memcpy(buf + 8, auth_key, sizeof(BYTE) * 8);
	
	ret = SMT_WriteBlock(sect, block + 1, buf);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;
	}
	sect = 1;			// ��һ����0�鿪ʼ�Ժ�ÿ���鶼�ܹ���
	block = 0;
	offset = 2;
	check_crc = 0;
	// �շ���������
	memset(buf, 0x00, sizeof(buf) - 1);
	for (right_type_num = 0; right_type_num < 256; right_type_num++)
	{
		if (0 == fee_rate_card_info->fee_right_num[right_type_num].right_flag)
			continue;
		right_type_bit[(255 - right_type_num) / 8] |= 1 << (right_type_num % 8);
		memcpy(fee_rate_data_buf + offset, &(fee_rate_card_info->fee_right_num[right_type_num].right_num), sizeof BYTE);
		
		check_crc += fee_rate_card_info->fee_right_num[right_type_num].right_num;		// �ۼ�Ч���
/*		
		itoa(fee_rate_card_info->fee_right_num[right_type_num].right_num, test, 10);
		MessageBox(NULL, test, NULL, NULL);
*/		
		for (int right_num = 0; right_num < fee_rate_card_info->fee_right_num[right_type_num].right_num; right_num++)
		{
			memcpy(fee_rate_data_buf + offset + 1, &(fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].time_ladder), 1);
			memcpy(fee_rate_data_buf + offset + 2, &(fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_time), 1);
			memcpy(fee_rate_data_buf + offset + 3, &(fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_fee), 1);
			check_crc += fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].time_ladder[0] + 
						fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_time[0] +
						fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_fee[0]; 
			offset += 3;	// ���ѭ��+3
		}
		offset += 1;		// ���+1���һ���ֽڵ�Ȩ�޷��ʸ���
	}

	// ��½��һ�����Ŀ�0�Ϳ�1, д��Ȩ��λͼ
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	
	ret = SMT_WriteBlock(sect, block, right_type_bit);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;
	}
	
	ret = SMT_WriteBlock(sect, block += 1, right_type_bit + 16);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;
	}

	int block_byte_num = 0;
	fee_rate_data_buf[fee_rate_data_length + 2] = check_crc;

	block = 2;															// block = 2��ʱ�����
	while (block_num < 1 + (fee_rate_data_length + 2) / 16)				// �����������������Ŀ���бȽ�
	{
		if (Login_Collect_Card(sect) != 0)
		{
			return E_CARD_LOGIN_ERROR;
		}
	
		ret = SMT_WriteBlock(sect, block, fee_rate_data_buf + block_byte_num);
		if (ret)
		{
			return E_CARD_WRITE_ERROR;
		}
		
		block_byte_num += 16;
		++block_num;													// �Ѿ�д��һ����
		++block;

		if (block >= 2)
		{
			block = 0;
			++sect;
			continue;
		}
		// ����ʣ������
		if ((fee_rate_data_length + 2) / 16 == block_num)
		{
			if ((fee_rate_data_length + 2) % 16 > 0)
			{
																		//	block_byte_num += (fee_rate_data_length + 2) % 16;
				ret = SMT_WriteBlock(sect, block, fee_rate_data_buf + block_byte_num);
				if (ret)
				{
					return E_CARD_WRITE_ERROR;
				}
				return 0;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

int __stdcall ReadCollectCardInfo(FEE_RATE_CARD_INFO *fee_rate_card_info)
{
	int sect = 0;
	int block = 1;
	int ret = 0;
	int fee_rate_data_length = 0;
	int right_type_num = 0;
	int offset = 0;
	int block_num = 0;
	int block_byte_num = 0;
	BYTE fee_rate_count = 0;
	BYTE buf[17] = "";
	BYTE right_type_bit[33] = "";
	BYTE fee_rate_data_buf[512] = "";
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	ret = SMT_ReadBlock(sect, block, buf);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}	
	memcpy(fee_rate_card_info->water_card_flag, buf, sizeof(fee_rate_card_info->water_card_flag) - 1);
	memcpy(&(fee_rate_card_info->packet_num), buf + 4, sizeof(fee_rate_card_info->packet_num));
	memcpy(fee_rate_card_info->check_crc, buf + 15, sizeof(fee_rate_card_info->check_crc) - 1);
	block++;
	memset(buf, 0, sizeof(buf) - 1);
	ret = SMT_ReadBlock(sect, block, buf);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}
	memcpy(fee_rate_card_info->main_work_key, buf, sizeof(fee_rate_card_info->main_work_key) - 1);
	memcpy(fee_rate_card_info->packet_work_key, buf + 8, sizeof(fee_rate_card_info->packet_work_key) - 1);
	
	sect = 1;
	block = 0;
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	ret = SMT_ReadBlock(sect, block, right_type_bit);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}
	block = 1;
	ret = SMT_ReadBlock(sect, block, right_type_bit + 16);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}
	block = 2;
	ret = SMT_ReadBlock(sect, block, buf);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}
	memcpy(fee_rate_card_info->data_length, buf, sizeof(BYTE) * 2);
	//memcpy(&fee_rate_data_length, fee_rate_card_info->data_length, sizeof(BYTE) * 2);
	//fee_rate_card_info->data_length = ((buf[0] << 8) & 0xff00) | buf[1];
	fee_rate_data_length = ((buf[0] << 8) & 0xff00) | buf[1];
//	fee_rate_data_length = fee_rate_card_info->data_length;
//	memcpy(&fee_rate_count, buf + 2, sizeof(fee_rate_count));	
//	fee_rate_data_buf[fee_rate_data_length + 2] = check_crc;
	// block = 2��ʱ�����
	while (block_num < 1 + (fee_rate_data_length + 2) / 16)				// �����������������Ŀ���бȽ�
	{

		if (Login_Collect_Card(sect) != 0)
		{
			return E_CARD_LOGIN_ERROR;
		}
	
		ret = SMT_ReadBlock(sect, block, fee_rate_data_buf + block_byte_num);
		if (ret)
		{
			return E_READ_CARD_ERROR;
		}
		
		block_byte_num += 16;
		++block_num;													// �Ѿ�д��һ����
		++block;

		if (block >= 2)
		{
			block = 0;
			++sect;
			continue;
		}
		// ����ʣ������
		if ((fee_rate_data_length + 2) / 16 == block_num)
		{
			if ((fee_rate_data_length + 2) % 16 > 0)
			{
				//	block_byte_num += (fee_rate_data_length + 2) % 16;
				ret = SMT_ReadBlock(sect, block, fee_rate_data_buf + block_byte_num);
				if (ret)
				{
					return E_READ_CARD_ERROR;
				}
			}
			++block_num;
		}
	}
	
	memcpy(fee_rate_card_info->check_crc, &fee_rate_data_buf[fee_rate_data_length + 2], sizeof(BYTE));
	
	offset = 2;
	for (right_type_num = 0; right_type_num < 32; right_type_num++)
	{
		if (right_type_bit[31 - right_type_num] != 0)
		{
			for (int bit = 0; bit < 8; bit++)
			{
				if ((right_type_bit[31 - right_type_num] & (1 << bit)) != 0)
				{
					fee_rate_card_info->fee_right_num[right_type_num * 8 + bit].right_flag = 1;
					fee_rate_card_info->fee_right_num[right_type_num * 8 + bit].right_num = fee_rate_data_buf[offset];
					offset += 1;
					for (int count = 0; count < fee_rate_card_info->fee_right_num[right_type_num * 8 + bit].right_num; count++)
					{
						memcpy(&(fee_rate_card_info->fee_right_num[right_type_num * 8 + bit].fee_rate[count]), fee_rate_data_buf + offset, sizeof(BYTE) * 3);
						offset += 3;
					}
//					offset += 1;
				}			
			}
		}
	}
	return 0;
}

int __stdcall WaterTransferSmallPacket(int BigPacketNo, int SmallPacketNo, int nMoney)
{
	int ret = 0;
//	int purse_packet_one = 1;
//	int purse_packet_two = 2;
	int packet_one_money = 0;
	int packet_two_money = 0;
	int transfer_money_use = 0;
//	double transfer_money = 0;
//	CString str_transfer_money = "";
	LOOPPURSEINFO LoopPurseInfoOne;
	LOOPPURSEINFO LoopPurseInfoTwo;
	memset(&LoopPurseInfoOne, 0, sizeof LoopPurseInfoOne);
	memset(&LoopPurseInfoTwo, 0, sizeof LoopPurseInfoTwo);
	transfer_money_use = nMoney;
	if (transfer_money_use <= 0)
	{
//		AfxMessageBox("�������������");
		return -1001;
	}
	if(SMT_ReadPacketInfo(BigPacketNo, &LoopPurseInfoOne))
	{
//		AfxMessageBox("��ȡ��Ǯ����Ϣʧ��");
		return -1002;
	}
	if (LoopPurseInfoOne.RemainMoney < 0)
	{
//		AfxMessageBox("��Ǯ������");
		return -1003;
	}
	if(SMT_ReadPacketInfo(SmallPacketNo, &LoopPurseInfoTwo))
	{
//		AfxMessageBox("��ȡ999Ǯ����Ϣʧ��");
		return -1004;
	}
	if (LoopPurseInfoTwo.RemainMoney < 0)
	{
//		AfxMessageBox("999Ǯ������");
		return -1005;
	}
	packet_one_money = LoopPurseInfoOne.RemainMoney;
	packet_two_money = LoopPurseInfoTwo.RemainMoney;
	
	ret = SMT_PacketSetMoney(BigPacketNo, (packet_one_money - transfer_money_use));
	if (ret)
	{
//		AfxMessageBox("д���Ǯ��ʧ��");
		return -1006;
	}
	ret = SMT_PacketSetMoney(SmallPacketNo, (packet_two_money + transfer_money_use));
	if (ret)
	{
//		AfxMessageBox("д��999Ǯ��ʧ��");
		return -1007;
	}
//	AfxMessageBox("תǮ���ɹ�");
	return 0;
}

int __stdcall SMT_ClearCollectCardData()
{
	int ret = 0;
	BYTE water_card_flag[5] = "LYCJ";
	if (ret = SMT_ClearWaterCard())
	{
		return ret;
	}
	if ((ret = SMT_WriteWaterCardFlag(water_card_flag)) != 0)
	{
		return ret;
	}
	return 0;
}

int __stdcall SMT_ReadWaterCardFlag(BYTE WaterCardFlag[4])
{
	int sect = 0;
	int block = 1;
	BYTE buf[17] = "";
	BYTE init_key[7] = "";
	BYTE card_type[3] = "";
	memcpy(init_key, CARD_INIT_KEY, sizeof(CARD_INIT_KEY));
	
	//�ж��Ƿ�Ϊ�㿨
	if (0 == LoginCardSect(sect, init_key, 0, card_type))
	{
		memset(WaterCardFlag, 0, sizeof(BYTE) * 4);
		return 0;
	}

	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	
	if (SMT_ReadBlock(sect, block, buf))
	{
		return E_READ_CARD_ERROR;	
	}
	
	memcpy(WaterCardFlag, buf, sizeof(BYTE) * 4);
	return 0;
}

int __stdcall SMT_InitNewCard4GDDXC(int * err_code,LPProcessCallBack lpCallBack)
{
	int ret = 0;
	if((ret = WriteCardBlock(err_code,WriteInitNewCardData,lpCallBack)) != 0)
	{
		SetLastErrMsg(ret,"��ʼ��ʱ������Կ��ʧ��");
		//*err_code = E_CARD_WRITE_ERROR;
		return ret;
	}
	return 0;
}
// ��������: ��ʽ���������ܣ����ָ�����ݴ�ѧ�ǿ�Ƭ36��37��38�������ݣ�����ʽ��Ǯ��������Ϣ
// ��������: ��
int __stdcall SMT_FormatCard4GZDXC(int CleanWaterFlag)
{
	int ret = 0;
	int block = 0;
	unsigned char ucRawData[16] = "";
	unsigned char ucTempData[16] = "";
	
	memset(ucRawData, 0x00, sizeof(ucRawData));
	memset(ucTempData, 0x00, sizeof(ucTempData));
	
	if (SMT_Login_With_UserKey(SMARD_CARD_SECT4K_NO - 3, CARD_INIT_KEY, 0) != 0)
	{
		if (ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO - 3))				// ˮ������ֻ����KEYA��д
		{
			SetLastErrMsg(ret,"��¼ˮ��33����ʧ��");
			return ret;
		}
		if(1==CleanWaterFlag)
		{
			for (block = 0; block < 15; block++)
			{
			 	if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO - 3, block, ucRawData))
				{
					SetLastErrMsg(ret,"д33����ʧ��");
			 		return ret;
				}
			}
		}
	}
	if (ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO))
	{
		SetLastErrMsg(ret,"��¼36����ʧ��");
		return ret;
	}
	for (block = 1; block < 15; block++)
	{
		if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO, block, ucRawData))
		{
			SetLastErrMsg(ret,"д36����ʧ��");
			return ret;
		}
	}

	if (ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1))
	{
		SetLastErrMsg(ret,"��¼37����ʧ��");
		return ret;
	}
	if (ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucRawData))
	{
		SetLastErrMsg(ret,"��37������0��ʧ��");
		return ret;
	}
	memset(ucRawData, 0x00, 7);
	memset(ucRawData + 12, 0x00, 4);

	for (block = 0; block < 15; block++)
	{
		//������3���Ǯ��������͵�4��Ĳ���������
		if ((3 == block) || (4 == block))
			continue;
		
		if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, block, ucTempData))
		{
			SetLastErrMsg(ret,"д37����ʧ��");
			return ret;
		}
	}
	block = 9;
	memset(ucTempData, 0xFF, sizeof(ucTempData));
	ucTempData[0] = block;												// 1��Ǯ��������Ϣ��������

	if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 4, ucTempData))
	{
		SetLastErrMsg(ret,"д37����ʧ��");
		return ret;
	}
	if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 0, ucRawData))	// д����ʾ����
	{
		SetLastErrMsg(ret,"д37����ʧ��");
		return ret;
	}
	
	if (ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucRawData))	// ��Ǯ������
	{
		SetLastErrMsg(ret,"��37����ʧ��");
		return ret;
	}
	
	block = 6;															// ��һǮ���ڵ�6��
	memset(ucRawData, 0xFF, sizeof(ucRawData));
	for (int packet_num = 0; packet_num < 1; packet_num++)				// ֻ��1Ǯ������, 1Ǯ��������Ϣ�ڿ�12											// һ��8��Ǯ����Ĭ��ȫ����
	{
		ucRawData[packet_num * 2] = 0x00;
		ucRawData[packet_num * 2 + 1] = block + packet_num * 3;
	}
	
	if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucRawData))
	{
		SetLastErrMsg(ret,"д37����ʧ��");
		return ret;
	}
	
	memset(ucRawData, 0x00, sizeof(ucRawData));
	ucRawData[0] = 0xFF;
	
	if (ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, 5, ucRawData))	// д�ڿ���־�ͺ������汾��
	{
		SetLastErrMsg(ret,"д37����ʧ��");
		return ret;
	}
	return 0;
}


int __stdcall YKT_encrypt_cardpwd(int cut_id,const char seedkey[32],const char pwd[9],char mpwd[64])
{
	if(encrypt_elec_card_pwd)
		return encrypt_elec_card_pwd(cut_id,seedkey,pwd,mpwd);
	return -1;
}
int __stdcall YKT_decrypt_cardpwd(int cut_id,const char seedkey[32],const char mpwd[64],char pwd[9])
{
	if(encrypt_elec_card_pwd)
		return decrypt_elec_card_pwd(cut_id,seedkey,mpwd,pwd);
	return -1;
}


int __stdcall SetConsumeLimit(unsigned int max_per_count,unsigned int max_per_day)
{
	return 0;
}

int __stdcall ReadConsumeLimit(unsigned int *max_per_count,unsigned int *max_per_day)
{
	*max_per_count = 0;
	*max_per_day = 0;
	return 0;
}

int __stdcall SetCardLockFlag(int lock_flag)
{
	return 0;
}

int __stdcall ReadCardLockFlag(int* lock_flag)
{
	*lock_flag = 0;
	return 0;
}


int __stdcall SMT_WriteWaterPackInfo(WATER_PACK_INFO2* info)
{
	int ret = -1;
	ret = SMT_GZWriteWaterPacket(info->price1,info->price2,info->price3,info->balance);
	if(ret)
		return ret;
	return 0;
}


// ��ȡ��ˮ����Ϣ
int __stdcall SMT_ReadWaterPackInfo(WATER_PACK_INFO2* info)
{
	int ret = -1;
	ret = SMT_GZReadWaterPacket(&(info->price1),&(info->price2),&(info->price3),&(info->balance));
	if(ret)
		return ret;
	return 0;
}


int __stdcall SMT_TransWaterPacket(int main_money,WATER_PACK_INFO3* info)
{
	char msg[512];
	WATER_PACK_INFO2 param;
	double temp;
	int ret = -1;
	ret = SMT_PacketSetMoney(1,main_money);
	// д��Ǯ��ʧ��
	if(ret)
		return -1;
	memset(&param,0,sizeof param);
	param.price1 = info->price1/100.0;
	round_float(&(param.price1),2);
	param.price2 = info->price2/100.0;
	round_float(&(param.price2),2);
	param.price3 = info->price3/100.0;
	round_float(&(param.price3),2);
	param.balance = info->balance/100.0;
	round_float(&(param.balance),2);

	sprintf(msg,"дˮ��Ǯ��,bala[%.2f]",param.balance);

	g_cardlogger<<"SMT_TransWaterPacket, water["<<info->balance<<"]"<<std::endl;
	
	ret = SMT_WriteWaterPackInfo(&param);
	// ��Ǯ��д�ɹ��ˣ�ˮ��Ǯ��дʧ����
	if(ret)
		return ret;

	return 0;
}

int __stdcall SMT_ReadWaterPackInfo2(WATER_PACK_INFO3* info)
{
	int ret;
	WATER_PACK_INFO2 param;
	memset(&param,0,sizeof param);
	ret = SMT_ReadWaterPackInfo(&param);
	if(ret)
		return ret;
	info->price1 = double_2_int(param.price1*100.0);
	info->price2 = double_2_int(param.price2*100.0);
	info->price3 = double_2_int(param.price3*100.0);
	info->balance = double_2_int(param.balance*100.0);
	return 0;
}

int __stdcall SMT_WriteWaterPackInfo2(WATER_PACK_INFO3* info)
{
	int ret;
	WATER_PACK_INFO2 param;
	memset(&param,0,sizeof param);

	param.price1 = info->price1/100.0;
	round_float(&(param.price1),2);
	param.price2 = info->price2/100.0;
	round_float(&(param.price2),2);
	param.price3 = info->price3/100.0;
	round_float(&(param.price3),2);
	param.balance = info->balance/100.0;
	round_float(&(param.balance),2);

	
	ret = SMT_WriteWaterPackInfo(&param);
	if(ret)
		return ret;
	return 0;

}
int __stdcall PublishXTWaterPack(WATER_PACK_INFO3* info)
{
	unsigned char buffer[16],buffer2[16];
	int sect=33;
	int ret;
	memset(buffer,0,sizeof buffer);
	memset(buffer2,0,sizeof buffer2);
	UserDataToCard(1,info->balance,info->balance,1,buffer2,buffer);

	ret = SMT_WriteBlock(sect,0,buffer);
	if(ret)
		return -1;
	memset(buffer2,0,sizeof buffer2);
	ret = SMT_WriteBlock(sect,1,buffer2);
	if(ret)
		return -1;
	memset(buffer2,0,sizeof buffer2);
	ret = SMT_WriteBlock(sect,2,buffer2);
	if(ret)
		return -1;
	return 0;
}

int __stdcall SMT_ReadWaterPackInfo_XT(WATER_PACK_INFO3* info)
{
	int sect;
	unsigned char phyid[9];
	unsigned char key[6];
	unsigned char card_type[4];
	unsigned char buffer[16];
	double remain;

	sect = 33;
	MF_ReadSeriesNo(phyid);
	memcpy(key,XT_LOGIN_WATER_KEYA,6);
	if( SMT_Login_With_UserKey(sect,key,CARD_KEY_A) != 0 )
	{
		return -2;
	}
	if(SMT_ReadBlock(sect,0,buffer)!=0)
		return -1;
	if(CardToUserData(buffer,(unsigned long*)&(info->price1),(unsigned long*)&(info->price2),(unsigned long*)&(info->balance)))
	{
		return -3;
	}
	return 0;
}

int __stdcall SMT_WriteWaterPackInfo_XT(WATER_PACK_INFO3* info)
{
	int ret;
	unsigned char buffer[16],buffer2[16];
	int sect=33;
	WATER_PACK_INFO3 old_info;
	if((ret=SMT_ReadWaterPackInfo_XT(&old_info))!=0)
	{
		// ��Ϊ���¿�
		if(ret==-3)
			return PublishXTWaterPack(info);
	}
	if(SMT_ReadBlock(sect,0,buffer2)!=0)
		return -1;

	if(old_info.balance == info->balance)
		return -10;

	info->price1 = old_info.price1;
	info->price2 = (info->balance - old_info.balance)+old_info.price2;
	if(UserDataToCard(1,info->price2,info->balance,2,buffer2,buffer))
	{
		// ����������£�������Ϊ���¿���
		return PublishXTWaterPack(info);
	}
#if 0
	if(SMT_WriteBlock(sect,0,buffer)!=0)
        return -2;
#else
	SMT_WriteBlock(sect,0,buffer);
	memset(buffer2,0,sizeof buffer2);
	if(SMT_ReadBlock(sect,0,buffer2)!=0)
		return -11; // ��;�ο�
	if(memcmp(buffer,buffer2,16)!=0)
		return -1;
#endif
	return 0;
}

int __stdcall SMT_TransWaterPacket_XT(int main_money,WATER_PACK_INFO3* info)
{
	char msg[512];
	WATER_PACK_INFO3 param;
	double temp;
	int ret = -1;
	ret = SMT_PacketSetMoney(1,main_money);
	// д��Ǯ��ʧ��
	if(ret)
		return -1;
	memset(&param,0,sizeof param);
	param.balance = info->balance;
	g_cardlogger<<"SMT_TransWaterPacket_XT, water["<<info->balance<<"]"<<std::endl;

	ret = SMT_WriteWaterPackInfo_XT(&param);
	// ��Ǯ��д�ɹ��ˣ�ˮ��Ǯ��дʧ����
	if(ret)
		return ret;

	return 0;
}

int __stdcall JD2XT_Card()

{
	int sect;
	unsigned char phyid[9];
	unsigned char key[6];
	unsigned char card_type[4];
	unsigned char buffer[16];
	int card_id;
	WATER_PACK_INFO3 info;
	sect = 33;
	
	if(ReadCardNO(&card_id))
	{
		return 1;
	}
	GZDXC_check_card();
	memcpy(key,LOGIN_WATER_KEYA,6);
	if( SMT_Login_With_UserKey(sect,key,CARD_KEY_A) != 0 )
	{
		return -2;
	}
	if(SMT_ReadWaterPackInfo2(&info)!=0)
	{
		return -3;
	}
	memcpy(key,LOGIN_WATER_KEYB,6);
	if( SMT_Login_With_UserKey(sect,key,CARD_KEY_B) != 0 )
	{
		return -2;
	}
	memcpy(buffer,XT_LOGIN_WATER_KEYA,6);
	memcpy(buffer+6,CARD_NEW_CTRL_BIT,4);
	memcpy(buffer+10,LOGIN_WATER_KEYB,6);

	if(SMT_WriteBlock(sect,PASSWD_BLOCK1_NUM,buffer)!=0)
	{
		// �����Ǿɵ���Կ������ϵ
		memcpy(key,LOGIN_WATER_KEYA,6);
		MF_ReadSeriesNo(phyid);
		if( SMT_Login_With_UserKey(sect,key,CARD_KEY_A) != 0 )
		{
			return -2;
		}
		if(SMT_WriteBlock(sect,PASSWD_BLOCK1_NUM,buffer)!=0)
		{
			return -8;
		}
	}
	
	memcpy(key,XT_LOGIN_WATER_KEYA,6);
	MF_ReadSeriesNo(phyid);
	if( SMT_Login_With_UserKey(sect,key,CARD_KEY_A) != 0 )
	{
		return -2;
	}

	info.price1 = card_id;
	if(PublishXTWaterPack(&info)!=0)
		return -1;
	return 0;
}
int __stdcall XT2JD_Card()
{
	int sect;
	unsigned char phyid[9];
	unsigned char key[6];
	unsigned char card_type[4];
	unsigned char buffer[16];
	WATER_PACK_INFO3 info;
	sect = 33;
	MF_ReadSeriesNo(phyid);
	memcpy(key,XT_LOGIN_WATER_KEYA,6);
	if( SMT_Login_With_UserKey(sect,key,CARD_KEY_A) != 0 )
	{
		return -2;
	}
	if(SMT_ReadWaterPackInfo_XT(&info)!=0)
	{
		return -3;
	}
	memcpy(key,LOGIN_WATER_KEYB,6);
	if( SMT_Login_With_UserKey(sect,key,CARD_KEY_B) != 0 )
	{
		return -2;
	}
	memcpy(buffer,LOGIN_WATER_KEYA,6);
	memcpy(buffer+6,CARD_NEW_CTRL_BIT,4);
	memcpy(buffer+10,LOGIN_WATER_KEYB,6);

	if(SMT_WriteBlock(sect,PASSWD_BLOCK1_NUM,buffer)!=0)
	{
		return -8;
	}

	memcpy(key,LOGIN_WATER_KEYA,6);
	if( SMT_Login_With_UserKey(sect,key,CARD_KEY_A) != 0 )
	{
		return -2;
	}

	info.price1 = 4;
	info.price2 = 4;
	info.price3 = 4;

	if(SMT_WriteWaterPackInfo2(&info)!=0)
		return -1;
	return 0;
}


void __stdcall YKT_get_version(char ver[512])
{
	sprintf(ver,"%s",CARDDLL_VERSION);
}

int __stdcall SMT_PacketSetMoney2(int nPacketNo, int nMoney, int nCnt)
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if (nPacketNo < 1)
		return -1;
	if (nMoney < 0)
		return -1;
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO + 1);
#else
	ret = Login_Card_Keya(3);
#endif
	if (ret != 0)	
		return ret;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, 3, ucBuffer);
#else
	ret = SMT_ReadBlock(3, 0, ucBuffer);
#endif
	if (ret != 0)	
		return -5;

	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
		return 1; //Ǯ��������ʹ��
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //Ǯ����������

#ifdef GZ_UNIVERSITY_TOWN
	ret = 0;
#else
	ret = Login_Card_Keya(sector);
#endif		
	if (ret != 0)
		return ret;
	unsigned char ucBuf1[16],ucBuf2[16],ucBufTmp[16];
	unsigned char ucCheck;
#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
	ret = SMT_ReadBlock(sector, 0, ucBuf1);
#endif
	if (ret != 0)	
		return -6;
	int i;
	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	{
		i = nMoney;
		ucBuf2[0] = i % 256;
		ucBuf2[1] = i / 256;
		ucBuf2[2] = i / 256 / 256;
		if(memcmp(ucBuf1,ucBuf2,3)==0)
			return 0;
		memcpy(ucBufTmp, ucBuf1, sizeof(ucBufTmp));
		// ����
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBufTmp);
#else
		ret = SMT_WriteBlock(sector, 2, ucBufTmp);
#endif
		if (ret != 0)	
			return -8;
		ucBuf1[0] = i % 256;
		ucBuf1[1] = i / 256;
		ucBuf1[2] = i / 256 / 256;
		i = nCnt;//ucBuf1[3] * 256 + ucBuf1[4];
		ucBuf1[3] = i / 256;
		ucBuf1[4] = i % 256;
		// 		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf1[7])									// (tm.GetDay()!=ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);                        // tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)tm.wMonth;								// tm.GetMonth();
		ucBuf1[7] = (BYTE)tm.wDay;									// tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;									// tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;								// tm.GetMinute();
		ucBuf1[15]=0;	
		for (i = 0; i < 15; i++)	
			ucBuf1[15] += ucBuf1[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf1);
#endif
		if(ret != 0)	
			return -8;
		return 0;
	}
	else
	{
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBuf2);
#else
		ret = SMT_ReadBlock(sector, 2, ucBuf2);
#endif
		if(ret != 0)	
			return -9;
		ucCheck = 0;
		for(i=0;i<15;i++)	
			ucCheck+=ucBuf2[i];
		if(ucCheck != ucBuf2[15])	
			return 2;
		i = nMoney;
		ucBuf2[0] = i%256;
		ucBuf2[1] = i/256;
		ucBuf2[2] = i/256/256;
		i = nCnt;//ucBuf2[3]*256+ucBuf2[4];
		ucBuf2[3] = i/256;
		ucBuf2[4] = i%256;
		//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//����ϴν��������뵱ǰʱ�䲻ͬ������ۼ����ѽ������
		if (tm.wDay != ucBuf2[7])                               // (tm.GetDay()!=ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);					// tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)tm.wMonth;							// tm.GetMonth();
		ucBuf2[7] = (BYTE)tm.wDay;								// tm.GetDay();
		ucBuf2[8] = (BYTE)tm.wHour;								// tm.GetHour();
		ucBuf2[9] = (BYTE)tm.wMinute;							// tm.GetMinute();
		ucBuf2[15]=0;	
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf2);
#else
		ret = SMT_WriteBlock(sector, 0, ucBuf2);
#endif
		if (ret != 0)	
			return -12;
	}
	return 0;
}

int __stdcall GZDXC_check_card()
{
	int ret,card_id;
	double money,money1;
	g_cardlogger<<"read card"<<std::endl;
	if(ReadCardNO(&card_id))
	{
		return 1;
	}
	g_cardlogger<<"check card["<<card_id<<"]"<<std::endl;
	if(do_is_exists(card_id,&money))
	{
		return 1;
	}
	g_cardlogger<<"read water"<<std::endl;
	WATER_PACK_INFO2 param;
	memset(&param,0,sizeof param);
	ret = SMT_ReadWaterPackInfo(&param);
	if(ret)
		return -1;

	char curr[17] = "";
	
	(g_cardlogger<<"write water["<<param.balance<<"]["<<param.price1<<"]"<<std::endl).flush();
	
	get_curr_datetime(curr);
	if(param.price1<=0.0001
		||param.price2<=0.0001
		||param.price3<=0.0001)
	{
		// ֱ���޸����Ϊ 10 Ԫ
		param.price1 = 0.0409;
		param.price2 = 0.0409;
		param.price3 = 0.0409;
		money1 = param.balance;
		param.balance = money;
		round_float(&(param.balance),2);
		ret = SMT_WriteWaterPackInfo(&param);
		if(ret)
		{
			//g_cardlogger<<curr<<"write card["<<card_id<<"]fialed["<<ret<<"]"<<std::endl;
			return -1;
		}
		(g_cardlogger<<"success "<<curr<<" card["<<card_id<<"]money["<<money1<<"]"<<std::endl).flush();
	}
	else if(param.balance >= 50.00001)
	{
		param.price1 = 0.0409;
		param.price2 = 0.0409;
		param.price3 = 0.0409;
		money1 = param.balance;
		param.balance = money;
		round_float(&(param.balance),2);
		ret = SMT_WriteWaterPackInfo(&param);
		if(ret)
		{
			//g_cardlogger<<curr<<"write card["<<card_id<<"]fialed["<<ret<<"]"<<std::endl;
			return -1;
		}
		(g_cardlogger<<"success "<<curr<<" card["<<card_id<<"]money["<<money1<<"]"<<std::endl).flush();
	}
	else
	{
		//g_cardlogger<<curr<<" card["<<card_id<<"] not need"<<std::endl;
	}
	return 0;
}


void __stdcall GZ_SetWaterCardType(int t)
{
	g_WaterCardType = t;

}
// �����ʼ����������
void __stdcall GZ_SetInitSect(int sect,int need)
{
	if(sect < GZ_CARD_SECT && sect > 39)
		return ;
	g_init_sect_map[sect] = need;
}
int __stdcall ReadCardMainKey2(short wantFlag)
{
	int ret = -1;

	if (TRUE == has_read_main_key && 
		(AUTH_CARD_FLAG == wantFlag || -1 == wantFlag)
		)
	{
		return 0;
	}

	unsigned char work_key[9] = "";
	if (SMT_ReadAuthCard2(work_key, &AUTH_CARD_FLAG) == 0)
	{
		if((AUTH_CARD_FLAG & wantFlag)!=0 || -1 == wantFlag)
		{
			has_read_main_key = TRUE;
			ret = 0;
			SMT_AutoDll(work_key);
			SMT_ControlBuzzer();
		}
	}

	return ret;
}