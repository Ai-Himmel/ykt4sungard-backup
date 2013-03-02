/* --------------------------------------------
 * 创建日期: 2008-06-20
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 卡片领入
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

int F846102(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char startno[11] = "";
	char endno[11] = "";
	char opercode[9] = "";
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	memset(&aPack,0,sizeof aPack);
	SetCol(handle,F_LVOL0,F_LVOL1,F_SEMP,F_SCUST_LIMIT2,F_VSMESS,0);
	
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->clear();
	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_CARDGET;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;

	int row=0;
	des2src(startno,rPack->scust_no);
	des2src(endno,rPack->scust_no2);
	des2src(opercode,rPack->semp);
	int cardtype=rPack->lvol0;
	double i_startno=atof(startno);
	double i_endno=atof(endno);
	if(i_endno<1)
		return E_ENDNO_RANGE;
	if(i_startno>i_endno)
		return E_STARTNO_GT_ENDNO;	
	ret=DB_t_cardbook_open_select_by_c3();
	if(ret)
	{
		return E_DB_CURSOR_DECLARE;
	}
	double db_curno=0;
	double db_endno=0;
	T_t_cardbook tCardBook;
	while(1)
	{
		memset(&tCardBook,0,sizeof(tCardBook));
		ret=DB_t_cardbook_fetch_select_by_c3(&tCardBook);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				break;
			else
				return E_DB_CARDBOOK_R;
		}
		db_curno=atof(tCardBook.curno);
		db_endno=atof(tCardBook.endno);
		if(amtcmp(i_startno,db_endno)>0)
			continue;
		if(amtcmp(i_endno,db_curno)<0)
			continue;
		if(amtcmp(i_startno,db_endno)>0)
			continue;
		DB_t_cardbook_close_select_by_c3();
		return E_DB_CARDBOOK_E;
	}
	T_t_cardbook tCardbook;

	memset(&tCardbook,0,sizeof(tCardbook));
	/////////////////////////////////rPack2TableStuct////////////////////////
	ret=getCardBookRecordNo(tCardbook.recordno);
	if(ret)
		return ret;
	tCardbook.cardtype=rPack->lvol0;
	des2src(tCardbook.startno,startno);
	des2src(tCardbook.endno,endno);
	des2src(tCardbook.curno,startno);
	tCardbook.unusedcnt=i_endno-i_startno+1;
	tCardbook.status[0]=STATUS_NORMAL;
	des2src(tCardbook.opercode,rPack->scust_limit2);
	getfmtsysdatetime(tCardbook.lastsaved);
	ret=DB_t_cardbook_add(&tCardbook);
	if(ret)
	{
	    if(DB_REPEAT==ret)
	        return E_DB_CARDBOOK_E;
	    else
	        return E_DB_CARDBOOK_I;
	}
	outPack->lvol0=tCardbook.cardtype;
	outPack->lvol1=tCardbook.unusedcnt;
	des2src(outPack->semp,tCardbook.opercode);
	sprintf(outPack->vsmess,"操作员%s领入数量%.lf,起始号码%s,结束号码%s",tCardbook.opercode,tCardbook.unusedcnt,tCardbook.startno,tCardbook.endno);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
