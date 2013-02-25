// PluginManage.h: interface for the CPluginManage class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_PLUGINMANAGE_H__7F445CF3_4E67_476B_9F00_523D97DFBF0F__INCLUDED_)
#define AFX_PLUGINMANAGE_H__7F445CF3_4E67_476B_9F00_523D97DFBF0F__INCLUDED_
/** 
 * 模块名						外接子系统
 * 文件名						PluginManage.h
 * 文件实现功能					子系统插件管理类
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: PluginManage.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../include/def.h"


/** 
 * @brief 插件管理类
 */
class CPluginManage  
{
private:
	/** 
	 * @brief 插件路径
	 */
	CString m_plugin_path;
	/** 
	 * @brief 插件结构
	 */
	ksf_plugin_module m_module;
	/** 
	 * @brief 打开插件的DLL句柄
	 */
	HINSTANCE m_hModule;
	/** 
	 * @brief 系统插件是否已经加载
	 */
	BOOL m_is_module_load;
	/** 
	 * @brief 保存当前插件路径到系统配置文件中
	 */
	void SaveModuleConfig();
public:
	/** 
	 * @brief 构造函数
	 */
	CPluginManage();
	/** 
	 * @brief 析构函数
	 */
	virtual ~CPluginManage();

	/** 
	 * @brief 从指定的路径加载插件
	 * 
	 * @param plugin_path - 插件路径
	 * @param reg - 是否调用插件入口函数。
	 * 
	 * @return - 成功返回 0 ，失败返回-1
	 */
	int LoadPluginFromFile(const char * plugin_path,BOOL reg = false);
	/** 
	 * @brief 调用插件入口函数注册插件
	 * 
	 * @return - 成功返回0，失败返回-1
	 */
	int RegistePluginModule();
	/** 
	 * @brief 调用插件入口函数释放插件
	 * 
	 * @return - 成功返回0，失败返回-1
	 */
	int UnRegistePluginModule();
	/** 
	 * @brief 从系统配置文件中加载插件
	 * 
	 * @param bInit - 是否加载并注册插件
	 */
	void LoadModuleConfig(BOOL bInit = FALSE);

	/** 
	 * @brief 取得当前插件结构
	 * 
	 * @return - 当前结构指针
	 */
	inline const ksf_plugin_module * GetPluginModule() const
	{
		return &m_module;
	}
	/** 
	 * @brief 插件是否已经加载
	 * 
	 * @return - 已加载返回 True，否则返回 False
	 */
	inline BOOL IsModuleLoaded()
	{
		return m_is_module_load;
	}
};

#endif // !defined(AFX_PLUGINMANAGE_H__7F445CF3_4E67_476B_9F00_523D97DFBF0F__INCLUDED_)
