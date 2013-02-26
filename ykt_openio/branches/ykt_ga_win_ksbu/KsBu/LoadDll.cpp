#include ".\loaddll.h"
#include "DllFunErrCode.h"
#include "DllFun.h"

DEF_DLLFUNC(GetDataInfo);
DEF_DLLFUNC(SaveInfo);
//#ifdef SYNJONES_FUNC
DEF_DLLFUNC(InitDB);
//#endif
DEF_DLLFUNC(CloseDB);
DEF_DLLFUNC(CheckAccountNo);

CLoadDll::CLoadDll(void) : m_h_data_info_dll(NULL)
{
}

CLoadDll::~CLoadDll(void)
{
}

int CLoadDll::LoadDataInfo(std::string str_dll_name)
{
	if (m_h_data_info_dll)
		return 0;

	m_h_data_info_dll = ::LoadLibrary(str_dll_name.c_str());
	if (NULL == m_h_data_info_dll)
		return DLLFUN_ERR_NO_DLL;

	LOAD_DLLFUNC(m_h_data_info_dll,GetDataInfo);
	LOAD_DLLFUNC(m_h_data_info_dll,SaveInfo);
//#ifdef SYNJONES_FUNC
	LOAD_DLLFUNC(m_h_data_info_dll,InitDB);
//#endif
	LOAD_DLLFUNC(m_h_data_info_dll,CloseDB);
	LOAD_DLLFUNC(m_h_data_info_dll,CheckAccountNo);

	return 0;
}

void CLoadDll::UnLoadAllDll()
{
	if (m_h_data_info_dll)
	{
		::FreeLibrary(m_h_data_info_dll);
		m_h_data_info_dll = NULL;
	}

	/************************************************************************/
	/* 以后可以添加......                                                                    
	/************************************************************************/

	return ;
}