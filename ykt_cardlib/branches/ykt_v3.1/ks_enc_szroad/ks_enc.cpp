#include "ks_enc.h"
#include "global_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des.h"


#define INVALID_KEY_LEN  -1	//长度无效
#define INVALID_DATA_LEN  -2	//长度无效

#define SR_SECTNO 9

static char g_version[]="1.0";
static char g_enc_name[] = "7+1 szroad";

static uint8 g_mf_mainkey[8];
static uint8 g_szroad_mainkey[6];

static unsigned char statickey[17]="3230303530313331";

static ks_enc_op_t g_enc_op;

// 初始化卡时写入的控制位
static uint8 CARD_NEW_CTRL_BIT[] = {0x7F,0x07,0x88,0x00};
// 出厂时的控制位
static uint8 CARD_INIT_CTRL_BIT[] = {0xFF,0x07,0x80,0x69};   // KEYA和KEYB具有相同权限, 出厂控制位KEYB操作无效

int KSAPI get_card_param(const char *param_name,char *param_value)
{
	if(strcmp(ENC_MFSIZE,param_name)==0)
	{
		sprintf(param_value,"%d",16);
	}
	else if(strcmp(ENC_INIT_MINSECT,param_name)==0)
	{
		sprintf(param_value,"%d",SR_SECTNO);
	}
	else if(strcmp(ENC_INIT_MAXSECT,param_name)==0)
	{
		sprintf(param_value,"%d",SR_SECTNO);
	}
	else
	{
		return KS_NOTSUPPORT;
	}
	return 0;
}


static int	decrypt_work_key(const unsigned char* text,unsigned char* mtext)
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


static int KSAPI set_main_key(const uint8 *mainkey,int idx)
{
	//decrypt_work_key(mainkey,g_mf_mainkey);
	if(idx==1)
		memcpy(g_mf_mainkey,mainkey,8);
	/*
	else if(idx==2)
		memcpy(g_szroad_mainkey,mainkey,6);
	*/
	return 0;
}

static int encrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result)
{
	des_context ctx;
	if(keylen != 8)
		return INVALID_KEY_LEN;
	if(datalen != 8)
		return INVALID_DATA_LEN;
	/*
	deskey(key,0);
	Ddes(data,Des_result);
	*/
	memset(&ctx,0,sizeof ctx);
	des_set_key(&ctx,key);
	des_encrypt(&ctx,data,Des_result);
	return 0;
}
static int dencrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result)
{
	des_context ctx;
	if(keylen != 8)
		return INVALID_KEY_LEN;
	if(datalen != 8)
		return INVALID_DATA_LEN;
	memset(&ctx,0,sizeof ctx);
	des_set_key(&ctx,key);
	des_decrypt(&ctx,data,Des_result);
	return 0;
}
static int encrypt_3des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result)
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

	/*
	deskey(szkey,0);
	Ddes(szplain,szcipher);
	*/
	encrypt_des(szkey,8,szplain,8,szcipher);

	memcpy(szkey,key+8,8);
	/*
	deskey(szkey,1);
	Ddes(szcipher,szplain);
	*/
	dencrypt_des(szkey,8,szcipher,8,szplain);

	memcpy(szkey,key,8);
	/*
	deskey(szkey,0);
	Ddes(szplain,szcipher);
	*/
	encrypt_des(szkey,8,szplain,8,szcipher);

	memcpy(Des_result,szcipher,8);
	return 0;
}

static int gen_user_card_keyA(unsigned char *key,unsigned char *text,unsigned char *keyA)
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
	}

	encrypt_des(key, 8, sPlain, 8, sCipher);
	memcpy(sCipher + 8, sCipher, 8);
	startpos=(sCipher[0] + sCipher[1] + sCipher[2] + sCipher[3] + sCipher[4] + sCipher[5] + sCipher[6] + sCipher[7]) ;
	startpos%=7;      // sCipher[17]6079813C4F1A2F92, startpos = 4
	memcpy(keyA, sCipher + startpos, 6);
	return 0;
}
//////////////////////////////////////////////////////////////////////////

static int gen_user_card_keyB(unsigned char *key,unsigned char *text,unsigned char *keyB)
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

static int do_get_szroad_keya(const uint8* mainkey,const uint8 *text,uint8* key)
{
	key[0] = mainkey[0]+text[0];
	key[1] = mainkey[1]+text[1];
	key[2] = mainkey[2]|text[2];
	key[3] = mainkey[3]^text[3];
	key[4] = mainkey[4]^text[0] + 0x18;
	key[5] = mainkey[5]&text[3] + 0x40;
	return 0;
}

static int KSAPI get_key(ks_card_info_t *card,ks_mf_cardkey_t *key,KS_MF_KEYTYPE t,int sect_no)
{
	uint8 keytext[8];
	int len;
	memset(keytext,0,sizeof keytext);
	if(sect_no < 0 || sect_no > 32)
		return KS_BLOCK_OVERFLOW;
	hex2dec((char*)(card->phyid),8,keytext+4,len);
	// MF 使用的物理ID号是反过来的
	keytext[0] = keytext[7];
	keytext[1] = keytext[6];
	keytext[2] = keytext[5];
	keytext[3] = keytext[4];

	if(t == MF_KEYA)
	{
		if(sect_no!= SR_SECTNO)
			return KS_BLOCK_OVERFLOW;
		do_get_szroad_keya(g_szroad_mainkey,keytext,key->key);
		key->keytype = MF_KEYA;
	}
	else if(t == MF_KEYB || t==MF_INITKEY)
	{
		gen_user_card_keyB(g_mf_mainkey,keytext,key->key);
		key->keytype = MF_KEYB;
	}
	else if(t==MF_ORGINKEY)
	{
		memset(key->key,0xFF,sizeof(key->key));
		key->keytype = MF_KEYA;
	}
	return 0;
}
static int KSAPI get_key_by_right(ks_card_info_t *card,ks_mf_cardkey_t *key,MF_KEY_RIGHT r,int sect_no)
{
	if(r & KR_WRITEKEY)
	{
		return get_key(card,key,MF_KEYB,sect_no);
	}
	else
	{
		return get_key(card,key,MF_KEYA,sect_no);
	}
	if(r & KR_WRITE)
	{
		return get_key(card,key,MF_KEYA,sect_no);
	}
	return 0;
}
static int KSAPI get_mf_init_key(ks_card_info_t *card,ks_mf_init_cardkey_t *keys,KS_MF_KEYTYPE t,int sect_no)
{
	if(t == MF_ORGINKEY)
	{
		memset(keys->keys[0].key,0xFF,6);
		memset(keys->keys[1].key,0xFF,6);
		keys->initkey = MF_KEYA;
		memcpy(keys->ctrlbit,CARD_INIT_CTRL_BIT,4);
	}
	else
	{
		get_key(card,&(keys->keys[0]),MF_KEYA,sect_no);
		get_key(card,&(keys->keys[1]),MF_KEYB,sect_no);
		keys->initkey = MF_KEYB;
		memcpy(keys->ctrlbit,CARD_NEW_CTRL_BIT,4);
	}
	return 0;
}

int KSAPI register_enc_op(ks_enc_op_t *op)
{
	memset(g_mf_mainkey,0,sizeof g_mf_mainkey);
	memset(g_szroad_mainkey,0,sizeof g_szroad_mainkey);

	g_enc_op.version = g_version;
	g_enc_op.enc_name = g_enc_name;

	g_enc_op.get_card_param = get_card_param;
	g_enc_op.get_key = get_key;
	g_enc_op.get_key_by_right = get_key_by_right;
	g_enc_op.get_mf_init_key = get_mf_init_key;
	g_enc_op.set_main_key = set_main_key;

	//g_szroad_mainkey = {0xe5,0x66,0x3b,0x7e,0xf6,0xda};
	g_szroad_mainkey[0] = 0xe5;
	g_szroad_mainkey[1] = 0x66;
	g_szroad_mainkey[2] = 0x3b;
	g_szroad_mainkey[3] = 0x7e;
	g_szroad_mainkey[4] = 0xf6;
	g_szroad_mainkey[5] = 0xda;
	memcpy(op,&g_enc_op,sizeof(ks_enc_op_t));
	return 0;
}