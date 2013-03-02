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
#include "transfunc.h"
int F846305(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int freefeeflag=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=TC_CARDRENEW;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	char backcardtype=rPack->sstat_type[0]; //C、以卡为准 A、以账户为准
		
	TRANS& trans=pAccTrans->trans;

	trans.usecardflag=1;
	trans.cardno=rPack->lvol0;
	trans.dpscnt=rPack->lvol5;
	trans.paycnt=rPack->lvol6;
	des2src(trans.showcardno,rPack->sorder0);
	des2src(trans.cardphyid,rPack->sstation0);
	if (!strlen(trans.cardphyid))
	    return E_INPUT_CARDPHYID;

	T_t_cardphytype tCardPhyType;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	
	ResetNormalCPack(&aPack,0,1);

		
	SetCol(handle,0);

	//检查卡
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
	trans.cardtype=tCard.cardtype;
	trans.feetype=tCard.feetype;
	trans.custid=tCard.custid;

	/*
	if(tCard.cardphytype!=rPack->lserial0)
	{
		DB_t_card_free_lock_by_cur();
		ERRTIP("补办选择卡物理类型%d与原卡物理类型%d不符",rPack->lserial0,tCard.cardphytype);
		return E_COMMON_ERR;
	}
	*/
    T_t_cardphytype tCardphytype;
    memset(&tCardphytype,0,sizeof(tCardphytype));
    ret=DB_t_cardphytype_read_by_cardphytype(tCard.cardphytype,&tCardphytype);
    if(ret)
    {
		DB_t_card_free_lock_by_cur();
		if(DB_NOTFOUND==ret)
			return E_DB_CARDPHYTYPE_N;
		else
			return E_DB_CARDPHYTYPE_R;
    }
    if(tCardphytype.cardphytypecode)
    {
		if(tCardphytype.cardphytypecode!=rPack->lvol3)
		{
			DB_t_card_free_lock_by_cur();
			ERRTIP("卡物理类型代码%X与系统代码%X不符",rPack->lvol3,tCardphytype.cardphytypecode);
			return E_COMMON_ERR;
		}
    }
    
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}
	if('1'==tCard.badflag[0])
	{
		if((CARDBADFLAG_CARDBAL==tCard.badtype[0])||(CARDBADFLAG_ACCBAL==tCard.badtype[0]))
		{
			DB_t_card_free_lock_by_cur();
			ERRTIP("该卡余额错误,请使用坏卡修复功能来处理,不必补办");
			return E_CARD_BAD_AND_NEED_UPDATE;
		}
	}
	//无卡只有挂失或卡物理损坏的情况下才可以补办卡
	if(tCard.lossflag[0]!='1'&&
		tCard.badflag[0]!='1')
	{
		DB_t_card_free_lock_by_cur();
		ERRTIP("该卡状态正常,不能补办");
		return E_COMMON_ERR;
	}


	//检查该客户是否存在未注销的卡
//	ret=IsExistOtherCardByCustid(tCard.custid,tCard.cardno);
	ret=IsExistNormalTmpCardByCustid(tCard.custid);
	if(ret)
	{
		DB_t_card_free_lock_by_cur();
		if(DB_EXIST==ret)
		{
			ERRTIP("该客户存在正常的过渡临时卡,请先注销过渡临时卡再补办");
			return E_EXIST_OTHERCARD;
		}
		else
			return ret;
	}
	if('1'==tCard.badflag[0])
	{
		//检查卡是否到了销卡的时间
		char enddate[9]={0};
		ret=calcEndDate(tCard.baddate,pAccTrans->sysPara.iRenewCardDayCnt,enddate);
		if(ret)
		{
			DB_t_card_free_lock_by_cur();		
			return ret;
		}
		if(strncmp(enddate,pAccTrans->trans.transdate,8)>0)
		{
			DB_t_card_free_lock_by_cur();	
			ERRTIP("请等到期后再补办");
			return ERRINFO(E_BADCARD_RECORDDATE_NOTREACH,enddate);
		}
		if(CARDBADFLAG_QUALITY==tCard.badtype[0])
			freefeeflag=1;
	}	
	else if('1'==tCard.lossflag[0])
	{
		char enddate[9]={0};
		if(strlen(tCard.lossdate))
		{
			ret=calcEndDate(tCard.lossdate,pAccTrans->sysPara.iRenewCardDayCnt,enddate);
			if(ret)
			{
				DB_t_card_free_lock_by_cur();		
				return ret;
			}
			if(strncmp(enddate,pAccTrans->trans.transdate,8)>0)
			{
				DB_t_card_free_lock_by_cur();		
				ERRTIP("请等到期后再补办");
				return ERRINFO(E_CARDLOSSDATE_NOREACH,enddate);
			}
		}
	}	
	ret=getCardVerNo(tCard.cardverno);
	if(ret)
	{
		DB_t_card_free_lock_by_cur();		
		return ret;
	}
	tCard.status[0]=STATUS_DELETE;
	strcpy(tCard.closedate,trans.transdate);
	des2src(tCard.lastsaved,trans.sysdatetime);
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,tCard.cardno);
		else 
			return E_DB_CARD_U;
	}
	//删除卡库不平表该卡的记录
	ret=DelCardAccDiffByCardno(trans.cardno);
	if(ret)
		return ret;
	T_t_customer tCustomer;

	memset(&tCustomer,0,sizeof(tCustomer));
	if(trans.custid>0)
	{
		ret=DB_t_customer_read_by_custid(trans.custid,&tCustomer);
		if(ret)
		{		
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CUSTOMER,trans.custid);
			else
				return E_DB_CUSTOMER_R;
		}
		trans.custid=tCustomer.custid;
		des2src(trans.custname,tCustomer.custname);
		des2src(trans.stuempno,tCustomer.stuempno);
	}
	
	T_t_cardtyperight cardtyperight;

	memset(&cardtyperight,0,sizeof(cardtyperight));
	ret=DB_t_cardtyperight_read_by_cardtype_and_feetype(tCard.cardtype,tCard.feetype,&cardtyperight);
	if(ret)
	{
		writelog(LOG_ERR,"cardtype[%d]feetype[%d]",tCard.cardtype,tCard.feetype);
		if(DB_NOTFOUND==ret)
			return E_NOCARDTYPERIGHT;
		else 
			return E_DB_CARDTYPERIGHT_R;
	}
	////添加旧卡版本号记录
	T_t_cardver cardver;

	memset(&cardver,0,sizeof(cardver));
	cardver.cardno=tCard.cardno;
	des2src(cardver.accdate,pAccTrans->trans.accdate);
	cardver.termid=trans.termid;
	cardver.termseqno=trans.termseqno;
	cardver.cardno=tCard.cardno;
	cardver.status[0]=STATUS_NORMAL;	
	des2src(cardver.cardphyid,tCard.cardphyid);
	des2src(cardver.stuempno,trans.stuempno);
	cardver.cardvertype=CARDVERTYPE_CARDCLOSE;
	des2src(cardver.cardverno,tCard.cardverno);
	ret=DB_t_cardver_add(&cardver);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDVER_E;
		else
			return E_DB_CARDVER_I;
	}
	T_t_card  tCardTest;
    ret=DB_t_card_read_by_cardphyid_and_status(trans.cardphyid,"1",&tCardTest);
    if (ret!=DB_NOTFOUND)
    {
        if (DB_SUCCESS==ret)
            return ERRINFO(E_EXIST_CARDPHYID,trans.cardphyid);
        else
            return E_DB_CARD_R;
    }
	if(pAccTrans->sysPara.bEnableCardMgr)
	{
		//使用新的显示卡号
	    if (!strlen(trans.showcardno))
    	    return E_INPUT_SHOWCARDNO;
	    ret=DB_t_card_read_by_showcardno_and_status(trans.showcardno,"1",&tCardTest);
	    if (ret!=DB_NOTFOUND)
	    {
	        if (DB_SUCCESS==ret)
	            return ERRINFO(E_EXIST_SHOWCARDNO,trans.showcardno);
	        else
	            return E_DB_CARD_R;
	    }
		int cardtype=0;
		ret=UseShowCardNo(trans.opercode,trans.showcardno,cardtype);
		if(ret)
		{
			return ret;
		}
		if(cardtype!=tCard.cardtype)
		{
			return ERRINFO(E_DIFF_CARDTYPE,cardtype,tCard.cardtype);
		}
		T_t_carddtl carddtl;
		memset(&carddtl,0,sizeof(carddtl));
		
		des2src(carddtl.accdate,trans.accdate);
		des2src(carddtl.acctime,trans.acctime);
		carddtl.termid=trans.termid;
		carddtl.termseqno=trans.termseqno;
		des2src(carddtl.opercode,trans.opercode);
		carddtl.cardtype=tCard.cardtype;
		carddtl.usetype=CARDUSETYPE_USE;
		carddtl.inoutflag=INOUTFLAG_OUT;
		carddtl.transcnt=1;
		strcpy(carddtl.summary,"补办卡");
		des2src(carddtl.cardphyid,trans.cardphyid);
		des2src(carddtl.showcardno,trans.showcardno);
		ret=DB_t_carddtl_add(&carddtl);
		if(ret)
		{
			if(DB_REPEAT==ret)
				return E_DB_CARDDTL_E;
			else
				return E_DB_CARDDTL_I;
		}
	}
	//使用卡片
	T_t_card  tNewCard;
	memset(&tNewCard,0,sizeof(tNewCard));

	des2src(tNewCard.cardphyid,trans.cardphyid);
	des2src(tNewCard.showcardno,trans.showcardno);
	des2src(tNewCard.expiredate,tCard.expiredate);
	des2src(tNewCard.accno,tCard.accno);
	tNewCard.cardtype=tCard.cardtype;
	tNewCard.feetype=tCard.feetype;
	des2src(tNewCard.cardpwd,tCard.cardpwd);
	tNewCard.custid=tCustomer.custid;
	tNewCard.lossflag[0]='0';
	tNewCard.frozeflag[0]='0';
	tNewCard.badflag[0]='0';
	tNewCard.lockflag[0]='0';
	tNewCard.status[0]=STATUS_NORMAL;
	tNewCard.cardphytype=tCard.cardphytype;
	des2src(tNewCard.opendate,pAccTrans->trans.transdate);
	des2src(tNewCard.lastsaved,trans.sysdatetime);
	ret = getNewUniqNo(KEYTYPE_CARDNO,&tNewCard.cardno);	//获取最大卡号
	if(ret)
	{
		return ret;
	}
	ret=getCardVerNo(tNewCard.cardverno);
	if(ret)
	{
		return ret;
	}
	ret=DB_t_card_add(&tNewCard);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARD_E;
		else
			return E_DB_CARD_I;
	}
	////添加新卡版本号记录
//	T_t_cardver cardver;

	memset(&cardver,0,sizeof(cardver));
	des2src(cardver.accdate,pAccTrans->trans.accdate);
	cardver.termid=trans.termid;
	cardver.termseqno=trans.termseqno;
	cardver.cardno=tNewCard.cardno;
	cardver.status[0]=STATUS_NORMAL;	
	des2src(cardver.cardphyid,tNewCard.cardphyid);
	des2src(cardver.stuempno,trans.stuempno);
	cardver.cardvertype=CARDVERTYPE_CARDOPEN;
	des2src(cardver.cardverno,tNewCard.cardverno);
	ret=DB_t_cardver_add(&cardver);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDVER_E;
		else
			return E_DB_CARDVER_I;
	}
	//添加换卡记录
	T_t_cardnochange tCardnoChange;
	
	memset(&tCardnoChange,0,sizeof(tCardnoChange));
	des2src(tCardnoChange.changedate,pAccTrans->trans.accdate);
	tCardnoChange.oldcardno=tCard.cardno;
	tCardnoChange.newcardno=tNewCard.cardno;
	ret=DB_t_cardnochange_add(&tCardnoChange);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDNOCHANGE_E;
		else
			return E_DB_CARDNOCHANGE_I;
	}
	//插入卡位图表
	T_t_cardbitmap tCardBitmap;

	memset(&tCardBitmap,0,sizeof(tCardBitmap));
	tCardBitmap.cardno=tNewCard.cardno;

	int num=(trans.paycnt-1)/1000;	
	if(num<1)
	{
		if(trans.paycnt>900)
			tCardBitmap.baseno=500;
		else
			tCardBitmap.baseno=0;
	}
	else
	{
		int offsetcnt= trans.paycnt - num*1000;
		if(offsetcnt<100)
			tCardBitmap.baseno = num*1000-500;
		else if(offsetcnt>600)
			tCardBitmap.baseno = num*1000+500;
		else
			tCardBitmap.baseno = num*1000;
	}
    memset(tCardBitmap.bitmap0,'0',sizeof(tCardBitmap.bitmap0)-1);
    memset(tCardBitmap.bitmap1,'0',sizeof(tCardBitmap.bitmap1)-1);
    memset(tCardBitmap.bitmap2,'0',sizeof(tCardBitmap.bitmap2)-1);
    memset(tCardBitmap.bitmap3,'0',sizeof(tCardBitmap.bitmap3)-1);
    memset(tCardBitmap.bitmap4,'0',sizeof(tCardBitmap.bitmap4)-1);
    memset(tCardBitmap.bitmap5,'0',sizeof(tCardBitmap.bitmap5)-1);
    memset(tCardBitmap.bitmap6,'0',sizeof(tCardBitmap.bitmap6)-1);
    memset(tCardBitmap.bitmap7,'0',sizeof(tCardBitmap.bitmap7)-1);
    memset(tCardBitmap.bitmap8,'0',sizeof(tCardBitmap.bitmap8)-1);
    memset(tCardBitmap.bitmap9,'0',sizeof(tCardBitmap.bitmap9)-1);
	ret=DB_t_cardbitmap_add(&tCardBitmap);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDBITMAP_E;
		else
			return E_DB_CARDBITMAP_I;
	}	
	//领取补助
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_by_accno(tNewCard.accno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDACCNO,tNewCard.accno);
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARDACC_LOGOUT,tCardAccount.accno);
	}
	double subsidyamt=0;
	int maxsubsidyno=0;
	//检查补助信息
	ret = UpdAllUnGetSubsidy(trans.cardno);
	if(ret)
	{
		writelog(LOG_ERR,"UpdAllUnGetSubsidy ret=[%d]",ret);
		return ret;
	}
	strcpy(trans.cardaccno,tCardAccount.accno);
	//押金处理
	if(freefeeflag)
	{
		pAccTrans->SetFreeFlag();
	}
	else
	{
		//扣押金
		if(amtcmp(tCardAccount.foregift,0)>0)
		{
			trans.transamt=tCardAccount.foregift;
			trans.inputamt=tCardAccount.foregift;
			trans.unusedamt = trans.inputamt;
			trans.fundtype=0;
			pAccTrans->trans.transtype=TRANSTYPE_FOREGIFT2COSTFEE;
			ret=pAccTrans->DoTransByTransType();
			if(ret)
				return ret;
			if(amtcmp(pAccTrans->trans.unusedamt,0)>0)
				return E_INPUT_AMT;
			if(amtcmp(pAccTrans->trans.unusedamt,0)<0)
				return E_AMT_LACK;
		}			
	}
	if(amtcmp(tCardAccount.cardbal,0)<=0)
	{
		trans.cardbefbal=D4U5(tCardAccount.availbal+tCardAccount.subsidybal);
	}
	else
	{
		if(amtcmp(tCardAccount.availbal,tCardAccount.cardbal)<=0)
			trans.cardbefbal=D4U5(tCardAccount.availbal+tCardAccount.subsidybal);
		else
			trans.cardbefbal=D4U5(tCardAccount.cardbal+tCardAccount.subsidybal);
	}
	if(amtcmp(tCardAccount.subsidybal,0)!=0)
	{
		//领取补助
		memset(&tCardAccount,0,sizeof(tCardAccount));
		ret=DB_t_account_read_lock_by_c0_and_accno(trans.cardaccno,&tCardAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_ACCNO,trans.cardaccno);
			else 
				return E_DB_ACCOUNT_R;
		}
		tCardAccount.availbal=D4U5(tCardAccount.availbal+tCardAccount.subsidybal);
		tCardAccount.subsidybal=0;
		ret=DB_t_account_update_lock_by_c0(&tCardAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_U;
			else 
				return E_DB_ACCOUNT_R;
		}
	}

	if(amtcmp(tCardAccount.balance,trans.cardbefbal)>0)
	{
		//走长款处理
//		if('C'==backcardtype)
//		{
			trans.transamt=D4U5(tCardAccount.balance-tCardAccount.frozebal-trans.cardbefbal);
			trans.inputamt=trans.transamt;
			trans.unusedamt = trans.inputamt;		
			trans.fundtype=0;
			pAccTrans->trans.transtype=TRANSTYPE_MORE_CARDBALINCOME;
			ret=pAccTrans->DoTransByTransType();
			if(ret)
				return ret;
			if(amtcmp(pAccTrans->trans.unusedamt,0)>0)
				return E_INPUT_AMT;
			if(amtcmp(pAccTrans->trans.unusedamt,0)<0)
				return E_AMT_LACK;
//		}
	}
	trans.cardflag=1;
	trans.usecardflag=1;
	trans.feetype=tCard.feetype;
	trans.fundtype=rPack->lvol9;
	trans.inputamt=rPack->damt0;
	trans.unusedamt = trans.inputamt;	
	if(trans.fundtype>4)
	{
		//如果从账户中扣卡成本费，则没有充值业务
		trans.fundtype=0;
		ret=pAccTrans->doFeeTrans();
		if(ret)
			return ret; 
	}
	else
	{
		des2src(trans.voucherno,rPack->scust_auth2);
		ret=pAccTrans->doTrans();
		if(ret)
			return ret; 
	}
	ret=pAccTrans->doTransEnd();
	if(ret)
		return ret;
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_lock_by_c0_and_accno(trans.cardaccno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDACCNO,trans.cardaccno);
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		DB_t_account_free_lock_by_c0();
		return ERRINFO(E_CARDACC_LOGOUT,tCardAccount.accno);
	}
	if(amtcmp(tCardAccount.availbal,0)<0)
	{	
		DB_t_account_free_lock_by_c0();
		return ERRIF_CARDACC_OVERDRAW;
	}
	//取可用余额作为出卡值
	trans.cardaftbal=tCardAccount.availbal;
	tCardAccount.cardbal=trans.cardaftbal;
	tCardAccount.lastdpscnt=0;
	tCardAccount.lastpaycnt=0;
	tCardAccount.dpscnt=0;
	tCardAccount.paycnt=0;
	if(amtcmp(trans.cardaftbal,0)>0)
	{
		tCardAccount.dpscnt=1;
		trans.dpscnt=1;
	}
	double CardMaxBal=0;
	ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
	if(ret)
	{
		DB_t_account_free_lock_by_c0();
		return ret;
	}
	if(amtcmp(trans.cardaftbal,CardMaxBal)>=0)
	{
		DB_t_account_free_lock_by_c0();
		return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);
	}
	tCardAccount.cardno=tNewCard.cardno;
	tCardAccount.lastsubsidyno=maxsubsidyno;
	tCardAccount.lastcardbal=trans.cardaftbal;
	des2src(tCardAccount.lasttransdate,trans.transdate);
	ret=DB_t_account_update_lock_by_c0(&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_U;
		else 
			return E_DB_ACCOUNT_R;
	}
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	strcpy(transdtl.transdate,trans.transdate);
	strcpy(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
	transdtl.cardno=tNewCard.cardno;
	transdtl.transflag= TF_DPS;
	transdtl.cardcnt=trans.dpscnt;
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.paytype=trans.fundtype;
	des2src(transdtl.voucherno,trans.voucherno);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	transdtl.errcode=0;
	transdtl.custid=tCustomer.custid;
	des2src(transdtl.custname,tCustomer.custname);
	des2src(transdtl.stuempno,tCustomer.stuempno);
	des2src(transdtl.showcardno,tNewCard.showcardno);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
		return E_DB_TRANSDTL_E;
	  else
		return E_DB_TRANSDTL_I;
	}		
	char cardpwd[33]="";
	char key[17]="";
	
	 //get_init_passwd_by_man_id(tCustomer.idno,cardpwd);
	strcpy(key,STATIC_SEED_KEY);
	EncodePwd(key,cardpwd,tNewCard.cardpwd, 1);

    SetCol(handle,F_LVOL1,F_LSAFE_LEVEL,F_LSAFE_LEVEL2,F_LVOL5,
           F_SALL_NAME,F_SPAGER,F_SCERT_NO,F_SHOLDER_AC_NO,
           F_SEMAIL2,F_SMARKET_CODE,F_SMARKET_CODE2,F_SDATE0,F_SNOTE,
           F_SSTAT_TYPE,F_SSTAT_TYPE2,F_SNATION_CODE,F_SBRANCH_CODE0,
           F_LVOL0,F_STX_PWD,F_LVOL8,F_LVOL11,F_LVOL12,
           F_SORDER0,F_SORDER1,F_SORDER2,F_SDATE3,F_STIME3,F_SEMP,
           F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,F_SNAME2,0);
    outPack->lvol1=tCustomer.custid;
    outPack->lsafe_level2=tCustomer.custtype;
    outPack->lvol5=tNewCard.feetype;
    des2src(outPack->sall_name,tCustomer.custname);
    des2src(outPack->spager,tCustomer.stuempno);
    des2src(outPack->scert_no,tCustomer.deptcode);
    des2src(outPack->semail2,tCustomer.idno);
    des2src(outPack->smarket_code,tCustomer.sex);
	des2src(outPack->smarket_code2,tCustomer.idtype);
    des2src(outPack->sdate0,tNewCard.expiredate);
    outPack->lvol0=tNewCard.cardno;
    des2src(outPack->stx_pwd,cardpwd);	
    outPack->lvol4=maxsubsidyno;
    outPack->lvol8=D4U5(pAccTrans->trans.cardaftbal*100,0);
    outPack->lvol11=D4U5(tCardAccount.singlemaxamt*100,0);
    outPack->lvol12=D4U5(tCardAccount.daycostmaxamt*100,0);
    des2src(outPack->sorder0,tNewCard.showcardno);	
	strcpy(outPack->snote,CARD_STRUCT_VERSION);				//制卡版本号
	strcpy(outPack->sorder1,CARD_REGISTER_PUBLISH_CODE);	//发卡注册标识号
	strcpy(outPack->sorder2,CARD_REGISTER_SERVICE_CODE);	//服务注册标识号
	sprintf(outPack->sholder_ac_no,"%d",tCustomer.custid);	//客户号
	des2src(outPack->sstat_type,tCustomer.idtype);			//证件类型
	des2src(outPack->snation_code,tCustomer.country);		//国籍
	des2src(outPack->sstat_type2,tCustomer.nation);	//民族
	des2src(outPack->sbranch_code0,tCustomer.areacode);		//院校代码	
    des2src(outPack->sname2,tCard.cardverno);	
    des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->stime3,pAccTrans->trans.acctime);
	outPack->lsafe_level=tCard.cardtype;
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
	des2src(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
