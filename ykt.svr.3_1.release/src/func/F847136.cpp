/* --------------------------------------------
 * 程序名称: F847136.sqc
 * 创建日期: 2007-8-8
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 回收 商户卡
 * --------------------------------------------
 * 修改日期: 2009-06-02
 * 修改人员: 闻剑
 * 修改描述: 3.0.0.0
 * 版本信息:
 * 备注信息:
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

static int DoCheck(ST_PACK *rPack,T_t_shopcard& tShopCard) {
    //检查卡是否已经使用
    int ret=0;

    CAccTrans *pAccTrans=CAccTrans::getInstance();
    TRANS& trans=pAccTrans->trans;

    tShopCard.cardno=rPack->lvol2;
    des2src(tShopCard.cardphyid,rPack->scust_auth);
    tShopCard.status[0]=STATUS_NORMAL;
    tShopCard.lossflag[0]='0';

    ret=DB_t_shopcard_read_lock_by_c0_and_cardno(tShopCard.cardno,&tShopCard);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_CARDNO;
        else
            return E_DB_SHOPCARD_R;
    }
    if(tShopCard.status[0]!=STATUS_NORMAL) {
        DB_t_shop_free_lock_by_c0();
        return E_CARD_LOGOUT;
    }
    T_t_shop tShop;

    memset(&tShop,0,sizeof(tShop));
    ret=DB_t_shop_read_by_shopid(tShopCard.shopid,&tShop);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_DB_SHOP_N;
        else
            return E_DB_SHOP_R;
    }
    des2src(trans.custname,tShop.shopname);
    return 0;
}
static int DoUpdate(T_t_shopcard& tShopCard) {
    int ret=0;

    tShopCard.status[0]=STATUS_DELETE;
    ret=DB_t_shopcard_update_lock_by_c0(&tShopCard);
    if(ret) {
        return E_DB_SHOPCARD_U;
    }
    return 0;
}

int F847136(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    des2src(pAccTrans->trans.opercode,rPack->semp);
    pAccTrans->trans.transcode=TC_SHOPCARDCLOSE;
    ret=pAccTrans->InitTrans();
    if (ret)
        return ret;
    TRANS& trans=pAccTrans->trans;

    T_t_shopcard  tShopCard;
    memset(&tShopCard,0,sizeof(tShopCard));

    ret=DoCheck(rPack,tShopCard);
    if (ret)
        return ret;
    ret=DoUpdate(tShopCard);
    if (ret)
        return ret;
    T_t_transdtl transdtl;
    memset(&transdtl,0,sizeof(transdtl));

    transdtl.purseno=trans.purseno;
    transdtl.amount=trans.totaltransamt;
    transdtl.managefee=trans.totalfeeamt;
    transdtl.paytype=trans.fundtype;
    des2src(transdtl.voucherno,trans.voucherno);
    transdtl.status[0]=DTLSTATUS_SUCCESS;
    transdtl.revflag[0]='0';
    transdtl.errcode=0;
    transdtl.custid=trans.custid;
    strcpy(transdtl.custname,trans.custname);
    strcpy(transdtl.transdate,trans.transdate);
    strcpy(transdtl.transtime,trans.transtime);
    strcpy(transdtl.accdate,trans.accdate);
    strcpy(transdtl.acctime,trans.acctime);
    transdtl.termid=trans.termid;
    transdtl.termseqno=trans.termseqno;
    transdtl.transcode=trans.transcode;
    des2src(transdtl.opercode,trans.opercode);
    transdtl.cardno=tShopCard.cardno;
    transdtl.cardbefbal=trans.cardbefbal;
    transdtl.cardaftbal=trans.cardaftbal;
    des2src(transdtl.showcardno,tShopCard.showcardno);
    GetStuempnoByCustid(transdtl.custid,transdtl.stuempno);
    ret=DB_t_transdtl_add(&transdtl);
    if (ret) {
        if (DB_REPEAT==ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }
    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    memset(&aPack,0,sizeof(aPack));
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_VSMESS,F_LSERIAL1,0);
    //检查客户信息，判断是否可以发行卡

    sprintf(outPack->vsmess,"商户号%d卡号%d回收成功",tShopCard.shopid,tShopCard.cardno);
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}

