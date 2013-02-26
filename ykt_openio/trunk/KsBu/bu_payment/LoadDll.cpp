#include "loaddll.h"
#include "DllFunErrCode.h"
#include "profile.h"

bool ReadIni1(char *inifile)
{
	TIniFile tf;
	
	printf("Begin to read ini-file:%s...\n",inifile);
	if (!tf.Open(inifile))
		return false;

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
	return ;
}
int CLoadDll::Init()
{
	return 0;
}