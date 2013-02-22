/* ----------------------------------------------------------
 * 程序名称：bank_gd.cpp
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
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank.h"
#include "bank_gd.h"
#include "mac.h"
#include "typdef.h"
#include "iso8583.h"


//void TRACE_BANK_TRANS(BANK_TRANS_REQUEST *pTransPak, char *stage);
void Trace_Bank_Package_GSYH(BANK_GSYH_TRADE_STRUCT *pTransPak, char *stage);
void Trace_Bank_Package_ZGYH_R(BANK_ZGYH_TRADE_STRUCT_TRANS_REQ *pTransPak, char *stage);
void Trace_Bank_Package_ZGYH_A(BANK_ZGYH_TRADE_STRUCT_TRANS_ANS *pTransPak, char *stage);
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank);
void WriteBufferLog(char *pBuffer,int Buffer_len,int colum_num);
int debug=2;

//按照通用接口规范进行封装各自银行的接口
int Bank_QueryBalance(INNER_TRANS_REQUEST * pNode,double *balance)
{

	int ret=0;
	char temp[6]="";
	int i=0;
	int flag=0;

	BANK_ZGYH_TRADE_STRUCT_TRANS_REQ 	zgyh_req;
	BANK_ZGYH_TRADE_STRUCT_TRANS_ANS 	zgyh_ans;

	BANK_GSYH_TRADE_STRUCT 			gsyh_req;
	BANK_GSYH_TRADE_STRUCT 			gsyh_ans;

	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&gsyh_ans,0x20,sizeof gsyh_ans);
	memset(&gsyh_req,0x20,sizeof gsyh_req);

	
	//分析上传银行卡号属于哪个银行，根据银行标志，发送给不同的银行
	for(i=0;i<=g_Bank.BankCount;i++)
	{
		if(i==g_Bank.BankCount)	return E_TRANS_BANK_CARD_NONSUPPORT;
		for(int j=0;j<MAX_RANGE;j++)
		{
			printf("i=[%d],j=[%d],bankcard=[%s],range=[%s],len=[%d]]\n",i,j,pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j],strlen(g_Bank.BankUnit[i].szBankCardRange[j]));
			if(0==strlen(g_Bank.BankUnit[i].szBankCardRange[j]))	break;
			if(0==memcmp(pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j]
				,strlen(g_Bank.BankUnit[i].szBankCardRange[j])))
			{
				flag=1;
				g_Bank.cur_bankid=i;
				break;
			}
		}
		if(flag==1)	
			break;
	}
	printf("Bank_Transfer start!i=[%d],g_Bank.BankUnit[i].iBankID=[%d]\n",i,g_Bank.BankUnit[i].iBankID);
	//中国银行，中国银行目前不支持查询银行余额的接口
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		return E_TRANS_BANK_FUNC_NONSUPPORT;
	}
	//工商银行，按照工商银行接口进行发送数据包并解析返回包
	else if(g_Bank.BankUnit[i].iBankID==BANK_GSYH)
	{
		memset(&gsyh_req.ZoneNo,0x20,sizeof(gsyh_req));
		memcpy(gsyh_req.ZoneNo,BANK_GSYH_ZONE_NO_GZ,4); //地区编号;广州:3602,珠海:2002;
		memcpy(gsyh_req.BusiType,BANK_GSYH_TYPE_SCHOOL,2);//交易类型，固定11
		memcpy(gsyh_req.TranCode,BANK_GSYH_TRADE_CODE_QUERYBALANCE,2);////交易类型;1:转帐,2:取消,3:余额查询
		gsyh_req.TranFlag[0]='0';						//交易标志;0:正交易,1:反交易
		memcpy(gsyh_req.BankCardNo,pNode->BankCardNo,strlen(pNode->BankCardNo));//银行卡号;借方帐号，清算时为学校帐号
		//memcpy(gsyh_req.TranMoney,pNode->TransMoney,strlen(pNode->TransMoney));//交易金额;
		memcpy(gsyh_req.MoneyType,"001",3);//货币种类;001:人民币
		memcpy(gsyh_req.TranDate,pNode->TradeDate,8); //交易日期;YYYYMMDD
		memcpy(gsyh_req.TranTime,pNode->TradeTime,6);//交易时间;HHMMSS
		gsyh_req.PwdFlag[0]='0';
		gsyh_req.PwdType[0]='0';
		memcpy(gsyh_req.LocalSn,"999999",6);
		memcpy(gsyh_req.LocalDetranSn,"000000",6);		//冲正时填入的原转帐交易流水号
		memcpy(gsyh_req.BankSn,"000000",6);			//银行流水号
		memcpy(gsyh_req.MercAccount,BANK_GSYH_MERCH_NO,5);	//圈存时为中山大学商户号,清算时为商户的商户号
		memcpy(gsyh_req.MercAccountCode,"01",2);		//户代号，指商户当有多个银行帐号时，该字段指示是哪一个帐号；先固定为01;
		memcpy(gsyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));	//校园卡号;
		memcpy(gsyh_req.PosNo,pNode->TerminalId,5);				//圈存机号;
		memcpy(gsyh_req.AgentPercent,"000000000",9);		//清算时的代理提成百分比
		memcpy(gsyh_req.AgentType,"01",2);			//业务种类,01:圈存,02:消费;
		//memset(gsyh_req.Filter,0x20,sizeof(gsyh_req.Filter));				//空格补位
		Trace_Bank_Package_GSYH(&gsyh_req,"send query bank package");
		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"receivce query bank package");
		if(0!=strncmp(gsyh_ans.RetCode,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",gsyh_ans.RetCode);
			memcpy(temp,gsyh_ans.RetCode,2);
			temp[2]=0;
			switch(atoi(temp))
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
				case 4:		//银行密码错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//银行处理超时
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//其他错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//填充应答包
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	//建设银行不支持查询银行卡交易
	else if(g_Bank.BankUnit[i].iBankID==BANK_JSYH)
	{
		return E_TRANS_BANK_FUNC_NONSUPPORT;
	}
	else
	{
		return E_TRANS_BANK_CARD_NONSUPPORT;
	}
	
	return 0;
}

int Bank_Transfer(INNER_TRANS_REQUEST * pNode,int serial_no)
{
	int ret=0;
	char temp[6]="";
	int flag=0;
	int i=0;
	int len=0;
	char sMoney[32]="";
	char sSerialno[32]="";

	BANK_ZGYH_TRADE_STRUCT_TRANS_REQ 	zgyh_req;
	BANK_ZGYH_TRADE_STRUCT_TRANS_ANS 	zgyh_ans;

	BANK_GSYH_TRADE_STRUCT 			gsyh_req;
	BANK_GSYH_TRADE_STRUCT 			gsyh_ans;

	MSG8583 jsyh_req,jsyh_ans;
	H_MSG8583 head_jsyh_req,head_jsyh_ans;

	ISO_MSG iso_jsyh_req,iso_jsyh_ans;
	iso8583_init(&iso_jsyh_req);
	iso8583_init(&iso_jsyh_ans);
	char jsyh_sbuf[2048]="";
	char jsyh_abuf[2048]="";
	

	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&gsyh_ans,0x20,sizeof gsyh_ans);
	memset(&gsyh_req,0x20,sizeof gsyh_req);

	memset(&jsyh_req,0x20,sizeof jsyh_req);
	memset(&jsyh_ans,0x20,sizeof jsyh_ans);
	memset(&head_jsyh_req,0x20,sizeof jsyh_req);
	memset(&head_jsyh_ans,0x20,sizeof jsyh_ans);
	

	//分析上传银行卡号属于哪个银行，根据银行标志，发送给不同的银行
	//转到transinfo外层去处理
	for(i=0;i<=g_Bank.BankCount;i++)
	{
		if(i==g_Bank.BankCount)	
		{
				writelog(LOG_ERR,"E_TRANS_BANK_CARD_NONSUPPORT,i=[%d]!g_Bank.BankCount=[%d]",i,g_Bank.BankCount);
				return E_TRANS_BANK_CARD_NONSUPPORT;
		}
		for(int j=0;j<MAX_RANGE;j++)
		{
			//printf("i=[%d],j=[%d],bankcard=[%s],range=[%s],len=[%d]]\n",i,j,pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j],strlen(g_Bank.BankUnit[i].szBankCardRange[j]));
			if(0==strlen(g_Bank.BankUnit[i].szBankCardRange[j]))	break;
			if(0==memcmp(pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j]
				,strlen(g_Bank.BankUnit[i].szBankCardRange[j])))
			{
				flag=1;
				g_Bank.cur_bankid=i;
				break;
			}
		}
		if(flag==1)	
			break;
	}
	printf("Bank_Transfer start!i=[%d],g_Bank.BankUnit[i].iBankID=[%d]\n",i,g_Bank.BankUnit[i].iBankID);
	
	//中国银行
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		//memset(&zgyh_req,0x20,sizeof(zgyh_req));
		//memset(zgyh_req.head.Ret,0x20,sizeof(zgyh_req.head.Ret));					//返回码; 非0000为不成功
		memcpy(zgyh_req.head.TranCode,BANK_ZGYH_TRADE_CODE_TRANS,4);			//交易码; DXRB:转账,DXRV:冲正
		//memset(zgyh_req.head.BrnId,0x20,sizeof(zgyh_req.head.BrnId));				//网点号; 空格
		//memset(zgyh_req.head.TmlId,0x20,sizeof(zgyh_req.head.TmlId));				//终端号; 空格
		//memset(zgyh_req.head.TelId,0x20,sizeof(zgyh_req.head.TelId));				//柜员号; 空格
		//memset(zgyh_req.head.Filer1,0x20,sizeof(zgyh_req.head.Filer1));				//预留项;
		zgyh_req.head.Mchno_len=0x08;				//固定值; 0x08
		memcpy(zgyh_req.head.Merch_no,BANK_ZGYH_MERCH_NO,8);			//单位编码;  必填
		//memset(zgyh_req.head.Mch_name,0x20,sizeof(zgyh_req.head.Mch_name));			//单位名称;空格
		//memset(zgyh_req.head.Errcd,0x20,sizeof(zgyh_req.head.Errcd));				//错误代码;
		//memset(zgyh_req.head.ErrMsg,0x20,sizeof(zgyh_req.head.ErrMsg));				//错误信息;
		sprintf(sSerialno,"%d",serial_no);
		memcpy(zgyh_req.head.LocalNo,sSerialno,strlen(sSerialno));			//本地流水号
		//memcpy(zgyh_req.head.LocalNo,sSerialno,strlen(sSerialno));					//本地流水号;
		//memset(zgyh_req.head.BankNo,0x20,sizeof(zgyh_req.head.BankNo));//银行流水号;
		//memset(zgyh_req.head.Filer2,0x20,sizeof(zgyh_req.head.Filer2));				//预留;

		memcpy(zgyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));			//校园卡帐号
		memcpy(zgyh_req.BankCard,pNode->BankCardNo,strlen(pNode->BankCardNo));	//银行卡号
		zgyh_req.CardType='D';				//卡类型；C信用卡,D借记卡

//		memcpy(zgyh_req.TranMoney,pNode->TransMoney,9);		//交易金额
//wenjian add
		sprintf(sMoney,"%013d",atoi(pNode->TransMoney));
		memcpy(zgyh_req.TranMoney,sMoney,sizeof(zgyh_req.TranMoney));	//交易金额
		//memset(zgyh_req.PinBlock,0x20,sizeof(zgyh_req.PinBlock));			//预留
		//memset(zgyh_req.TpkUdlmk,0x20,sizeof(zgyh_req.TpkUdlmk));			//预留
		Trace_Bank_Package_ZGYH_R(&zgyh_req,"Send query bank package:中国银行");
		ret=send_to_and_recv_from_bank(BANK_ZGYH,(char*)&zgyh_req,sizeof(zgyh_req),(char*)&zgyh_ans,sizeof(zgyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_ZGYH_A(&zgyh_ans,"Receivce query bank package:中国银行");
		if(0!=strncmp(zgyh_ans.head.Ret,"0000",4))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s],msg=[%s] ",
						zgyh_ans.head.Ret,zgyh_ans.head.ErrMsg);
			memcpy(temp,zgyh_ans.head.Ret,4);
			temp[4]=0;
			switch(atoi(temp))
			{
				case 1:		//银行卡挂失
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANK_RECVERR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_BANK_RECVERR;
			}
		}
	}
	//工商银行
	else if(g_Bank.BankUnit[i].iBankID==BANK_GSYH)
	{
//		memset(&gsyh_req,0x20,sizeof(gsyh_req));
		memcpy(gsyh_req.ZoneNo,BANK_GSYH_ZONE_NO_GZ,4); //地区编号;广州:3602,珠海:2002;
		memcpy(gsyh_req.BusiType,BANK_GSYH_TYPE_SCHOOL,2);//交易类型，固定11
		memcpy(gsyh_req.TranCode,BANK_GSYH_TRADE_CODE_TRANS,2);////交易类型;1:转帐,2:取消,3:余额查询
		gsyh_req.TranFlag[0]='0';						//交易标志;0:正交易,1:反交易
		memcpy(gsyh_req.BankCardNo,pNode->BankCardNo,strlen(pNode->BankCardNo));//银行卡号;借方帐号，清算时为学校帐号			
		//memcpy(gsyh_req.TranMoney,pNode->TransMoney,9);//交易金额;
		sprintf(sMoney,"%010d",atoi(pNode->TransMoney));
		memcpy(gsyh_req.TranMoney,sMoney,sizeof(gsyh_req.TranMoney));	//交易金额
		memcpy(gsyh_req.MoneyType,"001",3);//货币种类;001:人民币
		memcpy(gsyh_req.TranDate,pNode->TradeDate,8); //交易日期;YYYYMMDD
		memcpy(gsyh_req.TranTime,pNode->TradeTime,6);//交易时间;HHMMSS
		gsyh_req.PwdFlag[0]='0';
		gsyh_req.PwdType[0]='0';							
		sprintf(sSerialno,"%d",serial_no);
		memcpy(gsyh_req.LocalSn,sSerialno,strlen(sSerialno));			//本地流水号
		//memcpy(gsyh_req.LocalDetranSn,"000000",6);		//冲正时填入的原转帐交易流水号
		//memcpy(gsyh_req.BankSn,"000000",6);			//银行流水号
		memcpy(gsyh_req.MercAccount,BANK_GSYH_MERCH_NO,5);	//圈存时为中山大学商户号,清算时为商户的商户号
		memcpy(gsyh_req.MercAccountCode,"01",2);		//户代号，指商户当有多个银行帐号时，该字段指示是哪一个帐号；先固定为01;
		memcpy(gsyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));	//校园卡号;
		memcpy(gsyh_req.PosNo,pNode->TerminalId,strlen(pNode->TerminalId));	//圈存机号;
		memcpy(gsyh_req.AgentPercent,"000000000",9);		//清算时的代理提成百分比
		memcpy(gsyh_req.AgentType,"01",2);			//业务种类,01:圈存,02:消费;
		memset(gsyh_req.Filter,0x20,sizeof(gsyh_req.Filter));				//空格补位
		Trace_Bank_Package_GSYH(&gsyh_req,"Send query bank package:工商银行");
		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"Receivce query bank package:工商银行");
		if(0!=strncmp(gsyh_ans.RetCode,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",gsyh_ans.RetCode);
			memcpy(temp,gsyh_ans.RetCode,2);
			temp[2]=0;
			switch(atoi(temp))
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
				case 4:		//银行密码错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//银行处理超时
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//其他错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//填充应答包
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		//memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		//writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	//建设银行
	else if(g_Bank.BankUnit[i].iBankID==BANK_JSYH)
	{
		char buf[2048]="";
		char bitmap[16]={0x70,0x18,0x00,0x01,0x08,0x80,0x00,0x00};
		ret=iso8583_set(&iso_jsyh_req, 0, (unsigned char*)BANK_JSYH_TRADE_CODE_TRANS_REQ, 4);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.msgType,BANK_JSYH_TRADE_CODE_TRANS_REQ,4);
		ret=iso8583_set(&iso_jsyh_req, 1, (unsigned char*)bitmap,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.priActNum,pNode->BankCardNo,strlen(pNode->BankCardNo));
		ret=iso8583_set(&iso_jsyh_req, 2, (unsigned char*)pNode->BankCardNo,strlen(pNode->BankCardNo));
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.procCode,"000000",6);
		ret=iso8583_set(&iso_jsyh_req, 3, (unsigned char*)"000000", 6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.txnAmunt,pNode->TransMoney,strlen(pNode->TransMoney));
		sprintf(buf,"%012s",pNode->TransMoney);
		ret=iso8583_set(&iso_jsyh_req, 4,(unsigned char*)buf , 12);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.txnDatTim,"0000000000",10);
		//memset(jsyh_req.tracAudNum,'0',sizeof jsyh_req.tracAudNum);
		//memcpy(jsyh_req.txnLocDat,pNode->TradeDate,8);
		ret=iso8583_set(&iso_jsyh_req,13,(unsigned char*)pNode->TradeDate,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

		//memcpy(jsyh_req.txnLocTim,pNode->TradeTime,6);
		ret=iso8583_set(&iso_jsyh_req,12,(unsigned char*)pNode->TradeTime,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.bala_date,"0000",4);
		//memcpy(jsyh_req.trade_fee,"00000000",9);
		//memcpy(jsyh_req.acqInstID,BANK_JSYH_MERCH_NO,6);
		ret=iso8583_set(&iso_jsyh_req,32,(unsigned char*)BANK_JSYH_MERCH_NO,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		sprintf(sSerialno,"%020d",serial_no);
		//memcpy(jsyh_req.field37,sSerialno,strlen(sSerialno));
		ret=iso8583_set(&iso_jsyh_req,37,(unsigned char*)sSerialno,20);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.termID,pNode->TerminalId,strlen(pNode->TerminalId));
		memset(buf,0,sizeof buf);
		sprintf(buf,"%8s",pNode->TerminalId);
		ret=iso8583_set(&iso_jsyh_req,41,(unsigned char*)buf,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memset(jsyh_req.field48,'0',20);
		//memcpy(jsyh_req.pinDat,"00000000",8);
		//memcpy(jsyh_req.bankCode,BANK_JSYH_MERCH_NO,6);
		//memcpy(jsyh_req.englishNam,"T",2);
		//memcpy(jsyh_req.mac,"000000",6);
		
		//ret=Pack8583((unsigned char*)head_jsyh_req.msg, jsyh_req, 2);
		ret=iso8583_pack(&iso_jsyh_req, jsyh_sbuf);
		if(ret<=0)
		{
			writelog(LOG_ERR,"Pack8583 error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=send_to_and_recv_from_bank(BANK_JSYH,(char *)jsyh_sbuf,ret,(char*)jsyh_abuf,200,&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		//ret=UnPack8583((unsigned char*)head_jsyh_ans.msg,&jsyh_ans,2);
		ret=iso8583_unpack(&iso_jsyh_ans, jsyh_abuf);
		if(ret<0)
		{
			writelog(LOG_ERR,"UnPack8583 error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		if(0!=strncmp((char *)iso_jsyh_ans.fld[39].buf,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",iso_jsyh_ans.fld[39].buf);
			memcpy(temp,iso_jsyh_ans.fld[39].buf,2);
			temp[2]=0;
			switch(atoi(temp))
			{
				case 41:		//银行卡挂失
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 36:		//银行卡状态错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 51:		//银行卡金额不足
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 75:		//银行密码错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 96:		//银行处理超时
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 22:		//其他错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

	}
	else
	{
		return E_TRANS_BANK_CARD_NONSUPPORT;
	}
	return 0;

}

int Bank_Undo(INNER_TRANS_REQUEST * pNode)
{

	int ret=0;
	char temp[6]="";
	int flag=0;
	int i=0;

	char sMoney[32]="";
	char sSerialno[32]="";

	BANK_ZGYH_TRADE_STRUCT_DETRANS_REQ 	zgyh_req;
	BANK_ZGYH_TRADE_STRUCT_DETRANS_ANS 	zgyh_ans;

	BANK_GSYH_TRADE_STRUCT 			gsyh_req;
	BANK_GSYH_TRADE_STRUCT 			gsyh_ans;

	MSG8583 jsyh_req,jsyh_ans;
	H_MSG8583 head_jsyh_req,head_jsyh_ans;

	ISO_MSG iso_jsyh_req,iso_jsyh_ans;
	iso8583_init(&iso_jsyh_req);
	iso8583_init(&iso_jsyh_ans);
	char jsyh_sbuf[2048]="";
	char jsyh_abuf[2048]="";


	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&gsyh_ans,0x20,sizeof gsyh_ans);
	memset(&gsyh_req,0x20,sizeof gsyh_req);

	memset(&jsyh_req,0x20,sizeof jsyh_req);
	memset(&jsyh_ans,0x20,sizeof jsyh_ans);
	
	//分析上传银行卡号属于哪个银行，根据银行标志，发送给不同的银行
	for(i=0;i<=g_Bank.BankCount;i++)
	{
		if(i==g_Bank.BankCount)	
		{
				writelog(LOG_ERR,"E_TRANS_BANK_CARD_NONSUPPORT,i=[%d]!g_Bank.BankCount=[%d]",i,g_Bank.BankCount);
				return E_TRANS_BANK_CARD_NONSUPPORT;
		}
		for(int j=0;j<MAX_RANGE;j++)
		{
			//printf("i=[%d],j=[%d],bankcard=[%s],range=[%s],len=[%d]]\n",i,j,pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j],strlen(g_Bank.BankUnit[i].szBankCardRange[j]));
			if(0==strlen(g_Bank.BankUnit[i].szBankCardRange[j]))	break;
			if(0==memcmp(pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j]
				,strlen(g_Bank.BankUnit[i].szBankCardRange[j])))
			{
				flag=1;
				g_Bank.cur_bankid=i;
				break;
			}
		}
		if(flag==1)	
			break;
	}
	//中国银行
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		memset(zgyh_req.head.Ret,0x20,sizeof(zgyh_req.head.Ret));					//返回码; 非0000为不成功
		memcpy(zgyh_req.head.TranCode,BANK_ZGYH_TRADE_CODE_DETRANS,4);			//交易码; DXRB:转账,DXRV:冲正
		memset(zgyh_req.head.BrnId,0x20,sizeof(zgyh_req.head.BrnId));				//网点号; 空格
		memset(zgyh_req.head.TmlId,0x20,sizeof(zgyh_req.head.TmlId));				//终端号; 空格
		memset(zgyh_req.head.TelId,0x20,sizeof(zgyh_req.head.TelId));				//柜员号; 空格
		memset(zgyh_req.head.Filer1,0x20,sizeof(zgyh_req.head.Filer1));				//预留项;
		zgyh_req.head.Mchno_len=0x08;				//固定值; 0x08
		memcpy(zgyh_req.head.Merch_no,BANK_ZGYH_MERCH_NO,8);			//单位编码;  必填
		memset(zgyh_req.head.Mch_name,0x20,sizeof(zgyh_req.head.Mch_name));			//单位名称;空格
		memset(zgyh_req.head.Errcd,0x20,sizeof(zgyh_req.head.Errcd));				//错误代码;
		memset(zgyh_req.head.ErrMsg,0x20,sizeof(zgyh_req.head.ErrMsg));				//错误信息;

		sprintf(sSerialno,"%d",pNode->SendNo);
		memcpy(zgyh_req.head.LocalNo,sSerialno,strlen(sSerialno));			//本地流水号

		//sprintf(zgyh_req.head.LocalNo,"%d",pNode->SendNo);			//本地流水号;
		memset(zgyh_req.head.BankNo,0x20,sizeof(zgyh_req.head.BankNo));				//银行流水号;
		memset(zgyh_req.head.Filer2,0x20,sizeof(zgyh_req.head.Filer2));				//预留;

		memcpy(zgyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));			//校园卡帐号
		memcpy(zgyh_req.BankCard,pNode->BankCardNo,strlen(pNode->BankCardNo));	//银行卡号
		zgyh_req.CardType='D';				//卡类型；C信用卡,D借记卡
		sprintf(sMoney,"%013d",atoi(pNode->TransMoney)*100);
		memcpy(zgyh_req.TranMoney,sMoney,sizeof(zgyh_req.TranMoney));	//交易金额

		//memset(zgyh_req.PinBlock,0x20,sizeof(zgyh_req.PinBlock));			//预留
		//memset(zgyh_req.TpkUdlmk,0x20,sizeof(zgyh_req.TpkUdlmk));			//预留
		//memset(zgyh_req.XykSqh,0x20,sizeof(zgyh_req.XykSqh));		//信用卡授权号
		sprintf(sSerialno,"%d",pNode->RecvNo);
		memcpy(zgyh_req.OldLocalNo,sSerialno,strlen(sSerialno));			//本地流水号
		//sprintf(zgyh_req.OldLocalNo,"%d",pNode->RecvNo);		//原本地流水号

		//Trace_Bank_Package_ZGYH_R(&zgyh_req,"Send query bank package:中国银行");
		ret=send_to_and_recv_from_bank(BANK_ZGYH,(char*)&zgyh_req,sizeof(zgyh_req),(char*)&zgyh_ans,sizeof(zgyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		//Trace_Bank_Package_ZGYH_A(&zgyh_ans,"Receivce query bank package:中国银行");
		if(0!=strncmp(zgyh_ans.head.Ret,"0000",4))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s] ",zgyh_ans.head.Ret);
			memcpy(temp,zgyh_ans.head.Ret,4);
			temp[4]=0;
			switch(atoi(temp))
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
				case 4:		//银行密码错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//银行处理超时
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//其他错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}
	}
	//工商银行
	else if(g_Bank.BankUnit[i].iBankID==BANK_GSYH)
	{
		memcpy(gsyh_req.ZoneNo,BANK_GSYH_ZONE_NO_GZ,4); //地区编号;广州:3602,珠海:2002;
		memcpy(gsyh_req.BusiType,BANK_GSYH_TYPE_SCHOOL,2);//交易类型，固定11
		memcpy(gsyh_req.TranCode,BANK_GSYH_TRADE_CODE_DETRANS,2);////交易类型;1:转帐,2:取消,3:余额查询
		gsyh_req.TranFlag[0]='1';						//交易标志;0:正交易,1:反交易
		memcpy(gsyh_req.BankCardNo,pNode->BankCardNo,strlen(pNode->BankCardNo));//银行卡号;借方帐号，清算时为学校帐号			
		sprintf(sMoney,"%010d",atoi(pNode->TransMoney)*100);
		memcpy(gsyh_req.TranMoney,sMoney,sizeof(gsyh_req.TranMoney));	//交易金额
		memcpy(gsyh_req.MoneyType,"001",3);//货币种类;001:人民币
		memcpy(gsyh_req.TranDate,pNode->TradeDate,8); //交易日期;YYYY-MM-DD
		memcpy(gsyh_req.TranTime,pNode->TradeTime,6);//交易时间;HHMMSS
		gsyh_req.PwdFlag[0]='0';
		gsyh_req.PwdType[0]='0';	
		sprintf(sSerialno,"%d",pNode->SendNo);
		memcpy(gsyh_req.LocalSn,sSerialno,strlen(sSerialno));			//本地流水号
		//sprintf(gsyh_req.LocalSn,"%d",pNode->SendNo);			//本地流水号
		sprintf(sSerialno,"%d",pNode->RecvNo);
		memcpy(gsyh_req.LocalDetranSn,sSerialno,strlen(sSerialno));			//冲正时填入的原转帐交易流水号
		//sprintf(gsyh_req.LocalDetranSn,"%d",pNode->RecvNo);	//冲正时填入的原转帐交易流水号
		//memcpy(gsyh_req.BankSn,"000000",6);			//银行流水号
		memcpy(gsyh_req.MercAccount,BANK_GSYH_MERCH_NO,5);	//圈存时为中山大学商户号,清算时为商户的商户号
		memcpy(gsyh_req.MercAccountCode,"01",2);		//户代号，指商户当有多个银行帐号时，该字段指示是哪一个帐号；先固定为01;
		memcpy(gsyh_req.GDCAccount,pNode->CardNo,10);			//校园卡号;
		memcpy(gsyh_req.PosNo,pNode->TerminalId,strlen(pNode->TerminalId));	//圈存机号;
		memcpy(gsyh_req.AgentPercent,"000000000",9);		//清算时的代理提成百分比
		memcpy(gsyh_req.AgentType,"01",2);			//业务种类,01:圈存,02:消费;
		memset(gsyh_req.Filter,0x20,sizeof(gsyh_req.Filter));				//空格补位
		Trace_Bank_Package_GSYH(&gsyh_req,"Send query bank package:工商银行");
		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"Send query bank package:工商银行");
		if(0!=strncmp(gsyh_ans.RetCode,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",gsyh_ans.RetCode);
			memcpy(temp,gsyh_ans.RetCode,2);
			temp[2]=0;
			switch(atoi(temp))
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
				case 4:		//银行密码错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//银行处理超时
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//其他错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//填充应答包
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		//memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		//writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	//建设银行
	else if(g_Bank.BankUnit[i].iBankID==BANK_JSYH)
	{
		char buf[2048]="";
		char bitmap[16]={0x70,0x38,0x00,0x01,0x08,0x80,0x00,0x00};
		ret=iso8583_set(&iso_jsyh_req, 0, (unsigned char*)BANK_JSYH_TRADE_CODE_DETRANS_REQ, 4);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_jsyh_req, 1, (unsigned char*)bitmap,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_jsyh_req, 2, (unsigned char*)pNode->BankCardNo,strlen(pNode->BankCardNo));
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_jsyh_req, 3, (unsigned char*)"000000", 6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		sprintf(buf,"%012d",atoi(pNode->TransMoney)*100);
		ret=iso8583_set(&iso_jsyh_req, 4,(unsigned char*)buf , 12);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		memset(buf,0,sizeof buf);
		sprintf(buf,"%020d",pNode->RecvNo);
		ret=iso8583_set(&iso_jsyh_req, 11,(unsigned char*)buf , 20);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_jsyh_req,13,(unsigned char*)pNode->TradeDate,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=iso8583_set(&iso_jsyh_req,12,(unsigned char*)pNode->TradeTime,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_jsyh_req,32,(unsigned char*)BANK_JSYH_MERCH_NO,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		sprintf(sSerialno,"%020d",pNode->SendNo);
		ret=iso8583_set(&iso_jsyh_req,37,(unsigned char*)sSerialno,20);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		memset(buf,0,sizeof buf);
		sprintf(buf,"%8s",pNode->TerminalId);
		ret=iso8583_set(&iso_jsyh_req,41,(unsigned char*)buf,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_pack(&iso_jsyh_req, jsyh_sbuf);
		if(ret<=0)
		{
			writelog(LOG_ERR,"Pack8583 error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=send_to_and_recv_from_bank(BANK_JSYH,(char *)jsyh_sbuf,ret,(char*)jsyh_abuf,200,&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		//ret=UnPack8583((unsigned char*)head_jsyh_ans.msg,&jsyh_ans,2);
		ret=iso8583_unpack(&iso_jsyh_ans, jsyh_abuf);
		if(ret<0)
		{
			writelog(LOG_ERR,"UnPack8583 error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		if(0!=strncmp((char *)iso_jsyh_ans.fld[39].buf,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",iso_jsyh_ans.fld[39].buf);
			memcpy(temp,iso_jsyh_ans.fld[39].buf,2);
			temp[2]=0;
			switch(atoi(temp))
			{
				case 41:		//银行卡挂失
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 36:		//银行卡状态错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 51:		//银行卡金额不足
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 75:		//银行密码错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 96:		//银行处理超时
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 22:		//其他错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}
	}

	else
	{
		return E_TRANS_BANK_CARD_NONSUPPORT;
	}
	return 0;
}
int Bank_CheckLine()
{
	return 0;
}

int Bank_SignIn(INNER_TRANS_REQUEST *pNode)
{
	return 0;
}
int Bank_SignOut()
{
	return 0;
}
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank)
{
	struct SockNode  SockNode;
	char bank_ip[20]="";
	int bank_port=0;
	int ret=0;
	int delay_time=5000;

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
	ret=	SockNode.hSock.RecvDesignedLen(pRecv,recv_len,delay_time);
	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pRecv,ret,16);
	if (ret<=0)
	{
		writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
		return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
	}
	SockNode.hSock.Close();
	return 0;
}

void Trace_Bank_Package_GSYH(BANK_GSYH_TRADE_STRUCT *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);

	if(debug < 2)
		return;
	printf("交易代码	=[%2.2s]\n",pTransPak->TranCode);
	printf("交易结果	=[%2.2s]\n",pTransPak->RetCode);
	printf("交易日期	=[%8.8s]\n",pTransPak->TranDate);
	printf("交易时间	=[%6.6s]\n",pTransPak->TranTime);
	printf("校园卡帐号	=[%10.10s]\n",pTransPak->GDCAccount);
	printf("银行卡号	=[%20.20s]\n",pTransPak->BankCardNo);
	printf("商户号 		=[%8.8s]\n",pTransPak->MercAccount);
	printf("转账金额	=[%9.9s]\n",pTransPak->TranMoney);
	printf("借记卡余额	=[%9.9s]\n",pTransPak->TranMoney);
	printf("校园端流水号	=[%8.8s]\n",pTransPak->LocalSn);
	printf("银行流水号	=[%20.20s]\n",pTransPak->BankSn);
	printf("终端设备号	=[%5.5s]\n",pTransPak->PosNo);

}
void Trace_Bank_Package_ZGYH_R(BANK_ZGYH_TRADE_STRUCT_TRANS_REQ *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;
	printf("交易代码	=[%4.4s]\n",pTransPak->head.TranCode);
	printf("交易结果	=[%4.4s]\n",pTransPak->head.Ret);
	//printf("交易日期	=[%8.8s]\n",pTransPak->head.);
	//printf("交易时间	=[%6.6s]\n",pTransPak->TranTime);
	printf("校园卡帐号	=[%10.10s]\n",pTransPak->GDCAccount);
	printf("银行卡号	=[%20.20s]\n",pTransPak->BankCard);
	printf("商户号 		=[%8.8s]\n",pTransPak->head.Merch_no);
	printf("转账金额	=[%13.13s]\n",pTransPak->TranMoney);
	//printf("借记卡余额	=[%9.9s]\n",pTransPak->TranMoney);
	printf("校园端流水号	=[%20.20s]\n",pTransPak->head.LocalNo);
	printf("银行流水号	=[%8.8s]\n",pTransPak->head.BankNo);
	printf("终端设备号	=[%2.2s]\n",pTransPak->head.TmlId);

}
void Trace_Bank_Package_ZGYH_A(BANK_ZGYH_TRADE_STRUCT_TRANS_ANS *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;
	printf("交易代码	=[%4.4s]\n",pTransPak->head.TranCode);
	printf("交易结果	=[%4.4s]\n",pTransPak->head.Ret);
	//printf("交易日期	=[%8.8s]\n",pTransPak->head.);
	//printf("交易时间	=[%6.6s]\n",pTransPak->TranTime);
	printf("校园卡帐号	=[%10.10s]\n",pTransPak->GDCAccount);
	printf("银行卡号	=[%20.20s]\n",pTransPak->BankCard);
	printf("商户号 		=[%8.8s]\n",pTransPak->head.Merch_no);
	printf("转账金额	=[%9.9s]\n",pTransPak->TranMoney);
	printf("借记卡余额	=[%9.9s]\n",pTransPak->TranMoney);
	printf("校园端流水号	=[%20.20s]\n",pTransPak->head.LocalNo);
	printf("银行流水号	=[%8.8s]\n",pTransPak->head.BankNo);
	printf("终端设备号	=[%2.2s]\n",pTransPak->head.TmlId);

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

