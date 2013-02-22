#ifndef _BOCTRANS_H
#define _BOCTRANS_H
/* ----------------------------------------------------------
 * 程序名称：cmbctrans.h
 * 创建日期：2008-2-22
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：招行交易类
 * ----------------------------------------------------------*/

#include "trans.h"
#include "mytime.h"
#include "mystring.h"

class CCmbcTrans:public CTrans {
public:
	CCmbcTrans(ST_PACK*  pack):CTrans(pack){};
	CCmbcTrans(ST_CPACK*  cpack):CTrans(cpack){};
	
	bool prepare()
	{
		//转换币种
		string target = pBank->currencySourceMap[pRcvCpack->pack.snation_code];
		strncpy(pRcvCpack->pack.snation_code,target.c_str(),4);

		// 业务参考号
		//strcpy(pRcvCpack->pack.sphone,getFmtSysDateTime());
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
		string bankReturnCode,bankErrCode;
		string bankReturnMsg,bankErrMsg;
	        if(!getNodeValByNodeName(bankRepData,"RETCOD",bankReturnCode))
	        {
	            _errMsg="Error:get bank response packet <RETCOD> xmlnode error";
	            return false;
	        }
		
		 if(bankReturnCode !="0" )
	  	{
		    if(!getNodeValByNodeName(bankRepData,"ERRMSG",bankReturnMsg))
	            {
	                _errMsg="Error:get bank response packet <ERRMSG> xmlnode error";
	            }
	            else
	            {
	                _errMsg="Error:";
			  _errMsg+=bankReturnCode;
	                _errMsg+=bankReturnMsg;
	            }
		     return false;
	   	 }

		 if(getNodeValByNodeName(bankRepData, "ERRCOD", bankErrCode))
	 	{
	 		if(bankErrCode != "SUC0000")
 			{
 				_errMsg = "Error : ";
				_errMsg += bankErrCode;
 				if(getNodeValByNodeName(bankRepData, "ERRTXT", bankErrMsg))
					_errMsg += bankErrMsg;
				else
					_errMsg += bankReturnMsg;

				return false;					
 			}
				
	 	}
	       
		    if(!getNodeValByNodeName(bankRepData,"CMBSDKPKG",bankData))
		    {
	            		_errMsg="Error:get bank response data <CMBSDKPKG> xmlnode error";
			    return false;
		    }
		   return true;
		 }
};

#endif

 