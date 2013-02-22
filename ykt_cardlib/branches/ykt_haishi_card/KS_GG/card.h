#ifndef __CARD_H__
#define __CARD_H__

#include "serial.h"

/*
���Ƭ���������ֽڿ���
*/
int  Rc_ActiveCard(CSerial *ser, int ActiveMode, unsigned char *CardId);

//ѭ��
int  Rc_anticoll( CSerial *ser, int ActiveMode, unsigned char *CardId);

/*
����Ƭ
*/
int  Rc_CloseCard( CSerial *ser );

/*
��֤������
*/
int  Rc_ConfirmPwd( CSerial *ser, int BlockID, int PwdMode, unsigned char *CardId);

/*
��װ����
*/
int  Rc_LoadPwd( CSerial *ser, int PwdMode, int SectorID, unsigned char *Pwd);

/*
��������(16�ֽ�)
*/
int  Rc_ReadData( CSerial *ser, int BlockID, unsigned char *Data);

/*
д��
*/
int  Rc_WriteData( CSerial *ser, int BlockID, unsigned char *Data);


#endif  __CARD_H__