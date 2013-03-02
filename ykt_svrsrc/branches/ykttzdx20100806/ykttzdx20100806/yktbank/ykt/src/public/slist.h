
#ifndef __SLIST_H
#define __SLIST_H

/********************************************************
	处理以字符分割数据的类头文件
	文件名: slist.h
	说明: 包含处理以字符分割数据的类头文件和自定义宏、类型，函数声明。
	创建: 
	修改: 吴卫文 2000-04-03
	修改原因: 规范编码
**********************************************************/
#include "stdafx.h"
#include "iostream"
#include "list"
#define MAXCOLUMN 4096
using namespace std;
typedef list<string>STRINGLIST;
class CSList  //处理以字符分割数据的类
{
public:
	char * trim(char *s);
	bool FillStrings(char *mainstring,char separator='|'); //填充类，mainstring包含分割符
	int GetBuff(char *buffer,bool trimflag=true);  //得到有分割符的整个字符串
	void Clear();    //清除
	int GetCount();  //数据个数
	void SetAt(char *buffer,int nIndex);  //修改第nIndex个数据项
	char * GetAt(int nIndex);   //得到某个数据项
	bool Add(char *buffer);     //添加数据项
	CSList();
	virtual ~CSList();

private:
	STRINGLIST m_lst;
	int m_count;
	char m_separator[2];
};

#endif 

