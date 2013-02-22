/* ----------------------------------------------------------
 * 程序名称：F1006.cpp
 * 创建日期：2008-2-13
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：中国银行接口
 * ----------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <syslog.h>
#include <sys/file.h>
#include "mypub.h"  
#include "cpack.h"
#include "svrlink.h"
#include "pubfunc.h"
#include "bupub.h"
#include "mystring.h"
#include "httppost.h"
#include "ksbu.h"
#include "boctrans.h"

typedef struct _loginInfo
{
	char date[8];
	char token[64];
}LOGININFO;

static LOGININFO bocLoginInfo;

string getToken()
{	
	char *pDate = getSysDate();
	if( !strcmp(bocLoginInfo.date,pDate))
	{
		if(strlen(bocLoginInfo.token)!= 0 )
			return bocLoginInfo.token;
	}			
	else
	{	
		LOGININFO loginInfo;
		int fd = open("bocLoginInfo.xml",O_RDONLY);
		if(fd != -1)
		{	
			if(flock(fd,LOCK_EX | LOCK_NB) == -1)
				return "";
			if(read(fd,&loginInfo,sizeof(loginInfo)) == -1)
				return "";
			if(flock(fd,LOCK_UN | LOCK_NB) == -1)
				return "";
			if(!strcmp(pDate,loginInfo.date))
				return loginInfo.token;
		}
	}
	return "";
}

int setToken(string token,string date)
{

	strncpy(bocLoginInfo.date,date.c_str(),8);
	strncpy(bocLoginInfo.token,token.c_str(),64);
	
	int fd = open("bocLoginInfo.xml",O_RDWR|O_CREAT|O_TRUNC);
	if(fd != -1)
	{
		if(flock(fd,LOCK_EX | LOCK_NB) == -1)
			return -1;
		if(write(fd,&bocLoginInfo,sizeof(bocLoginInfo)) == -1)
			return -1;
		if(flock(fd,LOCK_UN | LOCK_NB) == -1)
			return -1;
		
		return 0;
	}
	return -1;
}

int sendRecvData(CTrans *pTrans,string &sendData,string &rcvData,int *pRetCode,char *szMsg)
{
	CHttpPost httpPost;
	httpPost.init();
	if(pTrans->debug)
		httpPost.setDebug();	
	httpPost.headAppend("Content-Type: application/xml");	
	httpPost.headSetopt();
	httpPost.setTimeout(pTrans->pBank->getNCService().timeout);

	if(!httpPost.httpPostData(pTrans->pBank->getNCService().url, sendData))
	{
		*pRetCode=9999;
		sprintf(szMsg,"%s(%s)",httpPost.getCurlErrMsg().c_str(),httpPost.getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		writelog(LOG_ERR,szMsg);
		return -1;
	}	
	rcvData = httpPost.getContent(); 
	
	cout<<"bankRepData:"<<rcvData.c_str()<<endl;
	return 0;
}


int loginGetToken(string &bankRepData,string &tokenDate,string &token)
{
	string bankReturnCode;
	string bankReturnMsg;
	string _errMsg;
        if(!getNodeValByNodeName(bankRepData,"rspcod",bankReturnCode))
        {
            _errMsg="Error:get bank response packet <rspcod> xmlnode error";
            return false;
        }
	
	 if(bankReturnCode !="B001")
  	{
	    if(!getNodeValByNodeName(bankRepData,"rspmsg",bankReturnMsg))
            {
                _errMsg="Error:get bank response packet <rspmsg> xmlnode error";
            }
            else
            {
                _errMsg="Error:";
		 _errMsg+=bankReturnCode;
                _errMsg+=bankReturnMsg;
            }
	     return false;
   	 }
	
       
	    if(!getNodeValByNodeName(bankRepData,"serverdt",tokenDate))
	    {
            		_errMsg="Error:get bank response data <serverdt> xmlnode error";
		    return false;
	    }

	 if(!getNodeValByNodeName(bankRepData,"token",token))
	    {
            		_errMsg="Error:get bank response data <token> xmlnode error";
		    return false;
	    }
	   return true;
 }


int F1006(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	*pRetCode=-1;
	ST_CPACK aPack;	

	CBocTrans   CbocTran(in_pack);
	CTrans *pTrans = &CbocTran;
	if(!pTrans->AssignReqHead())
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	pTrans->prepare();

	///还未签到，先签到
	string token = getToken() ;
	string templateData,bankRepData,tokenDate;
	if(token == "")
	{
		
		Trans *loginTrans = pTrans->pBank->_transArray.getTransByCode("1000");
		 if(!loginTrans)
		 {
                        return -1;
 		 }

		 Trans *tmpTrans = pTrans->pTrans;
		 pTrans->pTrans = loginTrans;

		//将客户端日期时间按格式填入
		 strcpy(in_pack->sphone2,getSysDateTime());
		 
		 if(!pTrans->replaceTemlateVarValue())
		{
			strcpy(szMsg,pTrans->getErrMsg().c_str());
		    	cout<<szMsg<<endl;
			return -1;
		}
		 if(sendRecvData(pTrans, pTrans->getTemplateData(),bankRepData , pRetCode, szMsg) == -1)
		 	return -1;
		 if(!loginGetToken( bankRepData, tokenDate,token))
		 	return -1;
		 tokenDate.erase(8);
		 setToken(token, tokenDate.c_str());
		 pTrans->pTrans = tmpTrans;
		 
	}

	
	strncpy(in_pack->saddr2,token.c_str(),token.size());
	
	if(!pTrans->replaceTemlateVarValue())
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}
	
	
	string bankReqData,bankData;
	if(!pTrans->buildSignData(bankReqData))
	{
		strcpy(szMsg,pTrans->getErrMsg().c_str());
	    	cout<<szMsg<<endl;
		return -1;
	}

	if(sendRecvData(pTrans,bankReqData,bankRepData, pRetCode, szMsg) == -1)
		return -1;

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
