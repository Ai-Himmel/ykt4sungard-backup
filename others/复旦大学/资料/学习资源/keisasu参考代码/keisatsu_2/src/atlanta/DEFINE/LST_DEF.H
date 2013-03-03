/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_DEF.H
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef	LST_DEF_H
	#define	LST_DEF_H	1

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysdoc.h" /* 追加 石橋 94/07/19 */

/************************************************************************
 * リストプリント余白の設定												*
 * 1996/12/10															*
 * 小谷正樹																*
 ************************************************************************/
#define	LST_LEFT_WHITE_A4	14	/*左余白A4 単位はｍｍ*/	/* 48->14 */
#define	LST_LEFT_WHITE_B4	24	/*左余白B4 単位はｍｍ*/	/* 48->24 */
#define	LST_LEFT_WHITE_A3	34	/*左余白B4 単位はｍｍ*/	/* 48->34 */

#if (PRO_PRINT_TYPE == LED)
	#define	LST_LEFT_WHITE_100	48	/*左余白プリンタヘッドから 単位は４ｍｍ*/
	#define	LST_LEFT_WHITE_75	68	/*左余白プリンタヘッドから 単位は４ｍｍ*/
	#define	LST_LEFT_WHITE_50	88	/*左余白プリンタヘッドから 単位は４ｍｍ*/
#endif

#define	LST_COLUM		81		/* リストプリント用バッファ (80+1→81 石橋 94/07/19) */

#if defined(STOCKHM2)		/* DVT: Modify by SMuratec K.W.Q 2004/11/03 */
 #define LST_BYTE_SIZE	216		/*ﾌﾟﾘﾝﾀｰﾊｰﾄﾞの1ﾗｲﾝﾄﾞｯﾄ数／8*/
#else
 #define LST_BYTE_SIZE	256		/*ﾌﾟﾘﾝﾀｰﾊｰﾄﾞの1ﾗｲﾝﾄﾞｯﾄ数／8*/
#endif						/* End of (defined (STOCKHM2)) */

#define	LST_IMAGE		(LST_BYTE_SIZE+8)	/* テストプリント用バッファ(括弧追加 石橋 94/08/20 掛け算に使う対策) */

#if 0
**#define	LST_FONT_X		8		/*ﾌｫﾝﾄの横ﾄﾞｯﾄ数*/
**#define	LST_FONT_Y		16		/*ﾌｫﾝﾄの縦ﾄﾞｯﾄ数*/
#endif

/* リスト行数(100%) */
#define	LST_A4_LEN		68				/*A4用紙の行数*/
#define	LST_LETTER_LEN	(LST_A4_LEN-4)	/*ﾚﾀｰ用紙の行数*/
#define	LST_B4_LEN		(LST_A4_LEN+16)	/*B4用紙の行数*/
#define	LST_LEGAL_LEN	(LST_A4_LEN+14)	/*ﾘｰｶﾞﾙ用紙の行数*/
#define	LST_A3_LEN		98				/*A3用紙の行数*/
#define	LST_A5_LEN		31				/*A5用紙の行数*/
#define	LST_B5_LEN		39				/*B5用紙の行数*/
#define	LST_A4R_LEN		46				/*A4R用紙の行数*/
/*#define	LST_A5R_LEN		34				/*A5R用紙の行数*/
#define	LST_A5R_LEN		32				/*A5R用紙の行数*//* 97/10/16 By M.Kuwahara */
/*#define	LST_B5R_LEN		42				/*B5R用紙の行数*/
#define	LST_B5R_LEN		40				/*B5R用紙の行数*//* 97/10/16 By M.Kuwahara */

/* リスト行数(75%) */
#define	LST_A4_LEN_75		91		/*A4用紙の行数*/
#define	LST_LETTER_LEN_75	85		/*ﾚﾀｰ用紙の行数*/
#define	LST_B4_LEN_75		112		/*B4用紙の行数*/
#define	LST_LEGAL_LEN_75	110		/*ﾘｰｶﾞﾙ用紙の行数*/
#define	LST_A3_LEN_75		130		/*A3用紙の行数*/
#define	LST_A5_LEN_75		43		/*A5用紙の行数*/
#define	LST_B5_LEN_75		54		/*B5用紙の行数*/
#define	LST_A4R_LEN_75		63		/*A4R用紙の行数*/
#define	LST_A5R_LEN_75		45		/*A5R用紙の行数*/
#define	LST_B5R_LEN_75		56		/*B5R用紙の行数*/

/*機器設定有効／無効*/
#if 0
**	#define	LST_M_ON			1		/*有効*/
**	#define	LST_M_OFF			0		/*無効*/
#endif
/*ﾜﾝﾀｯﾁｷｰ*/

/*ｻｰﾁ方法*/
#define	LST_SEARCH_NUMBER	0		/*番号順のｻｰﾁ*/
#define	LST_SEARCH_ASCII	1		/*名称ｱｽｷｰ順ｻｰﾁ*/

/*文字列比較*/
#define	LST_LT			0		/*String1 <	 String2*/
#define	LST_EQ			1		/*String1 == String2*/
#define	LST_GT			2		/*String1 >	 String2*/

/*ｱｽｷｰ順ｿｰﾄの比較文字数*/
#define	LST_COMP_LEN	16

/*ECM*/
#define	LST_ECM			0xC000	/*ECM bit CIPHER bit*/
/*ﾊﾟﾀｰﾝﾌﾟﾘﾝﾄ*/
#define	LST_IMG_Y_KK1	100		/*紙かすの1ﾊﾟﾀｰﾝ毎の印刷縦ﾄﾞｯﾄ数*/
#define	LST_KK_LINE_1	16		/*紙かすﾊﾟﾀｰﾝ縦線位置１（ｷｬﾗｸﾀ）*/
#define	LST_KK_LINE_2	188		/*紙かすﾊﾟﾀｰﾝ縦線位置２（ｷｬﾗｸﾀ）*/

/* 印刷／文字列作成の両方が必要な帳票の実行ﾓｰﾄﾞ*/
#define	LST_MODE_PRINT	0		/*印刷*/
#define	LST_MODE_LINE	1		/*１行作成*/

/*送受信区分*/
#define	LST_TX			0		/*送信*/
#define	LST_RX			1		/*受信*/

/*ｶﾝﾏ位置*/
#define	LST_COMMA_STR_BACK	0	/*ｶﾝﾏ位置(文字列の後)*/
#define	LST_COMMA_STR_FRONT	1	/*ｶﾝﾏ位置(文字列の前)*/

/*ｸﾞﾙｰﾌﾟﾘｽﾄ*/
#define	GROUP_END		0xff	/*ｸﾞﾙｰﾌﾟﾘｽﾄ ｻｰﾁのｴﾝﾄﾞ*/
#define	LST_SPEED		0		/*ｽﾋﾟｰﾄﾞﾀﾞｲﾔﾙ*/
#define	LST_ONETOUCH	1		/*ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ*/

/* ｵﾝﾗｲﾝ ﾓﾆﾀｰ */
/*#define	LST_DUMP_DATA	16	*/	/*ｵﾝﾗｲﾝ ﾓﾆﾀｰの１行に印刷するﾃﾞｰﾀ数*/

/* T30 */
/* #define	LST_FRAME_N_MAX		35		通常ﾌﾚｰﾑ数*/
#define	LST_FRAME_N_MAX		41		/*通常ﾌﾚｰﾑ数*/
#define	LST_T30_DATA_FLD	18		/*T30１行当りのﾃﾞｰﾀ印刷数*/

/* ERROR CODE */
#define	LST_ERR_CODE_MAX	40		/*error code max*/

#define	LST_TCF_PIX		0		/*TCF ro PTX*/
#define	LST_FAX_CTRL	1		/*Fax Control Field*/

/*#define	LST_PRM_SPACE	6		@* 機器設定リストの行間隔を何ドットにするか？For ANZU By H.Hirao Feb 27,1996 */
#define	LST_PRM_SPACE	4		/* 機器設定リストの行間隔を何ドットにするか？For ANZU By H.Hirao Feb 27,1996 */

/* T30 SPEED */
#define	LST_T30_SPEED		0x3c	/*00 1111 00*/	/*1*/
#define	LST_2400BPS_V27		0x00	/*00 0000 00*/	/*1*/
#define	LST_4800BPS_V27		0x08	/*00 0010 00*/	/*1*/
#define	LST_9600BPS_V29		0x04	/*00 0001 00*/	/*1*/
#define	LST_7200BPS_V29		0x0c	/*00 0011 00*/	/*1*/
#define	LST_14400BPS_V33	0x10	/*00 0100 00*/	/*1*/
#define	LST_12000BPS_V33	0x18	/*00 0110 00*/	/*1*/
#define	LST_14400BPS_V17	0x20	/*00 1000 00*/	/*1*/
#define	LST_12000BPS_V17	0x28	/*00 1010 00*/	/*1*/
#define	LST_9600BPS_V17		0x24	/*00 1001 00*/	/*1*/
#define	LST_7200BPS_V17		0x2c	/*00 1011 00*/	/*1*/
#define	LST_V27_FB			0x00	/*00 0000 00*/	/*1*/
#define	LST_V27				0x08	/*00 0010 00*/	/*1*/
#define	LST_V29				0x04	/*00 0001 00*/	/*1*/
#define	LST_V29_PLUS		0x0c	/*00 0011 00*/	/*1*/
#define	LST_V33_PLUS		0x1c	/*00 0111 00*/	/*1*/
#define	LST_V17_PLUS		0x2c	/*00 1011 00*/	/*1*/
/* T30 2次元符号化能力 */
#define	LST_T30_CODING		0x40	/*01000000*/	/*3*/
#define	LST_T30_TWO_DMS		0x80	/*10000000*/	/*1*/
#define	LST_T30_JBIG		0x20	/*00100000*/	/*9*/
/* t30 記録幅能力 */
#define	LST_T30_WIDTH		0x01	/*00000001*/	/*4*/
#define	LST_T30_WIDTH1		0x1e	/*000 1111 0*/	/*4*/
#define	LST_RW_A5_1216		0x02	/*000 0001 0*/	/*4*/
#define	LST_RW_A6_864		0x04	/*000 0010 0*/	/*4*/
#define	LST_RW_A5_1728		0x08	/*000 0100 0*/	/*4*/
#define	LST_RW_A6_1728		0x10	/*000 1000 0*/	/*4*/
#define	LST_T30_WIDTH2		0x03	/*000000 11*/	/*2*/
#define	LST_RW_A4			0x00	/*000000 00*/	/*2*/
#define	LST_RW_B4			0x01	/*000000 01*/	/*2*/
#define	LST_RW_A3			0x02	/*000000 10*/	/*2*/
/* T30 最小走査時間能力 */
#define	LST_T30_TIME		0x70	/*0 111 0000*/	/*2*/
#define	LST_20MS			0x00	/*0 000 0000*/	/*2*/
#define	LST_40MS			0x40	/*0 100 0000*/	/*2*/
#define	LST_10MS			0x20	/*0 010 0000*/	/*2*/
#define	LST_5MS				0x10	/*0 001 0000*/	/*2*/
#define	LST_10MS_H			0x60	/*0 110 0000*/	/*2*/
#define	LST_20MS_H			0x30	/*0 011 0000*/	/*2*/
#define	LST_40MS_H			0x50	/*0 101 0000*/	/*2*/
#define	LST_0MS				0x70	/*0 111 0000*/	/*2*/
/* T30 解像度 */
#define	LST_T30_HFINE		0x04	/*00000100*/	/*5*/
#define	LST_T30_SFINE		0x01	/*00000001*/	/*5*/
#define	LST_T30_FINE		0x40	/*01000000*/	/*1*/
/* T30 誤り訂正方式 */
#define	LST_T30_PARITY		0x04	/*00000100*/	/*3*/

/*END MARK*/
#define	NULL_PT			'\x0'	/*ﾇﾙ ﾎﾟｲﾝﾀｰ*/
#define	LST_CR			'\x0D'	/*ｷｬﾘｯｼﾞﾘﾀｰﾝ*/
#define	LST_LF			'\x0A'	/*ﾗｲﾝﾌｨｰﾄﾞ*/
#define	LST_EOT			'\x04'	/*ｴﾝﾄﾞ ｵﾌﾞ ﾃｷｽﾄﾞ*/

#define	LST_GROUP_BIT	32		/*ｸﾞﾙｰﾌﾟのﾋﾞｯﾄ数*/

/*名称種類*/
#define	LST_NAME_1		0		/*名称１（備考）*/
#define	LST_NAME_2		1		/*名称２（応用機能）*/

/*名称形式*/
#define	LST_NAME_LONG	0		/*ﾌﾙ名称*/
#define	LST_NAME_SHORT	1		/*略式名称*/

/*通信結果文字特殊処理*/
#define	LST_RESULT_TX_CONF	0	/*送信証専用形式*/
#define	LST_RESULT_COMMON	1	/*普通形式*/
#define	LST_JOURNAL_TX		3	/*送信ジャーナル形式*/
#define	LST_JOURNAL_RX		4	/*受信ジャーナル形式*/

/*積算分編集方法*/
#define	LST_YYMMDD		0		/* 年月日週	*/
#define	LST_DDHHMM		1		/* 日時分	*/
#define	LST_MMDDHHMM	2		/* 月日時分	*/
#if (PRO_OKI == ENABLE)	/* 沖ヨーロッパ仕様では、月／日を日／月に変更します by K.Watanabe 1998/10/13 */
#define	LST_DDMMHHMM	3		/* 日月時分	*/
#endif
								/* 西暦４桁対応 bythonda1999/11/16	*/
								/* ICHOUから移植してきました		*/
#define LST_YYYYMMDDHHMM1 4     /*年月日時分 "YYYY/MM/DD,HH:MM" 	*/
#define LST_YYYYMMDDHHMM2 5     /*年月日時分 "YYYY/MM/DD HH:MM" 	*/

#if defined(STOCKHM2)
#define LST_MMDDHHMM1   6		/* 月日時分 OPR用*//* Add by SMuratec C.P 2004/06/10 */
#define LST_MMDDHHMM2   7		/* 月日時分 LST用*//* Add by SMuratec C.P 2004/06/10 */
#endif

	/*#define	PRINT_TCR		1		*//*TCRfile[TxJournalPoint] By S.K */
	/*#define	PRINT_TCR_NOT	0		*//*TCRfile[TxJournalPoint]*/
#define	LST_DIAL_NOT	0xFF	/*SpeedDialData短縮ﾀﾞｲﾔﾙ未登録*/
#define	LST_SUBDIAL_NOT	0xFF	/*転送先ﾀﾞｲﾔﾙ未登録*/

/*flag ON OFF*/
#define	ON				1
#define	OFF				0

/*ｷｬﾗｸﾀﾌﾟﾘﾝﾄ関数*/
#define	LST_PRE_OPEN	0x00	/*プリOPEN*/
#define	LST_OPEN		0x10	/*プリントOPEN*/
#define	LST_PRINT		0x20	/*プリントRUN*/
#define	LST_LINE_FEED	0x30	/*改行*/
#define	LST_IMAGE_PRINT	0x40	/*イメージプリントRUN*/
#define	LST_CLOSE		0x50	/*プリントCLOSE*/
#define	LST_PRE_CLOSE	0x60	/*プリCLOSE*/
/* 以下、ソースを簡潔にするために桐用としてモード追加 94/08/24 石橋正和 */
#define LST_PRINT_ERR_CLOSE_NOT			0x80	/* プリントRUN(ｴﾗｰが発生してもcloseしない) */
#define LST_LINE_FEED_ERR_CLOSE_NOT		0x90	/* 改行(ｴﾗｰが発生してもcloseしない) */

/*ｷｬﾗｸﾀﾌﾟﾘﾝﾄ関数 error処理*/
#define	LST_ERR_CLOSE_NOT	0x08	/*CPrint時、ｴﾗｰが発生してもcloseしない*/
#define	LST_ERR_CLOSE		0x00	/*CPrint時、ｴﾗｰが発生したらcloseする*/

/*数値文字列処理*/
#if 0
**#define	LST_FRONT_ZERO	0		/*前ｾﾞﾛ埋め*/
**#define	LST_FRONT_SPACE	1		/*前ｽﾍﾟｰｽ埋め*/
**#define	LST_FRONT_DEL	2		/*前ｽﾍﾟｰｽ削除*/
#endif

/*年月、曜日*/
#if (0)	/* 97/05/15 M.Kuwahara */
#define	LST_A_NICHI		0xf0	/*ANK '日'*/
#define	LST_A_GETU		0xf1	/*ANK '月'*/
#define	LST_A_KA		0xf2	/*ANK '火'*/
#define	LST_A_SUI		0xf3	/*ANK '水'*/
#define	LST_A_MOKU		0xf4	/*ANK '木'*/
#define	LST_A_KIN		0xf5	/*ANK '金'*/
#define	LST_A_DOU		0xf6	/*ANK '土'*/
#define	LST_A_NEN		0xf7	/*ANK '年'*/
#endif
#define	LST_A_NICHI		0x08	/*ANK '日'*/
#define	LST_A_GETU		0x09	/*ANK '月'*/
#define	LST_A_KA		0x0A	/*ANK '火'*/
#define	LST_A_SUI		0x0B	/*ANK '水'*/
#define	LST_A_MOKU		0x0C	/*ANK '木'*/
#define	LST_A_KIN		0x0D	/*ANK '金'*/
#define	LST_A_DOU		0x0E	/*ANK '土'*/
#define	LST_A_NEN		0x0F	/*ANK '年'*/

/*特殊文字*/
#define	LST_A_TENTEN	0x10	/*ANK '‥'*/

/*修飾*/
#if 0
**#define	LST_ANK			0x00	/*修飾ANK*/
**#define	LST_KANJI		0x01	/*修飾漢字*/
**#define	LST_TWICE		0x02	/*修飾横倍角*/
**#define	LST_MESH		0x04	/*修飾網掛け*/
**#define	LST_INVERT		0x08	/*修飾反転*/
#endif

/*罫線（テンキーに線が引かれているものとして、番号を付ってある）*/
#define	LST_KLINE11		0x13	/*・*/		/* ﾗｲﾝ追加 97/09/24 Add By M.Kuwahara */
#define	LST_KLINE10		0x14	/*・*/		/* ﾗｲﾝ追加 97/09/19 Add By M.Kuwahara */
#define	LST_KLINE7		0x15	/*・*/
#define	LST_KLINE4		0x16	/*・*/
#define	LST_KLINE1		0x17	/*・*/
#define	LST_KLINE_		0x18	/*・*/
#define	LST_KLINE8		0x19	/*・*/
#define	LST_KLINE5		0x1a	/*・*/
#define	LST_KLINE2		0x1b	/*・*/
#define	LST_KLINE9		0x1c	/*・*/
#define	LST_KLINE6		0x1d	/*・*/
#define	LST_KLINE3		0x1e	/*・*/
#define	LST_KLINEI		0x1f	/*・*/

/*文字修飾の種類*/
#define	LST_NOT			0x30	/*修飾なし*/
#define	LST_XXX_XXX_KAN	0x31	/*漢字*/
#define	LST_XXX_TWI_XXX	0x32	/*横倍角*/
#define	LST_XXX_TWI_KAN	0x33	/*横倍角＋漢字*/
#define	LST_MES_XXX_XXX	0x34	/*網掛*/
#define	LST_MES_XXX_KAN	0x35	/*網掛＋漢字*/
#define	LST_MES_TWI_XXX	0x36	/*網掛＋横倍角*/
#define	LST_MES_TWI_KAN	0x37	/*網掛＋横倍角＋漢字*/
#define	LST_INV_XXX_XXX	0x38	/*反転*/
#define	LST_INV_XXX_KAN	0x39	/*反転＋漢字*/
#define	LST_INV_TWI_XXX	0x3A	/*反転＋横倍角*/
#define	LST_INV_TWI_KAN	0x3B	/*反転＋横倍角＋漢字*/

#define	LST_DATE_HOUR_MINUTE	0	/* 日時分形式 */
#define	LST_HOUR_MINUTE			1	/* 時分形式 */

/*とりあえずここにいれている*/
#define	CVR_LINES					18	 /* ｶﾊﾞｰﾍﾟｰｼﾞﾌﾟﾘﾝﾄ			*/
#define	RCR_LINES					22	 /* RECEIVE CONF.REPORT		*/
#define	REMOTE_MEMORY_OVER_LINES	11	 /* Remote Fax Memory Over	*/
#define	REPORT_TT_LINES				5	 /* 不達通知のタイトル部	*/	/* 竹内 Feb.16.1995 */	/* 6→5 「日時」削除 Mar.17.1995 */
#define	REPORT_MSG_LINES			5	 /* 不達通知のメッセージ部	*/	/* 竹内 Feb.16.1995 */

/*とりあえずここにいれている*/
#define		AUTO_PRINT_OFF		0	/* 自動出力OFF */
#define		AUTO_PRINT_ON		1	/* 自動出力ON  */

/*-----------------------------------------------------------------*/
/* 機器設定リスト用定義 	　97/06/27	by M.Kuwahara	 　　	 　*/
/*-----------------------------------------------------------------*/
#define	LST_PRM_TTI_ID				1		/* 発信元名					*/
#define	LST_PRM_SECUREDOCHOLD		2		/* 親展受信記憶期間			*/
#define	LST_PRM_JOURNALAUTOPRT		3		/* 通信管理記録自動			*/
#define	LST_PRM_CONFREPORT			4		/* 通信証					*/
#define	LST_PRM_PHONETYPE			5		/* 通信回線					*/
#define	LST_PRM_TXRXTYPE			6		/* 送信・受信				*//*  By O.Kimoto 1997/07/09 */
#define	LST_PRM_LINETYPE			7		/* 回線タイプ				*//*  By O.Kimoto 1997/07/09 */
#define	LST_PRM_RECEIVEMODE			8		/* 受信ﾓｰﾄﾞ					*/
#define	LST_PRM_SCANNERWIDTH		9		/* 読取ｻｲｽﾞ					*/
#define	LST_PRM_PRIMARYMODE			10		/* 優先文字ｻｲｽﾞ				*/
#define	LST_PRM_CONTRAST			11		/* 優先原稿濃度				*/
#define	LST_PRM_REDUCTIONRATE		12		/* ﾌﾟﾘﾝﾄ縮小率				*/
#define	LST_PRM_ROTATEMARGIN		13		/* 回転ﾏｰｼﾞﾝ				*//*  By O.Kimoto 1997/07/09 */
#define	LST_PRM_PAGECOMPOUND		14		/* ﾍﾟｰｼﾞ合成				*/
#define	LST_PRM_DIALINGPAUSE		15		/* ﾎﾟｰｽﾞ時間				*/
#define	LST_PRM_RINGGINGTIMES		16		/* 呼出ﾍﾞﾙ回数				*/
#define	LST_PRM_REDIALTIMES			17		/* ﾘﾀﾞｲﾔﾙ回数				*/
#define	LST_PRM_ECMMODE				18		/* ECMﾓｰﾄﾞ					*/
#define	LST_PRM_PASSCODE			19		/* ﾊﾟｽｺｰﾄﾞ					*/
#define	LST_PRM_CLOSEDNETWORK		20		/* 閉域通信					*/
#define	LST_PRM_SECURITYTX			21		/* ﾊﾟｽﾜｰﾄﾞ送信				*/
#define	LST_PRM_BLOCKJUNKFAX		22		/* ﾀﾞｲﾚｸﾄﾒｰﾙ				*/
#define	LST_PRM_REMOTEDIAGNOSTIC	23		/* ﾘﾓｰﾄ診断					*/
#define	LST_PRM_MEMORYTX			24		/* ﾒﾓﾘ送信					*/
#define	LST_PRM_STAMP				25		/* 済ｽﾀﾝﾌﾟ					*/
#define	LST_PRM_RS232C				26		/* RS232C					*/
#define	LST_PRM_DIALIN				27		/* ﾀﾞｲﾔﾙｲﾝ					*/
#define	LST_PRM_OPERATIONPROTECT	28		/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ			*/
#define	LST_PRM_MESAGETRANS			29		/* ﾒｯｾｰｼﾞ送信				*/
#define	LST_PRM_SILENTOPERATION		30		/* ｻｲﾚﾝﾄｵﾍﾟﾚｰｼｮﾝ			*/
#define	LST_PRM_COPYREDUCTION		31		/* ｺﾋﾟｰ縮小率				*/
#define	LST_PRM_PAPERSIZE			32		/* 記録紙ﾍﾟｰﾊﾟｰｻｲｽﾞ			*/
#define	LST_PRM_DEPARTMENT			33		/* 部門管理ｾｯﾄ				*/
#define	LST_PRM_DEPARTMENTPROTECT	34		/* 部門管理ﾌﾟﾛﾃｸﾄ			*/
#define	LST_PRM_REMOTESECURITYRX	35		/* ｾｷｭﾘﾃｨ受信				*/
#define	LST_PRM_PIN_ACCESSMODE		36		/* PINｱｸｾｽ					*/
#define	LST_PRM_DAYLIGHTSAVING		37		/* 夏時間自動切換え			*/
#define	LST_PRM_RINGMASTR			38		/* ﾘﾝｸﾞﾏｽﾀｾｯﾄ				*/
#define	LST_PRM_MERCURYPAUSE		39		/* ﾏｰｷｭﾘｰﾎﾟｰｽﾞ				*/
#define	LST_PRM_RXALARM				40		/* 受信完了ｱﾗｰﾑ				*/
#define	LST_PRM_COMPAGES			41		/* 枚数						*/
#define LST_PRM_COPYPROTECT			42		/* ｺﾋﾟｰ禁止					*/
#define LST_PRM_HOLDMELODY			43		/* 保留ﾒﾛﾃﾞｨｰ				*/	/* 追加 97/11/07 T.Fukumoto */
#define LST_PRM_SORTCOPY			44		/* ｿｰﾃｨﾝｸﾞｺﾋﾟｰ				*/	/* 追加 97/11/13 T.Fukumoto */
#define LST_PRM_RELAYED_RELAY_TX	45		/* 中々継					*/	/* Add By O.Kimoto 1998/03/02 */
#define LST_PRM_REMOTE_RX			46		/* リモート受信				*/	/* 追加 98/03/13 T.Fukumoto */
#define LST_PRM_ONHOOK_RX			47		/* オンフック受信			*/	/* 追加 98/03/13 T.Fukumoto */
#define	LST_PRM_PAPERTYPE			48		/* 記録紙ﾀｲﾌﾟ				*/	/* 1998/06/26 Add By M.Kuwahara */
#define	LST_PRM_WARP				49		/* ﾜｰﾌﾟ機能					*/	/* 1998/06/26 Add By M.Kuwahara */
#define	LST_PRM_NUMBERDISPLAY		50		/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ			*/	/* 1998/06/26 Add By M.Kuwahara */
#define	LST_PRM_MULTI_TTI_ID		51		/* 発信元名(ｶﾅID)			*/	/* Add By H.Fujimura 1999/01/07 */
#define	LST_PRM_ND_WARP				52		/* ＮＤワープ				*/	/* Add By H.Fujimura 1999/01/07 */
#define LST_PRM_MERCURYNUMBER		53		/* ﾏｰｷｭﾘｰﾅﾝﾊﾞｰ  		    */  /* Added by SMuratec C.P 2004/07/08 for prefix */
#define LST_PRM_DIALTONE			54		/* ダイヤルトーン検出		*/	/* Add by Y.Kano 2004/12/08 */

#if defined(KEISATSU)	/* 警察ＦＡＸ対応 Added by SMuratec 夏 2005/07/21 */
#define LST_PRM_PHONETYPE_EXT		55		/* 拡張回線の通信回線	上記 5  番目「通信回線」対応		*/
#define LST_PRM_RINGGINGTIMES_EXT	56		/* 拡張回線の呼出回数 	上記 16 番目「呼出ﾍﾞﾙ回数」対応		*/
#define LST_PRM_SETTING_LINE		57		/* 優先通信回線 ： 警電、加入、保持		*/
#define LST_PRM_SETTING_FAXMODE		58		/* 優先通信方式	： 一斉、個別、保持	*/
#define LST_PRM_SCRAMBLE_KEIDEN		59		/* 警電回線優先スクランブル */
#define LST_PRM_SCRAMBLE_KANYU		60		/* 加入回線優先スクランブル */
#define LST_PRM_REMOTE_NUM_ISSEI	61		/* 一斉通信の受信特番		*/
#define LST_PRM_REMOTE_NUM_KOBETSU	62		/* 個別通信の受信特番		*/
#define LST_PRM_DIALTONE_KEIDEN		63		/* 警電ダイヤルトーン検出	*/
#endif

/*-----------------------------------------------------------------*/
/* リストプリント用バッファ　　　　　　					 　　	 　*/
/*-----------------------------------------------------------------*/
union LstBuffer_t {
	  struct Code_t{
		  UBYTE Print[LST_COLUM];
		  UBYTE Attribute[LST_COLUM];
		  UBYTE Work[LST_COLUM];
	  } S;
	  UBYTE Image[LST_IMAGE];
};

/************************************************************************
*		   BY:	奥村明
*		 DATE:	1994/09/21
*		 TYPE:	DEFINE
* DESCRIPTION:	ジャーナル印刷種類
************************************************************************/
#if (PRO_CPU == SH7043)
	#define	LST_JRNL_HEAD	0
	#define	LST_JRNL_TX		1
	#define	LST_JRNL_RX		2
#endif

/************************************************************************
*		   BY:	石橋正和
*		 DATE:	1994/07/19
*		 TYPE:	DEFINE
* DESCRIPTION:	イメージ展開用バッファ(桐)
************************************************************************/
#if (PRO_PRINT_TYPE == LED)
	#if (PRO_PRINTER == DPI400)
		#define LST_WORD_WIDTH		256
	#endif
	#if (PRO_PRINTER == DPI200)
		#define LST_WORD_WIDTH		128
	#endif
#endif
#if (PRO_PRINT_TYPE == LASER)
	#if (PRO_PRINTER == DPI400)
		#define LST_A3_WORD_WIDTH	304
		#define LST_B4_WORD_WIDTH	256
		#define LST_A4_WORD_WIDTH	216
	#endif
	#if (PRO_PRINTER == DPI600)
		#define LST_A3_WORD_WIDTH	304	/*TBD*/
		#define LST_B4_WORD_WIDTH	256	/*TBD*/
		#define LST_A4_WORD_WIDTH	304
	#endif
	#define LST_WORD_WIDTH		304
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1998.9.2 K.Kawata*/
	#define LST_WORD_WIDTH		128
#endif

#if (PRO_PRINT_TYPE == THERMAL)	/* For HINOKI By O.Kimoto 1998/09/07 */
	#define LST_WORD_WIDTH		128
#endif
	#define LST_END_OF_PAGE		0x0F	/* イメージプリント中にページの最後まで印字した場合の
											返り値として */
	union FontImageBufferData_t {
		UBYTE	Font[3][16][80];				/* リストプリント用フォント展開イメージ */
												/* [0]&[1]=CharaterPrint [2]=CharacterTx */
		UWORD	Image[4][LST_WORD_WIDTH];		/* テストパターンプリント用 */
		UWORD	HeadImage[LST_WORD_WIDTH];		/**ﾃｽﾄﾊﾟﾀｰﾝﾌﾟﾘﾝﾄのﾍｯﾄﾞ用 (ANZU) H.Hirao Apr.04,1996 */
		UWORD	ByteImage[LST_PRM_SPACE][40];	/* 機器設定リスト用 (ANZU) H.Hirao Feb 27,1996 */
	};

/************************************************************************
*		   BY:	石橋正和
*		 DATE:	1994/06/02
*		 TYPE:	DEFINE
* DESCRIPTION:	キャラクタ送信用文字列バッファ(V53用)
************************************************************************/
#if (PRO_CPU == SH7043)
struct LST_CharacterTxData_t {
	UBYTE String[LST_COLUM];			/* 文字列 */
	UBYTE Attribute[LST_COLUM];			/* アトリビュート */
};
#endif

/************************************************************************
*		   BY:	桑原美紀
*		 DATE:	1997/09/19
*		 TYPE:	DEFINE
* DESCRIPTION:	消耗品発注票、モデル名変換バッファ
					ソフトウェアバージョンより取得したタイプ名をＦＡＸモデル名に変換
************************************************************************/
#if defined(JPN) || defined(USA)
struct LST_ModelChange_t {
	UBYTE FromModel[6];			/* バージョン名 */
	UBYTE ToModel[12];			/* 変換後モデル名 */
};
#else	/* OKI Office 120対応の為、欧州仕様のToModel桁数を増やします。S.Fukui Jul.9,1998 */

struct LST_ModelChange_t {
	UBYTE FromModel[6];			/* バージョン名 */
	UBYTE ToModel[15];			/* 変換後モデル名 */
};
#endif

/*これはプリンタードライバーにあるべきだがｺﾝﾊﾟｲﾙを通す為とりあえずここにいれてある*/
#define			CHAR_PAGE_END	9	/*センサーページエンド*/


#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  竹内 Feb.14.1995 */
	/*	不達通知を作成する関数 Set_CommErr_ChkMsg() の引数に使用する	*/
	#define	REPORT_TITLE	1
	#define	REPORT_MESSAGE	2
#endif

#endif

/* 以下はＰＯＰＬＡＲ＿Ｈ用です。
** 適当な条件が見つからないのでＰＲＯ＿ＰＡＮＥＬ==ＫＡＮＪＩで
** 判断しておきます
** By O.Kimoto 1997/08/09
*/

#if ( PRO_PANEL == KANJI )
#define	LST_FUNC_CTRY_TABLE_SW		2		/*FunctionCountryTableSw配列数*/

#define	LST_S_ONETOUCH				0x01	/* (0) A ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ			0*/
#define	LST_S_SPEED					0x02	/* (1) B 短縮ﾀﾞｲﾔﾙ			0*/
#define	LST_S_PROG					0x04	/* (2) C ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ		0*/
#define	LST_S_POLLING				0x08	/* (3) D ﾎﾟｰﾘﾝｸﾞ			0*/
#define	LST_S_SECURE				0x10	/* (4) E 親展				0*/
#define	LST_S_COMMAND				0x20	/* (5) F 通信予約			0*/
#define	LST_S_JOURNAL				0x40	/* (6) G 通信管理			0*/
#define	LST_S_DATE					0x80	/* (7) H 時計ｾｯﾄ			0*/
#define	LST_S_TTI					0x01	/* (8) I 発信元				1*/
#define	LST_S_USER					0x02	/* (9) J 機器設定			1*/
#define	LST_S_GROUP					0x04	/*(10) K ｸﾞﾙｰﾌﾟﾘｽﾄ			1*/
#define	LST_S_MESSAGE				0x08	/*(11) L ﾒｯｾｰｼﾞ				1*/
#define	LST_S_COST					0x10	/*(12) M 料金管理			1*/
#define	LST_S_BATCHTX				0x20	/*(13) N 一括送信			1*/
#define	LST_S_MULTIPROG				0x40	/*(14) O ﾏﾙﾁﾌﾟﾛｸﾞﾗﾑ			1*/
#define	LST_S_DEPART				0x80	/*(15) P 部門管理			1*/

#define	LST_SET_FUNC_CTRY_TABLE_SW	5		/*SettingsFunctionCountryTableSw配列数*/

#define	LST_S_PHONETYPE				0x01	/* (0) J01 通信回線			0*/
#define	LST_S_COMMUNICATIONRESULT	0x02	/* (1) J02 通信証			0*/
#define	LST_S_SCANNERWIDTH			0x04	/* (2) J03 読取ｻｲｽﾞ			0*/
#define	LST_S_GRAYSCALE				0x08	/* (3) J04 写真				0*/
#define	LST_S_PRIMARYMODE			0x10	/* (4) J05 優先文字ｻｲｽﾞ		0*/
#define	LST_S_CONTRAST				0x20	/* (5) J06 優先原稿濃度		0*/
#define	LST_S_DIALINGPAUSE			0x40	/* (6) J07 ﾎﾟｰｽﾞ時間		0*/
#define	LST_S_NUMBEROFRINGS			0x80	/* (7) J08 呼出ﾍﾞﾙ回数		0*/
#define	LST_S_SECONDTELEPHONEHOLD	0x01	/* (8) J09 子電話接続		1*/
#define	LST_S_ANSWERINGDEVICE		0x02	/* (9) J10 留守番電話		1*/
#define	LST_S_DIALIN				0x04	/*(10) J11 ﾀﾞｲﾔﾙｲﾝ			1*/
#define	LST_S_RECEIVEREDUCTION		0x08	/*(11) J12 ﾌﾟﾘﾝﾄ縮小率		1*/
#define	LST_S_ECMMODE				0x10	/*(12) J13 ECMﾓｰﾄﾞ			1*/
#define	LST_S_COPYPROTECT			0x20	/*(13) J14 ｺﾋﾟｰ禁止			1*/
#define	LST_S_REMOTEDIAGNOSTIC		0x40	/*(14) J15 ﾘﾓｰﾄ診断			1*/
#define	LST_S_NUMBEROFREDIALS		0x80	/*(15) J16 ﾘﾀﾞｲﾔﾙ回数		1*/
#define	LST_S_REDIALINTERVAL		0x01	/*(16) J17 ﾘﾀﾞｲﾔﾙ間隔		2*/
/* #define	LST_S_AUTORECEIVETIME	0x02	(17) J18 自動受信時刻		2*/
#define	LST_S_HOLDMELODY			0x02	/*(18) J19 保留ﾒﾛﾃﾞｨ		2*/
#define	LST_S_PASSCODE				0x04	/*(19) J20 ﾊﾟｽｺｰﾄﾞ			2*/
#define	LST_S_CLOSEDNETWORK			0x08	/*(20) J21 閉域通信			2*/
#define	LST_S_PRIMARYTELFAX			0x10	/*(21) J22 電話FAX優先		2*/
/* #define	LST_S_PRIMARYFAXTIME	0x40	(22) J23 ﾌｧｸｽ優先時刻		2*/
#define	LST_S_SECURITYTRANSMISSION	0x20	/*(23) J24 ﾊﾟｽﾜｰﾄﾞ送信		2*/
#define	LST_S_BLOCKJUNKFAX			0x40	/*(24) J25 ﾀﾞｲﾚｸﾄﾒｰﾙ		2*/
#define	LST_S_CHANGERECIVE			0x80	/*(25) J26 受信ﾓｰﾄﾞ			2*/
#define	LST_S_PAGECOMPOUND			0x01	/*(26) J27 ﾍﾟｰｼﾞ合成		3*/
#define	LST_S_RS232CPARAMETER		0x02	/*(27) J28 RS232C			3*/
#define	LST_S_STAMP					0x04	/*(28) J29 済ｽﾀﾝﾌﾟ			3*/
#define	LST_S_MEMORYTRANSMISSION	0x08	/*(29) J30 ﾒﾓﾘ送信			3*/
#define	LST_S_RELAYED_RELAY_TX		0x10	/*(30) J31 中々継			3*/
#define	LST_S_RECORDPAPER			0x20	/*(31) J32 記録紙ﾀｲﾌﾟ		3*/
#define	LST_S_PRINTSETTINGS			0x40	/*(32) J33 機器設定ﾘｽﾄ		3*/
/* #define	LST_S_DONORFILMTYPE		0x02	(33) J34 ﾄﾞﾅｰﾌｨﾙﾑﾀｲﾌﾟ		4*/

#endif

#if 0 /* (PRO_RELAYED_REPORT == ENABLE)	*/ /*  H.Kubo 1998/01/19 */
#define	LST_ACK_ONE_LINE_IMAGE 		0x01
#define	LST_EMPTY_ONE_LINE_IMAGE	0x02
#define	LST_ACK_PAGE_END			0x04
#endif /* (PRO_RELAYED_REPORT == ENABLE)	*/ /*  H.Kubo 1998/01/19 */

#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
/************************************************************************
*          BY:	清水政貴、木元修
*        DATE:	1996/06/10
* DESCRIPTION:	絵文字表示のための定義
************************************************************************/
#define LCD_PICFONT_TOTAL	4				/* 使用する文字数 */

#define LCD_PICFONT			0xF0			/* 下位４ビットで合計１６個の絵文字を定義可能 */
#define LCD_PICFONT_LOWER	0xFF			/* 絵文字表示のためのキャラクタコード
											** １ワードで表現し、２バイト目には 0xFF を格納
											*/
#endif

/* 印刷種類 チェックメッセージBで使用	1998/10/28 Y.Matsukuma */
#define	LST_PRINT_TCR		1
#define	LST_PRINT_TCR_NOT	0

