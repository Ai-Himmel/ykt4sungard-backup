// readcard1.cpp : implementation file
//

#include "stdafx.h"
#include "RfTest.h"
#include "readcard1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Creadcard

IMPLEMENT_DYNCREATE(Creadcard, CWinThread)

Creadcard::Creadcard()
{
}

Creadcard::~Creadcard()
{
}

BOOL Creadcard::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int Creadcard::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(Creadcard, CWinThread)
	//{{AFX_MSG_MAP(Creadcard)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Creadcard message handlers
