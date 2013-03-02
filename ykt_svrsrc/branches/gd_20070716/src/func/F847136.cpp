/* --------------------------------------------
 * 程序名称: F847136.sqc
 * 创建日期: 2007-8-8
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 回收 商户卡
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_
 #include <string.h>
 #include <stdio.h>
 #include "pubfunc.h"
 #include "pubdb.h"
 #include "pubdef.h"
 #include "errdef.h"
 #include "dbfunc.h"
 #include "fdsqc.h"
 #include "dbfunc_foo.h"

int F847136(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret = 0;
	char logicdate[11]="";								//业务日期
	char sysdate[11]="";
	char systime[9]="";
	
	int card_id=0;
	char cardphyid[12]="";
	
	T_t_pif_card tCard;
	T_t_aif_account  tAccount;
	T_t_tif_tradeserial  tradeserial;
	T_t_cif_customer   tCustomer;
	double dUniqNo = 0;
	InAcc	IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&IA,0,sizeof(IA));
	memset(&tCard, 0, sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,F_LSERIAL1,0);
	card_id = rPack->lvol2;									//客户类别
	des2src(cardphyid,rPack->scust_auth);
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	if(card_id<1)
	{
		*pRetCode=E_CARDNO_NOT_EXIST;
		goto L_RETU;
	}
	//检查客户信息，判断是否可以发行卡
	//注销卡
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	if('0'==tCard.state_id[CARDSTAT_TYPE_LOST])
	{
		//检查物理卡号是否一致
		trim(cardphyid);
		trim(tCard.physical_no);
		if(strcmp(tCard.physical_no,cardphyid)!=0)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",tCard.physical_no,cardphyid);
			*pRetCode= E_CARD_PHYNO_DIFFER;
			goto L_RETU;
		}
	}
	des2src(tCard.state_id,CARDSTAT_LOGOUT);		//注销
	des2src(tCard.end_time,sysdate);			//注销日期
	ret=DB_t_pif_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",tCard.card_id);
		*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_pif_card_free_lock_by_cur();

	//	更新账户信息表，改写卡号
	ret=DB_t_aif_account_read_by_customer_id_and_act_type(tCard.cosumer_id,ACCTYPE_SHOPMAIN,&tAccount);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_customer_id_and_act_type err,errcod=[%d]",ret);
		*pRetCode = E_DB_ACCOUNT_R;
		goto L_RETU;
	}

	tAccount.card_id=0;
	tAccount.card_type=0;
	
	ret=DB_t_aif_account_update_by_account_id(tAccount.account_id,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_update_by_account_id err,errcod=[%d]",ret);
		*pRetCode = E_DB_ACCOUNT_U;
		goto L_RETU;
	}

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqNo);  						//获得最大流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}

	tradeserial.serial_no = D2I(dUniqNo);											//流水号
	tradeserial.other_seri_no = 0;														//上传端流水号
	tradeserial.serial_state = SERISTAT_DEBT;												//流水状态
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间

	tradeserial.maindevice_id = rPack->lvol6;												//上传工作站标识
	tradeserial.device_id = rPack->lvol7;													//采集设备标识
	tradeserial.card_id = tCard.card_id;													//卡号
	des2src(tradeserial.showid,tCard.showid);												//显示卡号
	tradeserial.purse_id = PURSE_NO_ONE;												//钱包号
	tradeserial.customer_id = tCard.cosumer_id;													//客户标识

	des2src(tradeserial.oper_code , rPack->scust_limit);			//操作员代码
	tradeserial.sys_id = 0;																//外部系统标识
	tradeserial.trade_count=0;														//当前卡交易次数
	// 插入交易流水表
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
	out_pack->lserial1=tradeserial.serial_no;						//流水号
	sprintf(out_pack->vsmess,"商户号%d卡号%d回收成功",rPack->lvol0,card_id);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

