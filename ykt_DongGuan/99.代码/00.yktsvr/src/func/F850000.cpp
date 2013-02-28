/* --------------------------------------------
 * 创建日期: 2009-08-08
 * 程序作者:
 * 版本信息: 3.0.0.0
 * 程序功能: 请求交易参考号
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
#include "payment.h"

int F850000(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();

    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    memset(&aPack,0,sizeof(aPack));
    ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SPHONE3,F_SADDR,0);

	ats.trans.cardno= rPack->lvol0;
	if(ats.trans.cardno>0)
	{
		T_t_card  tCard;
		ret=ats.CheckAcc(&tCard);
		if(ret)
		{
			writelog(LOG_INFO,"检查状态失败");
			return ret;
		}
	}
	/////////////////////////////////////////////////////////
	int paycode=rPack->lcert_code;
	if(paycode)
	{
		SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,F_DAMT0,F_DAMT1,F_DAMT2,F_SDATE1,F_LWITHDRAW_FLAG,
			   F_SBANKNAME,F_SADDR,F_SNAME2,F_VSMESS,0);
		
		CPaymentBase *payment;
		payment = CPaymentBase::find_payment(paycode);
		if(NULL == payment)
		{
			return E_TRANS_FUNC_NONSUPPORT;
		}
		ret = payment->init(handle,&aPack,rPack);
		if(ret)
		{
			writelog(LOG_ERR,"trade[%d],ret[%d]",paycode,ret);		
			return	ret;
		}
		if(payment->payment_.onlinepay>0&&payment->payment_.paychkflag>0)
		{
			ret = payment->qry_acc(handle,rPack,outPack);
			if(ret)
			{
				writelog(LOG_ERR,"查询收款方账户信息错误trade[%d],ret[%d]",paycode,ret);
				return ret;
			}
		}
	}	
	T_t_refno tRefno;

	memset(&tRefno,0,sizeof(tRefno));
	
	get_random(tRefno.mac);

	ret= GetNewRefno(tRefno.refno);
	if(ret)
		return ret;
	des2src(tRefno.lastsaved,pAccTrans.hostdatetime);
	ret=DB_t_refno_add(&tRefno);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_REFNO_E;
		else
			return E_DB_REFNO_I;
	}
	strcpy(outPack->sphone3,tRefno.refno);
	strcpy(outPack->saddr,tRefno.mac);	
	/////////////////////////////////////////////////////////
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
