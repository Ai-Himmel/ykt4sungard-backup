/* ----------------------------------------------------------
 * �������ƣ�F1002.cpp
 * �������ڣ�2008-1-16
 * �������ߣ������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��������нӿ�
 * ----------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mypub.h"  
#include "cpack.h"
#include "svrlink.h"
#include "pubfunc.h"
#include "bupub.h"
#include "mystring.h"
#include "httppost.h"
#include "ksbu.h"
#include "cibtrans.h"
#define MSG_HEAD_LEN 6

int sendRecvData(char *host, short port,int timeout,
					string &sendData,string &recvData,int *pRetCode,char *szMsg)
{
	CTcpSocket  tcpSocket;
	int ret;
	char szBufLen[MSG_HEAD_LEN + 1] = "";
	int msgLen;
	if(!tcpSocket.ConnectTcp(host,port))
	{
		*pRetCode=9999;
		sprintf(szMsg,"������������IP[%s]Port[%d] ʧ��",host,port);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	ret = tcpSocket.Send((char*)sendData.c_str(),sendData.length());
	if(ret!=sendData.length())
	{
		*pRetCode=9999;
		sprintf(szMsg,"�������ݵ���������IP[%s]Port[%d] ʧ��",host,port);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	
	ret = tcpSocket.Recv(szBufLen, MSG_HEAD_LEN, timeout);		
	if(ret<0)
	{
		char errBuf[256];
		*pRetCode=9999;
		tcpSocket.GetLastError(errBuf);
		sprintf(szMsg,"����������IP[%s]Port[%d] ��������ʧ��,errMsg:[%s]",host,port,errBuf);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	msgLen = atol(szBufLen);
	if(msgLen < 1)
	{
		sprintf(szMsg,"����������IP[%s]Port[%d] ��������ʧ��",host,port);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	char *pRcvBuf=(char*)malloc(msgLen+1);
	if(!pRcvBuf)
	{
		*pRetCode=-1;
		sprintf(szMsg,"Ϊ���������н��յ����ݷ���ռ�ʧ��");
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	ret = tcpSocket.Recv(pRcvBuf, msgLen, timeout);		
	if(ret<0)
	{
		char errBuf[256];
		*pRetCode=9999;
		tcpSocket.GetLastError(errBuf);
		sprintf(szMsg,"����������IP[%s]Port[%d] ��������ʧ��,errMsg:[%s]",host,port,errBuf);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		free(pRcvBuf);		
		return -1;
	}
	tcpSocket.Close();
	
	string resCode = string(pRcvBuf,6);
	if(resCode != "000000")
	{
	  *pRetCode=9999;
	  sprintf(szMsg,"���������л�õ�ǩ����������");
	      cout<<szMsg<<endl;
	  writelog(LOG_ERR,szMsg);
	  free(pRcvBuf);      
	  return -1;
	}

	pRcvBuf[msgLen] = 0;
	recvData = string(pRcvBuf+6);
	free(pRcvBuf);
	return 0;
	
}

int F1002(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;
	
	writelog(LOG_ERR,"call F1002\n");
	*pRetCode=-1;
	ST_CPACK aPack;			
	
	CCibTrans   CibTran(in_pack);
	CCibTrans *pTrans = &CibTran;
	if(!pTrans->AssignReqHead())
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	pTrans->prepare();
	if(!pTrans->replaceTemlateVarValue())
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	string signReqData ;
	if(!pTrans->buildSignData(signReqData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	  	cout<<szMsg<<endl;
		return -1;
	}
	if(pTrans->debug)
		cout<<"signReqData: "<<signReqData<<endl;
		
	string transCode = pTrans->getTranCode();
	
	string signedData;	
	
	ret = sendRecvData((char*)pTrans->pBank->getNCSign().ip.c_str(),pTrans->pBank->getNCSign().port,
				   pTrans->pBank->getNCSign().timeout*1000,	signReqData,signedData,pRetCode,szMsg);
	
	if(ret !=0 )
		return -1;	
	
	CHttpPost httpPost;
	httpPost.init();	
	if(pTrans->debug)
		httpPost.setDebug();
	httpPost.headAppend("Content-Type: text/plain");
	httpPost.headAppend(string("USER_ID: ")+ pTrans->reqHead.userID);
	httpPost.headAppend("ensignRQ: true");
	httpPost.headAppend("ensignRS: true");	
	httpPost.headAppend("TRAN_CODE: " + pTrans->getTranCode());
	httpPost.headSetopt();
	httpPost.setTimeout(pTrans->pBank->getNCService().timeout);
	httpPost.httpSetProxyHostPort((char*)pTrans->pBank->getProxyHostPort().c_str());
//	httpPost.httpSetProxyUserPwd((char*)pTrans->pBank->getProxyUserPwd().c_str());
	if(pTrans->debug)
	{
		cout<<"����"<<pTrans->pTrans->_transName<<"����"<<pTrans->pBank->getBankName()<<endl;
		cout<<"bankReqData: "<<signedData<<endl;
	}
	if(!httpPost.httpPostData(pTrans->pBank->getNCService().url, signedData))   
	{
		*pRetCode=9999;
		sprintf(szMsg,"%s(%s)",httpPost.getCurlErrMsg().c_str(),httpPost.getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}	
	string& bankRepData=httpPost.getContent(); 
	
	if(pTrans->debug)
		cout<<"bankRepData:\n"<<bankRepData.c_str()<<endl;

	string verifyData;
	if(!pTrans->buildVerifyData(bankRepData,verifyData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	if(pTrans->debug)
		cout<<"verifyData: "<<verifyData.c_str()<<endl;
	string bankSignedData;
	ret = sendRecvData((char*)pTrans->pBank->getNCVerify().ip.c_str(),pTrans->pBank->getNCVerify().port,
				   pTrans->pBank->getNCVerify().timeout*1000,verifyData,bankSignedData,pRetCode,szMsg);

	if(ret !=0 )
		return -1;		
	if(pTrans->debug)
		cout<<"bankSignedData:\n"<<bankSignedData<<endl;			
	
		
	string bankData;
	if(!pTrans->parseVerifyBankSignedData(bankSignedData,bankData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}	
	
	if(!pTrans->buildResponseData(handle,bankData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	*pRetCode=0;
	return 0;
}

