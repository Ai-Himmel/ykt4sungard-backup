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
#include "..\include\pubfunc.h"
#include "rijndael-api-fst.h"
#include "md5.h"
#include <time.h>

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


typedef unsigned short uint16;

static const unsigned int  crc16_tab[256] = { 
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 
		0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef, 
		0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6, 
		0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de, 
		0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 
		0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 
		0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 
		0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 
		0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823, 
		0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b, 
		0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12, 
		0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a, 
		0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41, 
		0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 
		0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 
		0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 
		0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 
		0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067, 
		0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e, 
		0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256, 
		0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d, 
		0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 
		0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 
		0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 
		0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 
		0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 
		0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 
		0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92, 
		0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 
		0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1, 
		0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8, 
		0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 
};

static uint16  GenerateCRC16(const unsigned char *pBuf, uint16 len)
{
	uint16 crc; 
	unsigned char b, da;
	uint16 charcnt;

	crc = 0; 
	charcnt = 0;
	while (len--)
	{
		da = (unsigned char)(crc / 256); /* 以8位二进制数的形式暂存CRC的高8位 */ 
		crc <<= 8;						 /* 左移8位，相当于CRC的低8位乘以 */ 
		b = pBuf[charcnt];				 // 新移进来的字节值
		crc ^= crc16_tab[da ^ b];		 /* 高8位和当前字节相加后再查表求CRC ，再加上以前的CRC */ 
		charcnt++; 
	}
	return crc;
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

int __stdcall encrypt_work_key_asc(char src_text[17], char des_text[17])
{
	unsigned char text[9] = "";
	unsigned char mtext[9] = "";
	hex2dec(src_text, text, 8);
	encrypt_work_key(text, mtext);
	dec2hex(mtext, 8, des_text);
	
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
	startpos=(sCipher[0] + sCipher[1] + sCipher[2] + sCipher[3] + sCipher[4] + sCipher[5] + sCipher[6] + sCipher[7]) ;
	startpos%=7;      // sCipher[17]6079813C4F1A2F92, startpos = 4
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


void __stdcall CalcMD5(void * buf,unsigned int len,unsigned char md5[16])
{
	MD5_CTX ctx;
	memset(&ctx,0,sizeof ctx);
	MD5Init(&ctx);
	MD5Update(&ctx,(unsigned char*)buf,len);
	MD5Final(md5,&ctx);
}


int __stdcall encrypt_elec_card_pwd(int cut_id,const char seedkey[32],const char pwd[8],char mpwd[64])
{
	static const int max_pwd_len = 8;
	keyInstance key_inst;
	cipherInstance cipher_inst;
	unsigned char buf[16] = "";
	char temp[16] = "";
	char temp2[16] = "";
	char pwd_str[max_pwd_len*2+1] = "";
	unsigned char decrypt_buf[16] = "";
	char encrypt_seedkey[64] = "";
	unsigned char decrypt_str[64] = "";
	time_t radom_seed = time(NULL);
	int len,i,j,pwd_len;
	memset(&key_inst,0,sizeof key_inst);
	memset(&cipher_inst,0,sizeof cipher_inst);
	
	for(i = 0;i < max_pwd_len;++i)
	{
		switch(pwd[i])
		{
		case ' ':
		case '\t':
		case '\r':
		case '\n':
		case '\'':
		case '"':
		case '%':
		case '_':
			return -2;
		default:
			break;
		}
	}
	pwd_len = strlen(pwd);
	if(pwd_len > max_pwd_len)
		return -3;
	// 取4位随机种子
	srand((unsigned int)radom_seed);
	for(i = 0;i < 4;++i)
		buf[i] = (unsigned char)(rand() % 0xFF);

	// 密码不足8位右补空格
	memcpy(pwd_str,pwd,pwd_len);
	for(i=pwd_len;i < max_pwd_len;++i)
		pwd_str[pwd_len] = ' ';
	for(i=0;i < max_pwd_len;++i)
		pwd_str[i] ^= buf[i%4];

	// 加密的密钥
	for(i = 0;i < max_pwd_len;++i)
		pwd_str[max_pwd_len+i] = pwd_str[i] | (!temp[i]);
	memcpy(pwd_str+max_pwd_len,pwd_str,max_pwd_len);

	
	// 计算种子密钥
	memset(encrypt_seedkey,0,sizeof encrypt_seedkey);
	for(i = 0; i < 32 ;++i)
		encrypt_seedkey[i] = seedkey[i] ^ buf[i%4];
	CalcMD5((unsigned char*)encrypt_seedkey,32,(unsigned char*)temp);
	memset(encrypt_seedkey,0,sizeof encrypt_seedkey);
	for(i = 0,j = 0;i < 16; ++i)
		j += sprintf(encrypt_seedkey+j,"%02X",(unsigned char)temp[i]);


	// 计算CRC
	sprintf(temp,"%08X",cut_id);
	memset(temp2,0,sizeof temp2);
	for(i = 0;i < max_pwd_len;++i)
		temp2[i] = pwd_str[i] ^ temp[i];
	uint16 crc = GenerateCRC16((unsigned char *)temp2,max_pwd_len);
	sprintf(temp,"%04X",crc);
	memcpy(buf+4,temp,4);
	
	

	// 进行加密
	if(makeKey(&key_inst,DIR_ENCRYPT,128,encrypt_seedkey)==FALSE)
	{
		return -1;
	}
	if(cipherInit(&cipher_inst,MODE_CBC,NULL)==FALSE)
	{
		return -1;
	}
	len = blockEncrypt(&cipher_inst,&key_inst,(unsigned char*)pwd_str,16*8,decrypt_str);
	if(len == 16*8)
	{
		// 8 个字符种子
		for(i = 0;i < 4; ++i)
			sprintf(mpwd+i*2,"%02X",(unsigned char)buf[i]);
		// 4 个字符CRC
		memcpy(mpwd+8,temp,4);
		// 8 个字符密码
		for(i = 0;i < 16;++i)
			sprintf(mpwd+12+i*2,"%02X",decrypt_str[i]);
		//mpwd[28] = '\0';
		return 0;
	}
	return -1;
}
int __stdcall decrypt_elec_card_pwd(int cut_id,const char seedkey[32],const char mpwd[64],char pwd[8])
{
	char temp[17],temp1[17],buf[17];
	char encrypt_seed[65];
	unsigned char radom_seed[4];
	keyInstance key_inst;
	cipherInstance cipher_inst;
	int i,len;
	static const int max_pwd_len = 8;

	memset(&key_inst,0,sizeof key_inst);
	memset(&cipher_inst,0,sizeof cipher_inst);


	// 读取随机种子
	memcpy(temp,mpwd,8);
	memset(temp1,0,sizeof temp1);
	for(i = 0;i < 8;i+=2)
	{
		memcpy(temp1,temp+i,2);
		radom_seed[i/2] = (unsigned char)strtoul(temp1,NULL,16);
	}

	// 计算种子密钥
	memset(encrypt_seed,0,sizeof encrypt_seed);
	for(i = 0;i < 32;++i)
		encrypt_seed[i] = seedkey[i] ^ radom_seed[i%4];
	CalcMD5((unsigned char*)encrypt_seed,32,(unsigned char*)temp);
	memset(encrypt_seed,0,sizeof encrypt_seed);
	for(i = 0; i < 16 ;++i)
		sprintf(encrypt_seed+i*2,"%02X",(unsigned char)temp[i]);


	// 解密
	if(makeKey(&key_inst,DIR_DECRYPT,128,(char*)encrypt_seed)==FALSE)
	{
		return -1;
	}
	if(cipherInit(&cipher_inst,MODE_CBC,NULL)==FALSE)
	{
		return -1;
	}

	memset(temp1,0,sizeof temp1);
	memset(temp,0,sizeof temp);
	for(i = 0;i < 32; i+=2)
	{
		memcpy(temp1,mpwd+12+i,2);
		temp[i/2] = (unsigned char)strtoul(temp1,NULL,16);
	}
	memset(temp1,0,sizeof temp1);
	len = blockDecrypt(&cipher_inst,&key_inst,(BYTE*)temp,16*8,(BYTE*)temp1);

	for(i=0;i < max_pwd_len;++i)
		buf[i] = temp1[i] ^ radom_seed[i%4];
	

	// 计算密码
	sprintf(temp,"%08X",cut_id);
	for(i = 0;i < max_pwd_len;++i)
		temp1[i] = temp1[i] ^ temp[i];
	// CRC 校验
	uint16 crc = GenerateCRC16((unsigned char*)temp1,max_pwd_len);
	memset(temp,0,sizeof temp);
	sprintf(temp,"%04X",crc);
	if(strncmp(temp,mpwd+8,4))
	{
		return -2;
	}
	memcpy(pwd,buf,max_pwd_len);
	//memcpy(pwd,temp1,max_pwd_len);
	
	return 0;
}

int __stdcall calc_oper_pwd(const char *oper_code,const char *pwd,char *text)
{
	unsigned char key[8];
	unsigned char plaintext[8];
	unsigned char ciphertext[8];
	int i,j;
	if(strlen(oper_code) > 8)
		return -1;
	if(strlen(pwd) > 8)
		return -2;
	memset(key,0,sizeof key);
	memcpy(key,oper_code,strlen(oper_code));
	memset(plaintext,0,sizeof plaintext);
	memcpy(plaintext,pwd,strlen(pwd));
	encrypt_des(key,8,plaintext,8,ciphertext);
	for(i =0,j=0;i < 8;++i)
		j += sprintf(text+j,"%02X",ciphertext[i]);
	return 0;
}
