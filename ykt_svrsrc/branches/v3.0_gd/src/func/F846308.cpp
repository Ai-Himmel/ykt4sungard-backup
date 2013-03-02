/* --------------------------------------------
 * 创建日期: 2008-06-23
 * 程序作者:闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通冻结解冻
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

int DoFrozeCard(int cardno)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;

	T_t_card tCard;
	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_lock_by_cur_and_cardno(cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,cardno);
		else 
			return E_DB_CARD_R;
	}
	des2src(trans.showcardno,tCard.showcardno);
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOGOUT,cardno);
	}	
	if('1'==tCard.frozeflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_FREEZE,cardno);
	}
	tCard.frozeflag[0]='1';
	des2src(tCard.frozedate,trans.accdate);
	ret=getCardVerNo(tCard.cardverno);
	if(ret)
	{
		DB_t_card_free_lock_by_cur();
		return ret;
	}
	des2src(tCard.lastsaved,trans.sysdatetime);
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDNO;
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
				return E_NOTEXIST_CUSTOMER;
			else
				return E_DB_CUSTOMER_R;
		}
		trans.custid=tCard.custid;
		des2src(trans.custname,customer.custname);
		des2src(trans.stuempno,customer.stuempno);
	}
	//修改以前的解冻记录为删除状态
	UpdCardVerStatus(cardno,CARDVERTYPE_CARDUNFROZE);
	//更新系统黑名单最大版本号
	ret=SetSysParaVal(SYSPARA_MAXBLACKCARDVERNO,tCard.cardverno);
	if(ret)
	{
		return ret;
	}
	T_t_cardver cardver;
	memset(&cardver,0,sizeof(cardver));
	cardver.cardno=tCard.cardno;
	des2src(cardver.accdate,pAccTrans->trans.accdate);
	cardver.termid=trans.termid;
	cardver.termseqno=trans.termseqno;
	cardver.cardno=tCard.cardno;
	des2src(cardver.cardphyid,tCard.cardphyid);
	des2src(cardver.stuempno,customer.stuempno);	
	cardver.cardvertype=CARDVERTYPE_CARDFROZE;
	cardver.adddelflag[0]=ADDDELFLAG_ADD;
	cardver.status[0]=STATUS_NORMAL;	
	des2src(cardver.cardverno,tCard.cardverno);
	ret=DB_t_cardver_add(&cardver);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDVER_E;
		else
			return E_DB_CARDVER_I;
	}
	char broadcastblkflag[20]={0};
	ret=GetSysParaVal(SYSPARA_BROADCASTBLKLIST,broadcastblkflag);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return 0;
		else
			return E_DB_SYSKEY_R;
	}
	des2src(trans.summary,cardver.cardverno);
	if(broadcastblkflag[0]!='1')
		return 0;
	T_t_msglist tMsgList;
	memset(&tMsgList,0,sizeof(tMsgList));
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_CARDID,tCard.cardno);
	AddXmlItemStr(tMsgList.reqdata, XML_KEY_VERNUM,tCard.cardverno);
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_ADDDELSIGN,0);	//增删标志

	tMsgList.funcno = 930005;
	tMsgList.pfuncno = 846307;
	tMsgList.msglevel = MESLIST_PRIORITY_REALTIME;
	tMsgList.msgtype = MESLIST_TYPE_ORDER;
	ret=AddMsgLst(&tMsgList);
	if(ret)
	{
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		return ret;
	}
	return 0;
}
int DoUnFrozeCard(int cardno)
{
	int ret=0;
	T_t_card tCard;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;

	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_lock_by_cur_and_cardno(cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,cardno);
		else 
			return E_DB_CARD_R;
	}
	des2src(trans.showcardno,tCard.showcardno);
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOGOUT,cardno);
	}	
	if('1'!=tCard.frozeflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARDNO_NOFREEZE,cardno);
	}
	tCard.frozeflag[0]='0';
	strcpy(tCard.frozedate,"");
	if(tCard.lossflag[0]!='1')
	{
		ret=getCardVerNo(tCard.cardverno);
		if(ret)
		{
			DB_t_card_free_lock_by_cur();
			return ret;
		}
	}
	des2src(tCard.lastsaved,trans.sysdatetime);
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
		ret=DB_t_customer_read_by_custid(tCard.custid,&customer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_NOTEXIST_CUSTOMER;
			else
				return E_DB_CUSTOMER_R;
		}
		trans.custid=tCard.custid;
		des2src(trans.custname,customer.custname);
		des2src(trans.stuempno,customer.stuempno);
	}
	UpdCardVerStatus(cardno,CARDVERTYPE_CARDFROZE);
	//如果卡已被挂失，则不发送解冻名单
	if('1'==tCard.lossflag[0])
	{		
		return 0;
	}
	//更新系统黑名单最大版本号
	ret=SetSysParaVal(SYSPARA_MAXBLACKCARDVERNO,tCard.cardverno);
	if(ret)
	{
		return ret;
	}
	T_t_cardver cardver;
	memset(&cardver,0,sizeof(cardver));
	cardver.cardno=tCard.cardno;
	des2src(cardver.accdate,pAccTrans->trans.accdate);
	cardver.termid=trans.termid;
	cardver.termseqno=trans.termseqno;
	cardver.cardno=tCard.cardno;
	des2src(cardver.cardphyid,tCard.cardphyid);
	des2src(cardver.stuempno,customer.stuempno);	
	cardver.cardvertype=CARDVERTYPE_CARDUNFROZE;
	cardver.adddelflag[0]=ADDDELFLAG_DEL;
	cardver.status[0]=STATUS_NORMAL;
	des2src(cardver.cardverno,tCard.cardverno);
	ret=DB_t_cardver_add(&cardver);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDVER_E;
		else
			return E_DB_CARDVER_I;
	}
 	des2src(trans.summary,cardver.cardverno);
	char broadcastblkflag[20]={0};
	ret=GetSysParaVal(SYSPARA_BROADCASTBLKLIST,broadcastblkflag);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return 0;
		else
			return E_DB_SYSKEY_R;
	}
	if(broadcastblkflag[0]!='1')
		return 0;
	T_t_msglist tMsgList;
	memset(&tMsgList,0,sizeof(tMsgList));
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_CARDID,tCard.cardno);
	AddXmlItemStr(tMsgList.reqdata, XML_KEY_VERNUM,tCard.cardverno);
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_ADDDELSIGN,1);	//增删标志

	tMsgList.funcno = 930005;
	tMsgList.pfuncno = 846307;
	tMsgList.msglevel = MESLIST_PRIORITY_REALTIME;
	tMsgList.msgtype = MESLIST_TYPE_ORDER;
	ret=AddMsgLst(&tMsgList);
	if(ret)
	{
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		return ret;
	}
	return 0;
}

int F846308(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	des2src(pAccTrans->trans.opercode,rPack->semp);
	trans.cardno = rPack->lvol0;
    trans.termid=rPack->lwithdraw_flag;
	char frozeflag=rPack->sstatus1[0];
	
	if('1'==frozeflag)
	{		
		trans.transcode=TC_CARDFROZE;
		ret=pAccTrans->InitTrans();
		if(ret)
			return ret; 				
		ret=DoFrozeCard(trans.cardno);
	}
	else
	{
		trans.transcode=TC_CARDUNFROZE;
		ret=pAccTrans->InitTrans();
		if(ret)
			return ret; 				
		ret=DoUnFrozeCard(trans.cardno);
	}
	if(ret)
		return ret;
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	transdtl.cardno=trans.cardno;
	transdtl.custid=trans.custid;
	des2src(transdtl.custname,trans.custname);
    des2src(transdtl.stuempno,trans.stuempno);
	strcpy(transdtl.transdate,trans.transdate);
	strcpy(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
    transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	transdtl.errcode=0;
	transdtl.showcardno=atol(trans.showcardno);
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
	memset(&aPack,0,sizeof(aPack));
	
	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,0);
	SetCol(handle,F_SSERIAL0,F_VSMESS,0);
	strncpy(outPack->sserial0,trans.summary,12);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
