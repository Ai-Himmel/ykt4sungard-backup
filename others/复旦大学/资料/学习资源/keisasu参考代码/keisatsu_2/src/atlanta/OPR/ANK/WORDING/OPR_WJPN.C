/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_WJPN.C
*	Author		: 渡辺一章
*	Date		: 1996/10/25
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 日本語版オペレーションワーディング
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"

#define	CUB		CONST UBYTE

#if (PRO_CPU == SH7043)	/* ワーディング先頭位置認識用 */
 #if (WORDING_1 == JAPANESE)
	CUB D2W_1stWordingTop[]				= "\0";
 #endif
 #if (WORDING_2 == JAPANESE)
	CUB D2W_2ndWordingTop[]				= "\0";
 #endif
 #if (WORDING_3 == JAPANESE)
	CUB D2W_3rdWordingTop[]				= "\0";
 #endif
#endif

CUB	JPN_WordingHead[]					= "\0";	/* ﾜｰﾃﾞｨﾝｸﾞｻｲｽﾞ計算用(H8の様にﾜｰﾃﾞｨﾝｸﾞを縦に並べる場合必要) */
CUB	JPN_Null[]							= "\0";

/* 待機モード */
CUB	JPN_TelReady[]						= "ﾃﾞﾝﾜ ﾀｲｷ            ";
CUB	JPN_FaxReady[]						= "ﾌｧｸｽ ﾀｲｷ            ";
CUB	JPN_FaxTelReady[]					= "ﾌｧｸｽ/ﾃﾞﾝﾜ ﾀｲｷ       ";
CUB	JPN_TelFaxReady[]					= "ﾃﾞﾝﾜ/ﾌｧｸｽ ﾀｲｷ       ";
CUB	JPN_AnsFaxReady[]					= "ﾙｽ/ﾌｧｸｽ ﾀｲｷ         ";
CUB	JPN_DialInReady[]					= "ﾀﾞｲﾔﾙｲﾝ ﾀｲｷ         ";	/* (JPN) */
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1997/12/26 */
CUB	JPN_ScannerTransportReady[]			= "ﾐﾗｰｷｬﾘｯｼﾞ ﾕｿｳﾓｰﾄﾞ   ";
#endif

/* コピーモードの表示 */
#if (PRO_COPY_FAX_MODE == ENABLE)
CUB	JPN_CopyReady[]						= "ｺﾋﾟｰ ﾃﾞｷﾏｽ   ﾌﾞｽｳ:  ";
CUB	JPN_ManualCopyReady[]				= "ｺﾋﾟｰ ﾃｻﾞｼ    ﾌﾞｽｳ:  ";
CUB	JPN_CopyImpossibleReady[]			= "             ﾌﾞｽｳ:  ";
CUB	JPN_InputCopyMagnifi[]				= "ﾊﾞｲﾘﾂ ﾆｭｳﾘｮｸ(50-200)";
CUB	JPN_CopyMagnifiError[]				= "50-200% ｦ ﾄﾞｳｿﾞ     ";
CUB	JPN_ConfirmCopyMagnifi[]			= "999% ﾃﾞ ｺﾋﾟｰ ｼﾏｽｶ?  ";	/* 倍率は必ず999を定義（国別の表示位置対応） */
#endif

/* コマンド登録中の表示（上段） */
CUB	JPN_EnterFaxNumber[]				= "ｱｲﾃｻｷ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ";
CUB	JPN_InputGroupNumber[]				= "ｸﾞﾙｰﾌﾟﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ";
CUB	JPN_InputSpeedDialNumber[]			= "ﾀﾝｼｭｸ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ";
CUB	JPN_PressStart[]					= "ｽﾀｰﾄｷｰ ｦ ﾄﾞｳｿﾞ      ";
CUB	JPN_PressStartAgain[]				= "ｽﾀｰﾄｷｰ ｦ ﾓｳｲﾁﾄﾞ     ";
CUB	JPN_PressEnterKey[]					= "ｾｯﾄｷｰ ｦ ﾄﾞｳｿﾞ       ";

/* コピー部数入力中の表示（上段） */
CUB	JPN_SetCopyUnits[]					= "ｺﾋﾟｰﾌﾞｽｳ ｦ ﾄﾞｳｿﾞ    ";	/* POPLAR_B以外 */

/* 選択を促す表示（点滅する表示 ) */
CUB	JPN_ProgramEnter[]					= "            ｷﾉｳ/ｾｯﾄ ";
CUB	JPN_ProgramClear[]					= "            ｷﾉｳ/ｸﾘｱ ";
#if (PRO_CIPHER == ENABLE)
CUB	JPN_EnterClesr[]					= "            ｾｯﾄ/ｸﾘｱ ";
#endif
CUB	JPN_EnterStop[]						= "          ｾｯﾄ/ｽﾄｯﾌﾟ ";
CUB	JPN_CopyStop[]						= "         ｺﾋﾟｰ/ｽﾄｯﾌﾟ ";	/* POPLAR_B以外 */
CUB	JPN_StartStop[]						= "         ｽﾀｰﾄ/ｽﾄｯﾌﾟ ";
CUB	JPN_SpecialCommunicationEnter[]		= "       ｵｳﾖｳﾂｳｼﾝ/ｾｯﾄ ";
 #if defined(KEISATSU) /* ID49 O.Oshima 2005/12/02 */
CUB	JPN_ReviewStop[]					= "         ｶｸﾆﾝ/ｽﾄｯﾌﾟ ";
 #else
CUB	JPN_ReviewStop[]					= "     ﾂｳｼﾝｶｸﾆﾝ/ｽﾄｯﾌﾟ ";
 #endif
CUB	JPN_CheckProgramEnter[]				= "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ ";
CUB	JPN_CheckProgramClear[]				= "ｶｸﾆﾝ        ｷﾉｳ/ｸﾘｱ ";
CUB	JPN_CheckStartStop[]				= "ｶｸﾆﾝ     ｽﾀｰﾄ/ｽﾄｯﾌﾟ ";
#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
 #if defined(KEISATSU) /* ID49 O.Oshima 2005/12/02 */
CUB	JPN_CommunicationConfirmEnter[]		= "           ｶｸﾆﾝ/ｾｯﾄ ";/*20*/
 #else
CUB	JPN_CommunicationConfirmEnter[]		= "       ﾂｳｼﾝｶｸﾆﾝ/ｾｯﾄ ";/*20*/
 #endif
#endif

/*----------------------------------*
 *	応用機能
 *----------------------------------*/
/* 機能選択中 */
CUB	JPN_SetDelayedTransmission[]		= "  ｼﾞｺｸｼﾃｲ ﾂｳｼﾝ      ";
CUB	JPN_SetSecureTransmission[]			= "  ｼﾝﾃﾝ ｿｳｼﾝ         ";
CUB	JPN_SetRelayTransmission[]			= "  ﾁｭｳｹｲｼｼﾞ ｿｳｼﾝ     ";
CUB	JPN_SetPolling[]					= "  ﾎﾟｰﾘﾝｸﾞ           ";
CUB	JPN_SetBatchTransmission[]			= "  ｲｯｶﾂ ｿｳｼﾝ         ";
CUB	JPN_SetContPolling[]				= "  ﾚﾝｿﾞｸ ﾎﾟｰﾘﾝｸﾞ     ";
CUB	JPN_SetFcodeTransmission[]			= "  Fｺｰﾄﾞ ｿｳｼﾝ        ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */
CUB	JPN_SetFcodePolling[]				= "  Fｺｰﾄﾞ ﾎﾟｰﾘﾝｸﾞ     ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */
CUB	JPN_SetCipherTransmission[]			= "  ｽｸﾗﾝﾌﾞﾙ ｿｳｼﾝ      ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大17ﾊﾞｲﾄ(3ﾊﾞｲﾄ目から数えて)です（機種により不定） */

/* 各機能の詳細データ設定中（上段） */
CUB	JPN_DelayedTransmission[]			= "ｼﾞｺｸｼﾃｲ ﾂｳｼﾝ        ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	JPN_SecureTransmission[]			= "ｼﾝﾃﾝ ｿｳｼﾝ           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	JPN_RelayTransmission[]				= "ﾁｭｳｹｲｼｼﾞ ｿｳｼﾝ       ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	JPN_PollingCommunication[]			= "ﾎﾟｰﾘﾝｸﾞ             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	JPN_BatchTransmission[]				= "ｲｯｶﾂ ｿｳｼﾝ           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16(ﾎﾟﾌﾟﾗは17)ﾊﾞｲﾄです（機種により不定） */
CUB	JPN_ContinuousPolling[]				= "ﾚﾝｿﾞｸ ﾎﾟｰﾘﾝｸﾞ       ";
CUB	JPN_InputSubAddressNumber[]			= "ｻﾌﾞｱﾄﾞﾚｽ ｦ ﾄﾞｳｿﾞ    ";
CUB	JPN_InputPasswordNumber[]			= "ﾊﾟｽﾜｰﾄﾞ ｦ ﾄﾞｳｿﾞ     ";
CUB	JPN_SelectCipherExtensionKey[]		= "ﾀﾞﾌﾞﾙｶﾞｰﾄﾞ     :\0   ";

/* 各機能の詳細データ設定中（下段） */
CUB	JPN_EnterDelayedTxTime[]			= "ｼﾞｺｸｦ ﾄﾞｳｿﾞ \0       ";
CUB	JPN_InputMailBoxNumber[]			= "ｼﾝﾃﾝ ﾊﾞﾝｺﾞｳ:      \0 ";
CUB	JPN_RelayTxGroupNumber[]			= "ｸﾞﾙｰﾌﾟ ﾊﾞﾝｺﾞｳ:\0     ";
CUB	JPN_InputFileNumber[]				= "ﾌｧｲﾙ ﾊﾞﾝｺﾞｳ:\0       ";
CUB	JPN_BatchBoxIndexNumber[]			= "ﾎﾞｯｸｽ:    ﾌｧｲﾙ:     ";
CUB	JPN_EnterContPollStartTime[]		= "ｶｲｼ ｼﾞｶﾝ:     \0     ";
CUB	JPN_EnterContPollEndTime[]			= "ｼｭｳﾘｮｳ ｼﾞｶﾝ:  \0     ";

/*----------------------------------*
 *	濃度設定
 *----------------------------------*/
CUB	JPN_SetPaperContrast[]				= "ﾖﾐﾄﾘ ﾉｳﾄﾞ ｾｯﾄ       ";
CUB	JPN_ContrastLightDark[]				= "   ｳｽｸ         ｺｸ   ";

/*----------------------------------*
 *	機器エラー
 *----------------------------------*/
/* カバー */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)/* O.Oshima 2003/10/02 */
CUB	JPN_PleaseCloseScannerCover[]		= "ﾄｯﾌﾟｶﾊﾞｰｦ ﾄｼﾞﾃｸﾀﾞｻｲ ";
#else /*  (PRO_KEYPANEL == PANEL_STOCKHM2) DVT : mod by SMuratec C.P 2004/09/07 */
CUB	JPN_PleaseCloseScannerCover[]		= "ｹﾞﾝｺｳｶﾊﾞｰｦ ﾄｼﾞﾃｸﾀﾞｻｲ";
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	JPN_PleaseClose1stJamCover[]		= "ｻｲﾄﾞｶﾊﾞｰ1ｦ ﾄｼﾞﾃｸﾀﾞｻｲ";
CUB	JPN_PleaseClose2ndJamCover[]		= "ｻｲﾄﾞｶﾊﾞｰ2ｦ ﾄｼﾞﾃｸﾀﾞｻｲ";
CUB	JPN_PleaseClose3rdJamCover[]		= "ｻｲﾄﾞｶﾊﾞｰ3ｦ ﾄｼﾞﾃｸﾀﾞｻｲ";
CUB	JPN_PleaseOpen1stJamCover[]			= "ｻｲﾄﾞｶﾊﾞｰ1 ｦ ｱｹﾃ     ";
CUB	JPN_PleaseOpen2ndJamCover[]			= "ｻｲﾄﾞｶﾊﾞｰ2 ｦ ｱｹﾃ     ";
CUB	JPN_PleaseOpen3rdJamCover[]			= "ｻｲﾄﾞｶﾊﾞｰ3 ｦ ｱｹﾃ     ";
CUB	JPN_PleaseOpenTopCover[]			= "ﾄｯﾌﾟｶﾊﾞｰ ｦ ｱｹﾃ      ";
 #if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1998/01/28 */
CUB	JPN_PleaseOpenPrinterCover[]		= "ﾌﾟﾘﾝﾀｶﾊﾞｰ ｦ ｱｹﾃ     ";
 #endif
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) /* O.Oshima 2003/10/02 */
CUB	JPN_PleaseOpenCloseScanCover[]		= "ﾄｯﾌﾟｶﾊﾞｰ ｦ ｶｲﾍｲｼﾃ   ";
 #elif (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	JPN_PleaseOpenCloseScanCover[]		= "ﾊﾟﾈﾙ ﾐｷﾞ ﾖｺ ﾉ ﾚﾊﾞｰﾃﾞ";
 #else /* (PRO_KEYPANEL == PANEL_STOCKHM2) mod by SMuatec C.P 2004/09/07 */
CUB	JPN_PleaseOpenCloseScanCover[]		= "ｹﾞﾝｺｳｶﾊﾞｰ ｦ ｶｲﾍｲｼﾃ  ";
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
CUB	JPN_PleaseClosePrinterCover[]		= "ﾌﾟﾘﾝﾀｶﾊﾞｰｦ ﾄｼﾞﾃｸﾀﾞｻｲ";
#endif
#if (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	JPN_ScannerFeedErrorLow[]			= "ｶｲﾍｲｼ ｹﾞﾝｺｳ ｻｲｾｯﾄ   ";
#endif

/* カセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	JPN_PleaseCloseLowerCassette[]		= "ｶｾｯﾄ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ    ";
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	JPN_PleaseClose1stCassette[]		= "ｶｾｯﾄ1 ｦ ﾄｼﾞﾃｸﾀﾞｻｲ   ";
CUB	JPN_PleaseClose2ndCassette[]		= "ｶｾｯﾄ2 ｦ ﾄｼﾞﾃｸﾀﾞｻｲ   ";
CUB	JPN_PleaseClose3rdCassette[]		= "ｶｾｯﾄ3 ｦ ﾄｼﾞﾃｸﾀﾞｻｲ   ";
#endif

/* 記録紙 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)
CUB	JPN_ReplaceRxPaper[]				= "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ ";
CUB	JPN_NoSamePaper[]					= "ｼﾃｲﾖｳｼ ｶﾞ ｱﾘﾏｾﾝ     ";	/* 日本以外は、???_ReplaceRxPaperと同じです by K.Watanabe 1998/02/23 */
#endif

#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Modify by SMuratec 夏 2004/8/26 */
CUB	JPN_ReplaceRxPaper[]				= "ｷﾛｸｼ ｦ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ ";
CUB	JPN_NoSamePaper[]					= "ｼﾃｲﾖｳｼ ｶﾞ ｱﾘﾏｾﾝ     ";	/* 日本以外は、???_ReplaceRxPaperと同じです by K.Watanabe 1998/02/23 */
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	JPN_ReplaceRxPaper[]				= "ｷﾛｸｼ ｦ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ ";
CUB	JPN_ReplaceUpperRxPaper[]			= "ﾄﾚｲ ﾉ ｷﾛｸｼ ｶﾞ ｱﾘﾏｾﾝ ";
CUB	JPN_ReplaceLowerRxPaper[]			= "ｶｾｯﾄ ﾉ ｷﾛｸｼ ｶﾞ ｱﾘﾏｾﾝ";
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
CUB	JPN_Cassette1[]						= "ｶｾｯﾄ1               ";
CUB	JPN_Cassette2[]						= "ｶｾｯﾄ2               ";
CUB	JPN_Cassette3[]						= "ｶｾｯﾄ3               ";
CUB	JPN_ManualCassette[]				= "ﾃｻﾞｼ:\0  ";
#endif
CUB	JPN_RemoveManualPaper[]				= "ﾃｻﾞｼﾖｳｼ ｦ ﾄﾘﾉｿﾞｲﾃ   ";
CUB	JPN_CheckPaperSize[]				= "ｷﾛｸｼｻｲｽﾞ ｦ ｶｸﾆﾝｼﾃ   ";
CUB	JPN_PleaseOpenCloseTopCover[]		= "ﾄｯﾌﾟｶﾊﾞｰ ｦ ｶｲﾍｲｸﾀﾞｻｲ";
#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1998/01/28 */
CUB	JPN_PleaseOpenClosePrinterCover[]	= "ﾌﾟﾘﾝﾀｶﾊﾞｰｦ ｶｲﾍｲｸﾀﾞｻｲ";
#endif

/* プリンター */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ジャム時の表示内容を変更します。By H.Fujimura 1999/03/09 */
CUB	JPN_PleaseRemovePaper[]				= "ｷﾛｸｼ ｦ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ ";
#else
CUB	JPN_PleaseRemovePaper[]				= "ｷﾛｸｼ ｦ ﾄﾘﾉｿﾞｲﾃｸﾀﾞｻｲ ";
#endif
CUB	JPN_PleaseSupplyToner[]				= "ﾄﾅｰ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ  ";
CUB	JPN_PleaseReplaceToner[]			= "ﾄﾅｰ ｦ ｺｳｶﾝ ｼﾃｸﾀﾞｻｲ  ";
CUB	JPN_PleaseCallService[]				= "ﾃﾝｹﾝ ｦ ｵｳｹｸﾀﾞｻｲ     ";
CUB	JPN_PaperSizeError[]				= "ｷﾛｸｼﾉ ｻｲｽﾞ ｶﾞ ﾁｶﾞｲﾏｽ";	/* ANZUのみ */

CUB	JPN_CheckDrumLife[]					= "ﾄﾞﾗﾑ ｼﾞｭﾝﾋﾞ ｼﾃｸﾀﾞｻｲ ";
CUB	JPN_ReplaceDrum[]					= "ﾄﾞﾗﾑ ｦ ｺｳｶﾝ ｼﾃｸﾀﾞｻｲ ";
CUB	JPN_CheckDrum[]						= "ﾄﾞﾗﾑ ｶﾞ ｱﾘﾏｾﾝ       ";
CUB	JPN_CheckTonerLevel[]				= "ﾄﾅｰ ｶﾞ ﾉｺﾘﾜｽﾞｶﾃﾞｽ   ";
CUB	JPN_NoToner[]						= "ﾄﾅｰｶｰﾄﾘｯｼﾞ ｶﾞ ｱﾘﾏｾﾝ ";

/* スキャナ */
CUB	JPN_CallForService[]				= "ﾗﾝﾌﾟ ｶｸﾆﾝ           ";
CUB	JPN_CheckDocument[]					= "ﾏｲｽｳ ｦ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ ";
CUB	JPN_MirrorCarrigeError[]			= "ﾐﾗｰｷｬﾘｯｼﾞ ｴﾗｰ       ";

/* ジャムリカバー */
CUB	JPN_DocumentJam[]					= "ｹﾞﾝｺｳｶﾞ ﾂﾏﾘﾏｼﾀ      ";
CUB	JPN_InterruptDocScan[]				= "ﾖﾐﾄﾘｶﾞ ﾁｭｳﾀﾞﾝ ｻﾚﾏｼﾀ ";
CUB	JPN_NextScanEnterClear[]			= "ﾂﾂﾞｷﾉ ﾖﾐﾄﾘ  ｾｯﾄ/ｸﾘｱ ";
CUB	JPN_ResetPageNumber[]				= "  ﾍﾟｰｼﾞｶﾗ ｾｯﾄｼﾅｵｼﾃ  ";
CUB	JPN_ResetDocumentSet[]				= "ｹﾞﾝｺｳﾉ ｾｯﾄｦ ﾔﾘﾅｵｼﾃ  ";
CUB	JPN_PleasePressStartKey[]			= "ｽﾀｰﾄｷｰ ｦ ｵｼﾃｸﾀﾞｻｲ   ";
CUB	JPN_PleasePressEnterKey[]			= "ｾｯﾄｷｰ ｦ ｵｼﾃｸﾀﾞｻｲ    ";
CUB	JPN_PleasePressCopyKey[]			= "ｺﾋﾟｰｷｰ ｦ ｵｼﾃｸﾀﾞｻｲ   ";	/* POPLAR_B以外 */

/* 通信 */
CUB	JPN_CommunicationError[]			= "ﾂｳｼﾝ ｴﾗｰ            ";
CUB	JPN_NoStoredDialInNumber[]			= "ﾀﾞｲﾔﾙｲﾝ ｾｯﾄ ｻﾚﾃｲﾏｾﾝ ";	/* (JPN) */

/* ハングアップ */
CUB	JPN_HungUpPhone[]					= "ｼﾞｭﾜｷ ｶﾞ ｱｶﾞｯﾃｲﾏｽ   ";

/* 完了表示 */
CUB	JPN_TransmitComplete[]				= " **  ｿｳｼﾝ ｶﾝﾘｮｳ  ** ";
CUB	JPN_ReceiveComplete[]				= " **  ｼﾞｭｼﾝｶﾝﾘｮｳ  ** ";
CUB	JPN_PrintComplete[]					= " **  ﾌﾟﾘﾝﾄｶﾝﾘｮｳ  ** ";
CUB	JPN_StoreComplete[]					= " **  ﾖﾐﾄﾘ ｶﾝﾘｮｳ  ** ";
CUB	JPN_SetComplete[]					= " **  ｾｯﾄ ｶﾝﾘｮｳ  **  ";
CUB	JPN_ClearComplete[]					= " **  ｸﾘｱ ｶﾝﾘｮｳ  **  ";

/* リモート診断中の表示 */
CUB	JPN_RemoteDiagMode[]				= "ｻｰﾋﾞｽﾓｰﾄﾞ           ";

/* 操作エラー */
/* 絶対に途中に追加してはいかん */
CUB	JPN_InvalidNumber[]					= "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ";	/* INVALID_NUMBER_ERROR				*/
CUB	JPN_TooManyDigitsin[]				= "ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      ";	/* TOO_MANY_DIGITS_ERROR			*/
CUB	JPN_PleaseInput1_99[]				= "1-99 ｦ ﾄﾞｳｿﾞ        ";	/* INVALID_COPY_NUMBER_ERROR		*//* POPLAR_B以外 */
CUB	JPN_NoNumberStored[]				= "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         ";	/* NO_STORED_NUMBER_ERROR			*//* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	JPN_PleaseInput0_32[]				= "0-32 ｦ ﾄﾞｳｿﾞ        ";	/* INVALID_GROUP_NUMBER_ERROR		*/
CUB	JPN_TooManyLocations[]				= "ﾊﾞﾝｺﾞｳ 10ｶｼｮ ｲﾅｲ    ";	/* TOO_MANY_LOCATION_ERROR			*/
CUB	JPN_InsertDocument[]				= "ｹﾞﾝｺｳ ｦ ｾｯﾄ ｼﾃｸﾀﾞｻｲ ";	/* INSERT_DOCUMENT_ERROR			*/
CUB	JPN_FeederInUse[]					= "ｹﾞﾝｺｳ ｶﾞ ｾｯﾄ ｻﾚﾃｲﾏｽ ";	/* FEEDER_IN_USE_ERROR				*/
CUB	JPN_ScannerInUse[]					= "ｹﾞﾝｺｳ ﾖﾐﾄﾘﾁｭｳ ﾃﾞｽ   ";	/* SCANNER_USE_ERROR				*/
CUB	JPN_PollingInUse[]					= "ｹﾞﾝｺｳ ｶﾞ ｾｯﾄ ｽﾞﾐ ﾃﾞｽ";	/* ALREADY_POLLING_STORED_ERROR		*/
CUB	JPN_NoDocumentStored[]				= "ｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｾﾝ      ";	/* NO_STORED_DOCUMENT_ERROR			*/
CUB	JPN_CommandFull[]					= "ﾂｳｼﾝ ﾃﾞｷﾏｾﾝ         ";	/* COMMAND_FULL_ERROR				*/
CUB	JPN_NoCommand[]						= "ﾂｳｼﾝﾏﾁ ｱﾘﾏｾﾝ        ";	/* NO_COMMAND_ERROR					*/
CUB	JPN_NoCommandDocument[]				= "ﾖﾔｸｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｾﾝ   ";	/* NO_COMMAND_DOCUMENT_ERROR		*/
CUB	JPN_NoCommandResult[]				= "ﾂｳｼﾝｹｯｶ ｱﾘﾏｾﾝ       ";	/* NO_COMMAND_RESULT_ERROR			*/
CUB	JPN_SecureDocExist[]				= "ｹﾞﾝｺｳ ｶﾞ ﾁｸｾｷｻﾚﾃｲﾏｽ ";	/* SECURE_DOC_EXIST_ERROR			*/
CUB	JPN_PrinterInUse[]					= "ﾌﾟﾘﾝﾄﾁｭｳ ﾃﾞｽ        ";	/* PRINTER_IN_USE_ERROR				*/
CUB	JPN_InvalidIDCode[]					= "ﾊﾞﾝｺﾞｳ ｶﾞ ﾁｶﾞｲﾏｽ    ";	/* INVALID_ID_CODE_ERROR			*/
CUB	JPN_InvalidProtectPasscode[]		= "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ";	/* INVALID_PROTECT_PASSCODE_ERROR	*/
CUB	JPN_NoProtectPasscode[]				= "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ﾐﾄｳﾛｸﾃﾞｽ ";	/* NO_PROTECT_PASSCODE_ERROR		*/
CUB	JPN_InputRangeOver[]				= "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ";	/* INPUT_RANGE_OVER_ERROR			*/
CUB	JPN_BatchDocFull[]					= "                    ";	/* BATCH_DOCUMENT_FULL_ERROR		*/
CUB	JPN_LineBusy[]						= "ﾂｳｼﾝﾁｭｳ ﾃﾞｽ         ";	/* LINE_BUSY_ERROR					*/
CUB	JPN_ProtectedDocStored[]			= "ｼﾞｭｼﾝ ｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｽ ";	/* PROTECT_DOCUMENT_STORED_ERROR	*/
CUB	JPN_NoProtectDocStored[]			= "ｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｾﾝ      ";	/* NO_PROTECT_DOCUMENT_ERROR		*/
CUB	JPN_NoPinNumber[]					= "PIN ﾊﾞﾝｺﾞｳ ｶﾞ ｱﾘﾏｾﾝ ";	/* NO_PIN_NUMBER_ERROR				*/
CUB	JPN_NoDepartmentCode[]				= "ﾌﾞﾓﾝｺｰﾄﾞ ｶﾞ ﾐﾄｳﾛｸﾃﾞｽ";	/* NO_DEPARTMENTCODE_ERROR			*/
CUB	JPN_BatchDocStored[]				= "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        ";	/* BATCH_DOCUMENT_STORED_ERROR		*/
CUB	JPN_ResetDocument[]					= "ｹﾞﾝｺｳｾｯﾄ ﾔﾘﾅｵｼﾃｸﾀﾞｻｲ";	/* RESET_DOCUMENT_ERROR				*/
CUB	JPN_PleaseCloseBookCover[]			= "ﾌﾞｯｸｶﾊﾞｰ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ";	/* BOOK_COVER_OPEN_ERROR			*//* POPLAR_Bのみ */
CUB	JPN_PleaseWaitAMinute[]				= "ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ      ";	/* PRINTER_CLEANING_ERROR			*/
CUB	JPN_NotStoredDocument[]				= "ﾁｸｾｷ ﾃﾞｷﾏｾﾝ         ";	/* NOT_STORED_DOCUMENT_ERROR		*//* (PRO_F_CODE == ENABLE) */
CUB	JPN_BoxInUse[]						= "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        ";	/* BOX_IN_USE_ERROR					*//* (PRO_F_CODE == ENABLE) */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* O.Oshima 2003/11/07 */
CUB	JPN_TooManyDirectDial[]				= "ﾁｮｸｾﾂﾀﾞｲﾔﾙ 10ｶｼｮ ｲﾅｲ";	/* TOO_MANY_DIRECT_DIAL_ERROR		*//* <-20 製品仕様書見落とし。O.Oshima 2003/11/07 */
#else
CUB	JPN_TooManyDirectDial[]				= "ﾁｮｸｾﾂﾀﾞｲﾔﾙ 20ｶｼｮ ｲﾅｲ";	/* TOO_MANY_DIRECT_DIAL_ERROR		*//* <-20 製品仕様書見落とし。O.Oshima 2003/11/07 */
#endif
CUB	JPN_SettingSecureBox[]				= "ｼﾝﾃﾝﾎﾞｯｸｽ ﾃﾞｽ       ";	/* SETTING_SECURE_BOX_ERROR			*//* (PRO_F_CODE == ENABLE) */
CUB	JPN_BookSizeNoSet[]					= "ｻｲｽﾞ ｦ ｾｯﾃｲ ｼﾃｸﾀﾞｻｲ ";	/* BOOK_SIZE_NO_SET_ERROR			*//* POPLAR_Bのみ */
CUB	JPN_NotCompleteStoredDoc[]			= "ﾁｸｾｷ ｶﾝﾘｮｳ ｼﾃｲﾏｾﾝ   ";	/* NOT_COMPLETE_STORED_ERROR		*//* POPLAR_Bのみ */
CUB	JPN_NotCompleteCopy[]				= "ｺﾋﾟｰ ｶﾝﾘｮｳ ｼﾃｲﾏｾﾝ   ";	/* NOT_COMPLETE_COPY_ERROR			*//* POPLAR_Bのみ */
CUB	JPN_ScanPreparing[]					= "ﾖﾐﾄﾘ ｼﾞｭﾝﾋﾞﾁｭｳ ﾃﾞｽ  ";	/* SCAN_PREPARING_ERROR				*//* POPLAR_Bのみ */
CUB	JPN_CopyProtect[]					= "ｺﾋﾟｰｷﾝｼ ﾁｭｳﾃﾞｽ      ";	/* COPY_PROTECT_ERROR				*/
CUB	JPN_NotScanDocSize[]				= "ｹﾞﾝｺｳ ｻｲｽﾞ ｶｸﾆﾝ     ";	/* NOT_SCAN_DOC_SIZE_ERROR			*//* (PRO_CIPHER == ENABLE) */
CUB	JPN_ShortFigure[]					= "4ｹﾀ ｲｼﾞｮｳ ﾋﾂﾖｳ      ";	/* SHORT_FIGURE_ERROR				*//* (PRO_CIPHER == ENABLE) */
CUB	JPN_AlreadyStored[]					= "ﾊﾞﾝｺﾞｳ ｶﾞ ﾄｳﾛｸｻﾚﾃｲﾏｽ";	/* ALREADY_NUMBER_STORED_ERROR		*//* (FRA) */
CUB	JPN_NotEntry[]						= "ﾄｳﾛｸ ｻﾚﾃｲﾏｾﾝ        ";	/* NOT_ENTRY_ERROR					*//* (PRO_CIPHER == ENABLE) */
CUB	JPN_NoScanCipherMode[]				= "ﾁｮｳｺｳｶﾞｼﾂ ﾊ ﾑｺｳ ﾃﾞｽ ";	/* NO_SCAN_CIPHER_MODE_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	JPN_Ciphering[]						= "ｽｸﾗﾝﾌﾞﾙ ﾁｭｳﾃﾞｽ      ";	/* CIPHERING_ERROR					*//* (PRO_CIPHER == ENABLE) */
CUB	JPN_Deciphering[]					= "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ﾁｭｳﾃﾞｽ";	/* DECIPHERING_ERROR				*//* (PRO_CIPHER == ENABLE) */
CUB	JPN_UseDefaultCipherKey[]			= "ﾃﾞﾌｫﾙﾄ ﾃﾞ ｼﾖｳ ｻﾚﾃｲﾏｽ";	/* USE_DEFAULT_CIPHER_KEY_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	JPN_UseProgramOneTouch[]			= "ﾌﾟﾛｸﾞﾗﾑ ﾃﾞ ｼﾖｳｻﾚﾃｲﾏｽ";	/* USE_PROGRAM_ONETOUCH_ERROR		*//* (PRO_CIPHER == ENABLE) */
CUB	JPN_PleaseCloseTopCover[]			= "ﾄｯﾌﾟｶﾊﾞｰ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ";	/* TOP_COVER_OPEN_ERROR				*/
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1999/01/21 */
//#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
#endif
CUB	JPN_DialNumberStoredError[]			= "ﾌｧｸｽ ﾊﾞﾝｺﾞｳ ﾄｳﾛｸｽﾞﾐ ";	/* DIAL_NUMBER_STORED_ERROR			*/
CUB	JPN_ProgramStoredError[]			= "ﾌﾟﾛｸﾞﾗﾑｶﾞ ﾄｳﾛｸｻﾚﾃｲﾏｽ";	/* PROGRAM_STORED_ERROR				*/
CUB	JPN_MailAddressStoredError[]		= "ﾒｰﾙｱﾄﾞﾚｽ ﾄｳﾛｸｽﾞﾐ    ";	/* MAIL_ADDRESS_STORED_ERROR		*/
CUB	JPN_MailGroupStoredError[]			= "ｱﾄﾞﾚｽｸﾞﾙｰﾌﾟ ﾄｳﾛｸｽﾞﾐ ";	/* MAIL_GROUP_STORED_ERROR			*/
CUB	JPN_UserDataFullError[]				= "ｺﾚｲｼﾞｮｳ ﾄｳﾛｸﾃﾞｷﾏｾﾝ  ";	/* USER_DATA_FULL_ENTRY_ERROR		*/
CUB	JPN_NoRS232C_Error[]				= "RS232C ｶﾞ ｾｯﾄｻﾚﾃｲﾏｾﾝ";	/* NO_RS232C_PCB_ERROR				*/
CUB	JPN_TooManyDirectAdrError[]			= "ｱﾄﾞﾚｽ ｹﾝｽｳ ｵｰﾊﾞｰ ﾃﾞｽ";	/* TOO_MANY_DIRECT_ADDRESS_ERROR	*/
CUB	JPN_NoUserDataError[]				= "ﾕｰｻﾞﾃﾞｰﾀ ｶﾞ ﾐﾄｳﾛｸﾃﾞｽ";	/* NO_USER_DATA_ERROR				*/
CUB	JPN_InvalidAddressError[]			= "ﾀﾀﾞｼｲ ｱﾄﾞﾚｽ ｦ ﾄﾞｳｿﾞ ";	/* INVALID_ADDRESS_ERROR			*/
CUB	JPN_NoTCPIP_BoardError[]			= "ｵﾌﾟｼｮﾝ ｷﾊﾞﾝ ｶﾞ ｱﾘﾏｾﾝ";	/* NO_TCPIP_BOARD_ERROR				*/
CUB	JPN_MemoryFullError[]				= "ﾒﾓﾘｰ ｶﾞ ﾀﾘﾏｾﾝ       ";	/* MEMORY_FULL_ERROR				*/
CUB	JPN_AlreadyUsedError[]				= "ｽﾃﾞﾆ ﾄｳﾛｸｽﾞﾐ ﾃﾞｽ    ";	/* ALREADY_USED_ERROR				*/
CUB	JPN_NoEntryData[]					= "No Entry Data       ";	/* NO_ENTRY_DATA					*/
CUB	JPN_NoStoredAddress[]				= "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         ";	/* NO_STORED_ADDRESS_ERROR			*/
CUB	JPN_InvalidPassword[]				= "ﾊﾟｽﾜｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ   ";	/* INVALID_PASSWORD_ERROR			*/
CUB	JPN_ExecuteCommand[]				= "ｺﾏﾝﾄﾞ ｦ ｼﾞｯｺｳﾁｭｳ ﾃﾞｽ";	/* EXECUTE_COMMAND_ERROR			*/
CUB	JPN_NoDeviceError[]					= "No Device           ";	/* NO_DEVICE_ERROR					*/
#if (0)
//CUB JPN_NoAccessPointTelNumber[]		= "ｱｸｾｽﾎﾟｲﾝﾄ ﾐﾄｳﾛｸﾃﾞｽ  ";	/* NO_ACCESS_POINT_DATA_ERROR		*/
#endif
#if (0)	/* プログラムの構成上、条件コンパイルをはずします。By H.Fujimura 1999/01/21 */
//#endif
#endif
CUB	JPN_SettingRelayBox[]				= "ﾁｭｳｹｲﾎﾞｯｸｽ ﾃﾞｽ      ";	/* SETTING_RELAY_BOX_ERROR			*//* By H.Fujimura 1999/01/21 */
CUB	JPN_TooManyRelayDirect[]			= "ﾁｮｸｾﾂﾀﾞｲﾔﾙ 1ｶｼｮ ｲﾅｲ ";	/* TOO_MANY_RELAY_DIRECT_ERROR		*//* By H.Fujimura 1999/01/21 */

/*----------------------------------*
 *	通信中
 *----------------------------------*/
CUB	JPN_Transmit[]						= "ｿｳｼﾝ                ";
CUB	JPN_Receive[]						= "ｼﾞｭｼﾝ     ";
CUB	JPN_Called[]						= "   **  ﾁｬｸｼﾝ  **    ";
CUB	JPN_CallReservation[]				= "  **  ｶｲﾜ ﾖﾔｸ  **   ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	JPN_CallReservation_S[]				= " ** ﾃﾞﾝﾜ ﾖﾋﾞﾀﾞｼ **  ";
#endif

/*----------------------------------*
 *	原稿サイズ・線密度
 *----------------------------------*/
CUB	JPN_DocNormal[]						= "ﾋｮｳｼﾞｭﾝ   \0         ";
CUB	JPN_DocFine[]						= "ｺｳｶﾞｼﾂ    \0         ";
CUB	JPN_DocSFine[]						= "ﾁｮｳｺｳｶﾞｼﾂ \0         ";
#if (PRO_PITNEYBOWES == ENABLE) /* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
	/* 仕向け先ＵＳＡによりマルチワーディング対象外につき英語を転用しています。*/
CUB	JPN_DocGray[]						= "PHOTO     \0         "; 
CUB	JPN_DocHGray[]						= "H PHOTO   \0         "; 
#else
CUB	JPN_DocGray[]						= "ｼｬｼﾝ      \0         ";
#endif
CUB	JPN_DocHFine[]						= "H Fine    \0         "; /*評価用に追加1996/06/19Eguchi*/	/* 日本語に変更 */
CUB	JPN_DocEFine[]						= "E Fine    \0         "; /*評価用に追加1996/06/19Eguchi*/	/* 日本語に変更 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	JPN_DocFine_S[]						= "ｺﾏｶｲ      \0         ";
CUB	JPN_DocSFine_S[]					= "ｾｲｻｲ      \0         ";
#endif

/*----------------------------------*
 *	次原稿・メモリ残量
 *----------------------------------*/
CUB	JPN_NextDocument[]					= "ｼﾞｹﾞﾝｺｳ";
#if (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/22 */
CUB	JPN_MemoryAreaShort[]				= "            ﾒﾓﾘｰ   %";
CUB	JPN_MemoryAreaLong[]				= "            ﾒﾓﾘｰ   %";
#else
CUB	JPN_MemoryAreaShort[]				= "             ﾒﾓﾘ   %";
CUB	JPN_MemoryAreaLong[]				= "             ﾒﾓﾘ   %";
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/21 */
 #if (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	JPN_MemoryAreaLong2[]				= "   *****    ﾒﾓﾘｰ   %";
CUB	JPN_MemoryAreaShort2[]				= "            ﾒﾓﾘｰ   %";
 #else
CUB	JPN_MemoryAreaLong2[]				= "   *****     ﾒﾓﾘ   %";
CUB	JPN_MemoryAreaShort2[]				= "             ﾒﾓﾘ   %";	/* ＬＣＤ表示変更(0x7E = ->) By O.Kimoto 1999/02/25 */
 #endif
#endif
#if (PRO_NOT_AUTO_RX_DISP == ENABLE)	/* by K.Watanabe 1998/06/08 */
CUB	JPN_MemoryFull[]					= "ﾒﾓﾘ ｶﾞ ｲｯﾊﾟｲﾃﾞｽ     ";
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* メモリフル時は自動／手動受信ともに出来ない By O.Kimoto 2002/10/23 */
CUB	JPN_NotAutoReceive[]				= "ｼﾞｭｼﾝ ﾃﾞｷﾏｾﾝ        ";
 #else
CUB	JPN_NotAutoReceive[]				= "ｼﾞﾄﾞｳｼﾞｭｼﾝ ﾃﾞｷﾏｾﾝ   ";
 #endif
#endif

/*----------------------------------*
 *	月
 *----------------------------------*/
CUB	JPN_January[]						= "Jan";
CUB	JPN_February[]						= "Feb";
CUB	JPN_March[]							= "Mar";
CUB	JPN_April[]							= "Apr";
CUB	JPN_May[]							= "May";
CUB	JPN_June[]							= "Jun";
CUB	JPN_July[]							= "Jul";
CUB	JPN_August[]						= "Aug";
CUB	JPN_September[]						= "Sep";
CUB	JPN_October[]						= "Oct";
CUB	JPN_November[]						= "Nov";
CUB	JPN_December[]						= "Dec";

/*----------------------------------*
 *	予約表示
 *----------------------------------*/
CUB	JPN_Reserving[]						= "    ** ﾖﾔｸﾁｭｳ **    ";
CUB	JPN_AutoRedial[]					= " ** ｼﾞﾄﾞｳ ﾘﾀﾞｲﾔﾙ ** ";

/*----------------------------------*
 *	原稿セット時
 *----------------------------------*/
CUB	JPN_TransmitOrCopyReady[]			= "ﾂｳｼﾝ/ｺﾋﾟｰ ﾃﾞｷﾏｽ     ";
CUB	JPN_TransmitReady[]					= "ﾂｳｼﾝ ﾃﾞｷﾏｽ          ";	/* 日本以外は、???_TransmitOrCopyReadyと同じです */

#if (PRO_PC_PRINT == ENABLE)
/*----------------------------------*
 *	ＰＣプリント動作中
 *----------------------------------*/
CUB	JPN_PC_Print[]						= "PC                  ";
CUB	JPN_PC_Receiving[]					= "  **  ｼﾞｭｼﾝﾁｭｳ  **  ";
CUB	JPN_PC_MemoryOverFlow[]				= "PC ﾒﾓﾘ ｵｰﾊﾞｰ ﾃﾞｽ    ";
#endif

/*----------------------------------*
 *	プリント中
 *----------------------------------*/
CUB	JPN_Printing[]						= "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   ";

/*----------------------------------*
 *	ウォームアップ
 *----------------------------------*/
CUB	JPN_Wait[]							= "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **";

/*----------------------------------*
 *	イメージプリント
 *----------------------------------*/
CUB	JPN_PollingDocument[]				= "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ       ";
CUB	JPN_SecureMailDocument[]			= "ｼﾝﾃﾝｼﾞｭｼﾝ ﾌﾟﾘﾝﾄ     ";
CUB	JPN_MemoryRxDocument[]				= "                    ";	/* 日本語に変更 */
CUB	JPN_CommandDocument[]				= "ｿｳｼﾝ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ    ";
CUB	JPN_BatchTxDocument[]				= "ｲｯｶﾂｿｳｼﾝ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ";

/*----------------------------------*
 *	リストプリント
 *----------------------------------*/
CUB	JPN_PrintJournal[]					= "ﾂｳｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ       ";
#if (PRO_JOURNAL_VER_UP == ENABLE)	/* by K.Watanabe 2004/10/28 */
CUB	JPN_PrintJournalTx[]				= "ｿｳｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ       ";
CUB	JPN_PrintJournalRx[]				= "ｼﾞｭｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ      ";
CUB	JPN_PrintJournalTxRx[]				= "ｿｳｼﾞｭｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ    ";
#endif
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
CUB	JPN_PrintAllJournal[]				= "ﾂｳｼﾝｶﾝﾘ ﾌﾟﾘﾝﾄ       ";
CUB	JPN_PrintDailyReport[]				= "ﾂｳｼﾝﾆｯﾎﾟｳ ﾌﾟﾘﾝﾄ     ";
#endif
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	JPN_TCR[]							= "ｿｳｼﾝｶｸﾆﾝｼｮｳ         ";
#else
CUB	JPN_TCR[]							= "ｿｳｼﾝｼｮｳ             ";
#endif
CUB	JPN_PrintSpeedDial[]				= "ﾀﾝｼｭｸﾀﾞｲﾔﾙ ﾘｽﾄ      ";
CUB	JPN_PrintOneTouch[]					= "ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ﾘｽﾄ      ";
CUB	JPN_PrintProgramOneTouch[]			= "ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ﾘｽﾄ    ";
CUB	JPN_GroupList[]						= "ｸﾞﾙｰﾌﾟ ﾘｽﾄ          ";
CUB	JPN_SF_ProgramListPrint[]			= "ｷﾉｳ ﾘｽﾄ             ";
CUB	JPN_SetPrintSettings[]				= "ｷｷｾｯﾃｲ ﾘｽﾄ          ";
CUB	JPN_PrintCommands[]					= "ﾂｳｼﾝﾖﾔｸ ﾘｽﾄ         ";
CUB	JPN_PrintSecureMailList[]			= "ｼﾝﾃﾝｼｬ ﾘｽﾄ          ";
CUB	JPN_MessageList[]					= "ﾒｯｾｰｼﾞ ﾘｽﾄ          ";
CUB	JPN_PrintSecureMail[]				= "ｼﾝﾃﾝｼﾞｭｼﾝ ﾌﾟﾘﾝﾄ     ";
CUB	JPN_SF_T30MonitorPrint[]			= "T30ﾓﾆﾀ              ";
CUB	JPN_SF_FactoryFunctionList[]		= "ｺｳｼﾞｮｳ ﾌｧﾝｸｼｮﾝ ﾘｽﾄ  ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/15 */
CUB	JPN_SF_MemorySwitchMode[]			= "ﾒﾓﾘｰ ｽｲｯﾁ           ";
#else
CUB	JPN_SF_MemorySwitchMode[]			= "ﾒﾓﾘ ｽｲｯﾁ            ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	JPN_CheckMessage[]					= "ﾁｪｯｸ ﾒｯｾｰｼﾞ         ";
CUB	JPN_SF_OnLineMonitor[]				= "ｵﾝﾗｲﾝ ﾓﾆﾀ           ";
CUB	JPN_SF_OrderForm[]					= "ﾊｯﾁｭｳﾖｳｼ            ";

/*----------------------------------*
 *	パスコード
 *----------------------------------*/
CUB	JPN_InputPasscode[]					= "ﾊﾟｽｺｰﾄﾞ        :\0   ";
CUB	JPN_EnterProtectPasscode[]			= "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ     :\0   ";
CUB	JPN_OldProtectPasscode[]			= "Old ﾌﾟﾛﾃｸﾄｺｰﾄﾞ :\0   ";
CUB	JPN_NewProtectPasscode[]			= "New ﾌﾟﾛﾃｸﾄｺｰﾄﾞ :\0   ";
CUB	JPN_EnterIDCode[]					= "ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ   :\0   ";
#if (PRO_F_CODE == ENABLE)
CUB	JPN_EnterFcodePasscode[]			= "ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ   :\0   ";
#endif
#if (PRO_CIPHER == ENABLE)
CUB	JPN_CipherPassCode[]				= "ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ   :\0   ";
CUB	JPN_OldCipherPassCode[]				= "ｹﾞﾝｻﾞｲ ﾉ ﾊﾞﾝｺﾞｳ:\0   ";
CUB	JPN_NewCipherPassCode[]				= "ｱﾀﾗｼｲ ﾊﾞﾝｺﾞｳ   :\0   ";
#endif

/*----------------------------------*
 *	入力モード
 *----------------------------------*/
#if defined(JPN)
CUB	JPN_Kana[]							= ":ｶﾀｶﾅ    ";
 #if (PRO_JIS_CODE == ENABLE)
CUB	JPN_KanjiCode[]						= ":ｶﾝｼﾞｺｰﾄﾞ";
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
CUB	JPN_Alphameric[]					= ":ｴｲｽｳ    "; /* ';' to ':' Modified by SMuratec L.Z.W 2003/11/28 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	JPN_Upper[]							= ":ｴｲｽｳ ﾀﾞｲ";
CUB	JPN_Lower[]							= ":ｴｲｽｳ ｼｮｳ";
CUB	JPN_Symbol[]						= ":ｷｺﾞｳ    ";	/* ANZUのみ */
CUB	JPN_Code[]							= ":ｺｰﾄﾞ    ";
CUB	JPN_ModeNone[]						= ":        ";

/*----------------------------------*
 *	電話帳
 *----------------------------------*/
CUB	JPN_TelephoneBookMode[]				= "ﾃﾞﾝﾜﾁｮｳ          [ ]";

/*----------------------------------*
 *	電話
 *----------------------------------*/
CUB	JPN_OnHold[]						= "     ** ﾎﾘｭｳ **     ";	/* POPLAR_B以外 */
CUB	JPN_TelephoneMode[]					= "     ** ﾃﾞﾝﾜ **     ";

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 変更 by Y.kano 2003/09/08 */
CUB	JPN_ChangeVolume[]					= "ﾎﾞﾘｭｰﾑ:             ";
#else
CUB	JPN_ChangeVolume[]					= "  ﾎﾞﾘｭｰﾑ:           ";
#endif

/*----------------------------------*
 *	メモリーオーバーオペレーション
 *----------------------------------*/
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	JPN_MemoryOverFlow[]				= "ﾒﾓﾘｰｵｰﾊﾞｰ ﾃﾞｽ       ";
CUB	JPN_MemoryOverStartClear[]			= "ﾒﾓﾘｰﾌﾞﾝﾉﾐ  ｽﾀｰﾄ/ｸﾘｱ ";
CUB	JPN_MemoryOverEnterClear[]			= "ﾒﾓﾘｰﾌﾞﾝﾉﾐ   ｾｯﾄ/ｸﾘｱ ";
CUB	JPN_MemoryOverCopyClear[]			= "ﾒﾓﾘｰﾌﾞﾝﾉﾐ  ｺﾋﾟｰ/ｸﾘｱ ";	/* POPLAR_B以外 */
#elif (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	JPN_MemoryOverFlow[]				= "ﾒﾓﾘｰ ｵｰﾊﾞｰ ﾃﾞｽ      ";
CUB	JPN_MemoryOverStartClear[]			= "ﾒﾓﾘｰ ﾌﾞﾝﾉﾐ ｽﾀｰﾄ/ｸﾘｱ ";
CUB	JPN_MemoryOverEnterClear[]			= "ﾒﾓﾘｰ ﾌﾞﾝﾉﾐ  ｾｯﾄ/ｸﾘｱ ";
CUB	JPN_MemoryOverCopyClear[]			= "ﾒﾓﾘｰ ﾌﾞﾝﾉﾐ ｺﾋﾟｰ/ｸﾘｱ ";	/* POPLAR_B以外 */
#else
CUB	JPN_MemoryOverFlow[]				= "ﾒﾓﾘ ｵｰﾊﾞｰ ﾃﾞｽ       ";
CUB	JPN_MemoryOverStartClear[]			= "ﾒﾓﾘ ﾌﾞﾝﾉﾐ  ｽﾀｰﾄ/ｸﾘｱ ";
CUB	JPN_MemoryOverEnterClear[]			= "ﾒﾓﾘ ﾌﾞﾝﾉﾐ   ｾｯﾄ/ｸﾘｱ ";
CUB	JPN_MemoryOverCopyClear[]			= "ﾒﾓﾘ ﾌﾞﾝﾉﾐ  ｺﾋﾟｰ/ｸﾘｱ ";	/* POPLAR_B以外 */
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

/*----------------------------------*
 *	ファンクション関係
 *----------------------------------*/
/* 機能選択状態 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 全機種共通の変更でないのに条件が入っていなかったので条件追加 by K.Watanabe 2004/10/22 */
CUB	JPN_OneTouchDialMode[]				= "    ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ      ";
CUB	JPN_SpeedDialMode[]					= "    ﾀﾝｼｭｸﾀﾞｲﾔﾙ      ";
CUB	JPN_ProgramOneTouchMode[]			= "    ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ    ";
CUB	JPN_PollingMode[]					= "    ﾎﾟｰﾘﾝｸﾞ         ";
CUB	JPN_SecureMailMode[]				= "    ｼﾝﾃﾝ            ";
CUB	JPN_DelayedCommandsMode[]			= "    ﾂｳｼﾝﾖﾔｸ         ";
CUB	JPN_SetReportMode[]					= "    ﾂｳｼﾝｶﾝﾘ         ";
CUB	JPN_PrintGroupMode[]				= "    ｸﾞﾙｰﾌﾟ ﾘｽﾄ      ";
CUB	JPN_UserInstallMode[]				= "    ｾｯﾁ ﾓｰﾄﾞ        ";
CUB	JPN_UserSettingsMode[]				= "    ｷｷｾｯﾃｲ          ";
CUB	JPN_MessageMode[]					= "    ﾒｯｾｰｼﾞ          ";
CUB	JPN_SetNumberOfPagesMode[]			= "    ｹﾞﾝｺｳﾏｲｽｳ ｾｯﾄ   ";
CUB	JPN_SetDepartmentMode[]				= "    ﾌﾞﾓﾝｶﾝﾘ         ";
CUB	JPN_SetBatchTxMode[]				= "    ｲｯｶﾂ ｿｳｼﾝ       ";
CUB	JPN_SecurityReceiveMode[]			= "    ｾｷｭﾘﾃｨ ｼﾞｭｼﾝ    ";
CUB	JPN_FcodeBoxMode[]					= "    Fｺｰﾄﾞ ﾎﾞｯｸｽ     ";	/* (PRO_F_CODE == ENABLE) */
#else
CUB	JPN_OneTouchDialMode[]				= "  ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ        ";
CUB	JPN_SpeedDialMode[]					= "  ﾀﾝｼｭｸﾀﾞｲﾔﾙ        ";
CUB	JPN_ProgramOneTouchMode[]			= "  ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ      ";
CUB	JPN_PollingMode[]					= "  ﾎﾟｰﾘﾝｸﾞ           ";
CUB	JPN_SecureMailMode[]				= "  ｼﾝﾃﾝ              ";
CUB	JPN_DelayedCommandsMode[]			= "  ﾂｳｼﾝﾖﾔｸ           ";
CUB	JPN_SetReportMode[]					= "  ﾂｳｼﾝｶﾝﾘ           ";
CUB	JPN_PrintGroupMode[]				= "  ｸﾞﾙｰﾌﾟ ﾘｽﾄ        ";
CUB	JPN_UserInstallMode[]				= "  ｾｯﾁ ﾓｰﾄﾞ          ";
CUB	JPN_UserSettingsMode[]				= "  ｷｷｾｯﾃｲ            ";
CUB	JPN_MessageMode[]					= "  ﾒｯｾｰｼﾞ            ";
CUB	JPN_SetNumberOfPagesMode[]			= "  ｹﾞﾝｺｳﾏｲｽｳ ｾｯﾄ     ";
CUB	JPN_SetDepartmentMode[]				= "  ﾌﾞﾓﾝｶﾝﾘ           ";
CUB	JPN_SetBatchTxMode[]				= "  ｲｯｶﾂ ｿｳｼﾝ         ";
CUB	JPN_SecurityReceiveMode[]			= "  ｾｷｭﾘﾃｨ ｼﾞｭｼﾝ      ";
CUB	JPN_FcodeBoxMode[]					= "  Fｺｰﾄﾞ ﾎﾞｯｸｽ       ";	/* (PRO_F_CODE == ENABLE) */
#endif	/* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	JPN_ResetPrinterBoardMode[]			= "  ﾌﾟﾘﾝﾀｰｵﾌﾟｼｮﾝ ﾘｾｯﾄ ";	/* (PRO_PC_PRINT == ENABLE) */
#else
CUB	JPN_ResetPrinterBoardMode[]			= "  ﾌﾟﾘﾝﾀｵﾌﾟｼｮﾝ ﾘｾｯﾄ  ";	/* (PRO_PC_PRINT == ENABLE) */
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	JPN_SetClass1Mode[]					= "  PC-FAX            ";	/* (PRO_CLASS1 == ENABLE) */
CUB	JPN_SetCipherMode[]					= "  ｽｸﾗﾝﾌﾞﾙ ｾｯﾃｲ      ";	/* (PRO_CIPHER == ENABLE) */
CUB	JPN_PrintDecipherDocMode[]			= "  ｽｸﾗﾝﾌﾞﾙｶｲｼﾞｮ ﾌﾟﾘﾝﾄ";	/* (PRO_CIPHER == ENABLE) */

CUB	JPN_EnterOneTouchMode[]				= "   ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ｾｯﾄ   ";
CUB	JPN_EraseOneTouchMode[]				= "   ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ｸﾘｱ   ";
CUB	JPN_PrintOneTouchMode[]				= "   ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ﾘｽﾄ   ";

CUB	JPN_EnterSpeedDialMode[]			= "   ﾀﾝｼｭｸﾀﾞｲﾔﾙ ｾｯﾄ   ";
CUB	JPN_EraseSpeedDialMode[]			= "   ﾀﾝｼｭｸﾀﾞｲﾔﾙ ｸﾘｱ   ";
CUB	JPN_PrintSpeedDialMode[]			= "   ﾀﾝｼｭｸﾀﾞｲﾔﾙ ﾘｽﾄ   ";

CUB	JPN_EnterProgramOneTouchMode[]		= "   ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ｾｯﾄ ";
CUB	JPN_EraseProgramOneTouchMode[]		= "   ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ｸﾘｱ ";
CUB	JPN_PrintProgramOneTouchMode[]		= "   ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ﾘｽﾄ ";

CUB	JPN_StorePollingDocumentMode[]		= "   ﾎﾟｰﾘﾝｸﾞｹﾞﾝｺｳ ﾁｸｾｷ";
CUB	JPN_ErasePollingDocumentMode[]		= "   ﾎﾟｰﾘﾝｸﾞｹﾞﾝｺｳ ｸﾘｱ ";
CUB	JPN_PrintPollingDocumentMode[]		= "   ﾎﾟｰﾘﾝｸﾞｹﾞﾝｺｳﾌﾟﾘﾝﾄ";

CUB	JPN_SetSecureMailBoxMode[]			= "   ｼﾝﾃﾝ ｾｯﾄ         ";
CUB	JPN_PrintSecureMailListMode[]		= "   ｼﾝﾃﾝｼｬ ﾘｽﾄ       ";
CUB	JPN_PrintSecureMailMode[]			= "   ｼﾝﾃﾝｼﾞｭｼﾝ ﾌﾟﾘﾝﾄ  ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/15 */
CUB	JPN_SecureMailHoldTimeMode[]		= "   ｼﾝﾃﾝｼﾞｭｼﾝ ﾒﾓﾘｰｷｶﾝ";
#else
CUB	JPN_SecureMailHoldTimeMode[]		= "   ｼﾝﾃﾝｼﾞｭｼﾝ ﾒﾓﾘｷｶﾝ ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB	JPN_PrintCommandsMode[]				= "   ﾂｳｼﾝﾖﾔｸ ﾘｽﾄ      ";
CUB	JPN_PrintStoredDocumentMode[]		= "   ﾖﾔｸｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ   ";

CUB	JPN_JournalOnOffMode[]				= "   ﾂｳｼﾝｷﾛｸ ｼﾞﾄﾞｳｾｯﾄ ";
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	JPN_PrintJournalMode[]				= "   ﾂｳｼﾝｶﾝﾘ ﾌﾟﾘﾝﾄ    ";
#else
CUB	JPN_PrintJournalMode[]				= "   ﾂｳｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ    ";
#endif
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	JPN_PrintDailyReportMode[]			= "   ﾂｳｼﾝﾆｯﾎﾟｳ ﾌﾟﾘﾝﾄ  ";
#endif
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	JPN_SettingCommunicationResult[]	= "   ｿｳｼﾝｶｸﾆﾝｼｮｳ ｾｯﾄ  ";
#else
CUB	JPN_SettingCommunicationResult[]	= "   ﾂｳｼﾝｼｮｳ ｾｯﾄ      ";
#endif

#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	JPN_SettingScanParameters[]			= "    ｽｷｬﾅ ﾊﾟﾗﾒｰﾀｰ    ";
CUB	JPN_SettingPrintParameters[]		= "    ﾌﾟﾘﾝﾄ ﾊﾟﾗﾒｰﾀｰ   ";
CUB	JPN_SettingCopyParameters[]			= "    ｺﾋﾟｰ ﾊﾟﾗﾒｰﾀｰ    ";	/* POPLAR_B以外 */
#else
CUB	JPN_SettingScanParameters[]			= "    ｽｷｬﾅ ﾊﾟﾗﾒｰﾀ     ";
CUB	JPN_SettingPrintParameters[]		= "    ﾌﾟﾘﾝﾄ ﾊﾟﾗﾒｰﾀ    ";
CUB	JPN_SettingCopyParameters[]			= "    ｺﾋﾟｰ ﾊﾟﾗﾒｰﾀ     ";	/* POPLAR_B以外 */
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB	JPN_SettingPaperSize[]				= "    ｷﾛｸﾍﾟｰﾊﾟｰｻｲｽﾞｾｯﾄ";	/* ANZUのみ */
CUB	JPN_SettingCopyProtect[]			= "    ｺﾋﾟｰｷﾝｼ         ";
CUB	JPN_SettingDialingPause[]			= "    ﾎﾟｰｽﾞｼﾞｶﾝ ｾｯﾄ   ";
CUB	JPN_SettingNumberOfRings[]			= "    ﾖﾋﾞﾀﾞｼﾍﾞﾙｶｲｽｳｾｯﾄ";
CUB	JPN_SettingRedial[]					= "    ﾘﾀﾞｲﾔﾙ ｾｯﾃｲ     ";
CUB	JPN_SettingECMMode[]				= "    ECM ﾓｰﾄﾞ ｾｯﾄ    ";
CUB	JPN_SettingPasscode[]				= "    ﾊﾟｽｺｰﾄﾞ ｾｯﾄ     ";
CUB	JPN_SettingClosedNetwork[]			= "    ﾍｲｲｷﾂｳｼﾝ ｾｯﾄ    ";
CUB	JPN_SettingSecurityTransmission[]	= "    ﾊﾟｽﾜｰﾄﾞ ｿｳｼﾝ    ";
CUB	JPN_SettingBlockJunkMail[]			= "    ﾀﾞｲﾚｸﾄﾒｰﾙ ﾎﾞｳｼ  ";
CUB	JPN_SettingRemoteDiagnostic[]		= "    ｻｰﾋﾞｽﾓｰﾄﾞ ｾｯﾄ   ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/15 */
CUB	JPN_SettingMemoryTransmission[]		= "    ﾒﾓﾘｰｿｳｼﾝ ｾｯﾄ    ";
#else
CUB	JPN_SettingMemoryTransmission[]		= "    ﾒﾓﾘｿｳｼﾝ ｾｯﾄ     ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	JPN_SettingSilentOperation[]		= "    ｻｲﾚﾝﾄｵﾍﾟﾚｰｼｮﾝｾｯﾄ";
CUB	JPN_SettingDialIn[]					= "    ﾀﾞｲﾔﾙｲﾝ ｾｯﾄ     ";	/* (JPN) */
CUB	JPN_SettingProtectPasscode[]		= "    ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｾｯﾄ  ";
CUB	JPN_SettingOperationProtect[]		= "    ｵﾍﾟﾚｰｼｮﾝ ﾌﾟﾛﾃｸﾄ ";
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/16 */
CUB JPN_SettingRemoteRxParameters[]		= "    ﾘﾓｰﾄ ﾄｸﾊﾞﾝ      ";
#endif		/* End of (defined (KEISATSU)) */
CUB	JPN_SettingPINAccessMode[]			= "    PIN ﾓｰﾄﾞ ｾｯﾄ    ";
CUB	JPN_SettingRingMasta[]				= "    ﾘﾝｸﾞﾏｽﾀ ｾｯﾄ     ";	/* (USA) */
CUB	JPN_SettingStamp[]					= "    ｽﾐｽﾀﾝﾌﾟ ｾｯﾄ     ";
CUB	JPN_SettingResetDrumLife[]			= "    ﾄﾞﾗﾑ ｶｳﾝﾀ ｸﾘｱ   ";	/* ANZUのみ */
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */
CUB	JPN_SettingRxAlarm[]				= "    Set Rx Alarm    ";
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/22 */
CUB	JPN_SettingMercuryMode[]			= "    ﾌﾟﾚﾌｨｸｽ ｾｯﾄ     "; /* 変更必要 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	JPN_SettingHoldMelody[]				= "    ﾎﾘｭｳ ﾒﾛﾃﾞｨ ｾｯﾄ  ";
#endif
#if (PRO_REMOTE_RX == ENABLE)			/* ＮＴＴ仕様のポプラＬで使用 98/01/26 T.Fukumoto */
CUB	JPN_SettingRemoteReceive[]			= "    ﾘﾓｰﾄ ｼﾞｭｼﾝ ｾｯﾄ  ";
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	JPN_SettingOnHookReceive[]			= "    ｵﾝﾌｯｸ ｼﾞｭｼﾝ ｾｯﾄ ";	/* 98/03/13 Add By T.Fukumoto */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
CUB	JPN_SettingPrintSettings[]			= "    ｷｷｾｯﾃｲ ﾘｽﾄ      ";
#endif

CUB	JPN_SetMessageOnOff[]				= "   ﾒｯｾｰｼﾞ ｿｳｼﾝ      ";
CUB	JPN_SetMessage[]					= "   ﾒｯｾｰｼﾞ ｾｯﾄ       ";
CUB	JPN_PrintMessageList[]				= "   ﾒｯｾｰｼﾞ ﾘｽﾄ       ";

CUB	JPN_SettingDepartmentProtect[]		= "   ﾌﾞﾓﾝｶﾝﾘﾌﾟﾛﾃｸﾄ ｾｯﾄ";
CUB	JPN_SettingDepartmentCode[]			= "   ﾌﾞﾓﾝｶﾝﾘ ｺｰﾄﾞ ｾｯﾄ ";
CUB	JPN_SettingDepartmentOnOff[]		= "   ﾌﾞﾓﾝｶﾝﾘ ｾｯﾄ      ";
#if (PRO_DEPART_NEW_LIST == ENABLE)									/* added by thonda 1997/12/03 */
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/21 */
CUB	JPN_PrintDepartTimeList[]			= "   ﾌﾞﾓﾝｶﾝﾘﾘｽﾄ ﾌﾟﾘﾝﾄ ";
CUB	JPN_EraseDepartTimeList[]			= "   ﾌﾞﾓﾝｶﾝﾘﾘｽﾄ ｼｮｳｷｮ ";
 #else
CUB	JPN_PrintDepartTimeList[]			= "   ｼﾞｶﾝｶﾝﾘﾘｽﾄ ﾌﾟﾘﾝﾄ ";
CUB	JPN_EraseDepartTimeList[]			= "   ｼﾞｶﾝｶﾝﾘﾘｽﾄ ｼｮｳｷｮ ";
 #endif
#endif

CUB	JPN_SettingBatchBox[]				= "   ﾎﾞｯｸｽ ｾｯﾄ        ";
CUB	JPN_PrintBatchBoxList[]				= "   ﾎﾞｯｸｽ ﾘｽﾄ        ";
CUB	JPN_PrintBatchDocList[]				= "   ｹﾞﾝｺｳ ﾘｽﾄ        ";
CUB	JPN_PrintBatchDoc[]					= "   ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ      ";
CUB	JPN_EraseBatchBox[]					= "   ﾎﾞｯｸｽ ｸﾘｱ        ";
CUB	JPN_EraseBatchDoc[]					= "   ｹﾞﾝｺｳ ｸﾘｱ        ";

CUB	JPN_SettingSecurityRx[]				= "   ｾｷｭﾘﾃｨ ｼﾞｭｼﾝ ｾｯﾄ ";
CUB	JPN_PrintMemoryReceiveDoc[]			= "   ｼﾞｭｼﾝ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ";

#if (PRO_F_CODE == ENABLE)
CUB	JPN_EnterFcodeBoxMode[]				= "   ﾎﾞｯｸｽ ｾｯﾄ        ";
CUB	JPN_PrintFcodeBoxListMode[]			= "   ﾎﾞｯｸｽ ﾘｽﾄ        ";
CUB	JPN_PrintFcodeStoreDocListMode[]	= "   ﾁｸｾｷ ｹﾞﾝｺｳ ﾘｽﾄ   ";
CUB	JPN_PrintFcodeStoreDocMode[]		= "   ﾁｸｾｷ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ ";
CUB	JPN_EraseFcodeBoxMode[]				= "   ﾎﾞｯｸｽ ｸﾘｱ        ";
CUB	JPN_EraseFcodeDocMode[]				= "   ﾁｸｾｷ ｹﾞﾝｺｳ ｸﾘｱ   ";
CUB	JPN_StoreFcodeDocMode[]				= "   ｹﾞﾝｺｳ ﾁｸｾｷ       ";
#endif

#if (PRO_CIPHER == ENABLE)
CUB	JPN_EnterCipherKeyBookMode[]		= "   ｷｰﾊﾞﾝｸ ｾｯﾄ       ";
CUB	JPN_PrintCipherKeyBookListMode[]	= "   ｷｰﾊﾞﾝｸ ﾌﾟﾘﾝﾄ     ";
CUB	JPN_PrintCipherKeyMode[]			= "   ｷｰﾜｰﾄﾞ ﾌﾟﾘﾝﾄ     ";
CUB	JPN_EraseCipherKeyBookMode[]		= "   ｷｰﾜｰﾄﾞ ｸﾘｱ       ";
CUB	JPN_EraseCipherRxDocMode[]			= "   ｽｸﾗﾝﾌﾞﾙｹﾞﾝｺｳ ｸﾘｱ ";
CUB	JPN_EnterDefaultCipherKeyMode[]		= "   ﾃﾞﾌｫﾙﾄ ｷｰﾜｰﾄﾞ ｾｯﾄ";
CUB	JPN_EnterCipherServiceLabelMode[]	= "   ﾋﾝﾄ ﾋｮｳｼﾞｲﾁ      ";
CUB	JPN_EnterCipherPassCodeMode[]		= "   ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ ｾｯﾄ ";
#endif

CUB	JPN_SettingRS232CPCFaxScan[]		= "   PC-FAX ﾛｰｶﾙｽｷｬﾝ  ";
CUB	JPN_SettingRS232CParameter[]		= "   RS232C ｾｯﾄ       ";
CUB	JPN_SettingRS232CPCFaxInitial[]		= "   PC-FAX ｼｮｷｶ      ";

/*----------------------------------*
 *	ワンタッチ登録
 *----------------------------------*/
CUB	JPN_SelectOnetouch[]				= "ﾜﾝﾀｯﾁｷｰ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ";

CUB	JPN_EraseOneTouch[]					= "ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ｸﾘｱ      ";
CUB	JPN_EraseSpeedDial[]				= "ﾀﾝｼｭｸﾀﾞｲﾔﾙ ｸﾘｱ      ";
CUB	JPN_EraseProgramOneTouch[]			= "ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ｸﾘｱ    ";

/*----------------------------------*
 *	短縮登録
 *----------------------------------*/
CUB	JPN_SelectOptionalSpeedNumber[]		= "   /     (0-999):   ";

/* ワンタッチ・短縮ダイアルデータ入力中 */
/* このワーディングのサイズ及び登録順はかえてはいけない */
CUB	JPN_FaxNumber[]						= "ﾀﾞｲﾔﾙ ﾊﾞﾝｺﾞｳ        ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	JPN_AltNumber[]						= "ﾃﾝｿｳ ﾊﾞﾝｺﾞｳ         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	JPN_RemoteName[]					= "ｱｲﾃｻｷﾒｲ             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大9ﾊﾞｲﾄです */
CUB	JPN_GroupNumber[]					= "ｸﾞﾙｰﾌﾟ ﾊﾞﾝｺﾞｳ       ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/26 */
CUB	JPN_PinNumber[]						= "TTI ﾊﾞﾝｺﾞｳ          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
#else
CUB	JPN_PinNumber[]						= "PIN ﾊﾞﾝｺﾞｳ          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
#endif
CUB	JPN_Attribute1[]					= "ｿﾞｸｾｲ 1             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	JPN_Attribute2[]					= "ｿﾞｸｾｲ 2             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	JPN_Attribute3[]					= "ｿﾞｸｾｲ 3             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */
CUB	JPN_Attribute4[]					= "ｿﾞｸｾｲ 4             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */

CUB	JPN_SetPIN_Number[]					= "PIN ﾊﾞﾝｺﾞｳ ｾｯﾄ      ";

/*----------------------------------*
 *	プログラムワンタッチ
 *----------------------------------*/
CUB	JPN_SelectProgramOnetouch[]			= "ﾜﾝﾀｯﾁｷｰ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ";

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* By H.Fujimura 1999/01/21 */
/*----------------------------------*
 *	拡張版プログラムワンタッチ
 *----------------------------------*/
CUB JPN_ProgramItem[][21]		= {
										  "    ﾄｳﾛｸ ﾅｲﾖｳ: ﾂｳｼﾝ ",
										  "    ﾄｳﾛｸ ﾅｲﾖｳ: ﾘｽﾄ  ",
										  "    ﾄｳﾛｸ ﾅｲﾖｳ: ﾁｸｾｷ ",
};

CUB JPN_ProgramList[][21]		= {
										  "   ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ﾘｽﾄ   ",
										  "   ﾀﾝｼｭｸﾀﾞｲﾔﾙ ﾘｽﾄ   ",
										  "   ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ﾘｽﾄ ",
										  "   ｼﾝﾃﾝｼｬ ﾘｽﾄ       ",
										  "   ﾂｳｼﾝﾖﾔｸ ﾘｽﾄ      ",
 #if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
										  "   ﾂｳｼﾝｶﾝﾘ ﾌﾟﾘﾝﾄ    ",
										  "   ﾂｳｼﾝﾆｯﾎﾟｳ ﾌﾟﾘﾝﾄ  ",
 #else
										  "   ﾂｳｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ    ",
 #endif
										  "   ｸﾞﾙｰﾌﾟ ﾘｽﾄ       ",
										  "   ｷｷｾｯﾃｲ ﾘｽﾄ       ",
 #if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/08/24 */
										  "   ﾒｯｾｰｼﾞ ﾘｽﾄ       ",
 #else
										  "   ﾀﾞｲﾚｸﾄﾒｰﾙ ﾘｽﾄ    ",
										  "   ﾒｯｾｰｼﾞ ﾘｽﾄ       ",
										  "   ｲｯｶﾂｿｳｼﾝﾎﾞｯｸｽ ﾘｽﾄ",
										  "   ｲｯｶﾂｿｳｼﾝｹﾞﾝｺｳ ﾘｽﾄ",
 #endif
 #if (PRO_F_CODE == ENABLE)	/* By H.Fujimura 1999/01/21 */
										  "   Fｺｰﾄﾞﾎﾞｯｸｽ ﾘｽﾄ   ",
										  "   Fｺｰﾄﾞｹﾞﾝｺｳ ﾘｽﾄ   ",
 #endif
 #if (PRO_DEPART_NEW_LIST == ENABLE)	/* By H.Fujimura 1999/01/21 */
										  "   ﾌﾞﾓﾝｶﾝﾘ ﾘｽﾄ      ",
 #endif
 #if (PRO_NUMBER_DISPLAY == ENABLE)	/* By H.Fujimura 1999/01/21 */
										  "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘｽﾄ",
										  "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘﾚｷ",
 #endif
 #if (PRO_RX_DOC_TRANSFER == ENABLE)	/* By H.Fujimura 1999/01/21 */
										  "   FAXﾜｰﾌﾟ ﾘｽﾄ      ",
 #endif
};
CUB JPN_ProgramStore[][21]		= {
										  "   ﾎﾟｰﾘﾝｸﾞｹﾞﾝｺｳ ﾁｸｾｷ",
 #if (PRO_F_CODE == ENABLE)	/* By H.Fujimura 1999/01/21 */
										  "   Fｺｰﾄﾞｹﾞﾝｺｳ ﾁｸｾｷ  ",
 #endif
};

CUB JPN_ProgramTxModeSW[][21]	= {
										  "    ｶﾞｼﾂ: ---       ",
										  "    ｶﾞｼﾂ: ﾋｮｳｼﾞｭﾝ   ",
										  "    ｶﾞｼﾂ: ｺｳｶﾞｼﾂ    ",
										  "    ｶﾞｼﾂ: ﾁｮｳｺｳｶﾞｼﾂ ",
										  "    ｶﾞｼﾂ: ｼｬｼﾝ      ",
};

CUB JPN_ProgramContrastSW[][21]	= {
										  "    ﾉｳﾄﾞ:       --- ",
										  "    ﾉｳﾄﾞ:       ｳｽｸ ",
/*										  "    ﾉｳﾄﾞ:    ﾔﾔ ｳｽｸ ",*/
										  "    ﾉｳﾄﾞ:       ﾌﾂｳ ",
/*										  "    ﾉｳﾄﾞ:    ﾔﾔ ｺｸ  ",*/
										  "    ﾉｳﾄﾞ:       ｺｸ  ",
};

CUB JPN_ProgramStampSW[][21]	= {
										  "    ｽﾐｽﾀﾝﾌﾟ:    --- ",
										  "    ｽﾐｽﾀﾝﾌﾟ:    OFF ",
										  "    ｽﾐｽﾀﾝﾌﾟ:    ON  ",
};

 #if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/15 */
CUB JPN_ProgramMemoryTxSW[][21]	= {
										  "    ﾒﾓﾘｰｿｳｼﾝ:   --- ",
										  "    ﾒﾓﾘｰｿｳｼﾝ:   OFF ",
										  "    ﾒﾓﾘｰｿｳｼﾝ:   ON  ",
};
 #else
CUB JPN_ProgramMemoryTxSW[][21]	= {
										  "    ﾒﾓﾘｿｳｼﾝ:    --- ",
										  "    ﾒﾓﾘｿｳｼﾝ:    OFF ",
										  "    ﾒﾓﾘｿｳｼﾝ:    ON  ",
};
 #endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB JPN_ProgramConfirmSW[][21]	= {
 #if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
										  "ｿｳｼﾝｶｸﾆﾝｼｮｳ: ---    ",
										  "ｿｳｼﾝｶｸﾆﾝｼｮｳ: OFF    ",
										  "ｿｳｼﾝｶｸﾆﾝｼｮｳ: ｿｳｼﾝ   ",
										  "ｿｳｼﾝｶｸﾆﾝｼｮｳ: ｼﾞｭﾘｮｳ ",
 #else
										  "    ﾂｳｼﾝｼｮｳ: ---    ",
										  "    ﾂｳｼﾝｼｮｳ: OFF    ",
										  "    ﾂｳｼﾝｼｮｳ: ｿｳｼﾝ   ",
										  "    ﾂｳｼﾝｼｮｳ: ｼﾞｭﾘｮｳ ",
 #endif
};

 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB JPN_ProgramTxModeSW_S[][21]	= {
										  "    ｶﾞｼﾂ: ---       ",
										  "    ｶﾞｼﾂ: ﾋｮｳｼﾞｭﾝ   ",
										  "    ｶﾞｼﾂ: ｺﾏｶｲ      ",
										  "    ｶﾞｼﾂ: ｾｲｻｲ      ",
										  "    ｶﾞｼﾂ: ｼｬｼﾝ      ",
};
CUB JPN_ProgramContrastSW_S[][21]	= {
										  "    ﾉｳﾀﾝ:       --- ",
										  "    ﾉｳﾀﾝ:       ｺｲ  ",
										  "    ﾉｳﾀﾝ:       ﾌﾂｳ ",
										  "    ﾉｳﾀﾝ:       ｳｽｲ ",
};
 #endif
#endif	/* (PRO_EXT_P_ONETOUCH == ENABLE) */

/*----------------------------------*
 *	ポーリング
 *----------------------------------*/
CUB	JPN_StorePollingDocument[]			= "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ ﾁｸｾｷ  ";
CUB	JPN_ErasePollingDocument[]			= "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ ｸﾘｱ   ";
CUB	JPN_PrintPollingDocument[]			= "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ ";

/*----------------------------------*
 *	親展
 *----------------------------------*/
CUB	JPN_SetSecureMailBox[]				= "ｼﾝﾃﾝ ｾｯﾄ            ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/15 */
CUB	JPN_SecureMailHoldTime[]			= "ｼﾝﾃﾝｼﾞｭｼﾝ ﾒﾓﾘｰｷｶﾝ   ";
CUB	JPN_HoldTime1_31[]					= "ﾒﾓﾘｰｷｶﾝ  (1-31):  \0 ";
#else
CUB	JPN_SecureMailHoldTime[]			= "ｼﾝﾃﾝｼﾞｭｼﾝ ﾒﾓﾘｷｶﾝ    ";
CUB	JPN_HoldTime1_31[]					= "ﾒﾓﾘｷｶﾝ   (1-31):  \0 ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB	JPN_SecureMailName[]				= " :ｼﾝﾃﾝｼｬﾒｲ \0        ";	/* 先頭1文字は、親展番号をｾｯﾄします */

/*----------------------------------*
 *	通信予約
 *----------------------------------*/
CUB	JPN_PrintStoredDocument[]			= "ﾖﾔｸｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ      ";
CUB	JPN_InputCommandNumber[]			= "ﾖﾔｸ ﾊﾞﾝｺﾞｳ:         ";
#if (PRO_CIPHER == ENABLE)
CUB	JPN_SelectDecipher[]				= "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ  :\0   ";
#endif

/*----------------------------------*
 *	ジャーナル
 *----------------------------------*/
CUB	JPN_JournalOnOff[]					= "ﾂｳｼﾝｷﾛｸ ｼﾞﾄﾞｳｾｯﾄ    ";
CUB	JPN_SelectAutoPrint[]				= "ｼﾞﾄﾞｳ ﾌﾟﾘﾝﾄ:    \0   ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	JPN_TCRSelected[]					= "ｿｳｼﾝｶｸﾆﾝｼｮｳ ｦ ｾﾝﾀｸ  ";
#else
CUB	JPN_TCRSelected[]					= "ｿｳｼﾝｼｮｳ ｦ ｾﾝﾀｸ      ";
#endif
CUB	JPN_RCRSelected[]					= "ｼﾞｭﾘｮｳｼｮｳ ｦ ｾﾝﾀｸ    ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	JPN_SetCommunicationResult[]		= "ｿｳｼﾝｶｸﾆﾝｼｮｳ ｾｯﾄ     ";
#else
CUB	JPN_SetCommunicationResult[]		= "ﾂｳｼﾝｼｮｳ ｾｯﾄ         ";
#endif

/*----------------------------------*
 *	設置モード
 *----------------------------------*/
/* カレンダー入力 */
CUB	JPN_InputTime[]						= "ｹﾞﾝｻﾞｲ ｼﾞｺｸ ｦ ﾄﾞｳｿﾞ ";

/* 夏時間切り替え */
#if defined(USA)
CUB	JPN_DayLightSaving[]				= "Daylight Saving:\0   ";
#endif

/* ＴＴＩ */
CUB	JPN_EnterYourFaxNumber[]			= "ﾊｯｼﾝﾓﾄ ﾌｧｸｽ ﾊﾞﾝｺﾞｳ  ";
CUB	JPN_EnterYourName[]					= "ﾊｯｼﾝﾓﾄ ﾒｲ           ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	JPN_EnterYourKanaName[]				= "ﾊｯｼﾝﾓﾄ ｶﾅID         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* (JPN) */

/* 回線種別 */
CUB	JPN_SelectPhoneType[]				= "ﾀﾞｲﾔﾙ ﾀｲﾌﾟ   :\0     ";
CUB	JPN_10pps[]							= "              10pps ";
CUB	JPN_20pps[]							= "              20pps ";
CUB	JPN_Tone[]							= "              ﾌﾟｯｼｭ ";
#if defined (KEISATSU)/* 警察FAX Added by SMuratec K.W.Q 2005/06/07 */
CUB	JPN_SelectKeidenPhoneType[]			= "ｹｲﾃﾞﾝ ﾀﾞｲﾔﾙ  :\0     ";
CUB	JPN_SelectKanyuPhoneType[]			= "ｶﾆｭｳ  ﾀﾞｲﾔﾙ  :\0     ";
#endif		/* End of (defined (KEISATSU)) */

#if defined (KEISATSU) /* 警察FAX Added by SMuratec K.W.Q 2005/06/07 */
extern CONST UBYTE	D2W_SelectKeidenPhoneType[];
extern CONST UBYTE	D2W_SelectKanyuPhoneType[];
#endif		/* End of (defined (KEISATSU)) */

CUB	JPN_Pulse10[]						= "              Pulse ";
CUB	JPN_Pulse20[]						= "              Pulse ";
CUB	JPN_Push[]							= "              Tone  ";

CUB	JPN_PrintSettingList[]				= "ｷｷｾｯﾃｲ ﾘｽﾄ          ";	/* ANZUのみ */

#if (PRO_MULTI_LINE == ENABLE) || (PRO_MULTI_TTI == ENABLE)	/* 多回線仕様追加 1997/09/03 Y.Matsukuma */
/* マルチ回線ユーザー設定 */
/* 注）かっこの位置は固定すること。ただし、(9)は除く。 */
CUB	JPN_MultiYourFaxNumber[]			= "ﾊｯｼﾝﾓﾄ ﾌｧｸｽﾊﾞﾝｺﾞｳ( )";
CUB	JPN_MultiYourName[]					= "ﾊｯｼﾝﾓﾄﾒｲ( )         ";
CUB	JPN_MultiYourKanaName[]				= "ｶﾅID    ( )         ";	/* (JPN) */
CUB	JPN_MultiPhoneType[]				= "ﾀﾞｲﾔﾙ ﾀｲﾌﾟ( ):\0     ";
CUB	JPN_MultiTxRx[]						= "ｿｳｼﾝ/ｼﾞｭｼﾝ( ):\0     ";
CUB	JPN_SelectTxRx[]					= "              Tx/Rx ";
CUB	JPN_SelectTx[]						= "              Tx    ";
CUB	JPN_SelectRx[]						= "              Rx    ";
CUB	JPN_MultiLineType[]					= "ﾗｲﾝ ﾀｲﾌﾟ  (9):\0     ";	/* 回線表示位置には必ず9を定義（国別の表示位置対応） */
CUB	JPN_SelectLinePstn[]				= "              ｶﾞｲｾﾝ ";
CUB	JPN_SelectLinePbx[]					= "              ﾅｲｾﾝ  ";
CUB	JPN_SetAccessNumber[]				= "ｶﾞｲｾﾝ ｾﾂｿﾞｸﾊﾞﾝｺﾞｳ( )";
#endif

/* Ｆｕｎｃｔｉｏｎ */
CUB	JPN_On1[]							= "                ON  ";	/* ﾃﾞﾌｫﾙﾄがONではじまる場合 */
CUB	JPN_Off1[]							= "                OFF ";
CUB	JPN_Off2[]							= "                OFF ";	/* ﾃﾞﾌｫﾙﾄがOFFではじまる場合 */
CUB	JPN_On2[]							= "                ON  ";
CUB	JPN_Off3[]							= "                 OFF";
CUB	JPN_On3[]							= "                 ON ";
CUB	JPN_On4[]							= "                 ON ";
CUB	JPN_Off4[]							= "                 OFF";
CUB	JPN_ModeOff[]						= "               OFF  ";
CUB	JPN_Mode1[]							= "               ﾓｰﾄﾞ1";
CUB	JPN_Mode2[]							= "               ﾓｰﾄﾞ2";
CUB	JPN_Mode3[]							= "               ﾓｰﾄﾞ3";

/*----------------------------------*
 *	ユーザー設定
 *----------------------------------*/
/* 読み取りパラメータ */
/* 原稿読みとり幅 */
CUB	JPN_SelectScanWidth[]				= "ﾖﾐﾄﾘ ｻｲｽﾞ   :    \0  ";
CUB	JPN_ScanA4[]						= "                 A4 ";
CUB	JPN_ScanB4[]						= "                 B4 ";
CUB	JPN_ScanA3[]						= "                 A3 ";

/* 優先モード */
CUB	JPN_SelectPrimaryMode[]				= "ﾕｳｾﾝ ﾓｼﾞ:\0          ";
CUB	JPN_PrimaryModeNormal[]				= "           ﾋｮｳｼﾞｭﾝ  ";
CUB	JPN_PrimaryModeFine[]				= "           ｺｳｶﾞｼﾂ   ";
CUB	JPN_PrimaryModeSFine[]				= "           ﾁｮｳｺｳｶﾞｼﾂ";
CUB	JPN_PrimaryModeGray[]				= "           ｼｬｼﾝ     ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	JPN_PrimaryModeFine_S[]				= "           ｺﾏｶｲ     ";
CUB	JPN_PrimaryModeSFine_S[]			= "           ｾｲｻｲ     ";
#endif

/* 優先原稿濃度 */
CUB	JPN_SelectPrimaryContrast[]			= "ﾖﾐﾄﾘ ﾉｳﾄﾞ   :\0      ";
CUB	JPN_PrimaryContrastLight[]			= "             ｳｽｸ    ";
CUB	JPN_PrimaryContrastLittleLight[]	= "             ﾔﾔ ｳｽｸ ";
CUB	JPN_PrimaryContrastNormal[]			= "             ﾌﾂｳ    ";
CUB	JPN_PrimaryContrastLittleDark[]		= "             ﾔﾔ ｺｸ  ";
CUB	JPN_PrimaryContrastDark[]			= "             ｺｸ     ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	JPN_SelectPrimaryContrast_S[]		= "ﾖﾐﾄﾘ ﾉｳﾀﾝ   :\0      ";
CUB	JPN_PrimaryContrastLight_S[]		= "             ｺｲ     ";
CUB	JPN_PrimaryContrastDark_S[]			= "             ｳｽｲ    ";
#endif

#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	JPN_SetScanParameters[]				= "ｽｷｬﾅ ﾊﾟﾗﾒｰﾀｰ ｾｯﾄ    ";
#else
CUB	JPN_SetScanParameters[]				= "ｽｷｬﾅ ﾊﾟﾗﾒｰﾀ ｾｯﾄ     ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* プリントパラメータ */
CUB	JPN_SelectReceiveReduction[]		= "ｼｭｸｼｮｳﾘﾂ:     \0     ";
CUB	JPN_AutoReduction[]					= "              ｼﾞﾄﾞｳ ";
CUB	JPN_100[]							= "              100%  ";
CUB	JPN_97[]							= "               97%  ";
CUB	JPN_91[]							= "               91%  ";
CUB	JPN_81[]							= "               81%  ";
CUB	JPN_75[]							= "               75%  ";
CUB	JPN_InputThresholdValue0_85[]		= "ｼｷｲﾁ  (0-85mm):   \0 ";
CUB	JPN_SelectPageCompound[]			= "ﾍﾟｰｼﾞ ｺﾞｳｾｲ    : \0  ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	JPN_SetPrintParameters[]			= "ﾌﾟﾘﾝﾄ ﾊﾟﾗﾒｰﾀｰ ｾｯﾄ   ";
#else
CUB	JPN_SetPrintParameters[]			= "ﾌﾟﾘﾝﾄ ﾊﾟﾗﾒｰﾀ ｾｯﾄ    ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if (PRO_ROTATE == ENABLE)
CUB	JPN_SetRotateMargin[]				= "ｶｲﾃﾝ ｼﾞｭｼﾝ          ";
#endif

/* コピーパラメータ */
CUB	JPN_SelectSortingCopy[]				= "ｿｰﾃｨﾝｸﾞｺﾋﾟｰ:    \0   ";
CUB	JPN_SelectCopyReduction[]			= "ｼｭｸｼｮｳﾘﾂ:     \0     ";	/* POPLAR_B以外 */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	JPN_SetCopyParameters[]				= "ｺﾋﾟｰ ﾊﾟﾗﾒｰﾀｰ ｾｯﾄ    ";	/* POPLAR_B以外 */
#else
CUB	JPN_SetCopyParameters[]				= "ｺﾋﾟｰ ﾊﾟﾗﾒｰﾀ ｾｯﾄ     ";	/* POPLAR_B以外 */
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* 記録紙サイズ */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
CUB	JPN_EnterPaperSize[]				= "ｷﾛｸｼｻｲｽﾞ:    \0      ";
CUB	JPN_PaperSizeNone[]					= "             None   ";
CUB	JPN_PaperSizeA4[]					= "             A4     ";
CUB	JPN_PaperSizeB4[]					= "             B4     ";
CUB JPN_PaperSizeLetter[]				= "             Letter ";
CUB	JPN_PaperSizeLegal[]				= "             Legal  ";
CUB	JPN_PaperSizeF4[]					= "             F4     ";
CUB	JPN_SetPaperSize[]					= "ｷﾛｸﾍﾟｰﾊﾟｰｻｲｽﾞｾｯﾄ    ";

 #if (PRO_PC_PRINT == ENABLE)	/* ＰＣプリント */
CUB	JPN_SelectPaperSizeNone[]			= "             None   ";	/* 不要かもしれない */
CUB	JPN_SelectPaperSizeA5[]				= "             A5_P   ";
  #if defined(USA)
CUB	JPN_SelectPaperSizeLetter[]			= "             Letter ";
  #else
CUB	JPN_SelectPaperSizeLetter[]			= "             Ltr_P  ";
  #endif
  #if defined(USA)
CUB	JPN_SelectPaperSizeA4[]				= "             A4_P   ";
  #else
CUB	JPN_SelectPaperSizeA4[]				= "             A4     ";
  #endif
  #if defined(USA) || defined(TWN) /* 1998/01/09 Y.Matsukuma */
CUB	JPN_SelectPaperSizeLegal[]			= "             Legal  ";
  #else
CUB	JPN_SelectPaperSizeLegal[]			= "             Legal_P";
  #endif
CUB	JPN_SelectPaperSizeB5R[]			= "             B5R_P  ";
CUB	JPN_SelectPaperSizeB4[]				= "             B4_P   ";
CUB	JPN_SelectPaperSizeA3[]				= "             A3_P   ";
CUB	JPN_SelectPaperSizeA4R[]			= "             A4R_P  ";
CUB	JPN_SelectPaperSizeLetterR[]		= "             LtrR_P ";
  #if defined(TWN) || defined(AUS)	/* 1998/01/09 Y.Matsukuma */
CUB	JPN_SelectPaperSizeF4[]				= "             F4     ";
  #else
CUB	JPN_SelectPaperSizeF4[]				= "             F4_P   ";
  #endif
CUB	JPN_SelectPaperSizeA5R[]			= "             A5R_P  ";
CUB	JPN_SelectPaperSizePostcard[]		= "             Post_P ";
CUB	JPN_SelectPaperSizeLD[]				= "             Ld_P   ";
CUB	JPN_SelectPaperSizeGLetterR[]		= "             GLtrR_P";
CUB	JPN_SelectPaperSizeExecutiveR[]		= "             ExeR_P ";
CUB	JPN_SelectPaperSizeInvoiceR[]		= "             InvR_P ";
CUB	JPN_SelectPaperSizeGLegal[]			= "             GLegl_P";
CUB	JPN_SelectPaperSizeGLetter[]		= "             GLtr_P ";
CUB	JPN_SelectPaperSizeCard[]			= "             Card_P ";
CUB	JPN_SelectPaperSizeExecutive[]		= "             Exe_P  ";
CUB	JPN_SelectPaperSizeB5[]				= "             B5_P   ";
CUB	JPN_SelectPaperSizeC5[]				= "             C5_P   ";
CUB	JPN_SelectPaperSizeHalfLetter[]		= "             HLtr_P ";
CUB	JPN_SelectPaperSizeInvoice[]		= "             Inv_P  ";
CUB	JPN_SelectPaperSizeB6[]				= "             B6_P   ";
CUB	JPN_SelectPaperSizeDL[]				= "             DL_P   ";
CUB	JPN_SelectPaperSizeCM10[]			= "             CM10_P ";
CUB	JPN_SelectPaperSizeA6[]				= "             A6_P   ";
CUB	JPN_SelectPaperSizeMonarch[]		= "             Mnc_P  ";
CUB	JPN_SelectPaperSize35[]				= "             3x5_P  ";
CUB	JPN_SelectPaperSizeUser[]			= "             User_P ";
 #endif
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */

/* コピー禁止 */
CUB	JPN_SelectCopyProtect[]				= "ｺﾋﾟｰｷﾝｼ        :\0   ";

/* ポーズ */
CUB	JPN_SetDialingPause[]				= "ﾎﾟｰｽﾞｼﾞｶﾝ ｾｯﾄ       ";
CUB	JPN_PauseTime[]						= "ｼﾞｶﾝ        :\0      ";	/* 注）ｼﾞｶﾝ (05-10): の（）の部分は実行時に作成します */

/* べル回数 */
CUB	JPN_SetNumberOfRings[]				= "ﾖﾋﾞﾀﾞｼﾍﾞﾙｶｲｽｳｾｯﾄ    ";
CUB	JPN_NumberOfRings[]					= "ｶｲｽｳ        :\0      ";	/* 注）ｶｲｽｳ   (1-9): の（）の部分は実行時に作成します */

/* リダイアル */
CUB	JPN_RedialCount[]					= "ｶｲｽｳ        :\0      ";	/* 注）ｶｲｽｳ (02-10): の（）の部分は実行時に作成します */
CUB	JPN_SetNumberOfRedials[]			= "ﾘﾀﾞｲﾔﾙｶｲｽｳ ｾｯﾄ      ";
CUB	JPN_RedialInterval[]				= "ｶﾝｶｸ        :\0      ";	/* 注）ｶﾝｶｸ   (1-5): の（）の部分は実行時に作成します */
CUB	JPN_SetRedialInterval[]				= "ﾘﾀﾞｲﾔﾙｶﾝｶｸ ｾｯﾄ      ";
CUB	JPN_SetRedial[]						= "ﾘﾀﾞｲﾔﾙ ｾｯﾄ          ";

/* ECM */
CUB	JPN_SelectECMMode[]					= "ECM ﾓｰﾄﾞ:       \0   ";
CUB	JPN_SetECMMode[]					= "ECM ﾓｰﾄﾞ ｾｯﾄ        ";

/* パスコード */
CUB	JPN_SetPasscode[]					= "ﾊﾟｽｺｰﾄﾞ ｾｯﾄ         ";

/* 閉域通信設定 */
CUB	JPN_SelectClosedNetwork[]			= "ﾍｲｲｷ ﾂｳｼﾝ:      \0   ";
CUB	JPN_SetClosedNetwork[]				= "ﾍｲｲｷﾂｳｼﾝ ｾｯﾄ        ";

/* パスワード送信 */
CUB	JPN_SelectSecurityTransmission[]	= "ﾊﾟｽﾜｰﾄﾞ ｿｳｼﾝ:   \0   ";
CUB	JPN_SetSecurityTransmission[]		= "ﾊﾟｽﾜｰﾄﾞ ｿｳｼﾝ ｾｯﾄ    ";

/* ダイレクトメール防止 */
CUB	JPN_SelectBlockJunkMail[]			= "ﾀﾞｲﾚｸﾄﾒｰﾙ ﾎﾞｳｼ:\0    ";
CUB	JPN_SetBlockJunkMailDial[]			= "ﾀﾞｲﾚｸﾄﾒｰﾙ ﾀﾞｲﾔﾙ ｾｯﾄ ";
CUB	JPN_PrintBlockJunkMailDialList[]	= "ﾀﾞｲﾚｸﾄﾒｰﾙ ﾀﾞｲﾔﾙ ﾘｽﾄ ";
CUB	JPN_SetBlockJunkMail[]				= "ﾀﾞｲﾚｸﾄﾒｰﾙ ﾎﾞｳｼ      ";
CUB	JPN_BlockJunkMailSelectNumber[]		= "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ ";
CUB JPN_SetSameNumber[]					= "ﾊﾞﾝｺﾞｳ ｶﾞ ﾄｳﾛｸｻﾚﾃｲﾏｽ";

/* リモート診断 */
CUB	JPN_SelectRemoteDiagnostic[]		= "ｻｰﾋﾞｽﾓｰﾄﾞ:      \0   ";
CUB	JPN_SetRemoteDiagnostic[]			= "ｻｰﾋﾞｽﾓｰﾄﾞ ｾｯﾄ       ";

/* メモリー送信 */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/15 */
CUB	JPN_SelectMemoryTransmission[]		= "ﾒﾓﾘｰｿｳｼﾝ:       \0   ";
CUB	JPN_SetMemoryTransmission[]			= "ﾒﾓﾘｰｿｳｼﾝ ｾｯﾄ        ";
#else
CUB	JPN_SelectMemoryTransmission[]		= "ﾒﾓﾘｿｳｼﾝ:        \0   ";
CUB	JPN_SetMemoryTransmission[]			= "ﾒﾓﾘｿｳｼﾝ ｾｯﾄ         ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* サイレントオペレーション */
CUB	JPN_SelectSilentOperation[]			= "ｻｲﾚﾝﾄ ｵﾍﾟﾚｰｼｮﾝ: \0   ";
CUB	JPN_SetSilentOperation[]			= "ｻｲﾚﾝﾄ ｵﾍﾟﾚｰｼｮﾝ ｾｯﾄ  ";

/* プロテクトパスコード */
CUB	JPN_SetProtectPasscode[]			= "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｾｯﾄ      ";
CUB	JPN_ProtectPasscode[]				= "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ          ";

/* オペレーションプロテクト */
CUB	JPN_OperationProtectOnOff[]			= "ｵﾍﾟﾚｰｼｮﾝ ﾌﾟﾛﾃｸﾄ:\0   ";
CUB	JPN_SetOperationProtect[]			= "ｵﾍﾟﾚｰｼｮﾝ ﾌﾟﾛﾃｸﾄ ｾｯﾄ ";

/* ＰＩＮアクセスモードセット */
CUB	JPN_PINAccessMode[]					= "PIN ﾓｰﾄﾞ:      \0    ";
CUB	JPN_SetPINAccessMode[]				= "PIN ﾓｰﾄﾞ ｾｯﾄ        ";

/* リングマスター */
#if (PRO_RING_MASTER == ENABLE)	/* by K.Watanabe 1998/08/18 */
CUB	JPN_SelectRingMaster[]				= "ﾘﾝｸﾞﾏｽﾀｰ:       \0   ";
CUB	JPN_SelectRingPattern[]				= "ﾘﾝｸﾞﾊﾟﾀｰﾝ:        \0 ";
CUB	JPN_RingPattern_A[]					= "                  A ";
CUB	JPN_RingPattern_B[]					= "                  B ";
CUB	JPN_RingPattern_C[]					= "                  C ";
CUB	JPN_RingPattern_D[]					= "                  D ";
CUB	JPN_RingPattern_E[]					= "                  E ";
CUB	JPN_RingPattern_F[]					= "                  F ";
CUB	JPN_RingPattern_G[]					= "                  G ";
CUB	JPN_RingPattern_H[]					= "                  H ";
CUB	JPN_SetRingMaster[]					= "ﾘﾝｸﾞﾏｽﾀｰ ｾｯﾄ        ";
#endif

/* 済みスタンプ */
CUB	JPN_StampOnOff[]					= "ｽﾐｽﾀﾝﾌﾟ     :   \0   ";
CUB	JPN_SetStamp[]						= "ｽﾐｽﾀﾝﾌﾟ ｾｯﾄ         ";

/* ドラム寿命リセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* by K.Watanabe 1998/08/18 */
CUB	JPN_ResetDrumLife[]					= "ﾄﾞﾗﾑ ﾗｲﾌ ｶｳﾝﾀ ｸﾘｱ   ";
#endif

/* 受信アラームセット */
#if defined(GBR)
CUB	JPN_RxAlarm[]						= "Audible Alarm:  \0   ";
CUB	JPN_SetRxAlarm[]					= "Set Rx Alarm        ";
#endif

/*----------------------------------*
 *	マーキュリー
 *----------------------------------*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
 #if(PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)
/* マーキュリー番号  */
CUB	JPN_MercuryNumberSet[]				= "ﾀﾞｲﾔﾙ ﾌﾟﾚﾌｨｸｽ ﾅﾝﾊﾞｰ ";
/* マーキュリーポーズ  */
CUB	JPN_MercuryPauseSet[]				= "Mercury Pause Set   ";
CUB	JPN_SetMercury[]					= "ﾀﾞｲﾔﾙ ﾌﾟﾚﾌｨｸｽ ｾｯﾄ   ";
 #else
/* マーキュリー番号  */
CUB	JPN_MercuryNumberSet[]				= "ﾏｰｷｭﾘｰ ﾊﾞﾝｺﾞｳ       ";
/* マーキュリーポーズ  */
CUB	JPN_MercuryPauseSet[]				= "Mercury Pause Set   ";
CUB	JPN_SetMercury[]					= "ﾏｰｷｭﾘｰ ｾｯﾄ          ";
 #endif
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* 保留メロディーセット */
CUB	JPN_SelectHoldMelody[]				= "ﾎﾘｭｳ ﾒﾛﾃﾞｨ     :\0   ";
#endif

/* リモート受信 */
#if (PRO_REMOTE_RX == ENABLE)			/* ＮＴＴ仕様のポプラＬで使用 98/01/26 T.Fukumoto */
CUB	JPN_SelectRemoteReceive[]			= "ﾘﾓｰﾄ ｼﾞｭｼﾝ     :\0   ";
#endif

/* オンフック受信 */
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	JPN_SelectOnHookReceive[]			= "ｵﾝﾌｯｸ ｼﾞｭｼﾝ    :\0   ";	/* 98/03/13 Add By T.Fukumoto */
#endif

/* ダイアルイン */
#if (PRO_DIALIN == ENABLE)
CUB	JPN_SetDialIn[]						= "ﾀﾞｲﾔﾙｲﾝ ｾｯﾄ         ";
CUB	JPN_DialInFax[]						= "ﾌｧｸｽ:           \0   ";

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ＨＩＮＯＫＩは本体の刻印にあわせます。 By O.Kimoto 1999/02/09 */
CUB	JPN_DialInTel1[]					= "PHONE1:         \0   ";
CUB	JPN_DialInTel2[]					= "PHONE2:         \0   ";
#else
CUB	JPN_DialInTel1[]					= "ﾎﾝﾀｲﾃﾞﾝﾜ:       \0   ";
CUB	JPN_DialInTel2[]					= "ｿﾞｳｾﾂﾃﾞﾝﾜ:      \0   ";
#endif

CUB	JPN_DialInRings[]					= "ﾍﾞﾙｼﾞｶﾝ ｾｯﾄ         ";
CUB	JPN_DialInRings10_60[]				= "(10-60)      \0      ";
#endif

/*----------------------------------*
 *	カバーページ
 *----------------------------------*/
CUB	JPN_MessageOnOff[]					= "ﾒｯｾｰｼﾞ:         \0   ";
CUB	JPN_MessageTx[]						= "ﾒｯｾｰｼﾞ ｿｳｼﾝ         ";
CUB	JPN_SetCoverPageMessage[]			= "ﾒｯｾｰｼﾞ              ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	JPN_MessageSet[]					= "ﾒｯｾｰｼﾞ ｾｯﾄ          ";

/*----------------------------------*
 *	枚数設定
 *----------------------------------*/
CUB	JPN_InputPageCount[]				= "ｹﾞﾝｺｳ ﾏｲｽｳ ｦ ﾄﾞｳｿﾞ  ";

#if defined(POPLAR_F)
 #if defined(JP1)
	CUB	JPN_PageCount1_30[]					= "ｹﾞﾝｺｳ ﾏｲｽｳ (1-50):\0 ";
 #else
	CUB	JPN_PageCount1_30[]					= "ｹﾞﾝｺｳ ﾏｲｽｳ (1-30):\0 ";
 #endif
#else
 #if defined(POPLAR_N) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ポプラＬ（ＮＴＴ仕様） by K.Watanabe 1998/03/16 */
	CUB	JPN_PageCount1_30[]					= "ｹﾞﾝｺｳ ﾏｲｽｳ (1-30):\0 ";
 #else
	CUB	JPN_PageCount1_30[]					= "ｹﾞﾝｺｳ ﾏｲｽｳ (1-50):\0 ";
 #endif
#endif

/*----------------------------------*
 *	部門管理
 *----------------------------------*/
/* 部門管理プロテクトセット */
CUB	JPN_DepartmentProtect[]				= "ﾌﾞﾓﾝｶﾝﾘ ﾌﾟﾛﾃｸﾄ: \0   ";
CUB	JPN_SetDepartmentProtect[]			= "ﾌﾞﾓﾝｶﾝﾘ ﾌﾟﾛﾃｸﾄ ｾｯﾄ  ";

/* 部門コードセット */
CUB	JPN_DepartmentSelectNumber[]		= "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ ";

/* 部門管理セット */
CUB	JPN_DepartmentOnOff[]				= "ﾌﾞﾓﾝｶﾝﾘ:        \0   ";
CUB	JPN_SetDepartmentOnOff[]			= "ﾌﾞﾓﾝｶﾝﾘ ｾｯﾄ         ";

#if (PRO_DEPART_NEW_LIST == ENABLE)		/* 追記 By S.Fukui Jan.7,1998 */
/* 簡易部門毎時間管理リスト関連 */
CUB	JPN_EraseDepartTimeListMode[]		= "ﾌﾞﾓﾝｶﾝﾘﾘｽﾄ ｼｮｳｷｮ    ";
CUB	JPN_EraseDepartCode[]				= "    :ﾌﾞﾓﾝｺｰﾄﾞ ｼｮｳｷｮ ";	/* 先頭４文字は部門ｺｰﾄﾞ表示 */
CUB JPN_DepartCodeFull[]				= "ﾄｳﾛｸ ﾊ 100ｹﾝ ﾏﾃﾞﾃﾞｽ ";
#endif

/*----------------------------------*
 *	一括送信
 *----------------------------------*/
CUB	JPN_SelectBatchBoxNumber[]			= "ﾎﾞｯｸｽ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ  ";
CUB	JPN_TranssmissionTime[]				= "ｿｳｼﾝ ｼﾞｶﾝ           ";
CUB	JPN_EraseBatchBoxMode[]				= "ｲｯｶﾂ ｿｳｼﾝ ﾎﾞｯｸｽ ｸﾘｱ ";
CUB	JPN_EraseBatchDocumentMode[]		= "ｲｯｶﾂ ｿｳｼﾝ ｹﾞﾝｺｳ ｸﾘｱ ";

CUB	JPN_PrintBatchBoxMode[]				= "ｲｯｶﾂ ｿｳｼﾝ ﾎﾞｯｸｽ ﾘｽﾄ ";
CUB	JPN_PrintBatchDocListMode[]			= "ｲｯｶﾂ ｿｳｼﾝ ｹﾞﾝｺｳ ﾘｽﾄ ";
CUB	JPN_PrintBatchDocMode[]				= "ｲｯｶﾂｿｳｼﾝ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ";
CUB	JPN_BatchBoxNumber[]				= "ﾎﾞｯｸｽ ﾊﾞﾝｺﾞｳ:     \0 ";
CUB	JPN_BatchFileNumber[]				= "ﾌｧｲﾙ ﾊﾞﾝｺﾞｳ:     \0  ";

/*----------------------------------*
 *	セキュリティ受信
 *----------------------------------*/
/* セキュリティ受信セット */
CUB	JPN_SecurityReceive[]				= "ｾｷｭﾘﾃｨ ｼﾞｭｼﾝ:   \0   ";
CUB	JPN_SetSecurityReceive[]			= "ｾｷｭﾘﾃｨ ｼﾞｭｼﾝ ｾｯﾄ    ";

/* メモリ受信原稿プリント */
CUB	JPN_PrintMemoryReceiveDocMode[]		= "ｼﾞｭｼﾝ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ   ";

/*----------------------------------*
 *	Ｆコード
 *----------------------------------*/
#if (PRO_F_CODE == ENABLE)
CUB	JPN_SelectFcodeBoxNumber[]			= "ﾎﾞｯｸｽ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ  ";
CUB	JPN_EnterFcodeBoxName[]				= "  :ﾎﾞｯｸｽﾒｲ \0        ";
CUB	JPN_EnterFcodeSubAddress[]			= "  :ｻﾌﾞｱﾄﾞﾚｽ ﾊﾞﾝｺﾞｳ  ";
CUB	JPN_EnterFcodePassword[]			= "  :ﾊﾟｽﾜｰﾄﾞ ﾊﾞﾝｺﾞｳ   ";
CUB	JPN_SelectFcodeBoxKind[]			= "ﾎﾞｯｸｽ ｼｭﾍﾞﾂ:\0       ";  /* modified by honda 1997/09/18  NULLの位置を左に1ｼﾌﾄ */
CUB	JPN_FcodeBulletinBoardBox[]			= "            ｹｲｼﾞﾊﾞﾝ ";
CUB	JPN_FcodeConfidentialBox[]			= "            ｼﾝﾃﾝ    ";
#if (PRO_FCODE_RELAY == ENABLE)	/* By H.Fujimura 1999/01/21 */
CUB	JPN_FcodeRelayBox[]					= "            ﾁｭｳｹｲ   ";
#endif
CUB	JPN_SelectFcodeRxProhibition[]		= "ｼﾞｭｼﾝ ｷﾝｼ      :\0   ";
CUB	JPN_SelectFcodeRxDocPrint[]			= "ﾄﾞｳｼﾞ ﾌﾟﾘﾝﾄ    :\0   ";
CUB	JPN_SelectFcodeRxDocUpperWrite[]	= "ｹﾞﾝｺｳ ｳﾜｶﾞｷ    :\0   ";
CUB	JPN_SelectFcodeTxDocClear[]			= "ｿｳｼﾝ ｹﾞﾝｺｳ ｸﾘｱ :\0   ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/15 */
CUB	JPN_FcodeDocumentHoldTime[]			= "ｹﾞﾝｺｳ ﾒﾓﾘｰｷｶﾝ       ";
CUB	JPN_HoldTime0_31[]					= "ﾒﾓﾘｰｷｶﾝ  (0-31):  \0 ";
#else
CUB	JPN_FcodeDocumentHoldTime[]			= "ｹﾞﾝｺｳ ﾒﾓﾘｷｶﾝ        ";
CUB	JPN_HoldTime0_31[]					= "ﾒﾓﾘｷｶﾝ   (0-31):  \0 ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB	JPN_SelectFcodeStoreDocAdd[]		= "ｹﾞﾝｺｳ ﾂｲｶ      :\0   ";
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/11/13 */
CUB	JPN_StoreFcodeDocument[]			= "ｹﾞﾝｺｳ ﾁｸｾｷ F:       ";
#else
CUB	JPN_StoreFcodeDocument[]			= "ｹﾞﾝｺｳ ﾁｸｾｷ   ﾌｧｲﾙ:  ";
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
 #if (PRO_FCODE_RELAY == ENABLE)	/* By H.Fujimura 1999/01/21 */
CUB	JPN_InputRelayNumber[]				= "ﾊｲｼﾝｻｷ ｦ ﾄﾞｳｿﾞ      ";
CUB JPN_SetRelayTTI[][21]				= {
										  "ﾊｲｼﾝｼﾞ ﾊｯｼﾝﾓﾄ:\0     ",
										  "              ﾂｹﾅｲ  ",
										  "              ｿﾄﾂﾞｹ ",
										  "              ｳﾜｶﾞｷ ",
};
 #endif
#endif
CUB	JPN_SameNumber[]					= "ﾊﾞﾝｺﾞｳ ｶﾞ ﾄｳﾛｸｻﾚﾃｲﾏｽ";

/*----------------------------------*
 *	ＰＣプリントボード初期化
 *----------------------------------*/
#if (PRO_PC_PRINT == ENABLE)
CUB	JPN_BoardReset[]					= "ﾌﾟﾘﾝﾀｵﾌﾟｼｮﾝ ﾘｾｯﾄ    ";
#endif

/*----------------------------------*
 *	暗号化
 *----------------------------------*/
#if (PRO_CIPHER == ENABLE)
CUB	JPN_EnterCipherKeyName[]			= " :ｷｰﾜｰﾄﾞ ﾒｲ\0        ";	/* "ｷｰﾊﾞﾝｸ ﾒｲ" → "ｷｰﾜｰﾄﾞ ﾒｲ" by K.Watanabe 1998/04/27 */
CUB	JPN_EnterCipherKey[]				= " :ｷｰﾜｰﾄﾞ   \0        ";
CUB	JPN_EnterCipherKeyClue[]			= " :ｷｰﾜｰﾄﾞﾋﾝﾄ\0        ";
CUB	JPN_InputCipherRxDocNumber[]		= "ｼﾞｭｼﾝ ﾊﾞﾝｺﾞｳ     :\0 ";
CUB	JPN_InputCipherExtensionKey[]		= "ﾀﾞﾌﾞﾙｶﾞｰﾄﾞ      :\0  ";
CUB	JPN_SelectCipherDocErrRemoval[]		= "ｴﾗｰ ｼｭｳｾｲ      :\0   ";
CUB	JPN_SelectCipherKeySetKind[]		= "ｷｰﾜｰﾄﾞ ｾｯﾄ  :\0      ";
CUB	JPN_CipherKeySetDefault[]			= "             ﾃﾞﾌｫﾙﾄ ";
CUB	JPN_CipherKeySetKeyBook[]			= "             ｷｰﾊﾞﾝｸ ";
CUB	JPN_CipherKeySetDirect[]			= "             ﾁｮｸｾﾂ  ";
CUB	JPN_InputCipherDefaultKeyNo[]		= "ｷｰﾜｰﾄﾞﾊﾞﾝｺﾞｳ(0-9):\0 ";
 #if defined(USA)
CUB	JPN_InputServiceLabelPosition[]		= "ｵﾌｾｯﾄ (1-14.5\"):\0   ";  /* by t.fukumoto 1997/12/12 */
 #else
CUB	JPN_InputServiceLabelPosition[]		= "ｵﾌｾｯﾄ   (2-36cm):\0  ";
 #endif
CUB	JPN_CipherSelectNumber[]			= "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ ";
CUB	JPN_CipherExecute[]					= "ｽｸﾗﾝﾌﾞﾙ        99/99";
CUB	JPN_DecipherExecute[]				= "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ  99/99";
CUB	JPN_CipherExecuteError[]			= "ｽｸﾗﾝﾌﾞﾙ ｴﾗｰ         ";
CUB	JPN_DecipherExecuteError[]			= "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ｴﾗｰ   ";
CUB	JPN_DecipherKeyError[]				= "ｷｰﾜｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ    ";
CUB	JPN_ConfirmDecipherContinue[]		= "ｶｲｼﾞｮ ｹｲｿﾞｸ ｾｯﾄ/ｸﾘｱ ";
CUB	JPN_DecipherDocument[]				= "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ｹﾞﾝｺｳ ";
CUB	JPN_StopCipherExecute[]				= "ｽｸﾗﾝﾌﾞﾙ ﾁｭｳｼ        ";
CUB	JPN_StopDecipherExecute[]			= "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ﾁｭｳｼ  ";
#endif
CUB	JPN_InputPrintPageNumber[]			= "ﾌﾞｽｳ      (1-99):\0  ";
CUB	JPN_ProgressRate[]					= " 0%            100% ";

/*----------------------------------*
 *	クラス１
 *----------------------------------*/
CUB	JPN_SetRS232CParameter[]			= "RS232C ｾｯﾄ          ";
CUB	JPN_SetRS232CPCFaxInitial[]			= "PC-FAX ｼｮｷｶ         ";

/* ＲＳ２３２Ｃボーレート */
CUB	JPN_SelectRS232CBaudRate[]			= "ﾎﾞｰﾚｲﾄ    :\0        ";
CUB	JPN_RS232CVariable[]				= "           ｼﾞﾄﾞｳ    ";
CUB	JPN_RS232C600bps[]					= "             600bps ";
CUB	JPN_RS232C1200bps[]					= "            1200bps ";
CUB	JPN_RS232C2400bps[]					= "            2400bps ";
CUB	JPN_RS232C4800bps[]					= "            4800bps ";
CUB	JPN_RS232C9600bps[]					= "            9600bps ";
CUB	JPN_RS232C19200bps[]				= "           19200bps ";

/* ＲＳ２３２Ｃパリティビット設定 */
CUB	JPN_SelectParity[]					= "ﾊﾟﾘﾃｨ         :\0    ";
CUB	JPN_RS232CNone[]					= "               None ";
CUB	JPN_RS232COdd[]						= "               Odd  ";
CUB	JPN_RS232CEven[]					= "               Even ";

/* ＲＳ２３２Ｃストップビット設定 */
CUB	JPN_Select232CStopBit[]				= "ｽﾄｯﾌﾟﾋﾞｯﾄ    :\0     ";
CUB	JPN_RS232C1bit[]					= "              1 bit ";
CUB	JPN_RS232C2bit[]					= "              2 bit ";

/* ＲＳ２３２Ｃデータ長設定 */
CUB	JPN_Select232CDataLength[]			= "ﾃﾞｰﾀ ﾁｮｳ     :\0     ";
CUB	JPN_RS232C7bit[]					= "              7 bit ";
CUB	JPN_RS232C8bit[]					= "              8 bit ";

/* クラス１関連追加 */
CUB	JPN_PC_FAX_Scan[]					= "PC-FAX ﾛｰｶﾙｽｷｬﾝ     ";
CUB	JPN_PC_FAX_Print[]					= "PC-FAX ﾌﾟﾘﾝﾄ        ";
CUB	JPN_PC_FAX_Connect[]				= "PC-FAX ｾﾂｿﾞｸ        ";
CUB	JPN_PC_FAX_InitialError[]			= "PC-FAX ｼｮｷｶ ｴﾗｰ     ";
CUB	JPN_PC_FAX_Complete[]				= " ** PC-FAX ｶﾝﾘｮｳ ** ";
CUB	JPN_PC_FAX_InUse[]					= "PC-FAX ｼﾖｳﾁｭｳ       "; /* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
CUB	JPN_ReceiveInFax[]					= "FAX ｼﾞｭｼﾝ ｼﾏｽｶ ?    "; /* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */

/* 送信時、部門コード入力 */
CUB	JPN_EnterDepartmentCode[]			= "ﾌﾞﾓﾝｶﾝﾘ ｺｰﾄﾞ ｦ ﾄﾞｳｿﾞ";

/* 送信時、ダイヤル番号入力 */
CUB	JPN_EnterDialNumber[]				= "ﾀﾞｲﾔﾙ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ";

/* 送信時、ＰＩＮ番号入力 */
CUB	JPN_EnterPinNumber[]				= "PIN ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ  ";

/************************************************
** Dial-UpｲﾝﾀｰﾈｯﾄFAX関係	1998/03/12 by K.Okada
************************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/** ユーザ登録 */
CUB JPN_EMailSettingMode[]				= "  ﾒｰﾙ ｿｳｼﾞｭｼﾝ ｾｯﾃｲ  ";
CUB JPN_SetUserDataMode[]				= "   ﾕｰｻﾞﾃﾞｰﾀ ﾄｳﾛｸ    ";
CUB JPN_SetUserData[]					= "ﾕｰｻﾞﾃﾞｰﾀ ﾄｳﾛｸ       ";
/*↓この2つはこの順番で並べて記述*/
CUB JPN_NewEntry[]						= "ｼﾝｷ ﾄｳﾛｸ?           ";
CUB JPN_UpdateSetting[]					= "ﾄｳﾛｸﾅｲﾖｳ ﾍﾝｺｳ?      ";
CUB JPN_NewMailBox[]					= "ﾒｰﾙﾎﾞｯｸｽ ﾍﾝｺｳ? :\0   ";
/*↓この2つはこの順番で並べて記述*/
CUB JPN_No[]							= "                ｲｲｴ ";
CUB JPN_Yes[]							= "                ﾊｲ  ";
CUB JPN_UserCodeNumber[]				= "ｺｰﾄﾞ ﾊﾞﾝｺﾞｳ         ";
CUB JPN_UserCodeNumberAgain[]			= "ｻｲﾆｭｳﾘｮｸ            ";
CUB JPN_EnterYourCodeNumber[]			= "ｺｰﾄﾞ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ ";
CUB JPN_ISP_Name[]						= "ﾌﾟﾛﾊﾞｲﾀﾞ ﾒｲ         ";
CUB JPN_AccessPoint[]					= "ｱｸｾｽﾎﾟｲﾝﾄ           ";
/*↓この3つはこの順番で並べて記述*/
CUB JPN_1stTime[]						= ":1ｶｲﾒ \0             ";
CUB JPN_2ndTime[]						= ":2ｶｲﾒ \0             ";
CUB JPN_3rdTime[]						= ":3ｶｲﾒ \0             ";
CUB JPN_UserName[]						= "ﾅﾏｴ                 ";
CUB JPN_PPP_LoginID[]					= "PPP ﾛｸﾞｲﾝID         ";
CUB JPN_POP_LoginID[]					= "POP ﾛｸﾞｲﾝID         ";
/*↓この2つはこの順番で並べて記述*/
CUB JPN_PPP_Password[]					= "PPP ﾊﾟｽﾜｰﾄﾞ         ";
CUB JPN_PPP_PasswordAgain[]				= "ｻｲﾆｭｳﾘｮｸ            ";
/*↓この2つはこの順番で並べて記述*/
CUB JPN_POP_Password[]					= "POP ﾊﾟｽﾜｰﾄﾞ         ";
CUB JPN_POP_PasswordAgain[]				= "ｻｲﾆｭｳﾘｮｸ            ";
CUB JPN_MailAddress[]					= "ｱﾄﾞﾚｽ               ";
CUB JPN_PPP_Auth[]						= "PPP ﾆﾝｼｮｳﾎｳｼｷ       ";
/*↓この3つはこの順番で並べて記述*/
CUB JPN_PPP_PAP[]						= ":PAP  \0             ";
CUB JPN_PPP_CHAP[]						= ":CHAP \0             ";
CUB JPN_PPP_NoneAuth[]					= ":ﾅｼ   \0             ";
CUB JPN_Client[]						= "ｸﾗｲｱﾝﾄ              ";
CUB JPN_ISP_Server[]					= "ｻｰﾊﾞ                ";
CUB JPN_Gateway[]						= "ｹﾞｰﾄｳｪｲ             ";
CUB JPN_DNS_Server[]					= "DNS ｻｰﾊﾞ            ";
CUB JPN_Primary[]						= ":1ﾊﾞﾝﾒ    \0         "
CUB JPN_Secondary[]						= ":2ﾊﾞﾝﾒ    \0         ";
CUB JPN_SMTP_Server[]					= "SMTP ｻｰﾊﾞ           ";
CUB JPN_POP_Server[]					= "POP ｻｰﾊﾞ            ";

/** 機器動作設定 */
#if (0)
//CUB JPN_SetMachineStateMode[]			= "   ｼﾞﾄﾞｳ ｼﾞｭｼﾝ ｾｯﾃｲ ";
#endif
CUB JPN_SetMachineStateMode[]			= "   ﾒｰﾙ ｼﾞｭｼﾝ ｾｯﾃｲ   ";
CUB JPN_AutoReceive[]					= "ｼﾞﾄﾞｳ ﾒｰﾙ ﾁｪｯｸ: \0   ";
CUB JPN_AutoDownload[]					= "ｼﾞﾄﾞｳ ﾀﾞｳﾝﾛｰﾄﾞ: \0   ";
CUB JPN_AutoPrint[]						= "ｼﾞﾄﾞｳ ﾌﾟﾘﾝﾄ   : \0   ";
CUB JPN_DeleteMail[]					= "ﾒｰﾙ ﾉ ｻｸｼﾞｮ   : \0   ";
CUB JPN_MailHoldTime[]					= "ｼﾞｭｼﾝﾒｰﾙ ﾎｿﾞﾝ ｷｶﾝ   ";
CUB JPN_Days1_31[]						= "ﾎｿﾞﾝ ｷｶﾝ(1-31)      ";
CUB JPN_RxDuringTx[]					= "ｿｳｼﾝ ｺﾞ ｼﾞｭｼﾝ : \0   ";
CUB JPN_SetMachineState[]				= "ﾒｰﾙ ｼﾞｭｼﾝ ｾｯﾃｲ      ";
CUB JPN_AutoRxStartTime[]				= "ｶｲｼ ｼﾞｺｸ            ";
CUB JPN_AutoRxEndTime[]					= "ｼｭｳﾘｮｳ ｼﾞｺｸ         ";
CUB JPN_IntervalTime[]					= "ｼﾞｯｺｳ ｶﾝｶｸ          ";

/** トーン検出設定 */
#if (0)
CUB JPN_SetToneDetectMode[]				= "   ﾄｰﾝ ｹﾝｼｭﾂ ｾｯﾃｲ   ";
CUB JPN_SetDialParameter[]				= "ﾄｰﾝ ｹﾝｼｭﾂ ｾｯﾃｲ      ";
CUB JPN_DialToneOn[]					= "ﾀﾞｲﾔﾙ ﾄｰﾝ:      \0   ";
CUB JPN_BusyToneOn[]					= "ﾋﾞｼﾞｰ ﾄｰﾝ:      \0   ";
#endif

/** ユーザデータ消去 */
CUB JPN_EraseUserDataMode[]				= "   ﾕｰｻﾞ ｾｯﾃｲ ｼｮｳｷｮ  ";
CUB JPN_EraseUserData[]					= "ﾕｰｻﾞ ｾｯﾃｲ ｼｮｳｷｮ     ";

/**  メール設定リスト */
CUB JPN_PrintUserDataMode[]				= "   ﾕｰｻﾞ ｾｯﾃｲ ﾘｽﾄ    ";
CUB JPN_PrintUserData[]					= "ﾕｰｻﾞ ｾｯﾃｲ ﾘｽﾄ       ";

/** コマンド入力表示 */
CUB JPN_EnterMailAddress[]				= "ﾒｰﾙｱﾄﾞﾚｽ ｦ ﾄﾞｳｿﾞ    ";

/** 宛先 */
CUB JPN_SetMailAddressMode[]			= "  ﾒｰﾙ ｱﾄﾞﾚｽ         ";
CUB JPN_SetMailAddress[]				= "   ﾒｰﾙ ｱﾄﾞﾚｽ ﾄｳﾛｸ   ";
CUB JPN_AddressName[]					= "ｱｲﾃｻｷﾒｲ             ";
CUB JPN_EraseMailAddressMode[]			= "   ﾒｰﾙ ｱﾄﾞﾚｽ ｼｮｳｷｮ  ";
CUB JPN_EraseMailAddress[]				= "ﾒｰﾙｱﾄﾞﾚｽ ｼｮｳｷｮ      ";
CUB JPN_PrintMailAddressMode[]			= "   ﾒｰﾙ ｱﾄﾞﾚｽ ﾘｽﾄ    ";
CUB JPN_PrintMailAddress[]				= "ﾒｰﾙ ｱﾄﾞﾚｽ ﾘｽﾄ       ";
CUB JPN_SetMailGroup[]					= "   ｱﾄﾞﾚｽ ｸﾞﾙｰﾌﾟ ﾄｳﾛｸ";
CUB JPN_MailGroupSetting[]				= "ｱﾄﾞﾚｽ ｸﾞﾙｰﾌﾟ        ";
CUB JPN_EraseMailGroupMode[]			= "   ｱﾄﾞﾚｽｸﾞﾙｰﾌﾟ ｼｮｳｷｮ";
CUB JPN_EraseMailGroup[]				= "ｱﾄﾞﾚｽｸﾞﾙｰﾌﾟ ｼｮｳｷｮ   ";
CUB JPN_PrintMailGroupMode[]			= "   ﾒｰﾙ ｸﾞﾙｰﾌﾟ ﾘｽﾄ   ";
CUB JPN_PrintMailGroup[]				= "ﾒｰﾙ ｸﾞﾙｰﾌﾟ ﾘｽﾄ      ";
CUB JPN_PressOnetouch[]					= "ﾜﾝﾀｯﾁｷｰ ｦ ﾄﾞｳｿﾞ     ";

/** サービスファンクション */
CUB JPN_InitEngineBoard[]				= "I-FAX ｼｮｷｶ          ";
CUB JPN_IP_EchoRequest[]				= "IPﾊﾟｹｯﾄ ｴｺｰ ﾖｳｷｭｳ   ";
CUB JPN_INF_Complete[]					= "  **   ｼｭｳﾘｮｳ   **  ";
CUB	JPN_SF_TTL_Test[]					= "TTL Test            "; /*1998/6/9 Eguchi*/

/** 設置オペレーション */
CUB JPN_INF_InitialError[]				= "I-FAX ｼｮｷｶ ｴﾗｰ      ";

/** コマンド予約 */
CUB JPN_ReviewMailComMode[]				= "  ﾒｰﾙ ﾂｳｼﾝ ｶｸﾆﾝ     ";
CUB JPN_CancelMailCom[]					= "ﾒｰﾙ ﾂｳｼﾝ ﾖﾔｸ ｼｮｳｷｮ  ";
CUB JPN_PrintMailComMode[]				= "   ﾒｰﾙ ﾂｳｼﾝ ﾖﾔｸ ﾘｽﾄ ";
CUB JPN_PrintMailCom[]					= "ﾒｰﾙ ﾂｳｼﾝ ﾖﾔｸ ﾘｽﾄ    ";
CUB JPN_PrintStoredMailMode[]			= "   ﾖﾔｸ ﾒｰﾙ ﾌﾟﾘﾝﾄ    ";
CUB JPN_PrintStoredMail[]				= "ﾖﾔｸ ﾒｰﾙ ﾌﾟﾘﾝﾄ       ";
CUB JPN_EnterMailCommandNo[]			= "ﾖﾔｸ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ  ";

/** ジャーナルプリント */
CUB JPN_PrintMailJounalMode[]			= "   ﾒｰﾙ ﾂｳｼﾝ ｷﾛｸ ﾘｽﾄ ";
CUB JPN_PrintMailJournal[]				= "ﾒｰﾙ ﾂｳｼﾝ ｷﾛｸ ﾘｽﾄ    ";

/** 受信 */
CUB JPN_ManualReceiveMail[]				= "   ｼｭﾄﾞｳ ﾒｰﾙ ｼﾞｭｼﾝ  ";
CUB JPN_ReceiveMailMode[]				= "  ﾒｰﾙ ｼﾞｭｼﾝ         ";
CUB JPN_PrintReceiveMailMode[]			= "   ｼﾞｭｼﾝ ﾒｰﾙ ﾌﾟﾘﾝﾄ  ";
CUB JPN_PrintReceiveMail[]				= "ｼﾞｭｼﾝ ﾒｰﾙ ﾌﾟﾘﾝﾄ     ";

/** 動作中および終了表示 */
CUB JPN_INF_Abort[]						= "  **   ﾁｭｳﾀﾞﾝ   **  ";
CUB JPN_INF_NoNewMail[]					= "**  ｼﾝﾁｬｸ ﾒｰﾙ ﾅｼ  **";
CUB JPN_SendingMail[]					= "ﾒｰﾙ ｿｳｼﾝ            ";
CUB JPN_ReceivingMail[]					= "ﾒｰﾙ ｼﾞｭｼﾝ           ";
CUB JPN_INF_Creating[]					= "** ｿｳｼﾝ ｼﾞｭﾝﾋﾞﾁｭｳ **";
CUB JPN_INF_Dialing[]					= "  **  ﾀﾞｲｱﾙﾁｭｳ  **  ";
CUB JPN_INF_Connecting[]				= "  **  ｾﾂｿﾞｸﾁｭｳ  **  ";
CUB JPN_INF_Sending[]					= "  **  ｿｳｼﾝﾁｭｳ   **  ";
CUB JPN_INF_Receiving[]					= "  **  ｼﾞｭｼﾝﾁｭｳ  **  ";
CUB JPN_INF_Checking[]					= "   ** ﾁｪｯｸﾁｭｳ **    ";

CUB JPN_INF_PrintRcvReport[]			= "ｼﾞｭｼﾝ ﾂｳﾁ ﾌﾟﾘﾝﾄ     ";

/** PTTテスト信号送出サービスファンクション */
CUB JPN_PTT_TestMode[]					= "PTT ﾃｽﾄ ﾓｰﾄﾞ        ";
CUB JPN_PTT_Setting[]					= "PTT ﾃｽﾄ ｾｯﾃｨﾝｸﾞ     ";
CUB JPN_DataRate[]						= "    :ﾃﾞｰﾀ ﾚｰﾄ       ";
CUB JPN_SymbolRate[]					= "    :ｼﾝﾎﾞﾙ ﾚｰﾄ      ";
CUB JPN_CarrierBias[]					= "    :ｷｬﾘｱ ﾊﾞｲｱｽ     ";
CUB JPN_SecondChannel[]					= "    :2次 ﾁｬﾈﾙ       ";
CUB JPN_UpperBandEdge[]					= "    :ｱｯﾊﾟｰ ﾊﾞﾝﾄﾞｴｯｼﾞ";
CUB JPN_CarrierBiasRange[]				= "[-100<-->100]       ";
CUB JPN_BandEdgeRange[]					= "[0-22(dB)]          ";
CUB JPN_INF_Mode[]						= "    :ﾓｰﾄﾞ           ";

/* PTTテスト信号種類 */
/*↓この順番で並べて記述*/
CUB JPN_DTMF_Tone0[]					= "%TT00               ";
CUB JPN_DTMF_Tone1[]					= "%TT01               ";
CUB JPN_DTMF_Tone2[]					= "%TT02               ";
CUB JPN_DTMF_Tone3[]					= "%TT03               ";
CUB JPN_DTMF_Tone4[]					= "%TT04               ";
CUB JPN_DTMF_Tone5[]					= "%TT05               ";
CUB JPN_DTMF_Tone6[]					= "%TT06               ";
CUB JPN_DTMF_Tone7[]					= "%TT07               ";
CUB JPN_DTMF_Tone8[]					= "%TT08               ";
CUB JPN_DTMF_Tone9[]					= "%TT09               ";
CUB JPN_DTMF_ToneAst[]					= "%TT0A               ";
CUB JPN_DTMF_ToneSharp[]				= "%TT0B               ";
CUB JPN_DTMF_ToneA[]					= "%TT0C               ";
CUB JPN_DTMF_ToneB[]					= "%TT0D               ";
CUB JPN_DTMF_ToneC[]					= "%TT0E               ";
CUB JPN_DTMF_ToneD[]					= "%TT0F               ";
CUB JPN_V21Ch1MkSymbol[]				= "%TT10               ";
CUB JPN_V21Ch2MkSymbol[]				= "%TT11               ";
CUB JPN_V23BwardChMkSymbol[]			= "%TT12               ";
CUB JPN_V23FwardChMkSymbol[]			= "%TT13               ";
CUB JPN_V22CallMk600bps[]				= "%TT14               ";
CUB JPN_V22CallMk1200bps[]				= "%TT15               ";
CUB JPN_V22bisCallMk2400bps[]			= "%TT16               ";
CUB JPN_V22AnswerSignal[]				= "%TT17               ";
CUB JPN_V22bisAnswerSignal[]			= "%TT18               ";
CUB JPN_V21Ch1SpSymbol[]				= "%TT19               ";
CUB JPN_V21Ch2SpSymbol[]				= "%TT1A               ";
CUB JPN_V23BwardChSpSymbol[]			= "%TT1B               ";
CUB JPN_V23FwardChSpSymbol[]			= "%TT1C               ";
CUB JPN_V32_9600bps[]					= "%TT20               ";
CUB JPN_V32bis14400bps[]				= "%TT21               ";
CUB JPN_V32TCM9600bps[]					= "%TT22               ";
CUB JPN_V32TCM14400bps[]				= "%TT23               ";
CUB JPN_V32bisTCM7200bps[]				= "%TT24               ";
CUB JPN_V32_4800bps[]					= "%TT25               ";
CUB JPN_OffFook[]						= "%TT30               ";
CUB JPN_V25AnswerTone[]					= "%TT31               ";
CUB JPN_1800HzGuardTone[]				= "%TT32               ";
CUB JPN_V25Send1300Hz[]					= "%TT33               ";
CUB JPN_FaxSend1100Hz[]					= "%TT34               ";
CUB JPN_BellAnswer2225hz[]				= "%TT35               ";
CUB JPN_V21Ch2[]						= "%TT40               ";
CUB JPN_V27ter2400bps[]					= "%TT41               ";
CUB JPN_V27ter4800bps[]					= "%TT42               ";
CUB JPN_V29_7200bps[]					= "%TT43               ";
CUB JPN_V29_9600bps[]					= "%TT44               ";
CUB JPN_V17_7200bpsL_Train[]			= "%TT45               ";
CUB JPN_V17_7200bpsS_Train[]			= "%TT46               ";
CUB JPN_V17_9600bpsL_Train[]			= "%TT47               ";
CUB JPN_V17_9600bpsS_Train[]			= "%TT48               ";
CUB JPN_V17_12000bpsL_Train[]			= "%TT49               ";
CUB JPN_V17_12000bpsS_Train[]			= "%TT4A               ";
CUB JPN_V17_14400bpsL_Train[]			= "%TT4B               ";
CUB JPN_V17_14400bpsS_Train[]			= "%TT4C               ";
CUB JPN_VFC_Modulation[]				= "%TT5\0               ";
CUB JPN_V34_Modulation[]				= "%TT6\0               ";
/*↑この順番で並べて記述*/

/* Gurad Tone */
/*↓この3個はこの順番で並べて記述*/
CUB JPN_GT1800hz[]						= "ｶﾞｰﾄﾞ ﾄｰﾝ 1800 Hz   ";
CUB JPN_GT550hz[]						= "ｶﾞｰﾄﾞ ﾄｰﾝ 550 Hz    ";
CUB JPN_NoGuardTone[]					= "ｶﾞｰﾄﾞ ﾄｰﾝ ﾅｼ        ";

/* Mode */
/*↓この2個はこの順番で並べて記述*/
CUB JPN_OriginateMode[]					= "ｵﾘｼﾞﾈｲﾄ ﾓｰﾄﾞ        ";
CUB JPN_AnswerMode[]					= "ｱﾝｻｰ ﾓｰﾄﾞ           ";

/* Data Rate */
/*↓この12個はこの順番で並べて記述*/
CUB JPN_2400bps[]						= "2400 bps            ";
CUB JPN_4800bps[]						= "4800 bps            ";
CUB JPN_7200bps[]						= "7200 bps            ";
CUB JPN_9600bps[]						= "9600 bps            ";
CUB JPN_12000bps[]						= "12000 bps           ";
CUB JPN_14400bps[]						= "14400 bps           ";
CUB JPN_16800bps[]						= "16800 bps           ";
CUB JPN_19200bps[]						= "19200 bps           ";
CUB JPN_21600bps[]						= "21600 bps           ";
CUB JPN_24000bps[]						= "24000 bps           ";
CUB JPN_26400bps[]						= "26400 bps           ";
CUB JPN_28800bps[]						= "28800 bps           ";
CUB JPN_31200bps[]						= "31200 bps           ";
CUB JPN_33600bps[]						= "33600 bps           ";

/* Symbol Rate */
/*↓この6つはこの順番で並べて記述*/
CUB JPN_2400baud[]						= "2400 baud           ";
CUB JPN_2800baud[]						= "2800 baud           ";
CUB JPN_3000baud[]						= "3000 baud           ";
CUB JPN_3200baud[]						= "3200 baud           ";
CUB JPN_3429baud[]						= "3429 baud           ";

/* Second Channel */
/*↓この2つはこの順番で並べて記述*/
CUB JPN_Disable[]						= "ﾑｺｳ                 ";
CUB JPN_Enable[]						= "ﾕｳｺｳ                ";

/* Upper Band Edge */
/*↓この11個はこの順番で並べて記述*/
CUB JPN_V34BandEdge0Db[]				= "a = 0[dB]           ";
CUB JPN_V34BandEdge2Db[]				= "a = 2[dB]           ";
CUB JPN_V34BandEdge4Db[]				= "a = 4[dB]           ";
CUB JPN_V34BandEdge6Db[]				= "a = 6[dB]           ";
CUB JPN_V34BandEdge8Db[]				= "a = 8[dB]           ";
CUB JPN_V34BandEdge10Db[]				= "a = 10[dB]          ";
CUB JPN_V34BandEdgeG1Db[]				= "b=0.5[dB], c=1.0[dB]";
CUB JPN_V34BandEdgeG2Db[]				= "b=1.0[dB], c=2.0[dB]";
CUB JPN_V34BandEdgeG3Db[]				= "b=1.5[dB], c=3.0[dB]";
CUB JPN_V34BandEdgeG4Db[]				= "b=2.0[dB], c=4.0[dB]";
CUB JPN_V34BandEdgeG5Db[]				= "b=2.5[dB], c=5.0[dB]";
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* By H.Fujimura 1999/01/21 */
/*----------------------------------*
 *	ＦＡＸワープ
 *----------------------------------*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modified by SMuratec L.Z.W 2003/09/01 */
CUB	JPN_FaxWarpMode[]					= "    FAXﾜｰﾌﾟ         ";
#else
CUB	JPN_FaxWarpMode[]					= "  FAXﾜｰﾌﾟ           ";
#endif /* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	JPN_EnterFaxWarpMode[]				= "   FAXﾜｰﾌﾟ ｾｯﾄ      ";
CUB	JPN_PrintFaxWarpMode[]				= "   FAXﾜｰﾌﾟ ﾘｽﾄ      ";
CUB	JPN_SetFaxWarpMode[]				= "   FAXﾜｰﾌﾟ ｾｯﾃｲ     ";
CUB	JPN_EnterFaxWarp[]					= "FAXﾜｰﾌﾟ ｾｯﾄ         ";
CUB	JPN_PrintFaxWarp[]					= "FAXﾜｰﾌﾟ ﾘｽﾄ         ";
CUB	JPN_SetFaxWarp[]					= "FAXﾜｰﾌﾟ:\0           ";
CUB	JPN_WarpSelectNumber[]				= "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ ";
CUB	JPN_WarpTime[]						= "ｼﾃｲ ｼﾞｺｸ            ";
CUB	JPN_WarpWeek[][21]					= {
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/21 */
  #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 曜日をCGRAMから取り出し表示する。by Y.Kano 2003/10/28 */
  										  "\x28\x10\x29                 ",
										  "\x28\x11\x29                 ",
										  "\x28\x12\x29                 ",
										  "\x28\x13\x29                 ",
										  "\x28\x14\x29                 ",
										  "\x28\x15\x29                 ",
										  "\x28\x16\x29                 ",
  #else	/* HINOKI */
   #if defined(HINOKI3)		/* 新ＬＣＤドライバー対応 by Y.Kano 2005/01/21 */
  										  "\x28\x97\x29                 ",
										  "\x28\x91\x29                 ",
										  "\x28\x92\x29                 ",
										  "\x28\x93\x29                 ",
										  "\x28\x94\x29                 ",
										  "\x28\x95\x29                 ",
										  "\x28\x96\x29                 ",
   #else
  										  "\x28\xF0\x29                 ",
										  "\x28\xF1\x29                 ",
										  "\x28\xF2\x29                 ",
										  "\x28\xF3\x29                 ",
										  "\x28\xF4\x29                 ",
										  "\x28\xF5\x29                 ",
										  "\x28\xF6\x29                 ",
   #endif
  #endif	/* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
										  "\x28\x2A\x29                 ",
 #else
										  "ﾆﾁ                  ",
										  "ｹﾞﾂ                 ",
										  "ｶ                   ",
										  "ｽｲ                  ",
										  "ﾓｸ                  ",
										  "ｷﾝ                  ",
										  "ﾄﾞ                  ",
										  " *                  ",
 #endif
};
CUB	JPN_SelectWarpRxDocPrint[][21]		= {
										  "   ﾄﾞｳｼﾞ ﾌﾟﾘﾝﾄ: OFF ",
										  "   ﾄﾞｳｼﾞ ﾌﾟﾘﾝﾄ: ON  ",
};

/* ＷＡＲＰ転送先ワーディング追加 By O.Kimoto 1999/02/08 */
CUB	JPN_WarpAltNumber[]					= "ﾃﾝｿｳ ﾊﾞﾝｺﾞｳ         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです */

#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* By H.Fujimura 1999/01/21 */
/*----------------------------------*
 *	ナンバーディスプレイ
 *----------------------------------*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modified by SMuratec L.Z.W 2003/09/01 */
CUB	JPN_NumberDisplayMode[]				= "    ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ   ";
#else
CUB	JPN_NumberDisplayMode[]				= "  ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ     ";
#endif /* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	JPN_EnterNumberDisplayMode[]		= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ｾｯﾄ";
CUB	JPN_PrintNumberDisplayMode[]		= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘｽﾄ";
CUB	JPN_SetNumberDisplayMode[]			= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲｾｯﾃｲ";
CUB	JPN_EnterNumberDisplay[]			= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ｾｯﾄ   ";
CUB	JPN_PrintNumberDisplay[]			= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘｽﾄ   ";
CUB	JPN_SetNumberDisplay[]				= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ:\0     ";
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* By H.Fujimura 1999/01/21 */
CUB	JPN_Set_ND_Warp[]					= "NDﾜｰﾌﾟ:\0            ";
 #endif
CUB	JPN_ND_SelectNumber[]				= "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ ";
CUB	JPN_ND_TelMode[][21]				= {
										  "ﾃﾞﾝﾜｷ ｾﾂｿﾞｸ:\0       ",
										  "             OFF    ",
/*										  "             PHONE1 ",*/
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/24 */
										  "             TEL    ",
#else
										  "             PHONE2 ",
#endif		/* End of (defined (KEISATSU)) */
};
CUB	JPN_ND_NoNotice[]					= "ﾋﾂｳﾁ                ";
CUB	JPN_ND_OutOfDisp[]					= "ﾋｮｳｼﾞ ｹﾝｶﾞｲ         ";
CUB	JPN_ND_PublicTel[]					= "ｺｳｼｭｳ ﾃﾞﾝﾜ          ";
CUB	JPN_ND_Parameter[]					= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾊﾟﾗﾒｰﾀ";
CUB	JPN_Print_ND_JournalMode[]			= "   ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘﾚｷ";
CUB	JPN_Print_ND_Journal[]				= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘﾚｷ   ";
#endif

/*----------------------------------*
 *	通信確認
 *----------------------------------*/
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	JPN_ConfirmReport[]					= "ｿｳｼﾝｶｸﾆﾝｼｮｳ    :\0   ";
#else
CUB	JPN_ConfirmReport[]					= "ﾂｳｼﾝｼｮｳ        :\0   ";
#endif

/*----------------------------------*
 *	オペレーションプロテクト
 *----------------------------------*/
CUB	JPN_OperationProtected[]			= "ｵﾍﾟﾚｰｼｮﾝ ﾌﾟﾛﾃｸﾄ     ";

#if (PRO_COPY_FAX_MODE == ENABLE)
/*----------------------------------*
 *	コピーモード
 *----------------------------------*/
CUB	JPN_ChangeManual[]					= "      ﾃｻﾞｼ \x7E ｾｯﾄｷｰ  ";	/* \x7E = → */
#endif

#if (PRO_FBS == ENABLE)
/*----------------------------------*
 *	ブック送信
 *----------------------------------*/
CUB	JPN_SetBookTxDocumentSize[]			= "ｹﾞﾝｺｳ ｻｲｽﾞ ｾｯﾃｲ     ";
CUB	JPN_SetBookTxNextDocument[]			= "ｼﾞｹﾞﾝｺｳ ｾｯﾃｲ        ";

CUB	JPN_NextBookDocScanStart[]			= "ﾖﾐﾄﾘ ｶｲｼ \x7E ｼﾞｹﾞﾝｺｳｷｰ";	/* \x7E = → */
CUB	JPN_NextBookDocTxStart[]			= "ｿｳｼﾝ ｶｲｼ \x7E ｽﾀｰﾄｷｰ   ";	/* \x7E = → */
CUB	JPN_NextBookDocScanEnd[]			= "ﾖﾐﾄﾘ ｼｭｳﾘｮｳ \x7E ｾｯﾄｷｰ ";	/* \x7E = → */
#endif

/* 紙サイズ（R → 0x01(OPR_PAPER_SIZE_R)で定義して下さい） */
CUB	JPN_PaperSize_None[]				= "ﾅｼ\0  ";
CUB	JPN_PaperSize_A5[]					= "A5\0  ";
CUB	JPN_PaperSize_Letter[]				= "Ltr\0 ";
#if defined(USAOKI)	/* 1998/02/04 Y.Matsukuma */
CUB	JPN_PaperSize_A4[]					= "LT\0  ";
#else
CUB	JPN_PaperSize_A4[]					= "A4\0  ";
#endif
CUB	JPN_PaperSize_Legal[]				= "Legl\0";
CUB	JPN_PaperSize_B5R[]					= "B5\x01\0 ";
CUB	JPN_PaperSize_B4[]					= "B4\0  ";
CUB	JPN_PaperSize_A3[]					= "A3\0  ";
CUB	JPN_PaperSize_A4R[]					= "A4\x01\0 ";
CUB	JPN_PaperSize_LetterR[]				= "Ltr\x01\0";
CUB	JPN_PaperSize_F4[]					= "F4\0  ";
CUB	JPN_PaperSize_A5R[]					= "A5\x01\0 ";
CUB	JPN_PaperSize_Postcard[]			= "ﾊｶﾞｷ\0";
CUB	JPN_PaperSize_LD[]					= "Ld\0  ";
CUB	JPN_PaperSize_GLetterR[]			= "GLtr\x01";
CUB	JPN_PaperSize_ExecutiveR[]			= "Exe\x01\0";
/*  #if (PRO_KEYPANEL == PANEL_POPLAR_B)  *//* modified by honda 1997/11/14 */
/*   #if defined(JPN)  */
/*	CUB	JPN_PaperSize_InvoiceR[]			= "Inv\x01\0";  */
/*   #else  */
CUB	JPN_PaperSize_HalfLetterR[]			= "HLtr\x01";  /* added by honda 1997/10/04 */
/*   #endif  */
/*  #else  */
/*	CUB	JPN_PaperSize_InvoiceR[]			= "Inv\x01\0";  */
/*  #endif  */
CUB	JPN_PaperSize_GLegal[]				= "GLegl";
CUB	JPN_PaperSize_GLetter[]				= "GLtr\0";
CUB	JPN_PaperSize_Card[]				= "Card\0";
CUB	JPN_PaperSize_Executive[]			= "Exe\0 ";
CUB	JPN_PaperSize_B5[]					= "B5\0  ";
CUB	JPN_PaperSize_C5[]					= "C5\0  ";
CUB	JPN_PaperSize_HalfLetter[]			= "HLtr\0";
CUB	JPN_PaperSize_Invoice[]				= "Inv\0 ";
CUB	JPN_PaperSize_B6[]					= "B6\0  ";
CUB	JPN_PaperSize_DL[]					= "DL\0  ";
CUB	JPN_PaperSize_CM10[]				= "CM10\0";
CUB	JPN_PaperSize_A6[]					= "A6\0  ";
CUB	JPN_PaperSize_Monarch[]				= "Mnc\0 ";
CUB	JPN_PaperSize_35[]					= "3x5\0 ";
CUB	JPN_PaperSize_User[]				= "User\0";
CUB	JPN_PaperSize_OHP[]					= "OHP\0 ";	/* このﾜｰﾃﾞｨﾝｸﾞは、SYS_DOC.Hの定義とは無関係です */
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)	/* By S.Fukui Jan.23,1998 */
CUB	JPN_PaperSize_Auto[]				= "ｼﾞﾄﾞｳ";	/* このﾜｰﾃﾞｨﾝｸﾞは、SYS_DOC.Hの定義とは無関係です */
#endif
#if (PRO_PITNEYBOWES == ENABLE)
CUB	JPN_PaperSize_Ledger[]				= "LDGR\0";	/* 原稿サイズ表示ＰＢ用 By S.Fukui Aug.25,1998 */
CUB	JPN_PaperSize_LtLg[]				= "LTLG\0";	/* 原稿サイズ表示ＰＢ用 (For Letter/Legal) By S.Fukui Aug.25,1998 */
#endif

/*----------------------------------*
 *	サービスファンクション
 *----------------------------------*/
/* マシンパラメータ */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	JPN_SF_ParameterSet[]				= "ｷｷ ﾊﾟﾗﾒｰﾀｰ ｾｯﾄ      ";
CUB	JPN_SF_ParameterClear[]				= "ｷｷ ﾊﾟﾗﾒｰﾀｰ ｸﾘｱ      ";
#else
CUB	JPN_SF_ParameterSet[]				= "ｷｷ ﾊﾟﾗﾒｰﾀ ｾｯﾄ       ";
CUB	JPN_SF_ParameterClear[]				= "ｷｷ ﾊﾟﾗﾒｰﾀ ｸﾘｱ       ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* メモリースイッチ */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	JPN_SF_MemorySwitchSet[]			= "ﾒﾓﾘｰｽｲｯﾁ ｾｯﾄ        ";
CUB	JPN_SF_MemorySwitchClear[]			= "ﾒﾓﾘｰｽｲｯﾁ ｸﾘｱ        ";
#elif (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/15 */
CUB	JPN_SF_MemorySwitchSet[]			= "ﾒﾓﾘｰ ｽｲｯﾁ ｾｯﾄ       ";
CUB	JPN_SF_MemorySwitchClear[]			= "ﾒﾓﾘｰ ｽｲｯﾁ ｸﾘｱ       ";
#else
CUB	JPN_SF_MemorySwitchSet[]			= "ﾒﾓﾘ ｽｲｯﾁ ｾｯﾄ        ";
CUB	JPN_SF_MemorySwitchClear[]			= "ﾒﾓﾘ ｽｲｯﾁ ｸﾘｱ        ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* ユーザ設定クリア */
CUB	JPN_SF_BackUpFileClear[]			= "ﾕｰｻﾞ ｼﾖｳ ﾃﾞｰﾀ ｸﾘｱ   ";

/* オールラムクリア */
CUB	JPN_SF_AllClear[]					= "ｵｰﾙ ｸﾘｱ             ";

/* 機種固有スイッチ */
CUB	JPN_SF_UniqSwitchSet[]				= "ｷｼｭ ｺﾕｳ ｽｲｯﾁ ｾｯﾄ    ";
CUB	JPN_SF_UniqSwitchClear[]			= "ｷｼｭ ｺﾕｳ ｽｲｯﾁ ｸﾘｱ    ";

/* 保守用スイッチ */
CUB	JPN_SF_MaintenanceSet[]				= "ﾎｼｭﾖｳ ｽｲｯﾁ ｾｯﾄ      ";
CUB	JPN_SF_MaintenanceClear[]			= "ﾎｼｭﾖｳ ｽｲｯﾁ ｸﾘｱ      ";

/* テストファンクション -> このワーディングの並びはかえてはいけない */
#if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1997/10/02 Y.Matsukuma */
CUB	JPN_SF_LifeMonitor[]				= "ｷｷ ﾅｲﾌﾞ ｼﾞｮｳﾀｲ      ";
CUB	JPN_SF_LifeMonitorClear[]			= "ﾗｲﾌﾓﾆﾀ ｸﾘｱ          ";
CUB	JPN_SF_TestPatternPrint[]			= "ﾃｽﾄ ﾊﾟﾀｰﾝ ﾌﾟﾘﾝﾄ     ";
CUB	JPN_SF_StampTest[]					= "ｽﾐ ｽﾀﾝﾌﾟ ﾃｽﾄ        ";
CUB	JPN_SF_Shading[]					= "ｼｪｰﾃﾞｨﾝｸﾞﾃﾞｰﾀ ﾄﾘｺﾐ  ";
#elif (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ＨＩＮＯＫＩは原稿排出テストは有りません by O.Kimoto 1999/02/09 */
CUB	JPN_SF_LifeMonitor[]				= "ｷｷ ﾅｲﾌﾞ ｼﾞｮｳﾀｲ      ";
CUB	JPN_SF_TestPatternPrint[]			= "ﾃｽﾄ ﾊﾟﾀｰﾝ ﾌﾟﾘﾝﾄ     ";
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/12/26 */
CUB	JPN_SF_PS1_PB4_Threshold[]			= "PS1,PB4 ｼｷｲﾁ ｾｯﾃｲ   ";/* Add by Y.Kano 2003/12/26 */
 #else	/* HINOKIは済みスタンプを表示 */
CUB	JPN_SF_StampTest[]					= "ｽﾐ ｽﾀﾝﾌﾟ ﾃｽﾄ        ";
 #endif
CUB	JPN_SF_Shading[]					= "ｼｪｰﾃﾞｨﾝｸﾞﾃﾞｰﾀ ﾄﾘｺﾐ  ";
#else
CUB	JPN_SF_LifeMonitor[]				= "ｷｷ ﾅｲﾌﾞ ｼﾞｮｳﾀｲ      ";
CUB	JPN_SF_TestPatternPrint[]			= "ﾃｽﾄ ﾊﾟﾀｰﾝ ﾌﾟﾘﾝﾄ     ";
CUB	JPN_SF_StampTest[]					= "ｽﾐ ｽﾀﾝﾌﾟ ﾃｽﾄ        ";
CUB	JPN_SF_DocumentFeedOutTest[]		= "ｹﾞﾝｺｳﾊｲｼｭﾂ ﾃｽﾄ      ";
CUB	JPN_SF_Shading[]					= "ｼｪｰﾃﾞｨﾝｸﾞﾃﾞｰﾀ ﾄﾘｺﾐ  ";
#endif

/* ライフモニター */
CUB	JPN_SF_BoardNumber[]				= "ﾎﾞｰﾄﾞ ﾊﾞﾝｺﾞｳ?       ";
CUB	JPN_SF_LifeReadingPage[]			= "ﾖﾐﾄﾘ ﾏｲｽｳ           ";
CUB	JPN_SF_LifePrintingPage[]			= "ｲﾝｼﾞ ﾏｲｽｳ           ";
CUB	JPN_SF_LifeTxPage[]					= "ｿｳｼﾝ ﾏｲｽｳ           ";
CUB	JPN_SF_LifeDrumReplaceCount[]		= "ﾄﾞﾗﾑ ｺｳｶﾝ ｶｲｽｳ      ";
CUB	JPN_SF_LifeDrumLifeCount[]			= "ﾄﾞﾗﾑ ｼﾞｭﾐｮｳ ｶｳﾝﾀ    ";
CUB	JPN_SF_LifeTonerReplaceCount[]		= "ﾄﾅｰ ｺｳｶﾝ ｶｲｽｳ       ";
CUB	JPN_SF_LifeTonerLifeCount[]			= "ﾄﾅｰ ｼﾞｭﾐｮｳ ｶｳﾝﾀ     ";
CUB	JPN_SF_LifeFuserReplaceCount[]		= "ﾃｲﾁｬｸｷ ｺｳｶﾝ ｶｲｽｳ    ";
CUB	JPN_SF_LifeFuserLifeCount[]			= "ﾃｲﾁｬｸｷ ｼﾞｭﾐｮｳ ｶｳﾝﾀ  ";
CUB	JPN_SF_LifeTransferReplaceCount[]	= "ﾃﾝｼｬﾛｰﾗｰ ｺｳｶﾝ ｶｲｽｳ  ";
CUB	JPN_SF_LifeTransferLifeCount[]		= "ﾃﾝｼｬﾛｰﾗｰ ｼﾞｭﾐｮｳ ｶｳﾝﾀ";
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* By H.Fujimura 1999/01/21 */
CUB	JPN_SF_CPU_Revision[]				= "CPU ﾊﾞｰｼﾞｮﾝ         ";
CUB	JPN_SF_ROM_Revision[]				= "ROM ﾊﾞｰｼﾞｮﾝ         ";
#endif

/* テストパターン */
CUB	JPN_SF_Pattern[]					= "ﾊﾟﾀｰﾝ             \0 ";

/* 工場ファンクション */
CUB	JPN_SF_FactoryFunction[]			= "ｺｳｼﾞｮｳ ﾌｧﾝｸｼｮﾝ      ";

CUB	JPN_SF_LEDTest[]					= "LED ﾃｽﾄ             ";
CUB	JPN_SF_LCDTest[]					= "LCD ﾃｽﾄ             ";
CUB	JPN_SF_PanelTest[]					= "ﾊﾟﾈﾙｷｰ ﾃｽﾄ          ";

CUB	JPN_SF_SRAMCheck[]					= "SRAM ﾁｪｯｸ           ";
CUB	JPN_SF_DRAMCheck[]					= "DRAM ﾁｪｯｸ           ";
CUB	JPN_SF_RTCTest[]					= "RTC ﾃｽﾄ             ";
CUB	JPN_SF_RS232CTest[]					= "RS232C ﾃｽﾄ          ";
CUB	JPN_SF_CassetteCheck[]				= "ｶｾｯﾄﾃｽﾄ             ";

/* キー */
/*このワーディングの順番はキーコードの順番に一致させなくてはならない */
 #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
CUB	JPN_SF_Receive[]					= "ｼﾞﾄﾞｳ ｼﾞｭｼﾝ         ";
 #else
CUB	JPN_SF_Receive[]					= "ｼﾞｭｼﾝ               ";
 #endif
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/09/08 *//* by K.Watanabe 2004/10/15 */
 #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
CUB	JPN_SF_Hook[]						= "ﾓﾆﾀｰ                ";
 #else
CUB	JPN_SF_Hook[]						= "ｵﾝﾌｯｸ               ";
 #endif
#else
CUB	JPN_SF_Hook[]						= "ﾌｯｸ                 ";
#endif
 #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
CUB	JPN_SF_Hold[]						= "ﾐｼﾖｳ                ";
 #else
CUB	JPN_SF_Hold[]						= "ﾎﾘｭｳ                ";
 #endif
CUB	JPN_SF_Mode[]						= "ｶﾞｼﾂ                ";
CUB	JPN_SF_Contrast[]					= "ﾉｳﾄﾞ                ";
CUB	JPN_SF_Program[]					= ">                   ";
CUB	JPN_SF_CursorLeft[]					= "<                   ";
CUB	JPN_SF_Set[]						= "ｾｯﾄ                 ";
 #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
CUB	JPN_SF_DelayedCheck[]				= "ﾌｧｸｽ ﾁｭｳｼ/ｶｸﾆﾝ      ";
 #else
CUB	JPN_SF_DelayedCheck[]				= "ﾂｳｼﾝ ｶｸﾆﾝ           ";	/* "Review Commands" -> "Review" 合わせるか？ */
 #endif
CUB	JPN_SF_Clear[]						= "ｸﾘｱ                 ";
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1997/08/20 Y.Matsukuma */
CUB	JPN_SF_DialMark[]					= "ﾀﾞｲﾔﾙｷｺﾞｳ           ";
#else
CUB	JPN_SF_Sort[]						= "ｿｰﾄ                 ";
#endif
CUB	JPN_SF_Broadcast[]					= "ﾄﾞｳﾎｳ               ";	/* 注）通信確認でも使用（このﾜｰﾃﾞｨﾝｸﾞは最大16ﾊﾞｲﾄです） */
 #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
CUB	JPN_SF_Special[]					= "ｵｳﾖｳ ﾂｳｼﾝ           ";
 #else
CUB	JPN_SF_Special[]					= "ｵｳﾖｳ                ";
 #endif
CUB	JPN_SF_Group[]						= "ｸﾞﾙｰﾌﾟ              ";
 #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
CUB	JPN_SF_Speed[]						= "ﾀﾝｼｭｸ/ﾃﾞﾝﾜﾁｮｳ       ";
 #else
CUB	JPN_SF_Speed[]						= "ﾀﾝｼｭｸ               ";
 #endif
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/15 */
CUB	JPN_SF_MemoryTx[]					= "ﾒﾓﾘｰｿｳｼﾝ            ";
#else
CUB	JPN_SF_MemoryTx[]					= "ﾒﾓﾘｿｳｼﾝ             ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	JPN_SF_Stop[]						= "ｽﾄｯﾌﾟ               ";
CUB	JPN_SF_Start[]						= "ｽﾀｰﾄ                ";
CUB	JPN_SF_Copy[]						= "ｺﾋﾟｰ                ";	/* 注）ｺﾋﾟｰ表示でも使用 */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)/* 1997/08/20 Y.Matsukuma */
 #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
CUB	JPN_SF_Redial[]						= "ﾘﾀﾞｲﾔﾙ/ﾎﾟｰｽﾞ        ";
CUB	JPN_SF_Reservation[]				= "ｶｲﾜ ﾖﾔｸ             ";
 #else
CUB	JPN_SF_Redial[]						= "ﾘﾀﾞｲﾔﾙ              ";
CUB	JPN_SF_Stamp[]						= "ｽﾀﾝﾌﾟ               ";
 #endif
CUB	JPN_SF_Mercury[]					= "Mercury             "; /* アンズＬは従来のワーディングを使用 By S.Fukui Nov.17,1997 */
CUB	JPN_SF_Flash[]						= "Flash               ";
#elif (PRO_KEYPANEL == PANEL_STOCKHM2)  /* Modify by SMuratec 夏 2004/10/7 */
CUB	JPN_SF_Redial[]						= "ﾘﾀﾞｲﾔﾙ              ";
CUB	JPN_SF_Stamp[]						= "ｽﾀﾝﾌﾟ               ";
CUB	JPN_SF_Mercury[]					= "Prefix              ";
CUB	JPN_SF_Flash[]						= "Flash               ";
#else
CUB	JPN_SF_PaperSelect[]				= "ﾖｳｼｾﾝﾀｸ             ";
CUB	JPN_SF_Stamp[]						= "ｽﾀﾝﾌﾟ               ";
CUB	JPN_SF_Reduction[]					= "ｼｭｸｼｮｳ              ";
CUB	JPN_SF_Magnification[]				= "ｶｸﾀﾞｲ               ";
#endif
CUB	JPN_SF_CopyFax[]					= "ｺﾋﾟｰ/ﾌｧｸｽ           ";
CUB	JPN_SF_BookDocSize[]				= "ﾌﾞｯｸｹﾞﾝｺｳｻｲｽﾞ       ";
CUB	JPN_SF_CopyReset[]					= "ｺﾋﾟｰﾘｾｯﾄ            ";
CUB	JPN_SF_Tone[]						= "ﾄｰﾝ                 ";	/* 追加 97/11/29 T.Fukumoto */
#if defined(HINOKI3)	/* ONETOUCH_30_KEYがプレフィックスキーに変わったので by K.Watanabe 2004/10/26 */
CUB	JPN_SF_Prefix[]						= "ﾌﾟﾚﾌｨｸｽ             ";
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/24 N.Kondo */
CUB	JPN_SF_Receive_S[]					= "ｼﾞﾄﾞｳ/ｼｭﾄﾞｳ         ";
CUB	JPN_SF_Hook_S[]						= "ｵﾝﾌｯｸ/ﾃﾞﾝﾜ ﾖﾋﾞﾀﾞｼ   ";
CUB	JPN_SF_Contrast_S[]					= "ﾉｳﾀﾝ                ";
#endif


/* 回線テスト */
CUB	JPN_SF_LineTest[]					= "ｶｲｾﾝ ﾃｽﾄ            ";	/* 未使用 */
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/25 */
/* 警察FAX Added DVT_ID15 by SMuratec K.W.Q 2005/11/05 */
CUB JPN_SF_KEIDEN_RelayTest[]			= "ｹｲﾃﾞﾝ ﾘﾚｰ ﾃｽﾄ       ";
CUB JPN_SF_KEIDEN_TonalTest[]			= "ｹｲﾃﾞﾝ ﾄｰﾅﾙ ﾃｽﾄ      ";
CUB	JPN_SF_KEIDEN_DTMF_Test[]			= "ｹｲﾃﾞﾝ DTMF ﾃｽﾄ      ";
CUB	JPN_SF_PhoneTest[]					= "ｶﾆｭｳ ﾘﾚｰ ﾃｽﾄ        ";
CUB	JPN_SF_TonalTest[]					= "ｶﾆｭｳ ﾄｰﾅﾙ ﾃｽﾄ       ";
CUB	JPN_SF_DTMF_Test[]					= "ｶﾆｭｳ DTMF ﾃｽﾄ       ";
#else
CUB	JPN_SF_PhoneTest[]					= "ﾘﾚｰ ﾃｽﾄ             ";
CUB	JPN_SF_TonalTest[]					= "ﾄｰﾅﾙ ﾃｽﾄ            ";
CUB	JPN_SF_DTMF_Test[]					= "DTMF ﾃｽﾄ            ";
#endif		/* End of (defined (KEISATSU)) */

/* リレー */
CUB	JPN_SF_RelayTest1[]					= " CML  H  L  S  DP   ";
CUB	JPN_SF_RelayTest2[]					= " C24                ";
#if (PRO_MODEM == R288F)	/* By H.Fujimura 1999/01/21 */
 #if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/11/05 */
CUB	JPN_SF_R288F_RelayTest1[]			= " CML  HDST  L   S   ";
CUB	JPN_SF_R288F_Keiden_RelayTest1[]	= " CML  HDST  KL  S   ";
 #else
CUB	JPN_SF_R288F_RelayTest1[]			= " CML  H     L   S   ";
 #endif
CUB	JPN_SF_R288F_RelayTest2[]			= " C24  TONE  BZ  RI  ";
#endif

/* トーナル */
CUB	JPN_SF_FSK[]						= "FSK";
CUB	JPN_SF_White[]						= "White\0    ";
CUB	JPN_SF_Black[]						= "Black\0    ";
CUB	JPN_SF_Pix[]						= "     BPS   W:B =    ";

/* ミラーキャリッジ輸送モードセット */
CUB	JPN_SF_MirrorCarrigeModeSet[]		= "ﾐﾗｰｷｬﾘｯｼﾞﾕｿｳﾓｰﾄﾞ:\0  ";

/* サービスレポート */
CUB	JPN_SF_ServicePrint[]				= "ｻｰﾋﾞｽﾚﾎﾟｰﾄ          ";

CUB	JPN_SF_DTMF[]						= "DTMF";
CUB	JPN_SF_DTMFRow[]					= "ROW";
CUB	JPN_SF_DTMFColum[]					= "COL";

/* カセットテスト */
CUB	JPN_SF_CassetteOpen[]				= "ｶｾｯﾄ ｵｰﾌﾟﾝ\0  ";
CUB	JPN_SF_NoPaper[]					= "ｷﾛｸｼ ﾅｼ\0";
CUB	JPN_SF_SideCoverOpen[]				= "ｻｲﾄﾞｶﾊﾞｰ ｵｰﾌﾟﾝ\0";
CUB	JPN_SF_NoUnit[]						= "ﾕﾆｯﾄ ﾅｼ";

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ライフモニタークリア */
CUB	JPN_SF_LifeMonitorClear[]			= "ﾗｲﾌﾓﾆﾀ ｸﾘｱ          ";
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
/* ライフモニタクリアパスコード */
CUB	JPN_SF_ServiceCode[]				= "ｻｰﾋﾞｽｺｰﾄﾞ           ";
CUB	JPN_SF_EnterServiceCode[]			= "ｻｰﾋﾞｽｺｰﾄﾞ ｦ ﾄﾞｳｿﾞ   ";
#endif

/* プリンタメンテナンス */
CUB	JPN_SF_ReplaceCountSet[]			= "ｺｳｶﾝ ｶｳﾝﾀ ｾｯﾄ       ";
CUB	JPN_SF_ServiceCall[]				= "ｻｰﾋﾞｽｺｰﾙ            ";
CUB	JPN_SF_FuserReplace[]				= "ﾃｲﾁｬｸｷ ｺｳｶﾝ         ";
CUB	JPN_SF_TransferReplace[]			= "ﾃﾝｼｬﾛｰﾗｰ ｺｳｶﾝ       ";
CUB	JPN_SF_ServiceCallCount[]			= "ｻｰﾋﾞｽｺｰﾙ         :  ";
CUB	JPN_SF_HeatTrouble[]				= "ﾋｰﾀｰ ｴﾗｰ            ";
CUB	JPN_SF_HeatDisconnection[]			= "ｻｰﾐｽﾀ ﾀﾞﾝｾﾝ         ";
CUB	JPN_SF_HeatShortCircuit[]			= "ｻｰﾐｽﾀ ﾀﾝﾗｸ          ";
CUB	JPN_SF_InsideFanTrouble[]			= "ｷﾅｲ ﾌｧﾝ ｴﾗｰ         ";
CUB	JPN_SF_RxMotorTrouble[]				= "Rxﾓｰﾀｰ ｴﾗｰ          ";
CUB	JPN_SF_DrumTrouble[]				= "ﾄﾞﾗﾑﾋｭｰｽﾞ ｴﾗｰ       ";
CUB	JPN_SF_PsFanTrouble[]				= "ﾃﾞﾝｹﾞﾝ ﾌｧﾝ ｴﾗｰ      ";
CUB	JPN_SF_HvFuseDisconnect[]			= "ｺｳｱﾂ ﾋｭｰｽﾞ ﾀﾞﾝｾﾝ    ";

/* 消耗品発注機能 */
CUB	JPN_SF_ReceiverCustomerCode[]		= "ｵｸﾘｻｷ ｺｰﾄﾞ          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* (JPN) */
CUB	JPN_SF_ReceiverCompany[]			= "ｵｸﾘｻｷ ｼｬﾒｲ          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	JPN_SF_SenderCustomerCode[]			= "ｵｸﾘﾓﾄ ｺｰﾄﾞ          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	JPN_SF_SenderCompany[]				= "ｵｸﾘﾓﾄ ｼｬﾒｲ          ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
CUB	JPN_SF_SenderSection[]				= "                    ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* JPN以外は Address とする By S.Fukui Nov.15,1997 */
CUB	JPN_SF_SenderSection2[]				= "                    ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです *//* 60文字入力できるようにaddressを2段に分けます */
#else
CUB	JPN_SF_SenderSection[]				= "ｵｸﾘﾓﾄ ﾌﾞｶﾒｲ         ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
#endif
CUB	JPN_SF_SenderTelNumber[]			= "ｵｸﾘﾓﾄ ﾃﾞﾝﾜﾊﾞﾝｺﾞｳ    ";
CUB	JPN_SF_SerialNumber[]				= "ｼﾘｱﾙNo.             ";	/* 注）このﾜｰﾃﾞｨﾝｸﾞは最大11ﾊﾞｲﾄです */
CUB	JPN_SF_Date[]						= "ｾｯﾁﾋﾞ               ";
CUB	JPN_SF_PrintOrderForm[]				= "ﾊｯﾁｭｳﾖｳｼ ﾌﾟﾘﾝﾄ      ";
#if defined(US1)
CUB	JPN_SF_ToCompanyFaxNumber[]			= "Dist. Fax No.       ";	/* orderbythonda1998/11/11 */
CUB	JPN_SF_ToCompanyTelNumber[]			= "Dist. Tel No.       ";	/* orderbythonda1998/11/11 */
#endif

/* メモリダンプ */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/15 */
CUB	JPN_SF_MemoryDump[]					= "ﾒﾓﾘｰﾀﾞﾝﾌﾟ           ";
#else
CUB	JPN_SF_MemoryDump[]					= "ﾒﾓﾘﾀﾞﾝﾌﾟ            ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB	JPN_SF_MemoryDumpAddress[]			= "ｱﾄﾞﾚｽ      :        ";
CUB	JPN_SF_MemoryDumpLength[]			= "ﾃﾞｰﾀﾁｮｳ    :        ";

/* ＤＲＡＭクリア */
CUB	JPN_SF_ClearDRAM[]					= "DRAM ｸﾘｱ            ";

/* オプションデータ初期化 */
CUB	JPN_SF_OptionDataInitial[]			= "ｵﾌﾟｼｮﾝﾃﾞｰﾀ ｸﾘｱ      ";

/* 消耗品発注データクリア */
#if (PRO_PRINT_TYPE == THERMAL)	/* By H.Fujimura 1999/01/21 */
CUB	JPN_SF_MntDataClear[]				= "ｷｶｲ ﾊﾞﾝｺﾞｳ ｸﾘｱ      ";
#else
CUB	JPN_SF_OrderDataClear[]				= "ﾊｯﾁｭｳﾃﾞｰﾀ ｸﾘｱ       ";
#endif

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/20 */
/* T30モニター番号 */
CUB	JPN_SF_T30MonitorNumber[]			= "T30 No.:        \0   ";
#endif

CUB	JPN_SF_OK[]							= "OK                  ";
CUB	JPN_SF_NG[]							= "NG\0                 ";

/*----------------------------------*
 *	ＬＣＤ・リストでの頭文字表示
 *----------------------------------*/
#if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
CUB	JPN_HeadCharacter_Speed				= 'S';
CUB	JPN_HeadCharacter_Command			= 'C';
CUB	JPN_HeadCharacter_Batch				= 'B';
CUB	JPN_HeadCharacter_Polling			= 'P';
CUB	JPN_HeadCharacter_Tray				= 'T';
#endif

#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
/*----------------------------------*
 *	通信結果表示
 *----------------------------------*/
CUB	JPN_CommResultList[]				= "ﾂｳｼﾝｹｯｶ ｶｸﾆﾝ        ";/*20*/
CUB	JPN_Tx[]							= "Tx\0                 ";/*2*//*未翻訳*/
CUB	JPN_Rx[]							= "Rx\0                 ";/*2*//*未翻訳*/
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC 設定表示 */
CUB JPN_RemoteTxSetting[]				= "ﾃﾝｿｳ     ";
CUB JPN_RemoteTxSettingOff[]			= "OFF";
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 音量調整処理の追加 by Y.Kano 2003/08/27 */
/*----------------------------------*
 *	音量調整表示
 *----------------------------------*/
/* 音量調整選択の表示（上段） */
CUB	JPN_BuzzerVolume[]					= "01.ﾌﾞｻﾞｰ ｷｰﾀｯﾁ ｵﾝﾘｮｳ";/*20*/
CUB	JPN_MonitorVolume[]					= "02.ｽﾋﾟｰｶｰ ｵﾝﾘｮｳ     ";/*20*/
CUB	JPN_RingerControl[]					= "03.ﾁｬｸｼﾝ ﾍﾞﾙ        ";/*20*/
CUB	JPN_RingerControlOn[]				= "ﾁｬｸｼﾝ ﾍﾞﾙ  : ON     ";/*20*/
CUB	JPN_RingerControlOff[]				= "ﾁｬｸｼﾝ ﾍﾞﾙ  : OFF    ";/*20*/
/* 選択を促す表示（点滅する表示 ) */
CUB	JPN_BuzzerVolumeEnter[]				= "            \x7F/\x7E/ｾｯﾄ ";/*20*/

CUB	JPN_ShadingWord[]					= "B4ﾊｸｼ ｦ ｾﾂﾄ ｼﾃｸﾀﾞｻｲ ";/* Added by SMuratec K.W.Q 2003/08/11 */
CUB	JPN_ManualCutterMode[]				= "ｼｭﾄﾞｳ ｶｯﾀｰ ｼﾞｯｺｳ    ";/* Add by Y.Kano 2003/10/15 */
CUB	JPN_SF_PS2AdjustMode[]				= "PS2 ﾁｮｳｾｲ ﾓｰﾄﾞ      ";/* Add by Y.Kano 2003/10/17 */
CUB	JPN_PS2VolumueFullLight_1[]			= "PS2 ｦ ﾐｷﾞ ﾍ ｻｲﾀﾞｲｹﾞﾝ";/* Add by Y.Kano 2003/10/17 */
CUB	JPN_PS2VolumueFullLight_2[]			= "ﾏﾜｼﾃｸﾀﾞｻｲ           ";/* Add by Y.Kano 2003/10/17 */
CUB	JPN_PS2VolumueTitle[]				= "     PS2 ﾎﾞﾘｭｰﾑ     ";/* Add by Y.Kano 2003/10/17 */
CUB	JPN_PS2_OK[]						= "     ** OK **       ";/* Add by Y.Kano 2003/10/18 */
CUB JPN_PS2_Complete[]					= "    ** ｶﾝﾘｮｳ **     ";/* Add by Y.Kano 2003/10/18 */
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* チェッカー表示の追加 by SMuratec L.Z.W 2003/10/23 */
CUB JPN_Character[]						= "ﾓｼﾞ                 ";
CUB	JPN_SF_PS1_PB4_CheckMode[]			= "PS1,PB4 ｶｸﾆﾝﾓｰﾄﾞ    ";/* Add by Y.Kano 2003/12/18 */
CUB	JPN_Stop[]							= "              ｽﾄｯﾌﾟ ";/* Add by Y.Kano 2003/12/18 */
CUB	JPN_PleaseNonPaper[]				= "ｷﾛｸｼ ｦ ﾄﾘﾉｿﾞｲﾃｸﾀﾞｻｲ ";/* Add by Y.Kano 2003/12/18 */
CUB	JPN_SF_PS1_PB4_Error[]				= "PS1,PB4 ｶｸﾆﾝｼﾃｸﾀﾞｻｲ ";/* Add by Y.Kano 2003/12/26 */
CUB	JPN_SF_PS1_Error[]					= "PS1 ｶｸﾆﾝｼﾃｸﾀﾞｻｲ     ";/* Add by Y.Kano 2003/12/26 */
CUB	JPN_SF_PB4_Error[]					= "PB4 ｶｸﾆﾝｼﾃｸﾀﾞｻｲ     ";/* Add by Y.Kano 2003/12/26 */
#endif

#if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)	/* ＰＳ１、ＰＳ２、ＰＢ４閾値自動調整モード by Y.Kano 2004/10/06 */
CUB JPN_SF_PS1_PS2_PB4_AdjustMode[]		= "PS1,PS2,PB4 ｼｷｲﾁｾｯﾃｲ";
CUB	JPN_PleaseNonPaper[]				= "ｷﾛｸｼ ｦ ﾄﾘﾉｿﾞｲﾃｸﾀﾞｻｲ ";
CUB	JPN_SF_PS1_PS2_PB4_Error[]			= "PS1,PS2,PB4 ﾄﾘｺﾐﾁｴﾗｰ";
CUB	JPN_SF_PS1_PS2_Error[]				= "PS1,PS2 ﾄﾘｺﾐﾁｴﾗｰ    ";
CUB	JPN_SF_PS1_PB4_Error[]				= "PS1,PB4 ﾄﾘｺﾐﾁｴﾗｰ    ";
CUB	JPN_SF_PS1_Error[]					= "PS1 ﾄﾘｺﾐﾁｴﾗｰ        ";
CUB	JPN_SF_PS2_PB4_Error[]				= "PS2,PB4 ﾄﾘｺﾐﾁｴﾗｰ    ";
CUB	JPN_SF_PS2_Error[]					= "PS2 ﾄﾘｺﾐﾁｴﾗｰ        ";
CUB	JPN_SF_PB4_Error[]					= "PB4 ﾄﾘｺﾐﾁｴﾗｰ        ";
CUB	JPN_Stop[]							= "              ｽﾄｯﾌﾟ ";
CUB	JPN_SensorTest[]					= "ｾﾝｻｰﾃｽﾄ             ";
#endif

#if defined(STOCKHM2) || (PRO_JOURNAL_VER_UP == ENABLE)	/* Added by SMuratec C.P 2004/06/07 *//* by K.Watanabe 2004/10/15 */
/*----------------------------------*
 *	ジャーナルプリント
 *----------------------------------*/
CUB JPN_JournalTx[]						= "[01] ｿｳｼﾝｷﾛｸ        ";
CUB JPN_JournalRx[]						= "[02] ｼﾞｭｼﾝｷﾛｸ       ";
CUB JPN_JournalTxRx[]					= "[03] ｿｳｼﾞｭｼﾝｷﾛｸ     ";
#endif

#if defined(STOCKHM2)	/* Added by SMuratec C.P 2004/06/07 */
CUB	JPN_CommConfirm[]					= "ﾖﾔｸ ｶｸﾆﾝ            ";
CUB JPN_FunctionEnter[]					= "               /ｾｯﾄ ";
CUB JPN_InkConfirm[]					= "ｲﾝｸﾘﾎﾞﾝ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ";
#endif

/** トーン検出設定 */
#if defined(STOCKHM2) || defined(HINOKI3) /* 復活 by SMuratec 夏 2004/7/12*/ /* Add by Y.kano 2004/11/25 */
CUB JPN_SetToneDetectMode[]				= "   ﾄｰﾝ ｹﾝｼｭﾂ ｾｯﾃｲ   ";
CUB JPN_DialToneOn[]					= "ﾀﾞｲﾔﾙﾄｰﾝ ｹﾝｼｭﾂ :\0   ";
CUB	JPN_Off[]							= "OFF                 ";	/* ﾃﾞﾌｫﾙﾄがOFFではじまる場合 */
CUB	JPN_On[]							= "ON                  ";
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec K.W.Q 2005/06/02 */
/** トーン検出設定 */
CUB JPN_KanyuDialToneOn[]				= "ｶﾆｭｳ ﾀﾞｲﾔﾙ ﾄｰﾝ :\0   ";
CUB JPN_DefaultLine[]					= "ﾕｳｾﾝ ｶｲｾﾝ     :\0    ";
CUB JPN_DefaultCOMMethod[]				= "ﾕｳｾﾝ ﾎｳｼｷ     :\0    ";
CUB JPN_KeidenScramleOn[]				= "ｹｲﾃﾞﾝ S ﾕｳｾﾝ  :\0    ";
CUB JPN_KanyuScramleOn[]				= "ｶﾆｭｳ  S ﾕｳｾﾝ  :\0    ";
CUB JPN_Keiden[]						= "ｹｲﾃﾞﾝ               ";
CUB JPN_Kanyu[]							= "ｶﾆｭｳ                ";
CUB JPN_Issei[]							= "ｲｯｾｲ                ";
CUB JPN_Kobetsu[]						= "ｺﾍﾞﾂ                ";
CUB JPN_Hoji[]							= "ﾎｼﾞ                 ";
CUB JPN_S_On[]							= "S:ON                ";
CUB JPN_S_Off[]							= "S:OFF               ";
CUB JPN_Senyo[]							= "ｾﾝﾖｳ                ";

/*	サービス設定 */
CUB JPN_SetS1Bypass[]					= "   S1 ﾊﾞｲﾊﾟｽ        ";
CUB JPN_ScrambleAvailable[]				= "   ｽｸﾗﾝﾌﾞﾙ          ";
CUB JPN_KeyLockOn[]						= "   ｷｰ ﾛｯｸ           ";
CUB JPN_SendLevel[]						= "   ｿｳｼｭﾂ ﾚﾍﾞﾙ       ";
CUB JPN_DTMFSendLevel[]					= "   DTMF ｿｳｼｭﾂ ﾚﾍﾞﾙ  ";
#if (1)
CUB JPN_IsseiRingCount[]				= "   ｲｯｾｲ ﾒｲﾄﾞｳ ｼﾞｶﾝ  ";
CUB JPN_RingTimeout[]					= "ﾋﾞｮｳ                ";
#else
CUB JPN_IsseiRingCount[]				= "   ｲｯｾｲ ﾒｲﾄﾞｳ ｶｲｽｳ  ";
#endif
CUB JPN_IsseiAbility[]					= "   ｲｯｾｲｼﾚｲ ﾉｳﾘｮｸ    ";
CUB JPN_IsseiTimeOut[]					= "   ｲｯｾｲ ﾀｲﾑｱｳﾄ      ";
CUB JPN_RemoteRxDialOne[]				= "   ﾘﾓｰﾄ ﾄｸﾊﾞﾝ ｹﾀｽｳ  ";
CUB JPN_KeidenRxPriority[]				= "   ｹｲﾃﾞﾝ ﾕｳｾﾝ ｼﾞｭｼﾝ ";
CUB JPN_FPGAVersion[]					= "   FPGA ﾊﾞｰｼﾞｮﾝ     ";
CUB JPN_KeidenDialTone[]				= "   ｹｲﾃﾞﾝ ﾀﾞｲﾔﾙ ﾄｰﾝ  ";

CUB JPN_S1Bypass[]						= "S1 ﾊﾞｲﾊﾟｽ           ";
CUB JPN_Scramble[]						= "ｽｸﾗﾝﾌﾞﾙ             ";
CUB JPN_KeidenKanyu[]					= "ｹｲﾃﾞﾝ/ｶﾆｭｳ          ";
CUB JPN_IsseiKobetsu[]					= "ｲｯｾｲ/ｺﾍﾞﾂ           ";
CUB JPN_S_OnOFF[]						= "S:ON/OFF            ";
CUB JPN_KyotsuSenyo[]					= "ｷｮｳﾂｳ/ｾﾝﾖｳ          ";
CUB JPN_AutoRx[]						= "ｼﾞﾄﾞｳ ｼﾞｭｼﾝ         ";
#if (0)		/* 警察FAX DVT_ID27 Delete by SMuratec K.W.Q 2005/10/28 */
CUB JPN_KeidenIssei[]					= "ｹｲﾃﾞﾝ ｲｯｾｲ          ";
CUB JPN_KeidenKobetsu[]					= "ｹｲﾃﾞﾝ ｺﾍﾞﾂ          ";
#endif
CUB JPN_RingCount[]						= "ﾒｲﾄﾞｳ ｶｲｽｳ          ";
CUB JPN_IsseiSpeed[]					= "ｼﾝｺﾞｳ ｿｸﾄﾞ          ";
CUB JPN_IsseiCode[]						= "ﾌｺﾞｳｶ ﾎｳｼｷ          ";
CUB JPN_IsseiMinScanLineTime[]			= "ﾃﾞﾝｿｳ ｼﾞｶﾝ          ";
CUB JPN_NumberOfRings_Keiden[]			= "ｹｲﾃﾞﾝ ｶｲｽｳ          ";
CUB JPN_NumberOfRings_Kanyu[]			= "ｶﾆｭｳ ｶｲｽｳ           ";

/*	電話呼出中	*/
CUB JPN_KeidenTelBell[]					= "ﾖﾋﾞﾀﾞｼﾁｭｳ(ｹｲﾃﾞﾝ)    ";
CUB JPN_KanyuTelBell[]					= "ﾖﾋﾞﾀﾞｼﾁｭｳ(ｶﾆｭｳ)     ";

CUB JPN_Telephone[]						= "ﾃﾞﾝﾜ                ";

/*	指令モード	*/
CUB JPN_IsseiShireiKido[]				= "ｼﾚｲﾂｳｼﾝ ｷﾄﾞｳ        ";

/* S1アラーム */
CUB JPN_S1Alarm[]						= "Sｱﾗｰﾑ               ";

/* パネルキーテスト用 */
CUB JPN_SF_KeidenKanyu[]				= "ｹｲﾃﾞﾝ/ｶﾆｭｳ          ";
CUB JPN_SF_IsseiKobetsu[]				= "ｲｯｾｲ/ｺﾍﾞﾂ           ";
CUB JPN_SF_S_OnOff[]					= "S:ON/OFF            ";
CUB JPN_SF_KyotsuSenyo[]				= "ｷｮｳﾂｳ/ｾﾝﾖｳ          ";

/* 工場ファンクション */
CUB JPN_SF_CopyOnetouchA_ToAll[]		= "ﾜﾝﾀｯﾁﾃﾞｰﾀ ﾌｨﾙ       ";
CUB JPN_SF_Transmit1100HzTone[]			= "1100Hz ｿｳｼｭﾂ  :     ";
CUB JPN_SF_TransmitV29Data[]			= "V29 ｿｳｼｭﾂ     :     ";

#endif		/* End of (defined (KEISATSU)) */

#if defined(STOCKHM2) /* Add by SMuratec C.P 2004/07/23 */
CUB JPN_VolumeControl[]					= "    ｵﾝﾘｮｳ ｾｯﾄ       ";
#endif

#if (PRO_RTC_RX5C338A == ENABLE)
CUB JPN_RTC_Init[]						= "RTCｲﾆｼｬﾗｲｽﾞ         ";
#endif

CUB	JPN_WordingTail[]					= "\0";	/* ﾜｰﾃﾞｨﾝｸﾞｻｲｽﾞ計算用(H8の様にﾜｰﾃﾞｨﾝｸﾞを縦に並べる場合必要) */
#undef	CUB
