/* ----------------------------------------------------------
 * 程序名称：balance.c
 * 创建日期：2004-8-13 9:34
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：结帐处理函数集合
 * ----------------------------------------------------------
 * 修改日期：2004-09-08
 * 修改人员： 韩海东
 * 修改描述： 统一规范代码
 * 版本信息：1.0.0.1
 * 备注信息：
 * ----------------------------------------------------------
 * 修改日期：2004-12-28
 * 修改人员： 韩海东
 * 修改描述： 修改商户临时表导入到商户表中的部分，根据新需求
 			  该功能去掉，采取不删除商户的办法解决
 * 版本信息：1.0.0.2
 * 备注信息：
 * ----------------------------------------------------------
 * 修改日期：2005-02-09
 * 修改人员： 韩海东
 * 修改描述： 增加卡库不平机制的处理
 * 版本信息：1.0.0.3
 * 备注信息：
 * ----------------------------------------------------------
 * 修改日期：2005-10-27
 * 修改人员： 韩海东
 * 修改描述：修改备份流水的模式，采用sql语句实现，提高效率
 * 版本信息：1.0.0.4
 * 备注信息：
 * ----------------------------------------------------------
 * 修改日期：2005-11-14
 * 修改人员： 韩海东
 * 修改描述：备份门禁流水,并结算时清除
 * 版本信息：1.0.0.5
 * 备注信息：
 * ----------------------------------------------------------
 * 修改日期：2006-08-08
 * 修改人员： 韩海东
 * 修改描述：根据上海大学的需求，把独立核算的商户的每天的营业
  			  数据按照指定的数据格式形成文件，ftp形式发送给
 * 版本信息：1.0.0.6
 * 备注信息：
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/

#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "mypub.h"
#include "balance.h"
#include "dbfunc.h"
#include "account.h"

#define	SLEEP_TIME				60	//结账间隔时间

static int freezecard(int in_card_id,int in_cut_id,char* in_operator,int in_maindevice_id,int in_device_id)
{

  	int  ret = 0;
	int	card_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char	operator[33+1] = "";
	int	cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	double dSerial_no = 0;
	char sCardState[5] = "";
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_tif_meslist tMesList;

	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tMesList,0,sizeof(tMesList));

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode[%d]",ret);
		goto L_RETU;
	}
	//	准备输入信息
	card_id = in_card_id;												//卡标识
	cut_id = in_cut_id;												//客户号
	des2src(operator,in_operator);									//操作员号
	maindevice_id = in_maindevice_id;											//上传工作站标识
	device_id = in_device_id;												//采集设备标识

	//	检查客户信息，判断是否可以冻结
	ret = GetCardState(card_id,sCardState);
	if (ret)
	{
		writelog(LOG_ERR,"GetCardState error,errcode[%d],card_id[%d]",ret,sCardState);
		goto L_RET;
	}
	if(strncmp(sCardState,CARDSTAT_LOGOUT,4)==0)
	{
		writelog(LOG_ERR,"strncmp(sCardState,CARDSTAT_LOGOUT,4) error");
		goto L_RET;
	}
	if(STATE_TRUE==sCardState[CARDSTAT_TYPE_FREEZE])
	{
		writelog(LOG_ERR,"STATE_TRUE==sCardState[CARDSTAT_TYPE_FREEZE] error");
		goto L_RET;
	}
	//	修改卡状态为冻结
	ret = UpdateCardState(card_id,CARDSTAT_TYPE_FREEZE,STATE_TRUE);
	if (ret)
	{
		writelog(LOG_ERR,"UpdateCardState error,errcode[%d],card_id[%d]",ret,card_id);
		goto L_RET;
	}
	//如果该卡号被挂失,则解冻时对黑名单不处理
	if(STATE_FALSE==sCardState[CARDSTAT_TYPE_LOST])
	{
		//	插入黑名单表
		ret=DB_t_tif_black_sheet_del_by_card_id_and_is_ad(card_id,DELETE_BLACKLIST);
		if(ret)
		{
			if(ret!=DB_NOTFOUND)
			{
				writelog(LOG_ERR,"DB_t_tif_black_sheet_del_by_card_id_and_is_ad err[%d],card_id=[%d] ",ret,card_id);
				goto L_RETU;
			}
		}
		ret=InsertToBlkList(card_id,ADD_BLACKLIST);
		if(ret)
		{
			writelog(LOG_ERR,"InsertToBlkList err[%d],card_id=[%d] ",ret,card_id);
			goto L_RETU;
		}

		//广播黑名单
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,card_id);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//增删标志

		tMesList.funid = 930005;
		tMesList.level = 1;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			goto L_RETU;
		}
	}
	//	准备数据插入交易流水表
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerial_no);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode[%d]",ret);
		goto L_RETU;
	}
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	tradeserial.serial_no = (int)dSerial_no;									//流水号
	tradeserial.serial_type = TXCODE_FREEZE_CARD;								//冻结卡
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;							//流水状态
	tradeserial.maindevice_id = maindevice_id;									//上传工作站标识
	tradeserial.device_id = device_id;											//采集设备标识
	tradeserial.card_id = card_id;												//交易卡号
	tradeserial.customer_id=cut_id;											//客户号
	des2src(tradeserial.oper_code,operator);
	//	插入交易流水表
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode=[%d]",ret);
		goto L_RETU;
	}

	return 0;
L_RET:
	return ret;
L_RETU:
	db_rollback();
	return ret;


}

static int process(T_t_tif_tradeserial *p)
{
	int ret=0;
	//char szActno[17]="";				//帐户
	T_t_pif_card card;					//卡信息表
	T_t_cif_shop		shop;			//商户信息表
	T_t_aif_account	account;		//帐户表
	InAcc   IA;						//记账模块输入参数

	memset(&card,0,sizeof(card));
	memset(&shop,0,sizeof(shop));
	memset(&account,0,sizeof(account));
	memset(&IA,0,sizeof(IA));


	//IA.iMainDevId=p->maindevice_id;			//工作站标识
	//IA.iDevId=p->device_id;					//设备ID
	IA.iSerialNo=p->serial_no;					//流水号
	IA.iTradeNo=p->serial_type;				//交易码
	strcpy(IA.sTxDate,p->operate_date);		//交易日期
	strcpy(IA.sTxTime,p->operate_time);		//交易时间
	strcpy(IA.sTxCollectDate,p->collect_date);	//采集日期
	strcpy(IA.sTxCollectTime,p->collect_time);	//采集时间
	strcpy(IA.sTxAccDate,p->enteract_date);	//记账日期
	strcpy(IA.sTxAccTime,p->enteract_time);	//记账时间
	strcpy(IA.sArrInActno[0],p->out_account_id);		//账号
	strcpy(IA.sArrInActno[1],p->in_account_id);		//账号
	strcpy(IA.sMdeOper,p->oper_code);		//录入操作员
	strcpy(IA.sTalOper,p->oper_code);		//记账操作员

 	IA.dInCardBala=p->in_balance;                       //入卡值
       IA.dOutCardBala=p->out_balance;                   //出卡值

	//IA.in_card_bala=p->in_balance;		//入卡值
	//IA.out_card_bala=p->out_balance;		//出卡值
	IA.dArrInAmt[0]=p->trade_fee;					//发生额

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(&IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	return 0;
}

static int process_makeup(T_t_tif_tradeserial *p)
{
	int ret=0;
	//char szActno[17]="";			//帐户
	T_t_pif_card card;					//卡信息表
	T_t_cif_shop		shop;			//商户信息表
	T_t_aif_account	account;		//帐户表
	InAcc   IA;						//记账模块输入参数

	memset(&card,0,sizeof(card));
	memset(&shop,0,sizeof(shop));
	memset(&account,0,sizeof(account));
	memset(&IA,0,sizeof(IA));


	//IA.iMainDevId=p->maindevice_id;			//工作站标识
	//IA.iDevId=p->device_id;					//设备ID
	IA.iSerialNo=p->serial_no;					//流水号
	IA.iTradeNo=p->serial_type;				//交易码
	strcpy(IA.sTxDate,p->operate_date);		//交易日期
	strcpy(IA.sTxTime,p->operate_time);		//交易时间
	strcpy(IA.sTxCollectDate,p->collect_date);	//采集日期
	strcpy(IA.sTxCollectTime,p->collect_time);	//采集时间
	strcpy(IA.sTxAccDate,p->enteract_date);	//记账日期
	strcpy(IA.sTxAccTime,p->enteract_time);	//记账时间
	strcpy(IA.sArrInActno[0],p->out_account_id);		//账号
	strcpy(IA.sArrInActno[1],p->in_account_id);		//账号
	strcpy(IA.sMdeOper,p->oper_code);		//录入操作员
	strcpy(IA.sTalOper,p->oper_code);		//记账操作员

 	IA.dInCardBala=p->in_balance;                       //入卡值
       IA.dOutCardBala=p->out_balance;                   //出卡值

	//IA.in_card_bala=p->in_balance;		//入卡值
	//IA.out_card_bala=p->out_balance;		//出卡值
	IA.dArrInAmt[0]=p->trade_fee;					//发生额

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(&IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	return 0;
}

static int add_serialno(T_t_tif_tradeserial *p,double trans_amt,char * in_account_no,char * out_account_no)
{
	int ret=0;
	double dUniqno=0;
	char logicdate[11]="";
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}
	//p->serial_no;                			//流水号
	p->other_seri_no=0;                     			//上传端流水号
	p->serial_type=TXCODE_INNERTRANS;       	//交易代码
	p->serial_state=SERISTAT_NODEBT;        		//流水状态
	strcpy(p->operate_date,logicdate);            	//发生日期
	getsystime(p->operate_time);           		//发生时间
	strcpy(p->collect_date,logicdate);             	//采集日期
	strcpy(p->collect_time,p->operate_time);       //采集时间
	strcpy(p->enteract_date,logicdate);            	//入帐日期
	strcpy(p->enteract_time,p->operate_time);    //入帐时间
	p->maindevice_id=0;                     			//上传工作站标识
	p->device_id=0;                         			//交易发生设备标识
	//p->devphy999_id[8+1];                 //三九设备物理ID
	//p->showid[10+1];                      //显示卡号
	//p->card_id;                           //交易卡号
	//p->purse_id;                          //交易钱包号
	//p->trade_count;                       //当前卡中帐户交易次数
	p->trade_fee=trans_amt;                          			//本次交易金额
	//printf("p->trade_fee[%lf]\n",p->trade_fee);
	//p->in_balance;                        //入卡金额
	//p->out_balance;                       //出卡金额
	//p->deposit_fee;                       //押金金额
	//p->in_fee;                            //手续金额
	//p->cost_fee;                          //卡成本费
	//p->oldpwd[32+1];                      //原始密码
	//p->newpwd[32+1];                      //更新密码
	//p->customer_id;                       //客户标识
	strcpy(p->oper_code,"system");          		//操作员代码
	strncpy(p->out_account_id,out_account_no,sizeof(p->out_account_id)-1);               		//出帐帐号
	//printf("p->out_account_id[%s]\n",p->out_account_id);
	strncpy(p->in_account_id,in_account_no,sizeof(p->in_account_id)-1);                			//入帐账号
	//printf("p->in_account_id[%s]\n",p->in_account_id);
	//p->b_act_id[40+1];                    //外部系统帐号
	//p->sys_id;                            //外部系统标识
	//p->condition_id;                      //自动转帐条件标识
	//p->is_online[1+1];                    //是否联机
	//p->tmark;                             //交易标记
	//p->dev_auth[8+1];                     //终端设备授权号
	//p->comu_ver;                          //通信版本号
	//p->run_reaon;                         //启动原因
	//p->crc[5+1;                           //CRC校验	CRC
	p->ecode=0;                             				//返回码	ecode
	//p->revisesrial_no;                    //冲正流水号
	//p->reserve1[40+1];                    //预留字段1
	//p->reserve2[40+1];                    //预留字段2
	//p->reserve3[40+1];                    //预留字段3

	//取新的流水号
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqno);
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		p->ecode=ret;
		return ret;
	}
	p->serial_no=(int)dUniqno;
	ret = DB_t_tif_tradeserial_add(p);
	if (ret)
	{
		writelog(LOG_ERR,"消费流水表插入错误：SQLCODE= [%d] ",ret);
		ret= E_DB_TRADESERIAL_I;
		p->ecode=ret;
		return ret;
	}
	return 0;
}

static int add_serialno_makeup(T_t_tif_tradeserial *p)
{
	int ret=0;
	double dUniqno=0;
	char logicdate[11]="";
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}
	//p->serial_no;                			//流水号
	p->other_seri_no=0;                     			//上传端流水号
	//p->serial_type=TXCODE_INNERTRANS;       	//交易代码
	p->serial_state=SERISTAT_NODEBT;        		//流水状态
	strcpy(p->operate_date,logicdate);            	//发生日期
	getsystime(p->operate_time);           		//发生时间
	strcpy(p->collect_date,logicdate);             	//采集日期
	strcpy(p->collect_time,p->operate_time);       //采集时间
	strcpy(p->enteract_date,logicdate);            	//入帐日期
	strcpy(p->enteract_time,p->operate_time);    //入帐时间
	p->maindevice_id=0;                     			//上传工作站标识
	p->device_id=0;                         			//交易发生设备标识
	//p->devphy999_id[8+1];                 //三九设备物理ID
	//p->showid[10+1];                      //显示卡号
	//p->card_id;                           //交易卡号
	//p->purse_id;                          //交易钱包号
	//p->trade_count;                       //当前卡中帐户交易次数
	//p->trade_fee=trans_amt;                          			//本次交易金额
	//printf("p->trade_fee[%lf]\n",p->trade_fee);
	//p->in_balance;                        //入卡金额
	//p->out_balance;                       //出卡金额
	//p->deposit_fee;                       //押金金额
	//p->in_fee;                            //手续金额
	//p->cost_fee;                          //卡成本费
	//p->oldpwd[32+1];                      //原始密码
	//p->newpwd[32+1];                      //更新密码
	//p->customer_id;                       //客户标识
	strcpy(p->oper_code,"system");          		//操作员代码
	//strncpy(p->out_account_id,out_account_no,sizeof(p->out_account_id)-1);               		//出帐帐号
	printf("p->out_account_id[%s]\n",p->out_account_id);
	//strncpy(p->in_account_id,in_account_no,sizeof(p->in_account_id)-1);                			//入帐账号
	printf("p->in_account_id[%s]\n",p->in_account_id);
	//p->b_act_id[40+1];                    //外部系统帐号
	//p->sys_id;                            //外部系统标识
	//p->condition_id;                      //自动转帐条件标识
	//p->is_online[1+1];                    //是否联机
	//p->tmark;                             //交易标记
	//p->dev_auth[8+1];                     //终端设备授权号
	//p->comu_ver;                          //通信版本号
	//p->run_reaon;                         //启动原因
	//p->crc[5+1;                           //CRC校验	CRC
	p->ecode=0;                             				//返回码	ecode
	//p->revisesrial_no;                    //冲正流水号
	//p->reserve1[40+1];                    //预留字段1
	//p->reserve2[40+1];                    //预留字段2
	//p->reserve3[40+1];                    //预留字段3

	//取新的流水号
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqno);
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		p->ecode=ret;
		return ret;
	}
	p->serial_no=(int)dUniqno;
	ret = DB_t_tif_tradeserial_add(p);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode= [%d] ",ret);
		p->ecode=ret;
		return ret;
	}
	return 0;
}

int SearchLeafshop_and_Trans(int shop_id,char* Independ_or_not)
{

	int ret=0;
	int cnt=0;

	char type_yes_or_no[1+1]="";
	//T_v_tif_shopdeptfee 	v_shopdeptfee;
	T_t_cif_shop		  	t_shop;
	T_t_tif_tradeserial		t_tradeserial;
	T_t_aif_account		t_account;

	memset(&t_shop,0,sizeof(t_shop));

	ret=DB_t_cif_shop_read_by_shop_id(shop_id,&t_shop);
	if(ret)
	{
		writelog(LOG_ERR,"read tablet_cif_shop  shop_id[%d]",shop_id);
		if(DB_NOTFOUND==ret)
		{
			return E_SHP_ID_NOT_EXIST;
		}
		else
			return E_DB_SHOP_R;
	}
	strcpy(type_yes_or_no,TYPE_YES);
	if(strncmp(t_shop.is_leaf,type_yes_or_no,1))
	{
		//根据客户号和商户主账号类型查询账号表，得到账号
		memset(&t_account,0,sizeof(t_account));
		ret=DB_t_aif_account_read_by_customer_id_and_act_type(t_shop.cut_id,ACCTYPE_SHOPMAIN,&t_account);
		if((0!=ret)&&(DB_NOTFOUND!=ret))
		{
			writelog(LOG_ERR,"read_by_customer_id_and_act_type ret[%d]cutid[%d]",ret,t_shop.cut_id);
			return E_DB_ACCOUNT_R;
		}
		if(!strncmp(Independ_or_not,type_yes_or_no,1))
		{
			memset(&t_tradeserial,0,sizeof(t_tradeserial));
			ret=add_serialno(&t_tradeserial,t_account.cur_bala,INNER_ACCOUNT_BANKTRANSFER,t_account.account_id);
			if(ret)
			{
				writelog(LOG_ERR,"add_serialno error,t_account.account_id=[%s],errcode=[%d]",t_account.account_id,ret);
				db_rollback();
				return 	ret;
			}
		}
		else
		{
			memset(&t_tradeserial,0,sizeof(t_tradeserial));
			ret=add_serialno(&t_tradeserial,t_account.cur_bala,INNER_ACCOUNT_FINANCETRANSER,t_account.account_id);
			if(ret)
			{
				writelog(LOG_ERR,"add_serialno error,t_account.account_id=[%s],errcode=[%d]",t_account.account_id,ret);
			//	db_rollback();
				return 	ret;
			}
		}
		#if 0
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			db_rollback();
			return 	ret;
		}
		#endif
		//交易正常则进行下面的处理
		ret=process(&t_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"process ret[%d]",ret);
			goto L_RETU;
		}
		//更新流水状态
		getsysdate(t_tradeserial.enteract_date);			//处理日期
		getsystime(t_tradeserial.enteract_time);			//处理时间
		t_tradeserial.serial_state=SERISTAT_DEBT;		//已入帐
		ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
			goto L_RETU;
		}
		#if 0
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			goto L_RETU;
		}
		#endif
	}

	//循环判断下边的子节点是否为叶子商户
	ret=DB_t_cif_shop_open_select_by_cur2_and_dept_id(shop_id);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_shop_open_select_by_cur2_and_dept_id ret[%d]shop_id[%d]",ret,shop_id);
		return E_DB_SHOP_R;
	}
	while(1)
	{
		memset(&t_shop,0,sizeof(t_shop));
		ret=DB_t_cif_shop_fetch_select_by_cur2(&t_shop);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"DB_t_cif_shop_fetch_select_by_cur2 have not record,shop_id=[%d]!",t_shop.shop_id);
						break;
					}
				else
					break;
			}
			else
				goto L_RETU;
		}
		cnt++;
		ret=SearchLeafshop_and_Trans(t_shop.shop_id,Independ_or_not);
		if(ret)
		{
			writelog(LOG_DEBUG,"SearchLeafshop_and_Trans faild,ret[]t_shop.shop_id=[%d]!",ret,t_shop.shop_id);
			goto L_RETU;
		}
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		goto L_RETU;
	}
	return 0;

L_RETU:
	//回滚事务
	db_rollback();
	//更新流水状态
	getsysdate(t_tradeserial.enteract_date);			//处理日期
	getsystime(t_tradeserial.enteract_time);			//处理时间
	//t_tradeserial.ecode=*pRetCode;			//返回码
	t_tradeserial.serial_state=SERISTAT_DEBTEXC;		//入账异常状态
	ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
	}
	//提交事务
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
	}
	return E_ENTER_ACCOUNT;

}

/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 停止入帐操作，修改结算标志
      修改记录	:
*****************************************************/
int StopInBalance()
{
	char buffer[50];
	int ret=0;
	memset(buffer,0,sizeof(buffer));
	ret=GetParameter(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"Read syspara err [%d]",ret);
		return E_SEARCH_FLAG;
	}

	if(strncmp(buffer,"1",1)!=0)
	{
		strcpy(buffer,"1");
		ret=SetParameter(GLOBE_FLAG_BALANCE,buffer);
		if(ret)
		{
			writelog(LOG_ERR,"Write syspara err [%d]",ret);
			return E_CHANGE_FLAG;
		}
	}
	else
	{
		writelog(LOG_DEBUG,"The value of balance parameter is '%s',maybe there have another thread balancing now!",&buffer);
		return	E_BALANCE_NOW;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}

	mysleep(SLEEP_TIME);
	writelog(LOG_DEBUG,"Stop in balance succeed!");
	return 0;

}

/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 备份数据库，考虑结算可能会修改一些帐务信息，
      			  结算出现错误可以恢复
      修改记录	:
*****************************************************/

int BackupData()
{
	int ret=0;
	char logic_date[8+1]="";


	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}
	//备份交易明细表，ykt_cur.T_t_tif_tradelog------>ykt_his.T_t_tif_tradelog
	//ret=DB_t_tif_tradelog_open_select_by_cur2_and_enteract_date(logic_date);
	ret=Db_t_tif_tradelog_backup_by_bak_date(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Db_t_tif_tradelog_backup_by_bak_date error,errcode=[%d]",ret);
		return 	ret;
	}

	//备份流水表，ykt_cur.T_t_tif_tradeserial------>ykt_his.T_t_tif_tradeserial_his
	ret=Db_t_tif_tradeserial_backup_by_bak_date(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Db_t_tif_tradeserial_backup_by_bak_date error,errcode=[%d]",ret);
		return 	ret;
	}
	//备份门禁流水表
	ret=Db_v_door_txdtl_his_backup();
	if(ret)
	{
		writelog(LOG_ERR,"Db_v_door_txdtl_his_backup error,errcode=[%d]",ret);
	}
	/*
	ret=DB_t_tif_tradelog_open_with_hold_select_by_cur1();
	if(ret)
	{
		DB_t_tif_tradelog_close_select_by_cur1();
		writelog(LOG_ERR,"DB_t_tif_tradelog_open_with_hold_select_by_cur1 error,errcode=[%d]",ret);
		db_rollback();
		return 	ret;
	}
	getsystime(backup_time);

	while(1)
	{
		memset(&t_tradelog,0,sizeof(t_tradelog));
		ret=DB_t_tif_tradelog_fetch_select_by_cur1(&t_tradelog);
		if(ret)
		{
			DB_t_tif_tradelog_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_tradelog table!");
						break;
					}
				else		break;
			}
			else
				writelog(LOG_ERR,"DB_t_tif_tradelog_fetch_select_by_cur1 error,errcode=[%d]!",ret);
				return   ret;
		}
		cnt++;
		//赋值
		strncpy(t_tradelog_his.bak_date,logic_date,sizeof(t_tradelog_his.bak_date));
		//getsystime(t_tradelog_his.bak_time);
		strncpy(t_tradelog_his.bak_time,backup_time,sizeof(t_tradelog_his.bak_time));
		t_tradelog_his.serino             =t_tradelog.serino    ;
		t_tradelog_his.seri_type          =t_tradelog.seri_type ;
		t_tradelog_his.fee_type           =t_tradelog.fee_type  ;
		strncpy(t_tradelog_his.act_id       ,t_tradelog.act_id      ,sizeof(t_tradelog_his.act_id       ));
		strncpy(t_tradelog_his.subno        ,t_tradelog.subno       ,sizeof(t_tradelog_his.subno        ));
		strncpy(t_tradelog_his.other_actid  ,t_tradelog.other_actid ,sizeof(t_tradelog_his.other_actid  ));
		strncpy(t_tradelog_his.other_subno  ,t_tradelog.other_subno ,sizeof(t_tradelog_his.other_subno  ));
		t_tradelog_his.outorin            =t_tradelog.outorin       ;
		t_tradelog_his.op_fee             =t_tradelog.op_fee        ;
		t_tradelog_his.new_fee            =t_tradelog.new_fee       ;
		t_tradelog_his.cur_frozebala		=t_tradelog.cur_frozebala;
		t_tradelog_his.warrant_type       =t_tradelog.warrant_type  ;
		strncpy(t_tradelog_his.warrant_no   ,t_tradelog.warrant_no  ,sizeof(t_tradelog_his.warrant_no   ));
		strncpy(t_tradelog_his.operate_date ,t_tradelog.operate_date,sizeof(t_tradelog_his.operate_date ));
		strncpy(t_tradelog_his.operate_time  ,t_tradelog.operate_time ,sizeof(t_tradelog_his.operate_time ));
		strncpy(t_tradelog_his.collect_date ,t_tradelog.collect_date,sizeof(t_tradelog_his.collect_date ));
		strncpy(t_tradelog_his.collect_time  ,t_tradelog.collect_time ,sizeof(t_tradelog_his.collect_time ));
		strncpy(t_tradelog_his.enteract_date,t_tradelog.enteract_date,sizeof(t_tradelog_his.enteract_date));
		strncpy(t_tradelog_his.enteract_time ,t_tradelog.enteract_time,sizeof(t_tradelog_his.enteract_time ));
		t_tradelog_his.maindevice_id      =t_tradelog.maindevice_id ;
		t_tradelog_his.device_id          =t_tradelog.device_id     ;
		t_tradelog_his.annex              =t_tradelog.annex         ;
		strncpy(t_tradelog_his.record_oper  ,t_tradelog.record_oper ,sizeof(t_tradelog_his.record_oper  ));
		strncpy(t_tradelog_his.check_oper   ,t_tradelog.check_oper  ,sizeof(t_tradelog_his.check_oper   ));
		strncpy(t_tradelog_his.write_oper   ,t_tradelog.write_oper  ,sizeof(t_tradelog_his.write_oper   ));
		strncpy(t_tradelog_his.reserve_1    ,t_tradelog.reserve_1   ,sizeof(t_tradelog_his.reserve_1  ));
		strncpy(t_tradelog_his.reserve_2    ,t_tradelog.reserve_2   ,sizeof(t_tradelog_his.reserve_2  ));
		strncpy(t_tradelog_his.reserve_3    ,t_tradelog.reserve_3   ,sizeof(t_tradelog_his.reserve_3  ));
		strncpy(t_tradelog_his.comments    ,t_tradelog.comments   ,sizeof(t_tradelog_his.comments   ));

		ret=DB_t_tif_tradelog_his_add(&t_tradelog_his);
		if(ret)
		{
			DB_t_tif_tradelog_close_select_by_cur1();
			writelog(LOG_ERR,"DB_t_tif_tradelog_his_add record[%d] error,err[%d]",cnt,ret);
			db_rollback();
			return 	ret;
		}
		if(cnt%1000==0)
		{
			ret=db_commit();
			if(ret)
			{
				DB_t_tif_tradelog_close_select_by_cur1();
				writelog(LOG_ERR,"db_commit ret[%d]",ret);
				db_rollback();
				return 	ret;
			}

		}
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	DB_t_tif_tradelog_close_select_by_cur1();
	writelog(LOG_INFO,"Backup t_tif_tradelog succeed!,record=[%d]",cnt);
	//备份流水表，ykt_cur.T_t_tif_tradeserial------>ykt_his.T_t_tif_tradeserial_his

	getsystime(backup_time);
	cnt=0;
	ret=DB_t_tif_tradeserial_open_with_hold_select_by_cur2();
	if(ret)
	{
		DB_t_tif_tradeserial_close_select_by_cur2();
		writelog(LOG_ERR,"DB_t_tif_tradeserial_open_select_by_cur2 error,errcode=[%d]",ret);
		db_rollback();
		return 	ret;
	}
	while(1)
	{
		memset(&t_tradeserial,0,sizeof(t_tradeserial));
		memset(&t_tradeserial_his,0,sizeof(t_tradeserial_his));
		ret=DB_t_tif_tradeserial_fetch_select_by_cur2(&t_tradeserial);
		if(ret)
		{
			DB_t_tif_tradeserial_close_select_by_cur2();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't record from t_tif_tradeserial table!");
					return   0;
				}
				else		break;
			}
			else
			{
				writelog(LOG_DEBUG,"DB_t_tif_tradeserial_fetch_select_by_cur2 error,errcode[%d],record[%d]!",ret,cnt);
				return   ret;
			}
		}
		cnt++;
		//赋值
		strncpy(t_tradeserial_his.bak_date,logic_date,sizeof(t_tradeserial_his.bak_date));
		//getsystime(t_tradeserial_his.bak_time);
		strncpy(t_tradeserial_his.bak_time,backup_time,sizeof(t_tradeserial_his.bak_time));
		t_tradeserial_his.serial_no      =t_tradeserial.serial_no     ;
		t_tradeserial_his.other_seri_no  =t_tradeserial.other_seri_no ;
		t_tradeserial_his.serial_type    =t_tradeserial.serial_type   ;
		t_tradeserial_his.serial_state   =t_tradeserial.serial_state  ;
		strncpy(t_tradeserial_his.operate_date   ,t_tradeserial.operate_date  	,sizeof(t_tradeserial_his.operate_date   ));
		strncpy(t_tradeserial_his.operate_time   ,t_tradeserial.operate_time  	,sizeof(t_tradeserial_his.operate_time   ));
		strncpy(t_tradeserial_his.collect_date   ,t_tradeserial.collect_date  	,sizeof(t_tradeserial_his.collect_date   ));
		strncpy(t_tradeserial_his.collect_time   ,t_tradeserial.collect_time  	,sizeof(t_tradeserial_his.collect_time   ));
		strncpy(t_tradeserial_his.enteract_date  ,t_tradeserial.enteract_date 	,sizeof(t_tradeserial_his.enteract_date  ));
		strncpy(t_tradeserial_his.enteract_time  ,t_tradeserial.enteract_time 	,sizeof(t_tradeserial_his.enteract_time  ));
		t_tradeserial_his.maindevice_id  =t_tradeserial.maindevice_id ;
		t_tradeserial_his.device_id      =t_tradeserial.device_id     ;
		strncpy(t_tradeserial_his.devphy999_id   ,t_tradeserial.devphy999_id  	,sizeof(t_tradeserial_his.devphy999_id   ));
		strncpy(t_tradeserial_his.showid         ,t_tradeserial.showid        	,sizeof(t_tradeserial_his.showid         ));
		t_tradeserial_his.card_id        =t_tradeserial.card_id       ;
		t_tradeserial_his.purse_id       =t_tradeserial.purse_id      ;
		t_tradeserial_his.trade_count    =t_tradeserial.trade_count   ;
		t_tradeserial_his.trade_fee      =t_tradeserial.trade_fee     ;
		t_tradeserial_his.in_balance     =t_tradeserial.in_balance    ;
		t_tradeserial_his.out_balance    =t_tradeserial.out_balance   ;
		t_tradeserial_his.deposit_fee    =t_tradeserial.deposit_fee   ;
		t_tradeserial_his.in_fee         =t_tradeserial.in_fee        ;
		t_tradeserial_his.cost_fee       =t_tradeserial.cost_fee      ;
		t_tradeserial_his.boardfee=t_tradeserial.boardfee;
		strncpy(t_tradeserial_his.oldpwd         ,t_tradeserial.oldpwd        	,sizeof(t_tradeserial_his.oldpwd         ));
		strncpy(t_tradeserial_his.newpwd         ,t_tradeserial.newpwd        	,sizeof(t_tradeserial_his.newpwd         ));
		t_tradeserial_his.customer_id    =t_tradeserial.customer_id   ;
		strncpy(t_tradeserial_his.oper_code      ,t_tradeserial.oper_code     	,sizeof(t_tradeserial_his.oper_code      ));
		strncpy(t_tradeserial_his.out_account_id ,t_tradeserial.out_account_id	,sizeof(t_tradeserial_his.out_account_id ));
		strncpy(t_tradeserial_his.in_account_id  ,t_tradeserial.in_account_id 	,sizeof(t_tradeserial_his.in_account_id  ));
		strncpy(t_tradeserial_his.b_act_id       ,t_tradeserial.b_act_id      	,sizeof(t_tradeserial_his.b_act_id       ));
		t_tradeserial_his.sys_id         =t_tradeserial.sys_id        ;
		t_tradeserial_his.condition_id   =t_tradeserial.condition_id  ;
		strncpy(t_tradeserial_his.is_online      ,t_tradeserial.is_online     	,sizeof(t_tradeserial_his.is_online      ));
		t_tradeserial_his.tmark          =t_tradeserial.tmark         ;
		strncpy(t_tradeserial_his.dev_auth       ,t_tradeserial.dev_auth      	,sizeof(t_tradeserial_his.dev_auth       ));
		t_tradeserial_his.comu_ver       =t_tradeserial.comu_ver      ;
		t_tradeserial_his.run_reason     =t_tradeserial.run_reason    ;
		strncpy(t_tradeserial_his.crc            ,t_tradeserial.crc             ,sizeof(t_tradeserial_his.crc            ));
		t_tradeserial_his.ecode          =t_tradeserial.ecode           ;
		t_tradeserial_his.reviseserial_no=t_tradeserial.reviseserial_no ;
		strncpy(t_tradeserial_his.reserve_1      ,t_tradeserial.reserve_1       ,sizeof(t_tradeserial_his.reserve_1      ));
		strncpy(t_tradeserial_his.reserve_2      ,t_tradeserial.reserve_2       ,sizeof(t_tradeserial_his.reserve_2      ));
		strncpy(t_tradeserial_his.reserve_3      ,t_tradeserial.reserve_3       ,sizeof(t_tradeserial_his.reserve_3      ));

		ret=DB_t_tif_tradeserial_his_add(&t_tradeserial_his);
		if(ret)
		{
			DB_t_tif_tradeserial_close_select_by_cur2();
			writelog(LOG_ERR,"Insert history tradelog table record[%d] error,err[%d]",cnt,ret);
			db_rollback();
			return 	ret;
		}


		if(cnt%1000==0)
		{
			ret=db_commit();
			if(ret)
			{
				DB_t_tif_tradeserial_close_select_by_cur2();
				writelog(LOG_ERR,"db_commit ret[%d]",ret);
				db_rollback();
				return 	ret;
			}

		}

	}
	DB_t_tif_tradeserial_close_select_by_cur2();
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	writelog(LOG_INFO,"Backup t_tif_tradeserial succeed!,record=[%d]",cnt);
	*/

	return 0;
}

/****************************************************
      作    者	: hhd
      创建日期: 2004-10-19 11:34
      描    述 	: 备份帐户数据库
      修改记录:
*****************************************************/
int BackupAccount()
{
	int cnt=0;
	int ret=0;
	char logic_date[8+1]="";
	T_t_aif_account		account;
	T_t_tif_act_daysum 	act_daysum;

	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}

	ret=DB_t_aif_account_open_select_for_update_by_cur2();
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_open_select_by_cur1 error,errcode=[%d]",ret);
		return 	ret;
	}

	while(1)
	{
		memset(&account,0,sizeof(account));
		memset(&act_daysum,0,sizeof(act_daysum));
		ret=DB_t_aif_account_fetch_select_by_cur2(&account);
		if(ret)
		{
			DB_t_aif_account_close_select_by_cur2();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_aif_account table!");
						return   0;
					}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		//更新帐户表中的前次余额字段
		account.last_bala=account.cur_bala;
		account.last_freebala=account.cur_freebala;
		account.last_frozebala=account.cur_frozebala;
		//更新帐户表中卡库不平次数字段
		if(account.act_type==ACCTYPE_PERMAIN)
		{
			if(account.cur_freebala!=account.card_balance)
			{
				account.nobala_num++;
			}
			else
			{
				account.nobala_num=0;
			}
		}
		//更新帐户表
		ret=DB_t_aif_account_update_lock_by_cur2(&account);
		if(ret)
		{
			writelog(LOG_ERR,"Update t_aif_account error,record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	ret;
		}
		////生成报表过程结束
	 }
	DB_t_aif_account_close_select_by_cur2();
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		return -1;
	}

	writelog(LOG_INFO,"Backup t_aif_account succeed!,record=[%d]",cnt);
	return 0;
}


/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 计算管理费函数，原先考虑在日结过程中统一考虑
      			  计算管理费操作，现由杜叶飞进行处理
      修改记录	:
*****************************************************/
int CalculateMngFee()
{
	return 0;
}

/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 管理费退费操作，目前研究决定没月初统一退费
      修改记录	:
*****************************************************/

int WithdrowMngFee()
{
	return 0;
}

/****************************************************
      作    者	: hhd
      创建日期: 2004-8-13 9:34
      描    述 	: 生成卡库不平报表过程，由视图中提取数据添加到表中
      修改记录:
*****************************************************/

int CardDBNotBalance()
{
	T_t_tif_report_carddb_nobalance	t_no_balance;
	T_v_tif_report_carddb_nobalance v_no_balance;
	T_t_cif_customer				t_customer;
	T_t_tif_act_daysum			t_daysum;
	int ret=0;
	int cnt=0;
	char logic_date[10+1]="";
	char	buffer[100+1]="";
	//char sCardState[5] = "";
	double	carddb_nobala_money=0;
	int	carddb_nobala_times=0;


	double second;
	char	forward_date[10+1]="";
	char tmp_date[20+1]="";

	//取全局参数最大卡库不平金额
	ret=GetParameter(GLOBE_MAX_CARDDB_NOBALANCE_MONEY, buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter error,errcode[%d]",ret);
		return 	ret;
	}
	carddb_nobala_money=atof(buffer);
	//取全局参数最大卡库不平天数
	memset(buffer,0,sizeof(buffer));
	ret=GetParameter(GLOBE_MAX_CARDDB_NOBALANCE_TIMES,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter error,errcode[%d]",ret);
		return 	ret;
	}
	carddb_nobala_times=atoi(buffer);
	//取系统逻辑日期
	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}

	//得到逻辑日期前“系统允许最大不平天数”的日期
	strcpy(tmp_date,logic_date);
	//strcat(tmp_date,"000000");
	ret=datetime2second(tmp_date, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	second=second-(carddb_nobala_times-1)*24*60*60;
	ret=second2datetime(second, tmp_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}
	Strncpy(forward_date,tmp_date,sizeof(forward_date));



	ret=DB_t_tif_report_carddb_nobalance_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete from t_tif_report_carddb_nobalance where date=[%s],errcode=[%d]",logic_date,ret);
		goto L_RETU;
	}

	ret=DB_v_tif_report_carddb_nobalance_open_select_by_c1();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_report_carddb_nobalance err [%d]",ret);
		goto L_RETU;
	}

	while(1)
	{
		memset(&v_no_balance,0,sizeof(v_no_balance));
		memset(&t_no_balance,0,sizeof(t_no_balance));
		memset(&t_daysum,0,sizeof(t_daysum));

		ret=DB_v_tif_report_carddb_nobalance_fetch_select_by_c1(&v_no_balance);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't CardDB not balance record!");
					break;
				}
				else	 break;
			}
			else
			{
				writelog(LOG_DEBUG,"DB_v_tif_report_carddb_nobalance_fetch_select_by_c1 error,errcode=[%d],cnt=[%d]",ret,cnt);
				goto L_RETU;
			}
		}
		cnt++;

		////生成报表过程开始
		strncpy(t_no_balance.balance_date,logic_date,sizeof(t_no_balance.balance_date));
		strncpy(t_no_balance.account_id,v_no_balance.account_id,sizeof(t_no_balance.account_id));
		strncpy(t_no_balance.cut_name,v_no_balance.cut_name,sizeof(t_no_balance.cut_name));
		strncpy(t_no_balance.stuemp_no,v_no_balance.stuemp_no,sizeof(t_no_balance.stuemp_no));
		t_no_balance.type_id=v_no_balance.card_type;
		ret=DB_t_cif_customer_read_by_cut_id(v_no_balance.customer_id,&t_customer);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_cif_customer_read_by_cut_id error,v_no_balance.customer_id=[%d],errcode=[%d]",v_no_balance.customer_id,ret);
			goto L_RETU;
		}
		strncpy(t_no_balance.dept_name,t_customer.classdept_name,sizeof(t_no_balance.dept_name));
		t_no_balance.db_bala=v_no_balance.db_bala;
		t_no_balance.card_bala=v_no_balance.card_bala;
		t_no_balance.diff_bala=v_no_balance.diff_bala;
		t_no_balance.nobala_num=v_no_balance.nobala_num;

		ret=DB_t_tif_report_carddb_nobalance_add(&t_no_balance);
		if(ret)
		{
			writelog(LOG_ERR,"Insert t_tif_report_carddb_nobalance record[%d] err[%d]",cnt,ret);
			goto L_RETU;
		}
/*		//对卡库不平进行处理
		ret=GetCardState(v_no_balance.card_id,sCardState);	//得到卡状态
		if(ret)
		{
			writelog(LOG_ERR,"GetCardState error,err[%d],card_id[%d]",ret,v_no_balance.card_id);
			goto L_RETU;
		}
		if(STATE_TRUE!=sCardState[CARDSTAT_TYPE_FREEZE])	//对于已经冻结的帐户不进行处理
		{
			//如果不平金额超过最大值限制，则直接冻结，等待人工处理
			if(v_no_balance.diff_bala>carddb_nobala_money)	//进行冻结操作,人工处理
			{
				ret=freezecard(v_no_balance.card_id,v_no_balance.customer_id,"system", 0, 0);
				if(ret)
				{
					writelog(LOG_ERR,"freezecard error,err[%d],card_id[%d]",ret,v_no_balance.card_id);
				}
				continue;
			}
			//如果不平金额小于最大值，但是不平次数超过限制，进行调账处理，进行补助操作
			if(v_no_balance.nobala_num>carddb_nobala_times)
			{
				//暂时考虑不成熟，屏蔽代码
				//卡大库小，冻结账户，到前台进行改写卡操作

				if(v_no_balance.db_bala<v_no_balance.card_bala)
				{
					ret=freezecard(v_no_balance.card_id,v_no_balance.customer_id,"system", 0, 0);
					if(ret)
					{
						writelog(LOG_ERR,"freezecard error,err[%d],card_id[%d]",ret,v_no_balance.card_id);
					}
				}
				//卡小库大，补记一条流水，作为丢帐处理
				if(v_no_balance.db_bala>v_no_balance.card_bala)
				{
					memset(&tradeserial,0,sizeof(tradeserial));
					memset(&t_daysum,0,sizeof(t_daysum));

					tradeserial.serial_type=TXCODE_MAKEUPSERIAL;							//添加交易代码
					tradeserial.card_id=v_no_balance.card_id;									//添加卡号字段
					tradeserial.customer_id=v_no_balance.customer_id;							//添加客户号字段
					strncpy(tradeserial.out_account_id,v_no_balance.account_id,sizeof(tradeserial.out_account_id)-1);
					//读取系统允许最大不平天数前的账户的账户的信息
					ret=DB_t_tif_act_daysum_read_by_operate_date_and_account_id(forward_date, v_no_balance.account_id,&t_daysum);
					if(ret)
					{
						writelog(LOG_ERR,"DB_t_tif_act_daysum_read_by_operate_date_and_account_id error,errcode[%d],forward_date=[%s],account_id=[%s]",ret,forward_date,v_no_balance.account_id);
						goto L_RETU;
					}
					tradeserial.trade_fee=t_daysum.cur_freebala-t_daysum.card_balance;			//添加交易金额字段
					//如果n天前的账户卡大库小，则系统冻结账户不作处理
					if(tradeserial.trade_fee<=0)
					{
						ret=freezecard(v_no_balance.card_id,v_no_balance.customer_id,"system", 0, 0);
						if(ret)
						{
							writelog(LOG_ERR,"freezecard error,err[%d],card_id[%d]",ret,v_no_balance.card_id);
						}
						continue;
					}
					writelog(LOG_ERR,"in_account=[%s]",tradeserial.in_account_id);
					ret=add_serialno_makeup(&tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"add_serialno_makeup err,errcode[%d]",ret);
						goto L_RETU;
					}
					ret=process_makeup(&tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"process_makeup err,errcode[%d]",ret);
						goto L_RETU;
					}
				}
				continue;
			}


		}
	*/
		////生成报表过程结束
	 }


	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		goto L_RETU;
	}

	writelog(LOG_DEBUG,"There have CardDB not balance record[%d]!",cnt);
	return 0;

L_RETU:
	//回滚事务
	db_rollback();
	return -1;

}

/****************************************************
      作    者	: hhd
      创建日期: 2004-8-13 9:34
      描    述 	: 核对每个人的帐务，检查是否有入错帐的情况，同时生成
      			  		个人帐务不符记录报表
      修改记录:
*****************************************************/

int CheckPersonAccount()
{
	T_t_tif_report_erracc	t_erracc;
	T_v_tif_report_erracc	v_erracc;
	T_t_cif_customer		t_customer;
	T_t_aif_account		t_account;
//	T_t_aif_account		account;
	int ret=0;
	int cnt=0;
	char logic_date[10+1]="";

	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}

	//开始生成个人对帐不符报表
	ret=DB_t_tif_report_erracc_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete from report_carddb_nobalance where date=[%s],errcode=[%d]",logic_date,ret);
		return 	ret;
	}

	ret=DB_v_tif_report_erracc_open_select_by_c1();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_report_erracc view error,errorcode[%d]",ret);
		return 	E_DB_VIEW_ERRACC_R;
	}

	while(1)
	{
		memset(&v_erracc,0,sizeof(v_erracc));
		memset(&t_erracc,0,sizeof(t_erracc));
		memset(&t_customer,0,sizeof(t_customer));
		memset(&t_account,0,sizeof(t_account));
		ret=DB_v_tif_report_erracc_fetch_select_by_c1(&v_erracc);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't error account record!");
					return   0;
				}
				else		break;
			}
			else
				return   E_DB_VIEW_ERRACC_R;
		}
		cnt++;
		////生成报表过程开始

		//取耿刚写好取逻辑时间函数
		strncpy(t_erracc.balance_date,logic_date,sizeof(t_erracc.balance_date));
		strncpy(t_erracc.account_id,v_erracc.account_id,sizeof(t_erracc.account_id));
		strncpy(t_erracc.cut_name,v_erracc.cut_name,sizeof(t_erracc.cut_name));
		strncpy(t_erracc.stuemp_no,v_erracc.stuemp_no,sizeof(t_erracc.stuemp_no));
		t_erracc.type_id=v_erracc.card_type;
		//取客户的部门名称
		ret=DB_t_aif_account_read_by_account_id(t_erracc.account_id,&t_account);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id err[%d]",ret);
			return 	ret;
		}
		ret=DB_t_cif_customer_read_by_cut_id(t_account.customer_id,&t_customer);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_cif_customer_read_by_cut_id err[%d],customer_id=[%d]",ret,t_account.customer_id);
			return 	ret;
		}
		strncpy(t_erracc.dept_name,t_customer.classdept_name,sizeof(t_erracc.dept_name));

		t_erracc.last_bala=v_erracc.last_bala;
		t_erracc.cur_bala=v_erracc.cur_bala;
		t_erracc.trade_amt=v_erracc.sum_trade;
		t_erracc.diff_bala=t_erracc.last_bala-t_erracc.last_bala-t_erracc.trade_amt;
		//写入数据
		ret=DB_t_tif_report_erracc_add(&t_erracc);
		if(ret)
		{
			writelog(LOG_ERR,"Insert T_TIF_Report_ErrAcc record[%d] err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_TABLE_ERRACC_I;
		}

		////生成报表过程结束
	 }

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		return -1;
	}
	writelog(LOG_DEBUG,"There have error account record[%d]!",cnt);
	return 0;
}

/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 按照设计，核对过个人帐务后，再核对总帐
      修改记录	:
*****************************************************/

int CheckTotalAccount()
{
	T_v_tif_report_totalacc	v_totalacc;
	int ret=0;

	ret=DB_v_tif_report_totalacc_open_select_by_c1();
	if(ret)
	{
		writelog(LOG_ERR,"Open V_TIF_Report_TotalAcc err [%d]",ret);
		return 	E_DB_VIEW_TOTALACC_R;
	}

	memset(&v_totalacc,0,sizeof(v_totalacc));
	ret=DB_v_tif_report_totalacc_fetch_select_by_c1(&v_totalacc);
	if(ret)
	{
		if(ret==DB_NOTFOUND)
		{
			writelog(LOG_ERR,"There havn't record!");
			return   E_DB_VIEW_TOTALACC_N;
		}
		else
			return   E_DB_VIEW_ERRACC_R;
	}
	DB_v_tif_report_totalacc_close_select_by_c1();
	if(v_totalacc.total)
	{
		writelog(LOG_ERR,"Total account is not balance,Please attention!");
		return 	E_TOTAL_ACC;
	}
	else
		writelog(LOG_DEBUG,"Total account is balance!");
	return 0;
}

/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 生成运行情况报表过程
      修改记录	:
*****************************************************/

int CreateActiveReport()
{
	int ret=0;
	int cnt=0;

	double second=0;
	double temp=0;
	char logic_date[10+1]="";
	char	forward_date[10+1]="";
	char tmp_date[20+1]="";

	double total_acc_add_num=0;
	double total_acc_add_amt=0;
	double total_shp_add_num=0;
	double total_shp_add_amt=0;
	double total_dep_add_amt=0;
	double total_earn_add_amt=0;
	double total_in_amt=0;
	double total_cost_amt=0;
	double total_deposit_amt=0;
	double total_cash_amt=0;
	double total_bank_add_amt=0;
	double total_check_add_amt=0;
	double total_outlay_add_amt=0;
	double total_down_subsidy_amt=0;
	double total_up_subsidy_amt=0;

	T_v_tif_report_active	v_active;
	T_t_tif_report_active	t_active;
	T_t_tif_report_active	t_forward_active;
	T_t_aif_account		t_account;


	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}

	//得到逻辑时间的前一天
	strcpy(tmp_date,logic_date);
//	strcat(tmp_date,"000000");
	ret=datetime2second(tmp_date, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	second=second-24*60*60;
	ret=second2datetime(second, tmp_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}

	Strncpy(forward_date,tmp_date,sizeof(forward_date));

	//writelog(LOG_ERR,"logic_date=[%s]",logic_date);
	//writelog(LOG_ERR,"forward_date=[%s]",forward_date);


	ret=DB_t_tif_report_active_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_tif_report_active_del_by_balance_date error,errcode=[%d]",ret);
		return ret;
	}
	ret=DB_v_tif_report_active_open_select_by_cur1();
	if(ret)
	{
		writelog(LOG_ERR,"DB_v_tif_report_active_open_select_by_cur1 error,errcode=[%d]",ret);
		return ret;
	}

	while(1)
	{
		memset(&t_active,0,sizeof(t_active));
		strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date));
		ret=DB_v_tif_report_active_fetch_select_by_cur1(&v_active);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
					writelog(LOG_ERR,"There havn't one record in v_tif_report_active at least!");
					//暂时为了调试，屏蔽break，如果每有前一天数据就置空
					break;
			}
			else
				return   ret;
		}

		cnt++;

		//strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date));
		t_active.seri_type=v_active.serial_type;
		t_active.trade_number=v_active.trade_count;
		//考虑可以去掉该字段
		t_active.trade_amt=0;
		t_active.acc_addnum=v_active.acc_add_num;
		t_active.acc_amt=v_active.acc_add_amt;
		t_active.shop_addnum=v_active.shp_add_num;
		t_active.shop_amt=v_active.shp_add_amt;
		t_active.dep_amt=v_active.dep_add_amt;
		t_active.earn_amt=v_active.earn_add_amt;
		t_active.mng_amt=v_active.in_amt;
		t_active.cost_amt=v_active.cost_amt;
		t_active.ensure_amt=v_active.deposit_amt;
		t_active.cash_amt=v_active.cash_add_amt;
		t_active.bank_amt=v_active.bank_add_amt;
		t_active.check_add_amt=v_active.check_add_amt;
		t_active.outlay_add_amt=v_active.outlay_add_amt;
		t_active.down_subsidy_amt=v_active.down_subsidy_amt;
		t_active.up_subsidy_amt=v_active.up_subsidy_amt;
		//记录合计变化量
		total_acc_add_num =total_acc_add_num +v_active.acc_add_num;
		total_acc_add_amt =total_acc_add_amt +v_active.acc_add_amt;
		total_shp_add_num =total_shp_add_num +v_active.shp_add_num;
		total_shp_add_amt =total_shp_add_amt +v_active.shp_add_amt;
		total_dep_add_amt=total_dep_add_amt+v_active.dep_add_amt;
		total_earn_add_amt=total_earn_add_amt+v_active.earn_add_amt;
		total_in_amt      =total_in_amt      +v_active.in_amt;
		total_cost_amt    =total_cost_amt    +v_active.cost_amt;
		total_deposit_amt =total_deposit_amt +v_active.deposit_amt;
		total_cash_amt    =total_cash_amt    +v_active.cash_add_amt;
		total_bank_add_amt=total_bank_add_amt+v_active.bank_add_amt;
		total_check_add_amt=total_check_add_amt+v_active.check_add_amt;
		total_outlay_add_amt=total_outlay_add_amt+v_active.outlay_add_amt;
		total_down_subsidy_amt=total_down_subsidy_amt+v_active.down_subsidy_amt;
		total_up_subsidy_amt=total_up_subsidy_amt+v_active.up_subsidy_amt;

		ret=DB_t_tif_report_active_add(&t_active);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_tif_report_active_add error,record=[%d],errcode=[%d]",cnt,ret);
			return ret;
		}
	}

	//写三个总数(上次+本次+变化情况)
	//写上次状态---读取前一天的结算数据
	memset(&t_active,0,sizeof(t_active));
	ret=DB_t_tif_report_active_read_by_balance_date_and_seri_type(forward_date,9002,&t_forward_active);
	if(ret)
	{
		if(ret==DB_NOTFOUND)
		{
			writelog(LOG_ERR,"There havn't one record at least!");
			//暂时为了调试，屏蔽break，如果每有前一天数据就置空
			//break;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_tif_report_active_read_by_balance_date_and_seri_type error,forward_date=[%s],seri_type=[9002],errcode=[%d]",forward_date,ret);
			return ret;
		}
	}
	else
	{
		t_active.trade_number =t_forward_active.trade_number ;
		//t_active.trade_amt  =t_forward_active.trade_amt    ;
		t_active.acc_addnum   =t_forward_active.acc_addnum   ;
		t_active.acc_amt      =t_forward_active.acc_amt      ;
		t_active.shop_addnum  =t_forward_active.shop_addnum  ;
		t_active.shop_amt     =t_forward_active.shop_amt     ;
		t_active.dep_amt	=t_forward_active.dep_amt;
		t_active.earn_amt =t_forward_active.earn_amt;
		t_active.mng_amt      =t_forward_active.mng_amt      ;
		t_active.cost_amt     =t_forward_active.cost_amt     ;
		t_active.ensure_amt   =t_forward_active.ensure_amt   ;
		t_active.cash_amt     =t_forward_active.cash_amt     ;
		t_active.bank_amt     =t_forward_active.bank_amt     ;
		t_active.check_add_amt=t_forward_active.check_add_amt;
		t_active.outlay_add_amt=t_forward_active.outlay_add_amt;
		t_active.down_subsidy_amt=t_forward_active.down_subsidy_amt;
		t_active.up_subsidy_amt=t_forward_active.up_subsidy_amt;
	}
	strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date));
	t_active.seri_type    =9001;

	ret=DB_t_tif_report_active_add(&t_active);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_report_active_add error,errcode=[%d]",ret);
		return ret;
	}

	//写本次状态---读取当前帐户的真实余额
	memset(&t_active,0,sizeof(t_active));
	strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date)-1);
	t_active.seri_type=9002;
	t_active.trade_number=0;

	t_active.trade_amt=0;

	//temp=(double)t_active.acc_addnum;
	ret=Get_Account_Count_by_AccType(&temp,ACCTYPE_PERMAIN);
	if(ret)
	{
		writelog(LOG_ERR,"Get_Account_Count_by_AccType error,errcode=[%d]",ret);
		return ret;
	}

	t_active.acc_addnum=(int)temp;
	//writelog(LOG_ERR,"acc_addnum=[%f]",temp);

	//ret=Get_Account_SumMoney_by_AccType(double *SumMoney,int acctype);
	ret=Get_Account_SumMoney_by_AccType(&t_active.acc_amt,ACCTYPE_PERMAIN);
	if(ret)
	{
		writelog(LOG_ERR,"Get_Account_SumMoney_by_AccType error,errcode=[%d]",ret);
		return ret;
	}

	//temp=(double)(t_active.shop_addnum);
	//t_active.acc_amt=temp;
	//writelog(LOG_ERR,"acc_amt=[%f]",temp);

	ret=Get_Account_Count_by_AccType(&temp,ACCTYPE_SHOPMAIN);
	if(ret)
	{
		writelog(LOG_ERR,"Get_Account_Count_by_AccType error,errcode=[%d]",ret);
		return ret;
	}
	//ret=Get_Account_SumMoney_by_AccType(double *SumMoney,int acctype);

	//temp=(double)(t_active.shop_amt);
	t_active.shop_addnum=(int)temp;
	//writelog(LOG_ERR,"shop_addnum=[%f]",temp);
	ret=Get_Account_SumMoney_by_AccType(&t_active.shop_amt,ACCTYPE_SHOPMAIN);
	if(ret)
	{
		writelog(LOG_ERR,"Get_Account_SumMoney_by_AccType error,errcode=[%d]",ret);
		return ret;
	}
	//t_active.shop_amt=(int)temp;
	//writelog(LOG_ERR,"shop_amt=[%f]",temp);

	ret=DB_t_aif_account_read_by_account_id("5031",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.dep_amt=t_account.cur_bala;
	t_account.cur_bala=0;

	ret=DB_t_aif_account_read_by_account_id("5041",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.earn_amt=t_account.cur_bala;
	t_account.cur_bala=0;

	ret=DB_t_aif_account_read_by_account_id("5011",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.mng_amt=t_account.cur_bala;
	t_account.cur_bala=0;
	//writelog(LOG_ERR,"mng_amt=[%f]",temp);
	ret=DB_t_aif_account_read_by_account_id("5021",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.cost_amt=t_account.cur_bala;
	t_account.cur_bala=0;

	ret=DB_t_aif_account_read_by_account_id("2051",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.ensure_amt=t_account.cur_bala;
	t_account.cur_bala=0;

	ret=DB_t_aif_account_read_by_account_id("1011",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.cash_amt=t_account.cur_bala;
	t_account.cur_bala=0;

	ret=DB_t_aif_account_read_by_account_id("1021",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.bank_amt=t_account.cur_bala;
	t_account.cur_bala=0;
	//取经费本的当前余额
	ret=DB_t_aif_account_read_by_account_id("1041",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.check_add_amt=t_account.cur_bala;
	t_account.cur_bala=0;
	//取支票的当前余额
	ret=DB_t_aif_account_read_by_account_id("1031",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.outlay_add_amt=t_account.cur_bala;
	t_account.cur_bala=0;
	//取下发补助的当前余额
	ret=DB_t_aif_account_read_by_account_id("1071",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.down_subsidy_amt=t_account.cur_bala;
	t_account.cur_bala=0;
	//取待下发补助的当前余额
	ret=DB_t_aif_account_read_by_account_id("2071",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.up_subsidy_amt=t_account.cur_bala;
	t_account.cur_bala=0;

/*
	t_active.acc_addnum   =t_active.acc_addnum +  total_acc_add_num;
	t_active.acc_amt      =t_active.acc_amt    +  total_acc_add_amt;
	t_active.shop_addnum  =t_active.shop_addnum+  total_shp_add_num;
	t_active.shop_amt     =t_active.shop_amt   +  total_shp_add_amt;
	t_active.mng_amt      =t_active.mng_amt    +  total_in_amt;
	t_active.cost_amt     =t_active.cost_amt   +  total_cost_amt;
	t_active.ensure_amt   =t_active.ensure_amt +  total_deposit_amt;
	t_active.cash_amt     =t_active.cash_amt   +  total_cash_amt;
	t_active.bank_amt     =t_active.bank_amt   +  total_bank_add_amt;
*/

	ret=DB_t_tif_report_active_add(&t_active);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_report_active_add error,errcode=[%d]",ret);
		return ret;
	}

	//写变化情况
	memset(&t_active,0,sizeof(t_active));
	strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date));
	t_active.seri_type=9003;
	t_active.trade_number=0;
	//t_active.trade_amt=0;
	t_active.acc_addnum=total_acc_add_num;
	t_active.acc_amt=total_acc_add_amt;
	t_active.shop_addnum=total_shp_add_num;
	t_active.shop_amt=total_shp_add_amt;
	t_active.dep_amt=total_dep_add_amt;
	t_active.earn_amt=total_earn_add_amt;
	t_active.mng_amt=total_in_amt;
	t_active.cost_amt=total_cost_amt;
	t_active.ensure_amt=total_deposit_amt;
	t_active.cash_amt=total_cash_amt;
	t_active.bank_amt=total_bank_add_amt;
	t_active.check_add_amt=total_check_add_amt;
	t_active.outlay_add_amt=total_outlay_add_amt;
	t_active.down_subsidy_amt=total_down_subsidy_amt;
	t_active.up_subsidy_amt=total_up_subsidy_amt;

	ret=DB_t_tif_report_active_add(&t_active);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_report_active_add error,errcode=[%d]",ret);
		return ret;
	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}

	return 0;
}

/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 生成操作情况报表过程，具体参照数据库设计
      			  按照讨论结果，该报表的入帐数据从交易明晰表
      			  中出，但是非入帐数据在该表中又没有，考虑如果
      			  从不同的表中出不同的数据，代码比较复杂，
      			  所以暂时该报表中的数据还是从流水表中出，
      			  等其他都定后，需要修改再针对性修改
      修改记录	:
*****************************************************/

int CreateOperReport()
{
	T_v_tif_report_oper	v_oper;
	T_t_tif_report_oper		t_oper;

	int ret=0;
	int cnt=0;
	char logic_date[10+1]="";

	//清除当天的结算数据
	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}
	ret=DB_t_tif_report_oper_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete t_tif_report_oper report error,errorcode[%d]",ret);
		return 	ret;
	}

	ret=DB_v_tif_report_oper_open_select_by_c1();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_report_oper view error,errorcode[%d]",ret);
		return 	ret;
	}

	while(1)
	{
		memset(&v_oper,0,sizeof(v_oper));
		memset(&t_oper,0,sizeof(t_oper));
		ret=DB_v_tif_report_oper_fetch_select_by_c1(&v_oper);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't record from v_tif_report_oper view!");
					break;
				}
				else
					break;
			}
			else
				return   ret;
		}
		cnt++;
		////生成报表过程开始
		strncpy(t_oper.balance_date,logic_date,sizeof(t_oper.balance_date));
		strncpy(t_oper.operator_code,v_oper.oper_code,sizeof(t_oper.operator_code));
		t_oper.seri_type=v_oper.serial_type;
		t_oper.happen_num=v_oper.trade_count;
		t_oper.acc_add_amt=v_oper.acc_add_amt;
		t_oper.shp_add_amt=v_oper.shp_add_amt;
		t_oper.happen_amt=v_oper.trade_amt;
		t_oper.dep_amt=v_oper.dep_add_amt;
		t_oper.earn_amt=v_oper.earn_add_amt;
		t_oper.bank_amt=v_oper.bank_add_amt;
		t_oper.mng_amt=v_oper.in_amt;
		t_oper.ensure_amt=v_oper.deposit_amt;
		t_oper.cost_amt=v_oper.cost_amt;
		t_oper.cash_amt=v_oper.cash_amt;
		t_oper.check_amt=v_oper.check_amt;
		t_oper.outlay_amt=v_oper.outlay_amt;
		t_oper.down_subsidy_amt=v_oper.down_subsidy_amt;
		t_oper.up_subsidy_amt=v_oper.up_subsidy_amt;
		t_oper.maindevice_id=v_oper.maindevice_id;
		t_oper.device_id=v_oper.device_id;
		ret=DB_t_tif_report_oper_add(&t_oper);
		if(ret)
		{
			writelog(LOG_ERR,"Insert t_tif_report_oper record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	ret;
		}

		////生成报表过程结束
	 }

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	return 0;

}

/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 生成商户结算报表过程，具体参照数据库设计
      修改记录	:
*****************************************************/

int CreateShopReport()
{

	T_v_tif_shopdeptfee		v_shop_balance;
	T_t_tif_report_shop_balance 	t_shop_balance;
	char path_name[256]="";
	char file_name[256]="";
	int ret=0;
	int cnt=0;
	char logic_date[10+1]="";
	int indep_shop_count=0;
	double indep_shop_sum=0;
	FILE *fp;
	char *p=getenv("BIN_PATH");


	//清除当天的结算数据
	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}

	if(p==NULL)
	{
	   	writelog(LOG_ERR,"Cann't get env HOME PATH\n");
	   	return -1;
	}
	sprintf(path_name,"%s/balalog",p);
	sprintf(file_name,"%s/shop_trans%8.8s.txt",path_name,logic_date);

	if((fp = fopen(file_name,"wb"))==NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]",file_name);
		return	-1;
	}

	ret=DB_t_tif_report_shop_balance_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete t_tif_report_shop_balance report error,errorcode[%d]",ret);
		return 	ret;
	}
	//得到独立核算商户的总数和金额
	ret=GetCountIndepShop(&indep_shop_count);
	if(ret)
	{
		writelog(LOG_ERR,"GetCountIndepShop error,errorcode[%d]",ret);
		return 	ret;
	}
	ret=GetSumIndepShop(&indep_shop_sum);
	if(ret)
	{
		writelog(LOG_ERR,"GetSumIndepShop error,errorcode[%d]",ret);
		return 	ret;
	}

	if(0!=indep_shop_count)
	{
		if(NULL==fprintf(fp,"%d	%f	%s\r\n",indep_shop_count,indep_shop_sum,logic_date));
		{
			writelog(LOG_ERR,"fprintf error,");
		}
	}

	ret=DB_v_tif_shopdeptfee_open_select_by_c5();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_shopdeptfee view error,errorcode[%d]",ret);
		return 	E_DB_SHOPDEPTFEE_R;
	}

	while(1)
	{
		memset(&v_shop_balance,0,sizeof(v_shop_balance));
		memset(&t_shop_balance,0,sizeof(t_shop_balance));
		ret=DB_v_tif_shopdeptfee_fetch_select_by_c5(&t_shop_balance);
		if(ret)
		{
			DB_v_tif_shopdeptfee_close_select_by_c5();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from T_v_tif_shopdeptfee view!");
						return   0;
					}
				else		break;
			}
			else
				return   E_DB_SHOPDEPTFEE_R;
		}
		cnt++;
		////生成报表过程开始

		//写结帐日期和总商户收入(商户消费+搭伙费收入)

		strncpy(t_shop_balance.balance_date,logic_date,sizeof(t_shop_balance.balance_date));

		t_shop_balance.total_amt=t_shop_balance.trade_amt+t_shop_balance.mng_amt;

		//判断是否为独立核算商户,借用reserve1字段为1则为独立核算
		if(0==strncmp(t_shop_balance.reserve1,"1",1))
		{
			//printf("count=[%d]\n",cnt);
			if(NULL==fprintf(fp,"%d	%f\r\n",t_shop_balance.shop_id,t_shop_balance.total_amt))
			{
				writelog(LOG_ERR,"fprintf error,");
			}
		}

		ret=DB_t_tif_report_shop_balance_add(&t_shop_balance);
		if(ret)
		{
			writelog(LOG_ERR,"Insert t_tif_report_shop_balance record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_TABLE_ERRACC_I;
		}

		////生成报表过程结束
	 }
	
	DB_v_tif_shopdeptfee_close_select_by_c5();
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	fclose(fp);
	return 0;
}
int CreateRichDebtReport()
{

	int ret=0;
	int cnt=0;
	double second;
	char logic_date[10+1]="";
	char	forward_date[10+1]="";
	char tmp_date[20+1]="";

	char path_name[256]="";
	char file_name[256]="";
	FILE *fp;
	char *p=getenv("BIN_PATH");


	T_t_tif_subject_balance t_subject_balance;
	T_t_tif_subject_balance t_forward_subject_balance;

	T_t_tif_subject		t_subject;
	//得到逻辑时间
	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}
	//得到逻辑时间的前一天
	strcpy(tmp_date,logic_date);
//	strcat(tmp_date,"000000");
	ret=datetime2second(tmp_date, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	second=second-24*60*60;
	ret=second2datetime(second, tmp_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}
	Strncpy(forward_date,tmp_date,sizeof(forward_date));

	//writelog(LOG_ERR,"logic_date=[%s]",logic_date);
	//writelog(LOG_ERR,"forward_date=[%s]",forward_date);

	if(p==NULL)
	{
	   	writelog(LOG_ERR,"Cann't get env HOME PATH\n");
	   	return -1;
	}
	sprintf(path_name,"%s/balalog",p);
	sprintf(file_name,"%s/bala_trans%8.8s.txt",path_name,logic_date);

	if((fp = fopen(file_name,"wb"))==NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]",file_name);
		return	-1;
	}

	//清除当天的结算数据
	ret=DB_t_tif_subject_balance_del_by_txdate(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete t_tif_report_rich_debt report error,errorcode[%d]",ret);
		return 	ret;
	}

	ret=DB_v_tif_acttype_trade_open_select_by_c5();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_acttype_trade view error,errorcode[%d]",ret);
		return 	E_DB_SHOPDEPTFEE_R;
	}

	while(1)
	{
		memset(&t_subject_balance,0,sizeof(t_subject_balance));
		ret=DB_v_tif_acttype_trade_fetch_select_by_c5(&t_subject_balance);
		if(ret)
		{
			DB_v_tif_acttype_close_select_by_c5();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from T_tif_acttype_trade view!");
						return   0;
					}
				else		break;
			}
			else
				return   E_DB_SHOPDEPTFEE_R;
		}
		cnt++;

		//写结算日期
		strncpy(t_subject_balance.txdate,logic_date,sizeof(t_subject_balance.txdate));
		//写期初科目余额
		//读取科目表的基本信息，供下边使用
		ret=DB_t_tif_subject_read_by_subno(t_subject_balance.subno,&t_subject);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_tif_subject_read_by_subno error,errorcode[%d]",ret);
			return 	E_DB_SUBJECT_R;
		}
		//读取前一天的科目余额表
     		ret=DB_t_tif_subject_balance_read_by_txdate_and_subno(forward_date,t_subject_balance.subno,&t_forward_subject_balance);
		if(ret)
		{
			if(100==ret)
			{
				t_subject_balance.bbala_flag=t_subject.direct;
				t_subject_balance.bbala=0;
			}
			else
			{
				writelog(LOG_ERR,"Read from t_tif_subject_balance error,errorcode[%d]",ret);
				return 	E_DB_SHOPDEPTFEE_R;
			}
		}
		else
		{
			t_subject_balance.bbala_flag=t_forward_subject_balance.endbala_flag;
			t_subject_balance.bbala=t_forward_subject_balance.endbala;
		}
		//取科目表中的科目性质
		DB_t_tif_subject_read_by_subno(t_subject_balance.subno,&t_subject);
		//写期末科目余额

		t_subject_balance.endbala_flag=t_subject_balance.bbala_flag;
		if(3!=t_subject.direct)
		{
			if(1==t_subject_balance.bbala_flag)
			{
				 t_subject_balance.endbala=t_subject_balance.bbala+(t_subject_balance.dramnt-t_subject_balance.cramt);
			}
			else	 t_subject_balance.endbala=t_subject_balance.bbala-(t_subject_balance.dramnt-t_subject_balance.cramt);
		}
		else
		{
			if(1==t_subject_balance.bbala_flag)
			{
				 t_subject_balance.endbala=t_subject_balance.bbala+(t_subject_balance.dramnt-t_subject_balance.cramt);
			}
			else	 t_subject_balance.endbala=t_subject_balance.bbala-(t_subject_balance.dramnt-t_subject_balance.cramt);

			if(t_subject_balance.endbala<0)
			{
				t_subject_balance.endbala=abs(t_subject_balance.endbala);
				if(1==t_subject_balance.bbala_flag)	t_subject_balance.endbala_flag=2;
				else								t_subject_balance.endbala_flag=1;
			}

		}
		//写结算文件
		if(NULL==fprintf(fp,"%s	%f	%f	%f\r\n",t_subject_balance.subno,t_subject_balance.bbala,t_subject_balance.endbala,t_subject_balance.endbala-t_subject_balance.bbala));
		{
			writelog(LOG_ERR,"fprintf error,");
		}
		ret=DB_t_tif_subject_balance_add(&t_subject_balance);
		if(ret)
		{
			writelog(LOG_ERR,"Insert t_tif_subject_balance record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_TABLE_ERRACC_I;
		}

	 }
	fclose(fp);
	DB_v_tif_shopdeptfee_close_select_by_c5();
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	return 0;
}

int CreateBankCompReport()
{
	return 0;
}

int CreateTransReport()
{
	return 0;
}

/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 日结过后，统一修改部分隔天生效的参数
      修改记录	:
*****************************************************/

int ChangeConfigPara()
{
	int ret=0;
	int cnt=0;

	char logic_date[10+1]="";
	char tmp_date[10+1]="";
	char next_date[10+1]="";
	double second=0;

//	T_t_cif_shop 			t_shop;
//	T_t_cif_shop_log		t_shop_log;
	T_t_cif_shop_pos		t_shop_pos;
	T_t_cif_shop_pos_log	t_shop_pos_log;
	T_t_pif_syskey 		t_pif_syskey;
	T_t_tif_warrant		t_tif_warrant;

	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}
	//得到逻辑时间的下一天
	strcpy(tmp_date,logic_date);
//	strcat(tmp_date,"000000");
	ret=datetime2second(tmp_date, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	second=second+24*60*60;
	ret=second2datetime(second, tmp_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}
	Strncpy(next_date,tmp_date,sizeof(next_date));

	//writelog(LOG_ERR,"logic_date=[%s]",logic_date);
	//writelog(LOG_ERR,"next_date=[%s]",next_date);


	//修改凭证表的当前值为1
	ret=DB_t_tif_warrant_read_lock_by_cur_and_wtype(100,&t_tif_warrant);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_warrant_read_lock_by_cur_and_wtype error,errcode=[%d]",ret);
		return 	ret;
	}
	strcpy(t_tif_warrant.cur_no,"1");
	ret=DB_t_tif_warrant_update_by_wtype(100,&t_tif_warrant);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_warrant_update_by_wtype error,errcode=[%d]",ret);
		return 	ret;
	}

	/*
	//修改商户信息表，使临时商户信息表的数据生效
	//删除商户信息表的数据
	ret=DB_t_cif_shop_del_all();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_cif_shop_del error,errorcode[%d]",ret);
		return 	E_DB_SHOP_D;
	}
	//拷贝临时信息表的数据到商户信息表中

	ret=DB_t_cif_shop_log_open_select_by_cur2_and_update_date(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_shop_log_open_select_by_cur1 error,errorcode[%d]",ret);
		return 	ret;
	}
	while(1)
	{
		memset(&t_shop,0,sizeof(t_shop));
		memset(&t_shop_log,0,sizeof(t_shop_log));
		ret=DB_t_cif_shop_log_fetch_select_by_cur2(&t_shop_log);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't record from t_cif_shop_log table!");
					break;
				}
				else		break;
			}
			else
				writelog(LOG_DEBUG,"DB_t_cif_shop_log_fetch_select_by_cur2 error,errcode=[%d]!",ret);
				return   E_DB_SHOPDEPTFEE_R;
		}

		//strncpy(t_shop.update_date  ,logic_date, sizeof(t_shop.update_date  ));
		t_shop.shop_id		  =t_shop_log.shop_id;
		t_shop.cut_id             =t_shop_log.cut_id ;
		t_shop.dept_id            =t_shop_log.dept_id;
		strncpy(t_shop.shop_name    ,t_shop_log.shop_name  ,  sizeof(t_shop.shop_name    ))  ;
		t_shop.shop_type         =t_shop_log.shop_type;
		strncpy(t_shop.is_indep      ,t_shop_log.is_indep   ,   sizeof(t_shop.is_indep      ));
		strncpy(t_shop.is_leaf       ,t_shop_log.is_leaf    ,   sizeof(t_shop.is_leaf       ));
		t_shop.shop_state         =t_shop_log.shop_state;
		strncpy(t_shop.shop_manager ,t_shop_log.shop_manager, sizeof(t_shop.shop_manager ))   ;
		strncpy(t_shop.man          ,t_shop_log.man         , sizeof(t_shop.man          ))   ;
		strncpy(t_shop.sex           ,t_shop_log.sex        ,   sizeof(t_shop.sex           ));
		t_shop.nation             =t_shop_log.nation;
		strncpy(t_shop.man_id       ,t_shop_log.man_id      , sizeof(t_shop.man_id       ))   ;
		strncpy(t_shop.tel          ,t_shop_log.tel         , sizeof(t_shop.tel          ))   ;
		strncpy(t_shop.address     ,t_shop_log.address    , sizeof(t_shop.address     ))      ;
		strncpy(t_shop.is_getfee     ,t_shop_log.is_getfee  ,   sizeof(t_shop.is_getfee     ));
		t_shop.ratio              =t_shop_log.ratio;
		t_shop.manager_type       =t_shop_log.manager_type;
		t_shop.duty_type          =t_shop_log.duty_type   ;
		strncpy(t_shop.reg_time     ,t_shop_log.reg_time  ,   sizeof(t_shop.reg_time     ))   ;
		strncpy(t_shop.comments    ,t_shop_log.comments   , sizeof(t_shop.comments    ))      ;

		cnt++;
		ret=DB_t_cif_shop_add(&t_shop);
		if(ret)
		{
			writelog(LOG_ERR,"Insert DB_t_cif_shop_add record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_SHOP_I;
		}
		strncpy(t_shop_log.update_date,next_date,sizeof(t_shop_log.update_date));
		ret=DB_t_cif_shop_log_add(&t_shop_log);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_cif_shop_log_add record[%d],err[%d]",cnt,ret);
			db_rollback();
			return ret;
			//return 	E_DB_SHOP_LOG_I;
		}

	 }
	*/
	//修改商户设备信息表，使临时商户设备信息表的数据生效
	//删除商户设备信息表的数据

	ret=DB_t_cif_shop_pos_del_all();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_cif_shop_del error,errorcode[%d]",ret);
		return 	E_DB_SHOP_D;
	}
	//拷贝临时信息表的数据到商户信息表中
	ret=DB_t_cif_shop_pos_log_open_select_by_cur1_and_update_date(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_shop_pos_log_open_select_by_cur1_and_update_date error,errorcode[%d]",ret);
		return 	ret;
	}
	while(1)
	{
		memset(&t_shop_pos,0,sizeof(t_shop_pos));
		memset(&t_shop_pos_log,0,sizeof(t_shop_pos_log));
		ret=DB_t_cif_shop_pos_log_fetch_select_by_cur1(&t_shop_pos_log);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_cif_shop_pos_log table!");
						break;
					}
				else		break;
			}
			else
			{
				writelog(LOG_DEBUG,"DB_t_cif_shop_pos_log_fetch_select_by_cur1 error,errcode=[%d]",ret);
				return   ret;
			}
		}

		t_shop_pos.id            =t_shop_pos_log.id        ;
		t_shop_pos.device_id     =t_shop_pos_log.device_id ;
		t_shop_pos.shop_id       =t_shop_pos_log.shop_id   ;
		strncpy(t_shop_pos.begin_date    ,t_shop_pos_log.begin_date ,sizeof(t_shop_pos.begin_date  ));
		strncpy(t_shop_pos.begin_time    ,t_shop_pos_log.begin_time ,sizeof(t_shop_pos.begin_time  ));
		strncpy(t_shop_pos.end_time      ,t_shop_pos_log.end_time   ,sizeof(t_shop_pos.end_time    ));
		strncpy(t_shop_pos.end_date      ,t_shop_pos_log.end_date   ,sizeof(t_shop_pos.end_date    ));
		strncpy(t_shop_pos.comments      ,t_shop_pos_log.comments   ,sizeof(t_shop_pos.comments    ));
		cnt++;
		ret=DB_t_cif_shop_pos_add(&t_shop_pos);
		if(ret)
		{
			writelog(LOG_ERR,"Insert DB_t_cif_shop_pos record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_SHOP_POS_I;
		}
		strncpy(t_shop_pos_log.update_date,next_date,sizeof(t_shop_pos_log.update_date));
		ret=DB_t_cif_shop_pos_log_add(&t_shop_pos_log);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_cif_shop_pos_log_add record[%d],err[%d]",cnt,ret);
			db_rollback();
			return ret;
			//return 	E_DB_SHOP_POS_LOG_I;
		}

	 }
	//更改全局参数表，使临时全局参数表的数据生效
	//暂时耿刚说不用实现
	//T_t_pif_cur_syspara	t_syspara;


	//设置逻辑日期，增加一天
	ret=SetLogicDate(1);
	if(ret)
	{
		writelog(LOG_ERR,"SetLogicDate(1) error,errcode=[%d]!",ret);
		return ret;
	}


	//更改系统键值表中的KEYTYPE_TRADESERIAL键值为‘1’
	memset(&t_pif_syskey,0,sizeof(t_pif_syskey));
	ret=DB_t_pif_syskey_read_lock_by_cur_and_key_code(KEYTYPE_TRADESERIAL, &t_pif_syskey);
	if(ret)
	{
		writelog(LOG_ERR,"read syskey err[%d]type[%s]",ret,KEYTYPE_TRADESERIAL);
		if(DB_NOTFOUND==ret)
		{
			return E_DB_SYSKEY_N;
		}
		else
			return E_DB_SYSKEY_R;
	}
	t_pif_syskey.key_value=1;
	ret=DB_t_pif_syskey_update_lock_by_cur(&t_pif_syskey);
	if(ret)
	{
		writelog(LOG_ERR,"update syskey err[%d]",ret);
		return E_DB_SYSKEY_U;
	}
	DB_t_pif_syskey_free_lock_cur();
	ret = InitializeSyskey();
	if( ret )
	{
		return ret;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	return 0;
}

/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 日终的帐务结转
      修改记录	:
*****************************************************/
int AccountCarryForward()
{
	int ret=0;
	int cnt=0;
	double trans_amt=0;
	char yes_or_no[2]="";

	T_t_tif_tradeserial		t_tradeserial;
	T_t_aif_account		t_account;
	T_t_cif_shop			t_shop;


	//现金帐向银行存款帐结转
	memset(&t_account,0,sizeof(t_account));
	ret=DB_t_aif_account_read_by_account_id(INNER_ACCOUNT_CASH,&t_account);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d],account_id=[%s]",ret,INNER_ACCOUNT_CASH);
		return 	ret;
	}
	trans_amt=t_account.cur_bala;
	memset(&t_tradeserial,0,sizeof(t_tradeserial));
	ret=add_serialno(&t_tradeserial, trans_amt,INNER_ACCOUNT_CASH,INNER_ACCOUNT_BANKDEPOSIT);
	if(ret)
	{
		writelog(LOG_ERR,"add_serialno error,errcode=[%d]",ret);
		db_rollback();
		return 	ret;
	}
	//添加流水成功，提交事务
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}

	//交易正常则进行下面的处理
	ret=process(&t_tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		goto L_RETU;
	}

	//更新流水状态
	getsysdate(t_tradeserial.enteract_date);			//处理日期
	getsystime(t_tradeserial.enteract_time);			//处理时间
	t_tradeserial.serial_state=SERISTAT_DEBT;		//已入帐
	ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
		goto L_RETU;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		goto L_RETU;
	}
	//printf("process OK\n");

	//商户帐户向两个划拨帐户结转
	//独立核算商户结转
	strcpy(yes_or_no,TYPE_YES);
	ret=DB_t_cif_shop_open_select_by_cur3_and_is_indep(yes_or_no);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_shop_open_select_by_cur3_and_is_indep error, errcode=[%d]",ret);
		return ret;
	}

	while(1)
	{
		ret=DB_t_cif_shop_fetch_select_by_cur3(&t_shop);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"DB_t_cif_shop_fetch_select_by_cur2 have not record,shop_id=[%d]!",t_shop.shop_id);
						break;
					}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		ret=SearchLeafshop_and_Trans(t_shop.shop_id,yes_or_no);
		if(ret)
		{
			writelog(LOG_DEBUG,"SearchLeafshop_and_Trans faild,t_shop.shop_id=[%d],cnt=[%d]!",t_shop.shop_id,cnt);
			break;
		}
	}
	//非独立核算商户结转
	strcpy(yes_or_no,TYPE_NO);
	ret=DB_t_cif_shop_open_select_by_cur3_and_is_indep(yes_or_no);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_shop_open_select_by_cur3_and_is_indep error, errcode=[%d]",ret);
		return ret;
	}

	while(1)
	{
		ret=DB_t_cif_shop_fetch_select_by_cur3(&t_shop);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"DB_t_cif_shop_fetch_select_by_cur2 have not record,shop_id=[%d]!",t_shop.shop_id);
						break;
					}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		ret=SearchLeafshop_and_Trans(t_shop.shop_id,yes_or_no);
		if(ret)
		{
			writelog(LOG_DEBUG,"SearchLeafshop_and_Trans faild,t_shop.shop_id=[%d]!",t_shop.shop_id);
			break;
		}
	}

	writelog(LOG_INFO,"Transfer succeed!");
	return 0;

L_RETU:
	//回滚事务
	db_rollback();
	//更新流水状态
	getsysdate(t_tradeserial.enteract_date);			//处理日期
	getsystime(t_tradeserial.enteract_time);			//处理时间
	//t_tradeserial.ecode=*pRetCode;					//返回码
	t_tradeserial.serial_state=SERISTAT_DEBTEXC;		//入账异常状态
	ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
	}
	//提交事务
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
	}
	return E_ENTER_ACCOUNT;
}


int AccountCarryForward1()
{
	int ret=0;
	int cnt=0;
	int tm_shop_id=0;
	double trans_amt=0;
	//char yes_or_no[2]="";

	T_t_tif_tradeserial		t_tradeserial;
	T_t_aif_account		t_account;
	T_t_cif_shop			t_shop;


	//现金帐向银行存款帐结转
	memset(&t_account,0,sizeof(t_account));
	ret=DB_t_aif_account_read_by_account_id(INNER_ACCOUNT_CASH,&t_account);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d],account_id=[%s]",ret,INNER_ACCOUNT_CASH);
		return 	ret;
	}
	if(0==t_account.cur_bala)
	{
		writelog(LOG_INFO,"Trade amt equal 0,trade cancel!");
	}
	else
	{
		trans_amt=t_account.cur_bala;
		memset(&t_tradeserial,0,sizeof(t_tradeserial));
		ret=add_serialno(&t_tradeserial, trans_amt,INNER_ACCOUNT_CASH,INNER_ACCOUNT_BANKDEPOSIT);
		if(ret)
		{
			writelog(LOG_ERR,"add_serialno error,errcode=[%d]",ret);
			return 	ret;
		}
		//交易正常则进行下面的处理
		ret=process(&t_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"process ret[%d]",ret);
			goto L_RETU;
		}
		//添加流水成功，提交事务
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			db_rollback();
			return 	ret;
		}
		//更新流水状态
		getsysdate(t_tradeserial.enteract_date);			//处理日期
		getsystime(t_tradeserial.enteract_time);			//处理时间
		t_tradeserial.serial_state=SERISTAT_DEBT;		//已入帐
		ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
			goto L_RETU;
		}
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			goto L_RETU;
		}
	}
	//printf("process OK\n");

	//商户帐户向两个划拨帐户结转
	//独立核算商户结转
	ret=DB_t_aif_account_open_select_by_cur6_and_act_type_and_current_state(ACCTYPE_SHOPMAIN,1);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_open_select_by_cur6_and_act_type_and_current_state error, errcode=[%d]",ret);
		return ret;
	}

	while(1)
	{
		cnt++;
		memset(&t_account,0,sizeof(t_account));
		ret=DB_t_aif_account_fetch_select_by_cur6(&t_account);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_ERR,"DB_t_aif_account_fetch_select_by_cur6 have not record");
						break;
					}
				else		break;
			}
			else
			{
				writelog(LOG_ERR,"DB_t_aif_account_fetch_select_by_cur6 error,cnt=[%d],errcode=[%d]",cnt,ret);
				return   ret;
			}
		}


		if(0==t_account.cur_bala)
		{
			writelog(LOG_INFO,"Trade amt equal 0,trade cancel!");
		}
		else
		{
			ret=DB_t_cif_shop_read_by_cut_id(t_account.customer_id,&t_shop);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_cif_shop_read_by_cut_id error,customer_id=[%d],errcode=[%d]",t_account.customer_id,ret);
				return   ret;
			}
			while(1)
			{
				//printf("test1!\n");
				if(0==t_shop.shop_id) 				//证明该帐户为非独立核算账户
				{
					//printf("%d\n",__LINE__);
					memset(&t_tradeserial,0,sizeof(t_tradeserial));
					ret=add_serialno(&t_tradeserial, t_account.cur_bala,INNER_ACCOUNT_FINANCETRANSER,t_account.account_id);
					{
						writelog(LOG_ERR,"add_serialno error,errcode=[%d]",ret);
						db_rollback();
						return 	ret;
					}
					//交易正常则进行下面的处理
					ret=process(&t_tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"process ret[%d]",ret);
						goto L_RETU;
					}
					//更新流水状态
					getsysdate(t_tradeserial.enteract_date);			//处理日期
					getsystime(t_tradeserial.enteract_time);			//处理时间
					t_tradeserial.serial_state=SERISTAT_DEBT;		//已入帐
					ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
						goto L_RETU;
					}

					break;

				}

				//printf("%d\n",__LINE__);

				if(strncmp(t_shop.is_indep,TYPE_YES,1))
				{
					//ret=add_serialno(&t_tradeserial, t_account.cur_bala,INNER_ACCOUNT_BANKTRANSFER,INNER_ACCOUNT_BANKTRANSFER);
					memset(&t_tradeserial,0,sizeof(t_tradeserial));
					ret=add_serialno(&t_tradeserial, t_account.cur_bala,INNER_ACCOUNT_BANKTRANSFER,t_account.account_id);
					if(ret)
					{
						writelog(LOG_ERR,"add_serialno error,errcode=[%d]",ret);
						db_rollback();
						return 	ret;
					}
					//交易正常则进行下面的处理
					ret=process(&t_tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"process ret[%d]",ret);
						goto L_RETU;
					}
					//更新流水状态
					getsysdate(t_tradeserial.enteract_date);			//处理日期
					getsystime(t_tradeserial.enteract_time);			//处理时间
					t_tradeserial.serial_state=SERISTAT_DEBT;		//已入帐
					ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
						goto L_RETU;
					}
					break;
				}

				ret=DB_t_cif_shop_read_by_shop_id(tm_shop_id,&t_shop);

				if(ret)
				{
					writelog(LOG_ERR,"DB_t_cif_shop_read_by_shop_id error,shop_id=[%d],errcode=[%d]",t_shop.dept_id,ret);
					return   ret;
				}
				tm_shop_id=t_shop.dept_id;

			}

		}

	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		goto L_RETU;
	}
	writelog(LOG_INFO,"Shop account carry foreward succeed!record=[%d]",cnt);
	return 0;

L_RETU:
	//回滚事务
	db_rollback();
	//更新流水状态
	getsysdate(t_tradeserial.enteract_date);			//处理日期
	getsystime(t_tradeserial.enteract_time);			//处理时间
	//t_tradeserial.ecode=*pRetCode;					//返回码
	t_tradeserial.serial_state=SERISTAT_DEBTEXC;		//入账异常状态
	ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
	}
	//提交事务
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
	}
	return E_ENTER_ACCOUNT;
}

/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 删除流水表，交易明晰表中的数据
      修改记录	:
*****************************************************/
int DelTradeDate()
{
	int ret=0;

	//删除交易明细表
	ret=DB_t_tif_tradelog_del_all_by_step_commit();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_tif_tradelog_del_all error,errcode=[%d]",ret);
		db_rollback();
		return 	ret;
	}

	//删除流水表
	ret=DB_t_tif_tradeserial_del_all_by_step_commit();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_del_all error,errcode=[%d]",ret);
		db_rollback();
		return 	ret;
	}
	//删除门禁流水表
	ret=Db_t_door_txdtl_del_all_by_step_commit();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Db_t_door_txdtl_del_all_by_step_commit error,errcode=[%d]",ret);
		db_rollback();

	}
	//删除消息队列表
	ret=DB_t_tif_meslist_del_all_in_03_04_60_by_step_commit();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_tif_meslist_del_all_in_03_04_60_by_step_commit error,errcode=[%d]",ret);
		db_rollback();
		return 	0;
	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	writelog(LOG_INFO,"Delete t_tif_tradeserial and t_tif_tradelog succeed!");
	return 0;
}


/****************************************************
      作    者	: hhd
      创建日期	: 2004-8-13 9:34
      描    述 	: 修改日结标志，换天开工
      修改记录	:
*****************************************************/
int Startup()
{
	int ret=0;
	ret=SetParameter(GLOBE_FLAG_BALANCE,"0");
	if(ret)
	{
		writelog(LOG_ERR,"Change system balance flag failed!");
		return ret;
	}
	return 0;
}

/****************************************************
      作    者	: hhd
      创建日期	: 2005-12-16 9:34
      描    述 	: 按照共享库同步过来的冻结状态进行
      				  冻结客户
      修改记录	:
*****************************************************/

int DoFrozenCustomer()
{
	int ret=0;
	int cnt=0;
	int count=0;
	int card_id=0;
	int frozen_status=1;
	T_t_cif_customer t_customer;

	memset(&t_customer,0,sizeof(t_customer));

	ret=DB_t_cif_customer_open_select_with_hold_by_cur3_and_frozen_status(frozen_status);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_customer_open_select_by_cur2_and_frozen_status error, errcode=[%d]",ret);
		return ret;
	}
	while(1)
	{
		ret=DB_t_cif_customer_fetch_select_by_cur3(&t_customer);
		if(ret)
		{
			DB_t_cif_customer_close_select_by_cur3();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"DB_t_cif_customer_fetch_select_by_cur2 have not record");
					break;
				}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		ret=get_tradecard_no_by_stupid(t_customer.stuemp_no,&card_id);
		if(ret)
		{
			writelog(LOG_DEBUG,"Get_tradecard_no_by_stupid stuemp[%s] error,errcode=[%d]",t_customer.stuemp_no,ret);
			continue;
		}

		ret=freezecard(card_id,t_customer.cut_id,"system",0,0);
		if(ret)
		{
			writelog(LOG_DEBUG,"Freezecard customer error,errcode[%d],cut_id[%d],card_id[%d]",ret,t_customer.cut_id,card_id);
			continue;
		}
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			continue;
		}
		count++;

	}
	ret=DB_t_cif_customer_close_select_by_cur3();
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_customer_close_select_by_cur3 error,errcode[%d]",ret);
	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}

	writelog(LOG_DEBUG,"Freezecard customer total records[%d]",count);
	return 0;

}


/****************************************************
  作    者	: hhd
  创建日期	: 2006-08-08 9:34
  描    述 	: 根据上海大学的需求，把独立核算的商户的每天的营业
  			  数据按照指定的数据格式形成文件，ftp形式发送给
  			  上海大学sap服务器
  相关说明 	:
  			  文档格式：TXT文本文件
			  文档内容: 首行:转帐商户数<Tab>转帐总金额<Tab>转帐日期
							注：各字段以Tab键分隔，转帐日期为8位数字字符串，
								如20060728
						明细:商户唯一ID<Tab>转帐总金额
  修改记录	:
*****************************************************/
int GenIndepShopFtpData()
{

}





