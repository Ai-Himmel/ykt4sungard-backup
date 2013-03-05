/*--------------------------------------------------------------------------*/
/*プロジェクト: POPLAR_H                                                    */
/*モジュ-ル名 : POPH_SYS.H                                                  */
/*作成者名 	  : 野瀬                                                        */
/*日  付   	  : 96.10.11                                                    */
/*概  要   	  : SH7043                                                      */
/*  		    割込みコントローラ                  			            */
/*  		    バスステートコントローラ                  			        */
/*  		    内蔵ＤＭＡＣ                                                */
/*              外付けＤＭＡＣ                                              */
/*修正履歴 :    機種別に移動  By M.Kotani 97/06/11                          */
/*              POPLAR_Bよりコピー By O.Kimoto 1997/06/13                   */
/*              POPLAR_Hよりコピーしただけです。 By O.Kimoto 1998/09/07     */
/*--------------------------------------------------------------------------*/
#ifndef	HINO_SYS_H
	#define	HINO_SYS_H	1

#include "\src\atlanta\define\product.h"
/*************************************/
/*  割込みコントローラー・レジスター */
/*************************************/
    #define SH__ITR0		(*(UWORD *)0xffff8340)		/** ＩＮＴＣテストレジスタ０	   */
    #define SH__ITR1		(*(UWORD *)0xffff8342)		/** ＩＮＴＣテストレジスタ１	   */
    #define SH__ITR2		(*(UWORD *)0xffff8344)		/** ＩＮＴＣテストレジスタ２	   */
    #define SH__ITR3		(*(UWORD *)0xffff8346)		/** ＩＮＴＣテストレジスタ３	   */
	/*-----------------------------------------------------------------------------------------*/
    #define SH__IPRA		(*(UWORD *)0xffff8348)		/** 割込み優先レベル設定レジスタＡ */
#if (0) /* SAKAKIにあわせます 1998/11/25 by T.Soneoka */
**		#define	IRQ0_LEVEL		0xD000					/** ＩＲＱ０レベルＦ			   */
**		#define	IRQ1_LEVEL		0x0F00					/** ＩＲＱ１レベルＦ			   */
**		#define	IRQ2_LEVEL		0x00C0 /*0x00F0*/					/** ＩＲＱ２レベルＦ			   */
**		#define	IRQ3_LEVEL		0x000C /*0x000E*/					/** ＩＲＱ３レベルＦ			   */
#else
		#define	IRQ0_LEVEL		0xF000					/** ＩＲＱ０レベルＦ			   */
		#define	IRQ1_LEVEL		0x0F00					/** ＩＲＱ１レベルＦ			   */
		#define	IRQ2_LEVEL		0x00F0					/** ＩＲＱ２レベルＦ			   */
		#define	IRQ3_LEVEL		0x000F					/** ＩＲＱ３レベルＦ			   */
#endif
    #define SH__IPRB		(*(UWORD *)0xffff834A)		/** 割込み優先レベル設定レジスタＢ */
#if (0) /* SAKAKIにあわせます 1998/11/25 by T.Soneoka */
**		#define	IRQ4_LEVEL		0xC000					/** ＩＲＱ４レベルＦ			   */
**		#define	IRQ5_LEVEL		0x0C00					/** ＩＲＱ５レベルＦ			   */
**		#define	IRQ6_LEVEL		0x00C0					/** ＩＲＱ６レベルＦ			   */
**		#define	IRQ7_LEVEL		0x000C					/** ＩＲＱ７レベルＦ			   */
#else
		#define	IRQ4_LEVEL		0xF000					/** ＩＲＱ４レベルＦ			   */
		#define	IRQ5_LEVEL		0x0F00					/** ＩＲＱ５レベルＦ			   */
		#define	IRQ6_LEVEL		0x00F0					/** ＩＲＱ６レベルＦ			   */
		#define	IRQ7_LEVEL		0x000F					/** ＩＲＱ７レベルＦ			   */
#endif
    #define SH__IPRC		(*(UWORD *)0xffff834C)		/** 割込み優先レベル設定レジスタＣ */
		/* スキャナー・プリンタ位相ずれ対策 T.Nose */
		/* 内蔵ＤＭＡＣの優先順位は内蔵ＲＯＭで行っているのでＦのままとします T.Nose 1998/2/14 */
		#define	DMAC0_LEVEL		0xF000					/** ＤＭＡＣ０レベルＦ			   */
		#define	DMAC1_LEVEL		0x0F00					/** ＤＭＡＣ１レベルＦ			   */
		#define	DMAC2_LEVEL		0x00F0					/** ＤＭＡＣ２レベルＦ			   */
		#define	DMAC3_LEVEL		0x000F					/** ＤＭＡＣ３レベルＦ			   */
    #define SH__IPRD		(*(UWORD *)0xffff834E)		/** 割込み優先レベル設定レジスタＤ */
#if (0)
** 		/* スキャナーコーデック位相ずれ対策 T.Nose 1998/01/27 */
** 		#define	MTU0H_LEVEL		0xF000					/** ＭＴＵ０ＨレベルＦ			   */
** 		#define	MTU0L_LEVEL		0x0F00					/** ＭＴＵ０ＬレベルＦ			   */
** 		#define	MTU1H_LEVEL		0x00F0					/** ＭＴＵ１ＨレベルＦ			   */
** 		#define	MTU1L_LEVEL		0x000F					/** ＭＴＵ１ＬレベルＦ			   */
#else
		#define	MTU0H_LEVEL		0xC000					/** ＭＴＵ０ＨレベルＦ			   */
		#define	MTU0L_LEVEL		0x0F00					/** ＭＴＵ０ＬレベルＦ			   */
		#define	MTU1H_LEVEL		0x00C0					/** ＭＴＵ１ＨレベルＦ			   */
		#define	MTU1L_LEVEL		0x000F					/** ＭＴＵ１ＬレベルＦ			   */
#endif
    #define SH__IPRE		(*(UWORD *)0xffff8350)		/** 割込み優先レベル設定レジスタＥ */
		#define	MTU2H_LEVEL		0xF000					/** ＭＴＵ２ＨレベルＦ			   */
		#define	MTU2L_LEVEL		0x0F00					/** ＭＴＵ２ＬレベルＦ			   */
		#define	MTU3H_LEVEL		0x00F0					/** ＭＴＵ３ＨレベルＦ			   */
		#define	MTU3L_LEVEL		0x000F					/** ＭＴＵ３ＬレベルＦ			   */
    #define SH__IPRF		(*(UWORD *)0xffff8352)		/** 割込み優先レベル設定レジスタＦ */
		#define	MTU4H_LEVEL		0xF000					/** ＭＴＵ４ＨレベルＦ			   */
		#define	MTU4L_LEVEL		0x0F00					/** ＭＴＵ４ＬレベルＦ			   */
		#define	SCI0_LEVEL		0x00F0					/** ＳＣＩ０レベルＦ			   */
		#define	SCI1_LEVEL		0x000F					/** ＳＣＩ１レベルＦ			   */
    #define SH__IPRG		(*(UWORD *)0xffff8354)		/** 割込み優先レベル設定レジスタＧ */
#if (0)
** 		/* スキャナーコーデック位相ずれ対策 T.Nose 1998/01/27 */
** 		#define	AD_LEVEL		0xF000					/** ＡＤレベルＦ			   	   */
** 		#define	DTC_LEVEL		0x0F00					/** ＤＴＣレベルＦ			   	   */
** 		#define	CMT0_LEVEL		0x00F0					/** ＣＭＴ０レベルＦ			   */
** 		#define	CMT1_LEVEL		0x000F					/** ＣＭＴ１レベルＦ			   */
#else
		#define	AD_LEVEL		0xF000					/** ＡＤレベルＦ			   	   */
		#define	DTC_LEVEL		0x0C00					/** ＤＴＣレベルＦ			   	   */
		#define	CMT0_LEVEL		0x00F0					/** ＣＭＴ０レベルＦ			   */
		#define	CMT1_LEVEL		0x000F					/** ＣＭＴ１レベルＦ			   */
#endif
    #define SH__IPRH		(*(UWORD *)0xffff8356)		/** 割込み優先レベル設定レジスタＨ */
		#define	WDT_BSC_LEVEL	0xF000					/** ＷＤＴ、ＢＳＣレベルＦ	   	   */
		#define	IO_LEVEL		0x0F00					/** Ｉ／ＯレベルＦ			   	   */
		#define	RESERVE1_LEVEL	0x00F0					/** 予約レベルＦ			   	   */
		#define	RESERVE2_LEVEL	0x000F					/** 予約レベルＦ			   	   */
    #define SH__ICR			(*(UWORD *)0xffff8358)		/** 割込みコントロールレジスタ     */
    	#define	NMI_DOWN_EGDE	0x0000					/** ＮＭＩ入力を立ち下がりで検出   */
    	#define	NMI_UP_EGDE		0x0100					/** ＮＭＩ入力を立ち上がりで検出   */

		#define IRQ0_DOWN_EGDE	0x0080					/** ＩＲＱ０入力を立ち下がりで検出 */
		#define IRQ1_DOWN_EGDE	0x0040					/** ＩＲＱ１入力を立ち下がりで検出 */
		#define IRQ2_DOWN_EGDE	0x0020					/** ＩＲＱ２入力を立ち下がりで検出 */
		#define IRQ3_DOWN_EGDE	0x0010					/** ＩＲＱ３入力を立ち下がりで検出 */
		#define IRQ4_DOWN_EGDE	0x0008					/** ＩＲＱ４入力を立ち下がりで検出 */
		#define IRQ5_DOWN_EGDE	0x0004					/** ＩＲＱ５入力を立ち下がりで検出 */
		#define IRQ6_DOWN_EGDE	0x0002					/** ＩＲＱ６入力を立ち下がりで検出 */
		#define IRQ7_DOWN_EGDE	0x0001					/** ＩＲＱ７入力を立ち下がりで検出 */

    	#define	IRQ_LOW_LEVEL	0x0000					/** ＩＲＱ入力をロー・レベルで検出 */
    	#define	IRQ_DOWN_EGDE	0x00FF					/** ＩＲＱ入力を立ち下がりで検出   */
    #define SH__ISR			(*(UWORD *)0xffff835A)		/** ＩＲＱステータス・レジスタ     */
    	#define	IRQ0_STATUS		0x0080					/** ＩＲＱ０ステータス			   */
    	#define	IRQ1_STATUS		0x0040					/** ＩＲＱ１ステータス			   */
    	#define	IRQ2_STATUS		0x0020					/** ＩＲＱ２ステータス			   */
    	#define	IRQ3_STATUS		0x0010					/** ＩＲＱ３ステータス			   */
    	#define	IRQ4_STATUS		0x0008					/** ＩＲＱ４ステータス			   */
    	#define	IRQ5_STATUS		0x0004					/** ＩＲＱ５ステータス			   */
    	#define	IRQ6_STATUS		0x0002					/** ＩＲＱ６ステータス			   */
    	#define	IRQ7_STATUS		0x0001					/** ＩＲＱ７ステータス			   */
/********************************************/
/*  ユーザーブレークコントローラー（ＵＢＣ）*/
/********************************************/
	#define	SH__UBARH		(*(UWORD *)0xffff8600)		/**  ユーザーブレークアドレスレジスタＨ		*/
	#define	SH__UBARL		(*(UWORD *)0xffff8602)		/**  ユーザーブレークアドレスレジスタＬ		*/
	#define	SH__UBAMRH		(*(UWORD *)0xffff8604)		/**  ユーザーブレークアドレスマスクレジスタＨ	*/
	#define	SH__UBAMRL		(*(UWORD *)0xffff8606)		/**  ユーザーブレークアドレスマスクレジスタＬ	*/
	#define	SH__UBBR		(*(UWORD *)0xffff8608)		/**  ユーザーブレークバスサイクルレジスタ	*/
/**********************************************/
/*  データトランスファコントローラー（ＤＴＣ）*/
/**********************************************/
	#define	SH__DTEA		(*(UBYTE *)0xffff8700)		/**  DTCイネーブルレジスタA			*/
	#define	SH__DTEB		(*(UBYTE *)0xffff8701)		/**  DTCイネーブルレジスタB			*/
	#define	SH__DTEC		(*(UBYTE *)0xffff8702)		/**  DTCイネーブルレジスタC			*/
		#define TGIOD_ENABLE	0x80					/**  C7    */
		#define ADI_ENABLE		0x40					/**  C6    */
		#define IREQ0_ENABLE	0x20					/**  C5    */
		#define IREQ1_ENABLE	0x10					/**  C4    */
		#define IREQ2_ENABLE	0x08					/**  C3    */
		#define IREQ3_ENABLE	0x04					/**  C2    */
		#define IREQ4_ENABLE	0x02					/**  C1    */
		#define IREQ5_ENABLE	0x01					/**  C0    */
	#define	SH__DTED		(*(UBYTE *)0xffff8703)		/**  DTCイネーブルレジスタD			*/
		#define IREQ6_ENABLE	0x80					/**  D7    *//* exchange 7 to 6 By O.Kimoto 1997/09/19 */
		#define IREQ7_ENABLE	0x40					/**  D6    *//* exchange 6 to 7 By O.Kimoto 1997/09/19 */
		#define RXI1_ENABLE		0x02					/**  D1    *//* added by H.Hirao 1999/01/23 */
		#define TXI1_ENABLE		0x01					/**  D0    *//* added by H.Hirao 1999/01/23 */
	#define	SH__DTEE		(*(UBYTE *)0xffff8704)		/**  DTCイネーブルレジスタE			*/
	#define	SH__DTCSR		(*(UWORD *)0xffff8706)		/**  DTCコントロール／ステータスレジスタ	*/
		#define DTCSR_SWDTE		(UWORD)0x0100			/**  DTCソフトウェア起動 */
		#define DTCSR_AE		(UWORD)0x0200			/**  DTCアドレスエラー */
	#define	SH__DTBR		(*(UWORD *)0xffff8708)		/**  DTC情報ベースレジスタ			*/
		/* DTCモードレジスタ設定値 */
		#define DTMR_SM_INC		(UWORD)0x8000			/** DTSARは転送後増加 */
		#define DTMR_SM_DEC		(UWORD)0xC000			/** DTSARは転送後減少 */
		#define DTMR_DM_INC		(UWORD)0x2000			/** DTDARは転送後増加 */
		#define DTMR_DM_DEC		(UWORD)0x3000			/** DTDARは転送後減少 */
		#define DTMR_MD_REPEAT	(UWORD)0x0400			/** リピートモード */
		#define DTMR_MD_BLOCK	(UWORD)0x0800			/** ブロック転送モード */
		#define DTMR_SZ_WORD	(UWORD)0x0100			/** 転送サイズ・ワード */
		#define DTMR_SZ_DWORD	(UWORD)0x0200			/** 転送サイズ・ロング */
		#define DTMR_DTS_SRC	(UWORD)0x0080			/** ソース側がリピート又はブロック領域 */
		#define DTMR_CHNE_CONT	(UWORD)0x0040			/** データ転送継続 */
		#define DTMR_DISEL_SET	(UWORD)0x0020			/** インタラプトセレクト */
		#define DTMR_NMIM_CONT	(UWORD)0x0010			/** データ転送継続 */
/********************************************/
/*  キャッシュコントローラー（ＣＡＣ）		*/
/********************************************/
	#define	SH__CCR			(*(UWORD *)0xffff8740)		/**  キャッシュコントロールレジスタ	*/
		#define	CCR_DRAM_CASH_ENABLE	0x0010			/** DRAM空間キャッシュ許可			*/
		#define	CCR_CS3_CASH_ENABLE		0x0008			/** CS3空間キャッシュ許可			*/
		#define	CCR_CS2_CASH_ENABLE		0x0004			/** CS2空間キャッシュ許可			*/
		#define	CCR_CS1_CASH_ENABLE		0x0002			/** CS1空間キャッシュ許可			*/
		#define	CCR_CS0_CASH_ENABLE		0x0001			/** CS0空間キャッシュ許可			*/

/*******************************************/
/*  バスステートコントローラー・レジスター */
/*******************************************/
	#define	SH__BCR1		(*(UWORD *)0xffff8620)		/**  バスコントロールレジスタ１		*/
		#define	BCR1_MTU_WRITE_ENABLE	0x2000			/** MTUライト許可					*/
		#define	BCR1_MULTIPLEX_ENABLE	0x0100			/** マルチプレクスＩ／Ｏ許可		*/
		#define	BCR1_CS3_LONG			0x0080			/** CS3空間ロングサイズ指定			*/
		#define	BCR1_CS2_LONG			0x0040			/** CS2空間ロングサイズ指定			*/
		#define	BCR1_CS1_LONG			0x0020			/** CS1空間ロングサイズ指定			*/
		#define	BCR1_CS0_LONG			0x0010			/** CS0空間ロングサイズ指定			*/
		#define	BCR1_CS3_WORD			0x0008			/** CS3空間グサイズ指定				*/
		#define	BCR1_CS2_WORD			0x0004			/** CS2空間グサイズ指定				*/
		#define	BCR1_CS1_WORD			0x0002			/** CS1空間グサイズ指定				*/
		#define	BCR1_CS0_WORD			0x0001			/** CS0空間グサイズ指定				*/

	#define	SH__BCR2		(*(UWORD *)0xffff8622)		/**  バスコントロールレジスタ２		*/
		#define	BCR2_CS3_NO_IDLE		0x0000			/** CS3空間アイドルサイクルなし		*/
		#define	BCR2_CS3_1_IDLE			0x4000			/** CS3空間１アイドルサイクル		*/
		#define	BCR2_CS3_2_IDLE			0x8000			/** CS3空間２アイドルサイクル		*/
		#define	BCR2_CS3_3_IDLE			0xC000			/** CS3空間３アイドルサイクル		*/

		#define	BCR2_CS2_NO_IDLE		0x0000			/** CS2空間アイドルサイクルなし		*/
		#define	BCR2_CS2_1_IDLE			0x1000			/** CS2空間１アイドルサイクル		*/
		#define	BCR2_CS2_2_IDLE			0x2000			/** CS2空間２アイドルサイクル		*/
		#define	BCR2_CS2_3_IDLE			0x3000			/** CS2空間３アイドルサイクル		*/

		#define	BCR2_CS1_NO_IDLE		0x0000			/** CS1空間アイドルサイクルなし		*/
		#define	BCR2_CS1_1_IDLE			0x0400			/** CS1空間１アイドルサイクル		*/
		#define	BCR2_CS1_2_IDLE			0x0800			/** CS1空間２アイドルサイクル		*/
		#define	BCR2_CS1_3_IDLE			0x0C00			/** CS1空間３アイドルサイクル		*/

		#define	BCR2_CS0_NO_IDLE		0x0000			/** CS0空間アイドルサイクルなし		*/
		#define	BCR2_CS0_1_IDLE			0x0100			/** CS0空間１アイドルサイクル		*/
		#define	BCR2_CS0_2_IDLE			0x0200			/** CS0空間２アイドルサイクル		*/
		#define	BCR2_CS0_3_IDLE			0x0300			/** CS0空間３アイドルサイクル		*/

		#define	BCR2_CS3_CONT_1_IDLE	0x0080			/** CS3空間連続アクセス時１アイドルサイクル */
		#define	BCR2_CS2_CONT_1_IDLE	0x0040			/** CS2空間連続アクセス時１アイドルサイクル */
		#define	BCR2_CS1_CONT_1_IDLE	0x0020			/** CS1空間連続アクセス時１アイドルサイクル */
		#define	BCR2_CS0_CONT_1_IDLE	0x0010			/** CS0空間連続アクセス時１アイドルサイクル */

		#define	BCR2_CS3_ASSERT			0x0008			/** CS3空間/CSアサーと拡張有り		*/
		#define	BCR2_CS2_ASSERT			0x0004			/** CS2空間/CSアサーと拡張有り		*/
		#define	BCR2_CS1_ASSERT			0x0002			/** CS1空間/CSアサーと拡張有り		*/
		#define	BCR2_CS0_ASSERT			0x0001			/** CS0空間/CSアサーと拡張有り		*/
	#define	SH__WCR1		(*(UWORD *)0xffff8624)		/**  ウェイトコントロールレジスタ１	*/
		#define	WCR1_CS3_NO_WAIT		0x0000			/** CS3空間ノーウェイト				*/
		#define	WCR1_CS3_1WAIT			0x1000			/** CS3空間１ウェイト				*/
		#define	WCR1_CS3_2WAIT			0x2000			/** CS3空間２ウェイト				*/
		#define	WCR1_CS3_3WAIT			0x3000			/** CS3空間３ウェイト				*/
		#define	WCR1_CS3_4WAIT			0x4000			/** CS3空間４ウェイト				*//*キーポートのため追加 M.Kotani 97/10/17*/
		#define	WCR1_CS3_5WAIT			0x5000			/** CS3空間５ウェイト				*//*キーポートのため追加 M.Kotani 97/10/17*/
		#define	WCR1_CS3_6WAIT			0x6000			/** CS3空間６ウェイト				*//*キーポートのため追加 M.Kotani 97/10/17*/
		#define	WCR1_CS3_7WAIT			0x7000			/** CS3空間７ウェイト				*//*キーポートのため追加 M.Kotani 97/10/17*//*キーポートのため追加 M.Kotani 97/10/17*/
		#define	WCR1_CS3_8WAIT			0x8000			/** CS3空間８ウェイト				*//*キーポートのため追加 M.Kotani 97/10/17*/
		#define	WCR1_CS3_9WAIT			0x9000			/** CS3空間９ウェイト				*//*キーポートのため追加 M.Kotani 97/10/17*/
		#define	WCR1_CS3_10WAIT			0xA000			/** CS3空間１０ウェイト				*//*キーポートのため追加 M.Kotani 97/10/17*/
		#define	WCR1_CS3_15WAIT			0xF000			/** CS3空間１５ウェイト				*/

		#define	WCR1_CS2_NO_WAIT		0x0000			/** CS2空間ノーウェイト				*/
		#define	WCR1_CS2_1WAIT			0x0100			/** CS2空間１ウェイト				*/
		#define	WCR1_CS2_2WAIT			0x0200			/** CS2空間２ウェイト				*/
		#define	WCR1_CS2_3WAIT			0x0300			/** CS2空間３ウェイト				*/
		#define	WCR1_CS2_6WAIT			0x0600			/** CS2空間６ウェイト				*/
		#define	WCR1_CS2_15WAIT			0x0F00			/** CS2空間１５ウェイト				*/

		#define	WCR1_CS1_NO_WAIT		0x0000			/** CS1空間ノーウェイト				*/
		#define	WCR1_CS1_1WAIT			0x0010			/** CS1空間１ウェイト				*/
		#define	WCR1_CS1_2WAIT			0x0020			/** CS1空間２ウェイト				*/
		#define	WCR1_CS1_3WAIT			0x0030			/** CS1空間３ウェイト				*/
		#define	WCR1_CS1_15WAIT			0x00F0			/** CS1空間１５ウェイト				*/

		#define	WCR1_CS0_NO_WAIT		0x0000			/** CS3空間ノーウェイト				*/
		#define	WCR1_CS0_1WAIT			0x0001			/** CS3空間１ウェイト				*/
		#define	WCR1_CS0_2WAIT			0x0002			/** CS3空間２ウェイト				*/
		#define	WCR1_CS0_3WAIT			0x0003			/** CS3空間３ウェイト				*/
		#define	WCR1_CS0_15WAIT			0x000F			/** CS3空間１５ウェイト				*/
	#define	SH__WCR2		(*(UWORD *)0xffff8626)		/**  ウェイトコントロールレジスタ２	*/
		#define	WCR2_DRAM_DMA_NO_WAIT	0x0000			/** DRAM空間DMAノーウェイト			*/
		#define	WCR2_DRAM_DMA_1WAIT		0x0010			/** DRAM空間DMA１ウェイト			*/
		#define	WCR2_DRAM_DMA_2WAIT		0x0020			/** DRAM空間DMA２ウェイト			*/
		#define	WCR2_DRAM_DMA_3WAIT		0x0030			/** DRAM空間DMA３ウェイト			*/

		#define	WCR2_CS_DMA_NO_WAIT		0x0000			/** CS空間DMAノーウェイト			*/
		#define	WCR2_CS_DMA_1WAIT		0x0001			/** CS空間DMA１ウェイト				*/
		#define	WCR2_CS_DMA_2WAIT		0x0002			/** CS空間DMA２ウェイト				*/
		#define	WCR2_CS_DMA_15WAIT		0x000F			/** CS空間DMA１５ウェイト			*/

	#define	SH__DCR			(*(UWORD *)0xffff862A)		/**  DRAMエリアコントロールレジスタ			*/
		#define	DCR_RAS_PRECHARGE_25CYCLE	0x8000		/** RASプリチャージ 1.5/2.5サイクル */
		#define DCR_RAS_DELAY_2CYCLE	0x4000			/** RAS-CAS遅延サイクル数 1/2サイクル */

		#define DCR_RAS_AST_25CYCLE		0x0000			/** CASﾋﾞﾌｫｱRASﾘﾌﾚｯｼｭRASｱｻｰﾄｻｲｸﾙ 2.5ｻｲｸﾙ */
		#define DCR_RAS_AST_35CYCLE		0x1000			/** CASﾋﾞﾌｫｱRASﾘﾌﾚｯｼｭRASｱｻｰﾄｻｲｸﾙ 3.5ｻｲｸﾙ */
		#define DCR_RAS_AST_45CYCLE		0x2000			/** CASﾋﾞﾌｫｱRASﾘﾌﾚｯｼｭRASｱｻｰﾄｻｲｸﾙ 4.5ｻｲｸﾙ */
		#define DCR_RAS_AST_55CYCLE		0x3000			/** CASﾋﾞﾌｫｱRASﾘﾌﾚｯｼｭRASｱｻｰﾄｻｲｸﾙ 5.5ｻｲｸﾙ */

		#define DCR_DRAM_WR_2CYCLE		0x0000			/** ＤＲＡＭライトサイクル２サイクル */
		#define DCR_DRAM_WR_3CYCLE		0x0400			/** ＤＲＡＭライトサイクル３サイクル */
		#define DCR_DRAM_WR_4CYCLE		0x0800			/** ＤＲＡＭライトサイクル４サイクル */
		#define DCR_DRAM_WR_5CYCLE		0x0C00			/** ＤＲＡＭライトサイクル５サイクル */

		#define DCR_DRAM_RD_2CYCLE		0x0000			/** ＤＲＡＭリードサイクル２サイクル */
		#define DCR_DRAM_RD_3CYCLE		0x0100			/** ＤＲＡＭリードサイクル３サイクル */
		#define DCR_DRAM_RD_4CYCLE		0x0200			/** ＤＲＡＭリードサイクル４サイクル */
		#define DCR_DRAM_RD_5CYCLE		0x0300			/** ＤＲＡＭリードサイクル５サイクル */

		#define DCR_DRAM_IDLE_1CYCLE	0x0080			/** ＤＲＡＭアイドル１サイクル       */
		#define DCR_BURST_ENABLE		0x0020			/** ＤＲＡＭバースト許可             */
		#define DCR_RAS_DOWN_MODE		0x0010			/** ＲＡＳダウンモードでＤＲＡＭアクセス */

		#define DCR_DRAMBASS_BYTE		0x0000			/** ＤＲＡＭバス幅バイトサイズ指定   */
		#define DCR_DRAMBASS_WORD		0x0004			/** ＤＲＡＭバス幅ワードサイズ指定   */
		#define DCR_DRAMBASS_LONG		0x0008			/** ＤＲＡＭバス幅ロングサイズ指定   */

		#define DCR_AMX_9BIT			0x0000			/** アドレスマルチプレクス９ビット   */
		#define DCR_AMX_10BIT			0x0001			/** アドレスマルチプレクス１０ビット */
		#define DCR_AMX_11BIT			0x0002			/** アドレスマルチプレクス１１ビット */
		#define DCR_AMX_12BIT			0x0003			/** アドレスマルチプレクス１２ビット */

	#define	SH__RTCSR		(*(UWORD *)0xffff862C)		/**  リフレッシュタイマーコントロール／ステータスレジスタ */
		#define RTCSR_CMIE				0x0040			/** コンペアマッチによる割込許可     */

		#define RTCSR_CLK_STOP			0x0000			/** カウントアップ停止               */
		#define RTCSR_CLK_2				0x0004			/** システムクロック／２             */
		#define RTCSR_CLK_8				0x0008			/** システムクロック／８             */
		#define RTCSR_CLK_32			0x000C			/** システムクロック／３２           */
		#define RTCSR_CLK_128			0x0010			/** システムクロック／１２８         */
		#define RTCSR_CLK_512			0x0014			/** システムクロック／５１２         */
		#define RTCSR_CLK_2048			0x0018			/** システムクロック／２０４８       */
		#define RTCSR_CLK_4096			0x001C			/** システムクロック／４０９６       */

		#define RTSC_RFSH_ENABLE		0x0002			/** ＤＲＡＭリフレッシュをする       */
		#define RTSC_RMD_SELF			0x0001			/** セルフリフレッシュモード         */

	#define	SH__RTCNT		(*(UWORD *)0xffff862E)		/**  リフレッシュタイマーカウンタ			*/
	#define	SH__RTCOR		(*(UWORD *)0xffff8630)		/**  リフレッシュタイムコンスタントレジスタ	*/


/*******************************************/
/*  ダイレクトメモリアクセスコントローラー */
/*******************************************/
	/*--＜チャンネル０＞------------------------------------------------------------------------*/
	#define	DMA__SAR0		(*(UDWORD *)0xffff86C0)		/** ＤＭＡソースアドレスレジスタ０ */
	#define	DMA__DAR0		(*(UDWORD *)0xffff86C4)		/** ＤＭＡデスティネーションアドレスレジスタ０ */
	#define	DMA__TCR0		(*(UDWORD *)0xffff86C8)		/** ＤＭＡトランスファカウントレジスタ０ */
	#define	DMA__CHCR0		(*(UDWORD *)0xffff86CC)		/** ＤＭＡチャンネルコントロールレジスタ０ */
	/*--＜チャンネル１＞------------------------------------------------------------------------*/
	#define	DMA__SAR1		(*(UDWORD *)0xffff86D0)		/** ＤＭＡソースアドレスレジスタ１ */
	#define	DMA__DAR1		(*(UDWORD *)0xffff86D4)		/** ＤＭＡデスティネーションアドレスレジスタ１ */
	#define	DMA__TCR1		(*(UDWORD *)0xffff86D8)		/** ＤＭＡトランスファカウントレジスタ１ */
	#define	DMA__CHCR1		(*(UDWORD *)0xffff86DC)		/** ＤＭＡチャンネルコントロールレジスタ１ */
	/*--＜チャンネル２＞------------------------------------------------------------------------*/
	#define	DMA__SAR2		(*(UDWORD *)0xffff86E0)		/** ＤＭＡソースアドレスレジスタ２ */
	#define	DMA__DAR2		(*(UDWORD *)0xffff86E4)		/** ＤＭＡデスティネーションアドレスレジスタ２ */
	#define	DMA__TCR2		(*(UDWORD *)0xffff86E8)		/** ＤＭＡトランスファカウントレジスタ２ */
	#define	DMA__CHCR2		(*(UDWORD *)0xffff86EC)		/** ＤＭＡチャンネルコントロールレジスタ２ */
	/*--＜チャンネル３＞------------------------------------------------------------------------*/
	#define	DMA__SAR3		(*(UDWORD *)0xffff86F0)		/** ＤＭＡソースアドレスレジスタ３ */
	#define	DMA__DAR3		(*(UDWORD *)0xffff86F4)		/** ＤＭＡデスティネーションアドレスレジスタ３ */
	#define	DMA__TCR3		(*(UDWORD *)0xffff86F8)		/** ＤＭＡトランスファカウントレジスタ３ */
	#define	DMA__CHCR3		(*(UDWORD *)0xffff86FC)		/** ＤＭＡチャンネルコントロールレジスタ３ */
	/*-----------------------------------------------------------------------------------------*/

#if (0)
** 	/* ＨＩＮＯＫＩは、ＬＯＴＵＳ／ＫＵＲＵＭＩから移植します。
** 	** でも、向こうは、Volatile宣言を使っているので、Defineがあいません。
** 	** ゆえに、ＨＩＮＯＫＩ固有の部分に関しては、ＬＯＴＵＳ／ＫＵＲＵＭＩに
** 	** 合わせることにします。
** 	**  1998/10/05 by T.Soneoka
** 	*/
#endif
/*--＜チャンネル０＞------------------------------------------------------------------------*/
extern volatile UDWORD	dma_sar0;		/* 0xffff86C0：* ＤＭＡソースアドレスレジスタ０ */
extern volatile UDWORD	dma_dar0;		/* 0xffff86C4：* ＤＭＡデスティネーションアドレスレジスタ０ */
extern volatile UDWORD	dma_tcr0;		/* 0xffff86C8：* ＤＭＡトランスファカウントレジスタ０ */
extern volatile UDWORD	dma_chcr0;		/* 0xffff86CC：* ＤＭＡチャンネルコントロールレジスタ０ */
/*--＜チャンネル１＞------------------------------------------------------------------------*/
extern volatile UDWORD	dma_sar1;		/* 0xffff86D0：* ＤＭＡソースアドレスレジスタ１ */
extern volatile UDWORD	dma_dar1;		/* 0xffff86D4：* ＤＭＡデスティネーションアドレスレジスタ１ */
extern volatile UDWORD	dma_tcr1;		/* 0xffff86D8：* ＤＭＡトランスファカウントレジスタ１ */
extern volatile UDWORD	dma_chcr1;		/* 0xffff86DC：* ＤＭＡチャンネルコントロールレジスタ１ */
/*--＜チャンネル２＞------------------------------------------------------------------------*/
extern volatile UDWORD	dma_sar2;		/* 0xffff86E0：* ＤＭＡソースアドレスレジスタ２ */
extern volatile UDWORD	dma_dar2;		/* 0xffff86E4：* ＤＭＡデスティネーションアドレスレジスタ２ */
extern volatile UDWORD	dma_tcr2;		/* 0xffff86E8：* ＤＭＡトランスファカウントレジスタ２ */
extern volatile UDWORD	dma_chcr2;		/* 0xffff86EC：* ＤＭＡチャンネルコントロールレジスタ２ */
/*--＜チャンネル３＞------------------------------------------------------------------------*/
extern volatile UDWORD	dma_sar3;		/* 0xffff86F0：* ＤＭＡソースアドレスレジスタ３ */
extern volatile UDWORD	dma_dar3;		/* 0xffff86F4：* ＤＭＡデスティネーションアドレスレジスタ３ */
extern volatile UDWORD	dma_tcr3;		/* 0xffff86F8：* ＤＭＡトランスファカウントレジスタ３ */
extern volatile UDWORD	dma_chcr3;		/* 0xffff86FC：* ＤＭＡチャンネルコントロールレジスタ３ */
	/*--＜チャンネル０＞------------------------------------------------------------------------*/
	#define	DMA_SAR0		&dma_sar0								/** ＤＭＡソースアドレスレジスタ０ */
	#define	DMA_DAR0		&dma_dar0								/** ＤＭＡデスティネーションアドレスレジスタ０ */
	#define	DMA_TCR0		&dma_tcr0								/** ＤＭＡトランスファカウントレジスタ０ */
	#define	DMA_CHCR0		&dma_chcr0								/** ＤＭＡチャンネルコントロールレジスタ０ */
	/*--＜チャンネル１＞------------------------------------------------------------------------------------*/
	#define	DMA_SAR1		&dma_sar1								/** ＤＭＡソースアドレスレジスタ１ */
	#define	DMA_DAR1		&dma_dar1								/** ＤＭＡデスティネーションアドレスレジスタ１ */
	#define	DMA_TCR1		&dma_tcr1								/** ＤＭＡトランスファカウントレジスタ１ */
	#define	DMA_CHCR1		&dma_chcr1								/** ＤＭＡチャンネルコントロールレジスタ１ */
	/*--＜チャンネル２＞------------------------------------------------------------------------------------*/
	#define	DMA_SAR2		&dma_sar2								/** ＤＭＡソースアドレスレジスタ２ */
	#define	DMA_DAR2		&dma_dar2								/** ＤＭＡデスティネーションアドレスレジスタ２ */
	#define	DMA_TCR2		&dma_tcr2								/** ＤＭＡトランスファカウントレジスタ２ */
	#define	DMA_CHCR2		&dma_chcr2								/** ＤＭＡチャンネルコントロールレジスタ２ */
	/*--＜チャンネル３＞------------------------------------------------------------------------------------*/
	#define	DMA_SAR3		&dma_sar3								/** ＤＭＡソースアドレスレジスタ３ */
	#define	DMA_DAR3		&dma_dar3								/** ＤＭＡデスティネーションアドレスレジスタ３ */
	#define	DMA_TCR3		&dma_tcr3								/** ＤＭＡトランスファカウントレジスタ３ */
	#define	DMA_CHCR3		&dma_chcr3								/** ＤＭＡチャンネルコントロールレジスタ３ */
	/*-----------------------------------------------------------------------------------------*/

		/*--<各チャネルのＣＨＣＲレジスタビットアサイン>-------------------------------------*/
		#define CHCR_DI			0x00100000				/** チャネル３間接アドレスモード   */
		#define CHCR_RO			0x00080000				/** チャネル２ソースアドレスリロード */
		#define CHCR_RL			0x00040000				/** リクエストチェックレベルローアクティブ */
		#define CHCR_AM			0x00020000				/** アクノリッジモード書き込みサイクル */
		#define CHCR_AL			0x00010000				/** アクノリッジレベルローアクティブ */

		#define CHCR_DM_RGD		0x00000000				/** デスティネーションアドレス固定 */
		#define CHCR_DM_INC		0x00004000				/** デスティネーションアドレス増加 */
		#define CHCR_DM_DEC		0x00008000				/** デスティネーションアドレス減少 */

		#define CHCR_SM_RGD		0x00000000				/** ソースアドレス固定             */
		#define CHCR_SM_INC		0x00001000				/** ソースアドレス増加             */
		#define CHCR_SM_DEC		0x00002000				/** ソースアドレス減少             */

		#define CHCR_RS_DUAL	0x00000000				/** 外部リクエスト、デュアルアドレスモード */
		#define CHCR_RS_MEM_IO	0x00000200				/** 外部リクエスト、外部メモリー→外部Ｉ／Ｏ */
		#define CHCR_RS_IO_MEM	0x00000300				/** 外部リクエスト、外部Ｉ／Ｏ→外部メモリー */
		#define CHCR_RS_AUTO	0x00000400				/** オートリクエスト               */
		#define CHCR_RS_TGI0A	0x00000600				/** 内部リクエスト、ＴＧＩＡ０     */
		#define CHCR_RS_TGI1A	0x00000700				/** 内部リクエスト、ＴＧＩＡ１     */
		#define CHCR_RS_TGI2A	0x00000800				/** 内部リクエスト、ＴＧＩＡ２     */
		#define CHCR_RS_TGI3A	0x00000900				/** 内部リクエスト、ＴＧＩＡ３     */
		#define CHCR_RS_TGI4A	0x00000A00				/** 内部リクエスト、ＴＧＩＡ４     */
		#define CHCR_RS_ADI		0x00000B00				/** 内部リクエスト、Ａ／Ｄ         */
		#define CHCR_RS_TXI0	0x00000C00				/** 内部リクエスト、ＴＸＩ０       */
		#define CHCR_RS_RXI0	0x00000D00				/** 内部リクエスト、ＲＸＩ０       */
		#define CHCR_RS_TXI1	0x00000E00				/** 内部リクエスト、ＴＸＩ１       */
		#define CHCR_RS_RXI1	0x00000F00				/** 内部リクエスト、ＲＸＩ１       */
		#define CHCR_RS_MASK	0x00000F00				/** リソースセレクトマスク         */

		#define CHCR_DS			0x00000040				/** ＤＲＥＱ立ち下がり検出         */
		#define CHCR_TM			0x00000020				/** 転送モード、バースト転送       */

		#define CHCR_TS_BYTE	0x00000000				/** 転送サイズ、バイトサイズ       */
		#define CHCR_TS_WORD	0x00000008				/** 転送サイズ、ワードサイズ       */
		#define CHCR_TS_LONG	0x00000010				/** 転送サイズ、ロングサイズ       */
		#define CHCR_TS_MASK	0x00000018				/** 転送サイズマスク               */

		#define CHCR_IE			0x00000004				/** ＴＣ割込み許可                 */
		#define CHCR_TE			0x00000002				/** ＤＭＡＴＣフラグ               */
		#define CHCR_DE			0x00000001				/** ＤＲＥＱイネーブル             */

	#define	DMA__DMAOPR		(*(UDWORD *)0xffff86B0)		/** ＤＭＡオペレーションレジスタ   */
		#define DMAOPR_0123		0x0000					/** チャネル優先順位 CH0>CH1>CH2>CH3 */
		#define DMAOPR_0231		0x0100					/** チャネル優先順位 CH0>CH2>CH3>CH1 */
		#define DMAOPR_2013		0x0200					/** チャネル優先順位 CH2>CH0>CH1>CH3 */
		#define DMAOPR_RTRY		0x0300					/** チャネル優先順位 ラウンドロビン */
		#define DMAOPR_AE		0x0004					/** アドレスエラーフラグ           */
		#define DMAOPR_NMIF		0x0002					/** ＮＭＩフラグ                   */
		#define DMAOPR_DME		0x0001					/** ＤＭＡＣマスターイネーブル     */

/*****************************************************/
/*  １６ビットインテグレーテッドタイマパルスユニット */
/*****************************************************/
	/** ＳＨ７０４Ｘにはこのユニットは存在しない。 */
/*****************************************************/
/*  マルチファンクションタイマパルスユニット 		 */
/*****************************************************/
	/*--＜チャンネル共通＞----------------------------------------------------------------------*/
	#define	MTU__TSTR		(*(UBYTE *)0xffff8240)		/**  タイマースタートレジスタ		*/
		#define	TSTR_START_CH0			0x01			/** Ｃｈ．０カウンタスタート		*/
		#define	TSTR_START_CH1			0x02			/** Ｃｈ．１カウンタスタート		*/
		#define	TSTR_START_CH2			0x04			/** Ｃｈ．２カウンタスタート		*/
		#define	TSTR_START_CH3			0x40			/** Ｃｈ．３カウンタスタート		*/
		#define	TSTR_START_CH4			0x80			/** Ｃｈ．４カウンタスタート		*/
	#define	MTU__TSYR		(*(UBYTE *)0xffff8241)		/**  タイマーシンクロレジスタ		*/
	/*--＜チャンネル０＞------------------------------------------------------------------------*/
	#define	MTU__TCR0		(*(UBYTE *)0xffff8260)		/**  タイマーコントロールレジスタ０	*/
	#define	MTU__TMDR0		(*(UBYTE *)0xffff8261)		/**  タイマーモードレジスタ０		*/
	#define	MTU__TIOR0H		(*(UBYTE *)0xffff8262)		/**  タイマーＩ／Ｏコントロールレジスタ０Ｈ*/
	#define	MTU__TIOR0L		(*(UBYTE *)0xffff8263)		/**  タイマーＩ／Ｏコントロールレジスタ０Ｌ*/
	#define	MTU__TIER0		(*(UBYTE *)0xffff8264)		/**  タイマーインターラプトイネーブルレジスタ０*/
	#define	MTU__TSR0		(*(UBYTE *)0xffff8265)		/**  タイマーステータスレジスタ０	*/
	#define	MTU__TCNT0		(*(UWORD *)0xffff8266)		/**  タイマーカウンタ０				*/
	#define	MTU__TGR0A		(*(UWORD *)0xffff8268)		/**  ジェネラルレジスタ０Ａ			*/
	#define	MTU__TGR0B		(*(UWORD *)0xffff826A)		/**  ジェネラルレジスタ０Ｂ			*/
	#define	MTU__TGR0C		(*(UWORD *)0xffff826C)		/**  ジェネラルレジスタ０Ｃ			*/
	#define	MTU__TGR0D		(*(UWORD *)0xffff826E)		/**  ジェネラルレジスタ０Ｄ			*/
	/*--＜チャンネル１＞------------------------------------------------------------------------*/
	#define	MTU__TCR1		(*(UBYTE *)0xffff8280)		/**  タイマーコントロールレジスタ１	*/
	#define	MTU__TMDR1		(*(UBYTE *)0xffff8281)		/**  タイマーモードレジスタ１		*/
	#define	MTU__TIOR1		(*(UBYTE *)0xffff8282)		/**  タイマーＩ／Ｏコントロールレジスタ１*/
	#define	MTU__TIER1		(*(UBYTE *)0xffff8284)		/**  タイマーインターラプトイネーブルレジスタ１*/
	#define	MTU__TSR1		(*(UBYTE *)0xffff8285)		/**  タイマーステータスレジスタ１	*/
	#define	MTU__TCNT1		(*(UWORD *)0xffff8286)		/**  タイマーカウンタ１				*/
	#define	MTU__TGR1A		(*(UWORD *)0xffff8288)		/**  ジェネラルレジスタ１Ａ			*/
	#define	MTU__TGR1B		(*(UWORD *)0xffff828A)		/**  ジェネラルレジスタ１Ｂ			*/
	/*--＜チャンネル２＞------------------------------------------------------------------------*/
	#define	MTU__TCR2		(*(UBYTE *)0xffff82A0)		/**  タイマーコントロールレジスタ２	*/
	#define	MTU__TMDR2		(*(UBYTE *)0xffff82A1)		/**  タイマーモードレジスタ２		*/
	#define	MTU__TIOR2		(*(UBYTE *)0xffff82A2)		/**  タイマーＩ／Ｏコントロールレジスタ２*/
	#define	MTU__TIER2		(*(UBYTE *)0xffff82A4)		/**  タイマーインターラプトイネーブルレジスタ２*/
	#define	MTU__TSR2		(*(UBYTE *)0xffff82A5)		/**  タイマーステータスレジスタ２	*/
	#define	MTU__TCNT2		(*(UWORD *)0xffff82A6)		/**  タイマーカウンタ２				*/
	#define	MTU__TGR2A		(*(UWORD *)0xffff82A8)		/**  ジェネラルレジスタ２Ａ			*/
	#define	MTU__TGR2B		(*(UWORD *)0xffff82AA)		/**  ジェネラルレジスタ２Ｂ			*/
	/*--＜チャンネル３＞------------------------------------------------------------------------*/
	#define	MTU__TCR3		(*(UBYTE *)0xffff8200)		/**  タイマーコントロールレジスタ３	*/
	#define	MTU__TMDR3		(*(UBYTE *)0xffff8202)		/**  タイマーモードレジスタ３		*/
	#define	MTU__TIOR3H		(*(UBYTE *)0xffff8204)		/**  タイマーＩ／Ｏコントロールレジスタ３Ｈ*/
	#define	MTU__TIOR3L		(*(UBYTE *)0xffff8205)		/**  タイマーＩ／Ｏコントロールレジスタ３Ｌ*/
	#define	MTU__TIER3		(*(UBYTE *)0xffff8208)		/**  タイマーインターラプトイネーブルレジスタ３*/
	#define	MTU__TSR3		(*(UBYTE *)0xffff822C)		/**  タイマーステータスレジスタ３	*/
	#define	MTU__TCNT3		(*(UWORD *)0xffff8210)		/**  タイマーカウンタ３				*/
	#define	MTU__TGR3A		(*(UWORD *)0xffff8218)		/**  ジェネラルレジスタ３Ａ			*/
	#define	MTU__TGR3B		(*(UWORD *)0xffff821A)		/**  ジェネラルレジスタ３Ｂ			*/
	#define	MTU__TGR3C		(*(UWORD *)0xffff8224)		/**  ジェネラルレジスタ３Ｃ			*/
	#define	MTU__TGR3D		(*(UWORD *)0xffff8226)		/**  ジェネラルレジスタ３Ｄ			*/
	/*--＜チャンネル４＞------------------------------------------------------------------------*/
	#define	MTU__TCR4		(*(UBYTE *)0xffff8201)		/**  タイマーコントロールレジスタ４	*/
	#define	MTU__TMDR4		(*(UBYTE *)0xffff8203)		/**  タイマーモードレジスタ４		*/
	#define	MTU__TIOR4H		(*(UBYTE *)0xffff8206)		/**  タイマーＩ／Ｏコントロールレジスタ４Ｈ*/
	#define	MTU__TIOR4L		(*(UBYTE *)0xffff8207)		/**  タイマーＩ／Ｏコントロールレジスタ４Ｌ*/
	#define	MTU__TIER4		(*(UBYTE *)0xffff8209)		/**  タイマーインターラプトイネーブルレジスタ４*/
	#define	MTU__TSR4		(*(UBYTE *)0xffff822D)		/**  タイマーステータスレジスタ４	*/
	#define	MTU__TCNT4		(*(UWORD *)0xffff8212)		/**  タイマーカウンタ４				*/
	#define	MTU__TGR4A		(*(UWORD *)0xffff821C)		/**  ジェネラルレジスタ４Ａ			*/
	#define	MTU__TGR4B		(*(UWORD *)0xffff821E)		/**  ジェネラルレジスタ４Ｂ			*/
	#define	MTU__TGR4C		(*(UWORD *)0xffff8228)		/**  ジェネラルレジスタ４Ｃ			*/
	#define	MTU__TGR4D		(*(UWORD *)0xffff822A)		/**  ジェネラルレジスタ４Ｄ			*/
	/*--＜チャンネル３／４共通＞----------------------------------------------------------------*/
	#define	MTU__TOER		(*(UBYTE *)0xffff820A)		/**  タイマーアウトプットマスターイネーブルレジスタ*/
	#define	MTU__TOCR		(*(UBYTE *)0xffff820B)		/**  タイマーアウトプットコントロールレジスタ*/
	#define	MTU__TGCR		(*(UBYTE *)0xffff820D)		/**  タイマーゲートコントロールレジスタ*/
	#define	MTU__TCDR		(*(UWORD *)0xffff8214)		/**  タイマー周期データレジスタ		*/
	#define	MTU__TDDR		(*(UWORD *)0xffff8216)		/**  タイマーデッドタイムデータレジスタ*/
	#define	MTU__TCNTS		(*(UWORD *)0xffff8220)		/**  タイマーサブカウンタ			*/
	#define	MTU__TCBR		(*(UWORD *)0xffff8222)		/**  タイマー周期バッファレジスタ	*/

/*****************************************************/
/*  ウオッチドックタイマ							 */
/*****************************************************/
	#define	WDT__TCSR		(*(UBYTE *)0xffff8610)		/**  タイマーコントロール／ステータスレジスタ */
	#define	WDT__TCNT		(*(UBYTE *)0xffff8611)		/**  タイマーカウンタ				*/
	#define	WDT__RSTCSR		(*(UBYTE *)0xffff8612)		/**  リセットコントロール／ステータスレジスタ*/
/*****************************************************/
/*  シリアルコミュニケーションインターフェース		 */
/*****************************************************/
#if (0)
** 	/* ＨＩＮＯＫＩは、ＬＯＴＵＳ／ＫＵＲＵＭＩから移植します。
** 	** でも、向こうは、Volatile宣言を使っているので、Defineがあいません。
** 	** ゆえに、ＨＩＮＯＫＩ固有の部分に関しては、ＬＯＴＵＳ／ＫＵＲＵＭＩに
** 	** 合わせることにします。
** 	** By O.Kimoto 1998/09/21
** 	*/
** 	/*--＜チャンネル０＞------------------------------------------------------------------------*/
** 	#define	SCI__SMR0		(*(UBYTE *)0xffff81A0)		/**  シリアルモードレジスタ			*/
** 	#define	SCI__BRR0		(*(UBYTE *)0xffff81A1)		/**  ビットレートレジスタ			*/
** 	#define	SCI__SCR0		(*(UBYTE *)0xffff81A2)		/**  シリアルコントロールレジスタ	*/
** 	#define	SCI__TDR0		(*(UBYTE *)0xffff81A3)		/**  トランスミットデータレジスタ	*/
** 	#define	SCI__SSR0		(*(UBYTE *)0xffff81A4)		/**  シリアルステータスレジスタ		*/
** 	#define	SCI__RDR0		(*(UBYTE *)0xffff81A5)		/**  レシーブデータレジスタ			*/
** 	/*--＜チャンネル１＞------------------------------------------------------------------------*/
** 	#define	SCI__SMR1		(*(UBYTE *)0xffff81B0)		/**  シリアルモードレジスタ			*/
** 	#define	SCI__BRR1		(*(UBYTE *)0xffff81B1)		/**  ビットレートレジスタ			*/
** 	#define	SCI__SCR1		(*(UBYTE *)0xffff81B2)		/**  シリアルコントロールレジスタ	*/
** 	#define	SCI__TDR1		(*(UBYTE *)0xffff81B3)		/**  トランスミットデータレジスタ	*/
** 	#define	SCI__SSR1		(*(UBYTE *)0xffff81B4)		/**  シリアルステータスレジスタ		*/
** 	#define	SCI__RDR1		(*(UBYTE *)0xffff81B5)		/**  レシーブデータレジスタ			*/
#else
	/*--＜チャンネル０＞------------------------------------------------------------------------*/
	extern	volatile UBYTE	sci_smr0;		/* (0xffff81A0)	  シリアルモードレジスタ			*/
	extern	volatile UBYTE	sci_brr0;		/* (0xffff81A1)	  ビットレートレジスタ			*/
	extern	volatile UBYTE	sci_scr0;		/* (0xffff81A2)	  シリアルコントロールレジスタ	*/
	extern	volatile UBYTE	sci_tdr0;		/* (0xffff81A3)	  トランスミットデータレジスタ	*/
	extern	volatile UBYTE	sci_ssr0;		/* (0xffff81A4)	  シリアルステータスレジスタ		*/
	extern	volatile UBYTE	sci_rdr0;		/* (0xffff81A5)	  レシーブデータレジスタ			*/
	/*--＜チャンネル１＞------------------------------------------------------------------------*/
	extern	volatile UBYTE	sci_smr1;		/* (0xffff81B0)	  シリアルモードレジスタ			*/
	extern	volatile UBYTE	sci_brr1;		/* (0xffff81B1)	  ビットレートレジスタ			*/
	extern	volatile UBYTE	sci_scr1;		/* (0xffff81B2)	  シリアルコントロールレジスタ	*/
	extern	volatile UBYTE	sci_tdr1;		/* (0xffff81B3)	  トランスミットデータレジスタ	*/
	extern	volatile UBYTE	sci_ssr1;		/* (0xffff81B4)	  シリアルステータスレジスタ		*/
	extern	volatile UBYTE	sci_rdr1;		/* (0xffff81B5)	  レシーブデータレジスタ			*/

	/*--＜チャンネル０＞------------------------------------------------------------------------*/
	#define	SCI_SMR0	&sci_smr0	/**  シリアルモードレジスタ			*/
	#define	SCI_BRR0	&sci_brr0	/**  ビットレートレジスタ			*/
	#define	SCI_SCR0	&sci_scr0	/**  シリアルコントロールレジスタ	*/
	#define	SCI_TDR0	&sci_tdr0	/**  トランスミットデータレジスタ	*/
	#define	SCI_SSR0	&sci_ssr0	/**  シリアルステータスレジスタ		*/
	#define	SCI_RDR0	&sci_rdr0	/**  レシーブデータレジスタ			*/
	/*--＜チャンネル１＞------------------------------------------------------------------------*/
	#define	SCI_SMR1	&sci_smr1	/**  シリアルモードレジスタ			*/
	#define	SCI_BRR1	&sci_brr1	/**  ビットレートレジスタ			*/
	#define	SCI_SCR1	&sci_scr1	/**  シリアルコントロールレジスタ	*/
	#define	SCI_TDR1	&sci_tdr1	/**  トランスミットデータレジスタ	*/
	#define	SCI_SSR1	&sci_ssr1	/**  シリアルステータスレジスタ		*/
	#define	SCI_RDR1	&sci_rdr1	/**  レシーブデータレジスタ			*/
#endif

	/*--<< ＳＣＲ(シリアルコントロールレジスタ)ビットアサイン >>------------*/
	/* 以下の設定は、Jason\prj\Src\inc\cpu_map.hからコピーしました By O.Kimoto 1998/09/21 */
		#define	SCR_TIE		0x80	/* 送信データエンプティ割り込み要求許可 */
		#define	SCR_RIE		0x40	/* 受信データフル割り込み要求許可 */
		#define	SCR_TE		0x20	/* 送信動作許可 */
		#define	SCR_RE		0x10	/* 受信動作許可 */
		#define	SCR_MPIE	0x08	/* マルチプロセッサ割り込み許可 */
		#define	SCR_TEIE	0x04	/* 送信終了要求許可 */
		#define	SCR_CKE1	0x02	/* クロックイネーブル１ */
		#define	SCR_CKE0	0x01	/* クロックイネーブル０ */
	/*--<< ＳＳＲ(シリアルステータスレジスタ)ビットアサイン >>--------------*/
		#define	SSR_TDRE	0x80	/* トランスミットデータレジスタエンプティ*/
		#define	SSR_RDRF	0x40	/* レシーブデータレジスタフル */
		#define	SSR_ORER	0x20	/* オーバランエラー */
		#define	SSR_FER		0x10	/* フレーミングエラー */
		#define	SSR_PER		0x08	/* パリティエラー */
		#define	SSR_TEND	0x04	/* トランスミットエンド */
		#define	SSR_MPB		0x02	/* マルチプロセッサビット */
		#define	SSR_MPBT	0x01	/* マルチプロセッサビットトランスファ */
	/*--<< ＳＭＲ(シリアルモードレジスタ)ビットアサイン >>--------------*/
		#define SMR_CA				0x80	/* Clock同期式 */
		#define SMR_CHR_7BIT		0x40	/* 7Bit長 */
		#define SMR_PE				0x20	/* ParityEnable */
		#define SMR_ODD				0x10	/* Parity奇数 */
		#define SMR_STOP2			0x08	/* StopBit 2Bit */
		#define SMR_MP				0x04	/* MultiProcessorMode */
		#define SMR_CLK_MASK		0x03	/* Clock Mask Pattern */
/*****************************************************/
/*  コンペアマッチタイマ							 */
/*****************************************************/
	/*--＜共通＞--------------------------------------------------------------------------------*/
	#define	CMT__CMSTR		(*(UWORD *)0xffff83D0)		/**  コンペアマッチタイマースタートレジスタ*/
	/*--＜チャンネル０＞------------------------------------------------------------------------*/
	#define	CMT__CMCSR0		(*(UWORD *)0xffff83D2)		/**  コンペアマッチタイマーコントロール／ステータスレジスタ*/
	#define	CMT__CMCNT0		(*(UWORD *)0xffff83D4)		/**  コンペアマッチカウンタ０		*/
	#define	CMT__CMCOR0		(*(UWORD *)0xffff83D6)		/**  コンペアマッチコンスタントレジスタ０*/
	/*--＜チャンネル１＞------------------------------------------------------------------------*/
	#define	CMT__CMCSR1		(*(UWORD *)0xffff83D8)		/**  コンペアマッチタイマーコントロール／ステータスレジスタ*/
	#define	CMT__CMCNT1		(*(UWORD *)0xffff83DA)		/**  コンペアマッチカウンタ０		*/
	#define	CMT__CMCOR1		(*(UWORD *)0xffff83DC)		/**  コンペアマッチコンスタントレジスタ０*/
/*****************************************************/
/*  ピンファンクションコントローラ					 */
/*****************************************************/
	#define	PFC__PAIORH		(*(UWORD *)0xffff8384)		/**  ポートＡ・ＩＯレジスタＨ		*/
	#define	PFC__PAIORL		(*(UWORD *)0xffff8386)		/**  ポートＡ・ＩＯレジスタＬ		*/

	#define	PFC__PACRH		(*(UWORD *)0xffff8388)		/**  ポートＡコントロールレジスタＨ	*/
		#define PACRH_PA23MD_WRHH		0x4000			/**  ＰＡ２３はＷＲＨＨ             */
		#define PACRH_PA22MD_WRHL		0x1000			/**  ＰＡ２２はＷＲＨＬ             */
		#define PACRH_PA21MD_CASHH		0x0400			/**  ＰＡ２１はＣＡＳＨＨ           */
		#define PACRH_PA20MD_CASHL		0x0100			/**  ＰＡ２０はＣＡＳＨＬ           */
		#define PACRH_PA19MD_BACK		0x0040			/**  ＰＡ１９はＢＡＣＫ             */
		#define PACRH_PA19MD_DRAK1		0x0080			/**  ＰＡ１９はＤＲＡＫ１           */
		#define PACRH_PA18MD_BREQ		0x0010			/**  ＰＡ１８はＢＲＥＱ             */
		#define PACRH_PA18MD_DRAK0		0x0020			/**  ＰＡ１８はＤＲＡＫ０           */
		#define PACRH_PA17MD_WAIT		0x0004			/**  ＰＡ１７はＷＡＩＴ             */
		#define PACRH_PA16MD_AH			0x0001			/**  ＰＡ１６はＡＨ                 */
		#define PACRH_PA16_23_GP		0x0000			/**  ＰＡ１６～２３は汎用入力       */

	#define	PFC__PACRL1		(*(UWORD *)0xffff838C)		/**  ポートＡコントロールレジスタL1	*/
		#define PACRL1_PA15MD_CK		0x4000			/**  ＰＡ１５はＣＫ                 */
		#define PACRL1_PA14MD_RD		0x1000			/**  ＰＡ１４はＲＤ                 */
		#define PACRL1_PA13MD_WRH		0x0400			/**  ＰＡ１３はＷＲＨ               */
		#define PACRL1_PA12MD_WRL		0x0100			/**  ＰＡ１２はＷＲＬ               */
		#define PACRL1_PA11MD_CS1		0x0040			/**  ＰＡ１１はＣＳ１               */
		#define PACRL1_PA10MD_CS0		0x0010			/**  ＰＡ１０はＣＳ０               */
		#define PACRL1_PA9MD_TCLKD		0x0004			/**  ＰＡ９はＴＣＬＫＤ             */
		#define PACRL1_PA9MD_IRQ3		0x0008			/**  ＰＡ９はＩＲＱ３               */
		#define PACRL1_PA8MD_TCLKC		0x0001			/**  ＰＡ８はＴＣＬＫＣ             */
		#define PACRL1_PA8MD_IRQ2		0x0004			/**  ＰＡ８はＩＲＱ２               */
		#define PACRL1_PA8_15_GP		0x0000			/**  ＰＡ８～１５は汎用入力         */

	#define	PFC__PACRL2		(*(UWORD *)0xffff838E)		/**  ポートＡコントロールレジスタL２*/
		#define PACRL2_PA7MD_TCLKB		0x4000			/**  ＰＡ７はＴＣＬＫＢ             */
		#define PACRL2_PA7MD_CS3		0x8000			/**  ＰＡ７はＣＳ３                 */
		#define PACRL2_PA6MD_TCLKA		0x1000			/**  ＰＡ６はＴＣＬＫＡ             */
		#define PACRL2_PA6MD_CS2		0x2000			/**  ＰＡ６はＣＳ２                 */
		#define PACRL2_PA5MD_CSK1		0x0400			/**  ＰＡ５はＣＳＫ１               */
		#define PACRL2_PA5MD_DREQ1		0x0800			/**  ＰＡ５はＤＲＥＱ１             */
		#define PACRL2_PA4MD_TXD1		0x0100			/**  ＰＡ４はＴＸＤ１               */
		#define PACRL2_PA3MD_RXD1		0x0040			/**  ＰＡ３はＲＸＤ１               */
		#define PACRL2_PA2MD_SCK0		0x0010			/**  ＰＡ２はＣＳＫ０               */
		#define PACRL2_PA2MD_DRQ0		0x0020			/**  ＰＡ２はＤＲＥＱ０             */
		#define PACRL2_PA2MD_IRQ0		0x0030			/**  ＰＡ２はＩＲＥＱ０             */
		#define PACRL2_PA1MD_TXD0		0x0004			/**  ＰＡ１はＴＸＤ０               */
		#define PACRL2_PA0MD_RXD0		0x0001			/**  ＰＡ０はＲＸＤ０               */
		#define PACRL2_PA0_7_GP			0x0000			/**  ＰＡ０～７は汎用入出力         */

	#define	PFC__PBIOR		(*(UWORD *)0xffff8394)		/**  ポートＢ・ＩＯレジスタ			*/
	#define	PFC__PBCR1		(*(UWORD *)0xffff8398)		/**  ポートＢコントロールレジスタ１	*/
		#define PBCR1_PB9MD_IRQ7		0x0004			/**  ＰＢ９はＩＲＱ７               */
		#define PBCR1_PB9MD_A21			0x0008			/**  ＰＢ９はＡ２１                 */
		#define PBCR1_PB9MD_ADTRG		0x000C			/**  ＰＢ９はＡＤＴＲＧ             */
		#define PBCR1_PB8MD_IRQ6		0x0001			/**  ＰＢ８はＩＲＱ６               */
		#define PBCR1_PB8MD_A20			0x0002			/**  ＰＢ８はＡ２０                 */
		#define PBCR1_PB8MD_WAIT		0x0003			/**  ＰＢ８はＷＡＩＴ               */
		#define PBCR1_PB8_9_GP			0x0000			/**  ＰＢ８～９は汎用入出力         */

	#define	PFC__PBCR2		(*(UWORD *)0xffff839A)		/**  ポートＢコントロールレジスタ２	*/
		#define PBCR2_PB7MD_IRQ5		0x4000			/**  ＰＢ７はＩＲＱ５               */
		#define PBCR2_PB7MD_A19			0x8000			/**  ＰＢ７はＡ１９                 */
		#define PBCR2_PB7MD_BREQ		0xC000			/**  ＰＢ７はＢＲＥＱ               */
		#define PBCR2_PB6MD_IRQ4		0x1000			/**  ＰＢ６はＩＲＱ４               */
		#define PBCR2_PB6MD_A18			0x2000			/**  ＰＢ６はＡ１８                 */
		#define PBCR2_PB6MD_BACK		0x3000			/**  ＰＢ６はＢＡＣＫ               */
		#define PBCR2_PB5MD_IRQ3		0x0400			/**  ＰＢ５はＩＲＱ３               */
		#define PBCR2_PB5MD_POE3		0x0800			/**  ＰＢ５はＰＯＥ３               */
		#define PBCR2_PB5MD_RDWR		0x0C00			/**  ＰＢ５はＲＤＷＲ               */
		#define PBCR2_PB4MD_IRQ2		0x0100			/**  ＰＢ４はＩＲＱ２               */
		#define PBCR2_PB4MD_POE2		0x0200			/**  ＰＢ４はＰＯＥ２               */
		#define PBCR2_PB4MD_CASH		0x0300			/**  ＰＢ４はＣＡＳＨ               */
		#define PBCR2_PB3MD_IRQ1		0x0040			/**  ＰＢ３はＩＲＱ１               */
		#define PBCR2_PB3MD_POE1		0x0080			/**  ＰＢ３はＰＯＥ１               */
		#define PBCR2_PB3MD_CASL		0x00C0			/**  ＰＢ３はＣＡＳＬ               */
		#define PBCR2_PB2MD_IRQ0		0x0010			/**  ＰＢ２はＩＲＱ０               */
		#define PBCR2_PB2MD_POE0		0x0020			/**  ＰＢ２はＰＯＥ０               */
		#define PBCR2_PB2MD_RAS			0x0030			/**  ＰＢ２はＲＡＳ                 */
		#define PBCR2_PB1MD_A17			0x0004			/**  ＰＢ１はＡ１７                 */
		#define PBCR2_PB0MD_A16			0x0001			/**  ＰＢ０はＡ１６                 */
		#define PBCR2_PB0_7_GP			0x0000			/**  ＰＢ０から７は汎用入出力       */

	#define	PFC__PCIOR		(*(UWORD *)0xffff8396)		/**  ポートＣ・ＩＯレジスタ			*/
	#define	PFC__PCCR		(*(UWORD *)0xffff839C)		/**  ポートＣコントロールレジスタ	*/
		#define PCCR_PC15MD_A15			0x8000			/**  ＰＣ１５はＡ１５               */
		#define PCCR_PC14MD_A14			0x4000			/**  ＰＣ１４はＡ１４               */
		#define PCCR_PC13MD_A13			0x2000			/**  ＰＣ１３はＡ１３               */
		#define PCCR_PC12MD_A12			0x1000			/**  ＰＣ１２はＡ１２               */
		#define PCCR_PC11MD_A11			0x0800			/**  ＰＣ１１はＡ１１               */
		#define PCCR_PC10MD_A10			0x0400			/**  ＰＣ１０はＡ１０               */
		#define PCCR_PC9MD_A9			0x0200			/**  ＰＣ９はＡ９                   */
		#define PCCR_PC8MD_A8			0x0100			/**  ＰＣ８はＡ８                   */
		#define PCCR_PC7MD_A7			0x0080			/**  ＰＣ７はＡ７                   */
		#define PCCR_PC6MD_A6			0x0040			/**  ＰＣ６はＡ６                   */
		#define PCCR_PC5MD_A5			0x0020			/**  ＰＣ５はＡ５                   */
		#define PCCR_PC4MD_A4			0x0010			/**  ＰＣ４はＡ４                   */
		#define PCCR_PC3MD_A3			0x0008			/**  ＰＣ３はＡ３                   */
		#define PCCR_PC2MD_A2			0x0004			/**  ＰＣ２はＡ２                   */
		#define PCCR_PC1MD_A1			0x0002			/**  ＰＣ１はＡ１                   */
		#define PCCR_PC0MD_A0			0x0001			/**  ＰＣ０はＡ０                   */
		#define PCCR_PC0_15_GP			0x0000			/**  ＰＣ０～ＰＣ１５は汎用入出力   */

	#define	PFC__PDIORH		(*(UWORD *)0xffff83A4)		/**  ポートＤ・ＩＯレジスタＨ		*/
	#define	PFC__PDIORL		(*(UWORD *)0xffff83A6)		/**  ポートＤ・ＩＯレジスタＬ		*/
	#define	PFC__PDCRH1		(*(UWORD *)0xffff83A8)		/**  ポートＤコントロールレジスタＨ１*/
		#define PDCRH1_PD31MD_D31		0x4000			/**  ＰＤ３１はＤ３１               */
		#define PDCRH1_PD31MD_ADTRG		0x8000			/**  ＰＤ３１はＡＤＴＲＧ           */
		#define PDCRH1_PD30MD_D30		0x1000			/**  ＰＤ３０はＤ３０               */
		#define PDCRH1_PD30MD_IRQOUT	0x2000			/**  ＰＤ３０はＩＲＱＯＵＴ         */
		#define PDCRH1_PD29MD_D29		0x0400			/**  ＰＤ２９はＤ２９               */
		#define PDCRH1_PD29MD_CS3		0x0800			/**  ＰＤ２９はＣＳ３               */
		#define PDCRH1_PD28MD_D28		0x0100			/**  ＰＤ２８はＤ２８               */
		#define PDCRH1_PD28MD_CS2		0x0200			/**  ＰＤ２８はＣＳ２               */
		#define PDCRH1_PD27MD_D27		0x0040			/**  ＰＤ２７はＤ２７               */
		#define PDCRH1_PD27MD_DACK1		0x0080			/**  ＰＤ２７はＤＡＣＫ１           */
		#define PDCRH1_PD26MD_D26		0x0010			/**  ＰＤ２６はＤ２６               */
		#define PDCRH1_PD26MD_DACK0		0x0020			/**  ＰＤ２６はＤＡＣＫ０           */
		#define PDCRH1_PD25MD_D25		0x0004			/**  ＰＤ２５はＤ２５               */
		#define PDCRH1_PD25MD_DREQ1		0x0008			/**  ＰＤ２５はＤＲＥＱ１           */
		#define PDCRH1_PD24MD_D24		0x0001			/**  ＰＤ２４はＤ２４               */
		#define PDCRH1_PD24MD_DREQ0		0x0002			/**  ＰＤ２４はＤＲＥＱ０           */
		#define PDCRH1_PD24_31_GP		0x0000			/**  ＰＤ２４～３１は汎用入出力     */

	#define	PFC__PDCRH2		(*(UWORD *)0xffff83AA)		/**  ポートＤコントロールレジスタＨ２*/
		#define PDCRH2_PD23MD_D23		0x4000			/**  ＰＤ２３はＤ２３               */
		#define PDCRH2_PD23MD_IRQ7		0x8000			/**  ＰＤ２３はＩＲＱ７             */
		#define PDCRH2_PD22MD_D22		0x1000			/**  ＰＤ２２はＤ２２               */
		#define PDCRH2_PD22MD_IRQ6		0x2000			/**  ＰＤ２２はＩＲＱ６             */
		#define PDCRH2_PD21MD_D21		0x0400			/**  ＰＤ２１はＤ２１               */
		#define PDCRH2_PD21MD_IRQ5		0x0800			/**  ＰＤ２１はＩＲＱ５             */
		#define PDCRH2_PD20MD_D20		0x0100			/**  ＰＤ２０はＤ２０               */
		#define PDCRH2_PD20MD_IRQ4		0x0200			/**  ＰＤ２０はＩＲＱ４             */
		#define PDCRH2_PD19MD_D19		0x0040			/**  ＰＤ１９はＤ１９               */
		#define PDCRH2_PD19MD_IRQ3		0x0080			/**  ＰＤ１９はＩＲＱ３             */
		#define PDCRH2_PD18MD_D18		0x0010			/**  ＰＤ１８はＤ１８               */
		#define PDCRH2_PD18MD_IRQ2		0x0020			/**  ＰＤ１８はＩＲＱ２             */
		#define PDCRH2_PD17MD_D17		0x0004			/**  ＰＤ１７はＤ１７               */
		#define PDCRH2_PD17MD_IRQ1		0x0008			/**  ＰＤ１７はＩＲＱ１             */
		#define PDCRH2_PD16MD_D16		0x0001			/**  ＰＤ１６はＤ１６               */
		#define PDCRH2_PD16MD_IRQ0		0x0002			/**  ＰＤ１６はＩＲＱ０             */
		#define PDCRH2_PD16_23_GP		0x0000			/**  ＰＤ１６～２３は汎用入出力     */

	#define	PFC__PDCRL		(*(UWORD *)0xffff83AC)		/**  ポートＤコントロールレジスタL	*/
		#define PDCRL_PD15MD_D15		0x8000			/**  ＰＤ１５はＤ１５               */
		#define PDCRL_PD14MD_D14		0x4000			/**  ＰＤ１４はＤ１４               */
		#define PDCRL_PD13MD_D13		0x2000			/**  ＰＤ１３はＤ１３               */
		#define PDCRL_PD12MD_D12		0x1000			/**  ＰＤ１２はＤ１２               */
		#define PDCRL_PD11MD_D11		0x0800			/**  ＰＤ１１はＤ１１               */
		#define PDCRL_PD10MD_D10		0x0400			/**  ＰＤ１０はＤ１０               */
		#define PDCRL_PD9MD_D9			0x0200			/**  ＰＤ９はＤ９                   */
		#define PDCRL_PD8MD_D8			0x0100			/**  ＰＤ８はＤ８                   */
		#define PDCRL_PD7MD_D7			0x0080			/**  ＰＤ７はＤ７                   */
		#define PDCRL_PD6MD_D6			0x0040			/**  ＰＤ６はＤ６                   */
		#define PDCRL_PD5MD_D5			0x0020			/**  ＰＤ５はＤ５                   */
		#define PDCRL_PD4MD_D4			0x0010			/**  ＰＤ４はＤ４                   */
		#define PDCRL_PD3MD_D3			0x0008			/**  ＰＤ３はＤ３                   */
		#define PDCRL_PD2MD_D2			0x0004			/**  ＰＤ２はＤ２                   */
		#define PDCRL_PD1MD_D1			0x0002			/**  ＰＤ１はＤ１                   */
		#define PDCRL_PD0MD_D0			0x0001			/**  ＰＤ０はＤ０                   */
		#define PDCRL_PD0_15_GP			0x0000			/**  ＰＤ０～１５は汎用入出力       */

	#define	PFC__PEIOR		(*(UWORD *)0xffff83B4)		/**  ポートＥ・ＩＯレジスタ			*/
	#define	PFC__PECR1		(*(UWORD *)0xffff83B8)		/**  ポートＥコントロールレジスタ１	*/
		#define PECR1_PE15MD_TIOC4D		0x4000			/**  ＰＥ１５はＴＩＯＣ４Ｄ         */
		#define PECR1_PE15MD_DACK1		0x8000			/**  ＰＥ１５はＤＡＣＫ１           */
		#define PECR1_PE15MD_IRQOUT		0xC000			/**  ＰＥ１５はＩＲＱＯＵＴ         */
		#define PECR1_PE14MD_TIOC4C		0x1000			/**  ＰＥ１４はＴＩＯＣ４Ｃ         */
		#define PECR1_PE14MD_DACK0		0x2000			/**  ＰＥ１４はＤＡＣＫ０           */
		#define PECR1_PE14MD_AH			0x3000			/**  ＰＥ１４はＡＨ                 */
		#define PECR1_PE13MD_TIOC4B		0x0400			/**  ＰＥ１３はＴＩＯＣ４Ｂ         */
		#define PECR1_PE13MD_MRES		0x0800			/**  ＰＥ１３はＭＲＥＳ             */
		#define PECR1_PE12MD_TIOC4A		0x0100			/**  ＰＥ１２はＴＩＯＣ４Ａ         */
		#define PECR1_PE11MD_TIOC3D		0x0040			/**  ＰＥ１１はＴＩＯＣ３Ｄ         */
		#define PECR1_PE10MD_TIOC3C		0x0010			/**  ＰＥ１０はＴＩＯＣ３Ｃ         */
		#define PECR1_PE9MD_TIOC3B		0x0004			/**  ＰＥ９はＴＩＯＣ３Ｂ           */
		#define PECR1_PE8MD_TIOC3A		0x0001			/**  ＰＥ８はＴＩＯＣ３Ａ           */
		#define PECR1_PE8_15MD_GP		0x0000			/**  ＰＥ８～１５は汎用入出力       */

	#define	PFC__PECR2		(*(UWORD *)0xffff83BA)		/**  ポートＥコントロールレジスタ２	*/
		#define PECR2_PE7MD_TIOC2B		0x4000			/**  ＰＥ７はＴＩＯＣ２Ｂ           */
		#define PECR2_PE6MD_TIOC2A		0x1000			/**  ＰＥ６はＴＩＯＣ２Ａ           */
		#define PECR2_PE5MD_TIOC1B		0x0400			/**  ＰＥ５はＴＩＯＣ１Ｂ           */
		#define PECR2_PE4MD_TIOC1A		0x0100			/**  ＰＥ４はＴＩＯＣ１Ａ           */
		#define PECR2_PE3MD_TIOC0D		0x0040			/**  ＰＥ３はＴＩＯＣ０Ｄ           */
		#define PECR2_PE3MD_DRAK1		0x0080			/**  ＰＥ３はＤＲＡＫ１             */
		#define PECR2_PE2MD_TIOC0C		0x0010			/**  ＰＥ２はＴＩＯＣ０Ｃ           */
		#define PECR2_PE2MD_DREQ1		0x0020			/**  ＰＥ２はＤＲＥＱ１             */
		#define PECR2_PE1MD_TIOC0B		0x0004			/**  ＰＥ１はＴＩＯＣ０Ｂ           */
		#define PECR2_PE1MD_DRAK0		0x0008			/**  ＰＥ１はＤＲＡＫ０             */
		#define PECR2_PE0MD_TIOC0A		0x0001			/**  ＰＥ０はＴＩＯＣ０Ａ           */
		#define PECR2_PE0MD_DREQ0		0x0002			/**  ＰＥ０はＤＲＥＱ０             */
		#define PECR2_PE0_7_GP			0x0000			/**  ＰＥ０～７は汎用入出力         */

	#define	PFC__IFCR		(*(UWORD *)0xffff83C8)		/**  IRQOUT機能コントロールレジスタ	*/

/*****************************************************/
/*  Ｉ／Ｏポート									 */
/*****************************************************/
	/*--------------------------------------------------------------*/
	/* ＰＡＤＲＨ（ポートＡデータレジスタＨ）の設定                 */
	/*--------------------------------------------------------------*/
	#define	IO__PADRH		(*(UWORD *)0xffff8380)		/**  ポートＡデータレジスタＨ		*/
	#define	IO_PADRH_PORT	0xffff8380					/**  ポートＡデータレジスタＨ		*/
	/* READ PORT */
#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/21 */
		/* IO_BIT_SELVOIを代わりに定義しています */
#else
		#define	IO_BIT_DV				0x0001			/**  ＤＴＭＦ検確定			*/
#endif
		#define	IO_BIT_EST				0x0010			/**  Ｄｉａｌ　Ｉｎ(警察FAXではスクランブルSW ON/OFF) */
		#define	IO_BIT_XCIS				0x0020			/**  カッターセンサー位置	*/
		#define	IO_BIT_KY_RO			0x0040			/**  サーマルヘッドメーカー	*/
	/* WRITE PORT */
#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
		#define	IO_BIT_SELVOI			0x0001			/**  出力信号選択			*/
#endif
		#define	IO_BIT_CUTTER1			0x0004			/**  カッターモータ（カッタ）	*/
		#define IO_BIT_CUTTER2			0x0008			/**  カッターモータ（＋２４Ｖ）	*/
		#define IO_BIT_HCLK				0x0080			/**  クロック供給			*/ /* 2001/11/19 T.Takagi */

	/*--------------------------------------------------------------*/
	/* ＰＡＤＲＬ（ポートＡデータレジスタＬ）の設定                 */
	/*--------------------------------------------------------------*/
	#define	IO__PADRL		(*(UWORD *)0xffff8382)		/**  ポートＡデータレジスタＬ		*/
	#define	IO_PADRL_PORT	0xffff8382					/**  ポートＡデータレジスタＬ		*/
	/* READ PORT */
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/24 */
		#define IO_BIT_MDM_S1			0x0008			/* S1/モデムDTC割り込み検知 */
		#define IO_BIT_XLC3				0x0010			/* 基板エラー検知 */
		#define IO_BIT_K_L				0x0020			/* 警電回線Lリレー制御 */
		#define IO_BIT_LINESW			0x0040			/* 警電回線と加入回線の切り替えSW */
		#define IO_BIT_SUSBEL			0x0080			/* 擬似ベル切り替えSW */
#else /* !defined (KEISATSU) */
 #if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
		#define IO_BIT_XVOICIR			0x0008			/**  音声IC有無の識別		*/
		#define	IO_BIT_VOINAR			0x0010			/**  音声IC・アドレス状態	*/
 #else
		#define	IO_BIT_XRTS				0x0020			/**  ＲＴＳ（ＲＳ２３２Ｃ）	*/
		#define	IO_BIT_DTMF1			0x0040			/**  ＤＴＭＦデータ			*/
		#define	IO_BIT_DTMF2			0x0080			/**  ＤＴＭＦデータ			*/
		#define	IO_BIT_DTMF3			0x0100			/**  ＤＴＭＦデータ			*/
		#define	IO_BIT_DTMF4			0x0200			/**  ＤＴＭＦデータ			*/
 #endif
	/* WRITE PORT */
#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
		#define	IO_BIT_VOIRES			0x0020			/**  音声ICリセット			*/
		#define	IO_BIT_VOIST			0x0040			/**  音声IC動作				*/
		#define	IO_BIT_VOII0			0x0080			/**  音声ICアドレス			*/
		#define	IO_BIT_VOII1			0x0100			/**  音声ICアドレス			*/
		#define	IO_BIT_VOII2			0x0200			/**  音声ICアドレス			*/
#endif
#endif /* defined (KEISATSU) */

	/*--------------------------------------------------------------*/
	/* ＰＢＤＲ（ポートＢデータレジスタ）の初期設定                 */
	/*--------------------------------------------------------------*/
	#define	IO__PBDR		(*(UWORD *)0xffff8390)		/**  ポートＢデータレジスタ			*/
	#define	IO_PBDR_PORT	0xffff8390					/**  ポートＢデータレジスタ			*/
	/* READ PORT */
	/* WRITE PORT */

	/*--------------------------------------------------------------*/
	/* ＰＣＤＲ（ポートＣデータレジスタ）の初期設定                 */
	/*--------------------------------------------------------------*/
	#define	IO__PCDR		(*(UWORD *)0xffff8392)		/**  ポートＣデータレジスタ			*/
	#define	IO_PCDR_PORT	0xffff8392					/**  ポートＣデータレジスタ			*/
	/* READ PORT */
	/* WRITE PORT */

	/*--------------------------------------------------------------*/
	/* ＰＤＤＲＨ（ポートＤデータレジスタＨ）の初期設定             */
	/*--------------------------------------------------------------*/
	#define	IO__PDDRH		(*(UWORD *)0xffff83A0)		/**  ポートＤデータレジスタＨ		*/
	#define	IO_PDDRH_PORT	0xffff83A0					/**  ポートＤデータレジスタＨ		*/
	/* READ PORT */
		#define IO_BIT_RS_CTS				0x0080			/**  ＲＳ－２３２Ｃ送信可 */
		#define IO_BIT_RANK					0x4000			/**  京セラＴＰＨランク指定			*/
#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/21 */
		/* IO_BIT_TL13を代わりに定義しています */
#else
		/* #define IO_BIT_DTR				0x8000			@**  ＲＳ－２３２Ｃデータ端末レディ	*/
		#define IO_BIT_RS_DTR				0x8000			/**  ＲＳ－２３２Ｃデータ端末レディ	*/
#endif
	/* WRITE PORT */
#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
		#define IO_BIT_TL13					0x8000			/**  テストランド13		*/
#else									/* IO_BIT_TL13ポートを'H'固定にします。by Y.Kano 2004/03/26 */
		#define IO_BIT_TL13					0x8000			/**  テストランド13		*/
#endif

	/*--------------------------------------------------------------*/
	/* ＰＤＤＲＬ（ポートＤデータレジスタＬ）の初期設定             */
	/*--------------------------------------------------------------*/
	#define	IO__PDDRL		(*(UWORD *)0xffff83A2)		/**  ポートＤデータレジスタＬ		*/
	#define	IO_PDDRL_PORT	0xffff83A2					/**  ポートＤデータレジスタＬ		*/
	/* READ PORT */
	/* WRITE PORT */

	/*--------------------------------------------------------------*/
	/* ＰＥＤＲ（ポートＥデータレジスタ）の初期設定                 */
	/*--------------------------------------------------------------*/
	#define	IO__PEDR		(*(UWORD *)0xffff83B0)		/**  ポートＥデータレジスタ			*/
	extern	volatile UBYTE	io_pedr;					/* (0xffff81B4)	  シリアルステータスレジスタ		*/
	#define	IO_PEDR			&io_pedr					/**  ポートＥデータレジスタ			*/
	#define	IO_PEDR_PORT	0xffff83B0					/**  ポートＥデータレジスタ			*/
	/* WRITE PORT */
#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
		#define IO_BIT_TL02		0x0001					/**  テストランド2(未使用)								*/
#else
		#define	IO_BIT_RS_DCD	0x0001					/**  ＲＳ－２３２Ｃ データチャンネル受信キャリア検出	*/
#endif
		#define	IO_BIT_XRESM	0x0002					/**  モデムソフトリセット								*/
		#define	IO_BIT_RQCLR	0x0004					/**  モデムリクエストクリア								*/
		#define	IO_BIT_MUTE		0x0008					/**  スピーチＩＣミュート								*/
		/* #define	IO_BIT_BUZZ		0x0010					@**  ブザー出力（ＰＷＭＣＫ） *//*1998/10/07*/
		/* #define IO_BIT_TIOC1A	0x0010					@** ブザー クロック出力（ＰＷＭ出力） *//*1998/10/07*/
		#define	IO_BIT_PROAD	0x0010					/**  パネルデータロード									*/
		#define	IO_BIT_LRS		0x0020					/**  ＬＣＤドライバーレジスタ							*/
		#define	IO_BIT_LEWR1	0x0040					/**  ＬＥＤポートチップセレクト１						*/
		#define	IO_BIT_LEWR2	0x0080					/**  ＬＥＤポートチップセレクト２						*/
		/* #define	IO_BIT_PROAD	0x0100					@**  パネルデータロード *//*1998/10/07*/
		#define	IO_BIT_BUZZ		0x0100					/**  ブザー出力（ＰＷＭＣＫ）							*/
		#define IO_BIT_TIOC1A	0x0100					/** ブザー クロック出力（ＰＷＭ出力）					*/
		#define	IO_BIT_LEWR3	0x0200					/**  ＬＥＤポートチップセレクト３（フック／会話予約）	*/
		#define IO_BIT_LE		0x0400					/**  ＬＣＤドライバーＥクロック							*/
#if (PRO_RTC_RX5C338A == ENABLE)
		#define IO_BIT_RTCDT	0x0800					/**  SIO（データ入出力）ビット							*/
		#define IO_BIT_WRTCDA	IO_BIT_RTCDT			/**  Atlantaと共通にする為 */
		#define IO_BIT_RTCCE	0x1000					/**  ＲＴＣチップイネーブル								*/
		#define IO_BIT_CCLK		0x2000					/**  クロック制御ビット									*/
		#define IO_BIT_RTCCK	0x4000					/**  ＲＴＣ同期クロック									*/
#else
		#define IO_BIT_RTCDT	0x0800					/**  ＲＴＣシリアルデータ（ＷＲ）						*/
		#define IO_BIT_WRTCDA	IO_BIT_RTCDT			/**  Atlantaと共通にする為 */
		#define IO_BIT_RTCCE	0x1000					/**  ＲＴＣチップイネーブル								*/
		#define IO_BIT_RTCIO	0x2000					/**  ＲＴＣ ＩＮ／ＯＵＴセレクト						*/
		#define IO_BIT_RTCCK	0x4000					/**  ＲＴＣ同期クロック									*/
#endif
#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
		#define IO_BIT_TL01			0x8000					/**  テストランド1(未使用)								*/
#else
		/* #define IO_BIT_DSR		0x8000					@**  ＲＳ－２３２Ｃデータセットレディ					*/
		#define IO_BIT_RS_DSR		0x8000					/**  ＲＳ－２３２Ｃデータセットレディ					*/
#endif
	/* READ PORT */
		#define IO_BIT_RRTCDA	IO_BIT_RTCDT			/** Atlantaと共通にする為 */
		/* #define IO_BIT_RTCDT	0x0800	Readと同じ名前なのでコメント *//**  ＲＴＣシリアルデータ（ＷＲ）						*/

	/*--------------------------------------------------------------*/
	/* ＰＦＤＲ（ポートＦデータレジスタ）の初期設定                 */
	/*--------------------------------------------------------------*/
	#define	IO__PFDR		(*(UBYTE *)0xffff83B3)		/**  ポートＦデータレジスタ			*/
	#define	IO_PFDR_PORT	0xffff83B3					/**  ポートＦデータレジスタ			*/
		/* READ PORT */
		/* ＣＳ２空間のバス幅を決定するのに、
		**      ＳＡＫＡＫＩ ポート：Ｆ－Ｄ０＝０   ＝＞１６ビット
		**      ＨＩＮＯＫＩ ポート：Ｆ－Ｄ０＝１   ＝＞  ８ビット
		** とすれば、内蔵ＣＰＵで判断し、適切な設定をするようになっている。
		** しかし、ＥＳ基盤では急な話しだったので、ディップスイッチの０を流用しておく
		** メインＰＣＢが変更になればここの定義も変更するようにしてください。
		** by O.Kimoto 1998/09/19
		*/
		#define IO_BIT_CS2_BYTE_WORD	0x0001		/* CS2のバス幅 ０：１６ビット １：８ビット */
		#define	IO_BIT_DSW0				0x0001		/* ハードディップＳＷ	*/
		#define	IO_BIT_DSW1				0x0002		/* ハードディップＳＷ	*/
		#define	IO_BIT_DSW2				0x0004		/* ハードディップＳＷ	*/
		#define	IO_BIT_DSW3				0x0008		/* ハードディップＳＷ	*/
 #if defined(HINOKI3) || defined(KEISATSU)	/* PS1,PB4をポート読みする。by Y.Kano 2004/12/25 */
		#define IO_BIT_XPS1				0x0008		/* 記録紙検出センサー */
		#define IO_BIT_XPB4				0x0010		/* 記録紙Ｂ４センサー */
 #endif
		#define IO_BIT_BAT				0x0040		/* バックアップ電池残量（アナログ入力）	*/
		#define IO_BIT_TM1				0x0080		/* サーミスタ温度入力（アナログ入力）	*/

/*****************************************************/
/*  ポートアウトプットイネーブル					 */
/*****************************************************/
	#define	POE__ICSR		(*(UWORD *)0xffff83C0)		/**  入力レベルコントロール／ステータスレジスタ*/
	#define	POE__OCSR		(*(UWORD *)0xffff83C2)		/**  出力レベルコントロール／ステータスレジスタ*/

/*****************************************************/
/*  Ａ／Ｄ変換器									 */
/*****************************************************/
#if (PRO_CPU_VERSION == SH7043_R)
	#define	AD__ADCSR		(*(UBYTE *)0xffff83E0)		/**  Ａ／Ｄコントロール／ステータスレジスタ  */
		#define ADCSR_CH0	0x01						/**  チャネルセレクト０            */
		#define ADCSR_CH1	0x02						/**  チャネルセレクト１            */
		#define ADCSR_CH2	0x04						/**  チャネルセレクト２            */
		#define ADCSR_GRP	0x08						/**  グループモード                */
		#define ADCSR_CKS	0x10						/**  クロックセレクト              */
		#define ADCSR_ADST	0x20						/**  Ａ／Ｄスタート                */
		#define ADCSR_ADIE	0x40						/**  Ａ／Ｄインタラプトイネーブル  */
		#define ADCSR_ADF	0x80						/**  Ａ／Ｄエンドフラグ            */

	#define	AD__ADCR		(*(UBYTE *)0xffff83E1)		/**  Ａ／Ｄコントロールレジスタ    */
		#define ADCR_BUFE0	0x01						/**  バッファイネーブル０          */
		#define ADCR_BUFE1	0x02						/**  バッファイネーブル１          */
		#define ADCR_DSMP	0x04						/**  同時サンプリング              */
		#define ADCR_SCAN	0x08						/**  スキャンモード                */
		#define ADCR_TRGS0	0x10						/**  タイマトリガセレクト０        */
		#define ADCR_TRGS1	0x20						/**  タイマトリガセレクト１        */
		#define ADCR_PWR	0x40						/**  電源ビット                    */

	#define	AD__ADDRA		(*(UWORD *)0xffff83F0)		/**  Ａ／ＤデータレジスタＡ        */
	#define	AD__ADDRB		(*(UWORD *)0xffff83F2)		/**  Ａ／ＤデータレジスタＢ        */
	#define	AD__ADDRC		(*(UWORD *)0xffff83F4)		/**  Ａ／ＤデータレジスタＣ        */
	#define	AD__ADDRD		(*(UWORD *)0xffff83F6)		/**  Ａ／ＤデータレジスタＤ        */
	#define	AD__ADDRE		(*(UWORD *)0xffff83F8)		/**  Ａ／ＤデータレジスタＥ        */
	#define	AD__ADDRF		(*(UWORD *)0xffff83FA)		/**  Ａ／ＤデータレジスタＦ        */
	#define	AD__ADDRG		(*(UWORD *)0xffff83FC)		/**  Ａ／ＤデータレジスタＧ        */
	#define	AD__ADDRH		(*(UWORD *)0xffff83FE)		/**  Ａ／ＤデータレジスタＨ        */
#endif
#if (PRO_CPU_VERSION == SH7043_A)
	#define	AD__ADCSR0		(*(UBYTE *)0xffff8410)		/**  Ａ／Ｄコントロール／ステータスレジスタ  */
		#define ADCSR0_CH0	0x01						/**  チャネルセレクト０            */
		#define ADCSR0_CH1	0x02						/**  チャネルセレクト１            */
		#define ADCSR0_CKS	0x08						/**  クロックセレクト              */
		#define ADCSR0_SCAN	0x10						/**  スキャンモード                */
		#define ADCSR0_ADST	0x20						/**  Ａ／Ｄスタート                */
		#define ADCSR0_ADIE	0x40						/**  Ａ／Ｄインタラプトイネーブル  */
		#define ADCSR0_ADF	0x80						/**  Ａ／Ｄエンドフラグ            */
	#define	AD__ADCSR1		(*(UBYTE *)0xffff8411)		/**  Ａ／Ｄコントロール／ステータスレジスタ  */
		#define ADCSR1_CH0	0x01						/**  チャネルセレクト０            */
		#define ADCSR1_CH1	0x02						/**  チャネルセレクト１            */
		#define ADCSR1_CKS	0x08						/**  クロックセレクト              */
		#define ADCSR1_SCAN	0x10						/**  スキャンモード                */
		#define ADCSR1_ADST	0x20						/**  Ａ／Ｄスタート                */
		#define ADCSR1_ADIE	0x40						/**  Ａ／Ｄインタラプトイネーブル  */
		#define ADCSR1_ADF	0x80						/**  Ａ／Ｄエンドフラグ            */
	#define	AD__ADCR0		(*(UBYTE *)0xffff8412)		/**  Ａ／Ｄコントロールレジスタ    */
		#define ADCR0_TRGE	0x80						/**  トリガイネーブル              */
		#define ADCR0_RESERVE	0x7F					/**  予約ビット                    */
	#define	AD__ADCR1		(*(UBYTE *)0xffff8413)		/**  Ａ／Ｄコントロールレジスタ    */
		#define ADCR1_TRGE	0x80						/**  トリガイネーブル              */
		#define ADCR1_RESERVE	0x7F					/**  予約ビット                    */

	#define AD__ADDRA0		(*(UWORD *)0xffff8400)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRA0H		(*(UWORD *)0xffff8400)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRA0L		(*(UWORD *)0xffff8401)		/**  Ａ／ＤデータレジスタＡ        */

	#define AD__ADDRB0		(*(UWORD *)0xffff8402)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRB0H		(*(UWORD *)0xffff8402)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRB0L		(*(UWORD *)0xffff8403)		/**  Ａ／ＤデータレジスタＡ        */

	#define AD__ADDRC0		(*(UWORD *)0xffff8404)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRC0H		(*(UWORD *)0xffff8404)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRC0L		(*(UWORD *)0xffff8405)		/**  Ａ／ＤデータレジスタＡ        */

	#define AD__ADDRD0		(*(UWORD *)0xffff8406)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRD0H		(*(UWORD *)0xffff8406)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRD0L		(*(UWORD *)0xffff8407)		/**  Ａ／ＤデータレジスタＡ        */

	#define AD__ADDRA1		(*(UWORD *)0xffff8408)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRA1H		(*(UWORD *)0xffff8408)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRA1L		(*(UWORD *)0xffff8409)		/**  Ａ／ＤデータレジスタＡ        */

	#define AD__ADDRB1		(*(UWORD *)0xffff840A)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRB1H		(*(UWORD *)0xffff840A)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRB1L		(*(UWORD *)0xffff840B)		/**  Ａ／ＤデータレジスタＡ        */

	#define AD__ADDRC1		(*(UWORD *)0xffff840C)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRC1H		(*(UWORD *)0xffff840C)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRC1L		(*(UWORD *)0xffff840D)		/**  Ａ／ＤデータレジスタＡ        */

	#define AD__ADDRD1		(*(UWORD *)0xffff840E)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRD1H		(*(UWORD *)0xffff840E)		/**  Ａ／ＤデータレジスタＡ        */
	#define AD__ADDRD1L		(*(UWORD *)0xffff840F)		/**  Ａ／ＤデータレジスタＡ        */


	#define	AD__ADDRA		AD__ADDRA0		/**  Ａ／ＤデータレジスタＡ        */
	#define	AD__ADDRB		AD__ADDRB0		/**  Ａ／ＤデータレジスタＢ        */
	#define	AD__ADDRC		AD__ADDRC0		/**  Ａ／ＤデータレジスタＣ        */
	#define	AD__ADDRD		AD__ADDRD0		/**  Ａ／ＤデータレジスタＤ        *//* ＨＩＮＯＫＩ３ではＰＳ１ */
	#define	AD__ADDRE		AD__ADDRA1		/**  Ａ／ＤデータレジスタＥ        *//* ＨＩＮＯＫＩ３ではＰＢ４ */
	#define	AD__ADDRF		AD__ADDRB1		/**  Ａ／ＤデータレジスタＦ        *//* ＰＳ２ *//* Add By O.Kimoto 1999/03/29 */
	#define	AD__ADDRG		AD__ADDRC1		/**  Ａ／ＤデータレジスタＧ        *//* バッテリー */
	#define	AD__ADDRH		AD__ADDRD1		/**  Ａ／ＤデータレジスタＨ        *//* サーミスター */
#endif


	/*---------------------------------------------------------------------
	** AD__ADDREがこの値以下の場合はDRAMは充電されていない
	** 1998/08/31 H.Yoshikawa
	*/
	#define AD_BATTERY_MAX	(0x1FF)


/*****************************************************/
/*  キャシュメモリ（ＣＡＣ）						 */
/*****************************************************/
	#define	CAC_CCR		(*(UBYTE *)0xffff8740)		/**  キャッシュコントロールレジスタ  */
		#define CAC_CECS0	0x01						/**  ＣＳ０空間のキャッシュイネーブル  */
		#define CAC_CECS1	0x02						/**  ＣＳ１空間のキャッシュイネーブル  */
		#define CAC_CECS2	0x04						/**  ＣＳ２空間のキャッシュイネーブル  */
		#define CAC_CECS3	0x08						/**  ＣＳ３空間のキャッシュイネーブル  */
		#define CAC_CEDRAM	0x10						/**  ＤＲＡＭ空間のキャッシュイネーブル  */
	#define	CAC_ADDRESS_ARRAY		0xfffff000			/**  アドレスアレイ  */
	#define	CAC_ADDRESS_ARRAY_END	0xfffff400			/**  アドレスアレイ  */

#endif
