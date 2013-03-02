/* --------------------------------------------
 * 程序名称: F847181.sqc
 * 创建日期: 2005-04-11
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:  终端机未入账流水手工入账
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

int F847181(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	char    	tx_date[8+1]="";              	//发生日期
	char    	tx_time[6+1]="";      		//发生时间
	int		card_no=0;                    	//卡号
	char    	device_id[8+1]="";            	//终端机ID
	int		serial_no=0;                  	//终端机流水号
	int 		shop_id=0;
	double 	dUniqno=0;
	T_t_tif_tradeserial		tTradeserial;	//卡操作流水表
	T_t_tif_rcvdtl		tRcvdtl;
	char sysdate[11]="";
	char systime[9]="";

	memset(&tRcvdtl,0,sizeof(tRcvdtl));
	memset(&tTradeserial,0,sizeof(tTradeserial));
	getsysdate(sysdate);
	getsystime(systime);
	des2src(tx_date,rPack->sbank_pwd);
	des2src(tx_time,rPack->sbank_code);
	card_no=rPack->lvol0;
	des2src(device_id,rPack->sbank_pwd2);
	serial_no=rPack->lvol1;
	shop_id=rPack->lvol12;
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
			*pRetCode=E_DB_RCVDTL_R;
			writelog(LOG_ERR,"read_lock t_tif_rcvdtl err ret[%d]",ret);
		}
		goto L_RETU;
	}
	if(tRcvdtl.status[0]!='2')
	{
		*pRetCode=E_TX_CANNOT_DEAL;
		DB_t_tif_rcvdtl_free_lock_c0();
		goto L_RETU;
	}
	des2src(tRcvdtl.oper_no,rPack->sdate1);
	des2src(tRcvdtl.deal_date,sysdate);
	des2src(tRcvdtl.deal_time,systime);
      	tRcvdtl.status[0]='3';          				//1-未处理2-失败3-成功
	ret=DB_t_tif_rcvdtl_update_lock_by_c0(&tRcvdtl);
	if(ret)
	{
	        *pRetCode=E_DB_RCVDTL_U;
	        writelog(LOG_ERR,"DB_t_tif_rcvdtl_update_lock_by_c1[%d]",ret);
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
	ret=GetLogicDate(tTradeserial.enteract_date);						//业务日期
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"GetLogicDate  err ret[%d]",ret);
		goto L_RETU;
	}
	des2src(tTradeserial.enteract_time,systime);
	tTradeserial.maindevice_id=rPack->lvol11;
	des2src(tTradeserial.oper_code,rPack->sdate1);
	//取流水号,从帐处理
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqno);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		goto L_RETU;
	}
	tTradeserial.serial_no=D2I(dUniqno);
		//######################################################
	//入账处理
	switch(tTradeserial.serial_type)
	{
		case 930031:
			if(0==tRcvdtl.amount)
				break;
			tTradeserial.comu_ver=shop_id;
			ret=process930031(&tTradeserial);
			if(ret)
			{
				*pRetCode=ret;
				writelog(LOG_ERR,"process930031 err[%d]",ret);
				goto L_RETU;
			}
			break;
		default:
			*pRetCode=E_TXCODE_NOT_EXIST;	//交易码错误
			goto L_RETU;
	}
		//######################################################
	//业务处理成功处理
	tTradeserial.serial_state=SERISTAT_DEBT;			//已入帐
	//添加交易流水
	ret = DB_t_tif_tradeserial_add(&tTradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
