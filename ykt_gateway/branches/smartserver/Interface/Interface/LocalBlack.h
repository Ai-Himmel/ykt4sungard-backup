// LocalBlack.h: interface for the CLocalBlack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCALBLACK_H__C65F7549_49DC_40D4_9DCF_5AC04330E04C__INCLUDED_)
#define AFX_LOCALBLACK_H__C65F7549_49DC_40D4_9DCF_5AC04330E04C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLocalBlack  
{
	struct Head
	{
		int   nRecCount;
		char  sLastVer[24];
	};

protected:
	int		m_nType;
	FILE*	m_fp;

public:
	static CLock  Lock;

public:
	CLocalBlack();
	virtual ~CLocalBlack();

	bool Open(int nType);
	void Close();
	bool Write(TSBlackCard *pCard);
};

#endif // !defined(AFX_LOCALBLACK_H__C65F7549_49DC_40D4_9DCF_5AC04330E04C__INCLUDED_)
