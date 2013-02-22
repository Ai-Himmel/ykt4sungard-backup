/* ----------------------------------------------------------
 * 程序名称：bank_ccb_nm.cpp
 * 创建日期：2009-08-10
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：南大工行转账接口
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_icbc_nanjin.h"
#include "tcp.h"

#define STRLENCPY(des,src,len) strncpy(des,src,strlen(src)>len?len:strlen(src))
int debug=0;
void Trace_Bank_Package_GSYH(MSG *pTransPak, char *stage);
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_PACK *rPack);

int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	return 0;
}

//int Bank_Transfer(INNER_TRANS_REQUEST * pNode,int serial_no)
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	char temp[6]="";
	int flag=0;
	int i=0;
	int len=0;
	char sMoney[32]="";
	char sSerialno[32]="";

	MSG gsyh_req;
	MSG gsyh_ans;

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SDATE1,F_SCERT_NO,0);

	writelog(LOG_DEBUG,"nanjin icbc Bank_Trans start"); 
	memset(&gsyh_req,0x20,sizeof(gsyh_req));
	memcpy(gsyh_req.head.MsgLength,"0256",4);
	sprintf(gsyh_req.head.TradeType,"%-6s",BANK_GSYH_TRADE_CODE_TRANS);
	sprintf(gsyh_req.head.Sender,"%-7s",BANK_GSYH_SENDER);
	sprintf(gsyh_req.head.Receiver,"%-7s",BANK_GSYH_RECEIVER);
	memset(gsyh_req.head.PINKeySynFlag,0x20,sizeof gsyh_req.head.PINKeySynFlag);
	memset(gsyh_req.head.MACKeySynFlag,0x20,sizeof gsyh_req.head.MACKeySynFlag);
	memset(gsyh_req.head.MAC,0x20,sizeof gsyh_req.head.MAC);

	memset(gsyh_req.body.ReturnCode,0x20,sizeof gsyh_req.body.ReturnCode);
	memset(gsyh_req.body.Message,0x20,sizeof gsyh_req.body.Message);
	memcpy(gsyh_req.body.TradeTime,getsysdatetime(NULL),14);
	//sprintf(sSerialno,"%d",serial_no);
	STRLENCPY(sSerialno,rPack->sholder_ac_no+8,32);
	STRLENCPY(gsyh_req.body.SchoolTransSeq,sSerialno,16);			//本地流水号

	memset(gsyh_req.body.BankTransSeq,0x20,sizeof gsyh_req.body.BankTransSeq);
	STRLENCPY(gsyh_req.body.BankAccNO,rPack->scust_limit2,20);
	STRLENCPY(gsyh_req.body.CampusCard,rPack->sphone,20);	
	STRLENCPY(gsyh_req.body.StudentName,rPack->scust_limit,20);
	STRLENCPY(gsyh_req.body.StudentID,rPack->scust_auth2,18);
	int amt = D2I(rPack->damt0*100);
	sprintf(sMoney,"%012d",amt);
	memcpy(gsyh_req.body.Amount,sMoney,sizeof(gsyh_req.body.Amount));	//交易金额
	memset(gsyh_req.body.Balance,0x20,sizeof gsyh_req.body.Balance);
	memset(gsyh_req.body.BankCardPwd,0x20,sizeof gsyh_req.body.BankCardPwd);

	out_pack->lvol1 = 1;	
	*pRetCode = 0;
	
	Trace_Bank_Package_GSYH(&gsyh_req,"send query bank package");
	ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),rPack);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
		return E_TRANS_BANK_NOANSWER;
	}

	Trace_Bank_Package_GSYH(&gsyh_ans,"receivce query bank package");
	if(0!=strncmp(gsyh_ans.body.ReturnCode,"0000",4))
	{
		strncpy(szMsg, gsyh_ans.body.Message,sizeof(gsyh_ans.body.Message) );
		writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s]msg[%24.24s]",gsyh_ans.body.ReturnCode,gsyh_ans.body.Message);
		//strncpy(pNode->Reserve3,gsyh_ans.body.Message,24);
		//pNode->Reserve3[24]=0;
		memcpy(temp,gsyh_ans.body.ReturnCode,4);
		temp[4]=0;
		
		switch(atoi(temp))
		{
			case 1:		//银行卡挂失
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				*pRetCode=E_TRANS_BANKCARD_LOST;
			case 2:		//银行卡状态错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				*pRetCode=E_TRANS_BANKACC_STATERR;
			case 3:		//银行卡金额不足
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				*pRetCode=E_TRANS_BANKACC_NOMONEY;
			case 4:		//银行密码错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				*pRetCode=E_TRANS_BANKCARD_PWDERR;
			case 98:		//银行处理超时
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				*pRetCode=E_TRANS_BANK_NOANSWER;
			case 99:		//其他错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				*pRetCode=E_TRANS_UNKNOW_ERROR;
			default:		//其他未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				*pRetCode=E_TRANS_UNKNOW_ERROR;
		}
		return -1;
	}		
	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;

}

void Trace_Bank_Package_GSYH(MSG *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	if(debug < 2)
		return;
	printf("交易代码	=[%6.6s]\n",pTransPak->head.TradeType);
	printf("交易结果	=[%4.4s]\n",pTransPak->body.ReturnCode);
	printf("交易日期	=[%14.14s]\n",pTransPak->body.TradeTime);
	printf("校园卡帐号	=[%20.20s]\n",pTransPak->body.CampusCard);
	printf("银行卡号	=[%20.20s]\n",pTransPak->body.BankAccNO);
	printf("转账金额	=[%12.12s]\n",pTransPak->body.Amount);
	printf("借记卡余额	=[%12.12s]\n",pTransPak->body.Balance);
	printf("校园端流水号	=[%16.16s]\n",pTransPak->body.SchoolTransSeq);
	printf("银行流水号	=[%16.16s]\n",pTransPak->body.BankTransSeq);
	printf("持卡人姓名	=[%20.20s]\n",pTransPak->body.StudentName);
	printf("持卡人身份证号	=[%20.20s]\n",pTransPak->body.StudentID);

}

int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_PACK *rPack)
{
	struct SockNode  SockNode;
	char bank_ip[20]="";
	int bank_port=0;
	int ret=0;
	int delay_time=5000;

	des2src(bank_ip,rPack->scust_auth);					// 银行ip
	bank_port=rPack->lvol0;									// 银行端口
	delay_time = rPack->lvol1;								// 等待银行超时时间
	
	//启用signal，防止阻塞模式的socket

	alarm(delay_time/1000);
	//连接银行
	writelog(LOG_DEBUG,"bank_ip[%s],port[%d] ",bank_ip,bank_port);
	
	ret=SockNode.hSock.ConnectTcp(bank_ip,bank_port);
	if(!ret)
	{	
		alarm(0);
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],bank_ip[%s],port[%d] ",ret,bank_ip,bank_port);
		return E_TRANS_BANK_NETERR;
	}
	alarm(0);
	
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
	if (ret!=recv_len)
	{
		writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
		return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
	}
	SockNode.hSock.Close();
	return 0;
}

