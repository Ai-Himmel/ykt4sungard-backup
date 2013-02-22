#ifndef _KNG_Z18POS_H_
#define _KNG_Z18POS_H_

#define KNG_POS_SUCCESS 0			//成功
#define KNG_POS_UNEXPECT_CARD 0x01	//中途拔卡
#define KNG_POS_UNREAD_CARD 0x02	//不可识别卡
#define KNG_POS_PURSE_ERROR 0x03	//卡钱包错误
#define KNG_POS_HAS_RECORD 0x04		//未上传流水
#define KNG_POS_EXPIRED_COLL 0x05	//超过采集时间
#define KNG_POS_BLACK_CARD 0x06		//黑卡
#define KNG_POS_EXPIRED_CARD 0x07	//卡已过期
#define KNG_POS_NO_RIGHT 0x08		//无权限
#define KNG_POS_PURSE_LACK 0x09		//卡余额不足
#define KNG_POS_CARD_LOCKED 0x0A	//卡已锁
#define KNG_POS_FREE_CARD 0x0C		//免费卡
#define KNG_POS_REC_FULL  0x0D		//记录已满
#define KNG_POS_REPEAT_CONSUME 0x5A	//重复刷卡
#define KNG_POS_CLOCK_ERROR 0x5B	//时钟错误
#define KNG_POS_PARAM_ERROR 0x5C	//参数错误
#define KNG_POS_NO_RECORD 0x5D		//没有流水采集
#define KNG_POS_CONFIRM_SERI 0x5E	//采集流水问题
#define KNG_POS_NOT_SUPP_CARDTYPE 0x5F //不可识别卡
#define KNG_POS_HARDWARE_ERROR 0xB1 //设备故障, 只有在读写 FEROM , EEPROM 失败时，才会提示这个错误，
									// 在这种情况下，POS机进入错误异常提示界面，不允许工作，必须重启POS机
#define KNG_POS_DAIL 0x60           // GPRS 拨号失败
#define KNG_POS_DAIL_ERR 0x61       // GPRS 请求失败
#define KNG_POS_GPRS_RECV 0x62      // GPRS recv

#define KNG_POS_USER_CANCEL 0xA0 // 用户取消
#define KNG_POS_TIMEOUT 0xA1 // 超时
#define KNG_POS_ERROR	0xA2 // 一般错误
#define KNG_NOT_SUPPORT_CMD 0x0A3 // 不支持指令
#define KNG_COM_PACK_INV 0xA4 // 通讯数据包不合法
#define KNG_CRC_ERROR	0xA5	//数据校验错误 

#define KNG_LOGIN_DENY	0x30  //登录卡片错误
#define KNG_READ_CARD	0x31 //读卡失败
#define KNG_WRITE_CARD	0x32 //写卡失败
#define KNG_READ_PSAM_CARD 0x33 // 读PSAM 卡


#define POS_PHYID_ADDR 0x00 // 设备物理ID号地址
#define POS_REC_PTR_ADDR 0x000010 // 记录指针参数表地址
#define POS_WORKKEY_ADDR 0x40  // 工作密钥地址
#define POS_CONSUME_PARA_ADDR 0x60 // 消费参数表
#define POS_COL_DATE_ADDR 0x80 // 采集时间参数
#define POS_REC_BAK_PTR_ADDR 0x0000A0 // 备份记录指针参数表地址
#define POS_WELCOMEMSG_ADDR 0xD0 // 欢迎信息地址
#define POS_CONSUME_HIS_ADDR 0xE0 // 消费情况历史数据地址
#define POS_GPRS_PARA_ADDR 0xF0 // GPRS 参数地址
//#define POS_RECORD_BEGIN_ADDR	0x030EC0 // 流水记录开始地址
#define POS_RECORD_BEGIN_ADDR 0x310C0// 流水记录开始地址
#define POS_RECORD_END_ADDR 0x080000 // 流水记录结束地址
//#define POS_RECORD_END_ADDR 0x0312C0 // 流水记录结束地址(测试)

#define POS_CARDRIGHT_ADDR 0x030D80 // 卡权限表
#define POS_BLK_BEGIN_ADDR 0x000120 // 黑名单起始地址
#define POS_BLK_END_ADDR   0x030D3F   // 黑名单结束地址
#define POS_BLK_BYTE       199744  // 黑名单字节数
#define POS_BLKVER_ADDR    0x030D60 // 黑名单版本号地址
#define POS_CARDGROUP_ADDR 0x030EC0 // 卡类分组参数表

#define POS_REC_LEN 64 // 记录大小
#define POS_MAX_CARD_REC 10 // 卡中保存流水记录条数
#define POS_MAX_REC_CNT ((POS_RECORD_END_ADDR - POS_RECORD_BEGIN_ADDR)>>6)

/// 按键定义
#define KEY_ENTYER		0x08
#define KEY_ESC			0x05
#define KEY_DOWN		0x01
#define KEY_UP			0x02
#include "include/datatype.h"
#include <stdarg.h>

#include "config.h"

#define Z18_OK 1 // z18 pos API success 
#define Z18_FAILED 0 // z18 pos API failed

#define Z18_RECORD_VER 0x10 // POS流水结构版本

#define Z18_AUDIO_DELAY 75 // 75ms
#define Z18_AUDIO_DELAY_100  100	  // 100ms

#define REC_BLACK 0x00 // 黑卡
#define REC_NORMAL 0x0A //正常
#define REC_INVAL 0xFF // 无效
#define REC_UNEXPECT 0x02 // 中途拔卡



#define PSAM_SLOT 1 // PSAM 卡槽号
#define PSAM_CMD_SUCCESS 0x9000 // PSAM 指令成功返回码
#define CPU_USER_FILE_SPI 0x15 // 用户基本数据文件号
#define CPU_CONSUM_FILE_SPI 0x12 // 用户交易规则文件
#define CPU_CONSUM_FILE_SPI_IMMC	0x18		//交易明细文件
#define CPU_CMD_SUCCESS "\x90\x00" // CPU 卡指令返回状态

#define IS_CPUCMD_SUCC_RET(x) (memcmp((x).cReBuff+(x).cReLen-3,CPU_CMD_SUCCESS,2)!=0)

#if ENABLE_MIFARE_CARD
#define NOMARL_CARD_FLAG 0xFF
#else
#define NOMARL_CARD_FLAG 0x00
#endif



///////////////////////////////////////////////////
//  语音文件定义
//  请重刷卡
#define AU_TRY_AGAIN 1		
//  无效卡
#define AU_INVALID_CARD 2
// 学生卡
#define AU_STUDENT_CARD 3
// 教师卡
#define AU_TEACHER_CARD 4
// 临时卡
#define AU_TEMP_CARD 5
// 免费卡
#define AU_FREE_CARD 6
// 挂失卡
#define AU_LOST_CARD 7
// 不能重扣
#define AU_REPEAT 8
// 叮咚
#define AU_DINGDONG 9
// 叮
#define AU_DING 10
// 采集完成
#define AU_COL_FINISH 11
// 职工卡
#define AU_STAFF_CARD 12
// 管理卡
#define AU_MANAGE_CARD 13
// 请采集
#define AU_NEED_COL 14
// 请充值
#define AU_ADD_MONEY 15
// 请投币
#define AU_INSERT_COIN 16


#define Z18POS_COM_BAUD 57600

//
#define Z18POS_LED_ON 0
#define Z18POS_LED_OFF 1
#define Z18POS_LED_GREEN 1
#define Z18POS_LED_RED 2


typedef struct {
	uint8 mainkey[8];
	uint8 device_id[4];
	uint8 rec_ptr_flag;
	uint32 rec_wr_ptr;
	uint32 rec_rd_ptr;
	uint32 serial_no;
	uint8 rec_status;	// 当前记录的流水状态 ，0表示正常，1表示无效
	uint8 consume_ver[6]; // 消费参数版本
	uint32 base_money;
	uint16 card_interval; // 连续刷卡间隔
	uint8 collrec_interval; // 采集流水时间间隔
	uint8 uncoll_days; // 未采集天数
	uint8 last_tx_date[3]; // 最后交易日期, BCD
	uint32 total_money; // 当日累计消费额
	uint32 pre_total_money; //前日累计消费额
	uint8 use_card_right; // 是否设置了权限与分组
	uint8 card_right_ver[6]; // 卡权限版本
	uint8 card_right[32];
	uint8 card_fee[256];
    uint8 card_group[256]; // 卡类分组
	uint8 curr_time[7]; // YYYYMMDDHIMISS BCD码
	uint8 rec_buffer[64];
	uint8 welcome_msg[20]; // 欢迎信息
	uint8 blk_buffer[32]; //黑名单
	uint32 blk_begin_addr;// 黑名单起始地址, 0x00 表示未启用黑名单,0xFFFFFFFF 表示初始状态
	uint8 blk_ver[6]; // 黑名单版本号
	uint8 psam_termid[6]; // PSAM 卡终端号
#if USE_GPRS
    uint8 svr_ip[4];  // GPRS 服务器IP
    uint16 svr_port;  // GPRS 服务器端口
    uint8 local_sock; // GPRS socket
    uint16 local_port; // GRPS local port
#endif

}z18pos_param_t;

#define MAX_CARD_GROUP 6

typedef struct {
	uint8 ver;				// 流水版本
	uint8 device_id[4];		// 设备物理 ID
	uint32 serial_no;		// 流水号
	uint32 card_id;			// 交易卡号
	uint32 in_balance;		// 入卡金额
	uint32 tx_money;		// 交易金额
	uint16 tx_count;		// 交易次数
	uint8 tx_datetime[6];  // 交易日期, BCD
	uint8 tx_mark;			// 交易标志 
	uint8 tx_type;			// 交易类型
	uint8 purse_no;			// 钱包号
	uint8 pre_device_id[4]; // 前一笔设备物理ID
	uint8 pre_tx_time[4];	// 前一笔流水时间, BCD
	uint32 pre_in_balance;  // 前一笔入卡金额
	uint32 pre_tx_money;	// 前一笔交易金额
	uint32 pre_tx_mark;		// 前一笔交易标志
	uint16 tx_crc;			// crc
	uint8 tx_status;		// 交易状态
	uint32 wr_ptr;			// 写地址信息
}z18_record_t;


extern z18pos_param_t xdata g_z18pos;

typedef struct {
	uint8 phyno[8];
	uint8 keya[6];
	uint8 keyb[6];
	uint32 card_id;	// 交易卡号
	uint8 purse_sect; // 主钱包扇区号
	uint8 purse_type; // 0 主钱包，1备钱包
	uint32 balance; // 余额
	uint32 money; // 交易金额
	uint16 trade_count; // 交易次数
	uint16 subsidy_no; // 补助批次号
#if SAVE_CARD_REC==0
	uint8 card_comsume_date[6]; // 交易日期, BCD
#endif
	uint8 last_consume_date[6]; // 上次交易日期 , BCD
	uint8 card_type; // 卡权限
	uint8 black_ver[6]; //黑名单版本号, BCD
	uint8 black_flag; //锁卡标志
	uint8 rec_index; // 卡中记录索引号
	uint8 last_login_sect; // 上次登录扇区
}mifare_card_t;

typedef struct{
	uint8 process;
	uint8 rd_rec_sect;
	uint8 wr_rec_sect;
	uint8 wr_block;
	uint8 device_id[4];
	uint8 date_time[4]; // BCD
	uint32 tx_money;
	uint32 in_bala; 
}card_rec_info_t;

typedef struct {
    uint32 byte_offset;
    uint32 offset;
    uint8 bit_offset;
}blk_mem_info_t;


#include "config.h"

extern mifare_card_t xdata g_mycard;

extern uint8 data g_errorno;


/** 
 * @brief 全局使用的 data 缓存变量
 */
extern uint8 data g_rec_data[64];

/** 
 * @brief 全局使用的 xdata 缓存变量
 */
extern uint8 xdata g_global_buf[1024];
/** 
 * @brief 检查 pos 机参数，确保能正确执行
 * 
 * @return 
 */
int kng_check_pos_param();

/** 
 * @brief 等待
 * 
 * @param secs  - 单位为100ms
 */
void kng_sleep(uint16 secs);

/** 
 * @brief 输出错误
 * 
 * @param error 
 * @param msg 
 */
void print_error1(uint16 line,INT16U error,const char *msg);

#define print_error(x,y) print_error1(__LINE__,x,y)
/** 
 * @brief 格式化float值
 * 
 * @param v 
 * @param str 
 */
void d4u5_str(float v,uint8 *str);
/** 
 * @brief 输出文本
 * 
 * @param line 
 * @param sleep 
 * @param fmt 
 * @param ... 
 */
void print_line(uint8 line,uint8 sleep,const char *fmt,...);

/** 
 * @brief 写 EEPROM
 * 
 * @param addr 
 * @param len 
 * @param retries 
 * @param buf 
 * 
 * @return 
 */
uint8 z18pos_write_eeprom(uint32 addr,uint8 len,uint8 retries,uint8 *buf);

/** 
 * @brief 读 EEPROM
 * 
 * @param addr 
 * @param len 
 * @param retries 
 * @param buf 
 * 
 * @return 
 */
uint8 z18pos_read_eeprom(uint32 addr,uint8 len,uint8 retries,uint8 *buf);

bit z18pos_wait_key(uint8 key,uint8 timeout);

bit z18pos_check_rec_full();
bit z18pos_check_coll_interval();

uint8 z18pos_calc_blkinfo(uint32 card_id,blk_mem_info_t *blk);

// 检查营业额
uint8 z18pos_check_consume();
uint8 update_pre_total(uint8* total);

uint8 do_update_blksheet(uint8 *card_data);
uint8 do_update_blksheet_ver(uint8 *blkver);



#if DEBUG
void debug_hex(uint8 *hex,uint16 len);
void my_debug_string(const char *fmt,...);
#define debug_string(x) my_debug_string x
#else
#define debug_hex(x,y) do{}while(0)
#define debug_string(x) do{}while(0)
#endif

#if ENABLE_AUDIO
#define KNG_AUDIO(x,y) do{ audio(x,y); } while(0)
//#define KNG_AUDIO(x,y) audio(x,y)
#else
#define KNG_AUDIO(x,y) do{  } while(0)
#endif


#endif // _KNG_Z18POS_H_


