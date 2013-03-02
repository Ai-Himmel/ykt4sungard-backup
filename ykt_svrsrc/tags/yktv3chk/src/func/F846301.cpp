/* --------------------------------------------
 * 创建日期: 2008-06-04
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通开户
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
static int doCustomer(int custid,T_t_cardtype& tCardtype,T_t_customer& tCustomer)
{
	int ret=0;
	ret=DB_t_customer_read_lock_by_cur_and_custid(custid,&tCustomer);
	if(ret)
	{		
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.status[0]==STATUS_LOGOUT)
	{
		DB_t_customer_free_lock_cur();
		return E_CUSTOMER_LOGOUT;
	}
	if(tCustomer.feetype<1)
	{
		DB_t_customer_free_lock_cur();
		return E_NOSET_CUSTOMER_FEETYPE;
	}
	if(tCustomer.holdcardcnt)
	{		
		//检查该客户是否存在状态正常的卡
		T_t_card tCard;
		memset(&tCard,0,sizeof(tCard));
		ret=DB_t_card_read_by_custid_and_status_and_lossflag(tCustomer.custid,"1","0",&tCard);
		if(ret)
		{
			if(DB_NOTFOUND!=ret)
			{
				DB_t_customer_free_lock_cur();				
				return E_DB_CARD_R;
			}
		}
		else
		{
			//存在则不允许发卡
			DB_t_customer_free_lock_cur();				
			return E_CUSTOMER_HAVE_CARD;			
		}
		ret=DB_t_cardtype_read_by_cardtype(tCard.cardtype,&tCardtype);
		if(ret)
		{
			DB_t_customer_free_lock_cur();
			if(DB_NOTFOUND==ret)
				return E_DB_CARDTYPE_N;
			else
				return E_DB_CARDTYPE_R;
		}
		if(tCardtype.multicardable[0]=='0')
		{
			ret=DB_t_card_read_by_custid_and_status_and_cardtype(tCustomer.custid,"1",tCard.cardtype,&tCard);
			if(ret)
			{
				if(DB_NOTFOUND!=ret)
				{
					DB_t_customer_free_lock_cur();				
					return E_DB_CARD_R;
				}
			}
			else
			{
				//不允许发同类卡
				DB_t_customer_free_lock_cur();				
				return E_CUST_THISTYPECARD_EXIST;			
			}
		}
	}	
	tCustomer.useflag[0]='1';
	tCustomer.holdcardcnt++;
	getfmtsysdatetime(tCustomer.lastsaved);
	ret=DB_t_customer_update_lock_by_cur(&tCustomer);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_U;
	}
	return 0;
}

static int doCard(TRANS& trans,T_t_customer& tCustomer,T_t_cardtype& tCardtype,T_t_card& tCard)
{
	//检查卡是否已经使用
	int ret=0;
	char sysdate[9];
	getsysdate(sysdate);

	ret=chkShowCardNo(trans.opercode,tCard.cardtype,tCard.showcardno);
	if(ret)
	{
		return ret;
	}
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
	char cardpwd[33]="";
	char key[17]="";
	get_init_passwd_by_man_id(tCustomer.idno,cardpwd);
	strcpy(key,STATIC_SEED_KEY);
	EncodePwd(key,cardpwd,tCard.cardpwd, 0);
	
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
	//添加卡片使用明细记录
	T_t_carddtl tCarddtl;
	
	memset(&tCarddtl,0,sizeof(tCarddtl));
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
	T_t_cardver cardver;

	memset(&cardver,0,sizeof(cardver));
	cardver.cardno=tCard.cardno;
	des2src(cardver.accdate,trans.accdate);
	cardver.termid=trans.termid;
	cardver.termseqno=trans.termseqno;
	cardver.cardno=tCard.cardno;
	des2src(cardver.cardphyid,tCard.cardphyid);
	cardver.cardvertype=CARDVERTYPE_CARDOPEN;
	
	ret=addCardVerNo(cardver);
	if(ret)
		return ret;
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
	
	return 0;
}
static int doAccBook(TRANS& trans)
{

	return 0;
}
int F846301(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret=0;
	char sysdate[9]="";
	char systime[7]="";
	char sMsg[256]="";
	char anonymflag[2]="";

	CARDTRANSINFO cti;

	memset(&cti,0,sizeof(cti));

	//获取业务日期、流水号
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->clear();
	TRANS& trans=pAccTrans->trans;
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_CARDOPEN;
	ret=pAccTrans->addOperDtl();
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
//	des2src(cardtransdtl.collectdate,rPack->sdate1);
//	des2src(cardtransdtl.collecttime,rPack->stime1);
	cardtransdtl.transcode=trans.transcode;
	cardtransdtl.paytype=rPack->lvol9;
	des2src(cardtransdtl.voucherno,rPack->scust_auth2);
	cardtransdtl.purseno=PURSE_NO_ONE;
	cardtransdtl.cardcnt=1;
	cardtransdtl.cardbefbal=0;
	cardtransdtl.amount=0;
////	cardtransdtl.frontno=0;
	//des2src(cardtransdtl.devphyid,rPack->sname);
	//cardtransdtl.devseqno=rPack->lserial0;
	//des2src(cardtransdtl.bankcode,rPack->sbank_code);
	//des2src(cardtransdtl.bankcardno,rPack->scard0);
	//des2src(cardtransdtl.mobile,rPack->sphone2);
	des2src(cardtransdtl.opercode,trans.opercode);
	cardtransdtl.status[0]=DTLSTATUS_SUCCESS;
	cardtransdtl.revflag[0]='0';
	cardtransdtl.errcode=0;
	
	cardtransdtl.custid=rPack->lvol1;
	
	//int cardtype=0;
	int feetype=0;

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	memset(&aPack,0,sizeof(aPack));
	
	ResetNormalCPack(&aPack,0,1);
		
	SetCol(handle,0);

	getsysdate(sysdate);
	getsystime(systime);
	des2src(anonymflag,rPack->sstatus1);


	//检查客户
	T_t_customer tCustomer;
	T_t_cardtype tCardtype;
	
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tCardtype,0,sizeof(tCardtype));
	tCustomer.custid=cardtransdtl.custid;
	tCardtype.cardtype=rPack->lsafe_level;
	if(tCustomer.custid)
	{
		ret=doCustomer(tCustomer.custid,tCardtype,tCustomer);
		if(ret)
			return ret;
		feetype=tCustomer.feetype;
		//对于已发过卡的客户
	}
	else
	{
		if(anonymflag[0]!='1')
			return E_CUSTOMER_NOT_EXIST;
		
		ret=DB_t_cardtype_read_by_anonymflag(anonymflag,&tCardtype);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_NOCFG_ANONYMCARDTYPE;
			else
				return E_DB_CARDTYPE_R;
		}
		//cardtype=tCardtype.cardtype;
		feetype=tCardtype.feetype;
		if(!feetype)
			return E_NOCFG_ANONYMCARD_FEETYPE;
	}

	T_t_card tCard;
	memset(&tCard,0,sizeof(tCard));

	des2src(tCard.cardphyid,rPack->sstation0);
	des2src(tCard.showcardno,rPack->sorder0);
	des2src(tCard.expiredate,rPack->sdate0);
	tCard.cardtype=tCardtype.cardtype;
	tCard.feetype=feetype;
	if(!strlen(tCard.cardphyid))
		return E_INPUT_CARDPHYID;
	if(!strlen(tCard.showcardno))
		return E_INPUT_SHOWCARDNO;

	char cardpwd[33]="";
	char key[17]="";

	get_init_passwd_by_man_id(tCustomer.idno,cardpwd);
	strcpy(key,STATIC_SEED_KEY);
	EncodePwd(key,cardpwd,tCard.cardpwd, 0);

	ret=doCard(trans,tCustomer,tCardtype,tCard);
	if(ret)
		return ret;
	T_t_purse tPurse;
	memset(&tPurse,0,sizeof(tPurse));

	ret=DB_t_purse_read_by_purseno(PURSE_NO_ONE,&tPurse);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_PURSE_N;
		else
			return E_DB_PURSE_R;
	}
	if(tPurse.maxbal<1)
	{
		return E_NOSET_PURSE_MAXBALA;
	}

//	创建账号
	T_t_account tCardaccount;
	memset(&tCardaccount,0,sizeof(tCardaccount));
	ret = getNewActno(tCardaccount.accno);  	    									//获得最大帐号
	if (ret)
	{
		return ret;
	}
	des2src(tCardaccount.accname,tCustomer.custname);
	des2src(tCardaccount.subjno,SUBJECT_INDIVIDUALSAVING);
	des2src(tCardaccount.accpwd,tCard.cardpwd);
	tCardaccount.custid=tCustomer.custid;
	tCardaccount.cardno=tCard.cardno;
	tCardaccount.purseno=PURSE_NO_ONE;
	tCardaccount.cardmaxbal=tPurse.maxbal;
	tCardaccount.status[0]=STATUS_NORMAL;
	getsysdate(tCardaccount.lasttransdate);
	getsysdate(tCardaccount.opendate);
	tCardaccount.acctype=ACCTYPE_CARD;
	ret=DB_t_account_add(&tCardaccount);
	if(ret)
	{
	    if(DB_REPEAT==ret)
	        return E_DB_CARDACCOUNT_E;
	    else
	        return E_DB_CARDACCOUNT_I;
	}	
	memcpy(&pAccTrans->trans,&trans,sizeof(trans));
	///////////////////////////////
	pAccTrans->trans.transcode=iRequest;
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
	pAccTrans->cti.devseqno=trans.termseqno;
	pAccTrans->cti.calaftbalflag=0;
	strcpy(pAccTrans->trans.craccno,tCardaccount.accno);
	ret=pAccTrans->doFeeTrans();
	if(ret)
		return ret;
	ret=pAccTrans->doMainTrans();
	if(ret)
		return ret;
	if(trans.unusedamt>0)
		return E_INPUT_AMT;
	if(trans.unusedamt<0)
		return E_AMT_LACK;
	cardtransdtl.cardno=tCard.cardno;
	cardtransdtl.cardaftbal=pAccTrans->trans.cardaftbal;
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
