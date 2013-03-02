/* ----------------------------------------------------------
 * 程序名称：bank.cpp
 * 创建日期：2005-03-10 14:58
 * 程序作者：林钦
 * 版本信息：1.0.0.0
 * 程序功能：银行转帐各种交易函数实现
 * ----------------------------------------------------------
 * 修改日期: 2005-03-25
 * 修改人员: 韩海东
 * 修改描述: 冲正的使用密钥由静态密钥改称动态密钥，调用gen_mac函数
 * 版本信息：1.0.1.0
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bank.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bankdb.h"
#include "pubdb.h"

int debug = 3;

char * strnscpy(char *dst, char* src, int len)
{
	int i=0;
	for(i=0; *src!=0 && i<len; i++)
		*dst++ = *src++;
	for(;i<len;i++)
		*dst++ = ' ';

	return dst;

}

void TRACE_BANK_TRANS(BANK_TRANS_REQUEST *pTransPak, char *stage)
{
	if(debug == 0)
		return;

	printf("----------%s----------\n",stage);

	if(debug < 2)
		return;
	char a[16]="";
	printf("交易代码	=[%2.2s]\n",pTransPak->TradeCode);
	printf("交易结果	=[%2.2s]\n",pTransPak->RetCode);
	printf("交易日期	=[%8.8s]\n",pTransPak->TradeDate);
	printf("交易时间	=[%6.6s]\n",pTransPak->TradeTime);
	printf("校园卡帐号	=[%10.10s]\n",pTransPak->CustAccountNo);
	printf("银行卡号	=[%20.20s]\n",pTransPak->BankCardNo);
	printf("商户号 		=[%10.10s]\n",pTransPak->MercAccount);
	printf("转账金额	=[%9.9s]\n",pTransPak->TransMoney);
	printf("借记卡余额	=[%9.9s]\n",pTransPak->Balance);
	memcpy(a,pTransPak->BankCardPwd,16);
	printf("银行卡密码	=[%16.16s]\n",pTransPak->BankCardPwd);
	//printf("银行卡密码	=[%16.16s]\n","****************");
	printf("校园端流水号	=[%8.8s]\n",pTransPak->CustSn);
	printf("银行流水号	=[%20.20s]\n",pTransPak->BankSn);
	printf("学校代号	=[%16.16s]\n",pTransPak->CustNo);
	printf("自动转账标志	=[%d]\n",pTransPak->AutoFlag);
	printf("校验		=[%8.8s]\n",pTransPak->MAC);
	//printf("校验		=[%8.8s]\n","********");

};

/****************************************************
银行端交易处理函数
lq, 20050310，从transinfo.cpp移过来，以与bu相关代码脱离
!! 在取用银行密码时，一定要获取信号量
	p(semid);
	operations...;
	v(semid)
可视情况调整信号量控制的代码范围
如果银行对同一账户操作有并发限制，则将信号量控制扩大到整个操作
****************************************************/

//检查线路处理过程
int Do_CheckLine( BANK_TRANS_REQUEST *pBankTrans )
{

	char mac_key[32]="";
	//char mac[16]="";
	int ret;

	BANK_TRANS_REQUEST BankTransPak;

	memcpy(mac_key,STATIC_KEY,sizeof(mac_key));
	memset(&BankTransPak,0,BANK_TRANS_PACKLEN);

	//写交易代码
	memcpy( BankTransPak.TradeCode,TRADE_BANK_CHECKLINE, sizeof(BankTransPak.TradeCode));
	//写交易日期和交易时间
	getsysdate(BankTransPak.TradeDate);
	getsystime(BankTransPak.TradeTime);
	//写院校代码
	sprintf(BankTransPak.CustNo,"%-16s",SCHOOL_CODE);

	//写校验mac码----林钦此处应该用银行回传回来的动态密钥做mac密钥，此处改过来了
	generate_mac((char*)(&BankTransPak),sizeof(BankTransPak),BankTransPak.MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(&BankTransPak,"send checkline package");

	//发送数据到银行并同时接收银行数据，此处不判断返回的mac校验
	ret=send_to_and_recv_from_bank((char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,0);

	if(ret!=0)
	{
		writelog(LOG_ERR,"调用银行通信失败[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}

	TRACE_BANK_TRANS(&BankTransPak, "recv checkline package");

	//此处银行说不加mac传输的，所以此处不做校验
	/*
	ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,mac);
	ret=memcmp(mac,BankTransPak.MAC,8);
	if(ret!=0)
	{
		writelog(LOG_INFO,"数据校验错误");
		return	E_TRANS_BANK_RECVERR;
	}
	*/
	memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	return 0;

}

//签到交易处理过程
int Do_Login  (BANK_TRANS_REQUEST *pBankTrans)
{
	char mac_key[32]="";
	//char mac[16]="";
	int ret;

	BANK_TRANS_REQUEST BankTransPak;

	memcpy(mac_key,STATIC_KEY,sizeof(mac_key));
	memset(&BankTransPak,0,BANK_TRANS_PACKLEN);

	//写交易代码---------银行说把签到换成密钥交换，暂时把31-->34
	memcpy( BankTransPak.TradeCode,TRADE_BANK_CHGKEY, sizeof(BankTransPak.TradeCode));
	//写交易日期和交易时间
	getsysdate(BankTransPak.TradeDate);
	getsystime(BankTransPak.TradeTime);
	//写院校代码
	sprintf(BankTransPak.CustNo,"%-16s",SCHOOL_CODE);
	//写校验mac码

	ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(&BankTransPak,"send login package");

	//发送数据到银行并同时接收银行数据，此处不判断返回的mac校验
	ret=send_to_and_recv_from_bank((char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,0);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return ret;
	}
	//printf("%d\n",__LINE__);
	TRACE_BANK_TRANS(&BankTransPak,"recv login package");

	//此处银行说不加mac传输的，所以此处不做校验
	/*
	ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,mac);
	ret=memcmp(mac,BankTransPak.MAC,8);
	if(ret)
	{
		writelog(LOG_INFO,"Mac vertify fail,source_mac=[%s],true_mac[%s]",BankTransPak.MAC,mac);
		return	E_TRANS_BANK_RECVERR;
	}
	*/
	if(strncmp(BankTransPak.RetCode,"00",2)!=0)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return -1;
	}
	memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	writelog(LOG_INFO,"Congratulation,login to bank succeed!");
	return 0;

}

//签退交易处理过程
int Do_Quit	( BANK_TRANS_REQUEST *pBankTrans )
{

	char mac_key[32]="";
//	char mac[16]="";
	int ret;

	BANK_TRANS_REQUEST BankTransPak;

	memcpy(mac_key,STATIC_KEY,sizeof(mac_key));
	memset(&BankTransPak,0,BANK_TRANS_PACKLEN);

	//写交易代码
	memcpy( BankTransPak.TradeCode,TRADE_BANK_LOGOUT, sizeof(BankTransPak.TradeCode));
	//写交易日期和交易时间
	getsysdate(BankTransPak.TradeDate);
	getsystime(BankTransPak.TradeTime);
	//写院校代码
	sprintf(BankTransPak.CustNo,"%-16s",SCHOOL_CODE);

	//写校验mac码----林钦此处应该用银行回传回来的动态密钥做mac密钥，此处改过来了
	generate_mac((char*)(&BankTransPak),sizeof(BankTransPak),BankTransPak.MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(&BankTransPak,"send logout package");

	//发送数据到银行并同时接收银行数据，此处不判断返回的mac校验
	ret=send_to_and_recv_from_bank((char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,0);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}

	TRACE_BANK_TRANS(&BankTransPak,"recv logout package");

	//此处银行说不加mac传输的，所以此处不做校验
	/*

	ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,mac);
	ret=memcmp(mac,BankTransPak.MAC,8);
	if(ret)
	{
		writelog(LOG_INFO,"Mac vertify fail,source_mac=[%s],true_mac[%s]",BankTransPak.MAC,mac);
		return	E_TRANS_BANK_RECVERR;
	}
	*/
	memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	writelog(LOG_INFO,"Congratulation,logout from bank succeed!");
	return 0;

}

//自动转账交易处理过程
int Do_AutoTrans  ( BANK_TRANS_REQUEST *pBankTrans )
{

	return 0;

}

/** 冲正交易处理过程
假定pBankTrans里已经填好了交易数据(在bankguard.cpp里调用)
银行返回结果仍存放在pBankTrans里
*/
int Do_DeTrans  ( BANK_TRANS_REQUEST *pBankTrans )
{
	BANK_TRANS_REQUEST BankTransPak;
	memcpy((void*)&BankTransPak, (void*)pBankTrans, BANK_TRANS_PACKLEN);

	//做必要的数据预处理
	TRACE_BANK_TRANS(&BankTransPak,"send detrans package");

	int ret = send_to_and_recv_from_bank((char*)&BankTransPak, BANK_TRANS_PACKLEN, (char*)&BankTransPak, BANK_TRANS_PACKLEN,0);

	if(ret != 0)
		return ret;
	TRACE_BANK_TRANS(&BankTransPak,"recv detrans package");

	memcpy((char*)pBankTrans, (char*)&BankTransPak, BANK_TRANS_PACKLEN);

	// 调用者应该处理银行返回的BankSn

	return 0;
}

//对帐过程
int Do_Compare( BANK_TRANS_REQUEST *pBankTrans )
{
	char mac_key[32]="";
	char mac[16]="";
	int ret;

	BANK_TRANS_REQUEST BankTransPak;

	memcpy(mac_key,STATIC_KEY,sizeof(mac_key));
	memset(&BankTransPak,0,BANK_TRANS_PACKLEN);

	//写交易代码
	memcpy( BankTransPak.TradeCode,TRADE_BANK_COMP, sizeof(BankTransPak.TradeCode));
	//写交易日期和交易时间
	getsysdate(BankTransPak.TradeDate);
	getsystime(BankTransPak.TradeTime);
	//写院校代码
	sprintf(BankTransPak.CustNo,"%-16s",SCHOOL_CODE);
	//写校验mac码

	//写校验mac码----林钦此处应该用银行回传回来的动态密钥做mac密钥，此处改过来了
	generate_mac((char*)(&BankTransPak),sizeof(BankTransPak),BankTransPak.MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(&BankTransPak,"send compare package");

	//发送数据到银行并同时接收银行数据，此处不判断返回的mac校验
	ret=send_to_and_recv_from_bank((char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,0);

	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}

	TRACE_BANK_TRANS(&BankTransPak,"recv compare package");


	ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,mac);
	ret=memcmp(mac,BankTransPak.MAC,8);
	if(ret)
	{
		writelog(LOG_INFO,"Mac vertify fail,source_mac=[%s],true_mac[%s]",BankTransPak.MAC,mac);
		return	E_TRANS_BANK_RECVERR;
	}

	memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	writelog(LOG_INFO,"Congratulation, compare succeed!");

	return 0;


}
int Do_Compare_file()
{
///*
	FILE *fp;
	TIniFile tf;
	char path_name[256]="";
	char file_name[256]="";
	int ret=0;
	int cnt=0;
	int i=0;

	BANK_COMPARE_RECODE compare,compare1;
	T_t_tif_bank_comp	bank_comp;
	T_t_tif_report_trans_comp trans_comp;
	T_t_tif_tradeserial	tradeserial;
	T_t_tif_tradeserial_his his_tradeserial;
	T_t_tif_diff_transfer  diff_transfer;

	char logicdate[10]="";
	char tmp_date[10]="";
	char forward_date[10]="";

	double trans_count=0;
	double bank_count=0;
	double trans_amt=0;
	double bank_amt=0;
	double second=0;

	double temp=0;
	char *p=getenv("BIN_PATH");

	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=datetime2second(logicdate, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	 //trans_count=0;
	 //bank_count=0;
	 //trans_amt=0;
	// bank_amt=0;

	second=second-24*60*60;
	ret=second2datetime(second, forward_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}

	memset(&bank_comp,0,sizeof(bank_comp));
	memset(&compare,0,sizeof(compare));
	memset(&trans_comp,0,sizeof(trans_comp));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&his_tradeserial,0,sizeof(his_tradeserial));

	memset(&compare1,0x30,sizeof(compare1));

	ret=DB_t_tif_report_trans_comp_read_by_cmp_date(forward_date,&trans_comp);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_report_trans_comp_read_by_cmp_date error,errcode=[%d]",ret);
		goto LRet;
	}
	if(1==trans_comp.cmp_flag)
	{
		writelog(LOG_ERR,"trans_comp.cmp_flag =1,already compare!");
		goto LRet;
	}
	//配置环境变量
	if(p==NULL)
	{
	   	writelog(LOG_ERR,"Cann't get env HOME PATH\n");
	   	return -1;
	}
	//sprintf(path_name,"%s/ftp",p);
	sprintf(path_name,"%s",p);
	//strcpy(path_name,"/bank/ykt/src/bank/ftp");
	sprintf(file_name,"%s/XYK00002.%8.8s",path_name,forward_date);
	writelog(LOG_ERR,"Open indirect file=[%s]",file_name);
	if((fp = fopen(file_name,"rb"))==NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]",file_name);
		return	-1;
	}

	while(!feof(fp))
	{
		memset(&bank_comp,0,sizeof(bank_comp));
		memset(&compare,0,sizeof(compare));
		cnt++;
		if(NULL==fgets((char *)(&compare),sizeof(compare),fp))
		{
			writelog(LOG_ERR,"fgets error,");
			continue;
		}
		//不知道为什么，必须要跳一个才能对?
		if((cnt+2)%2==0)	continue;
		//开始进行赋值
		if(memcmp(&compare,&compare1,10)==0)	break;
		else
		{
			strncpy(bank_comp.op_date,forward_date,sizeof(bank_comp.op_date)-1);
			memcpy(bank_comp.tx_code,compare.TradeCode,2);
			bank_comp.card_id=atoi(compare.GDCAccount);
			memcpy(bank_comp.bankcard,compare.BankCard,20);
			bank_comp.local_sn=atoi(compare.LocalSn);
			//printf("--------local_sn[%d]=[%d]\n",cnt,bank_comp.local_sn);
			memcpy(bank_comp.bank_sn,compare.BankSn,20);
			strncpy(bank_comp.trans_money,compare.TransMomoy,9);

			ret=DB_t_tif_bank_comp_add(&bank_comp);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_tif_bank_comp_add rows[%d] error,errcode=[%d]",cnt,ret);
				goto LRet;
			}
		}
	}
	//读取对帐文件结束，关闭对仗文件，提交事务
	//printf("Line=[%d]\n",__LINE__);
	if(fclose(fp))
	{
		writelog(LOG_ERR,"Close file error,file=[%s]",file_name);
		goto LRet;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}

	//开始进行对帐
	cnt=0;

	//对总数
	ret=DB_his_t_tif_tradeserial_get_count_by_serial_type(&temp,240001,forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_get_count_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_count=trans_count+temp;
	trans_comp.localself_num=trans_count;

	ret=DB_his_t_tif_tradeserial_get_sum_by_serial_type(&temp, 240001, forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_his_t_tif_tradeserial_get_sum_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_amt=trans_amt+temp;
	trans_comp.localself_amt=trans_amt;

	ret=DB_t_tif_bank_comp_open_select_by_cur1_and_op_date(forward_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_bank_comp_open_select_by_cur1_and_op_date err,errcode=[%d]",ret);
		goto LRet;
	}
	while(1)
	{
		ret=DB_t_tif_bank_comp_fetch_select_by_cur1(&bank_comp);
		if(ret)
		{
			DB_t_tif_bank_comp_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_bankcomp table!");
						break;
					}
				else		break;
			}
			else
				goto LRet;
		}
		//增加对于非01交易码的交易的排出(比如:冲正)
		if(1!=atoi(bank_comp.tx_code)) 	{continue};
		cnt++;
		bank_count=bank_count+1;
		bank_amt=bank_amt+atof(bank_comp.trans_money)/100.00;
		memset(&diff_transfer,0,sizeof(diff_transfer));
		//printf("Line=[%d],cnt=[%d]\n",__LINE__,cnt);

		ret=DB_t_tif_tradeserial_his_read_by_bak_date_and_serial_no(forward_date,bank_comp.local_sn,&his_tradeserial);
		if(ret)
		{
			if(100==ret)
			{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
				continue;
			}
			else
			{
				writelog(LOG_ERR,"DB_t_tif_tradeserial_his_read_lock_by_c0_and_enteract_date_and_serial_no error,errcode=[%d]!",ret);
				break;
			}
		}
		if(his_tradeserial.serial_state!=2)
		{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_amt=0;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
		}
	}

	trans_comp.bankself_amt=bank_amt;
	trans_comp.bankself_num=bank_count;
	trans_comp.localself_amt=trans_amt;
	trans_comp.localself_num=trans_count;
	trans_comp.cmp_flag=1;
	strncpy(trans_comp.cmp_date,forward_date,sizeof(trans_comp.cmp_date)-1);
	ret=DB_t_tif_report_trans_comp_add(&trans_comp);
	if(ret)
	{
		writelog(LOG_DEBUG,"DB_t_tif_report_trans_comp_add error,errcode=[%d]",ret);
		goto LRet;

	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}
	return 0;

LRet:
	db_rollback();
	return ret;

	//*/
}
int Do_Compare_file_shoudong()
{
///*
	FILE *fp;
	TIniFile tf;
	char path_name[256]="";
	char file_name[256]="";
	int ret=0;
	int cnt=0;
	int i=0;

	BANK_COMPARE_RECODE compare,compare1;
	T_t_tif_bank_comp	bank_comp;
	T_t_tif_report_trans_comp trans_comp;
	T_t_tif_tradeserial	tradeserial;
	T_t_tif_tradeserial_his his_tradeserial;
	T_t_tif_diff_transfer  diff_transfer;

	char logicdate[10]="";
	char tmp_date[10]="";
	char forward_date[10]="";

	double trans_count=0;
	double bank_count=0;
	double trans_amt=0;
	double bank_amt=0;
	double second=0;

	double temp=0;
	char *p=getenv("BIN_PATH");

	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=datetime2second(logicdate, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	 //trans_count=0;
	 //bank_count=0;
	 //trans_amt=0;
	// bank_amt=0;

	second=second-24*60*60;
	ret=second2datetime(second, forward_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}

	memset(&bank_comp,0,sizeof(bank_comp));
	memset(&compare,0,sizeof(compare));
	memset(&trans_comp,0,sizeof(trans_comp));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&his_tradeserial,0,sizeof(his_tradeserial));

	memset(&compare1,0x30,sizeof(compare1));

	ret=DB_t_tif_report_trans_comp_read_by_cmp_date(forward_date,&trans_comp);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_report_trans_comp_read_by_cmp_date error,errcode=[%d]",ret);
		goto LRet;
	}
	if(1==trans_comp.cmp_flag)
	{
		writelog(LOG_ERR,"trans_comp.cmp_flag =1,already compare!");
		goto LRet;
	}
	//配置环境变量
	if(p==NULL)
	{
	   	writelog(LOG_ERR,"Cann't get env HOME PATH\n");
	   	return -1;
	}
	//sprintf(path_name,"%s/ftp",p);
	sprintf(path_name,"%s",p);
	//strcpy(path_name,"/bank/ykt/src/bank/ftp");
	sprintf(file_name,"%s/XYK00002.%8.8s",path_name,forward_date);
	writelog(LOG_ERR,"Open indirect file=[%s]",file_name);
	if((fp = fopen(file_name,"rb"))==NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]",file_name);
		return	-1;
	}

	while(!feof(fp))
	{
		memset(&bank_comp,0,sizeof(bank_comp));
		memset(&compare,0,sizeof(compare));
		cnt++;
		if(NULL==fgets((char *)(&compare),sizeof(compare),fp))
		{
			writelog(LOG_ERR,"fgets error,");
			continue;
		}
		//不知道为什么，必须要跳一个才能对?
		if((cnt+2)%2==0)	continue;
		//开始进行赋值
		if(memcmp(&compare,&compare1,10)==0)	break;
		else
		{
			strncpy(bank_comp.op_date,forward_date,sizeof(bank_comp.op_date)-1);
			memcpy(bank_comp.tx_code,compare.TradeCode,2);
			bank_comp.card_id=atoi(compare.GDCAccount);
			memcpy(bank_comp.bankcard,compare.BankCard,20);
			bank_comp.local_sn=atoi(compare.LocalSn);
			//printf("--------local_sn[%d]=[%d]\n",cnt,bank_comp.local_sn);
			memcpy(bank_comp.bank_sn,compare.BankSn,20);
			strncpy(bank_comp.trans_money,compare.TransMomoy,9);

			ret=DB_t_tif_bank_comp_add(&bank_comp);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_tif_bank_comp_add rows[%d] error,errcode=[%d]",cnt,ret);
				goto LRet;
			}
		}
	}
	//读取对帐文件结束，关闭对仗文件，提交事务
	//printf("Line=[%d]\n",__LINE__);
	if(fclose(fp))
	{
		writelog(LOG_ERR,"Close file error,file=[%s]",file_name);
		goto LRet;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}

	//开始进行对帐
	cnt=0;

	//对总数
	ret=DB_his_t_tif_tradeserial_get_count_by_serial_type(&temp,240001,forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_get_count_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_count=trans_count+temp;
	trans_comp.localself_num=trans_count;

	ret=DB_his_t_tif_tradeserial_get_sum_by_serial_type(&temp, 240001, forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_his_t_tif_tradeserial_get_sum_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_amt=trans_amt+temp;
	trans_comp.localself_amt=trans_amt;

	ret=DB_t_tif_bank_comp_open_select_by_cur1_and_op_date(forward_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_bank_comp_open_select_by_cur1_and_op_date err,errcode=[%d]",ret);
		goto LRet;
	}
	while(1)
	{
		ret=DB_t_tif_bank_comp_fetch_select_by_cur1(&bank_comp);
		if(ret)
		{
			DB_t_tif_bank_comp_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_bankcomp table!");
						break;
					}
				else		break;
			}
			else
				goto LRet;
		}
		cnt++;
		bank_count=bank_count+1;
		bank_amt=bank_amt+atof(bank_comp.trans_money)/100.00;
		memset(&diff_transfer,0,sizeof(diff_transfer));
		//printf("Line=[%d],cnt=[%d]\n",__LINE__,cnt);

		ret=DB_t_tif_tradeserial_his_read_by_bak_date_and_serial_no(forward_date,bank_comp.local_sn,&his_tradeserial);
		//流水表中没有记录的情况
		if(ret)
		{
			if(100==ret)
			{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
				continue;
			}
			else
			{
				writelog(LOG_ERR,"DB_t_tif_tradeserial_his_read_lock_by_c0_and_enteract_date_and_serial_no error,errcode=[%d]!",ret);
				break;
			}
		}
		//流水表中存在，但是没有入账的情况
		if(his_tradeserial.serial_state!=2)
		{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_amt=0;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
		}
	}

	trans_comp.bankself_amt=bank_amt;
	trans_comp.bankself_num=bank_count;
	trans_comp.localself_amt=trans_amt;
	trans_comp.localself_num=trans_count;
	trans_comp.cmp_flag=1;
	strncpy(trans_comp.cmp_date,forward_date,sizeof(trans_comp.cmp_date)-1);
	ret=DB_t_tif_report_trans_comp_add(&trans_comp);
	if(ret)
	{
		writelog(LOG_DEBUG,"DB_t_tif_report_trans_comp_add error,errcode=[%d]",ret);
		goto LRet;

	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}
	return 0;

LRet:
	db_rollback();
	return ret;

	//*/
}

int Do_Transfer(BANK_TRANS_REQUEST *pBankTrans)
{

	//char buffer[20]="";
	char temp[128]="";
	int ho_OpCount=0;
	int delay_time=0;
	double ho_Fee_Change=0;
	int ret=0;
	FILE *fp;
	TIniFile tf;
	int nrows=0;
	char path_name[128]="";
	char file_name[128]="";
	BANK_TRANSFER_HEAD		trans_head;
	BANK_TRANSFER_RECORD	trans_record;
	T_v_tif_shopdeptfee	v_shopdeptfee;
	T_t_cif_shop		t_shop;

	//系统正在结算，可以生成划拨文件
	//sleep(1);
	//ret=DB_v_tif_shopdeptfee_read_sum_fee(&ho_OpCount,&ho_Fee_Change);
	if(ret)
	{
		writelog(LOG_ERR,"DB_v_tif_shopdeptfee_read_sum_fee err [%d]",ret);
		return ret;
	}
	ho_OpCount=4;
	ho_Fee_Change=12345.98;
	strcpy(path_name,"/ykt/ykt/src/bank/ftp");
	sprintf(file_name,"%s/fd_%8.8s",path_name,getsysdate(NULL));

	#ifdef DEBUG
	//	strcpy(path_name,"./ftp/fd_20041009");
		writelog(LOG_ALERT,"file_name2=[%s]",file_name);
	#endif

	fp = fopen(file_name,"wb");
	if (fp==NULL)
	{
		writelog(LOG_ALERT,"Open indicate file fail");
		return -1;
	}
	memcpy(trans_head.rmb_batch_no,BATCH_NO,sizeof(trans_head.rmb_batch_no));
	fprintf(fp,"%-14.14s",trans_head.rmb_batch_no);		//批量编号

	memcpy(trans_head.rmb_start_seq,"000000",6);
	fprintf(fp,"%-6.6s",trans_head.rmb_start_seq);			//填000000

	trans_head.rmb_acc_status='0';
	fprintf(fp,"%c",trans_head.rmb_acc_status);			//记帐状态（填0）

	trans_head.rmb_chk_status='2';
	fprintf(fp,"%c",trans_head.rmb_chk_status);			//检查状态（填2）

	sprintf(trans_head.rmb_total_amount,"%-13d",int(ho_Fee_Change*100));
	fprintf(fp,"%-13.13s",trans_head.rmb_total_amount);		//总金额(11位整数2位小数，无小数点)

	sprintf(trans_head.rmb_total_num,"%-6d",ho_OpCount);
	fprintf(fp,"%-6.6s",trans_head.rmb_total_num);			//总笔数

	fprintf(fp,"%-13.13s",trans_head.rmb_enter_amount);	//入帐金额

	fprintf(fp,"%-6.6s",trans_head.rmb_enter_num);			//入帐笔数

	sprintf(trans_head.rmb_unit_name,"%-40s",UNIT_NAME);
	fprintf(fp,"%-40.40s",trans_head.rmb_unit_name);		//单位名称
#ifdef DEBUG
	writelog(LOG_ALERT,"trans_head.rmb_unit_name=[%s]",trans_head.rmb_unit_name);
#endif

	strcpy(trans_head.rmb_unit_account,UNIT_ACCOUNT);
	//sprintf(trans_head.rmb_unit_account,"%-20s"UNIT_ACCOUNT);
	fprintf(fp,"%-20.20s",trans_head.rmb_unit_account);		//单位帐号
#ifdef DEBUG
	writelog(LOG_ALERT,"trans_head.rmb_unit_account=[%s]",trans_head.rmb_unit_account);
#endif

	memcpy(trans_head.rmb_apply_date,getsysdate(NULL),sizeof(trans_head.rmb_apply_date));
	fprintf(fp,"%-8.8s",trans_head.rmb_apply_date);			//申请入帐日期（当天日期）

	//memcpy(trans_head.rmb_send_date,trans_head.rmb_apply_date,sizeof(trans_head.rmb_apply_date));
	memcpy(trans_head.rmb_send_date,getsystime(NULL),sizeof(trans_head.rmb_send_date));
	fprintf(fp,"%-8.8s",trans_head.rmb_send_date);			//上传日期（当天日期）

#ifdef DEBUG
	printf("[%14.14s]\n",trans_head.rmb_batch_no      ); 	//批量编号
	printf("[%6.6s]\n",trans_head.rmb_start_seq      ); 		//填000000
	printf("[%c]\n",trans_head.rmb_acc_status        ); 		//记帐状态（填0）
	printf("[%c]\n",trans_head.rmb_chk_status        ); 		//检查状态（填2）
	printf("[%13.13s]\n",trans_head.rmb_total_amount  ); 	//总金额(11位整数2位小数，无小数点)
	printf("[%6.6s]\n",trans_head.rmb_total_num      ); 	//总笔数
	printf("[%13.13s]\n",trans_head.rmb_enter_amount ); 	//入帐金额(11位整数2位小数，无小数点)
	printf("[%6.6s]\n",trans_head.rmb_enter_num     ); 	//入帐笔数
	printf("[%40.40s]\n",trans_head.rmb_unit_name    ); 	//单位名称
	printf("[%20.20s]\n",trans_head.rmb_unit_account  ); 	//单位帐号
	printf("[%8.8s]\n",trans_head.rmb_apply_date     ); 	//申请入帐日期（当天日期）
	printf("[%8.8s]\n",trans_head.rmb_send_date     );  	//上传日期（当天日期）
#endif

	//写入划拨文件
	// fprintf(fp,(char*)(&trans_head));
	strcpy(temp,"1");
	ret=DB_v_tif_shopdeptfee_open_select_by_c6_and_is_indep(temp);
	if(ret)
	{
		//db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_v_tif_shopdeptfee_open_select_by_c6_and_is_indep[%d]",ret);
		return ret;
	}

	while(1)
	{
		//初始化宿主变量
		ho_Fee_Change=0;
		memset(&v_shopdeptfee,0,sizeof(v_shopdeptfee));
		memset(&t_shop,0,sizeof(t_shop));
		ret=DB_v_tif_shopdeptfee_fetch_select_by_c6(&v_shopdeptfee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				if(0==nrows)
				{
					writelog(LOG_ERR,"DB_v_tif_shopdeptfee_fetch_select_by_c6[%d]",ret);
					break;
				}
				else		break;	//循环记录结束
			}
			else
			{
				//db_chk_err(__FILE__,__LINE__,&sqlca);
				writelog(LOG_ERR,"DB_v_tif_shopdeptfee_fetch_select_by_c6[%d]",ret);
				return ret;
			}
		}
		ret=DB_t_cif_shop_read_by_shop_id(v_shopdeptfee.shop_id,&t_shop);
		if(ret)
		{
			//db_chk_err(__FILE__,__LINE__,&sqlca);
			writelog(LOG_ALERT,"DB_t_cif_shop_read_by_shop_id[%d]",ret);
			return ret;
		}
		strcpy(trans_record.rmb_batch_no1,BATCH_NO);
		sprintf(trans_record.rmb_seq_no,"%d",nrows);
		trans_record.rmb_acc_status1='0';
		trans_record.rmb_tran_kind='2';
		strncpy(trans_record.rmb_cust_name,t_shop.b_act_name,sizeof(trans_record.rmb_cust_name));
		strncpy(trans_record.rmb_acc_no,t_shop.b_act_id,sizeof(trans_record.rmb_acc_no));
		trans_record.rmb_cb_cr='0';
		sprintf(trans_record.rmb_tran_amt,"%f",ho_Fee_Change);
		strcpy(trans_record.rmb_cur_code,"001");
		strcpy(trans_record.rmb_host_no,"00000000");
		memcpy(trans_record.rmb_ret_code,"    ",sizeof(trans_record.rmb_ret_code));
		strcpy(trans_record.rmb_acc_date,"00000000");
		strcpy(trans_record.rmb_host_no1,"000000000");
		strcpy(trans_record.rmb_open_branch,"0000000");
		memcpy(trans_record.rmb_vcho_kind,"  ",sizeof(trans_record.rmb_vcho_kind));
		strcpy(trans_record.rmb_vcho_bat_no,"00");
		strcpy(trans_record.rmb_vcho_no,"000000000");
		strcpy(trans_record.rmb_memo,"  ");
		strcpy(trans_record.rmb_tran_info,"  ");

		fprintf(fp,(char*)(&trans_record));

		nrows++;
	}
	fclose(fp);
	memset(pBankTrans,0,BANK_TRANS_PACKLEN);
	//开始银行发送清算报文
	memcpy( pBankTrans->TradeCode,TRADE_BANK_BALANCE, sizeof(pBankTrans->TradeCode));	//写交易代码
	//写交易日期和交易时间
	getsysdate(pBankTrans->TradeDate);
	getsystime(pBankTrans->TradeTime);
	//写院校代码
	sprintf(pBankTrans->CustNo,"%-16s",SCHOOL_CODE);
	//写银行卡号-此处约定为划拨文件名
	sprintf(pBankTrans->BankCardNo,"%8.8s",getsysdate(NULL));
	//写校验mac码
	//写校验mac码----林钦此处应该用银行回传回来的动态密钥做mac密钥，此处改过来了
	generate_mac((char*)pBankTrans,sizeof(pBankTrans),pBankTrans->MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(pBankTrans,"send transfer package");

	//发送数据到银行并同时接收银行数据，此处不判断返回的mac校验
	ret=send_to_and_recv_from_bank((char*)pBankTrans,BANK_TRANS_PACKLEN, (char*)pBankTrans,BANK_TRANS_PACKLEN,delay_time);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}
	TRACE_BANK_TRANS(pBankTrans,"recv transfer package");

	//农行暂时未校验该mac,所以暂时屏蔽掉

	ret=check_mac((char*)pBankTrans,BANK_TRANS_PACKLEN);
	if(ret)
	{
		writelog(LOG_ERR,"Receive data mac verify error,error code is [%d] ",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_RECVERR);
		return	E_TRANS_BANK_RECVERR;
	}
	writelog(LOG_INFO,"Congratulation, transer succeed!");

	return 0;
}

//通用函数定义

int send_to_and_recv_from_bank(char* pSend, int send_len,char* pRecv,int recv_len,int delay_time)
{
	struct SockNode  SockNode;
	char bank_ip[20]="";
	int bank_port=0;
	//int delay_time=0;
	int ret=0;


	TIniFile tf;

	if (!tf.Open(TRANS_INI_FILE))
	{
	   writelog(LOG_ERR,"Cann't open ini file,file=[%s]\n",TRANS_INI_FILE);
	   return E_TRANS_UNKNOW_ERROR;
	}

	tf.ReadString("BANK", "BANK_IP", "127.0.0.1", bank_ip,sizeof(bank_ip));
	bank_port=tf.ReadInt("BANK", "BANK_PORT",3501);
	if(0==delay_time)	delay_time=tf.ReadInt("BANK", "BANK_DELAY_TIME", 3000);
	tf.Close();

#ifdef	DEBUG
	//printf("BANK_IP=[%s],BANK_PORT[%d],DELAY_TIME[%d]\n",bank_ip,bank_port,delay_time);
#endif
	//连接银行
	ret=SockNode.hSock.ConnectTcp(bank_ip, bank_port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],bank_ip[%s],port[%d] ",ret,bank_ip,bank_port);
		return E_TRANS_BANK_NETERR;
	}

	//发送数据到银行
	ret=SockNode.hSock.Send(pSend, send_len);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,ret = %ret, error code is [%d] ",ret, errno);
		return E_TRANS_BANK_NETERR;
	}
	else if (0==ret)
	{
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to bank error，CTcpSocket.Send should not return this error,error code is[%d]!\n",errno);
	      	return	E_TRANS_BANK_NETERR;
	}

	system("sleep 1");

	//接收银行返回信息
	ret=	SockNode.hSock.Recv(pRecv,recv_len,delay_time);
	if (ret!=recv_len)
	{
		writelog(LOG_ERR,"Receive from bank error,ret= %ret, error code is [%d] ",ret, errno);
		return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
	}
	SockNode.hSock.Close();

	return 0;
}

//判断该设备是否签到过
int device_login_yes_or_no(int device_id)
{
	int ret=0;
	T_t_pif_device t_device;

	memset(&t_device,0,sizeof(t_device));
	ret=DB_t_pif_device_read_by_device_id(device_id,&t_device);
	if(ret)
	{
		writelog( LOG_ERR,"DB_t_pif_device_read_by_device_id error,errcode=[%d],device_id=[%d]",ret,device_id);
		return ret;
	}
	//writelog( LOG_ERR,"Device don't login,device_id=[%d],login_flag=[%d]",device_id,t_device.state_id);
	if(DEVISTAT_ONLINE!=t_device.state_id)
	{
		writelog( LOG_ERR,"Device don't login,device_id=[%d],login_flag=[%d]",device_id,t_device.state_id);
		return 9999;
	}
	return 0;
}


