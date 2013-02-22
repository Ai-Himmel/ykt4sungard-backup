/* ----------------------------------------------------------
 * �������ƣ�bank_icbc_nj.cpp
 * �������ڣ�2007-07-27 14:58
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��Ͼ��������нӿ�
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

//���п��󶨹�ϵ
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
	//��ֹ����Խ��
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
			strcpy(BCR->retmsg,"�����������");
		}
		else
		{
			strcpy(BCR->retmsg,"���ж�û����Ӧ");
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
		printf("���з�����Ϣ:%s\n",BCR->retmsg);
		if(strlen(BCR->retmsg)==0)
			strcpy(BCR->retmsg,"��������Ӧ��Ϣ");
		return 0;
	}
	strncpy(BCR->bankcardno,BankAns.body.BankAccNO,sizeof(BankAns.body.BankAccNO));
	trim(BCR->bankcardno);
	printf("���з��سɹ�,���п���:%s\n",BCR->bankcardno);
	writelog(LOG_INFO,"query bankcardno succeed!bankcardno[%s]",BCR->bankcardno);
	return 0;
}



//����ͨ�ýӿڹ淶���з�װ�������еĽӿ�
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

	//�����ϴ����п��������ĸ����У��������б�־�����͸���ͬ������
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
	//�й����У��й�����Ŀǰ��֧�ֲ�ѯ�������Ľӿ�
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		return E_TRANS_BANK_FUNC_NONSUPPORT;
	}
	//�������У����չ������нӿڽ��з������ݰ����������ذ�
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
				case 1:		//���п���ʧ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 2:		//���п�״̬����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 3:		//���п�����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 4:		//�����������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//���д���ʱ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//��������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//����δ֪����
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//���Ӧ���
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		strncpy(szbalance,gsyh_ans.body.Balance,12);
		szbalance[12]=0;
		ltrim(szbalance);
		*balance=atof(szbalance);
		//memcpy(pNode->Balance,gsyh_ans.body.Balance,sizeof(pNode->Balance));
		writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.body.Balance);
	}
	//�������в�֧�ֲ�ѯ���п�����
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
	

	//�����ϴ����п��������ĸ����У��������б�־�����͸���ͬ������
	//ת��transinfo���ȥ����
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
	
	//�й�����
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		return E_TRANS_BANK_CARD_NONSUPPORT;
	}
	//��������
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
		memcpy(gsyh_req.body.SchoolTransSeq,sSerialno,strlen(sSerialno));			//������ˮ��

		memset(gsyh_req.body.BankTransSeq,0x20,sizeof gsyh_req.body.BankTransSeq);
		memcpy(gsyh_req.body.BankAccNO,pNode->BankCardNo,strlen(pNode->BankCardNo));
		memcpy(gsyh_req.body.CampusCard,pNode->Reserve1,strlen(pNode->Reserve1));	
		memcpy(gsyh_req.body.StudentName,pNode->Reserve2,strlen(pNode->Reserve2));
		memcpy(gsyh_req.body.StudentID,pNode->Reserve3,strlen(pNode->Reserve3));
		sprintf(sMoney,"%012d",atoi(pNode->TransMoney));
		memcpy(gsyh_req.body.Amount,sMoney,sizeof(gsyh_req.body.Amount));	//���׽��
		memset(gsyh_req.body.Balance,0x20,sizeof gsyh_req.body.Balance);
		memset(gsyh_req.body.BankCardPwd,0x20,sizeof gsyh_req.body.BankCardPwd);

		Trace_Bank_Package_GSYH(&gsyh_req,"Send query bank package:��������");
		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"Receivce query bank package:��������");
		if(0!=strncmp(gsyh_ans.body.ReturnCode,"0000",4))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s]msg[%24.24s]",gsyh_ans.body.ReturnCode,gsyh_ans.body.Message);
			strncpy(pNode->Reserve3,gsyh_ans.body.Message,24);
			pNode->Reserve3[24]=0;
			memcpy(temp,gsyh_ans.body.ReturnCode,4);
			temp[4]=0;
			switch(atoi(temp))
			{
				case 1:		//���п���ʧ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 2:		//���п�״̬����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 3:		//���п�����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 4:		//�����������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//���д���ʱ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//��������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//����δ֪����
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//���Ӧ���
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		//memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		//writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	//��������
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
	//����signal����ֹ����ģʽ��socket

	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pSend,send_len,16);
//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);

	alarm(delay_time/1000);
	//��������
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

	
	//�������ݵ�����
	ret=SockNode.hSock.Send(pSend, send_len);
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
		writelog(LOG_ERR,"Send to bank error,ret = [%d] ",ret);
		return E_TRANS_BANK_NETERR;
	}
	else if (0==ret)
	{
		// ��Ӧ�ó����������
	      	writelog(LOG_ERR,"Send to bank error,CTcpSocket.Send should not return this error,error code is[%d]!\n",errno);
	      	return	E_TRANS_BANK_NETERR;
	}
//	writelog(LOG_INFO,"bank_ip[%s],port[%d] ",bank_ip,bank_port);

//	system("sleep 1");

	//�������з�����Ϣ
	ret=	SockNode.hSock.Recv(pRecv,recv_len,delay_time);
	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pRecv,recv_len,16);
	if (ret!=recv_len)
	{
		writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
		return	E_TRANS_BANK_NOANSWER;  // ����ʱ�������ʱ
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
	printf("���״���	=[%6.6s]\n",pTransPak->head.TradeType);
	printf("���׽��	=[%4.4s]\n",pTransPak->body.ReturnCode);
	printf("��������	=[%14.14s]\n",pTransPak->body.TradeTime);
	printf("У԰���ʺ�	=[%20.20s]\n",pTransPak->body.CampusCard);
	printf("���п���	=[%20.20s]\n",pTransPak->body.BankAccNO);
	printf("ת�˽��	=[%12.12s]\n",pTransPak->body.Amount);
	printf("��ǿ����	=[%12.12s]\n",pTransPak->body.Balance);
	printf("У԰����ˮ��	=[%16.16s]\n",pTransPak->body.SchoolTransSeq);
	printf("������ˮ��	=[%16.16s]\n",pTransPak->body.BankTransSeq);
	printf("�ֿ�������	=[%20.20s]\n",pTransPak->body.StudentName);
	printf("�ֿ������֤��	=[%20.20s]\n",pTransPak->body.StudentID);

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
