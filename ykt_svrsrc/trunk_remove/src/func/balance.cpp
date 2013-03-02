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
#include "dbfunc_foo.h"
#include "acctrans.h"

#define	SLEEP_TIME				60	//结账间隔时间

static int freezecard(int in_cardno,int in_custid,char* in_operator,int in_maindeviceid,int in_deviceid)
{

  	int  ret = 0;
	int	cardno = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char	oper[33+1] = "";
	int	custid  = 0;
	int	maindeviceid = 0;
	int	deviceid = 0;
	double dSerial_no = 0;
	char sCardState[5] = "";
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_msglist tMsgList;

	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tMsgList,0,sizeof(tMsgList));

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode[%d]",ret);
		goto L_RETU;
	}
	//	准备输入信息
	cardno = in_cardno;												//卡标识
	custid = in_custid;												//客户号
	des2src(oper,in_operator);									//操作员号
	maindeviceid = in_maindeviceid;											//上传工作站标识
	deviceid = in_deviceid;												//采集设备标识

	//	检查客户信息，判断是否可以冻结
	ret = GetCardState(cardno,sCardState);
	if (ret)
	{
		writelog(LOG_ERR,"GetCardState error,errcode[%d],cardno[%d]",ret,sCardState);
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
	ret = UpdateCardState(cardno,CARDSTAT_TYPE_FREEZE,STATE_TRUE);
	if (ret)
	{
		writelog(LOG_ERR,"UpdateCardState error,errcode[%d],cardno[%d]",ret,cardno);
		goto L_RET;
	}
	//如果该卡号被挂失,则解冻时对黑名单不处理
	if(STATE_FALSE==sCardState[CARDSTAT_TYPE_LOST])
	{
		//	插入黑名单表
//			ret=DB_t_tif_black_sheet_del_by_cardno_and_is_ad(cardno,DELETE_BLACKLIST);
//			if(ret)
//			{
//				if(ret!=DB_NOTFOUND)
//				{
//					writelog(LOG_ERR,"DB_t_tif_black_sheet_del_by_cardno_and_is_ad err[%d],cardno=[%d] ",ret,cardno);
//					goto L_RETU;
//				}
//			}
		ret=InsertToBlkList(cardno,ADD_BLACKLIST);
		if(ret)
		{
			writelog(LOG_ERR,"InsertToBlkList err[%d],cardno=[%d] ",ret,cardno);
			goto L_RETU;
		}

		//广播黑名单
		AddXmlItemInt(tMsgList.reqdata, XML_KEY_CARDID,cardno);
		AddXmlItemInt(tMsgList.reqdata, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//增删标志

		tMsgList.funcno = 930005;
		tMsgList.msglevel = 1;
		ret=AddMsgLst(&tMsgList);
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
	tradeserial.serial_no = D2I(dSerial_no);									//流水号
	tradeserial.serial_type = TXCODE_FREEZE_CARD;								//冻结卡
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;							//流水状态
	tradeserial.maindeviceid = maindeviceid;									//上传工作站标识
	tradeserial.deviceid = deviceid;											//采集设备标识
	tradeserial.cardno = cardno;												//交易卡号
	tradeserial.custid=custid;											//客户号
	des2src(tradeserial.opercode,oper);
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
	T_t_card card;					//卡信息表
	T_t_shop		shop;			//商户信息表
	T_t_aif_account	account;		//帐户表
	InAcc   IA;						//记账模块输入参数

	memset(&card,0,sizeof(card));
	memset(&shop,0,sizeof(shop));
	memset(&account,0,sizeof(account));
	memset(&IA,0,sizeof(IA));


	//IA.iMainDevId=p->maindeviceid;			//工作站标识
	//IA.iDevId=p->deviceid;					//设备ID
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
 	IA.dInCardBala=p->cardbefbal;                       //入卡值
       IA.dOutCardBala=p->cardaftbal;                   //出卡值

	//IA.in_card_bala=p->cardbefbal;		//入卡值
	//IA.out_card_bala=p->cardaftbal;		//出卡值
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
	int iSeqNo=0;
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
	p->maindeviceid=0;                     			//上传工作站标识
	p->deviceid=0;                         			//交易发生设备标识
	//p->devphyid[8+1];                 //三九设备物理ID
	//p->showid[10+1];                      //显示卡号
	//p->cardno;                           //交易卡号
	//p->purseno;                          //交易钱包号
	//p->trade_count;                       //当前卡中帐户交易次数
	p->trade_fee=trans_amt;                          			//本次交易金额
	//printf("p->trade_fee[%lf]\n",p->trade_fee);
	//p->cardbefbal;                        //入卡金额
	//p->cardaftbal;                       //出卡金额
	//p->depositfee;                       //押金金额
	//p->in_fee;                            //手续金额
	//p->cost_fee;                          //卡成本费
	//p->oldpwd[32+1];                      //原始密码
	//p->newpwd[32+1];                      //更新密码
	//p->custid;                       //客户标识
	strcpy(p->opercode,"system");          		//操作员代码
	strncpy(p->out_account_id,out_account_no,sizeof(p->out_account_id)-1);               		//出帐帐号
	//printf("p->out_account_id[%s]\n",p->out_account_id);
	strncpy(p->in_account_id,in_account_no,sizeof(p->in_account_id)-1);                			//入帐账号
	//printf("p->in_account_id[%s]\n",p->in_account_id);
	//p->b_act_id[40+1];                    //外部系统帐号
	//p->sysid;                            //外部系统标识
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
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &iSeqNo);
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		p->ecode=ret;
		return ret;
	}
	p->serial_no=iSeqNo;
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


int SearchLeafshop_and_Trans(int shopid,char* Independ_or_not)
{

	int ret=0;
	int cnt=0;

	char type_yes_or_no[1+1]="";
	//T_v_tif_shopdeptfee 	v_shopdeptfee;
	T_t_shop		  	t_shop;
	T_t_tif_tradeserial		t_tradeserial;
	T_t_aif_account		t_account;

	memset(&t_shop,0,sizeof(t_shop));

	ret=DB_t_shop_read_by_shop_id(shopid,&t_shop);
	if(ret)
	{
		writelog(LOG_ERR,"read tablet_cif_shop  shopid[%d]",shopid);
		if(DB_NOTFOUND==ret)
		{
			return E_NOTEXIST_SHOPID;
		}
		else
			return E_DB_SHOP_R;
	}
	strcpy(type_yes_or_no,TYPE_YES);
	if(strncmp(t_shop.endflag,type_yes_or_no,1))
	{
		//根据客户号和商户主账号类型查询账号表，得到账号
		memset(&t_account,0,sizeof(t_account));
		ret=DB_t_aif_account_read_by_customer_id_and_act_type(t_shop.custid,ACCTYPE_SHOPMAIN,&t_account);
		if((0!=ret)&&(DB_NOTFOUND!=ret))
		{
			writelog(LOG_ERR,"read_by_customer_id_and_act_type ret[%d]custid[%d]",ret,t_shop.custid);
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
	ret=DB_t_shop_open_select_by_cur2_and_dept_id(shopid);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_shop_open_select_by_cur2_and_dept_id ret[%d]shopid[%d]",ret,shopid);
		return E_DB_SHOP_R;
	}
	while(1)
	{
		memset(&t_shop,0,sizeof(t_shop));
		ret=DB_t_shop_fetch_select_by_cur2(&t_shop);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"DB_t_shop_fetch_select_by_cur2 have not record,shopid=[%d]!",t_shop.shopid);
						break;
					}
				else
					break;
			}
			else
				goto L_RETU;
		}
		cnt++;
		ret=SearchLeafshop_and_Trans(t_shop.shopid,Independ_or_not);
		if(ret)
		{
			writelog(LOG_DEBUG,"SearchLeafshop_and_Trans faild,ret[]t_shop.shopid=[%d]!",ret,t_shop.shopid);
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
	//t_tradeserial.errcode=*pRetCode;			//返回码
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
	ret=GetSysParaVal(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"Read syspara err [%d]",ret);
		return E_SEARCH_FLAG;
	}

	if(strncmp(buffer,"1",1)!=0)
	{
		strcpy(buffer,"1");
		ret=SetSysParaVal(GLOBE_FLAG_BALANCE,buffer);
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
	T_t_account		account;
	T_t_tif_act_daysum 	act_daysum;

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
      描    述 	: 管理费退费操作，目前研究决定每月初统一退费
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
	T_t_customer				t_customer;
	T_t_tif_act_daysum			t_daysum;
	T_t_aif_account 				t_aif_account;
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
	ret=GetSysParaVal(GLOBE_MAX_CARDDB_NOBALANCE_MONEY, buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetSysParaVal error,errcode[%d]",ret);
		return 	ret;
	}
	carddb_nobala_money=atof(buffer);
	//取全局参数最大卡库不平天数
	memset(buffer,0,sizeof(buffer));
	ret=GetSysParaVal(GLOBE_MAX_CARDDB_NOBALANCE_TIMES,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetSysParaVal error,errcode[%d]",ret);
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
		memset(&t_aif_account,0,sizeof(t_aif_account));

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
		ret=DB_t_aif_account_read_by_account_id(t_no_balance.account_id, &t_aif_account);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,t_no_balance.account_id=[%s],errcode=[%d]",t_no_balance.account_id,ret);
			goto L_RETU;
		}
		if(t_aif_account.current_state!=1) 	continue;
		strncpy(t_no_balance.custname,v_no_balance.custname,sizeof(t_no_balance.custname));
		strncpy(t_no_balance.stuempno,v_no_balance.stuempno,sizeof(t_no_balance.stuempno));
		t_no_balance.type_id=v_no_balance.card_type;
		ret=DB_t_customer_read_by_custid(v_no_balance.custid,&t_customer);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_customer_read_by_custid error,v_no_balance.custid=[%d],errcode=[%d]",v_no_balance.custid,ret);
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
		ret=GetCardState(v_no_balance.cardno,sCardState);	//得到卡状态
		if(ret)
		{
			writelog(LOG_ERR,"GetCardState error,err[%d],cardno[%d]",ret,v_no_balance.cardno);
			goto L_RETU;
		}
		if(STATE_TRUE!=sCardState[CARDSTAT_TYPE_FREEZE])	//对于已经冻结的帐户不进行处理
		{
			//如果不平金额超过最大值限制，则直接冻结，等待人工处理
			if(v_no_balance.diff_bala>carddb_nobala_money)	//进行冻结操作,人工处理
			{
				ret=freezecard(v_no_balance.cardno,v_no_balance.custid,"system", 0, 0);
				if(ret)
				{
					writelog(LOG_ERR,"freezecard error,err[%d],cardno[%d]",ret,v_no_balance.cardno);
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
					ret=freezecard(v_no_balance.cardno,v_no_balance.custid,"system", 0, 0);
					if(ret)
					{
						writelog(LOG_ERR,"freezecard error,err[%d],cardno[%d]",ret,v_no_balance.cardno);
					}
				}
				//卡小库大，补记一条流水，作为丢帐处理
				if(v_no_balance.db_bala>v_no_balance.card_bala)
				{
					memset(&tradeserial,0,sizeof(tradeserial));
					memset(&t_daysum,0,sizeof(t_daysum));

					tradeserial.serial_type=TXCODE_MAKEUPSERIAL;							//添加交易代码
					tradeserial.cardno=v_no_balance.cardno;									//添加卡号字段
					tradeserial.custid=v_no_balance.custid;							//添加客户号字段
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
						ret=freezecard(v_no_balance.cardno,v_no_balance.custid,"system", 0, 0);
						if(ret)
						{
							writelog(LOG_ERR,"freezecard error,err[%d],cardno[%d]",ret,v_no_balance.cardno);
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
	T_t_customer		t_customer;
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
		strncpy(t_erracc.custname,v_erracc.custname,sizeof(t_erracc.custname));
		strncpy(t_erracc.stuempno,v_erracc.stuempno,sizeof(t_erracc.stuempno));
		t_erracc.type_id=v_erracc.card_type;
		//取客户的部门名称
		ret=DB_t_aif_account_read_by_account_id(t_erracc.account_id,&t_account);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id err[%d]",ret);
			return 	ret;
		}
		ret=DB_t_customer_read_by_custid(t_account.custid,&t_customer);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_customer_read_by_custid err[%d],custid=[%d]",ret,t_account.custid);
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

	memset(&v_active,0,sizeof(v_active));
	memset(&t_active,0,sizeof(t_active));
	memset(&t_forward_active,0,sizeof(t_forward_active));
	memset(&t_account,0,sizeof(t_account));
	
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

		strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date)-1);
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
	strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date)-1);
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
	strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date)-1);
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
		strncpy(t_oper.operator_code,v_oper.opercode,sizeof(t_oper.operator_code));
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
		t_oper.maindeviceid=v_oper.maindeviceid;
		t_oper.deviceid=v_oper.deviceid;
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
      创建日期	: 2007-4-29 9:34
      描    述 	: 生成每天的帐务科目交易情况表
      修改记录	:
*****************************************************/

int CreateSubjectTradeReport()
{
	T_v_tif_subject_dept	v_subjectdept;
	T_t_tif_subject_dept	t_subjectdept;

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
	ret=DB_t_tif_subject_dept_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete t_tif_subject_dept report error,errorcode[%d]",ret);
		return 	ret;
	}

	ret=DB_v_tif_subject_dept_open_select_by_cur1();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_subject_dept view error,errorcode[%d]",ret);
		return 	ret;
	}

	while(1)
	{
		memset(&v_subjectdept,0,sizeof(v_subjectdept));
		memset(&t_subjectdept,0,sizeof(t_subjectdept));
		ret=DB_v_tif_subject_dept_fetch_select_by_cur1(&v_subjectdept);
		if(ret)
		{
			DB_v_tif_subject_dept_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't record from v_tif_subject_dept view!");
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
		strncpy(t_subjectdept.balance_date,logic_date,sizeof(t_subjectdept.balance_date)-1);
		strncpy(t_subjectdept.subno,v_subjectdept.subno,sizeof t_subjectdept.subno -1);
		t_subjectdept.seri_type=v_subjectdept.seri_type;
		t_subjectdept.outorin=v_subjectdept.outorin;
		t_subjectdept.op_count=v_subjectdept.op_count;
		t_subjectdept.fee_change=v_subjectdept.fee_change;
		ret=DB_t_tif_subject_dept_add(&t_subjectdept);
		if(ret)
		{
			writelog(LOG_ERR,"Insert t_tif_subject_dept record[%d],err[%d]",cnt,ret);
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
	ret=DB_t_tif_report_shop_balance_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete t_tif_report_shop_balance report error,errorcode[%d]",ret);
		return 	ret;
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
	return 0;
}


/****************************************************
      作    者	: hhd
      创建日期	: 2007-1-11 9:34
      描    述 	: 生成商户设备餐次报表
      修改记录	:
*****************************************************/

int CreateShopDevMealReport()
{

	T_v_tif_report_device_meal	v_device_meal;
	T_t_tif_report_device_meal 	t_device_meal;

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

	ret=DB_t_tif_report_device_meal_del_by_balance_date(logic_date);
	if((0!=ret)&&(DB_NOTFOUND!=ret))
	{
		writelog(LOG_ERR,"DB_t_tif_report_device_meal_del_by_balance_date error,errcode[%d]",ret);
		return 	ret;
	}

	ret=DB_v_tif_report_device_meal_open_select_by_cur1();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_report_device_meal view error,errcode[%d]",ret);
		return 	E_DB_V_REPORT_DEVICE_MEAL_R;
	}

	while(1)
	{
		memset(&v_device_meal,0,sizeof(v_device_meal));
		memset(&t_device_meal,0,sizeof(v_device_meal));
		ret=DB_v_tif_report_device_meal_fetch_select_by_cur1(&v_device_meal);
		if(ret)
		{
			DB_v_tif_report_device_meal_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't record from v_tif_report_device_meal view!");
					return   0;
				}
				else		break;
			}
			else
				return   E_DB_V_REPORT_DEVICE_MEAL_R;
		}
		
		cnt++;
		////生成报表过程开始
		des2src(t_device_meal.balance_date,logic_date);
		t_device_meal.shopid=v_device_meal.shopid;
		t_device_meal.meal_id=v_device_meal.meal_id;
		t_device_meal.deviceid=v_device_meal.deviceid;
		t_device_meal.trade_count=v_device_meal.trade_count;
		t_device_meal.trade_fee=v_device_meal.trade_fee;
		t_device_meal.mng_fee=v_device_meal.mng_fee;
		t_device_meal.total_fee=v_device_meal.total_fee;
		memset(t_device_meal.data_sign,0,sizeof(t_device_meal.data_sign));
		memset(t_device_meal.reserve_1,0,sizeof(t_device_meal.reserve_1));
		memset(t_device_meal.reserve_2,0,sizeof(t_device_meal.reserve_2));

		ret=DB_t_tif_report_device_meal_add(&t_device_meal);
		if(ret)
		{
			writelog(LOG_ERR,"Insert DB_t_tif_report_device_meal record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_V_REPORT_DEVICE_MEAL_I;
		}

		////生成报表过程结束
	 }
	
	DB_v_tif_report_device_meal_close_select_by_cur1();
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
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
		ret=DB_t_tif_subject_balance_add(&t_subject_balance);
		if(ret)
		{
			writelog(LOG_ERR,"Insert t_tif_subject_balance record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_TABLE_ERRACC_I;
		}

	 }
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
	T_t_shop			t_shop;


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
	ret=DB_t_shop_open_select_by_cur3_and_is_indep(yes_or_no);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_shop_open_select_by_cur3_and_is_indep error, errcode=[%d]",ret);
		return ret;
	}

	while(1)
	{
		ret=DB_t_shop_fetch_select_by_cur3(&t_shop);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"DB_t_shop_fetch_select_by_cur2 have not record,shopid=[%d]!",t_shop.shopid);
						break;
					}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		ret=SearchLeafshop_and_Trans(t_shop.shopid,yes_or_no);
		if(ret)
		{
			writelog(LOG_DEBUG,"SearchLeafshop_and_Trans faild,t_shop.shopid=[%d],cnt=[%d]!",t_shop.shopid,cnt);
			break;
		}
	}
	//非独立核算商户结转
	strcpy(yes_or_no,TYPE_NO);
	ret=DB_t_shop_open_select_by_cur3_and_is_indep(yes_or_no);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_shop_open_select_by_cur3_and_is_indep error, errcode=[%d]",ret);
		return ret;
	}

	while(1)
	{
		ret=DB_t_shop_fetch_select_by_cur3(&t_shop);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"DB_t_shop_fetch_select_by_cur2 have not record,shopid=[%d]!",t_shop.shopid);
						break;
					}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		ret=SearchLeafshop_and_Trans(t_shop.shopid,yes_or_no);
		if(ret)
		{
			writelog(LOG_DEBUG,"SearchLeafshop_and_Trans faild,t_shop.shopid=[%d]!",t_shop.shopid);
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
	//t_tradeserial.errcode=*pRetCode;					//返回码
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

	T_t_transdtl t_tradeserial;
	T_t_account			 t_account;
	T_t_shop				 t_shop;


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
			ret=DB_t_shop_read_by_custid(t_account.custid,&t_shop);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_shop_read_by_custid error,custid=[%d],errcode=[%d]",t_account.custid,ret);
				return   ret;
			}
			while(1)
			{
				//printf("test1!\n");
				if(0==t_shop.shopid) 				//证明该帐户为非独立核算账户
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

				ret=DB_t_shop_read_by_shop_id(tm_shop_id,&t_shop);

				if(ret)
				{
					writelog(LOG_ERR,"DB_t_shop_read_by_shop_id error,shopid=[%d],errcode=[%d]",t_shop.dept_id,ret);
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
	//t_tradeserial.errcode=*pRetCode;					//返回码
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
      描    述 	: 修改日结标志，换天开工
      修改记录	:
*****************************************************/
int Startup()
{
	int ret=0;
	ret=SetSysParaVal(GLOBE_FLAG_BALANCE,"0");
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
	int cardno=0;
	int frozen_status=1;
	T_t_customer t_customer;

	memset(&t_customer,0,sizeof(t_customer));

	ret=DB_t_customer_open_select_with_hold_by_cur3_and_frozen_status(frozen_status);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_customer_open_select_by_cur2_and_frozen_status error, errcode=[%d]",ret);
		return ret;
	}
	while(1)
	{
		ret=DB_t_customer_fetch_select_by_cur3(&t_customer);
		if(ret)
		{
			DB_t_customer_close_select_by_cur3();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"DB_t_customer_fetch_select_by_cur2 have not record");
					break;
				}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		ret=get_tradecardno_by_stupid(t_customer.stuempno,&cardno);
		if(ret)
		{
			writelog(LOG_DEBUG,"Get_tradecardno_by_stupid stuemp[%s] error,errcode=[%d]",t_customer.stuempno,ret);
			continue;
		}

		ret=freezecard(cardno,t_customer.custid,"system",0,0);
		if(ret)
		{
			writelog(LOG_DEBUG,"Freezecard customer error,errcode[%d],custid[%d],cardno[%d]",ret,t_customer.custid,cardno);
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
	ret=DB_t_customer_close_select_by_cur3();
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_customer_close_select_by_cur3 error,errcode[%d]",ret);
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
	return 0;
}

/****************************************************
  作    者	: hhd
  创建日期	: 2006-11-07 9:34
  描    述 	: 根据上海大学的需求，将操作员分组后，进行每日的解款金额汇总
  				汇总后的金额，作为sap系统现金解款的依据
  相关说明 	:
  修改记录	:
*****************************************************/
int  PayInCashForOperateGroup()
{
	int ret=0;
	int cnt=0;
	//int count=0;
	double cash=0;
	T_t_group_cash_report group_cash;
	//T_t_groups groups;
	char logic_date[8+1]="";
	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error, errcode=[%d]",ret);
		goto LRet;
	}
	ret=DB_t_group_cash_report_open_select_for_update_by_cur2();
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_group_cash_report_open_select_for_update_by_cur2 error, errcode=[%d]",ret);
		goto LRet;
	}
	while(1)
	{
		memset(&group_cash,0,sizeof(group_cash));
		ret=DB_t_group_cash_report_fetch_select_by_cur2(&group_cash);
		if(ret)
		{
			DB_t_group_cash_report_close_select_by_cur2();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"DB_t_group_cash_report_open_select_for_update_by_cur2 have not record");
					break;
				}
				else	 
				{
					writelog(LOG_DEBUG,"DB_t_group_cash update record=[%d]",cnt);
					break;
				}
			}
			else
				goto LRet;
		}
		cnt++;
		writelog(LOG_ERR,"cnt=[%d],group=[%s]",cnt,group_cash.groupid);

		ret=ReadFromOpenGroupAndRepOper(group_cash.groupid,&cash);
		if(ret)
		{
			writelog(LOG_ERR,"ReadFromOpenGroupAndRepOper groupid[%s] error,errcode=[%d]",group_cash.groupid,ret);
			goto LRet;
		}
		group_cash.pre_money=group_cash.cur_money;
		group_cash.cur_money+=cash;
		strcpy(group_cash.upd_date,logic_date);

		ret=DB_t_group_cash_report_update_lock_by_cur2(&group_cash);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_group_cash_report_update_lock_by_cur2  error,errcode=[%d]",ret);
			goto LRet;
		}

	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		goto LRet;
	}
	return 0;
LRet:
	db_rollback();
	return ret;

}

