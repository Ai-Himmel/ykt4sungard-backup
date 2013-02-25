/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户销户
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "acctrans.h"

static int doAccount(TRANS& trans) {
    int ret=0;
    T_t_netacc eaccount;

    memset(&eaccount,0,sizeof(eaccount));

    ret=DB_t_netacc_read_lock_by_c0_and_accno(trans.eaccno,&eaccount);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_EACCNO;
        else
            return E_DB_ACCOUNT_R;
    }
    if(eaccount.status[0]!=STATUS_NORMAL) {
        DB_t_netacc_free_lock_by_c0();
        return E_EACCNO_LOGOUT;
    }
    if(amtcmp(eaccount.balance,0)!=0) {
        writelog(LOG_ERR,"balance[%d]",eaccount.balance);
        DB_t_netacc_free_lock_by_c0();
        return E_CARDACC_BALANCE_NOZERO;
    }
    eaccount.status[0]=STATUS_DELETE;
    strcpy(eaccount.closedate,trans.transdate);
    ret=DB_t_netacc_update_lock_by_c0(&eaccount);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_EACCNO;
        else
            return E_DB_ACCOUNT_U;

    }
    return 0;
}
static int doCustomer(int custid,T_t_customer& tCustomer) {
    int ret=0;
    ret=DB_t_customer_read_lock_by_cur_and_custid(custid,&tCustomer);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_CUSTOMER;
        else
            return E_DB_CUSTOMER_R;
    }
    if(tCustomer.status[0]!=STATUS_NORMAL)
        return E_CUSTOMER_LOGOUT;
    tCustomer.eaccflag[0]='0';
    des2src(tCustomer.lastsaved,CAccTrans::getInstance()->trans.sysdatetime);
    ret=DB_t_customer_update_lock_by_cur(&tCustomer);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_CUSTOMER;
        else
            return E_DB_CUSTOMER_U;
    }
    return 0;
}

int F846332(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    des2src(pAccTrans->trans.opercode,rPack->semp);
    pAccTrans->trans.transcode=TC_EACCCLOSE;
    ret=pAccTrans->InitTrans();
    if(ret)
        return ret;
    TRANS& trans=pAccTrans->trans;

    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);

    SetCol(handle,0);

    des2src(trans.eaccno,rPack->sbank_acc);
    if(!strlen(trans.eaccno))
        return E_INPUTNULL_ACCNO;
    //去帐户信息
    T_t_netacc eaccount;
    memset(&eaccount,0,sizeof(eaccount));
    ret=DB_t_netacc_read_by_accno(trans.eaccno,&eaccount);
    if(ret) {
        writelog(LOG_ERR,"accno[%s]",trans.eaccno);
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_EACCNO;
        else
            return E_DB_ACCOUNT_R;
    }
    if(eaccount.status[0]!=STATUS_NORMAL) {
        return E_CARDACC_LOGOUT;
    }
    char seedkey[33]="";
    char inpwd_crypt[65]="";
    char inpwd_plain[65]="";
    char dbpwd_plain[65]="";
    des2src(inpwd_crypt,rPack->snote2);
    if(!strlen(inpwd_crypt))
        return E_PWD_NULL;
    ret=GetSysParaVal(GLOBLE_SYSPARA_STATIC_KEY,seedkey);
    if(ret)
        return ret;
    ret=decrypt_elec_card_pwd(0,seedkey,inpwd_crypt,inpwd_plain);
    if(ret)
        return	E_EACCPWD;
    ret=decrypt_elec_card_pwd(0,seedkey,eaccount.accpwd,dbpwd_plain);
    if(ret)
        return E_PWD_DECRYPT;
    if(strcmp(inpwd_plain,dbpwd_plain)!=0)
        return E_EACCPWD;
    //检查客户
    T_t_customer tCustomer;
    memset(&tCustomer,0,sizeof(tCustomer));
    ret=doCustomer(eaccount.custid,tCustomer);
    if(ret)
        return ret;
    //	创建账号
    pAccTrans->trans.custid=eaccount.custid;
    pAccTrans->trans.inputamt=eaccount.balance;
    trans.unusedamt = trans.inputamt;
    strcpy(pAccTrans->trans.eaccno,eaccount.accno);
    ret=pAccTrans->doTrans();
    if(ret)
        return ret;
    //注销帐户
    ret=doAccount(trans);
    if(ret)
        return ret;
    SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);
    des2src(outPack->sdate3,pAccTrans->trans.accdate);
    des2src(outPack->semp,trans.opercode);
    outPack->lwithdraw_flag=trans.termid;
    outPack->lserial1=trans.termseqno;
    sprintf(outPack->vsmess,"客户[%s]电子钱包销户成功",eaccount.accname);
    strcat(outPack->vsmess,pAccTrans->remark.c_str());
    des2src(trans.remark,outPack->vsmess);
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}

