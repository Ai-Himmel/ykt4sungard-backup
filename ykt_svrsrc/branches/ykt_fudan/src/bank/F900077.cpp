/* ----------------------------------------------------------
 * 程序名称：F900077.cpp
 * 创建日期：2004-09-09
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：转帐服务程序
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/

#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "errdef.h"
#include "mypub.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "fdsqc.h"
#include "transinfo.h"
#include "bank.h"
#include "shem.h"

#ifndef	SEGSIZE
	#define 	SEGSIZE	1024
#endif
#ifndef DEBUG
	#define DEBUG
#endif
#define CHECK_BANK_LOGIN	if(shm[3]!=1) goto L_RET_BANK_NOT_LOGIN;


// {900077 ,F900077,"转帐服务程序" ,"hhd"       ,1,     false,0,0,0,0,0},
//查询转帐流水
int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID * handle,int *pRetCode,char *szMsg);
int query_subsidy(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int get_subsidy(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_update_card_info(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int query_mendcard_info(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_mendcard(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int mendcard_make_sure(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int query_netcharge_accinfo(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_netcharge_acc(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_netcharge_check(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_remain_board_reckon(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);


int F900077(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{

	int ret=0;
	char tradecode[6+1]="";
	char op_datetime[15]="";

	// 此处检查银行登陆状态,可能过于严格,可转移到switch中需要银行登陆的功能中
	if(!BANK_LOGIN)
	{
		*pRetCode=E_TRANS_BANK_NETERR;
		return *pRetCode;
	}

	T_t_mif_devmonitor 		devmonitor;
	memset(&devmonitor,0,sizeof(devmonitor));
	
	INNER_TRANS_REQUEST 	from_pos,to_pos;
	//BANK_TRANS_REQUEST		from_bank;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	// 用于根据请求包整理本CPACK包的头清空包头位图和包体中的数据
	ResetNormalCPack(&aPack,0,1);

	//初始化交换结构
	memset(&from_pos,0,sizeof(from_pos));
	//从输入cpack中提取数据，填充到通用交换数据结构中
	memcpy(from_pos.TradeCode,in_pack->sclose_emp,sizeof(from_pos.TradeCode));		//交易代码
	memcpy(from_pos.TransMoney,in_pack->sorder0,sizeof(from_pos.TransMoney));		//交易金额
	memcpy(from_pos.ExtraMoney,in_pack->sorder1,sizeof(from_pos.ExtraMoney));		//附加交易金额
	Strncpy_t(from_pos.AccountMoney,in_pack->sserial1,sizeof(from_pos.AccountMoney));	//校园卡帐户金额
	from_pos.SendNo=in_pack->lvol0;												//发起方流水号
	from_pos.RecvNo=in_pack->lvol1;												//接受方流水号
	memcpy(from_pos.TradeDate,in_pack->sdate0,sizeof(from_pos.TradeDate));			//交易日期	 YYYYMMDD
	memcpy(from_pos.TradeTime,in_pack->stime0,sizeof(from_pos.TradeTime));			//交易时间	 HHMMSS
	memcpy(from_pos.BankDate,in_pack->sdate1,sizeof(from_pos.BankDate));			//银行处理日期
	memcpy(from_pos.BankTime,in_pack->stime1,sizeof(from_pos.BankTime));			//银行处理时间
	memcpy(from_pos.Balance,in_pack->scust_no,sizeof(from_pos.Balance));			//银行卡余额
	memcpy(from_pos.RetCode,in_pack->schange_emp,sizeof(from_pos.RetCode));		//交易结果
	memcpy(from_pos.CardNo,in_pack->sserial0,sizeof(from_pos.CardNo));				//校园卡卡号
	from_pos.Notecase=in_pack->lvol2;												//校园卡对应钱包号
	memcpy(from_pos.BankCardNo,in_pack->scust_auth,sizeof(from_pos.BankCardNo));	//银行卡号
	from_pos.MngFeeFlag=atoi(in_pack->sstatus1);									//手续费标志
	memcpy(from_pos.AccountPwd,in_pack->semp_pwd,sizeof(from_pos.AccountPwd));	//校园账户密码
	memcpy(from_pos.AccountNewPwd,in_pack->semp_pwd2,sizeof(from_pos.AccountNewPwd));	//校园账户新密码
	memcpy(from_pos.BankCardPwd,in_pack->sstation0,sizeof(from_pos.BankCardPwd));			//银行账户密码
	memcpy(from_pos.BankCardNewPwd,in_pack->sstation1,sizeof(from_pos.BankCardNewPwd));	//银行账户新密码
	memcpy(from_pos.TerminalId,in_pack->sorder2,sizeof(from_pos.TerminalId));				//终端编号

	//判断交易代码，进行相应处理
	//switch(241031)
	//int temp=atoi(from_pos.TradeCode);
	//printf("this is test record:atoi(from_pos.TradeCode)=[%d]\n",temp);

	SetCol(handle,0);
   	SetCol(handle,F_SCLOSE_EMP,F_SORDER0,F_SORDER1,F_SSERIAL1,F_LVOL0,F_LVOL1,F_SDATE0,F_STIME0,F_SDATE1,F_STIME1,F_SCUST_NO,F_SCHANGE_EMP,F_SSERIAL0,F_LVOL2,F_SCUST_AUTH,F_SSTATUS1,F_SEMP_PWD,F_SEMP_PWD2,F_SSTATION0,F_SSTATION1,F_SORDER2,0);

	memcpy(tradecode,from_pos.TradeCode,sizeof(from_pos.TradeCode));
	tradecode[6]=0;
	writelog(LOG_INFO,"Trade start,trade code=[%6.6s],card_id=[%s],bankcardno=[%s],TerminalId=[%s]!",tradecode,from_pos.CardNo,from_pos.BankCardNo,from_pos.TerminalId);
	switch(atoi(tradecode))
	{

		case TRADE_INNER_QUERYBANK:
			ret=Pos_QueryBank(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			memcpy(&to_pos,&from_pos,sizeof(to_pos));
			break;
		case TRADE_INNER_TRANS:
			ret=Pos_Transfer(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			memcpy(&to_pos,&from_pos,sizeof(to_pos));
			break;
		case TRADE_INNER_FEE:
			ret=Pos_Fee(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			memcpy(&to_pos,&from_pos,sizeof(to_pos));
			break;
		case TRADE_INNER_ADDRELATION:
			ret=Pos_AddRelation(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			memcpy(&to_pos,&from_pos,sizeof(to_pos));
			break;
		case TRADE_INNER_DELRELATION:
			ret=Pos_DelRelation(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			memcpy(&to_pos,&from_pos,sizeof(to_pos));
			break;
		case TRADE_INNER_POSLOGIN:
			ret=Pos_Login(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			memcpy(&to_pos,&from_pos,sizeof(to_pos));
			break;
		case TRADE_INNER_QUERYINNER:
			ret=Pos_QuerySchool(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			memcpy(&to_pos,&from_pos,sizeof(to_pos));
			break;
		case TRADE_INNER_CHANGEPWD:
			ret=Pos_ChangePwd(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			memcpy(&to_pos,&from_pos,sizeof(to_pos));
			break;
		case TRADE_INNER_LOST:
			ret=Pos_LostCard(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			memcpy(&to_pos,&from_pos,sizeof(to_pos));
			break;
		case TRADE_INNER_UNLOST:
			ret=Pos_UnlostCard(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			memcpy(&to_pos,&from_pos,sizeof(to_pos));
			break;
		case TRADE_INNER_QUERYSERIAL:
			ret=Pos_QuerySerial(&from_pos,handle,pRetCode,szMsg);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			return 0;
		case TRADE_INNER_WRITEERRCARD:
			ret=Pos_WriteErrCard(&from_pos);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			break;
		//前台发起部分，包括签到、签退、对帐等
		case TRADE_INNER_LOGIN:
			writelog(LOG_ERR,"start inner login!");
			break;
		//查询补助信息
		case TRADE_INNER_QUERYSUBSIDY:
			ret=query_subsidy(in_pack,handle,pRetCode,szMsg);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			return 0;
		//领取补助
		case TRADE_INNER_GETSUBSIDY:
			ret=get_subsidy(in_pack,handle,pRetCode,szMsg);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			return 0;
		case TRADE_INNER_UPDATE_CARDINFO:
			ret = do_update_card_info(in_pack,handle,pRetCode,szMsg);
			if(ret)
			{
				*pRetCode = ret;
				goto L_RETU;
			}
			return 0;
		//查询补写卡信息
		case TRADE_INNER_QUERY_MENDCARD_INFO:
			getsysdatetime(op_datetime);
			devmonitor.device_id=atoi(in_pack->sorder2);			//设备ID
			devmonitor.beatstate=0;
			des2src(devmonitor.op_time, op_datetime);
			des2src(devmonitor.collect_time, op_datetime);
			des2src(devmonitor.devtime, in_pack->sdate0);
		//	des2src(devmonitor.devtime+8, in_pack->stime0);   
			Strncpy(devmonitor.devtime+8, in_pack->stime0,14);
			ret = DB_t_mif_devmonitor_update_by_device_id(devmonitor.device_id, &devmonitor);
			writelog(LOG_INFO,"mif_devmonitor update device_id[%d],retcode[%d]",devmonitor.device_id,ret);
			if(ret)
			{
				if(ret ==DB_NOTFOUND)
				{	
					ret = DB_t_mif_devmonitor_add(&devmonitor);
					if(ret)
					{
						writelog(LOG_ERR,"devmonitor_add device_id[%d]errcode[%d]",devmonitor.device_id,ret);
						goto L_query;
					}
				}
				else
				{
					writelog(LOG_ERR,"devmonitor_update device_id[%d]errcode[%d]",devmonitor.device_id,ret);
					goto L_query;
				}
			}
	           
			if(db_commit())
				writelog(LOG_ERR,"commit [%d] devmonitor err",devmonitor.device_id);
L_query:				
			ret = query_mendcard_info(in_pack, handle, pRetCode, szMsg);
			if (ret)
			{
//				*pRetCode = ret;
				goto L_RETU;
			}
			return 0;
		//补写卡信息
		case TRADE_INNER_MEND_CARD:
			ret = do_mendcard(in_pack, handle, pRetCode, szMsg);
			if (ret)
			{
//				*pRetCode = ret;
				goto L_RETU;
			}
			return 0;
		//补写卡确认
		case TRADE_INNER_MEND_CARD_MAKE_SURE:
			ret = mendcard_make_sure(in_pack, handle, pRetCode, szMsg);
			if (ret)
			{
//				*pRetCode = ret;
				goto L_RETU;
			}
			return 0;
		//查询机房网络收费帐户信息
		case TRADE_INNER_QUERY_NETCHARGE_ACCINFO:
			ret = query_netcharge_accinfo(in_pack, handle, pRetCode, szMsg);
			if (ret)
			{
				*pRetCode = ret;
				goto L_RETU;
			}
			return 0;
		//网络收费帐户转账
		case TRADE_INNER_NETCHARGE_ACC_TRANS:
			ret = do_netcharge_acc(in_pack, handle, pRetCode, szMsg);
			if (ret)
			{
				*pRetCode = ret;
				writelog(LOG_INFO,"trade_inner_netcharge_acc_trans_errcode [%d]", ret);
				goto L_RETU;
			}
			return 0;
		//网络收费检查
		case TRADE_INNER_NETCHARGE_CHECK:
			ret = do_netcharge_check(in_pack, handle, pRetCode, szMsg);
			if (ret)
			{
				*pRetCode = ret;
				goto L_RETU;
			}
			return 0;
		case TRADE_INNER_REMAIN_BOARD_RECKON:
			ret = do_remain_board_reckon(in_pack, handle, pRetCode, szMsg);
			if (ret)
			{
				*pRetCode = ret;
				goto L_RETU;
			}
			return 0;
		default:
			writelog(LOG_INFO,"This trade can't supplied,tradecode=[%d]!",atoi(tradecode));
			*pRetCode=E_TRANS_FUNC_NONSUPPORT;
			goto L_RETU;
	}
	Strncpy_t(out_pack->sclose_emp,to_pos.TradeCode,sizeof(out_pack->sclose_emp));
	Strncpy_t(out_pack->sorder0,to_pos.TransMoney,sizeof(out_pack->sorder0));
	Strncpy_t(out_pack->sorder1,to_pos.ExtraMoney,sizeof(out_pack->sorder1));
	Strncpy_t(out_pack->sserial1,to_pos.AccountMoney,sizeof(out_pack->sserial1));
	out_pack->lvol0=to_pos.SendNo;
	out_pack->lvol1=to_pos.RecvNo;
	Strncpy_t(out_pack->sdate0,to_pos.TradeDate,sizeof(out_pack->sdate0));
	Strncpy_t(out_pack->stime0,to_pos.TradeTime,sizeof(out_pack->stime0));
	Strncpy_t(out_pack->sdate1,to_pos.BankDate,sizeof(out_pack->sdate1));
	Strncpy_t(out_pack->stime1,to_pos.BankTime,sizeof(out_pack->stime1));
	Strncpy_t(out_pack->scust_no,to_pos.Balance,sizeof(out_pack->scust_no));
	Strncpy_t(out_pack->schange_emp,to_pos.RetCode,sizeof(out_pack->schange_emp));
	Strncpy_t(out_pack->sserial0,to_pos.CardNo,sizeof(out_pack->sserial0));
	out_pack->lvol2=to_pos.Notecase;
	Strncpy_t(out_pack->scust_auth,to_pos.BankCardNo,sizeof(out_pack->scust_auth));
	sprintf(out_pack->sstatus1,"%c",to_pos.MngFeeFlag);
	Strncpy_t(out_pack->semp_pwd,to_pos.AccountPwd,sizeof(out_pack->semp_pwd));
	Strncpy_t(out_pack->semp_pwd2,to_pos.AccountNewPwd,sizeof(out_pack->semp_pwd2));
	Strncpy_t(out_pack->sstation0,to_pos.BankCardPwd,sizeof(out_pack->sstation0));
	Strncpy_t(out_pack->sstation1,to_pos.BankCardNewPwd,sizeof(out_pack->sstation1));
	Strncpy_t(out_pack->sorder2,to_pos.TerminalId,sizeof(out_pack->sorder2));

	PutRow(handle,out_pack,pRetCode,szMsg);

	writelog(LOG_INFO,"Trade succeed,trade code=[%6.6s]!",to_pos.TradeCode);
	return 0;

L_RETU:

	//writelog(LOG_ERR,"Trade faild,trade code=[%s],return code=[%d]!",to_pos.TradeCode,*pRetCode);
	return *pRetCode;

L_RET_BANK_NOT_LOGIN:

	writelog(LOG_ERR,"Trade faild,trade code=[%s],return code=[%d]!",to_pos.TradeCode,*pRetCode);
	*pRetCode=E_TRANS_BANK_NETERR;
	return *pRetCode;

}


