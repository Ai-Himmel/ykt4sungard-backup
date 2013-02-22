#ifndef __YCT_LIBREADER__H
#define __YCT_LIBREADER__H 

#include "kscard_imp.h"
#include "kscard.h"

//工具
unsigned char * __stdcall APP_AscToBcd(unsigned char* ascbuf, int ascbuf_len, unsigned char* bcdbuf);
unsigned char * __stdcall APP_BcdToAsc(unsigned char* bcdbuf, int bcdbuf_len, unsigned char* ascbuf);
char* __stdcall APP_trim(char* str);

//金仕达读写器接口===================================================
		/*int  dc_init(int port,long baud);
		功 能：初始化通讯口
		参 数：port：取值为0～19时，表示串口1～20；为100时，表示USB口通讯，此时波特率无效。
		baud：为通讯波特率9600～115200
		返 回：成功则返回串口标识符>0，失败返回负值，见错误代码表
		例：int icdev;
		icdev=dc_init(0,9600);//初始化串口1，波特率9600*/
int __stdcall ks_open_device(int port,int band);

		/*int dc_exit(int icdev);
		功 能：关闭端口
		参 数：icdev：通讯设备标识符
		返 回：成功返回0
		例：dc_exit(icdev);*/
int __stdcall ks_close_device();

		/*int dc_beep(int icdev,unsigned int _Msec);
		功 能：蜂鸣
		参 数：icdev：通讯设备标识符
		unsigned int _Msec：蜂鸣时间，单位是10毫秒
		返 回：成功则返回 0
		例：int st;
		st=dc_beep(icdev,10);            鸣叫100毫秒*/
void __stdcall ks_beep();

		/*
		int dc_card(int icdev,unsigned char _Mode,unsigned long *_Snr);
		功 能：寻卡，能返回在工作区域内某张卡的序列号(该函数包含了dc_request,dc_anticoll,dc_select的整体功能)						
								参 数：icdev：通讯设备标识符						
								_Mode：寻卡模式mode_card						
								_Snr：返回的卡序列号						
								返 回：成功则返回 0						
								例：int st;
		*/
		//寻卡
//int __stdcall ks_card(unsigned long *_Snr);
		/*
		__int16 dc_pro_reset(HANDLE ICDev,unsigned char *rlen, unsigned char *rbuff)
		说明：卡上电复位函数,仅针对于TYPE A 卡
		调用：int ICDev ---- dc_init 函数返回的端口标识符
		unsigned char *rlen ---- 返回复位信息的长度
		unsigned char * rbuff ---- 存放返回的复位信息
		返回： <0 错误。其绝对值为错误号
		=0 成功。
		举例：st=dc_pro_reset(ICDev,rlen,DataBuffer)*/
		//卡复位
int __stdcall ks_dc_pro_reset(unsigned char *rlen, unsigned char *rbuff);
		/*
		__int16 dc_pro_command(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff,unsigned char tt)
		说明：应用协议数据单元信息交换函数。该函数已封装T=CL操作
		调用：int ICDev ----dc_init 函数返回的端口标识符
		unsigned char slen ---- 发送的信息长度
		unsigned char * sbuff ---- 存放要发送的信息
		unsigned char *rlen ---- 返回信息的长度
		unsigned char * rbuff ---- 存放返回的信息
		unsigned char tt---- 延迟时间，单位为：10ms
		*/
		//CPU卡直通指令
int __stdcall ks_cpuapdu( unsigned char *sSendData, unsigned char nSendDatalen, 
								   unsigned char* sRespData,unsigned char &nRespDatalen );

//SAM
int __stdcall ks_dc_pro_reset_SAM(unsigned char *rlen, unsigned char *rbuff);
int __stdcall ks_cpuapdu4sam( unsigned char *sSendData, unsigned char nSendDatalen, 
									   unsigned char* sRespData,unsigned char &nRespDatalen );

	

		/*函数功能：
			由一卡通系统人员输入16字节的根密钥，系统自动产生
			消费密钥分散因子1、消费密钥分散因子2、
			圈存密钥分散因子1、
			TAC密钥分散因子1、TAC密钥分散因子2、
			PIN解锁分散因子、
			重装PIN分散因子、
			维护密钥分散因子、
			应用主控密钥分散因子共9条分散因子。
			函数原型：int ks_KeyCard_Publish( char* sMasterKey, char* sPin )
			入口参数：
			char* sMasterKey  -16字节的根（主）密钥 （0~9 a~f A~F） 
			char* sPin          -6个数字字符的个人密码
			出口参数：
			无
			函数返回： 
			0 --成功，其它值-错误(PBOC错误码)
		 */
int __stdcall ks_KeyCard_Publish( char* sMasterKey, char* sPin );

		/*	函数功能：
			在认证PIN通过后，才可以根据相应序号获取相应的应用密钥，序号对应关系如下：
			1--消费密钥1
			2--消费密钥2
			3--圈存密钥
			4--TAC密钥1
			5--TAC密钥2
			6--PIN解锁密钥
			7--重装PIN密钥
			8--维护密钥
			9--主控密钥
			函数原型：int ks_Get_Key (int nKeySerial,char* sPin char* sKey)
			入口参数：
			int    nKeySerial  -密钥序号
			char* sPin          -6个数字字符的个人密码
			出口参数：
			char* sKey  	  -16字密钥
			函数返回： 
			0 --成功，其它值-错误(PBOC错误码)
			可以将密钥获取后存于数据库中（最好加密钥保存)
		*/
int __stdcall ks_getkey (int nKeySerial,char* sPin, char* sKey);


		/*
			用户卡洗卡
			函数原型：int ks_init_card_UserCard(ST_SCARD_MAIN_KEY sStrKey,
				char *sAppid,
				char  *sShowCard,
				int nWalletDetailCount)
			入口参数：
				char * sAppid	-卡片用户序列号 (20个字符)
				char*sShowCard	-显示卡号  (10个字符)
				int nWalletDetailCount -钱包明细最大值
			出口参数：
			无
			函数返回:
			0 --成功，其它值-错误(PBOC错误码)
		*/
int __stdcall ks_initusercard(ST_CARDMAINKEY StrKey,char *sAppid,char  *sShowCard,int nWalletDetailCount);

		/*
			用户发卡
			函数原型：int ks_Make_card_UserCard(ST_SPUBLISHUSERCARDINFO sCardInfo)
			入口参数：
				ST_SPUBLISHUSERCARDINFO sCardInfo		
			出口参数：
				无
			函数返回： 
			0 --成功，其它值-错误(PBOC错误码)
		*/
int __stdcall ks_makeuserCard(ST_PUBLISHUSERCARDINFO sCardInfo);

		/*
			1.4.1.2.	PSAM卡洗卡
			函数原型：int ks_init_card_PSAMCard(char *sAppid,
			char *  sTerminalNo)
			入口参数：
			char *  sAppid- PSAM序列号
			char *  sTerminalNo -终端机编号
			出口参数：
			无
			函数返回： 
			0 --成功，其它值-错误(PBOC错误码)
			待处理的问题：3条密钥(消费、维护、主控，通过结构体ST_SCARD_MAIN_KEY传入）
		*/
//int __stdcall ks_initcard4samcard(ST_CARDMAINKEY StrKey,char *sAppid, char* sTerminalNo);


		/*
		1.5.1.	设置卡操作控制码
 			函数原型：int ks_set_oper_mask(int mode,int mask)
 			入口参数：
		int 	mode - 读卡/写卡模式，0表示读卡，1表示写卡
		int  mask - 读/写操作对应卡属性索引，见卡属性索引表
 			出口参数：
			无
 			函数返回： 
		0 --成功，其它见错误码表*/
int __stdcall ks_set_oper_mask(int mode,int mask);

		/*1.5.2.	清除卡操作控制码
		函数原型：int ks_clear_oper_mask(int mode,int mask)
		入口参数：
		int 	mode - 读卡/写卡模式，0表示读卡，1表示写卡
		int  mask - 读/写操作对应卡属性索引，见卡属性索引表
		出口参数：
		无
		函数返回： 
		0 --成功，其它见错误码表*/

int __stdcall ks_clear_oper_mask(int mode,int mask);
		/*1.5.3.	清除所有卡操作控制码
		函数原型：int ks_clear_all_oper_mask(int mode)
		入口参数：
		int 	mode - 读卡/写卡模式，0表示读卡，1表示写卡
		出口参数：
		无
		函数返回： 
		0 --成功，其它见错误码表*/
int __stdcall ks_clear_all_oper_mask(int mode);

		/*1.5.5.	获取卡信息字段
			函数原型：int ks_get_card_data(int mask,char *data)
			入口参数：
			int mask - 读/写卡操作对应卡属性索引，见索引表	
			无
			出口参数：
			int data - 卡属性值
			函数返回： 
			0 --成功，其它见错误码表
		*/
int __stdcall ks_get_card_data(int mask,char *data);


		/*1.5.6.	设置写字段数据
		函数原型：int ks_set_card_data(int mask,const char *data)
		入口参数：
		int mask - 读/写卡操作对应卡属性索引，见索引表	
		int data - 卡属性值
		出口参数：
		无
		函数返回： 
		0 --成功，其它见错误码表*/
int __stdcall ks_set_card_data(int mask,const char *data);


		/*1.5.4.	读取卡信息
			函数原型：int ks_read_card()
			入口参数：
			无
			出口参数：
			无
			函数返回： 
			0 --成功，其它见错误码表*/
int __stdcall ks_read_card();


		/*1.5.7.	写卡信息
		函数原型：int ks_write_card ()
		入口参数：
		无
		出口参数：
		无
		函数返回： 
		0 --成功，其它见错误码表*/
int __stdcall ks_write_card ();

		/*1.5.8.	验证口令
		函数原型：int ks_verify_pin(char pin[7])
		入口参数：
		char pin[7]  -6个数字字符的个人PIN
		出口参数：
		无
		函数返回： 
		0 --成功，其它见错误码表
		*/
int __stdcall ks_verify_pin(char pin[7]);

		/*1.5.10.	应用锁定
		函数原型：int ks_lock_application()
		入口参数：
		无
		出口参数：
		无
		函数返回： 
		0 --成功，其它见错误码表*/
int __stdcall ks_lock_application();


	/*1.5.10.	消费
	函数原型：int ks_Purchase()
	入口参数：
			nMoney  消费金额
	出口参数：
	无
	函数返回： 
	0 --成功，其它见错误码表*/
//int  __stdcall ks_Purchase( const int nMoney );

	/*1.5.10.	充值
	函数原型：int ks_AddMoney()
	入口参数：
			nMoney  充值金额
	出口参数：
	无
	函数返回： 
	0 --成功，其它见错误码表*/
int  __stdcall ks_AddMoney( const int nMoney );



//由于当时金仕达读写器不稳定
//羊城通读卡器===================================
//打开串口
bool __stdcall APP_CPU_Open(char *sCom, int nBaudRate);
//关闭串口
void __stdcall APP_CPU_Close();
//上电
bool __stdcall APP_CPU_PowerOn();
//下电
bool __stdcall APP_CPU_PowerOff();
//寻卡
bool __stdcall APP_CPU_RequestCard();
//寻卡
bool __stdcall APP_CPU_SelectCard(char sType,char* sSerialNo);
//CPU卡直通指令
int __stdcall APP_CPU_APDU_Cmd( unsigned char *sSendData, unsigned char nSendDatalen, unsigned char* sRespData,unsigned char &nRespDatalen );

//下电
bool __stdcall APP_SAM_PowerOff();
//上电
bool __stdcall APP_SAM_PowerOn();
//SAM卡直通指令
int __stdcall APP_SAM_APDU_Cmd(int nSamSlot, unsigned char *sSendData, unsigned char nSendDatalen, unsigned char* sRespData,unsigned char &nRespDatalen );

//错误信息
char* __stdcall APP_CPU_GetErrorCode(char *sMsg);	
int __stdcall YCT_CalMAC_PSAMorAMT(byte *sCardNo,byte* sCmd,byte *sMac);							   
									   
#endif