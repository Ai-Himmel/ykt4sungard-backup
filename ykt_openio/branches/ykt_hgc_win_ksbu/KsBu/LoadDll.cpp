#include ".\loaddll.h"
#include "DllFunErrCode.h"
#include "DllFun.h"

DEF_DLLFUNC(GetDataInfo);
DEF_DLLFUNC(SaveInfo);
DEF_DLLFUNC(InitDB);
DEF_DLLFUNC(CloseDB);
DEF_DLLFUNC(CNectDB);
DEF_DLLFUNC(GetRoomName);
DEF_DLLFUNC(SellElec);
DEF_DLLFUNC(GetDBStatus);
DEF_DLLFUNC(fCommandTS);
DEF_DLLFUNC(fInit);
DEF_DLLFUNC(encrypt_work_key_asc);
DEF_DLLFUNC(decrypt_work_key_asc);

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
	
	LOAD_DLLFUNC(m_h_data_info_dll,fInit);
	LOAD_DLLFUNC(m_h_data_info_dll,fCommandTS);

	return 0;
}

int CLoadDll::LoadDataInfo(std::string str_dll_name, int dll_type)
{
	if (m_h_data_info_dll)
		return 0;

	m_h_data_info_dll = ::LoadLibrary(str_dll_name.c_str());
	if (NULL == m_h_data_info_dll)
		return DLLFUN_ERR_NO_DLL;

	switch (dll_type)
	{
	case THIRD_RG_DLL:
		LOAD_DLLFUNC(m_h_data_info_dll,fInit);
		LOAD_DLLFUNC(m_h_data_info_dll,fCommandTS);
		break;
	case DESDLL:
		LOAD_DLLFUNC(m_h_data_info_dll,encrypt_work_key_asc);
		LOAD_DLLFUNC(m_h_data_info_dll,decrypt_work_key_asc);
		break;
	default:
	    break;
	}

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