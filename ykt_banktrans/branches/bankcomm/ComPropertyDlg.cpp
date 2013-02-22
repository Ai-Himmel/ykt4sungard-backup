// ComPropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bankComm.h"
#include "ComPropertyDlg.h"
#include ".\compropertydlg.h"


// CComPropertyDlg dialog

IMPLEMENT_DYNAMIC(CComPropertyDlg, CDialog)
CComPropertyDlg::CComPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComPropertyDlg::IDD, pParent)
{
	this->m_pDcb = NULL;
}

CComPropertyDlg::~CComPropertyDlg()
{
}

void CComPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CComPropertyDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CComPropertyDlg message handlers
BOOL CComPropertyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//串口号
	CComboBox*pComb=NULL; 
	
	CString c;
	int nIndex;
	//波特率
	pComb=(CComboBox*)this->GetDlgItem(IDC_COMBO1);
	pComb->AddString("1200");
	pComb->AddString("2400");
	pComb->AddString("4800");
	pComb->AddString("7200");
	pComb->AddString("9600");
	pComb->AddString("14400");
	pComb->AddString("19200");
	c.Format("%d",this->m_pDcb->BaudRate);
	nIndex=pComb->FindString(0,c);
	pComb->SetCurSel(nIndex);
	//数据位
	pComb=(CComboBox*)this->GetDlgItem(IDC_COMBO2);
	pComb->AddString("4");
	pComb->AddString("5");
	pComb->AddString("6");
	pComb->AddString("7");
	pComb->AddString("8");
	c.Format("%d",this->m_pDcb->ByteSize);
	nIndex=pComb->FindString(0,c);
	pComb->SetCurSel(nIndex);

	//停止位
	pComb=(CComboBox*)this->GetDlgItem(IDC_COMBO3);
	pComb->AddString("1");
	pComb->AddString("1.5");
	pComb->AddString("2");
	nIndex=this->m_pDcb->StopBits;
	pComb->SetCurSel(nIndex);

	//校验
	pComb=(CComboBox*)this->GetDlgItem(IDC_COMBO4);
	pComb->AddString("无校验");
	pComb->AddString("奇校验");
	pComb->AddString("偶校验");

	nIndex=this->m_pDcb->Parity;
	pComb->SetCurSel(nIndex);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常：OCX 属性页应返回 FALSE
}

void CComPropertyDlg::SetDCB(DCB* dcb)
{
	this->m_pDcb = dcb;

}

void CComPropertyDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CComboBox*pComb=NULL; 
	
	/*1.波特率
	*/
	int index=-1,i = 0;
	CString value;

	pComb=(CComboBox*)this->GetDlgItem(IDC_COMBO1);
	index=pComb->GetCurSel();
	if(index<0)
	{
		::AfxMessageBox("波特率不能为空!");
		return;
	}
	pComb->GetLBText(index,value);
	i=atoi(value);
	this->m_pDcb->BaudRate = i;  

	/*2.数据位
	*/
	pComb=(CComboBox*)this->GetDlgItem(IDC_COMBO2);
	index=pComb->GetCurSel();
	if(index<0)
	{
		::AfxMessageBox("数据位不能为空!");
		return;
	}
	pComb->GetLBText(index,value);
	i=atoi(value);
	this->m_pDcb->ByteSize = i;  

	/*3.停止位
	*/
	pComb=(CComboBox*)this->GetDlgItem(IDC_COMBO3);
	index=pComb->GetCurSel();
	if(index<0)
	{
		::AfxMessageBox("停止位不能为空!");
		return;
	}
	this->m_pDcb->StopBits = index;  

	/*4.校验
	*/
	pComb=(CComboBox*)this->GetDlgItem(IDC_COMBO4);
	index=pComb->GetCurSel();
	if(index<0)
	{
		::AfxMessageBox("校验不能为空!");
		return;
	}
	this->m_pDcb->Parity = index; 
	OnOK();
}
