/* --------------------------------------------
 * 程序名称: F843343.sqc
 * 创建日期: 2007-8-8
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 发行商户卡
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



int F843343(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int	hi_cutid = 0;											//客户ID
	int	hi_cuttype = 0;										//客户类型
	int i=0;
	int ret = 0;
	int len = 0;
	char h_showcardid[11] = "";						//显示卡号
	char h_password[7] = "";							//卡密码
	double h_temp_Card_id = 0;						//卡号
	char seed_key[17] = "";							//种子密钥
	char card_endtime[8 + 1] = "";						//卡的有效截至日期
	char logicdate[11]="";								//业务日期
	char sysdate[11]="";
	char systime[9]="";
	char sTempFeeType[256]="";
	char sMsg[256]="";
	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	int 	type=0;										//充值类型
	int card_type=0;
	T_t_cif_customer tCustomer;
	T_t_pif_card tCard;

	T_t_aif_account  tAccount;
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_savdtl		tSavdtl;
	T_t_pif_spefee 	tSpeFee;
	double dUniqNo = 0;
	InAcc	IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&IA,0,sizeof(IA));
	memset(&tCard, 0, sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSavdtl,0,sizeof(tSavdtl));

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,
				F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCERT_NO,
				F_SDATE0,F_SNAME,F_SNAME2,
				F_SOPEN_EMP,F_SSTATUS0,
				F_DAMT2,F_LSERIAL1,F_VSMESS,
   			       F_SORDER0,F_SORDER1,F_SORDER2,
   			       F_SHOLDER_AC_NO,F_SSTAT_TYPE,F_SSTAT_TYPE2,
   			       F_SNATION_CODE,F_SBRANCH_CODE0,F_LVOL10,F_LVOL11,
				0);
	hi_cutid = rPack->lvol0;									//客户ID
	hi_cuttype = rPack->lvol3;									//客户类别
	card_type=CT_MERCH;										//卡类型
	des2src(h_showcardid,rPack->scust_no);						//显示卡号
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//检查客户信息，判断是否可以发行卡
	des2src(tCard.physical_no, rPack->sbank_acc);				//物理卡号
	trim(h_showcardid);
	if(strlen(h_showcardid))
	{
		ret=IsExistShowCardNo(h_showcardid);
		if(ret)
		{
			//*pRetCode = ret;
			//goto L_RETU;
		}
	}
	ret=IsExistCardByPhyCardNo(tCard.physical_no);
	if(ret)
	{
		writelog(LOG_ERR,"IsExistCardByPhyCardNo err,errcod=[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	ret=IsExistCardByCustomId(hi_cutid);
	if (ret)
	{
		writelog(LOG_ERR,"IsExistCardByCustomId err,errcod=[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	//得到收费类别
	memset(&tCustomer,0,sizeof tCustomer);
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(hi_cutid, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",hi_cutid);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}

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
	}
	tCustomer.use_flag[0]='1';
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
	DB_t_cif_customer_free_lock_cur();
	ret = GetParameter(GLOBE_FLAG_TEMPCARD_FEETYPE,sTempFeeType);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter err,errcod=[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}

	//tradeserial.trade_fee =D4U5(rPack->damt0,2);

	//检查金额是否超过最大额度
	//	准备数据插入卡信息表
	memcpy(seed_key,STATIC_SEED_KEY,16);			//读种子密钥


	if(strlen(rPack->sdate0)==0)
	{
		*pRetCode=E_TB_CUSTOMER_NO_ENDTIME;
		goto L_RETU;
	}
	else
	{
		ret=IsInvalidDateTime(rPack->sdate0,"YYYYMMDD");
		if(ret)
		{
			*pRetCode = E_INPUT_DATE;
			goto L_RETU;
		}
		if(strncmp(rPack->sdate0,sysdate,8)<=0)
		{
			*pRetCode=E_INPUT_DATE;
			goto L_RETU;
		}
		des2src(card_endtime,rPack->sdate0);
	}
	//	默认密码, 初始取身份证的后6位, 没有身份证号用666666.
	if(strcmp(tCustomer.man_idtype,"1")==0)
	{
		get_init_passwd_by_man_id(tCustomer.man_id,h_password);
	}
	else
		strcpy(h_password,DEFAULT_CUST_PWD);
	ret = getNewUniqNo(KEYTYPE_CARD_ID,&h_temp_Card_id);						//获取最大卡号
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tCard.type_id=card_type;
	tradeserial.serial_type = TXCODE_MERCH_OPEN;

	tCard.card_id = D2I(h_temp_Card_id);										//卡号
	des2src(tCard.showid,h_showcardid);											//显示卡号
	des2src(tCard.is_main,TYPE_YES);  											//是否为主卡
	des2src(tCard.state_id,CARDSTAT_REG);										//卡状态
	EncodePwd(seed_key,h_password,tCard.password,0);							//卡密码
	tCard.cosumer_id = hi_cutid;													//客户标识
	tCard.account_count = ACCOUNT_COUNT_ONE;									//卡对应帐户个数
	des2src(tCard.begin_time,sysdate);											//注册时间
	des2src(tCard.end_time, card_endtime);										//截至时间

	tCard.phytype = PHYTYPE_NO_ONE;											//设备物理型号;默认为1
	//	插入卡信息
	ret = DB_t_pif_card_add(&tCard);
	if (ret)
	{
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_CARD_E;
		else
			*pRetCode = E_DB_CARD_I;
		goto L_RETU;
	}
	//	更新账户信息表，改写卡号
	ret=DB_t_aif_account_read_by_customer_id_and_act_type(hi_cutid,ACCTYPE_SHOPMAIN,&tAccount);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_customer_id_and_act_type err,errcod=[%d]",ret);
		*pRetCode = E_DB_ACCOUNT_R;
		goto L_RETU;
	}

	tAccount.card_id=tCard.card_id;
	tAccount.card_type=tCard.type_id;
	
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
	/*
	// add by 汤成2005-09-05
	// 记录发行正式卡信息
	/////////////////////////////////////////////////////////////////////////
	ret = InsertToCutUpdList(tCard.card_id, CUTUPD_ADD,tCard.physical_no);
	if( ret )
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	/////////////////////////////////////////////////////////////////////////
	*/
	tradeserial.serial_no = D2I(dUniqNo);											//流水号
	tradeserial.other_seri_no = 0;														//上传端流水号
	tradeserial.serial_state = SERISTAT_NODEBT;												//流水状态
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
	tradeserial.customer_id = hi_cutid;													//客户标识

	des2src(tradeserial.oper_code , rPack->scust_limit);			//操作员代码
	tradeserial.sys_id = 0;																//外部系统标识
	tradeserial.trade_count=1;														//当前卡交易次数
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
	T_t_cif_shop  t_cif_shop;
	memset(&t_cif_shop,0,sizeof t_cif_shop);
	ret=DB_t_cif_shop_read_by_cut_id(hi_cutid,&t_cif_shop);
	if(ret)
	{
		*pRetCode = E_DB_SHOP_R;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}
	//	返回卡号\密码\显示卡号\客户类型\图书证号\有效截至日期
	out_pack->lvol10=CT_MERCH;									//卡类型
	out_pack->lvol11=t_cif_shop.shop_id;							//商户号
	out_pack->lvol0 = (int)h_temp_Card_id;                      			//交易卡号
	out_pack->lvol1 = tCustomer.cut_type;						//客户类别
	out_pack->lvol5 = tCustomer.fee_type;						//收费类别
	des2src(out_pack->scust_no,h_showcardid);					//显示卡号
	des2src(out_pack->scust_no2,tCustomer.classdept_no);			//部门号
	des2src(out_pack->scust_auth,tCustomer.stuemp_no);			//学号
	des2src(out_pack->scert_no,tCustomer.man_id);				//身份证号
	des2src(out_pack->sname,tCustomer.cut_name);				//客户姓名
	des2src(out_pack->sname2,tCustomer.lib_cardid);				//图书证号
	des2src(out_pack->sstatus0,tCustomer.sex);					//性别
	des2src(out_pack->sopen_emp,h_password);					//卡密码
	des2src(out_pack->sdate0,card_endtime);					//有效截至日期
	strcpy(out_pack->sorder0,CARD_STRUCT_VERSION);			//制卡版本号
	strcpy(out_pack->sorder1,CARD_REGISTER_PUBLISH_CODE);	//发卡注册标识号
	strcpy(out_pack->sorder2,CARD_REGISTER_SERVICE_CODE);	//服务注册标识号
	sprintf(out_pack->sholder_ac_no,"%d",tCustomer.cut_id);		//客户号
	des2src(out_pack->sstat_type,tCustomer.man_idtype);			//证件类型
	des2src(out_pack->snation_code,tCustomer.country);			//国籍
	sprintf(out_pack->sstat_type2,"%d",tCustomer.nation);			//民族
	des2src(out_pack->sbranch_code0,tCustomer.school_code);		//院校代码
//	out_pack->damt2=tradeserial.out_balance;				//出卡值
	out_pack->lserial1=tradeserial.serial_no;						//流水号

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

