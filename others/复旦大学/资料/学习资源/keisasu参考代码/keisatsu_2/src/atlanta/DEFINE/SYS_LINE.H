#ifndef sys_line_h
	#define	sys_line_h
/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Apr.5,1996
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_OptionLineStatus[0-7];
* DESCRIPTION:   ﾏｼｰﾝ･ｽﾃｰﾀｽ
************************************************************************/
#define		SYS_OPTION_LINE_EXIST		0x0001	/* SET:オプション・ボード有りCLEAR: オプション・ボード無し */
#define		SYS_OPTION_SPEED_MAX_288	0x0002	/* SET：Ｒ２８．８ＫCLEAR:１４．４Ｋ */
#define		SYS_OPTION_PRE_LINE_BUSY	0x0004	/* SET:ＣＩ検出中CLEAR:ＣＩを検出していない */
#define		SYS_OPTION_LINE_BUSY		0x0008	/* SET:回線使用中CLEAR:回線未使用 */
#define		SYS_OPTION_STOP_FAXCOM		0x0010	/* SET:通信停止要求有りCLEAR:通信停止要求無し */
#define		SYS_OPTION_LINE_ERROR		0x0020	/* SET:接続ボード異常有りCLEAR:異常無し */
#define		SYS_OPTION_LINE_VALID		0x0040	/* SET:オプション・ボードして有効 CLEAR:オプション・ボードとして無効 */
#define		SYS_OPTION_TELEPHONE_UES	0x0080	/* SET:受話器使用中 1997/01/21 By N.Sakamoto */
#define		SYS_OPTION_FAXMODEM			0x0100	/* D65B-010 オプションモデムでＣｌａｓｓ1実行中 By Y.Matsukuma 1997/06/23 */
#define		SYS_OPTION_REAL_LINE_BUSY	0x0200	/* SET:通信起動中 CLEAR:まだ通信起動されてない 1997/10/09 Y.Murata */
/*	#define		未定義					0x0400	*/
/*	#define		未定義					0x0800	*/
/*	#define		未定義					0x1000	*/
/*	#define		未定義					0x2000	*/
/*	#define		未定義					0x4000	*/
/*	#define		未定義					0x8000	*/

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/28 */
/***********************************************************************
*          BY:   SMuratec 李
*        DATE:   Apr.5,1996
*        TYPE:   DEFINE
* VAR TO HOLD:   UBYTE	SYS_LineTelStatus;
* DESCRIPTION:   ２回線秘話機能用
************************************************************************/
 #if 0 /* 警察FAX (ナンバーディスプレイ) Modified by SMuratec 李 2005/11/05 */
@@#define		SYS_STD_LINE_STATUS			0x0F	/* 標準回線の秘話使用状態 */
@@ #define STD_READY			0X00	/* 秘話機能起動しない */
@@ #define STD_USED_IN_HDST	0X01	/* ハンドセット使用中 */
@@ #define STD_USED_IN_EXT	0X02	/* 外付け電話使用中 */
@@
@@#define		SYS_EXT_LINE_STATUS			0xF0	/* 拡張回線の秘話使用状態 */
@@ #define EXT_READY			0X00	/* 秘話機能起動しない */
@@ #define EXT_USED_IN_HDST	0X10	/* ハンドセット使用中 */
@@ #define EXT_USED_IN_EXT	0X20	/* 外付け電話使用中 */
#else /* #if 0 */
#define		SYS_STD_LINE_STATUS			0x07	/* 標準回線の秘話使用状態 */
 #define STD_READY			0X00	/* 秘話機能起動しない */
 #define STD_USED_IN_HDST	0X01	/* ハンドセット使用中 */
 #define STD_USED_IN_EXT	0X02	/* 外付け電話使用中 */

#define STD_TEL2_OFFHOOK	0X08	/* 標準回線の外付電話OFFHOOK状態 */	

#define		SYS_EXT_LINE_STATUS			0x70	/* 拡張回線の秘話使用状態 */
 #define EXT_READY			0X00	/* 秘話機能起動しない */
 #define EXT_USED_IN_HDST	0X10	/* ハンドセット使用中 */
 #define EXT_USED_IN_EXT	0X20	/* 外付け電話使用中 */
 
#define EXT_TEL2_OFFHOOK		0X80	/* 拡張回線の外付電話OFFHOOK状態 */	
#endif

/***********************************************************************
*          BY:   SMuratec 李
*        DATE:   2005/10/20
*        TYPE:   DEFINE
* VAR TO HOLD:   UBYTE	SYS_LineNDStatus;
* DESCRIPTION:   ２回線ナンバーディスプレイ機能用
************************************************************************/
 #define ND_READY			0X00	/* ナンバーディスプレイ機能起動しない */
 #define ND_USED_IN_STD		0X01	/* 標準回線ナンバーディスプレイ機能実行中 */
 #define ND_USED_IN_EXT		0X02	/* 拡張回線ナンバーディスプレイ機能実行中 */

#endif /* defined (KEISATSU) */

#endif
