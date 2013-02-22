#if !defined(AFX_MYCLISTCTRL_H__6726D3BA_7244_4175_8AD4_084F83282C9E__INCLUDED_)
#define AFX_MYCLISTCTRL_H__6726D3BA_7244_4175_8AD4_084F83282C9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyCListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyCListCtrl window

class CMyCListCtrl : public CListCtrl
{
// Construction
public:
	CMyCListCtrl();

// Attributes
public:
	CImageList m_imagelist;
	CFont	m_font;
// Operations
public:
	BOOL SMT_SelectRow( int nIndex);
	BOOL SMT_CancelSelectRow( int nIndex);
	int  SMT_GetColNum( );
	void SMT_DeleteAllCol( );
	void SMT_SetListFormat();
	int  SMT_GetSelectRowIndex( NMHDR* pNMHDR);
	int  SMT_GetSelectColIndex(NMHDR* pNMHDR );
	CString SMT_GetSelectValue( NMHDR* pNMHDR, CString sValue);
	void MyInit();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyCListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyCListCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCLISTCTRL_H__6726D3BA_7244_4175_8AD4_084F83282C9E__INCLUDED_)
