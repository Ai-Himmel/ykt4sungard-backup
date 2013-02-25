#include "kscardtype.h"
#include <iostream>
#include "global_func.h"
using namespace std;

ks_cardtype_base::ks_cardtype_base(const char *p):
    m_license(NULL),m_cardTypeNo(0),m_CardTypeCode(0),m_PSAMCardType(NULL),
    m_defaultCardType(KS_CPUCARD) {
    strcpy(cardtype_name,p);
    memset(&m_CardKeys,0,sizeof m_CardKeys);
    resetAll();
}
ks_cardtype_base::~ks_cardtype_base() {
}
void ks_cardtype_base::resetAll() {
    memset(m_currentADF,0,sizeof m_currentADF);
    memset(m_ADFData,0,sizeof m_ADFData);
}
int ks_cardtype_base::doRequestCard(char *szCardPhyID,KS_CARD_TYPE &t) {
    int nRet=0;
    char phyno[17] = {0};
    memset(m_ErrMsg,0,sizeof(m_ErrMsg));
    memset(m_szCardUID,0,sizeof(m_szCardUID));
    nRet=m_Reader->request_card(m_ReaderPara,phyno,m_defaultCardType);
    if(nRet) {
        SET_ERR("寻卡错误 "<<m_Reader->GetErrMsg(NULL));
        return nRet;
    }
    resetAll();
    if(szCardPhyID)
        strcpy(szCardPhyID,phyno);
    if(this->checkCardType(m_Reader->card_type())) {
        // 如果不支持该类卡，返回 1
        SET_ERR("不支持该类卡!");
        t = (KS_CARD_TYPE)m_Reader->card_type();
        return 1;
    }
    t = (KS_CARD_TYPE)m_Reader->card_type();
    strcpy(m_szCardUID,phyno);
    m_defaultCardType = t;
    SET_ERR("寻卡成功，type["<<m_defaultCardType<<"]");
    this->ClearAllFieldAllMode();
    return 0;
}
int ks_cardtype_base::doSuccessRequestCard() {
    return 0;
}
int ks_cardtype_base::RequestCard(char* szCardPhyID) {
    int nRet=0;
    KS_CARD_TYPE ct;
    resetAll();
    nRet = this->doRequestCard(szCardPhyID,ct);
    if(nRet < 0)
        return -1;
    else if(nRet == 0) {
        // 支持卡片
        return doSuccessRequestCard();
    } else {
        return ct;
    }
    return 0;
}
int ks_cardtype_base::CheckSupportCard(const char *szCardPhyID,KS_CARD_TYPE ct) {
    resetAll();
    if(this->checkCardType(ct)==0) {
        strcpy(this->m_szCardUID,szCardPhyID);
        this->m_defaultCardType = ct;
        return this->doSuccessRequestCard();
    }
    return -1;
}
int ks_cardtype_base::checkCardType(int ct) {
    return 0;
}
void ks_cardtype_base::SetAppPath(const char *path) {
    strcpy(m_szAppPath,path);
}
int	ks_cardtype_base::AuthDLL(const char *key,int flag) {
    return KS_NOTSUPPORT;
}
void ks_cardtype_base::SetLogTrace(KS_Log_Tracer *tracer) {
    KS_Log_Tracer::instance(tracer);
}
void ks_cardtype_base::SetLastErrMsg(const char* errmsg,const char *file /*= __FILE__*/,int line/*=__LINE__*/) {
    strcpy(m_ErrMsg,errmsg);
    KS_Log_Tracer::instance()->SetTraceFile(file,line);
    KS_Log_Tracer::instance()->TraceMsg(errmsg);
}
char*  ks_cardtype_base::GetLastErrMsg (char *errmsg) {
    if(errmsg!=NULL)
        strcpy(errmsg,m_ErrMsg);
    return m_ErrMsg;
}
void  ks_cardtype_base::Attach (ks_device_op_t *device,ks_reader_dev_t *reader,READER_TYPE t) {
    if(t == RT_USERCARD) {
        m_Reader=device;
        m_ReaderPara=reader;
    } else if(t == RT_PSAM) {
        return;
    } else {
        m_KeyReader=device;
        m_KeyReaderPara=reader;
    }
}
ks_device_op_t * ks_cardtype_base::GetDevice(READER_TYPE t) {
    switch(t) {
    case RT_USERCARD:
        return m_Reader;
    case RT_PSAM:
        return NULL;
    case RT_KEYCARD:
        return m_KeyReader;
    default:
        return NULL;
    }
}
ks_reader_dev_t *ks_cardtype_base::GetDevicePara(READER_TYPE t) {
    switch(t) {
    case RT_USERCARD:
        return m_ReaderPara;
    case RT_PSAM:
        return NULL;
    case RT_KEYCARD:
        return m_KeyReaderPara;
    default:
        return NULL;
    }
}
// 该函数将在打开串口后，由框架调用
int  ks_cardtype_base::OpenPort () {
    return 0;
}

int ks_cardtype_base::SetFieldReadMode(int fieldid) {
    if(fieldid>CF_END||fieldid<CF_START) {
        SET_ERR("SetFieldReadMode:字段索引"<<fieldid<<"不存在");
        return -1;
    }
    if(m_FieldVect[fieldid].unused) {
        SET_ERR("SetFieldReadMode:字段索引"<<fieldid<<"未使用");
        return 0;
    }
    if(m_FieldVect[fieldid].rw==RW_W) {
        SET_ERR("SetFieldWriteMode:字段索引"<<fieldid<<"不允许读");
        return -1;
    }
    m_EFMap[m_FieldVect[fieldid].fid].ReadFieldSet.insert(fieldid);
    return 0;
}
int ks_cardtype_base::SetFieldWriteMode(int fieldid) {
    if(fieldid>CF_END||fieldid<CF_START) {
        SET_ERR("SetFieldWriteMode:字段索引"<<fieldid<<"不存在");
        return -1;
    }
    if(m_FieldVect[fieldid].unused) {
        SET_ERR("SetFieldWriteMode:字段索引"<<fieldid<<"未使用");
        return 0;
    }
    if(m_FieldVect[fieldid].rw==RW_R) {
        SET_ERR("SetFieldWriteMode:字段索引"<<fieldid<<"不允许写");
        return -1;
    }
    m_EFMap[m_FieldVect[fieldid].fid].WriteFieldSet.insert(fieldid);
    return 0;
}
int ks_cardtype_base::SetFieldAllMode(int fieldid) {
    int nRet=0;
    nRet=SetFieldReadMode(fieldid);
    if(nRet)
        return nRet;
    return SetFieldWriteMode(fieldid);
}
void ks_cardtype_base::ClearFieldReadMode(int fieldid) {
    if(fieldid>CF_END||fieldid<CF_START)
        return;
    if(m_FieldVect[fieldid].unused) {
        return;
    }
    std::set<int>::iterator it;
    it=m_EFMap[m_FieldVect[fieldid].fid].ReadFieldSet.find(fieldid);
    if(it!=m_EFMap[m_FieldVect[fieldid].fid].ReadFieldSet.end()) {
        m_EFMap[m_FieldVect[fieldid].fid].ReadFieldSet.erase(it);
        return;
    }
}

void ks_cardtype_base::ClearFieldWriteMode(int fieldid) {
    if(fieldid>CF_END||fieldid<CF_START)
        return;
    if(m_FieldVect[fieldid].unused) {
        return;
    }
    std::set<int>::iterator it;
    it=m_EFMap[m_FieldVect[fieldid].fid].WriteFieldSet.find(fieldid);
    if(it!=m_EFMap[m_FieldVect[fieldid].fid].ReadFieldSet.end()) {
        m_EFMap[m_FieldVect[fieldid].fid].ReadFieldSet.erase(it);
        return;
    }
}
//清除该字段所有模式
void ks_cardtype_base::ClearFieldAllMode(int fieldID) {
    ClearFieldReadMode(fieldID);
    ClearFieldWriteMode(fieldID);
}
void ks_cardtype_base::ClearAllFieldReadMode() {
    std::map<int,EFBUF>::iterator it;
    for(it=m_EFMap.begin(); it!=m_EFMap.end(); ++it) {
        it->second.ReadFieldSet.clear();
        memset(it->second.ReadBuf,0,sizeof(it->second.ReadBuf));
    }
}

void ks_cardtype_base::ClearAllFieldWriteMode() {
    std::map<int,EFBUF>::iterator it;
    for(it=m_EFMap.begin(); it!=m_EFMap.end(); ++it) {
        it->second.WriteFieldSet.clear();
        memset(it->second.WriteBuf,0,sizeof(it->second.WriteBuf));
    }
}

void ks_cardtype_base::ClearAllFieldAllMode() {
    ClearAllFieldReadMode();
    ClearAllFieldWriteMode();
}
int ks_cardtype_base::ReadRecordFile(byte ucSFI,byte ucRecordNo,byte ucLength,byte *ucData) {
    int		nRet=0;
    char	szCmd[256]= {0};
    ks_cpu_cmd_t cmd;
    memset(&cmd,0,sizeof(cmd));
    sprintf(szCmd,"00B2%02X%02X%02X",ucRecordNo,(ucSFI<<3)+4,ucLength);
    cmd.send_buf=(byte*)szCmd;
    cmd.recv_buf=ucData;
    cmd.send_len=strlen(szCmd);
    cmd.cmd_type=1;//16进制
    nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
    if(nRet) {
        if(cmd.cmd_retcode) {
            GetErrMsgByErrCode(cmd.cmd_retcode,cmd.cmd_retmsg);
            char msg[512]= {0};
            sprintf(msg,"ReadRecordFile SFID=%X:%s",ucSFI,cmd.cmd_retmsg);
            SET_ERR(msg);
            return nRet;
        } else {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    return 0;
}
int ks_cardtype_base::SetKeyCard(ks_cardtype_base *c) {
    if(m_CardKeys.bLoad == 0)
        return -1;
    memcpy(&(c->m_CardKeys),&(this->m_CardKeys),sizeof(this->m_CardKeys));
    c->m_CardKeys.bLoad = 1;
    return 0;
}
int ks_cardtype_base::water_publishcard(int watertype,ks_water_pack_t *pack) {
    return 0;
}
int ks_cardtype_base::water_recyclecard(int watertype) {
    return 0;
}
int ks_cardtype_base::water_readmoney(int watertype,ks_water_pack_t *pack) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::water_writemoney(int watertype,ks_water_pack_t *pack) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::water_publishparamcard(int watertype,ks_water_param_t *param) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::water_recycleparamcard(int watertype) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::water_read_paramcard(int watertype,ks_water_param_t *param) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::water_read_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate) {
    return KS_NOTSUPPORT;
}
void ks_cardtype_base::DumpSectData(int watertype) {
    return ;
}

int ks_cardtype_base::GrayLock(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::GrayDebitUnlock(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::GrayUnlock(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::CAPPUpdate(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::CAPPDebit(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::PostPaidUpdate(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::PostPaidDebit(ST_TRANSPACK *transpack) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac/*=NULL*/,unsigned char *sTac/*=NULL*/) {
    return KS_NOTSUPPORT;
}
int ks_cardtype_base::selectADFBySFI(const char *SFI,int force/* = 0*/) {
    char sCmd[128];
    int nRet,n;
    unsigned char ucRespData[256]= {0},respLen=0;
    if(strcmp(m_currentADF,SFI)==0 && force == 0) {
        SET_ERR("目录已经选择["<<SFI<<"]");
        return 0;
    }
    sprintf(sCmd,"00A40000%02X%s",strlen(SFI)/2,SFI);
    nRet = this->Adpu4Hex(sCmd,strlen(sCmd),ucRespData,respLen);
    if(nRet) {
        SET_ERR("选择SAM目录错误["<<SFI<<"]Err["<<hex<<nRet<<"]");
        return nRet;
    }
    strcpy(m_currentADF,SFI);
    n = sizeof(m_ADFData) - 1;
    if(respLen > n/2)
        respLen = n;
    dec2hex(ucRespData,respLen,m_ADFData);
    return 0;
}
int ks_cardtype_base::selectADFByName(const char *ADFName,int force/* = 0*/) {
    char sCmd[128];
    int nRet,n;
    unsigned char ucRespData[256]= {0},respLen=0;
    if(strcmp(m_currentADF,ADFName)==0 && force == 0) {
        SET_ERR("目录已经选择["<<ADFName<<"]");
        return 0;
    }
    sprintf(sCmd,"00A40400%02X%s",strlen(ADFName)/2,ADFName);
    nRet = this->Adpu4Hex(sCmd,strlen(sCmd),ucRespData,respLen);
    if(nRet) {
        SET_ERR("选择SAM目录错误["<<ADFName<<"]Err["<<hex<<nRet<<"]");
        return nRet;
    }
    strcpy(m_currentADF,ADFName);
    n = sizeof(m_ADFData) - 1;
    if(respLen > n/2)
        respLen = n;
    dec2hex(ucRespData,respLen,m_ADFData);
    return 0;
}

///////////////////////////////////////////////////////////////////////
///  ks_psamcard_base
const char ks_psamcard_base::MF_SFI[]="3F00";
ks_psamcard_base::ks_psamcard_base():m_PSAMSlot(0),m_PowerOn(0) {
    memset(&m_CardKeys,0,sizeof m_CardKeys);
    m_ReaderPara = &m_Para;
}
ks_psamcard_base::~ks_psamcard_base() {
}
void ks_psamcard_base::resetAll() {
    memset(m_currentADF,0,sizeof m_currentADF);
    memset(m_ADFData,0,sizeof m_ADFData);
}
void ks_psamcard_base::SetLogTrace(KS_Log_Tracer *tracer) {
    KS_Log_Tracer::instance(tracer);
}
void ks_psamcard_base::setLicense(ks_cardlib_license *lic) {
    m_license = lic;
}
void ks_psamcard_base::setCardKeys(CARDKEYS &keys) {
    m_CardKeys = keys;
}
void ks_psamcard_base::Attach(const ks_device_op_t *reader,const ks_reader_dev_t * para) {
    m_Reader = reader;
    m_Para = *para;
}
void ks_psamcard_base::SetAppPath(const char *path) {
    strcpy(m_szAppPath,path);
}
void ks_psamcard_base::SetLastErrMsg(const char* errmsg,const char *file /*= __FILE__*/,int line/*= __LINE__*/) {
    strcpy(m_ErrMsg,errmsg);
    KS_Log_Tracer::instance()->SetTraceFile(file,line);
    KS_Log_Tracer::instance()->TraceMsg(errmsg);
}
char*  ks_psamcard_base::GetLastErrMsg (char *errmsg) {
    if(errmsg!=NULL)
        strcpy(errmsg,m_ErrMsg);
    return m_ErrMsg;
}
void ks_psamcard_base::SetSAMPara(const ks_reader_dev_t *para) {
    m_Para = *para;
    SET_ERR("更新SAM卡参数port["<<m_ReaderPara->cpuport<<"]");
}
int ks_psamcard_base::selectADFBySFI(const char *SFI,int force/* = 0*/) {
    char sCmd[128];
    int nRet,n;
    unsigned char ucRespData[256]= {0},respLen=0;
    if(strcmp(m_currentADF,SFI)==0 && force == 0) {
        SET_ERR("目录已经选择["<<SFI<<"]");
        return 0;
    }
    sprintf(sCmd,"00A40000%02X%s",strlen(SFI)/2,SFI);
    nRet = this->Adpu4HexSAM(sCmd,strlen(sCmd),ucRespData,respLen);
    if(nRet) {
        SET_ERR("选择SAM目录错误["<<SFI<<"]Err["<<hex<<nRet<<"]");
        return nRet;
    }
    strcpy(m_currentADF,SFI);
    n = sizeof(m_ADFData) - 1;
    if(respLen > n/2)
        respLen = n;
    dec2hex(ucRespData,respLen,m_ADFData);
    return 0;
}
int ks_psamcard_base::selectADFByName(const char *ADFName,int force/* = 0*/) {
    char sCmd[128];
    int nRet,n;
    unsigned char ucRespData[256]= {0},respLen=0;
    if(strcmp(m_currentADF,ADFName)==0 && force == 0) {
        SET_ERR("目录已经选择["<<ADFName<<"]");
        return 0;
    }
    sprintf(sCmd,"00A40400%02X%s",strlen(ADFName)/2,ADFName);
    nRet = this->Adpu4HexSAM(sCmd,strlen(sCmd),ucRespData,respLen);
    if(nRet) {
        SET_ERR("选择SAM目录错误["<<ADFName<<"]Err["<<hex<<nRet<<"]");
        return nRet;
    }
    strcpy(m_currentADF,ADFName);
    n = sizeof(m_ADFData) - 1;
    if(respLen > n/2)
        respLen = n;
    dec2hex(ucRespData,respLen,m_ADFData);
    return 0;
}
int ks_psamcard_base::ResetPSAM() {
    int ret=0;
    unsigned char rlen[24];
    unsigned char rbuff[256];
    if(m_PSAMSlot == m_ReaderPara->cpuport
            && m_PowerOn == 1)
        return 0;
    resetAll();
    if(m_ReaderPara->cpuport < 1 || m_ReaderPara->cpuport > 4) {
        SET_ERR("SAM卡座参数错误port["<<m_ReaderPara->cpuport<<"]");
        return -1;
    }
    ret=m_Reader->cpucard_poweron(m_ReaderPara,KS_PSAM,rlen,rbuff);
    if(ret) {
        SET_ERR("SAM卡座上电复位错误SAMNO["<<m_ReaderPara->cpuport<<"]ret["<<ret<<"]");
        return ret;
    }
    m_PSAMSlot = m_ReaderPara->cpuport;
    m_PowerOn = 1;
    return 0;
}
int ks_psamcard_base::Adpu4SAM(const unsigned char *uCmd,unsigned char ucSendLen,
                               unsigned char *ucRespData,unsigned char &ucRespLen) {
    int nRet;
    ks_cpu_cmd_t cmd;

    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (unsigned char *)uCmd;
    cmd.send_len = ucSendLen;
    cmd.recv_buf = ucRespData;
    cmd.cmd_type = 0;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
    if(nRet) {
        return nRet;
    }
    ucRespLen = cmd.recv_len;
    return 0;
}
int ks_psamcard_base::Adpu4HexSAM(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen) {
    int nRet,retry;
    ks_cpu_cmd_t cmd;

    retry = 0;
L_AGAIN:
    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (unsigned char*)szCmd;
    cmd.send_len = ucSendLen;
    cmd.recv_buf = ucRespData;
    cmd.cmd_type = 1;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
    if(nRet) {
        if(KS_CMDERROR == nRet && retry == 0) {
            // 可能需要上电复位
            SET_ERR("发送PSAM卡请求错误，尝试重复位");
            this->m_PSAMSlot = 0;
            nRet = this->ResetPSAM();
            if(nRet)
                return nRet;
            retry++;
            goto L_AGAIN;
        }
        if(cmd.cmd_retcode)
            return cmd.cmd_retcode;
        return nRet;
    }
    ucRespLen = cmd.recv_len;
    return 0;
}
