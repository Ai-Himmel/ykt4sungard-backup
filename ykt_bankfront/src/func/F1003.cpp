/* ----------------------------------------------------------
 * 程序名称：F1003.cpp
 * 创建日期：2008-2-22
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：招商银行接口
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
#include "cmbctrans.h"

int F1003(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;

	*pRetCode=-1;
	ST_CPACK aPack;		
	CCmbcTrans   CmbcTran(in_pack);
	CTrans *pTrans = &CmbcTran;
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
	
	CHttpPost httpPost;
	httpPost.init();
	if(pTrans->debug)
		httpPost.setDebug();
	httpPost.setTimeout(pTrans->pBank->getNCService().timeout);	
	
	string bankReqData;
	if(!pTrans->buildSignData(bankReqData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	if(pTrans->debug)
	{
		cout<<"requestData:"<<bankReqData<<endl;
		cout<<"发送"<<pTrans->pTrans->_transName<<"请求到"<<pTrans->pBank->getBankName()<<endl;
	}
	if(!httpPost.httpPostData(pTrans->pBank->getNCService().url, bankReqData))
	{
		*pRetCode=9999;
		sprintf(szMsg,"%s(%s)",httpPost.getCurlErrMsg().c_str(),httpPost.getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}	
	string& bankRepData=httpPost.getContent(); 
	string bankData;
	if(pTrans->debug)	
		cout<<"bankRepData:\n"<<bankRepData<<endl;
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
	if(pTrans->debug)
	{
		cout<<"print output data:"<<endl;
		printCpackFieldValue(&aPack);
	}
	*pRetCode=0;
	return 0;
}
