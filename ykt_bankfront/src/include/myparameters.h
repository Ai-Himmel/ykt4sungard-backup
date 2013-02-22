/* ----------------------------------------------------------
 * 程序名称：myparameters.h
 * 创建日期：2007-12-19
 * 程序作者：闻剑
 * 版本信息：1.0.0.0
 * 程序功能：解析xml配置文件类
 * ----------------------------------------------------------*/


#ifndef MYPARAMETERS_H
#define MYPARAMETERS_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "tinyxml.h"
using namespace std;
#define FIELDTYPE_RESP	0
#define FIELDTYPE_REQ   1
#define FIELDTYPE_FIXVAL 2

#define mystrcpy(des,src)  { \
    	    int minSize = ((sizeof(des) - 1) < strlen(src))?(sizeof(des) - 1):strlen(src);\
		    int i = 0;\
		    for (;i < minSize;i++)\
			    des[i] = src[i];\
		    des[i] = '\0';\
        }

#define MAX_PATH  260

const char localConfFile[] = "bankconf.xml";

//	void cutString(const char *str2cut, vector<string> & patternVect);


//	static int strVal(const char *str, int base) {
//		if (!str) return -1;
//		if (!str[0]) return 0;
//	
//	    char *finStr;
//	    int result = strtol(str, &finStr, base);
//	    if (*finStr != '\0')
//	        return -1;
//	    return result;
//	};

//	static int decStrVal(const char *str) {
//	    return strVal(str, 10);
//	};
//	
//	static int hexStrVal(const char *str) {
//	    return strVal(str, 16);
//	};

struct Field {
    string desc;
    string cpack;
    int 	type;
};
struct HeadField {
    Field bankCode;
    Field transCode;
    Field refID;
    Field date;
    Field time;
    Field corpID;
    Field userID;
    Field userPwd;
};
struct ReqHead {
    string bankCode;
    string transCode;
    string refID;
    string date;
    string time;
    string corpID;
    string userID;
    string userPwd;
};
struct Request {
    string _templateFile;
    string _templateStr;
    map<string,Field>   FieldMap;
    vector<string>  varList;
};
struct Response {
    string dataNodeName;
    string recordNodeName;
    string recordCount;
    map<string,Field>  SingleFieldMap;
    map<string,Field>  CycleFieldMap;
};
struct NetConfig {
	int timeout;
	int 	port;
	string protocol;
	string url;
	string ip;
	NetConfig& operator=(const NetConfig& nc)
	{
		if (this != &nc)
       	 {
	            this->timeout= nc.timeout;
		     this->protocol=nc.protocol;
		     this->ip=nc.ip;
		     this->port=nc.port;
		     this->url=nc.url;
		}
		return *this;
	}
};
struct Trans {
    string _transCode;
    string _transName;
    Request _request;
    Response _response;
};
const int MAX_TRANS=20;
struct TransArray
{
friend class MyParameters;
public:
    TransArray() : _nbTrans(0){}

    TransArray & operator=(const TransArray & ta)
    {
        if (this != &ta)
        {
            this->_nbTrans = ta._nbTrans;
            for (int i = 0 ; i < _nbTrans ; i++)
            {
                this->_transArray[i] = ta._transArray[i];
            }
        }
        return *this;
    }

    int getNbTrans() const {return _nbTrans;}
	void setNbTrans(int nb) {_nbTrans = nb;}

    Trans & getTrans(int index) {return _transArray[index];}

    bool hasEnoughSpace() {return (_nbTrans < MAX_TRANS);}

	void addTrans(const Trans trans) {
        _transArray[_nbTrans]=trans;
		_nbTrans++;
	}

    int getTransIndexByTransCode(const char *transCode) {
		if (!transCode)
			return -1;
        for (int i = 0 ; i < _nbTrans ; i++)
            if (!strcmp(_transArray[i]._transName.c_str(), transCode))
                return i;
        return -1;

    }
    int getTransIndexByName(const char *name) const {
		if (!name)
			return -1;
        for (int i = 0 ; i < _nbTrans ; i++)
            if (!strcmp(_transArray[i]._transName.c_str(), name))
                return i;
        return -1;
    }
    Trans * getTransByCode(const char *code) {
	 if (!code) return NULL;
        for (int i = 0 ; i < _nbTrans ; i++)
        {
            if (!strcmp(_transArray[i]._transCode.c_str(), code))
                return &(_transArray[i]);
        }
        return NULL;
    }

protected:
	Trans _transArray[MAX_TRANS];
	int _nbTrans;
};
class BankContainer
{
friend class MyParameters;
public:
    TransArray  _transArray;
    map<string,string> currencySourceMap;
    map<string,string> currencyTargetMap;

	BankContainer(const char *bankCode,const char *bankName) 
    {
        _bankCode=bankCode;
        _bankName=bankName;
    };
	BankContainer & operator=(const BankContainer & bc)
	{
		if (this != &bc)
       	 {
	            this->_bankCode= bc._bankCode;
	            this->_bankName= bc._bankName;
		     this->_ncSign =bc._ncSign;
		     this->_ncService=bc._ncService;
		     this->_ncVerify=bc._ncVerify;	
		     this->_proxyHostPort=bc._proxyHostPort;
		     this->_proxyUserPwd=bc._proxyUserPwd;
	            this->_transArray = bc._transArray;
		}
		return *this;
	}
	~BankContainer() {};
	const string& getBankCode() const {return _bankCode;}
	const string& getBankName() const {return _bankName;}	
	void setNCService(const NetConfig& nc)
	{
		 _ncService=nc;
	}
	void setNCSign(const NetConfig& nc)
	{
		_ncSign=nc;
	}
	void setNCVerify(const NetConfig& nc)
	{
		_ncVerify=nc;
	}
	void setProxyHostPort(const char *hostport)
	{
		_proxyHostPort = hostport;
	}	
	void setProxyUserPwd(const char *userpwd)
	{
		_proxyUserPwd = userpwd;
	}		
	NetConfig& getNCSign(){return _ncSign;}
	NetConfig& getNCService(){return _ncService;}
	NetConfig& getNCVerify(){return _ncVerify;}
	string& getProxyHostPort() {return _proxyHostPort;}
	string& getProxyUserPwd() {return _proxyUserPwd;}	
private:
	string _bankName;
	string  _bankCode;
	NetConfig _ncService;
	NetConfig _ncSign;
	NetConfig _ncVerify;
//	NetConfig _ncProxy;
	string _proxyHostPort;
	string _proxyUserPwd;
};
const int MAX_BANK=20;
class MyParameters
{
public:
	static MyParameters * getInstance() {return _pSelf;}
	bool load();
	void destroyInstance();
	const char * getAppPath() const {return _appPath;}
	BankContainer* getBAFromBankCode(const char *bankCode)
	{
	     if(!bankCode)
		    return NULL;
	     for (int i = 0 ; i < _nbBank; i++)
	     {
	            if (!strcmp(bankCode, _bankArray[i]->_bankCode.c_str()))                
				return _bankArray[i];
	     }
	     return NULL;
	}
	HeadField headField;
private:
	MyParameters();	
	~MyParameters() {
		for (int i = 0 ; i < _nbBank; i++)
			delete _bankArray[i];	
	}
	static MyParameters *_pSelf;

	TiXmlDocument *_pXmlDoc;
	char _appPath[MAX_PATH];
	bool getBankConfigFromXmlTree();
	bool feedBankConfig(TiXmlNode *node);
	bool feedTransArray(TiXmlNode *node);
	bool loadTemplateFile();
	BankContainer *_bankArray[MAX_BANK];
	int _nbBank;
};

#endif //MYPARAMETERS_H
