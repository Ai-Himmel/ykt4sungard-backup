
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sstream>
using namespace std;

#include "mystring.h"
#include "kscardtype.h"
#include "global_func.h"
#include "ks_cardtype_mobile.h"
#include "ksreader.h"
#include "des.h"
#include "log.h"
#include "ucs2code.h"
#pragma pack(1)	
typedef struct 
{
	byte ucCardStatus;		//��״̬	CHAR
	byte ucCardVerNo[7];	//�������汾�� BCD
	byte ucAppType;			//Ӧ������
	byte ucAppVer;			//Ӧ�ð汾
	byte ucCardNo[10];		//���׿���
	byte ucSubsidyno[4];	//�������κ� int32
	byte ucExpireDate[4];	//��ֹ����
	byte ucFeeType;			//�շ����
	byte ucIssueID[1];		//������ID
}EF_PUBLICAPP;
typedef struct 
{
	byte ucCardType;	//������
	byte ucSex;			//�Ա�
	byte ucName[20];	//����
	byte ucIDNo[32];	//���֤��
	byte ucIDType;		//�û�֤������
}EF_USERINFO;

typedef struct 
{
	byte ucLastTransDate[4];	//���������,BCD
	byte ucDayTotalAmt[3];		//�����ۼ����ѽ��,INT24
	byte ucDayMaxAmt[3];		//���ۼ��޶�,INT24����λ��
	byte ucCardPwd[3];			//������
	byte ucCustType;			//�ͻ����,CHAR
	byte ucCustID[4];			//�ͻ���,INT32
	byte ucSchoolCode;			//У������,CHAR
	byte ucStuempNo[20];		//ѧ���ţ�ANSI
	byte ucDeptCode[20];		//���Ŵ���,ANSI
	byte ucUnused[5];			//����
}EF_PRIVATEAPP;
#pragma pack()

#include "log.h"

CCardTypeMobile::CCardTypeMobile()
{
	set_cardtype_name("ks_cardtype_mobile.dll");
	m_sDefaultPin="1234";
	EF_FIELD EField;
	memset(&EField,0,sizeof(EField));
	//�ȳ�ʼ��Ϊ0
	if(m_FieldVect.size())
		m_FieldVect.clear();
	if(m_EFMap.size())
		m_EFMap.clear();
	EField.unused=1;
	for(int i=0;i<=CF_END;i++)
		m_FieldVect.push_back(EField);

	assert(sizeof(EF_PUBLICAPP)==30);
	assert(sizeof(EF_USERINFO)==55);
	assert(sizeof(EF_PRIVATEAPP)==64);

	EF_PUBLICAPP	PublicApp;
	EF_USERINFO		UserInfo;
	EF_PRIVATEAPP	PrivateApp;

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
	m_FieldVect[CF_CARDVERNO].type=FT_BCD;
	//Ӧ������
	m_FieldVect[CF_APPTYPE].unused=0;
	m_FieldVect[CF_APPTYPE].offset = &PublicApp.ucAppType-(byte*)&PublicApp;
	m_FieldVect[CF_APPTYPE].length = sizeof(PublicApp.ucAppType);
	m_FieldVect[CF_APPTYPE].fid=0x15;
	m_FieldVect[CF_APPTYPE].type=FT_INT8;
	//����
	m_FieldVect[CF_CARDNO].unused=0;
	m_FieldVect[CF_CARDNO].offset = PublicApp.ucCardNo-(byte*)&PublicApp;
	m_FieldVect[CF_CARDNO].length = sizeof(PublicApp.ucCardNo);
	m_FieldVect[CF_CARDNO].fid=0x15;
	m_FieldVect[CF_CARDNO].type=FT_BCD_LAPDZERO;
	//�������κ�
	m_FieldVect[CF_SUBSIDYNO].unused=0;
	m_FieldVect[CF_SUBSIDYNO].offset = PublicApp.ucSubsidyno - (byte*)&PublicApp;
	m_FieldVect[CF_SUBSIDYNO].length = sizeof(PublicApp.ucSubsidyno);
	m_FieldVect[CF_SUBSIDYNO].fid=0x15;
	m_FieldVect[CF_SUBSIDYNO].type=FT_INT32;
	//��������
	//m_FieldVect[CF_STARTDATE].offset = PublicApp.ucStartDate-(byte*)&PublicApp;
	//m_FieldVect[CF_STARTDATE].length = sizeof(PublicApp.ucStartDate);
	//m_FieldVect[CF_STARTDATE].fid=0x15;
	//m_FieldVect[CF_STARTDATE].type=FT_BCD;
	//��Ч��
	m_FieldVect[CF_EXPIREDATE].unused=0;
	m_FieldVect[CF_EXPIREDATE].offset = PublicApp.ucExpireDate-(byte*)&PublicApp;
	m_FieldVect[CF_EXPIREDATE].length = sizeof(PublicApp.ucExpireDate);
	m_FieldVect[CF_EXPIREDATE].fid=0x15;
	m_FieldVect[CF_EXPIREDATE].type=FT_BCD;
	//���ṹ�汾
	m_FieldVect[CF_CARDSTRUCTVER].unused=0;
	m_FieldVect[CF_CARDSTRUCTVER].offset = &PublicApp.ucAppVer-(byte*)&PublicApp;
	m_FieldVect[CF_CARDSTRUCTVER].length = sizeof(PublicApp.ucAppVer);
	m_FieldVect[CF_CARDSTRUCTVER].fid=0x15;
	m_FieldVect[CF_CARDSTRUCTVER].type=FT_INT8;
	//�շ����
	m_FieldVect[CF_FEETYPE].unused=0;
	m_FieldVect[CF_FEETYPE].offset = &PublicApp.ucFeeType - (byte*)&PublicApp;
	m_FieldVect[CF_FEETYPE].length = sizeof(PublicApp.ucFeeType);
	m_FieldVect[CF_FEETYPE].fid=0x15;
	m_FieldVect[CF_FEETYPE].type=FT_INT8;
	//���з���ʶ
	m_FieldVect[CF_PUBLISHID].unused=0;
	m_FieldVect[CF_PUBLISHID].offset = PublicApp.ucIssueID-(byte*)&PublicApp;
	m_FieldVect[CF_PUBLISHID].length = sizeof(PublicApp.ucIssueID);
	m_FieldVect[CF_PUBLISHID].fid=0x15;
	m_FieldVect[CF_PUBLISHID].type=FT_ANSI;
	//������
	m_FieldVect[CF_CARDTYPE].unused=0;
	m_FieldVect[CF_CARDTYPE].offset = &UserInfo.ucCardType - (byte*)&UserInfo;
	m_FieldVect[CF_CARDTYPE].length = sizeof(UserInfo.ucCardType);
	m_FieldVect[CF_CARDTYPE].fid=0x16;
	m_FieldVect[CF_CARDTYPE].type=FT_INT8;
	//�Ա�
	m_FieldVect[CF_SEX].unused=0;
	m_FieldVect[CF_SEX].offset = &UserInfo.ucSex - (byte*)&UserInfo;
	m_FieldVect[CF_SEX].length = sizeof(UserInfo.ucSex);
	m_FieldVect[CF_SEX].fid=0x16;
	m_FieldVect[CF_SEX].type=FT_INT8;
	//����
	m_FieldVect[CF_NAME].unused=0;
	m_FieldVect[CF_NAME].offset = UserInfo.ucName - (byte*)&UserInfo;
	m_FieldVect[CF_NAME].length = sizeof(UserInfo.ucName);
	m_FieldVect[CF_NAME].fid=0x16;
	m_FieldVect[CF_NAME].type=FT_UCS2;
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

	//���������
	m_FieldVect[CF_TRANSDATE].unused=0;
	m_FieldVect[CF_TRANSDATE].offset = PrivateApp.ucLastTransDate - (byte*)&PrivateApp;
	m_FieldVect[CF_TRANSDATE].length = sizeof(PrivateApp.ucLastTransDate);
	m_FieldVect[CF_TRANSDATE].fid=0x1B;
	m_FieldVect[CF_TRANSDATE].type=FT_BCD;
	//���ۼ�����޶�
	m_FieldVect[CF_DAYMAXAMT].unused=0;
	m_FieldVect[CF_DAYMAXAMT].offset = PrivateApp.ucDayMaxAmt - (byte*)&PrivateApp;
	m_FieldVect[CF_DAYMAXAMT].length = sizeof(PrivateApp.ucDayMaxAmt);
	m_FieldVect[CF_DAYMAXAMT].fid=0x1B;
	m_FieldVect[CF_DAYMAXAMT].type=FT_INT24;
	//�����ۼ��޶�(ͬ���ۼ�����޶�)
	//m_FieldVect[CF_SINGLEMAXAMT].unused=0;
	//m_FieldVect[CF_SINGLEMAXAMT].offset = PrivateApp.ucDayMaxAmt - (byte*)&PrivateApp;
	//m_FieldVect[CF_SINGLEMAXAMT].length = sizeof(PrivateApp.ucDayMaxAmt);
	//m_FieldVect[CF_SINGLEMAXAMT].fid=0x1B;
	//m_FieldVect[CF_SINGLEMAXAMT].type=FT_INT24;
	//������
	m_FieldVect[CF_CARDPWD].unused=0;
	m_FieldVect[CF_CARDPWD].offset = PrivateApp.ucCardPwd - (byte*)&PrivateApp;
	m_FieldVect[CF_CARDPWD].length = sizeof(PrivateApp.ucCardPwd);
	m_FieldVect[CF_CARDPWD].fid=0x1B;
	m_FieldVect[CF_CARDPWD].type=FT_BCD;	
	//�ͻ����
	m_FieldVect[CF_CUSTTYPE].unused=0;
	m_FieldVect[CF_CUSTTYPE].offset = &PrivateApp.ucCustType - (byte*)&PrivateApp;
	m_FieldVect[CF_CUSTTYPE].length = sizeof(PrivateApp.ucCustType);
	m_FieldVect[CF_CUSTTYPE].fid=0x1B;
	m_FieldVect[CF_CUSTTYPE].type=FT_INT8;
	//�ͻ���
	m_FieldVect[CF_CUSTID].unused=0;
	m_FieldVect[CF_CUSTID].offset = PrivateApp.ucCustID - (byte*)&PrivateApp;
	m_FieldVect[CF_CUSTID].length = sizeof(PrivateApp.ucCustID);
	m_FieldVect[CF_CUSTID].fid=0x1B;
	m_FieldVect[CF_CUSTID].type=FT_INT32;
	//ѧ����
	m_FieldVect[CF_STUEMPNO].unused=0;
	m_FieldVect[CF_STUEMPNO].offset = PrivateApp.ucStuempNo - (byte*)&PrivateApp;
	m_FieldVect[CF_STUEMPNO].length = sizeof(PrivateApp.ucStuempNo);
	m_FieldVect[CF_STUEMPNO].fid=0x1B;
	m_FieldVect[CF_STUEMPNO].type=FT_ANSI;
	//У��
	m_FieldVect[CF_SCHOOLCODE].unused=0;
	m_FieldVect[CF_SCHOOLCODE].offset = &PrivateApp.ucSchoolCode - (byte*)&PrivateApp;
	m_FieldVect[CF_SCHOOLCODE].length = sizeof(PrivateApp.ucSchoolCode);
	m_FieldVect[CF_SCHOOLCODE].fid=0x1B;
	m_FieldVect[CF_SCHOOLCODE].type=FT_INT8;
	//���Ŵ���
	m_FieldVect[CF_DEPTCODE].unused=0;
	m_FieldVect[CF_DEPTCODE].offset = PrivateApp.ucDeptCode - (byte*)&PrivateApp;
	m_FieldVect[CF_DEPTCODE].length = sizeof(PrivateApp.ucDeptCode);
	m_FieldVect[CF_DEPTCODE].fid=0x1B;
	m_FieldVect[CF_DEPTCODE].type=FT_ANSI;

	//Ǯ���ļ�
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

	EFBUF efbuf;
	
	memset(efbuf.ReadBuf,0,sizeof(efbuf.ReadBuf));
	memset(efbuf.WriteBuf,0,sizeof(efbuf.WriteBuf));

	efbuf.FileSize=30;
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x15]=efbuf;

	efbuf.FileSize=55;
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x16]=efbuf;

	//efbuf.FileSize=10;
	//efbuf.ReadRight=FR_MAC;
	//m_EFMap[0x1A]=efbuf;

	efbuf.FileSize=64;
	efbuf.ReadRight=FRR_MAC;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x1B]=efbuf;
	//Ǯ��
	efbuf.FileSize=0;
	efbuf.ReadRight=FRR_NULL;
	efbuf.WriteRight=FRW_NULL;
	m_EFMap[MONEY_SFID]=efbuf;

}
CCardTypeMobile::~CCardTypeMobile()
{
}

int CCardTypeMobile::SelectADF()
{	
	return this->selectADFByName("D1560001018003800000000100001002");
}
int CCardTypeMobile::UpdateKey(const byte ucMainKey[16],byte ucKeyIndex,byte ucKey[16])
{
	int nRet=0;
	byte ucCmd[256]={0};
	byte ucCmdLen=0;
	byte ucOutBuf[128]={0};
	int  iOutLen=0;
	byte ucMac[4]={0};
	byte ucSessionKey[17]={0};
	byte ucRandom[9]={0};
	byte ucPlainKey[20]={0};

	memcpy(ucCmd,"\x84\xD4\x00\x00\x1C",5);
	ucPlainKey[0]=0x13;
	ucPlainKey[1]=ucKeyIndex;
	ucPlainKey[2]=0x01;
	ucPlainKey[3]=0x82;	
	memcpy(ucPlainKey+4,ucKey,16);

	nRet=GetRandomNum(ucRandom);
	if(nRet)
	{
		return nRet;
	}
	//�ȼ������ػỰ��Կ
	EncryptKey(ucMainKey,2,ucRandom,4,ucSessionKey,iOutLen);
	//�����ػỰ��Կ���ܴ���������
	EncryptKey(ucSessionKey,1,ucPlainKey,20,ucOutBuf,iOutLen);

	memcpy(ucCmd+5,ucOutBuf,iOutLen);
	ucCmdLen=iOutLen+5;
	//����mac����ʼ������Ϊȫ0
	memset(ucRandom,0,sizeof(ucRandom));
	CalcMac(ucRandom,ucSessionKey,1,ucCmd,ucCmdLen,ucMac);

	memcpy(ucCmd+ucCmdLen,ucMac,4);
	ucCmdLen+=4;

	byte ucRes[256]={0};
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.send_buf=ucCmd;
	cmd.recv_buf=ucRes;
	cmd.send_len=ucCmdLen;
	cmd.cmd_type=0;//16����
	
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
int CCardTypeMobile::InitUserCard(const char *sShowCardNo)
{
	int nRet=0;
	int iLen=0;
	//char sCardPhyID[17]={0};
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
	
	nRet=SelectADF();
	if(nRet)
	{
		return nRet;
	}
	//���жϸÿ��Ƿ��Ѿ���ʼ��������Ѿ���ʼ�����򲻸�����Կ
	//�жϷ���:�жϲ������κ��ֶ��Ƿ��Ѿ���0
	//
	byte ucData[128]={0};
	nRet=ReadBinaryFile(0x15,0x00,30,ucData);
	if(nRet)
	{
		return nRet;
	}
	/*
	if(0x02==ucData[9])
	{
		SET_ERR("�ÿ��Ѿ���ʼ��");
		return -1;
	}
	*/
	byte ucMainKey[16]={0};
	byte ucDiverKey[16]={0};

	memset(ucMainKey,0x00,16);	//������Կ
	//�޸�ά����Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DAMK,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x02,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	//�޸�������Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DPK1,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x03,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	//�޸ĳ�ֵ��Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DLK1,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x04,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	//�޸�TAC��Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DTAC,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x05,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	//�޸�PIN������Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DUK,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x06,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	//�޸�PIN��װ��Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DRPK,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x07,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	byte ucAnsiData[21]={0};
	byte ucUCS2Data[21]={0};
	strcpy((char*)ucAnsiData,"�ƶ�e��ͨ");
	EncodeUCS2((byte*)ucAnsiData,ucUCS2Data);
	nRet=UpdateBinaryFile(0x1A,0,10,ucUCS2Data);
	if(nRet)
	{
		return nRet;
	}
	memset(ucData,0,sizeof(ucData));
	//��ʼ��0x15
	ucData[8]=0x01;//Ӧ�����ͱ�ʶ
	ucData[9]=0x02;//Ӧ�ð汾��
	ucData[29]=0x06;//���з���ʶ
	nRet=UpdateBinaryFile(0x15,0,30,ucData);
	if(nRet)
	{
		return nRet;
	}
	//��ʼ��0x16
	memset(ucData,0,sizeof(ucData));
	nRet=UpdateBinaryFile(0x16,0,55,ucData);
	if(nRet)
	{
		return nRet;
	}
	//��ʼ��0x1B
	memset(ucData,0xFF,sizeof(ucData));
	memset(ucData,0x00,sizeof(ucData)-5);
	nRet=UpdateBinaryFile(0x1B,0,64,ucData);
	if(nRet)
	{
		return nRet;
	}
	//��ʱ����
	//�޸�������Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,ucDiverKey);
	nRet=UpdateKey(ucMainKey,0x01,ucDiverKey);
	if(nRet)
	{
		return nRet;
	}
	return 0;
}
//�ָ�������״̬
int CCardTypeMobile::RestoreFactorySettings()
{
	int nRet=0;
	int iLen=0;
	byte ucData[128]={0};
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

	nRet=SelectADF();
	if(nRet)
	{
		return nRet;
	}
	//���жϸÿ��Ƿ��Ѿ���ʼ��������Ѿ���ʼ�����򲻸�����Կ
	//�жϷ���:�жϲ������κ��ֶ��Ƿ��Ѿ���0
	//
	memset(ucData,0,sizeof(ucData));
	nRet=ReadBinaryFile(0x15,0x00,30,ucData);
	if(nRet)
	{
		return nRet;
	}
	if(0x02!=ucData[9])
	{
		SET_ERR("�ÿ�δ��ʼ��,���ܻ���");
		return -1;
	}
	//�������Ϣ
	memset(ucData,0xFF,sizeof(ucData));
	nRet=UpdateBinaryFile(0x1A,0,10,ucData);
	if(nRet)
	{
		return nRet;
	}
	//��ʼ��0x15
	memset(ucData,0xFF,sizeof(ucData));
	nRet=UpdateBinaryFile(0x15,0,30,ucData);
	if(nRet)
	{
		return nRet;
	}
	//��ʼ��0x16
	memset(ucData,0xFF,sizeof(ucData));
	nRet=UpdateBinaryFile(0x16,0,55,ucData);
	if(nRet)
	{
		return nRet;
	}
	//��ʼ��0x1B
	memset(ucData,0xFF,sizeof(ucData));
	nRet=UpdateBinaryFile(0x1B,0,64,ucData);
	if(nRet)
	{
		return nRet;
	}
	byte ucMainKey[16]={0};
	byte ucKey[16]={0};
	//����������Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,ucMainKey);
	
	memset(ucKey,0xFF,sizeof(ucKey));
	nRet=UpdateKey(ucMainKey,0x02,ucKey);
	if(nRet)
	{
		return nRet;
	}
	nRet=UpdateKey(ucMainKey,0x03,ucKey);
	if(nRet)
	{
		return nRet;
	}
	nRet=UpdateKey(ucMainKey,0x04,ucKey);
	if(nRet)
	{
		return nRet;
	}
	nRet=UpdateKey(ucMainKey,0x05,ucKey);
	if(nRet)
	{
		return nRet;
	}
	nRet=UpdateKey(ucMainKey,0x06,ucKey);
	if(nRet)
	{
		return nRet;
	}
	nRet=UpdateKey(ucMainKey,0x07,ucKey);
	if(nRet)
	{
		return nRet;
	}
	memset(ucKey,0x00,16);
	nRet=UpdateKey(ucMainKey,0x01,ucKey);
	if(nRet)
	{
		return nRet;
	}
	return 0;
}

int CCardTypeMobile::RequestCard(char* szCardPhyID)
{
	if(m_ReaderPara->cpuport == CARDSLOT_RF)
	{
		return CCardType::RequestCard(szCardPhyID);
	}
	else
	{
		char szCmd[30];
		unsigned char recv_data[30];
		unsigned char recv_len;
		int ret;
		ret = m_Reader->cpucard_poweron(m_ReaderPara,KS_CPUCARD,&recv_len,recv_data);
		if(ret)
		{
			return ret;
		}
		ks_cpu_cmd_t cmd;
		memset(&cmd,0,sizeof(cmd));
		strcpy(szCmd,"3097431800");
		cmd.send_buf=(byte*)szCmd;
		cmd.recv_buf=recv_data;
		cmd.send_len=strlen(szCmd);
		cmd.cmd_type=1;//16����

		ret = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
		if(ret)
		{
			return ret;
		}

		memset(&cmd,0,sizeof(cmd));
		strcpy(szCmd,"3011111108");
		cmd.send_buf=(byte*)szCmd;
		cmd.recv_buf=recv_data;
		cmd.send_len=strlen(szCmd);
		cmd.cmd_type=1;//16����

		ret = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
		if(ret)
		{
			return ret;
		}


		dec2hex(recv_data,8,m_szCardUID);
		m_szCardUID[16] = 0;
		if(szCardPhyID)
			strcpy(szCardPhyID,m_szCardUID);
		return 0;
	}
}
int CCardTypeMobile::WriteCard()
{
	int ret;
	std::set<int>::iterator iter = m_EFMap[m_FieldVect[CF_CUSTID].fid].WriteFieldSet.find(CF_CUSTID);
	if(iter != m_EFMap[m_FieldVect[CF_CUSTID].fid].WriteFieldSet.end())
	{
		// ��Ҫ��Ӧ�޸��ƶ��Ž��ļ��Ŀͻ��ţ�����
		ret = UpdateDoorCustId();
	}
	ret = CCardType::WriteCard();
	if(ret)
		return ret;
	return 0;
}
int CCardTypeMobile::CalcSafeMacWithKey(const unsigned char *key,const char* szCmdBuf,int szLen,char *szMac)
{
	char szBuf[256];
	byte uCmd[256];
	int nCmdLen;
	string sCmd,sMsg;
	byte uRandom[9]={0},uMac[9]={0};
	int nRet;
	nRet=GetRandomNum(uRandom);
	if(nRet)
	{
		return nRet;
	}
	memset(szBuf,0,sizeof(szBuf));

	byte uDAMK[32]={0};
	byte uCardDAMK[32]={0};
	byte uCardUID[9]={0};;
	int nKeyLen=0;
	hex2dec(szCmdBuf,szLen,uCmd,nCmdLen);
	memcpy(uCardDAMK,key,16);
	hex2dec(m_szCardUID,16,uCardUID,nKeyLen);
	//PbocDiverKey(uCardUID,uDAMK,uCardDAMK);
	CalcMac(uRandom,uCardDAMK,2,uCmd,nCmdLen,uMac);
	dec2hex(uMac,4,szMac);
	return 0;
}
int CCardTypeMobile::UpdateDoorCustId()
{
	byte ucCustId[4];
	EF_FIELD fld;
	int offset,length,ret,custId,i;
	char sCmd[256] = {0};
	byte ucResp[256] = {0};
	char szMac[20] = {0};
	byte ucMainKey[16] = {0};
	char custNoStr[256] = {0};
	ks_cpu_cmd_t cmd;

	fld = m_FieldVect[CF_CUSTID];
	length = fld.length;
	offset = fld.offset;
	memcpy(ucCustId,m_EFMap[fld.fid].WriteBuf+offset,length);
	custId = get_4byte_int(ucCustId);
	memset(custNoStr,0,sizeof custNoStr);
	sprintf(custNoStr,"%d",custId);
	length = strlen(custNoStr);
	memset(custNoStr+length,' ',20-length);
	

#if 0
	dec2hex(m_EFMap[fld.fid].WriteBuf,64,ucResp);
#else
	// ѡ���Ž�Ŀ¼
	
	ret = this->selectADFByName("D1560001018003800000000100001001");
	if(ret)
		return ret;
#endif

	// ���µ� CMD
	memset(sCmd,0,sizeof sCmd);
	sprintf(sCmd,"04D69A%02X%02X",24,20+4);
	cmd.send_len = strlen(sCmd);

	dec2hex((byte*)custNoStr,20,sCmd+cmd.send_len);
	cmd.send_len = strlen(sCmd);
	memset(ucMainKey,0xFF,sizeof ucMainKey);
	ret = this->CalcSafeMacWithKey(ucMainKey,sCmd,cmd.send_len,szMac);
	if(ret)
	{
		return ret;
	}
	strcat(sCmd,szMac);
	cmd.send_len = strlen(sCmd);
	cmd.cmd_type = 1;
	cmd.send_buf = (byte*)sCmd;
	cmd.recv_buf = ucResp;
	ret = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(ret)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return ret;
		}
	}
	return 0;
}
void CCardTypeMobile::GetSupportCardType(unsigned int cardTypes[],int &cnt)
{
	int i = 0;
	cardTypes[i++] = 0x0501;
	cardTypes[i++] = 0x0300;
	cardTypes[i++] = 0x0400;
	cnt = i;
}
int CCardTypeMobile::checkCardType(int ct)
{
	switch(ct)
	{
	case KS_SIMCARD:
		m_CardTypeCode = 0x0501;
		return 0;
	case KS_CPUCARD:
		m_CardTypeCode = 0x0400;
		return 0;
	default:
		return -1;
	}
}
