#ifndef _CCB_H
#define _CCB_H
/* ----------------------------------------------------------
 * 程序名称：ccbtrans.h
 * 创建日期：2008-01-29
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：建设银行交易类
 * ----------------------------------------------------------*/
#include "trans.h"
#include "mytime.h"

typedef struct MSG_HEADER {
	char		version[ 9 ];
	char		packType[ 2 ];
	char		txCode[ 5 ];
	char		funcCode[ 4 ];
	char		commMode[ 2 ];
	char		totalBlock[ 9 ];
	char		curBlock[ 9 ];
	char		msgDataLen[ 9 ];
	char		msgExtLen[ 9 ];
	char		encryptMode[ 2 ];
	char		noUse[ 51 ];
}CCBMSGHEAD;

class CCcbTrans:public CTrans {
public:
	CCcbTrans(ST_PACK*  pack):CTrans(pack) {};
	CCcbTrans(ST_CPACK*  cpack):CTrans(cpack){};
	
	bool prepare()
	{
		return true;
	};

	string  getTranCode()
	{
		string tranCode;
		if(!getNodeValByNodeName(getTemplateData(),"TxCode",tranCode))
		{			
     			 _errMsg="Error:get template data <TxCode> xmlnode error";
     			 return "";	        
		}
		return tranCode;
	}
	 bool buildBankRequestData(const string& templateData,string& bankReqData)
	{
		CCBMSGHEAD msgHead;
		memset(&msgHead,0,sizeof(msgHead));
		strcpy(msgHead.version,"01");
		strcpy(msgHead.txCode,getTranCode().c_str());
		msgHead.commMode[0] =  'M';
		sprintf(msgHead.msgDataLen,"%d",templateData.size());
		msgHead.encryptMode[0] = 'N';
		
		bankReqData = string((char*)&msgHead,sizeof(msgHead));
		bankReqData += templateData;

		return true;
	}
	 bool parseBankResponseData(const string& bankRepData,string& bankData)
	 {
		string bankReturnCode;
		string bankReturnMsg;
	        if(!getNodeValByNodeName(bankRepData,"RespCode",bankReturnCode))
	        {
	            _errMsg="Error:get bank response packet <RespCode> xmlnode error";
	            return false;
	        }
		
		 if(bankReturnCode !="M0001" )
	  	{
		    if(!getNodeValByNodeName(bankRepData,"RespMsg",bankReturnMsg))
	            {
	                _errMsg="Error:get bank response packet <RespMsg> xmlnode error";
	            }
	            else
	            {
	                _errMsg="Error:";
			 _errMsg+=bankReturnCode;
	                _errMsg+=bankReturnMsg;
	            }
		     return false;
	   	 }
			      
			if(!getNodeValByNodeName(bankRepData,"Body",bankData))
			{
			    		_errMsg="Error:get bank response data <Body> xmlnode error";
			    return false;
			}
		   return true;
	}
};


#endif
