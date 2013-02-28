/* --------------------------------------------
 * 创建日期: 2007-07-21
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 卡片登录
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "transcode.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"

int F240000(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	TRANS& trans=ats.trans;
	trans.termid=atoi(rPack->sorder2);
	char seed_key[17] = "";
	char sInputPwd[33] = "";											//存放加密前的卡密钥
	char sCryptPwd[33] = "";									//存放加密后的卡密钥

	T_t_card		card;
	memset(&card,0,sizeof(card));


	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_LVOL2,F_SDATE0,0);

	trans.cardno=rPack->lvol0;
	if(trans.cardno<1)
		trans.cardno=atoi(rPack->sserial0);
	ret=DB_t_card_read_by_cardno(trans.cardno,&card);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}
	if(card.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
	/*
	if('1'==card.frozeflag[0])
	{
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==card.lossflag[0])
	{
		return ERRINFO(E_CARD_LOST,trans.cardno);
	}	
	if('1'==card.badflag[0])
	{
		return ERRINFO(E_CARD_BADRECORD,trans.cardno);
	}	
	if('1'==card.lockflag[0])
	{
		return ERRINFO(E_CARDNO_LOCKED,trans.cardno);
	}	
	*/
	des2src(sInputPwd,rPack->scust_limit);		//卡密码
	strcpy(seed_key,STATIC_SEED_KEY);			//种子密钥
	EncodePwd(seed_key,sInputPwd,sCryptPwd,0);	//加密
	if(strcmp(sCryptPwd,card.cardpwd)!=0)
	{
		writelog(LOG_ERR,"card err input[%s]db[%s]",sCryptPwd,card.cardpwd);
		return E_CARDPWD;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

