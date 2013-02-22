#ifndef _BCOMTRANS_H
#define _BCOMTRANS_H
/* ----------------------------------------------------------
 * 程序名称：bcomtrans.h
 * 创建日期：2008-1-18
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：交行交易类
 * ----------------------------------------------------------*/

#include "trans.h"
#include "mytime.h"
#include "mystring.h"

class CBcomTrans:public CTrans {
public:
	CBcomTrans(ST_PACK*  pack):CTrans(pack){};
	CBcomTrans(ST_CPACK*  cpack):CTrans(cpack){};
	
	bool prepare()
	{
		//发起方序号
		strcpy(pRcvCpack->pack.sphone3,getSysDateTime());

		//企业凭证号
		//strcpy(pRcvCpack->pack.sphone,getSysDateTime());
		return true;
	};


	bool buildSignData(string& signReqData)
	{
		signReqData.resize(0);		
		char szBuf[8]="";
		sprintf(szBuf,"0%-6d",_templateData.size());		
		signReqData = string(szBuf,7);
		signReqData += _templateData;
		return true;
	}	

	
	 bool parseVerifyBankSignedData(string& bankVerifyData,string& bankData)
	 {
		string bankAnsCode;
		string bankReturnMsg;
		
	    	if(!getNodeValByNodeName(bankVerifyData,"particular_code",bankAnsCode))
	    	{
	        	_errMsg="Error:get bank response packet <particular_code> xmlnode error";
	        	return false;
	    	}
		
	    	if(bankAnsCode!="0000")
	   	 {
			if(!getNodeValByNodeName(bankVerifyData,"particular_info",bankReturnMsg))
	        	{
	           		 _errMsg="Error:get bank response packet <particular_info> xmlnode error";
	        	}
	        	else
	        	{
		            	_errMsg="Error:";
		           	 _errMsg+=bankReturnMsg;
	        	}
		 	return false;
	    	}
	  
	   	if(!getNodeValByNodeName(bankVerifyData,pTrans->_response.dataNodeName,bankData))
		{
		    	_errMsg="Error:get bank verify data "+pTrans->_response.dataNodeName+ " xmlnode error";
		    	return false;
		}
		
		return true;

	}

	bool buildResponseData(TRUSERID *handle,ST_CPACK*  outCpack,string& bankData)
	{
		int retcode=0;
		char szMsg[256]="";
		map<string,Field>::iterator itMap;
		ResetNormalCPack(outCpack, 0, 1);
		if(pTrans->_response.recordNodeName.length()>0)
		{
			int row =0;
			string::size_type pos;
			string  recordNode=string("</")+pTrans->_response.recordNodeName+">";
			string serialRecordBuf;
			string recordCount;

			pos=bankData.find(recordNode);
			if(pos== string::npos)
			{
				return false;;
			}
			if(!getNodeValByNodeName(bankData,pTrans->_response.recordNodeName,serialRecordBuf))
			{
				return false;;
			}

			int recordNum;
			if(pTrans->_response.recordCount.length()>0)
			{
				if(!getNodeValByNodeName(bankData,pTrans->_response.recordCount,recordCount))
				{
					return false;
				}
				recordNum= atoi(recordCount.c_str());
				if(recordNum<=0)
				{
					_errMsg = "无记录";
					return false;
				}
			}

			vector<string> strlist;
			split2list(serialRecordBuf, '|' ,strlist);
			
			int index;
			int num = strlist.size();
			int fieldNum = num/(recordNum + 1);
			for(int j=1;j<=recordNum;j++)
			{
				for(itMap=pTrans->_response.CycleFieldMap.begin(); itMap!=pTrans->_response.CycleFieldMap.end();itMap++)
				{					
					index = getIndex(strlist,itMap->first);
					setCpackFieldValue(outCpack,itMap->second.cpack.c_str(),strlist[j*fieldNum+ index].c_str());
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
					setCpackFieldValue(outCpack,itMap->second.cpack.c_str(),nodeVal.c_str());
				}
				g_SvrLink.SetCol(0, outCpack->head.ParmBits);
				PutRow(handle,&(outCpack->pack), &retcode,szMsg);
				if(debug)
					printCpackFieldValue(outCpack);			
		}
		
		return true;
	}
	
};
#endif

 
