/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_WRD0.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 帳票用固定文字列
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\lst_def.h"

#if (PRO_CPU == SH7043) /* T.Nose 1996/07/04 */
	#pragma section LST_WRD0	/* セクション名の指定 CLST_WRD0 */
#endif

#define	CUB		CONST UBYTE

#if (PRO_CPU == SH7043)
CUB PWRD_WordingTop[]		= "\0"; /* 各国ワーディング先頭位置認識用 1996/07/04 T.Nose */
#endif

/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの先頭に入れる) */
CUB	PWRD_HEAD[]				= "";

/* 送信証　受領証 */
CUB	PWRD_TransConfReport[]	= "** Transmit Conf.Report **";
CUB	PWRD_RecConfReport[] 	= "** Receive Conf.Report **";
CUB	PWRD_FromTo[] 			= "--->";
CUB	PWRD_CommNo[] 			= "No.\000       ";
CUB	PWRD_CommMode[] 		= "Mode\000    ";
CUB	PWRD_CommStartTime[] 	= "Time\000    ";
CUB	PWRD_CommPages[] 		= "Pages\000   ";
CUB	PWRD_CommResult[] 		= "Result\000  ";
#if ( PRO_MAKER == FX )
CUB	PWRD_Normal[] 			= "Standard";
CUB	PWRD_Fine[] 			= "Fine\000 ";
CUB	PWRD_SFine[] 			= "SuperFine";
CUB	PWRD_Gray[] 			= "Halftone";
#else
CUB	PWRD_Normal[] 			= "NORMAL\000 ";
CUB	PWRD_Fine[] 			= "FINE\000 ";
 #if (PRO_OKI == ENABLE) /* OKI仕様 By T.Fukumoto 98/07/03 */
CUB	PWRD_SFine[] 			= "Ex-FINE\000 ";
 #else
CUB	PWRD_SFine[] 			= "S-FINE\000  ";
 #endif
 #if (PRO_PITNEYBOWES == ENABLE)
CUB	PWRD_Gray[] 			= "PHOTO\000  ";
CUB	PWRD_HFine[] 			= "H-FINE\000  ";	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
CUB	PWRD_HGray[] 			= "H PHOTO\000";	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
 #else
CUB	PWRD_Gray[] 			= "GRAY\000   ";
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SANYO仕様の追加 2000/02/24 N.Kondo */  /* Add by Y.Kano 2003/07/11 */
CUB	PWRD_Fine_S[] 			= "FINE\000 ";
CUB	PWRD_SFine_S[] 			= "S-FINE\000  ";
#endif
CUB	PWRD_Pages[] 			= "Page(s)";
CUB	PWRD_FaxD[] 			= "Fax:";

/* 通信管理レポート */
CUB	PWRD_TransmitJournal[]	= "[Transmit]      ";
CUB	PWRD_RecieveJournal[]	= "[Receive]       ";
CUB	PWRD_ContNo[]			= " No. ";
CUB	PWRD_RemoteFrom[]		= " From:  ";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題（終端をNULLで判断していない）があるので、ﾜｰﾃﾞｨﾝｸﾞを最大5ﾊﾞｲﾄ・ｺﾛﾝの位置固定(英語参照)にすること */
CUB	PWRD_RemoteTo[]			= "  To:   ";
CUB	PWRD_Mode[] 			= "  Mode\000  ";
#if ( PRO_MAKER == FX )
CUB	PWRD_Start[] 			= "Transmit";	/* 6/26 FX.ENG */
#else
CUB	PWRD_Start[] 			= " Start\000 ";
#endif
CUB	PWRD_Received[] 		= "Received";
CUB	PWRD_Time[] 			= " Time ";
CUB	PWRD_Page[] 			= "Page";
CUB	PWRD_Code[] 			= "Code";
CUB	PWRD_Result[] 			= "Result\000";
CUB	PWRD_Note[] 			= " Note\000";
CUB	PWRD_AltNo[] 			= "(Alt.No)";
CUB	PWRD_Secure[] 			= "Secure\000";
CUB	PWRD_Relay[] 			= "Relay\000 ";
CUB	PWRD_Polling[] 			= "Polling";
CUB	PWRD_DbPolling[] 		= "DB-Poll";
CUB	PWRD_Manual[] 			= "Manual\000";
CUB	PWRD_RelayedTxReport[]	= "RlyRpt.";
#if defined(USA) || defined(US2) || defined(AUS)	/*95/05/20 By j.masuda */
CUB	PWRD_FIP_Tx[] 			= "MFS_Tx\000";
CUB	PWRD_FIP_Rx[] 			= "MFS_Rx\000";
CUB	PWRD_FIP_Poll[] 		= "MFS_Pol";
CUB	PWRD_FIP_Sec[] 			= "MFS_Sec";
#else								/*95/05/20 By j.masuda */
CUB	PWRD_FIP_Tx[] 			= "FIP_Tx\000";
CUB	PWRD_FIP_Rx[] 			= "FIP_Rx\000";
CUB	PWRD_FIP_Poll[] 		= "FIP_Pol";
CUB	PWRD_FIP_Sec[] 			= "FIP_Sec";
#endif
CUB	PWRD_BrdCast[]	 		= "BRDCAST";
CUB	PWRD_Ok[] 				= "O K";
/* Fｺｰﾄﾞ */
CUB	PWRD_SUB_Tx[]			= "FcodeTx";
CUB PWRD_SEP_Rx[]			= "FC-Poll";
CUB PWRD_SUB_Rx[]			= "FcodeRx";
/* ｽｸﾗﾝﾌﾞﾙ */
CUB	PWRD_Cipher_Tx[]		= "SCRAMBL";                /* wording by honda 1997/11/10 */
CUB	PWRD_Cipher_Rx[]		= "SCRAMBL";                /* wording by honda 1997/11/10 */

/* 短縮ダイヤルリスト */
CUB	PWRD_TeleDirectory[] 	= "** Speed-Dial Directory **";
CUB	PWRD_No[]				= "No.";
#if ( PRO_MAKER == FX )
CUB	PWRD_RemoteLocation[]	= "     Name\000      ";	/* 6/28 FX.ENG */
CUB	PWRD_TeleNumber[] 		= "  Telephone No.   ";		/* 6/28 FX.ENG */
CUB	PWRD_GroupNumber[] 		= "Group No.       ";		/* 6/28 FX.ENG */
#else
CUB	PWRD_RemoteLocation[]	= "Remote Location\000";
CUB	PWRD_TeleNumber[] 		= " Telephone Number ";
CUB	PWRD_GroupNumber[] 		= "  Group Number  ";	/* ANZUのみ */
#endif
CUB	PWRD_Cost[]				= " Charge ";	/* POPLAR_Hのみ */

/* 属性リスト */
CUB PWRD_AttributeList[]	= "Attribute List";
CUB PWRD_Attribute[]		= "Attr.";

/* ワンタッチダイヤルリスト */
CUB	PWRD_OneDirectory[] 	= "** One-Touch Directory ** ";

/* プログラムリスト */
CUB	PWRD_DelyTime[] 		= " Start  ";
CUB	PWRD_Option[] 			= " Option\000";
CUB	PWRD_NotTime[] 			= "--:--";

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/26 By M.Kuwahara */
CUB	PWRD_PRG_Onetouch[]		= "One-Touch Directory   ";
CUB	PWRD_PRG_Speed[]		= "Speed-Dial Directory  ";
CUB	PWRD_PRG_Program[]		= "P One-Touch Directory ";
CUB	PWRD_PRG_SecureBox[]	= "SecureMail List       ";
CUB	PWRD_PRG_ComReserve[]	= "Command List          ";
 #if defined(SAKAKI) && defined(JP0) /* By M.Maeda 2002/10/21 */
CUB	PWRD_PRG_Journal[]		= "Journal(Tx/Rx)        ";
 #else
  #if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
CUB	PWRD_PRG_Journal[]		= "All Journals          ";
CUB	PWRD_PRG_DailyReport[]	= "Day Journal           ";
  #else
CUB	PWRD_PRG_Journal[]		= "Journal               ";
  #endif
 #endif
CUB	PWRD_PRG_Group[]		= "Group Directory       ";
CUB	PWRD_PRG_Setting[]		= "User Settings         ";
CUB	PWRD_PRG_Message[]		= "Fax Message From:     ";
CUB	PWRD_PRG_CostBase[]		= "Charge                ";
CUB	PWRD_PRG_DepartCode[]	= "Department List       ";
CUB	PWRD_PRG_BatchBox[]		= "BatchSendBox List     ";
CUB	PWRD_PRG_BatchDoc[]		= "BatchSendBoxDoc.      ";
CUB	PWRD_PRG_F_CodeBox[]	= "F-Code Box List       ";
CUB	PWRD_PRG_F_CodeDoc[]	= "F-Code List Of Doc.   ";
CUB	PWRD_PRG_BlockJunk[]	= "Block Junk Fax List   ";
CUB	PWRD_PRG_ND_Dial[]		= "Number Display List   ";
CUB	PWRD_PRG_ND_Journal[]	= "Number Display Journal";
CUB	PWRD_PRG_Warp[]			= "FaxWarp List          ";
 #if defined(SAKAKI) && defined(JP0) /* 2002/08/26 By M.Maeda */
CUB	PWRD_PRG_JournalTx[]	= "Journal(Tx)           ";
CUB	PWRD_PRG_JournalRx[]	= "Journal(Rx)           ";
 #endif
CUB PWRD_ListName[]			= "List Name";
CUB PWRD_CommReserved[]		= "Command ";
CUB PWRD_List[]				= "List";
CUB PWRD_DocStore[]			= "Store   ";
#endif

/* グループリスト */
CUB	PWRD_GroupDirectory[] 	= "** Group Directory **";
#if ( PRO_MAKER == FX )
CUB	PWRD_Location[]			= "  Name\000  ";
#else
CUB	PWRD_Location[]			= " Location";
#endif

/* 機器設定リスト */
CUB	PWRD_MachineSettings[] 	= "  ** User Settings ** ";
#if ( PRO_MAKER == FX )
CUB	PWRD_SubscriberID[] 	= "SendHeader";
#else
CUB	PWRD_SubscriberID[] 	= "Name:\000    ";
#endif
CUB	PWRD_SubscriberKanaID[]	= "Kana ID         ";
#if ( PRO_MAKER == FX )
CUB	PWRD_SubscriberNb[] 	= "Local ID    ";	/* 10/18 FX.ENG */
CUB	PWRD_JournalAutoPrt[] 	= "Auto Activity Rep";
CUB	PWRD_SecureDocHold[] 	= "Rcv MB Hold Time";
#else
CUB	PWRD_SubscriberNb[] 	= "Fax Number: ";
#if (PRO_OKI == ENABLE) /* OKI仕様 By T.Fukumoto 98/07/03 */
CUB	PWRD_JournalAutoPrt[] 	= "Report AutoPrint ";
#else
CUB	PWRD_JournalAutoPrt[] 	= "Journal AutoPrint";
#endif
 #if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	PWRD_SecureDocHold[] 	= "Secure Doc.Hold\000 ";
 #else
CUB	PWRD_SecureDocHold[] 	= "Secure Doc.Hold\000";
 #endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif
#if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/07/21 */
CUB	PWRD_PhoneType[]		= "STD Phone Type\000";
CUB	PWRD_EXTPhoneType[]		= "EXT Phone Type\000";
#else
CUB	PWRD_PhoneType[]		= "Phone Type";
#endif

#if ( PRO_MAKER == FX )
CUB	PWRD_ConfReport[]		= "Monitor Rep";
CUB	PWRD_ScannerWidth[]		= "Scan Width   ";	/* 6/28 FX.ENG */
CUB	PWRD_PrimaryMode[]		= "Resolution\000   ";	/* 6/28 FX.ENG */
CUB	PWRD_Contrast[]			= "Density\000      ";	/*11/01 FX.ENG */
CUB	PWRD_DialingPause[]		= "PauseDuration";
#else
#if defined(STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	PWRD_ConfReport[]		= "Report Type ";
#else
CUB	PWRD_ConfReport[]		= "Report Type";
#endif
CUB	PWRD_ScannerWidth[]		= "Scanner Width";
CUB	PWRD_PrimaryMode[]		= "Primary Mode\000 ";
CUB	PWRD_Contrast[]			= "Contrast\000     ";
CUB	PWRD_DialingPause[]		= "Dialing Pause";
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)/* SANYO仕様の追加 2000/02/24 N.Kondo */	/* Add by Y.Kano 2003/07/11 */
CUB	PWRD_Contrast_S[]		= "Contrast\000     ";
 #endif
#endif
#if !defined(KEISATSU)		/* 警察FAX Modify by SMuratec 夏 2005/07/21 */
CUB	PWRD_RinggingTimes[]	= "# of Rings\000   ";
#endif
#if ( PRO_MAKER == FX )
CUB	PWRD_ReductionRate[]	= "Reduction %   ";	/* 6/28 FX.ENG */
#else
CUB	PWRD_ReductionRate[]	= "Reduction Rate";
#endif
CUB	PWRD_EcmMode[]			= "ECM Mode";
CUB	PWRD_CopyProtect[]		= "Copy Protect";
CUB	PWRD_RemoteDiagnostic[]	= "Service Mode\000    ";
CUB	PWRD_RedialTimes[]		= "Redial Settings\000 ";
CUB	PWRD_Holdmelody[]		= "Hold Melody\000";
#if (PRO_OKI == ENABLE) /* OKI仕様 By T.Fukumoto 98/07/03 */
CUB	PWRD_Passcode[]			= "Password";
#else
CUB	PWRD_Passcode[]			= "Passcode";
#endif
CUB	PWRD_CloseNetwork[]		= "Closed Network\000";
CUB	PWRD_SilentOperation[]	= "Silent Mode\000    ";	/* JPN以外 */
#if ( PRO_MAKER == FX )
CUB	PWRD_SecurityTx[]		= "Secure Send      ";	/* 6/28 FX.ENG */
CUB	PWRD_BlockjunkFax[]		= "No Junk Fax\000    ";
#else
CUB	PWRD_SecurityTx[]		= "Security Transmit";
CUB	PWRD_BlockjunkFax[]		= "Block Junk Fax\000 ";
#endif
CUB	PWRD_RecieveMode[]		= "Receive Mode";
#if ( PRO_MAKER == FX )
CUB	PWRD_PageCompound[]		= "Combine Pages    ";	/* 9/17 FX.ENG */
#else
CUB	PWRD_PageCompound[]		= "Half-Page Recept.";
#endif
CUB	PWRD_SortingCopy[]		= "Sorting Copy";		/* POPLAR_Lのみ */
CUB	PWRD_Rs232c[]			= "RS232C Parameters";
CUB	PWRD_Stamp[]			= "Stamp\000 ";
CUB	PWRD_MemoryTx[]			= "Memory Transmit";
CUB	PWRD_RelayedRelayTx[]	= "Relayed Relay     ";

#if (PRO_PANEL == KANJI)
/* ＰＯＰＬＡＲ＿ＨはＬＣＤに待機モードを表示していないので、機器設定リストに表示させます。 By O.Kimoto 1998/03/02 */
 #if (PRO_DIALIN_SW == ENABLE) /* By H.Fujimura 2002/07/11 */
CUB	PWRD_DialIn[]			= "DialinNo         ";
 #else
CUB	PWRD_DialIn[]			= "DialinNo\0        ";
 #endif
CUB	PWRD_DialIn_Item1[]		= "Fax/Tel1/Tel2   ";
CUB	PWRD_DialIn_Item2[]		= "Fax/Tel1        ";
#else
CUB	PWRD_DialIn[]			= "DialinNo  Fax/Tel";	/* (JPN) */
#endif

CUB	PWRD_BellTime[]			= "  Times";			/* (JPN) */
CUB	PWRD_RingMastr[]		= "DRD Option       ";
CUB	PWRD_CopyReduction[]	= "Copy Reduc.Rate  ";	/**	'.'の後のスペースをとる By H.Hirao 1996/06/03	*/
CUB	PWRD_PaperSize[]		= "Paper Size       ";	/* ANZUのみ */
CUB PWRD_PC_PaperManual[]	= "PC Prn Paper Size";	/* ANZUのみ *//* bythonda1998/03/24 PCﾌﾟﾘﾝﾄﾃｻﾞｼﾖｳｼ */
CUB	PWRD_PaperType[]		= "Paper Type     ";	/* SAKAKIのみ */
CUB	PWRD_ToneLine[] 		= "Tone\000";
#if ( PRO_MAKER == FX )
CUB	PWRD_Pps10[] 			= "10pps";	/* 6/28 FX.ENG */
CUB	PWRD_Pps20[] 			= "20pps";	/* 6/28 FX.ENG */
#else
CUB	PWRD_Pps10[] 			= "Pulse";
CUB	PWRD_Pps20[] 			= "Pulse";
#endif
#if defined(STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	PWRD_TxConf[]			= "TCR\000        ";
#else
CUB	PWRD_TxConf[]			= "TCR\000    ";
#endif
CUB	PWRD_RxConf[]			= "RCR\000     ";
CUB	PWRD_A4[] 				= "A4";
CUB	PWRD_B4[] 				= "B4";
CUB	PWRD_A3[] 				= "A3";
CUB	PWRD_F4[] 				= "F4";
#if (PRO_PITNEYBOWES == ENABLE)			
CUB PWRD_LETTER[]			= "LTR";	/* ＰＢ仕様の為追加 By S.Fukui Aug. 25,1998 */
CUB PWRD_LEDGER[]			= "LD";		/* ＰＢ仕様の為追加 By S.Fukui Aug. 25,1998 */
#endif
#if ( PRO_MAKER == FX )
CUB	PWRD_Dark[] 			= "Darker";
CUB	PWRD_NormalDark[] 		= "Normal";
CUB	PWRD_Light[] 			= "Lighter";
#else
CUB	PWRD_Dark[] 			= "DARK\000 ";
CUB	PWRD_NormalDark[] 		= "NORMAL";
CUB	PWRD_Light[] 			= "LIGHT\000 ";
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)/* SANYO仕様の追加 2000/02/24 N.Kondo *//* Add by Y.Kano 2003/07/11 */
CUB	PWRD_Dark_S[] 			= "DARK\000 ";
CUB	PWRD_Light_S[] 			= "LIGHT\000 ";
#endif
CUB	PWRD_MinuteMark[] 		= "Minutes";
CUB	PWRD_SecondMark[] 		= "Sec.";
#if ( PRO_MAKER == FX )
CUB	PWRD_Try[] 				= "Times";
#else
CUB	PWRD_Try[] 				= "     ";
#endif
CUB	PWRD_Attemps[] 			= "Attempts";
CUB	PWRD_On[] 				= "ON\000";
CUB	PWRD_Off[] 				= "OFF";
CUB	PWRD_Mode1[]			= "Mode1";
CUB	PWRD_Mode2[]			= "Mode2";
CUB	PWRD_Mode3[]			= "Mode3";
CUB	PWRD_P100[] 			= "100%";
CUB	PWRD_P97[] 				= "97%";
CUB	PWRD_P91[] 				= "91%";
CUB	PWRD_P81[] 				= "81%";
CUB	PWRD_P75[] 				= "75%";
#if ( PRO_MAKER == FX )
CUB	PWRD_ThValue00mm[] 		= "Thrshld   00 mm";	/* 6/28 FX.ENG */
CUB	PWRD_TelFax[] 			= "Tel/Fax\000 ";
CUB	PWRD_Tel[] 				= "Tel\000";
CUB	PWRD_Fax[] 				= "Fax\000";
CUB	PWRD_AnsFax[] 			= "Ans/Fax\000";	/* 6/28 FX.ENG */
#else
CUB	PWRD_ThValue00mm[] 		= "Margin    00 mm";
CUB	PWRD_TelFax[] 			= "TEL/FAX\000 ";
CUB	PWRD_Tel[] 				= "TEL\000";
CUB	PWRD_Fax[] 				= "FAX\000";
 #if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 1998/10/20 */
CUB	PWRD_AnsFax[] 			= "TAD/FAX\000";
 #else
CUB	PWRD_AnsFax[] 			= "ANS/FAX\000";
 #endif
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec K.W.Q 2003/11/28 */
CUB	PWRD_DialInRx[]			= "DialinNo\0";
#endif

CUB	PWRD_FaxTel[]			= "FAX/TEL\000 "; /**	追加 For ANZU By H.Hirao 1996/05/21	*/
CUB	PWRD_Bps300[] 			= "300";
CUB	PWRD_Bps600[] 			= "600";
CUB	PWRD_Bps1200[] 			= "1200";
CUB	PWRD_Bps2400[] 			= "2400";
CUB	PWRD_Bps4800[] 			= "4800";
CUB	PWRD_Bps9600[] 			= "9600";
CUB	PWRD_Bps19200[] 		= "19200";
CUB	PWRD_BpsVariable[] 		= "Variable";			/** 追加 For POPLA By M.Kuwahara 1997/03/05 */
CUB	PWRD_None[] 			= "NONE";
CUB	PWRD_Odd[] 				= "ODD";
CUB	PWRD_Even[] 			= "EVEN";
CUB	PWRD_S1bit[] 			= "1bit";
CUB	PWRD_S2bit[] 			= "2bit";
CUB	PWRD_P7bit[] 			= "7bit";
CUB	PWRD_P8bit[] 			= "8bit";
CUB	PWRD_Days[] 			= "Days";
CUB	PWRD_Auto[] 			= "Auto\000";
CUB	PWRD_Pattern[]			= "Pattern:";	/* (USA) */
CUB	PWRD_Letter[]			= "Letter\0";
CUB	PWRD_Legal[]			= "Legal\0";
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* '95.07/20 By K.Watanabe *//* by K.Watanabe 2004/10/12 */
CUB	PWRD_RxAlarm[]			= "Rx Alarm     "; /* Add By H.H 1996/08/28 */
CUB	PWRD_MercuryPause[]		= "Prefix Pause "; /* Add By H.H 1996/08/28 Mercury Pause -> Prefix Pause */
CUB PWRD_MercuryNumber[]	= "Dial Prefix Number";/* Added by SMuratec C.P 2004/07/08 for prefix */
#endif
#if ( PRO_MAKER == FX )
CUB	PWRD_MesageTrans[]		= "Annotation      ";
#else
CUB	PWRD_MesageTrans[]		= "Cover Page      ";
#endif
CUB	PWRD_RemoteSecurityRx[]	= "Security Rx   ";
CUB	PWRD_NormalPaper[]		= "Normal\000   ";	/* SAKAKIのみ */
CUB PWRD_ThermalPaper[]		= "Thermal\000  ";	/* SAKAKIのみ */
CUB	PWRD_DepartmentProtect[]= "Department Protect";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
CUB	PWRD_Department[]		= "Department";				/* 追加 For ANZU By H.Hirao Feb 29,1996 */
CUB	PWRD_PINAccessMode[]	= "PIN Access Mode";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#if defined(USA)
CUB	PWRD_DayLightSaving[]	= "Daylight Saving";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#endif
CUB	PWRD_OperationProtect[]	= "Operation Protect\000";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#if (PRO_REMOTE_RX == ENABLE)
CUB	PWRD_RemoteReceive[]	= "Remote Transfer\000  ";	/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	PWRD_OnHookReceive[]	= "Onhook Transfer\000  ";	/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif

/* PRO_MULTI_LINE */
/* 基本的に下記ワーディングは
** 		見出し用：半角16文字
** 		内容用  ：半角 8文字
** とします。
** by O.Kimoto 1997/07/10
*/
						/*	   12345678901234567890 */
CUB PWRD_MultiTxRxType[]	= "Tx/Rx Type\000     ";
CUB PWRD_TxRx[]				= "Tx/Rx\000  ";
CUB PWRD_Tx[]				= "Tx\000     ";
CUB PWRD_Rx[]				= "Rx\000     ";
CUB PWRD_MultiLineType[]	= "line Type\000      ";
CUB PWRD_PstnLine[]			= "PSTN\000   ";
CUB PWRD_PbxLine[]			= "PBX\000    ";
CUB PWRD_PstnAccessNumber[]	= "Access No.   :\000 ";
CUB PWRD_LineNumber[]		= "Line Number:\000   ";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題（終端をNULLで判断していない）があるので、ﾜｰﾃﾞｨﾝｸﾞを最大11ﾊﾞｲﾄ・ｺﾛﾝの位置固定(日本語参照)にすること *//*  By O.Kimoto 1997/07/10 */
/** CUB	PWRD_SubscriberKanaID[]	= "発信元名(ｶﾅID)  "; */
/** CUB	PWRD_PhoneType[]		= "通信回線\000 "; */

#if (PRO_MULTI_LINE == ENABLE)	/*  By O.Kimoto 1997/01/06 */
CUB	PWRD_AddErrorMessage[4][31] = {
					/* 123456789012345678901234567890 */
					  "Check the Tx and Rx settings. ",	/** D.0.10 */
					  "Check the attrib. of dial num.",	/** D.0.11 */
					  "Check no. dialed and line type",	/** D.0.12 */
					  "Check no. dialed and line type"	/** D.0.13 */
					  };
#endif

/* 記録紙サイズ */
CUB	PWRD_Paper_A5[]			= "A5_P\0  ";
 #if defined(USA)
CUB	PWRD_Paper_Letter[]		= "Letter\0";
 #else
CUB	PWRD_Paper_Letter[]		= "Ltr_P\0 ";
 #endif
 #if defined(USA)
CUB	PWRD_Paper_A4[]			= "A4_P\0  ";
 #else
CUB	PWRD_Paper_A4[]			= "A4\0    ";
 #endif
 #if defined(USA) || defined(TWN) /* 1998/01/09 Y.Matsukuma */
CUB	PWRD_Paper_Legal[]		= "Legal\0 ";
 #else
CUB	PWRD_Paper_Legal[]		= "Legal_P";
 #endif
CUB	PWRD_Paper_B5R[]		= "B5R_P\0 ";
CUB	PWRD_Paper_B4[]			= "B4_P\0  ";
CUB	PWRD_Paper_A3[]			= "A3_P\0  ";
CUB	PWRD_Paper_A4R[]		= "A4R_P\0 ";
CUB	PWRD_Paper_LetterR[]	= "LtrR_P\0";
 #if defined(TWN) || defined(AUS)	/* 1998/01/08 Y.Matsukuma */
CUB	PWRD_Paper_F4[]			= "F4\0    ";
 #else
CUB	PWRD_Paper_F4[]			= "F4_P\0  ";
 #endif
CUB	PWRD_Paper_A5R[]		= "A5R_P\0 ";
CUB	PWRD_Paper_Postcard[]	= "Post_P\0";
CUB	PWRD_Paper_LD[]			= "Ld_P\0  ";
CUB	PWRD_Paper_GLetterR[]	= "GLtrR_P";
CUB	PWRD_Paper_ExecutiveR[]	= "ExeR_P\0";
CUB	PWRD_Paper_InvoiceR[]	= "InvR_P\0";
CUB	PWRD_Paper_GLegal[]		= "GLegl_P";
CUB	PWRD_Paper_GLetter[]	= "GLtr_P\0";
CUB	PWRD_Paper_Card[]		= "Card_P\0";
CUB	PWRD_Paper_Executive[]	= "Exe_P\0 ";
CUB	PWRD_Paper_B5[]			= "B5_P\0  ";
CUB	PWRD_Paper_C5[]			= "C5_P\0  ";
CUB	PWRD_Paper_HalfLetter[]	= "HLtr_P\0";
CUB	PWRD_Paper_Invoice[]	= "Inv_P\0 ";
CUB	PWRD_Paper_B6[]			= "B6_P\0  ";
CUB	PWRD_Paper_DL[]			= "DL_P\0  ";
CUB	PWRD_Paper_CM10[]		= "CM10_P\0";
CUB	PWRD_Paper_A6[]			= "A6_P\0  ";
CUB	PWRD_Paper_Monarch[]	= "Mnc_P\0 ";
CUB	PWRD_Paper_35[]			= "3x5_P\0 ";
CUB	PWRD_Paper_User[]		= "User_P\0";

/* 記録紙サイズ POPLAR用 */
CUB	PWRD_PaperSize_A5[]			= "A5\0    ";
CUB	PWRD_PaperSize_Letter[]		= "Letter\0";
CUB	PWRD_PaperSize_A4[]			= "A4\0    ";
CUB	PWRD_PaperSize_Legal[]		= "Legal\0 ";
CUB	PWRD_PaperSize_B5R[]		= "B5R\0   ";
CUB	PWRD_PaperSize_B4[]			= "B4\0    ";
CUB	PWRD_PaperSize_A3[]			= "A3\0    ";
CUB	PWRD_PaperSize_A4R[]		= "A4R\0   ";
CUB	PWRD_PaperSize_LetterR[]	= "LtrR\0  ";
CUB	PWRD_PaperSize_F4[]			= "F4\0    ";
CUB	PWRD_PaperSize_A5R[]		= "A5R\0   ";
CUB	PWRD_PaperSize_Postcard[] 	= "Post\0  ";
CUB	PWRD_PaperSize_LD[]			= "Ld\0    ";
CUB	PWRD_PaperSize_GLetterR[]	= "GLtrR\0 ";
CUB	PWRD_PaperSize_ExecutiveR[]	= "ExeR\0  ";
/*  #if (PRO_KEYPANEL == PANEL_POPLAR_B)  *//* modified by honda 1997/11/14 */
/*  #if defined(USA) || defined(GBR)  */
CUB	PWRD_PaperSize_HalfLetterR[]= "HLtrR\0 ";  /* added by honda 1997/10/04 */
/*   #else  */
/*  CUB	PWRD_PaperSize_InvoiceR[]	= "InvR\0  ";  */
/*   #endif  */
/*   #else  */
/*  CUB	PWRD_PaperSize_InvoiceR[]	= "InvR\0  ";  */
/*  #endif  */
CUB	PWRD_PaperSize_GLegal[]		= "GLegl\0 ";
CUB	PWRD_PaperSize_GLetter[]	= "GLtr\0  ";
CUB	PWRD_PaperSize_Card[]		= "Card\0  ";
CUB	PWRD_PaperSize_Executive[]	= "Exe\0   ";
CUB	PWRD_PaperSize_B5[]			= "B5\0    ";
CUB	PWRD_PaperSize_C5[]			= "C5\0    ";
CUB	PWRD_PaperSize_HalfLetter[]	= "HLtr\0  ";
CUB	PWRD_PaperSize_Invoice[]	= "Inv\0   ";
CUB	PWRD_PaperSize_B6[]			= "B6\0    ";
CUB	PWRD_PaperSize_DL[]			= "DL\0    ";
CUB	PWRD_PaperSize_CM10[]		= "CM10\0  ";
CUB	PWRD_PaperSize_A6[]			= "A6\0    ";
CUB	PWRD_PaperSize_Monarch[]	= "Mnc\0   ";
CUB	PWRD_PaperSize_35[]			= "3x5\0   ";
CUB	PWRD_PaperSize_User[]		= "User\0  ";

/* メモリスイッチ */
#if ( PRO_MAKER == FX )
CUB	PWRD_Machine_P[] 		= "Parameter    ";
#else
CUB	PWRD_Machine_P[] 		= "Machine Param";
#endif
CUB	PWRD_Memory_S[] 		= "Memory Switch";
CUB	PWRD_Uniq_S[]			= "Uniq.Switch  ";			/* 追加 For ANZU By H.Hirao Mar.28.1996 */
CUB	PWRD_BitNumber[] 		= "7654 3210";
CUB	PWRD_Default[] 			= " Default ";
CUB	PWRD_AutoSet[] 			= " Setting ";

/* POPLA追加 -- メモリスイッチの追加 */
CUB PWRD_MainteSwitch[]		= "Mnt Switch   ";

/* キノウリスト */
CUB	PWRD_ProgramList[]		= "Program List    ";

/* 通信予約リスト */
CUB	PWRD_ComReservedList[] 	= " ** Command List **  ";

/* 親展者登録リスト */
CUB	PWRD_SecureMailBList[]	= "** SecureMail List **  ";
#if ( PRO_MAKER == FX )
CUB	PWRD_UserName[] 		= "  Name    ";	/* 6/28 FX.ENG */
#else
CUB	PWRD_UserName[] 		= "User Name ";
#endif
CUB	PWRD_Box[] 				= "Box";

/* カバーページプリント */
CUB	PWRD_CoverPageMes[] 	= "Fax Message From:\000  ";	/* 右端 - 2ﾊﾞｲﾄの後、ｾﾝﾀﾘﾝｸﾞ */

/* 親展受信通知 */
CUB	PWRD_SecureMailNotice[] = " SecureMail  ";

/* 親展原稿消去通知 */
CUB	PWRD_ErasedDocuments[] 	= " Erased Documents ";

/* 代行受信消去通知 */
CUB	PWRD_ErasedDocumemts[] 	= "  Erased Documents  ";

/* 通信予約消去通知 */
CUB	PWRD_ErasedCommands[] 	= " Erased Command  ";
#if ( PRO_MAKER == FX )
CUB	PWRD_MemHoldDate[]		= "Print mailbox by   ";
#else
CUB	PWRD_MemHoldDate[]		= "Print SecureMail by";
#endif

/* チェックメッセージ */
CUB	PWRD_CheckMessage[] 	= "Check Message";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PWRD_MemoryOver[] 		= "Memory Over";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PWRD_PcMemoryOver[]		= "PC Memory Over";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PWRD_ErrorPages[] 		= "Error Page(s):";

/* Ｔ３０モニタ */
CUB	PWRD_T30Monitor[]		= "** T30 Monitor ** ";
CUB	PWRD_TxFrame[]			= "TxFrame";
CUB	PWRD_RxFrame[]			= "RxFrame";
CUB	PWRD_Datalong[]			= "D A T A";
CUB	PWRD_Rs144[]			= "144";
CUB	PWRD_Rs120[]			= "120";
CUB	PWRD_Rs96[]				= " 96";
CUB	PWRD_Rs72[]				= " 72";
CUB	PWRD_Rs48[]				= " 48";
CUB	PWRD_Rs24[]				= " 24";
CUB	PWRD_V17[]				= "V17";
CUB	PWRD_V33[]				= "V33";
CUB	PWRD_V29[]				= "V29";
CUB	PWRD_V27[]				= "V27";
CUB	PWRD_MH[]				= " MH";
CUB	PWRD_MR[]				= " MR";
CUB	PWRD_MMR[]				= "MMR";
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
CUB	PWRD_JBG[]				= "JBG";
#endif
CUB	PWRD_A5[]				= "A5";
CUB	PWRD_A6[]				= "A6";
CUB	PWRD_Wait20[]			= "20";
CUB	PWRD_Wait40[]			= "40";
CUB	PWRD_Wait10[]			= "10";
CUB	PWRD_Wait5[]			= " 5";
CUB	PWRD_Wait0[]			= " 0";
CUB	PWRD_ModeNR[]			= "N";
CUB	PWRD_ModeFN[]			= "F";
CUB	PWRD_ModeSF[]			= "S";
CUB	PWRD_ModeHF[]			= "H";

CUB	PWRD_Main[]				= "MAN";
CUB	PWRD_Reset[]			= "Res";
CUB	PWRD_Error[]			= "Err";
CUB	PWRD_Now[]				= "Now";
CUB	PWRD_DpramTx[]			= "Tx";
CUB	PWRD_DpramRx[]			= "Rx";

/* コウジョウ ファンクション リスト */
CUB	PWRD_FunctionList[]		= "Function List       ";
CUB	PWRD_LedTest[]			= "LED Test            ";
CUB	PWRD_LcdTest[]			= "LCD Test            ";
CUB	PWRD_Pane1keytest[]		= "Key Pad Test        ";
CUB	PWRD_Rs232cTest[]		= "RS232C Test         ";
CUB	PWRD_SramCheck[]		= "SRAM Check          ";
CUB	PWRD_DramCheck[]		= "DRAM Check          ";
CUB	PWRD_RTCTest[]			= "RTC Test            ";

/* オンラインモニタ */
#if ( PRO_CLASS1 == ENABLE )
CUB	PWRD_OnLineMonitor[]	= "< Online Monitor > ";
CUB	PWRD_OnLineTx[]			= "TX";
CUB	PWRD_OnLineRx[]			= "RX";
CUB	PWRD_OnLineData[]		= "Data";
CUB	PWRD_Speed[]			= "Speed";
CUB	PWRD_Command[]			= "Cmd";
CUB	PWRD_Response[]			= "Res";
CUB	PWRD_Abort[]			= "Abt";
#endif

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
CUB PWRD_F_CodeBox_List[]	= "** FCODE Box List **";
CUB PWRD_BoxName[]			= "Box Name\0";
CUB PWRD_SubAddress[]		= " Sub-Address\0 ";
CUB PWRD_CommPasscode[]		= "     Password\0    ";
CUB PWRD_Kind[]				= "Kind\0";
CUB PWRD_NoticeBoard[]		= "Bull\0  ";
CUB PWRD_RecvProtect[]		= "Rx Protect";
CUB PWRD_Replace[]			= "OVWRITE";              /* wording by honda 1997/11/10 */
CUB PWRD_RxPrint[]			= "Rx Print\0 ";
CUB PWRD_TransErase[]		= "Erase Polled Doc.";

#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
CUB PWRD_RelayName[] 		= "Relay ";
CUB PWRD_PutSubscriber[] 	= "TTI   ";
CUB PWRD_Avail[]			= "Avail ";
CUB	PWRD_NoTTI[]			= "No TTI  ";
CUB	PWRD_SUB_Relay[]		= "F-Relay";	/* 1998/09/25 By M.Kuwahara */
CUB	PWRD_SUB_Secure[]		= "F-Sec  ";	/* 1998/09/28 By M.Kuwahara */
#endif

#if (PRO_FCODE_KIND_DISPLAY == ENABLE)
CUB	PWRD_SUB_Bulletin[]		= "F-Bull ";	/* 1998/09/28 By M.Kuwahara */
#endif

/* サブアドレス原稿消去通知 */
CUB PWRD_Del_F_CodeBoxDoc_Notice[]	= "FCODE Boxes Doc. Erased  ";
CUB PWRD_BoxLocation[]		= "Location";
CUB PWRD_ThisBoxErased[]	= "These FCODE Box Documents were erased.";

/* サブアドレスＢＯＸ蓄積原稿リスト */
CUB PWRD_DocumentsNo[]		= " File#\0 ";
CUB PWRD_F_CodeDoc_List[]	= "**FCODE List Of Documents **";

/* サブアドレス受信通知 */
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 1998/10/20 */
CUB PWRD_F_CodeBoxRsv_Notice[]	= "FCODE Box Report ";
#else
CUB PWRD_F_CodeBoxRsv_Notice[]	= "FCODE Box Journal";
#endif
CUB PWRD_F_CodeReci[]		= "FCODE Box Received\0         ";
CUB PWRD_F_ReciDocMemory[]	= "Print ReceivedMail by";
#endif

/* ダイレクトメール防止ダイヤルリスト */
CUB	PWRD_BlockJunkList[]	= " ** Block Junk Fax List ** ";
CUB	PWRD_TelNum[]			= "Tel Number\0";

/* サービスレポート */
CUB	PWRD_ServiceReport[]	= "** Service Report **";

/* ポーリング原稿消去通知 */
CUB	PWRD_ErasePollDoc[]		= "Erased Poll Documents ";

/* 一括送信原稿リスト */
CUB PWRD_BatchTxDocList[]	= "** Batch Send Box Doc. **     "; /* For ANZU 挿入 96/02/13 H.Hirao */

/* 一括送信ＢＯＸリスト */
CUB PWRD_BatchTxBoxList[]	= "** Batch Send Box List **       "; /* For ANZU 挿入 96/02/13 H.Hirao */

CUB PWRD_Batch[]			= "Batch";
CUB PWRD_BoxNo[]			= "Box No.\000   ";

/* 暗号化受信通知リスト */
CUB PWRD_CipherReceiveNotice[]	= " SCRAMBLE RX REPORT ";       /* wording by honda 1998/4/28 */
CUB PWRD_ReceiveNo[]		= "Receive No";
CUB PWRD_KeyClue[]			= "Key Clue    ";         /* wording by honda 1997/11/7 */
CUB PWRD_KeyWordClue[]		= "Key Clue";

/* キーリスト、キーブックリスト */
CUB PWRD_KeyBookList[]		= "**KeyBookList**";
CUB PWRD_KeyWordList[]		= "**  Key  List    **";
CUB PWRD_KeyName[]			= "  Key Title ";
CUB PWRD_Key[]				= " Key  ";

/* 暗号化受信消去通知 */
CUB	PWRD_EraseScrambleRxDoc[]	= "Erased Scrambling Doc.";

/* 消耗品発注票 */
#if defined(JPN)
CUB PWRD_ConsumerOrderSheet[]	= "Order Sheet\0               ";   /* wording by honda 1997/11/13 */
CUB PWRD_ToOrder[]				= "To\0    ";
CUB PWRD_FromOrder[]			= "From\0  ";
CUB PWRD_CustomerCode[]			= "Cust. Code\0    ";		/* JPNは最大10byte *//* wording by honda 1997/11/13 */
CUB PWRD_DistributorName[]		= "Dist. Name\0       ";	/* JPNは最大10byte *//* wording by honda 1997/11/13 */
CUB PWRD_CustomerName[]			= "Cust. Name\0       ";	/* JPNは最大10byte *//* wording by honda 1997/11/13 */
CUB PWRD_Section[]				= "Section\0         ";		/* JPNは最大10byte */
CUB PWRD_ChargeName[]			= "Signature ";
CUB PWRD_ModelName[]			= "Model ";
CUB PWRD_OrderItem[]			= "Order Item";
CUB PWRD_TonerOrder1[]			= "Toner x 1\0       ";		/* 注）ﾄﾅｰ =5byte, x 1の位置固定（日本語参照） *//* wording by honda 1997/11/13 */
CUB PWRD_DrumOrder1[]			= "Drum  x 1\0       ";		/* 注）ﾄﾞﾗﾑ=5byte, x 1の位置固定（日本語参照） *//* wording by honda 1997/11/13 */
CUB PWRD_SeirialNumber[]		= "Serial No.\0         ";	/* JPNは最大10byte *//* wording by honda 1997/11/13 */
CUB PWRD_InstallDate[]			= "Instal.Date\0     ";		/* JPNは最大10byte *//* wording by honda 1997/11/13 */
CUB PWRD_BlockLetters[]			= "               ";		/* JPNは未使用 */
CUB PWRD_Remarks[]				= "Remarks";
CUB PWRD_OrderTonerChange[]		= "Replace toner with a new one.   ";
CUB PWRD_OrderTonerDrumChange[]	= "Replace toner/drum with a new one.      ";
CUB PWRD_OrderSheet[]			= "Please fill out and send this sheet by fax.                 ";
#elif defined(US1)			/* orderbythonda1998/11/11 */
CUB PWRD_ConsumerOrderSheet[]	= "PITNEY BOWES OFFICE SYSTEMS 4100";
CUB PWRD_ConsumerOrderSheet2[]	= "SUPPLIES ORDER FORM";
CUB PWRD_ToOrder[]				= "To:\0   ";				/* 海外は最大6文字 */
CUB PWRD_FromOrder[]			= "From:\0 ";				/* 海外は最大6文字 */
CUB PWRD_CustomerCode[]			= "Customer's Code";
CUB PWRD_DistributorName[]		= "Distributor's Name";
CUB PWRD_CustomerName[]			= "Customer's Name\0  ";
CUB PWRD_Section[]				= "Address(Ship to:)";
CUB PWRD_ChargeName[]			= "Signature ";
CUB PWRD_ModelName[]			= "Model ";
CUB PWRD_OrderItem[]			= "Item Needed: ";
CUB PWRD_TonerOrder1[]			= "Toner Cartridge x       PCS";		/* 注）Toner=5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PWRD_DrumOrder1[]			= "Drum Unit       x       PCS";		/* 注）Drum =5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PWRD_SeirialNumber[]		= "Serial No.";
CUB PWRD_InstallDate[]			= "Installation Date";
CUB PWRD_BlockLetters[]			= "Print Name :";
CUB PWRD_Remarks[]				= "Customer Account No. & Ship to Address";
CUB PWRD_OrderTonerChange[]		= "Replace toner with a new one.   ";	/* JPNのみ */
CUB PWRD_OrderTonerDrumChange[]	= "Your machine's display indicates that either the Toner Cartridge or Drum Unit";
CUB PWRD_OrderTonerDrumChange2[]= "requires replacement.";
CUB PWRD_OrderSheet[]			= "To order replacements by phone, call               , or fill out this form";
CUB PWRD_OrderSheet2[]			= "and fax it to               .";
#else
CUB PWRD_ConsumerOrderSheet[]	= "< Consumables Order Sheet >";
CUB PWRD_ToOrder[]				= "To\0    ";				/* 海外は最大6文字 */
CUB PWRD_FromOrder[]			= "From\0  ";				/* 海外は最大6文字 */
CUB PWRD_CustomerCode[]			= "Customer's Code";
CUB PWRD_DistributorName[]		= "Distributor's Name";
CUB PWRD_CustomerName[]			= "Customer's Name\0  ";
CUB PWRD_Section[]				= "Address(Ship to:)";
CUB PWRD_ChargeName[]			= "Signature ";
CUB PWRD_ModelName[]			= "Model ";
CUB PWRD_OrderItem[]			= "Order Item";
CUB PWRD_TonerOrder1[]			= "Toner x       PCS";		/* 注）Toner=5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PWRD_DrumOrder1[]			= "Drum  x       PCS";		/* 注）Drum =5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PWRD_SeirialNumber[]		= "Serial No.(18digits)";
CUB PWRD_InstallDate[]			= "Installation Date";
CUB PWRD_BlockLetters[]			= "Block Letters :";
CUB PWRD_Remarks[]				= "Remarks";
CUB PWRD_OrderTonerChange[]		= "Replace toner with a new one.   ";	/* JPNのみ */
CUB PWRD_OrderTonerDrumChange[]	= "Replace toner/drum with a new one.      ";
CUB PWRD_OrderSheet[]			= "Please fill out and send this sheet by fax.                 ";
#endif

/* 簡易料金管理リスト */
#if (PRO_DEPART_NEW_LIST == ENABLE)
CUB PWRD_DepartTimeList[]	= "  ** Department Time List **  ";  /* added by thonda 1997/12/02 */
#endif

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
CUB PWRD_KeyMacroList[] 		= "** ｷｰﾏｸﾛ ﾀｲﾄﾙ ﾘｽﾄ **";
CUB PWRD_NoTitle[] 				= "ﾀｲﾄﾙ未登録";
CUB PWRD_Title[] 				= "ﾀｲﾄﾙ";
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
CUB PWRD_NumberDisplayList[]	= "  ** Number Display List **  ";
CUB PWRD_NumberDisplay[]		= "NumberDisplay";
CUB PWRD_NoConnect[]			= "No TEL";
CUB PWRD_Tel1Connect[]			= "PHONE1   ";
 #if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/24 */
CUB PWRD_Tel2Connect[]			= "TEL\0     ";
 #else
CUB PWRD_Tel2Connect[]			= "PHONE2   ";
 #endif		/* End of (defined (KEISATSU)) */
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
CUB PWRD_ND_Warp[]				= "ND Warp\0";
 #endif

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
CUB PWRD_NumberDisplayJournal[]	= "** Number Display Journal **";
CUB PWRD_SubscriberNumber[]		= "Name      ";
CUB PWRD_NoNotice[]				= "No Notice";
CUB PWRD_OutOfDisp[]			= "Out Disp";
CUB PWRD_PublicTel[]			= "Public Tel";
CUB PWRD_FNetCall[]				= "F Net";
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
CUB PWRD_WarpList[]		 		= "** FAX Warp List **";
CUB PWRD_AppointedTime[]		= "Time    ";
CUB PWRD_WarpFunction[]			= "FAX Warp";
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1999/01/25 */
CUB	PWRD_WarpWeek[][4]			= {
								  "Sun",
								  "Mon",
								  "Tue",
								  "Wed",
								  "Thu",
								  "Fri",
								  "Sat",
								  "(-)"
};
#endif

/* 月 */
CUB	PWRD_Year_Eng[12][4] = {
	"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
	};

/* プログラムリスト */
CUB	PWRD_ProgOnetouchDir[] 	= "** Prog.One-Touch Directory **";

/* 親展受信通知 */
#if ( PRO_MAKER == FX )
CUB	PWRD_SecureMailReci[] 	= "Mailbox Documents are received.         ";
#else
CUB	PWRD_SecureMailReci[] 	= "SecureMail Received.                    ";
#endif

/* 親展原稿消去通知 */
CUB	PWRD_ThisSecMailEra[] 	= "These SecureMail Documents were erased.\000";

/* 代行受信消去通知 */
#if ( PRO_MAKER == FX )
CUB	PWRD_ThisMemErased[] 	= "Received documents are erased.\000         ";	/* 6/28 FX.ENG */
#else
CUB	PWRD_ThisMemErased[] 	= "These Documents were erased.\000           ";
#endif

/* 通信予約消去通知 */
#if ( PRO_MAKER == FX )
CUB	PWRD_ThisComErased[] 	= "Pending jobs are erased.\000                 ";	/* 6/28 FX.ENG */
#else
 #if (PRO_DRAM_BACKUP == ENABLE)			/*94/11/28 ↓ By jmasuda*/
 CUB	PWRD_ThisComErased[] 	= "Commands were erased.  \000                  ";
 #else									/*94/11/28 ↑ By jmasuda*/
 CUB	PWRD_ThisComErased[] 	= "All commands were erased.  \000              ";
 #endif
#endif

/* チェックメッセージ */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/26 */
CUB	PWRD_MryOverFeeder[]	= "Due to memory full,Trans. was failed.\000";
CUB	PWRD_SecurityMemOver[]	= "Memory full. Please print received security documents.\000                    ";
#else
CUB	PWRD_MryOverFeeder[]	= "Due to memory full,Trans. was failed.";
CUB	PWRD_SecurityMemOver[]	= "Memory full. Please print received security documents.\000                    ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* セキュリティ受信をONにする。メモリーオーバーするまで受信を行う。チェックメッセージが印字されるが、内容が一部間違っている。 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec K.W.Q 2003/10/20 */
CUB	PWRD_SecurityOperation1[]	= "Usage: Press PROGRAM,One-Touch[11],2,ENTER\0 ";
#else
CUB	PWRD_SecurityOperation1[]	= "Usage: Press PROGRAM,One-Touch[O],2,ENTER\0";   /* 0->O bythonda1998/04/16 *//* by honda 1997/11/7 */
#endif

#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 1998/10/20 */
CUB	PWRD_SecurityOperation2[]	= "       and then enter Password (4-digits)\0  ";
#else
CUB	PWRD_SecurityOperation2[]	= "       and then enter Passcode (4-digits)\0  "; /* by honda 1997/11/7 */
#endif

/* ポーリング原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB	PWRD_PollErase[]		= "Polled documents are erased.\000                  ";	/* 6/28 FX.ENG */
#else
CUB	PWRD_PollErase[]		= "Polling documents were erased.\000                ";
#endif
CUB	PWRD_DbPollErase[]		= "DB Polling documents were erased.\000                  ";

/* 一括送信原稿リスト */
CUB	PWRD_IndexNo[]			= "  Receipt#\000  ";

/* 一括送信原稿消去通知 */
/* CUB	PWRD_BatchTxDocErase[]	= "Batch send documents are erased.        "; */
CUB	PWRD_BatchTxDocErase[]	= "Batch send documents were erased.       ";	/* 表現を統一します。 By S.Fukui Mar.26,1998 */

/* 連続ポーリングコマンド消去通知 */
CUB	PWRD_ContinuousPollingErase[] = "Continuous Polling Command was erased.            ";/* 1996/10/18 Eguchi */

/* 暗号化受信原稿消去通知 */
CUB	PWRD_ScrambleRxErase[]		= "These Scrambling Documents were erased.        ";

/* 通信結果メッセージ */
#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 李 2005/11/10 */
CUB	PWRD_ResultName[9][31] = {  "Check condition of remote fax.",	/* "～ remote Fax." -> "～ remote fax." 1998/09/19 By M.Kuwahara*/
								"Check received documents.\000    ",
#if ( PRO_MAKER == FX )
								"Tray again.\000                  ",
								"Dial again.\000                  ",
#else
								"Repeat transmission.\000         ",
								"Line is busy.\000                ",
#endif
								"Memory full.\000                 ",
#if ( PRO_MAKER == FX )
								"Dialing No. not registered.   ",/* "Dialling ～" -> "Dialing ～" 1998/09/19 By M.Kuwahara */
								"Stoped                        ",	/* By H.Y 1994/12/20 FX.ENG */
#else
								"Dialing number is not set.    ",/* "Dialling Number is not setted."->"Dialing number is not set." 1998/09/19 By M.Kuwahara */
								"Stopped.\000                     ",
#endif
								"\000                             ",
								"\000                             " };
#else /* !defined (KEISATSU) */
CUB	PWRD_ResultName[8][31] = {  "Check condition of remote fax.",	/* "～ remote Fax." -> "～ remote fax." 1998/09/19 By M.Kuwahara*/
								"Check received documents.\000    ",
#if ( PRO_MAKER == FX )
								"Tray again.\000                  ",
								"Dial again.\000                  ",
#else
								"Repeat transmission.\000         ",
								"Line is busy.\000                ",
#endif
								"Memory full.\000                 ",
#if ( PRO_MAKER == FX )
								"Dialing No. not registered.   ",/* "Dialling ～" -> "Dialing ～" 1998/09/19 By M.Kuwahara */
								"Stoped                        ",	/* By H.Y 1994/12/20 FX.ENG */
#else
								"Dialing number is not set.    ",/* "Dialling Number is not setted."->"Dialing number is not set." 1998/09/19 By M.Kuwahara */
								"Stopped.\000                     ",
#endif
								"\000                             " };
#endif /* defined (KEISATSU) */
#if (PRO_MAKER == FX)	/* By H.Y 1994/12/20 */
CUB	PWRD_ResultChain[LST_ERR_CODE_MAX] = {
							'D','F','A','C','A',		/*0*/
							'G','A','A','A','C',        /*5*/
							'C','B','A','A','A',        /*10*/
							'C','A','A','G','A',        /*15*/
							'A','A','A','B','A',        /*20*/
							'E','A','A','A','A',		/*25*/
							'A','A','A','H','C',		/*30*/
							'G','C','C',' ',' ' }; 		/*35*/
#else
 #if defined(POPLAR_F)
CUB	PWRD_ResultChain[LST_ERR_CODE_MAX] = {
							'D','F','A','C','A',		/*0*/
							'G','A','A','A','C',        /*5*/
							'C','B','A','A','A',        /*10*/
							'C','A','A','G','A',        /*15*/
							'A','A','A','B','A',        /*20*/
							'E','A','A','A','A',		/*25*/
							'A','A','A','H','C',		/*30*/
							'G','C','C',' ',' ' }; 		/*35*/
 #else
CUB	PWRD_ResultChain[LST_ERR_CODE_MAX] = {
							'D','F','A','C','A',		/*0*/
							'G','A','A','A','C',        /*5*/
							'C','B','A','A','A',        /*10*/
							'C','A','A','G','A',        /*15*/	/* R.1.4のワーディングをH->G By O.Kimoto 2002/10/24 */
							'A','A','A','B','A',        /*20*/
							'E','A','A','A','A',		/*25*/
							'A','A','A','H','C',		/*30*/
							'G','C','C',' ',' ' }; 		/*35*/
 #endif
#endif
/*PWRD_ResultChain[]の'A'がPWRD_ResultName[][]の一番目のﾒｯｾｰｼﾞに対応する*/
CUB	PWRD_ResultCode[LST_ERR_CODE_MAX][7] = {
						"D.0.2", "D.0.6", "T.1.1", "T.1.2", "T.1.3",	/*0*/
						"T.1.4", "T.2.1", "T.2.2", "T.2.3", "T.3.1",	/*5*/
						"T.4.1", "T.4.2", "T.4.3", "T.5.1", "T.5.2",	/*10*/
						"T.5.3", "R.1.1", "R.1.2", "R.1.4", "R.2.3",	/*15*/
						"R.3.1", "R.3.3", "R.3.4", "R.4.1", "R.4.2",	/*20*/
						"R.4.4", "R.5.1", "R.5.2", "D.0.7", "T.4.4",	/*25*/
						"R.2.1", "R.3.2", "R.3.5", "R.4.5", "D.0.1",	/*30*/
						"D.0.3", "D.0.8", "R.1.3", "", "" };			/*35*/
/*最後の項目は必ず""としておく必要あり*/
/*PWRD_ResultCode[]がPWRD_ResultChain[]に対応する*/

#if (PRO_ROTATE == ENABLE)				/* ＤＰＲＡＭ経由の回転受信 */
					/*	   12345678901234567890 */
CUB PWRD_RotateMargin[]	= "Rotate Margin   ";
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
CUB PWRD_INF_AddressList[]		= "** Mail Address Directory **";
CUB PWRD_INF_GroupList[]		= "** Mail Group Directory **";
CUB	PWRD_INF_MailComList[]		= "** Reserved Mail Commands **";
CUB	PWRD_INF_SettingList[]		= "** User Setting List **";
CUB	PWRD_INF_ErasedMailList[]	= "     ** Erased Mails **     ";
CUB PWRD_INF_ErasedCommand[]	= "** Erased Mail Commands **";
CUB PWRD_INF_Group[]			= "Mail Group";
CUB PWRD_INF_Address[]			= "Mail Address";
CUB PWRD_INF_UserName[]			= "User Name";
CUB PWRD_INF_ProviderName[]		= "ISP Name\000    ";
CUB PWRD_INF_AccessPoint1[]		= "Access Point 1";
CUB PWRD_INF_AccessPoint2[]		= "Access Point 2";
CUB PWRD_INF_AccessPoint3[]		= "Access Point 3";
#if (0)
CUB PWRD_INF_PPPLoginID[]		= "Dial-Up Login ID  ";
CUB PWRD_INF_PPPPassword[]		= "Dial-Up Login Password ";
CUB PWRD_INF_PPPAuth[]			= "Password Authentication";
CUB PWRD_INF_POPLoginID[]		= "Mail Login ID";
CUB PWRD_INF_POPPassword[]		= "Mail Login Password";
#endif
CUB PWRD_INF_PPPLoginID[]		= "PPP Login ID";
CUB PWRD_INF_PPPPassword[]		= "PPP Login Password";
CUB PWRD_INF_PPPAuth[]			= "PPP Authentication";
CUB PWRD_INF_POPLoginID[]		= "POP Login ID";
CUB PWRD_INF_POPPassword[]		= "POP Login Password";

CUB PWRD_INF_MailAddress[]		= "Mail Address";
CUB PWRD_INF_SMTPServer[]		= "SMTP Server";
CUB PWRD_INF_POPServer[]		= "POP Server";
CUB PWRD_INF_PriDNSServer[]		= "Primary DNS Server";
CUB PWRD_INF_SecDNSServer[]		= "Secondary DNS Server";
CUB PWRD_INF_ClientAddress[]	= "Client IP Address";
CUB PWRD_INF_ServerAddress[]	= "Server IP Address";
CUB PWRD_INF_GatewayAddress[]	= "Gateway IP Address";
CUB PWRD_INF_TxRx[]				= "Tx with Rx\000 ";
CUB PWRD_INF_AutoRcvMail[]		= "Auto Receive Mail";

CUB PWRD_INF_StartTime[]		= "Start Time";
CUB PWRD_INF_EndTime[]			= "End Time\000 ";
CUB PWRD_INF_IntervalTime[]		= "Interval Time";
CUB PWRD_INF_HoldTime[]			= "Hold Days";
CUB PWRD_INF_AutoPrint[]		= "Auto Print";

CUB PWRD_INF_ComsWereErased[]	= "Mail Commands were erased.\000                 ";
CUB	PWRD_INF_MailsWereErased[]	= "Received mails were erased.\000        ";
CUB	PWRD_INF_Receiver[]			= "Receiver: \000";
CUB	PWRD_INF_ErrorCode[]		= "Error Code";
CUB	PWRD_INF_ReTx[]				= "Repeat transmission\000  ";
CUB	PWRD_INF_ReRx[]				= "Repeat reception\000     ";
CUB	PWRD_INF_DialErr[]			= "Fail to connect with ISP\000 ";
CUB	PWRD_INF_ChkSetting[]		= "Check Your settings\000      ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	PWRD_INF_MemErr[]			= "Memory full\000            ";
#else
CUB	PWRD_INF_MemErr[]			= "Memory full\000          ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB	PWRD_INF_ChkBoard[]			= "Check option board\000        ";
CUB	PWRD_INF_PowerOff[]			= "Power Off\000          ";
CUB	PWRD_INF_Kind[] 			= "Kind\000";
CUB	PWRD_INF_To[]	 			= "To";
CUB	PWRD_INF_Tx[] 				= "Tx";
CUB	PWRD_INF_Rx[] 				= "Rx";
CUB	PWRD_INF_User[]				= "User:\000";
CUB	PWRD_INF_AccessPoint[]		= "Access Point:";

CUB	PWRD_INF_ConnectTime[]		= "Connect Time (min)";
CUB	PWRD_INF_ConnectCount[]		= "Connect Count";

CUB	PWRD_MailReceptionReport[]	= "** Mail Reception Report **\000     ";
CUB	PWRD_MailSender[]			= "Sender\000";
CUB	PWRD_MailReceivedTime[]		= "ReceivedTime\000";
CUB	PWRD_MailAutoPrintTime[]	= "PrintTime\000   ";
CUB	PWRD_MailRxReportState1[]	= "Following mails have been received.                                    ";/*71*/
CUB	PWRD_MailRxReportState2[]	= "Please press PROGRAM,R,2,ENTER, and then enter your Code Number        ";
CUB	PWRD_MailRxReportState3[]	= "to print these mails.                                                  ";
CUB	PWRD_MailRxReportState4[]	= "These mails will be printed automatically when \"PrintTime\" will be passed. ";

/*追加 1998/5/25 Eguchi*/
CUB	PWRD_INF_JournalComStartTime[] = "StartTime  ";

CUB	PWRD_INF_Ok[]				= "OK\000";
CUB	PWRD_INF_Error[]			= "ERROR\000";
CUB	PWRD_INF_AutoDownLoad[]		= "Auto Download \000";
CUB	PWRD_INF_DeleteMail[]		= "Delete Mail\000";
CUB	PWRD_INF_AutoCheck[]		= "Auto Check Mail\000";

CUB	PWRD_INF_MailJournal[]		= "   ** Mail Journal **   ";

#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */

/* 通信結果プリント */
#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
CUB PWRD_TransmitResult[]		= "** Transmit Result **\0   ";/*25(40)*/
CUB PWRD_ReceiveResult[]		= "** Receive Result **\0    ";/*25(40)*/
#endif

#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
/*@^s**************************************************************************
**@^1
**@^2	ﾌﾟﾘﾝﾄ用固定文字列 ENGLISH (USA) 横倍角文字タイトル
**@^3	桐／紅葉のﾀｲﾄﾙは、最初から横倍角(全角)とし、別ﾌｧｲﾙとする
**@^4	94/ 5/27 豊田
**@^e*************************************************************************/

/* 送信証　受領証 */
CUB	PWRD_TransConfReport_K[] 		= "＊＊　Ｔｒａｎｓｍｉｔ　Ｃｏｎｆ．Ｒｅｐｏｒｔ　＊＊";
CUB	PWRD_RecConfReport_K[] 			= "＊＊　Ｒｅｃｅｉｖｅ　Ｃｏｎｆ．Ｒｅｐｏｒｔ　＊＊";

/* 通信管理レポート｢送信｣ ｢受信｣ */
CUB PWRD_TransmitJournal_K[]		= "＊＊　Ｔｒａｎｓｍｉｔ　Ｊｏｕｒｎａｌ　＊＊";
CUB PWRD_RecieveJournal_K[]			= " ＊＊　Ｒｅｃｅｉｖｅ　Ｊｏｕｒｎａｌ　＊＊ ";

/* 短縮ダイヤルリスト */
#if ( PRO_MAKER == FX )
CUB	PWRD_TeleDirectory_K[]			= " 　　＊＊　Ｓｐｅｅｄ－Ｄｉａｌ　Ｌｉｓｔ　＊＊　　 ";
#else
CUB	PWRD_TeleDirectory_K[]			= "＊＊　Ｓｐｅｅｄ－Ｄｉａｌ　Ｄｉｒｅｃｔｏｒｙ　＊＊";
#endif

/* ワンタッチダイヤルリスト */
#if ( PRO_MAKER == FX )
CUB	PWRD_OneDirectory_K[]			= " ＊＊　ＯｎｅーＴｏｕｃｈ　Ｄｉａｌ　Ｌｉｓｔ　＊＊ ";
#else
CUB	PWRD_OneDirectory_K[]			= " ＊＊　Ｏｎｅ－Ｔｏｕｃｈ　Ｄｉｒｅｃｔｏｒｙ　＊＊ ";
#endif

/* 属性リスト */
CUB PWRD_AttributeList_K[]			= "＊＊　Ａｔｔｒｉｂｕｔｅ　Ｌｉｓｔ　＊＊";

/* グループリスト */
#if ( PRO_MAKER == FX )
CUB PWRD_GroupDirectory_K[]			= "＊＊　Ｇｒｏｕｐ　Ｄｉａｌ　Ｌｉｓｔ　＊＊";
#else
CUB PWRD_GroupDirectory_K[]			= "＊＊　Ｇｒｏｕｐ　Ｄｉｒｅｃｔｏｒｙ　＊＊";
#endif

/* マルチプログラムリスト */
#if ( PRO_MAKER == FX )
CUB	PWRD_MultiProgram_K[]			= "　　＊＊　Ｍｕｌｔｉ　Ｐｒｏｇｒａｍ　Ｌｉｓｔ　＊＊　　";	/* 6/28 FX.ENG */
#else
CUB	PWRD_MultiProgram_K[]			= "＊＊　ＭｕｌｔｉＰｒｏｇｒａｍ　Ｄｉｒｅｃｔｏｒｙ　＊＊";	/* 6/28 FX.ENG */
#endif

/* 機器設定リスト */
#if ( PRO_MAKER == FX )
CUB PWRD_MachineSettings_K[]		= "　＊＊　Ｃｕｓｔｕｍ　Ｐｒｅｓｅｔｓ　＊＊　";	/* 6/28 FX.ENG */
#else
CUB PWRD_MachineSettings_K[]		= " 　＊＊　Ｕｓｅｒ　Ｓｅｔｔｉｎｇｓ　＊＊　 ";
#endif

/* 機能リスト */
#if ( PRO_MAKER == FX )
CUB PWRD_ProgramList_K[]			= "Ｆｕｎｃｔｉｏｎ　Ｔｒｅｅ　　　";
#else
CUB PWRD_ProgramList_K[]			= "Ｐｒｏｇｒａｍ　Ｌｉｓｔ　　　　";
#endif

/* 通信予約リスト */
#if ( PRO_MAKER == FX )
CUB PWRD_ComReservedList_K[]		= "＊＊Ｐｅｎｄｉｎｇ　Ｊｏｂｓ　Ｌｉｓｔ＊＊";	 /* 6/28 FX.ENG */
#else
CUB PWRD_ComReservedList_K[]		= " 　＊＊　Ｃｏｍｍａｎｄ　Ｌｉｓｔ　＊＊　 ";
#endif

/* 親展者リスト */
#if ( PRO_MAKER == FX )
CUB PWRD_SecureMailBList_K[]		= " 　　＊＊　Ｍａｉｌｂｏｘ　Ｌｉｓｔ　＊＊　　 ";
#else
CUB PWRD_SecureMailBList_K[]		= "　＊＊　ＳｅｃｕｒｅＭａｉｌ　Ｌｉｓｔ　＊＊　";
#endif

/* カバーページプリント */
#if ( PRO_MAKER == FX )
CUB PWRD_CoverPageMes_K[]			= " 　＊＊　Ｆａｘ　Ｍｅｓｓａｇｅ　＊＊　 ";
#else
CUB PWRD_CoverPageMes_K[]			= "Ｆａｘ　Ｍｅｓｓａｇｅ　Ｆｒｏｍ：　　　";
#endif

/* 親展受信通知 */
#if ( PRO_MAKER == FX )
CUB PWRD_SecureMailNotice_K[]		= "ＭａｉｌｂｏｘＲｅｐｏｒｔ";
#else
CUB PWRD_SecureMailNotice_K[]		= " 　ＳｅｃｕｒｅＭａｉｌ　 ";
#endif

/* 親展原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB PWRD_ErasedDocuments_K[]		= "Ｒｃｖ　Ｍａｉｌｂｏｘ　Ｅｒａｓｅｄ";
#else
CUB PWRD_ErasedDocuments_K[]		= "　Ｅｒａｓｅｄ　Ｄｏｃｕｍｅｎｔｓ　";
#endif

/* 代行受信消去通知 */
#if ( PRO_MAKER == FX )
CUB PWRD_ErasedDocumemts_K[]		= " Ｒｃｖ　Ｄｏｃｕｍｅｎｔ　Ｅｒａｓｅｄ ";	/* 6/28 FX.ENG */
#else
CUB PWRD_ErasedDocumemts_K[]		= "　　Ｅｒａｓｅｄ　Ｄｏｃｕｍｅｎｔｓ　　";
#endif

/* 通信予約消去通知 */
#if ( PRO_MAKER == FX )
CUB PWRD_ErasedCommands_K[]			= "Ｐｅｎｄｉｎｇ Ｊｏｂ Ｅｒａｓｅｄ";	/* 10/18 FX.ENG */
#else
CUB PWRD_ErasedCommands_K[]			= " 　Ｅｒａｓｅｄ　Ｃｏｍｍａｎｄ　 ";
#endif

/* チェックメッセージ　メモリオーバー */
#if ( PRO_MAKER == FX )
CUB PWRD_CheckMessage_K[]			= "Ｓｅｎｄ　Ｆａｉｌ　Ｒｅｐ";
#else
CUB PWRD_CheckMessage_K[]			= "Ｃｈｅｃｋ　Ｍｅｓｓａｇｅ";
#endif
CUB PWRD_MemoryOver_K[]				= "Ｍｅｍｏｒｙ　Ｏｖｅｒ";
CUB PWRD_PcMemoryOver_K[]			= "ＰＣ　Ｍｅｍｏｒｙ　Ｏｖｅｒ";

/* Ｔ３０モニタ */
CUB PWRD_T30Monitor_K[]				= " ＊＊　Ｔ３０　Ｍｏｎｉｔｏｒ　＊＊ ";

/* ﾎﾟｰﾘﾝｸﾞ原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB PWRD_ErasePollDoc_K[]			= " 　　Ｐｏｌｌｅｄ　Ｄｏｃ．Ｅｒａｓｅｄ　　 ";
#else
CUB PWRD_ErasePollDoc_K[]			= " Ｅｒａｓｅｄ　Ｐｏｌｌ　Ｄｏｃｕｍｅｎｔｓ ";
#endif

/* 一括送信原稿リスト */
CUB	PWRD_BatchTxDocList_K[]			= "＊＊　ＢａｔｃｈＳｅｎｄＢｏｘＤｏｃ．　＊＊";	/* 6/28 FX.ENG */

/* 一括送信原稿消去通知 */
CUB	PWRD_EraseBatchTxDoc_K[]		= " ＢａｔｃｈＳｅｎｄＤｏｃ．Ｅｒａｓｅｄ ";	/* 6/28 FX.ENG */

/* 一括送信ＢＯＸリスト */
CUB	PWRD_BatchTxBoxList_K[]			= "＊＊　ＢａｔｃｈＳｅｎｄＢｏｘ　Ｌｉｓｔ　＊＊";	/* 6/28 FX.ENG */

/* 部門管理リスト*/
#if ( PRO_MAKER == FX )
CUB	PWRD_DepartCodeList_K[]			= "　　　　　　＊＊　Ａｃｃｏｕｎｔ　Ｌｉｓｔ　＊＊　　　　　　";	/* 6/28 FX.ENG */
#else
CUB	PWRD_DepartCodeList_K[]			= " 　　　　＊＊　Ｄｅｐａｒｔｍｅｎｔ　Ｌｉｓｔ　＊＊　　　　 ";
#endif

/* 料金表 */
CUB	PWRD_CostBase_K[]				= "＊＊　Ｃｈａｒｇｅ　＊＊";	/* POPLAR_Hのみ */

/* プログラムリスト */
#if ( PRO_MAKER == FX )
CUB	PWRD_ProgOnetouchDir_K[]		= "　　　　＊＊　Ｐ　Ｏｎｅ　Ｔｏｕｃｈ　Ｌｉｓｔ　＊＊　　　　";
#else
CUB	PWRD_ProgOnetouchDir_K[]		= "＊＊　Ｐｒｏｇ．Ｏｎｅ－Ｔｏｕｃｈ　Ｄｉｒｅｃｔｏｒｙ　＊＊";
#endif

/* モニターレポート */
CUB	PWRD_MonitorReport_K[]			= "Ｍｏｎｉｔｏｒ　Ｒｅｐｏｒｔ";

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
CUB PWRD_F_CodeBox_List_K[]			= "＊＊　ＦＣＯＤＥ　Ｂｏｘ　Ｌｉｓｔ　＊＊";

/* サブアドレス原稿消去通知 */
CUB PWRD_Del_F_CodeBoxDoc_Notice_K[]	= "ＦＣＯＤ　Ｌｉｓｔ　Ｏｆ　Ｅｒａｓｅｄ　Ｂｏｘｅｓ";

/* サブアドレスBOX蓄積原稿リスト */
CUB PWRD_F_CodeDoc_List_K[]			= "＊＊  ＦＣＯＤＥ　Ｌｉｓｔ　Ｏｆ　Ｄｏｃｕｍｅｎｔｓ　＊＊";

/* サブアドレス受信通知 */
CUB PWRD_F_CodeBoxRsv_Notice_K[]	= "ＦＣＯＤＥ　Ｂｏｘ　Ｊｏｕｒｎａｌ";
#endif

/* ダイレクトメール防止ダイヤルリスト */
CUB	PWRD_BlockJunkList_K[]			= "＊＊　Ｂｌｏｃｋ　Ｊｕｎｋ　Ｆａｘ　Ｌｉｓｔ　＊＊　";

/* サービスレポート */
CUB	PWRD_ServiceReport_K[]			= "＊＊　Ｓｅｒｖｉｃｅ　Ｒｅｐｏｒｔ　＊＊";

/* 暗号化受信通知リスト */
/*CUB PWRD_CipherReceiveNotice_K[]	= "スクランブル受信通知";	 98/01/12 By M.Kuwahara */
CUB PWRD_CipherReceiveNotice_K[]	= "  Ｓｃｒａｍｂｌｅ　Ｒｘ　Ｒｅｐｏｒｔ  ";

/* キーブックリスト */
/*CUB PWRD_KeyBookList_K[]			= "＊＊　キーバンク　＊＊";	 98/01/12 By M.Kuwahara */
CUB PWRD_KeyBookList_K[]			= "＊＊　ＫｅｙＢｏｏｋＬｉｓｔ　＊＊";

/* キーリスト */
/*CUB PWRD_KeyWordList_K[]			= "＊＊　キーワードリスト　＊＊";*/
CUB PWRD_KeyWordList_K[]			= "＊＊  Ｋｅｙ Ｌｉｓｔ   ＊＊";

/* 暗号化受信消去通知 */
/*CUB	PWRD_EraseScrambleRxDoc_K[]		= "スクランブル原稿消去通知";*/
CUB	PWRD_EraseScrambleRxDoc_K[]		= "Ｅｒａｓｅｄ　Ｓｃｒａｍｂｌｉｎｇ　Ｄｏｃ．";

/* 消耗品発注票 */
 #if defined(JPN)
CUB PWRD_ConsumerOrderSheet_K[]		= "Ｏｒｄｅｒ　Ｓｈｅｅｔ";   /* modified by honda 1997/11/12 */
 #else
CUB PWRD_ConsumerOrderSheet_K[]		= "消耗品発注票　　　　　";
 #endif

 #if (PRO_COST == ENABLE)				/* 料金管理 *//* Add By O.Kimoto 1997/11/17 */
/* 料金表 */
CUB	PWRD_DialingCode[]		= "CityCode";
CUB	PWRD_Daytime[]			= "  Day(Sec/\\10)  ";	/* 6/28 FX.ENG */
CUB	PWRD_Night[]			= " Night(Sec/\\10) ";	/* 6/28 FX.ENG */
CUB	PWRD_Midnight[]			= "M.Night(Sec/\\10)";	/* 9/17 FX.ENG */
CUB	PWRD_Slash10[]			= "   ";
CUB	PWRD_WithinArea[]		= "AreaCall";
 #endif

 #if (PRO_LINENUMBER == TWICE_LINE)
/* 内蔵回線のラベルです。 By O.Kimoto 1997/12/20 */
#if (0)
** CUB PWRD_InternalLineName[][8]            = {
** 									/* 	"123456789" */
** 										"(Std.):",
** 										"(Ext.):"
** 										};
#endif
CUB PWRD_LineName[][8]			= {
									/* 	"123456789" */
										"Std.",
										"Ext.",
										"Opt."
										};
 #endif


#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
CUB	PWRD_INF_MailComList_K[]	= "＊＊　Ｒｅｓｅｒｖｅｄ　Ｍａｉｌ　Ｃｏｍｍａｎｄｓ　＊＊";
CUB	PWRD_INF_SettingList_K[]	= "＊＊　Ｕｓｅｒ　Ｓｅｔｔｉｎｇ　Ｌｉｓｔ　＊＊";
CUB	PWRD_INF_ErasedMailList_K[]	= "＊＊　Ｅｒａｓｅｄ　Ｍａｉｌｓ　＊＊";
CUB PWRD_INF_ErasedCommand_K[]	= "＊＊　Ｅｒａｓｅｄ　Ｍａｉｌ　Ｃｏｍｍａｎｄｓ　＊＊";
#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
CUB PWRD_KeyMacroList_K[]	= "＊＊　キーマクロ　タイトル　リスト　＊＊";
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
CUB PWRD_NumberDisplayList_K[] = "＊＊　Ｎｕｍｂｅｒ　Ｄｉｓｐｌａｙ　Ｌｉｓｔ　＊＊";

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
CUB PWRD_NumberDisplayJournal_K[]	= "＊＊　Ｎｕｍｂｅｒ　Ｄｉｓｐｌａｙ　Ｊｏｕｒｎａｌ　＊＊";
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
CUB PWRD_WarpList_K[] 		= "＊＊　ＦＡＸ　Ｗａｒｐ　Ｌｉｓｔ　＊＊";
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
CUB PWRD_EmergencyTitle_Emergency_K[] 		= " 　＊＊　緊急　＊＊ ";
CUB PWRD_EmergencyTitle_Normal_K[]	 		= " 　＊＊　普通　＊＊ ";
 #endif
#endif

#if (0)
** /* 宣言する位置が間違えています By O.Kimoto 2002/07/18 */
** #if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/17 K.Kawata */
** /* 再送時チェックメッセージ 2000/2/17 K.Kawata */
** CUB	PWRD_SendDocument[] = "Send the document(s) from page\0         ";
** #endif
#endif

#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
CUB PWRD_TransmitResult_K[]		= "＊＊　Ｔｒａｎｓｍｉｔ　Ｒｅｓｕｌｔ　＊＊\0   ";/*25(40)*/
CUB PWRD_ReceiveResult_K[]		= "＊＊　Ｒｅｃｅｉｖｅ　Ｒｅｓｕｌｔ　＊＊\0    ";/*25(40)*/
#endif

#endif

#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/17 K.Kawata */
/* 再送時チェックメッセージ 2000/2/17 K.Kawata */
CUB	PWRD_SendDocument[] = "Send the document(s) from page\0         ";
#endif

#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/10 */
CUB PWRD_DialTone[]			= "ﾀﾞｲﾔﾙﾄｰﾝ検出(加入)\0 ";/*17*/
CUB	PWRD_DialToneKeiden[]	= "ﾀﾞｲﾔﾙﾄｰﾝ検出(警電)\0 ";
#else
 #if defined(STOCKHM2) || defined(HINOKI3)	/*ダイヤルトーン検出対応 by SMuratec 夏 2004/7/14 */ /* Add by Y.Kano 2004/12/07 */
CUB	PWRD_DialTone[]			= "Dial Tone\0       ";
 #endif
#endif		/* End of (defined (KEISATSU)) */

#if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/07/21 */
CUB	PWRD_SettingLine[]		= "Fax Line\000  ";
CUB	PWRD_SettingFaxMode[]	= "Fax Mode\000  ";
CUB	PWRD_ScrambleKeiden[]	= "EXT Line Scramble";
CUB	PWRD_ScrambleKanyu[]	= "STD Line Scramble";
CUB	PWRD_RemoteNumIssei[]	= "Spec Remote Num\0  ";
CUB	PWRD_RemoteNumKobetu[]	= "Norm Remote Num\0  ";
CUB	PWRD_KeidenLine[]		= "EXT Line";
CUB	PWRD_KanyuLine[]		= "STD Line";
CUB	PWRD_IsseiFaxcom[]		= "Spec Fax";
CUB	PWRD_KobetuFaxcom[]		= "Norm Fax";
CUB	PWRD_SettingSave[]		= "Auto Save";
CUB	PWRD_EXTRinggingTimes[]	= "# EXT LINE Rings ";
CUB	PWRD_RinggingTimes[]	= "# STD LINE Rings ";
#endif
/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの最後に入れる) */
CUB	PWRD_TAIL[]			= "";

#if (PRO_CPU == SH7043) /* T.Nose 1996/07/04 */
	#pragma section
#endif

#undef	CUB
