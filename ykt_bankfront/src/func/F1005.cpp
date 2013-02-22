/* ----------------------------------------------------------
 * 程序名称：F1005.cpp
 * 创建日期：2007-12-19
 * 程序作者：闻剑
 * 版本信息：1.0.0.0
 * 程序功能：建设银行接口
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
#include "ccbtrans.h"
#include <fstream>
#include <sstream>


int F1005(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	
	*pRetCode=-1;
	ST_CPACK aPack;	
	
	CCcbTrans   CcbTran(in_pack);
	CCcbTrans *pTrans = &CcbTran;
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

	CTcpSocket  tcpSocket;
	int ret = -1;
	string bankReqData,bankRepData;

	if(!pTrans->buildBankRequestData(pTrans->getTemplateData(),bankReqData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}

	if(pTrans->debug)
		cout<<"bankReqData : "<<bankReqData<<endl;

	if(!tcpSocket.ConnectTcp((char*)pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port))
	{
		*pRetCode=9999;
		sprintf(szMsg,"连接建设银行IP[%s]Port[%d] 失败",pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	ret = tcpSocket.Send((char*)bankReqData.c_str(),bankReqData.length());
	if(ret!=bankReqData.length())
	{
		*pRetCode=9999;
		sprintf(szMsg,"发送数据到建设银行IP[%s]Port[%d] 失败",pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}

	CCBMSGHEAD ccbMsgHead;
	char *pccbMsgHead =(char*) &ccbMsgHead;
	ret = tcpSocket.Recv(pccbMsgHead, sizeof(ccbMsgHead), pTrans->pBank->getNCService().timeout*1000);		
	if(ret<=0)
	{
		char errBuf[256];
		*pRetCode=9999;
		tcpSocket.GetLastError(errBuf);
		sprintf(szMsg,"从建设银行IP[%s]Port[%d] 接收数据失败,Error: %s\n",pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port,errBuf);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}

	if(pTrans->debug)
	{
		cout<<"length: "<< ccbMsgHead.msgDataLen<<"type: " <<ccbMsgHead.commMode<<endl;
		cout<<ccbMsgHead.txCode <<" curblock : "<<ccbMsgHead.curBlock<<"totalblock : "<<ccbMsgHead.totalBlock<<endl;
	}
	int len = atoi(ccbMsgHead.msgDataLen);
	char *pRcvBuf=(char*)malloc(len+1);
	
	ret = tcpSocket.Recv(pRcvBuf, len, pTrans->pBank->getNCService().timeout*1000);		
	if(ret<=0)
	{
		*pRetCode=9999;
		sprintf(szMsg,"从建设银行IP[%s]Port[%d] 接收数据失败",pTrans->pBank->getNCService().ip.c_str(),pTrans->pBank->getNCService().port);
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	
	tcpSocket.Close();
	pRcvBuf[len] =0;
	bankRepData = string(pRcvBuf,len);
	if(pTrans->debug)
		cout<<"报文: bankRepData:"<<bankRepData<<endl;

	free(pRcvBuf);

	string fileName;
	if(getNodeValByNodeName(bankRepData, "FileName", fileName))
	{
		string repFile = "ccbRepFile";
		fileName.erase(0,fileName.find('\\'));
		repFile += fileName;

		string::size_type pos=0;
    
   		while( (pos=repFile.find('\\', pos)) != string::npos)
		{
       		repFile.replace(pos, 1, "/");
        		pos += 1;
    		}
		if(pTrans->debug)
			cout<<"xml file name: "<<repFile<<endl;
		std::ifstream  ifs(repFile.c_str());  
		if(!ifs.good())
		{
		    return -1;
		}
		istreambuf_iterator<char>  beg(ifs),end;   
		bankRepData = string(beg,end);
		ifs.close();
	}


	string bankData;
	if(!pTrans->parseBankResponseData(bankRepData,bankData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	
	if(!pTrans->buildResponseData(handle,&aPack,bankData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	*pRetCode=0;	
	return 0;
}
