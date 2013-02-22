#ifndef _BOCTRANS_H
#define _BOCTRANS_H
/* ----------------------------------------------------------
 * 程序名称：boctrans.h
 * 创建日期：2008-2-13
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：中行交易类
 * ----------------------------------------------------------*/

#include "trans.h"
#include "mytime.h"
#include "mystring.h"

class CBocTrans:public CTrans {
public:
	CBocTrans(ST_PACK*  pack):CTrans(pack){};
	CBocTrans(ST_CPACK*  cpack):CTrans(cpack){};
	
	bool prepare()
	{
		strcpy(pRcvCpack->pack.sphone,getSysTime());
		strcpy(pRcvCpack->pack.sphone3,getSysDateTime());
		return true;
	};

	bool buildSignData(string& signReqData)
	{
		signReqData.resize(0);		
		
		signReqData += _templateData;
		return true;
	}	
	
 
	 bool parseBankResponseData(const string& bankRepData,string& bankData)
	 {
		string bankReturnCode;
		string bankReturnMsg;
	        if(!getNodeValByNodeName(bankRepData,"rspcod",bankReturnCode))
	        {
	            _errMsg="Error:get bank response packet <rspcod> xmlnode error";
	            return false;
	        }
		
		 if(bankReturnCode !="B001" )
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
	       
		    if(!getNodeValByNodeName(bankRepData,"trans",bankData))
		    {
	            		_errMsg="Error:get bank response data <Body> xmlnode error";
			    return false;
		    }
		   return true;
		 }
};

#endif

 