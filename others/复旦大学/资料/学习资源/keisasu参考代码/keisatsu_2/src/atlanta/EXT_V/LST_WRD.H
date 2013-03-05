/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_WRD.H
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 帳票用固定文字列
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef	LST_WRD_H
	#define	LST_WRD_H	1

#include "\src\atlanta\define\product.h"	/*Add By M.Kotani 1998/01/30*/
#include "\src\atlanta\define\lst_def.h"

/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの先頭に入れる) */
#if (PRO_CPU == SH7043) /* ワーディング先頭位置認識用 1996/07/04 T.Nose */
extern CONST UBYTE PWRD_WordingTop[];
extern CONST UBYTE PWRD_1stWordingTop[];
extern CONST UBYTE PWRD_2ndWordingTop[];
extern CONST UBYTE PWRD_3rdWordingTop[];
#endif

extern CONST UBYTE	PWRD_HEAD[];

/* 送信証　受領証 */
extern CONST UBYTE	PWRD_TransConfReport[];
extern CONST UBYTE	PWRD_RecConfReport[];
extern CONST UBYTE	PWRD_FromTo[];
extern CONST UBYTE	PWRD_CommNo[];
extern CONST UBYTE	PWRD_CommMode[];
extern CONST UBYTE	PWRD_CommStartTime[];
extern CONST UBYTE	PWRD_CommPages[];
extern CONST UBYTE	PWRD_CommResult[];
extern CONST UBYTE	PWRD_Normal[];
extern CONST UBYTE	PWRD_Fine[];
extern CONST UBYTE	PWRD_SFine[];
extern CONST UBYTE	PWRD_Gray[];
#if (PRO_PITNEYBOWES == ENABLE)
extern CONST UBYTE	PWRD_HFine[];	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
extern CONST UBYTE  PWRD_HGray[];	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/ /* SANYO仕様の追加 2000/02/24 N.Kondo */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SANYO仕様の追加 2000/02/24 N.Kondo */

extern CONST UBYTE	PWRD_Fine_S[];
extern CONST UBYTE	PWRD_SFine_S[];
#endif
extern CONST UBYTE	PWRD_Pages[];
extern CONST UBYTE	PWRD_FaxD[];

/* 通信管理レポート */
extern CONST UBYTE	PWRD_TransmitJournal[];
extern CONST UBYTE	PWRD_RecieveJournal[];
extern CONST UBYTE	PWRD_ContNo[];
extern CONST UBYTE	PWRD_RemoteFrom[];
extern CONST UBYTE	PWRD_RemoteTo[];
extern CONST UBYTE	PWRD_Mode[];
extern CONST UBYTE	PWRD_Start[];
extern CONST UBYTE	PWRD_Received[];
extern CONST UBYTE	PWRD_Time[];
extern CONST UBYTE	PWRD_Page[];
extern CONST UBYTE	PWRD_Code[];
extern CONST UBYTE	PWRD_Result[];
extern CONST UBYTE	PWRD_Note[];
extern CONST UBYTE	PWRD_AltNo[];
extern CONST UBYTE	PWRD_Secure[];
extern CONST UBYTE	PWRD_Relay[];
extern CONST UBYTE	PWRD_Polling[];
extern CONST UBYTE	PWRD_DbPolling[];
extern CONST UBYTE	PWRD_Manual[];
extern CONST UBYTE	PWRD_RelayedTxReport[];
extern CONST UBYTE	PWRD_FIP_Tx[];
extern CONST UBYTE	PWRD_FIP_Rx[];
extern CONST UBYTE	PWRD_FIP_Poll[];
extern CONST UBYTE	PWRD_FIP_Sec[];
extern CONST UBYTE	PWRD_BrdCast[];
extern CONST UBYTE	PWRD_Ok[];
extern CONST UBYTE	PWRD_SUB_Tx[];
extern CONST UBYTE	PWRD_SEP_Rx[];
extern CONST UBYTE	PWRD_SUB_Rx[];
extern CONST UBYTE	PWRD_Cipher_Tx[];
extern CONST UBYTE	PWRD_Cipher_Rx[];

/* 短縮ダイヤルリスト */
extern CONST UBYTE	PWRD_TeleDirectory[];
extern CONST UBYTE	PWRD_No[];
extern CONST UBYTE	PWRD_RemoteLocation[];
extern CONST UBYTE	PWRD_TeleNumber[];
extern CONST UBYTE	PWRD_GroupNumber[];
extern CONST UBYTE	PWRD_Cost[];
extern CONST UBYTE	PWRD_Attribute[];

/* ワンタッチダイヤルリスト */
extern CONST UBYTE	PWRD_OneDirectory[];

/* プログラムリスト */
extern CONST UBYTE	PWRD_DelyTime[];
extern CONST UBYTE	PWRD_Option[];
extern CONST UBYTE	PWRD_NotTime[];

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/24 By M.Kuwahara */
extern CONST UBYTE	PWRD_PRG_Onetouch[];
extern CONST UBYTE	PWRD_PRG_Speed[];
extern CONST UBYTE	PWRD_PRG_Program[];
extern CONST UBYTE	PWRD_PRG_SecureBox[];
extern CONST UBYTE	PWRD_PRG_ComReserve[];
extern CONST UBYTE	PWRD_PRG_Journal[];
 #if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
extern CONST UBYTE	PWRD_PRG_DailyReport[];
 #endif
extern CONST UBYTE	PWRD_PRG_Group[];
extern CONST UBYTE	PWRD_PRG_Setting[];
extern CONST UBYTE	PWRD_PRG_Message[];
extern CONST UBYTE	PWRD_PRG_CostBase[];
extern CONST UBYTE	PWRD_PRG_DepartCode[];
extern CONST UBYTE	PWRD_PRG_BatchBox[];
extern CONST UBYTE	PWRD_PRG_BatchDoc[];
extern CONST UBYTE	PWRD_PRG_F_CodeBox[];
extern CONST UBYTE	PWRD_PRG_F_CodeDoc[];
extern CONST UBYTE	PWRD_PRG_BlockJunk[];
extern CONST UBYTE	PWRD_PRG_ND_Dial[];
extern CONST UBYTE	PWRD_PRG_ND_Journal[];
extern CONST UBYTE	PWRD_PRG_Warp[];
 #if defined(SAKAKI) && defined(JP0) /* 2002/08/26 By M.Maeda */
extern CONST UBYTE	PWRD_PRG_JournalTx[];
extern CONST UBYTE	PWRD_PRG_JournalRx[];
 #endif
extern CONST UBYTE	PWRD_ListName[];
extern CONST UBYTE	PWRD_CommReserved[];
extern CONST UBYTE	PWRD_List[];
extern CONST UBYTE	PWRD_DocStore[];
#endif

/* グループリスト */
extern CONST UBYTE	PWRD_GroupDirectory[];
extern CONST UBYTE	PWRD_Location[];

/* マルチプログラムリスト */
extern CONST UBYTE	PWRD_MultiProgram[];
extern CONST UBYTE	PWRD_ProgOnetouchNo[];

/* メモリスイッチ */
extern CONST UBYTE	PWRD_Machine_P[];
extern CONST UBYTE	PWRD_Memory_S[];
extern CONST UBYTE	PWRD_Uniq_S[];		/* 追加 For ANZU By H.Hirao Mar.28.1996 */
extern CONST UBYTE	PWRD_BitNumber[];
extern CONST UBYTE	PWRD_Default[];
extern CONST UBYTE	PWRD_AutoSet[];

/* POPLA追加 -- メモリスイッチの追加 97/03/04 M.Kuwahara */
extern CONST UBYTE	PWRD_MainteSwitch[];

/* 通信予約リスト */
extern CONST UBYTE	PWRD_ComReservedList[];

/*親展者登録リスト*/
extern CONST UBYTE	PWRD_SecureMailBList[];
extern CONST UBYTE	PWRD_UserName[];
extern CONST UBYTE	PWRD_Box[];

/* カバーページプリント */
extern CONST UBYTE	PWRD_CoverPageMes[];

/* 親展受信通知 */
extern CONST UBYTE	PWRD_SecureMailNotice[];

/* 親展原稿消去通知 */
extern CONST UBYTE	PWRD_ErasedDocuments[];

/* 代行受信消去通知 */
extern CONST UBYTE	PWRD_ErasedDocumemts[];

/* 通信予約消去通知 */
extern CONST UBYTE	PWRD_ErasedCommands[];
extern CONST UBYTE	PWRD_MemHoldDate[];

/* チェックメッセージ */
extern CONST UBYTE	PWRD_CheckMessage[];
extern CONST UBYTE	PWRD_MemoryOver[];
extern CONST UBYTE	PWRD_PcMemoryOver[];
extern CONST UBYTE	PWRD_ErrorPages[];

/* オンラインモニタ */
#if ( PRO_CLASS1 == ENABLE )
extern CONST UBYTE	PWRD_OnLineMonitor[];
extern CONST UBYTE	PWRD_OnLineTx[];
extern CONST UBYTE	PWRD_OnLineRx[];
extern CONST UBYTE	PWRD_OnLineData[];
extern CONST UBYTE	PWRD_Speed[];
extern CONST UBYTE	PWRD_Command[];
extern CONST UBYTE	PWRD_Response[];
extern CONST UBYTE	PWRD_Abort[];
#endif

/* メイルボックスインフォメーション */
extern CONST UBYTE	PWRD_MailInfo[];
extern CONST UBYTE	PWRD_MailBox[];
extern CONST UBYTE	PWRD_MailPages[];
extern CONST UBYTE	PWRD_MailBlocks[];

/* ポーリング原稿消去通知 */
extern CONST UBYTE	PWRD_ErasePollDoc[];

/* リモートファクス原稿消去通知 */
extern CONST UBYTE	PWRD_EraseRemoteFaxDoc[];

/* 一括送信原稿リスト */
extern CONST UBYTE	PWRD_BatchTxDocList[];

/* 一括送信原稿消去通知 */
extern CONST UBYTE	PWRD_EraseBatchTxDoc[];

/* 一括送信ＢＯＸリスト */
extern CONST UBYTE	PWRD_BatchTxBoxList[];

/* 料金表 */
extern CONST UBYTE	PWRD_CostBase[];

/* 月 */
extern CONST UBYTE	PWRD_Year_Eng[12][4];

/* プログラムリスト */
extern CONST UBYTE	PWRD_ProgOnetouchDir[];

/* 親展受信通知 */
extern CONST UBYTE	PWRD_SecureMailReci[];

/* 親展原稿消去通知 */
extern CONST UBYTE	PWRD_ThisSecMailEra[];

/* 代行受信消去通知 */
extern CONST UBYTE	PWRD_ThisMemErased[];

/* 通信予約消去通知 */
extern CONST UBYTE	PWRD_ThisComErased[];

/* チェックメッセージ */
extern CONST UBYTE	PWRD_MryOverFeeder[];
extern CONST UBYTE	PWRD_MryOverRecv[];
extern CONST UBYTE	PWRD_MryOverRecv2[];
extern CONST UBYTE	PWRD_CatchPhoneRecv[];
extern CONST UBYTE	PWRD_SecurityMemOver[];
extern CONST UBYTE	PWRD_SecurityOperation1[];
extern CONST UBYTE	PWRD_SecurityOperation2[];

/* ポーリング原稿消去通知 */
extern CONST UBYTE	PWRD_PollErase[];
extern CONST UBYTE	PWRD_DbPollErase[];

/* リモートファクス原稿消去通知 */
extern CONST UBYTE	PWRD_RemoteFaxErase[];

/* 一括送信原稿リスト */
extern CONST UBYTE	PWRD_IndexNo[];

/* 一括送信原稿消去通知 */
extern CONST UBYTE	PWRD_BatchTxDocErase[];

/* 連続ポーリングコマンド消去通知 */
extern CONST UBYTE	PWRD_ContinuousPollingErase[];

/* 料金表 */
extern CONST UBYTE	PWRD_DialingCode[];
extern CONST UBYTE	PWRD_Daytime[];
extern CONST UBYTE	PWRD_Night[];
extern CONST UBYTE	PWRD_Midnight[];
extern CONST UBYTE	PWRD_Slash10[];
extern CONST UBYTE	PWRD_WithinArea[];

/* モニターレポート */
extern CONST UBYTE	PWRD_MonitorReportMessage[];

/* 通信結果メッセージ */
#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 李 2005/11/10 */
extern CONST UBYTE	PWRD_ResultName[9][31];
#else /* !defined (KEISATSU) */
extern CONST UBYTE	PWRD_ResultName[8][31];
#endif /* defined (KEISATSU) */
extern CONST UBYTE	PWRD_ResultChain[LST_ERR_CODE_MAX];
extern CONST UBYTE	PWRD_ResultCode[LST_ERR_CODE_MAX][7];

/* ワーディングテーブルサイズ計算用(必ずﾜｰﾃﾞｨﾝｸﾞの最後に入れる) */
extern CONST UBYTE	PWRD_TAIL[];

#if defined(CHN)               /* S.Wang 1995/08/22  append by BU 1/9/95 */
extern CONST UBYTE    PWRD_PowerDownNotice[];
extern CONST UBYTE    PWRD_SecMailLost[];
extern CONST UBYTE    PWRD_FaxRecieveLost[];
#endif

extern CONST UBYTE	PWRD_Batch[];
extern CONST UBYTE 	PWRD_BoxNo[];

/* 機器設定リスト */
extern CONST UBYTE	PWRD_MachineSettings[];
extern CONST UBYTE	PWRD_SubscriberID[];
extern CONST UBYTE	PWRD_SubscriberKanaID[];
extern CONST UBYTE	PWRD_SubscriberNb[];
extern CONST UBYTE	PWRD_JournalAutoPrt[];
extern CONST UBYTE	PWRD_SecureDocHold[];
#if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/07/21 */
extern CONST UBYTE	PWRD_PhoneType[];
extern CONST UBYTE	PWRD_EXTPhoneType[];
#else
extern CONST UBYTE	PWRD_PhoneType[];
#endif
extern CONST UBYTE	PWRD_ConfReport[];
extern CONST UBYTE	PWRD_ScannerWidth[];
extern CONST UBYTE	PWRD_PrimaryMode[];
extern CONST UBYTE	PWRD_Contrast[];
extern CONST UBYTE	PWRD_DialingPause[];
#if !defined(KEISATSU)			/* 警察FAX Modify by SMuratec 夏 2005/07/21 */
extern CONST UBYTE	PWRD_RinggingTimes[];
#endif
extern CONST UBYTE	PWRD_ReductionRate[];

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/ /* SANYO仕様の追加 2000/02/24 N.Kondo */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SANYO仕様の追加 2000/02/24 N.Kondo */

extern CONST UBYTE	PWRD_Contrast_S[];
#endif
#if (PRO_ROTATE == ENABLE)				/* ＤＰＲＡＭ経由の回転受信 */
extern CONST UBYTE	PWRD_RotateMargin[];
#endif
extern CONST UBYTE	PWRD_EcmMode[];
extern CONST UBYTE	PWRD_CopyProtect[];
extern CONST UBYTE	PWRD_RemoteDiagnostic[];
extern CONST UBYTE	PWRD_RedialTimes[];
extern CONST UBYTE	PWRD_Holdmelody[];
extern CONST UBYTE	PWRD_Passcode[];
extern CONST UBYTE	PWRD_CloseNetwork[];
extern CONST UBYTE	PWRD_SilentOperation[];
extern CONST UBYTE	PWRD_SecurityTx[];
extern CONST UBYTE	PWRD_BlockjunkFax[];
extern CONST UBYTE	PWRD_RecieveMode[];
extern CONST UBYTE	PWRD_PageCompound[];
extern CONST UBYTE	PWRD_SortingCopy[];
extern CONST UBYTE	PWRD_Rs232c[];
extern CONST UBYTE	PWRD_Stamp[];
extern CONST UBYTE	PWRD_MemoryTx[];
extern CONST UBYTE	PWRD_RelayedRelayTx[];

#if (PRO_PANEL == KANJI)
/* ＰＯＰＬＡＲ＿ＨはＬＣＤに待機モードを表示していないので、機器設定リストに表示させます。 By O.Kimoto 1998/03/02 */
extern CONST UBYTE	PWRD_DialIn[];
extern CONST UBYTE	PWRD_DialIn_Item1[];
extern CONST UBYTE	PWRD_DialIn_Item2[];
#else
extern CONST UBYTE	PWRD_DialIn[];
#endif

extern CONST UBYTE	PWRD_BellTime[];
extern CONST UBYTE	PWRD_RingMastr[];
extern CONST UBYTE	PWRD_CopyReduction[];
extern CONST UBYTE	PWRD_PaperSize[];
extern CONST UBYTE	PWRD_PC_PaperManual[];
extern CONST UBYTE	PWRD_PaperType[];
extern CONST UBYTE	PWRD_ToneLine[];
extern CONST UBYTE	PWRD_Pps10[];
extern CONST UBYTE	PWRD_Pps20[];
extern CONST UBYTE	PWRD_TxConf[];
extern CONST UBYTE	PWRD_RxConf[];
extern CONST UBYTE	PWRD_A4[];
extern CONST UBYTE	PWRD_B4[];
extern CONST UBYTE	PWRD_A3[];
extern CONST UBYTE	PWRD_F4[];
#if (PRO_PITNEYBOWES == ENABLE)
extern CONST UBYTE  PWRD_LETTER[];		/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
extern CONST UBYTE  PWRD_LEDGER[];		/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998 */
#endif
extern CONST UBYTE	PWRD_Dark[];
extern CONST UBYTE	PWRD_NormalDark[];
extern CONST UBYTE	PWRD_Light[];

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/ /* SANYO仕様の追加 2000/02/24 N.Kondo */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SANYO仕様の追加 2000/02/24 N.Kondo */

extern CONST UBYTE	PWRD_Dark_S[];
extern CONST UBYTE	PWRD_Light_S[];
#endif
extern CONST UBYTE	PWRD_MinuteMark[];
extern CONST UBYTE	PWRD_SecondMark[];
extern CONST UBYTE	PWRD_Try[];
extern CONST UBYTE	PWRD_Attemps[];
extern CONST UBYTE	PWRD_On[];
extern CONST UBYTE	PWRD_Off[];
extern CONST UBYTE	PWRD_Mode1[];
extern CONST UBYTE	PWRD_Mode2[];
extern CONST UBYTE	PWRD_Mode3[];
extern CONST UBYTE	PWRD_P100[];
extern CONST UBYTE	PWRD_P97[];
extern CONST UBYTE	PWRD_P91[];
extern CONST UBYTE	PWRD_P81[];
extern CONST UBYTE	PWRD_P75[];
extern CONST UBYTE	PWRD_ThValue00mm[];
extern CONST UBYTE	PWRD_TelFax[];
extern CONST UBYTE	PWRD_Tel[];
extern CONST UBYTE	PWRD_Fax[];
extern CONST UBYTE	PWRD_AnsFax[];

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec K.W.Q 2003/11/28 */
extern CONST UBYTE	PWRD_DialInRx[];
#endif

extern CONST UBYTE	PWRD_FaxTel[];	/**	追加 For ANZU By H.Hirao 1996/05/21	*/
extern CONST UBYTE	PWRD_Bps300[];
extern CONST UBYTE	PWRD_Bps600[];
extern CONST UBYTE	PWRD_Bps1200[];
extern CONST UBYTE	PWRD_Bps2400[];
extern CONST UBYTE	PWRD_Bps4800[];
extern CONST UBYTE	PWRD_Bps9600[];
extern CONST UBYTE	PWRD_Bps19200[];
extern CONST UBYTE	PWRD_BpsVariable[];	/** 追加 For POPLA By M.Kuwahara 1997/03/05 */
extern CONST UBYTE	PWRD_None[];
extern CONST UBYTE	PWRD_Odd[];
extern CONST UBYTE	PWRD_Even[];
extern CONST UBYTE	PWRD_S1bit[];
extern CONST UBYTE	PWRD_S2bit[];
extern CONST UBYTE	PWRD_P7bit[];
extern CONST UBYTE	PWRD_P8bit[];
extern CONST UBYTE	PWRD_Days[];
extern CONST UBYTE	PWRD_Auto[];
extern CONST UBYTE	PWRD_Pattern[];
extern CONST UBYTE	PWRD_Letter[];
extern CONST UBYTE	PWRD_Legal[];
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* '95.07/20 By K.Watanabe *//* by K.Watanabe 2004/10/12 */
extern CONST UBYTE	PWRD_RxAlarm[];
extern CONST UBYTE	PWRD_MercuryPause[];
extern CONST UBYTE	PWRD_MercuryNumber[];/* Added by SMuratec C.P 2004/07/08 for prefix */
#endif
extern CONST UBYTE	PWRD_MesageTrans[];
extern CONST UBYTE	PWRD_RemoteSecurityRx[];
extern CONST UBYTE	PWRD_NormalPaper[];
extern CONST UBYTE	PWRD_ThermalPaper[];		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
extern CONST UBYTE	PWRD_DepartmentProtect[];	/* 追加 For ANZU By H.Hirao Feb 29,1996 */
extern CONST UBYTE	PWRD_Department[];			/* 追加 For ANZU By H.Hirao Feb 29,1996 */
extern CONST UBYTE	PWRD_PINAccessMode[];		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#if defined(USA)
extern CONST UBYTE	PWRD_DayLightSaving[];		/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#endif
extern CONST UBYTE	PWRD_OperationProtect[];	/* 追加 For ANZU By H.Hirao Feb 29,1996 */
#if (PRO_REMOTE_RX == ENABLE)
extern CONST UBYTE	PWRD_RemoteReceive[];		/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
extern CONST UBYTE	PWRD_OnHookReceive[];		/* ＮＴＴ仕様のポプラＬで使用 98/03/13 Add By T.Fukumoto */
#endif

/* PRO_MULTI_LINE */
extern CONST UBYTE	PWRD_MultiTxRxType[];
extern CONST UBYTE	PWRD_TxRx[];
extern CONST UBYTE	PWRD_Tx[];
extern CONST UBYTE	PWRD_Rx[];
extern CONST UBYTE	PWRD_MultiLineType[];
extern CONST UBYTE	PWRD_PstnLine[];
extern CONST UBYTE	PWRD_PbxLine[];
extern CONST UBYTE	PWRD_PstnAccessNumber[];
extern CONST UBYTE	PWRD_LineNumber[];

#if (PRO_MULTI_LINE == ENABLE)	/*  By O.Kimoto 1997/01/06 */
extern CONST UBYTE	PWRD_AddErrorMessage[4][31];
#endif

extern CONST UBYTE 	PWRD_MultiTxRxType[];
extern CONST UBYTE 	PWRD_TxRx[]	;
extern CONST UBYTE	PWRD_Tx[];
extern CONST UBYTE	PWRD_Rx[];
extern CONST UBYTE 	PWRD_MultiLineType[];
extern CONST UBYTE 	PWRD_PstnLine[];
extern CONST UBYTE 	PWRD_PbxLine[];
extern CONST UBYTE 	PWRD_PstnAccessNumber[];

/* 記録紙サイズ  */
extern CONST UBYTE	PWRD_Paper_A5[];
extern CONST UBYTE	PWRD_Paper_Letter[];
extern CONST UBYTE	PWRD_Paper_A4[];
extern CONST UBYTE	PWRD_Paper_Legal[];
extern CONST UBYTE	PWRD_Paper_B5R[];
extern CONST UBYTE	PWRD_Paper_B4[];
extern CONST UBYTE	PWRD_Paper_A3[];
extern CONST UBYTE	PWRD_Paper_A4R[];
extern CONST UBYTE	PWRD_Paper_LetterR[];
extern CONST UBYTE	PWRD_Paper_F4[];
extern CONST UBYTE	PWRD_Paper_A5R[];
extern CONST UBYTE	PWRD_Paper_Postcard[];
extern CONST UBYTE	PWRD_Paper_LD[];
extern CONST UBYTE	PWRD_Paper_GLetterR[];
extern CONST UBYTE	PWRD_Paper_ExecutiveR[];
extern CONST UBYTE	PWRD_Paper_InvoiceR[];
extern CONST UBYTE	PWRD_Paper_GLegal[];
extern CONST UBYTE	PWRD_Paper_GLetter[];
extern CONST UBYTE	PWRD_Paper_Card[];
extern CONST UBYTE	PWRD_Paper_Executive[];
extern CONST UBYTE	PWRD_Paper_B5[];
extern CONST UBYTE	PWRD_Paper_C5[];
extern CONST UBYTE	PWRD_Paper_HalfLetter[];
extern CONST UBYTE	PWRD_Paper_Invoice[];
extern CONST UBYTE	PWRD_Paper_B6[];
extern CONST UBYTE	PWRD_Paper_DL[];
extern CONST UBYTE	PWRD_Paper_CM10[];
extern CONST UBYTE	PWRD_Paper_A6[];
extern CONST UBYTE	PWRD_Paper_Monarch[];
extern CONST UBYTE	PWRD_Paper_35[];
extern CONST UBYTE	PWRD_Paper_User[];

/* 記録紙サイズ POPLAR用 */
extern CONST UBYTE	PWRD_PaperSize_A5[];
extern CONST UBYTE	PWRD_PaperSize_Letter[];
extern CONST UBYTE	PWRD_PaperSize_A4[];
extern CONST UBYTE	PWRD_PaperSize_Legal[];
extern CONST UBYTE	PWRD_PaperSize_B5R[];
extern CONST UBYTE	PWRD_PaperSize_B4[];
extern CONST UBYTE	PWRD_PaperSize_A3[];
extern CONST UBYTE	PWRD_PaperSize_A4R[];
extern CONST UBYTE	PWRD_PaperSize_LetterR[];
extern CONST UBYTE	PWRD_PaperSize_F4[];
extern CONST UBYTE	PWRD_PaperSize_A5R[];
extern CONST UBYTE	PWRD_PaperSize_Postcard[];
extern CONST UBYTE	PWRD_PaperSize_LD[];
extern CONST UBYTE	PWRD_PaperSize_GLetterR[];
extern CONST UBYTE	PWRD_PaperSize_ExecutiveR[];
extern CONST UBYTE	PWRD_PaperSize_HalfLetterR[];  /* added by honda 1997/10/04 POPLAR_B USA,GBR */
extern CONST UBYTE	PWRD_PaperSize_InvoiceR[];
extern CONST UBYTE	PWRD_PaperSize_GLegal[];
extern CONST UBYTE	PWRD_PaperSize_GLetter[];
extern CONST UBYTE	PWRD_PaperSize_Card[];
extern CONST UBYTE	PWRD_PaperSize_Executive[];
extern CONST UBYTE	PWRD_PaperSize_B5[];
extern CONST UBYTE	PWRD_PaperSize_C5[];
extern CONST UBYTE	PWRD_PaperSize_HalfLetter[];
extern CONST UBYTE	PWRD_PaperSize_Invoice[];
extern CONST UBYTE	PWRD_PaperSize_B6[];
extern CONST UBYTE	PWRD_PaperSize_DL[];
extern CONST UBYTE	PWRD_PaperSize_CM10[];
extern CONST UBYTE	PWRD_PaperSize_A6[];
extern CONST UBYTE	PWRD_PaperSize_Monarch[];
extern CONST UBYTE	PWRD_PaperSize_35[];
extern CONST UBYTE	PWRD_PaperSize_User[];

 #if defined(CHN)   /* S.Wang  1995/08/22 */
/* append some of new word by BU 12/31/94 */
extern CONST UBYTE    PWRD_Interval[];
extern CONST UBYTE    PWRD_Yes[];
extern CONST UBYTE    PWRD_Not[];
extern CONST UBYTE    PWRD_SortCopyOn[];
extern CONST UBYTE    PWRD_SortCopyOFF[];
extern CONST UBYTE    PWRD_JournalOn[];
extern CONST UBYTE    PWRD_JournalOFF[];
extern CONST UBYTE    PWRD_ConfirmOn[];
extern CONST UBYTE    PWRD_ConfirmOFF[];
extern CONST UBYTE    PWRD_FaxReady[];
/* -------------------------------------- */
 #endif

/* キノウリスト */
extern CONST UBYTE	PWRD_ProgramList[];

/* Ｔ３０モニタ */
extern CONST UBYTE	PWRD_T30Monitor[];
extern CONST UBYTE	PWRD_TxFrame[];
extern CONST UBYTE	PWRD_RxFrame[];
extern CONST UBYTE	PWRD_Datalong[];
extern CONST UBYTE	PWRD_Rs144[];
extern CONST UBYTE	PWRD_Rs120[];
extern CONST UBYTE	PWRD_Rs96[];
extern CONST UBYTE	PWRD_Rs72[];
extern CONST UBYTE	PWRD_Rs48[];
extern CONST UBYTE	PWRD_Rs24[];
extern CONST UBYTE	PWRD_V17[];
extern CONST UBYTE	PWRD_V33[];
extern CONST UBYTE	PWRD_V29[];
extern CONST UBYTE	PWRD_V27[];
extern CONST UBYTE	PWRD_MH[];
extern CONST UBYTE	PWRD_MR[];
extern CONST UBYTE	PWRD_MMR[];
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
extern CONST UBYTE	PWRD_JBG[];
#endif
extern CONST UBYTE	PWRD_A5[];
extern CONST UBYTE	PWRD_A6[];
extern CONST UBYTE	PWRD_Wait20[];
extern CONST UBYTE	PWRD_Wait40[];
extern CONST UBYTE	PWRD_Wait10[];
extern CONST UBYTE	PWRD_Wait5[];
extern CONST UBYTE	PWRD_Wait0[];
extern CONST UBYTE	PWRD_ModeNR[];
extern CONST UBYTE	PWRD_ModeFN[];
extern CONST UBYTE	PWRD_ModeSF[];
extern CONST UBYTE	PWRD_ModeHF[];

extern CONST UBYTE	PWRD_Main[];
extern CONST UBYTE	PWRD_Reset[];
extern CONST UBYTE	PWRD_Error[];
extern CONST UBYTE	PWRD_Now[];
extern CONST UBYTE	PWRD_DpramTx[];
extern CONST UBYTE	PWRD_DpramRx[];

/* コウジョウ ファンクション リスト */
extern CONST UBYTE	PWRD_FunctionList[];
extern CONST UBYTE	PWRD_LedTest[];
extern CONST UBYTE	PWRD_LcdTest[];
extern CONST UBYTE	PWRD_Pane1keytest[];
extern CONST UBYTE	PWRD_Rs232cTest[];
extern CONST UBYTE	PWRD_SramCheck[];
extern CONST UBYTE	PWRD_DramCheck[];
extern CONST UBYTE	PWRD_RTCTest[];

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
extern CONST UBYTE	PWRD_BoxName[];
extern CONST UBYTE	PWRD_SubAddress[];
extern CONST UBYTE	PWRD_CommPasscode[];
extern CONST UBYTE	PWRD_Kind[];
extern CONST UBYTE	PWRD_NoticeBoard[];
extern CONST UBYTE	PWRD_RecvProtect[];
extern CONST UBYTE	PWRD_Replace[];
extern CONST UBYTE	PWRD_RxPrint[];
extern CONST UBYTE	PWRD_TransErase[];

#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
extern CONST UBYTE	PWRD_RelayName[];
extern CONST UBYTE	PWRD_PutSubscriber[];
extern CONST UBYTE	PWRD_Avail[];
extern CONST UBYTE	PWRD_NoTTI[];
extern CONST UBYTE	PWRD_SUB_Relay[];	/* 1998/09/25 By M.Kuwahara */
extern CONST UBYTE	PWRD_SUB_Secure[];	/* 1998/09/28 By M.Kuwahara */
#endif

#if (PRO_FCODE_KIND_DISPLAY == ENABLE)
extern CONST UBYTE	PWRD_SUB_Bulletin[];	/* 1998/09/28 By M.Kuwahara */
#endif

/* サブアドレス原稿消去通知 */
extern CONST UBYTE	PWRD_BoxLocation[];
extern CONST UBYTE	PWRD_ThisBoxErased[];

/* サブアドレスBOX蓄積原稿リスト */
extern CONST UBYTE PWRD_DocumentsNo[];

/* サブアドレスBOX受信通知 */
extern CONST UBYTE PWRD_F_CodeReci[];
extern CONST UBYTE PWRD_F_ReciDocMemory[];
#endif

/* ダイレクトメール防止ダイヤルリスト */
extern CONST UBYTE PWRD_TelNum[];

/* 暗号化受信通知リスト */
extern CONST UBYTE PWRD_ReceiveNo[];
extern CONST UBYTE PWRD_KeyClue[];
extern CONST UBYTE PWRD_KeyWordClue[];

/* キーリスト、キーブックリスト */
extern CONST UBYTE PWRD_KeyName[];
extern CONST UBYTE PWRD_Key[];

/* 暗号化受信消去通知リスト */
extern CONST UBYTE PWRD_ScrambleRxErase[];

/* 消耗品発注票 */
extern CONST UBYTE PWRD_ToOrder[];
extern CONST UBYTE PWRD_FromOrder[];
extern CONST UBYTE PWRD_CustomerCode[];
extern CONST UBYTE PWRD_DistributorName[];
extern CONST UBYTE PWRD_CustomerName[];
extern CONST UBYTE PWRD_Section[];
extern CONST UBYTE PWRD_ChargeName[];
extern CONST UBYTE PWRD_ModelName[];
extern CONST UBYTE PWRD_OrderItem[];
extern CONST UBYTE PWRD_TonerOrder1[];
extern CONST UBYTE PWRD_DrumOrder1[];
extern CONST UBYTE PWRD_SeirialNumber[];
extern CONST UBYTE PWRD_InstallDate[];
extern CONST UBYTE PWRD_BlockLetters[];
extern CONST UBYTE PWRD_Remarks[];
extern CONST UBYTE PWRD_OrderTonerChange[];
extern CONST UBYTE PWRD_OrderTonerDrumChange[];
extern CONST UBYTE PWRD_OrderSheet[];
#if defined(US1)
extern CONST UBYTE PWRD_OrderTonerDrumChange2[];	/* orderbythonda1998/11/11 */
extern CONST UBYTE PWRD_OrderSheet2[];				/* orderbythonda1998/11/11 */
#endif

/* 簡易料金管理リスト */
#if (PRO_DEPART_NEW_LIST == ENABLE)
extern CONST UBYTE PWRD_DepartTimeList[];  /* added by thonda 1997/12/02 */
#endif

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
extern CONST UBYTE PWRD_KeyMacroList[];
extern CONST UBYTE PWRD_NoTitle[];
extern CONST UBYTE PWRD_Title[];
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
extern CONST UBYTE PWRD_NumberDisplayList[];
extern CONST UBYTE PWRD_NumberDisplay[];
extern CONST UBYTE PWRD_NoConnect[];
extern CONST UBYTE PWRD_Tel1Connect[];
extern CONST UBYTE PWRD_Tel2Connect[];
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
extern CONST UBYTE PWRD_ND_Warp[];
 #endif

/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
extern CONST UBYTE PWRD_NumberDisplayJournal[];
extern CONST UBYTE PWRD_SubscriberNumber[];
extern CONST UBYTE PWRD_NoNotice[];
extern CONST UBYTE PWRD_OutOfDisp[];
extern CONST UBYTE PWRD_PublicTel[];
extern CONST UBYTE PWRD_FNetCall[];
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
extern CONST UBYTE PWRD_WarpList[];
extern CONST UBYTE PWRD_AppointedTime[];
extern CONST UBYTE PWRD_WarpFunction[];
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1999/01/25 */
extern CONST UBYTE PWRD_WarpWeek[][4];
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
extern CONST UBYTE PWRD_INF_AddressList[];
extern CONST UBYTE PWRD_INF_GroupList[];
extern CONST UBYTE	PWRD_INF_MailComList[];
extern CONST UBYTE	PWRD_INF_SettingList[];
extern CONST UBYTE	PWRD_INF_ErasedMailList[];
extern CONST UBYTE PWRD_INF_ErasedCommand[];
extern CONST UBYTE PWRD_INF_Group[];
extern CONST UBYTE PWRD_INF_Address[];
extern CONST UBYTE PWRD_INF_UserName[];
extern CONST UBYTE PWRD_INF_ProviderName[];
extern CONST UBYTE PWRD_INF_AccessPoint1[];
extern CONST UBYTE PWRD_INF_AccessPoint2[];
extern CONST UBYTE PWRD_INF_AccessPoint3[];
extern CONST UBYTE PWRD_INF_PPPLoginID[];
extern CONST UBYTE PWRD_INF_PPPPassword[];
extern CONST UBYTE PWRD_INF_PPPAuth[];
extern CONST UBYTE PWRD_INF_POPLoginID[];
extern CONST UBYTE PWRD_INF_POPPassword[];
extern CONST UBYTE PWRD_INF_MailAddress[];
extern CONST UBYTE PWRD_INF_SMTPServer[];
extern CONST UBYTE PWRD_INF_POPServer[];
extern CONST UBYTE PWRD_INF_PriDNSServer[];
extern CONST UBYTE PWRD_INF_SecDNSServer[];
extern CONST UBYTE PWRD_INF_ClientAddress[];
extern CONST UBYTE PWRD_INF_ServerAddress[];
extern CONST UBYTE PWRD_INF_GatewayAddress[];
extern CONST UBYTE PWRD_INF_TxRx[];
extern CONST UBYTE PWRD_INF_AutoRcvMail[];
extern CONST UBYTE PWRD_INF_StartTime[];
extern CONST UBYTE PWRD_INF_EndTime[];
extern CONST UBYTE PWRD_INF_IntervalTime[];
extern CONST UBYTE PWRD_INF_HoldTime[];
extern CONST UBYTE PWRD_INF_AutoPrint[];
extern CONST UBYTE PWRD_INF_ComsWereErased[];
extern CONST UBYTE	PWRD_INF_MailsWereErased[];
extern CONST UBYTE	PWRD_INF_Receiver[];
extern CONST UBYTE	PWRD_INF_ErrorCode[];
extern CONST UBYTE	PWRD_INF_ReTx[];
extern CONST UBYTE	PWRD_INF_ReRx[];
extern CONST UBYTE  PWRD_INF_DialErr[];
extern CONST UBYTE  PWRD_INF_ChkSetting[];
extern CONST UBYTE	PWRD_INF_MemErr[];
extern CONST UBYTE	PWRD_INF_ChkBoard[];
extern CONST UBYTE	PWRD_INF_PowerOff[];
extern CONST UBYTE	PWRD_INF_Kind[];
extern CONST UBYTE	PWRD_INF_To[];
extern CONST UBYTE	PWRD_INF_Tx[];
extern CONST UBYTE	PWRD_INF_Rx[];
extern CONST UBYTE	PWRD_INF_User[];
extern CONST UBYTE	PWRD_INF_AccessPoint[];
extern CONST UBYTE	PWRD_INF_ConnectTime[];
extern CONST UBYTE	PWRD_INF_ConnectCount[];
extern CONST UBYTE	PWRD_MailReceptionReport[];
extern CONST UBYTE	PWRD_MailSender[];
extern CONST UBYTE	PWRD_MailReceivedTime[];
extern CONST UBYTE	PWRD_MailAutoPrintTime[];
extern CONST UBYTE	PWRD_MailRxReportState1[];
extern CONST UBYTE	PWRD_MailRxReportState2[];
extern CONST UBYTE	PWRD_MailRxReportState3[];
extern CONST UBYTE	PWRD_MailRxReportState4[];
extern CONST UBYTE 	PWRD_INF_JournalComStartTime[];/*1998/05/25 Eguchi*/
extern CONST UBYTE	PWRD_INF_Ok[];
extern CONST UBYTE	PWRD_INF_Error[];
extern CONST UBYTE	PWRD_INF_AutoDownLoad[];
extern CONST UBYTE	PWRD_INF_DeleteMail[];
extern CONST UBYTE	PWRD_INF_AutoCheck[];
extern CONST UBYTE	PWRD_INF_MailJournal[];
#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */

/* 通信結果プリント */
#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
extern CONST UBYTE PWRD_TransmitResult[];
extern CONST UBYTE PWRD_ReceiveResult[];
#endif

#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )

/* 送信証　受領証 */
extern CONST UBYTE PWRD_TransConfReport_K[];
extern CONST UBYTE PWRD_RecConfReport_K[];

/* 通信管理レポート｢送信｣ ｢受信｣ */
extern CONST UBYTE PWRD_TransmitJournal_K[];
extern CONST UBYTE PWRD_RecieveJournal_K[];

/* 短縮ダイヤルリスト */
extern CONST UBYTE PWRD_TeleDirectory_K[];

/* ワンタッチダイヤルリスト */
extern CONST UBYTE PWRD_OneDirectory_K[];

/* 属性リスト */
extern CONST UBYTE PWRD_AttributeList_K[];

/* グループリスト */
extern CONST UBYTE PWRD_GroupDirectory_K[];

/* マルチプログラムリスト */
extern CONST UBYTE PWRD_MultiProgram_K[];

/* 機器設定リスト */
extern CONST UBYTE PWRD_MachineSettings_K[];

/* 機能リスト */
extern CONST UBYTE PWRD_ProgramList_K[];

/* 通信予約リスト */
extern CONST UBYTE PWRD_ComReservedList_K[];

/* 親展者リスト */
extern CONST UBYTE PWRD_SecureMailBList_K[];

/* カバーページプリント */
extern CONST UBYTE PWRD_CoverPageMes_K[];

/* 親展受信通知 */
extern CONST UBYTE PWRD_SecureMailNotice_K[];

/* 親展原稿消去通知 */
extern CONST UBYTE PWRD_ErasedDocuments_K[];

/* 代行受信消去通知 */
extern CONST UBYTE PWRD_ErasedDocumemts_K[];

/* 通信予約消去通知 */
extern CONST UBYTE PWRD_ErasedCommands_K[];

/* チェックメッセージ　メモリオーバー */
extern CONST UBYTE PWRD_CheckMessage_K[];
extern CONST UBYTE PWRD_MemoryOver_K[];
extern CONST UBYTE PWRD_PcMemoryOver_K[];

/* Ｔ３０モニタ */
extern CONST UBYTE PWRD_T30Monitor_K[];

/* ﾎﾟｰﾘﾝｸﾞ原稿消去通知 */
extern CONST UBYTE PWRD_ErasePollDoc_K[];

/* 一括送信原稿リスト */
extern CONST UBYTE PWRD_BatchTxDocList_K[];

/* 一括送信原稿消去通知 */
extern CONST UBYTE	PWRD_EraseBatchTxDoc_K[];

/* 一括送信ＢＯＸリスト */
extern CONST UBYTE	PWRD_BatchTxBoxList_K[];

/* 部門管理リスト*/
extern CONST UBYTE PWRD_DepartCodeList_K[];

/* 料金表 */
extern CONST UBYTE PWRD_CostBase_K[];

/* プログラムリスト */
extern CONST UBYTE PWRD_ProgOnetouchDir_K[];

/* モニターレポート */
extern CONST UBYTE PWRD_MonitorReport_K[];

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
extern CONST UBYTE PWRD_F_CodeBox_List_K[];

/* サブアドレス原稿消去通知 */
extern CONST UBYTE PWRD_Del_F_CodeBoxDoc_Notice_K[];
/* サブアドレスＢＯＸ蓄積原稿リスト */
extern CONST UBYTE PWRD_F_CodeDoc_List_K[];

/* サブアドレスＢＯＸ蓄積原稿リスト */
extern CONST UBYTE PWRD_F_CodeBoxRsv_Notice_K[];
#endif

/* ダイレクトメール防止ダイヤルリスト */
extern CONST UBYTE PWRD_BlockJunkList_K[];

/* サービスレポート */
extern CONST UBYTE PWRD_ServiceReport_K[];

/* 暗号化受信通知リスト */
extern CONST UBYTE PWRD_CipherReceiveNotice_K[];

/* キーブックリスト */
extern CONST UBYTE PWRD_KeyBookList_K[];

/* キーリスト */
extern CONST UBYTE PWRD_KeyWordList_K[];

/* 暗号化受信消去通知リスト */
extern CONST UBYTE PWRD_EraseScrambleRxDoc_K[];

/* 消耗品発注票 */
extern CONST UBYTE PWRD_ConsumerOrderSheet_K[];

 #if (PRO_COST == ENABLE)				/* 料金管理 *//* Add By O.Kimoto 1997/11/17 */
/* 料金表 */
extern CONST UBYTE	PWRD_DialingCode[];
extern CONST UBYTE	PWRD_Daytime[];
extern CONST UBYTE	PWRD_Night[];
extern CONST UBYTE	PWRD_Midnight[];
extern CONST UBYTE	PWRD_Slash10[];
extern CONST UBYTE	PWRD_WithinArea[];
 #endif

 #if (PRO_LINENUMBER == TWICE_LINE)	/* 内蔵回線のラベルです。 By O.Kimoto 1997/12/20 */
#if (0)
//extern CONST UBYTE PWRD_InternalLineName[][8];
#endif
extern CONST UBYTE PWRD_LineName[][8];
 #endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)		/* 1998/03/11 by Y.Tanimoto */
extern CONST UBYTE	PWRD_INF_MailComList_K[];
extern CONST UBYTE	PWRD_INF_SettingList_K[];
extern CONST UBYTE	PWRD_INF_ErasedMailList_K[];
extern CONST UBYTE	PWRD_INF_ErasedCommand_K[];
#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE  */

/* キーマクロタイトルリスト */
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
extern CONST UBYTE	PWRD_KeyMacroList_K[];
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/* ナンバーディスプレイリスト */	/* 1998/06/25 By M.Kuwahara */
extern CONST UBYTE PWRD_NumberDisplayList_K[];
/* ナンバーディスプレイ通信履歴 */	/* 1998/09/19 By M.Kuwahara */
extern CONST UBYTE PWRD_NumberDisplayJournal_K[];
#endif

/* ワープ機能ダイヤルリスト */
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/25 By M.Kuwahara */
extern CONST UBYTE PWRD_WarpList_K[];
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
extern CONST UBYTE PWRD_EmergencyTitle_Emergency_K[];
extern CONST UBYTE PWRD_EmergencyTitle_Normal_K[];
 #endif
#endif

#if (0)
** /* 宣言する位置が間違えています By O.Kimoto 2002/07/18 */
** #if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/17 K.Kawata */
** /* 再送時チェックメッセージ 2000/2/17 K.Kawata */
** extern CONST UBYTE PWRD_SendDocument[];
** #endif
#endif

#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
extern CONST UBYTE PWRD_TransmitResult_K[];
extern CONST UBYTE PWRD_ReceiveResult_K[];
#endif

#else

/* 送信証　受領証 */
extern CONST UBYTE PWRD_TransConfReport[];
extern CONST UBYTE PWRD_RecConfReport[];

/* 通信管理レポート｢送信｣ ｢受信｣ */
extern CONST UBYTE PWRD_TransmitJournal[];
extern CONST UBYTE PWRD_RecieveJournal[];

/* 短縮ダイヤルリスト */
extern CONST UBYTE PWRD_TeleDirectory[];

/* ワンタッチダイヤルリスト */
extern CONST UBYTE PWRD_OneDirectory[];

/* 属性リスト */
extern CONST UBYTE PWRD_AttributeList[];

/* グループリスト */
extern CONST UBYTE PWRD_GroupDirectory[];

/* マルチプログラムリスト */
extern CONST UBYTE PWRD_MultiProgram[];

/* 機器設定リスト */
extern CONST UBYTE PWRD_MachineSettings[];

/* 機能リスト */
extern CONST UBYTE PWRD_ProgramList[];

/* 通信予約リスト */
extern CONST UBYTE PWRD_ComReservedList[];

/* 親展者リスト */
extern CONST UBYTE PWRD_SecureMailBList[];

/* カバーページプリント */
extern CONST UBYTE PWRD_CoverPageMes[];

/* 親展受信通知 */
extern CONST UBYTE PWRD_SecureMailNotice[];

/* 親展原稿消去通知 */
extern CONST UBYTE PWRD_ErasedDocuments[];

/* 代行受信消去通知 */
extern CONST UBYTE PWRD_ErasedDocumemts[];

/* 通信予約消去通知 */
extern CONST UBYTE PWRD_ErasedCommands[];

/* チェックメッセージ　メモリオーバー */
extern CONST UBYTE PWRD_CheckMessage[];
extern CONST UBYTE PWRD_MemoryOver[];

/* Ｔ３０モニタ */
extern CONST UBYTE PWRD_T30Monitor[];

/* ﾎﾟｰﾘﾝｸﾞ原稿消去通知 */
extern CONST UBYTE PWRD_ErasePollDoc[];

/* 一括送信原稿リスト */
extern CONST UBYTE PWRD_BatchTxDocList[];

/* 一括送信原稿消去通知 */
extern CONST UBYTE	PWRD_EraseBatchTxDoc[];

/* 一括送信ＢＯＸリスト */
extern CONST UBYTE	PWRD_BatchTxBoxList[];

/* 料金表 */
extern CONST UBYTE PWRD_CostBase[];

/* プログラムリスト */
extern CONST UBYTE PWRD_ProgOnetouchDir[];

/* モニターレポート */
extern CONST UBYTE PWRD_MonitorReport[];

#if (PRO_F_CODE == ENABLE)
/* サブアドレスＢＯＸ */
extern CONST UBYTE	PWRD_F_CodeBox_List[];

/* サブアドレス原稿消去通知 */
extern CONST UBYTE	PWRD_Del_F_CodeBoxDoc_Notice[];

/* サブアドレスBOX蓄積原稿リスト */
extern CONST UBYTE PWRD_F_CodeDoc_List[];

/* サブアドレスBOX受信通知 */
extern CONST UBYTE PWRD_F_CodeBoxRsv_Notice[];
#endif

/* ダイレクトメール防止ダイヤルリスト */
extern CONST UBYTE PWRD_BlockJunkList[];

/* サービスレポート */
extern CONST UBYTE PWRD_ServiceReport[];

/* 暗号化受信通知リスト */
extern CONST UBYTE PWRD_CipherReceiveNotice[];

/* キーブックリスト */
extern CONST UBYTE PWRD_KeyBookList[];

/* キーリスト */
extern CONST UBYTE PWRD_KeyWordList[];

/* 暗号化受信消去通知リスト */
extern CONST UBYTE PWRD_EraseScrambleRxDoc[];

/* 消耗品発注票 */
extern CONST UBYTE PWRD_ConsumerOrderSheet[];
 #if defined(US1)
extern CONST UBYTE PWRD_ConsumerOrderSheet2[];	/* orderbythonda1998/11/11 */
 #endif
#endif

#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/17 K.Kawata */
/* 再送時チェックメッセージ 2000/2/17 K.Kawata */
extern CONST UBYTE PWRD_SendDocument[];
#endif

#if defined(STOCKHM2) || defined(HINOKI3)	/*ダイヤルトーン検出対応 by SMuratec 夏 2004/7/14 */ /* Add by Y.Kano 2004/12/07 */
extern CONST UBYTE	PWRD_DialTone[];
#endif

#if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/07/21 */
extern CONST UBYTE	PWRD_DialToneKeiden[];
extern CONST UBYTE	PWRD_SettingLine[];
extern CONST UBYTE	PWRD_SettingFaxMode[];
extern CONST UBYTE	PWRD_ScrambleKeiden[];
extern CONST UBYTE	PWRD_ScrambleKanyu[];
extern CONST UBYTE	PWRD_RemoteNumIssei[];
extern CONST UBYTE	PWRD_RemoteNumKobetu[];
extern CONST UBYTE	PWRD_KeidenLine[];
extern CONST UBYTE	PWRD_KanyuLine[];
extern CONST UBYTE	PWRD_IsseiFaxcom[];
extern CONST UBYTE	PWRD_KobetuFaxcom[];
extern CONST UBYTE	PWRD_SettingSave[];
extern CONST UBYTE	PWRD_EXTRinggingTimes[];
extern CONST UBYTE	PWRD_RinggingTimes[];
#endif
#endif
