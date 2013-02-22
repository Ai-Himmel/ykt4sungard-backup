#ifndef _SPDBTRANS_H
#define _SPDBTRANS_H
/* ----------------------------------------------------------
 * 程序名称：spdbtrans.h
 * 创建日期：2007-12-19
 * 程序作者：闻剑
 * 版本信息：1.0.0.0
 * 程序功能：浦发银行交易类
 * ----------------------------------------------------------*/
#include "trans.h"
#include "mytime.h"

class CSpdbTrans:public CTrans {
public:
	CSpdbTrans(ST_PACK*  pack):CTrans(pack){}
	CSpdbTrans(ST_CPACK*  cpack):CTrans(cpack){}
	bool buildSignData(string& signReqData)
	{
		string body;
		signReqData.resize(0);
		if(!getNodeValByNodeName(_templateData, "body",body))
		{
			_errMsg="get body node value error";
			return false;
		}
		appendNewXmlNode(signReqData,"body",body);
		return true;
	}	
	bool parseSignedData(string& signedRepData,string& signedData)
	{
		    if(!getNodeValByNodeName(signedRepData,"sign",signedData))
		    {
	            		_errMsg="Error:get sign response data <sign> xmlnode error";
			    return false;
		    }
		   return true;
	}
	 bool buildBankRequestData(const string& signedData,string& bankReqData)
	{
		 string head;
		 string body;
	        string xmlBuf;
		string  packetBuf;
	   	 if(!getNodeValByNodeName(_templateData,"head",head))
	    	{
	             _errMsg="Error:get sign response data <sign> xmlnode error";
		     return false;
	    	}
	        appendNewXmlNode(body,"signature",signedData);
	        appendNewXmlNode(xmlBuf,"head",head);
	        appendNewXmlNode(xmlBuf,"body",body);
	        appendNewXmlNode(packetBuf,"packet",xmlBuf);
	        
	        char szBufLen[10];
	        sprintf(szBufLen,"%06d",packetBuf.size()+6);

	        bankReqData=string(szBufLen,6);
	        bankReqData += packetBuf;
		return true;
	}
	 bool parseBankResponseData(const string& bankRepData,string& bankSignedData)
	 {
		string bankReturnCode;
		string bankReturnMsg;
	        if(!getNodeValByNodeName(bankRepData,"returnCode",bankReturnCode))
	        {
	            _errMsg="Error:get bank response packet <returnCode> xmlnode error";
	            return false;
	        }
	        if(bankReturnCode!="AAAAAAA")
		  {
			    if(!getNodeValByNodeName(bankRepData,"returnMsg",bankReturnMsg))
		            {
		                _errMsg="Error:get bank response packet <returnMsg> xmlnode error";
		            }
		            else
		            {
		                _errMsg="Error:";
		                _errMsg+=bankReturnMsg;
		            }
			     return false;
		    }
		    if(!getNodeValByNodeName(bankRepData,"signature",bankSignedData))
		    {
	            		_errMsg="Error:get bank response data <signature> xmlnode error";
			    return false;
		    }
		   return true;
	 }
};
#endif
