// yktsubsystemDoc.h : interface of the CYktsubsystemDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_YKTSUBSYSTEMDOC_H__C2D541C9_57A2_4D50_8198_EE2ABA5BD7A5__INCLUDED_)
#define AFX_YKTSUBSYSTEMDOC_H__C2D541C9_57A2_4D50_8198_EE2ABA5BD7A5__INCLUDED_
/** 
 * 模块名						外接子系统
 * 文件名						yktsubsystemDoc.h
 * 文件实现功能					Document 类，保存系统进行数据
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: yktsubsystemDoc.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "PluginManage.h"
#include "ListenSocket.h"
#include "../include/def.h"
#include "subsystem.h"
#include <string>
#include <vector>

class CRequestSocket;
/** 
 * @brief Document类
 */
class CYktsubsystemDoc : public CDocument
{
private:
	//HINSTANCE m_hModule;
	/** 
	 * @brief 互斥变量
	 */
	CRITICAL_SECTION m_mutex;
	/** 
	 * @brief 系统侦听Socket
	 */
	CListenSocket * m_listenSock;
	/** 
	 * @brief 保存当前系统配置
	 */
	void SaveServerConfig();
	/** 
	 * @brief 从配置文件加载系统配置
	 */
	void LoadServerConfig();
	/** 
	 * @brief 系统侦听时间
	 */
	CTime m_timeStarted;
	/** 
	 * @brief 处理网络请求的Socket数量
	 */
	int m_runRequest;
	/** 
	 * @brief 系统允许的IP列表
	 */
	std::vector<long> m_allowIPList;
	/** 
	 * @brief 当前正在运行的Socket列表
	 */
	std::vector<CRequestSocket*>m_runningSocket;
protected: // create from serialization only
	DECLARE_DYNCREATE(CYktsubsystemDoc)
	/** 
	 * @brief 构造函数
	 */
	CYktsubsystemDoc();

	/** 
	 * @brief - 当前系统插件类
	 */
	CPluginManage m_plugin_manage;
	/** 
	 * @brief - 当前系统服务配置
	 */
	ksf_server_conf m_svr_conf;

	/** 
	 * @brief 读取允许的IP地址列表
	 */
	void LoadAllowIPList();
	/** 
	 * @brief 判断指定的IP是否在允许范围
	 * 
	 * @param sockin - IP 地址
	 * 
	 * @return - 允许返回 True, 不允许返回 FAlse
	 */
	BOOL IsAllowIP(in_addr * sockin);
// Attributes
public:
	/** 
	 * @brief 获取当前系统插件配置类
	 * 
	 * @return - 返回插件配置类的句柄
	 */
	inline CPluginManage * GetPluginModule()
	{
		return &m_plugin_manage;
	}
	/** 
	 * @brief 获取当前系统IP，MAC，Port信息
	 * 
	 * @return 
	 */
	inline ksf_server_conf * GetServerConfig()
	{
		return &m_svr_conf;
	}
	/** 
	 * @brief 关闭侦听
	 * 
	 * @return 成功关闭侦听返回 True,失败返回 False
	 */
	BOOL StopListening();
	/** 
	 * @brief 开始侦听
	 * 
	 * @return 成功开始侦听返回 True，失败返回 False
	 */
	BOOL StartListening();
	/** 
	 * @brief 当前侦听状态
	 * 
	 * @return - 正在侦听返回 True,否则返回 False
	 */
	BOOL IsListening();
	/** 
	 * @brief 记录当前处理业务的Socket，该方法为互斥的
	 * 
	 * @param sock - Socket 指针
	 * 
	 * @return - 返回所有的业务Socket数量
	 */
	inline int IncRunningRequest(CRequestSocket* sock)
	{
		EnterCriticalSection(&m_mutex);
		m_runningSocket.push_back(sock);
		++m_runRequest;
		LeaveCriticalSection(&m_mutex);
		return m_runRequest;
	}
	/** 
	 * @brief 删除指定的Socket，该方法为互斥的
	 * 
	 * @param sock - Socket 指针
	 * 
	 * @return - 返回删除后系统所有业务Socket数量
	 */
	int DecRunningRequest(CRequestSocket* sock);
	
	/** 
	 * @brief 获取当前所有处理业务的Socket数量，该方法为互斥的
	 * 
	 * @return - 数量
	 */
	inline int GetRunningRequest()
	{
		EnterCriticalSection(&m_mutex);
		return m_runRequest;
		LeaveCriticalSection(&m_mutex);
	}
	/** 
	 * @brief 释放所有超时的，并且接收数据完成，正在处理业务的Socket
	 * 
	 * @param timeout - 超时时间，如果为 -1 删除所有满足条件的Socket
	 * 
	 * @return - 返回删除的Socket数量
	 */
	int ReleaseTimeoutSocket(long timeout);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYktsubsystemDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CYktsubsystemDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CYktsubsystemDoc)
	afx_msg void OnServerCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YKTSUBSYSTEMDOC_H__C2D541C9_57A2_4D50_8198_EE2ABA5BD7A5__INCLUDED_)
