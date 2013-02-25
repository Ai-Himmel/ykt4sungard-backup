///////////////////////////////////////////////////////////////////////////////
////
#include "std.h"
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <wx/snglinst.h>
#include <wx/aboutdlg.h>

#include "resource.h"
#include "kscarddaemondlg.h"
#include "daemonsvr.h"
#include "kscarddaemon.h"
#include "dbhandler.h"
#include "svrrequest.h"
#include "syncthr.h"
//////////////////////////////////////////////////////////////////////////////
KsCardProcessor* KsCardProcessor::instance_ = NULL;
KsCardProcessor* KsCardProcessor::instance() {
    if(NULL == instance_) {
        instance_ = new KsCardProcessor;
    }
    return instance_;
}
void KsCardProcessor::FreeAll() {
    if(NULL != instance_) {
        delete instance_;
        instance_ = NULL;
    }
}

KsCardProcessor::KsCardProcessor() {
    requestHandler_.clear();
    //transdb_.Open(wxGetApp().dbpath_);
    //infodb_.Open(wxGetApp().dbpath_);
}
KsCardProcessor::~KsCardProcessor() {
    freeHandler();
}
TransDB& KsCardProcessor::GetTransDB() {

    return transdb_;
}
InfoDB& KsCardProcessor::GetInfoDB() {
    return infodb_;
}

int KsCardProcessor::ProcessRequest(KsCardMsg &req,KsCardMsg &resp) {
    REQUEST_HANDLER_MAP_TYPE::iterator iter;
    iter = requestHandler_.find(req.MsgType());
    if(iter != requestHandler_.end()) {
        KsCardRequestHandler* handler = iter->second;
        if(NULL == handler)
            return -2;
        resp.SetMsgType(req.MsgType());
        return handler->ProcessRequest(req,resp);
    }
    return -2;
}
int KsCardProcessor::RegisterRequest(const std::string &msgtype,KsCardRequestHandler *handler) {
    REQUEST_HANDLER_MAP_TYPE::iterator iter;
    iter = requestHandler_.find(msgtype);
    if(iter != requestHandler_.end()) {
        return -1;
    }
    requestHandler_.insert(REQUEST_HANDLER_MAP_TYPE::value_type(msgtype,handler));
    return 0;
}
void KsCardProcessor::freeHandler() {
    REQUEST_HANDLER_MAP_TYPE::iterator iter;
    for(iter = requestHandler_.begin(); iter != requestHandler_.end(); ++iter) {
        KsCardRequestHandler* handler = iter->second;
        if(NULL != handler) {
            delete handler;
        }
    }
    requestHandler_.clear();
}
std::string KsCardProcessor::CalcAuthCode(int termid) {
    time_t t;
    t = time(NULL);
    srand(t);
    int r = rand();
    r += termid;
    char temp[20]= {0};
    sprintf(temp,"%08X",r);
    this->authcode_ = temp;
    return this->authcode_;
}
int KsCardProcessor::CheckAuthCode(const std::string &authcode) {
    return (authcode == this->authcode_) ? 0 : -1;
}

///////////////////////////////////////////////////////////////////////////////
KsCardRequestHandler::KsCardRequestHandler() {
}
KsCardRequestHandler::~KsCardRequestHandler() {
}

///////////////////////////////////////////////////////////////////////////////
class KsCardLoginHandler : public KsCardRequestHandler {
public:
    KsCardLoginHandler():KsCardRequestHandler() {
    }
    virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp) {
        TransDB &trans = KsCardProcessor::instance()->GetTransDB();
        int termid = 0,termseqno = 0,ret;

        if(trans.IsOpen()) {
            resp.SetIntPara("data.retcode",EKS_DATABASE);
        } else {
            if(!req.GetIntPara("data.termid",&termid))
                return -1;

            ret = KsYktSvrUtil::LoginDevice(req);
            if(ret == -1) {
                resp.SetIntPara("data.retcode",EKS_LOGIN);
                resp.SetStrPara("data.retmsg","签到请求错误");
            } else if(ret == 0 || ret == -2) { // 成功，或通讯故障
                int createnew = (ret == -2) ? 0 : 1;
                if(trans.Login(req,createnew)) {
                    resp.SetIntPara("data.retcode",EKS_SYSTEM);
                    resp.SetStrPara("data.retmsg","更新本地数据错误");
                } else {
                    std::string authcode = KsCardProcessor::instance()->CalcAuthCode(termid);
                    resp.SetStrPara("authcode",authcode);
                    resp.SetIntPara("data.retcode",EKS_SUCCESS);
                    req.GetIntPara("data.termseqno",&termseqno);
                    resp.SetIntPara("data.termseqno",termseqno);

                    int shopid = 0;
                    req.GetIntPara("data.shopid",&shopid);
                    resp.SetIntPara("data.shopid",shopid);

                    std::string shopname;
                    req.GetStrPara("data.shopname",shopname);
                    resp.SetStrPara("data.shopname",shopname);
                }
            } else {
                resp.SetIntPara("data.retcode",EKS_SYSTEM);
                resp.SetStrPara("data.retmsg","系统异常");
            }
        }
        return 1;
    }
};
REGISTER_HANDLER("login",KsCardLoginHandler);

class KsCardInit4Purchase : public KsCardRequestHandler {
public:
    KsCardInit4Purchase():KsCardRequestHandler() {
    }
    virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp) {
        TransDB &trans = KsCardProcessor::instance()->GetTransDB();
        InfoDB &infodb = KsCardProcessor::instance()->GetInfoDB();
        std::string authcode;
        std::stringstream errmsg;
        int retcode = EKS_SUCCESS;
        if(!req.GetStrPara("authcode",authcode))
            return -1;
        if(KsCardProcessor::instance()->CheckAuthCode(authcode)) {
            errmsg<<"授权码错误";
            retcode = EKS_AUTHCODEERR;
        } else {
            if(trans.IsOpen() || infodb.IsOpen()) {
                errmsg<<"不能打开数据库";
                retcode = EKS_DATABASE;
            } else {
                int ret;
                CardVerInfo cardver;
                std::string cardverno;
                if(!req.GetStrPara("data.cardverno",cardverno)) {
                    return -1;
                }
                cardver.cardverno_ = cardverno;
                if(!req.GetIntPara("data.cardno",&(cardver.cardno_))) {
                    return -1;
                }
                ret = infodb.IsBlackCard(cardver);
                if(ret) {
                    errmsg<<"读取黑名单失败";
                    retcode = EKS_DATABASE;
                } else {
                    if(cardver.flag_ != CARDSTATUS_NORMAL) {
                        errmsg<<"卡已挂失";
                        resp.SetStrPara("data.cardstatus","L");
                        retcode = EKS_CARDLOST;
                        req.SetIntPara("data.status",DTLST_LOCKCARD);
                    } else {
                        req.SetIntPara("data.status",DTLST_INIT);
                    }
                    req.SetIntPara("data.transcode",TC_PURCHASE);
                    if(trans.CanDoTrans()) {
                        retcode = EKS_UNUPLDSERI;
                        errmsg<<"脱机流水笔数超过上限";
                    } else if((ret = trans.Init4Purchase(req))) {
                        errmsg<<"写流水失败";
                        retcode = EKS_DATABASE;
                    } else {
                        std::string value;
                        if(!req.GetStrPara("data.termid",value))
                            return -1;
                        resp.SetStrPara("data.termid",value);

                        if(!req.GetStrPara("data.termseqno",value))
                            return -1;
                        resp.SetStrPara("data.termseqno",value);

                        resp.SetStrPara("data.cardstatus","N");
                        errmsg<<"成功";
                    }
                }
            }
        }
        resp.SetIntPara("data.retcode",retcode);
        resp.SetStrPara("data.retmsg",errmsg.str());
        return 1;
    }
};
REGISTER_HANDLER("init4purchase",KsCardInit4Purchase);

class KsCardDebit4Purchase : public KsCardRequestHandler {
public:
    KsCardDebit4Purchase():KsCardRequestHandler() {
    }
    virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp) {
        TransDB &trans = KsCardProcessor::instance()->GetTransDB();
        std::string authcode;
        std::stringstream errmsg;
        int retcode = EKS_SYSTEM;
        if(!req.GetStrPara("authcode",authcode))
            return -1;
        if(KsCardProcessor::instance()->CheckAuthCode(authcode)) {
            errmsg<<"授权码错误";
            retcode = EKS_AUTHCODEERR;
        } else {
            if(trans.IsOpen()) {
                errmsg<<"不能打开数据库";
                retcode = EKS_DATABASE;
            } else {
                int ret = trans.Debit4Purchase(req);
                if(ret) {
                    errmsg<<"写流水失败";
                    retcode = EKS_DATABASE;
                } else {
                    std::string value;
                    if(!req.GetStrPara("data.termid",value))
                        return -1;
                    resp.SetStrPara("data.termid",value);

                    if(!req.GetStrPara("data.termseqno",value))
                        return -1;
                    resp.SetStrPara("data.termseqno",value);
                    errmsg<<"成功";
                    retcode = EKS_SUCCESS;
                }
            }
        }
        resp.SetIntPara("data.retcode",retcode);
        resp.SetStrPara("data.retmsg",errmsg.str());
        return 1;
    }
};
REGISTER_HANDLER("debit4purchase",KsCardDebit4Purchase);


class KsCardChkCardHandler : public KsCardRequestHandler {
public:
    KsCardChkCardHandler():KsCardRequestHandler() {
    }
    virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp) {
        InfoDB &infodb = KsCardProcessor::instance()->GetInfoDB();
        int cardno,ret;
        std::string cardverno,authcode;
        req.GetStrPara("authcode",authcode);
        if(KsCardProcessor::instance()->CheckAuthCode(authcode)) {
            resp.SetStrPara("data.retmsg","授权码错误");
            resp.SetIntPara("data.retcode",EKS_AUTHCODEERR);
            return 1;
        }

        if(infodb.IsOpen()) {
            resp.SetIntPara("data.retcode",EKS_DATABASE);
            resp.SetStrPara("data.retmsg","连接数据库错误");
        } else {
            if(!req.GetIntPara("data.cardno",&cardno))
                return -1;
            if(!req.GetStrPara("data.cardverno",cardverno))
                return -1;

            CardVerInfo cardver;
            cardver.cardno_ = cardno;
            cardver.cardverno_ = cardverno;
            ret = infodb.IsBlackCard(cardver);
            if(ret)
                return ret;
            if(cardver.flag_ == CARDSTATUS_NORMAL) {
                resp.SetStrPara("data.cardstatus","0");
            } else {
                resp.SetStrPara("data.cardstatus","1");
            }
            resp.SetIntPara("data.retcode",0);
        }
        return 1;
    }
};
REGISTER_HANDLER("chkcard",KsCardChkCardHandler);

class KsCardHeartBeatHandler : public KsCardRequestHandler {
public:
    KsCardHeartBeatHandler():KsCardRequestHandler() {
    }
    virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp) {
        InfoDB &infodb = KsCardProcessor::instance()->GetInfoDB();
        TransDB &transdb = KsCardProcessor::instance()->GetTransDB();
        std::string authcode;

        req.GetStrPara("authcode",authcode);
        if(KsCardProcessor::instance()->CheckAuthCode(authcode)) {
            resp.SetStrPara("data.retmsg","授权码错误");
            resp.SetIntPara("data.retcode",EKS_AUTHCODEERR);
            return 1;
        }

        if(infodb.IsOpen() || transdb.IsOpen()) {
            resp.SetIntPara("data.retcode",EKS_DATABASE);
            resp.SetStrPara("data.retmsg","连接数据库错误");
        } else {
            resp.SetIntPara("data.retcode",0);
        }
        return 1;
    }
};
REGISTER_HANDLER("heartbeat",KsCardHeartBeatHandler);


class KsCardCancel4Purchase : public KsCardRequestHandler {
public:
    KsCardCancel4Purchase():KsCardRequestHandler() {
    }
    virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp) {
        TransDB &trans = KsCardProcessor::instance()->GetTransDB();
        InfoDB &infodb = KsCardProcessor::instance()->GetInfoDB();
        std::string authcode;
        std::stringstream errmsg;
        int retcode = EKS_SUCCESS;
        if(!req.GetStrPara("authcode",authcode))
            return -1;
        if(KsCardProcessor::instance()->CheckAuthCode(authcode)) {
            errmsg<<"授权码错误";
            retcode = EKS_AUTHCODEERR;
        } else if(KsSyncThr::instance()->IsOnline() && KsYktSvrUtil::ChkHeartBeat()) {
            errmsg<<"一卡通服务脱机";
            retcode = EKS_SYSTEM;
        } else {
            if(trans.IsOpen() || infodb.IsOpen()) {
                errmsg<<"不能打开数据库";
                retcode = EKS_DATABASE;
            } else {
                int ret;
                CardVerInfo cardver;
                std::string cardverno;
                if(!req.GetStrPara("data.cardverno",cardverno)) {
                    return -1;
                }
                cardver.cardverno_ = cardverno;
                if(!req.GetIntPara("data.cardno",&(cardver.cardno_))) {
                    return -1;
                }
                ret = infodb.IsBlackCard(cardver);
                if(ret) {
                    errmsg<<"读取黑名单失败";
                    retcode = EKS_DATABASE;
                } else {
                    if(cardver.flag_ != CARDSTATUS_NORMAL) {
                        errmsg<<"卡已挂失";
                        resp.SetStrPara("data.cardstatus","L");
                        retcode = EKS_CARDLOST;
                        req.SetIntPara("data.status",DTLST_LOCKCARD);
                    } else {
                        req.SetIntPara("data.transcode",TC_CANCELPURCHASE);
                        if((ret = trans.CancelTransDtl(req))) {
                            errmsg<<"写流水失败";
                            retcode = EKS_DATABASE;
                        } else {
                            std::string value;
                            if(!req.GetStrPara("data.termid",value))
                                return -1;
                            resp.SetStrPara("data.termid",value);

                            if(!req.GetStrPara("data.termseqno",value))
                                return -1;
                            resp.SetStrPara("data.termseqno",value);

                            int amount = 0;
                            req.GetIntPara("data.amount",&amount);
                            resp.SetIntPara("data.amount",amount);

                            req.GetIntPara("data.retcode",&retcode);
                        }
                    }
                }
            }
        }
        resp.SetIntPara("data.retcode",retcode);
        resp.SetStrPara("data.retmsg",errmsg.str());
        return 1;
    }
};
REGISTER_HANDLER("cancel4purchase",KsCardCancel4Purchase);
