// lisencemanagerDlg.h : 头文件
//
#include <string>
#include <map>
#include "kslicense.h"
#include "afxcmn.h"
#include "ListCtrlEdit.h"
#include "ListCtrlComboBox.h"

#pragma once


// ClisencemanagerDlg 对话框
class ClisencemanagerDlg : public CDialog
{
// 构造
public:
	ClisencemanagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LISENCEMANAGER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	ks_cardlib_license m_license;
	CString m_private_keyfile;
	CString m_public_keyfile;
	CString m_lisence_file;
	void loadconfig();
	void loadpathconfig(int uID,std::map<std::string,std::string> &values);
	CString selectFile(int uID,LPCTSTR filter = NULL);
	void saveconfig();
	void savepathconfig(int uID,std::map<std::string,std::string> &values);
	void showloginfo(const CString &info);
	void getitemtext(int uID,char *text);
	void initial_list();
	void save_list_param();
	void load_param_2_list();

	int m_select_item_idx;

// 实现
protected:
	HICON m_hIcon;
	CStatusBar  m_wndStatusBar;
	CMenu m_listMenu;

	CListCtrlEdit m_listEdit;
	CListCtrlComboBox m_listComboBox; 

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSelprivkey();
	afx_msg void OnBnClickedBtnSelpubkey();
	afx_msg void OnBnClickedBtnLisence();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnLoadprivkey();
	afx_msg void OnBnClickedBtnLoadpubkey();
	afx_msg void OnBnClickedBtnLoadlisence();
	afx_msg void OnBnClickedBtnGenkey();
	afx_msg void OnBnClickedBtnSavelicense();
	CListCtrl m_list;
	afx_msg void OnNMRclickLstParams(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuAdd();
	afx_msg void OnMenuDel();
	afx_msg void OnNMClickLstParams(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkLstParams(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedLstParams(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnErrmsg();
};
