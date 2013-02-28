/* --------------------------------------------
 * 创建日期: 2008-06-30
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通充值
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
#include "checkcardstatus.h"
int F846312(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	TRANS& trans=ats.trans;
	strcpy(ats.trans.opercode,ats.reqpack->semp);
	strcpy(ats.trans.samno,ats.reqpack->snote);
	ats.trans.termseqno=ats.reqpack->lserial0;
	ats.trans.termdate=atol(ats.reqpack->sdate0);
	ats.trans.termtime= atol(ats.reqpack->stime0);
	des2src(ats.trans.cardphyid,ats.reqpack->sstation0);
	des2src(ats.trans.cardasno,ats.reqpack->sphone3); 
	ats.trans.fundtype=ats.reqpack->lvol9;
	if(!trans.fundtype)
		return E_INPUTNULL_PAYTYPE;
	ats.SetCardCntAndCardBal(ats.reqpack->lvol5,ats.reqpack->lvol6,ats.reqpack->lvol7);
	ats.SetInputAmt(ats.reqpack->damt0);
	char srvstatus[11]={0};
	ret =GetSysParaVal(110,srvstatus);
	if(ret)
	{
		return ret;
	}
	if(srvstatus[0]!='1')
	{
		ERRTIP("与加密机服务器通讯故障,请等待网络恢复后再充值");
		return E_COMMON_ERR;
	}
	ret=ats.ChkOper();
	if(ret)
		return ret;	
	ret=GetCardIDByCardasno(trans.cardasno,&ats.trans.cardid);
	if(ret)
	{
		return ret;
	}
	CCardDeposit obj;
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
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE0,F_STIME0,F_SPHONE3,F_SPHONE,F_SNAME2,F_SALL_NAME,
		F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL0,F_VSMESS,F_STIME3,F_SCERT_NO,0);	
	const T_t_operdtl& operdtl=obj.GetObjOperdtl();
	const T_t_carddtl& carddtl=obj.GetObjCarddtl();
	const T_t_card& card=obj.GetObjCard();
	const T_t_customer& customer=obj.GetObjCustomer();
	sprintf(outPack->sdate3,"%d",ats.accdate);
	strcpy(outPack->scert_no,obj.GetTrans().refno);
	outPack->lvol0=card.cardno;
	des2src(outPack->sphone3,card.cardasno);
	outPack->lvol8=obj.GetAftcardbal();
	outPack->lserial0=operdtl.operseqno;
	strcpy(outPack->sname2,obj.GetObjCardtype().cardtypename);
	strcpy(outPack->sall_name,customer.custname);
	strcpy(outPack->sphone,customer.mobile);
	sprintf(outPack->stime3,"%06d",ats.hosttime);
	des2src(outPack->semp,ats.trans.opercode);
	outPack->lwithdraw_flag=ats.trans.termid;
	des2src(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
