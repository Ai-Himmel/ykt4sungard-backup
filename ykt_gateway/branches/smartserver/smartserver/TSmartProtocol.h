// TSmartProtocol.h: interface for the TSmartProtocol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTPROTOCOL_H__A0EDB27C_30EA_4720_AFC9_1914FE69B8F4__INCLUDED_)
#define AFX_TSMARTPROTOCOL_H__A0EDB27C_30EA_4720_AFC9_1914FE69B8F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//************************************************************************************
//*����: TSmartProtocol  
//*����: Ӳ����Э��˵����
//************************************************************************************
class TSmartProtocol  
{
protected:
	HMODULE  m_hModule;

public:
	TSmartProtocol();
	virtual ~TSmartProtocol();

	void Initialized(LPCTSTR pszFileName);
	void Destory();
};

#endif // !defined(AFX_TSMARTPROTOCOL_H__A0EDB27C_30EA_4720_AFC9_1914FE69B8F4__INCLUDED_)
