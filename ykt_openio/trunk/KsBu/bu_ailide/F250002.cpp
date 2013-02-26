/* --------------------------------------------
 * ��������: F250002.sqc
 * ��������: 2007-08-16
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: ���ת��
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "cpack.h"
#include "bupub.h"
#include "tcp.h"
#include "logfile.h"

#pragma pack(1)

typedef struct{
	char prix[1];
	char length[4];
	char type[4];
	char bitery[16];
	char room[20];
	char cutid[22];
	char money[7];
	char datetime[10];
    char tracenum[18];
	char retnum[4];
	char clientid[4];
	char signcheck[32];
}ext_elect_req_t;

#pragma pack()

#define E_ELEC_DB_CONN	109176 //���ݿ����Ӵ���
#define E_ELEC_CARD	109177 //һ��ͨ�˺��뷿�䲻��Ӧ
#define E_ELEC_ROOM	109178 // �����ڵķ���
#define E_ELEC_WORKSTAT 109179 //�����ڹ���վ
#define E_ELEC_DATA	109180 //����У�����
#define E_ELEC_DATA_LOSS 109181 //���ݶ�ʧ
#define E_ELEC_UNKNOW	109182 //δ֪����
#define E_TRANS_REQUEST 109183 //������ʧ��
#define E_TRANS_CONNECT 109184 //��������ʧ��
#define E_TRANS_NOT_CONNECT 109185 //�����������
#define E_TRANS_TIME_OUT 109186 //����ʱ��Ӧ��


#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;

int F250002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;

	char host[21]="";		//�Է�������ip
	short port=0;			
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	CTcpSocket tcpsocket ;
	ext_elect_req_t  ElectTrans;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SADDR,F_SSECTYPES,0);

	strcpy(host,rPack->scust_auth);
	port=rPack->lvol0;
	memset(&ElectTrans,0,sizeof(ElectTrans));
    memcpy(&ElectTrans, rPack->ssectypes,142);

	g_LogFile.WriteLogEx(1001,"Connect to electricity system ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		g_LogFile.WriteLogEx(1001,"Connect to electricity system error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		*pRetCode=E_TRANS_CONNECT;
		goto l_ret;
	}
	//printf("send:[%s]\n",(char*)&ElectTrans);
	ret = tcpsocket.Send((char*)&ElectTrans,sizeof(ElectTrans));
	if (ret<0)
	{
	      	// ����ʱ���˿������⣬�������ر�
		g_LogFile.WriteLogEx(1001,"Send to electricity system error,error code is [%d] ",ret);
		*pRetCode=E_TRANS_REQUEST;
		goto l_ret;
	}
	else if(0==ret){
		// ��Ӧ�ó����������
	    g_LogFile.WriteLogEx(1001,"Send to electricity system error��CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		*pRetCode=E_TRANS_REQUEST;
	    goto l_ret;
	}
	memset(&ElectTrans,0,sizeof(ElectTrans));
	if(rPack->lvol1==1)
	{//��ʽ����
		ret = tcpsocket.Recv((char*)&ElectTrans, sizeof(ElectTrans), 15000);		
		tcpsocket.Close();
		if (ret!=142)
		{
			g_LogFile.WriteLogEx(1001,"Receive from electricity system error,error code is [%d] ",ret);
			*pRetCode=E_TRANS_TIME_OUT;
			goto l_ret;  // ����ʱ�������ʱ
		}
		//printf("trans recv:[%s]\n",(char*)&ElectTrans);
		if(strncmp(ElectTrans.retnum,"0001",4)==0
			|| strncmp(ElectTrans.retnum,"0410",4) == 0){
			//�ɹ�, �����ˮ���Ѿ����ڣ���ôҲ��Ϊת�˳ɹ�
			g_LogFile.WriteLogEx(1001,"ת�˳ɹ� ret[%4s] ",ElectTrans.retnum);
		}else if(strncmp(ElectTrans.retnum,"0400",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DATA;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0401",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DB_CONN;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0402",4)==0){
			//һ��ͨ�ʺ��뷿�䲻��Ӧ
			g_LogFile.WriteLogEx(1001,"trans success but ret[%4s] ",ElectTrans.retnum);
			sprintf(out_pack->saddr,ElectTrans.room,20);
		}else if(strncmp(ElectTrans.retnum,"0403",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_ROOM;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0404",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_WORKSTAT;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0406",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DATA_LOSS;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0407",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_UNKNOW;
			goto l_ret;	
		}
		else
		{
			g_LogFile.WriteLogEx(1001,"unknown error ,trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode = E_ELEC_UNKNOW;
			goto l_ret;
		}
	}else{
		ret=tcpsocket.Recv((char*)&ElectTrans, sizeof(ElectTrans), 15000);
		tcpsocket.Close();
		if (ret!=142)
		{
			g_LogFile.WriteLogEx(1001,"Receive from electricity system error,error code is [%d] ",ret);
			*pRetCode=E_TRANS_TIME_OUT;
			goto l_ret;  // ����ʱ�������ʱ
		}
		//printf("query recv:[%s]\n",(char*)&ElectTrans);	
		if(strncmp(ElectTrans.retnum,"0001",4)==0){
			//�ɹ�
			g_LogFile.WriteLogEx(1001,"��ѯ�ɹ� ret[%4s] ",ElectTrans.retnum);
		}else if(strncmp(ElectTrans.retnum,"0400",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DATA;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0401",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DB_CONN;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0402",4)==0){
			//һ��ͨ�ʺ��뷿�䲻��Ӧ
			g_LogFile.WriteLogEx(1001,"query success but ret[%4s] ",ElectTrans.retnum);
			sprintf(out_pack->saddr,ElectTrans.room,20);
		}else if(strncmp(ElectTrans.retnum,"0403",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_ROOM;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0404",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_WORKSTAT;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0406",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DATA_LOSS;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0407",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_UNKNOW;
			goto l_ret;	
		}
		else
		{
			g_LogFile.WriteLogEx(1001,"unknown error, query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_UNKNOW;
			goto l_ret;	
		}
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
l_ret:
	return -1;
}

#ifdef __cplusplus
}
#endif
