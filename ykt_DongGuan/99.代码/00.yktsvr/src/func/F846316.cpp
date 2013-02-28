/* --------------------------------------------
 * 创建日期: 2008-06-27
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通充值冲正
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

int F846316(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	des2src(ats.trans.opercode,rPack->semp);
	ats.trans.transcode=TC_CARDDEPOSITREV;
	ret=ats.ChkOper();
	if(ret)
		return ret;			
	TRANS& trans=ats.trans;
	des2src(trans.chkopercode,rPack->semp_no);

	ret=chk_oper_pwd(trans.chkopercode,rPack->scust_limit);
	if(ret)
		return ret;
	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	
	//des2src(oldaccdate,rPack->sdate3);
	int oldtermid=rPack->lwithdraw_flag;
	int oldtermseqno=rPack->lserial1;

	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_STIME3,F_SEMP,F_LSERIAL1,F_SSTATION0,F_VSMESS,0);	
	trans.cardflag=1;
	trans.usecardflag=1;
	trans.cardno=rPack->lvol0;
	ats.SetCardCntAndCardBal(rPack->lvol5,rPack->lvol6,rPack->lvol7);
	trans.aftpaycnt++;
	outPack->lvol0=ats.trans.cardno;
	outPack->lvol8=D4U5(ats.trans.cardaftbal*100,0);
	des2src(outPack->sdate3,ats.trans.accdate);
	des2src(outPack->stime3,ats.trans.acctime);
	des2src(outPack->semp,ats.trans.opercode);
	outPack->lserial1=ats.trans.termseqno;
	//sprintf(outPack->vsmess,"冲正金额%.2lf 卡余额%.2lf元",ats.trans.transamt,ats.trans.cardaftbal);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
