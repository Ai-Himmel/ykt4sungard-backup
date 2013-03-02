/* --------------------------------------------
 * 程序名称: F847127.c
 * 创建日期: 2005-11-18
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 手工借-手工贷
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
int F847127(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=TC_MANUALDRCR;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=pAccTrans->trans;

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	des2src(trans.draccno,rPack->sbank_acc);
	des2src(trans.craccno,rPack->sbank_acc2);
	trans.inputamt=rPack->damt0;
	if(amtcmp(trans.inputamt,0)==0)
	{
		return E_INPUT_AMT_NULL;
	}	
	if(!strlen(trans.draccno))
		return E_NO_DRACCNO;
	if(!strlen(trans.craccno))
		return E_NO_CRACCNO;
	if(strcmp(trans.draccno,trans.craccno)==0)
	{
		return E_INPUT_2ACTNO_EQ;
	}
	des2src(trans.opercode,rPack->scust_limit);
	des2src(trans.chkopercode,rPack->scust_limit2);
	trim(rPack->semp_pwd);
	if(strlen(trans.opercode)==0)
	{
		return E_INPUT_OPER_NULL;
	}
	if(strlen(trans.chkopercode)==0)
	{
		return E_INPUTNULL_CHKOPER;
	}
	if(strcmp(trans.opercode,trans.chkopercode)==0)
	{
		writelog(LOG_ERR,"oper1[%s]chkoper[%s]",trans.opercode,trans.chkopercode);
		return E_INPUT_2OPER_EQ;
	}
	ret=chk_oper_pwd(trans.chkopercode,rPack->semp_pwd);
	if(ret)
	{
		return ret;
	}
	pAccTrans->trans.transamt=pAccTrans->trans.inputamt;
	pAccTrans->trans.fundtype=0;
	pAccTrans->trans.transtype=TRANSTYPE_MANDRCR;
	ret=pAccTrans->DoTransByTransType();
	if(ret)
		return ret;	
	ret=pAccTrans->doTransEnd();
	if(ret)
		return ret;
	sprintf(trans.remark,"交易金额%.2lf,借方账户[%s]余额%.2lf,贷方账户[%s]余额%.2lf",trans.totaltransamt,trans.draccname,trans.draccaftbal,trans.craccname,trans.craccaftbal);
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	des2src(outPack->sdate3,pAccTrans->trans.sysdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	sprintf(outPack->vsmess,"%s 借方账户[%s]贷方帐户[%s]",pAccTrans->remark.c_str(),pAccTrans->trans.draccname,trans.craccname);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

