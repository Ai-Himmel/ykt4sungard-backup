// TSmartProtocol.cpp: implementation of the TSmartProtocol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartProtocol.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TSmartProtocol::TSmartProtocol()
{
	m_hModule = NULL ;
}

TSmartProtocol::~TSmartProtocol()
{

}

void TSmartProtocol::Initialized(LPCTSTR pszFileName)
{
	m_hModule = LoadLibrary(pszFileName);
	if( m_hModule == NULL )
		throw TException("����װ��Э�������̬��!", GetLastError());

	GetSmartProtocolRule = (lpfnGetSmartProtocolRule)GetProcAddress(m_hModule, "GetSmartProtocolRule");
	VerifyBufferValid = (lpfnVerifyBufferValid)GetProcAddress(m_hModule, "VerifyBufferValid");

	if( !GetSmartProtocolRule )
	{
		throw TException("�Ƿ���Э�������̬��!");
	}

	ZeroMemory(&SmartProtocol, sizeof(SmartProtocol));
	if( GetSmartProtocolRule(&SmartProtocol) != RET_OK )
	{
		throw TException("Э�������̬���ʼ��ʧ��!");
	}
}

void TSmartProtocol::Destory()
{
	if( m_hModule != NULL )
	{
 		FreeLibrary(m_hModule);
		m_hModule = NULL ;
	}
}

