// PluginManage.cpp: implementation of the CPluginManage class.
/** 
 * 模块名						外接子系统
 * 文件名						PluginManage.cpp
 * 文件实现功能					子系统插件管理类
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: PluginManage.cpp 15 2005-08-22 02:39:12Z cash $
 */

//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "yktsubsystem.h"
#include "PluginManage.h"
#include "sysutil.h"
#include "KLogfile.h"
#include "LogFactory.h"
#include <assert.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// define module function
def(int,registe_module,(ksf_plugin_module *module));
def(int,unregiste_module,(ksf_plugin_module *module));
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPluginManage::CPluginManage()
:m_is_module_load(FALSE)
{

}

CPluginManage::~CPluginManage()
{

}

int CPluginManage::LoadPluginFromFile(const char * plugin_path,BOOL reg)
{
	assert(plugin_path != NULL);
	KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
	if( !ksf_file_exists(plugin_path))
	{
		AfxMessageBox("插件不存在！");
		return -1;
	}
	log->WriteLog("加载插件[%s]",plugin_path);
	m_hModule = LoadLibrary(plugin_path);
	if( !m_hModule )
	{
		CString msg;
		msg.Format("不能加载 %s ",plugin_path);
		AfxMessageBox(msg);
		return -1;
	}
	bool err_code = false;

	load(m_hModule,registe_module);
	load(m_hModule,unregiste_module);

	if( err_code )
	{
		AfxMessageBox("不能加载入口函数");
		if( m_hModule )
			FreeLibrary(m_hModule);
		m_hModule = NULL;
		return -1;
	}
	log->WriteLog("加载插件成功!!",plugin_path);
	m_plugin_path.Format("%s",plugin_path);
	if( reg )
		return RegistePluginModule();
	return 1;
}

int CPluginManage::RegistePluginModule()
{
	memset(&m_module,0,sizeof(ksf_plugin_module));
	KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
	int ret = registe_module(&m_module);
	if( ret == 0)
	{
		log->WriteLog("加载插件[%s]日期[%s]",
			m_module.module_name,m_module.date);
		if(m_module.module_init)
		{
			ret = -1;
			try
			{
				if((ret=m_module.module_init()) != 0)
				{
					log->WriteLog("初始化插件[%s]失败,返回值[%d]",
						m_module.module_name,ret);
					return ret;
				}
				log->WriteLog("初始化插件[%s]成功",m_module.module_name);
			}
			catch(...)
			{
				log->WriteLog("初始化插件出现异常");
				AfxMessageBox("初始化插件出现异常");
				return ret;
			}
		}
		m_is_module_load = TRUE;
		strcpy(m_module.module_path,m_plugin_path);
		SaveModuleConfig();
	}
	return ret;
}

int CPluginManage::UnRegistePluginModule()
{
	int ret = -1;
	if( m_is_module_load )
	{
		if( m_module.module_release )
		{
			try
			{
				if((ret = m_module.module_release()) != 0)
				{
					return ret;
				}
			}
			catch(...)
			{
				// catch all exception but do nothing
			}
		
		}
		ret = unregiste_module(&m_module);
		FreeLibrary(m_hModule);
		memset(&m_module,0,sizeof(ksf_plugin_module));
		m_is_module_load = FALSE;
		return ret;
	}
	return 0;
}

void CPluginManage::SaveModuleConfig()
{
	AfxGetApp()->WriteProfileString(INI_MODULE_SECT,INI_MODULE_PATH,m_plugin_path);
}

void CPluginManage::LoadModuleConfig(BOOL bInit)
{
	m_plugin_path = AfxGetApp()->GetProfileString(INI_MODULE_SECT,INI_MODULE_PATH,"");
	if( !m_plugin_path.IsEmpty() && bInit)
	{
		LoadPluginFromFile(m_plugin_path,TRUE);
	}
}
