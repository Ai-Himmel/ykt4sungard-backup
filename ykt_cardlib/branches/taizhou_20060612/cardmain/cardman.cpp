// cardman.cpp : Defines the entry point for the DLL application.
//
/** 
 * ģ����					�������
 * �ļ���					cardman.cpp
 * �ļ�ʵ�ֹ���				�������ܺ���
 * ����						����
 * �汾						V0.1
 * ����						2005-06-25
 * ��ע
 * $Id: cardman.cpp 12 2006-06-12 01:22:50Z cheng.tang $
 */

#include "stdafx.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cardmng.h"
#include "cardutil.h"

/////////////////////////////////////////////////////////////////////
// ���� SmartCom411DXQ �⺯��
static HINSTANCE hSmartComDLL = NULL;
typedef INT (CALLBACK* LPSMT_ConnectMF280)(int ,int);
typedef INT (CALLBACK* LPSMT_ControlBuzzer)(void);
typedef INT (CALLBACK* LPSMT_CloseMF280)(void);	
typedef INT (CALLBACK* LPSMT_CreateGreyCard)(BOOL bPersonalFlag,BOOL bStateFlag, BOOL bBankInfo,BOOL bPacketFlag[8]);
typedef INT (CALLBACK* LPSMT_WriteCardStateInfo)(unsigned char ucShowCardNo[5],int nDealCardNo[1],unsigned char ucDeadLineDate[3],unsigned char ucCardRightType[1]);
typedef INT (CALLBACK* LPSMT_PacketAddMomey)(int ,int );
typedef INT (CALLBACK* LPSMT_PacketSetMoney)(int ,int );
typedef INT (CALLBACK* LPSMT_AutoDll)(unsigned char *);
typedef INT (CALLBACK* LPSMT_JudgeAutoFlag)();
typedef INT (CALLBACK* LPSMT_RequestCardExist)(unsigned char *,unsigned char *);
typedef INT (CALLBACK* LPSMT_ReadCardStateInfo)(unsigned char ucShowCardNo[5],int nDealCardNo[1],unsigned char ucDeadLineDate[3],unsigned char ucCardRightType[1]);
typedef INT (CALLBACK* LPSMT_WritePersonalInfo)(unsigned char ucName[8],unsigned char ucDutyNo[4],unsigned char ucCertificateNo[20],unsigned char ucDepartmentNo[10],unsigned char ucIdentifyNo[4],unsigned char ucSexNo[1], unsigned char ucCardNo[20]);
typedef INT (CALLBACK* LPSMT_ReadPersonalInfo)(unsigned char ucName[8],unsigned char ucDutyNo[4],unsigned char ucCertificateNo [20],unsigned char ucDepartmentNo[10],unsigned char ucIdentifyNo[4],unsigned char ucSexNo[1] ,unsigned char ucCardNo[20]);
typedef INT (CALLBACK* LPSMT_ChangeName)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeDutyNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeCerificateNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeDepartmentNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeIdentifyNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeSexNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ReadPacketInfo)(int,LOOPPURSEINFO *LoopPurseInfo);
typedef INT (CALLBACK* LPSMT_ChangeDeadLineDate)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeCardRightType)(unsigned char ucCardRightType[1]);
typedef INT (CALLBACK* LPSMT_WritePersonalPassword)(unsigned char PersonalPsd[3]);
typedef INT (CALLBACK* LPSMT_ReadPersonalPassword)(unsigned char PersonalPsd[3]);
typedef INT (CALLBACK* LPSMT_ClearCard)();
typedef INT (CALLBACK* LPSMT_SleepCard)();
typedef INT (CALLBACK* LPSMT_WriteLibraryNo)(unsigned char ucLibraryNo[13]);
typedef INT (CALLBACK* LPSMT_ReadLibraryNo)(unsigned char ucLibraryNo[13]);
typedef INT (CALLBACK* LPSMT_ChangeCardNo)(unsigned char ucCardNo[20]);
typedef INT (CALLBACK* LPSMT_ChangeShowCardNo)(unsigned char ucShowCardNo[5]);
typedef INT (CALLBACK* LPSMT_Login_With_UserKey )(int Sector,unsigned char *Buffer,int PaDSelect);
typedef INT (CALLBACK* LPSMT_WriteBlock )(int Sector,int BlockNo,BYTE *BlockBuf);
typedef INT (CALLBACK* LPSMT_ReadBlock )(int Sector,int BlockNo,BYTE *BlockBuf);
typedef INT (CALLBACK* LPSMT_ReadAuthCard)(BYTE manKey[8]);
typedef INT (CALLBACK* LPSMT_ReadAuthCard2)(BYTE manKey[8],short * flag);

//typedef INT (CALLBACK* LPSMT_SMT_ReadLibraryNo)(unsigned char ucLibraryNo[13]);
LPSMT_ConnectMF280				SMT_ConnectMF280=NULL;
LPSMT_ControlBuzzer				SMT_ControlBuzzer=NULL;
LPSMT_CloseMF280				SMT_CloseMF280=NULL;
LPSMT_CreateGreyCard			SMT_CreateGreyCard=NULL;
LPSMT_WriteCardStateInfo		SMT_WriteCardStateInfo=NULL;
LPSMT_AutoDll					SMT_AutoDll=NULL;
LPSMT_JudgeAutoFlag				SMT_JudgeAutoFlag=NULL;
LPSMT_RequestCardExist			SMT_RequestCardExist=NULL;
LPSMT_ReadCardStateInfo			SMT_ReadCardStateInfo=NULL;
LPSMT_WritePersonalInfo			SMT_WritePersonalInfo=NULL;
LPSMT_ReadPersonalInfo			SMT_ReadPersonalInfo=NULL;
LPSMT_WriteLibraryNo			SMT_WriteLibraryNo=NULL;
LPSMT_ReadLibraryNo				SMT_ReadLibraryNo=NULL;
LPSMT_ChangeName				SMT_ChangeName=NULL;
LPSMT_ChangeDutyNo				SMT_ChangeDutyNo=NULL;
LPSMT_ChangeCerificateNo		SMT_ChangeCerificateNo=NULL;
LPSMT_ChangeDepartmentNo		SMT_ChangeDepartmentNo=NULL;
LPSMT_ChangeIdentifyNo			SMT_ChangeIdentifyNo=NULL;
LPSMT_ChangeSexNo				SMT_ChangeSexNo=NULL;
LPSMT_ChangeCardNo				SMT_ChangeCardNo=NULL;
LPSMT_ChangeDeadLineDate		SMT_ChangeDeadLineDate=NULL;
LPSMT_ChangeCardRightType		SMT_ChangeCardRightType=NULL;
LPSMT_WritePersonalPassword		SMT_WritePersonalPassword=NULL;
LPSMT_ReadPersonalPassword		SMT_ReadPersonalPassword=NULL;

// ������
LPSMT_Login_With_UserKey		SMT_Login_With_UserKey=NULL;
LPSMT_WriteBlock				SMT_WriteBlock=NULL;
LPSMT_ReadBlock					SMT_ReadBlock=NULL;
LPSMT_ReadAuthCard				SMT_ReadAuthCard=NULL;
LPSMT_ReadAuthCard2				SMT_ReadAuthCard2=NULL;

//Ǯ������
LPSMT_PacketSetMoney     SMT_PacketSetMoney=NULL;
LPSMT_PacketAddMomey     SMT_PacketAddMomey=NULL;
LPSMT_ReadPacketInfo	 SMT_ReadPacketInfo=NULL;
LPSMT_ClearCard		 SMT_ClearCard=NULL;
LPSMT_SleepCard		 SMT_SleepCard=NULL;
LPSMT_ChangeShowCardNo	SMT_ChangeShowCardNo=NULL;

//////////////////////////////////////////////////////////////////////////

/*��������ID��*/
typedef long (CALLBACK * LPRequestCard )(char * ucSerialNo,char * ucType);
/*��ʼ������*/
typedef short (CALLBACK * LPConnectMF )(long port,long band);
/*���ùرմ���*/
typedef short (CALLBACK* LPCloseMF )();
/*��д����Ȩ*/
typedef long (CALLBACK * LPReaderAuthor)(char * buf);

/////////////////////////////////////////////////////////////////
// ���� CardDLL �⺯��
static HINSTANCE hCardDLL = NULL;

LPRequestCard			RequestCard=NULL;
LPConnectMF				ConnectMF=NULL;
LPCloseMF				CloseMF=NULL;
LPReaderAuthor			ReaderAuthor=NULL;


//////////////////////////////////////////////////////////////////////////
// ���� DesDLL �⺯��
static HINSTANCE hDesDLL;
typedef long (CALLBACK * lpgen_user_card_keyA )(BYTE * base_key,BYTE * buf,BYTE * key);
typedef long (CALLBACK * lpgen_user_card_keyB )(BYTE * base_key,BYTE * buf, BYTE * key);
typedef long (CALLBACK * lpgen_auth_card_keyA)(BYTE seed[8],BYTE key[6]);
typedef long (CALLBACK * lpgen_auth_card_keyB)(BYTE seed[8],BYTE key[6]);
typedef long (CALLBACK* lpdecrypt_work_key)(BYTE src_key[8],BYTE des_key[8]);
typedef long (CALLBACK* lpencrypt_work_key)(BYTE src_key[8],BYTE des_key[8]);
typedef long (CALLBACK* lpget_check_char)(BYTE buf[16]);
typedef int (CALLBACK* lpgen_extra_keyA)(BYTE* key,BYTE* text,BYTE* keyA);


lpgen_user_card_keyA	gen_user_card_keyA = NULL;
lpgen_user_card_keyB	gen_user_card_keyB = NULL;
lpgen_auth_card_keyA	gen_auth_card_keyA = NULL;
lpgen_auth_card_keyB	gen_auth_card_keyB = NULL;
lpencrypt_work_key		encrypt_work_key   = NULL;
lpdecrypt_work_key		decrypt_work_key   = NULL;
lpget_check_char		get_check_char	   = NULL;
lpgen_extra_keyA		gen_extra_keyA	   = NULL;


//////////////////////////////////////////////////////////////////////////

// ����������
#define SMARD_CARD_SECT_NO 32
// ��Կ����
#define CARD_KEY_LEN 6
// ��Կ���ڵĿ��
#define PASSWD_BLOCK_NUM 3

static BYTE CARD_INIT_KEY[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

// ����ʱ�Ŀ���λ
static BYTE CARD_INIT_CTRL_BIT[] = {0xFF,0x07,0x80,0x69};

// ��ʼ����ʱд��Ŀ���λ
static BYTE CARD_NEW_CTRL_BIT[] = {0x7F,0x07,0x88,0x00};

// ��Ȩ��Կ
static BYTE CARD_MAIN_KEY[9] = "";

// ��Ȩ��־
static short AUTH_CARD_FLAG = -1;

// ������Ȩ����Կʱ������
static BYTE AUTH_CARD_SEED[8] = "";

// ������
static BYTE PHILIPS_CARD_TYPE[] = {0x18,0};

#define CARD_KEY_A 0
#define CARD_KEY_B 1

//////////////////////////////////////////////////////////////
//// 
/** 
 * @brief �����Ƿ��Ѿ���
 */
static BOOL com_is_open = FALSE;

/** 
 * @brief �ǲ����Ѿ���ȡ��Ȩ��
 */
static BOOL has_read_main_key = FALSE;

/*
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
*/
/** 
 * @brief ���� SmartCom411DXQ ��
 * 
 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
 */
static int LoadSmartCom411DLL()
{
	if(hSmartComDLL)
		return 0;
    hSmartComDLL = LoadLibrary("SmartCom411DXQ.dll");
	if(!hSmartComDLL)
	{
		//AfxMessageBox(-1,"װ��SmartCom411DXQ.dll��̬��ʧ��");
		return -1;
	}
	
	SMT_ConnectMF280		 = (LPSMT_ConnectMF280)GetProcAddress(hSmartComDLL,"SMT_ConnectMF280");
	SMT_ControlBuzzer        = (LPSMT_ControlBuzzer)GetProcAddress(hSmartComDLL,"SMT_ControlBuzzer");
	SMT_CloseMF280           = (LPSMT_CloseMF280)GetProcAddress(hSmartComDLL,"SMT_CloseMF280");
	SMT_CreateGreyCard       = (LPSMT_CreateGreyCard)GetProcAddress(hSmartComDLL,"SMT_CreateGreyCard");
	SMT_WriteCardStateInfo   = (LPSMT_WriteCardStateInfo)GetProcAddress(hSmartComDLL,"SMT_WriteCardStateInfo");
	SMT_PacketAddMomey       = (LPSMT_PacketAddMomey)GetProcAddress(hSmartComDLL,"SMT_PacketAddMomey");
	SMT_PacketSetMoney       = (LPSMT_PacketSetMoney)GetProcAddress(hSmartComDLL,"SMT_PacketSetMoney");
	SMT_AutoDll				 = (LPSMT_AutoDll)GetProcAddress(hSmartComDLL,"SMT_AutoDll");
	SMT_JudgeAutoFlag  	     = (LPSMT_JudgeAutoFlag)GetProcAddress(hSmartComDLL,"SMT_JudgeAutoFlag");
    SMT_RequestCardExist  	 = (LPSMT_RequestCardExist)GetProcAddress(hSmartComDLL,"SMT_RequestCardExist");
	SMT_ReadCardStateInfo  	 = (LPSMT_ReadCardStateInfo)GetProcAddress(hSmartComDLL,"SMT_ReadCardStateInfo");
    SMT_WritePersonalInfo  	 = (LPSMT_WritePersonalInfo)GetProcAddress(hSmartComDLL,"SMT_WritePersonalInfo");
	SMT_ReadPersonalInfo     = (LPSMT_ReadPersonalInfo)GetProcAddress(hSmartComDLL,"SMT_ReadPersonalInfo");
	SMT_ChangeName           = (LPSMT_ChangeName)GetProcAddress(hSmartComDLL,"SMT_ChangeName");
	SMT_ChangeDutyNo         = (LPSMT_ChangeDutyNo)GetProcAddress(hSmartComDLL,"SMT_ChangeDutyNo");
	SMT_ChangeCerificateNo   = (LPSMT_ChangeCerificateNo)GetProcAddress(hSmartComDLL,"SMT_ChangeCerificateNo");
	SMT_ChangeDepartmentNo   = (LPSMT_ChangeDepartmentNo)GetProcAddress(hSmartComDLL,"SMT_ChangeDepartmentNo");
	SMT_ChangeIdentifyNo     = (LPSMT_ChangeIdentifyNo)GetProcAddress(hSmartComDLL,"SMT_ChangeIdentifyNo");
	SMT_ChangeSexNo          = (LPSMT_ChangeSexNo)GetProcAddress(hSmartComDLL,"SMT_ChangeSexNo");
    SMT_ReadPacketInfo       = (LPSMT_ReadPacketInfo)GetProcAddress(hSmartComDLL,"SMT_ReadPacketInfo");
	SMT_ChangeDeadLineDate   = (LPSMT_ChangeDeadLineDate)GetProcAddress(hSmartComDLL,"SMT_ChangeDeadLineDate");
	SMT_ChangeCardRightType  = (LPSMT_ChangeCardRightType)GetProcAddress(hSmartComDLL,"SMT_ChangeCardRightType");
	SMT_WritePersonalPassword   = (LPSMT_ChangeDeadLineDate)GetProcAddress(hSmartComDLL,"SMT_WritePersonalPassword");
	SMT_ReadPersonalPassword  = (LPSMT_ChangeCardRightType)GetProcAddress(hSmartComDLL,"SMT_ReadPersonalPassword");
	SMT_SleepCard  = (LPSMT_SleepCard)GetProcAddress(hSmartComDLL,"SMT_SleepCard");
	SMT_ClearCard			  = (LPSMT_ClearCard)GetProcAddress(hSmartComDLL,"SMT_ClearCard");
	SMT_WriteLibraryNo		  = (LPSMT_WriteLibraryNo)GetProcAddress(hSmartComDLL,"SMT_WriteLibraryNo");
	SMT_ReadLibraryNo		  = (LPSMT_ReadLibraryNo)GetProcAddress(hSmartComDLL,"SMT_ReadLibraryNo");
	SMT_ChangeCardNo		  = (LPSMT_ChangeCardNo)GetProcAddress(hSmartComDLL,"SMT_ChangeCardNo");
	SMT_ChangeShowCardNo	  = (LPSMT_ChangeShowCardNo)GetProcAddress(hSmartComDLL,"SMT_ChangeShowCardNo");
	//////////////////////////////////////////////////////////////////////////
	SMT_Login_With_UserKey	  = (LPSMT_Login_With_UserKey)GetProcAddress(hSmartComDLL,"SMT_Login_With_UserKey");
	SMT_WriteBlock			  = (LPSMT_WriteBlock)GetProcAddress(hSmartComDLL,"SMT_WriteBlock");
	SMT_ReadBlock			  = (LPSMT_ReadBlock)GetProcAddress(hSmartComDLL,"SMT_ReadBlock");
	SMT_ReadAuthCard		  = (LPSMT_ReadAuthCard)GetProcAddress(hSmartComDLL,"SMT_ReadAuthCard");
	SMT_ReadAuthCard2		  = (LPSMT_ReadAuthCard2)GetProcAddress(hSmartComDLL,"SMT_ReadAuthCard2");

	if ((!SMT_ConnectMF280) ||
		(!SMT_ControlBuzzer) ||
		(!SMT_CloseMF280) ||
		(!SMT_CreateGreyCard) ||
		(!SMT_WriteCardStateInfo) ||
		(!SMT_PacketAddMomey) ||
		(!SMT_PacketSetMoney) ||
		(!SMT_AutoDll) ||
		(!SMT_JudgeAutoFlag) ||
		(!SMT_RequestCardExist) ||
		(!SMT_ReadCardStateInfo) ||
		(!SMT_WritePersonalInfo) ||
		(!SMT_ReadPersonalInfo) ||
		(!SMT_ChangeName) ||
		(!SMT_ChangeDutyNo) ||
		(!SMT_ChangeCerificateNo) ||
		(!SMT_ChangeDepartmentNo) ||
		(!SMT_ChangeIdentifyNo) ||
		(!SMT_ChangeSexNo) ||
		(!SMT_ReadPacketInfo) ||
		(!SMT_ChangeDeadLineDate) ||
		(!SMT_ChangeCardRightType) ||
		(!SMT_WritePersonalPassword)||
		(!SMT_ReadPersonalPassword)||
		(!SMT_SleepCard)||
		(!SMT_ClearCard)||
		(!SMT_WriteLibraryNo)||
		(!SMT_ReadLibraryNo)||
		(!SMT_ChangeCardNo)||
		(!SMT_ChangeShowCardNo)||
		(!SMT_Login_With_UserKey)||
		(!SMT_WriteBlock)||
		(!SMT_ReadAuthCard2))
	{
		FreeLibrary(hSmartComDLL);
		hSmartComDLL = NULL;
		return -2;
	}
	return 0;
}

/** 
 * @brief ���� CardDLL ��
 * 
 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
 */
static int LoadCardDLL()
{
	if( hCardDLL )
		return 0;
	hCardDLL = LoadLibrary("carddll.dll");
	if( !hCardDLL )
	{
		return -1;
	}

	
	RequestCard	= (LPRequestCard)GetProcAddress(hCardDLL,"RequestCard");
	ConnectMF	= (LPConnectMF)GetProcAddress(hCardDLL,"ConnectMF");	
	CloseMF		= (LPCloseMF)GetProcAddress(hCardDLL,"CloseMF");
	ReaderAuthor= (LPReaderAuthor)GetProcAddress(hCardDLL,"ReaderAuthor");

	if(
		(!RequestCard) ||
		(!ConnectMF)||
		(!CloseMF) ||
		(!ReaderAuthor)
		)
	{
		FreeLibrary(hCardDLL);
		hCardDLL = NULL;
		return -2;
	}
	return 0;
}
/** 
 * @brief ���� DesDLL ��
 * 
 * @return - �ɹ����� 0�� ʧ�ܷ���-1
 */
static int LoadDesDLL()
{
	if( hDesDLL )
	{
		return 0;
	}
	hDesDLL = LoadLibrary("desdll.dll");
	if( !hDesDLL )
	{
		return -1;
	}
	gen_user_card_keyA = (lpgen_user_card_keyA)GetProcAddress(hDesDLL,"gen_user_card_keyA");
	gen_user_card_keyB = (lpgen_user_card_keyB)GetProcAddress(hDesDLL,"gen_user_card_keyB");
	gen_auth_card_keyA = (lpgen_auth_card_keyA)GetProcAddress(hDesDLL,"gen_auth_card_keyA");
	gen_auth_card_keyB = (lpgen_auth_card_keyB)GetProcAddress(hDesDLL,"gen_auth_card_keyB");
	encrypt_work_key = (lpencrypt_work_key)GetProcAddress(hDesDLL,"encrypt_work_key");
	decrypt_work_key = (lpdecrypt_work_key)GetProcAddress(hDesDLL,"decrypt_work_key");
	get_check_char = (lpget_check_char)GetProcAddress(hDesDLL,"get_check_char");
	gen_extra_keyA = (lpgen_extra_keyA)GetProcAddress(hDesDLL,"gen_extra_keyA");
	if( 
		(!gen_user_card_keyA)||
		(!gen_user_card_keyB)||
		(!gen_auth_card_keyA)||
		(!gen_auth_card_keyB)||
		(!encrypt_work_key)||
		(!decrypt_work_key)||
		(!get_check_char) ||
		(!gen_extra_keyA)
		)
	{
		FreeLibrary(hDesDLL);
		hDesDLL = NULL;
		return -2;
	}
	return 0;
}
/*
	�жϴ����Ƿ��Ѿ���
*/
static BOOL Is_Com_open()
{
	return com_is_open;
}
/** 
 * @brief ��ӿں�������ȡ��������ID
 * 
 * @param card_id - [out]��ȡ���Ŀ�����ID�ţ�����Ϊ4���ֽ�
 * @param card_type - [out] ��ȡ���Ŀ������ͣ�����Ϊ2���ֽ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1
 */
CARD_API int __stdcall ReadCardPhyID(BYTE card_id[4],BYTE card_type[2])
{
	return SMT_RequestCardExist(card_id,card_type);
}
/*
static int char2int(const char * value,int len,bool isHex)
{
	int ret = 0;
	int factor = 10;
	if( isHex )
		factor = 16;
	for(int i = len - 1 ;i >= 0;--i)
	{
		char c = value[i];
		if( c >= 'a' && c <= 'f')
			c -= 32;
		if(c >= '0' && c <= '9')
			ret += (c - '0') * (int)pow(factor,(len - i - 1));
		else if(c >= 'A' && c <= 'F' && isHex)
			ret += (c - 'A' + 10) * (int)pow(factor,(len - i - 1));
		else
			return ret;
	}
	return ret;
}
*/
/*
 *	��ȡ��Ȩ��Կ
 *  ����ֵ��
		�ɹ����� TRUE 
		���ɹ����� FALSE
 */
static BOOL Read_Author_Key()
{
	if( TRUE == has_read_main_key)
	{
		return TRUE;
	}
	if( SMT_ReadAuthCard2(CARD_MAIN_KEY,&AUTH_CARD_FLAG) == 0 )
	{
		has_read_main_key = TRUE;
		SMT_AutoDll(CARD_MAIN_KEY);
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
	
	assert(sect >= 0 || sect < SMARD_CARD_SECT_NO);

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
/** 
 * @brief д���ݵ�����ָ��������ָ����
 * 
 * @param sect - ������
 * @param block - ���
 * @param buf - ������������Ϊ16���ֽ�
 * 
 * @return - �ɹ����� 0��ʧ�ܷ���-1
 */
static int WriteCardData(long sect,long block,BYTE * buf)
{
	assert(buf != NULL);
	return SMT_WriteBlock(sect,block,buf);
}
/** 
 * @brief д������������
 * 
 * @param err_code - [out]�������
 * @param pFunc - CALLBACE ������������øú���д��
 * @param lpCallBack - CALLBACE �����������ڴ��������е��øú���������ΪNULL
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
static int WriteCardBlock(int *err_code,PWriteDataFunc pFunc,LPProcessCallBack lpCallBack)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key_a[7] = "";
	BYTE card_key_b[7] = "";
	int current_key, old_key;
	BOOL login_sect_succ = FALSE;
	
	CardKeyData card_key[3];
	
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
	if( gen_user_card_keyA(CARD_MAIN_KEY,card_id
			,card_key_a) != 0 )
	{
		*err_code = E_GEN_CARD_KEY_A_ERROR;
		return -1;
	}
	if( gen_user_card_keyB(CARD_MAIN_KEY,card_id
			,card_key_b) != 0 )
	{
		*err_code = E_GEN_CARD_KEY_B_ERROR;
		return -1;
	}
	// ��ʼ�� key ������
	memset((void *)card_key,0,sizeof(card_key));

	card_key[0].flag = CARD_KEY_A;
	memcpy(card_key[0].key,CARD_INIT_KEY,sizeof(CARD_INIT_KEY));

	card_key[1].flag = CARD_KEY_A;
	memcpy(card_key[1].key,card_key_a,sizeof(card_key_a));

	card_key[2].flag = CARD_KEY_B;
	memcpy(card_key[2].key,card_key_b,sizeof(card_key_b));
	
	// �ٶ�һ�ο����һ�¿� ID
	BYTE card_id_2[5] = "";
	SMT_RequestCardExist(card_id_2,card_type);
	if( memcmp(card_id,card_id_2,4) != 0)
	{
		* err_code = E_READ_CARD_ERROR;
		return -1;
	}
	// ������Ե�¼�� key ������
	current_key = 2;
	for(sect = 0;sect < SMARD_CARD_SECT_NO; ++sect)
	{
		// ���ûص�����
		if( lpCallBack != NULL )
			lpCallBack(sect);
		// ���γ�ʼ��ÿ������
		old_key = current_key;
		login_sect_succ = FALSE;
		// ���ҿ��Ե�¼�� key 
		while(TRUE)
		{
			// �����¼�ɹ� ����ѭ��
			if( LoginCardSect(sect,card_key[current_key].key
				,card_key[current_key].flag,card_type) == 0)
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key--;
			if( current_key < 0 )
				current_key = 2;
			if (current_key == old_key)
				break;
		}
		// �жϵ�ǰ�����Ƿ�ɹ���¼
		if (login_sect_succ == FALSE)
		{
			*err_code = E_CARD_LOGIN_ERROR;
			return -1;
		}
		// ����д���ص�����
		if( pFunc != NULL )
		{
			if( pFunc(sect,&card_key[1],&card_key[2],card_type,
				&card_key[current_key]) != 0)
			{
				// д�����ɹ�
				*err_code = E_CARD_WRITE_ERROR;
				return -1;
			}
		}
	}
	return 0;
}

/** 
 * @brief ��ӿں�������ȡ����������
 * 
 * @param startSect - ��ʼ������
 * @param endSect - ����������
 * @param block - ��ȡ�Ŀ飬��ȡ�������� 1 | 2 | 4 | 8 = 15
 *				  1:0 ��  2:1��  4:2��  8:3��
 * @param lpFunc - CALLBACK��������ȡ�������øú���
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
CARD_API int __stdcall ReadCardBlock(int startSect,int endSect
									 ,short block,LPGetBlockData lpFunc)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key_a[7] = "";
	BYTE card_key_b[7] = "";
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
	if( gen_user_card_keyA(CARD_MAIN_KEY,card_id
			,card_key_a) != 0 )
	{
		return -1;
	}
	if( gen_user_card_keyB(CARD_MAIN_KEY,card_id
			,card_key_b) != 0 )
	{
		return -1;
	}
	// ��ʼ�� key ������
	memset((void *)card_key,0,sizeof(card_key));

	card_key[0].flag = CARD_KEY_A;
	memcpy(card_key[0].key,CARD_INIT_KEY,sizeof(CARD_INIT_KEY));

	card_key[1].flag = CARD_KEY_A;
	memcpy(card_key[1].key,card_key_a,sizeof(card_key_a));

	card_key[2].flag = CARD_KEY_B;
	memcpy(card_key[2].key,card_key_b,sizeof(card_key_b));
	// ������Ե�¼�� key ������
	current_key = 0;
	for(sect = startSect;sect < endSect + 1; ++sect)
	{
		// ���γ�ʼ��ÿ������
		old_key = current_key;
		login_sect_succ = FALSE;
		// ���ҿ��Ե�¼�� key 
		while(TRUE)
		{
			// �����¼�ɹ� ����ѭ��
			if( LoginCardSect(sect,card_key[current_key].key
				,card_key[current_key].flag,card_type) == 0)
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key++;
			if( current_key > 2 )
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
				memset(buf,0,sizeof(buf));
				if(SMT_ReadBlock(sect,b,buf) != 0)
				{
					return -1;
				}
				// ���ö����ص�����
				if( lpFunc != NULL )
				{
					lpFunc(sect,b,buf,
						card_key[current_key].key,
						card_key[current_key].flag);
					
				}
			}
		}
		
	}
	return 0;
}

/** 
 * @brief ��ӿں��������¶�ȡ��Ȩ��
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
CARD_API int __stdcall ResetMainKey()
{
	if( ReaderAuthor((char *)CARD_MAIN_KEY) == 0 )
	{
		SMT_AutoDll(CARD_MAIN_KEY);
		has_read_main_key = TRUE;
		return TRUE;
	}
	return FALSE;
}

/** 
 * @brief ��ӿں�������ȡ��Ȩ��
 * 
 * @param main_key - [out] ��ȡ����Ȩ��Կ
 * @param wantFlag - [in]  ������Ȩ���ļ����������һ��������Ȩ��-1��ʾ������
 * @param readFlag - [out] ��ȡ������Ȩ���ı�־
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1
 */
CARD_API int __stdcall ReadCardMainKey(BYTE * main_key,short wantFlag,
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
	
	if( SMT_ReadAuthCard2(CARD_MAIN_KEY,&AUTH_CARD_FLAG) == 0 )
	{
		if(AUTH_CARD_FLAG == wantFlag || -1 == wantFlag)
		{
			has_read_main_key = TRUE;
			ret = 0;
			SMT_AutoDll(CARD_MAIN_KEY);
			SMT_ControlBuzzer();
			memcpy(main_key,CARD_MAIN_KEY,sizeof(CARD_MAIN_KEY));
			*readFlag = AUTH_CARD_FLAG;
		}
	}
	return ret;
}
/** 
 * @brief ��ӿں�����ʹ����ԿΪ����Ȩ
 * 
 * @param main_key - ��Ȩ��Կ������Ϊ8�ֽ�
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
CARD_API int __stdcall SetCardMainKey(BYTE main_key[8])
{
	if(!Is_Com_open())
	{
		AfxMessageBox("��򿪴���!");
		return -1;
	}
	memcpy(CARD_MAIN_KEY,main_key,sizeof(CARD_MAIN_KEY));
	SMT_AutoDll(CARD_MAIN_KEY);
	SMT_ControlBuzzer();
	has_read_main_key = TRUE;
	return 0;
}
/** 
 * @brief ��ʼ�����ص�����
 * 
 * @param sect - ������
 * @param keya - KEYA
 * @param keyb - KEYB
 * @param card_type - ������
 * @param login_key - ��¼����Կ
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
static int WriteInitNewCardData(long sect,CardKeyData * keya,CardKeyData *keyb
								,BYTE * card_type,CardKeyData * login_key)
{
	BYTE sect_data[17] = "";
	
	/*
	int ret;
	int i;
	if(sect < 12 && sect != 3)
	{
		
		// ����ǰ5����������		
		for(i = 0;i < 3;++i)
		{
			if(sect == 0 && i == 0)
				continue;
			if(sect == 1 && i == 0)
			{
				ret=SMT_ReadBlock(sect,i,sect_data);
				if(ret)
					return ret;
				memset(sect_data,0x00,7);
				memset(sect_data+12,0x00,4);
			}
			else
			{
				memset(sect_data,0,sizeof(sect_data));
			}
			ret = WriteCardData(sect,i,sect_data);
			// ���ɹ�Ҳ����
		}
		//SMT_RequestCardExist(sect_data,sect_data + 6);
		ret = LoginCardSect(sect,login_key->key,login_key->flag,card_type);
		if(ret)
			return -1;
	}
	*/
	// ��ʼ��д�������λ
	memset(sect_data,0,sizeof(sect_data));
	// key A
	memcpy(sect_data,keya->key,CARD_KEY_LEN);
	// control bit
	memcpy(sect_data+CARD_KEY_LEN,CARD_NEW_CTRL_BIT,sizeof(CARD_NEW_CTRL_BIT));
	// key B
	memcpy(sect_data+CARD_KEY_LEN+sizeof(CARD_NEW_CTRL_BIT),keyb->key,CARD_KEY_LEN);
	
	if(WriteCardData(sect,PASSWD_BLOCK_NUM,sect_data) == 0)
	{
		// д���ɹ��������Ƿ��ʼ���ɹ�
		// ����ʹ�� keyA ��¼
		if(LoginCardSect(sect,keya->key
			,keya->flag,card_type) != 0)
		{
			return -1;
		}
		// ����ʹ�� keyB ��¼
		if(LoginCardSect(sect,keyb->key
			,keyb->flag,card_type) != 0)
		{
			return -1;
		}
		return 0;
	}
	return -1;
}

/** 
 * @brief ��ӿں�������ʼ���¿�
 * 
 * @param err_code -[out] �������
 * @param showcardno - 10���ֽڵ���ʾ���ţ�����ΪNULL
 * @param lpCallBack - �ص��������ڴ��������е��øú���������ΪNULL
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
CARD_API int __stdcall InitNewCard(int * err_code,const char* showcardno
								   ,LPProcessCallBack lpCallBack)
{
	if(WriteCardBlock(err_code,WriteInitNewCardData,lpCallBack) != 0)
	{
		*err_code = E_CARD_WRITE_ERROR;
		return -1;
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
	/*
	
	int i;
	if(sect < 5 && sect != 3)
	{
		LoginCardSect(sect,keya->key,keya->flag,card_type);
		// ����ǰ5����������		
		for(i = 0;i < 3;++i)
		{
			if(sect == 0 && i == 0)
				continue;
			if(sect == 1 && i == 0)
			{
				ret=SMT_ReadBlock(sect,i,sect_data);
				if(ret)
					return ret;
				memset(sect_data,0x00,7);
				memset(sect_data+12,0x00,4);
			}
			else
			{
				memset(sect_data,0,sizeof(sect_data));
			}
			ret = WriteCardData(sect,i,sect_data);
		}
		SMT_RequestCardExist(sect_data,sect_data + 6);
		ret = LoginCardSect(sect,login_key->key,login_key->flag,card_type);
	}
	*/
	// ��ʼ��д�������λ
	memset(sect_data,0,sizeof(sect_data));
	// key A
	memcpy(sect_data,CARD_INIT_KEY,CARD_KEY_LEN);
	// control bit
	memcpy(sect_data+CARD_KEY_LEN,CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
	// key B
	memcpy(sect_data+CARD_KEY_LEN+sizeof(CARD_INIT_CTRL_BIT),CARD_INIT_KEY,CARD_KEY_LEN);
	// ����� ������ ��
	
	bool ctrl_bit = false;
	if(!memcmp(login_key->key,keyb->key,sizeof(keyb->key))
		&& card_type[0] == PHILIPS_CARD_TYPE[0])
	{
		// ������Keyb ��¼������Ϊ ������ ��
		ctrl_bit = true;
	}
	
	ret = -1;
	WriteCardData(sect,PASSWD_BLOCK_NUM,sect_data);
	// ����ʹ�� keyB ��¼
	if(LoginCardSect(sect,CARD_INIT_KEY
		,CARD_KEY_A,card_type) == 0 || ctrl_bit)
	{
		ret = 0;
	}
	return ret;
}

/** 
 * @brief ��ӿں��������տ�
 * 
 * @param err_code - [out]�������
 * @param lpFunc - �ص�����������ʱ���ã�����ΪNULL
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
CARD_API int __stdcall RefineCard(int *err_code,LPProcessCallBack lpFunc)
{
	if(SMT_ClearCard() != 0)
	{
		*err_code = E_CARD_WRITE_ERROR;
		return -1;
	}

	if(WriteCardBlock(err_code,WriteRefineCardData,lpFunc) != 0)
	{
		*err_code = E_CARD_WRITE_ERROR;
		return -1;
	}
	SMT_ControlBuzzer();
	return 0;
}

/** 
 * @brief ��ӿں������򿪴���
 * 
 * @param port - ���ں�
 * @param band - ������
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
CARD_API int __stdcall OpenCOM(int port,long band)
{
	//
	int ret = -1;
	if( !Is_Com_open() )
	{
		// ���� card dll
		if( (ret = LoadCardDLL()) )
		{
			return ret;
		}
		// ���� smartcom411 dll
		if( (ret = LoadSmartCom411DLL()) )
		{
			return ret;
		}
		// ���� des dll 
		if( (ret = LoadDesDLL()) )
		{
			return ret;
		}
		// �򿪴���
		ret = ConnectMF((int)port,band);
		com_is_open = (ret == 0);
	}
	if( Is_Com_open())
	{
		return 0;
	}
	else 
		return -1;
}

/** 
 * @brief ��ӿں������رմ���
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
CARD_API int __stdcall CloseCOM()
{
	if( Is_Com_open() )
	{
		com_is_open = (CloseMF() != 0);
	}
	return 0;
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
 * @brief ��ӿں�����������Ȩ��
 * 
 * @param err_code - �������
 * @param lpCallBack - �ص�����������ʱ���� ������ΪNULL
 * 
 * @return - �ɹ�����0��ʧ�ܷ���-1
 */
CARD_API int __stdcall ResetAuthCard(int * err_code,LPProcessCallBack lpCallBack)
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
		AfxMessageBox("��¼����ʧ�ܣ�");
		* err_code = E_CARD_LOGIN_ERROR;
		return -2;
	}
	if( SMT_ReadBlock(sect,1,buf) != 0)
	{
		AfxMessageBox("��ȡ����ʧ�ܣ�");
		* err_code = E_CARD_WRITE_ERROR;
		return -3;
	}
	// key b
	memcpy(priKeyB,buf,CARD_KEY_LEN);
	// block
	priBlock = buf[6] - '0';
	if( priBlock < 0 || priBlock > 2)
	{
		AfxMessageBox("���ݲ��Ϸ���");
		* err_code = E_INVALID_CARD;
		return -3;
	}
	// start pos
	// priStartPos = char2int((const char*)&buf[7],1,true);
	tmp[0] = buf[7];
	priStartPos = (short)strtoul(tmp,NULL,16);
	if( priStartPos < 0 || priStartPos > 10)
	{
		AfxMessageBox("���ݲ��Ϸ���");
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
		AfxMessageBox("��¼����ʧ�ܣ�");
		* err_code = E_CARD_LOGIN_ERROR;
		return -2;
	}
	if( SMT_ReadBlock(sect,2,buf) != 0)
	{
		AfxMessageBox("��ȡ����ʧ�ܣ�");
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
				AfxMessageBox("д��������ʧ�ܣ�");
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			// д����λ����
			strncpy((char*)tmpBuf,(char*)buf,sizeof(tmpBuf));
			if(SMT_WriteBlock(priSect,3,tmpBuf) != 0)
			{
				// key B Ҳ�޷�д��
				AfxMessageBox("д��������ʧ�ܣ�");
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			
		}
		else
		{
			// �޷��� key b ��¼��
			AfxMessageBox("��¼����ʧ�ܣ�");
			*err_code = E_CARD_LOGIN_ERROR;
			return -1;
		}
	}

	// �����Ƿ���ճɹ�
	if( LoginCardSect(priSect,CARD_INIT_KEY,CARD_KEY_A,card_type) != 0)
	{
		AfxMessageBox("��������ʧ�ܣ�");
		* err_code = E_CARD_WRITE_ERROR;
		return -2;
	}
	char msg[128] = "";
	// ������������
	for(sect = 0;sect < SMARD_CARD_SECT_NO;++sect)
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
				AfxMessageBox(msg);
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			// ��Key A ��¼����
			if( LoginCardSect(sect,CARD_INIT_KEY,CARD_KEY_A,card_type) != 0)
			{
				sprintf(msg,"���Ե�¼%d����ʧ�ܣ�",sect);
				AfxMessageBox(msg);
				* err_code = E_CARD_LOGIN_ERROR;
				return -1;
			}
		}
		else if( LoginCardSect(sect,CARD_INIT_KEY,CARD_KEY_A,card_type) == 0)
		{
			// ʹ�� ��ʼ�� ��Կ���е�¼����
			sprintf(msg,"����%dʹ�ó�ʼ��Կ��¼�ɹ���\n�Ƿ�������գ�",sect);
			if(AfxMessageBox(msg,MB_OKCANCEL) == IDCANCEL)
			{
				// �������������,�򷵻�
				* err_code = E_CARD_LOGIN_ERROR;
				return -2;
			}
		}
		else
		{
			sprintf(msg,"��¼����%d����ʧ��",sect);
			AfxMessageBox(msg);
			* err_code = E_CARD_LOGIN_ERROR;
			return -2;
		}
	}
	return 0;
}

/** 
 * @brief ��ʼ����Ȩ����ÿ��������Կ
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
	for(sect = 0;sect < SMARD_CARD_SECT_NO;++sect)
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
				AfxMessageBox(msg);
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
			AfxMessageBox(msg);
			return -1;
		}
		//////////////////////////////////////////////////////////////////////////
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
CARD_API int __stdcall NewAuthCard(BYTE main_key[8],int pri_sect
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
		AfxMessageBox("��Ȩ����������");
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
		AfxMessageBox("��ſ���");
		return -1;
	}
	// ������Կ
	BYTE auth_key[8] = "";
	if( decrypt_work_key(main_key,auth_key) != 0)
	{
		AfxMessageBox("������Կʧ�ܣ�");
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
		AfxMessageBox("������ԿAʧ�ܣ�");
		return -2;
	}
	if(gen_auth_card_keyB(AUTH_CARD_SEED,auth_key_b) != 0)
	{
		AfxMessageBox("������ԿBʧ�ܣ�");
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
		AfxMessageBox("��¼����ʧ�ܣ�");
		return -2;
	}
	if( SMT_WriteBlock(sect,1,buf) !=0 )
	{
		AfxMessageBox("д��ʧ�ܣ�");
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
		AfxMessageBox("��¼����ʧ�ܣ�");
		return -2;
	}
	if( SMT_WriteBlock(sect,2,buf) !=0 )
	{
		AfxMessageBox("д��ʧ�ܣ�");
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
		AfxMessageBox("��¼����ʧ�ܣ�");
		return -2;
	}
	crc = CalAuthCardCRC(auth_key_a,auth_key_b,pri_sect,pri_block,pri_startpos);
	buf[11] = (unsigned char)crc;
	if(SMT_WriteBlock(sect,0,buf) != 0)
	{
		AfxMessageBox("дУ��λʧ��");
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
		AfxMessageBox("��¼����ʧ�ܣ�");
		return -2;
	}
	if( SMT_WriteBlock(sect,pri_block,buf) !=0 )
	{
		AfxMessageBox("д��ʧ�ܣ�");
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
		AfxMessageBox("д��Կ����ʧ�ܣ�");
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
