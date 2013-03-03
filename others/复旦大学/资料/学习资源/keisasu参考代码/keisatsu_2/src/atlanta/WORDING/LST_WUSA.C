/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_WUSA.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 帳票用固定文字列 ENGLISH (USA)
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\lst_def.h"

#define	CUB		CONST UBYTE

#if (PRO_CPU == SH7043) /* ワーディング先頭位置認識用 1996/07/04 T.Nose */
	#if (WORDING_1 == ENGLISH)
		CUB PWRD_1stWordingTop[] = "\0";
	#endif
	#if (WORDING_2 == ENGLISH)
		CUB PWRD_2ndWordingTop[] = "\0";
	#endif
	#if (WORDING_3 == ENGLISH)
		CUB PWRD_3rdWordingTop[] = "\0";
	#endif
#endif

/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの先頭に入れる) */
CUB	PUSA_HEAD[]				= "";

/* 送信証　受領証 */
CUB	PUSA_TransConfReport[]	= "** Transmit Conf.Report **";
CUB	PUSA_RecConfReport[] 	= "** Receive Conf.Report **";
CUB	PUSA_FromTo[] 			= "--->";
CUB	PUSA_CommNo[] 			= "No.\000       ";
CUB	PUSA_CommMode[] 		= "Mode\000    ";
CUB	PUSA_CommStartTime[] 	= "Time\000    ";
CUB	PUSA_CommPages[] 		= "Pages\000   ";
CUB	PUSA_CommResult[] 		= "Result\000  ";
#if ( PRO_MAKER == FX )
CUB	PUSA_Normal[] 			= "Standard";
CUB	PUSA_Fine[] 			= "Fine\000 ";
CUB	PUSA_SFine[] 			= "SuperFine";
CUB	PUSA_Gray[] 			= "Halftone";
#else
CUB	PUSA_Normal[] 			= "NORMAL\000 ";
CUB	PUSA_Fine[] 			= "FINE\000 ";
 #if (PRO_OKI == ENABLE) /* OKI仕様 By T.Fukumoto 98/07/03 */
CUB	PUSA_SFine[] 			= "Ex-FINE\000 ";
 #else
CUB	PUSA_SFine[] 			= "S-FINE\000  ";
 #endif
 #if (PRO_PITNEYBOWES == ENABLE)
CUB	PUSA_Gray[] 			= "PHOTO\000  ";
CUB	PUSA_HFine[] 			= "H-FINE\000  ";	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
CUB	PUSA_HGray[] 			= "H PHOTO\000";	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
 #else
CUB	PUSA_Gray[] 			= "GRAY\000   ";
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)/* SANYO仕様の追加 2000/02/24 N.Kondo *//* Add by Y.Kano 2003/07/11 */
CUB	PUSA_Fine_S[] 			= "FINE\000 ";
CUB	PUSA_SFine_S[] 			= "S-FINE\000  ";
#endif
CUB	PUSA_Pages[] 			= "Page(s)";
CUB	PUSA_FaxD[] 			= "Fax:";

/* 通信管理レポート */
CUB	PUSA_TransmitJournal[]	= "[Transmit]      ";
CUB	PUSA_RecieveJournal[]	= "[Receive]       ";
CUB	PUSA_ContNo[]			= " No. ";
CUB	PUSA_RemoteFrom[]		= " From:  ";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題（終端をNULLで判断していない）があるので、ﾜｰﾃﾞｨﾝｸﾞを最大5ﾊﾞｲﾄ・ｺﾛﾝの位置固定(英語参照)にすること */
CUB	PUSA_RemoteTo[]			= "  To:   ";
CUB	PUSA_Mode[] 			= "  Mode\000  ";
#if ( PRO_MAKER == FX )
CUB	PUSA_Start[] 			= "Transmit";	/* 6/26 FX.ENG */
#else
CUB	PUSA_Start[] 			= " Start\000 ";
#endif
CUB	PUSA_Received[] 		= "Received";
CUB	PUSA_Time[] 			= " Time ";
CUB	PUSA_Page[] 			= "Page";
CUB	PUSA_Code[] 			= "Code";
CUB	PUSA_Result[] 			= "Result\000";
CUB	PUSA_Note[] 			= " Note\000";
CUB	PUSA_AltNo[] 			= "(Alt.No)";
CUB	PUSA_Secure[] 			= "Secure\000";
CUB	PUSA_Relay[] 			= "Relay\000 ";
CUB	PUSA_Polling[] 			= "Polling";
CUB	PUSA_DbPolling[] 		= "DB-Poll";
CUB	PUSA_Manual[] 			= "Manual\000";
CUB	PUSA_RelayedTxReport[]	= "RlyRpt.";
#if defined(USA) || defined(US2) || defined(AUS)	/*95/05/20 By j.masuda */
CUB	PUSA_FIP_Tx[] 			= "MFS_Tx\000";
CUB	PUSA_FIP_Rx[] 			= "MFS_Rx\000";
CUB	PUSA_FIP_Poll[] 		= "MFS_Pol";
CUB	PUSA_FIP_Sec[] 			= "MFS_Sec";
#else								/*95/05/20 By j.masuda */
CUB	PUSA_FIP_Tx[] 			= "FIP_Tx\000";
CUB	PUSA_FIP_Rx[] 			= "FIP_Rx\000";
CUB	PUSA_FIP_Poll[] 		= "FIP_Pol";
CUB	PUSA_FIP_Sec[] 			= "FIP_Sec";
#endif
CUB	PUSA_BrdCast[]	 		= "BRDCAST";
CUB	PUSA_Ok[] 				= "O K";
/* Fｺｰﾄﾞ */
CUB	PUSA_SUB_Tx[]			= "FcodeTx";
CUB PUSA_SEP_Rx[]			= "FC-Poll";
CUB PUSA_SUB_Rx[]			= "FcodeRx";
/* ｽｸﾗﾝﾌﾞﾙ */
CUB	PUSA_Cipher_Tx[]		= "SCRAMBL";                /* wording by honda 1997/11/10 */
CUB	PUSA_Cipher_Rx[]		= "SCRAMBL";                /* wording by honda 1997/11/10 */

/* 短縮ダイヤルリスト */
CUB	PUSA_TeleDirectory[] 	= "** Speed-Dial Directory **";
CUB	PUSA_No[]				= "No.";
#if ( PRO_MAKER == FX )
CUB	PUSA_RemoteLocation[]	= "     Name\000      ";	/* 6/28 FX.ENG */
CUB	PUSA_TeleNumber[] 		= "  Telephone No.   ";		/* 6/28 FX.ENG */
CUB	PUSA_GroupNumber[] 		= "Group No.       ";		/* 6/28 FX.ENG */
#else
CUB	PUSA_RemoteLocation[]	= "Remote Location\000";
CUB	PUSA_TeleNumber[] 		= " Telephone Number ";
CUB	PUSA_GroupNumber[] 		= "  Group Number  ";	/* ANZUのみ */
#endif
CUB	PUSA_Cost[]				= " Charge ";	/* POPLAR_Hのみ */

/* 属性リスト */
CUB PUSA_AttributeList[]	= "Attribute List";
CUB PUSA_Attribute[]		= "Attr.";

/* ワンタッチダイヤルリスト */
CUB	PUSA_OneDirectory[] 	= "** One-Touch Directory ** ";

/* プログラムリスト */
CUB	PUSA_DelyTime[] 		= " Start  ";
CUB	PUSA_Option[] 			= " Option\000";
CUB	PUSA_NotTime[] 			= "--:--";

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/26 By M.Kuwahara */
CUB	PUSA_PRG_Onetouch[]		= "One-Touch Directory   ";
CUB	PUSA_PRG_Speed[]		= "Speed-Dial Directory  ";
CUB	PUSA_PRG_Program[]		= "P One-Touch Directory ";
CUB	PUSA_PRG_SecureBox[]	= "SecureMail List       ";
CUB	PUSA_PRG_ComReserve[]	= "Command List          ";
 #if defined(SAKAKI) && defined(JP0) /* By M.Maeda 2002/10/21 */
CUB	PUSA_PRG_Journal[]		= "Journal(Tx/Rx)        ";
 #else
  #if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
CUB	PUSA_PRG_Journal[]		= "All Journals          ";
CUB	PUSA_PRG_DailyReport[]	= "Day Journal           ";
  #else
CUB	PUSA_PRG_Journal[]		= "Journal               ";
  #endif
 #endif
CUB	PUSA_PRG_Group[]		= "Group Directory       ";
CUB	PUSA_PRG_Setting[]		= "User Settings         ";
CUB	PUSA_PRG_Message[]		= "Fax Message From:     ";
CUB	PUSA_PRG_CostBase[]		= "Charge                ";
CUB	PUSA_PRG_DepartCode[]	= "Department List       ";
CUB	PUSA_PRG_BatchBox[]		= "BatchSendBox List     ";
CUB	PUSA_PRG_BatchDoc[]		= "BatchSendBoxDoc.      ";
CUB	PUSA_PRG_F_CodeBox[]	= "F-Code Box List       ";
CUB	PUSA_PRG_F_CodeDoc[]	= "F-Code List Of Doc.   ";
CUB	PUSA_PRG_BlockJunk[]	= "Block Junk Fax List   ";
CUB	PUSA_PRG_ND_Dial[]		= "Number Display List   ";
CUB	PUSA_PRG_ND_Journal[]	= "Number Display Journal";
CUB	PUSA_PRG_Warp[]			= "FaxWarp List          ";
 #if defined(SAKAKI) && defined(JP0) /* 2002/08/26 By M.Maeda */
CUB	PUSA_PRG_JournalTx[]	= "Journal(Tx)           ";
CUB	PUSA_PRG_JournalRx[]	= "Journal(Rx)           ";
 #endif
CUB PUSA_ListName[]			= "List Name";
CUB PUSA_CommReserved[]		= "Command ";
CUB PUSA_List[]				= "List";
CUB PUSA_DocStore[]			= "Store   ";
#endif

/* グループリスト */
CUB	PUSA_GroupDirectory[] 	= "** Group Directory **";
#if ( PRO_MAKER == FX )
CUB	PUSA_Location[]			= "  Name\000  ";
#else
CUB	PUSA_Location[]			= " Location";
#endif

/* 機器設定リスト */
CUB	PUSA_MachineSettings[] 	= "  ** User Settings ** ";
#if ( PRO_MAKER == FX )
CUB	PUSA_SubscriberID[] 	= "SendHeader";
#else
CUB	PUSA_SubscriberID[] 	= "Name:\000    ";
#endif
CUB	PUSA_SubscriberKanaID[]	= "Kana ID         ";
#if ( PRO_MAKER == FX )
CUB	PUSA_SubscriberNb[] 	= "Local ID    ";	/* 10/18 FX.ENG */
CUB	PUSA_JournalAutoPrt[] 	= "Auto Activity Rep";
CUB	PUSA_SecureDocHold[] 	= "Rcv MB Hold Time";
#else
CUB	PUSA_SubscriberNb[] 	= "Fax Number: ";
#if (PRO_OKI == ENABLE) /* OKI仕様 By T.Fukumoto 98/07/03 */
CUB	PUSA_JournalAutoPrt[] 	= "Report AutoPrint ";
#else
CUB	PUSA_JournalAutoPrt[] 	= "Journal AutoPrint";
#endif
 #if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	PUSA_SecureDocHold[] 	= "Secure Doc.Hold\000 ";
 #else
CUB	PUSA_SecureDocHold[] 	= "Secure Doc.Hold\000";
 #endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif
CUB	PUSA_PhoneType[]		= "Phone Type";
#if ( PRO_MAKER == FX )
CUB	PUSA_ConfReport[]		= "Monitor Rep";
CUB	PUSA_ScannerWidth[]		= "Scan Width   ";	/* 6/28 FX.ENG */
CUB	PUSA_PrimaryMode[]		= "Resolution\000   ";	/* 6/28 FX.ENG */
CUB	PUSA_Contrast[]			= "Density\000      ";	/*11/01 FX.ENG */
CUB	PUSA_DialingPause[]		= "PauseDuration";
#else
#if defined(STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	PUSA_ConfReport[]		= "Report Type ";
#else
CUB	PUSA_ConfReport[]		= "Report Type";
#endif
CUB	PUSA_ScannerWidth[]		= "Scanner Width";
CUB	PUSA_PrimaryMode[]		= "Primary Mode\000 ";
CUB	PUSA_Contrast[]			= "Contrast\000     ";
CUB	PUSA_DialingPause[]		= "Dialing Pause";
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)/* SANYO仕様の追加 2000/02/24 N.Kondo *//* Add by Y.Kano 2003/07/11 */
CUB	PUSA_Contrast_S[]		= "Contrast\000     ";
 #endif
#endif
CUB	PUSA_RinggingTimes[]	= "# of Rings\000   ";
#if ( PRO_MAKER == FX )
CUB	PUSA_ReductionRate[]	= "Reduction %   ";	/* 6/28 FX.ENG */
#else
CUB	PUSA_ReductionRate[]	= "Reduction Rate";
#endif
CUB	PUSA_EcmMode[]			= "ECM Mode";
CUB	PUSA_CopyProtect[]		= "Copy Protect";
CUB	PUSA_RemoteDiagnostic[]	= "Service Mode\000    ";
CUB	PUSA_RedialTimes[]		= "Redial Settings\000 ";
CUB	PUSA_Holdmelody[]		= "Hold Melody\000";
#if (PRO_OKI == ENABLE) /* OKI仕様 By T.Fukumoto 98/07/03 */
CUB	PUSA_Passcode[]			= "Password";
#else
CUB	PUSA_Passcode[]			= "Passcode";
#endif
CUB	PUSA_CloseNetwork[]		= "Closed Network\000";
CUB	PUSA_SilentOperation[]	= "Silent Mode\000    ";	/* JPN以外 */
#if ( PRO_MAKER == FX )
CUB	PUSA_SecurityTx[]		= "Secure Send      ";	/* 6/28 FX.ENG */
CUB	PUSA_BlockjunkFax[]		= "No Junk Fax\000    ";
#else
CUB	PUSA_SecurityTx[]		= "Security Transmit";
CUB	PUSA_BlockjunkFax[]		= "Block Junk Fax\000 ";
#endif
CUB	PUSA_RecieveMode[]		= "Receive Mode";
#if ( PRO_MAKER == FX )
CUB	PUSA_PageCompound[]		= "Combine Pages    ";	/* 9/17 FX.ENG */
#else
CUB	PUSA_PageCompound[]		= "Half-Page Recept.";
#endif
CUB	PUSA_SortingCopy[]		= "Sorting Copy";		/* POPLAR_Lのみ */
CUB	PUSA_Rs232c[]			= "RS232C Parameters";
CUB	PUSA_Stamp[]			= "Stamp\000 ";
CUB	PUSA_MemoryTx[]			= "Memory Transmit";
CUB	PUSA_RelayedRelayTx[]	= "Relayed Relay     ";

#if (PRO_PANEL == KANJI)
/* ＰＯＰＬＡＲ＿ＨはＬＣＤに待機モードを表示していないので、機器設定リストに表示させます。 By O.Kimoto 1998/03/02 */
CUB	PUSA_DialIn[]			= "DialinNo         ";
CUB	PUSA_DialIn_Item1[]		= "Fax/Tel1/Tel2   ";
CUB	PUSA_DialIn_Item2[]		= "Fax/Tel1        ";
#else
CUB	PUSA_DialIn[]			= "DialinNo  Fax/Tel";	/* (JPN) */
#endif

CUB	PUSA_BellTime[]			= "  Times";			/* (JPN) */
CUB	PUSA_RingMastr[]		= "DRD Option       ";
CUB	PUSA_CopyReduction[]	= "Copy Reduc.Rate  ";	/**	'.'の後のスペースをとる By H.Hirao 1996/06/03	*/
CUB	PUSA_PaperSize[]		= "Paper Size       ";	/* ANZUのみ */
CUB PUSA_PC_PaperManual[]	= "PC Prn Paper Size";	/* ANZUのみ *//* bythonda1998/03/24 PCﾌﾟﾘﾝﾄﾃｻﾞｼﾖｳｼ */
CUB	PUSA_PaperType[]		= "Paper Type     ";	/* SAKAKIのみ */
CUB	PUSA_ToneLine[] 		= "Tone\000";
#if ( PRO_MAKER == FX )
CUB	PUSA_Pps10[] 			= "10pps";	/* 6/28 FX.ENG */
CUB	PUSA_Pps20[] 			= "20pps";	/* 6/28 FX.ENG */
#else
CUB	PUSA_Pps10[] 			= "Pulse";
CUB	PUSA_Pps20[] 			= "Pulse";
#endif
#if defined(STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	PUSA_TxConf[]			= "TCR\000        ";
#else
CUB	PUSA_TxConf[]			= "TCR\000    ";
#endif
CUB	PUSA_RxConf[]			= "RCR\000     ";
CUB	PUSA_A4[] 				= "A4";
CUB	PUSA_B4[] 				= "B4";
CUB	PUSA_A3[] 				= "A3";
CUB	PUSA_F4[] 				= "F4";
#if (PRO_PITNEYBOWES == ENABLE)			
CUB PUSA_LETTER[]			= "LTR";	/* ＰＢ仕様の為追加 By S.Fukui Aug. 25,1998 */
CUB PUSA_LEDGER[]			= "LD";		/* ＰＢ仕様の為追加 By S.Fukui Aug. 25,1998 */
#endif
#if ( PRO_MAKER == FX )
CUB	PUSA_Dark[] 			= "Darker";
CUB	PUSA_NormalDark[] 		= "Normal";
CUB	PUSA_Light[] 			= "Lighter";
#else
CUB	PUSA_Dark[] 			= "DARK\000 ";
CUB	PUSA_NormalDark[] 		= "NORMAL";
CUB	PUSA_Light[] 			= "LIGHT\000 ";
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)/* SANYO仕様の追加 2000/02/24 N.Kondo *//* Add by Y.Kano 2003/07/11 */
CUB	PUSA_Dark_S[] 			= "DARK\000 ";
CUB	PUSA_Light_S[] 			= "LIGHT\000 ";
#endif
CUB	PUSA_MinuteMark[] 		= "Minutes";
CUB	PUSA_SecondMark[] 		= "Sec.";
#if ( PRO_MAKER == FX )
CUB	PUSA_Try[] 				= "Times";
#else
CUB	PUSA_Try[] 				= "     ";
#endif
CUB	PUSA_Attemps[] 			= "Attempts";
CUB	PUSA_On[] 				= "ON\000";
CUB	PUSA_Off[] 				= "OFF";
CUB	PUSA_Mode1[]			= "Mode1";
CUB	PUSA_Mode2[]			= "Mode2";
CUB	PUSA_Mode3[]			= "Mode3";
CUB	PUSA_P100[] 			= "100%";
CUB	PUSA_P97[] 				= "97%";
CUB	PUSA_P91[] 				= "91%";
CUB	PUSA_P81[] 				= "81%";
CUB	PUSA_P75[] 				= "75%";
#if ( PRO_MAKER == FX )
CUB	PUSA_ThValue00mm[] 		= "Thrshld   00 mm";	/* 6/28 FX.ENG */
CUB	PUSA_TelFax[] 			= "Tel/Fax\000 ";
CUB	PUSA_Tel[] 				= "Tel\000";
CUB	PUSA_Fax[] 				= "Fax\000";
CUB	PUSA_AnsFax[] 			= "Ans/Fax\000";	/* 6/28 FX.ENG */
#else
CUB	PUSA_ThValue00mm[] 		= "Margin    00 mm";
CUB	PUSA_TelFax[] 			= "TEL/FAX\000 ";
CUB	PUSA_Tel[] 				= "TEL\000";
CUB	PUSA_Fax[] 				= "FAX\000";
 #if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 1998/10/20 */
CUB	PUSA_AnsFax[] 			= "TAD/FAX\000";
 #else
CUB	PUSA_AnsFax[] 			= "ANS/FAX\000";
 #endif
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec K.W.Q 2003/11/28 */
CUB	PUSA_DialInRx[]			= "DialinNo\0";
#endif

CUB	PUSA_FaxTel[]			= "FAX/TEL\000 "; /**	追加 For ANZU By H.Hirao 1996/05/21	*/
CUB	PUSA_Bps300[] 			= "300";
CUB	PUSA_Bps600[] 			= "600";
CUB	PUSA_Bps1200[] 			= "1200";
CUB	PUSA_Bps2400[] 			= "2400";
CUB	PUSA_Bps4800[] 			= "4800";
CUB	PUSA_Bps9600[] 			= "9600";
CUB	PUSA_Bps19200[] 		= "19200";
CUB	PUSA_BpsVariable[] 		= "Variable";			/** 追加 For POPLA By M.Kuwahara 1997/03/05 */
CUB	PUSA_None[] 			= "NONE";
CUB	PUSA_Odd[] 				= "ODD";
CUB	PUSA_Even[] 			= "EVEN";
CUB	PUSA_S1bit[] 			= "1bit";
CUB	PUSA_S2bit[] 			= "2bit";
CUB	PUSA_P7bit[] 			= "7bit";
CUB	PUSA_P8bit[] 			= "8bit";
CUB	PUSA_Days[] 			= "Days";
CUB	PUSA_Auto[] 			= "Auto\000";
CUB	PUSA_Pattern[]			= "Pattern:";	/* (USA) */
CUB	PUSA_Letter[]			= "Letter\0";
CUB	PUSA_Legal[]			= "Legal\0";
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* '95.07/20 By K.Watanabe *//* by K.Watanabe 2004/10/12 */
CUB	PUSA_RxAlarm[]			= "Rx Alarm     "; /* Add By H.H 1996/08/28 */
CUB	PUSA_MercuryPause[]		= "Prefix Pause "; /* Add By H.H 1996/08/28 Mercury Pause -> Prefix Pause */
CUB PUSA_MercuryNumber[]	= "Dial Prefix Number";/* Added by SMuratec C.P 2004/07/08 for prefix */
#endif
#if ( PRO_MAKER == FX )
CUB	PUSA_MesageTrans[]		= "Annotation      ";
#else
CUB	PUSA_MesageTrans[]		= "Cover Page      ";
#endif
CUB	PUSA_RemoteSecurityRx[]	= "Security Rx   ";
CUB	PUSA_NormalPaper[]		= "Normal\000   ";	/* SAKAKIのみ */
CUB PUSA_ThermalPaper[]		= "Thermal\000  ";	/* SAKAKIのみ */
CUB	PUSA_DepartmentProtect[]= "Department Protect";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
CUB	PUSA_Department[]		= "Department";				/* 追加 For ANZU By H.Hirao Feb 29,1996 */
CUB	PUSA_PINAccessMode[]	= "PIN Access Mode";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#if defined(USA)
CUB	PUSA_DayLightSaving[]	= "Daylight Saving";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#endif
CUB	PUSA_OperationProtect[]	= "Operation Protect\000";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#if (PRO_REMOTE_RX == ENABLE)
CUB	PUSA_RemoteReceive[]	= "Remote Transfer\000  ";	/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	PUSA_OnHookReceive[]	= "Onhook Transfer\000  ";	/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif

/* PRO_MULTI_LINE */
/* 基本的に下記ワーディングは
** 		見出し用：半角16文字
** 		内容用  ：半角 8文字
** とします。
** by O.Kimoto 1997/07/10
*/
						/*	   12345678901234567890 */
CUB PUSA_MultiTxRxType[]	= "Tx/Rx Type\000     ";
CUB PUSA_TxRx[]				= "Tx/Rx\000  ";
CUB PUSA_Tx[]				= "Tx\000     ";
CUB PUSA_Rx[]				= "Rx\000     ";
CUB PUSA_MultiLineType[]	= "line Type\000      ";
CUB PUSA_PstnLine[]			= "PSTN\000   ";
CUB PUSA_PbxLine[]			= "PBX\000    ";
CUB PUSA_PstnAccessNumber[]	= "Access No.   :\000 ";
CUB PUSA_LineNumber[]		= "Line Number:\000   ";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題（終端をNULLで判断していない）があるので、ﾜｰﾃﾞｨﾝｸﾞを最大11ﾊﾞｲﾄ・ｺﾛﾝの位置固定(日本語参照)にすること *//*  By O.Kimoto 1997/07/10 */
/** CUB	PUSA_SubscriberKanaID[]	= "発信元名(ｶﾅID)  "; */
/** CUB	PUSA_PhoneType[]		= "通信回線\000 "; */

#if (PRO_MULTI_LINE == ENABLE)	/*  By O.Kimoto 1997/01/06 */
CUB	PUSA_AddErrorMessage[4][31] = {
					/* 123456789012345678901234567890 */
					  "Check the Tx and Rx settings. ",	/** D.0.10 */
					  "Check the attrib. of dial num.",	/** D.0.11 */
					  "Check no. dialed and line type",	/** D.0.12 */
					  "Check no. dialed and line type"	/** D.0.13 */
					  };
#endif

/* 記録紙サイズ */
CUB	PUSA_Paper_A5[]			= "A5_P\0  ";
 #if defined(USA)
CUB	PUSA_Paper_Letter[]		= "Letter\0";
 #else
CUB	PUSA_Paper_Letter[]		= "Ltr_P\0 ";
 #endif
 #if defined(USA)
CUB	PUSA_Paper_A4[]			= "A4_P\0  ";
 #else
CUB	PUSA_Paper_A4[]			= "A4\0    ";
 #endif
 #if defined(USA) || defined(TWN) /* 1998/01/09 Y.Matsukuma */
CUB	PUSA_Paper_Legal[]		= "Legal\0 ";
 #else
CUB	PUSA_Paper_Legal[]		= "Legal_P";
 #endif
CUB	PUSA_Paper_B5R[]		= "B5R_P\0 ";
CUB	PUSA_Paper_B4[]			= "B4_P\0  ";
CUB	PUSA_Paper_A3[]			= "A3_P\0  ";
CUB	PUSA_Paper_A4R[]		= "A4R_P\0 ";
CUB	PUSA_Paper_LetterR[]	= "LtrR_P\0";
 #if defined(TWN) || defined(AUS)	/* 1998/01/08 Y.Matsukuma */
CUB	PUSA_Paper_F4[]			= "F4\0    ";
 #else
CUB	PUSA_Paper_F4[]			= "F4_P\0  ";
 #endif
CUB	PUSA_Paper_A5R[]		= "A5R_P\0 ";
CUB	PUSA_Paper_Postcard[]	= "Post_P\0";
CUB	PUSA_Paper_LD[]			= "Ld_P\0  ";
CUB	PUSA_Paper_GLetterR[]	= "GLtrR_P";
CUB	PUSA_Paper_ExecutiveR[]	= "ExeR_P\0";
CUB	PUSA_Paper_InvoiceR[]	= "InvR_P\0";
CUB	PUSA_Paper_GLegal[]		= "GLegl_P";
CUB	PUSA_Paper_GLetter[]	= "GLtr_P\0";
CUB	PUSA_Paper_Card[]		= "Card_P\0";
CUB	PUSA_Paper_Executive[]	= "Exe_P\0 ";
CUB	PUSA_Paper_B5[]			= "B5_P\0  ";
CUB	PUSA_Paper_C5[]			= "C5_P\0  ";
CUB	PUSA_Paper_HalfLetter[]	= "HLtr_P\0";
CUB	PUSA_Paper_Invoice[]	= "Inv_P\0 ";
CUB	PUSA_Paper_B6[]			= "B6_P\0  ";
CUB	PUSA_Paper_DL[]			= "DL_P\0  ";
CUB	PUSA_Paper_CM10[]		= "CM10_P\0";
CUB	PUSA_Paper_A6[]			= "A6_P\0  ";
CUB	PUSA_Paper_Monarch[]	= "Mnc_P\0 ";
CUB	PUSA_Paper_35[]			= "3x5_P\0 ";
CUB	PUSA_Paper_User[]		= "User_P\0";

/* 記録紙サイズ POPLAR用 */
CUB	PUSA_PaperSize_A5[]			= "A5\0    ";
CUB	PUSA_PaperSize_Letter[]		= "Letter\0";
CUB	PUSA_PaperSize_A4[]			= "A4\0    ";
CUB	PUSA_PaperSize_Legal[]		= "Legal\0 ";
CUB	PUSA_PaperSize_B5R[]		= "B5R\0   ";
CUB	PUSA_PaperSize_B4[]			= "B4\0    ";
CUB	PUSA_PaperSize_A3[]			= "A3\0    ";
CUB	PUSA_PaperSize_A4R[]		= "A4R\0   ";
CUB	PUSA_PaperSize_LetterR[]	= "LtrR\0  ";
CUB	PUSA_PaperSize_F4[]			= "F4\0    ";
CUB	PUSA_PaperSize_A5R[]		= "A5R\0   ";
CUB	PUSA_PaperSize_Postcard[] 	= "Post\0  ";
CUB	PUSA_PaperSize_LD[]			= "Ld\0    ";
CUB	PUSA_PaperSize_GLetterR[]	= "GLtrR\0 ";
CUB	PUSA_PaperSize_ExecutiveR[]	= "ExeR\0  ";
/*  #if (PRO_KEYPANEL == PANEL_POPLAR_B)  *//* modified by honda 1997/11/14 */
/*  #if defined(USA) || defined(GBR)  */
CUB	PUSA_PaperSize_HalfLetterR[]= "HLtrR\0 ";  /* added by honda 1997/10/04 */
/*   #else  */
/*  CUB	PUSA_PaperSize_InvoiceR[]	= "InvR\0  ";  */
/*   #endif  */
/*   #else  */
/*  CUB	PUSA_PaperSize_InvoiceR[]	= "InvR\0  ";  */
/*  #endif  */
CUB	PUSA_PaperSize_GLegal[]		= "GLegl\0 ";
CUB	PUSA_PaperSize_GLetter[]	= "GLtr\0  ";
CUB	PUSA_PaperSize_Card[]		= "Card\0  ";
CUB	PUSA_PaperSize_Executive[]	= "Exe\0   ";
CUB	PUSA_PaperSize_B5[]			= "B5\0    ";
CUB	PUSA_PaperSize_C5[]			= "C5\0    ";
CUB	PUSA_PaperSize_HalfLetter[]	= "HLtr\0  ";
CUB	PUSA_PaperSize_Invoice[]	= "Inv\0   ";
CUB	PUSA_PaperSize_B6[]			= "B6\0    ";
CUB	PUSA_PaperSize_DL[]			= "DL\0    ";
CUB	PUSA_PaperSize_CM10[]		= "CM10\0  ";
CUB	PUSA_PaperSize_A6[]			= "A6\0    ";
CUB	PUSA_PaperSize_Monarch[]	= "Mnc\0   ";
CUB	PUSA_PaperSize_35[]			= "3x5\0   ";
CUB	PUSA_PaperSize_User[]		= "User\0  ";

/* メモリスイッチ */
#if ( PRO_MAKER == FX )
CUB	PUSA_Machine_P[] 		= "Parameter    ";
#else
CUB	PUSA_Machine_P[] 		= "Machine Param";
#endif
CUB	PUSA_Memory_S[] 		= "Memory Switch";
CUB	PUSA_Uniq_S[]			= "Uniq.Switch  ";			/* 追加 For ANZU By H.Hirao Mar.28.1996 */
CUB	PUSA_BitNumber[] 		= "7654 3210";
CUB	PUSA_Default[] 			= " Default ";
CUB	PUSA_AutoSet[] 			= " Setting ";

/* POPLA追加 -- メモリスイッチの追加 */
CUB PUSA_MainteSwitch[]		= "Mnt Switch   ";

/* キノウリスト */
CUB	PUSA_ProgramList[]		= "Program List    ";

/* 通信予約リスト */
CUB	PUSA_ComReservedList[] 	= " ** Command List **  ";

/* 親展者登録リスト */
CUB	PUSA_SecureMailBList[]	= "** SecureMail List **  ";
#if ( PRO_MAKER == FX )
CUB	PUSA_UserName[] 		= "  Name    ";	/* 6/28 FX.ENG */
#else
CUB	PUSA_UserName[] 		= "User Name ";
#endif
CUB	PUSA_Box[] 				= "Box";

/* カバーページプリント */
CUB	PUSA_CoverPageMes[] 	= "Fax Message From:\000  ";	/* 右端 - 2ﾊﾞｲﾄの後、ｾﾝﾀﾘﾝｸﾞ */

/* 親展受信通知 */
CUB	PUSA_SecureMailNotice[] = " SecureMail  ";

/* 親展原稿消去通知 */
CUB	PUSA_ErasedDocuments[] 	= " Erased Documents ";

/* 代行受信消去通知 */
CUB	PUSA_ErasedDocumemts[] 	= "  Erased Documents  ";

/* 通信予約消去通知 */
CUB	PUSA_ErasedCommands[] 	= " Erased Command  ";
#if ( PRO_MAKER == FX )
CUB	PUSA_MemHoldDate[]		= "Print mailbox by   ";
#else
CUB	PUSA_MemHoldDate[]		= "Print SecureMail by";
#endif

/* チェックメッセージ */
CUB	PUSA_CheckMessage[] 	= "Check Message";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PUSA_MemoryOver[] 		= "Memory Over";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PUSA_PcMemoryOver[]		= "PC Memory Over";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PUSA_ErrorPages[] 		= "Error Page(s):";

/* Ｔ３０モニタ */
CUB	PUSA_T30Monitor[]		= "** T30 Monitor ** ";
CUB	PUSA_TxFrame[]			= "TxFrame";
CUB	PUSA_RxFrame[]			= "RxFrame";
CUB	PUSA_Datalong[]			= "D A T A";
CUB	PUSA_Rs144[]			= "144";
CUB	PUSA_Rs120[]			= "120";
CUB	PUSA_Rs96[]				= " 96";
CUB	PUSA_Rs72[]				= " 72";
CUB	PUSA_Rs48[]				= " 48";
CUB	PUSA_Rs24[]				= " 24";
CUB	PUSA_V17[]				= "V17";
CUB	PUSA_V33[]				= "V33";
CUB	PUSA_V29[]				= "V29";
CUB	PUSA_V27[]				= "V27";
CUB	PUSA_MH[]				= " MH";
CUB	PUSA_MR[]				= " MR";
CUB	PUSA_MMR[]				= "MMR";
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
CUB	PUSA_JBG[]				= "JBG";
#endif
CUB	PUSA_A5[]				= "A5";
CUB	PUSA_A6[]				= "A6";
CUB	PUSA_Wait20[]			= "20";
CUB	PUSA_Wait40[]			= "40";
CUB	PUSA_Wait10[]			= "10";
CUB	PUSA_Wait5[]			= " 5";
CUB	PUSA_Wait0[]			= " 0";
CUB	PUSA_ModeNR[]			= "N";
CUB	PUSA_ModeFN[]			= "F";
CUB	PUSA_ModeSF[]			= "S";
CUB	PUSA_ModeHF[]			= "H";

CUB	PUSA_Main[]				= "MAN";
CUB	PUSA_Reset[]			= "Res";
CUB	PUSA_Error[]			= "Err";
CUB	PUSA_Now[]				= "Now";
CUB	PUSA_DpramTx[]			= "Tx";
CUB	PUSA_DpramRx[]			= "Rx";

/* コウジョウ ファンクション リスト */
CUB	PUSA_FunctionList[]		= "Function List       ";
CUB	PUSA_LedTest[]			= "LED Test            ";
CUB	PUSA_LcdTest[]			= "LCD Test            ";
CUB	PUSA_Pane1keytest[]		= "Key Pad Test        ";
CUB	PUSA_Rs232cTest[]		= "RS232C Test         ";
CUB	PUSA_SramCheck[]		= "SRAM Check          ";
CUB	PUSA_DramCheck[]		= "DRAM Check          ";
CUB	PUSA_RTCTest[]			= "RTC Test            ";

/* オンラインモニタ */
#if ( PRO_CLASS1 == ENABLE )
CUB	PUSA_OnLineMonitor[]	= "< Online Monitor > ";
CUB	PUSA_OnLineTx[]			= "TX";
CUB	PUSA_OnLineRx[]			= "RX";
CUB	PUSA_OnLineData[]		= "Data";
CUB	PUSA_Speed[]			= "Speed";
CUB	PUSA_Command[]			= "Cmd";
CUB	PUSA_Response[]			= "Res";
CUB	PUSA_Abort[]			= "Abt";
#endif

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
CUB PUSA_F_CodeBox_List[]	= "** FCODE Box List **";
CUB PUSA_BoxName[]			= "Box Name\0";
CUB PUSA_SubAddress[]		= " Sub-Address\0 ";
CUB PUSA_CommPasscode[]		= "     Password\0    ";
CUB PUSA_Kind[]				= "Kind\0";
CUB PUSA_NoticeBoard[]		= "Bull\0  ";
CUB PUSA_RecvProtect[]		= "Rx Protect";
CUB PUSA_Replace[]			= "OVWRITE";              /* wording by honda 1997/11/10 */
CUB PUSA_RxPrint[]			= "Rx Print\0 ";
CUB PUSA_TransErase[]		= "Erase Polled Doc.";

#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
CUB PUSA_RelayName[] 		= "Relay ";
CUB PUSA_PutSubscriber[] 	= "TTI   ";
CUB PUSA_Avail[]			= "Avail ";
CUB	PUSA_NoTTI[]			= "No TTI  ";
CUB	PUSA_SUB_Relay[]		= "F-Relay";	/* 1998/09/25 By M.Kuwahara */
CUB	PUSA_SUB_Secure[]		= "F-Sec  ";	/* 1998/09/28 By M.Kuwahara */
#endif

#if (PRO_FCODE_KIND_DISPLAY == ENABLE)
CUB	PUSA_SUB_Bulletin[]		= "F-Bull ";	/* 1998/09/28 By M.Kuwahara */
#endif

/* サブアドレス原稿消去通知 */
CUB PUSA_Del_F_CodeBoxDoc_Notice[]	= "FCODE Boxes Doc. Erased  ";
CUB PUSA_BoxLocation[]		= "Location";
CUB PUSA_ThisBoxErased[]	= "These FCODE Box Documents were erased.";

/* サブアドレスＢＯＸ蓄積原稿リスト */
CUB PUSA_DocumentsNo[]		= " File#\0 ";
CUB PUSA_F_CodeDoc_List[]	= "**FCODE List Of Documents **";

/* サブアドレス受信通知 */
#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 1998/10/20 */
CUB PUSA_F_CodeBoxRsv_Notice[]	= "FCODE Box Report ";
#else
CUB PUSA_F_CodeBoxRsv_Notice[]	= "FCODE Box Journal";
#endif
CUB PUSA_F_CodeReci[]		= "FCODE Box Received\0         ";
CUB PUSA_F_ReciDocMemory[]	= "Print ReceivedMail by";
#endif

/* ダイレクトメール防止ダイヤルリスト */
CUB	PUSA_BlockJunkList[]	= " ** Block Junk Fax List ** ";
CUB	PUSA_TelNum[]			= "Tel Number\0";

/* サービスレポート */
CUB	PUSA_ServiceReport[]	= "** Service Report **";

/* ポーリング原稿消去通知 */
CUB	PUSA_ErasePollDoc[]		= "Erased Poll Documents ";

/* 一括送信原稿リスト */
CUB PUSA_BatchTxDocList[]	= "** Batch Send Box Doc. **     "; /* For ANZU 挿入 96/02/13 H.Hirao */

/* 一括送信ＢＯＸリスト */
CUB PUSA_BatchTxBoxList[]	= "** Batch Send Box List **       "; /* For ANZU 挿入 96/02/13 H.Hirao */

CUB PUSA_Batch[]			= "Batch";
CUB PUSA_BoxNo[]			= "Box No.\000   ";

/* 暗号化受信通知リスト */
CUB PUSA_CipherReceiveNotice[]	= " SCRAMBLE RX REPORT ";       /* wording by honda 1998/4/28 */
CUB PUSA_ReceiveNo[]		= "Receive No";
CUB PUSA_KeyClue[]			= "Key Clue    ";         /* wording by honda 1997/11/7 */
CUB PUSA_KeyWordClue[]		= "Key Clue";

/* キーリスト、キーブックリスト */
CUB PUSA_KeyBookList[]		= "**KeyBookList**";
CUB PUSA_KeyWordList[]		= "**  Key  List    **";
CUB PUSA_KeyName[]			= "  Key Title ";
CUB PUSA_Key[]				= " Key  ";

/* 暗号化受信消去通知 */
CUB	PUSA_EraseScrambleRxDoc[]	= "Erased Scrambling Doc.";

/* 消耗品発注票 */
#if defined(JPN)
CUB PUSA_ConsumerOrderSheet[]	= "Order Sheet\0               ";   /* wording by honda 1997/11/13 */
CUB PUSA_ToOrder[]				= "To\0    ";
CUB PUSA_FromOrder[]			= "From\0  ";
CUB PUSA_CustomerCode[]			= "Cust. Code\0    ";		/* JPNは最大10byte *//* wording by honda 1997/11/13 */
CUB PUSA_DistributorName[]		= "Dist. Name\0       ";	/* JPNは最大10byte *//* wording by honda 1997/11/13 */
CUB PUSA_CustomerName[]			= "Cust. Name\0       ";	/* JPNは最大10byte *//* wording by honda 1997/11/13 */
CUB PUSA_Section[]				= "Section\0         ";		/* JPNは最大10byte */
CUB PUSA_ChargeName[]			= "Signature ";
CUB PUSA_ModelName[]			= "Model ";
CUB PUSA_OrderItem[]			= "Order Item";
CUB PUSA_TonerOrder1[]			= "Toner x 1\0       ";		/* 注）ﾄﾅｰ =5byte, x 1の位置固定（日本語参照） *//* wording by honda 1997/11/13 */
CUB PUSA_DrumOrder1[]			= "Drum  x 1\0       ";		/* 注）ﾄﾞﾗﾑ=5byte, x 1の位置固定（日本語参照） *//* wording by honda 1997/11/13 */
CUB PUSA_SeirialNumber[]		= "Serial No.\0         ";	/* JPNは最大10byte *//* wording by honda 1997/11/13 */
CUB PUSA_InstallDate[]			= "Instal.Date\0     ";		/* JPNは最大10byte *//* wording by honda 1997/11/13 */
CUB PUSA_BlockLetters[]			= "               ";		/* JPNは未使用 */
CUB PUSA_Remarks[]				= "Remarks";
CUB PUSA_OrderTonerChange[]		= "Replace toner with a new one.   ";
CUB PUSA_OrderTonerDrumChange[]	= "Replace toner/drum with a new one.      ";
CUB PUSA_OrderSheet[]			= "Please fill out and send this sheet by fax.                 ";
#elif defined(US1)			/* orderbythonda1998/11/11 */
CUB PUSA_ConsumerOrderSheet[]	= "PITNEY BOWES OFFICE SYSTEMS 4100";
CUB PUSA_ConsumerOrderSheet2[]	= "SUPPLIES ORDER FORM";
CUB PUSA_ToOrder[]				= "To:\0   ";				/* 海外は最大6文字 */
CUB PUSA_FromOrder[]			= "From:\0 ";				/* 海外は最大6文字 */
CUB PUSA_CustomerCode[]			= "Customer's Code";
CUB PUSA_DistributorName[]		= "Distributor's Name";
CUB PUSA_CustomerName[]			= "Customer's Name\0  ";
CUB PUSA_Section[]				= "Address(Ship to:)";
CUB PUSA_ChargeName[]			= "Signature ";
CUB PUSA_ModelName[]			= "Model ";
CUB PUSA_OrderItem[]			= "Item Needed: ";
CUB PUSA_TonerOrder1[]			= "Toner Cartridge x       PCS";		/* 注）Toner=5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PUSA_DrumOrder1[]			= "Drum Unit       x       PCS";		/* 注）Drum =5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PUSA_SeirialNumber[]		= "Serial No.";
CUB PUSA_InstallDate[]			= "Installation Date";
CUB PUSA_BlockLetters[]			= "Print Name :";
CUB PUSA_Remarks[]				= "Customer Account No. & Ship to Address";
CUB PUSA_OrderTonerChange[]		= "Replace toner with a new one.   ";	/* JPNのみ */
CUB PUSA_OrderTonerDrumChange[]	= "Your machine's display indicates that either the Toner Cartridge or Drum Unit";
CUB PUSA_OrderTonerDrumChange2[]= "requires replacement.";
CUB PUSA_OrderSheet[]			= "To order replacements by phone, call               , or fill out this form";
CUB PUSA_OrderSheet2[]			= "and fax it to               .";
#else
CUB PUSA_ConsumerOrderSheet[]	= "< Consumables Order Sheet >";
CUB PUSA_ToOrder[]				= "To\0    ";				/* 海外は最大6文字 */
CUB PUSA_FromOrder[]			= "From\0  ";				/* 海外は最大6文字 */
CUB PUSA_CustomerCode[]			= "Customer's Code";
CUB PUSA_DistributorName[]		= "Distributor's Name";
CUB PUSA_CustomerName[]			= "Customer's Name\0  ";
CUB PUSA_Section[]				= "Address(Ship to:)";
CUB PUSA_ChargeName[]			= "Signature ";
CUB PUSA_ModelName[]			= "Model ";
CUB PUSA_OrderItem[]			= "Order Item";
CUB PUSA_TonerOrder1[]			= "Toner x       PCS";		/* 注）Toner=5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PUSA_DrumOrder1[]			= "Drum  x       PCS";		/* 注）Drum =5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PUSA_SeirialNumber[]		= "Serial No.(18digits)";
CUB PUSA_InstallDate[]			= "Installation Date";
CUB PUSA_BlockLetters[]			= "Block Letters :";
CUB PUSA_Remarks[]				= "Remarks";
CUB PUSA_OrderTonerChange[]		= "Replace toner with a new one.   ";	/* JPNのみ */
CUB PUSA_OrderTonerDrumChange[]	= "Replace toner/drum with a new one.      ";
CUB PUSA_OrderSheet[]			= "Please fill out and send this sheet by fax.                 ";
#endif

/* 簡易料金管理リスト */
#if (PRO_DEPART_NEW_LIST == ENABLE)
CUB PUSA_DepartTimeList[]	= "  ** Department Time List **  ";  /* added by thonda 1997/12/02 */
#endif

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
CUB PUSA_KeyMacroList[] 		= "** ｷｰﾏｸﾛ ﾀｲﾄﾙ ﾘｽﾄ **";
CUB PUSA_NoTitle[] 				= "ﾀｲﾄﾙ未登録";
CUB PUSA_Title[] 				= "ﾀｲﾄﾙ";
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
CUB PUSA_NumberDisplayList[]	= "  ** Number Display List **  ";
CUB PUSA_NumberDisplay[]		= "NumberDisplay";
CUB PUSA_NoConnect[]			= "No TEL";
CUB PUSA_Tel1Connect[]			= "PHONE1   ";
CUB PUSA_Tel2Connect[]			= "PHONE2   ";
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
CUB PUSA_ND_Warp[]				= "ND Warp\0";
 #endif

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
CUB PUSA_NumberDisplayJournal[]	= "** Number Display Journal **";
CUB PUSA_SubscriberNumber[]		= "Name      ";
CUB PUSA_NoNotice[]				= "No Notice";
CUB PUSA_OutOfDisp[]			= "Out Disp";
CUB PUSA_PublicTel[]			= "Public Tel";
CUB PUSA_FNetCall[]				= "F Net";
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
CUB PUSA_WarpList[]		 		= "** FAX Warp List **";
CUB PUSA_AppointedTime[]		= "Time    ";
CUB PUSA_WarpFunction[]			= "FAX Warp";
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1999/01/25 */
CUB	PUSA_WarpWeek[][4]			= {
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
CUB	PUSA_Year_Eng[12][4] = {
	"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
	};

/* プログラムリスト */
CUB	PUSA_ProgOnetouchDir[] 	= "** Prog.One-Touch Directory **";

/* 親展受信通知 */
#if ( PRO_MAKER == FX )
CUB	PUSA_SecureMailReci[] 	= "Mailbox Documents are received.         ";
#else
CUB	PUSA_SecureMailReci[] 	= "SecureMail Received.                    ";
#endif

/* 親展原稿消去通知 */
CUB	PUSA_ThisSecMailEra[] 	= "These SecureMail Documents were erased.\000";

/* 代行受信消去通知 */
#if ( PRO_MAKER == FX )
CUB	PUSA_ThisMemErased[] 	= "Received documents are erased.\000         ";	/* 6/28 FX.ENG */
#else
CUB	PUSA_ThisMemErased[] 	= "These Documents were erased.\000           ";
#endif

/* 通信予約消去通知 */
#if ( PRO_MAKER == FX )
CUB	PUSA_ThisComErased[] 	= "Pending jobs are erased.\000                 ";	/* 6/28 FX.ENG */
#else
 #if (PRO_DRAM_BACKUP == ENABLE)			/*94/11/28 ↓ By jmasuda*/
 CUB	PUSA_ThisComErased[] 	= "Commands were erased.  \000                  ";
 #else									/*94/11/28 ↑ By jmasuda*/
 CUB	PUSA_ThisComErased[] 	= "All commands were erased.  \000              ";
 #endif
#endif

/* チェックメッセージ */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/26 */
CUB	PUSA_MryOverFeeder[]	= "Due to memory full,Trans. was failed.\000";
CUB	PUSA_SecurityMemOver[]	= "Memory full. Please print received security documents.\000                    ";
#else
CUB	PUSA_MryOverFeeder[]	= "Due to memory full,Trans. was failed.";
CUB	PUSA_SecurityMemOver[]	= "Memory full. Please print received security documents.\000                    ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* セキュリティ受信をONにする。メモリーオーバーするまで受信を行う。チェックメッセージが印字されるが、内容が一部間違っている。 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec K.W.Q 2003/10/20 */
CUB	PUSA_SecurityOperation1[]	= "Usage: Press PROGRAM,One-Touch[11],2,ENTER\0 ";
#else
CUB	PUSA_SecurityOperation1[]	= "Usage: Press PROGRAM,One-Touch[O],2,ENTER\0";   /* 0->O bythonda1998/04/16 *//* by honda 1997/11/7 */
#endif

#if (PRO_OKI == ENABLE)	/* OKI仕様 by K.Watanabe 1998/10/20 */
CUB	PUSA_SecurityOperation2[]	= "       and then enter Password (4-digits)\0  ";
#else
CUB	PUSA_SecurityOperation2[]	= "       and then enter Passcode (4-digits)\0  "; /* by honda 1997/11/7 */
#endif

/* ポーリング原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB	PUSA_PollErase[]		= "Polled documents are erased.\000                  ";	/* 6/28 FX.ENG */
#else
CUB	PUSA_PollErase[]		= "Polling documents were erased.\000                ";
#endif
CUB	PUSA_DbPollErase[]		= "DB Polling documents were erased.\000                  ";

/* 一括送信原稿リスト */
CUB	PUSA_IndexNo[]			= "  Receipt#\000  ";

/* 一括送信原稿消去通知 */
/* CUB	PUSA_BatchTxDocErase[]	= "Batch send documents are erased.        "; */
CUB	PUSA_BatchTxDocErase[]	= "Batch send documents were erased.       ";	/* 表現を統一します。 By S.Fukui Mar.26,1998 */

/* 連続ポーリングコマンド消去通知 */
CUB	PUSA_ContinuousPollingErase[] = "Continuous Polling Command was erased.            ";/* 1996/10/18 Eguchi */

/* 暗号化受信原稿消去通知 */
CUB	PUSA_ScrambleRxErase[]		= "These Scrambling Documents were erased.        ";

/* 通信結果メッセージ */
CUB	PUSA_ResultName[8][31] = {  "Check condition of remote fax.",	/* "～ remote Fax." -> "～ remote fax." 1998/09/19 By M.Kuwahara*/
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
#if (PRO_MAKER == FX)	/* By H.Y 1994/12/20 */
CUB	PUSA_ResultChain[LST_ERR_CODE_MAX] = {
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
CUB	PUSA_ResultChain[LST_ERR_CODE_MAX] = {
							'D','F','A','C','A',		/*0*/
							'G','A','A','A','C',        /*5*/
							'C','B','A','A','A',        /*10*/
							'C','A','A','G','A',        /*15*/
							'A','A','A','B','A',        /*20*/
							'E','A','A','A','A',		/*25*/
							'A','A','A','H','C',		/*30*/
							'G','C','C',' ',' ' }; 		/*35*/
 #else
CUB	PUSA_ResultChain[LST_ERR_CODE_MAX] = {
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
/*PUSA_ResultChain[]の'A'がPUSA_ResultName[][]の一番目のﾒｯｾｰｼﾞに対応する*/
CUB	PUSA_ResultCode[LST_ERR_CODE_MAX][7] = {
						"D.0.2", "D.0.6", "T.1.1", "T.1.2", "T.1.3",	/*0*/
						"T.1.4", "T.2.1", "T.2.2", "T.2.3", "T.3.1",	/*5*/
						"T.4.1", "T.4.2", "T.4.3", "T.5.1", "T.5.2",	/*10*/
						"T.5.3", "R.1.1", "R.1.2", "R.1.4", "R.2.3",	/*15*/
						"R.3.1", "R.3.3", "R.3.4", "R.4.1", "R.4.2",	/*20*/
						"R.4.4", "R.5.1", "R.5.2", "D.0.7", "T.4.4",	/*25*/
						"R.2.1", "R.3.2", "R.3.5", "R.4.5", "D.0.1",	/*30*/
						"D.0.3", "D.0.8", "R.1.3", "", "" };			/*35*/
/*最後の項目は必ず""としておく必要あり*/
/*PUSA_ResultCode[]がPUSA_ResultChain[]に対応する*/

#if (PRO_ROTATE == ENABLE)				/* ＤＰＲＡＭ経由の回転受信 */
					/*	   12345678901234567890 */
CUB PUSA_RotateMargin[]	= "Rotate Margin   ";
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
CUB PUSA_INF_AddressList[]		= "** Mail Address Directory **";
CUB PUSA_INF_GroupList[]		= "** Mail Group Directory **";
CUB	PUSA_INF_MailComList[]		= "** Reserved Mail Commands **";
CUB	PUSA_INF_SettingList[]		= "** User Setting List **";
CUB	PUSA_INF_ErasedMailList[]	= "     ** Erased Mails **     ";
CUB PUSA_INF_ErasedCommand[]	= "** Erased Mail Commands **";
CUB PUSA_INF_Group[]			= "Mail Group";
CUB PUSA_INF_Address[]			= "Mail Address";
CUB PUSA_INF_UserName[]			= "User Name";
CUB PUSA_INF_ProviderName[]		= "ISP Name\000    ";
CUB PUSA_INF_AccessPoint1[]		= "Access Point 1";
CUB PUSA_INF_AccessPoint2[]		= "Access Point 2";
CUB PUSA_INF_AccessPoint3[]		= "Access Point 3";
#if (0)
CUB PUSA_INF_PPPLoginID[]		= "Dial-Up Login ID  ";
CUB PUSA_INF_PPPPassword[]		= "Dial-Up Login Password ";
CUB PUSA_INF_PPPAuth[]			= "Password Authentication";
CUB PUSA_INF_POPLoginID[]		= "Mail Login ID";
CUB PUSA_INF_POPPassword[]		= "Mail Login Password";
#endif
CUB PUSA_INF_PPPLoginID[]		= "PPP Login ID";
CUB PUSA_INF_PPPPassword[]		= "PPP Login Password";
CUB PUSA_INF_PPPAuth[]			= "PPP Authentication";
CUB PUSA_INF_POPLoginID[]		= "POP Login ID";
CUB PUSA_INF_POPPassword[]		= "POP Login Password";

CUB PUSA_INF_MailAddress[]		= "Mail Address";
CUB PUSA_INF_SMTPServer[]		= "SMTP Server";
CUB PUSA_INF_POPServer[]		= "POP Server";
CUB PUSA_INF_PriDNSServer[]		= "Primary DNS Server";
CUB PUSA_INF_SecDNSServer[]		= "Secondary DNS Server";
CUB PUSA_INF_ClientAddress[]	= "Client IP Address";
CUB PUSA_INF_ServerAddress[]	= "Server IP Address";
CUB PUSA_INF_GatewayAddress[]	= "Gateway IP Address";
CUB PUSA_INF_TxRx[]				= "Tx with Rx\000 ";
CUB PUSA_INF_AutoRcvMail[]		= "Auto Receive Mail";

CUB PUSA_INF_StartTime[]		= "Start Time";
CUB PUSA_INF_EndTime[]			= "End Time\000 ";
CUB PUSA_INF_IntervalTime[]		= "Interval Time";
CUB PUSA_INF_HoldTime[]			= "Hold Days";
CUB PUSA_INF_AutoPrint[]		= "Auto Print";

CUB PUSA_INF_ComsWereErased[]	= "Mail Commands were erased.\000                 ";
CUB	PUSA_INF_MailsWereErased[]	= "Received mails were erased.\000        ";
CUB	PUSA_INF_Receiver[]			= "Receiver: \000";
CUB	PUSA_INF_ErrorCode[]		= "Error Code";
CUB	PUSA_INF_ReTx[]				= "Repeat transmission\000  ";
CUB	PUSA_INF_ReRx[]				= "Repeat reception\000     ";
CUB	PUSA_INF_DialErr[]			= "Fail to connect with ISP\000 ";
CUB	PUSA_INF_ChkSetting[]		= "Check Your settings\000      ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	PUSA_INF_MemErr[]			= "Memory full\000            ";
#else
CUB	PUSA_INF_MemErr[]			= "Memory full\000          ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB	PUSA_INF_ChkBoard[]			= "Check option board\000        ";
CUB	PUSA_INF_PowerOff[]			= "Power Off\000          ";
CUB	PUSA_INF_Kind[] 			= "Kind\000";
CUB	PUSA_INF_To[]	 			= "To";
CUB	PUSA_INF_Tx[] 				= "Tx";
CUB	PUSA_INF_Rx[] 				= "Rx";
CUB	PUSA_INF_User[]				= "User:\000";
CUB	PUSA_INF_AccessPoint[]		= "Access Point:";

CUB	PUSA_INF_ConnectTime[]		= "Connect Time (min)";
CUB	PUSA_INF_ConnectCount[]		= "Connect Count";

CUB	PUSA_MailReceptionReport[]	= "** Mail Reception Report **\000     ";
CUB	PUSA_MailSender[]			= "Sender\000";
CUB	PUSA_MailReceivedTime[]		= "ReceivedTime\000";
CUB	PUSA_MailAutoPrintTime[]	= "PrintTime\000   ";
CUB	PUSA_MailRxReportState1[]	= "Following mails have been received.                                    ";/*71*/
CUB	PUSA_MailRxReportState2[]	= "Please press PROGRAM,R,2,ENTER, and then enter your Code Number        ";
CUB	PUSA_MailRxReportState3[]	= "to print these mails.                                                  ";
CUB	PUSA_MailRxReportState4[]	= "These mails will be printed automatically when \"PrintTime\" will be passed. ";

/*追加 1998/5/25 Eguchi*/
CUB	PUSA_INF_JournalComStartTime[] = "StartTime  ";

CUB	PUSA_INF_Ok[]				= "OK\000";
CUB	PUSA_INF_Error[]			= "ERROR\000";
CUB	PUSA_INF_AutoDownLoad[]		= "Auto Download \000";
CUB	PUSA_INF_DeleteMail[]		= "Delete Mail\000";
CUB	PUSA_INF_AutoCheck[]		= "Auto Check Mail\000";

CUB	PUSA_INF_MailJournal[]		= "   ** Mail Journal **   ";

#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */

/* 通信結果プリント */
#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
CUB PUSA_TransmitResult[]		= "** Transmit Result **\0   ";/*25(40)*/
CUB PUSA_ReceiveResult[]		= "** Receive Result **\0    ";/*25(40)*/
#endif

#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
/*@^s**************************************************************************
**@^1
**@^2	ﾌﾟﾘﾝﾄ用固定文字列 ENGLISH (USA) 横倍角文字タイトル
**@^3	桐／紅葉のﾀｲﾄﾙは、最初から横倍角(全角)とし、別ﾌｧｲﾙとする
**@^4	94/ 5/27 豊田
**@^e*************************************************************************/

/* 送信証　受領証 */
CUB	PUSA_TransConfReport_K[] 		= "＊＊　Ｔｒａｎｓｍｉｔ　Ｃｏｎｆ．Ｒｅｐｏｒｔ　＊＊";
CUB	PUSA_RecConfReport_K[] 			= "＊＊　Ｒｅｃｅｉｖｅ　Ｃｏｎｆ．Ｒｅｐｏｒｔ　＊＊";

/* 通信管理レポート｢送信｣ ｢受信｣ */
CUB PUSA_TransmitJournal_K[]		= "＊＊　Ｔｒａｎｓｍｉｔ　Ｊｏｕｒｎａｌ　＊＊";
CUB PUSA_RecieveJournal_K[]			= " ＊＊　Ｒｅｃｅｉｖｅ　Ｊｏｕｒｎａｌ　＊＊ ";

/* 短縮ダイヤルリスト */
#if ( PRO_MAKER == FX )
CUB	PUSA_TeleDirectory_K[]			= " 　　＊＊　Ｓｐｅｅｄ－Ｄｉａｌ　Ｌｉｓｔ　＊＊　　 ";
#else
CUB	PUSA_TeleDirectory_K[]			= "＊＊　Ｓｐｅｅｄ－Ｄｉａｌ　Ｄｉｒｅｃｔｏｒｙ　＊＊";
#endif

/* ワンタッチダイヤルリスト */
#if ( PRO_MAKER == FX )
CUB	PUSA_OneDirectory_K[]			= " ＊＊　ＯｎｅーＴｏｕｃｈ　Ｄｉａｌ　Ｌｉｓｔ　＊＊ ";
#else
CUB	PUSA_OneDirectory_K[]			= " ＊＊　Ｏｎｅ－Ｔｏｕｃｈ　Ｄｉｒｅｃｔｏｒｙ　＊＊ ";
#endif

/* 属性リスト */
CUB PUSA_AttributeList_K[]			= "＊＊　Ａｔｔｒｉｂｕｔｅ　Ｌｉｓｔ　＊＊";

/* グループリスト */
#if ( PRO_MAKER == FX )
CUB PUSA_GroupDirectory_K[]			= "＊＊　Ｇｒｏｕｐ　Ｄｉａｌ　Ｌｉｓｔ　＊＊";
#else
CUB PUSA_GroupDirectory_K[]			= "＊＊　Ｇｒｏｕｐ　Ｄｉｒｅｃｔｏｒｙ　＊＊";
#endif

/* マルチプログラムリスト */
#if ( PRO_MAKER == FX )
CUB	PUSA_MultiProgram_K[]			= "　　＊＊　Ｍｕｌｔｉ　Ｐｒｏｇｒａｍ　Ｌｉｓｔ　＊＊　　";	/* 6/28 FX.ENG */
#else
CUB	PUSA_MultiProgram_K[]			= "＊＊　ＭｕｌｔｉＰｒｏｇｒａｍ　Ｄｉｒｅｃｔｏｒｙ　＊＊";	/* 6/28 FX.ENG */
#endif

/* 機器設定リスト */
#if ( PRO_MAKER == FX )
CUB PUSA_MachineSettings_K[]		= "　＊＊　Ｃｕｓｔｕｍ　Ｐｒｅｓｅｔｓ　＊＊　";	/* 6/28 FX.ENG */
#else
CUB PUSA_MachineSettings_K[]		= " 　＊＊　Ｕｓｅｒ　Ｓｅｔｔｉｎｇｓ　＊＊　 ";
#endif

/* 機能リスト */
#if ( PRO_MAKER == FX )
CUB PUSA_ProgramList_K[]			= "Ｆｕｎｃｔｉｏｎ　Ｔｒｅｅ　　　";
#else
CUB PUSA_ProgramList_K[]			= "Ｐｒｏｇｒａｍ　Ｌｉｓｔ　　　　";
#endif

/* 通信予約リスト */
#if ( PRO_MAKER == FX )
CUB PUSA_ComReservedList_K[]		= "＊＊Ｐｅｎｄｉｎｇ　Ｊｏｂｓ　Ｌｉｓｔ＊＊";	 /* 6/28 FX.ENG */
#else
CUB PUSA_ComReservedList_K[]		= " 　＊＊　Ｃｏｍｍａｎｄ　Ｌｉｓｔ　＊＊　 ";
#endif

/* 親展者リスト */
#if ( PRO_MAKER == FX )
CUB PUSA_SecureMailBList_K[]		= " 　　＊＊　Ｍａｉｌｂｏｘ　Ｌｉｓｔ　＊＊　　 ";
#else
CUB PUSA_SecureMailBList_K[]		= "　＊＊　ＳｅｃｕｒｅＭａｉｌ　Ｌｉｓｔ　＊＊　";
#endif

/* カバーページプリント */
#if ( PRO_MAKER == FX )
CUB PUSA_CoverPageMes_K[]			= " 　＊＊　Ｆａｘ　Ｍｅｓｓａｇｅ　＊＊　 ";
#else
CUB PUSA_CoverPageMes_K[]			= "Ｆａｘ　Ｍｅｓｓａｇｅ　Ｆｒｏｍ：　　　";
#endif

/* 親展受信通知 */
#if ( PRO_MAKER == FX )
CUB PUSA_SecureMailNotice_K[]		= "ＭａｉｌｂｏｘＲｅｐｏｒｔ";
#else
CUB PUSA_SecureMailNotice_K[]		= " 　ＳｅｃｕｒｅＭａｉｌ　 ";
#endif

/* 親展原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB PUSA_ErasedDocuments_K[]		= "Ｒｃｖ　Ｍａｉｌｂｏｘ　Ｅｒａｓｅｄ";
#else
CUB PUSA_ErasedDocuments_K[]		= "　Ｅｒａｓｅｄ　Ｄｏｃｕｍｅｎｔｓ　";
#endif

/* 代行受信消去通知 */
#if ( PRO_MAKER == FX )
CUB PUSA_ErasedDocumemts_K[]		= " Ｒｃｖ　Ｄｏｃｕｍｅｎｔ　Ｅｒａｓｅｄ ";	/* 6/28 FX.ENG */
#else
CUB PUSA_ErasedDocumemts_K[]		= "　　Ｅｒａｓｅｄ　Ｄｏｃｕｍｅｎｔｓ　　";
#endif

/* 通信予約消去通知 */
#if ( PRO_MAKER == FX )
CUB PUSA_ErasedCommands_K[]			= "Ｐｅｎｄｉｎｇ Ｊｏｂ Ｅｒａｓｅｄ";	/* 10/18 FX.ENG */
#else
CUB PUSA_ErasedCommands_K[]			= " 　Ｅｒａｓｅｄ　Ｃｏｍｍａｎｄ　 ";
#endif

/* チェックメッセージ　メモリオーバー */
#if ( PRO_MAKER == FX )
CUB PUSA_CheckMessage_K[]			= "Ｓｅｎｄ　Ｆａｉｌ　Ｒｅｐ";
#else
CUB PUSA_CheckMessage_K[]			= "Ｃｈｅｃｋ　Ｍｅｓｓａｇｅ";
#endif
CUB PUSA_MemoryOver_K[]				= "Ｍｅｍｏｒｙ　Ｏｖｅｒ";
CUB PUSA_PcMemoryOver_K[]			= "ＰＣ　Ｍｅｍｏｒｙ　Ｏｖｅｒ";

/* Ｔ３０モニタ */
CUB PUSA_T30Monitor_K[]				= " ＊＊　Ｔ３０　Ｍｏｎｉｔｏｒ　＊＊ ";

/* ﾎﾟｰﾘﾝｸﾞ原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB PUSA_ErasePollDoc_K[]			= " 　　Ｐｏｌｌｅｄ　Ｄｏｃ．Ｅｒａｓｅｄ　　 ";
#else
CUB PUSA_ErasePollDoc_K[]			= " Ｅｒａｓｅｄ　Ｐｏｌｌ　Ｄｏｃｕｍｅｎｔｓ ";
#endif

/* 一括送信原稿リスト */
CUB	PUSA_BatchTxDocList_K[]			= "＊＊　ＢａｔｃｈＳｅｎｄＢｏｘＤｏｃ．　＊＊";	/* 6/28 FX.ENG */

/* 一括送信原稿消去通知 */
CUB	PUSA_EraseBatchTxDoc_K[]		= " ＢａｔｃｈＳｅｎｄＤｏｃ．Ｅｒａｓｅｄ ";	/* 6/28 FX.ENG */

/* 一括送信ＢＯＸリスト */
CUB	PUSA_BatchTxBoxList_K[]			= "＊＊　ＢａｔｃｈＳｅｎｄＢｏｘ　Ｌｉｓｔ　＊＊";	/* 6/28 FX.ENG */

/* 部門管理リスト*/
#if ( PRO_MAKER == FX )
CUB	PUSA_DepartCodeList_K[]			= "　　　　　　＊＊　Ａｃｃｏｕｎｔ　Ｌｉｓｔ　＊＊　　　　　　";	/* 6/28 FX.ENG */
#else
CUB	PUSA_DepartCodeList_K[]			= " 　　　　＊＊　Ｄｅｐａｒｔｍｅｎｔ　Ｌｉｓｔ　＊＊　　　　 ";
#endif

/* 料金表 */
CUB	PUSA_CostBase_K[]				= "＊＊　Ｃｈａｒｇｅ　＊＊";	/* POPLAR_Hのみ */

/* プログラムリスト */
#if ( PRO_MAKER == FX )
CUB	PUSA_ProgOnetouchDir_K[]		= "　　　　＊＊　Ｐ　Ｏｎｅ　Ｔｏｕｃｈ　Ｌｉｓｔ　＊＊　　　　";
#else
CUB	PUSA_ProgOnetouchDir_K[]		= "＊＊　Ｐｒｏｇ．Ｏｎｅ－Ｔｏｕｃｈ　Ｄｉｒｅｃｔｏｒｙ　＊＊";
#endif

/* モニターレポート */
CUB	PUSA_MonitorReport_K[]			= "Ｍｏｎｉｔｏｒ　Ｒｅｐｏｒｔ";

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
CUB PUSA_F_CodeBox_List_K[]			= "＊＊　ＦＣＯＤＥ　Ｂｏｘ　Ｌｉｓｔ　＊＊";

/* サブアドレス原稿消去通知 */
CUB PUSA_Del_F_CodeBoxDoc_Notice_K[]	= "ＦＣＯＤ　Ｌｉｓｔ　Ｏｆ　Ｅｒａｓｅｄ　Ｂｏｘｅｓ";

/* サブアドレスBOX蓄積原稿リスト */
CUB PUSA_F_CodeDoc_List_K[]			= "＊＊  ＦＣＯＤＥ　Ｌｉｓｔ　Ｏｆ　Ｄｏｃｕｍｅｎｔｓ　＊＊";

/* サブアドレス受信通知 */
CUB PUSA_F_CodeBoxRsv_Notice_K[]	= "ＦＣＯＤＥ　Ｂｏｘ　Ｊｏｕｒｎａｌ";
#endif

/* ダイレクトメール防止ダイヤルリスト */
CUB	PUSA_BlockJunkList_K[]			= "＊＊　Ｂｌｏｃｋ　Ｊｕｎｋ　Ｆａｘ　Ｌｉｓｔ　＊＊　";

/* サービスレポート */
CUB	PUSA_ServiceReport_K[]			= "＊＊　Ｓｅｒｖｉｃｅ　Ｒｅｐｏｒｔ　＊＊";

/* 暗号化受信通知リスト */
/*CUB PWRD_CipherReceiveNotice_K[]	= "スクランブル受信通知";	 98/01/12 By M.Kuwahara */
CUB PUSA_CipherReceiveNotice_K[]	= "  Ｓｃｒａｍｂｌｅ　Ｒｘ　Ｒｅｐｏｒｔ  ";

/* キーブックリスト */
/*CUB PWRD_KeyBookList_K[]			= "＊＊　キーバンク　＊＊";	 98/01/12 By M.Kuwahara */
CUB PUSA_KeyBookList_K[]			= "＊＊　ＫｅｙＢｏｏｋＬｉｓｔ　＊＊";

/* キーリスト */
/*CUB PWRD_KeyWordList_K[]			= "＊＊　キーワードリスト　＊＊";*/
CUB PUSA_KeyWordList_K[]			= "＊＊  Ｋｅｙ Ｌｉｓｔ   ＊＊";

/* 暗号化受信消去通知 */
/*CUB	PWRD_EraseScrambleRxDoc_K[]		= "スクランブル原稿消去通知";*/
CUB	PUSA_EraseScrambleRxDoc_K[]		= "Ｅｒａｓｅｄ　Ｓｃｒａｍｂｌｉｎｇ　Ｄｏｃ．";

/* 消耗品発注票 */
 #if defined(JPN)
CUB PUSA_ConsumerOrderSheet_K[]		= "Ｏｒｄｅｒ　Ｓｈｅｅｔ";   /* modified by honda 1997/11/12 */
 #else
CUB PUSA_ConsumerOrderSheet_K[]		= "消耗品発注票　　　　　";
 #endif

 #if (PRO_COST == ENABLE)				/* 料金管理 *//* Add By O.Kimoto 1997/11/17 */
/* 料金表 */
CUB	PUSA_DialingCode[]		= "CityCode";
CUB	PUSA_Daytime[]			= "  Day(Sec/\\10)  ";	/* 6/28 FX.ENG */
CUB	PUSA_Night[]			= " Night(Sec/\\10) ";	/* 6/28 FX.ENG */
CUB	PUSA_Midnight[]			= "M.Night(Sec/\\10)";	/* 9/17 FX.ENG */
CUB	PUSA_Slash10[]			= "   ";
CUB	PUSA_WithinArea[]		= "AreaCall";
 #endif

 #if (PRO_LINENUMBER == TWICE_LINE)
/* 内蔵回線のラベルです。 By O.Kimoto 1997/12/20 */
#if (0)
** CUB PUSA_InternalLineName[][8]            = {
** 									/* 	"123456789" */
** 										"(Std.):",
** 										"(Ext.):"
** 										};
#endif
CUB PUSA_LineName[][8]			= {
									/* 	"123456789" */
										"Std.",
										"Ext.",
										"Opt."
										};
 #endif


#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
CUB	PUSA_INF_MailComList_K[]	= "＊＊　Ｒｅｓｅｒｖｅｄ　Ｍａｉｌ　Ｃｏｍｍａｎｄｓ　＊＊";
CUB	PUSA_INF_SettingList_K[]	= "＊＊　Ｕｓｅｒ　Ｓｅｔｔｉｎｇ　Ｌｉｓｔ　＊＊";
CUB	PUSA_INF_ErasedMailList_K[]	= "＊＊　Ｅｒａｓｅｄ　Ｍａｉｌｓ　＊＊";
CUB PUSA_INF_ErasedCommand_K[]	= "＊＊　Ｅｒａｓｅｄ　Ｍａｉｌ　Ｃｏｍｍａｎｄｓ　＊＊";
#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
CUB PUSA_KeyMacroList_K[]	= "＊＊　キーマクロ　タイトル　リスト　＊＊";
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
CUB PUSA_NumberDisplayList_K[] = "＊＊　Ｎｕｍｂｅｒ　Ｄｉｓｐｌａｙ　Ｌｉｓｔ　＊＊";

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
CUB PUSA_NumberDisplayJournal_K[]	= "＊＊　Ｎｕｍｂｅｒ　Ｄｉｓｐｌａｙ　Ｊｏｕｒｎａｌ　＊＊";
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
CUB PUSA_WarpList_K[] 		= "＊＊　ＦＡＸ　Ｗａｒｐ　Ｌｉｓｔ　＊＊";
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
CUB PUSA_EmergencyTitle_Emergency_K[] 		= " 　＊＊　緊急　＊＊ ";
CUB PUSA_EmergencyTitle_Normal_K[]	 		= " 　＊＊　普通　＊＊ ";
 #endif
#endif

#if (0)
** /* 宣言する位置が間違えています By O.Kimoto 2002/07/18 */
** #if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/17 K.Kawata */
** /* 再送時チェックメッセージ 2000/2/17 K.Kawata */
** CUB	PUSA_SendDocument[] = "Send the document(s) from page\0         ";
** #endif
#endif

#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
CUB PUSA_TransmitResult_K[]		= "＊＊　Ｔｒａｎｓｍｉｔ　Ｒｅｓｕｌｔ　＊＊\0   ";/*25(40)*/
CUB PUSA_ReceiveResult_K[]		= "＊＊　Ｒｅｃｅｉｖｅ　Ｒｅｓｕｌｔ　＊＊\0    ";/*25(40)*/
#endif

#endif

#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/17 K.Kawata */
/* 再送時チェックメッセージ 2000/2/17 K.Kawata */
CUB	PUSA_SendDocument[] = "Send the document(s) from page\0         ";
#endif

#if defined(STOCKHM2) || defined(HINOKI3)	/*ダイヤルトーン検出対応 by Y.Kano 2004/08/11 */ /* Add by Y.Kano 2004/12/07 */
CUB	PUSA_DialTone[]			= "Dial Tone Detect\0";
#endif

/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの最後に入れる) */
CUB	PUSA_TAIL[]			= "";

#undef	CUB
