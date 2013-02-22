#include "interface.h"
#include "CIniFile.h"
#include <Windows.h>
#include <fstream>
#include "logfile.h"
#include "kslicense.h"
#include "global_func.h"
#include "cardtypemanager.h"

extern ks_cardlib_license g_license;

extern std::ofstream log;

extern CardReaderManager g_ReaderManager;


ks_card_info_t g_cardinfo;

static int s_is_load = 0;


extern std::string g_card_read_right;
extern std::string g_card_write_right;

#if 0

static int do_load_device_layer(HMODULE m,ks_device_op_t* dev)
{
	LOAD_DLLFUNC(m,register_device_op);
	if(register_device_op(dev)==0)
		return 0;
	TRACE2_LOG(("注册硬件层失败"));
	return -1;
}
#if USE_CASE_TYPE_CLASS==0
static int do_load_cardtype_layer(HMODULE m,ks_cardtype_op_t* cardtype)
#else
static int do_load_cardtype_layer(HMODULE m,ks_cardtype_base* cardtype)
#endif
{
	LOAD_DLLFUNC(m,register_cardtype_op);
	if(register_cardtype_op(g_CardType)==0)
	{
		return 0;
	}
	TRACE2_LOG(("注册卡类型层失败"));
	return -1;
}
static int do_load_enc_layer(HMODULE m)
{
	LOAD_DLLFUNC(m,register_enc_op);
	if(register_enc_op(&g_enc_op)==0)
		return 0;
	TRACE2_LOG(("注册算法层失败"));
	return -1;
}
#endif 

static int do_load_license(const char *path,const std::string &pubkey,const std::string &lcs)
{
	int ret;
	char syspath[2048+1];
	char module_path[1024];
	if( !GetSystemDirectory( syspath ,sizeof(syspath) -1 ) )
	{
		ks_setlasterr("获取系统路径失败",-1);
		return -1;
	}
	ret = g_license.load_public_key_file(pubkey.c_str());
	if(ret)
	{
		sprintf(module_path,"%s\\pub.key",syspath);
		ret = g_license.load_public_key_file(module_path);
		if(ret)
		{
			ks_setlasterr("加载公钥失败，请检查文件是否存在[pub.key]");
			return ret;
		}
	}
	ret = g_license.load_license_file(lcs.c_str());
	if(ret)
	{
		sprintf(module_path,"%s\\license.lcs",syspath);
		ret = g_license.load_license_file(module_path);
		if(ret)
		{
			ks_setlasterr("加载公钥失败，请检查文件是否存在[license.lcs]");
			return ret;
		}
	}
	
	return 0;
}
static int do_check_interface()
{
	char current[18]="";
	char expired[20]="";
	char cardright[2048];
	if(g_license.get_public_param("kscardlib.expired",expired,sizeof(expired)-1))
	{
		ks_setlasterr("授权已过期");
		return -1;
	}
	
	get_current_datetime(current);
	if(strncmp(current,expired,8)>0)
	{
		ks_setlasterr("授权已过期");
		return -1;
	}

	memset(cardright,0,sizeof cardright);
	if(g_license.get_public_param("kscardlib.cardreadright",cardright,sizeof(cardright)-1))
	{
		ks_setlasterr("未配置权限");
		return -1;
	}
	g_card_read_right = cardright;

	memset(cardright,0,sizeof cardright);
	if(g_license.get_public_param("kscardlib.cardwriteright",cardright,sizeof(cardright)-1))
	{
		ks_setlasterr("未配置权限");
		return -1;
	}
	g_card_write_right = cardright;
	return 0;
}
int load_interface_layer(const char *path)
{
	DCLR_LOGMSG("load_interface_layer");
	char module_path[1024];
	char param_value[2048+1];
	int param_len = 0;
	std::string sPortNo1,sPortNo2,sLibReader1,sLibReader2,sLibEnc,sLibCardType,sPubKey,sLicense;
	if(s_is_load == 1)
	{
		TRACE_LOG("底层已经加载，返回");
		return 0;
	}

	TRACE_LOG("读取配置");
	//free_interface_layer();
	sprintf(module_path,"%s\\kscard.ini",path);
	CCIniFile ini(module_path);

	sprintf(module_path,"%s\\pub.key",path);
	sPubKey = ini.ReadString("INTERFACE","PUBKEY",module_path);
	if(sPubKey.empty())
	{
		sPubKey = module_path;
	}
	sprintf(module_path,"%s\\license.lcs",path);
	sLicense = ini.ReadString("INTERFACE","LICENSE",module_path);
	if(sLicense.empty())
	{
		sLicense = module_path;
	}
	TRACE2_LOG(("读取license[%s]",sLicense.c_str()));
	if(do_load_license(path,sPubKey,sLicense))
	{
		ks_setlasterr("加载license错误");
		return -1;
	}
	if(do_check_interface())
	{
		ks_setlasterr("检查license错误");
		return -1;
	}
	sPortNo1=ini.ReadString("INTERFACE","PORTNO1",0);
	sPortNo2=ini.ReadString("INTERFACE","PORTNO2",0);
	
	TRACE_LOG("加载卡类型库");
	if(CardTypeManager::instance()->loadCardTypeDLL(&g_license,path)!=0)
	{
		memset(param_value,0,sizeof param_value);
		CardTypeManager::instance()->getErrorMsg(param_value,"加载DLL失败");
		TRACE_LOG(param_value);
		ks_setlasterr(param_value);
		return -1;
	}
	TRACE_LOG("加载读卡器库");
	if(g_ReaderManager.loadReaderDLL(&g_license,path)!=0)
	{
		memset(param_value,0,sizeof param_value);
		g_ReaderManager.getErrorMsg(param_value);
		TRACE_LOG(param_value);
		ks_setlasterr(param_value);
		return -1;
	}
	TRACE_LOG("初始化卡库");
	if(g_ReaderManager.initAllCardType(&g_license,CardTypeManager::instance())!=0)
	{
		memset(param_value,0,sizeof param_value);
		CardTypeManager::instance()->getErrorMsg(param_value);
		TRACE_LOG(param_value);
		ks_setlasterr(param_value);
		return -1;
	}
	g_ReaderManager.setReaderPortByNo(1,atoi(sPortNo1.c_str()),115200);
	if(g_ReaderManager.getReaderCount() == 2)
	{
		g_ReaderManager.setReaderPortByNo(2,atoi(sPortNo2.c_str()),115200);
	}
	TRACE2_LOG(("加载底层成功"));
	param_len = sizeof(param_value)-1;
	g_license.get_public_param(ks_cardlib_license::LCNS_CUST_ID,param_value,param_len);
	TRACEMSG_LOG("CUST["<<param_value<<"]");
	g_license.get_public_param(ks_cardlib_license::LCNS_EXPIRED_DATE,param_value,param_len);
	TRACEMSG_LOG("EXPIREDATE["<<param_value<<"]");
	s_is_load = 1;
	return 0;

}

int free_interface_layer()
{
	CardTypeManager::instance()->freeAll();
	g_ReaderManager.freeAll();
	s_is_load = 0;
	return 0;
}