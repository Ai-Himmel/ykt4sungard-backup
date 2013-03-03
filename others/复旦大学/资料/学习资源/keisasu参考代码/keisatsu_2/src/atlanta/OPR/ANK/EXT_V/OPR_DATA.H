/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_DATA.H
*	Author		: 渡辺一章
*	Date		: 1996/10/17
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: オペレーション大域変数宣言
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef OPR_DATA_H
	#define OPR_DATA_H	1

#include	"\src\atlanta\define\message.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\define\timer10.h"

#if (PRO_COPY_FAX_MODE == ENABLE)
#include	"\src\atlanta\define\sysmcopy.h"
#endif

/************************************
 * キースキャン関連
 ************************************/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 		/* ＨＩＮＯＫＩ タイプ *//* 1998/09/21 by T.Soneoka */
	extern UBYTE	NewKeyData;				/* 今回のキー入力データ(APL参照用) */
	extern UBYTE	NewKey;					/* キー入力データ(割り込み内設定用) */
	extern UBYTE	InhibitKeyScan;			/* キースキャン禁止／許可フラグ	*/
	extern UBYTE	ChangeToneFlag;			/* トーン切り替えフラグ(0:Tone,1:Pulse) */
	extern UBYTE	TakeOverKey;			/* エラー表示中のキー入力を引き継ぐ為の変数 */
	extern UBYTE	BeforeNewKey;			/* 1回前のキー入力データ(割り込み内設定用) *//* Add by O.Kimoto 1999/02/26 */
#endif

extern UBYTE	NewKeyCode;					/* キーコード								*/
extern UBYTE	OldKeyCode;					/* 10ms前のキーコード						*/
extern UBYTE	HitKeyTime;					/* キーが押されている時間					*/
extern UBYTE	NoKeyTime;					/* キーが押されていない時間					*/
extern UBYTE	NoKeyFlag;					/* 一定時間キー入力がないことを示すフラグ	*/
extern UBYTE	KeyPortNumber;				/* スキャンしたキー入力ポートの番号			*/
extern UBYTE	OPR_InhibitKeyScan;			/* キースキャン禁止／許可フラグ				*/

#if (PRO_CONT_KEY_INPUT == ENABLE)
	extern UBYTE	ContinuousKeyHit;			/* 連続キー入力が確定したことを示すフラグ	*/
	extern UBYTE	ContinuousKeyTimer;			/* 連続キー入力中のキーが押されている時間	*/
	extern UBYTE	ContinuousKeyInputEnable;	/* 連続キー入力を許可するか禁止するか		*/
#endif


/************************************
 * TID
 ************************************/
extern UWORD	tskno_OPR_KeyTask;			/* キースキャンタスク							*/
extern UWORD	tskno_OPR_BuzzerTask;		/* ブザータスク									*/
extern UWORD	tskno_OPR_DispFlashTask;	/* 点滅表示制御用タスク							*/
extern UWORD	tskno_OPR_SheetCheckTask;	/* シート切り替えチェックタスク					*/
extern UWORD	tskno_OPR_KeyTimerTask;		/* キー待ち用タイマータスク						*/
extern UWORD	tskno_OPR_ChildTimerTask;	/* チャイルド表示用タイマータスク				*/
extern UWORD	tskno_OPR_ParamDispTask;	/* コピーパラメーター優先表示用タイマータスク	*/
#if (PRO_MODEM == R288F)	/* Add By H.Fujimura 1999/01/06 */
extern UWORD	tskno_MDM_FactoryTask;		/* 回線テスト用									*/
#endif

/************************************
 * 表示関連
 ************************************/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 		/* ＨＩＮＯＫＩ タイプ *//* 1998/09/21 by T.Soneoka */
	extern UBYTE	LcdScanPos;				/* LCD表示書き換え中の位置を示す */
	extern UWORD	LcdResetCount;			/* LCD表示クリア・カウンタ */
	extern UWORD	CursorBlinkCont;		/* カーソル点滅用カウンタ */
	extern UBYTE	CursorBlinkFlag;		/* カーソル点滅フラグ */
	extern UBYTE	LcdCursorPos;			/* カーソル表示位置 *//* 値が0xFF時、カーソル非表示状態 */
	
	extern UBYTE	CursorActionType;		/* 動作種別(0:Limit,1:Rotation) */
	extern UBYTE	CursorLeftLimit;		/* カーソル移動範囲：左端 */
	extern UBYTE	CursorRightLimit;		/* カーソル移動範囲：右端 */
	extern UBYTE	CursorCurrentPos;		/* カーソル現在位置 */
#if (0)
	extern UBYTE	DisplayBufHigh[OPR_DISPLAY_MAX + 1];
	extern UBYTE	DisplayBufLow[OPR_DISPLAY_MAX + 1];
	extern UBYTE	FuncDisplayBufHigh[OPR_DISPLAY_MAX + 1]; /*入力関数内で使用 */
	extern UBYTE	FuncDisplayBufLow[OPR_DISPLAY_MAX + 1];  /*入力関数内で使用 */
#endif
	/************************************************************************
	 *	LED制御用ﾃﾞｰﾀ By M.IIDA
	 ************************************************************************/
	extern UBYTE	Led1Status;
	extern UBYTE	Led1BlinkStatus;
	extern UBYTE	Led2Status;
	extern UBYTE	Led2BlinkStatus;
	extern UBYTE	Led3Status;
	extern UBYTE	Led3BlinkStatus;
#endif
extern UBYTE	SubTitleDisplayBuffer[OPR_DISPLAY_MAX + 1];
extern UBYTE	DisplayBufferHigh[OPR_DISPLAY_MAX + 1];
extern UBYTE	DisplayBufferLow[OPR_DISPLAY_MAX + 1];
extern UBYTE	FunctionDisplayBufferHigh[OPR_DISPLAY_MAX + 1];		/* 入力関数内で使用					*/
extern UBYTE	FunctionDisplayBufferLow[OPR_DISPLAY_MAX + 1];		/* 入力関数内で使用					*/
extern UBYTE	FlashBufferHighMain[OPR_DISPLAY_MAX + 1];			/* 上段点滅表示用（メイン）			*/
extern UBYTE	FlashBufferHighSub[OPR_DISPLAY_MAX + 1];			/* 上段点滅表示用（サブ）			*/
extern UBYTE	FlashBufferLowMain[OPR_DISPLAY_MAX + 1];			/* 下段点滅表示用（メイン）			*/
extern UBYTE	FlashBufferLowSub[OPR_DISPLAY_MAX + 1];				/* 下段点滅表示用（サブ）			*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/01 by K.Okada */
extern UBYTE	TempInputBuffer[OPR_INPUT_BUFFER_MAX];
extern UBYTE	TonalTestDisplayBuffer[OPR_DISPLAY_MAX + 1];
#endif
#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/15 */
/************************************************************************
*          BY:	石橋正和
*        DATE:	Thu 2 Nov 1993
* DESCRIPTION:	カーソルの表示位置(0～119)
************************************************************************/
extern UBYTE CursorPosition;

/************************************************************************
*          BY:	清水政貴
*        DATE:	Fri 08 Mar 1996
* DESCRIPTION:	仮想フレームバッファ
*				ＬＣＤのＶＲＡＭアドレス
************************************************************************/
extern UWORD LCD_VirtualFrameBuffer[LCD_HEIGHT][LCD_WIDTH];
extern UBYTE *LCD_Display;

extern struct LCD_DisplayData_t LCD_PageRAM[4];	/* LCD RAMアクセスのためのバッファ */

extern UBYTE	DisplayBuffer0[LCD_WIDTH + 1];
extern UBYTE	DisplayBuffer1[LCD_WIDTH + 1];
extern UBYTE	DisplayBuffer2[LCD_WIDTH + 1];
extern UBYTE	DisplayBuffer3[LCD_WIDTH + 1];
#endif

/***************************************
 * 登録用ワークバッファ
 ****************************************/
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/10/12 */
extern struct	InputNumberData_t			InputNumber_Mercury;	/* プレフィクス登録用のバッファ		*/
extern struct	CharacterInputData_t		CharacterInput_Mercury;	/* 数字等の文字入力バッファ			*/
#endif
extern struct	InputNumberData_t			InputNumber;			/* コマンド登録用のバッファ			*/
extern union	OperationBufferData_t		OPR_Buf;				/* オペレーションバッファ			*/
extern struct	CharacterInputData_t		CharacterInput;			/* 数字等の文字入力バッファ			*/
extern struct	SpecialCommandData_t		SpecialCommandValue;	/* 応用通信入力バッファ				*/
extern union	OperationTimeData_t			OperationTime;			/* 日時変換バッファ					*/
extern struct	TelControlData_t			TelControl;				/* 電話オペレーション用バッファ		*/
#if (PRO_F_CODE == ENABLE)	/* by K.Watanabe 1998/01/09 */
extern struct	OPR_FcodeFunctionData_t		OPR_FcodeData;			/* Ｆコード機能用データバッファ		*/
#endif
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/01/09 */
extern struct	OPR_CipherFunctionData_t	OPR_CipherData;			/* 暗号化機能用データバッファ		*/
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
extern struct	OPR_MailCommand_t			OPR_MailCommand;		/* インターネットFAX用メール送信時ワークバッファ */
extern struct	OPR_INF_UserData_t			OPR_INF_UserData;		/* インターネットFAX用ユーザデータバッファ */
extern struct	OPR_INF_TempAddressInput_t	OPR_INF_TempAddressInput;
extern struct	OPR_INF_UpdateUserData_t	OPR_INF_UpdateUserData;
#endif

/*****************************************
 * フラグ
 *****************************************/
extern UBYTE	OPR_TelBookTelephoneFlag;	/* 電話帳による電話要求						*/
extern UBYTE	OPR_ChildErrorFlag;			/* 登録エラー等のオペレーション中のエラー	*/
extern UBYTE	OPR_BatchTxEnableFlag;		/* 一括送信許可禁止フラグ					*/
extern UBYTE	ReleaseCommandFileRequest;
#if (PRO_MULTI_LINE == ENABLE)	/* 1996/11/20 Y.Matsukuma */	/* By M.Kotani 97/05/29 */
extern UBYTE	OPR_MultiDisplayFlag;		/* マルチ表示フラグ							*/
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
extern UBYTE	MailTxEnableFlag;				/* メール送信可能チェック要求 */
extern UBYTE	MailCommandEndFlag;				/* コマンド入力オペレーション終了 */
extern UBYTE	ReleaseMailCommandFileRequest;	/* メールコマンドファイル解放要求 */
extern UBYTE	OPR_DisplayMaskingFlag;			/* LCDマスク要求フラグ */
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By H.Fujimura 1999/04/02 */
extern UBYTE	OPR_SpecialDoctorReportFlag;/* 医師会特ＲＯＭ用メッセージ送信フラグ		*/
 #endif
#endif

/*****************************************
 * ブーリアン変数
 *****************************************/
extern UBYTE	IsFlashDisplayHigh;			/* 上段点滅表示制御								*/
extern UBYTE	IsFlashDisplayLow;			/* 下段点滅表示制御								*/
#if (PRO_FBS == ENABLE)
extern UBYTE	IsBookDocSizeSet;			/* ブック原稿サイズの設定状態確認				*/
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
extern UBYTE	IsCassetteManualChange;		/* 用紙選択時　カセット／手差しの切り替え用		*/
extern UBYTE	IsPriorityParamDisplay;		/* コピーパラメーター割り込み表示制御用			*/
extern UBYTE	IsMagnifiKeyInput;			/* 拡大・縮小キー押下チェック用					*/
extern UBYTE	IsModifyCopyMagnifi;		/* ADFに原稿セット時、自動倍率変更を行ったか	*/
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1997/11/25 */
extern UBYTE	IsSettingDensity;			/* 濃度設定中のチェック用						*/
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
extern UBYTE	IsIdleDisplay;				/* アイドルカウンタ表示フラグ					*/
#endif
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1998/01/28 */
extern UBYTE	IsTxOrScanStart;			/* CommandOperation()で、送信等が開始されたか	*/
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/06 */
extern UBYTE	IsSingleKeyOperation;		/* 単一オペレーション有効／無効					*/
extern UBYTE	IsDocumentSet;				/* DocmentSet 有効／無効 *//* Added by SMuratec L.Z.W 2003/07/31 */
extern UBYTE	IsDocumentStoring;			/* Added by SMuratec L.Z.W 2003/11/07 */
#endif
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2)
extern UBYTE	IsScanReserved;				/* QAT修正 Added by SMuratec 李 2004/11/09 */
extern UBYTE	IsCopyReserved;				/* QAT修正 Added by SMuratec 李 2004/11/15 */
extern UBYTE	IsScanTx;					/* QAT修正 Added by SMuratec 李 2004/11/09 */
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

/**************************************
 * 入力チェック用バッファ
 **************************************/
extern UBYTE	OPR_CharacterCheckBuffer[OPR_CHECK_BUFFER_MAX];
extern UBYTE	OPR_CharacterCheckPoint;

/***************************************
 *  メッセージ
 ***************************************/
extern MESSAGE_t	OperationMessageToMain;
#if (PRO_MODEM == R288F)	/* Add By H.Fujimura 1999/01/06 */
extern MESSAGE_t	LineFuncTxMsg;
extern MESSAGE_t	*LineFuncRxMsg;
#endif

/***************************************
 * 現在時刻退避用
 ***************************************/
extern UDWORD	BackUpCurrentTime;
extern UBYTE	BackUpCurrentTimeSet;

/******************************************
 * 確保したコマンドファイル番号
 * StatusがSYS_CMD_SETTINGになっているもの
 ******************************************/
extern UBYTE	SettingCommandFileNumber;

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/02/17
*             TYPE:
*      VAR TO HOLD:
*      DESCRIPTION:  コピーモード関係
************************************************************************/
#if (PRO_COPY_FAX_MODE == ENABLE)
extern struct	SYS_MultiCopyData_t OPR_CopyData;	/* コピーモードの設定値							*/
extern UBYTE	OPR_CopyNumberInputFigure;			/* コピー部数入力桁数							*/
extern UBYTE	OPR_NumberKeyInputMode;				/* 数字キー入力内容切り替え用					*/
extern UBYTE	OPR_OldMagnification;				/* コピー倍率入力時、確定前の倍率				*/
extern UBYTE	OPR_FixedMagnifiDocSize;			/* 固定倍率原稿サイズ by K.Watanabe 1997/11/26	*/
extern UBYTE	OPR_CopyParamCheck;					/* 用紙・倍率確認状態 by K.Watanabe 1997/12/05	*/
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/05/19
*             TYPE:
*      VAR TO HOLD:
*      DESCRIPTION:  ＣＧＲＡＭデータ書き込み制御用
************************************************************************/
#if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/16 */
extern UBYTE	*OPR_Writed_CGRAM_Address;	/* 現在書き込まれているＣＧＲＡＭのアドレス */
#endif

/************************************************************************
*               BY:  Y.Matsukuma
*             DATE:  
*             TYPE:
*      VAR TO HOLD:
*      DESCRIPTION:  マルチ回線用変数
************************************************************************/
#if (PRO_MULTI_LINE == ENABLE)
extern UBYTE	OPR_InstallLineCount;		/* マルチ回線設置モード登録時　回線カウント					*/
extern UBYTE	OPR_InstallOptionLine;		/* マルチ回線設置モード登録時　使用出来るオプションボード	*/
extern UBYTE	OPR_MultiLineCount;			/* マルチ回線カウント										*/
extern UDWORD	OPR_MultiDisplayTime;		/* マルチ表示時間											*/
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/06/23
*             TYPE:  struct
*      VAR TO HOLD:
*      DESCRIPTION:  タイマー設定用変数
************************************************************************/
extern struct	Timer10msData_t GetKeyTimer;	/* キー待ち用タイマー					*/
extern struct	Timer10msData_t ChildTimer;		/* チャイルド表示用タイマー				*/
#if (PRO_COPY_FAX_MODE == ENABLE)
extern struct	Timer10msData_t ParamDispTimer;	/* コピーパラメーター優先表示用タイマー	*/
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/08/07
*             TYPE:
*      VAR TO HOLD:
*      DESCRIPTION:  メモリダンプ用変数
************************************************************************/
extern UBYTE	*OPR_MemoryDumpAddress;		/* メモリダンプ開始アドレス	*/
extern UDWORD	OPR_MemoryDumpLength;		/* メモリダンプ長			*/

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/10/09
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  機器状態表示情報
************************************************************************/
extern UBYTE	OPR_DispInfo;

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/11/12
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  ダイヤル番号入力での入力情報
************************************************************************/
extern UBYTE	OPR_InputDialInfo;

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/11/27
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  濃度変更キー
************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
extern UBYTE	OPR_ChangeDensityKey;
#endif

/* E設 中西さんからの依頼 Busy Flag がこけない時LCDCをリセットする T.Nose 1997/12/01 */
extern UBYTE DEBUG_LCD_ResetFlag;

/************************************************************************
*               BY:  S.Fukui
*             DATE:  1997/12/04
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  ＢＣＤチェック用バッファ
************************************************************************/
#if defined(FRA)
extern UBYTE	BCD_CheckBuffer[SYS_TEL_2DIGIT_MAX];
#endif

/************************************************************************
*               BY:  Y.Matsukuma
*             DATE:  1998/07/07
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  ミノルタテストプリント用バッファ
************************************************************************/
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
extern UBYTE	OPR_MinoltaPatternCheck;
extern UBYTE 	OPR_MinoltaOnetouch;
extern UBYTE 	OPR_MinoltaPagesCheck;
extern UBYTE 	OPR_MinoltaPatternItem;	/* 1998/08/31 Y.Matsukuma */
extern UBYTE 	OPR_MinoltaDisplayCheck;
#endif

/************************************************************************
*               BY:  S.Wang
*             DATE:  1998/07/25
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  シンガポール市場調査ＲＯＭ用バッファ
************************************************************************/
#if (PRO_SGP_TEST_ROM == ENABLE)
extern UBYTE SYS_SgpDialBuffer[SYS_DIRECT_DIAL_MAX];
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Matsukuma */
extern UBYTE	OPR_FeedinDispTime;		/* 原稿繰り込み表示時間 */
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
** byO.Kimoto 1999/02/06
*/
extern UBYTE	LCD_DisplayBufferHigh[OPR_DISPLAY_MAX + 1];
extern UBYTE	LCD_DisplayBufferLow[OPR_DISPLAY_MAX + 1];
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1998/06/25
*             TYPE:  UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  ＬＣＤ使用状況
************************************************************************/
#if (PRO_ANK_TO_KANJI == ENABLE)
extern UBYTE	DisplayUsingCondition;
#endif

#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
/************************************************************************
*               BY:  N.KONDO
*             DATE:  2001/09/14
*             TYPE:  define
*      DESCRIPTION:  リスケジュール＆ジョブエディットオペレーション
************************************************************************/
extern UBYTE	OPR_ReviewCommandOprNextStep;		/* 予約確認オペレーション状態				*/
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) || defined(HINOKI3) || defined(KEISATSU)/* Added by SMuratec L.Z.W 2003/08/14 */ /* Add by Y.Kano 2004/12/21 */
/************************************************************************
*               BY:  Y.Kano
*             DATE:  2003/08/29
*             TYPE:  define
*      DESCRIPTION:  ボリューム設定オペレーション
************************************************************************/
extern UBYTE	DispChangeFlag;			/* ブザー、モニターボリューム表示切替	*/
/************************************************************************
*               BY:  SMuratec L.Z.W
*             DATE:  2003/08/14
*             TYPE:  define
*      DESCRIPTION:  文字コード入力
************************************************************************/
extern UBYTE	OPR_CharacterSetEnd;		/* 文字コード入力完了				*/

/* Added by SMuratec K.W.Q 2003/08/26 */
/************************************************************************
*               BY:  K.Watanabe
*             DATE:  2000/05/10
*             TYPE:  CONST UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  チェッカー用ワーディング
*                    （言語切り替えが必要無いので、ここで定義します）
************************************************************************/
extern CONST UBYTE	OPR_CheckerMainTestWord[];
extern CONST UBYTE	OPR_CheckerPanelAssyWord[];
extern CONST UBYTE	OPR_TestCompleteWord[];
/************************************************************************
*               BY:  Y.Kano
*             DATE:  2003/10/17
*             TYPE:  define
*      DESCRIPTION:  PS2ボリューム設定オペレーション
************************************************************************/
extern UBYTE	PS2Volumue;				/* PS2ボリューム表示	*/
extern UBYTE	OPR_PS2_Adjust_Flg;		/* PS2調整中フラグ ローカルに反映 by Y.Kano 2003/12/04 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */



#if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)
extern UBYTE	OPR_PaperSensor_Adjust_Flg;
#endif	/* End of (PRO_PAPER_AD_SENSOR_INIT == ENABLE) */

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/31 */
extern UBYTE	AttributeTimeoutCheck;
#endif		/* End of (defined (KEISATSU)) */

#endif	/* #ifndef OPR_DATA_H */
