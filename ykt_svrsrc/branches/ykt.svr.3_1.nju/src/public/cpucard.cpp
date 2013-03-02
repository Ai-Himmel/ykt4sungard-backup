#include "cpucard.h"
#include "gnudes.h"
#include "errdef.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pubfunc.h"

size_t cpu_str2hex(const char *str,size_t len,uint8 *hex)
{
	char temp[3];
	size_t i;
	memset(temp,0,sizeof temp);
	for(i = 0;i < len;i+=2)
	{
		memcpy(temp,str+i,2);
		hex[i/2] = (uint8)strtoul(temp,NULL,16);
	}
	return i/2;
}
size_t cpu_hex2str(const uint8 *hex,size_t len,char *str)
{
	size_t i,j;
	for(i = 0,j = 0;i < len; ++i)
		j += sprintf(str+j,"%02X",hex[i]);
	return j;
}
size_t cpu_str2bcd(const char *str,size_t len,uint8 *bcd)
{
	size_t i,j;
	for(i = 0;i < len;i+=2)
	{
		bcd[i/2] = ((str[i]-0x30)<<4) & 0xF0;
		bcd[i/2] |= (str[i+1]-0x30)&0xF0;
	}
	return len/2;
}
unsigned char* pboc_diver_key ( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] )
{
	int i;
	unsigned char tmp1[20], tmp2[20];	
	unsigned char ret1[20], ret2[20];	
	
	memset(tmp1, 0x00, sizeof tmp1 );
	memset(tmp2, 0x00, sizeof tmp2 );
	memset(ret1, 0x00, sizeof ret1 );
	memset(ret2, 0x00, sizeof ret2 );
	
	memcpy ( tmp1, cardno, 8 );
	for( i=0; i<8; i++) 
	{
		tmp2[i]=~tmp1[i];
	}
	des3_context d3ctx;
	des3_set_2keys(&d3ctx,key_in,key_in+8);
	des3_encrypt ( &d3ctx, tmp1, ret1 );
	des3_encrypt ( &d3ctx, tmp2, ret2 );
	memcpy ( key_out,   ret1, 8 );
	memcpy ( key_out+8, ret2, 8 );
	return key_out;
}

int cpu_calc_sk(const char *key,cpu_trade_t *trade)
{
	char des_data[16];
	uint8 hexkey[16],hexdata[8];
	int i;
	size_t key_len;
	des_context dctx;
	des3_context d3ctx;
	if(trade->tradecnt > 0xFFFF)
		return E_INPUT_ERROR;
	if(trade->termsno > 0xFFFF)
		return E_INPUT_ERROR;
	//writelog(LOG_INFO,"key[%s]",key);
	key_len = strlen(key);
	if(key_len != 32 && key_len != 16)
	{
		writelog(LOG_ERR,"key[%s]keylen[%d]",key,key_len);
		return E_INPUT_ERROR;
	}
	if(trade->trade_type == 0)
	{
		i = sprintf(des_data,"%s%04X8000",trade->random_key,trade->tradecnt);
	}
	else
	{
		i = sprintf(des_data,"%s%04X%04X",trade->random_key,trade->tradecnt,(0xFFFF&trade->termsno));
	}
	//writelog(LOG_ERR,"sk data[%s]",des_data);
	cpu_str2hex(des_data,i,hexdata);
	key_len = cpu_str2hex(key,key_len,hexkey);
	if(key_len == 16)
	{
		memset(&d3ctx,0,sizeof d3ctx);
		des3_set_2keys(&d3ctx,hexkey,hexkey+8);
		des3_encrypt(&d3ctx,hexdata,trade->sk);
		memset(des_data,0,sizeof des_data);
		cpu_hex2str(trade->sk,8,des_data);
	//	writelog(LOG_ERR,"des data[%s]",des_data);
	}
	else
	{
		memset(&dctx,0,sizeof dctx);
		des_set_key(&dctx,hexkey);
		des_encrypt(&dctx,hexdata,trade->sk);
	}
	return 0;
}

int cpu_calc_mac(cpu_trade_t *trade)
{
	char mac_data[64];
	uint8 hex_data[24],xor_data[8],cipher_data[8];
	char termid_bcd[10] = "";
	int i,j;
	des_context ctx;
	char termno[13]={0};
	i = 0;
	int len=strlen(trade->termno);
	if(len<=12)
	{
		//²¹Áã
		memset(termno,'0',12);
		memcpy(termno+12-len,trade->termno,len);
	}
	else
	{
		writelog(LOG_ERR,"termno[%s]",trade->termno);
		return E_INPUT_ERROR;
	}
	if(trade->trade_type == 0)
		i = sprintf(mac_data,"%08X02%s%s800000000000",trade->tradeamt,termno,trade->tx_datetime);
	else
		i = sprintf(mac_data,"%08X06%s%s800000000000",trade->tradeamt,termno,trade->tx_datetime);


//	writelog(LOG_ERR,"mac data[%s]",mac_data);
	if(i != 48)
		return E_INPUT_ERROR;
	
	memset(cipher_data,0,sizeof cipher_data);
	cpu_str2hex(mac_data,i,hex_data);
	// 3 round des encrypt
	for(j = 0;j < 3;++j)
	{
		for(i = 0;i < 8;++i)
		{
			xor_data[i] = cipher_data[i] ^ hex_data[j*8+i];
		}
		memset(&ctx,0,sizeof ctx);
		des_set_key(&ctx,trade->sk);
		des_encrypt(&ctx,xor_data,cipher_data);
	}	
	cpu_hex2str(cipher_data,4,trade->mac2);
//	writelog(LOG_DEBUG,"mac[%s]",trade->mac2);
	return 0;
}

int cpu_calc_mac1(cpu_trade_t *trade)
{
	return 0;
}

