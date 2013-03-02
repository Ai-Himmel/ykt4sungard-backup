// TSmartMonitor.cpp: implementation of the TSmartMonitor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartMonitor.h"
#include "TSmartServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TSmartMonitor::TSmartMonitor()
{
	m_pServer = NULL ;
}

TSmartMonitor::~TSmartMonitor()
{

}

void TSmartMonitor::Initialized(TSmartServer *pServer)
{
	m_pServer = pServer ;
}

void TSmartMonitor::Run()
{
	while( !IsShutdown() )
	{
		m_pServer->Monitor();
		Sleep(300);
	}
}
