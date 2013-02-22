#ifndef _KNG_Z18POS_H_
#define _KNG_Z18POS_H_

#define KNG_POS_SUCCESS 0			//�ɹ�
#define KNG_POS_UNEXPECT_CARD 0x01	//��;�ο�
#define KNG_POS_UNREAD_CARD 0x02	//����ʶ��
#define KNG_POS_PURSE_ERROR 0x03	//��Ǯ������
#define KNG_POS_HAS_RECORD 0x04		//δ�ϴ���ˮ
#define KNG_POS_EXPIRED_COLL 0x05	//�����ɼ�ʱ��
#define KNG_POS_BLACK_CARD 0x06		//�ڿ�
#define KNG_POS_EXPIRED_CARD 0x07	//���ѹ���
#define KNG_POS_NO_RIGHT 0x08		//��Ȩ��
#define KNG_POS_PURSE_LACK 0x09		//������
#define KNG_POS_CARD_LOCKED 0x0A	//������
#define KNG_POS_FREE_CARD 0x0C		//��ѿ�
#define KNG_POS_REC_FULL  0x0D		//��¼����
#define KNG_POS_REPEAT_CONSUME 0x5A	//�ظ�ˢ��
#define KNG_POS_CLOCK_ERROR 0x5B	//ʱ�Ӵ���
#define KNG_POS_PARAM_ERROR 0x5C	//��������
#define KNG_POS_NO_RECORD 0x5D		//û����ˮ�ɼ�
#define KNG_POS_CONFIRM_SERI 0x5E	//�ɼ���ˮ����
#define KNG_POS_NOT_SUPP_CARDTYPE 0x5F //����ʶ��
#define KNG_POS_HARDWARE_ERROR 0xB1 //�豸����, ֻ���ڶ�д FEROM , EEPROM ʧ��ʱ���Ż���ʾ�������
									// ����������£�POS����������쳣��ʾ���棬������������������POS��
#define KNG_POS_DAIL 0x60           // GPRS ����ʧ��
#define KNG_POS_DAIL_ERR 0x61       // GPRS ����ʧ��
#define KNG_POS_GPRS_RECV 0x62      // GPRS recv

#define KNG_POS_USER_CANCEL 0xA0 // �û�ȡ��
#define KNG_POS_TIMEOUT 0xA1 // ��ʱ
#define KNG_POS_ERROR	0xA2 // һ�����
#define KNG_NOT_SUPPORT_CMD 0x0A3 // ��֧��ָ��
#define KNG_COM_PACK_INV 0xA4 // ͨѶ���ݰ����Ϸ�
#define KNG_CRC_ERROR	0xA5	//����У����� 

#define KNG_LOGIN_DENY	0x30  //��¼��Ƭ����
#define KNG_READ_CARD	0x31 //����ʧ��
#define KNG_WRITE_CARD	0x32 //д��ʧ��
#define KNG_READ_PSAM_CARD 0x33 // ��PSAM ��


#define POS_PHYID_ADDR 0x00 // �豸����ID�ŵ�ַ
#define POS_REC_PTR_ADDR 0x000010 // ��¼ָ��������ַ
#define POS_WORKKEY_ADDR 0x40  // ������Կ��ַ
#define POS_CONSUME_PARA_ADDR 0x60 // ���Ѳ�����
#define POS_COL_DATE_ADDR 0x80 // �ɼ�ʱ�����
#define POS_REC_BAK_PTR_ADDR 0x0000A0 // ���ݼ�¼ָ��������ַ
#define POS_WELCOMEMSG_ADDR 0xD0 // ��ӭ��Ϣ��ַ
#define POS_CONSUME_HIS_ADDR 0xE0 // ���������ʷ���ݵ�ַ
#define POS_GPRS_PARA_ADDR 0xF0 // GPRS ������ַ
//#define POS_RECORD_BEGIN_ADDR	0x030EC0 // ��ˮ��¼��ʼ��ַ
#define POS_RECORD_BEGIN_ADDR 0x310C0// ��ˮ��¼��ʼ��ַ
#define POS_RECORD_END_ADDR 0x080000 // ��ˮ��¼������ַ
//#define POS_RECORD_END_ADDR 0x0312C0 // ��ˮ��¼������ַ(����)

#define POS_CARDRIGHT_ADDR 0x030D80 // ��Ȩ�ޱ�
#define POS_BLK_BEGIN_ADDR 0x000120 // ��������ʼ��ַ
#define POS_BLK_END_ADDR   0x030D3F   // ������������ַ
#define POS_BLK_BYTE       199744  // �������ֽ���
#define POS_BLKVER_ADDR    0x030D60 // �������汾�ŵ�ַ
#define POS_CARDGROUP_ADDR 0x030EC0 // ������������

#define POS_REC_LEN 64 // ��¼��С
#define POS_MAX_CARD_REC 10 // ���б�����ˮ��¼����
#define POS_MAX_REC_CNT ((POS_RECORD_END_ADDR - POS_RECORD_BEGIN_ADDR)>>6)

/// ��������
#define KEY_ENTYER		0x08
#define KEY_ESC			0x05
#define KEY_DOWN		0x01
#define KEY_UP			0x02
#include "include/datatype.h"
#include <stdarg.h>

#include "config.h"

#define Z18_OK 1 // z18 pos API success 
#define Z18_FAILED 0 // z18 pos API failed

#define Z18_RECORD_VER 0x10 // POS��ˮ�ṹ�汾

#define Z18_AUDIO_DELAY 75 // 75ms
#define Z18_AUDIO_DELAY_100  100	  // 100ms

#define REC_BLACK 0x00 // �ڿ�
#define REC_NORMAL 0x0A //����
#define REC_INVAL 0xFF // ��Ч
#define REC_UNEXPECT 0x02 // ��;�ο�



#define PSAM_SLOT 1 // PSAM ���ۺ�
#define PSAM_CMD_SUCCESS 0x9000 // PSAM ָ��ɹ�������
#define CPU_USER_FILE_SPI 0x15 // �û����������ļ���
#define CPU_CONSUM_FILE_SPI 0x12 // �û����׹����ļ�
#define CPU_CONSUM_FILE_SPI_IMMC	0x18		//������ϸ�ļ�
#define CPU_CMD_SUCCESS "\x90\x00" // CPU ��ָ���״̬

#define IS_CPUCMD_SUCC_RET(x) (memcmp((x).cReBuff+(x).cReLen-3,CPU_CMD_SUCCESS,2)!=0)

#if ENABLE_MIFARE_CARD
#define NOMARL_CARD_FLAG 0xFF
#else
#define NOMARL_CARD_FLAG 0x00
#endif



///////////////////////////////////////////////////
//  �����ļ�����
//  ����ˢ��
#define AU_TRY_AGAIN 1		
//  ��Ч��
#define AU_INVALID_CARD 2
// ѧ����
#define AU_STUDENT_CARD 3
// ��ʦ��
#define AU_TEACHER_CARD 4
// ��ʱ��
#define AU_TEMP_CARD 5
// ��ѿ�
#define AU_FREE_CARD 6
// ��ʧ��
#define AU_LOST_CARD 7
// �����ؿ�
#define AU_REPEAT 8
// ����
#define AU_DINGDONG 9
// ��
#define AU_DING 10
// �ɼ����
#define AU_COL_FINISH 11
// ְ����
#define AU_STAFF_CARD 12
// ����
#define AU_MANAGE_CARD 13
// ��ɼ�
#define AU_NEED_COL 14
// ���ֵ
#define AU_ADD_MONEY 15
// ��Ͷ��
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
	uint8 rec_status;	// ��ǰ��¼����ˮ״̬ ��0��ʾ������1��ʾ��Ч
	uint8 consume_ver[6]; // ���Ѳ����汾
	uint32 base_money;
	uint16 card_interval; // ����ˢ�����
	uint8 collrec_interval; // �ɼ���ˮʱ����
	uint8 uncoll_days; // δ�ɼ�����
	uint8 last_tx_date[3]; // ���������, BCD
	uint32 total_money; // �����ۼ����Ѷ�
	uint32 pre_total_money; //ǰ���ۼ����Ѷ�
	uint8 use_card_right; // �Ƿ�������Ȩ�������
	uint8 card_right_ver[6]; // ��Ȩ�ް汾
	uint8 card_right[32];
	uint8 card_fee[256];
    uint8 card_group[256]; // �������
	uint8 curr_time[7]; // YYYYMMDDHIMISS BCD��
	uint8 rec_buffer[64];
	uint8 welcome_msg[20]; // ��ӭ��Ϣ
	uint8 blk_buffer[32]; //������
	uint32 blk_begin_addr;// ��������ʼ��ַ, 0x00 ��ʾδ���ú�����,0xFFFFFFFF ��ʾ��ʼ״̬
	uint8 blk_ver[6]; // �������汾��
	uint8 psam_termid[6]; // PSAM ���ն˺�
#if USE_GPRS
    uint8 svr_ip[4];  // GPRS ������IP
    uint16 svr_port;  // GPRS �������˿�
    uint8 local_sock; // GPRS socket
    uint16 local_port; // GRPS local port
#endif

}z18pos_param_t;

#define MAX_CARD_GROUP 6

typedef struct {
	uint8 ver;				// ��ˮ�汾
	uint8 device_id[4];		// �豸���� ID
	uint32 serial_no;		// ��ˮ��
	uint32 card_id;			// ���׿���
	uint32 in_balance;		// �뿨���
	uint32 tx_money;		// ���׽��
	uint16 tx_count;		// ���״���
	uint8 tx_datetime[6];  // ��������, BCD
	uint8 tx_mark;			// ���ױ�־ 
	uint8 tx_type;			// ��������
	uint8 purse_no;			// Ǯ����
	uint8 pre_device_id[4]; // ǰһ���豸����ID
	uint8 pre_tx_time[4];	// ǰһ����ˮʱ��, BCD
	uint32 pre_in_balance;  // ǰһ���뿨���
	uint32 pre_tx_money;	// ǰһ�ʽ��׽��
	uint32 pre_tx_mark;		// ǰһ�ʽ��ױ�־
	uint16 tx_crc;			// crc
	uint8 tx_status;		// ����״̬
	uint32 wr_ptr;			// д��ַ��Ϣ
}z18_record_t;


extern z18pos_param_t xdata g_z18pos;

typedef struct {
	uint8 phyno[8];
	uint8 keya[6];
	uint8 keyb[6];
	uint32 card_id;	// ���׿���
	uint8 purse_sect; // ��Ǯ��������
	uint8 purse_type; // 0 ��Ǯ����1��Ǯ��
	uint32 balance; // ���
	uint32 money; // ���׽��
	uint16 trade_count; // ���״���
	uint16 subsidy_no; // �������κ�
#if SAVE_CARD_REC==0
	uint8 card_comsume_date[6]; // ��������, BCD
#endif
	uint8 last_consume_date[6]; // �ϴν������� , BCD
	uint8 card_type; // ��Ȩ��
	uint8 black_ver[6]; //�������汾��, BCD
	uint8 black_flag; //������־
	uint8 rec_index; // ���м�¼������
	uint8 last_login_sect; // �ϴε�¼����
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
 * @brief ȫ��ʹ�õ� data �������
 */
extern uint8 data g_rec_data[64];

/** 
 * @brief ȫ��ʹ�õ� xdata �������
 */
extern uint8 xdata g_global_buf[1024];
/** 
 * @brief ��� pos ��������ȷ������ȷִ��
 * 
 * @return 
 */
int kng_check_pos_param();

/** 
 * @brief �ȴ�
 * 
 * @param secs  - ��λΪ100ms
 */
void kng_sleep(uint16 secs);

/** 
 * @brief �������
 * 
 * @param error 
 * @param msg 
 */
void print_error1(uint16 line,INT16U error,const char *msg);

#define print_error(x,y) print_error1(__LINE__,x,y)
/** 
 * @brief ��ʽ��floatֵ
 * 
 * @param v 
 * @param str 
 */
void d4u5_str(float v,uint8 *str);
/** 
 * @brief ����ı�
 * 
 * @param line 
 * @param sleep 
 * @param fmt 
 * @param ... 
 */
void print_line(uint8 line,uint8 sleep,const char *fmt,...);

/** 
 * @brief д EEPROM
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
 * @brief �� EEPROM
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

// ���Ӫҵ��
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


