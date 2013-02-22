// kscard.cpp : Defines the initialization routines for the DLL.
#ifndef __KSCARD_H
#define __KSCARD_H
#pragma warning(disable:4786) 
#include "kscard_imp.h"
#include <map>
#include <vector>
#include <string>
#include <windows.h>
#include "kslicense.h"

#include "cardtypemanager.h"

//extern HANDLE g_nHandle;

using namespace std;

enum VALTYPE {VT_UNDEF,VT_BIN,VT_BCD,VT_ASC};
typedef struct 
{
	int  nFieldID;			//�ֶ�ID
	int  nFieldOffset;		//�ֶζ����ļ��е�ƫ�Ƶ�ַ
	int  nFieldSize;		//�ֶγ���
	char szFieldName[32];	//�ֶ�����
	byte ucFieldVal[32];	//�ֶ��ڿ��д洢��ֵ
	VALTYPE nFieldValType;		//�ֶδ洢����
}CARDFIELD;

class CKsCard
{
public:
	CKsCard();
	unsigned long m_uCardSNo;
	ST_BASEINFO   m_ReadBaseInfo;
	ST_PERSONINFO m_ReadPersonInfo;
	ST_TRANSPARA  m_ReadTransPara;
	ST_TRANSDTL   m_ReadTransdtl;
	ST_BASEINFO   m_WriteBaseInfo;
	ST_PERSONINFO m_WritePersonInfo;
	ST_TRANSPARA  m_WriteTransPara;
	map<int,string> mapReadFieldVal,mapWriteFieldVal;
//	int nSingleMaxAmt;
//	int nDayMaxAmt;
	int nCardBalance;
	int nCardDptCnt;
	int nCardPayCnt;
	int nCardSsdCnt;
	char sReadCardPwd[64],sWriteCardPwd[64];
	int SMT_MAC_UpdateBinaryFile( byte ucSFI,byte ucOffset,byte ucLength,byte *ccAppSerailNo,byte *ucData);
	//����¼�ļ�//1�ֽ�SFI��1�ֽڼ�¼�� 1�ֽڳ���
	int InitField();	
	void Clear();
	int ReadRecordFile(byte ucSFI,byte ucRecordNo,byte ucLength,byte *ucData);
	int ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	//int MacReadBinaryFile(byte ucSFI,   byte ucOffset,byte ucLength,byte *ucData);
	int MacReadBinaryFile(const char *sCardPhyID,byte ucSFI,   byte ucOffset,byte ucLength,byte *ucData);
	int ReadBinaryFile4Sam(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int ChangePin( char* coldPin, char* cnewPin);
	int VerifyPin( char* cPin);
	int SelectPacketOneDir(byte *ucRes);
	int SelectSchoolPacketDir(byte *ucRes);
	int SelectBankDir(byte *ucRes);
	int SelectMFDir(byte *ucRes);
	int SelectBaseFile(byte *ucRes);
	int SelectPersonFile(byte *ucRes);
	int SelectTransParaFile(byte *ucRes);
	int ReadBalance(int& cardbalance);
//	int ReadTrandtl(int num);
	int WriteCard(const char *sCardPhyID);
	int ReadPayCnt(int& cardpaycnt,int& cardbalance);
	int ReadDptCnt(int& carddptcnt,int& cardbalance);
	int ReadSsdCnt(int& cardssdcnt);
};

//2.�ṹ��===================================================
typedef struct SCardTableIndex
{
	int		nIndexNo; //������
	char	sIndexName[64]; //��������Ӧ���ƺ���
	char	sIndexValue[64];//��������Ӧ��ֵ
	bool	bStatus;		//��ʾ�Ƿ��Ѿ���ȡ true �Ѷ�  false δ��
}ST_CARDTABLEINDEX;

//����Կ
typedef struct SCardMainKey
{
	byte MK[17];	//������Կ
	byte DPK1[17];	//����1
	byte DPK2[17];	//����2
	byte DLK1[17];  //Ȧ��1
	byte DLK2[17];  //Ȧ��2
	byte DTAC[17];	//�ڲ���ԿTAC
	byte DACK[17];	//�ⲿ��֤0
	byte DUK[17];   //PIN����
	byte DRPK[17];	//PIN��װ
	byte DAMK[17];	//ά����Կ
	byte DACK1[17];	//�ⲿ��֤1
	byte DACK2[17];	//�ⲿ��֤2
	byte DACK3[17];	//�ⲿ��֤3
	byte LDACK[17];	//СǮ���ⲿ��֤��Կ
	byte LDAMK[17];	//СǮ��ά����Կ
	int  bLoad;
}ST_CARDMAINKEY;

typedef struct SuperCardKey
{
	byte DPK1[16];  //����1
	byte DPK2[16];  //����2
	byte DPK3[16];  //����3
	byte DLK1[16];  //Ȧ��1
	byte DLK2[16];  //Ȧ��2
	byte DLK3[16];  //Ȧ��3
	byte DTAC1[16]; //TAC1
	byte DTAC2[16]; //TAC2
	byte DTAC3[16]; //TAC3
	byte DUK[16];   //PIN����
	byte DRPK[16];  //PIN��װ
	byte DAMK[16];  //ά��
	byte DACK[16];  //����
	byte NPK1[16];  //�ڲ���֤����Կ
	byte EPK1[16];  //�ⲿ��֤����Կ1
	byte EPK2[16];  //�ⲿ��֤����Կ2
	byte EPK3[16];  //�ⲿ��֤����Կ3
	byte EPK4[16];  //�ⲿ��֤����Կ4
}ST_SUPERCARDKEY;
//����д��������ֵ
typedef struct SWriteCardInfo
{
	int  nIndex; //������	
	byte sValues[128]; //ֵ
}ST_WRITECARDINFO;

//���������������ֵ
typedef struct SReadCardInfo
{
	int  nIndex; //������	
	byte sValues[128]; //ֵ
}ST_READCARDINFO;


//����������Ϣ
typedef struct SPublicInfo_15
{
	char	sAppSerial[21]; //Ӧ�����к�(���׿���)
	char	sShowCard[11];  //��ʾ����
	int		nCardStatus;	//��״̬
	char	sBlkVer[15];	//�������汾
	char	sDeivceID[13];	//�豸ID��
	int		nFeeType;		//���շ����
	int     nCardType;		//�����
	int		nCardVer;		//���ṹ�汾 
	char	sStartDate[9];  //��������
	char	sValidDate[9];	//��Ч����
	int		nSubsidyBatchNo;//�������κ�
	int		nPublishID;		//���з���ʶ
} ST_PUBLICINFO_15;


//�ֿ��˻�����Ϣ
typedef struct SPersonalInfo_16
{
	int		nCustType;		//�ͻ�����
	int		nCustID;		//�ͻ���
	char	sStuEmpNo[21];	//ѧ����
	char	sName[31];		//����
	char	sDeptCode[21];	//���Ŵ���
	char	sIDNo[33];		//֤������
	int		nIDType;		//֤������
	int		nSex;			//�Ա�		1-��2-Ů
} ST_PERSONALINFO_16;

//���׹����ļ�
typedef struct STradeRule_12
{
	int		nOnceLimitMoney;	//����
	int		nDaySaleLimitMoney; //����
	int		nDetailMax;			//��ϸ���ֵ
} ST_TRADERULE_12;

typedef struct SPublishUserCardInfo
{
	char	sBankNo[21];
	ST_PUBLICINFO_15	sTrFile15;
	ST_PERSONALINFO_16 sTrFile16;
	ST_TRADERULE_12		sTrFile12;
} ST_PUBLISHUSERCARDINFO;


/*
int ks_resetpro(HANDLE ICDev,unsigned char *rlen, unsigned char *rbuff)
˵�������ϵ縴λ����,�������TYPE A ��
���ã�int ICDev ---- dc_init �������صĶ˿ڱ�ʶ��
unsigned char *rlen ---- ���ظ�λ��Ϣ�ĳ���
unsigned char * rbuff ---- ��ŷ��صĸ�λ��Ϣ
���أ� <0 ���������ֵΪ�����
=0 �ɹ���
������st=dc_pro_reset(ICDev,rlen,DataBuffer)*/
//����λ
int __stdcall ks_cpureset4sam(unsigned char *rlen, unsigned char *rbuff);

int __stdcall ks_setcpupara4sam(int SAMID);
/*
__int16 dc_pro_command(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff,unsigned char tt)
˵����Ӧ��Э�����ݵ�Ԫ��Ϣ�����������ú����ѷ�װT=CL����
���ã�int ICDev ----dc_init �������صĶ˿ڱ�ʶ��
unsigned char slen ---- ���͵���Ϣ����
unsigned char * sbuff ---- ���Ҫ���͵���Ϣ
unsigned char *rlen ---- ������Ϣ�ĳ���
unsigned char * rbuff ---- ��ŷ��ص���Ϣ
unsigned char tt---- �ӳ�ʱ�䣬��λΪ��10ms
*/
//CPU��ֱָͨ��
int __stdcall ks_cpuapdu( unsigned char *sSendData, unsigned char nSendDatalen, 
						 unsigned char* sRespData,unsigned char &nRespDatalen );

/*
__int16 dc_cpuapdu(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff)

˵����CPU��APDU��Ӧ��Э�����ݵ�Ԫ����Ϣ�����������ú�����װ��T=0��T=1���� 

���ã�int ICDev ----dc_init �������صĶ˿ڱ�ʶ��

unsigned char *slen ---- ���͵���Ϣ����

unsigned char * sbuff ---- ���Ҫ���͵���Ϣ

unsigned char *rlen ---- ������Ϣ�ĳ���

unsigned char * rbuff ---- ��ŷ��ص���Ϣ

���أ� <0 ���������ֵΪ�����

=0 �ɹ���
*/
int __stdcall ks_cpuapdu4hex(const char *szCmd,unsigned char nCmdlen,unsigned char* ucRespData,unsigned char &nRespDatalen );

//SAM��ֱָͨ��
int __stdcall ks_cpuapdu4sam( unsigned char *sSendData, unsigned char nSendDatalen, 
							 unsigned char* sRespData,unsigned char &nRespDatalen );

/*�������ܣ�
��һ��ͨϵͳ��Ա����16�ֽڵĸ���Կ��ϵͳ�Զ�����
������Կ��ɢ����1��������Կ��ɢ����2��
Ȧ����Կ��ɢ����1��
TAC��Կ��ɢ����1��TAC��Կ��ɢ����2��
PIN������ɢ���ӡ�
��װPIN��ɢ���ӡ�
ά����Կ��ɢ���ӡ�
Ӧ��������Կ��ɢ���ӹ�9����ɢ���ӡ�
����ԭ�ͣ�int ks_KeyCard_Publish( char* sMasterKey, char* sPin )
��ڲ�����
char* sMasterKey  -16�ֽڵĸ���������Կ ��0~9 a~f A~F�� 
char* sPin          -6�������ַ��ĸ�������
���ڲ�����
��
�������أ� 
0 --�ɹ�������ֵ-����(PBOC������)
*/
int __stdcall ks_publishkeycard(unsigned char* sMasterKey, char* sPin );
/*	�������ܣ�
����֤PINͨ���󣬲ſ��Ը�����Ӧ��Ż�ȡ��Ӧ��Ӧ����Կ����Ŷ�Ӧ��ϵ���£�
1--������Կ1
2--������Կ2
3--Ȧ����Կ
4--TAC��Կ1
5--TAC��Կ2
6--PIN������Կ
7--��װPIN��Կ
8--ά����Կ
9--������Կ
����ԭ�ͣ�int ks_Get_Key (int nKeySerial,char* sPin char* sKey)
��ڲ�����
int    nKeySerial  -��Կ���
char* sPin          -6�������ַ��ĸ�������
���ڲ�����
char* sKey  	  -16����Կ
�������أ� 
0 --�ɹ�������ֵ-����(PBOC������)
���Խ���Կ��ȡ��������ݿ��У���ü���Կ����)
*/
//������Կ��
int __stdcall ks_recyclekeycard();
//int __stdcall ks_getkey(int nKeySerial,char* sPin, char* sKey);
/*
�û�����
����ԭ�ͣ�int ks_Make_card_UserCard(ST_SPUBLISHUSERCARDINFO sCardInfo)
��ڲ�����
ST_SPUBLISHUSERCARDINFO sCardInfo		
���ڲ�����
��
�������أ� 
0 --�ɹ�������ֵ-����(PBOC������)
*/
int __stdcall ks_makeusercard(ST_PUBLISHUSERCARDINFO sCardInfo);
/*
�û���ϴ��
����ԭ�ͣ�int ks_init_card_UserCard(ST_SCARD_MAIN_KEY sStrKey,
char *sAppid,
char  *sShowCard,
int nWalletDetailCount)
��ڲ�����
char * sAppid	-��Ƭ�û����к� (20���ַ�)
char*sShowCard	-��ʾ����  (10���ַ�)
int nWalletDetailCount -Ǯ����ϸ���ֵ
���ڲ�����
��
��������:
0 --�ɹ�������ֵ-����(PBOC������)
*/
int __stdcall ks_initcard4user(ST_CARDMAINKEY StrKey,char *sAppid,char  *sShowCard,int nWalletDetailCount);
/*
1.4.1.2.	PSAM��ϴ��
����ԭ�ͣ�int ks_init_card_PSAMCard(char *sAppid,
char *  sTerminalNo)
��ڲ�����
char *  sAppid- PSAM���к�
char *  sTerminalNo -�ն˻����
���ڲ�����
��
�������أ� 
0 --�ɹ�������ֵ-����(PBOC������)
����������⣺3����Կ(���ѡ�ά�������أ�ͨ���ṹ��ST_SCARD_MAIN_KEY���룩
*/
int __stdcall ks_initcard4psam(ST_CARDMAINKEY StrKey,char *sAppid, char* sTerminalNo);

//��ֵ��ʼ��
int  __stdcall ks_addmoney(ST_TRANSPACK *deposit);
int __stdcall ks_cpuapdu4sam_hex(const char *sSendData, unsigned char nSendLen, 
								   unsigned char* sRespData,unsigned char &nRespLen );
//ͨ����̨����MAC
int __stdcall  ks_calctransmac(ST_TRANSPACK *transpack,char *sMac);
//����
int  __stdcall ks_purchase(ST_TRANSPACK *transpack);

int __stdcall ks_format_mfcard(const char *sCardPhyID,const char *sShowCardNo);
int __stdcall ks_external_auth(const char *phyno);
//////////////////////////////////////////////////////////////////////////
// mifare ����غ���
int ks_mf_login_card(int sectno);


/////////////////////////////////////////////////////////
extern ks_cardlib_license g_license;
#endif
