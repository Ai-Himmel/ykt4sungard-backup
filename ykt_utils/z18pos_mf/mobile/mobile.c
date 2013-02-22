/**
 * �ֳֻ�������
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <process.h>
#include <time.h>

#include "include/htlcd.h"
#include "include/htxlcd.h"
#include "include/commplus.h"
#include "include/infrared.h"

#define uint8 unsigned char 
#define uint16 unsigned int
#define uint32 unsigned long 
#define int16 int
#define int8 char
#define int32 long

extern _stklen = 4096u;   /* it very useful to reduce memory in HT-1800 */
extern _heaplen  = 256u;  /*    both stack & heap length must be set    */
#define KEY_BACKSPACE 0x08
#define KEY_ENTER 0x0D
#define KEY_SPACE 0x20
#define KEY_ESC 0x1B
 
#define STX1 0xC0
#define ETX1 0xC1
#define STX2 0xC2 
#define ETX2 0xC3
#define TXSLT 0x47
#define TXPCK_LEN 22

#define VERSION_STR "010118_b1"

#define CMD_RET 4

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
	uint8 reserve[15];		// ����
	uint16 tx_crc;			// crc
	uint8 tx_status;		// ����״̬
}z18_record_t;


uint8 wait_for_key(uint8 key);
uint8 confirm_msg(uint8 line,uint8 *msg);
void debug_cmd(uint8 *cmd,uint16 len);


/** 
 * @brief 
 * 
 * @param buf 
 * 
 * @return 
 */
uint16 get_2byte_int(uint8 *buf);
/** 
 * @brief 
 * 
 * @param buf 
 * 
 * @return 
 */
uint32 get_4byte_int(uint8 *buf);
void display_msg(uint8 line,uint8 *msg);
/** 
 * @brief �����������ݰ�
 * 
 * @param cmd - �������ݰ�
 * @param len - ���ݰ�����
 * 
 * @return - ���ط��ͳɹ������ݰ�����
 */
uint16 send_cmd(uint8 *cmd,uint16 len)
{
	uint8 b,status;
	uint16 start_pos;
	time_t start_time,end_time;
	PutAuxByte(cmd[0]);
	while(1)
	{
		if(GetAuxByte(&b,&status))
		{
			return 0;
		}
		if(b == TXSLT)
			break;
	}
	// send package data
	start_pos = 1;
	b = 0;
	time(&start_time);
	while(start_pos<len)
	{
		if(PutAuxByte(cmd[start_pos]))
		{
			// not success ,continue
			continue;
		}
		b++;
		if(b == TXPCK_LEN )
		{
			while(1)
			{
				GetAuxByte(&b,&status);
				if(b == TXSLT)
					break;
				time(&end_time);
				if(end_time-start_time>5)
					return 0;
			}
			b = 0;
		}
		start_pos++;
	}
	return start_pos;
}

/** 
 * @brief �������ݰ�
 * 
 * @param cmd - �������ݰ�����
 * @param maxlen - �������ݰ���󳤶�
 * @param recv_len - ʵ�ʽ��յĳ���
 * 
 * @return  - 0 ��ʾ����ʧ�� 1 ��ʾ���ճɹ�
 */
uint8 recv_cmd(uint8 *cmd,uint16 maxlen,uint16 *recv_len)
{
	uint16 start_pos,pack_len;
	uint8 b,status;
	time_t start_time,curr_time;
	time(&start_time);
	start_pos = 0;
	do
	{
		if(GetAuxByte(&b,&status))
		//if(!ExistAuxBGot(&b,&status))
		{
			time(&curr_time);
			if(curr_time-start_time>5)
				return 0;
			continue;
		}
	}while(b!=STX2);

	time(&start_time);
	cmd[start_pos++] = b;
	while(start_pos<maxlen)
	{
		//if(GetAuxByte(&b,&status))
		if(!ExistAuxBGot(&b,&status))
		{
			time(&curr_time);
			if(curr_time-start_time>5)
				break;
			// not success ,continue
			continue;
		}
		cmd[start_pos++] = b;
		if(start_pos==3)
		{
			pack_len = get_2byte_int(cmd+1);
		}
		else if(start_pos > 3)
		{
			if(start_pos-3 >= pack_len)
				break;
		}
	}
	if(start_pos >= pack_len+3)
	{
		*recv_len = pack_len+3;
		// �жϰ�����
		if(cmd[start_pos-1] != ETX2)
			return 0;
		return 1;
	}
	else
	{
		return 0;
	}

}
/** 
 * @brief ���� CRC
 * 
 * @param pBuf - buffer
 * @param len  - buffer length
 * 
 * @return - return CRC 16 code
 */
static uint16  GenerateCRC16(const unsigned char *pBuf, uint16 len)
{
	const unsigned int crc16_tab[256] = { 
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 
	0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef, 
	0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6, 
	0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de, 
	0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 
	0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 
	0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 
	0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 
	0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823, 
	0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b, 
	0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12, 
	0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a, 
	0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41, 
	0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 
	0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 
	0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 
	0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 
	0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067, 
	0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e, 
	0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256, 
	0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d, 
	0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 
	0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 
	0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 
	0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 
	0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 
	0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 
	0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92, 
	0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 
	0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1, 
	0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8, 
	0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 
	};


	uint16 crc; 
	unsigned char b, da;
	uint16 charcnt;
	crc = 0; 
	charcnt = 0;
	while (len--)
	{ 
		da = (unsigned char)(crc >> 8);			/* ��8λ������������ʽ�ݴ�CRC�ĸ�8λ */ 
		crc <<= 8;						/* ����8λ���൱��CRC�ĵ�8λ���� */ 
		b = pBuf[charcnt];				// ���ƽ������ֽ�ֵ
		crc ^= crc16_tab[da ^ b];		/* ��8λ�͵�ǰ�ֽ���Ӻ��ٲ����CRC ���ټ�����ǰ��CRC */ 
		charcnt++; 
	} 
	return crc;
}


/** 
 * @brief У�� CRC 
 * 
 * @param buf - buffer 
 * @param len - buffer length
 * @param crc - CRC code
 * 
 * @return  - return 0 success , return 1 faild
 */
static uint8 check_buffer_crc(uint8 *buf,uint16 len,uint8 *crc)
{
	uint16 crc_code,crc_code1;
	crc_code = GenerateCRC16(buf,len);
	crc_code1 = get_2byte_int(crc);	

	return (crc_code == crc_code1) ? 0 : 1;
}
/** 
 * @brief ��ȡ��ǰʱ��
 * 
 * @param curr_time - YYYYMMDDHI24MISS
 */
static void get_curr_time(uint8 *curr_time)
{
	time_t now;
	struct tm *t;
	time(&now);
	t = localtime(&now);
	sprintf(curr_time,"%04d%02d%02d%02d%02d%02d"
			,t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);

}
/** 
 * @brief �ַ���ת BCD
 * 
 * @param str - �ַ���
 * @param len - �ַ�������
 * @param bcd - ת BCD ��
 */
static void str2bcd(uint8* str,uint8 len,uint8 *bcd)
{
	uint8 i;
	if(len % 2 != 0)
	{
		return;
	}
	for(i = 0;i < len;i+=2)
	{
		bcd[i>>1] = (((str[i]-0x30)<<4)&0xF0) + ((str[i+1]-0x30)&0x0F);
	}
}
/** 
 * @brief BCD ��ת�ַ���
 * 
 * @param bcd - BCD ��
 * @param len - BCD �볤��
 * @param str - ת�ַ���
 */
static void bcd2str(uint8 *bcd,uint8 len,uint8 *str)
{
	uint8 i;
	for(i = 0;i < len;++i)
	{
		str[i<<1] = ((bcd[i] >> 4)&0x0F);
		str[(i<<1)+1] = (bcd[i]& 0x0F);
	}
}
/** 
 * @brief - ����У���
 * 
 * @param buf - ����� buffer
 * @param len - У��ͳ���
 * 
 * @return - ����У���
 */
static uint8 calc_sum(uint8 *buf,uint16 len)
{
	uint16 i;
	uint8 ret;
	for(i = 0,ret = 0;i < len;++i)
	{
		ret += (uint8)buf[i];
	}
	return ret;
}
static void do_show_version()
{
	uint8 msg[32];
	display_msg(1,"SunGard");
	sprintf(msg,"�汾��%s",VERSION_STR);
	confirm_msg(2,msg);
}
/** 
 * @brief ��ȡ��ǰʱ��� bcd ��
 * 
 * @param curr_time - bcd ��ʱ��
 */
static void get_curr_time_bcd(uint8 *curr_time)
{
	uint8 temp[15];
	get_curr_time(temp);
	str2bcd(temp,14,curr_time);
}


void debug_cmd(uint8 *cmd,uint16 len)
{
	char msg[32];
	uint16 i,j,p;
	clrscr();
	for(i = 0,j = 0;i < len;i+=8)
	{
		memset(msg,0,sizeof msg);
		p = (len-i>=8) ? 8 : (len-i);
		for(j=0;j<p;j++)
		{
			sprintf(msg+j*2,"%02X",cmd[i+j]);
		}
		saycstr(1,i/8+2,msg,_attr_NORM);
	}
	wait_for_key(KEY_ENTER);
	clrscr();
}

uint8 wait_for_key(uint8 key)
{
	uint8 k;
	do{
		if(kbhit())
		{
			k = getch();
			if(key == k)
				return k;
		}
	}while(1);
}

uint8 confirm_msg(uint8 line,uint8 *msg)
{
	uint8 k;
	uint8 line_msg[17];
	memset(line_msg,' ',sizeof(line_msg)-1);
	line_msg[16] = 0;
	memcpy(line_msg,msg,strlen(msg));
	if(msg != NULL)
		saycstr(1,line,line_msg,_attr_NORM);
	do{
		if(kbhit())
		{
			k = getch();
			if(KEY_ENTER == k
			   ||KEY_ESC == k)
				return k;
		}
	}while(1);
	return 0;
}
void display_msg(uint8 line,uint8 *msg)
{
	uint8 line_msg[17];
	memset(line_msg,' ',sizeof(line_msg)-1);
	line_msg[16] = 0;
	memcpy(line_msg,msg,strlen(msg));
	saycstr(1,line,line_msg,_attr_NORM);
}
uint8 check_cmd_ret(uint8 *cmd)
{
	return cmd[4];
}

uint32 get_4byte_int(uint8 *buf)
{
	uint32 r,t;
	t = buf[0];
	r = t<<24;
	t = buf[1];
	r += t<<16;
	t = buf[2];
	r += t<<8;
	t = buf[3];
	r += t;
	return r;
}
uint16 get_2byte_int(uint8 *buf)
{
	uint16 r,t;
	t = buf[0];
	r = t<<8;
	r += buf[1];
	return r;
}

static void do_main_process()
{
	uint8 key;
	uint16 recv_len;
	char device_id[9];
	char msg[64];
	// C00003C501C1
	uint8 cmd[10] = {0xC0,0x00,0x03,0xC5,0x01,0xC1};
	uint8 resp[64];
	saycstr(1,1,"׼��У׼POS��",_attr_NORM);
	saycstr(1,2,"��[ȷ��]��ʼ",_attr_NORM);
	saycstr(1,3,"��[ȡ��]����",_attr_NORM);
	do{
		if(kbhit())
		{
			key = getch();
			if(key == KEY_ENTER)
				break;
			else if(key == KEY_ESC)
				return;
			else
			{
				// ?? beep
			}
		}
	}while(1);
	
	
	saycstr(1,2,"�������ӳ��ػ�...",_attr_NORM);
	saycstr(1,3,"                 ",_attr_NORM);
	// ������������
	if(send_cmd(cmd,6)>0)
		saycstr(1,2,"��������ɹ�...",_attr_NORM);
	else
		saycstr(1,2,"��������ʧ��...",_attr_NORM);

	// ����Ӧ������
	if(recv_cmd(cmd,13,&recv_len))
	{
		//debug_cmd(cmd,recv_len);
		saycstr(1,3,msg,_attr_NORM);
		// �ж�Ӧ��
		if(cmd[CMD_RET] == 0x00)
			confirm_msg(2,"����Ӧ��ɹ�...");
		else
			confirm_msg(2,"����Ӧ��ʧ��...");
		return;
	}
	
	//saycstr(1,1,"�������",_attr_NORM);
	return;
}
// 1. У��ʱ�ӹ���
static void do_check_clock()
{
	uint8 len;
	uint16 recv_len;
	uint8 cmd[33] = {STX1,0x00,0x0C,0xC4,0x99,0x07};
	uint8 curr_time[7];
	len = 6;
	get_curr_time_bcd(curr_time);
	debug_cmd(curr_time,7);
	memcpy(cmd+len,curr_time,7);
	len += 7;

	cmd[len++] = calc_sum(cmd+3,len-3);
	cmd[len++] = ETX1;

	if(send_cmd(cmd,len)==0)
	{
		confirm_msg(2,"У��ʱ��ʧ��");	
		return;
	}
	else
	{
		len = 6;
		if(recv_cmd(cmd,len,&recv_len)==0)
		{
			confirm_msg(2,"У��ʱ��ʧ��");	
			return;
		}
		if(recv_len == 0
		   ||cmd[CMD_RET] != 0)
		{
			confirm_msg(2,"У��ʱ��ʧ��");	
			return;
		}
		confirm_msg(2,"У��ʱ�ӳɹ�");
		return ;
	}
}
/** 
 * @brief ���²ɼ�ʱ��
 * 
 * @return 
 */
static uint8 do_update_col_date()
{
	uint16 recv_len,len;
	uint8 cmd[12]={STX1,0x00,0x04,0xB7,0x99};
	len = 5;
	cmd[len++]= calc_sum(cmd+3,len-3);
	cmd[len++]= ETX1;
	if(send_cmd(cmd,len)==0)
	{
		confirm_msg(1,"���²ɼ�ʱ�����");
		return 1;
	}
	else 
	{
		memset(cmd,0,sizeof cmd);
		recv_len = 0;
		if(recv_cmd(cmd,6,&recv_len)==0)
		{
			confirm_msg(1,"���²ɼ�ʱ�����");
			return 1;
		}
		else if(cmd[CMD_RET] == 0x00)
		{
			confirm_msg(1,"���²ɼ�ʱ��");
			return 0;
		}
		else
		{
			confirm_msg(1,"���²ɼ�ʱ�����");
			return 1;
		}
	}
}

/** 
 * @brief �ɼ�POS����ˮ
 * 
 * @param fp - ��ˮ�ļ����
 * @param cnt - ����
 * 
 * @return - 0 ��ʾ�ɹ� 1 ��ʾʧ�� 2��ʾ�Ѿ��ɼ�����
 */
static uint8 do_collect_pos(FILE *fp,uint16 cnt)
{
	uint16 len,recv_len;
	uint32 serial_no;
	uint8 cmd[84] = {STX1,0x00,0x04,0x55,0x00};
	uint8 msg[32];
	len = 5;
	cmd[len++] = calc_sum(cmd+3,len-3);
	cmd[len++] = ETX1;
	
	sprintf(msg,"���ڲɼ���[%d]��",cnt);
	display_msg(1,msg);
	if(send_cmd(cmd,len)==0)
	{
		confirm_msg(1,"�ɼ���ˮʧ��");
		return 1;
	}
	else
	{
		len = 72;
		recv_len = 0;
		memset(cmd,0x00,sizeof cmd);
		recv_cmd(cmd,len,&recv_len);
		//debug_cmd(cmd,20);
		if(recv_len==0
		   ||(cmd[CMD_RET] != 0x00 && cmd[CMD_RET] != 0x5D))
		{
			confirm_msg(2,"�ɼ�ʧ��");
			return 1;
		}
		else
		{
			if(cmd[CMD_RET] == 0x5D)
			{
				do_update_col_date();
				confirm_msg(1,"POS����ˮ");
				return 2;
			}
			else if(cmd[CMD_RET] == 0x00)
			{
				// ������ˮ
				if(fwrite(cmd+CMD_RET+2,64,1,fp)==0)
				{
					confirm_msg(1,"д��ˮʧ��");
					return 1;
				}
				else
				{
					// confirm serial
					// get serial no
					cmd[0] = STX1;
					cmd[1] = 0x00;
					cmd[2] = 0x09;
					cmd[3] = 0x56;
					cmd[4] = 0x01;
					cmd[5] = 0x04;
					memcpy(cmd+80,cmd+CMD_RET+7,4);
					memcpy(cmd+6,cmd+80,4); // serial no
					cmd[10] = calc_sum(cmd+3,7);
					cmd[11] = ETX1;
					//confirm_msg(3,"ȷ����ˮ?");
					//debug_cmd(cmd,11);
					if(send_cmd(cmd,12)==0)
					{
						confirm_msg(1,"����ȷ��ʧ��");
						return 1;
					}
					else
					{
						len = 10;
						recv_len = 0;
						memset(cmd,0,sizeof cmd);
						if(recv_cmd(cmd,len,&recv_len)==0)
						{
							debug_cmd(cmd,recv_len);
							confirm_msg(1,"����ȷ��ʧ��");
							return 1;
						}
						if(recv_len ==0
						   || cmd[CMD_RET] != 0x00)
						{
							debug_cmd(cmd,recv_len);
							confirm_msg(1,"ȷ����ˮʧ��");
							return 1;
						}
						sprintf(msg,"�ɼ���[%d]���ɹ�",cnt);
						display_msg(2,msg);
						return 0;
					}
				}
			}
		}
	}
	return 1;
}
/** 
 * @brief �ɼ���ˮ
 */
static void do_collect_serial()
{
	FILE *fp;
	uint8 ret;
	uint16 cnt;
	char filename[512];
	char curr_time[15];
	get_curr_time(curr_time);
	curr_time[4] = 0;
	sprintf(filename,"record.dat");
	if((fp=fopen(filename,"a+b"))==NULL)
	{
		confirm_msg(1,"�򿪼�¼�ļ�ʧ�ܣ�");
		return;
	}
	fseek(fp,0L,SEEK_END);
	cnt = 0;
	while(1)
	{
		ret = do_collect_pos(fp,cnt);
		if(ret == 2)
		{
			//confirm_msg(1,"POS����ˮ�ɼ��ɹ�");
			break;
		}
		else if(ret==1)
		{
			sprintf(filename,"�ɼ��ж�,�ɹ�[%d]��",cnt-1);
			confirm_msg(1,filename);
			goto L_END;
		}
		else
		{
			cnt++;
			clrscr();
			continue;
		}
	}
	if(cnt>0)
	{
		sprintf(filename,"�ɼ��ɹ�[%d]����ˮ",cnt);
		confirm_msg(1,filename);
	}
L_END:
	// collect serial
	fclose(fp);
}
static void do_set_consume_param()
{
	FILE *fp;
	uint16 len,recv_len;
	uint8 cmd[48];
	if((fp = fopen("pay.dat","rb"))==NULL)
	{
		confirm_msg(1,"�򿪲����ļ�ʧ��");
		return;
	}
	cmd[0] = STX1;
	cmd[1] = 0;
	cmd[2] = 0x11;
	cmd[3] = 0xB2;
	cmd[4] = 0x01;
	cmd[5] = 0x0C;
	
	if(fread(cmd+6,32,1,fp)!=1)
	{
		confirm_msg(1,"��ȡ�����ļ�");
	}
	else //if(!check_buffer_crc(cmd+3,12,cmd+30))
	{
		len=12;
		cmd[6+len] = calc_sum(cmd+3,len+3);
		len++;
		cmd[6+len] = ETX1;
		len++;
		//debug_cmd(cmd,len+6);
		if(send_cmd(cmd,len+6)==0)
		{
			confirm_msg(1,"����ʧ��");
		}
		else
		{
			memset(cmd,0,sizeof cmd);
			if(recv_cmd(cmd,20,&recv_len)==0)
			{
				confirm_msg(1,"����ʧ��");
			}
			else if(cmd[CMD_RET] != 0x00)
			{
				confirm_msg(1,"���ش���");
			}
			else
			{
				confirm_msg(1,"���óɹ�");
			}
		}
	}
	fclose(fp);
}
static void do_set_cardright()
{
	uint8 cmd[512];
	uint16 len,recv_len;
	FILE *fp;
	if((fp=fopen("PURVIEW.DAT","rb"))==NULL)
	{
		confirm_msg(1,"���ļ�����");
		return;
	}
	cmd[0] = STX1;
	cmd[1] = 0x01;
	cmd[2] = 0x2C;
	cmd[3] = 0xB4;
	cmd[4] = 0x99;
	cmd[5] = 0x03;
	cmd[6] = 0x00;
	
	if(fread(cmd+7,294,1,fp)!=1)
	{
		confirm_msg(1,"��ȡʧ��");
		return;
	}
	else
	{	
		len=294;
		cmd[7+len] = calc_sum(cmd+3,len+4);
		len++;
		cmd[7+len] = ETX1;
		len++;
		if(send_cmd(cmd,len+7)==0)
		{
			confirm_msg(1,"����ʧ��");
		}
		else
		{
			memset(cmd,0,sizeof cmd);
			if(recv_cmd(cmd,20,&recv_len)==0)
			{
				confirm_msg(1,"����ʧ��");
			}
			else if(cmd[CMD_RET] != 0x00)
			{
				confirm_msg(1,"���ش���");
			}
			else
			{
				confirm_msg(1,"���óɹ�");
			}
		}

	}
	fclose(fp);
}
static void do_set_workkey()
{
	uint8 cmd[512];
    uint8 msg[64];
	uint16 len,recv_len;
	FILE *fp;
	if((fp=fopen("key.dat","rb"))==NULL)
	{
		confirm_msg(1,"���ļ�����");
		return;
	}
	cmd[0] = STX1;
	cmd[1] = 0x00;
	cmd[2] = 0x14;
	cmd[3] = 0xC3;
	cmd[4] = 0x01;
	cmd[5] = 0x00;
	cmd[6] = 0x0E;
	
	if(fread(cmd+7,14,1,fp)!=1)
	{
		confirm_msg(1,"��ȡʧ��");
		return;
	}
	else
	{	
		len=14;
		cmd[7+len] = calc_sum(cmd+3,len+4);
		len++;
		cmd[7+len] = ETX1;
		len++;
		//debug_cmd(cmd,len+7);
		if(send_cmd(cmd,len+7)==0)
		{
			confirm_msg(1,"����ʧ��");
		}
		else
		{
			memset(cmd,0,sizeof cmd);
			if(recv_cmd(cmd,20,&recv_len)==0)
			{
				confirm_msg(1,"����ʧ��");
			}
			else if(cmd[CMD_RET] != 0x00)
			{
                sprintf(msg,"���ش���[%X]",cmd[CMD_RET]);
				confirm_msg(1,msg);
			}
			else
			{
				confirm_msg(1,"���óɹ�");
			}
		}

	}
	fclose(fp);

}

//! ��ȡPOS ���ĺ������汾��
static int do_get_device_blkver(char *blkver)
{
    uint8 cmd[32];
    char msg[64]="";
    uint16 len,recv_len;

    cmd[0] = STX1;
	cmd[1] = 0x00;
	cmd[2] = 0x05;
	cmd[3] = 0xB5; // ��ȡ�������汾��
	cmd[4] = 0x99;
	cmd[5] = 0x00;
    cmd[6] = calc_sum(cmd+3,3);
    cmd[7] = ETX1;
    len = 8;
    if(send_cmd(cmd,len)==0)
    {
        confirm_msg(1,"��ȡ�汾�Ŵ���1");
    }
    else
    {
        memset(cmd,0,sizeof cmd);
        if(recv_cmd(cmd,20,&recv_len)==0)
        {
            //debug_cmd(cmd,16);
            confirm_msg(1,"��ȡ�汾�Ŵ���2");
        }
        else
        {
            if(cmd[CMD_RET] != 0x00)
            {
                confirm_msg(1,"��ȡ�汾��ʧ��");
            }
            else
            {
                if(cmd[6+6]==0xFF)
                    memcpy(blkver,cmd+6,6);
                else
                    memset(blkver,0x00,6);
                return 0;
            }
        }
    }
    
    return 1;
}
static long do_get_mid_addr(long start_addr,long end_addr,long mid_addr)
{
    long r;
    if(start_addr > end_addr)
        return -1;
    if(start_addr == end_addr)
        return -2;
    
    r = end_addr - start_addr;
    if(r > 10)
	{
        r = (r >> 1) + start_addr;
		if(r % 10 != 0)
		{
			r = (r / 10 * 10);
		}
		return r;
	}
    else
	{
		if(start_addr == mid_addr)
			return end_addr;
		else if(end_addr == mid_addr)
			return -2;
		else
			return start_addr;
	}
}

/*
 ����:
 0 - ��ʾ�ҵ���Ӧ�İ汾��
 1 - ��ʾ����İ汾�Ŵ����ļ������İ汾��
 2 - ��ʾ����İ汾��С���ļ�����С�İ汾��
*/
static int do_find_blklist(const uint8 *blkver,FILE *fp)
{
    long start_addr,end_addr,mid_addr,file_len;
    int ret;
    uint8 buffer[10];
    uint8 msg[16];
    //char msg[64];
    start_addr = 0;
    fseek(fp,0L,SEEK_END);
    file_len = ftell(fp);
    fseek(fp,0L,SEEK_SET);
    
    if(file_len % 10 != 0)
    {
        // ����10�ı���
        file_len = (file_len / 10) * 10;
    }
    //sprintf(msg,"len[%d]",file_len);
    end_addr = file_len - 10;
	mid_addr = -1;
    mid_addr = do_get_mid_addr(start_addr,end_addr,mid_addr);
    //sprintf(msg,"%d:%d:%d",start_addr,end_addr,mid_addr);
    while(mid_addr >= 0 )
    {
        fseek(fp,mid_addr,SEEK_SET);
        if(fread(buffer,10,1,fp)!=1)
        {
            return 1;
        }
        ret = memcmp(blkver,buffer+4,6);
        if(ret<0)
        {
            // 
            end_addr = mid_addr;
            mid_addr = do_get_mid_addr(start_addr,end_addr,mid_addr);
			if(mid_addr < 0) 
			{
				// û��
				return 2;
			}
        }
        else if(ret > 0)
        {
            start_addr = mid_addr;
            mid_addr = do_get_mid_addr(start_addr,end_addr,mid_addr);
			if(mid_addr < 0)
			{
				return 1;// ������
			}
			
        }
        else if(ret == 0)
        {
            // find 
			if(mid_addr == end_addr)
				return 1; // ������
            return 0;
        }
        //sprintf(msg,"find mid[%ld]",mid_addr);
        //confirm_msg(1,msg);
    }
    return 1;
}


static uint32 do_send_blklist(FILE *fp)
{
    uint8 max_per_send = 6;
    uint8 buffer[10],blkver[6];
    int ret,len,send_cnt,offset;
    uint16 recv_len;
    uint8 cmd[128],msg[32];
    uint32 total_cnt;

    total_cnt = 0;
    while(1)
    {
        cmd[0] = STX1;
        //cmd[1],cmd[2]
        cmd[3] = 0xB3;
        cmd[4] = 0x00;
        cmd[5] = 0; // ����
        send_cnt = 0;
        len = 6;
        offset = len + 7;
        while(!feof(fp) && send_cnt < max_per_send)
        {
            if(fread(buffer,10,1,fp)==1)
            {
                //
                send_cnt++;
                memcpy(cmd+offset,buffer,4);
                memcpy(cmd+len+1,buffer+4,6);
                offset+=4;
            }
            else
            {
                break;
            }
        }
        if(send_cnt == 0)
        {
            //confirm_msg(1,"�޺�����");
            return total_cnt;
        }
        else
        {
            //sprintf(msg,"len[%u]",offset);
            //confirm_msg(1,msg);
            
            cmd[5] = send_cnt;
            cmd[6] = send_cnt << 2 + 6;
            cmd[offset] = calc_sum(cmd+3,offset-3);
            offset++;
            cmd[offset++] = ETX1;
            cmd[1] = 0;
            cmd[2] = offset-3;
            
            //debug_cmd(cmd,offset);
            if(send_cmd(cmd,offset)==0)
            {
                confirm_msg(1,"���ͺ�����ʧ��");
                return total_cnt;
            }
            else
            {
                memset(cmd,0,sizeof cmd);
    			if(recv_cmd(cmd,16,&recv_len)==0)
    			{
    				confirm_msg(1,"����ʧ��");
                    return total_cnt;
    			}
    			else if(cmd[CMD_RET] != 0x00)
    			{
                    //debug_cmd(cmd,recv_len);
    				confirm_msg(1,"���ش���");
                    return total_cnt;
    			}
    			else
    			{
                    total_cnt += send_cnt;
    				if(send_cnt>=max_per_send || !feof(fp))
                        continue;
                    else
                        return total_cnt;
    			}
            }
        }
    }
    return total_cnt;
}

static void do_update_blklist()
{
    uint8 blkver[6],blkver_new[6];
    uint32 send_cnt;
    uint8 msg[32];
    FILE *fp;
    uint8 ret;

    ret = do_get_device_blkver(blkver);
    if(ret)
    {
        return;
    }
    fp = fopen("blklst.dat","rb");
    if(fp==NULL)
    {
        confirm_msg(1,"û�к���������");
        return;
    }
    //debug_cmd(blkver,6);
    memset(blkver_new,0x00,6);
    if(memcmp(blkver,blkver_new,6)==0)
    {
        //�Ӻ������ļ���һ����ʼ
        // ���غ�����
        do_send_blklist(fp);
    }
    else
    {
        // ���Һ�������ʼλ��
        ret = do_find_blklist(blkver,fp);
        //display_msg(1,"�������������");
        display_msg(1,"�����������Ժ�...");
        if(ret==0 || ret == 2)
        {
            // ���غ�����
            send_cnt = do_send_blklist(fp);
            sprintf(msg,"������[%lu]��",send_cnt);
            display_msg(2,msg);
            confirm_msg(1,"���غ��������");
        }
        else
        {
            // �Ѿ����µ����°汾
            confirm_msg(1,"���ػ��Ѿ������°汾");
        }
        
    }
    fclose(fp);
}

static void do_set_cardgroup()
{
    uint8 cmd[512];
	uint16 len,recv_len;
	FILE *fp;
	if((fp=fopen("cardgrp.dat","rb"))==NULL)
	{
		confirm_msg(1,"���ļ�����");
		return;
	}
	cmd[0] = STX1;
	cmd[1] = 0x01;
	cmd[2] = 0x2C;
	cmd[3] = 0xB9;
	cmd[4] = 0x99;
	cmd[5] = 0x00;
	cmd[6] = 0x00;
	
	if(fread(cmd+7,256,1,fp)!=1)
	{
		confirm_msg(1,"��ȡʧ��");
		return;
	}
	else
	{	
		len=256;
		cmd[7+len] = calc_sum(cmd+3,len+4);
		len++;
		cmd[7+len] = ETX1;
		len++;
		if(send_cmd(cmd,len+7)==0)
		{
			confirm_msg(1,"����ʧ��");
		}
		else
		{
			memset(cmd,0,sizeof cmd);
			if(recv_cmd(cmd,20,&recv_len)==0)
			{
				confirm_msg(1,"����ʧ��");
			}
			else if(cmd[CMD_RET] != 0x00)
			{
                debug_cmd(cmd,recv_len);
				confirm_msg(1,"���ش���");
			}
			else
			{
				confirm_msg(1,"���óɹ�");
			}
		}

	}
	fclose(fp);
}

static void do_main_menu()
{
	uint8 sel_menu;
	MENU_ITM menus[] = 
	{
		{"1.�ɼ���ˮ",'1'},
		{"2.�������Ѳ���",'3'},
		{"3.��Ȩ�޷���",'4'},
		{"4.У��ʱ��",'5'},
		{"5.������Կ",'6'},
		{"6.�汾",'7'},
		{"7.���º�����",'8'},
		{"8.��������",'9'},
		{"9.�˳�",255},
		{NULL,255},
	};
	do{
		sel_menu = menu(menus,"     ���˵� ",0,1,1);
		if(sel_menu == 255)
			return;
		clrscr();
		display_msg(1,"����������...");
		switch(sel_menu)
		{
		case '5':
			do_check_clock();
			break;
		case '1':
			do_collect_serial();
			break;
		case '3':
			do_set_consume_param();
			break;
		case '4':
			do_set_cardright();
			break;
		case '6':
			do_set_workkey();
			break;
		case '7':
			do_show_version();
			break;
        case '8':
            do_update_blklist();
            break;
        case '9':
            do_set_cardgroup();
            break;
        case 255:
		case KEY_ESC:
			return;
		default:
			break;
		}
		clrscr();
	}while(1);
	
}
int main()
{
	int16 ret;
	uint8 workmode,commmode;
	uint16 band;
	uint16 in_band;
	//directvideo=0;
	clrscr();
	// ��ʼͨѶ
	if(!ComPlsInstalled())
	{
		printf("Complus must be installed first!!!");
		exit(1);
	}
	/*
	if (InstallComPls(1) == 2) 
	{
		cprintf("BIOS Setting for COM1 or COM2 Error!!!!\r\n\n");
		return 0;
	}
	*/

	in_band = 19200;
	GetCommMode(&workmode,&commmode,&band);
	ret = SetCommMode(_AUX_MODE,1,in_band);
	//ret = SetCommMode(_PAK_MODE,1,in_band);
	if(ret)
	{
		printf("set comm mode ret[%d]",ret);
		exit(1);
	}
	EnableRx(0);
	IRPowerCtrl(_IrDAPowON);
	if (in_band == 57600) 
	{
		SetIRMFreq(921600);
	}
	if (in_band == 38400) 
	{
		SetIRMFreq(614400);
	}
	if (in_band == 19200) 
	{
		SetIRMFreq(307200);
	}
	if (in_band == 9600)
	{
		SetIRMFreq(153600);
	}
	SetIROutput(2);

	//do_main_process();
	do_main_menu();
	IRPowerCtrl(_IRPowOFF);
	SetIRMFreq(0);
	DisableRx();
	SetCommMode(workmode, commmode, band);  /* resume comm setting */
	return 0;
	
}


