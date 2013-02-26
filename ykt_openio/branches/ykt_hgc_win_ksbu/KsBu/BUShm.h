/********************************************************************
	created:	2005/07/08
	created:	8:7:2005   19:44
	filename: 	D:\proj\ksbass\SHMTest\BUShm.h
	file path:	D:\proj\ksbass\SHMTest
	file base:	BUShm
	file ext:	h
	author:		CHENYH
	
	purpose:	 ����ϣ���ṩһ�ֿ����ڶ�����£�ʹ�ù����ڴ��ķ���
            Ϊ�˴����������̶�ʹ�õĹ����ڴ�飬����ͳһʹ��һ��key_t
            ��һ����0xXXXXXXXX��ʾ�Ĺؼ��֣�Ϊ�˼�ʹ�÷���������Ͳ���
            ftok��������ֵ�ˡ�

            CBUShm�����ڴ���Դʹ�÷�����
            1. ������Ϊ���ṩ��һ����ͬһ�����ϵĲ�ͬ����ͨ�������ڴ���Դ
            ���ٹ���һЩ���ݣ�
            2. ����ʹ�ø�������ʹ����ͬ��KEY���һ����ͬ�Ĺ����ڴ���Դ��
            3. ��ȡ��������Open(...)���õ��������̷��ʹ����ڴ�ӳ���ڴ��ַshmptr��
            4. �ڵõ�ӳ���ڴ��ַshmptr�󣬶�д���ݿ���ֱ��ͨ�������ж�д��
            5. Ϊ�˱�����ͬһʱ��ͬʱ�����������ݣ��ڱ�Ҫ��ʱ�򣬿��ԶԹ����ڴ���Դ
            ���м�����
            6. �ڼ����������ʱ������ֱ�����ڴ�ӳ���ַ������Ҫͨ����������ʵ��
            ͨ��Lock()������Unlock()������
            7. ����Ҫ�������ڴ���Դ��ϵͳ��ɾ���������Ҫ�ñ���ʵ������Remove(...)��
            ɾ����ӦKEY�Ĺ����ڴ���Դ�������ʵ���Ѿ��ɹ��򿪲���û�б��رգ���ô��
            ɾ����ʵ���Ĺ����ڴ���Դ�����ʱ��ͺ�semkey��shmkey�޹ء�
*********************************************************************/
// BUShm.h: interface for the CBUShm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUSHM_H__24B9323D_EFD2_40DE_AC7B_C68A7B7F7566__INCLUDED_)
#define AFX_BUSHM_H__24B9323D_EFD2_40DE_AC7B_C68A7B7F7566__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#include <windows.h>
typedef int key_t;
typedef HANDLE SHMID;
#define INVALID_ID NULL
#else
/* ****** Updated by CHENYH at 2005-7-8 19:06:12 ****** 
����ϵͳƽ̨�������Ҫ������Щͷ�ļ���
#include <sys/types.h>
#include <sys/ipc.h>
*******************************************************/
#include <sys/shm.h>
typedef int SHMID;
#define INVALID_ID -1
#endif

#ifdef KSSHMT_EXPORTS
#define KSSHMT_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define KSSHMT_API __declspec(dllimport)
#else
#define KSSHMT_API 
#endif
#endif

class KSSHMT_API CBUShm  
{
private:
   int m_fileno;        // ���ڼ������ļ�, Ҳ���ǻ����ļ�
   SHMID m_shmid;       // �����ڴ�ID
   int m_size;          // �������ڴ泤��
   void *m_address;     // �����ڴ�ռ��ڱ������еĵ�ַ
   char m_szmsg[256];   // �ڴ����ʱ�����ڴ�Ŵ�����Ϣ

public:
	bool Unlock(int offset=0, int len = -1);
	bool Lock(int offset=0,int len=-1);

   // ������: Remove
   // ���  : ������ 2006-1-4 15:37:15
   // ����  : ɾ��ָ���Ĺ����ڴ���Դ
   // ����  : bool 
   // ����  : const char *name [IN]:ָ���ù����ڴ������
	static bool Remove(const char *name);

   // ������: CBUShm::Open
   // ���  : ������ 2005-7-8 23:07:22
   // ����  : �ñ���ʵ����һ�����̿ɱ��������ڴ�����
   //       ע�⣺��ʹ�ñ�������ʱ�򣬽���������ȷ��shmsize;
   //             ע�⣬���ﷵ�ص�ӳ���ַ����ϵͳ���صģ���Ҫ�����Ի�ָ��
   // ����  : void * NULL����ʧ�ܣ����򣬷��سɹ��򿪵Ĺ����ڴ�����Ľ���ӳ���ַ��
   // ����  : const char *name: ָ���ù����ڴ�����֣���name==NULLʱ������������������
   // ����  : int shmsize��������򿪵Ĺ����ڴ��С
	void * Open(const char *name, int shmsize);

   static key_t myftok(const char *path, int ID);



   // ������: GetSHMPtr
   // ���  : ������ 2005-7-10 15:13:07
   // ����  : �õ��������ڴ�ӳ�䵽�����̵��ڴ��ַ
   // ����  : void * ���������ڴ�ӳ��ĵ�ַ����û��ʹ��Open�򿪻��Ѿ����ر�
   //          ��ʱ�򣬷���ΪNULL��
	void * GetSHMPtr();

   // ������: GetMessage
   // ���  : ������ 2005-7-10 15:11:38
   // ����  : �������������ڴ���Դ��ʱ��������ش��󣬿���ͨ����
   //         �����õ�������Ϣ
   // ����  : char * ���ڲ���������У����һ�δ�����Ϣ
	char * GetMessage();

   // ������: Close
   // ���  : ������ 2005-7-9 0:13:21
   // ����  : �رձ�������Դ���Ӵ˱����̾Ͳ���ʹ�ñ���Դ�ˣ�
   //          ���ǲ�����ϵͳ��ɾ������Դ
   // ����  : void 
	void Close();

   // ������: Unlock
   // ���  : ������ 2005-7-9 0:12:45
   // ����  : �������Դ�Ǳ����̼����ģ�����н���
   // ����  : bool: �����Ƿ�ɹ�������false������GetMessage()�õ�������Ϣ 

   // ������: Lock
   // ���  : ������ 2005-7-9 0:11:47
   // ����  : �Ա���Դ���м���������ģʽ��
   // ����  : bool: �Ƿ�����ɹ�������false������GetMessage()�õ�������Ϣ
   
   CBUShm();
	virtual ~CBUShm();

private:
	bool locktype(int ltype, unsigned int offset, unsigned int  len);
};

#undef KSSHMT_API

#endif // !defined(AFX_BUSHM_H__24B9323D_EFD2_40DE_AC7B_C68A7B7F7566__INCLUDED_)
