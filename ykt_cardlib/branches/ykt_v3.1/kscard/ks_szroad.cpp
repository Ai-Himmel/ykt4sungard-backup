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


#define SR_SECTNO 9

int __stdcall ks_sr_publishcard(sr_water_info_t *info)
{
	int ret;
	uint8 buffer[16];
	char dt[15];
	int blockno;
	ret = ks_mf_login_card(SR_SECTNO);
	if(ret)
		return ret;
	
	memset(buffer,0,sizeof buffer);
	// ���׿���
	buffer[0] = (info->cardno >> 16) & 0xFF;
	buffer[1] = info->cardno & 0xFF;
	buffer[2] = (info->cardno >> 8) & 0xFF;
	// �����
	buffer[3] = info->cardtype;
	// �ͻ���
	set_4byte_int(buffer+10,info->custno);

	buffer[15] = calc_sum(buffer,15);

	blockno = 4 * SR_SECTNO;
	ret = g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer);
	if(ret)
	{
		DEBUG_LOG(("д��·ˮ���û���Ϣʧ��.[%d]",ret));
		return ret;
	}

	// дǮ��
	memset(buffer,0,sizeof buffer);
	get_current_datetime(dt);
	hex2dec(dt+2,12,buffer+6,ret);
	buffer[15] = calc_sum(buffer,15);

	blockno++;
	ret = g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer);
	if(ret)
	{
		DEBUG_LOG(("д��·ˮ��Ǯ����Ϣʧ��.[%d]",ret));
		return ret;
	}

	blockno++;
	ret = g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer);
	if(ret)
	{
		DEBUG_LOG(("д��·ˮ�ر���Ǯ����Ϣʧ��.[%d]",ret));
		return ret;
	}
	return 0;
}

int __stdcall ks_sr_recyclecard()
{
	int ret,blockno;
	uint8 buffer[16];
	ret = ks_mf_login_card(SR_SECTNO);
	if(ret)
		return ret;

	blockno = 4 * SR_SECTNO;
	ret = g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer);
	if(ret)
	{
		DEBUG_LOG(("д��·ˮ���û���Ϣʧ��.[%d]",ret));
		return ret;
	}

	// дǮ��
	memset(buffer,0,sizeof buffer);
	blockno++;
	ret = g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer);
	if(ret)
	{
		DEBUG_LOG(("д��·ˮ��Ǯ����Ϣʧ��.[%d]",ret));
		return ret;
	}

	blockno++;
	ret = g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer);
	if(ret)
	{
		DEBUG_LOG(("д��·ˮ�ر���Ǯ����Ϣʧ��.[%d]",ret));
		return ret;
	}
	return 0;
}

int __stdcall ks_sr_readmoney(sr_water_pack_t *pack)
{
	int ret,blockno;
	uint8 buffer[16],buffer2[16];
	uint8 sum;
	DEBUG_LOG(("����·ˮ��"));
	ret = ks_mf_login_card(SR_SECTNO);
	if(ret)
		return ret;

	blockno = 4 * SR_SECTNO;
	// ��Ǯ��
	memset(buffer,0,sizeof buffer);
	blockno++;
	ret = g_dev_op.read_block(&g_reader,&g_cardinfo,blockno,buffer);
	if(ret)
	{
		DEBUG_LOG(("����·ˮ��Ǯ����Ϣʧ��.[%d]",ret));
		return ret;
	}

	if(check_buffer_sum(buffer,15,buffer[15]))
	{
		// ������Ǯ��
		ret = g_dev_op.read_block(&g_reader,&g_cardinfo,blockno+1,buffer);
		if(ret)
		{
			DEBUG_LOG(("����·ˮ��Ǯ����Ϣʧ��"));
			return ret;
		}
		if(check_buffer_sum(buffer,15,buffer[15]))
		{
			DEBUG_LOG(("��·ˮ��Ǯ����ʽ����.[%d]"));
			return ret;
		}
	}
	pack->money = buffer[0] + buffer[1] * 256 + buffer[2] * 65536;
	pack->pre_money = buffer[3] + buffer[4] * 256 + buffer[5] * 65536;
	dec2hex(buffer+6,6,pack->add_time);
	pack->add_count = buffer[12] * 256 + buffer[13];
	return 0;
}

int __stdcall ks_sr_setmoeny(int money,int cnt)
{
	int ret,blockno;
	uint8 buffer[16],buffer2[16];
	char dt[15];
	uint8 sum;
	sr_water_pack_t pack;

	DEBUG_LOG(("����·ˮ��"));
	ret = ks_mf_login_card(SR_SECTNO);
	if(ret)
		return ret;

	blockno = 4 * SR_SECTNO;
	// ��Ǯ��
	memset(buffer,0,sizeof buffer);
	blockno++;
	ret = g_dev_op.read_block(&g_reader,&g_cardinfo,blockno,buffer);
	if(ret)
	{
		DEBUG_LOG(("����·ˮ��Ǯ����Ϣʧ��.[%d]",ret));
		return ret;
	}

	if(check_buffer_sum(buffer,15,buffer[15]))
	{
		// ������Ǯ��
		ret = g_dev_op.read_block(&g_reader,&g_cardinfo,blockno+1,buffer);
		if(ret)
		{
			DEBUG_LOG(("����·ˮ��Ǯ����Ϣʧ��"));
			return ret;
		}
		if(check_buffer_sum(buffer,15,buffer[15]))
		{
			DEBUG_LOG(("��·ˮ��Ǯ����ʽ����.[%d]"));
			return ret;
		}
	}
	pack.money = buffer[0] + buffer[1] * 256 + buffer[2] * 65536;
	pack.pre_money = buffer[3] + buffer[4] * 256 + buffer[5] * 65536;
	pack.add_count = buffer[12] * 256 + buffer[13];

	// ��Ϊд�ɹ�
	if(pack.add_count == cnt && pack.money == money)
		return 0;

	memset(buffer,0,sizeof buffer);
	buffer[0] = money % 65536;
	buffer[1] = (money / 256) % 256;
	buffer[2] = (money/65536) % 256;

	buffer[3] = pack.pre_money % 65536;
	buffer[4] = (pack.pre_money / 256) % 256;
	buffer[5] = (pack.pre_money / 65536) % 256;

	get_current_datetime(dt);
	hex2dec(dt+2,12,buffer+6,ret);

	buffer[12] = cnt / 256;
	buffer[13] = cnt % 256;

	buffer[15] = calc_sum(buffer,15);

	ret = g_dev_op.write_block(&g_reader,&g_cardinfo,blockno,buffer);
	if(!ret)
	{
		ret = g_dev_op.read_block(&g_reader,&g_cardinfo,blockno,buffer2);
		if(ret)
		{
			return KS_UNCONFIRM;
		}
		if(memcmp(buffer,buffer2,16)!=0)
			return KS_WRITECARD;
		g_dev_op.write_block(&g_reader,&g_cardinfo,blockno+1,buffer);
	}
	else
		return KS_WRITECARD;

	return 0;
}

