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
 * --------------------------------------------
 * 修改日期: 2005-12-26
 * 修改人员: 闻剑
 * 修改描述: 增加圈存写卡返回信息
 不正确的处理
 * 版本信息:
 * 备注信息:
 * --------------------------------------------
 * 修改日期: 2006-03-26
 * 修改人员: 韩海东
 * 修改描述: 增加圈存存在写卡成功
 错误返回的情况，防止
 多补钱
 * 版本信息:
 * 备注信息:
 * --------------------------------------------
 * 修改日期: 2006-12-27
 * 修改人员: 李翔
 * 修改描述: 添加水控大钱包补写添加到写卡失败表
 重新修改业务框架
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
#define     PURESE_COUNT 4

static int insert_chcard_blacklist(int i_serial_type)
{
	if(
		847104 == i_serial_type ||
		847116 == i_serial_type ||
		847126 == i_serial_type
	  )
	{
		return 0; 
	}
	else
	{
		return 1;
	}
}

static int do_process(T_t_pif_card *tCard, T_t_tif_writefailed *tWriteFailed, ST_PACK *rPack, T_t_tif_tradeserial *tradeserial)
{
	int ret = 0;
	int free_lock_flag = 1;                     //0关闭, 1表示打开
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char operate_date[11]="";
	//	char sSerialno[20]="";
	char physical_no[41]="";
	char old_physical_no[41]="";
	char deal_flag[1 + 1] = "";
	int 	iSerialno=0;
	int 	card_id=0;
	int 	serial_type=0;
	int   flag=0;
	double dSerialno=0;
	double  dAmt=0; 
	int cnt_purse_no = 0;
	int card_use_cnt=0;
	int seri_use_cnt=0;
	double seri_in_bala=0;
	double seri_out_bala=0;
	double seri_in_bala_next=0;
	double seri_out_bala_next=0;
	int amt_flag=0;
	char tx_date[11]="";

	T_t_tif_tradeserial_his tradeserialhis;
	T_t_tif_tradeserial old_tradeserial;

	memset(&old_tradeserial,0,sizeof(old_tradeserial));
	memset(&tradeserialhis,0,sizeof(tradeserialhis));

	des2src(physical_no,rPack->sbank_acc);
	card_id=rPack->lvol0;
	card_use_cnt=rPack->lvol8;
	cnt_purse_no = rPack->lvol4;

	getsysdate(sysdate);
	getsystime(systime);
	deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_Y;
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		free_lock_flag = 0;
		goto L_RETU_INNER;
	}
	//判断卡状态是否为写卡未成功状态
	ret=DB_t_pif_card_read_by_card_id(card_id, tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			ret = E_CARDNO_NOT_EXIST;
		else
			ret = E_DB_CARD_R;
		free_lock_flag = 0;
		goto L_RETU_INNER;
	}

	if(STATE_FALSE==tCard->state_id[CARDSTAT_TYPE_WFAIL])
	{
		ret = E_CARDSTATE_NOTWRITEFAIL;
		free_lock_flag = 0;
		goto L_RETU_INNER;
	}
	ret = DB_t_tif_writefailed_read_lock_by_c1_and_card_id_and_purese_no_and_deal_flag(tCard->card_id,cnt_purse_no,&deal_flag[0],tWriteFailed);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
			//            ret = E_DB_WRITEFAILED_N;
			ret = E_WRITEFAILED_DEAL_FLAG_N;         // 没有查到, 就是已经写过了
		else
			ret = E_DB_WRITEFAILED_R;
		goto L_RETU_INNER;
	}

	//  writelog(LOG_ERR,"XXX");
	iSerialno = tWriteFailed->serial_no;
	des2src(operate_date,tWriteFailed->tx_date);

	writelog(LOG_DEBUG,"Serialno[%d]",iSerialno);
	writelog(LOG_DEBUG,"operate_date[%s]",operate_date);
	writelog(LOG_DEBUG,"logictime[%s]",logicdate);
	if(strncmp(logicdate,operate_date,8)==0)
	{
		ret=DB_t_tif_tradeserial_read_by_serial_no(iSerialno,&old_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"Serialno[%d]",iSerialno);
			if(DB_NOTFOUND==ret)
				ret = E_SERIALNO_NOT_EXIST;
			else
				ret = E_DB_TRADESERIAL_R;
			goto L_RETU_INNER;
		}
		if(card_id!=old_tradeserial.card_id)
		{
			writelog(LOG_ERR,"input card_id [%d],tradeserial card_id[%d]",card_id,old_tradeserial.card_id);
			ret = E_CARDNO_SERIAL_NE;
			goto L_RETU_INNER;
		}
		serial_type=old_tradeserial.serial_type;
		flag=TYPE_CUR;
	}
	else
	{
		// TODO: 需要在数据库上建立索引
		ret=DB_t_tif_tradeserial_his_read_by_operate_date_and_serial_no(operate_date,iSerialno,&tradeserialhis);
		if(ret)
		{
			writelog(LOG_ERR,"operate_date[%s]Serialno[%d]",operate_date,iSerialno);
			if(DB_NOTFOUND==ret)
				ret = E_SERIALNO_NOT_EXIST;
			else
				ret = E_DB_TRADESERIAL_R;
			goto L_RETU_INNER;
		}
		if(card_id!=tradeserialhis.card_id)
		{
			writelog(LOG_ERR,"input card_id [%d],tradeserial card_id[%d]",card_id,tradeserialhis.card_id);
			ret = E_CARDNO_SERIAL_NE;
			goto L_RETU_INNER;
		}
		serial_type=tradeserialhis.serial_type;
		flag=TYPE_HIS;
	}
	if(TYPE_CUR==flag)
	{
		seri_in_bala=old_tradeserial.in_balance;
		seri_out_bala=old_tradeserial.out_balance;
		strncpy(tx_date,old_tradeserial.operate_date,sizeof(tx_date));
		dAmt=D4U5(old_tradeserial.out_balance-old_tradeserial.in_balance,2); 		//发生额=出卡值-入卡值
		seri_use_cnt=old_tradeserial.trade_count;
	}
	else
	{
		seri_in_bala=tradeserialhis.in_balance;
		seri_out_bala=tradeserialhis.out_balance;
		strncpy(tx_date,tradeserialhis.operate_date,sizeof(tx_date));
		dAmt=D4U5(tradeserialhis.out_balance-tradeserialhis.in_balance,2); 		//发生额=出卡值-入卡值
		seri_use_cnt=tradeserialhis.trade_count;
	}
	des2src(old_physical_no,tCard->physical_no);
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
				goto L_RETU_INNER;
			}
			//修改卡标志，置为正常状态
			ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, tCard);
			if(ret)
			{
				writelog(LOG_ERR,"card_id[%d]",card_id);
				if(DB_NOTFOUND==ret)
					ret = E_CARDNO_NOT_EXIST;
				else
					ret = E_DB_CARD_R;
				goto L_RETU_INNER;
			}
			des2src(tCard->physical_no,physical_no);			//更换物理卡号
			ret=DB_t_pif_card_update_lock_by_cur(tCard);
			if(ret)
			{
				writelog(LOG_ERR,"card_id[%d]",card_id);
				if(DB_NOTFOUND==ret)
					ret = E_CARDNO_NOT_EXIST;
				else
					ret = E_DB_CARD_U;
				goto L_RETU_INNER;
			}
			DB_t_pif_card_free_lock_by_cur();
			// 宏定义的判断, 0表示成功, 1表示不需要插入
			if (0 == insert_chcard_blacklist(serial_type))
			{
				ret = InsertToBlkList(tCard->card_id,CHCARD_BLACKLIST);
				if (ret)
				{
					goto L_RETU_INNER;
				}	
			}
			// add by 汤成 2005-8-10
			// 增加向名单表写入记录
			/*
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
			goto L_RETU_INNER;
			}
			break;
			default:
			break;
			}
			*/
		}
		tradeserial->in_balance=0;													//入卡值
		des2src(tWriteFailed->comments, "补写卡成功");
		break;
		//补写水控小钱包, 因小钱包扣款失败而起
		//水控小钱包补写归类到847119中，不单独编写
	case 847300:
		des2src(tWriteFailed->comments, "小钱包补写卡成功");
		tradeserial->in_balance = rPack->damt1;
		writelog(LOG_ERR,"小钱包入卡值[%f]",tradeserial->in_balance);
		break;
		//补写水控大钱包, 因大钱包扣款失败而起
		//水控制大钱包补写归类到847119中, 不单独编写
	case 847301:
		des2src(tWriteFailed->comments, "大钱包补写卡成功");
		tradeserial->in_balance = rPack->damt1;
		break;
		//银行转帐-Added by hhd at 20051225
		//考虑到有可能圈存写卡成功，但是提示失败
		//避免重复写卡
	case 240001:
		//判断卡中交易次数是否等于发生错误的流水的交易次数
		writelog(LOG_ERR,"card_use_cnt=[%d],seri_use_cnt=[%d]",card_use_cnt,seri_use_cnt);
		if((card_use_cnt+1)==seri_use_cnt)
		{
			//判断上传入卡值是否等于发生错误的流水的入卡值
			if(amtcmp(rPack->damt1,seri_in_bala)==0)	   //入卡值等于入卡值，卡没有写上
				tradeserial->in_balance=rPack->damt1;
			else if(amtcmp(rPack->damt1,seri_out_bala)==0)  //入卡值等于出卡值，卡已经写上
			{
				tradeserial->in_balance=rPack->damt1;
				amt_flag=1;
			}
			else
			{
				writelog(LOG_ERR,"In_balance abnormity,in_bala=[%f]",rPack->damt1);
				ret = E_ENTER_ACCOUNT;
				goto L_RETU_INNER;
			}
		}
		else if((card_use_cnt+1)>seri_use_cnt)
		{
			//当写卡不成功时，一般不会更新卡的交易次数，
			//导致下一次的交易次数还是等于失败流水的次数，
			//所以去下一条流水的时候，如果取不到，就+1
			ret=Get_card_next_serial(tCard->card_id,tx_date,seri_use_cnt,&seri_in_bala_next,&seri_out_bala_next);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
				{
					ret=Get_card_next_serial(tCard->card_id,tx_date,seri_use_cnt+1,&seri_in_bala_next,&seri_out_bala_next);
					if(ret)
					{
						writelog(LOG_ERR,"Get_card_next_serial(=) error,errcode=[%d]",ret);
						writelog(LOG_ERR,"没有找到下一笔流水");
						goto L_RETU_INNER;
					}
				}
				else
				{
					writelog(LOG_ERR,"Get_card_next_serial(+1) error,errcode=[%d]",ret);
					goto L_RETU_INNER;
				}
			}
			writelog(LOG_INFO,"seri_in_bala_next=[%f],seri_in_bala=[%f],seri_out_bala=[%f]",seri_in_bala_next,seri_in_bala,seri_out_bala);

			if(amtcmp(seri_in_bala_next/100,seri_in_bala)==0)
				tradeserial->in_balance=rPack->damt1;
			else if(amtcmp(seri_in_bala_next/100,seri_out_bala)==0)
			{
				tradeserial->in_balance=rPack->damt1;
				amt_flag=1;
			}
			else
			{
				tradeserial->in_balance=rPack->damt1;
				writelog(LOG_ERR,"In_balance abnormity,in_bala=[%f]",rPack->damt1);
				ret = E_ENTER_ACCOUNT;
				goto L_RETU_INNER;
			}
		}
		else
		{
			writelog(LOG_ERR,"In_total_cnt abnormity,in_total_cnt=[%d]",card_use_cnt);
			ret = E_ENTER_ACCOUNT;
			goto L_RETU_INNER;
		}
	default:
		if(strcmp(old_physical_no,physical_no)!=0)
		{
			writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",old_physical_no,physical_no);
			ret = E_CARD_PHYNO_DIFFER;
			goto L_RETU_INNER;
		}
		tradeserial->in_balance=rPack->damt1;										//入卡值
		break;
	}
	if(TYPE_CUR==flag)
		dAmt=D4U5(old_tradeserial.out_balance-old_tradeserial.in_balance,2); 		//发生额=出卡值-入卡值
	else
		dAmt=D4U5(tradeserialhis.out_balance-tradeserialhis.in_balance,2); 		//发生额=出卡值-入卡值
	//说明不需要写卡,则发生额置为0
	if(amt_flag==1)
	{
		tradeserial->trade_fee=0;											//补写卡值
	}
	else
	{
		tradeserial->trade_fee=dAmt;											//补写卡值
	}
	tradeserial->out_balance=tradeserial->in_balance+dAmt;					//出卡值
	writelog(LOG_ERR,"小钱包出卡值[%f]",tradeserial->out_balance);
	writelog(LOG_ERR,"小钱包交易金额[%f]",dAmt);

	if(tradeserial->out_balance<0||tradeserial->out_balance>999)
	{
		writelog(LOG_ERR,"tradeserial.out_balance[%lf]",tradeserial->out_balance);
		ret = E_TX_SERIAL;
		goto L_RETU_INNER;
	}
	writelog(LOG_DEBUG,"写卡失败日期%s,补写流水号%d,交易码%d,卡号%d,补写金额%.2lf,入卡值%lf,出卡值%lf",operate_date,iSerialno,serial_type,card_id,dAmt,tradeserial->in_balance,tradeserial->out_balance);

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialno);  				//获得流水号
	if(ret)
	{
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU_INNER;
	}

	tradeserial->serial_no = D2I(dSerialno);											//流水号
	tradeserial->other_seri_no = 0;												//上传端流水号
	tradeserial->serial_type = TXCODE_REWRITE_CARD;								//交易代码；备注：发卡+充值 用一个交易码，即847101； 发卡（不充值）另用一个交易码，即新的发卡程序文件名，从而区分发卡充值与发卡不充值的卡操作信息。
	tradeserial->serial_state = SERISTAT_DEBT;										//流水状态
	des2src(tradeserial->operate_date,sysdate);											//发生日期
	des2src(tradeserial->operate_time,systime);											//发生时间
	des2src(tradeserial->collect_date,sysdate);												//采集日期
	des2src(tradeserial->collect_time,systime);												//采集时间
	des2src(tradeserial->enteract_date,logicdate);											//处理日期
	des2src(tradeserial->enteract_time,systime);											//处理时间
	des2src(tradeserial->oper_code , rPack->scust_limit);
	tradeserial->maindevice_id = rPack->lvol6;											//上传工作站标识
	tradeserial->device_id = rPack->lvol7;												//采集设备标识
	tradeserial->card_id = tCard->card_id;											//卡号
	des2src(tradeserial->showid,tCard->showid);										//显示卡号
	tradeserial->purse_id = cnt_purse_no;										//钱包号,根据具体发现需要补写的钱包号决定
	tradeserial->customer_id = tCard->cosumer_id;									//客户标识
	tradeserial->reviseserial_no = iSerialno;											//原写卡失败流水号
	tradeserial->trade_count = card_use_cnt + 1;                                    //交易次数为卡交易次数+1           
	//	插入交易流水表
	ret = DB_t_tif_tradeserial_add(tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		goto L_RETU_INNER;
	}
	/******************************************************************/
	//更新写卡失败表
	tWriteFailed->deal_serial_no = tradeserial->serial_no;
	//	writelog(LOG_ERR,"流水号[%d]",tWriteFailed->deal_serial_no);
	tWriteFailed->deal_bala = tradeserial->trade_fee;
	des2src(tWriteFailed->deal_date,sysdate);
	des2src(tWriteFailed->deal_time,systime);
	//	tWriteFailed->deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_N;
	ret = DB_t_tif_writefailed_update_lock_by_c1(tWriteFailed);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
		{
			ret = E_DB_WRITEFAILED_N;
		}
		else
		{
			ret = E_DB_WRITEFAILED_U;    
		}
		goto L_RETU_INNER;
	}
	DB_t_tif_writefailed_free_lock_by_c1();
	/******************************************************************/
	return 0;
L_RETU_INNER:
	if (free_lock_flag)
		DB_t_tif_writefailed_free_lock_by_c1();
	return ret;
}

int F847119(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char h_password[7] = "";							//卡密码
	char seed_key[17] = "";							//种子密钥
	T_t_pif_card tCard;
	T_t_tif_tradeserial tradeserial;
	T_t_tif_writefailed tWriteFailed;
	T_t_cif_customer tCustomer;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCard,0,sizeof(tCard));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tWriteFailed, 0, sizeof tWriteFailed);
	memcpy(seed_key,STATIC_SEED_KEY,sizeof(seed_key));		//读种子密钥

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,F_LVOL6,
		   F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCUST_AUTH2,
		   F_SDATE0,F_SNAME,F_SNAME2,
		   F_SOPEN_EMP,F_SSTATUS0,
		   F_DAMT2,F_LSERIAL1,F_VSMESS,0);
	/************************************************************************/
	ret = do_process(&tCard, &tWriteFailed, rPack, &tradeserial);
	if (ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			*pRetCode = E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode = E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	EncodePwd(seed_key,h_password,tCard.password,1);			//卡密码
	DB_t_cif_customer_free_lock_cur();
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
