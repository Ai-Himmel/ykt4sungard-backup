#ifndef _CC_INIFILE_H_
#define _CC_INIFILE_H_

#ifdef _MSC_VER
#pragma once
#pragma warning (disable: 4786)
#endif

#include <string>
#include <vector>
#include <map>

class CCIniFile
{
public:
	CCIniFile();
	CCIniFile(const std::string &fileName);
	~CCIniFile(void);

private:
	static int ms_maxBufferSize;
	std::string m_fileName;
	std::string m_str_ini_name;
	char m_str_full_path[1024];
	

public:
	std::string ReadString(const char* section, const char* indent, const char* defaultValue);
	bool WriteString(const char* section, const char* indent, const char* value);
	void ReadSections(std::vector<std::string>& sect);
	void ReadSectionValues(const char* section,std::map<std::string,std::string>& values);
	void ReadSection(const char* section,std::vector<std::string>& keys);
	int ReadInteger(const char* section, const char* indent,int defaultValue);
	bool ReadBoolean(const char* section,const char* indent,bool defaultValue);

public:
	void GetIniName(char *str_ini_name);
	void SetIniName(const char *str_ini_name);
	int GetIniFile();
};

#endif // _CC_INIFILE_H_