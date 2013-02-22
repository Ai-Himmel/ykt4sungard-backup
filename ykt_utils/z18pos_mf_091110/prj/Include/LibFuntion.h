#ifndef _LIB_FUNTION_H
#define _LIB_FUNTION_H

#include "include/DataType.h"

//通过下载口调试函数 debug.lib
EXTERN	void	bp_SerialCtl(INT8U Num,INT32U iBand);
EXTERN	void	SerialCtl_1(INT8U Num,INT32U iBand);
EXTERN	INT8U	set_char(INT8U a);
EXTERN	INT8U	get_char(INT8U *mydata);
EXTERN	INT8U	set_char_1(INT8U a);
EXTERN	INT8U	get_char_1(INT8U *mydata);
EXTERN	void	DebugString(INT8U *string);
EXTERN	void	DebugHex(INT8U senddata);
EXTERN	void	DebugWord(INT16U asciiword);
EXTERN	void	DebugLong(INT32U asciilong);
EXTERN	void	DebugData(INT16U length,INT8U x,INT8U *buff);
EXTERN	void DebugPrint(unsigned char *fmt,...);

//显示库函数 display.lib
EXTERN void		DispInitialize(void);
EXTERN void		cls(void);
EXTERN void		Clear_line(INT8U line);
EXTERN void		Display(INT8U x,INT8U position,INT8U *ptr,INT8U mode);
EXTERN void		DisplayBcd(INT8U x,INT8U position,INT8U *ptr,INT8U length);
EXTERN void		DisplayStrSmall(INT8U x, INT8U y, char *lcd_string,INT8U mode);
EXTERN void		DisSmallBcd(INT8U x,INT8U y,INT8U *bcd,INT16U len);

//按键和语音函数	keypart.lib
EXTERN	INT8U	GetKeyVal(INT8U mode);
EXTERN	void	audio(INT8U Index,INT8U delaytime);

//FEROM存储器函数和E2PROM存储器函数 memory.lib
EXTERN	INT8U	FeSysRead(INT16U startadd,INT8U len,INT8U *buff);
EXTERN	INT8U	FeSysWrite(INT16U startadd, INT8U len,INT8U *buff);
EXTERN	INT8U	EeSysWrite(INT32U EeAddr,INT8U length,INT8U *Dat);
EXTERN	INT8U	EeSysRead(INT32U EeAddr,INT8U length,INT8U *Dat);

//TYPEA卡库   mifare.lib
EXTERN INT8U	loadconfig(void);
EXTERN INT8U	mif_request(INT8U mode);
EXTERN INT8U	mif_anticoll(INT8U mode,INT8U  *serial);
EXTERN INT8U	mif_select(INT8U mode,INT8U *serial,INT8U *SNK);
EXTERN INT8U	mif_loadkey(INT8U  *uncodekey);
EXTERN INT8U	mif_authen( INT8U keyab,INT8U sector,INT8U *serial);
EXTERN INT8U	mif_Read(INT8U block,INT8U *rdata);
EXTERN INT8U	mif_Write( INT8U block,INT8U *wdata );
EXTERN INT8U	mif_change(INT8U ad, INT8U block, INT8U *value);
EXTERN INT8U	mif_transfer(INT8U block);

//Psam 函数  psam.lib
EXTERN INT8U	IccPowOpen(INT8U ucPlusinID,INT32U baud,INT8U ucVoltage,INT8U *ATR);
EXTERN INT8U	IccIsoCommand(INT8U Slot,APDU_SEND *ApduSend,APDU_RESP *ApduRecv);

//时钟函数 RtcTime.lib
EXTERN void		InitRtcTime(void);
EXTERN INT8U	WriteRtcTime(INT8U *pTimer);
EXTERN INT8U	ReadRtcTime(INT8U *pTime);

//看门狗函数  bpPos.lib
EXTERN void		bp_Odog(void);   // enable watchdog
EXTERN void		bp_Cdog(void);   // disable watchdog
EXTERN void		clr_dog(void);   // reset watchdog timer

//辅助函数 other.lib
EXTERN	void	DESEncode(INT8U *src,INT8U *dec,INT8U *key,INT8U mode);
EXTERN	void	DESDecode(INT8U *src,INT8U *dec,INT8U *key,INT8U mode);
EXTERN	void	bp_beep(INT16U Times,INT8U delay);
EXTERN	INT8U	bp_TimerCheck(INT8U cTimerID);
EXTERN	void	bp_TimerSet(INT8U TimerID, INT16U Cnts);
EXTERN void		Led_OnOff(INT8U Index,INT8U mode);
EXTERN	void	Lcd_onoff(unsigned char mode);

//延时函数 bpPos.lib
EXTERN void		delay_50us(INT8U x);
EXTERN void		delay_1ms(INT8U	x);

//红外头函数
EXTERN	void	Init_Infrared_comm(INT32U	lBaud);

//GPRS函数
EXTERN	void	WNetInit(void);
EXTERN	INT8U	WNetCheckSim(void);
EXTERN	INT8U	WNetCheckSignal(void);
EXTERN	INT8U	WNetDial(INT8U	 *PARAM);
EXTERN	INT8U	WNetTCPConnect(INT8U *DIP, INT8U * DPORT);
EXTERN	INT8U	WNetTxd(INT8U *buff,INT16U len);
EXTERN	INT16U	WNetRxd(INT8U *buff,INT16U *len,INT16U MS);
EXTERN	void	WNetTCPClose(void);
EXTERN	void	WNetClose(void);
EXTERN	INT16U	GPRS_URMessage(char *dat);
EXTERN	INT8U	GPRS_SetupCSCA(char *Number);
EXTERN	INT8U	GPRS_UnReadCout(INT8U mode);
EXTERN	INT8U	GPRS_DelMessage(void);
#endif