/*******************************************************************************************************
* ANZU
*
*	 File	Name:  IDP_DEF.H
*	 Coded	  by:  坂本直史
*
*	 Note		:  日立画像処理ＬＳＩ(HD813301(IDP-301))全体定義
*
*				   '96,01,23  東芝 A4/B4部分のみ300dpi用に変更
*				   '96,03,13  日電 A4/B4部分のみ300dpi用に変更(最終的にANZUでは使用しない'96,04,04確認済)
*				   '96,04,18  東芝 B4 300dpi用Data再確認
*				   '96,08,09  日電 B4(ANZU B Type)300dpi用Test
*				   '96,10,09  SONY B4(ANZU B Type)300dpi用Test
*
********************************************************************************************************/
#ifndef	IDP_DEF_H
	#define	IDP_DEF_H	1

	#define	CCD_TYPE_ANZU_B		0		/* 0:ANZU_A(A4) 1:ANZU_B(B4) 1996/08/06 By N.Sakamoto */


	/*============*/
	/* IDP301全体 */
	/*============*/
	/*--------*/
	/* 戻り値 */
	/*--------*/
	#define IDP_OK		 0											/* 正常終了								*/
	#define IDP_ERROR	-1											/* 異常終了								*/
	#define IDP_BIT_ON	 1											/* BIT ON								*/
	#define IDP_BIT_OFF	 0											/* BIT OFF								*/

	/*---------------------------------------------*/
	/* IDP301動作種別(SCN/PRN/CDCのOpenTypeで指定) */
	/*---------------------------------------------*/
	#define IDP_NO_USE						0						/* 未使用								*/
	#define IDP_SCANNER_COPY				1						/* リアルタイムコピー					*/
	#define IDP_DOCUMENT_STORE				2						/* 原稿蓄積								*/
	#define IDP_STORE_DOCUMENT_PRINT		3						/* 蓄積原稿プリント						*/
	#define IDP_BUFFERRING_DOCUMENT_PRINT	4						/* バッファリング受信原稿プリント		*/
	#define IDP_SCANNER_TX					5						/* スキャナ送信							*/
	#define IDP_MEMORY_TX					6						/* メモリー送信（デコード方向）			*/
	#define IDP_CHARACTER_TX				7						/* キャラクタ送信（TTIを含む）			*/
	#define IDP_PRINTER_RX					8						/* プリンタ受信							*/
	#define IDP_BUFFERRING_RX				9						/* バッファリング受信					*/
	#define IDP_MEMORY_RX				   10						/* メモリー受信							*/
	#define IDP_LIST_PRINT				   11						/* リストプリント						*/

	/*----------*/
	/* 縮小種別 */
	/*----------*/
	#define IP_SCANNER_REDUCTION			0
	#define IP_MEMORY_REDUCTION				1
	#define IP_PRINTER_AUTO_REDUCTION		2
	#define IP_PRINTER_FIX_REDUCTION		3
	#define IP_PRINTER_MAGNIFICATION		4						/** MOMIJI Character Print用			*/
	#define IP_CHARACTER_MAGNIFICATION		5						/**	MOMIJI Character Tx用				*/


	/*======================*/
	/*	DIPP_AS モジュール	*/
	/*======================*/
	#define DIPP_REGISTER_SIZE				28						/* DIPP Auto Increment Register Size	*/

	/*	原稿サイズ検出用テーブルの構造体
	**		doc_sizeの範囲 : min < (原稿幅) <= max
	*/
	struct DIPP_SizeDetTable_t {
		UBYTE			size;		/* 検出サイズのdefine値(sysdoc.h参照) */
		UWORD			min;		/* 検出サイズの最小幅 (mm) */
		UWORD			max;		/* 検出サイズの最大幅 (mm) */
	};

	/*===================*/
	/*	IP-1 モジュール	 */
	/*===================*/
	#define IP_REGISTER_SIZE  48									/* IP Auto Increment Register Size		*/

	/*---------------*/
	/*	解像度変換	 */
	/*---------------*/
#if (0)
#if (PRO_CCD == DPI100)
	#define SCN_CCD_RESOLUTION	1
#endif
#if (PRO_CCD == DPI200)
	#define SCN_CCD_RESOLUTION	2
#endif
#if (PRO_CCD == DPI300)
	#define SCN_CCD_RESOLUTION	3
#endif
#if (PRO_CCD == DPI400)
	#define SCN_CCD_RESOLUTION	4
#endif
#if (PRO_CCD == DPI500)
	#define SCN_CCD_RESOLUTION	5
#endif
#if (PRO_CCD == DPI600)
	#define SCN_CCD_RESOLUTION	6
#endif
#if (PRO_CCD == DPI700)
	#define SCN_CCD_RESOLUTION	7
#endif
#if (PRO_CCD == DPI800)
	#define SCN_CCD_RESOLUTION	8
#endif

	/** 各サイズと読み取り幅とＣＣＤ解像度に対応したドット数 **/
	#define A4_PART_DOTS					((1727-(32*2))*(SCN_CCD_RESOLUTION/2))
	#define A4_FULL_DOTS					(1728         *(SCN_CCD_RESOLUTION/2))
	#define B4_PART_DOTS					((2048-(16*2))*(SCN_CCD_RESOLUTION/2))
	#define B4_FULL_DOTS					(2048         *(SCN_CCD_RESOLUTION/2))
	#define A3_PART_DOTS					((2432-(16*2))*(SCN_CCD_RESOLUTION/2))
	#define A3_FULL_DOTS					(2432         *(SCN_CCD_RESOLUTION/2))
#endif

#if (PRO_CCD == DPI200)
	#define SCN_DOT_PER_MM	8

	#define PRO_CCD_RESOLUTION	1		/* SAKAKI 1998/08/21 H.Yoshikawa */
#endif
#if (PRO_CCD == DPI300)
	#define SCN_DOT_PER_MM	12
#endif
#if (PRO_CCD == DPI400)
	#define SCN_DOT_PER_MM	16
#endif

#if (0)	/* 1998/09/02 H.Yoshikawa */
	#define A4_PART_DOTS	(214*SCN_DOT_PER_MM) /* 2mm Mask */
	#define A4_FULL_DOTS	(216*SCN_DOT_PER_MM)
	#define B4_PART_DOTS	(254*SCN_DOT_PER_MM) /* 2mm Mask */
	#define B4_FULL_DOTS	(256*SCN_DOT_PER_MM)
	#define A3_PART_DOTS	(302*SCN_DOT_PER_MM) /* 2mm Mask */
	#define A3_FULL_DOTS	(304*SCN_DOT_PER_MM)
#endif
	/*---------------------------------------------------------------------
	** POPLAR/ANZU_Lでは左右マスクをコーデックで使用するので、PART_DOTSは使用しない
	** PART_DOTS時のマスク量は過去機種に従いました。
	** マスク量を変更する場合には、
	**	 ●A4_PART_DOTS == DICEP_TRC_Table[A4][PART_DOTS] == DIPP_ADF_A4_PART_IWEND
	**	 ●DICEP_AR_SARC =encode_ptr->LineMemoryWritePtr * A3_FULL_DOTS + 左マスク量
	** となるようにしなければならない。
	** 1998/09/02 H.Yoshikawa
	*/
	#define A4_PART_DOTS	((216-(4*2))*SCN_DOT_PER_MM) /* 左右4mm Mask */
	#define A4_FULL_DOTS	(216*SCN_DOT_PER_MM)
	#define B4_PART_DOTS	((256-(2*2))*SCN_DOT_PER_MM) /* 左右2mm Mask */
	#define B4_FULL_DOTS	(256*SCN_DOT_PER_MM)
	#define A3_PART_DOTS	((304-(2*2))*SCN_DOT_PER_MM) /* 左右2mm Mask */
	#define A3_FULL_DOTS	(304*SCN_DOT_PER_MM)

	/*------------------------*/
	/* IP-1パラメータ設定情報 */
	/*------------------------*/
	struct IP_Control_def_t {
		UBYTE  IP_UseType;									/* IP-1利用種別							*/
		UBYTE  IP_Mode;										/* IP-1画像処理モード(単純2値/中間調(sysmode.h参照) */
		UWORD  IP_InputSize;								/* IP-1入力画素数						*/
		UWORD  IP_OutputSize;								/* IP-1出力処理画素数					*/
	};

	/*---------------------------*/
	/* スキャナ/プリンタ縮小定義 */
	/*---------------------------*/
	struct IP_ReductionTable_def_t {
		UBYTE IP_m;											/* R05:線密度変換用 mパラメータ			*/
		UBYTE IP_k;											/* R05:線密度変換用 kパラメータ			*/
		UBYTE IP_l_low;										/* R06:線密度変換用 lパラメータ(1)		*/
		UBYTE IP_l_high;									/* R07:線密度変換用 lパラメータ(2)		*/
	};

	/*---------------------------------------*/
	/*			スキャナ縮小定義			 */
	/*(ANZU専用mm系300dpiからinch系への縮小) */
	/*---------------------------------------*/
	struct IP_InchReductionTable_def_t {
		UBYTE  R05;											/* R05:線密度変換用 m,kパラメータ		*/
		UBYTE  R06;											/* R06:線密度変換用 lパラメータ(1)		*/
		UBYTE  R07;											/* R06:線密度変換用 lパラメータ(2)		*/
		UWORD  OutputBit;											/* 縮小後の出力画素数					*/
	};


	/*---------------------------------------------------------------------
	** SAKAKI用に追加
	** 1998/06/05 H.Yoshikawa
	*/
	/**********************/
	/*  DICEP モジュール  */
	/**********************/
	#define DICEP_A_CHANNEL      0
	#define DICEP_B_CHANNEL      1
	#define DICEP_REGISTER_SIZE  8  /* DICEP レジスタ サイズ */

#endif
