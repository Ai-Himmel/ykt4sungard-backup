/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户充值
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

int F846333(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=TC_EACCDEPOSIT;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=pAccTrans->trans;

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	
	des2src(trans.craccno,rPack->sbank_acc);
	des2src(trans.eaccno,rPack->sbank_acc);
	if(!strlen(trans.eaccno))
		return E_INPUTNULL_ACCNO;
	//检查客户
	//去帐户信息
	T_t_netacc tNetAcc;	
	memset(&tNetAcc,0,sizeof(tNetAcc));
	ret=DB_t_netacc_read_by_accno(trans.eaccno,&tNetAcc);
	if(ret)
	{
		writelog(LOG_ERR,"accno[%s]",trans.eaccno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tNetAcc.status[0]!=STATUS_NORMAL)
	{
		return E_EACCNO_LOGOUT;
	}
	//	创建账号
	pAccTrans->trans.custid=tNetAcc.custid;
	pAccTrans->trans.inputamt=rPack->damt0;
	if(!pAccTrans->trans.inputamt)
		return E_INPUT_AMT_NULL;
	pAccTrans->trans.fundtype=rPack->lvol9;
	des2src(pAccTrans->trans.voucherno,rPack->scust_auth2);
	ret=pAccTrans->doTrans();
	if(ret)
		return ret;	
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	des2src(outPack->sdate3,pAccTrans->trans.sysdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	sprintf(outPack->vsmess,"客户[%s] %s 帐户余额:%.2f元",tNetAcc.accname,pAccTrans->remark.c_str(),pAccTrans->trans.craccaftbal);
	des2src(trans.remark,outPack->vsmess);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
