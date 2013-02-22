#include "reg52.h"
#include "stdio.h"
#include <string.h>
#include <absacc.h>
#include <stdarg.h>
#include <stdlib.h>
#include "z18pos.h"
#include "intrins.h"
#include ".\Include\DataType.h"
#include ".\Include\LibFuntion.h"
#include "crc.h"
#include "mifare_card.h"
#include "consume.h"
#include "transfer.h"


typedef struct {
	INT16U err_no;
	const char *err_msg;
}err_msg_t;

typedef union {
	uint16 i16;
	struct {
		uint8 i8_1;
		uint8 i8_2;
	}u;
}test_union_t;


// 卡结构
mifare_card_t xdata g_mycard;
// POS 主参数
z18pos_param_t xdata g_z18pos;
// 扩展buffer
uint8 xdata g_global_buf[1024];

uint8 data g_errorno;

static err_msg_t xdata g_err[] = {
	{ KNG_POS_UNEXPECT_CARD 	,"中途拔卡"},
	{ KNG_POS_UNREAD_CARD		,"不可识别卡"},
	{ KNG_POS_PURSE_ERROR		,"卡钱包错误"},
	{ KNG_POS_HAS_RECORD		,"未上传流水"},
	{ KNG_POS_EXPIRED_COLL		,"请采集"},
	{ KNG_POS_BLACK_CARD		,"黑卡"},
	{ KNG_POS_EXPIRED_CARD		,"卡已过期"},
	{ KNG_POS_NO_RIGHT			,"无权限"},
	{ KNG_POS_PURSE_LACK		,"卡余额不足"},
	{ KNG_POS_CARD_LOCKED		,"卡已锁"},
	{ KNG_POS_FREE_CARD			,"免费卡"},
	{ KNG_POS_REC_FULL			,"记录已满"},
	{ KNG_POS_REPEAT_CONSUME	,"重复刷卡"},
	{ KNG_POS_PARAM_ERROR		,"设置错误"},
	{ KNG_POS_CLOCK_ERROR		,"时钟错误"},
	{ KNG_POS_HARDWARE_ERROR	,"硬件故障"},
	{ KNG_POS_NOT_SUPP_CARDTYPE ,"不支持卡类型"},
	{ 0xFE , "" },
};




void kng_sleep(uint16 secs)
{
	bp_TimerSet(0,secs);
	while(bp_TimerCheck(0)==FALSE)
	;
}

int kng_check_pos_param()
{
	uint8 ret;
	uint16 crc;
	uint32 addr;
	uint8 buffer[64];
	uint8 temp[16];
	memset(buffer,0x55,sizeof buffer);

	
	// 测试 EEPROM 的大小
	ret = EeSysRead(POS_RECORD_END_ADDR - 64,64,buffer);
	if(Z18_OK != ret)
	{
		print_error(KNG_POS_HARDWARE_ERROR,"存储容量");
		return KNG_POS_HARDWARE_ERROR;
	}
	ret = EeSysRead(0x00,42,buffer);
	if(Z18_OK != ret)
		return ret;
	memcpy(g_z18pos.device_id,buffer,4);
	calc_not(buffer,4,temp);
	if(memcmp(buffer+4,temp,4) != 0)
	{
		print_error(KNG_POS_PARAM_ERROR,"物理ID未设置");
		return KNG_POS_PARAM_ERROR;
	}
	crc = GenerateCRC16(buffer+16,24);
	set_2byte_int(crc,temp);
	//debug_hex(buffer+8,25);
	//debug_hex(temp,2);
	if(memcmp(buffer+40,temp,2)!=0)
	{
#if 1
		// 读取备参数
		if(EeSysRead(POS_REC_BAK_PTR_ADDR,26,g_rec_data)!=Z18_OK)
		{
			print_error(KNG_POS_HARDWARE_ERROR,"备参");
			return KNG_POS_HARDWARE_ERROR;
		}
		crc = GenerateCRC16(g_rec_data,24);
		set_2byte_int(crc,temp);
		if(memcmp(g_rec_data+24,temp,2)!=0)
		{
			print_error(KNG_POS_PARAM_ERROR,"主参错误");
			return KNG_POS_PARAM_ERROR;
		}
		else
		{
			if(EeSysWrite(POS_REC_PTR_ADDR,26,g_rec_data)!= Z18_OK)
			{
				print_error(KNG_POS_HARDWARE_ERROR,"恢复主");
				return KNG_POS_HARDWARE_ERROR;
			}
			memcpy(buffer+16,g_rec_data,26);
		}
#else
		print_error(KNG_POS_PARAM_ERROR,"主参错误");
		return KNG_POS_PARAM_ERROR;
#endif
	}
	// 保存记录指针
	calc_not(buffer+16,3,g_rec_data);
	if(memcmp(buffer+19,g_rec_data,3)!=0)
	{
		print_error(KNG_POS_PARAM_ERROR,"WR SERIAL");
		return KNG_POS_PARAM_ERROR;
	}
	g_z18pos.rec_wr_ptr = get_3byte_int(buffer+16);
	calc_not(buffer+22,3,g_rec_data);
	if(memcmp(buffer+25,g_rec_data,3)!=0)
	{
		print_error(KNG_POS_PARAM_ERROR,"RD SERIAL");
		return KNG_POS_PARAM_ERROR;
	}
	g_z18pos.rec_rd_ptr = get_3byte_int(buffer+22);
	g_z18pos.rec_ptr_flag = buffer[39];

	g_z18pos.serial_no = get_4byte_int(buffer+28);
	g_z18pos.total_money = get_4byte_int(buffer+32);

	memcpy(g_z18pos.last_tx_date,buffer+36,3);
    debug_string("start,wr[%lu],rd[%lu],serial[%lu]\n",g_z18pos.rec_wr_ptr,g_z18pos.rec_rd_ptr,g_z18pos.serial_no);

	if(z18pos_check_rec_full())
	{
		print_error(KNG_POS_REC_FULL,NULL);
		return KNG_POS_REC_FULL;
	}
	return 0;
}

void print_error1(uint16 line,INT16U error,const char *msg)
{

	INT16S i;
	char output[64];
	memset(output,0,sizeof(output));
	sprintf(output,"[%d]错误码：%d ",line,error);

	Clear_line(1);
	Display(1,0,output,0);

	for(i=0;;++i)
	{
		if(g_err[i].err_no == 0xFE)
			break;
		else if(g_err[i].err_no == error)
		{
			Clear_line(2);
			Display(2,0,g_err[i].err_msg,0);
			break;
		}
	}
	if(msg)
	{
		Clear_line(3);
		Display(3,0,msg,0);
	}
	bp_beep(100,20);
	kng_sleep(20);
}



#if DEBUG
void debug_hex(uint8 *hex,uint16 len)
{
	uint16 sect;
	sect = len >> 3;
	if(len % 8 > 0) sect++;
	if(sect == 0) sect = 1;
	/*
	cls();
	for(i = 0;i < sect && i < 4 ;++i)
	{
		DisplayBcd(i,0,hex+(i<<3),8);
	}
	for(;;)
	{
	if(GetKeyVal(1) == KEY_ESC)
	break;
	}
	*/
	DebugData((uint32)len,16,hex);
}

void debug_string(const char *fmt,...)
{
	char msg[64];
	va_list p;
	va_start(p,fmt);
	vsprintf(msg,fmt,p);
	va_end(p);
	/*
	cls();
	Display(0,0,msg,0);
	kng_sleep(30);
	*/
	DebugString(msg);
}
#else
#define debug_string
#define debug_hex(x,y)
#endif

void d4u5_str(float v,uint8 *str)
{
	sprintf(str,"%.02f",v);
}

void print_line(uint8 line,uint8 sleep,const char *fmt,...)
{
	char msg[64];
	va_list p;

	if(line < 0 || line > 3) return;
	va_start(p,fmt);
	vsprintf(msg,fmt,p);
	va_end(p);
	Clear_line(line);
	Display(line,0,msg,0);
	if(sleep > 0)
		kng_sleep(sleep);
}

static bit is_lear_year(uint16 year)
{
	if(((year % 100 != 0) && (year % 4 == 0)) ||
	   (year % 400 == 0))
		return 1;
	return 0;
}
static uint16 calc_days(uint8 *date)
{
	uint16 days;
	uint8 str[9];
	uint8 temp[3];
	uint8 month_day[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	uint16 year,month,day,i;
	bit lear_year;
	memset(str,0,sizeof str);
	memset(temp,0,sizeof temp);
	bcd2str(date,3,str);
	memcpy(temp,str,2);
	year = 2000 + atoi(temp);
	memcpy(temp,str+2,2);
	month = atoi(temp);
	memcpy(temp,str+4,2);
	day = atoi(temp);
	for(i = 2000,days=0;i < year;++i)
	{
		if(is_lear_year(i))
			days += 366;
		else
			days += 365;
	}
	lear_year = is_lear_year(year);
	for(i = 1;i < month;++i)
	{
		days += month_day[i];
		// 闰年 2 月
		if(lear_year && i == 2)
			days++;
	}
	days += day-1;
	return days;
}

// 计算时间
static uint16 calc_date_span(uint8 *begin_date,uint8 *end_date)
{
	uint16 begin_days,end_days;
	if(memcmp(begin_date,end_date,3) >= 0)
		return 0;
	
	begin_days = calc_days(begin_date);
	end_days = calc_days(end_date);
	return end_days - begin_days;
}

// 加载黑名单
static uint8 load_blksheet()
{
    uint8 ret;
    ret = EeSysRead(POS_BLKVER_ADDR,10,g_rec_data);
    if(ret != Z18_OK)
        return KNG_POS_HARDWARE_ERROR;
    if(g_rec_data[7] != 0x55 || g_rec_data[8] != 0xAA)
    {
        g_z18pos.blk_begin_addr = 0x00;
        return 0;
    }
    if(calc_sum(g_rec_data,6)!=g_rec_data[6])
    {
        g_z18pos.blk_begin_addr = 0x0000000;
        return KNG_POS_PARAM_ERROR;
    }
    memcpy(g_z18pos.blk_ver,g_rec_data,6);
    g_z18pos.blk_begin_addr = 0xFFFFFFFF;
    return 0;
}

static uint8 load_z18pos_param()
{
	uint16 crc_code;

	uint32 addr;

	if(loadconfig() != Z18_OK)
	{
		print_error(KNG_POS_HARDWARE_ERROR,"读卡器异常");	
		return KNG_POS_HARDWARE_ERROR;
	}
	InitRtcTime();
	ReadRtcTime(g_z18pos.curr_time);

	if(EeSysRead(0x40,24,g_rec_data) != Z18_OK)
	{
		debug_string("read 0x40 addr\n");
		print_error(KNG_POS_HARDWARE_ERROR,"读EEPROM 1");	
		return KNG_POS_HARDWARE_ERROR;
	}
	if( g_rec_data[22] != 0x55 || g_rec_data[23] != 0xAA)
	{
		print_error(KNG_POS_PARAM_ERROR,"EEPROM Data 1");
		return KNG_POS_PARAM_ERROR;
	}
	if(memcmp(g_rec_data+6,g_rec_data+14,6) != 0)
	{
		print_error(KNG_POS_PARAM_ERROR,"work key");	
		return KNG_POS_PARAM_ERROR;
	}
	decrypt_work_key(g_rec_data+6,g_z18pos.mainkey);
	//memcpy(g_z18pos.mainkey,g_rec_data+6,8);
	//debug_string("work key\n");
	//debug_hex(g_z18pos.mainkey,8);

	// 消费参数表
	if(EeSysRead(0x60,32,g_rec_data) != Z18_OK)
	{
		print_error(KNG_POS_HARDWARE_ERROR,"读EEPROM 2");	
		return KNG_POS_HARDWARE_ERROR;
	}
	
	crc_code = GenerateCRC16(g_rec_data,30);
	set_2byte_int(crc_code,g_rec_data+32);
	if(memcmp(g_rec_data+30,g_rec_data+32,2)!=0)
	{
		print_error(KNG_POS_PARAM_ERROR,"EEPROM Data 2");
		return KNG_POS_PARAM_ERROR;
	}
	memcpy(g_z18pos.consume_ver,g_rec_data,6);
	g_z18pos.base_money = get_3byte_int(g_rec_data+6);
	g_z18pos.collrec_interval = g_rec_data[9];
	g_z18pos.card_interval = get_2byte_int(g_rec_data+10);
	// TODO : 检查采集流水日期
	if(EeSysRead(0x80,6,g_rec_data)!=Z18_OK)
	{
		print_error(KNG_POS_HARDWARE_ERROR,"读EEPROM 2");	
		return KNG_POS_HARDWARE_ERROR;
	}
	calc_not(g_rec_data,3,g_rec_data+6);
	if(memcmp(g_rec_data+3,g_rec_data+6,3) !=0)
	{
		memcpy(g_rec_data,g_z18pos.curr_time+1,3);
		calc_not(g_rec_data,3,g_rec_data+3);
		if(EeSysWrite(0x80,6,g_rec_data) != Z18_OK)
		{
			print_error(KNG_POS_HARDWARE_ERROR,"写EEPROM 2");	
			return KNG_POS_HARDWARE_ERROR;
		}
	}
	g_z18pos.uncoll_days = calc_date_span(g_rec_data,g_z18pos.curr_time+1);
	debug_string("days[%d][%d]",(uint16)g_z18pos.uncoll_days,(uint16)g_z18pos.collrec_interval);
	if(z18pos_check_coll_interval())
		return KNG_POS_EXPIRED_COLL;

	// 卡权限，费率 参数表
	for(crc_code = 0;crc_code < 298;crc_code+=64)
	{
		if(EeSysRead(POS_CARDRIGHT_ADDR+crc_code,64,g_global_buf+crc_code) != Z18_OK)
		{
			print_error(KNG_POS_HARDWARE_ERROR,"读EEPROM 3");	
			return KNG_POS_HARDWARE_ERROR;
		}
	}
	g_z18pos.use_card_right = 0;
	if(g_global_buf[6] != 0x55 || g_global_buf[7] != 0xAA)
	{
		print_error(KNG_POS_PARAM_ERROR,"EEPROM Data 3");
		return KNG_POS_PARAM_ERROR;
	}
	crc_code = GenerateCRC16(g_global_buf,296);
	set_2byte_int(crc_code,g_rec_data);
	if(memcmp(g_rec_data,g_global_buf+296,2) !=0)
	{
		print_error(KNG_POS_PARAM_ERROR,"EEPROM Data 3");
		return KNG_POS_PARAM_ERROR;
	}
	memcpy(g_z18pos.card_right_ver,g_global_buf,6);
	memcpy(g_z18pos.card_right,g_global_buf+8,32);
	memcpy(g_z18pos.card_fee,g_global_buf+40,256);

	// 欢迎信息
	if(EeSysRead(0xD0,32,g_rec_data) != Z18_OK)
	{
		print_error(KNG_POS_HARDWARE_ERROR,"读EEPROM 4");	
		return KNG_POS_HARDWARE_ERROR;
	}
	//strcpy(g_z18pos.welcome_msg,"SunGard一卡通");
	memcpy(g_z18pos.welcome_msg,g_rec_data,16);
	g_z18pos.welcome_msg[16] = 0;
	//debug_hex(g_z18pos.welcome_msg,16);
	calc_not(g_rec_data+16,4,g_rec_data+32);
	if(memcmp(g_rec_data+32,g_rec_data+20,4) != 0)
	{
		g_z18pos.pre_total_money = 0;
	}
	else
		g_z18pos.pre_total_money = get_4byte_int(g_rec_data+16);
	g_z18pos.rec_status = 0;



    return load_blksheet();


}

typedef uint8 (*menu_func_t)(void);
typedef struct {
	const uint8 *menu;
	menu_func_t fn;
}menu_item_t;

menu_func_t do_menu_form(menu_item_t *menu_item,uint8 min_row,uint8 max_row)
{
	uint8 row,key;
	uint16 i;
	debug_string("display menu\n");
	cls();
	for(row=0;row<max_row+1;++row)
	{
		if(min_row == row)
			Display(row,0,menu_item[row].menu,1);
		else
			Display(row,0,menu_item[row].menu,0);
	}
	row = min_row;
	i = 0;
	for(;;)
	{
		key = GetKeyVal(1);
		if(key != 0xFF)
			Lcd_onoff(1);

		switch(key)
		{
		case KEY_ESC:
			return NULL;
		case KEY_ENTYER:
			if(menu_item[row].fn)
				return menu_item[row].fn;
			else
				bp_beep(10,30);
			break;
		case KEY_UP:
			if(row == min_row)
				bp_beep(10,10);
			else
			{
				Clear_line(row);
				Display(row,0,menu_item[row].menu,0);
				row--;
				Clear_line(row);
				Display(row,0,menu_item[row].menu,1);
			}
			break;
		case KEY_DOWN:
			if(row == max_row)
				bp_beep(10,30);
			else
			{
				Clear_line(row);
				Display(row,0,menu_item[row].menu,0);
				row++;
				Clear_line(row);
				Display(row,0,menu_item[row].menu,1);
			}
			break;
		case 0xFF:
			kng_sleep(1);
			i++;
			if(i > 300)
			{
				Lcd_onoff(0);
				i = 0;
			}
		default:
			break;
		}
	}
	return NULL;
}
static uint8 do_communication()
{
#if USE_INFRARED_COMM && USE_GPRS
	menu_item_t menu_item[]={
		{"1. 红外通讯  ",pos_infare},
		{"2. 串口通讯  ",pos_init_setting},
		{"3. GPRS通讯  ",pos_gprs},
		{"             ",NULL}
	};
#elif USE_INFRARED_COMM
    menu_item_t menu_item[]={
		{"1. 红外通讯  ",pos_infare},
		{"2. 串口通讯  ",pos_init_setting},
		{"             ",NULL},
        {"             ",NULL}
	};
#elif USE_GPRS
    menu_item_t menu_item[]={
		{"1. GPRS通讯  ",pos_gprs},
		{"2. 串口通讯  ",pos_init_setting},
		{"             ",NULL},
        {"             ",NULL}
	};
#else
    menu_item_t menu_item[]={
		{"1. 串口通讯  ",pos_init_setting},
		{"             ",NULL},
        {"             ",NULL},
        {"             ",NULL}
	};
#endif 
	menu_func_t func;
	clr_dog();
	func = do_menu_form(menu_item,0,2);
	if(func)
	{
		func();
	}
	return 0;
}

static void do_format_money(uint32 money,uint8 *str)
{
	uint8 len;
	sprintf(g_rec_data,"%lu",money);
	len = strlen(g_rec_data);
	//debug_string("%s,[%d\n",g_rec_data,len);
	memcpy(str,g_rec_data,len-2);
	str[len-3] = '.';
	memcpy(str+len-3,g_rec_data+len-3,2);
	str[len+1] = '\0';
}

static uint8 do_query_param()
{
	uint8 param[4][17];
	uint8 str[10];
	uint16 rec_cnt;
	uint8 key,redraw,page,max_page;
	redraw = 1;
	page = 0;
	max_page = 6;
	for(;;)
	{
		key = GetKeyVal(1);
		switch(key)
		{
		case KEY_UP:
			if(page>0)
			{
				page--;
				redraw = 1;
			}
			break;
		case KEY_DOWN:
			if(page < max_page)
			{
				page++;
				redraw = 1;
			}
			break;
		case KEY_ESC:
			return 0;
		default:
			break;
		}
		if(redraw)
		{
			memset(param,0,sizeof param);
            switch(page)
            {
                
			case 0:
			{
				sprintf(param[0],"设备物理ID");
				sprintf(param[1],"%02X%02X%02X%02X"
						,(uint16)g_z18pos.device_id[0]
						,(uint16)g_z18pos.device_id[1]
						,(uint16)g_z18pos.device_id[2]
						,(uint16)g_z18pos.device_id[3]);

				sprintf(param[2],"系统时间");
				InitRtcTime();
				ReadRtcTime(str);
				bcd2str(str,7,param[3]);
			}
            break;
            case 1:
			{
				sprintf(param[0],"当天营业额");
				sprintf(param[1],"%.02f 元",g_z18pos.total_money/100.0);
				//do_format_money(g_z18pos.total_money,param[1]);
				sprintf(param[2],"前一天营业额");
				sprintf(param[3],"%.02f 元",g_z18pos.pre_total_money/100.0);
				//do_format_money(g_z18pos.pre_total_money,param[3]);
			}
            break;
			case 2:
			{
				sprintf(param[0],"基础费率");
				sprintf(param[1],"%.02f 元",g_z18pos.base_money/100.0);
				//do_format_money(g_z18pos.base_money,param[1]);
				sprintf(param[2],"采集时间间隔");
				sprintf(param[3],"%d 天",(uint16)g_z18pos.collrec_interval);
			}
            break;
			case 3:
			{
				sprintf(param[0],"连续刷卡");
				sprintf(param[1],"%d 秒",g_z18pos.card_interval);
				sprintf(param[2],"当前流水号");
				sprintf(param[3],"%lu",g_z18pos.serial_no);
			}
            break;
			case 4:
			{
				sprintf(param[0],"未采集记录");
				// 每条记录64 byte
				rec_cnt =  get_serial_count();
				sprintf(param[1],"%u 条",rec_cnt);
				sprintf(param[2],"程序版本");
				sprintf(param[3],"%s",VER_STR);
			}
            break;
			case 5:
			{
				sprintf(param[0],"未采集天数");
				sprintf(param[1],"%u 天",(uint16)g_z18pos.uncoll_days);
			}	
            break;
			case 6:
			{
				sprintf(param[0],"Build");
				sprintf(param[1],"%s",__DATE__);
				sprintf(param[2],"%s",__TIME__);
			}
            break;
            default:
                break;
            }
			redraw = 0;
			cls();
			for(key=0;key<4;++key)
			{
				Display(key,0,param[key],0);
			}
		}
	}
	return 0;
}
void do_list_menu()
{
	menu_item_t menu_item[]={
		{g_z18pos.welcome_msg,NULL},
		{"1. 刷卡收费  ",read_card_loop},
		{"2. 查询      ",do_query_param},
		{"3. 通讯      ",do_communication}
	};
	
	menu_func_t func;
	clr_dog();
	func = do_menu_form(menu_item,1,3);
	if(func)
	{
		func();
	}
}
void main()
{
	uint16 ret;
	cls();
#ifndef USE_DOG
	bp_Cdog();
#endif
	delay_1ms(1000);
	bp_beep(30,20);
	DispInitialize();
	//bp_SerialCtl(0,115200);
	bp_SerialCtl(0,Z18POS_COM_BAUD);
	Lcd_onoff(1);

	Led_OnOff(1,0);
	memset(&g_z18pos,0,sizeof g_z18pos);
#if 1
	// 检查POS机参数
	ret = kng_check_pos_param();	
	if(ret)
	{
		// 检查参数失败，提示错误信息
#if USE_INFRARED_COMM
		if(ret == KNG_POS_REC_FULL)
            pos_infare();
        else
#endif
    		pos_init_setting();
		return;
	}

#endif 
	//pos_init_setting();
	//test_feprom();
	ret = load_z18pos_param();
	if(ret)
	{
		print_error(ret,NULL);
		z18pos_wait_key(KEY_ENTYER,0);
	}
	// 进入主循环
	InitRtcTime();
	ReadRtcTime(g_z18pos.curr_time);
#if 1
	while(1)
	{
		do_list_menu();
	}
#else
	while(1)
	{
		profile(0);
	}
#endif
}

uint8 z18pos_write_eeprom(uint32 addr,uint8 len,uint8 retries,uint8 *buf)
{
	uint8 ret;
	if(len > 64)
		return KNG_POS_PARAM_ERROR;
	if(addr < 0 || addr+len > POS_RECORD_END_ADDR)
		return KNG_POS_PARAM_ERROR;
	while(retries-->0)
	{
		ret = EeSysWrite(addr,len,buf);
		if(Z18_OK == ret)
			return 0;
	}
	return KNG_POS_HARDWARE_ERROR;
}

uint8 z18pos_read_eeprom(uint32 addr,uint8 len,uint8 retries,uint8 *buf)
{
	uint8 ret;
	if(len > 64)
		return KNG_POS_PARAM_ERROR;
	if(addr < 0 || addr+len > POS_RECORD_END_ADDR)
		return KNG_POS_HARDWARE_ERROR;
	memset(buf,0xaa,len);
	while(retries-->0)
	{
		ret = EeSysRead(addr,len,buf);
		//debug_string("addr[%lu]len[%d]ret[%d]",addr,(uint16)len,(uint16)ret);
		if(Z18_OK == ret)
			return 0;
	}
	return KNG_POS_HARDWARE_ERROR;
}
bit z18pos_wait_key(uint8 key,uint8 timeout)
{
	uint8 r;
	if(timeout > 0)
	{
		bp_TimerSet(0,timeout);
		while(1)
		{
			r = GetKeyVal(1);
			if(key == r)
				return 1;
			if(bp_TimerCheck(0) == FALSE)
				return 0;
		}
	}
	else
	{
		while(1)
		{
			r = GetKeyVal(1);
			if(r == key)
				return 1;
		}
		return 0;
	}
}	
bit z18pos_check_rec_full()
{
	if(g_z18pos.rec_wr_ptr == g_z18pos.rec_rd_ptr
	   && g_z18pos.rec_ptr_flag == 0x00)
	{
        debug_string("begin[%lu]end[%lu]\n",g_z18pos.rec_wr_ptr,g_z18pos.rec_rd_ptr);
		return 1;
	}
	return 0;
}
bit z18pos_check_coll_interval()
{
	return (g_z18pos.uncoll_days > g_z18pos.collrec_interval) ? 1 : 0;
}

uint8 z18pos_calc_blkinfo(uint32 card_id,blk_mem_info_t *blk)
{
    // 有黑卡标志 
	uint32 begin_addr,new_cardid;

    // 读取黑名单表
    // 计算偏移
    new_cardid = card_id - 1;
    blk->byte_offset = new_cardid >> 3; // g_mycard.card_id / 8
    begin_addr = blk->byte_offset << 3; // offset * 8
    if(new_cardid < begin_addr)
    {
        return KNG_POS_UNEXPECT_CARD;
    }
    else if(new_cardid >= begin_addr)
    {
        blk->bit_offset = new_cardid - begin_addr;

        // byte_offset / 32
        blk->offset = blk->byte_offset>>5;
        blk->offset <<= 5;
        
        
        blk->offset += POS_BLK_BEGIN_ADDR;
        if(blk->offset >= POS_BLK_END_ADDR)
            return KNG_POS_UNREAD_CARD;
    }
    debug_string("blk[%ul],[%ul],[%ul],[%d]\n",card_id,blk->offset,blk->byte_offset,(uint16)blk->bit_offset);
	return 0;
}

uint8 z18pos_check_consume()
{
    uint8 ret;
    uint16 crc;
    if(memcmp(g_z18pos.last_tx_date,g_z18pos.curr_time+1,3)!=0)
    {
        debug_hex(g_z18pos.last_tx_date,3);
        //debug_hex(g_z18pos.curr_time,7);
        // 更新了日期
        if(EeSysRead(POS_REC_PTR_ADDR,26,g_rec_data)==Z18_FAILED)
            return KNG_POS_HARDWARE_ERROR;

        ret = update_pre_total(g_rec_data+16);
        if(ret)
            return ret;

        memset(g_rec_data+16,0,4);
        memcpy(g_rec_data+20,g_z18pos.curr_time+1,3);
         
        crc = GenerateCRC16(g_rec_data,24);
        set_2byte_int(crc,g_rec_data+24);

        if(EeSysWrite(POS_REC_PTR_ADDR,26,g_rec_data)==Z18_FAILED)
            return KNG_POS_HARDWARE_ERROR;
        // 更新到下一天
        g_z18pos.pre_total_money = g_z18pos.total_money;
        g_z18pos.total_money = 0;
        memcpy(g_z18pos.last_tx_date,g_z18pos.curr_time+1,3);
        return 0;
    }
    return 0;
}

/** 
 * @brief 记录历史总金额
 * 
 * @param total 
 * 
 * @return 
 */
uint8 update_pre_total(uint8* total)
{
	uint8 buffer[24];
	memset(buffer,0,sizeof buffer);
	memcpy(buffer,total,4);
	calc_not(buffer,4,buffer+4);
	if(EeSysWrite(0xE0,8,buffer) == Z18_FAILED)
		return KNG_POS_HARDWARE_ERROR;
	return 0;
}


