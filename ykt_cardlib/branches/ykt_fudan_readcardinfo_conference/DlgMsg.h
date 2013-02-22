#pragma once


// CDlgMsg 对话框

class CDlgMsg : public CDialog
{
	DECLARE_DYNAMIC(CDlgMsg)

public:
	CDlgMsg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMsg();

// 对话框数据
	enum { IDD = IDD_DIALOG_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
protected:
	virtual void PostNcDestroy();
};
