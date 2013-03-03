/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_WITA.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 帳票用固定文字列 ITALIAN (ITA)
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\lst_def.h"

#define	CUB		CONST UBYTE

/* #define		ﾙ	0xD9	Oの下に_				*/

#if (PRO_CPU == SH7043) /* ワーディング先頭位置認識用 1996/07/04 T.Nose */
	#if (WORDING_1 == ITALIAN)
		CUB PWRD_1stWordingTop[] = "\0";
	#endif
	#if (WORDING_2 == ITALIAN)
		CUB PWRD_2ndWordingTop[] = "\0";
	#endif
	#if (WORDING_3 == ITALIAN)
		CUB PWRD_3rdWordingTop[] = "\0";
	#endif
#endif

/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの先頭に入れる) */
CUB	PITA_HEAD[]				= "";

/* 送信証　受領証 */
CUB	PITA_TransConfReport[] 	= "** Rapporto Conf.Trasm. **";
CUB	PITA_RecConfReport[] 	= "** Rapporto Conf.Ricez.**";
CUB	PITA_FromTo[] 			= "--->";
CUB	PITA_CommNo[] 			= "Nﾙ.\000       ";
CUB	PITA_CommMode[] 		= "Modo\000    ";
CUB	PITA_CommStartTime[] 	= "Tempo\000   ";
CUB	PITA_CommPages[] 		= "Pagine\000  ";
CUB	PITA_CommResult[] 		= "Esito\000   ";
#if ( PRO_MAKER == FX )
CUB	PITA_Normal[] 			= "Standard";
CUB	PITA_Fine[] 			= "Fine\000 ";
CUB	PITA_SFine[] 			= "SuperFine";
CUB	PITA_Gray[] 			= "Halftone";
#else
CUB	PITA_Normal[] 			= "Normal\000 ";
CUB	PITA_Fine[] 			= "Fin\000  ";
CUB	PITA_SFine[] 			= "S-Fin\000   ";
 #if (PRO_PITNEYBOWES == ENABLE)				/* 仕向け先ＵＳＡによりマルチワーディング対象外につき英語を転用しています。*/
CUB	PITA_Gray[] 			= "PHOTO\000  ";
CUB	PITA_HFine[] 			= "H-FINE\000  ";	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
CUB	PITA_HGray[] 			= "H PHOTO\000";	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
 #else
CUB	PITA_Gray[] 			= "Grigio\000 ";
 #endif
#endif
CUB	PITA_Pages[] 			= "Pagine\000";
CUB	PITA_FaxD[] 			= "Fax:";

/* 通信管理レポート */
CUB	PITA_TransmitJournal[]	= "[Trasmiss.]     ";
CUB	PITA_RecieveJournal[]	= "[Ricezione]     ";
CUB	PITA_ContNo[]			= " Nﾙ.\000";
CUB	PITA_RemoteFrom[]		= "   Da:\000 ";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題（終端をNULLで判断していない）があるので、ﾜｰﾃﾞｨﾝｸﾞを最大5ﾊﾞｲﾄ・ｺﾛﾝの位置固定(英語参照)にすること */
CUB	PITA_RemoteTo[]			= "   A:\000  ";
CUB	PITA_Mode[] 			= "  Modo\000  ";
#if ( PRO_MAKER == FX )
CUB	PITA_Start[] 			= "Transmit";	/* 6/26 FX.ENG */
#else
CUB	PITA_Start[] 			= " Inizio\000";
#endif
CUB	PITA_Received[] 		= " Inizio\000";
CUB	PITA_Time[] 			= "Intrv.";
CUB	PITA_Page[] 			= "Pag\000";
CUB	PITA_Code[] 			= "Cod.";
CUB	PITA_Result[] 			= "Elenco\000";
CUB	PITA_Note[] 			= " Nota\000";
CUB	PITA_AltNo[] 			= "Num.Alt.";
CUB	PITA_Secure[] 			= "Secure\000";
CUB	PITA_Relay[] 			= "Muta\000  ";
CUB	PITA_Polling[] 			= "Polling";
CUB	PITA_DbPolling[] 		= "Poll.DB";
CUB	PITA_Manual[] 			= "Manual\000";
CUB	PITA_RelayedTxReport[]	= "不達\000  ";
#if defined(USA) || defined(US2) || defined(AUS)	/*追加↓*/
CUB	PITA_FIP_Tx[] 			= "FIP_Tx ";
CUB	PITA_FIP_Rx[] 			= "FIP_Rx ";
CUB	PITA_FIP_Poll[] 		= "FIP_Pol";
CUB	PITA_FIP_Sec[] 			= "FIP_Sec";
#else												/*追加↑*/
CUB	PITA_FIP_Tx[] 			= "FIP Tx\000";
CUB	PITA_FIP_Rx[] 			= "FIP Rx\000";
CUB	PITA_FIP_Poll[] 		= "FIP Pol";
CUB	PITA_FIP_Sec[] 			= "FIP_Sec";
#endif
CUB	PITA_BrdCast[]	 		= "Diffus.";
CUB	PITA_Ok[] 				= "O K";
/* Fｺｰﾄﾞ */
CUB	PITA_SUB_Tx[]			= "FcodeTx";
CUB PITA_SEP_Rx[]			= "FC-Poll";
CUB PITA_SUB_Rx[]			= "FcodeRx";
/* ｽｸﾗﾝﾌﾞﾙ */
CUB	PITA_Cipher_Tx[]		= "ｽｸﾗﾝﾌﾞﾙ";
CUB	PITA_Cipher_Rx[]		= "ｽｸﾗﾝﾌﾞﾙ";

/* 短縮ダイヤルリスト */
CUB	PITA_TeleDirectory[] 	= "** Elenco Selez. Rapida **";
CUB	PITA_No[]				= "Nﾙ.";
#if ( PRO_MAKER == FX )
CUB	PITA_RemoteLocation[]	= "     Name\000      ";	/* 6/28 FX.ENG */
CUB	PITA_TeleNumber[] 		= "  Telephone No.   ";		/* 6/28 FX.ENG */
CUB	PITA_GroupNumber[] 		= "Group No.       ";		/* 6/28 FX.ENG */
#else
CUB	PITA_RemoteLocation[]	= "   Localita\000    ";
CUB	PITA_TeleNumber[] 		= " Numero Telefono\000 ";
CUB	PITA_GroupNumber[] 		= "  Numero Gruppo\000";	/* ANZUのみ */
#endif
CUB	PITA_Cost[]				= "        ";	/* POPLAR_Hのみ */

/* 属性リスト */
CUB PITA_AttributeList[]	= "** ｿﾞｸｾｲﾘｽﾄ **";
CUB PITA_Attribute[]		= "ｿﾞｸｾｲ";

/* ワンタッチダイヤルリスト */
CUB	PITA_OneDirectory[] 	= "** Elenco Selez. Veloce **";

/* プログラムリスト */
CUB	PITA_DelyTime[] 		= " Inizio\000";
CUB	PITA_Option[] 			= "Opcion  ";
CUB	PITA_NotTime[] 			= "--:--";

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/26 By M.Kuwahara */
CUB	PITA_PRG_Onetouch[]		= "ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ﾘｽﾄ        ";
CUB	PITA_PRG_Speed[]		= "短縮ﾀﾞｲﾔﾙ ﾘｽﾄ         ";
CUB	PITA_PRG_Program[]		= "ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ﾘｽﾄ      ";
CUB	PITA_PRG_SecureBox[]	= "親展BOXﾘｽﾄ            ";
CUB	PITA_PRG_ComReserve[]	= "通信予約ﾘｽﾄ           ";
CUB	PITA_PRG_Journal[]		= "通信管理ﾚﾎﾟｰﾄ         ";
CUB	PITA_PRG_Group[]		= "ｸﾞﾙｰﾌﾟ ﾘｽﾄ            ";
CUB	PITA_PRG_Setting[]		= "機器設定ﾘｽﾄ           ";
CUB	PITA_PRG_Message[]		= "ﾒｯｾｰｼﾞ ﾘｽﾄ            ";
CUB	PITA_PRG_CostBase[]		= "料金表                ";
CUB	PITA_PRG_DepartCode[]	= "部門管理ﾘｽﾄ           ";
CUB	PITA_PRG_BatchBox[]		= "一括送信BOXﾘｽﾄ        ";
CUB	PITA_PRG_BatchDoc[]		= "一括送信原稿ﾘｽﾄ       ";
CUB	PITA_PRG_F_CodeBox[]	= "FｺｰﾄﾞBOXﾘｽﾄ           ";
CUB	PITA_PRG_F_CodeDoc[]	= "FｺｰﾄﾞBOX蓄積原稿ﾘｽﾄ   ";
CUB	PITA_PRG_BlockJunk[]	= "ﾀﾞｲﾚｸﾄﾒｰﾙ防止ﾀﾞｲﾔﾙ ﾘｽﾄ";
CUB	PITA_PRG_ND_Dial[]		= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲﾀﾞｲﾔﾙ ﾘｽﾄ";
CUB	PITA_PRG_ND_Journal[]	= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ履歴     ";
CUB	PITA_PRG_Warp[]			= "FAXﾜｰﾌﾟ ﾘｽﾄ           ";
CUB PITA_ListName[]			= "ﾘｽﾄ名\0   ";
CUB PITA_CommReserved[]		= "通信予約";
CUB PITA_List[]				= "ﾘｽﾄ\0";
CUB PITA_DocStore[]			= "原稿蓄積";
#endif

/* グループリスト */
CUB	PITA_GroupDirectory[] 	= " ** Elenco Gruppi ** ";
#if ( PRO_MAKER == FX )
CUB	PITA_Location[]			= "  Name\000  ";
#else
CUB	PITA_Location[]			= " Cognome\000";
#endif

/* 機器設定リスト */
CUB	PITA_MachineSettings[] 	= "** Parametri Utante **";
#if ( PRO_MAKER == FX )
CUB	PITA_SubscriberID[] 	= "SendHeader";
#else
CUB	PITA_SubscriberID[] 	= "Cognome\000  ";
#endif
CUB	PITA_SubscriberKanaID[]	= "発信元名(ｶﾅID)  ";
#if ( PRO_MAKER == FX )
CUB	PITA_SubscriberNb[] 	= "Local ID    ";	/* 10/18 FX.ENG */
CUB	PITA_JournalAutoPrt[] 	= "Auto Activity Rep";
CUB	PITA_SecureDocHold[] 	= "Rcv MB Hold Time";
#else
CUB	PITA_SubscriberNb[] 	= "Numero Fax\000 ";
CUB	PITA_JournalAutoPrt[] 	= "Stampa auto\000     ";
CUB	PITA_SecureDocHold[] 	= "Tempo memo\000     ";
#endif
CUB	PITA_PhoneType[]		= "Tipo Tel.\000";
#if ( PRO_MAKER == FX )
CUB	PITA_ConfReport[]		= "Monitor Rep";
CUB	PITA_ScannerWidth[]		= "Scan Width   ";	/* 6/28 FX.ENG */
CUB	PITA_PrimaryMode[]		= "Resolution\000   ";	/* 6/28 FX.ENG */
CUB	PITA_Contrast[]			= "Density\000      ";	/*11/01 FX.ENG */
CUB	PITA_DialingPause[]		= "PauseDuration";
#else
CUB	PITA_ConfReport[]		= "Rapp Comm.\000";
CUB	PITA_ScannerWidth[]		= "Analisi Larg\000";
CUB	PITA_PrimaryMode[]		= "Modo init.\000   ";
CUB	PITA_Contrast[]			= "Contrasto\000    ";
CUB	PITA_DialingPause[]		= "Pausa num.\000  ";
#endif
CUB	PITA_RinggingTimes[]	= "Num.squilli\000  ";
#if ( PRO_MAKER == FX )
CUB	PITA_ReductionRate[]	= "Reduction %   ";	/* 6/28 FX.ENG */
#else
CUB	PITA_ReductionRate[]	= "Riduz. Rx\000    ";
#endif
CUB	PITA_EcmMode[]			= "Modo ECM";
CUB	PITA_CopyProtect[]		= "Copia imp.\000 ";
CUB	PITA_RemoteDiagnostic[]	= "Diagnosi rifiut\000 ";
CUB	PITA_RedialTimes[]		= "Rapp. Num./Pausa\000";
CUB	PITA_Holdmelody[]		= "Musica att.\000";
CUB	PITA_Passcode[]			= "Cod.acc.";
CUB	PITA_CloseNetwork[]		= "Rete chiuso\000   ";
CUB	PITA_SilentOperation[]	= "Modo Silente\000   ";	/* JPN以外 */
#if ( PRO_MAKER == FX )
CUB	PITA_SecurityTx[]		= "Secure Send      ";	/* 6/28 FX.ENG */
CUB	PITA_BlockjunkFax[]		= "No Junk Fax\000    ";
#else
CUB	PITA_SecurityTx[]		= "Taras. protetta  ";
CUB	PITA_BlockjunkFax[]		= "Ricez. protetta\000";
#endif
CUB	PITA_RecieveMode[]		= "Modo Ricez.\000";
#if ( PRO_MAKER == FX )
CUB	PITA_PageCompound[]		= "Combine Pages    ";	/* 9/17 FX.ENG */
#else
CUB	PITA_PageCompound[]		= "Comp. Paggine\000   ";
#endif
CUB	PITA_SortingCopy[]		= "Uscita copia";		/* POPLAR_Lのみ */
CUB	PITA_Rs232c[]			= "RS232C   Velocit.";
CUB	PITA_Stamp[]			= "Tampon\000";
CUB	PITA_MemoryTx[]			= "Em. Memoria\000   ";
CUB	PITA_RelayedRelayTx[]	= "中々継            ";
CUB	PITA_DialIn[]			= "Compos.No.Fax/Tel";	/* (JPN) */
CUB	PITA_BellTime[]			= "ﾍﾞﾙｼﾞｶﾝ";			/* (JPN) */
CUB	PITA_RingMastr[]		= "Opzion DRD Base  ";
CUB	PITA_CopyReduction[]	= "Rapp.Riduz.Copia ";
CUB	PITA_PaperSize[]		= "Dimensione Carta ";	/* ANZUのみ */
CUB PITA_PC_PaperManual[]	= "PCﾌﾟﾘﾝﾄ ﾃｻﾞｼﾖｳｼ  ";	/* ANZUのみ */
CUB	PITA_PaperType[]		= "記録紙ﾀｲﾌﾟ     ";	/* SAKAKIのみ */
CUB	PITA_ToneLine[] 		= "Tonal";
#if ( PRO_MAKER == FX )
CUB	PITA_Pps10[] 			= "10pps";	/* 6/28 FX.ENG */
CUB	PITA_Pps20[] 			= "20pps";	/* 6/28 FX.ENG */
#else
CUB	PITA_Pps10[] 			= "Impul";
CUB	PITA_Pps20[] 			= "Impul";
#endif
CUB	PITA_TxConf[]			= "Conf. Em";
CUB	PITA_RxConf[]			= "Conf. Rx\000";
CUB	PITA_A4[] 				= "A4";
CUB	PITA_B4[] 				= "B4";
CUB	PITA_A3[] 				= "A3";
CUB	PITA_F4[] 				= "F4";
#if (PRO_PITNEYBOWES == ENABLE)			
CUB PITA_LETTER[]			= "LTR";	/* ＰＢ仕様の為追加 By S.Fukui Aug. 25,1998 */
CUB PITA_LEDGER[]			= "LD";		/* ＰＢ仕様の為追加 By S.Fukui Aug. 25,1998 */
#endif
#if ( PRO_MAKER == FX )
CUB	PITA_Dark[] 			= "Darker";
CUB	PITA_NormalDark[] 		= "Normal";
CUB	PITA_Light[] 			= "Lighter";
#else
CUB	PITA_Dark[] 			= "Scuro\000";
CUB	PITA_NormalDark[] 		= "Normal";
CUB	PITA_Light[] 			= "Chiaro\000";
#endif
CUB	PITA_MinuteMark[] 		= "Minuti ";
CUB	PITA_SecondMark[] 		= "Sec.";
#if ( PRO_MAKER == FX )
CUB	PITA_Try[] 				= "Times";
#else
CUB	PITA_Try[] 				= "Squil";
#endif
CUB	PITA_Attemps[] 			= "Tantativ";
CUB	PITA_On[] 				= "Si\000";
CUB	PITA_Off[] 				= "No\000";
CUB	PITA_Mode1[]			= "Mode1";
CUB	PITA_Mode2[]			= "Mode2";
CUB	PITA_Mode3[]			= "Mode3";
CUB	PITA_P100[] 			= "100%";
CUB	PITA_P97[] 				= "97%";
CUB	PITA_P91[] 				= "91%";
CUB	PITA_P81[] 				= "81%";
CUB	PITA_P75[] 				= "75%";
#if ( PRO_MAKER == FX )
CUB	PITA_ThValue00mm[] 		= "Thrshld   00 mm";	/* 6/28 FX.ENG */
CUB	PITA_TelFax[] 			= "Tel/Fax\000 ";
CUB	PITA_Tel[] 				= "Tel\000";
CUB	PITA_Fax[] 				= "Fax\000";
CUB	PITA_AnsFax[] 			= "Ans/Fax\000";	/* 6/28 FX.ENG */
#else
CUB	PITA_ThValue00mm[] 		= "Soglio    00 mm";
CUB	PITA_TelFax[] 			= "Tel/Fax\000 ";
CUB	PITA_Tel[] 				= "Tel\000";
CUB	PITA_Fax[] 				= "Fax\000";
CUB	PITA_AnsFax[] 			= "Seg/Fax\000";
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec K.W.Q 2003/11/28 */
CUB	PITA_DialInRx[]			= "DialinNo\0";
#endif

CUB	PITA_FaxTel[]			= "FAX/TEL\000 "; /**	追加 For ANZU By H.Hirao 1996/05/21	*/
CUB	PITA_Bps300[] 			= "300";
CUB	PITA_Bps600[] 			= "600";
CUB	PITA_Bps1200[] 			= "1200";
CUB	PITA_Bps2400[] 			= "2400";
CUB	PITA_Bps4800[] 			= "4800";
CUB	PITA_Bps9600[] 			= "9600";
CUB	PITA_Bps19200[] 		= "19200";
CUB	PITA_BpsVariable[] 		= "Variable";		/** 追加 For POPLA By M.Kuwahara 1997/03/05 */
CUB	PITA_None[] 			= "NONE";
CUB	PITA_Odd[] 				= "ODD";
CUB	PITA_Even[] 			= "EVEN";
CUB	PITA_S1bit[] 			= "1bit";
CUB	PITA_S2bit[] 			= "2bit";
CUB	PITA_P7bit[] 			= "7bit";
CUB	PITA_P8bit[] 			= "8bit";
CUB	PITA_Days[] 			= "Gior";
CUB	PITA_Auto[] 			= "Auto\000";
CUB	PITA_Pattern[]			= "Modello:";	/* (USA) */
CUB	PITA_Letter[]			= "Lettera";
CUB	PITA_Legal[]			= "Legale";
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */	/* '95.07/20 By K.Watanabe */
CUB	PITA_RxAlarm[]			= "Audible Alarm";
CUB	PITA_MercuryPause[]		= "Prefix Pause ";/*追加 Mercury Pause -> Prefix Pause */
CUB PITA_MercuryNumber[]	= "Dial Prefix Number";/* Added by SMuratec C.P 2004/07/08 for prefix */
#endif
#if ( PRO_MAKER == FX )
CUB	PITA_MesageTrans[]		= "Annotation      ";
#else
CUB	PITA_MesageTrans[]		= "Messaggi Tras   ";
#endif
CUB	PITA_RemoteSecurityRx[]	= "Security Rx   ";
CUB	PITA_NormalPaper[]		= "Normal\000   ";	/* SAKAKIのみ */
CUB PITA_ThermalPaper[]		= "Thermal\000  ";	/* SAKAKIのみ */
CUB	PITA_DepartmentProtect[]= "Department Protect";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
CUB	PITA_Department[]		= "Department";				/* 追加 For ANZU By H.Hirao Feb 29,1996 */
CUB	PITA_PINAccessMode[]	= "PIN Access Mode";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#if defined(USA)
CUB	PITA_DayLightSaving[]	= "Daylight Saving";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#endif
CUB	PITA_OperationProtect[]	= "Operation Protect\000";	/* 追加 For ANZU By H.Hirao Feb 29,1996 */ /* 97/03/10 M.Kuwahara */
#if (PRO_REMOTE_RX == ENABLE)
CUB	PITA_RemoteReceive[]	= "Remote Transfer\000  ";	/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	PITA_OnHookReceive[]	= "Onhook Transfer\000  ";	/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif

/* PRO_MULTI_LINE */
/* 基本的に下記ワーディングは
** 		見出し用：半角16文字
** 		内容用  ：半角 8文字
** とします。
** by O.Kimoto 1997/07/10
*/
						/*	   12345678901234567890 */
CUB PITA_MultiTxRxType[]	= "送信･受信\000      ";
CUB PITA_TxRx[]				= "送受信\000 ";
CUB PITA_Tx[]				= "送信専用";
CUB PITA_Rx[]				= "受信専用";
CUB PITA_MultiLineType[]	= "外線･内線設定\000  ";
CUB PITA_PstnLine[]			= "外線\000   ";
CUB PITA_PbxLine[]			= "内線\000   ";
CUB PITA_PstnAccessNumber[]	= "外線接続番号 :\000 ";
CUB PITA_LineNumber[]		= "回線番号   :\000   ";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題（終端をNULLで判断していない）があるので、ﾜｰﾃﾞｨﾝｸﾞを最大11ﾊﾞｲﾄ・ｺﾛﾝの位置固定(日本語参照)にすること *//*  By O.Kimoto 1997/07/10 */
/** CUB	PITA_SubscriberKanaID[]	= "発信元名(ｶﾅID)  "; */
/** CUB	PITA_PhoneType[]		= "通信回線\000 "; */

#if (PRO_MULTI_LINE == ENABLE)	/*  By O.Kimoto 1997/01/06 */
CUB	PITA_AddErrorMessage[4][31] = {
					/* 123456789012345678901234567890 */
					  "Check Setting TX/RX Condition.",	/** D.0.10 */
					  "Repeat Transmit with G3 Mode. ",	/** D.0.11 */
					  "Check Dial Num. And Line Type ",	/** D.0.12 */
					  "Check Dial Num. And Line Type "	/** D.0.13 */
					  };
#endif

/* 記録紙サイズ */
CUB	PITA_Paper_A5[]			= "A5_P\0  ";
 #if defined(USA)
CUB	PITA_Paper_Letter[]		= "Letter\0";	/* Lettera */
 #else
CUB	PITA_Paper_Letter[]		= "Ltr_P\0 ";
 #endif
 #if defined(USA)
CUB	PITA_Paper_A4[]			= "A4_P\0  ";
 #else
CUB	PITA_Paper_A4[]			= "A4\0    ";
 #endif
 #if defined(USA) || defined(TWN) /* 1998/01/09 Y.Matsukuma */
CUB	PITA_Paper_Legal[]		= "Legal\0 ";	/* Legale */
 #else
CUB	PITA_Paper_Legal[]		= "Legal_P";
 #endif
CUB	PITA_Paper_B5R[]		= "B5R_P\0 ";
CUB	PITA_Paper_B4[]			= "B4_P\0  ";
CUB	PITA_Paper_A3[]			= "A3_P\0  ";
CUB	PITA_Paper_A4R[]		= "A4R_P\0 ";
CUB	PITA_Paper_LetterR[]	= "LtrR_P\0";
 #if defined(TWN) || defined(AUS)	/* 1998/01/08 Y.Matsukuma */
CUB	PITA_Paper_F4[]			= "F4\0    ";
 #else
CUB	PITA_Paper_F4[]			= "F4_P\0  ";
 #endif
CUB	PITA_Paper_A5R[]		= "A5R_P\0 ";
CUB	PITA_Paper_Postcard[]	= "Post_P\0";
CUB	PITA_Paper_LD[]			= "Ld_P\0  ";
CUB	PITA_Paper_GLetterR[]	= "GLtrR_P";
CUB	PITA_Paper_ExecutiveR[]	= "ExeR_P\0";
CUB	PITA_Paper_InvoiceR[]	= "InvR_P\0";
CUB	PITA_Paper_GLegal[]		= "GLegl_P";
CUB	PITA_Paper_GLetter[]	= "GLtr_P\0";
CUB	PITA_Paper_Card[]		= "Card_P\0";
CUB	PITA_Paper_Executive[]	= "Exe_P\0 ";
CUB	PITA_Paper_B5[]			= "B5_P\0  ";
CUB	PITA_Paper_C5[]			= "C5_P\0  ";
CUB	PITA_Paper_HalfLetter[]	= "HLtr_P\0";
CUB	PITA_Paper_Invoice[]	= "Inv_P\0 ";
CUB	PITA_Paper_B6[]			= "B6_P\0  ";
CUB	PITA_Paper_DL[]			= "DL_P\0  ";
CUB	PITA_Paper_CM10[]		= "CM10_P\0";
CUB	PITA_Paper_A6[]			= "A6_P\0  ";
CUB	PITA_Paper_Monarch[]	= "Mnc_P\0 ";
CUB	PITA_Paper_35[]			= "3x5_P\0 ";
CUB	PITA_Paper_User[]		= "User_P\0";

/* 記録紙サイズ POPLAR用 */
CUB	PITA_PaperSize_A5[]			= "A5\0    ";
CUB	PITA_PaperSize_Letter[]		= "Letter\0";
CUB	PITA_PaperSize_A4[]			= "A4\0    ";
CUB	PITA_PaperSize_Legal[]		= "Legal\0 ";
CUB	PITA_PaperSize_B5R[]		= "B5R\0   ";
CUB	PITA_PaperSize_B4[]			= "B4\0    ";
CUB	PITA_PaperSize_A3[]			= "A3\0    ";
CUB	PITA_PaperSize_A4R[]		= "A4R\0   ";
CUB	PITA_PaperSize_LetterR[]	= "LtrR\0  ";
CUB	PITA_PaperSize_F4[]			= "F4\0    ";
CUB	PITA_PaperSize_A5R[]		= "A5R\0   ";
CUB	PITA_PaperSize_Postcard[] 	= "Post\0  ";
CUB	PITA_PaperSize_LD[]			= "Ld\0    ";
CUB	PITA_PaperSize_GLetterR[]	= "GLtrR\0 ";
CUB	PITA_PaperSize_ExecutiveR[]	= "ExeR\0  ";
CUB	PITA_PaperSize_HalfLetterR[]= "HLtrR\0 ";
/*  CUB	PITA_PaperSize_InvoiceR[]	= "InvR\0  ";  *//* modified by honda 1997/11/14 */
CUB	PITA_PaperSize_GLegal[]		= "GLegl\0 ";
CUB	PITA_PaperSize_GLetter[]	= "GLtr\0  ";
CUB	PITA_PaperSize_Card[]		= "Card\0  ";
CUB	PITA_PaperSize_Executive[]	= "Exe\0   ";
CUB	PITA_PaperSize_B5[]			= "B5\0    ";
CUB	PITA_PaperSize_C5[]			= "C5\0    ";
CUB	PITA_PaperSize_HalfLetter[]	= "HLtr\0  ";
CUB	PITA_PaperSize_Invoice[]	= "Inv\0   ";
CUB	PITA_PaperSize_B6[]			= "B6\0    ";
CUB	PITA_PaperSize_DL[]			= "DL\0    ";
CUB	PITA_PaperSize_CM10[]		= "CM10\0  ";
CUB	PITA_PaperSize_A6[]			= "A6\0    ";
CUB	PITA_PaperSize_Monarch[]	= "Mnc\0   ";
CUB	PITA_PaperSize_35[]			= "3x5\0   ";
CUB	PITA_PaperSize_User[]		= "User\0  ";

/* メモリスイッチ */
#if ( PRO_MAKER == FX )
CUB	PITA_Machine_P[] 		= "Parameter    ";
#else
#endif
CUB	PITA_Machine_P[] 		= "Param._Utante";
CUB	PITA_Memory_S[] 		= "Inter._Memor.";
CUB	PITA_Uniq_S[]			= "Uniq.Switch  ";			/* 追加 For ANZU By H.Hirao Mar.28.1996 */
CUB	PITA_BitNumber[] 		= "7654 3210";
CUB	PITA_Default[] 			= " DIFETTO ";
CUB	PITA_AutoSet[] 			= "IMPOSTAZ.";

/* POPLA追加 -- メモリスイッチの追加 */
CBU PITA_MainteSwitch[]		= "Mnt Switch   ";

/* キノウリスト */
CUB	PITA_ProgramList[]		= "Lista Program   ";

/* 通信予約リスト */
CUB	PITA_ComReservedList[] 	= " ** Lista Comandi ** ";

/* 親展者登録リスト */
CUB	PITA_SecureMailBList[]	= "** Lista SecureMail ** ";
#if ( PRO_MAKER == FX )
CUB	PITA_UserName[] 		= "  Name    ";	/* 6/28 FX.ENG */
#else
CUB	PITA_UserName[] 		= "Nominativ\000";
#endif
CUB	PITA_Box[] 				= "Box";

/* カバーページプリント */
CUB	PITA_CoverPageMes[] 	= "Pagina di Copertura ";	/* 右端 - 2ﾊﾞｲﾄの後、ｾﾝﾀﾘﾝｸﾞ */

/* 親展受信通知 */
CUB	PITA_SecureMailNotice[] = " SecureMail  ";

/* 親展原稿消去通知 */
CUB	PITA_ErasedDocuments[] 	= "  Doc. Cancellat. ";

/* 代行受信消去通知 */
CUB	PITA_ErasedDocumemts[] 	= "Documento Cancellat.";

/* 通信予約消去通知 */
CUB	PITA_ErasedCommands[] 	= "Comandi Cancellat";
#if ( PRO_MAKER == FX )
CUB	PITA_MemHoldDate[]		= "Print mailbox by   ";
#else
CUB	PITA_MemHoldDate[]		= "(Tempo Ten.Memoria)";
#endif

/* チェックメッセージ */
CUB	PITA_CheckMessage[] 	= "Messa. Errore";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PITA_MemoryOver[] 		= "Mem. Piena ";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PITA_PcMemoryOver[]		= "PC Memory Over";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PITA_ErrorPages[] 		= "Pagg. Errore:\0";

/* Ｔ３０モニタ */
CUB	PITA_T30Monitor[]		= "** T30 Monitor ** ";
CUB	PITA_TxFrame[]			= "TxTrama";
CUB	PITA_RxFrame[]			= "RxTrama";
CUB	PITA_Datalong[]			= "Parola ";
CUB	PITA_Rs144[]			= "144";
CUB	PITA_Rs120[]			= "120";
CUB	PITA_Rs96[]				= " 96";
CUB	PITA_Rs72[]				= " 72";
CUB	PITA_Rs48[]				= " 48";
CUB	PITA_Rs24[]				= " 24";
CUB	PITA_V17[]				= "V17";
CUB	PITA_V33[]				= "V33";
CUB	PITA_V29[]				= "V29";
CUB	PITA_V27[]				= "V27";
CUB	PITA_MH[]				= " MH";
CUB	PITA_MR[]				= " MR";
CUB	PITA_MMR[]				= "MMR";
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
CUB	PITA_JBG[]				= "JBG";
#endif
CUB	PITA_A5[]				= "A5";
CUB	PITA_A6[]				= "A6";
CUB	PITA_Wait20[]			= "20";
CUB	PITA_Wait40[]			= "40";
CUB	PITA_Wait10[]			= "10";
CUB	PITA_Wait5[]			= " 5";
CUB	PITA_Wait0[]			= " 0";
CUB	PITA_ModeNR[]			= "N";
CUB	PITA_ModeFN[]			= "F";
CUB	PITA_ModeSF[]			= "S";
CUB	PITA_ModeHF[]			= "H";

CUB	PITA_Main[]				= "MAN";
CUB	PITA_Reset[]			= "Res";
CUB	PITA_Error[]			= "Err";
CUB	PITA_Now[]				= "Now";
CUB	PITA_DpramTx[]			= "Tx";
CUB	PITA_DpramRx[]			= "Rx";

/* コウジョウ ファンクション リスト */
CUB	PITA_FunctionList[]		= "Funzione di fabbrica";
CUB	PITA_LedTest[]			= "Testo LED           ";
CUB	PITA_LcdTest[]			= "Testo LCD           ";
CUB	PITA_Pane1keytest[]		= "Testo tastiera      ";
CUB	PITA_Rs232cTest[]		= "Testo RS232C        ";
CUB	PITA_SramCheck[]		= "Testo SRAM          ";
CUB	PITA_DramCheck[]		= "Testo DRAM          ";
CUB	PITA_RTCTest[]			= "Testo RTC           ";

/* オンラインモニタ */
#if ( PRO_CLASS1 == ENABLE )
CUB	PITA_OnLineMonitor[]	= "< Online Monitor > ";
CUB	PITA_OnLineTx[]			= "TX";
CUB	PITA_OnLineRx[]			= "RX";
CUB	PITA_OnLineData[]		= "Data";
CUB	PITA_Speed[]			= "Speed";
CUB	PITA_Command[]			= "Cmd";
CUB	PITA_Response[]			= "Res";
CUB	PITA_Abort[]			= "Abt";
#endif

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
CUB PITA_F_CodeBox_List[]	= " ** FｺｰﾄﾞBOXﾘｽﾄ **  ";
CUB PITA_BoxName[]			= "ﾎﾞｯｸｽ  ﾒｲ";
CUB PITA_SubAddress[]		= "SUBｱﾄﾞﾚｽﾊﾞﾝｺﾞｳ";
CUB PITA_CommPasscode[]		= "ﾂｳｼﾝﾊﾟｽﾜｰﾄﾞ ﾊﾞﾝｺﾞｳ";
CUB PITA_Kind[]				= "ｼｭﾍﾞﾂ";
CUB PITA_NoticeBoard[]		= "ｹｲｼﾞﾊﾞﾝ";
CUB PITA_RecvProtect[]		= "ｼﾞｭｼﾝｷﾝｼ\0 ";
CUB PITA_Replace[]			= "ｳﾜｶﾞｷ\0 ";
CUB PITA_RxPrint[]			= "ﾄﾞｳｼﾞﾌﾟﾘﾝﾄ";
CUB PITA_TransErase[]		= "ｿｳｼﾝｼﾞｹﾞﾝｺｳｼｮｳｷｮ\0";

#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
CUB PITA_RelayName[] 		= "配信先";
CUB PITA_PutSubscriber[] 	= "発信元";
CUB PITA_Avail[]			= "外付け";
CUB	PITA_NoTTI[]			= "付けない";
CUB	PITA_SUB_Relay[]		= "Fﾁｭｳｹｲ ";	/* 1998/09/25 By M.Kuwahara */
CUB	PITA_SUB_Secure[]		= "Fｼﾝﾃﾝ  ";	/* 1998/09/28 By M.Kuwahara */
#endif

#if (PRO_FCODE_KIND_DISPLAY == ENABLE)
CUB	PITA_SUB_Bulletin[]		= "Fｹｲｼﾞ  ";	/* 1998/09/28 By M.Kuwahara */
#endif

/* サブアドレス原稿消去通知 */
CUB PITA_Del_F_CodeBoxDoc_Notice[]	= " FｺｰﾄﾞBOXｹﾞﾝｺｳ ｼｮｳｷｮ ﾂｳﾁ ";
CUB PITA_BoxLocation[]		= "ｱｲﾃｻｷ ﾒｲ";
CUB PITA_ThisBoxErased[]	= "Fｺｰﾄﾞﾎﾞｯｸｽｹﾞﾝｺｳ ｶﾞ ｼｮｳｷｮｻﾚﾏｼﾀ.........";

/* サブアドレスＢＯＸ蓄積原稿リスト */
CUB PITA_DocumentsNo[]		= "ﾌｧｲﾙNo.\0";
CUB PITA_F_CodeDoc_List[]	= " ** FｺｰﾄﾞBOXﾁｸｾｷｹﾞﾝｺｳﾘｽﾄ ** ";

/* サブアドレス受信通知 */
CUB PITA_F_CodeBoxRsv_Notice[]	= " Fｺｰﾄﾞｼﾞｭｼﾝ ﾂｳﾁ  ";
CUB PITA_F_CodeReci[]		= "Fｺｰﾄﾞﾎﾞｯｸｽｹﾞﾝｺｳ ｦ ｼﾞｭｼﾝ ｼﾏｼﾀ";
CUB PITA_F_ReciDocMemory[]	= "(ｼﾝﾃﾝｹﾞﾝｺｳ ｷｵｸｷｶﾝ)\0  ";
#endif

/* ダイレクトメール防止ダイヤルリスト */
CUB	PITA_BlockJunkList[]	= " ** Block Junk Fax List ** ";
CUB	PITA_TelNum[]			= "Tel Number\0";

/* サービスレポート */
CUB	PITA_ServiceReport[]	= "** Service Report **";

/* ポーリング原稿消去通知 */
CUB	PITA_ErasePollDoc[]		= "  PollDoc. Cancellat. ";

/* 一括送信原稿リスト */
CUB PITA_BatchTxDocList[]	= "                              ";

/* 一括送信ＢＯＸリスト */
CUB PITA_BatchTxBoxList[]	= "                                ";

CUB PITA_Batch[]			= "Batch";
CUB PITA_BoxNo[]			= "Box No.\000   ";

/* 暗号化受信通知リスト */
CUB PITA_CipherReceiveNotice[]	= " ｽｸﾗﾝﾌﾞﾙ ｼﾞｭｼﾝ ﾂｳﾁ  ";
CUB PITA_ReceiveNo[]		= "受信No.\0  ";
CUB PITA_KeyClue[]			= "ｷｰﾜｰﾄﾞ ﾉ ﾋﾝﾄ";
CUB PITA_KeyWordClue[]		= "ﾋﾝﾄ     ";

/* キーリスト、キーブックリスト */
CUB PITA_KeyBookList[]		= " ** ｷｰﾊﾞﾝｸ **  ";	/* 98/01/12 By M.Kuwahara */
CUB PITA_KeyWordList[]		= "  ** ｷｰﾜｰﾄﾞﾘｽﾄ **  ";
CUB PITA_KeyName[]			= "ｷｰﾜｰﾄﾞ ﾉ ﾅﾏｴ";
CUB PITA_Key[]				= "ｷｰﾜｰﾄﾞ";

/* 暗号化受信消去通知 */
CUB	PITA_EraseScrambleRxDoc[]	= "Erased Scrambling Doc.";

/* 消耗品発注票 */
#if defined(JPN)
CUB PITA_ConsumerOrderSheet[]	= "ｼｮｳﾓｳﾋﾝ ﾊｯﾁｭｳﾋｮｳ\0          ";
CUB PITA_ToOrder[]				= "ﾊｯﾁｭｳｻｷ";
CUB PITA_FromOrder[]			= "ﾊｯﾁｭｳﾓﾄ";
CUB PITA_CustomerCode[]			= "ﾄｸｲｻｷｺｰﾄﾞ\0     ";		/* JPNは最大10byte */
CUB PITA_DistributorName[]		= "ｼｬﾒｲ\0             ";	/* JPNは最大10byte */
CUB PITA_CustomerName[]			= "ｼｬﾒｲ\0             ";	/* JPNは最大10byte */
CUB PITA_Section[]				= "ﾌﾞｶﾒｲ\0           ";		/* JPNは最大10byte */
CUB PITA_ChargeName[]			= "ｺﾞﾀﾝﾄｳｼｬﾒｲ";
CUB PITA_ModelName[]			= "ﾓﾃﾞﾙﾒｲ";
CUB PITA_OrderItem[]			= "ﾊｯﾁｭｳﾋﾝﾓｸ\0";
CUB PITA_TonerOrder1[]			= "ﾄﾅｰ   x 1\0       ";		/* 注）ﾄﾅｰ =5byte, x 1の位置固定（日本語参照） */
CUB PITA_DrumOrder1[]			= "ﾄﾞﾗﾑ  x 1\0       ";		/* 注）ﾄﾞﾗﾑ=5byte, x 1の位置固定（日本語参照） */
CUB PITA_SeirialNumber[]		= "ｼﾘｱﾙNo.\0            ";	/* JPNは最大10byte */
CUB PITA_InstallDate[]			= "ｾｯﾁﾋﾞ\0           ";		/* JPNは最大10byte */
CUB PITA_BlockLetters[]			= "               ";		/* JPNは未使用 */
CUB PITA_Remarks[]				= "ﾋﾞｺｳ   ";
CUB PITA_OrderTonerChange[]		= "ﾄﾅｰﾉｺｳｶﾝｶﾞ ﾋﾂﾖｳﾆﾅﾘﾏｼﾀ｡          ";
CUB PITA_OrderTonerDrumChange[]	= "ﾄﾅｰ/ﾄﾞﾗﾑﾉｺｳｶﾝｶﾞ ﾋﾂﾖｳﾆﾅﾘﾏｼﾀ｡             ";
CUB PITA_OrderSheet[]			= "ｵﾃｽｳﾃﾞｽｶﾞ､ｺﾉﾖｳｼｦﾂｶｯﾃ､ｶｷﾍFAXﾃﾞｺﾞﾁｭｳﾓﾝｸﾀﾞｻｲ｡                  ";
#elif defined(US1)			/* orderbythonda1998/11/11 */
CUB PITA_ConsumerOrderSheet[]	= "PITNEY BOWES OFFICE SYSTEMS 4100";
CUB PITA_ConsumerOrderSheet2[]	= "SUPPLIES ORDER FORM";
CUB PITAToOrder[]				= "To:\0   ";				/* 海外は最大6文字 */
CUB PITA_FromOrder[]			= "From:\0 ";				/* 海外は最大6文字 */
CUB PITA_CustomerCode[]			= "Customer's Code";
CUB PITA_DistributorName[]		= "Distributor's Name";
CUB PITA_CustomerName[]			= "Customer's Name\0  ";
CUB PITA_Section[]				= "Address(Ship to:)";
CUB PITA_ChargeName[]			= "Signature ";
CUB PITA_ModelName[]			= "Model ";
CUB PITA_OrderItem[]			= "Item Needed: ";
CUB PITA_TonerOrder1[]			= "Toner Cartridge x       PCS";		/* 注）Toner=5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PITA_DrumOrder1[]			= "Drum Unit       x       PCS";		/* 注）Drum =5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PITA_SeirialNumber[]		= "Serial No.";
CUB PITA_InstallDate[]			= "Installation Date";
CUB PITA_BlockLetters[]			= "Print Name :";
CUB PITA_Remarks[]				= "Customer Account No. & Ship to Address";
CUB PITA_OrderTonerChange[]		= "Replace toner with a new one.   ";	/* JPNのみ */
CUB PITA_OrderTonerDrumChange[]	= "Your machine's display indicates that either the Toner Cartridge or Drum Unit";
CUB PITA_OrderTonerDrumChange2[]= "requires replacement.";
CUB PITA_OrderSheet[]			= "To order replacements by phone, call               , or fill out this form";
CUB PITA_OrderSheet2[]			= "and fax it to               .";
#else
CUB PITA_ConsumerOrderSheet[]	= "   < ｼｮｳﾓｳﾋﾝ ﾊｯﾁｭｳﾋｮｳ >    ";
CUB PITA_ToOrder[]				= "ﾊｯﾁｭｳｻｷ";				/* 海外は最大6文字 */
CUB PITA_FromOrder[]			= "ﾊｯﾁｭｳﾓﾄ";				/* 海外は最大6文字 */
CUB PITA_CustomerCode[]			= "ﾄｸｲｻｷｺｰﾄﾞ\0     ";
CUB PITA_DistributorName[]		= "ｼｬﾒｲ\0             ";
CUB PITA_CustomerName[]			= "ｼｬﾒｲ\0             ";
CUB PITA_Section[]				= "ﾌﾞｶﾒｲ\0           ";
CUB PITA_ChargeName[]			= "ｺﾞﾀﾝﾄｳｼｬﾒｲ";
CUB PITA_ModelName[]			= "ﾓﾃﾞﾙﾒｲ";
CUB PITA_OrderItem[]			= "ﾊｯﾁｭｳﾋﾝﾓｸ\0";
CUB PITA_TonerOrder1[]			= "ﾄﾅｰ   x 1\0       ";		/* 注）Toner=5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PITA_DrumOrder1[]			= "ﾄﾞﾗﾑ  x 1\0       ";		/* 注）Drum =5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PITA_SeirialNumber[]		= "ｼﾘｱﾙNo.\0            ";
CUB PITA_InstallDate[]			= "ｾｯﾁﾋﾞ\0           ";
CUB PITA_BlockLetters[]			= "Block Letters :";
CUB PITA_Remarks[]				= "Nota   ";
CUB PITA_OrderTonerChange[]		= "ﾄﾅｰﾉｺｳｶﾝｶﾞ ﾋﾂﾖｳﾆﾅﾘﾏｼﾀ｡          ";	/* JPNのみ */
CUB PITA_OrderTonerDrumChange[]	= "ﾄﾅｰ/ﾄﾞﾗﾑﾉｺｳｶﾝｶﾞ ﾋﾂﾖｳﾆﾅﾘﾏｼﾀ｡             ";
CUB PITA_OrderSheet[]			= "ｵﾃｽｳﾃﾞｽｶﾞ､ｺﾉﾖｳｼｦﾂｶｯﾃ､ｶｷﾍFAXﾃﾞｺﾞﾁｭｳﾓﾝｸﾀﾞｻｲ｡                  ";
#endif

/* 簡易料金管理リスト */
#if (PRO_DEPART_NEW_LIST == ENABLE)
CUB PITA_DepartTimeList[]	= "   ** ﾌﾞﾓﾝﾍﾞﾂ ｼﾞｶﾝｶﾝﾘ ﾘｽﾄ **  ";  /* added by thonda 1997/12/02 */
#endif

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
CUB PITA_KeyMacroList[] 		= "** ｷｰﾏｸﾛ ﾀｲﾄﾙ ﾘｽﾄ **";
CUB PITA_NoTitle[] 				= "ﾀｲﾄﾙ未登録";
CUB PITA_Title[] 				= "ﾀｲﾄﾙ";
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
CUB PITA_NumberDisplayList[]	= "** ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾀﾞｲﾔﾙ ﾘｽﾄ **";
CUB PITA_NumberDisplay[]		= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ";
CUB PITA_NoConnect[]			= "未接続";
CUB PITA_Tel1Connect[]			= "PHONE1   ";
CUB PITA_Tel2Connect[]			= "PHONE2   ";
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
CUB PITA_ND_Warp[]				= "ND ﾜｰﾌﾟ\0";
 #endif

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
CUB PITA_NumberDisplayJournal[]	= "** ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾂｳｼﾝ ﾘﾚｷ **";
CUB PITA_SubscriberNumber[]		= "発信者番号";
CUB PITA_NoNotice[]				= "非通知\0  ";
CUB PITA_OutOfDisp[]			= "表示圏外";
CUB PITA_PublicTel[]			= "公衆電話\0 ";
CUB PITA_FNetCall[]				= "F Net";
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
CUB PITA_WarpList[]			 	= " ** FAXﾜｰﾌﾟ ﾘｽﾄ ** ";
CUB PITA_AppointedTime[]		= "指定時刻";
CUB PITA_WarpFunction[]			= "FAXﾜｰﾌﾟ\0";
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1999/01/25 */
CUB	PITA_WarpWeek[][4]			= {
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
CUB	PITA_Year_Eng[12][4] = {
	"Gen","Feb","Mar","Apr","Mag","Gui","Lug","Ago","Set","Ott","Nov","Dic"
	};

/* プログラムリスト */
CUB	PITA_ProgOnetouchDir[] 	= " ** Elenco Tasti Program. **  ";

/* 親展受信通知 */
#if ( PRO_MAKER == FX )
CUB	PITA_SecureMailReci[] 	= "Mailbox Documents are received.         ";
#else
CUB	PITA_SecureMailReci[] 	= "SecureMail Ricevuta.\000                   ";
#endif

/* 親展原稿消去通知 */
CUB	PITA_ThisSecMailEra[] 	= "Documenti SecureMail cancellati.\000       ";

/* 代行受信消去通知 */
#if ( PRO_MAKER == FX )
CUB	PITA_ThisMemErased[] 	= "Received documents are erased.\000         ";	/* 6/28 FX.ENG */
#else
CUB	PITA_ThisMemErased[] 	= "Documenti cancellati della memoria.\000    ";
#endif

/* 通信予約消去通知 */
#if ( PRO_MAKER == FX )
CUB	PITA_ThisComErased[] 	= "Pending jobs are erased.\000                 ";	/* 6/28 FX.ENG */
#else
#if (PRO_DRAM_BACKUP == ENABLE)			/*94/11/28 ↓ By jmasuda*/
CUB	PITA_ThisComErased[] 	= "Commands were erased.  \000                  ";
#else									/*94/11/28 ↑ By jmasuda*/
CUB	PITA_ThisComErased[] 	= "Comanda cancellata.\000                      ";
#endif
#endif

/* チェックメッセージ */
CUB	PITA_MryOverFeeder[]	= "Memoria Piena, No pue Trasmettere.\000  ";
CUB	PITA_SecurityMemOver[]	= "Memory full. Please print received security documents.\000                    ";/*追加*/

/* セキュリティ受信をONにする。メモリーオーバーするまで受信を行う。チェックメッセージが印字されるが、内容が一部間違っている。 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec K.W.Q 2003/10/20 */
CUB	PITA_SecurityOperation1[]	= "ｿｳｻ ：ｷﾉｳ -> ﾜﾝﾀｯﾁ 11 -> 2 -> ｾｯﾄ ｦ ｵｼ\0     ";
#else
CUB	PITA_SecurityOperation1[]	= "ｿｳｻ ：ｷﾉｳ -> ﾜﾝﾀｯﾁ O -> 2 -> ｾｯﾄ ｦ ｵｼ\0    ";
#endif

CUB	PITA_SecurityOperation2[]	= "      4ｹﾀﾉ ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｦ ﾆｭｳﾘｮｸ ｼﾃｸﾀﾞｻｲ\0     ";

/* ポーリング原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB	PITA_PollErase[]		= "Polled documents are erased.\000                  ";	/* 6/28 FX.ENG */
#else
CUB	PITA_PollErase[]		= "Documenti Polling cancellati della memoria\000    ";
#endif
CUB	PITA_DbPollErase[]		= "Documenti DB_Polling cancellati della memoria\000      ";

/* 一括送信原稿リスト */
CUB	PITA_IndexNo[]			= "             ";

/* 一括送信原稿消去通知 */
CUB	PITA_BatchTxDocErase[]	= "                                        ";

/* 連続ポーリングコマンド消去通知 */
CUB	PITA_ContinuousPollingErase[] = "Continuous Polling Command was erased.            ";/* 1996/10/18 Eguchi */

/* 暗号化受信原稿消去通知 */
CUB	PITA_ScrambleRxErase[]		= "These Scrambling Documents were erased.        ";

/* 通信結果メッセージ */
CUB	PITA_ResultName[8][31] = {  "Verif. la macc. a dist.\000      ",
								"Conf document ricevuti.\000      ",
#if ( PRO_MAKER == FX )
								"Tray again.\000                  ",
								"Dial again.\000                  ",
#else
								"Retrsmit.\000                    ",
								"Rchamare.\000                    ",
#endif
								"Memoria piena.\000               ",
#if ( PRO_MAKER == FX )
								"Dialing No. not registered.  ", /* "Dialling ～" -> "Dialing ～" 1998/09/19 By M.Kuwahara */
								"Stoped                        ",	/* By H.Y 1994/12/20 FX.ENG */
#else
								"Numero non estato memorizato.\000",
								"\000                             ",
#endif
								"\000                             " };
#if (PRO_MAKER == FX)	/* By H.Y 1994/12/20 */
CUB	PITA_ResultChain[LST_ERR_CODE_MAX] = {
							'D','F','A','C','A',		/*0*/
							'G','A','A','A','C',        /*5*/
							'C','B','A','A','A',        /*10*/
							'C','A','A','G','A',        /*15*/
							'A','A','A','B','A',        /*20*/
							'E','A','A','A','A',		/*25*/
							'A','A','A','H','C',		/*30*/
							'G','C','C',' ',' ' }; 		/*35*/
#else
CUB	PITA_ResultChain[LST_ERR_CODE_MAX] = {
							'D','F','A','C','A',		/*0*/
							'G','A','A','A','C',        /*5*/	/* T.1.4のワーディングをH->G By O.Kimoto 2002/10/24 */
							'C','B','A','A','A',        /*10*/
							'C','A','A','G','A',        /*15*/	/* R.1.4のワーディングをH->G By O.Kimoto 2002/10/24 */
							'A','A','A','B','A',        /*20*/
							'E','A','A','A','A',		/*25*/
							'A','A','A','H','C',		/*30*/
							'G','C','C',' ',' ' }; 		/*35*/	/* D.0.3のワーディングをH->G By O.Kimoto 2002/10/24 */
#endif
/*PITA_ResultChain[]の'A'がPITA_ResultName[][]の一番目のﾒｯｾｰｼﾞに対応する*/
CUB	PITA_ResultCode[LST_ERR_CODE_MAX][7] = {
						"D.0.2", "D.0.6", "T.1.1", "T.1.2", "T.1.3",	/*0*/
						"T.1.4", "T.2.1", "T.2.2", "T.2.3", "T.3.1",	/*5*/
						"T.4.1", "T.4.2", "T.4.3", "T.5.1", "T.5.2",	/*10*/
						"T.5.3", "R.1.1", "R.1.2", "R.1.4", "R.2.3",	/*15*/
						"R.3.1", "R.3.3", "R.3.4", "R.4.1", "R.4.2",	/*20*/
						"R.4.4", "R.5.1", "R.5.2", "D.0.7", "T.4.4",	/*25*/
						"R.2.1", "R.3.2", "R.3.5", "R.4.5", "D.0.1",	/*30*/
						"D.0.3", "D.0.8", "R.1.3", "", "" };			/*35*/
/*最後の項目は必ず""としておく必要あり*/
/*PITA_ResultCode[]がPITA_ResultChain[]に対応する*/

#if (PRO_ROTATE == ENABLE)				/* ＤＰＲＡＭ経由の回転受信 */
					/*	   12345678901234567890 */
CUB PITA_RotateMargin[]	= "Rotate Margin   ";
#endif


#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
CUB PITA_INF_AddressList[]		= "** Mail Address Directory **";
CUB PITA_INF_GroupList[]		= "** Mail Group Directory **";
CUB	PITA_INF_MailComList[]		= "** Reserved Mail Commands **";
CUB	PITA_INF_SettingList[]		= "** User Setting List **";
CUB	PITA_INF_ErasedMailList[]	= "     ** Erased Mails **     ";
CUB PITA_INF_ErasedCommand[]	= "** Erased Mail Commands **";
CUB PITA_INF_Group[]			= "Mail Group";
CUB PITA_INF_Address[]			= "Mail Address";
CUB PITA_INF_UserName[]			= "User Name";
CUB PITA_INF_ProviderName[]		= "ISP Name\000    ";
CUB PITA_INF_AccessPoint1[]		= "Access Point 1";
CUB PITA_INF_AccessPoint2[]		= "Access Point 2";
CUB PITA_INF_AccessPoint3[]		= "Access Point 3";
#if (0)
CUB PITA_INF_PPPLoginID[]		= "Dial-Up Login ID  ";
CUB PITA_INF_PPPPassword[]		= "Dial-Up Login Password ";
CUB PITA_INF_PPPAuth[]			= "Password Authentication";
CUB PITA_INF_POPLoginID[]		= "Mail Login ID";
CUB PITA_INF_POPPassword[]		= "Mail Login Password";
#endif
CUB PITA_INF_PPPLoginID[]		= "PPP Login ID";
CUB PITA_INF_PPPPassword[]		= "PPP Login Password";
CUB PITA_INF_PPPAuth[]			= "PPP Authentication";
CUB PITA_INF_POPLoginID[]		= "POP Login ID";
CUB PITA_INF_POPPassword[]		= "POP Login Password";

CUB PITA_INF_MailAddress[]		= "Mail Address";
CUB PITA_INF_SMTPServer[]		= "SMTP Server";
CUB PITA_INF_POPServer[]		= "POP Server";
CUB PITA_INF_PriDNSServer[]		= "Primary DNS Server";
CUB PITA_INF_SecDNSServer[]		= "Secondary DNS Server";
CUB PITA_INF_ClientAddress[]	= "Client IP Address";
CUB PITA_INF_ServerAddress[]	= "Server IP Address";
CUB PITA_INF_GatewayAddress[]	= "Gateway IP Address";
CUB PITA_INF_TxRx[]				= "Tx with Rx\000 ";
CUB PITA_INF_AutoRcvMail[]		= "Auto Receive Mail";

CUB PITA_INF_StartTime[]		= "Start Time";
CUB PITA_INF_EndTime[]			= "End Time\000 ";
CUB PITA_INF_IntervalTime[]		= "Interval Time";
CUB PITA_INF_HoldTime[]			= "Hold Days";
CUB PITA_INF_AutoPrint[]		= "Auto Print";

CUB PITA_INF_ComsWereErased[]	= "Mail Commands were erased.\000                 ";
CUB	PITA_INF_MailsWereErased[]	= "Received mails were erased.\000        ";
CUB	PITA_INF_Receiver[]			= "Receiver: \000";
CUB	PITA_INF_ErrorCode[]		= "Error Code";
CUB	PITA_INF_ReTx[]				= "Repeat transmission\000  ";
CUB	PITA_INF_ReRx[]				= "Repeat reception\000     ";
CUB	PITA_INF_DialErr[]			= "Fail to connect with ISP\000 ";
CUB	PITA_INF_ChkSetting[]		= "Check Your settings\000      ";
CUB	PITA_INF_MemErr[]			= "Memory full\000          ";
CUB	PITA_INF_ChkBoard[]			= "Check option board\000        ";
CUB	PITA_INF_PowerOff[]			= "Power Off\000          ";
CUB	PITA_INF_Kind[] 			= "Kind\000";
CUB	PITA_INF_To[]	 			= "To";
CUB	PITA_INF_Tx[] 				= "Tx";
CUB	PITA_INF_Rx[] 				= "Rx";
CUB	PITA_INF_User[]				= "User:\000";
CUB	PITA_INF_AccessPoint[]		= "Access Point:";

CUB	PITA_INF_ConnectTime[]		= "Connect Time (min)";
CUB	PITA_INF_ConnectCount[]		= "Connect Count";

CUB	PITA_MailReceptionReport[] = "** Mail Reception Report **\000     ";
CUB	PITA_MailSender[] = "Sender\000";
CUB	PITA_MailReceivedTime[]   = "ReceivedTime\000";
CUB	PITA_MailAutoPrintTime[] = "PrintTime\000   ";
CUB	PITA_MailRxReportState1[] = "Following mails have been received.                                    ";/*71*/
CUB	PITA_MailRxReportState2[] = "Please press PROGRAM,R,2,ENTER, and then enter your Code Number        ";
CUB	PITA_MailRxReportState3[] = "to print these mails.                                                  ";
CUB	PITA_MailRxReportState4[] = "These mails will be printed automatically when \"PrintTime\" will be passed. ";
/*追加 1998/5/25 Eguchi*/
CUB	PITA_INF_JournalComStartTime[] = "StartTime  ";

CUB	PITA_INF_Ok[]				= "OK\000";
CUB	PITA_INF_Error[]			= "ERROR\000";
CUB	PITA_INF_AutoDownLoad[]		= "Auto Download \000";
CUB	PITA_INF_DeleteMail[]		= "Delete Mail\000";
CUB	PITA_INF_AutoCheck[]		= "Auto Check Mail\000";
CUB	PITA_INF_MailJournal[]		= "   ** Mail Journal **   ";

#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */


#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
/*@^s**************************************************************************
**@^1
**@^2	ﾌﾟﾘﾝﾄ用固定文字列 全角文字タイトル
**@^3	桐／紅葉のﾀｲﾄﾙは、最初から横倍角(全角)とする
**@^4	94/ 5/27 豊田
**@^e*************************************************************************/

/* 送信証　受領証 */
CUB	PITA_TransConfReport_K[] 		= "                                                    ";
CUB	PITA_RecConfReport_K[] 			= "                                                  ";

/* 通信管理レポート｢送信｣ ｢受信｣ */
CUB PITA_TransmitJournal_K[]		= "                                            ";
CUB PITA_RecieveJournal_K[]			= "                                            ";

/* 短縮ダイヤルリスト */
#if ( PRO_MAKER == FX )
CUB	PITA_TeleDirectory_K[]			= " 　　＊＊　Ｓｐｅｅｄ－Ｄｉａｌ　Ｌｉｓｔ　＊＊　　 ";
#else
CUB	PITA_TeleDirectory_K[]			= "                                                    ";
#endif

/* ワンタッチダイヤルリスト */
#if ( PRO_MAKER == FX )
CUB	PITA_OneDirectory_K[]			= " ＊＊　ＯｎｅーＴｏｕｃｈ　Ｄｉａｌ　Ｌｉｓｔ　＊＊ ";
#else
CUB	PITA_OneDirectory_K[]			= "                                                    ";
#endif

/* 属性リスト */
CUB PITA_AttributeList_K[]			= "＊＊　Ａｔｔｒｉｂｕｔｅ　Ｌｉｓｔ　＊＊";

/* グループリスト */
#if ( PRO_MAKER == FX )
CUB PITA_GroupDirectory_K[]			= "＊＊　Ｇｒｏｕｐ　Ｄｉａｌ　Ｌｉｓｔ　＊＊";
#else
CUB PITA_GroupDirectory_K[]			= "                                          ";
#endif

/* マルチプログラムリスト */
#if ( PRO_MAKER == FX )
CUB	PITA_MultiProgram_K[]			= "　　＊＊　Ｍｕｌｔｉ　Ｐｒｏｇｒａｍ　Ｌｉｓｔ　＊＊　　";	/* 6/28 FX.ENG */
#else
CUB	PITA_MultiProgram_K[]			= "                                                        ";
#endif

/* 機器設定リスト */
#if ( PRO_MAKER == FX )
CUB PITA_MachineSettings_K[]		= "　＊＊　Ｃｕｓｔｕｍ　Ｐｒｅｓｅｔｓ　＊＊　";	/* 6/28 FX.ENG */
#else
CUB PITA_MachineSettings_K[]		= "                                            ";
#endif

/* 機能リスト */
#if ( PRO_MAKER == FX )
CUB PITA_ProgramList_K[]			= "Ｆｕｎｃｔｉｏｎ　Ｔｒｅｅ　　　";
#else
CUB PITA_ProgramList_K[]			= "                                ";
#endif

/* 通信予約リスト */
#if ( PRO_MAKER == FX )
CUB PITA_ComReservedList_K[]		= "＊＊Ｐｅｎｄｉｎｇ　Ｊｏｂｓ　Ｌｉｓｔ＊＊";	 /* 6/28 FX.ENG */
#else
CUB PITA_ComReservedList_K[]		= "                                          ";
#endif

/* 親展者リスト */
#if ( PRO_MAKER == FX )
CUB PITA_SecureMailBList_K[]		= " 　　＊＊　Ｍａｉｌｂｏｘ　Ｌｉｓｔ　＊＊　　 ";
#else
CUB PITA_SecureMailBList_K[]		= "                                              ";
#endif

/* カバーページプリント */
#if ( PRO_MAKER == FX )
CUB PITA_CoverPageMes_K[]			= " 　＊＊　Ｆａｘ　Ｍｅｓｓａｇｅ　＊＊　 ";
#else
CUB PITA_CoverPageMes_K[]			= "                                        ";
#endif

/* 親展受信通知 */
#if ( PRO_MAKER == FX )
CUB PITA_SecureMailNotice_K[]		= "ＭａｉｌｂｏｘＲｅｐｏｒｔ";
#else
CUB PITA_SecureMailNotice_K[]		= "                          ";
#endif

/* 親展原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB PITA_ErasedDocuments_K[]		= "Ｒｃｖ　Ｍａｉｌｂｏｘ　Ｅｒａｓｅｄ";
#else
CUB PITA_ErasedDocuments_K[]		= "                                    ";
#endif

/* 代行受信消去通知 */
#if ( PRO_MAKER == FX )
CUB PITA_ErasedDocumemts_K[]		= " Ｒｃｖ　Ｄｏｃｕｍｅｎｔ　Ｅｒａｓｅｄ ";	/* 6/28 FX.ENG */
#else
CUB PITA_ErasedDocumemts_K[]		= "                                        ";
#endif

/* 通信予約消去通知 */
#if ( PRO_MAKER == FX )
CUB PITA_ErasedCommands_K[]			= "Ｐｅｎｄｉｎｇ Ｊｏｂ Ｅｒａｓｅｄ";	/* 10/18 FX.ENG */
#else
CUB PITA_ErasedCommands_K[]			= "                                  ";
#endif

/* チェックメッセージ　メモリオーバー */
#if ( PRO_MAKER == FX )
CUB PITA_CheckMessage_K[]			= "Ｓｅｎｄ　Ｆａｉｌ　Ｒｅｐ";
#else
CUB PITA_CheckMessage_K[]			= "                          ";
#endif
CUB PITA_MemoryOver_K[]				= "                      ";
CUB PITA_PcMemoryOver_K[]			= "ＰＣ　Ｍｅｍｏｒｙ　Ｏｖｅｒ";

/* Ｔ３０モニタ */
CUB PITA_T30Monitor_K[]				= "                                    ";

/* ﾎﾟｰﾘﾝｸﾞ原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB PITA_ErasePollDoc_K[]			= " 　　Ｐｏｌｌｅｄ　Ｄｏｃ．Ｅｒａｓｅｄ　　 ";
#else
CUB PITA_ErasePollDoc_K[]			= "                                            ";
#endif

/* 一括送信原稿リスト */
CUB	PITA_BatchTxDocList_K[]			= "                                            ";

/* 一括送信原稿消去通知 */
CUB	PITA_EraseBatchTxDoc_K[]		= "                                        ";

/* 一括送信ＢＯＸリスト */
CUB	PITA_BatchTxBoxList_K[]			= "                                              ";

/* 部門管理リスト*/
#if ( PRO_MAKER == FX )
CUB	PITA_DepartCodeList_K[]			= "　　　　　　＊＊　Ａｃｃｏｕｎｔ　Ｌｉｓｔ　＊＊　　　　　　";	/* 6/28 FX.ENG */
#else
CUB	PITA_DepartCodeList_K[]			= "                                                            ";
#endif

/* 料金表 */
CUB	PITA_CostBase_K[]				= "                        ";	/* POPLAR_Hのみ */

/* プログラムリスト */
#if ( PRO_MAKER == FX )
CUB	PITA_ProgOnetouchDir_K[]		= "　　　　＊＊　Ｐ　Ｏｎｅ　Ｔｏｕｃｈ　Ｌｉｓｔ　＊＊　　　　";
#else
CUB	PITA_ProgOnetouchDir_K[]		= "                                                            ";
#endif

/* モニターレポート */
CUB	PITA_MonitorReport_K[]			= "                            ";

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
CUB PITA_F_CodeBox_List_K[]			= "　　＊＊　ＦコードＢＯＸリスト　＊＊　　";

/* サブアドレス原稿消去通知 */
CUB PITA_Del_F_CodeBoxDoc_Notice_K[]	= "　　ＦコードＢＯＸゲンコウ  ショウキョ  ツウチ　　";

/* サブアドレスBOX蓄積原稿リスト */
CUB PITA_F_CodeDoc_List_K[]			= "　　＊＊  ＦコードＢＯＸチクセキゲンコウリスト  ＊＊　　　";

/* サブアドレス受信通知 */
CUB PITA_F_CodeBoxRsv_Notice_K[]	= "　　Ｆコードジュシン  ツウチ　　　";
#endif

/* ダイレクトメール防止ダイヤルリスト */
CUB	PITA_BlockJunkList_K[]			= "＊＊　Ｂｌｏｃｋ　Ｊｕｎｋ　Ｆａｘ　Ｌｉｓｔ　＊＊　";

/* サービスレポート */
CUB	PITA_ServiceReport_K[]			= "＊＊　Ｓｅｒｖｉｃｅ　Ｒｅｐｏｒｔ　＊＊";

/* 暗号化受信通知リスト */
CUB PITA_CipherReceiveNotice_K[]	= "スクランブル受信通知                    ";

/* キーブックリスト */
CUB PITA_KeyBookList_K[]			= "  ＊＊    　キーバンク    　＊＊  ";	/* 98/01/12 By M.Kuwahara */

/* キーリスト */
CUB PITA_KeyWordList_K[]			= "＊＊　キーワードリスト　＊＊";

/* 暗号化受信消去通知 */
/*CUB	PITA_EraseScrambleRxDoc_K[]		= "スクランブル原稿消去通知";*/
CUB	PITA_EraseScrambleRxDoc_K[]		= "Ｅｒａｓｅｄ　Ｓｃｒａｍｂｌｉｎｇ　Ｄｏｃ．";

/* 消耗品発注票 */
 #if defined(JPN)
CUB PITA_ConsumerOrderSheet_K[]		= "　　消耗品発注票　　　";   /* modified by honda 1997/11/12 */
 #else
CUB PITA_ConsumerOrderSheet_K[]		= "消耗品発注票　　　　　";
 #endif

 #if (PRO_COST == ENABLE)				/* 料金管理 *//* Add By O.Kimoto 1997/11/17 */
/* 料金表 */
CUB	PITA_DialingCode[]		= "        ";
CUB	PITA_Daytime[]			= "                ";
CUB	PITA_Night[]			= "                ";
CUB	PITA_Midnight[]			= "                ";
CUB	PITA_Slash10[]			= "   ";
CUB	PITA_WithinArea[]		= "        ";
 #endif

 #if (PRO_LINENUMBER == TWICE_LINE)
/* 内蔵回線のラベルです。 By O.Kimoto 1997/12/20 */
CUB PITA_LineName[][8]			= {
									/* 	"123456789" */
										"Std.",
										"Ext.",
										"Opt."
										};
 #endif


#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
CUB	PITA_INF_MailComList_K[]	= "＊＊　Ｒｅｓｅｒｖｅｄ　Ｍａｉｌ　Ｃｏｍｍａｎｄｓ　＊＊";
CUB	PITA_INF_SettingList_K[]	= "＊＊　Ｕｓｅｒ　Ｓｅｔｔｉｎｇ　Ｌｉｓｔ　＊＊";
CUB	PITA_INF_ErasedMailList_K[]	= "＊＊　Ｅｒａｓｅｄ　Ｍａｉｌｓ　＊＊";
CUB PITA_INF_ErasedCommand_K[]	= "＊＊　Ｅｒａｓｅｄ　Ｍａｉｌ　Ｃｏｍｍａｎｄｓ　＊＊";
#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
CUB PITA_KeyMacroList_K[]	= "＊＊　キーマクロ　タイトル　リスト　＊＊";
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
CUB PITA_NumberDisplayList_K[] = "＊＊　ナンバーディスプレイ　ダイヤル　リスト　＊＊";

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
CUB PITA_NumberDisplayJournal_K[]	= "　　　　＊＊　ナンバーディスプレイ通信履歴　＊＊　　　　";
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
CUB PITA_WarpList_K[] 		= "　＊＊　ＦＡＸワープ　リスト　＊＊　　";
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
CUB PITA_EmergencyTitle_Emergency_K[] 		= " 　＊＊　緊急　＊＊ ";
CUB PITA_EmergencyTitle_Normal_K[]	 		= " 　＊＊　普通　＊＊ ";
 #endif
#endif

#endif

/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの最後に入れる) */
CUB	PITA_TAIL[]			= "";

#undef	CUB
