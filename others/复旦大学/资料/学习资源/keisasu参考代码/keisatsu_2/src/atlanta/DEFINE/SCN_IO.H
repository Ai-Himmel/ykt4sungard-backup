/*---------------------------------------------------------------------*/
/* プロジェクト : POPLAR/ANZU_L                                        */
/* ファイル名   : scn_io.h                                             */
/* 作成者       : 野瀬敏弘                                             */
/* 日  付       : 1996/10/15                                           */
/* 概  要       : G/A Scanner Port 定義                                */
/* 修正履歴     : \src\kobe\anzu\define\scn_io.hkrより流用 T.Nose      */
/*---------------------------------------------------------------------*/
#ifndef scn_io_h
	#define	scn_io_h
/*********************************************************************** 
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用Ｇ．Ａ．ベース・アドレス
************************************************************************/
/*	#define	MD9509_BASE_PORT	0x00C20700 BYTEｱｸｾｽのため奇数ｱﾄﾞﾚｽに変更 */
	#define	MD9509_BASE_PORT	0x00C20701
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_MTPC0_Status 
*         R/W:	Write
* DESCRIPTION:  モーター速度＝下位８ビット分ｘ（１／３ＭＨｚ）
*********************************************************************************************/
#define	MTPC0_PORT		MD9509_BASE_PORT+0x0000		/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_MTPC1_Status 
*         R/W:	Write
* DESCRIPTION:  モーター速度＝上位５ビット分（Ｄ０からＤ４）ｘ（１／３ＭＨｚ）
*				Ｄ５からＤ７は未使用
*********************************************************************************************/
#define	MTPC1_PORT		MD9509_BASE_PORT+0x0002		/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_MTP0_Status
*         R/W:	Write
* DESCRIPTION:  モーター速度変更間隔＝下位８ビット分ｘモーターステップ
*********************************************************************************************/
#define	MTP0_PORT		MD9509_BASE_PORT+0x0004		/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_MTP1_Status
*         R/W:	Write
* DESCRIPTION:  モーター速度変更間隔＝上位５ビット（Ｄ０からＤ４）分ｘモーターステップ
*				電流制御　Ｄ５　　Ｄ６
*							1		1		：１００％
*							1		0		：　６０％
*							0		1		：　２０％
*							0		0		：　　０％
*				Ｄ７：モーター励磁相
*********************************************************************************************/
#define	MTP1_PORT		MD9509_BASE_PORT+0x0006		/* アドレス								*/
#define	IO_BIT_CURRENT_POWER_D5	0x20
#define	IO_BIT_CURRENT_POWER_D6	0x40
#define	IO_BIT_MOTOR_EXCITE_METHOD	0x80	/* モーター励磁相 (0=2相 / 1=1-2相) */
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	UWORD SCN_SENSTP_Status
*         R/W:	Write
* DESCRIPTION:  読み取り後端設定＝下位８ビットｘモーターステップ
*********************************************************************************************/
#define	SENSTP0_PORT	MD9509_BASE_PORT+0x0008		/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	UWORD SCN_SENSTP1_Status 
*         R/W:	Write
* DESCRIPTION:  読み取り後端設定＝上位５ビット（Ｄ０からＤ４）分ｘモーターステップ
*********************************************************************************************/
#define	SENSTP1_PORT	MD9509_BASE_PORT+0x000A		/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	UWORD SCN_SSTSTP_Status
*         R/W:	Write
* DESCRIPTION:  読み取り先端設定＝下位８ビットｘモーターステップ
*********************************************************************************************/
#define	SSTSTP0_PORT	MD9509_BASE_PORT+0x000C		/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	UWORD SCN_SSTSTP1_Status 
*         R/W:	Write
* DESCRIPTION:  読み取り先端設定＝上位５ビット（Ｄ０からＤ４）分ｘモーターステップ
*********************************************************************************************/
#define	SSTSTP1_PORT	MD9509_BASE_PORT+0x000E		/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_SCNINT_Status 
*         R/W:	Write
* DESCRIPTION:  読み取り間隔設定＝４ビット（Ｄ０からＤ３）分ｘモーターステップ
*				SFINE : 0, FINE : 1, NORMAL : 3をセットする
*********************************************************************************************/
#define	SCNINT_PORT		MD9509_BASE_PORT+0x0010		/* アドレス								*/
#define	IO_BIT_SCANINT					0x0F		/* 読取り間隔設定の使用ビットマスク */
#define IO_BIT_CCTSCAN					0x10		/*CTSCAN　コントロール '96,01,12 By N.S. for ANZU */
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_DS2INTR_Status 
*         R/W:	Write
* DESCRIPTION:  ビット・アサイメント参照
*********************************************************************************************/
#define	DS2INTR_PORT	MD9509_BASE_PORT+0x0012		/* アドレス								*/

#define	IO_BIT_DS2_ON_ENABLE			0x01		/* ＤＳ２　ＯＮステータス許可			*/
#define	IO_BIT_DS2_OFF_ENABLE			0x02		/* ＤＳ２　ＯＦＦステータス許可			*/
#define	IO_BIT_DS2_ON_INT_ENABLE		0x04		/* ＤＳ２　ＯＮ割り込み許可				*/
#define	IO_BIT_DS2_OFF_INT_ENABLE		0x08		/* ＤＳ２　ＯＦＦ割り込み許可			*/
#define	IO_BIT_SCAN_START_INT_ENABLE	0x10		/* スキャン開始割り込み許可				*/
#define	IO_BIT_SCAN_END_INT_ENABLE		0x20		/* スキャン終了割り込み許可				*/
/****８月８日以降のＧ／Ａより下記定義が有効*/
#define	IO_BIT_IP_INT_ENABLE			0x40		/* ＩＤＰ　ＩＰ割り込み何時でも許可（１）／縮小発生以降許可（０） */
#define	IO_BIT_XLAINT_CLEAR				0x80		/* 縮小後のＩＰ割り込みクリア（ワンショット’０’パルス） */
/*******************************************/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_BUZZ_1K_Status
*         R/W:	Write
* DESCRIPTION:  
*				Ｄ０からＤ３　ブザー周波数＝ 23.4325KHz/(2*(設定値+1))
*					ex)23.4325/(2*(0x0A+1))=1.065KHz
*				Ｄ４からＤ７　１ＫＨｚ発生＝ 23.4325KHz/(2*(設定値+1))
*					ex)23.4325/(2*(0x0A+1))=1.065KHz
*********************************************************************************************/
#define	BUZZ_1K_PORT	MD9509_BASE_PORT+0x0014		/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_MTCNT_Status 
*         R/W:	Write
* DESCRIPTION:  ビット・アサイメント参照
*********************************************************************************************/
#define	MTCNT_PORT		MD9509_BASE_PORT+0x0016		/* アドレス								*/

#define	IO_BIT_XMOTOR_PULSE_CTR_CLEAR	0x01		/* モーターパルスカウンタクリア			*/
#define	IO_BIT_MOTOR_INTERVAL_LATCH		0x02		/* モーター変更間隔初期ラッチ			*/
#define	IO_BIT_MOTOR_SPEED_LATCH		0x04		/* モーター速度初期ラッチ				*/
#define	IO_BIT_LINE_INT_COUNT_LATCH		0x08		/* 割り込みライン数初期ラッチ			*/
#define	IO_BIT_MOTOR_INT_ENABLE			0x10		/* モーター割り込み許可					*/
#define	IO_BIT_MOTOR_PULSE_CLEAR		0x20		/* モーターパルスクリア					*/
#define	IO_BIT_MOTOR_CLOCKWISE			0x40		/* モーター正転逆転						*/
#define	IO_BIT_MOTOR_ENABLE				0x80		/* モーターイネーブル					*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_SCCNT_Status
*         R/W:	Write
* DESCRIPTION:  ビット・アサイメント参照
*********************************************************************************************/
#define	SCCNT_PORT		MD9509_BASE_PORT+0x0018		/* アドレス								*/
#define	IO_BIT_SCAN_END_LATCH			0x01		/* スキャンエンド初期ラッチ				*/
#define	IO_BIT_SCAN_START_LATCH			0x02		/* スキャンスタート初期ラッチ			*/
#define	IO_BIT_SCAN_INTERVAL_LATCH		0x04		/* スキャン間隔初期ラッチ				*/
#define	IO_BIT_SCAN_SOFT_START			0x08		/* ソフトスキャンスタート				*/
#define	IO_BIT_LINE_INT_ENABLE			0x10		/* 設定ライン数での割り込み許可			*/
#define	IO_BIT_BUZZER_ENABLE			0x20		/* ブザーのＯＮ／ＯＦＦ					*/
#define	IO_BIT_SCAN_SOFT_ENABLE			0x40		/* ソフト／ハードのスキャン切り替え		*/
#define	IO_BIT_SCAN_DMA_ENABLE			0x80		/* ＣＯＤＥＣメモリへのＤＭＡリクエスト許可 */
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_INTLNCN_Status
*         R/W:	Write
* DESCRIPTION:  Ｄ０からＤ７　設定数＝ライン割り込み間隔ｘ読み取りライン
*********************************************************************************************/
#define	INTLNCN_PORT	MD9509_BASE_PORT+0x001A		/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
*         R/W:	Read
* DESCRIPTION:  モーター・ステップ・カウント下位８ビット
*********************************************************************************************/
#define	MTCNT0_PORT	MD9509_BASE_PORT+0x0000			/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
*         R/W:	Read
* DESCRIPTION:  モーター・ステップ・カウント上位８ビット
*********************************************************************************************/
#define	MTCNT1_PORT	MD9509_BASE_PORT+0x0002			/* アドレス								*/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
*         R/W:	Read
* DESCRIPTION:  割り込み要因ステータス１（ＤＳ２割り込み発生時）
*********************************************************************************************/
#define	INTST0_PORT	MD9509_BASE_PORT+0x0004			/* アドレス								*/
#define	IO_BIT_SCANEND_INT		0x0001				/* 読み取り終了割り込み要求				*/
#define	IO_BIT_SCANSTART_INT	0x0002				/* 読み取り開始割り込み要求				*/
#define	IO_BIT_DS2OFF_INT		0x0004				/* ＤＳ２　ＯＦＦ割り込み要求			*/
#define	IO_BIT_DS2ON_INT		0x0008				/* ＤＳ２　ＯＮ割り込み要求				*/
/*********************************
#define	予備				0x0010
#define	予備				0x0020
#define	予備				0x0040
#define	予備				0x0080
*********************************/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
*         R/W:	Read
* DESCRIPTION:  割り込み要因ステータス２（スキャナー割り込み発生時）
*********************************************************************************************/
#define	INTST1_PORT	MD9509_BASE_PORT+0x0006			/* アドレス								*/
#define	IO_BIT_LINE_INT		0x0001					/* ライン割り込み要求					*/
#define	IO_BIT_MOTOR_INT	0x0002					/* モーター割り込み要求					*/
/*********************************
#define	予備				0x0004
#define	予備				0x0008
#define	予備				0x0010
#define	予備				0x0020
#define	予備				0x0040
#define	予備				0x0080
*********************************/
/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  23,Oct,1995
*        TYPE:  DEFINE
*         R/W:	Read
* DESCRIPTION:  ＩＤＰ縮小ステータス（ＩＤＰ割り込み発生時）
*********************************************************************************************/
#define	RED_PORT	MD9509_BASE_PORT+0x0008			/* アドレス								*/
/*****************************
#define	予備			0x0001
#define	予備			0x0002
*****************************/
#define	IO_BIT_LACT		0x0004						/* ０：保存ライン、１：縮小ライン		*/
/*****************************
#define	予備			0x0008
#define	予備			0x0010
#define	予備			0x0020
#define	予備			0x0040
#define	予備			0x0080
*****************************/
#endif
