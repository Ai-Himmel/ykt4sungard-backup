/* ----------------------------------------------------------
 * �������ƣ�bank_nyyh.cpp
 * �������ڣ�2007-07-27 14:58
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�ͨ�ýӿڹ淶�ķ�װ
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


void TRACE_BANK_TRANS(BANK_TRANS_REQUEST *pTransPak, char *stage);
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank);
void WriteBufferLog(char *pBuffer,int Buffer_len,int colum_num);
int debug=2;

//����ͨ�ýӿڹ淶���з�װ�������еĽӿ�
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
	
	//��֯���а�
	//д���״���
	memcpy( BankReqPak.TradeCode,TRADE_BANK_QUERY, BANK_TRADE_CODE_LEN);
	//д�������ںͽ���ʱ��
	getsysdate(BankReqPak.TradeDate);
	getsystime(BankReqPak.TradeTime);
	//memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
	//memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	//д���п����ֶ�
	//sprintf(BankReqPak.BankCardNo,"%-20s","1030399110000001042");	//д���п����ֶ�
	sprintf(BankReqPak.BankCardNo,"%-20s",from_pos.BankCardNo);
	//д���п������ֶ�
	//ͨ��16���Ƹ�ʽ���䣬�ٽ���
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

	//дУ԰����ˮ��
	sprintf(BankReqPak.CustSn,"%-8f",0);
	//дԺУ����
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);
	BankReqPak.AutoFlag='0';
	//дУ��mac��
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

	//ũ����ʱδУ���mac,������ʱ���ε�
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
			case 1:		//���п���ʧ
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//���п�״̬����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//���п�����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//����δ֪����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//�����������
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//ͨѶ����Կ��
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//����δ֪����
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return	E_TRANS_UNKNOW_ERROR;
		}
	}

	//���Ӧ���
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
	//��֯���а�
	memcpy(BankReqPak.TradeCode,TRADE_BANK_TRANS, BANK_TRADE_CODE_LEN);	//д���״���
	getsysdate(BankReqPak.TradeDate);
	getsystime(BankReqPak.TradeTime);
	//�������и��Ľӿ��е�У԰���˺��ֶ�ֻ��10������
	//����������У԰���˺��ֶ�����дУ԰������
	sprintf(BankReqPak.CustAccountNo,"%-10d",atoi(from_pos.CardNo));
	//sprintf(BankReqPak.BankCardNo,"%-20s","1030399110000001042");	//д���п����ֶ�
	sprintf(BankReqPak.BankCardNo,"%-20s",from_pos.BankCardNo);	//д���п����ֶ�
	memcpy(BankReqPak.MercAccount,SCHOOL_ACCOUNT_NO,sizeof(BankReqPak.MercAccount));	//д�̻����ֶ�
	sprintf(BankReqPak.TransMoney,"%-9s",from_pos.TransMoney);	//дת�ʽ���ֶ�
	//ͨ��16���ƴ��䣬Ȼ�����
	hex2dec(from_pos.BankCardPwd,(unsigned char*)BankReqPak.BankCardPwd, 8);
	//memcpy(BankReqPak.BankCardPwd,from_pos.BankCardPwd,sizeof(BankReqPak.BankCardPwd));	//д���п������ֶ�
	sprintf(sSerialno,"%d",serial_no);
	memcpy(BankReqPak.CustSn,sSerialno,strlen(sSerialno));	//дУ԰����ˮ��
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);	//дԺУ����
	BankReqPak.AutoFlag='0';	//д�Զ�������־
	generate_mac((char*)(&BankReqPak),sizeof(BankReqPak),BankReqPak.MAC);//дУ��mac��

	TRACE_BANK_TRANS(&BankReqPak,"send transfer package");

	//�������ݵ����в�ͬʱ�����������ݣ��˴����жϷ��ص�macУ��
	ret=send_to_and_recv_from_bank(BANK_NYYH,(char*)(&BankReqPak),sizeof(BankReqPak),(char*)(&BankAnsPak),sizeof(BankAnsPak),&g_Bank);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return ret;
	}

	TRACE_BANK_TRANS(&BankAnsPak,"receive transfer package");

	//У��mac���ж����н��հ��Ƿ���ȷ
	//Ŀǰ���ж�û��У��mac����������
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
			case 1:		//���п���ʧ
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//���п�״̬����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//���п�����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//����δ֪����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//�����������
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//ͨѶ����Կ��
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//����δ֪����
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
	
	//д���״���
	memcpy( BankReqPak.TradeCode,TRADE_BANK_DETRANS, BANK_TRADE_CODE_LEN);
	//д�������ںͽ���ʱ��
	memcpy(BankReqPak.TradeDate,pNode->TradeDate,sizeof(BankReqPak.TradeDate));
	memcpy(BankReqPak.TradeTime,pNode->TradeTime,sizeof(BankReqPak.TradeTime));
	//�ĳ�У԰������
	sprintf(BankReqPak.CustAccountNo,"%-10d",atoi(pNode->CardNo));
	//д���п����ֶ�
	memcpy(BankReqPak.BankCardNo,pNode->BankCardNo, sizeof(BankReqPak.BankCardNo));
	//д�̻����ֶ�
	memcpy(BankReqPak.MercAccount,SCHOOL_ACCOUNT_NO,sizeof(BankReqPak.MercAccount));
	//дת�ʽ���ֶ�
	sprintf(BankReqPak.TransMoney,"%09d",atoi(pNode->TransMoney));	//дת�ʽ���ֶ�
	//memcpy(BankReqPak.TransMoney,pNode->TransMoney,sizeof BankReqPak.TransMoney);
	//д���п������ֶ�!!!oldpwd? or pwd in shm?
	//memcpy(BankReqPak.BankCardPwd, tradeserial.oldpwd,sizeof(BankReqPak.BankCardPwd));
	//дУ԰����ˮ��!!!serial_no or ReviseSerial_no? f?
	sprintf(sSerialno,"%d",pNode->RecvNo);
	memcpy(BankReqPak.CustSn,sSerialno,strlen(sSerialno));			//������ˮ��
	//дԺУ����
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);
	//дУ��mac��
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
			case 1:		//���п���ʧ
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//���п�״̬����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//���п�����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//����δ֪����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//�����������
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//ͨѶ����Կ��
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//����δ֪����
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

	//д���״���
	memcpy( BankTransPak.TradeCode,TRADE_BANK_CHECKLINE, sizeof(BankTransPak.TradeCode));
	//д�������ںͽ���ʱ��
	getsysdate(BankTransPak.TradeDate);
	getsystime(BankTransPak.TradeTime);
	//дԺУ����
	sprintf(BankTransPak.CustNo,"%-16s",SCHOOL_CODE);
	//дУ��mac��----���մ˴�Ӧ�������лش������Ķ�̬��Կ��mac��Կ���˴��Ĺ�����
	generate_mac((char*)(&BankTransPak),sizeof(BankTransPak),BankTransPak.MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(&BankTransPak,"send checkline package");

	//�������ݵ����в�ͬʱ�����������ݣ��˴����жϷ��ص�macУ��
	ret=send_to_and_recv_from_bank(BANK_NYYH,(char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,&g_Bank);

	if(ret!=0)
	{
		writelog(LOG_ERR,"��������ͨ��ʧ��[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}

	TRACE_BANK_TRANS(&BankTransPak, "recv checkline package");

	//�˴�����˵����mac����ģ����Դ˴�����У��
	/*
	ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,mac);
	ret=memcmp(mac,BankTransPak.MAC,8);
	if(ret!=0)
	{
		writelog(LOG_INFO,"����У�����");
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

	//д���״���---------����˵��ǩ��������Կ��������ʱ��31-->34
	memcpy( BankTransPak.TradeCode,TRADE_BANK_CHGKEY, sizeof(BankTransPak.TradeCode));
	//д�������ںͽ���ʱ��
	getsysdate(BankTransPak.TradeDate);
	getsystime(BankTransPak.TradeTime);
	//дԺУ����
	sprintf(BankTransPak.CustNo,"%-16s",SCHOOL_CODE);
	//дУ��mac��

	ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(&BankTransPak,"send login package");

	//�������ݵ����в�ͬʱ�����������ݣ��˴����жϷ��ص�macУ��
	ret=send_to_and_recv_from_bank(BANK_NYYH,(char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,&g_Bank);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return ret;
	}
	//printf("%d\n",__LINE__);
	TRACE_BANK_TRANS(&BankTransPak,"recv login package");

	//�˴�����˵����mac����ģ����Դ˴�����У��
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

	//д���״���
	memcpy( BankTransPak.TradeCode,TRADE_BANK_LOGOUT, sizeof(BankTransPak.TradeCode));
	//д�������ںͽ���ʱ��
	getsysdate(BankTransPak.TradeDate);
	getsystime(BankTransPak.TradeTime);
	//дԺУ����
	sprintf(BankTransPak.CustNo,"%-16s",SCHOOL_CODE);

	//дУ��mac��----���մ˴�Ӧ�������лش������Ķ�̬��Կ��mac��Կ���˴��Ĺ�����
	generate_mac((char*)(&BankTransPak),sizeof(BankTransPak),BankTransPak.MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(&BankTransPak,"send logout package");

	//�������ݵ����в�ͬʱ�����������ݣ��˴����жϷ��ص�macУ��
	ret=send_to_and_recv_from_bank(BANK_NYYH,(char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,&g_Bank);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}

	TRACE_BANK_TRANS(&BankTransPak,"recv logout package");

	//�˴�����˵����mac����ģ����Դ˴�����У��
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
	//����signal����ֹ����ģʽ��socket

	alarm(delay_time/1000);
	//��������
	ret=SockNode.hSock.ConnectTcp(bank_ip,bank_port);
	if(!ret)
	{	
		alarm(0);
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],bank_ip[%s],port[%d] ",ret,bank_ip,bank_port);
		return E_TRANS_BANK_NETERR;
	}
	alarm(0);

	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pSend,send_len,16);
	
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

	system("sleep 1");

	//�������з�����Ϣ
	ret=	SockNode.hSock.Recv(pRecv,recv_len,delay_time);
	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pRecv,recv_len,16);
	if (ret!=recv_len)
	{
		writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
		return	E_TRANS_BANK_NOANSWER;  // ����ʱ�������ʱ
	}
	SockNode.hSock.Close();
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
	printf("���״���	=[%2.2s]\n",pTransPak->TradeCode);
	printf("���׽��	=[%2.2s]\n",pTransPak->RetCode);
	printf("��������	=[%8.8s]\n",pTransPak->TradeDate);
	printf("����ʱ��	=[%6.6s]\n",pTransPak->TradeTime);
	printf("У԰���ʺ�	=[%10.10s]\n",pTransPak->CustAccountNo);
	printf("���п���	=[%20.20s]\n",pTransPak->BankCardNo);
	printf("�̻��� 		=[%10.10s]\n",pTransPak->MercAccount);
	printf("ת�˽��	=[%9.9s]\n",pTransPak->TransMoney);
	printf("��ǿ����	=[%9.9s]\n",pTransPak->Balance);
	memcpy(a,pTransPak->BankCardPwd,16);
	printf("���п�����	=[%16.16s]\n",pTransPak->BankCardPwd);
	//printf("���п�����	=[%16.16s]\n","****************");
	printf("У԰����ˮ��	=[%8.8s]\n",pTransPak->CustSn);
	printf("������ˮ��	=[%20.20s]\n",pTransPak->BankSn);
	printf("ѧУ����	=[%16.16s]\n",pTransPak->CustNo);
	printf("�Զ�ת�˱�־	=[%d]\n",pTransPak->AutoFlag);
	printf("У��		=[%8.8s]\n",pTransPak->MAC);
	//printf("У��		=[%8.8s]\n","********");

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


