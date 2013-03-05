/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_WKAN.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ﾌﾟﾘﾝﾄ用固定文字列 JAPANESE (JPN) KANA/KANJI(KAN)
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\lst_def.h"

#define	CUB		CONST UBYTE

#if (PRO_CPU == SH7043) /* ワーディング先頭位置認識用 1996/07/04 T.Nose */
	#if (WORDING_1 == JAPANESE)
		CUB PWRD_1stWordingTop[] = "\0";
	#endif
	#if (WORDING_2 == JAPANESE)
		CUB PWRD_2ndWordingTop[] = "\0";
	#endif
	#if (WORDING_3 == JAPANESE)
		CUB PWRD_3rdWordingTop[] = "\0";
	#endif
#endif

/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの先頭に入れる) */
CUB	PKAN_HEAD[]				= "";

/* 送信証　受領証*/
#if defined(STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	PKAN_TransConfReport[] 	= "     ** 送信確認証 **     ";
#else
CUB	PKAN_TransConfReport[] 	= "      ** 送信証 **        ";
#endif
CUB	PKAN_RecConfReport[] 	= "      ** 受領証 **       ";
CUB	PKAN_FromTo[] 			= "--->";
CUB	PKAN_CommNo[] 			= "通信番号\000  ";
#if (PRO_COMMON_SAKAKI2 == ENABLE) /* 画質ﾓｰﾄﾞ By M.Maeda 2002/10/15 */
CUB	PKAN_CommMode[] 		= "画質ﾓｰﾄﾞ ";
#else
CUB	PKAN_CommMode[] 		= "通信ﾓｰﾄﾞ ";
#endif
CUB	PKAN_CommStartTime[] 	= "通信時間\000";
CUB	PKAN_CommPages[] 		= "通信枚数\000";
CUB	PKAN_CommResult[] 		= "通信結果\000";
#if ( PRO_MAKER == FX )
CUB	PKAN_Normal[] 			= "Standard";
CUB	PKAN_Fine[] 			= "Fine\000 ";
CUB	PKAN_SFine[] 			= "SuperFine";
CUB	PKAN_Gray[] 			= "Halftone";
#else
CUB	PKAN_Normal[] 			= "標準\000   ";
CUB	PKAN_Fine[] 			= "高画質";
CUB	PKAN_SFine[] 			= "超高画質\000";
 #if (PRO_PITNEYBOWES == ENABLE)				/* 仕向け先ＵＳＡによりマルチワーディング対象外につき英語を転用しています。*/
CUB	PKAN_Gray[] 			= "PHOTO\000  ";
CUB	PKAN_HFine[] 			= "H-FINE\000  ";	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
CUB	PKAN_HGray[] 			= "H PHOTO\000";	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
 #else
CUB	PKAN_Gray[] 			= "写真\000   ";
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)/* SANYO仕様の追加 2000/02/24 N.Kondo *//* Add by Y.Kano 2003/07/11 */
CUB	PKAN_Fine_S[] 			= "細かい";
CUB	PKAN_SFine_S[] 			= "精細\000    ";
#endif
CUB	PKAN_Pages[] 			= "ﾍﾟｰｼﾞ\000 ";
CUB	PKAN_FaxD[]				= "Fax:";

/* 通信管理レポート「送信」「受信」*/
CUB	PKAN_TransmitJournal[]	= "送信            ";
CUB	PKAN_RecieveJournal[]	= "受信            ";
CUB	PKAN_ContNo[]			= "通番\000";
CUB	PKAN_RemoteFrom[]		= "相手先名";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題があるので、変更時は注意すること */
CUB	PKAN_RemoteTo[]			= "相手先名";
#if (PRO_COMMON_SAKAKI2 == ENABLE) || defined(STOCKHM2)/* 画質ﾓｰﾄﾞ By M.Maeda 2002/10/15 *//* Added by SMuratec C.P 2004/06/21 for stockholm2 */
CUB	PKAN_Mode[] 			= " 画質ﾓｰﾄﾞ";
#else
CUB	PKAN_Mode[] 			= "  ﾓｰﾄﾞ\000  ";
#endif
#if ( PRO_MAKER == FX )
CUB	PKAN_Start[] 			= "Transmit";	/* 6/26 FX.ENG */
#else
CUB	PKAN_Start[] 			= "開始日時";
#endif
CUB	PKAN_Received[] 		= "開始日時";
CUB	PKAN_Time[] 			= " 時間 ";
CUB	PKAN_Page[] 			= "枚数";
CUB	PKAN_Code[] 			= "部門";
CUB	PKAN_Result[] 			= " 結果\000 ";
CUB	PKAN_Note[] 			= " 備考\000";
CUB	PKAN_AltNo[] 			= "(転送先)";
CUB	PKAN_Secure[] 			= "親展\000  ";
CUB	PKAN_Relay[] 			= "中継\000  ";
CUB	PKAN_Polling[] 			= "ﾎﾟｰﾘﾝｸﾞ";
CUB	PKAN_DbPolling[] 		= "検索ﾎﾟｰ";
CUB	PKAN_Manual[] 			= "手動\000  ";
CUB	PKAN_RelayedTxReport[]	= "不達\000  ";
#if defined(USA) || defined(US2) || defined(AUS)	/*追加↓*/
CUB	PKAN_FIP_Tx[] 			= "FIP_Tx ";
CUB	PKAN_FIP_Rx[] 			= "FIP_Rx ";
CUB	PKAN_FIP_Poll[] 		= "FIP_Pol";
CUB	PKAN_FIP_Sec[] 			= "FIP_Sec";
#else												/*追加↑*/
CUB	PKAN_FIP_Tx[] 			= "FIP_Tx ";
CUB	PKAN_FIP_Rx[] 			= "FIP_Rx ";
CUB	PKAN_FIP_Poll[] 		= "FIP_Pol";
CUB	PKAN_FIP_Sec[] 			= "FIP_Sec";
#endif
CUB	PKAN_BrdCast[]	 		= "同報\000  ";
CUB	PKAN_Ok[] 				= "O K";
/* Fｺｰﾄﾞ */
CUB	PKAN_SUB_Tx[]			= "Fｺｰﾄﾞ\000 ";
CUB PKAN_SEP_Rx[]			= "F ﾎﾟｰ\0 ";
CUB PKAN_SUB_Rx[]			= "Fｺｰﾄﾞ\000 ";
/* ｽｸﾗﾝﾌﾞﾙ */
CUB	PKAN_Cipher_Tx[]		= "ｽｸﾗﾝﾌﾞﾙ";
CUB	PKAN_Cipher_Rx[]		= "ｽｸﾗﾝﾌﾞﾙ";

/* 短縮ダイヤルリスト */
CUB	PKAN_TeleDirectory[] 	= "   ** ﾀﾝｼｭｸﾀﾞｲﾔﾙ ﾘｽﾄ **   ";
CUB	PKAN_No[]				= "No.";
#if ( PRO_MAKER == FX )
CUB	PKAN_RemoteLocation[]	= "     Name\000      ";	/* 6/28 FX.ENG */
CUB	PKAN_TeleNumber[] 		= "  Telephone No.   ";		/* 6/28 FX.ENG */
CUB	PKAN_GroupNumber[] 		= "Group No.       ";		/* 6/28 FX.ENG */
#else
CUB	PKAN_RemoteLocation[]	= "    相手先名\000   ";
CUB	PKAN_TeleNumber[] 		= "    ﾀﾞｲﾔﾙ番号\000    ";
CUB	PKAN_GroupNumber[] 		= "ｸﾞﾙｰﾌﾟNo\000       ";	/* ANZUのみ */
#endif
CUB	PKAN_Cost[]				= "  料金  ";	/* POPLAR_Hのみ */

/* 属性リスト */
CUB PKAN_AttributeList[]	= "** ｿﾞｸｾｲﾘｽﾄ **";
CUB PKAN_Attribute[]		= "属性\0";

/* ワンタッチダイヤルリスト */
CUB	PKAN_OneDirectory[] 	= "   ** ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ﾘｽﾄ **   ";

/* プログラムリスト */
CUB	PKAN_DelyTime[] 		= "指定日時";
CUB	PKAN_Option[]			= "応用機能";
CUB	PKAN_NotTime[] 			= "--:--";

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/26 By M.Kuwahara */
CUB	PKAN_PRG_Onetouch[]		= "ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ﾘｽﾄ        ";
CUB	PKAN_PRG_Speed[]		= "短縮ﾀﾞｲﾔﾙ ﾘｽﾄ         ";
CUB	PKAN_PRG_Program[]		= "ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ﾘｽﾄ      ";

#if (0)
** /* 通常の親展のオペレーションと統一させる。 By O.Kimoto 1999/02/09 */
** CUB	PKAN_PRG_SecureBox[]	= "親展BOXﾘｽﾄ            ";
#else
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
CUB	PKAN_PRG_SecureBox[]	= "親展者ﾘｽﾄ             ";
 #else
CUB	PKAN_PRG_SecureBox[]	= "親展BOXﾘｽﾄ            ";
 #endif
#endif

CUB	PKAN_PRG_ComReserve[]	= "通信予約ﾘｽﾄ           ";
 #if defined(SAKAKI) && defined(JP0) /* 2002/08/26 By M.Maeda */
CUB	PKAN_PRG_Journal[]		= "通信管理ﾚﾎﾟｰﾄ(送受信) ";
 #else
  #if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
CUB	PKAN_PRG_Journal[]		= "通信管理ﾌﾟﾘﾝﾄ         ";
CUB	PKAN_PRG_DailyReport[]	= "通信日報ﾌﾟﾘﾝﾄ         ";
  #else
CUB	PKAN_PRG_Journal[]		= "通信管理ﾚﾎﾟｰﾄ         ";
  #endif
 #endif
CUB	PKAN_PRG_Group[]		= "ｸﾞﾙｰﾌﾟ ﾘｽﾄ            ";
CUB	PKAN_PRG_Setting[]		= "機器設定ﾘｽﾄ           ";
CUB	PKAN_PRG_Message[]		= "ﾒｯｾｰｼﾞ ﾘｽﾄ            ";
CUB	PKAN_PRG_CostBase[]		= "料金表                ";
CUB	PKAN_PRG_DepartCode[]	= "部門管理ﾘｽﾄ           ";
CUB	PKAN_PRG_BatchBox[]		= "一括送信BOXﾘｽﾄ        ";
CUB	PKAN_PRG_BatchDoc[]		= "一括送信原稿ﾘｽﾄ       ";
CUB	PKAN_PRG_F_CodeBox[]	= "FｺｰﾄﾞBOXﾘｽﾄ           ";
CUB	PKAN_PRG_F_CodeDoc[]	= "FｺｰﾄﾞBOX蓄積原稿ﾘｽﾄ   ";
CUB	PKAN_PRG_BlockJunk[]	= "ﾀﾞｲﾚｸﾄﾒｰﾙ防止ﾀﾞｲﾔﾙ ﾘｽﾄ";
CUB	PKAN_PRG_ND_Dial[]		= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲﾀﾞｲﾔﾙ ﾘｽﾄ";
CUB	PKAN_PRG_ND_Journal[]	= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ履歴     ";
#if defined(SAKAKI) && defined(JP0) /* 2002/08/26 By M.Maeda */
CUB	PKAN_PRG_Warp[]			= "ﾌｧｸｽﾜｰﾌﾟ ﾘｽﾄ          ";
CUB	PKAN_PRG_JournalTx[]	= "通信管理ﾚﾎﾟｰﾄ(送信)   ";
CUB	PKAN_PRG_JournalRx[]	= "通信管理ﾚﾎﾟｰﾄ(受信)   ";
#else
CUB	PKAN_PRG_Warp[]			= "FAXﾜｰﾌﾟ ﾘｽﾄ           ";
#endif
CUB PKAN_ListName[]			= "ﾘｽﾄ名\0   ";
CUB PKAN_CommReserved[]		= "通信予約";
CUB PKAN_List[]				= "ﾘｽﾄ\0";
CUB PKAN_DocStore[]			= "原稿蓄積";
#endif

/* グループリスト */
CUB	PKAN_GroupDirectory[] 	= "  ** ｸﾞﾙｰﾌﾟ ﾘｽﾄ **   ";
#if ( PRO_MAKER == FX )
CUB	PKAN_Location[]			= "  Name\000  ";
#else
CUB	PKAN_Location[]			= "相手先名\000";
#endif

/* 機器設定リスト */
CUB	PKAN_MachineSettings[] 	= "   ** ｷｷｾｯﾃｲ ﾘｽﾄ **   ";
#if ( PRO_MAKER == FX )
CUB	PKAN_SubscriberID[] 	= "SendHeader";
#else
CUB	PKAN_SubscriberID[] 	= "発信元名\000 ";
#endif
CUB	PKAN_SubscriberKanaID[]	= "発信元名(ｶﾅID)  ";
#if ( PRO_MAKER == FX )
CUB	PKAN_SubscriberNb[] 	= "自局ＩＤ\000   ";
CUB	PKAN_JournalAutoPrt[] 	= "通信管理記録自動\000";
CUB	PKAN_SecureDocHold[] 	= "親展受信記憶期間";
#else
CUB	PKAN_SubscriberNb[] 	= "ﾌｧｸｽ番号\000   ";
CUB	PKAN_JournalAutoPrt[] 	= "通信管理記録自動\000";
 #if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	PKAN_SecureDocHold[] 	= "親展受信記憶期間\000";
 #else
CUB	PKAN_SecureDocHold[] 	= "親展受信記憶期間";
 #endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif
#if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/07/21 */
CUB	PKAN_PhoneType[]		= "通信回線(加入)\000";
CUB	PKAN_EXTPhoneType[]		= "通信回線(警電)\000";
#else
CUB	PKAN_PhoneType[]		= "通信回線\000 ";
#endif

#if ( PRO_MAKER == FX )
CUB	PKAN_ConfReport[]		= "ﾓﾆﾀｰﾚﾎﾟｰﾄ\000 ";
CUB	PKAN_ScannerWidth[]		= "読取ｻｲｽﾞ\000    ";
CUB	PKAN_PrimaryMode[]		= "画質\000         ";
CUB	PKAN_Contrast[]			= "濃度\000         ";
CUB	PKAN_DialingPause[]		= "ﾎﾟｰｽﾞ時間\000   ";
#else
#if defined(STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	PKAN_ConfReport[]		= "送信確認証\000 ";
#else
CUB	PKAN_ConfReport[]		= "通信証\000    ";
#endif
CUB	PKAN_ScannerWidth[]		= "読取ｻｲｽﾞ\000    ";
CUB	PKAN_PrimaryMode[]		= "優先文字ｻｲｽﾞ\000 ";
CUB	PKAN_Contrast[]			= "優先原稿濃度\000 ";
CUB	PKAN_DialingPause[]		= "ﾎﾟｰｽﾞ時間\000   ";
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)/* SANYO仕様の追加 2000/02/24 N.Kondo *//* Add by Y.Kano 2003/07/11 */
CUB	PKAN_Contrast_S[]		= "優先原稿濃淡\000 ";
 #endif
#endif
#if !defined(KEISATSU)		/* 警察FAX Modify by SMuratec 夏 2005/07/21 */
CUB	PKAN_RinggingTimes[]	= "呼出ﾍﾞﾙ回数\000  ";
#endif
#if ( PRO_MAKER == FX )
CUB	PKAN_ReductionRate[]	= "Reduction %   ";	/* 6/28 FX.ENG */
#else
CUB	PKAN_ReductionRate[]	= "ﾌﾟﾘﾝﾄ縮小率\000  ";
#endif
CUB	PKAN_EcmMode[]			= "ECM ﾓｰﾄﾞ";
CUB	PKAN_CopyProtect[]		= "ｺﾋﾟｰ禁止\000   ";
/*CUB	PKAN_RemoteDiagnostic[]	= "ﾘﾓｰﾄ診断\000        ";*/	/* ﾜｰﾃﾞｨﾝｸﾞの変更 97/03/10 M.kuwahara */
CUB	PKAN_RemoteDiagnostic[]	= "ｻｰﾋﾞｽﾓｰﾄﾞ\000       ";
CUB	PKAN_RedialTimes[]		= "ﾘﾀﾞｲﾔﾙ回数/間隔\000 ";
CUB	PKAN_Holdmelody[]		= "保留ﾒﾛﾃﾞｨ\000  ";
CUB	PKAN_Passcode[]			= "ﾊﾟｽｺｰﾄﾞ\000";
CUB	PKAN_CloseNetwork[]		= "閉域通信\000      ";
CUB	PKAN_SilentOperation[]	= "ｻｲﾚﾝﾄ ｵﾍﾟﾚｰｼｮﾝ\000 ";	/* JPN以外 */
#if ( PRO_MAKER == FX )
CUB	PKAN_SecurityTx[]		= "ﾊﾟｽﾜｰﾄﾞ送信\000     ";
CUB	PKAN_BlockjunkFax[]		= "DM禁止\000         ";
#else
CUB	PKAN_SecurityTx[]		= "ﾊﾟｽﾜｰﾄﾞ送信\000     ";
CUB	PKAN_BlockjunkFax[]		= "ﾀﾞｲﾚｸﾄﾒｰﾙ\000      ";
#endif
CUB	PKAN_RecieveMode[]		= "受信ﾓｰﾄﾞ\000   ";
#if ( PRO_MAKER == FX )
CUB	PKAN_PageCompound[]		= "Combine Pages    ";	/* 9/17 FX.ENG */
#else
CUB	PKAN_PageCompound[]		= "ﾍﾟｰｼﾞ合成\000       ";
#endif
CUB	PKAN_SortingCopy[]		= "ｿ-ﾃｨﾝｸﾞ ｺﾋﾟ-";		/* POPLAR_Lのみ */
CUB	PKAN_Rs232c[]			= "RS232C    ﾎﾞｰﾚｰﾄ ";
CUB	PKAN_Stamp[]			= "済ｽﾀﾝﾌﾟ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/26 */
CUB	PKAN_MemoryTx[]			= "ﾒﾓﾘｰ送信\000      ";
#else
CUB	PKAN_MemoryTx[]			= "ﾒﾓﾘ送信\000       ";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	PKAN_RelayedRelayTx[]	= "中々継            ";

#if (PRO_PANEL == KANJI)
/* ＰＯＰＬＡＲ＿ＨはＬＣＤに待機モードを表示していないので、機器設定リストに表示させます。 By O.Kimoto 1998/03/02 */
 #if (PRO_DIALIN_SW == ENABLE) /* By H.Fujimura 2002/07/11 */
CUB	PKAN_DialIn[]			= "ﾀﾞｲﾔﾙｲﾝ          ";
 #else
CUB	PKAN_DialIn[]			= "ﾀﾞｲﾔﾙｲﾝ\0         ";
 #endif
CUB	PKAN_DialIn_Item1[]		= "ﾌｧｸｽ/電話1/電話2";
CUB	PKAN_DialIn_Item2[]		= "ﾌｧｸｽ/電話1      ";
#else
CUB	PKAN_DialIn[]			= "ﾀﾞｲﾔﾙｲﾝ ﾌｧｸｽ/電話";	/* (JPN) */
#endif

CUB	PKAN_BellTime[]			= "ﾍﾞﾙ時間";			/* (JPN) */
CUB	PKAN_RingMastr[]		= "ﾘﾝｸﾞﾏｽﾀｰ ｾｯﾄ     ";
CUB	PKAN_CopyReduction[]	= "ｺﾋﾟｰ縮小率       ";
CUB	PKAN_PaperSize[]		= "記録ﾍﾟｰﾊﾟｰｻｲｽﾞ   ";	/* ANZUのみ */
CUB PKAN_PC_PaperManual[]	= "PCﾌﾟﾘﾝﾄ手差し用紙";	/* ANZUのみ */
CUB	PKAN_PaperType[]		= "記録紙ﾀｲﾌﾟ     ";	/* SAKAKIのみ */
CUB	PKAN_ToneLine[] 		= "ﾌﾟｯｼｭ";
#if ( PRO_MAKER == FX )
CUB	PKAN_Pps10[] 			= "10pps";	/* 6/28 FX.ENG */
CUB	PKAN_Pps20[] 			= "20pps";	/* 6/28 FX.ENG */
#else
CUB	PKAN_Pps10[] 			= "10PPS";
CUB	PKAN_Pps20[] 			= "20PPS";
#endif
#if defined(STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	PKAN_TxConf[]			= "送信確認証\000 ";
#else
CUB	PKAN_TxConf[]			= "送信証\000 ";
#endif
CUB	PKAN_RxConf[]			= "受領証\000  ";
CUB	PKAN_A4[] 				= "A4";
CUB	PKAN_B4[] 				= "B4";
CUB	PKAN_A3[] 				= "A3";
CUB	PKAN_F4[] 				= "F4";
#if (PRO_PITNEYBOWES == ENABLE)			
CUB PKAN_LETTER[]			= "LTR";	/* ＰＢ仕様の為追加 By S.Fukui Aug. 25,1998 */
CUB PKAN_LEDGER[]			= "LD";		/* ＰＢ仕様の為追加 By S.Fukui Aug. 25,1998 */
#endif
#if ( PRO_MAKER == FX )
CUB	PKAN_Dark[] 			= "こく\000 ";
CUB	PKAN_NormalDark[] 		= "ふつう";
CUB	PKAN_Light[] 			= "うすく\000";
#else
CUB	PKAN_Dark[] 			= "濃く\000 ";
CUB	PKAN_NormalDark[] 		= "普通\000 ";
CUB	PKAN_Light[] 			= "薄く\000  ";
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)/* SANYO仕様の追加 2000/02/24 N.Kondo *//* Add by Y.Kano 2003/07/11 */
CUB	PKAN_Dark_S[] 			= "薄い\000 ";
CUB	PKAN_Light_S[] 			= "濃い\000  ";
#endif
CUB	PKAN_MinuteMark[] 		= "分\000    ";
CUB	PKAN_SecondMark[] 		= "秒\000 ";
#if ( PRO_MAKER == FX )
CUB	PKAN_Try[] 				= "Times";
#else
CUB	PKAN_Try[] 				= "回\000  ";
#endif
CUB	PKAN_Attemps[] 			= "回\000     ";
CUB	PKAN_On[] 				= "ON\000";
CUB	PKAN_Off[] 				= "OFF";
CUB	PKAN_Mode1[]			= "ﾓｰﾄﾞ1";
CUB	PKAN_Mode2[]			= "ﾓｰﾄﾞ2";
CUB	PKAN_Mode3[]			= "ﾓｰﾄﾞ3";
CUB	PKAN_P100[] 			= "100%";
CUB	PKAN_P97[] 				= "97%";
CUB	PKAN_P91[] 				= "91%";
CUB	PKAN_P81[] 				= "81%";
CUB	PKAN_P75[] 				= "75%";
#if ( PRO_MAKER == FX )
CUB	PKAN_ThValue00mm[] 		= "Thrshld   00 mm";	/* 6/28 FX.ENG */
CUB	PKAN_TelFax[] 			= "Tel/Fax\000 ";
CUB	PKAN_Tel[] 				= "Tel\000";
CUB	PKAN_Fax[] 				= "Fax\000";
CUB	PKAN_AnsFax[] 			= "Ans/Fax\000";	/* 6/28 FX.ENG */
#else
CUB	PKAN_ThValue00mm[] 		= "しきい値  00 mm";
CUB	PKAN_TelFax[] 			= "電話ﾌｧｸｽ\000";
CUB	PKAN_Tel[] 				= "電話";
CUB	PKAN_Fax[] 				= "ﾌｧｸｽ";
CUB	PKAN_AnsFax[] 			= "留守ﾌｧｸｽ";
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec K.W.Q 2003/11/28 */
CUB	PKAN_DialInRx[]			= "ﾀﾞｲﾔﾙｲﾝ\0 ";
#endif

CUB	PKAN_FaxTel[]			= "ﾌｧｸｽ電話\000";	/**	追加 For ANZU By H.Hirao 1996/05/21	*/
CUB	PKAN_Bps300[] 			= "300";
CUB	PKAN_Bps600[] 			= "600";
CUB	PKAN_Bps1200[] 			= "1200";
CUB	PKAN_Bps2400[] 			= "2400";
CUB	PKAN_Bps4800[] 			= "4800";
CUB	PKAN_Bps9600[] 			= "9600";
CUB	PKAN_Bps19200[] 		= "19200";
CUB	PKAN_BpsVariable[] 		= "自動\000   ";		/** 追加 For POPLA By M.Kuwahara 1997/03/05 */
CUB	PKAN_None[] 			= "NONE";
CUB	PKAN_Odd[] 				= "ODD";
CUB	PKAN_Even[] 			= "EVEN";
CUB	PKAN_S1bit[] 			= "1bit";
CUB	PKAN_S2bit[] 			= "2bit";
CUB	PKAN_P7bit[] 			= "7bit";
CUB	PKAN_P8bit[] 			= "8bit";
CUB	PKAN_Days[] 			= "日\000 ";
CUB	PKAN_Auto[] 			= "自動\000";
CUB	PKAN_Pattern[]			= "ﾊﾟﾀｰﾝ  :";	/* (USA) */
CUB	PKAN_Letter[]			= "Letter\0";
CUB	PKAN_Legal[]			= "Legal\0";
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* '95.07/20 By K.Watanabe *//* by K.Watanabe 2004/10/12 */
CUB	PKAN_RxAlarm[]			= "Audible Alarm";
CUB	PKAN_MercuryPause[]		= "Prefix Pause ";/*追加 Mercury Pause -> Prefix Pause */
CUB PKAN_MercuryNumber[]	= "ﾀﾞｲﾔﾙ ﾌﾟﾚﾌｨｸｽ 番号";/* Added by SMuratec C.P 2004/07/08 for prefix */
#endif
#if ( PRO_MAKER == FX )
CUB	PKAN_MesageTrans[]		= "ｺﾒﾝﾄ            ";
#else
CUB	PKAN_MesageTrans[]		= "ﾒｯｾｰｼﾞ送信      ";
#endif
CUB	PKAN_RemoteSecurityRx[]	= "ｾｷｭﾘﾃｨ受信    ";	/* 変更 97/03/10 M.Kuwahara */
CUB	PKAN_NormalPaper[]		= "普通紙\000   ";	/* SAKAKIのみ */
CUB PKAN_ThermalPaper[]		= "感熱紙\000   ";	/* SAKAKIのみ */
CUB	PKAN_DepartmentProtect[]= "部門管理ﾌﾟﾛﾃｸﾄ\000   ";	/* 追加 For ANZU By H.Hirao Feb 29,1996 *//* 97/03/10 M.Kuwahara */
CUB	PKAN_Department[]		= "部門管理\000 ";			/* 追加 For ANZU By H.Hirao Feb 29,1996 */	/* 97/03/10 M.Kuwahara */
CUB	PKAN_PINAccessMode[]	= "PINﾓｰﾄﾞ\0       ";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#if defined(USA)
CUB	PKAN_DayLightSaving[]	= "Daylight Saving";		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#endif

#if (PRO_PANEL == KANJI)
CUB	PKAN_OperationProtect[]	= "操作 ﾌﾟﾛﾃｸﾄ\000      ";	/* 変更 「ｵﾍﾟﾚｰｼｮﾝ」-> 「操作」 By O.Kimoto 1998/03/02 */
#else
CUB	PKAN_OperationProtect[]	= "ｵﾍﾟﾚｰｼｮﾝ ﾌﾟﾛﾃｸﾄ\000  ";	/* 追加 For ANZU By H.Hirao Feb 29,1996 */ /* 97/03/10 M.Kuwahara */
#endif
#if (PRO_REMOTE_RX == ENABLE)
CUB	PKAN_RemoteReceive[]	= "ﾘﾓｰﾄ受信\000         ";	/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
CUB	PKAN_OnHookReceive[]	= "ｵﾝﾌｯｸ受信\000        ";	/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif

/* PRO_MULTI_LINE */
/* 基本的に下記ワーディングは
** 		見出し用：半角16文字
** 		内容用  ：半角 8文字
** とします。
** by O.Kimoto 1997/07/10
*/
						/*	   12345678901234567890 */
CUB PKAN_MultiTxRxType[]	= "送信･受信\000      ";
CUB PKAN_TxRx[]				= "送受信\000 ";
CUB PKAN_Tx[]				= "送信専用";
CUB PKAN_Rx[]				= "受信専用";
CUB PKAN_MultiLineType[]	= "外線･内線設定\000  ";
CUB PKAN_PstnLine[]			= "外線\000   ";
CUB PKAN_PbxLine[]			= "内線\000   ";
CUB PKAN_PstnAccessNumber[]	= "外線接続番号 :\000 ";
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/10/10 */
CUB PKAN_LineNumber[]		= "回線:\000          ";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題（終端をNULLで判断していない）があるので、ﾜｰﾃﾞｨﾝｸﾞを最大11ﾊﾞｲﾄ・ｺﾛﾝの位置固定(日本語参照)にすること *//*  By O.Kimoto 1997/07/10 */
#else /* !defined (KEISATSU) */
CUB PKAN_LineNumber[]		= "回線番号   :\000   ";	/* 注）ﾜｰﾃﾞｨﾝｸﾞの使用方法に問題（終端をNULLで判断していない）があるので、ﾜｰﾃﾞｨﾝｸﾞを最大11ﾊﾞｲﾄ・ｺﾛﾝの位置固定(日本語参照)にすること *//*  By O.Kimoto 1997/07/10 */
#endif /* defined (KEISATSU) */
/** CUB	PKAN_SubscriberKanaID[]	= "発信元名(ｶﾅID)  "; */
/** CUB	PKAN_PhoneType[]		= "通信回線\000 "; */

#if (PRO_MULTI_LINE == ENABLE)	/*  By O.Kimoto 1997/01/06 */
CUB	PKAN_AddErrorMessage[4][31] = {
					/* 123456789012345678901234567890 */
					  "回線設定を確認して下さい      ",	/** D.0.10 */
					  "回線の属性を確認して下さい    ",	/** D.0.11 */
					  "内線･外線設定を確認して下さい ",	/** D.0.12 */
					  "内線･外線設定を確認して下さい "	/** D.0.13 */
					  };
#endif

/* 記録紙サイズ */
CUB	PKAN_Paper_A5[]			= "A5_P\0  ";
 #if defined(USA)
CUB	PKAN_Paper_Letter[]		= "Letter\0";
 #else
CUB	PKAN_Paper_Letter[]		= "Ltr_P\0 ";
 #endif
 #if defined(USA)
CUB	PKAN_Paper_A4[]			= "A4_P\0  ";
 #else
CUB	PKAN_Paper_A4[]			= "A4\0    ";
 #endif
 #if defined(USA) || defined(TWN) /* 1998/01/09 Y.Matsukuma */
CUB	PKAN_Paper_Legal[]		= "Legal\0 ";
 #else
CUB	PKAN_Paper_Legal[]		= "Legal_P";
 #endif
CUB	PKAN_Paper_B5R[]		= "B5R_P\0 ";
CUB	PKAN_Paper_B4[]			= "B4_P\0  ";
CUB	PKAN_Paper_A3[]			= "A3_P\0  ";
CUB	PKAN_Paper_A4R[]		= "A4R_P\0 ";
CUB	PKAN_Paper_LetterR[]	= "LtrR_P\0";
 #if defined(TWN) || defined(AUS)	/* 1998/01/08 Y.Matsukuma */
CUB	PKAN_Paper_F4[]			= "F4\0    ";
 #else
CUB	PKAN_Paper_F4[]			= "F4_P\0  ";
 #endif
CUB	PKAN_Paper_A5R[]		= "A5R_P\0 ";
CUB	PKAN_Paper_Postcard[]	= "Post_P\0";
CUB	PKAN_Paper_LD[]			= "Ld_P\0  ";
CUB	PKAN_Paper_GLetterR[]	= "GLtrR_P";
CUB	PKAN_Paper_ExecutiveR[]	= "ExeR_P\0";
CUB	PKAN_Paper_InvoiceR[]	= "InvR_P\0";
CUB	PKAN_Paper_GLegal[]		= "GLegl_P";
CUB	PKAN_Paper_GLetter[]	= "GLtr_P\0";
CUB	PKAN_Paper_Card[]		= "Card_P\0";
CUB	PKAN_Paper_Executive[]	= "Exe_P\0 ";
CUB	PKAN_Paper_B5[]			= "B5_P\0  ";
CUB	PKAN_Paper_C5[]			= "C5_P\0  ";
CUB	PKAN_Paper_HalfLetter[]	= "HLtr_P\0";
CUB	PKAN_Paper_Invoice[]	= "Inv_P\0 ";
CUB	PKAN_Paper_B6[]			= "B6_P\0  ";
CUB	PKAN_Paper_DL[]			= "DL_P\0  ";
CUB	PKAN_Paper_CM10[]		= "CM10_P\0";
CUB	PKAN_Paper_A6[]			= "A6_P\0  ";
CUB	PKAN_Paper_Monarch[]	= "Mnc_P\0 ";
CUB	PKAN_Paper_35[]			= "3x5_P\0 ";
CUB	PKAN_Paper_User[]		= "User_P\0";

/* 記録紙サイズ POPLAR用 */
CUB	PKAN_PaperSize_A5[]			= "A5\0    ";
CUB	PKAN_PaperSize_Letter[]		= "Letter\0";
CUB	PKAN_PaperSize_A4[]			= "A4\0    ";
CUB	PKAN_PaperSize_Legal[]		= "Legal\0 ";
CUB	PKAN_PaperSize_B5R[]		= "B5R\0   ";
CUB	PKAN_PaperSize_B4[]			= "B4\0    ";
CUB	PKAN_PaperSize_A3[]			= "A3\0    ";
CUB	PKAN_PaperSize_A4R[]		= "A4R\0   ";
CUB	PKAN_PaperSize_LetterR[]	= "LtrR\0  ";
CUB	PKAN_PaperSize_F4[]			= "F4\0    ";
CUB	PKAN_PaperSize_A5R[]		= "A5R\0   ";
CUB	PKAN_PaperSize_Postcard[] 	= "Post\0  ";
CUB	PKAN_PaperSize_LD[]			= "Ld\0    ";
CUB	PKAN_PaperSize_GLetterR[]	= "GLtrR\0 ";
CUB	PKAN_PaperSize_ExecutiveR[]	= "ExeR\0  ";
CUB	PKAN_PaperSize_HalfLetterR[]= "HLtrR\0 ";
/*  CUB	PKAN_PaperSize_InvoiceR[]	= "InvR\0  ";  *//* modified by honda 1997/11/14 */
CUB	PKAN_PaperSize_GLegal[]		= "GLegl\0 ";
CUB	PKAN_PaperSize_GLetter[]	= "GLtr\0  ";
CUB	PKAN_PaperSize_Card[]		= "Card\0  ";
CUB	PKAN_PaperSize_Executive[]	= "Exe\0   ";
CUB	PKAN_PaperSize_B5[]			= "B5\0    ";
CUB	PKAN_PaperSize_C5[]			= "C5\0    ";
CUB	PKAN_PaperSize_HalfLetter[]	= "HLtr\0  ";
CUB	PKAN_PaperSize_Invoice[]	= "Inv\0   ";
CUB	PKAN_PaperSize_B6[]			= "B6\0    ";
CUB	PKAN_PaperSize_DL[]			= "DL\0    ";
CUB	PKAN_PaperSize_CM10[]		= "CM10\0  ";
CUB	PKAN_PaperSize_A6[]			= "A6\0    ";
CUB	PKAN_PaperSize_Monarch[]	= "Mnc\0   ";
CUB	PKAN_PaperSize_35[]			= "3x5\0   ";
CUB	PKAN_PaperSize_User[]		= "User\0  ";

/* メモリスイッチ */
#if ( PRO_MAKER == FX )
CUB	PKAN_Machine_P[] 		= "Parameter    ";
#else
 #if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	PKAN_Machine_P[] 		= "[機器ﾊﾟﾗﾒｰﾀｰ]";
 #else
CUB	PKAN_Machine_P[] 		= "[機器 ﾊﾟﾗﾒｰﾀ]";
 #endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/26 */
CUB	PKAN_Memory_S[] 		= "[ ﾒﾓﾘｰｽｲｯﾁ ]\000";
#else
CUB	PKAN_Memory_S[] 		= "[ ﾒﾓﾘ ｽｲｯﾁ ]\000";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
CUB	PKAN_Uniq_S[]			= "[ 固有ｽｲｯﾁ ]\000";	/* 追加 For ANZU By H.Hirao Mar.28.1996 *//* ﾜｰﾃﾞｨﾝｸﾞ変更 97/03/10 M.K */
CUB	PKAN_BitNumber[] 		= "7654 3210";
CUB	PKAN_Default[] 			= "　初期値 ";
CUB	PKAN_AutoSet[] 			= "　設定値 ";

/* POPLA追加 -- メモリスイッチの追加 */
CUB PKAN_MainteSwitch[]		= "[ 保守 ｽｲｯﾁ ]";

/* 機能リスト */
CUB	PKAN_ProgramList[]		= "ｷﾉｳ ﾘｽﾄ         ";

/* 通信予約リスト */
CUB	PKAN_ComReservedList[] 	= "  ** ﾂｳｼﾝﾖﾔｸ ﾘｽﾄ **  ";

/* 親展者登録リスト */
CUB	PKAN_SecureMailBList[]	= "** ｼﾝﾃﾝｼｬ ﾘｽﾄ **       ";
#if ( PRO_MAKER == FX )
CUB	PKAN_UserName[] 		= "  Name    ";	/* 6/28 FX.ENG */
#else
CUB	PKAN_UserName[] 		= "親展者名  ";
#endif
CUB	PKAN_Box[] 				= "Box";

/* カバーページプリント */
CUB	PKAN_CoverPageMes[] 	= "** ｿｳｼﾝ ｱﾝﾅｲｼｮｳ **  ";	/* 右端 - 2ﾊﾞｲﾄの後、ｾﾝﾀﾘﾝｸﾞ */

/* 親展受信通知 */
CUB	PKAN_SecureMailNotice[] = "ｼﾝﾃﾝｼﾞｭｼﾝ ﾂｳﾁ";

/* 親展原稿消去通知*/
CUB	PKAN_ErasedDocuments[] 	= "ｼﾝﾃﾝｼﾞｭｼﾝ ｼｮｳｷｮﾂｳﾁ";

/* 代行受信消去通知*/
CUB	PKAN_ErasedDocumemts[] 	= "ﾀﾞｲｺｳｼﾞｭｼﾝ ｼｮｳｷｮ ﾂｳﾁ";

/* 通信予約消去通知*/
CUB	PKAN_ErasedCommands[] 	= "ﾂｳｼﾝﾖﾔｸ ｼｮｳｷｮ ﾂｳﾁ";
#if ( PRO_MAKER == FX )
CUB	PKAN_MemHoldDate[]		= "Print mailbox by   ";
#else
CUB	PKAN_MemHoldDate[]		= "(親展原稿記憶期間)\000";
#endif

/* チェックメッセージ　メモリオーバー*/
CUB	PKAN_CheckMessage[] 	= " ﾁｪｯｸ ﾒｯｾｰｼﾞ ";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	PKAN_MemoryOver[]		= " ﾒﾓﾘｰｵｰﾊﾞｰ ";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PKAN_PcMemoryOver[]		= " PC ﾒﾓﾘｰｵｰﾊﾞｰ ";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
#elif (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/26 */
CUB	PKAN_MemoryOver[]		= " ﾒﾓﾘｰ ｵｰﾊﾞｰ";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PKAN_PcMemoryOver[]		= " PC ﾒﾓﾘｰ ｵｰﾊﾞｰ";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
#else
CUB	PKAN_MemoryOver[]		= " ﾒﾓﾘ ｵｰﾊﾞｰ ";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
CUB	PKAN_PcMemoryOver[]		= " PC ﾒﾓﾘ ｵｰﾊﾞｰ ";	/* 注）見出しのﾜｰﾃﾞｨﾝｸﾞなので、途中にNULLを入れない事 */
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB	PKAN_ErrorPages[] 		= "< ｴﾗｰ ﾍﾟｰｼﾞ >:";

/* Ｔ３０モニタ */
CUB	PKAN_T30Monitor[]		= "  ** T30 ﾓﾆﾀ **   ";
CUB	PKAN_TxFrame[]			= "TxFrame";
CUB	PKAN_RxFrame[]			= "RxFrame";
CUB	PKAN_Datalong[]			= "D A T A";
CUB	PKAN_Rs144[]			= "144";
CUB	PKAN_Rs120[]			= "120";
CUB	PKAN_Rs96[]				= " 96";
CUB	PKAN_Rs72[]				= " 72";
CUB	PKAN_Rs48[]				= " 48";
CUB	PKAN_Rs24[]				= " 24";
CUB	PKAN_V17[]				= "V17";
CUB	PKAN_V33[]				= "V33";
CUB	PKAN_V29[]				= "V29";
CUB	PKAN_V27[]				= "V27";
CUB	PKAN_MH[]				= " MH";
CUB	PKAN_MR[]				= " MR";
CUB	PKAN_MMR[]				= "MMR";
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
CUB	PKAN_JBG[]				= "JBG";
#endif
CUB	PKAN_A5[]				= "A5";
CUB	PKAN_A6[]				= "A6";
CUB	PKAN_Wait20[]			= "20";
CUB	PKAN_Wait40[]			= "40";
CUB	PKAN_Wait10[]			= "10";
CUB	PKAN_Wait5[]			= " 5";
CUB	PKAN_Wait0[]			= " 0";
CUB	PKAN_ModeNR[]			= "N";
CUB	PKAN_ModeFN[]			= "F";
CUB	PKAN_ModeSF[]			= "S";
CUB	PKAN_ModeHF[]			= "H";

CUB	PKAN_Main[]				= "MAN";
CUB	PKAN_Reset[]			= "Res";
CUB	PKAN_Error[]			= "Err";
CUB	PKAN_Now[]				= "Now";
CUB	PKAN_DpramTx[]			= "Tx";
CUB	PKAN_DpramRx[]			= "Rx";

/* 工場ファンクションリスト */
CUB	PKAN_FunctionList[]		= "ｺｳｼﾞｮｳ ﾌｧﾝｸｼｮﾝ ﾘｽﾄ  ";
CUB	PKAN_LedTest[]			= "LED ﾃｽﾄ             ";
CUB	PKAN_LcdTest[]			= "LCD ﾃｽﾄ             ";
CUB	PKAN_Pane1keytest[]		= "ﾊﾟﾈﾙｷｰ ﾃｽﾄ          ";
CUB	PKAN_Rs232cTest[]		= "RS232C ﾃｽﾄ          ";
CUB	PKAN_SramCheck[]		= "SRAM ﾁｪｯｸ           ";
CUB	PKAN_DramCheck[]		= "DRAM ﾁｪｯｸ           ";
CUB	PKAN_RTCTest[]			= "RTC ﾃｽﾄ             ";

/* オンラインモニタ */
#if ( PRO_CLASS1 == ENABLE )
CUB	PKAN_OnLineMonitor[]	= "< Online Monitor > ";
CUB	PKAN_OnLineTx[]			= "TX";
CUB	PKAN_OnLineRx[]			= "RX";
CUB	PKAN_OnLineData[]		= "Data";
CUB	PKAN_Speed[]			= "Speed";
CUB	PKAN_Command[]			= "Cmd";
CUB	PKAN_Response[]			= "Res";
CUB	PKAN_Abort[]			= "Abt";
#endif

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
CUB PKAN_F_CodeBox_List[]	= " ** FｺｰﾄﾞBOXﾘｽﾄ **  ";
CUB PKAN_BoxName[]			= " ﾎﾞｯｸｽ名\0";
CUB PKAN_SubAddress[]		= " SUBｱﾄﾞﾚｽ番号\0";
CUB PKAN_CommPasscode[]		= " 通信ﾊﾟｽﾜｰﾄﾞ番号\0 ";
CUB PKAN_Kind[]				= "種別\0";
CUB PKAN_NoticeBoard[]		= "掲示板\0";
CUB PKAN_RecvProtect[]		= "受信禁止\0 ";
CUB PKAN_Replace[]			= "上書き\0";
CUB PKAN_RxPrint[]			= "同時ﾌﾟﾘﾝﾄ\0";
CUB PKAN_TransErase[]		= "送信原稿消去\0    ";

#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
CUB PKAN_RelayName[] 		= "配信先";
CUB PKAN_PutSubscriber[] 	= "発信元";
CUB PKAN_Avail[]			= "外付け";
CUB	PKAN_NoTTI[]			= "付けない";
CUB	PKAN_SUB_Relay[]		= "F中継  ";	/* 1998/09/25 By M.Kuwahara */
CUB	PKAN_SUB_Secure[]		= "F親展  ";	/* 1998/09/28 By M.Kuwahara */
#endif

#if (PRO_FCODE_KIND_DISPLAY == ENABLE)
CUB	PKAN_SUB_Bulletin[]		= "F掲示板";	/* 1998/09/28 By M.Kuwahara */
#endif

/* サブアドレス原稿消去通知 */
CUB PKAN_Del_F_CodeBoxDoc_Notice[]	= " FｺｰﾄﾞBOXｹﾞﾝｺｳ ｼｮｳｷｮ ﾂｳﾁ ";
CUB PKAN_BoxLocation[]		= "相手先名";
CUB PKAN_ThisBoxErased[]	= "Fｺｰﾄﾞﾎﾞｯｸｽ原稿が消去されました．．．．";

/* サブアドレスＢＯＸ蓄積原稿リスト */
CUB PKAN_DocumentsNo[]		= "ﾌｧｲﾙ番号";
CUB PKAN_F_CodeDoc_List[]	= " ** FｺｰﾄﾞBOXﾁｸｾｷｹﾞﾝｺｳﾘｽﾄ ** ";

/* サブアドレス受信通知 */
CUB PKAN_F_CodeBoxRsv_Notice[]	= " Fｺｰﾄﾞｼﾞｭｼﾝ ﾂｳﾁ  ";
CUB PKAN_F_CodeReci[]		= "Fｺｰﾄﾞﾎﾞｯｸｽ原稿を受信しました";
CUB PKAN_F_ReciDocMemory[]	= "(親展原稿記憶期間)\0  ";
#endif

/* ダイレクトメール防止ダイヤルリスト */
CUB	PKAN_BlockJunkList[]	= "** ﾀﾞｲﾚｸﾄﾒｰﾙ防止ﾀﾞｲﾔﾙﾘｽﾄ **";
CUB	PKAN_TelNum[]			= " ﾀﾞｲﾔﾙ番号\0";

/* サービスレポート */
CUB	PKAN_ServiceReport[]	= "  ** ｻｰﾋﾞｽﾚﾎﾟｰﾄ **  ";

/* ポーリング原稿消去通知 */
CUB	PKAN_ErasePollDoc[]		= "ﾎﾟｰﾘﾝｸﾞｹﾞﾝｺｳ ｼｮｳｷｮ ﾂｳﾁ";

/* 一括送信原稿リスト */
CUB	PKAN_BatchTxDocList[]	= "                              ";

/* 一括送信ＢＯＸリスト */
CUB	PKAN_BatchTxBoxList[]	= "                                ";

CUB PKAN_Batch[]			= "一括 ";
CUB PKAN_BoxNo[]			= "Box No.\000   ";

/* 暗号化受信通知リスト */
CUB PKAN_CipherReceiveNotice[]	= " ｽｸﾗﾝﾌﾞﾙ ｼﾞｭｼﾝ ﾂｳﾁ  ";
CUB PKAN_ReceiveNo[]		= "受信No.\0  ";
CUB PKAN_KeyClue[]			= "ｷｰﾜｰﾄﾞのﾋﾝﾄ ";
CUB PKAN_KeyWordClue[]		= "ヒント  ";

/* キーリスト、キーブックリスト */
CUB PKAN_KeyBookList[]		= " ** ｷｰﾊﾞﾝｸ **  ";	/* 98/01/12 By M.Kuwahara */
CUB PKAN_KeyWordList[]		= "  ** ｷｰﾜｰﾄﾞﾘｽﾄ **  ";
CUB PKAN_KeyName[]			= "ｷｰﾜｰﾄﾞの名前";
CUB PKAN_Key[]				= "ｷｰﾜｰﾄﾞ";

/* 暗号化受信消去通知 */
CUB	PKAN_EraseScrambleRxDoc[]	= "ｽｸﾗﾝﾌﾞﾙｹﾞﾝｺｳ ｼｮｳｷｮ ﾂｳﾁ";

/* 消耗品発注票 */
#if defined(JPN)
CUB PKAN_ConsumerOrderSheet[]	= "ｼｮｳﾓｳﾋﾝ ﾊｯﾁｭｳﾋｮｳ\0          ";
 #if defined(POPLAR_F)	/* 2000/01/25 */
CUB PKAN_ToOrder[]				= "販売店\0";
CUB PKAN_FromOrder[]			= "お客様\0";
 #else
CUB PKAN_ToOrder[]				= "発注先\0";
CUB PKAN_FromOrder[]			= "発注元\0";
 #endif
CUB PKAN_CustomerCode[]			= "得意先ｺｰﾄﾞ\0    ";		/* JPNは最大10byte */
CUB PKAN_DistributorName[]		= "社名\0             ";	/* JPNは最大10byte */
CUB PKAN_CustomerName[]			= "社名\0             ";	/* JPNは最大10byte */
CUB PKAN_Section[]				= "部課名\0          ";		/* JPNは最大10byte */
CUB PKAN_ChargeName[]			= "ご担当者名";
CUB PKAN_ModelName[]			= "ﾓﾃﾞﾙ名";
CUB PKAN_OrderItem[]			= "発注品目\0 ";
CUB PKAN_TonerOrder1[]			= "ﾄﾅｰ   x 1\0       ";		/* 注）ﾄﾅｰ =5byte, x 1の位置固定（日本語参照） */
CUB PKAN_DrumOrder1[]			= "ﾄﾞﾗﾑ  x 1\0       ";		/* 注）ﾄﾞﾗﾑ=5byte, x 1の位置固定（日本語参照） */
CUB PKAN_SeirialNumber[]		= "ｼﾘｱﾙNo.\0            ";	/* JPNは最大10byte */
CUB PKAN_InstallDate[]			= "設置日\0          ";		/* JPNは最大10byte */
CUB PKAN_BlockLetters[]			= "               ";		/* JPNは未使用 */
CUB PKAN_Remarks[]				= "備考   ";
CUB PKAN_OrderTonerChange[]		= "トナーの交換が必要になりました。";
CUB PKAN_OrderTonerDrumChange[]	= "トナー／ドラムの交換が必要になりました。";
CUB PKAN_OrderSheet[]			= "お手数ですが、この用紙を使って、下記へＦＡＸでご注文下さい。";
#elif defined(US1)			/* orderbythonda1998/11/11 */
CUB PKAN_ConsumerOrderSheet[]	= "PITNEY BOWES OFFICE SYSTEMS 4100";
CUB PKAN_ConsumerOrderSheet2[]	= "SUPPLIES ORDER FORM";
CUB PKAN_ToOrder[]				= "To:\0   ";				/* 海外は最大6文字 */
CUB PKAN_FromOrder[]			= "From:\0 ";				/* 海外は最大6文字 */
CUB PKAN_CustomerCode[]			= "Customer's Code";
CUB PKAN_DistributorName[]		= "Distributor's Name";
CUB PKAN_CustomerName[]			= "Customer's Name\0  ";
CUB PKAN_Section[]				= "Address(Ship to:)";
CUB PKAN_ChargeName[]			= "Signature ";
CUB PKAN_ModelName[]			= "Model ";
CUB PKAN_OrderItem[]			= "Item Needed: ";
CUB PKAN_TonerOrder1[]			= "Toner Cartridge x       PCS";		/* 注）Toner=5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PKAN_DrumOrder1[]			= "Drum Unit       x       PCS";		/* 注）Drum =5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PKAN_SeirialNumber[]		= "Serial No.";
CUB PKAN_InstallDate[]			= "Installation Date";
CUB PKAN_BlockLetters[]			= "Print Name :";
CUB PKAN_Remarks[]				= "Customer Account No. & Ship to Address";
CUB PKAN_OrderTonerChange[]		= "Replace toner with a new one.   ";	/* JPNのみ */
CUB PKAN_OrderTonerDrumChange[]	= "Your machine's display indicates that either the Toner Cartridge or Drum Unit";
CUB PKAN_OrderTonerDrumChange2[]= "requires replacement.";
CUB PKAN_OrderSheet[]			= "To order replacements by phone, call               , or fill out this form";
CUB PKAN_OrderSheet2[]			= "and fax it to               .";
#else
CUB PKAN_ConsumerOrderSheet[]	= "   < ｼｮｳﾓｳﾋﾝ ﾊｯﾁｭｳﾋｮｳ >    ";
CUB PKAN_ToOrder[]				= "発注先\0";				/* 海外は最大6文字 */
CUB PKAN_FromOrder[]			= "発注元\0";				/* 海外は最大6文字 */
CUB PKAN_CustomerCode[]			= "得意先ｺｰﾄﾞ\0    ";
CUB PKAN_DistributorName[]		= "社名\0             ";
CUB PKAN_CustomerName[]			= "社名\0             ";
CUB PKAN_Section[]				= "部課名\0          ";
CUB PKAN_ChargeName[]			= "ご担当者名";
CUB PKAN_ModelName[]			= "ﾓﾃﾞﾙ名";
CUB PKAN_OrderItem[]			= "発注品目\0 ";
CUB PKAN_TonerOrder1[]			= "ﾄﾅｰ   x 1\0       ";		/* 注）Toner=5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PKAN_DrumOrder1[]			= "ﾄﾞﾗﾑ  x 1\0       ";		/* 注）Drum =5byte, xの位置固定, PCS=3byte（英語参照） */
CUB PKAN_SeirialNumber[]		= "ｼﾘｱﾙNo.\0            ";
CUB PKAN_InstallDate[]			= "設置日\0          ";
CUB PKAN_BlockLetters[]			= "               ";
CUB PKAN_Remarks[]				= "備考   ";
CUB PKAN_OrderTonerChange[]		= "トナーの交換が必要になりました。";	/* JPNのみ */
CUB PKAN_OrderTonerDrumChange[]	= "トナー／ドラムの交換が必要になりました。";
CUB PKAN_OrderSheet[]			= "お手数ですが、この用紙を使って、下記へＦＡＸでご注文下さい。";
#endif

/* 簡易料金管理リスト */
#if (PRO_DEPART_NEW_LIST == ENABLE)
CUB PKAN_DepartTimeList[]	= "   ** ﾌﾞﾓﾝﾍﾞﾂ ｼﾞｶﾝｶﾝﾘ ﾘｽﾄ **  ";  /* added by thonda 1997/12/02 */
#endif

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
CUB PKAN_KeyMacroList[] 		= "** ｷｰﾏｸﾛ ﾀｲﾄﾙ ﾘｽﾄ **";
CUB PKAN_NoTitle[] 				= "ﾀｲﾄﾙ未登録";
CUB PKAN_Title[] 				= "ﾀｲﾄﾙ";
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
CUB PKAN_NumberDisplayList[]	= "** ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾀﾞｲﾔﾙ ﾘｽﾄ **";
CUB PKAN_NumberDisplay[]		= "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ";
CUB PKAN_NoConnect[]			= "未接続";
CUB PKAN_Tel1Connect[]			= "PHONE1   ";
 #if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/24 */
CUB PKAN_Tel2Connect[]			= "TEL\0     ";
 #else
CUB PKAN_Tel2Connect[]			= "PHONE2   ";
 #endif		/* End of (defined (KEISATSU)) */
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
CUB PKAN_ND_Warp[]				= "ND ﾜｰﾌﾟ\0";
 #endif

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
CUB PKAN_NumberDisplayJournal[]	= "** ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾂｳｼﾝ ﾘﾚｷ **";
CUB PKAN_SubscriberNumber[]		= "発信者番号";
CUB PKAN_NoNotice[]				= "非通知\0  ";
CUB PKAN_OutOfDisp[]			= "表示圏外";
CUB PKAN_PublicTel[]			= "公衆電話\0 ";
CUB PKAN_FNetCall[]				= "F網\0 ";
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
 #if defined(SAKAKI) && defined(JP0) /* By M.Maeda 2002/10/18 */
CUB PKAN_WarpList[]			 	= " ** ﾌｧｸｽﾜｰﾌﾟ ﾘｽﾄ **";
CUB PKAN_AppointedTime[]		= "指定時刻";
CUB PKAN_WarpFunction[]			= "ﾌｧｸｽﾜｰﾌﾟ";
 #else
CUB PKAN_WarpList[]			 	= " ** FAXﾜｰﾌﾟ ﾘｽﾄ ** ";
CUB PKAN_AppointedTime[]		= "指定時刻";
CUB PKAN_WarpFunction[]			= "FAXﾜｰﾌﾟ\0";
 #endif
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1999/01/25 */
CUB	PKAN_WarpWeek[][4]			= {
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
CUB	PKAN_Year_Eng[12][4] = {
	"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
	};

/* プログラムリスト */
CUB	PKAN_ProgOnetouchDir[] 	= "    ** ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ﾘｽﾄ **    ";

/* 親展受信通知 */
#if ( PRO_MAKER == FX )
CUB	PKAN_SecureMailReci[] 	= "Mailbox Documents are received.         ";
#else
CUB	PKAN_SecureMailReci[] 	= "親展原稿を受信しました                  ";
#endif

/* 親展受信消去通知 */
CUB	PKAN_ThisSecMailEra[] 	= "親展受信原稿が消去されました．．．．．．";

/* 代行受信消去通知 */
#if ( PRO_MAKER == FX )
CUB	PKAN_ThisMemErased[] 	= "Received documents are erased.\000         ";	/* 6/28 FX.ENG */
#else
CUB	PKAN_ThisMemErased[] 	= "代行受信原稿が消去されました．．．．．．";
#endif

/* 通信予約消去通知 */
#if ( PRO_MAKER == FX )
CUB	PKAN_ThisComErased[] 	= "Pending jobs are erased.\000                 ";	/* 6/28 FX.ENG */
#else
#if (PRO_DRAM_BACKUP == ENABLE)			/*94/11/28 ↓ By jmasuda*/
/*CUB	PKAN_ThisComErased[] 	= "Commands were erased.  \000                  ";*/
CUB	PKAN_ThisComErased[] 	= "通信予約コマンドが消去されました．．．．．";
#else									/*94/11/28 ↑ By jmasuda*/
CUB	PKAN_ThisComErased[] 	= "通信予約コマンドが消去されました．．．．．";
#endif
#endif

/* チェックメッセージ */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/26 */
CUB	PKAN_MryOverFeeder[]	= "フィーダ送信して下さい\000               ";
CUB	PKAN_SecurityMemOver[]	= "メモリーが一杯です セキュリティ受信原稿をプリントして下さい\0               ";/*追加*/
#else
CUB	PKAN_MryOverFeeder[]	= "フィーダ送信して下さい               ";
CUB	PKAN_SecurityMemOver[]	= "メモリが一杯です セキュリティ受信原稿をプリントして下さい\0                 ";/*追加*/
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* セキュリティ受信をONにする。メモリーオーバーするまで受信を行う。チェックメッセージが印字されるが、内容が一部間違っている。 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec K.W.Q 2003/10/20 */
CUB	PKAN_SecurityOperation1[]	= "操作：機能→ワンタッチ１１→２→セットを押し";
#else
CUB	PKAN_SecurityOperation1[]	= "操作：機能→ワンタッチＯ→２→セットを押し";
#endif

CUB	PKAN_SecurityOperation2[]	= "      ４桁のプロテクトコードを入力して下さい";

/* ポーリング原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB	PKAN_PollErase[]		= "Polled documents are erased.\000                  ";	/* 6/28 FX.ENG */
#else
CUB	PKAN_PollErase[]		= "ポーリング原稿が消去されました．．．．．　　　 ";
#endif
CUB	PKAN_DbPollErase[]		= "検索ポーリング原稿が消去されました．．．　　　　　　";

/* 一括送信原稿リスト */
CUB	PKAN_IndexNo[]			= "  受付番号   ";

/* 一括送信原稿消去通知 */
CUB	PKAN_BatchTxDocErase[]	= "一括送信原稿が消去されました．．．．．．";

/* 連続ポーリングコマンド消去通知 */
CUB	PKAN_ContinuousPollingErase[] = "連続ポーリング予約が消去されました．．．．．      ";/* 1996/10/18 Eguchi */

/* 暗号化受信原稿消去通知 */
CUB	PKAN_ScrambleRxErase[]		= "スクランブル原稿が消去されました．．．．．     ";

/*通信結果ﾒｯｾｰｼﾞ*/
#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 李 2005/11/10 */
CUB	PKAN_ResultName[9][31] = {  "相手側機を確認して下さい\000     ",
								"受信原稿を確認して下さい\000     ",
#if ( PRO_MAKER == FX )
								"Tray again.\000                  ",
								"Dial again.\000                  ",
#else
								"もう一度送信して下さい\000       ",
								"もう一度ダイヤルして下さい\000   ",
#endif
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/26 */
								"メモリーオーバーしました\000     ",
#else
								"メモリオーバーしました\000       ",
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
#if (PRO_MAKER == FX)	/* By H.Y 1994/12/20 */
								"ダイヤル番号が登録されてません",
								"停止しました\000                 ",
#else
								"ダイヤル番号が登録されてません",
								"停止しました\000                 ",	/* 1998/10/14 H.Yoshikawa */
#endif
								"通信強制中断しました\000         ",
								"\000                             " };
#else /* !defined (KEISATSU) */
CUB	PKAN_ResultName[8][31] = {  "相手側機を確認して下さい\000     ",
								"受信原稿を確認して下さい\000     ",
#if ( PRO_MAKER == FX )
								"Tray again.\000                  ",
								"Dial again.\000                  ",
#else
								"もう一度送信して下さい\000       ",
								"もう一度ダイヤルして下さい\000   ",
#endif
#if (PRO_KEYPANEL == PANEL_STOCKHM2) || (PRO_UI_WORDING == ENABLE)	/* ワーディング修正 by Y.Kano 2004/08/10 *//* by K.Watanabe 2004/10/26 */
								"メモリーオーバーしました\000     ",
#else
								"メモリオーバーしました\000       ",
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
#if (PRO_MAKER == FX)	/* By H.Y 1994/12/20 */
								"ダイヤル番号が登録されてません",
								"停止しました\000                 ",
#else
								"ダイヤル番号が登録されてません",
								"停止しました\000                 ",	/* 1998/10/14 H.Yoshikawa */
#endif
								"\000                             " };
#endif /* defined (KEISATSU) */
#if (PRO_MAKER == FX)	/* By H.Y 1994/12/20 */
CUB	PKAN_ResultChain[LST_ERR_CODE_MAX] = {
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
CUB	PKAN_ResultChain[LST_ERR_CODE_MAX] = {
							'D','F','A','C','A',		/*0*/
							'G','A','A','A','C',        /*5*/
							'C','B','A','A','A',        /*10*/
							'C','A','A','G','A',        /*15*/	/* 2000/02/06 Y.Murata R.1.4をG */
							'A','A','A','B','A',        /*20*/
							'E','A','A','A','A',		/*25*/
							'A','A','A','H','C',		/*30*/
							'G','C','C',' ',' ' }; 		/*35*/
 #else
CUB	PKAN_ResultChain[LST_ERR_CODE_MAX] = {
							'D','F','A','C','A',		/*0*/
							'G','A','A','A','C',        /*5*/	/* T.1.4のワーディングをH->G By O.Kimoto 2002/10/24 */
							'C','B','A','A','A',        /*10*/
							'C','A','A','G','A',        /*15*/	/* R.1.4のワーディングをH->G By O.Kimoto 2002/10/24 */
							'A','A','A','B','A',        /*20*/
							'E','A','A','A','A',		/*25*/
							'A','A','A','H','C',		/*30*/
							'G','C','C',' ',' ' }; 		/*35*/	/* D.0.3のワーディングをH->G By O.Kimoto 2002/10/24 */
 #endif
#endif
/*PKAN17_ResultChain[]の'A'がPKAN_ResultName[][]の一番目のﾒｯｾｰｼﾞに対応する*/
CUB	PKAN_ResultCode[LST_ERR_CODE_MAX][7] = {
						"D.0.2", "D.0.6", "T.1.1", "T.1.2", "T.1.3",	/*0*/
						"T.1.4", "T.2.1", "T.2.2", "T.2.3", "T.3.1",	/*5*/
						"T.4.1", "T.4.2", "T.4.3", "T.5.1", "T.5.2",	/*10*/
						"T.5.3", "R.1.1", "R.1.2", "R.1.4", "R.2.3",	/*15*/
						"R.3.1", "R.3.3", "R.3.4", "R.4.1", "R.4.2",	/*20*/
						"R.4.4", "R.5.1", "R.5.2", "D.0.7", "T.4.4",	/*25*/
						"R.2.1", "R.3.2", "R.3.5", "R.4.5", "D.0.1",	/*30*/
						"D.0.3", "D.0.8", "R.1.3", "", "" };			/*35*/
/*最後の項目は必ず""としておく必要あり*/
/*PKAN_ResultCode[]がPKAN_ResultChain[]に対応する*/

#if (PRO_ROTATE == ENABLE)				/* ＤＰＲＡＭ経由の回転受信 */
					/*	   12345678901234567890 */
CUB PKAN_RotateMargin[]	= "回転しきい値\000   ";
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
CUB PKAN_INF_AddressList[]		= "     ** ﾒｰﾙｱﾄﾞﾚｽ ﾘｽﾄ **     ";
CUB PKAN_INF_GroupList[]		= "   ** ﾒｰﾙｸﾞﾙｰﾌﾟ ﾘｽﾄ **    ";
CUB	PKAN_INF_MailComList[]		= "    ** ﾒｰﾙﾂｳｼﾝﾖﾔｸ ﾘｽﾄ **    ";
CUB	PKAN_INF_SettingList[]		= "  ** ﾕｰｻﾞｰｾｯﾃｲ ﾘｽﾄ **  ";
CUB	PKAN_INF_ErasedMailList[] 	= "** ﾀﾞｲｺｳｼﾞｭｼﾝﾒｰﾙ ｼｮｳｷｮﾂｳﾁ **";
CUB PKAN_INF_ErasedCommand[]	= "** ﾒｰﾙﾂｳｼﾝﾖﾔｸ ｼｮｳｷｮﾂｳﾁ ** ";
CUB PKAN_INF_Address[]			= "ﾒｰﾙ ｱﾄﾞﾚｽ\000  ";
CUB PKAN_INF_Group[]			= "ﾒｰﾙ ｸﾞﾙｰﾌﾟ";
CUB PKAN_INF_UserName[]			= "ﾕｰｻﾞｰ名\000 ";
CUB PKAN_INF_ProviderName[]		= "ﾌﾟﾛﾊﾞｲﾀﾞｰ名\000 ";
CUB PKAN_INF_AccessPoint1[]		= "ｱｸｾｽﾎﾟｲﾝﾄ 1\000  ";
CUB PKAN_INF_AccessPoint2[]		= "ｱｸｾｽﾎﾟｲﾝﾄ 2\000  ";
CUB PKAN_INF_AccessPoint3[]		= "ｱｸｾｽﾎﾟｲﾝﾄ 3\000  ";
#if (0)
CUB PKAN_INF_PPPLoginID[]		= "ﾀﾞｲｱﾙｱｯﾌﾟ ﾛｸﾞｲﾝ ID";
CUB PKAN_INF_PPPPassword[]		= "ﾀﾞｲｱﾙｱｯﾌﾟ ﾛｸﾞｲﾝ ﾊﾟｽﾜｰﾄﾞ";
CUB PKAN_INF_PPPAuth[]			= "ﾊﾟｽﾜｰﾄﾞ認証方式\000       ";
CUB PKAN_INF_POPLoginID[]		= "ﾒｰﾙ ﾛｸﾞｲﾝ ID\000";
CUB PKAN_INF_POPPassword[]		= "ﾒｰﾙ ﾛｸﾞｲﾝ ﾊﾟｽﾜｰﾄﾞ\000 ";
#endif
CUB PKAN_INF_PPPLoginID[]		= "PPP ﾛｸﾞｲﾝ ID";
CUB PKAN_INF_PPPPassword[]		= "PPP ﾛｸﾞｲﾝ ﾊﾟｽﾜｰﾄﾞ ";
CUB PKAN_INF_PPPAuth[]			= "PPP 認証方式      ";
CUB PKAN_INF_POPLoginID[]		= "POP ﾛｸﾞｲﾝ ID";
CUB PKAN_INF_POPPassword[]		= "POP ﾛｸﾞｲﾝ ﾊﾟｽﾜｰﾄﾞ ";

CUB PKAN_INF_MailAddress[]		= "ﾒｰﾙ ｱﾄﾞﾚｽ\000  ";
CUB PKAN_INF_SMTPServer[]		= "SMTP ｻｰﾊﾞｰ\000";
CUB PKAN_INF_POPServer[]		= "POP ｻｰﾊﾞ-\000";
CUB PKAN_INF_PriDNSServer[]		= "ﾌﾟﾗｲﾏﾘ DNSｻｰﾊﾞ-\000  ";
CUB PKAN_INF_SecDNSServer[]		= "ｾｶﾝﾀﾞﾘ DNSｻｰﾊﾞｰ\000    ";
CUB PKAN_INF_ClientAddress[]	= "ｸﾗｲｱﾝﾄ IPｱﾄﾞﾚｽ\ ";
CUB PKAN_INF_ServerAddress[]	= "ｻｰﾊﾞ- IPｱﾄﾞﾚｽ\000  ";
CUB PKAN_INF_GatewayAddress[]	= "ｹﾞｰﾄｳｪｲ IPｱﾄﾞﾚｽ\000 ";
CUB PKAN_INF_TxRx[]				= "送信後受信\000 ";

CUB PKAN_INF_AutoRcvMail[]		= "自動受信\000        ";

CUB PKAN_INF_StartTime[]		= "開始時刻\000 ";
CUB PKAN_INF_EndTime[]			= "終了時刻\000 ";
CUB PKAN_INF_IntervalTime[]		= "実行間隔\000    ";
CUB PKAN_INF_HoldTime[]			= "保持期間\000";

CUB PKAN_INF_AutoPrint[]		= "自動ﾌﾟﾘﾝﾄ\000";

CUB PKAN_INF_ComsWereErased[]	= "メール通信予約コマンドが消去されました．．．";
CUB	PKAN_INF_MailsWereErased[]	= "代行受信メールが消去されました．．．";
CUB	PKAN_INF_Receiver[]			= "受信者名: \000";
CUB	PKAN_INF_ErrorCode[]		= "ｴﾗｰｺｰﾄﾞ\000  ";
CUB	PKAN_INF_ReTx[]				= "もう一度送信して下さい";
CUB	PKAN_INF_ReRx[]				= "もう一度受信して下さい";
CUB	PKAN_INF_DialErr[]			= "もう一度ダイアルして下さい";
CUB	PKAN_INF_ChkSetting[]		= "Check Your settings\000      ";
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB	PKAN_INF_MemErr[]			= "メモリーオーバーしました";
#else
CUB	PKAN_INF_MemErr[]			= "メモリオーバーしました";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

CUB	PKAN_INF_ChkBoard[]			= "ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞを確認して下さい";
CUB	PKAN_INF_PowerOff[]			= "電源断が発生しました";
CUB	PKAN_INF_Kind[]				= "種別\000";
CUB	PKAN_INF_To[]	 			= "To";
CUB	PKAN_INF_Tx[] 				= "Tx";
CUB	PKAN_INF_Rx[] 				= "Rx";
CUB	PKAN_INF_User[]				= "ﾕｰｻﾞｰ:";
CUB	PKAN_INF_AccessPoint[]		= "ｱｸｾｽ ﾎﾟｲﾝﾄ:\000 ";

CUB	PKAN_INF_ConnectTime[]		= "接続時間          ";
CUB	PKAN_INF_ConnectCount[]		= "接続回数     ";

CUB	PKAN_MailReceptionReport[]	= "＊＊　Ｍａｉｌ親展受信通知　＊＊\000";
CUB	PKAN_MailSender[]			= "送信者\000";
CUB	PKAN_MailReceivedTime[]		= "受信時刻\000    ";
CUB	PKAN_MailAutoPrintTime[]	= "プリント時刻\000";
CUB	PKAN_MailRxReportState1[]	= "下記の内容のＭａｉｌを受信しました。                                   ";/*71*/
CUB	PKAN_MailRxReportState2[]	= "機能、Ｒ、２、セット　の順にキーを操作して、あなたのコード番号を入力し ";
CUB	PKAN_MailRxReportState3[]	= "これらのＭａｉｌをプリントして下さい。                                 ";
CUB	PKAN_MailRxReportState4[]	= "受信Ｍａｉｌは\"プリント時刻\"を経過すると自動的にプリントされます。         ";

/*追加 1998/5/25 Eguchi*/
CUB	PUSA_INF_JournalComStartTime[] = "StartTime  ";

CUB	PKAN_INF_Ok[]				= "OK\000";
CUB	PKAN_INF_Error[]			= "ERROR\000";
CUB	PKAN_INF_AutoDownLoad[]		= "自動 ﾀﾞｳﾝﾛｰﾄﾞ \000";
CUB	PKAN_INF_DeleteMail[]		= "ﾒｰﾙ 消去   \000";
CUB	PKAN_INF_AutoCheck[]		= "自動 ﾒｰﾙ ﾁｪｯｸ  \000";

CUB	PKAN_INF_MailJournal[]		= "   ** Mail Journal **   ";

#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */

/* 通信結果プリント */
#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
CUB PKAN_TransmitResult[]		= "　＊＊　送信結果　＊＊　\0";/* "** Transmit Result **\0   " 2002/09/27 翻訳 By M.Maeda *//*25(40)*/
CUB PKAN_ReceiveResult[]		= "　＊＊　受信結果　＊＊　\0";/* "** Receive Result **\0    " 2002/09/27 翻訳 By M.Maeda *//*25(40)*/
#endif

#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
/*@^s**************************************************************************
**@^1
**@^2	ﾌﾟﾘﾝﾄ用固定文字列 漢字タイトル
**@^3	漢字のﾀｲﾄﾙは、外国語/ｶﾀｶﾅのﾀｲﾄﾙと文字幅が合わせにくいため
**@^4	94/ 5/27 豊田
**@^e*************************************************************************/

/* 送信証　受領証 */
#if defined(STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/09/08 */
CUB	PKAN_TransConfReport_K[] 		= " 　　　　　　　＊＊　送信確認証　＊＊　　　　　　　 ";
#else
CUB	PKAN_TransConfReport_K[] 		= " 　　　　　　　　＊＊　送信証　＊＊　　　　　　　　 ";
#endif
CUB	PKAN_RecConfReport_K[] 			= "　　　　　　　　＊＊　受領証　＊＊　　　　　　　　";

/* 通信管理レポート｢送信｣ ｢受信｣ */
CUB PKAN_TransmitJournal_K[]		= "　　　　＊＊　送信管理レポート　＊＊　　　　";
CUB PKAN_RecieveJournal_K[]			= "　　　　＊＊　受信管理レポート　＊＊　　　　";

/* 短縮ダイヤルリスト */
#if ( PRO_MAKER == FX )
CUB	PKAN_TeleDirectory_K[]			= " 　　＊＊　Ｓｐｅｅｄ－Ｄｉａｌ　Ｌｉｓｔ　＊＊　　 ";
#else
CUB	PKAN_TeleDirectory_K[]			= "　　　　　＊＊　短縮ダイヤル　リスト　＊＊　　　　　";
#endif

/* ワンタッチダイヤルリスト */
#if ( PRO_MAKER == FX )
CUB	PKAN_OneDirectory_K[]			= " ＊＊　ＯｎｅーＴｏｕｃｈ　Ｄｉａｌ　Ｌｉｓｔ　＊＊ ";
#else
CUB	PKAN_OneDirectory_K[]			= " 　　　＊＊　ワンタッチダイヤル　リスト　＊＊　　　 ";
#endif

/* 属性リスト */
CUB PKAN_AttributeList_K[]			= "　　　　 ＊＊　属性リスト　＊＊ 　　　　";

/* グループリスト */
#if ( PRO_MAKER == FX )
CUB PKAN_GroupDirectory_K[]			= "＊＊　Ｇｒｏｕｐ　Ｄｉａｌ　Ｌｉｓｔ　＊＊";
#else
CUB PKAN_GroupDirectory_K[]			= " 　　　＊＊　グループ　リスト　＊＊　　　 ";
#endif

/* マルチプログラムリスト */
#if ( PRO_MAKER == FX )
CUB	PKAN_MultiProgram_K[]			= "　　＊＊　Ｍｕｌｔｉ　Ｐｒｏｇｒａｍ　Ｌｉｓｔ　＊＊　　";	/* 6/28 FX.ENG */
#else
CUB	PKAN_MultiProgram_K[]			= "　　　　　＊＊　マルチプログラム　リスト　＊＊　　　　　";
#endif

/* 機器設定リスト */
#if ( PRO_MAKER == FX )
CUB PKAN_MachineSettings_K[]		= " 　　　　＊＊　機能設定リスト　＊＊　　　　 ";
#else
CUB PKAN_MachineSettings_K[]		= " 　　　　＊＊　機器設定リスト　＊＊　　　　 ";
#endif

/* 機能リスト */
#if ( PRO_MAKER == FX )
CUB PKAN_ProgramList_K[]			= "Ｆｕｎｃｔｉｏｎ　Ｔｒｅｅ　　　";
#else
CUB PKAN_ProgramList_K[]			= "機能リスト　　　　　　　　　　　";
#endif

/* 通信予約リスト */
#if ( PRO_MAKER == FX )
CUB PKAN_ComReservedList_K[]		= "＊＊Ｐｅｎｄｉｎｇ　Ｊｏｂｓ　Ｌｉｓｔ＊＊";	 /* 6/28 FX.ENG */
#else
CUB PKAN_ComReservedList_K[]		= "　　　　＊＊　通信予約リスト　＊＊　　　　";
#endif

/* 親展者リスト */
#if ( PRO_MAKER == FX )
CUB PKAN_SecureMailBList_K[]		= " 　　＊＊　Ｍａｉｌｂｏｘ　Ｌｉｓｔ　＊＊　　 ";
#else
CUB PKAN_SecureMailBList_K[]		= " 　　＊＊　親展者リスト　＊＊　　　　　　　　 ";
#endif

/* カバーページプリント */
#if ( PRO_MAKER == FX )
CUB PKAN_CoverPageMes_K[]			= " 　＊＊　Ｆａｘ　Ｍｅｓｓａｇｅ　＊＊　 ";
#else
CUB PKAN_CoverPageMes_K[]			= " 　　　　＊＊　送信案内証　＊＊　　　　 ";
#endif

/* 親展受信通知 */
#if ( PRO_MAKER == FX )
CUB PKAN_SecureMailNotice_K[]		= "ＭａｉｌｂｏｘＲｅｐｏｒｔ";
#else
CUB PKAN_SecureMailNotice_K[]		= " 　　　親展受信通知　　　 ";
#endif

/* 親展原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB PKAN_ErasedDocuments_K[]		= "Ｒｃｖ　Ｍａｉｌｂｏｘ　Ｅｒａｓｅｄ";
#else
CUB PKAN_ErasedDocuments_K[]		= "　　　　　親展受信消去通知　　　　　";
#endif

/* 代行受信消去通知 */
#if ( PRO_MAKER == FX )
CUB PKAN_ErasedDocumemts_K[]		= " Ｒｃｖ　Ｄｏｃｕｍｅｎｔ　Ｅｒａｓｅｄ ";	/* 6/28 FX.ENG */
#else
CUB PKAN_ErasedDocumemts_K[]		= "　　　　　　代行受信消去通知　　　　　　";
#endif

/* 通信予約消去通知 */
#if ( PRO_MAKER == FX )
CUB PKAN_ErasedCommands_K[]			= "Ｐｅｎｄｉｎｇ Ｊｏｂ Ｅｒａｓｅｄ";	/* 10/18 FX.ENG */
#else
CUB PKAN_ErasedCommands_K[]			= " 　　　　通信予約消去通知　　　　 ";
#endif

/* チェックメッセージ　メモリオーバー */
#if ( PRO_MAKER == FX )
CUB PKAN_CheckMessage_K[]			= " 　　未送信　レポート　　 ";
#else
CUB PKAN_CheckMessage_K[]			= " 　チェック　メッセージ　 ";
#endif
#if (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ワーディング修正 by Y.Kano 2004/08/10 */
CUB PKAN_MemoryOver_K[]				= " 　メモリーオーバー　 ";
CUB PKAN_PcMemoryOver_K[]			= "　ＰＣ　メモリーオーバー　　";
#elif (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/26 */
CUB PKAN_MemoryOver_K[]				= "　メモリー　オーバー　";
CUB PKAN_PcMemoryOver_K[]			= "　ＰＣ　メモリー　オーバー　";
#else
CUB PKAN_MemoryOver_K[]				= " 　メモリ　オーバー　 ";
CUB PKAN_PcMemoryOver_K[]			= "　ＰＣ　メモリ　オーバー　　";
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* Ｔ３０モニタ */
CUB PKAN_T30Monitor_K[]				= " 　　＊＊　Ｔ３０　モニタ　＊＊　　 ";

/* ﾎﾟｰﾘﾝｸﾞ原稿消去通知 */
#if ( PRO_MAKER == FX )
CUB PKAN_ErasePollDoc_K[]			= " 　　Ｐｏｌｌｅｄ　Ｄｏｃ．Ｅｒａｓｅｄ　　 ";
#else
CUB PKAN_ErasePollDoc_K[]			= " 　　　　　ポーリング原稿消去通知　　　　　 ";
#endif

/* 一括送信原稿リスト */
CUB	PKAN_BatchTxDocList_K[]			= " 　　　＊＊　一括送信原稿リスト　＊＊　　　 ";

/* 一括送信原稿消去通知 */
CUB	PKAN_EraseBatchTxDoc_K[]		= "　　　　　一括送信原稿消去通知　　　　　";

/* 一括送信ＢＯＸリスト */
CUB	PKAN_BatchTxBoxList_K[]			= " 　　　＊＊　一括送信ＢＯＸリスト　＊＊　　　 ";

/* 部門管理リスト*/
#if ( PRO_MAKER == FX )
CUB	PKAN_DepartCodeList_K[]			= "　　　　　　＊＊　Ａｃｃｏｕｎｔ　Ｌｉｓｔ　＊＊　　　　　　";	/* 6/28 FX.ENG */
#else
CUB	PKAN_DepartCodeList_K[]			= " 　　　　　　　　＊＊　部門管理リスト　＊＊　　　　　　　　 ";
#endif

/* 料金表 */
CUB	PKAN_CostBase_K[]				= " 　＊＊　料金表　＊＊　 ";	/* POPLAR_Hのみ */

/* プログラムリスト */
#if ( PRO_MAKER == FX )
CUB	PKAN_ProgOnetouchDir_K[]		= "　　　　＊＊　Ｐ　Ｏｎｅ　Ｔｏｕｃｈ　Ｌｉｓｔ　＊＊　　　　";
#else
CUB	PKAN_ProgOnetouchDir_K[]		= "　　　　　＊＊　プログラムワンタッチ　リスト　＊＊　　　　　";
#endif

/* モニターレポート */
CUB	PKAN_MonitorReport_K[]			= " 　　モニター　レポート　　 ";	/*FX*/

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
CUB PKAN_F_CodeBox_List_K[]			= "　　＊＊　ＦコードＢＯＸリスト　＊＊　　";

/* サブアドレス原稿消去通知 */
CUB PKAN_Del_F_CodeBoxDoc_Notice_K[]	= "　　        ＦコードＢＯＸ原稿消去通知        　　";

/* サブアドレスBOX蓄積原稿リスト */
CUB PKAN_F_CodeDoc_List_K[]			= "　　    ＊＊  ＦコードＢＯＸ蓄積原稿リスト  ＊＊    　　　";

/* サブアドレス受信通知 */
CUB PKAN_F_CodeBoxRsv_Notice_K[]	= "　　    Ｆコード受信通知   　　　 ";
#endif

/* ダイレクトメール防止ダイヤルリスト */
CUB	PKAN_BlockJunkList_K[]			= "＊＊　ダイレクトメール　防止　ダイヤルリスト　＊＊　";

/* サービスレポート */
CUB	PKAN_ServiceReport_K[]			= "　　　＊＊　サービスレポート　＊＊　　　";

/* 暗号化受信通知リスト */
/*CUB PKAN_CipherReceiveNotice_K[]	= "スクランブル受信通知";	* 98/01/12 By M.Kuwahara */
CUB PKAN_CipherReceiveNotice_K[]	= "          スクランブル受信通知          ";	/* By Y.Suzuki 1998/04/24 */

/* キーブックリスト */
/*CUB PKAN_KeyBookList_K[]			= "＊＊　キーバンク　＊＊";	@* 98/01/12 By M.Kuwahara */
CUB PKAN_KeyBookList_K[]			= "      ＊＊　キーバンク　＊＊      ";	/* 98/01/12 By M.Kuwahara */

/* キーリスト */
CUB PKAN_KeyWordList_K[]			= "＊＊　キーワードリスト　＊＊";

/* 暗号化受信消去通知 */
/*CUB	PKAN_EraseScrambleRxDoc_K[]		= "スクランブル原稿消去通知";*/
CUB	PKAN_EraseScrambleRxDoc_K[]		= "          スクランブル原稿消去通知          ";/* By Y.Suzuki 1998/04/24 */

/* 消耗品発注票 */
 #if defined(JPN)
CUB PKAN_ConsumerOrderSheet_K[]		= "　　消耗品発注票　　　";   /* modified by honda 1997/11/12 */
 #else
CUB PKAN_ConsumerOrderSheet_K[]		= "消耗品発注票　　　　　";
 #endif

 #if (PRO_COST == ENABLE)				/* 料金管理 *//* Add By O.Kimoto 1997/11/17 */
/* 料金表 */
CUB	PKAN_DialingCode[]		= "市外局番";
CUB	PKAN_Daytime[]			= "  昼間(秒/10円) ";
CUB	PKAN_Night[]			= "  夜間(秒/10円) ";
CUB	PKAN_Midnight[]			= "  深夜(秒/10円) ";
CUB	PKAN_Slash10[]			= "/10";
CUB	PKAN_WithinArea[]		= "市内通話";
 #endif

 #if (PRO_LINENUMBER == TWICE_LINE)
/* 内蔵回線のラベルです。 By O.Kimoto 1997/12/20 */
#if (0)
//CUB PKAN_InternalLineName[][8]			= {
//									/* 	"123456789" */
//										"(標準):",
//										"(拡張):"
//										};
#endif
CUB PKAN_LineName[][8]			= {
									/* 	"123456789" */
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/27 */
										"加入",
										"警電",
#else /* !defined (KEISATSU) */
										"標準",
										"拡張",
#endif /* defined (KEISATSU) */
										"外付"
										};
 #endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
CUB	PKAN_INF_MailComList_K[]	= "　　　　　 ＊＊　メール通信予約　リスト　＊＊　　　　　 ";
CUB	PKAN_INF_SettingList_K[]	= "　　　 ＊＊　ユーザー設定　リスト　＊＊　　　 ";
CUB	PKAN_INF_ErasedMailList_K[]	= " ＊＊　代行受信メール消去通知　＊＊ ";
CUB PKAN_INF_ErasedCommand_K[]	= "　　　　＊＊　メール通信予約消去通知　＊＊　　　　　";
#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
CUB PKAN_KeyMacroList_K[]	= "＊＊　キーマクロ　タイトル　リスト　＊＊";
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
CUB PKAN_NumberDisplayList_K[] = "＊＊　ナンバーディスプレイ　ダイヤル　リスト　＊＊";

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
CUB PKAN_NumberDisplayJournal_K[]	= "　　　　＊＊　ナンバーディスプレイ通信履歴　＊＊　　　　";
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
 #if defined(SAKAKI) && defined(JP0) /* By M.Maeda 2002/10/18 */
CUB PKAN_WarpList_K[] 		= "　＊＊　ファクスワープ　リスト　＊＊　";
 #else
CUB PKAN_WarpList_K[] 		= "　＊＊　ＦＡＸワープ　リスト　＊＊　　";
 #endif
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
CUB PKAN_EmergencyTitle_Emergency_K[] 		= " 　＊＊　緊急　＊＊ ";
CUB PKAN_EmergencyTitle_Normal_K[]	 		= " 　＊＊　普通　＊＊ ";
 #endif
#endif

#if (0)
** /* 宣言する位置が間違えています By O.Kimoto 2002/07/18 */
** #if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/17 K.Kawata */
** /* 再送時チェックメッセージ 2000/2/17 K.Kawata */
** CUB	PKAN_SendDocument[] = "ﾍﾟｰｼﾞから送り直してください。\0          ";
** #endif
#endif

#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
CUB PKAN_TransmitResult_K[]		= "　＊＊　送信結果　＊＊　\0                     ";	/*"＊＊　Ｔｒａｎｓｍｉｔ　Ｒｅｓｕｌｔ　＊＊\0   ";/*25(40)*//* 2002/09/27 翻訳 By M.Maeda */
CUB PKAN_ReceiveResult_K[]		= "　＊＊　受信結果　＊＊　\0                    ";		/*"＊＊　Ｒｅｃｅｉｖｅ　Ｒｅｓｕｌｔ　＊＊\0    ";/*25(40)*//* 2002/09/27 翻訳 By M.Maeda */
#endif

#endif

#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/17 K.Kawata */
/* 再送時チェックメッセージ 2000/2/17 K.Kawata */
CUB	PKAN_SendDocument[] = "ﾍﾟｰｼﾞから送り直してください。\0          ";
#endif

#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/10 */
CUB	PKAN_DialTone[]			= "ﾀﾞｲﾔﾙﾄｰﾝ検出(加入)\0 ";/*17*/
CUB	PKAN_DialToneKeiden[]	= "ﾀﾞｲﾔﾙﾄｰﾝ検出(警電)\0 ";
#else
 #if defined(STOCKHM2) || defined(HINOKI3)		/*ダイヤルトーン検出対応 by SMuratec 夏 2004/7/14 */ /* Add by Y.Kano 2004/12/07 */
 CUB	PKAN_DialTone[]			= "ﾀﾞｲﾔﾙﾄｰﾝ検出\0    ";/*17*/
 #endif 
#endif

#if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/07/21 */
CUB	PKAN_SettingLine[]		= "優先回線\000  ";
CUB	PKAN_SettingFaxMode[]	= "優先方式\000  ";
CUB	PKAN_ScrambleKeiden[]	= "ｽｸﾗﾝﾌﾞﾙ優先(警電)";
CUB	PKAN_ScrambleKanyu[]	= "ｽｸﾗﾝﾌﾞﾙ優先(加入)";
CUB	PKAN_RemoteNumIssei[]	= "ﾘﾓｰﾄ受信特番(一斉)";
CUB	PKAN_RemoteNumKobetu[]	= "ﾘﾓｰﾄ受信特番(個別)";
CUB	PKAN_KeidenLine[]		= "警電\0   ";
CUB	PKAN_KanyuLine[]		= "加入\0   ";
CUB	PKAN_IsseiFaxcom[]		= "一斉\0   ";
CUB	PKAN_KobetuFaxcom[]		= "個別\0   ";
CUB	PKAN_SettingSave[]		= "保持\0    ";
CUB	PKAN_EXTRinggingTimes[]	= "呼出ﾍﾞﾙ回数(警電)";
CUB	PKAN_RinggingTimes[]	= "呼出ﾍﾞﾙ回数(加入)";
#endif
/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの最後に入れる) */
CUB	PKAN_TAIL[]			= "";

#undef	CUB
