#include ".\loaddll.h"
#include "DllFunErrCode.h"
#include "DllFun.h"
#include <iostream>

DEF_DLLFUNC(GetDataInfo);
DEF_DLLFUNC(SaveInfo);
//#ifdef SYNJONES_FUNC
DEF_DLLFUNC(InitDB);
//#endif
DEF_DLLFUNC(CloseDB);

DEF_DLLFUNC(CNectDB);
DEF_DLLFUNC(GetRoomName);
DEF_DLLFUNC(SellElec);
DEF_DLLFUNC(GetDBStatus);
DEF_DLLFUNC(GetRemainE);
//DEF_DLLFUNC(GetEPrice);

DEF_DLLFUNC(GetPersonInfo);

//////////////////////////////////////////////////////////////////////////
// 兼容原来的旧接口
DEF_DLLFUNC(registe_module);
DEF_DLLFUNC(unregiste_module);

ksf_plugin_module g_global_module;

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
	/*
	LOAD_DLLFUNC(m_h_data_info_dll,CNectDB);
	LOAD_DLLFUNC(m_h_data_info_dll,GetRoomName);
	LOAD_DLLFUNC(m_h_data_info_dll,SellElec);
	LOAD_DLLFUNC(m_h_data_info_dll,GetDBStatus);
	LOAD_DLLFUNC(m_h_data_info_dll,GetRemainE);
//	LOAD_DLLFUNC(m_h_data_info_dll,GetEPrice);
	*/
	//LOAD_DLLFUNC(m_h_data_info_dll,GetDataInfo);
	LOAD_DLLFUNC(m_h_data_info_dll,registe_module);
	LOAD_DLLFUNC(m_h_data_info_dll,unregiste_module);
	memset(&g_global_module,0,sizeof g_global_module);
	if(registe_module(&g_global_module))
		return 	DLLFUN_ERR_NO_DLL;
	
	/*
	if(g_global_module.module_init())
	{
		return DLLFUN_ERR_NO_DLL;
	}
	*/
	std::cout<<"加载插件成功";
//	LOAD_DLLFUNC(m_h_data_info_dll,SaveInfo);
//#ifdef SYNJONES_FUNC
//	LOAD_DLLFUNC(m_h_data_info_dll,InitDB);
//#endif
//	LOAD_DLLFUNC(m_h_data_info_dll,CloseDB);

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