#ifndef _BOCTRANS_H
#define _BOCTRANS_H
/* ----------------------------------------------------------
 * �������ƣ�cmbctrans.h
 * �������ڣ�2008-2-22
 * �������ߣ������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����н�����
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
		//ת������
		string target = pBank->currencySourceMap[pRcvCpack->pack.snation_code];
		strncpy(pRcvCpack->pack.snation_code,target.c_str(),4);

		// ҵ��ο���
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

 