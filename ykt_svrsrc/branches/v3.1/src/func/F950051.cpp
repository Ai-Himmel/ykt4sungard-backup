/* --------------------------------------------
 * 创建日期: 2010-06-10
 * 程序作者: 闻剑
 * 版本信息: 3.0.0.0
 * 程序功能: 汇多CPU卡联机消费
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
#include "interfacefunc.h"
#include "interface.h"
#include "transfunc.h"
#include <string>
#include <sstream>
using namespace std;

void LockCard(int cardno,int blacklistflag,int cardstatus,TRUSERID *handle,int *pRetCode,char *szMsg)
{
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	
	ResetNormalCPack(&aPack,0,1);	
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL2,F_LSAFE_LEVEL,F_LSAFE_LEVEL2,F_LBANK_ACC_TYPE,F_LSERIAL0,F_VSMESS,0);		
	outPack->lvol0 = cardno;
	outPack->lserial0= cardstatus,	//卡状态码
	outPack->lvol2 = 1;			//是否要锁卡标志
	outPack->lbank_acc_type =blacklistflag;	//更新黑名单标志
	strncpy(outPack->vsmess,szMsg,255);
	PutRow(handle,outPack,pRetCode,szMsg);
}
//POS联机消费
static int	DoPosOnlineTrans(T_t_posdtl& posdtl,TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LSAFE_LEVEL,F_LSAFE_LEVEL2,F_LBANK_ACC_TYPE,F_LSERIAL0,0);	

	//判断卡版本号
	int blackcardlistflag=0;
	char maxblackcardverno[13]="";
	ret=GetSysParaVal(SYSPARA_MAXBLACKCARDVERNO,maxblackcardverno);
	if(ret)
		return ERRIF_DATABASE_QRY;
	if(strncmp(rPack->sname,maxblackcardverno,12)!=0)
		blackcardlistflag=1;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	trans.termid=posdtl.termid;
	if(!trans.termid)
	{
		return ERRIF_POS_TERMID;
	}
	trans.cardflag=1;
	trans.usecardflag=1;
	trans.cardno=posdtl.cardno;
	trans.purseno=posdtl.purseno;
	trans.paycnt=posdtl.cardcnt;
	trans.cardbefbal=posdtl.cardbefbal;
	trans.cardaftbal=posdtl.cardbefbal;
	trans.shopid=posdtl.shopid;
	trans.cardsubsidyno=posdtl.subsidyno;
	trans.inputamt=posdtl.amount;	
	memcpy(trans.transdate,posdtl.transdate,8);
	memcpy(trans.transtime,posdtl.transtime,6);
	//检查卡
	T_t_card  tCard;
	memset(&tCard,0,sizeof(tCard));
	ret=CardStatusInfoReadbyCardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		return ret;
	}
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		strcpy(szMsg,"卡已注销");
		LockCard(trans.cardno,blackcardlistflag,CARDSTATUS_CLOSE,handle,pRetCode,szMsg);
		return 0;
	}	
	if('1'==tCard.lockflag[0])
	{
		strcpy(szMsg,"卡已锁定");
		LockCard(trans.cardno,blackcardlistflag,CARDSTATUS_LOCK,handle,pRetCode,szMsg);
		return 0;
	}	
	if('1'==tCard.frozeflag[0])
	{
		strcpy(szMsg,"卡已冻结");
		LockCard(trans.cardno,blackcardlistflag,CARDSTATUS_FROZE,handle,pRetCode,szMsg);
		return 0;
	}
	if('1'==tCard.lossflag[0])
	{
		strcpy(szMsg,"卡已挂失");
		LockCard(trans.cardno,blackcardlistflag,CARDSTATUS_LOST,handle,pRetCode,szMsg);
		return 0;
	}	
	if('1'==tCard.badflag[0])
	{
		strcpy(szMsg,"卡已登记为坏卡");
		LockCard(trans.cardno,blackcardlistflag,CARDSTATUS_EXCEPT,handle,pRetCode,szMsg);	
		return 0;
	}		
	if(strncmp(tCard.expiredate,trans.transdate,8)<0)
	{
		strcpy(szMsg,"卡已过期");
		LockCard(trans.cardno,blackcardlistflag,CARDSTATUS_EXPIRE,handle,pRetCode,szMsg);	
		return 0;
	}
	trans.feetype=tCard.feetype;

	T_t_account account;

	memset(&account,0,sizeof(account));
	ret=CardAccInfoReadbyAccno(tCard.accno,&account);
	if(ret)
	{
		writelog(LOG_ERR,"cardaccno[%s]",tCard.accno);
		if(DB_NOTFOUND==ret)
			return ERRIF_CARDACC_EXCEPT;
		else
			return ERRIF_DATABASE_QRY;
	}
	if(amtcmp(trans.cardbefbal-account.availbal,MAXAMT_CARDGTACC)>=0)
	{
		strcpy(szMsg,"卡余额异常");
		LockCard(trans.cardno,blackcardlistflag,CARDSTATUS_EXCEPT,handle,pRetCode,szMsg);	
		return 0;
	}
	//如果卡余额比账户余额大于或等于100元则不允许消费
	des2src(trans.cardaccno,tCard.accno);
	trans.custid=tCard.custid;
	ret=UpdateCardBitmap(trans.cardno,trans.aftpaycnt,CARDBITMAPTYPE_POS_ONLINE);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]cardcnt[%d]",trans.cardno,trans.paycnt);
		if(E_EXIST_CARDCNT==ret)
			return ERRIF_CARDCNT_REPEAT;
		else
			return ERRIF_CARDCNT_EXCEPT;
	}
	//检查卡余额
	if(amtcmp(posdtl.amount,trans.cardaftbal)>0)
	{
		writelog(LOG_ERR,"交易金额[%.2lf]交易前卡余额[%.2lf]",posdtl.amount,trans.cardaftbal);
		return ERRIF_CARDBAL_SHORTAGE;
	}	
	trans.transcode=TC_POSDRAW;
	//获取终端流水号
	ret=pAccTrans->GetTermSeqno();
	if(ret)
	{
		writelog(LOG_ERR,"GetTermSeqno ret=",ret);
		if(E_ACCDATE_NOSWITCH==ret)
			return ERRIF_SYS_DAYENDACC;
		else
			return ERRIF_DATABASE_UPD;
	}
	int shoptype=0;
	char shopstatus[2]={0};
	ret=ShopAccReadbyShopid(trans.shopid,trans.shopaccno,&shoptype,shopstatus);
	if(ret)
	{
		writelog(LOG_ERR,"shopid[%d]",trans.shopid);
		return ret;
	}
	if(shopstatus[0]!=STATUS_NORMAL)
		return ERRIF_SHOP_CLOSE;
	if(shoptype!=SHOPTYPE_COSUMESHOP)
		return ERRIF_SHOP_TYPE;
	//正常记录
	trans.transtype=TRANSTYPE_POSPAYMENT;
	trans.transamt=D4U5(posdtl.amount-posdtl.managefee);
	trans.inputamt=trans.transamt;
	trans.unusedamt=trans.inputamt;
	ret=pAccTrans->DoTransByTransType();
	if(ret)
	{
		writelog(LOG_ERR,"DoTransByTransType ret=%d",ret);
		if(E_CARDACC_LOGOUT==ret)
			return ERRIF_CARD_CLOSE;
		else
			return ERRIF_SYSTEM;
	}
	if(amtcmp(pAccTrans->trans.unusedamt,0)>0)
		return ERRIF_CARDBAL_SHORTAGE;
	if(amtcmp(pAccTrans->trans.unusedamt,0)<0)
		return ERRIF_CARDBAL_EXCEPT;
	//正常流水
	if(pAccTrans->sysPara.iShopBoardFeeFlag)
	{
		trans.transtype=TRANSTYPE_SHOPBOARDFEE;
		trans.transamt=posdtl.managefee;
		trans.inputamt=trans.transamt;
		trans.unusedamt=trans.inputamt;
		ret=pAccTrans->DoTransByTransType();
		if(ret)
		{
			writelog(LOG_ERR,"DoTransByTransType ret=%d",ret);
			if(E_CARDACC_LOGOUT==ret)
				return ERRIF_CARD_CLOSE;
			else
				return ERRIF_SYSTEM;
		}
		if(amtcmp(pAccTrans->trans.unusedamt,0)>0)
			return ERRIF_CARDBAL_SHORTAGE;
		if(amtcmp(pAccTrans->trans.unusedamt,0)<0)
			return ERRIF_CARDBAL_EXCEPT;
	}
	else
	{
		trans.transtype=TRANSTYPE_BOARDFEE;
		trans.transamt=posdtl.managefee;
		trans.inputamt=trans.transamt;
		trans.unusedamt=trans.inputamt;
		ret=pAccTrans->DoTransByTransType();
		if(ret)
		{
			writelog(LOG_ERR,"DoTransByTransType ret=%d",ret);
			if(E_CARDACC_LOGOUT==ret)
				return ERRIF_CARD_CLOSE;
			else
				return ERRIF_SYSTEM;
		}
		if(amtcmp(pAccTrans->trans.unusedamt,0)>0)
			return ERRIF_CARDBAL_SHORTAGE;
		if(amtcmp(pAccTrans->trans.unusedamt,0)<0)
			return ERRIF_CARDBAL_EXCEPT;
	}			
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
//	transdtl.paytype=trans.fundtype;
//	des2src(transdtl.voucherno,trans.voucherno);
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.offlineflag=posdtl.datatype;
	transdtl.transflag= TF_PAY;
	transdtl.cardcnt=trans.paycnt;
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.amount=trans.totaltransamt;
	transdtl.managefee=posdtl.managefee;;
	transdtl.custid=trans.custid;
	transdtl.sysid=posdtl.sysid;
//	des2src(transdtl.coldate,posdtl.coldate);
//	des2src(transdtl.coltime,posdtl.coltime);
	des2src(transdtl.devphyid,posdtl.devphyid);
	transdtl.devseqno=posdtl.devseqno;
	des2src(transdtl.opercode,trans.opercode);
	des2src(transdtl.showcardno,tCard.showcardno);
	GetCustBaseInfoByCustID(transdtl.custid,transdtl.custname,transdtl.stuempno,NULL);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return ERRIF_DATABASE_REPEAT;
		else
			return ERRIF_DATABASE_INS;
	}		
	outPack->lvol0=trans.cardno;
	outPack->lvol1=D4U5(trans.cardaftbal*100,0);
	if(outPack->lvol1<0)
	{
		return ERRIF_CARDBAL_SHORTAGE;
	}
	des2src(posdtl.accdate,pAccTrans->trans.accdate);
	des2src(posdtl.acctime,pAccTrans->trans.acctime);
	posdtl.termid=trans.termid;
	posdtl.termseqno=trans.termseqno;
	posdtl.cardaftbal=trans.cardaftbal;
	posdtl.status[0]=DTLSTATUS_SUCCESS;
	ret = DB_t_posdtl_add(&posdtl);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",ret,posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
		if(DB_REPEAT==ret)
			return ERRIF_DATABASE_REPEAT;
		else
			return ERRIF_DATABASE_INS;
	}
	outPack->lbank_acc_type=blackcardlistflag;
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
int F950051(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();

	/*
	char termno[13]={0};

	des2src(termno,rPack->sstation0);
	if(strlen(termno)<1)
	{
		writelog(LOG_ERR,"termno[%s]",termno);
		return ERRIF_POS_TERMID;
	}
	T_t_psamcard psamcard;

	memset(&psamcard,0,sizeof(psamcard));
	ret=DB_t_psamcard_read_lock_by_c1_and_termno(termno,&psamcard);
	if(ret)
	{
		writelog(LOG_ERR,"psam termno[%s] not exist",termno);
		return ERRIF_AUTHCARD_NOTEXIST;
	}
	*/
	int transflag=rPack->lvol0;
	int revflag=rPack->lsafe_level;
	int onlineflag =rPack->lvol2;
	
	T_t_posdtl posdtl;
	memset(&posdtl,0,sizeof(posdtl));
	Cpack2Posdtl(rPack,posdtl);
	
	writelog(LOG_ERR,"devphyid[%s]",posdtl.devphyid);	
	return 2;	//取消联机交易
	if(strlen(posdtl.transdate)!=8)
	{
		writelog(LOG_ERR,"recv offline posdtl err: devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
		return ERRIF_SYSTEM;
	}
	if(strlen(posdtl.transtime)!=6)
	{
		writelog(LOG_ERR,"recv offline posdtl err: devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
		return ERRIF_SYSTEM;
	}
	if(!strlen(posdtl.devphyid))
	{
		writelog(LOG_ERR,"recv offline posdtl err: devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
		return ERRIF_POS_TERMID;
	}
	char runstatus[2]={0};
	char status[2]={0};
	ret=DeviceStatusInfoReadbyDevphyid(posdtl.devphyid,&(posdtl.termid),status,runstatus);
	if(ret)
	{
		writelog(LOG_ERR,"devphyid[%s]ret[%d]",posdtl.devphyid,ret);
		return ret;
	}
	if(STATUS_NORMAL!=status[0])
	{
		return ERRIF_POS_CLOSE;
	}
	if(DEVRUNSTATUS_REGIST==runstatus[0])
	{
		return ERRIF_POS_NOTLOGIN;
	}
	if(!posdtl.cardno)
		return ERRIF_CARD_NOTEXIST;
	if(!onlineflag)
	{
		writelog(LOG_ERR,"onlineflag[%d]error",onlineflag);
		return ERRIF_SYSTEM;
	}
	if(revflag)
	{
		writelog(LOG_ERR,"revflag[%d]error",revflag);	
		return ERRIF_SYSTEM;
	}
	ret=DoPosOnlineTrans(posdtl,handle,rPack,pRetCode,szMsg);
	if(ret)
	{
		//记录失败流水
		if(ret>ERRIF_OTHER)
		{
			writelog(LOG_ERR,"错误码未转换,errcode[%d]",ret);
			ret=ERRIF_OTHER;
		}
		else
			return ret;
	}
	return 0;
}

