// RF35OCXPpg.cpp : Implementation of the CRF35OCXPropPage property page class.

#include "stdafx.h"
#include "RF35OCX.h"
#include "RF35OCXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRF35OCXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRF35OCXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CRF35OCXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRF35OCXPropPage, "RF35OCX.RF35OCXPropPage.1",
	0x9d8e77ea, 0xa0df, 0x4d4d, 0x93, 0x5c, 0x17, 0x11, 0x97, 0x22, 0xc5, 0xb)


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXPropPage::CRF35OCXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CRF35OCXPropPage

BOOL CRF35OCXPropPage::CRF35OCXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_RF35OCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXPropPage::CRF35OCXPropPage - Constructor

CRF35OCXPropPage::CRF35OCXPropPage() :
	COlePropertyPage(IDD, IDS_RF35OCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CRF35OCXPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXPropPage::DoDataExchange - Moves data between page and properties

void CRF35OCXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CRF35OCXPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXPropPage message handlers
