/* --------------------------------------------
 * 程序名称: F847119.sqc
 * 创建日期: Sep 29 2004
 * 程序作者: 耿刚
 * 版本信息: 1.0.0.0
 * 程序功能: 补写卡信息
 * --------------------------------------------
 * 修改日期: 2004-11-29
 * 修改人员: 闻剑
 * 修改描述: 修改整个业务逻辑
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "fdsqc.h"
#define 	TYPE_CUR	1
#define 	TYPE_HIS	2

int F847119(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char operate_date[11]="";
	char sSerialno[20]="";
	char physical_no[41]="";
	char old_physical_no[41]="";
	int 	iSerialno=0;
	int 	card_id=0;
	int 	serial_type=0;
	int   flag=0;
	double dSerialno=0;
	double  dAmt=0;
	char h_password[7] = "";							//卡密码
	char seed_key[17] = "";							//种子密钥
	T_t_pif_card tCard;
	T_t_cif_customer  tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_tif_tradeserial tradeserial;
	T_t_tif_tradeserial old_tradeserial;
	T_t_tif_tradeserial_his tradeserialhis;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCard,0,sizeof(tCard));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&old_tradeserial,0,sizeof(old_tradeserial));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tradeserialhis,0,sizeof(tradeserialhis));
	memcpy(seed_key,STATIC_SEED_KEY,sizeof(seed_key));		//读种子密钥

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,
				F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCUST_AUTH2,
				F_SDATE0,F_SNAME,F_SNAME2,
				F_SOPEN_EMP,F_SSTATUS0,
				F_DAMT2,F_LSERIAL1,F_VSMESS,0);
	des2src(physical_no,rPack->sbank_acc);
	card_id=rPack->lvol0;

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//判断卡状态是否为写卡未成功状态
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if(STATE_FALSE==tCard.state_id[CARDSTAT_TYPE_WFAIL])
	{
		*pRetCode=E_CARDSTATE_NOTWRITEFAIL;
		goto L_RETU;
	}
	ret=GetXmlValue(sSerialno, sizeof(sSerialno), XML_KEY_SERIALNO, tCard.comments);
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=ret;
		goto L_RETU;
	}
	//修改账号表中的卡状态
	//根据流水号得到补卡的出卡值
	ret=GetXmlValue(operate_date, sizeof(operate_date), XML_KEY_OPERATEDATE, tCard.comments);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	iSerialno=atoi(sSerialno);
	if(strncmp(sysdate,operate_date,8)==0)
	{
		ret=DB_t_tif_tradeserial_read_by_serial_no(iSerialno,&old_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"Serialno[%d]",iSerialno);
			if(DB_NOTFOUND==ret)
				*pRetCode=E_SERIALNO_NOT_EXIST;
			else
				*pRetCode=E_DB_TRADESERIAL_R;
			goto L_RETU;
		}
		if(card_id!=old_tradeserial.card_id)
		{
			writelog(LOG_ERR,"input card_id [%d],tradeserial card_id[%d]",card_id,old_tradeserial.card_id);
			*pRetCode=E_CARDNO_SERIAL_NE;
			goto L_RETU;
		}
		serial_type=old_tradeserial.serial_type;
		flag=TYPE_CUR;
	}
	else
	{
		ret=DB_t_tif_tradeserial_his_read_by_enteract_date_and_serial_no(operate_date,iSerialno,&tradeserialhis);
		if(ret)
		{
			writelog(LOG_ERR,"operate_date[%s]Serialno[%d]",operate_date,iSerialno);
			if(DB_NOTFOUND==ret)
				*pRetCode=E_SERIALNO_NOT_EXIST;
			else
				*pRetCode=E_DB_TRADESERIAL_R;
			goto L_RETU;
		}
		if(card_id!=tradeserialhis.card_id)
		{
			writelog(LOG_ERR,"input card_id [%d],tradeserial card_id[%d]",card_id,tradeserialhis.card_id);
			*pRetCode=E_CARDNO_SERIAL_NE;
			goto L_RETU;
		}
		serial_type=tradeserialhis.serial_type;
		flag=TYPE_HIS;
	}
	des2src(old_physical_no,tCard.physical_no);
	trim(physical_no);
	trim(old_physical_no);
	switch(serial_type)
	{
		//发行正式卡
		case  847101:
		//补办正式卡
		case  847104:
		//发行过渡临时卡
		case 847116:
		//发行非记名临时卡
		case 847124:
		case 847125:
		case 847126:
			if(strcmp(old_physical_no,physical_no)!=0)
			{
				ret=IsExistCardByPhyCardNo(physical_no);
				if(ret)
				{
					*pRetCode = ret;
					goto L_RETU;
				}
				//修改卡标志，置为正常状态
				ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &tCard);
				if(ret)
				{
					writelog(LOG_ERR,"card_id[%d]",card_id);
					if(DB_NOTFOUND==ret)
						*pRetCode= E_CARDNO_NOT_EXIST;
					else
						*pRetCode= E_DB_CARD_R;
					goto L_RETU;
				}
				des2src(tCard.physical_no,physical_no);			//物理卡号
				ret=DB_t_pif_card_update_lock_by_cur(&tCard);
				if(ret)
				{
					writelog(LOG_ERR,"card_id[%d]",card_id);
					if(DB_NOTFOUND==ret)
						*pRetCode= E_CARDNO_NOT_EXIST;
					else
						*pRetCode= E_DB_CARD_U;
					goto L_RETU;
				}
				DB_t_pif_card_free_lock_by_cur();
				// add by 汤成 2005-8-10
				// 增加向名单表写入记录
				switch(serial_type)
				{
				//补办正式卡
				case  847104:
				//发行过渡临时卡
				case 847116:
				// 记名临时卡
				//case 847124:
				// VIP 卡
				case 847126:
					ret = InsertToBlkList(tCard.card_id,CHCARD_BLACKLIST);
					if(ret)
					{
						*pRetCode = ret;
						goto L_RETU;
					}
					break;
				default:
					break;
				}
			}
			tradeserial.in_balance=0;													//入卡值
			break;
		default:
			if(strcmp(old_physical_no,physical_no)!=0)
			{
				writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",old_physical_no,physical_no);
				*pRetCode= E_CARD_PHYNO_DIFFER;
				goto L_RETU;
			}
			tradeserial.in_balance=rPack->damt1;										//入卡值
			break;
	}
	if(TYPE_CUR==flag)
		dAmt=D4U5(old_tradeserial.out_balance-old_tradeserial.in_balance,2); 		//发生额=出卡值-入卡值
	else
		dAmt=D4U5(tradeserialhis.out_balance-tradeserialhis.in_balance,2); 		//发生额=出卡值-入卡值
	tradeserial.trade_fee=dAmt;											//补写卡值
	tradeserial.out_balance=tradeserial.in_balance+dAmt;					//出卡值
	if(tradeserial.out_balance<0||tradeserial.out_balance>999)
	{
		writelog(LOG_ERR,"tradeserial.out_balance[%lf]",tradeserial.out_balance);
		*pRetCode= E_TX_SERIAL;
		goto L_RETU;
	}
	writelog(LOG_DEBUG,"写卡失败日期%s,补写流水号%d,交易码%d,卡号%d,补写金额%.2lf,入卡值%lf,出卡值%lf",operate_date,iSerialno,serial_type,card_id,dAmt,tradeserial.in_balance,tradeserial.out_balance);

	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	EncodePwd(seed_key,h_password,tCard.password,0);			//卡密码
	//得到收费类别
	if(tCustomer.fee_type<1)
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
				*pRetCode=E_DB_SPEFEE_R;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//更新客户表的收费类别字段
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode= E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode= E_DB_CUSTOMER_U;
			goto L_RETU;
		}
	}
	DB_t_cif_customer_free_lock_cur();

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialno);  				//获得流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}

	tradeserial.serial_no = (int)dSerialno;											//流水号
	tradeserial.other_seri_no = 0;												//上传端流水号
	tradeserial.serial_type = TXCODE_REWRITE_CARD;								//交易代码；备注：发卡+充值 用一个交易码，即847101； 发卡（不充值）另用一个交易码，即新的发卡程序文件名，从而区分发卡充值与发卡不充值的卡操作信息。
	tradeserial.serial_state = SERISTAT_DEBT;										//流水状态
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	des2src(tradeserial.oper_code , rPack->scust_limit);
	tradeserial.maindevice_id = rPack->lvol6;											//上传工作站标识
	tradeserial.device_id = rPack->lvol7;												//采集设备标识
	tradeserial.card_id = tCard.card_id;											//卡号
	des2src(tradeserial.showid,tCard.showid);										//显示卡号
	tradeserial.purse_id = PURSE_NO_ONE;										//钱包号
	tradeserial.customer_id = tCard.cosumer_id;									//客户标识
	tradeserial.reviseserial_no=dSerialno;											//原写卡失败流水号
	//	插入交易流水表
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
	if(amtcmp(tradeserial.out_balance,0)<0)
	{
		*pRetCode=E_ENTER_ACCOUNT;
		goto L_RETU;
	}
	sprintf(out_pack->vsmess,"流水号:%d 补写金额:%.2lf元 补写前卡余额:%.2lf元  卡当前余额:%.2lf元",tradeserial.serial_no,tradeserial.trade_fee,tradeserial.in_balance,tradeserial.out_balance);
	writelog(LOG_DEBUG,out_pack->vsmess);

	out_pack->lvol0 = tCard.card_id;								//交易卡号
	out_pack->lvol1 = tCustomer.cut_type;						//客户类别
	out_pack->lvol5 = tCustomer.fee_type;						//收费类别
	des2src(out_pack->scust_no,tCard.showid);					//显示卡号
	des2src(out_pack->scust_no2,tCustomer.classdept_no);			//部门号
	des2src(out_pack->scust_auth,tCustomer.stuemp_no);			//学号
	des2src(out_pack->scust_auth2,tCustomer.man_id);			//身份证号
	des2src(out_pack->sname,tCustomer.cut_name);				//客户姓名
	des2src(out_pack->sname2,tCustomer.lib_cardid);				//图书证号
	des2src(out_pack->sstatus0,tCustomer.sex);					//性别
	des2src(out_pack->sopen_emp,h_password);					//卡密码
	des2src(out_pack->sdate0,tCard.end_time);					//有效截至日期

	out_pack->damt2=tradeserial.out_balance;					//出卡值=入卡值+发生额
	out_pack->lserial1=tradeserial.serial_no;						//流水号

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
