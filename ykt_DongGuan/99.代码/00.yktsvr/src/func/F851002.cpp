/* --------------------------------------------
 * 创建日期: 2011-04-12
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能:充值商户交款
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>	
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "errdef.h"
#include "dbfunc.h"
#include "busqc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "transfunc.h"


int F851002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	
	CAccTrans& ats=CAccTrans::GetInst();
	TRANS& trans=ats.trans;	
/*	
	ret=ats.CheckCfgUpdate();
	if(ret)
		return ret;

	des2src(trans.opercode,rPack->semp);
	ret=ats.InitTrans();
	if(ret)
		return ret;
	*/
	

	ret = ats.GetNewRefno(trans.refno); // 交易参考号
	if(ret)
		return ret;

	int termid = rPack->lvol0; // 终端编号
	int merchid=rPack->lvol1; // 商户编号
	int depositamt=rPack->lvol2; // 缴款金额
	int fundtype = rPack->lvol3; // 缴款类型
	int termseqno = rPack->lvol4; // 终端流水号

	// 参数检查
	if(	termid <= 0 || 
		merchid<1||
		depositamt<=0 || 
		fundtype < 0 ||
		termseqno <= 0 ||
		strlen(rPack->semp) <= 0||
		strlen(rPack->sbankname) <= 0)
	{
		return E_INPUT_DATA_INVAILD;
	}
	
	// 读取商户表
	T_t_merch t_merch;
	memset(&t_merch,0,sizeof(t_merch));
	
	ret=DB_t_merch_read_by_merchid(merchid,&t_merch);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCH_N;
		else
			return E_DB_MERCH_R;
	}

	if(t_merch.status=='2')
	{
		DB_t_merchpara_free_lock_by_c0();
		return E_DB_MERCH_NG;
	}

	// 读取充值商户参数表
	T_t_merchpara t_merchpara ;
	memset(&t_merchpara,0,sizeof(t_merchpara));

	ret = DB_t_merchpara_read_by_merchid(merchid, &t_merchpara);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCHPARA_N;
		else
			return E_DB_MERCHPARA_R;
	}

	if(t_merchpara.status!=1)
	{
		return E_DB_MERCHPARA_NG;
	}

	// 读取充值商户工作表
	T_t_merchwork t_merchwork ;
	memset(&t_merchwork,0,sizeof(t_merchwork));

	ret=DB_t_merchwork_read_lock_by_c0_and_merchid(merchid,&t_merchwork);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCHWORK_N;
		else
			return E_DB_MERCHWORK_R;
	}
	
	// 缴款金额
	t_merchwork.czamt += depositamt;

	ret=DB_t_merchwork_update_lock_by_c0(&t_merchwork);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCHWORK_N;
		else
			return E_DB_MERCHWORK_U;
	}

	T_t_operdtl _operdtl;
	memset(&_operdtl,0,sizeof(_operdtl));

	char sysDate[8+1]={0};
	char sysTime[6+1]={0};
	
	getsysdate(sysDate);
	getsystime(sysTime);
	
	// ADD Oper
	_operdtl.branchid = rPack->lvol5;
	_operdtl.operid = atoi(rPack->semp);
	_operdtl.hostdate = atoi(sysDate);
	_operdtl.hosttime = atoi(sysTime);
	_operdtl.accdate = _operdtl.hostdate;
	
	//GetCpackDataString(ats.reqpack, _operdtl.reqdata);
	strcpy(_operdtl.refno, trans.refno);
	_operdtl.operseqno = 0;
	if(_operdtl.operseqno < 1)
	{
		_operdtl.operseqno = atol(_operdtl.refno + 6);
	}
	
	_operdtl.transcode = TC_SHOPSAVING;
	sprintf(_operdtl.transdesc, "充值商户缴款");
	_operdtl.termid = termid;
	des2src(_operdtl.samno, rPack->scust_auth);
	_operdtl.termseqno = termseqno;
	_operdtl.cardno = 0;//
	_operdtl.amount = depositamt;
	_operdtl.otheramt = 0;
	_operdtl.status = TRANSTATUS_SUCC;

	ret = DB_t_operdtl_add(&_operdtl);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_OPERDTL_E;
		else
			return E_DB_OPERDTL_I;
	}

	// ADD Operacc
	T_t_operaccdtl _operaccdtl;
	memset(&_operaccdtl,0,sizeof(_operaccdtl));
	
	_operaccdtl.accdate = _operdtl.accdate;
	_operaccdtl.transdate= _operdtl.accdate;
	strcpy(_operaccdtl.refno, _operdtl.refno);
	_operaccdtl.transcode = _operdtl.transcode;
	_operaccdtl.inamt=_operdtl.amount;
	_operaccdtl.branchid= _operdtl.branchid;
	_operaccdtl.operid = _operdtl.operid;
	sprintf(_operaccdtl.remark, "充值商户交款");

	ret = DB_t_operaccdtl_add(&_operaccdtl);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_OPERDTL_E;
		else
			return E_DB_OPERDTL_I;
	}
	
	// 返回信息
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0, F_LVOL1, F_LVOL2, F_LVOL3 ,F_LVOL4, F_LVOL5,F_LVOL6, F_SBANKNAME, F_SCERT_NO, F_VSMESS,0);

	des2src(outPack->sbankname,t_merch.merchname); // 商户名
	outPack->lvol0=t_merchpara.merchid; // 商户编号
	outPack->lvol1=depositamt; // 缴款金额
	outPack->lvol2=t_merchwork.czamt; // 缴款后余额
	des2src(outPack->scert_no,_operdtl.refno); // 交易参考号
	outPack->lvol3=_operdtl.operseqno; // 操作员流水号
	outPack->lvol4=_operdtl.hostdate; // 记账日期
	outPack->lvol5=_operdtl.hosttime; // 记账时间
	outPack->lvol6=_operdtl.termseqno; // 终端流水号

	sprintf(outPack->vsmess,"商户[%s][%s]缴款%.2lf元 账户余额%.2lf元 最大额度%.2lf元 可用额度%.2lf元",
		t_merch.merchname,
		rPack->sbankname,
		depositamt/100.0,
		t_merchwork.czamt/100.0,
		t_merchpara.czamtmax/100.0,
		(t_merchpara.czamtmax + t_merchwork.czamt)/100.0);

	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}


