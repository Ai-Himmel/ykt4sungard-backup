#include "afxwin.h"
#if !defined(AFX_KSNLDLG_H__1D8AF42E_7DF3_45BA_9962_420CF6313832__INCLUDED_)
#define AFX_KSNLDLG_H__1D8AF42E_7DF3_45BA_9962_420CF6313832__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KSNLDlg.h : header file
//
#include "KSWorkflow.h"
#include "KSConfig.h"
#include "FG_DIB.h"
#include "KSMsgDrawer.h"
/////////////////////////////////////////////////////////////////////////////
// CKSNLDlg dialog

class CKSNLDlg : public CDialog
{
private:
	int ReadCardPhyID();
	int ReadICCardId();
	int m_timeout;
	int m_idletime;
	BOOL m_bShowDlg;
	KSMsgDrawer m_drawer;
	int m_sizeFlag;
// Construction
public:
	CKSNLDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKSNLDlg)
	enum { IDD = IDD_MAINDLG };
	CString	m_CardPhyID;
	CString	m_ICCardID;
	CListCtrl m_InfoListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKSNLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKSNLDlg)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 最大化窗口
	void MaxWindow(void);
	afx_msg void OnPaint();
	void OnFormKeyDown(UINT nChar, UINT nFlags);
private:
	// 从配置中加载功能参数
	int LoadFunctionConfig(void);
	CKSConfig m_config;
	// 绘制功能按键
	void DrawFuncBtn(CDC* pDC);                         // 重载
	// 绘制功能按钮
	void DrawFuncBtn(CDC* pDC, CKSWorkflow* workflow);  // 重载
	// 获取当前的 工作流
	CKSWorkflow* GetCurrentWorkflow(void);
	// 
	void Reset();
	void DisplayMessages(CDC * pDC,const CRect & client);
	CKSWorkflow* m_currentWorkflow;

	// 控制进入CKSNLDlg的重叠按键
	bool m_dlg_msg_overlapped;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int InputQuery(const CString & prompt, const CString & defaultValue, CString & value,int timeout);
	int InputPassword(const CString & prompt, CString & value,int timeout);
	int Confirm(const CString& prompt,int timeout);
	int Confirm(int timeout);
	// 显示信息
	int ShowTipMessage(const char* msg,int timeout = 10);
	inline CKSConfig * GetConfig()
	{
		return &m_config;
	}
	void AddMessageLine(const CString & msg,int lineno = 0,int size_offset = 0)
	{
		m_drawer.AddMessageLine(msg,lineno,size_offset);
	}
	void AddMessageLineEx(const CString & msg, int lineno = 0, int size_offset = 0, int msgDlgflag = 1)
	{
		m_drawer.AddMessageLineEx(msg, lineno, size_offset, msgDlgflag);
	}
	int GetMaxLineNo() const {return m_drawer.GetMaxLineNo();}
	int DisplayMessage(int timeout);
	void ClearMessageLine() { m_drawer.Reset(); }
	void SetTimeOut(int timeout);
	//! 显示列表窗体
	/*!
	 * \param timeout 超时时间
	 * \return 返回 IDOK,IDCENCEL
	 */
	int ShowListInfo(int timeout);
	//! 清除所有的列,包括所有的数据
	void ClearAllColumns();
	//! 增加一列
	/*!
	 * \param colName 列名
	 */
	void AddListColumns(const CString & colName,int width = -1);
	//! 增加一条记录
	/*!
	 * \param pText 列内容
	 * \param ... 可变参数,按顺序指定各列的值
	 * \return 返回行号,失败返回 -1
	 */
	int AddToListInfo(LPCTSTR pText,...);
public:
	void SetLimtText(int sizeFlag);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL DestroyWindow();
	int m_errcode;
	enum AlineText{AT_LEFT, AT_CENTER, AT_RIGHT};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSNLDLG_H__1D8AF42E_7DF3_45BA_9962_420CF6313832__INCLUDED_)
