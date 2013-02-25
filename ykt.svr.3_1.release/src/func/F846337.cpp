/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户密码修改
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

int F846337(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    des2src(pAccTrans->trans.opercode,rPack->semp);
    pAccTrans->trans.transcode=TC_EACCPWDUPD;
    ret=pAccTrans->InitTrans();
    if(ret)
        return ret;
    TRANS& trans=pAccTrans->trans;

    des2src(trans.eaccno,rPack->sbank_acc);
    if(!strlen(trans.eaccno))
        return E_INPUTNULL_ACCNO;

    char in_oldpwd_plain[65]="";
    char db_oldpwd_plain[65]="";
    char oldpwd[65]="";
    char newpwd[65]="";
    char seedkey[65]="";
    des2src(oldpwd,rPack->snote);
    if(!strlen(oldpwd))
        return E_PWD_NULL;
    des2src(newpwd,rPack->snote2);
    if(!strlen(newpwd))
        return E_PWD_NULL;
    //取帐户信息
    ret=GetSysParaVal(GLOBLE_SYSPARA_STATIC_KEY,seedkey);
    if(ret)
        return ret;
    ret=decrypt_elec_card_pwd(0,seedkey,oldpwd,in_oldpwd_plain);
    if(ret) {
        writelog(LOG_ERR,"oldpwd[%s]",oldpwd);
        return E_PWD_DECRYPT;	//去帐户信息
    }
    T_t_netacc eaccount;
    memset(&eaccount,0,sizeof(eaccount));
    ret=DB_t_netacc_read_lock_by_c0_and_accno(trans.eaccno,&eaccount);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_DB_ACCOUNT_N;
        else
            return E_DB_ACCOUNT_R;
    }
    if(eaccount.status[0]!=STATUS_NORMAL) {
        DB_t_netacc_free_lock_by_c0();
        return E_EACCNO_LOGOUT;
    }
    ret=decrypt_elec_card_pwd(0,seedkey,eaccount.accpwd,db_oldpwd_plain);
    if(ret) {
        writelog(LOG_ERR,"crypt ret[%d]:in_pwd[%s]db_pwd[%s],plain:in_pwd[%s]db_pwd[%s]",ret,oldpwd,eaccount.accpwd,in_oldpwd_plain,db_oldpwd_plain);
        DB_t_netacc_free_lock_by_c0();
        return E_PWD_DECRYPT;
    }
    if(strcmp(in_oldpwd_plain,db_oldpwd_plain)!=0) {
        writelog(LOG_ERR,"crypt:in_pwd[%s]db_pwd[%s],plain:in_pwd[%s]db_pwd[%s]",oldpwd,eaccount.accpwd,in_oldpwd_plain,db_oldpwd_plain);
        DB_t_netacc_free_lock_by_c0();
        return E_EACCPWD;
    }
    des2src(eaccount.accpwd,newpwd);
    ret=DB_t_netacc_update_lock_by_c0(&eaccount);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_EACCNO;
        else
            return E_DB_ACCOUNT_U;
    }
    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);
//	des2src(outPack->sdate3,pAccTrans->sysPara.sSettleDate);
//	des2src(outPack->semp,trans.opercode);
//	outPack->lwithdraw_flag=trans.termid;
//	outPack->lserial1=trans.termseqno;
    sprintf(outPack->vsmess,"客户[%s]电子账户密码修改成功",eaccount.accname);
    des2src(trans.remark,outPack->vsmess);
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}

