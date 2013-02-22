// Algorithm.h: interface for the Algorithm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGORITHM_H__8D0C3571_54CE_4CF5_AA11_4CF35BEC659C__INCLUDED_)
#define AFX_ALGORITHM_H__8D0C3571_54CE_4CF5_AA11_4CF35BEC659C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Algorithm  
{
public:
	int bcd2decA(unsigned char *sBcdStr, int bcd_len, char *sDecStr);
	void hex2dec(char *sHex,unsigned char * sDec,int dec_len);
	void dec2hex(unsigned char *sDec, int dec_len, char *sHex);
	int bcd2dec(unsigned char *sBcdStr, int bcd_len, unsigned char *sDecStr);
	int dec2bcd(unsigned char *sDecStr, unsigned char *sBcdStr, int bcd_len);
	Algorithm();
	virtual ~Algorithm();

};

#endif // !defined(AFX_ALGORITHM_H__8D0C3571_54CE_4CF5_AA11_4CF35BEC659C__INCLUDED_)
