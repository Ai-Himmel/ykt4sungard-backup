#include "stdafx.h"

/*=======================================================================
			DATA FOR DES PROGRAM
========================================================================*/

unsigned char	InitialTr[64] = {
	58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7
};

unsigned char	FinalTr[64] = {
	40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25
};

unsigned char	KeyTr1[56] = {
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18, 10,  2,
	59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36, 63, 55, 47, 39,
	31, 23, 15,  7, 62, 54, 46, 38, 30, 22, 14,  6, 61, 53, 45, 37,
	29, 21, 13,  5, 28, 20, 12,  4
};

unsigned char	KeyTr2[48] = {
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10, 23, 19, 12,  4,
	26,  8, 16,  7, 27, 20, 13,  2, 41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

unsigned char	Etr[48] = {
	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,  8,  9, 10, 11,
	12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21,
	22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};

unsigned char	Ptr[32] = {
	16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
	2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
};

unsigned char	S[8][64] = {
	{   14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13 },

	{   15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9 },

	{   10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12 },

	{    7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14 },

	{    2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3 },

	{   12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 },

	{    4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12 },

	{   13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 }
};	


unsigned char	Rots[16] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

void transpose(int *data,unsigned char *tr,int n)
{
	register int i, k;
	int     temp[64];

	for(i=0;i<n;i++){
		k=tr[i]-1;
		/*
		if(data[k]==(int)NULL) {
			printf("Nit Des Error..\n");
			fflush(stdout);
			k=tr[0]-1;
		}
		*/
		temp[i]=data[k];
	}
	for(i=0;i<n;i++) data[i]=temp[i];
}

void xchange(int *a)
{
	register int i,aa;
	for(i=0;i<32;i++){
		aa=a[i];
		a[i]=a[i+32];
		a[i+32]=aa;
	}
}

/***************************************************************************
  SUPPOSE dsp CONTAINS THE ASSCII ARRAY "12345F" AND WE EXECUTE THIS FUNCTION
  THEN THE ARRAY  AT hex WILL CONTAIN 12H,34H, 5FH
****************************************************************************/

void _stdcall SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count)
{
	int i;
	unsigned char ch;
	
	for(i=0;i<count;i++)
	{
		ch = dsp[i*2];
		if(ch>='a')
			ch -= 0x20;
		hex[i]=((ch<=0x39)?ch-0x30:ch-0x41+10);
		hex[i]=hex[i]<<4;

		ch = dsp[i*2+1];
		if(ch>='a')
			ch -= 0x20;
		hex[i]+=(((ch<=0x39)?ch-0x30:ch-0x41+10)&0x0f);
	}
}


/***************************************************************************
 SUPPOSE HEX CONTAINS THREE BYTES:12H 34H, 5FH AND WE EXECUTE THIS FUNCTION
 THEN dsp WILL CONTAIN ASCII BYTES "12345F"(Input:hex,count;Ouput:dsp)
 **************************************************************************/

void _stdcall SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count)
{
	int i;
	char ch;
	for(i=0;i<count;i++)
	{
		ch=(hex[i]&0xf0)>>4;
		dsp[i*2]=(ch>9)?ch+0x41-10:ch+0x30;
		ch=hex[i]&0x0f;
		dsp[i*2+1]=(ch>9)?ch+0x41-10:ch+0x30;
	}
}

void rotateleft(int *key)
{
	register int i,aa;

	aa=key[0];
	for (i=0;i<27;i++) key[i]=key[i+1];
	key[27]=aa;
	aa=key[28];
	for(i=28;i<55;i++)key[i]=key[i+1];
	key[55]=aa;
}

void rotateright(int *key)
{
	register int i,aa;

	aa=key[55];
	for(i=55;i>28;i--) key[i]=key[i-1];
	key[28]=aa;
	aa=key[27];
	for(i=27;i>0;i--) key[i]=key[i-1];
	key[0]=aa;
}

void fm(int func,int i,int *key,int *a,int *x)
{
	int e[48],ikey[56],y[48];
	int j,k,r;
	void transpose(int *,unsigned char *,int);
	void rotateleft(int *);
	void rotateright(int *);

	for(j=0;j<32;j++) e[j]=a[j];
	transpose(e,Etr,48);

	for(j=1;func==1 &&j<=Rots[i];j++) rotateleft(key);
	for(j=1;func==-1 && i>0 && j<=Rots[16-i];j++) rotateright(key);

	for(j=0;j<56;j++)ikey[j]=key[j];
	transpose(ikey,KeyTr2,48);

	for(j=0;j<48;j++) y[j]=(e[j]!=ikey[j])?1:0;
	for(k=0;k<8;k++){
		r=32*y[6*k]+16*y[6*k+5]+8*y[6*k+1]+4*y[6*k+2]+2*y[6*k+3]+y[6*k+4];
		x[4*k]  =((S[k][r]%16)>=8)?1:0;
		x[4*k+1]=((S[k][r]%8)>=4)?1:0;
		x[4*k+2]=((S[k][r]%4)>=2)?1:0;
		x[4*k+3]=(S[k][r]%2);
	}
	transpose(x,Ptr,32);
	return;
}

void xdes(int *plaintext,int *key,int *ciphertext,int func)
{
	int i,j;
	int a[64],x[32];
	void xchange(int *);
	void fm(int,int,int *,int *,int *);

	for(i=0;i<64;i++) a[i]=plaintext[i];
	transpose(a,InitialTr,64);
	if(func==-1) xchange(a);
	transpose(key,KeyTr1,56);
	for(i=0;i<16;i++){
		if(func==1) xchange(a);
		fm(func,i,key,a,x);
		for(j=0;j<32;j++)
			a[j+32]=(a[j+32]!=x[j])?1:0;
		if(func==-1) xchange(a);
	}
	if(func==1) xchange(a);
	transpose(a,FinalTr,64);
	for(i=0;i<64;i++)
		ciphertext[i]=a[i];
}

/****************************************************************************/
/****************************************************************************/

void _stdcall Smart_CardDes(unsigned char *AccountNum,unsigned char *SourceKey,unsigned char *PlainPin,unsigned char *CipherData,unsigned char CodeFlag)
{
	int i,j,t,plaintext[64],key[64],ciphertext[64];
	unsigned char temp,tp,result[8],account[8],pin[8];
	void xdes(int*,int*,int*,int);

	SVC_DSP_2_HEX(AccountNum,account,8);
	SVC_DSP_2_HEX(SourceKey,result,8);

	for(i=0;i<8;i++){
		t=result[i];
		key[i*8]=t/128;
		t%=128;
		key[i*8+1]=t/64;
		t%=64;
		key[i*8+2]=t/32;
		t%=32;
		key[i*8+3]=t/16;
		t%=16;
		key[i*8+4]=t/8;
		t%=8;
		key[i*8+5]=t/4;
		t%=4;
		key[i*8+6]=t/2;
		t%=2;
		key[i*8+7]=t;
	}

	if((CodeFlag=='e')||(CodeFlag=='E')){
		SVC_DSP_2_HEX(PlainPin,pin,3);
		memset(pin+3,0xff,5);

		result[0]=0x06;
		result[1]=pin[0];
		for(i=4;i<16;i++){
			if(i%2){
				temp=(pin[i/2-1]&0x0f);
				tp=account[i/2]&0xf0;
				tp>>=4;
				result[i/2]+=(temp^tp)&0x0f;
			}
			else {
				temp=(pin[i/2-1]&0xf0);
				tp=(account[i/2-1]&0x0f);
				tp<<=4;
				result[i/2]=(temp^tp)&0xf0;
			}
		}

		for(i=0;i<8;i++){
			t=result[i];
			plaintext[i*8]=t/128;
			t%=128;
			plaintext[i*8+1]=t/64;
			t%=64;
			plaintext[i*8+2]=t/32;
			t%=32;
			plaintext[i*8+3]=t/16;
			t%=16;
			plaintext[i*8+4]=t/8;
			t%=8;
			plaintext[i*8+5]=t/4;
			t%=4;
			plaintext[i*8+6]=t/2;
			t%=2;
			plaintext[i*8+7]=t;
		}

		xdes(plaintext,key,ciphertext,1);
		memset(CipherData,0,8);
		for(i=0;i<16;i++){
			temp=ciphertext[i*4]*8+ciphertext[i*4+1]*4+
			    ciphertext[i*4+2]*2+ciphertext[i*4+3];
			if(i%2) CipherData[i/2]+=temp;
			else {
				temp<<=4;
				CipherData[i/2]=temp;
			}
		}
	}
	else/* 'D' || 'd' */
	{
		for(i=0;i<8;i++){
			t=CipherData[i];
			plaintext[i*8]=t/128;
			t%=128;
			plaintext[i*8+1]=t/64;
			t%=64;
			plaintext[i*8+2]=t/32;
			t%=32;
			plaintext[i*8+3]=t/16;
			t%=16;
			plaintext[i*8+4]=t/8;
			t%=8;
			plaintext[i*8+5]=t/4;
			t%=4;
			plaintext[i*8+6]=t/2;
			t%=2;
			plaintext[i*8+7]=t;
		}

		xdes(plaintext,key,ciphertext,-1);

		for(i=0;i<8;i++)
		{
			temp=1;
			result[i] = 0;
			for(j=0;j<8;j++)
			{
				result[i]+=ciphertext[(i+1)*8-j-1]*temp;
				temp*=2;
			}
		}

		SVC_HEX_2_DSP(result+1,PlainPin,1);

		for(i=2;i<(result[0]/2+1)&&i<4;i++)
		{
			temp=((result[i]&0xf0)^((account[i-1]&0x0f)<<4));
			temp&=0xf0;
			tp=((result[i]&0x0f)^((account[i]&0xf0)>>4));
			tp&=0x0f;
			temp|=tp;

			SVC_HEX_2_DSP(&temp, PlainPin+(i-1)*2, 1);

		}
	}/* end of decode */

}

void _stdcall GenerateWorkingKey(unsigned char *Plain,unsigned char *WorkingKey)
{
	int i,t,plaintext[64],key[64],ciphertext[64];
	char ch,cs[2];
	unsigned char skey[17];

	strcpy((char*)skey,"1313131313131313");
	for(i=0;i<16;i++){
		ch=Plain[i];
		ch=(ch>='a'&&ch<='f')?(ch-0x20):ch;
		t=(ch>='A')?(ch-'A'+10):(ch-'0');
		plaintext[i*4]=t/8;
		t%=8;
		plaintext[i*4+1]=t/4;
		t%=4;
		plaintext[i*4+2]=t/2;
		t%=2;
		plaintext[i*4+3]=t;
	}
	for(i=0;i<16;i++){
		ch=skey[i];
		ch=(ch>='a'&&ch<='f')?(ch-0x20):ch;
		t=(ch>='A')?(ch-'A'+10):(ch-'0');
		key[i*4]=t/8;
		t%=8;
		key[i*4+1]=t/4;
		t%=4;
		key[i*4+2]=t/2;
		t%=2;
		key[i*4+3]=t;
	}
	xdes(plaintext,key,ciphertext,1);
	for(i=0;i<16;i++){
		t=ciphertext[i*4]*8+ciphertext[i*4+1]*4+ciphertext[i*4+2]*2
		    +ciphertext[i*4+3];
		sprintf(cs,"%X",t);
		WorkingKey[i]=cs[0];
	}
//	working_key[16]='\0';
}

/*  plain or result haves 8 bytes, skey haves 16 bytes*/
void _stdcall MAC_des(unsigned char *plain,unsigned char *skey,unsigned char *result)
{
	int i,t,plaintext[64],key[64],ciphertext[64];
	char ch,cs[2];
	unsigned char plain_temp[17],result_temp[17];

	SVC_HEX_2_DSP(plain,plain_temp,8);
	for(i=0;i<16;i++){
		ch=plain_temp[i];
		ch=(ch>='a'&&ch<='f')?(ch-0x20):ch;
		t=(ch>='A')?(ch-'A'+10):(ch-'0');
		plaintext[i*4]=t/8;
		t%=8;
		plaintext[i*4+1]=t/4;
		t%=4;
		plaintext[i*4+2]=t/2;
		t%=2;
		plaintext[i*4+3]=t;
	}
	for(i=0;i<16;i++){
		ch=skey[i];
		ch=(ch>='a'&&ch<='f')?(ch-0x20):ch;
		t=(ch>='A')?(ch-'A'+10):(ch-'0');
		key[i*4]=t/8;
		t%=8;
		key[i*4+1]=t/4;
		t%=4;
		key[i*4+2]=t/2;
		t%=2;
		key[i*4+3]=t;
	}
	xdes(plaintext,key,ciphertext,1);
	for(i=0;i<16;i++){
		t=ciphertext[i*4]*8+ciphertext[i*4+1]*4+ciphertext[i*4+2]*2
		    +ciphertext[i*4+3];
		sprintf(cs,"%X",t);
		result_temp[i]=cs[0];
	}

	result_temp[16] = 0;
	SVC_DSP_2_HEX(result_temp,result,8);
}

/*
//加密/解密函数
参数说明：
	InputData——输入的加密/解密数据。
	OutputData——加密/解密结果。
	CodeFlag——加密/解密代码，‘0’—加密，‘1’—解密。
*/
unsigned char sourcekey[17];
void Smart_UserDes(unsigned char* InputData,unsigned char* OutputData,char CodeFlag)
{
	int i,j,t,plaintext[64],key[64],ciphertext[64];
	unsigned char temp,result[8];
	void xdes(int*,int*,int*,int);
	int Len;

	//SVC_DSP_2_HEX(account_num,account,8);
	
	strcpy((char*)sourcekey,"3131313131313131");
	SVC_DSP_2_HEX(sourcekey,result,8);

	for(i=0;i<8;i++){
		t=result[i];
		key[i*8]=t/128;
		t%=128;
		key[i*8+1]=t/64;
		t%=64;
		key[i*8+2]=t/32;
		t%=32;
		key[i*8+3]=t/16;
		t%=16;
		key[i*8+4]=t/8;
		t%=8;
		key[i*8+5]=t/4;
		t%=4;
		key[i*8+6]=t/2;
		t%=2;
		key[i*8+7]=t;
	}

	if((CodeFlag=='e')||(CodeFlag=='E'))
	{
		memcpy(result,InputData,8);
		Len=strlen((char*)InputData);
		if(Len<8){
			memset(result+Len,0,8-Len);
		}

		for(i=0;i<8;i++){
			t=result[i];
			plaintext[i*8]=t/128;
			t%=128;
			plaintext[i*8+1]=t/64;
			t%=64;
			plaintext[i*8+2]=t/32;
			t%=32;
			plaintext[i*8+3]=t/16;
			t%=16;
			plaintext[i*8+4]=t/8;
			t%=8;
			plaintext[i*8+5]=t/4;
			t%=4;
			plaintext[i*8+6]=t/2;
			t%=2;
			plaintext[i*8+7]=t;
		}

		xdes(plaintext,key,ciphertext,1);

		memset(OutputData,0,8);
		for(i=0;i<16;i++){
			temp=ciphertext[i*4]*8+ciphertext[i*4+1]*4+
			    ciphertext[i*4+2]*2+ciphertext[i*4+3];
			if(i%2) OutputData[i/2]+=temp;
			else {
				temp<<=4;
				OutputData[i/2]=temp;
			}
		}
	}
	else/* 'D' || 'd' */
	{
		for(i=0;i<8;i++){
			t=InputData[i];
			plaintext[i*8]=t/128;
			t%=128;
			plaintext[i*8+1]=t/64;
			t%=64;
			plaintext[i*8+2]=t/32;
			t%=32;
			plaintext[i*8+3]=t/16;
			t%=16;
			plaintext[i*8+4]=t/8;
			t%=8;
			plaintext[i*8+5]=t/4;
			t%=4;
			plaintext[i*8+6]=t/2;
			t%=2;
			plaintext[i*8+7]=t;
		}

		xdes(plaintext,key,ciphertext,-1);

		for(i=0;i<8;i++)
		{
			temp=1;
			result[i] = 0;
			for(j=0;j<8;j++)
			{
				result[i]+=ciphertext[(i+1)*8-j-1]*temp;
				temp*=2;
			}
		}
		memcpy(OutputData,result,8);

	}/* end of decode */

}
