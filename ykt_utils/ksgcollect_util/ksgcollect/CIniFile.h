#ifndef _CC_INIFILE_H_
#define _CC_INIFILE_H_

#pragma once
#include <string>
#include <vector>
#include <map>

class CCIniFile
{
public:
	CCIniFile(const std::string &fileName);
	~CCIniFile(void);
private:
	// buffer 大小
	static int ms_maxBufferSize;
	// Ini文件名
	std::string m_fileName;
public:
	// 读取字符串值
	std::string ReadString(const char* section, const char* indent, const char* defaultValue);
	// 写入INI文件
	bool WriteString(const char* section, const char* indent, const char* value);
	// 读取所有的 Section
	void ReadSections(std::vector<std::string>& sect);
	// 读取section的所有 key和 value
	void ReadSectionValues(const char* section,std::map<std::string,std::string>& values);
	// 读取section下的所有 key
	void ReadSection(const char* section,std::vector<std::string>& keys);
	// 读取整数值
	int ReadInteger(const char* section, const char* indent,int defaultValue);
	// 读取布尔值（可以是 true , false , yes ,no ,1 , 0)
	bool ReadBoolean(const char* section,const char* indent,bool defaultValue);
};

#endif // _CC_INIFILE_H_