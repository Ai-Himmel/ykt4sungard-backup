#include "ks_dongguan_cardtype.h"
#include <assert.h>
#include "global_func.h"
#include "yktclt.h"

typedef struct 
{
byte issuer[2];
byte citycode[2];
byte industry[2];
byte rfu[2];
byte lockflag;
byte appver;
//byte intercode[2];
byte rfu2;
byte appid[9];
byte startdate[4];
byte expireddate[4];
byte cardmaintype;
byte cardmintype;
}PUBINFO;

typedef struct
{
byte cardverno[7];
byte cardid[4];
}CUSTDEFINFO;

typedef struct {
	byte ucCardCnt[2];		//���������
	byte ucLimit[3];		//͸֧�޶�
	byte ucTransAmt[4];		//���׽��
	byte ucTransType;		//��������
	byte ucTermID[6];		//�ն˱��
	byte ucTransDate[4];	//��������
	byte ucTransTime[3];	//����ʱ��
}TRANSDTL;
///////////////////////////////////////////////////////////
DGCardType::DGCardType():CCardType()
{
	this->set_cardtype_name("ks_dongguan_cardtype.dll");
	memset(m_appSerialNo,0,sizeof m_appSerialNo);
	this->m_sDefaultPin="1234";
}
DGCardType::~DGCardType()
{
}
int DGCardType::checkCardType(int ct)
{
	switch(ct)
	{
	case KS_CPUCARD:
	case KS_FIXCARD:
		return 0;
	default:
		return -1;
	}
}
int DGCardType::SelectADF ()
{
	return this->selectADFByName("A00000000386980701",1);
}
int DGCardType::InitUserCard (const char *sShowCardNo)
{
	return 0;
}
int DGCardType::RestoreFactorySettings ()
{
	return 0;
}
int DGCardType::InitCardTypeDLL()
{
	int ret;
	ret = CCardType::InitCardTypeDLL();
	if(ret)
		return ret;

	m_ReadFileLen = 128;
	m_WriteFileLen = 128;
	ret = initDef();
	if(ret)
		return ret;
	return 0;
}
int DGCardType::initDef()
{
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

	assert(sizeof(PUBINFO)==30);
	assert(sizeof(TRANSDTL)==23);
	assert(sizeof(CUSTDEFINFO)==11);

	PUBINFO PublicApp;
	TRANSDTL TransDtl;
	CUSTDEFINFO CustApp;

	///////////////////////////////////////////////////////////////
	// ������Ϣ�ļ� SFI = 0x15
	//���з���ʶ
	m_FieldVect[CF_PUBLISHID].unused=0;
	m_FieldVect[CF_PUBLISHID].offset = PublicApp.issuer - (byte*)&PublicApp;
	m_FieldVect[CF_PUBLISHID].length = sizeof(PublicApp.issuer);
	m_FieldVect[CF_PUBLISHID].fid=0x15;
	m_FieldVect[CF_PUBLISHID].type=FT_BCD;
	//���д���
	m_FieldVect[CF_CITYCODE].unused=0;
	m_FieldVect[CF_CITYCODE].offset = PublicApp.citycode - (byte*)&PublicApp;
	m_FieldVect[CF_CITYCODE].length = sizeof(PublicApp.citycode);
	m_FieldVect[CF_CITYCODE].fid=0x15;
	m_FieldVect[CF_CITYCODE].type=FT_BCD;
	//��ҵ����
	m_FieldVect[CF_INDUSTRYCODE].unused=0;
	m_FieldVect[CF_INDUSTRYCODE].offset = PublicApp.industry - (byte*)&PublicApp;
	m_FieldVect[CF_INDUSTRYCODE].length = sizeof(PublicApp.industry);
	m_FieldVect[CF_INDUSTRYCODE].fid=0x15;
	m_FieldVect[CF_INDUSTRYCODE].type=FT_BCD;
	//������־
	m_FieldVect[CF_CARDSTATUS].unused=0;
	m_FieldVect[CF_CARDSTATUS].offset = &PublicApp.lockflag - (byte*)&PublicApp;
	m_FieldVect[CF_CARDSTATUS].length = sizeof(PublicApp.lockflag);
	m_FieldVect[CF_CARDSTATUS].fid=0x15;
	m_FieldVect[CF_CARDSTATUS].type=FT_INT8;
	//Ӧ�����ͱ�ʶ
	m_FieldVect[CF_APPTYPE].unused=0;
	m_FieldVect[CF_APPTYPE].offset = &PublicApp.lockflag - (byte*)&PublicApp;
	m_FieldVect[CF_APPTYPE].length = sizeof(PublicApp.lockflag);
	m_FieldVect[CF_APPTYPE].fid=0x15;
	m_FieldVect[CF_APPTYPE].type=FT_BCD;
	//Ӧ�ð汾
	m_FieldVect[CF_CARDSTRUCTVER].unused=0;
	m_FieldVect[CF_CARDSTRUCTVER].offset = &PublicApp.appver - (byte*)&PublicApp;
	m_FieldVect[CF_CARDSTRUCTVER].length = sizeof(PublicApp.appver);
	m_FieldVect[CF_CARDSTRUCTVER].fid=0x15;
	m_FieldVect[CF_CARDSTRUCTVER].type=FT_BCD;
	//������ͨ��ʶ
	/*
	m_FieldVect[CF_INTERACTFLAG].unused=0;
	m_FieldVect[CF_INTERACTFLAG].offset = PublicApp.intercode - (byte*)&PublicApp;
	m_FieldVect[CF_INTERACTFLAG].length = sizeof(PublicApp.intercode);
	m_FieldVect[CF_INTERACTFLAG].fid=0x15;
	m_FieldVect[CF_INTERACTFLAG].type=FT_BCD;
	*/
	//Ӧ�����к�
	m_FieldVect[CF_APPSERIALNO].unused=0;
	m_FieldVect[CF_APPSERIALNO].offset = PublicApp.appid - (byte*)&PublicApp;
	m_FieldVect[CF_APPSERIALNO].length = sizeof(PublicApp.appid);
	m_FieldVect[CF_APPSERIALNO].fid=0x15;
	m_FieldVect[CF_APPSERIALNO].type=FT_HEX_STR;
	//��������
	m_FieldVect[CF_STARTDATE].unused=0;
	m_FieldVect[CF_STARTDATE].offset = PublicApp.startdate - (byte*)&PublicApp;
	m_FieldVect[CF_STARTDATE].length = sizeof(PublicApp.startdate);
	m_FieldVect[CF_STARTDATE].fid=0x15;
	m_FieldVect[CF_STARTDATE].type=FT_BCD;
	//��������
	m_FieldVect[CF_EXPIREDATE].unused=0;
	m_FieldVect[CF_EXPIREDATE].offset = PublicApp.expireddate - (byte*)&PublicApp;
	m_FieldVect[CF_EXPIREDATE].length = sizeof(PublicApp.expireddate);
	m_FieldVect[CF_EXPIREDATE].fid=0x15;
	m_FieldVect[CF_EXPIREDATE].type=FT_BCD;
	// �������
	m_FieldVect[CF_FEETYPE].unused=0;
	m_FieldVect[CF_FEETYPE].offset = &PublicApp.cardmaintype - (byte*)&PublicApp;
	m_FieldVect[CF_FEETYPE].length = sizeof(PublicApp.cardmaintype);
	m_FieldVect[CF_FEETYPE].fid=0x15;
	m_FieldVect[CF_FEETYPE].type=FT_INT8;
	// �������
	m_FieldVect[CF_SUBFEETYPE].unused=0;
	m_FieldVect[CF_SUBFEETYPE].offset = &PublicApp.cardmintype - (byte*)&PublicApp;
	m_FieldVect[CF_SUBFEETYPE].length = sizeof(PublicApp.cardmintype);
	m_FieldVect[CF_SUBFEETYPE].fid=0x15;
	m_FieldVect[CF_SUBFEETYPE].type=FT_INT8;

	/////////////////////////////////////////////////////////////////////
	// �汾��
	// �������汾��
	m_FieldVect[CF_CARDVERNO].unused=0;
	m_FieldVect[CF_CARDVERNO].offset = CustApp.cardverno - (byte*)&CustApp;
	m_FieldVect[CF_CARDVERNO].length = sizeof(CustApp.cardverno);
	m_FieldVect[CF_CARDVERNO].fid=0x16;
	m_FieldVect[CF_CARDVERNO].type=FT_BCD;
	// ����
	m_FieldVect[CF_CARDNO].unused=0;
	m_FieldVect[CF_CARDNO].offset = CustApp.cardid - (byte*)&CustApp;
	m_FieldVect[CF_CARDNO].length = sizeof(CustApp.cardid);
	m_FieldVect[CF_CARDNO].fid=0x16;
	m_FieldVect[CF_CARDNO].type=FT_INT32;
	//////////////////////////////////////////////////////////////////////
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

	efbuf.FileSize=sizeof(PUBINFO);
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x15]=efbuf;

	efbuf.FileSize=sizeof(CUSTDEFINFO);
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0x16]=efbuf;


	efbuf.FileSize=sizeof(TRANSDTL);
	efbuf.ReadRight=FRR_REC_FREE;
	efbuf.WriteRight=FRW_NULL;
	m_EFMap[0x18]=efbuf;

	//Ǯ��
	efbuf.FileSize=0;
	efbuf.ReadRight=FRR_NULL;
	efbuf.WriteRight=FRW_NULL;
	m_EFMap[MONEY_SFID]=efbuf;

	return 0;
	
}
void DGCardType::GetSupportCardType(unsigned int cardTypes[],int &cnt)
{
	int i = 0;
	cardTypes[i++] = 0x0103;
	cardTypes[i++] = 0x0302;
	cnt = i;
}
int DGCardType::readAppSerialNo()
{
	int nRet;
	unsigned char ucRespData[256] ={0},respLen = 0;
	if(strlen(m_appSerialNo)==0)
	{
		this->SetFieldReadMode(CF_APPSERIALNO);
		nRet = this->ReadCard();
		if(nRet)
		{
			SET_ERR("��Ӧ�����к�ʧ��");
			return -1;
		}
		//dec2hex(ucRespData+12,8,m_appSerialNo);
		char full_app_no[33]={0};
		this->GetFieldVal(CF_APPSERIALNO,full_app_no);
		memcpy(m_appSerialNo,full_app_no+2,16);
	}
	return 0;
}
int DGCardType::AddMoney(ST_TRANSPACK *transpack)
{
	char sPhyID[32]= {0};
	int nRet;
	if(readAppSerialNo())
	{
		//SET_ERR("δ��ȡ��Ӧ�����к�");
		return -1;
	}
	strcpy(sPhyID,transpack->sCardPhyID);
	strcpy(transpack->sCardPhyID,m_appSerialNo);
	nRet = CCardType::AddMoney(transpack);
	strcpy(transpack->sCardPhyID,sPhyID);
	return nRet;
}
int DGCardType::PayMoney(ST_TRANSPACK *payment)
{
	char sPhyID[32]= {0};
	int nRet;
	if(readAppSerialNo())
	{
		SET_ERR("δ��ȡ��Ӧ�����к�");
		return -1;
	}
	strcpy(sPhyID,payment->sCardPhyID);
	strcpy(payment->sCardPhyID,m_appSerialNo);
	nRet = CCardType::PayMoney(payment);
	strcpy(payment->sCardPhyID,sPhyID);
	return nRet;
}
int DGCardType::doSuccessRequestCard()
{
	int nRet;
	nRet = CCardType::doSuccessRequestCard();
	memset(m_appSerialNo,0,sizeof m_appSerialNo);
	if(nRet)
		return nRet;
	return readAppSerialNo();
	//return 0;
}
int DGCardType::CalcMacOnline(ST_TRANSPACK *transpack,char *sMac)
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
	/*
	��Ӧ�����к�	char(20)	scust_auth
	�ն�PSAM����	char(12)	sholder_ac_no
	�ն�PSAM����ˮ��	int	lserial0
	�ն˽�������	char(8)	sdate0
	�ն˽���ʱ��	char(6)	stime0
	����ֵǰ����	int	lvol1
	����ֵǰ���	int	lvol2
	��ֵ���	int	lvol0
	�������	char(8)	scust_auth2
	MAC1	char(8)	sholder_ac_no2
	*/
	clt.SetStringFieldByName("scust_auth",transpack->sCardPhyID);
	clt.SetStringFieldByName("sholder_ac_no",transpack->sTermno);
	clt.SetIntFieldByName("lserial0",transpack->nTermSeqno);
	clt.SetStringFieldByName("sdate0",transpack->sTransDate);
	clt.SetStringFieldByName("stime0",transpack->sTransTime);
	clt.SetIntFieldByName("lvol1",transpack->nDpsCardCnt);
	clt.SetIntFieldByName("lvol2",transpack->nBefBalance);
	clt.SetIntFieldByName("lvol0",transpack->nTransAmt);
	clt.SetStringFieldByName("scust_auth2",transpack->sRandom);
	clt.SetStringFieldByName("sholder_ac_no2",transpack->sMac);
	// ��ֵ��ȡ mac2
	if(!clt.SendRequest(10001,5000))
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
		GET_PACK_STR(clt,"scust_auth2",szMac);
		strcpy(sMac,szMac);
		GET_PACK_STR(clt,"sdate0",transpack->sTransDate);
		GET_PACK_STR(clt,"stime0",transpack->sTransTime);
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
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int KSAPI register_cardtype_op(ks_cardtype_base *&op)
{
	op = new DGCardType();
	return 0;
}
