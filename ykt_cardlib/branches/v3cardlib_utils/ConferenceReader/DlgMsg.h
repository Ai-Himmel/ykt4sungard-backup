#pragma once


// CDlgMsg �Ի���

class CDlgMsg : public CDialog
{
	DECLARE_DYNAMIC(CDlgMsg)

public:
	CDlgMsg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMsg();

// �Ի�������
	enum { IDD = IDD_DIALOG_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
protected:
	virtual void PostNcDestroy();
};
