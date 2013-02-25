
void calkey(unsigned char *serialno,int sectno,unsigned char *mkey,unsigned char *keya)
{
	int i,j;
	unsigned char plain[6];
	memcpy(plain,serialno,4);
	plain[4] = sectno;
	plain[5] = ~plain[4];
	
	for(i = 0;i < 6; ++i)
	{
		keya[i] = plain[i];
		for(j = 0;j < 6;++j)
			keya[i] ^= plain[j] ^ mkey[j];
	}
}


	calkey(snr,3,password_xf1,buff);