/* By Y.Suzuki 1996/10/15 */
/* Original File : jun\usr2:\src\ichou\define\sysdoc.h */
#ifndef	SYSDOC_H
	#define	SYSDOC_H

/************************************************************************
 * 原稿サイズ															*
 * unsigned char SYS_DocumentScanSize									*
 * sysscan.jsw参照														*
 * 1993/11/24 吉川弘康													*
 ************************************************************************/
#define SYS_DOCUMENT_A4_SIZE	0  /* A4 */
#define SYS_DOCUMENT_B4_SIZE	1  /* B4 */
#define SYS_DOCUMENT_A3_SIZE	2  /* A3 */
#define SYS_DOCUMENT_A5_SIZE	3  /* A5 */
#define SYS_DOCUMENT_B5_SIZE	4  /* B5 */
#define SYS_DOCUMENT_A6_SIZE	5  /* A6 */
#define SYS_DOCUMENT_LT_SIZE	6  /* LETTER */
#define SYS_DOCUMENT_LG_SIZE	7  /* LEGAL */

/*------------------------------------------------------------------------
**	定形原稿サイズ
**	unsigned char  SYS_RegularDocumentSize
**		縦/横(～R)は主走査に対する方向で、表示等は縦/横逆になる
**		※上記原稿サイズ(SYS_DocumentScanSize)は主走査の幅として区別する
**		1996/05/16 s.takeuchi
*/
#define	SYS_REGULAR_SIZE_UNKNOWN		0xff	/* 不定 */
#define	SYS_REGULAR_SIZE_A3				0		/* A3縦 */
#define	SYS_REGULAR_SIZE_B4				1		/* B4縦 */
#define	SYS_REGULAR_SIZE_A4				2		/* A4縦 */
#define	SYS_REGULAR_SIZE_A4R			3		/* A4横 */
#define	SYS_REGULAR_SIZE_B5R			4		/* B5横 */
#define	SYS_REGULAR_SIZE_A5R			5		/* A5横 */
#define	SYS_REGULAR_SIZE_LETTER			6		/* レター縦 */
#define	SYS_REGULAR_SIZE_LETTER_R		7		/* レター横 */
#define	SYS_REGULAR_SIZE_LEGAL			8		/* リーガル */
#define	SYS_REGULAR_SIZE_LEDGER			9		/*レジャー縦 */
#define SYS_REGULAR_SIZE_HALFLETTER_R	10      /* added by honda 1997/11/14 ハーフレター横 */
#define SYS_REGULAR_SIZE_F4				11		/* POPLAR_B AUS bythonda1998/05/12 */

/************************************************************************
 * 送信モード															*
 * unsigned char SYB_ModeSw												*
 * mm/inchともに共通													*
 * sysmode.jsw参照														*
 * 1993/11/24 吉川弘康													*
 * 注)メモリには、各モードともインチで蓄積される(94.1.12現在)			*
 *	  従って､メモリにインチ／ミリどちらで蓄積されているかを示す変数は､	*
 *	  不要																*
 *	  交信がインチ／ミリのどちらで行われるかを記憶する変数は必要		*
 *	  その変数によってインチー＞ミリ変換を行うか否かを判断する(鈴木)	*
 * モードのDEFINEはｸﾛｰﾊﾞｰがからむので容易に変更しないこと(村田)			*
 ************************************************************************/
						   /*		   主走査		   副走査		   */
#define SYS_NORMAL		0  /* 普通	   200dpi:8 dot/m  100dpi:3.85本/l */
#define SYS_FINE		1  /* 高画質   200dpi:8 dot/m  200dpi:7.7 本/l */
#define SYS_SFINE		2  /* 超高画質 200dpi:8 dot/m  400dpi:15.5本/l */
#define SYS_HFINE		3  /* 超高画質 400dpi:16dot/m  400dpi:15.5本/l */
#define SYS_GRAY16		4  /* 16階調   200dpi:8 dot/m  200dpi:7.7 本/l */
#define SYS_GRAY16_SEP	5  /* 16階調   200dpi:8 dot/m  200dpi:7.7 本/l */
						   /* 像域分離								   */
#define SYS_GRAY32		6  /* 32階調   200dpi:8 dot/m  200dpi:7.7 本/l */
#define SYS_GRAY32_SEP	7  /* 32階調   200dpi:8 dot/m  200dpi:7.7 本/l */
						   /* 像域分離								   */
#define SYS_GRAY64		8  /* 64階調   200dpi:8 dot/m  200dpi:7.7 本/l */
#define SYS_GRAY64_SEP	9  /* 64階調   200dpi:8 dot/m  200dpi:7.7 本/l */

#define	SYS_300_NORMAL	10 /*		   300dpi		   100dpi		   */
#define	SYS_300_FINE	11 /*		   300dpi		   200dpi		   */
#define SYS_OFINE		12 /*		   300dpi		   300dpi		   */
#define	SYS_EFINE		13 /*          300dpi          300dpi （㍉系） By S.Kawasaki 1996/06/14 */
#define	SYS_UFINE       14 /*          600dpi          600dpi （㍉系） By S.Kawasaki 1996/06/14 */
#define SYS_E_HFINE		15 /* 超高画質 300dpi:12dot/m  400dpi:15.5本/l */
						   /* 像域分離								   */
#define SYS_GRAY128		20 /* 128階調  200dpi:8 dot/m  200dpi:7.7 本/l */
#define SYS_GRAY128_SEP 21 /* 128階調  200dpi:8 dot/m  200dpi:7.7 本/l */
						   /* 像域分離								   */
#define SYS_NORMAL_ROT	30  /* 普通回転	   	100dpi: 4 dot/m 200dpi: 7.7本/l */
#define SYS_SFINE_ROT	31  /* 超高画質回転	400dpi:16 dot/m 200dpi: 7.7本/l */

#define SYS_SGRAY		40 /* 読み取りで変倍(ＩＣＨＯＵで使用検討中		*/ 
						   /*          400dpi:16 dot/mm 400dpi:15.4本/l */
#if (PRO_PITNEYBOWES == ENABLE)
#define SYS_HGRAY		50 /* SYS_SFINE以上の解像度での写真モード  [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
#endif
/************************************************************************
 * 送信モード mm or inch												*
 * unsigned char SYS_DocBlockData.ModeMethod							*
 * 通常　インチをセット　DIS/DTC ミリビットのみONの場合､ミリをセット	*
 *																		*
 * 1994/1/14 鈴木　　													*
 * 注)メモリには、各モードともインチで蓄積される(94.1.12現在)			*
 *	  従って､メモリにインチ／ミリどちらで蓄積されているかを示す変数は､	*
 *	  不要																*
 *	  交信がインチ／ミリのどちらで行われるかを記憶する変数は必要		*
 *	  その変数によってインチー＞ミリ変換を行うか否かを判断する(鈴木)	*
 ************************************************************************/
#define SYS_METRIC		   0  /* ミリ */
#define SYS_INCH		   1  /* インチ */

/************************************************************************
 * 原稿濃度																*
 * unsigned char SYS_DensSw												*
 * sysdens.jsw参照														*
 * 1993/11/24 吉川弘康													*
 ************************************************************************/
#if (0) /* ●ICHOU変更 by T.Soneoka 1996/06/19 */
#define SYS_NORMAL_DENSITY 0  /* 普通 (NORMAL) */
#define SYS_DARK_DENSITY   1  /* 濃く (DARK)   */
#define SYS_LIGHT_DENSITY  2  /* 淡く (LIGHT)  */
#endif
/* ●ICHOU変更 by T.Soneoka 1996/06/19 */
#define SYS_LIGHT_DENSITY			0	/* 薄く */
#define SYS_LIGHT_NORMAL_DENSITY	1	/* 薄く－普通の間 */
#define SYS_NORMAL_DENSITY			2	/* 普通 */
#define SYS_DARK_NORMAL_DENSITY		3	/* 濃く－普通の間 */
#define SYS_DARK_DENSITY			4	/* 濃く */

/* 1ライン画素数 */
#define SYS_A4_LINE		1728  /* Dot */
#define SYS_B4_LINE		2048  /* Dot */
#define SYS_A3_LINE		2432  /* Dot */

/* 符号化方式 */
#define SYS_IMAGE_DATA	   0
#define SYS_MH_CODE		   1
#define SYS_MR_CODE		   2
#define SYS_MMR_CODE	   3
#define SYS_MG3_CODE	   4	/*松下ｺｰﾃﾞｯｸ MN86063 & MN86064 のみ使用*/
#define SYS_JBIG_CODE	   5	/*松下ｺｰﾃﾞｯｸ MN86064のみ使用*/

/*------------------------------------------------------------------------
** 記録紙サイズ・記録紙エリア
** unsigned char SYS_Paper1Size				：１段目カセット
** unsigned char SYS_Paper2Size				：２段目カセット
** unsigned char SYS_Paper3Size				：３段目カセット
** unsigned char SYS_Paper4Size				：４段目カセット
** unsigned char SYS_ManualPaperSize		：手差しカセット
** unsigned char SYS_PC_PrintSize			：ＰＣプリントサイズ Oct.04.1996 by T.Soneoka
*/
#define SYS_NO_CASSETTE		0xFE		/* カセットなし				*/
#define SYS_NO_PAPER		0xFF		/* 記録紙なし				*/

#define SYS_NO_UNIT			0xFD		/* ユニットなし			For POPLAR	*/
#define SYS_SIDE_COVER_OPEN	0xFC		/* サイドカバーオープン	For POPLAR	*/

#define SYS_A5_PAPER		0			/* Ａ５縦					*/
#define SYS_LT_PAPER		1			/* レター縦					*/
#define SYS_A4_PAPER		2			/* Ａ４縦					*/
#define SYS_LG_PAPER		3			/* リーガル縦				*/
#define SYS_B5R_PAPER		4			/* ＪＩＳ Ｂ５横			*/
#define SYS_B4_PAPER		5			/* ＪＩＳ Ｂ４縦			*/
#define SYS_A3_PAPER		6			/* Ａ３縦					*/
#define SYS_A4R_PAPER		7			/* Ａ４横					*/
#define SYS_LTR_PAPER		8			/* レター横					*/
#define SYS_F4_PAPER		9			/* Ｆ４縦					*/
#define SYS_A5R_PAPER		10			/* Ａ５横					*/
#define SYS_POST_PAPER		11			/* はがき縦					*/
#define SYS_LD_PAPER		12			/* レジャー縦				*/
#define SYS_GLTR_PAPER		13			/* ガバメント・レター横		*/
#define SYS_EXER_PAPER		14			/* エグゼクティブ横			*/

#define SYS_HLTR_PAPER		15			/* ハーフレター横			*/  /* added by honda 1997/10/04 POPLAR_B USA.GBR */

#define SYS_INVR_PAPER		15			/* インボイス横				*/
#define SYS_GLG_PAPER		16			/* ガバメント・リーガル縦	*/
#define SYS_GLT_PAPER		17			/* ガバメントレター縦		*/
#define SYS_CARD_PAPER		18			/* カードストック紙			*/
#define SYS_EXE_PAPER		19			/* エグゼクティブ縦			*/
#define SYS_B5_PAPER		20			/* ＪＩＳ Ｂ５縦			*/
#define SYS_C5_PAPER		21			/* Ｃ５縦					*/
#define SYS_HLT_PAPER		22			/* ハーフ・レター縦			*/
#define SYS_INV_PAPER		23			/* インボイス縦				*/
#define SYS_B6_PAPER		24			/* ＪＩＳ Ｂ６縦			*/
#define SYS_DL_PAPER		25			/* ＤＬ縦					*/
#define SYS_CM10_PAPER		26			/* コマーシャル１０縦		*/
#define SYS_A6_PAPER		27			/* Ａ６縦					*/
#define SYS_MNC_PAPER		28			/* モナーク縦				*/
#define SYS_35_PAPER		29			/* ３”×５”縦				*/
#define SYS_USER_PAPER		30			/* 不定形紙					*/

#define SYS_FIRST_PAPER_SIZE	SYS_A5_PAPER	/* 記録紙サイズの最初のサイズ */
#define SYS_LAST_PAPER_SIZE		SYS_USER_PAPER	/* 記録紙サイズの最後のサイズ */

/*------------------------------------------------------------------------
** 指定カセット
** sysmcopy.hから移動した
*/
#define SYS_AUTO_CASSETTE		0	/* 自動選択・指定なし */
#define SYS_1ST_CASSETTE		1	/* １段目カセット選択 */
#define SYS_2ND_CASSETTE		2	/* ２段目カセット選択 */
#define SYS_3RD_CASSETTE		3	/* ３段目カセット選択 */
#define SYS_MANUAL_CASSETTE		4	/* 手差しカセット選択 */

/* 縮小方式 */
/*----------------------------------------------------------------
#define SYS_AUTO		   0  %* 自動縮小 *%
#define SYS_A3_TO_A4	   1  %* 固定縮小(A3->A4, 22/32) *%
#define SYS_A3_TO_B4	   2  %* 固定縮小(A3->B4, 27/32) *%
#define SYS_B4_TO_A4	   3  %* 固定縮小(B4->A4, 26/32) *%
#define SYS_P_A3_TO_A4	   4  %* 固定縮小(A3->A4, 26/38) *%
#define SYS_P_B4_TO_A4	   5  %* 固定縮小(B4->A4, 26/32) *%
							  %* 可変縮小は60.0～100%まで対応 *%
----------------------------------------------------------------*/
/*------------------------------*/
/*	定型サイズの縮小率			*//*		Feb.21'94	竹内茂樹	*/
/*------------------------------*/
#define		SYS_SAME		1000				/*	同サイズ (100%) */
#define		SYS_A3_TO_B4	1000 * 27 / 32		/*	固定縮小 (A3->B4, 27/32) */
#define		SYS_A3_TO_A4	1000 * 22 / 32		/*	固定縮小 (A3->A4, 22/32) */
#define		SYS_B4_TO_A4	1000 * 26 / 32		/*	固定縮小 (B4->A4, 26/32) */

/* 送信原稿長制限 */
#define SYS_NO_LIMIT		0  /* 制限無し */
#define	SYS_A4_LENGTH		1  /*追加'94/2/8***/
#define	SYS_B4_LENGTH		2  /*鈴木**********/
#define	SYS_A3_LENGTH		3  /***************/
#define SYS_MAX_1M			4  /* 最大長 1M */
#define SYS_MAX_TWICE_A4	5  /* F網対応原稿長 */

/*----------------------------------------------------------*/
/*	原稿制御ブロックにセットする最大原稿長（送信／受信）	*/
/*		Jun.14.1994	竹内	fcm_def.hから移動				*/
/*----------------------------------------------------------*/
#if (0)	/* 定型の横サイズ用に拡張 */
#define		SYS_A3_PAGE_LENGTH			1617	/*	Ａ３(縦)原稿長		*/
#define		SYS_B4_PAGE_LENGTH			1401	/*	Ｂ４(縦)原稿長		*/
#define		SYS_A4_PAGE_LENGTH			1143	/*	Ａ４(縦)原稿長		*/
#define		SYS_A4_2PAGE_LENGTH			2286	/*	Ｆ網用原稿長	*/
#define		SYS_NO_LIMIT_PAGE_LENGTH	0xffff	/*	無限長			*/
#endif
/* 副走査の長さ(3.85l/mmでのline数) */
#define		SYS_A3_PAGE_LENGTH				1617	/* =420.0mm : A3 */
#define		SYS_B4_PAGE_LENGTH				1401	/* =363.9mm : B4 */
#define		SYS_A4_PAGE_LENGTH				1143	/* =296.9mm : A4 */
#define		SYS_A4_2PAGE_LENGTH				2286	/* =593.8mm : F網用原稿長(A4x2) */
#define		SYS_A4R_PAGE_LENGTH				 808	/* =209.9mm : A4R */
#define		SYS_B5R_PAGE_LENGTH				 700	/* =181.8mm : B5R */
#define		SYS_A5R_PAGE_LENGTH				 569	/* =147.8mm : A5R */
#define		SYS_LETTER_PAGE_LENGTH			1074	/* =279.0mm : LETTER */
#define		SYS_LETTER_R_PAGE_LENGTH		 831	/* =215.8mm : LETTER R */
#define		SYS_LEGAL_PAGE_LENGTH			1370	/* =355.8mm : LEGAL */
#define		SYS_HALFLETTER_R_PAGE_LENGTH	 538	/* =139.7mm : HALFLETTER R *//* added by honda 1997/11/14 */
#define		SYS_F4_PAGE_LENGTH				1270	/* =330.0mm : F4 *//* POPLAR_B AUS bythonda1998/05/12 */
#define		SYS_NO_LIMIT_PAGE_LENGTH		0xffff	/* 無限長 */
/* 主走査の幅(mm) */
#define		SYS_A3_PAGE_WIDTH		304		/* 304mm : A3 */
#define		SYS_B4_PAGE_WIDTH		256		/* 256mm : B4 */
#define		SYS_A4_PAGE_WIDTH		216		/* 216mm : A4 */

/* 受信原稿長制限 */
#define SYS_MAX_RX		   3  /* '93,04,03 By N.S. FRA Only */

#endif
/************************************************************************
 * 原稿濃度																*
 * unsigned char SYS_ThermalHeadSize									*
 * 1994/01/18 木元　修													*
 ************************************************************************/
 #define SYS_THERMALHEAD_A4	0
 #define SYS_THERMALHEAD_B4	1	/* 0 By S.Kawasaki Feb.21,1994 */

/************************************************************************
 * インク・ドナー・フィルムのサイズ										*
 * unsigned char SYS_IDFSize											*
 * 1994/01/18 木元　修													*
 ************************************************************************/
 #define SYS_IDFSIZE_A4		0
 #define SYS_IDFSIZE_B4		1



#if 0	/* 変更予定	  ２００のスキャナの定義も必要？　インチの定義削除 ? 1996/12/12	 By T.Yamaguchi */
/************************************************************************
 * ミリ系（406DPI）スキャナー送信時のテーブル							*
 * unsigned char ？？？？？？											*
 * 1996/12/12  By T.Yamaguchi											*
 ************************************************************************/
#define	SYS_A3_406_TO_A3_203		0	/** A3ミリ(406DPI) To A3ミリ(203DPI)		**/
#define	SYS_A3_406_TO_A3_200		1	/** A3ミリ(406DPI) To A3インチ(200DPI)		**/
#define	SYS_A3_406_TO_B4_406		2	/** A3ミリ(406DPI) To B4ミリ(406DPI)		**/
#define	SYS_A3_406_TO_B4_203		3	/** A3ミリ(406DPI) To B4ミリ(203DPI)		**/
#define	SYS_A3_406_TO_B4_200		4	/** A3ミリ(406DPI) To B4インチ(200DPI)		**/
#define	SYS_A3_406_TO_A4_406		5	/** A3ミリ(406DPI) To A4ミリ(406DPI)		**/
#define	SYS_A3_406_TO_A4_203		6	/** A3ミリ(406DPI) To A4ミリ(203DPI)		**/
#define	SYS_A3_406_TO_A4_200		7	/** A3ミリ(406DPI) To A4インチ(200DPI)		**/
#define	SYS_B4_406_TO_B4_203		8	/** B4ミリ(406DPI) To B4ミリ(203DPI)		**/
#define	SYS_B4_406_TO_B4_200		9	/** B4ミリ(406DPI) To B4インチ(200DPI)		**/
#define	SYS_B4_406_TO_A4_406		10	/** B4ミリ(406DPI) To A4ミリ(406PI)			**/
#define	SYS_B4_406_TO_A4_203		11	/** B4ミリ(406DPI) To A4ミリ(203DPI)		**/
#define	SYS_B4_406_TO_A4_200		12	/** B4ミリ(406DPI) To A4インチ(200DPI)		**/
#define	SYS_A4_406_TO_A4_206		13	/** A4ミリ(406DPI) To Aミリ(203DPI)			**/
#define	SYS_A4_406_TO_A4_200		14	/** A4ミリ(406DPI) To Aインチ(200DPI)		**/
#define	SYS_A3_406_TO_A3_406		15
#define	SYS_B4_406_TO_B4_406		16
#define	SYS_A4_406_TO_A4_406		17

#endif


/************************************************************************
 * インチ系（300/400DPI）スキャナー送信時のテーブル							*
 * unsigned char ？？？？？？											*
 * 1994/08/3 S.Kawasaki													*
 ************************************************************************/
/*----------------------------------------------------------------------------------------------*/
/*																								*/
/*		解像度変換の読み替え																	*/
/*		POPLAR_B/H(400dpi),ANZU_L(300dpi)の間で条件コンパイルをできるだけ少なくする為に			*/
/*		ANZU_Lでは次の読み替えを行います｡														*/
/*		Ａ４原稿時:SYS_A4_400_TO_A4_200	(A4原稿400dpiからA4原稿200dpiに解像度変換)				*/
/*																								*/
/*					→ SYS_A4_303_TO_A4_203(A4原稿12dot/mmからA4原稿8dot/mmに解像度変換)		*/
/*																								*/
/*		Ｂ４原稿時:SYS_B4_400_TO_B4_200(B4原稿400dpiからB4原稿200dpiに解像度変換)				*/
/*																								*/
/*					→ SYS_B4_303_TO_B4_203(B4原稿12dot/mmからB4原稿8dot/mmに解像度変換)		*/
/*																								*/
/*		Ａ３原稿時:SYS_A3_400_TO_A3_200 →	ANZUの仕様にないので未変更							*/
/*																								*/
/*----------------------------------------------------------------------------------------------*/
#define	SYS_A3_400_TO_A3_200		0	/** A3インチ(400DPI) To A3インチ(200DPI)	**/
#define	SYS_A3_400_TO_A3_203		1	/** A3インチ(400DPI) To A3ミリ(203DPI)		**/
#define	SYS_A3_400_TO_B4_400		2	/** A3インチ(400DPI) To B4インチ(400DPI)	**/
#define	SYS_A3_400_TO_B4_200		3	/** A3インチ(400DPI) To B4インチ(200DPI)	**/
#define	SYS_A3_400_TO_B4_203		4	/** A3インチ(400DPI) To B4ミリ(203DPI)		**/
#define	SYS_A3_400_TO_A4_400		5	/** A3インチ(400DPI) To A4インチ(400DPI)	**/
#define	SYS_A3_400_TO_A4_200		6	/** A3インチ(400DPI) To A4インチ(200DPI)	**/
#define	SYS_A3_400_TO_A4_203		7	/** A3インチ(400DPI) To A4ミリ(203DPI)		**/
#define	SYS_B4_400_TO_B4_200		8	/** B4インチ(400DPI) To B4インチ(200DPI)	**/
#define	SYS_B4_400_TO_B4_203		9	/** B4インチ(400DPI) To B4ミリ(203DPI)		**/
#define	SYS_B4_400_TO_A4_400		10	/** B4インチ(400DPI) To A4インチ(400DPI)	**/
#define	SYS_B4_400_TO_A4_200		11	/** B4インチ(400DPI) To A4インチ(200DPI)	**/
#define	SYS_B4_400_TO_A4_203		12	/** B4インチ(400DPI) To A4ミリ(203DPI)		**/
#define	SYS_A4_400_TO_A4_200		13	/** A4インチ(400DPI) To Aインチ(200DPI)		**/
#define	SYS_A4_400_TO_A4_203		14	/** A4インチ(400DPI) To Aミリ(203DPI)		**/
#define	SYS_A3_400_TO_A3_400		15
#define	SYS_B4_400_TO_B4_400		16
#define	SYS_A4_400_TO_A4_400		17

