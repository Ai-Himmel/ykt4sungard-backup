// yktsubsystemDoc.h : interface of the CYktsubsystemDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_YKTSUBSYSTEMDOC_H__C2D541C9_57A2_4D50_8198_EE2ABA5BD7A5__INCLUDED_)
#define AFX_YKTSUBSYSTEMDOC_H__C2D541C9_57A2_4D50_8198_EE2ABA5BD7A5__INCLUDED_
/** 
 * ģ����						�����ϵͳ
 * �ļ���						yktsubsystemDoc.h
 * �ļ�ʵ�ֹ���					Document �࣬����ϵͳ��������
 * ����							����
 * �汾							V0.1
 * ����							2005-07-02
 * ��ע
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
 * @brief Document��
 */
class CYktsubsystemDoc : public CDocument
{
private:
	//HINSTANCE m_hModule;
	/** 
	 * @brief �������
	 */
	CRITICAL_SECTION m_mutex;
	/** 
	 * @brief ϵͳ����Socket
	 */
	CListenSocket * m_listenSock;
	/** 
	 * @brief ���浱ǰϵͳ����
	 */
	void SaveServerConfig();
	/** 
	 * @brief �������ļ�����ϵͳ����
	 */
	void LoadServerConfig();
	/** 
	 * @brief ϵͳ����ʱ��
	 */
	CTime m_timeStarted;
	/** 
	 * @brief �������������Socket����
	 */
	int m_runRequest;
	/** 
	 * @brief ϵͳ�����IP�б�
	 */
	std::vector<long> m_allowIPList;
	/** 
	 * @brief ��ǰ�������е�Socket�б�
	 */
	std::vector<CRequestSocket*>m_runningSocket;
protected: // create from serialization only
	DECLARE_DYNCREATE(CYktsubsystemDoc)
	/** 
	 * @brief ���캯��
	 */
	CYktsubsystemDoc();

	/** 
	 * @brief - ��ǰϵͳ�����
	 */
	CPluginManage m_plugin_manage;
	/** 
	 * @brief - ��ǰϵͳ��������
	 */
	ksf_server_conf m_svr_conf;

	/** 
	 * @brief ��ȡ�����IP��ַ�б�
	 */
	void LoadAllowIPList();
	/** 
	 * @brief �ж�ָ����IP�Ƿ�������Χ
	 * 
	 * @param sockin - IP ��ַ
	 * 
	 * @return - ������ True, �������� FAlse
	 */
	BOOL IsAllowIP(in_addr * sockin);
// Attributes
public:
	/** 
	 * @brief ��ȡ��ǰϵͳ���������
	 * 
	 * @return - ���ز��������ľ��
	 */
	inline CPluginManage * GetPluginModule()
	{
		return &m_plugin_manage;
	}
	/** 
	 * @brief ��ȡ��ǰϵͳIP��MAC��Port��Ϣ
	 * 
	 * @return 
	 */
	inline ksf_server_conf * GetServerConfig()
	{
		return &m_svr_conf;
	}
	/** 
	 * @brief �ر�����
	 * 
	 * @return �ɹ��ر��������� True,ʧ�ܷ��� False
	 */
	BOOL StopListening();
	/** 
	 * @brief ��ʼ����
	 * 
	 * @return �ɹ���ʼ�������� True��ʧ�ܷ��� False
	 */
	BOOL StartListening();
	/** 
	 * @brief ��ǰ����״̬
	 * 
	 * @return - ������������ True,���򷵻� False
	 */
	BOOL IsListening();
	/** 
	 * @brief ��¼��ǰ����ҵ���Socket���÷���Ϊ�����
	 * 
	 * @param sock - Socket ָ��
	 * 
	 * @return - �������е�ҵ��Socket����
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
	 * @brief ɾ��ָ����Socket���÷���Ϊ�����
	 * 
	 * @param sock - Socket ָ��
	 * 
	 * @return - ����ɾ����ϵͳ����ҵ��Socket����
	 */
	int DecRunningRequest(CRequestSocket* sock);
	
	/** 
	 * @brief ��ȡ��ǰ���д���ҵ���Socket�������÷���Ϊ�����
	 * 
	 * @return - ����
	 */
	inline int GetRunningRequest()
	{
		EnterCriticalSection(&m_mutex);
		return m_runRequest;
		LeaveCriticalSection(&m_mutex);
	}
	/** 
	 * @brief �ͷ����г�ʱ�ģ����ҽ���������ɣ����ڴ���ҵ���Socket
	 * 
	 * @param timeout - ��ʱʱ�䣬���Ϊ -1 ɾ����������������Socket
	 * 
	 * @return - ����ɾ����Socket����
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
