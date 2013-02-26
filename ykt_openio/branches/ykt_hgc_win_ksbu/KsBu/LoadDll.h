#ifndef _LOAD_DLL_H_
#define _LOAD_DLL_H_

#pragma once

#include <string>
#include <WTypes.h>

class CLoadDll
{
public:
	CLoadDll(void);
	~CLoadDll(void);
	int LoadDataInfo(std::string str_dll_name = "");
	int LoadDataInfo(std::string str_dll_name, int dll_type);
	void UnLoadAllDll();
private:
	HINSTANCE m_h_data_info_dll;
};

#endif