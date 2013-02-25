/* --------------------------------------------
 * 创建日期: 2011-10-26
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子钱包第三方扣款冲正
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
#include "transfunc.h"


//联机冲正,当日即时冲正
static int doTransRev(char *oldaccdate, int oldtermid, int oldtermseqno) {
    int ret = 0;
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    TRANS& trans = pAccTrans->trans;

    T_t_transdtl transdtl;
    memset(&transdtl, 0, sizeof(transdtl));
    ret = DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(oldaccdate, oldtermid, oldtermseqno, &transdtl);
    if(ret) {
        writelog(LOG_ERR, "ret[%d]accdate[%s]termid[%d]termseqno[%d]", ret, oldaccdate, oldtermid, oldtermseqno);
        if(DB_NOTFOUND == ret)
            return E_DB_TRANSDTL_N;
        else
            return E_DB_TRANSDTL_R;
    }
    if('1' == transdtl.revflag[0]) {
        DB_t_transdtl_free_lock_by_c0();
        pAccTrans->remark = "该交易已冲正";
        return 0;
    }
    transdtl.revflag[0] = '1';
    ret = DB_t_transdtl_update_lock_by_c0(&transdtl);
    if(ret) {
        writelog(LOG_ERR, "UpdateTransdtlRevFlag ret[%d]accdate[%s]termid[%d]termseqno[%d]", ret, oldaccdate, oldtermid, oldtermseqno);
        return ret;
    }
    if(transdtl.cardcnt > 0 && transdtl.cardno > 0) {
        if(TF_PAY == transdtl.transflag) {
            ret = UpdateCardBitmap(transdtl.cardno, transdtl.cardcnt, CARDBITMAPTYPE_REV);
            if(ret) {
                writelog(LOG_ERR, "UpdateCardBitmap err ret[%d]cardno[%d]cardcnt[%d]", ret, transdtl.cardno, transdtl.cardcnt);
            }
        }
    }
    if(strlen(trans.opercode)) {
        if(strcmp(transdtl.opercode, pAccTrans->trans.opercode) != 0) {
            des2src(transdtl.opercode, trans.opercode);
        }
    }

    trans.cardno = transdtl.cardno;
    trans.cardflag = 0;
    trans.offlineflag = 1;
    trans.revflag = 1; //冲正标志
    trans.cardbefbal = transdtl.cardbefbal;
    trans.cardaftbal = transdtl.cardbefbal;
    trans.transflag = transdtl.transflag;
    if(TF_DPS == trans.transflag) {
        trans.dpscnt = transdtl.cardcnt - 1;
        trans.aftdpscnt = trans.dpscnt;
    }
    if(TF_PAY == trans.transflag) {
        trans.paycnt = transdtl.cardcnt - 1;
        trans.aftpaycnt = trans.paycnt;
    }

    ret = pAccTrans->doTodayReverseTrans(oldaccdate, oldtermid, oldtermseqno);
    if(ret)
        return ret;
    //transdtl.cardaftbal = transdtl.cardbefbal;	//delete by chen 2012-01-05
//start add by chen 2012-01-04
    if (trans.transflag == 2) {		//消费
        transdtl.cardbefbal= trans.draccbefbal;
    } else {			//充值
        transdtl.cardbefbal= trans.craccbefbal;
    }
//end add by chen 2012-01-04
    transdtl.revflag[0] = '0';
    strcpy(transdtl.accdate, pAccTrans->trans.accdate);
    strcpy(transdtl.acctime, pAccTrans->trans.acctime);
    des2src(transdtl.transdate, pAccTrans->trans.transdate);
    des2src(transdtl.transtime, pAccTrans->trans.transtime);
    transdtl.transcode = pAccTrans->trans.transcode;
    transdtl.termid = pAccTrans->trans.termid;
    transdtl.termseqno = pAccTrans->trans.termseqno;
    transdtl.amount = -transdtl.amount;
//start add by chen 2012-01-04
    if (trans.transflag == 2) {		//消费
        transdtl.cardaftbal= trans.draccaftbal;
    } else {			//充值
        transdtl.cardaftbal= trans.craccaftbal;
    }
//end add by chen 2012-01-04
    transdtl.managefee = -transdtl.managefee;
    ret = DB_t_transdtl_add(&transdtl);
    if(ret) {
        if(DB_REPEAT == ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }
    return 0;
}


int F846341(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    TRANS& trans=pAccTrans->trans;
    des2src(trans.refno,rPack->sphone3);

    if(strlen(trans.refno)!=14) {
        ERRTIP("交易参考号错误");
        return E_COMMON_ERR;
    }
    T_t_refno tRefno;

    memset(&tRefno,0,sizeof(tRefno));

    ret=DB_t_refno_read_by_refno(trans.refno,&tRefno);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_DB_REFNO_N;
        else
            return E_DB_REFNO_R;
    }
    if(strncmp(tRefno.mac,rPack->saddr,8)!=0) {
        return E_MAC_FAIL;
    }

    if(RS_SUCC!=tRefno.status) {
        return ERRIF_TRANS_REVERSED;
    }

    pAccTrans->trans.transcode=TC_EACC2SHOPREV;
    pAccTrans->trans.termid=tRefno.termid;
    ret=pAccTrans->InitTrans();
    if(ret)
        return ret;

    ret=doTransRev(tRefno.accdate,tRefno.termid,tRefno.termseqno);
    if(ret) {
        writelog(LOG_ERR,"acctransrev err ret=%d",ret);
        return ret;
    }

    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);

    SetCol(handle,F_LVOL0,F_SPHONE3,F_SADDR,F_LWITHDRAW_FLAG,F_SDATE3,F_STIME3,F_SEMP,F_LSERIAL1,F_VSMESS,0);
    outPack->lvol0=pAccTrans->trans.cardno;
    des2src(outPack->sdate3,pAccTrans->trans.accdate);
    des2src(outPack->stime3,pAccTrans->trans.acctime);
    des2src(outPack->semp,pAccTrans->trans.opercode);
    outPack->lserial1=pAccTrans->trans.termseqno;
    strcpy(outPack->sphone3,tRefno.refno);
    strcpy(outPack->saddr,tRefno.mac);
    strcpy(outPack->vsmess,pAccTrans->remark.c_str());
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}


