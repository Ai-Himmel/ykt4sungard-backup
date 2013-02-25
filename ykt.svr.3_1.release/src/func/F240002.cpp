/* --------------------------------------------
 * 程序名称: F240002.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存转账后台模拟入账交易
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"

int F240002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {

    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    pAccTrans->trans.transcode=TC_BANKTRANS;
    TRANS& trans=pAccTrans->trans;
    trans.termid=atoi(rPack->sorder2);
    ret=pAccTrans->InitTrans();
    if(ret)
        return ret;
    trans.inputamt = rPack->lvol5/100.0;
    trans.unusedamt=trans.inputamt;
    trans.cardflag=1;
    trans.usecardflag=1;
    trans.cardbefbal=rPack->lvol6/100.00;
    trans.dpscnt=rPack->lvol1+1;
    trans.cardaftbal=trans.cardbefbal;
    //转账不允许转小数金额
    if((rPack->lvol5)%100>0) {
        writelog(LOG_ERR,"trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
        strcpy(szMsg,"转账金额必须是整数");
        return E_TRANS_TRANSMONEY_OUTRANGE;
    }
    if(rPack->lvol5<1) {
        writelog(LOG_ERR,"trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
        strcpy(szMsg,"转账金额不能为0");
        return E_TRANS_TRANSMONEY_OUTRANGE;
    }
    T_t_account		tAccount;		//帐户表
    T_t_card		card;

    memset(&tAccount,0,sizeof(tAccount));
    memset(&card,0,sizeof(card));


    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);


    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_LVOL2,F_LSERIAL0,F_SNAME2,0);


    //判断设备是否登陆
    if(0!=device_login_yes_or_no(trans.termid)) {
        writelog(LOG_ERR,"Device don't login");
        return E_TRANS_TERM_NOLOGIN;
    }
    trans.cardno=atoi(rPack->sserial0);
    ret=pAccTrans->CheckAcc(&card,&tAccount);
    if(ret)
        return ret;
    if(amtcmp(trans.cardbefbal-tAccount.balance,MAXAMT_CARDGTACC)>=0) {
        writelog(LOG_ERR,"cardbefbal[%.2lf]account balance[%.2lf]",trans.cardbefbal,tAccount.balance);
        return ERRIF_CARDBAL_EXCEPT;
    }
    double CardMaxBal=0;
    ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
    if(ret)
        return ret;
    if(amtcmp(trans.inputamt+trans.cardbefbal,CardMaxBal)>0)
        return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);
    trans.feetype=card.feetype;
    trans.cardtype=card.cardtype;
    trans.custid=card.custid;
    des2src(trans.cardaccno,tAccount.accno);		//贷方帐户,持卡人账户
    des2src(trans.draccno,rPack->sstation0);		//借方帐号，由前置机上传
    ret=pAccTrans->doFeeTrans();
    if(ret)
        return ret;
    ret=pAccTrans->doMainTrans();
    if(ret)
        return ret;
    ret=pAccTrans->doTransEnd();
    if(ret)
        return ret;
    //业务结束后，回滚事务
    ret=db_rollback();
    if(ret) {
        writelog(LOG_ERR,"db_rollback error,error code=[%d]",ret);
        return E_DB_ROLLBACK;
    }
    //重新取流水号
    ret=pAccTrans->GetTermSeqno();
    if(ret) {
        writelog(LOG_ERR,"GetTermSeqno error,error code=[%d]",ret);
        return ret;
    }
    T_t_transdtl transdtl;
    memset(&transdtl,0,sizeof(transdtl));

    des2src(transdtl.transdate,trans.transdate);
    des2src(transdtl.transtime,trans.transtime);
    strcpy(transdtl.accdate,trans.accdate);
    strcpy(transdtl.acctime,trans.acctime);
    transdtl.termid=trans.termid;
    transdtl.termseqno=trans.termseqno;
    transdtl.transcode=trans.transcode;
    transdtl.paytype=trans.fundtype;
    des2src(transdtl.voucherno,trans.voucherno);
    transdtl.cardno=trans.cardno;
    transdtl.purseno=trans.purseno;
    transdtl.transflag=TF_DPS;
    transdtl.cardcnt=trans.dpscnt;
    transdtl.cardbefbal=trans.cardbefbal;
    transdtl.amount=trans.totaltransamt;
    transdtl.managefee=trans.totalfeeamt;
    transdtl.cardaftbal=trans.cardaftbal;
    transdtl.custid=card.custid;
    //transdtl.sysid= rPack->lvol2;
    transdtl.exttype=EXTTYPE_BANKCARD;
    des2src(transdtl.extdata,rPack->scust_auth);
    des2src(transdtl.showcardno,card.showcardno);
    transdtl.status[0]=DTLSTATUS_FAIL;
    ret=GetNewRefno(transdtl.refno);
    if(ret) {
        ERRTIP("取交易参考号失败");
        return ret;
    }
    GetCustBaseInfoByCustID(card.custid,transdtl.custname,transdtl.stuempno,NULL);
    ret=DB_t_transdtl_add(&transdtl);
    if(ret) {
        if(DB_REPEAT==ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }
    char sMsg[255]="";
    char sDebugMsg[255]="";
    sprintf(sDebugMsg,"流水号:%d ",trans.termseqno);
    sprintf(sMsg,"充值前卡余额:%.2lf 转帐后卡余额:%.2lf ",trans.cardbefbal,trans.cardaftbal);
    strcat(sDebugMsg,sMsg);
    writelog(LOG_DEBUG,sDebugMsg);

    des2src(out_pack->sname2,transdtl.refno);
    out_pack->lserial0=trans.termseqno;
    out_pack->damt0=trans.cardaftbal;
    out_pack->damt1=transdtl.amount;
    out_pack->damt2=transdtl.managefee;
    out_pack->lvol1=transdtl.termseqno;
    out_pack->lvol2=D2I(trans.cardaftbal*100);

    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
}


