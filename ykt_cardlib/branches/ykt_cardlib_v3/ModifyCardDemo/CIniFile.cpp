#include "StdAfx.h"
#include "CIniFile.h"
#include "GlobalDef.h"

#ifdef WIN32
#include <Windows.h>
#endif

using namespace std;

int CCIniFile::ms_maxBufferSize = 16384;	// 16K

CCIniFile::CCIniFile() : m_str_ini_name("\\CardDll.ini")
{
	memset(m_str_full_path, 0, sizeof(m_str_full_path));		
}

CCIniFile::CCIniFile(const string &fileName)
:m_fileName(fileName)
{
}

CCIniFile::~CCIniFile(void)
{
}

string CCIniFile::ReadString(const char* section, const char* indent,
							 const char* defaultValue)
{
#ifdef WIN32
	char buffer[2048] = "";
	int len = GetPrivateProfileString(section,indent,defaultValue,
		buffer,sizeof buffer,m_fileName.c_str());
	return string(buffer,len);
#else
	throw exception();
#endif
}

bool CCIniFile::WriteString(const char* section, const char* indent,
							const char* value)
{
#ifdef WIN32
	BOOL bRet = WritePrivateProfileString(section,indent,value,m_fileName.c_str());
	return (bRet ? true : false);
#else
	throw exception();
#endif
}

void CCIniFile::ReadSections(vector<string>& sect)
{
#ifdef WIN32
	char * buffer = new char[ms_maxBufferSize];
	char *p;
	if(GetPrivateProfileString(NULL,NULL,NULL,buffer,
		ms_maxBufferSize,m_fileName.c_str()) != 0)
	{
		p = buffer;
		while(*p != '\0')
		{
			string section(p);
			sect.push_back(section);
			p += strlen(p) + 1;
		}
	}
	delete [] buffer;
#else
	throw exception();
#endif
}

void CCIniFile::ReadSectionValues(const char* section,map<string,string>& values)
{
#ifdef WIN32
	vector<string> keys;
	ReadSection(section,keys);
	vector<string>::iterator iter;
	for (iter = keys.begin();iter != keys.end();++iter)
	{
		string value = ReadString(section,(*iter).c_str(),"");
		pair<string,string> inPair(*iter,value);
		values.insert(inPair);
	}
#else
	throw exception();
#endif 

}

void CCIniFile::ReadSection(const char* section,vector<string>& keys)
{
#ifdef WIN32
	char * buffer = new char[ms_maxBufferSize];
	char *p;
	if(GetPrivateProfileString(section,NULL,NULL,buffer,
		ms_maxBufferSize,m_fileName.c_str()) != 0)
	{
		p = buffer;
		while(*p != '\0')
		{
			string key(p);
			keys.push_back(key);
			p += strlen(p) + 1;
		}
	}
	delete [] buffer;
#else
	throw exception();
#endif
}

int CCIniFile::ReadInteger(const char* section, const char* indent,int defaultValue)
{
	string v;
	v = ReadString(section,indent,"");
	if(v.empty())
	{
		return defaultValue;
	}
	int ret = atoi(v.c_str());
	return ret;
}

bool CCIniFile::ReadBoolean(const char* section,const char* indent,bool defaultValue)
{
	string v;
	v = ReadString(section,indent,"");
	if(v.empty())
	{
		return defaultValue;
	}
	if(!stricmp("TRUE",v.c_str()) 
		|| !stricmp("YES",v.c_str()) 
		|| !stricmp("1",v.c_str()))
	{
		return true;
	}
	else if(!stricmp("FALSE",v.c_str()) 
		|| !stricmp("NO",v.c_str()) 
		||!stricmp("0",v.c_str()))
	{
		return false;
	}
	return false;
}

int CCIniFile::GetIniFile()
{
	int len = GetModuleFileName(NULL, m_str_full_path, 1024);
	if(len <= 0)
	{	
		return KS_ERR_NOLOCALEXE;
	}
	m_str_full_path[len] = '\0';
	char *pos = strrchr(m_str_full_path, '\\');
	if (pos)
		strcpy(pos, m_str_ini_name.c_str());
	else
		return KS_ERR_NOINITFILE;

	return 0;
}

void CCIniFile::SetIniName(const char *str_ini_name)
{
	m_str_ini_name = str_ini_name;
}

void CCIniFile::GetIniName(char *str_ini_name)
{
	strcpy(str_ini_name, m_str_ini_name.c_str());
}