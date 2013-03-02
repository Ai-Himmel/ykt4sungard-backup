/* --------------------------------------------
 * 创建日期: 2008-06-23
 * 程序作者:闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通坏卡登记
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

int F846309(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret=0;
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
	pAccTrans->trans.transcode=TC_CARDBAD;

	char sysdate[9]="";
	char systime[7]="";

	int cardno=0;
	int cardtype=0;
	int feetype=0;
	int cardflag=0;
	int returnForgiftFlag=0;
	
	char cardphyid[9]="";
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	CARDTRANSINFO cti;
	
	memset(&cti,0,sizeof(cti));
	ResetNormalCPack(&aPack,0,1);
		
	SetCol(handle,0);

	trans.cardno = rPack->lvol0;
	char lossflag=rPack->sstatus1[0];
	char showcardno[11]="";
	char badflag=rPack->sstatus1[0];

	des2src(showcardno,rPack->sorder0);
	
	T_t_card tCard;

	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_by_showcardno_and_status(showcardno,"1",&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else 
			return E_DB_CARD_R;
	}
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		return E_CARD_LOGOUT;
	}
	if(tCard.cardattr[CARDSTAT_TYPE_BAD]=='1')
	{
			return E_BADCARD_RECORDED;
	}
	tCard.cardattr[CARDSTAT_TYPE_BAD]='1';
	getsysdate(tCard.lossdate);			
	ret=DB_t_card_update_by_cardno(tCard.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else 
			return E_DB_CARD_U;
	}
	
	//添加卡片回收明细记录
	T_t_carddtl tCarddtl;
	
	memset(&tCarddtl,0,sizeof(tCarddtl));
	/////////////////////////////////rPack2TableStuct////////////////////////
	des2src(tCarddtl.accdate,trans.accdate);
	tCarddtl.termid=trans.termid;
	tCarddtl.termseqno=trans.termseqno;
	tCarddtl.cardtype=tCard.cardtype;
	des2src(tCarddtl.showcardno,tCard.showcardno);
	des2src(tCarddtl.cardphyid,tCard.cardphyid);
	tCarddtl.cardusetype[0]=CARDUSETYPE_BADCARD;
	des2src(tCarddtl.opercode,trans.opercode);
	ret=DB_t_carddtl_add(&tCarddtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDDTL_E;
		else
			return E_DB_CARDDTL_I;
	}
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
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,0);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
