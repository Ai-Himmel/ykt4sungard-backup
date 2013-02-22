#ifndef _FUNC_H
#define _FUNC_H

#define COM1	0
#define COM2	1
#define COM3	2
#define COM4	3

#define BAUDR_110	0
#define BAUDR_300	1
#define BAUDR_600	2
#define BAUDR_1200	3
#define BAUDR_2400	4
#define BAUDR_4800	5
#define BAUDR_9600	6
#define BAUDR_14400	7
#define BAUDR_19200	8
#define BAUDR_38400	9
#define BAUDR_56000	10
#define BAUDR_57600	11
#define BAUDR_115200	12

#define DBIT_4		0
#define DBIT_5		1
#define DBIT_6		2
#define DBIT_7		3
#define DBIT_8		4

#define PARIT_NONE	0
#define PARIT_EVEN	1
#define PARIT_ODD	2
#define PARIT_MARK	3
#define PARIT_SPACE	4

#define STOPBITS_ONE	0
#define STOPBITS_ONE5	1
#define STOPBITS_TWO	2

//Command define
/*	Mifare Command	*/
#define CMD_SelectCard			0x01
#define CMD_LoginToSector		0x02
#define CMD_ReadDataBlock		0x03
#define CMD_WriteDataBlock		0x04
#define CMD_ReadValueBlock		0x05
#define CMD_WriteValueBlock		0x06
#define CMD_WriteMasterKey		0x07
#define CMD_IncrementValue		0x08
#define CMD_DecrementValue		0x09
#define CMD_CopyValue			0x0A
#define CMD_Halt				0x0B
#define CMD_ContinuousRead	    0x0C

#define CMD_GetATS				0x1A
#define CMD_Deselect			0x1B
#define CMD_ExchangeAPDU		0x1C

//---------------------------------------------
/*RTC command*/
#define CMD_ReadTime			0x57		
#define CMD_SetDate				0x58		
#define CMD_SetTime				0x59		
#define CMD_InputPassword		0x5a		

/* LCD command */
#define CMD_LcdClear			0x93
#define CMD_LcdEnglish			0x94
#define CMD_LcdChinese			0x95
#define CMD_LcdLargeEnglish		0x92
#define	CMD_LcdBackLightCtr		0x90

/* Buzzer command */
#define CMD_BuzzerSound		0x9B

/*Set Display Model*/
#define CMD_SetDisModel			0x60

/* Sam1 card command */
#define CMD_Sam1PowerUp			0x31
#define CMD_Sam1PowerDown		0x33
#define CMD_Sam1ExchangeApdu	0x34

/* Sam2 card command */
#define CMD_Sam2PowerUp			0x41
#define CMD_Sam2PowerDown		0x43
#define CMD_Sam2ExchangeApdu	0x44

/* ICC card command */
#define CMD_IccPowerUp			0x21
#define CMD_IccPowerDown		0x24
#define CMD_IccExchangeApdu		0x23
//---------------------------------------------
//----------------------------------


#define CMD_Reset				0xFF
//----------------------------------------------------------------------------------------------

//Event define
#define EVENT_CHECKSUM_ERROR	0xFD //代表接收包校验和错
#define EVENT_UNKNOWN_ERROR		0xFE
//----------------------------------------------------------------------------------------------

//Status define
#define STATUS_OperationSuccess			0x00
#define STATUS_NoTag					0x01
#define STATUS_LoginSuccess				0x02
#define STATUS_LoginFail				0x03
#define STATUS_ReadFail					0x04
#define STATUS_WriteFail				0x05
#define STATUS_UnableReadAfterWrite		0x06
#define STATUS_ReadAfterWriteError		0x07
#define STATUS_ResetFail				0x08
#define STATUS_HaltFail					0x09
#define STATUS_CollisionOccur       	0x0A
#define STATUS_NoSAK                	0x0B
#define STATUS_LoadKeyFail              0x0C
#define STATUS_NotAuthenticate          0x0D
#define STATUS_NotAValueBlock           0x0E
#define STATUS_UnableToHalt             0x0F

#define STATUS_AccessDenied             0x10
#define STATUS_InvalidATS               0x11

#define STATUS_SectorOutOfRange         0x20
#define STATUS_InvalidKeyType           0x21
#define STATUS_BlockOutOfRange          0x22

#define STATUS_HourOut					0x2C
#define STATUS_MinOUt					0x2D
#define STATUS_SecOut					0x2E

#define STATUS_YearOut					0x30	
#define STATUS_MonthOut					0x31
#define STATUS_DayOut					0x32	

//IC卡操作返回状态定义
#define CardOk             0x00    //操作成功
#define CardPower          0x45    //卡片电源状态不正确
#define CardTimeout        0x49    //数据接收超时
#define CardParity         0x4a    //数据接收／发送奇偶错
#define CardLRC            0x4b    //LRC校验错误
#define CardNoTS           0x65    //没有返回TS
#define CardNonStandard    0x46    //非标准卡
#define CardTD1            0x48    //不支持TD1中定义的协议类型
#define CardTD2            0x48    //不支持TD2中定义的协议类型[WARN]
#define CardFIDI           0x48    //不支持TA1中定义的FIDI
#define CardIFSI           0x48    //不支持卡片IFSI
#define CardTB3            0x48    //不支持卡片TB3

#define CardLc             0x52    //命令头中Lc错误（Lc不应等于0）
#define CardNAD            0x4c    //NAD节点错误（T=1）
#define CardPCB            0x4d    //不支持卡片发送的PCB
#define CardLEN            0x4e    //分组块LEN域错误（LEN>32）
#define CardBreak          0x4f    //卡片中止操作（T=1）
#define CardCard           0x50    //卡片接受数据失败
#define CardSync           0x51    //同步失调
#define CardNotOut         0x45   //卡片没有被拔出
#define CardNotInsert      0x42   //卡片没有被插入
#define CardError          0x3f   //操作失败

#define STATUS_ChecksumError			0xF0
#define STATUS_InvalidCommand			0xF1
#define STATUS_CommunicationLineError   	0xF2
#define STATUS_InputPasswordTimeOut     	0xF3
#define STATUS_CommTimeOut			0xF4

#define STATE_DataLenOut			0xF5

#define LED_Red					0xFE
#define LED_Green				0xFD
#define LED_RedAndGreen				0xFC

//----------------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

/* basic function phototype */
BOOL WINAPI SetBaud(int BaudIdx);
BOOL WINAPI ConnectionUSBDevice( void );
BOOL WINAPI Connection(int PortIdx);
void WINAPI Disconnection( void );

//********************************************************************
//非接触卡功能函数
//-----------------
//set card type
BYTE WINAPI MIFARE_SetCardType(BYTE CardType);

//Select Mifare card
BYTE WINAPI MIFARE_SelectCard(BYTE *SerialNum);

//Login to a sector
BYTE WINAPI MIFARE_LoginSector(BYTE Sector,BYTE Type,BYTE *pKey);

//Read a data block
BYTE WINAPI MIFARE_ReadDataBlock(BYTE Block,BYTE *pData);

//Write a data block
BYTE WINAPI MIFARE_WriteDataBlock(BYTE Block,BYTE *pData);

//Read a value block
BYTE WINAPI MIFARE_ReadValueBlock(BYTE Block,BYTE *pValue);

//Write a value block
BYTE WINAPI MIFARE_WriteValueBlock(BYTE Block,BYTE *pValue);

//Increment value
BYTE WINAPI MIFARE_IncrementValue(BYTE Block,BYTE *pValue);

//Decrement value
BYTE WINAPI MIFARE_DecrementValue(BYTE Block,BYTE *pValue);

//Copy value
BYTE WINAPI MIFARE_CopyValue(BYTE Source,BYTE Destination);

//Reset
BYTE WINAPI MIFARE_Reset(void);

//Halt
BYTE WINAPI MIFARE_Halt(void);

//Get ATS
BYTE WINAPI MIFARE_GetATS(BYTE *pATS, BYTE &rLenATS);

//Deselect
BYTE WINAPI MIFARE_Deselect(void);

//Exchange APDU
BYTE WINAPI MIFARE_ExchangeAPDU(BYTE *sData,BYTE sLen,BYTE *rData,BYTE &rLen);
//********************************************************************
//IC 卡功能函数(包括SAM1,SAM2和主接触卡功能函数)
//--------------------------
/* Sam1 card command */  //SAM1卡功能函数
 BYTE WINAPI SetSam1BaudRate(BYTE baudrate);
 //---------------------------
 BYTE WINAPI Sam1PowerUp(BYTE *ATR,BYTE &len);
//----------------------------
 BYTE WINAPI Sam1PowerDown(void);
//----------------------------
 BYTE WINAPI Sam1ExchangeApdu(BYTE *sData,BYTE sLen,BYTE *rData,BYTE &rLen);
//-----------------------------

/* Sam2 card command */	//SAM2卡功能函数
 BYTE WINAPI SetSam2BaudRate(BYTE baudrate);
//---------------------------
 BYTE WINAPI Sam2PowerUp(BYTE *ATR,BYTE &len);
//----------------------------
 BYTE WINAPI Sam2PowerDown(void);
//----------------------------
 BYTE WINAPI Sam2ExchangeApdu(BYTE *sData,BYTE sLen,BYTE *rData,BYTE &rLen);
//-----------------------------

/* ICC card command */	//主卡座功能函数
 BYTE WINAPI SetICCBaudRate(BYTE baudrate);
//---------------------------
 BYTE WINAPI IccPowerUp(BYTE *ATR,BYTE &len);
//----------------------------
 BYTE WINAPI IccPowerDown(void);
//----------------------------
 BYTE WINAPI IccExchangeApdu(BYTE *sData,BYTE sLen,BYTE *rData,BYTE &rLen);
//-----------------------------
//********************************************************************
//其它功能函数
//----------------------
/* LCD command */
 BYTE WINAPI LcdClear(void);
//----------------------------
 BYTE WINAPI LcdEnglish(BYTE line, BYTE col, char *string);
//-----------------------------
 BYTE WINAPI LcdChinese(BYTE line, BYTE col, BYTE index);
//-----------------------------
 BYTE WINAPI LcdLargeEnglish(BYTE line, BYTE col, char *string);
//-----------------------------
 BYTE WINAPI LcdBackLightCtr(BYTE on_off);
 //on_off = 0;			LCD背光灭
 //on_off 不等于零:		LCD背光亮(上电默认状态)
//----------------------------
/*Set Display Model*/
 BYTE WINAPI SetDisModel(BYTE time_normal);
  //on_off = 0;			根据要求显示
 //on_off 不等于零:		进入实时时钟显示模式(LCD下面一行自动显示当前时间状态)(上电默认状态)
//----------------------------
/*RTC command*/
//Read timer and date
BYTE WINAPI ReadTime(BYTE *rTime);
 //返回数据为:年月日时分秒(时间和日期数据为BCD码表示:如60秒-->数据为0x60)
//----------------------------
//Set timer
BYTE WINAPI SetTime(BYTE Hour,BYTE Min,BYTE Sec);
//-----------------------------
//Set date
BYTE WINAPI SetDate(BYTE Year,BYTE Month,BYTE Day);
//-----------------------------
BYTE WINAPI BuzzerSound(BYTE stime);
//-------------------------------------------------------------------------------
//Pinpad Command	(密码键盘命令)//注:密码键盘10S内没有输入读卡器自动退出输入密码状态
BYTE WINAPI InputPassword(BYTE Prompt,BYTE *rPassword,BYTE &rLen);
//Prompt=0x80:红绿灯亮
//Prompt=0x81:红灯亮绿灯灭，语音："请再输入一次"
//Prompt=0x82:红灯灭绿灯亮，语音："请输入密码"
//Prompt=0x83:红绿灯灭
//--------------------------------------------------------------------------------
BYTE WINAPI MIFARE_Reset(void);
//
BYTE WINAPI PASCAL HYMIFARE_EnterISP(void);

BYTE WINAPI PASCAL ChangeBaudRate(BYTE baudrate);
BYTE WINAPI PASCAL SetDeviceID(BYTE *deviceid);
BYTE WINAPI PASCAL ReadDeviceID(BYTE *deviceid);

//--------------------------------------
//键盘命令
BYTE WINAPI PASCAL ReadKey(BYTE *rData,BYTE &rLen);
//*rData:按键值buffer
BYTE WINAPI EnableKeyboard(BOOL beep, BOOL dismodel);
//beep(0:按键无声,1:按键有声)
//dismodel(0:按键显示明文, 1:按键显示密文*)
BYTE WINAPI DisableKeyboard(void);

//--------------------------------------
//sle4428卡命令
//上电
BYTE WINAPI PASCAL ScardPowerUp(void);
//校验密码
BYTE WINAPI PASCAL SLE4428VerifyPSC(BYTE PSC1, BYTE PSC2);

//读主储存器
BYTE WINAPI PASCAL SLE4428ReadData(WORD addr,BYTE rlen, BYTE *rData);

//写主储存器
BYTE WINAPI PASCAL SLE4428WriteData(WORD addr,BYTE wlen,BYTE *wData);

//下电
 //BYTE WINAPI IccPowerDown(void);
 
 //--------------------------------------
//sle4442卡命令
//上电
//BYTE WINAPI PASCAL ScardPowerUp(void);
//校验密码
BYTE WINAPI PASCAL SLE4442VerifyPSC(BYTE *PSC);

//读主储存器
BYTE WINAPI PASCAL SLE4442ReadMainMemory(BYTE addr,BYTE rlen, BYTE *rData);

//写主储存器
BYTE WINAPI PASCAL SLE4442WriteMainMemory(BYTE addr,BYTE wlen,BYTE *wData);

//读保护储存器
BYTE WINAPI PASCAL SLE4442ReadProtectMemory(BYTE *rData);

//写保护储存器
BYTE WINAPI PASCAL SLE4442WriteProtectMemory(BYTE addr,BYTE wData);

//读密码储存器
BYTE WINAPI PASCAL SLE4442ReadSecurityMemory(BYTE *rData);

//写密码储存器
BYTE WINAPI PASCAL SLE4442WriteSecurityMemory(BYTE addr,BYTE wlen,BYTE *wData);

//下电

 //BYTE WINAPI IccPowerDown(void);
/*EFlash (at29c040 command)*/
BYTE WINAPI PASCAL EFlash_ReadData(DWORD address,BYTE data_len, BYTE *pData); 
BYTE WINAPI PASCAL EFlash_WriteData(DWORD address,BYTE data_len, BYTE *pData);

#ifdef __cplusplus
}
#endif

#endif
