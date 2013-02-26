#include ".\loaddll.h"
#include "DllFunErrCode.h"
#include "DllFun.h"
#include <iostream>
#include <profile.h>

DEF_DLLFUNC(fCommandTS);
DEF_DLLFUNC(fInit);

ini_pack_para g_ini_para;

bool ReadIni1(char *inifile)
{
	TIniFile tf;
	printf("Begin to read ini-file:%s...\n",inifile);
	if (!tf.Open(inifile))
		return false;
	g_ini_para.flash_dealy = tf.ReadInt("TIME", "INIT_DELAY", 60);
	g_ini_para.dynamic_load_flag = tf.ReadInt("DLLFLAG", "DYNAMIC_LOAD_FLAG", 0);
	g_ini_para.sysjones_func = tf.ReadInt("DLLFLAG", "SYNJONES_FUNC", 0);
	tf.ReadString("DLLFLAG", "CARDDLL", "", g_ini_para.third_part_dll_name, sizeof(g_ini_para.third_part_dll_name) - 1);
	g_ini_para.port = tf.ReadInt("THIRD_ACCOUNT", "PORT", 0);
	tf.ReadString("THIRD_ACCOUNT", "USER_ID", "", g_ini_para.user_id, sizeof(g_ini_para.user_id) - 1);
	tf.ReadString("THIRD_ACCOUNT", "USER_PWD", "", g_ini_para.encrypt_pwd, sizeof(g_ini_para.encrypt_pwd) - 1);
	tf.ReadString("THIRD_ACCOUNT", "IP", "", g_ini_para.ip, sizeof(g_ini_para.ip) - 1);
	tf.ReadString("DLLFLAG", "DESDLL", "", g_ini_para.des_dll_name, sizeof(g_ini_para.des_dll_name) - 1);
	g_ini_para.debug_log = tf.ReadInt("THIRD_ACCOUNT", "DEBUG_LOG", 0);
	g_ini_para.des_flag = tf.ReadInt("DLLFLAG", "DESDLL_FLAG", 0);

	tf.Close();
	return(true);   
}

int GetRGRetData(char *result, char *key_name, char *value_name)
{
	char *pdest = NULL;
	char *plast = NULL;
	char count = 0;

	if (0 == strncmp(result, RG_SUCC, RG_FLAG_LEN))				// SUCCESSFUL
	{
		return 0;	
	}
	else if (0 == strncmp(result, RG_ACK, RG_FLAG_LEN))
	{
		pdest = strstr(result, key_name);
		pdest += strlen(key_name);
		pdest += strlen(RG_SPLIT2);
		plast = strstr(pdest, RG_SPLIT2);
		count = plast - pdest;
		strncpy(value_name, pdest, count);
	}
	else if (0 == strncmp(result, RG_ERR, RG_FLAG_LEN))
	{
		pdest = result;
		pdest += RG_FLAG_LEN;
		pdest += strlen(RG_SPLIT3);
		strcpy(value_name, pdest);

		return -1;
	}

	return 0;
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

	if (m_h_data_info_dll)
		return 0;

	str_dll_name = "samspiclient.dll";
	m_h_data_info_dll = ::LoadLibrary(str_dll_name.c_str());
	if (NULL == m_h_data_info_dll)
		return DLLFUN_ERR_NO_DLL;

	LOAD_DLLFUNC(m_h_data_info_dll,fInit);
	LOAD_DLLFUNC(m_h_data_info_dll,fCommandTS);


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