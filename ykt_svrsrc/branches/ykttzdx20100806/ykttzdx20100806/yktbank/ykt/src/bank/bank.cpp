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
#include "txntyp.h"
#include "typdef.h"

//int debug = 3;

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

};



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
	ret=SockNode.hSock.ConnectTcp(bank_ip, bank_port,5);
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

int send_to_and_recv_from_bank_of_boc(char* pSend, int send_len,char* pRecv,int *recv_len,int max_recv_len,int delay_time)
{
	struct SockNode  SockNode,SockNode_rsp;
	CTcpSocket sock;	

	char bank_ip[20]="";
	int bank_port=0;
	int bank_port_rsp=0;
	//int delay_time=0;
	int ret=0;
	char temp[5]="";
	int length=0;

	TIniFile tf;

	if (!tf.Open(TRANS_INI_FILE))
	{
	   writelog(LOG_ERR,"Cann't open ini file,file=[%s]\n",TRANS_INI_FILE);
	   return E_TRANS_UNKNOW_ERROR;
	}

	tf.ReadString("BANK", "BANK_IP", "127.0.0.1", bank_ip,sizeof(bank_ip));
	bank_port=tf.ReadInt("BANK", "BANK_PORT",9001);
	bank_port_rsp=tf.ReadInt("BANK", "BANK_PORT_RSP",9002);

	if(0==delay_time)	delay_time=tf.ReadInt("BANK", "BANK_DELAY_TIME", 3000);
	tf.Close();
	
#ifdef	DEBUG
	//printf("BANK_IP=[%s],BANK_PORT[%d],DELAY_TIME[%d]\n",bank_ip,bank_port,delay_time);
#endif
	writelog(LOG_DEBUG,"connect to bank [%s][%d][%d]",bank_ip,bank_port,bank_port_rsp);
	//��������
	ret=SockNode.hSock.ConnectTcp(bank_ip, bank_port,5);
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
	writelog(LOG_DEBUG,"send to bank success, waiting for responsing!!");
	sleep(1);
	if(!sock.Create())
	{
	      	writelog(LOG_ERR,"sock.Create error!\n");
	      	return	E_TRANS_BANK_NETERR;
	}
	if(!sock.Listen(bank_port_rsp))
	{
	      	writelog(LOG_ERR,"sock.Listen error![%d]",errno);
	      	return	E_TRANS_BANK_NETERR;
	}
	CTcpSocket rcv_sock;
	if(sock.Accept(rcv_sock))
	{
		int rcvlen = rcv_sock.Recv(pRecv,max_recv_len,delay_time);
		if(rcvlen < 0)
		{
		      	writelog(LOG_ERR,"sock.Recv error![%d][%d]\n",rcvlen,errno);
		      	return	E_TRANS_BANK_NOANSWER;
		}
		writelog(LOG_DEBUG,"recv length[%d]",rcvlen);
		*recv_len=rcvlen;
		return 0;
	}
	return E_TRANS_BANK_NOANSWER;


/*

	ret=SockNode_rsp.hSock.Listen(bank_port_rsp);
	if(!ret)
	{
		char msg[256]="";
		SockNode_rsp.hSock.GetLastError(msg);
	      	writelog(LOG_ERR,"Listen bank error,error code is[%d],msg=[%s]!\n",ret,msg);
		return	E_TRANS_BANK_NETERR;
	}
	CTcpSocket rcv_sock;
	ret=SockNode_rsp.hSock.Accept(rcv_sock);
	if(ret)
	{
		int rcvlen = SockNode.hSock.Recv(pRecv,max_recv_len,delay_time);
		if(rcvlen < 0)
		{
			char msg[256]="";
			SockNode_rsp.hSock.GetLastError(msg);
		      	writelog(LOG_ERR,"Receive from bank error,error code is[%d],msg=[%s]!\n",ret,msg);
			return	E_TRANS_BANK_NETERR;
		}
		*recv_len=rcvlen;
		SockNode.hSock.Close();
		SockNode_rsp.hSock.Close();
		rcv_sock.Close();
		return 0;
	}
	return -2;
	*/
}

//�жϸ��豸�Ƿ�ǩ����
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

int BOC_RET_NO(char ret_code[3])
{
	char rt_code[3]="";
	strncpy(rt_code,ret_code,sizeof(rt_code)-1);
	if(strncmp(rt_code,"98",sizeof(rt_code)-1)==0) return 109001;
	else if(strncmp(rt_code,"98",sizeof(rt_code)-1)==0) return 109001;  
	else if(strncmp(rt_code,"99",sizeof(rt_code)-1)==0) return 109002;  
	else if(strncmp(rt_code,"01",sizeof(rt_code)-1)==0) return 109003;  
	else if(strncmp(rt_code,"02",sizeof(rt_code)-1)==0) return 109004;  
	else if(strncmp(rt_code,"03",sizeof(rt_code)-1)==0) return 109005;  
	else if(strncmp(rt_code,"04",sizeof(rt_code)-1)==0) return 109006;  
	else if(strncmp(rt_code,"05",sizeof(rt_code)-1)==0) return 109007;  
	else if(strncmp(rt_code,"06",sizeof(rt_code)-1)==0) return 109008;  
	else if(strncmp(rt_code,"07",sizeof(rt_code)-1)==0) return 109009;  
	else if(strncmp(rt_code,"08",sizeof(rt_code)-1)==0) return 109010;  
	else if(strncmp(rt_code,"09",sizeof(rt_code)-1)==0) return 109011;  
	else if(strncmp(rt_code,"10",sizeof(rt_code)-1)==0) return 109012;  
	else if(strncmp(rt_code,"0A",sizeof(rt_code)-1)==0) return 109013;  
	else if(strncmp(rt_code,"0B",sizeof(rt_code)-1)==0) return 109014;  
	else if(strncmp(rt_code,"0C",sizeof(rt_code)-1)==0) return 109015;  
	else if(strncmp(rt_code,"0D",sizeof(rt_code)-1)==0) return 109016;  
	else if(strncmp(rt_code,"0E",sizeof(rt_code)-1)==0) return 109017;  
	else if(strncmp(rt_code,"0F",sizeof(rt_code)-1)==0) return 109018;  
	else if(strncmp(rt_code,"0G",sizeof(rt_code)-1)==0) return 109019;  
	else if(strncmp(rt_code,"11",sizeof(rt_code)-1)==0) return 109020;  
	else if(strncmp(rt_code,"12",sizeof(rt_code)-1)==0) return 109021;  
	else if(strncmp(rt_code,"13",sizeof(rt_code)-1)==0) return 109022;  
	else if(strncmp(rt_code,"14",sizeof(rt_code)-1)==0) return 109023;  
	else if(strncmp(rt_code,"15",sizeof(rt_code)-1)==0) return 109024;  
	else if(strncmp(rt_code,"16",sizeof(rt_code)-1)==0) return 109025;  
	else if(strncmp(rt_code,"17",sizeof(rt_code)-1)==0) return 109026;  
	else if(strncmp(rt_code,"18",sizeof(rt_code)-1)==0) return 109027;  
	else if(strncmp(rt_code,"19",sizeof(rt_code)-1)==0) return 109028;  
	else if(strncmp(rt_code,"20",sizeof(rt_code)-1)==0) return 109029;  
	else if(strncmp(rt_code,"21",sizeof(rt_code)-1)==0) return 109030;  
	else if(strncmp(rt_code,"22",sizeof(rt_code)-1)==0) return 109031;  
	else if(strncmp(rt_code,"23",sizeof(rt_code)-1)==0) return 109032;  
	else if(strncmp(rt_code,"24",sizeof(rt_code)-1)==0) return 109033;  
	else if(strncmp(rt_code,"25",sizeof(rt_code)-1)==0) return 109034;  
	else if(strncmp(rt_code,"26",sizeof(rt_code)-1)==0) return 109035;  
	else if(strncmp(rt_code,"27",sizeof(rt_code)-1)==0) return 109036;  
	else if(strncmp(rt_code,"28",sizeof(rt_code)-1)==0) return 109037;  
	else if(strncmp(rt_code,"29",sizeof(rt_code)-1)==0) return 109038;  
	else if(strncmp(rt_code,"30",sizeof(rt_code)-1)==0) return 109039;  
	else if(strncmp(rt_code,"31",sizeof(rt_code)-1)==0) return 109040;  
	else if(strncmp(rt_code,"32",sizeof(rt_code)-1)==0) return 109041;  
	else if(strncmp(rt_code,"33",sizeof(rt_code)-1)==0) return 109042;  
	else if(strncmp(rt_code,"34",sizeof(rt_code)-1)==0) return 109043;  
	else if(strncmp(rt_code,"35",sizeof(rt_code)-1)==0) return 109044;  
	else if(strncmp(rt_code,"36",sizeof(rt_code)-1)==0) return 109045;  
	else if(strncmp(rt_code,"37",sizeof(rt_code)-1)==0) return 109046;  
	else if(strncmp(rt_code,"38",sizeof(rt_code)-1)==0) return 109047;  
	else if(strncmp(rt_code,"39",sizeof(rt_code)-1)==0) return 109048;  
	else if(strncmp(rt_code,"40",sizeof(rt_code)-1)==0) return 109049;  
	else if(strncmp(rt_code,"41",sizeof(rt_code)-1)==0) return 109050;  
	else if(strncmp(rt_code,"42",sizeof(rt_code)-1)==0) return 109051;  
	else if(strncmp(rt_code,"43",sizeof(rt_code)-1)==0) return 109052;  
	else if(strncmp(rt_code,"44",sizeof(rt_code)-1)==0) return 109053;  
	else if(strncmp(rt_code,"45",sizeof(rt_code)-1)==0) return 109054;  
	else if(strncmp(rt_code,"46",sizeof(rt_code)-1)==0) return 109055;  
	else if(strncmp(rt_code,"A9",sizeof(rt_code)-1)==0) return 109056;  
	else if(strncmp(rt_code,"S1",sizeof(rt_code)-1)==0) return 109057;  
	else if(strncmp(rt_code,"S2",sizeof(rt_code)-1)==0) return 109058;  
	else if(strncmp(rt_code,"S3",sizeof(rt_code)-1)==0) return 109059;  
	else if(strncmp(rt_code,"S4",sizeof(rt_code)-1)==0) return 109060;  
	else if(strncmp(rt_code,"S5",sizeof(rt_code)-1)==0) return 109061;  
	else if(strncmp(rt_code,"R0",sizeof(rt_code)-1)==0) return 109062;  
	else if(strncmp(rt_code,"R1",sizeof(rt_code)-1)==0) return 109063;  
	else if(strncmp(rt_code,"R2",sizeof(rt_code)-1)==0) return 109064;  
	else if(strncmp(rt_code,"R3",sizeof(rt_code)-1)==0) return 109065;  
	else if(strncmp(rt_code,"R4",sizeof(rt_code)-1)==0) return 109066;  
	else if(strncmp(rt_code,"W3",sizeof(rt_code)-1)==0) return 109067;	 
	else if(strncmp(rt_code,"W4",sizeof(rt_code)-1)==0) return 109068;  
	else if(strncmp(rt_code,"W1",sizeof(rt_code)-1)==0) return 109069;  
	else if(strncmp(rt_code,"W5",sizeof(rt_code)-1)==0) return 109070;  
	else if(strncmp(rt_code,"W2",sizeof(rt_code)-1)==0) return 109071;  
	else if(strncmp(rt_code,"W8",sizeof(rt_code)-1)==0) return 109072;  
	else if(strncmp(rt_code,"61",sizeof(rt_code)-1)==0) return 109073;  
	else if(strncmp(rt_code,"62",sizeof(rt_code)-1)==0) return 109074;  
	else if(strncmp(rt_code,"63",sizeof(rt_code)-1)==0) return 109075;  
	else if(strncmp(rt_code,"64",sizeof(rt_code)-1)==0) return 109076;  
	else if(strncmp(rt_code,"65",sizeof(rt_code)-1)==0) return 109077;  
	else if(strncmp(rt_code,"66",sizeof(rt_code)-1)==0) return 109078;  
	else if(strncmp(rt_code,"67",sizeof(rt_code)-1)==0) return 109079;  
	else if(strncmp(rt_code,"68",sizeof(rt_code)-1)==0) return 109080;  
	else if(strncmp(rt_code,"69",sizeof(rt_code)-1)==0) return 109081;  
	else if(strncmp(rt_code,"80",sizeof(rt_code)-1)==0) return 109082;  
	else if(strncmp(rt_code,"70",sizeof(rt_code)-1)==0) return 109083;  
	else if(strncmp(rt_code,"71",sizeof(rt_code)-1)==0) return 109084;  
	else if(strncmp(rt_code,"72",sizeof(rt_code)-1)==0) return 109085;  
	else if(strncmp(rt_code,"73",sizeof(rt_code)-1)==0) return 109086;  
	else if(strncmp(rt_code,"74",sizeof(rt_code)-1)==0) return 109087;  
	else if(strncmp(rt_code,"75",sizeof(rt_code)-1)==0) return 109088;  
	else if(strncmp(rt_code,"76",sizeof(rt_code)-1)==0) return 109089;  
	else if(strncmp(rt_code,"M1",sizeof(rt_code)-1)==0) return 109090;  
	else if(strncmp(rt_code,"M2",sizeof(rt_code)-1)==0) return 109091;  
	else if(strncmp(rt_code,"M3",sizeof(rt_code)-1)==0) return 109092;  
	else if(strncmp(rt_code,"M4",sizeof(rt_code)-1)==0) return 109093;  
	else if(strncmp(rt_code,"M5",sizeof(rt_code)-1)==0) return 109094;  
	else if(strncmp(rt_code,"M6",sizeof(rt_code)-1)==0) return 109095;  
	else if(strncmp(rt_code,"M7",sizeof(rt_code)-1)==0) return 109096;  
	else if(strncmp(rt_code,"M8",sizeof(rt_code)-1)==0) return 109097;  
	else if(strncmp(rt_code,"M9",sizeof(rt_code)-1)==0) return 109098;  
	else if(strncmp(rt_code,"M0",sizeof(rt_code)-1)==0) return 109099;  
	else if(strncmp(rt_code,"MA",sizeof(rt_code)-1)==0) return 109100;  
	else if(strncmp(rt_code,"MB",sizeof(rt_code)-1)==0) return 109101;  
	else if(strncmp(rt_code,"MC",sizeof(rt_code)-1)==0) return 109102;  
	else if(strncmp(rt_code,"MD",sizeof(rt_code)-1)==0) return 109103;  
	else if(strncmp(rt_code,"F1",sizeof(rt_code)-1)==0) return 109104;  
	else if(strncmp(rt_code,"F2",sizeof(rt_code)-1)==0) return 109105;  
	else if(strncmp(rt_code,"F3",sizeof(rt_code)-1)==0) return 109106;  
	else if(strncmp(rt_code,"W7",sizeof(rt_code)-1)==0) return 109107;  
	else if(strncmp(rt_code,"F4",sizeof(rt_code)-1)==0) return 109108;  
	else if(strncmp(rt_code,"F5",sizeof(rt_code)-1)==0) return 109109;  
	else if(strncmp(rt_code,"F6",sizeof(rt_code)-1)==0) return 109110;  
	else if(strncmp(rt_code,"F7",sizeof(rt_code)-1)==0) return 109111;  
	else if(strncmp(rt_code,"F8",sizeof(rt_code)-1)==0) return 109112;  
	else if(strncmp(rt_code,"FA",sizeof(rt_code)-1)==0) return 109113;  
	else if(strncmp(rt_code,"FB",sizeof(rt_code)-1)==0) return 109114;  
	else if(strncmp(rt_code,"FC",sizeof(rt_code)-1)==0) return 109115;  
	else if(strncmp(rt_code,"FD",sizeof(rt_code)-1)==0) return 109116;  
	else if(strncmp(rt_code,"C1",sizeof(rt_code)-1)==0) return 109117;  
	else if(strncmp(rt_code,"C2",sizeof(rt_code)-1)==0) return 109118;  
	else if(strncmp(rt_code,"X1",sizeof(rt_code)-1)==0) return 109119;  
	else if(strncmp(rt_code,"X4",sizeof(rt_code)-1)==0) return 109120;  
	else if(strncmp(rt_code,"R8",sizeof(rt_code)-1)==0) return 109121;  
	else if(strncmp(rt_code,"W6",sizeof(rt_code)-1)==0) return 109122;  
	else if(strncmp(rt_code,"52",sizeof(rt_code)-1)==0) return 109123;  
	else if(strncmp(rt_code,"Z1",sizeof(rt_code)-1)==0) return 109124;  
	else if(strncmp(rt_code,"Z3",sizeof(rt_code)-1)==0) return 109125;  
	else if(strncmp(rt_code,"Z0",sizeof(rt_code)-1)==0) return 109126;  
	else if(strncmp(rt_code,"Z2",sizeof(rt_code)-1)==0) return 109127;  
	else if(strncmp(rt_code,"74",sizeof(rt_code)-1)==0) return 109128;  
	else if(strncmp(rt_code,"69",sizeof(rt_code)-1)==0) return 109129;  
	else if(strncmp(rt_code,"T0",sizeof(rt_code)-1)==0) return 109130;  
	else if(strncmp(rt_code,"Z5",sizeof(rt_code)-1)==0) return 109131;  
	else if(strncmp(rt_code,"Z6",sizeof(rt_code)-1)==0) return 109132;  
	else if(strncmp(rt_code,"Z7",sizeof(rt_code)-1)==0) return 109133;	 
	else if(strncmp(rt_code,"P4",sizeof(rt_code)-1)==0) return 109134;  
	else if(strncmp(rt_code,"PX",sizeof(rt_code)-1)==0) return 109135;  
	else if(strncmp(rt_code,"P6",sizeof(rt_code)-1)==0) return 109136;  
	else if(strncmp(rt_code,"Z9",sizeof(rt_code)-1)==0) return 109137;  
	else if(strncmp(rt_code,"Z8",sizeof(rt_code)-1)==0) return 109138;  
	else if(strncmp(rt_code,"ZA",sizeof(rt_code)-1)==0) return 109139;  
	else if(strncmp(rt_code,"ZC",sizeof(rt_code)-1)==0) return 109140;  
	else if(strncmp(rt_code,"ZZ",sizeof(rt_code)-1)==0) return 109141;  
	else if(strncmp(rt_code,"T1",sizeof(rt_code)-1)==0) return 109142;  
	else if(strncmp(rt_code,"T2",sizeof(rt_code)-1)==0) return 109143;  
	else if(strncmp(rt_code,"P0",sizeof(rt_code)-1)==0) return 109144;  
	else if(strncmp(rt_code,"P1",sizeof(rt_code)-1)==0) return 109145;  
	else if(strncmp(rt_code,"P2",sizeof(rt_code)-1)==0) return 109146;  
	else if(strncmp(rt_code,"P3",sizeof(rt_code)-1)==0) return 109147;  
	else if(strncmp(rt_code,"P5",sizeof(rt_code)-1)==0) return 109148;  
	else if(strncmp(rt_code,"P7",sizeof(rt_code)-1)==0) return 109149;  
	else if(strncmp(rt_code,"P8",sizeof(rt_code)-1)==0) return 109150;  
	else if(strncmp(rt_code,"P9",sizeof(rt_code)-1)==0) return 109151;  
	else if(strncmp(rt_code,"Q0",sizeof(rt_code)-1)==0) return 109152;  
	else if(strncmp(rt_code,"Q1",sizeof(rt_code)-1)==0) return 109153;  
	else if(strncmp(rt_code,"Q2",sizeof(rt_code)-1)==0) return 109154;  
	else if(strncmp(rt_code,"Q3",sizeof(rt_code)-1)==0) return 109155;  
	else if(strncmp(rt_code,"Q4",sizeof(rt_code)-1)==0) return 109156;  
	else if(strncmp(rt_code,"Q5",sizeof(rt_code)-1)==0) return 109157;  
	else if(strncmp(rt_code,"Q8",sizeof(rt_code)-1)==0) return 109158;  
	else if(strncmp(rt_code,"Q9",sizeof(rt_code)-1)==0) return 109159;  
	else if(strncmp(rt_code,"ME",sizeof(rt_code)-1)==0) return 109160;  
	else if(strncmp(rt_code,"N1",sizeof(rt_code)-1)==0) return 109161;  
	else if(strncmp(rt_code,"N2",sizeof(rt_code)-1)==0) return 109162;  
	else if(strncmp(rt_code,"N3",sizeof(rt_code)-1)==0) return 109163;  
	else if(strncmp(rt_code,"N4",sizeof(rt_code)-1)==0) return 109164;  
	else if(strncmp(rt_code,"77",sizeof(rt_code)-1)==0) return 109165;  
	else if(strncmp(rt_code,"0B",sizeof(rt_code)-1)==0) return 109166;  
	else if(strncmp(rt_code,"81",sizeof(rt_code)-1)==0) return 109167;  
	else return 109000;
}


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
int Do_DeTrans  ( BANK_TRANS_REQUEST *pBankTrans )
{
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
int Do_Compare( BANK_TRANS_REQUEST *pBankTrans )
{
	char mac_key[32]="";
	char mac[16]="";
	int ret;

	BANK_TRANS_REQUEST BankTransPak;

	memcpy(mac_key,STATIC_KEY,sizeof(mac_key));
	memset(&BankTransPak,0,BANK_TRANS_PACKLEN);

	//д���״���
	memcpy( BankTransPak.TradeCode,TRADE_BANK_COMP, sizeof(BankTransPak.TradeCode));
	//д�������ںͽ���ʱ��
	getsysdate(BankTransPak.TradeDate);
	getsystime(BankTransPak.TradeTime);
	//дԺУ����
	sprintf(BankTransPak.CustNo,"%-16s",SCHOOL_CODE);
	//дУ��mac��

	//дУ��mac��----���մ˴�Ӧ�������лش������Ķ�̬��Կ��mac��Կ���˴��Ĺ�����
	generate_mac((char*)(&BankTransPak),sizeof(BankTransPak),BankTransPak.MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(&BankTransPak,"send compare package");

	//�������ݵ����в�ͬʱ�����������ݣ��˴����жϷ��ص�macУ��
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

	ret=GetLogicDate(logicdate);								//ҵ������
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
	//���û�������
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
		//��֪��Ϊʲô������Ҫ��һ�����ܶ�?
		if((cnt+2)%2==0)	continue;
		//��ʼ���и�ֵ
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
	//��ȡ�����ļ��������رն����ļ����ύ����
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

	//��ʼ���ж���
	cnt=0;

	//������
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
		//���Ӷ��ڷ�01������Ľ��׵��ų�(����:����)
		if(1!=atoi(bank_comp.tx_code)) 	{continue;}
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

	ret=GetLogicDate(logicdate);								//ҵ������
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
	//���û�������
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
		//��֪��Ϊʲô������Ҫ��һ�����ܶ�?
		if((cnt+2)%2==0)	continue;
		//��ʼ���и�ֵ
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
	//��ȡ�����ļ��������رն����ļ����ύ����
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

	//��ʼ���ж���
	cnt=0;

	//������
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
		//��ˮ����û�м�¼�����
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
		//��ˮ���д��ڣ�����û�����˵����
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

	//ϵͳ���ڽ��㣬�������ɻ����ļ�
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
	fprintf(fp,"%-14.14s",trans_head.rmb_batch_no);		//�������

	memcpy(trans_head.rmb_start_seq,"000000",6);
	fprintf(fp,"%-6.6s",trans_head.rmb_start_seq);			//��000000

	trans_head.rmb_acc_status='0';
	fprintf(fp,"%c",trans_head.rmb_acc_status);			//����״̬����0��

	trans_head.rmb_chk_status='2';
	fprintf(fp,"%c",trans_head.rmb_chk_status);			//���״̬����2��

	sprintf(trans_head.rmb_total_amount,"%-13d",int(ho_Fee_Change*100));
	fprintf(fp,"%-13.13s",trans_head.rmb_total_amount);		//�ܽ��(11λ����2λС������С����)

	sprintf(trans_head.rmb_total_num,"%-6d",ho_OpCount);
	fprintf(fp,"%-6.6s",trans_head.rmb_total_num);			//�ܱ���

	fprintf(fp,"%-13.13s",trans_head.rmb_enter_amount);	//���ʽ��

	fprintf(fp,"%-6.6s",trans_head.rmb_enter_num);			//���ʱ���

	sprintf(trans_head.rmb_unit_name,"%-40s",UNIT_NAME);
	fprintf(fp,"%-40.40s",trans_head.rmb_unit_name);		//��λ����
#ifdef DEBUG
	writelog(LOG_ALERT,"trans_head.rmb_unit_name=[%s]",trans_head.rmb_unit_name);
#endif

	strcpy(trans_head.rmb_unit_account,UNIT_ACCOUNT);
	//sprintf(trans_head.rmb_unit_account,"%-20s"UNIT_ACCOUNT);
	fprintf(fp,"%-20.20s",trans_head.rmb_unit_account);		//��λ�ʺ�
#ifdef DEBUG
	writelog(LOG_ALERT,"trans_head.rmb_unit_account=[%s]",trans_head.rmb_unit_account);
#endif

	memcpy(trans_head.rmb_apply_date,getsysdate(NULL),sizeof(trans_head.rmb_apply_date));
	fprintf(fp,"%-8.8s",trans_head.rmb_apply_date);			//�����������ڣ��������ڣ�

	//memcpy(trans_head.rmb_send_date,trans_head.rmb_apply_date,sizeof(trans_head.rmb_apply_date));
	memcpy(trans_head.rmb_send_date,getsystime(NULL),sizeof(trans_head.rmb_send_date));
	fprintf(fp,"%-8.8s",trans_head.rmb_send_date);			//�ϴ����ڣ��������ڣ�

#ifdef DEBUG
	printf("[%14.14s]\n",trans_head.rmb_batch_no      ); 	//�������
	printf("[%6.6s]\n",trans_head.rmb_start_seq      ); 		//��000000
	printf("[%c]\n",trans_head.rmb_acc_status        ); 		//����״̬����0��
	printf("[%c]\n",trans_head.rmb_chk_status        ); 		//���״̬����2��
	printf("[%13.13s]\n",trans_head.rmb_total_amount  ); 	//�ܽ��(11λ����2λС������С����)
	printf("[%6.6s]\n",trans_head.rmb_total_num      ); 	//�ܱ���
	printf("[%13.13s]\n",trans_head.rmb_enter_amount ); 	//���ʽ��(11λ����2λС������С����)
	printf("[%6.6s]\n",trans_head.rmb_enter_num     ); 	//���ʱ���
	printf("[%40.40s]\n",trans_head.rmb_unit_name    ); 	//��λ����
	printf("[%20.20s]\n",trans_head.rmb_unit_account  ); 	//��λ�ʺ�
	printf("[%8.8s]\n",trans_head.rmb_apply_date     ); 	//�����������ڣ��������ڣ�
	printf("[%8.8s]\n",trans_head.rmb_send_date     );  	//�ϴ����ڣ��������ڣ�
#endif

	//д�뻮���ļ�
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
		//��ʼ����������
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
				else		break;	//ѭ����¼����
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
	//��ʼ���з������㱨��
	memcpy( pBankTrans->TradeCode,TRADE_BANK_BALANCE, sizeof(pBankTrans->TradeCode));	//д���״���
	//д�������ںͽ���ʱ��
	getsysdate(pBankTrans->TradeDate);
	getsystime(pBankTrans->TradeTime);
	//дԺУ����
	sprintf(pBankTrans->CustNo,"%-16s",SCHOOL_CODE);
	//д���п���-�˴�Լ��Ϊ�����ļ���
	sprintf(pBankTrans->BankCardNo,"%8.8s",getsysdate(NULL));
	//дУ��mac��
	//дУ��mac��----���մ˴�Ӧ�������лش������Ķ�̬��Կ��mac��Կ���˴��Ĺ�����
	generate_mac((char*)pBankTrans,sizeof(pBankTrans),pBankTrans->MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(pBankTrans,"send transfer package");

	//�������ݵ����в�ͬʱ�����������ݣ��˴����жϷ��ص�macУ��
	ret=send_to_and_recv_from_bank((char*)pBankTrans,BANK_TRANS_PACKLEN, (char*)pBankTrans,BANK_TRANS_PACKLEN,delay_time);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}
	TRACE_BANK_TRANS(pBankTrans,"recv transfer package");

	//ũ����ʱδУ���mac,������ʱ���ε�

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

//ͨ�ú�������

