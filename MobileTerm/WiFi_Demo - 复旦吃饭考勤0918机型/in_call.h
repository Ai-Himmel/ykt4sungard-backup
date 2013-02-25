/****************************************************************************
*
*�ļ�(File):         in_call.h
*
*�޸�(Modify):       2011/7/20 14:05:06
*
*����(Author):       USER
*
*����(Compile):      ����ƽ̨(Smart Platform)
*
*����(Description):
*
*
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011/7/20 14:05:06           USER 
----------------------------------------------------------------------------
****************************************************************************/


#ifndef   in_call_h_2011_07_20_17_05_06_INCLUDED
#define   in_call_h_2011_07_20_17_05_06_INCLUDED
#include "api.h"
/*****wifi*******/
#include "WiFi/WiFi.h"
#include "WiFi/NaNoWiFiConst.h"
#include "WiFi/WiFiPubFuncs.h"
#include <unistd.h>
/***************/
typedef struct
{
	//unsigned char phyNo[8];	//������
	//unsigned char time[16];		//����ʱ��
	//unsigned char cum_money[8];	//���ѽ��
	//unsigned char cum_date[8];		//��������
	//unsigned char cum_time[6];		//����ʱ��
	unsigned char num[6];	//ѧ��
	unsigned char count[8];		//�Է�����
//	unsigned char cum_date[8];		//��������
//	unsigned char cum_time[6];		//����ʱ��
}USER_INFO;	//�û����ݽṹ
#define	NUM_OF_FUDAN	301

#define DATA_TABLE_NUM	1	//���ݿ������
#define ATTENDANCE_INDEX	0	//���ݿ�������ţ��������ݿ��

#define	MAX_SEND_BUFFER	1000	//WIFI����ÿ����෢�͵������ֽ���

#define	READ_CARD_SECOND	10	//��������
//EEPROM
#define EEPROM_OFFSET_SERVERIPADD	0	//EEPROM��Ҫ��ƫ��������ʼλ�ã�������IP������16�ֽڣ�
//#define EEPROM_OFFSET_WIFI_HANDLE	16	//����wifi���ӵľ������ʼλ�ã���2�ֽڣ�
#define EEPROM_OFFSET_MAIN_KEY		18	//��Ȩ��������Կ��ʼλ�ã���8�ֽڣ�
#define EEPROM_OFFSET_ADM_PSD		26	//����Ա������ʼλ�ã���9�ֽڣ�
#define EEPROM_OFFSET_ADM_CTRL		35	//����Ա�������λ����ʼ���룩��ʼλ�ã���1�ֽڣ�
#define EEPROM_OFFSET_SERVERPORT	36	//�������˿ں���ʼλ�ã���8�ֽڣ�
#define EEPROM_OFFSET_SERVERSSID	44	//������SSID��ʼλ�ã���16�ֽڣ�
#define EEPROM_OFFSET_SEVPASSWORD	60	//������������ʼλ�ã���16�ֽڣ�
//USBͨ��

/****************������***********************/
void main_task();		//���˵�
void debugFun(char* debugStr);	//debug����
void adminPsd_init();	//����Ա�����ʼ��
/****************���˵�����***********************/
void workAttendance_task();	//���ڴ�
void consumption_task();	//����
void funSet_task();			//�������ò˵�
void vstDatabase_task();	//���ݲ�ѯ�˵�
void dataUpload_task();		//���ݴ���˵�
void discernID_task();		//���ʶ��˵�
void setAdmPsd_task();		//���ù���Ա����
/****************���ݴ���˵�����*****************/
void usb_upload_menu();		//usb�����ϴ��˵�
void wifi_upload_menu();	//wifi�����ϴ��˵�
void wifiInit_open();		//������ʼ��WIFI
void db_to_str(unsigned char* buf, int bufMax, int cnt);	//���ݿ��¼ת�ַ���
/****************�������ò˵�����*****************/
int setTime();				//ʱ������
int setDate();				//��������
void Set_Auto_Poweroff();	//�Զ��ػ�ʱ������
void setBacklight();		//�����ʱ������
void setKeybeeper();		//����������
void getAuthorize();		//��ȡ��Ȩ��
char adminPassword();		//�������Ա����
int	input_password(char *pPrompt,char *dBuf);	//��������
/****************���ݲ�ѯ����*****************/
void db_check();			//������ݿ�
void db_init_menu();		//��ʼ�����ݿ⣨�˵����ã�
void del_Allrecords();		//ɾ�����м�¼
void check_recordsCnt();	//��ѯ�Ѿ���¼������
void check_dbCapcity();		//����������
/****************EEPROM��д*******************/
char eeprom_read(unsigned char* readBuffer, unsigned short sizeLen, int romOffset);	//eeprom��
char eeprom_write(unsigned char* writeBuffer, unsigned short sizeLen, int romOffset);	//eepromд
void shortTochar(unsigned short* sh, unsigned char* st);	//shortתchar����
void charToshort(unsigned short* sh, unsigned char* s);	//char����תshort
/****************m1����д*****************/
char readM1Card(char (*card_r)());	//��M1�����
char readAuthorizeCard();		//����Ȩ��
//char workAttendance_xian() ;		//���ڼ�¼(���ƴ�)
//char workAttendanceTemp();		//���ڼ�¼������������ʱ�棩
//char workAttendance_Dalian();		//���ڼ�¼���������£�
char discernID();			//���ʶ��
void CalKeyA(unsigned char* ucSerialNo,unsigned char* ucWorkKey,unsigned char* ucKeyA);	//����KEYA��Կ
void	warning_beep();				//������
int calkeyAfromPSAM(char* keya, const char* phyNo);		//PSAM��ȡkeya
void discernID_Fudan();		//����������ʶ�����
char discID_fudan();	//����������ʶ�����
/********cpu������***********/
int get_4byte_int(unsigned char *value_str);
void set_4byte_int(unsigned char *value_str,int num);
 void mydec2hex(const unsigned char *uDecBuf,int iDecLen,char *sHexStr);	//��ѹ
 void myhex2dec(const char *sHexStr,int iHexLen,unsigned char *uDecBuf,int* iDecBUfLen);	//ѹ��
#if 0
char consumpionNM();		//��ҽ����
int	input_money(int line,int maxNum,int minNum,int minValue,int maxValue, char *pPrompt,int *retValue, char* dBuf)	;	//���ѽ�������
int myatomon(char* str);		//�ַ���ת����
char cpucardCum_neiyi(int money, int* leftMoney);	//���ɹ�ҽ�ƴ�ѧ����
 char cpuCard_init(unsigned char* phn);		//cpu����ʼ��

 #endif
/*********************************************/
#endif   /*in_call_h_2011_07_20_17_05_06_INCLUDED*/
 
