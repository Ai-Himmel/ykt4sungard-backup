/* ----------------------------------------------------------
 * �������ƣ�bank.cpp
 * �������ڣ�2005-03-10 14:58
 * �������ߣ�����
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�����ת�ʸ��ֽ��׺���ʵ��
 * ----------------------------------------------------------
 * �޸�����: 2005-03-25
 * �޸���Ա: ������
 * �޸�����: ������ʹ����Կ�ɾ�̬��Կ�ĳƶ�̬��Կ������gen_mac����
 * �汾��Ϣ��1.0.1.0
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

};

/****************************************************
���ж˽��״�����
lq, 20050310����transinfo.cpp�ƹ���������bu��ش�������
!! ��ȡ����������ʱ��һ��Ҫ��ȡ�ź���
	p(semid);
	operations...;
	v(semid)
������������ź������ƵĴ��뷶Χ
������ж�ͬһ�˻������в������ƣ����ź�������������������
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

//�����·�������
int Do_CheckLine( BANK_TRANS_REQUEST *pBankTrans )
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
	ret=send_to_and_recv_from_bank((char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,0);

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
	memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	return 0;

}

//ǩ�����״������
int Do_Login  (BANK_TRANS_REQUEST *pBankTrans)
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
	ret=send_to_and_recv_from_bank((char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,0);
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
	memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	writelog(LOG_INFO,"Congratulation,login to bank succeed!");
	return 0;

}

//ǩ�˽��״������
int Do_Quit	( BANK_TRANS_REQUEST *pBankTrans )
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
	ret=send_to_and_recv_from_bank((char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,0);
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
	memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	writelog(LOG_INFO,"Congratulation,logout from bank succeed!");
	return 0;

}

//�Զ�ת�˽��״������
int Do_AutoTrans  ( BANK_TRANS_REQUEST *pBankTrans )
{

	return 0;

}

/** �������״������
�ٶ�pBankTrans���Ѿ�����˽�������(��bankguard.cpp�����)
���з��ؽ���Դ����pBankTrans��
*/
int Do_DeTrans  (T_t_tif_tradeserial *tradeserial,BANK_TRANS_REQUEST *pBankTrans )
{
	//TODO: ���ͳ�����¼.ע����ո�
	writelog(LOG_INFO,"��������", ret);
	//��֯���а�
	//memset(pBankTrans, ' ', sizeof(bank_trans));
	//д���״���
	strnscpy( pBankTrans->TradeCode,TRADE_BANK_DETRANS, BANK_TRADE_CODE_LEN);
	//д�������ںͽ���ʱ��
	strnscpy(pBankTrans->TradeDate,tradeserial.operate_date,sizeof(pBankTrans->TradeDate));
	strnscpy(pBankTrans->TradeTime,tradeserial.operate_time,sizeof(pBankTrans->TradeTime));
	//�ĳ�У԰������
	sprintf(pBankTrans->CustAccountNo,"%-10d",tradeserial.card_id);
	//д���п����ֶ�
	strnscpy(pBankTrans->BankCardNo,tradeserial.b_act_id, sizeof(pBankTrans->BankCardNo));
	//д�̻����ֶ�
	strnscpy(pBankTrans->MercAccount,SCHOOL_ACCOUNT_NO,sizeof(pBankTrans->MercAccount));
	//дת�ʽ���ֶ�
	sprintf(pBankTrans->TransMoney,"%-9d", int(tradeserial.trade_fee));
	//д���п������ֶ�!!!oldpwd? or pwd in shm?
	strnscpy(pBankTrans->BankCardPwd, tradeserial.oldpwd,sizeof(pBankTrans->BankCardPwd));
	//дУ԰����ˮ��!!!serial_no or ReviseSerial_no? f?
	sprintf(pBankTrans->CustSn,"%-8d",tradeserial.other_seri_no);
	//sprintf(bank_trans.BankSn,
	//дԺУ����
	sprintf(pBankTrans->CustNo,"%-16s",SCHOOL_CODE);
	//дУ��mac��
	generate_mac((char*)pBankTrans,BANK_TRANS_PACKLEN,pBankTrans->MAC);

	BANK_TRANS_REQUEST BankTransPak;
	memcpy((void*)&BankTransPak, (void*)pBankTrans, BANK_TRANS_PACKLEN);

	//����Ҫ������Ԥ����
	TRACE_BANK_TRANS(&BankTransPak,"send detrans package");

	int ret = send_to_and_recv_from_bank((char*)&BankTransPak, BANK_TRANS_PACKLEN, (char*)&BankTransPak, BANK_TRANS_PACKLEN,0);

	if(ret != 0)
		return ret;
	TRACE_BANK_TRANS(&BankTransPak,"recv detrans package");

	memcpy((char*)pBankTrans, (char*)&BankTransPak, BANK_TRANS_PACKLEN);

	// ������Ӧ�ô������з��ص�BankSn

	return 0;
}

//���ʹ���
//ͨ�ú�������

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
	//��������
	ret=SockNode.hSock.ConnectTcp(bank_ip, bank_port,30);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],bank_ip[%s],port[%d] ",ret,bank_ip,bank_port);
		return E_TRANS_BANK_NETERR;
	}

	//�������ݵ�����
	ret=SockNode.hSock.Send(pSend, send_len);
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
		writelog(LOG_ERR,"Send to bank error,ret = %ret, error code is [%d] ",ret, errno);
		return E_TRANS_BANK_NETERR;
	}
	else if (0==ret)
	{
		// ��Ӧ�ó����������
	      	writelog(LOG_ERR,"Send to bank error��CTcpSocket.Send should not return this error,error code is[%d]!\n",errno);
	      	return	E_TRANS_BANK_NETERR;
	}

	system("sleep 1");

	//�������з�����Ϣ
	ret=	SockNode.hSock.Recv(pRecv,recv_len,delay_time);
	if (ret!=recv_len)
	{
		writelog(LOG_ERR,"Receive from bank error,ret= %ret, error code is [%d] ",ret, errno);
		return	E_TRANS_BANK_NOANSWER;  // ����ʱ�������ʱ
	}
	SockNode.hSock.Close();

	return 0;
}


