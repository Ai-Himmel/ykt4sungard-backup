
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

class CSList  //�������ַ��ָ����ݵ���
{
public:
	CSList();
	virtual ~CSList();

	bool FillStrings(const char *mainstring); //����࣬mainstring�����ָ��
	bool Add(char *buffer);     //���������

	int GetBuff(char *buffer,bool trimflag=false);  //�õ��зָ���������ַ���

	void SetAt(char *buffer,int nIndex);  //�޸ĵ�nIndex��������
	char * GetAt(int nIndex);   //�õ�ĳ��������

	void Clear();    //���
	int GetCount();  //���ݸ���

public:
	STRINGLIST m_lst;
	int m_count;
};

#endif //__SLIST_H__
