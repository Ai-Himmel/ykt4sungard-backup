/*	By Y.Suzuki 1996/10/15	*/
/* Original File : jun\usr2:\src\kobe\anzu\define\syspcrx.h */
#ifndef syspcrx_h
	#define syspcrx_h

/************************************************************************
 * ＰＣ受信原稿プリント													*
 * struct SYS_PCRXPRINTData_t SYB_PCRXPRINT;							*
 * 1996/08/08															*
 * 宮崎仁一																*
 ************************************************************************/
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)

struct	SYS_PcRxPrintData_t {
	UBYTE Status;			/* 動作状態 */
	UBYTE PrintDensity;		/* プリント濃度 */
	UBYTE TonarSaveMode;	/* トナーセーブモード */
	UWORD ReserveNumber;	/* 指定部数 */
	UBYTE JamRecovery;		/* ジャムリカバリ処理有り・無し By J.Miyazaki 1996/10/29 */
	UBYTE InchData;			/* 転送データインチorミリ By J.Miyazaki 1996/11/27 */
	UBYTE OHPMode;			/* ＯＨＰ印刷設定 By J.Miyazaki 1997/02/03 */
	UWORD ExecutiveNumber;	/* 実行済み部数 */
	UWORD RemainMultiPrintCount;	
	UBYTE Size;				/* 用紙サイズ H.Yoshikawa 1997/07/17 */ 
	UBYTE NoPaperCassette;	/* 自動カセット指定時に用紙なしとなった場合のカセット By M.Tachibana 1997/09/19 */
	UBYTE Reserve;			/* リザーブ */
	UWORD StorePage;		/* 受信枚数 ０～６５５３５ページまで 		*/
	UWORD PrintPage;		/* プリント枚数 ０～６５５３５ページまで 	*/
	UWORD ErasePage;		/* 消去ペ－ジ ０～６５５３５ページまで  	*/
	UWORD PrintEndPage;		/* プリント終了ページ（ＰＣ通知用）         */
};

#else

struct	SYS_PcRxPrintData_t {
	UBYTE Status;			/* 動作状態 */
	UBYTE PrintDensity;		/* プリント濃度 */
	UBYTE TonarSaveMode;	/* トナーセーブモード */
	UBYTE ReserveNumber;	/* 指定部数 */
	UBYTE JamRecovery;		/* ジャムリカバリ処理有り・無し By J.Miyazaki 1996/10/29 */
	UBYTE InchData;			/* 転送データインチorミリ By J.Miyazaki 1996/11/27 */
	UBYTE OHPMode;			/* ＯＨＰ印刷設定 By J.Miyazaki 1997/02/03 */
	UBYTE ExecutiveNumber;	/* 実行済み部数 */
	UBYTE RemainMultiPrintCount;	
	UBYTE Size;				/* 用紙サイズ H.Yoshikawa 1997/07/17 */ 
	UBYTE NoPaperCassette;	/* 自動カセット指定時に用紙なしとなった場合のカセット By M.Tachibana 1997/09/19 */
	UBYTE Reserve;			/* リザーブ */
	UWORD StorePage;		/* 受信枚数 ０～６５５３５ページまで 		*/
	UWORD PrintPage;		/* プリント枚数 ０～６５５３５ページまで 	*/
	UWORD ErasePage;		/* 消去ペ－ジ ０～６５５３５ページまで  	*/
	UWORD PrintEndPage;		/* プリント終了ページ（ＰＣ通知用）         */
};
#endif

/************************************************************************
 * ＰＣ受信原稿プリントの動作状態										*
 * struct SYS_PcRxPrintData_t											*
 * 1996/08/08															*
 * 宮崎仁一																*
 ************************************************************************/
#define SYS_PC_RX_EMPTY		0	/* 未使用 */
#define SYS_PC_RX_STORE		1	/* メモリ受信原稿(受領証含む)蓄積中 */
#define SYS_PC_RX_PRINT		2	/* メモリ受信原稿（受領証含む)プリント*/
								/* プリント待ち */
#define SYS_PC_RX_POWEROFF	3	/* 停電により消去された */
#define	SYS_PC_RX_JAMWAIT	0x80	/* ＰＣがジャムを検出していない状態 By J.Miyazaki 1997/03/28 */




#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/12 Y.Murata */
/*
 * テストプリント管理テーブル
*/
struct	SYS_MinoltaTestFuncData_t	{
	UWORD	Status;
	UWORD	IntervalTimer;		/* 1秒単位 ０の時は連続プリント */

	UBYTE	Status2;			/* 動作状態 */
	UBYTE	PrintDensity;		/* プリント濃度 */
	UBYTE	TonarSaveMode;	/* トナーセーブモード */
	UWORD	ReserveNumber;	/* 指定部数 */
	UBYTE	JamRecovery;		/* ジャムリカバリ処理有り・無し By J.Miyazaki 1996/10/29 */
	UBYTE	InchData;			/* 転送データインチorミリ By J.Miyazaki 1996/11/27 */
	UBYTE	OHPMode;			/* ＯＨＰ印刷設定 By J.Miyazaki 1997/02/03 */
	UWORD	ExecutiveNumber;	/* 実行済み部数 */
	UWORD	RemainMultiPrintCount;	
	UBYTE	Size;				/* 用紙サイズ H.Yoshikawa 1997/07/17 */ 
	UBYTE	NoPaperCassette;	/* 自動カセット指定時に用紙なしとなった場合のカセット By M.Tachibana 1997/09/19 */
	UBYTE	Reserve;			/* リザーブ */
	UWORD	StorePage;		/* 受信枚数 ０～６５５３５ページまで 		*/
	UWORD	PrintPage;		/* プリント枚数 ０～６５５３５ページまで 	*/
	UWORD	ErasePage;		/* 消去ペ－ジ ０～６５５３５ページまで  	*/
	UWORD	PrintEndPage;		/* プリント終了ページ（ＰＣ通知用）         */
};

/*Status定義*/
#define	SYS_FUNC_TEST_DATA_EMPTY		0
#define	SYS_FUNC_TEST_DATA_STORE		1
#define	SYS_FUNC_TEST_DATA_PRINT		2
#define	SYS_FUNC_TEST_DATA_OFF			3

#endif	/* (PRO_MINOLTA_TEST_FUNC == ENABLE) */


#endif	/* End of File */
