#include "stdafx.h"
#include "bu_yzzsjsw.h"
#include "kst_struct.h"
#include "publicfunc.h"
#include "tcp.h"
int Do_Yzzsjsw_Que(char * getdata,vector<SSocketInfo> &vecSockInfo,int idx)
{
		char logstr[1024]="";
		char rcvquerydata[1024]="";
		char senddata[1024]="";
		char *rtstr=NULL;
		SSocketInfo *sockInfo = &vecSockInfo[idx];
		int ret=0;
		CTcpSocket tcpsocket ;
		kst_ald_sqr kstquery;
		memset(&kstquery,0,sizeof(kstquery));
		queryald query;
		memset(&query,0,sizeof(query));
		queryaldrec  rcvquery;
		memset(&rcvquery,0,sizeof(rcvquery));
		try
				{
					memset(senddata,0,sizeof senddata);
					getkst_ald_sqr(getdata,kstquery);
					strcat(senddata,"QUERYUSER:USERID=\"");
					strcat(senddata,kstquery.roomname);
					strcat(senddata,"\";");
					rtstr=sendnetpay(senddata);
					memset(&rcvquery,0,sizeof rcvquery);
					get_rj_query(rtstr,rcvquery);
					strcpy(rcvquery.type,"1000");
					memcpy(rcvquery.roomname,kstquery.roomname,sizeof rcvquery.roomname);
					makekstsqldata(rcvquery,rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
					tcpsocket.Close();
					WriteLog("查询结束");
				}
				catch (exception& e)
				{
					strcpy(logstr,e.what());
					WriteLog(logstr);
					tcpsocket.Close();
				}
	
	return 0;
}

int Do_Yzzsjsw_Pay(char * getdata,vector<SSocketInfo> &vecSockInfo,int idx)
{
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
	SSocketInfo *sockInfo = &vecSockInfo[idx];
		 try
			{
				WriteLog("开始入帐了");
				memset(senddata,0,sizeof senddata);
				getkst_ald_pay(getdata,kstpay);
				strcat(senddata,"PAY:USERID=\"");
				strcat(senddata,kstpay.payaccount);
				strcat(senddata,"\",FEE=\"");
				if (strlen(kstpay.payamt)>0)
				{
				money=atoi(kstpay.payamt)/100;
				memset(kstpay.payamt,0,sizeof kstpay.payamt);
				sprintf(kstpay.payamt,"%0.2f",money);//转化成元
				}
				strcat(senddata,kstpay.payamt);
				strcat(senddata,"\";");
				rtstr=sendnetpay(senddata);
				memset(&rcvquery,0,sizeof rcvquery);
				//get_rj_query(rtstr,rcvquery);
				strcpy(recpay.roomname,kstpay.stdu);
				strcpy(recpay.type,"1001");
			   if (strncmp(rtstr,"SUC;",3))
			   {
					strcpy(recpay.retnum,"0");
					makekstpaydata(recpay,rcvquerydata);
					WriteLog(rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
			   }
			   else
			   { 
					strcpy(recpay.retnum,"-1");
					makekstpaydata(recpay,rcvquerydata);
					WriteLog(rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
			   }
			 
			
			}
	 catch (exception& e)
		{
			strcpy(logstr,e.what());
			WriteLog(logstr);
	
		}
	return 0;
}

int Do_yzzsjsw_Propay(char * getdata,vector<SSocketInfo> &vecSockInfo,int idx)
{
	char logstr[1024]="";
	char rcvquerydata[1024]="";
	char senddata[1024]="";
	int ret=0;
	char *rtstr=NULL;
	double money=0.0;
	payelect recpay;
	memset(&recpay,0,sizeof(recpay));
	kst_ald_sqr kstquery;
	memset(&kstquery,0,sizeof(kstquery));
	SSocketInfo *sockInfo = &vecSockInfo[idx];
	try
		{
			memset(senddata,0,sizeof senddata);
			getkst_ald_sqr(getdata,kstquery);
			strcat(senddata,"PAYPREFEE:USERID=\"");
			strcat(senddata,kstquery.stdu);
			strcat(senddata,"\",FEE=\"");
			money=atoi(kstquery.amt)/100;
			sprintf(kstquery.amt,"%0.2f",money);//转化成元
			strcat(senddata,kstquery.amt);
			strcat(senddata,"\";");
			rtstr=sendnetpay(senddata);
			queryaldrec  rcvquery;
			memset(&rcvquery,0,sizeof(rcvquery));
			
			strcpy(recpay.roomname,kstquery.roomname);	
			strcpy(recpay.type,"1002");
		   if (strcpy(rtstr,"SUC;"))
		   {
			 strcpy(recpay.retnum,"0");
		     makekstpaydata(recpay,rcvquerydata);
			 WriteLog(rcvquerydata);
			 vecSockInfo[idx].eCurOp =ExecCmd;
			 strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
		   }
		   else
		   {
			 strcpy(recpay.retnum,"-1");
			 makekstpaydata(recpay,rcvquerydata);
			 WriteLog(rcvquerydata);
			 vecSockInfo[idx].eCurOp =ExecCmd;
			 strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
		   }
		
		  }
	 catch (exception& e)
		{
			strcpy(logstr,e.what());
			WriteLog(logstr);
		}
	return 0;
}