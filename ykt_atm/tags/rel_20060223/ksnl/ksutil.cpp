#include "StdAfx.h"
#include "ksutil.h"
#include <assert.h>

void HexToAscii(BYTE * hexValue,int len,char * asciiValue)
{
	int i,j;
	assert(hexValue != NULL);
	assert(asciiValue != NULL);
	for(i = 0,j = 0;i < len;i++)
	{
		j += sprintf(asciiValue+j,"%02X",hexValue[i]);
	}
}