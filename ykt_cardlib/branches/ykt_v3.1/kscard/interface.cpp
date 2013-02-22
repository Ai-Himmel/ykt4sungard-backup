#include "interface.h"
#include "CIniFile.h"
#include <Windows.h>
#include "logfile.h"

ks_device_op_t g_dev_op;
ks_reader_dev_t g_reader;
ks_card_info_t g_cardinfo;
ks_enc_op_t g_enc_op;

static int s_is_load = 0;
// 设备接口层
static HMODULE g_device_handle = NULL;
// 算法接口层
static HMODULE g_enc_handle = NULL;

DEF_DLLFUNC(register_device_op);
DEF_DLLFUNC(register_enc_op);


static int do_load_device_layer(HMODULE m)
{
	LOAD_DLLFUNC(m,register_device_op);
	if(register_device_op(&g_dev_op)==0)
		return 0;
	DEBUG_LOG(("注册硬件层失败"));
	return -1;
}

static int do_load_enc_layer(HMODULE m)
{
	LOAD_DLLFUNC(m,register_enc_op);
	if(register_enc_op(&g_enc_op)==0)
		return 0;
	DEBUG_LOG(("注册算法层失败"));
	return -1;
}

int load_interface_layer(const char *path)
{
	char module_path[1024];
	int ret;
	std::string device_dll,enc_dll;
	if(s_is_load == 1)
		return 0;

	sprintf(module_path,"%s\\kscard.ini",path);
	CCIniFile ini(module_path);
	device_dll = ini.ReadString("INTERFACE","DEVICE","");
	enc_dll = ini.ReadString("INTERFACE","ENC","");

	if(device_dll.empty())
	{
		DEBUG_LOG(("未找到设备层接口"));
		return -1;
	}
	if(enc_dll.empty())
	{
		DEBUG_LOG(("未找到算法层接口"));
		return -1;
	}

	sprintf(module_path,"%s\\%s",path,device_dll.c_str());
	g_device_handle = LoadLibrary(module_path);
	if(g_device_handle == NULL)
	{
		DEBUG_LOG(("加载硬件层失败[%s]",device_dll.c_str()));
		return -2;
	}
	ret = do_load_device_layer(g_device_handle);
	if(ret)
		return -1;
	
	// TODO : 加载算法层

	sprintf(module_path,"%s\\%s",path,enc_dll.c_str());
	g_enc_handle = LoadLibrary(module_path);
	if(g_enc_handle == NULL)
	{
		DEBUG_LOG(("加载硬件层失败[%s]",enc_dll.c_str()));
		return -2;
	}
	ret = do_load_enc_layer(g_enc_handle);
	if(ret)
		return -1;
	s_is_load = 1;
	return 0;
}

int free_interface_layer()
{
	if(g_device_handle)
	{
		FreeLibrary(g_device_handle);
		g_device_handle = NULL;
		memset(&g_dev_op,0,sizeof g_dev_op);
	}
	if(g_enc_handle)
	{
		FreeLibrary(g_enc_handle);
		g_enc_handle = NULL;
		memset(&g_enc_op,0,sizeof g_enc_op);
	}

	s_is_load = 0;
	return 0;
}