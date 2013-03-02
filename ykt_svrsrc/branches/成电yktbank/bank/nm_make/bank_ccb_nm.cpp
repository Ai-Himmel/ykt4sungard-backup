/* ----------------------------------------------------------
 * �������ƣ�bank_ccb_nm.cpp
 * �������ڣ�2009-08-10
 * �������ߣ������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����ɲƾ�����ת�˽ӿ�
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_ccb_nm.h"
#include "tcp.h"

#define STRLENCPY(des,src,len) strncpy(des,src,strlen(src)>len?len:strlen(src))

//����ͨ�ýӿڹ淶���з�װ�������еĽӿ�
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;

	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;
//	TRANS_REQ trans_req;
//	TRANS_ANS trans_ans;
//	memset(&trans_req,0x20,sizeof trans_req);			// ������Ͽո�
//	memset(&trans_ans,0x20,sizeof trans_ans);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SDATE1,F_SCERT_NO,0);
	char buf[256] = " ";
	char tmp[8] = "";
	
	des2src(host,rPack->scust_auth);					// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1;								// �ȴ����г�ʱʱ��

	memset(buf,0x20,sizeof buf);			// ���ո�
	sprintf(buf,"%04d",REQ_PACK_LEN);		// ���峤��
	strcpy(buf+4,TRANS_CODE);				// ������
	STRLENCPY(buf+8, rPack->sdate0,8);				// ��������
	STRLENCPY(buf+16, rPack->sholder_ac_no,14);		// һ��ͨ���ײο���
	STRLENCPY(buf+30, rPack->sphone,32);				// ѧ����
	STRLENCPY(buf+62, rPack->scust_limit,32);			// ����
	STRLENCPY(buf+94,rPack->scust_auth2,18);			// ���֤��
	STRLENCPY(buf+112,rPack->scust_limit2,32);		// ���п���
	sprintf(buf+144,"%-17.2f",rPack->damt0);			// ���׽��
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}

	buf[REQ_PACK_LEN+4]=0;
	writelog(LOG_INFO,"trans send[%s]",buf);
	
	ret = tcpsocket.Send(buf,REQ_PACK_LEN+4);
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// ��Ӧ�ó����������
	      	writelog(LOG_ERR,"Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	ret = tcpsocket.Recv(buf, ANS_PACK_LEN+4, timeout);		
	tcpsocket.Close();
	
	buf[ANS_PACK_LEN+4]=0;
	writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",buf,ret);

	if (ret!=ANS_PACK_LEN+4)
	{
		out_pack->lvol1 = -1;							//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		strcpy(szMsg,"�����������ݴ���");
		goto r_ret;  
	}

	memcpy(tmp,buf,4);
	if(atoi(tmp) != ANS_PACK_LEN)
	{
		out_pack->lvol1 = -1;							//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"�����������ݴ���");
		goto r_ret;  // ����ʱ�������ʱ
	}
	memcpy(tmp,buf+20,6);								
	if(strncmp(tmp,"000000",6)!=0)
	{
		memcpy(szMsg,buf+26,34);
		*pRetCode = E_TRANS_BANK_RECVERR;
		goto r_ret;  // ���ж˴������
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->sdate1,buf+12,8);						// ������ˮ��
		memcpy(out_pack->scert_no,buf+26,34);					// ���з�����Ϣ
	}
	writelog(LOG_INFO,"bankretinfo[%s],lvol1[%d]",out_pack->scert_no,out_pack->lvol1);
r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;

	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;
	
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;
//	REVERSE_REQ reverse_req;
//	REVERSE_ANS reverse_ans;
//	memset(&reverse_req,0x20,sizeof reverse_req);			// ������Ͽո�
//	memset(&reverse_ans,0x20,sizeof reverse_ans);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SCERT_NO,0);

	des2src(host,rPack->scust_auth);					// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1;								// �ȴ����г�ʱʱ��
	char buf[256] = " ";
	char tmp[8] = "";

	memset(buf,0x20,sizeof buf);							// ���ո�
	sprintf(buf,"%04d",REV_REQ_PACK_LEN);					// ���峤��
	strcpy(buf+4,REV_TRANS_CODE);							// ������
	STRLENCPY(buf+8,rPack->sdate0,8);						// ��������
	STRLENCPY(buf+16,rPack->sholder_ac_no,14);			// һ��ͨ���ײο���
	STRLENCPY(buf+30,rPack->sphone,32);					// ѧ����
	STRLENCPY(buf+62,rPack->scust_limit2,32);				// ���п���
	sprintf(buf+94,"%-17.2f",rPack->damt0);					// ���׽��
	
	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}
	buf[REV_REQ_PACK_LEN +4]=0;
	writelog(LOG_INFO,"reverse send[%s]",buf);
	
	ret = tcpsocket.Send(buf,REV_REQ_PACK_LEN +4);
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// ��Ӧ�ó����������
	      	writelog(LOG_ERR,"Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	ret = tcpsocket.Recv(buf, REV_ANS_PACK_LEN+4, timeout);		
	tcpsocket.Close();
	
	buf[REV_ANS_PACK_LEN+4] = 0;
	writelog(LOG_INFO,"reverse recv[%s]",buf);
	
	if (ret!=REV_ANS_PACK_LEN+4)
	{
		out_pack->lvol1 = -1;							//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		strcpy(szMsg,"�����������ݴ���");
		goto r_ret;  
	}

	memcpy(tmp,buf,4);
	if(atoi(tmp) != REV_ANS_PACK_LEN)
	{
		out_pack->lvol1 = -1;							//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"�����������ݴ���");
		goto r_ret;  // ����ʱ�������ʱ
	}
	memcpy(tmp,buf+4,6);
	if(strncmp(tmp,"000000",6)!=0)
	{
		memcpy(szMsg,buf+10,34);
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->scert_no,buf+10,34);
	}
r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

