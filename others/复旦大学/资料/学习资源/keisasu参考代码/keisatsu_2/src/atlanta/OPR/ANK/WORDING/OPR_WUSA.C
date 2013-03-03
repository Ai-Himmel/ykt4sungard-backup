/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_WUSA.C
*	Author		: 渡辺一章
*	Date		: 1996/10/25
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 英語版オペレーションワーディング
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"

#define	CUB	 CONST UBYTE

#if (PRO_CPU == SH7043)	/* ワーディング先頭位置認識用 */
 #if (WORDING_1 == ENGLISH)
	CUB D2W_1stWordingTop[]				= "\0";
 #endif
 #if (WORDING_2 == ENGLISH)
	CUB D2W_2ndWordingTop[]				= "\0";
 #endif
 #if (WORDING_3 == ENGLISH)
	CUB D2W_3rdWordingTop[]				= "\0";
 #endif
#endif

CUB	ENG_WordingHead[]					= "\0";	/* ﾜｰﾃﾞｨﾝｸﾞｻｲｽﾞ計算用(H8の様にﾜｰﾃﾞｨﾝｸﾞを縦に並べる場合必要) */
CUB	ENG_Null[]							= "\0";

/* 待機モード */
CUB	ENG_TelReady[]						= "Tel Ready           ";
CUB	ENG_FaxReady[]						= "Fax Ready           ";
CUB	ENG_FaxTelReady[]					= "Fax/Tel Ready       ";
CUB	ENG_TelFaxReady[]					= "Tel/Fax Ready       ";
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_AnsFaxReady[]					= "TAD/Fax Ready       ";
#else
CUB	ENG_AnsFaxReady[]					= "Ans/Fax Ready       ";
#endif
CUB	ENG_DialInReady[]					= "Dial In Ready       ";	/* (JPN) */
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1997/12/26 */
CUB	ENG_ScannerTransportReady[]			= "Mirror Locked       ";	/* <- "Mirror Position     " By S.Fukui Feb.2,1998 */
#endif

/* コピーモードの表示 */
#if (PRO_COPY_FAX_MODE == ENABLE)
CUB	ENG_CopyReady[]						= "Copy Ready    Num:  ";
CUB	ENG_ManualCopyReady[]				= "Copy Tray     Num:  ";
CUB	ENG_CopyImpossibleReady[]			= "              Num:  ";
CUB	ENG_InputCopyMagnifi[]				= "Enter Reduce        ";
CUB	ENG_CopyMagnifiError[]				= "Enter 50-200%       ";
CUB	ENG_ConfirmCopyMagnifi[]			= "999% Are You Sure   ";	/* 倍率は必ず999を定義（国別の表示位置対応） */
#endif

/* コマンド登録中の表示（上段） */
CUB	ENG_EnterFaxNumber[]				= "Enter Fax Number    ";
CUB	ENG_InputGroupNumber[]				= "Enter Group No.     ";
CUB	ENG_InputSpeedDialNumber[]			= "Enter Speed-Dial No.";
CUB	ENG_PressStart[]					= "Press Start         ";
CUB	ENG_PressStartAgain[]				= "Press Start Again   ";
CUB	ENG_PressEnterKey[]					= "Press Enter Key     ";

/* コピー部数入力中の表示（上段） */
CUB	ENG_SetCopyUnits[]					= "# of pgs. to copy   ";	/* POPLAR_B以外 */

/* 選択を促す表示（点滅する表示 ) */
CUB	ENG_ProgramEnter[]					= "      Program/Enter ";
CUB	ENG_ProgramClear[]					= "      Program/Cancel";
#if (PRO_CIPHER == ENABLE)
CUB	ENG_EnterClesr[]					= "        Enter/Cancel";  /* ｾｯﾄ/ｸﾘｱ bythonda1998/07/15 */
#endif
CUB	ENG_EnterStop[]						= "         Enter/Stop ";
CUB	ENG_CopyStop[]						= "          Copy/Stop ";	/* POPLAR_B以外 */
CUB	ENG_StartStop[]						= "         Start/Stop ";  /* wording by t.honda 1997/09/20 ｽﾀｰﾄ/ｽﾄｯﾌﾟ */
CUB	ENG_SpecialCommunicationEnter[]		= "  Comm.Option/Enter ";
CUB	ENG_ReviewStop[]					= "       Review/Stop  ";  /* Confirm/Stop -> Review/Stop 1997/11/28 Y.Matsukuma */
CUB	ENG_CheckProgramEnter[]				= "Check Program/Enter ";
CUB	ENG_CheckProgramClear[]				= "Check Program/Cancel";
CUB	ENG_CheckStartStop[]				= "Check    Start/Stop ";
#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
CUB	ENG_CommunicationConfirmEnter[]		= "       Review/Enter ";/*20*//* ATLANTAでは"Comm.Cancel"ではなく"Review"を使用 */
#endif

/*----------------------------------*
 *	応用機能
 *----------------------------------*/
/* 機能選択中 */
CUB	ENG_SetDelayedTransmission[]		= "  Delayed           ";
CUB	ENG_SetSecureTransmission[]			= "  S Mail Tx         ";
CUB	ENG_SetRelayTransmission[]			= "  Relay Tx          ";
CUB	ENG_SetPolling[]					= "  Polling           ";
CUB	ENG_SetBatchTransmission[]			= "  Batch Tx          ";
CUB	ENG_SetContPolling[]				= "  Cont Polling      ";
CUB	ENG_SetFcodeTransmission[]			= "  F-Code Tx         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */
CUB	ENG_SetFcodePolling[]				= "  F-Code Polling    ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */
CUB	ENG_SetCipherTransmission[]			= "  Scrambling Tx     ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） *//* wording by t.honda 1997/09/20 ｱﾝｺﾞｳｶ ｿｳｼﾝ */

/* 各機能の詳細データ設定中（上段） */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/18 Y.Matsukuma */
CUB	ENG_DelayedTransmission[]			= "Program Stored      ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
#else
CUB	ENG_DelayedTransmission[]			= "Delayed             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
#endif
CUB	ENG_SecureTransmission[]			= "S Mail Tx           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	ENG_RelayTransmission[]				= "Relay Tx            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	ENG_PollingCommunication[]			= "Polling             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	ENG_BatchTransmission[]				= "Batch Tx            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	ENG_ContinuousPolling[]				= "Cont Polling        ";
CUB	ENG_InputSubAddressNumber[]			= "Enter Sub-Address   ";
CUB	ENG_InputPasswordNumber[]			= "Enter Password      ";  /* <- Enter Passcode :Modified By S.Fukui Dec.5,1997 */
CUB	ENG_SelectCipherExtensionKey[]		= "Key Extension  :\0   "; /* wording by t.honda 1997/09/20 ﾀﾞﾌﾞﾙｶﾞｰﾄﾞ */

/* 各機能の詳細データ設定中（下段） */
CUB	ENG_EnterDelayedTxTime[]			= "Enter Time: \0       ";
CUB	ENG_InputMailBoxNumber[]			= "S Mail No.        \0 ";
CUB	ENG_RelayTxGroupNumber[]			= "Group No.     \0     ";
CUB	ENG_InputFileNumber[]				= "File No.    \0       ";
CUB	ENG_BatchBoxIndexNumber[]			= "Box:      File:     ";
CUB	ENG_EnterContPollStartTime[]		= "Start Time:   \0     "; /* 1996/10/23 Y.Matsukum */
CUB	ENG_EnterContPollEndTime[]			= "End Time:     \0     "; /* 1996/10/23 Y.Matsukum */

/*----------------------------------*
 *	濃度設定
 *----------------------------------*/
CUB	ENG_SetPaperContrast[]				= "Set Contrast        ";
CUB	ENG_ContrastLightDark[]				= " Light         Dark ";

/*----------------------------------*
 *	機器エラー
 *----------------------------------*/
/* カバー */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* O.Oshima 2003/10/02 */
CUB	ENG_PleaseCloseScannerCover[]		= "Close Top Cover     ";
#else
CUB	ENG_PleaseCloseScannerCover[]		= "Close Scanner Cover ";
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	ENG_PleaseClose1stJamCover[]		= "Close 1st Side Cover";
CUB	ENG_PleaseClose2ndJamCover[]		= "Close 2nd Side Cover";
CUB	ENG_PleaseClose3rdJamCover[]		= "Close 3rd Side Cover";
CUB	ENG_PleaseOpen1stJamCover[]			= "Open 1st Side Cover ";  /* wording by t.honda 1997/09/20 ｻｲﾄﾞｶﾊﾞｰ1 ｦ ｱｹﾃ */
CUB	ENG_PleaseOpen2ndJamCover[]			= "Open 2nd Side Cover ";  /* wording by t.honda 1997/09/20 ｻｲﾄﾞｶﾊﾞｰ2 ｦ ｱｹﾃ */
CUB	ENG_PleaseOpen3rdJamCover[]			= "Open 3rd Side Cover ";  /* wording by t.honda 1997/09/20 ｻｲﾄﾞｶﾊﾞｰ3 ｦ ｱｹﾃ */
CUB	ENG_PleaseOpenTopCover[]			= "Open Top Cover      ";  /* wording by t.honda 1997/09/20 ﾄｯﾌﾟｶﾊﾞｰ ｦ ｱｹﾃ */
 #if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1998/01/28 */
CUB	ENG_PleaseOpenPrinterCover[]		= "Open Printer Cover  ";	/* 2000/01/19 Y.Murata */
 #endif
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* O.Oshima 2003/10/02 */
CUB	ENG_PleaseOpenCloseScanCover[]		= "Open&Close TopCover ";
 #else
CUB	ENG_PleaseOpenCloseScanCover[]		= "Open&Close ScanCover";
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
CUB	ENG_PleaseClosePrinterCover[]		= "Close Printer Cover ";	/* 2000/01/19 Y.Murata */
#endif
#if (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	ENG_ScannerFeedErrorLow[]			= "Reset Document      ";
#endif

/* カセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	ENG_PleaseCloseLowerCassette[]		= "Close Cassette      ";	/* 要変更 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	ENG_PleaseClose1stCassette[]		= "Close 1st Cassette  ";
CUB	ENG_PleaseClose2ndCassette[]		= "Close 2nd Cassette  ";
CUB	ENG_PleaseClose3rdCassette[]		= "Close 3rd Cassette  ";
#endif

/* 記録紙 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)
CUB	ENG_ReplaceRxPaper[]				= "Please Supply Paper ";
CUB	ENG_NoSamePaper[]					= "Please Supply Paper ";	/* 日本以外は、???_ReplaceRxPaperと同じです by K.Watanabe 1998/02/23 */
#endif

#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Modify by SMuratec 夏 2004/8/26 */
CUB	ENG_ReplaceRxPaper[]				= "Check Rx Paper      ";
CUB	ENG_NoSamePaper[]					= "Please Supply Paper ";	/* 日本以外は、???_ReplaceRxPaperと同じです by K.Watanabe 1998/02/23 */
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	ENG_ReplaceRxPaper[]				= "Check Rx Paper      ";
CUB	ENG_ReplaceUpperRxPaper[]			= "Check Tray Paper    ";
CUB	ENG_ReplaceLowerRxPaper[]			= "Check Cassette Paper";
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
CUB	ENG_Cassette1[]						= "1st Cassette        ";
CUB	ENG_Cassette2[]						= "2nd Cassette        ";
CUB	ENG_Cassette3[]						= "3rd Cassette        ";
CUB	ENG_ManualCassette[]				= "Tray:\0  ";
#endif
CUB	ENG_RemoveManualPaper[]				= "Remove Tray Paper   ";
CUB	ENG_CheckPaperSize[]				= "Check Rx Paper Size ";  /* wording by t.honda 1997/09/20 ｷﾛｸｼｻｲｽﾞ ｦ ｶｸﾆﾝｼﾃ*/
CUB	ENG_PleaseOpenCloseTopCover[]		= "Open&Close Top Cover";  /* wording by t.honda 1997/09/20 ﾄｯﾌﾟｶﾊﾞｰ ｦ ｶｲﾍｲｸﾀﾞｻｲ*/
#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1998/01/28 */
CUB	ENG_PleaseOpenClosePrinterCover[]	= "Open&Close Prn.Cover";	/* 2000/01/19 Y.Murata */
#endif

/* プリンター */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ジャム時の表示内容を変更します。By H.Fujimura 1999/03/09 */
CUB	ENG_PleaseRemovePaper[]				= "Check Rx Paper      ";  /* 変更するかも by honda 1997/10/01 */
#else
CUB	ENG_PleaseRemovePaper[]				= "Please Remove Paper ";  /* 変更するかも by honda 1997/10/01 */
#endif
CUB	ENG_PleaseSupplyToner[]				= "Please Supply Toner ";
CUB	ENG_PleaseReplaceToner[]			= "Please Replace Toner";  /* modified by honda 1997/10/01  */
CUB	ENG_PleaseCallService[]				= "Please Call Service ";
CUB	ENG_PaperSizeError[]				= "Check Paper Size    ";	/* ANZUのみ */

CUB	ENG_CheckDrumLife[]					= "Drum Near End       ";  /* modified by honda 1997/10/01 Please Prepare Drum */
CUB	ENG_ReplaceDrum[]					= "Please Replace Drum ";
CUB	ENG_CheckDrum[]						= "No Drum             ";
CUB	ENG_CheckTonerLevel[]				= "Toner Low           ";
CUB	ENG_NoToner[]						= "No Toner Cartridge  ";

/* スキャナ */
CUB	ENG_CallForService[]				= "Call For Service    ";
CUB	ENG_CheckDocument[]					= "Check # Of Pages    ";
CUB	ENG_MirrorCarrigeError[]			= "Mirror Carriage Err ";

/* ジャムリカバー */
CUB	ENG_DocumentJam[]					= "Document Jam        ";  /* modified by honda 1997/10/01 Please Remove Paper */
CUB	ENG_InterruptDocScan[]				= "Stop Scanning       ";
CUB	ENG_NextScanEnterClear[]			= "ContStor Enter/Cancl";  /* ContStor <- Continue Storing */
CUB	ENG_ResetPageNumber[]				= "p  . Reset Document ";  /* JPNとはﾍﾟｰｼﾞ位置が違う事に注意 By S.Fukui Oct.6,1997 */ /* 例) p12. Reset Document */
CUB	ENG_ResetDocumentSet[]				= "Reset Document      ";
CUB	ENG_PleasePressStartKey[]			= "Press Start Key     ";
CUB	ENG_PleasePressEnterKey[]			= "Press Enter Key     ";
CUB	ENG_PleasePressCopyKey[]			= "Press Copy Key      ";	/* POPLAR_B以外 */

/* 通信 */
CUB	ENG_CommunicationError[]			= "Communication Error ";
CUB	ENG_NoStoredDialInNumber[]			= "No Entered Dial In  ";	/* (JPN) */

/* ハングアップ */
CUB	ENG_HungUpPhone[]					= "Hang Up Phone       ";

/* 完了表示 */
CUB	ENG_TransmitComplete[]				= " **   Complete   ** ";
CUB	ENG_ReceiveComplete[]				= " **   Complete   ** ";
CUB	ENG_PrintComplete[]					= " **   Complete   ** ";
CUB	ENG_StoreComplete[]					= " **   Complete   ** ";
CUB	ENG_SetComplete[]					= " **   Complete   ** ";
CUB	ENG_ClearComplete[] 				= " **   Complete   ** ";

/* リモート診断中の表示 1996/01/25 Eguchi */
CUB	ENG_RemoteDiagMode[]				= "Service Mode        ";

/* 操作エラー */
/* 絶対に途中に追加してはいかん */
CUB	ENG_InvalidNumber[]					= "Invalid Number      ";	/* INVALID_NUMBER_ERROR				*/
CUB	ENG_TooManyDigitsin[]				= "Too Many Characters ";	/* TOO_MANY_DIGITS_ERROR			*/
CUB	ENG_PleaseInput1_99[]				= "Enter No. (1-99)    ";	/* INVALID_COPY_NUMBER_ERROR		*//* POPLAR_B以外 */
CUB	ENG_NoNumberStored[]				= "No Number Stored    ";	/* NO_STORED_NUMBER_ERROR			*//* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	ENG_PleaseInput0_32[]				= "Enter No. (0-32)    ";	/* INVALID_GROUP_NUMBER_ERROR		*/
CUB	ENG_TooManyLocations[]				= "Too Many Locations  ";	/* TOO_MANY_LOCATION_ERROR			*/
CUB	ENG_InsertDocument[]				= "Insert Document     ";	/* INSERT_DOCUMENT_ERROR			*/
CUB	ENG_FeederInUse[]					= "Feeder In Use       ";	/* FEEDER_IN_USE_ERROR				*/
CUB	ENG_ScannerInUse[]					= "Scanner In Use      ";	/* SCANNER_USE_ERROR				*/
CUB	ENG_PollingInUse[]					= "Polling In Use      ";	/* ALREADY_POLLING_STORED_ERROR		*/
CUB	ENG_NoDocumentStored[]				= "No Document Stored  ";	/* NO_STORED_DOCUMENT_ERROR			*/
CUB	ENG_CommandFull[]					= "All Commands In Use ";	/* COMMAND_FULL_ERROR				*/
CUB	ENG_NoCommand[]						= "No Command          ";	/* NO_COMMAND_ERROR					*/
CUB	ENG_NoCommandDocument[]				= "No Document Stored  ";	/* NO_COMMAND_DOCUMENT_ERROR		*/
CUB	ENG_NoCommandResult[]				= "No Report           ";	/* NO_COMMAND_RESULT_ERROR			*/
CUB	ENG_SecureDocExist[]				= "Document Stored     ";	/* SECURE_DOC_EXIST_ERROR			*/
CUB	ENG_PrinterInUse[]					= "Printer In Use      ";	/* PRINTER_IN_USE_ERROR				*/
CUB	ENG_InvalidIDCode[]					= "Invalid I.D. Code   ";	/* INVALID_ID_CODE_ERROR			*/
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_InvalidProtectPasscode[]		= "Invalid Password    ";	/* INVALID_PROTECT_PASSCODE_ERROR	*/
CUB	ENG_NoProtectPasscode[]				= "No Password         ";	/* NO_PROTECT_PASSCODE_ERROR		*/
#else
CUB	ENG_InvalidProtectPasscode[]		= "Invalid Passcode    ";	/* INVALID_PROTECT_PASSCODE_ERROR	*/
CUB	ENG_NoProtectPasscode[]				= "No Passcode         ";	/* NO_PROTECT_PASSCODE_ERROR		*/
#endif
CUB	ENG_InputRangeOver[]				= "Invalid Number      ";	/* INPUT_RANGE_OVER_ERROR			*/
CUB	ENG_BatchDocFull[]					= "                    ";	/* BATCH_DOCUMENT_FULL_ERROR		*/
CUB	ENG_LineBusy[]						= "Line Busy           ";	/* LINE_BUSY_ERROR					*/
CUB	ENG_ProtectedDocStored[]			= "Protect Doc. Stored ";	/* PROTECT_DOCUMENT_STORED_ERROR	*/
CUB	ENG_NoProtectDocStored[]			= "No Document Stored  ";	/* NO_PROTECT_DOCUMENT_ERROR		*/
CUB	ENG_NoPinNumber[]					= "No PIN Number       ";	/* NO_PIN_NUMBER_ERROR				*/
CUB	ENG_NoDepartmentCode[]				= "No Dept. Code       ";	/* NO_DEPARTMENTCODE_ERROR			*/
CUB	ENG_BatchDocStored[]				= "Document Stored     ";	/* BATCH_DOCUMENT_STORED_ERROR		*/
CUB	ENG_ResetDocument[]					= "Reset Document      ";	/* RESET_DOCUMENT_ERROR				*/
CUB	ENG_PleaseCloseBookCover[]			= "Close Book Cover    ";	/* BOOK_COVER_OPEN_ERROR			*//* POPLAR_Bのみ */
CUB	ENG_PleaseWaitAMinute[]				= "Please Wait         ";	/* PRINTER_CLEANING_ERROR			*/
CUB	ENG_NotStoredDocument[]				= "Document Full       ";	/* NOT_STORED_DOCUMENT_ERROR		*//* (PRO_F_CODE == ENABLE) */
CUB	ENG_BoxInUse[]						= "Box In Use          ";	/* BOX_IN_USE_ERROR					*//* (PRO_F_CODE == ENABLE) */
CUB	ENG_TooManyDirectDial[]				= "Too Many Locations  ";	/* TOO_MANY_DIRECT_DIAL_ERROR		*/
CUB	ENG_SettingSecureBox[]				= "In Secure Box       ";	/* SETTING_SECURE_BOX_ERROR			*//* (PRO_F_CODE == ENABLE) */
CUB	ENG_BookSizeNoSet[]					= "Enter Scan Size     ";	/* BOOK_SIZE_NO_SET_ERROR			*//* POPLAR_Bのみ */
CUB	ENG_NotCompleteStoredDoc[]			= "Store Not Completed ";	/* NOT_COMPLETE_STORED_ERROR		*//* POPLAR_Bのみ */
CUB	ENG_NotCompleteCopy[]				= "Copy Not Completed  ";	/* NOT_COMPLETE_COPY_ERROR			*//* POPLAR_Bのみ */
CUB	ENG_ScanPreparing[]					= "Scanner Adjusting   ";	/* SCAN_PREPARING_ERROR				*//* POPLAR_Bのみ */
CUB	ENG_CopyProtect[]					= "Copy Off            ";	/* COPY_PROTECT_ERROR				*/
CUB	ENG_NotScanDocSize[]				= "Not Acceptable Size ";	/* NOT_SCAN_DOC_SIZE_ERROR			*//* (PRO_CIPHER == ENABLE) */
CUB	ENG_ShortFigure[]					= "4 Letters or More   ";	/* SHORT_FIGURE_ERROR				*//* (PRO_CIPHER == ENABLE) */
CUB	ENG_AlreadyStored[]					= "Already Stored      ";	/* ALREADY_NUMBER_STORED_ERROR		*//* (FRA) */
CUB	ENG_NotEntry[]						= "No Key Stored       ";	/* NOT_ENTRY_ERROR					*//* (PRO_CIPHER == ENABLE) */
CUB	ENG_NoScanCipherMode[]				= "No Setting S Fine   ";	/* NO_SCAN_CIPHER_MODE_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	ENG_Ciphering[]						= "Scrambler In Use    ";	/* CIPHERING_ERROR					*//* (PRO_CIPHER == ENABLE) */
CUB	ENG_Deciphering[]					= "Descrambler In Use  ";	/* DECIPHERING_ERROR				*//* (PRO_CIPHER == ENABLE) */
CUB	ENG_UseDefaultCipherKey[]			= "In Use as Default   ";	/* USE_DEFAULT_CIPHER_KEY_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	ENG_UseProgramOneTouch[]			= "In Use in P OneTouch";	/* USE_PROGRAM_ONETOUCH_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	ENG_PleaseCloseTopCover[]			= "Close Top Cover     ";	/* TOP_COVER_OPEN_ERROR				*/
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1999/01/07 */
//#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#endif
CUB	ENG_DialNumberStoredError[]			= "FAX Number Stored   ";	/* DIAL_NUMBER_STORED_ERROR			*/
CUB	ENG_ProgramStoredError[]			= "Program Stored      ";	/* PROGRAM_STORED_ERROR				*/
CUB	ENG_MailAddressStoredError[]		= "Mail Address Stored ";	/* MAIL_ADDRESS_STORED_ERROR		*/
CUB	ENG_MailGroupStoredError[]			= "Mail Group Stored   ";	/* MAIL_GROUP_STORED_ERROR			*/
CUB	ENG_UserDataFullError[]				= "All User Data Stored";	/* USER_DATA_FULL_ENTRY_ERROR		*/
CUB	ENG_NoRS232C_Error[]				= "No RS-232C          ";	/* NO_RS232C_PCB_ERROR				*/
CUB	ENG_TooManyDirectAdrError[]			= "Too Many Address    ";	/* TOO_MANY_DIRECT_ADDRESS_ERROR	*/
CUB	ENG_NoUserDataError[]				= "No User Data        ";	/* NO_USER_DATA_ERROR				*/
CUB	ENG_InvalidAddressError[]			= "Invalid Address     ";	/* INVALID_ADDRESS_ERROR			*/
CUB	ENG_NoTCPIP_BoardError[]			= "No Optional Board   ";	/* NO_TCPIP_BOARD_ERROR				*/
CUB	ENG_MemoryFullError[]				= "Memory Full         ";	/* MEMORY_FULL_ERROR				*/
CUB	ENG_AlreadyUsedError[]				= "One-Touch In Use    ";	/* ALREADY_USED_ERROR				*/
CUB	ENG_NoEntryData[]					= "No Entry Data       ";	/* NO_ENTRY_DATA					*/
CUB	ENG_NoStoredAddress[]				= "No Address Stored   ";	/* NO_STORED_ADDRESS_ERROR			*/
CUB	ENG_InvalidPassword[]				= "Invalid Password    ";	/* INVALID_PASSWORD_ERROR			*/
CUB	ENG_ExecuteCommand[]				= "Executing Command   ";	/* EXECUTE_COMMAND_ERROR			*/
CUB	ENG_NoDeviceError[]					= "No Device           ";	/* NO_DEVICE_ERROR					*/
#if (0)
//CUB ENG_NoAccessPointTelNumber[]		= "No AP Tel Number    ";	/* NO_ACCESS_POINT_DATA_ERROR		*/
#endif
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1999/01/07 */
//#endif
#endif
CUB	ENG_SettingRelayBox[]				= "Relay Box           ";	/* SETTING_RELAY_BOX_ERROR			*//* By H.Fujimura 1999/01/07 */
CUB	ENG_TooManyRelayDirect[]			= "1 Locations or Less ";	/* TOO_MANY_RELAY_DIRECT_ERROR		*//* By H.Fujimura 1999/01/07 */

/*----------------------------------*
 *	通信中
 *----------------------------------*/
CUB	ENG_Transmit[]						= "Transmit            ";
CUB	ENG_Receive[]						= "Receive   ";
CUB	ENG_Called[]						= " ** Being Called ** ";
CUB	ENG_CallReservation[]				= "** Call Requested **";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	ENG_CallReservation_S[]				= "** Call Requested **";
#endif

/*----------------------------------*
 *	原稿サイズ・線密度
 *----------------------------------*/
CUB	ENG_DocNormal[]						= "Normal    \0         ";
CUB	ENG_DocFine[]						= "Fine      \0         ";
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_DocSFine[]						= "Ex Fine   \0         ";
#else
CUB	ENG_DocSFine[]						= "S Fine    \0         ";
#endif
#if (PRO_PITNEYBOWES == ENABLE) /* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
CUB	ENG_DocGray[]						= "PHOTO     \0         "; 
CUB	ENG_DocHGray[]						= "H PHOTO   \0         "; 
#else
CUB	ENG_DocGray[]						= "Gray      \0         ";
#endif
CUB	ENG_DocHFine[]						= "H Fine    \0         "; /*評価用に追加1996/06/19Eguchi*/
CUB	ENG_DocEFine[]						= "E Fine    \0         "; /*評価用に追加1996/06/19Eguchi*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	ENG_DocFine_S[]						= "Fine      \0         ";
CUB	ENG_DocSFine_S[]					= "S Fine    \0         ";
#endif

/*----------------------------------*
 *	次原稿・メモリ残量
 *----------------------------------*/
CUB	ENG_NextDocument[]					= "NextDoc";
CUB	ENG_MemoryAreaShort[]				= "             Mem   %";

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ＬＣＤ表示変更(0x7E = ->) By O.Kimoto 1999/02/25 */
 #if defined(TWN)
CUB	ENG_MemoryAreaLong[]				= "          Memory   %";
 #else
CUB	ENG_MemoryAreaLong[]				= "             Mem   %";
 #endif
#else
CUB	ENG_MemoryAreaLong[]				= "          Memory   %";
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/07 */
CUB	ENG_MemoryAreaLong2[]				= "   *****  Memory   %";
CUB	ENG_MemoryAreaShort2[]				= "             Mem   %";	/* ＬＣＤ表示変更(0x7E = ->) By O.Kimoto 1999/02/25 */
#endif

#if (PRO_NOT_AUTO_RX_DISP == ENABLE)	/* by K.Watanabe 1998/06/08 */
CUB	ENG_MemoryFull[]					= "Not Receiving       ";
CUB	ENG_NotAutoReceive[]				= "as Memory Full      ";
#endif

/*----------------------------------*
 *	月
 *----------------------------------*/
CUB	ENG_January[]						= "Jan";
CUB	ENG_February[]						= "Feb";
CUB	ENG_March[]							= "Mar";
CUB	ENG_April[]							= "Apr";
CUB	ENG_May[]							= "May";
CUB	ENG_June[]							= "Jun";
CUB	ENG_July[]							= "Jul";
CUB	ENG_August[]						= "Aug";
CUB	ENG_September[]						= "Sep";
CUB	ENG_October[]						= "Oct";
CUB	ENG_November[]						= "Nov";
CUB	ENG_December[]						= "Dec";

/*----------------------------------*
 *	予約表示
 *----------------------------------*/
CUB	ENG_Reserving[]						= "   ** Reserved **   ";
CUB	ENG_AutoRedial[]					= " ** Auto Redial **  ";

/*----------------------------------*
 *	原稿セット時
 *----------------------------------*/
CUB	ENG_TransmitOrCopyReady[]			= "Document Ready      ";
CUB	ENG_TransmitReady[]					= "Document Ready      ";	/* 日本以外は、???_TransmitOrCopyReadyと同じです */

#if (PRO_PC_PRINT == ENABLE)
/*----------------------------------*
 *	ＰＣプリント
 *----------------------------------*/
CUB	ENG_PC_Print[]						= "PC                  ";
CUB	ENG_PC_Receiving[]					= "  ** Receiving **   ";
CUB	ENG_PC_MemoryOverFlow[]				= "PC Memory Over Flow ";
#endif

/*----------------------------------*
 *	プリント中
 *----------------------------------*/
CUB	ENG_Printing[]						= "   ** Printing **   ";

/*----------------------------------*
 *	ウォームアップ
 *----------------------------------*/
CUB	ENG_Wait[]							= " ** Please Wait **  ";

/*----------------------------------*
 *	イメージプリント
 *----------------------------------*/
CUB	ENG_PollingDocument[]				= "Polling Doc         ";
CUB	ENG_SecureMailDocument[]			= "Print SecureMail    ";
CUB	ENG_MemoryRxDocument[]				= "                    ";
CUB	ENG_CommandDocument[]				= "Print Stored Doc.   ";
CUB	ENG_BatchTxDocument[]				= "Print Batch Doc.    ";

/*----------------------------------*
 *	リストプリント
 *----------------------------------*/
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 1998/10/20 */
CUB	ENG_PrintJournal[]					= "Print Report        ";
#else
CUB	ENG_PrintJournal[]					= "Print Journal       ";
#endif
#if (PRO_JOURNAL_VER_UP == ENABLE)	/* by K.Watanabe 2004/10/28 */
CUB	ENG_PrintJournalTx[]				= "Print Tx Journal    ";
CUB	ENG_PrintJournalRx[]				= "Print Rx Journal    ";
CUB	ENG_PrintJournalTxRx[]				= "Print TxRx Journal  ";
#endif
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
CUB	ENG_PrintAllJournal[]				= "Print All Journals  ";
CUB	ENG_PrintDailyReport[]				= "Print Day Journal   ";
#endif
CUB	ENG_TCR[]							= "TCR                 ";
CUB	ENG_PrintSpeedDial[]				= "Print Speed-Dial    ";
CUB	ENG_PrintOneTouch[]					= "Print One-Touch     ";
CUB	ENG_PrintProgramOneTouch[]			= "Print P One-Touch   ";
CUB	ENG_GroupList[]						= "Group List          ";
CUB	ENG_SF_ProgramListPrint[]			= "Program List        ";
CUB	ENG_SetPrintSettings[]				= "Print Settings      ";
CUB	ENG_PrintCommands[]					= "Print Commands      ";
CUB	ENG_PrintSecureMailList[]			= "Print S Mail List   ";
CUB	ENG_MessageList[]					= "Print Cover Message ";
CUB	ENG_PrintSecureMail[]				= "Print SecureMail    ";
CUB	ENG_SF_T30MonitorPrint[]			= "T30 Monitor         ";
CUB	ENG_SF_FactoryFunctionList[]		= "Function List       ";
CUB	ENG_SF_MemorySwitchMode[]			= "Memory Switch       ";
CUB	ENG_CheckMessage[]					= "Check Message       ";
CUB	ENG_SF_OnLineMonitor[]				= "On Line Monitor     ";
CUB	ENG_SF_OrderForm[]					= "Order Sheet         ";		/* 暫定 by S.Fukui Oct.22,1997 */

/*----------------------------------*
 *	パスコード
 *----------------------------------*/
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_InputPasscode[]					= "Password       :\0   ";
CUB	ENG_EnterProtectPasscode[]			= "Enter Password :\0   ";
CUB	ENG_OldProtectPasscode[]			= "Old Password   :\0   ";
CUB	ENG_NewProtectPasscode[]			= "New Password   :\0   ";
#else
CUB	ENG_InputPasscode[]					= "Passcode       :\0   ";
CUB	ENG_EnterProtectPasscode[]			= "Enter Passcode :\0   ";
CUB	ENG_OldProtectPasscode[]			= "Old Passcode   :\0   ";
CUB	ENG_NewProtectPasscode[]			= "New Passcode   :\0   ";
#endif
CUB	ENG_EnterIDCode[]					= "Enter I.D. Code:\0   ";
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
 #if (PRO_F_CODE == ENABLE)
CUB	ENG_EnterFcodePasscode[]			= "F-Code Password:\0   ";
 #endif
 #if (PRO_CIPHER == ENABLE)
CUB	ENG_CipherPassCode[]				= "Password       :\0   ";
CUB	ENG_OldCipherPassCode[]				= "Old Password   :\0   ";
CUB	ENG_NewCipherPassCode[]				= "New Password   :\0   ";
 #endif
#else
 #if (PRO_F_CODE == ENABLE)
  #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Change Passcode to I.D Code By O.Kimoto 1999/01/28 */

#if (0)
** /* ﾜｰﾃﾞｨﾝｸﾞ変更 By O.Kimoto 1999/02/08 */
** CUB	ENG_EnterFcodePasscode[]			= "F-Code I.D Code:\0   ";  /* wording by t.honda 1997/09/20 ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ */
#else
CUB	ENG_EnterFcodePasscode[]			= "Enter I.D. Code:\0   ";  /* wording by t.honda 1997/09/20 ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ */
#endif

  #else
CUB	ENG_EnterFcodePasscode[]			= "F-Code Passcode:\0   ";  /* wording by t.honda 1997/09/20 ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ */
  #endif
 #endif
 #if (PRO_CIPHER == ENABLE)
CUB	ENG_CipherPassCode[]				= "Passcode       :\0   ";  /* wording by t.honda 1997/09/20 ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ */
CUB	ENG_OldCipherPassCode[]				= "Old Passcode   :\0   ";  /* wording by t.honda 1997/09/20 ｹﾞﾝｻﾞｲ ﾉ ﾊﾞﾝｺﾞｳ */
CUB	ENG_NewCipherPassCode[]				= "New Passcode   :\0   ";  /* wording by t.honda 1997/09/20 ｱﾀﾗｼｲ ﾊﾞﾝｺﾞｳ */
 #endif
#endif

/*----------------------------------*
 *	入力モード
 *----------------------------------*/
#if defined(JPN)
CUB	ENG_Kana[]							= ":Kana    ";
 #if (PRO_JIS_CODE == ENABLE)
CUB	ENG_KanjiCode[]						= ":Kanji   ";		/* 2000/1/19 Y.Murata */
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
CUB	ENG_Alphameric[]					= ":Alphame."; /* ';' to ':' Modified by SMuratec L.Z.W 2003/11/28 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	ENG_Upper[]							= ":Upper   ";
CUB	ENG_Lower[]							= ":Lower   ";
CUB	ENG_Symbol[]						= ":Symbols ";	/* ANZUのみ */
CUB	ENG_Code[]							= ":Code    ";
CUB	ENG_ModeNone[]						= ":        ";

/*----------------------------------*
 *	電話帳
 *----------------------------------*/
CUB	ENG_TelephoneBookMode[]				= "Telephone Index  [ ]";

/*----------------------------------*
 *	電話
 *----------------------------------*/
CUB	ENG_OnHold[]						= "  **  On Hold  **   ";	/* POPLAR_B以外 */
CUB	ENG_TelephoneMode[]					= "  **  Tel Mode  **  ";
CUB	ENG_ChangeVolume[]					= "  Volume:           ";

/*----------------------------------*
 *	メモリーオーバーオペレーション
 *----------------------------------*/
CUB	ENG_MemoryOverFlow[]				= "Memory Over Flow    ";
CUB	ENG_MemoryOverStartClear[]			= "Start Or Cancel     ";
CUB	ENG_MemoryOverEnterClear[]			= "Enter Or Cancel     ";  /* wording by t.honda 1997/09/20 ﾒﾓﾘ ﾌﾞﾝﾉﾐ   ｾｯﾄ/ｸﾘｱ */
CUB	ENG_MemoryOverCopyClear[]			= "Copy Or Cancel      ";	/* POPLAR_B以外 */

/*----------------------------------*
 *	ファンクション関係
 *----------------------------------*/
/* 機能選択状態 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 全機種共通の変更でないのに条件が入っていなかったので条件追加 by K.Watanabe 2004/10/22 */
CUB	ENG_OneTouchDialMode[]				= "    One-Touch Dial  ";
CUB	ENG_SpeedDialMode[]					= "    Speed Dial      ";
CUB	ENG_ProgramOneTouchMode[]			= "    P One-Touch     ";
CUB	ENG_PollingMode[]					= "    Polling         ";
CUB	ENG_SecureMailMode[]				= "    SecureMail      ";
CUB	ENG_DelayedCommandsMode[]			= "    Delayed Commands";
CUB	ENG_SetReportMode[]					= "    Report          ";
CUB	ENG_PrintGroupMode[]				= "    Print Group List";
CUB	ENG_UserInstallMode[]				= "    User Install    ";
CUB	ENG_UserSettingsMode[]				= "    User Settings   ";
CUB	ENG_MessageMode[]					= "    Cover Page      ";
CUB	ENG_SetNumberOfPagesMode[]			= "    Set # Of Pages  ";
CUB	ENG_SetDepartmentMode[]				= "    Department Code ";
CUB	ENG_SetBatchTxMode[]				= "    Batch Tx        ";
CUB	ENG_SecurityReceiveMode[]			= "    Security Rx     ";
CUB	ENG_FcodeBoxMode[]					= "    F-Code Box      ";	/* (PRO_F_CODE == ENABLE) */
#else
CUB	ENG_OneTouchDialMode[]				= "  One-Touch Dial    ";
CUB	ENG_SpeedDialMode[]					= "  Speed Dial        ";
CUB	ENG_ProgramOneTouchMode[]			= "  P One-Touch       ";
CUB	ENG_PollingMode[]					= "  Polling           ";
CUB	ENG_SecureMailMode[]				= "  SecureMail        ";
CUB	ENG_DelayedCommandsMode[]			= "  Delayed Commands  ";
CUB	ENG_SetReportMode[]					= "  Report            ";
CUB	ENG_PrintGroupMode[]				= "  Print Group List  ";
CUB	ENG_UserInstallMode[]				= "  User Install      ";
CUB	ENG_UserSettingsMode[]				= "  User Settings     ";
CUB	ENG_MessageMode[]					= "  Cover Page        ";
CUB	ENG_SetNumberOfPagesMode[]			= "  Set # Of Pages    ";
CUB	ENG_SetDepartmentMode[]				= "  Department Code   ";
CUB	ENG_SetBatchTxMode[]				= "  Batch Tx          ";
CUB	ENG_SecurityReceiveMode[]			= "  Security Rx       ";
CUB	ENG_FcodeBoxMode[]					= "  F-Code Box        ";	/* (PRO_F_CODE == ENABLE) */
#endif	/* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	ENG_ResetPrinterBoardMode[]			= "  Reset Printer Opt.";	/* (PRO_PC_PRINT == ENABLE) */
CUB	ENG_SetClass1Mode[]					= "  PC-FAX            ";	/* (PRO_CLASS1 == ENABLE) */
CUB	ENG_SetCipherMode[]					= "  Set Scrambling    ";	/* (PRO_CIPHER == ENABLE) */
CUB	ENG_PrintDecipherDocMode[]			= "  Print Descrambled ";	/* (PRO_CIPHER == ENABLE) */

CUB	ENG_EnterOneTouchMode[]				= "   Enter One-Touch  ";
CUB	ENG_EraseOneTouchMode[]				= "   Erase One-Touch  ";
CUB	ENG_PrintOneTouchMode[]				= "   Print One-Touch  ";

CUB	ENG_EnterSpeedDialMode[]			= "   Enter Speed-Dial ";
CUB	ENG_EraseSpeedDialMode[]			= "   Erase Speed-Dial ";
CUB	ENG_PrintSpeedDialMode[]			= "   Print Speed-Dial ";

CUB	ENG_EnterProgramOneTouchMode[]		= "   Enter P One-Touch";
CUB	ENG_EraseProgramOneTouchMode[]		= "   Erase P One-Touch";
CUB	ENG_PrintProgramOneTouchMode[]		= "   Print P One-Touch";

CUB	ENG_StorePollingDocumentMode[]		= "   Store Polling Doc";
CUB	ENG_ErasePollingDocumentMode[]		= "   Erase Polling Doc";
CUB	ENG_PrintPollingDocumentMode[]		= "   Print Polling Doc";

CUB	ENG_SetSecureMailBoxMode[]			= "   Set S Mail Box   ";
CUB	ENG_PrintSecureMailListMode[]		= "   Print S Mail List";
CUB	ENG_PrintSecureMailMode[]			= "   Print SecureMail ";
CUB	ENG_SecureMailHoldTimeMode[]		= "   S Mail Hold Time ";

CUB	ENG_PrintCommandsMode[]				= "   Print Commands   ";
CUB	ENG_PrintStoredDocumentMode[]		= "   Print Stored Doc.";

#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_JournalOnOffMode[]				= "   Report On/Off    ";
CUB	ENG_PrintJournalMode[]				= "   Print Report     ";
#else
CUB	ENG_JournalOnOffMode[]				= "   Journal On/Off   ";
 #if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/22 */
CUB	ENG_PrintJournalMode[]				= "   Print AllJournals";
 #else
CUB	ENG_PrintJournalMode[]				= "   Print Journal    ";
 #endif
#endif
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	ENG_PrintDailyReportMode[]			= "   Print Day Journal";
#endif
CUB	ENG_SettingCommunicationResult[]	= "   Set Report Type  ";

CUB	ENG_SettingScanParameters[]			= "    Scan Parameters ";
CUB	ENG_SettingPrintParameters[]		= "    Print Parameters";
CUB	ENG_SettingCopyParameters[]			= "    Copy Parameters ";	/* POPLAR_B以外 */
CUB	ENG_SettingPaperSize[]				= "    Set Paper Size  ";	/* ANZUのみ */
CUB	ENG_SettingCopyProtect[]			= "    Copy Protect    ";  /* wording by t.honda 1997/09/20 ｺﾋﾟｰｷﾝｼ */
CUB	ENG_SettingDialingPause[]			= "   Set Dialing Pause";
CUB	ENG_SettingNumberOfRings[]			= "    Set # Of Rings  ";
CUB	ENG_SettingRedial[]					= "    Set Redial      ";
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/23 Y.Matsukuma */
CUB	ENG_SettingECMMode[]				= "    Cassette Protect";
#else
CUB	ENG_SettingECMMode[]				= "    Set ECM Mode    ";
#endif
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_SettingPasscode[]				= "    Set Password    ";
#else
CUB	ENG_SettingPasscode[]				= "    Set Passcode    ";
#endif
CUB	ENG_SettingClosedNetwork[]			= "    Closed Network  ";
CUB	ENG_SettingSecurityTransmission[]	= "    Security Tx     ";
CUB	ENG_SettingBlockJunkMail[]			= "    Block Junk Fax  ";
CUB	ENG_SettingRemoteDiagnostic[]		= "    Set Service Mode";
CUB	ENG_SettingMemoryTransmission[]		= "    Set Memory Tx   ";
CUB	ENG_SettingSilentOperation[]		= "    Set Silent Mode ";
CUB	ENG_SettingDialIn[]					= "    Set Dial In     ";	/* (JPN) */
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_SettingProtectPasscode[]		= "    Protect Password";
#else
CUB	ENG_SettingProtectPasscode[]		= "    Protect Passcode";
#endif
CUB	ENG_SettingOperationProtect[]		= "    Set Opr. Protect";
CUB	ENG_SettingPINAccessMode[]			= "    Set PIN Mode    ";
CUB	ENG_SettingRingMasta[]				= "    Set DRD         ";	/* (USA) */
CUB	ENG_SettingStamp[]					= "    Set Stamp       ";
CUB	ENG_SettingResetDrumLife[]			= "    Reset Drum Life ";	/* ANZUのみ */
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */
CUB	ENG_SettingRxAlarm[]				= "    Set Rx Alarm    ";
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/22 */
CUB	ENG_SettingMercuryMode[]			= "    Set Dial Prefix ";	/* "Set Mercury"より変更 By S.Fukui Nov.14,1997 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	ENG_SettingHoldMelody[]				= "    Set Hold Melody ";
#endif
#if (PRO_REMOTE_RX == ENABLE)			/* ＮＴＴ仕様のポプラＬで使用 98/01/26 T.Fukumoto */
CUB	ENG_SettingRemoteReceive[]			= "    Set Remote Trans";
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	ENG_SettingOnHookReceive[]			= "    Set Onhook Trans";	/* 98/03/13 Add By T.Fukumoto */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	ENG_SettingPrintSettings[]			= "    Print Settings  ";
#endif

CUB	ENG_SetMessageOnOff[]				= "   Set Cover Page   ";
CUB	ENG_SetMessage[]					= "   Enter Cover Page ";
CUB	ENG_PrintMessageList[]				= "   Print Cover Page ";

CUB	ENG_SettingDepartmentProtect[]		= "   Set Dept. Protect";
CUB	ENG_SettingDepartmentCode[]			= "   Set Dept. Code   ";
CUB	ENG_SettingDepartmentOnOff[]		= "   Set Dept. On/Off ";
#if (PRO_DEPART_NEW_LIST == ENABLE)									 /* added by thonda 1997/12/03 */
CUB	ENG_PrintDepartTimeList[]			= "   Print Dp.TimeList";	 /* (暫定)ワーディング確認中 By S.Fukui Dec.15,1997 */
CUB	ENG_EraseDepartTimeList[]			= "   Erase Dp.TimeList";	 /* (暫定)ワーディング確認中 By S.Fukui Dec.15,1997 */
#endif

CUB	ENG_SettingBatchBox[]				= "   Set Batch Box    ";
CUB	ENG_PrintBatchBoxList[]				= "   Print Box List   ";
CUB	ENG_PrintBatchDocList[]				= "   Print Doc. List  ";
CUB	ENG_PrintBatchDoc[]					= "   Print Batch Doc. ";
CUB	ENG_EraseBatchBox[]					= "   Erase Batch Box  ";
CUB	ENG_EraseBatchDoc[]					= "   Erase Batch Doc. ";

CUB	ENG_SettingSecurityRx[]				= "   Set Security Rx  ";
CUB	ENG_PrintMemoryReceiveDoc[]			= "   Print Mem Rx Doc.";

#if (PRO_F_CODE == ENABLE)
CUB	ENG_EnterFcodeBoxMode[]				= "   Set F-Code Box   ";
CUB	ENG_PrintFcodeBoxListMode[]			= "   Print Box List   ";
CUB	ENG_PrintFcodeStoreDocListMode[]	= "   Print Doc. List  ";
CUB	ENG_PrintFcodeStoreDocMode[]		= "   Print F-Code Doc.";
CUB	ENG_EraseFcodeBoxMode[]				= "   Erase F-Code Box ";
CUB	ENG_EraseFcodeDocMode[]				= "   Erase F-Code Doc.";
CUB	ENG_StoreFcodeDocMode[]				= "   Set F-Code Doc.  ";
#endif

#if (PRO_CIPHER == ENABLE)
CUB	ENG_EnterCipherKeyBookMode[]		= "   Set KeyBook      ";  /* wording by t.honda 1997/09/20 ｷｰﾊﾞﾝｸ ｾｯﾄ */
CUB	ENG_PrintCipherKeyBookListMode[]	= "   KeyBook List     ";  /* wording by t.honda 1997/09/20 ｷｰﾊﾞﾝｸ ﾘｽﾄ */
CUB	ENG_PrintCipherKeyMode[]			= "   Print Key        ";  /* wording by t.honda 1997/09/20 ｷｰﾜｰﾄﾞ ﾌﾟﾘﾝﾄ */
CUB	ENG_EraseCipherKeyBookMode[]		= "   Erase KeyBook    ";  /* wording by t.honda 1997/09/20 ｷｰﾊﾞﾝｸ ｸﾘｱ */
CUB	ENG_EraseCipherRxDocMode[]			= "   Erase Scrmbld Doc";  /* (暫定)ワーディング確認中 By S.Fukui Dec.15,1997 */
CUB	ENG_EnterDefaultCipherKeyMode[]		= "   Set Default Key  ";  /* wording by t.honda 1997/09/20 ﾃﾞﾌｫﾙﾄ ｷｰﾜｰﾄﾞ ｾｯﾄ */
CUB	ENG_EnterCipherServiceLabelMode[]	= "   Svc. Lbl. Posit. ";  /* wording by t.honda 1997/09/20 ﾋﾝﾄ ﾋｮｳｼﾞｲﾁ */
 #if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_EnterCipherPassCodeMode[]		= "   Set Password     ";
 #else
CUB	ENG_EnterCipherPassCodeMode[]		= "   Set Passcode     ";  /* wording by t.honda 1997/09/20 ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ ｾｯﾄ */
 #endif
#endif

CUB	ENG_SettingRS232CPCFaxScan[]		= "   PC-FAX Scan      ";
CUB	ENG_SettingRS232CParameter[]		= "   Set RS232C       ";
CUB	ENG_SettingRS232CPCFaxInitial[]		= "   PC-FAX Initial   ";

/*----------------------------------*
 *	ワンタッチ登録
 *----------------------------------*/
CUB	ENG_SelectOnetouch[]				= "Select One-Touch    ";

CUB	ENG_EraseOnetouch[]					= "Erase One-Touch     ";
CUB	ENG_EraseSpeedDial[]				= "Erase Speed-Dial    ";
CUB	ENG_EraseProgramOnetouch[]			= "Erase P One-Touch   ";

/*----------------------------------*
 *	短縮登録
 *----------------------------------*/
CUB	ENG_SelectOptionalSpeedNumber[]		= "   /     (0-999):   ";

/* ワンタッチ・短縮ダイアルデータ入力中 */
/* このワーディングのサイズ及び登録順はかえてはいけない */
CUB	ENG_FaxNumber[]						= "Fax Number          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	ENG_AltNumber[]						= "Alt. No.            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	ENG_RemoteName[]					= "Name                ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大9ﾊﾞｲﾄです */
CUB	ENG_GroupNumber[]					= "Group No.           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/26 */
CUB	ENG_PinNumber[]						= "TTI Number          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
#else
CUB	ENG_PinNumber[]						= "PIN Number          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
#endif
CUB	ENG_Attribute1[]					= "Attribute1          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	ENG_Attribute2[]					= "Attribute2          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	ENG_Attribute3[]					= "Attribute3          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	ENG_Attribute4[]					= "Attribute4          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */

CUB	ENG_SetPIN_Number[]					= "Set PIN Number      ";

/*----------------------------------*
 *	プログラムワンタッチ
 *----------------------------------*/
CUB	ENG_SelectProgramOnetouch[]			= "Select Program No.  ";

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	拡張版プログラムワンタッチ
 *----------------------------------*/
CUB ENG_ProgramItem[][21]		= {
/*										  "12345678901234567890"	*/
										  "         Type: Comm.",
										  "         Type: List ",
										  "         Type: Store",
};

CUB ENG_ProgramList[][21]		= {
/*										  "12345678901234567890"	*/
										  "   Print One-Touch  ",
										  "   Print Speed-Dial ",
										  "   Print P One-Touch",
										  "   S Mail Box List  ",
										  "   Print Commands   ",
 #if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
										  "   Print AllJournals",
										  "   Print Day Journal",
 #else
										  "   Print Journal    ",
 #endif
										  "   Group List       ",
										  "   Print Settings   ",
										  "   Print BlockJunk  ",
										  "   Print Cover Msg. ",
										  "   Batch Box List   ",
										  "   Batch Doc. List  ",
 #if (PRO_F_CODE == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "   F-Code Box List  ",
										  "   F-Code Doc. List ",
 #endif
 #if (PRO_DEPART_NEW_LIST == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "   Department List  ",
 #endif
 #if (PRO_NUMBER_DISPLAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "   ND Dial List     ",
										  "   ND Journal       ",
 #endif
 #if (PRO_RX_DOC_TRANSFER == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "   FAX Warp List    ",
 #endif
};

CUB ENG_ProgramStore[][21]		= {
										  "   Store Polling Doc",
 #if (PRO_F_CODE == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "   Store F-Code Doc ",
 #endif
};

CUB ENG_ProgramTxModeSW[][21]	= {
/*										  "12345678901234567890"	*/
										  "    Mode: ---       ",
										  "    Mode: Normal    ",
										  "    Mode: Fine      ",
										  "    Mode: S Fine    ",
										  "    Mode: Gray      ",
};

CUB ENG_ProgramContrastSW[][21]	= {
/*										  "12345678901234567890"	*/
										  "    Contrast:   --- ",
										  "    Contrast: Light ",
										  "    Contrast: Normal",
										  "    Contrast: Dark  ",
};

CUB ENG_ProgramStampSW[][21]	= {
										  "    Stamp  :    --- ",
										  "    Stamp  :    OFF ",
										  "    Stamp  :    ON  ",
};

CUB ENG_ProgramMemoryTxSW[][21]	= {
										  "    Mem. Tx:    --- ",
										  "    Mem. Tx:    OFF ",
										  "    Mem. Tx:    ON  ",
};

CUB ENG_ProgramConfirmSW[][21]	= {
/*										  "12345678901234567890"	*/
										  "    Conf.Report:--- ",
										  "    Conf.Report:OFF ",
										  "    Conf.Report:TCR ",
										  "    Conf.Report:RCR ",
};

 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB ENG_ProgramTxModeSW_S[][21]	= {
/*										  "12345678901234567890"	*/
										  "    Mode: ---       ",
										  "    Mode: Normal    ",
										  "    Mode: Fine      ",
										  "    Mode: S Fine    ",
										  "    Mode: Gray      ",
};

CUB ENG_ProgramContrastSW_S[][21]	= {
/*										  "12345678901234567890"	*/
										  "    Contrast:   --- ",
										  "    Contrast: Light ",
										  "    Contrast: Normal",
										  "    Contrast: Dark  ",
};
 #endif
#endif	/* (PRO_EXT_P_ONETOUCH == ENABLE) */

/*----------------------------------*
 *	ポーリング
 *----------------------------------*/
CUB	ENG_StorePollingDocument[]			= "Store Polling Doc   ";
CUB	ENG_ErasePollingDocument[]			= "Erase Polling Doc   ";
CUB	ENG_PrintPollingDocument[]			= "Print Polling Doc   ";

/*----------------------------------*
 *	親展
 *----------------------------------*/
CUB	ENG_SetSecureMailBox[]				= "Set SecureMail Box  ";
CUB	ENG_SecureMailHoldTime[]			= "S Mail Hold Time    ";
CUB	ENG_HoldTime1_31[]					= "Hold Time(1-31):  \0 ";
CUB	ENG_SecureMailName[]				= " :Name     \0        ";	/* 先頭1文字は、親展番号をｾｯﾄします */

/*----------------------------------*
 *	通信予約
 *----------------------------------*/
CUB	ENG_PrintStoredDocument[]			= "Print Stored Doc.   ";
CUB	ENG_InputCommandNumber[]			= "Command No.:        ";
#if (PRO_CIPHER == ENABLE)
CUB	ENG_SelectDecipher[]				= "Descrambling   :\0   ";  /* wording by t.honda 1997/09/20 ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ */
#endif

/*----------------------------------*
 *	ジャーナル
 *----------------------------------*/
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_JournalOnOff[]					= "Report On/Off       ";
#else
CUB	ENG_JournalOnOff[]					= "Journal On/Off      ";
#endif
CUB	ENG_SelectAutoPrint[]				= "Auto Print:     \0   ";
CUB	ENG_TCRSelected[]					= "TCR Selected        ";
CUB	ENG_RCRSelected[]					= "RCR Selected        ";
CUB	ENG_SetCommunicationResult[]		= "Set Report Type     ";

/*----------------------------------*
 *	設置モード
 *----------------------------------*/
/* カレンダー入力 */
CUB	ENG_InputTime[]						= "Enter Time          ";

/* 夏時間切り替え */
#if defined(USA)
CUB	ENG_DayLightSaving[]				= "Daylight Saving:\0   ";
#endif

/* ＴＴＩ */
CUB	ENG_EnterYourFaxNumber[]			= "Your Fax Number     ";
CUB	ENG_EnterYourName[]					= "Your Name           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	ENG_EnterYourKanaName[]				= "Your KanaID         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* (JPN) */

/* 回線種別 */
CUB	ENG_SelectPhoneType[]				= "Phone Type   :\0     ";
CUB	ENG_10pps[]							= "              10pps ";
CUB	ENG_20pps[]							= "              20pps ";
CUB	ENG_Tone[]							= "              Tone  ";

CUB	ENG_Pulse10[]						= "              Pulse ";
CUB	ENG_Pulse20[]						= "              Pulse ";
CUB	ENG_Push[]							= "              Tone  ";

CUB	ENG_PrintSettingList[]				= "Print Setting List  ";	/* ANZUのみ */

#if (PRO_MULTI_LINE == ENABLE) || (PRO_MULTI_TTI == ENABLE)	/* 多回線仕様追加 1997/09/03 Y.Matsukuma */
/* マルチ回線ユーザー設定 */
/* 注）かっこの位置は固定すること。ただし、(9)は除く。 */
CUB	ENG_MultiYourFaxNumber[]			= "Your Fax Number  ( )";
CUB	ENG_MultiYourName[]					= "YourName( )         ";
CUB	ENG_MultiYourKanaName[]				= "Kana ID ( )         ";	/* (JPN) */
CUB	ENG_MultiPhoneType[]				= "Phone Type( ):\0     ";
CUB	ENG_MultiTxRx[]						= "Tx/Rx     ( ):\0     ";
CUB	ENG_SelectTxRx[]					= "              Tx/Rx ";
CUB	ENG_SelectTx[]						= "              Tx    ";
CUB	ENG_SelectRx[]						= "              Rx    ";
CUB	ENG_MultiLineType[]					= "Line Type  (9):\0    ";	/* 回線表示位置には必ず9を定義（国別の表示位置対応） */
CUB	ENG_SelectLinePstn[]				= "               PSTN ";
CUB	ENG_SelectLinePbx[]					= "               PBX  ";
CUB	ENG_SetAccessNumber[]				= "PSTN Access No.  ( )";
#endif

/* Ｆｕｎｃｔｉｏｎ */
CUB	ENG_On1[]							= "                On  ";	/* ﾃﾞﾌｫﾙﾄがONではじまる場合 */
CUB	ENG_Off1[]							= "                Off ";
CUB	ENG_Off2[]							= "                Off ";	/* ﾃﾞﾌｫﾙﾄがOFFではじまる場合 */
CUB	ENG_On2[]							= "                On  ";
CUB	ENG_Off3[]							= "                 Off";
CUB	ENG_On3[]							= "                 On ";
CUB	ENG_On4[]							= "                 On ";
CUB	ENG_Off4[]							= "                 Off";
CUB	ENG_ModeOff[]						= "               Off  ";
CUB	ENG_Mode1[]							= "               Mode1";
CUB	ENG_Mode2[]							= "               Mode2";
CUB	ENG_Mode3[]							= "               Mode3";

/*----------------------------------*
 *	ユーザー設定
 *----------------------------------*/
/* 読み取りパラメータ */
/* 原稿読みとり幅 */
CUB	ENG_SelectScanWidth[]				= "Scan Width:      \0  ";
CUB	ENG_ScanA4[]						= "                 A4 ";
CUB	ENG_ScanB4[]						= "                 B4 ";
CUB	ENG_ScanA3[]						= "                 A3 ";

/* 優先モード */
CUB	ENG_SelectPrimaryMode[]				= "Primary:   \0        ";
CUB	ENG_PrimaryModeNormal[]				= "           Normal   ";
CUB	ENG_PrimaryModeFine[]				= "           Fine     ";
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_PrimaryModeSFine[]				= "           Ex Fine  ";
#else
CUB	ENG_PrimaryModeSFine[]				= "           S Fine   ";
#endif
CUB	ENG_PrimaryModeGray[]				= "           Gray     ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	ENG_PrimaryModeFine_S[]				= "           Fine     ";
CUB	ENG_PrimaryModeSFine_S[]			= "           S Fine   ";
#endif

/* 優先原稿濃度 */
CUB	ENG_SelectPrimaryContrast[]			= "Contrast:    \0      ";
CUB	ENG_PrimaryContrastLight[]			= "             Light  ";
CUB	ENG_PrimaryContrastLittleLight[]	= "             Lighter";  /* modified by honda 1997/10/01 Not As Dark ﾔﾔ ｳｽｸ */
CUB	ENG_PrimaryContrastNormal[]			= "             Normal ";
CUB	ENG_PrimaryContrastLittleDark[]		= "             Darker ";  /* modified by honda 1997/10/01 Not As Light ﾔﾔ ｺｸ */
CUB	ENG_PrimaryContrastDark[]			= "             Dark   ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	ENG_SelectPrimaryContrast_S[]		= "Contrast:    \0      ";
CUB	ENG_PrimaryContrastLight_S[]		= "             Light  ";
CUB	ENG_PrimaryContrastDark_S[]			= "             Dark   ";
#endif

CUB	ENG_SetScanParameters[]				= "Scan Parameters     ";

/* プリントパラメータ */
CUB	ENG_SelectReceiveReduction[]		= "Prnt Reduc Rate:\0   ";
CUB	ENG_AutoReduction[]					= "                Auto";
CUB	ENG_100[]							= "                100%";
CUB	ENG_97[]							= "                 97%";
CUB	ENG_91[]							= "                 91%";
CUB	ENG_81[]							= "                 81%";
CUB	ENG_75[]							= "                 75%";
CUB	ENG_InputThresholdValue0_85[]		= "Margin(0-85mm):   \0 ";
CUB	ENG_SelectPageCompound[]			= "Half Page Recpt: \0  ";
CUB	ENG_SetPrintParameters[]			= "Print Parameters    ";
#if (PRO_ROTATE == ENABLE)
CUB	ENG_SetRotateMargin[]				= "Rotate Print        ";	/* 回転受信 [暫定] S.Fukui Jan.9,1998 */
#endif

/* コピーパラメータ */
CUB	ENG_SelectSortingCopy[]				= "Sorting Copy:   \0   ";
CUB	ENG_SelectCopyReduction[]			= "Copy Reduc Rate:\0   ";	/* POPLAR_B以外 */
CUB	ENG_SetCopyParameters[]				= "Copy Parameters     ";	/* POPLAR_B以外 */

/* 記録紙サイズ */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	ENG_EnterPaperSize[]				= "Paper Size:  \0      ";
CUB	ENG_PaperSizeNone[]					= "             None   ";
CUB	ENG_PaperSizeA4[]					= "             A4     ";
CUB	ENG_PaperSizeB4[]					= "             B4     ";
CUB	ENG_PaperSizeLetter[]				= "             Letter ";
CUB	ENG_PaperSizeLegal[]				= "             Legal  ";
CUB	ENG_PaperSizeF4[]					= "             F4     ";
CUB	ENG_SetPaperSize[]					= "Set Paper Size      ";

 #if (PRO_PC_PRINT == ENABLE)	/* ＰＣプリント */
CUB	ENG_SelectPaperSizeNone[]			= "             None   ";	/* 不要かもしれない */
CUB	ENG_SelectPaperSizeA5[]				= "             A5_P   ";
  #if defined(USA)
CUB	ENG_SelectPaperSizeLetter[]			= "             Letter ";
  #else
CUB	ENG_SelectPaperSizeLetter[]			= "             Ltr_P  ";
  #endif
  #if defined(USA)
CUB	ENG_SelectPaperSizeA4[]				= "             A4_P   ";
  #else
CUB	ENG_SelectPaperSizeA4[]				= "             A4     ";
  #endif
  #if defined(USA) || defined(TWN) /* 1998/01/09 Y.Matsukuma */
CUB	ENG_SelectPaperSizeLegal[]			= "             Legal  ";
  #else
CUB	ENG_SelectPaperSizeLegal[]			= "             Legal_P";
  #endif
CUB	ENG_SelectPaperSizeB5R[]			= "             B5R_P  ";
CUB	ENG_SelectPaperSizeB4[]				= "             B4_P   ";
CUB	ENG_SelectPaperSizeA3[]				= "             A3_P   ";
CUB	ENG_SelectPaperSizeA4R[]			= "             A4R_P  ";
CUB	ENG_SelectPaperSizeLetterR[]		= "             LtrR_P ";
  #if defined(TWN) || defined(AUS)	/* 1998/01/09 Y.Matsukuma */
CUB	ENG_SelectPaperSizeF4[]				= "             F4     ";
  #else
CUB	ENG_SelectPaperSizeF4[]				= "             F4_P   ";
  #endif
CUB	ENG_SelectPaperSizeA5R[]			= "             A5R_P  ";
CUB	ENG_SelectPaperSizePostcard[]		= "             Post_P ";
CUB	ENG_SelectPaperSizeLD[]				= "             Ld_P   ";
CUB	ENG_SelectPaperSizeGLetterR[]		= "             GLtrR_P";
CUB	ENG_SelectPaperSizeExecutiveR[]		= "             ExeR_P ";
CUB	ENG_SelectPaperSizeInvoiceR[]		= "             InvR_P ";
CUB	ENG_SelectPaperSizeGLegal[]			= "             GLegl_P";
CUB	ENG_SelectPaperSizeGLetter[]		= "             GLtr_P ";
CUB	ENG_SelectPaperSizeCard[]			= "             Card_P ";
CUB	ENG_SelectPaperSizeExecutive[]		= "             Exe_P  ";
CUB	ENG_SelectPaperSizeB5[]				= "             B5_P   ";
CUB	ENG_SelectPaperSizeC5[]				= "             C5_P   ";
CUB	ENG_SelectPaperSizeHalfLetter[]		= "             HLtr_P ";
CUB	ENG_SelectPaperSizeInvoice[]		= "             Inv_P  ";
CUB	ENG_SelectPaperSizeB6[]				= "             B6_P   ";
CUB	ENG_SelectPaperSizeDL[]				= "             DL_P   ";
CUB	ENG_SelectPaperSizeCM10[]			= "             CM10_P ";
CUB	ENG_SelectPaperSizeA6[]				= "             A6_P   ";
CUB	ENG_SelectPaperSizeMonarch[]		= "             Mnc_P  ";
CUB	ENG_SelectPaperSize35[]				= "             3x5_P  ";
CUB	ENG_SelectPaperSizeUser[]			= "             User_P ";
 #endif
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */

/* コピー禁止 */
CUB	ENG_SelectCopyProtect[]				= "Copy Protect   :\0   ";  /* wording by t.honda 1997/09/20 ｺﾋﾟｰｷﾝｼ */

/* ポーズ */
CUB	ENG_SetDialingPause[]				= "Set Dialing Pause   ";
CUB	ENG_PauseTime[]						= "Time        :\0      ";	/* 注）ｼﾞｶﾝ (05-10): の（）の部分は実行時に作成します */

/* べル回数 */
CUB	ENG_SetNumberOfRings[]				= "Set # Of Rings      ";
CUB	ENG_NumberOfRings[]					= "#           :\0      ";	/* 注）ｶｲｽｳ   (1-9): の（）の部分は実行時に作成します */

/* リダイアル */
CUB	ENG_RedialCount[]					= "#           :\0      ";	/* 注）ｶｲｽｳ (02-10): の（）の部分は実行時に作成します */
CUB	ENG_SetNumberOfRedials[]			= "Set # Of Redials    ";
CUB	ENG_RedialInterval[]				= "Inter.      :\0      ";	/* 注）ｶﾝｶｸ   (1-5): の（）の部分は実行時に作成します */
CUB	ENG_SetRedialInterval[]				= "Set Redial Interval ";
CUB	ENG_SetRedial[]						= "Set Redial          ";

/* ECM */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/23 Y.Matsukuma */
CUB	ENG_SelectECMMode[]					= "CassetteProtect:\0   ";
CUB	ENG_SetECMMode[]					= "Set CassetteProtect ";
#else
CUB	ENG_SelectECMMode[]					= "ECM Mode:       \0   ";
CUB	ENG_SetECMMode[]					= "Set ECM Mode        ";
#endif

/* パスコード */
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_SetPasscode[]					= "Set Password        ";
#else
CUB	ENG_SetPasscode[]					= "Set Passcode        ";
#endif

/* 閉域通信設定 */
CUB	ENG_SelectClosedNetwork[]			= "Closed Net.:    \0   ";
CUB	ENG_SetClosedNetwork[]				= "Closed Network      ";

/* パスワード送信 */
CUB	ENG_SelectSecurityTransmission[]	= "Security Tx:    \0   ";
CUB	ENG_SetSecurityTransmission[]		= "Security Tx         ";

/* ダイレクトメール防止 */
CUB	ENG_SelectBlockJunkMail[]			= "Block Junk Fax:\0    ";
CUB	ENG_SetBlockJunkMailDial[]			= "Set BlockJunk Dial  ";
CUB	ENG_PrintBlockJunkMailDialList[]	= "Print BlockJunk Dial";
CUB	ENG_SetBlockJunkMail[]				= "Block Junk Fax      ";
CUB	ENG_BlockJunkMailSelectNumber[]		= "Select BlockJunk No.";
CUB ENG_SetSameNumber[]					= "Already Stored      ";

/* リモート診断 */
CUB	ENG_SelectRemoteDiagnostic[]		= "Service Mode:   \0   ";
CUB	ENG_SetRemoteDiagnostic[]			= "Set Service Mode    ";

/* メモリー送信 */
CUB	ENG_SelectMemoryTransmission[]		= "Memory Tx:      \0   ";
CUB	ENG_SetMemoryTransmission[]			= "Set Memory Tx       ";

/* サイレントオペレーション */
CUB	ENG_SelectSilentOperation[]			= "Silent Mode:    \0   ";
CUB	ENG_SetSilentOperation[]			= "Set Silent Mode     ";

/* プロテクトパスコード */
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 98/07/07 */
CUB	ENG_SetProtectPasscode[]			= "Protect Password    ";
CUB	ENG_ProtectPasscode[]				= "Protect Password    ";
#else
CUB	ENG_SetProtectPasscode[]			= "Protect Passcode    ";
CUB	ENG_ProtectPasscode[]				= "Protect Passcode    ";
#endif

/* オペレーションプロテクト */
CUB	ENG_OperationProtectOnOff[]			= "Opr.Protect:    \0   ";
CUB	ENG_SetOperationProtect[]			= "Set Opr. Protect    ";

/* ＰＩＮアクセスモードセット */
CUB	ENG_PINAccessMode[]					= "PIN Mode:      \0    ";
CUB	ENG_SetPINAccessMode[]				= "Set PIN Mode        ";

/* リングマスター */
#if (PRO_RING_MASTER == ENABLE)	/* by K.Watanabe 1998/08/18 */
CUB	ENG_SelectRingMaster[]				= "DRD:            \0   ";
CUB	ENG_SelectRingPattern[]				= "Ring Pattern:     \0 ";
CUB	ENG_RingPattern_A[]					= "                  A ";
CUB	ENG_RingPattern_B[]					= "                  B ";
CUB	ENG_RingPattern_C[]					= "                  C ";
CUB	ENG_RingPattern_D[]					= "                  D ";
CUB	ENG_RingPattern_E[]					= "                  E ";
CUB	ENG_RingPattern_F[]					= "                  F ";
CUB	ENG_RingPattern_G[]					= "                  G ";
CUB	ENG_RingPattern_H[]					= "                  H ";
CUB	ENG_SetRingMaster[]					= "Set DRD             ";
#endif

/* 済みスタンプ */
CUB	ENG_StampOnOff[]					= "Stamp:          \0   ";
CUB	ENG_SetStamp[]						= "Set Stamp           ";

/* ドラム寿命リセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* by K.Watanabe 1998/08/18 */
CUB	ENG_ResetDrumLife[]					= "Reset Drum Life     ";
#endif

/* 受信アラームセット */
#if defined(GBR)
CUB	ENG_RxAlarm[]						= "Audible Alarm:  \0   ";
CUB	ENG_SetRxAlarm[]					= "Set Rx Alarm        ";
#endif

/*----------------------------------*
 *	マーキュリー
 *----------------------------------*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
CUB	ENG_MercuryNumberSet[]				= "Dial Prefix No      ";	/* "Mercury Number" より変更 By S.Fukui Nov.14,1997 */
/* マーキュリーポーズ  */
CUB	ENG_MercuryPauseSet[]				= "Set Prefix Pause    ";	/* "Mercury Pause Set" より変更 By S.Fukui Nov.14,1997 */
CUB	ENG_SetMercury[]					= "Set Dial Prefix     ";	/* "Set Mercury"より変更 By S.Fukui Nov.14,1997 */
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* 保留メロディーセット */
CUB	ENG_SelectHoldMelody[]				= "Hold Melody    :\0   ";
#endif

/* リモート受信 */
#if (PRO_REMOTE_RX == ENABLE)			/* ＮＴＴ仕様のポプラＬで使用 98/01/26 T.Fukumoto */
CUB	ENG_SelectRemoteReceive[]			= "Remote Trans'  :\0   ";
#endif

/* オンフック受信 */
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	ENG_SelectOnHookReceive[]			= "Onhook Trans'  :\0   ";	/* 98/03/13 Add By T.Fukumoto */
#endif

/* ダイアルイン */
#if (PRO_DIALIN == ENABLE)
CUB	ENG_SetDialIn[]						= "Set Dial In         ";
CUB	ENG_DialInFax[]						= "Fax:            \0   ";

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ＨＩＮＯＫＩは本体の刻印にあわせます。 By O.Kimoto 1999/02/09 */
CUB	ENG_DialInTel1[]					= "PHONE1:         \0   ";
CUB	ENG_DialInTel2[]					= "PHONE2:         \0   ";
#else
CUB	ENG_DialInTel1[]					= "Tel1:           \0   ";
CUB	ENG_DialInTel2[]					= "EXT.Tel:        \0   ";
#endif

CUB	ENG_DialInRings[]					= "Set Ring Time       ";
CUB	ENG_DialInRings10_60[]				= "(10-60)      \0      ";
#endif

/*----------------------------------*
 *	カバーページ
 *----------------------------------*/
CUB	ENG_MessageOnOff[]					= "Cover Page:     \0   ";
CUB	ENG_MessageTx[]						= "Set Cover Page      ";
CUB	ENG_SetCoverPageMessage[]			= "Cover Page          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	ENG_MessageSet[]					= "Enter Cover Page    ";

/*----------------------------------*
 *	枚数設定
 *----------------------------------*/
CUB	ENG_InputPageCount[]				= "Enter # Of Pages    ";

#if defined(POPLAR_F)
 #if defined(JP1)
	CUB	ENG_PageCount1_30[]					= "           (1-50):\0 ";
 #else
	CUB	ENG_PageCount1_30[]					= "           (1-30):\0 ";
 #endif
#else
 #if defined(POPLAR_N) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ポプラＬ（ＮＴＴ仕様） by K.Watanabe 1998/03/16 */
	CUB	ENG_PageCount1_30[]					= "           (1-30):\0 ";
 #else
	CUB	ENG_PageCount1_30[]					= "           (1-50):\0 ";
 #endif
#endif

/*----------------------------------*
 *	部門管理
 *----------------------------------*/
/* 部門管理プロテクトセット */
CUB	ENG_DepartmentProtect[]				= "Dept. Protect:  \0   ";
CUB	ENG_SetDepartmentProtect[]			= "Set Dept. Protect   ";

/* 部門コードセット */
CUB	ENG_DepartmentSelectNumber[]		= "Select Department No";

/* 部門管理セット */
CUB	ENG_DepartmentOnOff[]				= "Dept. On/Off:   \0   ";
CUB	ENG_SetDepartmentOnOff[]			= "Set Dept. On/Off    ";

#if (PRO_DEPART_NEW_LIST == ENABLE)		/* 追記 By S.Fukui Jan.7,1998 */
/* 簡易部門毎時間管理リスト関連 */
CUB	ENG_EraseDepartTimeListMode[]		= "Erase Dp.TimeList   ";	/* この２行暫定ワーディング */
CUB	ENG_EraseDepartCode[]				= "    :Erase Dpt. Code";	/* 先頭４文字は部門ｺｰﾄﾞ表示 */
CUB ENG_DepartCodeFull[]				= "Dept.Code  Full     ";
#endif

/*----------------------------------*
 *	一括送信
 *----------------------------------*/
CUB	ENG_SelectBatchBoxNumber[]			= "Select Batch Box    ";
CUB	ENG_TranssmissionTime[]				= "Transmit Time       ";
CUB	ENG_EraseBatchBoxMode[]				= "Erase Batch Box     ";
CUB	ENG_EraseBatchDocumentMode[]		= "Erase Batch Doc.    ";

CUB	ENG_PrintBatchBoxMode[]				= "Print Box List      ";
CUB	ENG_PrintBatchDocListMode[]			= "Print Doc. List     ";
CUB	ENG_PrintBatchDocMode[]				= "Print Batch Doc.    ";
CUB	ENG_BatchBoxNumber[]				= "Enter Box No.     \0 ";
CUB	ENG_BatchFileNumber[]				= "Enter File No.   \0  ";

/*----------------------------------*
 *	セキュリティ受信
 *----------------------------------*/
/* セキュリティ受信セット */
CUB	ENG_SecurityReceive[]				= "Security Rx:    \0   ";
CUB	ENG_SetSecurityReceive[]			= "Set Security Rx     ";

/* メモリ受信原稿プリント */
CUB	ENG_PrintMemoryReceiveDocMode[]		= "Print Mem Rx Doc.   ";

/*----------------------------------*
 *	Ｆコード
 *----------------------------------*/
#if (PRO_F_CODE == ENABLE)
CUB	ENG_SelectFcodeBoxNumber[]			= "Select F-Code Box   ";
CUB	ENG_EnterFcodeBoxName[]				= "  :Box Name\0        ";
CUB	ENG_EnterFcodeSubAddress[]			= "  :Sub-Address No.  ";
CUB	ENG_EnterFcodePassword[]			= "  :Password         ";     /* Passcode -> Password に変更 */
CUB	ENG_SelectFcodeBoxKind[]			= "Box Type   :\0       ";
CUB	ENG_FcodeBulletinBoardBox[]			= "            Bulletin";
CUB	ENG_FcodeConfidentialBox[]			= "            Security";
#if (PRO_FCODE_RELAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
CUB	ENG_FcodeRelayBox[]					= "            Relay   ";
#endif
CUB	ENG_SelectFcodeRxProhibition[]		= "Rx Protect     :\0   ";
CUB	ENG_SelectFcodeRxDocPrint[]			= "Auto Print     :\0   ";
CUB	ENG_SelectFcodeRxDocUpperWrite[]	= "Overwrite Doc. :\0   ";
CUB	ENG_SelectFcodeTxDocClear[]			= "Erase Tx Doc.  :\0   ";
CUB	ENG_FcodeDocumentHoldTime[]			= "F-Code Doc Hold Time";
CUB	ENG_HoldTime0_31[]					= "Hold Time(0-31)  :\0 ";  /* wording by t.honda 1997/09/20 ﾒﾓﾘｷｶﾝ */
CUB	ENG_SelectFcodeStoreDocAdd[]		= "Add Document   :\0   ";
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/11/13 */
CUB	ENG_StoreFcodeDocument[]			= "F-Code Doc F:       ";
#else
CUB	ENG_StoreFcodeDocument[]			= "F-Code Doc.  File:  ";
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
 #if (PRO_FCODE_RELAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
CUB	ENG_InputRelayNumber[]				= "Enter Relay Number  ";
CUB ENG_SetRelayTTI[][21]				= {
										  "Select TTI   :\0     ",

#if (0)
** /* ﾜｰﾃﾞｨﾝｸﾞ変更 By O.Kimoto 1999/02/08 */
** 										  "              OFF    ",
** 										  "              Outside",
** 										  "              Inside ",
#else
										  "              Sender ",
										  "              Both   ",
										  "              Yours  ",
#endif

};
 #endif
#endif
CUB	ENG_SameNumber[]					= "Sub-Address In Use  ";

/*----------------------------------*
 *	ＰＣプリントボード初期化
 *----------------------------------*/
#if (PRO_PC_PRINT == ENABLE)
CUB	ENG_BoardReset[]					= "Reset Printer Opt.  ";
#endif

/*----------------------------------*
 *	暗号化
 *----------------------------------*/
#if (PRO_CIPHER == ENABLE)
CUB	ENG_EnterCipherKeyName[]			= " :Key Title\0        ";  /* wording by t.honda 1997/09/20 ｷｰﾊﾞﾝｸ ﾒｲ */
CUB	ENG_EnterCipherKey[]				= " :Set Key  \0        ";  /* wording by t.honda 1997/09/20 ｷｰﾜｰﾄﾞ */
CUB	ENG_EnterCipherKeyClue[]			= " :Key Clue \0        ";  /* wording by t.honda 1997/09/20 ｷｰﾜｰﾄﾞﾋﾝﾄ */
CUB	ENG_InputCipherRxDocNumber[]		= "Number Of Rx Doc.:\0 ";  /* wording by t.honda 1997/09/20 ｼﾞｭｼﾝ ﾊﾞﾝｺﾞｳ */
CUB	ENG_InputCipherExtensionKey[]		= "Key Extension   :\0  ";  /* wording by t.honda 1997/09/20 ﾀﾞﾌﾞﾙｶﾞｰﾄﾞ */
CUB	ENG_SelectCipherDocErrRemoval[]		= "Correct Error  :\0   ";  /* wording by t.honda 1997/09/20 ｴﾗｰ ｼｭｳｾｲ */
CUB	ENG_SelectCipherKeySetKind[]		= "Set Key     :\0      ";  /* wording by t.honda 1997/09/20 ｷｰﾜｰﾄﾞ ｾｯﾄ */
CUB	ENG_CipherKeySetDefault[]			= "             Default";   /* wording by t.honda 1997/09/20 ﾃﾞﾌｫﾙﾄ */
CUB	ENG_CipherKeySetKeyBook[]			= "             KeyBook";   /* wording by t.honda 1997/09/20 ｷｰﾊﾞﾝｸ */
CUB	ENG_CipherKeySetDirect[]			= "             Direct ";   /* wording by t.honda 1997/09/20 ﾁｮｸｾﾂ */
CUB	ENG_InputCipherDefaultKeyNo[]		= "Key Number  (0-9):\0 ";  /* wording by t.honda 1997/09/20 ｷｰﾜｰﾄﾞﾊﾞﾝｺﾞｳ */
 #if defined(USA)
CUB	ENG_InputServiceLabelPosition[]		= "Offset(1-14.5\"):\0   ";  /* by t.fukumoto 1997/12/12 */
 #else
CUB	ENG_InputServiceLabelPosition[]		= "Offset  (2-36cm):\0  ";  /* wording by t.honda 1997/09/20 ｵﾌｾｯﾄ */
 #endif
CUB	ENG_CipherSelectNumber[]			= "Select Key Number   ";   /* wording by t.honda 1997/09/20 ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ */
CUB	ENG_CipherExecute[]					= "Scrambling     99/99";
CUB	ENG_DecipherExecute[]				= "Descrambling   99/99";
CUB	ENG_CipherExecuteError[]			= "Scrambling Error    ";
CUB	ENG_DecipherExecuteError[]			= "Descrambling Error  ";
CUB	ENG_DecipherKeyError[]				= "Invalid Key         ";
CUB	ENG_ConfirmDecipherContinue[]		= "ContDscrm Entr/Cancl";	 /* (暫定)ワーディング確認中 By S.Fukui Dec.15,1997 */
CUB	ENG_DecipherDocument[]				= "Descrambled Document";  /* ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ｹﾞﾝｺｳ bythonda1998/02/24 */
CUB	ENG_StopCipherExecute[]				= "Stop Scrambling     ";  /* ｽｸﾗﾝﾌﾞﾙ ﾁｭｳｼ bythonda1998/07/15 */
CUB	ENG_StopDecipherExecute[]			= "Stop Descrambling   ";  /* ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ﾁｭｳｼ bythonda1998/07/15 */
#endif
CUB	ENG_InputPrintPageNumber[]			= "Num(1-99)       :\0  ";  /* wording by t.honda 1997/09/20 ﾌﾞｽｳ */
CUB	ENG_ProgressRate[]					= " 0%            100% ";

/*----------------------------------*
 *	クラス１
 *----------------------------------*/
CUB	ENG_SetRS232CParameter[]			= "Set RS232C          ";
CUB	ENG_SetRS232CPCFaxInitial[]			= "PC-FAX Initial      ";

/* ＲＳ２３２Ｃボーレート */
CUB	ENG_SelectRS232CBaudRate[]			= "Baud Rate :\0        ";
CUB	ENG_RS232CVariable[]				= "           Variable ";
CUB	ENG_RS232C600bps[]					= "             600bps ";
CUB	ENG_RS232C1200bps[]					= "            1200bps ";
CUB	ENG_RS232C2400bps[]					= "            2400bps ";
CUB	ENG_RS232C4800bps[]					= "            4800bps ";
CUB	ENG_RS232C9600bps[]					= "            9600bps ";
CUB	ENG_RS232C19200bps[]				= "           19200bps ";

/* ＲＳ２３２Ｃパリティビット設定 */
CUB	ENG_SelectParity[]					= "Parity        :\0    ";
CUB	ENG_RS232CNone[]					= "               None ";
CUB	ENG_RS232COdd[]						= "               Odd  ";
CUB	ENG_RS232CEven[]					= "               Even ";

/* ＲＳ２３２Ｃストップビット設定 */
CUB	ENG_Select232CStopBit[]				= "Stop Bit     :\0     ";
CUB	ENG_RS232C1bit[]					= "              1 bit ";
CUB	ENG_RS232C2bit[]					= "              2 bit ";

/* ＲＳ２３２Ｃデータ長設定 */
CUB	ENG_Select232CDataLength[]			= "Data Length  :\0     ";
CUB	ENG_RS232C7bit[]					= "              7 bit ";
CUB	ENG_RS232C8bit[]					= "              8 bit ";

/* クラス１関連追加 */
CUB	ENG_PC_FAX_Scan[]					= "PC-FAX Scan         ";
CUB	ENG_PC_FAX_Print[]					= "PC-FAX Print        ";
CUB	ENG_PC_FAX_Connect[]				= "PC-FAX Connection   ";
CUB	ENG_PC_FAX_InitialError[]			= "PC-FAX Initial Error";
CUB	ENG_PC_FAX_Complete[]				= " **   Complete   ** ";
CUB	ENG_PC_FAX_InUse[]					= "PC-FAX In Use       "; /* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
CUB	ENG_ReceiveInFax[]					= "Receive In Fax ?    "; /* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */

/* 送信時、部門コード入力 */
CUB	ENG_EnterDepartmentCode[]			= "Enter Dept. Code    ";

/* 送信時、ダイヤル番号入力 */
CUB	ENG_EnterDialNumber[]				= "Enter Fax Number    ";

/* 送信時、ＰＩＮ番号入力 */
CUB	ENG_EnterPinNumber[]				= "Enter PIN Number    ";

/************************************************
** Dial-UpｲﾝﾀｰﾈｯﾄFAX関係	1998/03/12 by K.Okada
************************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/** ユーザ登録 */
CUB ENG_EMailSettingMode[]				= "  E-Mail Setting    ";
CUB ENG_SetUserDataMode[]				= "   Set User Data    ";
CUB ENG_SetUserData[]					= "Set User Data       ";
/*↓この2つはこの順番で並べて記述*/
CUB ENG_NewEntry[]						= "New Entry?          ";
CUB ENG_UpdateSetting[]					= "Update Setting?     ";
CUB ENG_NewMailBox[]					= "New Mail Box?  :\0   ";
/*↓この2つはこの順番で並べて記述*/
CUB ENG_No[]							= "                No  ";
CUB ENG_Yes[]							= "                Yes ";
CUB ENG_UserCodeNumber[]				= "Your Code No.       ";
CUB ENG_UserCodeNumberAgain[]			= "Code No. Again      ";
CUB ENG_EnterYourCodeNumber[]			= "Enter Your Code No. ";
CUB ENG_ISP_Name[]						= "ISP Name            ";
CUB ENG_AccessPoint[]					= "Access Point        ";
/*↓この3つはこの順番で並べて記述*/
CUB ENG_1stTime[]						= ":1st  \0             ";
CUB ENG_2ndTime[]						= ":2nd  \0             ";
CUB ENG_3rdTime[]						= ":3rd  \0             ";
CUB ENG_UserName[]						= "Your Name           ";
CUB ENG_PPP_LoginID[]					= "PPP-ID              ";
CUB ENG_POP_LoginID[]					= "POP-ID              ";
/*↓この2つはこの順番で並べて記述*/
CUB ENG_PPP_Password[]					= "PPP-PWD             ";
CUB ENG_PPP_PasswordAgain[]				= "Again               ";
/*↓この2つはこの順番で並べて記述*/
CUB ENG_POP_Password[]					= "POP-PWD             ";
CUB ENG_POP_PasswordAgain[]				= "Again               ";
CUB ENG_MailAddress[]					= "Address             ";
CUB ENG_PPP_Auth[]						= "PPP Auth            ";
/*↓この3つはこの順番で並べて記述*/
CUB ENG_PPP_PAP[]						= ":PAP  \0             ";
CUB ENG_PPP_CHAP[]						= ":CHAP \0             ";
CUB ENG_PPP_NoneAuth[]					= ":NONE \0             ";
CUB ENG_Client[]						= "Client              ";
CUB ENG_ISP_Server[]					= "Server              ";
CUB ENG_Gateway[]						= "Gateway             ";
CUB ENG_DNS_Server[]					= "DNS Server          ";
CUB ENG_Primary[]						= ":Primary  \0         ";
CUB ENG_Secondary[]						= ":Secondary\0         ";
CUB ENG_SMTP_Server[]					= "SMTP Server         ";
CUB ENG_POP_Server[]					= "POP Server          ";

/** 機器動作設定 */
#if (0)
//CUB ENG_SetMachineStateMode[]			= "   Auto Mail Receive";
#endif
CUB ENG_SetMachineStateMode[]			= "   Mail Rx Setting  ";
CUB ENG_AutoReceive[]					= "Auto Check Mail:\0   ";
CUB ENG_AutoDownload[]					= "Auto Download : \0   ";
CUB ENG_AutoPrint[]						= "Auto Print    : \0   ";
CUB ENG_DeleteMail[]					= "Delete Mail   : \0   ";
CUB ENG_MailHoldTime[]					= "Mail Hold Days      ";
CUB ENG_Days1_31[]						= "Days(1-31)          ";
CUB ENG_RxDuringTx[]					= "Tx with Rx    : \0   ";
CUB ENG_SetMachineState[]				= "Mail Rx Setting     ";
CUB ENG_AutoRxStartTime[]				= "Start Time          ";
CUB ENG_AutoRxEndTime[]					= "End Time            ";
CUB ENG_IntervalTime[]					= "Interval Time       ";

/** トーン検出設定 */
#if (0)
//CUB ENG_SetToneDetectMode[]				= "   Set Tone Detect  ";
//CUB ENG_SetDialParameter[]				= "Set Tone Detect     ";
//CUB ENG_DialToneOn[]					= "Dial Tone:      \0   ";
//CUB ENG_BusyToneOn[]					= "Busy Tone:      \0   ";
#endif

/** ユーザデータ消去 */
CUB ENG_EraseUserDataMode[]				= "   Erase User Data  ";
CUB ENG_EraseUserData[]					= "Erase User Data     ";

/**  メール設定リスト */
CUB ENG_PrintUserDataMode[]				= "   Print User Data  ";
CUB ENG_PrintUserData[]					= "Print User Data     ";

/** コマンド入力表示 */
CUB ENG_EnterMailAddress[]				= "Enter Mail Address  ";

/** 宛先 */
CUB ENG_SetMailAddressMode[]			= "  Mail Address      ";
CUB ENG_SetMailAddress[]				= "   Set Mail Address ";
CUB ENG_AddressName[]					= "Name                ";
CUB ENG_EraseMailAddressMode[]			= "   Erase MailAddress";
CUB ENG_EraseMailAddress[]				= "Erase Mail Address  ";
CUB ENG_PrintMailAddressMode[]			= "   Print MailAddress";
CUB ENG_PrintMailAddress[]				= "Print Mail Address  ";
CUB ENG_SetMailGroup[]					= "   Set Mail Group   ";
CUB ENG_MailGroupSetting[]				= "Mail Group          ";
CUB ENG_EraseMailGroupMode[]			= "   Erase Mail Group ";
CUB ENG_EraseMailGroup[]				= "Erase Mail Group    ";
CUB ENG_PrintMailGroupMode[]			= "   Print Mail Group ";
CUB ENG_PrintMailGroup[]				= "Print Mail Group    ";
CUB ENG_PressOnetouch[]					= "Press One-Touch     ";

/** サービスファンクション */
CUB ENG_InitEngineBoard[]				= "Initialize I-FAX    ";
CUB ENG_IP_EchoRequest[]				= "IP Packet Echo Req. ";
CUB ENG_INF_Complete[]					= " **   Complete   ** ";
CUB	ENG_SF_TTL_Test[]					= "TTL Test            "; /*1998/6/9 Eguchi*/

/** 設置オペレーション */
CUB ENG_INF_InitialError[]				= "I-FAX Initial Error ";

/** コマンド予約 */
CUB ENG_ReviewMailComMode[]				= "  Review Mail Com.  ";
CUB ENG_CancelMailCom[]					= "Cancel Mail Com.    ";
CUB ENG_PrintMailComMode[]				= "   Print Mail Com.  ";
CUB ENG_PrintMailCom[]					= "Print Mail Com.     ";
CUB ENG_PrintStoredMailMode[]			= "   Print Stored Mail";
CUB ENG_PrintStoredMail[]				= "Print Stored Mail   ";
CUB ENG_EnterMailCommandNo[]			= "Enter Command No.   ";

/** ジャーナルプリント */
CUB ENG_PrintMailJounalMode[]			= "   Print Mail Jrnl. ";
CUB ENG_PrintMailJournal[]				= "Print Mail Jrnl.    ";

/** 受信 */
CUB ENG_ManualReceiveMail[]				= "   Manual Rcv. Mail ";
CUB ENG_ReceiveMailMode[]				= "  Receive Mail      ";
CUB ENG_PrintReceiveMailMode[]			= "   Print Rcv. Mail  ";
CUB ENG_PrintReceiveMail[]				= "Print Rcv. Mail     ";

/** 動作中および終了表示 */
CUB ENG_INF_Abort[]						= " **  Terminate  **  ";
CUB ENG_INF_NoNewMail[]					= " **  No New Mail  **";
CUB ENG_SendingMail[]					= "Send Mail           ";
CUB ENG_ReceivingMail[]					= "Receive Mail        ";
CUB ENG_INF_Creating[]					= "** Creating Email **";
CUB ENG_INF_Dialing[]					= "   ** Dialing **    ";
CUB ENG_INF_Connecting[]				= "  ** Connecting **  ";
CUB ENG_INF_Sending[]					= "   ** Sending **    ";
CUB ENG_INF_Receiving[]					= "  ** Receiving **   ";
CUB ENG_INF_Checking[]					= "   ** Checking **   ";

CUB ENG_INF_PrintRcvReport[]			= "Print Rcv. Report   ";

/** PTTテスト信号送出サービスファンクション */
CUB ENG_PTT_TestMode[]					= "PTT Test Mode       ";
CUB ENG_PTT_Setting[]					= "PTT Test Setting    ";
CUB ENG_DataRate[]						= "    :Data Rate      ";
CUB ENG_SymbolRate[]					= "    :Symbol Rate    ";
CUB ENG_CarrierBias[]					= "    :Carrier Bias   ";
CUB ENG_SecondChannel[]					= "    :2nd Channel    ";
CUB ENG_UpperBandEdge[]					= "    :Upper Band Edge";
CUB ENG_CarrierBiasRange[]				= "[-100<-->100]       ";
CUB ENG_BandEdgeRange[]					= "[0-22(dB)]          ";
CUB ENG_INF_Mode[]						= "    :Mode           ";

/* PTTテスト信号種類 */
/*↓この順番で並べて記述*/
CUB ENG_DTMF_Tone0[]					= "%TT00               ";
CUB ENG_DTMF_Tone1[]					= "%TT01               ";
CUB ENG_DTMF_Tone2[]					= "%TT02               ";
CUB ENG_DTMF_Tone3[]					= "%TT03               ";
CUB ENG_DTMF_Tone4[]					= "%TT04               ";
CUB ENG_DTMF_Tone5[]					= "%TT05               ";
CUB ENG_DTMF_Tone6[]					= "%TT06               ";
CUB ENG_DTMF_Tone7[]					= "%TT07               ";
CUB ENG_DTMF_Tone8[]					= "%TT08               ";
CUB ENG_DTMF_Tone9[]					= "%TT09               ";
CUB ENG_DTMF_ToneAst[]					= "%TT0A               ";
CUB ENG_DTMF_ToneSharp[]				= "%TT0B               ";
CUB ENG_DTMF_ToneA[]					= "%TT0C               ";
CUB ENG_DTMF_ToneB[]					= "%TT0D               ";
CUB ENG_DTMF_ToneC[]					= "%TT0E               ";
CUB ENG_DTMF_ToneD[]					= "%TT0F               ";
CUB ENG_V21Ch1MkSymbol[]				= "%TT10               ";
CUB ENG_V21Ch2MkSymbol[]				= "%TT11               ";
CUB ENG_V23BwardChMkSymbol[]			= "%TT12               ";
CUB ENG_V23FwardChMkSymbol[]			= "%TT13               ";
CUB ENG_V22CallMk600bps[]				= "%TT14               ";
CUB ENG_V22CallMk1200bps[]				= "%TT15               ";
CUB ENG_V22bisCallMk2400bps[]			= "%TT16               ";
CUB ENG_V22AnswerSignal[]				= "%TT17               ";
CUB ENG_V22bisAnswerSignal[]			= "%TT18               ";
CUB ENG_V21Ch1SpSymbol[]				= "%TT19               ";
CUB ENG_V21Ch2SpSymbol[]				= "%TT1A               ";
CUB ENG_V23BwardChSpSymbol[]			= "%TT1B               ";
CUB ENG_V23FwardChSpSymbol[]			= "%TT1C               ";
CUB ENG_V32_9600bps[]					= "%TT20               ";
CUB ENG_V32bis14400bps[]				= "%TT21               ";
CUB ENG_V32TCM9600bps[]					= "%TT22               ";
CUB ENG_V32TCM14400bps[]				= "%TT23               ";
CUB ENG_V32bisTCM7200bps[]				= "%TT24               ";
CUB ENG_V32_4800bps[]					= "%TT25               ";
CUB ENG_OffFook[]						= "%TT30               ";
CUB ENG_V25AnswerTone[]					= "%TT31               ";
CUB ENG_1800HzGuardTone[]				= "%TT32               ";
CUB ENG_V25Send1300Hz[]					= "%TT33               ";
CUB ENG_FaxSend1100Hz[]					= "%TT34               ";
CUB ENG_BellAnswer2225hz[]				= "%TT35               ";
CUB ENG_V21Ch2[]						= "%TT40               ";
CUB ENG_V27ter2400bps[]					= "%TT41               ";
CUB ENG_V27ter4800bps[]					= "%TT42               ";
CUB ENG_V29_7200bps[]					= "%TT43               ";
CUB ENG_V29_9600bps[]					= "%TT44               ";
CUB ENG_V17_7200bpsL_Train[]			= "%TT45               ";
CUB ENG_V17_7200bpsS_Train[]			= "%TT46               ";
CUB ENG_V17_9600bpsL_Train[]			= "%TT47               ";
CUB ENG_V17_9600bpsS_Train[]			= "%TT48               ";
CUB ENG_V17_12000bpsL_Train[]			= "%TT49               ";
CUB ENG_V17_12000bpsS_Train[]			= "%TT4A               ";
CUB ENG_V17_14400bpsL_Train[]			= "%TT4B               ";
CUB ENG_V17_14400bpsS_Train[]			= "%TT4C               ";
CUB ENG_VFC_Modulation[]				= "%TT5\0               ";
CUB ENG_V34_Modulation[]				= "%TT6\0               ";
/*↑この順番で並べて記述*/

/* Gurad Tone */
/*↓この3個はこの順番で並べて記述*/
CUB ENG_GT1800hz[]						= "Guard Tone 1800 Hz  ";
CUB ENG_GT550hz[]						= "Guard Tone 550 Hz   ";
CUB ENG_NoGuardTone[]					= "No Guard Tone       ";

/* Mode */
/*↓この2個はこの順番で並べて記述*/
CUB ENG_OriginateMode[]					= "Originate Mode      ";
CUB ENG_AnswerMode[]					= "Answer Mode         ";

/* Data Rate */
/*↓この12個はこの順番で並べて記述*/
CUB ENG_2400bps[]						= "2400 bps            ";
CUB ENG_4800bps[]						= "4800 bps            ";
CUB ENG_7200bps[]						= "7200 bps            ";
CUB ENG_9600bps[]						= "9600 bps            ";
CUB ENG_12000bps[]						= "12000 bps           ";
CUB ENG_14400bps[]						= "14400 bps           ";
CUB ENG_16800bps[]						= "16800 bps           ";
CUB ENG_19200bps[]						= "19200 bps           ";
CUB ENG_21600bps[]						= "21600 bps           ";
CUB ENG_24000bps[]						= "24000 bps           ";
CUB ENG_26400bps[]						= "26400 bps           ";
CUB ENG_28800bps[]						= "28800 bps           ";
CUB ENG_31200bps[]						= "31200 bps           ";
CUB ENG_33600bps[]						= "33600 bps           ";

/* Symbol Rate */
/*↓この6つはこの順番で並べて記述*/
CUB ENG_2400baud[]						= "2400 baud           ";
CUB ENG_2800baud[]						= "2800 baud           ";
CUB ENG_3000baud[]						= "3000 baud           ";
CUB ENG_3200baud[]						= "3200 baud           ";
CUB ENG_3429baud[]						= "3429 baud           ";

/* Second Channel */
/*↓この2つはこの順番で並べて記述*/
CUB ENG_Disable[]						= "Disable             ";
CUB ENG_Enable[]						= "Enable              ";

/* Upper Band Edge */
/*↓この11個はこの順番で並べて記述*/
CUB ENG_V34BandEdge0Db[]				= "a = 0[dB]           ";
CUB ENG_V34BandEdge2Db[]				= "a = 2[dB]           ";
CUB ENG_V34BandEdge4Db[]				= "a = 4[dB]           ";
CUB ENG_V34BandEdge6Db[]				= "a = 6[dB]           ";
CUB ENG_V34BandEdge8Db[]				= "a = 8[dB]           ";
CUB ENG_V34BandEdge10Db[]				= "a = 10[dB]          ";
CUB ENG_V34BandEdgeG1Db[]				= "b=0.5[dB], c=1.0[dB]";
CUB ENG_V34BandEdgeG2Db[]				= "b=1.0[dB], c=2.0[dB]";
CUB ENG_V34BandEdgeG3Db[]				= "b=1.5[dB], c=3.0[dB]";
CUB ENG_V34BandEdgeG4Db[]				= "b=2.0[dB], c=4.0[dB]";
CUB ENG_V34BandEdgeG5Db[]				= "b=2.5[dB], c=5.0[dB]";
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	ＦＡＸワープ
 *----------------------------------*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modified by SMuratec L.Z.W 2003/09/01 */
CUB	ENG_FaxWarpMode[]					= "    FAX Warp        ";
#else
CUB	ENG_FaxWarpMode[]					= "  FAX Warp          ";
#endif /* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB	ENG_EnterFaxWarpMode[]				= "   Enter FAX Warp   ";
CUB	ENG_PrintFaxWarpMode[]				= "   Print FAX Warp   ";
CUB	ENG_SetFaxWarpMode[]				= "   Set FAX Warp     ";
CUB	ENG_EnterFaxWarp[]					= "Enter FAX Warp      ";
CUB	ENG_PrintFaxWarp[]					= "Print FAX Warp      ";
CUB	ENG_SetFaxWarp[]					= "FAX Warp:\0          ";
CUB	ENG_WarpSelectNumber[]				= "Select FAX Warp Num.";
CUB	ENG_WarpTime[]						= "Enter Time          ";
CUB	ENG_WarpWeek[][21]					= {
#if defined(HINOKI3)	/* 新ＬＣＤドライバー対応 by Y.Kano 2005/01/21 */
  										  "\x28\x97\x29                 ",
										  "\x28\x91\x29                 ",
										  "\x28\x92\x29                 ",
										  "\x28\x93\x29                 ",
										  "\x28\x94\x29                 ",
										  "\x28\x95\x29                 ",
										  "\x28\x96\x29                 ",
										  "\x28\x2A\x29                 ",
#else	/* defined(HINOKI3) 以外 */
										  "Sun                 ",
										  "Mon                 ",
										  "Tue                 ",
										  "Wed                 ",
										  "Thu                 ",
										  "Fri                 ",
										  "Sat                 ",
										  " *                  ",
#endif	/* End of defined(HINOKI3) */
};
CUB	ENG_SelectWarpRxDocPrint[][21]		= {
										  "   Auto Print : OFF ",
										  "   Auto Print : ON  ",
};

/* ＷＡＲＰ転送先ワーディング追加 By O.Kimoto 1999/02/08 */
CUB	ENG_WarpAltNumber[]					= "Forwarding No.      ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */

#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	ナンバーディスプレイ
 *----------------------------------*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modified by SMuratec L.Z.W 2003/09/01 */
CUB	ENG_NumberDisplayMode[]				= "    Number Display  ";
#else
CUB	ENG_NumberDisplayMode[]				= "  Number Display    ";
#endif /* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	ENG_EnterNumberDisplayMode[]		= "   Enter Number Disp";
CUB	ENG_PrintNumberDisplayMode[]		= "   Print Number Disp";
CUB	ENG_SetNumberDisplayMode[]			= "   Set Number Disp. ";
CUB	ENG_EnterNumberDisplay[]			= "Enter Number Display";
CUB	ENG_PrintNumberDisplay[]			= "Print Number Display";
CUB	ENG_SetNumberDisplay[]				= "Number Disp. :\0     ";
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* By H.Fujimura 1999/01/07 */
CUB	ENG_Set_ND_Warp[]					= "ND Warp:\0           ";
 #endif
CUB	ENG_ND_SelectNumber[]				= "Select ND Number    ";
CUB	ENG_ND_TelMode[][21]				= {
										  "Connection :\0       ",
										  "             OFF    ",
/*										  "             PHONE1 ",*/
										  "             PHONE2 ",
};
CUB	ENG_ND_NoNotice[]					= "NO Notice           ";
CUB	ENG_ND_OutOfDisp[]					= "Out Of Display      ";
CUB	ENG_ND_PublicTel[]					= "Public Telephone    ";
CUB	ENG_ND_Parameter[]					= "Number Display Param";

CUB	ENG_Print_ND_JournalMode[]			= "   ND Journal       ";
CUB	ENG_Print_ND_Journal[]				= "ND Journal          ";
#endif

/*----------------------------------*
 *	通信確認
 *----------------------------------*/
CUB	ENG_ConfirmReport[]					= "Conf.Report    :\0   ";

/*----------------------------------*
 *	オペレーションプロテクト
 *----------------------------------*/
CUB	ENG_OperationProtected[]			= "Operation Protected ";

#if (PRO_COPY_FAX_MODE == ENABLE)
/*----------------------------------*
 *	コピーモード
 *----------------------------------*/
CUB	ENG_ChangeManual[]					= "      Tray \x7E Enter  ";	/* \x7E = → */
#endif

#if (PRO_FBS == ENABLE)
/*----------------------------------*
 *	ブック送信
 *----------------------------------*/
CUB	ENG_SetBookTxDocumentSize[]			= "Enter Scan Size     ";
CUB	ENG_SetBookTxNextDocument[]			= "Set Next Document   ";

CUB	ENG_NextBookDocScanStart[]			= "Start Scan \x7E Next   ";	/* \x7E = → *//* modified by honda 1997/10/01 Scan Start \x7E NextDoc */
CUB	ENG_NextBookDocTxStart[]			= "Tx Start \x7E Start    ";	/* \x7E = → *//* \x7E Start */
CUB	ENG_NextBookDocScanEnd[]			= "End Scan \x7E Enter    ";	/* \x7E = → *//* modified by honda 1997/10/01 Scan End \x7E Enter */
#endif

/* 紙サイズ（R → 0x01(OPR_PAPER_SIZE_R)で定義して下さい） */
CUB	ENG_PaperSize_None[]				= "None\0";
CUB	ENG_PaperSize_A5[]					= "A5\0  ";
CUB	ENG_PaperSize_Letter[]				= "Ltr\0 ";
#if defined(USAOKI)	/* 1998/02/04 Y.Matsukuma */
CUB	ENG_PaperSize_A4[]					= "LT\0  ";
#else
CUB	ENG_PaperSize_A4[]					= "A4\0  ";
#endif
CUB	ENG_PaperSize_Legal[]				= "Legl\0";
CUB	ENG_PaperSize_B5R[]					= "B5\x01\0 ";
CUB	ENG_PaperSize_B4[]					= "B4\0  ";
CUB	ENG_PaperSize_A3[]					= "A3\0  ";
CUB	ENG_PaperSize_A4R[]					= "A4\x01\0 ";
CUB	ENG_PaperSize_LetterR[]				= "Ltr\x01\0";
CUB	ENG_PaperSize_F4[]					= "F4\0  ";
CUB	ENG_PaperSize_A5R[]					= "A5\x01\0 ";
CUB	ENG_PaperSize_Postcard[]			= "Post\0";
CUB	ENG_PaperSize_LD[]					= "Ld\0  ";
CUB	ENG_PaperSize_GLetterR[]			= "GLtr\x01";
CUB	ENG_PaperSize_ExecutiveR[]			= "Exe\x01\0";
/*  #if (PRO_KEYPANEL == PANEL_POPLAR_B)  *//* modified by honda 1997/11/14 */
/*   #if defined(JPN)  */
/*	CUB	ENG_PaperSize_InvoiceR[]			= "Inv\x01\0";  */
/*   #else  */
CUB	ENG_PaperSize_HalfLetterR[]			= "HLtr\x01";  /* added by honda 1997/10/04 */
/*   #endif  */
/*  #else  */
/*	CUB	ENG_PaperSize_InvoiceR[]			= "Inv\x01\0";  */
/*  #endif  */
CUB	ENG_PaperSize_GLegal[]				= "GLegl";
CUB	ENG_PaperSize_GLetter[]				= "GLtr\0";
CUB	ENG_PaperSize_Card[]				= "Card\0";
CUB	ENG_PaperSize_Executive[]			= "Exe\0 ";
CUB	ENG_PaperSize_B5[]					= "B5\0  ";
CUB	ENG_PaperSize_C5[]					= "C5\0  ";
CUB	ENG_PaperSize_HalfLetter[]			= "HLtr\0";
CUB	ENG_PaperSize_Invoice[]				= "Inv\0 ";
CUB	ENG_PaperSize_B6[]					= "B6\0  ";
CUB	ENG_PaperSize_DL[]					= "DL\0  ";
CUB	ENG_PaperSize_CM10[]				= "CM10\0";
CUB	ENG_PaperSize_A6[]					= "A6\0  ";
CUB	ENG_PaperSize_Monarch[]				= "Mnc\0 ";
CUB	ENG_PaperSize_35[]					= "3x5\0 ";
CUB	ENG_PaperSize_User[]				= "User\0";
CUB	ENG_PaperSize_OHP[]					= "OHP\0 ";	/* このﾜｰﾃﾞｨﾝｸﾞは、SYS_DOC.Hの定義とは無関係です */
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)	/* By S.Fukui Jan.23,1998 */
CUB	ENG_PaperSize_Auto[]				= "Auto\0";	/* このﾜｰﾃﾞｨﾝｸﾞは、SYS_DOC.Hの定義とは無関係です */
#endif
#if (PRO_PITNEYBOWES == ENABLE)
CUB	ENG_PaperSize_Ledger[]				= "LDGR\0";	/* 原稿サイズ表示ＰＢ用 By S.Fukui Aug.25,1998 */
CUB	ENG_PaperSize_LtLg[]				= "LTLG\0";	/* 原稿サイズ表示ＰＢ用 (For Letter/Legal) By S.Fukui Aug.25,1998 */
#endif

/*----------------------------------*
 *	サービスファンクション
 *----------------------------------*/
/* マシンパラメータ */
CUB	ENG_SF_ParameterSet[]				= "Set Parameters      ";
CUB	ENG_SF_ParameterClear[]				= "Clear Parameters    ";

/* メモリースイッチ */
CUB	ENG_SF_MemorySwitchSet[]			= "Set Memory Switch   ";
CUB	ENG_SF_MemorySwitchClear[]			= "Clear Memory Switch ";

/* ユーザ設定クリア */
CUB	ENG_SF_BackUpFileClear[]			= "Clear User Settings ";

/* オールラムクリア */
CUB	ENG_SF_AllClear[]					= "All RAM Clear       ";

/* 機種固有スイッチ */
CUB	ENG_SF_UniqSwitchSet[]				= "Set Uniq Switch     ";
CUB	ENG_SF_UniqSwitchClear[]			= "Clear Uniq Switch   ";

/* 保守用スイッチ */
CUB	ENG_SF_MaintenanceSet[]				= "Set Maintenance     ";
CUB	ENG_SF_MaintenanceClear[]			= "Clear Maintenance   ";

/* テストファンクション -> このワーディングの並びはかえてはいけない */
#if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1997/10/02 Y.Matsukuma */
CUB ENG_SF_LifeMonitor[]				= "Life Monitor        ";
CUB ENG_SF_LifeMonitorClear[]			= "Clear Life Monitor  ";
CUB ENG_SF_TestPatternPrint[]			= "Printer Test        ";
CUB ENG_SF_StampTest[]					= "Stamp Test          ";
CUB ENG_SF_Shading[]					= "Set Background Level";
#elif (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ＨＩＮＯＫＩは原稿排出テストは有りません by O.Kimoto 1999/02/09 */
CUB	ENG_SF_LifeMonitor[]				= "Life Monitor        ";
CUB	ENG_SF_TestPatternPrint[]			= "Printer Test        ";
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/12/26 */
CUB	ENG_SF_PS1_PB4_Threshold[]			= "PS1,PB4 Setting Mode";/* Add by Y.Kano 2003/12/26 */
 #else	/* HINOKIは済みスタンプを表示 */
CUB	ENG_SF_StampTest[]					= "Stamp Test          ";
 #endif
CUB	ENG_SF_Shading[]					= "Set Background Level";
#else
CUB	ENG_SF_LifeMonitor[]				= "Life Monitor        ";
CUB	ENG_SF_TestPatternPrint[]			= "Printer Test        ";
CUB	ENG_SF_StampTest[]					= "Stamp Test          ";
CUB	ENG_SF_DocumentFeedOutTest[]		= "Feeder Test         ";
CUB	ENG_SF_Shading[]					= "Set Background Level";
#endif

/* ライフモニター */
CUB	ENG_SF_BoardNumber[]				= "Board Number?       ";
CUB	ENG_SF_LifeReadingPage[]			= "Pages Scanned       ";
CUB	ENG_SF_LifePrintingPage[]			= "Pages Printed       ";
CUB	ENG_SF_LifeTxPage[]					= "Pages Transmitted   ";
CUB	ENG_SF_LifeDrumReplaceCount[]		= "Drum Replaced Count ";	/* <- Replace By M.Tachibana 1997/10/29 */
CUB	ENG_SF_LifeDrumLifeCount[]			= "Drum Life           ";
CUB	ENG_SF_LifeTonerReplaceCount[]		= "Toner Replaced Count";
CUB	ENG_SF_LifeTonerLifeCount[]			= "Toner Life          ";
CUB	ENG_SF_LifeFuserReplaceCount[]		= "Fuser Replaced Count";
CUB	ENG_SF_LifeFuserLifeCount[]			= "Fuser Life          ";
CUB	ENG_SF_LifeTransferReplaceCount[]	= "Transfer Rplcd Count";
CUB	ENG_SF_LifeTransferLifeCount[]		= "Transfer Life       ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/07 */
CUB	ENG_SF_CPU_Revision[]				= "CPU Version         ";
CUB	ENG_SF_ROM_Revision[]				= "ROM Version         ";
#endif

/* テストパターン */
CUB	ENG_SF_Pattern[]					= "Pattern           \0 ";

/* 工場ファンクション */
CUB	ENG_SF_FactoryFunction[]			= "Factory Function    ";

CUB	ENG_SF_LEDTest[]					= "LED Test            ";
CUB	ENG_SF_LCDTest[]					= "LCD Test            ";
CUB	ENG_SF_PanelTest[]					= "Key Panel Test      ";

CUB	ENG_SF_SRAMCheck[]					= "SRAM Check          ";
CUB	ENG_SF_DRAMCheck[]					= "DRAM Check          ";
CUB	ENG_SF_RTCTest[]					= "RTC Test            ";
CUB	ENG_SF_RS232CTest[]					= "RS232C Test         ";
CUB	ENG_SF_CassetteCheck[]				= "Cassette Test       ";

/* キー */
/*このワーディングの順番はキーコードの順番に一致させなくてはならない */
CUB	ENG_SF_Receive[]					= "Auto Rx             ";
CUB	ENG_SF_Hook[]						= "Monitor/Call        ";
CUB	ENG_SF_Hold[]						= "Hold                ";
CUB	ENG_SF_Mode[]						= "Mode                ";
CUB	ENG_SF_Contrast[]					= "Contrast            ";
CUB	ENG_SF_Program[]					= ">                   ";
CUB	ENG_SF_CursorLeft[]					= "<                   ";
CUB	ENG_SF_Set[]						= "Enter               ";
CUB	ENG_SF_DelayedCheck[]				= "Review              ";	/* <- Confirm By S.Fukui Nov.29,1997 */ 
CUB	ENG_SF_Clear[]						= "Cancel              ";
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1997/08/20 Y.Matsukuma */
CUB	ENG_SF_DialMark[]					= "Dialing Options     ";
#else
CUB	ENG_SF_Sort[]						= "Sort Copy           ";
#endif
CUB	ENG_SF_Broadcast[]					= "Broadcast           ";	/* 注）通信確認でも使用（このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです） */
CUB	ENG_SF_Special[]					= "Com.Option          ";
CUB	ENG_SF_Group[]						= "Group               ";
CUB	ENG_SF_Speed[]						= "Speed               ";
CUB	ENG_SF_MemoryTx[]					= "Memory Transmit     ";
CUB	ENG_SF_Stop[]						= "Stop                ";
CUB	ENG_SF_Start[]						= "Start               ";
CUB	ENG_SF_Copy[]						= "Copy                ";	/* 注）ｺﾋﾟｰ表示でも使用 */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1997/08/20 Y.Matsukuma */
CUB	ENG_SF_Redial[]						= "Redial              ";
CUB	ENG_SF_Stamp[]						= "Stamp               ";
CUB	ENG_SF_Mercury[]					= "Prefix              ";  /* アンズＬも新ﾜｰﾃﾞｨﾝｸﾞ 1998/02/25 Y.Matsukuma */
CUB	ENG_SF_Flash[]						= "Flash               ";
#else
CUB	ENG_SF_PaperSelect[]				= "Paper Size?         ";
CUB	ENG_SF_Stamp[]						= "Stamp               ";
CUB	ENG_SF_Reduction[]					= "Reduct %            ";
CUB	ENG_SF_Magnification[]				= "Enlarge %           ";
#endif
CUB	ENG_SF_CopyFax[]					= "Copy/Fax            ";
CUB	ENG_SF_BookDocSize[]				= "Book Doc Size       ";
CUB	ENG_SF_CopyReset[]					= "Clear All           ";
CUB	ENG_SF_Tone[]						= "Tone                ";	/* 追加 97/11/29 T.Fukumoto */
#if defined(HINOKI3)	/* ONETOUCH_30_KEYがプレフィックスキーに変わったので by K.Watanabe 2004/10/26 */
CUB	ENG_SF_Prefix[]						= "Prefix              ";
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	ENG_SF_Receive_S[]					= "Auto Rx             ";
CUB	ENG_SF_Hook_S[]						= "Monitor/Call        ";
CUB	ENG_SF_Contrast_S[]					= "Contrast            ";
#endif

/* 回線テスト */
CUB	ENG_SF_LineTest[]					= "Line Test           ";	/* 未使用 */

CUB	ENG_SF_PhoneTest[]					= "Relay Test          ";
CUB	ENG_SF_TonalTest[]					= "Tonal Test          ";
CUB	ENG_SF_DTMF_Test[]					= "DTMF Test           ";

/* リレー */
CUB	ENG_SF_RelayTest1[]					= " CML  H  L  S  DP   ";
CUB	ENG_SF_RelayTest2[]					= " C24                ";
#if (PRO_MODEM == R288F)	/* By H.Fujimura 1999/01/07 */
 #if defined (JPN)
CUB	ENG_SF_R288F_RelayTest1[]			= " CML  H     L   S   ";
CUB	ENG_SF_R288F_RelayTest2[]			= " C24  TONE  BZ  RI  ";
 #else	/* ＴＷＮ用 by H.Hirao 1999/02/02 */
CUB	ENG_SF_R288F_RelayTest1[]			= " CML  H     DP  S   ";
CUB	ENG_SF_R288F_RelayTest2[]			= " C24        BZ      ";
 #endif
#endif

/* トーナル */
CUB	ENG_SF_FSK[]						= "FSK";
CUB	ENG_SF_White[]						= "White\0    ";
CUB	ENG_SF_Black[]						= "Black\0    ";
CUB	ENG_SF_Pix[]						= "     BPS   W:B =    ";

/* ミラーキャリッジ輸送モードセット */
CUB	ENG_SF_MirrorCarrigeModeSet[]		= "Mirror Locked   :\0  ";	/* <- "Mirror Position" By S.Fukui Feb.8,1998 */

/* サービスレポート */
CUB	ENG_SF_ServicePrint[]				= "Service Report      ";

CUB	ENG_SF_DTMF[]						= "DTMF";
CUB	ENG_SF_DTMFRow[]					= "ROW";
CUB	ENG_SF_DTMFColum[]					= "COL";

/* カセットテスト */
CUB	ENG_SF_CassetteOpen[]				= "Cassette Open";
CUB	ENG_SF_NoPaper[]					= "No Paper";
CUB	ENG_SF_SideCoverOpen[]				= "Side Cover Open";
CUB	ENG_SF_NoUnit[]						= "No Unit";

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ライフモニタークリア */
CUB	ENG_SF_LifeMonitorClear[]			= "Clear Life Monitor  ";
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
/* ライフモニタクリアパスコード */
CUB	ENG_SF_ServiceCode[]				= "Set Service Code    ";
CUB	ENG_SF_EnterServiceCode[]			= "Enter Service Code  ";
#endif

/* プリンタメンテナンス */
CUB	ENG_SF_ReplaceCountSet[]			= "Set Replace Counter ";
CUB	ENG_SF_ServiceCall[]				= "Service Call        ";
CUB	ENG_SF_FuserReplace[]				= "Replace Fuser       ";
CUB	ENG_SF_TransferReplace[]			= "Replace Transfer    ";
CUB	ENG_SF_ServiceCallCount[]			= "Service Call     :  ";
CUB	ENG_SF_HeatTrouble[]				= "Heater Error        ";
CUB	ENG_SF_HeatDisconnection[]			= "ThermistorDisconnect";
CUB	ENG_SF_HeatShortCircuit[]			= "Thermistor Short    ";
CUB	ENG_SF_InsideFanTrouble[]			= "Inside Fan Error    ";	/* <- Fan Motor Err By M.Tachibana 1997/10/29 */
CUB	ENG_SF_RxMotorTrouble[]				= "Rx Motor Error      ";	/* <- Rx Motor Err By M.Tachibana 1997/10/29 */
CUB	ENG_SF_DrumTrouble[]				= "Drum Fuse Error     ";  /* 暫定 by S.Fukui Sep.19,1997 */
CUB	ENG_SF_PsFanTrouble[]				= "PS Fan Error        ";  /* 暫定 by S.Fukui Oct.24,1997 *//* <- Cooler Fan By M.Tachibana 1997/10/29 */
CUB	ENG_SF_HvFuseDisconnect[]			= "H-VltFuse Disconnect";  /* 暫定 by S.Fukui Oct.24,1997 */

/* 消耗品発注機能 */	/* 暫定 By S.Fukui Oct.21,1997 */
CUB	ENG_SF_ReceiverCustomerCode[]		= "DIST CODE           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* (JPN) */
CUB	ENG_SF_ReceiverCompany[]			= "DIST NAME           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	ENG_SF_SenderCustomerCode[]			= "CUST CODE           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	ENG_SF_SenderCompany[]				= "CUST NAME           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
CUB	ENG_SF_SenderSection[]				= "Address1            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* JPN以外は Address とする By S.Fukui Nov.15,1997 */
CUB	ENG_SF_SenderSection2[]				= "Address2            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* JPN以外は Address とする By S.Fukui Nov.15,1997 */
#else
CUB	ENG_SF_SenderSection[]				= "Section             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
#endif
CUB	ENG_SF_SenderTelNumber[]			= "Customer's Tel      ";
CUB	ENG_SF_SerialNumber[]				= "Serial No.          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	ENG_SF_Date[]						= "Installation Date   ";
CUB	ENG_SF_PrintOrderForm[]				= "Print Order Sheet   ";
#if defined(US1)
CUB	ENG_SF_ToCompanyFaxNumber[]			= "Dist. Fax No.       ";	/* orderbythonda1998/11/11 */
CUB	ENG_SF_ToCompanyTelNumber[]			= "Dist. Tel No.       ";	/* orderbythonda1998/11/11 */
#endif

/* メモリダンプ */
CUB	ENG_SF_MemoryDump[]					= "Memory Dump         ";  /* wording by t.honda 1997/09/20 ﾒﾓﾘﾀﾞﾝﾌﾟ */
CUB	ENG_SF_MemoryDumpAddress[]			= "Address    :        ";  /* wording by t.honda 1997/09/20 ｱﾄﾞﾚｽ */
CUB	ENG_SF_MemoryDumpLength[]			= "Data Length:        ";  /* modified by honda 1997/10/01 DataLength ﾃﾞｰﾀﾁｮｳ */

/* ＤＲＡＭクリア */
CUB	ENG_SF_ClearDRAM[]					= "DRAM Clear          ";

/* オプションデータ初期化 */
CUB	ENG_SF_OptionDataInitial[]			= "Option Data Initial ";

/* 消耗品発注データクリア */
#if (PRO_PRINT_TYPE == THERMAL)	/* By H.Fujimura 1999/01/07 */
CUB	ENG_SF_MntDataClear[]				= "Mecha. No Clear     ";
#else
CUB	ENG_SF_OrderDataClear[]				= "Reset Order Sheet   ";	/* 暫定 By M.Tachibana 1997/12/22 */
#endif

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/20 */
/* T30モニター番号 */
CUB	ENG_SF_T30MonitorNumber[]			= "T30 No.:        \0   ";
#endif

CUB	ENG_SF_OK[]							= "OK                  ";
CUB	ENG_SF_NG[]							= "NG\0                 ";

/*----------------------------------*
 *	ＬＣＤ・リストでの頭文字表示
 *----------------------------------*/
#if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
CUB	ENG_HeadCharacter_Speed				= 'S';
CUB	ENG_HeadCharacter_Command			= 'C';
CUB	ENG_HeadCharacter_Batch				= 'B';
CUB	ENG_HeadCharacter_Polling			= 'P';
CUB	ENG_HeadCharacter_Tray				= 'T';
#endif

#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
/*----------------------------------*
 *	通信結果表示
 *----------------------------------*/
CUB	ENG_CommResultList[]				= "Communication Result";/*20*/
CUB	ENG_Tx[]							= "Tx\0                 ";/*2*/
CUB	ENG_Rx[]							= "Rx\0                 ";/*2*/
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC 設定表示 */
CUB ENG_RemoteTxSetting[]				= "Remote Rx";
CUB ENG_RemoteTxSettingOff[]			= "OFF";
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/*----------------------------------*
 *	音量調整表示
 *----------------------------------*/
/* 音量調整選択の表示（上段） */
CUB	ENG_BuzzerVolume[]					= "01.Key Touch Volume ";/*20*/
CUB	ENG_MonitorVolume[]					= "02.Monitor Volume   ";/*20*/
CUB	ENG_RingerControl[]					= "03.ﾁｬｸｼﾝ ﾍﾞﾙ        ";/*20*/
CUB	ENG_RingerControlOn[]				= "ﾁｬｸｼﾝ ﾍﾞﾙ  : ON     ";/*20*/
CUB	ENG_RingerControlOff[]				= "ﾁｬｸｼﾝ ﾍﾞﾙ  : OFF    ";/*20*/
/* 選択を促す表示（点滅する表示 ) */
CUB	ENG_BuzzerVolumeEnter[]				= "            \x7F/\x7E/Set ";/*20*/
CUB	ENG_ShadingWord[]					= "Please Supply Paper ";/* Added by SMuratec K.W.Q 2003/08/11 */
CUB	ENG_ManualCutterMode[]				= "Excute Manual Cutter";/* Add by Y.Kano 2003/10/15 */
CUB	ENG_SF_PS2AdjustMode[]				= "PS2 Adjust Mode     ";/* Add by Y.Kano 2003/10/17 */
CUB	ENG_PS2VolumueFullLight_1[]			= "Move To PS2 Volumue ";/* Add by Y.Kano 2003/10/17 */
CUB	ENG_PS2VolumueFullLight_2[]			= "Lighting            ";/* Add by Y.Kano 2003/10/17 */
CUB	ENG_PS2VolumueTitle[]				= "     PS2 Volumue    ";/* Add by Y.Kano 2003/10/17 */
CUB	ENG_PS2_OK[]						= "     ** OK **       ";/* Add by Y.Kano 2003/10/18 */
CUB ENG_PS2_Complete[]					= " **   Complete   ** ";/* Add by Y.Kano 2003/10/18 */
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* チェッカー表示の追加 by SMuratec L.Z.W 2003/10/23 */
CUB ENG_Character[]						= "Character           ";
CUB	ENG_SF_PS1_PB4_CheckMode[]			= "PS1,PB4 Check Mode  ";/* Add by Y.Kano 2003/12/18 */
CUB	ENG_Stop[]							= "              Stop  ";/* Add by Y.Kano 2003/12/18 */
CUB	ENG_PleaseNonPaper[]				= "Please Remove Paper ";/* Add by Y.Kano 2003/12/18 */
CUB	ENG_SF_PS1_PB4_Error[]				= "PS1,PB4 Sensor Error";/* Add by Y.Kano 2003/12/26 */
CUB	ENG_SF_PS1_Error[]					= "PS1 Sensor Error    ";/* Add by Y.Kano 2003/12/26 */
CUB	ENG_SF_PB4_Error[]					= "PB4 Sensor Error    ";/* Add by Y.Kano 2003/12/26 */
#endif

#if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)	/* ＰＳ１、ＰＳ２、ＰＢ４閾値自動調整モード by Y.Kano 2004/10/06 */
CUB ENG_SF_PS1_PS2_PB4_AdjustMode[]		= "PS1,PS2,PB4 Adjust  ";
CUB ENG_PleaseNonPaper[]				= "Please Remove Paper ";
CUB	ENG_SF_PS1_PS2_PB4_Error[]			= "PS1,PS2,PB4 Error   ";
CUB	ENG_SF_PS1_PS2_Error[]				= "PS1,PS2 Error       ";
CUB	ENG_SF_PS1_PB4_Error[]				= "PS1,PB4 Error       ";
CUB	ENG_SF_PS1_Error[]					= "PS1 Error           ";
CUB	ENG_SF_PS2_PB4_Error[]				= "PS2,PB4 Error       ";
CUB	ENG_SF_PS2_Error[]					= "PS2 Error           ";
CUB	ENG_SF_PB4_Error[]					= "PB4 Error           ";
CUB	ENG_Stop[]							= "               Stop ";
CUB	ENG_SensorTest[]					= "Sensor Test         ";
#endif

#if defined(STOCKHM2) || (PRO_JOURNAL_VER_UP == ENABLE)	/* Added by SMuratec C.P 2004/06/07 *//* by K.Watanabe 2004/10/15 */
/*----------------------------------*
 *	ジャーナルプリント
 *----------------------------------*/
CUB ENG_JournalTx[]						= "[01] Tx Journal     ";
CUB ENG_JournalRx[]						= "[02] Rx Journal     ";
CUB ENG_JournalTxRx[]					= "[03] TxRx Journal   ";
#endif

#if defined(STOCKHM2)	/* Added by SMuratec C.P 2004/06/07 */
CUB	ENG_CommConfirm[]					= "Comm Confirm        ";
CUB ENG_FunctionEnter[]					= "               /set ";
CUB ENG_InkConfirm[]					= "Ink Ribbon Confirm  ";
#endif

/** トーン検出設定 */
#if defined(STOCKHM2) || defined(HINOKI3)	/* 復活 by SMuratec 夏 2004/7/12*/ /* Add by Y.Kano 2004/11/25 */
CUB ENG_SetToneDetectMode[]				= "   Set Tone Detect  ";
CUB ENG_DialToneOn[]					= "Dial Tone:      \0   ";
CUB	ENG_Off[]							= "Off                 ";
CUB ENG_On[]							= "On                  ";
#endif

#if defined(STOCKHM2) /* Add by SMuratec C.P 2004/07/23 */
CUB ENG_VolumeControl[]					= "     Volume Control ";
#endif

#if (PRO_RTC_RX5C338A == ENABLE)
CUB ENG_RTC_Init[]						= "RTCｲﾆｼｬﾗｲｽﾞ         ";
#endif

CUB	ENG_WordingTail[]					= "\0";	/* ﾜｰﾃﾞｨﾝｸﾞｻｲｽﾞ計算用(H8の様にﾜｰﾃﾞｨﾝｸﾞを縦に並べる場合必要) */
#undef	CUB
