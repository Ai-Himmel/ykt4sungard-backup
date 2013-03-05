#ifndef __CARD_H__
#define __CARD_H__

#include "serial.h"

/*
激活卡片，返回四字节卡号
*/
int  Rc_ActiveCard(CSerial *ser, int ActiveMode, unsigned char *CardId);

//循卡
int  Rc_anticoll( CSerial *ser, int ActiveMode, unsigned char *CardId);

/*
挂起卡片
*/
int  Rc_CloseCard( CSerial *ser );

/*
认证块密码
*/
int  Rc_ConfirmPwd( CSerial *ser, int BlockID, int PwdMode, unsigned char *CardId);

/*
下装密码
*/
int  Rc_LoadPwd( CSerial *ser, int PwdMode, int SectorID, unsigned char *Pwd);

/*
读块数据(16字节)
*/
int  Rc_ReadData( CSerial *ser, int BlockID, unsigned char *Data);

/*
写卡
*/
int  Rc_WriteData( CSerial *ser, int BlockID, unsigned char *Data);


#endif  __CARD_H__