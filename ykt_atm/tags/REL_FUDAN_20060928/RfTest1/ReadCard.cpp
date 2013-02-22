// ReadCard.cpp : implementation file
//

#include "stdafx.h"
#include "RfTest.h"
#include "ReadCard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadCard

IMPLEMENT_DYNCREATE(CReadCard, CWinThread)

CReadCard::CReadCard()
{
}

CReadCard::~CReadCard()
{
}

BOOL CReadCard::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CReadCard::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CReadCard, CWinThread)
	//{{AFX_MSG_MAP(CReadCard)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadCard message handlers

int CReadCard::Run() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinThread::Run();
}

