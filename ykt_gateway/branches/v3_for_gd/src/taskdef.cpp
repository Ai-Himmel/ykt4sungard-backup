
#include "taskdef.h"

/*
#include <ACEXML/common/StrCharStream.h>
#include <ACEXML/common/DefaultHandler.h>
#include <ACEXML/parser/parser/Parser.h>
#include <ACEXML/common/InputSource.h>
 */
#include <ace/OS.h>
#include "tinyxml.h"
#include "ksgateway.h"

///////////////////////////////////////////////////////////////////////////////
//
int KSGTaskParams::Parse(const std::string& str)
{
	TiXmlDocument doc;
	if(str.empty())
		return -1;
	doc.Parse(str.c_str());
	TiXmlNode* root = doc.FirstChild("taskdef");
	if(!root)
		return -1;
	TiXmlNode* elem = root->FirstChild();
	while(elem!=NULL)
	{
		//elem->f
		TiXmlNode* t = elem->FirstChild();
		if(t)
			PutParam(elem->Value(),t->Value());
		else
			PutParam(elem->Value(),"");
		elem = elem->NextSibling();
	}
	return 0;

}
	std::string KSGTaskParams::GetParam(const std::string& key) const
throw(KeyNotFoundException)
{
	KeyValueMap::const_iterator i = _params.find(key);
	if(i == _params.end())
	{
		throw KeyNotFoundException();
	}
	return i->second;
}

	int KSGTaskParams::GetParamIntVal(const std::string& key) const
throw(KeyNotFoundException)
{
	try
	{
		std::string val = GetParam(key);
		return ACE_OS::atoi(val.c_str());
	}
	catch(KeyNotFoundException& e)
	{
		throw e;
	}
}

	double KSGTaskParams::GetParamDblVal(const std::string& key) const
throw(KeyNotFoundException)
{
	try
	{
		std::string val = GetParam(key);
		return ACE_OS::strtod(val.c_str(),NULL);
	}
	catch(KeyNotFoundException& e)
	{
		throw e;
	}
}

void KSGTaskParams::PutParam(const std::string& key,const std::string& val)
{
	KeyValueMap::iterator i = _params.find(key);
	if( i == _params.end() )
	{
		_params.insert(KeyValueMap::value_type(key,val));
		return;
	}
	//_params.insert(KeyValueMap::value_type)
	//i->second = val;
}
//////////////////////////////////////////////////////////////////////
void KSGTaskResponse::AddField(const std::string& key,int value)
{
	char buf[64] = "";
	ACE_OS::sprintf(buf,"%d",value);
	AddField(key,buf);
}
void KSGTaskResponse::AddField(const std::string& key,unsigned int value)
{
	char buf[64] = "";
	ACE_OS::sprintf(buf,"%u",value);
	AddField(key,buf);
}
void KSGTaskResponse::AddField(const std::string& key,long value)
{
	char buf[64] = "";
	ACE_OS::sprintf(buf,"%ld",value);
	AddField(key,buf);
}
void KSGTaskResponse::AddField(const std::string& key,unsigned long value)
{
	char buf[64] = "";
	ACE_OS::sprintf(buf,"%lu",value);
	AddField(key,buf);
}
void KSGTaskResponse::AddField(const std::string& key,double value)
{
	char buf[64] = "";
	ACE_OS::sprintf(buf,"%f",value);
	AddField(key,buf);
}
void KSGTaskResponse::AddField(const std::string& key,const std::string& value)
{
	_content.insert(ValueType::value_type(key,value));
}
void KSGTaskResponse::AddField(const std::string& key,const char* value,size_t len)
{
	std::string tmp(value,len);
	AddField(key,tmp);
}

//////////////////////////////////////////////////////////////////////
//
ACE_Time_Value KSGGetTaskTimeoutIntval()
{
	return ACE_Time_Value(0,KsgGetGateway()->GetConfig()->_execTimeout*1000);
}
