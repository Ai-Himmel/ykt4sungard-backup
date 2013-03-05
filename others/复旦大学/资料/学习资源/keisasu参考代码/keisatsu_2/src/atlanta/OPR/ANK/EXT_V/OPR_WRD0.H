/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_WRD0.H
*	Author		: 渡辺一章
*	Date		: 1996/10/17
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: オペレーションワーディング宣言
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef OPR_WRD_0
	#define OPR_WRD_0	1

#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/17 */
/* POPLAR_B NTT対応でワーディングファイルを新規に作成しましたが、全オペレーションのincludeファイルを
** 条件コンパイルで分けるのは大変なので、ここだけで対応します
*/
#include	"\src\atlanta\opr\ank\ext_v\ntt_wrd0.h"

#else
#include	"\src\atlanta\define\product.h"

#if (PRO_CPU == SH7043)	/* 各国ワーディング先頭位置認識用 1996/07/04 T.Nose */
extern CONST UBYTE	D2W_WordingTop[];
extern CONST UBYTE	D2W_1stWordingTop[];
extern CONST UBYTE	D2W_2ndWordingTop[];
extern CONST UBYTE	D2W_3rdWordingTop[];
#endif

extern CONST UBYTE	D2W_WordingHead[];
extern CONST UBYTE	D2W_Null[];

/* 待機モード */
extern CONST UBYTE	D2W_TelReady[];
extern CONST UBYTE	D2W_FaxReady[];
extern CONST UBYTE	D2W_FaxTelReady[];
extern CONST UBYTE	D2W_TelFaxReady[];
extern CONST UBYTE	D2W_AnsFaxReady[];
extern CONST UBYTE	D2W_DialInReady[];
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1997/12/26 */
extern CONST UBYTE	D2W_ScannerTransportReady[];
#endif

/* コピーモードの表示 */
#if (PRO_COPY_FAX_MODE == ENABLE)
extern CONST UBYTE	D2W_CopyReady[];
extern CONST UBYTE	D2W_ManualCopyReady[];
extern CONST UBYTE	D2W_CopyImpossibleReady[];
extern CONST UBYTE	D2W_InputCopyMagnifi[];
extern CONST UBYTE	D2W_CopyMagnifiError[];
extern CONST UBYTE	D2W_ConfirmCopyMagnifi[];
#endif

/* コマンド登録中の表示（上段） */
extern CONST UBYTE	D2W_EnterFaxNumber[];
extern CONST UBYTE	D2W_InputGroupNumber[];
extern CONST UBYTE	D2W_InputSpeedDialNumber[];
extern CONST UBYTE	D2W_PressStart[];
extern CONST UBYTE	D2W_PressStartAgain[];
extern CONST UBYTE	D2W_PressEnterKey[];

/* コピー部数入力中の表示（上段） */
extern CONST UBYTE	D2W_SetCopyUnits[];

/* 選択を促す表示（点滅する表示 ) */
extern CONST UBYTE	D2W_ProgramEnter[];
extern CONST UBYTE	D2W_ProgramClear[];
#if (PRO_CIPHER == ENABLE)
extern CONST UBYTE	D2W_EnterClesr[];
#endif
extern CONST UBYTE	D2W_EnterStop[];
extern CONST UBYTE	D2W_CopyStop[];
extern CONST UBYTE	D2W_StartStop[];
extern CONST UBYTE	D2W_SpecialCommunicationEnter[];
extern CONST UBYTE	D2W_ReviewStop[];
extern CONST UBYTE	D2W_CheckProgramEnter[];
extern CONST UBYTE	D2W_CheckProgramClear[];
extern CONST UBYTE	D2W_CheckStartStop[];
#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
extern CONST UBYTE	D2W_CommunicationConfirmEnter[];
#endif

/*----------------------------------*
 *	応用機能
 *----------------------------------*/
/* 機能選択中 */
extern CONST UBYTE	D2W_SetDelayedTransmission[];
extern CONST UBYTE	D2W_SetSecureTransmission[];
extern CONST UBYTE	D2W_SetRelayTransmission[];
extern CONST UBYTE	D2W_SetPolling[];
extern CONST UBYTE	D2W_SetBatchTransmission[];
extern CONST UBYTE	D2W_SetContPolling[];
extern CONST UBYTE	D2W_SetFcodeTransmission[];
extern CONST UBYTE	D2W_SetFcodePolling[];
extern CONST UBYTE	D2W_SetCipherTransmission[];

/* 各機能の詳細データ設定中（上段） */
extern CONST UBYTE	D2W_DelayedTransmission[];
extern CONST UBYTE	D2W_SecureTransmission[];
extern CONST UBYTE	D2W_RelayTransmission[];
extern CONST UBYTE	D2W_PollingCommunication[];
extern CONST UBYTE	D2W_BatchTransmission[];
extern CONST UBYTE	D2W_ContinuousPolling[];
extern CONST UBYTE	D2W_InputSubAddressNumber[];
extern CONST UBYTE	D2W_InputPasswordNumber[];
extern CONST UBYTE	D2W_SelectCipherExtensionKey[];

/* 各機能の詳細データ設定中（下段） */
extern CONST UBYTE	D2W_EnterDelayedTxTime[];
extern CONST UBYTE	D2W_InputMailBoxNumber[];
extern CONST UBYTE	D2W_RelayTxGroupNumber[];
extern CONST UBYTE	D2W_InputFileNumber[];
extern CONST UBYTE	D2W_BatchTxBoxNumber[];
extern CONST UBYTE	D2W_BatchBoxIndexNumber[];
extern CONST UBYTE	D2W_EnterContPollStartTime[];
extern CONST UBYTE	D2W_EnterContPollEndTime[];

/*----------------------------------*
 *	濃度設定
 *----------------------------------*/
extern CONST UBYTE	D2W_SetPaperContrast[];
extern CONST UBYTE	D2W_ContrastLightDark[];

/*----------------------------------*
 *	機器エラー
 *----------------------------------*/

/* カバー */
extern CONST UBYTE	D2W_PleaseCloseScannerCover[];
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
extern CONST UBYTE	D2W_PleaseClose1stJamCover[];
extern CONST UBYTE	D2W_PleaseClose2ndJamCover[];
extern CONST UBYTE	D2W_PleaseClose3rdJamCover[];
extern CONST UBYTE	D2W_PleaseOpen1stJamCover[];
extern CONST UBYTE	D2W_PleaseOpen2ndJamCover[];
extern CONST UBYTE	D2W_PleaseOpen3rdJamCover[];
extern CONST UBYTE	D2W_PleaseOpenTopCover[];
 #if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1998/01/28 */
extern CONST UBYTE	D2W_PleaseOpenPrinterCover[];
 #endif
extern CONST UBYTE	D2W_PleaseOpenCloseScanCover[];
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
extern CONST UBYTE	D2W_PleaseClosePrinterCover[];
#endif
#if (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/15 */
extern CONST UBYTE	D2W_ScannerFeedErrorLow[];
#endif

/* カセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
extern CONST UBYTE	D2W_PleaseCloseLowerCassette[];
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
extern CONST UBYTE	D2W_PleaseClose1stCassette[];
extern CONST UBYTE	D2W_PleaseClose2ndCassette[];
extern CONST UBYTE	D2W_PleaseClose3rdCassette[];
#endif

/* 記録紙 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
extern CONST UBYTE	D2W_ReplaceRxPaper[];
extern CONST UBYTE	D2W_NoSamePaper[];
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
extern CONST UBYTE	D2W_ReplaceRxPaper[];
extern CONST UBYTE	D2W_ReplaceUpperRxPaper[];
extern CONST UBYTE	D2W_ReplaceLowerRxPaper[];
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
extern CONST UBYTE	D2W_Cassette1[];
extern CONST UBYTE	D2W_Cassette2[];
extern CONST UBYTE	D2W_Cassette3[];
extern CONST UBYTE	D2W_ManualCassette[];
#endif
extern CONST UBYTE	D2W_RemoveManualPaper[];
extern CONST UBYTE	D2W_CheckPaperSize[];
extern CONST UBYTE	D2W_PleaseOpenCloseTopCover[];
#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1998/01/28 */
extern CONST UBYTE	D2W_PleaseOpenClosePrinterCover[];
#endif

/* プリンター */
extern CONST UBYTE	D2W_PleaseRemovePaper[];
extern CONST UBYTE	D2W_PleaseSupplyToner[];
extern CONST UBYTE	D2W_PleaseReplaceToner[];
extern CONST UBYTE	D2W_PleaseCallService[];
extern CONST UBYTE	D2W_PaperSizeError[];

extern CONST UBYTE	D2W_CheckDrumLife[];
extern CONST UBYTE	D2W_ReplaceDrum[];
extern CONST UBYTE	D2W_CheckDrum[];
extern CONST UBYTE	D2W_CheckTonerLevel[];
extern CONST UBYTE	D2W_NoToner[];

/* スキャナ */
extern CONST UBYTE	D2W_CallForService[];
extern CONST UBYTE	D2W_CheckDocument[];
extern CONST UBYTE	D2W_MirrorCarrigeError[];

/* ジャムリカバー */
extern CONST UBYTE	D2W_DocumentJam[];
extern CONST UBYTE	D2W_InterruptDocScan[];
extern CONST UBYTE	D2W_NextScanEnterClear[];
extern CONST UBYTE	D2W_ResetPageNumber[];
extern CONST UBYTE	D2W_ResetDocumentSet[];
extern CONST UBYTE	D2W_PleasePressStartKey[];
extern CONST UBYTE	D2W_PleasePressEnterKey[];
extern CONST UBYTE	D2W_PleasePressCopyKey[];

/* 通信 */
extern CONST UBYTE	D2W_CommunicationError[];
extern CONST UBYTE	D2W_NoStoredDialInNumber[];

/* ハングアップ */
extern CONST UBYTE	D2W_HungUpPhone[];

/* 完了表示 */
extern CONST UBYTE	D2W_TransmitComplete[];
extern CONST UBYTE	D2W_ReceiveComplete[];
extern CONST UBYTE	D2W_PrintComplete[];
extern CONST UBYTE	D2W_StoreComplete[];
extern CONST UBYTE	D2W_SetComplete[];
extern CONST UBYTE	D2W_ClearComplete[];

/* リモート診断中の表示 */
extern CONST UBYTE	D2W_RemoteDiagMode[];

/* 操作エラー */
extern CONST UBYTE	D2W_InvalidNumber[];
extern CONST UBYTE	D2W_TooManyDigitsin[];
extern CONST UBYTE	D2W_PleaseInput1_99[];
extern CONST UBYTE	D2W_NoNumberStored[];
extern CONST UBYTE	D2W_PleaseInput0_32[];
extern CONST UBYTE	D2W_TooManyLocations[];
extern CONST UBYTE	D2W_InsertDocument[];
extern CONST UBYTE	D2W_FeederInUse[];
extern CONST UBYTE	D2W_ScannerInUse[];
extern CONST UBYTE	D2W_PollingInUse[];
extern CONST UBYTE	D2W_NoDocumentStored[];
extern CONST UBYTE	D2W_CommandFull[];
extern CONST UBYTE	D2W_NoCommand[];
extern CONST UBYTE	D2W_NoCommandDocument[];
extern CONST UBYTE	D2W_NoCommandResult[];
extern CONST UBYTE	D2W_SecureDocExist[];
extern CONST UBYTE	D2W_PrinterInUse[];
extern CONST UBYTE	D2W_InvalidIDCode[];
extern CONST UBYTE	D2W_InvalidProtectPasscode[];
extern CONST UBYTE	D2W_NoProtectPasscode[];
extern CONST UBYTE	D2W_InputRangeOver[];
extern CONST UBYTE	D2W_BatchDocFull[];
extern CONST UBYTE	D2W_LineBusy[];
extern CONST UBYTE	D2W_ProtectedDocStored[];
extern CONST UBYTE	D2W_NoProtectDocStored[];
extern CONST UBYTE	D2W_NoPinNumber[];
extern CONST UBYTE	D2W_NoDepartmentCode[];
extern CONST UBYTE	D2W_BatchDocStored[];
extern CONST UBYTE	D2W_ResetDocument[];
extern CONST UBYTE	D2W_PleaseCloseBookCover[];
extern CONST UBYTE	D2W_PleaseWaitAMinute[];
extern CONST UBYTE	D2W_NotStoredDocument[];
extern CONST UBYTE	D2W_BoxInUse[];
extern CONST UBYTE	D2W_TooManyDirectDial[];
extern CONST UBYTE	D2W_SettingSecureBox[];
extern CONST UBYTE	D2W_BookSizeNoSet[];
extern CONST UBYTE	D2W_NotCompleteStoredDoc[];
extern CONST UBYTE	D2W_NotCompleteCopy[];
extern CONST UBYTE	D2W_ScanPreparing[];
extern CONST UBYTE	D2W_CopyProtect[];
extern CONST UBYTE	D2W_NotScanDocSize[];
extern CONST UBYTE	D2W_ShortFigure[];
extern CONST UBYTE	D2W_AlreadyStored[];
extern CONST UBYTE	D2W_NotEntry[];
extern CONST UBYTE	D2W_NoScanCipherMode[];
extern CONST UBYTE	D2W_Ciphering[];
extern CONST UBYTE	D2W_Deciphering[];
extern CONST UBYTE	D2W_UseDefaultCipherKey[];
extern CONST UBYTE	D2W_UseProgramOneTouch[];
extern CONST UBYTE	D2W_PleaseCloseTopCover[];
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1999/01/07 */
//#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#endif
extern CONST UBYTE	D2W_DialNumberStoredError[];
extern CONST UBYTE	D2W_ProgramStoredError[];
extern CONST UBYTE	D2W_MailAddressStoredError[];
extern CONST UBYTE	D2W_MailGroupStoredError[];
extern CONST UBYTE	D2W_UserDataFullError[];
extern CONST UBYTE	D2W_NoRS232C_Error[];
extern CONST UBYTE	D2W_TooManyDirectAdrError[];
extern CONST UBYTE	D2W_NoUserDataError[];
extern CONST UBYTE	D2W_InvalidAddressError[];
extern CONST UBYTE	D2W_NoTCPIP_BoardError[];
extern CONST UBYTE	D2W_MemoryFullError[];
extern CONST UBYTE	D2W_AlreadyUsedError[];
extern CONST UBYTE	D2W_NoEntryData[];
extern CONST UBYTE	D2W_NoStoredAddress[];
extern CONST UBYTE	D2W_InvalidPassword[];
extern CONST UBYTE	D2W_ExecuteCommand[];
extern CONST UBYTE	D2W_NoDeviceError[];
#if (0)
//extern CONST UBYTE D2W_NoAccessPointTelNumber[];
#endif
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1999/01/07 */
//#endif
#endif
extern CONST UBYTE	D2W_SettingRelayBox[];		/* By H.Fujimura 1999/01/07 */
extern CONST UBYTE	D2W_TooManyRelayDirect[];	/* By H.Fujimura 1999/01/07 */

/*----------------------------------*
 *	通信中
 *----------------------------------*/
extern CONST UBYTE	D2W_Transmit[];
extern CONST UBYTE	D2W_Receive[];
extern CONST UBYTE	D2W_Called[];
extern CONST UBYTE	D2W_CallReservation[];
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
extern CONST UBYTE	D2W_CallReservation_S[];
#endif

/*----------------------------------*
 *	原稿サイズ・線密度
 *----------------------------------*/
extern CONST UBYTE	D2W_DocNormal[];
extern CONST UBYTE	D2W_DocFine[];
extern CONST UBYTE	D2W_DocSFine[];
extern CONST UBYTE	D2W_DocGray[];
#if (PRO_PITNEYBOWES == ENABLE) /* [ＰＢ用解像度表示対応] */
extern CONST UBYTE	D2W_DocHGray[];
#endif
extern CONST UBYTE	D2W_DocHFine[]; /*評価用に追加1996/06/19Eguchi*/
extern CONST UBYTE	D2W_DocEFine[]; /*評価用に追加1996/06/19Eguchi*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
extern CONST UBYTE	D2W_DocFine_S[];
extern CONST UBYTE	D2W_DocSFine_S[];
#endif

/*----------------------------------*
 *	次原稿・メモリ残量
 *----------------------------------*/
extern CONST UBYTE	D2W_NextDocument[];
extern CONST UBYTE	D2W_MemoryAreaShort[];
extern CONST UBYTE	D2W_MemoryAreaLong[];
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/07 */
extern CONST UBYTE	D2W_MemoryAreaLong2[];
extern CONST UBYTE	D2W_MemoryAreaShort2[];	/* ＬＣＤ表示変更 By O.Kimoto 1999/02/25 */
#endif
#if (PRO_NOT_AUTO_RX_DISP == ENABLE)	/* by K.Watanabe 1998/06/08 */
extern CONST UBYTE	D2W_MemoryFull[];
extern CONST UBYTE	D2W_NotAutoReceive[];
#endif

/*----------------------------------*
 *	月
 *----------------------------------*/
extern CONST UBYTE	D2W_January[];
extern CONST UBYTE	D2W_February[];
extern CONST UBYTE	D2W_March[];
extern CONST UBYTE	D2W_April[];
extern CONST UBYTE	D2W_May[];
extern CONST UBYTE	D2W_June[];
extern CONST UBYTE	D2W_July[];
extern CONST UBYTE	D2W_August[];
extern CONST UBYTE	D2W_September[];
extern CONST UBYTE	D2W_October[];
extern CONST UBYTE	D2W_November[];
extern CONST UBYTE	D2W_December[];

/*----------------------------------*
 *	予約表示
 *----------------------------------*/
extern CONST UBYTE	D2W_Reserving[];
extern CONST UBYTE	D2W_AutoRedial[];

/*----------------------------------*
 *	原稿セット時
 *----------------------------------*/
extern CONST UBYTE	D2W_TransmitOrCopyReady[];
extern CONST UBYTE	D2W_TransmitReady[];

#if (PRO_PC_PRINT == ENABLE)
/*----------------------------------*
 *	ＰＣプリント
 *----------------------------------*/
extern CONST UBYTE	D2W_PC_Print[];
extern CONST UBYTE	D2W_PC_Receiving[];
extern CONST UBYTE	D2W_PC_MemoryOverFlow[];
#endif

/*----------------------------------*
 *	プリント中
 *----------------------------------*/
extern CONST UBYTE	D2W_Printing[];

/*----------------------------------*
 *	ウォームアップ
 *----------------------------------*/
extern CONST UBYTE	D2W_Wait[];

/*----------------------------------*
 *	イメージプリント
 *----------------------------------*/
extern CONST UBYTE	D2W_PollingDocument[];
extern CONST UBYTE	D2W_SecureMailDocument[];
extern CONST UBYTE	D2W_MemoryRxDocument[];
extern CONST UBYTE	D2W_CommandDocument[];
extern CONST UBYTE	D2W_BatchTxDocument[];
/** メモリ受信原稿、予約原稿プリント時の表示も考える */

/*----------------------------------*
 *	リストプリント
 *----------------------------------*/
extern CONST UBYTE	D2W_PrintJournal[];
#if (PRO_JOURNAL_VER_UP == ENABLE)	/* by K.Watanabe 2004/10/28 */
extern CONST UBYTE	D2W_PrintJournalTx[];
extern CONST UBYTE	D2W_PrintJournalRx[];
extern CONST UBYTE	D2W_PrintJournalTxRx[];
#endif
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
extern CONST UBYTE	D2W_PrintAllJournal[];
extern CONST UBYTE	D2W_PrintDailyReport[];
#endif
extern CONST UBYTE	D2W_TCR[];
extern CONST UBYTE	D2W_PrintSpeedDial[];
extern CONST UBYTE	D2W_PrintOneTouch[];
extern CONST UBYTE	D2W_PrintProgramOneTouch[];
extern CONST UBYTE	D2W_GroupList[];
extern CONST UBYTE	D2W_SF_ProgramListPrint[];
extern CONST UBYTE	D2W_SetPrintSettings[];
extern CONST UBYTE	D2W_PrintCommands[];
extern CONST UBYTE	D2W_PrintSecureMailList[];
extern CONST UBYTE	D2W_MessageList[];
extern CONST UBYTE	D2W_PrintSecureMail[];
extern CONST UBYTE	D2W_SF_T30MonitorPrint[];
extern CONST UBYTE	D2W_SF_FactoryFunctionList[];
extern CONST UBYTE	D2W_SF_MemorySwitchMode[];
extern CONST UBYTE	D2W_CheckMessage[];
extern CONST UBYTE	D2W_SF_OnLineMonitor[];
extern CONST UBYTE	D2W_SF_OrderForm[];

/*----------------------------------*
 *	パスコード
 *----------------------------------*/
extern CONST UBYTE	D2W_InputPasscode[];
extern CONST UBYTE	D2W_EnterProtectPasscode[];
extern CONST UBYTE	D2W_OldProtectPasscode[];
extern CONST UBYTE	D2W_NewProtectPasscode[];
extern CONST UBYTE	D2W_EnterIDCode[];
#if (PRO_F_CODE == ENABLE)
extern CONST UBYTE	D2W_EnterFcodePasscode[];
#endif
#if (PRO_CIPHER == ENABLE)
extern CONST UBYTE	D2W_CipherPassCode[];
extern CONST UBYTE	D2W_OldCipherPassCode[];
extern CONST UBYTE	D2W_NewCipherPassCode[];
#endif

/*----------------------------------*
 *	入力モード
 *----------------------------------*/
#if defined(JPN)
extern CONST UBYTE	D2W_Kana[];
 #if (PRO_JIS_CODE == ENABLE)
extern CONST UBYTE	D2W_KanjiCode[];
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
extern CONST UBYTE	D2W_Alphameric[];
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
extern CONST UBYTE	D2W_Upper[];
extern CONST UBYTE	D2W_Lower[];
extern CONST UBYTE	D2W_Symbol[];
extern CONST UBYTE	D2W_Code[];
extern CONST UBYTE	D2W_ModeNone[];

/*----------------------------------*
 *	電話帳
 *----------------------------------*/
extern CONST UBYTE	D2W_TelephoneBookMode[];

/*----------------------------------*
 *	電話
 *----------------------------------*/
extern CONST UBYTE	D2W_OnHold[];
extern CONST UBYTE	D2W_TelephoneMode[];
extern CONST UBYTE	D2W_ChangeVolume[];

/*----------------------------------*
 *	メモリーオーバーオペレーション
 *----------------------------------*/
extern CONST UBYTE	D2W_MemoryOverFlow[];
extern CONST UBYTE	D2W_MemoryOverStartClear[];
extern CONST UBYTE	D2W_MemoryOverEnterClear[];
extern CONST UBYTE	D2W_MemoryOverCopyClear[];

/*----------------------------------*
 *	ファンクション関係
 *----------------------------------*/
/* 機能選択状態 */
extern CONST UBYTE	D2W_OneTouchDialMode[];
extern CONST UBYTE	D2W_SpeedDialMode[];
extern CONST UBYTE	D2W_ProgramOneTouchMode[];
extern CONST UBYTE	D2W_PollingMode[];
extern CONST UBYTE	D2W_SecureMailMode[];
extern CONST UBYTE	D2W_DelayedCommandsMode[];
extern CONST UBYTE	D2W_SetReportMode[];
extern CONST UBYTE	D2W_PrintGroupMode[];
extern CONST UBYTE	D2W_UserInstallMode[];
extern CONST UBYTE	D2W_UserSettingsMode[];
extern CONST UBYTE	D2W_MessageMode[];
extern CONST UBYTE	D2W_SetNumberOfPagesMode[];
extern CONST UBYTE	D2W_SetDepartmentMode[];
extern CONST UBYTE	D2W_SetBatchTxMode[];
extern CONST UBYTE	D2W_SecurityReceiveMode[];
extern CONST UBYTE	D2W_FcodeBoxMode[];
extern CONST UBYTE	D2W_ResetPrinterBoardMode[];
extern CONST UBYTE	D2W_SetClass1Mode[];
extern CONST UBYTE	D2W_SetCipherMode[];
extern CONST UBYTE	D2W_PrintDecipherDocMode[];

extern CONST UBYTE	D2W_EnterOneTouchMode[];
extern CONST UBYTE	D2W_EraseOneTouchMode[];
extern CONST UBYTE	D2W_PrintOneTouchMode[];

extern CONST UBYTE	D2W_EnterSpeedDialMode[];
extern CONST UBYTE	D2W_EraseSpeedDialMode[];
extern CONST UBYTE	D2W_PrintSpeedDialMode[];

extern CONST UBYTE	D2W_EnterProgramOneTouchMode[];
extern CONST UBYTE	D2W_EraseProgramOneTouchMode[];
extern CONST UBYTE	D2W_PrintProgramOneTouchMode[];

extern CONST UBYTE	D2W_StorePollingDocumentMode[];
extern CONST UBYTE	D2W_ErasePollingDocumentMode[];
extern CONST UBYTE	D2W_PrintPollingDocumentMode[];

extern CONST UBYTE	D2W_SetSecureMailBoxMode[];
extern CONST UBYTE	D2W_PrintSecureMailListMode[];
extern CONST UBYTE	D2W_PrintSecureMailMode[];
extern CONST UBYTE	D2W_SecureMailHoldTimeMode[];

extern CONST UBYTE	D2W_PrintCommandsMode[];
extern CONST UBYTE	D2W_PrintStoredDocumentMode[];

extern CONST UBYTE	D2W_JournalOnOffMode[];
extern CONST UBYTE	D2W_PrintJournalMode[];
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/15 */
extern CONST UBYTE	D2W_PrintDailyReportMode[];
#endif
extern CONST UBYTE	D2W_SettingCommunicationResult[];

extern CONST UBYTE	D2W_SettingScanParameters[];
extern CONST UBYTE	D2W_SettingPrintParameters[];
extern CONST UBYTE	D2W_SettingCopyParameters[];
extern CONST UBYTE	D2W_SettingPaperSize[];
extern CONST UBYTE	D2W_SettingCopyProtect[];
extern CONST UBYTE	D2W_SettingDialingPause[];
extern CONST UBYTE	D2W_SettingNumberOfRings[];
extern CONST UBYTE	D2W_SettingRedial[];
extern CONST UBYTE	D2W_SettingECMMode[];
extern CONST UBYTE	D2W_SettingPasscode[];
extern CONST UBYTE	D2W_SettingClosedNetwork[];
extern CONST UBYTE	D2W_SettingSecurityTransmission[];
extern CONST UBYTE	D2W_SettingBlockJunkMail[];
extern CONST UBYTE	D2W_SettingRemoteDiagnostic[];
extern CONST UBYTE	D2W_SettingMemoryTransmission[];
extern CONST UBYTE	D2W_SettingSilentOperation[];
extern CONST UBYTE	D2W_SettingDialIn[];
extern CONST UBYTE	D2W_SettingProtectPasscode[];
extern CONST UBYTE	D2W_SettingOperationProtect[];
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/16 */
extern CONST UBYTE	D2W_SettingRemoteRxParameters[];
#endif		/* End of (defined (KEISATSU)) */
extern CONST UBYTE	D2W_SettingPINAccessMode[];
extern CONST UBYTE	D2W_SettingRingMasta[];
extern CONST UBYTE	D2W_SettingStamp[];
extern CONST UBYTE	D2W_SettingResetDrumLife[];
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */
extern CONST UBYTE	D2W_SettingRxAlarm[];
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/22 */
extern CONST UBYTE	D2W_SettingMercuryMode[];
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
extern CONST UBYTE	D2W_SettingHoldMelody[];
#endif
#if (PRO_REMOTE_RX == ENABLE)
extern CONST UBYTE	D2W_SettingRemoteReceive[];
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
extern CONST UBYTE	D2W_SettingOnHookReceive[];
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
extern CONST UBYTE	D2W_SettingPrintSettings[];
#endif

extern CONST UBYTE	D2W_SetMessageOnOff[];
extern CONST UBYTE	D2W_SetMessage[];
extern CONST UBYTE	D2W_PrintMessageList[];

extern CONST UBYTE	D2W_SettingDepartmentProtect[];
extern CONST UBYTE	D2W_SettingDepartmentCode[];
extern CONST UBYTE	D2W_SettingDepartmentOnOff[];
#if (PRO_DEPART_NEW_LIST == ENABLE)
extern CONST UBYTE	D2W_PrintDepartTimeList[];  /* by thonda 1997/12/03 */
extern CONST UBYTE	D2W_EraseDepartTimeList[];  /* by thonda 1997/12/03 */
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/10/15 */
extern CONST UBYTE	D2W_ManualCutterMode[];
#endif
extern CONST UBYTE	D2W_SettingBatchBox[];
extern CONST UBYTE	D2W_PrintBatchBoxList[];
extern CONST UBYTE	D2W_PrintBatchDocList[];
extern CONST UBYTE	D2W_PrintBatchDoc[];
extern CONST UBYTE	D2W_EraseBatchBox[];
extern CONST UBYTE	D2W_EraseBatchDoc[];

extern CONST UBYTE	D2W_SettingSecurityRx[];
extern CONST UBYTE	D2W_PrintMemoryReceiveDoc[];

#if (PRO_F_CODE == ENABLE)
extern CONST UBYTE	D2W_EnterFcodeBoxMode[];
extern CONST UBYTE	D2W_PrintFcodeBoxListMode[];
extern CONST UBYTE	D2W_PrintFcodeStoreDocListMode[];
extern CONST UBYTE	D2W_PrintFcodeStoreDocMode[];
extern CONST UBYTE	D2W_EraseFcodeBoxMode[];
extern CONST UBYTE	D2W_EraseFcodeDocMode[];
extern CONST UBYTE	D2W_StoreFcodeDocMode[];
#endif

#if (PRO_CIPHER == ENABLE)
extern CONST UBYTE	D2W_EnterCipherKeyBookMode[];
extern CONST UBYTE	D2W_PrintCipherKeyBookListMode[];
extern CONST UBYTE	D2W_PrintCipherKeyMode[];
extern CONST UBYTE	D2W_EraseCipherKeyBookMode[];
extern CONST UBYTE	D2W_EraseCipherRxDocMode[];
extern CONST UBYTE	D2W_EnterDefaultCipherKeyMode[];
extern CONST UBYTE	D2W_EnterCipherServiceLabelMode[];
extern CONST UBYTE	D2W_EnterCipherPassCodeMode[];
#endif

extern CONST UBYTE	D2W_SettingRS232CPCFaxScan[];
extern CONST UBYTE	D2W_SettingRS232CParameter[];
extern CONST UBYTE	D2W_SettingRS232CPCFaxInitial[];

/*----------------------------------*
 *	ワンタッチ登録
 *----------------------------------*/
extern CONST UBYTE	D2W_SelectOnetouch[];

extern CONST UBYTE	D2W_EraseOnetouch[];
extern CONST UBYTE	D2W_EraseSpeedDial[];
extern CONST UBYTE	D2W_EraseProgramOnetouch[];

/*----------------------------------*
 *	短縮登録
 *----------------------------------*/
extern CONST UBYTE	D2W_SelectOptionalSpeedNumber[];

/* ワンタッチ・短縮ダイアルデータ入力中 */
/* このワーディングのサイズ及び登録順はかえてはいけない */
extern CONST UBYTE	D2W_FaxNumber[];
extern CONST UBYTE	D2W_AltNumber[];
extern CONST UBYTE	D2W_RemoteName[];
extern CONST UBYTE	D2W_GroupNumber[];
extern CONST UBYTE	D2W_PinNumber[];
extern CONST UBYTE	D2W_Attribute1[];
extern CONST UBYTE	D2W_Attribute2[];
extern CONST UBYTE	D2W_Attribute3[];
extern CONST UBYTE	D2W_Attribute4[];

extern CONST UBYTE	D2W_SetPIN_Number[];

/*----------------------------------*
 *	プログラムワンタッチ
 *----------------------------------*/
extern CONST UBYTE	D2W_SelectProgramOnetouch[];

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	拡張版プログラムワンタッチ
 *----------------------------------*/
extern CONST UBYTE	D2W_ProgramItem[][21];
extern CONST UBYTE	D2W_ProgramList[][21];
extern CONST UBYTE	D2W_ProgramStore[][21];
extern CONST UBYTE	D2W_ProgramTxModeSW[][21];
extern CONST UBYTE	D2W_ProgramContrastSW[][21];
extern CONST UBYTE	D2W_ProgramStampSW[][21];
extern CONST UBYTE	D2W_ProgramMemoryTxSW[][21];
extern CONST UBYTE	D2W_ProgramConfirmSW[][21];
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
extern CONST UBYTE	D2W_ProgramTxModeSW_S[][21];
extern CONST UBYTE	D2W_ProgramContrastSW_S[][21];
#endif
#endif

/*----------------------------------*
 *	ポーリング
 *----------------------------------*/
extern CONST UBYTE	D2W_StorePollingDocument[];
extern CONST UBYTE	D2W_ErasePollingDocument[];
extern CONST UBYTE	D2W_PrintPollingDocument[];

/*----------------------------------*
 *	親展
 *----------------------------------*/
extern CONST UBYTE	D2W_SetSecureMailBox[];
extern CONST UBYTE	D2W_SecureMailHoldTime[];
extern CONST UBYTE	D2W_HoldTime1_31[];
extern CONST UBYTE	D2W_SecureMailName[];

/*----------------------------------*
 *	通信予約
 *----------------------------------*/
extern CONST UBYTE	D2W_PrintStoredDocument[];
extern CONST UBYTE	D2W_InputCommandNumber[];
#if (PRO_CIPHER == ENABLE)
extern CONST UBYTE	D2W_SelectDecipher[];
#endif

/*----------------------------------*
 *	ジャーナル
 *----------------------------------*/
extern CONST UBYTE	D2W_JournalOnOff[];
extern CONST UBYTE	D2W_SelectAutoPrint[];
extern CONST UBYTE	D2W_TCRSelected[];
extern CONST UBYTE	D2W_RCRSelected[];
extern CONST UBYTE	D2W_SetCommunicationResult[];

/*----------------------------------*
 *	設置モード
 *----------------------------------*/
/* カレンダー入力 */
extern CONST UBYTE	D2W_InputTime[];

/* 夏時間切り替え */
#if defined(USA)
extern CONST UBYTE	D2W_DayLightSaving[];
#endif

/* ＴＴＩ */
extern CONST UBYTE	D2W_EnterYourFaxNumber[];
extern CONST UBYTE	D2W_EnterYourName[];
extern CONST UBYTE	D2W_EnterYourKanaName[];

/* 回線種別 */
extern CONST UBYTE	D2W_SelectPhoneType[];
extern CONST UBYTE	D2W_10pps[];
extern CONST UBYTE	D2W_20pps[];
extern CONST UBYTE	D2W_Tone[];
extern CONST UBYTE	D2W_Pulse10[];
extern CONST UBYTE	D2W_Pulse20[];
extern CONST UBYTE	D2W_Push[];

#if defined (KEISATSU) /* 警察FAX Added by SMuratec K.W.Q 2005/06/07 */
extern CONST UBYTE	D2W_SelectKeidenPhoneType[];
extern CONST UBYTE	D2W_SelectKanyuPhoneType[];
#endif		/* End of (defined (KEISATSU)) */

extern CONST UBYTE	D2W_PrintSettingList[];

#if (PRO_MULTI_LINE == ENABLE) || (PRO_MULTI_TTI == ENABLE)	/* 多回線仕様追加 1997/09/03 Y.Matsukuma */
/* マルチ回線ユーザー設定 */
extern CONST UBYTE	D2W_MultiYourFaxNumber[];
extern CONST UBYTE	D2W_MultiYourName[];
extern CONST UBYTE	D2W_MultiYourKanaName[];
extern CONST UBYTE	D2W_MultiPhoneType[];
extern CONST UBYTE	D2W_MultiTxRx[];
extern CONST UBYTE	D2W_SelectTxRx[];
extern CONST UBYTE	D2W_SelectTx[];
extern CONST UBYTE	D2W_SelectRx[];
extern CONST UBYTE	D2W_MultiLineType[];
extern CONST UBYTE	D2W_SelectLinePstn[];
extern CONST UBYTE	D2W_SelectLinePbx[];
extern CONST UBYTE	D2W_SetAccessNumber[];
#endif

/* Ｆｕｎｃｔｉｏｎ */
extern CONST UBYTE	D2W_On1[];
extern CONST UBYTE	D2W_Off1[];
extern CONST UBYTE	D2W_Off2[];
extern CONST UBYTE	D2W_On2[];
extern CONST UBYTE	D2W_Off3[];
extern CONST UBYTE	D2W_On3[];
extern CONST UBYTE	D2W_On4[];
extern CONST UBYTE	D2W_Off4[];
extern CONST UBYTE	D2W_ModeOff[];
extern CONST UBYTE	D2W_Mode1[];
extern CONST UBYTE	D2W_Mode2[];
extern CONST UBYTE	D2W_Mode3[];

/*----------------------------------*
 *	ユーザー設定
 *----------------------------------*/
/* 読み取りパラメータ */
/* 原稿読みとり幅 */
extern CONST UBYTE	D2W_SelectScanWidth[];
extern CONST UBYTE	D2W_ScanA4[];
extern CONST UBYTE	D2W_ScanB4[];
extern CONST UBYTE	D2W_ScanA3[];

/* 優先モード */
extern CONST UBYTE	D2W_SelectPrimaryMode[];
extern CONST UBYTE	D2W_PrimaryModeNormal[];
extern CONST UBYTE	D2W_PrimaryModeFine[];
extern CONST UBYTE	D2W_PrimaryModeSFine[];
extern CONST UBYTE	D2W_PrimaryModeGray[];
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
extern CONST UBYTE	D2W_PrimaryModeFine_S[];
extern CONST UBYTE	D2W_PrimaryModeSFine_S[];
#endif

/* 優先原稿濃度 */
extern CONST UBYTE	D2W_SelectPrimaryContrast[];
extern CONST UBYTE	D2W_PrimaryContrastLight[];
extern CONST UBYTE	D2W_PrimaryContrastLittleLight[];
extern CONST UBYTE	D2W_PrimaryContrastNormal[];
extern CONST UBYTE	D2W_PrimaryContrastLittleDark[];
extern CONST UBYTE	D2W_PrimaryContrastDark[];
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
extern CONST UBYTE	D2W_SelectPrimaryContrast_S[];
extern CONST UBYTE	D2W_PrimaryContrastLight_S[];
extern CONST UBYTE	D2W_PrimaryContrastDark_S[];
#endif

extern CONST UBYTE	D2W_SetScanParameters[];

/* プリントパラメータ */
extern CONST UBYTE	D2W_SelectReceiveReduction[];
extern CONST UBYTE	D2W_AutoReduction[];
extern CONST UBYTE	D2W_100[];
extern CONST UBYTE	D2W_97[];
extern CONST UBYTE	D2W_91[];
extern CONST UBYTE	D2W_81[];
extern CONST UBYTE	D2W_75[];
extern CONST UBYTE	D2W_InputThresholdValue0_85[];
extern CONST UBYTE	D2W_SelectPageCompound[];
extern CONST UBYTE	D2W_SetPrintParameters[];
#if (PRO_ROTATE == ENABLE)
extern CONST UBYTE	D2W_SetRotateMargin[];
#endif

/* コピーパラメータ */
extern CONST UBYTE	D2W_SelectSortingCopy[];
extern CONST UBYTE	D2W_SelectCopyReduction[];
extern CONST UBYTE	D2W_SetCopyParameters[];

/* 記録紙サイズ */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
extern CONST UBYTE	D2W_EnterPaperSize[];
extern CONST UBYTE	D2W_PaperSizeNone[];
extern CONST UBYTE	D2W_PaperSizeA4[];
extern CONST UBYTE	D2W_PaperSizeB4[];
extern CONST UBYTE	D2W_PaperSizeLetter[];
extern CONST UBYTE	D2W_PaperSizeLegal[];
extern CONST UBYTE	D2W_PaperSizeF4[];
extern CONST UBYTE	D2W_SetPaperSize[];

 #if (PRO_PC_PRINT == ENABLE)	/* ＰＣプリント */
extern CONST UBYTE	D2W_SelectPaperSizeNone[];
extern CONST UBYTE	D2W_SelectPaperSizeA5[];
extern CONST UBYTE	D2W_SelectPaperSizeLetter[];
extern CONST UBYTE	D2W_SelectPaperSizeA4[];
extern CONST UBYTE	D2W_SelectPaperSizeLegal[];
extern CONST UBYTE	D2W_SelectPaperSizeB5R[];
extern CONST UBYTE	D2W_SelectPaperSizeB4[];
extern CONST UBYTE	D2W_SelectPaperSizeA3[];
extern CONST UBYTE	D2W_SelectPaperSizeA4R[];
extern CONST UBYTE	D2W_SelectPaperSizeLetterR[];
extern CONST UBYTE	D2W_SelectPaperSizeF4[];
extern CONST UBYTE	D2W_SelectPaperSizeA5R[];
extern CONST UBYTE	D2W_SelectPaperSizePostcard[];
extern CONST UBYTE	D2W_SelectPaperSizeLD[];
extern CONST UBYTE	D2W_SelectPaperSizeGLetterR[];
extern CONST UBYTE	D2W_SelectPaperSizeExecutiveR[];
extern CONST UBYTE	D2W_SelectPaperSizeInvoiceR[];
extern CONST UBYTE	D2W_SelectPaperSizeGLegal[];
extern CONST UBYTE	D2W_SelectPaperSizeGLetter[];
extern CONST UBYTE	D2W_SelectPaperSizeCard[];
extern CONST UBYTE	D2W_SelectPaperSizeExecutive[];
extern CONST UBYTE	D2W_SelectPaperSizeB5[];
extern CONST UBYTE	D2W_SelectPaperSizeC5[];
extern CONST UBYTE	D2W_SelectPaperSizeHalfLetter[];
extern CONST UBYTE	D2W_SelectPaperSizeInvoice[];
extern CONST UBYTE	D2W_SelectPaperSizeB6[];
extern CONST UBYTE	D2W_SelectPaperSizeDL[];
extern CONST UBYTE	D2W_SelectPaperSizeCM10[];
extern CONST UBYTE	D2W_SelectPaperSizeA6[];
extern CONST UBYTE	D2W_SelectPaperSizeMonarch[];
extern CONST UBYTE	D2W_SelectPaperSize35[];
extern CONST UBYTE	D2W_SelectPaperSizeUser[];
 #endif
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */

/* コピー禁止 */
extern CONST UBYTE	D2W_SelectCopyProtect[];

/* ポーズ */
extern CONST UBYTE	D2W_SetDialingPause[];
extern CONST UBYTE	D2W_PauseTime[];

/* べル回数 */
extern CONST UBYTE	D2W_SetNumberOfRings[];
extern CONST UBYTE	D2W_NumberOfRings[];

/* リダイアル */
extern CONST UBYTE	D2W_RedialCount[];
extern CONST UBYTE	D2W_SetNumberOfRedials[];
extern CONST UBYTE	D2W_RedialInterval[];
extern CONST UBYTE	D2W_SetRedialInterval[];
extern CONST UBYTE	D2W_SetRedial[];

/* ECM */
extern CONST UBYTE	D2W_SelectECMMode[];
extern CONST UBYTE	D2W_SetECMMode[];

/* パスコード */
extern CONST UBYTE	D2W_SetPasscode[];

/* 閉域通信設定 */
extern CONST UBYTE	D2W_SelectClosedNetwork[];
extern CONST UBYTE	D2W_SetClosedNetwork[];

/* パスワード送信 */
extern CONST UBYTE	D2W_SelectSecurityTransmission[];
extern CONST UBYTE	D2W_SetSecurityTransmission[];

/* ダイレクトメール防止 */
extern CONST UBYTE	D2W_SelectBlockJunkMail[];
extern CONST UBYTE	D2W_SetBlockJunkMailDial[];
extern CONST UBYTE	D2W_PrintBlockJunkMailDialList[];
extern CONST UBYTE	D2W_SetBlockJunkMail[];
extern CONST UBYTE	D2W_BlockJunkMailSelectNumber[];
extern CONST UBYTE	D2W_SetSameNumber[];

/* リモート診断 */
extern CONST UBYTE	D2W_SelectRemoteDiagnostic[];
extern CONST UBYTE	D2W_SetRemoteDiagnostic[];

/* メモリー送信 */
extern CONST UBYTE	D2W_SelectMemoryTransmission[];
extern CONST UBYTE	D2W_SetMemoryTransmission[];

/* サイレントオペレーション */
extern CONST UBYTE	D2W_SelectSilentOperation[];
extern CONST UBYTE	D2W_SetSilentOperation[];

/* プロテクトパスコード */
extern CONST UBYTE	D2W_SetProtectPasscode[];
extern CONST UBYTE	D2W_ProtectPasscode[];

/* オペレーションプロテクト */
extern CONST UBYTE	D2W_OperationProtectOnOff[];
extern CONST UBYTE	D2W_SetOperationProtect[];

/* ＰＩＮアクセスモードセット */
extern CONST UBYTE	D2W_PINAccessMode[];
extern CONST UBYTE	D2W_SetPINAccessMode[];

/* リングマスター */
#if (PRO_RING_MASTER == ENABLE)	/* by K.Watanabe 1998/08/18 */
extern CONST UBYTE	D2W_SelectRingMaster[];
extern CONST UBYTE	D2W_SelectRingPattern[];
extern CONST UBYTE	D2W_RingPatternDummy[];
extern CONST UBYTE	D2W_RingPattern_A[];
extern CONST UBYTE	D2W_RingPattern_B[];
extern CONST UBYTE	D2W_RingPattern_C[];
extern CONST UBYTE	D2W_RingPattern_D[];
extern CONST UBYTE	D2W_RingPattern_E[];
extern CONST UBYTE	D2W_RingPattern_F[];
extern CONST UBYTE	D2W_RingPattern_G[];
extern CONST UBYTE	D2W_RingPattern_H[];
extern CONST UBYTE	D2W_SetRingMaster[];
#endif

/* 済みスタンプ */
extern CONST UBYTE	D2W_StampOnOff[];
extern CONST UBYTE	D2W_SetStamp[];

/* ドラム寿命リセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* by K.Watanabe 1998/08/18 */
extern CONST UBYTE	D2W_ResetDrumLife[];
#endif

/* 受信アラームセット */
extern CONST UBYTE	D2W_RxAlarm[];
extern CONST UBYTE	D2W_SetRxAlarm[];

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
/*----------------------------------*
 *	マーキュリー
 *----------------------------------*/
/* マーキュリー番号  */
extern CONST UBYTE	D2W_MercuryNumberSet[];
/* マーキュリーポーズ */
extern CONST UBYTE	D2W_MercuryPauseSet[];
extern CONST UBYTE	D2W_SetMercury[];
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* 保留メロディーセット */
extern CONST UBYTE	D2W_SelectHoldMelody[];
#endif

#if (PRO_REMOTE_RX == ENABLE)
extern CONST UBYTE	D2W_SelectRemoteReceive[];
#endif

#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
extern CONST UBYTE	D2W_SelectOnHookReceive[];
#endif

/* ダイアルイン */
#if (PRO_DIALIN == ENABLE)
extern CONST UBYTE	D2W_SetDialIn[];
extern CONST UBYTE	D2W_DialInFax[];
extern CONST UBYTE	D2W_DialInTel1[];
extern CONST UBYTE	D2W_DialInTel2[];
extern CONST UBYTE	D2W_DialInRings[];
extern CONST UBYTE	D2W_DialInRings10_60[];
#endif

/*----------------------------------*
 *	カバーページ
 *----------------------------------*/
extern CONST UBYTE	D2W_MessageOnOff[];
extern CONST UBYTE	D2W_MessageTx[];
extern CONST UBYTE	D2W_SetCoverPageMessage[];
extern CONST UBYTE	D2W_MessageSet[];

/*----------------------------------*
 *	枚数設定
 *----------------------------------*/
extern CONST UBYTE	D2W_InputPageCount[];
extern CONST UBYTE	D2W_PageCount1_30[];

/*----------------------------------*
 *	部門管理
 *----------------------------------*/
/* 部門管理プロテクトセット */
extern CONST UBYTE	D2W_DepartmentProtect[];
extern CONST UBYTE	D2W_SetDepartmentProtect[];

/* 部門コードセット */
extern CONST UBYTE	D2W_DepartmentSelectNumber[];

/* 部門管理セット */
extern CONST UBYTE	D2W_DepartmentOnOff[];
extern CONST UBYTE	D2W_SetDepartmentOnOff[];

#if (PRO_DEPART_NEW_LIST == ENABLE)		/* 追記 By S.Fukui Jan.7,1998 */
/* 簡易部門毎時間管理リスト関連 */
extern CONST UBYTE	D2W_EraseDepartTimeListMode[];
extern CONST UBYTE  D2W_EraseDepartCode[];
extern CONST UBYTE  D2W_DepartCodeFull[];
#endif

/*----------------------------------*
 *	一括送信
 *----------------------------------*/
extern CONST UBYTE	D2W_SelectBatchBoxNumber[];
extern CONST UBYTE	D2W_TranssmissionTime[];
extern CONST UBYTE	D2W_EraseBatchBoxMode[];
extern CONST UBYTE	D2W_EraseBatchDocumentMode[];

extern CONST UBYTE	D2W_PrintBatchBoxMode[];
extern CONST UBYTE	D2W_PrintBatchDocListMode[];
extern CONST UBYTE	D2W_PrintBatchDocMode[];
extern CONST UBYTE	D2W_BatchBoxNumber[];
extern CONST UBYTE	D2W_BatchFileNumber[];

/*----------------------------------*
 *	セキュリティ受信
 *----------------------------------*/
/* セキュリティ受信セット */
extern CONST UBYTE	D2W_SecurityReceive[];
extern CONST UBYTE	D2W_SetSecurityReceive[];

/* メモリ受信原稿プリント */
extern CONST UBYTE	D2W_PrintMemoryReceiveDocMode[];

/*----------------------------------*
 *	Ｆコード
 *----------------------------------*/
#if (PRO_F_CODE == ENABLE)
extern CONST UBYTE	D2W_SelectFcodeBoxNumber[];
extern CONST UBYTE	D2W_EnterFcodeBoxName[];
extern CONST UBYTE	D2W_EnterFcodeSubAddress[];
extern CONST UBYTE	D2W_EnterFcodePassword[];
extern CONST UBYTE	D2W_SelectFcodeBoxKind[];
extern CONST UBYTE	D2W_FcodeBulletinBoardBox[];
extern CONST UBYTE	D2W_FcodeConfidentialBox[];
 #if (PRO_FCODE_RELAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
extern CONST UBYTE	D2W_FcodeRelayBox[];
 #endif
extern CONST UBYTE	D2W_SelectFcodeRxProhibition[];
extern CONST UBYTE	D2W_SelectFcodeRxDocPrint[];
extern CONST UBYTE	D2W_SelectFcodeRxDocUpperWrite[];
extern CONST UBYTE	D2W_SelectFcodeTxDocClear[];
extern CONST UBYTE	D2W_FcodeDocumentHoldTime[];
extern CONST UBYTE	D2W_HoldTime0_31[];
extern CONST UBYTE	D2W_SelectFcodeStoreDocAdd[];
extern CONST UBYTE	D2W_StoreFcodeDocument[];
 #if (PRO_FCODE_RELAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
extern CONST UBYTE	D2W_InputRelayNumber[];
extern CONST UBYTE	D2W_SetRelayTTI[][21];
 #endif
#endif
extern CONST UBYTE	D2W_SameNumber[];

/*----------------------------------*
 *	ＰＣプリントボード初期化
 *----------------------------------*/
#if (PRO_PC_PRINT == ENABLE)
extern CONST UBYTE	D2W_BoardReset[];
#endif

/*----------------------------------*
 *	暗号化
 *----------------------------------*/
#if (PRO_CIPHER == ENABLE)
extern CONST UBYTE	D2W_EnterCipherKeyName[];
extern CONST UBYTE	D2W_EnterCipherKey[];
extern CONST UBYTE	D2W_EnterCipherKeyClue[];
extern CONST UBYTE	D2W_InputCipherRxDocNumber[];
extern CONST UBYTE	D2W_InputCipherExtensionKey[];
extern CONST UBYTE	D2W_SelectCipherDocErrRemoval[];
extern CONST UBYTE	D2W_SelectCipherKeySetKind[];
extern CONST UBYTE	D2W_CipherKeySetDefault[];
extern CONST UBYTE	D2W_CipherKeySetKeyBook[];
extern CONST UBYTE	D2W_CipherKeySetDirect[];
extern CONST UBYTE	D2W_InputCipherDefaultKeyNo[];
extern CONST UBYTE	D2W_InputServiceLabelPosition[];
extern CONST UBYTE	D2W_CipherSelectNumber[];
extern CONST UBYTE	D2W_CipherExecute[];
extern CONST UBYTE	D2W_DecipherExecute[];
extern CONST UBYTE	D2W_CipherExecuteError[];
extern CONST UBYTE	D2W_DecipherExecuteError[];
extern CONST UBYTE	D2W_DecipherKeyError[];
extern CONST UBYTE	D2W_ConfirmDecipherContinue[];
extern CONST UBYTE	D2W_DecipherDocument[];
extern CONST UBYTE	D2W_StopCipherExecute[];
extern CONST UBYTE	D2W_StopDecipherExecute[];
#endif
extern CONST UBYTE	D2W_InputPrintPageNumber[];
extern CONST UBYTE	D2W_ProgressRate[];

/*----------------------------------*
 *	クラス１
 *----------------------------------*/
extern CONST UBYTE	D2W_SetRS232CParameter[];
extern CONST UBYTE	D2W_SetRS232CPCFaxInitial[];

/* ＲＳ２３２Ｃボーレート */
extern CONST UBYTE	D2W_SelectRS232CBaudRate[];
extern CONST UBYTE	D2W_RS232CVariable[];
extern CONST UBYTE	D2W_RS232C600bps[];
extern CONST UBYTE	D2W_RS232C1200bps[];
extern CONST UBYTE	D2W_RS232C2400bps[];
extern CONST UBYTE	D2W_RS232C4800bps[];
extern CONST UBYTE	D2W_RS232C9600bps[];
extern CONST UBYTE	D2W_RS232C19200bps[];

/* ＲＳ２３２Ｃパリティビット設定 */
extern CONST UBYTE	D2W_SelectParity[];
extern CONST UBYTE	D2W_RS232CNone[];
extern CONST UBYTE	D2W_RS232COdd[];
extern CONST UBYTE	D2W_RS232CEven[];

/* ＲＳ２３２Ｃストップビット設定 */
extern CONST UBYTE	D2W_Select232CStopBit[];
extern CONST UBYTE	D2W_RS232C1bit[];
extern CONST UBYTE	D2W_RS232C2bit[];

/* ＲＳ２３２Ｃデータ長設定 */
extern CONST UBYTE	D2W_Select232CDataLength[];
extern CONST UBYTE	D2W_RS232C7bit[];
extern CONST UBYTE	D2W_RS232C8bit[];

/* クラス１関連追加 *//*1996/09/13 Eguchi */
extern CONST UBYTE	D2W_PC_FAX_Scan[];
extern CONST UBYTE	D2W_PC_FAX_Print[];
extern CONST UBYTE	D2W_PC_FAX_Connect[];
extern CONST UBYTE	D2W_PC_FAX_InitialError[];
extern CONST UBYTE	D2W_PC_FAX_Complete[];
extern CONST UBYTE  D2W_PC_FAX_InUse[]; /* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
extern CONST UBYTE  D2W_ReceiveInFax[]; /* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */

/* 送信時、部門コード入力 */
extern CONST UBYTE	D2W_EnterDepartmentCode[];

/* 送信時、ダイヤル番号入力 */
extern CONST UBYTE	D2W_EnterDialNumber[];

/* 送信時、ＰＩＮ番号入力 */
extern CONST UBYTE	D2W_EnterPinNumber[];

/************************************************
** Dial-UpｲﾝﾀｰﾈｯﾄFAX関係	1998/03/12 by K.Okada
************************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/** ユーザ登録 */
extern CONST UBYTE D2W_EMailSettingMode[];
extern CONST UBYTE D2W_SetUserDataMode[];
extern CONST UBYTE D2W_SetUserData[];
/*↓この2つはこの順番で並べて記述*/
extern CONST UBYTE D2W_NewEntry[];
extern CONST UBYTE D2W_UpdateSetting[];
extern CONST UBYTE D2W_NewMailBox[];
/*↓この2つはこの順番で並べて記述*/
extern CONST UBYTE D2W_No[];
extern CONST UBYTE D2W_Yes[];
extern CONST UBYTE D2W_UserCodeNumber[];
extern CONST UBYTE D2W_UserCodeNumberAgain[];
extern CONST UBYTE D2W_EnterYourCodeNumber[];
extern CONST UBYTE D2W_ISP_Name[];
extern CONST UBYTE D2W_AccessPoint[];
/*↓この3つはこの順番で並べて記述*/
extern CONST UBYTE D2W_1stTime[];
extern CONST UBYTE D2W_2ndTime[];
extern CONST UBYTE D2W_3rdTime[];
extern CONST UBYTE D2W_UserName[];
extern CONST UBYTE D2W_PPP_LoginID[];
extern CONST UBYTE D2W_POP_LoginID[];
/*↓この2つはこの順番で並べて記述*/
extern CONST UBYTE D2W_PPP_Password[];
extern CONST UBYTE D2W_PPP_PasswordAgain[];
/*↓この2つはこの順番で並べて記述*/
extern CONST UBYTE D2W_POP_Password[];
extern CONST UBYTE D2W_POP_PasswordAgain[];
extern CONST UBYTE D2W_MailAddress[];
extern CONST UBYTE D2W_PPP_Auth[];
/*↓この3つはこの順番で並べて記述*/
extern CONST UBYTE D2W_PPP_PAP[];
extern CONST UBYTE D2W_PPP_CHAP[];
extern CONST UBYTE D2W_PPP_NoneAuth[];
extern CONST UBYTE D2W_Client[];
extern CONST UBYTE D2W_ISP_Server[];
extern CONST UBYTE D2W_Gateway[];
extern CONST UBYTE D2W_DNS_Server[];
extern CONST UBYTE D2W_Primary[];
extern CONST UBYTE D2W_Secondary[];
extern CONST UBYTE D2W_SMTP_Server[];
extern CONST UBYTE D2W_POP_Server[];

/** 機器動作設定 */
extern CONST UBYTE D2W_SetMachineStateMode[];
extern CONST UBYTE D2W_AutoReceive[];
extern CONST UBYTE D2W_AutoDownload[];
extern CONST UBYTE D2W_AutoPrint[];
extern CONST UBYTE D2W_DeleteMail[];
extern CONST UBYTE D2W_MailHoldTime[];
extern CONST UBYTE D2W_Days1_31[];
extern CONST UBYTE D2W_RxDuringTx[];
extern CONST UBYTE D2W_SetMachineState[];
extern CONST UBYTE D2W_AutoRxStartTime[];
extern CONST UBYTE D2W_AutoRxEndTime[];
extern CONST UBYTE D2W_IntervalTime[];

/** トーン検出設定 */
#if (0)
extern CONST UBYTE D2W_SetToneDetectMode[];
extern CONST UBYTE D2W_SetDialParameter[];
extern CONST UBYTE D2W_DialToneOn[];
extern CONST UBYTE D2W_BusyToneOn[];
#endif

/** ユーザデータ消去 */
extern CONST UBYTE D2W_EraseUserDataMode[];
extern CONST UBYTE D2W_EraseUserData[];

/**  メール設定リスト */
extern CONST UBYTE D2W_PrintUserDataMode[];
extern CONST UBYTE D2W_PrintUserData[];

/** コマンド入力表示 */
extern CONST UBYTE D2W_EnterMailAddress[];

/** 宛先 */
extern CONST UBYTE D2W_SetMailAddressMode[];
extern CONST UBYTE D2W_SetMailAddress[];
extern CONST UBYTE D2W_AddressName[];
extern CONST UBYTE D2W_EraseMailAddressMode[];
extern CONST UBYTE D2W_EraseMailAddress[];
extern CONST UBYTE D2W_PrintMailAddressMode[];
extern CONST UBYTE D2W_PrintMailAddress[];
extern CONST UBYTE D2W_SetMailGroup[];
extern CONST UBYTE D2W_MailGroupSetting[];
extern CONST UBYTE D2W_EraseMailGroupMode[];
extern CONST UBYTE D2W_EraseMailGroup[];
extern CONST UBYTE D2W_PrintMailGroupMode[];
extern CONST UBYTE D2W_PrintMailGroup[];
extern CONST UBYTE D2W_PressOnetouch[];

/** サービスファンクション */
extern CONST UBYTE D2W_InitEngineBoard[];
extern CONST UBYTE D2W_IP_EchoRequest[];
extern CONST UBYTE D2W_INF_Complete[];
extern CONST UBYTE D2W_SF_TTL_Test[];

/** 設置オペレーション */
extern CONST UBYTE D2W_INF_InitialError[];

/** コマンド予約 */
extern CONST UBYTE D2W_ReviewMailComMode[];
extern CONST UBYTE D2W_CancelMailCom[];
extern CONST UBYTE D2W_PrintMailComMode[];
extern CONST UBYTE D2W_PrintMailCom[];
extern CONST UBYTE D2W_PrintStoredMailMode[];
extern CONST UBYTE D2W_PrintStoredMail[];

/** ジャーナルプリント */
extern CONST UBYTE D2W_PrintMailJounalMode[];
extern CONST UBYTE D2W_PrintMailJournal[];

/** 受信 */
extern CONST UBYTE D2W_ManualReceiveMail[];
extern CONST UBYTE D2W_ReceiveMailMode[];
extern CONST UBYTE D2W_PrintReceiveMailMode[];
extern CONST UBYTE D2W_PrintReceiveMail[];

/** 動作中および終了表示　*/
extern CONST UBYTE D2W_INF_Abort[];
extern CONST UBYTE D2W_INF_NoNewMail[];
extern CONST UBYTE D2W_SendingMail[];
extern CONST UBYTE D2W_ReceivingMail[];
extern CONST UBYTE D2W_INF_Creating[];
extern CONST UBYTE D2W_INF_Dialing[];
extern CONST UBYTE D2W_INF_Connecting[];
extern CONST UBYTE D2W_INF_Sending[];
extern CONST UBYTE D2W_INF_Receiving[];
extern CONST UBYTE D2W_INF_Checking[];			/* 1998/08/18 by Y.Tanimoto */
extern CONST UBYTE D2W_INF_PrintRcvReport[];	/* 1998/05/15 by Y.Tanimoto */

/** サービスファンクション */
/** PTTテスト */
extern CONST UBYTE D2W_PTT_TestMode[];
extern CONST UBYTE D2W_PTT_Setting[];
extern CONST UBYTE D2W_DataRate[];
extern CONST UBYTE D2W_SymbolRate[];
extern CONST UBYTE D2W_CarrierBias[];
extern CONST UBYTE D2W_SecondChannel[];
extern CONST UBYTE D2W_UpperBandEdge[];
extern CONST UBYTE D2W_VFC_Modulation[];
extern CONST UBYTE D2W_V34_Modulation[];
extern CONST UBYTE D2W_CarrierBiasRange[];
extern CONST UBYTE D2W_BandEdgeRange[];
extern CONST UBYTE D2W_INF_Mode[];

/* PTTテスト信号種類 */
/*↓この順番で並べて記述*/
extern CONST UBYTE D2W_DTMF_Tone0[];
extern CONST UBYTE D2W_DTMF_Tone1[];
extern CONST UBYTE D2W_DTMF_Tone2[];
extern CONST UBYTE D2W_DTMF_Tone3[];
extern CONST UBYTE D2W_DTMF_Tone4[];
extern CONST UBYTE D2W_DTMF_Tone5[];
extern CONST UBYTE D2W_DTMF_Tone6[];
extern CONST UBYTE D2W_DTMF_Tone7[];
extern CONST UBYTE D2W_DTMF_Tone8[];
extern CONST UBYTE D2W_DTMF_Tone9[];
extern CONST UBYTE D2W_DTMF_ToneAst[];
extern CONST UBYTE D2W_DTMF_ToneSharp[];
extern CONST UBYTE D2W_DTMF_ToneA[];
extern CONST UBYTE D2W_DTMF_ToneB[];
extern CONST UBYTE D2W_DTMF_ToneC[];
extern CONST UBYTE D2W_DTMF_ToneD[];
extern CONST UBYTE D2W_V21Ch1MkSymbol[];
extern CONST UBYTE D2W_V21Ch2MkSymbol[];
extern CONST UBYTE D2W_V23BwardChMkSymbol[];
extern CONST UBYTE D2W_V23FwardChMkSymbol[];
extern CONST UBYTE D2W_V22CallMk600bps[];
extern CONST UBYTE D2W_V22CallMk1200bps[];
extern CONST UBYTE D2W_V22bisCallMk2400bps[];
extern CONST UBYTE D2W_V22AnswerSignal[];
extern CONST UBYTE D2W_V22bisAnswerSignal[];
extern CONST UBYTE D2W_V21Ch1SpSymbol[];
extern CONST UBYTE D2W_V21Ch2SpSymbol[];
extern CONST UBYTE D2W_V23BwardChSpSymbol[];
extern CONST UBYTE D2W_V23FwardChSpSymbol[];
extern CONST UBYTE D2W_V32_9600bps[];
extern CONST UBYTE D2W_V32bis14400bps[];
extern CONST UBYTE D2W_V32TCM9600bps[];
extern CONST UBYTE D2W_V32TCM14400bps[];
extern CONST UBYTE D2W_V32bisTCM7200bps[];
extern CONST UBYTE D2W_V32_4800bps[];
extern CONST UBYTE D2W_OffFook[];
extern CONST UBYTE D2W_V25AnswerTone[];
extern CONST UBYTE D2W_1800HzGuardTone[];
extern CONST UBYTE D2W_V25Send1300Hz[];
extern CONST UBYTE D2W_FaxSend1100Hz[];
extern CONST UBYTE D2W_BellAnswer2225hz[];
extern CONST UBYTE D2W_V21Ch2[];
extern CONST UBYTE D2W_V27ter2400bps[];
extern CONST UBYTE D2W_V27ter4800bps[];
extern CONST UBYTE D2W_V29_7200bps[];
extern CONST UBYTE D2W_V29_9600bps[];
extern CONST UBYTE D2W_V17_7200bpsL_Train[];
extern CONST UBYTE D2W_V17_7200bpsS_Train[];
extern CONST UBYTE D2W_V17_9600bpsL_Train[];
extern CONST UBYTE D2W_V17_9600bpsS_Train[];
extern CONST UBYTE D2W_V17_12000bpsL_Train[];
extern CONST UBYTE D2W_V17_12000bpsS_Train[];
extern CONST UBYTE D2W_V17_14400bpsL_Train[];
extern CONST UBYTE D2W_V17_14400bpsS_Train[];
extern CONST UBYTE D2W_VFC_Modulation[];
extern CONST UBYTE D2W_V34_Modulation[];
/*↑この順番で並べて記述*/

/* Gurad Tone */
/*↓この3個はこの順番で並べて記述*/
extern CONST UBYTE D2W_GT1800hz[];
extern CONST UBYTE D2W_GT550hz[];
extern CONST UBYTE D2W_NoGuardTone[];

/* Mode */
/*↓この2個はこの順番で並べて記述*/
extern CONST UBYTE D2W_OriginateMode[];
extern CONST UBYTE D2W_AnswerMode[];

/* Data Rate */
/*↓この12個はこの順番で並べて記述*/
extern CONST UBYTE D2W_2400bps[];
extern CONST UBYTE D2W_4800bps[];
extern CONST UBYTE D2W_7200bps[];
extern CONST UBYTE D2W_9600bps[];
extern CONST UBYTE D2W_12000bps[];
extern CONST UBYTE D2W_14400bps[];
extern CONST UBYTE D2W_16800bps[];
extern CONST UBYTE D2W_19200bps[];
extern CONST UBYTE D2W_21600bps[];
extern CONST UBYTE D2W_24000bps[];
extern CONST UBYTE D2W_26400bps[];
extern CONST UBYTE D2W_28800bps[];
extern CONST UBYTE D2W_31200bps[];
extern CONST UBYTE D2W_33600bps[];

/* Symbol Rate */
/*↓この6つはこの順番で並べて記述*/
extern CONST UBYTE D2W_2400baud[];
extern CONST UBYTE D2W_2800baud[];
extern CONST UBYTE D2W_3000baud[];
extern CONST UBYTE D2W_3200baud[];
extern CONST UBYTE D2W_3429baud[];

/* Second Channel */
/*↓この2つはこの順番で並べて記述*/
extern CONST UBYTE D2W_Disable[];
extern CONST UBYTE D2W_Enable[];

/* Upper Band Edge */
/*↓この11個はこの順番で並べて記述*/
extern CONST UBYTE D2W_V34BandEdge0Db[];
extern CONST UBYTE D2W_V34BandEdge2Db[];
extern CONST UBYTE D2W_V34BandEdge4Db[];
extern CONST UBYTE D2W_V34BandEdge6Db[];
extern CONST UBYTE D2W_V34BandEdge8Db[];
extern CONST UBYTE D2W_V34BandEdge10Db[];
extern CONST UBYTE D2W_V34BandEdgeG1Db[];
extern CONST UBYTE D2W_V34BandEdgeG2Db[];
extern CONST UBYTE D2W_V34BandEdgeG3Db[];
extern CONST UBYTE D2W_V34BandEdgeG4Db[];
extern CONST UBYTE D2W_V34BandEdgeG5Db[];
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	ＦＡＸワープ
 *----------------------------------*/
extern CONST UBYTE D2W_FaxWarpMode[];
extern CONST UBYTE D2W_EnterFaxWarpMode[];
extern CONST UBYTE D2W_PrintFaxWarpMode[];
extern CONST UBYTE D2W_SetFaxWarpMode[];
extern CONST UBYTE D2W_EnterFaxWarp[];
extern CONST UBYTE D2W_PrintFaxWarp[];
extern CONST UBYTE D2W_SetFaxWarp[];
extern CONST UBYTE D2W_WarpSelectNumber[];
extern CONST UBYTE D2W_WarpTime[];
extern CONST UBYTE D2W_WarpWeek[][21];
extern CONST UBYTE D2W_SelectWarpRxDocPrint[][21];

extern CONST UBYTE D2W_WarpAltNumber[];		/* ＷＡＲＰ転送先ワーディング追加 By O.Kimoto 1999/02/08 */

#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	ナンバーディスプレイ
 *----------------------------------*/
extern CONST UBYTE D2W_NumberDisplayMode[];
extern CONST UBYTE D2W_EnterNumberDisplayMode[];
extern CONST UBYTE D2W_PrintNumberDisplayMode[];
extern CONST UBYTE D2W_SetNumberDisplayMode[];
extern CONST UBYTE D2W_EnterNumberDisplay[];
extern CONST UBYTE D2W_PrintNumberDisplay[];
extern CONST UBYTE D2W_SetNumberDisplay[];
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* By H.Fujimura 1999/01/07 */
extern CONST UBYTE D2W_Set_ND_Warp[];
 #endif
extern CONST UBYTE D2W_ND_SelectNumber[];
extern CONST UBYTE D2W_ND_TelMode[][21];
extern CONST UBYTE D2W_ND_NoNotice[];
extern CONST UBYTE D2W_ND_OutOfDisp[];
extern CONST UBYTE D2W_ND_PublicTel[];
extern CONST UBYTE D2W_ND_Parameter[];
extern CONST UBYTE D2W_Print_ND_JournalMode[];
extern CONST UBYTE D2W_Print_ND_Journal[];
#endif

/*----------------------------------*
 *	通信確認
 *----------------------------------*/
extern CONST UBYTE	D2W_ConfirmReport[];

/*----------------------------------*
 *	オペレーションプロテクト
 *----------------------------------*/
extern CONST UBYTE	D2W_OperationProtected[];

#if (PRO_COPY_FAX_MODE == ENABLE)
/*----------------------------------*
 *	コピーモード
 *----------------------------------*/
extern CONST UBYTE	D2W_ChangeManual[];
#endif

#if (PRO_FBS == ENABLE)
/*----------------------------------*
 *	ブック送信
 *----------------------------------*/
extern CONST UBYTE	D2W_SetBookTxDocumentSize[];
extern CONST UBYTE	D2W_SetBookTxNextDocument[];

extern CONST UBYTE	D2W_NextBookDocScanStart[];
extern CONST UBYTE	D2W_NextBookDocTxStart[];
extern CONST UBYTE	D2W_NextBookDocScanEnd[];
#endif

/* 紙サイズ（R → 0x01(OPR_PAPER_SIZE_R)で定義して下さい） */
extern CONST UBYTE	D2W_PaperSize_None[];
extern CONST UBYTE	D2W_PaperSize_A5[];
extern CONST UBYTE	D2W_PaperSize_Letter[];
extern CONST UBYTE	D2W_PaperSize_A4[];
extern CONST UBYTE	D2W_PaperSize_Legal[];
extern CONST UBYTE	D2W_PaperSize_B5R[];
extern CONST UBYTE	D2W_PaperSize_B4[];
extern CONST UBYTE	D2W_PaperSize_A3[];
extern CONST UBYTE	D2W_PaperSize_A4R[];
extern CONST UBYTE	D2W_PaperSize_LetterR[];
extern CONST UBYTE	D2W_PaperSize_F4[];
extern CONST UBYTE	D2W_PaperSize_A5R[];
extern CONST UBYTE	D2W_PaperSize_Postcard[];
extern CONST UBYTE	D2W_PaperSize_LD[];
extern CONST UBYTE	D2W_PaperSize_GLetterR[];
extern CONST UBYTE	D2W_PaperSize_ExecutiveR[];
extern CONST UBYTE	D2W_PaperSize_HalfLetterR[];  /* ハーフレター横 added by honda 1997/10/04 */
extern CONST UBYTE	D2W_PaperSize_InvoiceR[];
extern CONST UBYTE	D2W_PaperSize_GLegal[];
extern CONST UBYTE	D2W_PaperSize_GLetter[];
extern CONST UBYTE	D2W_PaperSize_Card[];
extern CONST UBYTE	D2W_PaperSize_Executive[];
extern CONST UBYTE	D2W_PaperSize_B5[];
extern CONST UBYTE	D2W_PaperSize_C5[];
extern CONST UBYTE	D2W_PaperSize_HalfLetter[];
extern CONST UBYTE	D2W_PaperSize_Invoice[];
extern CONST UBYTE	D2W_PaperSize_B6[];
extern CONST UBYTE	D2W_PaperSize_DL[];
extern CONST UBYTE	D2W_PaperSize_CM10[];
extern CONST UBYTE	D2W_PaperSize_A6[];
extern CONST UBYTE	D2W_PaperSize_Monarch[];
extern CONST UBYTE	D2W_PaperSize_35[];
extern CONST UBYTE	D2W_PaperSize_User[];
extern CONST UBYTE	D2W_PaperSize_OHP[];
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)	/* By S.Fukui Jan.23,1998 */
extern CONST UBYTE 	D2W_PaperSize_Auto[];
#endif
#if (PRO_PITNEYBOWES == ENABLE)
extern CONST UBYTE	D2W_PaperSize_Ledger[];	/* 原稿サイズ表示ＰＢ用 By S.Fukui Aug.25,1998 */
extern CONST UBYTE	D2W_PaperSize_LtLg[];	/* 原稿サイズ表示ＰＢ用 (For Letter/Legal) By S.Fukui Aug.25,1998 */
#endif
/*----------------------------------*
 *	サービスファンクション
 *----------------------------------*/
/* マシンパラメータ */
extern CONST UBYTE	D2W_SF_ParameterSet[];
extern CONST UBYTE	D2W_SF_ParameterClear[];

/* メモリースイッチ */
extern CONST UBYTE	D2W_SF_MemorySwitchSet[];
extern CONST UBYTE	D2W_SF_MemorySwitchClear[];

/* ユーザ設定クリア */
extern CONST UBYTE	D2W_SF_BackUpFileClear[];

/* オールラムクリア */
extern CONST UBYTE	D2W_SF_AllClear[];

/* 機種固有スイッチ */
extern CONST UBYTE	D2W_SF_UniqSwitchSet[];
extern CONST UBYTE	D2W_SF_UniqSwitchClear[];

/* 保守用スイッチ */
extern CONST UBYTE	D2W_SF_MaintenanceSet[];
extern CONST UBYTE	D2W_SF_MaintenanceClear[];

/* テストファンクション -> このワーディングの並びはかえてはいけない*/
#if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1997/10/02 Y.Matsukuma */
extern CONST UBYTE	D2W_SF_LifeMonitor[];
extern CONST UBYTE	D2W_SF_LifeMonitorClear[];
extern CONST UBYTE	D2W_SF_TestPatternPrint[];
extern CONST UBYTE	D2W_SF_StampTest[];
extern CONST UBYTE	D2W_SF_Shading[];
#elif (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ＨＩＮＯＫＩは原稿排出テストは有りません by O.Kimoto 1999/02/09 */
extern CONST UBYTE	D2W_SF_LifeMonitor[];
extern CONST UBYTE	D2W_SF_TestPatternPrint[];
extern CONST UBYTE	D2W_SF_StampTest[];
extern CONST UBYTE	D2W_SF_Shading[];
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/12/26 */
extern CONST UBYTE	D2W_SF_PS1_PB4_Threshold[];		/* Add by Y.Kano 2003/12/26 */
 #endif
#else
extern CONST UBYTE	D2W_SF_LifeMonitor[];
extern CONST UBYTE	D2W_SF_TestPatternPrint[];
extern CONST UBYTE	D2W_SF_StampTest[];
extern CONST UBYTE	D2W_SF_DocumentFeedOutTest[];
extern CONST UBYTE	D2W_SF_Shading[];
#endif

/* ライフモニター */
extern CONST UBYTE	D2W_SF_BoardNumber[];
extern CONST UBYTE	D2W_SF_LifeReadingPage[];
extern CONST UBYTE	D2W_SF_LifeTxPage[];
extern CONST UBYTE	D2W_SF_LifePrintingPage[];
extern CONST UBYTE	D2W_SF_LifeDrumReplaceCount[];
extern CONST UBYTE	D2W_SF_LifeDrumLifeCount[];
extern CONST UBYTE	D2W_SF_LifeTonerReplaceCount[];
extern CONST UBYTE	D2W_SF_LifeTonerLifeCount[];
extern CONST UBYTE	D2W_SF_LifeFuserReplaceCount[];
extern CONST UBYTE	D2W_SF_LifeFuserLifeCount[];
extern CONST UBYTE	D2W_SF_LifeTransferReplaceCount[];
extern CONST UBYTE	D2W_SF_LifeTransferLifeCount[];
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/07 */
extern CONST UBYTE	D2W_SF_CPU_Revision[];
extern CONST UBYTE	D2W_SF_ROM_Revision[];
#endif

/* テストパターン */
extern CONST UBYTE	D2W_SF_Pattern[];

/* 工場ファンクション */
extern CONST UBYTE	D2W_SF_FactoryFunction[];

extern CONST UBYTE	D2W_SF_LEDTest[];
extern CONST UBYTE	D2W_SF_LCDTest[];
extern CONST UBYTE	D2W_SF_PanelTest[];

extern CONST UBYTE	D2W_SF_SRAMCheck[];
extern CONST UBYTE	D2W_SF_DRAMCheck[];
extern CONST UBYTE	D2W_SF_RTCTest[];
extern CONST UBYTE	D2W_SF_RS232CTest[];
extern CONST UBYTE	D2W_SF_CassetteCheck[];

/* キー */
/*このワーディングの順番はキーコードの順番に一致させなくてはならない */
extern CONST UBYTE	D2W_SF_Receive[];
extern CONST UBYTE	D2W_SF_Hook[];
extern CONST UBYTE	D2W_SF_Hold[];
extern CONST UBYTE	D2W_SF_Mode[];
extern CONST UBYTE	D2W_SF_Contrast[];
extern CONST UBYTE	D2W_SF_Program[];
extern CONST UBYTE	D2W_SF_CursorLeft[];
extern CONST UBYTE	D2W_SF_Set[];
extern CONST UBYTE	D2W_SF_DelayedCheck[];
extern CONST UBYTE	D2W_SF_Clear[];	
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1997/08/20 Y.Matsukuma */
extern CONST UBYTE	D2W_SF_DialMark[];
#else
extern CONST UBYTE	D2W_SF_Sort[];
#endif
extern CONST UBYTE	D2W_SF_Broadcast[];
extern CONST UBYTE	D2W_SF_Special[];
extern CONST UBYTE	D2W_SF_Group[];
extern CONST UBYTE	D2W_SF_Speed[];
extern CONST UBYTE	D2W_SF_MemoryTx[];
extern CONST UBYTE	D2W_SF_Stop[];
extern CONST UBYTE	D2W_SF_Start[];
extern CONST UBYTE	D2W_SF_Copy[];
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1997/08/20 Y.Matsukuma */
extern CONST UBYTE	D2W_SF_Redial[];
 #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
extern CONST UBYTE	D2W_SF_Reservation[];
 #else
extern CONST UBYTE	D2W_SF_Stamp[];
 #endif
extern CONST UBYTE	D2W_SF_Mercury[];
extern CONST UBYTE	D2W_SF_Flash[];
#else
extern CONST UBYTE	D2W_SF_PaperSelect[];
extern CONST UBYTE	D2W_SF_Stamp[];
extern CONST UBYTE	D2W_SF_Reduction[];
extern CONST UBYTE	D2W_SF_Magnification[];
#endif
extern CONST UBYTE	D2W_SF_CopyFax[];
extern CONST UBYTE	D2W_SF_BookDocSize[];
extern CONST UBYTE	D2W_SF_CopyReset[];
extern CONST UBYTE	D2W_SF_Tone[];
#if defined(HINOKI3)	/* ONETOUCH_30_KEYがプレフィックスキーに変わったので by K.Watanabe 2004/10/26 */
extern CONST UBYTE	D2W_SF_Prefix[];
#endif

/* 回線テスト */
extern CONST UBYTE	D2W_SF_LineTest[];
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/25 */
/* 警察FAX DVT_ID15 Added by SMuratec K.W.Q 2005/11/05 */
extern CONST UBYTE	D2W_SF_KEIDEN_RelayTest[];
extern CONST UBYTE	D2W_SF_KEIDEN_TonalTest[];
extern CONST UBYTE	D2W_SF_KEIDEN_DTMF_Test[];
#endif		/* End of (defined (KEISATSU)) */
extern CONST UBYTE	D2W_SF_PhoneTest[];
extern CONST UBYTE	D2W_SF_TonalTest[];
extern CONST UBYTE	D2W_SF_DTMF_Test[];

/* リレー */
extern CONST UBYTE	D2W_SF_RelayTest1[];
extern CONST UBYTE	D2W_SF_RelayTest2[];
#if (PRO_MODEM == R288F)	/* By H.Fujimura 1999/01/07 */
 #if defined (KEISATSU)		/* 警察FAX DVT_ID15 Modify by SMuratec K.W.Q 2005/11/05 */
extern CONST UBYTE	D2W_SF_R288F_RelayTest1[];
extern CONST UBYTE	D2W_SF_R288F_Keiden_RelayTest1[];
 #else
extern CONST UBYTE	D2W_SF_R288F_RelayTest1[];
 #endif		/* End of (defined (KEISATSU)) */
extern CONST UBYTE	D2W_SF_R288F_RelayTest2[];
#endif

/* トーナル */
extern CONST UBYTE	D2W_SF_FSK[];
extern CONST UBYTE	D2W_SF_White[];
extern CONST UBYTE	D2W_SF_Black[];
extern CONST UBYTE	D2W_SF_Pix[];

/* ミラーキャリッジ輸送モードセット */
extern CONST UBYTE	D2W_SF_MirrorCarrigeModeSet[];

/* サービスレポート */
extern CONST UBYTE	D2W_SF_ServicePrint[];

extern CONST UBYTE	D2W_SF_DTMF[];
extern CONST UBYTE	D2W_SF_DTMFRow[];
extern CONST UBYTE	D2W_SF_DTMFColum[];

/* カセットテスト */
extern CONST UBYTE	D2W_SF_CassetteOpen[];
extern CONST UBYTE	D2W_SF_NoPaper[];
extern CONST UBYTE	D2W_SF_SideCoverOpen[];
extern CONST UBYTE	D2W_SF_NoUnit[];

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ライフモニタークリア */
extern CONST UBYTE	D2W_SF_LifeMonitorClear[];
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
/* ライフモニタクリアパスコード */
extern CONST UBYTE	D2W_SF_ServiceCode[];
extern CONST UBYTE	D2W_SF_EnterServiceCode[];
#endif

/* プリンタメンテナンス */
extern CONST UBYTE	D2W_SF_ReplaceCountSet[];
extern CONST UBYTE	D2W_SF_ServiceCall[];
extern CONST UBYTE	D2W_SF_FuserReplace[];
extern CONST UBYTE	D2W_SF_TransferReplace[];
extern CONST UBYTE	D2W_SF_ServiceCallCount[];
extern CONST UBYTE	D2W_SF_HeatTrouble[];
extern CONST UBYTE	D2W_SF_HeatDisconnection[];
extern CONST UBYTE	D2W_SF_HeatShortCircuit[];
extern CONST UBYTE	D2W_SF_FanTrouble[];
extern CONST UBYTE	D2W_SF_RxTrouble[];
extern CONST UBYTE	D2W_SF_DrumTrouble[];
extern CONST UBYTE	D2W_SF_CoolerFanMotorTrouble[];
extern CONST UBYTE	D2W_SF_HvFuseDisconnect[];

/* 消耗品発注機能 */
extern CONST UBYTE	D2W_SF_ReceiverCustomerCode[];
extern CONST UBYTE	D2W_SF_ReceiverCompany[];
extern CONST UBYTE	D2W_SF_SenderCustomerCode[];
extern CONST UBYTE	D2W_SF_SenderCompany[];
extern CONST UBYTE	D2W_SF_SenderSection[];
extern CONST UBYTE	D2W_SF_SenderSection2[];  /* orderbythonda1998/05/18 */
extern CONST UBYTE	D2W_SF_SenderTelNumber[];
extern CONST UBYTE	D2W_SF_SerialNumber[];
extern CONST UBYTE	D2W_SF_Date[];
extern CONST UBYTE	D2W_SF_PrintOrderForm[];
#if defined(US1)
extern CONST UBYTE	D2W_SF_ToCompanyFaxNumber[];	/* orderbythonda1998/11/11 */
extern CONST UBYTE	D2W_SF_ToCompanyTelNumber[];	/* orderbythonda1998/11/11 */
#endif

/* メモリダンプ */
extern CONST UBYTE	D2W_SF_MemoryDump[];
extern CONST UBYTE	D2W_SF_MemoryDumpAddress[];
extern CONST UBYTE	D2W_SF_MemoryDumpLength[];

/* ＤＲＡＭクリア */
extern CONST UBYTE	D2W_SF_ClearDRAM[];

/* オプションデータ初期化 */
extern CONST UBYTE	D2W_SF_OptionDataInitial[];

/* 消耗品発注データクリア */
#if (PRO_PRINT_TYPE == THERMAL)	/* By H.Fujimura 1999/01/07 */
extern CONST UBYTE	D2W_SF_MntDataClear[];
#else
extern CONST UBYTE	D2W_SF_OrderDataClear[];
#endif

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/20 */
/* T30モニター番号 */
extern CONST UBYTE	D2W_SF_T30MonitorNumber[];
#endif

extern CONST UBYTE	D2W_SF_OK[];
extern CONST UBYTE	D2W_SF_NG[];

/*----------------------------------*
 *	ＬＣＤ・リストでの頭文字表示
 *----------------------------------*/
#if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
extern CONST UBYTE	D2W_HeadCharacter_Speed;
extern CONST UBYTE	D2W_HeadCharacter_Command;
extern CONST UBYTE	D2W_HeadCharacter_Batch;
extern CONST UBYTE	D2W_HeadCharacter_Polling;
extern CONST UBYTE	D2W_HeadCharacter_Tray;
#endif

#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
/*----------------------------------*
 *	通信結果表示
 *----------------------------------*/
extern CONST UBYTE	D2W_CommResultList[];
extern CONST UBYTE	D2W_Tx[];
extern CONST UBYTE	D2W_Rx[];
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC 設定表示 */
extern CONST UBYTE	D2W_RemoteTxSetting[];
extern CONST UBYTE	D2W_RemoteTxSettingOff[];
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 音量調整処理の追加 by Y.Kano 2003/08/27 */
/*----------------------------------*
 *	音量調整表示
 *----------------------------------*/
extern CONST UBYTE	D2W_BuzzerVolume[];
extern CONST UBYTE	D2W_MonitorVolume[];
extern CONST UBYTE	D2W_BuzzerVolumeEnter[];
extern CONST UBYTE	D2W_RingerControl[];
extern CONST UBYTE	D2W_RingerControlOn[];
extern CONST UBYTE	D2W_RingerControlOff[];
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
extern CONST UBYTE	D2W_ShadingWord[];	 			/* Added by SMuratec K.W.Q 2003/08/11 */
extern CONST UBYTE	D2W_SF_PS2AdjustMode[];			/* Add by Y.Kano 2003/10/17 */
extern CONST UBYTE	D2W_PS2VolumueFullLight_1[];	/* Add by Y.Kano 2003/10/17 */
extern CONST UBYTE	D2W_PS2VolumueFullLight_2[];	/* Add by Y.Kano 2003/10/17 */
extern CONST UBYTE	D2W_PS2VolumueTitle[];			/* Add by Y.Kano 2003/10/17 */
extern CONST UBYTE	D2W_PS2VolumueSenter[];			/* Add by Y.Kano 2003/10/17 */
extern CONST UBYTE	D2W_PS2_OK[];					/* Add by Y.Kano 2003/10/18 */
extern CONST UBYTE 	D2W_PS2_Complete[];				/* Add by Y.Kano 2003/10/18 */
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* チェッカー表示の追加 by SMuratec L.Z.W 2003/10/23 */
extern CONST UBYTE 	D2W_Character[];
extern CONST UBYTE	D2W_SF_PS1_PB4_CheckMode[];		/* Add by Y.Kano 2003/12/18 */
extern CONST UBYTE	D2W_Stop[];						/* Add by Y.Kano 2003/12/18 */
extern CONST UBYTE	D2W_PleaseNonPaper[];			/* Add by Y.Kano 2003/12/18 */
extern CONST UBYTE	D2W_SF_PS1_PB4_Error[];			/* Add by Y.Kano 2003/12/26 */
extern CONST UBYTE	D2W_SF_PS1_Error[];				/* Add by Y.Kano 2003/12/26 */
extern CONST UBYTE	D2W_SF_PB4_Error[];				/* Add by Y.Kano 2003/12/26 */
#endif

#if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)	/* ＰＳ１、ＰＳ２、ＰＢ４閾値自動調整モード by Y.Kano 2004/10/06 */
extern CONST UBYTE	D2W_SF_PS1_PS2_PB4_AdjustMode[];
extern CONST UBYTE	D2W_PleaseNonPaper[];
extern CONST UBYTE	D2W_SF_PS1_PS2_PB4_Error[];
extern CONST UBYTE	D2W_SF_PS1_PS2_Error[];
extern CONST UBYTE	D2W_SF_PS1_PB4_Error[];
extern CONST UBYTE	D2W_SF_PS1_Error[];
extern CONST UBYTE	D2W_SF_PS2_PB4_Error[];
extern CONST UBYTE	D2W_SF_PS2_Error[];
extern CONST UBYTE	D2W_SF_PB4_Error[];
extern CONST UBYTE	D2W_Stop[];
extern CONST UBYTE	D2W_SensorTest[];
#endif

#if defined(STOCKHM2) || (PRO_JOURNAL_VER_UP == ENABLE)	/* Added by SMuratec C.P 2004/06/07 *//* by K.Watanabe 2004/10/15 */
/*----------------------------------*
 *	ジャーナルプリント
 *----------------------------------*/
extern CONST UBYTE	D2W_JournalTx[];
extern CONST UBYTE	D2W_JournalRx[];
extern CONST UBYTE	D2W_JournalTxRx[];
#endif

#if defined(STOCKHM2)	/* Added by SMuratec C.P 2004/06/07 */
extern CONST UBYTE  D2W_CommConfirm[];
extern CONST UBYTE  D2W_FunctionEnter[];
extern CONST UBYTE  D2W_InkConfirm[];
#endif

/** トーン検出設定 */
#if defined(STOCKHM2) || defined(HINOKI3)	/* 復活 by SMuratec 夏 2004/7/12*/ /* Add by Y.Kano 2004/11/25 */
extern CONST UBYTE D2W_SetToneDetectMode[];
extern CONST UBYTE D2W_SetDialParameter[];
extern CONST UBYTE D2W_DialToneOn[];
extern CONST UBYTE D2W_On[];
extern CONST UBYTE D2W_Off[];
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec K.W.Q 2005/06/02 */
/** トーン検出設定 */
extern CONST UBYTE D2W_KanyuDialToneOn[];
extern CONST UBYTE D2W_DefaultLine[];
extern CONST UBYTE D2W_DefaultCOMMethod[];
extern CONST UBYTE D2W_KeidenScramleOn[];
extern CONST UBYTE D2W_KanyuScramleOn[];
extern CONST UBYTE D2W_Keiden[];
extern CONST UBYTE D2W_Kanyu[];
extern CONST UBYTE D2W_Issei[];
extern CONST UBYTE D2W_Kobetsu[];
extern CONST UBYTE D2W_Hoji[];
extern CONST UBYTE D2W_S_On[];
extern CONST UBYTE D2W_S_Off[];
extern CONST UBYTE D2W_Senyo[];

/*	サービス設定 */
extern CONST UBYTE D2W_SetS1Bypass[];
extern CONST UBYTE D2W_ScrambleAvailable[];
extern CONST UBYTE D2W_KeyLockOn[];
extern CONST UBYTE D2W_SendLevel[];
extern CONST UBYTE D2W_DTMFSendLevel[];
#if (1)
extern CONST UBYTE D2W_IsseiRingTimeout[];
extern CONST UBYTE D2W_RingTimeout[];
#else
extern CONST UBYTE D2W_IsseiRingCount[];
#endif
extern CONST UBYTE D2W_IsseiAbility[];
extern CONST UBYTE D2W_IsseiTimeOut[];
extern CONST UBYTE D2W_RemoteRxDialOne[];
extern CONST UBYTE D2W_KeidenRxPriority[];
extern CONST UBYTE D2W_FPGAVersion[];
extern CONST UBYTE D2W_KeidenDialTone[];

extern CONST UBYTE D2W_S1Bypass[];
extern CONST UBYTE D2W_Scramble[];
extern CONST UBYTE D2W_KeidenKanyu[];
extern CONST UBYTE D2W_IsseiKobetsu[];
extern CONST UBYTE D2W_S_OnOFF[];
extern CONST UBYTE D2W_KyotsuSenyo[];
extern CONST UBYTE D2W_AutoRx[];
#if (0)		/* 警察FAX DVT_ID27 Delete by SMuratec K.W.Q 2005/10/28 */
extern CONST UBYTE D2W_KeidenIssei[];
extern CONST UBYTE D2W_KeidenKobetsu[];
#endif
extern CONST UBYTE D2W_RingCount[];
extern CONST UBYTE D2W_IsseiSpeed[];
extern CONST UBYTE D2W_IsseiCode[];
extern CONST UBYTE D2W_IsseiMinScanLineTime[];
extern CONST UBYTE D2W_NumberOfRings_Keiden[];
extern CONST UBYTE D2W_NumberOfRings_Kanyu[];

/*	電話呼出中	*/
extern CONST UBYTE D2W_KeidenTelBell[];
extern CONST UBYTE D2W_KanyuTelBell[];

extern CONST UBYTE D2W_Telephone[];

/*	指令モート	*/
extern CONST UBYTE D2W_IsseiShireiKido[];

/* S1アラーム */
extern CONST UBYTE D2W_S1Alarm[];

/* パネルキーテスト用 */
extern CONST UBYTE D2W_SF_KeidenKanyu[];
extern CONST UBYTE D2W_SF_IsseiKobetsu[];
extern CONST UBYTE D2W_SF_S_OnOff[];
extern CONST UBYTE D2W_SF_KyotsuSenyo[];

/* 工場ファンクション */
extern CONST UBYTE D2W_SF_CopyOnetouchA_ToAll[];
extern CONST UBYTE D2W_SF_Transmit1100HzTone[];
extern CONST UBYTE D2W_SF_TransmitV29Data[];

#endif		/* End of (defined (KEISATSU)) */

#if defined(STOCKHM2) /* Add by SMuratec C.P 2004/07/23 */
extern CONST UBYTE D2W_VolumeControl[];
#endif

#if (PRO_RTC_RX5C338A == ENABLE)
extern CONST UBYTE D2W_RTC_Init[];
#endif

extern CONST UBYTE	D2W_WordingTail[];
#endif	/* (PRO_ANK_TO_KANJI == ENABLE) */
#endif	/* OPR_WRD_0 */
