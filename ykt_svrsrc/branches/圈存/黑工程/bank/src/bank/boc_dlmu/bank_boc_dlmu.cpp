/* ----------------------------------------------------------
 * 程序名称：bank_boc_dl.cpp
 * 创建日期：2010-07-22 14:58
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
#include "bank_boc_dlmu.h"
#include "mac.h"
#include "typdef.h"
#include "iso8583.h"



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

	MSG8583 zgyh_req,zgyh_ans;
	H_MSG8583 head_zgyh_req,head_zgyh_ans;

	ISO_MSG iso_zgyh_req,iso_zgyh_ans;

	iso8583_init(&iso_zgyh_req);
	iso8583_init(&iso_zgyh_ans);

	char zgyh_sbuf[2048]="";
	char zgyh_abuf[2048]="";
	

	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&head_zgyh_req,0x20,sizeof head_zgyh_req);
	memset(&head_zgyh_ans,0x20,sizeof head_zgyh_ans);

	
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


	MSG8583 zgyh_req,zgyh_ans;
	H_MSG8583 head_zgyh_req,head_zgyh_ans;

	ISO_MSG iso_zgyh_req,iso_zgyh_ans;

	iso8583_init(&iso_zgyh_req);
	iso8583_init(&iso_zgyh_ans);

	char zgyh_sbuf[2048]="";
	char zgyh_abuf[2048]="";
	

	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&head_zgyh_req,0x20,sizeof head_zgyh_req);
	memset(&head_zgyh_ans,0x20,sizeof head_zgyh_ans);
	

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
		char buf[2048]="";
		char bitmap[16]={0x70,0x18,0x00,0x01,0x08,0x80,0x00,0x00};
		ret=iso8583_set(&iso_zgyh_req, 0, (unsigned char*)BANK_ZGYH_TRADE_CODE_TRANS_REQ, 4);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_zgyh_req, 1, (unsigned char*)bitmap,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_zgyh_req, 2, (unsigned char*)pNode->BankCardNo,strlen(pNode->BankCardNo));
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_zgyh_req, 3, (unsigned char*)BANK_ZGYH_EXEC_CODE_TRANS_REQ, 6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		sprintf(buf,"%012s",pNode->TransMoney);
		ret=iso8583_set(&iso_zgyh_req, 4,(unsigned char*)buf , 12);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

		memset(buf,0x00,sizeof buf);
		sprintf(buf,"%06d",pNode->RecvNo);
		ret=iso8583_set(&iso_zgyh_req,11,(unsigned char*)buf,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=iso8583_set(&iso_zgyh_req,13,(unsigned char*)pNode->TradeDate,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=iso8583_set(&iso_zgyh_req,12,(unsigned char*)pNode->TradeTime,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		memset(buf,0x00,sizeof buf);
		sprintf(buf,"%08s",pNode->SencodMagTune+20);
		ret=iso8583_set(&iso_zgyh_req,14,(unsigned char*)buf,4);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_zgyh_req,22,(unsigned char*)"022",3);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=iso8583_set(&iso_zgyh_req,24,(unsigned char*)"003",3);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_zgyh_req,25,(unsigned char*)"000",3);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		memset(buf,0x00,sizeof buf);
		sprintf(buf,"%02d",strlen(pNode->SencodMagTune));
		sprintf(buf+2,"%s",pNode->SencodMagTune);
		ret=iso8583_set(&iso_zgyh_req,35,(unsigned char*)buf,strlen(buf));
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		memset(buf,0x00,sizeof buf);
		sprintf(buf,"%03d",strlen(pNode->ThirdMagTune));
		sprintf(buf+3,"%s",pNode->ThirdMagTune);
		ret=iso8583_set(&iso_zgyh_req,36,(unsigned char*)buf,strlen(buf));
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

//		sprintf(sSerialno,"%020d",serial_no);
		//memcpy(jsyh_req.field37,sSerialno,strlen(sSerialno));
//		ret=iso8583_set(&iso_jsyh_req,37,(unsigned char*)sSerialno,20);
//		if(ret<=0)
//		{
//			writelog(LOG_ERR,"iso8583_set error");
//			return E_TRANS_UNKNOW_ERROR;
//		}
		//memcpy(jsyh_req.termID,pNode->TerminalId,strlen(pNode->TerminalId));
		memset(buf,0,sizeof buf);
		sprintf(buf,"%8s",pNode->TerminalId);
		ret=iso8583_set(&iso_zgyh_req,41,(unsigned char*)buf,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=iso8583_set(&iso_zgyh_req,42,(unsigned char*)BANK_ZGYH_MERCH_NO,15);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=iso8583_set(&iso_zgyh_req,52,(unsigned char*)pNode->BankCardPwd,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		memset(buf,0x00,sizeof buf);
		sprintf(buf,"%06d",pNode->RecvNo);
		ret=iso8583_set(&iso_zgyh_req,62,(unsigned char*)buf,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		
		ret=iso8583_pack(&iso_zgyh_req, zgyh_sbuf);
		if(ret<=0)
		{
			writelog(LOG_ERR,"Pack8583 error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=send_to_and_recv_from_bank(BANK_JSYH,(char *)zgyh_sbuf,ret,(char*)zgyh_abuf,200,&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		ret=iso8583_unpack(&iso_zgyh_ans, zgyh_abuf);
		if(ret<0)
		{
			writelog(LOG_ERR,"UnPack8583 error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		if(0!=strncmp((char *)iso_zgyh_ans.fld[39].buf,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",iso_zgyh_ans.fld[39].buf);
			memcpy(temp,iso_zgyh_ans.fld[39].buf,2);
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
				case 55:		//银行密码错误
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

	MSG8583 zgyh_req,zgyh_ans;
	H_MSG8583 head_zgyh_req,head_zgyh_ans;

	ISO_MSG iso_zgyh_req,iso_zgyh_ans;

	iso8583_init(&iso_zgyh_req);
	iso8583_init(&iso_zgyh_ans);

	char zgyh_sbuf[2048]="";
	char zgyh_abuf[2048]="";


	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

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

