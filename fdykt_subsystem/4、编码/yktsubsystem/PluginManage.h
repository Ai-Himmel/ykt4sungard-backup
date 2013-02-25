// PluginManage.h: interface for the CPluginManage class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_PLUGINMANAGE_H__7F445CF3_4E67_476B_9F00_523D97DFBF0F__INCLUDED_)
#define AFX_PLUGINMANAGE_H__7F445CF3_4E67_476B_9F00_523D97DFBF0F__INCLUDED_
/** 
 * ģ����						�����ϵͳ
 * �ļ���						PluginManage.h
 * �ļ�ʵ�ֹ���					��ϵͳ���������
 * ����							����
 * �汾							V0.1
 * ����							2005-07-02
 * ��ע
 * $Id: PluginManage.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../include/def.h"


/** 
 * @brief ���������
 */
class CPluginManage  
{
private:
	/** 
	 * @brief ���·��
	 */
	CString m_plugin_path;
	/** 
	 * @brief ����ṹ
	 */
	ksf_plugin_module m_module;
	/** 
	 * @brief �򿪲����DLL���
	 */
	HINSTANCE m_hModule;
	/** 
	 * @brief ϵͳ����Ƿ��Ѿ�����
	 */
	BOOL m_is_module_load;
	/** 
	 * @brief ���浱ǰ���·����ϵͳ�����ļ���
	 */
	void SaveModuleConfig();
public:
	/** 
	 * @brief ���캯��
	 */
	CPluginManage();
	/** 
	 * @brief ��������
	 */
	virtual ~CPluginManage();

	/** 
	 * @brief ��ָ����·�����ز��
	 * 
	 * @param plugin_path - ���·��
	 * @param reg - �Ƿ���ò����ں�����
	 * 
	 * @return - �ɹ����� 0 ��ʧ�ܷ���-1
	 */
	int LoadPluginFromFile(const char * plugin_path,BOOL reg = false);
	/** 
	 * @brief ���ò����ں���ע����
	 * 
	 * @return - �ɹ�����0��ʧ�ܷ���-1
	 */
	int RegistePluginModule();
	/** 
	 * @brief ���ò����ں����ͷŲ��
	 * 
	 * @return - �ɹ�����0��ʧ�ܷ���-1
	 */
	int UnRegistePluginModule();
	/** 
	 * @brief ��ϵͳ�����ļ��м��ز��
	 * 
	 * @param bInit - �Ƿ���ز�ע����
	 */
	void LoadModuleConfig(BOOL bInit = FALSE);

	/** 
	 * @brief ȡ�õ�ǰ����ṹ
	 * 
	 * @return - ��ǰ�ṹָ��
	 */
	inline const ksf_plugin_module * GetPluginModule() const
	{
		return &m_module;
	}
	/** 
	 * @brief ����Ƿ��Ѿ�����
	 * 
	 * @return - �Ѽ��ط��� True�����򷵻� False
	 */
	inline BOOL IsModuleLoaded()
	{
		return m_is_module_load;
	}
};

#endif // !defined(AFX_PLUGINMANAGE_H__7F445CF3_4E67_476B_9F00_523D97DFBF0F__INCLUDED_)
