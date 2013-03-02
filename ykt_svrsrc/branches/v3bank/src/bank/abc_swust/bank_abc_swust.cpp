/* ----------------------------------------------------------
 * �������ƣ�bank_abc_yntv.cpp
  * �������ڣ�2011-06-20
 * �������ߣ������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����ƴ�ũҵ���нӿ�
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "shem.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_abc_swust.h"
#include "tcp.h"
#include "d3des.h"


#define BANK_LOGIN	(shm[1]==1)			// �Ƿ�ǩ��

static void GenPub(char *msgpub,char *tradecode,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf,"TRADE_ID",tradecode);			//���״��루�̶����� 4 λ�ַ���
	if(rPack->lvol6)
		AddXmlItemInt(buf,"DEV_ID",rPack->lvol6);			//�豸�ţ���󳤶� 15 λ�ַ���
	else
		AddXmlItemStr(buf,"DEV_ID","AUTO001");			//�豸�ţ���󳤶� 15 λ�ַ���
	AddXmlItemStr(buf, "TELLER", "AUTO0001");			//�����ţ���󳤶� 15 λ�ַ���		
	AddXmlItemStr(buf,"BANK_ID","03");				//���б��		
	AddXmlItemStr(msgpub, "PUB", buf);						
}

// ��ֵ����
static void GenMsgBodyTrans(char *msgbody,ST_PACK *rPack)	
{
	char buf[1024]="";
	AddXmlItemStr(buf, "COM_ID", SCHOOLCODE);					//��˾���루��󳤶�8λ��
	AddXmlItemStr(buf, "DPT_ID", "");								//���ű��루��󳤶�15λ��
	AddXmlItemStr(buf, "CUST_ID", rPack->sphone);					//�ͻ���ţ���󳤶�20λ��--һ��ͨѧ����
	AddXmlItemStr(buf, "CO_NUM",rPack->sholder_ac_no);			//������ţ���󳤶� 20 λ��
	AddXmlItemStr(buf, "ACC",rPack->scust_limit2);					//��/�ʻ�����
	AddXmlItemInt(buf, "MONEY_TRADE",D2I(rPack->damt0*100));		//֧�����(�17���䳤����ȷ���֣�û��С��)
	AddXmlItemStr(buf, "TRADE_SEQ",rPack->sholder_ac_no);			//��˾��������ˮ�ţ���󳤶�20λ��
	
	AddXmlItemStr(buf, "TRADE_DATE",rPack->sdate0);				//�������ڣ� YYYYMMDD �̶����� 8 λ��
	AddXmlItemStr(msgbody, "IN", buf);							//ȫ������MsgBody ��	
}

// ��������
static void GenMsgBodyTransRev(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "COM_ID", SCHOOLCODE);					//��˾���루��󳤶�8λ��
	AddXmlItemStr(buf, "DPT_ID", "");								//���ű��루��󳤶�15λ��
	AddXmlItemStr(buf, "TRADE_SEQ_OLD",rPack->sholder_ac_no);		//ԭ��˾��������ˮ��
	AddXmlItemInt(buf, "MONEY_TRADE",D2I(rPack->damt0*100));		//֧�����(�17���䳤����ȷ���֣�û��С��)
	AddXmlItemStr(buf, "TRADE_SEQ",rPack->sholder_ac_no);			//��˾��������ˮ�ţ���󳤶�20λ��
	AddXmlItemStr(buf, "TRADE_DATE",rPack->sdate0);				//�������ڣ� YYYYMMDD �̶����� 8 λ��
	AddXmlItemStr(msgbody, "IN", buf);							//ȫ������MsgBody ��	
}

// ��ѯ����
static void GenMsgBodyQuery(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "CUST_ID", rPack->sphone);					//�ͻ���ţ���󳤶�20λ��--һ��ͨѧ����
	AddXmlItemStr(buf, "COM_ID", SCHOOLCODE);					//��˾���루��󳤶�8λ��
	AddXmlItemStr(buf, "DPT_ID", "");								//���ű��루��󳤶�15λ��
	AddXmlItemStr(buf, "ACC","");								//�ʺţ���ֵ����ʱ���ã�
	AddXmlItemStr(msgbody, "IN", buf);							//ȫ������MsgBody ��	
}

//ǩ��
static void GenMsgBodySign(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "COM_ID", SCHOOLCODE);					//��˾���루��󳤶�8λ��
	AddXmlItemStr(buf, "DPT_ID", "");								//���ű��루��󳤶�15λ��
	AddXmlItemStr(buf, "DATE", rPack->sdate0);				

	AddXmlItemStr(msgbody, "IN", buf);							//ȫ������MsgBody ��	
}

// ����������
static void GenMsgBodyBind(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "CUST_ID", rPack->spager);					//�ͻ���ţ���󳤶�20λ��--һ��ͨѧ����
	AddXmlItemStr(buf, "COM_ID", SCHOOLCODE);					//��˾���루��󳤶�8λ��
	AddXmlItemStr(buf, "DPT_ID", "");								//���ű��루��󳤶�15λ��
	AddXmlItemStr(buf, "CUST_NAME",rPack->sall_name);				//�ͻ���������󳤶�50λ��
	AddXmlItemStr(buf, "PASS_ID",rPack->semail2);					//���֤�ţ��̶�����15��18λ��
	AddXmlItemStr(buf, "ACC",rPack->scard0);						//��/�ʻ�����
	AddXmlItemStr(buf, "TRADE_SEQ",rPack->sholder_ac_no);			//��˾��������ˮ�ţ���󳤶�20λ��

	AddXmlItemStr(msgbody, "IN", buf);							//ȫ������MsgBody ��	
}

static void GenMsgBodyCheckAcc(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "TRADE_DATE", rPack->sdate0);			
	AddXmlItemStr(buf, "COM_ID", SCHOOLCODE);					//��˾���루��󳤶�8λ��

	AddXmlItemStr(msgbody, "IN", buf);							//ȫ������MsgBody ��	
}
static void GenIn(char *msgIn,char *tradecode,ST_PACK *rPack)
{
		if(memcmp( BANK_SIGN_IN,tradecode,4)==0)
			GenMsgBodySign(msgIn,rPack);
		
		else if(memcmp( BIND_BANK,tradecode,4)==0
			||memcmp( UN_BIND_BANK,tradecode,4)==0)
			GenMsgBodyBind(msgIn,rPack);
	
		else if(memcmp( TRANS_CODE,tradecode,4)==0)
			GenMsgBodyTrans(msgIn,rPack);

		else if(memcmp( REV_TRANS_CODE,tradecode,4)==0)
			GenMsgBodyTransRev(msgIn,rPack);
		
		else if(memcmp( QUERY_BALA,tradecode,4)==0)
			GenMsgBodyQuery(msgIn,rPack);
		else if(memcmp( BANK_ACCCHECK,tradecode,4)==0)
			GenMsgBodyCheckAcc(msgIn,rPack);
		else
			return ;
}
static int GenTransReqMSG(unsigned char *msg,char *transcode,ST_PACK *rPack,bool bdynamic)
{
	int index=0;
	int offset = 4+3+4;   				//������Ϣ����(4)	��Ϣͷ��3��	�����루4��
	char tmp[5]="";
	unsigned char k[17] = "";
	unsigned char clear[17] = "";

	char msgpub[1024]="";
	char msgIn[1024]="";
	char transcont[4096]="";
	
	GenPub(msgpub,transcode,rPack);	
	GenIn(msgIn,transcode,rPack);

	char *trans_head="<BANKINTF>";
	char *trans_tail="</BANKINTF>";
	
	int transhead_len = strlen(trans_head);
	int msgPub_len = strlen(msgpub);
	int msgIn_len = strlen(msgIn);
	int transtail_len = strlen(trans_tail);
	
	int msglen  = strlen(XML_HEAD);	
	memcpy(transcont,XML_HEAD,msglen);						//XML ͷ
	
	memcpy(transcont+msglen,trans_head,transhead_len);			// <BANKINTF>
	msglen += transhead_len;
	
	memcpy(transcont+msglen,msgpub,msgPub_len);				// Pub
	msglen += msgPub_len;
	
	memcpy(transcont+msglen,msgIn,msgIn_len);					// In
	msglen += msgIn_len;
	
	memcpy(transcont+msglen,trans_tail,transtail_len);				//</BANKINTF>
	msglen += transtail_len;
	
	writelog(LOG_DEBUG,"send pre-encrypt [%s]",transcont);

	if(bdynamic)						// ��̬��Կ
	{
		memcpy((char*)k,shm+10,8);
	}
	else
		memcpy((char*)k, FIXKEY,8);
	
	for(index=0;index<msglen;index+=8)
	{
		memcpy((char*)clear,transcont+index,8);
		deskey(k, 0);
		Ddes(clear, msg+offset+index);							
	}

	msglen = 3+4 + index +3;			// 	������Ϣ����
	sprintf(tmp,"%04d",msglen);
	memcpy(msg,tmp,4);
	memcpy(msg+4,"TEB",3);
	memcpy(msg+7,transcode,4);
	memcpy(msg+offset+index,"***",3);
	return offset+index+3;

}

int GetRecvMsg(unsigned char *msg,int msglen,bool bdynamic)
{
	int ret=0;
	int index=0;
	int offset=3+4;					//��Ϣͷ��3��	�����루4��
	unsigned char k[17] = "";
	unsigned char secret[17] = "";

	if(bdynamic)						// ��̬��Կ
	{
		memcpy((char*)k,shm+10,8);
	}
	else
		memcpy((char*)k, FIXKEY,8);
	
	for(;index<msglen-offset-3;index+=8)
	{
		memcpy((char*)secret,(char*)msg+index+offset,8);
		deskey(k, 1);
		Ddes(secret, msg+index+offset);								
	}
	return 0;	
}
int Bank_Bind_Process(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg,char *tradecode)
{
	int ret=0;
	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;
	int msglen=0;
	char retcode[5];

	if(!BANK_LOGIN)
	{
		ret = Bank_SignIn(handle,rPack,pRetCode,szMsg);
		if(ret)
		{
			writelog(LOG_ERR,"ǩ��ʧ��ret[%d]",ret);
			return ret;
		}
	}
	
	char tmp[120]="";
	unsigned char msg[4096]="";

	// ���ɷ��ͱ���
	msglen=GenTransReqMSG(msg,tradecode,rPack,true);

	
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LSAFE_LEVEL,F_VSVARSTR0,F_SCARD0,0);
	
	out_pack->lsafe_level=E_COMMON_ERR;
	
	des2src(host,rPack->scust_auth);						// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1*1000;							// �ȴ����г�ʱʱ��(����)

	writelog(LOG_INFO,"bank info:  ip_addr[%s],port[%d],timeout[%d] ",host,port,timeout);

	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"�������д���");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send((char*)msg,msglen);
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"�������ݴ���");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// ��Ӧ�ó����������
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	writelog(LOG_DEBUG,"Send ret [%d] ",ret);
	memset(msg,0,sizeof msg);
	memset(tmp,0,sizeof tmp);

	ret = tcpsocket.Recv(tmp, 4, timeout);					// �ձ��ĳ���
	if (ret != 4)
	{
		writelog(LOG_ERR,"���������������ݳ��ȴ���");
		strcpy(szMsg,"���������������ݳ��ȴ���");
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;  
	}
	writelog(LOG_DEBUG,"���������������ݰ���ret[%d],head[%s]",ret,tmp);
	msglen = atoi(tmp);

	ret = tcpsocket.Recv((char*)msg, msglen, timeout);					// �ձ�������
	if (ret != msglen)
	{
		writelog(LOG_ERR,"���������������ݰ������");
		strcpy(szMsg,"���������������ݰ������");
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;  
	}

	tcpsocket.Close();

	GetRecvMsg(msg,msglen,true);
		
	writelog(LOG_INFO,"bind recv[%s]",(char*)msg);

	ret=GetXmlValue(retcode, 5, "RET_CODE",(char*)msg);
	if(ret)
	{
		writelog(LOG_ERR,"�������з������ݴ���");
		strcpy(szMsg,"�������з������ݴ���");
		return E_TRANS_BANK_RECVERR;  
	}

	memset(tmp,0,sizeof tmp);
	ret=GetXmlValue(tmp, 101, "MSG",(char*)msg);
	if(ret)
	{
		writelog(LOG_ERR,"�������з������ݴ���");
		strcpy(szMsg,"�������з������ݴ���");
		return E_TRANS_BANK_RECVERR;  
	}

	out_pack->lsafe_level=atoi(retcode);
	des2src(out_pack->vsvarstr0,tmp);
	des2src(out_pack->scard0, rPack->scard0);

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

int Bank_Bind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
	return Bank_Bind_Process(handle, rPack, pRetCode, szMsg,BIND_BANK);
}

int Bank_UnBind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
	return Bank_Bind_Process(handle, rPack, pRetCode, szMsg,UN_BIND_BANK);
}

int Bank_Querybind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
	//return Bank_Bind_Process(handle, rPack, pRetCode, szMsg,QUERY_BIND);
}

//����ͨ�ýӿڹ淶���з�װ�������еĽӿ�
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;
	int msglen=0;
	char retcode[5];

	if(!BANK_LOGIN)
	{
		ret = Bank_SignIn(handle,rPack,pRetCode,szMsg);
		if(ret)
		{
			writelog(LOG_ERR,"ǩ��ʧ��ret[%d]",ret);
			return ret;
		}
	}

	char tmp[120]="";
	unsigned char msg[4096]="";


	// ���ɷ��ͱ���
	msglen=GenTransReqMSG(msg,TRANS_CODE,rPack,true);

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SPHONE,0);
	
	des2src(host,rPack->scust_auth);					// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1*1000;							// �ȴ����г�ʱʱ��(����)

	writelog(LOG_INFO,"bank info:  ip_addr[%s],port[%d],timeout[%d] ",host,port,timeout);
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"�������д���");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send((char*)msg,msglen);
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"�������ݴ���");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// ��Ӧ�ó����������
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	writelog(LOG_DEBUG,"Send ret [%d] ",ret);
	memset(msg,0,sizeof msg);
	memset(tmp,0,sizeof tmp);

	ret = tcpsocket.Recv(tmp, 4, timeout);					// �ձ��ĳ���
	if (ret != 4)
	{
		tcpsocket.Close();
		out_pack->lvol1 = -1;								//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		writelog(LOG_ERR,"��ֵ�����������ݰ������");
		goto r_ret;  
	}
	writelog(LOG_DEBUG,"��ֵ�����������ݰ���ret[%d],head[%s]",ret,tmp);
	msglen = atoi(tmp);

	ret = tcpsocket.Recv((char*)msg, msglen, timeout);					// �ձ�������
	if (ret != msglen)
	{
		tcpsocket.Close();
		out_pack->lvol1 = -1;								//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		writelog(LOG_ERR,"��ֵ�����������ݰ������");
		goto r_ret;  
	}
	tcpsocket.Close();

	GetRecvMsg(msg,msglen,true);
		
	writelog(LOG_INFO,"trans recv[%s]",(char*)msg);

	if(memcmp(msg+3,TRANS_CODE,4) !=0)							// ǰ4λӦ����8914
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		writelog(LOG_ERR,"��ֵ�����������ݽ��������");
		goto r_ret;  
	}

	ret=GetXmlValue(retcode, 5, "RET_CODE",(char*)msg);
	if(ret)
	{
		writelog(LOG_ERR,"�������з������ݴ���");
		strcpy(szMsg,"�������з������ݴ���");
		return E_TRANS_BANK_RECVERR;  
	}
	if(memcmp(retcode,"0000",4)!=0)
	{
		memset(tmp,0,sizeof tmp);
		ret=GetXmlValue(tmp, 101, "MSG",(char*)msg);
		if(ret)
		{
			writelog(LOG_ERR,"�������з������ݴ���");
			strcpy(szMsg,"�������з������ݴ���");
			return E_TRANS_BANK_RECVERR;  
		}

		des2src(szMsg,tmp);
		return E_TRANS_BANK_RECVERR;
	}	
	else
	{
		memset(tmp,0,sizeof tmp);
		ret=GetXmlValue(tmp, 31, "BANK_SEQ",(char*)msg);
		if(ret)
		{
			writelog(LOG_ERR,"�������з������ݴ���");
			strcpy(szMsg,"�������з������ݴ���");
			return E_TRANS_BANK_RECVERR;  
		}		
		des2src(out_pack->sphone,tmp);				// ������ˮ��
		out_pack->lvol1 = 1;
	}
	writelog(LOG_INFO,"trans:bank transno[%s],lvol1[%d]",out_pack->sphone,out_pack->lvol1);

r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

// ����
int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;
	int msglen=0;
	char retcode[5];

	if(!BANK_LOGIN)
	{
		ret = Bank_SignIn(handle,rPack,pRetCode,szMsg);
		if(ret)
		{
			writelog(LOG_ERR,"ǩ��ʧ��ret[%d]",ret);
			return ret;
		}
	}

	char tmp[120]="";
	unsigned char msg[4096]="";
	msglen=GenTransReqMSG(msg,REV_TRANS_CODE,rPack,true);
	
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SCERT_NO,F_SPHONE,0);

	des2src(host,rPack->scust_auth);					// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1*1000;								// �ȴ����г�ʱʱ��

	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"�������д���");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send((char*)msg,msglen);
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"�������ݴ���");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// ��Ӧ�ó����������
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	memset(msg,0,sizeof msg);
	ret = tcpsocket.Recv(tmp, 4, timeout);					// �ձ��ĳ���
	if (ret != 4)
	{
		tcpsocket.Close();
		out_pack->lvol1 = -1;								//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		writelog(LOG_ERR,"���������������ݰ�������");
		goto r_ret;  
	}
	writelog(LOG_DEBUG,"���������������ݰ���ret[%d],head[%s]",ret,tmp);
	msglen = atoi(tmp);

	ret = tcpsocket.Recv((char*)msg, msglen, timeout);					// �ձ�������
	if (ret != msglen)
	{
		tcpsocket.Close();
		out_pack->lvol1 = -1;								//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		writelog(LOG_ERR,"���������������ݰ������");
		goto r_ret;  
	}
	tcpsocket.Close();
	
	GetRecvMsg(msg,msglen,true);
		
	writelog(LOG_INFO,"Reverse recv[%s]",(char*)msg);

	if(memcmp(msg+3,REV_TRANS_CODE,4) !=0)							// ǰ4λӦ����8915
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		writelog(LOG_ERR,"���������������ݽ��������");
		goto r_ret;  
	}

	ret=GetXmlValue(retcode, 5, "RET_CODE",(char*)msg);
	if(ret)
	{
		writelog(LOG_ERR,"�������з������ݴ���");
		strcpy(szMsg,"�������з������ݴ���");
		return E_TRANS_BANK_RECVERR;  
	}
	if(memcmp(retcode,"0000",4)!=0)
	{
		memset(tmp,0,sizeof tmp);
		ret=GetXmlValue(tmp, 101, "MSG",(char*)msg);
		if(ret)
		{
			writelog(LOG_ERR,"�������з������ݴ���");
			strcpy(szMsg,"�������з������ݴ���");
			return E_TRANS_BANK_RECVERR;  
		}

		des2src(szMsg,tmp);
		return E_TRANS_BANK_RECVERR;
	}	
	else
	{
		memset(tmp,0,sizeof tmp);
		ret=GetXmlValue(tmp, 31, "BANK_SEQ",(char*)msg);
		if(ret)
		{
			writelog(LOG_ERR,"�������з������ݴ���");
			strcpy(szMsg,"�������з������ݴ���");
			return E_TRANS_BANK_RECVERR;  
		}		
		des2src(out_pack->sphone,tmp);				// ������ˮ��
		out_pack->lvol1 = 1;
	}	
	writelog(LOG_INFO,"Reverse:bank transno[%s],lvol1[%d]",out_pack->sphone,out_pack->lvol1);		

r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

// ��ѯ���п����
int Bank_Querybala(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;
	int msglen=0;
	char retcode[5];

	if(!BANK_LOGIN)
	{
		ret = Bank_SignIn(handle,rPack,pRetCode,szMsg);
		if(ret)
		{
			writelog(LOG_ERR,"ǩ��ʧ��ret[%d]",ret);
			return ret;
		}
	}

	char tmp[120]="";
	unsigned char msg[4096]="";

	// ���ɷ��ͱ���
	msglen=GenTransReqMSG(msg,QUERY_BALA,rPack,true);

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SALL_NAME,F_DAMT0,F_DAMT1,0);
	
	des2src(host,rPack->scust_auth);						// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1*1000;							// �ȴ����г�ʱʱ��

	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"�������д���");
		return E_TRANS_CONNECT;
	}

	ret = tcpsocket.Send((char*)msg,msglen);
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"�������ݴ���");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// ��Ӧ�ó����������
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	memset(msg,0,sizeof msg);
	ret = tcpsocket.Recv(tmp, 4, timeout);					// �ձ��ĳ���
	if (ret != 4)
	{
		tcpsocket.Close();
		out_pack->lvol1 = -1;								//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		writelog(LOG_ERR,"��ѯ�������������ݰ�������");
		goto r_ret;  
	}
	writelog(LOG_DEBUG,"��ѯ�������������ݰ���ret[%d],head[%s]",ret,tmp);
	msglen = atoi(tmp);

	ret = tcpsocket.Recv((char*)msg, msglen, timeout);					// �ձ�������
	if (ret != msglen)
	{
		tcpsocket.Close();
		out_pack->lvol1 = -1;								//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		writelog(LOG_ERR,"��ѯ�������������ݰ������");
		goto r_ret;  
	}
	tcpsocket.Close();

	GetRecvMsg(msg,msglen,true);
		
	writelog(LOG_INFO,"querybala recv[%s]",(char*)msg);

	if(memcmp(msg+3,QUERY_BALA,4) !=0)							// ǰ4λӦ����8920
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		writelog(LOG_ERR,"��ѯ�������������ݽ��������");
		goto r_ret;  
	}

	ret=GetXmlValue(retcode, 5, "RET_CODE",(char*)msg);
	if(ret)
	{
		writelog(LOG_ERR,"�������з������ݴ���");
		strcpy(szMsg,"�������з������ݴ���");
		return E_TRANS_BANK_RECVERR;  
	}
	if(memcmp(retcode,"0000",4)!=0)
	{
		ret=GetXmlValue(tmp, 101, "MSG",(char*)msg);
		if(ret)
		{
			writelog(LOG_ERR,"�������з������ݴ���");
			strcpy(szMsg,"�������з������ݴ���");
			return E_TRANS_BANK_RECVERR;  
		}

		des2src(szMsg,tmp);
		return E_TRANS_BANK_RECVERR;
	}	
	else
	{
		memset(tmp,0,sizeof tmp);
		ret=GetXmlValue(tmp, 21, "MONEY_TRADE",(char*)msg);
		if(ret)
		{
			writelog(LOG_ERR,"�������з������ݴ���");
			strcpy(szMsg,"�������з������ݴ���");
			return E_TRANS_BANK_RECVERR;  
		}		
		out_pack->damt0 = D4U5(atof(tmp)/100.0, 2);
		out_pack->damt1= out_pack->damt0;	
		out_pack->lvol1 = 1;
	}
	writelog(LOG_INFO,"querybala:cutname[%s],actbala[%f],actavlbala[%f]",out_pack->sall_name,out_pack->damt0,out_pack->damt1);

r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

int Bank_SignIn(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int msglen=0;
	char host[16]="";		//�Է�������ip
	char tmp[120]="";
	short port = 0;			
	int timeout = 0;
	unsigned char msg[4096]="";
	char retcode[5];
	
	CTcpSocket tcpsocket ;

	msglen=GenTransReqMSG(msg,BANK_SIGN_IN,rPack,false);

	des2src(host,rPack->scust_auth);						// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1*1000;							// �ȴ����г�ʱʱ��(����)

	writelog(LOG_INFO,"bank info:  ip_addr[%s],port[%d],timeout[%d] ",host,port,timeout);

	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"�������д���");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send((char*)msg,msglen);
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"�������ݴ���");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// ��Ӧ�ó����������
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	writelog(LOG_DEBUG,"Send ret [%d] ",ret);
	memset(msg,0,sizeof msg);
	ret = tcpsocket.Recv(tmp, 4, timeout);					// �ձ��ĳ���
	if (ret != 4)
	{
		writelog(LOG_ERR,"ǩ�������������ݳ��ȴ���");
		strcpy(szMsg,"ǩ�������������ݳ��ȴ���");
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;  
	}
	writelog(LOG_DEBUG,"ǩ�������������ݰ���ret[%d],head[%s]",ret,tmp);
	msglen = atoi(tmp);

	ret = tcpsocket.Recv((char*)msg, msglen, timeout);					// �ձ�������
	if (ret != msglen)
	{
		writelog(LOG_ERR,"ǩ�������������ݰ������");
		strcpy(szMsg,"ǩ�������������ݰ������");
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;  
	}
	
	tcpsocket.Close();

	GetRecvMsg(msg,msglen,false);
		
	writelog(LOG_INFO,"signIn recv[%s]",(char*)msg);

	if(memcmp(msg+3,BANK_SIGN_IN,4) !=0)							// ǰ4λӦ����8910
	{
		writelog(LOG_ERR,"ǩ�������������ݽ��������");
		return E_TRANS_BANK_RECVERR;  
	}

	ret=GetXmlValue(retcode, 5, "RET_CODE",(char*)msg);
	if(ret)
	{
		writelog(LOG_ERR,"�������з������ݴ���");
		strcpy(szMsg,"�������з������ݴ���");
		return E_TRANS_BANK_RECVERR;  
	}

	if(memcmp(retcode,"0000",4)!=0)
	{
		writelog(LOG_DEBUG,"retcode[%s]",retcode);
		ret=GetXmlValue(tmp, 101, "MSG",(char*)msg);
		if(ret)
		{
			writelog(LOG_ERR,"�������з������ݴ���");
			strcpy(szMsg,"�������з������ݴ���");
			return E_TRANS_BANK_RECVERR;  
		}
		strcpy(szMsg,tmp);
		return E_TRANS_BANK_RECVERR;  
	}	

	memset(tmp,0,sizeof tmp);
	ret=GetXmlValue(tmp, 9, "NEW_KEY",(char*)msg);
	if(ret)
	{
		writelog(LOG_ERR,"�������з������ݴ���");
		strcpy(szMsg,"�������з������ݴ���");
		return ret;
	}
	else				// ǩ���ɹ�
	{
		shm[1]=1;
		shm[3]=0;
		memcpy(shm+10,tmp,8);

		char buffer[20]="";
		int k=0;
		for(int i=0;i<8;i++)
		{
			k=tmp[i];
			sprintf(&buffer[2*i],"%02X",k);
		}
		buffer[16]=0;
		writelog(LOG_INFO,"Bank dynamic key=[%s]",buffer);
	}
	
	return 0;
}

int Bank_Checkacc(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int msglen=0;
	char host[16]="";		//�Է�������ip
	char tmp[120]="";
	short port = 0;			
	int timeout = 0;
	unsigned char msg[4096]="";
	char retcode[5];
	
	CTcpSocket tcpsocket ;

	msglen=GenTransReqMSG(msg,BANK_ACCCHECK,rPack,true);

	des2src(host,rPack->scust_auth);						// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1*1000;							// �ȴ����г�ʱʱ��(����)

	writelog(LOG_INFO,"bank info:  ip_addr[%s],port[%d],timeout[%d] ",host,port,timeout);

	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"�������д���");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send((char*)msg,msglen);
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"�������ݴ���");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// ��Ӧ�ó����������
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	writelog(LOG_DEBUG,"Send ret [%d] ",ret);
	memset(msg,0,sizeof msg);
	ret = tcpsocket.Recv(tmp, 4, timeout);					// �ձ��ĳ���
	if (ret != 4)
	{
		writelog(LOG_ERR,"���˽����������ݳ��ȴ���");
		strcpy(szMsg,"���˽����������ݳ��ȴ���");
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;  
	}
	writelog(LOG_DEBUG,"���˽����������ݰ���ret[%d],head[%s]",ret,tmp);
	msglen = atoi(tmp);

	ret = tcpsocket.Recv((char*)msg, msglen, timeout);					// �ձ�������
	if (ret != msglen)
	{
		writelog(LOG_ERR,"���˽����������ݰ������");
		strcpy(szMsg,"���˽����������ݰ������");
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;  
	}
	
	tcpsocket.Close();

	GetRecvMsg(msg,msglen,true);
		
	writelog(LOG_INFO,"checkacc recv[%s]",(char*)msg);

	if(memcmp(msg+3,BANK_ACCCHECK,4) !=0)							// ǰ4λӦ����8918
	{
		writelog(LOG_ERR,"���˽����������ݽ��������");
		return E_TRANS_BANK_RECVERR;  
	}

	ret=GetXmlValue(retcode, 5, "RET_CODE",(char*)msg);
	if(ret)
	{
		writelog(LOG_ERR,"�������з������ݴ���");
		strcpy(szMsg,"�������з������ݴ���");
		return E_TRANS_BANK_RECVERR;  
	}

	if(memcmp(retcode,"0000",4)!=0)
	{
		writelog(LOG_DEBUG,"retcode[%s]",retcode);
		ret=GetXmlValue(tmp, 101, "MSG",(char*)msg);
		if(ret)
		{
			writelog(LOG_ERR,"�������з������ݴ���");
			strcpy(szMsg,"�������з������ݴ���");
			return E_TRANS_BANK_RECVERR;  
		}
		strcpy(szMsg,tmp);
		return E_TRANS_BANK_RECVERR;  
	}	
	return 0;
}

