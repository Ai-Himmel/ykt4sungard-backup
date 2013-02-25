///////////////////////////////////////////////////////////////////////////////
#include "ks_cardtmpl.h"

///////////////////////////////////////////////////////////////////////////////
ks_cardtmpl::ks_cardtmpl():ks_cardtype_base("ks_cardtmpl.dll") {
}
ks_cardtmpl::~ks_cardtmpl() {
}

void ks_cardtmpl::GetSupportCardType(unsigned int cardTypes[],int &cnt) {
}
char* ks_cardtmpl::GetErrMsgByErrCode( int nErrCode,char *sErrInfo) {
    return "";
}
int  ks_cardtmpl::SetFieldVal(int FieldID,const char *fieldval) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::GetFieldVal(int FieldID,char *fieldval) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::testCardExists(char *szCardPhyID) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::SelectADF () {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::VerifyPin (const char* sPin) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::ReadCard () {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::WriteCard () {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::InitUserCard (const char *sShowCardNo) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::LoadKeysFromKeyCard (const char *sKeyCardPwd) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::IsLoadKeys () {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::IsLoadCloneKeys () {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::LoadKeys4Clone (const char sKeyCardPin[7]) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::CloneKeyCard (const char sCloneCardPin[7]) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::PublishKeyCard (unsigned char* sMasterKey,const char* sPin) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::RecycleKeyCard () {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::RestoreFactorySettings () {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::SaveKeys () {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::VerifyCardPasswd(const char *cardphyid,const char* sCardPasswd,int& iIsPass) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::CommInit (const char *svrip,int svrport,int svrfunc) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::AddMoney(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::PayMoney(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::ExtAuth(const char *cardphyid,int keyidx) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::Adpu(const unsigned char *ucCmd,unsigned char ucSendLen,
                       unsigned char *ucRespData,unsigned char &ucRespLen) {
    return KS_NOTSUPPORT;
}
int  ks_cardtmpl::Adpu4Hex(const char *szCmd,unsigned char ucSendLen,
                           unsigned char *ucRespData,unsigned char &ucRespLen) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::ReadRecordFile(int SFI,unsigned char *ucData,int idx/* = 1*/,int len/* = 0*/) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::ReadRecordFile4Mac(int SFI,unsigned char *ucData,int idx/* = 1*/,int len/* = 0*/) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::InitForTrans(ST_TRANSPACK *trans,int trans_type) {
    return KS_NOTSUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
int ks_cardtmpl::water_publishcard(int watertype,ks_water_pack_t *pack) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::water_recyclecard(int watertype) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::water_readmoney(int watertype,ks_water_pack_t *pack) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::water_writemoney(int watertype,ks_water_pack_t *pack) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::water_publishparamcard(int watertype,ks_water_param_t *param) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::water_recycleparamcard(int watertype) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::water_read_paramcard(int watertype,ks_water_param_t *param) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate) {
    return KS_NOTSUPPORT;
}
int ks_cardtmpl::water_read_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate) {
    return KS_NOTSUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
int KSAPI register_cardtype_op(ks_cardtype_base *&op) {
    op = new ks_cardtmpl();
    return 0;
}