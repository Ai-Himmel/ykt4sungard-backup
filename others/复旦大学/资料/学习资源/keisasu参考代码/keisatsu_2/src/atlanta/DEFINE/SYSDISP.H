/*---------------------------------------------------------------------------*/
/*  プロジェクト : Atlanta                                                   */
/*  ファイル名   : SYSDISP.h                                                 */
/*  モジュール   :                                                           */
/*  作成者       : 村田                                                      */
/*  日  付       : 1996/12/24                                                */
/*  概  要       : マルチ回線表示定義                                        */
/*               :                                                           */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#ifndef	sysdisp_h
	#define	sysdisp_h



struct SYS_DisplayData_t {
	UBYTE SYS_FaxCommStage;					/* 通信遷移状態 define */
	UBYTE SYS_CurrentExecQueueNo;			/* Grape実行ExecQueueの番号 */
	UBYTE SYS_DocBlock_Src_Size;			/* 元原稿パラメータ define */
	UBYTE SYS_DocBlock_Src_Mode;			/* 元原稿パラメータ define */
	UBYTE SYS_DocBlock_Dst_Size;			/* 先原稿パラメータ define */
	UBYTE SYS_DocBlock_Dst_Mode;			/* 先原稿パラメータ define */
	UBYTE GrayModeFlag;						/* ファイン、中間調の場合--YES yes/no */
	UBYTE FaxComTXorRX_Sign;				/* 送信／受信識別フラグ　送信、受信、リモート診断識別 define */
	UBYTE SYS_FaxComType;					/* 交信種別 define */
	UBYTE SYS_FaxComTxType;					/* 送信原稿種別 define */
	UBYTE TxBaudRate;						/* 確定送信ボーレイト define */
	UBYTE RxBaudRate;						/* 確定受信ボーレイト define */
	UBYTE TxECM_Mode;						/* 確定ＥＣＭ送信指定 yes/no */
	UBYTE RxECM_Mode;						/* 確定ＥＣＭ受信指定 yes/no */
	UBYTE FinalRxMode;						/* 確定受信モード define */
	UWORD SYS_TxTotalPage;							/* 全送信ページ数 */
	UWORD SYS_RxTotalPage;							/* 全受信ページ数 */
	UWORD TxMemoryFilePage;							/* メモリ送信を行う原稿のファイルページ */
	UWORD MDM_RxTotalLine;							/* 受信トータルライン */
	UWORD MDM_RxErrorTotalLine;						/* 受信エラートータルライン */
	UWORD BatchTxFinishPage;						/* 一括送信送信済み頁数 */
	UBYTE NonStandardID[SYS_TTI_ID_MAX];	/* 交信相手機の村田ＩＤ */
	UBYTE StandardID[SYS_ID_MAX];			/* 交信相手機の標準ＩＤ */

#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
	/** ICHOUで４行ディスプレイ表示のため、以下を追加 1997/06/26 M.Shimizu */
	UBYTE CommandFileOptionItem;		/* 通信種別						define */
	UWORD CommandFilePage;						/* メモリ送信総ページ			valye  */
#endif
};








#endif
