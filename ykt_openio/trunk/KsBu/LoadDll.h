#ifndef _LOAD_DLL_H_
#define _LOAD_DLL_H_

#pragma once

#include <string>


class CLoadDll
{
public:
	CLoadDll(void);
	~CLoadDll(void);
	int LoadDataInfo(std::string str_dll_name = "");
	void UnLoadAllDll();
	int Init();
private:
	void * m_h_data_info_dll;
};

#endif