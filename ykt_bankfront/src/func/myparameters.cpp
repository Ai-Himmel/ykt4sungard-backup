#include <iostream>
#include <fstream>
#include <sstream>
#include "myparameters.h"

static void getVarList(const char *str, vector<string>& strlist)
{
    int len=strlen(str);
    int i=0;
    string var;
    while(i<len)
    {
        while(i<len&&str[i]!=':')i++;
        if(i>=len)
            break;
        var.resize(0);
        var+=str[i++];
		while(i<len) 
        {
            if(isalnum(str[i])||str[i]=='_')
                var+=str[i++];
            else
                break;
        }
        //cout<<"var:"<<var<<endl;
        strlist.push_back(var);   
	}
}
MyParameters * MyParameters::_pSelf = new MyParameters;

MyParameters::MyParameters() :_pXmlDoc(NULL),_nbBank(0)
{
}
bool MyParameters::load(/*bool noUserPath*/)
{
	char localConfPath[]="bankconf.xml";
	//---------------------------------------//
	// bankconf.xml  //
	//---------------------------------------//
	_pXmlDoc = new TiXmlDocument(localConfPath);
	bool loadOkay = _pXmlDoc->LoadFile();
	if (!loadOkay)
	{
		cerr<<"Load "<<localConfPath<<" failed!"<<endl;
		delete _pXmlDoc;
		_pXmlDoc = NULL;
	        return false;
	}
	else
    {
        if(!getBankConfigFromXmlTree())
            return false;
        if(!loadTemplateFile())
            return false;
    }
	return true;
}

void MyParameters::destroyInstance()
{
	if (_pXmlDoc != NULL)
	{
		delete _pXmlDoc;
	}
	delete _pSelf;
}
bool MyParameters::getBankConfigFromXmlTree()
{
	if (!_pXmlDoc)
		return false;
	
	TiXmlNode *root = _pXmlDoc->FirstChild("config");
	if (!root) 
		return false;
	TiXmlNode *headNode = root->FirstChildElement("head");
	if (!headNode) 
		return false;
	TiXmlNode *bankCodeNode = headNode->FirstChild("bankcode");
	TiXmlNode *transCodeNode = headNode->FirstChild("transcode");
	TiXmlNode *refIDNode = headNode->FirstChild("refid");
	TiXmlNode *dateNode = headNode->FirstChild("date");
	TiXmlNode *timeNode = headNode->FirstChild("time");
	TiXmlNode *corpIDNode = headNode->FirstChild("corpid");
	TiXmlNode *userIDNode = headNode->FirstChild("userid");
	TiXmlNode *userPwdNode = headNode->FirstChild("userpwd");

    	if(!bankCodeNode||!transCodeNode||!refIDNode||!dateNode||!timeNode||!corpIDNode||!userIDNode||!userPwdNode)
        return false;
	const char *desc =  (bankCodeNode->ToElement())->Attribute("desc");
    	const char *cpack = (bankCodeNode->ToElement())->Attribute("cpack");
	if (!desc ||!cpack) 
        	return false;
	 headField.bankCode.desc=desc;
	 headField.bankCode.cpack=cpack;

	desc =  (transCodeNode->ToElement())->Attribute("desc");
    	cpack = (transCodeNode->ToElement())->Attribute("cpack");
	if (!desc ||!cpack) 
        	return false;
	 headField.transCode.desc=desc;
	 headField.transCode.cpack=cpack;

	desc =  (refIDNode->ToElement())->Attribute("desc");
    	cpack = (refIDNode->ToElement())->Attribute("cpack");
	if (!desc ||!cpack) 
        	return false;
	 headField.refID.desc=desc;
	 headField.refID.cpack=cpack;

	desc =  (dateNode->ToElement())->Attribute("desc");
    	cpack = (dateNode->ToElement())->Attribute("cpack");
	if (!desc ||!cpack) 
        	return false;
	 headField.date.desc=desc;
	 headField.date.cpack=cpack;

	desc =  (timeNode->ToElement())->Attribute("desc");
    	cpack = (timeNode->ToElement())->Attribute("cpack");
	if (!desc ||!cpack) 
        	return false;
	 headField.time.desc=desc;
	 headField.time.cpack=cpack;

	desc =  (corpIDNode->ToElement())->Attribute("desc");
    	cpack = (corpIDNode->ToElement())->Attribute("cpack");
	if (!desc ||!cpack) 
        	return false;
	 headField.corpID.desc=desc;
	 headField.corpID.cpack=cpack;

	desc =  (userIDNode->ToElement())->Attribute("desc");
    	cpack = (userIDNode->ToElement())->Attribute("cpack");
	if (!desc ||!cpack) 
        	return false;
	 headField.userID.desc=desc;
	 headField.userID.cpack=cpack;

	desc =  (userPwdNode->ToElement())->Attribute("desc");
    	cpack = (userPwdNode->ToElement())->Attribute("cpack");
	if (!desc ||!cpack) 
        	return false;
	 headField.userPwd.desc=desc;
	 headField.userPwd.cpack=cpack;

	TiXmlNode *banksNode = root->FirstChildElement("banks");
	if (!banksNode) 
		return false;
	return feedBankConfig(banksNode);
}
bool MyParameters::feedBankConfig(TiXmlNode *node)
{
	for (TiXmlNode *childNode = node->FirstChildElement("bank");
		childNode;
		childNode = childNode->NextSibling("bank") )
	{
		const char *bankName = (childNode->ToElement())->Attribute("name");
		const char *bankCode = (childNode->ToElement())->Attribute("bankCode");
		if (!bankName || !bankCode) 
            		return false;
		NetConfig  ncSign,ncService,ncVerify;
		string proxyHostPort,proxyUserPwd;
		TiXmlNode *signNode = childNode->FirstChildElement("sign");
		if(signNode)
		{
			const char *protocol = (signNode->ToElement())->Attribute("protocol");
			const char *timeout = (signNode->ToElement())->Attribute("timeout");
			if(!protocol||!timeout)
				return false;
			ncSign.protocol=protocol;
			ncSign.timeout=atol(timeout);
			if(!strcmp(protocol,"http"))
			{
		    		const char *url = (signNode->ToElement())->Attribute("url");
				if(!url)
					return false;
				ncSign.url=url;
			}
			else
			{
			    	const char *ip = (signNode->ToElement())->Attribute("ip");
			   	const char *port = (signNode->ToElement())->Attribute("port");
				if(!ip||!port)
					return false;
				ncSign.ip=ip;
				ncSign.port=atol(port);
			}
		}
		TiXmlNode *serviceNode = childNode->FirstChildElement("service");
		if(serviceNode)
		{
			const char *protocol = (serviceNode->ToElement())->Attribute("protocol");
			const char *timeout = (serviceNode->ToElement())->Attribute("timeout");
			if(!protocol||!timeout)
				return false;
			ncService.protocol=protocol;
			ncService.timeout=atol(timeout);
			if(!strcmp(protocol,"http"))
			{
		    		const char *url = (serviceNode->ToElement())->Attribute("url");
				if(!url)
					return false;
				ncService.url=url;
			}
			else
			{
			    	const char *ip = (serviceNode->ToElement())->Attribute("ip");
			   	const char *port = (serviceNode->ToElement())->Attribute("port");
				if(!ip||!port)
					return false;
				ncService.ip=ip;
				ncService.port=atol(port);
			}
		}
		TiXmlNode *proxyNode = childNode->FirstChildElement("proxy");
		if(proxyNode)
		{
			const char *hostPort =(proxyNode->ToElement())->Attribute("hostPort");
			if(!hostPort)
				return false;
			proxyHostPort = hostPort;
			const char *userPwd =(proxyNode->ToElement())->Attribute("userPwd");
			if(userPwd)
			{
				proxyUserPwd= userPwd;
			}
		}
		TiXmlNode *verifyNode = childNode->FirstChildElement("verify");
		if(verifyNode)
		{
			const char *protocol = (verifyNode->ToElement())->Attribute("protocol");
			const char *timeout = (verifyNode->ToElement())->Attribute("timeout");
			if(!protocol||!timeout)
				return false;
			ncVerify.protocol=protocol;
			ncVerify.timeout=atol(timeout);
			if(!strcmp(protocol,"http"))
			{
		    		const char *url = (verifyNode->ToElement())->Attribute("url");
				if(!url)
					return false;
				ncVerify.url=url;
			}
			else
			{
			    	const char *ip = (verifyNode->ToElement())->Attribute("ip");
			   	const char *port = (verifyNode->ToElement())->Attribute("port");
				if(!ip||!port)
					return false;
				ncVerify.ip=ip;
				ncVerify.port=atol(port);
			}
		}
		
		_bankArray[_nbBank] = new BankContainer(bankCode,bankName);

		TiXmlNode *currency = childNode->FirstChildElement("currencymap");
		if(currency)
		{
			for (TiXmlNode *fieldNode = currency->FirstChildElement("field");
				fieldNode;
				fieldNode = fieldNode->NextSibling("field") )
			{
				const char *desc = (fieldNode->ToElement())->Attribute("desc");
				const char *source = (fieldNode->ToElement())->Attribute("source");
				const char *target = (fieldNode->ToElement())->Attribute("target");		
				if( !source || !target)
					return false;
				_bankArray[_nbBank]->currencySourceMap[source] = target;
				_bankArray[_nbBank]->currencyTargetMap[target] = source;
			}
		}
		_bankArray[_nbBank]->setNCSign(ncSign);
		_bankArray[_nbBank]->setNCService(ncService);
		_bankArray[_nbBank]->setNCVerify(ncVerify);
		_bankArray[_nbBank]->setProxyHostPort(proxyHostPort.c_str());
		_bankArray[_nbBank]->setProxyUserPwd(proxyUserPwd.c_str());		
		_nbBank++;
		TiXmlNode *translistNode = childNode->FirstChildElement("translist");
		if(!translistNode)
			return false;
       	if(!feedTransArray(translistNode))
          	  	return false;
	}	            
    return true;
}
bool MyParameters::feedTransArray(TiXmlNode *node)
{
	for (TiXmlNode *childNode = node->FirstChildElement("trans");
		childNode ;
		childNode = childNode->NextSibling("trans"))
	{
		const char *transCode = (childNode->ToElement())->Attribute("code");
		const char *transName = (childNode->ToElement())->Attribute("name");

        TiXmlNode *requestNode = childNode->FirstChildElement("request");
        const char *templateFile = (requestNode->ToElement())->Attribute("templateFile");
        if(!templateFile)
            return false;
        Trans trans;
        trans._transCode=transCode;
        trans._transName=transName;
        trans._request._templateFile=templateFile;
      //  trans._request.FieldMap.clear();
      //  trans._response.FieldMap.clear();
    	for (TiXmlNode *varNode = requestNode->FirstChildElement("var");
		varNode;
		varNode = varNode->NextSibling("var") )
        {
            const char *desc=(varNode->ToElement())->Attribute("desc");
            const char *name=(varNode->ToElement())->Attribute("name");
            const char *cpack=(varNode->ToElement())->Attribute("cpack");
            if(!desc||!name||!cpack)
                return false;
//            field._name=name;
	     Field field;
            field.desc=desc;
            field.cpack=cpack;
            trans._request.FieldMap[name]=field;
        }
        TiXmlNode *responseNode = childNode->FirstChildElement("response");
        const char *dataName = (responseNode->ToElement())->Attribute("dataName");
        const char *recordName = (responseNode->ToElement())->Attribute("recordName");
        const char *recordCount = (responseNode->ToElement())->Attribute("recordCount");
	    if(dataName)
		    trans._response.dataNodeName=dataName;
	    if(recordName)
		    trans._response.recordNodeName=recordName;
	    if(recordCount)
		    trans._response.recordCount=recordCount;
	
    	for (TiXmlNode *fieldNode = responseNode->FirstChildElement("field");
		fieldNode;
		fieldNode = fieldNode->NextSibling("field") )
        {
            const char *desc=(fieldNode->ToElement())->Attribute("desc");
            const char *name=(fieldNode->ToElement())->Attribute("name");
            const char *cpack=(fieldNode->ToElement())->Attribute("cpack");
            const char *type=(fieldNode->ToElement())->Attribute("type");			
            if(!desc||!name||!cpack)
                return false;
	     Field field;
            field.desc=desc;
            field.cpack=cpack;
	     field.type=FIELDTYPE_RESP;
	     if(type)
	     {
			if(strcmp(type,"input")==0)
				field.type=FIELDTYPE_REQ;
			else if(strcmp(type,"fixval")==0)
				field.type=FIELDTYPE_FIXVAL;
		 	if(strcmp(type,"single")==0)
		            	trans._response.SingleFieldMap[name]=field;		 	
		     	else
		            	trans._response.CycleFieldMap[name]=field;
	     }
	    else
		   	trans._response.CycleFieldMap[name]=field;

        }
        if(_bankArray[_nbBank-1]->_transArray.hasEnoughSpace())
            _bankArray[_nbBank-1]->_transArray.addTrans(trans);
        else
            return false;
	}
    return true;
}
bool MyParameters::loadTemplateFile()
{

    for(int i=0;i<_nbBank;i++)
    {
        for(int j=0;j<_bankArray[i]->_transArray._nbTrans;j++)
        {
            Trans& t=_bankArray[i]->_transArray._transArray[j];
            std::ifstream  ifs(t._request._templateFile.c_str());  
            if(!ifs.good())
            {
                cout<<"load templatefile:"<<t._request._templateFile<<" failed!"<<endl;
                return false;
            }
            istreambuf_iterator<char>  beg(ifs),end;   
            t._request._templateStr= string(beg,end);
            ifs.close();
            t._request.varList.clear();
            getVarList(t._request._templateStr.c_str(),t._request.varList);
          //  for(int k=0;k<t._request.varList.size();k++)
          //      cout<<"varlist"<<k<<"=>"<<t._request.varList[k]<<endl;
        }
    } 
    return true;
}

