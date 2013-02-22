// desdll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "desdll.h"
#include "d3des.h"
#include "comm.h"
#include "des.h"

#define INVALID_KEY_LEN  -1	//长度无效
#define INVALID_DATA_LEN  -2	//长度无效
#pragma warning( disable : 4244 )
static unsigned char statickey[17]="3230303530313331";
static unsigned char workkey[17]="FAB18DF02EFCCDDA";
BOOL APIENTRY DllMain( HANDLE hModule, 
					   DWORD  ul_reason_for_call, 
					   LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

static unsigned char add_2(unsigned char add1, unsigned char add2)
{
	unsigned char ad1, ad2, sum;
	ad1 = add1;
	ad2 = add2;
	sum = (ad1 + ad2) % 0x100;
	return sum;
}

static void dess_ming(unsigned char key[4],unsigned char Source[4],unsigned char dest[4])
{
	unsigned char x0, x1, x2, x3, y0, y1, y2, y3, m, n, add1, add2;
	x0 = key[0];
	x1 = key[1];
	x2 = key[2];
	x3 = key[3];
	y0 = Source[0];
	y1 = Source[1];
	y2 = Source[2];
	y3 = Source[3];
	m = x0 ^ x1;
	add1 = m;
	add2 = y2;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x1;
	n = add_2(add1, add2);
	add1 = n;
	add2 = y3;
	n = add_2(add1, add2);
	m = m ^ y0;
	n = n ^ y1;
	y0 = m;
	y1 = n;
	add1 = m;
	add2 = x1 ^ x2;
	m = add_2(add1, add2);
	add1 = x1;
	add2 = x2;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y2;
	n = n ^ y3;
	y2 = m;
	y3 = n;
	add1 = y1;
	add2 = x2 ^ x3;
	m = add_2(add1, add2);
	add1 = x2;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = y0;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = m;
	add2 = x0 ^ x3;
	m = add_2(add1, add2); 
	add1 = x0;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	add1 = y3;
	add2 = x0 ^ x3;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = y2;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	add1 = m;
	add2 = x2 ^ x3;
	m = add_2(add1, add2);
	add1 = x2;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = y1;
	add2 = x1 ^ x2;
	m = add_2(add1, add2);
	add1 = x1;
	add2 = x2;
	add1 = add_2(add1, add2);
	add2 = y0;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = m;
	add2 = x0 ^ x1;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x1;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	dest[0] = y0;
	dest[1]= y1;
	dest[2] = y2;
	dest[3] = y3;
}

int	__stdcall encrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result)
{
	if(keylen != 8)
		return INVALID_KEY_LEN;
	if(datalen != 8)
		return INVALID_DATA_LEN;
	deskey(key,0);
	Ddes(data,Des_result);
	return 0;
}

int	__stdcall dencrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result)
{
	if(keylen != 8)
		return INVALID_KEY_LEN;
	if(datalen != 8)
		return INVALID_DATA_LEN;
	deskey(key,1);
	Ddes(data,Des_result);
	return 0;
}

int	__stdcall encrypt_3des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result)
{
	unsigned char szkey[9];
	unsigned char szplain[9];
	unsigned char szcipher[9];
	if(keylen != 16)
		return INVALID_KEY_LEN;
	if(datalen != 8)
		return INVALID_DATA_LEN;

	memset(szkey,0,sizeof(szkey));
	memset(szplain,0,sizeof(szplain));
	memset(szcipher,0,sizeof(szcipher));

	memcpy(szkey,key,8);
	memcpy(szplain,data,8);

	deskey(szkey,0);
	Ddes(szplain,szcipher);

	memcpy(szkey,key+8,8);
	deskey(szkey,1);
	Ddes(szcipher,szplain);

	memcpy(szkey,key,8);
	deskey(szkey,0);
	Ddes(szplain,szcipher);

	memcpy(Des_result,szcipher,8);
	return 0;
}

int	__stdcall dencrypt_3des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result)
{
	unsigned char szkey[9];
	unsigned char szplain[9];
	unsigned char szcipher[9];
	if(keylen != 16)
		return INVALID_KEY_LEN;
	if(datalen != 8)
		return INVALID_DATA_LEN;

	memset(szkey,0,sizeof(szkey));
	memset(szplain,0,sizeof(szplain));
	memset(szcipher,0,sizeof(szcipher));

	memcpy(szkey,key,8);
	memcpy(szcipher,data,8);

	deskey(szkey,1);
	Ddes(szcipher,szplain);

	memcpy(szkey,key+8,8);
	deskey(szkey,0);
	Ddes(szplain,szcipher);

	memcpy(szkey,key,8);
	deskey(szkey,1);
	Ddes(szcipher,szplain);

	memcpy(Des_result,szplain,8);
	return 0;
}
//参数：buf1~buf3,字符串指针，原始字符串地址，长度8位
//key，密钥明文的地址
//返回值：0，成功；其它失败
int	__stdcall gen_work_key(unsigned char* buf1,unsigned char* buf2,unsigned char*buf3,unsigned char* key)
{
	unsigned int  i;
	unsigned long ul;
	char temp[3];
	unsigned char szKey[9];
	unsigned char statkey[9];

	memset(temp,0,sizeof(temp));
	memset(statkey,0,sizeof(statkey));
	memset(szKey,0,sizeof(szKey));

	for(i=0;i<8;i++)
	{
		szKey[i]=buf1[i]^buf2[i]^buf3[i];
		szKey[i]=~szKey[i];
	}
	for(i=0;i<8;i++)
	{
		memcpy(temp,&workkey[2*i],2);
		ul=strtoul(temp,NULL,16);
		statkey[i]=ul;
	}
	encrypt_des(statkey,8,szKey,8,key);
	return 0;
}

int	__stdcall encrypt_work_key(unsigned char* text,unsigned char* mtext)
{
	unsigned int  i;
	unsigned long ul;
	char temp[3];
	unsigned char plain[9];
	unsigned char statkey[9];

	memset(temp,0,sizeof(temp));
	memset(plain,0,sizeof(plain));
	memset(statkey,0,sizeof(statkey));
	memcpy(plain,text,8);
	for(i=0;i<8;i++)
	{
		memcpy(temp,&statickey[2*i],2);
		ul=strtoul(temp,NULL,16);
		statkey[i]=ul;
		plain[i]=~plain[i];
		mtext[i]=plain[i]^statkey[i];
	}
	return 0;
}

int	__stdcall decrypt_work_key(unsigned char* text,unsigned char* mtext)
{
	unsigned int  i;
	unsigned long ul;
	char temp[3];
	unsigned char statkey[9];

	memset(temp,0,sizeof(temp));
	memset(statkey,0,sizeof(statkey));
	for(i=0;i<8;i++)
	{
		memcpy(temp,&statickey[2*i],2);
		ul=strtoul(temp,NULL,16);
		statkey[i]=ul;
		mtext[i]=text[i]^statkey[i];
		mtext[i]=~mtext[i];
	}
	return 0;
}

int	__stdcall get_check_char(unsigned char buf[16])
{
	int i=0;
	unsigned int sum=0;
	unsigned int check_char=0;
	int check[16]={7,9,10,5, 8,4,2,1, 6,3,7,9, 10,5,8,2};
	for(i=0;i<16;i++)
		sum+=(buf[i]*check[i]);
	check_char=sum%255;
	return check_char;
}

// 检查校验位是否合法，返回值为0为合法，为-1非法。
//buf内容为上述1-5共16个字节连接成的字符串.checkchar为校验位字符
int	__stdcall check_valid(unsigned char buf[16],unsigned char check_char)
{
	int i=0;
	unsigned int sum=0;
	unsigned int key=0;
	int check[16]={7,9,10,5, 8,4,2,1, 6,3,7,9, 10,5,8,2};
	for(i=0;i<16;i++)
		sum+=(buf[i]*check[i]);
	key=sum%255;
	if(key==check_char)
		return 0;
	else
		return -1;
}

int __stdcall gen_extra_keyA(unsigned char* key,unsigned char* text,unsigned char* keyA)
{
	unsigned int i;
	unsigned char sPlain[9];
	for(i = 0;i < 4;++i)
	{
		sPlain[i] = text[i];
		sPlain[i+4] = ~text[i];
	}
	dess_ming(key,text,keyA);
	dess_ming(key,text+4,keyA+4);
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
int	__stdcall gen_user_card_keyA(unsigned char *key,unsigned char *text,unsigned char *keyA)
{
	// gen_user_card_keyA算出来的keyA和des_code算出来的ucDesData是一样的东西
	unsigned int i;
/*	unsigned int j;*/
	unsigned char sPlain[9];	
	unsigned char sCipher[17]; 
	unsigned int  startpos = 0;
	unsigned char ucRawData[256];
 	unsigned char ucDesData[256] = "";
	unsigned char ucdata[17];
	int iTemp = 0;
	memset(sPlain, 0, sizeof(sPlain));	
	memset(sCipher, 0, sizeof(sCipher));
	memset(ucDesData, 0, sizeof(ucDesData));
	memset(ucdata, 0, sizeof(ucdata));
	memset(ucRawData, 0, sizeof(ucRawData));
	memset(ucDesData, 0, sizeof(ucDesData));
	memcpy(ucRawData, text, 4);
	for(i = 0; i < 4; i++)
	{
		sPlain[i] = text[i];
		sPlain[i+4] = ~text[i];
/*		ucRawData[i + 4] = ~ucRawData[i];*/
	}
	//////////////////////////////////////////////////////////////////////////
//	des_code(key, ucRawData, ucDesData, '0');
	//////////////////////////////////////////////////////////////////////////
// 	memcpy(ucdata, ucDesData, 8);
// 	memcpy(ucdata + 8, ucDesData, 8);
// 	for (i = 0; i < 8; i++)
// 	{
// 		iTemp += ucdata[i] * i;
// 	}
// 	i = iTemp % 10;
// 	memcpy(keyA, ucdata + i, 6);
	encrypt_des(key, 8, sPlain, 8, sCipher);
	memcpy(sCipher + 8, sCipher, 8);
	startpos=(sCipher[0] + sCipher[1] + sCipher[2] + sCipher[3] + sCipher[4] + sCipher[5] + sCipher[6] + sCipher[7]) % 7;      // sCipher[17]6079813C4F1A2F92, startpos = 4
	memcpy(keyA, sCipher + startpos, 6);
	//	memcpy(ucDesData, sCipher+startpos, 6);
	//////////////////////////////////////////////////////////////////////////
	// 加入偏移的算法
	//////////////////////////////////////////////////////////////////////////
//	memcpy(ucDesData, sCipher, 16);
// 	memcpy(ucdata, sCipher, 8);

// 	memcpy(ucdata + 8, sCipher, 8);
// 	for (j = 0; j < 8; j++)
// 	{
// 		iTemp += sCipher[j] * j;
// 	}
// 	j = iTemp % 10;
// 	memcpy(keyA, ucdata + j, 6);
	return 0;
}
//////////////////////////////////////////////////////////////////////////

int	__stdcall gen_user_card_keyB(unsigned char *key,unsigned char *text,unsigned char *keyB)
{
	unsigned int  i;
	unsigned char sPlain[9];
	unsigned char sCipher[17];
	unsigned int  startpos=0;
	unsigned char sKey[17];

	memset(sPlain,0,sizeof(sPlain));
	memset(sCipher,0,sizeof(sCipher));
	memset(sKey,0,sizeof(sKey));
	for(i=0;i<4;i++)
	{
		sPlain[i]=~text[i];
		sPlain[i+4]=text[i];
	}
	for(i=0;i<8;i++)
	{
		sKey[i]=key[i];
		sKey[i+8]=~key[i];
	}
	encrypt_3des(sKey,16,sPlain,8,sCipher);
	memcpy(sCipher+8,sCipher,8);
	startpos=(sCipher[0]+sCipher[1]+sCipher[2]+sCipher[3]+sCipher[4]+sCipher[5]+sCipher[6]+sCipher[7])%7;
	memcpy(keyB,sCipher+startpos,6);
	return 0;
}

int	__stdcall gen_auth_card_keyA(unsigned char *text,unsigned char *keyA)
{
	unsigned int  i=0;
	unsigned long ul;
	char temp[3]="";
	unsigned char statkey[9]="";

	memset(temp,0,sizeof(temp));
	memset(statkey,0,sizeof(statkey));
	for(i=0;i<8;i++)
	{
		memcpy(temp,&workkey[2*i],2);
		ul=strtoul(temp,NULL,16);
		statkey[i]=ul;
	}
	encrypt_des(statkey,8,text,8,keyA);
	return 0;
}

int	__stdcall gen_auth_card_keyB(unsigned char *text,unsigned char *keyB)
{
	unsigned int  i=0;
	unsigned long ul;
	char temp[3]="";
	unsigned char statkey[17]="";

	memset(temp,0,sizeof(temp));
	memset(statkey,0,sizeof(statkey));
	for(i=0;i<8;i++)
	{
		memcpy(temp,&workkey[2*i],2);
		ul=strtoul(temp,NULL,16);
		statkey[i]=ul;
		statkey[i+8]=~statkey[i];
	}
	encrypt_3des(statkey,16,text,8,keyB);
	return 0;
}

int __stdcall gen_auth_card_ksykt(unsigned char *src_key, unsigned char *text, unsigned char *des_key)
{
	unsigned char tdes_key[17] = "";
	unsigned char tdes_src[17] = "";
	unsigned char data[9] = "";
	short key_pos = 0;

	for (int i = 0; i < 16; i++)
	{
		tdes_src[i] ^= src_key[i % 4];
		tdes_src[i + 1] += tdes_src[i];
	}

	for (int j = 0; j < 8; j++)
	{
		data[j] += (tdes_src[j] ^ (~*text));
	}
	
	dencrypt_3des(src_key, 16, data, 8, tdes_key);
	memcpy(tdes_key + 8, src_key, 8);

	key_pos = *text;

	if (key_pos>= 0 && key_pos <= 7)
	{
		des_key[key_pos] = tdes_key[key_pos];
		for (int m = 1; m <= 6; m++)
		{
			des_key[(key_pos + m) % 6] += (tdes_key[key_pos + m - 1] ^ tdes_key[key_pos + m] ^ key_pos);
		}
	}
	else if (key_pos >= 8 && key_pos <= 15)
	{

	}
	else if (key_pos >= 16 && key_pos <= 23)
	{
		des_key[0] = key_pos;
		des_key[1] = key_pos % 6;
		memcpy(des_key + 2, src_key, 4);
	}
	else 
	{

	}

	return 0;
}

void cal_des(unsigned char *key, unsigned char *text, unsigned char *mtext)
{
	DES(key, text, mtext);
}

void cal_dedes(unsigned char *key, unsigned char *text, unsigned char *mtext)
{
	_DES(key, text, mtext);
}