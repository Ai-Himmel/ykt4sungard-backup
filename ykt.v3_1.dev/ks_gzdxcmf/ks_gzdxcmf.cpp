///////////////////////////////////////////////////////////////////////////////
#include "ks_gzdxcmf.h"
#include "kslicense.h"
#include <assert.h>


#ifndef byte
#define byte unsigned char
#endif

#pragma pack(1)
struct PERSINFO {
    byte rfu1[16];
    byte stuempno[20];
    byte schoolcode[2];
    byte cardtype;
    byte shopid[2];
    byte rfu2[7];
    byte custname[8];
    byte dutycode[4];
    byte idno[20];
    byte deptno[10];
    byte idtype[4];
    byte sex;
    byte rfu3;
    byte custid[4];
    byte certtype;
    byte national[2];
    byte expdate[3];
    byte country[3];
    byte opencardflag;
    byte rfu4;
    byte issueverno;
    byte issueid[10];
    byte rfu5[6];
    byte serviceno[10];
    byte rfu6[102];
};
#pragma pack()

#define SET_FIELDTYPE(s,f,fi,sect,t) do{ m_FieldVect[fi].unused=0; \
	m_FieldVect[fi].length = sizeof(f); \
	if(1 == m_FieldVect[fi].length){ m_FieldVect[fi].offset = f-(byte*)&s;} \
	else { m_FieldVect[fi].offset = f-(byte*)&s; } \
	m_FieldVect[fi].fid = sect; \
	m_FieldVect[fi].type=t; }while(0)


///////////////////////////////////////////////////////////////////////////////
ks_gzdxcmf::ks_gzdxcmf():ks_cardtype_base("ks_gzdxcmf.dll"),m_initMaxSectNo(0),m_initMinSectNo(0) {
    memset(m_initSectBitmap,0,sizeof m_initSectBitmap);
    memset(m_recycleSectBitmap,0,sizeof m_recycleSectBitmap);
    memset(m_initMFKey,0,sizeof m_initMFKey);
}
ks_gzdxcmf::~ks_gzdxcmf() {
}
int ks_gzdxcmf::doInitMFCard() {
    //size_t sectno;
    return 0;
}
void ks_gzdxcmf::GetSupportCardType(unsigned int cardTypes[],int &cnt) {
    cardTypes[cnt++] = 0x0201;
    cardTypes[cnt++] = 0x0400;
}
int ks_gzdxcmf::InitCardTypeDLL() {
    int ret;
    int iVal = 0;
    char param[512]= {0};
    int maxlen;
    ////////////////////////////////////////////////////////////////////////
    if(m_license->get_public_int_param("kscardlib.mfcard.maxsect",&iVal)) {
        SET_ERR("未设置 kscardlib.mfcard.maxsect");
        return -1;
    }
    m_initMaxSectNo = (size_t)iVal;
    if(m_license->get_public_int_param("kscardlib.mfcard.minsect",&iVal)) {
        SET_ERR("未设置 kscardlib.mfcard.minsect");
        return -1;
    }
    m_initMinSectNo = (size_t)iVal;
    if(m_initMaxSectNo <= m_initMinSectNo
            || m_initMaxSectNo > MAX_MF_SECTNO
            || m_initMinSectNo >= MAX_MF_SECTNO) {
        SET_ERR("设置初始化卡扇区参数错误");
        return -1;
    }
    ///////////////////////////////////////////////////////////////////////
    maxlen = sizeof(param)-1;
    memset(param,0,sizeof param);
    if(m_license->get_public_param("kscardlib.mfinit.sect",param,maxlen)) {
        SET_ERR("未设置 kscardlib.mfinit.sect");
        return -1;
    }
    strncpy(m_initSectBitmap,param,MAX_MF_SECTNO);

    memset(param,0,sizeof param);
    if(m_license->get_public_param("kscardlib.mfrecycle.sect",param,maxlen)) {
        SET_ERR("未设置 kscardlib.mfrecycle.sect");
        return -1;
    }
    strncpy(m_recycleSectBitmap,param,MAX_MF_SECTNO);

    /////////////////////////////////////////////////////////////////////
    initCardDef();
    return 0;
}
void ks_gzdxcmf::initCardDef() {
    m_FieldVect.clear();

    EF_FIELD EField;
    memset(&EField,0,sizeof(EField));
    EField.unused=1;

    for(int i=0; i<=CF_END; i++)
        m_FieldVect.push_back(EField);

    assert(sizeof(PERSINFO) == BLOCK_PER_SECT * BYTE_PER_BLOCK);
    PERSINFO perinfo;
    int sectno=36;
    //客户号
    SET_FIELDTYPE(perinfo,perinfo.custid,CF_CUSTID,sectno,FT_INT32);
    assert(m_FieldVect[CF_CUSTID].length == 4);

}
void ks_gzdxcmf::SetMifare1Key(const char *sCipherKey) {
    return;
}
char* ks_gzdxcmf::GetErrMsgByErrCode( int nErrCode,char *sErrInfo) {
    return "";
}
int  ks_gzdxcmf::SetFieldVal(int FieldID,const char *fieldval) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::GetFieldVal(int FieldID,char *fieldval) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::testCardExists(char *szCardPhyID) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::SelectADF () {
    return 0;
}
int  ks_gzdxcmf::VerifyPin (const char* sPin) {
    return 0;
}
int  ks_gzdxcmf::ReadCard () {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::WriteCard () {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::InitUserCard (const char *sShowCardNo) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::LoadKeysFromKeyCard (const char *sKeyCardPwd) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::IsLoadKeys () {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::IsLoadCloneKeys () {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::LoadKeys4Clone (const char sKeyCardPin[7]) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::CloneKeyCard (const char sCloneCardPin[7]) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::PublishKeyCard (unsigned char* sMasterKey,const char* sPin) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::RecycleKeyCard () {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::RestoreFactorySettings () {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::SaveKeys () {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::VerifyCardPasswd(const char *cardphyid,const char* sCardPasswd,int& iIsPass) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::CommInit (const char *svrip,int svrport,int svrfunc) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::AddMoney(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::PayMoney(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::ExtAuth(const char *cardphyid,int keyidx) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::Adpu(const unsigned char *ucCmd,unsigned char ucSendLen,
                      unsigned char *ucRespData,unsigned char &ucRespLen) {
    return KS_NOTSUPPORT;
}
int  ks_gzdxcmf::Adpu4Hex(const char *szCmd,unsigned char ucSendLen,
                          unsigned char *ucRespData,unsigned char &ucRespLen) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::ReadRecordFile(int SFI,unsigned char *ucData,int idx/* = 1*/,int len/* = 0*/) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::ReadRecordFile4Mac(int SFI,unsigned char *ucData,int idx/* = 1*/,int len/* = 0*/) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::InitForTrans(ST_TRANSPACK *trans,int trans_type) {
    return KS_NOTSUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
int ks_gzdxcmf::water_publishcard(int watertype,ks_water_pack_t *pack) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::water_recyclecard(int watertype) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::water_readmoney(int watertype,ks_water_pack_t *pack) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::water_writemoney(int watertype,ks_water_pack_t *pack) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::water_publishparamcard(int watertype,ks_water_param_t *param) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::water_recycleparamcard(int watertype) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::water_read_paramcard(int watertype,ks_water_param_t *param) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate) {
    return KS_NOTSUPPORT;
}
int ks_gzdxcmf::water_read_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate) {
    return KS_NOTSUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
int KSAPI register_cardtype_op(ks_cardtype_base *&op) {
    op = new ks_gzdxcmf();
    return 0;
}