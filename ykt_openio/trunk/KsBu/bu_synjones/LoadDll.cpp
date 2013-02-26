#include ".\loaddll.h"
#include "DllFunErrCode.h"
#include "DllFun.h"
#include <iostream>


//#ifdef SYNJONES_FUNC
DEF_DLLFUNC(GetDataInfo);
DEF_DLLFUNC(SaveInfo);
//#ifdef SYNJONES_FUNC
DEF_DLLFUNC(InitDB);
//#endif
DEF_DLLFUNC(CloseDB);


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

	// TODO : 新中兴接口库名称
	str_dll_name = "";
	m_h_data_info_dll = ::LoadLibrary(str_dll_name.c_str());
	if (NULL == m_h_data_info_dll)
		return DLLFUN_ERR_NO_DLL;

	
	LOAD_DLLFUNC(m_h_data_info_dll,GetDataInfo);
	LOAD_DLLFUNC(m_h_data_info_dll,SaveInfo);
	LOAD_DLLFUNC(m_h_data_info_dll,InitDB);
	LOAD_DLLFUNC(m_h_data_info_dll,CloseDB);
	std::cout<<"加载插件成功";
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