
#include <assert.h>
#include "cardtypemanager.h"
#include "ksdevice.h"
#include "log.h"
#include "logfile.h"
#include "interface.h"
CLog* CLog::_instance = NULL;

#define ERR_MSG(n,m) do { this->errorCode_ = n;this->errorMsg_.str("");this->errorMsg_<<m<<std::ends; }while(0)
#define ERR_MSG_RET(n,m) do { ERR_MSG(n,m); return n; } while(0)

DEF_DLLFUNC(register_cardtype_op);
DEF_DLLFUNC(register_device_op);
DEF_DLLFUNC(register_sam_op);

static ks_psamcard_dummy *g_dummy_psamcard = NULL;

CardTypeManager* CardTypeManager::instance_ = NULL;

CardTypeManager::CardTypeManager():cpuCardType_(NULL),LastcpuCardType_(NULL),cpuCardTypeId_(0xFFFFFFFF),
    errorCode_(0),psamCardType_(NULL) {
    // empty

}

CardTypeManager::~CardTypeManager() {
    freeAll();
}

CardTypeManager* CardTypeManager::instance() {
    if(instance_ == NULL) {
        instance_ = new CardTypeManager();
    }
    assert(instance_ != NULL);

    return instance_;
}

const char* CardTypeManager::getErrorMsg(char *msg,const char* defaultmsg) {
    static char szErrMsg[256];
    memset(szErrMsg,0,sizeof(szErrMsg));
    if(errorMsg_.str().size()<1) {
        if(defaultmsg)
            errorMsg_<<defaultmsg;
        else
            errorMsg_<<"没有错误消息";
        errorMsg_<<std::ends;
    }
    if(msg)
        strcpy(msg,errorMsg_.str().c_str());
    strncpy(szErrMsg,errorMsg_.str().c_str(),sizeof(szErrMsg)-1);
    return szErrMsg;
}
int CardTypeManager::registerDLL(HMODULE h,ks_cardtype_base *& c) {
    LOAD_DLLFUNC(h,register_cardtype_op);
    if(register_cardtype_op(c)==0) {
        return 0;
    }
    return -1;
}
int CardTypeManager::loadDLL(const char *cardtype,ks_cardtype_base *& c) {
    HMODULE h;
    h = LoadLibrary(cardtype);
    if(h == NULL) {
        ERR_MSG_RET(KS_COMM_ERR,"无法加载["<<cardtype<<"]");
    }
    cardTypeHandle_.push_back(h);
    if(registerDLL(h,c)) {
        FreeLibrary(h);
        ERR_MSG_RET(KS_COMM_ERR,"注册卡类型库错误["<<cardtype<<"]");
    }
    return addSupportTypes(c,cardtype);
}
int CardTypeManager::addSupportTypes(ks_cardtype_base *c,const char *cardtype) {
    CARDTYPE_ID types[24] = {0};
    int typeCnt = 0;
    c->GetSupportCardType(types,typeCnt);
    if(typeCnt == 0) {
        ERR_MSG_RET(KS_COMM_ERR,"卡类型库未定义卡类型标识["<<cardtype<<"]");
    }
    int i;
    CARDTYPE_MAP::const_iterator iter;
    for(i = 0; i < typeCnt; ++i) {
        iter = cardTypeMap_.find(types[i]);
        /*
        if(iter != cardTypeMap_.end())
        {
        	ERR_MSG_RET(KS_COMM_ERR,"卡类型库["<<cardtype<<"]卡类型标识已定义["<<types[i]<<"]");
        }
        */
        // TODO : 对于高位相同进行判断，高位相同也认为是不能注册的
        this->cardTypeMap_.insert(CARDTYPE_MAP::value_type(types[i],c));
    }
    return 0;
}
int CardTypeManager::doLoadAllDLL(ks_cardlib_license *lic,const char *baseDir) {
    int cardtypeCnt,i,ret;
    char paraName[128];
    char paraValue[512];
    size_t paraLen;
    std::string dllPath;
    assert(lic != NULL);
    lic->get_public_int_param("kscardlib.cardtypecnt",&cardtypeCnt);
    if(cardtypeCnt <= 0 || cardtypeCnt > 4) {
        ERR_MSG_RET(KS_COMM_ERR,"卡类型库数量错误");
    }
    paraLen = sizeof(paraValue) - 1;
    for(i = 1; i <= cardtypeCnt; ++i) {
        sprintf(paraName,"kscardlib.cardtype%d",i);
        memset(paraValue,0,sizeof paraValue);
        lic->get_public_param(paraName,paraValue,paraLen);
        if(strlen(paraValue) == 0) {
            ERR_MSG_RET(KS_COMM_ERR,"卡类型库["<<i<<"]未配置");
        }
        dllPath = baseDir;
        dllPath += "\\";
        dllPath += paraValue;
        ks_cardtype_base *c;
        TRACE2_LOG(("加载卡库[%s]",dllPath.c_str()));
        ret = loadDLL(dllPath.c_str(),c);
        if(ret) {
            return ret;
        }
        if(strcmp(c->cardtype_name,paraValue) != 0) {
            ERR_MSG_RET(KS_COMM_ERR,"卡类型库["<<paraValue<<"]与定义的名称不符");
        }
        cardTypeVec_.push_back(c);
        c->SetAppPath(baseDir);
        c->set_license(lic);
        c->SetCardTypeNo(i);
        KS_Log_Tracer *l = KS_Log_Tracer::instance();
        c->SetLogTrace(l);
    }
    return 0;

}
int CardTypeManager::registerPSAMDLL(HMODULE h,ks_psamcard_base *& c) {
    LOAD_DLLFUNC(h,register_sam_op);
    if(register_sam_op(c)==0) {
        return 0;
    }
    return -1;
}
int CardTypeManager::loadPSAM(const char *cardtype,ks_psamcard_base *& p) {
    HMODULE h;
    h = LoadLibrary(cardtype);
    if(h == NULL) {
        ERR_MSG_RET(KS_COMM_ERR,"无法加载["<<cardtype<<"]");
    }
    cardTypeHandle_.push_back(h);
    if(registerPSAMDLL(h,p)) {
        FreeLibrary(h);
        ERR_MSG_RET(KS_COMM_ERR,"注册卡类型库错误["<<cardtype<<"]");
    }
    return 0;
}
int CardTypeManager::doLoadPSAMDLL(ks_cardlib_license *lic,const char *baseDir) {
    std::string dllPath;
    char paraValue[512];
    size_t paraLen;
    size_t i;
    assert(lic != NULL);
    memset(paraValue,0,sizeof paraValue);
    paraLen = sizeof(paraValue) - 1;
    lic->get_public_param("kscardlib.psamcardtype",paraValue,paraLen);
    if(strlen(paraValue) == 0) {
        ERR_MSG(KS_COMM_ERR,"PSAM卡类型库未配置,使用默认配置");
        strcpy(paraValue,"ks_psamcard.dll");
    }
    if(strcmp(paraValue,"None")) {
        dllPath = baseDir;
        dllPath += "\\";
        dllPath += paraValue;
        TRACE2_LOG(("加载PSAM库[%s]",dllPath.c_str()));
        if(loadPSAM(dllPath.c_str(),psamCardType_)) {
            return -1;
        }
        if(psamCardType_->InitDll(lic)) {
            ERR_MSG(KS_COMM_ERR,"PSAM初始化失败");
            return -1;
        }
    } else {
        g_dummy_psamcard = new ks_psamcard_dummy();
        psamCardType_ = g_dummy_psamcard;
    }
    psamCardType_->SetLogTrace(KS_Log_Tracer::instance());
    for(i = 0; i < this->getCardTypeCount(); ++i) {
        ks_cardtype_base *c = this->getCardTypeByIdx(i);
        c->SetPSAMCardType(psamCardType_);
    }
    return 0;
}
int CardTypeManager::loadCardTypeDLL(ks_cardlib_license *lic,const char *baseDir) {
    int ret;
    freeAll();
    ret = doLoadAllDLL(lic,baseDir);
    if(ret) {
        freeAll();
    }
    ret = doLoadPSAMDLL(lic,baseDir);
    if(ret) {
        freeAll();
    }
    return ret;
}

void CardTypeManager::freeAll() {
    size_t i;
    for(i = 0; i < cardTypeVec_.size(); ++i) {
        HMODULE h = cardTypeHandle_.at(i);
        FreeLibrary(h);
    }
    cardTypeVec_.clear();
    cardTypeHandle_.clear();
    cardTypeMap_.clear();
}

ks_cardtype_base *CardTypeManager::getCardType(CARDTYPE_ID id) const {
    CARDTYPE_MAP::const_iterator i;
    i = cardTypeMap_.find(id);
    if(i != cardTypeMap_.end()) {
        ks_cardtype_base * r = i->second;
        return r;
    }
    return NULL;
}

ks_cardtype_base *CardTypeManager::getCardTypeByIdx(size_t idx) {
    assert(idx>=0 && idx < cardTypeVec_.size());
    return cardTypeVec_.at(idx);
}

void CardTypeManager::setErrorMsg(const char *errmsg,const char *defaultmsg) {
    errorMsg_.str("");
    if(strlen(errmsg))
        errorMsg_<<errmsg;
    else if(defaultmsg)
        errorMsg_<<defaultmsg;
    else
        errorMsg_<<"没有错误信息";
}
int CardTypeManager::requestCard(char *phyId) {
    int i,j;
    int ret;
    KS_CARD_TYPE ct;
    char phyno[32] = {0};
    // modify 2010-12-8 tc 删除掉，可能会影响寻卡速度
    /*
    if(NULL != cpuCardType_)
    {
    	if(cpuCardType_->testCardExists(phyId) == 0)
    	{
    		return 0;
    	}
    }
    */
    for(i = 0; i < this->getCardTypeCount(); ++i) {
        cpuCardType_= this->getCardTypeByIdx(i);
        ret = cpuCardType_->RequestCard(phyno);
        if(ret==0) {
            // find card
            cpuCardTypeId_ = cpuCardType_->RequestCardType();
            strcpy(phyId,phyno);
            return 0;
        } else if(ret < 0) {
            continue;
        } else {
            ct = (KS_CARD_TYPE)ret;
            for(j = 0; j < this->getCardTypeCount(); ++j) {
                ks_cardtype_base *c = this->getCardTypeByIdx(j);
                // 必须是同一款读卡器
                if((c != cpuCardType_) &&
                        (c->GetDevice(ks_cardtype_base::RT_USERCARD) == cpuCardType_->GetDevice(ks_cardtype_base::RT_USERCARD))) {
                    ret = c->CheckSupportCard(phyno,ct);
                    if(!ret) {
                        cpuCardType_ = c;
                        cpuCardTypeId_ = cpuCardType_->RequestCardType();
                        strcpy(phyId,phyno);
                        return 0;
                    }
                }
            }
        }
    }
    setErrorMsg(cpuCardType_->GetLastErrMsg(NULL),"寻卡失败");
    cpuCardType_=NULL;
    return ret;
}
ks_cardtype_base * CardTypeManager::getLastCardType(bool req /*= true*/) {
    char phyId[32] = {0};
    if(cpuCardType_ == NULL) {
        if(!req) {
            // 只有一个卡类型库时，默认返回该对象指针
            if(this->getCardTypeCount() == 1) {
                cpuCardType_ = this->getCardTypeByIdx(0);
                return cpuCardType_;
            }
            return NULL;
        }
        if(this->requestCard(phyId)!=0) {
            return NULL;
        }
    }
    return cpuCardType_;
}
int CardTypeManager::getCardTypeCode() {
    int cardTypeCode = 0;
    ks_cardtype_base *c = this->getLastCardType(false);
    if(c == NULL) {
        cardTypeCode = 0;
        return -1;
    }
    cardTypeCode = c->getCardTypeCode();
    return cardTypeCode;
}
int CardTypeManager::initComm(const char *ip,int port,int func) {
    int ret;
    int i;
    for(i = 0; i < this->getCardTypeCount(); ++i) {
        ks_cardtype_base *c = this->getCardTypeByIdx((size_t)i);
        ret = c->CommInit(ip,port,func);
        if(ret) {
            ERR_MSG_RET(ret,"初始化读卡库通讯参数错误...");
        }
    }
    return 0;
}
ks_psamcard_base *CardTypeManager::getPSAMCardType() const {
    return this->psamCardType_;
}
///////////////////////////////////////////////////////////////////////////////////
CardReaderManager::CardReaderManager():beepReader_(0) {
    // empty
    errorMsg_.str("");
    m_bPortOpen=0;
    freeAll();
}
CardReaderManager::~CardReaderManager() {
    // empty
}

int CardReaderManager::loadReaderDLL(ks_cardlib_license *lic,const char *baseDir) {
    int ret;
    freeAll();
    ret = doLoadReaderDLL(lic,baseDir);
    if(ret) {
        freeAll();
    }
    return ret;
}
int CardReaderManager::registerDLL(HMODULE h,ks_device_op_t *op) {
    LOAD_DLLFUNC(h,register_device_op);
    if(register_device_op(op)) {
        return -1;
    }
    return 0;
}

int CardReaderManager::doLoadReaderDLL(ks_cardlib_license *lic,const char *baseDir) {
    int i,ret,readerCnt;
    std::string readerName;
    char paraName[128];
    char paraValue[512];
    int paraLen;
    assert(lic != NULL);

    paraLen = sizeof(paraValue) - 1;
    lic->get_public_int_param("kscardlib.dllcount",&readerCnt);
    if(readerCnt <1 || readerCnt > MAX_READER) {
        ERR_MSG_RET(KS_COMM_ERR,"读卡器库配置错误");
    }
    for(i = 1; i <= readerCnt; ++i) {
        sprintf(paraName,"kscardlib.dll%d",i);
        memset(paraValue,0,sizeof paraValue);
        lic->get_public_param(paraName,paraValue,paraLen);
        ks_device_op_t op;
        readerName = baseDir;
        readerName += "\\";
        readerName += paraValue;
        TRACE2_LOG(("加载读卡器库[%s]",readerName.c_str()));
        ret = loadDLL(readerName.c_str(),&op);
        if(ret) {
            return ret;
        }
        op.set_logger(KS_Log_Tracer::instance());
        reader_[i-1] = op;
        TRACE_LOG("加载读卡器库成功");
    }
    return loadPara(lic);
}

int CardReaderManager::loadDLL(const char *path,ks_device_op_t *op) {
    HMODULE h;
    int ret;
    h = LoadLibrary(path);
    if(h == NULL) {
        ERR_MSG_RET(KS_COMM_ERR,"加载读卡器库错误["<<path<<"]");
    }
    ret = registerDLL(h,op);
    if(ret) {
        FreeLibrary(h);
        ERR_MSG_RET(KS_COMM_ERR,"注册读卡器库错误["<<path<<"]");
    }
    readerHandle_.push_back(h);
    return 0;

}
void CardReaderManager::freeAll() {
    size_t i;
    for(i = 0; i < readerHandle_.size(); ++i) {
        HMODULE h = readerHandle_.at(i);
        FreeLibrary(h);
    }
    readerHandle_.clear();
    memset(reader_,0,sizeof reader_);
    memset(readerType_,0,sizeof readerType_);
    memset(readerPara_,0,sizeof readerPara_);
    memset(cardTypeReaderPara_,0,sizeof cardTypeReaderPara_);
    memset(cardTypeReaderNo_,0,sizeof cardTypeReaderNo_);
    memset(readerNo_,0,sizeof readerNo_);
    memset(readerOpen_,0,sizeof readerOpen_);
}
int CardReaderManager::loadPara(ks_cardlib_license *lic) {
    int cpuReader,PSAMReader,keyReader;
    int cpuPort,psamPort,keyPort;
    int readerCnt;

    readerCnt = getReaderCount();
    assert(readerCnt > 0);

    lic->get_public_int_param("kscardlib.cpureader1",&cpuReader);
    lic->get_public_int_param("kscardlib.psamreader",&PSAMReader);
    lic->get_public_int_param("kscardlib.keyreader",&keyReader);
    if(cpuReader < 1 || cpuReader > readerCnt
            || PSAMReader < 1 || PSAMReader > readerCnt
            || keyReader < 1 || keyReader > readerCnt) {
        ERR_MSG_RET(KS_COMM_ERR,"用户卡,PSAM卡,密钥卡读卡器配置错误");
    }
    readerType_[ks_cardtype_base::RT_USERCARD] = &reader_[cpuReader-1];
    readerType_[ks_cardtype_base::RT_PSAM] = &reader_[PSAMReader-1];
    readerType_[ks_cardtype_base::RT_KEYCARD] = &reader_[keyReader-1];

    readerNo_[ks_cardtype_base::RT_USERCARD] = cpuReader;
    readerNo_[ks_cardtype_base::RT_PSAM] = PSAMReader;
    readerNo_[ks_cardtype_base::RT_KEYCARD] = keyReader;

    // parameter
    lic->get_public_int_param("kscardlib.cpuport1",&cpuPort);
    lic->get_public_int_param("kscardlib.psamport",&psamPort);
    lic->get_public_int_param("kscardlib.keycardtype",&keyPort);

    readerPara_[ks_cardtype_base::RT_USERCARD].cpuport = cpuPort;
    readerPara_[ks_cardtype_base::RT_USERCARD].no = cpuReader;

    readerPara_[ks_cardtype_base::RT_PSAM].cpuport = psamPort;
    readerPara_[ks_cardtype_base::RT_PSAM].no = PSAMReader;

    readerPara_[ks_cardtype_base::RT_KEYCARD].cpuport = keyPort;
    readerPara_[ks_cardtype_base::RT_KEYCARD].no = keyReader;

    return 0;
}

int CardReaderManager::initAllCardType(ks_cardlib_license *lic,CardTypeManager * manager) {
    int paraValue = 0;
    int paraLen;
    paraLen = sizeof(paraValue) - 1;
    if(lic->get_public_int_param("kscardlib.beepreader",&paraValue)) {
        paraValue = 1;
    }
    // 判断合法性
    if(paraValue < 1 || paraValue > this->getReaderCount())
        paraValue = 1;
    beepReader_ = paraValue;
    return doInitCardType(lic,manager);
}

int CardReaderManager::doInitCardType(ks_cardlib_license *lic,CardTypeManager * manager) {
    size_t i;
    char paraName[128];
    int cpuReader,cpuPort;
    ks_reader_dev_t *para;
    int ret;
    for(i = 0; i< manager->getCardTypeCount(); ++i) {
        ks_cardtype_base *c = manager->getCardTypeByIdx(i);
        assert(c != NULL);
        // reader index
        sprintf(paraName,"kscardlib.cpureader%d",i+1);
        lic->get_public_int_param(paraName,&cpuReader);
        ks_device_op_t * dev = NULL;
        dev = this->getReaderByIdx(cpuReader-1);
        if(dev==NULL) {
            ERR_MSG_RET(KS_COMM_ERR,"卡类型库["<<i+1<<"]配置读卡器参数错误");
        }
        // parameter
        sprintf(paraName,"kscardlib.cpuport%d",i+1);
        lic->get_public_int_param(paraName,&cpuPort);

        cardTypeReaderNo_[i] = cpuReader;

        this->cardTypeReaderPara_[i] = this->readerPara_[ks_cardtype_base::RT_USERCARD];
        para = &this->cardTypeReaderPara_[i];
        *para = *(this->getReaderParaByNo(cpuReader));
        para->cpuport = cpuPort;
        para->no = cpuReader;

        c->Attach(dev,para,ks_cardtype_base::RT_USERCARD);
        //c->Attach(readerType_[ks_cardtype_base::RT_PSAM],
        //	&readerPara_[ks_cardtype_base::RT_PSAM],ks_cardtype_base::RT_PSAM);
        c->Attach(readerType_[ks_cardtype_base::RT_KEYCARD],
                  &readerPara_[ks_cardtype_base::RT_KEYCARD],ks_cardtype_base::RT_KEYCARD);
        ret = c->InitCardTypeDLL();
        if(ret) {
            ERR_MSG_RET(KS_COMM_ERR,"初始化卡类型库错误["<<c->cardtype_name<<"]ret["<<ret<<"]");
        }
    }
    ks_psamcard_base * psam = CardTypeManager::instance()->getPSAMCardType();
    if(psam) {
        psam->Attach(readerType_[ks_cardtype_base::RT_PSAM],&readerPara_[ks_cardtype_base::RT_PSAM]);
        TRACE2_LOG(("加载PSAM卡类型port[%d]",readerPara_[ks_cardtype_base::RT_PSAM].cpuport));
    }
    return 0;
}
ks_device_op_t* CardReaderManager::getReaderByType(ks_cardtype_base::READER_TYPE t) {
    if(t == ks_cardtype_base::RT_USERCARD) {
        ks_cardtype_base *c = CardTypeManager::instance()->getLastCardType();
        if(c == NULL) {

            return NULL;
        }
        return c->GetDevice(t);
    }
    return readerType_[t];
    //return readerType_[t];
}
ks_reader_dev_t* CardReaderManager::getReaderParaByType(ks_cardtype_base::READER_TYPE t) {
    if(t == ks_cardtype_base::RT_USERCARD) {
        ks_cardtype_base *c = CardTypeManager::instance()->getLastCardType();
        if(c == NULL)
            return NULL;
        int no = c->GetCardTypeNo();
        assert(no>=1 && no <= CardTypeManager::instance()->getCardTypeCount());
        return &cardTypeReaderPara_[no-1];
    } else {
        return &readerPara_[t];
    }
}
void CardReaderManager::setErrorMsg(const char *errmsg,const char *defaultmsg) {
    errorMsg_.str("");
    if(strlen(errmsg))
        errorMsg_<<errmsg;
    else if(defaultmsg)
        errorMsg_<<defaultmsg;
    else
        errorMsg_<<"没有错误信息";
    errorMsg_<<std::ends;
}
const char * CardReaderManager::getErrorMsg(char *msg,const char* defaultmsg) {
    static char szErrMsg[256];
    memset(szErrMsg,0,sizeof(szErrMsg));
    if(errorMsg_.str().size()<1) {
        if(defaultmsg)
            errorMsg_<<defaultmsg;
        else
            errorMsg_<<"没有错误消息";
        errorMsg_<<std::ends;
    }
    if(msg)
        strcpy(msg,errorMsg_.str().c_str());
    strncpy(szErrMsg,errorMsg_.str().c_str(),sizeof(szErrMsg)-1);
    return szErrMsg;
}
ks_reader_dev_t *CardReaderManager::getReaderParaByNo(int no) {
    int i;
    assert(no >=1 && no <= MAX_READER);

    for(i = 0; i < CardTypeManager::instance()->getCardTypeCount(); ++i) {
        if(cardTypeReaderNo_[i] == no) {
            return &cardTypeReaderPara_[i];
        }
    }
    return NULL;
}

ks_device_op_t *CardReaderManager::getReaderByIdx(int idx) {
    assert(idx >= 0  && idx < this->getReaderCount());
    return &reader_[idx];
}

ks_device_op_t *CardReaderManager::getReaderByNo(size_t no) {
    assert(no > 0  && no <= this->getReaderCount());
    return &reader_[no-1];
}
void CardReaderManager::setReaderPortByNo(int no,int port,int baud) {
    int i;
    for(i = 0; i < CardTypeManager::instance()->getCardTypeCount(); ++i) {
        if(cardTypeReaderNo_[i] == no) {
            ks_reader_dev_t * para = &this->cardTypeReaderPara_[i];
            para->port = port;
            para->baud = baud;
        }
    }
    ks_device_op_t *dev = this->getReaderByNo(no);
    for(i = 0; i < MAX_READER_TYPE; ++i) {
        if(readerNo_[i] == no) {
            readerPara_[i].port = port;
            readerPara_[i].baud = baud;
        }
    }
}

ks_reader_dev_t *CardReaderManager::getPSAMReaderPara() {
    return &readerPara_[ks_cardtype_base::RT_PSAM];
}
ks_reader_dev_t *CardReaderManager::getKeyCardReaderPara() {
    return &readerPara_[ks_cardtype_base::RT_KEYCARD];
}
int CardReaderManager::findReaderPortAndBaud(int no,int &port,int &baud) {
    int i;
    for(i = 0; i < MAX_READER_TYPE; ++i) {
        ks_reader_dev_t *para = &readerPara_[i];
        if(para->no == no) {
            port = para->port;
            baud = para->baud;
            return 0;
        }
    }
    for(i = 0; i < CardTypeManager::MAX_CARDTYPE; ++i) {
        ks_reader_dev_t *para = &cardTypeReaderPara_[i];
        if(para->no == no) {
            port = para->port;
            baud = para->baud;
            return 0;
        }
    }
    return -1;
}
int CardReaderManager::doOpenPort(int no,int port,int baud) {
    int i,ret,p,b;
    ks_reader_dev_t para;
    ks_device_op_t *op;
    memset(&para,0,sizeof(para));
    for(i = 0; i < this->getReaderCount(); ++i) {
        op = &reader_[i];
        if(readerOpen_[i] == 1) {
            CLog::GetObj().WriteTime()<<__FILE__<<"("<<__LINE__<<") No."<<i<<"读卡器端口已打开\n";
            continue;
        }
        if(i + 1 == no) {
            if(port == 0) {
                if(findReaderPortAndBaud(i+1,p,b)==0) {
                    para.port = p;
                    para.baud = b;
                    if(p == 100)
                        para.devtype = KS_READER_USB;
                    else
                        para.devtype = KS_READER_COM;
                    ret = op->open_device(&para);
                    if(ret) {
                        //setErrorMsg(op->GetErrMsg(NULL),"打开主读卡器端口失败");
                        TRACE2_LOG(("打开主读卡器端口失败,port[%d]",para.port));
                        return -1;
                    }
                    readerOpen_[i] = 1;
                    op->beep(&para);
                } else {
                    TRACE_LOG("主读卡器端口未配置,打开失败");
                    return -1;
                }
            } else {
                para.port = port;
                para.baud = baud;
                if(port == 100)
                    para.devtype = KS_READER_USB;
                else
                    para.devtype = KS_READER_COM;
                ret = op->open_device(&para);
                if(ret) {
                    TRACE2_LOG(("打开主读卡器端口失败,port[%d]",para.port));
                    return -1;
                }
                this->setReaderPortByNo(no,port,baud);
                op->beep(&para);
                readerOpen_[i] = 1;
            }
        } else {
            if(findReaderPortAndBaud(i+1,p,b)==0) {
                para.port = p;
                para.baud = b;
                if(p == 100)
                    para.devtype = KS_READER_USB;
                else
                    para.devtype = KS_READER_COM;
                ret = op->open_device(&para);
                if(ret) {
                    TRACE2_LOG(("打开附属读卡器端口失败,port[%d]",para.port));
                    return -1;
                }
                readerOpen_[i] = 1;
                op->beep(&para);
            } else {
                TRACE_LOG("附属读卡器端口未配置,打开失败");
                return -1;
            }
        }
    }
    return 0;
}
int CardReaderManager::openPort(int no,int port,int baud) {
    if(m_bPortOpen) {
        CLog::GetObj().WriteTime()<<__FILE__<<"("<<__LINE__<<")端口已打开\n";
        TRACE_LOG("端口已打开");
        return  0;
    }
    CLog::GetObj().WriteTime()<<__FILE__<<"("<<__LINE__<<")打开端口\n";
    int ret = doOpenPort(no,port,baud);
    if(ret) {
        CLog::GetObj().WriteTime()<<__FILE__<<"("<<__LINE__<<")端口打开失败:"<<this->getErrorMsg(NULL)<<"\n";
        setErrorMsg("读卡器端口打开失败");
        return ret;
    }
    int i;
    ks_cardtype_base *c;
    for(i = 0; i < CardTypeManager::instance()->getCardTypeCount(); ++i) {
        c = CardTypeManager::instance()->getCardTypeByIdx(i);
        ret = c->OpenPort();
        if(ret) {
            setErrorMsg("调用卡类型库OpenPort失败");
            return ret;
        }
    }
    m_bPortOpen=1;
    return 0;
}
void CardReaderManager::closePort() {
    CLog::GetObj().WriteTime()<<__FILE__<<"("<<__LINE__<<")关闭端口\n";
    int i;
    for(i = 0; i < this->getReaderCount(); ++i) {
        ks_reader_dev_t& para = readerPara_[i];
        ks_device_op_t& op = reader_[i];
        if(readerOpen_[i] == 1)
            op.close_device(&para);
        readerOpen_[i] = 0;
    }
    m_bPortOpen=0;
}
int CardReaderManager::beep() {
    int i;
    i = beepReader_ - 1;
    ks_reader_dev_t& para = readerPara_[i];
    ks_device_op_t& op = reader_[i];
    if(readerOpen_[i] == 1) {
        op.beep(&para);
    }
    return 0;
}
int CardReaderManager::beeperr() {
    int i;
    i = beepReader_ - 1;
    ks_reader_dev_t& para = readerPara_[i];
    ks_device_op_t& op = reader_[i];
    if(readerOpen_[i] == 1) {
        op.beeperr(&para);
    }
    return 0;
}