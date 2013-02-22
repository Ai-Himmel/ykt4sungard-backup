#ifndef _BOCTRANS_H
#define _BOCTRANS_H
/* ----------------------------------------------------------
 * �������ƣ�boctrans.h
 * �������ڣ�2008-2-13
 * �������ߣ������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����н�����
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

 