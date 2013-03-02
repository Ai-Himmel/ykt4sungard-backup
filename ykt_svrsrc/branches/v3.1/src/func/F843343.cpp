/* --------------------------------------------
 * 创建日期: 2009-06-02
 * 程序作者: 闻剑
 * 版本信息: 3.0.0.0
 * 程序功能: 发行商户卡
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
#define SHOPCARDTYPE   10
#define SHOPFEETYPE		1
static int DoCheck(ST_PACK *rPack,T_t_shopcard& tShopCard,T_t_shop& tShop)
{
    //检查卡是否已经使用
    int ret=0;

    CAccTrans *pAccTrans=CAccTrans::getInstance();
    TRANS& trans=pAccTrans->trans;

    des2src(tShopCard.cardphyid,rPack->sbank_acc);
    des2src(tShopCard.showcardno,rPack->sorder0);
    des2src(tShopCard.expiredate,rPack->sdate0);
    des2src(tShopCard.opendate,trans.accdate);
	des2src(tShopCard.lastsaved,trans.sysdatetime);
	tShopCard.status[0]=STATUS_NORMAL;
	tShopCard.lossflag[0]='0';
	tShopCard.shopid =rPack->lvol0;

    if(!strlen(tShopCard.cardphyid))
        return E_INPUT_CARDPHYID;
	if(!strlen(tShopCard.expiredate))
		return E_INPUT_EXPIREDATE;
    //判断到期日期
    ret=IsInvalidDateTime(tShopCard.expiredate,"YYYYMMDD");
    if (ret)
        return ERRINFO(E_INPUT_EXPIREDATE,tShopCard.expiredate);
    if (strncmp(tShopCard.expiredate,trans.accdate,8)<0)
        return ERRINFO(E_INPUT_EXPIREDATE,tShopCard.expiredate);
	//检查商户   
	ret=DB_t_shop_read_by_shopid(tShopCard.shopid,&tShop);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_SHOPID,tShopCard.shopid);
		else
			return E_DB_SHOPCARD_R;
	}
	if(tShop.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_SHOP_LOGOUT,tShop.shopid);
	}
    char cardpwd[33]={0};
    char key[17]={0};

    get_init_passwd_by_man_id(tShop.idno,cardpwd);
    strcpy(key,STATIC_SEED_KEY);
    EncodePwd(key,cardpwd,tShopCard.cardpwd, 0);

	strcpy(trans.cardpwd,cardpwd);//临时保存密码
	//检查是否存在商户卡
	T_t_shopcard tShopCardCheck;
	memset(&tShopCardCheck,0,sizeof(tShopCardCheck));
	ret=DB_t_shopcard_read_by_shopid_and_status(tShopCard.shopid,tShopCard.status,&tShopCardCheck);
	if(ret)
	{
		if(DB_NOTFOUND!=ret)
			return E_DB_SHOPCARD_R;
	}
	else
	{
		ERRTIP("该商户商户卡已发行");
		return E_COMMON_ERR;
	}
    ret=DB_t_shopcard_read_by_cardphyid_and_status(tShopCard.cardphyid,tShopCard.status,&tShopCardCheck);
    if (ret!=DB_NOTFOUND)
    {
        if (DB_SUCCESS==ret)
            return ERRINFO(E_EXIST_CARDPHYID,tShopCard.cardphyid);
        else
            return E_DB_CARD_R;
    }
    return 0;
}
static int DoUpdate(T_t_shopcard& tShopCard)
{
	int ret=0;

    ret = getNewUniqNo(KEYTYPE_CARDNO,&tShopCard.cardno);	//获取最大卡号
    if (ret)
    {
        return ret;
    }
	ret=DB_t_shopcard_add(&tShopCard);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_SHOPCARD_E;
		else
			return E_DB_SHOPCARD_I;
	}
	return 0;
}
int F843343(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    des2src(pAccTrans->trans.opercode,rPack->scust_limit);
    pAccTrans->trans.transcode=TC_SHOPCARDOPEN;
    ret=pAccTrans->InitTrans();
    if (ret)
        return ret;
    TRANS& trans=pAccTrans->trans;

    T_t_shop tShop;
	T_t_shopcard  tShopCard;

	memset(&tShop,0,sizeof(tShop));
	memset(&tShopCard,0,sizeof(tShopCard));
	
    ret=DoCheck(rPack,tShopCard,tShop);
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
    strcpy(transdtl.custname,tShop.shopname);
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
    ret=DB_t_transdtl_add(&transdtl);
    if (ret)
    {
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
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,
				F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCERT_NO,
				F_SDATE0,F_SNAME,F_SNAME2,
				F_SOPEN_EMP,F_SSTATUS0,
				F_DAMT2,F_LSERIAL1,F_VSMESS,
   			       F_SORDER0,F_SORDER1,F_SORDER2,
   			       F_SHOLDER_AC_NO,F_SSTAT_TYPE,F_SSTAT_TYPE2,
   			       F_SNATION_CODE,F_SBRANCH_CODE0,F_LVOL10,F_LVOL11,
				0);

	outPack->lvol10=SHOPCARDTYPE;							//卡类型
	outPack->lvol11=tShopCard.shopid;						//商户号
	outPack->lvol0 = tShopCard.cardno;						//交易卡号
	outPack->lvol1 = CUSTTYPE_SHOP;							//客户类别
	outPack->lvol5 = SHOPFEETYPE;							//收费类别
	des2src(outPack->scust_no,tShopCard.showcardno);		//显示卡号
	des2src(outPack->scust_no2,tShop.deptcode);				//部门号
	des2src(outPack->scert_no,tShop.idno);					//身份证号
	des2src(outPack->sname,tShop.shopname);					//客户姓名
	des2src(outPack->sopen_emp,trans.cardpwd);				//卡密码
	des2src(outPack->sdate0,tShopCard.expiredate); 			//有效截至日期
	strcpy(outPack->sorder0,CARD_STRUCT_VERSION);			//制卡版本号
	strcpy(outPack->sorder1,CARD_REGISTER_PUBLISH_CODE);	//发卡注册标识号
	strcpy(outPack->sorder2,CARD_REGISTER_SERVICE_CODE);	//服务注册标识号
	sprintf(outPack->sholder_ac_no,"%d",tShop.shopid); 		//商户号
	des2src(outPack->sstat_type,tShop.idtype); 				//证件类型
	des2src(outPack->sbranch_code0,tShop.areacode);		//院校代码
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}

