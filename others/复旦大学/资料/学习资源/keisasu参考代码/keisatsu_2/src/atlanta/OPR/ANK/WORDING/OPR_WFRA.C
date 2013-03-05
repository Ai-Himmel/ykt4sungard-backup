/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_WFRA.C
*	Author		: 渡辺一章
*	Date		: 1996/10/25
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: フランス語版オペレーションワーディング
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"

#define	CUB		CONST UBYTE

/* #define		｢	0xA2	eの上に´(右上から)		*/
/* #define		･	0xA5	aの上に｀(左上から)		*/
/* #define		ｧ	0xA7	cの下にJ				*/
/* #define		ｨ	0xA8	eの上に＾				*/
/* #define		ｪ	0xAA	eの上に｀(左上から)		*/
/* #define		ｬ	0xAC	iの上に＾				*/
/* #define		ｳ	0xB3	Oの上に＾				*/
/* #define		ｶ	0xB6	uの上に＾				*/
/* #define		ﾏ	0xCF	ﾟ (特殊文字の丸)		*/

#if (PRO_CPU == SH7043)	/* ワーディング先頭位置認識用 */
 #if (WORDING_1 == FRENCH)
	CUB D2W_1stWordingTop[]				= "\0";
 #endif
 #if (WORDING_2 == FRENCH)
	CUB D2W_2ndWordingTop[]				= "\0";
 #endif
 #if (WORDING_3 == FRENCH)
	CUB D2W_3rdWordingTop[]				= "\0";
 #endif
#endif

CUB	FRA_WordingHead[]					= "\0";	/* ﾜｰﾃﾞｨﾝｸﾞｻｲｽﾞ計算用(H8の様にﾜｰﾃﾞｨﾝｸﾞを縦に並べる場合必要) */
CUB	FRA_Null[]							= "\0";

/* 待機モード */
CUB	FRA_TelReady[]						= "T｢l Prｨt            ";
CUB	FRA_FaxReady[]						= "Fax Prｨt            ";
CUB	FRA_FaxTelReady[]					= "Fax/T｢l Prｨt        ";
CUB	FRA_TelFaxReady[]					= "T｢l/Fax Prｨt        ";
CUB	FRA_AnsFaxReady[]					= "R｢pond./Fax Prｨt    ";
CUB	FRA_DialInReady[]					= "Dial In Ready       ";	/* JPN */
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1997/12/26 */
CUB	FRA_ScannerTransportReady[]			= "Miroir bloqu        ";  /* ﾐﾗｰｷｬﾘｯｼﾞ ﾕｿｳﾓｰﾄﾞ bythonda1998/02/24 */
#endif

/* コピーモードの表示 */
#if (PRO_COPY_FAX_MODE == ENABLE)
CUB	FRA_CopyReady[]						= "Copie Prｨte  Qt  :  ";
CUB	FRA_ManualCopyReady[]				= "Plat.Copies  Qt  :  ";
CUB	FRA_CopyImpossibleReady[]			= "             Qt  :  ";
CUB	FRA_InputCopyMagnifi[]				= "Prog.R｢duct.(50-200)";
CUB	FRA_CopyMagnifiError[]				= "Entrer 50-200%      ";
CUB	FRA_ConfirmCopyMagnifi[]			= "999% Certain?       ";	/* 倍率は必ず999を定義（国別の表示位置対応） */
#endif

/* コマンド登録中の表示（上段） */
CUB	FRA_EnterFaxNumber[]				= "Prog. num｢ro d'appel";
CUB	FRA_InputGroupNumber[]				= "Prog. num｢ro groupe ";
CUB	FRA_InputSpeedDialNumber[]			= "Prog. num. abr｢g｢   ";
CUB	FRA_PressStart[]					= "Presser D｢but       ";
CUB	FRA_PressStartAgain[]				= "R｢-appuyer sur START";
CUB	FRA_PressEnterKey[]					= "Appuyer sur Entrer  ";

/* コピー部数入力中の表示（上段） */
CUB	FRA_SetCopyUnits[]					= "Nb pages ･ copier   ";	/* POPLAR_B以外 */

/* 選択を促す表示（点滅する表示 ) */
CUB	FRA_ProgramEnter[]					= "      Program./Val. ";
CUB	FRA_ProgramClear[]					= "      Program./Eff. ";
#if (PRO_CIPHER == ENABLE)
CUB	FRA_EnterClesr[]					= "          Val./Eff. ";  /* ｾｯﾄ/ｸﾘｱ bythonda1998/07/15 */
#endif
CUB	FRA_EnterStop[]						= "          Val./Stop ";
CUB	FRA_CopyStop[]						= "        Copier/Stop ";	/* POPLAR_B以外 */
CUB	FRA_StartStop[]						= "         D｢but/Stop ";
CUB	FRA_SpecialCommunicationEnter[]		= "        Em.Sp./Val. ";
CUB	FRA_ReviewStop[]					= "         Liste/Stop ";
CUB	FRA_CheckProgramEnter[]				= "V｢rif. Program./Val.";
CUB	FRA_CheckProgramClear[]				= "V｢rif. Program./Eff.";
CUB	FRA_CheckStartStop[]				= "V｢rif.   D｢but/Stop ";
#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
CUB	FRA_CommunicationConfirmEnter[]		= "         Liste/Val. ";/*20*/
#endif

/*----------------------------------*
 *	応用機能
 *----------------------------------*/
/* 機能選択中 */
CUB	FRA_SetDelayedTransmission[]		= "  Diff｢r｢           ";
CUB	FRA_SetSecureTransmission[]			= "  Em. SecureMail    ";
CUB	FRA_SetRelayTransmission[]			= "  Diffusion relais  ";
#if (PRO_OKI == ENABLE)
CUB	FRA_SetPolling[]					= "  Relｪve            ";	/* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#else
CUB	FRA_SetPolling[]					= "  Polling           ";
#endif
CUB	FRA_SetBatchTransmission[]			= "  Envoi group｢      ";
#if (PRO_OKI == ENABLE)
CUB	FRA_SetContPolling[]				= "  Relｪve Continu    ";	/* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#else
CUB	FRA_SetContPolling[]				= "  Polling Continu   ";
#endif
CUB	FRA_SetFcodeTransmission[]			= "  Em.F-Code         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */
CUB	FRA_SetFcodePolling[]				= "  Rel.F-Code        ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */
CUB	FRA_SetCipherTransmission[]			= "  Em.Chiffr｢e       ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */

/* 各機能の詳細データ設定中（上段） */
CUB	FRA_DelayedTransmission[]			= "Diff｢r｢             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	FRA_SecureTransmission[]			= "Em. SecureMail      ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	FRA_RelayTransmission[]				= "Diffusion relais    ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
#if (PRO_OKI == ENABLE)
CUB	FRA_PollingCommunication[]			= "Relｪve              ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） *//* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#else
CUB	FRA_PollingCommunication[]			= "Polling             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） *//* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#endif
CUB	FRA_BatchTransmission[]				= "Envoi group｢        ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
#if (PRO_OKI == ENABLE)
CUB	FRA_ContinuousPolling[]				= "Relｪve Continu      ";	/* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#else
CUB	FRA_ContinuousPolling[]				= "Polling Continu     ";
#endif
CUB	FRA_InputSubAddressNumber[]			= "Prog.Sous-adresse   ";
CUB	FRA_InputPasswordNumber[]			= "Prog.Code d'accｪs   ";
CUB	FRA_SelectCipherExtensionKey[]		= "Ext.touche     :\0   ";

/* 各機能の詳細データ設定中（下段） */
CUB	FRA_EnterDelayedTxTime[]			= "Prog. heure:\0       ";
CUB	FRA_InputMailBoxNumber[]			= "Nﾏ SecureMail     \0 ";
CUB	FRA_RelayTxGroupNumber[]			= "Groupe Nﾏ     \0     ";
#if (PRO_OKI == ENABLE)
CUB	FRA_InputFileNumber[]				= "Nﾏ fichier. \0       ";
#else
CUB	FRA_InputFileNumber[]				= "Doc. Nﾏ.    \0       ";
#endif
CUB	FRA_BatchBoxIndexNumber[]			= "Boｬte:    Fich.:    ";
CUB	FRA_EnterContPollStartTime[]		= "D｢but       : \0     ";  /* Heure D｢but -> */
CUB	FRA_EnterContPollEndTime[]			= "Fin         : \0     ";  /* Heure Fin -> */

/*----------------------------------*
 *	濃度設定
 *----------------------------------*/
CUB	FRA_SetPaperContrast[]				= "Ajuster Contraste   ";
CUB	FRA_ContrastLightDark[]				= " Clair         Fonc ";

/*----------------------------------*
 *	機器エラー
 *----------------------------------*/
/* カバー */
CUB	FRA_PleaseCloseScannerCover[]		= "Fermer capot analys."; /*　未　*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	FRA_PleaseClose1stJamCover[]		= "Fermer1er capot cｳt ";
CUB	FRA_PleaseClose2ndJamCover[]		= "Fermer2nd capot cｳt ";
CUB	FRA_PleaseClose3rdJamCover[]		= "Fermer3me capot cｳt ";
CUB	FRA_PleaseOpen1stJamCover[]			= "Ouvrir1er capot cｳt ";
CUB	FRA_PleaseOpen2ndJamCover[]			= "Ouvrir2nd capot cｳt ";
CUB	FRA_PleaseOpen3rdJamCover[]			= "Ouvrir3me capot cｳt ";
CUB	FRA_PleaseOpenTopCover[]			= "Ouvrir Capot sup｢r. ";
#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1998/01/28 */
CUB	FRA_PleaseOpenPrinterCover[]		= "ﾌﾟﾘﾝﾀｶﾊﾞｰ ｦ ｱｹﾃ     ";
#endif
CUB	FRA_PleaseOpenCloseScanCover[]		= "Ouv&Ferm Capot Anal.";  /* ｹﾞﾝｺｳｶﾊﾞｰ ｦ ｶｲﾍｲｼﾃ bythonda1998/02/24 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
CUB	FRA_PleaseClosePrinterCover[]		= "ﾌﾟﾘﾝﾀｶﾊﾞｰｦ ﾄｼﾞﾃｸﾀﾞｻｲ";
#endif

/* カセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	FRA_PleaseCloseLowerCassette[]		= "Fermer la cassette  ";
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	FRA_PleaseClose1stCassette[]		= "Fermer 1ｪre cassette";
CUB	FRA_PleaseClose2ndCassette[]		= "Fermer 2nde cassette";
CUB	FRA_PleaseClose3rdCassette[]		= "Fermer 3ｪme cassette";
#endif

/* 記録紙 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	FRA_ReplaceRxPaper[]				= "Ajouter du pap.SVP  ";
CUB	FRA_NoSamePaper[]					= "Ajouter du pap.SVP  ";	/* 日本以外は、???_ReplaceRxPaperと同じです by K.Watanabe 1998/02/23 */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	FRA_ReplaceRxPaper[]				= "Ajouter papier r｢c. ";
CUB	FRA_ReplaceUpperRxPaper[]			= "V｢rifier tiroir pap.";
CUB	FRA_ReplaceLowerRxPaper[]			= "V｢rifier cassette   ";
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
CUB	FRA_Cassette1[]						= "1ｪre cassette       ";
CUB	FRA_Cassette2[]						= "2nde cassette       ";
CUB	FRA_Cassette3[]						= "3ｪme cassette       ";
CUB	FRA_ManualCassette[]				= "Plat:\0  ";
#endif
CUB	FRA_RemoveManualPaper[]				= "Oter plateau papier ";   /* ﾃｻﾞｼﾖｳｼ ｦ ﾄﾘﾉｿﾞｲﾃ bythonda1998/02/24 */
CUB	FRA_CheckPaperSize[]				= "V｢rif.format pap.Rx ";
CUB	FRA_PleaseOpenCloseTopCover[]		= "Ouv/Ferm.Capot Sup. ";
#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1998/01/28 */
CUB	FRA_PleaseOpenClosePrinterCover[]	= "ﾌﾟﾘﾝﾀｶﾊﾞｰｦ ｶｲﾍｲｸﾀﾞｻｲ";
#endif

/* プリンター */
CUB	FRA_PleaseRemovePaper[]				= "Retirer le Papier   ";
CUB	FRA_PleaseSupplyToner[]				= "Ajouter du Toner    ";
CUB	FRA_PleaseReplaceToner[]			= "Remplacer le Toner  ";
CUB	FRA_PleaseCallService[]				= "Appeler la Mainten. ";
CUB	FRA_PaperSizeError[]				= "V｢rifier taille pap.";	/* ANZUのみ */

CUB	FRA_CheckDrumLife[]					= "Pr｢voir Tambour     ";
CUB	FRA_ReplaceDrum[]					= "Rempl. Tambour      ";
CUB	FRA_CheckDrum[]						= "Abs. Tambour        ";
CUB	FRA_CheckTonerLevel[]				= "V｢rifier Niv. Toner ";
CUB	FRA_NoToner[]						= "Abs.cartouche toner ";

/* スキャナ */
CUB	FRA_CallForService[]				= "Appel maintenance   ";
CUB	FRA_CheckDocument[]					= "Confirm Nbre de Doc.";
CUB	FRA_MirrorCarrigeError[]			= "Err.Miroir Analyse  ";

/* ジャムリカバー */
CUB	FRA_DocumentJam[]					= "Bourrage Original   ";
CUB	FRA_InterruptDocScan[]				= "Arrｨt Analyse       ";
CUB	FRA_NextScanEnterClear[]			= "M｢mCont.Entrer/Annl.";
CUB	FRA_ResetPageNumber[]				= "p   Replacer origin.";
CUB	FRA_ResetDocumentSet[]				= "Replacer Original   ";
CUB	FRA_PleasePressStartKey[]			= "Appuyer sur D｢but   ";
CUB	FRA_PleasePressEnterKey[]			= "Appuyer sur Entrer  ";
CUB	FRA_PleasePressCopyKey[]			= "Appuyer sur Copie   ";	/* POPLAR_B以外 */

/* 通信 */
CUB	FRA_CommunicationError[]			= "Erreur de communic  ";
CUB	FRA_NoStoredDialInNumber[]			= "No Entered Dial In  ";	/* JPN */

/* ハングアップ */
CUB	FRA_HungUpPhone[]					= "Raccrocher t｢l｢phone";

/* 完了表示 */
CUB	FRA_TransmitComplete[]				= "   ** Termin｢ **    ";
CUB	FRA_ReceiveComplete[]				= "   ** Termin｢ **    ";
CUB	FRA_PrintComplete[]					= "   ** Termin｢ **    ";
CUB	FRA_StoreComplete[]					= "   ** Termin｢ **    ";
CUB	FRA_SetComplete[]					= "   ** Termin｢ **    ";
CUB	FRA_ClearComplete[]					= "   ** Termin｢ **    ";

/* リモート診断中の表示 1996/01/25 Eguchi */
CUB	FRA_RemoteDiagMode[]				= "Mode de service     ";

/* 操作エラー */
/* 絶対に途中に追加してはいかん */
CUB	FRA_InvalidNumber[]					= "Num｢ro incorrect    ";	/* INVALID_NUMBER_ERROR				*/
CUB	FRA_TooManyDigitsin[]				= "Trop de chiffres    ";	/* TOO_MANY_DIGITS_ERROR			*/
CUB	FRA_PleaseInput1_99[]				= "Entrer (1-99)       ";	/* INVALID_COPY_NUMBER_ERROR		*//* POPLAR_B以外 */
/* CUB	FRA_NoNumberStored[]				= "Pas de num progr    ";*/	/* 暫定 bythonda1998/02/13 			*/
CUB	FRA_NoNumberStored[]				= "Pas de num. M｢m.    ";	/* NO_STORED_NUMBER_ERROR			*//* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	FRA_PleaseInput0_32[]				= "Prog. Nﾏ (0-32)     ";	/* INVALID_GROUP_NUMBER_ERROR		*/
CUB	FRA_TooManyLocations[]				= "Trop de destinations";	/* TOO_MANY_LOCATION_ERROR			*/
CUB	FRA_InsertDocument[]				= "Introd. l'original  ";	/* INSERT_DOCUMENT_ERROR			*/
CUB	FRA_FeederInUse[]					= "Chargeur utilis｢    ";	/* FEEDER_IN_USE_ERROR				*/
CUB	FRA_ScannerInUse[]					= "Analyseur utilis｢   ";	/* SCANNER_USE_ERROR				*/
#if (PRO_OKI == ENABLE)
CUB	FRA_PollingInUse[]					= "Relｪve utilis｢      ";	/* ALREADY_POLLING_STORED_ERROR		*//* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#else
CUB	FRA_PollingInUse[]					= "Polling utilis｢     ";	/* ALREADY_POLLING_STORED_ERROR		*/
#endif
CUB	FRA_NoDocumentStored[]				= "Pas de doc. en m｢m. ";	/* NO_STORED_DOCUMENT_ERROR			*/
CUB	FRA_CommandFull[]					= "Commande indisponib.";	/* COMMAND_FULL_ERROR				*/
CUB	FRA_NoCommand[]						= "Pas de commande     ";	/* NO_COMMAND_ERROR					*/
CUB	FRA_NoCommandDocument[]				= "Pas de comm. en m｢m.";	/* NO_COMMAND_DOCUMENT_ERROR		*/
CUB	FRA_NoCommandResult[]				= "Absence Rapport     ";	/* NO_COMMAND_RESULT_ERROR			*/
CUB	FRA_SecureDocExist[]				= "Document en m｢moire ";	/* SECURE_DOC_EXIST_ERROR			*//* 未 */
CUB	FRA_PrinterInUse[]					= "Imprimante utilis｢e ";	/* PRINTER_IN_USE_ERROR				*/
CUB	FRA_InvalidIDCode[]					= "Code I.D incorrect  ";	/* INVALID_ID_CODE_ERROR			*/
CUB	FRA_InvalidProtectPasscode[]		= "Code accｴs incorrect";	/* INVALID_PROTECT_PASSCODE_ERROR	*//* 未 */
CUB	FRA_NoProtectPasscode[]				= "Pas de code d'accｴs ";	/* NO_PROTECT_PASSCODE_ERROR		*//* 未 */
CUB	FRA_InputRangeOver[]				= "Num｢ro incorrect    ";	/* INPUT_RANGE_OVER_ERROR			*/
CUB	FRA_BatchDocFull[]					= "                    ";	/* BATCH_DOCUMENT_FULL_ERROR		*/
CUB	FRA_LineBusy[]						= "Emission du chargeur";	/* LINE_BUSY_ERROR					*/
CUB	FRA_ProtectedDocStored[]			= "Doc. Prot｢g｢ en m｢m.";	/* PROTECT_DOCUMENT_STORED_ERROR	*//* 未 */
CUB	FRA_NoProtectDocStored[]			= "Pas de doc. en m｢m  ";	/* NO_PROTECT_DOCUMENT_ERROR		*/
CUB	FRA_NoPinNumber[]					= "Pas de code PIN     ";	/* NO_PIN_NUMBER_ERROR				*//* 未 */
CUB	FRA_NoDepartmentCode[]				= "Code d｢partem. Abs. ";	/* NO_DEPARTMENTCODE_ERROR			*//* 未 */
CUB	FRA_BatchDocStored[]				= "Document en m｢moire ";	/* BATCH_DOCUMENT_STORED_ERROR		*/
CUB	FRA_ResetDocument[]					= "Replacer l'original ";	/* RESET_DOCUMENT_ERROR				*/
CUB	FRA_PleaseCloseBookCover[]			= "Fermer capot livre  ";	/* BOOK_COVER_OPEN_ERROR			*//* POPLAR_Bのみ */
CUB	FRA_PleaseWaitAMinute[]				= "Patientez           ";	/* PRINTER_CLEANING_ERROR			*/
CUB	FRA_NotStoredDocument[]				= "Original Complet    ";	/* NOT_STORED_DOCUMENT_ERROR		*//* (PRO_F_CODE == ENABLE) */
CUB	FRA_BoxInUse[]						= "Boｬte utilis｢e      ";	/* BOX_IN_USE_ERROR					*//* (PRO_F_CODE == ENABLE) */
CUB	FRA_TooManyDirectDial[]				= "Trop de caractｪres  ";	/* TOO_MANY_DIRECT_DIAL_ERROR		*//* <- Trop de destinations */
CUB	FRA_SettingSecureBox[]				= "Dans Boｬte ･ lettre ";	/* SETTING_SECURE_BOX_ERROR			*//* (PRO_F_CODE == ENABLE) */
CUB	FRA_BookSizeNoSet[]					= "Prog.format Analyse ";	/* BOOK_SIZE_NO_SET_ERROR			*//* POPLAR_Bのみ */
CUB	FRA_NotCompleteStoredDoc[]			= "M｢m.partielle       ";	/* NOT_COMPLETE_STORED_ERROR		*//* POPLAR_Bのみ */
CUB	FRA_NotCompleteCopy[]				= "Copie partielle     ";	/* NOT_COMPLETE_COPY_ERROR			*//* POPLAR_Bのみ */
CUB	FRA_ScanPreparing[]					= "R｢glage Analyseur   ";	/* SCAN_PREPARING_ERROR				*//* POPLAR_Bのみ */
CUB	FRA_CopyProtect[]					= "Mode Copie stopp    ";	/* COPY_PROTECT_ERROR				*/
CUB	FRA_NotScanDocSize[]				= "Format refus        ";	/* NOT_SCAN_DOC_SIZE_ERROR			*//* (PRO_CIPHER == ENABLE) */
CUB	FRA_ShortFigure[]					= "4\x22Letter\x22 ou plus   ";	/* SHORT_FIGURE_ERROR				*//* (PRO_CIPHER == ENABLE) */
CUB	FRA_AlreadyStored[]					= "D｢j･ m｢moris        ";	/* ALREADY_NUMBER_STORED_ERROR		*//* (FRA) */
CUB	FRA_NotEntry[]						= "Pas de cl｢ m｢moris｢e";   /* NOT_ENTRY_ERROR					*//* (PRO_CIPHER == ENABLE) */
CUB	FRA_NoScanCipherMode[]				= "Pas de r｢glage SFin ";   /* NO_SCAN_CIPHER_MODE_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	FRA_Ciphering[]						= "Chiffrage utilis    ";   /* CIPHERING_ERROR					*//* (PRO_CIPHER == ENABLE) */
CUB	FRA_Deciphering[]					= "D｢chiffrage utilis  ";   /* DECIPHERING_ERROR				*//* (PRO_CIPHER == ENABLE) */
CUB	FRA_UseDefaultCipherKey[]			= "Utiliser par d｢faut ";   /* USE_DEFAULT_CIPHER_KEY_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	FRA_UseProgramOneTouch[]			= "Utii.en Une-Touche P";   /* USE_PROGRAM_ONETOUCH_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	FRA_PleaseCloseTopCover[]			= "Fermer capot sup｢r. ";	/* TOP_COVER_OPEN_ERROR				*/
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1999/01/07 */
//#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 In English by K.Okada */
#endif
CUB	FRA_DialNumberStoredError[]			= "FAX Number Stored   ";	/* DIAL_NUMBER_STORED_ERROR			*/
CUB	FRA_ProgramStoredError[]			= "Program Stored      ";	/* PROGRAM_STORED_ERROR				*/
CUB	FRA_MailAddressStoredError[]		= "Mail Address Stored ";	/* MAIL_ADDRESS_STORED_ERROR		*/
CUB	FRA_MailGroupStoredError[]			= "Mail Group Stored   ";	/* MAIL_GROUP_STORED_ERROR			*/
CUB	FRA_UserDataFullError[]				= "All User Data Stored";	/* USER_DATA_FULL_ENTRY_ERROR		*/
CUB	FRA_NoRS232C_Error[]				= "No RS-232C          ";	/* NO_RS232C_PCB_ERROR				*/
CUB	FRA_TooManyDirectAdrError[]			= "Too Many Address    ";	/* TOO_MANY_DIRECT_ADDRESS_ERROR	*/
CUB	FRA_NoUserDataError[]				= "No User Data        ";	/* NO_USER_DATA_ERROR				*/
CUB	FRA_InvalidAddressError[]			= "Invalid Address     ";	/* INVALID_ADDRESS_ERROR			*/
CUB	FRA_NoTCPIP_BoardError[]			= "No Optional Board   ";	/* NO_TCPIP_BOARD_ERROR				*/
CUB	FRA_MemoryFullError[]				= "Memory Full         ";	/* MEMORY_FULL_ERROR				*/
CUB	FRA_AlreadyUsedError[]				= "One-Touch In Use    ";	/* ALREADY_USED_ERROR				*/
CUB	FRA_NoEntryData[]					= "No Entry Data       ";	/* NO_ENTRY_DATA					*/
CUB	FRA_NoStoredAddress[]				= "No Address Stored   ";	/* NO_STORED_ADDRESS_ERROR			*/
CUB	FRA_InvalidPassword[]				= "Invalid Password    ";	/* INVALID_PASSWORD_ERROR			*/
CUB	FRA_ExecuteCommand[]				= "Executing Command   ";	/* EXECUTE_COMMAND_ERROR			*/
CUB	FRA_NoDeviceError[]					= "No Device           ";	/* NO_DEVICE_ERROR					*/
#if (0)
//CUB FRA_NoAccessPointTelNumber[]		= "No AP Tel Number    ";	/* NO_ACCESS_POINT_DATA_ERROR		*/
#endif
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1999/01/07 */
//#endif
#endif
CUB	FRA_SettingRelayBox[]				= "Relay Box           "; /* 要翻訳 by sasaki 00/01/06 */	/* SETTING_RELAY_BOX_ERROR			*//* By H.Fujimura 1999/01/07 */
CUB	FRA_TooManyRelayDirect[]			= "1 Locations or Less "; /* 要翻訳 by sasaki 00/01/06 */	/* TOO_MANY_RELAY_DIRECT_ERROR		*//* By H.Fujimura 1999/01/07 */

/*----------------------------------*
 *	通信中
 *----------------------------------*/
CUB	FRA_Transmit[]						= "Emission            ";
CUB	FRA_Receive[]						= "R｢ception ";
CUB	FRA_Called[]						= "   **  Appel｢  **   ";
CUB	FRA_CallReservation[]				= "** Appel Demamd｢ ** ";

/*----------------------------------*
 *	原稿サイズ・線密度
 *----------------------------------*/
CUB	FRA_DocNormal[]						= "Normal    \0         ";
CUB	FRA_DocFine[]						= "Fin       \0         ";
CUB	FRA_DocSFine[]						= "S Fine    \0         ";
#if (PRO_PITNEYBOWES == ENABLE) /* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
CUB	FRA_DocGray[]						= "Photo     \0         ";
CUB	FRA_DocHGray[]						= "H Photo   \0         ";
#else
CUB	FRA_DocGray[]						= "Gris      \0         ";
#endif
CUB	FRA_DocHFine[]						= "H-Fin     \0         "; /*評価用に追加1996/06/19Eguchi*/
CUB	FRA_DocEFine[]						= "E-Fin     \0         "; /*評価用に追加1996/06/19Eguchi*/

/*----------------------------------*
 *	次原稿・メモリ残量
 *----------------------------------*/
CUB	FRA_NextDocument[]					= "DocSuiv";
CUB	FRA_MemoryAreaShort[]				= "             M｢m   %";	/* 要申請確認 */
CUB	FRA_MemoryAreaLong[]				= "         M｢moire   %";	/* 要申請確認 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/07 */
CUB	FRA_MemoryAreaLong2[]				= "   ***** M｢moire   %";	/* 要申請確認 */
CUB	FRA_MemoryAreaShort2[]				= "   0x7E0x7E0x7E0x7E0x7E0x7E0x7E0x7E0x7E ﾒﾓﾘ   %";	/* ＬＣＤ表示変更(0x7E = ->) By O.Kimoto 1999/02/25 */
#endif
#if (PRO_NOT_AUTO_RX_DISP == ENABLE)	/* by K.Watanabe 1998/06/08 */
CUB	FRA_MemoryFull[]					= "Not Receiving       ";
CUB	FRA_NotAutoReceive[]				= "as Memory Full      ";
#endif

/*----------------------------------*
 *	月
 *----------------------------------*/
CUB	FRA_January[]						= "Jan";
CUB	FRA_February[]						= "F｢v";
CUB	FRA_March[]							= "Mar";
CUB	FRA_April[]							= "Avr";
CUB	FRA_May[]							= "Mai";
CUB	FRA_June[]							= "Jui";
CUB	FRA_July[]							= "Jul";
CUB	FRA_August[]						= "Aoｶ";
CUB	FRA_September[]						= "Sep";
CUB	FRA_October[]						= "Oct";
CUB	FRA_November[]						= "Nov";
CUB	FRA_December[]						= "D｢c";

/*----------------------------------*
 *	予約表示
 *----------------------------------*/
CUB	FRA_Reserving[]						= "   ** R｢serv｢e **   ";
CUB	FRA_AutoRedial[]					= " ** Rappel Auto. ** ";

/*----------------------------------*
 *	原稿セット時
 *----------------------------------*/
CUB	FRA_TransmitOrCopyReady[]			= "Em. Prｨt            ";
CUB	FRA_TransmitReady[]					= "Em. Prｨt            ";	/* 日本以外は、???_TransmitOrCopyReadyと同じです */

#if (PRO_PC_PRINT == ENABLE)
/*----------------------------------*
 *	ＰＣプリント
 *----------------------------------*/
CUB	FRA_PC_Print[]						= "PC                  ";
CUB	FRA_PC_Receiving[]					= "  ** R｢ception **   ";
CUB	FRA_PC_MemoryOverFlow[]				= "PC D｢passement m｢mo.";   /* PC ﾒﾓﾘ ｵｰﾊﾞｰ ﾃﾞｽ bythonda1998/02/24 */
#endif

/*----------------------------------*
 *	プリント中
 *----------------------------------*/
CUB	FRA_Printing[]						= "  ** Impression **  ";

/*----------------------------------*
 *	ウォームアップ
 *----------------------------------*/
CUB	FRA_Wait[]							= "  ** Patientez **   ";

/*----------------------------------*
 *	イメージプリント
 *----------------------------------*/
#if (PRO_OKI == ENABLE)
CUB	FRA_PollingDocument[]				= "Doc. relｪve         ";	/* polling -> relｪve by K.Watanabe 1999/02/04 */
#else
CUB	FRA_PollingDocument[]				= "Doc. Polling        ";
#endif
CUB	FRA_SecureMailDocument[]			= "Imp. SecureMail     ";
CUB	FRA_MemoryRxDocument[]				= "                    ";
CUB	FRA_CommandDocument[]				= "Imp. doc. en m｢moire";
CUB	FRA_BatchTxDocument[]				= "Imp. Docum. batch   ";

/*----------------------------------*
 *	リストプリント
 *----------------------------------*/
CUB	FRA_PrintJournal[]					= "Imp. Journal        ";
CUB	FRA_TCR[]							= "TCR                 ";
CUB	FRA_PrintSpeedDial[]				= "Imp. num. abr｢g｢s   ";
CUB	FRA_PrintOneTouch[]					= "Imp. Une-Touche     ";
CUB	FRA_PrintProgramOneTouch[]			= "Imp. Une-T. prog.   ";
CUB	FRA_GroupList[]						= "Liste groupes       ";
CUB	FRA_SF_ProgramListPrint[]			= "Imp. Liste Programm.";
CUB	FRA_SetPrintSettings[]				= "Imp. paramｪtres     ";
CUB	FRA_PrintCommands[]					= "Imp. commandes      ";
CUB	FRA_PrintSecureMailList[]			= "Imp. liste S.Mail   ";
CUB	FRA_MessageList[]					= "Liste Message       ";
CUB	FRA_PrintSecureMail[]				= "Imp. SecureMail     ";
CUB	FRA_SF_T30MonitorPrint[]			= "Imp. Moniteur T30   ";
CUB	FRA_SF_FactoryFunctionList[]		= "Fonctions Usine     ";
CUB	FRA_SF_MemorySwitchMode[]			= "Interr. M｢moire     ";
CUB	FRA_CheckMessage[]					= "Message d'erreur    ";
CUB	FRA_SF_OnLineMonitor[]				= "Ecoute Lighe        ";
CUB	FRA_SF_OrderForm[]					= "Bon de Commande     ";

/*----------------------------------*
 *	パスコード
 *----------------------------------*/
CUB	FRA_InputPasscode[]					= "Code d'accｪs   :\0   ";
CUB	FRA_EnterProtectPasscode[]			= "Prog Code accｪs:\0   ";
CUB	FRA_OldProtectPasscode[]			= "Ancien code    :\0   ";
CUB	FRA_NewProtectPasscode[]			= "Nouveau code   :\0   ";
CUB	FRA_EnterIDCode[]					= "Prog. code I.D.:\0   ";
#if (PRO_F_CODE == ENABLE)
CUB	FRA_EnterFcodePasscode[]			= "Code F-CODE    :\0   ";
#endif
#if (PRO_CIPHER == ENABLE)
CUB	FRA_CipherPassCode[]				= "Code d'accｪs   :\0   ";
CUB	FRA_OldCipherPassCode[]				= "Ancien code    :\0   ";
CUB	FRA_NewCipherPassCode[]				= "Nouveau code   :\0   ";
#endif

/*----------------------------------*
 *	入力モード
 *----------------------------------*/
#if defined(JPN)
CUB	FRA_Kana[]							= ":ｶﾀｶﾅ    ";
 #if (PRO_JIS_CODE == ENABLE)
CUB	FRA_KanjiCode[]						= ":ｶﾝｼﾞｺｰﾄﾞ";
 #endif
#endif
CUB	FRA_Upper[]							= ":Majusc. ";
CUB	FRA_Lower[]							= ":Minusc. ";
CUB	FRA_Symbol[]						= ":Symbole ";	/* ANZUのみ */
CUB	FRA_Code[]							= ":Code    ";
CUB	FRA_ModeNone[]						= ":        ";

/*----------------------------------*
 *	電話帳
 *----------------------------------*/
CUB	FRA_TelephoneBookMode[]				= "Annuaire T｢l｢ph  [ ]";

/*----------------------------------*
 *	電話
 *----------------------------------*/
CUB	FRA_OnHold[]						= "  ** En attente **  ";	/* POPLAR_B以外 */
CUB	FRA_TelephoneMode[]					= "** Mode t｢l｢phone **";
CUB	FRA_ChangeVolume[]					= "  Volume:           ";

/*----------------------------------*
 *	メモリーオーバーオペレーション
 *----------------------------------*/
CUB	FRA_MemoryOverFlow[]				= "D｢passement m｢moire ";
CUB	FRA_MemoryOverStartClear[]			= "Emettre ou Effacer  ";
CUB	FRA_MemoryOverEnterClear[]			= "Entrer ou Annuler   ";
CUB	FRA_MemoryOverCopyClear[]			= "Copier ou Effacer   ";	/* POPLAR_B以外 */

/*----------------------------------*
 *	ファンクション関係
 *----------------------------------*/
/* 機能選択状態 */
CUB	FRA_OneTouchDialMode[]				= "  Num. Une-Touche   ";
CUB	FRA_SpeedDialMode[]					= "  Num. abr｢g｢e      ";
CUB	FRA_ProgramOneTouchMode[]			= "  Prog. Une-Touche  ";
#if (PRO_OKI == ENABLE)
CUB	FRA_PollingMode[]					= "  Relｪve            ";	/* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#else
CUB	FRA_PollingMode[]					= "  Polling           ";	/* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#endif
CUB	FRA_SecureMailMode[]				= "  SecureMail        ";
CUB	FRA_DelayedCommandsMode[]			= "  Command. diff｢r｢es";
CUB	FRA_SetReportMode[]					= "  Rapport           ";
CUB	FRA_PrintGroupMode[]				= "  Imp. liste groupes";
CUB	FRA_UserInstallMode[]				= "  Mise en Service   ";
CUB	FRA_UserSettingsMode[]				= "  Paramｪt. utilisat.";
CUB	FRA_MessageMode[]					= "  Message           ";
CUB	FRA_SetNumberOfPagesMode[]			= "  Prog. page comp.  ";
CUB	FRA_SetDepartmentMode[]				= "  Code d｢partement  ";
CUB	FRA_SetBatchTxMode[]				= "  Envoi group｢      ";
CUB	FRA_SecurityReceiveMode[]			= "  Em. S｢curit｢      ";
CUB	FRA_FcodeBoxMode[]					= "  Boｬte F-CODE      ";	/* (PRO_F_CODE == ENABLE) */
CUB	FRA_ResetPrinterBoardMode[]			= "  Init.Opt.Imprim.  ";	/* (PRO_PC_PRINT == ENABLE) */
CUB	FRA_SetClass1Mode[]					= "  PC-FAX            ";	/* (PRO_CLASS1 == ENABLE) */
CUB	FRA_SetCipherMode[]					= "  Prog.Chiffrage    ";	/* (PRO_CIPHER == ENABLE) */
CUB	FRA_PrintDecipherDocMode[]			= "  Imp.D｢chiffr.     ";	/* (PRO_CIPHER == ENABLE) */

CUB	FRA_EnterOneTouchMode[]				= "   Prog. Une-Touche ";
CUB	FRA_EraseOneTouchMode[]				= "   Eff. Une-Touche  ";
CUB	FRA_PrintOneTouchMode[]				= "   Imp. Une-Touche  ";

CUB	FRA_EnterSpeedDialMode[]			= "   Prog num. abr｢g｢s";
CUB	FRA_EraseSpeedDialMode[]			= "   Eff. num. abr｢g｢s";
CUB	FRA_PrintSpeedDialMode[]			= "   Imp. num. abr｢g｢s";

CUB	FRA_EnterProgramOneTouchMode[]		= "   Prog Une-T. prog.";
CUB	FRA_EraseProgramOneTouchMode[]		= "   Eff. Une-T. prog.";
CUB	FRA_PrintProgramOneTouchMode[]		= "   Imp. Une-T. prog.";

#if (PRO_OKI == ENABLE)
CUB	FRA_StorePollingDocumentMode[]		= "   Ent. doc. relｪve ";	/* polling -> relｪve by K.Watanabe 1999/02/04 */
CUB	FRA_ErasePollingDocumentMode[]		= "   Eff. doc. relｪve ";	/* polling -> relｪve by K.Watanabe 1999/02/04 */
CUB	FRA_PrintPollingDocumentMode[]		= "   Imp. doc. relｪve ";	/* polling -> relｪve by K.Watanabe 1999/02/04 */
#else
CUB	FRA_StorePollingDocumentMode[]		= "   Ent. doc. Polling";
CUB	FRA_ErasePollingDocumentMode[]		= "   Eff. doc. Polling";
CUB	FRA_PrintPollingDocumentMode[]		= "   Imp. doc. Polling";
#endif

CUB	FRA_SetSecureMailBoxMode[]			= "   Boｬte SecureMail ";
CUB	FRA_PrintSecureMailListMode[]		= "   Imp. liste S.Mail";
CUB	FRA_PrintSecureMailMode[]			= "   Imp. SecureMail  ";
CUB	FRA_SecureMailHoldTimeMode[]		= "   M｢mo. SecureMail ";

CUB	FRA_PrintCommandsMode[]				= "   Imp. commandes   ";
CUB	FRA_PrintStoredDocumentMode[]		= "   Imp. doc. m｢mor. ";

CUB	FRA_JournalOnOffMode[]				= "   Journal oui/non  ";
CUB	FRA_PrintJournalMode[]				= "   Imp. Journal     ";
CUB	FRA_SettingCommunicationResult[]	= "   Prog. rapp comm. ";

CUB	FRA_SettingScanParameters[]			= "    Param. Analyse  ";
CUB	FRA_SettingPrintParameters[]		= "    Param.Impression";
CUB	FRA_SettingCopyParameters[]			= "    Param. Copie    ";	/* POPLAR_B以外 */
CUB	FRA_SettingPaperSize[]				= "    Prog.Format Pap.";	/* ANZUのみ */
CUB	FRA_SettingCopyProtect[]			= "    Protect.Copie   ";
CUB	FRA_SettingDialingPause[]			= "    Prog. pause num.";
CUB	FRA_SettingNumberOfRings[]			= "    Prog. nomb. sonn";
CUB	FRA_SettingRedial[]					= "    Prog. Rappel    ";
CUB	FRA_SettingECMMode[]				= "    Prog. mode ECM  ";
CUB	FRA_SettingPasscode[]				= "    Prog.code accｪs ";
CUB	FRA_SettingClosedNetwork[]			= "    Prog. r｢s. ferm｢";
CUB	FRA_SettingSecurityTransmission[]	= "    Emiss. prot｢g｢e ";
CUB	FRA_SettingBlockJunkMail[]			= "    R｢cept. prot｢g｢e";
CUB	FRA_SettingRemoteDiagnostic[]		= "   Prog.mode Service";
CUB	FRA_SettingMemoryTransmission[]		= "    Prog. ｢m. m｢mo. ";
CUB	FRA_SettingSilentOperation[]		= "    Prog.Mode Silen.";
CUB	FRA_SettingDialIn[]					= "    Set Dial In     ";	/* JPN */
CUB	FRA_SettingProtectPasscode[]		= "    Code protection ";
CUB	FRA_SettingOperationProtect[]		= "    Pr.Util prot｢g｢e";
CUB	FRA_SettingPINAccessMode[]			= "    Prog. mode PIN  ";
CUB	FRA_SettingRingMasta[]				= "    Prog.DRD        ";	/* (USA) */
CUB	FRA_SettingStamp[]					= "    Prog. tampon    ";
CUB	FRA_SettingResetDrumLife[]			= "    Init.Vie tambour";	/* ANZUのみ */
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */
CUB	FRA_SettingRxAlarm[]				= "    Prog.Alarme R｢c.";
CUB	FRA_SettingMercuryMode[]			= "    Prog. pr｢f.num. ";
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	FRA_SettingHoldMelody[]				= "    Wartemelodie    ";
#endif
#if (PRO_REMOTE_RX == ENABLE)			/* ＮＴＴ仕様のポプラＬで使用 98/01/26 T.Fukumoto */
CUB	FRA_SettingRemoteReceive[]			= "    Set Remote Trans";
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	FRA_SettingOnHookReceive[]			= "    Set Onhook Trans";	/* 98/03/13 Add By T.Fukumoto */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	FRA_SettingPrintSettings[]			= "    Imp. paramｪtres ";
#endif

CUB	FRA_SetMessageOnOff[]				= "   Message Emis     ";
CUB	FRA_SetMessage[]					= "   Prog. Message    ";
CUB	FRA_PrintMessageList[]				= "   Liste Message    ";

CUB	FRA_SettingDepartmentProtect[]		= "   Prog d｢part Prot.";
CUB	FRA_SettingDepartmentCode[]			= "   Prog code d｢pt.  ";
CUB	FRA_SettingDepartmentOnOff[]		= "   Prog D｢pt oui/non";
#if (PRO_DEPART_NEW_LIST == ENABLE)									/* added by thonda 1997/12/03 */
CUB	FRA_PrintDepartTimeList[]			= "   ImpListeTemps Ext";
CUB	FRA_EraseDepartTimeList[]			= "   EffListeTemps Ext";
#endif

CUB	FRA_SettingBatchBox[]				= "   Prog boｬte envoi ";
CUB	FRA_PrintBatchBoxList[]				= "   Imp. liste boｬtes";
CUB	FRA_PrintBatchDocList[]				= "   Imp liste docum. ";
CUB	FRA_PrintBatchDoc[]					= "   Imp doc envoi gr.";
CUB	FRA_EraseBatchBox[]					= "   Eff. Boｬte envoi ";
CUB	FRA_EraseBatchDoc[]					= "   Eff. Doc. Envoi  ";

CUB	FRA_SettingSecurityRx[]				= "   Prog R｢c. S｢cur. ";
CUB	FRA_PrintMemoryReceiveDoc[]			= "   Imp doc reｧus m｢m";

#if (PRO_F_CODE == ENABLE)
CUB	FRA_EnterFcodeBoxMode[]				= "   Prog.Boｬte F-CODE";
CUB	FRA_PrintFcodeBoxListMode[]			= "   Imp.liste Boｬte  ";
CUB	FRA_PrintFcodeStoreDocListMode[]	= "   Imp.liste Doc.   ";
CUB	FRA_PrintFcodeStoreDocMode[]		= "   Imp.Doc.F-Code   ";
CUB	FRA_EraseFcodeBoxMode[]				= "   Eff.Boｬte F-CODE ";
CUB	FRA_EraseFcodeDocMode[]				= "   Eff.Doc.F-CODE   ";
CUB	FRA_StoreFcodeDocMode[]				= "   Prog.Doc.F-CODE  ";
#endif

#if (PRO_CIPHER == ENABLE)
CUB	FRA_EnterCipherKeyBookMode[]		= "   Prog.R｢p.Touches ";
CUB	FRA_PrintCipherKeyBookListMode[]	= "   Liste R｢p.Touche ";
CUB	FRA_PrintCipherKeyMode[]			= "   Imp.Touche       ";
CUB	FRA_EraseCipherKeyBookMode[]		= "   Eff.R｢p.Touches  ";
CUB	FRA_EraseCipherRxDocMode[]			= "   Eff.Doc.Chiffr.  ";
CUB	FRA_EnterDefaultCipherKeyMode[]		= "   Prog.Touche repli";
CUB	FRA_EnterCipherServiceLabelMode[]	= "   Posit.｢tiq.Serv. ";
CUB	FRA_EnterCipherPassCodeMode[]		= "   Prog.code accｪs  ";
#endif

CUB	FRA_SettingRS232CPCFaxScan[]		= "   PC-FAX Analyse   ";
CUB	FRA_SettingRS232CParameter[]		= "   Prog.RS232C      ";
CUB	FRA_SettingRS232CPCFaxInitial[]		= "   PC-FAX Initial   ";

/*----------------------------------*
 *	ワンタッチ登録
 *----------------------------------*/
CUB	FRA_SelectOnetouch[]				= "S｢lect. Nﾏ Une-Touch";

CUB	FRA_EraseOnetouch[]					= "Eff. Une-Touche     ";
CUB	FRA_EraseSpeedDial[]				= "Eff. num. abr｢g｢s   ";
CUB	FRA_EraseProgramOnetouch[]			= "Eff. Une-T. prog.   ";

/*----------------------------------*
 *	短縮登録
 *----------------------------------*/
CUB	FRA_SelectOptionalSpeedNumber[]		= "   /     (0-999):   ";

/* ワンタッチ・短縮ダイアルデータ入力中 */
/* このワーディングのサイズ及び登録順はかえてはいけない */
CUB	FRA_FaxNumber[]						= "Num｢ro Fax          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	FRA_AltNumber[]						= "Num. repli          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	FRA_RemoteName[]					= "Nom                 ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大9ﾊﾞｲﾄです */
CUB	FRA_GroupNumber[]					= "Num｢ro group        ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	FRA_PinNumber[]						= "Code PIN            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	FRA_Attribute1[]					= "Attribut 1          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	FRA_Attribute2[]					= "Attribut 2          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	FRA_Attribute3[]					= "Attribut 3          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	FRA_Attribute4[]					= "Attribut 4          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */

CUB	FRA_SetPIN_Number[]					= "Prog. code PIN      ";

/*----------------------------------*
 *	プログラムワンタッチ
 *----------------------------------*/
CUB	FRA_SelectProgramOnetouch[]			= "S｢l. No. Program.   ";

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	拡張版プログラムワンタッチ
 *----------------------------------*/
CUB FRA_ProgramItem[][21]		= {
										  "         Type: Comm.",
										  "         Type: Aff. ",
										  "         Type: Mem. ",
};
CUB FRA_ProgramList[][21]		= {
										  "   Imp. Une-Touche  ",
										  "   Imp. num.abr｢g｢s ",
										  "   Imp. Une-T.prog. ",
										  "    Set Onhook Trans",
										  "   Imp. commandes   ",
										  "   Imp. Journal     ",
										  "   Liste groupes    ",
										  "   Imp. param｢tres  ",
										  "   Imp Num prot｢g｢s ",
										  "   Liste Message    ",
										  "   Liste Boite envoi",
										  "   Liste Doc. Envoi ",
 #if (PRO_F_CODE == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "   Liste BoiteF-Code",
										  "   Liste BoiteF-Code",
 #endif
 #if (PRO_DEPART_NEW_LIST == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "   Liste Departement",
 #endif
 #if (PRO_NUMBER_DISPLAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "    NDﾀﾞｲﾔﾙ ﾘｽﾄ     ",
										  "    NDﾘﾚｷ ﾌﾟﾘﾝﾄ     ",
 #endif
 #if (PRO_RX_DOC_TRANSFER == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "    FAXﾜｰﾌﾟ ﾘｽﾄ     ",
 #endif
};
CUB FRA_ProgramStore[][21]		= {
										  "   Ent. doc. polling",
 #if (PRO_F_CODE == ENABLE)	/* By H.Fujimura 1999/01/07 */
										  "   Mem. Doc. F-Code ",
 #endif
};
CUB FRA_ProgramTxModeSW[][21]	= {
										  "    Mode: ---       ",
										  "    Mode: Normal    ",
										  "    Mode: Fin       ",
										  "    Mode: S-Fin     ",
										  "    Mode: Gris      ",
};
CUB FRA_ProgramContrastSW[][21]	= {
										  "    Contraste:---   ",
										  "    Contraste:Clair ",
/*										  "    ﾉｳﾄﾞ:    ﾔﾔ ｳｽｸ ",*/
										  "    Contraste:Normal",
/*										  "    ﾉｳﾄﾞ:    ﾔﾔ ｺｸ  ",*/
										  "    Contraste:Fonc｢ ",
};
CUB FRA_ProgramStampSW[][21]	= {
										  "    tampon: ---     ",
										  "    tampon: ---     ",
										  "    tampon: ---     ",
};
CUB FRA_ProgramMemoryTxSW[][21]	= {
										  "    ｢m. m｢mo.: ---  ",
										  "    ｢m. m｢mo.: Off  ",
										  "    ｢m. m｢mo.: On   ",
};
CUB FRA_ProgramConfirmSW[][21]	= {
										  "    R｢sult.comm: ---",
										  "    R｢sult.comm: Off",
										  "    R｢sult.comm: TCR",
										  "    R｢sult.comm: RCR",
};
#endif	/* (PRO_EXT_P_ONETOUCH == ENABLE) */

/*----------------------------------*
 *	ポーリング
 *----------------------------------*/
#if (PRO_OKI == ENABLE)
CUB	FRA_StorePollingDocument[]			= "Entrer doc. relｪve  ";	/* polling -> relｪve by K.Watanabe 1999/02/04 */
CUB	FRA_ErasePollingDocument[]			= "Effacer doc. relｪve ";	/* polling -> relｪve by K.Watanabe 1999/02/04 */
CUB	FRA_PrintPollingDocument[]			= "Imp. doc. relｪve    ";	/* polling -> relｪve by K.Watanabe 1999/02/04 */
#else
CUB	FRA_StorePollingDocument[]			= "Entrer doc. Polling ";
CUB	FRA_ErasePollingDocument[]			= "Effacer doc. Polling";
CUB	FRA_PrintPollingDocument[]			= "Imp. doc. Polling   ";
#endif

/*----------------------------------*
 *	親展
 *----------------------------------*/
CUB	FRA_SetSecureMailBox[]				= "Prog. Boｬte S.Mail  ";
CUB	FRA_SecureMailHoldTime[]			= "M｢mor. SecureMail   ";
CUB	FRA_HoldTime1_31[]					= "Dur｢e m｢mo.(1-31):\0 ";
CUB	FRA_SecureMailName[]				= " :Nom      \0        ";	/* 先頭1文字は、親展番号をｾｯﾄします */

/*----------------------------------*
 *	通信予約
 *----------------------------------*/
CUB	FRA_PrintStoredDocument[]			= "Imp. doc. en m｢moire";
CUB	FRA_InputCommandNumber[]			= "Nﾏ de comm.   :     ";
#if (PRO_CIPHER == ENABLE)
CUB	FRA_SelectDecipher[]				= "D｢chiffrage    :\0   ";	/* 1998/01/19 １バイト足らんやんけ～ */
#endif

/*----------------------------------*
 *	ジャーナル
 *----------------------------------*/
CUB	FRA_JournalOnOff[]					= "Journal oui/non     ";
CUB	FRA_SelectAutoPrint[]				= "Imp. autom.    :\0   ";
CUB	FRA_TCRSelected[]					= "TCR s｢lectionn｢     ";
CUB	FRA_RCRSelected[]					= "RCR s｢lectionn｢     ";
CUB	FRA_SetCommunicationResult[]		= "Prog. rapp comm.    ";

/*----------------------------------*
 *	設置モード
 *----------------------------------*/
/* カレンダー入力 */
CUB	FRA_InputTime[]						= "Prog. heure         ";

/* 夏時間切り替え */
#if defined(USA)
CUB	FRA_DayLightSaving[]				= "Heure d'｢t｢    :\0   ";
#endif

/* ＴＴＩ */
CUB	FRA_EnterYourFaxNumber[]			= "Votre num.de Fax    ";  /* Votre num｢ro de Fax -> */
CUB	FRA_EnterYourName[]					= "VotreNom            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	FRA_EnterYourKanaName[]				= "Your KanaID         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* JPN */

/* 回線種別 */
CUB	FRA_SelectPhoneType[]				= "Type T｢l     :\0     ";  /* Type de T｢l -> */
CUB	FRA_10pps[]							= "              10pps ";
CUB	FRA_20pps[]							= "              20pps ";
CUB	FRA_Tone[]							= "              Tonal.";  /* Tone bythonda1998/02/24 */

CUB	FRA_Pulse10[]						= "              Impul.";
CUB	FRA_Pulse20[]						= "              Impul.";
CUB	FRA_Push[]							= "              Tonal.";  /* Tone bythonda1998/02/24 */

CUB	FRA_PrintSettingList[]				= "Imp liste paramｪtres";	/* ANZUのみ */

#if (PRO_MULTI_LINE == ENABLE) || (PRO_MULTI_TTI == ENABLE)	/* 多回線仕様追加 1997/09/03 Y.Matsukuma */
/* マルチ回線ユーザー設定 */	/* ANZU_Lと分けてたが、共通にします。1998/01/19 Y.Matsukuma */
/* 注）かっこの位置は固定すること。ただし、(9)は除く。 */
CUB	FRA_MultiYourFaxNumber[]			= "Votre num.de Fax ( )";  /* Votre Num｢ro Fax -> */
CUB	FRA_MultiYourName[]					= "VotreNom( )         ";
CUB	FRA_MultiYourKanaName[]				= "Kana ID ( )         ";	/* JPN */
CUB	FRA_MultiPhoneType[]				= "Type T｢l  ( ):\0     ";
CUB	FRA_MultiTxRx[]						= "Em/R｢c.   ( ):\0     ";
CUB	FRA_SelectTxRx[]					= "              Em/R｢c";
CUB	FRA_SelectTx[]						= "              Em.   ";
CUB	FRA_SelectRx[]						= "              R｢c.  ";
CUB	FRA_MultiLineType[]					= "Type ligne (9):\0    ";/* <- Ligne No.*/	/* 回線表示位置には必ず9を定義（国別の表示位置対応） */
CUB	FRA_SelectLinePstn[]				= "               PSTN ";
CUB	FRA_SelectLinePbx[]					= "               PBX  ";
CUB	FRA_SetAccessNumber[]				= "Num. Accｪs r｢seau( )";
#endif

/* Ｆｕｎｃｔｉｏｎ */
CUB	FRA_On1[]							= "                Oui ";	/* ﾃﾞﾌｫﾙﾄがONではじまる場合 */
CUB	FRA_Off1[]							= "                Non ";
CUB	FRA_Off2[]							= "                Non ";	/* ﾃﾞﾌｫﾙﾄがOFFではじまる場合 */
CUB	FRA_On2[]							= "                Oui ";
CUB	FRA_Off3[]							= "                 Non";
CUB	FRA_On3[]							= "                 Oui";
CUB	FRA_On4[]							= "                 Oui";
CUB	FRA_Off4[]							= "                 Non";
CUB	FRA_ModeOff[]						= "               Non  ";
CUB	FRA_Mode1[]							= "               Mode1";
CUB	FRA_Mode2[]							= "               Mode2";
CUB	FRA_Mode3[]							= "               Mode3";

/*----------------------------------*
 *	ユーザー設定
 *----------------------------------*/
/*読み取りパラメータ */
/* 原稿読みとり幅 */
CUB	FRA_SelectScanWidth[]				= "Larg analyse    :\0  ";
CUB	FRA_ScanA4[]						= "                 A4 ";
CUB	FRA_ScanB4[]						= "                 B4 ";
CUB	FRA_ScanA3[]						= "                 A3 ";

/* 優先モード */
CUB	FRA_SelectPrimaryMode[]				= "Initial   :\0        ";
CUB	FRA_PrimaryModeNormal[]				= "           Normal   ";
CUB	FRA_PrimaryModeFine[]				= "           Fin      ";
CUB	FRA_PrimaryModeSFine[]				= "           S-Fin    ";
CUB	FRA_PrimaryModeGray[]				= "           Gris     ";

/* 優先原稿濃度 */
CUB	FRA_SelectPrimaryContrast[]			= "Contraste   :\0      ";
CUB	FRA_PrimaryContrastLight[]			= "             Clair  ";
CUB	FRA_PrimaryContrastLittleLight[]	= "             Eclairc";  /* ﾔﾔ ｳｽｸ bythonda1998/02/24 */
CUB	FRA_PrimaryContrastNormal[]			= "             Normal ";
CUB	FRA_PrimaryContrastlittleDark[]		= "             Foncer ";  /* ﾔﾔ ｺｸ bythonda1998/02/24 */
CUB	FRA_PrimaryContrastDark[]			= "             Fonc｢  ";

CUB	FRA_SetScanParameters[]				= "Param. Analyse      ";

/* プリントパラメータ */
CUB	FRA_SelectReceiveReduction[]		= "Taux R｢duct Imp:\0   ";
CUB	FRA_AutoReduction[]					= "                Auto";
CUB	FRA_100[]							= "                100%";
CUB	FRA_97[]							= "                 97%";
CUB	FRA_91[]							= "                 91%";
CUB	FRA_81[]							= "                 81%";
CUB	FRA_75[]							= "                 75%";
CUB	FRA_InputThresholdValue0_85[]		= "Seuil    (0-85mm):\0 ";
CUB	FRA_SelectPageCompound[]			= "Comp. pages     :\0  ";
CUB	FRA_SetPrintParameters[]			= "Param. Impression   ";
#if (PRO_ROTATE == ENABLE)
CUB	FRA_SetRotateMargin[]				= "Pivoter Impression  ";  /* ｶｲﾃﾝ ｼﾞｭｼﾝ bythonda1998/02/24 */
#endif

/* コピーパラメータ */
CUB	FRA_SelectSortingCopy[]				= "Tri Copies     :\0   ";
CUB	FRA_SelectCopyReduction[]			= "Taux R｢d. Copie:\0   ";	/* POPLAR_B以外 */
CUB	FRA_SetCopyParameters[]				= "Param. Copie        ";	/* POPLAR_B以外 */

/* 記録紙サイズ */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	FRA_EnterPaperSize[]				= "Format Pap. :\0      ";
CUB	FRA_PaperSizeNone[]					= "             None   ";
CUB	FRA_PaperSizeA4[]					= "             A4     ";
CUB	FRA_PaperSizeB4[]					= "             B4     ";
CUB	FRA_PaperSizeLetter[]				= "             Letter ";
CUB	FRA_PaperSizeLegal[]				= "             Legal  ";
CUB	FRA_PaperSizeF4[]					= "             F4     ";
CUB	FRA_SetPaperSize[]					= "Prog Format Pap.    ";

 #if (PRO_PC_PRINT == ENABLE)	/* ＰＣプリント */
CUB	FRA_SelectPaperSizeNone[]			= "             None   ";	/* 不要かもしれない */
CUB	FRA_SelectPaperSizeA5[]				= "             A5_P   ";
  #if defined(USA)
CUB	FRA_SelectPaperSizeLetter[]			= "             Letter ";
  #else
CUB	FRA_SelectPaperSizeLetter[]			= "             Ltr_P  ";
  #endif
  #if defined(USA)
CUB	FRA_SelectPaperSizeA4[]				= "             A4_P   ";
  #else
CUB	FRA_SelectPaperSizeA4[]				= "             A4     ";
  #endif
  #if defined(USA) || defined(TWN) /* 1998/01/09 Y.Matsukuma */
CUB	FRA_SelectPaperSizeLegal[]			= "             Legal  ";
  #else
CUB	FRA_SelectPaperSizeLegal[]			= "             Legal_P";
  #endif
CUB	FRA_SelectPaperSizeB5R[]			= "             B5R_P  ";
CUB	FRA_SelectPaperSizeB4[]				= "             B4_P   ";
CUB	FRA_SelectPaperSizeA3[]				= "             A3_P   ";
CUB	FRA_SelectPaperSizeA4R[]			= "             A4R_P  ";
CUB	FRA_SelectPaperSizeLetterR[]		= "             LtrR_P ";
  #if defined(TWN) || defined(AUS)	/* 1998/01/09 Y.Matsukuma */
CUB	FRA_SelectPaperSizeF4[]				= "             F4     ";
  #else
CUB	FRA_SelectPaperSizeF4[]				= "             F4_P   ";
  #endif
CUB	FRA_SelectPaperSizeA5R[]			= "             A5R_P  ";
CUB	FRA_SelectPaperSizePostcard[]		= "             Post_P ";
CUB	FRA_SelectPaperSizeLD[]				= "             Ld_P   ";
CUB	FRA_SelectPaperSizeGLetterR[]		= "             GLtrR_P";
CUB	FRA_SelectPaperSizeExecutiveR[]		= "             ExeR_P ";
CUB	FRA_SelectPaperSizeInvoiceR[]		= "             InvR_P ";
CUB	FRA_SelectPaperSizeGLegal[]			= "             GLegl_P";
CUB	FRA_SelectPaperSizeGLetter[]		= "             GLtr_P ";
CUB	FRA_SelectPaperSizeCard[]			= "             Card_P ";
CUB	FRA_SelectPaperSizeExecutive[]		= "             Exe_P  ";
CUB	FRA_SelectPaperSizeB5[]				= "             B5_P   ";
CUB	FRA_SelectPaperSizeC5[]				= "             C5_P   ";
CUB	FRA_SelectPaperSizeHalfLetter[]		= "             HLtr_P ";
CUB	FRA_SelectPaperSizeInvoice[]		= "             Inv_P  ";
CUB	FRA_SelectPaperSizeB6[]				= "             B6_P   ";
CUB	FRA_SelectPaperSizeDL[]				= "             DL_P   ";
CUB	FRA_SelectPaperSizeCM10[]			= "             CM10_P ";
CUB	FRA_SelectPaperSizeA6[]				= "             A6_P   ";
CUB	FRA_SelectPaperSizeMonarch[]		= "             Mnc_P  ";
CUB	FRA_SelectPaperSize35[]				= "             3x5_P  ";
CUB	FRA_SelectPaperSizeUser[]			= "             User_P ";
 #endif
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */

/* コピー禁止 */
CUB	FRA_SelectCopyProtect[]				= "Protect Copie  :\0   ";

/* ポーズ */
CUB	FRA_SetDialingPause[]				= "Prog. pause num.    ";
CUB	FRA_PauseTime[]						= "Temps       :\0      ";	/* 注）ｼﾞｶﾝ (05-10): の（）の部分は実行時に作成します */

/* べル回数 */
CUB	FRA_SetNumberOfRings[]				= "Prog. nomb. sonn    ";
CUB	FRA_NumberOfRings[]					= "Nﾏ          :\0      ";	/* 注）ｶｲｽｳ   (1-9): の（）の部分は実行時に作成します */

/* リダイアル */
CUB	FRA_RedialCount[]					= "Nﾏ          :\0      ";	/* 注）ｶｲｽｳ (02-10): の（）の部分は実行時に作成します */
CUB	FRA_SetNumberOfRedials[]			= "Prog nomb. rapp.    ";
CUB	FRA_RedialInterval[]				= "Interv.     :\0      ";	/* 注）ｶﾝｶｸ   (1-5): の（）の部分は実行時に作成します *//* :を左に2ﾊﾞｲﾄｼﾌﾄ by K.Watanabe 1998/08/11 */
CUB	FRA_SetRedialInterval[]				= "Prog pause rapp.    ";
CUB	FRA_SetRedial[]						= "Prog. Rappel        ";

/* ECM */
CUB	FRA_SelectECMMode[]					= "Mode ECM       :\0   ";
CUB	FRA_SetECMMode[]					= "Prog. mode ECM      ";

/* パスコード */
CUB	FRA_SetPasscode[]					= "Prog code accｪs     ";

/* 閉域通信設定 */
CUB	FRA_SelectClosedNetwork[]			= "R｢s. ferm｢     :\0   ";
CUB	FRA_SetClosedNetwork[]				= "Prog. r｢s. ferm｢    ";

/* パスワード送信 */
CUB	FRA_SelectSecurityTransmission[]	= "Emiss. prot｢g｢e:\0   ";
CUB	FRA_SetSecurityTransmission[]		= "Emiss. prot｢g｢e     ";

/* ダイレクトメール防止 */
CUB	FRA_SelectBlockJunkMail[]			= "R｢c. prot｢g｢e :\0    ";
CUB	FRA_SetBlockJunkMailDial[]			= "Prog Num prot｢g｢e   ";
CUB	FRA_PrintBlockJunkMailDialList[]	= "Imp Num prot｢g｢e    ";
CUB	FRA_SetBlockJunkMail[]				= "R｢cept. prot｢g｢e    ";
CUB	FRA_BlockJunkMailSelectNumber[]		= "Choix Num prot｢g    ";
CUB FRA_SetSameNumber[]					= "D｢j･ m｢moris        ";

/* リモート診断 */
CUB	FRA_SelectRemoteDiagnostic[]		= "Mode de Service:\0   ";
CUB	FRA_SetRemoteDiagnostic[]			= "Prog. mode Service  ";

/* メモリー送信 */
CUB	FRA_SelectMemoryTransmission[]		= "Em. m｢moire    :\0   ";
CUB	FRA_SetMemoryTransmission[]			= "Prog. ｢m. m｢mo.     ";

/* サイレントオペレーション */
CUB	FRA_SelectSilentOperation[]			= "mode Silen.    :\0   ";
CUB	FRA_SetSilentOperation[]			= "Set Mode Silen.     ";

/* プロテクトパスコード */
CUB	FRA_SetProtectPasscode[]			= "Code protection     ";
CUB	FRA_ProtectPasscode[]				= "Code protection     ";

/* オペレーションプロテクト */
CUB	FRA_OperationProtectOnOff[]			= "Utilis prot｢e｢ :\0   ";
CUB	FRA_SetOperationProtect[]			= "Pr. Util prot｢e｢e   ";

/* ＰＩＮアクセスモードセット */
CUB	FRA_PINAccessMode[]					= "Mode PIN      :\0    ";
CUB	FRA_SetPINAccessMode[]				= "Prog. mode PIN      ";

/* リングマスター */
#if (PRO_RING_MASTER == ENABLE)	/* by K.Watanabe 1998/08/18 */
CUB	FRA_SelectRingMaster[]				= "DRD            :\0   ";
CUB	FRA_SelectRingPattern[]				= "Cadence Sonnerie :\0 ";
CUB	FRA_RingPattern_A[]					= "                  A ";
CUB	FRA_RingPattern_B[]					= "                  B ";
CUB	FRA_RingPattern_C[]					= "                  C ";
CUB	FRA_RingPattern_D[]					= "                  D ";
CUB	FRA_RingPattern_E[]					= "                  E ";
CUB	FRA_RingPattern_F[]					= "                  F ";
CUB	FRA_RingPattern_G[]					= "                  G ";
CUB	FRA_RingPattern_H[]					= "                  H ";
CUB	FRA_SetRingMaster[]					= "Prog DRD            ";
#endif

/* 済みスタンプ */
CUB	FRA_StampOnOff[]					= "Tampon         :\0   ";
CUB	FRA_SetStamp[]						= "Prog. tampon        ";

/* ドラム寿命リセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* by K.Watanabe 1998/08/18 */
CUB	FRA_ResetDrumLife[]					= "Init. Vie tambour   ";
#endif

/* 受信アラームセット */
#if defined(GBR)
CUB	FRA_RxAlarm[]						= "Alarme Audible :\0   ";
CUB	FRA_SetRxAlarm[]					= "Prog. Alarme R｢c.   ";
#endif

/*----------------------------------*
 *	マーキュリー
 *----------------------------------*/
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */
/* マーキュリー番号  */
CUB	FRA_MercuryNumberSet[]				= "Composer pr｢fixe    ";
/* マーキュリーポーズ  */
CUB	FRA_MercuryPauseSet[]				= "Prog. pause pr｢fixe ";
CUB	FRA_SetMercury[]					= "Prog. pr｢fixe num   ";
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* 保留メロディーセット */
CUB	FRA_SelectHoldMelody[]				= "Wartemelodie   :\0   ";
#endif

/* リモート受信 */
#if (PRO_REMOTE_RX == ENABLE)			/* ＮＴＴ仕様のポプラＬで使用 98/01/26 T.Fukumoto */
CUB	FRA_SelectRemoteReceive[]			= "ﾘﾓｰﾄ ｼﾞｭｼﾝ     :\0   ";
#endif

/* オンフック受信 */
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	FRA_SelectOnHookReceive[]			= "ｵﾝﾌｯｸ ｼﾞｭｼﾝ    :\0   ";	/* 98/03/13 Add By T.Fukumoto */
#endif

/* ダイアルイン */
#if (PRO_DIALIN == ENABLE)
CUB	FRA_SetDialIn[]						= "                    ";
CUB	FRA_DialInFax[]						= "                    ";
CUB	FRA_DialInTel1[]					= "                    ";
CUB	FRA_DialInTel2[]					= "                    ";
CUB	FRA_DialInRings[]					= "                    ";
CUB	FRA_DialInRings10_60[]				= "                    ";
#endif

/*----------------------------------*
 *	カバーページ
 *----------------------------------*/
CUB	FRA_MessageOnOff[]					= "Message        :\0   ";
CUB	FRA_MessageTx[]						= "Prog. Message       ";
CUB	FRA_SetCoverPageMessage[]			= "Message             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	FRA_MessageSet[]					= "Prog. Message       ";

/*----------------------------------*
 *	枚数設定
 *----------------------------------*/
CUB	FRA_InputPageCount[]				= "Prog. nomb. pages   ";
#if defined(POPLAR_N) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ポプラＬ（ＮＴＴ仕様） by K.Watanabe 1998/03/16 */
CUB	FRA_PageCount1_30[]					= "           (1-30):\0 ";
#else
CUB	FRA_PageCount1_30[]					= "           (1-50):\0 ";
#endif

/*----------------------------------*
 *	部門管理
 *----------------------------------*/
/* 部門管理プロテクトセット */
CUB	FRA_DepartmentProtect[]				= "D｢part. Prot｢g｢:\0   ";
CUB	FRA_SetDepartmentProtect[]			= "Prog d｢part Prot.   ";

/* 部門コードセット */
CUB	FRA_DepartmentSelectNumber[]		= "Choix Num D｢partem. ";

/* 部門管理セット */
CUB	FRA_DepartmentOnOff[]				= "D｢pt. Oui/Non  :\0   ";
CUB	FRA_SetDepartmentOnOff[]			= "Prog D｢pt oui/non   ";

#if (PRO_DEPART_NEW_LIST == ENABLE)		/* 追記 By S.Fukui Jan.7,1998 */
/* 簡易部門毎時間管理リスト関連 */
CUB	FRA_EraseDepartTimeListMode[]		= "EffListeTemps.Ext.  ";
CUB	FRA_EraseDepartCode[]				= "    :Eff Coded｢part.";  /* ﾌﾞﾓﾝｺｰﾄﾞ ｼｮｳｷｮ bythonda1998/02/24 *//* 先頭４文字は部門ｺｰﾄﾞ表示 */
CUB FRA_DepartCodeFull[]				= "Code d｢pt Complet   ";
#endif

/*----------------------------------*
 *	一括送信
 *----------------------------------*/
CUB	FRA_SelectBatchBoxNumber[]			= "S｢lect boｬte envoi. ";
CUB	FRA_TranssmissionTime[]				= "Heure d'envoi       ";
CUB	FRA_EraseBatchBoxMode[]				= "Eff. Boｬte envoi    ";
CUB	FRA_EraseBatchDocumentMode[]		= "Eff. Doc. Envoi     ";

CUB	FRA_PrintBatchBoxMode[]				= "Imp. Liste boｬtes   ";
CUB	FRA_PrintBatchDocListMode[]			= "Imp liste docum.    ";
CUB	FRA_PrintBatchDocMode[]				= "Imp doc envoi gr.   ";
CUB	FRA_BatchBoxNumber[]				= "Entrer No boｬte   \0 ";
CUB	FRA_BatchFileNumber[]				= "Entrer No Fich.  \0  "; /* "Entrer No fichier\0  " 変更 by sasaki 00/01/14 */

/*----------------------------------*
 *	セキュリティ受信
 *----------------------------------*/
/* セキュリティ受信セット */
CUB	FRA_SecurityReceive[]				= "R｢c. S｢curit｢  :\0   ";
CUB	FRA_SetSecurityReceive[]			= "Prog R｢c. S｢cur.    ";

/* メモリ受信原稿プリント */
CUB	FRA_PrintMemoryReceiveDocMode[]		= "Imp doc rcｧus m｢m   ";

/*----------------------------------*
 *	Ｆコード
 *----------------------------------*/
#if (PRO_F_CODE == ENABLE)
CUB	FRA_SelectFcodeBoxNumber[]			= "Choix Boｬte F-CODE  ";
CUB	FRA_EnterFcodeBoxName[]				= "  :NomBoｬte\0        ";
CUB	FRA_EnterFcodeSubAddress[]			= "  :Adresse          ";
CUB	FRA_EnterFcodePassword[]			= "  :Code d'accｪs     "; /* "  :Prog.Code accｪs  " 変更 by sasaki 00/01/14 */
CUB	FRA_SelectFcodeBoxKind[]			= "Type Boｬte :\0       ";
CUB	FRA_FcodeBulletinBoardBox[]			= "            Bulletin";
CUB	FRA_FcodeConfidentialBox[]			= "            S｢curit ";
#if (PRO_FCODE_RELAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
CUB	FRA_FcodeRelayBox[]					= "            relais  ";
#endif
CUB	FRA_SelectFcodeRxProhibition[]		= "Protect R｢c.   :\0   ";
CUB	FRA_SelectFcodeRxDocPrint[]			= "Imp.Autom.     :\0   ";
CUB	FRA_SelectFcodeRxDocUpperWrite[]	= "Ecraser Doc.   :\0   ";
CUB	FRA_SelectFcodeTxDocClear[]			= "Eff.Doc.Em.    :\0   ";
CUB	FRA_FcodeDocumentHoldTime[]			= "R｢t.Doc.F-CODE      ";
CUB	FRA_HoldTime0_31[]					= "R｢tension  (0-31):\0 ";
CUB	FRA_SelectFcodeStoreDocAdd[]		= "Ajout.Doc.     :\0   ";
CUB	FRA_StoreFcodeDocument[]			= "Doc F-CODE  Fich.:  ";
 #if (PRO_FCODE_RELAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
CUB	FRA_InputRelayNumber[]				= "Ent. No. Relais     ";
CUB FRA_SetRelayTTI[][21]				= {
										  "Select. TTI  :\0     ",
										  "              ﾂｹﾅｲ  ",
										  "              ｿﾄﾂﾞｹ ",
										  "              ｳﾜｶﾞｷ ",
};
 #endif
#endif
CUB	FRA_SameNumber[]					= "Adresse Utilis｢e    ";

/*----------------------------------*
 *	ＰＣプリントボード初期化
 *----------------------------------*/
#if (PRO_PC_PRINT == ENABLE)
CUB	FRA_BoardReset[]					= "Init.Opt.Imprim.    ";
#endif

/*----------------------------------*
 *	暗号化
 *----------------------------------*/
#if (PRO_CIPHER == ENABLE)
CUB	FRA_EnterCipherKeyName[]			= " :Titre Tch\0        ";
CUB	FRA_EnterCipherKey[]				= " :Prog.Tch.\0        ";
CUB	FRA_EnterCipherKeyClue[]			= " :Ident Tch\0        ";
CUB	FRA_InputCipherRxDocNumber[]		= "Nbre.Doc.Reｧus   :\0 ";
CUB	FRA_InputCipherExtensionKey[]		= "Ext.Touche      :\0  ";
CUB	FRA_SelectCipherDocErrRemoval[]		= "Corr.Erreur    :\0   ";
CUB	FRA_SelectCipherKeySetKind[]		= "Prog.Tch.   :\0      ";
CUB	FRA_CipherKeySetDefault[]			= "             D｢faut.";
CUB	FRA_CipherKeySetKeyBook[]			= "             R｢pTch.";
CUB	FRA_CipherKeySetDirect[]			= "             Direct ";
CUB	FRA_InputCipherDefaultKeyNo[]		= "Num.Touche  (0-9):\0 ";
 #if defined(USA)
CUB	FRA_InputServiceLabelPosition[]		= "Offset(1-14.5\"):\0   ";  /* by t.fukumoto 1997/12/12 */
 #else
CUB	FRA_InputServiceLabelPosition[]		= "Offset  (2-36cm):\0  ";
 #endif
CUB	FRA_CipherSelectNumber[]			= "Choix Num.Cl.       ";
CUB	FRA_CipherExecute[]					= "Chiff.Doc.     99/99";
CUB	FRA_DecipherExecute[]				= "D｢chiff.Doc.   99/99";
CUB	FRA_CipherExecuteError[]			= "Erreur Chiff.       ";
CUB	FRA_DecipherExecuteError[]			= "Erreur D｢chiff.     ";
CUB	FRA_DecipherKeyError[]				= "Touche inutilisable ";
CUB	FRA_ConfirmDecipherContinue[]		= "ContD｢chf Entr/Annul";  /* ｶｲｼﾞｮ ｹｲｿﾞｸ ｾｯﾄ/ｸﾘｱ bythonda1998/03/19 */
CUB	FRA_DecipherDocument[]				= "Document d｢chiffr   ";  /* ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ｹﾞﾝｺｳ bythonda1998/02/24 */
CUB	FRA_StopCipherExecute[]				= "Arrｨt chiffrage     ";  /* ｽｸﾗﾝﾌﾞﾙ ﾁｭｳｼ bythonda1998/07/15 */
CUB	FRA_StopDecipherExecute[]			= "Arrｨt d｢chiffrage   ";  /* ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ﾁｭｳｼ bythonda1998/07/15 */
#endif
CUB	FRA_InputPrintPageNumber[]			= "Num｢ro    (1-99):\0  ";
CUB	FRA_ProgressRate[]					= " 0%            100% ";

/*----------------------------------*
 *	クラス１
 *----------------------------------*/
CUB	FRA_SetRS232CParameter[]			= "Prog.RS232C         ";
CUB	FRA_SetRS232CPCFaxInitial[]			= "PC-FAX Initial      ";

/* ＲＳ２３２Ｃボーレート */
CUB	FRA_SelectRS232CBaudRate[]			= "Vitesse   :\0        ";
CUB	FRA_RS232CVariable[]				= "           Variable ";
CUB	FRA_RS232C600bps[]					= "             600bps ";
CUB	FRA_RS232C1200bps[]					= "            1200bps ";
CUB	FRA_RS232C2400bps[]					= "            2400bps ";
CUB	FRA_RS232C4800bps[]					= "            4800bps ";
CUB	FRA_RS232C9600bps[]					= "            9600bps ";
CUB	FRA_RS232C19200bps[]				= "           19200bps ";

/* ＲＳ２３２Ｃパリティビット設定 */
CUB	FRA_SelectParity[]					= "Parit｢     :\0       ";
CUB	FRA_RS232CNone[]					= "            Sans    ";
CUB	FRA_RS232COdd[]						= "            Impaire ";
CUB	FRA_RS232CEven[]					= "            Paire   ";

/* ＲＳ２３２Ｃストップビット設定 */
CUB	FRA_Select232CStopBit[]				= "Stop         :\0     ";
CUB	FRA_RS232C1bit[]					= "              1 bit ";
CUB	FRA_RS232C2bit[]					= "              2 bit ";

/* ＲＳ２３２Ｃデータ長設定 */
CUB	FRA_Select232CDataLength[]			= "Long mot     :\0     ";
CUB	FRA_RS232C7bit[]					= "              7 bit ";
CUB	FRA_RS232C8bit[]					= "              8 bit ";

/* クラス１関連追加 */
CUB	FRA_PC_FAX_Scan[]					= "PC-FAX Analyse      ";
CUB	FRA_PC_FAX_Print[]					= "Impres. PC-FAX      ";
CUB	FRA_PC_FAX_Connect[]				= "Connexion PC-FAX    ";
CUB	FRA_PC_FAX_InitialError[]			= "PC-FAX Err. Initial.";
CUB	FRA_PC_FAX_Complete[]				= "   ** Termin｢ **    ";
CUB	FRA_PC_FAX_InUse[]					= "PC-FAX utilis｢      "; /* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
CUB	FRA_ReceiveInFax[]					= "R｢ception par Fax ? "; /* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */

/* 送信時、部門コード入力 */
CUB	FRA_EnterDepartmentCode[]			= "Entrer code d｢part. ";

/* 送信時、ダイヤル番号入力 */
CUB	FRA_EnterDialNumber[]				= "Entrer Num｢ro Fax   ";

/* 送信時、ＰＩＮ番号入力 */
CUB	FRA_EnterPinNumber[]				= "Entrer code PIN     ";

/***********************************************************
** Dial-UpｲﾝﾀｰﾈｯﾄFAX関係	1998/03/12 In English by K.Okada
***********************************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/** ユーザ登録 */
CUB FRA_EMailSettingMode[]				= "  E-Mail Setting    ";
CUB FRA_SetUserDataMode[]				= "   Set User Data    ";
CUB FRA_SetUserData[]					= "Set User Data       ";
/*↓この2つはこの順番で並べて記述*/
CUB FRA_NewEntry[]						= "New Entry?          ";
CUB FRA_UpdateSetting[]					= "Update Setting?     ";
CUB FRA_NewMailBox[]					= "New Mail Box?  :\0   ";
/*↓この2つはこの順番で並べて記述*/
CUB FRA_No[]							= "                No  ";
CUB FRA_Yes[]							= "                Yes ";
CUB FRA_UserCodeNumber[]				= "Your Code No.       ";
CUB FRA_UserCodeNumberAgain[]			= "Code No. Again      ";
CUB FRA_EnterYourCodeNumber[]			= "Enter Your Code No. ";
CUB FRA_ISP_Name[]						= "ISP Name            ";
CUB FRA_AccessPoint[]					= "Access Point        ";
/*↓この3つはこの順番で並べて記述*/
CUB FRA_1stTime[]						= ":1st  \0             ";
CUB FRA_2ndTime[]						= ":2nd  \0             ";
CUB FRA_3rdTime[]						= ":3rd  \0             ";
CUB FRA_UserName[]						= "Your Name           ";
CUB FRA_PPP_LoginID[]					= "PPP-ID              ";
CUB FRA_POP_LoginID[]					= "POP-ID              ";
/*↓この2つはこの順番で並べて記述*/
CUB FRA_PPP_Password[]					= "PPP-PWD             ";
CUB FRA_PPP_PasswordAgain[]				= "Again               ";
/*↓この2つはこの順番で並べて記述*/
CUB FRA_POP_Password[]					= "POP-PWD             ";
CUB FRA_POP_PasswordAgain[]				= "Again               ";
CUB FRA_MailAddress[]					= "Address             ";
CUB FRA_PPP_Auth[]						= "PPP Auth            ";
/*↓この3つはこの順番で並べて記述*/
CUB FRA_PPP_PAP[]						= ":PAP  \0             ";
CUB FRA_PPP_CHAP[]						= ":CHAP \0             ";
CUB FRA_PPP_NoneAuth[]					= ":NONE \0             ";
CUB FRA_Client[]						= "Client              ";
CUB FRA_ISP_Server[]					= "Server              ";
CUB FRA_Gateway[]						= "Gateway             ";
CUB FRA_DNS_Server[]					= "DNS Server          ";
CUB FRA_Primary[]						= ":Primary  \0         ";
CUB FRA_Secondary[]						= ":Secondary\0         ";
CUB FRA_SMTP_Server[]					= "SMTP Server         ";
CUB FRA_POP_Server[]					= "POP Server          ";

/** 機器動作設定 */
#if (0)
//CUB FRA_SetMachineStateMode[]			= "   Auto Mail Receive";
#endif
CUB FRA_SetMachineStateMode[]			= "   Mail Rx Setting  ";
CUB FRA_AutoReceive[]					= "Auto Check Mail:\0   ";
CUB FRA_AutoDownload[]					= "Auto Download : \0   ";
CUB FRA_AutoPrint[]						= "Auto Print    : \0   ";
CUB FRA_DeleteMail[]					= "Delete Mail   : \0   ";
CUB FRA_MailHoldTime[]					= "Mail Hold Days      ";
CUB FRA_Days1_31[]						= "Days(1-31)          ";
CUB FRA_RxDuringTx[]					= "Tx with Rx    : \0   ";
CUB FRA_SetMachineState[]				= "Mail Rx Setting     ";
CUB FRA_AutoRxStartTime[]				= "Start Time          ";
CUB FRA_AutoRxEndTime[]					= "End Time            ";
CUB FRA_IntervalTime[]					= "Interval Time       ";

/** トーン検出設定 */
#if (0)
//CUB FRA_SetToneDetectMode[]				= "   Set Tone Detect  ";
//CUB FRA_SetDialParameter[]				= "Set Tone Detect     ";
//CUB FRA_DialToneOn[]					= "Dial Tone:      \0   ";
//CUB FRA_BusyToneOn[]					= "Busy Tone:      \0   ";
#endif

/** ユーザデータ消去 */
CUB FRA_EraseUserDataMode[]				= "   Erase User Data  ";
CUB FRA_EraseUserData[]					= "Erase User Data     ";

/**  メール設定リスト */
CUB FRA_PrintUserDataMode[]				= "   Print User Data  ";
CUB FRA_PrintUserData[]					= "Print User Data     ";

/** コマンド入力表示 */
CUB FRA_EnterMailAddress[]				= "Enter Mail Address  ";

/** 宛先 */
CUB FRA_SetMailAddressMode[]			= "  Mail Address      ";
CUB FRA_SetMailAddress[]				= "   Set Mail Address ";
CUB FRA_AddressName[]					= "Name                ";
CUB FRA_EraseMailAddressMode[]			= "   Erase MailAddress";
CUB FRA_EraseMailAddress[]				= "Erase Mail Address  ";
CUB FRA_PrintMailAddressMode[]			= "   Print MailAddress";
CUB FRA_PrintMailAddress[]				= "Print Mail Address  ";
CUB FRA_SetMailGroup[]					= "   Set Mail Group   ";
CUB FRA_MailGroupSetting[]				= "Mail Group          ";
CUB FRA_EraseMailGroupMode[]			= "   Erase Mail Group ";
CUB FRA_EraseMailGroup[]				= "Erase Mail Group    ";
CUB FRA_PrintMailGroupMode[]			= "   Print Mail Group ";
CUB FRA_PrintMailGroup[]				= "Print Mail Group    ";
CUB FRA_PressOnetouch[]					= "Press One-Touch     ";

/** サービスファンクション */
CUB FRA_InitEngineBoard[]				= "Initialize I-FAX    ";
CUB FRA_IP_EchoRequest[]				= "IP Packet Echo Req. ";
CUB FRA_INF_Complete[]					= " **   Complete   ** ";
CUB	FRA_SF_TTL_Test[]					= "TTL Test            "; /*1998/6/9 Eguchi*/

/** 設置オペレーション */
CUB FRA_INF_InitialError[]				= "I-FAX Initial Error ";

/** コマンド予約 */
CUB FRA_ReviewMailComMode[]				= "  Review Mail Com.  ";
CUB FRA_CancelMailCom[]					= "Cancel Mail Com.    ";
CUB FRA_PrintMailComMode[]				= "   Print Mail Com.  ";
CUB FRA_PrintMailCom[]					= "Print Mail Com.     ";
CUB FRA_PrintStoredMailMode[]			= "   Print Stored Mail";
CUB FRA_PrintStoredMail[]				= "Print Stored Mail   ";
CUB FRA_EnterMailCommandNo[]			= "Enter Command No.   ";

/** ジャーナルプリント */
CUB FRA_PrintMailJounalMode[]			= "   Print Mail Jrnl. ";
CUB FRA_PrintMailJournal[]				= "Print Mail Jrnl.    ";

/** 受信 */
CUB FRA_ManualReceiveMail[]				= "   Manual Rcv. Mail ";
CUB FRA_ReceiveMailMode[]				= "  Receive Mail      ";
CUB FRA_PrintReceiveMailMode[]			= "   Print Rcv. Mail  ";
CUB FRA_PrintReceiveMail[]				= "Print Rcv. Mail     ";

/** 動作中および終了表示 */
CUB FRA_INF_Abort[]						= " **  Terminate  **  ";
CUB FRA_INF_NoNewMail[]					= " **  No New Mail  **";
CUB FRA_SendingMail[]					= "Send Mail           ";
CUB FRA_ReceivingMail[]					= "Receive Mail        ";
CUB FRA_INF_Creating[]					= "** Creating Email **";
CUB FRA_INF_Dialing[]					= "   ** Dialing **    ";
CUB FRA_INF_Connecting[]				= "  ** Connecting **  ";
CUB FRA_INF_Sending[]					= "   ** Sending **    ";
CUB FRA_INF_Receiving[]					= "  ** Receiving **   ";
CUB FRA_INF_Checking[]					= "   ** Checking **   ";

CUB FRA_INF_PrintRcvReport[]			= "Print Rcv. Report   ";

/** PTTテスト信号送出サービスファンクション */
CUB FRA_PTT_TestMode[]					= "PTT Test Mode       ";
CUB FRA_PTT_Setting[]					= "PTT Test Setting    ";
CUB FRA_DataRate[]						= "    :Data Rate      ";
CUB FRA_SymbolRate[]					= "    :Symbol Rate    ";
CUB FRA_CarrierBias[]					= "    :Carrier Bias   ";
CUB FRA_SecondChannel[]					= "    :2nd Channel    ";
CUB FRA_UpperBandEdge[]					= "    :Upper Band Edge";
CUB FRA_CarrierBiasRange[]				= "[-100<-->100]       ";
CUB FRA_BandEdgeRange[]					= "[0-22(dB)]          ";
CUB FRA_INF_Mode[]						= "    :Mode           ";

/* PTTテスト信号種類 */
/*↓この順番で並べて記述*/
CUB FRA_DTMF_Tone0[]					= "%TT00               ";
CUB FRA_DTMF_Tone1[]					= "%TT01               ";
CUB FRA_DTMF_Tone2[]					= "%TT02               ";
CUB FRA_DTMF_Tone3[]					= "%TT03               ";
CUB FRA_DTMF_Tone4[]					= "%TT04               ";
CUB FRA_DTMF_Tone5[]					= "%TT05               ";
CUB FRA_DTMF_Tone6[]					= "%TT06               ";
CUB FRA_DTMF_Tone7[]					= "%TT07               ";
CUB FRA_DTMF_Tone8[]					= "%TT08               ";
CUB FRA_DTMF_Tone9[]					= "%TT09               ";
CUB FRA_DTMF_ToneAst[]					= "%TT0A               ";
CUB FRA_DTMF_ToneSharp[]				= "%TT0B               ";
CUB FRA_DTMF_ToneA[]					= "%TT0C               ";
CUB FRA_DTMF_ToneB[]					= "%TT0D               ";
CUB FRA_DTMF_ToneC[]					= "%TT0E               ";
CUB FRA_DTMF_ToneD[]					= "%TT0F               ";
CUB FRA_V21Ch1MkSymbol[]				= "%TT10               ";
CUB FRA_V21Ch2MkSymbol[]				= "%TT11               ";
CUB FRA_V23BwardChMkSymbol[]			= "%TT12               ";
CUB FRA_V23FwardChMkSymbol[]			= "%TT13               ";
CUB FRA_V22CallMk600bps[]				= "%TT14               ";
CUB FRA_V22CallMk1200bps[]				= "%TT15               ";
CUB FRA_V22bisCallMk2400bps[]			= "%TT16               ";
CUB FRA_V22AnswerSignal[]				= "%TT17               ";
CUB FRA_V22bisAnswerSignal[]			= "%TT18               ";
CUB FRA_V21Ch1SpSymbol[]				= "%TT19               ";
CUB FRA_V21Ch2SpSymbol[]				= "%TT1A               ";
CUB FRA_V23BwardChSpSymbol[]			= "%TT1B               ";
CUB FRA_V23FwardChSpSymbol[]			= "%TT1C               ";
CUB FRA_V32_9600bps[]					= "%TT20               ";
CUB FRA_V32bis14400bps[]				= "%TT21               ";
CUB FRA_V32TCM9600bps[]					= "%TT22               ";
CUB FRA_V32TCM14400bps[]				= "%TT23               ";
CUB FRA_V32bisTCM7200bps[]				= "%TT24               ";
CUB FRA_V32_4800bps[]					= "%TT25               ";
CUB FRA_OffFook[]						= "%TT30               ";
CUB FRA_V25AnswerTone[]					= "%TT31               ";
CUB FRA_1800HzGuardTone[]				= "%TT32               ";
CUB FRA_V25Send1300Hz[]					= "%TT33               ";
CUB FRA_FaxSend1100Hz[]					= "%TT34               ";
CUB FRA_BellAnswer2225hz[]				= "%TT35               ";
CUB FRA_V21Ch2[]						= "%TT40               ";
CUB FRA_V27ter2400bps[]					= "%TT41               ";
CUB FRA_V27ter4800bps[]					= "%TT42               ";
CUB FRA_V29_7200bps[]					= "%TT43               ";
CUB FRA_V29_9600bps[]					= "%TT44               ";
CUB FRA_V17_7200bpsL_Train[]			= "%TT45               ";
CUB FRA_V17_7200bpsS_Train[]			= "%TT46               ";
CUB FRA_V17_9600bpsL_Train[]			= "%TT47               ";
CUB FRA_V17_9600bpsS_Train[]			= "%TT48               ";
CUB FRA_V17_12000bpsL_Train[]			= "%TT49               ";
CUB FRA_V17_12000bpsS_Train[]			= "%TT4A               ";
CUB FRA_V17_14400bpsL_Train[]			= "%TT4B               ";
CUB FRA_V17_14400bpsS_Train[]			= "%TT4C               ";
CUB FRA_VFC_Modulation[]				= "%TT5\0               ";
CUB FRA_V34_Modulation[]				= "%TT6\0               ";
/*↑この順番で並べて記述*/

/* Gurad Tone */
/*↓この3個はこの順番で並べて記述*/
CUB FRA_GT1800hz[]						= "Guard Tone 1800 Hz  ";
CUB FRA_GT550hz[]						= "Guard Tone 550 Hz   ";
CUB FRA_NoGuardTone[]					= "No Guard Tone       ";

/* Mode */
/*↓この2個はこの順番で並べて記述*/
CUB FRA_OriginateMode[]					= "Originate Mode      ";
CUB FRA_AnswerMode[]					= "Answer Mode         ";

/* Data Rate */
/*↓この12個はこの順番で並べて記述*/
CUB FRA_2400bps[]						= "2400 bps            ";
CUB FRA_4800bps[]						= "4800 bps            ";
CUB FRA_7200bps[]						= "7200 bps            ";
CUB FRA_9600bps[]						= "9600 bps            ";
CUB FRA_12000bps[]						= "12000 bps           ";
CUB FRA_14400bps[]						= "14400 bps           ";
CUB FRA_16800bps[]						= "16800 bps           ";
CUB FRA_19200bps[]						= "19200 bps           ";
CUB FRA_21600bps[]						= "21600 bps           ";
CUB FRA_24000bps[]						= "24000 bps           ";
CUB FRA_26400bps[]						= "26400 bps           ";
CUB FRA_28800bps[]						= "28800 bps           ";
CUB FRA_31200bps[]						= "31200 bps           ";
CUB FRA_33600bps[]						= "33600 bps           ";


/* Symbol Rate */
/*↓この6つはこの順番で並べて記述*/
CUB FRA_2400baud[]						= "2400 baud           ";
CUB FRA_2800baud[]						= "2800 baud           ";
CUB FRA_3000baud[]						= "3000 baud           ";
CUB FRA_3200baud[]						= "3200 baud           ";
CUB FRA_3429baud[]						= "3429 baud           ";

/* Second Channel */
/*↓この2つはこの順番で並べて記述*/
CUB FRA_Disable[]						= "Disable             ";
CUB FRA_Enable[]						= "Enable              ";

/* Upper Band Edge */
/*↓この11個はこの順番で並べて記述*/
CUB FRA_V34BandEdge0Db[]				= "a = 0[dB]           ";
CUB FRA_V34BandEdge2Db[]				= "a = 2[dB]           ";
CUB FRA_V34BandEdge4Db[]				= "a = 4[dB]           ";
CUB FRA_V34BandEdge6Db[]				= "a = 6[dB]           ";
CUB FRA_V34BandEdge8Db[]				= "a = 8[dB]           ";
CUB FRA_V34BandEdge10Db[]				= "a = 10[dB]          ";
CUB FRA_V34BandEdgeG1Db[]				= "b=0.5[dB], c=1.0[dB]";
CUB FRA_V34BandEdgeG2Db[]				= "b=1.0[dB], c=2.0[dB]";
CUB FRA_V34BandEdgeG3Db[]				= "b=1.5[dB], c=3.0[dB]";
CUB FRA_V34BandEdgeG4Db[]				= "b=2.0[dB], c=4.0[dB]";
CUB FRA_V34BandEdgeG5Db[]				= "b=2.5[dB], c=5.0[dB]";
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	ＦＡＸワープ
 *----------------------------------*/
CUB	FRA_FaxWarpMode[]					= "  FAXﾜｰﾌﾟ           ";
CUB	FRA_EnterFaxWarpMode[]				= "   FAXﾜｰﾌﾟ ｾｯﾄ      ";
CUB	FRA_PrintFaxWarpMode[]				= "   FAXﾜｰﾌﾟ ﾘｽﾄ      ";
CUB	FRA_SetFaxWarpMode[]				= "   FAXﾜｰﾌﾟ ｾｯﾃｲ     ";
CUB	FRA_EnterFaxWarp[]					= "FAXﾜｰﾌﾟ ｾｯﾄ         ";
CUB	FRA_PrintFaxWarp[]					= "FAXﾜｰﾌﾟ ﾘｽﾄ         ";
CUB	FRA_SetFaxWarp[]					= "FAXﾜｰﾌﾟ:\0           ";
CUB	FRA_WarpSelectNumber[]				= "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ ";
CUB	FRA_WarpTime[]						= "ｼﾃｲ ｼﾞｺｸ            ";
CUB	FRA_WarpWeek[][21]					= {
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
CUB	FRA_SelectWarpRxDocPrint[][21]		= {
										  "   ﾄﾞｳｼﾞ ﾌﾟﾘﾝﾄ: OFF ",
										  "   ﾄﾞｳｼﾞ ﾌﾟﾘﾝﾄ: ON  ",
};

/* ＷＡＲＰ転送先ワーディング追加 By O.Kimoto 1999/02/08 */
CUB	FRA_WarpAltNumber[]					= "ﾃﾝｿｳ ﾊﾞﾝｺﾞｳ         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */

#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* By H.Fujimura 1999/01/07 */
/*----------------------------------*
 *	ナンバーディスプレイ
 *----------------------------------*/
CUB	FRA_NumberDisplayMode[]				= "  ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ     ";
CUB	FRA_EnterNumberDisplayMode[]		= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ｾｯﾄ";
CUB	FRA_PrintNumberDisplayMode[]		= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘｽﾄ";
CUB	FRA_SetNumberDisplayMode[]			= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲｾｯﾃｲ";
CUB	FRA_EnterNumberDisplay[]			= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ｾｯﾄ   ";
CUB	FRA_PrintNumberDisplay[]			= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘｽﾄ   ";
CUB	FRA_SetNumberDisplay[]				= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ:\0     ";
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* By H.Fujimura 1999/01/07 */
CUB	FRA_Set_ND_Warp[]					= "NDﾜｰﾌﾟ:\0            ";
 #endif
CUB	FRA_ND_SelectNumber[]				= "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ ";
CUB	FRA_ND_TelMode[][21]				= {
										  "ﾃﾞﾝﾜｷ ｾﾂｿﾞｸ:\0       ",
										  "             OFF    ",
/*										  "             PHONE1 ",*/
										  "             PHONE2 ",
};
CUB	FRA_ND_NoNotice[]					= "ﾋﾂｳﾁ                ";
CUB	FRA_ND_OutOfDisp[]					= "ﾋｮｳｼﾞ ｹﾝｶﾞｲ         ";
CUB	FRA_ND_PublicTel[]					= "ｺｳｼｭｳ ﾃﾞﾝﾜ          ";
CUB	FRA_ND_Parameter[]					= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾊﾟﾗﾒｰﾀ";
CUB	FRA_Print_ND_JournalMode[]			= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘﾚｷ";
CUB	FRA_Print_ND_Journal[]				= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘﾚｷ   ";
#endif

/*----------------------------------*
 *	通信確認
 *----------------------------------*/
CUB	FRA_ConfirmReport[]					= "R｢sult. comm   :\0   ";

/*----------------------------------*
 *	オペレーションプロテクト
 *----------------------------------*/
CUB	FRA_OperationProtected[]			= "Utilisation prot｢g｢e";

#if (PRO_COPY_FAX_MODE == ENABLE)
/*----------------------------------*
 *	コピーモード
 *----------------------------------*/
CUB	FRA_ChangeManual[]					= "      Plat \x7E Prog.  ";	/* \x7E = → */
#endif

#if (PRO_FBS == ENABLE)
/*----------------------------------*
 *	ブック送信
 *----------------------------------*/
CUB	FRA_SetBookTxDocumentSize[]			= "Prog.Format analyse ";
CUB	FRA_SetBookTxNextDocument[]			= "Prog.Doc.suivant    ";

CUB	FRA_NextBookDocScanStart[]			= "D｢butanal.\x7E DocSuiv.";	/* \x7E = → */
CUB	FRA_NextBookDocTxStart[]			= "Em.Anal.  \x7E Start   ";	/* \x7E = → */
CUB	FRA_NextBookDocScanEnd[]			= "Finanal.  \x7E Prog.   ";	/* \x7E = → */
#endif

/* 紙サイズ（R → 0x01(OPR_PAPER_SIZE_R)で定義して下さい） */
CUB	FRA_PaperSize_None[]				= "Sans\0";	/* ﾅｼ → Sans by K.Watanabe 1998/08/10 */
CUB	FRA_PaperSize_A5[]					= "A5\0  ";
CUB	FRA_PaperSize_Letter[]				= "Ltr\0 ";
#if defined(USAOKI)	/* 1998/02/04 Y.Matsukuma */
CUB	FRA_PaperSize_A4[]					= "LT\0  ";
#else
CUB	FRA_PaperSize_A4[]					= "A4\0  ";
#endif
CUB	FRA_PaperSize_Legal[]				= "Legl\0";
CUB	FRA_PaperSize_B5R[]					= "B5\x01\0 ";
CUB	FRA_PaperSize_B4[]					= "B4\0  ";
CUB	FRA_PaperSize_A3[]					= "A3\0  ";
CUB	FRA_PaperSize_A4R[]					= "A4\x01\0 ";
CUB	FRA_PaperSize_LetterR[]				= "Ltr\x01\0";
CUB	FRA_PaperSize_F4[]					= "F4\0  ";
CUB	FRA_PaperSize_A5R[]					= "A5\x01\0 ";
CUB	FRA_PaperSize_Postcard[]			= "Post\0";
CUB	FRA_PaperSize_LD[]					= "Ld\0  ";
CUB	FRA_PaperSize_GLetterR[]			= "GLtr\x01";
CUB	FRA_PaperSize_ExecutiveR[]			= "Exe\x01\0";
/*  #if (PRO_KEYPANEL == PANEL_POPLAR_B)  *//* modified by honda 1997/11/14 */
/*   #if defined(JPN)  */
/*  CUB	FRA_PaperSize_InvoiceR[]			= "Inv\x01\0";  */
/*   #else  */
CUB	FRA_PaperSize_HalfLetterR[]			= "HLtr\x01";  /* added by honda 1997/10/04 */
/*   #endif  */
/*  #else  */
/*  CUB	FRA_PaperSize_InvoiceR[]			= "Inv\x01\0";  */
/*  #endif  */
CUB	FRA_PaperSize_GLegal[]				= "GLegl";
CUB	FRA_PaperSize_GLetter[]				= "GLtr\0";
CUB	FRA_PaperSize_Card[]				= "Card\0";
CUB	FRA_PaperSize_Executive[]			= "Exe\0 ";
CUB	FRA_PaperSize_B5[]					= "B5\0  ";
CUB	FRA_PaperSize_C5[]					= "C5\0  ";
CUB	FRA_PaperSize_HalfLetter[]			= "HLtr\0";
CUB	FRA_PaperSize_Invoice[]				= "Inv\0 ";
CUB	FRA_PaperSize_B6[]					= "B6\0  ";
CUB	FRA_PaperSize_DL[]					= "DL\0  ";
CUB	FRA_PaperSize_CM10[]				= "CM10\0";
CUB	FRA_PaperSize_A6[]					= "A6\0  ";
CUB	FRA_PaperSize_Monarch[]				= "Mnc\0 ";
CUB	FRA_PaperSize_35[]					= "3x5\0 ";
CUB	FRA_PaperSize_User[]				= "User\0";
CUB	FRA_PaperSize_OHP[]					= "OHP\0 ";	/* このﾜｰﾃﾞｨﾝｸﾞは、SYS_DOC.Hの定義とは無関係です */
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)	/* By S.Fukui Jan.23,1998 */
CUB	FRA_PaperSize_Auto[]				= "Auto\0";	/* このﾜｰﾃﾞｨﾝｸﾞは、SYS_DOC.Hの定義とは無関係です */
#endif
#if (PRO_PITNEYBOWES == ENABLE)
CUB	FRA_PaperSize_Ledger[]				= "LDGR\0";	/* 原稿サイズ表示ＰＢ用 By S.Fukui Aug.25,1998 */
CUB	FRA_PaperSize_LtLg[]				= "LTLG\0";	/* 原稿サイズ表示ＰＢ用 (For Letter/Legal) By S.Fukui Aug.25,1998 */
#endif

/*----------------------------------*
 *	サービスファンクション
 *----------------------------------*/
/* マシンパラメータ */
CUB	FRA_SF_ParameterSet[]				= "Prog. Paramｪtres    ";
CUB	FRA_SF_ParameterClear[]				= "Eff. Paramｪtres     ";

/* メモリースイッチ */
CUB	FRA_SF_MemorySwitchSet[]			= "Prog. Interr. M｢mo. ";
CUB	FRA_SF_MemorySwitchClear[]			= "Eff. Interr. M｢moire";

/* ユーザ設定クリア */
CUB	FRA_SF_BackUpFileClear[]			= "Eff. Sauvegarde     ";

/* オールラムクリア */
CUB	FRA_SF_AllClear[]					= "Tout Effac｢         ";

/* 機種固有スイッチ */
CUB	FRA_SF_UniqSwitchSet[]				= "Prog. Switch unique ";
CUB	FRA_SF_UniqSwitchClear[]			= "Eff. Switch unique  ";

/* 保守用スイッチ */
CUB	FRA_SF_MaintenanceSet[]				= "Mode maintenance    ";
CUB	FRA_SF_MaintenanceClear[]			= "Eff. Mode mainten   ";

/* テストファンクション -> このワーディングの並びはかえてはいけない */
 #if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1997/10/02 Y.Matsukuma */
CUB	FRA_SF_LifeMonitor[]				= "Life Monitor        ";
CUB	FRA_SF_LifeMonitorClear[]			= "Eff. Life Monitor   ";
CUB	FRA_SF_TestPatternPrint[]			= "Test Imprimante     ";
CUB	FRA_SF_StampTest[]					= "Test Tampon         ";
CUB	FRA_SF_Shading[]					= "Prog.Fond.R｢f｢rence ";
 #elif (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ＨＩＮＯＫＩは原稿排出テストは有りません by O.Kimoto 1999/02/09 */
CUB	FRA_SF_LifeMonitor[]				= "Life Monitor        ";
CUB	FRA_SF_TestPatternPrint[]			= "Test Imprimante     ";
CUB	FRA_SF_StampTest[]					= "Test Tampon         ";
CUB	FRA_SF_Shading[]					= "Prog.Fond.R｢f｢rence ";
 #else
CUB	FRA_SF_LifeMonitor[]				= "Life Monitor        ";
CUB	FRA_SF_TestPatternPrint[]			= "Test Imprimante     ";
CUB	FRA_SF_StampTest[]					= "Test Tampon         ";
CUB	FRA_SF_DocumentFeedOutTest[]		= "Test Avance         ";
CUB	FRA_SF_Shading[]					= "Prog.Fond.R｢f｢rence ";
 #endif

/* ライフモニター */
CUB	FRA_SF_BoardNumber[]				= "Num Carte?          ";
CUB	FRA_SF_LifeReadingPage[]			= "Pages Analys｢es     ";
CUB	FRA_SF_LifePrintingPage[]			= "Pages Imprim｢es     ";
CUB	FRA_SF_LifeTxPage[]					= "Pages Emises        ";
CUB	FRA_SF_LifeDrumReplaceCount[]		= "Compt. Remp. Tambour";
CUB	FRA_SF_LifeDrumLifeCount[]			= "Vie du tambour      ";
CUB	FRA_SF_LifeTonerReplaceCount[]		= "Compt.Util.Toner    ";
CUB	FRA_SF_LifeTonerLifeCount[]			= "Vie Toner           ";
CUB	FRA_SF_LifeFuserReplaceCount[]		= "Compt.Fixateur      ";
CUB	FRA_SF_LifeFuserLifeCount[]			= "Vie Fixateur        ";
CUB	FRA_SF_LifeTransferReplaceCount[]	= "Compt.Transfert     ";
CUB	FRA_SF_LifeTransferLifeCount[]		= "Vie Transfert       ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/07 */
CUB	FRA_SF_CPU_Revision[]				= "CPU ﾊﾞｰｼﾞｮﾝ         ";
CUB	FRA_SF_ROM_Revision[]				= "ROM ﾊﾞｰｼﾞｮﾝ         ";
#endif

/* テストパターン */
CUB	FRA_SF_Pattern[]					= "R｢f｢rence         \0 ";

/* 工場ファンクション */
CUB	FRA_SF_FactoryFunction[]			= "Fonction Usine      ";

CUB	FRA_SF_LEDTest[]					= "Test LED            ";
CUB	FRA_SF_LCDTest[]					= "Test Afficheur      ";
CUB	FRA_SF_PanelTest[]					= "Test Clavier        ";

CUB	FRA_SF_SRAMCheck[]					= "Test SRAM           ";
CUB	FRA_SF_DRAMCheck[]					= "Test DRAM           ";
CUB	FRA_SF_RTCTest[]					= "Test RTC            ";
CUB	FRA_SF_RS232CTest[]					= "Test RS232C         ";
CUB	FRA_SF_CassetteCheck[]				= "Test Cassette       ";

/* キー */
/*このワーディングの順番はキーコードの順番に一致させなくてはならない */
CUB	FRA_SF_Receive[]					= "R｢ception           ";
CUB	FRA_SF_Hook[]						= "Numerotation Appel  ";
CUB	FRA_SF_Hold[]						= "Attente             ";
CUB	FRA_SF_Mode[]						= "Mode                ";
CUB	FRA_SF_Contrast[]					= "Contraste           ";
CUB	FRA_SF_Program[]					= ">                   ";
CUB	FRA_SF_CursorLeft[]					= "<                   ";
CUB	FRA_SF_Set[]						= "Prog.               ";
CUB	FRA_SF_DelayedCheck[]				= "Confirmation Comm.  ";
CUB	FRA_SF_Clear[]						= "Eff.                ";
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1997/08/20 Y.Matsukuma */
CUB	FRA_SF_DialMark[]					= "Carat. Num｢rot.     ";
#else
CUB	FRA_SF_Sort[]						= "Tri                 ";
#endif
CUB	FRA_SF_Broadcast[]					= "Diffusion           ";	/* 注）通信確認でも使用（このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです） */
CUB	FRA_SF_Special[]					= "Em. Sp｢ciale        ";
CUB	FRA_SF_Group[]						= "Groupe              ";
CUB	FRA_SF_Speed[]						= "Vitesse             ";
CUB	FRA_SF_MemoryTx[]					= "Emission M｢moire    ";
CUB	FRA_SF_Stop[]						= "Stop                ";
CUB	FRA_SF_Start[]						= "D｢but               ";
CUB	FRA_SF_Copy[]						= "Copie               ";	/* 注）ｺﾋﾟｰ表示でも使用 */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1997/08/20 Y.Matsukuma */
CUB	FRA_SF_Redial[]						= "Rappel              ";
CUB	FRA_SF_Stamp[]						= "Tampon              ";
CUB	FRA_SF_Mercury[]					= "pr｢fixe             ";  /* アンズＬも新ﾜｰﾃﾞｨﾝｸﾞ 1998/02/25 Y.Matsukuma */
CUB	FRA_SF_Flash[]						= "Flash               ";
#else
CUB	FRA_SF_PaperSelect[]				= "Choix Papier        ";
CUB	FRA_SF_Stamp[]						= "Tampon              ";
CUB	FRA_SF_Reduction[]					= "R｢duction           ";
CUB	FRA_SF_Magnification[]				= "Agrandissement      ";
#endif
CUB	FRA_SF_CopyFax[]					= "Copie/Fax           ";
CUB	FRA_SF_BookDocSize[]				= "Format Livre        ";
CUB	FRA_SF_CopyReset[]					= "Initial.Copie       ";
CUB	FRA_SF_Tone[]						= "Tonalit             ";  /* Tone bythonda1998/02/24 *//* 追加 97/11/29 T.Fukumoto */

/* 回線テスト */
CUB	FRA_SF_LineTest[]					= "Test Ligne          ";	/* 未使用 */

CUB	FRA_SF_PhoneTest[]					= "Test Ligne          ";
CUB	FRA_SF_TonalTest[]					= "Test Tonalite       ";
CUB	FRA_SF_DTMF_Test[]					= "Test DTMF           ";

/* リレー */
CUB	FRA_SF_RelayTest1[]					= " CML  H  L  S  DP   ";
CUB	FRA_SF_RelayTest2[]					= " C24                ";
#if (PRO_MODEM == R288F)	/* By H.Fujimura 1999/01/07 */
 #if defined (JPN)
CUB	FRA_SF_R288F_RelayTest1[]			= " CML  H     L   S   ";
CUB	FRA_SF_R288F_RelayTest2[]			= " C24  TONE  BZ  RI  ";
 #else	/* ＴＷＮ用 by H.Hirao 1999/02/02 */
CUB	FRA_SF_R288F_RelayTest1[]			= " CML  H     DP  S   ";
CUB	FRA_SF_R288F_RelayTest2[]			= " C24        BZ      ";
 #endif
#endif

/* トーナル */
CUB	FRA_SF_FSK[]						= "FSK";
CUB	FRA_SF_White[]						= "Blanc\0    ";
CUB	FRA_SF_Black[]						= "Noir\0     ";
CUB	FRA_SF_Pix[]						= "     BPS   B:N =    ";

/* ミラーキャリッジ輸送モードセット */
CUB	FRA_SF_MirrorCarrigeModeSet[]		= "Miroir bloqu    :\0  ";  /* Position Miroir bythonda1998/02/24 */

/* サービスレポート */
CUB	FRA_SF_ServicePrint[]				= "Rapport Service     ";

CUB	FRA_SF_DTMF[]						= "DTMF";
CUB	FRA_SF_DTMFRow[]					= "ROW";
CUB	FRA_SF_DTMFColum[]					= "COL";

/* カセットテスト */
CUB	FRA_SF_CassetteOpen[]				= "Cass.Ouverte.";
CUB	FRA_SF_NoPaper[]					= "Abs.Pap.";
CUB	FRA_SF_SideCoverOpen[]				= "Capot Lat.ouv. ";
CUB	FRA_SF_NoUnit[]						= "AbsUnit";

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ライフモニタークリア */
CUB	FRA_SF_LifeMonitorClear[]			= "Eff. Life Monitor   ";
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
/* ライフモニタクリアパスコード */
CUB	FRA_SF_ServiceCode[]				= "Entrer Code Serv.   ";  /* 要翻訳 thonda */
CUB	FRA_SF_EnterServiceCode[]			= "Prog. Code Service  ";  /* 要翻訳 thonda */
#endif

/* プリンタメンテナンス */
CUB	FRA_SF_ReplaceCountSet[]			= "Prog.Compteur Rempl.";
CUB	FRA_SF_ServiceCall[]				= "Appel de Service    ";
CUB	FRA_SF_FuserReplace[]				= "Rempl.le four       ";
CUB	FRA_SF_TransferReplace[]			= "Rempl.le transfert  ";
CUB	FRA_SF_ServiceCallCount[]			= "Appel de Service :  ";
CUB	FRA_SF_HeatTrouble[]				= "Erreur Chauff.      ";
CUB	FRA_SF_HeatDisconnection[]			= "D｢connex. Thermist. ";  /* Chauff.d｢branch bythonda1998/02/24 */
CUB	FRA_SF_HeatShortCircuit[]			= "Court-circuit Therm.";  /* Chauff.C.-circuit bythonda1998/02/24 */
CUB	FRA_SF_InsideFanTrouble[]			= "Err.Vent.Interne    ";
CUB	FRA_SF_RxMotorTrouble[]				= "Err.Mot.R｢ception   ";
CUB	FRA_SF_DrumTrouble[]				= "Err.Fix.Tambour     ";
CUB	FRA_SF_PsFanTrouble[]				= "Err.Vent.Alim.      ";
CUB	FRA_SF_HvFuseDisconnect[]			= "D｢conn.Fusible THT  ";

/* 消耗品発注機能 */
CUB	FRA_SF_ReceiverCustomerCode[]		= "Code Dist.          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* JPN */
CUB	FRA_SF_ReceiverCompany[]			= "Nom.Dist.           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	FRA_SF_SenderCustomerCode[]			= "Code Cli.           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	FRA_SF_SenderCompany[]				= "Nom.Cli.            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
CUB	FRA_SF_SenderSection[]				= "Adresse1            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* JPN以外は Address とする By S.Fukui Nov.15,1997 */
CUB	FRA_SF_SenderSection2[]				= "Adresse2            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* 60文字入力できるようにaddressを2段に分けます */
#else
CUB	FRA_SF_SenderSection[]				= "ｵｸﾘﾓﾄ ﾌﾞｶﾒｲ         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
#endif
CUB	FRA_SF_SenderTelNumber[]			= "T｢l｢ph.Client       ";
CUB	FRA_SF_SerialNumber[]				= "No S｢rie            ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	FRA_SF_Date[]						= "Date Installation   ";
CUB	FRA_SF_PrintOrderForm[]				= "Imp.Bon de Commande ";
#if defined(US1)
CUB	FRA_SF_ToCompanyFaxNumber[]			= "Dist. Fax No.       ";	/* orderbythonda1998/11/11 */
CUB	FRA_SF_ToCompanyTelNumber[]			= "Dist. Tel No.       ";	/* orderbythonda1998/11/11 */
#endif

/* メモリダンプ */
CUB	FRA_SF_MemoryDump[]					= "Ecras. M｢moire      ";
CUB	FRA_SF_MemoryDumpAddress[]			= "Adresse    :        ";
CUB	FRA_SF_MemoryDumpLength[]			= "Long. data :        ";

/* ＤＲＡＭクリア */
CUB	FRA_SF_ClearDRAM[]					= "Eff. DRAM           ";

/* オプションデータ初期化 */
CUB	FRA_SF_OptionDataInitial[]			= "Option Data Base    ";

/* 消耗品発注データクリア */
#if (PRO_PRINT_TYPE == THERMAL)	/* By H.Fujimura 1999/01/07 */
CUB	FRA_SF_MntDataClear[]				= "ｷｶｲ ﾊﾞﾝｺﾞｳ ｸﾘｱ      ";
#else
CUB	FRA_SF_OrderDataClear[]				= "Init. bon commande  ";  /* ﾊｯﾁｭｳﾃﾞｰﾀ ｸﾘｱ bythonda1998/02/24 */
#endif

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/20 */
/* T30モニター番号 */
CUB	FRA_SF_T30MonitorNumber[]			= "T30 No.:        \0   ";
#endif

CUB	FRA_SF_OK[]							= "OUI                 ";
CUB	FRA_SF_NG[]							= "NON\0                ";

/*----------------------------------*
 *	ＬＣＤ・リストでの頭文字表示
 *----------------------------------*/
#if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
CUB	FRA_HeadCharacter_Speed				= 'S';
CUB	FRA_HeadCharacter_Command			= 'C';
CUB	FRA_HeadCharacter_Batch				= 'B';
CUB	FRA_HeadCharacter_Polling			= 'P';
CUB	FRA_HeadCharacter_Tray				= 'T';
#endif

#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
/*----------------------------------*
 *	通信結果表示
 *----------------------------------*/
CUB	FRA_CommResultList[]				= "R｢sultat Communicat.";/*20*/
CUB	FRA_Tx[]							= "Tx\0                 ";/*2*/
CUB	FRA_Rx[]							= "Rx\0                 ";/*2*/
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC 設定表示 */
CUB FRA_RemoteTxSetting[]				= "ﾃﾝｿｳ     ";
CUB FRA_RemoteTxSettingOff[]			= "OFF";
#endif

#if defined(STOCKHM2)	/* Added by SMuratec C.P 20034/06/07 */
/*----------------------------------*
 *	ジャーナルプリント
 *----------------------------------*/
CUB FRA_JournalTx[]						= "[01] ｿｳｼﾝｷﾛｸ        ";
CUB FRA_JournalRx[]						= "[02] ｼﾞｭｼﾝｷﾛｸ       ";
CUB FRA_JournalTxRx[]					= "[03] ｿｳｼﾞｭｼﾝｷﾛｸ     ";
CUB	FRA_CommConfirm[]					= "ﾖﾔｸ ｶｸﾆﾝ            "; 
CUB FRA_FunctionEnter[]					= "               /ｾｯﾄ ";
CUB FRA_InkConfirm[]					= "ｲﾝｸﾘﾎﾞﾝ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ";

#endif

#if (PRO_RTC_RX5C338A == ENABLE)
CUB FRA_RTC_Init[]						= "RTCｲﾆｼｬﾗｲｽﾞ         ";
#endif

CUB	FRA_WordingTail[]					= "\0";	/* ﾜｰﾃﾞｨﾝｸﾞｻｲｽﾞ計算用(H8の様にﾜｰﾃﾞｨﾝｸﾞを縦に並べる場合必要) */

#undef	CUB
