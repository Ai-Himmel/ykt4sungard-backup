/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户止付、解付
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

int F846335(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    des2src(pAccTrans->trans.opercode,rPack->semp);
    char stoppayflag[2]="";
    stoppayflag[0]=rPack->sstatus1[0];
    if(stoppayflag[0]=='1')
        pAccTrans->trans.transcode=TC_EACCSTOPPAY;
    else
        pAccTrans->trans.transcode=TC_EACCUNSTOPPAY;
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
    T_t_netacc tNetAcc;
    memset(&tNetAcc,0,sizeof(tNetAcc));
    ret=DB_t_netacc_read_lock_by_c0_and_accno(trans.eaccno,&tNetAcc);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_EACCNO;
        else
            return E_DB_ACCOUNT_R;
    }
    if(tNetAcc.status[0]!=STATUS_NORMAL) {
        DB_t_netacc_free_lock_by_c0();
        return E_EACCNO_LOGOUT;
    }
    if(stoppayflag[0]=='1') {
        if(tNetAcc.stoppayflag[0]=='1') {
            DB_t_netacc_free_lock_by_c0();
            return E_EACC_STOPPAY;
        }
        sprintf(trans.remark,"客户[%s]电子帐户[%s]止付",tNetAcc.accname,tNetAcc.accno);
    } else {
        if(tNetAcc.stoppayflag[0]=='0') {
            DB_t_netacc_free_lock_by_c0();
            return E_EACC_NO_STOPPAY;
        }
        sprintf(trans.remark,"客户[%s]电子帐户[%s]取消止付",tNetAcc.accname,tNetAcc.accno);
    }
    tNetAcc.stoppayflag[0]=stoppayflag[0];
    ret=DB_t_netacc_update_lock_by_c0(&tNetAcc);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_CARDACCNO;
        else
            return E_DB_ACCOUNT_U;
    }
    SetCol(handle,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);
    des2src(outPack->sdate3,pAccTrans->trans.accdate);
    des2src(outPack->semp,trans.opercode);
    outPack->lwithdraw_flag=trans.termid;
    outPack->lserial1=trans.termseqno;
    strcpy(outPack->vsmess,trans.remark);
    strcat(outPack->vsmess,"成功");
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}
