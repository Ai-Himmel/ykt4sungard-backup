/* By S.K Spe.21,1995 */
#ifndef sysdial_h
	#define sysdial_h

#include "\src\atlanta\define\sysmax.h"

/************************************************************************
 * 電話番号																*
 * struct SYS_CommandData SYS_CommandFile[SYS_COM_FILE_MAX]				*
 * syscomf.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
/* 一括送信用 */
struct SYS_BatchTxDialData_t {
	UBYTE Item;			/* ダイヤル種別 */
/*#if (PRO_PIN_ACCESS == ENABLE)*/
	UBYTE PIN_Number[SYS_PIN_MAX]; /** PIN番号登録ＢＣＤコードで８桁まで。 By S.K Sep.21,1995 ANZU */
/*#endif*/
	union {
		UBYTE Direct[SYS_DIRECT_DIAL_MAX];
						/* 直接ﾀﾞｲﾔﾙ番号 */
						/* BCDで記憶 */
						/* 最終桁に続くの1バイトには､0FFHをセット */
						/* 0H～09H : ダイヤル数字0～9に対応 */
						/* 0AH	   : * */
						/* 0BH	   : # */
						/* 0CH	   : / */	/* '-'->'/' By H.Y 1994/06/24 */
						/* 0DH	   : - */	/* '/'->'-' By H.Y 1994/06/24 */
						/* 0EH	   : ! */
						/* 0FH	   : エンドマーク */
		UBYTE Onetouch;	/* ワンタッチ番号　*/
						/* SYS_OnetuchDial[]の配列のオフセット値 */
		UWORD Speed;	/* 短縮番号 */
						/* SYS_SpeedDial[]の配列のオフセット値 */
		UWORD Group;	/* グループ番号 */
						/* スカラー値 */
						/* 0を選択すると1～32の全てのグループ番号を指定 */
		UBYTE FxSpeed[SYS_FXSPEED_DIAL_MAX];
						/* 短縮番号をワイルドカードを使用しての複数指定 */
						/* FXBCDで記憶 */
						/* 0H～09H : ダイヤル数字0～9に対応 */
						/* 0AH	   : #(グループ指定) */
						/* 0BH	   : *(ワイルドカード指定) */
						/* 0CH～0FH: 未使用 */
						/* 例)｢00H,1AH｣の場合｢短縮10～19｣を指定 */
	}FaxNumber;
};


/* 一括送信以外 */
struct SYS_DialData_t {
/*#if (PRO_PIN_ACCESS == ENABLE)*/
	UBYTE PIN_Number[SYS_COM_DIRECT_DIAL_MAX][SYS_PIN_MAX]; /** PIN番号登録ＢＣＤコードで８桁まで。 By S.K Sep.21,1995 ANZU */
/*#endif*/
	UBYTE Direct[SYS_COM_DIRECT_DIAL_MAX][SYS_DIRECT_DIAL_MAX];
	UBYTE Onetouch[SYS_ONETOUCH_BIT_FIELD_MAX];
	UBYTE Speed[SYS_SPEED_BIT_FIELD_MAX];
	UDWORD Group;
};

/************************************************************************
 * 電話番号																*
 * struct SYS_ExecQueueData SYS_ExecQueue[SYS_EXEC_QUEUE_MAX]			*
 * sysexec.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
struct	SYS_ExecDialData_t {
	UBYTE Item;			/* ダイヤル種別 */
	union			{
		UBYTE Command;	/* 通信予約番号 */
						/* SYS_CommandFile[].DialNumber[]の配列オフセット値	*/
		UBYTE Onetouch;	/* ワンタッチ番号 */
		UWORD Speed;	/* 短縮番号 */
	}ExecNumber;
};

/************************************************************************
 * 電話番号のダイヤル種別												*
 * struct SYS_DialData.Item												*
 * struct SYS_ExecDialData.Item											*
 * syscomf.jsw参照														*
 * sysexec.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_EMPTY_DIAL		0	/* 未使用 */
#define SYS_DIRECT_DIAL		1	/* 直接ダイヤル */
#define SYS_ONETOUCH_DIAL	2	/* ワンタッチダイヤル */
#define SYS_SPEED_DIAL		3	/* 短縮ダイヤル */
#define SYS_GROUP_DIAL		4	/* グループダイヤル */
#define SYS_FXSPEED_DIAL	5	/* 短縮一括ダイヤル(FX仕様) */

/***********************************************************************
*		   BY:	 S.Kawasaki
*		 DATE:	 Wed 8 Apr 1992
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 struct	DialingData	SYS_DialingNumber
* DESCRIPTION:	 多機能電話用バッファデータ
************************************************************************/
struct	DialingData_t {
	UBYTE Buffer[DIALING_NUMBER_MAX];
	UBYTE ReadPointer;
	UBYTE WritePointer;
};

#if 0 /* 通信のみで使うので削除する */
/***********************************************************************
*		   BY:	 t.yamaguchi
*		 DATE:	 Fri 22 Dec
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 struct	PinDialingData	SYS_DialingPinNumber
* DESCRIPTION:	 PIN番号用バッファデータ
************************************************************************/
struct PinDialingData_t {
	UBYTE PinBuffer[PIN_DIALING_NUMBER_MAX];
	UBYTE ReadPointer;
	UBYTE WritePointer;
};
#endif

#endif
