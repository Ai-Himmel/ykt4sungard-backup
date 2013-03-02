/* ----------------------------------------------------------
 * �������ƣ�bank_ccb_ahut.cpp
 * �������ڣ�2009-08-10
 * �������ߣ������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����չ����нӿ�
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_ccb_ahut.h"
#include "tcp.h"

////��ͷ��ֻ�н������ڣ�ʱ�䣬��ˮ�ţ��ն˺��ڱ仯
// termid  	: rPack->lvol6
// refno   	: rPack->sholder_ac_no
// transdate	:rPack->sdate0
// transtime	:rPack->stime0
static void GenMsgHead(char *msghead,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf,"AreaNo","");								//��������
	AddXmlItemStr(buf,"ChanNo","");								//��������
	AddXmlItemInt(buf, "TerminalNo", rPack->lvol6);					//�ն˱��
	AddXmlItemStr(buf,"TransNo",rPack->sholder_ac_no);			//������ˮ��
	AddXmlItemStr(buf,"TransDate",rPack->sdate0);				//��������
	AddXmlItemStr(buf,"TransTime",rPack->stime0);					//����ʱ��
	AddXmlItemStr(buf,"BankNo","");								//��������
	AddXmlItemStr(buf,"TellerNo","");								//��Ա����
	AddXmlItemInt(buf, "FuncTionFlag", 1);							//�����־
	AddXmlItemStr(msghead, "MsgHead", buf);						// ȫ������MsgHead ��	
	writelog(LOG_DEBUG,"msghead[%s] ",msghead);
}

// ��ֵ����
static void GenMsgBodyTrans(char *msgbody,ST_PACK *rPack)	
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//ѧУ����
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//У԰������(ʹ��ѧ����)
	AddXmlItemStr(buf, "CusName", rPack->scust_limit);				//�ͻ�����
	AddXmlItemInt(buf, "SignFlag", 1);								//ǩԼ��־
	AddXmlItemStr(buf, "ActNo", rPack->scust_limit2);				// ���п���
	AddXmlItemDbl(buf, "Amount", rPack->damt0);					// ���׽��

	AddXmlItemStr(msgbody, "MsgBody", buf);						//ȫ������MsgBody ��	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

// ��������
static void GenMsgBodyTransRev(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//ѧУ����
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//У԰������(ʹ��ѧ����)
	AddXmlItemDbl(buf, "Amount", rPack->damt0);					// ���׽��
	AddXmlItemStr(buf, "RSeqNo", rPack->sholder_ac_no);			//������ˮ��

	AddXmlItemStr(msgbody, "MsgBody", buf);						//ȫ������MsgBody ��	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

static void GenMsgBodyQuery(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//ѧУ����
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//У԰������(ʹ��ѧ����)
	AddXmlItemInt(buf, "SignFlag", 1);								//ǩԼ��־
	AddXmlItemStr(buf, "ActNo", rPack->scust_limit2);				// ���п���

	AddXmlItemStr(msgbody, "MsgBody", buf);						//ȫ������MsgBody ��	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

static void GenTransReqMSG(char *msg,char *transcode,char *msghead,char *msgbody)
{
	char len_buf[16]="";
	char transcont[2048]="";
	char *trans_head="<TranRequest>";
	char *trans_tail="</TranRequest>";

	int transhead_len = strlen(trans_head);
	int msghead_len = strlen(msghead);
	int msgbody_len = strlen(msgbody);
	int transtail_len = strlen(trans_tail);
	int xmlhead_len = strlen(XML_HEAD);

	int transcont_len =   transhead_len + msghead_len + msgbody_len + transtail_len;
	
	memcpy(transcont,trans_head,transhead_len);
	memcpy(transcont+transhead_len,msghead,msghead_len);
	memcpy(transcont+transhead_len+msghead_len,msgbody,msgbody_len);
	memcpy(transcont+transhead_len+msghead_len+msgbody_len,trans_tail,transtail_len);

	sprintf(len_buf,"%08d",4 + xmlhead_len + transcont_len);
	memcpy(msg,len_buf,8);											// 8λ����
	memcpy(msg+8,transcode,4);										// 4λ������
	memcpy(msg+12,XML_HEAD,xmlhead_len);							// xml ͷ
	memcpy(msg + xmlhead_len +12,transcont,transcont_len);				// ��������(msghead + msgbody)
	writelog(LOG_DEBUG,"msg[%s] ",msg);
}

//����ͨ�ýӿڹ淶���з�װ�������еĽӿ�
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int msglen=0;
	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;

	char msg[4096]="";
	char msghead[1024] = "";							// �洢��ͷ
	char msgbody[1024]="";								// �洢����
	char tmp[256] = "";

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
	//���ɰ�ͷ
	GenMsgHead(msghead,rPack);

	//����ת�˰���
	GenMsgBodyTrans(msgbody,rPack);

	// ����ת�˱���
	GenTransReqMSG(msg,TRANS_CODE,msghead,msgbody);

	msglen = strlen(msg);
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"�������д���");
		return E_TRANS_CONNECT;
	}

	writelog(LOG_INFO,"trans send[%s]",msg);
	
	ret = tcpsocket.Send(msg,msglen);
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
	ret = tcpsocket.Recv(tmp, 8, timeout);						// �Ȱѳ���������
	if(ret !=8)
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		writelog(LOG_ERR,"��ֵ�����������ݰ�������ret[%d],tmp[%s]",ret,tmp);
		strcpy(szMsg,"��ֵ�����������ݰ�������");
		goto r_ret;  										// ����ʱ�������ʱ
	}
	writelog(LOG_DEBUG,"��ֵ�����������ݰ���ret[%d],head[%s]",ret,tmp);
	msglen = atoi(tmp);
	ret = tcpsocket.Recv(msg, msglen, timeout);					// �ձ�������
	writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",msg,ret);

	if (ret<4 || ret != msglen)
	{
		out_pack->lvol1 = -1;								//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		strcpy(szMsg,"��ֵ�����������ݰ������");
		goto r_ret;  
	}

	if(strncmp(msg,"1120",4) !=0)							// ǰ4λӦ���� 1120
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"��ֵ�����������ݽ��������");
		goto r_ret;  
	}

	ret = GetXmlValue(tmp, 5, "ResultCode", msg);
	if(ret)
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"��ֵ�����������ݷ��������");
		goto r_ret;  
	}
					
	if(strncmp(tmp,"0000",4)!=0)
	{
		GetXmlValue(tmp,40,"Err_Info",msg);
		strcpy(szMsg,tmp);									// ���з����Ĵ�����Ϣ
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		GetXmlValue(tmp, 21, "TransNo", msg);
		memcpy(out_pack->sphone,tmp,strlen(tmp));				// ������ˮ��
		GetXmlValue(tmp, 100, "Err_Info", msg);					// ���з�����Ϣ
	}
	writelog(LOG_INFO,"trans:bank transno[%s],retinfo[%s],lvol1[%d]",out_pack->sphone,tmp,out_pack->lvol1);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

// ����
int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int msglen = 0;
	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;

	char msg[4096]="";
	char msghead[1024] = "";							// �洢��ͷ
	char msgbody[1024]="";								// �洢����
	char tmp[256] = "";
	
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SCERT_NO,0);

	des2src(host,rPack->scust_auth);					// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1*1000;								// �ȴ����г�ʱʱ��

	//���ɰ�ͷ
	GenMsgHead(msghead,rPack);

	//���ɳ�������
	GenMsgBodyTrans(msgbody,rPack);

	// ���ɳ�������
	GenTransReqMSG(msg,REV_TRANS_CODE,msghead,msgbody);

	msglen = strlen(msg);
	
	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"�������д���");
		return E_TRANS_CONNECT;
	}
	writelog(LOG_INFO,"reverse send[%s]",msg);
	
	ret = tcpsocket.Send(msg,msglen);
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
	ret = tcpsocket.Recv(tmp, 8, timeout);						// �Ȱѳ���������
	if(ret !=8)
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		writelog(LOG_ERR,"���������������ݰ�������ret[%d],tmp[%s]",ret,tmp);
		strcpy(szMsg,"���������������ݰ�������");
		goto r_ret;  										// ����ʱ�������ʱ
	}

	msglen = atoi(tmp);
	ret = tcpsocket.Recv(msg, msglen, timeout);					// �ձ�������
	writelog(LOG_INFO,"transRev recv[%s],recvlen[%d]",msg,ret);

	if (ret<4 || ret != msglen)
	{
		out_pack->lvol1 = -1;								//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		strcpy(szMsg,"���������������ݰ������");
		goto r_ret;  
	}

	if(strncmp(msg,"1130",4) !=0)							// ǰ4λӦ���� 1130
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"���������������ݽ��������");
		goto r_ret;  
	}

	ret = GetXmlValue(tmp, 5, "ResultCode", msg);
	if(ret)
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"���������������ݷ��������");
		goto r_ret;  
	}
					
	if(strncmp(tmp,"0000",4)!=0)
	{
		GetXmlValue(tmp,40,"Err_Info",msg);
		strcpy(szMsg,tmp);									// ���з����Ĵ�����Ϣ
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		GetXmlValue(tmp, 21, "TransNo", msg);
		memcpy(out_pack->sphone,tmp,strlen(tmp));				// ������ˮ��
		GetXmlValue(tmp, 100, "Err_Info", msg);					// ���з�����Ϣ
	}
	writelog(LOG_INFO,"transrev:bank transno[%s],retinfo[%s],lvol1[%d]",out_pack->sphone,tmp,out_pack->lvol1);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

// ��ѯ���п����
int Bank_Querybala(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int msglen=0;
	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;

	char msg[4096]="";
	char msghead[1024] = "";							// �洢��ͷ
	char msgbody[1024]="";								// �洢����
	char tmp[256] = "";

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SALL_NAME,F_DAMT0,F_DAMT1,0);
	
	des2src(host,rPack->scust_auth);					// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1*1000;							// �ȴ����г�ʱʱ��

	//���ɰ�ͷ
	GenMsgHead(msghead,rPack);

	//���ɲ�ѯ����
	GenMsgBodyQuery(msgbody,rPack);

	// ���ɲ�ѯ����
	GenTransReqMSG(msg,QUERY_BALA,msghead,msgbody);

	msglen = strlen(msg);
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"�������д���");
		return E_TRANS_CONNECT;
	}

	writelog(LOG_INFO,"querybala send[%s]",msg);
	
	ret = tcpsocket.Send(msg,msglen);
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
	ret = tcpsocket.Recv(tmp, 8, timeout);						// �Ȱѳ���������
	if(ret !=8)
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"��ѯ�������������ݰ�������");
		goto r_ret;  										// ����ʱ�������ʱ
	}

	msglen = atoi(tmp);
	ret = tcpsocket.Recv(msg, msglen, timeout);					// �ձ�������
	writelog(LOG_INFO,"querybala recv[%s],recvlen[%d]",msg,ret);

	if (ret<4 || ret != msglen)
	{
		out_pack->lvol1 = -1;								//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		strcpy(szMsg,"��ѯ�������������ݰ������");
		goto r_ret;  
	}

	if(strncmp(msg,"1110",4) !=0)							// ǰ4λӦ���� 1110
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"��ѯ�������������ݽ��������");
		goto r_ret;  
	}

	ret = GetXmlValue(tmp, 5, "ResultCode", msg);
	if(ret)
	{
		out_pack->lvol1 = -1;								//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"��ѯ�������������ݷ��������");
		goto r_ret;  
	}
					
	if(strncmp(tmp,"0000",4)!=0)
	{
		GetXmlValue(tmp,40,"Err_Info",msg);
		strcpy(szMsg,tmp);									// ���з����Ĵ�����Ϣ
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		GetXmlValue(tmp, 40, "CusName", msg);
		memcpy(out_pack->sall_name,tmp,strlen(tmp));				// �ͻ�����
		GetXmlValue(tmp, 20, "ActBal", msg);						// �ʻ����
		out_pack->damt0 = D4U5(atof(tmp), 2);
		GetXmlValue(tmp, 20, "ActAvlBal", msg);					// �ʻ��������
		out_pack->damt1= D4U5(atof(tmp), 2);	
		
	}
	writelog(LOG_INFO,"querybala:cutname[%s],actbala[%f],actavlbala[%f]",out_pack->sall_name,out_pack->damt0,out_pack->damt1);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

