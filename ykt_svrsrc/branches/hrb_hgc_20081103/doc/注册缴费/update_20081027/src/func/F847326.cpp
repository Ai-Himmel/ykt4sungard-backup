/* --------------------------------------------
 * 程序名称: F847326.cpp
 * 创建日期: 2008-08-04
 * 程序作者: 李翔
 * 版本信息: 1.0.0.0
 * 程序功能: 注册缴费批量冻结
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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
#include "fdsqc.h"
#include "banktype.h"

static int DoInsertRegisterLog(ST_PACK *rPack)
{
	int ret = 0;
	T_t_tif_register_pay_log t_tif_register_pay_log;
	memset(&t_tif_register_pay_log, 0, sizeof(t_tif_register_pay_log));
	des2src(t_tif_register_pay_log.cut_name, rPack->semail);
	des2src(t_tif_register_pay_log.stuemp_no, rPack->scust_auth);
	t_tif_register_pay_log.register_flag = rPack->lvol0;					// regiser flag
	t_tif_register_pay_log.flag = 0;										// update flag
	t_tif_register_pay_log.reserver_no1 = rPack->lvol1;					// register login and logout flag
	t_tif_register_pay_log.last_register_flag = rPack->lvol5;
	des2src(t_tif_register_pay_log.operate_date, rPack->semp_pwd);
	des2src(t_tif_register_pay_log.operate_time, rPack->semp_pwd2);
	des2src(t_tif_register_pay_log.modify_date, rPack->semp_pwd);
	des2src(t_tif_register_pay_log.modify_time, rPack->semp_pwd2);
	des2src(t_tif_register_pay_log.system_no, rPack->semail2);
	
	ret = DB_t_tif_register_pay_log_add(&t_tif_register_pay_log);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
			ret = E_DB_REGISTER_PAY_LOG_N;
		else
			ret = E_DB_REGISTER_PAY_LOG_I;

		return ret;
	}

	return 0;
}

static int freezecard(int in_card_id,int in_cut_id,char* in_operator,int in_maindevice_id,int in_device_id)
{
  	int  ret = 0;
	int	card_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char	oper[33+1] = "";
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
		goto L_RET;
	}
	//	准备输入信息
	card_id = in_card_id;												//卡标识
	cut_id = in_cut_id;												//客户号
	des2src(oper,in_operator);									//操作员号
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
		ret=InsertToBlkList(card_id,ADD_BLACKLIST);
		if(ret)
		{
			writelog(LOG_ERR,"InsertToBlkList err[%d],card_id=[%d] ",ret,card_id);
			goto L_RET;
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
			goto L_RET;
		}
	}
	//	准备数据插入交易流水表
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerial_no);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode[%d]",ret);
		goto L_RET;
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
	tradeserial.maindevice_id = maindevice_id;									//上传工作站标识
	tradeserial.device_id = device_id;											//采集设备标识
	tradeserial.card_id = card_id;												//交易卡号
	tradeserial.customer_id=cut_id;											//客户号
	des2src(tradeserial.oper_code,oper);
	//	插入交易流水表
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode=[%d]",ret);
		goto L_RET;
	}

	sleep(1);					// 黑名单插入根据触发器来, 触发器1秒钟触发一个单位
	return 0;
	
L_RET:
	return ret;
}

int DoRegisterModify(ST_PACK *rPack)
{
	int ret = 0;
	int cnt = 0;
	int card_id = 0;
	char logicdate[11] = "";
	char sysdate[11] = "";
	T_t_cif_customer t_customer;
	// 导入数据
	T_t_tif_register_pay register_src, register_tmp;
	T_t_tif_register_info register_info;

	memset(&register_src, 0, sizeof(register_src));
	memset(&register_tmp, 0, sizeof(register_tmp));
	memset(&t_customer, 0, sizeof(t_customer));
	memset(&register_info, 0, sizeof(register_info));

	des2src(register_src.cut_name, rPack->semail);
	des2src(register_src.stuemp_no, rPack->scust_auth);
	register_src.register_flag = rPack->lvol0;					// regiser flag
	register_src.flag = 0;										// update flag
	register_src.reserver_no1 = rPack->lvol1;					// register login and logout flag
	
	ret = DB_t_tif_register_info_read_by_register_flag(register_src.register_flag, &register_info);
	if (ret)
	{
		// 此处如果读取不正确应该给个默认值
		des2src(register_src.register_info, "");
	}

	des2src(register_src.register_info, register_info.register_info);
	getsysdate(register_src.operate_date);
	getsystime(register_src.operate_time);	
	des2src(rPack->semp_pwd, register_src.operate_date);
	des2src(rPack->semp_pwd2, register_src.operate_time);
	
	writelog(LOG_ERR, "stuemp_no=[%22.22s], name=[%20.20s], flag=[%d]", register_src.stuemp_no, register_src.cut_name, register_src.register_flag);
	// update records
	ret = DB_t_tif_register_pay_read_lock_by_cur_and_stuemp_no(register_src.stuemp_no, &register_tmp);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
		{	
			writelog(LOG_ERR,"DB_t_tif_register_pay_read_lock_by_cur_and_stuemp_no not found");
			ret = E_DB_REGISTER_PAY_N;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_tif_register_pay_read_lock_by_cur_and_stuemp_no errorcode=[%d]", ret);
			ret = E_DB_REGISTER_PAY_R;
		}
		goto L_RETU;
	}	

	if (register_tmp.register_flag == register_src.register_flag) 
	{
		ret = E_DB_REGISTER_PAY_NOTNEEDUPDATE;
		goto L_RETU;
	}

	rPack->lvol5 = register_tmp.register_flag;
	memcpy(&register_tmp, &register_src, sizeof(register_src));
	ret = DB_t_tif_register_pay_update_lock_by_cur(&register_tmp);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
			ret = E_DB_REGISTER_PAY_N;
		else
			ret = E_DB_REGISTER_PAY_U;
		goto L_RETU;
	}

	DB_t_tif_register_pay_free_lock_cur();

	DoInsertRegisterLog(rPack);
	
	ret = db_commit();
	if (ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}

	// 按照第1, 3, 4情况批量冻结
	writelog(LOG_ERR, "fetch_select stuemp_no=[%22.22s], name=[%20.20s], flag=[%d]", register_src.stuemp_no, register_src.cut_name, register_src.register_flag);
	// 以注册缴费信息表中的数据查询到客户信息表进行冻结
	ret = DB_t_cif_customer_read_by_stuemp_no(register_src.stuemp_no, &t_customer);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"DB_t_cif_customer_read_by_stuemp_no not found!");
			ret = E_STUNO_NOT_EXIST;
			goto L_RETU;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_cif_customer_read_by_stuemp_no error, errcode=[%d]!",ret);
			ret = E_DB_CUSTOMER_R;
			goto L_RETU;
		}
	}
	
	ret = get_tradecard_no_by_stupid(t_customer.stuemp_no, &card_id);
	if (ret)
	{
		writelog(LOG_DEBUG,"Get_tradecard_no_by_stupid stuemp[%s] error,errcode=[%d]",t_customer.stuemp_no,ret);
		goto L_RETU;
	}

	ret = freezecard(card_id, t_customer.cut_id, "system",0,0);
	if (ret)
	{
		writelog(LOG_DEBUG,"Freezecard customer error,errcode[%d],cut_id[%d],card_id[%d]",ret,t_customer.cut_id,card_id);
		goto L_RETU;
	}

	return 0;
L_RETU:
	return ret;

LRet:
	db_rollback();
	return ret;
}

int DoRegisterInput(ST_PACK *rPack)
{
	int ret = 0;
	int cnt = 0;
	int card_id = 0;
	char logicdate[11] = "";
	char sysdate[11] = "";
	T_t_cif_customer t_customer;
	// 导入数据
	T_t_tif_register_pay register_src, register_tmp;
	T_t_tif_register_info register_info;

	memset(&register_src, 0, sizeof(register_src));
	memset(&register_tmp, 0, sizeof(register_tmp));
	memset(&t_customer, 0, sizeof(t_customer));
	memset(&register_info, 0, sizeof(register_info));

	des2src(register_src.cut_name, rPack->semail);
	des2src(register_src.stuemp_no, rPack->scust_auth);
	register_src.register_flag = rPack->lvol0;					// regiser flag
	register_src.flag = 0;										// update flag
	register_src.reserver_no1 = rPack->lvol1;					// register login and logout flag
	
	ret = DB_t_tif_register_info_read_by_register_flag(register_src.register_flag, &register_info);
	if (ret)
	{
		// 此处如果读取不正确应该给个默认值
		des2src(register_src.register_info, "");
	}

	des2src(register_src.register_info, register_info.register_info);
	getsysdate(register_src.operate_date);
	getsystime(register_src.operate_time);	
	des2src(rPack->semp_pwd, register_src.operate_date);
	des2src(rPack->semp_pwd2, register_src.operate_time);
	
	writelog(LOG_ERR, "stuemp_no=[%22.22s], name=[%20.20s], flag=[%d]", register_src.stuemp_no, register_src.cut_name, register_src.register_flag);
	ret = DB_t_tif_register_pay_read_by_stuemp_no(register_src.stuemp_no, &register_tmp);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
		{	
			ret = DB_t_tif_register_pay_add(&register_src);
			if (ret)
			{
				writelog(LOG_ERR,"DB_t_tif_register_add rows[%d] error,errcode=[%d]",cnt, ret);
				goto LRet;
			}
		}
		else
		{
			ret = E_DB_REGISTER_PAY_R;
			goto L_RETU;
		}
	}
	else		// already have records 
	{
		// update records
		if (register_tmp.register_flag == register_src.register_flag)
		{
			// if need to update log flag, elapse next code and update register record 
			if (register_tmp.flag == register_src.flag)
			{
				writelog(LOG_ERR,"flag to be equal register stuemp_no = [%s]", register_tmp.stuemp_no);
				return 0;
			}
		}

		ret = DB_t_tif_register_pay_read_lock_by_cur_and_stuemp_no(register_src.stuemp_no, &register_tmp);
		if (ret)
		{
			if (DB_NOTFOUND == ret)
			{	
				writelog(LOG_ERR,"DB_t_tif_register_pay_read_lock_by_cur_and_stuemp_no not found");
				ret = E_DB_REGISTER_PAY_N;
			}
			else
			{
				writelog(LOG_ERR,"DB_t_tif_register_pay_read_lock_by_cur_and_stuemp_no errorcode=[%d]", ret);
				ret = E_DB_REGISTER_PAY_R;
			}
			goto L_RETU;
		}	

		rPack->lvol5 = register_tmp.register_flag;
		memcpy(&register_tmp, &register_src, sizeof(register_src));
		ret = DB_t_tif_register_pay_update_lock_by_cur(&register_tmp);
		if (ret)
		{
			if (DB_NOTFOUND == ret)
				ret = E_DB_REGISTER_PAY_N;
			else
				ret = E_DB_REGISTER_PAY_U;
			goto L_RETU;
		}

		DB_t_tif_register_pay_free_lock_cur();
	}
	
	DoInsertRegisterLog(rPack);

	if (register_src.flag)					// update flag logout and not to freeze this card
	{
		return 0;	
	}
	
	// 按照第1, 3, 4情况批量冻结
	writelog(LOG_ERR, "fetch_select stuemp_no=[%22.22s], name=[%20.20s], flag=[%d]", register_src.stuemp_no, register_src.cut_name, register_src.register_flag);
	// 以注册缴费信息表中的数据查询到客户信息表进行冻结
	ret = DB_t_cif_customer_read_by_stuemp_no(register_src.stuemp_no, &t_customer);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"DB_t_cif_customer_read_by_stuemp_no not found!");
			ret = E_STUNO_NOT_EXIST;
			goto L_RETU;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_cif_customer_read_by_stuemp_no error, errcode=[%d]!",ret);
			ret = E_DB_CUSTOMER_R;
			goto L_RETU;
		}
	}
	
	ret = get_tradecard_no_by_stupid(t_customer.stuemp_no, &card_id);
	if (ret)
	{
		writelog(LOG_DEBUG,"Get_tradecard_no_by_stupid stuemp[%s] error,errcode=[%d]",t_customer.stuemp_no,ret);
		goto L_RETU;
	}

	ret = freezecard(card_id, t_customer.cut_id, "system",0,0);
	if (ret)
	{
		writelog(LOG_DEBUG,"Freezecard customer error,errcode[%d],cut_id[%d],card_id[%d]",ret,t_customer.cut_id,card_id);
	}

	return 0;
L_RETU:
	return ret;

LRet:
	db_rollback();
	return ret;
}

int DoRegisterFileUpdate(ST_PACK *rPack)
{
	int ret = 0;
	int cnt = 0;
	int card_id = 0;
	char logicdate[11] = "";
	char sysdate[11] = "";
	FILE *fp = NULL;
	T_t_cif_customer t_customer;
	// 导入数据
	T_t_tif_register_pay register_src, register_tmp;
	T_t_tif_register_info register_info;

	memset(&register_src, 0, sizeof(register_src));
	memset(&register_tmp, 0, sizeof(register_tmp));
	memset(&t_customer, 0, sizeof(t_customer));
	memset(&register_info, 0, sizeof(register_info));

	HRBGC_ZCJF_FILE hrbgc_zcjf;						// 哈尔滨工程大学注册缴费结构
	memset(&hrbgc_zcjf, 0, sizeof(hrbgc_zcjf));

	if ((fp = fopen(rPack->sbankname, "rb")) == NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]", rPack->sbankname);
		ret = E_TRANS_COMP_OPENFILE;
		goto L_RETU;
	}

	// 获取对账文件第一条记录
	if (NULL == fgets((char *)(&hrbgc_zcjf), sizeof(hrbgc_zcjf), fp))	
	{
		writelog(LOG_ERR,"fgets error");
		ret = E_TRANS_COMP_GETRECORD;
		goto L_RETU;
	}	

	while (1)
	{
		memset(&register_src, 0, sizeof(register_src));
		des2src(register_src.stuemp_no, hrbgc_zcjf.stuemp_no);
		strncpy(register_src.cut_name, ntrim(hrbgc_zcjf.name, sizeof(hrbgc_zcjf.name)), sizeof(hrbgc_zcjf.name) - 1);
		register_src.register_flag = hrbgc_zcjf.flag[0] - 0x30; 
		register_src.flag = hrbgc_zcjf.log_flag[0] - 0x30;
		ret = DB_t_tif_register_info_read_by_register_flag(register_src.register_flag, &register_info);
		if (ret)
		{
			// 此处如果读取不正确应该给个默认值
			des2src(register_src.register_info, "");
		}
	
		des2src(register_src.register_info, register_info.register_info);
		getsysdate(register_src.operate_date);
		getsystime(register_src.operate_time);
		des2src(rPack->semp_pwd, register_src.operate_date);
		des2src(rPack->semp_pwd2, register_src.operate_time);
	
		writelog(LOG_ERR, "stuemp_no=[%22.22s], name=[%20.20s], flag=[%d]", register_src.stuemp_no, register_src.cut_name, register_src.register_flag);
		// add records
		ret = DB_t_tif_register_pay_read_by_stuemp_no(register_src.stuemp_no, &register_tmp);
		if (ret)
		{
			if (DB_NOTFOUND == ret)
			{	
				ret = DB_t_tif_register_pay_add(&register_src);
				if (ret)
				{
					writelog(LOG_ERR,"DB_t_tif_register_add rows[%d] error,errcode=[%d]",cnt, ret);
					goto LRet;
				}
			}
			else
			{
				ret = E_DB_REGISTER_PAY_R;
				goto L_RETU;
			}
		}
		else		// already have records 
		{
			// update records
			if (register_tmp.register_flag == (hrbgc_zcjf.flag[0] - 0x30))
			{
				// if need to update log flag, elapse next code and update register record 
				if (register_tmp.flag == (hrbgc_zcjf.log_flag[0] - 0x30))
				{
					writelog(LOG_ERR,"flag to be equal register stuemp_no=[%s] hrbgc_zcjf stuemp_no=[%s]", register_tmp.stuemp_no, hrbgc_zcjf.stuemp_no);
					goto L_RETU1;
				}
			}

			ret = DB_t_tif_register_pay_read_lock_by_cur_and_stuemp_no(register_src.stuemp_no, &register_tmp);
			if (ret)
			{
				if (DB_NOTFOUND == ret)
				{	
					writelog(LOG_ERR,"DB_t_tif_register_pay_read_lock_by_cur_and_stuemp_no not found");
					ret = E_DB_REGISTER_PAY_N;
				}
				else
				{
					writelog(LOG_ERR,"DB_t_tif_register_pay_read_lock_by_cur_and_stuemp_no errorcode=[%d]", ret);
					ret = E_DB_REGISTER_PAY_R;
				}
				goto L_RETU;
			}	

			rPack->lvol5 = register_tmp.register_flag;
			memcpy(&register_tmp, &register_src, sizeof(register_src));
			ret = DB_t_tif_register_pay_update_lock_by_cur(&register_tmp);
			if (ret)
			{
				if (DB_NOTFOUND == ret)
					ret = E_DB_REGISTER_PAY_N;
				else
					ret = E_DB_REGISTER_PAY_U;
				goto L_RETU;
			}

			DB_t_tif_register_pay_free_lock_cur();
		}

		DoInsertRegisterLog(rPack);
		
		ret = db_commit();
		if (ret)
		{
			writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
			goto LRet;
		}

L_RETU1:
		cnt++;
		if (NULL == fgets((char *)(&hrbgc_zcjf), sizeof(hrbgc_zcjf), fp))	
		{
			writelog(LOG_ERR,"no more records get!");
			break;
		}
	}
	
	if (fclose(fp))
	{
		writelog(LOG_ERR,"Close file error,file=[%s]", rPack->sbankname);
		goto L_RETU;
	}

	// 按照第三种和第四种情况批量冻结
	cnt = 0;
	getsysdate(sysdate);
	ret = DB_t_tif_register_pay_open_select_by_cur2_and_operate_date(sysdate);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_register_pay_open_select_by_cur2_and_operate_date errorcode=[%d], systdate=[%s]", ret, sysdate);
		goto LRet;
	}

	writelog(LOG_ERR,"DB_t_tif_register_pay_open_select_by_cur2_and_operate_date systdate=[%s]", sysdate);
	while(1)
	{
		memset(&register_src, 0, sizeof(register_src));
		ret = DB_t_tif_register_pay_fetch_select_by_cur2(&register_src);
		if (ret)
		{
			DB_t_tif_register_pay_close_select_by_cur2();
			if(ret == DB_NOTFOUND)
			{
				writelog(LOG_DEBUG,"There have no more record from t_tif_register table!");
				break;
			}
			else
			{
				writelog(LOG_DEBUG,"DB_t_tif_register_pay_fetch_select_by_cur2 errorcode=[%d]", ret);
				goto LRet;
			}
		}

		writelog(LOG_ERR, "fetch_select stuemp_no=[%22.22s], name=[%20.20s], flag=[%d]", register_src.stuemp_no, register_src.cut_name, register_src.register_flag);
		if (register_src.register_flag != REGISTER_FULL)
		{
			// 以注册缴费信息表中的数据查询到客户信息表进行冻结
			ret = DB_t_cif_customer_read_by_stuemp_no(register_src.stuemp_no, &t_customer);
			if (ret)
			{
				if (DB_NOTFOUND == ret)
				{
					writelog(LOG_ERR,"DB_t_cif_customer_read_by_stuemp_no not found!");
					continue;
				}
				else
				{
					writelog(LOG_ERR,"DB_t_cif_customer_read_by_stuemp_no error, errcode=[%d]!",ret);
					break;
				}
			}
		
			ret = get_tradecard_no_by_stupid(t_customer.stuemp_no, &card_id);
			if (ret)
			{
				writelog(LOG_DEBUG,"Get_tradecard_no_by_stupid stuemp[%s] error,errcode=[%d]",t_customer.stuemp_no,ret);
				continue;
			}

			writelog(LOG_DEBUG,"card_id=[%d] cut_id=[%d]", card_id, t_customer.cut_id);
			ret = freezecard(card_id, t_customer.cut_id, "system",0,0);
			if (ret)
			{
				writelog(LOG_DEBUG,"Freezecard customer error,errcode[%d],cut_id[%d],card_id[%d]",ret,t_customer.cut_id,card_id);
				continue;
			}
			cnt++;
		}
		else
		{
			writelog(LOG_ERR,"not found freeze stuemp_no =[%s]", register_src.stuemp_no);
			continue;
		}
	}
	
	return 0;

L_RETU:
	return ret;

LRet:
	db_rollback();
	return ret;
}

int F847326(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	char path_name[256] = "";
	char file_name[256] = "";
	int i = 0;	
	int card_id = 0;
	int input_flag = 0;
	input_flag = rPack->lvol2;

	ret = GetParameter(GLOBAL_UPLOAD_PATH, path_name);
	if (ret)
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}

	strcat(file_name, path_name);
	strcat(file_name, "/");
	strcat(file_name, rPack->scard0);
	des2src(rPack->sbankname, file_name);

	writelog(LOG_ERR,"input flag = [%d]",input_flag);
	switch(input_flag)
	{
	case 0:
		ret = DoRegisterFileUpdate(rPack);
		break;
	case 1:
		ret = DoRegisterInput(rPack); 
		break;
	case 2:
		ret = DoRegisterModify(rPack);
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}

	if (ret) { goto L_RETU; }
	
	ret = db_commit();
	if (ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]", ret);
		db_rollback();
		goto L_RETU;
	}
	
	return 0;
	
L_RETU:
	*pRetCode = ret;
	return ret;
}

