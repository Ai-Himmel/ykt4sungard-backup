/* --------------------------------------------
 * 程序名称: F847183.sqc
 * 创建日期: 2005-04-11
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:  交易冲正
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"

int F847183(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	char    	tx_date[8+1]="";              	//发生日期
	char    	tx_time[6+1]="";      		//发生时间
	int		card_no=0;                    	//卡号
	char    	device_id[8+1]="";            	//终端机ID
	int		serial_no=0;                  	//终端机流水号
	double 	dUniqno=0;
	T_t_tif_tradeserial		tTradeserial;	//卡操作流水表
	T_t_tif_rcvdtl		tRcvdtl;
	char sysdate[11]="";
	char systime[9]="";
       ST_CPACK aPack;
       ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	memset(&tRcvdtl,0,sizeof(tRcvdtl));
	memset(&tTradeserial,0,sizeof(tTradeserial));
	getsysdate(sysdate);
	getsystime(systime);
	des2src(tTradeserial.enteract_time,systime);

	des2src(tx_date,rPack->sbank_pwd);
	des2src(tx_time,rPack->sbank_code);
	card_no=rPack->lvol0;
	des2src(device_id,rPack->sbank_pwd2);
	serial_no=rPack->lvol1;
	trim(rPack->scust_limit);
	trim(rPack->scust_limit2);
	trim(rPack->semp_pwd);

	if(strlen(rPack->scust_limit)==0)
	{
		*pRetCode=E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	if(strlen(rPack->scust_limit2)==0)
	{
		*pRetCode=E_INPUT_AUTH_OPER_NULL;
		goto L_RETU;
	}
	if(strcmp(rPack->scust_limit,rPack->scust_limit2)==0)
	{
		writelog(LOG_ERR,"oper[%s]auth_oper[%s]",rPack->scust_limit,rPack->scust_limit2);
		*pRetCode=E_OPER_AND_AUTH_OPER_EQ;
		goto L_RETU;
	}
	ret=chk_oper_pwd(rPack->scust_limit2,rPack->semp_pwd);
	if(ret)
	{
		if(E_OPER_NOT_EXIST==ret)
			*pRetCode=E_AUTH_OPER_NOT_EXIST;
		else if(E_PASSWORD_WRONG==ret)
			*pRetCode=E_AUTH_OPER_PWD;
		else
			*pRetCode=ret;
		goto L_RETU;
	}
	 ret=DB_t_tif_rcvdtl_read_lock_by_c0_and_tx_date_and_tx_time_and_card_no_and_device_id_and_serial_no(tx_date,tx_time,card_no,device_id,serial_no,&tRcvdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			writelog(LOG_ERR,"tx_date[%s],tx_time[%s],card_no[%d],device_id[%s],serial_no[%d]",tx_date,tx_time,card_no,device_id,serial_no);
			*pRetCode=E_SERIALNO_NOT_EXIST;
		}
		else
		{
			writelog(LOG_ERR,"read_lock t_tif_rcvdtl err ret[%d]",ret);
			*pRetCode=E_DB_RCVDTL_R;
		}
		goto L_RETU;
	}
	if(tRcvdtl.status[0]=='4')
	{
		*pRetCode=E_TX_SERIAL_CZ;
		DB_t_tif_rcvdtl_free_lock_c0();
		goto L_RETU;
	}
	if(tRcvdtl.status[0]!='3')
	{
		*pRetCode=E_TX_SERIAL_CANNOT_CZ;
		DB_t_tif_rcvdtl_free_lock_c0();
		goto L_RETU;
	}
	if(tRcvdtl.amount<0)
	{
		*pRetCode=E_TX_SERIAL_CANNOT_CZ;
		DB_t_tif_rcvdtl_free_lock_c0();
		goto L_RETU;
	}
	tRcvdtl.status[0]='4';				//冲正
	des2src(tRcvdtl.oper_no,rPack->scust_limit);
	des2src(tRcvdtl.deal_date,sysdate);
	des2src(tRcvdtl.deal_time,systime);
	ret=DB_t_tif_rcvdtl_update_lock_by_c0(&tRcvdtl);
	if(ret)
	{
	        *pRetCode=E_DB_RCVDTL_U;
	        writelog(LOG_ERR,"DB_t_tif_rcvdtl_update_lock_by_c0[%d]",ret);
	        goto L_RETU;
	}
	DB_t_tif_rcvdtl_free_lock_c0();
	//赋值
	ret=getdata(&tTradeserial,&tRcvdtl);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	des2src(tTradeserial.operate_date,sysdate);
	des2src(tTradeserial.operate_time,systime);
	des2src(tTradeserial.collect_date,sysdate);
	des2src(tTradeserial.collect_time,systime);
	ret=GetLogicDate(tTradeserial.enteract_date);						//业务日期
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"GetLogicDate  err ret[%d]",ret);
		goto L_RETU;
	}
	des2src(tTradeserial.enteract_time,systime);
	tTradeserial.in_balance =rPack->damt1;
 	tTradeserial.trade_fee = -1 * D4U5(tRcvdtl.amount/100.0,2);		//本次消费金额
 	tTradeserial.boardfee = -1 * D4U5(tRcvdtl.manage_fee/100.0,2);	//本次消费管理费
    tTradeserial.out_balance=tTradeserial.in_balance-tTradeserial.trade_fee;
	tTradeserial.trade_count=rPack->lvol10;
	tTradeserial.maindevice_id=rPack->lvol6;
//	tTradeserial.sys_id=rPack->lvol6;
	des2src(tTradeserial.oper_code,rPack->scust_limit);
	tTradeserial.reviseserial_no=tTradeserial.other_seri_no;

	//取流水号,从帐处理
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqno);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		goto L_RETU;
	}
	tTradeserial.serial_no=(int)dUniqno;
		//######################################################
	//入账处理
	switch(tTradeserial.serial_type)
	{
		case 930031:
			// 交易冲正
			if(0==tRcvdtl.amount)
				break;
			tTradeserial.serial_type=TXCODE_TX_REVEAL;
			ret=process930031(&tTradeserial);
			if(ret)
			{	//业务处理失败处理
				*pRetCode=ret;
				goto L_RETU;
			}
			break;
		case 930034:
			// 充值冲正
			if(0==tRcvdtl.amount)
				break;
			tTradeserial.serial_type=TXCODE_TX_REVEAL;
			ret=process930034(&tTradeserial);
			if(ret)
			{	//业务处理失败处理
				*pRetCode=ret;
				goto L_RETU;
			}
			break;
		case 930036:
			// 搭伙费冲正
			if(0==tRcvdtl.amount)
				break;
			tTradeserial.serial_type=TXCODE_TX_REVEAL;
			ret=process930036(&tTradeserial);
			if(ret)
			{	//业务处理失败处理
				*pRetCode=ret;
				goto L_RETU;
			}
			break;
		default:
			*pRetCode=E_TXCODE_NOT_EXIST;	//交易码错误
			goto L_RETU;
	}
	//######################################################
	//添加交易流水
        tTradeserial.serial_state=SERISTAT_DEBT;
        ret = DB_t_tif_tradeserial_add(&tTradeserial);
        if (ret)
        {
                writelog(LOG_ERR,"DB_t_tif_tradeserial_add ret[%d]",ret);
                if(DB_REPEAT==ret)
                        *pRetCode= E_DB_TRADESERIAL_E;
                else
                        *pRetCode= E_DB_TRADESERIAL_I;
                goto L_RETU;
        }
	if(amtcmp(tTradeserial.out_balance,0)<0)
	{
		*pRetCode=E_ENTER_ACCOUNT;
		goto L_RETU;
	}
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_DAMT3,F_VSMESS,0);
	out_pack->lserial1=tTradeserial.serial_no;
	out_pack->damt2=tTradeserial.out_balance;
	out_pack->damt3=-tTradeserial.trade_fee;
	sprintf(out_pack->vsmess,"流水号:%d 冲正金额:%.2lf元 冲正前卡余额:%.2lf元 卡当前余额:%.2lf元",tTradeserial.serial_no,-tTradeserial.trade_fee,tTradeserial.in_balance,tTradeserial.out_balance);
	writelog(LOG_DEBUG,out_pack->vsmess);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
