#ifndef __YCT_LIBREADER__H
#define __YCT_LIBREADER__H 

#include "kscard_imp.h"
#include "kscard.h"

//����
unsigned char * __stdcall APP_AscToBcd(unsigned char* ascbuf, int ascbuf_len, unsigned char* bcdbuf);
unsigned char * __stdcall APP_BcdToAsc(unsigned char* bcdbuf, int bcdbuf_len, unsigned char* ascbuf);
char* __stdcall APP_trim(char* str);

//���˴��д���ӿ�===================================================
		/*int  dc_init(int port,long baud);
		�� �ܣ���ʼ��ͨѶ��
		�� ����port��ȡֵΪ0��19ʱ����ʾ����1��20��Ϊ100ʱ����ʾUSB��ͨѶ����ʱ��������Ч��
		baud��ΪͨѶ������9600��115200
		�� �أ��ɹ��򷵻ش��ڱ�ʶ��>0��ʧ�ܷ��ظ�ֵ������������
		����int icdev;
		icdev=dc_init(0,9600);//��ʼ������1��������9600*/
int __stdcall ks_open_device(int port,int band);

		/*int dc_exit(int icdev);
		�� �ܣ��رն˿�
		�� ����icdev��ͨѶ�豸��ʶ��
		�� �أ��ɹ�����0
		����dc_exit(icdev);*/
int __stdcall ks_close_device();

		/*int dc_beep(int icdev,unsigned int _Msec);
		�� �ܣ�����
		�� ����icdev��ͨѶ�豸��ʶ��
		unsigned int _Msec������ʱ�䣬��λ��10����
		�� �أ��ɹ��򷵻� 0
		����int st;
		st=dc_beep(icdev,10);            ����100����*/
void __stdcall ks_beep();

		/*
		int dc_card(int icdev,unsigned char _Mode,unsigned long *_Snr);
		�� �ܣ�Ѱ�����ܷ����ڹ���������ĳ�ſ������к�(�ú���������dc_request,dc_anticoll,dc_select�����幦��)						
								�� ����icdev��ͨѶ�豸��ʶ��						
								_Mode��Ѱ��ģʽmode_card						
								_Snr�����صĿ����к�						
								�� �أ��ɹ��򷵻� 0						
								����int st;
		*/
		//Ѱ��
//int __stdcall ks_card(unsigned long *_Snr);
		/*
		__int16 dc_pro_reset(HANDLE ICDev,unsigned char *rlen, unsigned char *rbuff)
		˵�������ϵ縴λ����,�������TYPE A ��
		���ã�int ICDev ---- dc_init �������صĶ˿ڱ�ʶ��
		unsigned char *rlen ---- ���ظ�λ��Ϣ�ĳ���
		unsigned char * rbuff ---- ��ŷ��صĸ�λ��Ϣ
		���أ� <0 ���������ֵΪ�����
		=0 �ɹ���
		������st=dc_pro_reset(ICDev,rlen,DataBuffer)*/
		//����λ
int __stdcall ks_dc_pro_reset(unsigned char *rlen, unsigned char *rbuff);
		/*
		__int16 dc_pro_command(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff,unsigned char tt)
		˵����Ӧ��Э�����ݵ�Ԫ��Ϣ�����������ú����ѷ�װT=CL����
		���ã�int ICDev ----dc_init �������صĶ˿ڱ�ʶ��
		unsigned char slen ---- ���͵���Ϣ����
		unsigned char * sbuff ---- ���Ҫ���͵���Ϣ
		unsigned char *rlen ---- ������Ϣ�ĳ���
		unsigned char * rbuff ---- ��ŷ��ص���Ϣ
		unsigned char tt---- �ӳ�ʱ�䣬��λΪ��10ms
		*/
		//CPU��ֱָͨ��
int __stdcall ks_cpuapdu( unsigned char *sSendData, unsigned char nSendDatalen, 
								   unsigned char* sRespData,unsigned char &nRespDatalen );

//SAM
int __stdcall ks_dc_pro_reset_SAM(unsigned char *rlen, unsigned char *rbuff);
int __stdcall ks_cpuapdu4sam( unsigned char *sSendData, unsigned char nSendDatalen, 
									   unsigned char* sRespData,unsigned char &nRespDatalen );

	

		/*�������ܣ�
			��һ��ͨϵͳ��Ա����16�ֽڵĸ���Կ��ϵͳ�Զ�����
			������Կ��ɢ����1��������Կ��ɢ����2��
			Ȧ����Կ��ɢ����1��
			TAC��Կ��ɢ����1��TAC��Կ��ɢ����2��
			PIN������ɢ���ӡ�
			��װPIN��ɢ���ӡ�
			ά����Կ��ɢ���ӡ�
			Ӧ��������Կ��ɢ���ӹ�9����ɢ���ӡ�
			����ԭ�ͣ�int ks_KeyCard_Publish( char* sMasterKey, char* sPin )
			��ڲ�����
			char* sMasterKey  -16�ֽڵĸ���������Կ ��0~9 a~f A~F�� 
			char* sPin          -6�������ַ��ĸ�������
			���ڲ�����
			��
			�������أ� 
			0 --�ɹ�������ֵ-����(PBOC������)
		 */
int __stdcall ks_KeyCard_Publish( char* sMasterKey, char* sPin );

		/*	�������ܣ�
			����֤PINͨ���󣬲ſ��Ը�����Ӧ��Ż�ȡ��Ӧ��Ӧ����Կ����Ŷ�Ӧ��ϵ���£�
			1--������Կ1
			2--������Կ2
			3--Ȧ����Կ
			4--TAC��Կ1
			5--TAC��Կ2
			6--PIN������Կ
			7--��װPIN��Կ
			8--ά����Կ
			9--������Կ
			����ԭ�ͣ�int ks_Get_Key (int nKeySerial,char* sPin char* sKey)
			��ڲ�����
			int    nKeySerial  -��Կ���
			char* sPin          -6�������ַ��ĸ�������
			���ڲ�����
			char* sKey  	  -16����Կ
			�������أ� 
			0 --�ɹ�������ֵ-����(PBOC������)
			���Խ���Կ��ȡ��������ݿ��У���ü���Կ����)
		*/
int __stdcall ks_getkey (int nKeySerial,char* sPin, char* sKey);


		/*
			�û���ϴ��
			����ԭ�ͣ�int ks_init_card_UserCard(ST_SCARD_MAIN_KEY sStrKey,
				char *sAppid,
				char  *sShowCard,
				int nWalletDetailCount)
			��ڲ�����
				char * sAppid	-��Ƭ�û����к� (20���ַ�)
				char*sShowCard	-��ʾ����  (10���ַ�)
				int nWalletDetailCount -Ǯ����ϸ���ֵ
			���ڲ�����
			��
			��������:
			0 --�ɹ�������ֵ-����(PBOC������)
		*/
int __stdcall ks_initusercard(ST_CARDMAINKEY StrKey,char *sAppid,char  *sShowCard,int nWalletDetailCount);

		/*
			�û�����
			����ԭ�ͣ�int ks_Make_card_UserCard(ST_SPUBLISHUSERCARDINFO sCardInfo)
			��ڲ�����
				ST_SPUBLISHUSERCARDINFO sCardInfo		
			���ڲ�����
				��
			�������أ� 
			0 --�ɹ�������ֵ-����(PBOC������)
		*/
int __stdcall ks_makeuserCard(ST_PUBLISHUSERCARDINFO sCardInfo);

		/*
			1.4.1.2.	PSAM��ϴ��
			����ԭ�ͣ�int ks_init_card_PSAMCard(char *sAppid,
			char *  sTerminalNo)
			��ڲ�����
			char *  sAppid- PSAM���к�
			char *  sTerminalNo -�ն˻����
			���ڲ�����
			��
			�������أ� 
			0 --�ɹ�������ֵ-����(PBOC������)
			����������⣺3����Կ(���ѡ�ά�������أ�ͨ���ṹ��ST_SCARD_MAIN_KEY���룩
		*/
//int __stdcall ks_initcard4samcard(ST_CARDMAINKEY StrKey,char *sAppid, char* sTerminalNo);


		/*
		1.5.1.	���ÿ�����������
 			����ԭ�ͣ�int ks_set_oper_mask(int mode,int mask)
 			��ڲ�����
		int 	mode - ����/д��ģʽ��0��ʾ������1��ʾд��
		int  mask - ��/д������Ӧ��������������������������
 			���ڲ�����
			��
 			�������أ� 
		0 --�ɹ����������������*/
int __stdcall ks_set_oper_mask(int mode,int mask);

		/*1.5.2.	���������������
		����ԭ�ͣ�int ks_clear_oper_mask(int mode,int mask)
		��ڲ�����
		int 	mode - ����/д��ģʽ��0��ʾ������1��ʾд��
		int  mask - ��/д������Ӧ��������������������������
		���ڲ�����
		��
		�������أ� 
		0 --�ɹ����������������*/

int __stdcall ks_clear_oper_mask(int mode,int mask);
		/*1.5.3.	������п�����������
		����ԭ�ͣ�int ks_clear_all_oper_mask(int mode)
		��ڲ�����
		int 	mode - ����/д��ģʽ��0��ʾ������1��ʾд��
		���ڲ�����
		��
		�������أ� 
		0 --�ɹ����������������*/
int __stdcall ks_clear_all_oper_mask(int mode);

		/*1.5.5.	��ȡ����Ϣ�ֶ�
			����ԭ�ͣ�int ks_get_card_data(int mask,char *data)
			��ڲ�����
			int mask - ��/д��������Ӧ��������������������	
			��
			���ڲ�����
			int data - ������ֵ
			�������أ� 
			0 --�ɹ����������������
		*/
int __stdcall ks_get_card_data(int mask,char *data);


		/*1.5.6.	����д�ֶ�����
		����ԭ�ͣ�int ks_set_card_data(int mask,const char *data)
		��ڲ�����
		int mask - ��/д��������Ӧ��������������������	
		int data - ������ֵ
		���ڲ�����
		��
		�������أ� 
		0 --�ɹ����������������*/
int __stdcall ks_set_card_data(int mask,const char *data);


		/*1.5.4.	��ȡ����Ϣ
			����ԭ�ͣ�int ks_read_card()
			��ڲ�����
			��
			���ڲ�����
			��
			�������أ� 
			0 --�ɹ����������������*/
int __stdcall ks_read_card();


		/*1.5.7.	д����Ϣ
		����ԭ�ͣ�int ks_write_card ()
		��ڲ�����
		��
		���ڲ�����
		��
		�������أ� 
		0 --�ɹ����������������*/
int __stdcall ks_write_card ();

		/*1.5.8.	��֤����
		����ԭ�ͣ�int ks_verify_pin(char pin[7])
		��ڲ�����
		char pin[7]  -6�������ַ��ĸ���PIN
		���ڲ�����
		��
		�������أ� 
		0 --�ɹ����������������
		*/
int __stdcall ks_verify_pin(char pin[7]);

		/*1.5.10.	Ӧ������
		����ԭ�ͣ�int ks_lock_application()
		��ڲ�����
		��
		���ڲ�����
		��
		�������أ� 
		0 --�ɹ����������������*/
int __stdcall ks_lock_application();


	/*1.5.10.	����
	����ԭ�ͣ�int ks_Purchase()
	��ڲ�����
			nMoney  ���ѽ��
	���ڲ�����
	��
	�������أ� 
	0 --�ɹ����������������*/
//int  __stdcall ks_Purchase( const int nMoney );

	/*1.5.10.	��ֵ
	����ԭ�ͣ�int ks_AddMoney()
	��ڲ�����
			nMoney  ��ֵ���
	���ڲ�����
	��
	�������أ� 
	0 --�ɹ����������������*/
int  __stdcall ks_AddMoney( const int nMoney );



//���ڵ�ʱ���˴��д�����ȶ�
//���ͨ������===================================
//�򿪴���
bool __stdcall APP_CPU_Open(char *sCom, int nBaudRate);
//�رմ���
void __stdcall APP_CPU_Close();
//�ϵ�
bool __stdcall APP_CPU_PowerOn();
//�µ�
bool __stdcall APP_CPU_PowerOff();
//Ѱ��
bool __stdcall APP_CPU_RequestCard();
//Ѱ��
bool __stdcall APP_CPU_SelectCard(char sType,char* sSerialNo);
//CPU��ֱָͨ��
int __stdcall APP_CPU_APDU_Cmd( unsigned char *sSendData, unsigned char nSendDatalen, unsigned char* sRespData,unsigned char &nRespDatalen );

//�µ�
bool __stdcall APP_SAM_PowerOff();
//�ϵ�
bool __stdcall APP_SAM_PowerOn();
//SAM��ֱָͨ��
int __stdcall APP_SAM_APDU_Cmd(int nSamSlot, unsigned char *sSendData, unsigned char nSendDatalen, unsigned char* sRespData,unsigned char &nRespDatalen );

//������Ϣ
char* __stdcall APP_CPU_GetErrorCode(char *sMsg);	
int __stdcall YCT_CalMAC_PSAMorAMT(byte *sCardNo,byte* sCmd,byte *sMac);							   
									   
#endif