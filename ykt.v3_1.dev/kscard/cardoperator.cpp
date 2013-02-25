#include "cardoperator.h"
#include "yktclt.h"

CardOperator::CardOperator(ks_cardtype_base *cardtype):
    cardtype_(cardtype),card_balance_(0),card_deposit_count_(0) {
    memset(account_date_,0,sizeof account_date_);
    memset(app_serial_no_,0,sizeof app_serial_no_);
}
CardOperator::~CardOperator() {
}
int CardOperator::Deposite(ST_TRANSPACK &pack) {
    // read card info
    char temp[64]= {0};
    cardtype_->SetFieldReadMode(CF_CARDBAL);
    cardtype_->SetFieldReadMode(CF_DPSCNT);
    cardtype_->SetFieldReadMode(CF_APPSERIALNO);

    int ret;
    ret = ks_readcard();
    if(ret) {
        ks_setlasterr("读写卡错误");
        return -1;
    }

    cardtype_->GetFieldVal(CF_CARDBAL,temp);
    card_balance_ = atoi(temp);
    cardtype_->GetFieldVal(CF_DPSCNT,temp);
    card_deposit_count_ = atoi(temp);
    cardtype_->GetFieldVal(CF_APPSERIALNO,app_serial_no_);

    if(card_balance_ != pack.nBefBalance
            || card_deposit_count_ != pack.nDpsCardCnt) {
        ks_setlasterr("卡当前余额与参数不一致");
        return -1;
    }

    // 圈存初始化请求
    ret = cardtype_->InitForTrans(&pack,ks_cardtype_base::TRNS_TYPE_LOAD);
    if(ret) {
        pack.cRetryFlag = 0;
        pack.cGetProveFlag = 0;
        return -1;
    }
    // 发起初始化后台请求
    ret = SendLoadInitial(pack);
    if(ret) {
        // ks_setlasterr("发送");
        return -1;
    }
    // 发起圈存确认请求,超时重试 3 次
    int retries = 3;
    char szMac2[9];
    while(retries-- > 0) {
        ret = SendLoadDebit(pack,szMac2);
        if(ret) {
            continue;
        }
        break;
    }
    if(retries < 0) {
        TRACE_LOG("圈存确认失败，请重试写卡");
        pack.cGetProveFlag = 1;
        return -1;
    }
    // 写卡余额
    strcpy(pack.sMac,szMac2);
    ret = cardtype_->DebitForTrans(&pack);
    if(ret) {
        if(pack.cGetProveFlag==1) {
            // need retry
            TRACE_LOG("更新卡余额失败");
            return -1;
        }
    }
    pack.nAftBalance = pack.nBefBalance + pack.nTransAmt;
    return 0;
}
int CardOperator::DepositeRetry(ST_TRANSPACK &pack) {
    // read card info
    char temp[64]= {0};
    cardtype_->SetFieldReadMode(CF_CARDBAL);
    cardtype_->SetFieldReadMode(CF_DPSCNT);
    cardtype_->SetFieldReadMode(CF_APPSERIALNO);
    int ret;
    ret = ks_readcard();
    if(ret) {
        ks_setlasterr("读写卡错误");
        return -1;
    }

    cardtype_->GetFieldVal(CF_CARDBAL,temp);
    card_balance_ = atoi(temp);
    cardtype_->GetFieldVal(CF_DPSCNT,temp);
    card_deposit_count_ = atoi(temp);
    cardtype_->GetFieldVal(CF_APPSERIALNO,app_serial_no_);

    if(card_balance_ != pack.nBefBalance
            || card_deposit_count_ != pack.nDpsCardCnt) {
        ks_setlasterr("卡当前余额与参数不一致");
        return -1;
    }

    // 圈存初始化请求
    ret = cardtype_->InitForTrans(&pack,ks_cardtype_base::TRNS_TYPE_LOAD);
    if(ret) {
        pack.cRetryFlag = 0;
        pack.cGetProveFlag = 0;
        return -1;
    }
    // 发起圈存重写卡请求,超时重试 3 次
    int retries = 3;
    char szMac2[9];
    while(retries-- > 0) {
        ret = SendRetry(pack,szMac2);
        if(ret) {
            continue;
        }
        break;
    }
    if(retries < 0) {
        TRACE_LOG("圈存确认失败，请重试写卡");
        pack.cGetProveFlag = 1;
        return -1;
    }
    // 写卡余额
    strcpy(pack.sMac,szMac2);
    ret = cardtype_->DebitForTrans(&pack);
    if(ret) {
        if(pack.cGetProveFlag==1) {
            // need retry
            TRACE_LOG("更新卡余额失败");
            return -1;
        }
    }
    pack.nAftBalance = pack.nBefBalance + pack.nTransAmt;
    return 0;
}
int CardOperator::DepositeCancel(ST_TRANSPACK &pack) {
    return -1;
}
int CardOperator::SendLoadInitial(ST_TRANSPACK &pack) {
    if(pack.nTransType != ks_cardtype_base::TRNS_TYPE_LOAD) {
        ks_setlasterr("交易类型错误，不是充值交易");
        return -1;
    }
    pack.cRetryFlag = 0;
    pack.cGetProveFlag = 0;
    KS_YKT_Clt clt;
    /*
    卡应用序列号	char(20)	scust_auth
    终端PSAM卡号	char(12)	sholder_ac_no
    终端PSAM卡流水号	int	lserial0
    终端交易日期	char(8)	sdate0
    终端交易时间	char(6)	stime0
    卡充值前次数	int	lvol1
    卡充值前余额	int	lvol2
    充值金额	int	lvol0
    卡随机数	char(8)	scust_auth2
    MAC1	char(8)	sholder_ac_no2
    */
    clt.SetStringFieldByName("scust_auth",app_serial_no_); // 应该是应用序列号
    clt.SetStringFieldByName("sname2",pack.sCardPhyID);
    clt.SetStringFieldByName("sholder_ac_no",pack.sTermno);
    clt.SetIntFieldByName("lserial0",pack.nTermSeqno);
    clt.SetStringFieldByName("sdate0",pack.sTransDate);
    clt.SetStringFieldByName("stime0",pack.sTransTime);
    clt.SetIntFieldByName("lvol1",pack.nDpsCardCnt);
    clt.SetIntFieldByName("lvol2",pack.nBefBalance);
    clt.SetIntFieldByName("lvol0",pack.nTransAmt);
    clt.SetStringFieldByName("scust_auth2",pack.sRandom);
    clt.SetStringFieldByName("sholder_ac_no2",pack.sMac);
    clt.SetStringFieldByName("semp",pack.sOperCode);
    clt.SetStringFieldByName("sstatus0","I");

    if(!clt.SendRequest(846801,10000)) {
        // TODO : 可能是超时
        char szMsg[512]= {0};
        char errmsg[512]= {0};
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
        ks_setlasterr(errmsg,clt.GetReturnCode());
        pack.cRetryFlag = 1;
        return -1;
    }
    int nRet;
    if((nRet = clt.GetReturnCode())!=0) {
        // 充值失败
        char szMsg[512];
        clt.GetReturnMsg(szMsg);
        ks_setlasterr(szMsg,nRet);
        return nRet;
    }
    clt.GetNextPackage();
    char szRefno[15]= {0};
    GET_PACK_STR(clt,"sphone",szRefno);
    if(strlen(szRefno) == 0) {
        ks_setlasterr("后台返回错误,未获取参考号");
        return -1;
    }
    strcpy(pack.sRefNo,szRefno);
    GET_PACK_STR(clt,"sdate3",account_date_);
    return 0;
}
int CardOperator::SendLoadDebit(ST_TRANSPACK &pack,char *sMac2) {
    if(pack.nTransType != ks_cardtype_base::TRNS_TYPE_LOAD) {
        ks_setlasterr("交易类型错误，不是充值交易");
        return -1;
    }
    pack.cRetryFlag = 0;
    pack.cGetProveFlag = 0;
    KS_YKT_Clt clt;
    /*
    卡应用序列号	char(20)	scust_auth
    终端PSAM卡号	char(12)	sholder_ac_no
    终端PSAM卡流水号	int	lserial0
    终端交易日期	char(8)	sdate0
    终端交易时间	char(6)	stime0
    卡充值前次数	int	lvol1
    卡充值前余额	int	lvol2
    充值金额	int	lvol0
    卡随机数	char(8)	scust_auth2
    MAC1	char(8)	sholder_ac_no2
    交易参考号
    */
    clt.SetStringFieldByName("scust_auth",app_serial_no_); // 应该是应用序列号
    clt.SetStringFieldByName("sname2",pack.sCardPhyID);
    clt.SetStringFieldByName("sholder_ac_no",pack.sTermno);
    clt.SetIntFieldByName("lserial0",pack.nTermSeqno);
    clt.SetStringFieldByName("sdate0",pack.sTransDate);
    clt.SetStringFieldByName("stime0",pack.sTransTime);
    clt.SetIntFieldByName("lvol1",pack.nDpsCardCnt);
    clt.SetIntFieldByName("lvol2",pack.nBefBalance);
    clt.SetIntFieldByName("lvol0",pack.nTransAmt);
    clt.SetStringFieldByName("scust_auth2",pack.sRandom);
    clt.SetStringFieldByName("sholder_ac_no2",pack.sMac);
    clt.SetStringFieldByName("sphone",pack.sRefNo);
    clt.SetStringFieldByName("sstatus0","C");
    clt.SetStringFieldByName("sdate3",account_date_);
    clt.SetStringFieldByName("semp",pack.sOperCode);

    if(!clt.SendRequest(846801,5000)) {
        // TODO : 可能是超时
        char szMsg[512]= {0};
        char errmsg[512]= {0};
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
        ks_setlasterr(errmsg,clt.GetReturnCode());
        pack.cRetryFlag = 1;
        return -1;
    }
    int nRet;
    if((nRet = clt.GetReturnCode())!=0) {
        // 充值失败
        char szMsg[512];
        clt.GetReturnMsg(szMsg);
        ks_setlasterr(szMsg,nRet);
        return nRet;
    }
    clt.GetNextPackage();
    char szRefno[15]= {0};
    GET_PACK_STR(clt,"sphone",szRefno);
    if(strcmp(szRefno,pack.sRefNo)!=0) {
        ks_setlasterr("确认时交易参考号错误");
        return -1;
    }
    char szMac2[9]= {0};
    GET_PACK_STR(clt,"scust_auth2",szMac2);
    strcpy(sMac2,szMac2);
    char host_date[9]= {0};
    char host_time[7]= {0};
    GET_PACK_STR(clt,"sdate0",host_date);
    GET_PACK_STR(clt,"stime0",host_time);
    strcpy(pack.sTransDate,host_date);
    strcpy(pack.sTransTime,host_time);
    return 0;
}

int CardOperator::SendRetry(ST_TRANSPACK &pack,char *sMac2) {
    if(pack.nTransType != ks_cardtype_base::TRNS_TYPE_LOAD) {
        ks_setlasterr("交易类型错误，不是充值交易");
        return -1;
    }
    if(strlen(pack.sRefNo)==0) {
        ks_setlasterr("交易参考号不能为空");
        return -1;
    }
    KS_YKT_Clt clt;
    clt.SetStringFieldByName("scust_auth",app_serial_no_); // 应该是应用序列号
    clt.SetStringFieldByName("sname2",pack.sCardPhyID);
    clt.SetStringFieldByName("sholder_ac_no",pack.sTermno);
    clt.SetIntFieldByName("lserial0",pack.nTermSeqno);
    clt.SetStringFieldByName("sdate0",pack.sTransDate);
    clt.SetStringFieldByName("stime0",pack.sTransTime);
    clt.SetIntFieldByName("lvol1",pack.nDpsCardCnt);
    clt.SetIntFieldByName("lvol2",pack.nBefBalance);
    clt.SetIntFieldByName("lvol0",pack.nTransAmt);
    clt.SetStringFieldByName("scust_auth2",pack.sRandom);
    clt.SetStringFieldByName("sholder_ac_no2",pack.sMac);
    clt.SetStringFieldByName("sphone",pack.sRefNo);
    clt.SetStringFieldByName("sdate3",pack.sTransDate); // 记账时间
    clt.SetStringFieldByName("semp",pack.sOperCode);


    if(!clt.SendRequest(846802,5000)) {
        // TODO : 可能是超时
        char szMsg[512]= {0};
        char errmsg[512]= {0};
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
        ks_setlasterr(errmsg,clt.GetReturnCode());
        pack.cRetryFlag = 1;
        return -1;
    }
    int nRet;
    if((nRet = clt.GetReturnCode())!=0) {
        // 充值失败
        char szMsg[512];
        clt.GetReturnMsg(szMsg);
        ks_setlasterr(szMsg,nRet);
        return nRet;
    }
    clt.GetNextPackage();
    char szRefno[15]= {0};
    GET_PACK_STR(clt,"sphone",szRefno);
    if(strcmp(szRefno,pack.sRefNo)!=0) {
        ks_setlasterr("确认时交易参考号错误");
        return -1;
    }
    char szMac2[9]= {0};
    GET_PACK_STR(clt,"scust_auth2",szMac2);
    strcpy(sMac2,szMac2);
    char host_date[9]= {0};
    char host_time[7]= {0};
    GET_PACK_STR(clt,"sdate0",host_date);
    GET_PACK_STR(clt,"stime0",host_time);
    strcpy(pack.sTransDate,host_date);
    strcpy(pack.sTransTime,host_time);
    return 0;
}