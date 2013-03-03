/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_WFRA.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 帳票用固定文字列 FRENCH (FRA)
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\lst_def.h"

#define	CUB		CONST UBYTE

/* #define		｢	0xA2	eの上に´(右上から)		*/
/* #define		ｧ	0xA7	cの下にJ				*/
/* #define		ｪ	0xAA	eの上に｀(左上から)		*/
/* #define		ｬ	0xAC	iの上に＾				*/
/* #define		ｶ	0xB6	uの上に＾				*/
/* #define		ﾏ	0xCF	ﾟ (特殊文字の丸)		*/

#if (PRO_CPU == SH7043) /* ワーディング先頭位置認識用 1996/07/04 T.Nose */
	#if (WORDING_1 == FRENCH)
		CUB PWRD_1stWordingTop[] = "\0";
	#endif
	#if (WORDING_2 == FRENCH)
		CUB PWRD_2ndWordingTop[] = "\0";
	#endif
	#if (WORDING_3 == FRENCH)
		CUB PWRD_3rdWordingTop[] = "\0";
	#endif
#endif

/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの先頭に入れる) */
CUB	PFRA_HEAD[]				= "";

/* 送信証　受領証 */
CUB	PFRA_TransConfReport[] 	= "  ** Rapport Emission **  ";
CUB	PFRA_RecConfReport[] 	= " ** Rapport R｢ception ** ";
CUB	PFRA_FromTo[] 			= "--->";
CUB	PFRA_CommNo[] 			= "Nﾏ.\000       ";
CUB	PFRA_CommMode[] 		= "Mode\000    ";
CUB	PFRA_CommStartTime[] 	= "Dur｢e\000   ";
CUB	PFRA_CommPages[] 		= "Pages\000   ";
CUB	PFRA_CommResult[] 		= "R｢sultat\000";
#if ( PRO_MAKER == FX )
CUB	PFRA_Normal[] 			= "Standard";
CUB	PFRA_Fine[] 			= "Fine\000 ";
CUB	PFRA_SFine[] 			= "SuperFine";
CUB	PFRA_Gray[] 			= "Halftone";
#else
CUB	PFRA_Normal[] 			= "Normal\000 ";
CUB	PFRA_Fine[] 			= "Fin\000  ";
CUB	PFRA_SFine[] 			= "S-Fin\000   ";
 #if (PRO_PITNEYBOWES == ENABLE)
CUB	PFRA_Gray[] 			= "Photo\000  ";
CUB	PFRA_HFine[] 			= "H-Fin\000   ";	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
CUB	PFRA_HGray[] 			= "H Photo\000";	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
 #else
CUB	PFRA_Gray[] 			= "Gris\000   ";
 #endif
#endif
CUB	PFRA_Pages[] 			= "Page(s)";
CUB	PFRA_FaxD[] 			= "Fax:";

/* 通信管理レポート */
CUB	PFRA_TransmitJournal[]	= "[Emission]      ";
CUB	PFRA_RecieveJournal[]	= "[R｢ception]     ";
CUB	PFRA_ContNo[]			= " Nﾏ.\000";
CUB	PFRA_RemoteFrom[]		= "   De:\000 ";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題（終端をNULLで判断していない）があるので、ﾜｰﾃﾞｨﾝｸﾞを最大5ﾊﾞｲﾄ・ｺﾛﾝの位置固定(英語参照)にすること */
CUB	PFRA_RemoteTo[]			= "   A\000   ";
CUB	PFRA_Mode[] 			= "  Mode\000  ";
#if ( PRO_MAKER == FX )
CUB	PFRA_Start[] 			= "Transmit";	/* 6/26 FX.ENG */
#else
CUB	PFRA_Start[] 			= " D｢but\000 ";
#endif
CUB	PFRA_Received[] 		= " D｢but\000 ";
CUB	PFRA_Time[] 			= "Dur｢e\000";
CUB	PFRA_Page[] 			= "Page";
CUB	PFRA_Code[] 			= "Code";
CUB	PFRA_Result[] 			= "R｢sult.";
CUB	PFRA_Note[] 			= " Note\000";
CUB	PFRA_AltNo[] 			= "NUM ALT.";
CUB	PFRA_Secure[] 			= "S｢cure\000";
CUB	PFRA_Relay[] 			= "Relais\000";
#if (PRO_OKI == ENABLE)
CUB	PFRA_Polling[] 			= "Relｪve\0";	/* Polling -> Relｪve by K.Watanabe 1999/02/04 */
CUB	PFRA_DbPolling[] 		= "Relｪ.DB";	/* Poll -> Relｪ by K.Watanabe 1999/02/04 */
#else
CUB	PFRA_Polling[] 			= "Polling";
CUB	PFRA_DbPolling[] 		= "Poll.DB";
#endif
CUB	PFRA_Manual[] 			= "Manuel\000";
CUB	PFRA_RelayedTxReport[]	= "RapEmRl";
#if defined(USA) || defined(US2) || defined(AUS)	/*95/05/24 By j.masuda */
CUB	PFRA_FIP_Tx[] 			= "MFS_Em\000";
CUB	PFRA_FIP_Rx[] 			= "MFS_Rx\000";
CUB	PFRA_FIP_Poll[] 		= "MFS_Pol";
CUB	PFRA_FIP_Sec[] 			= "MFS_Sec";
#else								/*95/05/24 By j.masuda */
CUB	PFRA_FIP_Tx[] 			= "FIP_Em\000";
CUB	PFRA_FIP_Rx[] 			= "FIP_Rx\000";
CUB	PFRA_FIP_Poll[] 		= "FIP_Rel";	/* Pol -> Rel by K.Watanabe 1999/02/04 */
CUB	PFRA_FIP_Sec[] 			= "FIP_Sec";
#endif
CUB	PFRA_BrdCast[]	 		= "Diffus.";
CUB	PFRA_Ok[] 				= "Cor";
/* Fｺｰﾄﾞ */
CUB	PFRA_SUB_Tx[]			= "EmFcode";
#if (PRO_OKI == ENABLE)	/* 条件コンパイルが入っていなかったので追加 by K.Watanabe 1999/12/28 */
CUB PFRA_SEP_Rx[]			= "Relｪ-FC";	/* Poll -> Relｪ by K.Watanabe 1999/02/04 */
#else
CUB PFRA_SEP_Rx[]			= "Poll-FC";
#endif
CUB PFRA_SUB_Rx[]			= "R｢cFcod";
/* ｽｸﾗﾝﾌﾞﾙ */
CUB	PFRA_Cipher_Tx[]		= "CHIFFR.";
CUB	PFRA_Cipher_Rx[]		= "CHIFFR.";

/* 短縮ダイヤルリスト */
CUB	PFRA_TeleDirectory[] 	= "** R｢pert. Num. Abr｢g｢e **";
CUB	PFRA_No[]				= "Nﾏ.";
#if ( PRO_MAKER == FX )
CUB	PFRA_RemoteLocation[]	= "     Name\000      ";	/* 6/28 FX.ENG */
CUB	PFRA_TeleNumber[] 		= "  Telephone No.   ";		/* 6/28 FX.ENG */
CUB	PFRA_GroupNumber[] 		= "Group No.       ";		/* 6/28 FX.ENG */
#else
CUB	PFRA_RemoteLocation[]	= "  Emplacement\000  ";
CUB	PFRA_TeleNumber[] 		= "  Num｢ro d'appel\000 ";
CUB	PFRA_GroupNumber[] 		= "Num｢ro de Group ";	/* ANZUのみ *//*正規のﾜｰﾃﾞｨﾝｸﾞはこれ" Num｢ro de Group"1996/12/28 T.Isobe*/
#endif
CUB	PFRA_Cost[]				= "        ";	/* POPLAR_Hのみ */

/* 属性リスト */
CUB PFRA_AttributeList[]	= "Liste Attribut";
CUB PFRA_Attribute[]		= "Attr.";

/* ワンタッチダイヤルリスト */
CUB	PFRA_OneDirectory[] 	= "** R｢pert. Une-Touches ** ";

/* プログラムリスト */
CUB	PFRA_DelyTime[] 		= "  D｢but\000";
CUB	PFRA_Option[] 			= " Option\000";
CUB	PFRA_NotTime[] 			= "--:--";

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/26 By M.Kuwahara */
CUB	PFRA_PRG_Onetouch[]		= "ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ﾘｽﾄ        ";
CUB	PFRA_PRG_Speed[]		= "短縮ﾀﾞｲﾔﾙ ﾘｽﾄ         ";
CUB	PFRA_PRG_Program[]		= "ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ﾘｽﾄ      ";
CUB	PFRA_PRG_SecureBox[]	= "親展BOXﾘｽﾄ            ";
CUB	PFRA_PRG_ComReserve[]	= "通信予約ﾘｽﾄ           ";
CUB	PFRA_PRG_Journal[]		= "通信管理ﾚﾎﾟｰﾄ         ";
CUB	PFRA_PRG_Group[]		= "ｸﾞﾙｰﾌﾟ ﾘｽﾄ            ";
CUB	PFRA_PRG_Setting[]		= "機器設定ﾘｽﾄ           ";
CUB	PFRA_PRG_Message[]		= "ﾒｯｾｰｼﾞ ﾘｽﾄ            ";
CUB	PFRA_PRG_CostBase[]		= "料金表                ";
CUB	PFRA_PRG_DepartCode[]	= "部門管理ﾘｽﾄ           ";
CUB	PFRA_PRG_BatchBox[]		= "一括送信BOXﾘｽﾄ        ";
CUB	PFRA_PRG_BatchDoc[]		= "一括送信原稿ﾘｽﾄ       ";
CUB	PFRA_PRG_F_CodeBox[]	= "FｺｰﾄﾞBOXﾘｽﾄ           ";
CUB	PFRA_PRG_F_CodeDoc[]	= "FｺｰﾄﾞBOX蓄積原稿ﾘｽﾄ   ";
CUB	PFRA_PRG_BlockJunk[]	= "ﾀﾞｲﾚｸﾄﾒｰﾙ防止ﾀﾞｲﾔﾙ ﾘｽﾄ";
CUB	PFRA_PRG_ND_Dial[]		= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲﾀﾞｲﾔﾙ ﾘｽﾄ";
CUB	PFRA_PRG_ND_Journal[]	= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ履歴     ";
CUB	PFRA_PRG_Warp[]			= "FAXﾜｰﾌﾟ ﾘｽﾄ           ";
 #if defined(SAKAKI) && defined(JP0) /* 2002/08/26 By M.Maeda */
CUB	PFRA_PRG_JournalTx[]	= "通信管理ﾚﾎﾟｰﾄ(送信)   ";
CUB	PFRA_PRG_JournalRx[]	= "通信管理ﾚﾎﾟｰﾄ(受信)   ";
 #endif
CUB PFRA_ListName[]			= "ﾘｽﾄ名\0   ";
CUB PFRA_CommReserved[]		= "通信予約";
CUB PFRA_List[]				= "ﾘｽﾄ\0";
CUB PFRA_DocStore[]			= "原稿蓄積";
#endif

/* グループリスト */
CUB	PFRA_GroupDirectory[] 	= "** R｢pert. Groupes **";
#if ( PRO_MAKER == FX )
CUB	PFRA_Location[]			= "  Name\000  ";
#else
CUB	PFRA_Location[]			= " Emplac.\000";
#endif

/* 機器設定リスト */
CUB	PFRA_MachineSettings[] 	= "* Paramｪtres Machine *";
#if ( PRO_MAKER == FX )
CUB	PFRA_SubscriberID[] 	= "SendHeader";
#else
CUB	PFRA_SubscriberID[] 	= "ID Abonn｢\000";
#endif
CUB	PFRA_SubscriberKanaID[]	= "Kana ID         ";
#if ( PRO_MAKER == FX )
CUB	PFRA_SubscriberNb[] 	= "Local ID    ";	/* 10/18 FX.ENG */
CUB	PFRA_JournalAutoPrt[] 	= "Auto Activity Rep";
CUB	PFRA_SecureDocHold[] 	= "Rcv MB Hold Time";
#else
CUB	PFRA_SubscriberNb[] 	= "Num. Appel\000 ";
CUB	PFRA_JournalAutoPrt[] 	= "Imp. Journal Auto"; /* "Imp. Auto Journal"->"Imp. Journal Auto" BY H.H 1997/03/14 */
CUB	PFRA_SecureDocHold[] 	= "Sauvegarde SMail";
#endif
CUB	PFRA_PhoneType[]		= "Type T｢l.\000";
#if ( PRO_MAKER == FX )
CUB	PFRA_ConfReport[]		= "Monitor Rep";
CUB	PFRA_ScannerWidth[]		= "Scan Width   ";	/* 6/28 FX.ENG */
CUB	PFRA_PrimaryMode[]		= "Resolution\000   ";	/* 6/28 FX.ENG */
CUB	PFRA_Contrast[]			= "Density\000      ";	/*11/01 FX.ENG */
CUB	PFRA_DialingPause[]		= "PauseDuration";
#else
CUB	PFRA_ConfReport[]		= "Rapport\000   ";
CUB	PFRA_ScannerWidth[]		= "Larg. analyse";
CUB	PFRA_PrimaryMode[]		= "D｢fin. init.\000 ";
CUB	PFRA_Contrast[]			= "Contraste\000    ";
CUB	PFRA_DialingPause[]		= "Pause Appel\000 ";
#endif
CUB	PFRA_RinggingTimes[]	= "Nbre Sonneries";
#if ( PRO_MAKER == FX )
CUB	PFRA_ReductionRate[]	= "Reduction %   ";	/* 6/28 FX.ENG */
#else
CUB	PFRA_ReductionRate[]	= "Taux R｢duction";
#endif
CUB	PFRA_EcmMode[]			= "Mode ECM";
CUB	PFRA_CopyProtect[]		= "Interd copie";
CUB	PFRA_RemoteDiagnostic[]	= "Mode Maintenance\000";
CUB	PFRA_RedialTimes[]		= "Prog. Rappels\000   "; /* "Rappels initial"->"Prog. Rappels" BY H.H 1997/03/14 */
CUB	PFRA_Holdmelody[]		= "Mus. attente";
CUB	PFRA_Passcode[]			= "Code acc";
CUB	PFRA_CloseNetwork[]		= "R｢s. ferm｢\000    ";
CUB	PFRA_SilentOperation[]	= "Mode Silen.\000    ";	/* JPN以外 */
#if ( PRO_MAKER == FX )
CUB	PFRA_SecurityTx[]		= "Secure Send      ";	/* 6/28 FX.ENG */
CUB	PFRA_BlockjunkFax[]		= "No Junk Fax\000    ";
#else
CUB	PFRA_SecurityTx[]		= "Em. S｢curit｢\000    ";
CUB	PFRA_BlockjunkFax[]		= "Tri appels\000     ";
#endif
CUB	PFRA_RecieveMode[]		= "Mode R｢cept.";
#if ( PRO_MAKER == FX )
CUB	PFRA_PageCompound[]		= "Combine Pages    ";	/* 9/17 FX.ENG */
#else
CUB	PFRA_PageCompound[]		= "R｢c. 1/2 Page\000   "; /* "Page Compac."->"R｢c. 1/2Page" BY H.H 1997/03/14 */
#endif
CUB	PFRA_SortingCopy[]		= "Tri copies\000 ";		/* POPLAR_Lのみ */
CUB	PFRA_Rs232c[]			= "Param. RS232C    ";
CUB	PFRA_Stamp[]			= "Tampon\000";
CUB	PFRA_MemoryTx[]			= "Em. M｢moire\000   ";
CUB	PFRA_RelayedRelayTx[]	= "Relais Relay      ";
CUB	PFRA_DialIn[]			= "DialinNo  Fax/Tel";	/* (JPN) */
CUB	PFRA_BellTime[]			= "Times  ";			/* (JPN) */
CUB	PFRA_RingMastr[]		= "DRD              ";
CUB	PFRA_CopyReduction[]	= "R｢duce Copie     ";
CUB	PFRA_PaperSize[]		= "Format Pap.      ";	/* ANZUのみ */
CUB PFRA_PC_PaperManual[]	= "Format Pap.Imp.PC";	/* ANZUのみ *//* PCﾌﾟﾘﾝﾄ ﾃｻﾞｼﾖｳｼ bythonda1998/02/24 */
CUB	PFRA_PaperType[]		= "Type Papier    ";	/* SAKAKIのみ */
CUB	PFRA_ToneLine[] 		= "Ton  ";
#if ( PRO_MAKER == FX )
CUB	PFRA_Pps10[] 			= "10pps";	/* 6/28 FX.ENG */
CUB	PFRA_Pps20[] 			= "20pps";	/* 6/28 FX.ENG */
#else
CUB	PFRA_Pps10[] 			= "Impul";
CUB	PFRA_Pps20[] 			= "Impul";
#endif
CUB	PFRA_TxConf[]			= "TCR\000    ";
CUB	PFRA_RxConf[]			= "RCR\000     ";
CUB	PFRA_A4[] 				= "A4";
CUB	PFRA_B4[] 				= "B4";
CUB	PFRA_A3[] 				= "A3";
CUB	PFRA_F4[] 				= "F4";
#if (PRO_PITNEYBOWES == ENABLE)
CUB PFRA_LETTER[]			= "LTR";	/* ＰＢ仕様の為追加 By S.Fukui Aug. 25,1998 */
CUB PFRA_LEDGER[]			= "LD";		/* ＰＢ仕様の為追加 By S.Fukui Aug. 25,1998 */
#endif
#if ( PRO_MAKER == FX )
CUB	PFRA_Dark[] 			= "Darker";
CUB	PFRA_NormalDark[] 		= "Normal";
CUB	PFRA_Light[] 			= "Lighter";
#else
CUB	PFRA_Dark[] 			= "Fonc｢\000";
CUB	PFRA_NormalDark[] 		= "Normal";
CUB	PFRA_Light[] 			= "Clair\000 ";
#endif
CUB	PFRA_MinuteMark[] 		= "Min.\000  ";
CUB	PFRA_SecondMark[] 		= "Sec.";
#if ( PRO_MAKER == FX )
CUB	PFRA_Try[] 				= "Times";
#else
CUB	PFRA_Try[] 				= "Sonn.";
#endif
CUB	PFRA_Attemps[] 			= "Rappels\000";
CUB	PFRA_On[] 				= "Oui";
CUB	PFRA_Off[] 				= "Non";
CUB	PFRA_Mode1[]			= "Mode1";
CUB	PFRA_Mode2[]			= "Mode2";
CUB	PFRA_Mode3[]			= "Mode3";
CUB	PFRA_P100[] 			= "100%";
CUB	PFRA_P97[] 				= "97%";
CUB	PFRA_P91[] 				= "91%";
CUB	PFRA_P81[] 				= "81%";
CUB	PFRA_P75[] 				= "75%";
#if ( PRO_MAKER == FX )
CUB	PFRA_ThValue00mm[] 		= "Thrshld   00 mm";	/* 6/28 FX.ENG */
CUB	PFRA_TelFax[] 			= "Tel/Fax\000 ";
CUB	PFRA_Tel[] 				= "Tel\000";
CUB	PFRA_Fax[] 				= "Fax\000";
CUB	PFRA_AnsFax[] 			= "Ans/Fax\000";	/* 6/28 FX.ENG */
#else
CUB	PFRA_ThValue00mm[] 		= "Marge     00 mm";
CUB	PFRA_TelFax[] 			= "T｢l/Fax\000 ";
CUB	PFRA_Tel[] 				= "T｢l.";
CUB	PFRA_Fax[] 				= "Fax\000";
CUB	PFRA_AnsFax[] 			= "R｢p/Fax\000";
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec K.W.Q 2003/11/28 */
CUB	PFRA_DialInRx[]			= "DialinNo\0";
#endif

CUB	PFRA_FaxTel[]			= "Fax/T｢l\000 "; /**	追加 For ANZU By H.Hirao 1996/05/21	*/
CUB	PFRA_Bps300[] 			= "300";
CUB	PFRA_Bps600[] 			= "600";
CUB	PFRA_Bps1200[] 			= "1200";
CUB	PFRA_Bps2400[] 			= "2400";
CUB	PFRA_Bps4800[] 			= "4800";
CUB	PFRA_Bps9600[] 			= "9600";
CUB	PFRA_Bps19200[] 		= "19200";
CUB	PFRA_BpsVariable[] 		= "Variable";		/** 追加 For POPLA By M.Kuwahara 1997/03/05 */
CUB	PFRA_None[] 			= "Sans";
CUB	PFRA_Odd[] 				= "Imp";			/* "ODD"→"Imp"   by M.HARADA 95.09.04 */
CUB	PFRA_Even[] 			= "Pair";			/* "EVEN"→"Pair" by M.HARADA 95.09.04 */
CUB	PFRA_S1bit[] 			= "1bit";
CUB	PFRA_S2bit[] 			= "2bit";
CUB	PFRA_P7bit[] 			= "7bit";
CUB	PFRA_P8bit[] 			= "8bit";
CUB	PFRA_Days[] 			= "Jour";
CUB	PFRA_Auto[] 			= "Auto\000";
CUB	PFRA_Pattern[]			= "Mire   :";	/* (USA) *//* "Type   :"->"Mire   :" BY H.H 1997/03/14 */
CUB	PFRA_Letter[]			= "Letter\0";
CUB	PFRA_Legal[]			= "Legal\0";
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */	/* '95.07/20 By K.Watanabe */
CUB	PFRA_RxAlarm[]			= "Alarme sonore";
CUB	PFRA_MercuryPause[]		= "Prefix Pause "; /* Add By H.H 1996/08/28 Mercury Pause -> Prefix Pause */
CUB PFRA_MercuryNumber[]	= "Dial Prefix Number";/* Added by SMuratec C.P 2004/07/08 for prefix */
#endif
#if ( PRO_MAKER == FX )
CUB	PFRA_MesageTrans[]		= "Annotation      ";
#else
CUB	PFRA_MesageTrans[]		= "Page de garde\000  "; /* "Message Em."->"Page de garde" BY H.H 1997/03/14 */
#endif
CUB	PFRA_RemoteSecurityRx[]	= "R｢c. Prot｢g｢e ";
CUB	PFRA_NormalPaper[]		= "Normal\000   ";	/* SAKAKIのみ */
CUB PFRA_ThermalPaper[]		= "Thermal\000  ";	/* SAKAKIのみ */
CUB	PFRA_DepartmentProtect[]= "Depart. Prot｢g｢\000  "; 	/* 追加 For ANZU By H.Hirao Feb 29,1996 */
CUB	PFRA_Department[]		= "Depart.\000  ";				/* 追加 For ANZU By H.Hirao Feb 29,1996 */
CUB	PFRA_PINAccessMode[]	= "Mode PIN\000      ";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#if defined(USA)
CUB	PFRA_DayLightSaving[]	= "Heure d'｢t｢\000   ";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#endif
CUB	PFRA_OperationProtect[]	= "Utilisat. Prot｢g｢e";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#if (PRO_REMOTE_RX == ENABLE)
CUB	PFRA_RemoteReceive[]	= "Remote Transfer\000  ";	/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	PFRA_OnHookReceive[]	= "Onhook Transfer\000  ";	/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif


/* PRO_MULTI_LINE */
/* 基本的に下記ワーディングは
** 		見出し用：半角16文字
** 		内容用  ：半角 8文字
** とします。
** by O.Kimoto 1997/07/10
*/
						/*	   12345678901234567890 */
/* CUB PFRA_MultiPhoneType[]	= "Type T｢l.  ( )";	@@ Change */
CUB PFRA_MultiTxRxType[]	= "Type Em/R｢c.\000   ";	/** Change */
CUB PFRA_TxRx[]				= "Em/R.\000  ";			/** Change */
CUB PFRA_Tx[]				= "Em.\000    ";			/** Change */
CUB PFRA_Rx[]				= "R.\000     ";			/** Change */
CUB PFRA_MultiLineType[]	= "Type Ligne\000     ";	/** Change */ /* "Type ligne( )"->"Type Ligne( )" BY H.H 1997/03/14 */
CUB PFRA_PstnLine[]			= "PSTN\000   ";			/** No Change */
CUB PFRA_PbxLine[]			= "PBX\000    ";			/** Change */
CUB PFRA_PstnAccessNumber[]	= "Num. Accｪs   :\000 ";	/** Change *//* .とAの間を詰めました 1998/01/09 Y.Matsukuma */
CUB PFRA_LineNumber[]		= "Num. Ligne :\000   ";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題（終端をNULLで判断していない）があるので、ﾜｰﾃﾞｨﾝｸﾞを最大11ﾊﾞｲﾄ・ｺﾛﾝの位置固定(日本語参照)にすること *//** Change */ /* "Ligne No.:"->"Num｢roLigne:" BY H.H 1997/03/14 */
														/* "Num. Ligne:\000    " -> "Num. Ligne :\000    " 1998/03/03 By M.Kuwahara */
/** CUB	PFRA_SubscriberKanaID[]	= "発信元名(ｶﾅID)  "; */
/** CUB	PFRA_PhoneType[]		= "通信回線\000 "; */

#if (PRO_MULTI_LINE == ENABLE)	/*  By O.Kimoto 1997/01/06 */
CUB	PFRA_AddErrorMessage[4][31] = {
					/* 123456789012345678901234567890 */
					  "V｢rif. paramｪtres ｢m. et r｢c. ",	/** D.0.10 */
					  "V｢rif. attr. une-T/num. abr｢g.",	/** D.0.11 */
					  "V｢rif. comb. type ligne/num.  ",	/** D.0.12 */
					  "V｢rif. comb. type ligne/num.  "	/** D.0.13 */
					  };
#endif

/* 記録紙サイズ */
CUB	PFRA_Paper_A5[]			= "A5_P\0  ";
 #if defined(USA)
CUB	PFRA_Paper_Letter[]		= "Letter\0";
 #else
CUB	PFRA_Paper_Letter[]		= "Ltr_P\0 ";
 #endif
 #if defined(USA)
CUB	PFRA_Paper_A4[]			= "A4_P\0  ";
 #else
CUB	PFRA_Paper_A4[]			= "A4\0    ";
 #endif
 #if defined(USA) || defined(TWN) /* 1998/01/09 Y.Matsukuma */
CUB	PFRA_Paper_Legal[]		= "Legal\0 ";
 #else
CUB	PFRA_Paper_Legal[]		= "Legal_P";
 #endif
CUB	PFRA_Paper_B5R[]		= "B5R_P\0 ";
CUB	PFRA_Paper_B4[]			= "B4_P\0  ";
CUB	PFRA_Paper_A3[]			= "A3_P\0  ";
CUB	PFRA_Paper_A4R[]		= "A4R_P\0 ";
CUB	PFRA_Paper_LetterR[]	= "LtrR_P\0";
 #if defined(TWN) || defined(AUS)	/* 1998/01/08 Y.Matsukuma */
CUB	PFRA_Paper_F4[]			= "F4\0    ";
 #else
CUB	PFRA_Paper_F4[]			= "F4_P\0  ";
 #endif
CUB	PFRA_Paper_A5R[]		= "A5R_P\0 ";
CUB	PFRA_Paper_Postcard[]	= "Post_P\0";
CUB	PFRA_Paper_LD[]			= "Ld_P\0  ";
CUB	PFRA_Paper_GLetterR[]	= "GLtrR_P";
CUB	PFRA_Paper_ExecutiveR[]	= "ExeR_P\0";
CUB	PFRA_Paper_InvoiceR[]	= "InvR_P\0";
CUB	PFRA_Paper_GLegal[]		= "GLegl_P";
CUB	PFRA_Paper_GLetter[]	= "GLtr_P\0";
CUB	PFRA_Paper_Card[]		= "Card_P\0";
CUB	PFRA_Paper_Executive[]	= "Exe_P\0 ";
CUB	PFRA_Paper_B5[]			= "B5_P\0  ";
CUB	PFRA_Paper_C5[]			= "C5_P\0  ";
CUB	PFRA_Paper_HalfLetter[]	= "HLtr_P\0";
CUB	PFRA_Paper_Invoice[]	= "Inv_P\0 ";
CUB	PFRA_Paper_B6[]			= "B6_P\0  ";
CUB	PFRA_Paper_DL[]			= "DL_P\0  ";
CUB	PFRA_Paper_CM10[]		= "CM10_P\0";
CUB	PFRA_Paper_A6[]			= "A6_P\0  ";
CUB	PFRA_Paper_Monarch[]	= "Mnc_P\0 ";
CUB	PFRA_Paper_35[]			= "3x5_P\0 ";
CUB	PFRA_Paper_User[]		= "User_P\0";

/* 記録紙サイズ POPLAR用 */
CUB	PFRA_PaperSize_A5[]			= "A5\0    ";
CUB	PFRA_PaperSize_Letter[]		= "Letter\0";
CUB	PFRA_PaperSize_A4[]			= "A4\0    ";
CUB	PFRA_PaperSize_Legal[]		= "Legal\0 ";
CUB	PFRA_PaperSize_B5R[]		= "B5R\0   ";
CUB	PFRA_PaperSize_B4[]			= "B4\0    ";
CUB	PFRA_PaperSize_A3[]			= "A3\0    ";
CUB	PFRA_PaperSize_A4R[]		= "A4R\0   ";
CUB	PFRA_PaperSize_LetterR[]	= "LtrR\0  ";
CUB	PFRA_PaperSize_F4[]			= "F4\0    ";
CUB	PFRA_PaperSize_A5R[]		= "A5R\0   ";
CUB	PFRA_PaperSize_Postcard[] 	= "Post\0  ";
CUB	PFRA_PaperSize_LD[]			= "Ld\0    ";
CUB	PFRA_PaperSize_GLetterR[]	= "GLtrR\0 ";
CUB	PFRA_PaperSize_ExecutiveR[]	= "ExeR\0  ";
/*  #if (PRO_KEYPANEL == PANEL_POPLAR_B)  *//* modified by honda 1997/11/14 */
/*   #if defined(USA) || defined(GBR)  */
CUB	PFRA_PaperSize_HalfLetterR[]= "HLtrR\0 ";  /* added by honda 1997/10/04 */
/*   #else  */
/*  CUB	PFRA_PaperSize_InvoiceR[]	= "InvR\0  ";  */
/*   #endif  */
/*  #else  */
/*  CUB	PFRA_PaperSize_InvoiceR[]	= "InvR\0  ";  */
/*  #endif  */
CUB	PFRA_PaperSize_GLegal[]		= "GLegl\0 ";
CUB	PFRA_PaperSize_GLetter[]	= "GLtr\0  ";
CUB	PFRA_PaperSize_Card[]		= "Card\0  ";
CUB	PFRA_PaperSize_Executive[]	= "Exe\0   ";
CUB	PFRA_PaperSize_B5[]			= "B5\0    ";
CUB	PFRA_PaperSize_C5[]			= "C5\0    ";
CUB	PFRA_PaperSize_HalfLetter[]	= "HLtr\0  ";
CUB	PFRA_PaperSize_Invoice[]	= "Inv\0   ";
CUB	PFRA_PaperSize_B6[]			= "B6\0    ";
CUB	PFRA_PaperSize_DL[]			= "DL\0    ";
CUB	PFRA_PaperSize_CM10[]		= "CM10\0  ";
CUB	PFRA_PaperSize_A6[]			= "A6\0    ";
CUB	PFRA_PaperSize_Monarch[]	= "Mnc\0   ";
CUB	PFRA_PaperSize_35[]			= "3x5\0   ";
CUB	PFRA_PaperSize_User[]		= "User\0  ";

/* メモリスイッチ */
#if ( PRO_MAKER == FX )
CUB	PFRA_Machine_P[] 		= "Parameter    ";
#else
CUB	PFRA_Machine_P[] 		= "Param Machine";
#endif
CUB	PFRA_Memory_S[] 		= "Switch M｢mo.\000";
CUB	PFRA_Uniq_S[]			= "Switch uniq. ";			/* 追加 For ANZU By H.Hirao Mar.28.1996 */
CUB	PFRA_BitNumber[] 		= "7654 3210";
CUB	PFRA_Default[] 			= " D｢faut  ";
CUB	PFRA_AutoSet[] 			= "Param｢tr.";

/* POPLA追加 -- メモリスイッチの追加 */
CUB PFRA_MainteSwitch[]		= "Switch maint.";  /* <- Mnt Switch */

/* キノウリスト */
CUB	PFRA_ProgramList[]		= "Liste Programm. ";

/* 通信予約リスト */
CUB	PFRA_ComReservedList[] 	= "** Liste Commandes **";

/* 親展者登録リスト */
CUB	PFRA_SecureMailBList[]	= "** Liste SecureMail ** ";
#if ( PRO_MAKER == FX )
CUB	PFRA_UserName[] 		= "  Name    ";	/* 6/28 FX.ENG */
#else
CUB	PFRA_UserName[] 		= "Utilisat.\000";
#endif
CUB	PFRA_Box[] 				= "Box";

/* カバーページプリント */
CUB	PFRA_CoverPageMes[] 	= "** Formulaire Fax **";	/* 右端 - 2ﾊﾞｲﾄの後、ｾﾝﾀﾘﾝｸﾞ */

/* 親展受信通知 */
CUB	PFRA_SecureMailNotice[] = " SecureMail  ";

/* 親展原稿消去通知 */
CUB	PFRA_ErasedDocuments[] 	= "Documents effac｢s ";

/* 代行受信消去通知 */
CUB	PFRA_ErasedDocumemts[] 	= " Documents effac｢s  ";

/* 通信予約消去通知 */
CUB	PFRA_ErasedCommands[] 	= "Documents effac｢s";
#if ( PRO_MAKER == FX )
CUB	PFRA_MemHoldDate[]		= "Print mailbox by   ";
#else
CUB	PFRA_MemHoldDate[]		= "(Date sauvegarde)\000 ";
#endif

/* チェックメッセージ */
CUB	PFRA_CheckMessage[] 	= " Mess.Alarme ";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PFRA_MemoryOver[] 		= "M｢m. Pleine";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PFRA_PcMemoryOver[]		= "  D｢p.M｢m.PC  ";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PFRA_ErrorPages[] 		= "< Pages Err.>:";

/* Ｔ３０モニタ */
CUB	PFRA_T30Monitor[]		= "** Moniteur T30 **";
CUB	PFRA_TxFrame[]			= "TrameEm";
CUB	PFRA_RxFrame[]			= "TrameRx";
CUB	PFRA_Datalong[]			= "Donn｢es";
CUB	PFRA_Rs144[]			= "144";
CUB	PFRA_Rs120[]			= "120";
CUB	PFRA_Rs96[]				= " 96";
CUB	PFRA_Rs72[]				= " 72";
CUB	PFRA_Rs48[]				= " 48";
CUB	PFRA_Rs24[]				= " 24";
CUB	PFRA_V17[]				= "V17";
CUB	PFRA_V33[]				= "V33";
CUB	PFRA_V29[]				= "V29";
CUB	PFRA_V27[]				= "V27";
CUB	PFRA_MH[]				= " MH";
CUB	PFRA_MR[]				= " MR";
CUB	PFRA_MMR[]				= "MMR";
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
CUB	PFRA_JBG[]				= "JBG";
#endif
CUB	PFRA_A5[]				= "A5";
CUB	PFRA_A6[]				= "A6";
CUB	PFRA_Wait20[]			= "20";
CUB	PFRA_Wait40[]			= "40";
CUB	PFRA_Wait10[]			= "10";
CUB	PFRA_Wait5[]			= " 5";
CUB	PFRA_Wait0[]			= " 0";
CUB	PFRA_ModeNR[]			= "N";
CUB	PFRA_ModeFN[]			= "F";
CUB	PFRA_ModeSF[]			= "S";
CUB	PFRA_ModeHF[]			= "H";

CUB	PFRA_Main[]				= "MAN";
CUB	PFRA_Reset[]			= "Res";
CUB	PFRA_Error[]			= "Err";
CUB	PFRA_Now[]				= "Now";
CUB	PFRA_DpramTx[]			= "Tx";
CUB	PFRA_DpramRx[]			= "Rx";

/* コウジョウ ファンクション リスト */
CUB	PFRA_FunctionList[]		= "Fonctions Usine     ";
CUB	PFRA_LedTest[]			= "Test LED            ";
CUB	PFRA_LcdTest[]			= "Test Afficheur      ";
CUB	PFRA_Pane1keytest[]		= "Test Clavier        ";
CUB	PFRA_Rs232cTest[]		= "Test RS232C         ";
CUB	PFRA_SramCheck[]		= "Test SRAM           ";
CUB	PFRA_DramCheck[]		= "Test DRAM           ";
CUB	PFRA_RTCTest[]			= "Test RTC            ";

/* オンラインモニタ */
#if ( PRO_CLASS1 == ENABLE )
CUB	PFRA_OnLineMonitor[]	= " < Ecoute Ligne >  ";
CUB	PFRA_OnLineTx[]			= "TX";
CUB	PFRA_OnLineRx[]			= "RX";
CUB	PFRA_OnLineData[]		= "Data";
CUB	PFRA_Speed[]			= "Vit. ";
CUB	PFRA_Command[]			= "Cmd";
CUB	PFRA_Response[]			= "R｢p";
CUB	PFRA_Abort[]			= "Abd";
#endif

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
CUB PFRA_F_CodeBox_List[]	= "** ListBoｬteFCode **";
CUB PFRA_BoxName[]			= "NomBoｬte\0";
CUB PFRA_SubAddress[]		= " Adresse\0     ";
CUB PFRA_CommPasscode[]		= "Mot.de Passe\0.    ";
CUB PFRA_Kind[]				= "Type\0";
CUB PFRA_NoticeBoard[]		= "Bull.\0 ";
CUB PFRA_RecvProtect[]		= "R｢c.Prot\0 ";
CUB PFRA_Replace[]			= "Ecraser";
CUB PFRA_RxPrint[]			= "Imp.R｢c.\0 ";
CUB PFRA_TransErase[]		= "Eff.Doc.Rｪleve\0  ";

#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
CUB PFRA_RelayName[] 		= "配信先";
CUB PFRA_PutSubscriber[] 	= "発信元";
CUB PFRA_Avail[]			= "外付け";
CUB	PFRA_NoTTI[]			= "付けない";
CUB	PFRA_SUB_Relay[]		= "Fﾁｭｳｹｲ ";	/* 1998/09/25 By M.Kuwahara */
CUB	PFRA_SUB_Secure[]		= "Fｼﾝﾃﾝ  ";	/* 1998/09/28 By M.Kuwahara */
#endif

#if (PRO_FCODE_KIND_DISPLAY == ENABLE)
CUB	PFRA_SUB_Bulletin[]		= "Fｹｲｼﾞ  ";	/* 1998/09/28 By M.Kuwahara */
#endif

/* サブアドレス原稿消去通知 */
CUB PFRA_Del_F_CodeBoxDoc_Notice[]	= "Doc.Boｬte F-Code effac｢s ";
CUB PFRA_BoxLocation[]		= "Destinat";
CUB PFRA_ThisBoxErased[]	= "Ces doc.pour boｬte FCODE sont effac｢s ";

/* サブアドレスＢＯＸ蓄積原稿リスト */
CUB PFRA_DocumentsNo[]		= " Fich.# ";
CUB PFRA_F_CodeDoc_List[]	= "** Liste documents FCODE ** ";

/* サブアドレス受信通知 */
CUB PFRA_F_CodeBoxRsv_Notice[]	= "Journ.Boｬte FCODE";
CUB PFRA_F_CodeReci[]		= "R｢c.Boｬte FCODE   \0         ";
CUB PFRA_F_ReciDocMemory[]	= "Imp.cont.Boｬte avant ";
#endif

/* ダイレクトメール防止ダイヤルリスト */
CUB	PFRA_BlockJunkList[]	= " **  Liste fax refus｢s  ** ";
CUB	PFRA_TelNum[]			= "Num. appel\0";

/* サービスレポート */
CUB	PFRA_ServiceReport[]	= "** Rapport Serv. ** ";

/* ポーリング原稿消去通知 */
#if (PRO_OKI == ENABLE)
CUB	PFRA_ErasePollDoc[]		= " Doc. Relｪve Effac｢s  ";	/* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#else
CUB	PFRA_ErasePollDoc[]		= " Doc. Polling Effac｢s ";
#endif

/* 一括送信原稿リスト */
CUB PFRA_BatchTxDocList[]	= "** Doc. Envoi group｢ **       ";

/* 一括送信ＢＯＸリスト */
CUB PFRA_BatchTxBoxList[]	= "** Liste Envoi group｢ **        ";

CUB PFRA_Batch[]			= "Boｬte";			/** Change */
CUB PFRA_BoxNo[]			= "Boｬte No.\000 ";		/** Change */

/* 暗号化受信通知リスト */
CUB PFRA_CipherReceiveNotice[]	= "Rapp.R｢c.chiff.     ";
CUB PFRA_ReceiveNo[]		= "Num.R｢c..\0";
CUB PFRA_KeyClue[]			= "Abr｢vTch    ";
CUB PFRA_KeyWordClue[]		= "Abr｢vTch";

/* キーリスト、キーブックリスト */
CUB PFRA_KeyBookList[]		= "** R｢p.Touch.**";	/* 98/01/12 By M.Kuwahara */
CUB PFRA_KeyWordList[]		= "  ** List.Tch.**   ";
CUB PFRA_KeyName[]			= "  Nom.Tch.  ";
CUB PFRA_Key[]				= "Touche";

/* 暗号化受信消去通知 */
CUB	PFRA_EraseScrambleRxDoc[]	= "Eff.Document chiffr.  ";

/* 消耗品発注票 */
#if defined(JPN)
CUB PFRA_ConsumerOrderSheet[]	= "ｼｮｳﾓｳﾋﾝ ﾊｯﾁｭｳﾋｮｳ\0          ";
CUB PFRA_ToOrder[]				= "ﾊｯﾁｭｳｻｷ";
CUB PFRA_FromOrder[]			= "ﾊｯﾁｭｳﾓﾄ";
CUB PFRA_CustomerCode[]			= "ﾄｸｲｻｷｺｰﾄﾞ\0     ";		/* JPNは最大10byte */
CUB PFRA_DistributorName[]		= "ｼｬﾒｲ\0             ";	/* JPNは最大10byte */
CUB PFRA_CustomerName[]			= "ｼｬﾒｲ\0             ";	/* JPNは最大10byte */
CUB PFRA_Section[]				= "ﾌﾞｶﾒｲ\0           ";		/* JPNは最大10byte */
CUB PFRA_ChargeName[]			= "ｺﾞﾀﾝﾄｳｼｬﾒｲ";
CUB PFRA_ModelName[]			= "ﾓﾃﾞﾙﾒｲ";
CUB PFRA_OrderItem[]			= "ﾊｯﾁｭｳﾋﾝﾓｸ\0";
CUB PFRA_TonerOrder1[]			= "ﾄﾅｰ   x 1\0       ";		/* 注）ﾄﾅｰ =5byte, x 1の位置固定（日本語参照） */
CUB PFRA_DrumOrder1[]			= "ﾄﾞﾗﾑ  x 1\0       ";		/* 注）ﾄﾞﾗﾑ=5byte, x 1の位置固定（日本語参照） */
CUB PFRA_SeirialNumber[]		= "ｼﾘｱﾙNo.\0            ";	/* JPNは最大10byte */
CUB PFRA_InstallDate[]			= "ｾｯﾁﾋﾞ\0           ";		/* JPNは最大10byte */
CUB PFRA_BlockLetters[]			= "               ";		/* JPNは未使用 */
CUB PFRA_Remarks[]				= "ﾋﾞｺｳ   ";
CUB PFRA_OrderTonerChange[]		= "ﾄﾅｰﾉｺｳｶﾝｶﾞ ﾋﾂﾖｳﾆﾅﾘﾏｼﾀ｡          ";
CUB PFRA_OrderTonerDrumChange[]	= "ﾄﾅｰ/ﾄﾞﾗﾑﾉｺｳｶﾝｶﾞ ﾋﾂﾖｳﾆﾅﾘﾏｼﾀ｡             ";
CUB PFRA_OrderSheet[]			= "ｵﾃｽｳﾃﾞｽｶﾞ､ｺﾉﾖｳｼｦﾂｶｯﾃ､ｶｷﾍFAXﾃﾞｺﾞﾁｭｳﾓﾝｸﾀﾞｻｲ｡                  ";
#elif defined(US1)			/* orderbythonda1998/11/11 */
CUB PFRA_ConsumerOrderSheet[]	= "PITNEY BOWES OFFICE SYSTEMS 4100";
CUB PFRA_ConsumerOrderSheet2[]	= "SUPPLIES ORDER FORM";
CUB PFRA_ToOrder[]				= "To:\0   ";				/* 海外は最大6文字 */
CUB PFRA_FromOrder[]			= "From:\0 ";				/* 海外は最大6文字 */
CUB PFRA_CustomerCode[]			= "Customer's Code";
CUB PFRA_DistributorName[]		= "Distributor's Name";
CUB PFRA_CustomerName[]			= "Customer's Name\0  ";
CUB PFRA_Section[]				= "Address(Ship to:)";
CUB PFRA_ChargeName[]			= "Signature ";
CUB PFRA_ModelName[]			= "Model ";
CUB PFRA_OrderItem[]			= "Item Needed: ";
CUB PFRA_TonerOrder1[]			= "Toner Cartridge x       PCS";		/* 注）Toner=5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PFRA_DrumOrder1[]			= "Drum Unit       x       PCS";		/* 注）Drum =5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PFRA_SeirialNumber[]		= "Serial No.";
CUB PFRA_InstallDate[]			= "Installation Date";
CUB PFRA_BlockLetters[]			= "Print Name :";
CUB PFRA_Remarks[]				= "Customer Account No. & Ship to Address";
CUB PFRA_OrderTonerChange[]		= "Replace toner with a new one.   ";	/* JPNのみ */
CUB PFRA_OrderTonerDrumChange[]	= "Your machine's display indicates that either the Toner Cartridge or Drum Unit";
CUB PFRA_OrderTonerDrumChange2[]= "requires replacement.";
CUB PFRA_OrderSheet[]			= "To order replacements by phone, call               , or fill out this form";
CUB PFRA_OrderSheet2[]			= "and fax it to               .";
#else
CUB PFRA_ConsumerOrderSheet[]	= " < Commande Consommables > ";
CUB PFRA_ToOrder[]				= "Vers   ";				/* 海外は最大6文字 */
CUB PFRA_FromOrder[]			= "De     ";				/* 海外は最大6文字 */
CUB PFRA_CustomerCode[]			= "Code client    ";
CUB PFRA_DistributorName[]		= "Nom.distributeur\0 ";
CUB PFRA_CustomerName[]			= "Nom.client\0       ";
CUB PFRA_Section[]				= "Adresse(livr.)\0  ";
CUB PFRA_ChargeName[]			= "Signature ";
CUB PFRA_ModelName[]			= "Modｪle";
CUB PFRA_OrderItem[]			= "Objet Comm";   /* ﾊｯﾁｭｳﾋﾝﾓｸ\0 bythonda1998/02/24 */
CUB PFRA_TonerOrder1[]			= "Toner x       Qt ";		/* 注）Toner=5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PFRA_DrumOrder1[]			= "Tamb  x       Qt ";		/* 注）Drum =5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PFRA_SeirialNumber[]		= "No.S｢rie\0           ";
CUB PFRA_InstallDate[]			= "Data installation";
CUB PFRA_BlockLetters[]			= "Majuscules :   ";
CUB PFRA_Remarks[]				= "Note   ";
CUB PFRA_OrderTonerChange[]		= "Remplacer le toner par nouveau  ";	/* JPNのみ *//* ﾄﾅｰﾉｺｳｶﾝｶﾞ ﾋﾂﾖｳﾆﾅﾘﾏｼﾀ｡ bythonda1998/02/24 */
CUB PFRA_OrderTonerDrumChange[]	= "Remplacer Toner/Tambour par nouveau     ";  /* ﾄﾅｰ/ﾄﾞﾗﾑﾉｺｳｶﾝｶﾞ ﾋﾂﾖｳﾆﾅﾘﾏｼﾀ｡ bythonda1998/02/24 */
CUB PFRA_OrderSheet[]			= "Compl｢ter et envoyer cette feuille par fax                  ";  /* "ｵﾃｽｳﾃﾞｽｶﾞ､ｺﾉﾖｳｼｦﾂｶｯﾃｶｷﾍFAXﾃﾞｺﾞﾁｭｳﾓﾝｸﾀﾞｻｲ  bythonda1998/02/24 */
#endif

/* 簡易料金管理リスト */
#if (PRO_DEPART_NEW_LIST == ENABLE)
CUB PFRA_DepartTimeList[]	= "** Liste dur｢es/D｢partement **";  /* added by thonda 1997/12/02 */
#endif

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
CUB PFRA_KeyMacroList[]			= "** ｷｰﾏｸﾛ ﾀｲﾄﾙ ﾘｽﾄ **";
CUB PFRA_NoTitle[] 				= "ﾀｲﾄﾙ未登録";
CUB PFRA_Title[] 				= "ﾀｲﾄﾙ";
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
CUB PFRA_NumberDisplayList[]	= "** ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾀﾞｲﾔﾙ ﾘｽﾄ **";
CUB PFRA_NumberDisplay[]		= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ";
CUB PFRA_NoConnect[]			= "未接続";
CUB PFRA_Tel1Connect[]			= "PHONE1   ";
CUB PFRA_Tel2Connect[]			= "PHONE2   ";
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
CUB PFRA_ND_Warp[]				= "ND ﾜｰﾌﾟ\0";
 #endif

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
CUB PFRA_NumberDisplayJournal[]	= "** ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾂｳｼﾝ ﾘﾚｷ **";
CUB PFRA_SubscriberNumber[]		= "発信者番号";
CUB PFRA_NoNotice[]				= "非通知\0  ";
CUB PFRA_OutOfDisp[]			= "表示圏外";
CUB PFRA_PublicTel[]			= "公衆電話\0 ";
CUB PFRA_FNetCall[]				= "F Net";
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
CUB PFRA_WarpList[]		 		= " ** FAXﾜｰﾌﾟ ﾘｽﾄ ** ";
CUB PFRA_AppointedTime[]		= "指定時刻";
CUB PFRA_WarpFunction[]			= "FAXﾜｰﾌﾟ\0";
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1999/01/25 */
CUB	PFRA_WarpWeek[][4]			= {
								  "(\x08)",
								  "(\x09)",
								  "(\x0A)",
								  "(\x0B)",
								  "(\x0C)",
								  "(\x0D)",
								  "(\x0E)",
								  "(-)"
};
#endif

/* 月 */
CUB	PFRA_Year_Eng[12][4] = {
	"Jan","F｢b","Mar","Avr","Mai","Jui","Jul","Aoｶ","Sep","Oct","Nov","D｢c"
	};

/* プログラムリスト */
CUB	PFRA_ProgOnetouchDir[] 	= "** R｢pert. Une-Touche Prog. **";

/* 親展受信通知 */
#if ( PRO_MAKER == FX )
CUB	PFRA_SecureMailReci[] 	= "Mailbox Documents are received.         ";
#else
CUB	PFRA_SecureMailReci[] 	= "Message SecureMail Reｧu.\000               ";
#endif

/* 親展原稿消去通知 */
CUB	PFRA_ThisSecMailEra[] 	= "Message SecureMail effac｢s.\000            ";	/*要翻訳2000/01/13*/

/* 代行受信消去通知 */
#if ( PRO_MAKER == FX )
CUB	PFRA_ThisMemErased[] 	= "Received documents are erased.\000         ";	/* 6/28 FX.ENG */
#else
CUB	PFRA_ThisMemErased[] 	= "Message effac｢s de la M｢moire.\000         ";
#endif

/* 通信予約消去通知 */
#if ( PRO_MAKER == FX )
CUB	PFRA_ThisComErased[] 	= "Pending jobs are erased.\000                 ";	/* 6/28 FX.ENG */
#else
#if (PRO_DRAM_BACKUP == ENABLE)			/*94/11/28 ↓ By jmasuda*/
CUB	PFRA_ThisComErased[] 	= "Commands were erased.  \000                  ";
#else									/*94/11/28 ↑ By jmasuda*/
CUB	PFRA_ThisComErased[] 	= "Commandes ont ｢t｢ effac｢es.    \000          ";
#endif
#endif

/* チェックメッセージ */
CUB	PFRA_MryOverFeeder[]	= "M｢moire Pleine_Emission non effectu｢e";
CUB	PFRA_SecurityMemOver[]	= "M｢moire pleine. Pri｢re d'imprimer les documents s｢curit｢ reｧus.\000           ";

/* セキュリティ受信をONにする。メモリーオーバーするまで受信を行う。チェックメッセージが印字されるが、内容が一部間違っている。 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec K.W.Q 2003/10/20 */
CUB	PFRA_SecurityOperation1[]	= "Util.:appuyer sur PROG,Une-Tch[11],2,Entrer ";     /* 0->O bythonda1998/04/16 */
#else
CUB	PFRA_SecurityOperation1[]	= "Util.:appuyer sur PROG,Une-Tch[O],2,Entrer";     /* 0->O bythonda1998/04/16 */
#endif

CUB	PFRA_SecurityOperation2[]	= "      et entrer le code d'accｪs(4 carac.)\0  ";

/* ポーリング原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB	PFRA_PollErase[]		= "Polled documents are erased.\000                  ";	/* 6/28 FX.ENG */
#else
 #if (PRO_OKI == ENABLE)
CUB	PFRA_PollErase[]		= "Doc. Pour Relｪve effac｢s de la m｢moire.\000       ";	/* Polling -> Relｪve by K.Watanabe 1999/02/04 */
 #else
CUB	PFRA_PollErase[]		= "Doc. Pour Polling effac｢s de la m｢moire.\000      ";
 #endif
#endif
#if (PRO_OKI == ENABLE)
CUB	PFRA_DbPollErase[]		= "Doc. Pour DB.Relｪve effac｢s de la m｢moire.\000         ";	/* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#else
CUB	PFRA_DbPollErase[]		= "Doc. Pour DB.Polling effac｢s de la m｢moire.\000        ";
#endif

/* 一括送信原稿リスト */
CUB	PFRA_IndexNo[]			= "R｢ception No.";

/* 一括送信原稿消去通知 */
CUB	PFRA_BatchTxDocErase[]	= "Documents pour envoi group｢ effac｢s.    ";

/* 連続ポーリングコマンド消去通知 */
#if (PRO_OKI == ENABLE)
CUB	PFRA_ContinuousPollingErase[] = "Commande de Relｪve Continu Effac｢e.               ";	/* Polling -> Relｪve by K.Watanabe 1999/02/04 */
#else
CUB	PFRA_ContinuousPollingErase[] = "Commande de Polling Continu Effac｢e.              ";/* 1996/10/18 Eguchi */
#endif

/* 暗号化受信原稿消去通知 */
CUB	PFRA_ScrambleRxErase[]		= "Ces documents chiffr｢s ont ｢t｢ effac｢s         ";

/* 通信結果メッセージ */
CUB	PFRA_ResultName[8][31] = {  "V｢rifier appareil distant.\000   ",
								"Conf. r｢ception documents.\000   ",
#if ( PRO_MAKER == FX )
								"Tray again.\000                  ",
								"Dial again.\000                  ",
#else
								"Retransmettre.\000               ",
								"Rappeler.\000                    ",
#endif
								"M｢moire Pleine.\000              ",
#if ( PRO_MAKER == FX )
								"Dialing No. not registered.   ",/* "Dialling ～" -> "Dialing ～" 1998/09/19 By M.Kuwahara */
								"Stoped                        ",	/* By H.Y 1994/12/20 FX.ENG */
#else
								"Nﾏappel｢ non programm｢.\000      ",
								"Arr｢t｢.\000                      ",
#endif
								"\000                             " };
#if (PRO_MAKER == FX)	/* By H.Y 1994/12/20 */
CUB	PFRA_ResultChain[LST_ERR_CODE_MAX] = {
							'D','F','A','C','A',		/*0*/
							'G','A','A','A','C',        /*5*/
							'C','B','A','A','A',        /*10*/
							'C','A','A','G','A',        /*15*/
							'A','A','A','B','A',        /*20*/
							'E','A','A','A','A',		/*25*/
							'A','A','A','H','C',		/*30*/
							'G','C','C',' ',' ' }; 		/*35*/
#else
CUB	PFRA_ResultChain[LST_ERR_CODE_MAX] = {
							'D','F','A','C','A',		/*0*/
							'G','A','A','A','C',        /*5*/
							'C','B','A','A','A',        /*10*/
							'C','A','A','G','A',        /*15*/	/* R.1.4のワーディングをH->G By O.Kimoto 2002/10/24 */
							'A','A','A','B','A',        /*20*/
							'E','A','A','A','A',		/*25*/
							'A','A','A','H','C',		/*30*/
							'G','C','C',' ',' ' };		/*35*/
#endif
/*PFRA_ResultChain[]の'A'がPFRA_ResultName[][]の一番目のﾒｯｾｰｼﾞに対応する*/
CUB	PFRA_ResultCode[LST_ERR_CODE_MAX][7] = {
						"D.0.2", "D.0.6", "T.1.1", "T.1.2", "T.1.3",	/*0*/
						"T.1.4", "T.2.1", "T.2.2", "T.2.3", "T.3.1",	/*5*/
						"T.4.1", "T.4.2", "T.4.3", "T.5.1", "T.5.2",	/*10*/
						"T.5.3", "R.1.1", "R.1.2", "R.1.4", "R.2.3",	/*15*/
						"R.3.1", "R.3.3", "R.3.4", "R.4.1", "R.4.2",	/*20*/
						"R.4.4", "R.5.1", "R.5.2", "D.0.7", "T.4.4",	/*25*/
						"R.2.1", "R.3.2", "R.3.5", "R.4.5", "D.0.1",	/*30*/
						"D.0.3", "D.0.8", "R.1.3", "", "" };			/*35*/
/*最後の項目は必ず""としておく必要あり*/
/*PFRA_ResultCode[]がPFRA_ResultChain[]に対応する*/

#if (PRO_ROTATE == ENABLE)				/* ＤＰＲＡＭ経由の回転受信 */
					/*	   12345678901234567890 */
CUB PFRA_RotateMargin[]	= "Rotate Margin   ";
#endif


#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
CUB PFRA_INF_AddressList[]		= "** Mail Address Directory **";
CUB PFRA_INF_GroupList[]		= "** Mail Group Directory **";
CUB	PFRA_INF_MailComList[]		= "** Reserved Mail Commands **";
CUB	PFRA_INF_SettingList[]		= "** User Setting List **";
CUB	PFRA_INF_ErasedMailList[]	= "     ** Erased Mails **     ";
CUB PFRA_INF_ErasedCommand[]	= "** Erased Mail Commands **";
CUB PFRA_INF_Group[]			= "Mail Group";
CUB PFRA_INF_Address[]			= "Mail Address";
CUB PFRA_INF_UserName[]			= "User Name";
CUB PFRA_INF_ProviderName[]		= "ISP Name\000    ";
CUB PFRA_INF_AccessPoint1[]		= "Access Point 1";
CUB PFRA_INF_AccessPoint2[]		= "Access Point 2";
CUB PFRA_INF_AccessPoint3[]		= "Access Point 3";
#if (0)
CUB PFRA_INF_PPPLoginID[]		= "Dial-Up Login ID  ";
CUB PFRA_INF_PPPPassword[]		= "Dial-Up Login Password ";
CUB PFRA_INF_PPPAuth[]			= "Password Authentication";
CUB PFRA_INF_POPLoginID[]		= "Mail Login ID";
CUB PFRA_INF_POPPassword[]		= "Mail Login Password";
#endif
CUB PFRA_INF_PPPLoginID[]		= "PPP Login ID";
CUB PFRA_INF_PPPPassword[]		= "PPP Login Password";
CUB PFRA_INF_PPPAuth[]			= "PPP Authentication";
CUB PFRA_INF_POPLoginID[]		= "POP Login ID";
CUB PFRA_INF_POPPassword[]		= "POP Login Password";

CUB PFRA_INF_MailAddress[]		= "Mail Address";
CUB PFRA_INF_SMTPServer[]		= "SMTP Server";
CUB PFRA_INF_POPServer[]		= "POP Server";
CUB PFRA_INF_PriDNSServer[]		= "Primary DNS Server";
CUB PFRA_INF_SecDNSServer[]		= "Secondary DNS Server";
CUB PFRA_INF_ClientAddress[]	= "Client IP Address";
CUB PFRA_INF_ServerAddress[]	= "Server IP Address";
CUB PFRA_INF_GatewayAddress[]	= "Gateway IP Address";
CUB PFRA_INF_TxRx[]				= "Tx with Rx\000 ";

CUB PFRA_INF_AutoRcvMail[]		= "Auto Receive Mail";

CUB PFRA_INF_StartTime[]		= "Start Time";
CUB PFRA_INF_EndTime[]			= "End Time\000 ";
CUB PFRA_INF_IntervalTime[]		= "Interval Time";
CUB PFRA_INF_HoldTime[]			= "Hold Days";

CUB PFRA_INF_AutoPrint[]		= "Auto Print";

CUB PFRA_INF_ComsWereErased[]	= "Mail Commands were erased.\000                 ";
CUB	PFRA_INF_MailsWereErased[]	= "Received mails were erased.\000        ";
CUB	PFRA_INF_Receiver[]			= "Receiver: \000";
CUB	PFRA_INF_ErrorCode[]		= "Error Code";
CUB	PFRA_INF_ReTx[]				= "Repeat transmission\000  ";
CUB	PFRA_INF_ReRx[]				= "Repeat reception\000     ";
CUB	PFRA_INF_DialErr[]			= "Fail to connect with ISP\000 ";
CUB	PFRA_INF_ChkSetting[]		= "Check Your settings\000      ";
CUB	PFRA_INF_MemErr[]			= "Memory full\000          ";
CUB	PFRA_INF_ChkBoard[]			= "Check option board\000        ";
CUB	PFRA_INF_PowerOff[]			= "Power Off\000          ";
CUB	PFRA_INF_Kind[] 			= "Kind\000";
CUB	PFRA_INF_To[]	 			= "To";
CUB	PFRA_INF_Tx[] 				= "Tx";
CUB	PFRA_INF_Rx[] 				= "Rx";
CUB	PFRA_INF_User[]				= "User:\000";
CUB	PFRA_INF_AccessPoint[]		= "Access Point:";

CUB	PFRA_INF_ConnectTime[]		= "Connect Time (min)";
CUB	PFRA_INF_ConnectCount[]		= "Connect Count";

CUB	PFRA_MailReceptionReport[] = "** Mail Reception Report **\000     ";
CUB	PFRA_MailSender[] = "Sender\000";
CUB	PFRA_MailReceivedTime[]   = "ReceivedTime\000";
CUB	PFRA_MailAutoPrintTime[] = "PrintTime\000   ";
CUB	PFRA_MailRxReportState1[] = "Following mails have been received.                                    ";/*71*/
CUB	PFRA_MailRxReportState2[] = "Please press PROGRAM,R,2,ENTER, and then enter your Code Number        ";
CUB	PFRA_MailRxReportState3[] = "to print these mails.                                                  ";
CUB	PFRA_MailRxReportState4[] = "These mails will be printed automatically when \"PrintTime\" will be passed. ";
/*追加 1998/5/25 Eguchi*/
CUB	PFRA_INF_JournalComStartTime[] = "StartTime  ";

CUB	PFRA_INF_Ok[]				= "OK\000";
CUB	PFRA_INF_Error[]			= "ERROR\000";
CUB	PFRA_INF_AutoDownLoad[]		= "Auto Download \000";
CUB	PFRA_INF_DeleteMail[]		= "Delete Mail\000";
CUB	PFRA_INF_AutoCheck[]		= "Auto Check Mail\000";
CUB	PFRA_INF_MailJournal[]		= "   ** Mail Journal **   ";

#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */


#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
/*@^s**************************************************************************
**@^1
**@^2	ﾌﾟﾘﾝﾄ用固定文字列 横倍角タイトル
**@^3	桐／紅葉のﾀｲﾄﾙは、最初から横倍角(全角)とする
**@^4	94/ 5/27 豊田
**@^e*************************************************************************/

/*以下は、半角文字用なので全角文字用の#defineを決めること*/
/* #define     ｢       0x82   e ﾉ ﾐｷﾞ ｳｴ ｶﾗ ﾁｮﾝ (e') */
/* #define     ｪ       0x8A   e ﾉ ﾋﾀﾞﾘ ｳｴ ｶﾗ ﾁｮﾝ(e`) */
/* #define     ﾙ       0xF9   ﾟ ﾄｸｼｭﾓｼﾞ ﾉ ﾏﾙ    (ﾟ ) */
/* #define     ｧ       0x87   ｺﾓｼﾞ c ﾉ ｼﾀﾆ ﾌﾆｬﾗ (cj) */
/* #define     ｶ       0x96   u ﾉ ｳｴﾆ ﾔﾏ        (u^) */

/* 送信証　受領証 */
CUB	PFRA_TransConfReport_K[] 		= "　　＊＊　Ｒａｐｐｏｒｔ　Ｅｍｉｓｓｉｏｎ　＊＊　　";
CUB	PFRA_RecConfReport_K[] 			= "　＊＊　Ｒａｐｐｏｒｔ　Ｒ「ｃｅｐｔｉｏｎ　＊＊　";

/* 通信管理レポート｢送信｣ ｢受信｣ */
CUB PFRA_TransmitJournal_K[]		= "　＊＊Ｊｏｕｒｎａｌ　Ｅｍｉｓｓｉｏｎ＊＊　";
CUB PFRA_RecieveJournal_K[]			= " ＊＊Ｊｏｕｒｎａｌ　Ｒ「ｃｅｐｒｉｏｎ＊＊ ";

/* 短縮ダイヤルリスト */
#if ( PRO_MAKER == FX )
CUB	PFRA_TeleDirectory_K[]			= " 　　＊＊　Ｓｐｅｅｄ－Ｄｉａｌ　Ｌｉｓｔ　＊＊　　 ";
#else
CUB	PFRA_TeleDirectory_K[]			= "＊＊　Ｒ「ｐｅｒｔ．　Ｎｕｍ．　Ａｂｒ「ｇ「ｅ　＊＊";
#endif

/* ワンタッチダイヤルリスト */
#if ( PRO_MAKER == FX )
CUB	PFRA_OneDirectory_K[]			= " ＊＊　ＯｎｅーＴｏｕｃｈ　Ｄｉａｌ　Ｌｉｓｔ　＊＊ ";
#else
CUB	PFRA_OneDirectory_K[]			= " ＊＊　Ｒ「ｐｅｒｔ．　Ｕｎｅ－Ｔｏｕｃｈｅｓ　＊＊ ";
#endif

/* 属性リスト */
CUB PFRA_AttributeList_K[]			= "＊＊　Ｌｉｓｔｅ　Ａｔｔｒｉｂｕｔ　＊＊";

/* グループリスト */
#if ( PRO_MAKER == FX )
CUB PFRA_GroupDirectory_K[]			= "＊＊　Ｇｒｏｕｐ　Ｄｉａｌ　Ｌｉｓｔ　＊＊";
#else
CUB PFRA_GroupDirectory_K[]			= "＊＊　Ｒ「ｐｅｒｔ．　Ｇｒｏｕｐｅｓ　＊＊";
#endif

/* マルチプログラムリスト */
#if ( PRO_MAKER == FX )
CUB	PFRA_MultiProgram_K[]			= "　　＊＊　Ｍｕｌｔｉ　Ｐｒｏｇｒａｍ　Ｌｉｓｔ　＊＊　　";	/* 6/28 FX.ENG */
#else
CUB	PFRA_MultiProgram_K[]			= "　　　　　＊＊　                        　＊＊　　　　　";
#endif

/* 機器設定リスト */
#if ( PRO_MAKER == FX )
CUB PFRA_MachineSettings_K[]		= "　＊＊　Ｃｕｓｔｕｍ　Ｐｒｅｓｅｔｓ　＊＊　";	/* 6/28 FX.ENG */
#else
CUB PFRA_MachineSettings_K[]		= "＊　Ｐａｒａｍエｔｒｅｓ　Ｍａｃｈｉｎｅ　＊";
#endif

/* 機能リスト */
#if ( PRO_MAKER == FX )
CUB PFRA_ProgramList_K[]			= "Ｆｕｎｃｔｉｏｎ　Ｔｒｅｅ　　　";
#else
CUB PFRA_ProgramList_K[]			= "Ｌｉｓｔｅ　Ｐｒｏｇｒａｍｍ．　";
#endif

/* 通信予約リスト */
#if ( PRO_MAKER == FX )
CUB PFRA_ComReservedList_K[]		= "＊＊Ｐｅｎｄｉｎｇ　Ｊｏｂｓ　Ｌｉｓｔ＊＊";	 /* 6/28 FX.ENG */
#else
CUB PFRA_ComReservedList_K[]		= "＊＊　Ｌｉｓｔｅ　Ｃｏｍｍａｎｄｅｓ　＊＊";
#endif

/* 親展者リスト */
#if ( PRO_MAKER == FX )
CUB PFRA_SecureMailBList_K[]		= " 　　＊＊　Ｍａｉｌｂｏｘ　Ｌｉｓｔ　＊＊　　 ";
#else
CUB PFRA_SecureMailBList_K[]		= " ＊＊　Ｌｉｓｔｅ　ＳｅｃｕｒｅＭａｉｌ　＊＊ ";
#endif

/* カバーページプリント */
#if ( PRO_MAKER == FX )
CUB PFRA_CoverPageMes_K[]			= " 　＊＊　Ｆａｘ　Ｍｅｓｓａｇｅ　＊＊　 ";
#else
CUB PFRA_CoverPageMes_K[]			= "＊＊　Ｆｏｒｍｕｌａｉｒｅ　Ｆａｘ　＊＊";
#endif

/* 親展受信通知 */
#if ( PRO_MAKER == FX )
CUB PFRA_SecureMailNotice_K[]		= "ＭａｉｌｂｏｘＲｅｐｏｒｔ";
#else
CUB PFRA_SecureMailNotice_K[]		= " 　ＳｅｃｕｒｅＭａｉｌ　 ";
#endif

/* 親展原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB PFRA_ErasedDocuments_K[]		= "Ｒｃｖ　Ｍａｉｌｂｏｘ　Ｅｒａｓｅｄ";
#else
CUB PFRA_ErasedDocuments_K[]		= " Ｄｏｃｕｍｅｎｔｓ　ｅｆｆａｃ「ｓ ";
#endif

/* 代行受信消去通知 */
#if ( PRO_MAKER == FX )
CUB PFRA_ErasedDocumemts_K[]		= " Ｒｃｖ　Ｄｏｃｕｍｅｎｔ　Ｅｒａｓｅｄ ";	/* 6/28 FX.ENG */
#else
CUB PFRA_ErasedDocumemts_K[]		= " 　Ｄｏｃｕｍｅｎｔｓ　ｅｆｆａｃ「ｓ　 ";
#endif

/* 通信予約消去通知 */
#if ( PRO_MAKER == FX )
CUB PFRA_ErasedCommands_K[]			= "Ｐｅｎｄｉｎｇ Ｊｏｂ Ｅｒａｓｅｄ";	/* 10/18 FX.ENG */
#else
CUB PFRA_ErasedCommands_K[]			= "Ｄｏｃｕｍｅｎｔｓ　ｅｆｆａｃ「ｓ";
#endif

/* チェックメッセージ　メモリオーバー */
#if ( PRO_MAKER == FX )
CUB PFRA_CheckMessage_K[]			= "Ｓｅｎｄ　Ｆａｉｌ　Ｒｅｐ";
#else
CUB PFRA_CheckMessage_K[]			= "　Ｍｅｓｓ．Ａｌａｒｍｅ　";
#endif
CUB PFRA_MemoryOver_K[]				= "Ｍ「ｍ．　Ｐｌｅｉｎｅ";
CUB PFRA_PcMemoryOver_K[]			= "ＰＣ　Ｍｅｍｏｒｙ　Ｏｖｅｒ";

/* Ｔ３０モニタ */
CUB PFRA_T30Monitor_K[]				= "＊＊　Ｍｏｎｉｔｅｕｒ　Ｔ３０　＊＊";

/* ﾎﾟｰﾘﾝｸﾞ原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB PFRA_ErasePollDoc_K[]			= " 　　Ｐｏｌｌｅｄ　Ｄｏｃ．Ｅｒａｓｅｄ　　 ";
#else
CUB PFRA_ErasePollDoc_K[]			= "　　　　　　　　　　　　　　　　　　　　　　";
#endif

/* 一括送信原稿リスト */
CUB	PFRA_BatchTxDocList_K[]			= "       ＊＊　                  　＊＊       ";

/* 一括送信原稿消去通知 */
CUB	PFRA_EraseBatchTxDoc_K[]		= "                                        ";

/* 一括送信ＢＯＸリスト */
CUB	PFRA_BatchTxBoxList_K[]			= "       ＊＊　                    　＊＊       ";

/* 部門管理リスト*/
#if ( PRO_MAKER == FX )
CUB	PFRA_DepartCodeList_K[]			= "　　　　　　＊＊　Ａｃｃｏｕｎｔ　Ｌｉｓｔ　＊＊　　　　　　";	/* 6/28 FX.ENG */
#else
CUB	PFRA_DepartCodeList_K[]			= "               ＊＊　              　＊＊                   ";
#endif

/* 料金表 */
CUB	PFRA_CostBase_K[]				= "   ＊＊　      　＊＊   ";	/* POPLAR_Hのみ */

/* プログラムリスト */
#if ( PRO_MAKER == FX )
CUB	PFRA_ProgOnetouchDir_K[]		= "　　　　＊＊　Ｐ　Ｏｎｅ　Ｔｏｕｃｈ　Ｌｉｓｔ　＊＊　　　　";
#else
CUB	PFRA_ProgOnetouchDir_K[]		= "＊＊　Ｒ「ｐｅｒｔ．　Ｕｎｅ－Ｔｏｕｃｈｅ　Ｐｒｏｇ．　＊＊";
#endif

/* モニターレポート */
CUB	PFRA_MonitorReport_K[]			= "                            ";

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
CUB PFRA_F_CodeBox_List_K[]			= "　　＊＊　ＦコードＢＯＸリスト　＊＊　　";

/* サブアドレス原稿消去通知 */
CUB PFRA_Del_F_CodeBoxDoc_Notice_K[]	= "　　ＦコードＢＯＸゲンコウ  ショウキョ  ツウチ　　";

/* サブアドレスBOX蓄積原稿リスト */
CUB PFRA_F_CodeDoc_List_K[]			= "　　＊＊  ＦコードＢＯＸチクセキゲンコウリスト  ＊＊　　　";

/* サブアドレス受信通知 */
CUB PFRA_F_CodeBoxRsv_Notice_K[]	= "　　Ｆコードジュシン  ツウチ　　　";
#endif

/* ダイレクトメール防止ダイヤルリスト */
CUB	PFRA_BlockJunkList_K[]			= "＊＊　Ｂｌｏｃｋ　Ｊｕｎｋ　Ｆａｘ　Ｌｉｓｔ　＊＊　";

/* サービスレポート */
CUB	PFRA_ServiceReport_K[]			= "＊＊　Ｓｅｒｖｉｃｅ　Ｒｅｐｏｒｔ　＊＊";

/* 暗号化受信通知リスト */
/*CUB PFRA_CipherReceiveNotice_K[]	= "スクランブル受信通知";*/
CUB PFRA_CipherReceiveNotice_K[]	= "     Ｒａｐｐ．Ｒ「ｃ．ｃｈｉｆｆ．     ";

/* キーブックリスト */
/*CUB PFRA_KeyBookList_K[]			= "＊＊　キーバンク　＊＊";	 98/01/12 By M.Kuwahara */
CUB PFRA_KeyBookList_K[]			= "＊＊  　Ｒ「ｐ．Ｔｏｕｃｈ．  ＊＊";

/* キーリスト */
/*CUB PFRA_KeyWordList_K[]			= "＊＊　キーワードリスト　＊＊";*/
CUB PFRA_KeyWordList_K[]			= "＊＊　Ｌｉｓｔ．Ｔｃｈ．＊＊";

/* 暗号化受信消去通知 */
/*CUB	PFRA_EraseScrambleRxDoc_K[]		= "スクランブル原稿消去通知";*/
CUB	PFRA_EraseScrambleRxDoc_K[]		= "  Ｅｆｆ．Ｄｏｃｕｍｅｎｔ　ｃｈｉｆｆｒ．  ";

/* 消耗品発注票 */
 #if defined(JPN)
CUB PFRA_ConsumerOrderSheet_K[]		= "　　消耗品発注票　　　";   /* modified by honda 1997/11/12 */
 #else
CUB PFRA_ConsumerOrderSheet_K[]		= "消耗品発注票　　　　　";
 #endif

 #if (PRO_COST == ENABLE)				/* 料金管理 *//* Add By O.Kimoto 1997/11/17 */
/* 料金表 */
CUB	PFRA_DialingCode[]		= "        ";
CUB	PFRA_Daytime[]			= "                ";
CUB	PFRA_Night[]			= "                ";
CUB	PFRA_Midnight[]			= "                ";
CUB	PFRA_Slash10[]				= "   ";
CUB	PFRA_WithinArea[]			= "        ";
 #endif

 #if (PRO_LINENUMBER == TWICE_LINE)
/* 内蔵回線のラベルです。 By O.Kimoto 1997/12/20 */
/* CUB PWRD_InternalLineName[][8]			= { */
CUB PFRA_LineName[][8]			= {
									/* 	"123456789" */
										"Std.",
										"Ext.",
										"Opt."
										};
 #endif


#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
CUB	PFRA_INF_MailComList_K[]	= "＊＊　Ｒｅｓｅｒｖｅｄ　Ｍａｉｌ　Ｃｏｍｍａｎｄｓ　＊＊";
CUB	PFRA_INF_SettingList_K[]	= "＊＊　Ｕｓｅｒ　Ｓｅｔｔｉｎｇ　Ｌｉｓｔ　＊＊";
CUB	PFRA_INF_ErasedMailList_K[]	= "＊＊　Ｅｒａｓｅｄ　Ｍａｉｌｓ　＊＊";
CUB PFRA_INF_ErasedCommand_K[]	= "＊＊　Ｅｒａｓｅｄ　Ｍａｉｌ　Ｃｏｍｍａｎｄｓ　＊＊";
#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
CUB PFRA_KeyMacroList_K[]	= "＊＊　キーマクロ　タイトル　リスト　＊＊";
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
CUB PFRA_NumberDisplayList_K[] = "＊＊　ナンバーディスプレイ　ダイヤル　リスト　＊＊";

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
CUB PFRA_NumberDisplayJournal_K[]	= "　　　　＊＊　ナンバーディスプレイ通信履歴　＊＊　　　　";
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
CUB PFRA_WarpList_K[] 		= "　＊＊　ＦＡＸワープ　リスト　＊＊　　";
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
CUB PFRA_EmergencyTitle_Emergency_K[] 		= " 　＊＊　緊急　＊＊ ";
CUB PFRA_EmergencyTitle_Normal_K[]	 		= " 　＊＊　普通　＊＊ ";
 #endif
#endif

#endif

/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの最後に入れる) */
CUB	PFRA_TAIL[]			= "";

#undef	CUB

