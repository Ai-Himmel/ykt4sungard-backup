/* --------------------------------------------
 * 创建日期: 2008 8 21
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户销户
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

static int doAccount(char *cardaccno)
{
	int ret=0;
	T_t_aif_account tAccount;

	memset(&tAccount,0,sizeof(tAccount));

	ret=DB_t_aif_account_read_lock_by_cur_and_account_id(cardaccno,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_R;
	}
	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
	{
		DB_t_aif_account_free_lock_cur();
		return E_EACCNO_LOGOUT;
	}
	if(amtcmp(tAccount.cur_freebala,0)!=0)
	{
		writelog(LOG_ERR,"balance[%d]",tAccount.cur_freebala);
		DB_t_aif_account_free_lock_cur();
		return E_EACC_BALANCE_NOZERO;
	}
	tAccount.current_state=ACCOUNTSTAT_LOGOUT;
	getsysdate(tAccount.close_date);
	getsystime(tAccount.close_time);
	ret=DB_t_aif_account_update_lock_by_cur(&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else 
			return E_DB_ACCOUNT_U;

	}
	return 0;
}
static int doCustomer(int custid,T_t_cif_customer& tCustomer)
{
	int ret=0;
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(custid,&tCustomer);
	if(ret)
	{		
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.cut_state!=CUSTSTAT_REGIST)
		return E_CUSTOMER_LOGOUT;
	tCustomer.eaccflag[0]='0';
	ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_U;
	}
	return 0;
}
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

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//联机交易
	IA->iTxCnt=0;					//交易次数
	IA->dInCardBala=0;				//入卡值
	IA->dOutCardBala=0;							//出卡值

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
//	p->out_balance=IA->dOutCardBala;			//出卡值
	return 0;
}


int F846332(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char logicdate[9]="";
	char sysdate[9]="";
	char systime[7]="";
	char accno[21]="";
	double dUniqno = 0;
	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
		
	SetCol(handle,0);

	InAcc	IA;
	memset(&IA,0,sizeof(IA));
	des2src(accno,rPack->sbank_acc);	//电子帐户
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;
	//去帐户信息
	T_t_aif_account tAccount;	
	memset(&tAccount,0,sizeof(tAccount));
	ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
	{
		return E_EACCNO_LOGOUT;
	}	
	char seedkey[33]="";
	char inpwd_crypt[65]="";
	char inpwd_plain[65]="";
	char dbpwd_plain[65]="";
	des2src(inpwd_crypt,rPack->snote2);
	if(!strlen(inpwd_crypt))
		return E_INPUTNULL_PWD;
	ret=GetParameter(2006,seedkey);
	if(ret)
		return ret;
	ret=decrypt_elec_card_pwd(0,seedkey,inpwd_crypt,inpwd_plain);
	if(ret)
		return	E_EACCPWD;
	ret=decrypt_elec_card_pwd(0,seedkey,tAccount.password,dbpwd_plain);
	if(ret)
		return E_PWD_DECRYPT;
	if(strcmp(inpwd_plain,dbpwd_plain)!=0)
		return E_EACCPWD;
	//检查客户
	T_t_cif_customer tCustomer;
	memset(&tCustomer,0,sizeof(tCustomer));
	ret=doCustomer(tAccount.customer_id,tCustomer);
	if(ret)
		return ret;
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);		//业务日期
	if(ret)
		return ret;
	
	//生成流水
	T_t_tif_tradeserial  tradeserial;
	memset(&tradeserial,0,sizeof(tradeserial));
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  						//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"ret [%d]",ret);
		return ret;
	}
	tradeserial.serial_no = D2I(dUniqno);											//流水号
	tradeserial.other_seri_no = 0;														//上传端流水号
	tradeserial.serial_type = TXCODE_EACC_CLOSE;											//交易代码；
	tradeserial.serial_state = SERISTAT_DEBT;												//流水状态
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	des2src(tradeserial.oper_code, rPack->semp);										//操作员代码
	tradeserial.customer_id=tAccount.customer_id;											//客户号

	tradeserial.trade_fee=tAccount.cur_bala;
	//	插入交易流水表
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return	E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	} 	
	des2src(IA.sArrInActno[5],tAccount.account_id);							//帐户
	IA.iCardNo=0;
	IA.iFeeType=0;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}
	//注销帐户
	ret=doAccount(accno);
	if(ret)
		return ret;
	SetCol(handle,F_LSERIAL1,F_VSMESS,0);	
	
	outPack->lserial1=tradeserial.serial_no;
	sprintf(outPack->vsmess,"账户[%s]销户成功,退帐户余额%.2lf",tAccount.account_id,tAccount.cur_bala);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

