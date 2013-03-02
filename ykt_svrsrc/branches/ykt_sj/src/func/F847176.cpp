/* --------------------------------------------
 * 程序名称: F847176.c
 * 创建日期: 2010-04-08
 * 程序作者: xlh
 * 版本信息: 1.0.0.0
 * 程序功能: 过期流水手工借-手工贷
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"

static int getacc(char *divphi,T_t_aif_account *acc)
{  
   // T_t_aif_account accrt=&acc;
    int ret=0;
	T_t_pif_device device;
	memset(&device,0,sizeof(device));
	T_t_cif_shop_pos shoppos;
	memset(&shoppos,0,sizeof(shoppos));
	T_t_cif_shop shop;
	memset(&shop,0,sizeof(shop));
	T_t_aif_account accrt;
	memset(&accrt,0,sizeof(accrt));
	ret=DB_t_pif_device_read_by_devphy999_id(divphi,&device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_by_devphy999_id err [%s]",divphi);
		return ret;
	}
	writelog(LOG_ERR,"shipid ret[%d]",device.device_id);
    ret=DB_t_cif_shop_pos_read_by_device_id(device.device_id,&shoppos);
	if (ret)
	{
		writelog(LOG_ERR," DB_t_cif_shop_pos_read_by_device_id err [%d]",device.device_id);
		return ret;
	 }
	ret=DB_t_cif_shop_read_by_shop_id(shoppos.shop_id,&shop);
	if (ret)
	{
		writelog(LOG_ERR," DB_t_cif_shop_read_by_shop_id err [%d]",shoppos.shop_id);
		return ret;
	 }
	ret = DB_t_aif_account_read_by_customer_id_and_act_type(
		shop.cut_id,ACCTYPE_SHOPMAIN,&accrt);
	if (ret)
	{
		writelog(LOG_ERR," DB_t_aif_account_read_by_customer_id_and_act_type err [%d]",shop.cut_id);
		return ret;
	 }
     strcpy(acc->account_id,accrt.account_id);
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
	strcpy(IA->sChkOper,p->oper_code);			//复核操作员

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//无卡交易
	IA->iTxCnt=0;								//交易次数
	IA->dInCardBala=0;							//入卡值
	IA->dOutCardBala=0;							//出卡值

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;			//出卡值
	if(amtcmp(p->out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}
	return 0;
}

int F847176(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	char logicdate[11]="";										//业务日期
	char sysdate[11]="";
	char systime[9]="";
	InAcc	IA;
	char  ia_buf[1024]="";
	char sbank_acc[41]="";
	char sbank_acc2[41]="";
	double dUniqno = 0;
	char sMsg[256]="";
	char    tx_date[8+1]="";              	//发生日期
	char    tx_time[6+1]="";      		//发生时间
	int		card_no=0;                    	//卡号
	char    deviceph_id[8+1]="";            	//终端机ID
	int		serial_no=0;
	T_t_tif_tradeserial tradeserial;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
    T_t_tif_rcvdtl		tRcvdtl;
	memset(&tRcvdtl,0,sizeof(tRcvdtl));
	memset(&tradeserial,0,sizeof(tradeserial));
	T_t_aif_account account;
	memset(&account,0,sizeof(account));
	memset(&IA,0,sizeof(IA));
	T_t_pif_device device;
	memset(&device,0,sizeof(device));
	IA.pVoidPointer=ia_buf;
	ResetNormalCPack(&aPack,0,1);

/*	if(amtcmp(rPack->damt0,0)==0)
	{
		*pRetCode=E_INPUT_AMT_NULL;
		goto L_RETU;
	}
	*/
	if(strlen(rPack->semp)==0)
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}
	des2src(tx_time,rPack->sbank_pwd);
	des2src(tx_date,rPack->sdate0);
	card_no=rPack->lvol0;
	des2src(deviceph_id,rPack->sbank_pwd2);
	serial_no=rPack->lvol1;
	writelog(LOG_ERR,"tx_date[%s],tx_time[%s],card_no[%d],device_id[%s],serial_no[%d]",tx_date,tx_time,card_no,deviceph_id,serial_no);
	ret=DB_t_tif_rcvdtl_read_lock_by_c0_and_tx_date_and_tx_time_and_card_no_and_device_id_and_serial_no(tx_date,tx_time,card_no,deviceph_id,serial_no,&tRcvdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			writelog(LOG_ERR,"tx_date[%s],tx_time[%s],card_no[%d],device_id[%s],serial_no[%d]",tx_date,tx_time,card_no,deviceph_id,serial_no);
			*pRetCode=E_SERIALNO_NOT_EXIST;
		}
		else
		{
			*pRetCode=E_DB_RCVDTL_R;
			writelog(LOG_ERR,"read_lock t_tif_rcvdtl err ret[%d]",ret);
		}
		goto L_RETU;
	}
	if(tRcvdtl.status[0]!='9')
	{
		*pRetCode=E_TX_CANNOT_DEAL;
		DB_t_tif_rcvdtl_free_lock_c0();
		goto L_RETU;
	}
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	tradeserial.trade_fee = tRcvdtl.amount;						//发生金额
	ret=DB_t_pif_device_read_by_devphy999_id(deviceph_id,&device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_by_devphy999_id err [%s]",deviceph_id);
		return ret;
	}
	ret=getacc("00000000",&account);
	if (ret)
	  {
		writelog(LOG_ERR," 获得帐号失败 err [%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	  }
	strcpy(sbank_acc,account.account_id);
	//memset(account,0,sizeof(account));
	ret=getacc(deviceph_id,&account);
	if (ret)
		{
		writelog(LOG_ERR," 获得帐号失败 err [%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	  }
	strcpy(sbank_acc2,account.account_id);
	writelog(LOG_ERR," sbank_acc[%s],sbank_acc2 [%s]",sbank_acc,sbank_acc2);
	tradeserial.device_id=device.device_id;
	des2src(tradeserial.out_account_id,sbank_acc);//出账
	des2src(tradeserial.in_account_id,sbank_acc2);//入账
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  		//获得最大流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no = D2I(dUniqno);							//流水号
	tradeserial.other_seri_no = 0;								//上传端流水号
	tradeserial.serial_type  = TXCODE_CARD_DBCR;				//交易码
	tradeserial.serial_state = SERISTAT_DEBT;						//流水状态
	des2src(tradeserial.operate_date,sysdate);					//发生日期
	des2src(tradeserial.operate_time,systime);					//发生时间
	des2src(tradeserial.collect_date,sysdate);						//采集日期
	des2src(tradeserial.collect_time,systime);						//采集时间
	des2src(tradeserial.enteract_date,logicdate);					//处理日期
	des2src(tradeserial.enteract_time,systime);					//处理时间
	tradeserial.maindevice_id = rPack->lvol6;						//上传工作站标识
	tradeserial.in_balance=rPack->damt0;						//入卡值
	tradeserial.trade_count=0;									//交易次数
	des2src(tradeserial.oper_code,rPack->semp);			//操作员代码
	tradeserial.sys_id = 0;										//外部系统标识
	des2src(tradeserial.reserve_1,"过期流水处理");
	IA.iCardNo=0;
	IA.iFeeType=1;
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	des2src(IA.sArrInActno[0],tradeserial.out_account_id);				//借方帐号
	des2src(IA.sArrInActno[1],tradeserial.in_account_id);				//贷方帐号
	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[1]=rPack->lvol1;
	IA.iArrInFeeSwitch[2]=rPack->lvol2;
	IA.iArrInFeeSwitch[3]=rPack->lvol3;
	IA.iArrInFeeSwitch[4]=rPack->lvol4;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	writelog(LOG_ERR," 开始入账 err [%d]",ret);
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(out_pack->vsmess,"流水号:%d ",IA.iSerialNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	strcat(out_pack->vsmess,(char*)IA.pVoidPointer);
	writelog(LOG_DEBUG,out_pack->vsmess);
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_DAMT3,F_DAMT4,F_VSMESS,0);
	out_pack->lserial1=tradeserial.serial_no;			//流水号
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	des2src(tRcvdtl.oper_no,rPack->semp);
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
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

