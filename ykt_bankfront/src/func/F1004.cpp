/* ----------------------------------------------------------
 * �������ƣ�F1004.cpp
 * �������ڣ�2008-1-18
 * �������ߣ������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ���ͨ���нӿ�
 * ----------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <syslog.h>
#include "mypub.h"  
#include "cpack.h"
#include "svrlink.h"
#include "pubfunc.h"
#include "bupub.h"
#include "mystring.h"
#include "httppost.h"
#include "ksbu.h"
#include "bcomtrans.h"
int F1004(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;

	*pRetCode=-1;
	ST_CPACK aPack;		
	CTcpSocket  tcpSocket;
	CBcomTrans   BcomTran(in_pack);
	CTrans *pTrans = &BcomTran;
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
	
	string signReqData;
	if(!pTrans->buildSignData(signReqData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	if(pTrans->debug)
		cout<<"signReqData: "<<signReqData.c_str()<<endl;
	

	if(!tcpSocket.ConnectTcp((char*)pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port))
	{
		*pRetCode=9999;
		sprintf(szMsg,"���ӽ�ͨ����IP[%s]Port[%d] ʧ��",pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	ret = tcpSocket.Send((char*)signReqData.c_str(),signReqData.length());
	if(ret!=signReqData.length())
	{
		*pRetCode=9999;
		sprintf(szMsg,"�������ݵ���ͨ����IP[%s]Port[%d] ʧ��",pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	
	char szBufLen[8]="";
	int timout=pTrans->pBank->getNCService().timeout*1000;
	ret = tcpSocket.Recv(szBufLen, 7, timout);		
	if(ret<=0)
	{
		*pRetCode=9999;
		sprintf(szMsg,"�ӽ�ͨ����IP[%s]Port[%d] ��������ʧ��",pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	if(pTrans->debug)
		cout<<"���ĳ��� : "<<szBufLen<<endl;
	int len = atol(szBufLen+1);
	
	char *pRcvBuf=(char*)malloc(len+1);
	if(!pRcvBuf)
	{
		*pRetCode=9999;
		sprintf(szMsg,"�ӽ�ͨ����IP[%s]Port[%d] ��������ʧ��",pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		free(pRcvBuf);
		return -1;
	}
	ret = tcpSocket.Recv(pRcvBuf, len, timout);		
	if(ret<0)
	{
		char errBuf[256];
		*pRetCode=9999;
		tcpSocket.GetLastError(errBuf);
		sprintf(szMsg,"�ӽ�ͨ����IP[%s]Port[%d] ��������ʧ��,errMsg:[%s]",pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port,errBuf);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		free(pRcvBuf);		
		return -1;
	}
	tcpSocket.Close();
	pRcvBuf[len] = 0;
	if(pTrans->debug)
		cout<<pRcvBuf<<endl;
	
	string bankVerifyData(pRcvBuf,len);	
	free(pRcvBuf);
	
	string bankData;
	if(!pTrans->parseVerifyBankSignedData(bankVerifyData,bankData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	if(pTrans->debug)
		cout<<"bankData: "<<bankData<<endl;
	if(!pTrans->buildResponseData(handle,&aPack,bankData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	*pRetCode=0;

	return 0;
}
