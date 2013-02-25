/* --------------------------------------------
 * 创建日期: 2010-08-05
 * 程序作者: 闻剑
 * 版本信息: 3.0.0.0
 * 程序功能: 水控余额转主钱包
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
#include "busqc.h"
#include "acctrans.h"
#include "transfunc.h"
#include "interfacefunc.h"

static int checklosecardacc(int cardno,T_t_card  *tCard,T_t_account *tAccount) {
    int ret = DB_t_card_read_by_cardno(cardno, tCard);
    if(tCard->status[0]!=STATUS_NORMAL) {
        DB_t_card_free_lock_by_cur();
        return ERRINFO(E_CARD_LOGOUT,cardno);
    }
    /*
    if('1'==tCard->frozeflag[0])
    {
    	DB_t_card_free_lock_by_cur();
    	return ERRINFO(E_CARD_FREEZE,cardno);
    }
    if('1'==tCard->badflag[0])
    {
    	DB_t_card_free_lock_by_cur();
    	return ERRINFO(E_CARD_BADRECORD,cardno);
    }
    // 只有挂失状态才能无卡退
    if('1'!=tCard->lossflag[0])
    {
    	DB_t_card_free_lock_by_cur();
    	return ERRINFO(E_CARDNO_NOLOST,cardno);
    }
    */
    ret=DB_t_account_read_by_accno(tCard->accno,tAccount);
    if(ret) {
        writelog(LOG_ERR,"accno[%s]",tCard->accno);
        if(DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_ACCNO,tCard->accno);
        else
            return E_DB_ACCOUNT_R;
    }
    if(tAccount->status[0]!=STATUS_NORMAL) {
        return ERRINFO(E_CARDACC_LOGOUT,tAccount->accno);
    }
    return 0;
}

// 退水控钱包到主钱包
static int waterbalareturn(CAccTrans *pAccTrans,ST_PACK *rPack,ST_PACK *outPack) {
    int ret=0;
    double waterbefbal = 0;
    double wateraftbal = 0;
    TRANS& trans=pAccTrans->trans;

    trans.cardno=rPack->lvol0;
    trans.purseno=PURSE_NO_ONE;
    trans.cardflag=1;
    trans.usecardflag=1;
    pAccTrans->SetCardCntAndCardBal(rPack->lvol5,rPack->lvol6,rPack->lvol7);
    trans.aftdpscnt++;
    des2src(trans.cardphyid,rPack->sstation1);

    T_t_card  tCard;
    memset(&tCard,0,sizeof(tCard));

    T_t_account tAccount;
    memset(&tAccount,0,sizeof(tAccount));

    /*

    if(!rPack->lvol2)		// 有卡
    {
    	ERRTIP("无卡小钱包余额不退");
    	return E_COMMON_ERR;
    }
    ret=pAccTrans->CheckAcc(&tCard,&tAccount);
    if(ret)
    {
    	writelog(LOG_ERR,"检查状态失败");
    	return ret;
    }
    */

    ret = DB_t_card_read_by_cardno(trans.cardno,&tCard);
    if(ret) {
        if(DB_NOTFOUND == ret)
            return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
        return ret;
    }

    trans.custid=tCard.custid;
    des2src(trans.showcardno,tCard.showcardno);
    des2src(trans.cardaccno,tCard.accno);


    ret=DB_t_account_read_by_accno(tCard.accno,&tAccount);
    if(ret) {
        return E_DB_ACCOUNT_R;
    }

    strcpy(trans.custname,tAccount.accname);

    // 小钱包类型
    T_t_pursetype  pursetype;
    memset(&pursetype,0,sizeof(pursetype));

    pursetype.pursetype=rPack->lvol1;
    if(pursetype.pursetype<1) {
        ERRTIP("请输入小钱包类型");
        return E_COMMON_ERR;
    }
    ret=DB_t_pursetype_read_by_pursetype(pursetype.pursetype,&pursetype);
    if(ret) {
        if(DB_NOTFOUND==ret) {
            ERRTIP("钱包类型[%d]不存在",pursetype.pursetype);
            return E_COMMON_ERR;
        } else
            return E_DB_PURSETYPE_R;
    }
    if(!pursetype.enableflag) {
        ERRTIP("钱包类型[%d]未启用",pursetype.pursetype);
        return E_COMMON_ERR;
    }
    if(!pursetype.refundflag) {
        //ERRTIP("钱包类型[%d]不允许退款",pursetype.pursetype);
        outPack->lvol0=tCard.cardno;
        outPack->lvol9=D2I(pAccTrans->trans.cardaftbal*100);
        outPack->lvol8=0;
        outPack->lsafe_level2=0;
        des2src(outPack->sdate3,pAccTrans->trans.accdate);
        des2src(outPack->stime3,pAccTrans->trans.acctime);
        des2src(outPack->semp,trans.opercode);
        outPack->lwithdraw_flag=trans.termid;
        outPack->lserial1=trans.termseqno;
        //sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
        sprintf(trans.remark,"小钱包不允许退款");
        des2src(outPack->vsmess,trans.remark);
        return 0;
    }
    /*
    T_t_cardbalance  cardbalance;
    memset(&cardbalance,0,sizeof(cardbalance));
    ret=DB_t_cardbalance_read_lock_by_c0_and_accno_and_pursetype(tAccount.accno,pursetype.pursetype,&cardbalance);
    if(ret)
    {
    	if(DB_NOTFOUND==ret)			// 早期的卡没开小钱包账户
    	{
    		return E_DB_CARDBALANCE_N;
    	}

    	else
    		return E_DB_CARDBALANCE_R;
    }

    if(rPack->lvol2)			//有卡
    {
    	trans.cardflag=1;
    	trans.usecardflag=1;
    	pAccTrans->SetCardCntAndCardBal(rPack->lvol5,rPack->lvol6,rPack->lvol7);
    	trans.aftdpscnt++;
    	des2src(trans.cardphyid,rPack->sstation1);

    	waterbefbal = D4U5(rPack->lsafe_level/100.0);
    	trans.inputamt= waterbefbal;

    	if(amtcmp(trans.inputamt,pursetype.pursemaxbal)>0)
    		trans.inputamt=pursetype.pursemaxbal;

    	if(amtcmp(trans.inputamt,cardbalance.balance)>0)
    		trans.inputamt=cardbalance.balance;
    }
    else
    {
    	//无卡
    	if(amtcmp(cardbalance.cardbal,cardbalance.balance)>0)
    		trans.inputamt=cardbalance.balance;
    	else
    		trans.inputamt=cardbalance.cardbal;

    	waterbefbal = trans.inputamt;
    	trans.cardflag=1;							// 涉及到计算卡余额，不然退大钱包有问题
    	trans.cardbefbal=tAccount.cardbal;				// 大钱包卡余额
    	trans.cardaftbal=tAccount.cardbal;
    	des2src(trans.custname,tAccount.accname);
    	des2src(trans.showcardno,tCard.showcardno);
    	des2src(trans.cardaccno,tCard.accno);
    }
    */
    //waterbefbal = D4U5(rPack->lsafe_level/100.0);


    if(rPack->lvol2) { //有卡
        waterbefbal = D4U5(rPack->lsafe_level/100.0);
    } else { //无卡
        if(pursetype.refundflag == 1) { //无卡退小钱包
            T_t_cardbalance  cardbalance;
            memset(&cardbalance,0,sizeof(cardbalance));
            ret=DB_t_cardbalance_read_lock_by_c0_and_accno_and_pursetype(tAccount.accno,pursetype.pursetype,&cardbalance);
            if(ret) {
                if(DB_NOTFOUND==ret) {		// 早期的卡没开小钱包账户
                    return E_DB_CARDBALANCE_N;
                } else
                    return E_DB_CARDBALANCE_R;
            }

            if(amtcmp(cardbalance.cardbal,cardbalance.balance)>0)
                waterbefbal=cardbalance.balance;
            else
                waterbefbal=cardbalance.cardbal;

            trans.cardflag=1;
            trans.cardbefbal=tAccount.cardbal;				// 大钱包卡余额
            trans.cardaftbal=tAccount.cardbal;

            // 更新水控卡余额
            cardbalance.balance = 0;
            cardbalance.cardbal = 0;
            ret=DB_t_cardbalance_update_lock_by_c0(&cardbalance);
            if(ret) {
                return E_DB_CARDBALANCE_U;
            }
        }
    }


    trans.inputamt= waterbefbal;
    if(amtcmp(trans.inputamt,pursetype.pursemaxbal)>0) {
        //"小钱包余额大于最大钱包余额,只能按最大余额退卡";
        trans.inputamt=pursetype.pursemaxbal;
    }
    double CardMaxBal=0;
    ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
    if(ret)
        return ret;
    if(amtcmp(trans.cardbefbal+trans.inputamt,CardMaxBal)>0)
        return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);
    trans.feetype=tCard.feetype;
    trans.custid=tCard.custid;
    trans.transamt=trans.inputamt;
    trans.unusedamt = trans.inputamt;
    if(pursetype.onlineflag) {
        //联机水控退款
        pAccTrans->trans.transtype=TRANSTYPE_WATERREFUND;
        ret=pAccTrans->DoTransByTransType();
        if(ret)
            return ret;
        ret=pAccTrans->doTransEnd();
        if(ret)
            return ret;
    } else {
        if(pursetype.shopid<1) {
            ERRTIP("钱包类型[%d]没有设置对应的水控商户",pursetype.pursetype);
            return E_COMMON_ERR;
        }
        //否则脱机水控
        int shoptype=0;
        char shopstatus[2]= {0};
        ret=ShopAccReadbyShopid(pursetype.shopid,trans.shopaccno,&shoptype,shopstatus);
        if(ret) {
            writelog(LOG_ERR,"shopid[%d]",pursetype.shopid);
            return ret;
        }
        if(shopstatus[0]!=STATUS_NORMAL)
            return ERRIF_SHOP_CLOSE;
        if(shoptype!=SHOPTYPE_COSUMESHOP)
            return ERRIF_SHOP_TYPE;
        pAccTrans->trans.transtype=TRANSTYPE_SHOPREFUND;
        ret=pAccTrans->DoTransByTransType();
        if(ret)
            return ret;
        ret=pAccTrans->doTransEnd();
        if(ret)
            return ret;
    }
    T_t_transdtl transdtl;
    memset(&transdtl,0,sizeof(transdtl));
    des2src(transdtl.refno,trans.refno);
    des2src(transdtl.transdate,trans.transdate);
    des2src(transdtl.transtime,trans.transtime);
    strcpy(transdtl.accdate,trans.accdate);
    strcpy(transdtl.acctime,trans.acctime);
    transdtl.termid=trans.termid;
    transdtl.termseqno=trans.termseqno;
    transdtl.transcode=trans.transcode;
    transdtl.cardno=trans.cardno;
    transdtl.purseno=trans.purseno;
    transdtl.transflag= TF_DPS;
    transdtl.cardcnt=trans.aftdpscnt;
    transdtl.cardbefbal=trans.cardbefbal;
    transdtl.cardaftbal=trans.cardaftbal;
    transdtl.amount=trans.totaltransamt;
    transdtl.managefee=trans.totalfeeamt;
    transdtl.custid=trans.custid;
    des2src(transdtl.custname,trans.custname);
    des2src(transdtl.opercode,trans.opercode);
    transdtl.status[0]=DTLSTATUS_SUCCESS;
    des2src(transdtl.showcardno,trans.showcardno);
    GetStuempnoByCustid(transdtl.custid,transdtl.stuempno);
    ret=DB_t_transdtl_add(&transdtl);
    if(ret) {
        if(DB_REPEAT==ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }
    T_t_pursetransdtl pursetransdtl;
    memset(&pursetransdtl,0,sizeof(pursetransdtl));
    des2src(pursetransdtl.refno,transdtl.refno);
    des2src(pursetransdtl.transdate,transdtl.transdate);
    des2src(pursetransdtl.transtime,transdtl.transtime);
    strcpy(pursetransdtl.accdate,transdtl.accdate);
    strcpy(pursetransdtl.acctime,transdtl.acctime);
    pursetransdtl.termid=transdtl.termid;
    pursetransdtl.termseqno=transdtl.termseqno;
    pursetransdtl.transcode=transdtl.transcode;
    pursetransdtl.cardno=transdtl.cardno;
    pursetransdtl.pursetype=pursetype.pursetype;
    pursetransdtl.transflag= TF_PAY;
    pursetransdtl.cardcnt=0;
    pursetransdtl.cardbefbal=waterbefbal;
    pursetransdtl.cardaftbal=wateraftbal;
    pursetransdtl.amount=transdtl.amount;
    pursetransdtl.custid=transdtl.custid;
    des2src(pursetransdtl.custname,transdtl.custname);
    des2src(pursetransdtl.opercode,transdtl.opercode);
    pursetransdtl.status[0]=transdtl.status[0];
    des2src(pursetransdtl.showcardno,trans.showcardno);
    des2src(pursetransdtl.stuempno,transdtl.stuempno);
    ret=DB_t_pursetransdtl_add(&pursetransdtl);
    if(ret) {
        if(DB_REPEAT==ret)
            return E_DB_PURSETRANSDTL_E;
        else
            return E_DB_PURSETRANSDTL_I;
    }
    outPack->lvol0=tCard.cardno;
    outPack->lvol9=D2I(pAccTrans->trans.cardaftbal*100);
    outPack->lvol8=D2I(pAccTrans->trans.totaltransamt*100);
    //outPack->lsafe_level=D2I(wateraftbal*100);
    outPack->lsafe_level2=0;
    des2src(outPack->sdate3,pAccTrans->trans.accdate);
    des2src(outPack->stime3,pAccTrans->trans.acctime);
    des2src(outPack->semp,trans.opercode);
    outPack->lwithdraw_flag=trans.termid;
    outPack->lserial1=trans.termseqno;
    sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
    des2src(outPack->vsmess,trans.remark);
    return 0;
}

/*
static int waternobalareturn(CAccTrans *pAccTrans,ST_PACK *rPack,ST_PACK *outPack)
{
	int ret =0;
	T_t_card  tCard;
	T_t_pursetype  pursetype;
	memset(&pursetype,0,sizeof(pursetype));
	memset(&tCard,0,sizeof(tCard));

	pAccTrans->trans.transcode=TC_WATERNOBALARET;
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.termid=rPack->lwithdraw_flag;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;

	TRANS& trans=pAccTrans->trans;

	trans.cardno=rPack->lvol0;
	trans.purseno=PURSE_NO_TWO;

	ret = DB_t_card_read_by_cardno(trans.cardno, &tCard);
	if(ret)
		return E_DB_CARD_R;

	trans.feetype=tCard.feetype;
	trans.custid=tCard.custid;
	trans.transamt=trans.inputamt;
	trans.unusedamt = trans.inputamt;

	trans.cardbefbal=trans.inputamt;
	trans.cardaftbal=0;

	pursetype.pursetype=rPack->lvol1;
	ret=DB_t_pursetype_read_by_pursetype(pursetype.pursetype,&pursetype);
	if(ret)
	{
		return E_DB_PURSETYPE_R;
	}

	writelog(LOG_INFO,"transamt[%f],pursetype[%d],onlineflag[%d]",trans.transamt,pursetype.pursetype,pursetype.onlineflag);
	if(pursetype.onlineflag)
	{
		pAccTrans->trans.transtype=TRANSTYPE_WATERNOBALAREFUND;
		ret=pAccTrans->DoTransByTransType();
		if(ret)
			return ret;
		ret=pAccTrans->doTransEnd();
		if(ret)
			return ret;
	}
	else				// 脱机水控不支持
	{
		return 0;
	}
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));
	des2src(transdtl.refno,trans.refno);
	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.cardaftbal=trans.cardaftbal;
    	transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
	transdtl.custid=trans.custid;
	des2src(transdtl.custname,trans.custname);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
    	des2src(transdtl.showcardno,trans.showcardno);
	GetStuempnoByCustid(transdtl.custid,transdtl.stuempno);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}

	return 0;
}
*/
int F850020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    pAccTrans->trans.transcode=TC_WATERBALRETURN;
    des2src(pAccTrans->trans.opercode,rPack->semp);
    pAccTrans->trans.termid=rPack->lwithdraw_flag;
    ret=pAccTrans->InitTrans();
    if(ret)
        return ret;
    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    memset(&aPack,0,sizeof(aPack));
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL2,F_LVOL3,F_LVOL8,F_SDATE0,F_SPHONE3,F_SADDR,F_LVOL5,F_LVOL9,F_LSAFE_LEVEL,F_LSAFE_LEVEL2,
           F_SDATE3,F_STIME3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);


    ret = waterbalareturn(pAccTrans,rPack,outPack);
    if(ret)
        return ret;
    /*
    if(amtcmp(outPack->damt0, 0)>0 )			// 小钱包卡库不平
    {
    	pAccTrans->Reset();
    	pAccTrans->trans.inputamt= outPack->damt0;
    	ret = waternobalareturn(pAccTrans,rPack,outPack);
    	if(ret)
    		return ret;
    }
    */
    if(iRequest != 846305) { // 补办卡时，不返回结果
        PutRow(handle,outPack,pRetCode,szMsg);
    }
    return 0;
}
