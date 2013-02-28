/* --------------------------------------------
 * 创建日期: 2010-11-10
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 自动修正最近一笔联机写卡失败交易
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
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"
#include <string>
#include <sstream>
static int CheckCardStatus()
{
    CAccTrans& ats = CAccTrans::GetInst();
    TRANS& trans = ats.trans;
    T_t_card tCard;
    memset(&tCard, 0, sizeof(tCard));
    int ret = 0;
    ret = DB_t_card_read_by_cardno(trans.cardno, &tCard);
    if(ret)
    {
        writelog(LOG_ERR, "cardno[%d]", trans.cardno);
        if(DB_NOTFOUND == ret)
            return ERRINFO(E_NOTEXIST_CARDNO, trans.cardno);
        else
            return E_DB_CARD_R;
    }
    if(tCard.status[0] != STATUS_NORMAL)
    {
        return ERRINFO(E_CARD_LOGOUT, trans.cardno);
    }
    if('1' == tCard.frozeflag[0])
    {
        return ERRINFO(E_CARD_FREEZE, trans.cardno);
    }
    if('1' == tCard.lossflag[0])
    {
        return ERRINFO(E_CARD_LOST, trans.cardno);
    }
    if('1' == tCard.badflag[0])
    {
        return ERRINFO(E_CARD_BADRECORD, trans.cardno);
    }
    //检查卡的有效期
    if(strcmp(tCard.expiredate, trans.transdate) <= 0)
        return E_CARD_EXPIRED;
    trans.cardphytype = tCard.cardphytype;
    return 0;
}
static int CardTransCheck(const T_t_cardtrans& cardtrans)
{
    CAccTrans& ats = CAccTrans::GetInst();
    TRANS& trans = ats.trans;
    if(amtcmp(cardtrans.cardbefbal, trans.cardbefbal) == 0)
    {
        if(amtcmp(cardtrans.cardbefbal, cardtrans.cardaftbal) == 0)
        {
            return 0;
        }
        if(TC_POSDEPOSIT == cardtrans.transcode)
            return 0;
        if(amtcmp(cardtrans.cardbefbal, cardtrans.cardaftbal) > 0)
        {
            //消费
            if(cardtrans.paycnt == trans.paycnt)
            {
                trans.errcode = 1;
                return 0;
            }
        }
        else if(amtcmp(cardtrans.cardbefbal, cardtrans.cardaftbal) < 0)
        {
            //充值
            if(cardtrans.dpscnt == trans.dpscnt)
            {
                trans.errcode = 1;
                return 0;
            }
        }
    }
    return 0;
}
int CardTransProcess(T_t_cardtrans& cardtrans)
{
    CAccTrans& ats = CAccTrans::GetInst();
    TRANS& trans = ats.trans;
    int ret = DB_t_cardtrans_read_lock_by_c0_and_cardno(trans.cardno, &cardtrans);
    if(ret)
    {
        if(DB_NOTFOUND == ret)
            return 0;
        else
            return E_DB_CARDTRANS_R;
    }
    ret = CardTransCheck(cardtrans);
    if(ret)
    {
        DB_t_cardtrans_free_lock_by_c0();
        return ret;
    }
    if(trans.errcode)
    {
        trans.cardaftbal = cardtrans.cardaftbal;
        trans.addamt = D4U5(trans.cardaftbal - trans.cardbefbal);
        trans.transcode = cardtrans.transcode;
        if(trans.transcode)
        {
            T_t_transcode *_pCfgTransCode = ats.getCfgTranscode(cardtrans.transcode);
            if(_pCfgTransCode)
                strcpy(trans.remark, _pCfgTransCode->transname);
        }
        cardtrans.updcnt++;
        strcpy(cardtrans.updtime, trans.sysdatetime);
        ret = DB_t_cardtrans_update_lock_by_c0(&cardtrans);
        if(ret)
        {
            return E_DB_CARDTRANS_U;
        }
    }
    else
    {
        DB_t_cardtrans_free_lock_by_c0();
    }
    return 0;
}
static int DoResponse(const T_t_cardtrans& cardtrans, TRUSERID *handle, int *pRetCode, char *szMsg)
{
    CAccTrans& ats = CAccTrans::GetInst();
    TRANS& trans = ats.trans;
    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, F_LVOL0, F_LVOL1, F_LVOL7, F_LVOL8, F_DAMT0, F_LCERT_CODE,
           F_SDATE0, F_STIME0, F_LWITHDRAW_FLAG, F_LSERIAL0, F_LSERIAL1, F_SNOTE, F_VSMESS, 0);
    outPack->lwithdraw_flag = trans.termid;
    outPack->lvol0 = trans.cardno;
    outPack->lvol7 = D4U5(trans.cardbefbal * 100, 0);
    outPack->lvol8 = D4U5(trans.cardaftbal * 100, 0);

    if(trans.errcode)
    {
        outPack->lvol1 = 1;
        outPack->damt0 = trans.addamt;
        outPack->lcert_code = trans.transcode;
        outPack->lserial0 = cardtrans.termid;
        outPack->lserial1 = cardtrans.termseqno;
        strcpy(outPack->sdate0, cardtrans.transdate);
        strcpy(outPack->stime0, cardtrans.transtime);
        strcpy(outPack->snote, trans.remark);
    }
    PutRow(handle, outPack, pRetCode, szMsg);
    return 0;
}

int F200001(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    CAccTrans& ats = CAccTrans::GetInst();
    TRANS& trans = ats.trans;
    trans.termid = rPack->lwithdraw_flag;
    trans.cardno = rPack->lvol0;
    ats.SetCardCntAndCardBal(rPack->lvol5, rPack->lvol6, rPack->lvol7);
//	trans.transcode= rPack->lcert_code;
    ret = CheckCardStatus();
    if(ret)
    {
        return ret;
    }
    T_t_cardtrans cardtrans;
    memset(&cardtrans, 0, sizeof(cardtrans));
    ret = CardTransProcess(cardtrans);
    if(ret)
    {
        return ret;
    }
    ret = DoResponse(cardtrans, handle, pRetCode, szMsg);
    if(ret)
    {
        return ret;
    }
    return 0;
}
