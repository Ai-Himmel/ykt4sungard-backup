
#ifndef __SLIST_H
#define __SLIST_H

/********************************************************
	�������ַ��ָ����ݵ���ͷ�ļ�
	�ļ���: slist.h
	˵��: �����������ַ��ָ����ݵ���ͷ�ļ����Զ���ꡢ���ͣ�����������
	����: 
	�޸�: ������ 2000-04-03
	�޸�ԭ��: �淶����
**********************************************************/
#include "stdafx.h"
#include "iostream"
#include "list"
#define MAXCOLUMN 4096
using namespace std;
typedef list<string>STRINGLIST;
class CSList  //�������ַ��ָ����ݵ���
{
public:
	char * trim(char *s);
	bool FillStrings(char *mainstring,char separator='|'); //����࣬mainstring�����ָ��
	int GetBuff(char *buffer,bool trimflag=true);  //�õ��зָ���������ַ���
	void Clear();    //���
	int GetCount();  //���ݸ���
	void SetAt(char *buffer,int nIndex);  //�޸ĵ�nIndex��������
	char * GetAt(int nIndex);   //�õ�ĳ��������
	bool Add(char *buffer);     //���������
	CSList();
	virtual ~CSList();

private:
	STRINGLIST m_lst;
	int m_count;
	char m_separator[2];
};

#endif 

