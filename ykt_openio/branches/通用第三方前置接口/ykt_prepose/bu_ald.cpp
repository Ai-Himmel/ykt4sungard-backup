#include "stdafx.h"
#include "bu_ald.h"
#include "kst_struct.h"
#include "publicfunc.h"
#include "tcp.h"
int Do_Aldwork_Que(char * getdata,vector<SSocketInfo> &vecSockInfo,int idx)
{
		char sddt[1024]="";
		size_t offset=0;
		char logstr[1024]="";
		char rcvquerydata[1024]="";
		unsigned  char  inmd5[67]="";
		unsigned char soutmd5[32]="";
		char signature[33]="";
		char temp[256]="";
		char senddata[1024]="";
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
			getkst_ald_sqr(getdata,kstquery);
			EnterCriticalSection(&g_cs);
			makequerysenddata(query ,kstquery);
			LeaveCriticalSection(&g_cs);
		}
		catch (exception& e)
		{
			strcpy(logstr,e.what());
			WriteLog(logstr);
		}
		if (strncmp(school,"yjz",3)!=0)//是否云交职
		{
				ret = tcpsocket.ConnectTcp(remotehost, remoteport,logstr);
				if (ret!=1)
				{
					WriteLog(logstr);
					memset(logstr,0,sizeof logstr);
					strcpy(rcvquery.type,"1000");
					strcpy(rcvquery.retnum,"5");
					try
					{
						makekstsqldata(rcvquery,rcvquerydata);
						vecSockInfo[idx].eCurOp =ExecCmd;
						strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
					}
					catch (exception& e)
					{
						strcpy(logstr,e.what());
						WriteLog(logstr);
					}
					return -1;
				}
				//

				 memcpy(sddt,query.discern,1);
				 offset=offset+1;
				 memcpy(sddt+offset,query.length,4);
				 offset=offset+4;
				 memcpy(sddt+offset,query.type,4);
				 memcpy(inmd5+0,query.type,4);
				 offset=offset+4;
				 memcpy(sddt+offset,query.bitmap,16);
				 memcpy(inmd5+4,query.bitmap,16);
				 offset=offset+16;
				 memcpy(sddt+offset,addrightsqace(query.roomname,20),20);
				  memcpy(inmd5+20,addrightsqace(query.roomname,20),20);
				 offset=offset+20;
				 memcpy(sddt+offset,addrightsqace(kstquery.stdu,22),22);
				 memcpy(inmd5+42,addrightsqace(kstquery.stdu,22),22);
				 offset=offset+22;
				 //
				 memset(temp,0,sizeof temp);
				 memcpy(sddt+offset,addleftzero(temp,7),7);
				 offset=offset+7;
				  memset(temp,0,sizeof temp);
				 memcpy(sddt+offset,addleftzero(temp,10),10);
				 offset=offset+10;
				  memset(temp,0,sizeof temp);
				 memcpy(sddt+offset,addleftzero(temp,18),18);
				 offset=offset+18;
				 //
				// memcpy(sddt+offset,addrightsqace(query.Correspondence,1),1);
				// memcpy(inmd5+43,addrightsqace(query.Correspondence,1),1);
				// offset=offset+1;
				  memcpy(sddt+offset,addrightsqace(temp,4),4);
				  memcpy(inmd5+43,addrightsqace(temp,4),4);
				 offset=offset+4;
				 memcpy(sddt+offset,addrightsqace(query.station,4),4);
				 memcpy(inmd5+47,addrightsqace(query.station,4),4);
				 offset=offset+4;
				  CalcMD5(inmd5,sizeof(inmd5),soutmd5);
				 dec2hex(soutmd5,16,signature);
				 memcpy(sddt+offset,addleftzero(signature,32),32);
				 offset=offset+32;
				ret = tcpsocket.Send((char*)&sddt,strlen(sddt));
				//
				//ret = tcpsocket.Send((char*)&query,sizeof(query));
				if (ret<0)
				{
					WriteLog("发送数据失败！");
				}
				ret=tcpsocket.Recv((char*)&rcvquery, sizeof(rcvquery), 15000);	
 				if (ret!=188) //188
				{
						WriteLog("数据接收失败！");
						strcpy(rcvquery.type,"1000");
						strcpy(rcvquery.retnum,"5");
					try
						{
							makekstsqldata(rcvquery,rcvquerydata);
							vecSockInfo[idx].eCurOp =ExecCmd;
							 strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
						}
					catch (exception& e)
						{
							strcpy(logstr,e.what());
							WriteLog(logstr);
						}
					return -1;
				}
				else
				{
					strcpy(rcvquery.type,"1000");
					makekstsqldata(rcvquery,rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
				}
		}
		else
		{
			ret = tcpsocket.ConnectTcp(remotehost, remoteport,logstr);
			if (ret!=1)
			{
				WriteLog(logstr);
				memset(logstr,0,sizeof logstr);
				strcpy(rcvquery.type,"1000");
				strcpy(rcvquery.retnum,"5");
				try
				{
					makekstsqldata(rcvquery,rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
				}
				catch (exception& e)
				{
					strcpy(logstr,e.what());
					WriteLog(logstr);
				}
				return -1;
			}
             memset(sddt,0,sizeof sddt);
			 memset(temp,0,sizeof temp);
			 strcpy(temp,"0014100010000000000000000");
			 memcpy(sddt,temp,25);
             memcpy(sddt+25,query.roomname,20);
			 memset(temp,0,sizeof temp);
             strcpy(temp,"0014100010000000000000000");
             memcpy(sddt+25+45,temp,29);
			 memset(temp,0,sizeof temp);
			 strcpy(temp,"1                     000000012041736210000000000000000000000000100000000000000000000000000000000");
			 memcpy(sddt+25+45+74,temp,97);
			ret = tcpsocket.Send((char*)&sddt,strlen(sddt));
			if (ret<0)
			{
				WriteLog("发送数据失败！");
			}
			memset(senddata,0,sizeof senddata);
			ret=tcpsocket.Recv(senddata, 142, 15000);	
			if (ret!=142) //188
			{
				WriteLog("数据接收失败！");
				strcpy(rcvquery.type,"1000");
				strcpy(rcvquery.retnum,"5");
				try
				{
					makekstsqldata(rcvquery,rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
				}
				catch (exception& e)
				{
					strcpy(logstr,e.what());
					WriteLog(logstr);
				}
				return -1;
			}
			else
			{
				memcpy(rcvquery.retnum,senddata+102,4);
				if (strncmp(rcvquery.retnum,"0402",4)==0)
				{
				 memcpy(rcvquery.retnum,"0001",4);
				}
				strcpy(rcvquery.type,"1000");
				makekstsqldata(rcvquery,rcvquerydata);
				vecSockInfo[idx].eCurOp =ExecCmd;
				strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
			}
		}
      
		tcpsocket.Close();
	
	return 0;
}

int Do_Aldwork_Pay(char * getdata,vector<SSocketInfo> &vecSockInfo,int idx)
{
	char logstr[1024]="";
	char rcvquerydata[1024]="";
	int ret=0;
	kst_ald_pay kstpay;
	memset(&kstpay,0,sizeof(kstpay));
	payelect pay;
	memset(&pay,0,sizeof(pay));
	payelect recpay;
	memset(&recpay,0,sizeof(recpay));
	SSocketInfo *sockInfo = &vecSockInfo[idx];
	CTcpSocket tcpsocket ;
	try
			{
				EnterCriticalSection(&g_cs);
				getkst_ald_pay(getdata,kstpay);
				makepaysenddata(pay,kstpay);
				LeaveCriticalSection(&g_cs);
			}
		catch (exception& e)
			{
				strcpy(logstr,e.what());
				WriteLog(logstr);
			}
		ret = tcpsocket.ConnectTcp(remotehost, remoteport,logstr);
		if (ret!=1)
		{
			WriteLog(logstr);
			strcpy(recpay.type,"1001");
			strcpy(recpay.retnum,"5");
			try
				{
				makekstpaydata(recpay,rcvquerydata);
				vecSockInfo[idx].eCurOp =ExecCmd;
				strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
				}
			catch (exception& e)
				{
				strcpy(logstr,e.what());
				WriteLog(logstr);
				}
			return -1;
		}
		ret = tcpsocket.Send((char*)&pay,sizeof(pay));
	    if (ret<0)
		{
			WriteLog("发送数据失败！");
		}
		ret=tcpsocket.Recv((char*)&recpay, sizeof(recpay), 150000);	
		if (ret!=142)
		{
			WriteLog("数据接收失败！");
			strcpy(recpay.type,"1001");
			strcpy(recpay.retnum,"5");
			try
				{
					makekstpaydata(recpay,rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
				}
			catch (exception& e)
				{
					strcpy(logstr,e.what());
					WriteLog(logstr);
				}
		}
		else
		{
			strcpy(recpay.type,"1001");
			makekstpaydata(recpay,rcvquerydata);
			vecSockInfo[idx].eCurOp =ExecCmd;
			strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
		}
       
		tcpsocket.Close();
	return 0;
}

int Do_Aldwork_Rvs(char * getdata,vector<SSocketInfo> &vecSockInfo,int idx)
{
	char logstr[1024]="";
	char rcvquerydata[1024]="";
	int ret=0;
	payelect pay;
	memset(&pay,0,sizeof(pay));
	payelect recpay;
	memset(&recpay,0,sizeof(recpay));
	kst_ald_rvs kstrvs;
	memset(&kstrvs,0,sizeof(kstrvs));
	SSocketInfo *sockInfo = &vecSockInfo[idx];
	CTcpSocket tcpsocket ;
	try
			  {
				getkst_ald_rvs(getdata,kstrvs);
				makervssenddata(pay,kstrvs);
				ret = tcpsocket.ConnectTcp(remotehost, remoteport,logstr);
				if (ret)
				{
					WriteLog(logstr);
					return -1;
				}
				ret = tcpsocket.Send((char*)&pay,sizeof(pay));
				if (ret<0)
				{
					WriteLog("发送数据失败！");
				}
					ret=tcpsocket.Recv((char*)&recpay, sizeof(recpay), 1500000);	
				if (ret!=142)
				{
					WriteLog("数据接收失败！");
					return -1;
				}
				else
				{
					strcpy(recpay.type,"1002");
					makekstrecdata(recpay,rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
				}
		       
				tcpsocket.Close();
			}
			catch (exception& e)
			{
					strcpy(logstr,e.what());
					WriteLog(logstr);
			}
	return 0;
}