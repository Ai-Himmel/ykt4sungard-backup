// LoadDll.h: interface for the LoadDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADDLL_H__FDBF08FB_D63C_41C6_9105_1CD5D6D4021B__INCLUDED_)
#define AFX_LOADDLL_H__FDBF08FB_D63C_41C6_9105_1CD5D6D4021B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
using namespace std;

class CLoadDll  
{
public:
	int LoadAllInfo();
	void UnLoadKingStarDll();
	int LoadKingStarDll();
	CLoadDll();
	virtual ~CLoadDll();

private:
	std::string m_str_get_dllname;
	HINSTANCE m_h_ks_dll;
};

#endif // !defined(AFX_LOADDLL_H__FDBF08FB_D63C_41C6_9105_1CD5D6D4021B__INCLUDED_)
