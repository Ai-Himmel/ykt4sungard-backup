#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sstream>
#include "yktclt.h"
#include "mystring.h"
#include "kscardtype.h"
#include "global_func.h"
#include "ks_cardtype.h"
#include "ksreader.h"
#include "des.h"
#include "ucs2code.h"
#pragma comment (lib, "bccclt.lib")
#pragma pack(1)

typedef struct {
	byte ucCardNo[10];		//���׿���
	byte ucShowCardNo[10];	//��ʾ����
	byte ucCardStatus;		//��״̬0 ����
	byte ucCardVerNo[7];	//���������汾��
	byte ucDeviceID[6];		//�豸ID
	byte ucFeeType;			//�շ����
	byte ucCardStructVer;	//���ṹ�汾
	byte ucStartDate[4];	//��������
	byte ucExpireDate[4];	//��������
	byte ucLockCardCnt[2];  //�󸶷��������״���
	byte ucLockTransDate[4]; //������������
	byte ucCardType;		//�����
	byte ucPublishDate[4];  //��������
	byte ucPublishID;	    //���з���ʶ
}BASEINFO;
typedef struct {
	byte ucName[32];		//����
	byte ucIDNo[32];		//֤������
	byte ucIDType;			//֤������
	byte ucSex;				//�Ա�
	byte ucStuempNo[20];	//ѧ����
	byte ucDeptCode[20];	//���Ŵ���
	byte ucCustType;		//�ͻ����
	byte ucCustID[4];		//�ͻ���
}PERSONINFO;
typedef struct {
	byte ucSingleMaxAmt[3];
	byte ucDayMaxAmt[3];
}TRANSPARA;
typedef struct {
	byte ucCardCnt[2];		//���������
	byte ucLimit[3];		//͸֧�޶�
	byte ucTransAmt[4];		//���׽��
	byte ucTransType;		//��������
	byte ucTermID[6];		//�ն˱��
	byte ucTransDate[4];	//��������
	byte ucTransTime[3];	//����ʱ��
}TRANSDTL;

typedef struct {
	byte ucTransDate[4];
	byte ucTransTime[3];
	byte ucTransType;
	byte ucTermNo[6]; // PSAM���ն˻����
	byte ucTermSeqNo[4]; // �ն˽������
	byte ucCardBefBal[4];
	byte ucTransAmount[3];
	byte ucManageFee[3];
	byte ucTransCnt[2];
	byte ucExtraAmount[4];
	byte ucTotalPerDay[3];
	byte shopId[2];
	byte reserve;
}FULLTRANSDTL;
#pragma pack()

char CCardType::szHexKSCCK[33]={"19081A14141A0819E6F7E5EBEBE5F7E6"};



//��ȡ��������Ϣ
char * CCardType::GetErrMsgByErrCode( int nErrCode,char *sErrInfo)
{
	switch( nErrCode)
	{
	case 0x9000:
	case 0x0000:
		sprintf(m_ErrMsg,"Err-%04X:�ɹ�",nErrCode);
		break;
	case 0x6200:
		sprintf(m_ErrMsg,"Err-%04X:�����豸�п�δ���뵽λ",nErrCode);
		break;
	case 0x6281:
		sprintf(m_ErrMsg,"Err-%04X:���͵����ݿ��ܴ���",nErrCode);
		break;
	case 0x6283:
		sprintf(m_ErrMsg,"Err-%04X:ѡ���ļ���Ч���ļ�����ԿУ�����",nErrCode);
		break;
	case 0x63C1:
		sprintf(m_ErrMsg,"Err-%04X:�����,����1�λ���",nErrCode);
		break;
	case 0x63C2:
		sprintf(m_ErrMsg,"Err-%04X:�����,����2�λ���",nErrCode);
		break;
	case 0x63C3:
		sprintf(m_ErrMsg,"Err-%04X:�����,����3�λ���",nErrCode);
		break;
	case 0x63C4:
		sprintf(m_ErrMsg,"Err-%04X:�����,����4�λ���",nErrCode);
		break;
	case 0x63C5:
		sprintf(m_ErrMsg,"Err-%04X:�����,����5�λ���",nErrCode);
		break;
	case 0x63C6:
		sprintf(m_ErrMsg,"Err-%04X:�����,����6�λ���",nErrCode);
		break;
	case 0x63C7:
		sprintf(m_ErrMsg,"Err-%04X:�����,����7�λ���",nErrCode);
		break;
	case 0x63C8:
		sprintf(m_ErrMsg,"Err-%04X:�����,����8�λ���",nErrCode);
		break;
	case 0x63C9:
		sprintf(m_ErrMsg,"Err-%04X:�����,����9�λ���",nErrCode);
		break;
	case 0x63CA:
		sprintf(m_ErrMsg,"Err-%04X:�����,����10�λ���",nErrCode);
		break;
	case 0x63CB:
		sprintf(m_ErrMsg,"Err-%04X:�����,����11�λ���",nErrCode);
		break;
	case 0x63CC:
		sprintf(m_ErrMsg,"Err-%04X:�����,����12�λ���",nErrCode);
		break;
	case 0x63CD:
		sprintf(m_ErrMsg,"Err-%04X:�����,����13�λ���",nErrCode);
		break;
	case 0x63CE:
		sprintf(m_ErrMsg,"Err-%04X:�����,����14�λ���",nErrCode);
		break;
	case 0x6400:
		sprintf(m_ErrMsg,"Err-%04X:״̬��־δ�ı�",nErrCode);
		break;
	case 0x6581:
		sprintf(m_ErrMsg,"Err-%04X:дEEPROM���ɹ�",nErrCode);
		break;
	case 0x6700:
		sprintf(m_ErrMsg,"Err-%04X:ָ�������Ȳ���ȷ",nErrCode);
		break;
	case 0x6900:
		sprintf(m_ErrMsg,"Err-%04X:CLA����·����Ҫ��ƥ��",nErrCode);
		break;
	case 0x6901:
		sprintf(m_ErrMsg,"Err-%04X:��Ч��״̬",nErrCode);
		break;
	case 0x6981:
		sprintf(m_ErrMsg,"Err-%04X:�������ļ��ṹ������",nErrCode);
		break;
	case 0x6982:
		sprintf(m_ErrMsg,"Err-%04X:������д���޸Ŀ�Ƭ�İ�ȫ״̬",nErrCode);
		break;
	case 0x6983:
		sprintf(m_ErrMsg,"Err-%04X:��Կ�Ѿ�������",nErrCode);
		break;
	case 0x6984:
		sprintf(m_ErrMsg,"Err-%04X:�������Ч,����ȡ�����",nErrCode);
		break;
	case 0x6985:
		sprintf(m_ErrMsg,"Err-%04X:ʹ������������",nErrCode);
		break;
	case 0x6986:
		sprintf(m_ErrMsg,"Err-%04X:����������ִ������,��ǰ�ļ�����EF",nErrCode);
		break;
	case 0x6987:
		sprintf(m_ErrMsg,"Err-%04X:�ް�ȫ���Ļ�MAC��ʧ",nErrCode);
		break;
	case 0x6988:
		sprintf(m_ErrMsg,"Err-%04X:��ȫ��������MAC����ȷ",nErrCode);
		break;
	case 0x6A80:
		sprintf(m_ErrMsg,"Err-%04X:�������������",nErrCode);
		break;
	case 0x6A81:
		sprintf(m_ErrMsg,"Err-%04X:���ܲ�֧�ֻ�����MF��Ƭ�Ѿ�����",nErrCode);
		break;
	case 0x6A82:
		sprintf(m_ErrMsg,"Err-%04X:��Ƭ���ļ�δ�ҵ�",nErrCode);
		break;
	case 0x6A83:
		sprintf(m_ErrMsg,"Err-%04X:��Ƭ�м�¼δ�ҵ�",nErrCode);
		break;
	case 0x6A84:
		sprintf(m_ErrMsg,"Err-%04X:�ļ����㹻�ռ�",nErrCode);
		break;
	case 0x6A86:
		sprintf(m_ErrMsg,"Err-%04X:����P1P2����",nErrCode);
		break;
	case 0x6A87:
		sprintf(m_ErrMsg,"Err-%04X:�ް�ȫ����",nErrCode);
		break;
	case 0x6A88:
		sprintf(m_ErrMsg,"Err-%04X:��Կδ�ҵ�",nErrCode);
		break;
	case 0x6B00:
		sprintf(m_ErrMsg,"Err-%04X:�ڴﵽLe/Lc�ֽ�֮ǰ�ļ�����,ƫ��������",nErrCode);
		break;
	case 0x6D00:
		sprintf(m_ErrMsg,"Err-%04X:��Ч��INS",nErrCode);
		break;
	case 0x6E00:
		sprintf(m_ErrMsg,"Err-%04X:��Ч��CLA",nErrCode);
		break;
	case 0x6F00:
		sprintf(m_ErrMsg,"Err-%04X:������Ч",nErrCode);
		break;
	case 0x6FF0:
		sprintf(m_ErrMsg,"Err-%04X:������ϵͳ����",nErrCode);
		break;
	case 0xFFFF:
		sprintf(m_ErrMsg,"Err-%04X:�޷��жϵĴ���",nErrCode);
		break;
	case 0x9210:
		sprintf(m_ErrMsg,"Err-%04X:��Ƭ��DF���ڴ治��",nErrCode);
		break;
	case 0x9220:
		sprintf(m_ErrMsg,"Err-%04X:�ļ�ID�Ѵ���",nErrCode);
		break;
	case 0x9240:
		sprintf(m_ErrMsg,"Err-%04X:��Ƭ�ڴ�����",nErrCode);
		break;
	case 0x9302:
		sprintf(m_ErrMsg,"Err-%04X:MAC����",nErrCode);
		break;
	case 0x9303:
		sprintf(m_ErrMsg,"Err-%04X:Ӧ���ѱ�����",nErrCode);
		break;
	case 0x9400:
		sprintf(m_ErrMsg,"Err-%04X:û��ѡ��ǰ��EF�ļ�ID",nErrCode);
		break;
	case 0x9401:
		sprintf(m_ErrMsg,"Err-%04X:����",nErrCode);
		break;
	case 0x9402:
		sprintf(m_ErrMsg,"Err-%04X:������Χ��û�иü�¼",nErrCode);
		break;
	case 0x9403:
		sprintf(m_ErrMsg,"Err-%04X:��Կδ�ҵ�",nErrCode);
		break;
	case 0x9404:
		sprintf(m_ErrMsg,"Err-%04X:EF���ļ�IDû���ҵ�",nErrCode);
		break;
	case 0x9406:
		sprintf(m_ErrMsg,"Err-%04X:�����MAC������",nErrCode);
		break;
	case 0x9802:
		sprintf(m_ErrMsg,"Err-%04X:û����Ҫ����Կ",nErrCode);
		break;
	case 0x9804:
		sprintf(m_ErrMsg,"Err-%04X:��������û�������MAC��",nErrCode);
		break;
	case 0x9810:
		sprintf(m_ErrMsg,"Err-%04X:��Ӧ�ñ�����",nErrCode);
		break;
	case 0x9835:
		sprintf(m_ErrMsg,"Err-%04X:û��ȡ�����",nErrCode);
		break;
	case 0x9840:
		sprintf(m_ErrMsg,"Err-%04X:��KEY����ס",nErrCode);
		break;
	default:
		sprintf(m_ErrMsg,"Err-%04X:��֪���Ĵ���",nErrCode);
		break;
	}
	if(sErrInfo)
		strcpy(sErrInfo,m_ErrMsg);
	return m_ErrMsg;
}
unsigned char* CCardType::PbocDiverKey( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] )
{
	int i;
	unsigned char tmp1[20], tmp2[20];
	unsigned char ret1[20], ret2[20];

	memset(tmp1, 0x00, sizeof tmp1 );
	memset(tmp2, 0x00, sizeof tmp2 );
	memset(ret1, 0x00, sizeof ret1 );
	memset(ret2, 0x00, sizeof ret2 );

	memcpy ( tmp1, cardno, 8 );
	for( i=0; i<8; i++)
	{
		tmp2[i]=~tmp1[i];
	}
	des3_context ctx3;
	des3_set_2keys(&ctx3,key_in,key_in+8);
	des3_encrypt(&ctx3, tmp1, ret1);
	des3_encrypt(&ctx3, tmp2, ret2);
	memcpy( key_out,ret1, 8 );
	memcpy( key_out+8,ret2, 8 );
	return key_out;
}
void CCardType::GetSupportCardType(unsigned int cardTypes[],int &cnt)
{
	int i = 0;
	cardTypes[i++] = 0x0100;
	cardTypes[i++] = 0x0300;
	cardTypes[i++] = 0x0400;
	cnt = i;
}
int CCardType::testCardExists(char *szCardPhyID)
{
	int nRet;
	unsigned char uRandom[8] = {0};
	nRet = this->GetRandomNum(uRandom);
	if(nRet)
		return -1;
	strcpy(szCardPhyID,this->m_szCardUID);
	return 0;
}
int CCardType::EncryptKey(const unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen)
{
	int i=0;
	byte ucKey[17]={0};
	des_context ctx;
	des3_context ctx3;
	// ��ʽ������ֵ: �� "80 00 00 ...", ��8�ֽڳ��� ==> buf
	int nBlock=0;
	if(iDataLen%8)
		nBlock = iDataLen/8 + 1; // �ܿ���
	else
		nBlock = iDataLen/8;
	byte* buf = new byte[nBlock*8+10];
	memset(buf, 0, nBlock*8*sizeof(byte));
	memcpy(buf, uData, iDataLen*sizeof(byte));
	buf[iDataLen] = 0x80;
	memcpy(ucKey,uKey,nKeyLen*8);
	if(nKeyLen==2)
	{
		des3_set_2keys(&ctx3,ucKey,ucKey+8);
	}
	else
	{
		des_set_key(&ctx,ucKey);
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
//����MAC����
int CCardType::CalcSessionKey(unsigned char *ucRandom,unsigned char *ucKey,unsigned char *ucSessionKey)
{
	int i=0;
	des_context ctx;
	byte ucX[8]={0},ucY[8]={0};
	memcpy(ucX,ucRandom,8);
	//for(i=0;i<8; i++)
	//{
	//	ucY[i] = ~ucX[i];
	//}
	des_set_key(&ctx,ucKey);
	des_encrypt(&ctx,ucX,ucX);
	des_set_key(&ctx,ucKey+8);
	des_decrypt(&ctx,ucX,ucX);
	des_set_key(&ctx,ucKey);
	des_encrypt(&ctx,ucX,ucX);

	//des_set_key(&ctx,ucKey);
	//des_encrypt(&ctx,ucY,ucY);
	//des_set_key(&ctx,ucKey+8);
	//des_decrypt(&ctx,ucY,ucY);
	//des_set_key(&ctx,ucKey);
	//des_encrypt(&ctx,ucY,ucY);

	memcpy(ucSessionKey,ucX,8);
//	memcpy(ucSessionKey+8,ucY,8);
	return 0;
}
//����MAC����
int CCardType::CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac)
{
	int i=0;
	des_context ctx;
	BYTE uTemp[16];
	// ��ʼ��MAC�����ֵ ==> temp
	memset(uTemp, 0, sizeof(uTemp));
	memcpy(uTemp, uRandom, 8 * sizeof(BYTE));
	// ��ʽ������ֵ: �� "80 00 00 ...", ��8�ֽڳ��� ==> buf
	int nBlock=0;
	if(iMacDataLen%8)
		nBlock = iMacDataLen/8 + 1; // �ܿ���
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
	// temp ����λ ==> MAC
	memcpy(uMac, uTemp, 4 * sizeof(byte));
	return 0;
}
CCardType::CCardType():ks_cardtype_base("ks_cardtype.dll")
	,m_ReadFileLen(64),m_WriteFileLen(32),m_keycardType(KS_CPUCARD),m_CardBal(0),m_PayCnt(0),m_DpsCnt(0)
{
	m_defaultCardType = KS_CPUCARD;

	memset(m_TempBuff,0,sizeof(m_TempBuff));
	m_sDefaultPin="000000";
	memset(&m_CardKeys,0,sizeof(m_CardKeys));
	memset(&m_CloneKeys,0,sizeof(m_CloneKeys));
	EF_FIELD EField;
	memset(&EField,0,sizeof(EField));
	EField.unused=1;
	//�ȳ�ʼ��Ϊ0
	for(int i=0;i<=CF_END;i++)
		m_FieldVect.push_back(EField);
	assert(sizeof(BASEINFO)==56);
	assert(sizeof(PERSONINFO)==111);
	assert(sizeof(TRANSPARA)==6);
	assert(sizeof(FULLTRANSDTL)==40);
	assert(sizeof(TRANSDTL)==23);

	BASEINFO	PublicApp;
	PERSONINFO	UserInfo;
	TRANSPARA	PrivateApp;
	//FULLTRANSDTL TransDtl;
	TRANSDTL TransDtl;
	//���з���ʶ
	m_FieldVect[CF_PUBLISHID].unused=0;
	m_FieldVect[CF_PUBLISHID].offset = &(PublicApp.ucPublishID)-(byte*)&PublicApp;
	m_FieldVect[CF_PUBLISHID].length = sizeof(PublicApp.ucPublishID);
	m_FieldVect[CF_PUBLISHID].fid=0x15;
	m_FieldVect[CF_PUBLISHID].type=FT_INT16;

	//��ʾ����
	m_FieldVect[CF_SHOWCARDNO].unused=0;
	m_FieldVect[CF_SHOWCARDNO].offset = PublicApp.ucShowCardNo-(byte*)&PublicApp;
	m_FieldVect[CF_SHOWCARDNO].length = sizeof(PublicApp.ucShowCardNo);
	m_FieldVect[CF_SHOWCARDNO].fid=0x15;
	m_FieldVect[CF_SHOWCARDNO].type=FT_ANSI;
	//Ӧ������
	//m_FieldVect[CF_APPTYPE].unused=1;
	//m_FieldVect[CF_APPTYPE].offset = &ReadPublicApp.ucAppType-(byte*)&ReadPublicApp;
	//m_FieldVect[CF_APPTYPE].length = sizeof(ReadPublicApp.ucAppType);
	//m_FieldVect[CF_APPTYPE].fid=0x15;
	//m_FieldVect[CF_APPTYPE].type=FT_INT8;
	//����
	m_FieldVect[CF_CARDNO].unused=0;
	m_FieldVect[CF_CARDNO].offset = PublicApp.ucCardNo-(byte*)&PublicApp;
	m_FieldVect[CF_CARDNO].length = sizeof(PublicApp.ucCardNo);
	m_FieldVect[CF_CARDNO].fid=0x15;
	m_FieldVect[CF_CARDNO].type=FT_BCD_LAPDZERO;

	//��״̬
	m_FieldVect[CF_CARDSTATUS].unused=0;
	m_FieldVect[CF_CARDSTATUS].offset = &PublicApp.ucCardStatus - (byte*)&PublicApp;
	m_FieldVect[CF_CARDSTATUS].length = sizeof(PublicApp.ucCardStatus);
	m_FieldVect[CF_CARDSTATUS].fid=0x15;
	m_FieldVect[CF_CARDSTATUS].type=FT_INT8;
	//���汾��
	m_FieldVect[CF_CARDVERNO].unused=0;
	m_FieldVect[CF_CARDVERNO].offset = PublicApp.ucCardVerNo - (byte*)&PublicApp;
	m_FieldVect[CF_CARDVERNO].length = sizeof(PublicApp.ucCardVerNo);
	m_FieldVect[CF_CARDVERNO].fid=0x15;
	m_FieldVect[CF_CARDVERNO].type=FT_BCD_LPAD20;
	//�������κ�
	/*
	m_FieldVect[CF_SUBSIDYNO].unused=0;
	m_FieldVect[CF_SUBSIDYNO].offset = &(PublicApp.ucSubsidyno) - (byte*)&PublicApp;
	m_FieldVect[CF_SUBSIDYNO].length = sizeof(PublicApp.ucSubsidyno);
	m_FieldVect[CF_SUBSIDYNO].fid=0x15;
	m_FieldVect[CF_SUBSIDYNO].type=FT_INT8;
	*/

	//��������
	m_FieldVect[CF_STARTDATE].unused=0;
	m_FieldVect[CF_STARTDATE].offset = PublicApp.ucStartDate-(byte*)&PublicApp;
	m_FieldVect[CF_STARTDATE].length = sizeof(PublicApp.ucStartDate);
	m_FieldVect[CF_STARTDATE].fid=0x15;
	m_FieldVect[CF_STARTDATE].type=FT_BCD;
	//��Ч��
	m_FieldVect[CF_EXPIREDATE].unused=0;
	m_FieldVect[CF_EXPIREDATE].offset = PublicApp.ucExpireDate-(byte*)&PublicApp;
	m_FieldVect[CF_EXPIREDATE].length = sizeof(PublicApp.ucExpireDate);
	m_FieldVect[CF_EXPIREDATE].fid=0x15;
	m_FieldVect[CF_EXPIREDATE].type=FT_BCD;
	//���ṹ�汾
	m_FieldVect[CF_CARDSTRUCTVER].unused=0;
	m_FieldVect[CF_CARDSTRUCTVER].offset = &PublicApp.ucCardStructVer-(byte*)&PublicApp;
	m_FieldVect[CF_CARDSTRUCTVER].length = sizeof(PublicApp.ucCardStructVer);
	m_FieldVect[CF_CARDSTRUCTVER].fid=0x15;
	m_FieldVect[CF_CARDSTRUCTVER].type=FT_INT8;
	//�շ����
	m_FieldVect[CF_FEETYPE].unused=0;
	m_FieldVect[CF_FEETYPE].offset = &PublicApp.ucFeeType - (byte*)&PublicApp;
	m_FieldVect[CF_FEETYPE].length = sizeof(PublicApp.ucFeeType);
	m_FieldVect[CF_FEETYPE].fid=0x15;
	m_FieldVect[CF_FEETYPE].type=FT_INT8;
	//������
	m_FieldVect[CF_CARDTYPE].unused=0;
	m_FieldVect[CF_CARDTYPE].offset = &PublicApp.ucCardType - (byte*)&PublicApp;
	m_FieldVect[CF_CARDTYPE].length = sizeof(PublicApp.ucCardType);
	m_FieldVect[CF_CARDTYPE].fid=0x15;
	m_FieldVect[CF_CARDTYPE].type=FT_INT8;

	//��������ʱ���״���
	m_FieldVect[CF_LOCKCARDCNT].unused=0;
	m_FieldVect[CF_LOCKCARDCNT].offset = PublicApp.ucLockCardCnt - (byte*)&PublicApp;
	m_FieldVect[CF_LOCKCARDCNT].length = sizeof(PublicApp.ucLockCardCnt);
	m_FieldVect[CF_LOCKCARDCNT].fid=0x15;
	m_FieldVect[CF_LOCKCARDCNT].type=FT_INT16;

	//��������ʱ�����ն˺�
	m_FieldVect[CF_LOCKTERMID].unused=0;
	m_FieldVect[CF_LOCKTERMID].offset = PublicApp.ucDeviceID - (byte*)&PublicApp;
	m_FieldVect[CF_LOCKTERMID].length = sizeof(PublicApp.ucDeviceID);
	m_FieldVect[CF_LOCKTERMID].fid=0x15;
	m_FieldVect[CF_LOCKTERMID].type=FT_BCD;

	//��������ʱ��������
	m_FieldVect[CF_LOCKTRANSDATE].unused=0;
	m_FieldVect[CF_LOCKTRANSDATE].offset = PublicApp.ucLockTransDate - (byte*)&PublicApp;
	m_FieldVect[CF_LOCKTRANSDATE].length = sizeof(PublicApp.ucLockTransDate);
	m_FieldVect[CF_LOCKTRANSDATE].fid=0x15;
	m_FieldVect[CF_LOCKTRANSDATE].type=FT_BCD;

	//��������ʱ����ʱ��
	m_FieldVect[CF_LOCKTRANSTIME].unused=1;


	///////////////////////////////////////////////////////////////////

	//����
	m_FieldVect[CF_NAME].unused=0;
	m_FieldVect[CF_NAME].offset = UserInfo.ucName - (byte*)&UserInfo;
	m_FieldVect[CF_NAME].length = sizeof(UserInfo.ucName);
	m_FieldVect[CF_NAME].fid=0x16;
	m_FieldVect[CF_NAME].type=FT_ANSI;
	//���֤��
	m_FieldVect[CF_IDNO].unused=0;
	m_FieldVect[CF_IDNO].offset = UserInfo.ucIDNo - (byte*)&UserInfo;
	m_FieldVect[CF_IDNO].length = sizeof(UserInfo.ucIDNo);
	m_FieldVect[CF_IDNO].fid=0x16;
	m_FieldVect[CF_IDNO].type=FT_ANSI;
	//֤������
	m_FieldVect[CF_IDTYPE].unused=0;
	m_FieldVect[CF_IDTYPE].offset = &UserInfo.ucIDType - (byte*)&UserInfo;
	m_FieldVect[CF_IDTYPE].length = sizeof(UserInfo.ucIDType);
	m_FieldVect[CF_IDTYPE].fid=0x16;
	m_FieldVect[CF_IDTYPE].type=FT_INT8;

	//�����ۼ�����޶�
	m_FieldVect[CF_SINGLEMAXAMT].unused=0;
	m_FieldVect[CF_SINGLEMAXAMT].offset = PrivateApp.ucSingleMaxAmt - (byte*)&PrivateApp;
	m_FieldVect[CF_SINGLEMAXAMT].length = sizeof(PrivateApp.ucSingleMaxAmt);
	m_FieldVect[CF_SINGLEMAXAMT].fid=0x12;
	m_FieldVect[CF_SINGLEMAXAMT].type=FT_INT24;
	//���ۼ�����޶�
	m_FieldVect[CF_DAYMAXAMT].unused=0;
	m_FieldVect[CF_DAYMAXAMT].offset = PrivateApp.ucDayMaxAmt - (byte*)&PrivateApp;
	m_FieldVect[CF_DAYMAXAMT].length = sizeof(PrivateApp.ucDayMaxAmt);
	m_FieldVect[CF_DAYMAXAMT].fid=0x12;
	m_FieldVect[CF_DAYMAXAMT].type=FT_INT24;

	//������
	m_FieldVect[CF_CARDPWD].unused=0;
	m_FieldVect[CF_CARDPWD].offset = 0;
	m_FieldVect[CF_CARDPWD].length = 6;
	m_FieldVect[CF_CARDPWD].fid=0x19;
	m_FieldVect[CF_CARDPWD].type=FT_ANSI;

	//�ͻ����
	m_FieldVect[CF_CUSTTYPE].unused=0;
	m_FieldVect[CF_CUSTTYPE].offset = &UserInfo.ucCustType - (byte*)&UserInfo;
	m_FieldVect[CF_CUSTTYPE].length = sizeof(UserInfo.ucCustType);
	m_FieldVect[CF_CUSTTYPE].fid=0x16;
	m_FieldVect[CF_CUSTTYPE].type=FT_INT8;
	//�ͻ���
	m_FieldVect[CF_CUSTID].unused=0;
	m_FieldVect[CF_CUSTID].offset = UserInfo.ucCustID - (byte*)&UserInfo;
	m_FieldVect[CF_CUSTID].length = sizeof(UserInfo.ucCustID);
	m_FieldVect[CF_CUSTID].fid=0x16;
	m_FieldVect[CF_CUSTID].type=FT_INT32;
	//ѧ����
	m_FieldVect[CF_STUEMPNO].unused=0;
	m_FieldVect[CF_STUEMPNO].offset = UserInfo.ucStuempNo - (byte*)&UserInfo;
	m_FieldVect[CF_STUEMPNO].length = sizeof(UserInfo.ucStuempNo);
	m_FieldVect[CF_STUEMPNO].fid=0x16;
	m_FieldVect[CF_STUEMPNO].type=FT_ANSI;
	//У��
	//m_FieldVect[CF_SCHOOLCODE].unused=0;
	//m_FieldVect[CF_SCHOOLCODE].offset = &UserInfo.ucSchoolCode - (byte*)&PrivateApp;
	//m_FieldVect[CF_SCHOOLCODE].length = sizeof(PrivateApp.ucSchoolCode);
	//m_FieldVect[CF_SCHOOLCODE].fid=0x1B;
	//m_FieldVect[CF_SCHOOLCODE].type=FT_INT8;
	//���Ŵ���
	m_FieldVect[CF_DEPTCODE].unused=0;
	m_FieldVect[CF_DEPTCODE].offset = UserInfo.ucDeptCode - (byte*)&UserInfo;
	m_FieldVect[CF_DEPTCODE].length = sizeof(UserInfo.ucDeptCode);
	m_FieldVect[CF_DEPTCODE].fid=0x16;
	m_FieldVect[CF_DEPTCODE].type=FT_ANSI;
	//�Ա�
	m_FieldVect[CF_SEX].unused=0;
	m_FieldVect[CF_SEX].offset = &UserInfo.ucSex - (byte*)&UserInfo;
	m_FieldVect[CF_SEX].length = sizeof(UserInfo.ucSex);
	m_FieldVect[CF_SEX].fid=0x16;
	m_FieldVect[CF_SEX].type=FT_INT8;

	//Ǯ���ļ�
	//Ǯ���ٶ��ļ�SFID=0x99;
	//�����
	m_FieldVect[CF_CARDBAL].unused=0;
	m_FieldVect[CF_CARDBAL].offset =0;
	m_FieldVect[CF_CARDBAL].length =0;
	m_FieldVect[CF_CARDBAL].fid=MONEY_SFID;
	m_FieldVect[CF_CARDBAL].type=FT_INT32;
	m_FieldVect[CF_CARDBAL].rw=RW_R;
	//���Ѵ���
	m_FieldVect[CF_PAYCNT].unused=0;
	m_FieldVect[CF_PAYCNT].offset =0;
	m_FieldVect[CF_PAYCNT].length =0;
	m_FieldVect[CF_PAYCNT].fid=MONEY_SFID;
	m_FieldVect[CF_PAYCNT].type=FT_INT32;
	m_FieldVect[CF_PAYCNT].rw=RW_R;
	//��ֵ����
	m_FieldVect[CF_DPSCNT].unused=0;
	m_FieldVect[CF_DPSCNT].offset =0;
	m_FieldVect[CF_DPSCNT].length =0;
	m_FieldVect[CF_DPSCNT].fid=MONEY_SFID;
	m_FieldVect[CF_DPSCNT].type=FT_INT32;
	m_FieldVect[CF_DPSCNT].rw=RW_R;

	///////////////////////////////
	// ������ϸ�ļ� SFID = 0x18
	//���׽��(���һ�ν���)
	m_FieldVect[CF_TRANSAMT].unused=0;
	m_FieldVect[CF_TRANSAMT].offset = TransDtl.ucTransAmt - (byte*)&TransDtl;
	m_FieldVect[CF_TRANSAMT].length = sizeof(TransDtl.ucTransAmt);
	m_FieldVect[CF_TRANSAMT].fid=0x18;
	m_FieldVect[CF_TRANSAMT].type=FT_INT32;

	//���״���(���һ�ν���)
	m_FieldVect[CF_CARDCNT].unused=0;
	m_FieldVect[CF_CARDCNT].offset = TransDtl.ucCardCnt - (byte*)&TransDtl;
	m_FieldVect[CF_CARDCNT].length = sizeof(TransDtl.ucCardCnt);
	m_FieldVect[CF_CARDCNT].fid=0x18;
	m_FieldVect[CF_CARDCNT].type=FT_INT16;

	//�����ն˻����(���һ�ν���)
	m_FieldVect[CF_TERMID].unused=0;
	m_FieldVect[CF_TERMID].offset = TransDtl.ucTermID - (byte*)&TransDtl;
	m_FieldVect[CF_TERMID].length = sizeof(TransDtl.ucTermID);
	m_FieldVect[CF_TERMID].fid=0x18;
	m_FieldVect[CF_TERMID].type=FT_BCD;

	//��������(���һ�ν���)
	m_FieldVect[CF_TRANSTYPE].unused=0;
	m_FieldVect[CF_TRANSTYPE].offset = &(TransDtl.ucTransType) - (byte*)&TransDtl;
	m_FieldVect[CF_TRANSTYPE].length = sizeof(TransDtl.ucTransType);
	m_FieldVect[CF_TRANSTYPE].fid=0x18;
	m_FieldVect[CF_TRANSTYPE].type=FT_INT8;

	//��������(���һ�ν���)
	m_FieldVect[CF_TRANSDATE].unused=0;
	m_FieldVect[CF_TRANSDATE].offset = TransDtl.ucTransDate - (byte*)&TransDtl;
	m_FieldVect[CF_TRANSDATE].length = sizeof(TransDtl.ucTransDate);
	m_FieldVect[CF_TRANSDATE].fid=0x18;
	m_FieldVect[CF_TRANSDATE].type=FT_BCD;

	//����ʱ��(���һ�ν���)
	m_FieldVect[CF_TRANSTIME].unused=0;
	m_FieldVect[CF_TRANSTIME].offset = TransDtl.ucTransTime - (byte*)&TransDtl;
	m_FieldVect[CF_TRANSTIME].length = sizeof(TransDtl.ucTransTime);
	m_FieldVect[CF_TRANSTIME].fid=0x18;
	m_FieldVect[CF_TRANSTIME].type=FT_BCD;


	EFBUF efbuf;

	memset(efbuf.ReadBuf,0,sizeof(efbuf.ReadBuf));
	memset(efbuf.WriteBuf,0,sizeof(efbuf.WriteBuf));

	efbuf.FileSize=sizeof(BASEINFO);
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x15]=efbuf;

	efbuf.FileSize=sizeof(PERSONINFO);
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x16]=efbuf;

	efbuf.FileSize=6;
	efbuf.ReadRight=FRR_EXTAUTH_MAC;
	efbuf.WriteRight=FRW_MAC_DIRECT;
	m_EFMap[0x19]=efbuf;

	efbuf.FileSize=sizeof(TRANSPARA);
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x12]=efbuf;

	efbuf.FileSize=sizeof(TRANSDTL);
	efbuf.ReadRight=FRR_REC_FREE;
	efbuf.WriteRight=FRW_NULL;
	m_EFMap[0x18]=efbuf;

	//Ǯ��
	efbuf.FileSize=0;
	efbuf.ReadRight=FRR_NULL;
	efbuf.WriteRight=FRW_NULL;
	m_EFMap[MONEY_SFID]=efbuf;

}
#define LOG writelog(logger,)


int CCardType::doSuccessRequestCard()
{
	int nRet=0;
	unsigned char ats[128],rlen;
	if(this->m_defaultCardType == KS_CPUCARD || this->m_defaultCardType == KS_FIXCARD)
	{
		nRet = m_Reader->cpucard_poweron(m_ReaderPara,m_defaultCardType,&rlen,ats);
		if(nRet)
		{
			SET_ERR("���ϵ縴λ����");
			return nRet;
		}
	}
	return 0;
}

int CCardType::SelectADF()
{
	return this->selectADFBySFI("DF03");
}
int CCardType::ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucRes)
{
	int		nRet=0;
	char	szCmd[256]={0};
	byte	nResLen=0;
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	sprintf(szCmd,"00B0%02X%02X%02X",0x80+ucSFI,ucOffset,ucLength);
	cmd.send_buf=(byte*)szCmd;
	cmd.recv_buf=ucRes;
	cmd.send_len=strlen(szCmd);
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			GetErrMsgByErrCode(cmd.cmd_retcode,cmd.cmd_retmsg);
			SET_ERR("ReadBinaryFile SFID="<<ltohex(ucSFI)<<cmd.cmd_retmsg);
			return nRet;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	return 0;
}
int CCardType::ReadBinaryFile4Mac(byte ucSFI,byte ucOffset,byte ucLength,byte *ucRes)
{
	int nRet=0;
	char	szCmd[64]={0};
	char szMac[9]={0};
	byte	nResLen=0;
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	sprintf(szCmd,"04B0%02X%02X04",0x80+ucSFI,ucOffset);
	nRet=CalcSafeMac4Sam(szCmd,szMac);
	if(nRet)
	{
		return nRet;
	}
	strcat(szCmd,szMac);
	//cmd.send_len=strlen(szCmd);

	//sprintf(szCmd+cmd.send_len,"%02X",ucLength);

	cmd.send_buf=(byte*)szCmd;
	cmd.recv_buf=ucRes;
	cmd.send_len=strlen(szCmd);
	cmd.cmd_type=1;//16����

	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR("ReadBinaryFile4Mac SFID="<<ltohex(ucSFI)<<" nRet="<<ltohex(cmd.cmd_retcode));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	return 0;
}
int CCardType::VerifyPin(const char* sPin)
{
	string  sCmd;
	byte	ucRes[256]={0};
	char  szPin[13]={0};
	if(NULL==sPin)
	{
		strcpy(szPin,m_sDefaultPin.c_str());
	}
	else
	{
		strcpy(szPin,sPin);
	}
	int len=strlen(szPin);
	if(len%2)
	{
		SET_ERR("PIN�ĳ��ȱ�����2�ı���");
		return -1;
	}
	len/=2;
	if(len<2||len>6)
	{
		SET_ERR("PIN���ȴ���");
		return -1;
	}
	sCmd="00200000";
	sCmd+=ltohex(len);
	sCmd+=szPin;
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));

	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.recv_buf=ucRes;
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	int nRet=0;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	return 0;
}
int CCardType::VerifyCardPasswd(const char *cardphyid,const char* sCardPasswd,int& iIsPass)
{
	int nRet=0;
	string  sCmd;
	char	szPasswd[9]={0};
	byte	ucRes[256]={0};
	int len=strlen(sCardPasswd);
	if(len>8)
	{
		SET_ERR("���볤�ȴ���");
		return -1;
	}
	strcpy(szPasswd,sCardPasswd);
	nRet=ExtAuth(cardphyid,1);
	if(nRet)
	{
		return nRet;
	}
	nRet=ReadBinaryFile4Mac(0x19,0,8,ucRes);
	if(nRet)
		return nRet;
	if(memcmp(szPasswd,ucRes,8)==0)
		iIsPass=1;
	else
		iIsPass=0;
	return 0;
}
int CCardType::ExecExtAuthCmd(const unsigned char ucExtAuthKey[16],int nKeyIndex)
{
	int nRet=0;
	unsigned char ucCCK[17]={0};
	memcpy(ucCCK,ucExtAuthKey,16);

	unsigned char ucSendData[256]={0};
	unsigned char ucRespData[256]={0};
	unsigned char ucBuff[64]={0};
	unsigned char ucRandom[9]={0};

	nRet=GetRandomNum(ucRandom);
	if(nRet)
		return nRet;

	des3_context ctx3;
	des3_set_2keys( &ctx3, ucCCK,ucCCK+8);
	des3_encrypt(&ctx3,ucRandom,ucBuff);
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;

	memcpy(ucSendData,"\x00\x82\x00\x00\x08",5);
	ucSendData[3]=nKeyIndex;
	memcpy(ucSendData+5,ucBuff,8);
	cmd.send_buf=ucSendData;
	cmd.recv_buf=ucRespData;
	cmd.send_len=0x0D;
	cmd.cmd_type=0;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			GetErrMsgByErrCode(cmd.cmd_retcode,cmd.cmd_retmsg);
			SET_ERR(cmd.cmd_retmsg);
			return nRet;
		}
		else
		{
			m_Reader->GetErrMsg(cmd.cmd_retmsg);
			SET_ERR(cmd.cmd_retmsg);
			return nRet;
		}
	}
	return 0;
}
int CCardType::ExtAuth(const char *cardphyid,int keyidx)
{
	string sCmd;
	unsigned char ucRespData[512]={0};
	unsigned char ucRandom[9]={0};
	char sRandomHex[17]={0};
	char encrypt_random[24] = {0};
	int nRet;

	nRet=SelectADF();
	if(nRet)
		return nRet;
	nRet=GetRandomNum(ucRandom);
	if(nRet)
		return nRet;

	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;

	dec2hex(ucRandom,8,sRandomHex);
	nRet = CalcExtAuthEncrypt4Sam(cardphyid,keyidx,sRandomHex,encrypt_random);
	if(nRet)
	{
		return nRet;
	}
	sCmd = "008200"+ltohex(keyidx)+"08";
	sCmd += encrypt_random;

	cmd.cmd_type=1;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	return 0;
}
int CCardType::GetDpsCnt()
{
	int nRet=0;
	string sCmd;
	byte	ucRespData[256]={0};

	nRet=SelectADF();
	if(nRet)
	{
		return nRet;
	}
	nRet=VerifyPin(m_sDefaultPin.c_str());
	if(nRet)
	{
		return nRet;
	}
	sCmd="805000020B0100002710112233445566";
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));

	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.recv_buf=ucRespData;
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//�����
	m_CardBal=get_4byte_int(ucRespData);
	//���Ѵ���
	m_DpsCnt=get_2byte_int(ucRespData+4);
	return 0;
}
int CCardType::GetPayCnt()
{
	int nRet=0;
	string sCmd;
	byte ucRespData[256]={0};

	nRet=SelectADF();
	if(nRet)
	{
		return nRet;
	}
	sCmd="805001020B0100000000112233445566";
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));

	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.recv_buf=ucRespData;
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//�����
	m_CardBal=get_4byte_int(ucRespData);
	//���Ѵ���
	m_PayCnt=get_2byte_int(ucRespData+4);
	return 0;
}
int CCardType::GetBalance()
{
	int nRet=0;
	char szCmd[512];
	byte ucRes[256];

	nRet=SelectADF();
	if(nRet)
	{
		return nRet;
	}
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	sprintf(szCmd,"805C000204");
	cmd.send_buf=(byte*)szCmd;
	cmd.recv_buf=ucRes;
	cmd.send_len=strlen(szCmd);
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	m_CardBal=get_4byte_int(ucRes);
	return 0;
}
int CCardType::GetRandomNum(byte *uRandomNum)
{
	//	string sCmd="0084000008";
	int nRet;
	byte ucCmd[256]={0};
	byte ucResp[256]={0};
	memset(uRandomNum,0,8);
	memcpy(ucCmd,"\x00\x84\x00\x00\x04",5);
	//ע�������������ֻ��ȡ4�ֽ�
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.send_buf=ucCmd;
	cmd.recv_buf=ucResp;
	cmd.send_len=5;
	cmd.cmd_type=0;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL)<<" GenRandomNum");
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memcpy(uRandomNum,ucResp,4);
	memset(m_szRandomNum,0,sizeof m_szRandomNum);
	dec2hex(uRandomNum,4,this->m_szRandomNum);
	return 0;
}
//��PSAM������DF03�µ��޸��ļ���MAC
int CCardType::CalcSafeMac4Sam(const char *szCmdbuf,char *szMac)
{
	int ret;
	unsigned char uRandom[8]={0};
	char szRandom[17] = {0};
	ret = this->GetRandomNum(uRandom);
	if(ret)
		return ret;
	dec2hex(uRandom,4,szRandom);
	memcpy(szRandom+8,"00000000",8);
	strcpy(this->m_szRandomNum,szRandom);
	return m_PSAMCardType->CalcSafeMac4Sam(this,szCmdbuf,szMac);
}

int CCardType::CalcExtAuthEncrypt4Sam(const char *szCardNo,int keyidx,const char *szCmdbuf,char *szEncrypt)
{
	return m_PSAMCardType->CalcExtAuthEncrypt4Sam(this,keyidx,szCmdbuf,szEncrypt);
}

int CCardType::CalcSafeMac(const char* szCmdBuf,char *szMac)
{
	char szBuf[256];
	string sCmd,sMsg;
	int nCmdLen;
	byte uCmd[256];
	byte uRandom[9]={0},uMac[9]={0};
	int nRet;
	nRet=GetRandomNum(uRandom);
	if(nRet)
	{
		return nRet;
	}
	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdBuf);
	memcpy(szBuf,szCmdBuf,nCmdBufLen);
	//nCmdBufLen/=2;
	//if( nCmdBufLen%8 )
	//	memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);
	//else
	//	memcpy(szBuf+nCmdBufLen*2,"8000000000000000",16);

	//string sKey="14FED29EE124BB88A5400CA3040EB941";

	//string sKey="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	string sKey="0A5DE6CE985D43989B7EBE64AD8EB9C3";
	byte uDAMK[32]={0};
	byte uCardDAMK[32]={0};
	byte uCardUID[9]={0};;
	int nKeyLen=0;
	hex2dec(szBuf,nCmdBufLen,uCmd,nCmdLen);
	hex2dec(sKey.c_str(),sKey.size(),uDAMK,nKeyLen);
	hex2dec(m_szCardUID,16,uCardUID,nKeyLen);
	PbocDiverKey(uCardUID,uDAMK,uCardDAMK);
	CalcMac(uRandom,uCardDAMK,2,uCmd,nCmdLen,uMac);
	/////test
//	CalcMac(uRandom,uDAMK,2,uCmd,nCmdLen,uMac);
	/////test
	dec2hex(uMac,4,szMac);
	return 0;
}
#if 0
int CCardType::CalcSafeMac(const char* szCmdBuf,char *szMac)
{
	char szBuf[256];
	string sCmd,sMsg;
	int nCmdLen;
	byte uCmd[256];
	byte uRandom[9]={0},uMac[9]={0};
	int nRet;
	nRet=GetRandomNum(uRandom);
	if(nRet)
	{
		return nRet;
	}
	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdBuf);
	memcpy(szBuf,szCmdBuf,nCmdBufLen);
	//nCmdBufLen/=2;
	//if( nCmdBufLen%8 )
	//	memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);
	//else
	//	memcpy(szBuf+nCmdBufLen*2,"8000000000000000",16);

	//string sKey="14FED29EE124BB88A5400CA3040EB941";

	string sKey="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	//string sKey="0A5DE6CE985D43989B7EBE64AD8EB9C3";
	byte uDAMK[32]={0};
	byte uCardDAMK[32]={0};
	byte uCardUID[9]={0};;
	int nKeyLen=0;
	hex2dec(szBuf,nCmdBufLen,uCmd,nCmdLen);
	/*
	hex2dec(m_szCardUID,16,uCardUID,nKeyLen);
	PbocDiverKey(uCardUID,uDAMK,uCardDAMK);
	CalcMac(uRandom,uCardDAMK,2,uCmd,nCmdLen,uMac);
	*/
	/////test
	hex2dec(sKey.c_str(),sKey.size(),uDAMK,nKeyLen);
	CalcMac(uRandom,uDAMK,2,uCmd,nCmdLen,uMac);
	/////test
	dec2hex(uMac,4,szMac);
	return 0;
}
#endif

//��ȫд
int  CCardType::UpdateBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData)
{
	int		nRet=0;
	char	szCmd[512]={0};
	byte    ucResp[256];
	char	szMac[9]={0};
	byte	nResLen=0;
	//nRet=SelectADF();
	//if(nRet)
	//	return nRet;
	sprintf(szCmd,"04D6%02X%02X%02X",0x80+ucSFI,ucOffset,ucLength+4);
	//����MAC
	dec2hex(ucData,ucLength,szCmd+strlen(szCmd));

	//nRet=CalcSafeMac(szCmd,szMac);
	nRet=CalcSafeMac4Sam(szCmd,szMac);
	if(nRet)
	{
		return nRet;
	}
	strcat(szCmd,szMac);
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.send_buf=(byte*)szCmd;
	cmd.recv_buf=ucResp;
	cmd.send_len=strlen(szCmd);
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR("�����ļ�����ret="<<GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	return 0;
}

int CCardType::ReadCard()
{
	int nRet=0;
	m_DpsCnt=0;
	m_PayCnt=0;
	m_CardBal=0;
	bool bSetReadField=false;
	nRet=SelectADF();
	if(nRet)
		return nRet;

	map<int,EFBUF>::iterator it;
	for(it=m_EFMap.begin();it!=m_EFMap.end();++it)
	{
		if(!it->second.ReadFieldSet.size())
			continue;
		bSetReadField=true;
		if(MONEY_SFID==it->first)
		{
			int iNeedReadBalance=1;
			if(it->second.ReadFieldSet.find(CF_DPSCNT)!=it->second.ReadFieldSet.end())
			{
				nRet=GetDpsCnt();
				if(nRet)
					return nRet;
				iNeedReadBalance=0;
			}
			if(it->second.ReadFieldSet.find(CF_PAYCNT)!=it->second.ReadFieldSet.end())
			{
				nRet=GetPayCnt();
				if(nRet)
					return nRet;
				iNeedReadBalance=0;
			}
			if(iNeedReadBalance)
			{
				nRet=GetBalance();
				if(nRet)
					return nRet;
			}
			continue;
		}
		memset(it->second.ReadBuf,0,sizeof(it->second.ReadBuf));
		switch(it->second.ReadRight)
		{
		case FRR_NULL:
			break;
		case FRR_REC_FREE:
		case FRR_REC_MAC:
			// TODO :
			nRet = ReadRecordFile(it->first,it->second.ReadBuf,1,it->second.FileSize);
			if(nRet)
			{
				if(nRet != 0x6A83)
					return nRet;
				else
				{
					memset(it->second.ReadBuf,0,it->second.FileSize);
				}
			}
			break;
		case FRR_FREE:
			if(it->second.FileSize>m_ReadFileLen)
			{
				nRet=ReadBinaryFile(it->first,0x00,m_ReadFileLen,it->second.ReadBuf);
				if(nRet)
					return nRet;
				nRet=ReadBinaryFile(it->first,m_ReadFileLen,it->second.FileSize-m_ReadFileLen,it->second.ReadBuf+m_ReadFileLen);
				if(nRet)
					return nRet;
			}
			else
			{
				nRet=ReadBinaryFile(it->first,0x00,it->second.FileSize,it->second.ReadBuf);
				if(nRet)
					return nRet;
			}
			break;
		case FRR_EXTAUTH_MAC:
			nRet = ExtAuth(m_szCardUID,1);
			if(nRet)
				return nRet;
		case FRR_MAC:
			if(it->second.FileSize>m_ReadFileLen)
			{
				nRet=ReadBinaryFile4Mac(it->first,0x00,m_ReadFileLen,it->second.ReadBuf);
				if(nRet)
					return nRet;
				nRet=ReadBinaryFile4Mac(it->first,m_ReadFileLen,it->second.FileSize-m_ReadFileLen,it->second.ReadBuf+m_ReadFileLen);
				if(nRet)
					return nRet;
			}
			else
			{
				nRet=ReadBinaryFile4Mac(it->first,0x00,it->second.FileSize,it->second.ReadBuf);
				if(nRet)
					return nRet;
			}
			break;
		default:
			break;
		}
	}
	/*
	if(!bSetReadField)
	{
		SET_ERR("����ʧ��:û�гɹ�����Ҫ��ȡ���ֶ�");
		return -1;
	}
	*/
	return 0;
}
int CCardType::WriteCard()
{
	int nRet=0;
	int sect_len = m_WriteFileLen;
	nRet=SelectADF();
	if(nRet)
		return nRet;
	map<int,EFBUF>::iterator itMap;
	set<int>::iterator itSet;
	for(itMap=m_EFMap.begin();itMap!=m_EFMap.end();++itMap)
	{
		if(!itMap->second.WriteFieldSet.size())
			continue;
		if(itMap->first==MONEY_SFID)
			continue;
		if(FRW_NULL==itMap->second.WriteRight)
			continue;
		if(FRW_MAC==itMap->second.WriteRight
			|| FRW_ENCRYPT == itMap->second.WriteRight
			|| FRW_ENCRYPT_MAC == itMap->second.WriteRight)
		{
			memset(itMap->second.ReadBuf,0,sizeof(itMap->second.ReadBuf));
			switch(itMap->second.ReadRight)
			{
			case FRR_NULL:
				break;
			case FRR_FREE:
				if(itMap->second.FileSize>sect_len)
				{
					nRet=ReadBinaryFile(itMap->first,0x00,sect_len,itMap->second.ReadBuf);
					if(nRet)
						return nRet;
					nRet=ReadBinaryFile(itMap->first,sect_len,itMap->second.FileSize-sect_len,itMap->second.ReadBuf+sect_len);
					if(nRet)
						return nRet;
				}
				else
				{
					nRet=ReadBinaryFile(itMap->first,0x00,itMap->second.FileSize,itMap->second.ReadBuf);
					if(nRet)
						return nRet;
				}
				break;
			case FRR_EXTAUTH_MAC:
				nRet = ExtAuth(m_szCardUID,1);
				if(nRet)
					return nRet;
			case FRR_MAC:
				if(itMap->second.FileSize>sect_len)
				{
					nRet=ReadBinaryFile4Mac(itMap->first,0x00,sect_len,itMap->second.ReadBuf);
					if(nRet)
						return nRet;
					nRet=ReadBinaryFile4Mac(itMap->first,sect_len,itMap->second.FileSize-sect_len,itMap->second.ReadBuf+sect_len);
					if(nRet)
						return nRet;
				}
				else
				{
					nRet=ReadBinaryFile4Mac(itMap->first,0x00,itMap->second.FileSize,itMap->second.ReadBuf);
					if(nRet)
						return nRet;
				}
				break;
			default:
				break;
			}
			for ( itSet=itMap->second.WriteFieldSet.begin() ; itSet != itMap->second.WriteFieldSet.end(); ++itSet )
			{
				int fieldidx=*itSet;
				memcpy(itMap->second.ReadBuf+m_FieldVect[fieldidx].offset,itMap->second.WriteBuf+m_FieldVect[fieldidx].offset,m_FieldVect[fieldidx].length);
			}
			memcpy(itMap->second.WriteBuf,itMap->second.ReadBuf,sizeof(itMap->second.WriteBuf));
			//MACд
			//if(FRW_MAC==itMap->second.WriteRight)
			{
				if(itMap->second.FileSize>sect_len)
				{
					nRet=UpdateBinaryFile(itMap->first,0x00,sect_len,itMap->second.WriteBuf);
					if(nRet)
						return nRet;
					nRet=UpdateBinaryFile(itMap->first,sect_len,itMap->second.FileSize-sect_len,itMap->second.WriteBuf+sect_len);
					if(nRet)
						return nRet;
				}
				else
				{
					nRet=UpdateBinaryFile(itMap->first,0x00,itMap->second.FileSize,itMap->second.WriteBuf);
					if(nRet)
						return nRet;
				}
			}
		}
		else if(FRW_MAC_DIRECT==itMap->second.WriteRight)
		{
			if(itMap->second.FileSize>sect_len)
			{
				nRet=UpdateBinaryFile(itMap->first,0x00,sect_len,itMap->second.WriteBuf);
				if(nRet)
					return nRet;
				nRet=UpdateBinaryFile(itMap->first,sect_len,itMap->second.FileSize-sect_len,itMap->second.WriteBuf+sect_len);
				if(nRet)
					return nRet;
			}
			else
			{
				nRet=UpdateBinaryFile(itMap->first,0x00,itMap->second.FileSize,itMap->second.WriteBuf);
				if(nRet)
					return nRet;
			}
		}
		itMap->second.WriteFieldSet.clear();
		memset(itMap->second.ReadBuf,0,sizeof(itMap->second.ReadBuf));
		memset(itMap->second.WriteBuf,0,sizeof(itMap->second.WriteBuf));
	}
	return 0;
}
int CCardType::SetFieldVal(int FieldID,const char *fieldval)
{
	char szFieldVal[64]={0};
	byte ucBuff[64]={0};
	int num=0;

	strcpy(szFieldVal,fieldval);

	EF_FIELD& FieldObj= m_FieldVect[FieldID];
	switch(FieldObj.type)
	{
		case FT_UCS2:
			szFieldVal[FieldObj.length]=0;
			EncodeUCS2((byte*)szFieldVal,ucBuff);
			break;
		case FT_ANSI:
			memcpy(ucBuff,szFieldVal,FieldObj.length);
			break;
		case FT_BCD_LPAD20:
			if(strlen(fieldval)==12)
			{
				sprintf(szFieldVal,"20%s",fieldval);
			}
			asc2bcd(szFieldVal,FieldObj.length*2,ucBuff,num);
			break;
		case FT_BCD_LAPDZERO:
			lpad(szFieldVal,FieldObj.length*2,'0');
			asc2bcd(szFieldVal,FieldObj.length*2,ucBuff,num);
			break;
		case FT_BCD:
			asc2bcd(szFieldVal,FieldObj.length*2,ucBuff,num);
			break;
		case FT_INT8:
			num=atoi(szFieldVal);
			ucBuff[0]=num;
			break;
		case FT_INT16:
			num=atol(szFieldVal);
			set_2byte_int(ucBuff,num);
			break;
		case FT_INT24:
			num=atol(szFieldVal);
			set_3byte_int(ucBuff,num);
			break;
		case FT_INT32:
			num=atol(szFieldVal);
			set_4byte_int(ucBuff,num);
			break;
		case FT_HEX_STR:
			num = strlen(szFieldVal);
			if(num % 2 != 0) num++;
			if(num > FieldObj.length*2)
				num = FieldObj.length*2;
			hex2dec(szFieldVal,num,ucBuff,num);
			break;
		default:
			return -1;
	}
	SetFieldWriteMode(FieldID);
	memcpy(m_EFMap[FieldObj.fid].WriteBuf +FieldObj.offset,ucBuff,FieldObj.length);
	return 0;
}

int CCardType::GetFieldVal(int FieldID,char *fieldval)
{
	char szFieldVal[64]={0};
	byte ucBuff[64]={0};
	int num=0;
	if(FieldID>CF_END||FieldID<CF_START)
	{
		SET_ERR("GetFieldVal:�ֶ�����"<<FieldID<<"������");
		return -1;
	}
	if(FieldID == CF_SUBSIDYNO)
	{
		strcpy(fieldval,"0");
		return 0;
	}

	EF_FIELD& FieldObj= m_FieldVect[FieldID];

	if(m_FieldVect[FieldID].unused)
	{
		SET_ERR("GetFieldVal:�ֶ�����"<<FieldID<<"δʹ��");
		switch(FieldObj.type)
		{
		case FT_INT8:
		case FT_INT16:
		case FT_INT24:
		case FT_INT32:
			strcpy(fieldval,"0");
			break;
		default:
			fieldval[0]=0;
			break;
		}
		return 0;
	}
	if(RW_W==m_FieldVect[FieldID].rw)
	{
		SET_ERR("���ֶ�"<<FieldID<<"�������");
		return -1;
	}
	set<int>::iterator it;
	it=m_EFMap[m_FieldVect[FieldID].fid].ReadFieldSet.find(FieldID);
	if(it==m_EFMap[m_FieldVect[FieldID].fid].ReadFieldSet.end())
	{
		SET_ERR("GetFieldVal:�ֶ�����"<<FieldID<<"δ���ö�");
		return 0;
	}
	switch(FieldID)
	{
		case CF_CARDBAL:
			sprintf(fieldval,"%d",m_CardBal);
			return 0;
		case CF_PAYCNT:
			sprintf(fieldval,"%d",m_PayCnt);
			return 0;
		case CF_DPSCNT:
			sprintf(fieldval,"%d",m_DpsCnt);
			return 0;
		default:
			break;
	}

	memcpy(ucBuff,m_EFMap[FieldObj.fid].ReadBuf+FieldObj.offset,FieldObj.length);
	switch(FieldObj.type)
	{
	case FT_UCS2:
		DecodeUCS2(ucBuff,(byte*)fieldval,FieldObj.length);
		fieldval[FieldObj.length]=0;
		break;
	case FT_ANSI:
		strcpy(fieldval,(char*)ucBuff);
		break;
	case FT_BCD:
	case FT_BCD_LPAD20:
		bcd2asc(ucBuff,FieldObj.length,szFieldVal);
		strcpy(fieldval,szFieldVal);
		break;
	case FT_BCD_LAPDZERO:
		bcd2asc(ucBuff,FieldObj.length,szFieldVal);
		for(num=0;num<FieldObj.length*2;num++)
		{
			if(szFieldVal[num]!='0')
					break;
		}
		strcpy(fieldval,szFieldVal+num);
		break;
	case FT_INT8:
		sprintf(fieldval,"%d",ucBuff[0]);
		break;
	case FT_INT16:
		num=get_2byte_int(ucBuff);;
		sprintf(fieldval,"%d",num);
		break;
	case FT_INT24:
		num=get_3byte_int(ucBuff);
		sprintf(fieldval,"%d",num);
		break;
	case FT_INT32:
		num=get_4byte_int(ucBuff);
		sprintf(fieldval,"%d",num);
		break;
	case FT_HEX_STR:
		dec2hex(ucBuff,FieldObj.length,fieldval);
		fieldval[FieldObj.length*2]=0;
		break;
	default:
		return -1;
	}
	return 0;
}
int CCardType::doRequestKeyCard(char *sCardPhyID)
{
	int nRet;
	unsigned char rlen,rdata[256]={0};
	char phyno[32] = {0};
	nRet=m_KeyReader->request_card(m_KeyReaderPara,phyno,m_keycardType);
	if(nRet)
	{
		SET_ERR("Ѱ��Կ������,"<<m_KeyReader->GetErrMsg(NULL));
		return nRet;
	}
	nRet=m_KeyReader->cpucard_poweron(m_KeyReaderPara,m_keycardType,&rlen,rdata);
	if(nRet)
	{
		SET_ERR("��Կ���ϵ����,"<<m_KeyReader->GetErrMsg(NULL));
		return nRet;
	}
	if(sCardPhyID)
		strcpy(sCardPhyID,phyno);
	return 0;
}
#define MAIN_CCK	"\x53\x89\x19\x80\x11\x23\x19\x76\x11\x13\xAA\xBB\xCC\x88\x00\xAE"
//����Կ����ȡ��Կ
int CCardType::LoadKeysFromKeyCard(const char *sKeyCardPwd)
{
	string sCmd;
	byte ucMainKey[16]={0};
	byte ucWorkKey[16]={0};
	int nRet=0;
	char sCardPhyID[17]={0};

	if(strlen(sKeyCardPwd)!=6)
	{
		SET_ERR("��Կ�����볤�ȴ���");
		return -1;
	}
	memcpy(ucMainKey,MAIN_CCK,16);

	nRet = doRequestKeyCard(sCardPhyID);
	if(nRet)
	{
		return nRet;
	}
	sCmd="0020000003";
	sCmd+=sKeyCardPwd;

	byte ucRespData[256]={0};
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.recv_buf=ucRespData;
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_KeyReader->cpucard_cmd(m_KeyReaderPara,&cmd,m_keycardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_KeyReader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//CCK
	memset(ucRespData,0,sizeof ucRespData);
	sCmd="00B0950010";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_KeyReader->cpucard_cmd(m_KeyReaderPara,&cmd,m_keycardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_KeyReader->GetErrMsg(NULL));
			return nRet;
		}
	}
	des3_context ctx3;
	des3_set_2keys( &ctx3, ucMainKey,ucMainKey+8 );
	des3_decrypt( &ctx3,ucRespData,m_CardKeys.MK);
	des3_decrypt( &ctx3,ucRespData+8,m_CardKeys.MK+8);
	for(int index=0;index<14;index++)
	{
		memset(ucRespData,0,sizeof ucRespData);
		sCmd="00B096";
		sCmd+= ltohex(index*8);
		sCmd+= "10";
		cmd.send_buf=(byte*)sCmd.c_str();
		cmd.send_len=sCmd.size();
		cmd.cmd_type=1;//16����
		nRet=m_KeyReader->cpucard_cmd(m_KeyReaderPara,&cmd,m_keycardType);
		if(nRet)
		{
			if(cmd.cmd_retcode)
			{
				SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
				return cmd.cmd_retcode;
			}
			else
			{
				SET_ERR(m_KeyReader->GetErrMsg(NULL));
				return nRet;
			}
		}
		memset(ucWorkKey,0,sizeof(ucWorkKey));
		des3_set_2keys( &ctx3, m_CardKeys.MK,m_CardKeys.MK+8 );
		des3_decrypt( &ctx3,ucRespData,ucWorkKey);
		des3_decrypt( &ctx3,ucRespData+8,ucWorkKey+8);
		memset(ucRespData,0,sizeof ucRespData);
		//������
		if( index == 0 )       memcpy(m_CardKeys.DPK1,ucWorkKey,16);
		else if(  index== 1 )  memcpy(m_CardKeys.DPK2,ucWorkKey,16);
		else if(  index== 2 )  memcpy(m_CardKeys.DLK1,ucWorkKey,16);
		else if(  index== 3 )  memcpy(m_CardKeys.DLK2,ucWorkKey,16);
		else if(  index== 4 )  memcpy(m_CardKeys.DTAC,ucWorkKey,16);
		else if(  index== 5 )  memcpy(m_CardKeys.DACK,ucWorkKey,16);
		else if(  index== 6 )  memcpy(m_CardKeys.DUK,ucWorkKey,16);
		else if(  index== 7 )  memcpy(m_CardKeys.DRPK,ucWorkKey,16);
		else if(  index== 8 )  memcpy(m_CardKeys.DAMK,ucWorkKey,16);
		else if(  index== 9 )  memcpy(m_CardKeys.DACK1,ucWorkKey,16);
		else if(  index== 10)  memcpy(m_CardKeys.DACK2,ucWorkKey,16);
		else if(  index== 11)  memcpy(m_CardKeys.DACK3,ucWorkKey,16);
		else if(  index== 12)  memcpy(m_CardKeys.LDACK,ucWorkKey,16);
		else if(  index== 13)  memcpy(m_CardKeys.LDAMK,ucWorkKey,16);
	}
	memcpy(cardtype_buff,m_CardKeys.LDACK,16);
	m_CardKeys.bLoad=1;
	m_PSAMCardType->setCardKeys(m_CardKeys);
	return 0;
}
int CCardType::IsLoadKeys()
{
	return m_CardKeys.bLoad;
}
int CCardType::IsLoadCloneKeys()
{
	return m_CloneKeys.bLoad;
}
//��¡��Կ��
int CCardType::LoadKeys4Clone(const char sKeyCardPin[7])
{
	string sCmd;
	int nRet=0;
	byte rlen=0;
	unsigned char ucRespData[256]={0};
	unsigned char ucRespLen=0;
	char sCardPhyID[17]={0};
	if(strlen(sKeyCardPin)!=6)
	{
		SET_ERR("��Կ�����볤�ȴ���");
		return -1;
	}
	nRet = doRequestKeyCard(sCardPhyID);
	if(nRet)
	{
		return nRet;
	}
	sCmd="0020000003";
	sCmd+=sKeyCardPin;

	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	memset(ucRespData,0,sizeof ucRespData);
	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	sCmd="00B0950010";
	memset(ucRespData,0,sizeof ucRespData);
	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(&m_CloneKeys,0,sizeof(m_CloneKeys));
	memcpy(m_CloneKeys.MK,ucRespData,16);
	for(int index=0;index<14;index++)
	{
		sCmd="00B096";
		sCmd+= ltohex(index*8);
		sCmd+= "10";
		memset(ucRespData,0,sizeof ucRespData);
		cmd.recv_buf=ucRespData;
		cmd.send_buf=(byte*)sCmd.c_str();
		cmd.send_len=sCmd.size();
		cmd.cmd_type=1;
		nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
		if(nRet)
		{
			if(cmd.cmd_retcode)
			{
				SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
				return cmd.cmd_retcode;
			}
			else
			{
				SET_ERR(m_Reader->GetErrMsg(NULL));
				return nRet;
			}
		}		//������
		if( index == 0 )       memcpy(m_CloneKeys.DPK1,ucRespData,8);
		else if(  index== 1 )  memcpy(m_CloneKeys.DPK2,ucRespData,8);
		else if(  index== 2 )  memcpy(m_CloneKeys.DLK1,ucRespData,8);
		else if(  index== 3 )  memcpy(m_CloneKeys.DLK2,ucRespData,8);
		else if(  index== 4 )  memcpy(m_CloneKeys.DTAC,ucRespData,8);
		else if(  index== 5 )  memcpy(m_CloneKeys.DACK,ucRespData,8);
		else if(  index== 6 )  memcpy(m_CloneKeys.DUK,ucRespData,8);
		else if(  index== 7 )  memcpy(m_CloneKeys.DRPK,ucRespData,8);
		else if(  index== 8 )  memcpy(m_CloneKeys.DAMK,ucRespData,8);
		else if(  index== 9 )  memcpy(m_CloneKeys.DACK1,ucRespData,8);
		else if(  index== 10)  memcpy(m_CloneKeys.DACK2,ucRespData,8);
		else if(  index== 11)  memcpy(m_CloneKeys.DACK3,ucRespData,8);
		else if(  index== 12)  memcpy(m_CloneKeys.LDACK,ucRespData,8);
		else if(  index== 13)  memcpy(m_CloneKeys.LDAMK,ucRespData,8);
	}
	m_CloneKeys.bLoad=1;
	return 0;
}
//��¡��Կ��
int CCardType::CloneKeyCard(const char sCloneCardPin[7])
{
	string sCmd;
	char sCardPhyID[17]={0};
	int nRet=0;
	char tmp[512]={0};
	unsigned char ucSendData[256]={0};
	unsigned char nSendLen=0;
	unsigned char ucRespData[256]={0};
	unsigned char ucRespLen=0;
	unsigned char ucCCK[17]={0};

	if(m_CloneKeys.bLoad!=1)
	{
		SET_ERR("��Կδװ��");
		return -1;
	}
	if(strlen(sCloneCardPin)!=6)
	{
		SET_ERR("��Կ�����볤�ȱ�����6λ");
		return -1;
	}
	for(int i=0;i<6;i++)
	{
		if(sCloneCardPin[i]>'9'||sCloneCardPin[i]<'0')
		{
			SET_ERR("������ֻ��ʹ������");
			return -1;
		}
	}
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;
	cmd.cmd_type=1;

	nRet = doRequestKeyCard(sCardPhyID);
	if(nRet)
	{
		return nRet;
	}
	memset(ucCCK, 0xFF,sizeof ucCCK);
	nRet=ExecExtAuthCmd(ucCCK);
	if(nRet)
	{
		if(0x6A88!=nRet)
		{
			if(0x63 == nRet>>8)
			{
				int iLen=0;
				hex2dec(szHexKSCCK,32,ucCCK,iLen);
				nRet=ExecExtAuthCmd(ucCCK);
				if(nRet)
				{
					return nRet;
				}
				else
				{
					SET_ERR("�ÿ���ʹ��,�������·������Ȼ��ոÿ�");
					return -1;
				}
			}
			return nRet;
		}
	}
	sCmd="00A40000023F00";
	memset(ucRespData,0,sizeof ucRespData);
	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	sCmd="80E00000073F004001AAFFFF";
	memset(ucRespData,0,sizeof ucRespData);
	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
//	sCmd="80D401001539F0F0AAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	memset(ucRespData,0,sizeof(ucRespData));
	sCmd =  "80D401001539F0FFAAFF";
	sCmd += szHexKSCCK;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof(ucRespData));
	sCmd="80D40100083AF0EF1166";
	sCmd+=sCloneCardPin;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof(ucRespData));
	sCmd="80E000150728001011EFFFFE";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof ucRespData);
	sCmd="80E00016072800E011EFFFFE";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof ucRespData);
	memset(tmp,0,sizeof(tmp));
	dec2hex(m_CloneKeys.MK,16,tmp);
	sCmd="00D6950010";
	sCmd+=tmp;
	memset(ucRespData,0,sizeof ucRespData);
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	unsigned char rBuff[256]={0};
	memset(rBuff,0,sizeof rBuff);
	int offset=8;
	unsigned char *pbuf=rBuff;
	memcpy(pbuf,m_CloneKeys.DPK1,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DPK2,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DLK1,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DLK2,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DTAC,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DACK,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DUK,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DRPK,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DAMK,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DACK1,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DACK2,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.DACK3,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.LDACK,offset);
	pbuf+=offset;
	memcpy(pbuf,m_CloneKeys.LDAMK,offset);
	pbuf+=offset;

	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff,0x40,tmp); //8*8

	sCmd="00D6960040";
	sCmd+=tmp;
	memset(ucRespData,0,sizeof ucRespData);
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff+0x40,0x30,tmp);  //6*8
	sCmd="00D6964030"; //����0x40ƫ�Ƶ�ַ
	sCmd+=tmp;
	memset(ucRespData,0,sizeof ucRespData);
	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	return 0;
}
//������Կ��
int CCardType::PublishKeyCard(unsigned char* sMasterKey,const char* sPin)
{
	//unsigned long _Snr=0;
	string sCmd;
	char sCardPhyID[17]={0};
	int nRet=0;
	char tmp[512]={0};
	unsigned char ucSendData[256]={0};
	unsigned char nSendLen=0;
	unsigned char ucRespData[256]={0};
	unsigned char ucRespLen=0;
	unsigned char ucCCK[17]={0};

	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;
	cmd.cmd_type=1;

	if(strlen(sPin)!=6)
	{
		SET_ERR("�����볤�ȴ���");
		return -1;
	}
	for(int i=0;i<6;i++)
	{
		if(sPin[i]>'9'||sPin[i]<'0')
		{
			SET_ERR("������ֻ��ʹ������");
			return -1;
		}
	}
	nRet = doRequestKeyCard(sCardPhyID);
	if(nRet)
	{
		return nRet;
	}
	memset(ucCCK, 0xFF,sizeof ucCCK);
	nRet=ExecExtAuthCmd(ucCCK);
	if(nRet)
	{
		if(0x6A88!=nRet)
		{
			if(0x63 == nRet>>8)
			{
				int iLen=0;
				hex2dec(szHexKSCCK,32,ucCCK,iLen);
				nRet=ExecExtAuthCmd(ucCCK);
				if(nRet)
				{
					return nRet;
				}
				else
				{
					SET_ERR("�ÿ���ʹ��,�������·������Ȼ��ոÿ�");
					return -1;
				}
			}
			return nRet;
		}
	}
	sCmd="00A40000023F00";

	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof(ucRespData));
	sCmd="80E00000073F004001AAFFFF";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//sCmd="80D401001539F0F0AAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	memset(ucRespData,0,sizeof(ucRespData));
	sCmd =  "80D401001539F0FFAAFF";
	sCmd += szHexKSCCK;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof(ucRespData));
	sCmd="80D40100083AF0EF1166";
	sCmd+=sPin;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof(ucRespData));
	sCmd="80E000150728001011EFFFFE";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof(ucRespData));
	sCmd="80E00016072800E011EFFFFE";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof(ucRespData));
	des3_context ctx3;
	byte ucMainCCK[17]={0};
	memcpy(ucMainCCK,MAIN_CCK,16);
	des3_set_2keys( &ctx3, ucMainCCK,ucMainCCK+8 );
	des3_encrypt( &ctx3,sMasterKey,ucRespData);
	des3_encrypt( &ctx3,sMasterKey+8,ucRespData+8);

	memset(tmp,0,sizeof(tmp));
	dec2hex(ucRespData,16,tmp);
	sCmd="00D6950010";
	sCmd+=tmp;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	unsigned char rBuff[256]={0};
	memset(rBuff,    0,sizeof rBuff);
	for( int i=0; i<14; i++ )
	{
		memset(ucRespData,0,sizeof ucRespData);
		sCmd="0084000008";
		cmd.send_buf=(byte*)sCmd.c_str();
		cmd.send_len=sCmd.size();
		nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
		if(nRet)
		{
			if(cmd.cmd_retcode)
			{
				SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
				return cmd.cmd_retcode;
			}
			else
			{
				SET_ERR(m_Reader->GetErrMsg(NULL));
				return nRet;
			}
		}
		des3_encrypt(&ctx3,ucRespData,rBuff+i*8);
	}
	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff,0x40,tmp); //8*8

	sCmd="00D6960040";
	sCmd+=tmp;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//nSendLen=5+0x10;
	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff+0x40,0x30,tmp);  //6*8

	sCmd="00D6964030"; //����0x40ƫ�Ƶ�ַ
	sCmd+=tmp;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	return 0;
}
/*
unsigned char a[]={"kingstar"};
unsigned char b[]={"ratsgnik"};
for(i=0;i<8;i++)
{
ucCCK[i]=a[i]^b[i];
ucCCK[8+i]=~ucCCK[i];
}
char buf[33]={0};
dec2hex(ucCCK,16,buf);
*/
//������Կ��
int CCardType::RecycleKeyCard()
{
	string sCmd;
	int nRet=0;
	nRet = doRequestKeyCard(NULL);
	if(nRet)
	{
		return nRet;
	}
	int iLen=0;
	unsigned char ucCCK[17]={0};

	int i=0;
	hex2dec(szHexKSCCK,32,ucCCK,iLen);
	nRet=ExecExtAuthCmd(ucCCK);
	if(nRet)
	{
		if(0x6A88!=nRet)
		{
			if(0x63 == nRet>>8)
			{
				//ʹ�ó�����Կ
				memset(ucCCK, 0xFF,sizeof ucCCK);
				nRet=ExecExtAuthCmd(ucCCK);
				if(nRet)
				{
					return nRet;
				}
			}
		}
		else
		{
			SET_ERR("�ÿ��ѻ���");
			return -1;
		}
	}

	unsigned char ucRespData[256]={0};

	sCmd="800E000000";

	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));

	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	m_Reader->beep(m_ReaderPara);
	return 0;
}

int CCardType::RestoreFactorySettings()
{
	string sCmd;
	int nRet=0;
	if(!m_CardKeys.bLoad)
	{
		SetLastErrMsg("��Կδװ��");
		return -1;
	}
	nRet=RequestCard();
	if(nRet)
	{
		return nRet;
	}
	int iLen=0;
	unsigned char ucCCK[17]={0};

	int i=0;
	hex2dec(szHexKSCCK,32,ucCCK,iLen);
	nRet=ExecExtAuthCmd(ucCCK);
	if(nRet)
	{
		if(0x6A88!=nRet)
		{
			if(0x63 == nRet>>8)
			{
				//ʹ�ó�����Կ
				memset(ucCCK, 0xFF,sizeof ucCCK);
				nRet=ExecExtAuthCmd(ucCCK);
				if(nRet)
				{
					return nRet;
				}
			}
		}
		else
		{
			//SET_ERR("�ÿ��ѻ���");
			m_Reader->beep(m_ReaderPara);
			return 0;
		}
	}
	unsigned char ucRespData[256]={0};

	sCmd="800E000000";

	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));

	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//m_Reader->beep(m_ReaderPara);
	return 0;
}
int CCardType::CommInit(const char *svrip,int svrport,int svrfunc)
{
	if(KS_YKT_Clt::Initialize(svrip,svrport,svrfunc))
	{
		//char path[1024];
		//GetModuleFileName(NULL,path,1024);
		//DEBUG_LOG(("xpackpath:%s",path));
		//AfxMessageBox(path);
		if(strlen(m_szAppPath))
		{
			char cpack_path[256]="";
			sprintf(cpack_path,"%s\\cpack.dat",m_szAppPath);
			KS_YKT_Clt::set_xpack_path(cpack_path);
		}
		else
			KS_YKT_Clt::set_xpack_path(".\\cpack.dat");
		return 0;
	}
	SET_ERR("����ͨѶ����ʧ��");
	return -1;
}
int CCardType::SaveKeys()
{
	int nRet=0;
	if(!IsLoadKeys())
	{
		SET_ERR("��Կδװ��");
		return -1;
	}
	if(!KS_YKT_Clt::IsInitialized())
	{
		SET_ERR("ϵͳͨѶģ��δ��ʼ��");
		return -1;
	}
	// ���̨��������
	KS_YKT_Clt clt;
	char sKeyHexStr[33];
	bool bRet=false;

	memset(sKeyHexStr,0,sizeof(sKeyHexStr));

	dec2hex(m_CardKeys.MK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("sall_name",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DPK1,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("scust_limit",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DPK2,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("scust_limit2",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DLK1,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("semail",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DLK2,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("semail2",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DTAC,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("snote",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DACK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("snote2",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DUK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("scert_no",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DRPK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("scert_no2",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DAMK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("scert_addr",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DACK1,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("vsvarstr1",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DACK2,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("vsvarstr2",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.DACK3,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("vsvarstr3",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.LDACK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("sbank_acc",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(m_CardKeys.LDAMK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("sbank_acc2",sKeyHexStr);
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}	// ����
	//����Ϊ�������
	bRet=clt.SetStringFieldByName("sstatus0","A");
	if(!bRet)
	{
		SET_ERR("����ͨѶ���ݰ�����");
		return -1;
	}
	if(!clt.SendRequest(845000,5000))
	{
		// TODO : �����ǳ�ʱ
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"������ͨѶ����:%s,������:%d",szMsg,clt.GetReturnCode());
		SET_ERR(errmsg);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		// ��ֵʧ��
		char sErrMsg[256]={0};
		clt.GetReturnMsg(sErrMsg);
		SET_ERR(sErrMsg);
		return nRet;
	}
	return 0;
}
int CCardType::InitUserCard(const char *sShowCardNo)
{
	int nRet=0;
	int iLen=0;
	byte ucCardPhyID[9]={0};
	if(!m_CardKeys.bLoad)
	{
		SetLastErrMsg("��Կδװ��");
		return -1;
	}
	//Ѱ��
	nRet=RequestCard();
	if(nRet)
	{
		return nRet;
	}
	if(strlen(m_szCardUID)==8)
		strcat(m_szCardUID,"80000000");
	if(strlen(m_szCardUID)!=16)
	{
		SET_ERR("������ID["<<m_szCardUID<<"]���ȴ���");
		return -1;
	}
	hex2dec(m_szCardUID,16,ucCardPhyID,iLen);

	int ret=0;
	vector<string> CmdVector;
	string sTmp;
	string sCmd;
	char sHexStr[64];
	byte rlen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char ucShowCardNo[11];
	if(NULL!=sShowCardNo && strlen(sShowCardNo)>10)
	{
		SET_ERR("��ʾ����["<<sShowCardNo<<"���ȴ���");
		return -1;
	}
	memset(ucShowCardNo,0,sizeof(ucShowCardNo));

	if(NULL!=sShowCardNo && strlen(sShowCardNo)>0)
	{
		strcpy((char*)ucShowCardNo,sShowCardNo);
	}

	CARDKEYS  LocalCardKeys;
	memset(&LocalCardKeys,0,sizeof(LocalCardKeys));

	PbocDiverKey(ucCardPhyID,m_CardKeys.DPK1,LocalCardKeys.DPK1);			//����1
	PbocDiverKey(ucCardPhyID,m_CardKeys.DPK1,LocalCardKeys.DPK2);			//����2
	PbocDiverKey(ucCardPhyID,m_CardKeys.DLK1,LocalCardKeys.DLK1);			//Ȧ��1
	PbocDiverKey(ucCardPhyID,m_CardKeys.DLK2,LocalCardKeys.DLK2);			//Ȧ��2
	PbocDiverKey(ucCardPhyID,m_CardKeys.DTAC,LocalCardKeys.DTAC);			//�ڲ���ԿTAC
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK,LocalCardKeys.DACK);			//Ӧ��������Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DUK,LocalCardKeys.DUK);				//PIN����
	PbocDiverKey(ucCardPhyID,m_CardKeys.DRPK,LocalCardKeys.DRPK);			//PIN��װ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DAMK,LocalCardKeys.DAMK);			//ά����Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,LocalCardKeys.DACK1);			//�ⲿ��֤1
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK2,LocalCardKeys.DACK2);			//�ⲿ��֤2
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK3,LocalCardKeys.DACK3);			//�ⲿ��֤3
	PbocDiverKey(ucCardPhyID,m_CardKeys.LDACK,LocalCardKeys.LDACK);			//СǮ���ⲿ��֤��Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.LDAMK,LocalCardKeys.LDAMK);			//СǮ��ά����Կ
	//ȡ�����`
	memset(ucRespData,0,sizeof(ucRespData));
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;
	unsigned char ucSendData[256]={0};
	unsigned char ucCCK[17]={0};
	memset(ucCCK, 0xFF,sizeof ucCCK);
	nRet=ExecExtAuthCmd(ucCCK);
	if(nRet)
	{
		if(0x6A88!=nRet)
		{
			if(0x63 == nRet>>8)
			{
				int iLen=0;
				hex2dec(szHexKSCCK,32,ucCCK,iLen);
				nRet=ExecExtAuthCmd(ucCCK);
				if(nRet)
				{
					return nRet;
				}
				else
				{
					SET_ERR("�ÿ���ʹ��,�������·������Ȼ��ոÿ�");
					return -1;
				}
			}
			return nRet;
		}
	}
	//ɾ��MF�µ�Ŀ¼���ļ�
	sCmd="800E000000";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//DIR�ļ�
	sCmd="00A4000000";
	CmdVector.push_back(sCmd);
	//������Կ�ļ�
	sCmd="80E00000073F004001AAFFFF";
	CmdVector.push_back(sCmd);
	//д���������Կ
	sCmd = "80D401001539F0AAAAAA";		//ʮ�����Ի���
	sCmd += szHexKSCCK;
	CmdVector.push_back(sCmd);

	//Ŀ¼�����ļ� EF01
//	sCmd="80E0000107AA0310F0F0FFFF";
//	CmdVector.push_back(sCmd);
	//��DF02
	sCmd="80E0DF021838009DF0AA957FFFD15600000145415359454E5452590000";
	CmdVector.push_back(sCmd);
	//��DF03
	sCmd="80E0DF03173811C8F0AA957FFFD156000001BDF0CACBB4EFD6A7B8B6";
	CmdVector.push_back(sCmd);
	//��DF04
	sCmd="80E0DF0418380330F0AA957FFFD156000001BDF0CACBB4EFC7AEB0FC32";
	CmdVector.push_back(sCmd);
	//ѡ��DF02
	sCmd="00A4040010D15600000145415359454E5452590000";
	CmdVector.push_back(sCmd);
	sCmd="80E00000073F004001AAFFFF";
	CmdVector.push_back(sCmd);
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DACK,16,sHexStr);
	sCmd="80D401001539F0AAAA66 ";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);

	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DAMK,16,sHexStr);
	sCmd="80D401001536F0AAFF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);

	//EF15
	sCmd="80E0001507A8003CF0F0FFFE";
	CmdVector.push_back(sCmd);
	//ѡ��DF03
	sCmd="00A404000FD156000001BDF0CACBB4EFD6A7B8B6";
	CmdVector.push_back(sCmd);
	//������Կ�ļ�
	sCmd="80E00000073F013001FFFFFF";//��Ҫ���Ȩ��FF�����޸�
	CmdVector.push_back(sCmd);
	//д���ⲿ��֤��ԿACK
	//sCmd="80D401001539F0F0AA33 FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DACK,16,sHexStr);
	sCmd = "80D401001539F0FFFF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//////////////////////////////////////////////////////////////////////
	//д��������Կ1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DPK1,16,sHexStr);
	sCmd="80D40101153EF00C0100";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��������Կ2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DPK2,16,sHexStr);
	sCmd="80D40102153EF00D0100";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��������Կ3
	//memset(sHexStr,0,sizeof(sHexStr));
	//dec2hex(g_MainKey.DPK3,16,sHexStr);
	//sCmd="80D40103153EF0020100";
	//sCmd+=sHexStr;
	//CmdVector.push_back(sCmd);
	//д��Ȧ����Կ1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DLK1,16,sHexStr);
	sCmd="80D40101153FF00E0200";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��Ȧ����Կ2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DLK2,16,sHexStr);
	sCmd="80D40102153FF00F0200";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д���ڲ���֤��Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DTAC,16,sHexStr);
	sCmd="80D401001534F00E0300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д�����������Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DUK,16,sHexStr);
	sCmd="80D401001537F00EFF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��PIN��װ��Կ��Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DRPK,16,sHexStr);
	sCmd="80D401011538F00EFF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д���ⲿ��֤��Կ1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DACK1,16,sHexStr);
	sCmd="80D401011539F00E2233";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д���ⲿ��֤��Կ2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DACK2,16,sHexStr);
	sCmd="80D401021539F00EBB33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д���ⲿ��֤��Կ3
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DACK3,16,sHexStr);
	sCmd="80D401031539F00ECC33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��Ӧ��ά����Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DAMK,16,sHexStr);
	sCmd="80D401011536F00BFF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��TAC��Կ
	//д�����
	sCmd="80D40100083AF0EF1133000000";
	CmdVector.push_back(sCmd);
	//����Ӧ�û����ļ� 0015
	sCmd="80E0001507A80038F0F0FFFE";
	CmdVector.push_back(sCmd);
	//д����ʾ����
	CmdVector.push_back("SHOWCARDNO");
	//�ֿ��˻����ļ� 0016
	sCmd="80E0001607A80070F0F0FFFE";
	CmdVector.push_back(sCmd);
	//���׹����ļ� 0012
	sCmd="80E0001207A80040F0F0FFFE";//����0x40
	CmdVector.push_back(sCmd);
	//18������ϸ
	sCmd="80E00018072E3217F0FFFFFF";
	CmdVector.push_back(sCmd);
	//Ǯ��
	sCmd="80E0EF02072F0208F0F0FF18";
	CmdVector.push_back(sCmd);
	//������ϸ�ļ�
	//sCmd="80E0000207AE0A28F0F0FFFE";
	//CmdVector.push_back(sCmd);
	//����Ǯ�������ļ�
	sCmd="80E0000107AE3228F0F0FFFE";
	CmdVector.push_back(sCmd);
	//�����ļ�
	sCmd="80E0001907A80010F2F0FF0A";
	CmdVector.push_back(sCmd);

	//;DF04
	sCmd="00A4040010D156000001BDF0CACBB4EFC7AEB0FC32";
	CmdVector.push_back(sCmd);

	sCmd="80E00000073F00D801AAFFFF";
	CmdVector.push_back(sCmd);
	//������Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DACK,16,sHexStr);
	sCmd="80D401001539F0AAAA66";
	sCmd +=sHexStr;
	CmdVector.push_back(sCmd);
	//СǮ���ļ�
	sCmd="80E0 0001 07 A80007F4F0FF0A";
	CmdVector.push_back(sCmd);
	//д��СǮ���ⲿ��֤��Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.LDACK,16,sHexStr);
	sCmd="80D401011539F0024433";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��СǮ��Ӧ��ά����Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.LDAMK,16,sHexStr);
	sCmd="80D401011536F00AFF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);

	for(int i=0;i<CmdVector.size();i++)
	{
		string& sSendData=CmdVector[i];
		if(sSendData=="SHOWCARDNO")
		{
			char szMac[9]={0};
			//����MAC
			memset(sHexStr,0,sizeof(sHexStr));
			dec2hex(ucShowCardNo,10,sHexStr);		//���ݿ�
			sSendData="04D6950A";
			sSendData+=ltohex(14);	//����+4�ֽ�MAC
			sSendData+=sHexStr;
			ret=CalcSafeMac4Sam(sSendData.c_str(),szMac);
			if(ret)
			{
				return ret;
			}
			sSendData+=szMac;
		}

		string_replace(sSendData," ","");
		string_replace(sSendData,"\t","");
		cmd.send_buf=(byte*)sSendData.c_str();
		cmd.send_len=sSendData.size();
		cmd.cmd_type=1;//16����
		nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
		if(nRet)
		{
			if(cmd.cmd_retcode)
			{
				SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
				return cmd.cmd_retcode;
			}
			else
			{
				SET_ERR(m_Reader->GetErrMsg(NULL));
				return nRet;
			}
		}
	}
	nRet = this->selectADFBySFI("3F00",1);
	return nRet;
}
int CCardType::CalcMacOnline(ST_TRANSPACK *transpack,char *sMac)
{
	int nRet=0,nLen=0;
	int nSendLen=0;
	unsigned char ucRespLen=0;

	unsigned char nRespLen=0;
	char szMac[9]={0};
	//���
	if(strlen(transpack->sCardPhyID)!=16)
	{
		if(strlen(transpack->sCardPhyID)==8)
		{
			strcat(transpack->sCardPhyID,"80000000");
		}
		else
		{
			SET_ERR("�����ų��ȴ���");
			//DEBUG_LOG(("������[%s]���ȴ���",transpack->sCardPhyID));
			return -1;
		}
	}
	if(strlen(transpack->sTermno)!=12)
	{
		SET_ERR("�ն˱�ų��ȴ���");
		//DEBUG_LOG(("�ն˱��[%s]���ȴ���",transpack->sTermno));
		return -1;
	}
	if(strlen(transpack->sTransDate)!=8)
	{
		SET_ERR("�������ڳ��ȴ���");
		//DEBUG_LOG(("��������[%s]���ȴ���",transpack->sTransDate));
		return -1;
	}
	if(strlen(transpack->sTransTime)!=6)
	{
		SET_ERR("����ʱ�䳤�ȴ���");
		//DEBUG_LOG(("����ʱ��[%s]���ȴ���",transpack->sTransDate));
		return -1;
	}
	if(transpack->nTransAmt==0)
	{
		SET_ERR("���׽���Ϊ0");
		//DEBUG_LOG((ks_geterrmsg(NULL)));
		return -1;

	}
	if(!KS_YKT_Clt::IsInitialized())
	{
		SET_ERR("ϵͳδ��ʼ��");
		return -1;
	}
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lsafe_level",transpack->nTransType); 	// ��������
	clt.SetIntFieldByName("lvol0",transpack->nCardNo); 				// ���׿���
	clt.SetStringFieldByName("sstation1",transpack->sCardPhyID); 	// ������
	if(transpack->nTransType)
		clt.SetIntFieldByName("lvol6",transpack->nPayCardCnt); 			// ����ǰ����
	else
		clt.SetIntFieldByName("lvol6",transpack->nDpsCardCnt); 			// ����ǰ����

	clt.SetIntFieldByName("lvol7",transpack->nBefBalance); 			// �뿨ֵ
	clt.SetDoubleFieldByName("lvol1",transpack->nTransAmt); 		// ���(��)
	clt.SetStringFieldByName("sdate0",transpack->sTransDate);		//��������
	clt.SetStringFieldByName("stime0",transpack->sTransTime);		//����ʱ��
	clt.SetStringFieldByName("sstock_code",transpack->sRandom); 	// �����
	clt.SetStringFieldByName("sserial0",transpack->sTermno); 		// �ն˺�
	clt.SetIntFieldByName("lserial0",transpack->nTermSeqno); 		// �ն���ˮ��
	clt.SetStringFieldByName("semp",transpack->sOperCode); 			// ����Ա
	clt.SetStringFieldByName("sstock_code2",transpack->sMac); //MAC1
	// ��ֵ��ȡ mac2
	if(!clt.SendRequest(846313,5000))
	{
		// TODO : �����ǳ�ʱ
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"������ͨѶ����:%s,������:%d",szMsg,clt.GetReturnCode());
		SET_ERR(errmsg);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		// ��ֵʧ��
		clt.GetReturnMsg(transpack->sErrMsg);
		SET_ERR(transpack->sErrMsg);
		//DEBUG_LOG(("����ʧ�ܴ�����[%d]������Ϣ[%s]",nRet,transpack->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

		//	clt.GetIntFieldByName("lserial1",(int*)&(transpack->nHostSeqno)); // ��̨��ˮ��
		//	clt.GetIntFieldByName("lvol0",&ret_data); // ���׿���
		GET_PACK_STR(clt,"sstock_code2",szMac);
		strcpy(sMac,szMac);
	}
	else
	{
		//DEBUG_LOG(("��ֵʧ��cardid[%d],ret[%X]",transpack->nCardNo,nRet));
		// ���ص�����������
		SET_ERR("��������������");
		return -1;
	}
	SET_ERR("Online����MAC["<<transpack->sRandom<<"]["<<szMac<<"]");
	return 0;
}
int CCardType::CalcDepositMac4Sam(ST_TRANSPACK *transpack,char *sMac)
{
	byte ucPhyId[8];
	byte cardDLKKey[16];
	byte sk[8];
	byte cipher_data[8];
	byte xor_data[8];
	des_context dctx;
	des3_context d3ctx;
	char szData[256];
	byte uData[256];
	char termno[20];

	int len,i,j;
	if(!m_CardKeys.bLoad)
	{
		SET_ERR("δװ����Կ����Կ");
		return -1;
	}

	memset(cardDLKKey,0,sizeof cardDLKKey);
	if(strlen(m_szCardUID)==16)
		hex2dec(this->m_szCardUID,16,ucPhyId,len);
	else
	{
		hex2dec(this->m_szCardUID,8,ucPhyId,len);
		memcpy(ucPhyId+4,"\x80\x00\x00\x00",4);
	}
	this->PbocDiverKey(ucPhyId,m_CardKeys.DLK1,cardDLKKey);

	// ��������
	sprintf(szData,"%s%04X8000",transpack->sRandom,transpack->nDpsCardCnt);
	hex2dec(szData,strlen(szData),uData,len);
	// ���������Կ
	memset(&d3ctx,0,sizeof d3ctx);
	des3_set_2keys(&d3ctx,cardDLKKey,cardDLKKey+8);
	memset(sk,0,sizeof sk);
	des3_encrypt(&d3ctx,uData,sk);

	// ����MAC
	sprintf(termno,"%s",transpack->sTermno);
	sprintf(szData,"%08X02%s%s%s800000000000",transpack->nTransAmt,termno,
		transpack->sTransDate,transpack->sTransTime);
	memset(uData,0,sizeof uData);
	hex2dec(szData,strlen(szData),uData,len);

	memset(cipher_data,0,sizeof cipher_data);
	for(i = 0;i < 3; ++i)
	{
		for(j = 0;j < 8; ++j)
		{
			xor_data[j] = cipher_data[j] ^ uData[i*8+j];
		}
		memset(&dctx,0,sizeof dctx);
		des_set_key(&dctx,sk);
		des_encrypt(&dctx,xor_data,cipher_data);
	}
	dec2hex(cipher_data,4,sMac);
	SET_ERR("����MAC");
	return 0;
}
int CCardType::AddMoney(ST_TRANSPACK *deposit)
{
	string sCmd;
	int nRet=0,nLen=0;
	char sHexStr[256]={0};
	unsigned char ucRespData[256];
	int nSendLen=0;
	unsigned char ucRespLen=0;
	char termno[13]={0};
	unsigned char sMac1[9]={0};

	memset(ucRespData,0,sizeof(ucRespData));
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;

	nRet=SelectADF();
	if(nRet)
	{
		deposit->cRetryFlag=1;
		return nRet;
	}
	nRet=VerifyPin(NULL);
	if(nRet)
	{
		deposit->cRetryFlag=1;
		return nRet;
	}
	sCmd="805000020B01";
	//���׽��
	//sprintf(sSendData+strlen(sSendData),"%02X%02X%02X%02X%012d",
	//	deposit->nTransAmt/256/256/256,
	//	deposit->nTransAmt/256/256,
	//	deposit->nTransAmt/256,
	//	deposit->nTransAmt%256,0);
	//�ն˺�
	byte ucTransAmt[5]={0};
	lpad(deposit->sTermno,12,'0');
	memset(sHexStr,0,sizeof(sHexStr));
	set_4byte_int(ucTransAmt,deposit->nTransAmt);
	dec2hex(ucTransAmt,4,sHexStr);
	sCmd+=sHexStr;
	sCmd+=deposit->sTermno;
	//�����ĳ���
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		deposit->cRetryFlag=1;
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
//	dec2hex(ucRespData,ucRespLen,temp);
//	DEBUG_LOG(("init for load resp[%s]",temp));
	char sMac2[9]={0};
	memset(sMac2,0,sizeof sMac2);
	//�����
	int nBefBal=get_4byte_int(ucRespData);
	//���Ѵ���
	int nDptCnt=get_2byte_int(ucRespData+4);
	//ȡ�����
	dec2hex(ucRespData+8,4,deposit->sRandom);
	// MAC1
	dec2hex(ucRespData+12,4,deposit->sMac);

//	DEBUG_LOG(("random[%s]date[%s]time[%s]",deposit->sRandom,deposit->sTransDate,deposit->sTransTime));
	//��ֵ����
	deposit->nDpsCardCnt=nDptCnt;

	if(nBefBal != deposit->nBefBalance)
	{
		if(nBefBal == deposit->nAftBalance)
		{
			// ��Ϊ�Ѿ���Ǯ�ɹ���
//			DEBUG_LOG(("�����ѳɹ�"));
			return 0;
		}
		SET_ERR("����ǰ����뿨�в�һ��");
		return -1;
	}
#if 0
	// ����
	strcpy(deposit->sTransDate,"20100712");
	strcpy(deposit->sTransTime,"133948");
	strcpy(deposit->sRandom,"D7B9770C");
#endif
#if 1 && defined(_DEBUG)
	nRet = CalcDepositMac4Sam(deposit,sMac2);
#else
	nRet=CalcMacOnline(deposit,sMac2);
#endif

	if(nRet)
	{
		deposit->cRetryFlag=1;
		//DEBUG_LOG(("����MAC2ʧ�� ret=%X",nRet));
		return nRet;
	}
	// ����д������
	memset(ucRespData,0,sizeof ucRespData);
	sCmd="805200000B";
	sCmd.append(deposit->sTransDate,8);
	sCmd.append(deposit->sTransTime,6);
	sCmd.append(sMac2,8);

	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		deposit->cRetryFlag=1;
		deposit->cGetProveFlag=1;
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	SET_ERR("��ֵ�ɹ�card["<<deposit->nCardNo<<"]money["<<deposit->nTransAmt
		<<"]dpscnt["<<deposit->nDpsCardCnt<<"]["<<deposit->sTransDate<<deposit->sTransTime
		<<"]");
	return 0;
}
int CCardType::PayMoney(ST_TRANSPACK *payment)
{
	string sCmd;
	char sHexStr[256]="";
	int  nSendDataHexLen=0;
	unsigned char ucSendData[256]="";
	int  nSendDataLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;

	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;

	int nRet=0,nLen=0;
	char sMac1[9]={0};
	char temp[256]={0};

	nRet=SelectADF();
	if(nRet)
	{
		payment->cRetryFlag=1;
		return nRet;
	}
	sCmd="805001020B01";
	//���׽��
	byte ucTransAmt[5]={0};
	memset(sHexStr,0,sizeof(sHexStr));
	lpad(payment->sTermno,12,'0');
	set_4byte_int(ucTransAmt,payment->nTransAmt);
	dec2hex(ucTransAmt,4,sHexStr);
	sCmd+=sHexStr;
	sCmd+=payment->sTermno;
	//�����ĳ���
	//DEBUG_LOG(("init for payment req[%s]",sCmd.c_str()));
	memset(ucRespData, 0,sizeof(ucRespData));
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		payment->cRetryFlag=1;
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
//	dec2hex(ucRespData,ucRespLen+2,temp);
//	DEBUG_LOG(("init for load resp[%s]",temp));
	//�����
	int nBefBal=get_4byte_int(ucRespData);
	//���Ѵ���
	int nPayCnt=get_2byte_int(ucRespData+4);
	//ȡ�����
	dec2hex(ucRespData+11,4,payment->sRandom);

	if(nBefBal != payment->nBefBalance)
	{
		if(nBefBal == payment->nAftBalance)
		{
			// ��Ϊ�Ѿ���Ǯ�ɹ���
			return 0;
		}
		SET_ERR("����ǰ����뿨�в�һ��");
		return -1;
	}
	payment->nPayCardCnt=nPayCnt;
	payment->nTransType = TRNS_TYPE_PURCHASE;

	byte sDate[20],sTime[20];
	memset(sDate,0,sizeof sDate);
	memset(sTime,0,sizeof sTime);
#if 0
	// ����MAC1
	nRet=CalcMacOnline(payment,sMac1);
	if(nRet)
	{
		payment->cRetryFlag=1;
		return nRet;
	}
#else
	nRet =CalcTransMac4Sam(payment,sMac1);
	if(nRet)
	{
		payment->cRetryFlag=1;
		return nRet;
	}
#endif
	// ����д������
	byte ucTermSeqno[5]={0};
	memset(ucRespData,0,sizeof(ucRespData));
	//payment->nTermSeqno = 0;
	set_4byte_int(ucTermSeqno,payment->nTermSeqno);
	dec2hex(ucTermSeqno,4,sHexStr);
	sHexStr[8]=0;
	sCmd="805401000F";
	sCmd+=sHexStr;
	sCmd.append(payment->sTransDate,8);
	sCmd.append(payment->sTransTime,6);
	sCmd += sMac1;
	memset(ucRespData, 0,sizeof(ucRespData));
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		payment->cRetryFlag=1;
		payment->cGetProveFlag=1;
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	dec2hex(ucRespData,4,payment->sMac); // TAC ��
	//doCheckPurchaseTAC(payment);
	payment->nErrCode = 0;
	return 0;
}
int CCardType::doCheckPurchaseTAC(ST_TRANSPACK *transpack)
{
	char szCmd[256] = {0};
	char data[256] = {0};
	int nRet;
	unsigned char respLen,ucResp[256] = {0};
	std::vector<std::string> vCmd;
	// delivery key
	sprintf(szCmd,"801A280408%s",transpack->sCardPhyID);
	vCmd.push_back(szCmd);
	// cipher data
	sprintf(data,"%08X06%s%08X%s%s8000",transpack->nTransAmt,transpack->sTermno,transpack->nTermSeqno
		,transpack->sTransDate,transpack->sTransTime);
	assert(strlen(data)==48);
	sprintf(szCmd,"80FA050020%s%s","0000000000000000",data);
	vCmd.push_back(szCmd);

	std::vector<std::string>::iterator iter;
	for(iter = vCmd.begin(); iter != vCmd.end(); ++iter)
	{
		std::string c = *iter;
		memset(ucResp,0,sizeof ucResp);
		respLen = 0;
		nRet = m_PSAMCardType->Adpu4HexSAM(c.c_str(),c.length(),ucResp,respLen);
		if(nRet)
		{
			SET_ERR("����TACʧ��");
			return nRet;
		}
	}
	memset(data,0,sizeof data);
	dec2hex(ucResp,4,data);
	if(strcmp(transpack->sMac,data)==0)
		return 0;
	SET_ERR("��֤����MACʧ��Card["<<transpack->sMac<<"] SAM["<<data<<"]");
	return -1;

}

int CCardType::Adpu(const unsigned char *ucCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen)
{
	int nRet=0;
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)ucCmd;
	cmd.send_len=ucSendLen;
	cmd.cmd_type=0;
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	ucRespLen=cmd.recv_len;
	return 0;
}
int CCardType::DoAdpu4Hex(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen,KS_CARD_TYPE CardType)
{
	int nRet=0;
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;
	cmd.send_buf=(byte*)szCmd;
	cmd.send_len=ucSendLen;
	cmd.cmd_type=1;	//16����
	if(CardType == KS_PSAM)
	{
		return KS_NOTSUPPORT;
	}
	else if(CardType == KS_KEYCARD)
	{
		nRet=m_KeyReader->cpucard_cmd(m_KeyReaderPara,&cmd,m_keycardType);
	}
	else
	{
		nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,CardType);
	}
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR("ִ��ָ�����"<<GetErrMsgByErrCode(cmd.cmd_retcode,NULL)
				<<" type["<<CardType<<"]");
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	ucRespLen=cmd.recv_len;
	return 0;
}
int CCardType::Adpu4Hex(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen)
{
	return DoAdpu4Hex(szCmd,ucSendLen,ucRespData,ucRespLen,m_defaultCardType);
}

int CCardType::InitForTrans(ST_TRANSPACK *trans,int trans_type)
{
	int nRet;
	std::string sCmd;
	char sHexStr[256]="";
	int  nSendDataHexLen=0;
	unsigned char ucSendData[256]="";
	int  nSendDataLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	char sRandom[30];
	char temp[256]={0};
	char sMac1[20] = {0};

	nRet= SelectADF();
	if(nRet)
	{
		return nRet;
	}
	trans->nTransType = trans_type;
	// ����
	if(trans_type == TRNS_TYPE_PURCHASE)
	{

		sCmd="805001020B01";
		//���׽��
		byte ucTransAmt[5]={0};
		memset(sHexStr,0,sizeof(sHexStr));
		lpad(trans->sTermno,12,'0');
		set_4byte_int(ucTransAmt,trans->nTransAmt);
		dec2hex(ucTransAmt,4,sHexStr);
		sCmd+=sHexStr;
		sCmd+=trans->sTermno;
		//�ն˺�
		//�����ĳ���
		memset(ucRespData, 0,sizeof ucRespData);
		if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
		{
			SET_ERR("���ѳ�ʼ��ʧ��"<<nRet);
			return nRet;
		}
		dec2hex(ucRespData,ucRespLen+2,temp);
		//�����
		int nBefBal=get_4byte_int(ucRespData);
		//���Ѵ���
		int nPayCnt=get_2byte_int(ucRespData+4);
		if(nBefBal != trans->nBefBalance)
		{
			if(nBefBal + trans->nTransAmt == trans->nBefBalance)
			{
				if(nPayCnt == trans->nPayCardCnt+1)//�����ѳɹ�
				{
					return 0;
				}
			}
			//ks_setlasterr("������ǰ����뵱ǰ������",-1);
			return -1;
		}
		if(nPayCnt != trans->nPayCardCnt)
		{
			SET_ERR("���Ѵ����뿨�в�һ��");
			return -1;
		}
		memset(sRandom,0,sizeof(sRandom));
		//ȡ�����
		dec2hex(ucRespData+11,4,sRandom);
		memcpy(trans->sRandom,sRandom,8);
		trans->sRandom[8] = 0;
		return 0;
	}
	else if(trans_type == TRNS_TYPE_LOAD )// ��ֵ
	{
		if( (nRet=VerifyPin())!=0) return nRet;
		sCmd="805000020B01";
		//���׽��
		//�ն˺�
		byte ucTransAmt[5]={0};
		memset(sHexStr,0,sizeof(sHexStr));
		lpad(trans->sTermno,12,'0');
		set_4byte_int(ucTransAmt,trans->nTransAmt);
		dec2hex(ucTransAmt,4,sHexStr);
		sCmd+=sHexStr;
		sCmd+=trans->sTermno;
		//�����ĳ���

		if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
		{
			SET_ERR("��ֵ��ʼ��ʧ��"<<nRet);
			return nRet;
		}
		dec2hex(ucRespData,ucRespLen,temp);
		char sMac2[9]={0};
		memset(sMac2,0,sizeof sMac2);
		//�����
		int nBefBal=get_4byte_int(ucRespData);
		//���Ѵ���
		int nDpsCnt=get_2byte_int(ucRespData+4);
		//ȡ�����
		dec2hex(ucRespData+8,4,trans->sRandom);
		dec2hex(ucRespData+12,4,trans->sMac);


		trans->nDpsCardCnt=nDpsCnt;
		trans->nBefBalance =nBefBal;
		return 0;
	}
	else if(trans_type == TRNS_TYPE_GRAYLOCK)
	{
		// INITIAL FOR GREY LOCK
		sCmd = "E07A08020701";
		lpad(trans->sTermno,12,'0');
		sCmd += trans->sTermno;
		sCmd += "0F";
		memset(ucRespData, 0,sizeof ucRespData);
		if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
		{
			return nRet;
		}

		trans->nBefBalance = get_4byte_int(ucRespData);
		trans->nPayCardCnt = get_2byte_int(ucRespData+4);
		memset(sRandom,0,sizeof(sRandom));
		//ȡ�����
		dec2hex(ucRespData+11,4,sRandom);
		memcpy(trans->sRandom,sRandom,8);
		trans->sRandom[8] = 0;

		// ����mac1
		nRet = CalcTransMac4Sam(trans,sMac1);
		if(nRet)
		{
			return nRet;
		}

		// GREY LOCK
		sCmd = "E07C08000B";
		memset(temp,0,sizeof temp);
		set_4byte_int((unsigned char*)temp,trans->nTermSeqno);
		sCmd += temp;
		sCmd += trans->sRandom;
		sCmd += trans->sTransDate;
		sCmd += trans->sTransTime;
		sCmd += sMac1;
		sCmd += "10";
		memset(ucRespData, 0,sizeof ucRespData);
		if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
		{
			return nRet;
		}

		// ������Կ
		dec2hex(ucRespData+4,4,trans->sMac);
		trans->sMac[8] = 0;
		return 0;
	}
	else if(trans_type == TRNS_TYPE_CAPP_PURCHASE)
	{
		sCmd = "805003020B01";

		// ���׽��
		byte ucTransAmt[5]={0};
		memset(sHexStr,0,sizeof(sHexStr));
		set_4byte_int(ucTransAmt,trans->nTransAmt);
		dec2hex(ucTransAmt,4,sHexStr);
		sCmd+=sHexStr;
		// �ն˺�
		lpad(trans->sTermno,12,'0');
		sCmd+=trans->sTermno;
		sCmd += "0F";

		memset(ucRespData, 0,sizeof ucRespData);
		if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
		{
			return nRet;
		}
		dec2hex(ucRespData,ucRespLen,temp);
		char sMac2[9]={0};
		memset(sMac2,0,sizeof sMac2);
		//�����
		int nBefBal=get_4byte_int(ucRespData);
		//���Ѵ���
		int nDpsCnt=get_2byte_int(ucRespData+4);
		//ȡ�����
		dec2hex(ucRespData+8,4,trans->sRandom);


		trans->nDpsCardCnt=nDpsCnt;
		trans->nBefBalance =nBefBal;
		return 0;

	}
	else if (trans_type == TRNS_TYPE_POSTPAID)
	{

		PAYDTL_FILE newdtl;
		memset(&newdtl,0,sizeof newdtl);
		nRet = dealPostPaidPreProcess(trans,&newdtl);
		if(nRet)
		{
			return -1;
		}
		//
		return 0;
	}
	else
	{
		SET_ERR("�������");
		return -1;
	}
	return 0;
}
int CCardType::DebitForTrans(ST_TRANSPACK *trans)
{
	unsigned char ucRespData[256];
	ks_cpu_cmd_t cmd;
	std::string sCmd;
	int nRet;
	if(trans->nTransType == TRNS_TYPE_LOAD )// ��ֵ
	{
		memset(ucRespData,0,sizeof ucRespData);
		sCmd="805200000B";
		sCmd.append(trans->sTransDate,8);
		sCmd.append(trans->sTransTime,6);
		sCmd.append(trans->sMac,8);

		cmd.send_buf=(byte*)sCmd.c_str();
		cmd.send_len=sCmd.size();
		cmd.recv_buf=(byte*)ucRespData;
		cmd.cmd_type=1;//16����
		nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
		if(nRet)
		{
			trans->cRetryFlag=1;
			trans->cGetProveFlag=1;
			if(cmd.cmd_retcode)
			{
				SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
				return cmd.cmd_retcode;
			}
			else
			{
				SET_ERR(m_Reader->GetErrMsg(NULL));
				return nRet;
			}
		}
		SET_ERR("��ֵ�ɹ�card["<<trans->nCardNo<<"]money["<<trans->nTransAmt
			<<"]dpscnt["<<trans->nDpsCardCnt<<"]["<<trans->sTransDate<<trans->sTransTime
			<<"]");
		return 0;
	}
	else if(trans->nTransType == TRNS_TYPE_PURCHASE) // ����
	{
		SET_ERR("��δʵ�ָù���");
		return -1;
	}
	else
	{
		SET_ERR("��֧�ֵ���������");
		return -1;
	}
}
int CCardType::dealPostPaidPreProcess(ST_TRANSPACK * trans,PAYDTL_FILE * pay)
{
	byte ucRespData[512];
	int nRet,nSendDataLen,num;
	byte ucRespLen;
	std::string sCmd;
	char sMac1[9] = {0};
	char sHexStr[512];
	char temp[64];
	// 1. ��ȡ����־
	// 2. ���¼�¼�ļ�
	// 3. ������
	byte lock_flag = 0;
	sCmd = "00B0951401";
	memset(ucRespData, 0,sizeof ucRespData);
	if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		SET_ERR("��ȡ������־ʧ��");
		return nRet;
	}
	lock_flag = ucRespData[0];
	if(lock_flag == CS_LOCK )
	{
		// ���ѱ�����
		return -1;
	}
	// ���¼�¼�ļ� , �ļ���ʶ�� 0 0 0 0 1  1 0 0 B = 0x0C
	sCmd = "00B2010C00";
	memset(ucRespData, 0,sizeof ucRespData);
	if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		if(nRet != 0x6A83)
		{
			SET_ERR("��ȡ��¼�ļ�ʧ��");
			return nRet;
		}
		memset(&m_lastPayDTL,0,sizeof m_lastPayDTL);
	}
	else
	{
		memcpy(&m_lastPayDTL,ucRespData,sizeof(m_lastPayDTL));
	}

	//
	fillPayDTL(trans,pay);
	dealDailySumPay(&m_lastPayDTL,pay);
	memset(pay->transAmt,0,sizeof(pay->transAmt));
	// POSTPAID
	num = get_3byte_int(m_lastPayDTL.transAmt);
	if(m_lastPayDTL.transType == TRNS_TYPE_POSTPAID && num == 0)
	{
		// ���¼�¼
		sCmd = "00DC000C";
	}
	else
	{
		// ���Ӽ�¼
		sCmd = "04E2000C";
	}
	// ����·����д + 4 byte MAC
	nSendDataLen = sizeof(PAYDTL_FILE) + 4;
	memset(temp,0,sizeof temp);
	sprintf(temp,"%02X",nSendDataLen);
	sCmd += temp;
	//
	memset(sHexStr,0,sizeof sHexStr);
	dec2hex((const unsigned char*)pay,sizeof(PAYDTL_FILE),sHexStr);
	sCmd += sHexStr;
	// ����mac
	this->CalcSafeMac4Sam(sCmd.c_str(),sMac1);
	sCmd += sMac1;

	//
	memset(ucRespData, 0,sizeof ucRespData);
	if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		SET_ERR("׷�Ӽ�¼ʧ��");
		return nRet;
	}
	// ����������ʶ
	sCmd = "04D6951405";
	sprintf(temp,"%02X",CS_LOCK);
	sCmd += temp;
	this->CalcSafeMac4Sam(sCmd.c_str(),sMac1);
	sCmd += sMac1;
	memset(ucRespData, 0,sizeof ucRespData);
	if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		SET_ERR("����������־ʧ��");
		return nRet;
	}
	return 0;
}

void CCardType::fillPayDTL(ST_TRANSPACK * trans,PAYDTL_FILE * pay)
{
	int len,num;
	hex2dec(trans->sTransDate,8,pay->transDate,len);
	hex2dec(trans->sTransTime,6,pay->transTime,len);
	// TODO : trans type
	pay->transType = TRNS_TYPE_POSTPAID;
	///////////
	hex2dec(trans->sTermno,12,pay->termNO,len);
	set_2byte_int(pay->termSeqno,trans->nTermSeqno);
	set_4byte_int(pay->befBalance,trans->nBefBalance);
	set_3byte_int(pay->transAmt,trans->nTransAmt);
	set_2byte_int(pay->payCardCnt,trans->nPayCardCnt);


}
void CCardType::dealDailySumPay(PAYDTL_FILE * oldpay,PAYDTL_FILE * newpay)
{
	int dailysum;
	dailysum = get_3byte_int(oldpay->dailySumFee);
	if(memcmp(oldpay->transDate,newpay->transDate,4) !=0)
	{
		// ��������
		dailysum = get_3byte_int(newpay->transAmt);
	}
	else
	{
		dailysum += get_3byte_int(newpay->transAmt);
	}
	set_3byte_int(newpay->dailySumFee,dailysum);
}


int CCardType::GrayDebitUnlock(ST_TRANSPACK *transpack)
{
	int nRet;
	std::string sCmd;
	char sHexStr[256]="";
	int  nSendDataHexLen=0;
	unsigned char ucSendData[256]="";
	int  nSendDataLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char ucTransAmt[5] = {0};

	sCmd = "E07E08021B";
	// ���׽��
	set_4byte_int(ucTransAmt,transpack->nTransAmt);
	memset(sHexStr,0,sizeof sHexStr);
	dec2hex(ucTransAmt,4,sHexStr);
	sCmd += sHexStr;
	// �����״���
	set_2byte_int(ucTransAmt,transpack->nPayCardCnt);
	memset(sHexStr,0,sizeof sHexStr);
	dec2hex(ucTransAmt,2,sHexStr);
	sCmd += sHexStr;
	// �ն˻����
	lpad(transpack->sTermno,12,'0');
	sCmd += transpack->sTermno;
	// �ն˻��������
	set_4byte_int(ucTransAmt,transpack->nTermSeqno);
	memset(sHexStr,0,sizeof sHexStr);
	dec2hex(ucTransAmt,4,sHexStr);
	sCmd += sHexStr;
	//���� ���� ʱ��
	sCmd += transpack->sTransDate;
	sCmd += transpack->sTransTime;
	// GMAC
	sCmd += transpack->sMac;
	sCmd += "04";

	memset(ucRespData, 0,sizeof ucRespData);
	if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}

	return 0;

}
int CCardType::GrayUnlock(ST_TRANSPACK *transpack)
{
	return KS_NOTSUPPORT;
}

int CCardType::CalcTransMac4Sam(ST_TRANSPACK *transpack,char *sMac)
{
	return m_PSAMCardType->CalcTransMac4Sam(transpack,sMac);
}


int CCardType::CAPPUpdate(ST_TRANSPACK *transpack)
{
	int nRet;
	std::string sCmd;
	char sHexStr[256]="";
	int  nSendDataHexLen=0;
	unsigned char ucSendData[256]="";
	int  nSendDataLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char ucTransAmt[5] = {0};

	return -1;
}
int CCardType::CAPPDebit(ST_TRANSPACK *transpack)
{
	int nRet;
	std::string sCmd;
	char sHexStr[256]="";
	int  nSendDataHexLen=0;
	unsigned char ucSendData[256]="";
	int  nSendDataLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char ucTransAmt[5] = {0};
	//  P2 = 0 0 0 0 0 0 0 0
	sCmd = "80DC02001B";
	// ���µļ�¼��
	return -1;

}

int CCardType::ReadRecordFile(int SFI,unsigned char *ucData,int idx,int len)
{
	char szCmd[256];
	byte uResp[256],respLen;
	ks_cpu_cmd_t cmd;
	int nRet;
	if(len >256)
	{
		SET_ERR("��ȡ��¼���ȳ���256���ֽ�");
		return KS_NOTSUPPORT;
	}
	sprintf(szCmd,"00B2%02X%02X%02X",idx,(SFI<<3)+4,len);

	memset(&cmd,0,sizeof cmd);
	cmd.send_buf = (byte*)szCmd;
	cmd.send_len = strlen(szCmd);
	cmd.recv_buf = uResp;
	cmd.cmd_type = 1; // hex
	nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,this->m_defaultCardType);
	if(nRet)
	{
		SET_ERR("��ȡ��¼�ļ�ʧ��,ret["<<nRet<<"]");
		return nRet;
	}

	memcpy(ucData,uResp,cmd.recv_len-2);
	return 0;
}
int CCardType::ReadRecordFile4Mac(int SFI,unsigned char *ucData,int idx,int len)
{
	SET_ERR("�޷���ȡ����ȫ���ĵļ�¼�ļ�");
	return KS_NOTSUPPORT;
}

int CCardType::PostPaidUpdate(ST_TRANSPACK *transpack)
{
	// 1 �ж�������־
	// 2 ��ȡ���һ����ϸ���ж��Ƿ��Ǻ󸶷�����
	// 3 ����������ˮ��¼
	return -1;

}
int CCardType::PostPaidDebit(ST_TRANSPACK *transpack)
{
	// 1 �ж�������־
	// 2 ��ȡ���һ����ϸ���ж��Ƿ��Ǻ󸶷�����
	// 3 ����������ˮ��¼
	// 4 �ۿ����
	return -1;
}

int CCardType::InitCardTypeDLL()
{
	//m_keycardPara = *m_KeyReaderPara;
	m_license->get_public_int_param("kscardlib.keycardtype",&(m_keycardPara.cpuport));
	if(m_KeyReaderPara->cpuport == CARDSLOT_RF)
	{
		m_keycardType = KS_CPUCARD;
	}
	else
	{
		m_keycardType = KS_PSAM;
	}
	return 0;
}
//nTransType 1-��ֵ 2-���ѣ�����ǰ�����ѻ��ֵ����
int CCardType::GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac,unsigned char *sTac)
{
	unsigned char ucCmd[33]={"\x80\x5A\x00"};
	unsigned char ucRespData[256]={0};
	unsigned char ucRespLen=0;;
	if(1==nTransFlag)
	{
		ucCmd[3]=0x02;
	}
	else
	{
		ucCmd[3]=0x06;
	}
	ucCmd[4]=0x02;
	set_2byte_int(ucCmd+5,CardCnt);
	ucCmd[7]=0x08;

	int nRet=Adpu(ucCmd,8,ucRespData,ucRespLen);
	if(nRet)
	{
		//SET_ERR("ȡ������֤ʧ��"<<nRet);
		return nRet;
	}
	if(sMac)
	{
		memcpy(sMac,ucRespData,4);
	}
	if(sTac)
	{
		memcpy(sTac,ucRespData+4,4);
	}
	return 0;
}

int CCardType::checkCardType(int ct)
{
	switch(ct)
	{
		case KS_CPUCARD:
		case KS_FIXCARD:
			m_CardTypeCode = 0x0100;
			return 0;
		default:
			return -1;
	}
}
