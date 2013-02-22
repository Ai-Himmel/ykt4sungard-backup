// ExceptionErr.h: interface for the CExceptionErr class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable: 4786)
#include <string>
#include <map>

#if !defined(AFX_EXCEPTIONERR_H__8E00BACC_E8C0_47B9_BAB9_947C3FDF7C81__INCLUDED_)
#define AFX_EXCEPTIONERR_H__8E00BACC_E8C0_47B9_BAB9_947C3FDF7C81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

class CExceptionErr  
{
public:
	int ShowErrMsg(int error_code);
	int SearchErr(int error_code);
	CExceptionErr();
	virtual ~CExceptionErr();

private:
	map<int, std::string> m_map_err_info;
	CString m_err_msg;
	int m_err_count;
};

#endif // !defined(AFX_EXCEPTIONERR_H__8E00BACC_E8C0_47B9_BAB9_947C3FDF7C81__INCLUDED_)
