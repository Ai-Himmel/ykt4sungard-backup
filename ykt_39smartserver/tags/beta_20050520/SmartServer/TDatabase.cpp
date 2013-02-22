// TDatabase.cpp: implementation of the TDatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TDatabase.h"

const DWORD ACTIVE_TIME = 1000 * 60 * 2; //活跃时间为2分钟

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TDatabase::TDatabase()
{
	m_bFree = TRUE ;
	m_Connect = NULL ;
	m_bOpen = FALSE ;
	m_dwQueryTimeOut = DB_QUERY_TIMEOUT;
	m_dwLoginTimeOut = DB_LOGIN_TIMEOUT;

	lstrcpy(m_szErrorText, _T(""));
}

TDatabase::TDatabase(DBSType nDBType, int nType, LPCTSTR pszServer, LPCTSTR pszUser, LPCTSTR pszPass)
{
	m_nDBSType = nDBType ;

	m_bFree = TRUE ;
	m_Connect = NULL ;
	m_bOpen = FALSE ;

	m_dwQueryTimeOut = DB_QUERY_TIMEOUT;
	m_dwLoginTimeOut = DB_LOGIN_TIMEOUT;

	lstrcpy(m_szErrorText, _T(""));

	if( !Open(nType, pszServer, pszUser, pszPass) )
	{
		throw TException(m_szErrorText);
	}
}

TDatabase::~TDatabase()
{
	Close();
}

BOOL TDatabase::Open(int nType, LPCTSTR pszServer, LPCTSTR pszUser, LPCTSTR pszPass)
{
	ZeroMemory(m_szConnect, sizeof(m_szConnect));

	switch(nType)
	{
	case DB_TYPE_ACCESS:
		wsprintf(m_szConnect,"Provider=Microsoft.Jet.OLEDB.3.51;File Name=%s;User ID=%s;Password=%s",
			pszServer, pszUser, pszPass);
		break;
	case DB_TYPE_SQLSERVER:
		wsprintf(m_szConnect,"Provider=sqloledb;Data Source=%s;User Id=%s;Password=%s;",
			pszServer, pszUser, pszPass);
		break;
	default:
		wsprintf(m_szConnect,"Provider=MSDAORA;Data Source=%s;User ID=%s;Password=%s",
			pszServer, pszUser, pszPass);
		break;
	}

	try
	{
		m_bFree = TRUE ;
		m_bOpen = FALSE ;

		CoInitialize(NULL);

		HRESULT hr = m_Connect.CreateInstance(__uuidof(Connection));
		if( FAILED(hr) )
		{
			throw TException("初始化OLE环境失败!不能创建ADO对象!!");
		}

		m_Connect->ConnectionTimeout = m_dwLoginTimeOut ;
		m_Connect->CommandTimeout = m_dwQueryTimeOut ;

		hr = m_Connect->Open((_bstr_t)m_szConnect, "", "", NULL);
		if( FAILED(hr) )
		{
			_com_issue_error(hr);
			return FALSE;
		}

		m_bOpen = TRUE ;
	}
	catch(_com_error &e)
	{
		TCHAR  szText[512];
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());
		wsprintf(szText, "打开数据库失败(服务名:%s,用户:%s,密码:%s). %s %s", 
			pszServer, pszUser, pszPass, (LPCSTR) bstrSource, (LPCSTR) bstrDescription);
		SetErrorText(szText);
		return FALSE;
	}
	catch(TException& e)
	{
		TCHAR  szText[512];
		wsprintf(szText, "打开数据库失败(服务名:%s,用户:%s,密码:%s). %s", 
			pszServer, pszUser, pszPass, e.GetText());
		SetErrorText(szText);
		return FALSE;
	}

	return TRUE;
}

void TDatabase::Close()
{
	if( m_Connect != NULL )
	{
		if( m_Connect->GetState() != adStateClosed )
		{
			if( IsBusy() )
			{
				Sleep(20);
			}
			m_Connect->Close();
		}
		m_Connect = NULL ;
	}
	m_bOpen = FALSE ;
}

BOOL TDatabase::BeginTrans()
{
	if( !IsOpen() )
		return FALSE;

	try
	{
		m_Connect->BeginTrans();
	}
	catch(_com_error &e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}
	return TRUE;
}

BOOL TDatabase::Rollback()
{
	if( !IsOpen() )
		return FALSE;

	try
	{
		m_Connect->RollbackTrans();
	}
	catch(_com_error &e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}
	return TRUE;
}

BOOL TDatabase::CommitTrans()
{
	if( !IsOpen() )
		return FALSE;

	try
	{
		m_Connect->CommitTrans();
	}
	catch(_com_error &e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}
	return TRUE;
}

BOOL TDatabase::IsBusy() const 
{
	return !m_bFree;
}

BOOL TDatabase::ExecuteSQL(LPCTSTR pszSQL)
{
	if( !IsOpen() )
	{
		m_bFree = TRUE ;
		return FALSE;
	}

	char szProc[32];
	strcpy(szProc, "execute");

	try
	{
		m_bFree = FALSE ;
		if( _strnicmp(pszSQL, szProc, strlen(szProc) ))
			m_Connect->Execute((_bstr_t)pszSQL, NULL, adCmdText);
		else
		{
			m_Connect->Execute((_bstr_t)&pszSQL[strlen(szProc)], NULL, adCmdStoredProc);
		}
	}
	catch(_com_error &e)
	{
		m_bFree = TRUE ;
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}

	m_bFree = TRUE ;

	return TRUE;
}

LPCTSTR TDatabase::GetConnect() const 
{
	return m_szConnect;
}

TDatabase& TDatabase::operator=(const TDatabase& Database)
{
	m_bOpen = Database.m_bOpen;
	m_Connect = Database.m_Connect;
	m_dwLoginTimeOut = Database.m_dwLoginTimeOut;
	m_dwQueryTimeOut = Database.m_dwQueryTimeOut;

	lstrcpy(m_szErrorText, Database.m_szErrorText);
	lstrcpy(m_szConnect, Database.m_szConnect);

	return *this;
}

void TDatabase::SetBusy(BOOL bBool)
{
	m_Lock.Lock();
	m_bFree = bBool;
	m_Lock.Unlock();
}

TRecordset::TRecordset()
{
	m_bOpen = FALSE ;
	m_Connect = NULL ;
	m_Recordset = NULL ;
	lstrcpy(m_szErrorText, _T(""));
}

TRecordset::TRecordset(TDatabase *pDB)
{
	m_bOpen = FALSE ;
	m_Connect = pDB->m_Connect ;
	m_Recordset = NULL ;
	lstrcpy(m_szErrorText, _T(""));
}

void TRecordset::SetDatabase(TDatabase *pDB)
{
	m_Connect = pDB->m_Connect ;
}

TRecordset::~TRecordset()
{
	Close();
}

BOOL TRecordset::Open(LPCTSTR pszQuery, CursorTypeEnum nCursorType)
{
	try
	{
		m_bOpen = FALSE;

		HRESULT hr = m_Recordset.CreateInstance(__uuidof(Recordset));
		if( FAILED(hr) )
		{
			return FALSE;
		}

		hr = m_Recordset->Open(pszQuery, 
						_variant_t((IDispatch *)m_Connect,true), 
						nCursorType,
						adLockReadOnly, adCmdText);
		if( FAILED(hr) )
		{
			return FALSE;
		}

		m_bOpen = TRUE;
	}
	catch(_com_error& e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}
	
	return TRUE;
}

void TRecordset::Close()
{
	if( m_bOpen )
	{
		m_Recordset->Close();
		m_bOpen = FALSE ;
	}
}

BOOL TRecordset::IsBOF()
{
	return m_Recordset->BOF;
}

BOOL TRecordset::IsEOF()
{
	return m_Recordset->EndOfFile;
}

BOOL TRecordset::MoveFirst()
{
	HRESULT hr = m_Recordset->MoveFirst();
	if( FAILED(hr) )
	{
		return FALSE;
	}
	return TRUE;
}

BOOL TRecordset::MoveLast()
{
	HRESULT hr = m_Recordset->MoveLast();
	if( FAILED(hr) )
	{
		return FALSE;
	}
	return TRUE;
}

BOOL TRecordset::MoveNext()
{
	if( IsEOF() )
		return TRUE ;

	HRESULT hr = m_Recordset->MoveNext();
	if( FAILED(hr) )
	{
		return FALSE;
	}
	return TRUE;
}

BOOL TRecordset::MovePrev()
{
	if( IsBOF() )
		return TRUE;

	HRESULT hr = m_Recordset->MovePrevious();
	if( FAILED(hr) )
	{
		return FALSE;
	}
	return TRUE;
}

UINT TRecordset::GetFieldCount()
{
	LONG nRecCount = 0 ;

	if( IsOpen() )
	{
		nRecCount = m_Recordset->Fields->GetCount();
	}
	return (UINT)nRecCount;
}

LONG TRecordset::GetRecordCount()
{
	long hr = m_Recordset->GetRecordCount();
	if( hr == -1 )
	{
		m_Recordset->MoveLast();
		hr = m_Recordset->GetRecordCount();
	}
	return hr;
}

BOOL TRecordset::GetFieldName(UINT nIndex, LPTSTR pszRetFieldName)
{
	if( IsOpen() )
	{
		_variant_t  var;
		var.vt = VT_I2;
		var.iVal = nIndex; 

		pszRetFieldName = (LPTSTR)m_Recordset->Fields->GetItem(var)->GetName();
		if( lstrcmp(pszRetFieldName, _T("")) )
			return TRUE;
	}
	return FALSE;
}

BOOL TRecordset::GetFieldValue(UINT nFieldIndex, LPTSTR pszRetFieldValue)
{
	_variant_t varValue;
	varValue.vt = VT_I2;
	varValue.iVal = nFieldIndex; 

	BOOL bRet = TRUE ;
	_variant_t  var;

	strcpy(pszRetFieldValue, "");

	try
	{
		var = m_Recordset->Fields->GetItem(varValue)->GetValue();
		switch(var.vt)
		{
		case VT_DATE:	//DATE
			if( FAILED(VarI1FromDate(var.date, pszRetFieldValue)) ) 
			{
				bRet = FALSE ;
			}
			break;
		case VT_BSTR:	//BSTR 
			{
			_bstr_t  varNew(var);
			lstrcpy(pszRetFieldValue, (LPCTSTR)varNew);
			}
			break;
		case VT_I1:     //char
			lstrcpy(pszRetFieldValue, (LPTSTR)var.cVal);
			break;
		default:
			bRet = FALSE;
			break;
		}
	}
	catch(_com_error& e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}

	return bRet;
}

BOOL TRecordset::GetFieldValue(LPCTSTR pszFieldName, LPTSTR pszRetFieldValue)
{
	BOOL bRet = TRUE ;
	_variant_t  var;

	strcpy(pszRetFieldValue, "");

	try
	{
		var = m_Recordset->Fields->GetItem(pszFieldName)->GetValue();
		switch(var.vt)
		{
		case VT_DATE:	//DATE
			if( FAILED(VarI1FromDate(var.date, pszRetFieldValue)) ) 
			{
				bRet = FALSE ;
			}
			break;
		case VT_BSTR:	//BSTR 
			{
			_bstr_t  varNew(var);
			lstrcpy(pszRetFieldValue, (LPCTSTR)varNew);
			}
			break;
		case VT_I1:     //char
			lstrcpy(pszRetFieldValue, (LPTSTR)var.cVal);
			break;
		default:
			bRet = FALSE;
			break;
		}
	}
	catch(_com_error& e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}

	return bRet;
}

BOOL TRecordset::GetFieldValue(UINT nFieldIndex, long *pFieldValue)
{
	_variant_t varValue;
	varValue.vt = VT_I2;
	varValue.iVal = nFieldIndex; 		

	BOOL bRet = TRUE ;
	_variant_t  var;

	*pFieldValue = 0 ;

	try
	{
		var = m_Recordset->Fields->GetItem(varValue)->GetValue();
		switch(varValue.vt)
		{
		case VT_UI1:	//Byte
			*pFieldValue = (long)var.bVal;
		case VT_BOOL:	//VARIANT_BOOL            
			*pFieldValue = (long)var.boolVal;
			break;
		case VT_I2:		//Short                   
			*pFieldValue = (long)var.iVal;
			break;
		case VT_I4:		//long                    
			*pFieldValue = (long)var.lVal;
			break;
		case VT_UI4:	//unsigned long           
		case VT_DECIMAL:
			*pFieldValue = (long)var.lVal;
			break;
		case VT_UI2:	//unsigned short          
			*pFieldValue = (long)var.uiVal;
			break;
		case VT_INT:	//int                     
			*pFieldValue = (long)var.intVal;
			break;
		case VT_UINT:	//unsgiend int
			*pFieldValue = (long)var.uintVal;
			break;
		default:
			bRet = FALSE ;
			break;
		}
	}
	catch(_com_error& e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}

	return bRet;
}

BOOL TRecordset::GetFieldValue(LPCTSTR pszFieldName, long *pFieldValue)
{
	BOOL bRet = TRUE ;
	_variant_t  var;

	*pFieldValue = 0 ;

	try
	{
		var = m_Recordset->Fields->GetItem(pszFieldName)->GetValue();
		switch(var.vt)
		{
		case VT_UI1:	//Byte
			*pFieldValue = (long)var.bVal;
			break;
		case VT_BOOL:	//VARIANT_BOOL            
			*pFieldValue = (long)var.boolVal;
			break;
		case VT_I2:		//Short                   
			*pFieldValue = (long)var.iVal;
			break;
		case VT_I4:		//long                    
		case VT_DECIMAL:
			*pFieldValue = (long)var;
			break;
		case VT_UI4:	//unsigned long           
			*pFieldValue = (long)var.ulVal;
			break;
		case VT_UI2:	//unsigned short          
			*pFieldValue = (long)var.uiVal;
			break;
		case VT_INT:	//int                     
			*pFieldValue = (long)var.intVal;
			break;
		case VT_UINT:	//unsgiend int
			*pFieldValue = (long)var.uintVal;
			break;
		default:
			bRet = FALSE ;
			break;
		}
	}
	catch(_com_error& e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}

	return bRet;
}

BOOL TRecordset::GetFieldValue(UINT nFieldIndex, float *pFieldValue)
{
	_variant_t varValue;
	varValue.vt = VT_I2;
	varValue.iVal = nFieldIndex; 		

	BOOL bRetCode = TRUE ;
	_variant_t  var;

	*pFieldValue = 0.00;

	try
	{
		var = m_Recordset->Fields->GetItem(varValue)->GetValue();
		switch(var.vt)
		{
		case VT_R4:
			*pFieldValue = var.fltVal ;
			break;
		case VT_CY:
			{
				char sBuffer[32];

				ZeroMemory(sBuffer, sizeof(sBuffer));
				if( FAILED(VarI1FromCy(var.cyVal, sBuffer)) )
					bRetCode = FALSE ;
				else
					*pFieldValue = (float)atof(sBuffer);
			}
		default:
			bRetCode = FALSE ;
			break;
		}
	}
	catch(_com_error& e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}

	return bRetCode;
}

BOOL TRecordset::GetFieldValue(LPCTSTR pszFieldName, float *pFieldValue)
{
	BOOL bRetCode = TRUE ;
	_variant_t  var;

	*pFieldValue = 0.00;

	try
	{
		var = m_Recordset->Fields->GetItem(pszFieldName)->GetValue();
		switch(var.vt)
		{
		case VT_R4:
			*pFieldValue = var.fltVal ;
			break;
		case VT_CY:
			{
				char sBuffer[32];

				ZeroMemory(sBuffer, sizeof(sBuffer));
				if( FAILED(VarI1FromCy(var.cyVal, sBuffer)) )
					bRetCode = FALSE ;
				else
					*pFieldValue = (float)atof(sBuffer);
			}
		default:
			bRetCode = FALSE ;
			break;
		}
	}
	catch(_com_error& e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}

	return bRetCode;
}

BOOL TRecordset::GetFieldValue(UINT nFieldIndex, double *pFieldValue)
{
	_variant_t varValue;
	BOOL bRetCode = TRUE ;
	_variant_t  var;

	*pFieldValue = 0.00;

	varValue.vt = VT_I2;
	varValue.iVal = nFieldIndex; 		

	try
	{
		var = m_Recordset->Fields->GetItem(varValue)->GetValue();
		switch(var.vt)
		{
		case VT_R8:
			*pFieldValue = var.dblVal;
			break;
		default:
			bRetCode = FALSE;
			break;
		}
	}
	catch(_com_error& e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}
	return bRetCode;
}

BOOL TRecordset::GetFieldValue(LPCTSTR pszFieldName, double *pFieldValue)
{
	BOOL bRetCode = TRUE ;
	_variant_t  var;

	*pFieldValue = 0.00;

	try
	{
		var = m_Recordset->Fields->GetItem(pszFieldName)->GetValue();
		switch(var.vt)
		{
		case VT_R8:
			*pFieldValue = var.dblVal;
			break;
		default:
			bRetCode = FALSE;
			break;
		}
	}
	catch(_com_error& e)
	{
		SetErrorText(e.ErrorMessage());
		return FALSE;
	}
	return bRetCode;
}

TDatabasePool::TDatabasePool()
{
	m_DBList.Clear();

	m_bSchedule = FALSE ;

	m_nMax = 10 ;
	m_nBusyCount = 0 ;
}

TDatabasePool::~TDatabasePool()
{
	DestoryDatabasePool();
}

void TDatabasePool::Initialized(int nMax)
{
	if( nMax < 1 )
		throw TException("数据库参数不正确!");

	m_nBusyCount = 0 ;
	m_nMax = nMax ;
	m_DBList.Clear();
	m_bSchedule = TRUE ;
}

void TDatabasePool::AddDatabase(int nCount, DBSType nDBType, int nType, LPCTSTR pszServer, LPCTSTR pszUser, LPCTSTR pszPass)
{
	TDatabase *pDB = NULL ;

	for(long n=0; n< nCount && GetDBCount() <= m_nMax; n++)
	{
		pDB = GetNewDatabase(nDBType, nType, pszServer, pszUser, pszPass);
		if( pDB == NULL )
		{
			DestoryDatabasePool();
			throw TException("数据库连接失败!");
		}

		AddDatabase(pDB);
	}
}

void TDatabasePool::DelDatabase(long nIndex)
{
	m_DBLock.Lock();
	if( nIndex < 0 ||  nIndex >= m_DBList.GetCount() )
	{
		m_DBLock.Unlock();
		return ;
	}
	else
	{
		TDatabase *pDB = (TDatabase*)m_DBList[nIndex];
		if( pDB != NULL && !pDB->IsBusy() )
			m_DBList.Remove(pDB);
		m_DBLock.Unlock();
	}
}

TDatabase* TDatabasePool::GetNewDatabase(DBSType nDBType, int nType, LPCTSTR pszServer, LPCTSTR pszUser, LPCTSTR pszPass)
{
	return new TDatabase(nDBType, nType, pszServer, pszUser, pszPass);
}

long TDatabasePool::GetDBCount() 
{
	long n = 0 ;

	m_DBLock.Lock();
	n = m_DBList.GetCount();
	m_DBLock.Unlock();

	return n;
}

void TDatabasePool::AddDatabase(TDatabase *pDB)
{
	m_DBLock.Lock();
	pDB->SetBusy(FALSE);
	m_DBList.Add(pDB);
	m_DBLock.Unlock();
}

void TDatabasePool::DelDatabase(TDatabase *pDB)
{
	m_DBLock.Lock();
	for(long i=0; i< m_DBList.GetCount(); i++)
	{
		TDatabase *pDB = (TDatabase*)m_DBList[i];
		if( pDB != NULL && !pDB->IsBusy() )
		{
			m_DBList.Remove(pDB);
			break;
		}
	}
	m_DBLock.Unlock();
}

void TDatabasePool::Monitor()
{
	if( m_bSchedule )
	{
		DoSchedule(1000);
	}
}

void TDatabasePool::DoSchedule(LONG nScheduleTime)
{

}

TDatabase* TDatabasePool::GetFreeDatabase(int nFlag)
{
	TDatabase *pDB = NULL ;

	m_DBLock.Lock();

	if( m_nBusyCount >= m_DBList.GetCount() )
	{
		m_DBLock.Unlock();
		return NULL;
	}

	for(long n=0; n< m_DBList.GetCount(); n++)
	{
		pDB = (TDatabase *)m_DBList.Get(n);
		if( !pDB->IsBusy() && pDB->GetDBSType() == nFlag )
		{
			pDB->SetBusy(TRUE);
			m_nBusyCount++;
		}
	}

	m_DBLock.Unlock();

	return pDB;
}

void TDatabasePool::FreeDatabase(TDatabase *pDB) 
{
	m_DBLock.Lock();

	m_nBusyCount--;
	pDB->SetBusy(FALSE);

	m_DBLock.Unlock();
}

void TDatabasePool::DestoryDatabasePool()
{
	m_DBLock.Lock();

	for(int i=0; i< m_DBList.GetCount(); i++)
	{
		TDatabase *pDB = (TDatabase *)m_DBList.Get(i);
		if( pDB != NULL )
		{
			pDB->Close();
			delete pDB;
		}
	}

	m_DBList.Clear();

	m_bSchedule = FALSE ;
	m_nBusyCount = 0 ;

	m_DBLock.Unlock();
}


TDBRecord::TDBRecord()
{
	m_pdb = NULL ;
	m_dwTick = 0 ;
	MakeActived();
}

TDBRecord::~TDBRecord()
{
	if( m_dbRs.IsOpen() )
		m_dbRs.Close();
}

void TDBRecord::Release()
{
	if( m_dbRs.IsOpen() )
		m_dbRs.Close();

	m_pdb = NULL ;
	delete this ;
}

bool TDBRecord::IsActived()
{
	return (GetTickCount()-m_dwTick>ACTIVE_TIME?false:true);
}

void TDBRecord::MakeActived()
{
	m_dwTick = GetTickCount();
}
