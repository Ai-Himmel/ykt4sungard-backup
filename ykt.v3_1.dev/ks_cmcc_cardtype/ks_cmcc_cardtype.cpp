#include "ks_cmcc_cardtype.h"
#include "kscardtype.h"
#include "global_func.h"
#include "mystring.h"
#include "des.h"
#include "yktclt.h"
#include <assert.h>


typedef int (KSAPI *mf_register_cardtype_op)(ks_cardtype_base *&op);

mf_register_cardtype_op mf_reg_op = NULL;

#pragma pack(1)
typedef struct {
    byte blackver[7];
    byte cardstatus;
    byte password[3];
    byte maxpertime[3];
    byte maxperday[3];
    byte feetype;
    byte cardno[3];
    byte termid[6];
    byte txdate[3];
    byte txtime[3];
    byte custname[20];
    byte sex;
    byte txcnt[2];
    byte normallyopen;
    byte reserve[7];
} CUSTDEFINFO;

typedef struct {
    byte stuempno[20];
    byte custid[4];
    byte appindex;
    byte expireddate[4];
    byte apptype;
    byte lockflag;
    CUSTDEFINFO info;
} PUBINFO;

#pragma pack()

#define TEST_CARDTYPE(r) do { if(m_defaultCardType!=KS_FIXCARD) return (r); }while(0)
#define TEST_PARAMCARDTYPE() do { if(m_defaultCardType!=KS_MFCARD) return KS_NOTSUPPORT; }while(0)

ks_cmcc_cardtype::ks_cmcc_cardtype():loadKeyVer_(1),purchaseKeyVer_(1),
    m_childct(NULL),mf_cardtype_handle(NULL),enterpriceAppID_(0) {
    set_cardtype_name("ks_cmcc_cardtype.dll");
    memset(enterpriceCode_,0,sizeof enterpriceCode_);
    memset(strEnterpriceCode_,0,sizeof strEnterpriceCode_);
    memset(mfCardLibName_,0,sizeof mfCardLibName_);
    memset(appSerialNo_,0,sizeof appSerialNo_);
}
ks_cmcc_cardtype::~ks_cmcc_cardtype() {
    if(m_childct) {
        delete m_childct;
        m_childct = NULL;
    }
    if(mf_cardtype_handle) {
        FreeLibrary(mf_cardtype_handle);
        mf_cardtype_handle = NULL;
    }
}

void  ks_cmcc_cardtype::Attach(ks_device_op_t *device,ks_reader_dev_t *reader,READER_TYPE t) {
    CCardType::Attach(device,reader,t);
    if(m_childct)
        m_childct->Attach(m_Reader,m_ReaderPara,t);
}


int ks_cmcc_cardtype::SelectADF() {
    return this->selectADFByName("D1560001018000000000000100000000",1);
}
int ks_cmcc_cardtype::UpdateKey(const byte ucMainKey[16],byte ucKeyIndex,byte ucKey[16]) {
    int nRet=0;
    byte ucCmd[256]= {0};
    byte ucCmdLen=0;
    byte ucOutBuf[128]= {0};
    int  iOutLen=0;
    byte ucMac[4]= {0};
    byte ucSessionKey[17]= {0};
    byte ucRandom[9]= {0};
    byte ucPlainKey[20]= {0};

    memcpy(ucCmd,"\x84\xD4\x00\x00\x1C",5);
    ucPlainKey[0]=0x13;
    ucPlainKey[1]=ucKeyIndex;
    ucPlainKey[2]=0x01;
    ucPlainKey[3]=0x82;
    memcpy(ucPlainKey+4,ucKey,16);

    nRet=GetRandomNum(ucRandom);
    if(nRet) {
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

    byte ucRes[256]= {0};
    ks_cpu_cmd_t cmd;
    memset(&cmd,0,sizeof(cmd));
    cmd.send_buf=ucCmd;
    cmd.recv_buf=ucRes;
    cmd.send_len=ucCmdLen;
    cmd.cmd_type=0;//16����

    nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        if(cmd.cmd_retcode) {
            SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
            return cmd.cmd_retcode;
        } else {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    return 0;
}
int ks_cmcc_cardtype::createSubApp() {
    char szCmd[256];
    int datalen;
    datalen = 37 + 64 + 4;
    //sprintf(szCmd,"84500000%02X%s%s",datalen,strEnterpriceCode_,"00000000000000000000");
    return 0;
}
int ks_cmcc_cardtype::hasCreateSubApp(bool &create) {
    ks_cpu_cmd_t cmd;
    char szCmd[64];
    unsigned char uResp[256];
    int ret;
    sprintf(szCmd,"8052000007%s%02X",strEnterpriceCode_,enterpriceAppID_);

    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (unsigned char*)szCmd;
    cmd.send_len = strlen(szCmd);
    cmd.cmd_type = 1; // hex
    cmd.recv_buf = uResp;

    ret = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(ret) {
        create = false;
        if(cmd.cmd_retcode == 0x9317) {
            return 0;
        }
        return -1;
    }
    create = true;
    return 0;
}
int ks_cmcc_cardtype::InitUserCard(const char *sShowCardNo) {
    int nRet=0;
    int iLen=0;
    char sCardPhyID[17]= {0};
    char szData[256];
    byte uData[256];
    byte ucCardPhyID[9]= {0};

    //Ѱ��
    nRet=RequestCard();
    if(nRet) {
        return nRet;
    }
    if(strlen(m_szCardUID)==8)
        strcat(m_szCardUID,"80000000");
    if(strlen(m_szCardUID)!=16) {
        SET_ERR("������ID["<<m_szCardUID<<"]���ȴ���");
        return -1;
    }
    hex2dec(m_szCardUID,16,ucCardPhyID,iLen);

    nRet=SelectADF();
    if(nRet) {
        return nRet;
    }
    //���жϸÿ��Ƿ��Ѿ���ʼ��������Ѿ���ʼ�����򲻸�����Կ
    //
    bool hasCreate;
    nRet = hasCreateSubApp(hasCreate);
    if(nRet) {
        SET_ERR("��ȡ����Ӧ�ô���");
        return nRet;
    }

    if(hasCreate == false) {
        SET_ERR("��Ӧ��δ��������ȷ����Ƭ�Ѿ���ʼ��");
        return -1;
    }

    nRet = delSubApp();
    if(nRet) {
        SET_ERR("��ʼ������Ϣʧ�� "<<GetLastErrMsg(NULL));
        return -1;
    }
    if(m_defaultCardType==KS_FIXCARD) {
        nRet=m_childct->doSubRequestCard(NULL);
        if(nRet) {
            SET_ERR(m_childct->GetLastErrMsg(NULL));
            return nRet;
        }
        nRet=m_childct->InitUserCard(sShowCardNo);
        if(nRet) {
            SET_ERR(m_childct->GetLastErrMsg(NULL));
            return nRet;
        }
    }
    return 0;
}
//�ָ�������״̬
int ks_cmcc_cardtype::RestoreFactorySettings() {
    int nRet=0;
    int iLen=0;
    byte ucData[128]= {0};
    byte ucCardPhyID[9]= {0};

    //Ѱ��
    nRet=RequestCard();
    if(nRet) {
        return nRet;
    }
    if(strlen(m_szCardUID)==8)
        strcat(m_szCardUID,"80000000");
    if(strlen(m_szCardUID)!=16) {
        SET_ERR("������ID["<<m_szCardUID<<"]���ȴ���");
        return -1;
    }
    hex2dec(m_szCardUID,16,ucCardPhyID,iLen);

    nRet = delSubApp();
    if(nRet) {
        SET_ERR("��ʼ������Ϣʧ�� "<<GetLastErrMsg(NULL));
        return -1;
    }
    if(m_defaultCardType==KS_FIXCARD) {
        nRet=m_childct->doSubRequestCard(NULL);
        if(nRet) {
            SET_ERR(m_childct->GetLastErrMsg(NULL));
            return nRet;
        }
        nRet=m_childct->RestoreFactorySettings();
        if(nRet) {
            SET_ERR(m_childct->GetLastErrMsg(NULL));
            return nRet;
        }
    }
    return 0;

}
// �������ʹ�õ� MAC
int ks_cmcc_cardtype::CalcSafeMac4Sam(const char *szCmdbuf,char *szMac) {
    //return m_PSAMCardType->CalcSafeMac4Sam(this->strAppSerialNo_,sCardPhyID,szCmdbuf,szMac);
    return m_PSAMCardType->CalcSafeMac4Sam(this,szCmdbuf,szMac);
}
// delete sub_application
int ks_cmcc_cardtype::delSubApp() {
    char szData[64];
    int nRet;
    this->SetFieldVal(CF_STUEMPNO,"");
    this->SetFieldVal(CF_CARDNO,"0");
    this->SetFieldVal(CF_CARDVERNO,"00000000000000");
    this->SetFieldVal(CF_EXPIREDATE,"20000000");
    this->SetFieldVal(CF_CARDSTATUS,"1");
    this->SetFieldVal(CF_NAME,"");
    this->SetFieldVal(CF_SINGLEMAXAMT,"0");
    this->SetFieldVal(CF_DAYMAXAMT,"0");
    this->SetFieldVal(CF_SEX,"0");
    this->SetFieldVal(CF_FEETYPE,"0");
    this->SetFieldVal(CF_CUSTID,"0");
    this->SetFieldVal(CF_LOCKCARDCNT,"0");
    //
    this->SetFieldVal(CF_APPTYPE,"16"); // 0x10
    sprintf(szData,"%d",this->enterpriceAppID_);
    this->SetFieldVal(CF_APPID,szData);
    this->SetFieldVal(CF_APPLOCKFLAG,"0");

    nRet = CCardType::WriteCard();
    if(nRet) {
        SET_ERR(GetLastErrMsg(NULL));
        return nRet;
    }
    return 0;
}

int ks_cmcc_cardtype::DoRequestCard(char* szCardPhyID,KS_CARD_TYPE& t) {
    int nRet=0;
    memset(m_ErrMsg,0,sizeof(m_ErrMsg));
    memset(m_szCardUID,0,sizeof(m_szCardUID));
    nRet=m_Reader->request_card(m_ReaderPara,m_szCardUID,t);
    if(nRet) {
        SET_ERR("Ѱ������,"<<m_Reader->GetErrMsg(NULL)<<"ret:"<<nRet);
        return nRet;
    }
    if(szCardPhyID)
        strcpy(szCardPhyID,m_szCardUID);
    if(this->checkCardType(m_Reader->card_type())) {
        SET_ERR("Ѱ������,��֧�ָ��࿨!");
        t = (KS_CARD_TYPE)m_Reader->card_type();
        return 1;
    }
    this->m_defaultCardType = (KS_CARD_TYPE)m_Reader->card_type();
    t = m_defaultCardType;
    this->ClearAllFieldAllMode();
    return 0;
}
int ks_cmcc_cardtype::doRequestCard(char *szCardPhyID,KS_CARD_TYPE &t) {
    int ret;
    KS_CARD_TYPE ct;
    if(m_ReaderPara->cpuport == CARDSLOT_RF) {
        ct = KS_FIXCARD;
        ret = DoRequestCard(szCardPhyID,ct);
        if(ret) {
            return ret;
        }
    } else {
        char szCmd[30];
        unsigned char recv_data[30];
        unsigned char recv_len;
        ret = m_Reader->cpucard_poweron(m_ReaderPara,KS_CPUCARD,&recv_len,recv_data);
        if(ret) {
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
        if(ret) {
            return ret;
        }

        memset(&cmd,0,sizeof(cmd));
        strcpy(szCmd,"3011111108");
        cmd.send_buf=(byte*)szCmd;
        cmd.recv_buf=recv_data;
        cmd.send_len=strlen(szCmd);
        cmd.cmd_type=1;//16����

        ret = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
        if(ret) {
            return ret;
        }
        dec2hex(recv_data,8,m_szCardUID);
        m_szCardUID[16] = 0;
        if(szCardPhyID)
            strcpy(szCardPhyID,m_szCardUID);
        m_defaultCardType = KS_SIMCARD;
    }
    return ret;
}
int ks_cmcc_cardtype::doSuccessRequestCard() {
    if(m_defaultCardType == KS_CPUCARD || m_defaultCardType == KS_FIXCARD) {
        unsigned char recv_data[30];
        unsigned char recv_len;
        int ret;
        ret = m_Reader->cpucard_poweron(m_ReaderPara,m_defaultCardType,&recv_len,recv_data);
        if(ret) {
            return ret;
        }
    }
    return this->readCardInfo();
}
int ks_cmcc_cardtype::CalcSafeMacWithKey(const unsigned char *key,const char* szCmdBuf,int szLen,char *szMac) {
    char szBuf[256];
    byte uCmd[256];
    int nCmdLen;
    string sCmd,sMsg;
    byte uRandom[9]= {0},uMac[9]= {0};
    int nRet;
    nRet=GetRandomNum(uRandom);
    if(nRet) {
        return nRet;
    }
    memset(szBuf,0,sizeof(szBuf));

    byte uDAMK[32]= {0};
    byte uCardDAMK[32]= {0};
    byte uCardUID[9]= {0};;
    int nKeyLen=0;
    hex2dec(szCmdBuf,szLen,uCmd,nCmdLen);
    memcpy(uCardDAMK,key,16);
    hex2dec(m_szCardUID,16,uCardUID,nKeyLen);
    //PbocDiverKey(uCardUID,uDAMK,uCardDAMK);
    CalcMac(uRandom,uCardDAMK,2,uCmd,nCmdLen,uMac);
    dec2hex(uMac,4,szMac);
    return 0;
}
void ks_cmcc_cardtype::GetSupportCardType(unsigned int cardTypes[],int &cnt) {
    int i = 0;
    cardTypes[i++] = 0x0101;
    cardTypes[i++] = 0x0503;
    cardTypes[i++] = 0x0300;
    cardTypes[i++] = 0x0400;
    cnt = i;
}
int ks_cmcc_cardtype::checkCardType(int ct) {
    switch(ct) {
    case KS_MFCARD:
        m_CardTypeCode = 0x0200;
        return 0;
    case KS_SIMCARD:
        m_CardTypeCode = 0x0503;
        return 0;
    case KS_FIXCARD:
    case KS_CPUCARD:
        m_CardTypeCode = 0x0101;
        return 0;
    default:
        return -1;
    }
}
int ks_cmcc_cardtype::initDef() {
    EF_FIELD EField;
    memset(&EField,0,sizeof(EField));
    //�ȳ�ʼ��Ϊ0
    if(m_FieldVect.size())
        m_FieldVect.clear();
    if(m_EFMap.size())
        m_EFMap.clear();
    EField.unused=1;
    for(int i=0; i<=CF_END; i++)
        m_FieldVect.push_back(EField);

    assert(sizeof(CUSTDEFINFO)==64);
    assert(sizeof(PUBINFO)==31+64);

    PUBINFO PublicApp;

    // ��ҵID��
    /*
    m_FieldVect[CF_ENTERPRICECODE].unused=0;
    m_FieldVect[CF_ENTERPRICECODE].offset = PublicApp.enterpricecode - (byte*)&PublicApp;
    m_FieldVect[CF_ENTERPRICECODE].length = sizeof(PublicApp.enterpricecode);
    m_FieldVect[CF_ENTERPRICECODE].fid=this->enterpriceAppID_;
    m_FieldVect[CF_ENTERPRICECODE].type=FT_BCD;
    */

    //�������κ�
    m_FieldVect[CF_SUBSIDYNO].unused=1;
    m_FieldVect[CF_SUBSIDYNO].offset = 0;
    m_FieldVect[CF_SUBSIDYNO].length = 0;
    m_FieldVect[CF_SUBSIDYNO].fid=this->enterpriceAppID_;
    m_FieldVect[CF_SUBSIDYNO].type=FT_INT32;
    // �ͻ����
    m_FieldVect[CF_CUSTTYPE].unused=1;
    m_FieldVect[CF_CUSTTYPE].offset = 0;
    m_FieldVect[CF_CUSTTYPE].length = 0;
    m_FieldVect[CF_CUSTTYPE].fid=this->enterpriceAppID_;
    m_FieldVect[CF_CUSTTYPE].type=FT_INT8;
    // ֤������
    m_FieldVect[CF_IDTYPE].unused=1;
    m_FieldVect[CF_IDTYPE].offset = 0;
    m_FieldVect[CF_IDTYPE].length = 0;
    m_FieldVect[CF_IDTYPE].fid=this->enterpriceAppID_;
    m_FieldVect[CF_IDTYPE].type=FT_INT8;

    // �����
    m_FieldVect[CF_CARDTYPE].unused=1;
    m_FieldVect[CF_CARDTYPE].offset = 0;
    m_FieldVect[CF_CARDTYPE].length = 0;
    m_FieldVect[CF_CARDTYPE].fid=this->enterpriceAppID_;
    m_FieldVect[CF_CARDTYPE].type=FT_INT8;


    //ѧ����
    m_FieldVect[CF_STUEMPNO].unused=0;
    m_FieldVect[CF_STUEMPNO].offset = PublicApp.stuempno - (byte*)&PublicApp;
    m_FieldVect[CF_STUEMPNO].length = sizeof(PublicApp.stuempno);
    m_FieldVect[CF_STUEMPNO].fid=this->enterpriceAppID_;
    m_FieldVect[CF_STUEMPNO].type=FT_ANSI;
    //�ͻ���
    m_FieldVect[CF_CUSTID].unused=0;
    m_FieldVect[CF_CUSTID].offset = PublicApp.custid - (byte*)&PublicApp;
    m_FieldVect[CF_CUSTID].length = sizeof(PublicApp.custid);
    m_FieldVect[CF_CUSTID].fid=this->enterpriceAppID_;
    m_FieldVect[CF_CUSTID].type=FT_INT32;
    //��Ӧ��������
    m_FieldVect[CF_APPID].unused=0;
    m_FieldVect[CF_APPID].offset = &PublicApp.appindex - (byte*)&PublicApp;
    m_FieldVect[CF_APPID].length = sizeof(PublicApp.appindex);
    m_FieldVect[CF_APPID].fid=this->enterpriceAppID_;
    m_FieldVect[CF_APPID].type=FT_INT8;
    //��Ч��
    m_FieldVect[CF_EXPIREDATE].unused=0;
    m_FieldVect[CF_EXPIREDATE].offset = PublicApp.expireddate - (byte*)&PublicApp;
    m_FieldVect[CF_EXPIREDATE].length = sizeof(PublicApp.expireddate);
    m_FieldVect[CF_EXPIREDATE].fid=this->enterpriceAppID_;
    m_FieldVect[CF_EXPIREDATE].type=FT_BCD;
    //��Ӧ������
    m_FieldVect[CF_APPTYPE].unused=0;
    m_FieldVect[CF_APPTYPE].offset = &PublicApp.apptype - (byte*)&PublicApp;
    m_FieldVect[CF_APPTYPE].length = sizeof(PublicApp.apptype);
    m_FieldVect[CF_APPTYPE].fid=this->enterpriceAppID_;
    m_FieldVect[CF_APPTYPE].type=FT_INT8;
    //��Ӧ��������־
    m_FieldVect[CF_APPLOCKFLAG].unused=0;
    m_FieldVect[CF_APPLOCKFLAG].offset = &PublicApp.lockflag - (byte*)&PublicApp;
    m_FieldVect[CF_APPLOCKFLAG].length = sizeof(PublicApp.lockflag);
    m_FieldVect[CF_APPLOCKFLAG].fid=this->enterpriceAppID_;
    m_FieldVect[CF_APPLOCKFLAG].type=FT_INT8;
    //���汾��
    m_FieldVect[CF_CARDVERNO].unused=0;
    m_FieldVect[CF_CARDVERNO].offset = PublicApp.info.blackver - (byte*)&PublicApp;
    m_FieldVect[CF_CARDVERNO].length = sizeof(PublicApp.info.blackver);
    m_FieldVect[CF_CARDVERNO].fid=this->enterpriceAppID_;
    m_FieldVect[CF_CARDVERNO].type=FT_BCD_LPAD20;
    //��״̬
    m_FieldVect[CF_CARDSTATUS].unused=0;
    m_FieldVect[CF_CARDSTATUS].offset = &PublicApp.info.cardstatus - (byte*)&PublicApp;
    m_FieldVect[CF_CARDSTATUS].length = sizeof(PublicApp.info.cardstatus);
    m_FieldVect[CF_CARDSTATUS].fid=this->enterpriceAppID_;
    m_FieldVect[CF_CARDSTATUS].type=FT_INT8;

    //������
    m_FieldVect[CF_CARDPWD].unused=0;
    m_FieldVect[CF_CARDPWD].offset = PublicApp.info.password-(byte*)&PublicApp;
    m_FieldVect[CF_CARDPWD].length = sizeof(PublicApp.info.password);
    m_FieldVect[CF_CARDPWD].fid=this->enterpriceAppID_;
    m_FieldVect[CF_CARDPWD].type=FT_BCD;
    //���������޶�
    m_FieldVect[CF_SINGLEMAXAMT].unused=0;
    m_FieldVect[CF_SINGLEMAXAMT].offset = PublicApp.info.maxpertime-(byte*)&PublicApp;
    m_FieldVect[CF_SINGLEMAXAMT].length = sizeof(PublicApp.info.maxpertime);
    m_FieldVect[CF_SINGLEMAXAMT].fid=this->enterpriceAppID_;
    m_FieldVect[CF_SINGLEMAXAMT].type=FT_INT24;
    //���ۼ������޶�
    m_FieldVect[CF_DAYMAXAMT].unused=0;
    m_FieldVect[CF_DAYMAXAMT].offset = PublicApp.info.maxperday-(byte*)&PublicApp;
    m_FieldVect[CF_DAYMAXAMT].length = sizeof(PublicApp.info.maxperday);
    m_FieldVect[CF_DAYMAXAMT].fid=this->enterpriceAppID_;
    m_FieldVect[CF_DAYMAXAMT].type=FT_INT24;
    //�շ����
    m_FieldVect[CF_FEETYPE].unused=0;
    m_FieldVect[CF_FEETYPE].offset = &PublicApp.info.feetype - (byte*)&PublicApp;
    m_FieldVect[CF_FEETYPE].length = sizeof(PublicApp.info.feetype);
    m_FieldVect[CF_FEETYPE].fid=this->enterpriceAppID_;
    m_FieldVect[CF_FEETYPE].type=FT_INT8;
    //���׿���
    m_FieldVect[CF_CARDNO].unused=0;
    m_FieldVect[CF_CARDNO].offset = PublicApp.info.cardno - (byte*)&PublicApp;
    m_FieldVect[CF_CARDNO].length = sizeof(PublicApp.info.cardno);
    m_FieldVect[CF_CARDNO].fid=this->enterpriceAppID_;
    m_FieldVect[CF_CARDNO].type=FT_INT24;
    //�����ն˺�
    m_FieldVect[CF_LOCKTERMID].unused=0;
    m_FieldVect[CF_LOCKTERMID].offset = PublicApp.info.termid-(byte*)&PublicApp;
    m_FieldVect[CF_LOCKTERMID].length = sizeof(PublicApp.info.termid);
    m_FieldVect[CF_LOCKTERMID].fid=this->enterpriceAppID_;
    m_FieldVect[CF_LOCKTERMID].type=FT_BCD;
    // ��������ʱ��
    m_FieldVect[CF_LOCKTRANSDATE].unused=0;
    m_FieldVect[CF_LOCKTRANSDATE].offset = PublicApp.info.txdate-(byte*)&PublicApp;
    m_FieldVect[CF_LOCKTRANSDATE].length = sizeof(PublicApp.info.txdate);
    m_FieldVect[CF_LOCKTRANSDATE].fid=this->enterpriceAppID_;
    m_FieldVect[CF_LOCKTRANSDATE].type=FT_BCD;

    m_FieldVect[CF_LOCKTRANSTIME].unused=0;
    m_FieldVect[CF_LOCKTRANSTIME].offset = PublicApp.info.txtime-(byte*)&PublicApp;
    m_FieldVect[CF_LOCKTRANSTIME].length = sizeof(PublicApp.info.txtime);
    m_FieldVect[CF_LOCKTRANSTIME].fid=this->enterpriceAppID_;
    m_FieldVect[CF_LOCKTRANSTIME].type=FT_BCD;
    //����
    m_FieldVect[CF_NAME].unused=0;
    m_FieldVect[CF_NAME].offset = PublicApp.info.custname-(byte*)&PublicApp;
    m_FieldVect[CF_NAME].length = sizeof(PublicApp.info.custname);
    m_FieldVect[CF_NAME].fid=this->enterpriceAppID_;
    m_FieldVect[CF_NAME].type=FT_ANSI;
    // �Ա�
    m_FieldVect[CF_SEX].unused=0;
    m_FieldVect[CF_SEX].offset = &PublicApp.info.sex-(byte*)&PublicApp;
    m_FieldVect[CF_SEX].length = sizeof(PublicApp.info.sex);
    m_FieldVect[CF_SEX].fid=this->enterpriceAppID_;
    m_FieldVect[CF_SEX].type=FT_INT8;
    // �������״���
    m_FieldVect[CF_LOCKCARDCNT].unused=0;
    m_FieldVect[CF_LOCKCARDCNT].offset = PublicApp.info.txcnt-(byte*)&PublicApp;
    m_FieldVect[CF_LOCKCARDCNT].length = sizeof(PublicApp.info.txcnt);
    m_FieldVect[CF_LOCKCARDCNT].fid=this->enterpriceAppID_;
    m_FieldVect[CF_LOCKCARDCNT].type=FT_INT16;

    // ��������־
    m_FieldVect[CF_NORMALLYOPEN].unused=0;
    m_FieldVect[CF_NORMALLYOPEN].offset = &(PublicApp.info.normallyopen)-(byte*)&PublicApp;
    m_FieldVect[CF_NORMALLYOPEN].length = sizeof(PublicApp.info.normallyopen);
    m_FieldVect[CF_NORMALLYOPEN].fid=this->enterpriceAppID_;
    m_FieldVect[CF_NORMALLYOPEN].type=FT_INT8;


    ///////////////////////////////////////////////////////////////
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

    //////////////////////////////////////////////////////////
    EFBUF efbuf;

    memset(efbuf.ReadBuf,0,sizeof(efbuf.ReadBuf));
    memset(efbuf.WriteBuf,0,sizeof(efbuf.WriteBuf));

    efbuf.FileSize=sizeof(PUBINFO);
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_ENCRYPT_MAC;
    m_EFMap[this->enterpriceAppID_]=efbuf;

    //Ǯ��
    efbuf.FileSize=0;
    efbuf.ReadRight=FRR_NULL;
    efbuf.WriteRight=FRW_NULL;
    m_EFMap[MONEY_SFID]=efbuf;

    return 0;
}
int ks_cmcc_cardtype::InitCardTypeDLL() {
    char param[512];
    int paramLen,ret;
    paramLen = sizeof(param) - 1;
    memset(param,0,sizeof param);

    ret = CCardType::InitCardTypeDLL();
    if(ret) {
        SET_ERR("��ʼ�������Ϳ�ʧ��");
        return -1;
    }
    memset(param,0,sizeof param);
    if(m_license->get_public_param("kscardlib.cmcc.mfcardlib",param,paramLen)) {
        strcpy(mfCardLibName_,"ks_mfcard.dll");
    } else {
        strcpy(mfCardLibName_,param);
    }
    ret = load_mfcard_type();
    if(ret) {
        SET_ERR("����M1��ʧ��");
        return -1;
    }
    memset(param,0,sizeof param);
    if(m_license->get_public_param("kscardlib.cmcc.enterpricecode",param,paramLen)) {
        SET_ERR("δ������ҵID");
        return -1;
    }
    if(strlen(param) != 12) {
        SET_ERR("��ҵID�ų��Ȳ���ȷ");
        return -1;
    }
    strcpy(strEnterpriceCode_,param);
    hex2dec(param,12,enterpriceCode_,ret);
    m_license->get_public_int_param("kscardlib.cmcc.enterprice.appid",&enterpriceAppID_);

    if(enterpriceAppID_< 1 ) { //|| enterpriceAppID_ > 0x1F)
        SET_ERR("��ҵ�Զ�����Ӧ��ID�Ŵ���");
        return -1;
    }
    m_ReadFileLen = 128;
    m_WriteFileLen = 128;
    ret = initDef();
    if(ret)
        return ret;

    assert(m_childct != NULL);
    m_childct->set_license(this->m_license);
    m_childct->SetPSAMCardType(this->GetPSAMCardType());
    return m_childct->InitCardTypeDLL();
}

int ks_cmcc_cardtype::CalcMacOnline(ST_TRANSPACK *transpack,char *sMac) {
    int nRet=0,nLen=0;
    int nSendLen=0;
    unsigned char ucRespLen=0;

    unsigned char nRespLen=0;
    char szMac[9]= {0};
    //���

    if(strlen(transpack->sTermno)!=12) {
        SET_ERR("�ն˱�ų��ȴ���");
        //DEBUG_LOG(("�ն˱��[%s]���ȴ���",transpack->sTermno));
        return -1;
    }
    if(strlen(transpack->sTransDate)!=8) {
        SET_ERR("�������ڳ��ȴ���");
        //DEBUG_LOG(("��������[%s]���ȴ���",transpack->sTransDate));
        return -1;
    }
    if(strlen(transpack->sTransTime)!=6) {
        SET_ERR("����ʱ�䳤�ȴ���");
        //DEBUG_LOG(("����ʱ��[%s]���ȴ���",transpack->sTransDate));
        return -1;
    }
    if(transpack->nTransAmt==0) {
        SET_ERR("���׽���Ϊ0");
        //DEBUG_LOG((ks_geterrmsg(NULL)));
        return -1;

    }
    if(!KS_YKT_Clt::IsInitialized()) {
        SET_ERR("ϵͳδ��ʼ��");
        return -1;
    }
    KS_YKT_Clt clt;
    clt.SetIntFieldByName("lsafe_level",transpack->nTransType); 	// ��������
    clt.SetIntFieldByName("lvol0",transpack->nCardNo); 				// ���׿���
    clt.SetStringFieldByName("sstation1",this->m_appSerialNo); 	// Ӧ�����к�
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
    clt.SetIntFieldByName("lvol5",1); // �ƶ��淶
    clt.SetStringFieldByName("sstock_code2",sMac); // �ƶ��淶
    // ��ֵ��ȡ mac2
    if(!clt.SendRequest(846313,5000)) {
        // TODO : �����ǳ�ʱ
        char szMsg[256]= {0};
        char errmsg[256]= {0};
        //sprintf("������(ip:%s,drtp port:%d,funcno:%d)ͨѶ��ʱ)",clt.)
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"������ͨѶ����:%s,������:%d",szMsg,clt.GetReturnCode());
        SET_ERR(errmsg);
        return -1;
    }
    if((nRet = clt.GetReturnCode())!=0) {
        // ��ֵʧ��
        clt.GetReturnMsg(transpack->sErrMsg);
        SET_ERR(transpack->sErrMsg);
        //DEBUG_LOG(("����ʧ�ܴ�����[%d]������Ϣ[%s]",nRet,transpack->sErrMsg));
        return nRet;
    }
    if(clt.HasMoreRecord()) {
        clt.GetNextPackage();
        GET_PACK_STR(clt,"sstock_code2",szMac);
        strcpy(sMac,szMac);
    } else {
        SET_ERR("��������������");
        return -1;
    }
    return 0;
}
int ks_cmcc_cardtype::AddMoney(ST_TRANSPACK *deposit) {
    string sCmd;
    int nRet=0,nLen=0;
    char sHexStr[256]= {0};
    unsigned char ucRespData[256];
    int nSendLen=0;
    unsigned char ucRespLen=0;
    char termno[13]= {0};
    unsigned char sMac1[9]= {0};

    memset(ucRespData,0,sizeof(ucRespData));
    ks_cpu_cmd_t cmd;
    memset(&cmd,0,sizeof(cmd));
    cmd.recv_buf=ucRespData;


    sCmd="807400021A";
    sCmd += this->strEnterpriceCode_;
    sCmd += "03010001000000000001";
    //���׽��
    //�ն˺�
    byte ucTransAmt[5]= {0};
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
    if(nRet) {
        deposit->cRetryFlag=1;
        if(cmd.cmd_retcode) {
            SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
            return cmd.cmd_retcode;
        } else {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    char sMac2[9]= {0};

    memset(sMac2,0,sizeof sMac2);
    //�����
    int nBefBal=get_4byte_int(ucRespData);
    //���Ѵ���
    int nDptCnt=get_2byte_int(ucRespData+8);
    //ȡ�����
    dec2hex(ucRespData+12,4,deposit->sRandom);
    // MAC1
    dec2hex(ucRespData+16,4,sMac2);

    //��ֵ����
    deposit->nDpsCardCnt=nDptCnt;

    if(nBefBal != deposit->nBefBalance) {
        if(nBefBal == deposit->nAftBalance) {
            // ��Ϊ�Ѿ���Ǯ�ɹ���
            return 0;
        }
        SET_ERR("����ǰ����뿨�в�һ��");
        return -1;
    }
#if 1 && defined(_DEBUG)
    nRet = CalcDepositMac4Sam(deposit,sMac2);
    if(nRet) {
        deposit->cRetryFlag=1;
        //DEBUG_LOG(("����MAC2ʧ�� ret=%X",nRet));
        return nRet;
    }
#else
    nRet=CalcMacOnline(deposit,sMac2);
    if(nRet) {
        deposit->cRetryFlag=1;
        //DEBUG_LOG(("����MAC2ʧ�� ret=%X",nRet));
        return nRet;
    }
#endif

    // ����д������
    memset(ucRespData,0,sizeof ucRespData);
    sCmd="8476000012";
    sCmd+= this->strEnterpriceCode_;
    sCmd+="03";
    sCmd.append(deposit->sTransDate,8);
    sCmd.append(deposit->sTransTime,6);
    sCmd.append(sMac2,8);

    cmd.send_buf=(byte*)sCmd.c_str();
    cmd.send_len=sCmd.size();
    cmd.cmd_type=1;//16����
    nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        deposit->cRetryFlag=1;
        deposit->cGetProveFlag=1;
        if(cmd.cmd_retcode) {
            SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
            return cmd.cmd_retcode;
        } else {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    return 0;
}

int ks_cmcc_cardtype::PayMoney(ST_TRANSPACK *payment) {
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
    char sMac1[9]= {0};
    char temp[256]= {0};

    sCmd="807C010212";
    sCmd+=this->strEnterpriceCode_;
    sCmd+="0301";
    //���׽��
    byte ucTransAmt[5]= {0};
    memset(sHexStr,0,sizeof(sHexStr));
    lpad(payment->sTermno,12,'0');
    set_4byte_int(ucTransAmt,payment->nTransAmt);
    dec2hex(ucTransAmt,4,sHexStr);
    sCmd+=sHexStr;
    sCmd+=payment->sTermno;

    //�����ĳ���
    memset(ucRespData, 0,sizeof(ucRespData));
    cmd.send_buf=(byte*)sCmd.c_str();
    cmd.send_len=sCmd.size();
    cmd.cmd_type=1;//16����
    nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        payment->cRetryFlag=1;
        if(cmd.cmd_retcode) {
            SET_ERR("���ѳ�ʼ��ʧ��type["<<m_defaultCardType<<"] "<<GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
            return cmd.cmd_retcode;
        } else {
            SET_ERR("���ѳ�ʼ��ʧ��type["<<m_defaultCardType<<"] "<<m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    //�����
    int nBefBal=get_4byte_int(ucRespData+24);
    //���Ѵ���
    int nPayCnt=get_2byte_int(ucRespData+32);
    //ȡ�����
    dec2hex(ucRespData+39,4,payment->sRandom);

    /*
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
    */
    payment->nPayCardCnt=nPayCnt;
    payment->nTransType = TRNS_TYPE_PURCHASE;

    byte sDate[20],sTime[20];
    memset(sDate,0,sizeof sDate);
    memset(sTime,0,sizeof sTime);

    strcpy(payment->sCardPhyID,this->m_appSerialNo);
    nRet = m_PSAMCardType->CalcTransMac4Sam(payment,sMac1);
    strcpy(payment->sCardPhyID,this->m_szCardUID);
    if(nRet) {
        payment->cRetryFlag=1;
        return nRet;
    }
    // ����д������

    memset(ucRespData,0,sizeof(ucRespData));
    // debit for purchase
    sCmd="847E010016";
    sCmd+=this->strEnterpriceCode_;
    sCmd+="03";
    // term seqno
    byte ucTermSeqno[5]= {0};
    set_4byte_int(ucTermSeqno,payment->nTermSeqno);
    dec2hex(ucTermSeqno,4,sHexStr);
    sHexStr[8]=0;
    sCmd+=sHexStr;
    // tx date time
    sCmd.append(payment->sTransDate,8);
    sCmd.append(payment->sTransTime,6);
    // mac1
    //sMac1[0] = 'F';
    sCmd += sMac1;
    if(strlen(sMac1) != 8) {
        SET_ERR("����MAC���ȴ���");
    }
    memset(ucRespData, 0,sizeof(ucRespData));
    cmd.send_buf=(byte*)sCmd.c_str();
    cmd.send_len=sCmd.size();
    cmd.cmd_type=1;//16����
    nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        payment->cRetryFlag=1;
        payment->cGetProveFlag=1;
        if(cmd.cmd_retcode) {
            SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
            return cmd.cmd_retcode;
        } else {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    payment->nErrCode = 0;
    return 0;
}

// ����һ����Կ����MAC
// ��ɢΪ2����ɢ
int ks_cmcc_cardtype::CalcMacData(unsigned char *key,unsigned char *seed3rd,
                                  char *data,char *mac) {
    char szData[256];
    unsigned char uData[256];
    unsigned char uCardKey[16];
    unsigned char cipher_data[16],xor_data[16];
    des_context dctx;
    int len,i,j;

    memset(uCardKey,0,sizeof uCardKey);

    //1 ��
    sprintf(szData,"03%02X800000000000",this->loadKeyVer_);
    hex2dec(szData,16,uData,len);
    this->PbocDiverKey(uData,key,uCardKey);

    // 2 ��
    // Ӧ�����кţ�3-16������Կ�汾
    sprintf(szData,"%s%02X",this->m_appSerialNo+2,this->loadKeyVer_);
    hex2dec(szData,16,uData,len);
    this->PbocDiverKey(uData,uCardKey,uCardKey);

    // 3 ��, ������Կ
    this->PbocDiverKey(seed3rd,uCardKey,uCardKey);

    // calc mac
    // ����MAC

    len = strlen(data);
    hex2dec(data,len,uData,len);
    memset(cipher_data,0,sizeof cipher_data);
    len /= 8;
    for(i = 0; i < len; ++i) {
        for(j = 0; j < 8; ++j) {
            xor_data[j] = cipher_data[j] ^ uData[i*8+j];
        }
        memset(&dctx,0,sizeof dctx);
        des_set_key(&dctx,uCardKey);
        des_encrypt(&dctx,xor_data,cipher_data);
    }
    des_set_key(&dctx,uCardKey+8);
    des_decrypt(&dctx,cipher_data,xor_data);
    des_set_key(&dctx,uCardKey);
    des_encrypt(&dctx,xor_data,cipher_data);
    dec2hex(cipher_data,4,mac);
    return 0;
}
int ks_cmcc_cardtype::CompareMac1(unsigned char *key,ST_TRANSPACK *transpack,char *sMac1) {
    byte sk[16];
    byte cipher_data[8];
    byte xor_data[8];
    des_context dctx;
    des3_context d3ctx;
    char szData[256];
    byte uData[256];
    char sMac2[9];
    int len,i,j;

    memset(szData,0,sizeof szData);

    //strcpy(transpack->sRandom,"3AB706D1");
    // ��������
    sprintf(szData,"%s%04X8000",transpack->sRandom,transpack->nDpsCardCnt);
    hex2dec(szData,strlen(szData),uData,len);
    // ���������Կ
    /*
    memset(&d3ctx,0,sizeof d3ctx);
    des3_set_2keys(&d3ctx,key,key+8);
    memset(sk,0,sizeof sk);
    des3_encrypt(&d3ctx,uData,sk);
    */
    memset(sk,0,sizeof sk);
    this->PbocDiverKey(uData,key,sk);

    // ����MAC
    sprintf(szData,"%08X%08X02%s80",transpack->nBefBalance,transpack->nTransAmt,transpack->sTermno);
    memset(uData,0,sizeof uData);
    hex2dec(szData,strlen(szData),uData,len);

    memset(cipher_data,0,sizeof cipher_data);
    len /= 8;
    for(i = 0; i < len; ++i) {
        for(j = 0; j < 8; ++j) {
            xor_data[j] = cipher_data[j] ^ uData[i*8+j];
        }
        memset(&dctx,0,sizeof dctx);
        des_set_key(&dctx,sk);
        des_encrypt(&dctx,xor_data,cipher_data);
    }
    des_set_key(&dctx,sk+8);
    des_decrypt(&dctx,cipher_data,xor_data);
    des_set_key(&dctx,sk);
    des_encrypt(&dctx,xor_data,cipher_data);

    memset(sMac2,0,sizeof sMac2);
    dec2hex(cipher_data,4,sMac2);
    if(strcmp(sMac1,sMac2)==0)
        return 0;

    return -1;

}
int ks_cmcc_cardtype::CalcDepositMac4Sam(ST_TRANSPACK *transpack,char *sMac) {
    char szData[256];
    byte uData[256];
    byte seedKey[16];
    char termno[20];
    char sMac1[9];
    int len;

    //byte loadKey[] = "\x93\xE2\xBA\x07\x60\x15\x96\x38\x9D\xA3\xD7\x36\xB9\xDA\x0B\x13";
    char szLoadKey[]="ef2f1b5ba85f1ce046ea54b3f2718e47";
    byte loadKey[16];

    hex2dec(szLoadKey,32,loadKey,len);

    //strcpy(transpack->sRandom,"3AB706D1");
    sprintf(szData,"%s%04X8000",transpack->sRandom,transpack->nDpsCardCnt);
    hex2dec(szData,strlen(szData),seedKey,len);

    // У��MAC1
    sprintf(szData,"%08X%08X02%s80",transpack->nBefBalance,transpack->nTransAmt,transpack->sTermno);

    CalcMacData(loadKey,seedKey,szData,sMac1);

    if(strcmp(sMac1,sMac)) {
        SET_ERR("У��MAC1����ȷ");
        return -1;
    }

    // ����MAC2
    sprintf(termno,"%s",transpack->sTermno);
    sprintf(szData,"%08X02%s%s%s800000000000",transpack->nTransAmt,termno,
            transpack->sTransDate,transpack->sTransTime);

    CalcMacData(loadKey,seedKey,szData,sMac);

    return 0;
}
int ks_cmcc_cardtype::readCardInfo() {
    int nRet;
    char szCmd[64];
    unsigned char uResp[256];
    ks_cpu_cmd_t cmd;

    nRet = this->SelectADF();
    if(nRet) {
        return nRet;
    }
    sprintf(szCmd,"00B09500");
    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (unsigned char*)szCmd;
    cmd.send_len = strlen(szCmd);
    cmd.recv_buf = uResp;
    cmd.cmd_type = 1;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        SET_ERR("��ȡ��Ӧ�����к�ʧ��");
        return nRet;
    }
    memcpy(this->appSerialNo_,uResp+10,8);
    dec2hex(this->appSerialNo_,8,this->m_appSerialNo);
    return 0;
}
int ks_cmcc_cardtype::ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData) {
    char szData[256];
    byte uData[256];
    ks_cpu_cmd_t cmd;
    int nRet;

    sprintf(szData,"805C000007%s%02X",this->strEnterpriceCode_,ucSFI);

    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (unsigned char *)szData;
    cmd.send_len = strlen(szData);
    cmd.recv_buf = uData;
    cmd.cmd_type = 1;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
        return cmd.cmd_retcode;
    }
    // ȥ����ҵID��
    memcpy(ucData,uData+6,cmd.recv_len-6-2);
    return 0;
}

int ks_cmcc_cardtype::GetDpsCnt() {
    std::string sCmd;
    unsigned char ucRespData[256];
    ks_cpu_cmd_t cmd;
    int nRet;

    sCmd="807400021A";
    sCmd += this->strEnterpriceCode_;
    sCmd += "03010001000000000001";
    //���׽��
    //�ն˺�
    sCmd += "00000001000000000000";
    //�����ĳ���
    cmd.send_buf=(byte*)sCmd.c_str();
    cmd.send_len=sCmd.size();
    cmd.recv_buf = ucRespData;
    cmd.cmd_type=1;//16����
    nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        if(cmd.cmd_retcode) {
            SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
            return cmd.cmd_retcode;
        } else {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    //�����
    m_CardBal = get_4byte_int(ucRespData);
    //���Ѵ���
    m_DpsCnt = get_2byte_int(ucRespData+8);
    return 0;
}

int ks_cmcc_cardtype::GetPayCnt() {
    std::string sCmd;
    unsigned char ucRespData[256];
    ks_cpu_cmd_t cmd;
    int nRet;

    sCmd="807C010212";
    sCmd += this->strEnterpriceCode_;
    sCmd += "030100000000000000000000";
    //�����ĳ���
    cmd.send_buf=(byte*)sCmd.c_str();
    cmd.send_len=sCmd.size();
    cmd.recv_buf = ucRespData;
    cmd.cmd_type=1;//16����
    nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        if(cmd.cmd_retcode) {
            SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
            return cmd.cmd_retcode;
        } else {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    //�����
    m_CardBal = get_4byte_int(ucRespData+24);
    //���Ѵ���
    m_PayCnt = get_2byte_int(ucRespData+32);
    return 0;
}
int ks_cmcc_cardtype::InitForTrans(ST_TRANSPACK *trans,int trans_type) {
    int nRet;
    std::string sCmd;
    char sHexStr[256]="";
    int  nSendDataHexLen=0;
    unsigned char ucSendData[256]="";
    int  nSendDataLen=0;
    unsigned char ucRespData[256];
    unsigned char ucRespLen=0;
    char sRandom[30];
    char temp[256]= {0};
    char sMac1[20] = {0};

    if(trans_type == TRNS_TYPE_PURCHASE) {

        sCmd="807C010212";
        sCmd += this->strEnterpriceCode_;
        sCmd += "0301";
        //���׽��
        byte ucTransAmt[5]= {0};
        memset(sHexStr,0,sizeof(sHexStr));
        lpad(trans->sTermno,12,'0');
        set_4byte_int(ucTransAmt,trans->nTransAmt);
        dec2hex(ucTransAmt,4,sHexStr);
        sCmd+=sHexStr;
        sCmd+=trans->sTermno;
        //�ն˺�
        //�����ĳ���
        memset(ucRespData, 0,sizeof ucRespData);
        if( (nRet=Adpu4Hex((char*)sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 ) {
            SET_ERR("���ѳ�ʼ��ʧ��"<<nRet);
            return nRet;
        }
        dec2hex(ucRespData,ucRespLen+2,temp);
        //�����
        int nBefBal=get_4byte_int(ucRespData+24);
        //���Ѵ���
        int nPayCnt=get_2byte_int(ucRespData+32);
        if(nBefBal != trans->nBefBalance) {
            if(nBefBal + trans->nTransAmt == trans->nBefBalance) {
                if(nPayCnt == trans->nPayCardCnt+1) { //�����ѳɹ�
                    return 0;
                }
            }
            //ks_setlasterr("������ǰ����뵱ǰ������",-1);
            return -1;
        }
        if(nPayCnt != trans->nPayCardCnt) {
            SET_ERR("���Ѵ����뿨�в�һ��");
            return -1;
        }
        memset(sRandom,0,sizeof(sRandom));
        //ȡ�����
        dec2hex(ucRespData+39,4,sRandom);
        memcpy(trans->sRandom,sRandom,8);
        trans->sRandom[8] = 0;
        return 0;
    }
    SET_ERR("��֧�ֵĽ�������");
    return -1;
}

int ks_cmcc_cardtype::UpdateBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData) {
    // ���ܸ���
    char szData[256],szCmd[256],sRandom[17],sMac[17];
    byte uData[256],uCmd[256],uEncryptData[256];
    byte uDataLen;
    byte uRandom[8];
    std::string sCmd;
    ks_cpu_cmd_t cmd;
    int nRet,len;

    memset(&cmd,0,sizeof cmd);
    if(ucLength > sizeof(uData)-1) {
        SET_ERR("д�����ݳ��ȳ�������");
        return -1;
    }
    //
    memset(uRandom,0,sizeof uRandom);


    // 3 ����ɢ
    nRet = this->GetRandomNum(uRandom);
    if(nRet) {
        return nRet;
    }
    uRandom[4]=0x80;
    dec2hex(uRandom,8,sRandom);
    strcpy(this->m_szRandomNum,sRandom);

    nRet = m_PSAMCardType->ResetPSAM();
    if(nRet) {
        SET_ERR("PSAM����λ����");
        return -1;
    }

    // select adf

    //sprintf(szCmd,"00A4040010D1560001018000000000000100000000");

    //nRet = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uData,uDataLen);
    nRet=m_PSAMCardType->selectADFByName("D1560001018000000000000100000000");
    if(nRet) {
        SET_ERR("ѡĿ¼ʧ�� : "<<GetErrMsgByErrCode(nRet,NULL));
        return -1;
    }


    //strcpy(sRandom,"7AA27AC380000000");
    sCmd = "801A040110";
    sCmd += sRandom;
    // 2����ɢ
    sprintf(szData,"%s%02X",this->m_appSerialNo+2,this->loadKeyVer_);
    sCmd += szData;
    // 1����ɢ
    //sprintf(szData,"%02X%02X800000000000",this->enterpriceAppID_,this->loadKeyVer_);
    //sCmd += szData;

    nRet = m_PSAMCardType->Adpu4HexSAM(sCmd.c_str(),sCmd.length(),uData,uDataLen);
    if(nRet) {
        SET_ERR(GetErrMsgByErrCode(nRet,NULL));
        return -1;
    }

    // cipher data
    int nBeginPos,nBlockSize,nDataLen,nSegLen;
    nBlockSize = 32;
    nBeginPos = 0;
    uData[0] = ucLength;
    // ��������
    memcpy(uData+1,ucData,ucLength);
    nDataLen = ucLength + 1;
    if(nDataLen % 8 != 0) {
        memcpy(uData+nDataLen,"\x80\x00\x00\x00\x00\x00\x00\x00",8-(nDataLen%8));
        nDataLen += 8 - (nDataLen % 8);
    }
    dec2hex(uData,nDataLen,szCmd);
    while(nBeginPos < nDataLen) {
        nSegLen = (nBeginPos + nBlockSize > nDataLen) ? (nDataLen - nBeginPos) : nBlockSize;

        memset(szCmd,0,sizeof szCmd);
        sprintf(szCmd,"80FA0200%02X",nSegLen);
        hex2dec(szCmd,strlen(szCmd),uCmd,len);
        memcpy(uCmd+len,uData+nBeginPos,nSegLen);

        memset(&cmd,0,sizeof cmd);
        cmd.send_buf = uCmd;
        cmd.send_len = nSegLen+len;
        cmd.recv_buf = uEncryptData+nBeginPos;
        //nRet = m_PSAMReader->cpucard_cmd(m_PSAMReaderPara,&cmd,KS_PSAM);
        nRet = m_PSAMCardType->Adpu4SAM(uCmd,cmd.send_len,cmd.recv_buf,cmd.recv_len);
        if(nRet) {
            SET_ERR(GetErrMsgByErrCode(nRet,NULL));
            return -1;
        }
        nBeginPos += nSegLen;
    }
    // ����MAC
    memset(szCmd,0,sizeof szCmd);
    // ����+��ҵID��+4�ֽ�MAC
    len = sprintf(szCmd,"84540100%02X%s",nDataLen+6+4,this->strEnterpriceCode_);
    dec2hex(uEncryptData,nDataLen,szCmd+len);

    nRet = this->CalcSafeMac4Sam(szCmd,sMac);
    if(nRet) {
        SET_ERR(GetErrMsgByErrCode(nRet,NULL));
        return -1;
    }
    // ��������
    memset(&cmd,0,sizeof cmd);
    strcat(szCmd,sMac);
    cmd.send_buf = (unsigned char*)szCmd;
    cmd.send_len = strlen(szCmd);
    cmd.recv_buf = uData;
    cmd.cmd_type = 1;

    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        SET_ERR(GetErrMsgByErrCode(nRet,NULL));
        return -1;
    }

    return 0;
}

int ks_cmcc_cardtype::GetBalance() {
    std::string sCmd;
    unsigned char ucRespData[256];
    ks_cpu_cmd_t cmd;
    int nRet;

    sCmd="805E000207";
    sCmd += this->strEnterpriceCode_;
    sCmd += "03";
    //�����ĳ���
    cmd.send_buf=(byte*)sCmd.c_str();
    cmd.send_len=sCmd.size();
    cmd.recv_buf = ucRespData;
    cmd.cmd_type=1;//16����
    nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        if(cmd.cmd_retcode) {
            SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
            return cmd.cmd_retcode;
        } else {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    //�����
    m_CardBal = get_4byte_int(ucRespData);
    return 0;
}

//��ȡ��������Ϣ
char * ks_cmcc_cardtype::GetErrMsgByErrCode( int nErrCode,char *sErrInfo) {
    switch( nErrCode) {
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
    case 0x9835:
        sprintf(m_ErrMsg,"Err-%04X:û��ȡ�����",nErrCode);
        break;
    case 0x9840:
        sprintf(m_ErrMsg,"Err-%04X:��KEY����ס",nErrCode);
        break;
    case 0x9311:
        sprintf(m_ErrMsg,"Err-%04X:MAC����",nErrCode);
        break;
    case 0x9312:
        sprintf(m_ErrMsg,"Err-%04X:��ҵ������Ӧ�ò�����",nErrCode);
        break;
    case 0x9314:
        sprintf(m_ErrMsg,"Err-%04X:��Ӧ�����ʹ���",nErrCode);
        break;
    case 0x9316:
        sprintf(m_ErrMsg,"Err-%04X:��ҵID����",nErrCode);
        break;
    case 0x9317:
        sprintf(m_ErrMsg,"Err-%04X:��Ӧ�������Ŵ�",nErrCode);
        break;
    default:
        sprintf(m_ErrMsg,"Err-%04X:��֪���Ĵ���",nErrCode);
        break;
    }
    if(sErrInfo)
        strcpy(sErrInfo,m_ErrMsg);
    return m_ErrMsg;
}

//////////////////////////////////////////////////////////////////
int ks_cmcc_cardtype::LoadKeysFromKeyCard(const char *sKeyCardPwd) {
    char mainkey[36]= {0};
    int nRet;
    nRet = CCardType::LoadKeysFromKeyCard(sKeyCardPwd);
    if(nRet) {
        return nRet;
    }
    //dec2hex(this->cardtype_buff,16,mainkey);
    //m_childct->AuthDLL(mainkey,0);
    this->SetKeyCard(m_childct);
    return 0;
}

void ks_cmcc_cardtype::SetMifare1Key(const char *sCipherKey) {
    if(m_childct)
        m_childct->AuthDLL(sCipherKey,1);
}

int ks_cmcc_cardtype::load_mfcard_type() {
    char path[1024];
    char exec_path[2048]="";
    char *p;
    GetModuleFileName(NULL,path,1023);
    p = strrchr(path,'\\');
    if(p) {
        *p = 0;
    }
    sprintf(exec_path,"%s\\%s",path,mfCardLibName_);
    mf_cardtype_handle = LoadLibrary(exec_path);
    if(!mf_cardtype_handle) {
        if( !GetSystemDirectory(path,sizeof(path)-1) ) {
            SET_ERR("��ȡϵͳ·��ʧ��");
            return -1;
        }
        sprintf(exec_path,"%s\\%s",path,mfCardLibName_);
        mf_cardtype_handle = LoadLibrary(exec_path);
        if(!mf_cardtype_handle) {
            SET_ERR("�޷�����mfcardtype");
            return -1;
        }
    }
    mf_reg_op = (mf_register_cardtype_op)GetProcAddress(mf_cardtype_handle,"register_cardtype_op");
    if(mf_reg_op==NULL) {
        SET_ERR("�޷�����mfcardtype,�ӿں�������");
        return -1;
    }
    mf_reg_op(m_childct);
    if(strcmp(m_childct->cardtype_name,mfCardLibName_)) {
        SET_ERR("DLL���Ʋ���ȷ");
        return -1;
    }
    m_childct->Attach(m_Reader,m_ReaderPara,RT_USERCARD);
    m_childct->Attach(m_KeyReader,m_KeyReaderPara,RT_KEYCARD);
    return 0;
}

int ks_cmcc_cardtype::water_publishcard(int watertype,ks_water_pack_t *pack) {
    int nRet;
    TEST_CARDTYPE(0);
    nRet=m_childct->RequestCard(NULL);
    if(nRet)
        return nRet;
    return m_childct->water_publishcard(watertype,pack);
}
int ks_cmcc_cardtype::water_recyclecard(int watertype) {
    int nRet;
    TEST_CARDTYPE(0);
    nRet=m_childct->RequestCard(NULL);
    if(nRet)
        return nRet;
    return m_childct->water_recyclecard(watertype);
}
int ks_cmcc_cardtype::water_readmoney(int watertype,ks_water_pack_t *pack) {
    int nRet;
    TEST_CARDTYPE(KS_NOTSUPPORT);
    nRet=m_childct->RequestCard(NULL);
    if(nRet)
        return nRet;
    return m_childct->water_readmoney(watertype,pack);
}
int ks_cmcc_cardtype::water_writemoney(int watertype,ks_water_pack_t *pack) {
    int nRet;
    TEST_CARDTYPE(KS_NOTSUPPORT);
    nRet=m_childct->RequestCard(NULL);
    if(nRet)
        return nRet;
    return m_childct->water_writemoney(watertype,pack);
}
int ks_cmcc_cardtype::water_publishparamcard(int watertype,ks_water_param_t *param) {
    int nRet;
    TEST_PARAMCARDTYPE();
    nRet=m_childct->RequestCard(NULL);
    if(nRet)
        return nRet;
    return m_childct->water_publishparamcard(watertype,param);
}
int ks_cmcc_cardtype::water_recycleparamcard(int watertype) {
    int nRet;
    TEST_PARAMCARDTYPE();
    nRet=m_childct->RequestCard(NULL);
    if(nRet)
        return nRet;
    return m_childct->water_recycleparamcard(watertype);
}
int ks_cmcc_cardtype::water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate) {
    int nRet;
    TEST_PARAMCARDTYPE();
    nRet=m_childct->RequestCard(NULL);
    if(nRet)
        return nRet;
    return m_childct->water_publish_legacycard(watertype,fee_rate);
}
int ks_cmcc_cardtype::water_read_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate) {
    int nRet;
    TEST_PARAMCARDTYPE();
    nRet=m_childct->RequestCard(NULL);
    if(nRet)
        return nRet;
    return m_childct->water_read_legacycard(watertype,fee_rate);
}
void ks_cmcc_cardtype::DumpSectData(int watertype) {
    int nRet;
    m_childct->RequestCard(NULL);
    m_childct->DumpSectData(watertype);
}

int ks_cmcc_cardtype::SetFieldReadMode(int fieldid) {
    int nRet;
    nRet = CCardType::SetFieldReadMode(fieldid);
    if(nRet)
        return nRet;
    return 0;
}
//��������ֶεĶ�ģʽ
void ks_cmcc_cardtype::ClearAllFieldReadMode() {
    CCardType::ClearAllFieldReadMode();
    if(m_childct)
        m_childct->ClearAllFieldReadMode();
}
//������ֶζ�ģʽ
void ks_cmcc_cardtype::ClearFieldReadMode(int fieldID) {
    CCardType::ClearFieldReadMode(fieldID);
    if(m_childct)
        m_childct->ClearFieldReadMode(fieldID);
}

int ks_cmcc_cardtype::SetFieldWriteMode(int fieldid) {
    int nRet;
    if(fieldid == CF_APPID || fieldid == CF_APPTYPE ) {
        SET_ERR("�ֶ�������Ȩ��["<<fieldid<<"]");
        return -1;
    }
    nRet = CCardType::SetFieldWriteMode(fieldid);
    if(nRet)
        return nRet;
    if(m_defaultCardType == KS_SIMCARD)
        return 0;
    if(m_childct) {
        nRet = m_childct->SetFieldWriteMode(fieldid);
        if(nRet) {
            SET_ERR(m_childct->GetLastErrMsg(NULL));
            return nRet;
        }
    }
    return 0;
}
//���ø��ֶζ�дģʽ
int ks_cmcc_cardtype::SetFieldAllMode(int fieldID) {
    int nRet;
    nRet = CCardType::SetFieldAllMode(fieldID);
    if(nRet)
        return nRet;
    if(m_defaultCardType == KS_SIMCARD)
        return 0;
    if(m_childct) {
        nRet= m_childct->SetFieldAllMode(fieldID);
        if(nRet) {
            SET_ERR(m_childct->GetLastErrMsg(NULL));
            return nRet;
        }
    }
    return 0;
}
//������ֶ�дģʽ
void ks_cmcc_cardtype::ClearFieldWriteMode(int fieldID) {
    CCardType::ClearFieldWriteMode(fieldID);
    if(m_childct)
        m_childct->ClearFieldWriteMode(fieldID);
}
//������ֶ�����ģʽ
void ks_cmcc_cardtype::ClearFieldAllMode(int fieldID) {
    CCardType::ClearFieldAllMode(fieldID);
    if(m_childct)
        m_childct->ClearFieldAllMode(fieldID);
}
//��������ֶε�дģʽ
void ks_cmcc_cardtype::ClearAllFieldWriteMode() {
    CCardType::ClearAllFieldWriteMode();
    if(m_childct)
        m_childct->ClearAllFieldWriteMode();
}
//��������ֶεĶ�дģʽ
void ks_cmcc_cardtype::ClearAllFieldAllMode() {
    CCardType::ClearAllFieldAllMode();
    if(m_childct)
        m_childct->ClearAllFieldAllMode();
}
int ks_cmcc_cardtype::ReadCard() {
    return CCardType::ReadCard();
}
int ks_cmcc_cardtype::WriteCard() {
    int nRet;
    nRet = CCardType::WriteCard();
    if(nRet)
        return nRet;
    if(m_defaultCardType == KS_SIMCARD)
        return 0;
    if(m_childct) {
        nRet=m_childct->doSubRequestCard(NULL);
        if(nRet) {
            SET_ERR(m_childct->GetLastErrMsg(NULL));
            return nRet;
        }
        nRet = m_childct->WriteCard();
        if(nRet) {
            SET_ERR(m_childct->GetLastErrMsg(NULL));
            return nRet;
        }
        return CCardType::RequestCard(NULL);
    }
    return 0;
}

int ks_cmcc_cardtype::SetFieldVal(int FieldID,const char *fieldval) {
    int nRet;
    if(CF_APPTYPE == FieldID || CF_APPID == FieldID) {
        SET_ERR("�����Բ������޸�ID["<<FieldID<<"]");
        return -1;
    }

    nRet = CCardType::SetFieldVal(FieldID,fieldval);
    if(nRet)
        return nRet;
    if(m_defaultCardType == KS_SIMCARD)
        return 0;
    if(m_childct) {
        nRet = m_childct->SetFieldVal(FieldID,fieldval);
        if(nRet) {
            SET_ERR(m_childct->GetLastErrMsg(NULL));
            return nRet;
        }
    }
    return 0;
}
int ks_cmcc_cardtype::GetFieldVal(int FieldID,char *fieldval) {
    int nRet;
    nRet = CCardType::GetFieldVal(FieldID,fieldval);
    return nRet;
}

//nTransType 1-��ֵ 2-���ѣ�����ǰ�����ѻ��ֵ����
int ks_cmcc_cardtype::GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac,unsigned char *sTac) {
    char szCmd[256];
    unsigned char ucRespData[256]= {0};
    unsigned char ucRespLen=0;

    nTransFlag = (nTransFlag == 1) ? 0x02 : 0x06;
    sprintf(szCmd,"807200%02X09%s03%04X",nTransFlag,this->strEnterpriceCode_,CardCnt);

    int nRet=this->Adpu4Hex(szCmd,strlen(szCmd),ucRespData,ucRespLen);
    if(nRet) {
        //SET_ERR("ȡ������֤ʧ��"<<nRet);
        return nRet;
    }
    if(sMac) {
        memcpy(sMac,ucRespData,4);
    }
    if(sTac) {
        memcpy(sTac,ucRespData+4,4);
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////
int KSAPI register_cardtype_op(ks_cardtype_base *&op) {
    // 2010-8-8 tc
    // �����µ�ģʽ��ÿ��ע�ᶼ�����µĶ���
    op = new ks_cmcc_cardtype();
    return 0;
}
