#include "cpucard.h"
#include "gnudes.h"
#include "errdef.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

size_t cpu_str2hex(const char *str,size_t len,byte *hex)
{
	char temp[3];
	size_t i;
	memset(temp,0,sizeof temp);
	for(i = 0;i < len;i+=2)
	{
		memcpy(temp,str+i,2);
		hex[i/2] = (byte)strtoul(temp,NULL,16);
	}
	return i/2;
}
size_t cpu_hex2str(const byte *hex,size_t len,char *str)
{
	size_t i,j;
	for(i = 0,j = 0;i < len; ++i)
		j += sprintf(str+j,"%02X",hex[i]);
	return j;
}

int cpu_calc_sk(const char *key,cpu_trade_t *trade)
{
	char des_data[16];
	byte hexkey[16],hexdata[8];
	int i;
	size_t key_len;
	des_context dctx;
	des3_context d3ctx;
	if(trade->tradecnt > 0xFFFF)
		return E_INPUT_ERROR;
	if(trade->termsno > 0xFFFF)
		return E_INPUT_ERROR;

	key_len = strlen(key);
	if(key_len != 32 && key_len != 16)
		return E_INPUT_ERROR;

	if(trade->trade_type == 0)
	{
		i = sprintf(des_data,"%08X%04X8000",trade->random_key,trade->tradecnt);
	}
	else
	{
		i = sprintf(des_data,"%08X%04X%04X",
					trade->random_key,trade->tradecnt,(0xFFFF&trade->termsno));
	}
	
	cpu_str2hex(des_data,i,hexdata);
	key_len = cpu_str2hex(key,key_len,hexkey);
	if(key_len == 16)
	{
		memset(&d3ctx,0,sizeof d3ctx);
		des3_set_2keys(&d3ctx,hexkey,hexkey+8);
		des3_encrypt(&d3ctx,hexdata,trade->sk);
	}
	else
	{
		memset(&dctx,0,sizeof dctx);
		des_set_key(&dctx,hexkey);
		des_encrypt(&dctx,hexdata,trade->sk);
	}
	return 0;
}

int cpu_calc_mac2(cpu_trade_t *trade)
{
	char mac_data[64];
	byte hex_data[24],xor_data[8],cipher_data[8];
	int i,j;
	des_context ctx;

	i = 0;
	if(trade->trade_type == 0)
		i = sprintf(mac_data,"%08X02%12X%s800000000000",trade->tradeamt,trade->termid,trade->tx_datetime);
	else
		i = sprintf(mac_data,"%08X06%12X%s800000000000",trade->tradeamt,trade->termid,trade->tx_datetime);

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
	memcpy(trade->mac2,cipher_data,8);
	return 0;
}

int cpu_calc_mac1(cpu_trade_t *trade)
{
	return 0;
}

