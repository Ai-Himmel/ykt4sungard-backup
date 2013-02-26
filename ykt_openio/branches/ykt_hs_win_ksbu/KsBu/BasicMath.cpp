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