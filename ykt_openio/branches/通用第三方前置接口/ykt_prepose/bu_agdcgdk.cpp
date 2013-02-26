#include "stdafx.h"
#include <ctype.h> 
#include <windows.h>
#include   <time.h>
#include <stdio.h>
#include "bu_agdsjsw.h"
#include "kst_struct.h"
#include "publicfunc.h"
#include "https.h"

int Do_Agdcgdk_Que(char * getdata,vector<SSocketInfo> &vecSockInfo,int idx)
{
        _variant_t  vsql;
		_variant_t connstr;
		string	httpstring;
		char xiaoqu_id[30]="";
		char room_id[30]="";
	    char urldata[30]="";
		char logstr[1024]="";
		char rcvquerydata[1024]="";
		char senddata[1024]="";
		char *rtstr=NULL;
		SSocketInfo *sockInfo = &vecSockInfo[idx];
		_ConnectionPtr m_pConnection;
		_RecordsetPtr pPtr;
		int ret=0;
		kst_ald_sqr kstquery;
		memset(&kstquery,0,sizeof(kstquery));
		queryald query;
		memset(&query,0,sizeof(query));
		queryaldrec  rcvquery;
		memset(&rcvquery,0,sizeof(rcvquery));
		
			getkst_ald_sqr(getdata,kstquery);
			if (connsqlsign==1)
			{
					strcpy(rcvquery.account,kstquery.stdu);
					strcpy(rcvquery.station,"2");
					 makekstsqldata(rcvquery,rcvquerydata);
					 vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
					return -1;
			}
		
		   ::CoInitialize(NULL);///初始化COM库
		  ret=m_pConnection.CreateInstance("ADODB.Connection");//建立实例返回HRESULT 所以最好if一下看看成功否
				if (ret)
				{
					strcpy(rcvquery.account,kstquery.stdu);
			    strcpy(rcvquery.station,"2");
				 makekstsqldata(rcvquery,rcvquerydata);
				 vecSockInfo[idx].eCurOp =ExecCmd;
				strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
					WriteLog("Create Instance failed!");
					return -1 ;
				}
   				if (FAILED(pPtr.CreateInstance("ADODB.Recordset")))
				{
					strcpy(rcvquery.account,kstquery.stdu);
			    strcpy(rcvquery.station,"2");
				 makekstsqldata(rcvquery,rcvquerydata);
				 vecSockInfo[idx].eCurOp =ExecCmd;
				strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
					WriteLog("Create Instance failed!");
					return -1 ;
				}
		_bstr_t connnect=Connectstr;
		try
		{
			char sqlstr[1024]= "select count(*) as num from kd_room where room=";
			strcat(sqlstr,kstquery.roomname);
			vsql.SetString(sqlstr);
			connstr.SetString(Connectstr);
			_bstr_t bsql=sqlstr;
			m_pConnection->ConnectionString=Connectstr;
			try
			{
					if (FAILED(m_pConnection->Open(connnect,"","",-1)))
					{ 
						
						
					}
			}
			catch(_com_error e)
			{
					 strcpy(rcvquery.account,kstquery.stdu);
					 strcpy(rcvquery.station,"2");
					 makekstsqldata(rcvquery,rcvquerydata);
					 vecSockInfo[idx].eCurOp =ExecCmd;
					 strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
					 if (connsqlsign==1)
					 {    
						EnterCriticalSection(&g_cs);
						connsqlsign=1;
						LeaveCriticalSection(&g_cs);
					 }
					
					return -1;
			}
			 m_pConnection->Close();
		//	 m_pConnection->Release();
			try
			{
					if(FAILED(pPtr->Open(vsql,connstr,adOpenStatic,adLockOptimistic,adCmdText)))
					{
					WriteLog("Open table failed!");
					pPtr->Close();
					return -1;
					}
			}
			catch(_com_error e)
			{
					strcpy(rcvquery.account,kstquery.stdu);
					strcpy(rcvquery.station,"2");
					 makekstsqldata(rcvquery,rcvquerydata);
					 vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
					pPtr->Close();
					return -1;
			}
			 strcpy(rcvquery.type,"1000");
			if (!pPtr->GetadoEOF())
			{	
				 _variant_t varnum;
				 varnum = pPtr->GetCollect ("num");
				// sprintf(rcvquery.money,"%lf",varmoney.dblVal);
				 strcpy(rcvquery.account,kstquery.stdu);
				 if( varnum.intVal!=1)
				 {  if (varnum.intVal!=0)
					{
					strcpy(rcvquery.retnum,"1111");
					}
					else
					{
					 strcpy(rcvquery.retnum,"1112");
					}
				 }
				 else
				 {
				 strcpy(rcvquery.retnum,"0001");
				 }
				 makekstsqldata(rcvquery,rcvquerydata);
				 vecSockInfo[idx].eCurOp =ExecCmd;
				 strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
				 pPtr->Close();
				 return -1;
			}
			else
			{	
				 strcpy(rcvquery.account,kstquery.stdu);
				 strcpy(rcvquery.station,"2");
				 makekstsqldata(rcvquery,rcvquerydata);
				 vecSockInfo[idx].eCurOp =ExecCmd;
				strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
				pPtr->Close();
				return -1;
			}
			//pPtr->Release();
		}
		catch (exception& e)
		{
			strcpy(logstr,e.what());
			WriteLog(logstr);
		}
	return 0;
}

int Do_Agdcgdk_Pay(char * getdata,vector<SSocketInfo> &vecSockInfo,int idx)
{
	char logstr[1024]="";
	char rcvquerydata[1024]="";
	_variant_t  vsql;
	_variant_t connstr;
	string	httpstring;
	char xiaoqu_id[30]="";
	char room_id[30]="";
	int ret=0;
	double money=0.0;
	kst_ald_pay kstpay;
	memset(&kstpay,0,sizeof(kstpay));
	payelect pay;
	memset(&pay,0,sizeof(pay));
	payelect recpay;
	memset(&recpay,0,sizeof(recpay));
	kst_ald_sqr kstquery;
	memset(&kstquery,0,sizeof(kstquery));
	_ConnectionPtr m_pConnection;
	_RecordsetPtr pPtr;
	SSocketInfo *sockInfo = &vecSockInfo[idx];
	try
	 {
			getkst_ald_pay(getdata,kstpay);
			if (connsqlsign==1)
			{
				strcpy(recpay.retnum,"-1");
				makekstpaydata(recpay,rcvquerydata);
				WriteLog(rcvquerydata);
				vecSockInfo[idx].eCurOp =ExecCmd;
				strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
				return -1;
			}	
			 ::CoInitialize(NULL);///初始化COM库
			 ret=m_pConnection.CreateInstance("ADODB.Connection");//建立实例返回HRESULT 所以最好if一下看看成功否
			if (ret)
			{
				strcpy(recpay.retnum,"-1");
				makekstpaydata(recpay,rcvquerydata);
				WriteLog(rcvquerydata);
				vecSockInfo[idx].eCurOp =ExecCmd;
				strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));	
				WriteLog("Create Instance failed!");
				 return -1;
			}
   			if (FAILED(pPtr.CreateInstance("ADODB.Recordset")))
			{
				strcpy(recpay.retnum,"-1");
				makekstpaydata(recpay,rcvquerydata);
				 WriteLog(rcvquerydata);
				vecSockInfo[idx].eCurOp =ExecCmd;
				strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata)); 
				WriteLog("Create Instance failed!");
				return -1 ;
			}
				m_pConnection->ConnectionString=Connectstr;
				_bstr_t conn=Connectstr;
				try
				{
					if (FAILED(m_pConnection->Open(conn,"","",-1)))
					{ 
						
					}
			//		 m_pConnection->Close();
				}
				catch(_com_error e)
				{
					strcpy(recpay.retnum,"-1");
					makekstpaydata(recpay,rcvquerydata);
					 WriteLog(rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
					 if (connsqlsign==1)
						 {    
							EnterCriticalSection(&g_cs);
							connsqlsign=1;
							LeaveCriticalSection(&g_cs);
						 }
					
						 return -1;
				}

	
				//char sqlstr[1024]= "select xiaoqu_id,room_id from kd_room where room_id=";
				char sqlstr[1024]= "select * from kd_room where room=";
				strcat(sqlstr,kstpay.payaccount);//房间号
				_variant_t  queryql;
				queryql.SetString(sqlstr);
				connstr.SetString(Connectstr);
				try
				{
					if(FAILED(pPtr->Open(queryql,connstr,adOpenStatic,adLockOptimistic,adCmdText)))
					{
					WriteLog("Open table failed!");
					
					return -1;
					}
				}
				catch(_com_error e)
				{
					strcpy(recpay.retnum,"-1");
					makekstpaydata(recpay,rcvquerydata);
					 WriteLog(rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
					
					 return -1;
				}
				if(!pPtr->GetadoEOF())
				{
					_variant_t varxiaoqu_id;
					_variant_t varroom_id;
					varxiaoqu_id = pPtr->GetCollect ("xiaoqu_id");
					varroom_id = pPtr->GetCollect ("room_id");
					sprintf(xiaoqu_id,"%d", varxiaoqu_id.intVal);
					sprintf(room_id,"%d", varroom_id.intVal);
					pPtr->Close();
				}
				//pPtr->Release();
				char datetime[30]="";
				char temp[32]="";
				char sqlinsstr[1024]="Insert into kd_tmp(buyer_id,xiaoqu_id,room_id,tranamt,endatatime,custsn) values(";
				strcat(sqlinsstr,"'");
				strcat(sqlinsstr,kstpay.stdu);
				strcat(sqlinsstr,"'");
				strcat(sqlinsstr,",");
				strcat(sqlinsstr,xiaoqu_id);
				strcat(sqlinsstr,",");
				strcat(sqlinsstr,room_id);
				strcat(sqlinsstr,",");
				if (strlen(kstpay.payamt)>0)
				{
				money=atoi(kstpay.payamt)/100;
				memset(kstpay.payamt,0,sizeof kstpay.payamt);
				itoa(money,kstpay.payamt,10);
				}
				strcat(sqlinsstr,kstpay.payamt);
				strcat(sqlinsstr,",");
				strcat(sqlinsstr,"convert(char(100),GETDATE(),20)");
				strcat(sqlinsstr,",");
				strcat(sqlinsstr,"'");
				strcat(sqlinsstr,kstpay.paycode);
				strcat(sqlinsstr,"'");
				strcat(sqlinsstr,")");
				_bstr_t bsinstrql=sqlinsstr;
				_variant_t vtOptional;
				WriteLog(sqlinsstr);
				strcpy(recpay.account,kstquery.stdu);
				strcpy(recpay.type,"1001");
//				m_pConnection->Close();
				if (FAILED(m_pConnection->Execute(bsinstrql,&vtOptional,-1)))
				{
					strcpy(recpay.retnum,"-1");
					makekstpaydata(recpay,rcvquerydata);
					WriteLog(rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
				}
				else
				{
					strcpy(recpay.retnum,"0001");
					makekstpaydata(recpay,rcvquerydata);
					WriteLog(rcvquerydata);
					vecSockInfo[idx].eCurOp =ExecCmd;
					strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(rcvquerydata));
				}
				m_pConnection->Close();
			//	m_pConnection->Release();
		 }
		catch (exception& e)
		{
			strcpy(logstr,e.what());
			WriteLog(logstr);
		}
	return 0;
}