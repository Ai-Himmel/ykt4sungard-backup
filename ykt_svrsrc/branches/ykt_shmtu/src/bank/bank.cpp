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
int Bank_QueryBalance(INNER_TRANS_REQUEST * pNode,double *balance)
{
	return 0;
}

int Bank_Transfer(INNER_TRANS_REQUEST * pNode)
{
	return 0;
}
int Bank_Undo()
{
	return 0;
}
int Bank_CheckLine()
{
	return 0;
}

int Bank_SignIn()
{
	return 0;
}
int Bank_SignOut()
{
	return 0;
}

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
int Do_DeTrans  (T_t_tif_tradeserial *tradeserial,BANK_TRANS_REQUEST *pBankTrans )
{
	//TODO: 发送冲正记录.注意填空格
	writelog(LOG_INFO,"补发冲正", ret);
	//组织银行包
	//memset(pBankTrans, ' ', sizeof(bank_trans));
	//写交易代码
	strnscpy( pBankTrans->TradeCode,TRADE_BANK_DETRANS, BANK_TRADE_CODE_LEN);
	//写交易日期和交易时间
	strnscpy(pBankTrans->TradeDate,tradeserial.operate_date,sizeof(pBankTrans->TradeDate));
	strnscpy(pBankTrans->TradeTime,tradeserial.operate_time,sizeof(pBankTrans->TradeTime));
	//改成校园卡卡号
	sprintf(pBankTrans->CustAccountNo,"%-10d",tradeserial.card_id);
	//写银行卡号字段
	strnscpy(pBankTrans->BankCardNo,tradeserial.b_act_id, sizeof(pBankTrans->BankCardNo));
	//写商户号字段
	strnscpy(pBankTrans->MercAccount,SCHOOL_ACCOUNT_NO,sizeof(pBankTrans->MercAccount));
	//写转帐金额字段
	sprintf(pBankTrans->TransMoney,"%-9d", int(tradeserial.trade_fee));
	//写银行卡密码字段!!!oldpwd? or pwd in shm?
	strnscpy(pBankTrans->BankCardPwd, tradeserial.oldpwd,sizeof(pBankTrans->BankCardPwd));
	//写校园端流水号!!!serial_no or ReviseSerial_no? f?
	sprintf(pBankTrans->CustSn,"%-8d",tradeserial.other_seri_no);
	//sprintf(bank_trans.BankSn,
	//写院校代码
	sprintf(pBankTrans->CustNo,"%-16s",SCHOOL_CODE);
	//写校验mac码
	generate_mac((char*)pBankTrans,BANK_TRANS_PACKLEN,pBankTrans->MAC);

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
	ret=SockNode.hSock.ConnectTcp(bank_ip, bank_port,30);
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


