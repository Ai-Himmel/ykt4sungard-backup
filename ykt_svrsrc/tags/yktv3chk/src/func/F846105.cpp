/* --------------------------------------------
 * 创建日期: 2008-6-20
 * 程序作者:闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 卡片作废
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "busqc.h"
#include "acctrans.h"
#include "dbfunc_foo.h"

int F846105(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{	
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->clear();
	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_CARDDISABLE;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;
	
	char showcardno[11]="";
	char opercode[9]="";
	des2src(showcardno,rPack->scust_no);
	des2src(opercode,rPack->semp);
	int cardtype=rPack->lvol0;

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	
	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,F_VSMESS,0);

	T_t_cardbook tCardBook;
	T_t_cardbook oldtCardBook;

	ret=DB_t_cardbook_open_select_by_c1_and_status("1");
	if(ret)
	{
		return E_DB_CURSOR_DECLARE;
	}

	while(1)
	{
		memset(&tCardBook,0,sizeof(tCardBook));
		ret=DB_t_cardbook_fetch_select_by_c1(&tCardBook);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_CARDBOOK_N;
			else
				return E_DB_CARDBOOK_R;
		}
		if(strcmp(showcardno,tCardBook.curno)<0)
			continue;
		if(strcmp(showcardno,tCardBook.endno)>0)
			continue;
		break;
	}
	memcpy(&oldtCardBook,&tCardBook,sizeof(oldtCardBook));
	if(strcmp(showcardno,tCardBook.curno)==0)
	{
		if(strcmp(showcardno,tCardBook.endno)==0)
		{
			tCardBook.status[0]=STATUS_LOGOUT;
		}
		else
		{
			getNextShowCardNo(showcardno,1,tCardBook.curno);
			tCardBook.unusedcnt==atof(tCardBook.endno)-atof(tCardBook.curno)+1;
		}
		getfmtsysdatetime(tCardBook.lastsaved);					
		ret=DB_t_cardbook_update_by_recordno(tCardBook.recordno,&tCardBook);
		if(ret)
			return E_DB_CARDBOOK_U; 	
	}
	else
	{
		if(strcmp(showcardno,tCardBook.endno)==0)
		{
			getNextShowCardNo(showcardno,-1,tCardBook.endno);
			tCardBook.unusedcnt=atof(tCardBook.endno)-atof(tCardBook.curno)+1;
			getfmtsysdatetime(tCardBook.lastsaved);					
			ret=DB_t_cardbook_update_by_recordno(tCardBook.recordno,&tCardBook);
			if(ret)
				return E_DB_CARDBOOK_U; 				
		}
		else
		{
			getNextShowCardNo(showcardno,-1,tCardBook.endno);
			tCardBook.unusedcnt=atof(tCardBook.endno)-atof(tCardBook.curno)+1;
			getfmtsysdatetime(tCardBook.lastsaved);
			ret=DB_t_cardbook_update_by_recordno(tCardBook.recordno,&tCardBook);
			if(ret)
				return E_DB_CARDBOOK_U; 
			////////////////////////////////////////////
			getNextShowCardNo(showcardno,1,oldtCardBook.startno);
			ret=getCardBookRecordNo(oldtCardBook.recordno);
			if(ret)
				return ret;
			strcpy(oldtCardBook.curno,oldtCardBook.startno);
			oldtCardBook.unusedcnt=atof(oldtCardBook.endno)-atof(oldtCardBook.curno)+1;
			oldtCardBook.status[0]=STATUS_NORMAL;
			getfmtsysdatetime(oldtCardBook.lastsaved);
			ret=DB_t_cardbook_add(&oldtCardBook);
			if(ret)
				return E_DB_CARDBOOK_I;
		}
		////////////////////////////////////////////
		ret=getCardBookRecordNo(oldtCardBook.recordno);
		if(ret)
			return ret;
		strcpy(oldtCardBook.curno,showcardno);
		strcpy(oldtCardBook.startno,showcardno);
		strcpy(oldtCardBook.endno,showcardno);
		oldtCardBook.usedcnt=1;
		oldtCardBook.status[0]=STATUS_LOGOUT;
		getfmtsysdatetime(oldtCardBook.lastsaved);
		ret=DB_t_cardbook_add(&oldtCardBook);
		if(ret)
			return E_DB_CARDBOOK_I;
	}
	sprintf(outPack->vsmess,"操作员%s号码%s作废成功",opercode,showcardno);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
