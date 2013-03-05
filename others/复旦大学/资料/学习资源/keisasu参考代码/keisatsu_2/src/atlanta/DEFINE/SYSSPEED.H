/*	By Y.Suzuki 1996/10/15	*/
/* Original File : jun\usr2:\src\ichou\define\sysspeed.h */
/* 機種によっては、必要？ ↓ */
/*	unsigned char NamePronunciation[SYS_NAME_PRONUNCIATION_MAX];	@* カタカナ半角 */
#ifndef sysspeed_h
	#define sysspeed_h

#include "\src\atlanta\define\sysmax.h"	/* Add by NOBUKO  Jul.04,94 */

/************************************************************************
 * 標準短縮ダイヤル														*
 * struct SYS_SpeedDialData_t SYB_SpeedDial[SYS_SPEED_DIAL_MAX]			*
 * sysspeed.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_SpeedDialData_t {
	UBYTE Dial[SYS_TEL_2DIGIT_MAX];
									/* 電話番号 */
									/* BCDで記憶 */
									/* 最終桁に続くの1バイトは0FFH */
									/* 0H～09H : ダイヤル数字0～9に対応 */
									/* 0AH     : * */
									/* 0BH     : # */
									/* 0CH     : - */
									/* 0DH     : / */
									/* 0EH     : ! */
									/* 0FH     : エンドマーク */
	UBYTE Name[SYS_DIAL_NAME_MAX];	/* 相手先名(NULL含む) */

	UBYTE NamePronunciation[SYS_NAME_PRONUNCIATION_MAX];	/* カタカナ半角 */

/*#if (PRO_PIN_ACCESS == ENABLE)*/
	UBYTE PIN_Number[SYS_PIN_MAX];	/** PIN番号登録ＢＣＤコードで８桁まで。 By S.K Sep.21,1995 ANZU */
/*#endif*/

#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
	UBYTE Keisatsu;					/* 警察仕様属性の明示(ビットアサイン) */
#else
/*#if (PRO_SUB_DIAL == ENABLE)*/
	UBYTE SubDialPosition;			/* 転送先 */
									/* SYB_SubDial[]の配列オフセット値 */
/*#endif*/
#endif

/*#if (PRO_COST == ENABLE)*/
	UBYTE CostPosition;				/* 料金テーブル */
									/* SYB_CostTable[]の配列オフセット値 */
/*#endif*/
	UDWORD Group;					/* グループ番号 */
									/* 1ビットが1グルーフ゜に対応 */
									/* LSB:グループ1、MSB:グループ32 */
	UBYTE Attribute1;				/* 属性1 */
									/* SYS_MemorySwitch[10]と同じ */
	UBYTE Attribute2;				/* 属性2 */
									/* SYS_MemorySwitch[11]と同じ */
									/* 警察FAXではAttribute2中の送出レベルが0の場合はその値を参照せず、*/
									/* メモリSWに設定してある送出レベルを使用する */
	UBYTE Attribute3;				/* 属性3 */
									/* SYS_MemorySwitch[12]と同じ */
/* ↓●ICHOU追加 by T.Soneoka 1996/05/17 */
	UBYTE Attribute4;				/* SYS_MemorySwitch[13]と同じ */
};

/*******************************************************************************
	警察仕様属性のビットアサイン
												2005/04/14 石橋正和
*******************************************************************************/
#if defined (KEISATSU)

#define SYS_KEISATSU_KEIDEN			0x01	/* 警電 */
#define SYS_KEISATSU_KANYU			0x02	/* 加入 */

#define SYS_KEISATSU_ISSEI			0x04	/* 一斉 */
#define SYS_KEISATSU_KOBETSU		0x08	/* 個別 */

#define SYS_KEISATSU_SCRAMBLE_ON	0x10	/* スクランブルON */
#define SYS_KEISATSU_SCRAMBLE_OFF	0x20	/* スクランブルOFF */

#define SYS_KEISATSU_KYOTSU			0x40	/* スクランブル共通 */
#define SYS_KEISATSU_SENYO			0x80	/* スクランブル専用 */

#endif

#endif
