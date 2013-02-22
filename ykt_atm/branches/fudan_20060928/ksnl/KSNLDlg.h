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
	// ��󻯴���
	void MaxWindow(void);
	afx_msg void OnPaint();
	void OnFormKeyDown(UINT nChar, UINT nFlags);
private:
	// �������м��ع��ܲ���
	int LoadFunctionConfig(void);
	CKSConfig m_config;
	// ���ƹ��ܰ���
	void DrawFuncBtn(CDC* pDC);                         // ����
	// ���ƹ��ܰ�ť
	void DrawFuncBtn(CDC* pDC, CKSWorkflow* workflow);  // ����
	// ��ȡ��ǰ�� ������
	CKSWorkflow* GetCurrentWorkflow(void);
	// 
	void Reset();
	void DisplayMessages(CDC * pDC,const CRect & client);
	CKSWorkflow* m_currentWorkflow;

	// ���ƽ���CKSNLDlg���ص�����
	bool m_dlg_msg_overlapped;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int InputQuery(const CString & prompt, const CString & defaultValue, CString & value,int timeout);
	int InputPassword(const CString & prompt, CString & value,int timeout);
	int Confirm(const CString& prompt,int timeout);
	int Confirm(int timeout);
	// ��ʾ��Ϣ
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
	//! ��ʾ�б���
	/*!
	 * \param timeout ��ʱʱ��
	 * \return ���� IDOK,IDCENCEL
	 */
	int ShowListInfo(int timeout);
	//! ������е���,�������е�����
	void ClearAllColumns();
	//! ����һ��
	/*!
	 * \param colName ����
	 */
	void AddListColumns(const CString & colName,int width = -1);
	//! ����һ����¼
	/*!
	 * \param pText ������
	 * \param ... �ɱ����,��˳��ָ�����е�ֵ
	 * \return �����к�,ʧ�ܷ��� -1
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
