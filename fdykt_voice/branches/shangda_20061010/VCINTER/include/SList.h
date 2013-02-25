
#ifndef __SLIST_H__
#define __SLIST_H__

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>

#define MAXCOLUMN 4096

using namespace std;
typedef list<string>STRINGLIST;

class CSList  //处理以字符分割数据的类
{
public:
	CSList();
	virtual ~CSList();

	bool FillStrings(const char *mainstring); //填充类，mainstring包含分割符
	bool Add(char *buffer);     //添加数据项

	int GetBuff(char *buffer,bool trimflag=false);  //得到有分割符的整个字符串

	void SetAt(char *buffer,int nIndex);  //修改第nIndex个数据项
	char * GetAt(int nIndex);   //得到某个数据项

	void Clear();    //清除
	int GetCount();  //数据个数

public:
	STRINGLIST m_lst;
	int m_count;
};

#endif //__SLIST_H__
