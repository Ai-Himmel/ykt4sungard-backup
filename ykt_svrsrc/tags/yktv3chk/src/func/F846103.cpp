/* --------------------------------------------
 * 创建日期: 2008-6-20
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 卡片上交
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

int F846103(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->clear();	
	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_CARDPUT;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;

	int cardtype=0;
	char startno[11]="";
	char endno[11]="";
	char opercode[9]="";

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,F_VSMESS,0);
	
	des2src(startno,rPack->scust_no);
	des2src(endno,rPack->scust_no2);
	des2src(opercode,rPack->semp);
	cardtype=rPack->lvol0;
	double i_startno=atof(startno);
	double i_endno=atof(endno);
	double db_curno=0;
	double db_endno=0;
	
	T_t_cardbook tCardbook;
	T_t_cardbook oldtCardbook;	

	memset(&tCardbook,0,sizeof(tCardbook));
	memset(&oldtCardbook,0,sizeof(oldtCardbook));
	ret=DB_t_cardbook_open_select_by_c1_and_status("1");
	if(ret)
	{
		return E_DB_CURSOR_DECLARE;
	}

	while(1)
	{
		memset(&tCardbook,0,sizeof(tCardbook));
		ret=DB_t_cardbook_fetch_select_by_c1(&tCardbook);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_CARDBOOK_N;
			else
				return E_DB_CARDBOOK_R;
		}
		db_curno=atof(tCardbook.curno);
		db_endno=atof(tCardbook.endno);
		
		if(amtcmp(i_endno,db_curno)<0)
			continue;
		if(amtcmp(i_startno,db_endno)>0)
			continue;
		break;
	}
	DB_t_cardbook_close_select_by_c1();
	if(amtcmp(i_startno,i_endno)>0)
		return E_STARTNO_GT_ENDNO;
	if(amtcmp(i_startno,db_endno)>0)
		return E_STARTNO_RANGE;
	if(amtcmp(i_startno,db_curno)<0)
		return E_STARTNO_RANGE;
	if(amtcmp(i_endno,db_curno)<0)
		return E_ENDNO_RANGE;
	if(amtcmp(i_endno,db_endno)>0)
		return E_ENDNO_RANGE;
	double cardcnt=i_endno-i_startno+1;
	
	memcpy(&oldtCardbook,&tCardbook,sizeof(oldtCardbook));
	if(strcmp(startno,tCardbook.curno)==0)
	{
		if(strcmp(endno,tCardbook.endno)==0)
		{
			if(strcmp(startno,tCardbook.startno)==0)
			{
				ret=DB_t_cardbook_del_by_recordno(tCardbook.recordno);
				if(ret)
					return E_DB_CARDBOOK_U; 	
			}
			else
			{
				getNextShowCardNo(startno,-1,tCardbook.endno);
				tCardbook.unusedcnt==0;				
				tCardbook.status[0]=STATUS_LOGOUT;
				getfmtsysdatetime(tCardbook.lastsaved); 					
				ret=DB_t_cardbook_update_by_recordno(tCardbook.recordno,&tCardbook);
				if(ret)
					return E_DB_CARDBOOK_U; 	
			}
		}
		else
		{
			if(strcmp(startno,tCardbook.startno)!=0||tCardbook.usedcnt>0)
			{
				getNextShowCardNo(startno,-1,tCardbook.endno);
				tCardbook.unusedcnt==0; 			
				tCardbook.status[0]=STATUS_LOGOUT;
				getfmtsysdatetime(tCardbook.lastsaved); 					
				ret=DB_t_cardbook_update_by_recordno(tCardbook.recordno,&tCardbook);
				if(ret)
					return E_DB_CARDBOOK_U;
				////////////////////////////////////////////////////////////////////////
				ret=getCardBookRecordNo(oldtCardbook.recordno);
				if(ret)
					return ret;
				getNextShowCardNo(endno,1,oldtCardbook.startno);
				strcpy(oldtCardbook.curno,oldtCardbook.startno);
				oldtCardbook.unusedcnt=atof(oldtCardbook.endno)-atof(oldtCardbook.curno)+1;
				oldtCardbook.status[0]=STATUS_NORMAL;
				getfmtsysdatetime(oldtCardbook.lastsaved);
				ret=DB_t_cardbook_add(&oldtCardbook);
				if(ret) 
					return E_DB_CARDBOOK_I;
			}
			else
			{
				getNextShowCardNo(endno,1,tCardbook.startno);
				strcpy(tCardbook.curno,tCardbook.startno);
				tCardbook.unusedcnt=atof(tCardbook.endno)-atof(tCardbook.curno)+1;
				tCardbook.status[0]=STATUS_NORMAL;
				getfmtsysdatetime(tCardbook.lastsaved); 					
				ret=DB_t_cardbook_update_by_recordno(tCardbook.recordno,&tCardbook);
				if(ret)
					return E_DB_CARDBOOK_U; 	
			}
		}
	}	
	else
	{
		if(strcmp(endno,tCardbook.endno)==0)
		{
			getNextShowCardNo(startno,-1,tCardbook.endno);
			tCardbook.unusedcnt=atof(tCardbook.endno)-atof(tCardbook.curno)+1;
			getfmtsysdatetime(tCardbook.lastsaved);
			ret=DB_t_cardbook_update_by_recordno(tCardbook.recordno,&tCardbook);
			if(ret)
				return E_DB_CARDBOOK_U; 	
		}
		else
		{
			getNextShowCardNo(startno,-1,tCardbook.endno);
			tCardbook.unusedcnt=atof(tCardbook.endno)-atof(tCardbook.curno)+1;
			getfmtsysdatetime(tCardbook.lastsaved);
			ret=DB_t_cardbook_update_by_recordno(tCardbook.recordno,&tCardbook);
			if(ret)
				return E_DB_CARDBOOK_U; 
			////////////////////////////////////////////
			ret=getCardBookRecordNo(oldtCardbook.recordno);
			if(ret)
				return ret;
			getNextShowCardNo(endno,1,oldtCardbook.startno);
			strcpy(oldtCardbook.curno,oldtCardbook.startno);
			oldtCardbook.unusedcnt=atof(oldtCardbook.endno)-atof(oldtCardbook.curno)+1;
			oldtCardbook.status[0]=STATUS_NORMAL;
			getfmtsysdatetime(oldtCardbook.lastsaved);
			ret=DB_t_cardbook_add(&oldtCardbook);
			if(ret)	
				return E_DB_CARDBOOK_I;
		}
	}
	sprintf(outPack->vsmess,"操作员%s上交卡片数量%.lf,上交起始号码%s，结束号码%s",tCardbook.opercode,cardcnt,startno,endno);
    PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
