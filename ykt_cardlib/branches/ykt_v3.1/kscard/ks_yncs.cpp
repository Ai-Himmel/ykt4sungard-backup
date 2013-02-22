#include "kscard.h"
#include "global.h"
#include "YCTReaderInterface.h"
#include "YCT_LibReader.h"
#include <vector>
#include <string>
#include <windows.h>
#include "mystring.h"
#include "des.h"
#include "yktclt.h"
#include "logfile.h"
#include "global_func.h"
#include "interface.h"
#include "ksdevice.h"

#define MAX_WATER_PACK_MONEY 200000
static void set_3byte_money(unsigned char *buffer,int money)
{
	buffer[0] = money & 0xFF;
	buffer[1] = (money / 256) % 256;
	buffer[2] = (money / 256 / 256) % 256;
}
static int get_3byte_money(unsigned char *buffer)
{
	int t;
	t = buffer[0] + buffer[1] * 256 + buffer[2] * 256 * 256;
	return t;
}
static void set_4byte_money(unsigned char *buffer,int money)
{
	buffer[0] = money & 0xFF;
	buffer[1] = (money / 256) % 256;
	buffer[2] = (money / 256 / 256) % 256;
	buffer[4] = (money/256/256/256) % 256;
}
static int get_4byte_money(unsigned char *buffer)
{
	int t;
	t = buffer[0] + buffer[1] * 256 + buffer[2] * 256 * 256 + buffer[3] * 256 * 256 * 256;
	return t;
}
static int hd_water_login_fix(ks_water_pack_t *pack)
{
	int sectno,ret,blockno;
	char param_value[256] = "";
	ks_mf_cardkey_t card_key;
	ks_mf_init_cardkey_t init_key;
	unsigned char buffer[16];
	char phyid[9];
	if(g_enc_op.get_card_param("yncs_hd_sect",param_value))
		return KS_NOPARAMFOUND;
	sectno = atoi(param_value);

	ret = ks_mf_login_card(sectno);
	if(ret)
	{
		if(ks_mf_card(phyid))
			return KS_REQUESTCARD;
		g_enc_op.get_key(&g_cardinfo,&card_key,MF_KEYB,sectno);
		if(g_dev_op.login_card(&g_reader,&g_cardinfo,sectno,MF_KEYB,card_key.key)!=0)
		{
			DEBUG_LOG(("扇区[%d]keyb登陆失败",sectno));
			return KS_LOGINCARD;
		}
		g_enc_op.get_mf_init_key(&g_cardinfo,&init_key,MF_INITKEY,sectno);
		memcpy(buffer,init_key.keys[MF_KEYA].key,6);
		memcpy(buffer+6,init_key.ctrlbit,4);
		memcpy(buffer+10,init_key.keys[MF_KEYB].key,6);
		blockno = sectno * 4;
		if(g_dev_op.write_block(&g_reader,&g_cardinfo,blockno+3,buffer)!=0)
		{
			DEBUG_LOG(("扇区[%d]写密钥失败",sectno));
			return KS_WRITECARD;
		}
		return 0;
	}
	return 0;
}
static int hd_water_readmoney(ks_water_pack_t *pack)
{
	int sectno,ret,blockno;
	unsigned char buffer[16],buffer2[16];
	char param_value[256] = "";
	
	if(g_enc_op.get_card_param("yncs_hd_sect",param_value))
		return KS_NOPARAMFOUND;
	sectno = atoi(param_value);

#if 1
	ret = ks_mf_login_card(sectno);
#else
	if(!ks_checkloadkeys())
	{
		ks_setlasterr("密钥未装载",-1);
		return KS_NOTAUTH;
	}
	ret = hd_water_login_fix(pack);
#endif

	if(ret)
		return ret;

	blockno = sectno * 4;

	memset(buffer,0xFF,sizeof buffer);
	if(g_dev_op.read_block(&g_reader,&g_cardinfo,blockno,buffer))
	{
		return KS_READCARD;
	}
	if(check_buffer_xor(buffer,15,buffer[15]))
	{
		if(g_dev_op.read_block(&g_reader,&g_cardinfo,blockno+1,buffer))
		{
			return KS_READCARD;
		}
		if(check_buffer_xor(buffer,15,buffer[15]))
		{
			return KS_PURSEERROR;
		}
	}
	if(g_dev_op.read_block(&g_reader,&g_cardinfo,blockno+2,buffer2))
	{
		return KS_READCARD;
	}
	if(check_buffer_xor(buffer2,15,buffer2[15]))
	{
		return KS_PURSEERROR;
	}
	pack->money = get_3byte_int(buffer);
	pack->totalmoney = get_4byte_int(buffer+3);
	pack->price1 = get_2byte_int(buffer+7);
	pack->price2 = get_2byte_int(buffer+9);
	pack->price3 = get_2byte_int(buffer+11);
	pack->addcount = get_2byte_int(buffer+13);
	
	pack->custno = get_3byte_int(buffer2);
	pack->cardtype = buffer2[3];
	pack->expireddate[0] = '2';
	pack->expireddate[1] = '0';
	bcd2asc(buffer2+4,3,pack->expireddate+2);
	pack->lockflag = buffer2[7];
	return 0;
}
static int hd_water_writemoney(ks_water_pack_t *pack)
{
	int sectno,ret,blockno,offset;
	unsigned char buffer[16],buffer2[16];
	char param_value[256] = "";
	

	if(g_enc_op.get_card_param("yncs_hd_sect",param_value))
		return KS_NOPARAMFOUND;
	sectno = atoi(param_value);
#if 1
	ret = ks_mf_login_card(sectno);
#else
	if(!ks_checkloadkeys())
	{
		ks_setlasterr("密钥未装载",-1);
		return KS_NOTAUTH;
	}
	ret = hd_water_login_fix(pack);
#endif
	if(ret)
		return ret;

	blockno = sectno * 4;

	memset(buffer,0xFF,sizeof buffer);
	offset = 0;
	set_3byte_int(buffer,pack->money);
	offset+=3;
	set_4byte_int(buffer+offset,pack->totalmoney);
	offset+=4;
	set_2byte_int(buffer+offset,pack->price1);
	offset+=2;
	set_2byte_int(buffer+offset,pack->price2);
	offset+=2;
	set_2byte_int(buffer+offset,pack->price3);
	offset+=2;
	set_2byte_int(buffer+offset,pack->addcount);
	buffer[15] = calc_xor(buffer,15);

	ret = g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer);
	if(!g_dev_op.read_block(&g_reader,&g_cardinfo,blockno,buffer2))
	{
		if(memcmp(buffer,buffer2,16)!=0)
			return KS_WRITECARD;
	}
	else
		return KS_UNCONFIRM;

	memset(buffer,0xFF,sizeof buffer);
	offset = 0;
	set_3byte_int(buffer,pack->cardno);
	offset+=3;
	buffer[offset]=(unsigned char)pack->cardtype;
	offset++;
	asc2bcd(pack->expireddate+2,6,buffer+offset,ret);
	offset+=3;
	buffer[offset] = pack->lockflag;
	buffer[15] = calc_xor(buffer,15);
	ret = g_dev_op.write_block(&g_reader,&g_cardinfo,blockno+2,buffer);
	if(!g_dev_op.read_block(&g_reader,&g_cardinfo,blockno+2,buffer2))
	{
		if(memcmp(buffer,buffer2,16)!=0)
			return KS_WRITECARD;
	}
	else
		return KS_UNCONFIRM;
	return 0;
}

static int hd_water_publishcard(ks_water_pack_t *pack)
{	
	return hd_water_writemoney(pack);
}
static int hd_water_recyclecard()
{
	int sectno,ret,blockno;
	unsigned char buffer[16];
	char param_value[256] = "";
	if(g_enc_op.get_card_param("yncs_hd_sect",param_value))
		return KS_NOPARAMFOUND;
	sectno = atoi(param_value);

	ret = ks_mf_login_card(sectno);
	if(ret)
		return ret;

	blockno = sectno * 4;
	memset(buffer,0,sizeof buffer);
	if(g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer))
	{
		return KS_WRITECARD;
	}
	if(g_dev_op.write_block(&g_reader,&g_cardinfo,blockno+1,buffer))
	{
		return KS_WRITECARD;
	}
	if(g_dev_op.write_block(&g_reader,&g_cardinfo,blockno+2,buffer))
	{
		return KS_WRITECARD;
	}
	return 0;
}
static int hd_water_publishparamcard(ks_water_param_t *param)
{
	int ret,block_no,len,offset,sect,watersect;
	unsigned char param_key_a[] = {0x23,0x55,0x33,0x78,0x12,0xAB};
	unsigned char param_key_b[] = {0x34,0x22,0x35,0x23,0x45,0x34};
	unsigned char param_init_key[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	unsigned char seed_key[8];
	unsigned char new_ctrl_bit[] = {0x7F,0x07,0x88,0x00};
	char param_value[128];
	unsigned char buffer[16];
	char phyid[9];

	// 获取汇多参数卡的参数信息
	// param card keya
	if(g_enc_op.get_card_param("yncs_hd_paramcardkey",param_value)!=0)
	{
		DEBUG_LOG(("未设置汇多参数卡密钥参数"));
		return KS_NOPARAMFOUND;
	}
	hex2dec(param_value,12,param_key_a,len);
	// param card keyb
	if(g_enc_op.get_card_param("yncs_waterparamcardkeyb",param_value)!=0)
	{
		DEBUG_LOG(("未设置汇多参数卡密钥参数"));
		return KS_NOPARAMFOUND;
	}
	hex2dec(param_value,12,param_key_b,len);
	// water seed keys
	if(g_enc_op.get_card_param("yncs_hd_seedkey",param_value)!=0)
	{
		DEBUG_LOG(("未设置汇多参数卡密钥参数"));
		return KS_NOPARAMFOUND;
	}
	hex2dec(param_value,16,seed_key,len);
	// water param sect 
	if(g_enc_op.get_card_param("yncs_hd_paramsect",param_value)!=0)
	{
		DEBUG_LOG(("未设置汇多参数卡密钥参数"));
		return KS_NOPARAMFOUND;
	}
	sect = atoi(param_value);
	block_no = sect*4;
	// water card sect
	if(g_enc_op.get_card_param("yncs_hd_sect",param_value)!=0)
	{
		DEBUG_LOG(("未设置汇多参数卡密钥参数"));
		return KS_NOPARAMFOUND;
	}
	watersect = atoi(param_value);

	// 登录扇区
	if(g_dev_op.login_card(&g_reader,&g_cardinfo,sect,MF_KEYA,param_key_a)!=0)
	{
		ret = ks_mf_card(phyid);
		if(ret)
			return KS_REQUESTCARD;
		// 登录 参数卡 15 扇区错误
		if(g_dev_op.login_card(&g_reader,&g_cardinfo,sect,MF_KEYA,param_init_key)!=0)
		{
			DEBUG_LOG(("初始化汇多设置卡失败，参数扇区无法初始化,请确认该扇区密钥"));
			return KS_LOGINCARD;
		}
		memcpy(buffer,param_key_a,6);
		memcpy(buffer+6,new_ctrl_bit,4);
		memcpy(buffer+10,param_key_b,6);
		if(g_dev_op.write_block(&g_reader,&g_cardinfo,block_no+3,buffer)!=0)
		{
			DEBUG_LOG(("写汇多设置卡失败，请确认该扇区可读写"));
			return KS_WRITECARD;
		}
	}
	
	// 写参数卡
	offset = 0;
	memcpy(buffer,seed_key,8);
	offset += 8;
	set_2byte_int(buffer+offset,param->minmoney);
	offset += 2;
	set_3byte_int(buffer+offset,param->maxmoney);
	offset += 3;
	set_2byte_int(buffer+offset,param->unit);
	offset += 2;
	buffer[15] = calc_xor(buffer,offset);
	if(g_dev_op.write_block(&g_reader,&g_cardinfo,block_no,buffer)!=0)
	{
		DEBUG_LOG(("写汇多设置卡失败，请确认该块[%d]可读写",block_no));
		return KS_WRITECARD;
	}
	memset(buffer,0xFF,16);
	offset = 0;
	set_2byte_int(buffer+offset,param->transmoney);
	offset += 2;
	buffer[offset++] = param->priceindex;
	buffer[offset++] = watersect;
	buffer[offset++] = 0;
	buffer[15] = calc_xor(buffer,15);
	if(g_dev_op.write_block(&g_reader,&g_cardinfo,block_no+1,buffer)!=0)
	{
		DEBUG_LOG(("写汇多设置卡失败，请确认该块[%d]可读写",block_no+1));
		return KS_WRITECARD;
	}
	return 0;
}

static int hd_water_recycleparamcard()
{
	/*
	int ret,block_no,len,sect;
	unsigned char param_key_a[] = {0x23,0x55,0x33,0x78,0x12,0xAB};
	unsigned char param_key_b[] = {0x34,0x22,0x35,0x23,0x45,0x34};
	unsigned char param_init_key[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	unsigned char seed_key[8];
	unsigned char new_ctrl_bit[] = {0x7F,0x07,0x88,0x00};
	char param_value[128];
	unsigned char buffer[16];

	// 获取汇多参数卡的参数信息
	// param card keya
	if(g_enc_op.get_card_param("yncs_hd_paramcardkey",param_value)!=0)
	{
		DEBUG_LOG(("未设置汇多参数卡密钥参数"));
		return KS_NOPARAMFOUND;
	}
	hex2dec(param_value,12,param_key_a,len);
	// param card keyb
	if(g_enc_op.get_card_param("yncs_waterparamcardkeyb",param_value)!=0)
	{
		DEBUG_LOG(("未设置汇多参数卡密钥参数"));
		return KS_NOPARAMFOUND;
	}
	hex2dec(param_value,12,param_key_b,len);
	if(g_dev_op.login_card(&g_reader,&g_cardinfo,block_no))
	return 0;
	*/
	return KS_NOTSUPPORT;
}

//////////////////////////////////////////////////////////////////////////
// 新天卡结构

static int xt_water_recyclecard()
{
	int sectno,ret,blockno;
	unsigned char buffer[16];
	char param_value[256] = "";
	if(g_enc_op.get_card_param("yncs_xt_sect",param_value))
		return KS_NOPARAMFOUND;
	sectno = atoi(param_value);

	blockno = sectno * 4;
	ret = ks_mf_login_card(sectno);
	if(ret)
		return ret;
	memset(buffer,0,sizeof buffer);
	if(g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer))
	{
		return KS_WRITECARD;
	}
	if(g_dev_op.write_block(&g_reader,&g_cardinfo,blockno+1,buffer))
	{
		return KS_WRITECARD;
	}
	return 0;
}
static int xt_water_readmoney(ks_water_pack_t *pack)
{
	int sectno,ret,blockno;
	unsigned char buffer[16];
	char param_value[256] = "";
	if(g_enc_op.get_card_param("yncs_xt_sect",param_value))
		return KS_NOPARAMFOUND;
	sectno = atoi(param_value);
	blockno = sectno * 4;

	DEBUG_LOG(("读新天水控钱包"));
	ret = ks_mf_login_card(sectno);
	if(ret)
		return ret;
	memset(buffer,0,sizeof buffer);
	if(g_dev_op.read_block(&g_reader,&g_cardinfo,blockno,buffer))
	{
		return KS_READCARD;
	}
	if(check_buffer_sum(buffer,15,buffer[15]))
	{
		if(g_dev_op.read_block(&g_reader,&g_cardinfo,blockno+1,buffer))
		{
			return KS_READCARD;
		}
		if(check_buffer_sum(buffer,15,buffer[15]))
		{
			return KS_PURSEERROR;
		}
	}
	pack->money = get_3byte_money(buffer);
	pack->totalmoney = get_3byte_money(buffer+4);
	pack->custno = get_4byte_money(buffer+10);
	return 0;
}
static int xt_water_writemoney(ks_water_pack_t *pack)
{
	int sectno,ret,blockno,offset,i;
	unsigned char buffer[16],buffer2[16];
	char param_value[256] = "";
	if(g_enc_op.get_card_param("yncs_xt_sect",param_value))
		return KS_NOPARAMFOUND;
	sectno = atoi(param_value);
	if(pack->money > MAX_WATER_PACK_MONEY)
		return KS_EXCEEDMONEY;

	//for(i=15;i<16;++i)
	//{		
	//	sectno = i;
		blockno = sectno *4;


		ret = ks_mf_login_card(sectno);
		if(ret)
			return ret;
		offset = 0;
		memset(buffer,0,sizeof buffer);
		set_3byte_money(buffer,pack->money);
		offset+=3;
		offset++;
		set_3byte_money(buffer+offset,pack->totalmoney);
		offset+=3;
		offset+=3;
		pack->custno = 1;
		set_4byte_money(buffer+offset,pack->custno);
		buffer[15] = calc_sum(buffer,15);
		//DEBUG_LOG(("写钱包[%d]",sectno));
		g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer);
		if(g_dev_op.read_block(&g_reader,&g_cardinfo,blockno,buffer2))
		{
			return KS_UNCONFIRM;
		}
		if(memcmp(buffer,buffer2,16)!=0)
			return KS_WRITECARD;
		DEBUG_LOG(("写钱包[%d]完成",sectno));
	//}
	return 0;
}

static int xt_water_publishcard(ks_water_pack_t *pack)
{
	return xt_water_writemoney(pack);
}
static int do_format_xt_paramcard(ks_water_param_t *param)
{
	int i,ret;
	char phyid[9];
	unsigned char orgin_keya[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	unsigned char new_keya[] = {0x01,0x02,0x03,0x04,0x05,0x06};
	ret = ks_mf_card(phyid);
	if(ret)
		return KS_REQUESTCARD;

	for(i = 1;i < 15;++i)
	{
		ret = g_dev_op.login_card(&g_reader,&g_cardinfo,i,MF_KEYA,orgin_keya);
		if(ret)
		{
			ret = ks_mf_card(phyid);
			if(ret)
				return KS_REQUESTCARD;
			ret = g_dev_op.login_card(&g_reader,&g_cardinfo,i,MF_KEYA,new_keya);
			if(ret)
			{
				DEBUG_LOG(("发行新天设置卡失败，扇区[%d]无法登录",i));
				return KS_LOGINCARD;
			}
		}
	}
	DEBUG_LOG(("格式化新天设置卡[%s]成功",phyid));
	return 0;
}
static int do_xt_water_paramcard(ks_water_param_t *param)
{
	int i,ret,block_no;
	char phyid[9];
	unsigned char orgin_keya[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	unsigned char new_keya[] = {0x01,0x02,0x03,0x04,0x05,0x06};
	unsigned char new_keyb[] = {0x34,0x22,0x35,0x23,0x45,0x34};
	unsigned char new_ctrl_bit[] = {0x7F,0x07,0x88,0x00};
	unsigned char data[16],data1[16];
	unsigned char card_key[16];
	memcpy(card_key,new_keya,6);
	memcpy(card_key+6,new_ctrl_bit,4);
	memcpy(card_key+10,new_keyb,6);



	//////////////////////////////////////////////////////////////////////////
	// 卡结构数据
	memset(data,0,sizeof data);
	// 单价
	data[0] = param->unitmoney % 256;
	data[1] = param->unitmoney / 256;
	// 扇区号
	data[2] = param->watersect % 256;
	// 控制器编号
	data[3] = param->termid % 256;
	data[4] = param->termid / 256;
	// 预充值
	data[5] = param->transmoney % 256;
	// 剩余量报警
	data[6] = param->minmoney % 256;
	// 单价
	memcpy(data+8,data,2);
	data[10] = data[2];
	memcpy(data+11,data+3,2);
	//data[13] = data[5];
	data[14] = data[6];
	for(i = 0,data[15] = 0;i < 15;++i)
		data[15] += data[i];

	memset(data1,0,sizeof data1);
	memcpy(data1,param->workkey,6);
	memcpy(data1+8,param->workkey,6);
	for(i = 0, data1[15]=0;i < 15;++i)
		data1[15] += data1[i];

	ret = ks_mf_card(phyid);
	if(ret)
		return KS_REQUESTCARD;

	for (i = 1;i < 16;++i)
	{
		block_no = i * 4;
		ret = g_dev_op.login_card(&g_reader,&g_cardinfo,i,MF_KEYA,new_keya);
		if(ret)
		{
			ret = ks_mf_card(phyid);
			if(ret)
				return KS_REQUESTCARD;
			// 不是初始密钥，需要从新初始化
			ret = g_dev_op.login_card(&g_reader,&g_cardinfo,i,MF_KEYA,orgin_keya);
			if(ret)
			{
				DEBUG_LOG(("初始化新天设置卡失败，扇区[%d]无法初始化,请确认该扇区密钥",i));
				return KS_LOGINCARD;
			}

			ret = g_dev_op.write_block(&g_reader,&g_cardinfo,block_no+3,card_key);
			if(ret)
			{
				DEBUG_LOG(("初始化新天设置卡失败，扇区[%d]无法写入密钥，请确认卡扇区",i));
				return KS_WRITECARD;
			}
			// 更改密钥后重新登录
			ret = ks_mf_card(phyid);
			if(ret)
				return KS_REQUESTCARD;
			ret = g_dev_op.login_card(&g_reader,&g_cardinfo,i,MF_KEYA,new_keya);
			if(ret)
			{
				DEBUG_LOG(("初始化新天设置卡扇区[%d]后，无法登录,请确认该扇区密钥",i));
				return KS_LOGINCARD;
			}
		}
		// 写设置卡参数
		ret = g_dev_op.write_block(&g_reader,&g_cardinfo,block_no,data);
		if(ret)
		{
			DEBUG_LOG(("写新天参数卡扇区[%d]失败",i));
			return KS_WRITECARD;
		}
		ret = g_dev_op.write_block(&g_reader,&g_cardinfo,block_no+1,data1);
		if(ret)
		{
			DEBUG_LOG(("写新天参数卡扇区[%d]失败",i));
			return KS_WRITECARD;
		}
	}
	return 0;
}

static int do_xt_water_initcard(ks_water_param_t *param)
{
	int i,ret,block_no;
	char phyid[9];
	unsigned char orgin_keya[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	unsigned char new_keya[] = {0x01,0x02,0x03,0x04,0x05,0x06};
	unsigned char new_keyb[] = {0x34,0x22,0x35,0x23,0x45,0x34};
	unsigned char new_ctrl_bit[] = {0x7F,0x07,0x88,0x00};
	unsigned char data[16];
	unsigned char card_key[16];
	memcpy(card_key,new_keya,6);
	memcpy(card_key+6,new_ctrl_bit,4);
	memcpy(card_key+10,new_keyb,6);



	//////////////////////////////////////////////////////////////////////////
	// 卡结构数据
	memset(data,0,sizeof data);
	memset(data,0xFA,4);
	for(i = 0,data[15] = 0;i < 15;++i)
		data[15] += data[i];


	ret = ks_mf_card(phyid);
	if(ret)
		return KS_REQUESTCARD;

	for (i = 1;i < 16;++i)
	{
		block_no = i * 4;
		ret = g_dev_op.login_card(&g_reader,&g_cardinfo,i,MF_KEYA,new_keya);
		if(ret)
		{
			ret = ks_mf_card(phyid);
			if(ret)
				return KS_REQUESTCARD;
			// 不是初始密钥，需要从新初始化
			ret = g_dev_op.login_card(&g_reader,&g_cardinfo,i,MF_KEYA,orgin_keya);
			if(ret)
			{
				DEBUG_LOG(("初始化新天清零卡失败，扇区[%d]无法初始化,请确认该扇区密钥",i));
				return KS_LOGINCARD;
			}

			ret = g_dev_op.write_block(&g_reader,&g_cardinfo,block_no+3,card_key);
			if(ret)
			{
				DEBUG_LOG(("初始化新天清零卡失败，扇区[%d]无法写入密钥，请确认卡扇区",i));
				return KS_WRITECARD;
			}
			// 更改密钥后重新登录
			ret = ks_mf_card(phyid);
			if(ret)
				return KS_REQUESTCARD;
			ret = g_dev_op.login_card(&g_reader,&g_cardinfo,i,MF_KEYA,new_keya);
			if(ret)
			{
				DEBUG_LOG(("初始化新天清零卡扇区[%d]后，无法登录,请确认该扇区密钥",i));
				return KS_LOGINCARD;
			}
		}
		// 写设置卡参数
		ret = g_dev_op.write_block(&g_reader,&g_cardinfo,block_no,data);
		if(ret)
		{
			DEBUG_LOG(("写新天参数卡扇区[%d]失败",i));
			return KS_WRITECARD;
		}
		ret = g_dev_op.write_block(&g_reader,&g_cardinfo,block_no+1,data);
		if(ret)
		{
			DEBUG_LOG(("写新天参数卡扇区[%d]失败",i));
			return KS_WRITECARD;
		}
		ret = g_dev_op.write_block(&g_reader,&g_cardinfo,block_no+2,data);
		if(ret)
		{
			DEBUG_LOG(("写新天参数卡扇区[%d]失败",i));
			return KS_WRITECARD;
		}
	}

	return 0;
}
static int xt_water_publishparamcard(ks_water_param_t *param)
{
	int ret;
	switch(param->cardflag)
	{
	case 0:
		ret = do_xt_water_paramcard(param);
		break;
	case 1:
		ret = do_xt_water_initcard(param);
		break;
	default:
		return -1;
	}
	return ret;
}
static int xt_water_recycleparamcard()
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// 
int __stdcall ks_water_publishcard(int watertype,ks_water_pack_t *pack)
{
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_publishcard(pack);
	case KS_HD_WATER:
		return hd_water_publishcard(pack);
	default:
		return KS_NOTSUPPORT;
	}
}
int __stdcall ks_water_recyclecard(int watertype)
{
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_recyclecard();
	case KS_HD_WATER:
		return hd_water_recyclecard();
	default:
		return KS_NOTSUPPORT;
	}
}
int __stdcall ks_water_readmoney(int watertype,ks_water_pack_t *pack)
{
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_readmoney(pack);
	case KS_HD_WATER:
		return hd_water_readmoney(pack);
	default:
		return KS_NOTSUPPORT;
	}
}
int __stdcall ks_water_writemoney(int watertype,ks_water_pack_t *pack)
{
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_writemoney(pack);
	case KS_HD_WATER:
		return hd_water_writemoney(pack);
	default:
		return KS_NOTSUPPORT;
	}
}	


int __stdcall ks_water_publishparamcard(int watertype,ks_water_param_t *param)
{
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_publishparamcard(param);
	case KS_HD_WATER:
		return hd_water_publishparamcard(param);
	default:
		return KS_NOTSUPPORT;
	}
}
int __stdcall ks_water_recycleparamcard(int watertype)
{
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_recycleparamcard();
	case KS_HD_WATER:
		return hd_water_recycleparamcard();
	default:
		return KS_NOTSUPPORT;
	}
}
