#include "reg52.h"
#include "mifare_card.h"
#include "z18pos.h"
#include ".\Include\LibFuntion.h"
#include <string.h>
#include "stdio.h"
#include <stdlib.h>
#include "crc.h"

#define REC_PARAM_SECT 5

static uint8 rec_block;
uint8 gen_user_card_keyA(uint8 *key,const uint8 *text,uint8 *keyA)
{
	// gen_user_card_keyA�������keyA��des_code�������ucDesData��һ���Ķ���
	uint8 i;
	uint8 sPlain[9];	
	uint8 sCipher[17]; 
	uint16 startpos = 0;
	memset(sPlain, 0, sizeof(sPlain));	
	memset(sCipher, 0, sizeof(sCipher));
	for(i = 0; i < 4; i++)
	{
		sPlain[i] = text[i];
		sPlain[i+4] = ~text[i];
	}
#if 0
	Display(0,0,"main key",0);
	kng_sleep(20);
	debug_hex(key,8);
	kng_sleep(50);
	cls();
	Display(0,0,"text",0);
	kng_sleep(20);
	debug_hex(sPlain,8);
	kng_sleep(50);
#endif
	//encrypt_des(key, 8, sPlain, 8, sCipher);
	DESEncode(sPlain,sCipher,key,0);
	memcpy(sCipher + 8, sCipher, 8);
	for(i=0,startpos=0;i < 8;++i)
		startpos += (uint16)sCipher[i];
	startpos %= 7;
#if 0
	sprintf(msg,"pos :%d",startpos);
	cls();
	Display(0,0,msg,0);
	kng_sleep(50);
#endif
	memcpy(keyA, sCipher + startpos, 6);

#if 0
	cls();
	Display(0,0,"cipher",0);
	kng_sleep(20);
	debug_hex(sCipher,8);
	kng_sleep(100);
#endif
	return 0;
}

bit check_buffer_crc(const uint8 *buff,uint8 len)
{
	uint8 i,crc,notcrc;
	for(i=0,crc=0,notcrc=0;i<len;++i)
	{
		crc += buff[i];
		notcrc |= buff[i];
	}
	// ����ʧ��
	if(crc != buff[len] || notcrc == 0)
		return 1;
	return 0;
}
uint8 kng_login_card(uint8 *phyno,uint8 sect)
{
	uint8 ret;
	if(g_mycard.last_login_sect == sect)
		return 0;
	// ������һ�ſ������¼���keya
	if(memcmp(phyno,g_mycard.phyno,4) != 0)
	{
		gen_user_card_keyA(g_z18pos.mainkey,phyno,g_mycard.keya);
#if 0
		debug_hex(g_z18pos.mainkey,8);
		debug_hex(g_mycard.keya,6);
		debug_hex(g_mycard.phyno,4);
#endif
		memcpy(g_mycard.phyno,phyno,4);

	}
	ret = mif_loadkey(g_mycard.keya);
	if(ret != Z18_OK)
	{
		debug_string("load key!\n");
		return KNG_LOGIN_DENY;
	}
	ret = mif_authen(0,sect,phyno);
	if(ret==Z18_OK)
	{
		g_mycard.last_login_sect = sect;
		return 0;
	}
	g_mycard.last_login_sect = 0xFF;
	debug_string("login faild %d\n",(uint16)sect);
	debug_hex(g_mycard.phyno,4);
	debug_hex(g_mycard.keya,6);
	return KNG_LOGIN_DENY;

}
uint8 kng_read_phyno(uint8 *phyno)
{
	uint16 ret;
	uint8 snk;
	uint8 err_sn[4];
	memset(err_sn,0x00,sizeof err_sn);
	ret = mif_anticoll(0,phyno);
	if(ret == Z18_FAILED)
	{
		return KNG_READ_CARD;
	}
	if(memcmp(err_sn,phyno,4)==0)
	{
		return KNG_POS_NOT_SUPP_CARDTYPE;
	}
	ret = mif_select(0,phyno,&snk);
	if(ret != Z18_OK)
	{
		// ѡ��ʧ��
		debug_string("select card\n");
		return KNG_READ_CARD;
	}
	return 0;
}



static void get_money_from_buffer(const uint8 *buffer,uint32 *money,uint16 *count)
{
	// ����Ǯ�����
	uint32 r;
	uint32 t;
	r = buffer[0];
	t = buffer[1];
	t <<= 8;

	r += t;
	t = buffer[2];
	t <<= 16;
	r += t;
	*money = r;

	// ���״���
	t = buffer[3];
	t <<=8;
	r = t;
	r += buffer[4];
	*count = (uint16)r;
}
static void set_money_buffer(uint32 money,uint16 count,uint8 *buffer)
{
	buffer[0] = money & 0xFF;
	buffer[1] = (money >> 8) & 0xFF;
	buffer[2] = (money >> 16) & 0xFF;

	buffer[3] = (count >> 8) & 0xFF;
	buffer[4] = (uint8)(count  & 0xFF);
}

static void set_3byte_money(uint32 money,uint8 *buffer)
{
	buffer[0] = money & 0xFF;
	buffer[1] = (money >> 8) & 0xFF;
	buffer[2] = (money >> 16) & 0xFF;
}
static uint32 get_3byte_money(uint8 *buffer)
{
	uint32 r;
	uint32 t;
	r = buffer[0];
	t = buffer[1];
	t <<= 8;

	r += t;
	t = buffer[2];
	t <<= 16;
	r += t;
	return r;
}
static uint8 z18_read_card(uint8 block,uint8 retries,uint8 *buffer)
{
	uint8 ret;
	while(retries-->0)
	{
		ret = mif_Read(block,buffer);
		if(ret == Z18_OK)
			return 0;
	}
	return KNG_READ_CARD;
}

static uint8 z18_write_card(uint8 block,uint8 retries,uint8 *buffer)
{
	uint8 ret;
	while(retries-->0)
	{
		ret = mif_Write(block,buffer);
		if(ret == Z18_OK)
			return 0;
	}
	return KNG_WRITE_CARD;
}

uint8 read_card_info(const uint8 *phyno)
{
	uint16 ret;
	uint8 buffer[16];
	uint8 expired_date[9];
	uint8 offset,value;
	ret = kng_login_card(phyno,1);
	if(ret)
	{
		debug_string("login sect 1\n");
		return KNG_LOGIN_DENY;
	}
	memset(buffer,0,sizeof buffer);
	ret = mif_Read(4,buffer);
	if(Z18_OK != ret)
	{
		debug_string("read block 4\n");
		return KNG_READ_CARD;
	}
	// TODO : �Ͼ���ѧ�汾��Ҫ�ж�������־
	//
	// ���׿���
	g_mycard.card_id = get_3byte_int(buffer);
	if(g_mycard.card_id <= 0)
	{
		return KNG_POS_UNEXPECT_CARD;
	}

	// ��Ȩ�� 
	g_mycard.card_type = buffer[3];	
	if(g_mycard.card_type <= 0)
	{
		return KNG_POS_UNEXPECT_CARD;
	}
	// ��Ч��, string ��ʽ
	#if 0
	memset(expired_date,0,sizeof expired_date);
	sprintf(expired_date,"20%02d%02d%02d",(uint16)buffer[4],(uint16)buffer[5],(uint16)buffer[6]);

	//debug_string(expired_date);

	// ע�⣬ÿ�ζ���ʱ������ȫ��ϵͳʱ����������ֵ����Ϊ����ʱ���¼����ˮ��
	InitRtcTime();
	//ReadRtcTime(g_z18pos.curr_time);
	ReadRtcTime(g_rec_data);
	if(memcmp(g_rec_data,g_z18pos.curr_time,4) > 0)
	{
		g_z18pos.uncoll_days++;
	}
	memcpy(g_z18pos.curr_time,g_rec_data,7);
	bcd2str(g_z18pos.curr_time,4,g_rec_data);
	if(strncmp(g_rec_data,expired_date,8) >= 0)
	{
		// ������
		return KNG_POS_EXPIRED_CARD;
	}
	#else
	hex2bcd(buffer+4,3,g_rec_data);
    if(memcmp(g_z18pos.curr_time+1,g_rec_data,3)>=0)
    {
        // ������
		return KNG_POS_EXPIRED_CARD;
    }
    #endif

	// �жϿ�Ȩ��
	// card_type / 8 д��  card_type >> 3
	//debug_string("right[%d]\n",(uint16)g_mycard.card_type);
	//debug_hex(g_z18pos.card_right,32);
	offset = (g_mycard.card_type >> 3) & 0x00FF;
	value = g_z18pos.card_right[offset];
	offset = offset << 3;
	offset = g_mycard.card_type - offset;
	//debug_string("r[%d][%d]\n",(uint16)value,(uint16)offset);
	if( !(value & (1 << (8 - offset))) )
	{
		return KNG_POS_NO_RIGHT;
	}

	return 0;
}

static uint32 time_2_secs(uint8 *time_bcd)
{
	uint32 r;
	r = ((time_bcd[0]&0xF0)>>4) * 36000 + (time_bcd[0]&0x0F) * 3600;
	r += ((time_bcd[1]&0xF0)>>4) * 600 + (time_bcd[1]&0x0F) * 60;
	r += ((time_bcd[2]&0xF0)>>4) * 10 + (time_bcd[2]&0x0F);
	return r;
}




// ���屣�濨��ˮ
#ifdef SAVE_CARD_REC

// �ж�ʱ������1  ��ʾ���ܿ۷ѣ�0  ��ʾ���Կ۷�
static bit check_card_interval(z18_record_t *record)
{
	uint32 secs1,secs2;
	uint8 time_bcd[3];
	// ͬһ̨POS���ж�
	if(memcmp(g_z18pos.device_id,record->pre_device_id,4)==0)
	{
		// ��������POS������¼��ˮ�����Ǳ��������ж�
		if(memcmp(record->pre_tx_time,g_mycard.last_consume_date+2,3)!=0)
		{
			return 0;
		}
		// �ȱȽ�ˢ������
		// ͬһ�����ѲŽ����ж�
		if(memcmp(g_z18pos.curr_time+1,g_mycard.last_consume_date,3)==0)
		{
			// ת������
			secs1 = time_2_secs(g_z18pos.curr_time+4);
			//debug_string("1[%ld]\n",secs1);

			// ���һ�ʽ�����Ǯ���н���ʱ��һ��
			if(memcmp(g_mycard.last_consume_date+2,record->pre_tx_time,3)==0)
			{
				secs2 = time_2_secs(record->pre_tx_time+1);
			}
			else
			{
				/*
				memset(time_bcd,0,sizeof time_bcd);
				memcpy(time_bcd,g_mycard.last_consume_date+3,2);
				*/
				secs2 = time_2_secs(g_mycard.last_consume_date+3);
			}
			//debug_string("2[%ld]\n",secs2);

			if(secs1 > secs2)
			{
				if(secs1-secs2 <= g_z18pos.card_interval)
				{
					debug_string("1[%lu]2[%lu]\n",secs1,secs2);
					return 1;
				}
			}
		}
	}
	return 0; // ���Կۿ�
}


// �ж��Ƿ�д���ɹ�������1 ��ʾ����Ҫд��0 ��ʾ��Ҫд��
static uint8 check_last_consume(z18_record_t *record)
{
	// �ϴν����뿨ֵ == ��ǰ���뿨ֵ���������û��д�Ͽ�
	// FIXME : 2009-9-6
	// ���ж��ǲ��ǵ��쵱ʱ�����Ľ���
	
	if(record->pre_in_balance == g_mycard.balance)
	{
		debug_string("balance not change!");
		//if(memcmp(g_z18pos.device_id,record->pre_device_id,4) == 0)
		{
			if(g_mycard.last_consume_date[2]==record->pre_tx_time[0])
			{
				
				// �ϴν����뿨ֵ == ��ǰ�뿨ֵ 
				// �ϴν����豸 == ��ǰ�����豸
				// �ϴν��� �� == ��ǰ���� ��
				// ����������������û��д��
				return 0;
			}
		}
	}
	else
	{
		debug_string("balance changed!");
		// ������ϵĽ���ʱ��һ�£�д���ѳɹ�
		if(memcmp(g_mycard.last_consume_date+2,record->pre_tx_time,3)==0)
		{
			debug_string("tx_time equals");
			// �����Ǳ�����û��д��
			// �����жϽ���ʱ������̴���
			if(!check_card_interval(record))
			{
				return 0;
			}
			return 1;
		}
		
		return 0;		
		
	}
	return 1;
}


static uint8 check_card_process(card_rec_info_t *card_rec,z18_record_t *record)
{
	uint8 ret,i,block,rd_block;
	uint8 sect_ary[] = {0,5,6,6,6,7,7,7,8,8,8};
	//uint8 block_ary[] = {0,2,4,5,6,8,9,10,12,13,14};
	uint8 block_ary[] = {0,2,0,1,2,0,1,2,0,1,2};
	bit c1,c2;
	ret = kng_login_card(g_mycard.phyno,5);
	if(ret)
	{
		debug_string("login sect 5\n");
		return ret;
	}
	block = 5<<2;
	// �ȶ�ȡ��������
	ret = z18_read_card(block,1,g_rec_data);
	if(ret)
	{
		debug_string("read block 20\n");
		return ret;
	}
	ret = z18_read_card(block+1,1,g_rec_data+16);
	if(ret)
	{
		debug_string("read block 20\n");
		return ret;
	}
	// ��������ȷ
	c1 = check_buffer_crc(g_rec_data,15);
	c2 = check_buffer_crc(g_rec_data+16,15);
	if(c1 == 0 && c2 == 0)
	{
L_CHECK_CARD:
		if(g_rec_data[0] >= 11)
			g_rec_data[0] = CARD_PRC_BEGIN;
		if(g_rec_data[0] > 0 && g_rec_data[0] < 11)
		{
			// ��ȡ��ˮ
			card_rec->rd_rec_sect = sect_ary[g_rec_data[0]];
			rd_block = (card_rec->rd_rec_sect<<2) + block_ary[g_rec_data[0]];
			// ��ȡ�ϴν������
			ret = kng_login_card(g_mycard.phyno,card_rec->rd_rec_sect);
			if(ret)
				return ret;
			ret = z18_read_card(rd_block,1,g_rec_data+32);
			if(ret)
				return ret;
			i = 32;
			memcpy(record->pre_device_id,g_rec_data+i,4);
			i+=4;
			memcpy(record->pre_tx_time,g_rec_data+i,4);
			i+=4;
			record->pre_in_balance = get_4byte_int(g_rec_data+i);
			i+=4;
			record->pre_tx_money = get_3byte_int(g_rec_data+i);
			i+=3;
			record->pre_tx_mark = g_rec_data[i];
			debug_string("card record\n");
			debug_hex(g_rec_data+32,16);
		}

		// ��������һ��
		if(memcmp(g_rec_data,g_rec_data+16,16)==0)
		{
			
			// �ж�ˢ��ʱ����
			if(check_card_interval(record))
			{
				return KNG_POS_REPEAT_CONSUME;
			}
			// �ϴν��׳ɹ�������������
			g_mycard.rec_index = g_rec_data[0] + 1;
			
L_CHECK_CARD2:

			if(g_mycard.rec_index > CARD_MAX_REC)
				g_mycard.rec_index = 1;
			g_rec_data[0] = g_mycard.rec_index;
			card_rec->wr_rec_sect = sect_ary[g_mycard.rec_index];
			card_rec->wr_block = (card_rec->wr_rec_sect<<2) + block_ary[g_mycard.rec_index];

			debug_string("interval idx[%d]\n",(uint16)g_mycard.rec_index);
			
			// ��������������¼��ǰ��ˮ
			// �ȼ���ˮ���ٸ���������
			ret = kng_login_card(g_mycard.phyno,card_rec->wr_rec_sect);
			if(ret)
				return ret;
			i = 32;
			memcpy(g_rec_data+i,g_z18pos.device_id,4);
			i +=4;
			memcpy(g_rec_data+i,g_z18pos.curr_time+3,4);
			i += 4;
			set_4byte_int(record->in_balance,g_rec_data+i);
			i+=4;
			set_3byte_int(record->tx_money,g_rec_data+i);
			i+=3;
			g_rec_data[i] = 0x0A;
			debug_string("write serial sect[%d]\n",(uint16)card_rec->wr_rec_sect);
			ret = z18_write_card(card_rec->wr_block,3,g_rec_data+32);
			if(ret)
			{
				debug_string("sect[%d]block[%d]\n",(uint16)card_rec->wr_rec_sect,(uint16)card_rec->wr_block);
				return ret;
			}
			ret = kng_login_card(g_mycard.phyno,5);
			for(i=0,g_rec_data[15]=0;i<15;++i)
				g_rec_data[15] += g_rec_data[i];
			ret = z18_write_card(block,3,g_rec_data);
			if(ret)
			{
				debug_string("write sect 5\n");
				return ret;
			}
			// ����
			return 0;

		}
		else
		{
			// �ж�д��״̬
			// FIXME : �޸��жϵ�bug
			if(check_last_consume(record))
			{
				// ���±�������������һ�� 
				ret = kng_login_card(g_mycard.phyno,5);
				if(ret)
					return ret;
				ret = z18_write_card(block+1,3,g_rec_data);
				if(ret)
				{
					debug_string("write block[5:21]\n");
					return ret;
				}
				// ���Ѿ�д�ɹ�
				return KNG_POS_REPEAT_CONSUME;
			}
			// �ϴ�д��δ�ɹ������¸���������
			g_mycard.rec_index = g_rec_data[0];
			goto L_CHECK_CARD2;
		}
	}
	else if(c1 == 0)
	{
		// ������������ȡ��ˮ
		goto L_CHECK_CARD;
	}
	else if(c2 == 0)
	{
		// ���ݱ�������ȡ��ˮ
		// ���������󣬿����ǿ������⣬ֱ�Ӹ��»�������
		memcpy(g_rec_data,g_rec_data+16,16);
		goto L_CHECK_CARD;
	}
	else
	{
		// �¿���ֱ�ӿۿ�
		memset(g_rec_data,0xFF,16);
		g_rec_data[0] = 0;
		g_rec_data[1] = CARD_PRC_BEGIN;
		memcpy(g_rec_data+16,g_rec_data,16);
		goto L_CHECK_CARD;
	}
	return KNG_POS_PURSE_ERROR;
}
#else

// 1 ��ʾ�ظ�����, 0 ��ʾ��������
static bit check_card_interval(z18_record_t *record)
{
	if(memcmp(record->pre_tx_time,g_mycard.last_consume_date,3)==0)
	{
		return 1;
	}
	
}

#define do_is_under_interval(_s1,_s2) do { \
	if(_s1 > _s2) \
	{ \
		if(_s1 - _s2 <= g_z18pos.card_interval) return KNG_POS_REPEAT_CONSUME; \
	} else if( _s1 <= _s2) return KNG_POS_REPEAT_CONSUME; \
	}while(0)
	
static int do_check_card_interval(uint8 block,z18_record_t *record)
{
	char ret;
	uint8 i;
	uint32 s1,s2;
#if CHECK_CARD_INVTERVAL

	ret = memcmp(g_mycard.card_comsume_date,g_mycard.last_consume_date,5);
	if(ret==0)
	{
		debug_string("consume date equals\n");
		// �ղŽ��е�����
		if(memcmp(record->pre_device_id,g_z18pos.device_id,4)==0)
		{
			// ��ͬһ̨�豸�ϵ�����
			if(memcmp(g_z18pos.curr_time+1,g_mycard.card_comsume_date,3)<=0)
			{
				s1 = time_2_secs(g_z18pos.curr_time+4);
				s2 = time_2_secs(g_mycard.card_comsume_date+3);
				do_is_under_interval(s1,s2);
			}
		}
	}
	else if(ret>0)
	{
		// ��δд��
		debug_string("not write card\n");
		
	}
	else 
	{
		debug_string("had write card\n");
		// �Ѿ�д������������
		if(memcmp(g_z18pos.curr_time+1,g_mycard.card_comsume_date,3)<=0)
		{
			s1 = time_2_secs(g_z18pos.curr_time+4);
			s2 = time_2_secs(g_mycard.card_comsume_date+3);
			do_is_under_interval(s1,s2);
		}
	}
#endif 
	memset(g_rec_data,0,16);
	memcpy(g_rec_data,g_z18pos.device_id,4);
	memcpy(g_rec_data+4,g_z18pos.curr_time+1,6);
	for(i=0,g_rec_data[15]=0;i<15;++i)
		g_rec_data[15]+=g_rec_data[i];
	if(z18_write_card(block,3,g_rec_data))
	{
		return KNG_WRITE_CARD;
	}
	return 0;
}

#endif // SAVE_CARD_REC

static uint8 do_read_purse(uint8 block,z18_record_t *record)
{
	uint16 ret;
	uint8 buffer1[16];
	// ��Ǯ��
	ret = kng_login_card(g_mycard.phyno,g_mycard.purse_sect);
	if(ret)
	{
		debug_string("login card purse sect\n");
		return KNG_LOGIN_DENY;
	}
	ret = z18_read_card(block,1,buffer1);
	if(ret)
	{
		debug_string("read purse block\n");
		return KNG_READ_CARD;
	}

	if(check_buffer_crc(buffer1,15)==0)
	{
		// �����ɹ�
	}
	else
	{
		// ��ȡ����Ǯ��
		memset(buffer1,0,sizeof buffer1);
		ret = z18_read_card(block+2,1,buffer1);
		if(ret)
		{
			debug_string("read purse backup\n");
			return KNG_READ_CARD;
		}
		if(check_buffer_crc(buffer1,15))
		{
			// Ǯ����
			return KNG_POS_PURSE_ERROR;
		}
	}
	// ȡ�õ�ǰ�����
	get_money_from_buffer(buffer1,&g_mycard.balance,&g_mycard.trade_count);
	//debug_hex(buffer1+5,5);
	hex2bcd(buffer1+5,5,g_mycard.last_consume_date);
	g_mycard.last_consume_date[5] = 0;
	//debug_string("parse date");

#ifndef SAVE_CARD_REC
	ret = z18_read_card(block+1,1,buffer1);
	if(ret)
	{
		debug_string("read index \n");
		return KNG_READ_CARD;
	}
	if(check_buffer_crc(buffer1,15)==0)
	{
		memcpy(record->pre_device_id,buffer1,4);
		memcpy(g_mycard.card_comsume_date,buffer1+4,6);
	}
	else
	{
		memset(record->pre_device_id,0,4);
		memset(g_mycard.card_comsume_date,0,sizeof g_mycard.card_comsume_date);
	}

#endif 	
	return 0;


}
uint8 read_card_purse(z18_record_t *record,card_rec_info_t *card_rec)
{
	uint16 ret;
	uint8 buffer1[16];
	uint8 purse_no,block;
	ret = kng_login_card(g_mycard.phyno,3);
	if(ret)
	{
		debug_string("login card 3 sect\n");
		return KNG_LOGIN_DENY;
	}

	memset(buffer1,0,sizeof buffer1);
	ret = z18_read_card(12,1,buffer1);
	if(ret)
	{
		debug_string("read card 12 block\n");
		return KNG_READ_CARD;
	}
	// Ǯ������
	purse_no = buffer1[1];
	// ��������־
	ret = z18_read_card(14,1,buffer1);
	if(ret)
	{
		debug_string("read blk 14\n");
		return ret;
	}
	g_mycard.black_flag = buffer1[0];
    //debug_string("read blk [%02X]\n",g_mycard.black_flag);
	//bcd2str(buffer1+1,6,g_mycard.black_ver);
	memcpy(g_mycard.black_ver,buffer1+1,6);
	// ��Ǯ��
	g_mycard.purse_sect = purse_no;
	block = purse_no << 2;
	ret = do_read_purse(block,record);
	if(ret)
	{
		debug_string("read purse\n");
		return ret;
	}
	record->in_balance = g_mycard.balance;
#ifdef SAVE_CARD_REC
	// ��ȡ�ϴν�����ϸ�����ˢ��ʱ��
	// ��鿨����״̬
	ret = check_card_process(card_rec,record);
	if(ret)
	{
		debug_string("check card\n");
		return ret;
	}
#else
	ret = do_check_card_interval(block+1,record);
	if(ret)
	{
		debug_string("check card\n");
		return ret;
	}
#endif // SAVE_CARD_REC

	/*
	// ���ˢ��ʱ��
	if(strncmp(g_z18pos.curr_time+2,g_mycard.last_consume_date,6) == 0)
	{
	// �Ƚ�ʱ��
	memset(temp,0,sizeof temp);
	memcpy(temp,g_z18pos.curr_time+8,2);
	min_1 = atoi(temp) * 60; // Сʱ
	memcpy(temp,g_z18pos.curr_time+10,2);
	min_1 += atoi(temp); // ����

	memcpy(temp,g_mycard.last_consume_date+6,2);
	min_2 = atoi(temp) * 60; // Сʱ
	memcpy(temp,g_mycard.last_consume_date+8,2);
	min_2 += atoi(temp); // ����

	if(min_1 - min_2 <= g_z18pos.card_interval)
	{
	return KNG_POS_REPEAT_CONSUME;
	}
	}
	*/
	return 0;

}

static uint8 do_write_purse(z18_record_t *record)
{
	uint8 buffer[16],buffer1[16];
	uint8 crc,notcrc;
	uint8 i,ret,block;
	uint32 card_balance;
	uint16 card_count;

	ret = kng_login_card(g_mycard.phyno,g_mycard.purse_sect);
	if(ret)
	{
		return ret;
	}
	// ����������
	block = g_mycard.purse_sect << 2;

	// ��ȡ��������
	memset(buffer,0,sizeof buffer);
	ret = z18_read_card(block,3,buffer);
	if(ret) return ret;

	for(i = 0,crc=0,notcrc=0;i < 15; ++i)
	{
		crc += buffer[i];
		notcrc |= buffer[i];
	}
	if(crc == buffer[15] && notcrc != 0)
	{
		// ��Ǯ����ȷ
		get_money_from_buffer(buffer,&card_balance,&card_count);
		if(card_balance == record->in_balance - record->tx_money
		   && card_count == record->tx_count)
		{
			// ��Ϊд���ɹ������سɹ�
			return 0;
		}
		// д��Ǯ��
		ret = z18_write_card(block+2,3,buffer);
		if(ret)  return ret;

	}
	else
	{
		// ����Ǯ��
		ret = z18_read_card(block+2,3,buffer);
		if(ret)
		{
			return KNG_READ_CARD;
		}
		for(i = 0,crc=0,notcrc=0;i < 15; ++i)
		{
			crc += buffer[i];
			notcrc |= buffer[i];
		}
		if(crc != buffer[15] || notcrc == 0)
		{
			// ��Ǯ������
			return KNG_POS_PURSE_ERROR;
		}
		// д��Ǯ��
		get_money_from_buffer(buffer,&card_balance,&card_count);
		if(card_balance == record->in_balance - record->tx_money
		   && card_count == record->tx_count)
		{
			// ��Ϊ��Ǯ����ȷ�����سɹ�
			// �������ǲ��������������������
			z18_write_card(block,3,buffer);
			return 0;
		}
	}
	// ������Ǯ��
	set_money_buffer(record->in_balance-record->tx_money,record->tx_count,buffer);

	//debug_hex(g_z18pos.curr_time,6);
	//debug_hex(g_mycard.last_consume_date,6);
	// ϵͳ��ǰ���ڲ��������һ�ν�������
	if(memcmp(g_z18pos.curr_time+1,g_mycard.last_consume_date,3) <= 0)
	{
		// ���µ����ۼ����Ѷ�
		// FIXME : �˴��Ŀ��ṹ����ȷ��Ӧ���ǵ�λ��ǰ
		card_balance = get_3byte_money(buffer+10);
		card_balance += record->tx_money;
		//set_3byte_int(card_balance,buffer+10);
		set_3byte_money(card_balance,buffer+10);
		bcd2hex(g_z18pos.curr_time+1,5,buffer+5);
	}
	else
	{
		// ���ν��׽��Ϊ�����ۼƽ��׽��
		// FIXME : �˴��Ŀ��ṹ����ȷ��Ӧ���ǵ�λ��ǰ
		//set_3byte_int(record->tx_money,buffer+10);
		set_3byte_money(record->tx_money,buffer+10);
		// buffer[5] , YYMMDDHIMI
		bcd2hex(g_z18pos.curr_time+1,5,buffer+5);
	}


	for(i = 0,buffer[15] = 0;i < 15; ++i)
		buffer[15] += buffer[i];

	memset(buffer1,0,sizeof buffer1);
	// д��
	ret = z18_write_card(block,3,buffer);
	// ����
	if(z18_read_card(block,3,buffer1))
	{
		// ���д��Ҳʧ�ܣ�����ʧ��
		if(ret)
			return KNG_WRITE_CARD;
		// ��;�ο�
		return KNG_POS_UNEXPECT_CARD;
	}
	// �ж�д���ɹ�
	if(memcmp(buffer,buffer1,16) == 0)
		return 0;
	else
		return KNG_WRITE_CARD;

}
uint8 write_card_purse(z18_record_t *record,card_rec_info_t *card_rec)
{
	uint8 ret;
	uint8 buf[16];
	ret = kng_login_card(g_mycard.phyno,g_mycard.purse_sect);
	if(ret)
		return ret;
	ret = do_write_purse(record);
	if(ret)
		return ret;
	
#ifdef SAVE_CARD_REC
	// ���±�����
	ret = kng_login_card(g_mycard.phyno,5);
	if(ret)
		return ret;
	
	memset(buf,0xFF,16);
	// FIXME : ��ȡ�����������±�����
	ret = z18_read_card(20,3,buf);
	if(ret)
		return ret;
	/*
	buf[0] = g_mycard.rec_index;
	buf[1] = CARD_PRC_BEGIN;
	for(ret=0,buf[15]=0;ret < 15;++ret)
		buf[15] += buf[ret];
	*/
	ret = z18_write_card(21,3,buf);
	if(ret)
		return ret;
#endif // SAVE_CARD_REC

	return 0;
}

