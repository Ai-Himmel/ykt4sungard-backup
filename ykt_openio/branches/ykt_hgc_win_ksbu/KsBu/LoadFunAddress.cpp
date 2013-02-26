#include "LoadAppAddress.h"
#include "DllFun.h"

//DEF_DLLFUNC(GetPersonInfo);

/*
HINSTANCE h_sl_person_info_dll = NULL;

CLoadDll::CLoadDll() : m_h_sl_person_info_dll(NULL)
{

}

int CLoadDll::LoadSLPersonInfo(std::string str_dll_name)
{
	if (m_h_sl_person_info_dll)
		return 0;

	m_h_sl_person_info_dll = ::LoadLibrary(str_dll_name.c_str());
	if (NULL == m_h_sl_person_info_dll)
		return DLLFUN_ERR_NO_DLL;

	LOAD_DLLFUNC(m_h_sl_person_info_dll,GetPersonInfo);
	return 0;
}

void CLoadDll::UnLoadAllDll()
{
	if (m_h_sl_person_info_dll)
	{
		::FreeLibrary(m_h_sl_person_info_dll);
		m_h_sl_person_info_dll = NULL;
	}

	/************************************************************************/
	/* 以后可以添加......                                                                    
	/************************************************************************/

//	return ;
//}