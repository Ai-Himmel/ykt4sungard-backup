/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_DEF.H
*	Author		: 渡辺一章
*	Date		: 1996/10/17
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: オペレーション固定値定義
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef OPR_DEF_H
	#define OPR_DEF_H	1

#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\define\time.h"
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#include	"\src\atlanta\define\sys_infd.h"
#endif


#define	RIGHT_ARROW					0x7E	/* 右矢印（→） */

/*-------------------------*
 * ＬＣＤドライバー関係
 *-------------------------*/
/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)	*/	/* ＨＩＮＯＫＩ タイプ *//* 1998/09/21 by T.Soneoka */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ＨＩＮＯＫＩ タイプ *//* 1998/09/21 by T.Soneoka */

	#define	DDRAM_FIRST_ROW_ADDRESS		0x80	/* DDRAM１行目アドレス(10000000) */
	#define	DDRAM_SECOND_ROW_ADDRESS	0xc0	/* DDRAM２行目アドレス(10100000) */

	/*--------------------*/
	/* インストラクション */
	/*--------------------*/
	#define	LCD_CLEAR_DISPLAY			0x01	/* DDRAMに0x20をwrite	*/
	#define	LCD_ENTRY_MODE				0x06	/* カーソル移動方向右/アドレスインクリメント/表示シフトしない */
	#define	LCD_DISPLAY_ON				0x0C	/* 表示ON/カーソルOFF	*/
	#define	LCD_DISPLAY_OFF				0x08	/* 表示OFF/カーソルOFF	*/
	#define	LCD_CURSOR_ON				0x0E	/* 表示ON/カーソルOFF	*/
	#define	LCD_CURSOR_OFF				0x0c	/* 表示ON/カーソルOFF	*/
	#define	LCD_FUNCTION_SET			0x38	/* データ長8ビット/２行	*/
	#define	LCD_CGRAM_ADDRESS			0x40	/* CGRAMアドレス 0000000 */

	/* Busy待ち時間：BUSYが立たないときの念のためのタイムアウト時間 */
	/* インストラクション実行時間が2.1msecのもの：10msec待つ */
	#define	LCD_BUSY_WAIT_TIME10MSEC	4500
	/* インストラクション実行時間が50usecのもの：700usec待つ */
	#define	LCD_BUSY_WAIT_TIME200USEC	100

	/* ＣＧＲＡＭテーブル　１文字あたりのバイト数	*/
	#define	LCD_SPECIAL_CHARACTER_MAX 	8
	/* ＣＧＲＡＭテーブル　定義データ数	*/
	#define	LCD_CGRAM_TABLE_MAX			8
	#define	LCD_CGRAM_WRITE_DATA_COUNT	LCD_SPECIAL_CHARACTER_MAX * LCD_CGRAM_TABLE_MAX

	/*--------------------------------*
	 * ＬＣＤ関係
	 *--------------------------------*/
	#define	LCD_LOWER_ADD	20		/* ＬＣＤ下段表示加算値	*/
	#define	WORDING_LEN		21		/* ワーディングサイズ	*/

	/*----------------------------------------------*
	 * LCD&LED シリアル書き込み位置制御 LcdScanPos
	 *----------------------------------------------*/
	#define LCD_HIGH_INST_POS		0
	#define LCD_HIGH_START_POS		1

	#define LCD_WR_MAX				44
	#define LCD_HIGH_END_POS		21
	#define LCD_LOW_INST_POS		21
	#define LCD_LOW_START_POS		22
	#define LCD_LOW_END_POS			42
	#define LED1_WRITE_POS			42
	#define LED2_WRITE_POS			43

	/* FROM_ONETOUCH_SHEET_CHECK -> APL_MSG.H */
	#define	MSG_ONETOUCH_SHEET_CHANGE	0
#else
 #if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/15 */
/************************************************************************
*          BY:	石橋正和
*        DATE:	Thu 21 Oct 1993
*        TYPE:	DEFINE
* VAR TO HOLD:	unsigned char LCD_Data
* DESCRIPTION:	LCTCの双方向データバス
************************************************************************/
#define LCD_ADRS_WRPORT		0x0040		/* I/Oアドレス(このアドレスでRSがLowになり、*/
										/* アドレスレジスタが選択される)			*/
										/* (RSはA0に接続されているため)				*/
#define LCD_DATA_WRPORT		0x0041		/* I/Oアドレス(このアドレスでRSがHighになり、*/
										/* データレジスタが選択される)				*/

/************************************************************************
*          BY:	石橋正和
*        DATE:	Mon 1 Nov 1993
*        TYPE:	DEFINE
* VAR TO HOLD:	
* DESCRIPTION:	LCDの大きさ
************************************************************************/
#define LCD_WIDTH				(unsigned char)30	/* 幅(半角)             */
#define LCD_HEIGHT				(unsigned char)4	/* 高さ                 */
#define LCD_TOTAL_CHARACTERS	(unsigned char)120	/* 全文字数(半角)       */
#define LCD_DOT_LINE			(unsigned char)16	/* 1行当たりのドットライン数 */

/************************************************************************
*          BY:	石橋正和
*        DATE:	Mon 2 Nov 1993
*        TYPE:	DEFINE
* VAR TO HOLD:	->DotPattern[]の上位8ビット
* DESCRIPTION:	文字のアトリビュート
************************************************************************/
#define ATTRIBUTE_NORMAL		0x00FF	/* 通常 */
#define ATTRIBUTE_REVERSE		0x08FF	/* 反転 */
#define ATTRIBUTE_BLINK 		0x20FF	/* 点滅 */

/************************************************************************
*          BY:	石橋正和
*        DATE:	Thu 21 Oct 1993
* DESCRIPTION:	LCDの表示データのための構造体
************************************************************************/
struct LCD_DisplayData_t {
	UWORD DotPattern[LCD_HEIGHT][LCD_DOT_LINE][LCD_WIDTH];  /* アトリビュート+ドットパターン */
	UWORD String[LCD_TOTAL_CHARACTERS]; /* 表示している全文字 */
		/* Stringは、本来ならunsigned charが適当なのだが、フレームバッファがワードアクセスしか */
		/* できないためUWORDとしてある (1画面4080byte = 0FF0Hbyte使用)                  */
};

/************************************************************************
*          BY:	清水政貴
*        DATE:	Thu 07 Mar 1996
* DESCRIPTION:	LCTC(M66270FP)のためのデータ定義
************************************************************************/
#define LCTC_VRAM_1PAGE_SIZE	(LCD_HEIGHT*LCD_DOT_LINE*LCD_WIDTH)	/* ＶＲＡＭ１ページ分のバイト数 */

#define LCD_SHOW		0xd  				/* ＬＣＤの表示，非表示 */
#define LCD_HIDE		9

#define LCTC_REG1		0x00C10000 /* 0x40 */			/* モードレジスタ */
#define LCTC_REG2		0x00C10002 /* 0x42 */			/* 水平表示文字数 */
#define LCTC_REG3		0x00C10004 /* 0x44 */			/* 水平同期パルス幅 */
#define LCTC_REG4		0x00C10006 /* 0x46 */			/* サイクルスチールイネーブル幅 */
#define LCTC_REG5		0x00C10008 /* 0x48 */			/* 垂直ライン数 */
#define LCTC_REG6		0x00C1000A /* 0x4a */			/* 表示スタートアドレス（下位）*/
#define LCTC_REG7		0x00C1000C /* 0x4c */			/* 表示スタートアドレス（上位）*/
#define LCTC_REG8		0x00C1000E /* 0x4e */			/* Ｍ出力周期可変レジスタ */

									/* 仮想フレームバッファからキャラクタを取得する */
#define LCD_GET_FRAMEBUFFER_CHAR(off) (unsigned char)(*((UWORD *)LCD_VirtualFrameBuffer + (off)))

/************************************************************************
*          BY:	清水政貴
*        DATE:	1996/06/10
* DESCRIPTION:	絵文字表示のための定義
************************************************************************/
#define LCD_PICFONT_TOTAL	4				/* 使用する文字数 */

#define LCD_PICFONT			0xF0			/* 下位４ビットで合計１６個の絵文字を定義可能 */
#define LCD_PICFONT_LOWER	0xFF			/* 絵文字表示のためのキャラクタコード
											** １ワードで表現し、２バイト目には 0xFF を格納
											*/

#define	OPR_PIC_FONT_0				0xF0	/* ピクチャーフォントテーブルの０番目の文字		*/
#define	OPR_PIC_FONT_1				0xF1	/* ピクチャーフォントテーブルの１番目の文字		*/
#define	OPR_PIC_FONT_2				0xF2	/* ピクチャーフォントテーブルの２番目の文字		*/
#define	OPR_PIC_FONT_3				0xF3	/* ピクチャーフォントテーブルの３番目の文字		*/
#define	OPR_PIC_FONT_4				0xF4	/* ピクチャーフォントテーブルの４番目の文字		*/
#define	OPR_PIC_FONT_5				0xF5	/* ピクチャーフォントテーブルの５番目の文字		*/
#define	OPR_PIC_FONT_6				0xF6	/* ピクチャーフォントテーブルの６番目の文字		*/
#define	OPR_PIC_FONT_7				0xF7	/* ピクチャーフォントテーブルの７番目の文字		*/
#define	OPR_PIC_FONT_8				0xF8	/* ピクチャーフォントテーブルの８番目の文字		*/
#define	OPR_PIC_FONT_9				0xF9	/* ピクチャーフォントテーブルの９番目の文字		*/
#define	OPR_PIC_FONT_10				0xFA	/* ピクチャーフォントテーブルの１０番目の文字	*/
#define	OPR_PIC_FONT_11				0xFB	/* ピクチャーフォントテーブルの１１番目の文字	*/
#define	OPR_PIC_FONT_12				0xFC	/* ピクチャーフォントテーブルの１２番目の文字	*/
#define	OPR_PIC_FONT_13				0xFD	/* ピクチャーフォントテーブルの１３番目の文字	*/
#define	OPR_PIC_FONT_14				0xFE	/* ピクチャーフォントテーブルの１４番目の文字	*/
#define	OPR_PIC_FONT_15				0xFF	/* ピクチャーフォントテーブルの１５番目の文字	*/

 #else	/* (PRO_ANK_TO_KANJI == DISABLE) */
	#define	DDRAM_FIRST_ROW_ADDRESS		0x80	/* DDRAM１行目アドレス    */ /* 10000000 */
	#define	DDRAM_SECOND_ROW_ADDRESS	0xc0	/* DDRAM２行目アドレス	  */ /* 10100000 */

	/* インストラクション */
	#define	LCD_CLEAR_DISPLAY			0x01	/* DDRAMに0x20をwrite	*/
	#define	LCD_ENTRY_MODE				0x06	/* カーソル移動方向右/アドレスインクリメント/表示シフトしない */
	#define	LCD_DISPLAY_ON				0x0C	/* 表示ON/カーソルOFF	*/
	#define	LCD_DISPLAY_OFF				0x08	/* 表示OFF/カーソルOFF	*/
	#define	LCD_CURSOR_ON				0x0E	/* 表示ON/カーソルOFF	*/
	#define	LCD_CURSOR_OFF				0x0c	/* 表示ON/カーソルOFF	*/
	#define	LCD_FUNCTION_SET			0x38	/* データ長8ビット/２行	*/
	#define	LCD_CGRAM_ADDRESS			0x40	/* CGRAMアドレス 0000000	*/

	/* Busy待ち時間：BUSYが立たないときの念のためのタイムアウト時間 */
	#if (0)
	/*#define	LCD_BUSY_WAIT_TIME10MSEC	300		/* インストラクション実行時間が2.1msecのもの：10msec待つ */
	/*#define	LCD_BUSY_WAIT_TIME200USEC	17		/* インストラクション実行時間が50usecのもの：700usec待つ */
	#endif
	#define	LCD_BUSY_WAIT_TIME10MSEC	4500	/* インストラクション実行時間が2.1msecのもの：10msec待つ */
	#define	LCD_BUSY_WAIT_TIME200USEC	100		/* インストラクション実行時間が50usecのもの：700usec待つ */

	#define	LCD_SPECIAL_CHARACTER_MAX 	8		/* ＣＧＲＡＭテーブル　１文字あたりのバイト数	*/
	#define	LCD_CGRAM_TABLE_MAX			8		/* ＣＧＲＡＭテーブル　定義データ数				*/
	#define	LCD_CGRAM_WRITE_DATA_COUNT	LCD_SPECIAL_CHARACTER_MAX * LCD_CGRAM_TABLE_MAX
 #endif	/* (PRO_ANK_TO_KANJI == ENABLE)	*/
#endif

/*--------------------------------*
 * ＬＣＤ関係
 *--------------------------------*/
#define	OPR_LCD_LOWER_ADD		20	/* LCD下段表示加算値				*/
#define	OPR_WORDING_LEN			21	/* ワーディングサイズ				*/
#define	OPR_KANJI_CODE_LEN		6	/* 漢字コードの長さ（かっこを含む）	*/

/* 注）OPR_PAPER_SIZE_Rは、ワーディングで直接define値を定義しているので値を変更しないこと				*/
#define	OPR_PAPER_SIZE_R			0x01	/* 紙サイズのＲを表すグラフィック							*/
#define	OPR_ONETOUCH_MARK			0x02	/* ダイアル中のワンタッチＵ１～Ｕ２のＵを表す（アンズ用）	*/
#define	OPR_ONETOUCH_MARK_LEFT		0x03	/* ダイヤル中のワンタッチの左かっこ（ポプラ用）				*/
#define	OPR_ONETOUCH_MARK_RIGHT		0x04	/* ダイヤル中のワンタッチの右かっこ（ポプラ用）				*/
#define	OPR_SPEED_MARK				0x05	/* ダイヤル中の短縮記号										*/
#define	OPR_GROUP_MARK				0x06	/* ダイヤル中のグループ記号									*/
#define	OPR_PROGRAM_MARK			0x07	/* ダイアル中のプログラムワンタッチ記号（アンズ用）			*/
#define	OPR_PROGRAM_MARK_LEFT		0x08	/* ダイヤル中のプログラムワンタッチの左かっこ（ポプラ用）	*/
#define	OPR_PROGRAM_MARK_RIGHT		0x09	/* ダイヤル中のプログラムワンタッチの右かっこ（ポプラ用）	*/
#define	OPR_PIN_MARK				0x0A	/* ダイアル中のダイアル番号とＰＩＮ番号の区切りの"*"を表す	*/
#define	OPR_KANJI_CODE_MARK_LEFT	0x0B	/* 発信元名入力中の漢字コードを表す左かっこ					*/
#define	OPR_KANJI_CODE_MARK_RIGHT	0x0C	/* 発信元名入力中の漢字コードを表す右かっこ					*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#define DIRECT_ADDRESS_MARK			0x0D	/* ダイレクトアドレス入力モード記号のコード					*/
#endif

/* ＣＧＲＡＭアクセス用のコードの定義を追加 by K.Watanabe 1998/10/26 */
#define	OPR_CG_FONT_0				0x10	/* ＣＧＲＡＭテーブルの０番目の文字							*/
#define	OPR_CG_FONT_1				0x11	/* ＣＧＲＡＭテーブルの１番目の文字							*/
#define	OPR_CG_FONT_2				0x12	/* ＣＧＲＡＭテーブルの２番目の文字							*/
#define	OPR_CG_FONT_3				0x13	/* ＣＧＲＡＭテーブルの３番目の文字							*/
#define	OPR_CG_FONT_4				0x14	/* ＣＧＲＡＭテーブルの４番目の文字							*/
#define	OPR_CG_FONT_5				0x15	/* ＣＧＲＡＭテーブルの５番目の文字							*/
#define	OPR_CG_FONT_6				0x16	/* ＣＧＲＡＭテーブルの６番目の文字							*/
#define	OPR_CG_FONT_7				0x17	/* ＣＧＲＡＭテーブルの７番目の文字							*/

/* カレンダー表示での漢字表示用のコードの定義を追加 by K.Watanabe 1998/10/27
** 注）HINOKIだけは、カレンダー表示用の漢字をフォントの中に持っているので、ＣＧＲＡＭを使いません
*/

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if 0 /* defined (HINOKI2) */	/* LCDドライバ変更対応。以下の文字をCGRAMから持ってくるよう変更 2002/04/27 T.Takagi */
//#define	OPR_FONT_DAY				OPR_CG_FONT_0	/* 日												*/
//#define	OPR_FONT_MONTH				OPR_CG_FONT_1	/* 月												*/
//#define	OPR_FONT_YEAR				OPR_CG_FONT_7	/* 年												*/
 #else
  #if defined(SATSUKI2) || defined(STOCKHM2)		/* LCDドライバ変更対応。以下の文字をCGRAMから持ってくるよう変更 by Y.Kano 2003/08/18 */
#define	OPR_FONT_DAY				OPR_CG_FONT_0	/* 日												*/
#define	OPR_FONT_MONTH				OPR_CG_FONT_1	/* 月												*/
#define	OPR_FONT_YEAR				OPR_CG_FONT_7	/* 年												*/
  #elif defined(HINOKI3)	/* LCDドライバ変更対応 by K.Watanabe 2004/10/14 */
#define	OPR_FONT_DAY				0x97			/* 日												*/
#define	OPR_FONT_MONTH				0x91			/* 月												*/
#define	OPR_FONT_YEAR				0x90			/* 年												*/
  #else		/* HINOKI */
#define	OPR_FONT_DAY				0xF0			/* 日												*/
#define	OPR_FONT_MONTH				0xF1			/* 月												*/
#define	OPR_FONT_YEAR				0xF7			/* 年												*/
  #endif	/* End of defined(SATSUKI2) */
 #endif
#else
#define	OPR_FONT_DAY				OPR_CG_FONT_0	/* 日												*/
#define	OPR_FONT_MONTH				OPR_CG_FONT_1	/* 月												*/
#define	OPR_FONT_YEAR				OPR_CG_FONT_7	/* 年												*/
#endif

#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/22 */
#define	OPR_FONT_LINE				OPR_PIC_FONT_0	/* 画面区切り線										*/
#define	OPR_FONT_DEN_LEFT			OPR_PIC_FONT_2	/* 濃度：左端										*/
#define	OPR_FONT_DEN_TEN			OPR_PIC_FONT_3	/* 濃度：薄く・やや薄く・やや濃く・濃くの位置		*/
#define	OPR_FONT_DEN_NOR			OPR_PIC_FONT_4	/* 濃度：普通										*/
#define	OPR_FONT_DEN_RIGHT			OPR_PIC_FONT_5	/* 濃度：右端										*/
#define	OPR_FONT_DEN_SET			OPR_PIC_FONT_6	/* 濃度：設定値										*/
#define	OPR_FONT_VOLUME_MIN			OPR_PIC_FONT_7	/* ボリューム：小									*/
#define	OPR_FONT_VOLUME_MID			OPR_PIC_FONT_8	/* ボリューム：中									*/
#define	OPR_FONT_VOLUME_MAX			OPR_PIC_FONT_9	/* ボリューム：大									*/

#define	OPR_LCD_LINE1_LEFT			0x01			/* ディスプレイ１行目　左側部分(20byte)使用中		*/
#define	OPR_LCD_LINE1_RIGHT			0x02			/* ディスプレイ１行目　右側部分(10byte)使用中		*/
#define	OPR_LCD_LINE1				0x03			/* ディスプレイ１行目　全部　　(30byte)使用中		*/
#define	OPR_LCD_LINE2_LEFT			0x04			/* ディスプレイ２行目　左側部分(20byte)使用中		*/
#define	OPR_LCD_LINE2_RIGHT			0x08			/* ディスプレイ２行目　右側部分(10byte)使用中		*/
#define	OPR_LCD_LINE2				0x0C			/* ディスプレイ２行目　全部　　(30byte)使用中		*/
#define	OPR_LCD_LINE3_LEFT			0x10			/* ディスプレイ３行目　左側部分(20byte)使用中		*/
#define	OPR_LCD_LINE3_RIGHT			0x20			/* ディスプレイ３行目　右側部分(10byte)使用中		*/
#define	OPR_LCD_LINE3				0x30			/* ディスプレイ３行目　全部　　(30byte)使用中		*/
#define	OPR_LCD_LINE4_LEFT			0x40			/* ディスプレイ４行目　左側部分(20byte)使用中		*/
#define	OPR_LCD_LINE4_RIGHT			0x80			/* ディスプレイ４行目　右側部分(10byte)使用中		*/
#define	OPR_LCD_LINE4				0xC0			/* ディスプレイ４行目　全部　　(30byte)使用中		*/
#endif

/*--------------------------*
 * メッセージ
 *--------------------------*/
/* FROM_10MS_TIMER */
#define	MSG_GET_KEY_TIMEUP		0	/* キー待ちタイマー　タイムアップ					*/
#define	MSG_CHILD_TIMEUP		1	/* チャイルド表示タイマー　タイムアップ				*/
#define	MSG_PARAM_DISP_TIMEUP	2	/* コピーパラメータ優先表示タイマー　タイムアップ	*/

/* FROM_ONETOUCH_SHEET_CHECK -> APL_MSG.H*/
#define	MSG_ONETOUCH_SHEET_CHANGE	0

#define	OPR_YES		1
#define	OPR_NO		0

/*-------------------------*
 * 最大値
 *-------------------------*/
#define	OPR_INP_NUM_ONETOUCH_MAX		5 * SYS_ONETOUCH_MAX		/* 全ワンタッチ指定分の領域		5([01],) * 最大ﾜﾝﾀｯﾁ数(72)	*/
#define	OPR_INP_NUM_SPEED_MAX			5 * SYS_SPEED_DIAL_MAX		/* 全短縮指定分の領域			5(S001,) * 最大短縮数(128)	*/
#define	OPR_INP_NUM_GROUP_MAX			4 * SYS_GROUP_NUMBER_MAX	/* 全グループ指定分の領域		4(G01,)  * 最大ｸﾞﾙｰﾌﾟ数(32)	*/
#if (PRO_PIN_ACCESS == ENABLE)
/* 全直接ダイヤル（ＰＩＮ番号含む）指定分の領域		(40 + 1(PIN記号) + 8 + 1(同報記号)) * 最大直接ﾀﾞｲﾔﾙ数(20) */
#define	OPR_INP_NUM_DIRECT_MAX			(((SYS_DIRECT_DIAL_MAX -  1) * 2) + 1 + (SYS_PIN_MAX * 2) + 1) * SYS_COM_DIRECT_DIAL_MAX
#else
/* 全直接ダイヤル指定分の領域						(40 + 1(同報記号)) * 最大直接ﾀﾞｲﾔﾙ数(20) */
#define	OPR_INP_NUM_DIRECT_MAX			(((SYS_DIRECT_DIAL_MAX -  1) * 2) + 1) * SYS_COM_DIRECT_DIAL_MAX
#endif

/* PIN番号が含まれていなかったので追加（合わせて種別ごとに定義を分割しました） by K.Watanabe 1998/05/12 */
#if (0)
///* すべての同報数分確保（1947ﾊﾞｲﾄ）		72(最大ﾜﾝﾀｯﾁ数)*5([01],) + 128(最大短縮数)*5(S001,) + 32(最大ｸﾞﾙｰﾌﾟ数)*4(G01,) + 20(直接ﾀﾞｲﾔﾙ数)*41 - 1(最後の相手先には同報マーク未使用) */
///*#define	OPR_INPUT_NUMBER_BUFFER_MAX	(SYS_COM_DIAL_MAX * ((SYS_DIRECT_DIAL_MAX - 1) * 2 + 1))	/ ﾌﾟﾛｸﾞﾗﾑ入力ﾊﾞｯﾌｧ最大数 10宛先×(40桁(ﾀﾞｲﾚｸﾄﾀﾞｲｱﾙ)＋1(ｺﾝﾏ)) = 410 */
//#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
//#define	OPR_INPUT_NUMBER_BUFFER_MAX		(SYS_ONETOUCH_MAX * 5) + (SYS_SPEED_DIAL_MAX * 5) + (SYS_GROUP_NUMBER_MAX * 4) + (SYS_COM_DIRECT_DIAL_MAX * ((SYS_DIRECT_DIAL_MAX * 2) - 1)) - 1 + (SYS_ONETOUCH_MAX * 5) + (SYS_INF_MAIL_DIRECT_COUNT_MAX * (SYS_INF_MAIL_ADDRESS_MAX - 1 + 2))
//#else
///* PIN番号が含まれていなかったので追加（合わせて種別ごとに定義を分割しました） */
//#define	OPR_INPUT_NUMBER_BUFFER_MAX		(SYS_ONETOUCH_MAX * 5) + (SYS_SPEED_DIAL_MAX * 5) + (SYS_GROUP_NUMBER_MAX * 4) + (SYS_COM_DIRECT_DIAL_MAX * ((SYS_DIRECT_DIAL_MAX * 2) - 1)) - 1
//#endif
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
#define	OPR_INPUT_NUMBER_BUFFER_MAX		OPR_INP_NUM_ONETOUCH_MAX + OPR_INP_NUM_SPEED_MAX + OPR_INP_NUM_GROUP_MAX + OPR_INP_NUM_DIRECT_MAX - 1 + OPR_INP_NUM_ONETOUCH_MAX + (SYS_INF_MAIL_DIRECT_COUNT_MAX * (SYS_INF_MAIL_ADDRESS_MAX - 1 + 2))
#else
#define	OPR_INPUT_NUMBER_BUFFER_MAX		OPR_INP_NUM_ONETOUCH_MAX + OPR_INP_NUM_SPEED_MAX + OPR_INP_NUM_GROUP_MAX + OPR_INP_NUM_DIRECT_MAX - 1
#endif

#define	OPR_DIRECT_DIAL_BUFFER_MAX		((SYS_DIRECT_DIAL_MAX - 1) * 2) + 1	/* 直接ダイヤルバッファの最大値 */
/* ワンタッチ・短縮のグループ設定で全グループ設定可能により変更（95ﾊﾞｲﾄ）　32(最大ｸﾞﾙｰﾌﾟ数) * 3(01,) - 1(最後の相手先には同報マーク未使用) */
/*#define	OPR_CHARACTER_INPUT_MAX			OPR_KANJI_CODE_LEN * ((SYS_TTI_MAX - 1) / 2)	/* 文字入力用ﾊﾞｯﾌｧ最大値（66ﾊﾞｲﾄ:漢字ｺｰﾄﾞで11文字） */
/* 暗号化送信（キーのヒント）追加により変更（103ﾊﾞｲﾄ必要）　ｷｰのﾋﾝﾄの最大入力数(35ﾊﾞｲﾄ)内で漢字ｺｰﾄﾞが17文字入力可能(17文字 x 6ﾊﾞｲﾄ + 1ﾊﾞｲﾄ) */
/*#define	OPR_CHARACTER_INPUT_MAX			(SYS_GROUP_NUMBER_MAX * 3) - 1	/* 文字入力用バッファ最大値	*/
#define	OPR_CHARACTER_INPUT_MAX			150		/* 文字入力用バッファ最大値						*/
#define	OPR_CHECK_BUFFER_MAX			OPR_CHARACTER_INPUT_MAX + 1		/* 文字入力データチェック用のバッファの最大値	*/
#define	OPR_DISPLAY_MAX					20		/* LCD最大表示文字数							*/
#define	OPR_TELBOOK_SIDE_MAX			38		/* 電話帳検索用テーブルの横方向の最大値			*/

#define	DB_FILE_DIGIT_MAX				4		/* 検索ポーリング受信ファイル番号の最大桁数		*/
#define	DATABASE_NUMBER_MAX				9999	/* 検索ポーリング受信のファイル番号の最大値		*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/10/08 */
#define	SPEED_FIGURE_MAX				2		/* 短縮番号の最大桁数							*/
#else
#define	SPEED_FIGURE_MAX				3		/* 短縮番号の最大桁数							*/
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* #define OP_SPEED_FIGURE_MAX				4	*/	/* 任意短縮番号表示桁数 2002/02/12 By M.Maeda	*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/10/08 */
#define OP_SPEED_FIGURE_MAX				2		/* 2桁にしておきます。2002/10/18 T.Takagi */
#else
#define OP_SPEED_FIGURE_MAX				3		/* 3桁にしておきます。2002/10/18 T.Takagi */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#define	GROUP_FIGURE_MAX				2		/* グループ番号の最大桁数						*/
#define	GROUP_DIAL_MAX					10		/* １つのワンタッチ・短縮に登録できるグループ数	*/
#define	COM_DIGIT_MAX					2		/* 未定。現在は１桁 -> 2桁						*/
#define	OPR_FCODE_BOX_FIGURE_MAX		2		/* ＦコードＢＯＸ番号の最大桁数					*/
#define	OPR_KEY_BOOK_FIGURE_MAX			1		/* 暗号化キーブック番号の最大桁数				*/

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* 1996/06/28 H,Yagi *//* by K.Watanabe 2004/10/12 */
#define	MERCURY_DIGIT_MAX				2		/* マキュリーアクセス番号の桁数					*/
#endif

#define	OPR_ROMAJI_KANA_TABLE_MAX		270		/* ローマ字カナ変換用テーブルサイズ				*/

#define OPR_OPTIONAL_SPEED_MAX			999		/* 任意短縮範囲									*/

#define JUNK_CODE_MIN					4		/* ジャンクメール登録番号最小桁					*/
#define JUNK_CODE_MAX					8		/* ジャンクメール登録番号最大桁					*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
/**************************************
** ユーザデータ登録時のテンプバッファ
** OPR_INF_UserData.TempUserData[]のMAX値
** ユーザデータファイルのメンバの中で
** 配列の要素最大値
**************************************/
#define OPR_USER_DATA_TEMP_MAX	SYS_INF_MAIL_ADDRESS_MAX
/***********************************************
** ユーザ名かPOP LoginIDをセットする変数のMAX値
** (OPR_Buf.ReviewCtrl.UserNameOrID[])
** コマンド確認時LCDに表示する
** ユーザデータファイルのユーザ名とPOP LoginIDの
** どちらか大きい方を指定
***********************************************/
#define OPR_USER_NAME_OR_ID_MAX	(SYS_INF_POP_ID_MAX-1)
/****************************************
** メール送信コマンド確認時の宛先バッファ
** OPR_Buf.ReviewCtrl.InputBuffer[]
****************************************/
#define OPR_INPUT_BUFFER_MAX OPR_DISPLAY_MAX
/**********************************
** ユーザコード番号の最大・最小桁数
**********************************/
#define OPR_USER_CODE_MIN				4
#define OPR_USER_CODE_MAX				SYS_INF_USER_CODE_MAX
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
#define	ND_FIGURE_MAX					2		/* ナンバーディスプレイ登録番号の最大桁数		*/
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
#define	WARP_FIGURE_MAX					1		/* ＦＡＸワープ登録番号の最大桁数				*/
#endif

/*-----------------------------*
 * 番号入力用入力種別
 *-----------------------------*/
/* NumberInput()用 */
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
#define	OPR_NUMBER_INPUT_NO_INITIAL		0	/* 初期値をセットしない											*/
#endif
#define	OPR_COMMAND_NUMBER_INPUT		1	/* 通信予約ファイル番号入力（予約原稿プリント）					*/
#define	OPR_TX_MAIL_BOX_NUMBER_INPUT	2	/* 親展ボックス番号入力（親展送信）								*/
#define	OPR_MAIL_BOX_NUMBER_INPUT		3	/* 親展ボックス番号入力（親展ボックス登録・親展受信プリント）	*/
#define	OPR_STORE_POLLING_NUMBER_INPUT	4	/* ポーリング　ファイル番号入力（ポーリング原稿蓄積）			*/
#define	OPR_POLLING_FILE_NUMBER_INPUT	5	/* ポーリング　ファイル番号入力（ポーリング原稿消去・プリント）	*/
#define	OPR_BATCH_BOX_NUMBER_INPUT		6	/* 一括送信ボックス番号入力（一括送信原稿消去・プリント・送信）	*/
#define	OPR_BATCH_INDEX_NUMBER_INPUT	7	/* 一括送信ファイル番号入力（一括送信原稿消去・プリント）		*/
#define	OPR_PRG_BATCH_BOX_INPUT			8	/* 一括送信ボックス番号入力（プログラムワンタッチ登録）			*/
#define	OPR_FCODE_BOX_DOC_NUMBER_INPUT	9	/* Ｆコード　ファイル番号入力（Ｆコード蓄積原稿消去・プリント）	*/
#define	OPR_CIPHER_RX_DOC_NUMBER_INPUT	10	/* 暗号化受信原稿番号入力（暗号化受信原稿復号化）				*/
#define	OPR_CIPHER_EXTENSION_KEY_INPUT	11	/* 暗号化拡張キー番号入力（暗号化受信原稿復号化）				*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#define	OPR_USERCODE_NUMBER_CHECK		12	/* ユーザコード番号入力チェック									*/
#define	OPR_USERCODE_NUMBER_INPUT		13	/* ユーザコード番号入力											*/
#define	OPR_MAIL_COMMAND_NUMBER_INPUT	14	/* メールコマンド入力											*/
#define	SF_PTT_VFC_BAND_EDGE_INPUT		15	/* ｻｰﾋﾞｽﾌｧﾝｸｼｮﾝPTTﾃｽﾄ信号用ﾊﾟﾗﾒｰﾀ値入力							*/
#endif
#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/09 */
#define	OPR_T30_MONITOR_NUMBER_INPUT	16	/* Ｔ３０モニター番号入力（Ｔ30モニタープリント）				*/
#endif

/* GroupNumberInput()用 */
#define	OPR_GROUP_NUMBER_INPUT			1	/* グループ番号入力						*/
#define	OPR_RELAYGROUP_NUMBER_INPUT		2	/* 中継指示送信グループ番号入力			*/

/* InputNumberRotation()用 */
#define	OPR_TX_DEPART_CODE_INPUT		1	/* 送信時の部門コード入力				*/
#define	OPR_JUNK_MAIL_NUMBER_INPUT		2	/* ジャンクメール防止ダイヤル番号入力	*/

/*------------------------------------------
 * 時計入力
 * カレンダーの種類
 *------------------------------------------*/
#define	JPN_CLOCK_TYPE				0
#define	USA_CLOCK_TYPE				1
#define	EUR_CLOCK_TYPE				2
#define	OPR_SET_CLOCK				3
#define	OPR_SET_DATE_TIME			4
#define	OPR_SET_PROGRAM_DATE_TIME	5
#define	OPR_SET_BATCH_DATE_TIME		6

#define	CALENDER_TYPE				0
#define	COMMAND_TIME_TYPE			1
#define	SECURITY_RX_TIME_TYPE		2
#define	CONT_POLLING_RX_TIME_TYPE	3
#define	CALENDER_DATE_TYPE			4
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#define AUTO_MAIL_RX_TIME_TYPE		5
#endif

/* セット中のコマンドファイルがないことを示す (SettinfCommandFileNumber)*/
#define	NO_SETTING_COMMAND_FILE		0xFF

/************************************************************************
 * 各種入力番号の表示最小値												*
 * Copied from \src\rice\v53\define\opr_def.hv By S.K May.18,1995       *
 ************************************************************************/
#define	OPR_BATCH_FILE_MIN			1	/* 一括送信ＢＯＸ				*/
#define	OPR_SPEED_DIAL_MIN			1	/* 短縮番号						*/
#if (PRO_MAKER == FX)
#define	OPR_MAILBOX_MIN				1	/* 親展番号						*/
#endif
#if (PRO_MAKER == MML)
#define	OPR_MAILBOX_MIN				0	/* 親展番号						*/
#endif
#define	OPR_DATA_BASE_NUMBER_MIN	0	/* 検索ポーリングファイル番号	*/
#define	OPR_SECURE_MAIL_HOLD_MIN	1	/* 親展受信原稿保存期間			*/
#define	OPR_BATCH_FILE_MIN			1	/* 一括送信ＢＯＸ				*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
#define	OPR_PRG_NUMBER_MIN			73	/* プログラムワンタッチ			*/
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)	/* Add By H.Fujimura 1998/12/28 */
 #if defined(HINOKI3)	/* by K.Watanabe 2004/10/18 */
#define	OPR_PRG_NUMBER_MIN			1	/* プログラムワンタッチ			*/
 #else
#define	OPR_PRG_NUMBER_MIN			25	/* プログラムワンタッチ			*/
 #endif
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
#define	OPR_PRG_NUMBER_MIN			25	/* プログラムワンタッチ			*/
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)
#define	OPR_PRG_NUMBER_MIN			1	/* プログラムワンタッチ			*/
#endif
#define	OPR_FCODE_BOX_MIN			1	/* ＦコードＢＯＸ番号			*/
#define	OPR_CIPHER_KEY_BOOK_MIN		0	/* 暗号化キーブック番号			*/
#if (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
#define	OPR_ND_MIN					1	/* ナンバーディスプレイ登録番号	*/
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
#define	OPR_WARP_MIN				1	/* ＦＡＸワープ登録番号			*/
#endif

/************************************************
 * キー入力をチャタリングとみなす時間
 ************************************************/
#define	KEY_CHATTARING_ON_TIME			2
#define	KEY_CHATTARING_OFF_TIME			3
#define	ONETOUCH_SHEET_MAX				2

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI) *//* 1998/09/22 by T.Soneoka */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 1998/09/22 by T.Soneoka */ /* Add by Y.Kano 2003/07/10 */

	#define	KEY_MATRICS_COLUM_MAX			8
#else
	#define	KEY_MATRICS_COLUM_MAX			10
#endif
#define	SHEET_SWITCH_CHATTERING_TIME	1
#if (PRO_CONT_KEY_INPUT == ENABLE)
#define	CONTINUOUS_KEY_INPUT_TIME		100
#define	KEY_HIT_TIME					10
#endif

/**************************************************
 * ワンタッチのシート状態
 *************************************************/
#define	ONETOUCH_SHEET1			0
#define	ONETOUCH_SHEET2			1

/**********************************************
 * ワンタッチの先頭コードと最終コード 1995/11/27 Eguchi
 **********************************************/
#define	ONETOUCH_MIN_KEY	ONETOUCH_A_KEY
#define	ONETOUCH_MAX_KEY	ONETOUCH_8_KEY

/*********************************************
 * リターン値
 ********************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#define OPR_START			3	/* コマンドスタート */
#define OPR_MAIL_CONTINUE	2	/* メールコマンドオペレーション続行 */
#endif
#define	OPR_CONTINUE	1	/* オペレーション続行		*/
#define	OPR_END			0	/* オペレーション終了／完了	*/

#define	CONFIRM_EXEC	1
#define	CONFIRM_ABORT	2


/****************************************
 * 全角第１バイトの範囲
 ***************************************/
#define WORD_CHARACTER_MIN		0x80
#define WORD_CHARACTER_MAX		0x9F

/*************************************************
 * シフトJIS第１・第２水準エリア 第１バイトの範囲
 ************************************************/
#define SHIFT_JIS_1_HIGH_MIN	0x81
#define SHIFT_JIS_1_HIGH_MAX	0x9F

/*************************************************
 * シフトJIS第２水準エリア 第１バイトの範囲
 ************************************************/
#define SHIFT_JIS_2_HIGH_MIN	0xE0
#define SHIFT_JIS_2_HIGH_MAX	0xFC

/*************************************************
 * シフトJIS第１・第２水準エリア 第２バイトの範囲
 ************************************************/
#define SHIFT_JIS_LOW_MIN		0x40
#define SHIFT_JIS_LOW_MAX		0xFC

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/04/10
*             TYPE:  define
*      VAR TO HOLD:  GetFontAddress()
*      DESCRIPTION:  漢字フォントデータ獲得　戻り値（アドレス内容）
************************************************************************/
#define	CG_ADDRESS		0	/* ＣＧのアドレス					*/
#define	FONT_DATA_NO	1	/* 漢字フォントテーブルの配列番号	*/


/********************************
 * 名前入力。入力モード		SATSUKI2では別の定義を利用します。2003/11/28 SMuratec
 ********************************/
#define	ROMAN_TO_KANA_MODE	0	/* ローマ字カナ変換モード（日本のみ）	*/
#define	KANJI_CODE_MODE		1	/* 漢字コードモード（日本のみ）			*/
#define	UPPER_MODE			2	/* 英数大文字モード						*/
#define	LOWER_MODE			3	/* 英数小文字モード						*/
#define	SIGNAL_MODE			4	/* 記号モード							*/
#define	HEX_CODE_MODE		5	/* ＨＥＸコードモード					*/
#define	CODE_MODE			6	/* 記号・ＨＥＸコードモード				*/

/**********************************
 * 電話帳オペレーション戻値
 * 1995/05/24 Eguchi
 **********************************/
/*#define	OPR_CONTINUE			1 */
#define	TELBOOK_END				2
#define	TELBOOK_FAXCOM			3
#define	TELBOOK_TEL				4
#define	TELBOOK_TEL_ON_HOOK		5	/* 現在未使用 */
#define	TELBOOK_BROADCAST		6
#define	TELBOOK_SPEED_KEY		7
#define	TELBOOK_SET				8

/***********************************
 * 電話帳テーブル
 ***********************************/
#define	OPR_TELBOOK_DATANUMBER		0
#define	OPR_TELBOOK_SORTPRIORITY	1

/**********************************
 * 電話帳オペレーション引数他
 * コマンド登録用オペレーションの引数の兼用
 **********************************/
#define	OPR_COM_OPE			0	/* コマンド登録オペレーション		*/
#define	OPR_TEL_OPE			1	/* 電話オペレーション				*/
#define	OPR_PRG_OPE			2	/* プログラム登録オペレーション		*/
#define	OPR_MAIN_OPE		3	/* メインオペレーション				*/
#define	OPR_BOOK_SIZE_OPE	4	/* ブック原稿サイズオペレーション	*/
#define	OPR_COM_OPTION_OPE	5	/* 応用通信オペレーション			*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
#define	OPR_INP_CHAR_OPE	6	/* 文字入力オペレーション			*/
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/**********************************
 * Key Wait Time (Int)
 * 1995/06/16	Eguchi
 **********************************/
#define	KEY_WAIT_FOREVER		0xFFFF
#define	KEY_WAIT_ONE_MINUTE		6000
#define	KEY_WAIT_ONE_SECOND		100
#define	KEY_WAIT_2_SECOND		200
#define	KEY_WAIT_FEW_TIME		300

/*********************************
 * ボリューム調整モード
 ********************************/
#define	OPR_VOLUME_UP		0
#define	OPR_VOLUME_DOWN		1

/*-------------------------------*
 * データシフト方向
 *-------------------------------*/
#define	SHIFT_BACKWORD		0
#define	SHIFT_FORWORD		1

/*-------------------------------*
 * ポーリングオペレーション種別
 *-------------------------------*/
#define	STORE_POLLING_DOC	0
#define	ERASE_POLLING_DOC	1
#define	PRINT_POLLING_DOC	2

/*-------------------------------------------*
 * ワンタッチ・短縮登録オペレーションモード
 *-------------------------------------------*/
#define	ENTER_DIAL_NUMBER	0
#define	ENTER_SUB_DIAL		1
#define	ENTER_REMOTE_NAME	2
#define	ENTER_GROUP_NUMBER	3
#define	ENTER_PIN_NUMBER	4
#define	ENTER_ATTRIBUTE1	5
#define	ENTER_ATTRIBUTE2	6
#define	ENTER_ATTRIBUTE3	7
#define	ENTER_ATTRIBUTE4	8

/*--------------------------------------------*
 * プログラムワンタッチ関係
 *--------------------------------------------*/
#define	PROGRAM_ENTER_MODE	0
#define	PROGRAM_START_MODE	1

/*--------------------------------------------*
 * プログラムワンタッチ登録状態
 *--------------------------------------------*/
#define	OPR_PRG_NO_STORED		0	/* 未登録					*/
#define	OPR_PRG_DELAYED_TX		1	/* 時刻指定送信				*/
#define	OPR_PRG_SECURE_TX		2	/* 親展送信					*/
#define	OPR_PRG_RELAY_BROADCAST	3	/* 中継指示送信				*/
#define	OPR_PRG_POLLING_RX		4	/* ポーリング受信			*/
#define	OPR_PRG_BATCH_TX		5	/* 一括送信					*/
#define	OPR_PRG_FCODE_TX		6	/* Ｆコード送信				*/
#define	OPR_PRG_FCODE_POLL		7	/* Ｆコードポーリング受信	*/
#define	OPR_PRG_CIPHER_TX		8	/* 暗号化送信				*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
#define	OPR_PRG_MAIL_GROUP		9	/* メールアドレスグループ	*/
#endif
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
#define	OPR_PRG_LIST			10	/* リスト					*/
#define	OPR_PRG_STORE			11	/* 蓄積						*/
#endif

/*----------------------------------*
 * ダイアル記号
 *----------------------------------*/
#define	PAUSE_MARK			1
#define	TONE_MARK			2
#define	FLASH_MARK			3
#define	MERCURY_MARK		4
#define	MERCURY_TONE_MARK	5
#define	MULTI_TEL_MARK		6	/* ２回線仕様用 */

/*---------------------------------*
 * データ型
 *---------------------------------*/
#define	ASC_DATA_TYPE		0
#define	BCD_DATA_TYPE		1
#define	ASC_JIS_DATA_TYPE	2
#define	BCD_PIN_DATA_TYPE	3	/* PIN番号は終端文字がないため BCD_DATA_TYPE と区別する 97/12/04 T.Fukumoto */

/*------------------------------------*
 * 親展オペレーションモード
 *------------------------------------*/
#define	ENTER_SECURE_BOXNO			0	/* 親展ボックス登録		*/
#define	CHECK_SECURE_PASSCODE		1	/* パスコードチェック	*/
#define	ENTER_SECURE_BOXNAME		2	/* 名前入力				*/
#define	ENTER_SECURE_NEW_PASSCODE	3	/* パスコード入力		*/
#define	SET_SECURE_END				4	/* 終了					*/
#define	SET_SECURE_COMPLETE			5	/* 完了					*/

/*--------------------------------------*
 * ＦコードＢＯＸ登録オペレーション制御
 *--------------------------------------*/
#define	SELECT_FCODE_BOX_NO			 0	/* ＢＯＸ番号選択					*/
#define	CHECK_FCODE_PASS_CODE		 1	/* パスコード（暗証番号）チェック	*/
#define	ENTER_FCODE_BOX_NAME		 2	/* ＢＯＸ名登録						*/
#define	ENTER_FCODE_SUB				 3	/* サブアドレス番号登録				*/
#define	ENTER_FCODE_PWD				 4	/* 通信パスワード番号登録			*/
#define	SELECT_FCODE_KIND			 5	/* ＢＯＸ種類選択					*/
#define	ENTER_FCODE_OPTION			 6	/* オプション設定					*/
#define	ENTER_FCODE_HOLDTIME		 7	/* 原稿保持期間設定					*/
#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
#define	ENTER_FCODE_RELAY_BOX		 8	/* 中継ＢＯＸ設定					*/
#define	ENTER_FCODE_PASS_CODE		 9	/* パスコード（暗証番号）登録		*/
#define	SELECT_FCODE_BOX_STOP		10	/* ＢＯＸ番号選択中止				*/
#define	SET_FCODE_STOP				11	/* ＢＯＸ登録中止					*/
#define	SET_FCODE_COMPLETE			12	/* ＢＯＸ登録完了					*/
#else
#define	ENTER_FCODE_PASS_CODE		 8	/* パスコード（暗証番号）登録		*/
#define	SELECT_FCODE_BOX_STOP		 9	/* ＢＯＸ番号選択中止				*/
#define	SET_FCODE_STOP				10	/* ＢＯＸ登録中止					*/
#define	SET_FCODE_COMPLETE			11	/* ＢＯＸ登録完了					*/
#endif

/*--------------------------------------------*
 * 暗号化機能キーブック登録オペレーション制御
 *--------------------------------------------*/
#define	SELECT_CIPHER_KEY_BOOK_NO		0	/* キーブック番号選択				*/
#define	CHECK_CIPHER_KEY_PASSCODE		1	/* パスコード（暗証番号）チェック	*/
#define	ENTER_CIPHER_KEY_BOOK_NAME		2	/* キーブック名登録					*/
#define	ENTER_CIPHER_KEY				3	/* 暗号化キーの登録					*/
#define	ENTER_CIPHER_KEY_CLUE			4	/* 暗号化キーのヒントの登録			*/
#define	ENTER_CIPHER_KEY_PASSCODE		5	/* パスコード（暗証番号）登録		*/
#define	SELECT_CIPHER_KEY_BOOK_STOP		6	/* キーブック番号選択中止			*/
#define	SET_CIPHER_KEY_BOOK_STOP		7	/* キーブック登録中止				*/
#define	SET_CIPHER_KEY_BOOK_COMPLETE	8	/* キーブック登録完了				*/

/*-------------------------------------*
 * パスコード登録モード
 *-------------------------------------*/
#define	PASS_CODE_ENTER_ZERO_OK		0	/* 新規登録（"0000"登録可能）	*/
#define	PASS_CODE_ENTER_ZERO_NG		1	/* 新規登録（"0000"登録不可能）	*/
#define	CHK_PASS_CODE_ENTER			2	/* 暗証番号の確認用入力			*/

/*------------------------------------*
 * パラメータセット／クリアモード
 *------------------------------------*/
#define	PARAMETER_SET				1
#define	PARAMETER_CLEAR				2
#define	MACHINE_PARAMETER_MODE		0
#define	MEMORY_SWITCH_MODE			1
#define	UNIQ_SWITCH_MODE			2
#define	MAINTENANCE_SWITCH_MODE		3

/*-----------------------------------*
 * オペレーション中のエラー
 *-----------------------------------*/
/* 操作エラー */
#define	OPR_NO_ERROR					 0
#define	INVALID_NUMBER_ERROR			 1
#define	TOO_MANY_DIGITS_ERROR			 2
#define	INVALID_COPY_NUMBER_ERROR		 3
#define	NO_STORED_NUMBER_ERROR			 4
#define	INVALID_GROUP_NUMBER_ERROR		 5
#define	TOO_MANY_LOCATION_ERROR			 6
#define	INSERT_DOCUMENT_ERROR			 7
#define	FEEDER_IN_USE_ERROR				 8
#define	SCANNER_USE_ERROR				 9
#define	ALREADY_POLLING_STORED_ERROR	10
#define	NO_STORED_DOCUMENT_ERROR		11
#define	COMMAND_FULL_ERROR				12
#define	NO_COMMAND_ERROR				13
#define	NO_COMMAND_DOCUMENT_ERROR		14
#define	NO_COMMAND_RESULT_ERROR			15
#define	SECURE_DOC_EXIST_ERROR			16
#define	PRINTER_IN_USE_ERROR			17
#define	INVALID_ID_CODE_ERROR			18
#define	INVALID_PROTECT_PASSCODE_ERROR	19
#define	NO_PROTECT_PASSCODE_ERROR		20
#define	INPUT_RANGE_OVER_ERROR			21
#define	BATCH_DOCUMENT_FULL_ERROR		22
#define	LINE_BUSY_ERROR					23
#define	PROTECT_DOCUMENT_STORED_ERROR	24
#define	NO_PROTECT_DOCUMENT_ERROR		25
#define	NO_PIN_NUMBER_ERROR				26
#define	NO_DEPARTMENTCODE_ERROR         27
#define	BATCH_DOCUMENT_STORED_ERROR		28
#define	RESET_DOCUMENT_ERROR			29
#define	BOOK_COVER_OPEN_ERROR			30
#define	PRINTER_CLEANING_ERROR			31
#define	NOT_STORED_DOCUMENT_ERROR		32
#define	BOX_IN_USE_ERROR				33
#define	TOO_MANY_DIRECT_DIAL_ERROR		34
#define	SETTING_SECURE_BOX_ERROR		35
#define	BOOK_SIZE_NO_SET_ERROR			36
#define	NOT_COMPLETE_STORED_ERROR		37
#define	NOT_COMPLETE_COPY_ERROR			38
#define	SCAN_PREPARING_ERROR			39
#define	COPY_PROTECT_ERROR				40
#define	NOT_SCAN_DOC_SIZE_ERROR			41
#define	SHORT_FIGURE_ERROR				42
#define	ALREADY_NUMBER_STORED_ERROR		43
#define	NOT_ENTRY_ERROR					44
#define	NO_SCAN_CIPHER_MODE_ERROR		45
#define	CIPHERING_ERROR					46
#define	DECIPHERING_ERROR				47
#define	USE_DEFAULT_CIPHER_KEY_ERROR	48
#define	USE_PROGRAM_ONETOUCH_ERROR		49
#define	TOP_COVER_OPEN_ERROR			50
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1998/12/28 */
//#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/12 by K.Okada */
#endif
#define	FAX_NUMBER_STORED_ERROR			51
#define	PROGRAM_STORED_ERROR			52
#define	MAIL_ADDRESS_STORED_ERROR		53
#define	MAIL_GROUP_STORED_ERROR			54
#define	USER_DATA_FULL_ENTRY_ERROR		55
#define	NO_RS232C_PCB_ERROR				56
#define	TOO_MANY_DIRECT_ADDRESS_ERROR	57
#define	NO_USER_DATA_ERROR				58
#define	INVALID_ADDRESS_ERROR			59
#define	NO_TCPIP_BOARD_ERROR			60
#define	MEMORY_FULL_ERROR				61
#define	ALREADY_USED_ERROR				62
#define	NO_ENTRY_DATA_ERROR				63
#define	NO_STORED_ADDRESS_ERROR			64
#define	INVALID_PASSWORD_ERROR			65
#define	EXECUTE_COMMAND_ERROR			66
#define NO_DEVICE_ERROR					67
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1998/12/28 */
//#endif
#endif
#define	SETTING_RELAY_BOX_ERROR			68	/* Add By H.Fujimura 1998/12/28 */
#define	TOO_MANY_RELAY_DIRECT_ERROR		69	/* Add By H.Fujimura 1998/12/28 */

/*******************************************
 * ファンクションオペレーション
 *******************************************/
#define	FIRST_KEY			0
#define	SECOND_KEY			1

/* そのた */
#define	ONETOUCH_CODE		0
#define	ONETOUCH_OFFSET		1
#define	SET_PIN_NUMBER		0
#define	START_PIN_NUMBER	1

/********************************************
 * LINE STATUS
 ********************************************/
#define	OPR_NCU_IDLE			0
#define	OPR_TEL1_OFFHOOK		1
#define	OPR_TEL2_OFFHOOK		2
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/08/23 */
#define	OPR_LINE_HOLD			4
#define	OPR_LINEHOLDTEL1UP		5
#define	OPR_HOOKKEY_OFFHOOK		8
#define OPR_TEL1_TEL2_OFFHOOK	3
#define OPR_TEL1_HOOK_OFFHOOK	9
#define OPR_TEL2_HOOK_OFFHOOK	10
#else /* !defined (KEISATSU) */
#define	OPR_HOOKKEY_OFFHOOK		3
#define	OPR_LINE_HOLD			4
#define	OPR_LINEHOLDTEL1UP		5
#endif /* defined (KEISATSU) */

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/11/12
*             TYPE:  define
*      VAR TO HOLD:  OPR_InputDialInfo
*      DESCRIPTION:  ダイヤル番号入力での入力情報
************************************************************************/
#define	SPEED_MARK_INPUT	0x01	/* 短縮キーを押した後（番号入力前）		*/
#define	GROUP_MARK_INPUT	0x02	/* グループキーを押した後（番号入力前）	*/
#define	PROGRAM_INPUT		0x04	/* プログラムワンタッチが指定されている	*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#define MAIL_DIRECT_MARK_INPUT	0x08	/** ダイレクトアドレスが入力されている */
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
/************************************************************************
*               BY:  K.Watanabe
*             DATE:  2001/04/04
*             TYPE:  define
*      VAR TO HOLD:  
*      DESCRIPTION:  文字入力用定義
************************************************************************/
#define	OPR_KATAKANA_MODE		0	/* カタカナ入力モード					*/
#define	OPR_ALPHAMERIC_MODE		1	/* 英数字入力モード						*/
#define	OPR_1_BYTE_CODE_MODE	2	/* 半角文字コード入力モード(ASCII･ANK)	*/
#define	OPR_2_BYTE_CODE_MODE	3	/* 全角文字コード入力モード(区点コード)	*/

#define	OPR_TEN_KEY_MAX					12	/* テンキーの数					*/
#define	OPR_KATAKANA_CHARACTER_MAX		11	/* カタカナ入力テーブルのサイズ	*/
#define	OPR_ALPHAMERIC_CHARACTER_MAX	14	/* 英数入力テーブルのサイズ		*/
#define	OPR_CODE_FIGURE_MAX				4	/* コード入力時の桁数			*/

struct ANK_CharacterTable_t {
	UWORD	KUTEN_Code;
	UBYTE	Character;
};
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/**************************************************
 * 予約確認消去モード
 **************************************************/
#define	OPR_COMMAND_REVIEW		1
#define	OPR_EXEC_REVIEW			2
#define	OPR_COM_DIAL_REVIEW		3

/**************************************************
 * 予約確認。参照コマンド種別（コマンド検索モード )
 **************************************************/
#define	OPR_EXECUTE_COMMAND		1
#define	OPR_WAITING_COMMAND		2
#define	OPR_EXECUTE_BATCH		3
#define	OPR_WAITING_BATCH		4
#define	OPR_EXECUTE_CONTPOLL	5
#define	OPR_WAITING_CONTPOLL	6
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#define	OPR_EXECUTE_MAILTRX		7
#define	OPR_WAITING_MAILTRX		8
#endif


/**************************************************
 * 予約確認。参照コマンド種別最大数
 **************************************************/
#if (PRO_CONTINUOUS_POLLING == ENABLE)
 #if (PRO_BATCH_TX == ENABLE)
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
  	#define	OPR_MAX_COM_SEARCH		9
  #else
	#define	OPR_MAX_COM_SEARCH		7
  #endif
 #else
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
 	#define	OPR_MAX_COM_SEARCH		7
  #else
	#define	OPR_MAX_COM_SEARCH		5
  #endif
 #endif
#else
 #if (PRO_BATCH_TX == ENABLE)
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
  	#define	OPR_MAX_COM_SEARCH		7
  #else
	#define	OPR_MAX_COM_SEARCH		5
  #endif
 #else
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
  	#define	OPR_MAX_COM_SEARCH		5
  #else
	#define	OPR_MAX_COM_SEARCH		3
  #endif
 #endif
#endif

/**************************************************
 * 予約確認同報種別
 **************************************************/
#define	OPR_EXEC_BROADCAST		1
#define	OPR_WAIT_BROADCAST		2

/*****************************************************************
 * 予約確認。コマンドあるいは実行キューの参照位置再設定時のモード
 ****************************************************************/
#define	COMMAND_REVIEW_MODE		0	/* コマンド確認時（通信確認キーによるスクロール時）のポインター再設定*/
#define	COMMAND_CLEAR_MODE		1	/* コマンド消去後のポインター再設定 */
#define COMMAND_FIRST_REVIEW	2   /* コマンド確認時 (通信確認キーによる最初の確認時）

/*******************************************************************************
 * メモリー送信時：原稿蓄積可能かどうかを判断するための空きブロックの閾値
 *
 * ＣＣＩＴＴ．Ｎｏ１．チャートを４枚分蓄積するために必要なブロック数とします。
 *
 * CCITT No1.Chart １枚分：約１２ＫＢｙｔｅ（ＭＧ３、Ｎｏｒｍａｌ）
 * 1Block:4KByte
 * 多めにとって、１６Ｋ／枚とする。
 *
 * ＊受信時の閾値と区別した理由はスキャナの解像度がどのように関係
 *   してくるかわからなかったので、同じにできるものであればこの
 *   デファインははずします
 * 1996/02/29 Eguchi
 ******************************************************************************/
#define	OPR_MEM_TX_STORE_BORDER		16

/***********************************************
 * 一括送信ボックス使用状態
 ***********************************************/
#define	BATCH_BOX_NOT_ENTRY	1	/* 未登録 */
#define	BATCH_BOX_EMPTY		2	/* 未使用 */
#define	BATCH_BOX_STORING	3	/* 蓄積中 */
#define	BATCH_BOX_WAITING	4	/* 予約中 */
#define	BATCH_BOX_EXECUTE	5	/* 実行中 */
#define	BATCH_BOX_ERASED	6
#define	BATCH_BOX_POWER_OFF	7

/*********************************************
 * ワンタッチ・短縮・プログラム・一括送信ボックス消去
 * オペレーション状態
 *********************************************/
#define	ERASE_ITEM_SELECT_STEP	0	/* 消去項目?選択モード */
#define ERASE_CONFIRM_STEP		1	/* 消去確認モード *? */
#define	ERASE_COMPLETE_STEP		2	/* 消去完了表示終了まちモード */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
/*****************************************************
** 以下のチェックを行う関数のリターン値
** 1. 入力バッファ(InputNumber.Buffer[])のカーソル位置
**    の文字がどの通信種類の宛先に属するか
** 2. 入力バッファの中にどの通信種類の
**    宛先が含まれているか
** 3. ワンタッチの登録内容
** 4. プログラムワンタッチの登録内容
** (関数名)
** CheckDestKindAtCursorPosition()
** CheckDestKindInInputBuffer()
** CheckOnetouchStoreStatus()
** CheckProgramStoreStatus()
*****************************************************/
#define IS_EMPTY_DESTINATION	0			/* バッファ空 */
#define IS_FAX_NUMBER			1			/* FAX番号 */
#define IS_MAIL_ADDRESS			2			/* メールアドレス */
#define IS_MAIL_FAX_DESTINATION	3			/* FAX番号とメールアドレスの混在 */

/****************************************
** InputNumberMailMarkSet()の処理モード
****************************************/
#define DIRECT_ADDRESS_INPUT_MODE	1		/* ダイレクトアドレス入力記号挿入処理 */
#define ADDRESS_MARK_INPUT_MODE		2		/* ダイレクトアドレスに使用される記号挿入処理 */

/******************************************
** 入力バッファの宛先入力状態
** CheckDestKindInInputBuffer()の中の
** ローカル変数input_statusにセットされる値
******************************************/
#define FAX_NUMBER_INPUT	(UBYTE)0x01		/* FAX番号が入力されていた場合 */
#define MAIL_ADDRESS_INPUT	(UBYTE)0x02		/* メールアドレスが入力されていた場合 */

/******************
** IPアドレスの桁数
******************/
#define IP_ADDRESS_FIGURE 12				/* ピリオドを除くIPアドレスの桁数 */
#define IP_ADDRESS_BLOCK_FIGURE 3			/* ピリオドで区切られた1区切りの桁数 */
#define IP_ADDRESS_BLOCK_NUMBER (IP_ADDRESS_FIGURE/IP_ADDRESS_BLOCK_FIGURE)	/* 区切りの個数 */

/*********************
**	自動受信の実行間隔
*********************/
#define AUTO_RCV_INTERVAL_INIT_TIME 180	/* 初期値 */
#define AUTO_RCV_INTERVAL_MIN_TIME 3	/* 最小値 */

/*******************************************************
** トーン検出・非検出設定
** SetDialParameter()
** OperationBuffer.EnterSettingControl.EnableBitの設定値
*******************************************************/
#define DIAL_TONE_DETECT_ON	0x01
#define BUSY_TONE_DETECT_ON	0x02

/************************************************
** 個々のユーザに対するメールコマンド有無チェック
** CheckUserMailCommand()のリターン値
************************************************/
#define OPR_MAIL_NO_CMD			0
#define OPR_MAIL_CMD_WAITING	1
#define OPR_MAIL_CMD_EXECUTE	2

/*************************************
** ユーザデータ登録チェックモード
** （PIN番号が登録されているかどうか）
** CheckAllUserDataStore()の引数
*************************************/
#define NO_CHECK_PIN_STORE_IN_USER_DATA	0
#define CHECK_PIN_STORE_IN_USER_DATA	1

/**************************
** 登録項目の種類
** 共通関数中での分岐に使用
**************************/
#define OPR_INF_KIND_USER_NAME		1
#define OPR_INF_KIND_ISP_NAME		2
#define OPR_INF_KIND_PPP_ID			3
#define OPR_INF_KIND_PPP_PASSWORD	4
#define OPR_INF_KIND_POP_ID			5
#define OPR_INF_KIND_POP_PASSWORD	6
#define OPR_INF_KIND_SMTP_SERVER	7
#define OPR_INF_KIND_POP_SERVER		8
#define OPR_INF_KIND_CLIENT_IP		9
#define OPR_INF_KIND_ISP_SERVER_IP	10
#define OPR_INF_KIND_GATEWAY_IP		11

/*****************************
** PTTテスト信号送出開始・終了
** opr_msrv.c
*****************************/
#define SF_DMDM_TONAL_SIGNAL_TEST_END	0
#define SF_DMDM_TONAL_SIGNAL_TEST_START	1
#define SF_DMDM_TONAL_SIGNAL_TEST_CONT	2
#define SF_DMDM_TONAL_SIGNAL_TEST_STOP	3

/******************************************
** PTTテスト信号
** V.FC変調アッパー・バンド・エッジの減衰量
** opr_msrv.c
******************************************/
#define UPPER_BAND_EDGE_FIGURE_MAX		2
#define UPPER_BAND_EDGE_MAX				22
#endif

/**************************************************/
/*  各種登録用のバッファ 						　*/
/**************************************************/

/*--------------------------------------*
 * 文字入力用バッファ
 * 数字入力、名前入力・・・・
 *--------------------------------------*/
struct CharacterInputData_t {
		UBYTE	Buffer[OPR_CHARACTER_INPUT_MAX + 1];	/* 入力データ									*/
		UBYTE	CursorPosition;							/* 入力位置										*/
		UBYTE	WritePosition;							/* 入力最後尾									*/
		UBYTE	DisplayStartPosition;					/* 入力データ上表示開始位置						*/
		UBYTE	LcdDisplayPosition;						/* ＬＣＤ上表示開始位置							*/
		UBYTE	MaxFigure;								/* 入力可能最大桁数								*/
		UWORD	MaxValue;								/* 入力可能最大値								*/
		UWORD	MinValue;								/* 入力可能最小値								*/
		UBYTE	InputKeyBuffer[5];						/* カナ入力時ローマ字カナ変換バッファ			*/
		UBYTE	InputKeyPosition;						/* カナ入力時ローマ字カナ変換バッファ入力位置	*/
		UBYTE	Mode;									/* 名前入力時入力モード							*/
		UBYTE	*FixedWordingHigh;						/* 上段表示固定文字列							*/
		UBYTE	*FixedWordingLow;						/* 下段表示固定文字列							*/
		UBYTE	IsNoInputEnable;						/* 未入力可能か									*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		UBYTE	Only7bitAsciiEnable;					/* 文字入力時７bitコードの入力しかできない */
															/* このフラグが１の場合以下のようになる */
															/* JPN:かな入力禁止、HEXコード入力禁止、・入力禁止  */
															/* USA:HEXコード入力禁止、・入力禁止 				*/
		UBYTE	AddressMarkInputMode;					/* メールアドレス中の記号(".","@","_","-")入力モード */
#endif
#if (PRO_NAME_RECALL == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
		UBYTE	*Name;									/* 相手先名(NULL含む)							*/
#endif
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/21 */
		UBYTE	Keisatsu;								/* 警察仕様属性の明示(ビットアサイン) */
		UBYTE	KeisatsuBuf[4];
		UBYTE	KeisatsuPosition;
#endif		/* End of (defined (KEISATSU)) */
};

/*------------------------------------*
 * 	プログラム登録用バッファ		  *
 *  コマンド登録・プログラム登録	  *
 *------------------------------------*/
struct	InputNumberData_t {	/* 419byte */
	UBYTE	Buffer[OPR_INPUT_NUMBER_BUFFER_MAX + 1];	/* 登録中データ (相手先番号)						*/
	UWORD	WritePosition;								/* 入力最終位置									  2 */
	UWORD	CursorPosition;								/* 入力位置										  2 */
	UWORD	DisplayStartPosition;						/* 表示開始位置									  2 */
	UBYTE	MultiNumberStatus;							/* 同報フラグ									  1 */
	UBYTE	InputDialType;								/* 入力種別										  1 */
	UBYTE	PIN_NumberCheck;							/* ＰＩＮ番号入力チェック要不要 YES:要、NO：不要  1 */
};

/* InputDialType.InputDialTypeの値 */
#define	COMMAND_DIAL_TYPE	0
#define	PROGRAM_DIAL_TYPE	1
#define	BATCH_DIAL_TYPE		2

/*--------------------------------------*
 * オペレーションバッファ
 *--------------------------------------*/
union OperationBufferData_t {

	/*------------------------------*/
	/* ワンタッチ・短縮ダイヤル登録 */
	/*------------------------------*/
	struct OnetouchSpeedControlData_t {	/* 12byte */
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//		UBYTE	SelectNumber;					/* 現在編集中のワンタッチ,短縮の番号 */
#endif
		UWORD	SelectNumber;					/* 現在編集中のワンタッチ,短縮の番号 */
												/* ０ ～ SYS_ONETOUCH_DIAL_MAX - 1:ワンタッチダイアルＡ～４*/
												/* SYS_ONETOUCH_DIAL_MAX～SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX - 1　:短縮 000～169に対応*/
		UBYTE	SelectNumberDisplayBuffer[5];	/* ワンタッチ記号及び短縮番号表示用文字列 */
		UBYTE	SpeedNumberInputBuffer[4];		/* 短縮番号入力バッファ */
		UBYTE	SpeedNumberInputPosition;		/* 短縮番号入力位置 */
		UWORD	SelectOptionalNumber;			/* 現在編集中の任意短縮 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		UBYTE	MailAddressSetting;				/* ワンタッチメールアドレス登録 */
#endif
	} OntchSpdCtrl;

	/*-------------------------------------------------------*/
	/* プログラムワンタッチ登録用バッファ  1995/11/27 Eguchi */
	/*-------------------------------------------------------*/
	struct ProgramOnetouchControlData_t {	/* 12byte */
		UBYTE	SelectNumber;					/* 現在編集中のプログラム番号 */
		UBYTE	SelectNumberDisplayBuffer[5];	/* プログラムワンタッチ記号表示用バッファ　*/
	} ProgOntchCtrl;

	/*------------------------*/
	/* 親展受信ボックス登録用 */
	/*------------------------*/
	struct SecureMailControlData_t {	/* 6 Byte */
		UBYTE	BoxNumber;					/* ボックス番号 */
		UBYTE	BoxName[SYS_BOX_NAME_MAX];	/* ボックス名（入力されたデータを一時退避しておく */
		UWORD	Passcode;					/* パスコード */
	} ScurMailCtrl;

	/*-----------------------------------------------------------*
	 * 機器設定用制御データ
	 * SYB_SettingStatus[]に登録される項目の編集にのみ使用する
	 * 将来、例えばワンタッチ登録中に何かSYB_SettingStatus[]
	 * を編集するようなことになれば、OperationBufferから外に
	 * 出さねばならない.
	 *-----------------------------------------------------------*/
	struct EnterSettingControlData_t {	/* 14Byte */
		UBYTE	*ItemWording;		/* 上段表示固定文字列 	*/
		UBYTE	*SelectWording;		/* 選択肢先頭文字列   	*/
		UBYTE	SelectCount;		/* 選択肢個数 		  	*/
		UBYTE	EnableBit;			/* 機器設定データ中の設定ビット */
		UBYTE	SettingData;		/* 現在の設定値 		*/
		UBYTE	ValidPattern;
		UBYTE	ShiftCount;			/* ビットデータをスカラー値で処理するためのビットのシフト回数 */
		UBYTE	DisplayBuffer[OPR_DISPLAY_MAX + 1];
	} EntrSettingCtrl;

#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 1996/09/17 by K.Watanabe */
	/* 機器設定用制御データ（選択枝９個以上用） */
	struct EnterSettingControlDataToLong_t {
		UBYTE	*ItemWording;		/* 上段表示固定文字列			*/
		UBYTE	*SelectWording;		/* 選択肢先頭文字列				*/
		UBYTE	SelectCount;		/* 選択肢個数					*/
		UBYTE	EnableBit;			/* 機器設定データ中の設定ビット	*/
		UBYTE	SettingData;		/* 現在の設定値					*/
		UDWORD	ValidPattern;
		UBYTE	ShiftCount;			/* ビットデータをスカラー値で処理するためのビットのシフト回数 */
		UBYTE	DisplayBuffer[OPR_DISPLAY_MAX + 1];
		UBYTE	SetPosition;		/* セットステータス 97/07/03 Add by M.Kuwahara */
	} EntrSettingCtrlLng;
#endif	/* (PRO_PC_PRINT == ENABLE) */

	/* コピーオペレーション用 */
	struct CopyConrolData_t {	/*5Byte */
		UBYTE	ReserveNumber;			/* 指定部数 */
		UBYTE	ReserveNumberBuffer[3]; /* 部数入力値表示用バッファ */
		UBYTE	NumberInputFlag;		/* 部数入力、未入力フラグ */
	} CopyCtrl;

	/* メモリスイッチ・マシンパラメーターオペレーション用*/
	/* 編集するマシンパラメータ・メモリースイッチが決定されるまで */
	/* ワンタッチ短縮の属性編集には使用していない  */
	struct SoftSwitchData_t {	/* 8Byte */
		UBYTE	*ItemWording; 	/* セット時の上段文字列 [Set Memory Switch]などクリア時はこの文字列の次の文字列 */
		UBYTE	*SetParameter;	/* セットするパラメータ SYS_MachineParameter/SYS_MemorySwitchの先頭アドレス */
		UBYTE	SwitchMax;	  	/* セットするパラメータの個数 */
		UBYTE	SelectSwitch; 	/* セットするパラメータの番号（スイッチ番号) 00(A0)～99(J9) */
	} SoftSwCtrl;

	/* 一括送信ボックス登録用 */
	struct BatchTxControlData_t {	/* 1 + 26 + 17 + 4 = 48 Byte */
		UBYTE	SelectNumber;						/* 一括送信ボックス番号  */
		struct	SYS_BatchTxDialData_t DialNumber;	/* ダイアル番号 */
		UBYTE	Name[SYS_DIAL_NAME_MAX];			/* 名前 */
		UDWORD	ProgramTime;						/* 送信時刻 ->未使用。SpecialCommandValueを使用 */
	} BatTxCtrl;

	/* 予約確認オペレーション用  **/
	struct ReviewControlData_t {
		UBYTE	CommandPointer;		/* コマンド単位での確認消去モードでの現在の参照位置 */
		UBYTE	ExecItem;			/* 宛先単位での確認消去モードでの現在の種別コード */
		UBYTE	ExecPointer;		/* 宛先単位での確認消去モードでの現在の参照位置 */
		UBYTE	ReviewMode;			/* コマンド単位か宛先単位か */
									/* OPR_COMMAND_REVIEW,OPR_EXEC_REVIEW,OPR_COM_DIAL_REVIEW */
		UBYTE	SearchCommandType;	/* 現在検索しているコマンドのグループ */
									/* OPR_EXECUTE_COMMAND/OPR_EXECUTE_BATCH/OPR_WAITING_COMMAND/OPR_WAITING_BATCH */
		UBYTE	CommandKind;		/* コマンド種別（コマンドファイルか一括送信か) */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		UBYTE	UserNameOrID[OPR_USER_NAME_OR_ID_MAX];	/* ユーザ名(登録されていないときはPOP LoginID) */
		UBYTE	InputBuffer[OPR_INPUT_BUFFER_MAX];			/* 宛先入力バッファ */
#endif
	} ReviewCtrl;

	/* 部門管理オペレーション用 */
	UBYTE	DepartmentSelectNumber;

	/* ジャンクメール防止ダイヤルオペレーション用 */
	UBYTE	JunkMailSelectNumber;

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	/*--------------------------------------*/
	/* ナンバーディスプレイオペレーション用 */
	/*--------------------------------------*/
	struct ND_Ctrl_t {	/* 5byte */
		UBYTE	SelectNumber;						/* 現在編集中のナンバーディスプレイの登録番号 */
		UBYTE	DisplayBuffer[ND_FIGURE_MAX + 2];	/* ナンバーディスプレイ登録番号表示用文字列 */
	} ND_Ctrl;
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	/*------------------------------*/
	/* ＦＡＸワープオペレーション用 */
	/*------------------------------*/
	struct WarpCtrl_t {	/* 4byte */
		UBYTE	SelectNumber;						/* 現在編集中のＦＡＸワープの登録番号 */
		UBYTE	DisplayBuffer[WARP_FIGURE_MAX + 2];	/* ＦＡＸワープ登録番号表示用文字列 */
	} WarpCtrl;
#endif

};

/*---------------------------------*/
/* 電話オペレーション用 79Byte	   */
/*---------------------------------*/
/* TelControlをOperationBufferの外に出す */

#define	OPR_TELCONTROL_BUFFER_MAX	50	/* ﾀﾞｲｱﾙ40桁＋PIN番号8桁＋＊が入る分のバッファ */

struct TelControlData_t {
	UBYTE	Buffer[OPR_TELCONTROL_BUFFER_MAX];
	UBYTE	SpeedBuffer[5];		/*短縮番号入力バッファ */
	UBYTE	SpeedPosition;		/*短縮番号入力位置 */
	UBYTE	NcuStatus;			/*回線回りの状態 */
	UBYTE	PinAccessMode;		/*ＰＩＮアクセスモード */
	UBYTE	PinNumberDialFlag;	/*ＰＩＮをダイアルしたことを表すフラグ */
								/*初期化時に０にセットされ、ダイアルバッファにセットする所*/
								/*で１にセットする以外は更新してはならない */
								/*このフラグが立っていたら、ＰＩＮ番号のダイアルは不要 */
	UBYTE	AfterPinDialDisplayBuffer[OPR_DISPLAY_MAX];
};

/*-------------------------*
 * 応用機能登録用
 *-------------------------*/
struct SpecialCommandData_t {	/*30byte*/
	UDWORD	CommandTime;					/* 時刻指定("分"単位）		*/
	struct	SYS_OptionData_t CommandOption;	/* 応用機能					*/
#if (PRO_DEPARTMENT == ENABLE)
	UWORD	DepartmentCode;					/* 部門コード				*/
#endif
	UBYTE	TitleMessage;					/* カバーページ設定			*/
	UBYTE	Page;							/* 送信ページ数				*/
#if (PRO_PIN_ACCESS == ENABLE)
	UBYTE	PIN_Number[SYS_PIN_MAX];		/* ＰＩＮ番号(個人別ＰＩＮアクセスの際のＰＩＮ番号) */
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	UDWORD	ContPollingStartTime;			/* 連続ポーリング開始時刻	*/
	UDWORD	ContPollingEndTime;				/* 連続ポーリング終了時刻	*/
#endif
};

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1998/01/09
*             TYPE:  struct
*      VAR TO HOLD:  struct OPR_FcodeFunctionData_t OPR_FcodeData
*      DESCRIPTION:  Ｆコード機能用構造体定義
************************************************************************/
#if (PRO_F_CODE == ENABLE)
struct OPR_FcodeFunctionData_t {
	UBYTE	Status;												/* サブアドレスＢＯＸ管理テーブルの登録状態	*/
	UBYTE	BoxName[SYS_BOX_NAME_MAX];							/* ボックス名								*/
	UBYTE	SubAddress[SYS_ID_MAX];								/* ＳＵＢ（サブアドレス番号）				*/
	UBYTE	Password[SYS_ID_MAX];								/* ＰＷＤ（通信パスワード）					*/
	UBYTE	HoldTime;											/* 原稿保持期間								*/
	UBYTE	Option;												/* オプション設定							*/
	UWORD	PassCode;											/* パスコード								*/
	UBYTE	BoxNumber;											/* ボックス番号								*/
	UBYTE	BoxNumberInpPos;									/* ボックス番号入力位置						*/
	UBYTE	BoxNumberInpBuf[OPR_FCODE_BOX_FIGURE_MAX + 1];		/* ボックス番号入力バッファ					*/
 #if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	UBYTE	Onetouch[SYS_ONETOUCH_BIT_FIELD_MAX];				/* 中継配信先（ワンタッチ）					*/
	UBYTE	Speed[SYS_SPEED_BIT_FIELD_MAX];						/* 中継配信先（短縮）						*/
	UDWORD	Group;												/* 中継配信先（グループ）					*/
 #endif
};
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1998/01/09
*             TYPE:  struct
*      VAR TO HOLD:  struct OPR_CipherFunctionData_t OPR_CipherData
*      DESCRIPTION:  暗号化機能用構造体定義
************************************************************************/
#if (PRO_CIPHER == ENABLE)
struct OPR_CipherFunctionData_t {
	/* SYB_KeyBookData・CipherData展開用 */
	UBYTE	KeyExtensionOn;										/* 拡張キー設定					*/
	UBYTE	Key[SYS_KEY_MAX];									/* 暗号化キー					*/
	UBYTE	KeyClue[SYS_KEY_CLUE_MAX];							/* 暗号化キーのヒント			*/
	UBYTE	KeyName[SYS_BOX_NAME_MAX];							/* キーの名前					*/
	UWORD	KeyPassCode;										/* キーごとの暗証番号			*/

	/* CipherData展開用 */
	UWORD	PrintPageNo;										/* 暗号化解除時のプリント部数	*/
	UBYTE	ExtensionKey;										/* 拡張キー						*/
	UBYTE	NoiseRemovalOn;										/* 暗号化解除時のノイズ除去設定	*/
	UBYTE	SetKeyMode;											/* キー入力の設定方法			*/

	/* オペレーション制御用 */
	UBYTE	TitleWording[OPR_WORDING_LEN];						/* タイトルワーディング			*/
	UBYTE	KeyBookNumber;										/* キーブック番号				*/
	UBYTE	KeyBookNumberInpPos;								/* キーブック番号入力位置		*/
	UBYTE	KeyBookNumberInpBuf[OPR_KEY_BOOK_FIGURE_MAX + 1];	/* キーブック番号入力バッファ	*/
	UBYTE	SelectKeyBookType;									/* キーブック選択時の処理内容	*/
};
#endif

/*----------------------------*
 * 現在時刻を格納する領域
 *----------------------------*/
union OperationTimeData_t {	/* 7Byte */
	TIME_DATA_t	BCD_StructTime;
	UBYTE		BCD_StringTime[7];
};

/*----------------------------------*
 * Function Table
 *----------------------------------*/
struct FUNCTION_TABLE_t {
	UBYTE		FirstCode;				/* （１）第一入力キー・コード 			*//* 機能番号 */
	UBYTE		SecondCode;				/* （２）第二入力キー・コード 			*//* 現状未使用 */
	UBYTE		Available;				/* （３）有効／無効の区別     			*//* 現在ほとんど未使用 */
	CONST UBYTE	*Wording;				/* （４）表示文字へのポインター 		*/
	void		(*FunctionName)(void);	/* （５）実行関数 						*/
	struct FUNCTION_TABLE_t *NextLevel;	/* （６）下位層のテーブルへのポインター */
};

/*--------------------------------------*
 * SERVICE Function Table
 *--------------------------------------*/
struct SERV_FUNCTION_t {
	UBYTE	KeyCode;				/* コード（機能＊の次に入力されるキーコード */
	void	(*ExecFunction)(void);	/* 実行関数 */
};

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1996/11/20
*             TYPE:  struct
*      VAR TO HOLD:  CONST struct ROMAJI_KATAKANA_TABLE_t RomajiToKatakanaTable[OPR_ROMAJI_KANA_TABLE_MAX]
*      DESCRIPTION:  ローマ字カナ変換テーブル構造体定義
************************************************************************/
struct ROMAJI_KATAKANA_TABLE_t {
	UBYTE	Romaji[4];
	UBYTE	Katakana[4];
};

#if (PRO_COPY_FAX_MODE == ENABLE)
/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/03/10
*             TYPE:  define
*      VAR TO HOLD:  CONST struct OPR_MANUAL_PAPER_TABLE_t	OPR_SelectManualPaperTable[]
*                    CONST struct OPR_MAGNIFI_PAPER_TABLE_t	OPR_FixedMagnification_*[]
*                    CONST struct OPR_FIXED_MAGNIFI_TABLE_t	OPR_FixedMagnificationTable[]
*                    CONST struct OPR_FIXED_MAGNIFI_TABLE_t	OPR_FixedReductionTable[]
*                    CONST struct OPR_PRINT_PAPER_TABLE_t	OPR_PrintPaperSize_*[]
*                    CONST struct OPR_BOOK_COPY_DOC_TABLE_t	OPR_BookCopyDocumentSizeTable[]
*      DESCRIPTION:  コピーモード用構造体定義
************************************************************************/
/* 手差し記録紙サイズ選択テーブル用構造体定義 by K.Watanabe 1997/12/18 */
struct OPR_MANUAL_PAPER_TABLE_t {
	UBYTE	PaperSize;		/* 手差し記録紙サイズ				*/
	UBYTE	OHP_Mode;		/* ＯＨＰモード（0:記録紙, 1:OHP）	*/
};

/* コピー固定倍率テーブル用構造体定義 */
struct OPR_MAGNIFI_PAPER_TABLE_t {
	UBYTE	DocumentSize;		/* 原稿サイズ	*/
	UBYTE	PaperSize;			/* 記録紙サイズ	*/
};
struct OPR_FIXED_MAGNIFI_TABLE_t {
	UBYTE	Magnification;									/* コピー倍率					*/
	struct OPR_MAGNIFI_PAPER_TABLE_t *(MagnifiTablePtr);	/* コピー倍率テーブルポインター	*/
};

/* ブックコピー原稿サイズ設定テーブル用構造体定義 */
struct OPR_PRINT_PAPER_TABLE_t {
	UBYTE	Magnification;		/* コピー倍率 */
	UBYTE	BookDocumentSize;	/* 原稿サイズ */
};
struct OPR_BOOK_COPY_DOC_TABLE_t {
	UBYTE	PaperSize;										/* 記録紙サイズ				*/
	struct OPR_PRINT_PAPER_TABLE_t *(PrintPaperTablePtr);	/* 記録紙テーブルポインター	*/
};
#endif

/************************************************************************
*               BY:  M.Kuwahara
*             DATE:  1997/06/05
*             TYPE:  define
*      VAR TO HOLD:  CONST struct LED_AREA_t LedArea[]
*      DESCRIPTION:  ＬＥＤテスト用 点灯順序設定用テーブル定義
************************************************************************/
struct LED_AREA_t {
	UBYTE	Port;			/* ＬＥＤ・ポート */
	UWORD	LedType;		/* ＬＥＤ選択場所 */
};

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/12/12
*             TYPE:  struct
*      VAR TO HOLD:  CONST struct OPR_INCH_CENTI_TABLE_t OPR_ChangeInchCentiTable[]
*      DESCRIPTION:  インチ・センチ変換テーブル用構造体定義
************************************************************************/
#if (PRO_CIPHER == ENABLE)
struct OPR_INCH_CENTI_TABLE_t {
	UBYTE	Inch;		/* インチを１０倍した値			*/
	UBYTE	Centi;		/* インチをセンチに変換した値	*/
};
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
/****************************
** メール送信時作業用バッファ
****************************/
struct	OPR_MailCommand_t	{
	UBYTE	DirectAddressInputMode;	/* ダイレクトアドレス入力時のモード */
	UBYTE	HexCodeInputBuffer[3];	/* Hexコード入力バッファ */
	UBYTE	HexCodeInputPosition;	/* Hexコード入力カーソル位置 */
	UBYTE	HistoryReadPosition;	/* ヒストリ読み位置 */
	UBYTE	UserNumber;				/* ユーザ番号 */
	UBYTE	GetMailCommandFile;		/* コマンド番号 */
};
/**********************************
** ユーザデータ登録用ワークバッファ
**********************************/
struct	OPR_INF_UserData_t	{
	UBYTE	TempUserData[OPR_USER_DATA_TEMP_MAX];			/* 汎用ユーザデータワークバッファ */
	UBYTE	TempCodeNumberInit[OPR_USER_CODE_MAX];			/* コード番号初期値バッファ */
	UBYTE	TempOptionalSetting;							/* オプション設定ビットアサイン */
	UWORD	TempStartTime;									/* 自動受信開始時間 */
	UWORD	TempEndTime;									/* 自動受信終了時間 */
	UWORD	TempIntervalTime;								/* 自動受信時間間隔 */
	UWORD	TempHoldTime;									/* 受信メール保持期間 */
#if (0)
//	UBYTE	TempToneSetting;								/* トーン検出設定ビットアサイン */
#endif
};
/************************************
** メール送信上段表示用ワークバッファ
************************************/
struct	OPR_INF_TempAddressInput_t	{
	UBYTE Buffer[OPR_INPUT_BUFFER_MAX];
	UBYTE Offset;
};

/****************************
** ユーザデータ登録変更フラグ
****************************/
struct	OPR_INF_UpdateUserData_t	{
	UBYTE MailBoxChangeFlag;
	UBYTE UserCodeNumberFlag;
	UBYTE UserNameFlag;
	UBYTE ISP_NameFlag;
	UBYTE TelNumberFlag[SYS_INF_SUB_DIAL_MAX];
	UBYTE PIN_NumberFlag;
	UBYTE PPP_LoginID_Flag;
	UBYTE PPP_PasswordFlag;
	UBYTE PPP_AuthenticationFlag;
	UBYTE POP_LoginID_Flag;
	UBYTE POP_PasswordFlag;
	UBYTE MailAddressFlag;
	UBYTE SMTP_ServerFlag;
	UBYTE POP_ServerFlag;
	UBYTE Primary_DNS_ServerFlag;
	UBYTE Secondary_DNS_ServerFlag;
	UBYTE IP_AddressFlag;
	UBYTE ISP_ServerAddressFlag;
	UBYTE GatewayAddressFlag;
};
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
/* 拡張プログラムワンタッチ（リスト）用構造体定義 */
struct OPR_ProgramList_t {
	UBYTE	Item;							/* 種別 */
	void	(*EnterFunction)(void);			/* 実行関数 */
};
/* 拡張プログラムワンタッチ（蓄積）用構造体定義 */
struct OPR_ProgramStore_t {
	UBYTE	Item;							/* 種別 */
	UBYTE	(*SetFunction)(UBYTE);			/* 登録関数 */
	void	(*EnterFunction)(UBYTE);		/* 実行関数 */
};
#endif

/* 機器設定の設定項目の有効無効のテーブルオフセット値 */
#define	OPR_LINE_TYPE				 0
#define	OPR_SCAN_WITDH				 1
#define	OPR_PRIMARY_MODE			 2
#define	OPR_PRIMARY_CONTRAST		 3
#define	OPR_RECEIVE_MODE			 4
#define	OPR_RX_REDUCTION			 5
#define	OPR_RS232C_SPEED			 6
#define	OPR_RS232C_PARITY			 7
#define	OPR_RING_PATTERN			 8
#define	OPR_COPY_REDUCTION			 9
#define	OPR_UPPER_PAPER				10
#define	OPR_LOWER_PAPER				11
#define	OPR_PIN_MODE				12
#define	OPR_HALFTONE				13
#define OPR_JUNK_MAIL				14
 #if (PRO_KEYPANEL == PANEL_ANZU_L)		/* 1998/06/03 Y.Murata ｱﾗﾑｺ特殊対応 LT,LG,A4対応 ARM_A4*/
#define	OPR_UPPER_PAPER_ARM			15
 #endif

#define	OPR_VALID_CHECK_NOT_NEED	0xFF

/* 機器設定の設定項目の有効無効のビット位置のデファイン */
#define	OPR_DIAL_10PPS				0x01
#define	OPR_DIAL_20PPS				0x02
#define	OPR_DIAL_TONE				0x04

#define	OPR_SCANNER_A4				0x01
#define	OPR_SCANNER_B4				0x02
#define	OPR_SCANNER_A3				0x04

#define	OPR_MODE_NORMAL				0x01
#define	OPR_MODE_FINE				0x02
#define	OPR_MODE_SFINE				0x04
#define	OPR_MODE_GRAY				0x08

#define	OPR_DENS_LIGHT				0x01
#define	OPR_DENS_LITTLE_LIGHT		0x02
#define	OPR_DENS_NORMAL				0x04
#define	OPR_DENS_LITTLE_DARK		0x08
#define	OPR_DENS_DARK				0x10

#define	OPR_TEL_READY				0x01	/* 手動受信モード TEL				*/
#define	OPR_FAX_READY				0x02	/* 自動受信モード FAX				*/
#define	OPR_FAX_TEL_READY			0x04	/* 自動受信モード FAX/TEL(FAX優先)	*/
#define	OPR_TEL_FAX_READY			0x08	/* 自動受信モード TEL/FAX(TEL優先)	*/
#define	OPR_ANS_FAX_READY			0x10	/* 自動受信モード ANS/FAX			*/
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* DIAL_INの追加 by Y.Kano 2003/08/26 */
#define	OPR_DIAL_IN_READY			0x20	/* 自動受信モード DIAL_IN			*/
 #endif

#define	OPR_RX_REDUCTION_1			0x01	/* 固定受信縮小率1 Auto	*/
#define	OPR_RX_REDUCTION_2			0x02	/* 固定受信縮小率2 100	*/
#define	OPR_RX_REDUCTION_3			0x04	/* 固定受信縮小率3 97	*/
#define	OPR_RX_REDUCTION_4			0x08	/* 固定受信縮小率4 91	*/
#define	OPR_RX_REDUCTION_5			0x10	/* 固定受信縮小率5 81	*/
#define	OPR_RX_REDUCTION_6			0x20	/* 固定受信縮小率6 75	*/
#define	OPR_RX_REDUCTION_7			0x40	/* 固定受信縮小率7 ??	*/

#define	OPR_RS232C_SPEED_VARIABLE	0x01	/* RS232C速度AUTO */
#define	OPR_RS232C_SPEED_600		0x02	/* RS232C速度600 */
#define	OPR_RS232C_SPEED_1200		0x04	/* RS232C速度1200 */
#define	OPR_RS232C_SPEED_2400		0x08	/* RS232C速度2400 */
#define	OPR_RS232C_SPEED_4800		0x10	/* RS232C速度4800 */
#define	OPR_RS232C_SPEED_9600		0x20	/* RS232C速度9600 */
#define	OPR_RS232C_SPEED_19200		0x40	/* RS232C速度19200 */

#define	OPR_RS232C_PARITY_NONE		0x00	/* RS232CパリティNONE */
#define	OPR_RS232C_PARITY_ODD		0x10	/* RS232CパリティODD */
#define	OPR_RS232C_PARITY_EVEN		0x20	/* RS232CパリティEVEN */

#define	OPR_RS232C_DATA_LENGTH_8	0x08	/* RS232Cデータ長８or７ */
#define	OPR_RS232C_STOP_LENGTH_2	0x40	/* RS232Cストップビット2or1 */

#define	OPR_RING_PATTERN_1			0x01	/* リングマスタのベルパターン1 */
#define	OPR_RING_PATTERN_2			0x02	/* リングマスタのベルパターン2 */
#define	OPR_RING_PATTERN_3			0x04	/* リングマスタのベルパターン3 */
#define	OPR_RING_PATTERN_4			0x08	/* リングマスタのベルパターン4 */
#define	OPR_RING_PATTERN_5			0x10	/* リングマスタのベルパターン5 */
#define	OPR_RING_PATTERN_6			0x20	/* リングマスタのベルパターン6 */
#define	OPR_RING_PATTERN_7			0x40	/* リングマスタのベルパターン5 */	/* MBS要求により追加 '95.03/23 By J.Miyazaki */
#define	OPR_RING_PATTERN_8			0x80	/* リングマスタのベルパターン6 */	/* MBS要求により追加 '95.03/23 By J.Miyazaki */

#define	OPR_COPY_FIXED_REDUCTION_1	0x01	/* コピー用固定縮小率1 Auto */
#define	OPR_COPY_FIXED_REDUCTION_2	0x02	/* コピー用固定縮小率2 100  */
#define	OPR_COPY_FIXED_REDUCTION_3	0x04	/* コピー用固定縮小率3 97   */
#define	OPR_COPY_FIXED_REDUCTION_4	0x08	/* コピー用固定縮小率4 91   */
#define	OPR_COPY_FIXED_REDUCTION_5	0x10	/* コピー用固定縮小率5 81   */
#define	OPR_COPY_FIXED_REDUCTION_6	0x20	/* コピー用固定縮小率6 75   */
#define	OPR_COPY_FIXED_REDUCTION_7	0x40	/* コピー用固定縮小率7 ??   */

#define	OPR_UPPER_SIZE_NONE			0x01	/* 上段ｶｾｯﾄ無 */
#define	OPR_UPPER_SIZE_A4			0x02	/* 上段手動記録紙選択A4 */
#define	OPR_UPPER_SIZE_B4			0x04	/* 上段手動記録紙選択B4 */
#define	OPR_UPPER_SIZE_LETTER		0x08	/* 上段手動記録紙選択レター */
#define	OPR_UPPER_SIZE_LEGAL		0x10	/* 上段手動記録紙選択リーガル */
#define	OPR_UPPER_SIZE_F4			0x20	/* 上段手動記録紙選択F4 */

#define	OPR_LOWER_SIZE_NONE			0x01	/* 下段ｶｾｯﾄ無 */
#define	OPR_LOWER_SIZE_A4			0x02	/* 下段手動記録紙選択A4 */
#define	OPR_LOWER_SIZE_B4			0x04	/* 下段手動記録紙選択B4 */
#define	OPR_LOWER_SIZE_LETTER		0x08	/* 下段手動記録紙選択レター */
#define	OPR_LOWER_SIZE_LEGAL		0x10	/* 下段手動記録紙選択リーガル */
#define	OPR_LOWER_SIZE_F4			0x20	/* 下段手動記録紙選択F4 */

#define	OPR_PIN_ACCESS_OFF			0x01	/* ＰＩＮアクセスしない */
#define	OPR_PIN_ACCESS_MODE1		0x02	/* 個別ＰＩＮアクセス（相手先別のＰＩＮ番号で発呼） */
#define	OPR_PIN_ACCESS_MODE2		0x04	/* 部門ＰＩＮアクセス（発呼者別のＰＩＮ番号で発呼)  */

#define	OPR_HALFTONE_16_1			0x01	/* 写真１　階調１６ */
#define	OPR_HALFTONE_16_2			0x02	/* 写真２　階調１６ */
#define	OPR_HALFTONE_64_1			0x04	/* 写真１　階調６４ */
#define	OPR_HALFTONE_64_2			0x08	/* 写真２　階調６４ */

#define OPR_BLOCK_JUNK_FAX_OFF		0x01	/* ダイレクトメール防止 ＯＦＦ	 */
#define OPR_BLOCK_JUNK_FAX_MODE1	0x02	/* ダイレクトメール防止 モード１ */
#define OPR_BLOCK_JUNK_FAX_MODE2	0x04	/* ダイレクトメール防止 モード２ */
#define OPR_BLOCK_JUNK_FAX_MODE3	0x08	/* ダイレクトメール防止 モード３ */

/***********************************************************************
*          BY:   Y.Matsukuma ( JCS )
*        DATE:   1996/01/23
*        TYPE:   DEFINE
* VAR TO HOLD:   UWORD SF_RelayStatus
* DESCRIPTION:   Display of Service Function For Relay Test
************************************************************************/
#define	OPR_RELAY_ALL_OFF		0x00
#define	OPR_CML_RELAY_ON		0x01
#define	OPR_DP_RELAY_ON			0x02
#define	OPR_S_RELAY_ON			0x04
#define	OPR_H_RELAY_ON			0x08
#define	OPR_L_RELAY_ON			0x10
#define	OPR_C24_RELAY_ON		0x20

/* SRAM Test */
#if (0)
#define	OPR_BKUPRAM_START		(UBYTE *)0x10003800L	/* Segment = 1000H,Offset = 3800H */
#define	OPR_BKUPRAM_END			(UBYTE *)0x1000FFFFL	/* Segment = 1000H,Offset = FFFFH */
#define	OPR_PATJOURNAL_START	(UBYTE *)0x20000000L	/* Segment = 2000H,Offset = 0000H */
#define	OPR_PATJOURNAL_END		(UBYTE *)0x2000FFFFL	/* Segment = 2000H,Offset = FFFFH */
#endif
#define	OPR_BKUPRAM_START		(UBYTE *)0x00400000L
#define	OPR_BKUPRAM_END			(UBYTE *)0x0040FFFFL
#define	OPR_PATJOURNAL_START	(UBYTE *)0x00440000L
#define	OPR_PATJOURNAL_END		(UBYTE *)0x0044FFFFL

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/08/26 Y.Matsukuma */
#define		OPR_BKUPRAM1_START		(UBYTE *)0x00400000L
#define		OPR_BKUPRAM1_END		(UBYTE *)0x0040FFFFL
#define		OPR_BKUPRAM2_START		(UBYTE *)0x00440000L
#define		OPR_BKUPRAM2_END		(UBYTE *)0x0044FFFFL
#define		OPR_HIGHSRAM_START		(UBYTE *)0x00800000L
#define		OPR_HIGHSRAM_END		(UBYTE *)0x008057FFL
#endif

/* RS232C Test */
#define	CHECK_OK		1

/* 部門管理 */
#define	DPTCODE_MAX		4

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1996/09/17
*             TYPE:  define
*      VAR TO HOLD:  CONST UDWORD ValidSelectBitPatternTableLong[]
*      DESCRIPTION:  ＰＣプリント対応　上段記録紙サイズ設定
************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
/* 機器設定の設定項目の有効無効のテーブルオフセット値 */
#define	OPR_PCR_UPPER_PAPER				0
/* #define	OPR_VALID_CHECK_NOT_NEED	0xFF	ValidSelectBitPatternTable[]と共用 */

/* 機器設定の設定項目の有効無効のビット位置のデファイン */
#define	OPR_PCR_MANUAL_SIZE_NONE	0x00000001		/* 上段手動記録紙選択　なし                   */
#define	OPR_PCR_MANUAL_SIZE_A5		0x00000002		/* 上段手動記録紙選択　Ａ５縦                 */
#define	OPR_PCR_MANUAL_SIZE_LT		0x00000004		/* 上段手動記録紙選択　レター縦               */
#define	OPR_PCR_MANUAL_SIZE_A4		0x00000008		/* 上段手動記録紙選択　Ａ４縦                 */
#define	OPR_PCR_MANUAL_SIZE_LG		0x00000010		/* 上段手動記録紙選択　リーガル縦             */
#define	OPR_PCR_MANUAL_SIZE_B5R		0x00000020		/* 上段手動記録紙選択　Ｂ５横 ＪＩＳ          */
#define	OPR_PCR_MANUAL_SIZE_B4		0x00000040		/* 上段手動記録紙選択　Ｂ４縦 ＪＩＳ          */
#define	OPR_PCR_MANUAL_SIZE_A3		0x00000080		/* 上段手動記録紙選択　Ａ３縦                 */
#define	OPR_PCR_MANUAL_SIZE_A4R		0x00000100		/* 上段手動記録紙選択　Ａ４横                 */
#define	OPR_PCR_MANUAL_SIZE_LTR		0x00000200		/* 上段手動記録紙選択　レター横               */
#define	OPR_PCR_MANUAL_SIZE_F4		0x00000400		/* 上段手動記録紙選択　Ｆ４縦                 */
#define	OPR_PCR_MANUAL_SIZE_A5R		0x00000800		/* 上段手動記録紙選択　Ａ５横                 */
#define	OPR_PCR_MANUAL_SIZE_POST	0x00001000		/* 上段手動記録紙選択　はがき縦               */
#define	OPR_PCR_MANUAL_SIZE_LD		0x00002000		/* 上段手動記録紙選択　レジャー縦             */
#define	OPR_PCR_MANUAL_SIZE_GLTR	0x00004000		/* 上段手動記録紙選択　ガバメント・レター横   */
#define	OPR_PCR_MANUAL_SIZE_EXER	0x00008000		/* 上段手動記録紙選択　エグゼブティブ横       */
#define	OPR_PCR_MANUAL_SIZE_HLTR	0x00010000		/* 上段手動記録紙選択　ハーフレター横         */  /* added by honda 1997/10/09 */
#define	OPR_PCR_MANUAL_SIZE_INVR	0x00010000		/* 上段手動記録紙選択　インボイス横           */
#define	OPR_PCR_MANUAL_SIZE_GLG		0x00020000		/* 上段手動記録紙選択　ガバメント・リーガル縦 */
#define	OPR_PCR_MANUAL_SIZE_GLT		0x00040000		/* 上段手動記録紙選択　ガバメント・レター縦   */
#define	OPR_PCR_MANUAL_SIZE_CARD	0x00080000		/* 上段手動記録紙選択　カードストック紙       */
#define	OPR_PCR_MANUAL_SIZE_EXE		0x00100000		/* 上段手動記録紙選択　エグゼブティブ縦       */
#define	OPR_PCR_MANUAL_SIZE_B5		0x00200000		/* 上段手動記録紙選択　Ｂ５縦 ＪＩＳ          */
#define	OPR_PCR_MANUAL_SIZE_C5		0x00400000		/* 上段手動記録紙選択　Ｃ５縦                 */
#define	OPR_PCR_MANUAL_SIZE_HLT		0x00800000		/* 上段手動記録紙選択　ハーフ・レター縦       */
#define	OPR_PCR_MANUAL_SIZE_INV		0x01000000		/* 上段手動記録紙選択　インボイス縦           */
#define	OPR_PCR_MANUAL_SIZE_B6		0x02000000		/* 上段手動記録紙選択　Ｂ６縦 ＪＩＳ          */
#define	OPR_PCR_MANUAL_SIZE_DL		0x04000000		/* 上段手動記録紙選択　ＤＬ縦                 */
#define	OPR_PCR_MANUAL_SIZE_CM10	0x08000000		/* 上段手動記録紙選択　コマーシャル１０縦     */
#define	OPR_PCR_MANUAL_SIZE_A6		0x10000000		/* 上段手動記録紙選択　Ａ６縦                 */
#define	OPR_PCR_MANUAL_SIZE_MNC		0x20000000		/* 上段手動記録紙選択　モナーク縦             */
#define	OPR_PCR_MANUAL_SIZE_35		0x40000000		/* 上段手動記録紙選択　３”ｘ５”縦           */
#define	OPR_PCR_MANUAL_SIZE_USER	0x80000000		/* 上段手動記録紙選択　不定形紙               */
#endif	/* (PRO_PC_PRINT == ENABLE) */

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1996/12/27
*             TYPE:  define
*      VAR TO HOLD:  SetDialDataToDispBuffer()
*      DESCRIPTION:  ダイヤルデータ表示用バッファ展開時呼出し箇所
************************************************************************/
#define	OPR_PROGRAM_DISPLAY		0	/* プログラムワンタッチ登録から呼出し	*/
#define	OPR_PROGRAM_EXECUTE		1	/* プログラム送信コマンド展開から呼出し	*/
#define	OPR_TX_DISPLAY			2	/* 送信相手先表示から呼出し				*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/01/29
*             TYPE:  define
*      VAR TO HOLD:  CheckOnetouchData()
*      DESCRIPTION:  ワンタッチダイヤル検査戻り値
************************************************************************/
#define	OPR_EXCEPT_ONETOUCH		0	/* ワンタッチダイヤル以外				*/
#define	OPR_ONETOUCH_DIAL		1	/* ワンタッチダイヤル（０１～７２）		*/
#define	OPR_ONETOUCH_ALPHABET	2	/* ワンタッチダイヤル（Ａ～Ｚ，ａ～ｚ）	*/
#define	OPR_ONETOUCH_NUMBER		3	/* ワンタッチダイヤル（Ｕ１～Ｕ８）		*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/01/30
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  ワンタッチ番号桁数
************************************************************************/
/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

#define	OPR_ONETOUCH_NUMBER_FIGURE	2	/* ０１から７２の数字部分の桁数	*/
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
#define	OPR_ONETOUCH_NUMBER_FIGURE	1	/* Ｕ１～Ｕ８の数字部分の桁数	*/
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/02/06
*             TYPE:  define
*      VAR TO HOLD:  SetOnetouchCode()
*      DESCRIPTION:  ワンタッチ記号セット方法
************************************************************************/
#define	OPR_SET_ONETOUCH_CODE		1	/* かっこをつけてワンタッチ番号をセットする	*/
#define	OPR_SET_ONETOUCH_NUMBER		2	/* ワンタッチ番号のみセットする				*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/02/14
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  プログラムワンタッチの先頭のキーコード
************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
#define	OPR_TOP_PROGRAM_KEY		ONETOUCH_73_KEY
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)	/* Add By H.Fujimura 1998/12/28 */
#define	OPR_TOP_PROGRAM_KEY		ONETOUCH_25_KEY
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
#define	OPR_TOP_PROGRAM_KEY		0xFF	/* Modify by SMuratec L.Z.W 2003/09/16 */
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)
#define	OPR_TOP_PROGRAM_KEY		PROGRAM_P01
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/02/17
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  コピー部数最大桁数
************************************************************************/
#define	OPR_COPY_NUMBER_FIGURE_MAX		2	/* ２桁 */

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/02/25
*             TYPE:  define
*      VAR TO HOLD:  CONST struct OPR_FIXED_MAGNIFI_TABLE_t OPR_FixedMagnificationTable[]
*                    CONST struct OPR_FIXED_MAGNIFI_TABLE_t OPR_FixedReductionTable[]
*      DESCRIPTION:  コピー固定倍率
************************************************************************/
#define	OPR_MAGNIFI_50					 50				/* 　５０％	*/
#define	OPR_MAGNIFI_64					 64				/* 　６４％	*/
#define	OPR_MAGNIFI_70					 70				/* 　７０％	*/
#define	OPR_MAGNIFI_78					 78				/* 　７８％	*/
#define	OPR_MAGNIFI_81					 81				/* 　８１％	*/
#define	OPR_MAGNIFI_86					 86				/* 　８６％	*/
#define	OPR_MAGNIFI_93					 93				/* 　９３％	*/
#define	OPR_MAGNIFI_100					100				/* １００％	*/
#define	OPR_MAGNIFI_115					115				/* １１５％	*/
#define	OPR_MAGNIFI_122					122				/* １２２％	*/
#define	OPR_MAGNIFI_129					129				/* １２９％	*/
#define	OPR_MAGNIFI_141					141				/* １４１％	*/
#define	OPR_MAGNIFI_172					172				/* １７２％	*/
#define	OPR_MAGNIFI_200					200				/* ２００％	*/
#define	OPR_COPY_REDUCTION_MIN			OPR_MAGNIFI_50	/* 最小倍率	*/
#define	OPR_COPY_MAGNIFICATION_MAX		OPR_MAGNIFI_200	/* 最大倍率	*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/03/12
*             TYPE:  define
*      VAR TO HOLD:  NameInput()
*      DESCRIPTION:  名前入力で漢字入力が、可能／不可能の判断用
************************************************************************/
#define	OPR_KANJI_DISABLE		0	/* 漢字入力不可能	*/
#define	OPR_KANJI_ENABLE		1	/* 漢字入力可能		*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/04/24
*             TYPE:  define
*      VAR TO HOLD:  InputFcodeNumber(), InputFcodeStoreDocFile()
*      DESCRIPTION:  Ｆコードオペレーション定義
************************************************************************/
#define	OPR_FCODE_SET_SUB_ADDRESS		0	/* サブアドレス番号の登録	*/
#define	OPR_FCODE_SET_PASSWORD			1	/* 通信パスワード番号の登録	*/

#define	OPR_FCODE_STORE_DOC_PRINT		0	/* 蓄積原稿プリント			*/
#define	OPR_FCODE_STORE_DOC_ERASE		1	/* 蓄積原稿消去				*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/05/06
*             TYPE:  define
*      VAR TO HOLD:  OPR_NumberKeyInputMode
*      DESCRIPTION:  コピーモード　テンキー入力内容
************************************************************************/
#define	OPR_COPY_NUMBER_INPUT_MODE		0	/* コピー部数入力モード	*/
#define	OPR_COPY_MAGNIFI_INPUT_MODE		1	/* コピー倍率入力モード	*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/06/09
*             TYPE:  define
*      VAR TO HOLD:  CheckScanStartEnable()
*      DESCRIPTION:  原稿読み取り時、原稿がセットされているかのチェックを行うかどうか
************************************************************************/
#define	OPR_DOC_SET_NO_CHK			0	/* ﾁｪｯｸを行いません														*/
#define	OPR_DOC_SET_CHK_ONLY		1	/* ﾁｪｯｸを行い、ｴﾗｰ表示のみ行います										*/
#define	OPR_DOC_SET_CHK_INP_SET		2	/* ﾁｪｯｸを行い、ｴﾗｰ表示とﾌﾞｯｸ原稿ｻｲｽﾞ入力を行います（ｾｯﾄｷｰで終了）		*/
#define	OPR_DOC_SET_CHK_INP_STR		3	/* ﾁｪｯｸを行い、ｴﾗｰ表示とﾌﾞｯｸ原稿ｻｲｽﾞ入力を行います（ｽﾀｰﾄｷｰで終了）		*/
#define	OPR_DOC_SET_CHK_MANUAL_TRX	4	/* ﾁｪｯｸを行い、ｴﾗｰ表示のみ行います（ﾌﾞｯｸ原稿未設定のｴﾗｰ表示はしません）	*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/06/13
*             TYPE:  define
*      VAR TO HOLD:  CheckScanStartEnable()
*      DESCRIPTION:  原稿読み取り開始可能検査関数の戻り値
*          COMMENT:  ポプラＢのポーリング等の読み取り時にＦＢＳを使用する時は、
*                    CheckScanStartEnable()の中で原稿サイズの入力を行う様に
*                    変更したので戻り値の種類を増やしました
************************************************************************/
#define	OPR_SCAN_ENABLE			0	/* 読み取り可能							*/
#define	OPR_SCAN_DISABLE		1	/* 読み取り不可能						*/
#define	OPR_SCAN_STOP			2	/* 読み取り中止（ﾌﾞｯｸ原稿ｻｲｽﾞ入力中止）	*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/06/20
*             TYPE:  define
*      VAR TO HOLD:  CheckCopyMagnifiLimit()
*      DESCRIPTION:  コピー倍率適正範囲内検査関数の戻り値
************************************************************************/
#define	OPR_MAGNIFI_OK			0	/* 適正範囲内			*/
#define	OPR_MAGNIFI_UNDER		1	/* 適正範囲より小さい	*/
#define	OPR_MAGNIFI_OVER		2	/* 適正範囲より大きい	*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/07/04
*             TYPE:  define
*      VAR TO HOLD:  ModifyADF_CopyMagnifi()
*      DESCRIPTION:  ＡＤＦコピー倍率変更処理　呼び出し場所
************************************************************************/
#define	OPR_PAPER_SELECT		0	/* 用紙選択				*/
#define	OPR_ADF_DOC_IN			1	/* ＡＤＦに原稿をセット	*/
#define	OPR_ADF_DOC_OUT			2	/* ＡＤＦの原稿を抜く	*/
#define	OPR_CASSETTE_CLOSE		3	/* カセットクローズ		*/

/************************************************************************
*               BY:  M.Kuwahara
*             DATE:  1997/07/09
*             TYPE:  define
*      VAR TO HOLD:  ServiceCallOperation()
*      DESCRIPTION:  プリンタメンテナンス
************************************************************************/
#define	OPR_LIFE_ERROR_MAX		8	/* サービスコールのエラー最大数 */

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/07/18
*             TYPE:  define
*      VAR TO HOLD:  SelectCipherKeySet()
*      DESCRIPTION:  暗号化キー選択入力関数の呼び出し元
************************************************************************/
#define	OPR_DECIPHER_DOC		0	/* 暗号化予約原稿プリント・受信暗号化原稿復元	*/
#define	OPR_COM_OPTION			1	/* 応用通信										*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/09/12
*             TYPE:  define
*      VAR TO HOLD:  DisplayBookDocumentData()
*      DESCRIPTION:  ブック原稿設定値表示関数の呼び出し元
************************************************************************/
#define	OPR_CHG_BOOK_SIZE		0	/* ブック原稿サイズ変更	*/
#define	OPR_CHG_NEXT_DOC		1	/* 次原稿設定			*/

/************************************************************************
*               BY:  S.Fukui
*             DATE:  1997/10/01
*             TYPE:  define
*      VAR TO HOLD:  SelectData()
*      DESCRIPTION:  SelectData()の戻り値
************************************************************************/
#define	OPR_CANCELED			0	/* 設定中止（ストップ/タイムアウト)	*/
#define	OPR_ENTERED				1	/* 設定完了							*/
#define	OPR_CHANGED_MODE		2	/* モード変更						*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/10/09
*             TYPE:  define
*      VAR TO HOLD:  OPR_DispInfo
*      DESCRIPTION:  機器状態表示情報
************************************************************************/
#define	OPR_DSP_NO_ERROR		0x00	/* エラー未表示							*/
#define	OPR_DSP_ERROR_HIGH		0x01	/* エラー表示（上段を使用）				*/
#define	OPR_DSP_ERROR_LOW		0x02	/* 　　〃　　（下段を使用）				*/
#define	OPR_DSP_ERROR			0x03	/* 　　〃　　							*/
#define	OPR_DSP_SCAN_DISABLE	0x04	/* 　　〃　　（読み取り不可能エラー）	*/
#define	OPR_DSP_PRINT_DISABLE	0x08	/* 　　〃　　（プリント不可能エラー）	*/
#define	OPR_DSP_IDLE			0x10	/* 待機表示								*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/10/21
*             TYPE:  define
*      VAR TO HOLD:  OPR_Buf.CipherCtrl.SelectKeyBookType
*      DESCRIPTION:  暗号化機能キーブック選択目的
************************************************************************/
#define	OPR_EXCEPT_KEYBOOK_SET	0	/* キーブック登録以外	*/
#define	OPR_KEYBOOK_SET			1	/* キーブック登録		*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/11/10
*             TYPE:  define
*      VAR TO HOLD:  DisplayMachineErrorLow(), DisplayMachineErrorLow2()
*      DESCRIPTION:  エラー状態表示関数の引数
************************************************************************/
#define	OPR_ERROR_CHK			0	/* エラーの状態をチェック（表示はしません）	*/
#define	OPR_ERROR_DISP			1	/* エラーを表示								*/

/************************************************************************
*               BY:  Y.Matsukuma
*             DATE:  1997/11/14
*             TYPE:  define
*      VAR TO HOLD:  InputPbxCheck()
*      DESCRIPTION:  内線入力のチェックするバッファ種類
************************************************************************/
#define	OPR_CHARACTER_INP		0	/* ワンタッチ・短縮 */
#define	OPR_INPUT_NUMBER		1	/* 直接・一括送信・プログラムワンタッチ */

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/12/05
*             TYPE:  define
*      VAR TO HOLD:  OPR_CopyParamCheck
*      DESCRIPTION:  用紙・倍率確認状態
************************************************************************/
#define	OPR_NO_PARAM_CHK		0xFF	/* 確認必要なし（コピーパラメーター表示）			*/
#define	OPR_PARAM_CHK			0		/* 確認必要あり（エラー表示）						*/
#define	OPR_CHANGE_PARAM		1		/* 確認必要なし（エラー表示中に用紙・倍率を変更）	*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/12/10
*             TYPE:  define
*      VAR TO HOLD:  CheckADF_CopyMagnifi()
*      DESCRIPTION:  ＡＤＦコピー可能倍率検査の戻り値
************************************************************************/
#define	OPR_MAGNIFI_CHK_OK		0	/* 設定倍率が、コピー可能最大倍率未満							*/
#define	OPR_MAGNIFI_CHG_OK		1	/* 倍率変更確認ＯＫ（設定倍率が、コピー可能最大倍率より大きい）	*/
#define	OPR_MAGNIFI_CHG_NG		2	/* 倍率変更確認ＮＧ（設定倍率が、コピー可能最大倍率より大きい）	*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/12/12
*             TYPE:  define
*      VAR TO HOLD:  CheckCipherExecEnable()
*      DESCRIPTION:  暗号化・復号化可能検査関数の呼び出し元
************************************************************************/
#define	OPR_CIPHER_TX			0	/* 暗号化送信										*/
#define	OPR_DECIPHER_TX_DOC		1	/* 暗号化予約原稿復号化								*/
#define	OPR_DECIPHER_RX_DOC		2	/* 暗号化受信原稿復号化								*/
#define	OPR_DECIPHER_SCAN_DOC	3	/* 読み取り原稿復号化（将来的に追加するときのため）	*/

/************************************************************************
*               BY:  T.Fukumoto
*             DATE:  1997/12/17
*             TYPE:  define
*      VAR TO HOLD:  ValidNoStoredNumberInput()
*      DESCRIPTION:  未登録が可能な固定長数値入力の戻り値
************************************************************************/
#define	OPR_NUMBER_INPUT_STOP	0xFF	/* 設定中止（ストップ/タイムアウト) */
#define	OPR_NUMBER_NO_STORED	0xFE	/* 未登録 							*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1998/01/07
*             TYPE:  define
*      VAR TO HOLD:  DisplayCipherProcess()
*      DESCRIPTION:  暗号化・復号化の進捗度表示の引数
************************************************************************/
#define	OPR_CIPHER_EXEC			0	/* 暗号化中	*/
#define	OPR_DECIPHER_EXEC		1	/* 復号化中	*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1998/03/12
*             TYPE:  define
*      VAR TO HOLD:  GetCursorPositionDataKind()
*      DESCRIPTION:  カーソル位置データ種別獲得関数の戻り値
************************************************************************/
#if (PRO_DIAL_NAME_DISP == ENABLE) || (PRO_NEW_DIAL_OPR == ENABLE)
#define	OPR_CURSOR_DATA_NONE	0x00	/* データが未入力						*/
#define	OPR_CURSOR_DIRECT_DIAL	0x01	/* カーソル位置のデータが直接ダイヤル	*/
#define	OPR_CURSOR_ONETOUCH		0x02	/*           〃          ワンタッチ		*/
#define	OPR_CURSOR_SPEED		0x04	/*           〃          短縮			*/
#define	OPR_CURSOR_GROUP		0x08	/*           〃          グループ		*/
#define	OPR_CURSOR_INVALID_DATA	0x10	/* 無効なデータ（ダイヤル記号のみ）		*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/13 by K.Okada */
#define	OPR_CURSOR_DIRECT_ADDRESS	0x20	/* カーソル位置のデータが直接メールアドレス */
#endif
#endif

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/31 Y.Matsukuma */
/************************************************************************
*               BY:  Y.Matsukuma
*             DATE:  1998/08/31
*             TYPE:  define
*      DESCRIPTION:  ミノルタテストプリントの種類
************************************************************************/
#define	OPR_MINOLTA_FLASH			0	/* インターバルタイム無 */
#define	OPR_MINOLTA_HOLD			1	/* インターバルタイム有 */
#define	OPR_MINOLTA_ONETOUCH		2	/* ワンタッチ */
#define	OPR_MINOLTA_PROGRAM			3	/* プログラムワンタッチ */
#endif

#if (PRO_MODEM == R288F)	/* Add By H.Fujimura 1998/12/28 */
/************************************************************************
*               BY:  H.Fujimura
*             DATE:  1998/12/28
*             TYPE:  define
*      VAR TO HOLD:  SYS_FactoryOptModemData.Kind
*      DESCRIPTION:  回線テスト・テスト項目種別
************************************************************************/
	#define MDM_RELAY_CML_ON			0				/* CML */
	#define MDM_RELAY_CML_OFF			1
	#define MDM_RELAY_H_ON				2				/* H */
	#define MDM_RELAY_H_OFF				3
	#define MDM_RELAY_L_ON				4				/* L */
	#define MDM_RELAY_L_OFF				5
	#define MDM_RELAY_S_ON				6				/* S */
	#define MDM_RELAY_S_OFF				7
	#define MDM_RELAY_MODEM_ON			8				/* S */
	#define MDM_RELAY_MODEM_OFF			9
	#define MDM_RELAY_CONT24_ON			10				/* CONT24 */
	#define MDM_RELAY_CONT24_OFF		11
	#define MDM_RELAY_TONE_ON			12				/* CONT24 */
	#define MDM_RELAY_TONE_OFF			13
	#define MDM_RELAY_BZ_ON				14				/* CONT24 */
	#define MDM_RELAY_BZ_OFF			15
	#define MDM_RELAY_RI_ON				16				/* RI(GK) */
	#define MDM_RELAY_RI_OFF			17
	#define MDM_RELAY_PHONE2_ON			18				/* RI(GK) */
	#define MDM_RELAY_PHONE2_OFF		19
	#define MDM_RELAY_DP_ON				20				/* DP added by H.Hirao 1999/02/02 */
	#define MDM_RELAY_DP_OFF			21
#endif

#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
/*********************************************
 * 予約確認オペレーション状態
 *********************************************/
#define	OPR_COMMAND_REVIEW_WAIT		0	/* 予約確認			*/
#define	OPR_COMMUNICATION_RESULT	1	/* 通信結果表示		*/
/*#define	OPR_RESCHEDULE_COMMAND	2	*//* リスケジュール	*/
#define	OPR_COMMAND_CONTINUE		3	/* 予約確認続行		*/
#define	OPR_COMMAND_END				4	/* 予約確認終了		*/
/*#define	OPR_COMMAND_BACK		5	*//* 予約確認戻る		*/

/************************************************************************
*               BY:  N.Kondo
*             DATE:  2001/09/21
*             TYPE:  define
*      DESCRIPTION:  予約確認コマンド有り無し
************************************************************************/
/*#define	OPR_NO_COMMAND			0*/		/* コマンドなし	*/
/*#define	OPR_COMMAND				1*/		/* コマンドあり	*/

#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) || defined(HINOKI3)	/* Added by SMuratec K.W.Q 2003/09/02 */ /* Add by Y.Kano 2004/12/21 */
#define OPR_BELLRING_TEST				0x01	/*　擬似ベル鳴動　*/
#define OPR_HOLDMELODY_TEST				0x02	/*　保留メロデイー　*/
#define OPR_ALLCLEAR_TEST				0x03	/*　オールクリア　*/
#define OPR_DRAM_TEST					0x04	/*　標準ＤＲＡＭ　*/
#define OPR_SRAM_TEST					0x05	/*　ＳＤＡＭ　*/
#define OPR_TESTPATTERNPRINT_TEST		0x06	/*　テストパダーン印字　*/
#define OPR_LISTPRINT_TEST				0x07	/*　リストプリント印字　*/
#define OPR_SHADING_TEST				0x08	/*　シューデイング　*/
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Add by Y.Kano 2003/10/17 */
/***********************************************************************
*          BY:   Y.kano
*        DATE:   2003/10/17
*        TYPE:   DEFINE
* VAR TO HOLD:   UBYTE Volumue
* DESCRIPTION:   PS2 Volumue Adjust
************************************************************************/
#define VOLUMUE_0		0x00	/* PS2右矢印１ケ表示 		*/
#define VOLUMUE_1		0x01	/* PS2左矢印１ケ表示 		*/
#define VOLUMUE_2		0x02	/* PS2左矢印２ケ表示 		*/
#define VOLUMUE_3		0x03	/* PS2左矢印３ケ表示 		*/
#define VOLUMUE_OK		0x04	/* PS2ボリューム設定ＯＫ 	*/
#endif

#endif	/* #ifndef OPR_DEF_H */
