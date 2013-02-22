// Algorithm.cpp: implementation of the Algorithm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Algorithm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Algorithm::Algorithm()
{

}

Algorithm::~Algorithm()
{

}

int Algorithm::dec2bcd(unsigned char *sDecStr, unsigned char *sBcdStr, int bcd_len)
{
	int count;
	unsigned char lch, hch;

	for (count = 0; count < bcd_len; count++)
	{
		lch = sDecStr[2 * count] - '0';
		hch = sDecStr[2 * count + 1] - '0';
		lch = lch << 4;
		hch = hch & 0x0F;
		lch = lch & 0xF0;
		sBcdStr[count] = hch | lch;
	}
	return 0;
}

int Algorithm::bcd2dec(unsigned char *sBcdStr, int bcd_len, unsigned char *sDecStr)
{
	int count;
	unsigned char lch, hch;

	for (count = 0; count < bcd_len; count++)
	{
		hch = (sBcdStr[count] & 0x0F);
		lch = (sBcdStr[count] & 0xF0);
		lch = lch >> 4;
		sDecStr[2 * count] = lch + '0';
		sDecStr[2 * count + 1] = hch + '0';
	}
	return 0;
}

void Algorithm::dec2hex(unsigned char *sDec, int dec_len, char *sHex)
{
	int i = 0;
	int k = 0;
	for(i = 0; i < dec_len; i++)
	{
		k = sDec[i];
		sprintf(&sHex[2 * i], "%02X", k);
	}
}

void Algorithm::hex2dec(char *sHex, unsigned char *sDec, int dec_len)
{
	int i = 0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp, 0, sizeof(sHexTmp));
	for(i=0; i < dec_len; i++)
	{
		memcpy(sHexTmp, &sHex[2 * i], 2);
		ul = strtoul(sHexTmp, NULL, 16);
		sDec[i] = (unsigned char)ul;
	}
}

int Algorithm::bcd2decA(unsigned char *sBcdStr, int bcd_len, char *sDecStr)
{
	int i;
	unsigned char lch, hch;

	for(i = 0; i < bcd_len; i++)
	{
		hch = (sBcdStr[i] & 0x0F);
		lch = (sBcdStr[i] & 0xF0);
		lch = lch >> 4;
		sDecStr[2 * i] = lch + '0';
		sDecStr[2 * i + 1] = hch + '0';
	}
	return 0;
}
