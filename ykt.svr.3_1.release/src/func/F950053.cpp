/* --------------------------------------------
 * 创建日期: 9 17 2004
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:POS 联机充值冲正
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "acctrans.h"
#include "busqc.h"
static int doReverse(char* oldaccdate,int oldtermid,int oldtermseqno) {
    //查找操作员流水
    int ret=0;
    T_t_card tCard;

    CAccTrans *pAccTrans=CAccTrans::getInstance();
    TRANS& trans=pAccTrans->trans;
    T_t_transdtl transdtl;
    memset(&transdtl,0,sizeof(transdtl));
    ret=DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(oldaccdate,oldtermid,oldtermseqno,&transdtl);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_DB_TRANSDTL_N;
        else
            return E_DB_TRANSDTL_R;
    }
    if(trans.cardno!=transdtl.cardno) {
        DB_t_transdtl_free_lock_by_c0();
        return E_CARDNO_DIFFER;
    }
    if(transdtl.transcode!=TC_POSDEPOSIT&&
            transdtl.transcode!=TC_POSDEPOSITREV&&
            transdtl.transcode!=TC_SHOPPOSDEPOSIT&&
            transdtl.transcode!=TC_SHOPPOSDEPOSITREV&&
            transdtl.transcode!=TC_CARDDEPOSIT&&
            transdtl.transcode!=TC_CARDDEPOSITREV) {
        DB_t_transdtl_free_lock_by_c0();
        return E_TRANSCODE_NOT_SAVING;
    }
    if(transdtl.revflag[0]=='1') {
        DB_t_transdtl_free_lock_by_c0();

        memset(&tCard,0,sizeof(tCard));
        ret=DB_t_card_read_by_cardno(transdtl.cardno,&tCard);
        if(ret) {
            writelog(LOG_ERR,"cardno[%d]",transdtl.cardno);
            if(DB_NOTFOUND==ret)
                return E_DB_CARD_N;
            else
                return E_DB_CARD_R;
        }
        //pAccTrans->remark="该交易已冲正";
        //strcpy(cardphyid,tCard.cardphyid);
        return E_TRANS_REVERSED;
    }
    transdtl.revflag[0]='1';
    ret=DB_t_transdtl_update_lock_by_c0(&transdtl);
    if(ret) {
        return E_DB_TRANSDTL_U;
    }
    memset(&tCard,0,sizeof(tCard));
    ret=DB_t_card_read_by_cardno(transdtl.cardno,&tCard);
    if(ret) {
        writelog(LOG_ERR,"cardno[%d]",transdtl.cardno);
        if(DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CARDNO,transdtl.cardno);
        else
            return E_DB_CARD_R;
    }
    if(tCard.status[0]!=STATUS_NORMAL) {
        return ERRINFO(E_CARD_LOGOUT,transdtl.cardno);
    }
    if('1'==tCard.frozeflag[0]) {
        return ERRINFO(E_CARD_FREEZE,transdtl.cardno);
    }
    if('1'==tCard.lossflag[0]) {
        return ERRINFO(E_CARD_LOST,transdtl.cardno);
    }
    if('1'==tCard.badflag[0]) {
        return ERRINFO(E_CARD_BADRECORD,transdtl.cardno);
    }
//	ret=UpdateCardBitmap(trans.cardno,trans.cardcnt,CARDBITMAPTYPE_INCREV,0);
//	if(ret)
//		return ret;
    T_t_transdtl transdtlrev;
    memset(&transdtlrev,0,sizeof(transdtlrev));

    des2src(transdtlrev.transdate,trans.transdate);
    des2src(transdtlrev.transtime,trans.transtime);
    des2src(transdtlrev.accdate,pAccTrans->trans.accdate);
    strcpy(transdtlrev.acctime,trans.acctime);
    transdtlrev.termid=trans.termid;
    transdtlrev.termseqno=trans.termseqno;
    transdtlrev.transcode=trans.transcode;
    transdtlrev.paytype=0;
    transdtlrev.cardno=transdtl.cardno;
    transdtlrev.purseno=transdtl.purseno;
    transdtlrev.transflag = transdtl.transflag;
    transdtlrev.cardcnt=transdtl.cardcnt;
    transdtlrev.cardbefbal=transdtl.cardbefbal;
    transdtlrev.amount = -transdtl.amount;
    transdtlrev.managefee= -transdtl.managefee;
    transdtlrev.custid=transdtl.custid;
    des2src(transdtlrev.custname,transdtl.custname);
    transdtlrev.cardaftbal=transdtl.cardbefbal;
//	if(amtcmp(transdtlrev.cardaftbal,0)<0)
//		return ERRINFO(E_CARD_BALANCE_SHORTAGE,transdtlrev.cardaftbal);
    des2src(transdtlrev.opercode,trans.opercode);
    transdtlrev.status[0]=DTLSTATUS_SUCCESS;
    transdtlrev.errcode=0;
    ret=DB_t_transdtl_add(&transdtlrev);
    if(ret) {
        if(DB_REPEAT==ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }
    trans.cardflag=1;
    ret=pAccTrans->doTodayReverseTrans(oldaccdate,oldtermid,oldtermseqno);
    if(ret)
        return ret;
    trans.cardaftbal=transdtlrev.cardaftbal;
    trans.transamt=transdtlrev.amount;
    return 0;
}
int F950053(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    TRANS& trans=pAccTrans->trans;
    ret=pAccTrans->CheckCfgUpdate();
    if(ret)
        return ret;
    int lastdevseqno=rPack->lvol4;
    char devphyid[31]="";
    des2src(devphyid,rPack->sdate1);
    T_t_transdtl transdtl;

    memset(&transdtl,0,sizeof(transdtl));
    ret=DB_t_transdtl_read_by_accdate_and_devphyid_and_devseqno(trans.transdate,devphyid,lastdevseqno,&transdtl);
    if(ret) {
        writelog(LOG_ERR,"transdate[%s]devphyid[%s]devseqno[%d]",trans.transdate,devphyid,lastdevseqno);
        if(DB_NOTFOUND==ret)
            return 0;
        else
            return E_DB_TRANSDTL_R;

    }
    if(transdtl.revflag[0]=='1') {
        return 0;
    }
    ret=GetDevIdByDevPhyId(&(trans.termid),devphyid);
    if(ret) {
        return ret;
    }
    pAccTrans->GetTermSeqno();
    if(transdtl.transcode==TC_POSDEPOSIT)
        pAccTrans->trans.transcode=TC_POSDEPOSITREV;
    else if(transdtl.transcode==TC_SHOPPOSDEPOSIT)
        pAccTrans->trans.transcode=TC_SHOPPOSDEPOSITREV;
    else
        return E_TRANSCODE_NOT_SAVING;
    ret=doReverse(transdtl.accdate,transdtl.termid,transdtl.termseqno);
    if(ret)
        return ret;

    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);

    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL5,F_LVOL10,F_LCERT_CODE,0);

    outPack->lvol5 = transdtl.cardno;
    outPack->lvol10 = (int)D4U5(transdtl.cardaftbal*100,0);
    outPack->lcert_code = transdtl.termseqno;

//	outPack->lvol0=pAccTrans->trans.cardno;
//	outPack->lvol8=D4U5(pAccTrans->trans.cardaftbal*100,0);
//	des2src(outPack->sdate3,pAccTrans->sysPara.sSettleDate);
//	des2src(outPack->semp,pAccTrans->trans.opercode);
//	outPack->lserial1=pAccTrans->trans.termseqno;
    sprintf(outPack->vsmess,"冲正金额%.2lf 卡余额%.2lf",trans.transamt,trans.cardaftbal);
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}
