#ifndef _CC_INIFILE_H_
#define _CC_INIFILE_H_

#ifdef _MSC_VER
#pragma once
#pragma warning (disable: 4786)
#endif

#include <string>
#include <vector>
#include <map>
#include "StdAfx.h"

class CCIniFile
{
public:
	//! constructor
	/*!
	 \param filename INI�ļ���·��
	 */
	CCIniFile(const std::string &fileName);
	~CCIniFile(void);
private:
	//<! buffer ��С
	static int ms_maxBufferSize;
	//<! Ini�ļ���
	std::string m_fileName;
public:
	//! ��ȡ�ַ���ֵ
	std::string ReadString(const char* section, const char* indent, const char* defaultValue);
	//! д��INI�ļ�
	bool WriteString(const char* section, const char* indent, const char* value);
	//! ��ȡ���е� Section
	void ReadSections(std::vector<std::string>& sect);
	//! ��ȡsection������ key�� value
	void ReadSectionValues(const char* section,std::map<std::string,std::string>& values);
	//! ��ȡsection�µ����� key
	void ReadSection(const char* section,std::vector<std::string>& keys);
	//! ��ȡ����ֵ
	int ReadInteger(const char* section, const char* indent,int defaultValue);
	//! ��ȡ����ֵ�������� true , false , yes ,no ,1 , 0)
	bool ReadBoolean(const char* section,const char* indent,bool defaultValue);
};

#endif // _CC_INIFILE_H_
