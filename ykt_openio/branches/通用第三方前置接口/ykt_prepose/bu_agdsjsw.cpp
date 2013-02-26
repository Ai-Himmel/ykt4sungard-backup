#include "stdafx.h"
#include "bu_agdsjsw.h"
#include "kst_struct.h"
#include "publicfunc.h"
#include "https.h"
int Do_Agdsjsw_Que(char * getdata,vector<SSocketInfo> &vecSockInfo,int idx)
{
		SYSTEMTIME sys;
		GetLocalTime( &sys );
		char tmp[128]={0};

		sprintf(tmp,"[%4d/%02d/%02d %02d:%02d:%02d] �����˿�ʼ\n",
			sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond); 

		WriteLog(tmp);
		printf(tmp);

	    char urldata[30]="";
		char logstr[1024]="";
		char rcvquerydata[1024]="";
		char senddata[1024]="";
		char *rtstr=NULL;
		SSocketInfo *sockInfo = &vecSockInfo[idx];
		int ret=0;
		Agd_ThirdPay ThirdPay={0};
		memset(&ThirdPay,0,sizeof(ThirdPay));
		kst_ald_sqr kstquery={0};
		memset(&kstquery,0,sizeof(kstquery));
		queryald query={0};
		memset(&query,0,sizeof(query));
		queryaldrec  rcvquery={0};
		memset(&rcvquery,0,sizeof(rcvquery));
		try
			{
			 getkst_ald_sqr(getdata,kstquery);	
			 time_t   tmCurrent   =   time(NULL);
			 sprintf_s(urldata,"%ld",tmCurrent);
			// strcat(kstquery.trcd,kstquery.stdu);
			// strcat(kstquery.trcd,urldata);
			 strcpy(rcvquery.roomname,kstquery.roomname);
			 strcpy(rcvquery.money,kstquery.amt);
			 strcpy(rcvquery.account,kstquery.stdu);
			 strcpy(rcvquery.type,"1000");
			
			 ret=send_https_get_usename(kstquery,ThirdPay);
			 if (ret)
			{		
					WriteLog("��ȡ�û���Ϣʧ��");
					printf("��ȡ�û���Ϣʧ��\n");

					strcpy(rcvquery.signature,kstquery.area);
					strcpy(rcvquery.account,kstquery.stdu);
					strcpy(rcvquery.retnum,"0003");
					makekstsqldata(rcvquery,rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
					ret=sendhttpsdestory();
					return -1;
				
			 }

			 	
			ret=sendhttpsint();
			if (ret)
			{   
				 WriteLog("��ʼ��https����ʧ�ܣ�");
				 printf("��ʼ��https����ʧ�ܣ�\n");
				 strcpy(rcvquery.account,kstquery.stdu);
				 strcpy(rcvquery.retnum,"0002");
				 makekstsqldata(rcvquery,rcvquerydata);
				 vecSockInfo[idx].eCurOp =ExecCmd;
				 strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
				 ret=sendhttpsdestory();
				 return -1;
			}
			
			 ret=send_https_get_inpayamountid(kstquery,ThirdPay);
			 if (ret)
			{	
					WriteLog("������ʧ��");
					printf("������ʧ��\n");

					strcpy(rcvquery.account,kstquery.stdu);
					strcpy(rcvquery.signature,kstquery.area);
					strcpy(rcvquery.retnum,"0003");
					makekstsqldata(rcvquery,rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
					ret=sendhttpsdestory();
					return -1;
				
			 }
			else
			 { 
					WriteLog("�����˳ɹ�");
					printf("�����˳ɹ�\n");

					strcpy(rcvquery.retnum,"0001");
				    makekstsqldata(rcvquery,rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
					ret=sendhttpsdestory();
					return -1;
			 }

			
			}
			catch (exception& e)
		{
			strcpy(logstr,e.what());
			WriteLog(logstr);
		}
	return 0;
}

int Do_Agdsjsw_Pay(char * getdata,vector<SSocketInfo> &vecSockInfo,int idx)
{

	SYSTEMTIME sys;
	GetLocalTime( &sys );
	char tmp[128]={0};

	sprintf(tmp,"[%4d/%02d/%02d %02d:%02d:%02d] ��ʽ���˿�ʼ\n",
		sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond); 

	WriteLog(tmp);
	printf(tmp);

	char logstr[1024]="";
	char rcvquerydata[1024]="";
	int ret=0;
	char senddata[1024]="";
	char *rtstr=NULL;
	double money=0.0;
	kst_ald_pay kstpay;
	memset(&kstpay,0,sizeof(kstpay));
	payelect pay;
	memset(&pay,0,sizeof(pay));
	payelect recpay;
	memset(&recpay,0,sizeof(recpay));
	queryaldrec  rcvquery;
    memset(&rcvquery,0,sizeof(rcvquery));
	Agd_ThirdPay ThirdPay={0};
	sprintf(ThirdPay.status, "ʧ��");
	kst_ald_sqr kstquery;
	memset(&kstquery,0,sizeof(kstquery));
	SSocketInfo *sockInfo = &vecSockInfo[idx];


			try
			{

			 getkst_ald_pay(getdata,kstpay);

			char* str = get_payid_date(kstpay, ThirdPay); // ����
			free(str);

			 ret=sendhttpsint();
			 if (ret)
			 {
					WriteLog("��ʼ��ʧ��");
					printf("��ʼ��ʧ��\n");

					recodepaydata(ThirdPay);

					strcpy(recpay.retnum,"0003");
					makekstpaydata(recpay,rcvquerydata);
					WriteLog(rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
					return -1;
			 }
			 WriteLog("��ֵȷ�ϣ�");
			 ret=get_name_httpquest(kstpay,ThirdPay);

			 //��ó�ֵ��¼��
			 ret=get_pay_id(kstpay,ThirdPay);
			 strcpy(recpay.roomname,kstpay.payaccount);
			 strcpy(recpay.money,kstpay.payamt);
			// strcpy(recpay.roomname,kstpay.stdu);
			 strcpy(recpay.type,"1001");

			 if (ret)
				{
					recodepaydata(ThirdPay);
					WriteLog("��ó�ֵ��¼��ʧ��");
					printf("��ó�ֵ��¼��ʧ��\n");

					strcpy(recpay.retnum,"0003");
					makekstpaydata(recpay,rcvquerydata);
					WriteLog(rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
					 ret=sendhttpsdestory();
					return -1;
			   }

			ret=sendhttpsfix(kstpay,ThirdPay);
			strcpy(recpay.account,kstquery.roomname);
		    strcpy(recpay.type,"1001");
			 if (ret)
			{
				recodepaydata(ThirdPay);
				WriteLog("��ֵȷ��ʧ��");
				printf("��ֵȷ��ʧ��\n");
				strcpy(recpay.retnum,"0003");
				makekstpaydata(recpay,rcvquerydata);
				WriteLog(rcvquerydata);
				vecSockInfo[idx].eCurOp =ExecCmd;
				strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
				 ret=sendhttpsdestory();
                return -1;
			 }
			else
			{

				recodepaydata(ThirdPay);

				strcpy(recpay.retnum,"0001");
				makekstpaydata(recpay,rcvquerydata);
				WriteLog(rcvquerydata);
				vecSockInfo[idx].eCurOp =ExecCmd;
				strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));		
			 }

			 ret=sendhttpsdestory();

			WriteLog("�������");
			printf("�������\n");
		 }
		catch (exception& e)
		{
			strcpy(logstr,e.what());
			WriteLog(logstr);
		}
	return 0;
}
