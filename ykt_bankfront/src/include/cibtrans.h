#ifndef _CIBTRANS_H
#define _CIBTRANS_H
/* ----------------------------------------------------------
 * 程序名称：cibtrans.h
 * 创建日期：2008-1-16
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：中信银行交易类
 * ----------------------------------------------------------*/

#include "trans.h"
#include "mytime.h"
#include "string"
class CCibTrans:public CTrans {
public:
	CCibTrans(ST_PACK*  pack):CTrans(pack){};
	CCibTrans(ST_CPACK*  cpack):CTrans(cpack){};
	
	bool prepare()
	{
		return true;
	};

	string getTranCode()
	{
		string tranCode;
		if(!getNodeValByNodeName(getTemplateData(),"TRAN_CODE",tranCode))
		{			
     			 _errMsg="Error:get template data <TRAN_CODE> xmlnode error";
     			 return "";	        
		}
		return tranCode;
	}
	bool buildSignData(string& signReqData )
	{
		string signData = getTemplateData();
		char szBufLen[10];
		sprintf(szBufLen,"%06d",signData.size());
		signReqData=string(szBufLen,6);
		signReqData += signData;		
		return true;
	}

	bool buildVerifyData(string& bankSignedData,string & verifyData)
	{
		char szBufLen[10];
		sprintf(szBufLen,"%06d",bankSignedData.size());

		verifyData = string(szBufLen,6);
		verifyData += bankSignedData;
		return true;
	}
	
	bool parseVerifyBankSignedData(string & bankRepData, string & bankData)
 	{
 		 string statusID;
 		 if(!getNodeValByNodeName(bankRepData,"STATUS_ID",statusID))
	 	{
	 		 _errMsg="Error:get template data <STATUS_ID> xmlnode error";
     			 return false;	
	 	}

		if(statusID != "AAAAAAA")
		{
			string statusText;
			if(!getNodeValByNodeName(bankRepData,"STATUS_TEXT",statusText))
		 	{
		 		 _errMsg="Error:get template data <STATUS_TEXT> xmlnode error";
	     			 return false;	
		 	}
			 _errMsg = statusText;
			return false;
		}

		 if(!getNodeValByNodeName(bankRepData,"CITICIB",bankData))
	 	{
	 		 _errMsg="Error:get template data <CITICIB> xmlnode error";
     			 return false;	
	 	}
		return true;
 	}

	 bool buildResponseData(TRUSERID *handle,string& bankData)
	{
		int retcode=0;
		int row=0;
		char szMsg[256]="";
		map<string,Field>::iterator itMap;
		if(pTrans->_response.recordNodeName.length()>0)
		{
			string::size_type pos;
			string  recordNode=string("</")+pTrans->_response.recordNodeName+">";
			string recordBuf;

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
			}
			
			while(1)
			{
				pos=bankData.find(recordNode);
				if(pos== string::npos)
				{
					break;
				}
				if(!getNodeValByNodeName(bankData,pTrans->_response.recordNodeName,recordBuf))
				{
					break;
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
			int num,index;
			vector<string> strlist;
			string nodeVal;
			string tmpBankData;
			for(itMap=pTrans->_response.CycleFieldMap.begin(); itMap!=pTrans->_response.CycleFieldMap.end();itMap++)
			{				
				string nodeVal;
				char szVal[256]="";
				switch(itMap->second.type)
				{
				case FIELDTYPE_RESP:
					num = split2list( itMap->first, '.', strlist);
					index = 0;
					tmpBankData = bankData;
					while(index < num)
					{
						getNodeValByNodeName(tmpBankData,strlist[index],nodeVal);
						tmpBankData = nodeVal;
						index++;
					}				
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

};
#endif

 
