/* --------------------------------------------
 * 创建日期: 2008-06-04
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通补办卡
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

static int check(int cardno,T_t_customer& tCustomer,T_t_card& tCard)
{
	int ret=0;

	ret=DB_t_card_read_by_cardno(cardno,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else
			return E_DB_CARD_R;
	}
	if(tCard.cardattr[CARDSTAT_TYPE_FREEZE]=='1')
	{
		return E_REWCARD_CARDFROZE;	
	}
	if((tCard.cardattr[CARDSTAT_TYPE_LOST]!='1')&&(tCard.cardattr[CARDSTAT_TYPE_BAD]!='1'))
	{
		return E_REWCARD_CARDSTATUS;
		
	}
	T_t_cardtype tCardtype;
	
	memset(&tCardtype,0,sizeof(tCardtype));

	ret=DB_t_cardtype_read_by_cardtype(tCard.cardtype,&tCardtype);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_CARDTYPE_N;
		else
			return E_DB_CARDTYPE_R;
	}
	if(tCardtype.renewable[0]!='1')
	{
		return E_CARD_CANNOT_RENEW;
	}
	if(tCard.custid)
	{
		ret=DB_t_customer_read_by_custid(tCard.custid,&tCustomer);
		if(ret)
		{		
			if(DB_NOTFOUND==ret)
				return E_CUSTOMER_NOT_EXIST;
			else
				return E_DB_CUSTOMER_R;
		}
		if(tCustomer.status[0]=='2')
		{
			return E_CUSTOMER_LOGOUT;
		}
		if(tCustomer.feetype<1)
		{
			return E_NOSET_CUSTOMER_FEETYPE;
		}
	}
	char lossexpiredate[9]="";
	char sysdate[9]="";
	char sDays[10]="";
	ret=getParaVal(GLOBE_RENEWCARDDATE,sDays);
	if(ret)
		return ret;
	int days=atoi(sDays);
	
	ret=calcEndDate(tCard.lossdate,days,lossexpiredate);
	if(ret)
		return ret;
	getsysdate(sysdate);
	if(strcmp(sysdate,lossexpiredate)<0)
	{
		return E_CARDLOSSDATE_NOREACH;
	}
	return 0;
}

static int AddCard(T_t_customer& tCustomer,T_t_card& tCard)
{
	//检查卡是否已经使用
	int ret=0;
	char sysdate[9];
	getsysdate(sysdate);

	tCard.status[0]=STATUS_NORMAL;
	ret=DB_t_card_read_by_cardphyid_and_status(tCard.cardphyid,tCard.status,&tCard);
	if(ret!=DB_NOTFOUND)
	{
	    if(DB_SUCCESS==ret)
	        return E_CARDPHYID_EXIST;
	    else
	        return E_DB_CARD_R;
	}
	ret=DB_t_card_read_by_showcardno_and_status(tCard.showcardno,tCard.status,&tCard);
	if(ret!=DB_NOTFOUND)
	{
	    if(DB_SUCCESS==ret)
	        return E_SHOWCARDNO_EXIST;
	    else
	        return E_DB_CARD_R;
	}	
	T_t_cardtype tCardtype;
	
	memset(&tCardtype,0,sizeof(tCardtype));

	ret=DB_t_cardtype_read_by_cardtype(tCard.cardtype,&tCardtype);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_CARDTYPE_N;
		else
			return E_DB_CARDTYPE_R;
	}
	//判断到期日期
	if(strlen(tCard.expiredate)<1)
	{
		ret=IsInvalidDateTime(tCustomer.outdate,"YYYYMMDD");
		if(ret==0)
		{
			if(strncmp(tCustomer.outdate,sysdate,8)>0)
			{
				
				des2src(tCard.expiredate,tCustomer.outdate);
			}
		}
		else
		{		
			
			if(tCardtype.validdays<1)
				return E_NOSET_CARDTYPE_VALIDDAYS;
			ret=calcEndDate(sysdate,tCardtype.validdays,tCard.expiredate);
			if(ret)
				return ret;
		}
	}
	else 
	{
		ret=IsInvalidDateTime(tCard.expiredate,"YYYYMMDD");
		if(ret)
			return E_INPUT_EXPIREDATE;
		if(strncmp(tCard.expiredate,sysdate,8)<0)
			return E_INPUT_EXPIREDATE;
	}	
	tCard.custid=tCustomer.custid;
	des2src(tCard.stuempno,tCustomer.stuempno);
	memset(tCard.cardattr,'0',sizeof(tCard.cardattr));
	des2src(tCard.opendate,sysdate);
	getfmtsysdatetime(tCard.lastsaved);
	ret = getNewUniqNo(KEYTYPE_CARDNO,&tCard.cardno);	//获取最大卡号
	if(ret)
	{
		return ret;
	}
	ret=DB_t_card_add(&tCard);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARD_E;
		else
			return E_DB_CARD_I;
	}
	return 0;
}
int F846305(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret=0;
	char sysdate[9]="";
	char systime[7]="";
	char sMsg[256]="";

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	pAccTrans->clear();
	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_CARDRENEW;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	
	ResetNormalCPack(&aPack,0,1);
		
	SetCol(handle,0);


	//检查操作员

	//检查客户
	T_t_customer tCustomer;
	T_t_card  tOldCard;
	
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tOldCard,0,sizeof(tOldCard));	
	
	int cardno=rPack->lvol0;	
	ret=check(cardno,tCustomer,tOldCard);
	if(ret)
		return ret;
	//注销原卡
	ret=DB_t_card_read_lock_by_cur_and_cardno(tOldCard.cardno,&tOldCard);
	if(ret)
	{
		writelog(LOG_ERR,"lost_cardno[%d]",tOldCard.cardno);
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else
			return E_DB_CARD_R;
	}
	tOldCard.status[0]=STATUS_LOGOUT;			//注销
	des2src(tOldCard.closedate,sysdate);		//注销日期
	ret=DB_t_card_update_lock_by_cur(&tOldCard);
	if(ret)
	{
		writelog(LOG_ERR,"lost_cardno[%d]",tOldCard.cardno);
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else
			return E_DB_CARD_R;
	}
	//使用卡片
	T_t_card  tCard;
	memset(&tCard,0,sizeof(tCard));

	des2src(tCard.cardphyid,rPack->sstation0);
	des2src(tCard.showcardno,rPack->sorder0);
	des2src(tCard.expiredate,tOldCard.expiredate);
	tCard.cardtype=tOldCard.cardtype;
	tCard.feetype=tOldCard.feetype;
	des2src(tCard.cardpwd,tOldCard.cardpwd);

	ret=chkShowCardNo(trans.opercode,tCard.cardtype,tCard.showcardno);
	if(ret)
	{
		return ret;
	}
	char cardpwd[33]="";
	char key[17]="";

	//get_init_passwd_by_man_id(tCustomer.idno,cardpwd);
	strcpy(key,STATIC_SEED_KEY);
	EncodePwd(key,cardpwd,tOldCard.cardpwd, 1);
	
	ret=AddCard(tCustomer,tCard);
	if(ret)
		return ret;	
	//添加卡片使用明细
	T_t_carddtl tCarddtl;
	
	memset(&tCarddtl,0,sizeof(tCarddtl));
	/////////////////////////////////rPack2TableStuct////////////////////////
	des2src(tCarddtl.accdate,trans.accdate);
	tCarddtl.termid=trans.termid;
	tCarddtl.termseqno=trans.termseqno;
	tCarddtl.cardtype=tCard.cardtype;
	des2src(tCarddtl.showcardno,tCard.showcardno);
	des2src(tCarddtl.cardphyid,tCard.cardphyid);
	tCarddtl.cardusetype[0]=CARDUSETYPE_OPENCARD;
	des2src(tCarddtl.opercode,trans.opercode);
	ret=DB_t_carddtl_add(&tCarddtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDDTL_E;
		else
			return E_DB_CARDDTL_I;
	}

	//添加换卡记录
	T_t_cardinstead tCardinstead;
	
	memset(&tCardinstead,0,sizeof(tCardinstead));

	des2src(tCardinstead.accdate,trans.accdate);
	tCardinstead.termid=trans.termid;
	tCardinstead.termseqno=trans.termseqno;
	tCardinstead.oldcardno=tOldCard.cardno;
	des2src(tCardinstead.oldcardphyid,tOldCard.cardphyid);
	tCardinstead.cardno=tCard.cardno;
	des2src(tCardinstead.cardphyid,tCard.cardphyid);
	ret=DB_t_cardinstead_add(&tCardinstead);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDINSTEAD_E;
		else
			return E_DB_CARDINSTEAD_I;
	}
	//插入卡位图表
	T_t_cardbitmap tCardBitmap;

	tCardBitmap.cardno=tCard.cardno;
	tCardBitmap.baseno=0;
	memset(tCardBitmap.bitmap,'0',sizeof(tCardBitmap.bitmap));
	tCardBitmap.bitmap[0]='1';
	
	ret=DB_t_cardbitmap_add(&tCardBitmap);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDBITMAP_E;
		else
			return E_DB_CARDBITMAP_I;
	}	

	T_t_account tCardaccount;
	memset(&tCardaccount,0,sizeof(tCardaccount));
	ret=DB_t_account_read_lock_by_c1_and_cardno_and_purseno(tOldCard.cardno,PURSE_NO_ONE,&tCardaccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else 
			return E_DB_ACCOUNT_R;

	}
	tCardaccount.cardno=tCard.cardno;
	//考虑补助
	tCardaccount.availbal= tCardaccount.availbal+ tCardaccount.subsidybal;
	tCardaccount.subsidybal=0;
	tCardaccount.lastcardcnt=1;
	tCardaccount.lastcardbal=tCardaccount.availbal;
	getsysdate(tCardaccount.lasttransdate);
	ret=DB_t_account_update_lock_by_c1(&tCardaccount);
	if(ret)
	{
		return E_DB_ACCOUNT_U;
	}	
	///////////////////////////////
	pAccTrans->trans.usecardflag=1;	
	pAccTrans->trans.custid=tCustomer.custid;
	pAccTrans->trans.feetype=tCard.feetype;
	//////////////////////////////
	pAccTrans->trans.fundtype=rPack->lvol9;
	pAccTrans->trans.inputamt=rPack->damt0;
	
	des2src(pAccTrans->cti.cardaccno,tCardaccount.accno);
	pAccTrans->cti.cardno=tCardaccount.cardno;
	pAccTrans->cti.purseno=tCardaccount.purseno;
	pAccTrans->cti.cardtype=tCard.cardtype;
	pAccTrans->cti.cardbefbal=0;
	pAccTrans->cti.cardaftbal=0;
	pAccTrans->cti.cardcnt=1;
	pAccTrans->cti.calaftbalflag=0;

	ret=pAccTrans->doAccTrans();
	if(ret)
		return ret;
	T_t_cardtransdtl cardtransdtl;
	memset(&cardtransdtl,0,sizeof(cardtransdtl));

	strcpy(cardtransdtl.transdate,trans.transdate);
	strcpy(cardtransdtl.transtime,trans.transtime);
	strcpy(cardtransdtl.accdate,trans.accdate);
	strcpy(cardtransdtl.acctime,trans.acctime);
	cardtransdtl.termid=trans.termid;
	cardtransdtl.termseqno=trans.termseqno;
	cardtransdtl.transcode=trans.transcode;
	des2src(cardtransdtl.opercode,trans.opercode);
	cardtransdtl.status[0]=DTLSTATUS_SUCCESS;
	cardtransdtl.errcode=0;
	ret=DB_t_cardtransdtl_add(&cardtransdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_CARDTRANSDTL_E;
	  else
	    return E_DB_CARDTRANSDTL_I;
	}		
	SetCol(handle,F_LVOL1,F_LSAFE_LEVEL2,F_LVOL5,
        F_SALL_NAME,F_SPAGER,F_SCERT_NO,
        F_SEMAIL2,F_SMARKET_CODE,F_SDATE0,
        F_LVOL0,F_STX_PWD,F_LVOL8,
        F_SORDER0,F_SDATE3,F_SEMP,
        F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol1=tCustomer.custid;
	outPack->lsafe_level2=tCustomer.custtype;
	outPack->lvol5=tCard.feetype;
	des2src(outPack->sall_name,tCustomer.custname);
	des2src(outPack->spager,tCustomer.stuempno);
	des2src(outPack->scert_no,tCustomer.deptcode);
	des2src(outPack->semail2,tCustomer.idno);
	des2src(outPack->smarket_code,tCustomer.sex);
	des2src(outPack->sdate0,tCard.expiredate);
	outPack->lvol0=tCard.cardno;
	des2src(outPack->stx_pwd,cardpwd);
	outPack->lvol8=0;
	des2src(outPack->sorder0,tCard.showcardno);
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
