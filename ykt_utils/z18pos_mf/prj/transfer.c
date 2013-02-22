#include "reg52.h"
#include "Include/LibFuntion.h"
#include <string.h>
#include "stdio.h"
#include <stdlib.h>
#include "crc.h"
#include "communication.h"
#include "transfer.h"
#include "z18pos.h"
#include "consume.h"
#if USE_GPRS
#include "gprs.h"
#endif

#define KNG_COMM_CMD 0xC5 // 获取设备物理ID及时钟
#define KNG_READ_EEPROM 0xA1
#define KNG_WRITE_EEPROM 0xA2
#define KNG_RESET_PARAM 0xC1
#define KNG_SET_PHYID 0xC2
#define KNG_GET_PHYID 0xC5
#define KNG_SET_KEY 0xC3
#define KNG_CHECK_CLOCK 0xC4
#define KNG_CLEAR_SERIAL 0xB1
#define KNG_SET_CONSUME_PARAM 0xB2
#define KNG_ADDDEL_BLK 0xB3
#define KNG_CARD_RIGHT 0xB4
#define KNG_COL_SERI 0x55
#define KNG_COL_SERI_CONFIRM 0x56
#define KNG_SET_WELCOME_MSG 0xB6
#define KNG_UPDATE_COL_DATE 0xB7
#define KNG_GET_BLKVER 0xB5
#define KNG_SET_SVRIP  0xB8
#define KNG_SET_CARDGRP 0xB9


// buffer data index
#define BUF_CMD 3  // 指令码索引
#define BUF_PARAM 4 // 指令参数索引
#define BUF_PARAM2 5 // 指令参数索引
#define BUF_REQ_DATA 6 // 请求数据索引
#define BUF_REQ_DATA1 7 // 请求数据索引
#define BUF_RET 4 // 应答码索引
#define BUF_RESP_DATA 6 // 应答数据索引


static uint8 g_status_sym[] = {'|','/','-','\\'};

#define RESP_HEAD_LEN 3

static uint8 do_pack_cmd_buf(uint8 *buf,uint8 datalen,bit crc)
{
	uint16 len;
	buf[0] = STX2;
	len = 0;
	// debug_string(("datalen[%d]\n",(uint16)datalen));
	if(datalen>0)
	{
		// CMD + RET + LEN = 3 byte
		len = 3 + datalen;
		buf[5] = (uint8)datalen;
		if(crc)
		{
			buf[RESP_HEAD_LEN+len] = calc_sum(buf+RESP_HEAD_LEN,len);
			len += 1;
		}
		buf[RESP_HEAD_LEN+len++] = ETX2;
		set_2byte_int(len,buf+1);
	}
	else
	{
		len = 2;
		if(crc)
		{
			buf[5] = calc_sum(buf+3,len);
			len++;
			buf[2] = 4;
		}
		else
			buf[2] = 3;
		buf[1] = 0;
        buf[RESP_HEAD_LEN+len++] = ETX2;
	}
	
	return (uint8)len+RESP_HEAD_LEN;
}
static bit do_pack_cmd_extbuf(COMM_TYPE_T *comm,uint16 datalen,bit crc)
{
	uint16 len;
	comm->buffer[0] = STX2;
	comm->buf_begin = 0;
	len = 0;
	if(datalen>0)
	{
		// CMD + RET + LEN = 3 byte
		len = 3 + datalen;
		if(datalen >= 256)
		{
			len++;
			comm->buffer[5] = 0x00;
			comm->buffer[6] = (uint8)(datalen - 256);
			// 包头长 7 byte
			comm->buflen = 7;
			
		}
		else
		{
			comm->buffer[5] = (uint8)datalen;
			// 包头长 6 byte
			comm->buflen = 6;
		}
		if(crc)
		{
			comm->ext_buffer[3+len] = calc_sum(comm->ext_buffer,len);
			len += 1; // add crc code
			comm->ext_buf_len++;
		}
		comm->ext_buffer[comm->ext_buf_len]=ETX2;
		comm->ext_buf_len++;
		len++;
		set_2byte_int(comm->buflen-3+comm->ext_buf_len,comm->buffer+1);
		return 1;
	}
	else
	{
		return 0;
	}
}
static bit do_check_cmd_cuf_crc(COMM_TYPE_T *comm)
{
	/*
	uint16 crc_code;
	uint8 crc_buf[2];
	crc_code = GenerateCRC16(buf,len);
	set_2byte_int(crc_code,crc_buf);
	return (memcmp(buf+len,crc_buf,2)==0) ? 1 : 0;
	*/
	uint8 crc_code;
	uint16 len;
	if(comm->use_ext)
	{
		// crc_code = calc_sum(comm->buffer+3,61);
		// crc_code = calc_sum2(comm->ext_buffer,comm->ext_buf_len-2,crc_code);
		crc_code = calc_sum(comm->ext_buffer,comm->ext_buf_len-2);
		//debug_string("ext,[%02X][%d][%02X][%02X]\n",(uint16)comm->ext_buffer[0],
		//			 comm->ext_buf_len,(uint16)comm->ext_buffer[comm->ext_buf_len-2],
		//			 (uint16)crc_code);
		//debug_hex(comm->ext_buffer,comm->ext_buf_len);
		return (comm->ext_buffer[comm->ext_buf_len-2] == crc_code) ? 1 : 0;
	}
	else
	{
		len = get_2byte_int(comm->buffer+1);
		crc_code = calc_sum(comm->buffer+3,len-2);
		return (comm->buffer[len-2+3] == crc_code) ? 1 : 0;
	}
}
/*
static bit do_wait_key(uint16 timeout)
{
	uint8 key;
	do{
		key = GetKeyVal(1);
		if(key == KEY_ESC)
			return 1;
		kng_sleep(1);
	}while(--timeout>0);
	return 0;
}
*/

uint8 do_update_blksheet(uint8 *card_data)
{
    uint32 card_id;
    uint8 blk_bit;
    blk_mem_info_t blk;
    card_id = get_3byte_int(card_data);
    if(card_id==0)
        return KNG_POS_PARAM_ERROR;

    memset(&blk,0,sizeof blk);
    if(z18pos_calc_blkinfo(card_id,&blk))
        return KNG_POS_PARAM_ERROR;
    // 跟新卡号
    if(EeSysRead(blk.offset,32,g_global_buf)!= Z18_OK)
        return KNG_POS_HARDWARE_ERROR;

    blk_bit = 0x01 << (7-blk.bit_offset);
    if(card_data[3] == 0x00) // 挂失
    {
        if(blk_bit & g_global_buf[blk.byte_offset] != 0)
            return 0;
        g_global_buf[blk.byte_offset] |= blk_bit;
    }
    else // 解挂
    {
        if(blk_bit & g_global_buf[blk.byte_offset]  == 0)
            return 0;
        g_global_buf[blk.byte_offset] &= ~blk_bit;
       
    }

    
    if(EeSysWrite(blk.offset,32,g_global_buf) != Z18_OK)
    {
        return KNG_POS_HARDWARE_ERROR;
    }
    memcpy(g_z18pos.blk_buffer,g_global_buf,32);
    g_z18pos.blk_begin_addr = blk.offset;
    return 0;
    
}
uint8 do_update_blksheet_ver(uint8 *blkver)
{
    if(EeSysRead(POS_BLKVER_ADDR,10,g_global_buf)!=Z18_OK)
        return KNG_POS_HARDWARE_ERROR;
    if(memcmp(g_global_buf,blkver,6)==0)
    {
        if(g_global_buf[7] == 0x55 && g_global_buf[8] == 0xAA)
        {
            // 不用更新
            return 0;
        }
    }
    memcpy(g_global_buf,blkver,6);
    g_global_buf[6] = calc_sum(g_global_buf,6);
    g_global_buf[7] = 0x55;
    g_global_buf[8] = 0xAA;
    if(EeSysWrite(POS_BLKVER_ADDR,10,g_global_buf)!= Z18_OK)
    {
        return KNG_POS_HARDWARE_ERROR;
    }
    // 保存黑名单版本号
    memcpy(g_z18pos.blk_ver,g_global_buf,6);
    return 0;
    
}
static uint8 do_setting_pos(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
	uint8 cmd, ret,param;
	uint32 addr,serial_no;
	uint8 send_len;
	uint16 crc_code,len,len1;
	bit crc,flag1,flag2;
	comm->buffer = g_rec_data;
	comm->buffer2 = g_rec_data + 32;
	comm->ext_buffer = g_global_buf;
	comm->use_ext = 0;
	// set pack head
	comm->timeout = 5;
	comm->bufmaxlen=32;
    //print_line(0,0,"recv ptr[%04X]",op->recv_request);
    //print_line(1,30,"send ptr[%04X]",op->send_data);
	print_line(0,10,"waitting...");
	debug_string(("begin request...\n"));
#if 1
	do{
		comm->timeout = 10;
		comm->use_ext = 0;
		//if(!op->recv_data(comm,comm->bufmaxlen))
		if(op->recv_request(comm)==0)
		{
			if(z18pos_wait_key(KEY_ESC,3))
				return KNG_POS_USER_CANCEL;
			continue;
		}
		comm->buflen = 32;
		flag2 = 0;
		crc = 0;
		len = 0x00;
		//debug_hex(comm->buffer,recv_len);
		// 如果是初始化命令，处理业务流程
		cmd = comm->buffer[BUF_CMD];
		param = comm->buffer[BUF_PARAM];
		//debug_string(("exec cmd[%d]",(uint16)cmd));
		print_line(1,0,"process...");
		switch(cmd)
		{
		case KNG_COMM_CMD:
			// 初始化POS机
			// TODO : 判断是不是POS机在正常工作下被初始化
			param = comm->buffer[BUF_PARAM];
			if((param & 0x01) != 0)
			{
				ret = EeSysRead(POS_PHYID_ADDR,16,comm->buffer2);
				if(ret!=Z18_OK)
				{
					ret = KNG_POS_HARDWARE_ERROR;
					break;
				}
				memcpy(comm->buffer+BUF_RESP_DATA,comm->buffer2,4);
				len += 4;
				memcpy(g_z18pos.device_id,comm->buffer2,4);
			}
			if((param & 0x02) != 0)
			{
				//InitRtcTime();
				if(ReadRtcTime(comm->buffer2) != Z18_OK)
				{
					ret = KNG_POS_HARDWARE_ERROR;
					break;
				}
				memcpy(comm->buffer+BUF_RESP_DATA+len,comm->buffer2,7);
				len += 7;
			}
			crc = 1;
			ret = 0;
			break;
		case KNG_SET_PHYID:
			if(comm->buffer[BUF_PARAM] != 0x99 
			   || comm->buffer[BUF_PARAM+1] != 0x08)
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
            /*
			if(memcmp(g_z18pos.device_id,comm->buffer+BUF_REQ_DATA,4)!=0)
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
			*/
			// TODO : check crc
			memcpy(comm->buffer2,comm->buffer+BUF_REQ_DATA+4,4);
			calc_not(comm->buffer2,4,comm->buffer2+4);
			ret = EeSysWrite(POS_PHYID_ADDR,8,comm->buffer2);
			if(ret != Z18_OK)
			{
				ret = KNG_POS_HARDWARE_ERROR;
				break;
			}
			memcpy(g_z18pos.device_id,comm->buffer2,4);
			print_line(1,1,"设置物理ID成功");
			ret = 0;
			break;
		case KNG_CHECK_CLOCK:
			memcpy(comm->buffer2,comm->buffer+BUF_CMD,12);
			//debug_hex(comm->buffer2,12);
			if(!do_check_cmd_cuf_crc(comm))
			{
				//debug_string(("time check crc err"));
				print_line(1,3,"校准时钟超时");
				ret =  KNG_POS_TIMEOUT;
				break;
			}
			//InitRtcTime();
			if(WriteRtcTime(comm->buffer+BUF_REQ_DATA))
			{
				print_line(1,3,"校准时钟成功");
				ret = 0;
			}
			else
				ret = 0xFF;
			break;
		case KNG_SET_KEY:
			if(!do_check_cmd_cuf_crc(comm))
			{
				ret = KNG_CRC_ERROR;
				break;
			}
			if(param != 1 && param != 2)
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
			param = comm->buffer[BUF_PARAM2];
			if(param != 0x00 && param != 0x01)
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
			len = comm->buffer[BUF_PARAM2+1];
			if(len != 14)
			{
				ret = KNG_COM_PACK_INV;
				break;
			}
			// 数据长度
			ret = EeSysRead(POS_WORKKEY_ADDR,24,comm->buffer2);
			if(Z18_OK != ret)
			{
				ret = KNG_POS_HARDWARE_ERROR;
				break;
			}
			ret = 0x01;
			flag1 = 1;
			if(comm->buffer2[22] == 0x55 && comm->buffer2[23] == 0xAA)
			{
				if(memcmp(comm->buffer2+6,comm->buffer+BUF_PARAM2+1+6,8)==0)
				{
					// 密钥一致，不用更新
					flag1 = 0;
				}
				// 设备中的版本号大于等于指令中的版本号，不更新
				if(memcmp(comm->buffer2,comm->buffer+BUF_REQ_DATA1,6)>=0)
				{
					flag1 = 0;
				}
			}

			if(flag1)
			{
				// 6 byte 版本号 + 8 byte 密钥
				memcpy(comm->buffer2,comm->buffer+BUF_PARAM2+2,14);
				// 备份密钥
				memcpy(comm->buffer2+14,comm->buffer2+6,8);
				comm->buffer2[22] = 0x55;
				comm->buffer2[23] = 0xAA;
				if(EeSysWrite(POS_WORKKEY_ADDR,24,comm->buffer2) != Z18_OK)
				{
					debug_string(("write error,0x40\n"));
					ret = KNG_POS_HARDWARE_ERROR;
					break;
				}
				// 更新工作密钥
				//memcpy(g_z18pos.mainkey,comm->buffer2+6,8);
				decrypt_work_key(comm->buffer2+6,g_z18pos.mainkey);
				ret = 0x00;
                //print_line(1,30,"set key ok");
			}
			// else  直接覆盖
			//
			// 清空流水
			if(param == 0x01)
			{
				// 清除流水
				if(EeSysRead(POS_REC_PTR_ADDR,26,comm->buffer2) != Z18_OK)
				{
					ret = KNG_POS_HARDWARE_ERROR;
					break;
				}
				// 设置读指针与写指针一致
				memcpy(comm->buffer2+6,comm->buffer2,6);
				// 清空日累计消费额与最后一次消费日期
				memset(comm->buffer2+16,0x00,7);
				comm->buffer2[23] = 0xFF;			//置写指针在前
				crc_code = GenerateCRC16(comm->buffer2,24);
				set_2byte_int(crc_code,comm->buffer2+24);
				if(EeSysWrite(POS_REC_PTR_ADDR,26,comm->buffer2) != Z18_OK)
				{
					ret = KNG_POS_HARDWARE_ERROR;
					break;
				}
				// TODO : 备份数据到备份块
				if(EeSysWrite(POS_REC_BAK_PTR_ADDR,26,comm->buffer2) != Z18_OK)
				{
					ret = KNG_POS_HARDWARE_ERROR;
					break;
				}
                ret = 0;
			}
			len = 0;
			crc = 1;
			break;
		case KNG_READ_EEPROM:
			flag1 = 0;
			comm->ext_buffer = g_global_buf;
			comm->ext_buf_len = sizeof(g_global_buf);
			len = comm->buffer[BUF_PARAM];
			if(len == 0)
			{
				// 读取扩展域
				len = comm->buffer[BUF_PARAM+1];
				flag1 = 1;
				addr = get_3byte_int(comm->buffer+BUF_PARAM+3);
				comm->ext_buf_len = 256 + len;
			}
			else
			{
				addr = get_3byte_int(comm->buffer+BUF_PARAM+2);
				comm->ext_buf_len = len;
			}
			// 判断地址的合法性
			if(addr >= POS_RECORD_END_ADDR 
			   || addr + comm->ext_buf_len >= POS_RECORD_END_ADDR)
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
			if(addr % 16 != 0)
			{
				ret = KNG_COM_PACK_INV;
				break;
			}
			//print_line(1,15,"addr[%lu][%d]",addr,comm->ext_buf_len);
			// 包头长 6 byte + 1 byte crc + 1 byte ETX2
			//  MAIN_PACK_LEN - 8
			if(comm->ext_buf_len <= 56)
			{
				if(EeSysRead(addr,comm->ext_buf_len,comm->buffer+6)!= Z18_OK)
				{
					ret = KNG_POS_HARDWARE_ERROR;
					break;
				}
				flag2 = 0;
				comm->use_ext = 0;
			}
			else
			{
				comm->use_ext = 1;
				flag2 = 1;
				crc_code = 0;
				while(crc_code < comm->ext_buf_len)
				{
					send_len = (comm->ext_buf_len - crc_code >= 64) ? 64 : (comm->ext_buf_len - crc_code);
					if(EeSysRead(addr+crc_code,send_len,comm->ext_buffer+crc_code)!= Z18_OK)
					//if(EeSysRead(addr+crc_code,send_len,comm->buffer)!= Z18_OK)
					{
						ret = KNG_POS_HARDWARE_ERROR;
						break;
					}
					//debug_hex(comm->buffer,send_len);
					//memcpy(comm->ext_buffer+crc_code,comm->buffer,send_len);
					crc_code += send_len;
				}
			}
			len = comm->ext_buf_len;
			crc = 1;
			ret = 0;
			break;
		case KNG_SET_CONSUME_PARAM:
			if(!do_check_cmd_cuf_crc(comm))
			{
				ret = KNG_CRC_ERROR;
				break;
			}
			if(EeSysRead(POS_CONSUME_PARA_ADDR,32,comm->buffer2)!=Z18_OK)
			{
				ret = KNG_POS_HARDWARE_ERROR;
				break;
			}
			if(param == 0x00)
			{
				// 比较版本号
				if(memcmp(comm->buffer2,comm->buffer+BUF_REQ_DATA,6) >= 0)
				{
					ret = 0x01;
					 break;
				}
			}
			// 基础费率不能大于 1000 元
			addr = get_3byte_int(comm->buffer+BUF_REQ_DATA+6);
			if(addr > 100000)
			{
				ret = KNG_COM_PACK_INV;
				break;
			}
			// 不能超过60天
			if(comm->buffer[BUF_REQ_DATA+9] > 0x60)
			{
				ret = KNG_COM_PACK_INV;
				break;
			}
			crc_code = get_2byte_int(comm->buffer+BUF_REQ_DATA+10);
			// 最大间隔不能超过 10 小时
			if(crc_code > 360000 || crc_code < 60)
			{
				ret = KNG_COM_PACK_INV;
				break;
			}
			memset(comm->buffer2,0xFF,32);
			memcpy(comm->buffer2,comm->buffer+BUF_REQ_DATA,12);
			crc_code = GenerateCRC16(comm->buffer2,30);
			set_2byte_int(crc_code,comm->buffer2+30);
			if(EeSysWrite(POS_CONSUME_PARA_ADDR,32,comm->buffer2)!=Z18_OK)
			{
				ret = KNG_POS_HARDWARE_ERROR;
				break;
			}
			memcpy(g_z18pos.consume_ver,comm->buffer+BUF_REQ_DATA,6);
			g_z18pos.base_money = get_3byte_int(comm->buffer+BUF_REQ_DATA+6);
			g_z18pos.collrec_interval = comm->buffer[BUF_REQ_DATA+9];
			g_z18pos.card_interval = get_2byte_int(comm->buffer+BUF_REQ_DATA+10);
			ret = 0;
			break;
        case KNG_SET_CARDGRP:
            if(!do_check_cmd_cuf_crc(comm))
			{
				ret = KNG_CRC_ERROR;
				break;
			}
            if(param != 0x99)
            {
                ret = KNG_POS_PARAM_ERROR;
                break;
            }
            len1 = 512;
            memcpy(comm->ext_buffer+len1,comm->buffer+BUF_REQ_DATA1,57);
            memcpy(comm->ext_buffer+len1+57,comm->ext_buffer,256-57);
            // 校准数据
            for(crc_code = 0;crc_code < 256;++crc_code)
            {
                if(comm->ext_buffer[len1+crc_code] >= MAX_CARD_GROUP)
                    comm->ext_buffer[len1+crc_code] = 0;
            }
            // 写参数
            for(crc_code = 0;crc_code < 256;crc_code += 64)
            {
                ret = EeSysWrite(POS_CARDGROUP_ADDR+crc_code,64,comm->ext_buffer+len1+crc_code);
                if(ret!=Z18_OK)
                {
                    ret = KNG_POS_HARDWARE_ERROR;
                    break;
                }
            }
            memcpy(g_z18pos.card_group,comm->ext_buffer+len1,256);
            ret = 0;
            len = 0;
            break;
		case KNG_CARD_RIGHT:
			// 使用了 ext_buffer
			if(!do_check_cmd_cuf_crc(comm))
			{
				comm->use_ext=0;
				ret = KNG_CRC_ERROR;
				break;
			}
			comm->use_ext=0;
			addr = POS_CARDRIGHT_ADDR;
			if(param != 0x99)
			{
				// 判断启用标志
				if(g_z18pos.use_card_right)
				{
					if(memcmp(g_z18pos.card_right_ver,comm->buffer+BUF_PARAM2+2,6)>=0)
					{
						ret = 0x01;
						break;
					}
				}
			}
			len1 = 512;
			param = comm->buffer[BUF_PARAM2];
			if(param == 0x01)
			{
				memcpy(comm->ext_buffer+len1,comm->buffer+BUF_PARAM+2,6);
				len1+=6;
				comm->ext_buffer[len1++] = 0x55;
				comm->ext_buffer[len1++] = 0xAA;
				memcpy(comm->ext_buffer+len1,comm->buffer+BUF_PARAM+8,32);
				len1+=32;
				memcpy(comm->ext_buffer+len1,g_z18pos.card_fee,256);
				len1+=256;
			}
			else if(param == 0x02)
			{
				// 版本号
				memcpy(comm->ext_buffer+len1,comm->buffer+BUF_REQ_DATA1,6);
				len1+=6;
				comm->ext_buffer[len1++] = 0x55;
				comm->ext_buffer[len1++] = 0xAA;
				memcpy(comm->ext_buffer+len1,g_z18pos.card_right,32);
				len1+=32;
				memcpy(comm->ext_buffer+len1,comm->buffer+BUF_REQ_DATA1+6,51);
				len1+=51;
				memcpy(comm->ext_buffer+len1,comm->ext_buffer,205);
				len1+=205;
			}
			else if(param == 0x03)
			{
				// 版本号
				memcpy(comm->ext_buffer+len1,comm->ext_buffer+4,6);
				len1+=6;
				comm->ext_buffer[len1++] = 0x55;
				comm->ext_buffer[len1++] = 0xAA;
				memcpy(comm->ext_buffer+len1,comm->ext_buffer+10,288);
				len1+=288;
				//debug_string(("cardright[%d]\n",len1-512));
				//debug_hex(comm->ext_buffer+512,len1-512);
				g_z18pos.use_card_right = 1;
			
			}
			else
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
			len = 296;
			crc_code = GenerateCRC16(comm->ext_buffer+512,len);
			set_2byte_int(crc_code,comm->ext_buffer+512+len);
			len += 2;
			// 后续包
			//debug_string(("cardright[%d]\n",len1-512));
			for(crc_code = 0; crc_code < len;crc_code+=32)
			{
				send_len = (len - crc_code >= 32) ? 32 : (len - crc_code);
				if(EeSysWrite(addr+crc_code,send_len,comm->ext_buffer+512+crc_code)!= Z18_OK)
				{
					ret = KNG_POS_HARDWARE_ERROR;
					break;
				}
				//debug_hex(comm->ext_buffer+512+crc_code,send_len);
			}
			len1=512;
			memcpy(g_z18pos.card_right_ver,comm->ext_buffer+len1,6);
			len1+=8;
			memcpy(g_z18pos.card_right,comm->ext_buffer+len1,32);
			len1+=32;
			memcpy(g_z18pos.card_fee,comm->ext_buffer+len1,256);
			len = 0;
			ret = 0;
			crc = 0;
			break;
		case KNG_CLEAR_SERIAL:
			if(param != 0x55 || comm->buffer[BUF_PARAM+1] != 0xAA)
			{
				ret = KNG_COM_PACK_INV;
				break;
			}
			if(comm->buffer[BUF_PARAM+2] != 0x06)
			{
				ret = KNG_COM_PACK_INV;
				break;
			}
			memset(comm->buffer2,0,sizeof 32);
			// 写记录指针
			set_3byte_int(POS_RECORD_BEGIN_ADDR,comm->buffer2);
			calc_not(comm->buffer2,3,comm->buffer2+3);
			// 读记录指针
			set_3byte_int(0x00,comm->buffer2+6);
			calc_not(comm->buffer2+6,3,comm->buffer2+9);
			// 流水号保留
			#if 1
			set_4byte_int(0,comm->buffer2+12);
            #else
            set_4byte_int(1254,comm->buffer2+12);
            #endif
			comm->buffer2[23] = 0xFF;
			// 计算crc
			crc_code = GenerateCRC16(comm->buffer2,24);
			set_2byte_int(crc_code,comm->buffer2+24);
			if(EeSysWrite(POS_REC_PTR_ADDR,26,comm->buffer2)!=Z18_OK)
			{
				ret = KNG_POS_HARDWARE_ERROR;
				break;
			}
			// 备份块
			if(EeSysWrite(POS_REC_BAK_PTR_ADDR,26,comm->buffer2)!=Z18_OK)
			{
				ret = KNG_POS_HARDWARE_ERROR;
				break;
			}
			g_z18pos.rec_rd_ptr = 0x00;
			g_z18pos.rec_wr_ptr = POS_RECORD_BEGIN_ADDR;
			g_z18pos.total_money = 0;
			g_z18pos.rec_ptr_flag = 0xFF;
			g_z18pos.serial_no = 0;
			ret = 0;
			len = 0;
			break;
		case KNG_SET_WELCOME_MSG:
			len = comm->buffer[BUF_PARAM+1];
			if(len > 16)
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
			comm->buffer[BUF_REQ_DATA+len] = 0;
			// debug_hex(comm->buffer+BUF_REQ_DATA,16);
			if(EeSysWrite(POS_WELCOMEMSG_ADDR,16,comm->buffer+BUF_REQ_DATA) != Z18_OK)
			{
				ret = KNG_POS_HARDWARE_ERROR;
				break;
			}
			memcpy(g_z18pos.welcome_msg,comm->buffer+BUF_REQ_DATA,16);
			ret = 0;
			len = 0;
			break;
		case KNG_COL_SERI:
			if(!do_check_cmd_cuf_crc(comm))
			{
				ret = KNG_CRC_ERROR;
				break;
			}
			addr = 0;
			if(param == 0x00)
			{
				if(get_serial_count() == 0)
				{
					ret = KNG_POS_NO_RECORD;
					break;
				}
				if(g_z18pos.rec_rd_ptr == 0x00)
				{
					addr = POS_RECORD_BEGIN_ADDR;
				}
				else
					addr = g_z18pos.rec_rd_ptr;
			}
			else if(param == 0x01)
			{
				// 计算流水地址
				if(comm->buffer[BUF_PARAM+1] != 0x04)
				{
					ret = KNG_POS_PARAM_ERROR;
					break;
				}
				serial_no = get_4byte_int(comm->buffer+BUF_REQ_DATA);
				addr = get_record_addr(serial_no);
			}
			else
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
			if(addr == 0 || addr < POS_RECORD_BEGIN_ADDR)
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
            debug_string(("col seri,[%lu],[%lu]\n",serial_no,addr));
			if(EeSysRead(addr,POS_REC_LEN,comm->ext_buffer)!=Z18_OK)
			{
				ret = KNG_POS_HARDWARE_ERROR;
				break;
			}
			comm->use_ext = 1;
			comm->ext_buf_len = POS_REC_LEN;
			len = POS_REC_LEN;
			ret = 0;
			crc = 1;
			flag2 = 1;
			break;
		case KNG_COL_SERI_CONFIRM:
			debug_hex(comm->buffer,14);
			if(param != 0x01)
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
			if(comm->buffer[BUF_PARAM+1] != 0x04)
			{
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
			serial_no = get_4byte_int(comm->buffer+BUF_REQ_DATA);
            #if 0
			addr = get_record_addr(serial_no);
			if(addr == 0 || addr < POS_RECORD_BEGIN_ADDR)
			{
				debug_string(("serial[%lu][%lu]\n",serial_no,addr));
				ret = KNG_POS_PARAM_ERROR;
				break;
			}
			//debug_string(("[%lu][%lu]",g_z18pos.rec_rd_ptr,addr));
			if(g_z18pos.rec_rd_ptr != addr)
			{
				debug_string(("rd ptr \n"));
				ret = KNG_POS_CONFIRM_SERI;
				break;
			}
			
			if(EeSysRead(addr,POS_REC_LEN,comm->ext_buffer)!=Z18_OK)
			{
				ret = KNG_POS_HARDWARE_ERROR;
				break;
			}
            addr = get_4byte_int(comm->ext_buffer+5);
			if(addr != serial_no)
			{
				debug_string(("serial no \n"));
				ret = KNG_POS_CONFIRM_SERI;
				break;
			}
			#else
            if(EeSysRead(g_z18pos.rec_rd_ptr,POS_REC_LEN,comm->ext_buffer)!=Z18_OK)
            {
                ret = KNG_POS_HARDWARE_ERROR;
				break;
            }
            addr = get_4byte_int(comm->ext_buffer+5);
            if(addr != serial_no)
			{
				debug_string(("serial no \n"));
				ret = KNG_POS_CONFIRM_SERI;
				break;
			}
            #endif
			
			ret = update_record_read_ptr();
			if(ret)
			{
				debug_string(("update rec\n"));
                break;
			}
			crc = 1;
			len = 0;
			break;
		case KNG_UPDATE_COL_DATE:
			if(!do_check_cmd_cuf_crc(comm))
			{
				ret = KNG_CRC_ERROR;
				break;
			}
			InitRtcTime();
			ReadRtcTime(comm->buffer2);
			calc_not(comm->buffer2+1,3,comm->buffer2+4);
			if(EeSysWrite(POS_COL_DATE_ADDR,6,comm->buffer2+1)!=Z18_OK)
			{
				ret = KNG_POS_HARDWARE_ERROR;
				break;
			}
			g_z18pos.uncoll_days = 0;
			ret = 0;
			crc = 0;
			len = 0;
			KNG_AUDIO(AU_COL_FINISH,Z18_AUDIO_DELAY_100);
			break;
        case KNG_ADDDEL_BLK:
            if(!do_check_cmd_cuf_crc(comm))
			{
				ret = KNG_CRC_ERROR;
				break;
			}
            if(param == 0x99)
            {
                memset(g_global_buf,0x00,32);
                for(addr = POS_BLK_BEGIN_ADDR;addr < POS_BLK_END_ADDR;addr += 32)
                {
                    debug_string(("write addr[%lu]\n",addr));
                    if(EeSysWrite(addr,32,g_global_buf) != Z18_OK)
                    {
                        ret = KNG_POS_HARDWARE_ERROR;
                        break;
                    }
                    print_line(1,0,"clear black %c",g_status_sym[(addr>>5)% 4]);
                }
                break;
            }
            else if(param == 0x00)
            {
                param = comm->buffer[BUF_PARAM2];
                if(param > 10)
                {
                    ret = KNG_POS_PARAM_ERROR;
                    break;
                }
                for(send_len = 0;send_len < param;++send_len)
                {
                    ret = do_update_blksheet(comm->buffer+BUF_REQ_DATA1+6+(send_len<<2));
                    if(ret)
                        break;
                }
                if(send_len < param)
                {
                    break;
                }
                debug_hex(comm->buffer+BUF_REQ_DATA1,6);
                ret = do_update_blksheet_ver(comm->buffer+BUF_REQ_DATA1);
                if(ret)
                    break;
                ret = 0;
    			crc = 0;
    			len = 0;
                //KNG_AUDIO(AU_DING,Z18_AUDIO_DELAY);
            }
            else
            {
                ret = KNG_POS_PARAM_ERROR;
                break;
            }
            break;
        case KNG_GET_BLKVER:
            if(param != 0x99)
            {
                ret = KNG_POS_PARAM_ERROR;
                break;
            }
            if(EeSysRead(POS_BLKVER_ADDR,10,comm->buffer+BUF_RESP_DATA)!=Z18_OK)
            {
                ret = KNG_POS_HARDWARE_ERROR;
                break;
            }
            if(comm->buffer[BUF_REQ_DATA+7] != 0x55 || comm->buffer[BUF_REQ_DATA+8] != 0xAA)
            {
                comm->buffer[BUF_REQ_DATA+6] = 0xAA;
            }
            else if(calc_sum(comm->buffer+BUF_RESP_DATA,6)!=comm->buffer[BUF_RESP_DATA+6])
            {
                memset(comm->buffer+BUF_RESP_DATA,0,sizeof 6);
                comm->buffer[BUF_RESP_DATA+6] = 0xAA;
            }
            else
            {
                comm->buffer[BUF_RESP_DATA+6] = 0xFF;
            }
            
            crc = 1;
            len = 7;
            ret = 0;
            break;
#if USE_GPRS
        case KNG_SET_SVRIP:
            if(!do_check_cmd_cuf_crc(comm))
            {
				ret = KNG_CRC_ERROR;
				break;
			}
            if(param != 0x99)
            {
                ret = KNG_POS_PARAM_ERROR;
                break;
            }
            
            calc_not(comm->buffer+BUF_REQ_DATA1,6,comm->buffer+BUF_REQ_DATA1+6);
            if(EeSysWrite(POS_GPRS_PARA_ADDR,12,comm->buffer+BUF_REQ_DATA1)!=Z18_OK)
            {
                ret = KNG_POS_HARDWARE_ERROR;
                break;
            }
            memcpy(g_z18pos.svr_ip,comm->buffer+BUF_REQ_DATA1,4);
            g_z18pos.svr_port = get_2byte_int(comm->buffer+BUF_REQ_DATA1+4);
            len = 0;
            ret = 0;
            break;
#endif
		default:
			debug_string(("not support cmd[%d]\n",(uint16)cmd));
			return KNG_NOT_SUPPORT_CMD;
		}
		
		// 应答
		comm->buffer[BUF_CMD] = cmd;
		comm->buffer[BUF_RET] = ret;
		if(!flag2)
		{
            
			send_len = do_pack_cmd_buf(comm->buffer,len,crc);
			comm->buf_begin=0;
			//debug_string(("send len[%d]\n",(uint16)send_len));
			//debug_hex(comm->buffer,send_len);
			//print_line(1,30,"return[%04X]",op->send_data);
			//print_line(1,30,"my send1");
			op->send_data(comm,send_len);
		}
		else
		{
			// send ext buffer
			if(do_pack_cmd_extbuf(comm,len,crc))
			{
				//debug_string(("ext buf,[%d]\n",len));
				//print_line(1,30,"my send");
				op->send_data(comm,len);
			}
		}
		print_line(1,0,"process ok");
		//kng_sleep(1);
	}while(1);
#else
	do{
		comm->buflen=1;
		g_rec_data[0] = 0x55;
		send_len = op->send_data(comm);
		if(send_len)
		{
			print_line(0,1,"send secucces!");
			kng_sleep(5);
		}
		else
			print_line(0,1,"send failed!");
		if(do_wait_key(3))
			return KNG_POS_TIMEOUT;
	}while(1);
#endif 
}

#if USE_INFRARED_COMM

uint8 pos_infare()
{
	COMM_TYPE_T comm;
	uint8 ret;
	cls();
	print_line(0,10,"init infrared...");
	comm.port_no = 1;
	comm.band = 19200;
	comm.ver = 1;
    /*
	if(register_infrared(&comm,&op))
	{
		print_error(KNG_POS_HARDWARE_ERROR,"不支持红外");
		return KNG_POS_HARDWARE_ERROR;
	}
	*/
	if(g_Infrared_op.open(&comm))
	{
		print_error(KNG_POS_HARDWARE_ERROR,"打开红外失败");
		return KNG_POS_HARDWARE_ERROR;
	}
	Led_OnOff(2,0);
	do{
		ret = do_setting_pos(&comm,&g_Infrared_op);
		if(ret)
		{
			//print_error(ret,NULL);
			if(KNG_POS_USER_CANCEL == ret)
				break;
		}
		if(z18pos_wait_key(KEY_ESC,3))
		{
			ret = KNG_POS_TIMEOUT;
			break;
		}
	}while(1);
	Led_OnOff(2,1);
	return ret;
}

#endif

#if 0
uint8 pos_comm()
{
	COMM_TYPE_T comm;
	COMM_OPERATION_T op;
	uint8 ret;
	cls();
	print_line(0,20,"communication...");
	comm.port_no = 0;
	comm.band = Z18POS_COM_BAUD;
	comm.ver = 1;
	if(register_commport(&comm,&op))
	{
		print_error(KNG_POS_HARDWARE_ERROR,"不支持串口");
	}
	//debug_string(("init comm port"));
	if(op.open(&comm))
	{
		print_error(KNG_POS_HARDWARE_ERROR,"打开串口失败");
	}
	do{
		ret = do_setting_pos(&comm,&op);
		if(ret)
		{
			//print_error(ret,NULL);
			if(KNG_POS_USER_CANCEL == ret)
				return ret;
		}
		if(do_wait_key(3))
			return KNG_POS_TIMEOUT;
	}while(1);
	return ret;
}
#endif 


#if USE_GPRS
uint8 pos_gprs()
{
	COMM_TYPE_T xdata comm;
	cls();

	comm.port_no = 1;
	comm.band = 9600;
	comm.ver = 1;
    /*
	if(register_commport(&comm,&op))
	{
		print_error(KNG_POS_HARDWARE_ERROR,"不支持GPRS");
		return KNG_POS_HARDWARE_ERROR;
	}
	*/

    print_line(0,1,"init pos...");
	if(g_COM_op.open(&comm))
	{
		print_error(KNG_POS_HARDWARE_ERROR,"打开GPRS失败");
		return KNG_POS_HARDWARE_ERROR;
	}

	Led_OnOff(Z18POS_LED_RED,Z18POS_LED_ON);
	
    // TODO: gprs logon , connect
    do{

        if(z18pos_wait_key(KEY_ESC,100)) 
            break;
        if(gprs_connect(&comm,&g_COM_op))
        {
            gprs_disconnect(&comm,&g_COM_op);
            continue;
        }
        if(gprs_send_record(&comm,&g_COM_op))
            continue;
        if(gprs_download_black(&comm,&g_COM_op))
            continue;
        break;
        //gprs_disconnect(&comm,&g_COM_op);
    }while(1);
    Led_OnOff(Z18POS_LED_RED,Z18POS_LED_OFF);
    //print_line(1,20,"gprs finish");
	return 0;
}
#endif 


uint8 pos_init_setting()
{
	COMM_TYPE_T xdata comm;
	uint8 ret;
	cls();

	comm.port_no = 0;
	comm.band = Z18POS_COM_BAUD;
	comm.ver = 1;
    /*
	if(register_commport(&comm,&op))
	{
		print_error(KNG_POS_HARDWARE_ERROR,"不支持串口");
		return KNG_POS_HARDWARE_ERROR;
	}
	*/
	if(g_COM_op.open(&comm))
	{
		print_error(KNG_POS_HARDWARE_ERROR,"打开串口失败");
		return KNG_POS_HARDWARE_ERROR;
	}

	Led_OnOff(2,0);
	debug_string(("init pos...\n"));
	do{
		ret = do_setting_pos(&comm,&g_COM_op);
		if(ret)
		{
			//print_error(ret,NULL);
			if(KNG_POS_USER_CANCEL == ret)
				break;
		}
		if(z18pos_wait_key(KEY_ESC,3))
		{
			ret = KNG_POS_TIMEOUT;
			break;
		}
	}while(1);
	Led_OnOff(2,1);
	return ret;
}
