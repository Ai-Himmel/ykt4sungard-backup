#include "reg52.h"
#include "Include/LibFuntion.h"
#include "stdio.h"
#include <string.h>
#include <absacc.h>
#include <stdarg.h>
#include <stdlib.h>

#define KEY_ENTYER		0x08
#define KEY_ESC			0x05
#define KEY_DOWN		0x01
#define KEY_UP			0x02

#define Z18_OK 1 // z18 pos API success 
#define Z18_FAILED 0 // z18 pos API failed
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



#define PSAM_SLOT 1 // PSAM ���ۺ�
#define PSAM_CMD_SUCCESS 0x9000 // PSAM ָ��ɹ�������
#define CPU_USER_FILE_SPI 0x15 // �û����������ļ���
#define CPU_CONSUM_FILE_SPI 0x12 // �û����׹����ļ�
#define CPU_CMD_SUCCESS "\x90\x00" // CPU ��ָ���״̬

#define IS_CPUCMD_SUCC_RET(x) (memcmp((x).cReBuff+(x).cReLen-3,CPU_CMD_SUCCESS,2)!=0)

#define NOMARL_CARD_FLAG 0x00

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

mifare_card_t xdata g_mycard;
z18pos_param_t xdata g_z18pos;


static uint32 data r,t;
uint32 get_3byte_int(uint8 *buffer)
{
	t = buffer[0];
	r = t<<16;
	t = buffer[1];
	r += t<<8;
	r+=buffer[2];
	return r;
}
uint32 get_4byte_int(uint8 *buffer)
{
	t = buffer[0];
	r = t<<24;
	t = buffer[1];
	r += t<<16;
	t = buffer[2];
	r += t<<8;
	r += buffer[3];
	return r;
}

uint16 get_2byte_int(uint8 *buffer)
{
	uint16 r;
	memcpy((uint8*)&r,buffer,2);
	return r;
}
void set_2byte_int(uint16 value,uint8 *buffer)
{
	memcpy(buffer,(uint8*)&value,2);
}

void set_4byte_int(uint32 value,uint8 *buffer)
{
	buffer[0] = (uint8)((value>>24)&0xFF);
	buffer[1] = (uint8)((value>>16)&0xFF);
	buffer[2] = (uint8)((value>>8)&0xFF);
	buffer[3] = (uint8)(value&0xFF);
}


static void debug_hex(uint8 *hex,uint16 len)
{
	uint16 sect;
	sect = len >> 3;
	if(len % 8 > 0) sect++;
	if(sect == 0) sect = 1;

	DebugData((uint32)len,16,hex);
}

static void debug_string(const char *fmt,...)
{
	char msg[64];
	va_list p;
	va_start(p,fmt);
	vsprintf(msg,fmt,p);
	va_end(p);
	DebugString(msg);
}

static void bcd2hex(uint8 *bcd,uint8 len,uint8 *hex)
{
	uint8 i;
	for(i=0;i<len;++i)
	{
		hex[i] = ((bcd[i]&0xF0)>>4)*10;
		hex[i] += (bcd[i]&0x0F);
	}
}
static void hex2bcd(uint8 *hex,uint8 len,uint8 *bcd)
{
    uint8 i;
    for(i=0;i<len;++i)
    {
        bcd[i] = (hex[i]/10) << 4;
        bcd[i] += (hex[i]%10);
    }
}

void bcd2str(uint8 *bcd,uint8 len,uint8 *str)
{
	uint8 i;
	for(i = 0;i < len; ++i)
	{
		str[i<<1] = ((bcd[i] >> 4) & 0x0F) + 0x30;
		str[(i<<1)+1] = (bcd[i] & 0x0F) + 0x30;
	}

}

static bit g_reset_card = 0;
///// CPU ����غ���
static uint8 cpu_reset()
{
    DES_EXCHANGE exch;
    memset(&exch,0,sizeof exch);
    exch.cSeLen = 2;
    exch.cSendBuff[0] = 0xe0;
    exch.cSendBuff[1] = 0x50;
    if(DesFireExchangeData(&exch)!=Z18_OK)
    {
        return 1;
    }
    g_reset_card = 1;
    return 0;
}

static uint8 cpu_sendcmd(DES_EXCHANGE xdata *ex)
{
    if(g_reset_card==1)
    {
        g_reset_card = 0;
        ex->cSendBuff[0] = 0x0A;
        ex->cSendBuff[1] = 0x00;
		ex->cSeLen += 2;
    }
    else
    {
        ex->cSendBuff[0] = 0x0B;
        ex->cSendBuff[1] = 0x00;
        g_reset_card = 1;
		ex->cSeLen += 2;
    }
    if(DesFireExchangeData(ex)!=Z18_OK)
    {
        return 1;
    }
    return 0;
}

uint8 cpu_read_binary_file(DES_EXCHANGE xdata *ex,uint8 SFI,uint8 offset,uint8 len)
{
	ex->cSendBuff[2] = 0x00;
	ex->cSendBuff[3] = 0xB0;
	ex->cSendBuff[4] = 0x80 + SFI;
	ex->cSendBuff[5] = offset;
	ex->cSendBuff[6] = len;
	ex->cSeLen = 5;
	if(cpu_sendcmd(ex))
	{
		debug_string("read binary file\n");
		return KNG_READ_CARD;
	}
	if(ex->cReLen < len)
	{
		return KNG_READ_CARD;
	}
	return 0;
}


#define do_is_under_interval(_s1,_s2) do { \
	if(_s1 > _s2) \
	{ \
		if(_s1 - _s2 <= g_z18pos.card_interval) return KNG_POS_REPEAT_CONSUME; \
	} else if( _s1 <= _s2) return KNG_POS_REPEAT_CONSUME; \
	}while(0)
	
static int do_check_card_interval(z18_record_t *record)
{
	
#if CHECK_CARD_INVTERVAL
	char ret;
	uint32 s1,s2;


	ret = memcmp(g_mycard.card_comsume_date,g_mycard.last_consume_date,5);
    //print_line(1,10,g_mycard.card_comsume_date);
	if(ret==0)
	{
		debug_string(("consume date equals\n"));

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
		debug_string(("not write card\n"));
		
	}
	else 
	{
		debug_string(("had write card\n"));
		// �Ѿ�д������������
		if(memcmp(g_z18pos.curr_time+1,g_mycard.card_comsume_date,3)<=0)
		{
			s1 = time_2_secs(g_z18pos.curr_time+4);
			s2 = time_2_secs(g_mycard.card_comsume_date+3);
			do_is_under_interval(s1,s2);
		}
	}
#endif 
	
	return 0;
}


uint8 read_card_info(const uint8 *phyno)
{
    DES_EXCHANGE xdata exh;
	uint8 offset;
	uint8 temp[10];
    uint8 cmd[12] = {0x00,0xa4,0x00,0x00,0x02,0xdf,0x03};
    memset(&exh,0,sizeof exh);
    // ѡ��У԰��֧��Ӧ��
    // 00a4000002df03
    memcpy(exh.cSendBuff + 2,cmd,7);
	exh.cSeLen = 7;
    if(cpu_sendcmd(&exh)!=0)
    {
        return KNG_READ_CARD;
    }
	memset(&exh,0,sizeof exh);
	if(cpu_read_binary_file(&exh,CPU_USER_FILE_SPI,0,56)!=0)
	{
		return KNG_READ_CARD;
	}
	// ����
	offset = 9;
	memset(temp,0,sizeof temp);
	bcd2str(exh.cReBuff+offset,3,temp);
	debug_hex(exh.cReBuff,56);
	g_mycard.card_id=atol(temp);  // ���׿���
	debug_string("card %lu\n",g_mycard.card_id);
	offset += 3 + 10;
	g_mycard.black_flag = exh.cReBuff[offset]; // ������־
	offset++;
	if(g_mycard.black_flag != NOMARL_CARD_FLAG)
		return KNG_POS_BLACK_CARD;
	
	memcpy(g_mycard.black_ver,exh.cReBuff+offset+1,6); // �������汾��
	offset += 7;
	offset += 6;
	
	g_mycard.card_type = exh.cReBuff[offset]; // ��Ȩ�����
	offset++;
	offset+=5;
	// �Ƚ���Ч��
	if(memcmp(g_z18pos.curr_time+1,exh.cReBuff+offset,3)>0)
	{
		return KNG_POS_EXPIRED_CARD;
	}
	
    return 0;
}

static uint8 GenerateRandom(char *buff)
{
	DES_EXCHANGE xdata exh;
	memset(&exh,0,sizeof exh);
	memcpy(exh.cSendBuff+2,"\x00\x84\x00\x00\x04",5);
	exh.cSeLen = 5;
	if(cpu_sendcmd(&exh))
	{
		return KNG_READ_CARD;
	}
	memcpy(buff,exh.cReBuff+2,4);
	return 0;
}
static uint8 CalcDF03SafeMac4Sam(const uint8 xdata *cmd,const uint8 xdata *random_data,uint8 len,uint8 xdata * mac)
{
	uint8 ret,offset;
	APDU_SEND send;
	APDU_RESP recv;
	/*
	memset(&send,0,sizeof send);
	memset(&recv,0,sizeof recv);
	memcpy(send.Command,"\x00\x84\x00\x00",4);
	send.Lc=0;
	send.Le=4;
	if(!IccIsoCommand(PSAM_SLOT,&send,&recv))
	{
		debug_string("psam random err\n");
		return KNG_READ_PSAM_CARD;
	}
	if(recv.SW!=PSAM_CMD_SUCCESS)
	{
		debug_string("psam random err sw[%x]\n",recv.SW);
		return KNG_READ_PSAM_CARD;
	}
	debug_string("psam random[%04x]\n",recv.SW);
	debug_hex(recv.DataOut,recv.LenOut);
	*/
	
	
		
	// delivery key
	memset(&send,0,sizeof send);
	memset(&recv,0,sizeof recv);
	memcpy(send.Command,"\x80\x1A\x28\x01",4);
	send.Lc=8;
	send.Le=0;
	memcpy(send.DataIn,g_mycard.phyno,8);
	IccIsoCommand(PSAM_SLOT,&send,&recv);
	
	if(recv.SW!=PSAM_CMD_SUCCESS)
	{
		debug_string("psam delivery err sw[%X]\n",recv.SW);
		return KNG_READ_PSAM_CARD;
	}
	
	// cipher data
	memset(&send,0,sizeof send);
	memset(&recv,0,sizeof recv);
	memcpy(send.Command,"\x80\xFA\x05\x00",4);
	memcpy(send.DataIn,random_data,8);
	offset = 8;
	memcpy(send.DataIn+offset,cmd,len);
	offset += len;
	if(len % 8 == 0)
	{
		memcpy(send.DataIn+offset,"\x80\x00\x00\x00\x00\x00\x00\x00",8);
		offset += 8;
	}
	else
	{
		len = 8 - (offset % 8);
		memcpy(send.DataIn+offset,"\x80\x00\x00\x00\x00\x00\x00\x00",len);
		offset += len;
	}
	send.Lc = offset;
	send.Le = 0;
	IccIsoCommand(PSAM_SLOT,&send,&recv);
	if((recv.SW & 0x6100) != 0x6100)
	{
		debug_string("psam cipher err sw[%X]\n",recv.SW);
		return KNG_READ_PSAM_CARD;
	}
	ret = (uint8)(recv.SW & 0xFF);
	
	// get response
	memset(&send,0,sizeof send);
	memset(&recv,0,sizeof recv);
	memcpy(send.Command,"\x00\xC0\x00\x00",4);
	send.Le = ret;
	IccIsoCommand(PSAM_SLOT,&send,&recv);
	if(recv.SW != PSAM_CMD_SUCCESS)
		return KNG_READ_PSAM_CARD;
	
	memcpy(mac,recv.DataOut,4);
	return 0;
	
}

uint8 read_card_purse(z18_record_t *record,card_rec_info_t *card_rec)
{
	DES_EXCHANGE xdata exh;
	uint8 random_data[8];
	uint8 offset,ret;
	uint16 last_cnt;
	uint8 xdata cmd[40] = {0x80,0x50,0x01,0x02,0x0B,0x01,0x00,0x00,0x00,0x00,0x11,0x22,0x33,0x44,0x55,0x66};
	uint8 xdata mac[4];
	memset(&exh,0,sizeof exh);
	exh.cSeLen = 16;
	memcpy(exh.cSendBuff+2,cmd,exh.cSeLen);
	
	if(cpu_sendcmd(&exh)!=0)
	{
		return KNG_READ_CARD;
	}
	if(exh.cReLen < 8)
		return KNG_READ_CARD;
	debug_string("read balance\n");
	offset = 2;
	g_mycard.balance = get_4byte_int(exh.cReBuff+offset);
	offset += 4;
	g_mycard.trade_count = get_2byte_int(exh.cReBuff+offset);
	
	// ���ϴν���ʱ�����
	memset(&exh,0,sizeof exh);
	if(cpu_read_binary_file(&exh,CPU_CONSUM_FILE_SPI,0,16)!=0)
	{
		return KNG_READ_CARD;
	}
	debug_string("read consume \n");
	debug_hex(exh.cReBuff,exh.cReLen);
	offset = 6+2;
	last_cnt = get_2byte_int(exh.cReBuff+offset);
	offset += 2;
	/*
	if(last_cnt <= g_mycard.trade_count)
	{
		// �ۿ�ɹ����������������ж�
	}
	else if(last_cnt == g_mycard.trade_count + 1)
	{
		// �ϴοۿ�Ϊ��ɣ�ֱ�ӿۿ�
		goto L_END;
	}
	else if(last_cnt > g_mycard.trade_count)
	{
		// ���������⣬���������̴���
	}
	*/
	if(last_cnt == g_mycard.trade_count + 1)
	{
		// �ϴοۿ�Ϊ��ɣ�ֱ�ӿۿ�
		
	}
	else
	{
		memcpy(g_mycard.last_consume_date,g_z18pos.curr_time+1,6);
		memcpy(g_mycard.last_consume_date+2,exh.cReBuff+offset,4);
		offset+=4;
		memcpy(record->pre_device_id,exh.cReBuff+offset,4);
		ret = do_check_card_interval(record);
		if(ret)
		{
			debug_string("check card\n");
			return ret;
		}
		debug_hex(g_mycard.last_consume_date,6);
		debug_hex(record->pre_device_id,4);
		// ���¿ۿ�ʱ��
		cmd[0] = 0x04;
		cmd[1] = 0xD6;
		cmd[2] = 0x80 + CPU_CONSUM_FILE_SPI;
		cmd[3] = 6; // �ļ�ƫ��
		cmd[4] = 10 + 4; // ���³���, 10 byte ���� + 4 byte MAC
		offset = 5;
		set_2byte_int(g_mycard.trade_count+1,cmd+offset);
		offset += 2;
		memcpy(cmd+offset,g_z18pos.curr_time+3,4);
		offset += 4;
		memcpy(cmd+offset,g_z18pos.device_id,4);
		offset += 4;
		debug_hex(cmd,offset);
		// CPU ��ȡ�����
		memset(random_data,0,sizeof random_data);
		ret = GenerateRandom(random_data);
		if(ret)
		{
			debug_string("gen random number\n");
			return ret;
		}
		ret = CalcDF03SafeMac4Sam(cmd,random_data,offset,mac);
		if(ret)
		{
			debug_string("CalcDF03SafeMac4Sam error \n");
			return ret;
		}
		//debug_string("calc DF03 mac len[%d]\n",(uint16)offset);
		//debug_hex(mac,4);
		memcpy(cmd+offset,mac,4);
		offset += 4;
		memset(&exh,0,sizeof exh);
		memcpy(exh.cSendBuff+2,cmd,offset);
		exh.cSeLen = offset;
		ret = cpu_sendcmd(&exh);
		if(ret || IS_CPUCMD_SUCC_RET(exh))
		{
			debug_string("update consumer file err[%d]\n",(uint16)exh.cReLen);
			return KNG_WRITE_CARD;
		}
	}
    return 0;
}
uint8 write_card_purse(z18_record_t *record,card_rec_info_t *card_rec)
{
	uint8 ret,offset;
	APDU_SEND xdata send;
	APDU_RESP xdata recv;
	DES_EXCHANGE xdata exh;
	
	memset(&exh,0,sizeof exh);
	memcpy(exh.cSendBuff+2,"\x80\x50\x01\x02\x0B\x01",6);
	offset = 2+6;
	set_4byte_int(record->tx_money,exh.cSendBuff+offset);
	offset += 4;
	memcpy(exh.cSendBuff+offset,g_z18pos.psam_termid,6);
	offset += 6;
	exh.cSeLen = offset - 2;
	ret = cpu_sendcmd(&exh);
	if(ret)
	{
		return KNG_READ_CARD;
	}
	//debug_hex(exh.cReBuff,exh.cReLen);
	if(ret || IS_CPUCMD_SUCC_RET(exh))
	{
		debug_string("init consumer err[%d]\n",(uint16)exh.cReLen);
		return KNG_WRITE_CARD;
	}
	
	memset(&send,0,sizeof send);
	memset(&recv,0,sizeof recv);

    memcpy(send.Command,"\x80\x70\x00\x00",4);
    offset = 0;
    memcpy(send.DataIn+offset,exh.cReBuff+13,4); // �����
    offset += 4;
    memcpy(send.DataIn+offset,exh.cReBuff+6,2); // ���״���
    offset += 2;
    set_4byte_int(record->tx_money,send.DataIn+offset); // ���׽��
    offset += 4;
    send.DataIn[offset++] = 0x06; // �������ͱ�ʶ
    memcpy(send.DataIn+offset,g_z18pos.curr_time,7); // �������ڣ�ʱ��
    offset+=7;
    send.DataIn[offset++] = 1; // ��Կ�汾
    send.DataIn[offset++] = 0; // ��Կ�㷨
    memcpy(send.DataIn+offset,g_mycard.phyno,8); // ������
	offset+=8;
	
    send.Lc = offset;
    send.Le = 0x00;

    IccIsoCommand(PSAM_SLOT,&send,&recv);
    if((recv.SW&0x6100)!=0x6100)
    {
        debug_string("sam init for purchase [%X]\n ",recv.SW);
        return KNG_WRITE_CARD;
    }
	memset(&send,0,sizeof send);
	memcpy(send.Command,"\x00\xC0\x00\x00",4);
	send.Le = (uint8)(recv.SW&0xFF);
	memset(&recv,0,sizeof recv);
	//debug_string("get resp[%d]",(uint16)send.Le);
	IccIsoCommand(PSAM_SLOT,&send,&recv);
    if(recv.SW != PSAM_CMD_SUCCESS)
    {
        debug_string("sam purchase resp [%X]\n ",recv.SW);
        return KNG_WRITE_CARD;
    }
    //debug_hex(recv.DataOut,recv.LenOut);	
	
	memset(&exh,0,sizeof exh);
	memcpy(exh.cSendBuff+2,"\x80\x54\x01\x00\x0F",5);
	offset = 2+5;
	memcpy(exh.cSendBuff+offset,recv.DataOut,4); // term seqno
	offset += 4;
	memcpy(exh.cSendBuff+offset,g_z18pos.curr_time,7); // tx date time
	offset += 7;
	memcpy(exh.cSendBuff+offset,recv.DataOut+4,4); // MAC1
	offset += 4;
	exh.cSeLen = offset - 2;
	ret = cpu_sendcmd(&exh);
	if(ret)
	{
		return KNG_WRITE_CARD;
	}
	//debug_hex(exh.cReBuff,exh.cReLen);
	if(ret || IS_CPUCMD_SUCC_RET(exh))
	{
		debug_string("debit purchase err[%d]\n",(uint16)exh.cReLen);
		return KNG_WRITE_CARD;
	}
	
    return 0;
}

uint8 load_psam_card()
{
	uint8 ret;
	uint8 buff[20];
	APDU_SEND xdata send;
	APDU_RESP xdata recv;
	ret = IccPowOpen(PSAM_SLOT,9600,3,buff);
	if(ret == 0)
	{
		return KNG_READ_PSAM_CARD;
	}
	
	memset(&send,0,sizeof send);
	memset(&recv,0,sizeof recv);
	memcpy(send.Command,"\x00\xB0",2);
	send.Command[2] = 0x80+0x16;
	send.Command[3] = 0;
	send.Lc=0;
	send.Le=6;
	if(!IccIsoCommand(PSAM_SLOT,&send,&recv))
	{
		debug_string("psam get termid err\n");
		return KNG_READ_PSAM_CARD;
	}
	if(recv.SW!=PSAM_CMD_SUCCESS)
	{
		debug_string("psam err sw[%X]\n",recv.SW);
		return KNG_READ_PSAM_CARD;
	}
	memcpy(g_z18pos.psam_termid,recv.DataOut,6);
	memset(&send,0,sizeof send);
	memset(&recv,0,sizeof recv);
	// select
	memcpy(send.Command,"\x00\xA4\x00\x00",4); 
	memcpy(send.DataIn,"\xDF\x03",2);
	send.Lc=2;
	send.Le=0;
	if(!IccIsoCommand(PSAM_SLOT,&send,&recv))
	{
		debug_string("psam select err\n");
		return KNG_READ_PSAM_CARD;
	}
	if((recv.SW & 0x6100) != 0x6100)
	{
		debug_string("psam select err sw[%X]\n",recv.SW);
		return KNG_READ_PSAM_CARD;
	}
	return 0;
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

void main()
{
	uint8 ret,i;
	uint8 phyno[8];
	uint8 sType;
	card_rec_info_t rec;
	z18_record_t record;
	
	delay_1ms(1000);
	bp_beep(30,20);
	DispInitialize();
	//bp_SerialCtl(0,115200);
	bp_SerialCtl(0,57600);
	Lcd_onoff(1);

	Led_OnOff(1,0);
	memset(phyno,0,sizeof phyno);
	memset(&g_z18pos,0,sizeof g_z18pos);
	
	memcpy(g_z18pos.device_id,"\x00\x00\xAA\xBB",4);
	InitRtcTime();
	ReadRtcTime(g_z18pos.curr_time);
	
	ret = loadconfig();
	if(!ret)
	{
		debug_string("load config error\n");
		return;
	}
	ret = load_psam_card();
	if(ret)
	{
		debug_string("load psam card\n");
		return;
	}
	z18pos_wait_key(KEY_ESC,0);
	ret = mif_request(0);
	if (!ret)
	{
		debug_string("no card\n");
		return;
	}

	ret = mif_anticoll(0, phyno);
	if (!ret)
	{
		debug_string("anticoll err\n");
		return;
	}
	

	ret = mif_select(0, phyno, &sType);
	if (!ret)
	{
		debug_string("select err\n");
		return;
	}
	for(i = 0;i< 4;++i)
		g_mycard.phyno[i] = phyno[3-i];
	memcpy(g_mycard.phyno+4,"\x80\x00\x00\x00",4);
	//memcpy(g_mycard.phyno,phyno,4);
	if(cpu_reset())
	{
		debug_string("cpureset err\n");
		return;
	}
	
	ret = read_card_info(phyno);
	if(ret)
	{
		debug_string("read cpu card\n");
		return;
	}
	memset(&rec,0,sizeof rec);
	memset(&record,0,sizeof record);
	ret = read_card_purse(&record,&rec);
	if(ret)
	{
		debug_string("read cpu balance\n");
		return;
	}
    record.tx_money = 100;
	ret = write_card_purse(&record,&rec);
	if(ret)
	{
		debug_string("write card purse\n");
		return;
	}
	debug_string("success!\n");
}
