// PushThread.h: interface for the CPushThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUSHTHREAD_H__255A119D_F398_422E_90BB_DFA47DF22B17__INCLUDED_)
#define AFX_PUSHTHREAD_H__255A119D_F398_422E_90BB_DFA47DF22B17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WThread.h"
#include "dbf.h"
#include "vector"

class CDestStatus  
{
public:
   unsigned short iDestNo; // Ŀ����ͨѶƽ̨�ڵ��
   unsigned short iFuncNo; // Ŀ����ע�Ṧ�ܺ�

   unsigned int  batchno; // ��ǰĿ���ĻỰID ����ע���¼ʱ���䣬ֱ���´��µ�¼ʱ+1��

   int    iSourceNo;  // ��Ŀ������ͨ���ĸ�ͨѶƽ̨���͵ݴ�����
   time_t tSendTime;  // �ϴη��͵�ʱ��
   time_t tSendTime0; // �״η��͵�ʱ��
   unsigned int unAckRecord; // �ϴ�δȷ�ϵļ�¼

public:
	CDestStatus();
	CDestStatus(const CDestStatus &ds);
	virtual ~CDestStatus();

};

// Ŀ����Ϊ�˴��ڴ���ɨ���¼���ݣ�������ֱ��ɨ�����ͼ�¼�⣬�Լӿ촦���ٶȣ����ٻ�������
class CPushRecord  
{
public:
   int  bunit;             // ���������ĸ�BULink����ģ���ackflag='2'��Ч
   unsigned int recno;     // ԭʼ���ͼ�¼��
   unsigned short destno;  
   unsigned short funcno;
   char ackflag;           // ȷ��״̬���� 1/2 a/b-������δȷ�ϣ�
   time_t patime;          // ����ʱ��
   time_t valid_at;          // �ڶ��ʱ�䱻ȷ�ϲ�����Ч�����򣬾ͱ�������������Ҫ����
   
public:
	CPushRecord();
   CPushRecord(const CPushRecord &pr);
	virtual ~CPushRecord();

};


typedef std::list<CDestStatus> VPUSHDEST;
typedef std::list<CPushRecord> VPUSHRECORD;


class CPushThread : public CWThread  
{
public:
   int         m_index;    // ��ǰ���ӵ�ͨѶƽ̨���
   CDRTPRouter *pRouter;    // ������ص�ͨѶƽ̨

private:
   CDBF        m_pdbf;
   int         m_pdbfdate; // ��ǰʹ�õ����ͼ�¼������
   int         lastrecord;   // ��ǰ��������һ������XDBF���ݿ��¼��
   VPUSHDEST   vdeststatus;  // Ŀ��״̬��
   VPUSHRECORD vprecords;    // �뱾������ص����ͼ�¼����Ҫȷ�ϵģ�

   char        pdata[MAXDATASIZE]; // ���ڴ���������ݵĻ���
   char        szMsg[256];   // ��������Ϣ
   
public:
	CPushThread();
	virtual ~CPushThread();

private:
	bool ReadAckData();
	int PushDataInClient(CPushRecord *pPR, int pdlen=0);
	bool SetPushDbfRecord(unsigned int recno, char ackflag);
	int ReadPushRecord(CPushRecord *pData,int &routerid, char *packdata, int &pdlen);
	int Run();

};

#endif // !defined(AFX_PUSHTHREAD_H__255A119D_F398_422E_90BB_DFA47DF22B17__INCLUDED_)
