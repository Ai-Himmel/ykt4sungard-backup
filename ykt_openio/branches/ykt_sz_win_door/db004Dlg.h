// db004Dlg.h : header file
//

#if !defined(AFX_DB004DLG_H__2F15CCB8_DD94_4409_BAF4_AB773A57B21D__INCLUDED_)
#define AFX_DB004DLG_H__2F15CCB8_DD94_4409_BAF4_AB773A57B21D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDb004Dlg dialog

class CDb004Dlg : public CDialog
{
// Construction
public:
	~CDb004Dlg();
	CDb004Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDb004Dlg)
	enum { IDD = IDD_DB004_DIALOG };

// 	CString	m_strId;
// 	CString	m_strName;
// 	UINT	m_nScore;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDb004Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	BOOL m_bAdd;
	CFile file;
	BOOL oraflag;
	BOOL sqlflag;
	BOOL fileflag;
	_RecordsetPtr m_pRecordset;// ,m_oraRecordset,m_sqlRecordset;
	_ConnectionPtr m_pConnection,m_oraConnection,m_sqlConnection;
	_CommandPtr m_sqlCommand;
	//__int64 Str2Int64(char* str);
	CString GetTime();
	void GetCollect(_RecordsetPtr& m_oraRecordset,CString& CARDNO,CString& CUSTNAME,CString& DEPTNAME,CString& NEW_CARDUPDTIME); 
	CString EMh2d(char *strh);
	BOOL FileExist(CString fileName);
	BOOL Openfile(CFile& file);
	void WriteLogstr(char* s);
	void WriteLogint(int i);
	void WriteLogcstr(CString str);
	void OnTimer(UINT_PTR nIDEvent);
	void EnableInput(BOOL bEnable);
	void AddUser();
	void DelUser(); 
	void RegisterLostCard();
	void ReleaseLostCard();
	void BbCard();
	void FreshList();
	void Opencmd(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* sqltext);
	void Opencmd_ret(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* sqltext,_ParameterPtr& ret_var);
	//void ConnectDb(_RecordsetPtr& m_pRecordset,_ConnectionPtr& m_pConnection);
	//void ConnectDb(_RecordsetPtr& m_pRecordset,_ConnectionPtr& m_pConnection,char* udl);
	//void ConnectDb(_RecordsetPtr& m_rs,_CommandPtr& m_cmd,_ConnectionPtr& m_cnn,char* udl);
	BOOL ConnectDb(_ConnectionPtr& m_cnn,char* udl);
	void Appendcmd(_CommandPtr& m_pCommand,char prm_name[],DataTypeEnum prm_type,ParameterDirectionEnum prm_direction,char prm_value[]);
	//int Executecmd(_CommandPtr& m_pCommand);
	int Executecmd(_CommandPtr& m_pCommand,_ParameterPtr& ret_var);
	void Appendret(_CommandPtr& m_pCommand,_ParameterPtr& mp_var);
	//int wg_NewConsumer(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,int CARDPHYID,char* ConsumerName,char* GroupName);
	int sp_wg_NewConsumer(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID,char* ConsumerName,char* GroupName);
	int sp_wg_DeleteConsumer(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID);
	int sp_wg_EditConsumerNameAndGroupName(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID,char* ConsumerName,char* GroupName);
	int sp_wg_RegisterLostCard(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID,char* NewCARDPHYID);
	int sp_wg_RegisterLostCardWithoutNewCard(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID);
	int sp_wg_ReleaseLostCard(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID);
	bool SearchSqlGroup(char* DEPTNAME);
	void AddSqlGroup(char* f_GroupName);

	// Generated message map functions
	//{{AFX_MSG(CDb004Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
//	afx_msg void OnButtonAdd();
//	afx_msg void OnButtonSave();
//	afx_msg void OnButtonCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButton1();
//	afx_msg void OnBnClickedButton2();
//	afx_msg void OnBnClickedButton3();
//	afx_msg void OnBnClickedButton4();
//	afx_msg void OnBnClickedButton5();
	afx_msg void a(UINT_PTR nIDEvent);
	afx_msg void OnClose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB004DLG_H__2F15CCB8_DD94_4409_BAF4_AB773A57B21D__INCLUDED_)
