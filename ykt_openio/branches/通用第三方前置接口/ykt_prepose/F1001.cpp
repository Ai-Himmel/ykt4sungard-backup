/* ----------------------------------------------------------
 * 程序名称：F1001.cpp
 * 创建日期：2007-12-19
 * 程序作者：闻剑
 * 版本信息：1.0.0.0
 * 程序功能：浦发银行余额查询
 * ----------------------------------------------------------*/
#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <syslog.h>
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
	ST_CPACK aPack;		
	CSpdbTrans   SpdbTran(in_pack);
	CTrans *pTrans = &SpdbTran;
	if(!pTrans->getBankAndTrans())
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	cout<<"print input data:"<<endl;
	printCpackFieldValue(pTrans->_cpack);
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
	cout<<"签名"<<endl;	
	CHttpPost httpPost;
	httpPost.init();
	httpPost.headAppend("Content-Type: INFOSEC_SIGN/1.0");
	httpPost.headSetopt();
	if(!httpPost.httpPostData(pTrans->_pBank->getSignUrl(),signReqData))
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
	//cout<<"requestData:"<<bankReqData<<endl;
	cout<<"发送"<<pTrans->_pTrans->_transName<<"请求到"<<pTrans->_pBank->getBankName()<<endl;
	httpPost.reset();
	if(!httpPost.httpPostData(pTrans->_pBank->getBankUrl(), bankReqData))
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
	cout<<"验签名"<<endl;
	httpPost.reset();
	httpPost.headAppend("Content-Type: INFOSEC_VERIFY_SIGN/1.0");
	httpPost.headSetopt();
	if(!httpPost.httpPostData(pTrans->_pBank->getSignUrl(), bankSignedData))
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
	cout<<"bankVerifyData:\n"<<bankVerifyData<<endl;
	if(!pTrans->parseVerifyBankSignedData(bankVerifyData,bankData))
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
	cout<<"交易成功"<<endl;
	cout<<"print output data:"<<endl;
	printCpackFieldValue(&aPack);
	*pRetCode=0;
	return 0;
}
