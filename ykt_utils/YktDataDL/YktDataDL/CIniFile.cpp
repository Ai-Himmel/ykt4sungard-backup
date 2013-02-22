#include <windows.h>
#include "cinifile.h"
using namespace std;

int CCIniFile::ms_maxBufferSize = 16384;	// 16K

CCIniFile::CCIniFile(const string &fileName)
:m_fileName(fileName)
{

}

CCIniFile::~CCIniFile(void)
{
}

// ��ȡ�ַ���ֵ
string CCIniFile::ReadString(const char* section, const char* indent,
							 const char* defaultValue)
{
#ifdef WIN32
	char buffer[2048] = "";
	int len = GetPrivateProfileString(section,indent,defaultValue,
		buffer,sizeof buffer,m_fileName.c_str());
//	AfxMessageBox(buffer);                              // ���Բ��� , buffer(nl8900face.ini)
	return string(buffer,len);
#else
	throw exception("Not support method");
#endif
}

// д��INI�ļ�
bool CCIniFile::WriteString(const char* section, const char* indent,
							const char* value)
{
#ifdef WIN32
	BOOL bRet = WritePrivateProfileString(section,indent,value,m_fileName.c_str());
	return (bRet ? true : false);
#else
	throw exception("Not support method");
#endif
}
// ��ȡ���е� Section 
void CCIniFile::ReadSections(vector<string>& sect)
{
#ifdef WIN32
	char * buffer = new char[ms_maxBufferSize];
	char *p;
	if(GetPrivateProfileString(NULL,NULL,NULL,buffer,
		ms_maxBufferSize,m_fileName.c_str()) != 0)
	{
		p = buffer;
		// ��������һ������2�� '\0'
		while(*p != '\0')
		{
			string section(p);
			sect.push_back(section);
			p += strlen(p) + 1;
	//		AfxMessageBox(p);                                    // ���Բ���
		}
	}
	delete [] buffer;
#else
	throw exception("Not support method");
#endif
}

// ��ȡsection������ key�� value
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
	throw exception("Not support method");
#endif 

}
// ��ȡsection�µ����� key
void CCIniFile::ReadSection(const char* section,vector<string>& keys)
{
#ifdef WIN32
	char * buffer = new char[ms_maxBufferSize];
	char *p;
	if(GetPrivateProfileString(section,NULL,NULL,buffer,
		ms_maxBufferSize,m_fileName.c_str()) != 0)
	{
		p = buffer;
		// ��������һ������2�� '\0'
		while(*p != '\0')
		{
			string key(p);
			keys.push_back(key);
			p += strlen(p) + 1;
		}
	}
	delete [] buffer;
#else
	throw exception("Not support method");
#endif
}

// ��ȡ����ֵ
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
