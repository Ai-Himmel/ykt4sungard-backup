/********************************************************************
	created:	2007/11/15
	created:	15:11:2007   11:38
	filename: 	D:\proj\ksbass\testipc\MQDLL\BUSem.h
	file path:	D:\proj\ksbass\testipc\MQDLL
	file base:	BUSem
	file ext:	h
	author:		Yonghua.Chen
	
	purpose:	Ϊ���ܹ�����һ���ʺ���Windows��Unix��Linux�µ�һ���źŵ�
         ����Windows�µ��źŵƲ����ó����������ˣ�����ƽ̨Ҳ��ֻѡ��һ���ź���
*********************************************************************/
// BUSem.h: interface for the CBUSem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUSEM_H__A7F8F520_79EE_4798_ABB6_9F2846FA15DB__INCLUDED_)
#define AFX_BUSEM_H__A7F8F520_79EE_4798_ABB6_9F2846FA15DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#include <windows.h>
#define H_SEMP HANDLE
#define INVALID_SEMP NULL
#else
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define H_SEMP int
#define INVALID_SEMP -1

//#define MAXSEMPNO 100 ��AIX�²��Թ����У���������64�����ϵ��̲߳��Ե�ʱ�򣬻��Ե��൱����, �ɴ˻����������
#define MAXSEMPNO 50
#endif


class CBUSem  
{
private:
   H_SEMP m_sempid;
   int    m_sempno;

public:
	void Remove(const char *name, int semid);
	bool Open(const char *name, int semid, int maxvalue);
	void SetValue(int value);
	int GetValue();
	bool IsOpened();
	int V();               // �ͷſ�����Դ����������SEMP���� +1
	int P(int usTimeout);  // ���ٿ�����Դ����������SEMP���� -1
	void Close();
	CBUSem();
	virtual ~CBUSem();

private:
   
};

#endif // !defined(AFX_BUSEM_H__A7F8F520_79EE_4798_ABB6_9F2846FA15DB__INCLUDED_)
