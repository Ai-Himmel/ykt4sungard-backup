/* --------------------------------------------
 * 程序名称: F240021.cpp
 * 创建日期: 2009-08-07
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存转账
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
#include "bupub.h"
#include "svrlink.h"

static int doTrans(int tradecode,T_t_transdtl  *transdtl,char *errmsg)
{
	int ret = 0;
	int request_type = 2401;
	int drtp_branch  = 0;
	int base_funcno = 0;
	int bcc_timeout = 0;
	char bankcode[3] = "";
	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = request_type;
	
	SetHeadCol(&sPack,F_LCERT_CODE,F_SCUST_AUTH,F_LVOL0,F_LVOL1,F_SDATE0,
		F_SHOLDER_AC_NO,F_SPHONE,F_SCUST_LIMIT,F_SCUST_LIMIT2,F_SCUST_AUTH2,F_DAMT0,0);      

	T_t_bankcard bankcard;
	memset(&bankcard,0,sizeof bankcard);
	ret = DB_t_bankcard_read_by_custid_and_bankcardno(transdtl->custid,transdtl->extdata, &bankcard);
	if(ret)
	{
		return E_DB_BANKCARD_R;
	}
	des2src(bankcode,bankcard.bankcode);

	T_t_cfgbank cfgbank;
	memset(&cfgbank,0,sizeof cfgbank);
	ret = DB_t_cfgbank_read_by_bankcode(bankcode,&cfgbank);
	if(ret)
	{
		return E_DB_CFGBANK_R;
	}

	T_t_customer customer;
	memset(&customer,0,sizeof customer);
	ret = DB_t_customer_read_by_custid(transdtl->custid, &customer);
	if(ret)
	{
		return E_DB_CUSTOMER_R;
	}
	
	drtp_branch = cfgbank.bccdrtpno;								// drtp 编号
	base_funcno = cfgbank.bccfuncno;							// 前置主功能号
	bcc_timeout = cfgbank.bcctimeout;								// 前置超时时间

	sPack.pack.lcert_code = tradecode;								// 交易码
	des2src(sPack.pack.scust_auth,cfgbank.bankip);					// 银行ip
	sPack.pack.lvol0 = cfgbank.bankport;							// 银行端口
	sPack.pack.lvol1 = cfgbank.banktimeout*1000;					// 银行超时时间

	des2src(sPack.pack.sdate0,transdtl->transdate);					// 交易日期
	des2src(sPack.pack.sholder_ac_no,transdtl->refno);				// 一卡通交易参考号
	des2src(sPack.pack.sphone,transdtl->stuempno);					// 学工号
	des2src(sPack.pack.scust_limit,customer.custname);				// 姓名
	des2src(sPack.pack.scust_auth2,customer.idno);					// 身份证号
	des2src(sPack.pack.scust_limit2,transdtl->extdata);				// 银行卡号
	sPack.pack.damt0 = transdtl->amount;							// 交易金额
	if(bcc_timeout<5)
	   bcc_timeout=5;
	
	ret = ExtCall(0, drtp_branch, base_funcno, 0, bcc_timeout, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		writelog(LOG_ERR,"extcall 2401 ret[%d],retcode[%d] timeout[%d] ",ret,aPack.head.retCode,bcc_timeout);
		if (ret < 0)				// 通讯错误，要冲正的
		{
			strcpy(errmsg,"调用后台业务失败，业务终止");
			return E_BCC_NETWORK;
		}
		else						// 收到前置返回的错误
		{
			trim(aPack.pack.vsmess);
			strcpy(errmsg,aPack.pack.vsmess);
			return E_COMMON_ERR;
		}
	}
	if(aPack.pack.lvol1 != 1)		// 前置解包错误
	{	
		strcpy(errmsg,"接收银行数据错误");
		return E_BCC_NETWORK;
	}
	return 0;
}


int F240021(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int ret1 = 0;
	int reverse_flag = 0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->trans.transcode=TC_BANKTRANS;
	TRANS& trans=pAccTrans->trans;
	trans.termid=rPack->lcert_code;

	T_t_account	tAccount;		//帐户表
	T_t_transdtl  transdtl;		//卡操作流水表
	T_t_card	card;
	T_t_refno refno;

	memset(&tAccount,0,sizeof(tAccount));
	memset(&transdtl,0,sizeof(transdtl));
	memset(&card,0,sizeof(card));
	memset(&refno,0,sizeof(refno));


	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_LVOL2,F_SDATE0,0);

	//判断是否处于日终结算状态
	/*
 	ret=GetSysParaVal(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetSysParaVal error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		writelog(LOG_ERR,"System is balance now!");
		return E_TRANS_BANK_SERVICE_NOEXIT;
	}
	*/
	trans.cardno=rPack->lvol0;
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

	des2src(refno.refno,rPack->sname2);
	ret = DB_t_refno_read_by_refno(refno.refno,&refno);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_REFNO_N;
		else
			return E_DB_REFNO_R;
	}
	if(strncmp(refno.mac,rPack->stx_pwd,8)!=0)
	{
		ERRTIP("交易参考号MAC校验错误");
		return E_COMMON_ERR;
	}

	ret = DB_t_transdtl_read_by_refno(refno.refno, &transdtl);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_TRANSDTL_N;
		else
			return E_DB_TRANSDTL_R;
	}
	if(transdtl.status[0] != DTLSTATUS_INIT)
	{
		if(transdtl.status[0] == DTLSTATUS_SUCCESS)					// 已经成功了
		{
			out_pack->damt0=transdtl.cardaftbal;
			out_pack->damt1=transdtl.amount;
			out_pack->damt2=transdtl.managefee;	
			out_pack->lvol2=D2I(transdtl.cardaftbal*100);
			return 0;
		}
		else
		{
			ERRTIP("流水处理失败");
			return E_COMMON_ERR;
		}
	}
	
	ret = doTrans(TRADE_TRANS,&transdtl,szMsg);
	if(ret)
	{
		if(ret != E_BCC_NETWORK)
		{
			transdtl.errcode = ret;
			transdtl.status[0] = DTLSTATUS_FAIL;
			des2src(transdtl.remark,szMsg);
			if(DB_t_transdtl_update_by_refno(refno.refno,&transdtl))
				return E_DB_TRANSDTL_U;
			else
			{			
				db_commit();
				return ret;
			}
		}
		else							// 通讯问题，要冲正
		{
			reverse_flag = 1;
			goto L_RET;
		}
	}

	trans.inputamt = transdtl.amount;
	trans.unusedamt=trans.inputamt;
	//开始填充流水数据
	//流水号
	//模式修改为，测试入帐产生流水号，记录流水结构，正式入账只修改该
	//流水的出卡值以及流水状态

	writelog(LOG_INFO,"trans sucess");
	ret=pAccTrans->InitTrans();
	if(ret)
	{
		reverse_flag = 1;
		goto L_RET;
	}
	//判断转帐金额是否超出钱包最大限额
	ret=DB_t_account_read_by_accno(card.accno,&tAccount);
	if(ret)
	{
		reverse_flag = 1;
		ret = E_DB_ACCOUNT_R;
		goto L_RET;
	}
	writelog(LOG_INFO,"name[%s]",tAccount.accname);
//	if(amtcmp(tAccount.availbal+trans.inputamt,tAccount.cardmaxbal)>0)
//	{
//		DB_t_transdtl_free_lock_by_c0();
//		return E_TRANS_TRANSMONEY_OUTRANGE;
//	}
	des2src(trans.cardaccno,tAccount.accno);			//贷方帐户,持卡人账户
	trans.cardflag=1;
	trans.usecardflag=1;
	trans.feetype=card.feetype;
	trans.cardtype=card.cardtype;
	trans.cardbefbal=transdtl.cardbefbal;
	trans.dpscnt=transdtl.cardcnt;
	trans.cardaftbal=trans.cardbefbal;
	
	ret=pAccTrans->doFeeTrans();
	if(ret)
	{
		reverse_flag = 1;
		goto L_RET;
	}
	//writelog(LOG_INFO,"donfeetrans done");
	ret=pAccTrans->doMainTrans();
	if(ret)
	{
		reverse_flag = 1;
		goto L_RET;
	}
	//writelog(LOG_INFO,"doMainTrans done");
	ret=pAccTrans->doTransEnd();
	if(ret)
	{
		reverse_flag = 1;
		goto L_RET;
	}
	//结束填充流水数据
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	

	ret=DB_t_transdtl_update_by_refno(refno.refno,&transdtl);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_transdtl_update_by_refno error,error code=[%d]",ret);
		reverse_flag = 1;
	}
	
L_RET:	
	if(reverse_flag)
	{
		transdtl.status[0] = DTLSTATUS_FAIL;
		ret1 = doTrans(TRADE_REVERSE, &transdtl, szMsg);
		if(ret1)												// 冲正也失败了，对账解决不平
		{
			transdtl.errcode = ret1;
			des2src(transdtl.remark,szMsg);
			strcat(transdtl.remark," 冲正失败");
			if(DB_t_transdtl_update_by_refno(refno.refno,&transdtl))
				return E_DB_TRANSDTL_U;
			else
			{			
				db_commit();
				return ret1;
			}
		}
		///////////////冲正成功了，提示刚才要冲正的原因
		transdtl.errcode = ret;
		if(DB_t_transdtl_update_by_refno(refno.refno,&transdtl))
			return E_DB_TRANSDTL_U;
		else
		{			
			db_commit();
			return ret;
		}
	}	
	
	out_pack->damt0=transdtl.cardaftbal;
	out_pack->damt1=transdtl.amount;
	out_pack->damt2=transdtl.managefee;	
	out_pack->lvol2=D2I(transdtl.cardaftbal*100);
	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

