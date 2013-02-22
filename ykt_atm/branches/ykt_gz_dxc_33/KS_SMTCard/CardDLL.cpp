#include "stdafx.h"
#include "CardDLL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>

int InitInstance();
int ifReadyOK();
//int isConnectMF = -1;    //�ж϶�д���Ƿ�ɹ���ʼ��
static int	ErrCode;
static char ErrMsg[256];

// ������SMARTCOM411DXQ.dll
static unsigned char LOGIN_WATER_KEYA[7] = {0x33, 0x25, 0x26, 0xab, 0xcd, 0xef};   // ���ݴ�ѧ��ר��ˮ��ת�˵�¼��Կ
static unsigned char LOGIN_WATER_KEYB[7] = {0x07, 0x64, 0x36, 0x01, 0x36, 0x00};

unsigned char SMT_UCWORKINGKEY[256]="";
int nAutoFlag = 0;

//////////////////////////////////////////////////////////////////////////
// ��ʼ����
// ��ʼ��������
#define SMARD_CARD_SECT_NO 32
// ��Ȩ��������
#define AUTH_CARD_SECT_NO 32
// ��Կ����
#define CARD_KEY_LEN 6
// ��ʼ����ʱд��Ŀ���λ
static BYTE CARD_NEW_CTRL_BIT[] = {0x7F,0x07,0x88,0x00};
// ����ʱ�Ŀ���λ
static BYTE CARD_INIT_CTRL_BIT[] = {0xFF,0x07,0x80,0x69};
// PHILIP������
static BYTE PHILIPS_CARD_TYPE[] = {0x18,0};
// ��Կ���ڵĿ��
#define PASSWD_BLOCK_NUM 3
// ��Ȩ��Կ
//static BYTE CARD_MAIN_KEY[9] = "";
// �жϴ����Ƿ��Ѿ���
static BOOL com_is_open = FALSE;
// 0����KEYA, 1����KEYB
#define CARD_KEY_A 0
#define CARD_KEY_B 1
// ��ʼ���Ľ�ֵ
static BYTE CARD_INIT_KEY[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
// �ж��Ƿ��Ѷ���Ȩ��
static BOOL has_read_main_key = FALSE;
 
// ���ݴ�ѧ��ר�п�Ƭ��������
#define GZ_UNIVERSITY_TOWN 1			    // ͨ���궨�������ֺ����4k����
#define SMARD_CARD_SECT4K_NO 36				// ��4k������ʼ������
#define PASSWD_BLOCK1_NUM 15				// 32����������ݿ鶼Ϊ16��

// ��Ȩ��־
static short AUTH_CARD_FLAG = -1;
static unsigned char s_water_common_card[2] = {0xF9,0x9E};
static unsigned char s_water_clear_card[2] = {0xF9,0x9C};
static unsigned char s_water_clear_card2[2] = {0xF9,0x9A};
static unsigned char s_water_new_card[2] = {0xF9,0x9D};
static unsigned char s_water_auth_card[2] = {0xF9,0x9F};

//////////////////////////////////////////////////////////////////////////
typedef std::map<int,double> CARD_MONEY_MAP;

CARD_MONEY_MAP g_cardmoney;
std::ofstream g_cardlogger;
//FILE * g_cardlogger = NULL;


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
	g_cardlogger.open("c:\\watercardlog.txt",std::ofstream::out|std::ofstream::app);
	if(!g_cardlogger.good())
		return -1;
	/*
	if((g_cardlogger = fopen("watercardlog.txt","wb+"))==NULL)
	{
		return -1;
	}
	*/
	
	ifs.open("c:\\watercard.lst",std::ifstream::in);
	
	if(!ifs.good())
	{
		//fprintf(g_cardlogger,"load list error\n");
		g_cardlogger<<"open list error"<<std::endl;
		return -1;
	}
	
	g_cardmoney.clear();
	while(!ifs.eof())
	{
		std::getline(ifs,line);
		if(split_string(tokens,line,',') < 2)
			continue;
		int card_id = atoi(tokens[0].c_str());
		double money = atof(tokens[1].c_str());
		g_cardmoney.insert(CARD_MONEY_MAP::value_type(card_id,money));
		//fprintf(g_cardlogger,"card[%d][%f]\n",card_id,money);
		g_cardlogger<<"card["<<card_id<<"]money["<<money<<"]"<<std::endl;
	}
//	fflush(g_cardlogger);
	return 0;
}
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

int __stdcall GZDXC_check_card();

// ������COMM.H�����ݽṹ

// ������COMM.H�����ݽṹ
char bufSmartCom[2056] = "";
char bufDesdll[2056] = "";
char pathBuf[512] = "";
char bufJdcdll[512] = "";
char iniFilePathBuf[512] = "";

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
 	GetIniFile(iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLL1", "", bufSmartCom, sizeof(bufSmartCom), iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLL2", "", bufDesdll, sizeof(bufDesdll), iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLL3", "", bufJdcdll, sizeof(bufJdcdll), iniFilePathBuf);
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
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
/*	FilePathBuf = strncat("\\", pathBuf, 1);*/
	strncat(pathBuf, "\\CardDll.ini", 13);
	strcpy(FilePathBuf, pathBuf);
}
//////////////////////////////////////////////////////////////////////////

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

LPSMT_ConnectMF280				SMT_ConnectMF280=NULL;
LPSMT_ControlBuzzer				SMT_ControlBuzzer=NULL;
LPSMT_CloseMF280				SMT_CloseMF280=NULL;
LPSMT_RequestCardExist			SMT_RequestCardExist=NULL;

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
typedef long (CALLBACK * lpgen_user_card_keyA )(unsigned char *key,unsigned char *text,unsigned char *keyA);;
typedef long (CALLBACK * lpgen_user_card_keyB )(unsigned char *key,unsigned char *text,unsigned char *keyA);;
typedef INT (CALLBACK *lpencrypt_work_key)(unsigned char* text,unsigned char* mtext);
typedef long (CALLBACK* lpgen_auth_card_keyA)(BYTE seed[8],BYTE key[6]);
typedef long (CALLBACK* lpgen_auth_card_keyB)(BYTE seed[8],BYTE key[6]);
typedef long (CALLBACK* lpdecrypt_work_key)(BYTE src_key[8],BYTE des_key[8]);
typedef long (CALLBACK* lpget_check_char)(BYTE buf[16]);
typedef int	 (CALLBACK* lpgen_card_ming_des)(unsigned char *text, unsigned char *user_key);

lpgen_user_card_keyA	gen_user_card_keyA = NULL;
lpgen_user_card_keyB	gen_user_card_keyB = NULL;
lpencrypt_work_key      encrypt_work_key = NULL;
lpgen_auth_card_keyA	gen_auth_card_keyA	= NULL;
lpgen_auth_card_keyB	gen_auth_card_keyB	= NULL;
lpdecrypt_work_key		decrypt_work_key	= NULL;
lpget_check_char		get_check_char		= NULL;
lpgen_card_ming_des     gen_card_ming_des	= NULL;
 
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
	/*
	unsigned char ucSerialNo[5], ucKeyA[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	//1 --- ����KEYA
	SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	ret = SMT_Login_With_UserKey(sector,ucKeyA,0);                        // ���λ�ó�������
	if(ret != 0)
	{
		return -2;//��Ƭ��½ʧ��
	}
	return 0;
	*/
	unsigned char ucSerialNo[5],
				  ucKeyA[6];
	int ret = 0;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	//1 --- ����KEYA
	if (SMARD_CARD_SECT4K_NO == sector)
		gen_card_ming_des(ucSerialNo, ucKeyA);
	else
		SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);

	ret = SMT_Login_With_UserKey(sector, ucKeyA, 0);                       
	if(ret != 0)
	{
		return -2;//��Ƭ��½ʧ��
	}
	return 0;
}

static int Login_Card_Keyb(int sector)
{
	unsigned char ucSerialNo[5], ucKeyB[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//��Ƭ���ڸ�Ӧ��
	//1 --- ����KEYB
	SMT_Cal_KeyB(SMT_UCWORKINGKEY, ucSerialNo, ucKeyB);
	ret = SMT_Login_With_UserKey(sector, ucKeyB, 1);                       
	if(ret != 0)
	{
		return -2;
	}
	return 0;
}

//FreeLibrary(hDLL);
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

int __stdcall ConnectMF(int com,int baud)
{
	int ret = 0;
	if(hDLL == NULL || hDesDLL == NULL || hJdcDLL == NULL)
	{
		ret=Load_Dll();
		if(ret)
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
//	SMT_CloseMF280();
	ret = SMT_ConnectMF280(com,baud);
	if(ret!= 0)
	{
		return ret;
	}
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
//	isConnectMF=-1;
	return 0;
}

//���п�
int __stdcall PublishCard(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	BOOL bPersonalFlag=TRUE;
	BOOL bStateFlag=TRUE;
	BOOL bBankInfo=TRUE;
	BOOL bPacketFlag[8]={TRUE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE};
	int iCardNo[1];
	memset(ucBcdShowCardNo,0,sizeof(ucBcdShowCardNo));

	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	ret=SMT_ClearCard();
	if(ret)
	{
		SetErrMsg(ret,"��ʽ����ʧ��");
		return ret;
	}
	ret = strlen((char*)pc->ShowCardNo);
	if( 10==ret )	
	{
		//SetErrMsg(ret,"��ʾ���ų��Ȳ���10λ");
		//return -4;		     //��ʾ����λ������
		//ת��ΪBCD��
		dec2bcd(pc->ShowCardNo,ucBcdShowCardNo,5);
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
	
	SMT_ControlBuzzer();
	return 0;
}

int ifReadyOK()
{
//	if (isConnectMF) return isConnectMF;

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
//	if (isConnectMF) return isConnectMF;
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

//	if (isConnectMF) return isConnectMF;
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

int __stdcall ReadInfoFromCard(TPublishCard *pc)
{
	/*
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];		//�û���ʹ�ý�ֹ����
	unsigned char ucCardRightType[1];		//Ȩ��λ
	int iCardNo[1];

	ret = ifReadyOK();
	if (ret !=0)
		return ret;

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
	return 0;
	*/
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];		//�û���ʹ�ý�ֹ����
	unsigned char ucCardRightType[1];		//Ȩ��λ
	int iCardNo[1];
	
	ret = ifReadyOK();
	if (ret !=0)
		return ret;
	
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

//���¿���Ϣ
int __stdcall UpdateCardInfo(TPublishCard *CardInfo)
{
	int ret = 0; 
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
	//ת��Ϊ����
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
		if(ret != 0)
		{
			SetErrMsg(ret,"�޸���ʾ����ʱ����");
			return ret;
		}
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

//	if (isConnectMF) return isConnectMF;

	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	int nPacketNo = 1;
	
	memset(LoopPurseInfo,0,sizeof(LOOPPURSEINFO));  //��ǰ�����ڴ淢�������ԭ����û��#pragma pack(1)

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
	/*
	int ret;
	unsigned char ucBuffer[16];	
	ret = Login_Card_Keya(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1,0,ucBuffer);
	if(ret != 0)	
		return ret;
	nCardNo[0] = ucBuffer[0]*256*256+ucBuffer[1]*256+ucBuffer[2];
	return 0;
	*/
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
	}

//////////////////////////////////////////////////////////////////////////
// ����dessdll.dll��	
	if (NULL == hDesDLL)
	{
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
		if (
			(!gen_user_card_keyA) || 
			(!gen_user_card_keyB) ||
			(!encrypt_work_key)	  ||
			(!gen_auth_card_keyA) ||
			(!gen_auth_card_keyB) ||
			(!decrypt_work_key)	  ||	
			(!get_check_char)     ||
			(!gen_card_ming_des)
			)
		{
			FreeLibrary(hDesDLL);
			hDesDLL = NULL;
			return -2;
		}
	}
	
//////////////////////////////////////////////////////////////////////////
// ����JDyktCustomerCardDLL.dll��, ���ݴ�ѧ��ˮ��ת��ר������
	if (NULL == hJdcDLL)
	{
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
	nAutoFlag = 1;										// ���������ӵĶ���
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
	nAutoFlag = 1;
	return 0;
}

// ��������: ��ȡ���к�
// ��������: ���к�����
int __stdcall ReadSerial(unsigned char *serial)
{
	return MF_ReadSeriesNo(serial);
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

// ��������: ��ȡ��Ƭʹ�ý�������
// ��������: ��ֹ����ʱ��
int __stdcall SMT_ReadDeadLineDate(unsigned char ucDeadLineDate[3])
{
	int ret;
	unsigned char ucBuffer[16];

	ret = Login_Card_Keyb(SMARD_CARD_SECT4K_NO);

	if(ret != 0)	
		return ret;

	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO, 6, ucBuffer);			// 36������6��
	if(ret != 0)
		return -6; //����ʧ��

	//memcpy(ucBuffer + 7, ucDeadLineDate, 3);
	memcpy(ucDeadLineDate,ucBuffer+7,3);
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
int __stdcall SMT_WritePersonalPassword(unsigned char PersonalPsd[6])
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

//	memcpy(ucBuffer, PersonalPsd, 3);
	dec2bcd(PersonalPsd, ucBuffer, 3);

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

// ��������: ��Ǯ����Ϣ
// ��������: nPacketNo(Ǯ����), LoopPurseInfo(����Ǯ����Ϣ)
int __stdcall SMT_ReadPacketInfo(int nPacketNo, LOOPPURSEINFO *LoopPurseInfo)   
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if(nPacketNo<1)
		return -1;
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
		LoopPurseInfo->RemainMoney = ucBuf1[0] + ucBuf1[1] * 256 + ucBuf1[2] * 256 * 256;
		LoopPurseInfo->DealTimes   = ucBuf1[3] * 256 + ucBuf1[4];
		LoopPurseInfo->DealYear    = ucBuf1[5];
		LoopPurseInfo->DealMonth   = ucBuf1[6];
		LoopPurseInfo->DealDay     = ucBuf1[7];
		LoopPurseInfo->DealHour    = ucBuf1[8];
		LoopPurseInfo->DealMin     = ucBuf1[9];
		LoopPurseInfo->DealTimes_CurTime = ucBuf1[0x0D];
		LoopPurseInfo->DealTimes_CurDay  = ucBuf1[0X0E];
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
		memcpy(ucBufTmp, ucBuf1, sizeof(ucBufTmp));
#ifdef GZ_UNIVERSITY_TOWN
		ret = SMT_WriteBlock(SMARD_CARD_SECT4K_NO + 1, sector + 2, ucBufTmp);
#else
		ret = SMT_WriteBlock(sector, 2, ucBufTmp);
#endif
		if (ret != 0)	
			return -8;
		i = nMoney;
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
	
	// 
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

// ��������: ���úڿ����
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

// ��������: ������ͨ���
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

// ��������: ��ȡ��֤��2
// ��������: ucWorkKey(������Կ), flag(���λ��)
int __stdcall SMT_ReadAuthCard2(unsigned char ucWorkKey[8],short * flag)
{
	int ret;
	unsigned char ucSerialNo[5]="";
	unsigned char ucInitKeyA[6]="",ucInitKeyB[6]="";
	//////////////////////////////////////////////////////////////////////////
	// ������
	ret = Load_Dll();
	if (ret != 0)
	{
		MessageBox(NULL, "��Ƭ���ڸ�Ӧ��", NULL, MB_OK);
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
	{
		MessageBox(NULL, "��Ƭ���ڸ�Ӧ��", NULL, MB_OK);
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
		MessageBox(NULL, "��Ƭ���ڸ�Ӧ��", NULL, MB_OK);
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

// ��������: ����Ǯ����Ϣ
// ��������: nPacketNo(Ǯ����), pPackInfo(Ǯ����Ϣָ��)
int __stdcall SMT_SetPacketInfo(int nPacketNo,MONEY_PACK_INFO *pPackInfo)
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
// ��������: nPacketNo(Ǯ����), tx_cnt(???)
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

// ��ȡǮ�����
int __stdcall ReadBalance(int nPacketNo,int nBalance[1],int nCnt[1])
{
	char line[10]="";
	char err_msg[10] = "";
	int ret,sector;
	unsigned char ucBuffer[16];
#ifdef GZ_UNIVERSITY_TOWN
	ret = Login_Card_Keya(SMARD_CARD_SECT4K_NO + 1);
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
		return ret;
	}
		
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
	{
		itoa(ret, err_msg, 10);
		MessageBox(NULL, "3", NULL, MB_OK);
		MessageBox(NULL, err_msg, NULL, MB_OK);
		return ret;
	}
	unsigned char ucBuf1[16],ucBuf2[16];
	unsigned char ucCheck;

#ifdef GZ_UNIVERSITY_TOWN
	ret = SMT_ReadBlock(SMARD_CARD_SECT4K_NO + 1, sector, ucBuf1);				// 37��, ��6, ��Ǯ����
#else
	ret = SMT_ReadBlock(sector,0,ucBuf1);
#endif
	if(ret != 0)
	{
		itoa(ret, err_msg, 10);
		MessageBox(NULL, "4", NULL, MB_OK);
		MessageBox(NULL, err_msg, NULL, MB_OK);
		return ret;
	}

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
		{
			itoa(ret, err_msg, 10);
			MessageBox(NULL, "5", NULL, MB_OK);
			MessageBox(NULL, err_msg, NULL, MB_OK);
			return ret;
		}

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
	GZDXC_check_card();
	return 0;	
}

//////////////////////////////////////////////////////////////////////////
#define WATER_SECT_NO  0x0E
#define WATER_SECT_BLK_NO 1
// static unsigned char s_water_temp_key[4] = {0x22,0x33,0x44,0x55};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ���㺯��
//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
// ������ˮ�Ĳ���
//////////////////////////////////////////////////////////////////////////

// ��½��ˮƬ��
static int LoginWaterSection()
{
	return 0;
}

// ��ȡ��ˮ����Ϣ
int __stdcall SMT_ReadWaterPackInfo(WATER_PACK_INFO* info)
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
		info->price1 = 0;
		info->price2 = 0;
		info->price3 = 0;
		info->balance = 0;
	}
	else
	{
		if (ret = DecodeData(data, physical_no, &group_id, &customer_id, &(info->price1), &(info->price2), &(info->price3), &(info->balance)))
			return ret;
	}

	return 0;
}

int WriteCardData(long sect,long block,BYTE * buf)
{
	assert(buf != NULL);
	return SMT_WriteBlock(sect,block,buf);
}

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

int __stdcall SMT_WriteWaterPackInfo(WATER_PACK_INFO* info)
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

	ret = MF_ReadSeriesNo(ucSerialNo);
	if (ret < 0)
		return -1;					// ��Ƭ���ڸ�Ӧ��

	physical_no = ucSerialNo[0] * 256 * 256 * 256 + ucSerialNo[1] * 256 * 256 + ucSerialNo[2] * 256 + ucSerialNo[3];

	ret = SMT_Login_With_UserKey(33, CARD_INIT_KEY, 0);			// ˮ������ֻ��KEYA��¼                      
	if (ret != 0)
	{
		return -2;					// ��Ƭ��½ʧ��
	}

	if (0 == SMT_ReadBlock(33, 0, ucBuffer))
	{
		memcpy(sect_data, LOGIN_WATER_KEYA, CARD_KEY_LEN);
		memcpy(sect_data + CARD_KEY_LEN, CARD_INIT_CTRL_BIT, sizeof(CARD_INIT_CTRL_BIT));
		memcpy(sect_data + CARD_KEY_LEN + sizeof(CARD_INIT_CTRL_BIT), LOGIN_WATER_KEYB, CARD_KEY_LEN);
		if (ret = WriteCardData(33, PASSWD_BLOCK1_NUM, sect_data))
			return ret;
	}

	ret = SMT_Login_With_UserKey(33, LOGIN_WATER_KEYA, 0);			// ˮ������ֻ��KEYA��¼                      
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
		if (ret = SMT_ReadCutId(&customer_id))
			return ret;	
	}
	else
	{
		if (ret = DecodeData(data, physical_no, &group_id, &customer_id, &price4, &price5, &price6, &balance1))
			return ret;
	}

	memset(data, 0, sizeof(data));

	ret = SMT_Login_With_UserKey(33, LOGIN_WATER_KEYA, 0);			// ˮ������ֻ��KEYA��¼                      
	if (ret != 0)
	{
		return -6;					// ��Ƭ��½ʧ��
	}

	group_id = 1;					// ���ݹ��ݴ�ѧ��ˮ������

	if (ret = EncodeData(physical_no, group_id, customer_id, info->price1, info->price2, info->price3, info->balance, data))
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

// ������ˮ����
int __stdcall SMT_WaterSetCapability(int value)
{
	return 0;
}

// ��½��ʼ��
static int LoginOriginalCard(int sect,int keytype = 1)
{
	return 0;
}

// ��ʼ����ˮ��Ϣ
int __stdcall SMT_InitWaterInfo(const WATER_PACK_INFO* info)
{
	return 0;
}

// ��ˮ��֤
int __stdcall SMT_WaterNewAuthCard()
{
	return 0;
}



int __stdcall GZDXC_check_card()
{
	int ret,card_id;
	double money,money1;
	//fprintf(g_cardlogger,"read card\n");
	g_cardlogger<<"read card"<<std::endl;
	if(ReadCardNO(&card_id))
	{
		return 1;
	}
	//fprintf(g_cardlogger,"check card[%d]\n",card_id);
	g_cardlogger<<"check card["<<card_id<<"]"<<std::endl;
	if(do_is_exists(card_id,&money))
	{
		return 1;
	}
	g_cardlogger<<"read water"<<std::endl;
	//fprintf(g_cardlogger,"read water\n");
	WATER_PACK_INFO param;
	memset(&param,0,sizeof param);
	ret = SMT_ReadWaterPackInfo(&param);
	if(ret)
		return -1;
	ret = 0;
	char curr[17] = "";
	
	(g_cardlogger<<"write water["<<param.balance<<"]["<<param.price1<<"]"<<std::endl).flush();
	//fprintf(g_cardlogger,"write water[%f][%f]\n",param.balance,param.price1);

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
		//g_cardlogger<<curr<<" card["<<card_id<<"]money["<<money1<<"]"<<std::endl;
		ret = SMT_WriteWaterPackInfo(&param);
		if(ret)
		{
			//g_cardlogger<<curr<<"write card["<<card_id<<"]fialed["<<ret<<"]"<<std::endl;
			return -1;
		}
		(g_cardlogger<<"success "<<curr<<" card["<<card_id<<"]money["<<money1<<"]"<<std::endl).flush();
		//fprintf(g_cardlogger,"success %s card[%d]money[%f]\n",curr,card_id,money);
		//fflush(g_cardlogger);
	}
	else if(param.balance >= 50.00001)
	{
		param.price1 = 0.0409;
		param.price2 = 0.0409;
		param.price3 = 0.0409;
		money1 = param.balance;
		param.balance = money;
		round_float(&(param.balance),2);
		//g_cardlogger<<curr<<" card["<<card_id<<"]money["<<money1<<"]"<<std::endl;
		ret = SMT_WriteWaterPackInfo(&param);
		if(ret)
		{
			//g_cardlogger<<curr<<"write card["<<card_id<<"]fialed["<<ret<<"]"<<std::endl;
			return -1;
		}
		(g_cardlogger<<"success "<<curr<<" card["<<card_id<<"]money["<<money1<<"]"<<std::endl).flush();
		//fprintf(g_cardlogger,"success %s card[%d]money[%f]\n",curr,card_id,money);
		//fflush(g_cardlogger);
	}
	else
	{
		(g_cardlogger<<curr<<" card["<<card_id<<"] not need"<<std::endl).flush();
	}
	return 0;
}



















