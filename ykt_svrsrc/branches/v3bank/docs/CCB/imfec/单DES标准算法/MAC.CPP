#include <string.h>
#include "OemDefin.H"
#include <malloc.h>
#include <fcntl.h>
#include <memory.h>

// S-function table
BYTE SFun_Tab[8][64] =
{
	//  S-1
	{
		14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
		 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
         4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
    },
	//  S-2
    {
		15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
		 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	     0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
		13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
	},
    //  S-3
	{
		10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
		13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
		13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
		 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
	},
    //  S-4
	{
		 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
		13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
		10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
		 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
	},
    //  S-5
	{
		 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
		14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	     4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
		11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
	},
    //  S-6
	{
		12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
		10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
		 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
		 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
	} ,
    //  S-7
	{
		 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
		13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
		 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
		 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
	},
    //  S-8
	{
		13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
		 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
		 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
		 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
	}
};

//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////Asc,Bcd码转换//////////////////////////////

int  NCBS_Asc0_FToBcd(BYTE *pAscBuf,int ascLen,BYTE *pBcdBuf,BYTE rightFill0)
{
	BYTE data1=0x55,data2=0,rightMake=NC_False;
	int  i=0;
	if(ascLen<1)
		return NC_False;
	if( (ascLen & 0x01) == 0x00){      //数据位数正好对齐
		data1=0x55;
		rightMake=NC_False;
	}
	else if(rightFill0 ==NC_False){   //数据位数对不齐,左补0
		data1=0;
		rightMake=NC_False;
	}
	else if(rightFill0 ==NC_True){   //数据位数对不齐,右补0
		data1=0x55;
		rightMake=NC_True;
	}
	else
		return NC_False;
    for(i=0;i<ascLen;i++,pAscBuf++){
		if ( *pAscBuf >= 'a' )
			data2 = *pAscBuf - 'a' + 10 ;
		else if ( *pAscBuf >= 'A' )
			data2 = *pAscBuf- 'A' + 10 ;
		else if ( *pAscBuf >= '0' )
			data2 = *pAscBuf-'0' ;
		else
			data2 = 0;
		if ( data1 == 0x55 )
			data1 = data2 ;
		else {
			*pBcdBuf ++ = (data1 << 4) | data2 ;
			data1 = 0x55 ;
		}
	}
	if( rightMake==NC_True)
		*pBcdBuf ++ =  data2<<4 ;
    return NC_True;
}

int  NCBS_BcdToAsc0_F(BYTE *pBcdBuf,int bcdLen,BYTE *pAscBuf,int ascLen,BYTE LeftFirst)
{
	int  i=0;
	BYTE data=0;
	if(bcdLen <1 || ascLen<bcdLen*2-1 || ascLen>bcdLen*2 )
		return NC_False;
    if(ascLen==bcdLen*2-1 && LeftFirst==NC_False){
		data= ((*pBcdBuf++) & 0x0F);
		*pAscBuf++=  (data>0x09) ?  ('A'+(data- 0xa)) : ('0'+data);
		i=1;
	}
	else
		i=0;
	for(;i<bcdLen;i++){
		data= ((*pBcdBuf) & 0xF0)>>4;
		*pAscBuf++=  (data>0x09) ?  ('A'+(data- 0xa)) : ('0'+data);
		data= ((*pBcdBuf) & 0x0F);
		*pAscBuf ++=  (data>0x09) ?  ('A'+(data- 0xa)) : ('0'+data);
		pBcdBuf++;
	}
    return NC_True;
}

void   DoFirstChange(BYTE *pS)   // change s
{
	int i, j;
	BYTE tmp[8]={0,0,0,0,0,0,0,0};
	memset(tmp,0x00,8);
	for(i = 0; i < 8; ++i){
		for(j = 0; j < 8; ++j)
			tmp[7-j] |=(BYTE) (((pS[i] >> j) & 0x01 ) << i);
	}
	for(i = 0; i < 4; ++i){
		pS[i] = tmp[2*i+1];
		pS[i+4] = tmp[2*i];
	}
}		

void   DoLastChange(BYTE *pS)
{
	int i, j;
	BYTE tmp[8]={0,0,0,0,0,0,0,0};
	memset(tmp,0x00,8);
	for(i = 0; i < 8; ++i){
		for(j = 0; j < 4; ++j){
			tmp[i] |= (BYTE)(((pS[j] << (7-i)) & 0x80) >> (2*j+1));
			tmp[i] |= (BYTE)(((pS[j+4] << (7-i)) & 0x80) >> (2*j));
		}
	}
	memcpy(pS,tmp,8);
}

void MakeKey(BYTE * pKeyS,BYTE * pKeyD)   // Key ->C, D
{
	int i, j;
	BYTE tmp[8]={0,0,0,0,0,0,0,0};
	memset(tmp,0x00,8);
	memset(pKeyD,0x00,8);
	//D = C + 4;
	for(i = 0; i < 8; ++i){
		for(j = 0; j < 8; ++j)
			tmp[7-j] |= (BYTE)(((pKeyS[i] & (0x01 << j)) >> j) << i);
	}
	for(i = 0; i < 4; i++) {
		pKeyD[i] = tmp[i];
		pKeyD[i+4] = tmp[6-i];
	}
	pKeyD[3] &= 0xf0;
	pKeyD[3+4] = (BYTE)((pKeyD[3+4] & 0x0f) << 4);
}
		
void   DoLeft(BYTE *pS, int n)  // left shift s n bits
{
	BYTE L, t;
	int  i;
	L =(BYTE)( 0xff << (8 - n));
	t =(BYTE)((pS[0] & L) >> 4);
	pS[3] |= t;
	for(i = 0; i < 3; i++){
		pS[i] <<= n;
		t = (BYTE)((pS[i+1] & L) >> (8 - n));
		pS[i] |= t;
	}
	pS[3] = (BYTE)(pS[3] << n);
}        

void   MyrShift(BYTE *pS)    // right shift s 1 bits
{
	BYTE  l=(BYTE)(pS[0] & 1);
	BYTE  l1 =(BYTE)(pS[1] & 1);
	pS[0] >>= 1;
	pS[1] >>= 1;
	pS[1] |= (BYTE)(l << 7);
	l =(BYTE)( pS[2] & 1);
	pS[2] >>= 1;
	pS[2] |= (BYTE)(l1 << 7);
	pS[3] >>= 1;
	pS[3] |= (BYTE)(l << 7);
	if((pS[3] & 0xf) != 0){
		pS[0] |= 0x80;
		pS[3] &= 0xf0;
	}
}        
void   DoRight(BYTE *pS, int n)    // right shift s n bits
{ 
	int i=0;
	for(i = 0; i < n; ++i)  
		MyrShift(pS);
}
		
void   EExpand(BYTE *pS, BYTE *pR)
{
	pR[0] = (BYTE)(((pS[3] & 0x01) << 7) | ((pS[0] & 0xf8) >> 1) | ((pS[0] & 0x18) >> 3));
	pR[1] = (BYTE)(((pS[0] & 0x07) << 5) | ((pS[0] & 0x01) << 3) |
				((pS[1] & 0x80) >> 3) | ((pS[1] & 0xe0) >> 5));
	pR[2] = (BYTE)(((pS[1] & 0x18) << 3) | ((pS[1] & 0x1f) << 1) | ((pS[2] & 0x80) >> 7));
	pR[3] = (BYTE)(((pS[1] & 0x01) << 7) | ((pS[2] & 0xf8) >> 1) | ((pS[2] & 0x18) >> 3));
	pR[4] = (BYTE)(((pS[2] & 0x07) << 5) | ((pS[2] & 0x01) << 3) |
				((pS[3] & 0x80) >> 3) | ((pS[3] & 0xe0) >> 5));
	pR[5] = (BYTE)(((pS[3] & 0x18) << 3) | ((pS[3] & 0x1f) << 1) | ((pS[0] & 0x80) >> 7));
}

void   PChang(BYTE *pS)
{
	int  i;
	BYTE t[4]={0,0,0,0};
	t[0] = (BYTE)(((pS[1] & 0x01) << 7) | ((pS[0] & 0x02) << 5) | ((pS[2] & 0x10) << 1) |
		((pS[2] & 0x08) << 1) | (pS[3] & 0x08)  | ((pS[1] & 0x10) >> 2) |
		((pS[3] & 0x10) >> 3) | ((pS[2] & 0x80) >> 7) );
	t[1] = (BYTE)((pS[0] & 0x80)  | ((pS[1] & 0x02) << 5) | ((pS[2] & 0x02) << 4) |
		((pS[3] & 0x40) >> 2) | (pS[0] & 0x08)  | ((pS[2] & 0x40) >> 4) |
		(pS[3] & 0x02)  | ((pS[1] & 0x40) >> 6) );
	t[2] = (BYTE)(((pS[0] & 0x40) << 1) | ((pS[0] & 0x01) << 6) | ((pS[2] & 0x01) << 5) |
		((pS[1] & 0x04) << 2) | ((pS[3] & 0x01) << 3) | ((pS[3] & 0x20) >> 3) |
		((pS[0] & 0x20) >> 4) | ((pS[1] & 0x80) >> 7) ) ;
	t[3] = (BYTE)(((pS[2] & 0x20) << 2) | ((pS[1] & 0x08) << 3) | ((pS[3] & 0x04) << 3) |
		((pS[0] & 0x04) << 2) | ((pS[2] & 0x04) << 1) | ((pS[1] & 0x20) >> 3) |
		((pS[0] & 0x10) >> 3) | ((pS[3] & 0x80) >> 7) ) ;
	//Array.Copy(t,1,s,1,4);
	for(i= 0 ; i < 4; ++i)  
		pS[i] = t[i];
}

BYTE   FindS(BYTE *pS, int begin,int ns)
{
	int  col=0, num=0, index=0;
	if(ns == 1 || ns == 5){
		col = (( pS[begin] & 0x80) >> 6 ) | ((pS[begin] & 0x04) >> 2);
		num = ( pS[begin] & 0x78) >> 3;
		index = col * 16 + num;
	}
	if(ns == 2 || ns == 6){
		col = ( pS[begin] & 0x02) | ((pS[begin+1] & 0x10) >> 4);
		num = ((pS[begin] & 0x01) << 3) | (( pS[begin+1] & 0xe0) >> 5);
		index = col * 16 + num;
	}
	if(ns == 3 || ns == 7){
		col = (( pS[begin+1] & 0x08) >> 2) | ((pS[begin+2] & 0x40) >> 6);
		num = (( pS[begin+1] & 0x07) << 1) | ((pS[begin+2] & 0x80) >> 7);
		index = col * 16 + num;
	}
	if(ns == 4 || ns == 8){
		col = (( pS[begin+2] & 0x20) >> 4) | (pS[begin+2] & 0x01) ;
		num = (( pS[begin+2] & 0x1e) >> 1);
		index = col * 16 + num;
	}
	return SFun_Tab[ns-1][index];
}

void   DoSfun(BYTE *pS, BYTE *pR)
{
	pR[0] = (BYTE)((FindS(pS,0,1) << 4) | FindS(pS,0,2));
	pR[1] = (BYTE)((FindS(pS,0,3) << 4) | FindS(pS,0,4));
	pR[2] = (BYTE)((FindS(pS,3,5) << 4) | FindS(pS,3,6));
	pR[3] = (BYTE)((FindS(pS,3,7) << 4) | FindS(pS,3,8));
}

void   FFun(BYTE *pR, BYTE *pK, BYTE *pM)
{
	int  i;
	BYTE t[6]={0,0,0,0,0,0};
	memset(t,0x00,6);
	EExpand(pR, t);
	for(i = 0; i < 6; ++i)  t[i] ^= pK[i];
		DoSfun(t, pM);
	PChang(pM);
}

void   DoMut(BYTE *pL, BYTE *pR, BYTE *pK)
{
	int  i;
	BYTE t[4]={0,0,0,0};
	memset(t,0x00,4);
    FFun(pR, pK, t);
	for(i = 0; i < 4; ++i){
		t[i] ^= pL[i];
		pL[i] = pR[i];
		pR[i] = t[i];
	}
}

void   SetKey(BYTE encrypt, BYTE *pC, BYTE *pD, int n, BYTE *pK)
{
	memset(pK,0x00,6);
	if(encrypt==NC_True){
		DoLeft(pC, n);
		DoLeft(pD, n);
	}
	pK[0] = (BYTE) ( ((pC[1] & 4) << 5) | ((pC[2] & 0X80) >> 1) | (pC[1] & 0X20) |
		((pC[2] & 1) << 4) | ((pC[0] & 0X80) >> 4) | ((pC[0] & 8) >> 1) |
		((pC[0] & 0X20) >> 4) | ((pC[3] & 0X10) >> 4));
	pK[1] =(BYTE) ( ((pC[1] & 2) << 6) | ((pC[0] & 4) << 4) | ((pC[2] & 8) << 2) |
		((pC[1] & 0X40) >> 2) | ((pC[2] & 2) << 2) | ((pC[2] & 0x20) >> 3) |
		((pC[1] & 0X10) >> 3) | ((pC[0] & 0X10) >> 4));
	pK[2] =(BYTE) ( ((pC[3] & 0x40) << 1) | ((pC[0] & 0X01) << 6) | ((pC[1] & 0X01) << 5) |
		((pC[0] & 2) << 3) | ((pC[3] & 0X20) >> 2) | ((pC[2] & 0x10) >> 2) |
		((pC[1] & 0X08) >> 2) | ((pC[0] & 0X40) >> 6));
	pK[3] =(BYTE) (  ((pD[1] & 0x08) << 4) | ((pD[2] & 0X01) << 6) | (pD[0] & 0X20)  |
		((pD[1] & 0x80) >> 3) | ((pD[2] & 0X20) >> 2) | ((pD[3] & 0x20) >> 3) |
		((pD[0] & 0X40) >> 5) | ((pD[1] & 0X10) >> 4));
	pK[4] =(BYTE) (  ((pD[2] & 0x02) << 6) | ((pD[2] & 0X80) >> 1) | ((pD[0] & 0X08) << 2) |
		(pD[2] & 0x10)  | ((pD[1] & 0X01) << 3 ) | ((pD[2] & 0x08) >> 1) |
		((pD[1] & 0X20) >> 4) | ((pD[3] & 0X10) >> 4));
	pK[5] =(BYTE) (  ((pD[0] & 0x04) << 5) | ((pD[3] & 0X80) >> 1) | ((pD[2] & 0X40)) >> 1 |
		((pD[1] & 0x04) << 2) | ((pD[2] & 0X04) << 1) | ((pD[0] & 0x01) << 2) |
		((pD[0] & 0X80) >> 6) | ((pD[0] & 0X10) >> 4));
	if(encrypt==NC_False){
		DoRight(pC, n);
		DoRight(pD, n);
	}
}

void DesEncrypt(BYTE* pKey, BYTE *pBufS) 
{
	int  i ;
	int	 nLoop[16]={1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
	BYTE C0[4],D0[4],L[4],R[4],K[6];
	BYTE c;
    memset(C0,0x00,4);
    memset(D0,0x00,4);
    memset(L,0x00,4);
    memset(R,0x00,4);
    memset(K,0x00,6);
	//unsigned char *L, *R, c;
	//unsigned char *D0 = C0 + 4;
	DoFirstChange(pBufS);
	//L = s1; R = s1 + 4;
	memcpy(C0,pKey,4);
	memcpy(D0,pKey+4,4);
	memcpy(L,pBufS,4);
	memcpy(R,pBufS+4,4);
	for(i = 0; i < 16; ++i)	{
		SetKey(NC_True, C0, D0, nLoop[i], K);
		DoMut(L, R, K);
	}
	memcpy(pBufS,L,4);
	memcpy(pBufS+4,R,4);
	for(i = 0; i < 4; ++i){
		c = R[i];
		pBufS[i+4] = L[i];
		pBufS[i] = c;
	}
	DoLastChange(pBufS);
}

void  DesDecryptor(BYTE *pKey,BYTE *pBufS)
{
	int  i ;
	int	 nLoop[16]={1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 1};
	BYTE C0[4],D0[4],L[4],R[4],K[6];
	BYTE c;
    memset(C0,0x00,4);
    memset(D0,0x00,4);
    memset(L,0x00,4);
    memset(R,0x00,4);
    memset(K,0x00,6);
	//unsigned char *L, *R, c;
	//unsigned char *D0 = C0 + 4;
	DoFirstChange(pBufS);
	//L = s1; R = s1 + 4;
	memcpy(C0,pKey,4);
	memcpy(D0,pKey+4,4);
	memcpy(L,pBufS,4);
	memcpy(R,pBufS+4,4);
    for(i = 0; i < 16; ++i){
		SetKey(NC_False, C0, D0, nLoop[i], K);
		DoMut(L, R, K);
	}
	memcpy(pBufS,L,4);
	memcpy(pBufS+4,R,4);
	for(i = 0; i < 4; ++i){
		c = R[i];
		pBufS[i+4] = L[i];
		pBufS[i] = c;
	}
	DoLastChange(pBufS);
}

int  NCBS_Des08_Encrypt(BYTE *pKey08,BYTE *pBufS08,BYTE *pBufD08)
{ 
	BYTE key[8],bufS[8],newKey[8];
	memset(pBufD08,0x00,8);
	memset(newKey,0x00,8);
	memcpy(key,pKey08,8);
	memcpy(bufS,pBufS08,8);
	MakeKey(key,newKey);			// get C,D
	DesEncrypt(newKey,bufS);
	memcpy(pBufD08,bufS,8);
	return NC_True;
} 

int  NCBS_Des08_Decryptor(BYTE *pKey08,BYTE *pBufS08,BYTE *pBufD08)
{
	BYTE key[8],bufS[8],newKey[8];
	memset(pBufD08,0x00,8);
	memset(newKey,0x00,8);
	memcpy(key,pKey08,8);
	memcpy(bufS,pBufS08,8);
	MakeKey(key,newKey);       // get C,D
	DesDecryptor(newKey,bufS);
	memcpy(pBufD08,bufS,8);
	return NC_True;
} 

int  NCBS_Des08_Ansi98Encrypt(BYTE *pKey08,BYTE *pBankCardNo20,int bankCardLen,BYTE *pBankPass08,BYTE *pBufD08)
{
	BYTE  pinBcd[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	BYTE  cardBcd[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	int i=0, bankSeek=bankCardLen-13;
	memset(pBufD08,0x00,8);
	if(bankCardLen<16 || bankCardLen>20)
		return NC_False;
	memset(pinBcd,0xFF,8);
	memset(cardBcd,0xFF,8);
    NCBS_Asc0_FToBcd(pBankPass08,6,pinBcd+1,NC_True);
	pinBcd[0]=0x06;
 	//pinBCD[4]=pinBCD[5]=pinBCD[6]=pinBCD[7]=0xFF;
    NCBS_Asc0_FToBcd(pBankCardNo20+bankSeek,12,cardBcd+2,NC_True);
	for(i=2;i<8;i++)
		pinBcd[i] ^=cardBcd[i];
	NCBS_Des08_Encrypt(pKey08,pinBcd,pBufD08);
	return NC_True;
}

int  NCBS_Des08_Ansi98Decryptor(BYTE *pKey08,BYTE *pBankCardNo20,int bankCardLen,BYTE *pBufS08,BYTE *pBankPass08)
{
	BYTE  pinBcd[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	BYTE  cardBcd[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	BYTE  bufD[16];
	int i=0, bankSeek=bankCardLen-13;
	memset(pBankPass08,0x00,8);
	if(bankCardLen<16 || bankCardLen>20)
		return NC_False;
	memset(pinBcd,0xFF,8);
	memset(cardBcd,0xFF,8);
    NCBS_Asc0_FToBcd(pBankCardNo20+bankSeek,12,cardBcd+2,NC_True);
	NCBS_Des08_Decryptor(pKey08,pBufS08,bufD);
    pinBcd[0]=bufD[0];
	pinBcd[1]=bufD[1];
	for(i=2;i<8;i++)
		pinBcd[i] =(BYTE)(bufD[i] ^ cardBcd[i]);
	NCBS_BcdToAsc0_F(pinBcd+1,3,bufD+2,6,NC_True);
    memcpy(pBankPass08,bufD+2,6);
	pBankPass08[6]=pBankPass08[7]=0x20;
	return NC_True;
}

int  NCBS_Des08_Ansi99New(BYTE *pKey08,BYTE *pBufS,int begin,int len,BYTE *pMacD08)
{
	BYTE  data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	BYTE  mac[9] ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	BYTE  *pS=pBufS+begin;
	int   i=0,j=0;
	memset(pMacD08,0x00,8);
	memset(mac,0x00,8);
	if(begin<0 || len <0)
		return NC_False;
    for(i=0,pS=pBufS+begin;i<len;i+=8,pS+=8)
	{
		if(i+8 < len)
			memcpy(data,pS,8);
		else{
			memset(data,0x00,8);
			memcpy(data,pS,len-i);
		}
		for (j=0; j<8; j++) 
			mac[j]=(BYTE)(mac[j] ^ data[j]);
		NCBS_Des08_Encrypt(pKey08,mac,pMacD08);
		memcpy(mac,pMacD08,8);
	}
	return NC_True;
}

int  NCBS_Des08_Ansi99Check(BYTE *pKey08,BYTE *pBufS,int begin,int len,BYTE *pMacS08,BYTE *pMacD08)
{	
	if(NCBS_Des08_Ansi99New(pKey08,pBufS,begin,len,pMacD08)==NC_True){
		if(memcmp(pMacS08,pMacD08,8)==0)
			return NC_True;
	}
	return NC_False;
}



////////////////////////////////////////////////////////////////////
char sbox1[] =
{
   14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
    0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
    4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
   15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13
};


char sbox2[] =
{
   15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
    3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
    0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
   13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9
};




char sbox3[] =
{
   10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
   13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
   13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
    1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12
};




char sbox4[] =
{ 
    7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
   13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
   10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
    3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14
};




char sbox5[] =
{ 
    2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
   14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
    4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
   11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3
};




char sbox6[] =
{
   12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
   10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
    9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
    4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13
};





char sbox7[] =
{ 
    4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
   13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
    1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
    6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12
};




char sbox8[] =
{
   13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
    1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
    7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
    2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11
};



char *sbox[] =
{ 
   sbox1, 
   sbox2, 
   sbox3, 
   sbox4,
   sbox5,
   sbox6,
   sbox7,
   sbox8
};


/* 
**   for initial permutation
*/
char table1[] = 
{
   58,50,42,34,26,18,10, 2,60,52,44,36,28,20,12, 4,
   62,54,46,38,30,22,14, 6,64,56,48,40,32,24,16, 8,
   57,49,41,33,25,17, 9, 1,59,51,43,35,27,19,11, 3,
   61,53,45,37,29,21,13, 5,63,55,47,39,31,23,15, 7
};



/* 
**   for permutation choice 1
*/
char table2[] =
{
   57,49,41,33,25,17, 9, 1,58,50,42,34,26,18,
   10, 2,59,51,43,35,27,19,11, 3,60,52,44,36,
   63,55,47,39,31,23,15, 7,62,54,46,38,30,22,
   14, 6,61,53,45,37,29,21,13, 5,28,20,12, 4
};



/* 
**   for expansion function
*/
char table3[] = 
{
   32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9,10,11,
   12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,
   22,23,24,25,24,25,26,27,28,29,28,29,30,31,32, 1
};



/* 
**   for permutation choice 2
*/
char table4[] = 
{
   14,17,11,24, 1, 5, 3,28,15, 6,21,10,23,19,12, 4,
   26, 8,16, 7,27,20,13, 2,41,52,31,37,47,55,30,40,
   51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32
};




/* 
**   for inverse of initial permutation
*/
char table5[] = 
{
   40, 8,48,16,56,24,64,32,39, 7,47,15,55,23,63,31,
   38, 6,46,14,54,22,62,30,37, 5,45,13,53,21,61,29,
   36, 4,44,12,52,20,60,28,35, 3,43,11,51,19,59,27,
   34, 2,42,10,50,18,58,26,33, 1,41, 9,49,17,57,25
};




/* 
**   for permutation function P
*/
char table6[] = 
{
   16, 7,20,21,29,12,28,17, 1,15,23,26, 5,18,31,10,
    2, 8,24,14,32,27, 3, 9,19,13,30, 6,22,11, 4,25
};




/* 
**   for selection function
*/
char table7[] = 
{ 
    1, 6, 2, 1, 7,12, 8, 5,13,18,14, 9,19,24,20,13,
   25,30,26,17,31,36,32,21,37,42,38,25,43,48,44,29
};



/* 
**   for shift left 1
*/
char table8[] = 
{ 
    2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,
   18,19,20,21,22,23,24,25,26,27,28, 1,30,31,32,33,
   34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,
   50,51,52,53,54,55,56,29
};




/* 
**   for shift left 2
*/
char table9[] = 
{    
    3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,
   19,20,21,22,23,24,25,26,27,28, 1, 2,31,32,33,34,
   35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,
   51,52,53,54,55,56,29,30
};



/* 
**   for shift right 1
*/
char table10[] = 
{
   28, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
   16,17,18,19,20,21,22,23,24,25,26,27,56,29,30,31,
   32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
   48,49,50,51,52,53,54,55
};




/* 
**   for shift right 2
*/
char table11[] = 
{
   27,28, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
   15,16,17,18,19,20,21,22,23,24,25,26,55,56,29,30,
   31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,
   47,48,49,50,51,52,53,54
};





/* 
**   content is table index,total count
*/
char *table[] =
{
   table1,table2,table3,table4, table5,table6,
   table7,table8,table9,table10,table11
};



unsigned char initial_permutation[] = { 0, 64 };
unsigned char permutation_c1[] = { 1, 56 };
unsigned char expansion_function[] = { 2, 48 };
unsigned char permutation_c2[] = { 3, 48 };
unsigned char inverse_ip[] = { 4, 64 };
unsigned char permutation_fp[] = { 5, 32 };
unsigned char shift_left1[] = { 7, 56 };
unsigned char shift_left2[] = { 8, 56 };
unsigned char shift_right1[] = { 9, 56 };
unsigned char shift_right2[] = { 10, 56 };
unsigned char x64[8],i64[8],k64[8],k56[7],k48[6],l32[4],r48[6],r32[4];





void transdata( unsigned char *input,
                unsigned char *output,
                unsigned char *function )
{
   int i;
   unsigned char out[8];

   /* 
   **   initial value with 0
   */
   for ( i=0; i<(int)(function[1]>>3); i++ )
   {
       out[i]=0;
   }

   for ( i=0; i<(int)function[1]; i++ )
   {
       out[i>>3] |= ( unsigned char )( ( input[table[function[0]][i]-1 >> 3]
                      & ( 0x80 >> ( table[function[0]][i]-1 & 0x7 ) ) )
                      << ( table[function[0]][i]-1 & 0x7 ) ) >> (i&0x7);
   }

   /* 
   **   initial value with 0
   */
   for ( i=0; i<(int)(function[1]>>3); i++ )
   {
       output[i]=out[i];
   }
}




void SDES_select( unsigned char *input, unsigned char *output )
{
   int idx,i,j,k,cnt;

   /* 
   **   initial value with 0
   */
   for ( i=0; i<4; i++ )
   {
       output[i] = 0;
   }

   cnt = 0;
   for ( i=0; i<8; i++ )
   {
       for ( j=5, k=0, idx=0; j>=0; j-- )
       {
           idx+=((input[table7[cnt]-1+k>>3] & (0x80>>(table7[cnt]-1+k & 0x7)))
                ? 1 <<j : 0);

           if ( j>3 )
           {
              cnt++;
           }
           else
           {
              k++;
           }
       }

       cnt++;
       for ( j=0; j<4; j++ )
       {
           output[table7[cnt]+j-1 >> 3] |= ((sbox[i][idx] & (0x08 >> j)) << 4+j)
                                        >> (table7[cnt]+j-1 & 0x7);
       }
       cnt++;
   }
}



/* 
**   io->r32 
**   input->k56 
*/
void fnct( unsigned char *io, unsigned char *input )
{
   unsigned char k48[6],r48[6],s32[4];
   int i;

   /* 
   **   28+28 to 48
   */
   transdata( input, k48, permutation_c2 ); 

   /* 
   **   32 to 48
   */
   transdata( io, r48, expansion_function ); 

   /* 
   **   expn xor key
   */
   for ( i=0; i<6; i++ )
   {
       r48[i] ^= k48[i];
   }

   SDES_select( r48, s32 );

   transdata( s32, io, permutation_fp );
}



/* 
**   input->x64 
**   key->k64 
**   output->i64 
*/
void SDES_Encrypt( unsigned char *input, 
              unsigned char *key, 
              unsigned char *output )
{
   unsigned char i64[8],k56[7],t32[4];

   transdata( input, i64, initial_permutation );
   transdata( key, k56, permutation_c1 );

   /*
   **   shift left 1
   */
   transdata( k56, k56, shift_left1 );

   t32[0] = i64[4]; 
   t32[1] = i64[5]; 
   t32[2] = i64[6]; 
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0]; 
   i64[5] ^= i64[1]; 
   i64[6] ^= i64[2]; 
   i64[7] ^= i64[3];
   i64[0]  = t32[0]; 
   i64[1]  = t32[1]; 
   i64[2]  = t32[2]; 
   i64[3]  = t32[3];

   /*
   **   shift left 1
   */
   transdata( k56, k56, shift_left1 );

   t32[0] = i64[4]; 
   t32[1] = i64[5]; 
   t32[2] = i64[6]; 
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0]; 
   i64[5] ^= i64[1]; 
   i64[6] ^= i64[2]; 
   i64[7] ^= i64[3];
   i64[0]  = t32[0]; 
   i64[1]  = t32[1]; 
   i64[2]  = t32[2]; 
   i64[3]  = t32[3];

   /*
   **   shift left 2
   */
   transdata(k56,k56,shift_left2);

   t32[0] = i64[4]; 
   t32[1] = i64[5]; 
   t32[2] = i64[6]; 
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0]; 
   i64[5] ^= i64[1]; 
   i64[6] ^= i64[2]; 
   i64[7] ^= i64[3];
   i64[0]  = t32[0]; 
   i64[1]  = t32[1]; 
   i64[2]  = t32[2]; 
   i64[3]  = t32[3];

   /*
   **   shift left 2
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4]; 
   t32[1] = i64[5]; 
   t32[2] = i64[6]; 
   t32[3] = i64[7];

   fnct(i64+4,k56);

   i64[4] ^= i64[0]; 
   i64[5] ^= i64[1]; 
   i64[6] ^= i64[2]; 
   i64[7] ^= i64[3];
   i64[0]  = t32[0]; 
   i64[1]  = t32[1]; 
   i64[2]  = t32[2]; 
   i64[3]  = t32[3];

   /*
   **   shift left 2
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4]; 
   t32[1] = i64[5]; 
   t32[2] = i64[6]; 
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0]; 
   i64[5] ^= i64[1]; 
   i64[6] ^= i64[2]; 
   i64[7] ^= i64[3];
   i64[0]  = t32[0]; 
   i64[1]  = t32[1]; 
   i64[2]  = t32[2]; 
   i64[3]  = t32[3];

   /*
   **   shift left 2 
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4]; 
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0]; 
   i64[5] ^= i64[1]; 
   i64[6] ^= i64[2]; 
   i64[7] ^= i64[3];
   i64[0]  = t32[0]; 
   i64[1]  = t32[1]; 
   i64[2]  = t32[2]; 
   i64[3]  = t32[3];

   /*
   **   shift left 2 
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   fnct(i64+4,k56);

   i64[4] ^= i64[0];
   i64[5] ^= i64[1];
   i64[6] ^= i64[2];
   i64[7] ^= i64[3];
   i64[0]  = t32[0];
   i64[1]  = t32[1];
   i64[2]  = t32[2];
   i64[3]  = t32[3];

   /*
   **   shift left 2 
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4]; 
   t32[1] = i64[5]; 
   t32[2] = i64[6]; 
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0]; 
   i64[5] ^= i64[1]; 
   i64[6] ^= i64[2]; 
   i64[7] ^= i64[3];
   i64[0]  = t32[0]; 
   i64[1]  = t32[1]; 
   i64[2]  = t32[2]; 
   i64[3]  = t32[3];

   /*
   **   shift left 1 
   */
   transdata( k56, k56, shift_left1 );

   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0];
   i64[5] ^= i64[1];
   i64[6] ^= i64[2];
   i64[7] ^= i64[3];
   i64[0]  = t32[0];
   i64[1]  = t32[1];
   i64[2]  = t32[2];
   i64[3]  = t32[3];

   /*
   **   shift left 2 
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0];
   i64[5] ^= i64[1];
   i64[6] ^= i64[2];
   i64[7] ^= i64[3];
   i64[0]  = t32[0];
   i64[1]  = t32[1];
   i64[2]  = t32[2];
   i64[3]  = t32[3];

   /*
   **   shift left 2
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0];
   i64[5] ^= i64[1];
   i64[6] ^= i64[2];
   i64[7] ^= i64[3];
   i64[0]  = t32[0];
   i64[1]  = t32[1];
   i64[2]  = t32[2];
   i64[3]  = t32[3];

   /*
   **   shift left 2
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0];
   i64[5] ^= i64[1];
   i64[6] ^= i64[2];
   i64[7] ^= i64[3];
   i64[0]  = t32[0];
   i64[1]  = t32[1];
   i64[2]  = t32[2];
   i64[3]  = t32[3];

   /*
   **   shift left 2
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0];
   i64[5] ^= i64[1];
   i64[6] ^= i64[2];
   i64[7] ^= i64[3];
   i64[0]  = t32[0];
   i64[1]  = t32[1];
   i64[2]  = t32[2];
   i64[3]  = t32[3];

   /*
   **   shift left 2
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0];
   i64[5] ^= i64[1];
   i64[6] ^= i64[2];
   i64[7] ^= i64[3];
   i64[0]  = t32[0];
   i64[1]  = t32[1];
   i64[2]  = t32[2];
   i64[3]  = t32[3];

   /*
   **   shift left 2
   */
   transdata( k56, k56, shift_left2 );

   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0];
   i64[5] ^= i64[1];
   i64[6] ^= i64[2];
   i64[7] ^= i64[3];
   i64[0]  = t32[0];
   i64[1]  = t32[1];
   i64[2]  = t32[2];
   i64[3]  = t32[3];

   /*
   **   shift left 1
   */
   transdata( k56, k56, shift_left1 );

   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   fnct( i64+4, k56 );

   i64[4] ^= i64[0];
   i64[5] ^= i64[1];
   i64[6] ^= i64[2];
   i64[7] ^= i64[3];
   i64[0]  = t32[0];
   i64[1]  = t32[1];
   i64[2]  = t32[2];
   i64[3]  = t32[3];

   /*
   **   substitute
   */
   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   i64[4] = i64[0];
   i64[5] = i64[1];
   i64[6] = i64[2];
   i64[7] = i64[3];

   i64[0] = t32[0];
   i64[1] = t32[1];
   i64[2] = t32[2];
   i64[3] = t32[3];

   transdata( i64, output, inverse_ip );
}




/*
**   input->x64 
**     key->k64
**  output->i64
*/
void SDES_Decrypt( unsigned char *input,
              unsigned char *key,
              unsigned char *output )
{
   unsigned char i64[8],k56[7],t32[4];

   transdata( input, i64, initial_permutation );

   /*
   **   substitute
   */
   t32[0] = i64[4];
   t32[1] = i64[5];
   t32[2] = i64[6];
   t32[3] = i64[7];

   i64[4] = i64[0];
   i64[5] = i64[1];
   i64[6] = i64[2];
   i64[7] = i64[3];

   i64[0] = t32[0];
   i64[1] = t32[1];
   i64[2] = t32[2];
   i64[3] = t32[3];

   transdata( key, k56, permutation_c1 );

   /*
   **   shift right 1
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right1 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 2 
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 1
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct(i64,k56);

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right1 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 2
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right2 );

   /*
   **   shift right 1
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right1 );

   /*
   **   shift right 1 
   */
   t32[0] = i64[0];
   t32[1] = i64[1];
   t32[2] = i64[2];
   t32[3] = i64[3];

   fnct( i64, k56 );

   i64[0] ^= i64[4];
   i64[1] ^= i64[5];
   i64[2] ^= i64[6];
   i64[3] ^= i64[7];
   i64[4]  = t32[0];
   i64[5]  = t32[1];
   i64[6]  = t32[2];
   i64[7]  = t32[3];

   transdata( k56, k56, shift_right1 );

   /*
   **   substitute
   */
   transdata( i64, output, inverse_ip );

}


/**  加密数据串
***  输入：1、pbyKey 密钥
***        2、iLen 数据长度
***        3、pbyInputDate 输入数据
***  输出：1、pbyOutputData 输出数据
***  说明：最大输入数据长度256
***        若数据不是8的倍数，则后补0X00至8的倍数
**/
void EncryptData( unsigned char *pbyKey, 
                  int           iLen,
                  unsigned char *pbyInputData,
                  unsigned char *pbyOutputData )
{
   int  i;
   unsigned char abyBuf[4096];

   memset( abyBuf, 0, 4096 );
   memcpy( abyBuf, pbyInputData, iLen );

   for ( i=0; i<(iLen/8); i++ )
   {
      SDES_Encrypt( abyBuf+i*8,
                    pbyKey,
                    pbyOutputData+i*8 );
   }
}

/**  解密数据串
***  输入：1、pbyKey 密钥
***        2、iLen 数据长度
***        3、pbyInputDate 输入数据
***  输出：1、pbyOutputData 输出数据
***  说明：解密由EncryptData加密的数据
**/
void DecryptData( unsigned char *pbyKey,
                  int           iLen,
                  unsigned char *pbyInputData,
                  unsigned char *pbyOutputData )
{
   int  i;
   unsigned char abyBuf[4096];

   memset( abyBuf, 0, 4096 );
   memcpy( abyBuf, pbyInputData, iLen );

   for ( i=0; i<(iLen/8); i++ )
   {
      SDES_Decrypt( abyBuf+i*8,
                    pbyKey,
                    pbyOutputData+i*8 );
   }
}

/**3DES加密***
***输入：1、input 要加密的数据8byte
***      2、key   16byte密钥（前8bype为密钥1，后8byte为密钥2）
***输出：1、output 加密结果8byte
***算法：input->密钥1加密->密钥2解密->密钥1加密->output
***/
void SDES_TriEncrypt( unsigned char *input,
                      int      eiLen,
                      unsigned char *key,
                      unsigned char *output )

{
   unsigned char abykey1[8];
   unsigned char abykey2[8];
   unsigned char output1[4096];
   unsigned char output2[4096];

   memcpy( abykey1, key, 8 );
   memcpy( abykey2, key+8, 8 );

   EncryptData( abykey1, eiLen, input, output1 ); 
   DecryptData( abykey2, eiLen, output1, output2 ); 
   EncryptData( abykey1, eiLen, output2, output ); 
}

/**3DES解密***
***输入：1、input 要解密的数据8byte
***      2、key   16byte密钥（前8bype为密钥1，后8byte为密钥2）
***输出：1、output 解密结果8byte
***算法：input->密钥1解密->密钥2加密->密钥1解密->output
***/
void SDES_TriDecrypt( unsigned char *input,
                      int eiLen,
                      unsigned char *key,
                      unsigned char *output )

{
   unsigned char abykey1[8];
   unsigned char abykey2[8];
   unsigned char output1[4096];
   unsigned char output2[4096];
   int  i;

   memcpy( abykey1, key, 8 );
   memcpy( abykey2, key+8, 8 );


   DecryptData( abykey1, eiLen, input, output1 ); 

   EncryptData( abykey2, eiLen, output1, output2 ); 

   DecryptData( abykey1, eiLen, output2, output ); 

}

