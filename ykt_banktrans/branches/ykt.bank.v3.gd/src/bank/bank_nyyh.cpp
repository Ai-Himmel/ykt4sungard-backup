/* ----------------------------------------------------------
 * 程序名称：bank_nyyh.cpp
 * 创建日期：2007-07-27 14:58
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：通用接口规范的封装
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include "bank.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank.h"
#include "bank_nyyh.h"
#include "mac.h"

ISO8583 Tbl8583[128] = 
{ 
/* FLD 1 */ {0,"BIT MAP,EXTENDED ", 8, 0, 0, 2, NULL,0}, 
/* FLD 2 */ {0,"RIMARY ACCOUNT NUMBER ", 22, 0, 2, 0, NULL,0}, 
/* FLD 3 */ {0,"ROCESSING CODE ", 6, 0, 0, 0, NULL,0}, 
/* FLD 4 */ {0,"AMOUNT, TRANSACTION ", 12, 0, 0, 1, NULL,0}, 
/* FLD 5 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 6 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 7 */ {0,"TRANSACTION DATE AND TIME ", 10, 0, 0, 0, NULL,0}, 
/* FLD 8 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 9 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 10 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 11 */ {0,"SYSTEM TRACE AUDIT NUMBER ", 6, 0, 0, 1, NULL,0}, 
/* FLD 12 */ {0,"TIME, LOCAL TRANSACTION ", 6, 0, 0, 0, NULL,0}, 
/* FLD 13 */ {0,"DATE, LOCAL TRANSACTION ", 4, 0, 0, 0, NULL,0}, 
/* FLD 14 */ {0,"DATE, EXPIRATION ", 4, 0, 0, 0, NULL,0}, 
/* FLD 15 */ {0,"DATE, SETTLEMENT ", 4, 0, 0, 0, NULL,0}, 
/* FLD 16 */ {0,"NO USE ", 4, 0, 0, 0, NULL,0}, 
/* FLD 17 */ {0,"DATE, CAPTURE ", 4, 0, 0, 0, NULL,0}, 
/* FLD 18 */ {0,"MERCHANT'S TYPE ", 4, 0, 0, 0, NULL,0}, 
/* FLD 19 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 20 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 21 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 22 */ {0,"OINT OF SERVICE ENTRY MODE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 23 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 24 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 25 */ {0,"OINT OF SERVICE CONDITION CODE ", 2, 0, 0, 0, NULL,0}, 
/* FLD 26 */ {0,"NO USE ", 2, 0, 0, 0, NULL,0}, 
/* FLD 27 */ {0,"NO USE ", 1, 0, 0, 0, NULL,0}, 
/* FLD 28 */ {0,"field27 ", 6, 0, 0, 0, NULL,0}, 
/* FLD 29 */ {0,"NO USE ", 8, 0, 1, 0, NULL,0}, 
/* FLD 30 */ {0,"NO USE ", 8, 0, 1, 0, NULL,0}, 
/* FLD 31 */ {0,"NO USE ", 8, 0, 1, 0, NULL,0}, 
/* FLD 32 */ {0,"ACQUIRER INSTITUTION ID. CODE ", 11, 0, 2, 0, NULL,0}, 
/* FLD 33 */ {0,"FORWARDING INSTITUTION ID. CODE ", 11, 0, 2, 0, NULL,0}, 
/* FLD 34 */ {0,"NO USE ", 28, 0, 2, 0, NULL,0}, 
/* FLD 35 */ {0,"TRACK 2 DATA ", 37, 0, 2, 0, NULL,0}, 
/* FLD 36 */ {0,"TRACK 3 DATA ",104, 0, 3, 0, NULL,0}, 
/* FLD 37 */ {0,"RETRIEVAL REFERENCE NUMBER ", 12, 0, 0, 0, NULL,0}, 
/* FLD 38 */ {0,"AUTH. IDENTIFICATION RESPONSE ", 6, 0, 0, 0, NULL,0}, 
/* FLD 39 */ {0,"RESPONSE CODE ", 2, 0, 0, 0, NULL,0}, 
/* FLD 40 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 41 */ {0,"CARD ACCEPTOR TERMINAL ID. ", 8, 0, 0, 0, NULL,0}, 
/* FLD 42 */ {0,"CARD ACCEPTOR IDENTIFICATION CODE ", 15, 0, 0, 0, NULL,0}, 
/* FLD 43 */ {0,"CARD ACCEPTOR NAME LOCATION ", 40, 0, 0, 0, NULL,0}, 
/* FLD 44 */ {0,"ADDITIONAL RESPONSE DATA ", 25, 0, 2, 0, NULL,0}, 
/* FLD 45 */ {0,"NO USE ", 76, 0, 2, 0, NULL,0}, 
/* FLD 46 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 47 */ {0,"field47 ",999, 0, 3, 0, NULL,0}, 
/* FLD 48 */ {0,"ADDITIONAL DATA --- PRIVATE ",999, 0, 3, 0, NULL,0}, 
/* FLD 49 */ {0,"CURRENCY CODE,TRANSACTION ", 3, 0, 0, 0, NULL,0}, 
/* FLD 50 */ {0,"CURRENCY CODE,SETTLEMENT ", 3, 0, 0, 0, NULL,0}, 
/* FLD 51 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 52 */ {0,"ERSONAL IDENTIFICATION NUMBER DATA ", 8, 0, 0, 2, NULL,0}, 
/* FLD 53 */ {0,"SECURITY RELATED CONTROL INformATION", 16, 0, 0, 0, NULL,0}, 
/* FLD 54 */ {0,"ADDITIONAL AMOUNTS ",120, 0, 3, 0, NULL,0}, 
/* FLD 55 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 56 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 57 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 58 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 59 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 60 */ {0,"NO USE ", 5, 0, 3, 0, NULL,0}, 
/* FLD 61 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 62 */ {0,"NO USE ", 11, 0, 3, 0, NULL,0}, 
/* FLD 63 */ {0,"NO USE ", 11, 0, 3, 0, NULL,0}, 
/* FLD 64 */ {0,"MESSAGE AUTHENTICATION CODE FIELD ", 8, 0, 0, 2, NULL,0}, 
/* FLD 65 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 66 */ {0,"NO USE ", 1, 0, 0, 0, NULL,0}, 
/* FLD 67 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 68 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 69 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 70 */ {0,"SYSTEM MANAGEMENT INformATION CODE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 71 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 72 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 73 */ {0,"NO USE ", 6, 0, 0, 0, NULL,0}, 
/* FLD 74 */ {0,"NUMBER OF CREDITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 75 */ {0,"REVERSAL NUMBER OF CREDITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 76 */ {0,"NUMBER OF DEBITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 77 */ {0,"REVERSAL NUMBER OF DEBITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 78 */ {0,"NUMBER OF TRANSFER ", 10, 0, 0, 0, NULL,0}, 
/* FLD 79 */ {0,"REVERSAL NUMBER OF TRANSFER ", 10, 0, 0, 0, NULL,0}, 
/* FLD 80 */ {0,"NUMBER OF INQUIRS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 81 */ {0,"AUTHORIZATION NUMBER ", 10, 0, 0, 0, NULL,0}, 
/* FLD 82 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 83 */ {0,"CREDITS,TRANSCATION FEEAMOUNT ", 12, 0, 0, 0, NULL,0}, 
/* FLD 84 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 85 */ {0,"DEBITS,TRANSCATION FEEAMOUNT ", 12, 0, 0, 0, NULL,0}, 
/* FLD 86 */ {0,"AMOUNT OF CREDITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 87 */ {0,"REVERSAL AMOUNT OF CREDITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 88 */ {0,"AMOUNT OF DEBITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 89 */ {0,"REVERSAL AMOUNT OF DEBITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 90 */ {0,"ORIGINAL DATA ELEMENTS ", 42, 0, 0, 0, NULL,0}, 
/* FLD 91 */ {0,"FILE UPDATE CODE ", 1, 0, 0, 0, NULL,0}, 
/* FLD 92 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 93 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 94 */ {0,"SERVICE INDICATOR ", 7, 0, 0, 0, NULL,0}, 
/* FLD 95 */ {0,"REPLACEMENT AMOUNTS ", 42, 0, 0, 0, NULL,0}, 
/* FLD 96 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 97 */ {0,"AMOUNT OF NET SETTLEMENT ", 16, 0, 0, 0, NULL,0}, 
/* FLD 98 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 99 */ {0,"SETTLEMENT INSTITUTION ID ", 11, 0, 2, 0, NULL,0}, 
/* FLD 100 */ {0,"RECVEING INSTITUTION ID ", 11, 0, 2, 0, NULL,0}, 
/* FLD 101 */ {0,"FILENAME ", 17, 0, 2, 0, NULL,0}, 
/* FLD 102 */ {0,"ACCOUNT IDENTIFICATION1 ", 28, 0, 2, 0, NULL,0}, 
/* FLD 103 */ {0,"ACCOUNT IDENTIFICATION2 ", 28, 0, 2, 0, NULL,0}, 
/* FLD 104 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 105 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 106 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 107 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 108 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 109 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 110 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 111 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 112 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 113 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 114 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 115 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 116 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 117 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 118 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 119 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 120 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 121 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 122 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 123 */ {0,"NEW PIN DATA ", 8, 0, 3, 2, NULL,0}, 
/* FLD 124 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 125 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 126 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 127 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 128 */ {0,"MESSAGE AUTHENTICATION CODE FIELD ", 8, 0, 0, 2, NULL,0}, 
}; 



void TRACE_BANK_TRANS(BANK_TRANS_REQUEST *pTransPak, char *stage);
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank);
void WriteBufferLog(char *pBuffer,int Buffer_len,int colum_num);
int debug=2;

//按照通用接口规范进行封装各自银行的接口
int Bank_QueryBalance(INNER_TRANS_REQUEST * pNode,double *balance)
{

	int ret=0;
	INNER_TRANS_REQUEST  from_pos;
	BANK_TRANS_REQUEST BankReqPak;
	BANK_TRANS_REQUEST BankAnsPak;

	memset(&from_pos,0,sizeof from_pos);
	memset(&BankReqPak,0,sizeof BankReqPak);
	memset(&BankAnsPak,0,sizeof BankAnsPak);
	memcpy(&from_pos,pNode,sizeof(from_pos));
	
	//组织银行包
	//写交易代码
	memcpy( BankReqPak.TradeCode,TRADE_BANK_QUERY, BANK_TRADE_CODE_LEN);
	//写交易日期和交易时间
	getsysdate(BankReqPak.TradeDate);
	getsystime(BankReqPak.TradeTime);
	//memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
	//memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	//写银行卡号字段
	//sprintf(BankReqPak.BankCardNo,"%-20s","1030399110000001042");	//写银行卡号字段
	sprintf(BankReqPak.BankCardNo,"%-20s",from_pos.BankCardNo);
	//写银行卡密码字段
	//通过16进制格式传输，再解密
	hex2dec(from_pos.BankCardPwd, (unsigned char*)BankReqPak.BankCardPwd, 8);
	//memcpy(BankReqPak.BankCardPwd,from_pos.BankCardPwd,sizeof(BankReqPak.BankCardPwd));
	#ifdef DEBUG
		char buffer[100]="";
		int k=0;
		for(int i=0;i<16;i++)
		{
			k=(unsigned char)BankReqPak.BankCardPwd[i];
			sprintf(&buffer[2*i],"%02X",k);
		}
		writelog(LOG_INFO,"BankCardNo=[%s],BankCardPwd=[%s]",BankReqPak.BankCardNo,buffer);
		writelog(LOG_INFO,"BankCardNo=[%s],fromCardPwd=[%s]",BankReqPak.BankCardNo,from_pos.BankCardPwd);
	#endif

	//写校园端流水号
	sprintf(BankReqPak.CustSn,"%-8f",0);
	//写院校代码
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);
	BankReqPak.AutoFlag='0';
	//写校验mac码
	generate_mac((char*)(&BankReqPak),sizeof(BankReqPak),BankReqPak.MAC);

	//memcpy(SockNode.Buf,&BankReqPak,sizeof(BankReqPak));
	TRACE_BANK_TRANS(&BankReqPak,"send query bank package");

	ret=send_to_and_recv_from_bank(BANK_NYYH,(char*)(&BankReqPak),sizeof(BankReqPak),(char*)(&BankAnsPak),sizeof(BankAnsPak),&g_Bank);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}


	TRACE_BANK_TRANS(&BankAnsPak,"receivce query bank package");

	//农行暂时未校验该mac,所以暂时屏蔽掉
	/*
	ret=check_mac((char*)(&BankAnsPak), sizeof(BankAnsPak));
	if(ret)
	{
		writelog(LOG_ERR,"Receive data mac verify error,error code is [%d] ",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_RECVERR);
		return	E_TRANS_BANK_RECVERR;
	}
	*/
	if(0!=strncmp(BankAnsPak.RetCode,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",BankAnsPak.RetCode);
		BankAnsPak.RetCode[2]=0;
		switch(atoi(BankAnsPak.RetCode))
		{
			case 1:		//银行卡挂失
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//银行卡状态错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//银行卡金额不足
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//银行未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//银行密码错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//通讯或密钥错
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//其他未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return	E_TRANS_UNKNOW_ERROR;
		}
	}

	//填充应答包
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	memcpy(pNode->Balance,BankAnsPak.Balance,sizeof(pNode->Balance));
	writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%s]",BankAnsPak.Balance);
	return 0;
}

int Bank_Transfer(INNER_TRANS_REQUEST * pNode,int serial_no)
{

	int ret=0;
	double unique=0;
	int temp_serial_no=0;
	char logicdate[11]="";
	char buffer[16]="";
	int i=0;

	char sMoney[32]="";
	char sSerialno[32]="";

	INNER_TRANS_REQUEST  from_pos;
	BANK_TRANS_REQUEST BankReqPak;
	BANK_TRANS_REQUEST BankAnsPak;

	memset(&from_pos,0,sizeof from_pos);
	memset(&BankReqPak,0,sizeof BankReqPak);
	memset(&BankAnsPak,0,sizeof BankAnsPak);
	
	memcpy(&from_pos,pNode,sizeof from_pos);
	//组织银行包
	memcpy(BankReqPak.TradeCode,TRADE_BANK_TRANS, BANK_TRADE_CODE_LEN);	//写交易代码
	writelog(LOG_DEBUG,"trans code [%s]",TRADE_BANK_TRANS);
	getsysdate(BankReqPak.TradeDate);
	getsystime(BankReqPak.TradeTime);
	//由于银行给的接口中的校园卡账号字段只有10个长度
	//所以这里在校园卡账号字段上填写校园卡卡号
	sprintf(BankReqPak.CustAccountNo,"%-10d",atoi(from_pos.CardNo));
	//sprintf(BankReqPak.BankCardNo,"%-20s","1030399110000001042");	//写银行卡号字段
	sprintf(BankReqPak.BankCardNo,"%-20s",from_pos.BankCardNo);	//写银行卡号字段
	memcpy(BankReqPak.MercAccount,SCHOOL_ACCOUNT_NO,sizeof(BankReqPak.MercAccount));	//写商户号字段
	sprintf(BankReqPak.TransMoney,"%-9s",from_pos.TransMoney);	//写转帐金额字段
	//通过16进制传输，然后解密
	hex2dec(from_pos.BankCardPwd,(unsigned char*)BankReqPak.BankCardPwd, 8);
	//memcpy(BankReqPak.BankCardPwd,from_pos.BankCardPwd,sizeof(BankReqPak.BankCardPwd));	//写银行卡密码字段
	sprintf(sSerialno,"%d",serial_no);
	memcpy(BankReqPak.CustSn,sSerialno,strlen(sSerialno));	//写校园端流水号
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);	//写院校代码
	BankReqPak.AutoFlag='0';	//写自动自助标志
	generate_mac((char*)(&BankReqPak),sizeof(BankReqPak),BankReqPak.MAC);//写校验mac码

	TRACE_BANK_TRANS(&BankReqPak,"send transfer package");

	//发送数据到银行并同时接收银行数据，此处不判断返回的mac校验
	ret=send_to_and_recv_from_bank(BANK_NYYH,(char*)(&BankReqPak),sizeof(BankReqPak),(char*)(&BankAnsPak),sizeof(BankAnsPak),&g_Bank);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return ret;
	}

	TRACE_BANK_TRANS(&BankAnsPak,"receive transfer package");

	//校验mac，判断银行接收包是否正确
	//目前银行端没有校验mac，所以屏蔽
	/*
	ret=check_mac((char*)(&BankAnsPak), sizeof(BankAnsPak));
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return	E_TRANS_BANK_RECVERR;
	}
	*/
	if(0!=strncmp(BankAnsPak.RetCode,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%s] ",BankAnsPak.RetCode);
		BankAnsPak.RetCode[2]=0;
		switch(atoi(BankAnsPak.RetCode))
		{
			case 1:		//银行卡挂失
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//银行卡状态错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//银行卡金额不足
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//银行未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//银行密码错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//通讯或密钥错
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//其他未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return	E_TRANS_UNKNOW_ERROR;
		}
	}
	return 0;
}

int Bank_Undo(INNER_TRANS_REQUEST * pNode)
{

	int ret=0;
	BANK_TRANS_REQUEST BankReqPak;
	BANK_TRANS_REQUEST BankAnsPak;
	char sMoney[32]="";
	char sSerialno[32]="";
	memset(&BankReqPak, ' ', sizeof(BankReqPak));
	memset(&BankAnsPak, ' ', sizeof(BankAnsPak));
	
	//写交易代码
	memcpy( BankReqPak.TradeCode,TRADE_BANK_DETRANS, BANK_TRADE_CODE_LEN);
	//写交易日期和交易时间
	memcpy(BankReqPak.TradeDate,pNode->TradeDate,sizeof(BankReqPak.TradeDate));
	memcpy(BankReqPak.TradeTime,pNode->TradeTime,sizeof(BankReqPak.TradeTime));
	//改成校园卡卡号
	sprintf(BankReqPak.CustAccountNo,"%-10d",atoi(pNode->CardNo));
	//写银行卡号字段
	memcpy(BankReqPak.BankCardNo,pNode->BankCardNo, sizeof(BankReqPak.BankCardNo));
	//写商户号字段
	memcpy(BankReqPak.MercAccount,SCHOOL_ACCOUNT_NO,sizeof(BankReqPak.MercAccount));
	//写转帐金额字段
	sprintf(BankReqPak.TransMoney,"%09d",atoi(pNode->TransMoney));	//写转帐金额字段
	//memcpy(BankReqPak.TransMoney,pNode->TransMoney,sizeof BankReqPak.TransMoney);
	//写银行卡密码字段!!!oldpwd? or pwd in shm?
	//memcpy(BankReqPak.BankCardPwd, tradeserial.oldpwd,sizeof(BankReqPak.BankCardPwd));
	//写校园端流水号!!!serial_no or ReviseSerial_no? f?
	sprintf(sSerialno,"%d",pNode->RecvNo);
	memcpy(BankReqPak.CustSn,sSerialno,strlen(sSerialno));			//本地流水号
	//写院校代码
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);
	//写校验mac码
	generate_mac((char*)(&BankReqPak),sizeof(BankReqPak),BankReqPak.MAC);

	TRACE_BANK_TRANS(&BankReqPak,"send detrans package");

	ret = send_to_and_recv_from_bank(BANK_NYYH,(char*)&BankReqPak, BANK_TRANS_PACKLEN, (char*)&BankAnsPak, BANK_TRANS_PACKLEN,&g_Bank);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return ret;
	}
	TRACE_BANK_TRANS(&BankAnsPak,"recv detrans package");
	if(0!=strncmp(BankAnsPak.RetCode,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%s] ",BankAnsPak.RetCode);
		BankAnsPak.RetCode[2]=0;
		switch(atoi(BankAnsPak.RetCode))
		{
			case 1:		//银行卡挂失
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//银行卡状态错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//银行卡金额不足
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//银行未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//银行密码错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//通讯或密钥错
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//其他未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return	E_TRANS_UNKNOW_ERROR;
		}
	}
	pNode->SendNo=atoi(BankAnsPak.CustSn);
	pNode->RecvNo=atoi(BankAnsPak.BankSn);

	//memcpy((char*)pBankTrans, (char*)&BankTransPak, BANK_TRANS_PACKLEN);
	
	return 0;
}
int Bank_CheckLine()
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
	//memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	return 0;
}

int Bank_SignIn(INNER_TRANS_REQUEST *pNode)
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
	memcpy(pNode->BankCardPwd, BankTransPak.BankCardPwd, sizeof(pNode->BankCardPwd));
	writelog(LOG_INFO,"Congratulation,login to bank succeed!");
	return 0;
}
int Bank_SignOut()
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
	//memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	writelog(LOG_INFO,"Congratulation,logout from bank succeed!");
	return 0;
}

int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank)
{
	char bank_ip[20]="";
	int bank_port=0;
	int ret=0;
	int delay_time=5000;
	struct SockNode  SockNode;
	des2src(bank_ip,pBank->BankUnit[pBank->cur_bankid].szBankIP);
	bank_port=pBank->BankUnit[pBank->cur_bankid].iBankPort;
	delay_time=pBank->BankUnit[pBank->cur_bankid].iBankTimeout;
	//启用signal，防止阻塞模式的socket

	alarm(delay_time/1000);
	//连接银行
	ret=SockNode.hSock.ConnectTcp(bank_ip,bank_port);
	if(!ret)
	{	
		alarm(0);
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],bank_ip[%s],port[%d] ",ret,bank_ip,bank_port);
		return E_TRANS_BANK_NETERR;
	}
	alarm(0);

	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pSend,send_len,16);
	
	//发送数据到银行
	ret=SockNode.hSock.Send(pSend, send_len);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,ret = [%d] ",ret);
		return E_TRANS_BANK_NETERR;
	}
	else if (0==ret)
	{
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to bank error,CTcpSocket.Send should not return this error,error code is[%d]!\n",errno);
	      	return	E_TRANS_BANK_NETERR;
	}

	system("sleep 1");

	//接收银行返回信息
	ret=	SockNode.hSock.Recv(pRecv,recv_len,delay_time);
	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pRecv,recv_len,16);
	if (ret!=recv_len)
	{
		writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
		return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
	}
	SockNode.hSock.Close();
	return 0;
}

int Bank_GetRecvPacket(INNER_TRANS_REQUEST * pNode, ST_BANK *bank, void *recv_packet)
{
	return 0;
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

}
void WriteBufferLog(char *pBuffer,int Buffer_len,int colum_num)
{
	int i=0;
	int j=0;
	char buffer[10240]="";
	char hex_buffer[1024]="";
	char char_buffer[1024]="";
	char tmp_char[2+1]="";
	for(i=0;i<Buffer_len;i++)
	{
		sprintf(tmp_char,"%02X ",(unsigned char)pBuffer[i]);
		strcat(hex_buffer,tmp_char);
		if ((unsigned char)pBuffer[i]<32||(unsigned char)pBuffer[i]>128)
		{
			strcat(char_buffer,".");
		}
		else
		{
			sprintf(tmp_char,"%c",(unsigned char)pBuffer[i]);
			strcat(char_buffer,tmp_char);
		}
		if((i%colum_num+1==colum_num&&i>0))
		{ 
			strcat(buffer,hex_buffer);
			strcat(buffer," ; ");
			strcat(buffer,char_buffer);
			strcat(buffer,"\r\n");
			hex_buffer[0]=0;
			char_buffer[0]=0;
		}
	}
	memset(&hex_buffer[(i%colum_num)*3],' ',colum_num*3-(i%colum_num)*3);
	hex_buffer[colum_num*3]=0;
	strcat(buffer,hex_buffer);
	strcat(buffer," ; ");
	strcat(buffer,char_buffer);
	strcat(buffer,"\r\n");
	
	//writelog(LOG_DEBUG,"%s",buffer);
	printf(buffer);
}

int Bank_AdjustCompareFile(INNER_TRANS_REQUEST *pNode, ST_BANK *bank, void *var_object1, void *var_object2, void *var_object3)
{
	return 0;
}
