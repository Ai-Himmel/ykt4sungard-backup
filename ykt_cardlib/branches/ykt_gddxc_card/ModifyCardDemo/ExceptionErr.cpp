// ExceptionErr.cpp: implementation of the CExceptionErr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModifyCardDemo.h"
#include "ExceptionErr.h"
#include "GlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExceptionErr::CExceptionErr() : m_err_msg(""), m_err_count(0)
{
	int err_count = 0;
	while (g_Err_Def[err_count].err_code != KS_ERR_EXIT)
	{
		m_map_err_info[g_Err_Def[err_count].err_code] = g_Err_Def[err_count].err_info;
		++err_count;
	}
	m_err_count = err_count;
}

CExceptionErr::~CExceptionErr()
{

}

int CExceptionErr::SearchErr(int error_code)
{
	try
	{
		if (error_code > g_Err_Def[m_err_count - 1].err_code || error_code < g_Err_Def[0].err_code)
			throw exception();
		else
			return	ShowErrMsg(error_code);
	}
	catch (exception e)
	{
		return	ShowErrMsg(KS_ERR_EXIT);
	}
}


int CExceptionErr::ShowErrMsg(int error_code)
{
	char str_err_code[5] = "";
	m_err_msg = m_map_err_info[error_code].c_str();
	itoa(error_code, str_err_code, 10);
	MessageBox(NULL, (LPCSTR)m_err_msg, str_err_code, NULL);
	return 0;
}
