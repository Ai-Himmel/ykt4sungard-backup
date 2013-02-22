/* ----------------------------------------------------------
 * 程序名称：bank_icbc_nj.cpp
 * 创建日期：2007-07-27 14:58
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：南京工商银行接口
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
#include "bank_icbc_nj.h"
#include "mac.h"
#include "typdef.h"


//void TRACE_BANK_TRANS(BANK_TRANS_REQUEST *pTransPak, char *stage);
void Trace_Bank_Package_GSYH(MSG *pTransPak, char *stage);
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank);
void WriteBufferLog(char *pBuffer,int Buffer_len,int colum_num);
int debug=2;

//银行卡绑定关系
int BankCardRelation(tagBankCardRelation* BCR)
{
	int ret=0;
	MSG BankReq;
	MSG BankAns;
	
	memset(&BankReq,0x20,sizeof BankReq);
	memset(&BankAns,0,sizeof BankAns);
	memcpy(BankReq.head.MsgLength,"0256",4);
	switch(BCR->transtype)
	{
		case 'A':
			memcpy(BankReq.head.TradeType,BANK_ICBC_TRANSCODE_RELATION_ADD,strlen(BANK_ICBC_TRANSCODE_RELATION_ADD));
			break;
		case 'D':
			memcpy(BankReq.head.TradeType,BANK_ICBC_TRANSCODE_RELATION_DEL,strlen(BANK_ICBC_TRANSCODE_RELATION_DEL));
			break;
		default:
			memcpy(BankReq.head.TradeType,BANK_ICBC_TRANSCODE_RELATION_QRY,strlen(BANK_ICBC_TRANSCODE_RELATION_QRY));
			break;
	}
	memcpy(BankReq.head.Sender,BANK_ICBC_SENDER,strlen(BANK_ICBC_SENDER));
	memcpy(BankReq.head.Receiver,BANK_ICBC_RECEIVER,strlen(BANK_ICBC_RECEIVER));
//	memset(gsyh_req.head.PINKeySynFlag,0x20,sizeof gsyh_req.head.PINKeySynFlag);
//	memset(gsyh_req.head.MACKeySynFlag,0x20,sizeof gsyh_req.head.MACKeySynFlag);
//	memset(gsyh_req.head.MAC,0x20,sizeof gsyh_req.head.MAC);

//	memset(gsyh_req.body.ReturnCode,0x20,sizeof gsyh_req.body.ReturnCode);
//	memset(gsyh_req.body.Message,0x20,sizeof gsyh_req.body.Message);
	memcpy(BankReq.body.TradeTime,getsysdatetime(NULL),14);
//	memset(gsyh_req.body.SchoolTransSeq,0x20,sizeof gsyh_req.body.SchoolTransSeq);
//	memset(gsyh_req.body.BankTransSeq,0x20,sizeof gsyh_req.body.BankTransSeq);
	//防止拷贝越界
	BCR->bankcardno[20]=0;
	BCR->stuempno[20]=0;
	BCR->custname[20]=0;
	BCR->idno[18]=0;
	memcpy(BankReq.body.BankAccNO,BCR->bankcardno,strlen(BCR->bankcardno));
	memcpy(BankReq.body.CampusCard,BCR->stuempno,strlen(BCR->stuempno));	
	memcpy(BankReq.body.StudentName,BCR->custname,strlen(BCR->custname));
	memcpy(BankReq.body.StudentID,BCR->idno,strlen(BCR->idno));
//	memset(gsyh_req.body.Amount,0x20,sizeof gsyh_req.body.Amount);
//	memset(gsyh_req.body.Balance,0x20,sizeof gsyh_req.body.Balance);
//	memset(gsyh_req.body.BankCardPwd,0x20,sizeof gsyh_req.body.BankCardPwd);
	
	Trace_Bank_Package_GSYH(&BankReq,"send query bank package");
////////////////////////////////////////////////////////////////////////
//test
//	strcpy(BCR->bankcardno,"12345543211234554321");
//	return 0;//test
	ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&BankReq,sizeof(BankReq),(char*)&BankAns,sizeof(BankAns),&g_Bank);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
		if(E_TRANS_BANK_NETERR==ret)
		{
			strcpy(BCR->retmsg,"银行网络故障");
		}
		else
		{
			strcpy(BCR->retmsg,"银行端没有响应");
		}
		return ret;
	}
	Trace_Bank_Package_GSYH(&BankAns,"receivce query bank package");
	
	if(0!=strncmp(BankAns.body.ReturnCode,"0000",4))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s]msg[%24.24s]",BankAns.body.ReturnCode,BankAns.body.Message);
		char retcode[5]="";
		strncpy(retcode,BankAns.body.ReturnCode,sizeof(BankAns.body.ReturnCode));
		retcode[4]=0;
		BCR->retcode=atoi(retcode);
		strncpy(BCR->retmsg,BankAns.body.Message,sizeof(BankAns.body.Message));
		trim(BCR->retmsg);
		printf("银行返回信息:%s\n",BCR->retmsg);
		if(strlen(BCR->retmsg)==0)
			strcpy(BCR->retmsg,"银行无响应信息");
		return 0;
	}
	strncpy(BCR->bankcardno,BankAns.body.BankAccNO,sizeof(BankAns.body.BankAccNO));
	trim(BCR->bankcardno);
	printf("银行返回成功,银行卡号:%s\n",BCR->bankcardno);
	writelog(LOG_INFO,"query bankcardno succeed!bankcardno[%s]",BCR->bankcardno);
	return 0;
}



//按照通用接口规范进行封装各自银行的接口
int Bank_QueryBalance(INNER_TRANS_REQUEST * pNode,double *balance)
{

	int ret=0;
	char temp[6]="";
	int i=0;
	int flag=0;
	char szbalance[13]="";

	MSG gsyh_req;
	MSG gsyh_ans;
	
	memset(&gsyh_req,0x20,sizeof gsyh_req);
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
		memset(&gsyh_req,0x20,sizeof(gsyh_req));
		memcpy(gsyh_req.head.MsgLength,"0256",4);
		sprintf(gsyh_req.head.TradeType,"%-6s",BANK_GSYH_TRADE_CODE_QUERYBALANCE);
		sprintf(gsyh_req.head.Sender,"%-7s",BANK_GSYH_SENDER);
		sprintf(gsyh_req.head.Receiver,"%-7s",BANK_GSYH_RECEIVER);
		memset(gsyh_req.head.PINKeySynFlag,0x20,sizeof gsyh_req.head.PINKeySynFlag);
		memset(gsyh_req.head.MACKeySynFlag,0x20,sizeof gsyh_req.head.MACKeySynFlag);
		memset(gsyh_req.head.MAC,0x20,sizeof gsyh_req.head.MAC);

		memset(gsyh_req.body.ReturnCode,0x20,sizeof gsyh_req.body.ReturnCode);
		memset(gsyh_req.body.Message,0x20,sizeof gsyh_req.body.Message);
		memcpy(gsyh_req.body.TradeTime,getsysdatetime(NULL),14);
		memset(gsyh_req.body.SchoolTransSeq,0x20,sizeof gsyh_req.body.SchoolTransSeq);
		memset(gsyh_req.body.BankTransSeq,0x20,sizeof gsyh_req.body.BankTransSeq);
		memcpy(gsyh_req.body.BankAccNO,pNode->BankCardNo,strlen(pNode->BankCardNo));
		memcpy(gsyh_req.body.CampusCard,pNode->Reserve1,strlen(pNode->Reserve1));	
		memcpy(gsyh_req.body.StudentName,pNode->Reserve2,strlen(pNode->Reserve2));
		memcpy(gsyh_req.body.StudentID,pNode->Reserve3,strlen(pNode->Reserve3));
		memset(gsyh_req.body.Amount,0x20,sizeof gsyh_req.body.Amount);
		memset(gsyh_req.body.Balance,0x20,sizeof gsyh_req.body.Balance);
		memset(gsyh_req.body.BankCardPwd,0x20,sizeof gsyh_req.body.BankCardPwd);
		
		Trace_Bank_Package_GSYH(&gsyh_req,"send query bank package");

		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"receivce query bank package");
		if(0!=strncmp(gsyh_ans.body.ReturnCode,"0000",4))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s]msg[%24.24s]",gsyh_ans.body.ReturnCode,gsyh_ans.body.Message);
			strncpy(pNode->Reserve3,gsyh_ans.body.Message,24);
			pNode->Reserve3[24]=0;
			memcpy(temp,gsyh_ans.body.ReturnCode,4);
			temp[4]=0;
			return 9998;
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
		strncpy(szbalance,gsyh_ans.body.Balance,12);
		szbalance[12]=0;
		ltrim(szbalance);
		*balance=atof(szbalance);
		//memcpy(pNode->Balance,gsyh_ans.body.Balance,sizeof(pNode->Balance));
		writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.body.Balance);
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

	MSG gsyh_req;
	MSG gsyh_ans;
	
	memset(&gsyh_req,0x20,sizeof gsyh_req);
	memset(&gsyh_req,0x20,sizeof gsyh_req);
	

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
		return E_TRANS_BANK_CARD_NONSUPPORT;
	}
	//工商银行
	else if(g_Bank.BankUnit[i].iBankID==BANK_GSYH)
	{

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
		sprintf(sSerialno,"%d",serial_no);
		memcpy(gsyh_req.body.SchoolTransSeq,sSerialno,strlen(sSerialno));			//本地流水号

		memset(gsyh_req.body.BankTransSeq,0x20,sizeof gsyh_req.body.BankTransSeq);
		memcpy(gsyh_req.body.BankAccNO,pNode->BankCardNo,strlen(pNode->BankCardNo));
		memcpy(gsyh_req.body.CampusCard,pNode->Reserve1,strlen(pNode->Reserve1));	
		memcpy(gsyh_req.body.StudentName,pNode->Reserve2,strlen(pNode->Reserve2));
		memcpy(gsyh_req.body.StudentID,pNode->Reserve3,strlen(pNode->Reserve3));
		sprintf(sMoney,"%012d",atoi(pNode->TransMoney));
		memcpy(gsyh_req.body.Amount,sMoney,sizeof(gsyh_req.body.Amount));	//交易金额
		memset(gsyh_req.body.Balance,0x20,sizeof gsyh_req.body.Balance);
		memset(gsyh_req.body.BankCardPwd,0x20,sizeof gsyh_req.body.BankCardPwd);

		Trace_Bank_Package_GSYH(&gsyh_req,"Send query bank package:工商银行");
		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"Receivce query bank package:工商银行");
		if(0!=strncmp(gsyh_ans.body.ReturnCode,"0000",4))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s]msg[%24.24s]",gsyh_ans.body.ReturnCode,gsyh_ans.body.Message);
			strncpy(pNode->Reserve3,gsyh_ans.body.Message,24);
			pNode->Reserve3[24]=0;
			memcpy(temp,gsyh_ans.body.ReturnCode,4);
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

		//填充应答包
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		//memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		//writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	//建设银行
	else if(g_Bank.BankUnit[i].iBankID==BANK_JSYH)
	{
		return E_TRANS_BANK_CARD_NONSUPPORT;
	}
	else
	{
		return E_TRANS_BANK_CARD_NONSUPPORT;
	}
	return 0;

}

int Bank_Undo(INNER_TRANS_REQUEST * pNode)
{
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

//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);
	des2src(bank_ip,pBank->BankUnit[pBank->cur_bankid].szBankIP);
//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);
	bank_port=pBank->BankUnit[pBank->cur_bankid].iBankPort;
//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);
	delay_time=pBank->BankUnit[pBank->cur_bankid].iBankTimeout;
//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);
	//启用signal，防止阻塞模式的socket

	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pSend,send_len,16);
//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);

	alarm(delay_time/1000);
	//连接银行
//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);
	
	bool bSucc=SockNode.hSock.ConnectTcp(bank_ip,bank_port);
	if(!bSucc)
	{	
		alarm(0);
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],bank_ip[%s],port[%d] ",ret,bank_ip,bank_port);
		return E_TRANS_BANK_NETERR;
	}
	alarm(0);
//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);

	
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
//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);

//	system("sleep 1");

	//接收银行返回信息
	ret=	SockNode.hSock.Recv(pRecv,recv_len,delay_time);
	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pRecv,recv_len,16);
	if (ret!=recv_len)
	{
		writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
		return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
	}
	SockNode.hSock.Close();
//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);
	return 0;
}

void Trace_Bank_Package_GSYH(MSG *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);

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
void WriteBufferLog(char *pBuffer,int Buffer_len,int colum_num)
{
//	writelog(LOG_INFO,"$$$$$$$$$$$$$bufferlen[%d]",Buffer_len);
	return;
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

int Bank_GetRecvPacket(INNER_TRANS_REQUEST * pNode, ST_BANK *bank, void *recv_packet)
{
	return 0;
}
