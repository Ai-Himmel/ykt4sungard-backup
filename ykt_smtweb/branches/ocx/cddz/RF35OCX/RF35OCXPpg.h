#if !defined(AFX_RF35OCXPPG_H__BBE8D977_BD27_4FEC_BE6D_43F7E984FAE0__INCLUDED_)
#define AFX_RF35OCXPPG_H__BBE8D977_BD27_4FEC_BE6D_43F7E984FAE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// RF35OCXPpg.h : Declaration of the CRF35OCXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRF35OCXPropPage : See RF35OCXPpg.cpp.cpp for implementation.

class CRF35OCXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRF35OCXPropPage)
	DECLARE_OLECREATE_EX(CRF35OCXPropPage)

// Constructor
public:
	CRF35OCXPropPage();

// Dialog Data
	//{{AFX_DATA(CRF35OCXPropPage)
	enum { IDD = IDD_PROPPAGE_RF35OCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRF35OCXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RF35OCXPPG_H__BBE8D977_BD27_4FEC_BE6D_43F7E984FAE0__INCLUDED)
