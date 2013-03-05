/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_WRD0.C
*	Author		: 渡辺一章
*	Date		: 1996/10/23
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ＬＣＤ用固定文字列（窓にあたるもの）
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"

#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/17 */
/* POPLAR_B NTT対応でワーディングファイルを新規に作成したので、ここで対応します */
#include	"\src\atlanta\opr\ank\wording\ntt_wrd0.c"

#else
#if (PRO_CPU == SH7043)
	/*
	** RISCコンパイラー用のデータセクションを設定します。
	** OPR_WRD0はCOPR_WRD0の名前が自動的に設定されます。
	** 86系のセグメント名に相当する。
	** By S.Kawasaki 1996/03/11
	*/
	#pragma	section	OPR_WRD0
#endif

#define	CUB		CONST UBYTE

#if (PRO_CPU == SH7043)
CUB D2W_WordingTop[]					= "\0"; /* 各国ワーディング先頭位置認識用 1996/07/04 T.Nose */
#endif

CUB	D2W_WordingHead[]					= "\0";	/* ﾜｰﾃﾞｨﾝｸﾞｻｲｽﾞ計算用(H8の様にﾜｰﾃﾞｨﾝｸﾞを縦に並べる場合必要) */
CUB	D2W_Null[]							= "\0";

/* 待機モード */
CUB	D2W_TelReady[]						= "Tel Ready           ";
CUB	D2W_FaxReady[]						= "Fax Ready           ";
CUB	D2W_FaxTelReady[]					= "Fax/Tel Ready       ";
CUB	D2W_TelFaxReady[]					= "Tel/Fax Ready       ";
CUB	D2W_AnsFaxReady[]					= "Ans/Fax Ready       ";
CUB	D2W_DialInReady[]					= "Dial In Ready       ";	/* (JPN) */
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1997/12/26 */
CUB	D2W_ScannerTransportReady[]			= "Mirror Locked       ";
#endif

/* コピーモードの表示 */
#if (PRO_COPY_FAX_MODE == ENABLE)
CUB	D2W_CopyReady[]						= "Copy Ready    Num:  ";
CUB	D2W_ManualCopyReady[]				= "Copy Tray     Num:  ";
CUB	D2W_CopyImpossibleReady[]			= "              Num:  ";
CUB	D2W_InputCopyMagnifi[]				= "Enter Reduce        ";
CUB	D2W_CopyMagnifiError[]				= "Enter 50-200%       ";
CUB	D2W_ConfirmCopyMagnifi[]			= "999% Are You Sure   ";	/* 倍率は必ず999を定義（国別の表示位置対応） */
#endif

/* コマンド登録中の表示（上段） */
CUB	D2W_EnterFaxNumber[]				= "Enter Fax Number    ";
CUB	D2W_InputGroupNumber[]				= "Enter Group No.     ";
CUB	D2W_InputSpeedDialNumber[]			= "Enter Speed-Dial No.";
CUB	D2W_PressStart[]					= "Press Start         ";
CUB	D2W_PressStartAgain[]				= "Press Start Again   ";
CUB	D2W_PressEnterKey[]					= "Press Enter Key     ";

/* コピー部数入力中の表示（上段） */
CUB	D2W_SetCopyUnits[]					= "# of pgs. to copy   ";	/* POPLAR_B以外 */

/* 選択を促す表示（点滅する表示 ) */
CUB	D2W_ProgramEnter[]					= "      Program/Enter ";
CUB	D2W_ProgramClear[]					= "      Program/Cancel";
#if (PRO_CIPHER == ENABLE)
CUB	D2W_EnterClesr[]					= "        Enter/Cancel";
#endif
CUB	D2W_EnterStop[]						= "         Enter/Stop ";
CUB	D2W_CopyStop[]						= "          Copy/Stop ";	/* POPLAR_B以外 */
CUB	D2W_StartStop[]						= "         Start/Stop ";
CUB	D2W_SpecialCommunicationEnter[]		= "  Comm.Option/Enter ";
CUB	D2W_ReviewStop[]					= "       Review/Stop  ";
CUB	D2W_CheckProgramEnter[]				= "Check Program/Enter ";
CUB	D2W_CheckProgramClear[]				= "Check Program/Cancel";
CUB	D2W_CheckStartStop[]				= "Check    Start/Stop ";
#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
CUB	D2W_CommunicationConfirmEnter[]		= "       Review/Enter ";/*20*/
#endif

/*----------------------------------*
 *	応用機能
 *----------------------------------*/
/* 機能選択中 */
CUB	D2W_SetDelayedTransmission[]		= "  Delayed           ";
CUB	D2W_SetSecureTransmission[]			= "  S Mail Tx         ";
CUB	D2W_SetRelayTransmission[]			= "  Relay Tx          ";
CUB	D2W_SetPolling[]					= "  Polling           ";
CUB	D2W_SetBatchTransmission[]			= "  Batch Tx          ";
CUB	D2W_SetContPolling[]				= "  Cont Polling      ";
CUB	D2W_SetFcodeTransmission[]			= "  F-Code Tx         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */
CUB	D2W_SetFcodePolling[]				= "  F-Code Polling    ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */
CUB	D2W_SetCipherTransmission[]			= "  Scrambling Tx     ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */

/* 各機能の詳細データ設定中（上段） */
CUB	D2W_DelayedTransmission[]			= "Delayed             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	D2W_SecureTransmission[]			= "S Mail Tx           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	D2W_RelayTransmission[]				= "Relay Tx            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	D2W_PollingCommunication[]			= "Polling             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	D2W_BatchTransmission[]				= "Batch Tx            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	D2W_ContinuousPolling[]				= "Cont Polling        ";
CUB	D2W_InputSubAddressNumber[]			= "Enter Sub-Address   ";
CUB	D2W_InputPasswordNumber[]			= "Enter Password      ";
CUB	D2W_SelectCipherExtensionKey[]		= "Key Extension  :\0   ";

/* 各機能の詳細データ設定中（下段） */
CUB	D2W_EnterDelayedTxTime[]			= "Enter Time: \0       ";
CUB	D2W_InputMailBoxNumber[]			= "S Mail No.        \0 ";
CUB	D2W_RelayTxGroupNumber[]			= "Group No.     \0     ";
CUB	D2W_InputFileNumber[]				= "File No.    \0       ";
CUB	D2W_BatchBoxIndexNumber[]			= "Box:      File:     ";
CUB	D2W_EnterContPollStartTime[]		= "Start Time:   \0     "; /* 1996/10/23 Y.Matsukuma */
CUB	D2W_EnterContPollEndTime[]			= "End Time:     \0     "; /* 1996/10/23 Y.Matsukuma */

/*----------------------------------*
 *	濃度設定
 *----------------------------------*/
CUB	D2W_SetPaperContrast[]				= "Set Contrast        ";
CUB	D2W_ContrastLightDark[]				= " Light         Dark ";

/*----------------------------------*
 *	機器エラー
 *----------------------------------*/
/* カバー */
CUB	D2W_PleaseCloseScannerCover[]		= "Close Scanner Cover ";
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	D2W_PleaseClose1stJamCover[]		= "Close 1st Side Cover";
CUB	D2W_PleaseClose2ndJamCover[]		= "Close 2nd Side Cover";
CUB	D2W_PleaseClose3rdJamCover[]		= "Close 3rd Side Cover";
CUB	D2W_PleaseOpen1stJamCover[]			= "Open 1st Side Cover ";
CUB	D2W_PleaseOpen2ndJamCover[]			= "Open 2nd Side Cover ";
CUB	D2W_PleaseOpen3rdJamCover[]			= "Open 3rd Side Cover ";
CUB	D2W_PleaseOpenTopCover[]			= "Open Top Cover      ";
 #if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1998/01/28 */
CUB	D2W_PleaseOpenPrinterCover[]		= "ﾌﾟﾘﾝﾀｶﾊﾞｰ ｦ ｱｹﾃ     ";
 #endif
CUB	D2W_PleaseOpenCloseScanCover[]		= "Open&Close ScanCover";
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
CUB	D2W_PleaseClosePrinterCover[]		= "ﾌﾟﾘﾝﾀｶﾊﾞｰｦ ﾄｼﾞﾃｸﾀﾞｻｲ";
#endif
#if (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	D2W_ScannerFeedErrorLow[]			= "Reset Document      ";
#endif

/* カセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	D2W_PleaseCloseLowerCassette[]		= "Close Cassette      ";	/* 要変更 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	D2W_PleaseClose1stCassette[]		= "Close 1st Cassette  ";
CUB	D2W_PleaseClose2ndCassette[]		= "Close 2nd Cassette  ";
CUB	D2W_PleaseClose3rdCassette[]		= "Close 3rd Cassette  ";
#endif

/* 記録紙 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)
CUB	D2W_ReplaceRxPaper[]				= "Please Supply Paper ";
CUB	D2W_NoSamePaper[]					= "Please Supply Paper ";	/* 日本以外は、???_ReplaceRxPaperと同じです by K.Watanabe 1998/02/23 */
#endif

#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Modify by SMuratec 夏 2004/8/26 */
CUB	D2W_ReplaceRxPaper[]				= "Check Rx Paper      ";
CUB	D2W_NoSamePaper[]					= "Please Supply Paper ";	/* 日本以外は、???_ReplaceRxPaperと同じです by K.Watanabe 1998/02/23 */
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	D2W_ReplaceRxPaper[]				= "Check Rx Paper      ";
CUB	D2W_ReplaceUpperRxPaper[]			= "Check Tray Paper    ";
CUB	D2W_ReplaceLowerRxPaper[]			= "Check Cassette Paper";
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
CUB	D2W_Cassette1[]						= "1st Cassette        ";
CUB	D2W_Cassette2[]						= "2nd Cassette        ";
CUB	D2W_Cassette3[]						= "3rd Cassette        ";
CUB	D2W_ManualCassette[]				= "Tray:\0  ";
#endif
CUB	D2W_RemoveManualPaper[]				= "Remove Tray Paper   ";
CUB	D2W_CheckPaperSize[]				= "Check Rx Paper Size ";
CUB	D2W_PleaseOpenCloseTopCover[]		= "Open&Close Top Cover";
#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1998/01/28 */
CUB	D2W_PleaseOpenClosePrinterCover[]	= "ﾌﾟﾘﾝﾀｶﾊﾞｰｦ ｶｲﾍｲｸﾀﾞｻｲ";
#endif

/* プリンター */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ジャム時の表示内容を変更します。By H.Fujimura 1999/03/09 */
CUB	D2W_PleaseRemovePaper[]				= "Check Rx Paper      ";
#else
CUB	D2W_PleaseRemovePaper[]				= "Please Remove Paper ";
#endif
CUB	D2W_PleaseSupplyToner[]				= "Please Supply Toner ";
CUB	D2W_PleaseReplaceToner[]			= "Please Replace Toner";
CUB	D2W_PleaseCallService[]				= "Please Call Service ";
CUB	D2W_PaperSizeError[]				= "Check Paper Size    ";	/* ANZUのみ */

CUB	D2W_CheckDrumLife[]					= "Drum Near End       ";
CUB	D2W_ReplaceDrum[]					= "Please Replace Drum ";
CUB	D2W_CheckDrum[]						= "No Drum             ";
CUB	D2W_CheckTonerLevel[]				= "Toner Low           ";
CUB	D2W_NoToner[]						= "No Toner Cartridge  ";

/* スキャナ */
CUB	D2W_CallForService[]				= "Call For Service    ";
CUB	D2W_CheckDocument[]					= "Check # Of Pages    ";
CUB	D2W_MirrorCarrigeError[]			= "Mirror Carriage Err ";

/* ジャムリカバー */
CUB	D2W_DocumentJam[]					= "Document Jam        ";
CUB	D2W_InterruptDocScan[]				= "Stop Scanning       ";
CUB	D2W_NextScanEnterClear[]			= "ContStor Enter/Cancl";
CUB	D2W_ResetPageNumber[]				= "p  . Reset Document ";
CUB	D2W_ResetDocumentSet[]				= "Reset Document      ";
CUB	D2W_PleasePressStartKey[]			= "Press Start Key     ";
CUB	D2W_PleasePressEnterKey[]			= "Press Enter Key     ";
CUB	D2W_PleasePressCopyKey[]			= "Press Copy Key      ";	/* POPLAR_B以外 */

/* 通信 */
CUB	D2W_CommunicationError[]			= "Communication Error ";
CUB	D2W_NoStoredDialInNumber[]			= "No Entered Dial In  ";	/* (JPN) */

/* ハングアップ */
CUB	D2W_HungUpPhone[]					= "Hang Up Phone       ";

/* 完了表示 */
CUB	D2W_TransmitComplete[]				= " **   Complete   ** ";
CUB	D2W_ReceiveComplete[]				= " **   Complete   ** ";
CUB	D2W_PrintComplete[]					= " **   Complete   ** ";
CUB	D2W_StoreComplete[]					= " **   Complete   ** ";
CUB	D2W_SetComplete[]					= " **   Complete   ** ";
CUB	D2W_ClearComplete[] 				= " **   Complete   ** ";

/* リモート診断中の表示 1996/01/25 Eguchi */
CUB	D2W_RemoteDiagMode[]				= "Service Mode        ";

/* 操作エラー */
/* 絶対に途中に追加してはいかん */
CUB	D2W_InvalidNumber[]					= "Invalid Number      ";	/* INVALID_NUMBER_ERROR				*/
CUB	D2W_TooManyDigitsin[]				= "Too Many Characters ";	/* TOO_MANY_DIGITS_ERROR			*/
CUB	D2W_PleaseInput1_99[]				= "Enter No. (1-99)    ";	/* INVALID_COPY_NUMBER_ERROR		*//* POPLAR_B以外 */
CUB	D2W_NoNumberStored[]				= "No Number Stored    ";	/* NO_STORED_NUMBER_ERROR			*//* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	D2W_PleaseInput0_32[]				= "Enter No. (0-32)    ";	/* INVALID_GROUP_NUMBER_ERROR		*/
CUB	D2W_TooManyLocations[]				= "Too Many Locations  ";	/* TOO_MANY_LOCATION_ERROR			*/
CUB	D2W_InsertDocument[]				= "Insert Document     ";	/* INSERT_DOCUMENT_ERROR			*/
CUB	D2W_FeederInUse[]					= "Feeder In Use       ";	/* FEEDER_IN_USE_ERROR				*/
CUB	D2W_ScannerInUse[]					= "Scanner In Use      ";	/* SCANNER_USE_ERROR				*/
CUB	D2W_PollingInUse[]					= "Polling In Use      ";	/* ALREADY_POLLING_STORED_ERROR		*/
CUB	D2W_NoDocumentStored[]				= "No Document Stored  ";	/* NO_STORED_DOCUMENT_ERROR			*/
CUB	D2W_CommandFull[]					= "All Commands In Use ";	/* COMMAND_FULL_ERROR				*/
CUB	D2W_NoCommand[]						= "No Command          ";	/* NO_COMMAND_ERROR					*/
CUB	D2W_NoCommandDocument[]				= "No Document Stored  ";	/* NO_COMMAND_DOCUMENT_ERROR		*/
CUB	D2W_NoCommandResult[]				= "No Report           ";	/* NO_COMMAND_RESULT_ERROR			*/
CUB	D2W_SecureDocExist[]				= "Document Stored     ";	/* SECURE_DOC_EXIST_ERROR			*/
CUB	D2W_PrinterInUse[]					= "Printer In Use      ";	/* PRINTER_IN_USE_ERROR				*/
CUB	D2W_InvalidIDCode[]					= "Invalid I.D. Code   ";	/* INVALID_ID_CODE_ERROR			*/
CUB	D2W_InvalidProtectPasscode[]		= "Invalid Passcode    ";	/* INVALID_PROTECT_PASSCODE_ERROR	*/
CUB	D2W_NoProtectPasscode[]				= "No Passcode         ";	/* NO_PROTECT_PASSCODE_ERROR		*/
CUB	D2W_InputRangeOver[]				= "Invalid Number      ";	/* INPUT_RANGE_OVER_ERROR			*/
CUB	D2W_BatchDocFull[]					= "                    ";	/* BATCH_DOCUMENT_FULL_ERROR		*/
CUB	D2W_LineBusy[]						= "Line Busy           ";	/* LINE_BUSY_ERROR					*/
CUB	D2W_ProtectedDocStored[]			= "Protect Doc. Stored ";	/* PROTECT_DOCUMENT_STORED_ERROR	*/
CUB	D2W_NoProtectDocStored[]			= "No Document Stored  ";	/* NO_PROTECT_DOCUMENT_ERROR		*/
CUB	D2W_NoPinNumber[]					= "No PIN Number       ";	/* NO_PIN_NUMBER_ERROR				*/
CUB	D2W_NoDepartmentCode[]				= "No Dept. Code       ";	/* NO_DEPARTMENTCODE_ERROR			*/
CUB	D2W_BatchDocStored[]				= "Document Stored     ";	/* BATCH_DOCUMENT_STORED_ERROR		*/
CUB	D2W_ResetDocument[]					= "Reset Document      ";	/* RESET_DOCUMENT_ERROR				*/
CUB	D2W_PleaseCloseBookCover[]			= "Close Book Cover    ";	/* BOOK_COVER_OPEN_ERROR			*//* POPLAR_Bのみ */
CUB	D2W_PleaseWaitAMinute[]				= "Please Wait         ";	/* PRINTER_CLEANING_ERROR			*/
CUB	D2W_NotStoredDocument[]				= "Document Full       ";	/* NOT_STORED_DOCUMENT_ERROR		*//* (PRO_F_CODE == ENABLE) */
CUB	D2W_BoxInUse[]						= "Box In Use          ";	/* BOX_IN_USE_ERROR					*//* (PRO_F_CODE == ENABLE) */
CUB	D2W_TooManyDirectDial[]				= "Too Many Locations  ";	/* TOO_MANY_DIRECT_DIAL_ERROR		*/
CUB	D2W_SettingSecureBox[]				= "In Secure Box       ";	/* SETTING_SECURE_BOX_ERROR			*//* (PRO_F_CODE == ENABLE) */
CUB	D2W_BookSizeNoSet[]					= "Enter Scan Size     ";	/* BOOK_SIZE_NO_SET_ERROR			*//* POPLAR_Bのみ */
CUB	D2W_NotCompleteStoredDoc[]			= "Store Not Completed ";	/* NOT_COMPLETE_STORED_ERROR		*//* POPLAR_Bのみ */
CUB	D2W_NotCompleteCopy[]				= "Copy Not Completed  ";	/* NOT_COMPLETE_COPY_ERROR			*//* POPLAR_Bのみ */
CUB	D2W_ScanPreparing[]					= "Scanner Adjusting   ";	/* SCAN_PREPARING_ERROR				*//* POPLAR_Bのみ */
CUB	D2W_CopyProtect[]					= "Copy Off            ";	/* COPY_PROTECT_ERROR				*/
CUB	D2W_NotScanDocSize[]				= "Not Acceptable Size ";	/* NOT_SCAN_DOC_SIZE_ERROR			*//* (PRO_CIPHER == ENABLE) */
CUB	D2W_ShortFigure[]					= "4 Letters or More   ";	/* SHORT_FIGURE_ERROR				*//* (PRO_CIPHER == ENABLE) */
CUB	D2W_AlreadyStored[]					= "Already Stored      ";	/* ALREADY_NUMBER_STORED_ERROR		*//* (FRA) */
CUB	D2W_NotEntry[]						= "No Key Stored       ";	/* NOT_ENTRY_ERROR					*//* (PRO_CIPHER == ENABLE) */
CUB	D2W_NoScanCipherMode[]				= "No Setting S Fine   ";	/* NO_SCAN_CIPHER_MODE_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	D2W_Ciphering[]						= "Scrambler In Use    ";	/* CIPHERING_ERROR					*//* (PRO_CIPHER == ENABLE) */
CUB	D2W_Deciphering[]					= "Descrambler In Use  ";	/* DECIPHERING_ERROR				*//* (PRO_CIPHER == ENABLE) */
CUB	D2W_UseDefaultCipherKey[]			= "In Use as Default   ";	/* USE_DEFAULT_CIPHER_KEY_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	D2W_UseProgramOneTouch[]			= "In Use in P OneTouch";	/* USE_PROGRAM_ONETOUCH_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	D2W_PleaseCloseTopCover[]			= "Close Top Cover     ";	/* TOP_COVER_OPEN_ERROR				*/
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1999/01/07 */
//#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#endif
CUB	D2W_DialNumberStoredError[]			= "FAX Number Stored   ";	/* DIAL_NUMBER_STORED_ERROR			*/
CUB	D2W_ProgramStoredError[]			= "Program Stored      ";	/* PROGRAM_STORED_ERROR				*/
CUB	D2W_MailAddressStoredError[]		= "Mail Address Stored ";	/* MAIL_ADDRESS_STORED_ERROR		*/
CUB	D2W_MailGroupStoredError[]			= "Mail Group Stored   ";	/* MAIL_GROUP_STORED_ERROR			*/
CUB	D2W_UserDataFullError[]				= "All User Data Stored";	/* USER_DATA_FULL_ENTRY_ERROR		*/
CUB	D2W_NoRS232C_Error[]				= "No RS-232C          ";	/* NO_RS232C_PCB_ERROR				*/
CUB	D2W_TooManyDirectAdrError[]			= "Too Many Address    ";	/* TOO_MANY_DIRECT_ADDRESS_ERROR	*/
CUB	D2W_NoUserDataError[]				= "No User Data        ";	/* NO_USER_DATA_ERROR				*/
CUB	D2W_InvalidAddressError[]			= "Invalid Address     ";	/* INVALID_ADDRESS_ERROR			*/
CUB	D2W_NoTCPIP_BoardError[]			= "No Optional Board   ";	/* NO_TCPIP_BOARD_ERROR				*/
CUB	D2W_MemoryFullError[]				= "Memory Full         ";	/* MEMORY_FULL_ERROR				*/
CUB	D2W_AlreadyUsedError[]				= "One-Touch In Use    ";	/* ALREADY_USED_ERROR				*/
CUB	D2W_NoEntryData[]					= "No Entry Data       ";	/* NO_ENTRY_DATA					*/
CUB	D2W_NoStoredAddress[]				= "No Address Stored   ";	/* NO_STORED_ADDRESS_ERROR			*/
CUB	D2W_InvalidPassword[]				= "Invalid Password    ";	/* INVALID_PASSWORD_ERROR			*/
CUB	D2W_ExecuteCommand[]				= "Executing Command   ";	/* EXECUTE_COMMAND_ERROR			*/
CUB	D2W_NoDeviceError[]					= "No Device           ";	/* NO_DEVICE_ERROR					*/
#if (0)
//CUB D2W_NoAccessPointTelNumber[]		= "No AP Tel Number    ";	/* NO_ACCESS_POINT_DATA_ERROR		*/
#endif
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1999/01/07 */
//#endif
#endif
CUB	D2W_SettingRelayBox[]				= "ﾁｭｳｹｲﾎﾞｯｸｽ ﾃﾞｽ      ";	/* SETTING_RELAY_BOX_ERROR			*//* By H.Fujimura 1999/01/07 */
CUB	D2W_TooManyRelayDirect[]			= "ﾁｮｸｾﾂﾀﾞｲﾔﾙ 1ｶｼｮ ｲﾅｲ ";	/* TOO_MANY_RELAY_DIRECT_ERROR		*//* By H.Fujimura 1999/01/07 */

/*----------------------------------*
 *	通信中
 *----------------------------------*/
CUB	D2W_Transmit[]						= "Transmit            ";
CUB	D2W_Receive[]						= "Receive   ";
CUB	D2W_Called[]						= " ** Being Called ** ";
CUB	D2W_CallReservation[]				= "** Call Requested **";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	D2W_CallReservation_S[]				= "** Call Requested **";
#endif

/*----------------------------------*
 *	原稿サイズ・線密度
 *----------------------------------*/
CUB	D2W_DocNormal[]						= "Normal    \0         ";
CUB	D2W_DocFine[]						= "Fine      \0         ";
CUB	D2W_DocSFine[]						= "S Fine    \0         ";
#if (PRO_PITNEYBOWES == ENABLE) /* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
CUB	D2W_DocGray[]						= "PHOTO     \0         "; 
CUB	D2W_DocHGray[]						= "H PHOTO   \0         "; 
#else
CUB	D2W_DocGray[]						= "Gray      \0         ";
#endif
CUB	D2W_DocHFine[]						= "H Fine    \0         "; /*評価用に追加1996/06/19Eguchi*/
CUB	D2W_DocEFine[]						= "E Fine    \0         "; /*評価用に追加1996/06/19Eguchi*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	D2W_DocFine_S[]						= "Fine      \0         ";
CUB	D2W_DocSFine_S[]					= "S Fine    \0         ";
#endif

/*----------------------------------*
 *	次原稿・メモリ残量
 *----------------------------------*/
CUB	D2W_NextDocument[]					= "NextDoc";
CUB	D2W_MemoryAreaShort[]				= "             Mem   %";
CUB	D2W_MemoryAreaLong[]				= "          Memory   %";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/07 */
CUB	D2W_MemoryAreaLong2[]				= "   *****  Memory   %";
CUB	D2W_MemoryAreaShort2[]				= "             ﾒﾓﾘ   %";	/* ＬＣＤ表示変更(0x7E = ->) By O.Kimoto 1999/02/25 */
#endif
#if (PRO_NOT_AUTO_RX_DISP == ENABLE)	/* by K.Watanabe 1998/06/08 */
CUB	D2W_MemoryFull[]					= "Not Receiving       ";
CUB	D2W_NotAutoReceive[]				= "as Memory Full      ";
#endif

/*----------------------------------*
 *	月
 *----------------------------------*/
CUB	D2W_January[]						= "Jan";
CUB	D2W_February[]						= "Feb";
CUB	D2W_March[]							= "Mar";
CUB	D2W_April[]							= "Apr";
CUB	D2W_May[]							= "May";
CUB	D2W_June[]							= "Jun";
CUB	D2W_July[]							= "Jul";
CUB	D2W_August[]						= "Aug";
CUB	D2W_September[]						= "Sep";
CUB	D2W_October[]						= "Oct";
CUB	D2W_November[]						= "Nov";
CUB	D2W_December[]						= "Dec";

/*----------------------------------*
 *	予約表示
 *----------------------------------*/
CUB	D2W_Reserving[]						= "   ** Reserved **   ";
CUB	D2W_AutoRedial[]					= " ** Auto Redial **  ";

/*----------------------------------*
 *	原稿セット時
 *----------------------------------*/
CUB	D2W_TransmitOrCopyReady[]			= "Document Ready      ";
CUB	D2W_TransmitReady[]					= "Document Ready      ";	/* 日本以外は、???_TransmitOrCopyReadyと同じです */

#if (PRO_PC_PRINT == ENABLE)
/*----------------------------------*
 *	ＰＣプリント
 *----------------------------------*/
CUB	D2W_PC_Print[]						= "PC                  ";
CUB	D2W_PC_Receiving[]					= "  ** Receiving **   ";
CUB	D2W_PC_MemoryOverFlow[]				= "PC Memory Over Flow ";
#endif

/*----------------------------------*
 *	プリント中
 *----------------------------------*/
CUB	D2W_Printing[]						= "   ** Printing **   ";

/*----------------------------------*
 *	ウォームアップ
 *----------------------------------*/
CUB	D2W_Wait[]							= " ** Please Wait **  ";

/*----------------------------------*
 *	イメージプリント
 *----------------------------------*/
CUB	D2W_PollingDocument[]				= "Polling Doc         ";
CUB	D2W_SecureMailDocument[]			= "Print SecureMail    ";
CUB	D2W_MemoryRxDocument[]				= "                    ";
CUB	D2W_CommandDocument[]				= "Print Stored Doc.   ";
CUB	D2W_BatchTxDocument[]				= "Print Batch Doc.    ";

/*----------------------------------*
 *	リストプリント
 *----------------------------------*/
CUB	D2W_PrintJournal[]					= "Print Journal       ";
#if (PRO_JOURNAL_VER_UP == ENABLE)	/* by K.Watanabe 2004/10/28 */
CUB	D2W_PrintJournalTx[]				= "Print Tx Journal    ";
CUB	D2W_PrintJournalRx[]				= "Print Rx Journal    ";
CUB	D2W_PrintJournalTxRx[]				= "Print TxRx Journal  ";
#endif
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
CUB	D2W_PrintAllJournal[]				= "Print All Journals  ";
CUB	D2W_PrintDailyReport[]				= "Print Day Journal   ";
#endif
CUB	D2W_TCR[]							= "TCR                 ";
CUB	D2W_PrintSpeedDial[]				= "Print Speed-Dial    ";
CUB	D2W_PrintOneTouch[]					= "Print One-Touch     ";
CUB	D2W_PrintProgramOneTouch[]			= "Print P One-Touch   ";
CUB	D2W_GroupList[]						= "Group List          ";
CUB	D2W_SF_ProgramListPrint[]			= "Program List        ";
CUB	D2W_SetPrintSettings[]				= "Print Settings      ";
CUB	D2W_PrintCommands[]					= "Print Commands      ";
CUB	D2W_PrintSecureMailList[]			= "Print S Mail List   ";
CUB	D2W_MessageList[]					= "Print Cover Message ";
CUB	D2W_PrintSecureMail[]				= "Print SecureMail    ";
CUB	D2W_SF_T30MonitorPrint[]			= "T30 Monitor         ";
CUB	D2W_SF_FactoryFunctionList[]		= "Function List       ";
CUB	D2W_SF_MemorySwitchMode[]			= "Memory Switch       ";
CUB	D2W_CheckMessage[]					= "Check Message       ";
CUB	D2W_SF_OnLineMonitor[]				= "On Line Monitor     ";
CUB	D2W_SF_OrderForm[]					= "Order Sheet         ";

/*----------------------------------*
 *	パスコード
 *----------------------------------*/
CUB	D2W_InputPasscode[]					= "Passcode       :\0   ";
CUB	D2W_EnterProtectPasscode[]			= "Enter Passcode :\0   ";
CUB	D2W_OldProtectPasscode[]			= "Old Passcode   :\0   ";
CUB	D2W_NewProtectPasscode[]			= "New Passcode   :\0   ";
CUB	D2W_EnterIDCode[]					= "Enter I.D. Code:\0   ";
#if (PRO_F_CODE == ENABLE)
CUB	D2W_EnterFcodePasscode[]			= "F-Code Passcode:\0   ";
#endif
#if (PRO_CIPHER == ENABLE)
CUB	D2W_CipherPassCode[]				= "Passcode       :\0   ";
CUB	D2W_OldCipherPassCode[]				= "Old Passcode   :\0   ";
CUB	D2W_NewCipherPassCode[]				= "New Passcode   :\0   ";
#endif

/*----------------------------------*
 *	入力モード
 *----------------------------------*/
#if defined(JPN)
CUB	D2W_Kana[]							= ":Kana    ";
 #if (PRO_JIS_CODE == ENABLE)
CUB	D2W_KanjiCode[]						= ":ｶﾝｼﾞｺｰﾄﾞ";
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
CUB	D2W_Alphameric[]					= ":Alphame."; /* ';' to ':' Modified by SMuratec L.Z.W 2003/11/28 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	D2W_Upper[]							= ":Upper   ";
CUB	D2W_Lower[]							= ":Lower   ";
CUB	D2W_Symbol[]						= ":Symbols ";	/* ANZUのみ */
CUB	D2W_Code[]							= ":Code    ";
CUB	D2W_ModeNone[]						= ":        ";

/*----------------------------------*
 *	電話帳
 *----------------------------------*/
CUB	D2W_TelephoneBookMode[]				= "Telephone Index  [ ]";

/*----------------------------------*
 *	電話
 *----------------------------------*/
CUB	D2W_OnHold[]						= "  **  On Hold  **   ";	/* POPLAR_B以外 */
CUB	D2W_TelephoneMode[]					= "  **  Tel Mode  **  ";

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 変更 by Y.kano 2003/09/08 */
CUB	D2W_ChangeVolume[]					= "Volume:             ";
#else
CUB	D2W_ChangeVolume[]					= "  Volume:           ";
#endif

/*----------------------------------*
 *	メモリーオーバーオペレーション
 *----------------------------------*/
CUB	D2W_MemoryOverFlow[]				= "Memory Over Flow    ";
CUB	D2W_MemoryOverStartClear[]			= "Start Or Cancel     ";
CUB	D2W_MemoryOverEnterClear[]			= "Enter Or Cancel     ";
CUB	D2W_MemoryOverCopyClear[]			= "Copy Or Cancel      ";	/* POPLAR_B以外 */

/*----------------------------------*
 *	ファンクション関係
 *----------------------------------*/
/* 機能選択状態 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 全機種共通の変更でないのに条件が入っていなかったので条件追加 by K.Watanabe 2004/10/22 */
CUB	D2W_OneTouchDialMode[]				= "    One-Touch Dial  ";
CUB	D2W_SpeedDialMode[]					= "    Speed Dial      ";
CUB	D2W_ProgramOneTouchMode[]			= "    P One-Touch     ";
CUB	D2W_PollingMode[]					= "    Polling         ";
CUB	D2W_SecureMailMode[]				= "    SecureMail      ";
CUB	D2W_DelayedCommandsMode[]			= "    Delayed Commands";
CUB	D2W_SetReportMode[]					= "    Report          ";
CUB	D2W_PrintGroupMode[]				= "    Print Group List";
CUB	D2W_UserInstallMode[]				= "    User Install    ";
CUB	D2W_UserSettingsMode[]				= "    User Settings   ";
CUB	D2W_MessageMode[]					= "    Cover Page      ";
CUB	D2W_SetNumberOfPagesMode[]			= "    Set # Of Pages  ";
CUB	D2W_SetDepartmentMode[]				= "    Department Code ";
CUB	D2W_SetBatchTxMode[]				= "    Batch Tx        ";
CUB	D2W_SecurityReceiveMode[]			= "    Security Rx     ";
CUB	D2W_FcodeBoxMode[]					= "    F-Code Box      ";	/* (PRO_F_CODE == ENABLE) */
#else
CUB	D2W_OneTouchDialMode[]				= "  One-Touch Dial    ";
CUB	D2W_SpeedDialMode[]					= "  Speed Dial        ";
CUB	D2W_ProgramOneTouchMode[]			= "  P One-Touch       ";
CUB	D2W_PollingMode[]					= "  Polling           ";
CUB	D2W_SecureMailMode[]				= "  SecureMail        ";
CUB	D2W_DelayedCommandsMode[]			= "  Delayed Commands  ";
CUB	D2W_SetReportMode[]					= "  Report            ";
CUB	D2W_PrintGroupMode[]				= "  Print Group List  ";
CUB	D2W_UserInstallMode[]				= "  User Install      ";
CUB	D2W_UserSettingsMode[]				= "  User Settings     ";
CUB	D2W_MessageMode[]					= "  Cover Page        ";
CUB	D2W_SetNumberOfPagesMode[]			= "  Set # Of Pages    ";
CUB	D2W_SetDepartmentMode[]				= "  Department Code   ";
CUB	D2W_SetBatchTxMode[]				= "  Batch Tx          ";
CUB	D2W_SecurityReceiveMode[]			= "  Security Rx       ";
CUB	D2W_FcodeBoxMode[]					= "  F-Code Box        ";	/* (PRO_F_CODE == ENABLE) */
#endif	/* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	D2W_ResetPrinterBoardMode[]			= "  Reset Printer Opt.";	/* (PRO_PC_PRINT == ENABLE) */
CUB	D2W_SetClass1Mode[]					= "  PC-FAX            ";	/* (PRO_CLASS1 == ENABLE) */
CUB	D2W_SetCipherMode[]					= "  Set Scrambling    ";	/* (PRO_CIPHER == ENABLE) */
CUB	D2W_PrintDecipherDocMode[]			= "  Print Descrambled ";	/* (PRO_CIPHER == ENABLE) */

CUB	D2W_EnterOneTouchMode[]				= "   Enter One-Touch  ";
CUB	D2W_EraseOneTouchMode[]				= "   Erase One-Touch  ";
CUB	D2W_PrintOneTouchMode[]				= "   Print One-Touch  ";

CUB	D2W_EnterSpeedDialMode[]			= "   Enter Speed-Dial ";
CUB	D2W_EraseSpeedDialMode[]			= "   Erase Speed-Dial ";
CUB	D2W_PrintSpeedDialMode[]			= "   Print Speed-Dial ";

CUB	D2W_EnterProgramOneTouchMode[]		= "   Enter P One-Touch";
CUB	D2W_EraseProgramOneTouchMode[]		= "   Erase P One-Touch";
CUB	D2W_PrintProgramOneTouchMode[]		= "   Print P One-Touch";

CUB	D2W_StorePollingDocumentMode[]		= "   Store Polling Doc";
CUB	D2W_ErasePollingDocumentMode[]		= "   Erase Polling Doc";
CUB	D2W_PrintPollingDocumentMode[]		= "   Print Polling Doc";

CUB	D2W_SetSecureMailBoxMode[]			= "   Set S Mail Box   ";
CUB	D2W_PrintSecureMailListMode[]		= "   Print S Mail List";
CUB	D2W_PrintSecureMailMode[]			= "   Print SecureMail ";
CUB	D2W_SecureMailHoldTimeMode[]		= "   S Mail Hold Time ";

CUB	D2W_PrintCommandsMode[]				= "   Print Commands   ";
CUB	D2W_PrintStoredDocumentMode[]		= "   Print Stored Doc.";

CUB	D2W_JournalOnOffMode[]				= "   Journal On/Off   ";
CUB	D2W_PrintJournalMode[]				= "   Print Journal    ";
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	D2W_PrintDailyReportMode[]			= "   ﾂｳｼﾝﾆｯﾎﾟｳ ﾌﾟﾘﾝﾄ  ";
#endif
CUB	D2W_SettingCommunicationResult[]	= "   Set Report Type  ";

CUB	D2W_SettingScanParameters[]			= "    Scan Parameters ";
CUB	D2W_SettingPrintParameters[]		= "    Print Parameters";
CUB	D2W_SettingCopyParameters[]			= "    Copy Parameters ";	/* POPLAR_B以外 */
CUB	D2W_SettingPaperSize[]				= "    Set Paper Size  ";	/* ANZUのみ */
CUB	D2W_SettingCopyProtect[]			= "    Copy Protect    ";
CUB	D2W_SettingDialingPause[]			= "   Set Dialing Pause";
CUB	D2W_SettingNumberOfRings[]			= "    Set # Of Rings  ";
CUB	D2W_SettingRedial[]					= "    Set Redial      ";
CUB	D2W_SettingECMMode[]				= "    Set ECM Mode    ";
CUB	D2W_SettingPasscode[]				= "    Set Passcode    ";
CUB	D2W_SettingClosedNetwork[]			= "    Closed Network  ";
CUB	D2W_SettingSecurityTransmission[]	= "    Security Tx     ";
CUB	D2W_SettingBlockJunkMail[]			= "    Block Junk Fax  ";
CUB	D2W_SettingRemoteDiagnostic[]		= "    Set Service Mode";
CUB	D2W_SettingMemoryTransmission[]		= "    Set Memory Tx   ";
CUB	D2W_SettingSilentOperation[]		= "    Set Silent Mode ";
CUB	D2W_SettingDialIn[]					= "    Set Dial In     ";	/* (JPN) */
CUB	D2W_SettingProtectPasscode[]		= "    Protect Passcode";
CUB	D2W_SettingOperationProtect[]		= "    Set Opr. Protect";
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/16 */
CUB D2W_SettingRemoteRxParameters[]		= "    ﾘﾓｰﾄ ﾄｸﾊﾞﾝ      ";
#endif		/* End of (defined (KEISATSU)) */
CUB	D2W_SettingPINAccessMode[]			= "    Set PIN Mode    ";
CUB	D2W_SettingRingMasta[]				= "    Set DRD         ";	/* (USA) */
CUB	D2W_SettingStamp[]					= "    Set Stamp       ";
CUB	D2W_SettingResetDrumLife[]			= "    Reset Drum Life ";	/* ANZUのみ */
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */
CUB	D2W_SettingRxAlarm[]				= "    Set Rx Alarm    ";
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/22 */
CUB	D2W_SettingMercuryMode[]			= "    Set Dial Prefix ";
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	D2W_SettingHoldMelody[]				= "    Set Hold Melody ";
#endif
#if (PRO_REMOTE_RX == ENABLE)			/* ＮＴＴ仕様のポプラＬで使用 98/01/26 T.Fukumoto */
CUB	D2W_SettingRemoteReceive[]			= "    Set Remote Trans";
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	D2W_SettingOnHookReceive[]			= "    Set Onhook Trans";	/* 98/03/13 Add By T.Fukumoto */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	D2W_SettingPrintSettings[]			= "    Print Settings  ";
#endif

CUB	D2W_SetMessageOnOff[]				= "   Set Cover Page   ";
CUB	D2W_SetMessage[]					= "   Enter Cover Page ";
CUB	D2W_PrintMessageList[]				= "   Print Cover Page ";

CUB	D2W_SettingDepartmentProtect[]		= "   Set Dept. Protect";
CUB	D2W_SettingDepartmentCode[]			= "   Set Dept. Code   ";
CUB	D2W_SettingDepartmentOnOff[]		= "   Set Dept. On/Off ";
#if (PRO_DEPART_NEW_LIST == ENABLE)									/* added by thonda 1997/12/03 */
CUB	D2W_PrintDepartTimeList[]			= "   Print Dp.TimeList";
CUB	D2W_EraseDepartTimeList[]			= "   Erase Dp.TimeList";
#endif

CUB	D2W_SettingBatchBox[]				= "   Set Batch Box    ";
CUB	D2W_PrintBatchBoxList[]				= "   Print Box List   ";
CUB	D2W_PrintBatchDocList[]				= "   Print Doc. List  ";
CUB	D2W_PrintBatchDoc[]					= "   Print Batch Doc. ";
CUB	D2W_EraseBatchBox[]					= "   Erase Batch Box  ";
CUB	D2W_EraseBatchDoc[]					= "   Erase Batch Doc. ";

CUB	D2W_SettingSecurityRx[]				= "   Set Security Rx  ";
CUB	D2W_PrintMemoryReceiveDoc[]			= "   Print Mem Rx Doc.";

#if (PRO_F_CODE == ENABLE)
CUB	D2W_EnterFcodeBoxMode[]				= "   Set F-Code Box   ";
CUB	D2W_PrintFcodeBoxListMode[]			= "   Print Box List   ";
CUB	D2W_PrintFcodeStoreDocListMode[]	= "   Print Doc. List  ";
CUB	D2W_PrintFcodeStoreDocMode[]		= "   Print F-Code Doc.";
CUB	D2W_EraseFcodeBoxMode[]				= "   Erase F-Code Box ";
CUB	D2W_EraseFcodeDocMode[]				= "   Erase F-Code Doc.";
CUB	D2W_StoreFcodeDocMode[]				= "   Set F-Code Doc.  ";
#endif

#if (PRO_CIPHER == ENABLE)
CUB	D2W_EnterCipherKeyBookMode[]		= "   Set KeyBook      ";
CUB	D2W_PrintCipherKeyBookListMode[]	= "   KeyBook List     ";
CUB	D2W_PrintCipherKeyMode[]			= "   Print Key        ";
CUB	D2W_EraseCipherKeyBookMode[]		= "   Erase KeyBook    ";
CUB	D2W_EraseCipherRxDocMode[]			= "   Erase Scrmbld Doc";
CUB	D2W_EnterDefaultCipherKeyMode[]		= "   Set Default Key  ";
CUB	D2W_EnterCipherServiceLabelMode[]	= "   Svc. Lbl. Posit. ";
CUB	D2W_EnterCipherPassCodeMode[]		= "   Set Passcode     ";
#endif

CUB	D2W_SettingRS232CPCFaxScan[]		= "   PC-FAX Scan      ";
CUB	D2W_SettingRS232CParameter[]		= "   Set RS232C       ";
CUB	D2W_SettingRS232CPCFaxInitial[]		= "   PC-FAX Initial   ";

/*----------------------------------*
 *	ワンタッチ登録
 *----------------------------------*/
CUB	D2W_SelectOnetouch[]				= "Select One-Touch    ";

CUB	D2W_EraseOnetouch[]					= "Erase One-Touch     ";
CUB	D2W_EraseSpeedDial[]				= "Erase Speed-Dial    ";
CUB	D2W_EraseProgramOnetouch[]			= "Erase P One-Touch   ";

/*----------------------------------*
 *	短縮登録
 *----------------------------------*/
CUB	D2W_SelectOptionalSpeedNumber[]		= "   /     (0-999):   ";

/* ワンタッチ・短縮ダイアルデータ入力中 */
/* このワーディングのサイズ及び登録順はかえてはいけない */
CUB	D2W_FaxNumber[]						= "Fax Number          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	D2W_AltNumber[]						= "Alt. No.            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	D2W_RemoteName[]					= "Name                ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大9ﾊﾞｲﾄです */
CUB	D2W_GroupNumber[]					= "Group No.           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/26 */
CUB	D2W_PinNumber[]						= "TTI Number          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
#else
CUB	D2W_PinNumber[]						= "PIN Number          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
#endif
CUB	D2W_Attribute1[]					= "Attribute1          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	D2W_Attribute2[]					= "Attribute2          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	D2W_Attribute3[]					= "Attribute3          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	D2W_Attribute4[]					= "Attribute4          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */

CUB	D2W_SetPIN_Number[]					= "Set PIN Number      ";

/*----------------------------------*
 *	プログラムワンタッチ
 *----------------------------------*/
CUB	D2W_SelectProgramOnetouch[]			= "Select Program No.  ";

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	拡張版プログラムワンタッチ
 *----------------------------------*/
CUB D2W_ProgramItem[][21]		= {
										  "    ﾄｳﾛｸ ﾅｲﾖｳ: ﾂｳｼﾝ ",
										  "    ﾄｳﾛｸ ﾅｲﾖｳ: ﾘｽﾄ  ",
										  "    ﾄｳﾛｸ ﾅｲﾖｳ: ﾁｸｾｷ ",
};

CUB D2W_ProgramList[][21]		= {
										  "    ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ﾘｽﾄ  ",
										  "    ﾀﾝｼｭｸﾀﾞｲﾔﾙ ﾘｽﾄ  ",
										  "    ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ﾘｽﾄ",
										  "    ｼﾝﾃﾝｼｬ ﾘｽﾄ      ",
										  "    ﾂｳｼﾝﾖﾔｸ ﾘｽﾄ     ",
 #if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
										  "   ｽﾍﾞﾃﾉﾂｳｼﾝｷﾛｸﾌﾟﾘﾝﾄ",
										  "    ﾂｳｼﾝﾆｯﾎﾟｳ ﾌﾟﾘﾝﾄ ",
 #else
										  "    ﾂｳｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ   ",
 #endif
										  "    ｸﾞﾙｰﾌﾟ ﾘｽﾄ      ",
										  "    ｷｷｾｯﾃｲ ﾘｽﾄ      ",
 #if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/08/24 */
										  "    ﾒｯｾｰｼﾞ ﾘｽﾄ      ",
 #else
 										  "    DMﾎﾞｳｼ ﾀﾞｲﾔﾙ ﾘｽﾄ",
										  "    ﾒｯｾｰｼﾞ ﾘｽﾄ      ",
										  "    ｲｯｶﾂ ﾎﾞｯｸｽ ﾘｽﾄ  ",
										  "    ｲｯｶﾂ ｹﾞﾝｺｳ ﾘｽﾄ  ", 
 #endif
 #if (PRO_F_CODE == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "    Fｺｰﾄﾞ ﾎﾞｯｸｽ ﾘｽﾄ ",
										  "    Fｺｰﾄﾞ ﾁｸｾｷ ﾘｽﾄ  ",
 #endif
 #if (PRO_DEPART_NEW_LIST == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "    ｼﾞｶﾝｶﾝﾘﾘｽﾄ ﾌﾟﾘﾝﾄ",
 #endif
 #if (PRO_NUMBER_DISPLAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "    NDﾀﾞｲﾔﾙ ﾘｽﾄ     ",
										  "    NDﾘﾚｷ ﾌﾟﾘﾝﾄ     ",
 #endif
 #if (PRO_RX_DOC_TRANSFER == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "    FAXﾜｰﾌﾟ ﾘｽﾄ     ",
 #endif
};

CUB D2W_ProgramStore[][21]		= {
										  "    ﾎﾟｰﾘﾝｸﾞ ﾁｸｾｷ    ",
 #if (PRO_F_CODE == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "    Fｺｰﾄﾞ ﾁｸｾｷ      ",
 #endif
};

CUB D2W_ProgramTxModeSW[][21]	= {
										  "    ｶﾞｼﾂ: ---       ",
										  "    ｶﾞｼﾂ: ﾋｮｳｼﾞｭﾝ   ",
										  "    ｶﾞｼﾂ: ｺｳｶﾞｼﾂ    ",
										  "    ｶﾞｼﾂ: ﾁｮｳｺｳｶﾞｼﾂ ",
										  "    ｶﾞｼﾂ: ｼｬｼﾝ      ",
};

CUB D2W_ProgramContrastSW[][21]	= {
										  "    ﾉｳﾄﾞ:       --- ",
										  "    ﾉｳﾄﾞ:       ｳｽｸ ",
/*										  "    ﾉｳﾄﾞ:    ﾔﾔ ｳｽｸ ",*/
										  "    ﾉｳﾄﾞ:       ﾌﾂｳ ",
/*										  "    ﾉｳﾄﾞ:    ﾔﾔ ｺｸ  ",*/
										  "    ﾉｳﾄﾞ:       ｺｸ  ",
};

CUB D2W_ProgramStampSW[][21]	= {
										  "    ｽﾐｽﾀﾝﾌﾟ:    --- ",
										  "    ｽﾐｽﾀﾝﾌﾟ:    OFF ",
										  "    ｽﾐｽﾀﾝﾌﾟ:    ON  ",
};

CUB D2W_ProgramMemoryTxSW[][21]	= {
										  "    ﾒﾓﾘｿｳｼﾝ:    --- ",
										  "    ﾒﾓﾘｿｳｼﾝ:    OFF ",
										  "    ﾒﾓﾘｿｳｼﾝ:    ON  ",
};

CUB D2W_ProgramConfirmSW[][21]	= {
										  "    ﾂｳｼﾝｼｮｳ  :  --- ",
										  "    ﾂｳｼﾝｼｮｳ  :  OFF ",
										  "    ｿｳｼﾝｼｮｳ  :  ON  ",
										  "    ｼﾞｭﾘｮｳｼｮｳ:  ON  ",
};

 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB D2W_ProgramTxModeSW_S[][21]	= {
										  "    ｶﾞｼﾂ: ---       ",
										  "    ｶﾞｼﾂ: ﾋｮｳｼﾞｭﾝ   ",
										  "    ｶﾞｼﾂ: ｺﾏｶｲ      ",
										  "    ｶﾞｼﾂ: ｾｲｻｲ      ",
										  "    ｶﾞｼﾂ: ｼｬｼﾝ      ",
};

CUB D2W_ProgramContrastSW_S[][21]	= {
										  "    ﾉｳﾄﾞ:       --- ",
										  "    ﾉｳﾄﾞ:       ｺｲ  ",
										  "    ﾉｳﾄﾞ:       ﾌﾂｳ ",
										  "    ﾉｳﾄﾞ:       ｳｽｲ ",
};
 #endif
#endif	/* (PRO_EXT_P_ONETOUCH == ENABLE) */

/*----------------------------------*
 *	ポーリング
 *----------------------------------*/
CUB	D2W_StorePollingDocument[]			= "Store Polling Doc   ";
CUB	D2W_ErasePollingDocument[]			= "Erase Polling Doc   ";
CUB	D2W_PrintPollingDocument[]			= "Print Polling Doc   ";

/*----------------------------------*
 *	親展
 *----------------------------------*/
CUB	D2W_SetSecureMailBox[]				= "Set SecureMail Box  ";
CUB	D2W_SecureMailHoldTime[]			= "S Mail Hold Time    ";
CUB	D2W_HoldTime1_31[]					= "Hold Time(1-31):  \0 ";
CUB	D2W_SecureMailName[]				= " :Name     \0        ";	/* 先頭1文字は、親展番号をｾｯﾄします */

/*----------------------------------*
 *	通信予約
 *----------------------------------*/
CUB	D2W_PrintStoredDocument[]			= "Print Stored Doc.   ";
CUB	D2W_InputCommandNumber[]			= "Command No.:        ";
#if (PRO_CIPHER == ENABLE)
CUB	D2W_SelectDecipher[]				= "Descrambling   :\0   ";
#endif

/*----------------------------------*
 *	ジャーナル
 *----------------------------------*/
CUB	D2W_JournalOnOff[]					= "Journal On/Off      ";
CUB	D2W_SelectAutoPrint[]				= "Auto Print:     \0   ";
CUB	D2W_TCRSelected[]					= "TCR Selected        ";
CUB	D2W_RCRSelected[]					= "RCR Selected        ";
CUB	D2W_SetCommunicationResult[]		= "Set Report Type     ";

/*----------------------------------*
 *	設置モード
 *----------------------------------*/
/* カレンダー入力 */
CUB	D2W_InputTime[]						= "Enter Time          ";

/* 夏時間切り替え */
#if defined(USA)
CUB	D2W_DayLightSaving[]				= "Daylight Saving:\0   ";
#endif

/* ＴＴＩ */
CUB	D2W_EnterYourFaxNumber[]			= "Your Fax Number     ";
CUB	D2W_EnterYourName[]					= "Your Name           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	D2W_EnterYourKanaName[]				= "Your KanaID         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* (JPN) */

/* 回線種別 */
CUB	D2W_SelectPhoneType[]				= "Phone Type   :\0     ";
CUB	D2W_10pps[]							= "              10pps ";
CUB	D2W_20pps[]							= "              20pps ";
CUB	D2W_Tone[]							= "              Tone  ";

#if defined (KEISATSU) /* 警察FAX Added by SMuratec K.W.Q 2005/06/07 */
CUB	D2W_SelectKeidenPhoneType[]			= "ｹｲﾃﾞﾝ ﾀﾞｲﾔﾙ  :\0     ";
CUB	D2W_SelectKanyuPhoneType[]			= "ｶﾆｭｳ  ﾀﾞｲﾔﾙ  :\0     ";
#endif		/* End of (defined (KEISATSU)) */

CUB	D2W_Pulse10[]						= "              Pulse ";
CUB	D2W_Pulse20[]						= "              Pulse ";
CUB	D2W_Push[]							= "              Tone  ";

CUB	D2W_PrintSettingList[]				= "Print Setting List  ";	/* ANZUのみ */

#if (PRO_MULTI_LINE == ENABLE) || (PRO_MULTI_TTI == ENABLE)	/* 多回線仕様追加 1997/09/03 Y.Matsukuma */
/* マルチ回線ユーザー設定 */
/* 注）かっこの位置は固定すること。ただし、(9)は除く。 */
CUB	D2W_MultiYourFaxNumber[]			= "Your Fax Number  ( )";
CUB	D2W_MultiYourName[]					= "YourName( )         ";
CUB	D2W_MultiYourKanaName[]				= "Kana ID ( )         ";	/* (JPN) */
CUB	D2W_MultiPhoneType[]				= "Phone Type( ):\0     ";
CUB	D2W_MultiTxRx[]						= "Tx/Rx     ( ):\0     ";
CUB	D2W_SelectTxRx[]					= "              Tx/Rx ";
CUB	D2W_SelectTx[]						= "              Tx    ";
CUB	D2W_SelectRx[]						= "              Rx    ";
CUB	D2W_MultiLineType[]					= "Line Type  (9):\0    ";	/* 回線表示位置には必ず9を定義（国別の表示位置対応） */
CUB	D2W_SelectLinePstn[]				= "               PSTN ";
CUB	D2W_SelectLinePbx[]					= "               PBX  ";
CUB	D2W_SetAccessNumber[]				= "PSTN Access No.  ( )";
#endif

/* Ｆｕｎｃｔｉｏｎ */
CUB	D2W_On1[]							= "                On  ";	/* ﾃﾞﾌｫﾙﾄがONではじまる場合 */
CUB	D2W_Off1[]							= "                Off ";
CUB	D2W_Off2[]							= "                Off ";	/* ﾃﾞﾌｫﾙﾄがOFFではじまる場合 */
CUB	D2W_On2[]							= "                On  ";
CUB	D2W_Off3[]							= "                 Off";
CUB	D2W_On3[]							= "                 On ";
CUB	D2W_On4[]							= "                 On ";
CUB	D2W_Off4[]							= "                 Off";
CUB	D2W_ModeOff[]						= "               Off  ";
CUB	D2W_Mode1[]							= "               Mode1";
CUB	D2W_Mode2[]							= "               Mode2";
CUB	D2W_Mode3[]							= "               Mode3";

/*----------------------------------*
 *	ユーザー設定
 *----------------------------------*/
/* 読み取りパラメータ */
/* 原稿読みとり幅 */
CUB	D2W_SelectScanWidth[]				= "Scan Width:      \0  ";
CUB	D2W_ScanA4[]						= "                 A4 ";
CUB	D2W_ScanB4[]						= "                 B4 ";
CUB	D2W_ScanA3[]						= "                 A3 ";

/* 優先モード */
CUB	D2W_SelectPrimaryMode[]				= "Primary:   \0        ";
CUB	D2W_PrimaryModeNormal[]				= "           Normal   ";
CUB	D2W_PrimaryModeFine[]				= "           Fine     ";
CUB	D2W_PrimaryModeSFine[]				= "           S Fine   ";
CUB	D2W_PrimaryModeGray[]				= "           Gray     ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	D2W_PrimaryModeFine_S[]				= "           Fine     ";
CUB	D2W_PrimaryModeSFine_S[]			= "           S Fine   ";
#endif

/* 優先原稿濃度 */
CUB	D2W_SelectPrimaryContrast[]			= "Contrast:    \0      ";
CUB	D2W_PrimaryContrastLight[]			= "             Light  ";
CUB	D2W_PrimaryContrastLittleLight[]	= "             Lighter";
CUB	D2W_PrimaryContrastNormal[]			= "             Normal ";
CUB	D2W_PrimaryContrastLittleDark[]		= "             Darker ";
CUB	D2W_PrimaryContrastDark[]			= "             Dark   ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	D2W_SelectPrimaryContrast_S[]		= "Contrast:    \0      ";
CUB	D2W_PrimaryContrastLight_S[]		= "             Light  ";
CUB	D2W_PrimaryContrastDark_S[]			= "             Dark   ";
#endif

CUB	D2W_SetScanParameters[]				= "Scan Parameters     ";

/* プリントパラメータ */
CUB	D2W_SelectReceiveReduction[]		= "Prnt Reduc Rate:\0   ";
CUB	D2W_AutoReduction[]					= "                Auto";
CUB	D2W_100[]							= "                100%";
CUB	D2W_97[]							= "                 97%";
CUB	D2W_91[]							= "                 91%";
CUB	D2W_81[]							= "                 81%";
CUB	D2W_75[]							= "                 75%";
CUB	D2W_InputThresholdValue0_85[]		= "Margin(0-85mm):   \0 ";
CUB	D2W_SelectPageCompound[]			= "Half Page Recpt: \0  ";
CUB	D2W_SetPrintParameters[]			= "Print Parameters    ";
#if (PRO_ROTATE == ENABLE)
CUB	D2W_SetRotateMargin[]				= "Rotate Print        ";
#endif

/* コピーパラメータ */
CUB	D2W_SelectSortingCopy[]				= "Sorting Copy:   \0   ";
CUB	D2W_SelectCopyReduction[]			= "Copy Reduc Rate:\0   ";	/* POPLAR_B以外 */
CUB	D2W_SetCopyParameters[]				= "Copy Parameters     ";	/* POPLAR_B以外 */

/* 記録紙サイズ */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	D2W_EnterPaperSize[]				= "Paper Size:  \0      ";
CUB	D2W_PaperSizeNone[]					= "             None   ";
CUB	D2W_PaperSizeA4[]					= "             A4     ";
CUB	D2W_PaperSizeB4[]					= "             B4     ";
CUB	D2W_PaperSizeLetter[]				= "             Letter ";
CUB	D2W_PaperSizeLegal[]				= "             Legal  ";
CUB	D2W_PaperSizeF4[]					= "             F4     ";
CUB	D2W_SetPaperSize[]					= "Set Paper Size      ";

 #if (PRO_PC_PRINT == ENABLE)	/* ＰＣプリント */
CUB	D2W_SelectPaperSizeNone[]			= "             None   ";	/* 不要かもしれない */
CUB	D2W_SelectPaperSizeA5[]				= "             A5_P   ";
  #if defined(USA)
CUB	D2W_SelectPaperSizeLetter[]			= "             Letter ";
  #else
CUB	D2W_SelectPaperSizeLetter[]			= "             Ltr_P  ";
  #endif
  #if defined(USA)
CUB	D2W_SelectPaperSizeA4[]				= "             A4_P   ";
  #else
CUB	D2W_SelectPaperSizeA4[]				= "             A4     ";
  #endif
  #if defined(USA) || defined(TWN) /* 1998/01/09 Y.Matsukuma */
CUB	D2W_SelectPaperSizeLegal[]			= "             Legal  ";
  #else
CUB	D2W_SelectPaperSizeLegal[]			= "             Legal_P";
  #endif
CUB	D2W_SelectPaperSizeB5R[]			= "             B5R_P  ";
CUB	D2W_SelectPaperSizeB4[]				= "             B4_P   ";
CUB	D2W_SelectPaperSizeA3[]				= "             A3_P   ";
CUB	D2W_SelectPaperSizeA4R[]			= "             A4R_P  ";
CUB	D2W_SelectPaperSizeLetterR[]		= "             LtrR_P ";
  #if defined(TWN) || defined(AUS)	/* 1998/01/09 Y.Matsukuma */
CUB	D2W_SelectPaperSizeF4[]				= "             F4     ";
  #else
CUB	D2W_SelectPaperSizeF4[]				= "             F4_P   ";
  #endif
CUB	D2W_SelectPaperSizeA5R[]			= "             A5R_P  ";
CUB	D2W_SelectPaperSizePostcard[]		= "             Post_P ";
CUB	D2W_SelectPaperSizeLD[]				= "             Ld_P   ";
CUB	D2W_SelectPaperSizeGLetterR[]		= "             GLtrR_P";
CUB	D2W_SelectPaperSizeExecutiveR[]		= "             ExeR_P ";
CUB	D2W_SelectPaperSizeInvoiceR[]		= "             InvR_P ";
CUB	D2W_SelectPaperSizeGLegal[]			= "             GLegl_P";
CUB	D2W_SelectPaperSizeGLetter[]		= "             GLtr_P ";
CUB	D2W_SelectPaperSizeCard[]			= "             Card_P ";
CUB	D2W_SelectPaperSizeExecutive[]		= "             Exe_P  ";
CUB	D2W_SelectPaperSizeB5[]				= "             B5_P   ";
CUB	D2W_SelectPaperSizeC5[]				= "             C5_P   ";
CUB	D2W_SelectPaperSizeHalfLetter[]		= "             HLtr_P ";
CUB	D2W_SelectPaperSizeInvoice[]		= "             Inv_P  ";
CUB	D2W_SelectPaperSizeB6[]				= "             B6_P   ";
CUB	D2W_SelectPaperSizeDL[]				= "             DL_P   ";
CUB	D2W_SelectPaperSizeCM10[]			= "             CM10_P ";
CUB	D2W_SelectPaperSizeA6[]				= "             A6_P   ";
CUB	D2W_SelectPaperSizeMonarch[]		= "             Mnc_P  ";
CUB	D2W_SelectPaperSize35[]				= "             3x5_P  ";
CUB	D2W_SelectPaperSizeUser[]			= "             User_P ";
 #endif
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */

/* コピー禁止 */
CUB	D2W_SelectCopyProtect[]				= "Copy Protect   :\0   ";

/* ポーズ */
CUB	D2W_SetDialingPause[]				= "Set Dialing Pause   ";
CUB	D2W_PauseTime[]						= "Time        :\0      ";	/* 注）ｼﾞｶﾝ (05-10): の（）の部分は実行時に作成します */

/* べル回数 */
CUB	D2W_SetNumberOfRings[]				= "Set # Of Rings      ";
CUB	D2W_NumberOfRings[]					= "#           :\0      ";	/* 注）ｶｲｽｳ   (1-9): の（）の部分は実行時に作成します */

/* リダイアル */
CUB	D2W_RedialCount[]					= "#           :\0      ";	/* 注）ｶｲｽｳ (02-10): の（）の部分は実行時に作成します */
CUB	D2W_SetNumberOfRedials[]			= "Set # Of Redials    ";
CUB	D2W_RedialInterval[]				= "Inter.      :\0      ";	/* 注）ｶﾝｶｸ   (1-5): の（）の部分は実行時に作成します */
CUB	D2W_SetRedialInterval[]				= "Set Redial Interval ";
CUB	D2W_SetRedial[]						= "Set Redial          ";

/* ECM */
CUB	D2W_SelectECMMode[]					= "ECM Mode:       \0   ";
CUB	D2W_SetECMMode[]					= "Set ECM Mode        ";

/* パスコード */
CUB	D2W_SetPasscode[]					= "Set Passcode        ";

/* 閉域通信設定 */
CUB	D2W_SelectClosedNetwork[]			= "Closed Net.:    \0   ";
CUB	D2W_SetClosedNetwork[]				= "Closed Network      ";

/* パスワード送信 */
CUB	D2W_SelectSecurityTransmission[]	= "Security Tx:    \0   ";
CUB	D2W_SetSecurityTransmission[]		= "Security Tx         ";

/* ダイレクトメール防止 */
CUB	D2W_SelectBlockJunkMail[]			= "Block Junk Fax:\0    ";
CUB	D2W_SetBlockJunkMailDial[]			= "Set BlockJunk Dial  ";
CUB	D2W_PrintBlockJunkMailDialList[]	= "Print BlockJunk Dial";
CUB	D2W_SetBlockJunkMail[]				= "Block Junk Fax      ";
CUB	D2W_BlockJunkMailSelectNumber[]		= "Select BlockJunk No.";
CUB D2W_SetSameNumber[]					= "Already Stored      ";

/* リモート診断 */
CUB	D2W_SelectRemoteDiagnostic[]		= "Service Mode:   \0   "; /* 1996/01/25 Eguchi */
CUB	D2W_SetRemoteDiagnostic[]			= "Set Service Mode    "; /* 1996/01/25 Eguchi */

/* メモリー送信 */
CUB	D2W_SelectMemoryTransmission[]		= "Memory Tx:      \0   ";
CUB	D2W_SetMemoryTransmission[]			= "Set Memory Tx       ";

/* サイレントオペレーション */
CUB	D2W_SelectSilentOperation[]			= "Silent Mode:    \0   ";
CUB	D2W_SetSilentOperation[]			= "Set Silent Mode     ";

/* プロテクトパスコード */
CUB	D2W_SetProtectPasscode[]			= "Protect Passcode    ";
CUB	D2W_ProtectPasscode[]				= "Protect Passcode    ";

/* オペレーションプロテクト */
CUB	D2W_OperationProtectOnOff[]			= "Opr.Protect:    \0   ";
CUB	D2W_SetOperationProtect[]			= "Set Opr. Protect    ";

/* ＰＩＮアクセスモードセット */
CUB	D2W_PINAccessMode[]					= "PIN Mode:      \0    ";
CUB	D2W_SetPINAccessMode[]				= "Set PIN Mode        ";

/* リングマスター */
#if (PRO_RING_MASTER == ENABLE)	/* by K.Watanabe 1998/08/18 */
CUB	D2W_SelectRingMaster[]				= "DRD:            \0   ";
CUB	D2W_SelectRingPattern[]				= "Ring Pattern:     \0 ";
CUB	D2W_RingPattern_A[]					= "                  A ";
CUB	D2W_RingPattern_B[]					= "                  B ";
CUB	D2W_RingPattern_C[]					= "                  C ";
CUB	D2W_RingPattern_D[]					= "                  D ";
CUB	D2W_RingPattern_E[]					= "                  E ";
CUB	D2W_RingPattern_F[]					= "                  F ";
CUB	D2W_RingPattern_G[]					= "                  G ";
CUB	D2W_RingPattern_H[]					= "                  H ";
CUB	D2W_SetRingMaster[]					= "Set DRD             ";
#endif

/* 済みスタンプ */
CUB	D2W_StampOnOff[]					= "Stamp:          \0   ";
CUB	D2W_SetStamp[]						= "Set Stamp           ";

/* ドラム寿命リセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* by K.Watanabe 1998/08/18 */
CUB	D2W_ResetDrumLife[]					= "Reset Drum Life     ";
#endif

/* 受信アラームセット */
#if defined(GBR)
CUB	D2W_RxAlarm[]						= "Audible Alarm:  \0   ";
CUB	D2W_SetRxAlarm[]					= "Set Rx Alarm        ";
#endif

/*----------------------------------*
 *	マーキュリー
 *----------------------------------*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
/* マーキュリー番号  */
CUB	D2W_MercuryNumberSet[]				= "Dial Prefix No      ";
/* マーキュリーポーズ  */
CUB	D2W_MercuryPauseSet[]				= "Set Prefix Pause    ";
CUB	D2W_SetMercury[]					= "Set Dial Prefix     ";
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* 保留メロディーセット */
CUB	D2W_SelectHoldMelody[]				= "Hold Melody    :\0   ";
#endif

/* リモート受信 */
#if (PRO_REMOTE_RX == ENABLE)			/* ＮＴＴ仕様のポプラＬで使用 98/01/26 T.Fukumoto */
CUB	D2W_SelectRemoteReceive[]			= "Remote Trans'  :\0   ";
#endif

/* オンフック受信 */
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	D2W_SelectOnHookReceive[]			= "Onhook Trans'  :\0   ";	/* 98/03/13 Add By T.Fukumoto */
#endif

/* ダイアルイン */
#if (PRO_DIALIN == ENABLE)
CUB	D2W_SetDialIn[]						= "Set Dial In         ";
CUB	D2W_DialInFax[]						= "Fax:            \0   ";
CUB	D2W_DialInTel1[]					= "Tel1:           \0   ";
CUB	D2W_DialInTel2[]					= "EXT.Tel:        \0   ";
CUB	D2W_DialInRings[]					= "Set Ring Time       ";
CUB	D2W_DialInRings10_60[]				= "(10-60)      \0      ";
#endif

/*----------------------------------*
 *	カバーページ
 *----------------------------------*/
CUB	D2W_MessageOnOff[]					= "Cover Page:     \0   ";
CUB	D2W_MessageTx[]						= "Set Cover Page      ";
CUB	D2W_SetCoverPageMessage[]			= "Cover Page          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	D2W_MessageSet[]					= "Enter Cover Page    ";

/*----------------------------------*
 *	枚数設定
 *----------------------------------*/
CUB	D2W_InputPageCount[]				= "Enter # Of Pages    ";

#if defined(POPLAR_F)
 #if defined(JP1)
	CUB	D2W_PageCount1_30[]					= "           (1-50):\0 ";
 #else
	CUB	D2W_PageCount1_30[]					= "           (1-30):\0 ";
 #endif
#else
 #if defined(POPLAR_N) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ポプラＬ（ＮＴＴ仕様） by K.Watanabe 1998/03/16 */
	CUB	D2W_PageCount1_30[]					= "           (1-30):\0 ";
 #else
	CUB	D2W_PageCount1_30[]					= "           (1-50):\0 ";
 #endif
#endif

/*----------------------------------*
 *	部門管理
 *----------------------------------*/
/* 部門管理プロテクトセット */
CUB	D2W_DepartmentProtect[]				= "Dept. Protect:  \0   ";
CUB	D2W_SetDepartmentProtect[]			= "Set Dept. Protect   ";

/* 部門コードセット */
CUB	D2W_DepartmentSelectNumber[]		= "Select Department No";

/* 部門管理セット */
CUB	D2W_DepartmentOnOff[]				= "Dept. On/Off:   \0   ";
CUB	D2W_SetDepartmentOnOff[]			= "Set Dept. On/Off    ";

#if (PRO_DEPART_NEW_LIST == ENABLE)		/* 追記 By S.Fukui Jan.7,1998 */
/* 簡易部門毎時間管理リスト関連 */
CUB	D2W_EraseDepartTimeListMode[]		= "Erase Dp.TimeList   ";
CUB	D2W_EraseDepartCode[]				= "    :Erase Dpt. Code";	/* 先頭４文字は部門ｺｰﾄﾞ表示 */
CUB D2W_DepartCodeFull[]				= "Dept.Code  Full     ";
#endif

/*----------------------------------*
 *	一括送信
 *----------------------------------*/
CUB	D2W_SelectBatchBoxNumber[]			= "Select Batch Box    ";
CUB	D2W_TranssmissionTime[]				= "Transmit Time       ";
CUB	D2W_EraseBatchBoxMode[]				= "Erase Batch Box     ";
CUB	D2W_EraseBatchDocumentMode[]		= "Erase Batch Doc.    ";

CUB	D2W_PrintBatchBoxMode[]				= "Print Box List      ";
CUB	D2W_PrintBatchDocListMode[]			= "Print Doc. List     ";
CUB	D2W_PrintBatchDocMode[]				= "Print Batch Doc.    ";
CUB	D2W_BatchBoxNumber[]				= "Enter Box No.     \0 ";
CUB	D2W_BatchFileNumber[]				= "Enter File No.   \0  ";

/*----------------------------------*
 *	セキュリティ受信
 *----------------------------------*/
/* セキュリティ受信セット */
CUB	D2W_SecurityReceive[]				= "Security Rx:    \0   ";
CUB	D2W_SetSecurityReceive[]			= "Set Security Rx     ";

/* メモリ受信原稿プリント */
CUB	D2W_PrintMemoryReceiveDocMode[]		= "Print Mem Rx Doc.   ";

/*----------------------------------*
 *	Ｆコード
 *----------------------------------*/
#if (PRO_F_CODE == ENABLE)
CUB	D2W_SelectFcodeBoxNumber[]			= "Select F-Code Box   ";
CUB	D2W_EnterFcodeBoxName[]				= "  :Box Name\0        ";
CUB	D2W_EnterFcodeSubAddress[]			= "  :Sub-Address No.  ";
CUB	D2W_EnterFcodePassword[]			= "  :Password         ";
CUB	D2W_SelectFcodeBoxKind[]			= "Box Type   :\0       ";  /* modified by honda 1997/09/18  NULLの位置を左に1ｼﾌﾄ */
CUB	D2W_FcodeBulletinBoardBox[]			= "            Bulletin";
CUB	D2W_FcodeConfidentialBox[]			= "            Security";
#if (PRO_FCODE_RELAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
CUB	D2W_FcodeRelayBox[]					= "            ﾁｭｳｹｲ   ";
#endif
CUB	D2W_SelectFcodeRxProhibition[]		= "Rx Protect     :\0   ";
CUB	D2W_SelectFcodeRxDocPrint[]			= "Auto Print     :\0   ";
CUB	D2W_SelectFcodeRxDocUpperWrite[]	= "Overwrite Doc. :\0   ";
CUB	D2W_SelectFcodeTxDocClear[]			= "Erase Tx Doc.  :\0   ";
CUB	D2W_FcodeDocumentHoldTime[]			= "F-Code Doc Hold Time";
CUB	D2W_HoldTime0_31[]					= "Hold Time(0-31)  :\0 ";
CUB	D2W_SelectFcodeStoreDocAdd[]		= "Add Document   :\0   ";
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/11/13 */
CUB	D2W_StoreFcodeDocument[]			= "F-Code Doc F:       ";
#else
CUB	D2W_StoreFcodeDocument[]			= "F-Code Doc.  File:  ";
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
 #if (PRO_FCODE_RELAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
CUB	D2W_InputRelayNumber[]				= "ﾊｲｼﾝｻｷ ｦ ﾄﾞｳｿﾞ      ";
CUB D2W_SetRelayTTI[][21]				= {
										  "ﾊｲｼﾝｼﾞ ﾊｯｼﾝﾓﾄ:\0     ",
										  "              ﾂｹﾅｲ  ",
										  "              ｿﾄﾂﾞｹ ",
										  "              ｳﾜｶﾞｷ ",
};
 #endif
#endif
CUB	D2W_SameNumber[]					= "Sub-Address In Use  ";

/*----------------------------------*
 *	ＰＣプリントボード初期化
 *----------------------------------*/
#if (PRO_PC_PRINT == ENABLE)
CUB	D2W_BoardReset[]					= "Reset Printer Opt.  ";
#endif

/*----------------------------------*
 *	暗号化
 *----------------------------------*/
#if (PRO_CIPHER == ENABLE)
CUB	D2W_EnterCipherKeyName[]			= " :Key Title\0        ";
CUB	D2W_EnterCipherKey[]				= " :Set Key  \0        ";
CUB	D2W_EnterCipherKeyClue[]			= " :Key Clue \0        ";
CUB	D2W_InputCipherRxDocNumber[]		= "Number Of Rx Doc.:\0 ";
CUB	D2W_InputCipherExtensionKey[]		= "Key Extension   :\0  ";
CUB	D2W_SelectCipherDocErrRemoval[]		= "Correct Error  :\0   ";
CUB	D2W_SelectCipherKeySetKind[]		= "Set Key     :\0      ";
CUB	D2W_CipherKeySetDefault[]			= "             Default";
CUB	D2W_CipherKeySetKeyBook[]			= "             KeyBook";
CUB	D2W_CipherKeySetDirect[]			= "             Direct ";
CUB	D2W_InputCipherDefaultKeyNo[]		= "Key Number  (0-9):\0 ";
 #if defined(USA)
CUB	D2W_InputServiceLabelPosition[]		= "Offset(1-14.5\"):\0   ";  /* by t.fukumoto 1997/12/12 */
 #else
CUB	D2W_InputServiceLabelPosition[]		= "Offset  (2-36cm):\0  ";
 #endif
CUB	D2W_CipherSelectNumber[]			= "Select Key Number   ";
CUB	D2W_CipherExecute[]					= "Scrambling     99/99";
CUB	D2W_DecipherExecute[]				= "Descrambling   99/99";
CUB	D2W_CipherExecuteError[]			= "Scrambling Error    ";
CUB	D2W_DecipherExecuteError[]			= "Descrambling Error  ";
CUB	D2W_DecipherKeyError[]				= "Invalid Key         ";
CUB	D2W_ConfirmDecipherContinue[]		= "ContDscrm Entr/Cancl";
CUB	D2W_DecipherDocument[]				= "Descrambled Document";
CUB	D2W_StopCipherExecute[]				= "Stop Scrambling     ";
CUB	D2W_StopDecipherExecute[]			= "Stop Descrambling   ";
#endif
CUB	D2W_InputPrintPageNumber[]			= "Num(1-99)       :\0  ";
CUB	D2W_ProgressRate[]					= " 0%            100% ";

/*----------------------------------*
 *	クラス１
 *----------------------------------*/
CUB	D2W_SetRS232CParameter[]			= "Set RS232C          ";
CUB	D2W_SetRS232CPCFaxInitial[]			= "PC-FAX Initial      ";

/* ＲＳ２３２Ｃボーレート */
CUB	D2W_SelectRS232CBaudRate[]			= "Baud Rate :\0        ";
CUB	D2W_RS232CVariable[]				= "           Variable ";
CUB	D2W_RS232C600bps[]					= "             600bps ";
CUB	D2W_RS232C1200bps[]					= "            1200bps ";
CUB	D2W_RS232C2400bps[]					= "            2400bps ";
CUB	D2W_RS232C4800bps[]					= "            4800bps ";
CUB	D2W_RS232C9600bps[]					= "            9600bps ";
CUB	D2W_RS232C19200bps[]				= "           19200bps ";

/* ＲＳ２３２Ｃパリティビット設定 */
CUB	D2W_SelectParity[]					= "Parity        :\0    ";
CUB	D2W_RS232CNone[]					= "               None ";
CUB	D2W_RS232COdd[]						= "               Odd  ";
CUB	D2W_RS232CEven[]					= "               Even ";

/* ＲＳ２３２Ｃストップビット設定 */
CUB	D2W_Select232CStopBit[]				= "Stop Bit     :\0     ";
CUB	D2W_RS232C1bit[]					= "              1 bit ";
CUB	D2W_RS232C2bit[]					= "              2 bit ";

/* ＲＳ２３２Ｃデータ長設定 */
CUB	D2W_Select232CDataLength[]			= "Data Length  :\0     ";
CUB	D2W_RS232C7bit[]					= "              7 bit ";
CUB	D2W_RS232C8bit[]					= "              8 bit ";

/* クラス１関連追加 */
CUB	D2W_PC_FAX_Scan[]					= "PC-FAX Scan         "; /* 翻訳まだ1996/09/12*/
CUB	D2W_PC_FAX_Print[]					= "PC-FAX Print        "; /* 翻訳まだ1996/09/12*/
CUB	D2W_PC_FAX_Connect[]				= "PC-FAX Connection   "; /* 翻訳まだ1996/09/12*/
CUB	D2W_PC_FAX_InitialError[]			= "PC-FAX Initial Error"; /* 翻訳まだ1996/09/12*/
CUB	D2W_PC_FAX_Complete[]				= " **   Complete   ** ";
CUB	D2W_PC_FAX_InUse[]					= "PC-FAX In Use       "; /* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
CUB	D2W_ReceiveInFax[]					= "Receive In Fax ?    "; /* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */

/* 送信時、部門コード入力 */
CUB	D2W_EnterDepartmentCode[]			= "Enter Dept. Code    ";

/* 送信時、ダイヤル番号入力 */
CUB	D2W_EnterDialNumber[]				= "Enter Fax Number    ";

/* 送信時、ＰＩＮ番号入力 */
CUB	D2W_EnterPinNumber[]				= "Enter PIN Number    ";

/************************************************
** Dial-UpｲﾝﾀｰﾈｯﾄFAX関係	1998/03/12 by K.Okada
************************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/** ユーザ登録 */
CUB D2W_EMailSettingMode[]				= "  E-Mail Setting    ";
CUB D2W_SetUserDataMode[]				= "   Set User Data    ";
CUB D2W_SetUserData[]					= "Set User Data       ";
/*↓この2つはこの順番で並べて記述*/
CUB D2W_NewEntry[]						= "New Entry?          ";
CUB D2W_UpdateSetting[]					= "Update Setting?     ";
CUB D2W_NewMailBox[]					= "New Mail Box?  :\0   ";
/*↓この2つはこの順番で並べて記述*/
CUB D2W_No[]							= "                No  ";
CUB D2W_Yes[]							= "                Yes ";
CUB D2W_UserCodeNumber[]				= "Your Code No.       ";
CUB D2W_UserCodeNumberAgain[]			= "Code No. Again      ";
CUB D2W_EnterYourCodeNumber[]			= "Enter Your Code No. ";
CUB D2W_ISP_Name[]						= "ISP Name            ";
CUB D2W_AccessPoint[]					= "Access Point        ";
/*↓この3つはこの順番で並べて記述*/
CUB D2W_1stTime[]						= ":1st  \0             ";
CUB D2W_2ndTime[]						= ":2nd  \0             ";
CUB D2W_3rdTime[]						= ":3rd  \0             ";
CUB D2W_UserName[]						= "Your Name           ";
CUB D2W_PPP_LoginID[]					= "PPP-ID              ";
CUB D2W_POP_LoginID[]					= "POP-ID              ";
/*↓この2つはこの順番で並べて記述*/
CUB D2W_PPP_Password[]					= "PPP-PWD             ";
CUB D2W_PPP_PasswordAgain[]				= "Again               ";
/*↓この2つはこの順番で並べて記述*/
CUB D2W_POP_Password[]					= "POP-PWD             ";
CUB D2W_POP_PasswordAgain[]				= "Again               ";
CUB D2W_MailAddress[]					= "Address             ";
CUB D2W_PPP_Auth[]						= "PPP Auth            ";
/*↓この3つはこの順番で並べて記述*/
CUB D2W_PPP_PAP[]						= ":PAP  \0             ";
CUB D2W_PPP_CHAP[]						= ":CHAP \0             ";
CUB D2W_PPP_NoneAuth[]					= ":NONE \0             ";
CUB D2W_Client[]						= "Client              ";
CUB D2W_ISP_Server[]					= "Server              ";
CUB D2W_Gateway[]						= "Gateway             ";
CUB D2W_DNS_Server[]					= "DNS Server          ";
CUB D2W_Primary[]						= ":Primary  \0         ";
CUB D2W_Secondary[]						= ":Secondary\0         ";
CUB D2W_SMTP_Server[]					= "SMTP Server         ";
CUB D2W_POP_Server[]					= "POP Server          ";

/** 機器動作設定 */
#if (0)
//CUB D2W_SetMachineStateMode[]			= "   Auto Mail Receive";
#endif
CUB D2W_SetMachineStateMode[]			= "   Mail Rx Setting  ";
CUB D2W_AutoReceive[]					= "Auto Check Mail:\0   ";
CUB D2W_AutoDownload[]					= "Auto Download : \0   ";
CUB D2W_AutoPrint[]						= "Auto Print    : \0   ";
CUB D2W_DeleteMail[]					= "Delete Mail   : \0   ";
CUB D2W_MailHoldTime[]					= "Mail Hold Days      ";
CUB D2W_Days1_31[]						= "Days(1-31)          ";
CUB D2W_RxDuringTx[]					= "Tx with Rx    : \0   ";
CUB D2W_SetMachineState[]				= "Mail Rx Setting     ";
CUB D2W_AutoRxStartTime[]				= "Start Time          ";
CUB D2W_AutoRxEndTime[]					= "End Time            ";
CUB D2W_IntervalTime[]					= "Interval Time       ";

/** トーン検出設定 */
#if (0)
CUB D2W_SetToneDetectMode[]				= "   Set Tone Detect  ";
CUB D2W_SetDialParameter[]				= "Set Tone Detect     ";
CUB D2W_DialToneOn[]					= "Dial Tone:      \0   ";
CUB D2W_BusyToneOn[]					= "Busy Tone:      \0   ";
#endif

/** ユーザデータ消去 */
CUB D2W_EraseUserDataMode[]				= "   Erase User Data  ";
CUB D2W_EraseUserData[]					= "Erase User Data     ";

/**  メール設定リスト */
CUB D2W_PrintUserDataMode[]				= "   Print User Data  ";
CUB D2W_PrintUserData[]					= "Print User Data     ";

/** コマンド入力表示 */
CUB D2W_EnterMailAddress[]				= "Enter Mail Address  ";

/** 宛先 */
CUB D2W_SetMailAddressMode[]			= "  Mail Address      ";
CUB D2W_SetMailAddress[]				= "   Set Mail Address ";
CUB D2W_AddressName[]					= "Name                ";
CUB D2W_EraseMailAddressMode[]			= "   Erase MailAddress";
CUB D2W_EraseMailAddress[]				= "Erase Mail Address  ";
CUB D2W_PrintMailAddressMode[]			= "   Print MailAddress";
CUB D2W_PrintMailAddress[]				= "Print Mail Address  ";
CUB D2W_SetMailGroup[]					= "   Set Mail Group   ";
CUB D2W_MailGroupSetting[]				= "Mail Group          ";
CUB D2W_EraseMailGroupMode[]			= "   Erase Mail Group ";
CUB D2W_EraseMailGroup[]				= "Erase Mail Group    ";
CUB D2W_PrintMailGroupMode[]			= "   Print Mail Group ";
CUB D2W_PrintMailGroup[]				= "Print Mail Group    ";
CUB D2W_PressOnetouch[]					= "Press One-Touch     ";

/** サービスファンクション */
CUB D2W_InitEngineBoard[]				= "Initialize I-FAX    ";
CUB D2W_IP_EchoRequest[]				= "IP Packet Echo Req. ";
CUB D2W_INF_Complete[]					= " **   Complete   ** ";
CUB	D2W_SF_TTL_Test[]					= "TTL Test            "; /*1998/6/9 Eguchi*/

/** 設置オペレーション */
CUB D2W_INF_InitialError[]				= "I-FAX Initial Error ";

/** コマンド予約 */
CUB D2W_ReviewMailComMode[]				= "  Review Mail Com.  ";
CUB D2W_CancelMailCom[]					= "Cancel Mail Com.    ";
CUB D2W_PrintMailComMode[]				= "   Print Mail Com.  ";
CUB D2W_PrintMailCom[]					= "Print Mail Com.     ";
CUB D2W_PrintStoredMailMode[]			= "   Print Stored Mail";
CUB D2W_PrintStoredMail[]				= "Print Stored Mail   ";
CUB D2W_EnterMailCommandNo[]			= "Enter Command No.   ";

/** ジャーナルプリント */
CUB D2W_PrintMailJounalMode[]			= "   Print Mail Jrnl. ";
CUB D2W_PrintMailJournal[]				= "Print Mail Jrnl.    ";

/** 受信 */
CUB D2W_ManualReceiveMail[]				= "   Manual Rcv. Mail ";
CUB D2W_ReceiveMailMode[]				= "  Receive Mail      ";
CUB D2W_PrintReceiveMailMode[]			= "   Print Rcv. Mail  ";
CUB D2W_PrintReceiveMail[]				= "Print Rcv. Mail     ";

/** 動作中および終了表示 */
CUB D2W_INF_Abort[]						= " **  Terminate  **  ";
CUB D2W_INF_NoNewMail[]					= " **  No New Mail  **";
CUB D2W_SendingMail[]					= "Send Mail           ";
CUB D2W_ReceivingMail[]					= "Receive Mail        ";
CUB D2W_INF_Creating[]					= "** Creating Email **";
CUB D2W_INF_Dialing[]					= "   ** Dialing **    ";
CUB D2W_INF_Connecting[]				= "  ** Connecting **  ";
CUB D2W_INF_Sending[]					= "   ** Sending **    ";
CUB D2W_INF_Receiving[]					= "  ** Receiving **   ";
CUB D2W_INF_Checking[]					= "   ** Checking **   ";

CUB D2W_INF_PrintRcvReport[]			= "Print Rcv. Report   ";

/** PTTテスト信号送出サービスファンクション */
CUB D2W_PTT_TestMode[]					= "PTT Test Mode       ";
CUB D2W_PTT_Setting[]					= "PTT Test Setting    ";
CUB D2W_DataRate[]						= "    :Data Rate      ";
CUB D2W_SymbolRate[]					= "    :Symbol Rate    ";
CUB D2W_CarrierBias[]					= "    :Carrier Bias   ";
CUB D2W_SecondChannel[]					= "    :2nd Channel    ";
CUB D2W_UpperBandEdge[]					= "    :Upper Band Edge";
CUB D2W_CarrierBiasRange[]				= "[-100<-->100]       ";
CUB D2W_BandEdgeRange[]					= "[0-22(dB)]          ";
CUB D2W_INF_Mode[]						= "    :Mode           ";

/* PTTテスト信号種類 */
/*↓この順番で並べて記述*/
CUB D2W_DTMF_Tone0[]					= "%TT00               ";
CUB D2W_DTMF_Tone1[]					= "%TT01               ";
CUB D2W_DTMF_Tone2[]					= "%TT02               ";
CUB D2W_DTMF_Tone3[]					= "%TT03               ";
CUB D2W_DTMF_Tone4[]					= "%TT04               ";
CUB D2W_DTMF_Tone5[]					= "%TT05               ";
CUB D2W_DTMF_Tone6[]					= "%TT06               ";
CUB D2W_DTMF_Tone7[]					= "%TT07               ";
CUB D2W_DTMF_Tone8[]					= "%TT08               ";
CUB D2W_DTMF_Tone9[]					= "%TT09               ";
CUB D2W_DTMF_ToneAst[]					= "%TT0A               ";
CUB D2W_DTMF_ToneSharp[]				= "%TT0B               ";
CUB D2W_DTMF_ToneA[]					= "%TT0C               ";
CUB D2W_DTMF_ToneB[]					= "%TT0D               ";
CUB D2W_DTMF_ToneC[]					= "%TT0E               ";
CUB D2W_DTMF_ToneD[]					= "%TT0F               ";
CUB D2W_V21Ch1MkSymbol[]				= "%TT10               ";
CUB D2W_V21Ch2MkSymbol[]				= "%TT11               ";
CUB D2W_V23BwardChMkSymbol[]			= "%TT12               ";
CUB D2W_V23FwardChMkSymbol[]			= "%TT13               ";
CUB D2W_V22CallMk600bps[]				= "%TT14               ";
CUB D2W_V22CallMk1200bps[]				= "%TT15               ";
CUB D2W_V22bisCallMk2400bps[]			= "%TT16               ";
CUB D2W_V22AnswerSignal[]				= "%TT17               ";
CUB D2W_V22bisAnswerSignal[]			= "%TT18               ";
CUB D2W_V21Ch1SpSymbol[]				= "%TT19               ";
CUB D2W_V21Ch2SpSymbol[]				= "%TT1A               ";
CUB D2W_V23BwardChSpSymbol[]			= "%TT1B               ";
CUB D2W_V23FwardChSpSymbol[]			= "%TT1C               ";
CUB D2W_V32_9600bps[]					= "%TT20               ";
CUB D2W_V32bis14400bps[]				= "%TT21               ";
CUB D2W_V32TCM9600bps[]					= "%TT22               ";
CUB D2W_V32TCM14400bps[]				= "%TT23               ";
CUB D2W_V32bisTCM7200bps[]				= "%TT24               ";
CUB D2W_V32_4800bps[]					= "%TT25               ";
CUB D2W_OffFook[]						= "%TT30               ";
CUB D2W_V25AnswerTone[]					= "%TT31               ";
CUB D2W_1800HzGuardTone[]				= "%TT32               ";
CUB D2W_V25Send1300Hz[]					= "%TT33               ";
CUB D2W_FaxSend1100Hz[]					= "%TT34               ";
CUB D2W_BellAnswer2225hz[]				= "%TT35               ";
CUB D2W_V21Ch2[]						= "%TT40               ";
CUB D2W_V27ter2400bps[]					= "%TT41               ";
CUB D2W_V27ter4800bps[]					= "%TT42               ";
CUB D2W_V29_7200bps[]					= "%TT43               ";
CUB D2W_V29_9600bps[]					= "%TT44               ";
CUB D2W_V17_7200bpsL_Train[]			= "%TT45               ";
CUB D2W_V17_7200bpsS_Train[]			= "%TT46               ";
CUB D2W_V17_9600bpsL_Train[]			= "%TT47               ";
CUB D2W_V17_9600bpsS_Train[]			= "%TT48               ";
CUB D2W_V17_12000bpsL_Train[]			= "%TT49               ";
CUB D2W_V17_12000bpsS_Train[]			= "%TT4A               ";
CUB D2W_V17_14400bpsL_Train[]			= "%TT4B               ";
CUB D2W_V17_14400bpsS_Train[]			= "%TT4C               ";
CUB D2W_VFC_Modulation[]				= "%TT5\0               ";
CUB D2W_V34_Modulation[]				= "%TT6\0               ";
/*↑この順番で並べて記述*/

/* Gurad Tone */
/*↓この3個はこの順番で並べて記述*/
CUB D2W_GT1800hz[]						= "Guard Tone 1800 Hz  ";
CUB D2W_GT550hz[]						= "Guard Tone 550 Hz   ";
CUB D2W_NoGuardTone[]					= "No Guard Tone       ";

/* Mode */
/*↓この2個はこの順番で並べて記述*/
CUB D2W_OriginateMode[]					= "Originate Mode      ";
CUB D2W_AnswerMode[]					= "Answer Mode         ";

/* Data Rate */
/*↓この12個はこの順番で並べて記述*/
CUB D2W_2400bps[]						= "2400 bps            ";
CUB D2W_4800bps[]						= "4800 bps            ";
CUB D2W_7200bps[]						= "7200 bps            ";
CUB D2W_9600bps[]						= "9600 bps            ";
CUB D2W_12000bps[]						= "12000 bps           ";
CUB D2W_14400bps[]						= "14400 bps           ";
CUB D2W_16800bps[]						= "16800 bps           ";
CUB D2W_19200bps[]						= "19200 bps           ";
CUB D2W_21600bps[]						= "21600 bps           ";
CUB D2W_24000bps[]						= "24000 bps           ";
CUB D2W_26400bps[]						= "26400 bps           ";
CUB D2W_28800bps[]						= "28800 bps           ";
CUB D2W_31200bps[]						= "31200 bps           ";
CUB D2W_33600bps[]						= "33600 bps           ";

/* Symbol Rate */
/*↓この6つはこの順番で並べて記述*/
CUB D2W_2400baud[]						= "2400 baud           ";
CUB D2W_2800baud[]						= "2800 baud           ";
CUB D2W_3000baud[]						= "3000 baud           ";
CUB D2W_3200baud[]						= "3200 baud           ";
CUB D2W_3429baud[]						= "3429 baud           ";

/* Second Channel */
/*↓この2つはこの順番で並べて記述*/
CUB D2W_Disable[]						= "Disable             ";
CUB D2W_Enable[]						= "Enable              ";

/* Upper Band Edge */
/*↓この11個はこの順番で並べて記述*/
CUB D2W_V34BandEdge0Db[]				= "a = 0[dB]           ";
CUB D2W_V34BandEdge2Db[]				= "a = 2[dB]           ";
CUB D2W_V34BandEdge4Db[]				= "a = 4[dB]           ";
CUB D2W_V34BandEdge6Db[]				= "a = 6[dB]           ";
CUB D2W_V34BandEdge8Db[]				= "a = 8[dB]           ";
CUB D2W_V34BandEdge10Db[]				= "a = 10[dB]          ";
CUB D2W_V34BandEdgeG1Db[]				= "b=0.5[dB], c=1.0[dB]";
CUB D2W_V34BandEdgeG2Db[]				= "b=1.0[dB], c=2.0[dB]";
CUB D2W_V34BandEdgeG3Db[]				= "b=1.5[dB], c=3.0[dB]";
CUB D2W_V34BandEdgeG4Db[]				= "b=2.0[dB], c=4.0[dB]";
CUB D2W_V34BandEdgeG5Db[]				= "b=2.5[dB], c=5.0[dB]";
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	ＦＡＸワープ
 *----------------------------------*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modified by SMuratec L.Z.W 2003/09/01 */
CUB	D2W_FaxWarpMode[]					= "    FAXﾜｰﾌﾟ         ";
#else
CUB	D2W_FaxWarpMode[]					= "  FAXﾜｰﾌﾟ           ";
#endif /* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	D2W_EnterFaxWarpMode[]				= "   FAXﾜｰﾌﾟ ｾｯﾄ      ";
CUB	D2W_PrintFaxWarpMode[]				= "   FAXﾜｰﾌﾟ ﾘｽﾄ      ";
CUB	D2W_SetFaxWarpMode[]				= "   FAXﾜｰﾌﾟ ｾｯﾃｲ     ";
CUB	D2W_EnterFaxWarp[]					= "FAXﾜｰﾌﾟ ｾｯﾄ         ";
CUB	D2W_PrintFaxWarp[]					= "FAXﾜｰﾌﾟ ﾘｽﾄ         ";
CUB	D2W_SetFaxWarp[]					= "FAXﾜｰﾌﾟ:\0           ";
CUB	D2W_WarpSelectNumber[]				= "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ ";
CUB	D2W_WarpTime[]						= "ｼﾃｲ ｼﾞｺｸ            ";
CUB	D2W_WarpWeek[][21]					= {
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
										  "ﾆﾁ                  ",
										  "ｹﾞﾂ                 ",
										  "ｶ                   ",
										  "ｽｲ                  ",
										  "ﾓｸ                  ",
										  "ｷﾝ                  ",
										  "ﾄﾞ                  ",
										  " *                  ",
#endif	/* End of defined(HINOKI3) */
};
CUB	D2W_SelectWarpRxDocPrint[][21]		= {
										  "   ﾄﾞｳｼﾞ ﾌﾟﾘﾝﾄ: OFF ",
										  "   ﾄﾞｳｼﾞ ﾌﾟﾘﾝﾄ: ON  ",
};

/* ＷＡＲＰ転送先ワーディング追加 By O.Kimoto 1999/02/08 */
CUB	D2W_WarpAltNumber[]					= "ﾃﾝｿｳ ﾊﾞﾝｺﾞｳ         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */

#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	ナンバーディスプレイ
 *----------------------------------*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modified by SMuratec L.Z.W 2003/09/01 */
CUB	D2W_NumberDisplayMode[]				= "    ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ   ";
#else
CUB	D2W_NumberDisplayMode[]				= "  ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ     ";
#endif /* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	D2W_EnterNumberDisplayMode[]		= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ｾｯﾄ";
CUB	D2W_PrintNumberDisplayMode[]		= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘｽﾄ";
CUB	D2W_SetNumberDisplayMode[]			= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲｾｯﾃｲ";
CUB	D2W_EnterNumberDisplay[]			= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ｾｯﾄ   ";
CUB	D2W_PrintNumberDisplay[]			= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘｽﾄ   ";
CUB	D2W_SetNumberDisplay[]				= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ:\0     ";
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* By H.Fujimura 1999/01/07 */
CUB	D2W_Set_ND_Warp[]					= "NDﾜｰﾌﾟ:\0            ";
 #endif
CUB	D2W_ND_SelectNumber[]				= "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ ";
CUB	D2W_ND_TelMode[][21]				= {
										  "ﾃﾞﾝﾜｷ ｾﾂｿﾞｸ:\0       ",
										  "             OFF    ",
/*										  "             PHONE1 ",*/
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/24 */
										  "             TEL    ",
#else
										  "             PHONE2 ",
#endif
};
CUB	D2W_ND_NoNotice[]					= "ﾋﾂｳﾁ                ";
CUB	D2W_ND_OutOfDisp[]					= "ﾋｮｳｼﾞ ｹﾝｶﾞｲ         ";
CUB	D2W_ND_PublicTel[]					= "ｺｳｼｭｳ ﾃﾞﾝﾜ          ";
CUB	D2W_ND_Parameter[]					= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾊﾟﾗﾒｰﾀ";
CUB	D2W_Print_ND_JournalMode[]			= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘﾚｷ";
CUB	D2W_Print_ND_Journal[]				= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘﾚｷ   ";
#endif

/*----------------------------------*
 *	通信確認
 *----------------------------------*/
CUB	D2W_ConfirmReport[]					= "Conf.Report    :\0   ";

/*----------------------------------*
 *	オペレーションプロテクト
 *----------------------------------*/
CUB	D2W_OperationProtected[]			= "Operation Protected ";

#if (PRO_COPY_FAX_MODE == ENABLE)
/*----------------------------------*
 *	コピーモード
 *----------------------------------*/
CUB	D2W_ChangeManual[]					= "      Tray \x7E Enter  ";	/* \x7E = → */
#endif

#if (PRO_FBS == ENABLE)
/*----------------------------------*
 *	ブック送信
 *----------------------------------*/
CUB	D2W_SetBookTxDocumentSize[]			= "Enter Scan Size     ";
CUB	D2W_SetBookTxNextDocument[]			= "Set Next Document   ";

CUB	D2W_NextBookDocScanStart[]			= "Start Scan \x7E Next   ";	/* \x7E = → */
CUB	D2W_NextBookDocTxStart[]			= "Tx Start \x7E Start    ";	/* \x7E = → */
CUB	D2W_NextBookDocScanEnd[]			= "End Scan \x7E Enter    ";	/* \x7E = → */
#endif

/* 紙サイズ（R → 0x01(OPR_PAPER_SIZE_R)で定義して下さい） */
CUB	D2W_PaperSize_None[]				= "None\0";
CUB	D2W_PaperSize_A5[]					= "A5\0  ";
CUB	D2W_PaperSize_Letter[]				= "Ltr\0 ";
#if defined(USAOKI)	/* 1998/02/04 Y.Matsukuma */
CUB	D2W_PaperSize_A4[]					= "LT\0  ";
#else
CUB	D2W_PaperSize_A4[]					= "A4\0  ";
#endif
CUB	D2W_PaperSize_Legal[]				= "Legl\0";
CUB	D2W_PaperSize_B5R[]					= "B5\x01\0 ";
CUB	D2W_PaperSize_B4[]					= "B4\0  ";
CUB	D2W_PaperSize_A3[]					= "A3\0  ";
CUB	D2W_PaperSize_A4R[]					= "A4\x01\0 ";
CUB	D2W_PaperSize_LetterR[]				= "Ltr\x01\0";
CUB	D2W_PaperSize_F4[]					= "F4\0  ";
CUB	D2W_PaperSize_A5R[]					= "A5\x01\0 ";
CUB	D2W_PaperSize_Postcard[]			= "Post\0";
CUB	D2W_PaperSize_LD[]					= "Ld\0  ";
CUB	D2W_PaperSize_GLetterR[]			= "GLtr\x01";
CUB	D2W_PaperSize_ExecutiveR[]			= "Exe\x01\0";
/*  #if (PRO_KEYPANEL == PANEL_POPLAR_B)  *//* modified by honda 1997/11/14 */
/*   #if defined(USA) || defined(GBR)  */
CUB	D2W_PaperSize_HalfLetterR[]			= "HLtr\x01";  /* added by honda 1997/10/04 */
/*   #else  */
/*  CUB	D2W_PaperSize_InvoiceR[]			= "Inv\x01\0";  */
/*   #endif  */
/*  #else  */
/*	CUB	D2W_PaperSize_InvoiceR[]			= "Inv\x01\0";  */
/*  #endif  */
CUB	D2W_PaperSize_GLegal[]				= "GLegl";
CUB	D2W_PaperSize_GLetter[]				= "GLtr\0";
CUB	D2W_PaperSize_Card[]				= "Card\0";
CUB	D2W_PaperSize_Executive[]			= "Exe\0 ";
CUB	D2W_PaperSize_B5[]					= "B5\0  ";
CUB	D2W_PaperSize_C5[]					= "C5\0  ";
CUB	D2W_PaperSize_HalfLetter[]			= "HLtr\0";
CUB	D2W_PaperSize_Invoice[]				= "Inv\0 ";
CUB	D2W_PaperSize_B6[]					= "B6\0  ";
CUB	D2W_PaperSize_DL[]					= "DL\0  ";
CUB	D2W_PaperSize_CM10[]				= "CM10\0";
CUB	D2W_PaperSize_A6[]					= "A6\0  ";
CUB	D2W_PaperSize_Monarch[]				= "Mnc\0 ";
CUB	D2W_PaperSize_35[]					= "3x5\0 ";
CUB	D2W_PaperSize_User[]				= "User\0";
CUB	D2W_PaperSize_OHP[]					= "OHP\0 ";	/* このﾜｰﾃﾞｨﾝｸﾞは、SYS_DOC.Hの定義とは無関係です */
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)	/* By S.Fukui Jan.23,1998 */
CUB	D2W_PaperSize_Auto[]				= "Auto\0";	/* このﾜｰﾃﾞｨﾝｸﾞは、SYS_DOC.Hの定義とは無関係です */
#endif
#if (PRO_PITNEYBOWES == ENABLE)
CUB	D2W_PaperSize_Ledger[]				= "LDGR\0";	/* 原稿サイズ表示ＰＢ用 By S.Fukui Aug.25,1998 */
CUB	D2W_PaperSize_LtLg[]				= "LTLG\0";	/* 原稿サイズ表示ＰＢ用 (For Letter/Legal) By S.Fukui Aug.25,1998 */
#endif

/*----------------------------------*
 *	サービスファンクション
 *----------------------------------*/
/* マシンパラメータ */
CUB	D2W_SF_ParameterSet[]				= "Set Parameters      ";
CUB	D2W_SF_ParameterClear[]				= "Clear Parameters    ";

/* メモリスイッチ */
CUB	D2W_SF_MemorySwitchSet[]			= "Set Memory Switch   ";
CUB	D2W_SF_MemorySwitchClear[]			= "Clear Memory Switch ";

/* ユーザ設定クリア */
CUB	D2W_SF_BackUpFileClear[]			= "Clear User Settings ";

/* オールラムクリア */
CUB	D2W_SF_AllClear[]					= "All RAM Clear       ";

/* 機種固有スイッチ */
CUB	D2W_SF_UniqSwitchSet[]				= "Set Uniq Switch     ";
CUB	D2W_SF_UniqSwitchClear[]			= "Clear Uniq Switch   ";

/* 保守用スイッチ */
CUB	D2W_SF_MaintenanceSet[]				= "Set Maintenance     ";
CUB	D2W_SF_MaintenanceClear[]			= "Clear Maintenance   ";

/* テストファンクション -> このワーディングの並びはかえてはいけない */
#if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1997/10/02 Y.Matsukuma */
CUB D2W_SF_LifeMonitor[]				= "Life Monitor        ";
CUB D2W_SF_LifeMonitorClear[]			= "Clear Life Monitor  ";
CUB D2W_SF_TestPatternPrint[]			= "Printer Test        ";
CUB D2W_SF_StampTest[]					= "Stamp Test          ";
CUB D2W_SF_Shading[]					= "Set Background Level";
#elif (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ＨＩＮＯＫＩは原稿排出テストは有りません by O.Kimoto 1999/02/09 */
CUB	D2W_SF_LifeMonitor[]				= "Life Monitor        ";
CUB	D2W_SF_TestPatternPrint[]			= "Printer Test        ";
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/12/26 */
CUB	D2W_SF_PS1_PB4_Threshold[]			= "PS1,PB4 Setting Mode";/* Add by Y.Kano 2003/12/26 */
 #else	/* HINOKIは済みスタンプを表示 */
CUB	D2W_SF_StampTest[]					= "Stamp Test          ";
 #endif
CUB	D2W_SF_Shading[]					= "Set Background Level";
#else
CUB	D2W_SF_LifeMonitor[]				= "Life Monitor        ";
CUB	D2W_SF_TestPatternPrint[]			= "Printer Test        ";
CUB	D2W_SF_StampTest[]					= "Stamp Test          ";
CUB	D2W_SF_DocumentFeedOutTest[]		= "Feeder Test         ";
CUB	D2W_SF_Shading[]					= "Set Background Level";
#endif

/* ライフモニター */
CUB	D2W_SF_BoardNumber[]				= "Board Number?       ";
CUB	D2W_SF_LifeReadingPage[]			= "Pages Scanned       ";
CUB	D2W_SF_LifePrintingPage[]			= "Pages Printed       ";
CUB	D2W_SF_LifeTxPage[]					= "Pages Transmitted   ";
CUB	D2W_SF_LifeDrumReplaceCount[]		= "Drum Replaced Count ";
CUB	D2W_SF_LifeDrumLifeCount[]			= "Drum Life           ";
CUB	D2W_SF_LifeTonerReplaceCount[]		= "Toner Replaced Count";
CUB	D2W_SF_LifeTonerLifeCount[]			= "Toner Life          ";
CUB	D2W_SF_LifeFuserReplaceCount[]		= "Fuser Replaced Count";
CUB	D2W_SF_LifeFuserLifeCount[]			= "Fuser Life          ";
CUB	D2W_SF_LifeTransferReplaceCount[]	= "Transfer Rplcd Count";
CUB	D2W_SF_LifeTransferLifeCount[]		= "Transfer Life       ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/07 */
CUB	D2W_SF_CPU_Revision[]				= "CPU ﾊﾞｰｼﾞｮﾝ         ";
CUB	D2W_SF_ROM_Revision[]				= "ROM ﾊﾞｰｼﾞｮﾝ         ";
#endif

/* テストパターン */
CUB	D2W_SF_Pattern[]					= "Pattern           \0 ";

/* 工場ファンクション */
CUB	D2W_SF_FactoryFunction[]			= "Factory Function    ";

CUB	D2W_SF_LEDTest[]					= "LED Test            ";
CUB	D2W_SF_LCDTest[]					= "LCD Test            ";
CUB	D2W_SF_PanelTest[]					= "Key Panel Test      ";
CUB	D2W_SF_SRAMCheck[]					= "SRAM Check          ";
CUB	D2W_SF_DRAMCheck[]					= "DRAM Check          ";
CUB	D2W_SF_RTCTest[]					= "RTC Test            ";
CUB	D2W_SF_RS232CTest[]					= "RS232C Test         ";
CUB	D2W_SF_CassetteCheck[]				= "Cassette Test       ";

/* キー */
/*このワーディングの順番はキーコードの順番に一致させなくてはならない */
CUB	D2W_SF_Receive[]					= "Auto Rx             ";
CUB	D2W_SF_Hook[]						= "Monitor/Call        ";
CUB	D2W_SF_Hold[]						= "Hold                ";
CUB	D2W_SF_Mode[]						= "Mode                ";
CUB	D2W_SF_Contrast[]					= "Contrast            ";
CUB	D2W_SF_Program[]					= ">                   ";
CUB	D2W_SF_CursorLeft[]					= "<                   ";
CUB	D2W_SF_Set[]						= "Enter               ";
CUB	D2W_SF_DelayedCheck[]				= "Review              ";
CUB	D2W_SF_Clear[]						= "Cancel              ";
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1997/08/20 Y.Matsukuma */
CUB	D2W_SF_DialMark[]					= "Dialing Options     ";
#else
CUB	D2W_SF_Sort[]						= "Sort Copy           ";
#endif
CUB	D2W_SF_Broadcast[]					= "Broadcast           ";	/* 注）通信確認でも使用（このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです） */
CUB	D2W_SF_Special[]					= "Com.Option          ";
CUB	D2W_SF_Group[]						= "Group               ";
CUB	D2W_SF_Speed[]						= "Speed               ";
CUB	D2W_SF_MemoryTx[]					= "Memory Transmit     ";
CUB	D2W_SF_Stop[]						= "Stop                ";
CUB	D2W_SF_Start[]						= "Start               ";
CUB	D2W_SF_Copy[]						= "Copy                ";	/* 注）ｺﾋﾟｰ表示でも使用 */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1997/08/20 Y.Matsukuma */
CUB	D2W_SF_Redial[]						= "Redial              ";
 #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
CUB	D2W_SF_Reservation[]				= "ｶｲﾜ ﾖﾔｸ             ";
 #else
CUB	D2W_SF_Stamp[]						= "Stamp               ";
 #endif
CUB	D2W_SF_Mercury[]					= "Prefix              ";
CUB	D2W_SF_Flash[]						= "Flash               ";
#else
CUB	D2W_SF_PaperSelect[]				= "Paper Size?         ";
CUB	D2W_SF_Stamp[]						= "Stamp               ";
CUB	D2W_SF_Reduction[]					= "Reduct %            ";
CUB	D2W_SF_Magnification[]				= "Enlarge %           ";
#endif
CUB	D2W_SF_CopyFax[]					= "Copy/Fax            ";
CUB	D2W_SF_BookDocSize[]				= "Book Doc Size       ";
CUB	D2W_SF_CopyReset[]					= "Clear All           ";
CUB	D2W_SF_Tone[]						= "Tone                ";	/* 追加 97/11/29 T.Fukumoto */
#if defined(HINOKI3)	/* ONETOUCH_30_KEYがプレフィックスキーに変わったので by K.Watanabe 2004/10/26 */
CUB	D2W_SF_Prefix[]						= "Prefix              ";
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	D2W_SF_Receive_S[]					= "Auto Rx             ";
CUB	D2W_SF_Hook_S[]						= "Monitor/Call        ";
CUB	D2W_SF_Contrast_S[]					= "Contrast            ";
#endif

/* 回線テスト */
CUB	D2W_SF_LineTest[]					= "Line Test           ";	/* 未使用 */

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/25 */
/* 警察FAX Added DVT_ID15 by SMuratec K.W.Q 2005/11/05 */
CUB D2W_SF_KEIDEN_RelayTest[]			= "Keiden Relay Test   ";
CUB D2W_SF_KEIDEN_TonalTest[]			= "keiden Tonal Test   ";
CUB	D2W_SF_KEIDEN_DTMF_Test[]			= "Keiden DTMF Test    ";
CUB	D2W_SF_PhoneTest[]					= "Kanyu Relay Test    ";
CUB	D2W_SF_TonalTest[]					= "Kanyu Tonal Test    ";
CUB	D2W_SF_DTMF_Test[]					= "Kanyu DTMF Test     ";
#else
CUB	D2W_SF_PhoneTest[]					= "Relay Test          ";
CUB	D2W_SF_TonalTest[]					= "Tonal Test          ";
CUB	D2W_SF_DTMF_Test[]					= "DTMF Test           ";
#endif		/* End of (defined (KEISATSU)) */

/* リレー */
CUB	D2W_SF_RelayTest1[]					= " CML  H  L  S  DP   ";
CUB	D2W_SF_RelayTest2[]					= " C24                ";
#if (PRO_MODEM == R288F)	/* By H.Fujimura 1999/01/07 */
 #if defined (JPN)
  #if defined (KEISATSU)		/* 警察FAX DVT_ID15 Modify by SMuratec K.W.Q 2005/11/05 */
CUB	D2W_SF_R288F_RelayTest1[]			= " CML  HDST  L   S   ";
CUB	D2W_SF_R288F_Keiden_RelayTest1[]	= " CML  HDST  KL  S   ";
  #else
CUB	D2W_SF_R288F_RelayTest1[]			= " CML  H     L   S   ";
  #endif		/* End of (defined (KEISATSU)) */
CUB	D2W_SF_R288F_RelayTest2[]			= " C24  TONE  BZ  RI  ";
 #else	/* ＴＷＮ用 by H.Hirao 1999/02/02 */
CUB	D2W_SF_R288F_RelayTest1[]			= " CML  H     DP  S   ";
CUB	D2W_SF_R288F_RelayTest2[]			= " C24        BZ      ";
 #endif
#endif

/* トーナル */
CUB	D2W_SF_FSK[]						= "FSK";
CUB	D2W_SF_White[]						= "White\0    ";
CUB	D2W_SF_Black[]						= "Black\0    ";
CUB	D2W_SF_Pix[]						= "     BPS   W:B =    ";

/* ミラーキャリッジ輸送モードセット */
CUB	D2W_SF_MirrorCarrigeModeSet[]		= "Mirror Locked   :\0  ";

/* サービスレポート */
CUB	D2W_SF_ServicePrint[]				= "Service Report      ";

/* DTMF */
CUB	D2W_SF_DTMF[]						= "DTMF";
CUB	D2W_SF_DTMFRow[]					= "ROW";
CUB	D2W_SF_DTMFColum[]					= "COL";

/* カセットテスト */
CUB	D2W_SF_CassetteOpen[]				= "Cassette Open";
CUB	D2W_SF_NoPaper[]					= "No Paper";
CUB	D2W_SF_SideCoverOpen[]				= "Side Cover Open";
CUB	D2W_SF_NoUnit[]						= "No Unit";

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ライフモニタークリア */
CUB	D2W_SF_LifeMonitorClear[]			= "Clear Life Monitor  ";
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
/* ライフモニタクリアパスコード */
CUB	D2W_SF_ServiceCode[]				= "Set Service Code    ";
CUB	D2W_SF_EnterServiceCode[]			= "Enter Service Code  ";
#endif

/* プリンタメンテナンス */
CUB	D2W_SF_ReplaceCountSet[]			= "Set Replace Counter ";
CUB	D2W_SF_ServiceCall[]				= "Service Call        ";
CUB	D2W_SF_FuserReplace[]				= "Replace Fuser       ";
CUB	D2W_SF_TransferReplace[]			= "Replace Transfer    ";
CUB	D2W_SF_ServiceCallCount[]			= "Service Call     :  ";
CUB	D2W_SF_HeatTrouble[]				= "Heater Error        ";
CUB	D2W_SF_HeatDisconnection[]			= "ThermistorDisconnect";
CUB	D2W_SF_HeatShortCircuit[]			= "Thermistor Short    ";
CUB	D2W_SF_InsideFanTrouble[]			= "Inside Fan Error    ";
CUB	D2W_SF_RxMotorTrouble[]				= "Rx Motor Error      ";
CUB	D2W_SF_DrumTrouble[]				= "Drum Fuse Error     ";
CUB	D2W_SF_PsFanTrouble[]				= "PS Fan Error        ";
CUB	D2W_SF_HvFuseDisconnect[]			= "H-VltFuse Disconnect";

/* 消耗品発注機能 */
CUB	D2W_SF_ReceiverCustomerCode[]		= "DIST CODE           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* (JPN) */
CUB	D2W_SF_ReceiverCompany[]			= "DIST NAME           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	D2W_SF_SenderCustomerCode[]			= "CUST CODE           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	D2W_SF_SenderCompany[]				= "CUST NAME           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
CUB	D2W_SF_SenderSection[]				= "Address1            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* JPN以外は Address とする By S.Fukui Nov.15,1997 */
CUB	D2W_SF_SenderSection2[]				= "Address2            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* 60文字入力できるようにAddressを2段に分けます */
#else
CUB	D2W_SF_SenderSection[]				= "Section             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
#endif
CUB	D2W_SF_SenderTelNumber[]			= "Customer's Tel      ";
CUB	D2W_SF_SerialNumber[]				= "Serial No.          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	D2W_SF_Date[]						= "Installation Date   ";
CUB	D2W_SF_PrintOrderForm[]				= "Print Order Sheet   ";
#if defined(US1)
CUB	D2W_SF_ToCompanyFaxNumber[]			= "Dist. Fax No.       ";	/* orderbythonda1998/11/11 */
CUB	D2W_SF_ToCompanyTelNumber[]			= "Dist. Tel No.       ";	/* orderbythonda1998/11/11 */
#endif

/* メモリダンプ */
CUB	D2W_SF_MemoryDump[]					= "Memory Dump         ";
CUB	D2W_SF_MemoryDumpAddress[]			= "Address    :        ";
CUB	D2W_SF_MemoryDumpLength[]			= "Data Length:        ";

/* ＤＲＡＭクリア */
CUB	D2W_SF_ClearDRAM[]					= "DRAM Clear          ";

/* オプションデータ初期化 */
CUB	D2W_SF_OptionDataInitial[]			= "Option Data Initial ";

/* 消耗品発注データクリア */
#if (PRO_PRINT_TYPE == THERMAL)	/* By H.Fujimura 1999/01/07 */
CUB	D2W_SF_MntDataClear[]				= "ｷｶｲ ﾊﾞﾝｺﾞｳ ｸﾘｱ      ";
#else
CUB	D2W_SF_OrderDataClear[]				= "Reset Order Sheet   ";
#endif

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/20 */
/* T30モニター番号 */
CUB	D2W_SF_T30MonitorNumber[]			= "T30 No.:        \0   ";
#endif

CUB	D2W_SF_OK[]							= "OK                  ";
CUB	D2W_SF_NG[]							= "NG\0                 ";

/*----------------------------------*
 *	ＬＣＤ・リストでの頭文字表示
 *----------------------------------*/
#if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
CUB	D2W_HeadCharacter_Speed				= 'S';
CUB	D2W_HeadCharacter_Command			= 'C';
CUB	D2W_HeadCharacter_Batch				= 'B';
CUB	D2W_HeadCharacter_Polling			= 'P';
CUB	D2W_HeadCharacter_Tray				= 'T';
#endif

#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
/*----------------------------------*
 *	通信結果表示
 *----------------------------------*/
CUB	D2W_CommResultList[]				= "Communication Result";/*20*/
CUB	D2W_Tx[]							= "Tx\0                 ";/*2*/
CUB	D2W_Rx[]							= "Rx\0                 ";/*2*/
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC 設定表示 */
CUB D2W_RemoteTxSetting[]				= "Remote Rx";
CUB D2W_RemoteTxSettingOff[]			= "OFF";
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 音量調整処理の追加 by Y.Kano 2003/08/27 */
/*----------------------------------*
 *	音量調整表示
 *----------------------------------*/
/* 音量調整選択の表示（上段） */
CUB	D2W_BuzzerVolume[]					= "01.Key Touch Volume ";/*20*/
CUB	D2W_MonitorVolume[]					= "02.Monitor Volume   ";/*20*/
CUB	D2W_RingerControl[]					= "03.ﾁｬｸｼﾝ ﾍﾞﾙ        ";/*20*/
CUB	D2W_RingerControlOn[]				= "ﾁｬｸｼﾝ ﾍﾞﾙ  : ON     ";/*20*/
CUB	D2W_RingerControlOff[]				= "ﾁｬｸｼﾝ ﾍﾞﾙ  : OFF    ";/*20*/
/* 選択を促す表示（点滅する表示 ) */
CUB	D2W_BuzzerVolumeEnter[]				= "            \x7F/\x7E/ｾｯﾄ ";/*20*/

CUB	D2W_ShadingWord[]					= "Please Supply Paper ";/* Added by SMuratec K.W.Q 2003/08/11 */
CUB	D2W_ManualCutterMode[]				= "Excute Manual Cutter";/* Add by Y.Kano 2003/10/15 */
CUB	D2W_SF_PS2AdjustMode[]				= "PS2 Adjust Mode     ";/* Add by Y.Kano 2003/10/17 */
CUB	D2W_PS2VolumueFullLight_1[]			= "Move To PS2 Volumue ";/* Add by Y.Kano 2003/10/17 */
CUB	D2W_PS2VolumueFullLight_2[]			= "Lighting            ";/* Add by Y.Kano 2003/10/17 */
CUB	D2W_PS2VolumueTitle[]				= "     PS2 Volumue    ";/* Add by Y.Kano 2003/10/17 */
CUB	D2W_PS2_OK[]						= "     ** OK **       ";/* Add by Y.Kano 2003/10/18 */
CUB D2W_PS2_Complete[]					= " **   Complete   ** ";/* Add by Y.Kano 2003/10/18 */
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* チェッカー表示の追加 by SMuratec L.Z.W 2003/10/23 */
CUB D2W_Character[]						= "Character           ";
CUB D2W_SF_PS1_PB4_CheckMode[]			= "PS1,PB4 Check Mode  ";/* Add by Y.Kano 2003/12/18 */
CUB	D2W_Stop[]							= "              ｽﾄｯﾌﾟ ";/* Add by Y.Kano 2003/12/18 */
CUB	D2W_PleaseNonPaper[]				= "Please Remove Paper ";/* Add by Y.Kano 2003/12/18 */
CUB	D2W_SF_PS1_PB4_Error[]				= "PS1,PB4 Sensor Error";/* Add by Y.Kano 2003/12/26 */
CUB	D2W_SF_PS1_Error[]					= "PS1 Sensor Error    ";/* Add by Y.Kano 2003/12/26 */
CUB	D2W_SF_PB4_Error[]					= "PB4 Sensor Error    ";/* Add by Y.Kano 2003/12/26 */
#endif

#if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)	/* ＰＳ１、ＰＳ２、ＰＢ４閾値自動調整モード by Y.Kano 2004/10/06 */
CUB D2W_SF_PS1_PS2_PB4_AdjustMode[]		= "PS1,PS2,PB4 Adjust  ";
CUB D2W_PleaseNonPaper[]				= "Please Remove Paper ";
CUB	D2W_SF_PS1_PS2_PB4_Error[]			= "PS1,PS2,PB4 Error   ";
CUB	D2W_SF_PS1_PS2_Error[]				= "PS1,PS2 Error       ";
CUB	D2W_SF_PS1_PB4_Error[]				= "PS1,PB4 Error       ";
CUB	D2W_SF_PS1_Error[]					= "PS1 Error           ";
CUB	D2W_SF_PS2_PB4_Error[]				= "PS2,PB4 Error       ";
CUB	D2W_SF_PS2_Error[]					= "PS2 Error           ";
CUB	D2W_SF_PB4_Error[]					= "PB4 Error           ";
CUB	D2W_Stop[]							= "               Stop ";
CUB	D2W_SensorTest[]					= "Sensor Test         ";
#endif

#if defined(STOCKHM2) || (PRO_JOURNAL_VER_UP == ENABLE)	/* Added by SMuratec C.P 2004/06/07 *//* by K.Watanabe 2004/10/15 */
/*----------------------------------*
 *	ジャーナルプリント
 *----------------------------------*/
CUB D2W_JournalTx[]						= "[01] Tx Journal     ";
CUB D2W_JournalRx[]						= "[02] Rx Journal     ";
CUB D2W_JournalTxRx[]					= "[03] TxRx Journal   ";
#endif

#if defined(STOCKHM2)	/* Added by SMuratec C.P 2004/06/07 */
CUB	D2W_CommConfirm[]					= "Comm Confirm        ";
CUB D2W_FunctionEnter[]					= "               /set ";
CUB D2W_InkConfirm[]					= "Ink Ribbon Confirm  ";
#endif

/** トーン検出設定 */
#if defined(STOCKHM2) || defined(HINOKI3) /* 復活 by SMuratec 夏 2004/7/12*/ /* Add by Y.Kano 2004/11/25 */
CUB D2W_SetToneDetectMode[]				= "   Set Tone Detect  ";
CUB D2W_DialToneOn[]					= "Dial Tone:      \0   ";
CUB	D2W_Off[]							= "Off                 ";
CUB D2W_On[]							= "On                  ";
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec K.W.Q 2005/06/02 */
/** トーン検出設定 */
CUB D2W_KanyuDialToneOn[]				= "ｶﾆｭｳ ﾀﾞｲﾔﾙ ﾄｰﾝ :\0   ";
CUB D2W_DefaultLine[]					= "ﾕｳｾﾝ ｶｲｾﾝ     :\0    ";
CUB D2W_DefaultCOMMethod[]				= "ﾕｳｾﾝ ﾎｳｼｷ     :\0    ";
CUB D2W_KeidenScramleOn[]				= "ｹｲﾃﾞﾝ S ﾕｳｾﾝ  :\0    ";
CUB D2W_KanyuScramleOn[]				= "ｶﾆｭｳ  S ﾕｳｾﾝ  :\0    ";
CUB D2W_Keiden[]						= "ｹｲﾃﾞﾝ               ";
CUB D2W_Kanyu[]							= "ｶﾆｭｳ                ";
CUB D2W_Issei[]							= "ｲｯｾｲ                ";
CUB D2W_Kobetsu[]						= "ｺﾍﾞﾂ                ";
CUB D2W_Hoji[]							= "ﾎｼﾞ                 ";
CUB D2W_S_On[]							= "S:ON                ";
CUB D2W_S_Off[]							= "S:OFF               ";
CUB D2W_Senyo[]							= "ｾﾝﾖｳ                ";

/*	サービス設定 */
CUB D2W_SetS1Bypass[]					= "   S1 ﾊﾞｲﾊﾟｽ        ";
CUB D2W_ScrambleAvailable[]				= "   ｽｸﾗﾝﾌﾞﾙ          ";
CUB D2W_KeyLockOn[]						= "   ｷｰ ﾛｯｸ           ";
CUB D2W_SendLevel[]						= "   ｿｳｼｭﾂ ﾚﾍﾞﾙ       ";
CUB D2W_DTMFSendLevel[]					= "   DTMF ｿｳｼｭﾂ ﾚﾍﾞﾙ  ";
#if (1)
CUB D2W_IsseiRingTimeout[]				= "   ｲｯｾｲ ﾒｲﾄﾞｳ ｼﾞｶﾝ  ";
CUB D2W_RingTimeout[]					= "ﾋﾞｮｳ                ";
#else
CUB D2W_IsseiRingCount[]				= "   ｲｯｾｲ ﾒｲﾄﾞｳ ｶｲｽｳ  ";
#endif
CUB D2W_IsseiAbility[]					= "   ｲｯｾｲｼﾚｲ ﾉｳﾘｮｸ    ";
CUB D2W_IsseiTimeOut[]					= "   ｲｯｾｲ ﾀｲﾑｱｳﾄ      ";
CUB D2W_RemoteRxDialOne[]				= "   ﾘﾓｰﾄ ﾄｸﾊﾞﾝ ｹﾀｽｳ  ";
CUB D2W_KeidenRxPriority[]				= "   ｹｲﾃﾞﾝ ﾕｳｾﾝ ｼﾞｭｼﾝ ";
CUB D2W_FPGAVersion[]					= "   FPGA ﾊﾞｰｼﾞｮﾝ     ";
CUB D2W_KeidenDialTone[]				= "   ｹｲﾃﾞﾝ ﾀﾞｲﾔﾙ ﾄｰﾝ  ";

CUB D2W_S1Bypass[]						= "S1 ﾊﾞｲﾊﾟｽ           ";
CUB D2W_Scramble[]						= "ｽｸﾗﾝﾌﾞﾙ             ";
CUB D2W_KeidenKanyu[]					= "ｹｲﾃﾞﾝ/ｶﾆｭｳ          ";
CUB D2W_IsseiKobetsu[]					= "ｲｯｾｲ/ｺﾍﾞﾂ           ";
CUB D2W_S_OnOFF[]						= "S:ON/OFF            ";
CUB D2W_KyotsuSenyo[]					= "ｷｮｳﾂｳ/ｾﾝﾖｳ          ";
CUB D2W_AutoRx[]						= "ｼﾞﾄﾞｳ ｼﾞｭｼﾝ         ";
#if (0)		/* 警察FAX DVT_ID27 Delete by SMuratec K.W.Q 2005/10/28 */
CUB D2W_KeidenIssei[]					= "ｹｲﾃﾞﾝ ｲｯｾｲ          ";
CUB D2W_KeidenKobetsu[]					= "ｹｲﾃﾞﾝ ｺﾍﾞﾂ          ";
#endif
CUB D2W_RingCount[]						= "ﾒｲﾄﾞｳ ｶｲｽｳ          ";
CUB D2W_IsseiSpeed[]					= "ｼﾝｺﾞｳ ｿｸﾄﾞ          ";
CUB D2W_IsseiCode[]						= "ﾌｺﾞｳｶ ﾎｳｼｷ          ";
CUB D2W_IsseiMinScanLineTime[]			= "ﾃﾞﾝｿｳ ｼﾞｶﾝ          ";
CUB D2W_NumberOfRings_Keiden[]			= "ｹｲﾃﾞﾝ ｶｲｽｳ          ";
CUB D2W_NumberOfRings_Kanyu[]			= "ｶﾆｭｳ ｶｲｽｳ           ";

/*	電話呼出中	*/
CUB D2W_KeidenTelBell[]					= "ﾖﾋﾞﾀﾞｼﾁｭｳ(ｹｲﾃﾞﾝ)    ";
CUB D2W_KanyuTelBell[]					= "ﾖﾋﾞﾀﾞｼﾁｭｳ(ｶﾆｭｳ)     ";

CUB D2W_Telephone[]						= "ﾃﾞﾝﾜ                ";

/*	指令モード	*/
CUB D2W_IsseiShireiKido[]				= "ｼﾚｲﾂｳｼﾝ ｷﾄﾞｳ        ";

/* S1アラーム */
CUB D2W_S1Alarm[]						= "Sｱﾗｰﾑ               ";

/* パネルキーテスト用 */
CUB D2W_SF_KeidenKanyu[]				= "ｹｲﾃﾞﾝ/ｶﾆｭｳ          ";
CUB D2W_SF_IsseiKobetsu[]				= "ｲｯｾｲ/ｺﾍﾞﾂ           ";
CUB D2W_SF_S_OnOff[]					= "S:ON/OFF            ";
CUB D2W_SF_KyotsuSenyo[]				= "ｷｮｳﾂｳ/ｾﾝﾖｳ          ";

/* 工場ファンクション */
CUB D2W_SF_CopyOnetouchA_ToAll[]		= "ﾜﾝﾀｯﾁﾃﾞｰﾀ ﾌｨﾙ       ";
CUB D2W_SF_Transmit1100HzTone[]			= "1100Hz ｿｳｼｭﾂ  :     ";
CUB D2W_SF_TransmitV29Data[]			= "V29 ｿｳｼｭﾂ     :     ";

#endif		/* End of (defined (KEISATSU)) */

#if defined(STOCKHM2) /* Add by SMuratec C.P 2004/07/23 */
CUB D2W_VolumeControl[]					= "    Volume Control  ";
#endif

#if (PRO_RTC_RX5C338A == ENABLE)
CUB D2W_RTC_Init[]						= "RTCｲﾆｼｬﾗｲｽﾞ         ";
#endif

CUB	D2W_WordingTail[]					= "\0";	/* ﾜｰﾃﾞｨﾝｸﾞｻｲｽﾞ計算用(H8の様にﾜｰﾃﾞｨﾝｸﾞを縦に並べる場合必要) */

#if (PRO_CPU == SH7043)
	#pragma	section
#endif

#undef	CUB

#endif	/* (PRO_ANK_TO_KANJI == ENABLE) */
