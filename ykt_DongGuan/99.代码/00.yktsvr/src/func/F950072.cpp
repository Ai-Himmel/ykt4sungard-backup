/* --------------------------------------------
 * 创建日期: 2010-10-22 
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 汇多充值机充值请求
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
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"
#include "interfacefunc.h"
#include "interface.h"
#include "transfunc.h"


extern int addPOSCheckPOS(int deviceid,T_t_device &tDevice);

static int doCard(const T_t_card& tCard)
{
	char sysdate[9]={0};
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		return ERRIF_CARD_CLOSE;
	}	
	if('1'==tCard.lockflag[0])
	{
		return ERRIF_CARD_LOCKED;
	}
	if('1'==tCard.frozeflag[0])
	{
		return ERRIF_CARD_FROZED;
	}
	if('1'==tCard.lossflag[0])
	{
		return ERRIF_CARD_LOST;
	}	
	if('1'==tCard.badflag[0])
	{
		return ERRIF_CARD_BAD;
	}		
	//检查卡的有效期
	if(strcmp(tCard.expiredate,CAccTrans::GetInst().trans.transdate)<=0)
		return ERRIF_CARD_EXPIRED;
	return 0;
}

static int doRecordTransPack(ST_PACK *rPack,T_t_transpack &transpack,T_t_device &tDevice)
{
	int ret;
	GetCpackDataString(rPack,transpack.reqdata);
	des2src(transpack.transdate,rPack->sdate0);
	des2src(transpack.transtime,rPack->stime0);
	transpack.reqsno = rPack->lserial0;
	
	sprintf(transpack.packetid,"%s%s%03d",transpack.transdate,transpack.transtime,transpack.reqsno%1000);
	sprintf(transpack.reqid,"%d",tDevice.deviceid);
	//transpack.funcno = iRequest;
	transpack.status[0]=TRANSPACKSTATE_NODEAL;
	transpack.revflag = 0;
	des2src(transpack.lastupdtime,CAccTrans::GetInst().hostdatetime);
	transpack.datalen = strlen(transpack.reqdata);
	ret = DB_t_transpack_add(&transpack);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
			//
			return DB_REPEAT;
		}
		else
		{
			return E_DB_ERROR;
		}
	}
	if(db_commit())
		return E_DB_ERROR;
	return 0;
}
static int doCheck950072(T_t_device &tDevice,T_t_dpsoper &tOperator,T_t_card &tCard,ST_PACK *rPack)
{
	int ret;
	ret = addPOSCheckPOS(rPack->lwithdraw_flag,tDevice);
	if(ret)
	{
		return ret;
	}
	

	ret = DB_t_dpsoper_read_by_opercode(rPack->semp_no,&tOperator);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"DB_t_dpsopercard_read_by_opercode error ,ret[%d]",ret);
			return ERRIF_POS_NOTLOGIN;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_dpsopercard_read_by_opercode error ,ret[%d]",ret);
			return ERRIF_SYSTEM;
		}
	}
	if(tOperator.batchno != rPack->lvol1)
	{
		writelog(LOG_ERR,"oper[%s]device[%s] batchno error db[%d] pos[%d]",tOperator.opercode,
			tDevice.devphyid,tOperator.batchno,rPack->lvol1);
		return ERRIF_POS_NOAUTH;
	}
	if(tOperator.authcode!= rPack->lvol2)
	{
		writelog(LOG_ERR,"oper[%s]device[%s] authcode error db[%d] pos[%d]",tOperator.opercode,
			tDevice.devphyid,tOperator.authcode,rPack->lvol2);
		return ERRIF_POS_NOAUTH;
	}
	if(strcmp(tDevice.devphyid,tOperator.devphyid))
	{
		writelog(LOG_ERR,"oper[%s] db device[%s] pos[%s]",tOperator.opercode,tOperator.devphyid,
			tDevice.devphyid);
		return ERRIF_POS_NOAUTH;
	}
	return 0;
}

static int doAccount(T_t_transdtl &transdtl,T_t_card &tCard,ST_PACK *rPack)
{
	int ret;
	CAccTrans& ats = CAccTrans::GetInst();
	TRANS &trans = ats.trans;
	
	ret = ats.InitTrans();
	if(ret)
	{
		writelog(LOG_ERR,"InitTrans error ,ret[%d]",ret);
		return ERRIF_SYSTEM;
	}
	trans.cardno=tCard.cardno;
	if(trans.cardno<1)
	{
		return ERRIF_CARD_NOTEXIST;
	}	
	trans.fundtype=1;// 现金
	trans.feetype=tCard.feetype;
	trans.cardtype=tCard.cardtype;
	trans.cardphytype=tCard.cardphytype;
	des2src(trans.transdate,rPack->sdate0);
	des2src(trans.transtime,rPack->stime0);
	if(IsInvalidDateTime(trans.transdate,"YYYYMMDD"))
	{
		return ERRIF_POS_NOINWORKTIME;
	}
	if(IsInvalidDateTime(trans.transtime,"HHMMSS"))
	{
		return ERRIF_POS_NOINWORKTIME;
	}
	if(strcmp(trans.transdate,trans.accdate)!=0)
	{
		return ERRIF_POS_NOINWORKTIME;
	}
	T_t_account tAccount;
	memset(&tAccount,0,sizeof(tAccount));

	ret=CardAccInfoReadbyAccno(trans.cardaccno,&tAccount);
	if(ret)
	{	
		return ret;
	}
	if(tAccount.status[0]!=STATUS_NORMAL)
	{
		return ERRIF_CARDACC_EXCEPT;
	}
	if(amtcmp(tAccount.balance-trans.cardbefbal,MAXAMT_CARDGTACC)>0)
	{
		writelog(LOG_ERR,"卡余额[%.2lf]错误",trans.cardbefbal);
		return ERRIF_CARDBAL_EXCEPT;
	}
	double CardMaxBal=0;
	ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
	if(ret)
		return ERRIF_SYSTEM;
	if(amtcmp(trans.inputamt+trans.cardbefbal,CardMaxBal)>0)
	{
		writelog(LOG_ERR,"card balance error");
		return ERRIF_CARDBAL_EXCEPT;
	}
	trans.custid=tCard.custid;
	if(trans.custid>0)
	{
		ret=GetCustBaseInfoByCustID(trans.custid,trans.custname,trans.stuempno,NULL);
		if(ret)
			return ret;
	}
	// 此处是并发请求，需要改进
	ret = ats.doTrans();
	if(ret)
	{
		writelog(LOG_ERR,"ats.doTrans error, ret=[%d]",ret);
		return ERRIF_SYSTEM;
	}
	ret = ats.doTransEnd();
	if(ret)
	{
		writelog(LOG_ERR,"ats.doTransEnd error, ret=[%d]",ret);
		return ERRIF_SYSTEM;
	}
	des2src(transdtl.opercode,trans.opercode);
	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.transflag = trans.transflag;
	transdtl.cardcnt=trans.aftdpscnt;
	transdtl.cardbefbal=trans.cardbefbal;
    transdtl.amount=trans.inputamt;
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.custid=tAccount.custid;
	transdtl.devseqno =rPack->lserial0;
	des2src(transdtl.custname,trans.custname);
	des2src(transdtl.stuempno,trans.stuempno);
	des2src(transdtl.showcardno,tCard.showcardno);
	
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}	
	return 0;
}
static int calcDepositKey(const T_t_card &tCard,ST_PACK *rPack,char *mac)
{
	int ret;
	T_t_cardphytype tCardPhyType;
	cpu_trade_t cpu_trade;
	char sMac[25] = {0};
	
	memset(&tCardPhyType,0,sizeof tCardPhyType);

	memset(&cpu_trade,0,sizeof cpu_trade);
	cpu_trade.trade_type=0;
	des2src(cpu_trade.random_key,rPack->sbank_pwd);
	cpu_trade.tradeamt = rPack->lvol8;
	cpu_trade.tradecnt = rPack->lvol5; // 必须是交易前次数
	cpu_trade.balance = rPack->lvol7;
	cpu_trade.termsno = rPack->lserial0;
	des2src(cpu_trade.termno,rPack->sstation0); // 终端号
	strncpy(cpu_trade.tx_datetime,rPack->sdate0,8);
	strncpy(cpu_trade.tx_datetime+8,rPack->stime0,6);
	des2src(sMac,rPack->sstock_code); // MAC1,只在移动规范中使用
	//des2src(cpu_trade.cardphyid,rPack->sname);
	des2src(cpu_trade.cardphyid,tCard.cardphyid);


	ret = DB_t_cardphytype_read_by_cardphytype(tCard.cardphytype,&tCardPhyType);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"cannot find cardphytype code[%d]",tCard.cardphytype);
			return ERRIF_CARD_NORIGHT;
		}
		else
			return ERRIF_SYSTEM;
	}
	if(tCard.cardphytype == CARDPHYTYPE_CPU)
	{
		if((tCardPhyType.cardphytypecode & 0x0100) == 0x0100)
		{
			// 
			ret = calc_cpucard_mac(&cpu_trade,sMac,0);
		}
		else
		{
			writelog(LOG_ERR,"not support card phytype phytype[%d]code[%d]",
					tCardPhyType.cardphytype,tCardPhyType.cardphytypecode);
			return ERRIF_CARD_NORIGHT;
		}
	}
	else if(tCard.cardphytype == CARDPHYTYPE_RFID)
	{
		if(tCardPhyType.cardphytypecode == 0x0501) // 广州大学城
		{
			return ERRIF_CARD_NORIGHT;
		}
		else if(tCardPhyType.cardphytypecode == 0x0502) // 电信CPU 卡
		{
			ret = calc_cpucard_mac(&cpu_trade,sMac,0);
		}
		else if(tCardPhyType.cardphytypecode == 0x0503) // 移动手机卡
		{
			ret = calc_cpucard_mac(&cpu_trade,sMac,1);
		}
		else if(tCardPhyType.cardphytypecode == 0x0504) // 电信翼机通卡
		{
			ret = calc_cpucard_mac(&cpu_trade,sMac,2);
		}
		else
		{
			return ERRIF_CARD_NORIGHT;
		}
	}
	else if(tCard.cardphytype == CARDPHYTYPE_MF1)
	{
		return 0;
	}
	else
	{
		return ERRIF_CARD_NORIGHT;
	}
	if(ret)
	{
		return ERRIF_OTHER;
	}
	strcpy(mac,sMac);
	return 0;
}
static int do950072(T_t_transpack &transpack,ST_PACK *rPack,ST_PACK *outPack)
{
	int ret;
	T_t_dpsoper tOperator;
	T_t_device tDevice;
	T_t_card tCard;
	T_t_transdtl transdtl;
	memset(&tDevice,0,sizeof tDevice);
	memset(&tOperator,0,sizeof tOperator);
	memset(&transdtl,0,sizeof transdtl);
	memset(&tCard,0,sizeof(tCard));

	des2src(tDevice.devphyid,rPack->sphone3);
	
	CAccTrans& ats = CAccTrans::GetInst();
	TRANS &trans = ats.trans;
	trans.transcode = TC_POSDEPOSIT;
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.inputamt= D4U5(rPack->lvol8/100.0,2);	
	trans.unusedamt = trans.inputamt;
	ats.SetCardCntAndCardBal(rPack->lvol5,rPack->lvol6,rPack->lvol7);
	trans.transflag=TF_DPS;
	trans.aftdpscnt++;
	
	ret = doCheck950072(tDevice,tOperator,tCard,rPack);
	if(ret)
		return ret;

	// 记录transpack
	ret = doRecordTransPack(rPack,transpack,tDevice);
	if(ret)
	{		
		if(DB_REPEAT == ret)
		{
			writelog(LOG_ERR,"transpack exists[%s][%s]",transpack.packetid,transpack.reqid);
		}
		else
		{
			writelog(LOG_ERR,"doRecordTransPack  Err ret[%d][%s][%s]",ret,transpack.packetid,transpack.reqid);
			return ERRIF_SYSTEM;
		}
	}
	if(rPack->lvol8 % 100 != 0)
	{
		return ERRIF_POS_TRANSAMT;
	}
	ret = CardStatusInfoReadbyCardno(rPack->lvol4,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",rPack->lvol4);
		return ret;
	}
	ret = doCard(tCard);
	if(ret)
	{
		writelog(LOG_ERR,"doCard,ret=[%d]",ret);
		return ret;
	}
	strcpy(trans.cardaccno,tCard.accno);
	trans.feetype=tCard.feetype;
	trans.cardtype=tCard.cardtype;
	trans.cardphytype=tCard.cardphytype;
	trans.termid = tDevice.deviceid;
	des2src(trans.opercode,tOperator.opercode);
	/*
	T_t_cardtrans tCardTrans;
	memset(&tCardTrans,0,sizeof tCardTrans);
	ret = DB_t_cardtrans_read_by_cardno(tCard.cardno,&tCardTrans);
	if(ret)
	{
		if(DB_NOTFOUND!=ret)
		{
			writelog(LOG_ERR,"DB_t_cardtrans_read_by_cardno,cardno[%d] error",tCard.cardno);
			return ERRIF_SYSTEM;
		}
	}
	else
	{
		if( (tCardTrans.termid == trans.termid)&&
			(tCardTrans.transcode == trans.transcode)&&
			(tCardTrans.dpscnt == trans.dpscnt)&&
			(amtcmp(tCardTrans.cardbefbal,trans.cardbefbal)==0))
		{
			//交易已成功
			writelog(LOG_ERR,"last deposit write card failed,该卡上次写卡失败,需重写卡,cardno[%d]",tCardTrans.cardno);
			//return ERRIF_CARDBAL_EXCEPT; 
		}
	}
	*/
	ret = DB_t_transpack_read_lock_by_c0_and_packetid_and_reqid(transpack.packetid,transpack.reqid,&transpack);
	if(ret)
	{
		return ERRIF_SYSTEM;
	}
	if(transpack.status[0] == TRANSPACKSTATE_NODEAL)
	{	
		ret = doAccount(transdtl,tCard,rPack);
		if(ret)
		{
			return ret;
		}
		transpack.status[0] = TRANSPACKSTATE_SUCCESS;
		des2src(transpack.lastupdtime,trans.sysdatetime);
		transpack.termid = transdtl.termid;
		transpack.termseqno = transdtl.termseqno;
		des2src(transpack.accdate,transdtl.accdate);
		ret = DB_t_transpack_update_lock_by_c0(&transpack);
		if(ret)
		{
			return ERRIF_SYSTEM;
		}
		ret=SaveCardTransInfo();
		if(ret)
		{
			writelog(LOG_ERR,"SaveCardTransInfo ret=%d",ret);
			return ret;
		}
	}
	else if(TRANSPACKSTATE_CANCEL == transpack.status[0])
	{
		DB_t_transpack_free_lock_by_c0();
		return ERRIF_TRANS_REVERSED;
	}
	else
	{
		DB_t_transpack_free_lock_by_c0();
		T_t_cardtrans tCardTrans;
		memset(&tCardTrans,0,sizeof tCardTrans);
		ret = DB_t_cardtrans_read_by_cardno(tCard.cardno,&tCardTrans);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_cardtrans_read_by_cardno,cardno[%d] error",tCard.cardno);
			return ERRIF_SYSTEM;
		}
		if((tCardTrans.dpscnt+1 == trans.dpscnt)&&
			(amtcmp(tCardTrans.cardaftbal,trans.cardbefbal)==0))
		{
			//交易已成功
			writelog(LOG_ERR,"Deposit success,该充值写卡已成功,不需要重写,cardno[%d]",tCardTrans.cardno);
			return ERRIF_DATA;
		}
		if((tCardTrans.termid != trans.termid)||
		   (tCardTrans.transcode != trans.transcode)||
		   (tCardTrans.dpscnt != trans.dpscnt) || 
		   (amtcmp(tCardTrans.cardbefbal,trans.cardbefbal)!=0)||
		   (strncmp(tCardTrans.transdate,trans.transdate,8)!=0))
		{
			writelog(LOG_ERR,"Deposit repeat error,重复发送充值异常cardno[%d]",tCardTrans.cardno);
			return ERRIF_DATA;
		}
		transdtl.termid = tDevice.deviceid;
		transdtl.devseqno = rPack->lserial0;
		transdtl.cardno = tCard.cardno;
		
	}
	// 计算充值MAC
	ret = calcDepositKey(tCard,rPack,outPack->semail);
	if(ret)
	{
		writelog(LOG_ERR,"calc mac error,ret[%d]",ret);
		return ERRIF_CARD_STATUSEXCEPT;	
	}
	outPack->lvol4=transdtl.cardno;
	outPack->lvol7=D2I(transdtl.cardbefbal*100.0);
	outPack->lvol8=D2I(transdtl.amount*100.0);
	outPack->lvol10=D2I(transdtl.cardaftbal*100.0);
	des2src(outPack->sdate3,transdtl.accdate);
	des2src(outPack->stime3,transdtl.acctime);
	des2src(outPack->semp,transdtl.opercode);
	outPack->lwithdraw_flag=transdtl.termid;
	outPack->lserial0=transdtl.devseqno;
	des2src(outPack->scust_auth,transdtl.refno);	
    sprintf(transdtl.remark,"%s卡余额%.2lf元",ats.remark.c_str(),ats.trans.cardaftbal);
    des2src(outPack->vsmess,transdtl.remark);
	return 0;
}
int F950072(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	T_t_transpack transpack;
	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	
	memset(&transpack,0,sizeof transpack);
	

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LCERT_CODE,F_LWITHDRAW_FLAG,F_SPHONE3,F_LBANK_ACC_TYPE,F_SDATE3,F_STIME3,
		F_SEMAIL,F_LSERIAL0,F_SCUST_AUTH,F_LVOL4,F_LVOL7,F_LVOL8,F_LVOL10,0);

	transpack.funcno = iRequest;
	
	ret = do950072(transpack,rPack,outPack);
	if(ret)
	{
		db_rollback();
		outPack->lcert_code = ret;
	}
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}



