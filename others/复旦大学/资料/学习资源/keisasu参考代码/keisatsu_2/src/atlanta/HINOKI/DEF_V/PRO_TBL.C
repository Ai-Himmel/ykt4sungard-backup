/************************************************************************
*	System		: SAKAKI
*	File Name	: PRO_TBL.C
*	Author		: 吉川弘康
*	Date		: 1998/06/12
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	:
*	Maintenance	: MOMIJI用からSAKAKI用に変更した。
*				  SAKAKIでは使用しませんが、ATLANTA共通のため定義だけします
*				  SAKAKIよりコピーしただけです。	By O.Kimoto 1998/09/07
*				  HINOKIでは使用しませんが、ATLANTA共通のため定義だけします
*	Copyright (C) 1998 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
/*---------------------------------------------------------------------------*/
/*  プロジェクト : Jun/KOBE                                                  */
/*  ファイル名   : PRO_DEF.H                                                 */
/*  モジュール   :                                                           */
/*               :                                                           */
/*  作成者       : 村田                                                      */
/*  日  付       : 1996/11/12                                                */
/*  概  要       : オプションボード機能スペック定義ファイル                  */
/*               :                                                           */
/*  修正履歴     : Atlantaへ移植 By M.Kotani 97/03/24                        */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\pro_def.h"

/*------------------*/
/* ホスト機器の性能 */
/*------------------*/
CONST struct SYS_MachinePerformanceData_t SYS_MachinePerformance[8] = {
/*ボード０*/
/*フルスペックサポート*/
	{
	PRO_SPEC_400_400_MODE,		/*AvailableRxResolution;	受信可能線密度		*/
	0,							/*AvailableRxResolutionSub;	受信可能線密度SUB	*/
	PRO_SPEC_MAX_PAPER_SIZE_B4,	/*PaperSizeMAX;				最大記録紙サイズ	*/
	PRO_SPEC_SCANNING_TIME10,	/*TxMinimumScanningTime;	最小伝送時間		*/
	0,							/*TxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_SCANNING_TIME0,	/*RxMinimumScanningTime;	最小伝送時間		*/
	0,							/*RxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_MMR_CODE,			/*AvailableTxCodingMethod;	通信符号化方式		*/

#if (0)
** 	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
** 	PRO_SPEC_MMR_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#else
	PRO_SPEC_MG3_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#endif

	PRO_SPEC_METRIC,			/*TxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_METRIC,			/*RxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_MSE1,				/*TxMSE_Method;				ＳＭＳＥモード		*/
	PRO_SPEC_MSE1,				/*RxMSE_Method;				ＳＭＳＥモード		*/
	0,							/*Reserve14;									*/
	0,							/*Reserve15;									*/
	0,							/*Reserve16;									*/
	0,							/*Reserve17;									*/
	0,							/*Reserve18;									*/
	0,							/*Reserve19;									*/
	0							/*Reserve20;									*/
	},
/*ボード１*/
	{
	PRO_SPEC_400_400_MODE,		/*AvailableRxResolution;	受信可能線密度		*/
	0,							/*AvailableRxResolutionSub;	受信可能線密度SUB	*/
	PRO_SPEC_MAX_PAPER_SIZE_B4,	/*PaperSizeMAX;				最大記録紙サイズ	*/
	PRO_SPEC_SCANNING_TIME10,	/*TxMinimumScanningTime;	最小伝送時間		*/
	0,							/*TxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_SCANNING_TIME0,	/*RxMinimumScanningTime;	最小伝送時間		*/
	0,							/*RxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_MMR_CODE,			/*AvailableTxCodingMethod;	通信符号化方式		*/

#if (0)
** 	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
** 	PRO_SPEC_MMR_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#else
	PRO_SPEC_MG3_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#endif

	PRO_SPEC_METRIC,			/*TxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_METRIC,			/*RxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_MSE1,				/*TxMSE_Method;				ＳＭＳＥモード		*/
	PRO_SPEC_MSE1,				/*RxMSE_Method;				ＳＭＳＥモード		*/
	0,							/*Reserve14;									*/
	0,							/*Reserve15;									*/
	0,							/*Reserve16;									*/
	0,							/*Reserve17;									*/
	0,							/*Reserve18;									*/
	0,							/*Reserve19;									*/
	0							/*Reserve20;									*/
	},
/*ボード２*/
	{
	PRO_SPEC_400_400_MODE,		/*AvailableRxResolution;	受信可能線密度		*/
	0,							/*AvailableRxResolutionSub;	受信可能線密度SUB	*/
	PRO_SPEC_MAX_PAPER_SIZE_B4,	/*PaperSizeMAX;				最大記録紙サイズ	*/
	PRO_SPEC_SCANNING_TIME10,	/*TxMinimumScanningTime;	最小伝送時間		*/
	0,							/*TxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_SCANNING_TIME0,	/*RxMinimumScanningTime;	最小伝送時間		*/
	0,							/*RxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_MMR_CODE,			/*AvailableTxCodingMethod;	通信符号化方式		*/

#if (0)
** 	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
** 	PRO_SPEC_MMR_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#else
	PRO_SPEC_MG3_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#endif

	PRO_SPEC_METRIC,			/*TxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_METRIC,			/*RxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_MSE1,				/*TxMSE_Method;				ＳＭＳＥモード		*/
	PRO_SPEC_MSE1,				/*RxMSE_Method;				ＳＭＳＥモード		*/
	0,							/*Reserve14;									*/
	0,							/*Reserve15;									*/
	0,							/*Reserve16;									*/
	0,							/*Reserve17;									*/
	0,							/*Reserve18;									*/
	0,							/*Reserve19;									*/
	0							/*Reserve20;									*/
	},
/*ボード３*/
	{
	PRO_SPEC_400_400_MODE,		/*AvailableRxResolution;	受信可能線密度		*/
	0,							/*AvailableRxResolutionSub;	受信可能線密度SUB	*/
	PRO_SPEC_MAX_PAPER_SIZE_B4,	/*PaperSizeMAX;				最大記録紙サイズ	*/
	PRO_SPEC_SCANNING_TIME10,	/*TxMinimumScanningTime;	最小伝送時間		*/
	0,							/*TxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_SCANNING_TIME0,	/*RxMinimumScanningTime;	最小伝送時間		*/
	0,							/*RxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_MMR_CODE,			/*AvailableTxCodingMethod;	通信符号化方式		*/

#if (0)
** 	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
** 	PRO_SPEC_MMR_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#else
	PRO_SPEC_MG3_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#endif

	PRO_SPEC_METRIC,			/*TxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_METRIC,			/*RxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_MSE1,				/*TxMSE_Method;				ＳＭＳＥモード		*/
	PRO_SPEC_MSE1,				/*RxMSE_Method;				ＳＭＳＥモード		*/
	0,							/*Reserve14;									*/
	0,							/*Reserve15;									*/
	0,							/*Reserve16;									*/
	0,							/*Reserve17;									*/
	0,							/*Reserve18;									*/
	0,							/*Reserve19;									*/
	0							/*Reserve20;									*/
	},
/*ボード４*/
	{
	PRO_SPEC_400_400_MODE,		/*AvailableRxResolution;	受信可能線密度		*/
	0,							/*AvailableRxResolutionSub;	受信可能線密度SUB	*/
	PRO_SPEC_MAX_PAPER_SIZE_B4,	/*PaperSizeMAX;				最大記録紙サイズ	*/
	PRO_SPEC_SCANNING_TIME10,	/*TxMinimumScanningTime;	最小伝送時間		*/
	0,							/*TxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_SCANNING_TIME0,	/*RxMinimumScanningTime;	最小伝送時間		*/
	0,							/*RxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_MMR_CODE,			/*AvailableTxCodingMethod;	通信符号化方式		*/

#if (0)
** 	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
** 	PRO_SPEC_MMR_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#else
	PRO_SPEC_MG3_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#endif

	PRO_SPEC_METRIC,			/*TxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_METRIC,			/*RxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_MSE1,				/*TxMSE_Method;				ＳＭＳＥモード		*/
	PRO_SPEC_MSE1,				/*RxMSE_Method;				ＳＭＳＥモード		*/
	0,							/*Reserve14;									*/
	0,							/*Reserve15;									*/
	0,							/*Reserve16;									*/
	0,							/*Reserve17;									*/
	0,							/*Reserve18;									*/
	0,							/*Reserve19;									*/
	0							/*Reserve20;									*/
	},
/*ボード５*/
	{
	PRO_SPEC_400_400_MODE,		/*AvailableRxResolution;	受信可能線密度		*/
	0,							/*AvailableRxResolutionSub;	受信可能線密度SUB	*/
	PRO_SPEC_MAX_PAPER_SIZE_B4,	/*PaperSizeMAX;				最大記録紙サイズ	*/
	PRO_SPEC_SCANNING_TIME10,	/*TxMinimumScanningTime;	最小伝送時間		*/
	0,							/*TxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_SCANNING_TIME0,	/*RxMinimumScanningTime;	最小伝送時間		*/
	0,							/*RxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_MMR_CODE,			/*AvailableTxCodingMethod;	通信符号化方式		*/

#if (0)
** 	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
** 	PRO_SPEC_MMR_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#else
	PRO_SPEC_MG3_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#endif

	PRO_SPEC_METRIC,			/*TxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_METRIC,			/*RxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_MSE1,				/*TxMSE_Method;				ＳＭＳＥモード		*/
	PRO_SPEC_MSE1,				/*RxMSE_Method;				ＳＭＳＥモード		*/
	0,							/*Reserve14;									*/
	0,							/*Reserve15;									*/
	0,							/*Reserve16;									*/
	0,							/*Reserve17;									*/
	0,							/*Reserve18;									*/
	0,							/*Reserve19;									*/
	0							/*Reserve20;									*/
	},
/*ボード６*/
	{
	PRO_SPEC_400_400_MODE,		/*AvailableRxResolution;	受信可能線密度		*/
	0,							/*AvailableRxResolutionSub;	受信可能線密度SUB	*/
	PRO_SPEC_MAX_PAPER_SIZE_B4,	/*PaperSizeMAX;				最大記録紙サイズ	*/
	PRO_SPEC_SCANNING_TIME10,	/*TxMinimumScanningTime;	最小伝送時間		*/
	0,							/*TxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_SCANNING_TIME0,	/*RxMinimumScanningTime;	最小伝送時間		*/
	0,							/*RxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_MMR_CODE,			/*AvailableTxCodingMethod;	通信符号化方式		*/

#if (0)
** 	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
** 	PRO_SPEC_MMR_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#else
	PRO_SPEC_MG3_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#endif

	PRO_SPEC_METRIC,			/*TxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_METRIC,			/*RxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_MSE1,				/*TxMSE_Method;				ＳＭＳＥモード		*/
	PRO_SPEC_MSE1,				/*RxMSE_Method;				ＳＭＳＥモード		*/
	0,							/*Reserve14;									*/
	0,							/*Reserve15;									*/
	0,							/*Reserve16;									*/
	0,							/*Reserve17;									*/
	0,							/*Reserve18;									*/
	0,							/*Reserve19;									*/
	0							/*Reserve20;									*/
	},
/*ボード７*/
	{
	PRO_SPEC_400_400_MODE,		/*AvailableRxResolution;	受信可能線密度		*/
	0,							/*AvailableRxResolutionSub;	受信可能線密度SUB	*/
	PRO_SPEC_MAX_PAPER_SIZE_B4,	/*PaperSizeMAX;				最大記録紙サイズ	*/
	PRO_SPEC_SCANNING_TIME10,	/*TxMinimumScanningTime;	最小伝送時間		*/
	0,							/*TxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_SCANNING_TIME0,	/*RxMinimumScanningTime;	最小伝送時間		*/
	0,							/*RxMinimumScanningTimeSub;	最小伝送時間SUB		*/
	PRO_SPEC_MMR_CODE,			/*AvailableTxCodingMethod;	通信符号化方式		*/

#if (0)
** 	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
** 	PRO_SPEC_MMR_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#else
	PRO_SPEC_MG3_CODE,			/*AvailableRxCodingMethod;	通信符号化方式		*/
#endif

	PRO_SPEC_METRIC,			/*TxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_METRIC,			/*RxModeMethod;				インチ／ミリ		*/
	PRO_SPEC_MSE1,				/*TxMSE_Method;				ＳＭＳＥモード		*/
	PRO_SPEC_MSE1,				/*RxMSE_Method;				ＳＭＳＥモード		*/
	0,							/*Reserve14;									*/
	0,							/*Reserve15;									*/
	0,							/*Reserve16;									*/
	0,							/*Reserve17;									*/
	0,							/*Reserve18;									*/
	0,							/*Reserve19;									*/
	0							/*Reserve20;									*/
	}
};

/*-------------------------------------------------*/
/* グレープに動作させたい機能（マスター／スレーブ）*/
/*-------------------------------------------------*/
CONST UWORD	SYS_OptionBoaudFunctionTable[8][5] = {
/*ボード０*/
/*フルスペックサポート*/
	{
/*0*/	0
		&	~PRO_FUNC_TEL_FAX_MODE			/* ＴＥＬ／ＦＡＸ	*/
		&	~PRO_FUNC_ANS_FAX_MODE			/* ＡＮＳ／ＦＡ		*/
		&	~PRO_FUNC_TEL_MODE				/* ＴＥＬ			*/
		&	~PRO_FUNC_REMOTE_DIAG			/* リモート診断		*/
#if (PRO_PIN_ACCESS == ENABLE)
		|	PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#else
		&	~PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#endif
		|	PRO_FUNC_RING_MASTER			/* リングマスター	*/
		&	~PRO_FUNC_CLASS1				/* クラス１			*/
		&	~PRO_FUNC_CLASS2				/* クラス２			*/
		|	PRO_FUNC_POLLING_TX				/* ポーリング送信	*/
		|	PRO_FUNC_DB_POLLING_TX			/* 検索ポーリング送信 */
		|	PRO_FUNC_SECURE_RX				/* 親展受信			*/
		|	PRO_FUNC_RELAYED_TX				/* 中継配信			*/
#if 1 /* Clover では実際には参照されていないが、論理的には必要。 Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#else
@@		&	~PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#endif
		&	~PRO_FUNC_RELAYED_REPORT		/* 不達通知			*/
		&	~PRO_FUNC_DIALIN				/* ダイアルイン		*/
		|	PRO_FUNC_ERASE_TX_MEM_PAGE		/* 送信済みメモリの消去 */
		,
/*1*/	0
		|	PRO_FUNC_JUNK_FAX_MODE_TYPE		/* ﾀﾞｲﾚｸﾄﾒｰﾙﾓｰﾄﾞ別編 */
#if (PRO_COST == ENABLE) /* Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_COST					/* 料金管理			 */
#else
		&	~PRO_FUNC_COST					/* 料金管理			 */
#endif
		|	PRO_FUNC_F_CODE					/* Ｆコード			 */
		|	PRO_FUNC_CIPHER				/* アリロー			 */
		|	PRO_FUNC_ERROR_MONITOR			/* 通信エラーモニタ	 */
		|	PRO_FUNC_MAIL_COMP_CHK			/* 親展競合ｺﾝﾊﾟﾁ編	 */
		,
	/* 予備 */
/*2*/	0
		,
	/* 予備 */
/*3*/	0
		,
	/* 予備 */
/*4*/	0
		,
	/* 予備 */
	},

/*ボード１*/
	{
/*0*/	0
		&	~PRO_FUNC_TEL_FAX_MODE			/* ＴＥＬ／ＦＡＸ	*/
		&	~PRO_FUNC_ANS_FAX_MODE			/* ＡＮＳ／ＦＡ		*/
		&	~PRO_FUNC_TEL_MODE				/* ＴＥＬ			*/
		&	~PRO_FUNC_REMOTE_DIAG			/* リモート診断		*/
#if (PRO_PIN_ACCESS == ENABLE)
		|	PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#else
		&	~PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#endif
		|	PRO_FUNC_RING_MASTER			/* リングマスター	*/
		&	~PRO_FUNC_CLASS1				/* クラス１			*/
		&	~PRO_FUNC_CLASS2				/* クラス２			*/
		|	PRO_FUNC_POLLING_TX				/* ポーリング送信	*/
		|	PRO_FUNC_DB_POLLING_TX			/* 検索ポーリング送信 */
		|	PRO_FUNC_SECURE_RX				/* 親展受信			*/
		|	PRO_FUNC_RELAYED_TX				/* 中継配信			*/
#if 1 /* Clover では実際には参照されていないが、論理的には必要。 Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#else
@@		&	~PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#endif
		&	~PRO_FUNC_RELAYED_REPORT		/* 不達通知			*/
		&	~PRO_FUNC_DIALIN				/* ダイアルイン		*/
		|	PRO_FUNC_ERASE_TX_MEM_PAGE		/* 送信済みメモリの消去 */
		,
/*1*/	0
		|	PRO_FUNC_JUNK_FAX_MODE_TYPE		/* ﾀﾞｲﾚｸﾄﾒｰﾙﾓｰﾄﾞ別編 */
#if (PRO_COST == ENABLE) /* Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_COST					/* 料金管理			 */
#else
		&	~PRO_FUNC_COST					/* 料金管理			 */
#endif
		|	PRO_FUNC_F_CODE					/* Ｆコード			 */
		|	PRO_FUNC_CIPHER				/* アリロー			 */
		|	PRO_FUNC_ERROR_MONITOR			/* 通信エラーモニタ	 */
		|	PRO_FUNC_MAIL_COMP_CHK			/* 親展競合ｺﾝﾊﾟﾁ編	 */
		,
	/* 予備 */
/*2*/	0
		,
	/* 予備 */
/*3*/	0
		,
	/* 予備 */
/*4*/	0
		,
	/* 予備 */
	},
/*ボード２*/
	{
/*0*/	0
		&	~PRO_FUNC_TEL_FAX_MODE			/* ＴＥＬ／ＦＡＸ	*/
		&	~PRO_FUNC_ANS_FAX_MODE			/* ＡＮＳ／ＦＡ		*/
		&	~PRO_FUNC_TEL_MODE				/* ＴＥＬ			*/
		&	~PRO_FUNC_REMOTE_DIAG			/* リモート診断		*/
#if (PRO_PIN_ACCESS == ENABLE)
		|	PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#else
		&	~PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#endif
		|	PRO_FUNC_RING_MASTER			/* リングマスター	*/
		&	~PRO_FUNC_CLASS1				/* クラス１			*/
		&	~PRO_FUNC_CLASS2				/* クラス２			*/
		|	PRO_FUNC_POLLING_TX				/* ポーリング送信	*/
		|	PRO_FUNC_DB_POLLING_TX			/* 検索ポーリング送信 */
		|	PRO_FUNC_SECURE_RX				/* 親展受信			*/
		|	PRO_FUNC_RELAYED_TX				/* 中継配信			*/
#if 1 /* Clover では実際には参照されていないが、論理的には必要。 Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#else
@@		&	~PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#endif
		&	~PRO_FUNC_RELAYED_REPORT		/* 不達通知			*/
		&	~PRO_FUNC_DIALIN				/* ダイアルイン		*/
		|	PRO_FUNC_ERASE_TX_MEM_PAGE		/* 送信済みメモリの消去 */
		,
/*1*/	0
		|	PRO_FUNC_JUNK_FAX_MODE_TYPE		/* ﾀﾞｲﾚｸﾄﾒｰﾙﾓｰﾄﾞ別編 */
#if (PRO_COST == ENABLE) /* Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_COST					/* 料金管理			 */
#else
		&	~PRO_FUNC_COST					/* 料金管理			 */
#endif
		|	PRO_FUNC_F_CODE					/* Ｆコード			 */
		|	PRO_FUNC_CIPHER				/* アリロー			 */
		|	PRO_FUNC_ERROR_MONITOR			/* 通信エラーモニタ	 */
		|	PRO_FUNC_MAIL_COMP_CHK			/* 親展競合ｺﾝﾊﾟﾁ編	 */
		,
	/* 予備 */
/*2*/	0
		,
	/* 予備 */
/*3*/	0
		,
	/* 予備 */
/*4*/	0
		,
	/* 予備 */
	},
/*ボード３*/
	{
/*0*/	0
		&	~PRO_FUNC_TEL_FAX_MODE			/* ＴＥＬ／ＦＡＸ	*/
		&	~PRO_FUNC_ANS_FAX_MODE			/* ＡＮＳ／ＦＡ		*/
		&	~PRO_FUNC_TEL_MODE				/* ＴＥＬ			*/
		&	~PRO_FUNC_REMOTE_DIAG			/* リモート診断		*/
#if (PRO_PIN_ACCESS == ENABLE)
		|	PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#else
		&	~PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#endif
		|	PRO_FUNC_RING_MASTER			/* リングマスター	*/
		&	~PRO_FUNC_CLASS1				/* クラス１			*/
		&	~PRO_FUNC_CLASS2				/* クラス２			*/
		|	PRO_FUNC_POLLING_TX				/* ポーリング送信	*/
		|	PRO_FUNC_DB_POLLING_TX			/* 検索ポーリング送信 */
		|	PRO_FUNC_SECURE_RX				/* 親展受信			*/
		|	PRO_FUNC_RELAYED_TX				/* 中継配信			*/
#if 1 /* Clover では実際には参照されていないが、論理的には必要。 Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#else
@@		&	~PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#endif
		&	~PRO_FUNC_RELAYED_REPORT		/* 不達通知			*/
		&	~PRO_FUNC_DIALIN				/* ダイアルイン		*/
		|	PRO_FUNC_ERASE_TX_MEM_PAGE		/* 送信済みメモリの消去 */
		,
/*1*/	0
		|	PRO_FUNC_JUNK_FAX_MODE_TYPE		/* ﾀﾞｲﾚｸﾄﾒｰﾙﾓｰﾄﾞ別編 */
#if (PRO_COST == ENABLE) /* Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_COST					/* 料金管理			 */
#else
		&	~PRO_FUNC_COST					/* 料金管理			 */
#endif
		|	PRO_FUNC_F_CODE					/* Ｆコード			 */
		|	PRO_FUNC_CIPHER				/* アリロー			 */
		|	PRO_FUNC_ERROR_MONITOR			/* 通信エラーモニタ	 */
		|	PRO_FUNC_MAIL_COMP_CHK			/* 親展競合ｺﾝﾊﾟﾁ編	 */
		,
	/* 予備 */
/*2*/	0
		,
	/* 予備 */
/*3*/	0
		,
	/* 予備 */
/*4*/	0
		,
	/* 予備 */
	},
/*ボード４*/
	{
/*0*/	0
		&	~PRO_FUNC_TEL_FAX_MODE			/* ＴＥＬ／ＦＡＸ	*/
		&	~PRO_FUNC_ANS_FAX_MODE			/* ＡＮＳ／ＦＡ		*/
		&	~PRO_FUNC_TEL_MODE				/* ＴＥＬ			*/
		&	~PRO_FUNC_REMOTE_DIAG			/* リモート診断		*/
#if (PRO_PIN_ACCESS == ENABLE)
		|	PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#else
		&	~PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#endif
		|	PRO_FUNC_RING_MASTER			/* リングマスター	*/
		&	~PRO_FUNC_CLASS1				/* クラス１			*/
		&	~PRO_FUNC_CLASS2				/* クラス２			*/
		|	PRO_FUNC_POLLING_TX				/* ポーリング送信	*/
		|	PRO_FUNC_DB_POLLING_TX			/* 検索ポーリング送信 */
		|	PRO_FUNC_SECURE_RX				/* 親展受信			*/
		|	PRO_FUNC_RELAYED_TX				/* 中継配信			*/
#if 1 /* Clover では実際には参照されていないが、論理的には必要。 Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#else
@@		&	~PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#endif
		&	~PRO_FUNC_RELAYED_REPORT		/* 不達通知			*/
		&	~PRO_FUNC_DIALIN				/* ダイアルイン		*/
		|	PRO_FUNC_ERASE_TX_MEM_PAGE		/* 送信済みメモリの消去 */
		,
/*1*/	0
		|	PRO_FUNC_JUNK_FAX_MODE_TYPE		/* ﾀﾞｲﾚｸﾄﾒｰﾙﾓｰﾄﾞ別編 */
#if (PRO_COST == ENABLE) /* Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_COST					/* 料金管理			 */
#else
		&	~PRO_FUNC_COST					/* 料金管理			 */
#endif
		|	PRO_FUNC_F_CODE					/* Ｆコード			 */
		|	PRO_FUNC_CIPHER				/* アリロー			 */
		|	PRO_FUNC_ERROR_MONITOR			/* 通信エラーモニタ	 */
		|	PRO_FUNC_MAIL_COMP_CHK			/* 親展競合ｺﾝﾊﾟﾁ編	 */
		,
	/* 予備 */
/*2*/	0
		,
	/* 予備 */
/*3*/	0
		,
	/* 予備 */
/*4*/	0
		,
	/* 予備 */
	},
/*ボード５*/
	{
/*0*/	0
		&	~PRO_FUNC_TEL_FAX_MODE			/* ＴＥＬ／ＦＡＸ	*/
		&	~PRO_FUNC_ANS_FAX_MODE			/* ＡＮＳ／ＦＡ		*/
		&	~PRO_FUNC_TEL_MODE				/* ＴＥＬ			*/
		&	~PRO_FUNC_REMOTE_DIAG			/* リモート診断		*/
#if (PRO_PIN_ACCESS == ENABLE)
		|	PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#else
		&	~PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#endif
		|	PRO_FUNC_RING_MASTER			/* リングマスター	*/
		&	~PRO_FUNC_CLASS1				/* クラス１			*/
		&	~PRO_FUNC_CLASS2				/* クラス２			*/
		|	PRO_FUNC_POLLING_TX				/* ポーリング送信	*/
		|	PRO_FUNC_DB_POLLING_TX			/* 検索ポーリング送信 */
		|	PRO_FUNC_SECURE_RX				/* 親展受信			*/
		|	PRO_FUNC_RELAYED_TX				/* 中継配信			*/
#if 1 /* Clover では実際には参照されていないが、論理的には必要。 Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#else
@@		&	~PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#endif
		&	~PRO_FUNC_RELAYED_REPORT		/* 不達通知			*/
		&	~PRO_FUNC_DIALIN				/* ダイアルイン		*/
		|	PRO_FUNC_ERASE_TX_MEM_PAGE		/* 送信済みメモリの消去 */
		,
/*1*/	0
		|	PRO_FUNC_JUNK_FAX_MODE_TYPE		/* ﾀﾞｲﾚｸﾄﾒｰﾙﾓｰﾄﾞ別編 */
#if (PRO_COST == ENABLE) /* Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_COST					/* 料金管理			 */
#else
		&	~PRO_FUNC_COST					/* 料金管理			 */
#endif
		|	PRO_FUNC_F_CODE					/* Ｆコード			 */
		|	PRO_FUNC_CIPHER				/* アリロー			 */
		|	PRO_FUNC_ERROR_MONITOR			/* 通信エラーモニタ	 */
		|	PRO_FUNC_MAIL_COMP_CHK			/* 親展競合ｺﾝﾊﾟﾁ編	 */
		,
	/* 予備 */
/*2*/	0
		,
	/* 予備 */
/*3*/	0
		,
	/* 予備 */
/*4*/	0
		,
	/* 予備 */
	},
/*ボード６*/
	{
/*0*/	0
		&	~PRO_FUNC_TEL_FAX_MODE			/* ＴＥＬ／ＦＡＸ	*/
		&	~PRO_FUNC_ANS_FAX_MODE			/* ＡＮＳ／ＦＡ		*/
		&	~PRO_FUNC_TEL_MODE				/* ＴＥＬ			*/
		&	~PRO_FUNC_REMOTE_DIAG			/* リモート診断		*/
#if (PRO_PIN_ACCESS == ENABLE)
		|	PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#else
		&	~PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#endif
		|	PRO_FUNC_RING_MASTER			/* リングマスター	*/
		&	~PRO_FUNC_CLASS1				/* クラス１			*/
		&	~PRO_FUNC_CLASS2				/* クラス２			*/
		|	PRO_FUNC_POLLING_TX				/* ポーリング送信	*/
		|	PRO_FUNC_DB_POLLING_TX			/* 検索ポーリング送信 */
		|	PRO_FUNC_SECURE_RX				/* 親展受信			*/
		|	PRO_FUNC_RELAYED_TX				/* 中継配信			*/
#if 1 /* Clover では実際には参照されていないが、論理的には必要。 Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#else
@@		&	~PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#endif
		&	~PRO_FUNC_RELAYED_REPORT		/* 不達通知			*/
		&	~PRO_FUNC_DIALIN				/* ダイアルイン		*/
		|	PRO_FUNC_ERASE_TX_MEM_PAGE		/* 送信済みメモリの消去 */
		,
/*1*/	0
		|	PRO_FUNC_JUNK_FAX_MODE_TYPE		/* ﾀﾞｲﾚｸﾄﾒｰﾙﾓｰﾄﾞ別編 */
#if (PRO_COST == ENABLE) /* Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_COST					/* 料金管理			 */
#else
		&	~PRO_FUNC_COST					/* 料金管理			 */
#endif
		|	PRO_FUNC_F_CODE					/* Ｆコード			 */
		|	PRO_FUNC_CIPHER				/* アリロー			 */
		|	PRO_FUNC_ERROR_MONITOR			/* 通信エラーモニタ	 */
		|	PRO_FUNC_MAIL_COMP_CHK			/* 親展競合ｺﾝﾊﾟﾁ編	 */
		,
	/* 予備 */
/*2*/	0
		,
	/* 予備 */
/*3*/	0
		,
	/* 予備 */
/*4*/	0
		,
	/* 予備 */
	},
/*ボード７*/
	{
/*0*/	0
		&	~PRO_FUNC_TEL_FAX_MODE			/* ＴＥＬ／ＦＡＸ	*/
		&	~PRO_FUNC_ANS_FAX_MODE			/* ＡＮＳ／ＦＡ		*/
		&	~PRO_FUNC_TEL_MODE				/* ＴＥＬ			*/
		&	~PRO_FUNC_REMOTE_DIAG			/* リモート診断		*/
#if (PRO_PIN_ACCESS == ENABLE)
		|	PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#else
		&	~PRO_FUNC_PIN					/* ＰＩＮアクセス	*/
#endif
		|	PRO_FUNC_RING_MASTER			/* リングマスター	*/
		&	~PRO_FUNC_CLASS1				/* クラス１			*/
		&	~PRO_FUNC_CLASS2				/* クラス２			*/
		|	PRO_FUNC_POLLING_TX				/* ポーリング送信	*/
		|	PRO_FUNC_DB_POLLING_TX			/* 検索ポーリング送信 */
		|	PRO_FUNC_SECURE_RX				/* 親展受信			*/
		|	PRO_FUNC_RELAYED_TX				/* 中継配信			*/
#if 1 /* Clover では実際には参照されていないが、論理的には必要。 Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#else
@@		&	~PRO_FUNC_RELAYED_RELAY_TX		/* 中中継			*/
#endif
		&	~PRO_FUNC_RELAYED_REPORT		/* 不達通知			*/
		&	~PRO_FUNC_DIALIN				/* ダイアルイン		*/
		|	PRO_FUNC_ERASE_TX_MEM_PAGE		/* 送信済みメモリの消去 */
		,
/*1*/	0
		|	PRO_FUNC_JUNK_FAX_MODE_TYPE		/* ﾀﾞｲﾚｸﾄﾒｰﾙﾓｰﾄﾞ別編 */
#if (PRO_COST == ENABLE) /* Changed by H.Kubo 1998/04/24 */
		|	PRO_FUNC_COST					/* 料金管理			 */
#else
		&	~PRO_FUNC_COST					/* 料金管理			 */
#endif
		|	PRO_FUNC_F_CODE					/* Ｆコード			 */
		|	PRO_FUNC_CIPHER				/* アリロー			 */
		|	PRO_FUNC_ERROR_MONITOR			/* 通信エラーモニタ	 */
		|	PRO_FUNC_MAIL_COMP_CHK			/* 親展競合ｺﾝﾊﾟﾁ編	 */
		,
	/* 予備 */
/*2*/	0
		,
	/* 予備 */
/*3*/	0
		,
	/* 予備 */
/*4*/	0
		,
	/* 予備 */
	}
};
