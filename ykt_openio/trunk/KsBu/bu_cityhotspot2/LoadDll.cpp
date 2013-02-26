#include ".\loaddll.h"
#include "DllFunErrCode.h"
#include "DllFun.h"
#include <iostream>
#include <profile.h>

ini_pack_para g_ini_para;

bool ReadIni1(char *inifile)
{
	TIniFile tf;
	printf("Begin to read ini-file:%s...\n",inifile);
	if (!tf.Open(inifile))
		return false;
	g_ini_para.timeout = tf.ReadInt("SERVER", "TIMEOUT", 5000);
	g_ini_para.port = tf.ReadInt("SERVER", "PORT", 5050);
	tf.ReadString("SERVER", "IP", "127.0.0.1", g_ini_para.ip, sizeof(g_ini_para.ip) - 1);
	tf.Close();
	return(true);   
}
CLoadDll::CLoadDll(void) : m_h_data_info_dll(NULL)
{
}

CLoadDll::~CLoadDll(void)
{
}

int CLoadDll::LoadDataInfo(std::string str_dll_name)
{
	if(!ReadIni1((char*)str_dll_name.c_str()))
		return -1000;			// 读取配置文件出错
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