#include "BasicMath.h"

void round_float(double *f, int bits) 
{
	static const int DECIMAL_BASE = 10;    
	unsigned int n,scale,m;    
	int i;
	scale = 1;
	for (i = 0; i < bits + 1;  i++)
	{
		scale *= DECIMAL_BASE;
	}

	n = (*f) * scale;
	//	n += 5;
	m = n % 10;
	if (m < 5)
		n = n - m;
	else
		n = n - m + 10;    

	*f = ((double)n / scale);
}

int GetRGRetData(char *result, char *key_name, char *value_name)
{
	char *pdest = NULL;
	char *plast = NULL;
	char count = 0;

	if (0 == strncmp(result, RG_SUCC, RG_FLAG_LEN))				// SUCCESSFUL
	{
		return 0;	
	}
	else if (0 == strncmp(result, RG_ACK, RG_FLAG_LEN))
	{
		pdest = strstr(result, key_name);
		pdest += strlen(key_name);
		pdest += strlen(RG_SPLIT2);
		plast = strstr(pdest, RG_SPLIT2);
		count = plast - pdest;
		strncpy(value_name, pdest, count);
	}
	else if (0 == strncmp(result, RG_ERR, RG_FLAG_LEN))
	{
		pdest = result;
		pdest += RG_FLAG_LEN;
		pdest += strlen(RG_SPLIT3);
		strcpy(value_name, pdest);

		return -1;
	}

	return 0;
}