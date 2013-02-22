#include "reg52.h"
#include "consume.h"
#include "z18pos.h"
#include "stdio.h"
#include <string.h>
#include <absacc.h>
#include <stdarg.h>
#include "intrins.h"
#include ".\Include\DataType.h"
#include ".\Include\LibFuntion.h"
#include "z18pos.h"
#include "crc.h"
#include "mifare_card.h"


uint8 data g_rec_data[64];
static bit g_lcd_flag = 0;



#if 1
static void turn_on_lcd()
{
	if(!g_lcd_flag)
	{
		Lcd_onoff(1);
		//Led_OnOff(1,0);
		g_lcd_flag = 1;
	}

}
#endif


static uint8 check_black_card()
{
    blk_mem_info_t blk;
    uint8 ret;
	// 有黑卡标志 
	if(g_mycard.black_flag != NOMARL_CARD_FLAG)
	{
        debug_string(("card black flag[%02X]\n",(uint16)g_mycard.black_flag));
		return KNG_POS_BLACK_CARD;
	}
#if ENABLE_BLKLST
    if(g_z18pos.blk_begin_addr == 0x00)
    {
        // 未启用黑名单
        return 0;
    }
    // 比较版本号,肯定不是黑卡
    
    if(memcmp(g_z18pos.blk_ver,g_mycard.black_ver,6)<0)
    {
        return 0;
    }
    // 读取黑名单表
    // 计算偏移
    memset(&blk,0,sizeof blk);
    ret = z18pos_calc_blkinfo(g_mycard.card_id,&blk);
    if(ret)
    {
        debug_string(("calc blk info\n"));
        return  ret;
    }
    
    
    if(g_z18pos.blk_begin_addr != blk.offset)
    {
        if(EeSysRead(blk.offset,32,g_z18pos.blk_buffer)!=Z18_OK)
        {
            debug_string(("read blk addr[%ul]\n",blk.offset));
            return KNG_POS_HARDWARE_ERROR;
        }
        g_z18pos.blk_begin_addr = blk.offset;
    }
    if((g_z18pos.blk_buffer[blk.byte_offset] & (1<<(7-blk.bit_offset))) != 0)
    {
        debug_string(("black card\n"));
        return KNG_POS_BLACK_CARD;
    }
#endif 
	return 0;
}
/** 
 * @brief 生成流水号
 * 
 * @param record 
 * 
 * @return 
 */
#if 1
static uint8 get_next_serial_no(z18_record_t *record)
{
	uint16 ret,crc;
	uint32 next_ptr;
	uint8 buffer[64];
	uint8 crc_buff[2];
	uint8 rec_date[7];
	uint8 i,main_error,flag;
	uint8 param_len = 26;
	// 先读取主参数表
	/*
	 * 记流水流程如下：
	 * 1。 先更新流水号值
	 * 2. 写卡
	 * 3. 更新流水状态
	 * 当第2步失败的时候，如果明确没有写到卡上，那这笔流水就直接覆盖掉, 因此我们直接读备块参数
	 */
	memset(buffer,0,sizeof buffer);
	memset(crc_buff,0,sizeof crc_buff);
	main_error = 1;
	ret = EeSysRead(POS_REC_PTR_ADDR,param_len,buffer);
	if(Z18_FAILED == ret)
	{
		debug_string(("read ptr \n"));
		return KNG_POS_HARDWARE_ERROR;
	}
	// 判断crc
	//debug_hex(buffer+8,25);
	crc = GenerateCRC16(buffer,param_len-2);
	//debug_string(("crc[%u]",crc));
	set_2byte_int(crc,crc_buff);
	//debug_hex(crc_buff,2);
	if(memcmp(crc_buff,buffer+24,2) == 0)
	{
		//debug_string(("main sect"));
		// crc 校验正确
		for(i = 0;i < 3;++i)
		{
			if(buffer[i] != ~buffer[3+i])
				break;
			if(buffer[6+i] != ~buffer[9+i])
				break;
		}
		// 保存备参数的内容，以便将来恢复使用
		memcpy(g_z18pos.rec_buffer,buffer,sizeof(g_z18pos.rec_buffer));
		main_error = 0;
		// 在这种情况下因为最后一次写卡失败，主参数表已经被恢复,主备参数一致，这样就不需要再写备参数表
		if(g_z18pos.rec_status == 0)
		{
			//debug_string(("sect backup"));
			// 先备份到备区
			ret = EeSysWrite(POS_REC_BAK_PTR_ADDR,param_len,buffer);
			if(Z18_FAILED == ret)
			{
				debug_string(("write ptr back\n"));
				return KNG_POS_HARDWARE_ERROR;
			}
		}
	}
	if(main_error == 1)
	{
		// 读取备块
		memset(buffer,0,sizeof buffer);
		ret = EeSysRead(POS_REC_BAK_PTR_ADDR,param_len,buffer);
		if(Z18_FAILED == ret)
		{
			debug_string(("read ptr back\n"));
			return KNG_POS_HARDWARE_ERROR;
		}
		//debug_string(("back sect")); 
		memset(crc_buff,0,sizeof crc_buff);
		crc = GenerateCRC16(buffer,24);
		set_2byte_int(crc,crc_buff);
		if(memcmp(crc_buff,buffer+24,2) != 0)
		{
			debug_string(("back ptr crc\n"));
			// 备块错误
			return KNG_POS_PARAM_ERROR;
		}
		// crc 校验正确
		for(i = 0;i < 3;++i)
		{
			if(buffer[i] != ~buffer[3+i])
			{
				debug_string(("bak ptr crc\n"));
				return KNG_POS_PARAM_ERROR;
			}
			if(buffer[6+i] != ~buffer[9+i])
			{
				debug_string(("bak ptr crc\n"));
				return KNG_POS_PARAM_ERROR;
			}
		}
		// 保存备参数的内容，以便将来恢复使用
		memcpy(g_z18pos.rec_buffer,buffer,sizeof(g_z18pos.rec_buffer));
	}
	// 写主区
	record->serial_no = get_4byte_int(buffer+12);
	g_z18pos.serial_no = record->serial_no;
	g_z18pos.rec_wr_ptr = get_3byte_int(buffer);
	g_z18pos.rec_rd_ptr = get_3byte_int(buffer+6);
	g_z18pos.rec_ptr_flag = buffer[23];
	flag = g_z18pos.rec_ptr_flag;
	// 如果写记录指针与读记录指针相等，则认为记录已满
	
	if(z18pos_check_rec_full())
	{
		// flash 已经写满，重新开始
		debug_string(("record full\n"));
		return KNG_POS_REC_FULL;	
	}
	

	if(g_z18pos.rec_rd_ptr == 0x00)
	{
		g_z18pos.rec_rd_ptr = POS_RECORD_BEGIN_ADDR;
		set_3byte_int(POS_RECORD_BEGIN_ADDR,buffer+6);
		calc_not(buffer+6,3,buffer+9);
	}
	next_ptr = g_z18pos.rec_wr_ptr + POS_REC_LEN;
	if(next_ptr >= POS_RECORD_END_ADDR)
	{
		// flash 写到最后 ，需要从头开始
		next_ptr = POS_RECORD_BEGIN_ADDR;
		if(next_ptr <= g_z18pos.rec_rd_ptr )
            flag = 0x00;
        else
            flag = 0xFF;
	}
    // 当前流水记录的位置
    record->wr_ptr = g_z18pos.rec_wr_ptr;
	//debug_string(("get serial no"));
	// 更新到下一条写记录地址
	set_3byte_int(next_ptr,buffer);
	calc_not(buffer,3,buffer+3);

	// 累计金额
	g_z18pos.total_money = get_4byte_int(buffer+16);
	memcpy(rec_date,buffer+20,3);
    /*
	if(memcmp(g_z18pos.curr_time+1,rec_date,3) >0)
	{
		// 更新到下一天
		memcpy(buffer+20,g_z18pos.curr_time+1,3);
		// 写累计金额到前日累计金额
		ret = update_pre_total(g_z18pos.total_money);
		if(ret)
		{
			debug_string(("update pre money\n"));
			return ret;
		}
		g_z18pos.total_money = record->tx_money;
		debug_string(("money[%lu][%lu]",g_z18pos.total_money,record->tx_money));
		memcpy(buffer+20,g_z18pos.curr_time+1,3);
	}
	else
	{
		g_z18pos.total_money += record->tx_money;
		debug_string(("money[%lu][%lu]",g_z18pos.total_money,record->tx_money));
	}
	*/
	g_z18pos.total_money += record->tx_money;
	memcpy(g_z18pos.last_tx_date,buffer+20,3);
	// 更新当日累计金额
	set_4byte_int(g_z18pos.total_money,buffer+16);
	// 流水号
	set_4byte_int(record->serial_no+1,buffer+12);
	g_z18pos.serial_no++;
    g_z18pos.rec_wr_ptr = next_ptr;
	buffer[23] = flag;
	// 计算 crc
	crc = GenerateCRC16(buffer,24);
	set_2byte_int(crc,buffer+24);

    //debug_string(("wr ptr[%lu]rd[%lu]serial[%lu]\n",g_z18pos.rec_wr_ptr,g_z18pos.rec_rd_ptr,g_z18pos.serial_no));
	ret = EeSysWrite(POS_REC_PTR_ADDR,param_len,buffer);
	if(ret == Z18_OK)
	{
        g_z18pos.rec_ptr_flag = flag;
		return 0;
	}
	
	debug_string(("update ptr error\n"));
	return KNG_POS_HARDWARE_ERROR;	
}
#else
static uint8 get_next_serial_no(z18_record_t *record)
{
	record->serial_no = 1;
	record->wr_ptr = POS_RECORD_BEGIN_ADDR;
	return 0;
}
#endif
/** 
 * @brief 当写卡失败时，恢复上一次流水号
 * 
 * @return 
 */
static uint8 reverse_serial_no()
{
	uint8 ret;
	ret = EeSysWrite(POS_REC_PTR_ADDR,26,g_z18pos.rec_buffer);
	if(Z18_OK == ret)
	{
        
		return 0;
	}
    debug_string(("reverse serial\n"));
	return KNG_POS_HARDWARE_ERROR;
}

static uint8 record_serial(z18_record_t *record ,uint8 flag,uint8 data *buffer)
{
	uint8 offset,ret;
	// 根据 flag 的值来控制业务流程
	// 1 : 记录新的流水
	// 2 : 更新流水状态
	// 新记录流水
	if(flag==1)
	{
		offset = 0;
		// 版本号
		buffer[offset] = record->ver;
		offset++;
		// 设备物理 ID	
		memcpy(buffer+offset,g_z18pos.device_id,4);
		offset+=4;
		// 流水号
		set_4byte_int(record->serial_no,buffer+offset);
		offset+=4;
		// 交易卡号
		set_3byte_int(record->card_id,buffer+offset);
		offset +=3;
		// 入卡金额
		set_4byte_int(record->in_balance,buffer+offset);
		offset+=4;
		// 交易金额
		set_3byte_int(record->tx_money,buffer+offset);
		offset+=3;
		// 交易次数
		memcpy(buffer+offset,(uint8*)&record->tx_count,2);
		offset+=2;
		// 交易时间
		//str2bcd(record->tx_datetime,12,buffer+offset);
		memcpy(buffer+offset,record->tx_datetime,6);
		offset+=6;
		// 交易标志
		buffer[offset++] = record->tx_mark;
		// 交易类型
		buffer[offset++] = record->tx_type;
		// 钱包号
		buffer[offset++] = record->purse_no;
		// 前一笔流水
#if SAVE_CARD_REC
		memcpy(buffer+offset,record->pre_device_id,4);
		offset+=4;
		memcpy(buffer+offset,record->pre_tx_time,4);
		offset+=4;
		set_4byte_int(record->pre_in_balance,buffer+offset);
		offset+=4;
		set_3byte_int(record->pre_tx_money,buffer+offset);
		offset+=3;
		buffer[offset++] = record->pre_tx_mark;
#else
		memset(buffer+offset,0x00,16);
		offset+=16;
#endif
		// 15 byte 保留
		offset+=15;
		// crc offset = 61
		record->tx_crc = GenerateCRC16(buffer,offset);
		set_2byte_int(record->tx_crc,buffer+offset);
		offset+=2;
		// 状态
		buffer[offset++] = record->tx_status;

		if(offset != POS_REC_LEN)
		{
			//debug_string(("error serial[%d]\n",(uint16)offset));
			return KNG_POS_PARAM_ERROR;
		}
		//record->wr_ptr = g_z18pos.rec_wr_ptr;	
		//debug_string(("wr ptr[%ld]",g_z18pos.rec_wr_ptr));
		//ret = z18pos_write_eeprom(record->wr_ptr,offset,3,buffer);
		ret = EeSysWrite(record->wr_ptr,offset,buffer);
		if(ret != Z18_OK)
		{
            //debug_string(("record serial[%lu]\n",g_z18pos.rec_wr_ptr));
			return ret;
		}
		//get_next_wr_ptr();
		return 0;
	}
	else
	{
		// 更新交易标志
		buffer[27] = record->tx_mark;
		// 更新 crc 
		record->tx_crc = GenerateCRC16(buffer,POS_REC_LEN-3);
		set_2byte_int(record->tx_crc,buffer+61);
		// 更新 flash
		ret = EeSysWrite(record->wr_ptr,POS_REC_LEN,buffer);
		if(ret != Z18_OK)
		{
            debug_string(("upd rec,[%lu]\n",record->wr_ptr));
			return ret;
		}
		return 0;
		// 更新状态信息
	}
}


/** 
 * @brief 消费
 */
static uint8 consume_card()
{
	uint8 ret;
	uint8 phyno[4];
    uint8 audio_idx[MAX_CARD_GROUP]= {AU_DINGDONG,AU_TEACHER_CARD,AU_STUDENT_CARD,AU_STAFF_CARD,AU_TEMP_CARD
		,AU_FREE_CARD};
	uint32 money;
	float f_money;
	uint8 money_str[10];
	uint8 balance_str[10];
	z18_record_t xdata record;
	card_rec_info_t card_rec;

	memset(money_str,0,sizeof money_str);
	memset(balance_str,0,sizeof balance_str);
	// 当寻卡成功，才进入此函数
	// 1. 获取卡物理ID
	memset(phyno,0xFF,sizeof phyno);
	memset(&record,0xFF,sizeof record);
	memset(&g_rec_data,0xFF,sizeof g_rec_data);
	
	ret = kng_read_phyno(phyno);
	if(ret)
	{
		// 读卡失败
		return ret;
	}
	if(z18pos_check_rec_full())
	{
		//debug_string(("record full[%lu][%lu]\n",g_z18pos.rec_rd_ptr,g_z18pos.rec_wr_ptr));
		return KNG_POS_REC_FULL;
	}

	ret = read_card_info(phyno);
	if(ret)
	{
		return ret;
	}
	//debug_string(("r[%d][%d]\n",(uint16)g_mycard.card_type,(uint16)g_z18pos.card_fee[g_mycard.card_type-1]));
	//debug_hex(g_z18pos.card_fee,256);
	money = g_z18pos.base_money * g_z18pos.card_fee[g_mycard.card_type-1] / 100;

	memset(&card_rec,0,sizeof card_rec);
	record.card_id = g_mycard.card_id;
	memcpy(record.device_id,g_z18pos.device_id,4);
	memcpy(record.tx_datetime,g_z18pos.curr_time+1,6);
	record.tx_money = money;
	ret = read_card_purse(&record,&card_rec);
	if(ret)
	{
		//if(KNG_POS_REPEAT_CONSUME == ret)
		//	KNG_AUDIO(AU_REPEAT,Z18_AUDIO_DELAY);
		return ret;
	}

	if(g_mycard.balance < money)
	{
		// 卡余额不足
		//KNG_AUDIO(AU_ADD_MONEY,Z18_AUDIO_DELAY);
		return KNG_POS_PURSE_LACK;
	}

	record.in_balance = g_mycard.balance;
	record.purse_no = 0;
	record.tx_count = g_mycard.trade_count + 1;
	record.tx_mark = REC_INVAL;
	record.tx_type = 1;
	record.tx_status = 1;
	// 检查是否黑卡
	ret = check_black_card();
	if(ret)
	{
		if(KNG_POS_BLACK_CARD == ret)
		{
			// 黑卡流水
			record.tx_mark = 0x00;
			record.tx_status = 2;
			record.tx_money = 0; //不计交易金额
		}
		else return ret;
	}

	ret = get_next_serial_no(&record);
	if(ret)
	{
		debug_string(("get next serial\n"));
		return ret;
	}
	//debug_string(("serial[%ld]",record.serial_no));
	// 记流水
	memset(g_rec_data,0xFF,sizeof g_rec_data);
	ret = record_serial(&record,1,g_rec_data);
	if(ret)
	{
		//记录流水失败
		debug_string(("record serial\n"));
		return ret;
	}
	if(record.tx_mark == 0x00)
	{
		// 黑卡报警
		print_line(1,1,"黑卡");
		turn_on_lcd();
		//KNG_AUDIO(AU_LOST_CARD,Z18_AUDIO_DELAY);
		return KNG_POS_BLACK_CARD;
	}

	// 写卡
	ret = write_card_purse(&record,&card_rec);
	//print_line(3,10,"write ret[%d]",(uint16)ret);
	// 写卡完成后提示金额
	//debug_string(("1[%ld]2[%d]",record.in_balance,money));
	f_money = record.in_balance - money;
	// debug_string(("float[%f]",f_money));
	d4u5_str(f_money/100.0,balance_str);
	d4u5_str(money/100.0,money_str);
	if(money == 0) print_line(1,0,"免费卡");
	else print_line(1,0,"扣款 %s 元",money_str);
	print_line(2,0,"余额 %s 元",balance_str);
	print_line(3,0,"流水号[%ld]",record.serial_no);
	if(ret)
	{
		if(KNG_POS_UNEXPECT_CARD == ret)
		{
			// 中途拔卡
			record.tx_mark = 0x02;
			record_serial(&record,3,g_rec_data);
			kng_sleep(10);
		}
		else
		{
			// 流水无效，下一笔流水直接覆盖
			g_z18pos.rec_status = 1;
			// 恢复主参数表
			reverse_serial_no();
			print_line(3,10,"请重刷");
		}
		turn_on_lcd();
		//KNG_AUDIO(AU_TRY_AGAIN,Z18_AUDIO_DELAY);
		return ret;
	}
	else
	{
		// 更新当天营业额
	}
	// 写卡成功
	record.tx_mark = 0x0A;
	record.tx_status = 2;
	record_serial(&record,2,g_rec_data);
	g_z18pos.rec_status = 0; // 流水写成功	
	// 更新流水状态
	turn_on_lcd();
	//if(money != 0)
	//{
		//KNG_AUDIO(AU_DINGDONG,Z18_AUDIO_DELAY);
	if(g_mycard.card_type >= 93 && g_mycard.card_type <= 96)
		ret = 0;
	else
		ret = g_z18pos.card_group[g_mycard.card_type-1];
	KNG_AUDIO(audio_idx[ret],Z18_AUDIO_DELAY);
	//debug_string(("serial[%ld]",record.serial_no));
	//kng_sleep(10);
	//}
	//else
	//{
	//	KNG_AUDIO(AU_FREE_CARD,Z18_AUDIO_DELAY);
	//	kng_sleep(10);
	//}
	return 0;

}
uint8 read_card_loop()
{	
	uint8 ret;
	bit flag1;
	uint16 tick;
	cls();
	Display(0,0,g_z18pos.welcome_msg,0);
	tick = 0;
	g_lcd_flag = 0;
	flag1 = 0;
	Led_OnOff(1,0);
	while(1)
	{
		clr_dog();
		ret = GetKeyVal(1);
		if(ret != 0xFF)
			Lcd_onoff(1);
		if(ret == KEY_ESC)
			break;
		ret = mif_request(0);
		if(flag1)
		{
			cls();
			Display(0,0,g_z18pos.welcome_msg,0);
			flag1 = 0;
		}

		if(ret == Z18_FAILED)
		{
			z18pos_check_consume();
			kng_sleep(1);
			tick+=3;
			if(tick >= 60)
			{
				tick = 0;
				cls();
				Display(0,0,g_z18pos.welcome_msg,0);
				//Led_OnOff(1,1);
				Lcd_onoff(0);
				g_lcd_flag = 0;
               
	            		ReadRtcTime(g_z18pos.curr_time);
			}
			if(z18pos_check_coll_interval() && get_serial_count()>0)
			{
				KNG_AUDIO(AU_NEED_COL,Z18_AUDIO_DELAY);
				//print_error(KNG_POS_EXPIRED_COLL,NULL);
				return KNG_POS_EXPIRED_COLL;
			}
		}
		else
		{
			InitRtcTime();
			ReadRtcTime(g_z18pos.curr_time);
			memset(&g_mycard,0,sizeof g_mycard);
			g_mycard.last_login_sect = 0xFF;
			tick = 0;
			// 寻卡成功
			ret = consume_card();
            #if DEBUG
			if(ret>0)
			{
				debug_string(("consume [%d]\n",(uint16)ret));
			}
            #endif
			switch(ret)
			{
			case KNG_POS_PARAM_ERROR:
			case KNG_POS_HARDWARE_ERROR:
				print_error(ret,NULL);
				break;
			case KNG_POS_SUCCESS:
				//kng_sleep(1);
				break;
			case KNG_POS_REC_FULL:
			    	KNG_AUDIO(AU_NEED_COL,Z18_AUDIO_DELAY);
				kng_sleep(1);
				break;
			case KNG_POS_NO_RIGHT:
			case KNG_POS_EXPIRED_CARD:
			case KNG_POS_UNREAD_CARD:
			case KNG_POS_NOT_SUPP_CARDTYPE:
			    	KNG_AUDIO(AU_INVALID_CARD,Z18_AUDIO_DELAY);
				kng_sleep(1);
				break;
			case KNG_POS_REPEAT_CONSUME:
				KNG_AUDIO(AU_REPEAT,Z18_AUDIO_DELAY_100);
				//kng_sleep(10);
				break;
			case KNG_POS_PURSE_LACK:
				KNG_AUDIO(AU_ADD_MONEY,Z18_AUDIO_DELAY);
				//kng_sleep(10);
				break;
			case KNG_POS_BLACK_CARD:
				KNG_AUDIO(AU_LOST_CARD,Z18_AUDIO_DELAY);
				kng_sleep(1);
				break;
			default:
				break;
			}
			flag1 = 1;
		}
	}
	return 0;
}

uint16 get_serial_count()
{
	uint16 cnt;
    debug_string(("cnt[%lu][%lu]\n",g_z18pos.rec_wr_ptr , g_z18pos.rec_rd_ptr));
	if(g_z18pos.rec_wr_ptr > g_z18pos.rec_rd_ptr)
	{
		if(g_z18pos.rec_rd_ptr == 0)
			return (g_z18pos.rec_wr_ptr-POS_RECORD_BEGIN_ADDR)>>6;
		else
			return ((g_z18pos.rec_wr_ptr - g_z18pos.rec_rd_ptr) >> 6);
	}
	else if(g_z18pos.rec_wr_ptr < g_z18pos.rec_rd_ptr)
	{
		// 
		cnt = (g_z18pos.rec_wr_ptr - POS_RECORD_BEGIN_ADDR)>>6;
		cnt += ((POS_RECORD_END_ADDR - g_z18pos.rec_rd_ptr) >>6);
		return cnt;
	}
	else
	{
		if(g_z18pos.rec_ptr_flag == 0x00)
		{
			// 记录已满
			return POS_MAX_REC_CNT;
		}
        return 0;
	}
}


uint32 get_record_addr(uint32 serial_no)
{
	uint32 addr,begin_serial;
	addr = 0;
	if(serial_no > g_z18pos.serial_no)
	{
		return 0;
	}
	// 起始流水号
	begin_serial = g_z18pos.serial_no - ((g_z18pos.rec_wr_ptr-POS_RECORD_BEGIN_ADDR)>>6);
	
    
	//addr = g_z18pos.serial_no - ((g_z18pos.rec_wr_ptr-POS_RECORD_BEGIN_ADDR)>>6);
	debug_string(("addr[%lu][%lu],[%lu][%lu]\n",begin_serial,serial_no,g_z18pos.rec_rd_ptr,g_z18pos.rec_wr_ptr));
	if(begin_serial <= serial_no)
	{
		// 在 wr ptr 之前
		addr = POS_RECORD_BEGIN_ADDR + ((serial_no - begin_serial) << 6);
	}
	else
	{
		//
		addr = begin_serial - ((POS_RECORD_END_ADDR - g_z18pos.rec_wr_ptr)>>6);
		if(serial_no < addr)
		{
			return 0;
		}
		addr = ((serial_no - addr)<<6) + g_z18pos.rec_wr_ptr;
	}
    debug_string(("serial addr[%lu]\n",addr,g_z18pos.rec_rd_ptr,g_z18pos.rec_wr_ptr));
	return addr;
}

uint8 update_record_read_ptr()
{
	uint32 addr;
	uint16 crc_code;
	uint8 flag;
	if(EeSysRead(POS_REC_PTR_ADDR,26,g_global_buf+900)!=Z18_OK)
	{
		return KNG_POS_HARDWARE_ERROR;
	}

	if(!check_buf_crc(g_global_buf+900,24))
	{
		return KNG_CRC_ERROR;
	}

	calc_not(g_global_buf+906,3,g_global_buf+1000);
	if(memcmp(g_global_buf+909,g_global_buf+1000,3) != 0)
	{
		return KNG_POS_PARAM_ERROR;
	}
	// 读记录指针
	addr = get_3byte_int(g_global_buf+906);

	//debug_string(("read ptr[%lu]\n",addr));
	flag = g_z18pos.rec_ptr_flag;
	// rec_rd_ptr 指向的是最后一次读取的流水地址，下次读取的是下一条记录
	debug_string(("upd ptr[%lu][%lu]\n",addr,g_z18pos.rec_wr_ptr));
	if(addr < g_z18pos.rec_wr_ptr)
	{
		if(addr == 0x00)
		{
			// 没有流水
			return KNG_POS_NO_RECORD;
		}
		else
			addr += POS_REC_LEN;
	}
	else if(addr == g_z18pos.rec_wr_ptr)
	{
		if(g_z18pos.rec_ptr_flag == 0x00)
		{
			addr += POS_REC_LEN;
			if(addr >= POS_RECORD_END_ADDR)
			{
				addr = POS_RECORD_BEGIN_ADDR;
                flag = 0xFF;
			}
		}
		else
		{
            
			return KNG_POS_NO_RECORD;
		}
	}
	else 
	{
		if(addr + POS_REC_LEN >= POS_RECORD_END_ADDR)
		{
			addr = POS_RECORD_BEGIN_ADDR;
			flag = 0xFF;
		}
		else
		{
			addr += POS_REC_LEN;
		}
	}
    if(addr <= g_z18pos.rec_wr_ptr)
        flag = 0xFF;
    else
        flag = 0x00;
	set_3byte_int(addr,g_global_buf+906);
	calc_not(g_global_buf+906,3,g_global_buf+909);
	g_global_buf[923] = flag;
	// calc crc 
	crc_code = GenerateCRC16(g_global_buf+900,24);
	set_2byte_int(crc_code,g_global_buf+924);
	if(EeSysWrite(POS_REC_PTR_ADDR,26,g_global_buf+900) != Z18_OK)
	{
		return KNG_POS_HARDWARE_ERROR;
	}
	if(EeSysWrite(POS_REC_BAK_PTR_ADDR,26,g_global_buf+900) != Z18_OK)
	{
		return KNG_POS_HARDWARE_ERROR;
	}
	g_z18pos.rec_ptr_flag = flag;
	g_z18pos.rec_rd_ptr = addr;
	return 0;
}
/*
uint8 get_next_wr_ptr()
{
	if(g_z18pos.rec_wr_ptr + POS_REC_LEN >= POS_RECORD_END_ADDR)
	{
		g_z18pos.rec_wr_ptr = POS_RECORD_BEGIN_ADDR;
	}
	else 
	{
		g_z18pos.rec_wr_ptr += POS_REC_LEN;
	}
	return 0;
}
*/

