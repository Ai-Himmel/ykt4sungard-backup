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


int F846308(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
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

	int	cardno = rPack->lvol0;
	char lossflag=rPack->sstatus1[0];

	T_t_card tCard;

	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_lock_by_cur_and_cardno(cardno,&tCard);
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
		DB_t_card_free_lock_by_cur();
		return E_CARD_LOGOUT;
	}
	if(lossflag=='1')
	{
		if(tCard.cardattr[CARDSTAT_TYPE_FREEZE]=='1')
		{
				return E_CARDNO_FREEZE;
		}
		tCard.cardattr[CARDSTAT_TYPE_FREEZE]='1';
		getsysdate(tCard.lossdate);		
		pAccTrans->trans.transcode=TC_CARDFROZE;
	}
	else
	{
		if(tCard.cardattr[CARDSTAT_TYPE_FREEZE]=='0')
		{
				return E_CARDNO_NOFREEZE;
		}
		tCard.cardattr[CARDSTAT_TYPE_FREEZE]='0';
		strcpy(tCard.lossdate,"");
		pAccTrans->trans.transcode=TC_CARDUNFROZE;
	}
		
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else 
			return E_DB_CARD_U;
	}
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;	
	T_t_cardtransdtl cardtransdtl;
	memset(&cardtransdtl,0,sizeof(cardtransdtl));

	cardtransdtl.cardno=tCard.cardno;
	cardtransdtl.custid=tCard.custid;
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
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	memset(&aPack,0,sizeof(aPack));
	
	ResetNormalCPack(&aPack,0,1);
		
	SetCol(handle,0);
	SetCol(handle,F_SSERIAL0,F_VSMESS);
	strncpy(outPack->sserial0,getsysdatetime(NULL)+2,12);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
