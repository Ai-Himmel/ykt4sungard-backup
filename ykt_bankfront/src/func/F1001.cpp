/* ----------------------------------------------------------
 * 程序名称：F1001.cpp
 * 创建日期：2007-12-19
 * 程序作者：闻剑
 * 版本信息：1.0.0.0
 * 程序功能：浦发银行接口
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
#include "spdbtrans.h"
int F1001(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;

	*pRetCode=-1;
	CSpdbTrans   SpdbTran(in_pack);
	CTrans *pTrans = &SpdbTran;
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
		cout<<"签名"<<endl;	
	CHttpPost httpPost;
	httpPost.init();
	if(pTrans->debug)
		httpPost.setDebug();
	httpPost.headAppend("Content-Type: INFOSEC_SIGN/1.0");
	httpPost.headSetopt();
	httpPost.setTimeout(pTrans->pBank->getNCSign().timeout);	
	if(!httpPost.httpPostData(pTrans->pBank->getNCSign().url,signReqData))
	{
		*pRetCode=9999;
		sprintf(szMsg,"%s(%s)",httpPost.getCurlErrMsg().c_str(),httpPost.getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	string signedRepData;
	string signedData;
	signedRepData=httpPost.getContent();
	if(!pTrans->parseSignedData(signedRepData,signedData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	string bankReqData;
	if(!pTrans->buildBankRequestData(signedData,bankReqData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	if(pTrans->debug)
		cout<<"发送"<<pTrans->pTrans->_transName<<"请求到"<<pTrans->pBank->getBankName()<<endl;
	httpPost.reset();
	if(pTrans->debug)
		httpPost.setDebug();
//		httpPost.httpSetProxyHostPort((char*)pTrans->pBank->getProxyHostPort().c_str());
//		httpPost.httpSetProxyUserPwd((char*)pTrans->pBank->getProxyUserPwd().c_str());		
	httpPost.setTimeout(pTrans->pBank->getNCService().timeout);
	if(!httpPost.httpPostData(pTrans->pBank->getNCService().url, bankReqData))
	{
		*pRetCode=9999;
		sprintf(szMsg,"%s(%s)",httpPost.getCurlErrMsg().c_str(),httpPost.getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}	
	string& bankRepData=httpPost.getContent(); 
	string bankSignedData;
	//cout<<"bankRepData:\n"<<bankRepData<<endl;
	if(!pTrans->parseBankResponseData(bankRepData,bankSignedData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	if(pTrans->debug)
		cout<<"验签名"<<endl;
	httpPost.reset();
	if(pTrans->debug)
		httpPost.setDebug();
	httpPost.headAppend("Content-Type: INFOSEC_VERIFY_SIGN/1.0");
	httpPost.headSetopt();
	httpPost.setTimeout(pTrans->pBank->getNCVerify().timeout);
	if(!httpPost.httpPostData(pTrans->pBank->getNCVerify().url, bankSignedData))
	{
		*pRetCode=9999;
		sprintf(szMsg,"%s(%s)",httpPost.getCurlErrMsg().c_str(),httpPost.getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}
	string bankVerifyData;
	string bankData;
	bankVerifyData=httpPost.getContent();
	
	if(pTrans->debug)
		cout<<"bankVerifyData:\n"<<bankVerifyData<<endl;
	if(!pTrans->parseVerifyBankSignedData(bankVerifyData,bankData))
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
