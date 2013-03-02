/*--------------------------------------
entry:	asc
	len	--- the length of asc
return:	0 --- SUCC
	-1 --- FAIL
	bcd
----------------------------------------*/
asctobcd(bcd, asc, len)
char	*bcd, *asc;
int	len;
{
char	*p;
int	i, j;

	p = (char *) malloc( (len+1) * sizeof(char) );

	for(i = 0; i < len; i++) {
		if( (asc[i] >= '0') && (asc[i] <= '9') )
			p[i] = asc[i] - '0';
		else if( (asc[i] >= 'a') && (asc[i] <= 'f') )
			p[i] = asc[i] - 'a' + 10;
		else if( (asc[i] >= 'A') && (asc[i] <= 'F') )
			p[i] = asc[i] - 'A' + 10;

		else { 
			free(p); 
			return(-1);
		}
	}

	j = (len + len%2) / 2;
	if( len%2 ) p[len+1] = 0;

	for (i=0; i<j; i++) {
		bcd[i] = (p[2*i] & 0x0f)<<4;
		bcd[i] |= (p[2*i+1] & 0x0f);
	}

	free(p);
	return(0);
}

/*-------------------------------------------
entry:	bcd
	len	---  the length of asc
return:	asc
---------------------------------------------*/
bcdtoasc(asc, bcd, len)
char	*asc, *bcd;
int	len;
{
int	i, j;

	j = (len + len%2) / 2;
	for(i=0; i<j; i++) {
		asc[2*i] = (bcd[i] >> 4) & 0x0f;
		asc[2*i+1] = bcd[i] & 0x0f; 
	}	
	for(i=0; i<len; i++) {
		if( asc[i] > 0x09)
			asc[i] = 'A' + asc[i] - 0x0a;
		else	asc[i] += '0';
	}
	
	asc[len] = 0;
}
