/* ----------------------------------------------------------
 * �������ƣ�bank_ccb_nm.cpp
 * �������ڣ�2010-10-26
 * �������ߣ�xlh
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��ɵ罨��ת�˽ӿ�
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_ccb_cd.h"
#include "tcp.h"
#include "bank.h"


#define STRLENCPY(des,src,len) strncpy(des,src,strlen(src)>len?len:strlen(src))

static void leftzstr(int len,char *intstr,char *outstr)
{
	int totallength=0;
	int strlength=0;
	strlength=strlen(intstr);
	totallength=len-strlength;
	strlength=strlen(intstr);
	for(int i=0;i<totallength;i++)
	{
		strcat(outstr,"0");
	}
	strcat(outstr,intstr);

}
//����ͨ�ýӿڹ淶���з�װ�������еĽӿ�
int Bank_CheckLine()
{
	return 0;
}
int SignInOut(INNER_TRANS_REQUEST * inner_trans,ST_BANK_CONFIG *g_Bank,char *signo)
{
	int ret=0;
       char packlen[6]="";
       char len[5]="";
	char host[16]="";		//�Է�������ip
	char szMsg[1024]="";
	short port = 0;			
	int timeout = 0;
       char temp[512]="";
	char sysdate[11]="";
	char systime[9]="";
	CTcpSocket tcpsocket ;
	char buf[256] = " ";
	char tmp[8] = "";
	des2src(host,g_Bank->BankUnit[2].szBankIP);					// ����ip
	port=g_Bank->BankUnit[2].iBankPort;									// ���ж˿�
	timeout =g_Bank->BankUnit[2].iBankTimeout;								// �ȴ����г�ʱʱ��
  	getsysdate(sysdate);
	getsystime(systime);
	//******************************************************************
	//��ͷ
	//******************************************************************
	PACKHEAD head;
      SignInOut_REQ tran;
 	memset(&tran,0x20,sizeof tran);			// ���ո�
	memset(&head,0x20,sizeof head);			// ���ո�
	sprintf(len,"%d",sizeof tran -5);
	leftzstr(5,len,packlen);
	memcpy(tran.head.packlen,packlen ,(int)sizeof (tran.head.packlen));    //������
	des2src(tran.head.Txcode,REGISTRATION_CODE);    //������
	des2src(tran.head.TxDate, sysdate); //��������
	des2src(tran.head.TxTime,systime);//����ʱ��
	des2src(tran.head.TxChannel,"23232323");//����	
	leftzstr(16,systime,temp);
	memcpy(tran.head.Serial,temp,(int)sizeof (tran.head.Serial));//���ײο���
	des2src(tran.head.RespCode,"E9999");//��ʼ����
	//******************************************************************
	//����
	//******************************************************************
	des2src(tran.SignInOut,signo);//ǩ��ǩ��
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}

	//writelog(LOG_INFO,"trans send[%s]",buf);
	
	ret = tcpsocket.Send((char*)&tran,sizeof tran);
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

	ret = tcpsocket.Recv((char*)&head, sizeof head, timeout);		
	tcpsocket.Close();
	
	
	writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",buf,ret);

	if (ret!=sizeof head)
	{
		strcpy(szMsg,"�����������ݴ���");
		printf(szMsg);
		return ret;  
	}

	memcpy(tmp,head.packlen,5);
	if(atoi(tmp) !=sizeof head)
	{
		strcpy(szMsg,"�����������ݴ���");
		printf(szMsg);
		return ret;  // ����ʱ�������ʱ
	}					
	if(strncmp(head.RespCode,"00000",5)!=0)
	{
		memcpy(szMsg,head.RespMess,34);
		ret = E_TRANS_BANK_RECVERR;
		return printf(szMsg);;  // ���ж˴������
		return ret;
	}
	


	
	return 0;
}

int ToRegister(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
       char packlen[6]="";
       char len[5]="";
	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;
       char temp[512]="";
	char sysdate[11]="";
	char systime[9]="";
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SDATE1,F_SCERT_NO,0);
	char buf[256] = " ";
	char tmp[8] = "";
	des2src(host,rPack->scust_auth);					// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1;								// �ȴ����г�ʱʱ��
    	getsysdate(sysdate);
	getsystime(systime);
	//******************************************************************
	//��ͷ
	//******************************************************************
	PACKHEAD head;
       ToRegister_REQ tran;
	memset(&tran,0x20,sizeof tran);			// ���ո�
	memset(&head,0x20,sizeof head);			// ���ո�
	sprintf(len,"%d",sizeof tran -5);
	leftzstr(5,len,packlen);
	memcpy(tran.head.packlen,packlen, sizeof (tran.head.packlen));    //������
	des2src(tran.head.Txcode,SIGNED_CODE);    //������
	des2src(tran.head.TxDate, sysdate); //��������
	des2src(tran.head.TxTime,systime);//����ʱ��
	des2src(tran.head.TxChannel,"23232323");//����
	des2src(rPack->sholder_ac_no,rPack->semail2);//��Ϊû�У��������֤
	leftzstr(16,rPack->sholder_ac_no,temp);
	memcpy(tran.head.Serial,temp,sizeof (tran.head.Serial));//���ײο���
	des2src(tran.head.RespCode,"E9999");//��ʼ����
	//******************************************************************
	//����
	//******************************************************************

       switch(rPack->sstatus0[0])
	{
		case 'A':
			des2src(tran.Func,"0");//ǩԼ��Լ 0��1
			break;
		case 'D':
			des2src(tran.Func,"1");//ǩԼ��Լ 0��1
			break;
		default:
			break;
	}
	des2src(tran.BankCard,rPack->scard0);
	des2src(tran.SchoolCard,rPack->spager);
	des2src(tran.SchoolNo,rPack->semail2);
	des2src(tran.SchoolName,rPack->sall_name);
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}

	//writelog(LOG_INFO,"trans send[%s]",buf);
	
	ret = tcpsocket.Send((char*)&tran,sizeof tran);
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

	ret = tcpsocket.Recv((char*)&head, sizeof head, timeout);		
	tcpsocket.Close();
	
	writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",buf,ret);

	if (ret!=sizeof head)
	{
		out_pack->lvol1 = -1;							//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		strcpy(szMsg,"�����������ݴ���");
		goto r_ret;  
	}

	memcpy(tmp,head.packlen,5);
	if(atoi(tmp) !=sizeof head)
	{
		out_pack->lvol1 = -1;							//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"�����������ݴ���");
		goto r_ret;  // ����ʱ�������ʱ
	}					
	if(strncmp(head.RespCode,"00000",5)!=0)
	{
		memcpy(szMsg,head.RespMess,34);
		*pRetCode = E_TRANS_BANK_RECVERR;
		goto r_ret;  // ���ж˴������
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->sdate1,head.BankSerial,sizeof out_pack->sdate1 );						// ������ˮ��
		memcpy(out_pack->scert_no,head.RespMess,sizeof out_pack->scert_no);					// ���з�����Ϣ
	}
	writelog(LOG_INFO,"bankretinfo[%s],lvol1[%d]",out_pack->scert_no,out_pack->lvol1);
r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
       char packlen[6]="";
       char len[5]="";
	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;
       char temp[512]="";
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SDATE1,F_SCERT_NO,0);
	char buf[256] = " ";
	char tmp[8] = "";
	des2src(host,rPack->scust_auth);					// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1;								// �ȴ����г�ʱʱ��
	//******************************************************************
	//��ͷ
	//******************************************************************
	PACKHEAD head;
       TRANS_REQ tran;
	memset(&tran,0x20,sizeof tran);			// ���ո�
	memset(&head,0x20,sizeof head);			// ���ո�
	sprintf(len,"%d",sizeof tran -5);
	leftzstr(5,len,packlen);
	memcpy(tran.head.packlen,packlen, sizeof (tran.head.packlen));    //������
	des2src(tran.head.Txcode,TRANS_CODE);    //������
	des2src(tran.head.TxDate, rPack->sdate0); //��������
	des2src(tran.head.TxTime,rPack->stime0);//����ʱ��
	des2src(tran.head.TxChannel,"23232323");//����	
	leftzstr(16,rPack->sholder_ac_no,temp);
	memcpy(tran.head.Serial,temp,sizeof (tran.head.Serial));//���ײο���
	des2src(tran.head.RespCode,"E9999");//��ʼ����
	//******************************************************************
	//����
	//******************************************************************
	des2src(tran.SchoolCard,rPack->sphone);//������ѧ����
	des2src(tran.SchoolName,rPack->scust_limit);//����
	des2src(tran.SchoolNo,rPack->scust_auth2);//���֤��
	des2src(tran.BankCard,rPack->scust_limit2);//���п���
	memset(temp,0,sizeof temp);
	sprintf(temp,"%lf",rPack->damt0);
	des2src(tran.RopAmt,temp);
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}

	//writelog(LOG_INFO,"trans send[%s]",buf);
	
	ret = tcpsocket.Send((char*)&tran,sizeof tran);
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

	ret = tcpsocket.Recv((char*)&head, sizeof head, timeout);		
	tcpsocket.Close();
	
	writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",buf,ret);

	if (ret!=sizeof head)
	{
		out_pack->lvol1 = -1;							//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		strcpy(szMsg,"�����������ݴ���");
		goto r_ret;  
	}

	memcpy(tmp,head.packlen,5);
	if(atoi(tmp) !=sizeof head)
	{
		out_pack->lvol1 = -1;							//�������ݴ��󣬺�̨Ӧ�����з�����
		strcpy(szMsg,"�����������ݴ���");
		goto r_ret;  // ����ʱ�������ʱ
	}					
	if(strncmp(head.RespCode,"00000",5)!=0)
	{
		memcpy(szMsg,head.RespMess,34);
		*pRetCode = E_TRANS_BANK_RECVERR;
		goto r_ret;  // ���ж˴������
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->sdate1,head.BankSerial,sizeof out_pack->sdate1);						// ������ˮ��
		memcpy(out_pack->scert_no,head.RespMess,sizeof out_pack->scert_no);					// ���з�����Ϣ
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
       char packlen[6]="";
       char len[5]="";
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SCERT_NO,0);

	des2src(host,rPack->scust_auth);					// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1;								// �ȴ����г�ʱʱ��
	 char temp[512]="";

	//******************************************************************
	//��ͷ
	//******************************************************************
	PACKHEAD head;
       REVTRANS_REQ tran;
	memset(&tran,0x20,sizeof tran);			// ���ո�
	memset(&head,0x20,sizeof head);			// ���ո�
	sprintf(len,"%d",sizeof tran -5);
	leftzstr(5,len,packlen);
	memcpy(tran.head.packlen,packlen, sizeof (tran.head.packlen));    //������
	des2src(tran.head.Txcode,TRANS_CODE);    //������
	des2src(tran.head.TxDate, rPack->sdate0); //��������
	des2src(tran.head.TxTime,rPack->stime0);//����ʱ��
	des2src(tran.head.TxChannel,"23232323");//����	
	leftzstr(16,rPack->sholder_ac_no,temp);
	memcpy(tran.head.Serial,temp,sizeof (tran.head.Serial));//���ײο���
	des2src(tran.head.RespCode,"E9999");//��ʼ����
	//******************************************************************
	//����
	//******************************************************************
	des2src(tran.OldTxdate, rPack->sdate0);    //ԭ��������
	des2src(tran.OldTransBankId, temp);
	memset(temp,0,sizeof temp);
	sprintf(temp,"%d",rPack->damt0);
	des2src(tran.OldRopAmt, temp);
	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}
	
	
	ret = tcpsocket.Send((char*)&tran,sizeof tran);
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

	ret = tcpsocket.Recv((char*)&head, sizeof head, timeout);		
	tcpsocket.Close();
	
	if (ret!=sizeof head)
	{
		out_pack->lvol1 = -1;							//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		strcpy(szMsg,"�����������ݴ���");
		goto r_ret;  
	}

	
	if(strncmp(head.RespCode,"00000",5)!=0)
	{
		memcpy(szMsg,head.RespMess,sizeof szMsg);
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->scert_no,head.RespMess,sizeof out_pack->scert_no);
	}
r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


int ListDown(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;

	char host[16]="";		//�Է�������ip
	short port = 0;			
	int timeout = 0;
       char packlen[6]="";
       char len[5]="";
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SCERT_NO,0);

	des2src(host,rPack->scust_auth);					// ����ip
	port=rPack->lvol0;									// ���ж˿�
	timeout = rPack->lvol1;								// �ȴ����г�ʱʱ��
	 char temp[512]="";

	//******************************************************************
	//��ͷ
	//******************************************************************
	ListDown_ans head;
       ListDown_REQ tran;
	memset(&tran,0x20,sizeof tran);			// ���ո�
	memset(&head,0x20,sizeof head);			// ���ո�
	sprintf(len,"%d",sizeof tran -5);
	leftzstr(5,len,packlen);
	memcpy(tran.head.packlen,packlen, sizeof (tran.head.packlen));    //������
	des2src(tran.head.Txcode,TRANS_CODE);    //������
	des2src(tran.head.TxDate, rPack->sdate0); //��������
	des2src(tran.head.TxTime,rPack->stime0);//����ʱ��
	des2src(tran.head.TxChannel,"23232323");//����	
	leftzstr(16,rPack->sholder_ac_no,temp);
	memcpy(tran.head.Serial,temp,sizeof (tran.head.Serial));//���ײο���
	des2src(tran.head.RespCode,"E9999");//��ʼ����
	//******************************************************************
	//����
	//******************************************************************
	des2src(tran.CompareDate, rPack->sdate0);    //ԭ��������
	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}
	
	
	ret = tcpsocket.Send((char*)&tran,sizeof tran);
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

	ret = tcpsocket.Recv((char*)&head, sizeof head, timeout);		
	tcpsocket.Close();
	
	if (ret!=sizeof head)
	{
		out_pack->lvol1 = -1;							//��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
		strcpy(szMsg,"�����������ݴ���");
		goto r_ret;  
	}

	
	if(strncmp(head.head.RespCode,"00000",5)!=0)
	{
		memcpy(szMsg,head.head.RespMess,sizeof szMsg);
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->scert_no,head.head.RespMess,sizeof out_pack->scert_no);
		memcpy(out_pack->scert_no2,head.AnsNumSuc,sizeof out_pack->scert_no2);
		memcpy(out_pack->snote,head.AnsNumFal,sizeof out_pack->snote);
		memcpy(out_pack->snote2,head.RopeCntAmt,sizeof out_pack->snote2);//�ܽ��
	}
r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


