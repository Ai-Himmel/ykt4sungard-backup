/* --------------------------------------------
 * 程序名称: F240020.cpp
 * 创建日期: 2009-08-07
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存转账后台记录流水
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"

int F240020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->trans.transcode=TC_BANKTRANS;
	TRANS& trans=pAccTrans->trans;
	trans.termid=rPack->lcert_code;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	trans.inputamt = rPack->lvol5/100.0;
	trans.unusedamt=trans.inputamt;
	trans.cardflag=1;
	trans.usecardflag=1;
	trans.cardbefbal=rPack->lvol6/100.00;
	trans.dpscnt=rPack->lvol1+1;	//充值次数
	trans.cardaftbal=trans.cardbefbal;
	//转账不允许转小数金额
	if((rPack->lvol5)%100>0)
	{
		writelog(LOG_ERR,"trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		strcpy(szMsg,"转账金额必须是整数");
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}
	if(rPack->lvol5<1)
	{
		writelog(LOG_ERR,"trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		strcpy(szMsg,"转账金额不能为0");
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}
	T_t_account		tAccount;		//帐户表
	T_t_card		card;
	T_t_bankcard 	bankcard;
	T_t_cfgbank     cfgbank;
	T_t_device device;
	
	memset(&cfgbank,0,sizeof cfgbank);
	memset(&tAccount,0,sizeof(tAccount));
	memset(&card,0,sizeof(card));
	memset(&bankcard,0,sizeof(bankcard));
	memset(&device,0,sizeof device);

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_AUTH,F_SNAME,F_SNAME2,F_LSERIAL0,F_STX_PWD,F_LVOL5,F_LVOL6,0);


	/*判断设备是否登陆
	if(0!=device_login_yes_or_no(trans.termid))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}
	*/
	
	/*
	char buffer[16]="";
	//判断是否处于日终结算状态
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

	ret=DB_t_device_read_by_deviceid(trans.termid, &device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_device_read_by_deviceid err,errcode=[%d],device_id=[%d]",ret,trans.termid);
		return E_DB_DEVICE_R;
	}
		
	trans.cardno=rPack->lvol0;
	ret=pAccTrans->CheckAcc(&card,&tAccount);
	if(ret)
		return ret;
	if(amtcmp(trans.cardbefbal-tAccount.balance,MAXAMT_CARDGTACC)>=0)
	{
		writelog(LOG_ERR,"cardbefbal[%.2lf]account balance[%.2lf]",trans.cardbefbal,tAccount.balance);
		return ERRIF_CARDBAL_EXCEPT;
	}
	double CardMaxBal=0;
	ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
	if(ret)
		return ret;
	if(amtcmp(trans.inputamt+trans.cardbefbal,CardMaxBal)>0)
		return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);

	trans.feetype=card.feetype;
	trans.cardtype=card.cardtype;
	trans.custid=card.custid;
//	if(tAccount.lastdpscnt>trans.dpscnt)
//	{
//		return ERRINFO(E_CARDCNT_LT_LASTCARDCNT,trans.dpscnt,tAccount.lastdpscnt);
//	}

	//校验绑定关系
	ret = DB_t_bankcard_read_by_custid(card.custid, &bankcard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			strcpy(szMsg,"学工号和银行卡号未绑定");
			return E_DB_BANKCARD_N;
		}
		else
		{
			return E_DB_BANKCARD_R;
		}
	}
	
	ret = DB_t_cfgbank_read_by_bankcode(bankcard.bankcode,&cfgbank);
	if(ret)
	{
		return E_DB_CFGBANK_R;
	}
	
	if(strncmp(trans.acctime,cfgbank.bankstarttime,6) < 0
		|| strncmp(trans.acctime,cfgbank.bankendtime,6) > 0)
	{
		return E_OUT_BANKTIME;
	}

	//取流水号
	ret=pAccTrans->GetTermSeqno();
	if(ret)
	{
		writelog(LOG_ERR,"GetTermSeqno error,error code=[%d]",ret);
		return ret;
	}

	T_t_refno tRefno;

	memset(&tRefno,0,sizeof(tRefno));
	
	get_random(tRefno.mac);

	ret= GetNewRefno(tRefno.refno);
	if(ret)
		return ret;
	des2src(tRefno.lastsaved,trans.sysdatetime);
	des2src(tRefno.accdate,trans.transdate);
	tRefno.termid = trans.termid;
	tRefno.termseqno = trans.termseqno;
	ret=DB_t_refno_add(&tRefno);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_REFNO_E;
		else
			return E_DB_REFNO_I;
	}
	
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.transflag = TF_DPS;
	transdtl.cardcnt=trans.dpscnt;
	transdtl.cardbefbal=trans.cardbefbal;
    transdtl.amount=trans.inputamt;
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.custid=tAccount.custid;
	//transdtl.sysid= rPack->lvol2;
	transdtl.exttype=EXTTYPE_BANKCARD;
	des2src(transdtl.extdata,bankcard.bankcardno);
	des2src(transdtl.showcardno,card.showcardno);
	transdtl.status[0]=DTLSTATUS_INIT;
	des2src(transdtl.refno,tRefno.refno);
	des2src(transdtl.devphyid,device.devphyid);
	GetCustBaseInfoByCustID(card.custid,transdtl.custname,transdtl.stuempno,NULL);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}	
	des2src(out_pack->scust_auth,bankcard.bankcardno);					// 银行卡号
	des2src(out_pack->sname,transdtl.stuempno);							// 学工号
	des2src(out_pack->sname2,transdtl.refno);							// 交易参考号
	des2src(out_pack->stx_pwd,tRefno.mac);								// 随机数
	out_pack->lserial0=trans.termseqno;									// 终端流水号
	out_pack->lvol5 = D2I(trans.inputamt*100);									// 交易金额 (分)
	out_pack->lvol6 = D2I(trans.cardbefbal*100);									// 入卡值(分)

	writelog(LOG_INFO,"bankcardno[%s],stuempno[%s],refno[%s],termseqno[%d],inputamt[%d],befbal[%d]",out_pack->scust_auth,
		out_pack->sname,out_pack->sname2,out_pack->lserial0,out_pack->lvol5,out_pack->lvol6);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


