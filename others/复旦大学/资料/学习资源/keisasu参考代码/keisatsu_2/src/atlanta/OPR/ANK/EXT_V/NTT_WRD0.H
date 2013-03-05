/************************************************************************
*	System		: POPLAR_B NTT
*	File Name	: NTT_WRD0.H
*	Author		: 渡辺一章
*	Date		: 1999/06/14
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: オペレーションワーディング宣言
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef NTT_WRD_0
	#define NTT_WRD_0	1

#include	"\src\atlanta\define\product.h"

#if (PRO_CPU == SH7043)	/* 各国ワーディング先頭位置認識用 */
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
#if (PRO_FBS == ENABLE)
extern CONST UBYTE	D2W_ScannerTransportReady[];
#endif

/* コピーモードの表示 */
#if (PRO_COPY_FAX_MODE == ENABLE)
extern CONST UBYTE	D2W_CopyReady[];
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

/* 選択を促す表示（点滅する表示 ) */
extern CONST UBYTE	D2W_ProgramEnter[];
extern CONST UBYTE	D2W_ProgramClear[];
extern CONST UBYTE	D2W_EnterStop[];
extern CONST UBYTE	D2W_StartStop[];
extern CONST UBYTE	D2W_SpecialCommunicationEnter[];
extern CONST UBYTE	D2W_ReviewStop[];
extern CONST UBYTE	D2W_CheckProgramEnter[];
extern CONST UBYTE	D2W_CheckProgramClear[];
extern CONST UBYTE	D2W_CheckStartStop[];

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

/* 各機能の詳細データ設定中（上段） */
extern CONST UBYTE	D2W_DelayedTransmission[];
extern CONST UBYTE	D2W_SecureTransmission[];
extern CONST UBYTE	D2W_RelayTransmission[];
extern CONST UBYTE	D2W_PollingCommunication[];
extern CONST UBYTE	D2W_BatchTransmission[];
extern CONST UBYTE	D2W_ContinuousPolling[];
extern CONST UBYTE	D2W_InputSubAddressNumber[];
extern CONST UBYTE	D2W_InputPasswordNumber[];

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
extern CONST UBYTE	D2W_ContrastLightDark[];

/*----------------------------------*
 *	機器エラー
 *----------------------------------*/

/* カバー */
extern CONST UBYTE	D2W_PleaseCloseScannerCover[];
extern CONST UBYTE	D2W_PleaseClose1stJamCover[];
extern CONST UBYTE	D2W_PleaseClose2ndJamCover[];
extern CONST UBYTE	D2W_PleaseClose3rdJamCover[];
extern CONST UBYTE	D2W_PleaseOpen1stJamCover[];
extern CONST UBYTE	D2W_PleaseOpen2ndJamCover[];
extern CONST UBYTE	D2W_PleaseOpen3rdJamCover[];
extern CONST UBYTE	D2W_PleaseOpenTopCover[];
extern CONST UBYTE	D2W_PleaseOpenCloseScanCover[];

/* カセット */
extern CONST UBYTE	D2W_PleaseClose1stCassette[];
extern CONST UBYTE	D2W_PleaseClose2ndCassette[];
extern CONST UBYTE	D2W_PleaseClose3rdCassette[];

/* 記録紙 */
extern CONST UBYTE	D2W_ReplaceManualPaper[];
extern CONST UBYTE	D2W_RepRxPaper1stCassette[];
extern CONST UBYTE	D2W_RepRxPaper2ndCassette[];
extern CONST UBYTE	D2W_RepRxPaper3rdCassette[];
extern CONST UBYTE	D2W_ReplaceRxPaper[];
extern CONST UBYTE	D2W_NoSamePaper[];
extern CONST UBYTE	D2W_ManualCassette[];
extern CONST UBYTE	D2W_RemoveManualPaper[];
extern CONST UBYTE	D2W_CheckPaperSize[];
extern CONST UBYTE	D2W_PleaseOpenCloseTopCover[];

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
#if (0)
//#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
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
//#endif
#endif
extern CONST UBYTE	D2W_SettingRelayBox[];
extern CONST UBYTE	D2W_TooManyRelayDirect[];

/*----------------------------------*
 *	通信中
 *----------------------------------*/
extern CONST UBYTE	D2W_Called[];
extern CONST UBYTE	D2W_Transmit[];
extern CONST UBYTE	D2W_Receive[];
extern CONST UBYTE	D2W_PollingRx[];
extern CONST UBYTE	D2W_CallReservation[];

/*----------------------------------*
 *	原稿サイズ・線密度
 *----------------------------------*/
extern CONST UBYTE	D2W_DocNormal[];
extern CONST UBYTE	D2W_DocFine[];
extern CONST UBYTE	D2W_DocSFine[];
extern CONST UBYTE	D2W_DocGray[];
extern CONST UBYTE	D2W_DocHFine[];
extern CONST UBYTE	D2W_DocEFine[];

/*----------------------------------*
 *	次原稿・メモリ残量
 *----------------------------------*/
extern CONST UBYTE	D2W_NextDocument_Ari[];
extern CONST UBYTE	D2W_NextDocument_Nashi[];
extern CONST UBYTE	D2W_MemoryArea[];
#if (PRO_NOT_AUTO_RX_DISP == ENABLE)
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

/*----------------------------------*
 *	入力モード
 *----------------------------------*/
#if defined(JPN)
extern CONST UBYTE	D2W_Kana[];
#endif
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
extern CONST UBYTE	D2W_SettingPINAccessMode[];
extern CONST UBYTE	D2W_SettingRingMasta[];
extern CONST UBYTE	D2W_SettingStamp[];
extern CONST UBYTE	D2W_SettingResetDrumLife[];
extern CONST UBYTE	D2W_SettingRxAlarm[];
extern CONST UBYTE	D2W_SettingMercuryMode[];
#if (PRO_REMOTE_RX == ENABLE)
extern CONST UBYTE	D2W_SettingRemoteReceive[];
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
extern CONST UBYTE	D2W_SettingOnHookReceive[];
#endif
extern CONST UBYTE	D2W_SettingPrintSettings[];

extern CONST UBYTE	D2W_SetMessageOnOff[];
extern CONST UBYTE	D2W_SetMessage[];
extern CONST UBYTE	D2W_PrintMessageList[];

extern CONST UBYTE	D2W_SettingDepartmentProtect[];
extern CONST UBYTE	D2W_SettingDepartmentCode[];
extern CONST UBYTE	D2W_SettingDepartmentOnOff[];

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

extern CONST UBYTE	D2W_PrintSettingList[];

#if (PRO_MULTI_LINE == ENABLE) || (PRO_MULTI_TTI == ENABLE)
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

/* 優先原稿濃度 */
extern CONST UBYTE	D2W_SelectPrimaryContrast[];
extern CONST UBYTE	D2W_PrimaryContrastLight[];
extern CONST UBYTE	D2W_PrimaryContrastLittleLight[];
extern CONST UBYTE	D2W_PrimaryContrastNormal[];
extern CONST UBYTE	D2W_PrimaryContrastLittleDark[];
extern CONST UBYTE	D2W_PrimaryContrastDark[];

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

/* 済みスタンプ */
extern CONST UBYTE	D2W_StampOnOff[];
extern CONST UBYTE	D2W_SetStamp[];

/* 受信アラームセット */
extern CONST UBYTE	D2W_RxAlarm[];
extern CONST UBYTE	D2W_SetRxAlarm[];

extern CONST UBYTE	D2W_MercuryNumberSet[];

/* マーキュリーポーズ */
extern CONST UBYTE	D2W_MercuryPauseSet[];
extern CONST UBYTE	D2W_MercuryPauseTime[];

extern CONST UBYTE	D2W_SetMercury[];

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
 #if (PRO_FCODE_RELAY == ENABLE)
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
 #if (PRO_FCODE_RELAY == ENABLE)
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

/* 送信時、部門コード入力 */
extern CONST UBYTE	D2W_EnterDepartmentCode[];

/* 送信時、ダイヤル番号入力 */
extern CONST UBYTE	D2W_EnterDialNumber[];

/* 送信時、ＰＩＮ番号入力 */
extern CONST UBYTE	D2W_EnterPinNumber[];

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
extern CONST UBYTE	D2W_PaperSize_HalfLetterR[];
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
extern CONST UBYTE	D2W_SF_LifeMonitor[];
extern CONST UBYTE	D2W_SF_TestPatternPrint[];
extern CONST UBYTE	D2W_SF_StampTest[];
extern CONST UBYTE	D2W_SF_DocumentFeedOutTest[];
extern CONST UBYTE	D2W_SF_Shading[];

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
extern CONST UBYTE	D2W_SF_Sort[];
extern CONST UBYTE	D2W_SF_Broadcast[];
extern CONST UBYTE	D2W_SF_Special[];
extern CONST UBYTE	D2W_SF_Group[];
extern CONST UBYTE	D2W_SF_Speed[];
extern CONST UBYTE	D2W_SF_MemoryTx[];
extern CONST UBYTE	D2W_SF_Stop[];
extern CONST UBYTE	D2W_SF_Start[];
extern CONST UBYTE	D2W_SF_Copy[];
extern CONST UBYTE	D2W_SF_PaperSelect[];
extern CONST UBYTE	D2W_SF_Stamp[];
extern CONST UBYTE	D2W_SF_Reduction[];
extern CONST UBYTE	D2W_SF_Magnification[];
extern CONST UBYTE	D2W_SF_CopyFax[];
extern CONST UBYTE	D2W_SF_BookDocSize[];
extern CONST UBYTE	D2W_SF_CopyReset[];

/* 回線テスト */
extern CONST UBYTE	D2W_SF_PhoneTest[];
extern CONST UBYTE	D2W_SF_TonalTest[];
extern CONST UBYTE	D2W_SF_DTMF_Test[];

/* リレー */
extern CONST UBYTE	D2W_SF_RelayTest1[];
extern CONST UBYTE	D2W_SF_RelayTest2[];

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

/* ライフモニタークリア */
extern CONST UBYTE	D2W_SF_LifeMonitorClear[];

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
extern CONST UBYTE	D2W_SF_SenderSection2[];
extern CONST UBYTE	D2W_SF_SenderTelNumber[];
extern CONST UBYTE	D2W_SF_SerialNumber[];
extern CONST UBYTE	D2W_SF_Date[];
extern CONST UBYTE	D2W_SF_PrintOrderForm[];

/* メモリダンプ */
extern CONST UBYTE	D2W_SF_MemoryDump[];
extern CONST UBYTE	D2W_SF_MemoryDumpAddress[];
extern CONST UBYTE	D2W_SF_MemoryDumpLength[];

/* ＤＲＡＭクリア */
extern CONST UBYTE	D2W_SF_ClearDRAM[];

/* オプションデータ初期化 */
extern CONST UBYTE	D2W_SF_OptionDataInitial[];

/* 消耗品発注データクリア */
extern CONST UBYTE	D2W_SF_OrderDataClear[];

extern CONST UBYTE	D2W_SF_OK[];
extern CONST UBYTE	D2W_SF_NG[];

extern CONST UBYTE	D2W_WordingTail[];

#endif	/* NTT_WRD_0 */
