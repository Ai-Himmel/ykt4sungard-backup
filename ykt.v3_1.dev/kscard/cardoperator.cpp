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
        ks_setlasterr("��д������");
        return -1;
    }

    cardtype_->GetFieldVal(CF_CARDBAL,temp);
    card_balance_ = atoi(temp);
    cardtype_->GetFieldVal(CF_DPSCNT,temp);
    card_deposit_count_ = atoi(temp);
    cardtype_->GetFieldVal(CF_APPSERIALNO,app_serial_no_);

    if(card_balance_ != pack.nBefBalance
            || card_deposit_count_ != pack.nDpsCardCnt) {
        ks_setlasterr("����ǰ����������һ��");
        return -1;
    }

    // Ȧ���ʼ������
    ret = cardtype_->InitForTrans(&pack,ks_cardtype_base::TRNS_TYPE_LOAD);
    if(ret) {
        pack.cRetryFlag = 0;
        pack.cGetProveFlag = 0;
        return -1;
    }
    // �����ʼ����̨����
    ret = SendLoadInitial(pack);
    if(ret) {
        // ks_setlasterr("����");
        return -1;
    }
    // ����Ȧ��ȷ������,��ʱ���� 3 ��
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
        TRACE_LOG("Ȧ��ȷ��ʧ�ܣ�������д��");
        pack.cGetProveFlag = 1;
        return -1;
    }
    // д�����
    strcpy(pack.sMac,szMac2);
    ret = cardtype_->DebitForTrans(&pack);
    if(ret) {
        if(pack.cGetProveFlag==1) {
            // need retry
            TRACE_LOG("���¿����ʧ��");
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
        ks_setlasterr("��д������");
        return -1;
    }

    cardtype_->GetFieldVal(CF_CARDBAL,temp);
    card_balance_ = atoi(temp);
    cardtype_->GetFieldVal(CF_DPSCNT,temp);
    card_deposit_count_ = atoi(temp);
    cardtype_->GetFieldVal(CF_APPSERIALNO,app_serial_no_);

    if(card_balance_ != pack.nBefBalance
            || card_deposit_count_ != pack.nDpsCardCnt) {
        ks_setlasterr("����ǰ����������һ��");
        return -1;
    }

    // Ȧ���ʼ������
    ret = cardtype_->InitForTrans(&pack,ks_cardtype_base::TRNS_TYPE_LOAD);
    if(ret) {
        pack.cRetryFlag = 0;
        pack.cGetProveFlag = 0;
        return -1;
    }
    // ����Ȧ����д������,��ʱ���� 3 ��
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
        TRACE_LOG("Ȧ��ȷ��ʧ�ܣ�������д��");
        pack.cGetProveFlag = 1;
        return -1;
    }
    // д�����
    strcpy(pack.sMac,szMac2);
    ret = cardtype_->DebitForTrans(&pack);
    if(ret) {
        if(pack.cGetProveFlag==1) {
            // need retry
            TRACE_LOG("���¿����ʧ��");
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
        ks_setlasterr("�������ʹ��󣬲��ǳ�ֵ����");
        return -1;
    }
    pack.cRetryFlag = 0;
    pack.cGetProveFlag = 0;
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
    clt.SetStringFieldByName("scust_auth",app_serial_no_); // Ӧ����Ӧ�����к�
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
        // TODO : �����ǳ�ʱ
        char szMsg[512]= {0};
        char errmsg[512]= {0};
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"������ͨѶ����:%s,������:%d",szMsg,clt.GetReturnCode());
        ks_setlasterr(errmsg,clt.GetReturnCode());
        pack.cRetryFlag = 1;
        return -1;
    }
    int nRet;
    if((nRet = clt.GetReturnCode())!=0) {
        // ��ֵʧ��
        char szMsg[512];
        clt.GetReturnMsg(szMsg);
        ks_setlasterr(szMsg,nRet);
        return nRet;
    }
    clt.GetNextPackage();
    char szRefno[15]= {0};
    GET_PACK_STR(clt,"sphone",szRefno);
    if(strlen(szRefno) == 0) {
        ks_setlasterr("��̨���ش���,δ��ȡ�ο���");
        return -1;
    }
    strcpy(pack.sRefNo,szRefno);
    GET_PACK_STR(clt,"sdate3",account_date_);
    return 0;
}
int CardOperator::SendLoadDebit(ST_TRANSPACK &pack,char *sMac2) {
    if(pack.nTransType != ks_cardtype_base::TRNS_TYPE_LOAD) {
        ks_setlasterr("�������ʹ��󣬲��ǳ�ֵ����");
        return -1;
    }
    pack.cRetryFlag = 0;
    pack.cGetProveFlag = 0;
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
    ���ײο���
    */
    clt.SetStringFieldByName("scust_auth",app_serial_no_); // Ӧ����Ӧ�����к�
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
        // TODO : �����ǳ�ʱ
        char szMsg[512]= {0};
        char errmsg[512]= {0};
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"������ͨѶ����:%s,������:%d",szMsg,clt.GetReturnCode());
        ks_setlasterr(errmsg,clt.GetReturnCode());
        pack.cRetryFlag = 1;
        return -1;
    }
    int nRet;
    if((nRet = clt.GetReturnCode())!=0) {
        // ��ֵʧ��
        char szMsg[512];
        clt.GetReturnMsg(szMsg);
        ks_setlasterr(szMsg,nRet);
        return nRet;
    }
    clt.GetNextPackage();
    char szRefno[15]= {0};
    GET_PACK_STR(clt,"sphone",szRefno);
    if(strcmp(szRefno,pack.sRefNo)!=0) {
        ks_setlasterr("ȷ��ʱ���ײο��Ŵ���");
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
        ks_setlasterr("�������ʹ��󣬲��ǳ�ֵ����");
        return -1;
    }
    if(strlen(pack.sRefNo)==0) {
        ks_setlasterr("���ײο��Ų���Ϊ��");
        return -1;
    }
    KS_YKT_Clt clt;
    clt.SetStringFieldByName("scust_auth",app_serial_no_); // Ӧ����Ӧ�����к�
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
    clt.SetStringFieldByName("sdate3",pack.sTransDate); // ����ʱ��
    clt.SetStringFieldByName("semp",pack.sOperCode);


    if(!clt.SendRequest(846802,5000)) {
        // TODO : �����ǳ�ʱ
        char szMsg[512]= {0};
        char errmsg[512]= {0};
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"������ͨѶ����:%s,������:%d",szMsg,clt.GetReturnCode());
        ks_setlasterr(errmsg,clt.GetReturnCode());
        pack.cRetryFlag = 1;
        return -1;
    }
    int nRet;
    if((nRet = clt.GetReturnCode())!=0) {
        // ��ֵʧ��
        char szMsg[512];
        clt.GetReturnMsg(szMsg);
        ks_setlasterr(szMsg,nRet);
        return nRet;
    }
    clt.GetNextPackage();
    char szRefno[15]= {0};
    GET_PACK_STR(clt,"sphone",szRefno);
    if(strcmp(szRefno,pack.sRefNo)!=0) {
        ks_setlasterr("ȷ��ʱ���ײο��Ŵ���");
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