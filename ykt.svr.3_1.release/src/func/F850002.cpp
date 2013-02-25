/* --------------------------------------------
 * 创建日期: 2009-08-08
 * 程序作者:
 * 版本信息: 3.0.0.0
 * 程序功能:保存 写卡异常流水
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


int F850002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    CAccTrans *pAccTrans=CAccTrans::getInstance();

    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    memset(&aPack,0,sizeof(aPack));
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,F_SPHONE3,F_SADDR,0);


    int ret=0;
    T_t_refno tRefno;

    memset(&tRefno,0,sizeof(tRefno));
    T_t_exceptdtl exceptdtl;
    memset(&exceptdtl,0,sizeof(exceptdtl));

    des2src(exceptdtl.refno,rPack->sphone3);
    ret=DB_t_refno_read_by_refno(exceptdtl.refno,&tRefno);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_DB_REFNO_N;
        else
            return E_DB_REFNO_R;
    }

    des2src(exceptdtl.accdate,rPack->sdate3);
    exceptdtl.termid=rPack->lwithdraw_flag;
    exceptdtl.termseqno=rPack->lserial1;
    des2src(exceptdtl.accdate,tRefno.accdate);
    exceptdtl.termid=tRefno.termid;
    exceptdtl.termseqno=tRefno.termseqno;
    exceptdtl.cardno=rPack->lvol0;
    exceptdtl.purseno=rPack->lvol1;
    exceptdtl.dpscnt=rPack->lvol5;
    exceptdtl.paycnt=rPack->lvol6;
    exceptdtl.cardbefbal=rPack->lvol7/100.0;
    exceptdtl.cardaftbal=rPack->lvol8/100.0;
    exceptdtl.failtype=rPack->lbank_acc_type;
    exceptdtl.status=1;
    //des2src(exceptdtl.remark,rPack->ssectypes);
    des2src(exceptdtl.lastsaved,pAccTrans->trans.sysdatetime);
    ret=DB_t_exceptdtl_add(&exceptdtl);
    if(ret) {
        if(DB_REPEAT==ret)
            return E_DB_EXCEPTDTL_E;
        else
            return E_DB_EXCEPTDTL_I;
    }
    return 0;
}

