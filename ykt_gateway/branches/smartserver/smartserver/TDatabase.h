// TDatabase.h : ADO���ݿ������װ��
//
// ���ļ���ǰ�òɼ��������������ɲ���֮һ.
// Copyright (C) ?-2004 �㶫�����ǻ۵�����Ϣ��ҵ���޹�˾
// ��������Ȩ��.
// 
// ����&ʱ��:  ��ΰ  2004.02
//
// ���ļ���������TDatabase��/TRecordset��/TDatabasePool��/TDBRecord
// 
#if !defined(AFX_TDATABASE_H__EF1F7E7A_0929_4E05_9E50_BD4AFAF292E2__INCLUDED_)
#define AFX_TDATABASE_H__EF1F7E7A_0929_4E05_9E50_BD4AFAF292E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const DWORD DB_QUERY_TIMEOUT = 2000 ;
const DWORD DB_LOGIN_TIMEOUT = 2000 ;

//�������ݿ�����
enum DBSType
{
	DB_TYPE_TEST,       //��������
	DB_TYPE_DEBUG,      //����
	DB_TYPE_NORMAL,     //����
	DB_TYPE_TASK		//����̬��
};

//******************************************************************************
//*����: TDatabase
//*����: ��װADO���ݿ��ȡ
//******************************************************************************
class TDatabase
{
protected:
	_ConnectionPtr 	m_Connect;

	TLock	m_Lock;

	BOOL	m_bOpen;
	BOOL	m_bFree;

	DBSType m_nDBSType;
	int     m_nType;

	DWORD	m_dwQueryTimeOut;
	DWORD	m_dwLoginTimeOut;

	TCHAR	m_szErrorText[512];
	TCHAR   m_szConnect[512];

public:
	TDatabase();
	TDatabase(DBSType nDBType, int nType, LPCTSTR pszServer, LPCTSTR pszUser, LPCTSTR pszPass);
	virtual ~TDatabase();

	virtual BOOL Open(int nType, LPCTSTR pszServer, LPCTSTR pszUser, LPCTSTR pszPass);
	virtual void Close();

	BOOL BeginTrans();
	BOOL Rollback();
	BOOL CommitTrans();

	BOOL ExecuteSQL(LPCTSTR pszSQL);

	void SetLoginTimeout(DWORD dwTimeOut) { m_dwLoginTimeOut = DB_LOGIN_TIMEOUT; }
	void SetQueryTimeout(DWORD dwTimeOut) { m_dwLoginTimeOut = DB_QUERY_TIMEOUT; }

	BOOL IsOpen() const { return m_bOpen; }
	LPCTSTR GetConnect() const ;
	BOOL IsBusy() const ;

	DBSType GetDBSType() const { return m_nDBSType; }

	void SetBusy(BOOL bBool);

	TDatabase& operator=(const TDatabase& Database);
	_ConnectionPtr GetHandle() const { return m_Connect; }

	void SetErrorText(LPCTSTR pszErrorText)
	{
		lstrcpy(m_szErrorText, pszErrorText);
	}

	friend class TRecordset;
};

//******************************************************************************
//*����: TRecordset
//*����: ADO���ݿ��¼��
//******************************************************************************
class TRecordset
{
protected:
	BOOL			m_bOpen;

	_ConnectionPtr	m_Connect;
	_RecordsetPtr   m_Recordset;

	TCHAR			m_szErrorText[256];

public:
	TRecordset();
	TRecordset(TDatabase *pDB);
	virtual ~TRecordset();

	void SetDatabase(TDatabase *pDB);

	virtual BOOL Open(LPCTSTR pszQuery, CursorTypeEnum nCursorType = adOpenDynamic);
	virtual void Close();

	BOOL IsOpen() const { return m_bOpen; }

	BOOL IsBOF();
	BOOL IsEOF();

	BOOL MoveFirst();
	BOOL MoveLast();
	BOOL MoveNext();
	BOOL MovePrev();

	UINT GetFieldCount();
	LONG GetRecordCount();

	BOOL GetFieldName(UINT nIndex, LPTSTR pszRetFieldName);

	BOOL GetFieldValue(UINT nFieldIndex, LPTSTR pszRetFieldValue);
	BOOL GetFieldValue(LPCTSTR pszFieldName, LPTSTR pszRetFieldValue);

	BOOL GetFieldValue(UINT nFieldIndex, long *pFieldValue);
	BOOL GetFieldValue(LPCTSTR pszFieldName, long *pFieldValue);

	BOOL GetFieldValue(UINT nFieldIndex, float *pFieldValue);
	BOOL GetFieldValue(LPCTSTR pszFieldName, float *pFieldValue);

	BOOL GetFieldValue(UINT nFieldIndex, double *pFieldValue);
	BOOL GetFieldValue(LPCTSTR pszFieldName, double *pFieldValue);

	void SetErrorText(LPCTSTR pszErrorText)
	{
		lstrcpy(m_szErrorText, pszErrorText);
	}

	LPCTSTR GetErrorText() const { return m_szErrorText; }
};

//******************************************************************************
//*����: TRecordset
//*����: �򵥵����ݿ����ӳ�(���Զ���������������)
//******************************************************************************
class TDatabasePool
{
protected:
	LONG	m_nConnect;
	int     m_nMax;

	BOOL	m_bSchedule;
	LONG	m_nBusyCount;

	TLock	m_DBLock;
	TList	m_DBList;

protected:
	virtual void Monitor();

	void AddDatabase(TDatabase *pDB);
	void DelDatabase(TDatabase *pDB);

	virtual void DoSchedule(LONG nScheduleTime);
	virtual TDatabase* GetNewDatabase(DBSType nDBType, int nType, LPCTSTR pszServer, LPCTSTR pszUser, LPCTSTR pszPass);

public:
	TDatabasePool();
	virtual ~TDatabasePool();

	void Initialized(int nMax);
	void Clear();

	void AddDatabase(int nCount, DBSType nDBType, int nType, LPCTSTR pszServer, LPCTSTR pszUser, LPCTSTR pszPass);
	void DelDatabase(long nIndex);

	void FreeDatabase(TDatabase *pDB);
	TDatabase* GetFreeDatabase(int nFlag);

	void DestoryDatabasePool();

	long GetDBCount();
};

//******************************************************************************
//*����: TDBRecord
//*����: ��������ݿ���Դ��
//******************************************************************************
class TDBRecord
{
public:
	TRecordset   m_dbRs;
	TDatabase   *m_pdb;         
	DWORD        m_dwTick;      //���

public:
	TDBRecord();
	virtual ~TDBRecord();

	void MakeActived();
	void Release();
	bool IsActived();
};

#endif // !defined(AFX_TDATABASE_H__EF1F7E7A_0929_4E05_9E50_BD4AFAF292E2__INCLUDED_)
