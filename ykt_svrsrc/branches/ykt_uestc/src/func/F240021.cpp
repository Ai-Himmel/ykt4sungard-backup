/* --------------------------------------------
 * 程序名称: F240021.cpp
 * 创建日期: 2010-10-25
 * 程序作者:xlh
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
#include "dbfunc_foo.h"
//#include "busqc.h"
#include "bupub.h"
#include "svrlink.h"
#include "ext_consumer.h"


static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;

	IA->iMainDevId=p->maindevice_id;				//工作站标识
	IA->iDevId=p->device_id;						//设备ID
	IA->iSerialNo=p->serial_no;					//流水号
	IA->iTradeNo=p->serial_type;					//交易码
	strcpy(IA->sTxDate,p->operate_date);			//交易日期
	strcpy(IA->sTxTime,p->operate_time);			//交易时间
	strcpy(IA->sTxCollectDate,p->collect_date);		//采集日期
	strcpy(IA->sTxCollectTime,p->collect_time);		//采集时间
	strcpy(IA->sTxAccDate,p->enteract_date);		//记账日期
	strcpy(IA->sTxAccTime,p->enteract_time);		//记账时间
	strcpy(IA->sMdeOper,p->oper_code);			//操作员
	strcpy(IA->sChkOper,p->reserve_1);			//复核操作员

	IA->iUseCardFlag=IS_YES;						//卡交易
	IA->iTxCnt=p->trade_count;					//交易次数
	IA->dInCardBala=p->in_balance;				//入卡值
	IA->dOutCardBala=-1;							//出卡值
       IA->iCardNo=p->card_id;
	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;			//出卡值
	return 0;
}

static int doTrans(int tradecode,ST_PACK *rPack,T_t_tif_tradeserial   *tradeserial,char *errmsg)
{
	int ret = 0;
	int request_type = 2401;
	int drtp_branch  = 0;
	int base_funcno = 0;
	int bcc_timeout = 0;
	char dateserialno[50]="";
	char serialno[20]="";
	char bankcode[3] = "";
	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = request_type;
	
	SetHeadCol(&sPack,F_LCERT_CODE,F_SCUST_AUTH,F_LVOL0,F_LVOL1,F_LVOL6,F_SDATE0,F_STIME0,
		F_SHOLDER_AC_NO,F_SPHONE,F_SCUST_LIMIT,F_SCUST_LIMIT2,F_SCUST_AUTH,F_SPHONE3,F_SCUST_AUTH2,F_DAMT0,F_SBANK_PWD,
		F_VSVARSTR0,F_VSVARSTR1,F_SORDER2,0);      

	T_t_bankcard bankcard;
	memset(&bankcard,0,sizeof bankcard);
	ret = DB_t_bankcard_read_by_custid_and_bankcardno(tradeserial->customer_id,tradeserial->b_act_id, &bankcard);
	if(ret)
	{
		return E_DB_BANKCARD_R;
	}
	des2src(bankcode,bankcard.bankcode);

	T_t_cfgbank cfgbank;
	memset(&cfgbank,0,sizeof cfgbank);
	T_t_refno  refno;
	memset(&refno,0,sizeof refno);
	ret = DB_t_cfgbank_read_by_bankcode(bankcode,&cfgbank);
	if(ret)
	{
		return E_DB_CFGBANK_R;
	}
       des2src(dateserialno,rPack->sname2);
       ret=DB_t_refno_read_by_dateserialno(dateserialno,&refno);
	T_t_cif_customer customer;
	memset(&customer,0,sizeof customer);
	ret = DB_t_cif_customer_read_by_cut_id(tradeserial->customer_id, &customer);
	if(ret)
	{
		return E_DB_CUSTOMER_R;
	}
	
	drtp_branch = cfgbank.bccdrtpno;								// drtp 编号
	base_funcno = cfgbank.bccfuncno;								// 前置主功能号
	bcc_timeout = cfgbank.bcctimeout;								// 前置超时时间
	if(bcc_timeout<10)
	   bcc_timeout=10;
	if(cfgbank.banktimeout<bcc_timeout)
		cfgbank.banktimeout = bcc_timeout-2;					//保证银行超时时间不能大于bcc等待时间
	sPack.pack.lcert_code = tradecode;							// 交易码
	des2src(sPack.pack.scust_auth,cfgbank.bankip);					// 银行ip
	sPack.pack.lvol0 = cfgbank.bankport;							// 银行端口
	sPack.pack.lvol1 = cfgbank.banktimeout;					// 银行超时时间

	des2src(sPack.pack.sdate0,tradeserial->enteract_date);					// 交易日期
	des2src(sPack.pack.stime0,tradeserial->enteract_time);					// 交易时间
	des2src(sPack.pack.sholder_ac_no,refno.refno);				// 一卡通交易参考号
	des2src(sPack.pack.sphone,customer.stuemp_no);				// 学工号
	des2src(sPack.pack.scust_limit,customer.cut_name);				// 姓名
	des2src(sPack.pack.scust_auth2,customer.man_id);					// 身份证号
	des2src(sPack.pack.scust_limit2,tradeserial->b_act_id);				// 银行卡号
	sPack.pack.damt0 = tradeserial->trade_fee;							// 交易金额
	des2src(sPack.pack.sphone3,rPack->sphone3);				//银行卡密码，ansi加密处理过
	des2src(sPack.pack.vsvarstr0, rPack->vsvarstr0);				//二磁道数据
	des2src(sPack.pack.vsvarstr1, rPack->vsvarstr1);				//三磁道数据
	des2src(sPack.pack.sorder2,tradeserial->devphy999_id);					//设备物理ID
	//writelog(LOG_ERR,"vsvarstr0=[%s] ",rPack->vsvarstr0);
	sPack.pack.lvol6 = tradeserial->sys_id;							// 终端号
	
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
	des2src(tradeserial->reserve_2,aPack.pack.sphone);				// 银行端流水号
	return 0;
}


int F240021(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int ret1 = 0;
	int reverse_flag = 0;
	char buffer[16]="";
     	char sMaxCardBalance[20]="";
	char sMsg[300]="";
	char sDebugMsg[1024]="";
	char logicdate[11]="";
	double dMaxCardBalance=0;
       double trans_amt=0.0;
	T_t_aif_account	tAccount;		//帐户表
	T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	T_t_pif_card	card;
	T_t_refno refno;
	T_t_cif_customer	tCustomer;
	InAcc	IA;
	T_t_pif_spefee 	tSpeFee;
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&card,0,sizeof(card));
	memset(&refno,0,sizeof(refno));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&IA,0,sizeof(IA));

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_LVOL2,F_SDATE0,0);
       ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	tradeserial.sys_id=rPack->lcert_code;

	//判断是否处于日终结算状态
 	ret=GetParameter(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		
		writelog(LOG_ERR,"GetParameter error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		
		writelog(LOG_ERR,"System is balance now!");
		return E_TRANS_BANK_SERVICE_NOEXIT;
	}

	tradeserial.card_id=rPack->lvol0;
	ret=DB_t_pif_card_read_by_card_id(tradeserial.card_id,&card);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		return E_TRANS_SCHACC_NOEXIT;
	}
	
	if(strncmp(card.state_id,CARDSTAT_LOGOUT,4)==0)
	{
		
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return E_TRANS_SCHACC_DESTORY;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}

		if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_WFAIL])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_WFAIL;
	}

	//转账不允许转小数金额
	if((rPack->lvol5)%100>0)
	{
		writelog(LOG_ERR,"Trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}

	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(rPack->lvol7, &tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d],serial_no=[%d]",ret,rPack->lvol7);
		return E_DB_TRADESERIAL_R;
	}
	//判断转帐金额是否超出钱包最大限额
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card.card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card.card_id);
		if(DB_NOTFOUND==ret)
		{
			return E_TRANS_SCHACC_NOEXIT;
		}
		else
		{
			return E_TRANS_UNKNOW_ERROR;
			
		}
	}
	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter GLOBE_MAXCARDBALANCE error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
		
	}
	dMaxCardBalance=atof(sMaxCardBalance);

	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}

	//读取客户收费类别字段
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(card.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",card.cosumer_id);
		if(DB_NOTFOUND==ret)
		{
			return E_TRANS_UNKNOW_ERROR;
			
		}
		else
		{
			return E_TRANS_UNKNOW_ERROR;
			
		}
	}
	if(0==tCustomer.fee_type)
	{
		ret=DB_t_pif_spefee_read_by_dept_code_and_cut_type(tCustomer.classdept_no, tCustomer.cut_type,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.fee_type=tCustomer.cut_type;
			}
			else
			{
				DB_t_cif_customer_free_lock_cur();
				writelog(LOG_ERR,"DB_t_pif_spefee_read_by_dept_code_and_cut_type error,errcode=[%d]",ret);
				return E_TRANS_UNKNOW_ERROR;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		DB_t_cif_customer_free_lock_cur();
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
		//ERRTIP("交易参考号MAC校验错误");
		return E_COMMON_ERR;
	}
	ret = doTrans(TRADE_TRANS,rPack,&tradeserial,szMsg);
	if(ret)
	{
		if(ret != E_BCC_NETWORK)
		{
			tradeserial.ecode= ret;
			tradeserial.serial_state = SERISTAT_DEBTEXC;
			des2src(tradeserial.reserve_1,szMsg);
			if(DB_t_tif_tradeserial_update_by_serial_no(tradeserial.serial_no,&tradeserial))
				return E_DB_TRADESERIAL_U;
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
	//填写入账结构,问问闻剑
	des2src(IA.sArrInActno[0],tAccount.account_id);			//贷方帐户,持卡人账户
	des2src(IA.sArrInActno[2],rPack->sstation0);				//借方帐号，由前置机上传
	IA.iCardNo=card.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process err,errcode[%d]",ret);
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		goto L_RET;
	}
	sprintf(sDebugMsg,"流水号:%d ",IA.iSerialNo);
	for(int i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		switch(IA.iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial.deposit_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_BANK_PRE_TOLL_BOARD:
				tradeserial.boardfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
				tradeserial.in_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_BANK_TRANSFER:
				trans_amt=IA.dArrOutAmt[i];
				break;
			default:
				break;
		}
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(sDebugMsg,sMsg);
		}
	}
	//结束填充流水数据
	tradeserial.serial_state=SERISTAT_DEBT;
	ret=DB_t_tif_tradeserial_update_lock_by_cur(&tradeserial);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"DB_t_tif_tradeserial_update_lock_by_cur error,error code=[%d]",ret);
		goto L_RET;
	}


	sprintf(sMsg,"充值前卡余额:%.2lf 转帐后卡余额:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
    	strcat(sDebugMsg,sMsg);
	writelog(LOG_DEBUG,sDebugMsg);

	if(tradeserial.serial_state != SERISTAT_NODEBT)
	{
		if(tradeserial.serial_state== SERISTAT_DEBT)					// 已经成功了
		{
			out_pack->damt0=tradeserial.out_balance;
			out_pack->damt1=tradeserial.trade_fee;
			out_pack->damt2=0;	//管理费
			out_pack->lvol2=D2I(tradeserial.out_balance *100);
			writelog(LOG_DEBUG,"已经成功返回了");
			PutRow(handle,out_pack,pRetCode,szMsg);
			return 0;
		}
		else
		{
			//ERRTIP("流水处理失败");
			return E_COMMON_ERR;
		}
	}
	

	
L_RET:	
	if(reverse_flag)
	{
		tradeserial.serial_state = SERISTAT_DEBTEXC;
		ret1 = doTrans(TRADE_REVERSE, rPack,&tradeserial, szMsg);
		if(ret1)												// 冲正也失败了，对账解决不平
		{
			tradeserial.ecode= ret1;
			des2src(tradeserial.reserve_1,szMsg);
			strcat(tradeserial.reserve_1," 冲正失败");
			if(DB_t_tif_tradeserial_update_by_serial_no(tradeserial.serial_no,&tradeserial))
				return E_DB_TRADESERIAL_U;
			else
			{			
				db_commit();
				return ret1;
			}
		}
		///////////////冲正成功了，提示刚才要冲正的原因
		tradeserial.ecode= ret;
		if(DB_t_tif_tradeserial_update_by_serial_no(tradeserial.serial_no,&tradeserial))
			return E_DB_TRADESERIAL_U;
		else
		{			
			db_commit();
			return ret;
		}
	}	
	out_pack->damt0=tradeserial.out_balance;
	out_pack->damt1=tradeserial.trade_fee;
	out_pack->damt2=0;	//管理费
	out_pack->lvol2=D2I(tradeserial.out_balance*100);	
	PutRow(handle,out_pack,pRetCode,szMsg);
       return 0;

}

