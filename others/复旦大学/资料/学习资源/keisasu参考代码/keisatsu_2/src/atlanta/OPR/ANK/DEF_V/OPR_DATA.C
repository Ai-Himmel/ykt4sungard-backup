/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_DATA.C
*	Author		: 渡辺一章
*	Date		: 1996/10/16
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: オペレーション大域変数宣言
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\message.h"

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)	*//* Add By H.Fujimura 1999/01/06 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By H.Fujimura 1999/01/06 */ /* Add by Y.Kano 2003/07/11 */

#include	"\src\atlanta\define\std.h"
#endif
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#if (PRO_COPY_FAX_MODE == ENABLE)
#include	"\src\atlanta\define\sysmcopy.h"
#endif


/************************************
 * キースキャン関連
 ************************************/
#if (PRO_KEYPANEL == PANEL_HINOKI)		/* ＨＩＮＯＫＩ タイプ *//* 1998/09/21 by T.Soneoka */
	UBYTE	NewKeyData = 0;				/* 今回のキー入力データ(APL参照用) */
	UBYTE	NewKey = 0;					/* キー入力データ(割り込み内設定用) */
	UBYTE	InhibitKeyScan = 0;			/* キースキャン禁止／許可フラグ	*/
	UBYTE	ChangeToneFlag = 0;			/* トーン切り替えフラグ(0:Tone,1:Pulse) */
	UBYTE	TakeOverKey = 0;			/* エラー表示中のキー入力を引き継ぐ為の変数 */
	UBYTE	BeforeNewKey = 0;			/* 1回前のキー入力データ(割り込み内設定用) *//* Add by O.Kimoto 1999/02/26 */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ＳＡＴＳＵＫＩ２ タイプ *//* Add by Y.Kano 2003/07/11 */
	UBYTE	NewKeyData = 0;				/* 今回のキー入力データ(APL参照用) */
	UBYTE	NewKey = 0;					/* キー入力データ(割り込み内設定用) */
	UBYTE	InhibitKeyScan = 0;			/* キースキャン禁止／許可フラグ	*/
	UBYTE	ChangeToneFlag = 0;			/* トーン切り替えフラグ(0:Tone,1:Pulse) */
	UBYTE	TakeOverKey = 0;			/* エラー表示中のキー入力を引き継ぐ為の変数 */
	UBYTE	BeforeNewKey = 0;			/* 1回前のキー入力データ(割り込み内設定用) *//* Add by O.Kimoto 1999/02/26 */
#endif


UBYTE	NewKeyCode = 0;						/* キーコード								*/
UBYTE	OldKeyCode = 0;						/* 10ms前のキーコード						*/
UBYTE	HitKeyTime = 0;						/* キーが押されている時間					*/
UBYTE	NoKeyTime = 0;						/* キーが押されていない時間					*/
UBYTE	NoKeyFlag = 0;						/* 一定時間キー入力がないことを示すフラグ	*/
UBYTE	KeyPortNumber = 0;					/* スキャンしたキー入力ポートの番号			*/
UBYTE	OPR_InhibitKeyScan = 0;				/* キースキャン禁止／許可フラグ				*/

#if (PRO_CONT_KEY_INPUT == ENABLE)
	UBYTE	ContinuousKeyHit = 0;				/* 連続キー入力が確定したことを示すフラグ	*/
	UBYTE	ContinuousKeyTimer = 0;				/* 連続キー入力中のキーが押されている時間	*/
	UBYTE	ContinuousKeyInputEnable = 0;		/* 連続キー入力を許可するか禁止するか		*/
#endif

/************************************
 * TID
 ************************************/
UWORD	tskno_OPR_KeyTask        = 0xffff;	/* キースキャンタスク							*/
UWORD	tskno_OPR_BuzzerTask     = 0xffff;	/* ブザータスク									*/
UWORD	tskno_OPR_DispFlashTask  = 0xffff;	/* 点滅表示制御用タスク							*/
UWORD	tskno_OPR_SheetCheckTask = 0xffff;	/* シート切り替えチェックタスク					*/
UWORD	tskno_OPR_KeyTimerTask   = 0xffff;	/* キー待ち用タイマータスク						*/
UWORD	tskno_OPR_ChildTimerTask = 0xffff;	/* チャイルド表示用タイマータスク				*/
UWORD	tskno_OPR_ParamDispTask  = 0xffff;	/* コピーパラメーター優先表示用タイマータスク	*/
#if (PRO_MODEM == R288F)	/* Add By H.Fujimura 1999/01/06 */
UWORD	tskno_MDM_FactoryTask    = 0xffff;	/* 回線テスト用									*/
#endif

/************************************
 * 表示関連
 ************************************/

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)	*/	/* ＨＩＮＯＫＩ タイプ *//* 1998/09/21 by T.Soneoka */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ＨＩＮＯＫＩ タイプ *//* 1998/09/21 by T.Soneoka */

	UBYTE	LcdScanPos = 0;				/* LCD表示書き換え中の位置を示す */
	UWORD	LcdResetCount = 0;			/* LCD表示クリア・カウンタ */
	UWORD	CursorBlinkCont = 0;		/* カーソル点滅用カウンタ */
	UBYTE	CursorBlinkFlag = 0;		/* カーソル点滅フラグ */
	UBYTE	LcdCursorPos = 0;			/* カーソル表示位置 *//* 値が0xFF時、カーソル非表示状態 */
	
	UBYTE	CursorActionType = 0;		/* 動作種別(0:Limit,1:Rotation) */
	UBYTE	CursorLeftLimit = 0;		/* カーソル移動範囲：左端 */
	UBYTE	CursorRightLimit = 0;		/* カーソル移動範囲：右端 */
	UBYTE	CursorCurrentPos = 0;		/* カーソル現在位置 */

#if (0)
	UBYTE	DisplayBufHigh[DISPLAY_MAX + 1] = 0;
	UBYTE	DisplayBufLow[DISPLAY_MAX + 1] = 0;
	UBYTE	FuncDisplayBufHigh[DISPLAY_MAX + 1] = 0; /*入力関数内で使用 */
	UBYTE	FuncDisplayBufLow[DISPLAY_MAX + 1] = 0;  /*入力関数内で使用 */
#endif
	/************************************************************************
	 *	LED制御用ﾃﾞｰﾀ By M.IIDA
	 ************************************************************************/
	UBYTE	Led1Status = 0;
	UBYTE	Led1BlinkStatus = 0;
	UBYTE	Led2Status = 0;
	UBYTE	Led2BlinkStatus = 0;
	UBYTE	Led3Status = 0;
	UBYTE	Led3BlinkStatus = 0;
#endif

UBYTE	SubTitleDisplayBuffer[OPR_DISPLAY_MAX + 1] = {0};
UBYTE	DisplayBufferHigh[OPR_DISPLAY_MAX + 1] = {0};
UBYTE	DisplayBufferLow[OPR_DISPLAY_MAX + 1] = {0};
UBYTE	FunctionDisplayBufferHigh[OPR_DISPLAY_MAX + 1] = {0};	/* 入力関数内で使用					*/
UBYTE	FunctionDisplayBufferLow[OPR_DISPLAY_MAX + 1] = {0};	/* 入力関数内で使用					*/
UBYTE	FlashBufferHighMain[OPR_DISPLAY_MAX + 1] = {0};			/* 上段点滅表示用（メイン）			*/
UBYTE	FlashBufferHighSub[OPR_DISPLAY_MAX + 1] = {0};			/* 上段点滅表示用（サブ）			*/
UBYTE	FlashBufferLowMain[OPR_DISPLAY_MAX + 1] = {0};			/* 下段点滅表示用（メイン）			*/
UBYTE	FlashBufferLowSub[OPR_DISPLAY_MAX + 1] = {0};			/* 下段点滅表示用（サブ）			*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/01 by K.Okada */
UBYTE	TempInputBuffer[OPR_INPUT_BUFFER_MAX] = {0};
UBYTE	TonalTestDisplayBuffer[OPR_DISPLAY_MAX + 1] = {0};
#endif
#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/15 */
/************************************************************************
*          BY:	石橋正和
*        DATE:	Thu 2 Nov 1993
* DESCRIPTION:	カーソルの表示位置(0～119)
************************************************************************/
UBYTE	CursorPosition = 0;

/************************************************************************
*          BY:	清水政貴
*        DATE:	Fri 8 Mar 1996
* DESCRIPTION:	仮想フレームバッファ
*				（M66270FPはビットマップでＶＲＡＭを持っているため）
*				LCDのＶＲＡＭポインタ
************************************************************************/
UWORD	LCD_VirtualFrameBuffer[LCD_HEIGHT][LCD_WIDTH] = {0};
UBYTE	*LCD_Display = 0;

#pragma	section	LCDBUF	/* add 1999/06/18 by T.Soneoka */
struct LCD_DisplayData_t LCD_PageRAM[4] = {0};	/* LCD RAMアクセスのためのバッファ */
#pragma	section

UBYTE	DisplayBuffer0[LCD_WIDTH + 1];
UBYTE	DisplayBuffer1[LCD_WIDTH + 1];
UBYTE	DisplayBuffer2[LCD_WIDTH + 1];
UBYTE	DisplayBuffer3[LCD_WIDTH + 1];
#endif

/***************************************
 * 登録用ワークバッファ
 ****************************************/
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/10/12 */
struct	InputNumberData_t			InputNumber_Mercury = {0};		/* プレフィクス登録用のバッファ		*/
struct	CharacterInputData_t		CharacterInput_Mercury = {0};	/* 数字等の文字入力バッファ			*/
#endif
struct	InputNumberData_t			InputNumber = {0};			/* コマンド登録用のバッファ			*/
union	OperationBufferData_t		OPR_Buf = {0};				/* オペレーションバッファ			*/
struct	CharacterInputData_t		CharacterInput = {0};		/* 数字等の文字入力バッファ			*/
struct	SpecialCommandData_t		SpecialCommandValue = {0};	/* 応用通信入力バッファ				*/
union	OperationTimeData_t			OperationTime = {0};		/* 日時変換バッファ					*/
struct	TelControlData_t			TelControl = {0};			/* 電話オペレーション用バッファ		*/
#if (PRO_F_CODE == ENABLE)	/* by K.Watanabe 1998/01/09 */
struct	OPR_FcodeFunctionData_t		OPR_FcodeData = {0};		/* Ｆコード機能用データバッファ		*/
#endif
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/01/09 */
struct	OPR_CipherFunctionData_t	OPR_CipherData = {0};		/* 暗号化機能用データバッファ		*/
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998.03.12 by K.Okada */
struct	OPR_MailCommand_t			OPR_MailCommand = {0};		/* インターネットFAX用メール送信時ワークバッファ */
struct	OPR_INF_UserData_t			OPR_INF_UserData = {0};		/* インターネットFAX用ユーザデータバッファ */
struct	OPR_INF_TempAddressInput_t	OPR_INF_TempAddressInput = {0};
struct	OPR_INF_UpdateUserData_t	OPR_INF_UpdateUserData = {0};
#endif

/*****************************************
 * フラグ
 *****************************************/
UBYTE	OPR_TelBookTelephoneFlag = 0;		/* 電話帳による電話要求						*/
UBYTE	OPR_ChildErrorFlag = 0;				/* 登録エラー等のオペレーション中のエラー	*/
UBYTE	OPR_BatchTxEnableFlag = 0;			/* 一括送信許可禁止フラグ					*/
UBYTE	ReleaseCommandFileRequest = 0;
#if (PRO_MULTI_LINE == ENABLE)	/* 1996/11/20 Y.Matsukuma */	/* By M.Kotani 97/05/29 */
UBYTE	OPR_MultiDisplayFlag = 0;			/* マルチ表示フラグ							*/
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998.03.12 by K.Okada */
UBYTE MailTxEnableFlag = 0;					/* メール送信可能チェック要求 */
UBYTE MailCommandEndFlag = 0;				/* コマンド入力オペレーション終了 */
UBYTE ReleaseMailCommandFileRequest = 0;	/* メールコマンドファイル解放要求 */
UBYTE OPR_DisplayMaskingFlag = 0;			/* LCDマスク要求フラグ */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By H.Fujimura 1999/04/02 */
UBYTE	OPR_SpecialDoctorReportFlag = 0;	/* 医師会特ＲＯＭ用メッセージ送信フラグ		*/
 #endif
#endif

/*****************************************
 * ブーリアン変数
 *****************************************/
UBYTE	IsFlashDisplayHigh = 0;				/* 上段点滅表示制御								*/
UBYTE	IsFlashDisplayLow = 0;				/* 下段点滅表示制御								*/
#if (PRO_FBS == ENABLE)
UBYTE	IsBookDocSizeSet = 0;				/* ブック原稿サイズの設定状態確認				*/
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
UBYTE	IsCassetteManualChange = 0;			/* 用紙選択時　カセット／手差しの切り替え用		*/
UBYTE	IsPriorityParamDisplay = 0;			/* コピーパラメーター割り込み表示制御用			*/
UBYTE	IsMagnifiKeyInput = 0;				/* 拡大・縮小キー押下チェック用					*/
UBYTE	IsModifyCopyMagnifi = 0;			/* ADFに原稿セット時、自動倍率変更を行ったか	*/
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1997/11/25 */
UBYTE	IsSettingDensity = 0;				/* 濃度設定中のチェック用						*/
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
UBYTE	IsIdleDisplay = 0;					/* アイドルカウンタ表示フラグ					*/
#endif
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1998/01/28 */
UBYTE	IsTxOrScanStart = 0;				/* CommandOperation()で、送信等が開始されたか	*/
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)	/* Add By H.Fujimura 1999/01/06 */
UBYTE	IsSingleKeyOperation = TRUE;		/* 単一オペレーション有効						*/
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)		/* Add by Y.Kano 2003/07/11 */
UBYTE	IsSingleKeyOperation = TRUE;		/* 単一オペレーション有効						*/
UBYTE	IsDocumentSet = FALSE;				/* Added by SMuratec L.Z.W 2003/07/31 */
UBYTE	IsDocumentStoring = FALSE; 			/* Added by SMuratec L.Z.W 2003/11/07 */
#endif

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2)
UBYTE	IsScanReserved = FALSE;				/* QAT修正 Added by SMuratec 李 2004/11/09 */
UBYTE	IsCopyReserved = FALSE;				/* QAT修正 Added by SMuratec 李 2004/11/15 */
UBYTE	IsScanTx = FALSE;					/* QAT修正 Added by SMuratec 李 2004/11/09 */
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

/**************************************
 * 入力チェック用バッファ
 **************************************/
UBYTE	OPR_CharacterCheckBuffer[OPR_CHECK_BUFFER_MAX] = {0};
UBYTE	OPR_CharacterCheckPoint = 0;

/***************************************
 *  メッセージ
 ***************************************/
MESSAGE_t	OperationMessageToMain = {0};
#if (PRO_MODEM == R288F)	/* Add By H.Fujimura 1999/01/06 */
MESSAGE_t	LineFuncTxMsg = {0};
MESSAGE_t	*LineFuncRxMsg = 0;
#endif

/***************************************
 * 現在時刻退避用
 ***************************************/
UDWORD	BackUpCurrentTime = 0;
UBYTE	BackUpCurrentTimeSet = 0;

/******************************************
 * 確保したコマンドファイル番号
 * StatusがSYS_CMD_SETTINGになっているもの
 ******************************************/
UBYTE	SettingCommandFileNumber = NO_SETTING_COMMAND_FILE;

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/02/17
*             TYPE:
*      VAR TO HOLD:
*      DESCRIPTION:  コピーモード関係
************************************************************************/
#if (PRO_COPY_FAX_MODE == ENABLE)
struct	SYS_MultiCopyData_t OPR_CopyData = {0};		/* コピーモードの設定値							*/
UBYTE	OPR_CopyNumberInputFigure = 0;				/* コピー部数入力桁数							*/
UBYTE	OPR_NumberKeyInputMode = 0;					/* 数字キー入力内容切り替え用					*/
UBYTE	OPR_OldMagnification = 0;					/* コピー倍率入力時、確定前の倍率				*/
UBYTE	OPR_FixedMagnifiDocSize = 0;				/* 固定倍率原稿サイズ by K.Watanabe 1997/11/26	*/
UBYTE	OPR_CopyParamCheck = 0;						/* 用紙・倍率確認状態 by K.Watanabe 1997/12/05	*/
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/05/19
*             TYPE:
*      VAR TO HOLD:
*      DESCRIPTION:  ＣＧＲＡＭデータ書き込み制御用
************************************************************************/
#if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/16 */
UBYTE	*OPR_Writed_CGRAM_Address = 0;	/* 現在書き込まれているＣＧＲＡＭのアドレス */
#endif

/************************************************************************
*               BY:  Y.Matsukuma
*             DATE:  
*             TYPE:
*      VAR TO HOLD:
*      DESCRIPTION:  マルチ回線用変数
************************************************************************/
#if (PRO_MULTI_LINE == ENABLE)
UBYTE	OPR_InstallLineCount = 0;		/* マルチ回線設置モード登録時　回線カウント					*/
UBYTE	OPR_InstallOptionLine = 0;		/* マルチ回線設置モード登録時　使用出来るオプションボード	*/
UBYTE	OPR_MultiLineCount = 0;			/* マルチ回線カウント										*/
UDWORD	OPR_MultiDisplayTime = 0;		/* マルチ表示時間											*/
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/06/23
*             TYPE:  struct
*      VAR TO HOLD:
*      DESCRIPTION:  タイマー設定用変数
************************************************************************/
struct	Timer10msData_t GetKeyTimer = {0};		/* キー待ち用タイマー					*/
struct	Timer10msData_t ChildTimer = {0};		/* チャイルド表示用タイマー				*/
#if (PRO_COPY_FAX_MODE == ENABLE)
struct	Timer10msData_t ParamDispTimer = {0};	/* コピーパラメーター優先表示用タイマー	*/
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/08/07
*             TYPE:
*      VAR TO HOLD:
*      DESCRIPTION:  メモリダンプ用変数
************************************************************************/
UBYTE	*OPR_MemoryDumpAddress = 0;		/* メモリダンプ開始アドレス	*/
UDWORD	OPR_MemoryDumpLength = 0;		/* メモリダンプ長			*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/10/09
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  機器状態表示情報
************************************************************************/
UBYTE	OPR_DispInfo = 0;

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/11/12
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  ダイヤル番号入力での入力情報
************************************************************************/
UBYTE	OPR_InputDialInfo = 0;

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/11/27
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  濃度変更キー
************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
UBYTE	OPR_ChangeDensityKey = 0;
#endif

/* E設 中西さんからの依頼 Busy Flag がこけない時LCDCをリセットする T.Nose 1997/12/01 */
UBYTE DEBUG_LCD_ResetFlag = 0;

/************************************************************************
*               BY:  S.Fukui
*             DATE:  1997/12/04
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  ＢＣＤチェック用バッファ
************************************************************************/
#if defined(FRA)
UBYTE BCD_CheckBuffer[SYS_TEL_2DIGIT_MAX] = {0};
#endif

/************************************************************************
*               BY:  Y.Matsukuma
*             DATE:  1998/07/07
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  ミノルタテストプリント用バッファ
************************************************************************/
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
UBYTE OPR_MinoltaPatternCheck = 0;
UBYTE OPR_MinoltaOnetouch = 0;
UBYTE OPR_MinoltaPagesCheck = 0;
UBYTE OPR_MinoltaPatternItem = 0;	/* 1998/08/31 Y.Matsukuma */
UBYTE OPR_MinoltaDisplayCheck = 0;
#endif

/************************************************************************
*               BY:  S.Wang
*             DATE:  1998/07/25
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  シンガポール市場調査ＲＯＭ用バッファ
************************************************************************/
#if (PRO_SGP_TEST_ROM == ENABLE)
UBYTE SYS_SgpDialBuffer[SYS_DIRECT_DIAL_MAX] = {0};
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Matsukuma */
UBYTE	OPR_FeedinDispTime = 0;		/* 原稿繰り込み表示時間 */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

/* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
** byO.Kimoto 1999/02/06
*/
UBYTE	LCD_DisplayBufferHigh[OPR_DISPLAY_MAX + 1] = {0};
UBYTE	LCD_DisplayBufferLow[OPR_DISPLAY_MAX + 1] = {0};
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1998/06/25
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  ＬＣＤ使用状況
************************************************************************/
#if (PRO_ANK_TO_KANJI == ENABLE)
UBYTE	DisplayUsingCondition = 0;
#endif

#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
/************************************************************************
*               BY:  N.KONDO
*             DATE:  2001/09/14
*             TYPE:  define
*      DESCRIPTION:  リスケジュール＆ジョブエディットオペレーション
************************************************************************/
UBYTE	OPR_ReviewCommandOprNextStep = 0;		/* 予約確認オペレーション状態				*/
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) || defined(HINOKI3)	/* Add by Y.Kano 2003/08/29 */ /* Add by Y.Kano 2004/12/21 */
/************************************************************************
*               BY:  Y.Kano
*             DATE:  2003/08/29
*             TYPE:  define
*      DESCRIPTION:  ボリューム設定オペレーション
************************************************************************/
UBYTE	DispChangeFlag = 0;		/* ブザー、モニターボリューム表示切替	*/
/************************************************************************
*               BY:  SMuratec L.Z.W
*             DATE:  2003/08/14
*             TYPE:  define
*      DESCRIPTION:  文字コード入力
************************************************************************/
UBYTE	OPR_CharacterSetEnd = 0;		/* 文字コード入力完了				*/

/* Added by SMuratec K.W.Q 2003/08/26 */
/************************************************************************
*               BY:  K.Watanabe
*             DATE:  2000/05/10
*             TYPE:  CONST UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  チェッカー用ワーディング
*                    （言語切り替えが必要無いので、ここで定義します）
************************************************************************/
CONST UBYTE	OPR_CheckerMainTestWord[]		= "##MAIN_PCBｼﾞﾄﾞｳﾃｽﾄ##";
CONST UBYTE	OPR_CheckerPanelAssyWord[]		= "##   PANEL ASSY   ##";
CONST UBYTE OPR_TestCompleteWord[]			= " **   Complete   ** ";
/************************************************************************
*               BY:  Y.Kano
*             DATE:  2003/10/17
*             TYPE:  define
*      DESCRIPTION:  PS2ボリューム設定オペレーション
************************************************************************/
UBYTE	PS2Volumue = 0;			/* PS2ボリューム表示	*/
UBYTE	OPR_PS2_Adjust_Flg = 0;	/* PS2調整中フラグ ローカルに反映 by Y.Kano 2003/12/04 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */


#if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)
UBYTE	OPR_PaperSensor_Adjust_Flg = FALSE;
#endif	/* End of (PRO_PAPER_AD_SENSOR_INIT == ENABLE) */

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/31 */
UBYTE	AttributeTimeoutCheck = 0;	/* ０： 属性タイムアウト検視しない	１：属性タイムアウト検視する */
#endif		/* End of (defined (KEISATSU)) */
