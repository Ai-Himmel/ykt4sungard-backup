#ifndef _TRANS_H
#define _TRANS_H

#include <iostream>
#include <sstream>
#include "cpack.h"
#include "myparameters.h"
#include "mycpack.h"
#include "mytime.h"
using namespace std;
extern CSvrLink g_SvrLink;

class CTrans
{
public:
	CTrans(ST_PACK*  pack)
	{
		char *pCPACK=(char*)pack;
		pCPACK=pCPACK-sizeof(ST_PACKHEAD);
		pRcvCpack=(ST_CPACK*)pCPACK;
		pMyParameters = MyParameters::getInstance();
		debug=false;
	}
	CTrans(ST_CPACK*  cpack)
	{ 
		pRcvCpack=cpack;
		pMyParameters = MyParameters::getInstance();
		debug=false;
		/////////////////////////////////////////
	}
	virtual ~CTrans()
	{

	}
	bool AssignReqHead()
	{
		char fieldVal[256]="";
		//读取调试标志
		//报文号
		ResetNormalCPack(&aPack, 0, 1);		
	  	 if(getCpackFieldValue(pRcvCpack,"lserial1",fieldVal))
	  	 {
		 	_errMsg=string("读取请求包")+"lserial1"+"字段值失败";
			return false;
	  	 }
		 if(fieldVal[0]!='0')
		 	debug=true;
		 else
		 	debug=false;
	  	 if(getCpackFieldValue(pRcvCpack,pMyParameters->headField.bankCode.cpack.c_str(),fieldVal))
	  	 {
		 	_errMsg=string("读取请求包")+pMyParameters->headField.bankCode.cpack+"字段值失败";
			return false;
	  	 }
		 reqHead.bankCode=fieldVal;		 
	  	 if(getCpackFieldValue(pRcvCpack,pMyParameters->headField.transCode.cpack.c_str(),fieldVal))
	  	 {
		 	_errMsg=string("读取请求包")+pMyParameters->headField.transCode.cpack+"字段值失败";
			return false;
	  	 }
		 reqHead.transCode=fieldVal;
	  	 if(getCpackFieldValue(pRcvCpack,pMyParameters->headField.refID.cpack.c_str(),fieldVal))
	  	 {
		 	_errMsg=string("读取请求包")+pMyParameters->headField.refID.cpack+"字段值失败";
			return false;
	  	 }
		 reqHead.refID=fieldVal;
	  	 if(getCpackFieldValue(pRcvCpack,pMyParameters->headField.date.cpack.c_str(),fieldVal))
	  	 {
		 	_errMsg=string("读取请求包")+pMyParameters->headField.date.cpack+"字段值失败";
			return false;
	  	 }
		 reqHead.date=fieldVal;
	  	 if(getCpackFieldValue(pRcvCpack,pMyParameters->headField.time.cpack.c_str(),fieldVal))
	  	 {
		 	_errMsg=string("读取请求包")+pMyParameters->headField.time.cpack+"字段值失败";
			return false;
	  	 }
		 reqHead.time=fieldVal;
	  	 if(getCpackFieldValue(pRcvCpack,pMyParameters->headField.corpID.cpack.c_str(),fieldVal))
	  	 {
		 	_errMsg=string("读取请求包")+pMyParameters->headField.corpID.cpack+"字段值失败";
			return false;
	  	 }
		 reqHead.corpID=fieldVal;
	  	 if(getCpackFieldValue(pRcvCpack,pMyParameters->headField.userID.cpack.c_str(),fieldVal))
	  	 {
		 	_errMsg=string("读取请求包")+pMyParameters->headField.userID.cpack+"字段值失败";
			return false;
	  	 }
		 reqHead.userID=fieldVal;
	  	 if(getCpackFieldValue(pRcvCpack,pMyParameters->headField.userPwd.cpack.c_str(),fieldVal))
	  	 {
		 	_errMsg=string("读取请求包")+pMyParameters->headField.userPwd.cpack+"字段值失败";
			return false;
	  	 }
		 reqHead.userPwd=fieldVal;
		 pBank =pMyParameters->getBAFromBankCode(reqHead.bankCode.c_str());
		 if(!pBank)
		 {
                        _errMsg=string("读取银行代码")+reqHead.bankCode+"的配置失败";
                        return false;
		 }
		 pTrans=pBank->_transArray.getTransByCode(reqHead.transCode.c_str());
		 if(!pTrans)
		 {
                        _errMsg=string("读取银行代码")+reqHead.bankCode+"交易代码"+reqHead.transCode+"的配置失败";
                        return false;
 		 }
		if(debug)
		{
			cout<<"print input data:"<<endl;
			printCpackFieldValue(pRcvCpack);
		}
		strcpy((char*)pRcvCpack->pack.usset0,getPacketID());
		strcpy((char*)pRcvCpack->pack.usset1,getSysDate());
		strcpy((char*)pRcvCpack->pack.usset2,getSysTime());
		strcpy((char*)pRcvCpack->pack.usset3,getSysDateTime());
		strcpy((char*)pRcvCpack->pack.usset4,getFmtSysDate());
		strcpy((char*)pRcvCpack->pack.usset5,getFmtSysTime());
		strcpy((char*)pRcvCpack->pack.usset6,getFmtSysDateTime());
		return true;
	}
	virtual bool prepare()
	{
		return true;
	}
	virtual bool replaceTemlateVarValue()
	{
		 _templateData=pTrans->_request._templateStr;
		  for(unsigned int i=0;i<pTrans->_request.varList.size();i++)
		 {
		        string& var=pTrans->_request.varList[i];
			if(pTrans->_request.FieldMap[var].desc.empty())
			{
			      	_errMsg= var+" bankconf.xml not config";
		            	return false;
			}
			//先替换系统变量
		        string& cpack=pTrans->_request.FieldMap[var].cpack;
		        if(cpack.empty())
		        {
			      	_errMsg= var+" var's cpack field not config";
		            	return false;
		        }
			 char varVal[257]="";
			 if(getCpackFieldValue(pRcvCpack,cpack.c_str(),varVal))
			 {
			      	_errMsg= string("got var ")+var+"value from cpack field "+cpack+" error";
		            	return false;
			 }
			if(debug)
				 cout<<"get var "<<var<<" field from "<<cpack<<" value:"<<varVal<<endl;
		        string_replace(_templateData,var,varVal);
		    }
		  if(debug)
		  	cout<<"packet:"<<_templateData<<endl;
		  return true;
	}


	virtual string  getTranCode()
	{
		return "";
	}
	
	//根据配置参数组织报文
	virtual bool buildHead()
	{
		
		return true;
	}
	virtual bool buildBody()
	{
		return true;
	}
	virtual bool release()
	{
		return true;
	}
	virtual bool buildSignData(string& signReqData )
	{
		return true;
	}
	virtual bool parseSignedData(string& signedRepData,string& signedData)
	{
		return true;
	}
	virtual bool buildBankRequestData(const string& signedData,string& bankReqData)
	{
		return true;
	}
	virtual bool parseBankResponseData(const string& bankRepData,string& bankSignedData)
	{
		return true;
	}

	virtual bool buildVerifyData(string& verifyData)
	{
		return true;
	}

	virtual bool parseVerifyBankSignedData(string& bankRepData,string& bankData)
	{
		if(!getNodeValByNodeName(bankRepData,pTrans->_response.dataNodeName,bankData))
		{
		    	_errMsg="Error:get bank response data "+pTrans->_response.dataNodeName+ " xmlnode error";
		    	return false;
		}
		return true;
	}
	virtual bool buildResponseData(TRUSERID *handle,ST_CPACK*  outCpack,string& bankData)
	{
		int retcode=0;
		int row=0;
		char szMsg[256]="";
		map<string,Field>::iterator itMap;
		ResetNormalCPack(outCpack, 0, 1);
		if(pTrans->_response.recordNodeName.length()>0)
		{
			string::size_type pos;
			string  recordNode=string("</")+pTrans->_response.recordNodeName+">";
			string recordBuf;
			if(bankData.find(recordNode) == string::npos) 
			{
				_errMsg = "无记录";
				return false;
			}
			//		
			for(itMap=pTrans->_response.SingleFieldMap.begin(); itMap!=pTrans->_response.SingleFieldMap.end();itMap++)
			{
					string nodeVal;
					getNodeValByNodeName(bankData,itMap->first,nodeVal);
					if(pBank->currencyTargetMap[nodeVal] !="")
						setCpackFieldValue(outCpack,itMap->second.cpack.c_str(),pBank->currencyTargetMap[nodeVal].c_str());
					else
						setCpackFieldValue(outCpack,itMap->second.cpack.c_str(),nodeVal.c_str());			
				
				//cout<<"set cpack field "<<itMap->second._cpack<<":"<<nodeVal<<endl;
			}
			//
			while(1)
			{
				pos=bankData.find(recordNode);
				if(pos== string::npos)
				{
					return true;
				}
				if(!getNodeValByNodeName(bankData,pTrans->_response.recordNodeName,recordBuf))
				{
					return true;
				}
				bankData=bankData.erase(0,pos+recordNode.length());
				//cout<<"recordBuf:"<<recordBuf<<endl;
				for(itMap=pTrans->_response.CycleFieldMap.begin(); itMap!=pTrans->_response.CycleFieldMap.end();itMap++)
				{
					string nodeVal;
					getNodeValByNodeName(recordBuf,itMap->first,nodeVal);
					if(pBank->currencyTargetMap[nodeVal] !="")
						setCpackFieldValue(outCpack,itMap->second.cpack.c_str(),pBank->currencyTargetMap[nodeVal].c_str());
					else
						setCpackFieldValue(outCpack,itMap->second.cpack.c_str(),nodeVal.c_str());	
					//setCpackFieldValue(outCpack,itMap->second.cpack.c_str(),nodeVal.c_str());				
					//cout<<"set cpack field "<<itMap->second._cpack<<":"<<nodeVal<<endl;
				}
				if(!row)
					g_SvrLink.SetCol(0, outCpack->head.ParmBits);
				PutRow(handle,&(outCpack->pack), &retcode,szMsg);
				if(debug)
					printCpackFieldValue(outCpack);	
				row++;
			}
		}
		else
		{
				for(itMap=pTrans->_response.CycleFieldMap.begin(); itMap!=pTrans->_response.CycleFieldMap.end();itMap++)
				{
					string nodeVal;
					getNodeValByNodeName(bankData,itMap->first,nodeVal);
					if(pBank->currencyTargetMap[nodeVal] !="")
						setCpackFieldValue(outCpack,itMap->second.cpack.c_str(),pBank->currencyTargetMap[nodeVal].c_str());
					else
						setCpackFieldValue(outCpack,itMap->second.cpack.c_str(),nodeVal.c_str());	
					//setCpackFieldValue(outCpack,itMap->second.cpack.c_str(),nodeVal.c_str());
				}
				g_SvrLink.SetCol(0, outCpack->head.ParmBits);
				PutRow(handle,&(outCpack->pack), &retcode,szMsg);
				if(debug)
					printCpackFieldValue(outCpack);	
		}
		return true;
	}
	virtual bool buildResponseData(TRUSERID *handle,string& bankData)
	{
		int retcode=0;
		int row=0;
		char szMsg[256]="";
		map<string,Field>::iterator itMap;
		
		if(pTrans->_response.recordNodeName.length()>0)
		{
			//多记录处理
			string::size_type pos;
			string  recordNode=string("</")+pTrans->_response.recordNodeName+">";
			string recordBuf;
			if(bankData.find(recordNode) == string::npos) 
			{
				_errMsg = "无记录";
				return false;
			}
			//		
			for(itMap=pTrans->_response.SingleFieldMap.begin(); itMap!=pTrans->_response.SingleFieldMap.end();itMap++)
			{
					string nodeVal;
					char szVal[256]="";
					switch(itMap->second.type)
					{
					case FIELDTYPE_RESP:
						getNodeValByNodeName(bankData,itMap->first,nodeVal);
						if((itMap->second.desc=="币种")&&(pBank->currencyTargetMap[nodeVal] !=""))
							setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),pBank->currencyTargetMap[nodeVal].c_str());
						else
							setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),nodeVal.c_str());	
						break;
					case FIELDTYPE_FIXVAL:
						setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),itMap->first.c_str());
						break;
					case FIELDTYPE_REQ:
						getCpackFieldValue(pRcvCpack,itMap->second.cpack.c_str(),szVal);
						setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),szVal);
						break;
					}
				//cout<<"set cpack field "<<itMap->second._cpack<<":"<<nodeVal<<endl;
			}
			//
			while(1)
			{
				pos=bankData.find(recordNode);
				if(pos== string::npos)
				{
					return true;
				}
				if(!getNodeValByNodeName(bankData,pTrans->_response.recordNodeName,recordBuf))
				{
					return true;
				}
				bankData=bankData.erase(0,pos+recordNode.length());
				//cout<<"recordBuf:"<<recordBuf<<endl;
				for(itMap=pTrans->_response.CycleFieldMap.begin(); itMap!=pTrans->_response.CycleFieldMap.end();itMap++)
				{
					string nodeVal;
					char szVal[256]="";
					switch(itMap->second.type)
					{
					case FIELDTYPE_RESP:
						getNodeValByNodeName(recordBuf,itMap->first,nodeVal);
						if((itMap->second.desc=="币种")&&(pBank->currencyTargetMap[nodeVal] !=""))
							setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),pBank->currencyTargetMap[nodeVal].c_str());
						else
							setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),nodeVal.c_str());	
						break;
					case FIELDTYPE_FIXVAL:
						setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),itMap->first.c_str());
						break;
					case FIELDTYPE_REQ:
						getCpackFieldValue(pRcvCpack,itMap->second.cpack.c_str(),szVal);
						setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),szVal);
						break;
					}
					//cout<<"set cpack field "<<itMap->second._cpack<<":"<<nodeVal<<endl;
				}
				if(!row)
					g_SvrLink.SetCol(0, aPack.head.ParmBits);
				PutRow(handle,&(aPack.pack), &retcode,szMsg);
				if(debug)
					printCpackFieldValue(&aPack);	
				row++;
			}
		}
		else
		{
				for(itMap=pTrans->_response.CycleFieldMap.begin(); itMap!=pTrans->_response.CycleFieldMap.end();itMap++)
				{
					string nodeVal;
					char szVal[256]="";
					switch(itMap->second.type)
					{
					case FIELDTYPE_RESP:
						getNodeValByNodeName(bankData,itMap->first,nodeVal);
						if((itMap->second.desc=="币种")&&(pBank->currencyTargetMap[nodeVal] !=""))
							setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),pBank->currencyTargetMap[nodeVal].c_str());
						else
							setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),nodeVal.c_str());	
						break;
					case FIELDTYPE_FIXVAL:
						setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),itMap->first.c_str());
						break;
					case FIELDTYPE_REQ:
						getCpackFieldValue(pRcvCpack,itMap->second.cpack.c_str(),szVal);
						setCpackFieldValue(&aPack,itMap->second.cpack.c_str(),szVal);
						break;
					}
				}
				g_SvrLink.SetCol(0, aPack.head.ParmBits);
				PutRow(handle,&(aPack.pack), &retcode,szMsg);
				if(debug)
					printCpackFieldValue(&aPack);	
		}
		return true;
	}
	string& getHead() { return _head;}
	string& getBody() { return _body;}
	string& getTemplateData() { return _templateData;}
	void setErrMsg(const char *errMsg){ _errMsg=errMsg; }
	string& getErrMsg(){return _errMsg;};
	ST_CPACK *pRcvCpack;
	ST_CPACK aPack;	
	MyParameters *pMyParameters;
	BankContainer* pBank;	
	Trans *pTrans;	
	ReqHead reqHead;
	bool debug;
protected:
	string _errMsg;
	string _head;
	string _body;
	string _templateData;
};
#endif
