/* --------------------------------------------
 * 创建日期: 2008-06-27
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 卡余额调整
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
#include "transfunc.h"
#include "cardprocess.h"

int F846322(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	CAccTrans& ats = CAccTrans::GetInst();
	TRANS& trans = ats.trans;
	des2src(ats.trans.opercode, rPack->semp);
	ats.trans.transcode = TC_CARDBALMOD;
	des2src(trans.cardasno, ats.reqpack->scard0);
	strcpy(ats.trans.samno, ats.reqpack->snote);
	ats.trans.termseqno=ats.reqpack->lserial0;
	ats.trans.termdate = atol(ats.reqpack->sdate0);
	ats.trans.termtime = atol(ats.reqpack->stime0);
	ats.SetCardCntAndCardBal(ats.reqpack->lvol5, ats.reqpack->lvol6, ats.reqpack->lvol7);
	des2src(trans.cardphyid, ats.reqpack->sstation1);
	if(ats.reqpack->lbank_acc_type > 0)
	{
		ats.trans.inputamt= D4U5(ats.reqpack->damt0 * 100.0);
	}
	else
	{
		ats.trans.inputamt = -D4U5(ats.reqpack->damt0 * 100.0);
	}
	ret = ats.ChkOper();
	if(ret)
		return ret;
	ret = chk_oper_pwd(rPack->semp_no, rPack->scust_limit);
	if(ret)
	  return ret;
	ret = GetCardIDByCardasno(trans.cardasno, &trans.cardid);
	if(ret)
	{
		return ret;
	}
	CCardBalUpd obj;
	obj.SetTrans(ats.trans);
	
	if(!obj.LockCard())
	{
		return obj.GetErrCode();
	}
	if(!obj.ExecBefChk())
	{
		return obj.GetErrCode();
	}
	if(!obj.Execute())
	{
		return obj.GetErrCode();
	}
	if(!obj.ExecAftChk())
	{
		return obj.GetErrCode();
	}
	if(!obj.SaveExecResult())
	{
		return obj.GetErrCode();
	}
	if(!obj.buildOutput())
	{
		return obj.GetErrCode();
	}
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle, F_LVOL0, F_LVOL8, F_SDATE0, F_SCARD0,
	       F_SDATE3, F_STIME3, F_SEMP, F_LWITHDRAW_FLAG, F_LSERIAL0, F_VSMESS, F_SNAME2,F_SALL_NAME,F_SPHONE,0);
	outPack->lvol0 = obj.GetObjCard().cardno;
	des2src(outPack->scard0, obj.GetObjCard().cardasno);
	outPack->lvol8 = obj.GetAftcardbal();
	sprintf(outPack->sdate3, "%d", ats.hostdate);
	sprintf(outPack->stime3, "%06d", ats.hosttime);
	des2src(outPack->semp, trans.opercode);
	outPack->lwithdraw_flag = trans.termid;
	outPack->lserial0 = trans.operseqno;
	strcpy(outPack->sname2,obj.GetObjCardtype().cardtypename);
	strcpy(outPack->sall_name,obj.GetObjCustomer().custname);
	strcpy(outPack->sphone,obj.GetObjCustomer().mobile);

	writelog(LOG_ERR, "cardno:%d,cardbal:%d,date:%s,time:%s" , outPack->lvol0 , outPack->lvol8, outPack->sdate3, outPack->stime3);
	sprintf(trans.remark, "余额调整%.2lf元,卡余额%.2lf元",ats.trans.inputamt/ 100.0,obj.GetAftcardbal()/ 100.0);
	des2src(outPack->vsmess, trans.remark);
	PutRow(handle, outPack, pRetCode, szMsg);
	return 0;
}
