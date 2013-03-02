/* --------------------------------------------
 * 创建日期: 2008-06-30
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 更新卡信息
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

int UpdCardBaseInfo(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	T_t_card tCard;
	memset(&tCard,0,sizeof(tCard));

	ret=DB_t_card_read_by_cardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
		else 
			return E_DB_CARD_R;
	}
	trans.custid=tCard.custid;
	trans.cardtype=tCard.cardtype;
	trans.feetype=tCard.feetype;
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
	if('1'==tCard.frozeflag[0])
	{
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==tCard.lossflag[0])
	{
		return ERRINFO(E_CARD_LOST,trans.cardno);
	}	
	T_t_customer customer;

	memset(&customer,0,sizeof(customer));
	if(tCard.custid)
	{
		ret=DB_t_customer_read_by_custid(tCard.custid,&customer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CUSTOMER,tCard.custid);
			else
				return E_DB_CUSTOMER_R;
		}
	}	
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_lock_by_c0_and_accno(tCard.accno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_ACCNO,tCard.accno);
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		DB_t_account_free_lock_by_c0();
		return ERRINFO(E_CARDACC_LOGOUT,tCardAccount.accno);
	}
	if(amtcmp(rPack->damt11,0)>=0)
	{
		tCardAccount.singlemaxamt=rPack->damt11;
		if(amtcmp(tCardAccount.singlemaxamt,500)>0)
		{
			DB_t_account_free_lock_by_c0();
			ERRTIP("单次消费限额不能超过500元");
			return E_COMMON_ERR;
		}
	}
	if(amtcmp(rPack->damt12,0)>=0)
	{
		tCardAccount.daycostmaxamt=rPack->damt12;
		if(amtcmp(tCardAccount.daycostmaxamt,10000)>0)
		{
			DB_t_account_free_lock_by_c0();
			ERRTIP("日累计消费限额不能超过10000元");
			return E_COMMON_ERR;
		}
	}
	ret=DB_t_account_update_lock_by_c0(&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_CARDNO_PURSENO_NOACCNO,trans.cardno,trans.purseno);
		else 
			return E_DB_ACCOUNT_U;
	}
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.sysdate);
	strcpy(transdtl.acctime,trans.systime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.paytype=trans.fundtype;
	des2src(transdtl.voucherno,trans.voucherno);
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.cardbefbal=trans.cardbefbal;	
	transdtl.cardcnt=trans.cardcnt;
	transdtl.cardaftbal=trans.cardbefbal;		
	transdtl.managefee=trans.totalfeeamt;
	transdtl.amount=trans.totaltransamt;
	transdtl.custid=trans.custid;
	des2src(transdtl.custname,customer.custname);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
    transdtl.showcardno=atol(tCard.showcardno);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
		return E_DB_TRANSDTL_E;
	  else
		return E_DB_TRANSDTL_I;
	}	

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);	
	ResetNormalCPack(&aPack,0,1);		
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_LSAFE_LEVEL2,F_LVOL4,F_LVOL5,
				F_SALL_NAME,F_SPAGER,F_SCERT_NO,
				F_SEMAIL2,F_SMARKET_CODE,F_SDATE0,
				F_LVOL0,F_STX_PWD,F_LVOL8,F_LVOL6,
				F_SORDER0,F_SEMP,F_LVOL11,F_LVOL12,
				F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol1=customer.custid;
	outPack->lsafe_level2=customer.custtype;
	outPack->lvol5=tCard.feetype;
	strncpy(outPack->sall_name,customer.custname,8);
	des2src(outPack->spager,customer.stuempno);
	des2src(outPack->scert_no,customer.deptcode);
	des2src(outPack->semail2,customer.idno);
	des2src(outPack->smarket_code,customer.sex);
	des2src(outPack->sdate0,tCard.expiredate);
	outPack->lvol0=tCard.cardno;
	outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
	outPack->lvol11=D4U5(tCardAccount.singlemaxamt*100,0);
	outPack->lvol12=D4U5(tCardAccount.daycostmaxamt*100,0);
	outPack->lvol6=tCardAccount.lastcardcnt;
	outPack->lvol4=tCardAccount.lastsubsidyno;
	des2src(outPack->sorder0,tCard.showcardno);
	des2src(outPack->sdate3,pAccTrans->trans.sysdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	des2src(outPack->vsmess,"更新卡信息成功");
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
int UpdCardExpireDate(char *cardexpiredate,TRUSERID *handle,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	T_t_card tCard;
	memset(&tCard,0,sizeof(tCard));
	
	ret=DB_t_card_read_lock_by_cur_and_cardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
		else 
			return E_DB_CARD_R;
	}
	trans.custid=tCard.custid;
	trans.cardtype=tCard.cardtype;
	trans.feetype=tCard.feetype;
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
	if('1'==tCard.frozeflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==tCard.lossflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOST,trans.cardno);
	}	
	//比较卡物理ID是否相同
	if(strcmp(tCard.cardphyid,trans.cardphyid)!=0)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_PHYNO_DIFFER,trans.cardphyid,tCard.cardphyid);
	}
	ret=IsInvalidDateTime(cardexpiredate,"YYYYMMDD");
	if(ret)
		return ret;
	if(strncmp(trans.sysdate,cardexpiredate,8)>=0)
		return ERRINFO(E_CARD_EXPIREDATE,cardexpiredate,trans.sysdate);
	des2src(tCard.expiredate,cardexpiredate);
	getfmtsysdatetime(tCard.lastsaved);
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDNO;
		else 
			return E_DB_CARD_U;
	}
	T_t_customer customer;

	memset(&customer,0,sizeof(customer));
	if(tCard.custid)
	{
		ret=DB_t_customer_read_lock_by_cur_and_custid(tCard.custid,&customer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CUSTOMER,tCard.custid);
			else
				return E_DB_CUSTOMER_R;
		}
		if(strncmp(customer.outdate,cardexpiredate,8)!=0)
		{
			des2src(customer.outdate,cardexpiredate);
			getfmtsysdatetime(customer.lastsaved);
			ret=DB_t_customer_update_lock_by_cur(&customer);
			if(ret)
			{
				return E_DB_CUSTOMER_U;
			}
		}
		else
		{
			DB_t_customer_free_lock_cur();
		}
	}
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_by_accno(tCard.accno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_ACCNO,tCard.accno);
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARDACC_LOGOUT,tCardAccount.accno);
	}	
	trans.custid=tCard.custid;
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.sysdate);
	strcpy(transdtl.acctime,trans.systime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.paytype=trans.fundtype;
	des2src(transdtl.voucherno,trans.voucherno);
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.cardbefbal=trans.cardbefbal;	
	transdtl.cardcnt=trans.cardcnt;
	transdtl.cardaftbal=trans.cardaftbal;		
	transdtl.managefee=trans.totalfeeamt;
	transdtl.amount=trans.totaltransamt;
	transdtl.custid=tCardAccount.custid;
	transdtl.showcardno=atoi(tCard.showcardno);
	des2src(transdtl.custname,customer.custname);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
		return E_DB_TRANSDTL_E;
	  else
		return E_DB_TRANSDTL_I;
	}	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);	
	ResetNormalCPack(&aPack,0,1);		
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_LSAFE_LEVEL2,F_LVOL4,F_LVOL5,
				F_SALL_NAME,F_SPAGER,F_SCERT_NO,
				F_SEMAIL2,F_SMARKET_CODE,F_SDATE0,
				F_LVOL0,F_STX_PWD,F_LVOL8,F_LVOL6,
				F_SORDER0,F_SEMP,F_LVOL11,F_LVOL12,
				F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol1=customer.custid;
	outPack->lsafe_level2=customer.custtype;
	outPack->lvol5=tCard.feetype;
	des2src(outPack->sall_name,customer.custname);
	des2src(outPack->spager,customer.stuempno);
	des2src(outPack->scert_no,customer.deptcode);
	des2src(outPack->semail2,customer.idno);
	des2src(outPack->smarket_code,customer.sex);
	des2src(outPack->sdate0,tCard.expiredate);
	outPack->lvol0=tCard.cardno;
	outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
	outPack->lvol11=D4U5(tCardAccount.singlemaxamt*100,0);
	outPack->lvol12=D4U5(tCardAccount.daycostmaxamt*100,0);
	outPack->lvol6=tCardAccount.lastcardcnt;
	outPack->lvol4=tCardAccount.lastsubsidyno;
	des2src(outPack->sorder0,tCard.showcardno);
	des2src(outPack->sdate3,pAccTrans->trans.sysdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
//		des2src(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
int UpdBadCard(TRUSERID *handle,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	T_t_card tCard;
	memset(&tCard,0,sizeof(tCard));
	if(trans.cardno<1)
	{
		ret=DB_t_card_read_by_cardphyid_and_status(trans.cardphyid,"1",&tCard);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CARDPHYID,trans.cardphyid);
			else 
				return E_DB_CARD_R;
		}
		trans.cardno=tCard.cardno;
	}
	ret=DB_t_card_read_lock_by_cur_and_cardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
		else 
			return E_DB_CARD_R;
	}
	trans.custid=tCard.custid;
	trans.cardtype=tCard.cardtype;
	trans.feetype=tCard.feetype;
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
	if('1'==tCard.frozeflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==tCard.lossflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOST,trans.cardno);
	}	
	//比较卡物理ID是否相同
	if(strcmp(tCard.cardphyid,trans.cardphyid)!=0)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_PHYNO_DIFFER,trans.cardphyid,tCard.cardphyid);
	}
	if('1'!=tCard.badflag[0])
	{
		return ERRINFO(E_CARD_NOBADRECORD,trans.cardno);
	}
	if((CARDBADFLAG_CARDBAL!=tCard.badtype[0])&&(CARDBADFLAG_ACCBAL!=tCard.badtype[0]))
	{
		DB_t_card_free_lock_by_cur();
		ERRTIP("该卡已经登记为卡片损坏,请检查该卡是否完全损坏,如果没有损坏,请修改该卡损坏类型为余额错误类型再来修复");
		return E_COMMON_ERR;
	}
	char badtype=tCard.badtype[0];
	char enddate[9]="";
	ret=calcEndDate(tCard.baddate,pAccTrans->sysPara.iPosdtlMaxDayCnt,enddate);
	if(ret)
	{
		DB_t_card_free_lock_by_cur();				
		return ret;
	}
	if(strncmp(enddate,trans.transdate,8)>0)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_BADCARD_RECORDDATE_NOTREACH,enddate);
	}
	tCard.badflag[0]='0';
	tCard.badtype[0]=0;
	tCard.baddate[0]=0;
	getfmtsysdatetime(tCard.lastsaved);
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
		else 
			return E_DB_CARD_U;
	}
	T_t_customer customer;

	memset(&customer,0,sizeof(customer));
	if(tCard.custid)
	{
		ret=DB_t_customer_read_by_custid(tCard.custid,&customer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CUSTOMER,tCard.custid);
			else
				return E_DB_CUSTOMER_R;
		}
	}
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_lock_by_c0_and_accno(tCard.accno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDACCNO,tCard.accno);
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		DB_t_account_free_lock_by_c0();
		return ERRINFO(E_CARDACC_LOGOUT,tCardAccount.accno);
	}	
	if(CARDBADFLAG_ACCBAL==badtype)
	{
		//以卡修库
		if(amtcmp(tCardAccount.availbal,trans.cardbefbal)<0)
		{
			//在卡比库大的时候不允许更新
			DB_t_account_free_lock_by_c0();		
			ERRTIP("卡余额比账户余额大,不允许以卡修库");
			return E_COMMON_ERR;
		}
		if(amtcmp(tCardAccount.availbal,trans.cardbefbal)==0)
		{
			DB_t_account_free_lock_by_c0();		
			ERRTIP("卡余额与账户余额已经相等,不需要以卡修库");
			return E_COMMON_ERR;
		}
		//库余额错误，以卡余额为准，但必须卡余额小于库余额
		//更新账户余额与卡余额一致
		trans.cardaftbal=trans.cardbefbal;
		tCardAccount.lastcardbal = trans.cardaftbal;
		tCardAccount.lastcardcnt = trans.cardcnt;
		strcpy(tCardAccount.lasttransdate,trans.sysdate);
		ret=DB_t_account_update_lock_by_c0(&tCardAccount);
		if(ret)
		{
			return E_DB_ACCOUNT_U;
		}		
		//考虑消费流水丢失的情况,走长款处理
		trans.cardflag=0;//一定要设为无卡
		trans.transamt=D4U5(tCardAccount.availbal-trans.cardbefbal);
		trans.inputamt=trans.transamt;
		trans.fundtype=0;
		des2src(trans.cardaccno,tCardAccount.accno);
		pAccTrans->trans.transtype=TRANSTYPE_MORE_CARDBALINCOME;
		ret=pAccTrans->DoTransByTransType();
		if(ret)
			return ret;
		if(pAccTrans->trans.unusedamt>0)
			return E_INPUT_AMT;
		if(pAccTrans->trans.unusedamt<0)
			return E_AMT_LACK;
	}
	else
	{
		//卡余额错误,把库余额写入卡余额
		//更新卡余额与账户余额一致
		if(trans.cardcnt>tCardAccount.lastcardcnt)
			tCardAccount.lastcardcnt = trans.cardcnt;
		tCardAccount.lastcardbal = tCardAccount.availbal;
		strcpy(tCardAccount.lasttransdate,trans.sysdate);
		ret=DB_t_account_update_lock_by_c0(&tCardAccount);
		if(ret)
		{
			return E_DB_ACCOUNT_U;
		}
		trans.cardcnt=tCardAccount.lastcardcnt;
		trans.cardaftbal=tCardAccount.availbal;
	}

	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	des2src(transdtl.accdate,pAccTrans->trans.sysdate);
	des2src(transdtl.acctime,trans.transtime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.paytype=trans.fundtype;
	des2src(transdtl.voucherno,trans.voucherno);
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.cardbefbal=trans.cardbefbal;	
	transdtl.cardcnt=trans.cardcnt;
	transdtl.cardaftbal=trans.cardaftbal;		
	transdtl.managefee=trans.totalfeeamt;
	transdtl.amount=trans.totaltransamt;
	transdtl.custid=tCardAccount.custid;
	des2src(transdtl.custname,tCardAccount.accname);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	transdtl.showcardno=atol(tCard.showcardno);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
		return E_DB_TRANSDTL_E;
	  else
		return E_DB_TRANSDTL_I;
	}	

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);	
	ResetNormalCPack(&aPack,0,1);		
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_LSAFE_LEVEL2,F_LVOL4,F_LVOL5,
				F_SALL_NAME,F_SPAGER,F_SCERT_NO,
				F_SEMAIL2,F_SMARKET_CODE,F_SDATE0,
				F_LVOL0,F_STX_PWD,F_LVOL8,F_LVOL6,
				F_SORDER0,F_SEMP,F_LVOL11,F_LVOL12,
				F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol1=customer.custid;
	outPack->lsafe_level2=customer.custtype;
	outPack->lvol5=tCard.feetype;
	strncpy(outPack->sall_name,customer.custname,8);
	des2src(outPack->spager,customer.stuempno);
	des2src(outPack->scert_no,customer.deptcode);
	des2src(outPack->semail2,customer.idno);
	des2src(outPack->smarket_code,customer.sex);
	des2src(outPack->sdate0,tCard.expiredate);
	outPack->lvol0=tCard.cardno;
	outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
	outPack->lvol11=D4U5(tCardAccount.singlemaxamt*100,0);
	outPack->lvol12=D4U5(tCardAccount.daycostmaxamt*100,0);
	outPack->lvol6=tCardAccount.lastcardcnt;
	outPack->lvol4=tCardAccount.subsidyno;
	des2src(outPack->sorder0,tCard.showcardno);
	des2src(outPack->sdate3,pAccTrans->trans.sysdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	des2src(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
int RewriteCardInfo(TRUSERID *handle,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	T_t_card tCard;
	memset(&tCard,0,sizeof(tCard));

	ret=DB_t_card_read_by_cardphyid_and_status(trans.cardphyid,"1",&tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDPHYID,trans.cardphyid);
		else 
			return E_DB_CARD_R;
	}
	trans.cardno=tCard.cardno;
	trans.custid=tCard.custid;
	trans.cardtype=tCard.cardtype;
	trans.feetype=tCard.feetype;
//	if(tCard.status[0]!=STATUS_NORMAL)
//	{
//		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
//	}	
	if('1'==tCard.frozeflag[0])
	{
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==tCard.lossflag[0])
	{
		return ERRINFO(E_CARD_LOST,trans.cardno);
	}	
    char cardpwd[33]="";
    char key[17]="";
    strcpy(key,STATIC_SEED_KEY);
    EncodePwd(key,cardpwd,tCard.cardpwd, 1);

	T_t_customer customer;

	memset(&customer,0,sizeof(customer));
	if(tCard.custid)
	{
		ret=DB_t_customer_read_by_custid(tCard.custid,&customer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CUSTOMER,tCard.custid);
			else
				return E_DB_CUSTOMER_R;
		}
	}	
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_by_accno(tCard.accno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_ACCNO,tCard.accno);
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARDACC_LOGOUT,tCardAccount.accno);
	}
	if(trans.cardcnt>1||tCardAccount.lastcardcnt>1)
	{
		ERRTIP("该卡已使用,不能重写卡信息");
		return ERRINFO(E_CARD_USED,trans.cardno);
	}
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.sysdate);
	strcpy(transdtl.acctime,trans.systime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.paytype=trans.fundtype;
	des2src(transdtl.voucherno,trans.voucherno);
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.cardbefbal=trans.cardbefbal;	
	transdtl.cardcnt=tCardAccount.lastcardcnt;
	transdtl.cardaftbal=tCardAccount.lastcardbal;		
	transdtl.managefee=trans.totalfeeamt;
	transdtl.amount=trans.totaltransamt;
	transdtl.custid=trans.custid;
	des2src(transdtl.custname,customer.custname);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
		return E_DB_TRANSDTL_E;
	  else
		return E_DB_TRANSDTL_I;
	}	

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);	
	ResetNormalCPack(&aPack,0,1);		
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_LSAFE_LEVEL2,F_LVOL4,F_LVOL5,
				F_SALL_NAME,F_SPAGER,F_SCERT_NO,
				F_SEMAIL2,F_SMARKET_CODE,F_SDATE0,
				F_LVOL0,F_STX_PWD,F_LVOL8,F_LVOL6,
				F_SORDER0,F_SEMP,F_LVOL11,F_LVOL12,
				F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol0=trans.cardno;
	outPack->lvol1=trans.custid;
	outPack->lsafe_level2=customer.custtype;
	outPack->lvol5=tCard.feetype;
	strncpy(outPack->sall_name,customer.custname,8);
	des2src(outPack->spager,customer.stuempno);
	des2src(outPack->scert_no,customer.deptcode);
	des2src(outPack->semail2,customer.idno);
	des2src(outPack->smarket_code,customer.sex);
	des2src(outPack->sdate0,tCard.expiredate);
	outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
	outPack->lvol6=tCardAccount.lastcardcnt;
	outPack->lvol11=D4U5(tCardAccount.singlemaxamt*100,0);
	outPack->lvol12=D4U5(tCardAccount.daycostmaxamt*100,0);
	outPack->lvol4=tCardAccount.lastsubsidyno;
	des2src(outPack->sorder0,tCard.showcardno);
	des2src(outPack->sdate3,pAccTrans->trans.sysdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
    des2src(outPack->stx_pwd,cardpwd);
	des2src(outPack->vsmess,"重写卡信息成功");
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
int ClearCardInfo(TRUSERID *handle,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;

	T_t_card tCard;
	memset(&tCard,0,sizeof(tCard));

	ret=DB_t_card_read_by_cardphyid_and_status(trans.cardphyid,"1",&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
		{
			ST_CPACK aPack;
			ST_PACK *outPack = &(aPack.pack);	
			ResetNormalCPack(&aPack,0,1);		
			SetCol(handle,0);
			SetCol(handle,F_LVOL0,F_VSMESS,0);	
			strcpy(outPack->vsmess,"该卡信息可以清空");
			PutRow(handle,outPack,pRetCode,szMsg);
			return 0;
		}
		else 
			return E_DB_CARD_R;
	}
	ERRTIP("该卡未注销，不能清空卡信息");
	return E_COMMON_ERR;
}
int F846320(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char cardexpiredate[9]="";
	CAccTrans *pAccTrans=CAccTrans::getInstance();
//	GetCpackDataString(rPack,pAccTrans->cpackdata);
//	writelog(LOG_INFO,"cpack:[%s]",pAccTrans->cpackdata);
//	writelog(LOG_INFO,"%s:846320 Start",getdbtimestamp(NULL));

	ret=pAccTrans->CheckCfgUpdate();
	if(ret)
		return ret;
	TRANS& trans=pAccTrans->trans;
	des2src(pAccTrans->trans.opercode,rPack->semp);
    trans.termid=rPack->lwithdraw_flag;
	
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.cardno=rPack->lvol0;	
	trans.purseno=PURSE_NO_ONE;
	trans.cardcnt=rPack->lvol6;
	trans.cardbefbal=rPack->lvol7/100.0;
	trans.cardaftbal=trans.cardbefbal;
	des2src(trans.cardphyid,rPack->sstation1);
	des2src(cardexpiredate,rPack->sdate0);

	char updateflag=rPack->sstatus1[0];
	switch(updateflag)
	{
			case '1'://更新基本信息
				trans.transcode=TC_CARDUPDBASEINFO;
				ret=pAccTrans->InitTrans();
				if(ret)
					return ret; 
				ret=UpdCardBaseInfo(handle,rPack,pRetCode,szMsg);
				if(ret)
					return ret;
				break;
			case '2'://延长有效期
				trans.transcode=TC_CARDUPDEXPIREDATE;
				ret=pAccTrans->InitTrans();
				if(ret)
					return ret; 	
				ret=UpdCardExpireDate(cardexpiredate,handle,pRetCode,szMsg);
				if(ret)
					return ret;
				break;
			case '3'://坏卡修复
				trans.transcode=TC_CARDUPDBADCARD;		
				ret=pAccTrans->InitTrans();
				if(ret)
					return ret; 		
				ret=UpdBadCard(handle,pRetCode,szMsg);
				if(ret)
					return ret;
				break;
			case '4'://重写卡信息
				trans.transcode=TC_CARDREWRITE;		
				ret=pAccTrans->InitTrans();
				if(ret)
					return ret;
				ret=RewriteCardInfo(handle,pRetCode,szMsg);
				if(ret)
					return ret;
				break;
			case '5'://清空卡信息
				trans.transcode=TC_CARDCLEAR; 	
				ret=pAccTrans->InitTrans();
				if(ret)
					return ret; 
				ret=ClearCardInfo(handle,pRetCode,szMsg);
				if(ret)
					return ret;
				break;
			default:
				return E_UPDCARDTYPE;
	}
	return ret;
}
