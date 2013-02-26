#include ".\loaddll.h"
#include "DllFunErrCode.h"
#include "DllFun.h"
#include <iostream>

DEF_DLLFUNC(CNectDB);
DEF_DLLFUNC(GetRoomName);
DEF_DLLFUNC(SellElec);
DEF_DLLFUNC(GetDBStatus);
DEF_DLLFUNC(GetRemainE);


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

	str_dll_name = "jsdykt.dll";
	m_h_data_info_dll = ::LoadLibrary(str_dll_name.c_str());
	if (NULL == m_h_data_info_dll)
		return DLLFUN_ERR_NO_DLL;
	
	LOAD_DLLFUNC(m_h_data_info_dll,CNectDB);
	LOAD_DLLFUNC(m_h_data_info_dll,GetRoomName);
	LOAD_DLLFUNC(m_h_data_info_dll,SellElec);
	LOAD_DLLFUNC(m_h_data_info_dll,GetDBStatus);
	LOAD_DLLFUNC(m_h_data_info_dll,GetRemainE);


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