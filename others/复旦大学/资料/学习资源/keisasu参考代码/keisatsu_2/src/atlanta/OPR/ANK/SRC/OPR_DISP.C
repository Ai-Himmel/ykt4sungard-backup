/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_DISP.C
*	Author		: 渡辺一章
*	Date		: 1996/10/30
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ＬＣＤ表示関係
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\mntsw_a.h"				/* MNT_SW_A9, DISPLAY_HFINE_EFINE */
#include	"\src\atlanta\define\mntsw_b.h"				/* MNT_SW_B4, DSP_SCAN_DOC_SIZE */
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\sysmcopy.h"
#include	"\src\atlanta\define\sysprint.h"
#include	"\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\define\sysscan.h"				/* T.Nose 1997/05/19↓下検索 */
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"				/* DateTypeGet() */
#include	"\src\atlanta\define\mem_pro.h"				/* MEM_CountEmptyBlockRate() */
#include	"\src\atlanta\define\stng_pro.h"			/* CHK_CopyProtectON() */
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"				/* CHK_ErrorLineDisplay(), CHK_CommunicationSpeedDisplay() */

#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"				/* PWRD_A5 */
#include	"\src\atlanta\ext_v\man_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\scn_data.h"
#if (PRO_MODEM == R288F) /* By H.Fujimura 1999/01/18 */
 #if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"	/* MDM_RxTotalLine, MDM_RxErrorTotalLine */
 #else
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"	/* MDM_RxTotalLine, MDM_RxErrorTotalLine */
 #endif
#elif (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* MDM_RxTotalLine, MDM_RxErrorTotalLine */
#else
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"	/* MDM_RxTotalLine, MDM_RxErrorTotalLine */
#endif
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"		/* DisplayBufferHigh, DisplayBufferLow */
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\sys_opt.h"
#include	"\src\atlanta\define\sysdisp.h"
#include	"\src\atlanta\define\mlt_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\ext_v\mlt_data.h"
#endif
#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mon.h"
#endif
#if (PRO_PRINT_TYPE == LED)
#include	"\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/01/07 */
#include	"\src\atlanta\scd\ext_v\cph_data.h"
#endif
#if (PRO_PC_PRINT == ENABLE)	/* by K.Watanabe 1998/02/23 */
#include	"\src\atlanta\ext_v\dpr_data.h"
#endif
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
 #include	"\src\atlanta\ext_v\bkupram.h"
#endif

#if (PRO_DRUM_PRT_CNT == ENABLE)/* NTT のみ By Y.Suzuki 1998/07/06*/
#include "\src\atlanta\prt\ph3\ext_v\prn_tbl.h"
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ＬＣＤ表示変更 By O.Kimoto 1999/02/25 */
#include "\src\atlanta\define\mntsw_h.h"
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/15 */
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\hinoki\define\m_param.h"
#endif		/* End of (defined (KEISATSU)) */

#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/30 */
#include	"\src\atlanta\define\sys_line.h"
#endif /* defined (KEISATSU) */

/* Prototype
void	UpdateLCD(void);
void	DisplayMachineError(void);
void	DisplayMachineErrorHigh(void);
UBYTE	DisplayMachineErrorLow(UBYTE);
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
void	DisplayMachineError2(void);
UBYTE	DisplayMachineErrorLow2(UBYTE);
#endif
void	DisplayFaxCom(void);
void	DisplayStoreMemTxDocument(void);
#if (PRO_BATCH_TX == ENABLE)
void	DisplayStoreBatcTxDocument(void);
#endif
void	DisplayTransmit(void);
void	DisplayReceive(void);
UBYTE	GetCommunicationResolution(UBYTE);
UWORD	GetCommunicationSpeed(UBYTE);
UBYTE	DisplayMultiLineFaxCom(void);
void	DisplayWaitAMinutes(void);
void	DisplayCalender(void);
void	DisplayFeedOut(void);
void	DisplayIdle(void);
void	DisplayRxMode(void);
void	DisplayCopy(UBYTE);
void	DisplayImagePrint(void);
void	DisplayListPrint(void);
UBYTE	DisplayDocumentStore(void);
void	DisplayDocumentStoreHigh(void);
@* void	DisplayDocumentSet(UBYTE); 1997/05/19 T.Nose *@
void	DisplayDocumentSet(void);
void	SetDocumentScanSizeWording(UBYTE *, UBYTE);
void	SetRegularDocumentSizeWording(UBYTE *);
void	DisplayComplete(void);
void	DisplayDocumentOnFeeder(void);
#if (PRO_CLASS1 == ENABLE)
void	DisplayClass1(void);
#endif
#if (PRO_PC_PRINT == ENABLE)
void	DisplayPcPrint(void);
#endif
#if (PRO_CIPHER == ENABLE)
void	DisplayCipherProcess(UBYTE *);
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
void	DisplayCopyMode(void);
void	DisplayCopyModeHigh(void);
void	DisplayCopyModeLow(void);
void	SetCopyModePaperDensity(void);
void	SetCassettePaperSize(UBYTE *);
UBYTE	*SetCassetteCharacter(UBYTE *, UBYTE);
void	SetCassetteWording(UBYTE *, UBYTE);
void	SetCopyModeMagnification(UBYTE *);
void	SetDocumentSize(void);
void	DisplayReplacePaperSize(UBYTE);
#endif
void	SetPaperSizeWording(UBYTE *, UBYTE, UBYTE);
#if (PRO_MULTI_LINE == ENABLE)
void	OverWriteDisplayData(UBYTE);
UBYTE	BaudRateCompatible(UBYTE);
void	UpdateCheckerDisplay(void);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
void	IdleCountDisplay(UDWORD);
#endif
*/

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/14 Y.Matsukuma */
void	MinoltaPrinterErrorDisplay(void);
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
#include	"\src\atlanta\define\sys_infd.h"
#include	"\src\atlanta\ext_v\sys_inf.h"
void	DisplayINF_Terminate(void);
void	DisplayINF_NoNewMail(void);
void	DisplayInternetFax(void);
void	DisplayINF_ExecKind(void);
UBYTE	*GetMailComKindStrAddress(UBYTE);
void	DisplayINF_ExecStatus(void);
UBYTE	CheckReservedMailComExist(void);
UBYTE	CheckRedialMailComExist(void);
#endif

#if (0)	/* by K.Watanabe 1998/04/30 */
//#if (PRO_KEYPANEL == PANEL_POPLAR_B)
///* 電源ONした時に、何も押していないのにNackが鳴る現象のデバッグ用に追加 by K.Watanabe 1998/04/28 */
//const UBYTE	DBG_Sw = 0;
//#endif
#endif

#if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/16 */
/*************************************************************************
	module		:[ＬＣＤ表示更新]
	function	:[
		1.機器状態を表示する。
		2.オペレーション中、電話中は表示を更新しない。
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/05]
	author		:[江口,渡辺一章]
*************************************************************************/
void UpdateLCD(void)
{
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/11/14 */
	UWORD	mem_area;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/11/07 */
	/* 
	DVT修正：原稿サイズ、メモリー残量の表示がされない場合で
			 画質キと濃度キの一番回押すは禁止されないので、
			 ここで以上キを無効になる必要です。
	*/ 
	IsDocumentSet = FALSE; /* Added by SMuratec 李 2004/08/17 */
	IsDocumentStoring = FALSE;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
	OPR_DispInfo = OPR_DSP_NO_ERROR;	/* エラー未表示をセット */

#if (PRO_FBS == ENABLE)
	/*----------------------------------------------*/
	/** オペレーション中であれば表示は更新しません	*/
	/*----------------------------------------------*/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_OPERATE) {
		return;
	}

	/*--------------------------------------*/
	/** チャイルド表示中はなにも表示しない	*/
	/*--------------------------------------*/
	if (CheckChildDisplay() == TRUE) {
		return;
	}

	/** コピー待機中の表示（動作中・エラーの表示より、コピーパラメーター表示を優先させる時） */
	if (tskno_OPR_ParamDispTask != 0xffff) {	/* コピーモードで、画面を更新するキーが押された時 */
		DisplayCopyMode();
		return;
	}

	/** 電話中の表示 */
	/* 1.SYS_OPERATEがOFFで、SYS_PANEL_BUSYがONしているのは電話中だけです
	** 2.電話中の表示はオペレーション内で行っていましたが、原稿蓄積で次原稿なしが選択された場合
	** 　蓄積完了時にオペレーションが走らないために、蓄積中の表示が残ったままになるので、
	** 　ここでも表示させるようにします
	*/
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PANEL_BUSY) {
		DisplayNCUStatus();
		return;
	}

	/** 原稿蓄積時の表示（次原稿の表示の関係で、PRO_FBSで表示の優先度を替えます） */
	/* 1.コピーモードの時は、優先順位はどちらでもかまいませんが、ファクスモードに合わせておきます
	** 2.電話中にポーリング蓄積等がされた場合は、蓄積表示を優先します
	*/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {
		if (DisplayDocumentStore() == OPR_END) {	/* 表示を行った時 */
			return;
		}
	}
#else

 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 電話中原稿設定表示追加 Added by SMuratec L.Z.W 2003/11/25 */
	/*----------------------------------------------*/
	/** オペレーション中であれば表示は更新しません	*/
	/** 注）電話中は、SYS_PANEL_BUSYがONしています	*/
	/*----------------------------------------------*/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_OPERATE) {
		return;
	}
	
	/** 電話中の表示 */
	/* SYS_OPERATEがOFFで、SYS_PANEL_BUSYがONしているのは電話中だけです
	*/
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PANEL_BUSY) {
		DisplayNCUStatus();
		return;
	}
 #else
 
	/*----------------------------------------------*/
	/** オペレーション中であれば表示は更新しません	*/
	/** 注）電話中は、SYS_PANEL_BUSYがONしています	*/
	/*----------------------------------------------*/
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_OPERATE)
	 || (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PANEL_BUSY)) {
		return;
	}
 #endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	/*--------------------------------------*/
	/** チャイルド表示中はなにも表示しない	*/
	/*--------------------------------------*/
	if (CheckChildDisplay() == TRUE) {
		return;
	}
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/21 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) &&
		(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
		ClearDisplayHigh();
		ClearDisplayLow();

		/** 下段の表示 */
		DisplayStringLow(0, D2W_Wait);
		return;
	}
#endif		/* End of (defined (KEISATSU)) */

	/*--------------*/
	/** 完了表示	*/
	/*--------------*/
#if (PRO_CLASS1 == DISABLE)
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
	if ((tskno_faxcom_complete     != 0xffff)		/** 通信完了 */
	 || (timer_store_copy_complete != 0xff)			/** コピー原稿蓄積完了 <- tskno_store_complete T.Nose 1997/03/11 */
	 || (timer_store_fax_complete  != 0xff)			/** メモリー送信原稿蓄積完了 by K.Watanabe 1997/11/19 */
	 || (tskno_inf_complete        != 0xffff)		/** ｲﾝﾀｰﾈｯﾄFAX　通信完了表示　by Y.Tanimoto */
	 || (tskno_print_complete      != 0xffff)) {	/** 印字完了 */
		DisplayComplete();
		return;
	}
 #else	/* by Y.Tanimoto end of "PRO_DIALUP_INTERNET_FAX == ENABLE" */
	if ((tskno_faxcom_complete     != 0xffff)		/** 通信完了 */
	 || (timer_store_copy_complete != 0xff)			/** コピー原稿蓄積完了 <- tskno_store_complete T.Nose 1997/03/11 */
	 || (timer_store_fax_complete  != 0xff)			/** メモリー送信原稿蓄積完了 by K.Watanabe 1997/11/19 */
	 || (tskno_print_complete      != 0xffff)) {	/** 印字完了 */
		DisplayComplete();
		return;
	}
 #endif	/* by Y.Tanimoto end of "PRO_DIALUP_INTERNET_FAX == ENABLE" */
#else
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
	if ((tskno_faxcom_complete     != 0xffff)		/** 通信完了 */
	 || (timer_store_copy_complete != 0xff)			/** 蓄積完了 <- tskno_store_complete T.Nose 1997/03/11 */
	 || (timer_store_fax_complete  != 0xff)			/** メモリー送信原稿蓄積完了 by K.Watanabe 1997/11/19 */
	 || (tskno_print_complete      != 0xffff)		/** 印字完了 */
	 || (tskno_inf_complete        != 0xffff)		/** ｲﾝﾀｰﾈｯﾄFAX　通信完了表示　by Y.Tanimoto */
	 || (tskno_pc_fax_complete     != 0xffff)) {	/** ＰＣーＦＡＸ終了 */
		DisplayComplete();
		return;
	}
 #else	/* by Y.Tanimoto end of "PRO_DIALUP_INTERNET_FAX == ENABLE" */
	if ((tskno_faxcom_complete     != 0xffff)		/** 通信完了 */
	 || (timer_store_copy_complete != 0xff)			/** 蓄積完了 <- tskno_store_complete T.Nose 1997/03/11 */
	 || (timer_store_fax_complete  != 0xff)			/** メモリー送信原稿蓄積完了 by K.Watanabe 1997/11/19 */
	 || (tskno_print_complete      != 0xffff)		/** 印字完了 */
	 || (tskno_pc_fax_complete     != 0xffff)) {	/** ＰＣーＦＡＸ終了 */
		DisplayComplete();
		return;
	}
 #endif	/* by Y.Tanimoto end of "PRO_DIALUP_INTERNET_FAX == ENABLE" */
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
	/* ｲﾝﾀｰﾈｯﾄFAX用　COMPLETE以外の終了表示　*/
	if (tskno_inf_terminate != 0xFFFF) { /*ユーザアボート*/
		DisplayINF_Terminate();
		return;
	}
	if (tskno_inf_nomail != 0xFFFF) { /*新着メール無し*/
		DisplayINF_NoNewMail();
		return;
	}
#endif

	/*----------------------------------------------------------*/
	/** 機器エラー発生時の表示（動作中も常に表示するエラー）	*/
	/*----------------------------------------------------------*/
	/* DisplayMachineError()の中で、エラー表示を行うステータスは個別にチェックしているので
	** 特にここでステータスをチェックしてから関数を呼ばないといけない、という事はないが
	** DisplayMachineError()を呼んでしまうとエラーが無くても１ビットずつステータスをチェック
	** するので、先に大まかにチェックしてから呼ぶようにします
	** 注）ブックカバーオープン等のエラー表示をしない場合でも、DisplayMachineError()を
	** 　　呼んでしまいますが、完全に表示と一致するステータスだけチェックしようとすると、
	** 　　表示に追加する時に、必ず２箇所にチェックを追加する必要がでてくるのと、
	** 　　同じステータスの中でエラー表示をしないビットの方が少ない、と言う理由からです
	*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PC_NO_SAME_DOCUMENT)	/* 条件追加 by K.Watanabe 1998/02/23 */
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS1])
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS2])
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS3])
	 || (SYS_MachineStatus[SYS_SCANNER_STATUS])
	 || (SYS_MachineStatus[SYS_COVER_STATUS])
	 || (SYS_MachineStatus[SYS_ERROR_STATUS])
	 || (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_CIPHER_ERROR_ALARM)) {
		DisplayMachineError();
		if (OPR_DispInfo & OPR_DSP_ERROR) {	/* エラー表示を行った時 */
			return;
		}
	}
#else
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1])
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS2])
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS3])
	 || (SYS_MachineStatus[SYS_SCANNER_STATUS])
	 || (SYS_MachineStatus[SYS_COVER_STATUS])
	 || (SYS_MachineStatus[SYS_ERROR_STATUS])
	 || (SYS_MachineStatus[SYS_WARNING_STATUS])) {
		DisplayMachineError();
		if (OPR_DispInfo & OPR_DSP_ERROR) {	/* エラー表示を行った時 */
			return;
		}
	}
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Matsukuma */
/* 通信時に原稿を繰り込んだ時、約２秒表示 */
 #if (PRO_DOC_IN == DISABLE)
	if ((OPR_FeedinDispTime != 0) 
		&& (MultiLineBusy() != 0xFF)) {
 #else
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN) 
		&& (OPR_FeedinDispTime != 0) 
		&& (MultiLineBusy() != 0xFF)) {
 #endif
		DisplayStringHigh(0, D2W_TransmitReady);
		DisplayDocumentSet();
		return;
	}
#endif

	/*------------------*/
	/** 動作状態の表示	*/
	/*------------------*/
#if (PRO_FBS == DISABLE)
	/** 原稿蓄積時の表示（次原稿の表示の関係で、PRO_FBSで表示の優先度を替えます） */
 #if (PRO_DISPLAY_STOP_KEY_OPR == ENABLE) /* By H.Fujimura 1999/01/18 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)					/* 原稿蓄積中で、*/
	 && !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_DOC_STORE)) {	/* 原稿蓄積停止要求ではない*/
 #else
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {
 #endif
		if (DisplayDocumentStore() == OPR_END) {	/* 表示を行った時 */
			return;
		}
	}
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* オペレーションのデュアル対応　Added by SMuratec L.Z.W 2003/11/14 */
	if (CMN_CheckDocumentOnFeeder() == TRUE								/** ＡＤＦに原稿がセットされている時 */
		 && CMN_CheckFeederCommandEmpty() == TRUE						/** スキャナーコマンドがあらない時 Added by SMuratec L.Z.W 2003/11/19 */
		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中ではなく、*/
		 && !((DS1()&&!(DS2())&&!TXIL()))								/* FEED IN SCANNER BUSYではない　SYS_FEED_INとしては表示の問題がある*/
		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {	/* FEED OUT SCANNER BUSYではない*/
		/* 通信時に　*/
		if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) && (!CHK_ReadyModeCopy())) {
			switch (SYS_FaxCommStage) { /* 受信時だけ動作可能　*/
			case FCM_CALLED:		/**着信*/
			case FCM_RECEIVE:		/**受信*/
			case FCM_ERROR_LINE:	/** エラーラインの表示 */
			case FCM_RECEIVE_SET:	/** 相手先名の表示 */
				DisplayDocumentOnFeeder();
				DisplayDocumentSet();
				/*　受信中にメモリー残量表示が消すますので、ここで原稿蓄積用の為に追加します。*/
				mem_area = (UWORD)MEM_CountEmptyBlockRate();
				CMN_StringCopy(&DisplayBufferHigh[16], &D2W_MemoryAreaLong[16]);
				CMN_UnsignedIntToASC(&DisplayBufferHigh[16], mem_area, 3, ' ');
				DisplayStringHigh(16,&DisplayBufferHigh[16]);
				return;
			default:
				break;
			}
		}
		/*　プリント中には原稿サイズ、メモリー残量が表示されないこと　*/ /* Modified by SMuratec 李 32004/08/17 */
		else if ( (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
		 && ((!CHK_ReadyModeCopy()) || (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE))) {
		}
		else{
			DisplayDocumentOnFeeder();
			DisplayDocumentSet();
			return;
		}
	}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		
	/** 通信時の表示 */
#if (PRO_MULTI_LINE == DISABLE)
 #if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/26 */
  #if (0)
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) &&
		(!CHK_ReadyModeCopy()) && 
		(!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_IDLE))) {
  #else
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) &&
		(!CHK_ReadyModeCopy())) {
		
		if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_IDLE) &&
			 CheckIsKanyuLine()) {
			DisplayRxMode();
			DisplayStringLow(0, D2W_IsseiShireiKido);
			return;
		}
		else {
  #endif

		if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_FAXCOM) && CheckIsKanyuLine()) {
  #if (0)		/* 警察FAX QAT_ID2 Modify by SMuratec K.W.Q 2005/12/06 */
			ClearDisplayHigh();
			ClearDisplayLow();
  #else
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
  #endif
			switch (SYS_FaxCommStage) {
			case FCM_TRANSMIT_SET:
				if (CHK_CommunicationSpeedDisplay()) {
					CMN_UnsignedIntToASC(FunctionDisplayBufferHigh, GetCommunicationSpeed(TxBaudRate), 5, ' ');
					FunctionDisplayBufferHigh[5] = 'b';
					FunctionDisplayBufferHigh[6] = 'p';
					FunctionDisplayBufferHigh[7] = 's';
					DisplayStringHigh(0, FunctionDisplayBufferHigh);
					break;
				}
			case FCM_TRANSMIT:		/** 送信時。相手機の能力がわかるまで */
				CMN_StringCopyNumNotNULL(FunctionDisplayBufferHigh, D2W_Transmit, 4);
				FunctionDisplayBufferHigh[5] = ':';

				DisplayStringHigh(0, FunctionDisplayBufferHigh);
				break;
			case FCM_ERROR_LINE:
				if (CHK_ErrorLineDisplay() && MDM_RxTotalLine) {
					CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[9], MDM_RxErrorTotalLine, 5, '0');
					FunctionDisplayBufferHigh[14] = 0x2F;	/* ' /' */
					CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[15], MDM_RxTotalLine, 5, '0');
					DisplayStringHigh(0, FunctionDisplayBufferHigh);
					break;
				}
			case FCM_RECEIVE_SET:
				if (CHK_CommunicationSpeedDisplay()) {
					CMN_UnsignedIntToASC(FunctionDisplayBufferHigh, GetCommunicationSpeed(RxBaudRate), 5, ' ');
					FunctionDisplayBufferHigh[5] = 'b';
					FunctionDisplayBufferHigh[6] = 'p';
					FunctionDisplayBufferHigh[7] = 's';
					DisplayStringHigh(0, FunctionDisplayBufferHigh);
					break;
				}
			case FCM_RECEIVE:		/**受信*/
				CMN_StringCopyNumNotNULL(FunctionDisplayBufferHigh, D2W_Receive, 5);
				FunctionDisplayBufferHigh[5] = ':';

				DisplayStringHigh(0, FunctionDisplayBufferHigh);
				break;
			}
			/* DisplayKeisatsuSettings(FunctionDisplayBufferLow); */
			/* 通信中に下段の属性表示がデフォルトに戻る不具合対策 06/01/10 石橋正和 */
			CMN_StringCopyNumNotNULL(FunctionDisplayBufferLow, D2W_Kanyu, 5);
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[6], &D2W_Issei, 4);
			if (CMN_CheckScrambleSwOn() == TRUE) {
				if (FCM_ExecutingS1Info.Available == TRUE) {
					CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[11], D2W_S_On, 5);
					if (FCM_ExecutingS1Info.Method == SYS_S1_SENYO) {
						CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[16], D2W_Senyo, 4);
					}
				}
				else {
					CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[11], D2W_S_Off, 5);
				}
			}
			/* 不具合対策ここまで */
			
			DisplayStringLow(0 , FunctionDisplayBufferLow);
			return;
		}
		else {
			switch (SYS_InternalLineNumber) {
			case SYS_STD_LINE_COM:
				if (CheckIsKanyuLine()) {
					DisplayFaxCom();
					return;
				}
				break;
			case SYS_EXT_LINE_COM:
 
				if (!(CheckIsKanyuLine())) {
					DisplayFaxCom();
					return;
				}
				break;

			}
		}
#if (1)
		}
#endif
	}
 #else
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) && (!CHK_ReadyModeCopy())) {
		DisplayFaxCom();
		return;
	}
 #endif		/* End of (defined (KEISATSU)) */
#else
	if (DisplayMultiLineFaxCom() == OPR_END) {	/* 表示を行った時 */
		return;
	}
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/18 */
	/** ナンバーディスプレイ着信表示 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY) && (!CHK_ReadyModeCopy())) {
 #if defined (KEISATSU)		/* 警察FAX ナンバーディスプレイ Added by SMuratec K.W.Q 2005/10/25 */
  #if 0 /* 警察FAX ナンバーディスプレイ Added by SMuratec 李 2005/11/23 */
@@		if ((SYS_LineNDStatus != ND_USED_IN_EXT) && CheckIsKanyuLine()){
@@			if (SYS_CalledLineNumber == SYS_TWICE_LINE_IN_CI) {
@@			}
@@			else {
@@				DisplayND_CallerID();
@@				ClearDisplayLow();
@@				return;
@@			}
@@		}
@@		else if ((SYS_LineNDStatus != ND_USED_IN_STD) && (!CheckIsKanyuLine())){
@@			DisplayND_CallerID();
@@			ClearDisplayLow();
@@			return;
@@		}
  #else
		DisplayND_CallerID();
		ClearDisplayLow();
		return;
  #endif
 #else
		DisplayND_CallerID();
		ClearDisplayLow();
		return;
 #endif
	}
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
	/*-----------------------------------*
	 *インターネットＦＡＸ動作中の表示
	 *-----------------------------------*/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_DIALUP_INTERNET_FAX) {
		DisplayInternetFax();
		return;
	}
#endif

	/** ジャムリカバー中の表示 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_JAM_RECOVER) {
		DisplayJamRecover();
		return;
	}

#if (PRO_PRINT_TYPE == LED)		/* M.Tachibana 1997/04/16 */
	/** ウォームアップ中の表示 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_WARMUP)
	 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_IMAGE_PRINT  |
													SYS_LIST_PRINT   |
													SYS_SCANNER_COPY |
													SYS_MULTI_COPY)))
	 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_MANUAL_COPY))
	 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_FCOT_INITIAL_ABORT))) {
		DisplayPrinterWarmUp();
		return;
	}
#endif

#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/01/21 */
	/** メモリ・プリント時の表示 */
	/** 復号化原稿プリント中の表示 */

	/* 受信暗号化原稿消去確認の後、復号化中にプリント中の表示をしない様にする */
	/* 注）仕様変更により、２頁目以降の復号化中でも、SYS_IMAGE_PRINTがONしたままになるので、
	** 　　復号化中ならプリント中の表示を止める必要があります。
	** 　　本来なら、その判断にSYS_DESCRAMBLE_EXECを使用するのが正しいのですが、
	** 　　受信暗号化原稿消去確認中に、このステータスがONしていないと、着信してしまうために、
	** 　　全頁終了するまでONしたままなので、復号化中のみを判断出来るように、代わりに
	** 　　SYS_DISPLAY_DESCRAMBLEを使用しています。
	*/
#if (0)	 /* By Y.Suzuki 1998/07/23 */
//	if (((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)
//	  || (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_PRINT))
//	 && ((!CHK_ReadyModeCopy()) || (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE))) {
#endif
	if (((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)
	  || (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_PRINT))
	 && !(SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DISPLAY_DESCRAMBLE)
	 && ((!CHK_ReadyModeCopy()) || (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE))) {
		DisplayImagePrint();
		return;
	}
#else
	/** メモリ・プリント時の表示 */
	/* ポプラＢで、ＰＣプリント受信原稿のプリントだけは、コピーモードでも表示します by K.Watanabe 1998/01/28 */
 #if (PRO_DISPLAY_STOP_KEY_OPR == ENABLE) /* By H.Fujimura 1999/01/18 */
  #if (PRO_PRINT_TYPE == THERMAL) /* By H.Fujimura 1999/02/18 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)			/* ｲﾒｰｼﾞ･ﾌﾟﾘﾝﾄ中で、*/
	 && !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_IMAGE_PRINT)	/* ｲﾒｰｼﾞﾌﾟﾘﾝﾄ停止要求ではない*/
	 && (SYS_DocumentPrintClass != SYS_PRINT_CLASS_INITIAL)					/* プリンターの初期化要求ではない*/
	 && ((!CHK_ReadyModeCopy()) || (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE))) {
  #else
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)			/* ｲﾒｰｼﾞ･ﾌﾟﾘﾝﾄ中で、*/
	 && !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_IMAGE_PRINT)	/* ｲﾒｰｼﾞﾌﾟﾘﾝﾄ停止要求ではない*/
	 && ((!CHK_ReadyModeCopy()) || (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE))) {
  #endif
 #else
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)
	 && ((!CHK_ReadyModeCopy()) || (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE))) {
 #endif
		DisplayImagePrint();
		return;
	}
#endif

	/** リスト・プリント時の表示 */
#if (PRO_DISPLAY_STOP_KEY_OPR == ENABLE) /* By H.Fujimura 1999/01/18 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT)			/* ﾘｽﾄ･ﾌﾟﾘﾝﾄ中で、*/
	 && !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_LIST_PRINT)	/* ﾘｽﾄ･ﾌﾟﾘﾝﾄ停止要求ではない*/
	 && (!CHK_ReadyModeCopy())) {
#else
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT) && (!CHK_ReadyModeCopy())) {
#endif
		DisplayListPrint();
		return;
	}

#if (PRO_COPY_FAX_MODE == ENABLE)	/* 1997/08/13 Y.Matsukuma */
	/** マルチコピープリント時の表示（マルチコピープリント中はSYS_IMAGE_PRINTはたたない） */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_MULTI_COPY)
	 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_FCOT_INITIAL_ABORT))
	 && (CHK_ReadyModeCopy())) {
		DisplayCopy(TRUE);
		return;
	}

	/** 手差しコピー時の表示 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_MANUAL_COPY) && (CHK_ReadyModeCopy())) {
		DisplayCopy(TRUE);
		return;
	}
#else
	/**スキャナ・コピー時の表示 */
 #if (PRO_DISPLAY_STOP_KEY_OPR == ENABLE) /* By H.Fujimura 1999/01/18 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)				/* ｽｷｬﾅｰ･ｺﾋﾟｰ中で、*/
	 && !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_SCANNER_COPY)) {	/* ｽｷｬﾅｰ･ｺﾋﾟｰ停止要求ではない*/
 #else
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) { /** スキャナー・コピー中なら */
 #endif
		DisplayCopy(TRUE);
		return;
	}

	/** マルチコピープリント時の表示（マルチコピープリント中はSYS_IMAGE_PRINTはたたない） */
 #if (PRO_DISPLAY_STOP_KEY_OPR == ENABLE) /* By H.Fujimura 1999/01/18 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_MULTI_COPY)				/* ﾏﾙﾁ･ｺﾋﾟｰ中で、*/
	 && !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_IMAGE_PRINT)) {	/* ｲﾒｰｼﾞﾌﾟﾘﾝﾄ停止要求ではない*/
 #else
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_MULTI_COPY) {
 #endif
		DisplayCopy(TRUE);
		return;
	}
#endif

#if (PRO_CLASS1 == ENABLE)
	/** クラス１動作中の表示 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM) {
		DisplayClass1();
		return;
	}
#endif

#if (PRO_PC_PRINT == ENABLE)
	/** ＰＣプリント原稿受信中の表示 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PC_PRINTDATA_RX) {
		DisplayPcPrint();
		return;
	}
#endif

#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/04 */
	/* 暗号化中の表示 */
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_EXEC) && (!CHK_ReadyModeCopy())) {
		DisplayCipherProcess(D2W_CipherExecute);	/* "ｽｸﾗﾝﾌﾞﾙ        99/99" */
		return;
	}

	/* 暗号化原稿復号化中の表示 */
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_EXEC) && (!CHK_ReadyModeCopy())) {
		DisplayCipherProcess(D2W_DecipherExecute);	/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ  99/99" */
		return;
	}
#endif

	/** 原稿繰り込み中の表示（ＡＤＦに原稿をセットした時に、少しだけ繰り込む仕様の時のみ） */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN) {
		/* DisplayDocumentSet(CMN_GetDocumentScanSize()); T.Nose 1997/05/19 */
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* (紙の初期繰り込みの時に表示するはF200と同じくなります) Modify by SMuratec L.Z.W 2003/10/20 */
		DisplayDocumentSet();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		return;
	}

#if (PRO_DISPLAY_STOP_KEY_OPR == DISABLE) /* By H.Fujimura 1999/01/18 */
	/** 原稿排出中の表示 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT) && (!CHK_ReadyModeCopy())) {
		DisplayFeedOut();
		return;
	}
#endif

#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/21 */
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {
		DisplayWaitAMinutes();	/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
		return;
	}
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	/*------------------------------------------------------*/
	/** 機器エラー発生時の表示（待機中のみ表示するエラー）	*/
	/** 注）必ず、DisplayIdle()の直前でcallすること			*/
	/*------------------------------------------------------*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1]) {
		DisplayMachineError2();
		if (OPR_DispInfo & OPR_DSP_ERROR) {	/* エラー表示を行った時 */
			return;
		}
	}
#endif

	/** アイドル状態の表示 */
	DisplayIdle();
	OPR_DispInfo = OPR_DSP_IDLE;	/* 待機表示をセット */
}

/*************************************************************************
	module		:[エラー状態表示（動作中も常に表示するエラー）]
	function	:[
		1.機器エラー発生時のＬＣＤ表示を行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/24]
	author		:[渡辺一章]
*************************************************************************/
void DisplayMachineError(void)
{
	OPR_DispInfo = DisplayMachineErrorLow(OPR_ERROR_DISP);

	/* 下段にのみエラー表示を行っている時の上段表示 */
	if ((OPR_DispInfo & OPR_DSP_ERROR) == OPR_DSP_ERROR_LOW) {
		DisplayMachineErrorHigh();
	}

#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1997/12/05 */
	if (OPR_DispInfo & OPR_DSP_ERROR) {	/* エラー表示時 */
		if (OPR_CopyParamCheck == OPR_NO_PARAM_CHK) {	/* コピー開始，用紙・倍率変更前の時 */
			OPR_CopyParamCheck = OPR_PARAM_CHK;	/* 用紙・倍率確認状態に、確認必要ありをセット */
		}
	}
#endif
}

/*************************************************************************
	module		:[エラー状態表示（上段機器状態）]
	function	:[
		1.エラーが発生した時の機器状態を、上段に表示します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/24]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayMachineErrorHigh(void)
{
#if (PRO_MULTI_LINE == ENABLE)
	UBYTE	i;
#endif

	/** 原稿蓄積中 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {
		ClearDisplayHigh();
	}
 #if defined (KEISATSU)		/* 警察FAX QAT Added by SMuratec K.W.Q 2005/12/06 */
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) &&
			(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_IDLE) &&
			CheckIsKanyuLine()) {
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');	

		DisplayKeisatsuSettings(FunctionDisplayBufferHigh);
	   	DisplayStringHigh(0,FunctionDisplayBufferHigh);
	}
 #endif		/* End of (defined (KEISATSU)) */

	/** 通信中 */
#if (PRO_MULTI_LINE == DISABLE)
 /* 警察FAX DVT Modify by SMuratec K.W.Q 2005/12/01 
 ** 指令のDCS待ちモードで、エラー発生して、LCDの上段をクリア対応
 */
 #if defined (KEISATSU)
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) &&
			(!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_IDLE)) && 
			/* 警察FAX DVT_ID55 Added by SMuratec 夏 2005/12/05 */
			(((SYS_InternalLineNumber == SYS_STD_LINE_COM) && (CheckIsKanyuLine())) ||
			((SYS_InternalLineNumber == SYS_EXT_LINE_COM) && (!CheckIsKanyuLine()))) &&
			(!CHK_ReadyModeCopy())) { 
 #else
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) && (!CHK_ReadyModeCopy())) {
 #endif		/* End of (defined (KEISATSU)) */
		ClearDisplayHigh();
		/* ﾎﾟｰﾘﾝｸﾞ受信中にｶｾｯﾄｵｰﾌﾟﾝでｿｳｼﾝを表示してしまうため 1997/12/15  By T.Yamaguchi */
		if (SYS_FaxCommStage == FCM_POLLING) {	/** ポーリング */
			DisplayStringHigh(0, D2W_PollingCommunication);	/* "ﾎﾟｰﾘﾝｸﾞ             " */
		}
		else {
			/*警察FAX DVT_ID61 Added by SMuratec 夏 2005/12/08 */
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_FAXCOM){
				CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
				if (SYS_FaxComType==SYS_MANUAL_TX){
					CMN_StringCopyNumNotNULL(DisplayBufferHigh, D2W_Transmit, 4);
				}
				else {
					CMN_StringCopyNumNotNULL(DisplayBufferHigh, D2W_Receive, 5);
				}
				DisplayStringHigh(0, DisplayBufferHigh);
				return;
			}
			
			if (FaxComTXorRX_Sign == TX_COM_MODE) {	/* 送信中 */
#if defined (KEISATSU)		/* 警察FAX DVT_ID28 Modify by SMuratec K.W.Q 2005/11/04 */
 #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
				ClearDisplayHigh();
 #endif
				CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
				CMN_StringCopyNumNotNULL(DisplayBufferHigh, D2W_Transmit, 4);
 #if 0 /* 警察FAX QAT_ID1 by SMuratec 夏 2005/12/05 */
				DisplayBufferHigh[5] = ':';
 #endif
 #if (0)/* 警察FAX DVT Delete by SMuratec K.W.Q 2005/11/14 */
				SetDialDataToDispBuffer(OPR_TX_DISPLAY, &SYB_CommandFile[SYS_DocumentStoreNo], &DisplayBufferHigh[6]);
 #endif
				DisplayStringHigh(0, DisplayBufferHigh);
#else
				DisplayStringHigh(0, D2W_Transmit);	/* "ｿｳｼﾝ                " */
#endif		/* End of (defined (KEISATSU)) */
			}
			if (FaxComTXorRX_Sign == RX_COM_MODE) {	/* 受信中 */
				if (SYS_FaxCommStage != FCM_CALLED) {
#if defined (KEISATSU)		/* 警察FAX DVT_ID28 Modify by SMuratec K.W.Q 2005/11/04 */
 #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
					ClearDisplayHigh();
 #endif
					CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
					CMN_StringCopyNumNotNULL(DisplayBufferHigh, D2W_Receive, 5);
 #if 0 /* 警察FAX QAT_ID1 by SMuratec 夏 2005/12/05 */
					DisplayBufferHigh[5] = ':';
 #endif

 #if (0)/* 警察FAX DVT Delete by SMuratec K.W.Q 2005/11/14 */
					if (NonStandardID[0] != NULL) {		/*相手機のＴＴＩあり。(NSSに相手先名がセットされている) */
						CMN_StringCopy(&DisplayBufferHigh[6], NonStandardID);
					}
					else if (StandardID[0] != NULL) {	/*相手機のＩＤあり。(TSIに相手先番号がセットされている) */
						CMN_StringCopy(&DisplayBufferHigh[6], StandardID);
					}
 #endif

					DisplayStringHigh(0, DisplayBufferHigh);
#else
					DisplayStringHigh(0, D2W_Receive);	/* "ｼﾞｭｼﾝ     " */
#endif		/* End of (defined (KEISATSU)) */
				}
			}
		}
	}
#else
	else if (((i = MultiLineBusy()) != 0xFF) && (!CHK_ReadyModeCopy())) {	/** 通信中なら */
		if (i == 0) {	/** ホストなら */
			ClearDisplayHigh();
			/* ﾎﾟｰﾘﾝｸﾞ受信中にｶｾｯﾄｵｰﾌﾟﾝでｿｳｼﾝを表示してしまうため 1997/12/15  By T.Yamaguchi */
			if (SYS_FaxCommStage == FCM_POLLING) {	/** ポーリング */
				DisplayStringHigh(0, D2W_PollingCommunication);	/* "ﾎﾟｰﾘﾝｸﾞ             " */
			}
			else {
				if (FaxComTXorRX_Sign == TX_COM_MODE) {	/* 送信中 */
					DisplayStringHigh(0, D2W_Transmit);	/* "ｿｳｼﾝ                " */
				}
				if (FaxComTXorRX_Sign == RX_COM_MODE) {	/* 受信中 */
					if (SYS_FaxCommStage != FCM_CALLED) {
						DisplayStringHigh(0, D2W_Receive);	/* "ｼﾞｭｼﾝ     " */
					}
				}
			}
		}
		else {
			ClearDisplayHigh();
			if (SYS_Opt[i].FaxComTXorRX_Sign == TX_COM_MODE) {	/* 送信中 */
				DisplayStringHigh(0, D2W_Transmit);	/* "ｿｳｼﾝ                " */
			}
			if (SYS_Opt[i].FaxComTXorRX_Sign == RX_COM_MODE) {	/* 受信中 */
				if (SYS_FaxCommStage != FCM_CALLED) {
					DisplayStringHigh(0, D2W_Receive);	/* "ｼﾞｭｼﾝ     " */
				}
			}
		}
	}
#endif	/* (PRO_MULTI_LINE == DISABLE) */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/18 */
	/** ナンバーディスプレイ着信表示 */
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY) && (!CHK_ReadyModeCopy())) {
		DisplayND_CallerID();
	}
#endif

	/** プリント中 */
#if (PRO_PRINT_TYPE == THERMAL) /* By H.Fujimura 1999/02/18 */
	else if ((((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)
		    && (SYS_DocumentPrintClass != SYS_PRINT_CLASS_INITIAL))			/* プリンターの初期化要求ではない*/
		   || (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT))
		  && (!CHK_ReadyModeCopy())) {
		ClearDisplayHigh();
	}
#else
	else if (((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)
		   || (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT))
		  && (!CHK_ReadyModeCopy())) {
		ClearDisplayHigh();
	}
#endif

	/** コピー中 */
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)
		  || (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_MULTI_COPY)
		  || (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_MANUAL_COPY)) {
#if (PRO_COPY_FAX_MODE == ENABLE)
		if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
			DisplayCopy(FALSE);
		}
		else {						/* ファクスモードの時 */
			ClearDisplayHigh();
		}
#else
		DisplayCopy(FALSE);
#endif
	}

#if (PRO_DISPLAY_STOP_KEY_OPR == DISABLE) /* By H.Fujimura 1999/01/18 */
	/** 原稿排出中 */
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT) && (!CHK_ReadyModeCopy())) {
		DisplayDocumentOnFeeder();
	}
#endif

#if (PRO_CLASS1 == ENABLE) /* 1996/09/13 Eguchi */
	/** クラス１動作中 */
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM) && (!CHK_ReadyModeCopy())) {
		DisplayStringHigh(0, D2W_PC_FAX_Connect);	/* "PC-FAX ｾﾂｿﾞｸ        " */
	}
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
	/**　インターネットＦＡＸ動作中　*/
	else if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_DIALUP_INTERNET_FAX) { /** インターネットＦＡＸ動作中 */
		DisplayINF_ExecKind();
	}
#endif

	/** 待機中の表示 */
	else {
		DisplayIdle();
	}
}

/*************************************************************************
	module		:[エラー状態表示（下段エラー内容）]
	function	:[
		1.ＬＣＤ下段にエラーの内容を表示します
	]
	return		:[
		OPR_DSP_NO_ERROR		:エラー未表示
		OPR_DSP_ERROR_HIGH		:エラー表示（上段を使用）
		OPR_DSP_ERROR_LOW		:　　〃　　（下段を使用）
		（以下はポプラＢでのみ使用）
		OPR_DSP_SCAN_DISABLE	:　　〃　　（読み取り不可能エラー）
		OPR_DSP_PRINT_DISABLE	:　　〃　　（プリント不可能エラー）
	]
	common		:[
		SYS_MachineStatus
		FaxComTXorRX_Sign
	]
	condition	:[]
	comment		:[
		アンズにおけるカセットの扱い
			上段カセットー＞ＭＰトレイ（脱着不可能）
			下段カセットー＞オプションカセット
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/24]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE DisplayMachineErrorLow(UBYTE is_error_disp)
{
	UBYTE	ret;	/* リターン値 */

	ret = OPR_DSP_ERROR_LOW;	/* エラー表示（下段を使用）をセット */

/*--------------------*/
/* ポプラＢ・ポプラＬ */
/*--------------------*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_COPY_FAX_MODE == ENABLE)
	/** 手差し記録紙なし */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_MANUAL_PAPER) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayReplacePaperSize(SYS_MANUAL_CASSETTE);
		}
		ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
		return(ret);
	}
 #endif

	/** メモリーオーバー */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			ClearDisplayHigh();	/* サービスからの要望により上段クリア by K.Watanabe 1997/11/14 */
			DisplayStringLow(0, D2W_MemoryOverFlow);				/* "ﾒﾓﾘ ｵｰﾊﾞｰ ﾃﾞｽ       " */
		}
		ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
		return(ret);
	}

 #if (PRO_PC_PRINT == ENABLE)		/* 1998/02/12 By M.Kuwahara */
	/** ＰＣプリントメモリオーバー */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_PC_MEMORY_OVER) {
/*	if (SYS_PcMemoryOverDispRequest) {	*/
		if (is_error_disp) {	/* エラー表示を行う時 */
			ClearDisplayHigh();
			DisplayStringLow(0, D2W_PC_MemoryOverFlow);				/* "PCﾒﾓﾘ ｵｰﾊﾞｰ ﾃﾞｽ     " */
		}
		ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
		return(ret);
	}
 #endif

#if defined (KEISATSU) /* 警察FAX 05/11/16 石橋正和 */
	/* S1アラーム */
	if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_S1) && (!CHK_ReadyModeCopy())) {
		if (is_error_disp) { /* エラー表示を行う時 */
			DisplayStringLow(0, D2W_S1Alarm); /* "Sｱﾗｰﾑ               " */
		}
		return(ret);
	}
#endif
	
	/** 通信エラー */
	if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_FAXCOM) && (!CHK_ReadyModeCopy())) {
#if (PRO_KEYPANEL == PANEL_STOCKHM2) /* QAT修正  By SMuratec 李 2004/10/27 */
		if ( !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) ) {
			if (is_error_disp) {	/* エラー表示を行う時 */
				DisplayStringLow(0, D2W_CommunicationError);			/* "ﾂｳｼﾝ ｴﾗｰ            " */
			}
			return(ret);
		}
#else
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CommunicationError);			/* "ﾂｳｼﾝ ｴﾗｰ            " */
		}
		return(ret);
#endif /* (PRO_KEYPANEL == PANEL_STOCKHM2) */
	}

#if defined(KEISATSU)	/* 警察FAX DVT by SMuratec 夏 2005/11/19 */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) {
 /* 警察FAX DVT_ID56 Modify start by SMuratec 夏 2005/12/06 */
 #if 0
		if (is_error_disp && 
		  (((Hangup_Line & SYS_LINE_KANYU_HANGUP) && CheckIsKanyuLine())||
		  ((Hangup_Line & SYS_LINE_KEIDEN_HANGUP) && !CheckIsKanyuLine()))) {	/* エラー表示を行う時 */
			DisplayStringHigh(0, D2W_HungUpPhone);					/* "ｼﾞｭﾜｷ ｶﾞ ｱｶﾞｯﾃｲﾏｽ   " */
			ClearDisplayLow();
			ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
		}
		else{
		
			ret = OPR_DSP_NO_ERROR;	/* エラー未表示をセット */
		}
		return(ret);
 #else
		if (((Hangup_Line & SYS_LINE_KANYU_HANGUP) && CheckIsKanyuLine())||
		  ((Hangup_Line & SYS_LINE_KEIDEN_HANGUP) && !CheckIsKanyuLine())) {	/* エラー表示を行う時 */
			if (is_error_disp){
				DisplayStringHigh(0, D2W_HungUpPhone);					/* "ｼﾞｭﾜｷ ｶﾞ ｱｶﾞｯﾃｲﾏｽ   " */
				ClearDisplayLow();
			}
			ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
			return(ret);
		}
 #endif 
	}
#else
	/** ハングアップエラー */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) {
		/* 通信エラーとハングアップが同時に発生した場合は、アラームはハングアップブザーだが表示は通信エラー表示になる
		** ハングアップの優先順位をあげると、通信エラーの表示が一瞬ちらつく様に見えるのでこのようにしている
		** （桐／椛と同じです）
		*/
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringHigh(0, D2W_HungUpPhone);					/* "ｼﾞｭﾜｷ ｶﾞ ｱｶﾞｯﾃｲﾏｽ   " */
			ClearDisplayLow();
		}
		ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
		return(ret);
	}
#endif
 #if (PRO_CLASS1 == ENABLE) /* 1996/09/13 Eguchi */ /* 取り敢えずこの位置にいれておく */
	if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_CLASS1_INIT) && (!CHK_ReadyModeCopy())) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PC_FAX_InitialError);			/* "PC-FAX ｼｮｷｶ ｴﾗｰ     " */
		}
		return(ret);
	}
 #endif

 #if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/04 */
	/* 暗号化・復号化中メモリオーバー */
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_MEM_OVER)
	 || (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_MEM_OVER)) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			ClearDisplayHigh();
			DisplayStringLow(0, D2W_MemoryOverFlow);				/* "ﾒﾓﾘ ｵｰﾊﾞｰ ﾃﾞｽ       " */
		}
		ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
		return(ret);
	}

	/* 暗号化中エラー */
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_ERROR) && (!CHK_ReadyModeCopy())) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CipherExecuteError);			/* "ｽｸﾗﾝﾌﾞﾙ ｴﾗｰ         " */
		}
		return(ret);
	}

	/* 復号化中エラー */
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_ERROR) && (!CHK_ReadyModeCopy())) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_DecipherExecuteError);			/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ｴﾗｰ   " */
		}
		return(ret);
	}
 #endif

	/** ランプ確認 */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_LAMP_ERROR) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CallForService);				/* "ﾗﾝﾌﾟ ｶｸﾆﾝ           " */
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}

 #if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	/** プリンターカバーオープン */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseCloseTopCover);			/* "ﾄｯﾌﾟｶﾊﾞｰ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}

	/** プリンターカバーオープン（ＲＸＩＬ瞬断） by K.Watanabe 1998/03/05 */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_MOMENT_TOP_COVER_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseCloseTopCover);			/* "ﾄｯﾌﾟｶﾊﾞｰ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}
 #else									/* ポプラＬのロジック追加 by K.Watanabe 1998/01/19 */
	/* プリンタユニットカバーが開けられたら、表示は"ﾄｯﾌﾟｶﾊﾞｰ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ" → "ﾌﾟﾘﾝﾀｶﾊﾞｰｦ ﾄｼﾞﾃｸﾀﾞｻｲ"にします */

	/** プリンタユニットカバーオープン */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClosePrinterCover);		/* "ﾌﾟﾘﾝﾀｶﾊﾞｰｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}

	/** トップカバーオープン */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseCloseTopCover);			/* "ﾄｯﾌﾟｶﾊﾞｰ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}
 #endif

	/** スキャナーカバー */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseCloseScannerCover);		/* "ｹﾞﾝｺｳｶﾊﾞｰｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		}
 #if (PRO_FBS == DISABLE)
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
 #endif
		return(ret);
	}

	/** 繰り込み不良 */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringHigh(0, D2W_PleaseOpenCloseScanCover);		/* "ｹﾞﾝｺｳｶﾊﾞｰ ｦ ｶｲﾍｲｼﾃ  " */
 #if (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/15 */
			DisplayStringLow(0, D2W_ScannerFeedErrorLow);			/* "ｶｲﾍｲｼ ｹﾞﾝｺｳ ｻｲｾｯﾄ   " */
 #else
			DisplayStringLow(0, D2W_ResetDocument);					/* "ｹﾞﾝｺｳｾｯﾄ ﾔﾘﾅｵｼﾃｸﾀﾞｻｲ" */
 #endif
		}
 #if (0)	/* 上段表示追加 by K.Watanabe 1998/01/14 */
 //		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
 #endif
		/* エラー表示（上段を使用・読み取り不可能エラー）をセット */
		ret |= (OPR_DSP_ERROR_HIGH | OPR_DSP_SCAN_DISABLE);
		return(ret);
	}

 #if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/06/12 */
	/** スクランブル原稿長エラー */
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_LENGTH_ERROR) && (!CHK_ReadyModeCopy())) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_NotScanDocSize);				/* "ｹﾞﾝｺｳ ｻｲｽﾞ ｶｸﾆﾝ     " */
		}
		return(ret);
	}
 #endif

	/** 枚数エラー */
	if ((SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_PAGE_ERROR) && (!CHK_ReadyModeCopy())) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CheckDocument);					/* "ﾏｲｽｳ ｦ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ " */
		}
		return(ret);
	}

	/** ミラーキャリッジエラー */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_ERROR) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_MirrorCarrigeError);			/* "ﾐﾗｰｷｬﾘｯｼﾞ ｴﾗｰ       " */
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}

	/** ジャムカバーオープン（１段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_JAM_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose1stJamCover);		/* "ｻｲﾄﾞｶﾊﾞｰ1ｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** ジャムカバーオープン（２段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_2JAM_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose2ndJamCover);		/* "ｻｲﾄﾞｶﾊﾞｰ2ｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** ジャムカバーオープン（３段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_3JAM_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose3rdJamCover);		/* "ｻｲﾄﾞｶﾊﾞｰ3ｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** 排出ジャム・搬送ジャム */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ジャム時の表示内容を変更します。By H.Fujimura 1999/03/09 */
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_EXIT_JAM)
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_REG_JAM)) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseRemovePaper);				/* "ｷﾛｸｼ ｦ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}
#else
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_EXIT_JAM)
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_REG_JAM)) {
		if (is_error_disp) {	/* エラー表示を行う時 */
 #if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* ポプラＬのワーディング変更 by K.Watanabe 1998/01/28 */
			DisplayStringHigh(0, D2W_PleaseOpenTopCover);			/* "ﾄｯﾌﾟｶﾊﾞｰ ｦ ｱｹﾃ      " */
 #else
			DisplayStringHigh(0, D2W_PleaseOpenPrinterCover);		/* "ﾌﾟﾘﾝﾀｶﾊﾞｰ ｦ ｱｹﾃ     " */
 #endif
			DisplayStringLow(0, D2W_PleaseRemovePaper);				/* "ｷﾛｸｼ ｦ ﾄﾘﾉｿﾞｲﾃｸﾀﾞｻｲ " */
		}
		/* エラー表示（上段を使用・プリント不可能エラー）をセット */
		ret |= (OPR_DSP_ERROR_HIGH | OPR_DSP_PRINT_DISABLE);
		return(ret);
	}
#endif

	/** 給紙ジャム（手差し） */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_MANUAL_FEED_JAM) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringHigh(0, D2W_RemoveManualPaper);			/* "ﾃｻﾞｼﾖｳｼ ｦ ﾄﾘﾉｿﾞｲﾃ   " */
			DisplayStringLow(0, D2W_PleaseOpenCloseTopCover);		/* "ﾄｯﾌﾟｶﾊﾞｰ ｦ ｶｲﾍｲｸﾀﾞｻｲ" */
		}
		/* エラー表示（上段を使用・プリント不可能エラー）をセット */
		ret |= (OPR_DSP_ERROR_HIGH | OPR_DSP_PRINT_DISABLE);
		return(ret);
	}

	/** 給紙ジャム（カセット） */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ジャム時の表示内容を変更します。By H.Fujimura 1999/03/09 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_MISS_FEED_JAM) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseRemovePaper);				/* "ｷﾛｸｼ ｦ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}
#else
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_MISS_FEED_JAM) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_1ST_FEED_JAM) {
				DisplayStringHigh(0, D2W_PleaseOpen1stJamCover);	/* "ｻｲﾄﾞｶﾊﾞｰ1 ｦ ｱｹﾃ     " */
			}
			else if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_2ND_FEED_JAM) {
				DisplayStringHigh(0, D2W_PleaseOpen2ndJamCover);	/* "ｻｲﾄﾞｶﾊﾞｰ2 ｦ ｱｹﾃ     " */
			}
			else if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_3RD_FEED_JAM) {
				DisplayStringHigh(0, D2W_PleaseOpen3rdJamCover);	/* "ｻｲﾄﾞｶﾊﾞｰ3 ｦ ｱｹﾃ     " */
			}
 #if (0)	/* 手差しのジャムだけ表示を変更します by K.Watanabe 1998/01/14 */
 //			else if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_MANUAL_FEED_JAM) {
 //				DisplayStringHigh(0, D2W_ManualFeedError);			/* "ﾃｻﾞｼ ｷｭｳｼﾌﾞ ﾉ       " */
 //			}
 #endif
			DisplayStringLow(0, D2W_PleaseRemovePaper);				/* "ｷﾛｸｼ ｦ ﾄﾘﾉｿﾞｲﾃｸﾀﾞｻｲ " */
		}
		/* エラー表示（上段を使用・プリント不可能エラー）をセット */
		ret |= (OPR_DSP_ERROR_HIGH | OPR_DSP_PRINT_DISABLE);
		return(ret);
	}
#endif

#if (PRO_PRINT_TYPE == THERMAL) /* By H.Fujimura 1999/01/18 */
	/**	記録紙ジャム表示	*/
#if (0) /* 1998/11/19 by T.Soneoka */
**	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM) {
#else
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM) 
	|| (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_CUTTER_ERROR)) {
#endif
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseRemovePaper);				/* "ｷﾛｸｼ ｦ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** プリンタヘッド温度異常 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_Wait);							/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
		}
		return(ret);
	}
#endif

	/** カセットオープン（１段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE1_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose1stCassette);		/* "ｶｾｯﾄ1 ｦ ﾄｼﾞﾃｸﾀﾞｻｲ   " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** カセットオープン（２段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE2_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose2ndCassette);		/* "ｶｾｯﾄ2 ｦ ﾄｼﾞﾃｸﾀﾞｻｲ   " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** カセットオープン（３段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE3_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose3rdCassette);		/* "ｶｾｯﾄ3 ｦ ﾄｼﾞﾃｸﾀﾞｻｲ   " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** 原稿サイズエラー */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_SIZE_ERROR) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringHigh(0, D2W_CheckPaperSize);				/* "ｷﾛｸｼｻｲｽﾞ ｦ ｶｸﾆﾝｼﾃ   " */
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ポプラＬのワーディング変更 by K.Watanabe 1998/01/28 */
			DisplayStringLow(0, D2W_PleaseOpenCloseTopCover);		/* "ﾄｯﾌﾟｶﾊﾞｰ ｦ ｶｲﾍｲｸﾀﾞｻｲ" */
 #else
			DisplayStringLow(0, D2W_PleaseOpenClosePrinterCover);	/* "ﾌﾟﾘﾝﾀｶﾊﾞｰｦ ｶｲﾍｲｸﾀﾞｻｲ" */
 #endif
		}
		/* エラー表示（上段を使用・プリント不可能エラー）をセット */
		ret |= (OPR_DSP_ERROR_HIGH | OPR_DSP_PRINT_DISABLE);
		return(ret);
	}

	/** ドラム交換：プリント不可 */
	/* 復活、優先順位を上げる By M.Tachibana 1998/01/27 */
	/* トナー→ドラムから、ドラム→トナーの優先順位に変更します by K.Watanabe 1998/02/03 */
 #if (PRO_DRUM_PRT_CNT == ENABLE)/* NTT のみ By Y.Suzuki 1998/07/06*/
	/* NTT 仕様は、ドラムの寿命がきてもプリントを続ける。表示は、コウカンの表示とする */
	/*if (SYS_DispReplaceDrum) {*/
	if (SYB_PrinterLifeMonitor.DrumLifeCount > (UDWORD)PRN_DrumPrintStopMax) {
 #else
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_END_DRUM) {
 #endif
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_ReplaceDrum);					/* "ﾄﾞﾗﾑ ｦ ｺｳｶﾝ ｼﾃｸﾀﾞｻｲ " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** トナー交換：プリント不可 */
	/* 優先順位を上げる By M.Tachibana 1998/01/27 */
	/* トナー→ドラムから、ドラム→トナーの優先順位に変更します by K.Watanabe 1998/02/03 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_END_TONER) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseReplaceToner);			/* "ﾄﾅｰ ｦ ｺｳｶﾝ ｼﾃｸﾀﾞｻｲ  " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** サービスコールエラー */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_ERROR_ALARM3) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseCallService);				/* "ﾃﾝｹﾝ ｦ ｵｳｹｸﾀﾞｻｲ     " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

 #if (PRO_PC_PRINT == ENABLE)	/* by K.Watanabe 1998/02/23 */
	/** 指定サイズ記録紙なし（ＰＣプリント自動カセット選択時） */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PC_NO_SAME_DOCUMENT) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			CMN_StringCopyNULL(DisplayBufferHigh, D2W_PC_Print);	/* "PC                  " */
			DisplayBufferHigh[2] = ':';
			SetPaperSizeWording(&DisplayBufferHigh[3], DPR_PCR_NoSameDocumentSize, FALSE);
			DisplayStringHigh(0, DisplayBufferHigh);				/* "PC:A4               " */
			DisplayStringLow(0, D2W_NoSamePaper);					/* "ｼﾃｲﾖｳｼ ｶﾞ ｱﾘﾏｾﾝ     " */
		}
		ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
		return(ret);
	}
 #endif

	/** 記録紙なし（すべてのカセット） */
	if (CMN_CheckPaperExist() == FALSE) {
#if (PRO_KEYPANEL == PANEL_STOCKHM2) /* QAT修正  By SMuratec 李 2004/10/27 */
#if 0 /* QAT修正：初期化での記録紙無しの表示をしない事 by SMuratec 李 2004/11/03 */
		if ( !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) ) {
#else
		if ( !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)
			&& !((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)			/* ｲﾒｰｼﾞ･ﾌﾟﾘﾝﾄ中で、*/
	 		&& (SYS_DocumentPrintClass == SYS_PRINT_CLASS_INITIAL)) ) {				/* 初期化中 */
#endif
			if (is_error_disp) {	/* エラー表示を行う時 */
				DisplayStringLow(0, D2W_ReplaceRxPaper);				/* "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ " */
			}
			return(ret);
		}
#else /* (PRO_KEYPANEL != PANEL_STOCKHM2) */
		if (is_error_disp) {	/* エラー表示を行う時 */
 #if (PRO_COPY_FAX_MODE == ENABLE)
			/* ファクスモードではカセット段数の表示をしていないので、上段をクリアしません by K.Watanabe 1997/12/24 */
			if (CHK_ReadyModeCopy()) {
				ClearDisplayHigh();
				ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
			}
 #endif
			DisplayStringLow(0, D2W_ReplaceRxPaper);				/* "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ " */
		}
		return(ret);
#endif /* (PRO_KEYPANEL == PANEL_STOCKHM2) */
	}

	/* コピーモードで、コピー中でない時 */
 #if (PRO_COPY_FAX_MODE == ENABLE)
	if ((CHK_ReadyModeCopy())
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_MULTI_COPY)
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_MANUAL_COPY)) {
		/** １段目カセット記録紙なし */
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {
			if (is_error_disp) {	/* エラー表示を行う時 */
				DisplayReplacePaperSize(SYS_1ST_CASSETTE);
			}
			ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
			return(ret);
		}

		/** ２段目カセット記録紙なし */
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) {
			if (is_error_disp) {	/* エラー表示を行う時 */
				DisplayReplacePaperSize(SYS_2ND_CASSETTE);
			}
			ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
			return(ret);
		}

		/** ３段目カセット記録紙なし */
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER3) {
			if (is_error_disp) {	/* エラー表示を行う時 */
				DisplayReplacePaperSize(SYS_3RD_CASSETTE);
			}
			ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
			return(ret);
		}
	}
	/* ファクスモードか、コピーモードでコピー中の時 */
	else {
		/** いずれかのカセットの記録紙なし */
		if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER)
		 || (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2)
		 || (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER3)) {
			if (is_error_disp) {	/* エラー表示を行う時 */
				DisplayStringLow(0, D2W_ReplaceRxPaper);			/* "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ " */
			}
			return(ret);
		}
	}
 #elif (PRO_KEYPANEL == PANEL_STOCKHM2) /* QAT修正 By SMuratec 李 2004/10/27 */
 #else
	/** いずれかのカセットの記録紙なし */
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER)
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2)
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER3)) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_ReplaceRxPaper);				/* "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ " */
		}
		return(ret);
	}
 #endif	/* (PRO_COPY_FAX_MODE == ENABLE) */

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Added by SMuratec 李 2004/06/25 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_INK) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_InkConfirm);				/* "ｲﾝｸﾘﾎﾞﾝ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ" */
		}
		return(ret);
	}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

	/** ドラムユニットなし */
	/* トナー→ドラムから、ドラム→トナーの優先順位に変更します by K.Watanabe 1998/02/03 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_DRUM) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CheckDrum);						/* "ﾄﾞﾗﾑ ｶﾞ ｱﾘﾏｾﾝ       " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** カートリッジなし */
	/* トナー→ドラムから、ドラム→トナーの優先順位に変更します by K.Watanabe 1998/02/03 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_CARTRIDGE) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_NoToner);						/* "ﾄﾅｰｶｰﾄﾘｯｼﾞ ｶﾞ ｱﾘﾏｾﾝ " */
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

 #if (0)	/* 優先順位を上げる By M.Tachibana 1998/01/27 */
 //	/** トナー交換：プリント不可 */
 //	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_END_TONER) {
 //		if (is_error_disp) {	/* エラー表示を行う時 */
 //			DisplayStringLow(0, D2W_PleaseReplaceToner);			/* "ﾄﾅｰ ｦ ｺｳｶﾝ ｼﾃｸﾀﾞｻｲ  " */
 //		}
 //		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
 //		return(ret);
 //	}
 #endif

 #if (0)	/* このステータスは使用されなくなったので削除します by K.Watanabe 1997/11/12 */
 //	/** ドラム交換：プリント不可 */
 //	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_END_DRUM) {
 //		if (is_error_disp) {	/* エラー表示を行う時 */
 //			DisplayStringLow(0, D2W_ReplaceDrum);					/* "ﾄﾞﾗﾑ ｦ ｺｳｶﾝ ｼﾃｸﾀﾞｻｲ " */
 //		}
 //		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
 //		return(ret);
 //	}
 #endif

 #if (0)	/* 以下のエラーは動作中は表示させないので、DisplayMachineErrorLow2()に移動します by K.Watanabe 1997/10/16 */
 //	/** トナーなし：プリント可(トナー残量少ない) */
 //	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_FEW_TONER) {
 //		if (is_error_disp) {	/* エラー表示を行う時 */
 //			DisplayStringLow(0, D2W_CheckTonerLevel);				/* "ﾄﾅｰ ｶﾞ ﾉｺﾘﾜｽﾞｶﾃﾞｽ   " */
 //		}
 //		return(ret);
 //	}
 //
 //	/** ドラム寿命がちかい：プリント可 */
 //	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NEAREND_DRUM) {
 //		if (is_error_disp) {	/* エラー表示を行う時 */
 //			DisplayStringLow(0, D2W_CheckDrumLife);					/* "ﾄﾞﾗﾑ ｼﾞｭﾝﾋﾞ ｼﾃｸﾀﾞｻｲ " */
 //		}
 //		return(ret);
 //	}
 #endif

	/** ダイアルイン番号確認 */
	if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_NO_DIAL_IN_NUMBER) && (!CHK_ReadyModeCopy())) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_NoStoredDialInNumber);			/* "ﾀﾞｲﾔﾙｲﾝ ｾｯﾄ ｻﾚﾃｲﾏｾﾝ " */
		}
		return(ret);
	}
#else
/*----------*/
/* アンズＬ */
/*----------*/
	/** メモリーオーバー */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER) {
		DisplayStringLow(0, D2W_MemoryOverFlow);				/* "ﾒﾓﾘ ｵｰﾊﾞｰ ﾃﾞｽ       " */
		return(ret);
	}

#if (0)	/* ANZUは従来の仕様のまま By M.Tachibana 1998/02/19 */
//#if (PRO_PC_PRINT == ENABLE)		/* 1998/02/12 By M.Kuwahara */
//	/** ＰＣプリントメモリオーバー */
//	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_PC_MEMORY_OVER) {
///*	if (SYS_PcMemoryOverDispRequest) {	*/
//		DisplayStringLow(0, D2W_PC_MemoryOverFlow);				/* "PCﾒﾓﾘ ｵｰﾊﾞｰ ﾃﾞｽ     " */
//		return(ret);
//	}
//#endif
#endif

	/** 通信エラー */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_FAXCOM) {
		DisplayStringLow(0, D2W_CommunicationError);			/* "ﾂｳｼﾝ ｴﾗｰ            " */
		return(ret);
	}

	/** ハングアップエラー */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) {
		/* 通信エラーとハングアップが同時に発生した場合は、アラームはハングアップブザーだが表示は通信エラー表示になる。
		** ハングアップの優先順位をあげると、通信エラーの表示が一瞬ちらつく様に見えるのでこのようにしている。
		** （桐／椛と同じです）
		*/
		DisplayStringHigh(0, D2W_HungUpPhone);					/* "ｼﾞｭﾜｷ ｶﾞ ｱｶﾞｯﾃｲﾏｽ   " */
		ClearDisplayLow();
		ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
		return(ret);
	}

 #if (PRO_CLASS1 == ENABLE) /* 1996/09/13 Eguchi */ /* 取り敢えずこの位置にいれておく */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_CLASS1_INIT) {
		DisplayStringLow(0, D2W_PC_FAX_InitialError);			/* "PC-FAX ｼｮｷｶ ｴﾗｰ     " */
		return(ret);
	}
 #endif

 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/28 by Y.Tanimot */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_INF_INIT) {
		DisplayStringLow(0, D2W_INF_InitialError);
		return(ret);
	}
 #endif

	/** ランプ確認 */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_LAMP_ERROR) {
		DisplayStringLow(0, D2W_CallForService);				/* "ﾗﾝﾌﾟ ｶｸﾆﾝ           " */
		return(ret);
	}

	/** スキャナーカバー */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN) {
		DisplayStringLow(0, D2W_PleaseCloseScannerCover);		/* "ｹﾞﾝｺｳｶﾊﾞｰｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		return(ret);
	}

	/** 繰り込み不良 */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR) {
		DisplayStringLow(0, D2W_ResetDocument);					/* "ｹﾞﾝｺｳｾｯﾄ ﾔﾘﾅｵｼﾃｸﾀﾞｻｲ" */
		return(ret);
	}

	/** 枚数エラー */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_PAGE_ERROR) {
		DisplayStringLow(0, D2W_CheckDocument);					/* "ﾏｲｽｳ ｦ ｶｸﾆﾝ ｼﾃｸﾀﾞｻｲ " */
		return(ret);
	}

	/** ミラーキャリッジエラー */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_ERROR) {
		DisplayStringLow(0, D2W_MirrorCarrigeError);			/* "ﾐﾗｰｷｬﾘｯｼﾞ ｴﾗｰ       " */
		return(ret);
	}

	/** 下段カセットオープン */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE2_OPEN) {
		DisplayStringLow(0, D2W_PleaseCloseLowerCassette);		/* "ｶｾｯﾄ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ    " */
		return(ret);
	}

	/** プリンターカバーオープン */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
		DisplayStringLow(0, D2W_PleaseCloseTopCover);			/* "ﾄｯﾌﾟｶﾊﾞｰ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		return(ret);
	}

	/** ジャム  */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_ERROR_JAM) {
		DisplayStringLow(0, D2W_PleaseRemovePaper);				/* "ｷﾛｸｼ ｦ ﾄﾘﾉｿﾞｲﾃｸﾀﾞｻｲ " */
		return(ret);
	}

	/** 手差しトレイの原稿サイズエラー → 解除するにはオペレーションで紙ｻｲｽﾞをセットする */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_SIZE_ERROR) {
		DisplayStringLow(0, D2W_PaperSizeError);				/* "ｷﾛｸｼﾉ ｻｲｽﾞ ｶﾞ ﾁｶﾞｲﾏｽ" */
		return(ret);
	}

	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* プリンターエラー（ServiceManCall)のエラー変更。			     */
	/* ﾌｧﾝｴﾗｰ/ﾓｰﾀｰｴﾗｰ/ﾚｰｻﾞｰｴﾗｰ/ｼﾘｱﾙｴﾗｰのみに修正しました。			 */
	/* By S.Kawasaki Jan.18,1996                                     */
	/* ---> 元に戻しました。1996/02/07 Eguchi 						 */
	/* 		メモリーエラーはANZUではあり得ません					 */
	/*****************************************************************/
	/** サービスコールエラー */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_ERROR_ALARM3) {
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/14 Y.Matsukuma */
		MinoltaPrinterErrorDisplay();
#else
		DisplayStringLow(0, D2W_PleaseCallService);				/* "ﾃﾝｹﾝ ｦ ｵｳｹｸﾀﾞｻｲ     " */
#endif
		return(ret);
	}

	/** 記録紙なし */
	if (CMN_CheckPaperExist() == FALSE) {
		/* 上下段カセットとも記録紙なし */
		/* 上段記録紙なしで下段カセットユニットなし。または */
		/* 上段記録紙なしで下段カセットありで記録紙なし     */
		DisplayStringLow(0, D2W_ReplaceRxPaper);				/* "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ " */
		return(ret);
	}

	/** トナーなし(トナー残量少ない) */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_FEW_TONER) {
		DisplayStringLow(0, D2W_PleaseSupplyToner);				/* "ﾄﾅｰ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ  " */
		return(ret);
	}

	/** ドラム寿命がちかい */
	if (SYS_MachineStatus[SYS_WARNING_STATUS] & SYS_WARNING_DRUM_REPLACE) {
		DisplayStringLow(0, D2W_ReplaceDrum);					/* "ﾄﾞﾗﾑ ｦ ｺｳｶﾝ ｼﾃｸﾀﾞｻｲ " */
		return(ret);
	}

	/* ここにくるのは次の場合 */
	/* 上段記録紙ありで下段カセットユニットなし */
	/* 上段記録紙ありで下段カセットユニットありで下段記録紙なし */
	/* 上段記録紙ありで下段カセットユニットありで下段記録紙あり */
	/* 上段記録紙なしで下段カセットユニットありで下段記録紙あり */

	/** 上段記録紙なし */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {
		DisplayStringLow(0, D2W_ReplaceUpperRxPaper);			/* "ﾄﾚｲ ﾉ ｷﾛｸｼ ｶﾞ ｱﾘﾏｾﾝ " */
		return(ret);
	}

	/** 下段記録紙なし */
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) && (SYS_SecondCassetteFlag == 1)) {
		/* 第２条件は不要かもしれないが念のため */
		DisplayStringLow(0, D2W_ReplaceLowerRxPaper);			/* "ｶｾｯﾄ ﾉ ｷﾛｸｼ ｶﾞ ｱﾘﾏｾﾝ" */
		return(ret);
	}

	/** インクリボンなし */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_INK) {
/*		DisplayStringLow(0, D2W_ReplaceDonorFilm);杏にはなし*/
		return(ret);
	}

	/** ダイアルイン番号確認 */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_NO_DIAL_IN_NUMBER) {
		DisplayStringLow(0, D2W_NoStoredDialInNumber);			/* "ﾀﾞｲﾔﾙｲﾝ ｾｯﾄ ｻﾚﾃｲﾏｾﾝ " */
		return(ret);
	}
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  */

	/** エラーの状態ではあるが、表示を書き換えない場合 */
	/* POPLAR_Bでは、記録紙なしのエラーはそのカセットが選択されていないと
	** 表示しないのでこの処理を追加しました
	** 注）この関数をCALLする時点で判断したいが、同時にエラーが立っている時の
	** 　　優先順位の関係があるので難しい
	*/
	ret = OPR_DSP_NO_ERROR;	/* エラー未表示をセット */
	return(ret);
}

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/*************************************************************************
	module		:[エラー状態表示（待機中のみ表示するエラー）]
	function	:[
		1.機器エラー発生時のＬＣＤ表示を行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/10/16]
	author		:[渡辺一章]
*************************************************************************/
void DisplayMachineError2(void)
{
	OPR_DispInfo = DisplayMachineErrorLow2(OPR_ERROR_DISP);

	/* 下段にのみエラー表示を行っている時の上段表示 */
	if ((OPR_DispInfo & OPR_DSP_ERROR) == OPR_DSP_ERROR_LOW) {
		DisplayIdle();
	}

#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1997/12/05 */
	if (OPR_DispInfo & OPR_DSP_ERROR) {	/* エラー表示時 */
		if (OPR_CopyParamCheck == OPR_NO_PARAM_CHK) {	/* コピー開始，用紙・倍率変更前の時 */
			OPR_CopyParamCheck = OPR_PARAM_CHK;	/* 用紙・倍率確認状態に、確認必要ありをセット */
		}
	}
#endif
}

/*************************************************************************
	module		:[エラー状態表示（下段エラー内容）]
	function	:[
		1.ＬＣＤ下段にエラーの内容を表示します
	]
	return		:[
		OPR_DSP_NO_ERROR		:エラー未表示
		OPR_DSP_ERROR_HIGH		:エラー表示（上段を使用）
		OPR_DSP_ERROR_LOW		:　　〃　　（下段を使用）
		（以下はポプラＢでのみ使用）
		OPR_DSP_SCAN_DISABLE	:　　〃　　（読み取り不可能エラー）
		OPR_DSP_PRINT_DISABLE	:　　〃　　（プリント不可能エラー）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/10/16]
	author		:[渡辺一章]
*************************************************************************/
UBYTE DisplayMachineErrorLow2(UBYTE is_error_disp)
{
	UBYTE	ret;	/* リターン値 */

	ret = OPR_DSP_ERROR_LOW;	/* エラー表示（下段を使用）をセット */

	/** ドラム寿命がちかい：プリント可 */
	/* トナー→ドラムから、ドラム→トナーの優先順位に変更します by K.Watanabe 1998/02/03 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NEAREND_DRUM) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CheckDrumLife);					/* "ﾄﾞﾗﾑ ｼﾞｭﾝﾋﾞ ｼﾃｸﾀﾞｻｲ " */
		}
		return(ret);
	}

	/** トナーなし：プリント可(トナー残量少ない) */
	/* トナー→ドラムから、ドラム→トナーの優先順位に変更します by K.Watanabe 1998/02/03 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_FEW_TONER) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CheckTonerLevel);				/* "ﾄﾅｰ ｶﾞ ﾉｺﾘﾜｽﾞｶﾃﾞｽ   " */
		}
		return(ret);
	}

	ret = OPR_DSP_NO_ERROR;	/* エラー未表示をセット */
	return(ret);
}
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  */

/*************************************************************************
	module		:[通信中の表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/04]
	author		:[江口]
*************************************************************************/
void DisplayFaxCom(void)
{
#if (PRO_MULTI_LINE == DISABLE)
	switch (SYS_FaxCommStage) {
#else
	switch (SYS_Display.SYS_FaxCommStage) {
#endif
	case FCM_TRANSMIT:		/** 送信時。相手機の能力がわかるまで */
	case FCM_TRANSMIT_SET:	/** 相手先の能力がわかってから*/
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/22 */
 #if (0)		/* 警察FAX QAT_ID2 Delete by SMuratec K.W.Q 2005/12/06 */
		ClearDisplayHigh();
		ClearDisplayLow();
 #endif
#endif		/* End of (defined (KEISATSU)) */
		DisplayTransmit();
		break;
	case FCM_CALLED:		/**着信*/
#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/18 */
		/** ナンバーディスプレイ着信表示 */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY) {
			DisplayND_CallerID();
		}
		else {
			ClearDisplayHigh();
		}
#else
		ClearDisplayHigh();
#endif
		DisplayStringLow(0, D2W_Called);
		break;
	case FCM_RECEIVE:		/**受信*/
#if (0)			/* 警察FAX DVT Modify by SMuratec K.W.Q 2005/11/19 */
		ClearDisplayHigh();
		ClearDisplayLow();
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/27 */
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopyNumNotNULL(DisplayBufferHigh, D2W_Receive, 5);
		DisplayBufferHigh[5] = ':';

		DisplayStringHigh(0, DisplayBufferHigh);
		
		CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	 	if (SYS_InternalLineNumber == SYS_STD_LINE_COM){
			CMN_StringCopyNumNotNULL(DisplayBufferLow, D2W_Kanyu,5);
			
			CMN_StringCopyNumNotNULL(&DisplayBufferLow[6], &D2W_Kobetsu,4);
		}
		else{
			CMN_StringCopyNumNotNULL(DisplayBufferLow, D2W_Keiden,5);
			
			if (FCM_ExecutingS1Info.Protocol == SYS_PROTOCOL_KOBETSU) {
				CMN_StringCopyNumNotNULL(&DisplayBufferLow[6], &D2W_Kobetsu,4);
			}
			else {
				CMN_StringCopyNumNotNULL(&DisplayBufferLow[6], &D2W_Issei,4);
			}
		}
		
		DisplayStringLow(0, DisplayBufferLow);
#else
		DisplayStringLow(0, D2W_Receive);	/* "ｼﾞｭｼﾝ     " */
#endif		/* End of (defined (KEISATSU)) */
		break;
#endif
	case FCM_ERROR_LINE:	/** エラーラインの表示 */
	case FCM_RECEIVE_SET:	/** 相手先名の表示 */
		DisplayReceive();
		break;
	case FCM_POLLING:		/** ポーリング */
		DisplayStringHigh(0, D2W_PollingCommunication);	/* "ﾎﾟｰﾘﾝｸﾞ             " */
		ClearDisplayLow();
		break;
	case FCM_REMOTE_FAX_TRANSMIT:	/** ソウシン */ /* 1994/09/06 Y.Murata Remote Fax Tx LCD Debug *//*ANZUにはこのパスなし*/
		DisplayStringHigh(0, D2W_Transmit);	/* "ｿｳｼﾝ                " */
		ClearDisplayLow();
		break;
	case FCM_VOICE_CALLED:	/** 会話予約の表示 */ /*相手が会話予約を掛けてきた場合である*/
		DisplayStringHigh(0, D2W_CallReservation);
		ClearDisplayLow();
		break;
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
	case FCM_FLASH_ROM_WRITING:
		ClearDisplayHigh();
		DisplayStringHigh(0, D2W_RemoteDiagMode);	/* "ｻｰﾋﾞｽﾓｰﾄﾞ           " */
		DisplayStringLow(0, D2W_Wait);	/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
		break;
#endif
	default:
		break;
	}
	
	/* Added start by SMuratec K.W.Q 2003/08/11 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	if (SYS_VoiceSwitch){
		DisplayStringHigh(0, D2W_CallReservation);
	}
#endif
	/* Added end by SMuratec K.W.Q 2003/08/11 */
	
}

/*************************************************************************
	module		:[送信時の相手先表示]
	function	:[
		1.自動発呼時の相手先電話番号表示
		2.直接ダイアルの場合:FAX番号をそのまま表示
		3.ワンタッチダイアルの場合:相手先名がセットされているなら、相手先名表示。なければ電話番号表示
		4.短縮ダイアルの場合:相手先名がセットされているなら、相手先名表示。なければ電話番号表示
	]
	return		:[なし]
	common		:[
				SYS_CurrentExecutingCommand
				SYB_CommandFile
				SYB_OnetouchDial
				SYB_SpeedDial
	]
	condition	:[]
	comment		:[手動送信時の表示をどうする？]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/10]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayTransmit(void)
{
	struct	SYS_ExecQueueData_t *ep;
	UBYTE	*size_word;
	UBYTE	size;
	UBYTE	mode;
	UBYTE	*disp_buffer_address;	/* DisplayBufferHigh上で最後尾の文字があるアドレス by J.Kishida 2002/11/18 */

#if (PRO_MULTI_LINE == DISABLE)
	/*-----------------------*/
	/* 上段表示				 */
	/*-----------------------*/

	/* 実行きゅうのポインターを獲得 */
	ep = &SYB_ExecQueue[SYS_CurrentExecQueueNo];

	/* 表示バッファクリア*/
	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	disp_buffer_address = &DisplayBufferHigh[0];	/* 変数に表示バッファの先頭アドレスを入れておく by J.Kishida 2002/11/18 */

#if (0)
** 	/* 回線速度表示異常不具合 by O.Kimoto 1999/02/01 */
** 	if (SYS_FaxCommStage == (UBYTE)(FCM_TRANSMIT_SET && CHK_CommunicationSpeedDisplay())) [
#else
	if ((SYS_FaxCommStage == FCM_TRANSMIT_SET) && CHK_CommunicationSpeedDisplay()) {
#endif

		CMN_UnsignedIntToASC(DisplayBufferHigh, GetCommunicationSpeed(TxBaudRate), 5, ' ');
		DisplayBufferHigh[5] = 'b';
		DisplayBufferHigh[6] = 'p';
		DisplayBufferHigh[7] = 's';

		disp_buffer_address = &DisplayBufferHigh[8];	/* 最後尾のアドレスをいれておく by J.Kishida 2002/11/18 */
	}
	else {
		/* 返り値を読み取るように変数追加しました by J.Kishida 2002/11/18 */
 #if defined(FRA)
		if (StandardID[0] != NULL) {
			disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh, StandardID, OPR_DISPLAY_MAX);
		}
		else if (NonStandardID[0] != NULL) {
			disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh, NonStandardID, OPR_DISPLAY_MAX);
		}
 #else
		if (NonStandardID[0] != NULL) {
			disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh, NonStandardID, OPR_DISPLAY_MAX);
		}
		else if (StandardID[0] != NULL) {
			disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh, StandardID, OPR_DISPLAY_MAX);
		}
 #endif

		else if ((ep->Status == SYS_EXEC_EXECUTE) || (ep->Status == SYS_EXEC_FORWARD_EXECUTE)){
 #if (0)
			/*
			// 一括BOXの相手先名の先頭にスペースを入れて登録した場合，
			// 発呼時にワンタッチ/短縮の相手先名の方が表示されてしまいます．
			// 
			// 一括BOXの相手先名が登録されていなければ，バッファには
			// 1文字もコピーされないので，CMN_StringCopyNumNotNULL()の返り値
			// (何文字コピーされたか)を見て判断するようにします．
			// by J.Kishida 2002/11/18
			*/
//  #if (PRO_BATCH_TX == ENABLE)
//			if (ep->Kind == SYS_BATCH_TX) {
//				CMN_StringCopyNumNotNULL(DisplayBufferHigh, SYB_BatchTxFile[ep->Number.Batch].Name, OPR_DISPLAY_MAX);
//			}
//  #endif
//			if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) [
 #else
  #if (PRO_BATCH_TX == ENABLE)
			if (ep->Kind == SYS_BATCH_TX) {
				disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh,
															   SYB_BatchTxFile[ep->Number.Batch].Name,
															   OPR_DISPLAY_MAX);
			}
  #endif
			if (disp_buffer_address == &DisplayBufferHigh[0]) {		/** 一括送信BOXのBOX名がない場合 */
 #endif
				switch (ep->ExecDial.Item) {	/** ダイアル種別毎の処理 */
				case SYS_DIRECT_DIAL:		/** ダイレクトダイアルの場合 */
					if (ep->Kind == SYS_COMMAND_TRX) {
						CMN_BCD_ToASC_StringNum(
							DisplayBufferHigh,
							SYB_CommandFile[ep->Number.Command].DialNumber.Direct[ep->ExecDial.ExecNumber.Command],
							OPR_DISPLAY_MAX);
					}

 #if (PRO_BATCH_TX == ENABLE)
					else {
						CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
												SYB_BatchTxFile[ep->Number.Batch].DialNumber[0].FaxNumber.Direct,
												OPR_DISPLAY_MAX);
					}
 #endif
 #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/11/12 */
					ChangeDisplayBuffer(DisplayBufferHigh);
 #endif
					break;
				case SYS_ONETOUCH_DIAL:		/** ワンタッチダイアル */
 #if (0)
					/*
					// ワンタッチ/短縮の相手先名の先頭にスペースを入れて登録した場合，
					// 発呼時に相手先名の上からダイヤル番号がかぶさって表示されます．
					// 
					// 単純にスペースの場合の処理を取ってしまうと，この関数の始めで
					// バッファを全てスペースで埋めてクリアしているので，本当に相手先名が
					// 登録されてない場合にダイヤル番号を表示してくれません．
					// 
					// ワンタッチ/短縮の相手先名が登録されていなければ，バッファには
					// 1文字もコピーされないので，CMN_StringCopyNumNotNULL()の返り値
					// (何文字コピーされたか)を見て判断するようにします．
					// by J.Kishida 2002/11/18
					*/
//					/** 相手先名を表示 */
//					CMN_StringCopyNumNotNULL(DisplayBufferHigh,
//											 SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Name,
//											 OPR_DISPLAY_MAX);
//					if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) [	/** ダイアル番号がない場合 */
 #else
					/** 相手先名を表示 */
					disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh,
																   SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Name,
																   OPR_DISPLAY_MAX);

					if (disp_buffer_address == &DisplayBufferHigh[0]) {	/** 相手先名がない場合 */
 #endif

#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
						/** FAX番号を表示 */
						CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
												SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Dial,
												OPR_DISPLAY_MAX);
#else
						if (ep->Status == SYS_EXEC_FORWARD_EXECUTE) {	/** 転送中の場合 */
							/** 転送先番号を表示 */
 #if (0) /* 転送中にクリアされると表示がおかしくなる不具合対策。By H.Fujimura 1999/03/24 */
 **							CMN_BCD_ToASC_StringNum(
 **								DisplayBufferHigh,
 **								SYB_SubDial[SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].SubDialPosition],
 **								OPR_DISPLAY_MAX);
 #else
							if (SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].SubDialPosition != 0xFF) {
								CMN_BCD_ToASC_StringNum(
									DisplayBufferHigh,
									SYB_SubDial[SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].SubDialPosition],
									OPR_DISPLAY_MAX);
							}
 #endif
						}
						else {											/** 転送中でない */
							/** FAX番号を表示 */
							CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
													SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Dial,
													OPR_DISPLAY_MAX);
						}
#endif

					}
 #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/11/12 */
 					ChangeDisplayBuffer(DisplayBufferHigh);
 #endif
					break;
				case SYS_SPEED_DIAL:
 #if (0)	/* ワンタッチ/短縮の相手先名が上書きされる by J.Kishida 2002/11/18 */
//					/** 相手先名を表示 */
//					CMN_StringCopyNumNotNULL(DisplayBufferHigh,
//											 SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Name,
//											 OPR_DISPLAY_MAX);
//					if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) [	/** ダイアル番号がない場合 */
 #else
					/** 相手先名を表示 */
					disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh,
																   SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Name,
																   OPR_DISPLAY_MAX);

					if (disp_buffer_address == &DisplayBufferHigh[0]) {	/** 相手先名がない場合 */
 #endif

#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
						/** FAX番号を表示 */
						CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
												SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Dial,
												OPR_DISPLAY_MAX);
#else
						if (ep->Status == SYS_EXEC_FORWARD_EXECUTE) {	/** 転送中の場合 */
							/** 転送先番号を表示 */
 #if (0) /* 転送中にクリアされると表示がおかしくなる不具合対策。By H.Fujimura 1999/03/24 */
 ** #if (0) /* 短縮転送中の転送番号が正しく表示されない不具合対策。By H.Fujimura 1999/03/24 */
 ** **							CMN_BCD_ToASC_StringNum(
 ** **								DisplayBufferHigh,
 ** **								SYB_SubDial[SYB_OnetouchDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition],
 ** **								OPR_DISPLAY_MAX);
 ** #else
 **							CMN_BCD_ToASC_StringNum(
 **								DisplayBufferHigh,
 **								SYB_SubDial[SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition],
 **								OPR_DISPLAY_MAX);
 ** #endif
 #else
							if (SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition != 0xFF) {
								CMN_BCD_ToASC_StringNum(
									DisplayBufferHigh,
									SYB_SubDial[SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition],
									OPR_DISPLAY_MAX);
							}
 #endif
						}
						else {											/** 転送中でない */
							/** FAX番号を表示 */
							CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
													SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Dial,
													OPR_DISPLAY_MAX);
						}
#endif
					}
 #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/11/12 */
 					ChangeDisplayBuffer(DisplayBufferHigh);
 #endif
					break;
				}
			}
			
		}
		else { /* 手動送信？？？ */
#if !defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/08/08 */
			CMN_StringCopy(DisplayBufferHigh, D2W_Transmit);	/* "ｿｳｼﾝ                " */
#endif		/* End of (defined (KEISATSU)) */
		}
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/08/08 */
		/*--------------------------*/
		/* 下段表示					*/
		/*--------------------------*/
 #if (1)		/* 警察FAX QAT_ID2 Added by SMuratec K.W.Q 2005/12/06 */
		CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');
 #endif
		DisplayFaxComKeisatsu(DisplayBufferLow);
		DisplayStringLow(0, DisplayBufferLow);
#endif		/* End of (defined (KEISATSU)) */
	}
	
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/06 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopyNumNotNULL(FunctionDisplayBufferHigh, D2W_Transmit, 4);
	FunctionDisplayBufferHigh[5] = ':';
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[6], DisplayBufferHigh, OPR_DISPLAY_MAX - 6);

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
#else
	DisplayStringHigh(0, DisplayBufferHigh);
#endif		/* End of (defined (KEISATSU)) */

 #if !defined (KEISATSU)		/* 警察FAX Deleted by SMuratec K.W.Q 2005/07/06 */
	/*--------------------------*/
	/* 下段表示					*/
	/*--------------------------*/
	/* 表示バッファクリア*/
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	if (SYS_FaxCommStage == FCM_TRANSMIT) {	/* フェーズＢ */
		size = SYS_DocBlock.Src.Size;
		mode = SYS_DocBlock.Src.Mode;
	}
	else {									/* フェーズＣの頭 */
		size = SYS_DocBlock.Dst.Size;

		if (SYB_MaintenanceSwitch[MNT_SW_A9] & DISPLAY_HFINE_EFINE) {
			/* 写真モードでもEFineで送信している場合Efineと表示する。*/
			/* 1996/06/19 eguchi */
			/* 評価用の処理 */
			mode = SYS_DocBlock.Dst.Mode;
		}
		else {
			/* 通常の処理 */
			if (GrayModeFlag) {
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
				if ((SYS_DocBlock.Dst.Mode == SYS_NORMAL) || (SYS_DocBlock.Dst.Mode == SYS_FINE)) {	
					mode = SYS_GRAY64;
				}
				else  {	/* S-FINE 以上の解像度の時 */
					mode = SYS_HGRAY;
				}
#else
				mode = SYS_GRAY64; /*写真モードやったらなんでもいい */
#endif
			}
			else {
				mode = SYS_DocBlock.Dst.Mode;
			}
		}
	}
 #endif		/* End of (!defined (KEISATSU)) */
	
#else	/* ここから (PRO_MULTI_LINE == ENABLE) */

	/*--------------*/
	/* マルチ回線用 */
	/*--------------*/
	/*-----------------------*/
	/* 上段表示				 */
	/*-----------------------*/

	/* 実行きゅうのポインターを獲得 */
	ep = &SYB_ExecQueue[SYS_Display.SYS_CurrentExecQueueNo];

	/* 表示バッファクリア*/
	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	disp_buffer_address = &DisplayBufferHigh[0];	/* 変数に表示バッファの先頭アドレスを入れておく by J.Kishida 2002/11/18 */

	if (SYS_Display.SYS_FaxCommStage == FCM_TRANSMIT_SET && CHK_CommunicationSpeedDisplay()) {
		CMN_UnsignedIntToASC(DisplayBufferHigh, GetCommunicationSpeed(SYS_Display.TxBaudRate), 5, ' ');
		DisplayBufferHigh[5] = 'b';
		DisplayBufferHigh[6] = 'p';
		DisplayBufferHigh[7] = 's';

		disp_buffer_address = &DisplayBufferHigh[8];	/* 最後尾のアドレスをいれておく by J.Kishida 2002/11/18 */
	}
	else {
		/* 返り値を読み取るように変数追加しました by J.Kishida 2002/11/18 */
 #if defined(FRA)	/* by M.HARADA '96/11/12 */
		if (SYS_Display.StandardID[0] != NULL) {
			disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh, SYS_Display.StandardID, OPR_DISPLAY_MAX);
		}
		else if (SYS_Display.NonStandardID[0] != NULL) {
			disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh, SYS_Display.NonStandardID, OPR_DISPLAY_MAX);
		}
 #else
		if (SYS_Display.NonStandardID[0] != NULL) {
			disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh, SYS_Display.NonStandardID, OPR_DISPLAY_MAX);
  #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/08 */
			/*--------------------------*/
			/* 下段表示					*/
			/*--------------------------*/
			DisplayFaxComKeisatsu(DisplayBufferLow);
			DisplayStringLow(0, DisplayBufferLow);
  #endif		/* End of (defined (KEISATSU)) */
		}
		else if (SYS_Display.StandardID[0] != NULL) {
			disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh, SYS_Display.StandardID, OPR_DISPLAY_MAX);
  #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/08 */
			/*--------------------------*/
			/* 下段表示					*/
			/*--------------------------*/
			DisplayFaxComKeisatsu(DisplayBufferLow);
			DisplayStringLow(0, DisplayBufferLow);
  #endif		/* End of (defined (KEISATSU)) */
		}
 #endif

		else if ((ep->Status == SYS_EXEC_EXECUTE) || (ep->Status == SYS_EXEC_FORWARD_EXECUTE)){
 #if (0)
			/*
			// 一括BOXの相手先名の先頭にスペースを入れて登録した場合，
			// 発呼時にワンタッチ/短縮の相手先名の方が表示されてしまいます．
			// 
			// 一括BOXの相手先名が登録されていなければ，バッファには
			// 1文字もコピーされないので，CMN_StringCopyNumNotNULL()の返り値
			// (何文字コピーされたか)を見て判断するようにします．
			// by J.Kishida 2002/11/18
			*/
//  #if (PRO_BATCH_TX == ENABLE)
//			if (ep->Kind == SYS_BATCH_TX) {
//				CMN_StringCopyNumNotNULL(DisplayBufferHigh, SYB_BatchTxFile[ep->Number.Batch].Name, OPR_DISPLAY_MAX);
//			}
//  #endif
//			if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) [
 #else
  #if (PRO_BATCH_TX == ENABLE)
			if (ep->Kind == SYS_BATCH_TX) {
				disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh,
															   SYB_BatchTxFile[ep->Number.Batch].Name,
															   OPR_DISPLAY_MAX);
			}
  #endif
			if (disp_buffer_address == &DisplayBufferHigh[0]) {		/** 一括送信BOXのBOX名がない場合 */
 #endif
				switch (ep->ExecDial.Item) {	/** ダイアル種別毎の処理 */
				case SYS_DIRECT_DIAL:		/** ダイレクトダイアルの場合 */
					if (ep->Kind == SYS_COMMAND_TRX) {
						CMN_BCD_ToASC_StringNum(
							DisplayBufferHigh,
							SYB_CommandFile[ep->Number.Command].DialNumber.Direct[ep->ExecDial.ExecNumber.Command],
							OPR_DISPLAY_MAX);
					}
 #if (PRO_BATCH_TX == ENABLE)
					else {
						CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
												SYB_BatchTxFile[ep->Number.Batch].DialNumber[0].FaxNumber.Direct,
												OPR_DISPLAY_MAX);
					}
 #endif
					break;
				case SYS_ONETOUCH_DIAL:		/** ワンタッチダイアル */
 #if (0)
					/*
					// ワンタッチ/短縮の相手先名の先頭にスペースを入れて登録した場合，
					// 発呼時に相手先名の上からダイヤル番号がかぶさって表示されます．
					// 
					// 単純にスペースの場合の処理を取ってしまうと，この関数の始めで
					// バッファを全てスペースで埋めてクリアしているので，本当に相手先名が
					// 登録されてない場合にダイヤル番号を表示してくれません．
					// 
					// ワンタッチ/短縮の相手先名が登録されていなければ，バッファには
					// 1文字もコピーされないので，CMN_StringCopyNumNotNULL()の返り値
					// (何文字コピーされたか)を見て判断するようにします．
					// by J.Kishida 2002/11/18
					*/
//					/** 相手先名を表示 */
//					CMN_StringCopyNumNotNULL(DisplayBufferHigh,
//											 SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Name,
//											 OPR_DISPLAY_MAX);
//					if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) [	/** ダイアル番号がない場合 */
 #else
					/** 相手先名を表示 */
					disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh,
																   SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Name,
																   OPR_DISPLAY_MAX);

					if (disp_buffer_address == &DisplayBufferHigh[0]) {	/** 相手先名がない場合 */
 #endif
#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
						/** FAX番号を表示 */
						CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
												SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Dial,
												OPR_DISPLAY_MAX);
#else
						if (ep->Status == SYS_EXEC_FORWARD_EXECUTE) {	/** 転送中の場合 */
							/** 転送先番号を表示 */
 #if (0) /* 転送中にクリアされると表示がおかしくなる不具合対策。By H.Fujimura 1999/03/24 */
 **							CMN_BCD_ToASC_StringNum(
 **								DisplayBufferHigh,
 **								SYB_SubDial[SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].SubDialPosition],
 **								OPR_DISPLAY_MAX);
 #else
							if (SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].SubDialPosition != 0xFF) {
								CMN_BCD_ToASC_StringNum(
									DisplayBufferHigh,
									SYB_SubDial[SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].SubDialPosition],
									OPR_DISPLAY_MAX);
							}
 #endif
						}
						else {											/** 転送中でない */
							/** FAX番号を表示 */
							CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
													SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Dial,
													OPR_DISPLAY_MAX);
						}
#endif
					}
					break;
				case SYS_SPEED_DIAL:
 #if (0)	/* ワンタッチ/短縮の相手先名が上書きされる by J.Kishida 2002/11/18 */
//					/** 相手先名を表示 */
//					CMN_StringCopyNumNotNULL(DisplayBufferHigh,
//											 SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Name,
//											 OPR_DISPLAY_MAX);
//					if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) [	/** ダイアル番号がない場合 */
 #else
					/** 相手先名を表示 */
					disp_buffer_address = CMN_StringCopyNumNotNULL(DisplayBufferHigh,
																   SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Name,
																   OPR_DISPLAY_MAX);

					if (disp_buffer_address == &DisplayBufferHigh[0]) {	/** 相手先名がない場合 */
 #endif
#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
						/** FAX番号を表示 */
						CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
												SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Dial,
												OPR_DISPLAY_MAX);
#else
						if (ep->Status == SYS_EXEC_FORWARD_EXECUTE) {	/** 転送中の場合 */
							/** 転送先番号を表示 */
 #if (0) /* 転送中にクリアされると表示がおかしくなる不具合対策。By H.Fujimura 1999/03/24 */
 ** #if (0) /* 短縮転送中の転送番号が正しく表示されない不具合対策。By H.Fujimura 1999/03/24 */
 ** **							CMN_BCD_ToASC_StringNum(
 ** **								DisplayBufferHigh,
 ** **								SYB_SubDial[SYB_OnetouchDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition],
 ** **								OPR_DISPLAY_MAX);
 ** #else
 **							CMN_BCD_ToASC_StringNum(
 **								DisplayBufferHigh,
 **								SYB_SubDial[SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition],
 **								OPR_DISPLAY_MAX);
 ** #endif
 #else
							if (SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition != 0xFF) {
								CMN_BCD_ToASC_StringNum(
									DisplayBufferHigh,
									SYB_SubDial[SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition],
									OPR_DISPLAY_MAX);
							}
 #endif
						}
						else {											/** 転送中でない */
							/** FAX番号を表示 */
							CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
													SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Dial,
													OPR_DISPLAY_MAX);
						}
#endif
					}
					break;
				}
			}
  #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/08 */
			/*--------------------------*/
			/* 下段表示					*/
			/*--------------------------*/
   #if (1)		/* 警察FAX QAT_ID2 Added by SMuratec K.W.Q 2005/12/06 */
			CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');
   #endif
			DisplayFaxComKeisatsu(DisplayBufferLow);
			DisplayStringLow(0, DisplayBufferLow);
  #endif		/* End of (defined (KEISATSU)) */
		}
		else { /* 手動送信？？？ */
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/08/08 */
			/*--------------------------*/
			/* 下段表示					*/
			/*--------------------------*/
			CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

		 	if (SYS_InternalLineNumber == SYS_STD_LINE_COM){
				CMN_StringCopyNumNotNULL(DisplayBufferLow, D2W_Kanyu,5);
				
				CMN_StringCopyNumNotNULL(&DisplayBufferLow[6], &D2W_Kobetsu,4);
			}
			else{
				CMN_StringCopyNumNotNULL(DisplayBufferLow, D2W_Keiden,5);
				
				if (FCM_ExecutingS1Info.Protocol == SYS_PROTOCOL_KOBETSU) {
					CMN_StringCopyNumNotNULL(&DisplayBufferLow[6], &D2W_Kobetsu,4);
				}
				else {
					CMN_StringCopyNumNotNULL(&DisplayBufferLow[6], &D2W_Issei,4);
				}
			}

 			if (CMN_CheckScrambleSwOn() == TRUE) {
				if (FCM_ExecutingS1Info.Available == FALSE)
				{
					CMN_StringCopyNumNotNULL(&DisplayBufferLow[11], D2W_S_Off,5);
				}
				else{
					CMN_StringCopyNumNotNULL(&DisplayBufferLow[11], D2W_S_On,5);

					if (FCM_ExecutingS1Info.Method == SYS_S1_SENYO){
						CMN_StringCopyNumNotNULL(&DisplayBufferLow[16], D2W_Senyo,4);
					}
				}
			}
			DisplayStringLow(0, DisplayBufferLow);

#else
			CMN_StringCopy(DisplayBufferHigh, D2W_Transmit);	/* "ｿｳｼﾝ                " */
#endif		/* End of (defined (KEISATSU)) */
		}

	}
	
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/06 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopyNumNotNULL(FunctionDisplayBufferHigh, D2W_Transmit, 4);
	FunctionDisplayBufferHigh[5] = ':';
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[6], DisplayBufferHigh, OPR_DISPLAY_MAX - 6);

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
#else
	DisplayStringHigh(0, DisplayBufferHigh);
#endif		/* End of (defined (KEISATSU)) */

#if !defined (KEISATSU)		/* 警察FAX Deleted by SMuratec K.W.Q 2005/07/06 */
	/*--------------------------*/
	/* 下段表示					*/
	/*--------------------------*/
	/* 表示バッファクリア*/
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	if (SYS_Display.SYS_FaxCommStage == FCM_TRANSMIT) {	/* フェーズＢ */
		size = SYS_Display.SYS_DocBlock_Src_Size;
		mode = SYS_Display.SYS_DocBlock_Src_Mode;
 #if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
		if ((mode == SYS_HFINE) || (mode == SYS_EFINE)) { 
			mode = SYS_SFINE;	/* S FINE 以上の解像度のとき表示をオーバーレイに合わせて S FINE とする */
		}
 #endif
	}
	else {												/* フェーズＣの頭 */
		size = SYS_Display.SYS_DocBlock_Dst_Size;

		if (SYB_MaintenanceSwitch[MNT_SW_A9] & DISPLAY_HFINE_EFINE) {
			/* 写真モードでもEFineで送信している場合Efineと表示する。*/
			/* 1996/06/19 eguchi */
			/* 評価用の処理 */
			mode = SYS_Display.SYS_DocBlock_Dst_Mode;
		}
		else {
			/* 通常の処理 */
			if (SYS_Display.GrayModeFlag) {
 #if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
				if ((SYS_DocBlock.Dst.Mode == SYS_NORMAL) || (SYS_DocBlock.Dst.Mode == SYS_FINE)) {	
					mode = SYS_GRAY64; 
				}
				else  {	/* S-FINE 以上の解像度の時 */
					mode = SYS_HGRAY;
				}
 #else
				mode = SYS_GRAY64;	/* 写真モードやったらなんでもいい */
 #endif
			}
			else {
				mode = SYS_Display.SYS_DocBlock_Dst_Mode;
			}
		}
	}
#endif		/* End of (!defined (KEISATSU)) */
#endif	/* (PRO_MULTI_LINE == DISABLE) */

#if !defined (KEISATSU)		/* 警察FAX Deleted by SMuratec K.W.Q 2005/07/06 */
	/* 原稿サイズ */
	switch (size) {
	case SYS_DOCUMENT_A4_SIZE:
 #if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用読取りサイズ表示対応] By S.Fukui Aug.25,1998  */
		size_word = D2W_PaperSize_LtLg; 
 #else
		size_word = D2W_PaperSize_A4;
 #endif
		break;
	case SYS_DOCUMENT_B4_SIZE:
		size_word = D2W_PaperSize_B4;
		break;
	case SYS_DOCUMENT_A3_SIZE:
 #if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用読取りサイズ表示対応] By S.Fukui Aug.25,1998  */
		size_word = D2W_PaperSize_Ledger;
 #else
		size_word = D2W_PaperSize_A3;
 #endif
		break;
 #if (0)	/* By M.Tachibana 1997/07/05 */
	case SYS_DOCUMENT_A5R_SIZE:
		size_word = D2W_PaperSize_A5R;
		break;
	case SYS_DOCUMENT_B5R_SIZE:
		size_word = D2W_PaperSize_B5R;
		break;
 #endif
	default:
		size_word = D2W_PaperSize_B4;
		break;
	}
	CMN_StringCopy(DisplayBufferLow, size_word);

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/10/16 */
	if (SYS_FaxComTxType == SYS_SCANNER_TX) {	/* スキャナ送信実行中で濃度、画質を設定するできます。 */
		DisplayDocumentSet();
	}
	else{
		/* 原稿モード */
		CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(mode), 10);
		DisplayStringLow(0, DisplayBufferLow);
	}
#else
	/* 原稿モード */
	CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(mode), 10);
	DisplayStringLow(0, DisplayBufferLow);
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif		/* End of (!defined (KEISATSU)) */
}

/*************************************************************************
	module		:[受信時の上段表示]
	function	:[
		1.表示する順番(優先順位）は「相手先名 > 相手先FAX番号 > "ソウシン"の順番
	]
	return		:[なし]
	common		:[
		NonStandardID		：相手先名
		StandardID			：相手先ＦＡＸ番号
		FaxComTXorRX_Sign	：送受信判別フラグ
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/10]
	author		:[江口]
*************************************************************************/
void DisplayReceive(void)
{
	UBYTE	disp_error_line;

#if (PRO_MULTI_LINE == DISABLE)
	/*---------------------------*/
	/* 上段表示   				 */
	/*---------------------------*/
	disp_error_line = 0;
	if (SYS_FaxCommStage == FCM_ERROR_LINE && CHK_ErrorLineDisplay()) { /* エラーラインの表示要求あり */
		disp_error_line = 1;
	}

	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	if (CHK_CommunicationSpeedDisplay()) {
		CMN_UnsignedIntToASC(DisplayBufferHigh, GetCommunicationSpeed(RxBaudRate), 5, ' ');
		DisplayBufferHigh[5] = 'b';
		DisplayBufferHigh[6] = 'p';
		DisplayBufferHigh[7] = 's';
	}
	else {
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/27 */
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopyNumNotNULL(DisplayBufferHigh, D2W_Receive, 5);
		DisplayBufferHigh[5] = ':';
#endif		/* End of (defined (KEISATSU)) */

		if (NonStandardID[0] != NULL) {		/*相手機のＴＴＩあり。(NSSに相手先名がセットされている) */
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/27 */
			CMN_StringCopy(&DisplayBufferHigh[6], NonStandardID);
#else
			CMN_StringCopy(DisplayBufferHigh, NonStandardID);
#endif		/* End of (defined (KEISATSU)) */
		}
		else if (StandardID[0] != NULL) {	/*相手機のＩＤあり。(TSIに相手先番号がセットされている) */
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/27 */
			CMN_StringCopy(&DisplayBufferHigh[6], StandardID);
#else
			CMN_StringCopy(DisplayBufferHigh, StandardID);
#endif		/* End of (defined (KEISATSU)) */
		}
		else {
#if (0) /* なんか変やしこめんとにする 1996/05/24 Eguchi */
			if (FaxComTXorRX_Sign == TX_COM_MODE) {/* ?????なんかへんやぞ！これ　TBD */
				CMN_StringCopy(DisplayBufferHigh, D2W_Transmit);	/* "ｿｳｼﾝ                " */
			}
#endif
		}
	}
	if (disp_error_line && MDM_RxTotalLine) {
		CMN_UnsignedIntToASC(&DisplayBufferHigh[9], MDM_RxErrorTotalLine, 5, '0');
		DisplayBufferHigh[14] = 0x2F;	/* ' /' */
		CMN_UnsignedIntToASC(&DisplayBufferHigh[15], MDM_RxTotalLine, 5, '0');
	}

 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
	if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
  #if 0
  //		CMN_UnsignedIntToASC(&DisplayBufferHigh[9], ECM_BlockCounter+1, 5, '0');
  //		DisplayBufferHigh[14] = 0x2F;	/* ' /' */
  //		CMN_UnsignedIntToASC(&DisplayBufferHigh[15], 16, 5, '0');
  #endif
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(DisplayBufferHigh, D2W_RemoteDiagMode);	/* "ｻｰﾋﾞｽﾓｰﾄﾞ           " */
	}
 #endif
	DisplayStringHigh(0, DisplayBufferHigh);

	/*------------------------------------*/
	/* 下段表示 						  */
	/*------------------------------------*/
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/09/14 */
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

 	if (SYS_InternalLineNumber == SYS_STD_LINE_COM){
		CMN_StringCopyNumNotNULL(DisplayBufferLow, D2W_Kanyu,5);
		
		CMN_StringCopyNumNotNULL(&DisplayBufferLow[6], &D2W_Kobetsu,4);
	}
	else{
		CMN_StringCopyNumNotNULL(DisplayBufferLow, D2W_Keiden,5);
		
		if (FCM_ExecutingS1Info.Protocol == SYS_PROTOCOL_KOBETSU) {
			CMN_StringCopyNumNotNULL(&DisplayBufferLow[6], &D2W_Kobetsu,4);
		}
		else {
			CMN_StringCopyNumNotNULL(&DisplayBufferLow[6], &D2W_Issei,4);
		}
	}
	
	if (CMN_CheckScrambleSwOn() == TRUE) {
		if (FCM_ExecutingS1Info.Available == FALSE)
		{
			CMN_StringCopyNumNotNULL(&DisplayBufferLow[11], D2W_S_Off,5);
		}
		else{
			CMN_StringCopyNumNotNULL(&DisplayBufferLow[11], D2W_S_On,5);

			if (FCM_ExecutingS1Info.Method == SYS_S1_SENYO){
				CMN_StringCopyNumNotNULL(&DisplayBufferLow[16], D2W_Senyo,4);
			}
		}
	}
	
	DisplayStringLow(0, DisplayBufferLow);
#else
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
	if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
		DisplayStringLow(0, D2W_Wait);	/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
	}
	else {
		CMN_StringCopy(DisplayBufferLow, D2W_Receive);	/* "ｼﾞｭｼﾝ     " */

		CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(SYS_DocBlock.Src.Mode), 10);
	}
 #else
	CMN_StringCopy(DisplayBufferLow, D2W_Receive);	/* "ｼﾞｭｼﾝ     " */

	CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(SYS_DocBlock.Src.Mode), 10);
 #endif

	DisplayStringLow(0, DisplayBufferLow);
#endif
#else
	/*--------------*/
	/* マルチ回線用 */
	/*--------------*/
	/*---------------------------*/
	/* 上段表示					 */
	/*---------------------------*/
	disp_error_line = 0;
	if (SYS_Display.SYS_FaxCommStage == FCM_ERROR_LINE && CHK_ErrorLineDisplay()) {	/* エラーラインの表示要求あり */
		disp_error_line = 1;
	}

	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	if (CHK_CommunicationSpeedDisplay()) {
		CMN_UnsignedIntToASC(DisplayBufferHigh, GetCommunicationSpeed(SYS_Display.RxBaudRate), 5, ' ');
		DisplayBufferHigh[5] = 'b';
		DisplayBufferHigh[6] = 'p';
		DisplayBufferHigh[7] = 's';
	}
	else {
		if (SYS_Display.NonStandardID[0] != NULL) {		/* 相手機のＴＴＩあり。(NSSに相手先名がセットされている) */
			CMN_StringCopy(DisplayBufferHigh, SYS_Display.NonStandardID);
		}
		else if (SYS_Display.StandardID[0] != NULL) {	/* 相手機のＩＤあり。(TSIに相手先番号がセットされている) */
			CMN_StringCopy(DisplayBufferHigh, SYS_Display.StandardID);
		}
		else {
#if (0) /* なんか変やしこめんとにする 1996/05/24 Eguchi */
//			if (FaxComTXorRX_Sign == TX_COM_MODE) {/* ?????なんかへんやぞ！これ　TBD */
//				CMN_StringCopy(DisplayBufferHigh, D2W_Transmit);	/* "ｿｳｼﾝ                " */
//			}
#endif
		}
	}

	if (disp_error_line && SYS_Display.MDM_RxTotalLine) {
		CMN_UnsignedIntToASC(&DisplayBufferHigh[9], SYS_Display.MDM_RxErrorTotalLine, 5, '0');
		DisplayBufferHigh[14] = 0x2F;  /*  /  */
		CMN_UnsignedIntToASC(&DisplayBufferHigh[15], SYS_Display.MDM_RxTotalLine, 5, '0');
	}
 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
	if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
  #if 0
  //		CMN_UnsignedIntToASC(&DisplayBufferHigh[9], ECM_BlockCounter+1, 5, '0');
  //		DisplayBufferHigh[14] = 0x2F;	/* ' /' */
  //		CMN_UnsignedIntToASC(&DisplayBufferHigh[15], 16, 5, '0');
  #endif
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(DisplayBufferHigh, D2W_RemoteDiagMode);	/* "ｻｰﾋﾞｽﾓｰﾄﾞ           " */
	}
 #endif

	DisplayStringHigh(0, DisplayBufferHigh);

	/*------------------------------------*/
	/* 下段表示 						  */
	/*------------------------------------*/
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
	if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
		CMN_StringCopy(DisplayBufferLow, D2W_Wait);	/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
	}
	else {
		CMN_StringCopy(DisplayBufferLow, D2W_Receive);	/* "ｼﾞｭｼﾝ     " */

		CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(SYS_Display.SYS_DocBlock_Src_Mode), 10);
	}
 #else
	CMN_StringCopy(DisplayBufferLow, D2W_Receive);	/* "ｼﾞｭｼﾝ     " */

	CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(SYS_Display.SYS_DocBlock_Src_Mode), 10);
 #endif

	DisplayStringLow(0, DisplayBufferLow);
#endif	/* (PRO_MULTI_LINE == DISABLE) */
}

/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[]
	author		:[江口]
*************************************************************************/
UBYTE *GetCommunicationResolution(UBYTE mode)
{
	switch (mode) {
	case SYS_NORMAL:
		return (D2W_DocNormal);
	case SYS_FINE:
		return (D2W_DocFine);
	case SYS_SFINE:
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
 		return (D2W_DocSFine);
#endif
	case SYS_HFINE:
	case SYS_EFINE:
	case SYS_E_HFINE:	/* for ANZU_L 300*400dpi 1997/11/13 by T.Soneoka */
		/*-----以下追加　1996/06/19　Eguchi ----*/
		if (SYB_MaintenanceSwitch[MNT_SW_A9] & DISPLAY_HFINE_EFINE) {
			/* 通信中のモードがHFine・EFineの場合に表示もHFine・EFineとそれぞれ表示する場合 */
			/* E_HFINEの時はﾜｰﾃﾞｨﾝｸﾞ増やすのめんどくさいしHFINEにしとく 1997/11/27 */
			if ((mode == SYS_HFINE) || (mode == SYS_E_HFINE)) {
				return (D2W_DocHFine);
			}
			if (mode == SYS_EFINE) {
				return (D2W_DocEFine);
			}
		}
		/*----以上追加 1996/06/19 Eguchi ----------*/
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
		return (D2W_DocHFine);  
#else
		return (D2W_DocSFine);
#endif

	case SYS_GRAY16:
	case SYS_GRAY16_SEP:
	case SYS_GRAY64:
	case SYS_GRAY64_SEP:
		return (D2W_DocGray);
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
 	case SYS_HGRAY:		
		return (D2W_DocHGray);
#endif
	default:
		return (D2W_DocNormal);
	}
}

/*************************************************************************
	module		:[交信速度の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/06/04]
	author		:[江口]
*************************************************************************/
UWORD GetCommunicationSpeed(UBYTE baud_rate)
{
#if (PRO_MULTI_LINE == DISABLE) && (PRO_MODEM != R288F)
	switch(baud_rate){
	case BPS2400_V27:	/* 2400bps */
		return(2400);
	case BPS4800_V27:	/* 4800bps */
		return(4800);
	case BPS7200_V29:	/* 7200bps */
	case BPS7200_V17:	/* 7200bps */
		return(7200);
	case BPS9600_V29:	/* 9600bps */
	case BPS9600_V17:	/* 9600bps */
		return(9600);
	case BPS12000_V33:	/* 12000bps */
	case BPS12000_V17:	/* 12000bps */
		return(12000);
	case BPS14400_V33:	/* 14400bps */
	case BPS14400_V17:	/* 14400bps */
		return(14400);
	case BPS300_V21:	/* 14400bps */
		return(300);
	}

#else
	switch(baud_rate){
	case BPS2400_V27:	/* 2400bps */
	case BPS2400_V34:	/* 2400bps */
		return(2400);
	case BPS4800_V27:	/* 4800bps */
	case BPS4800_V34:	/* 4800bps */
		return(4800);
	case BPS7200_V29:	/* 7200bps */
	case BPS7200_V17:	/* 7200bps */
	case BPS7200_V34:	/* 7200bps */
		return(7200);
	case BPS9600_V29:	/* 9600bps */
	case BPS9600_V17:	/* 9600bps */
	case BPS9600_V34:	/* 9600bps */
		return(9600);
	case BPS12000_V33:	/* 12000bps */
	case BPS12000_V17:	/* 12000bps */
	case BPS12000_V34:	/*12000bps */
		return(12000);
	case BPS14400_V33:	/* 14400bps */
	case BPS14400_V17:	/* 14400bps */
	case BPS14400_V34:	/* 14400bps */
		return(14400);
	case BPS16800_V34:	/* 16800bps */
		return(16800);
	case BPS19200_V34:	/* 19200bps */
		return(19200);
	case BPS21600_V34:	/* 21600bps */
		return(21600);
	case BPS24000_V34:	/* 24000bps */
		return(24000);
	case BPS26400_V34:	/* 26400bps */
		return(26400);
	case BPS28800_V34:	/* 28800bps */
		return(28800);
	case BPS31200_V34:	/* 31200bps */
		return(31200);
	case BPS33600_V34:	/* 33600bps */
		return(33600);
	case BPS300_V21:	/* 300bps */
		return(300);
	}
#endif	/* (PRO_MULTI_LINE == DISABLE) */
	return (0);	/*取り敢えず０をかえす */
}

/*************************************************************************
	module		:[通信中の表示（マルチ回線用）]
	function	:[
		1.
	]
	return		:[
		OPR_CONTINUE	:表示未更新
		OPR_END			:表示更新
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/11]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_MULTI_LINE == ENABLE)
UBYTE DisplayMultiLineFaxCom(void)
{
	UBYTE	i;

	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		return(OPR_CONTINUE);
	}

	if (((i = MultiLineBusy()) != 0xFF) && (OPR_MultiDisplayFlag != 1)) {	/** 通常で通信中なら */
		OverWriteDisplayData(i);
		DisplayFaxCom();

		if (CHK_UNI_MultiDisplayLineNumber() != 0) {
			DisplayChar(17, '(');
			DisplayChar(18, ChangeNumberToASC_Code((UBYTE)OPT_GetMultiLinrNumber(i)));
			DisplayChar(19, ')');
		}
		return(OPR_END);
	}

	/*------------*/
	/* マルチ表示 */
	/*------------*/
	/* ３回線になったときは、変更または、追加しなければならない */
	/* ホストのみ通信（オプションの状態は、表示させない） */
	if (((i = MultiLineBusy()) != 0xFF)	/* どれか通信中 */
	 && (OPR_MultiDisplayFlag == 1)		/* マルチ表示ＯＮ */
	 && (i == 0)						/* ホスト通信 */
	 && (MultiOptAllLineBusy() == 0)) {	/* オプションライン通信なし */
		OverWriteDisplayData(i);
		DisplayFaxCom();

		if (CHK_UNI_MultiDisplayLineNumber() != 0) {
			DisplayChar(17, '(');
			DisplayChar(18, ChangeNumberToASC_Code((UBYTE)1));
			DisplayChar(19, ')');
		}
		return(OPR_END);
	}

	/* オプションのみ通信 （ホストの待機状態も順番に表示させる） */
	if (((i = MultiLineBusy()) != 0xFF)
	 && (OPR_MultiDisplayFlag == 1)
	 && (i != 0)
	 && (OPT_GetMultiLinrNumber(i) == OPR_MultiLineCount)
	 && (MultiOptAllLineBusy() != 0)) {
		for (i = 1; i <= SYS_OPTION_BOARD_MAX; i++ ) {
			if (CHK_OptionLineBusy(i) != 0) {
				if (OPT_GetMultiLinrNumber(i) == OPR_MultiLineCount) {
					OverWriteDisplayData(i);
					break;
				}
			}
		}
		DisplayFaxCom();

		if (CHK_UNI_MultiDisplayLineNumber() != 0) {
			DisplayChar(17, '(');
			DisplayChar(18, ChangeNumberToASC_Code((UBYTE)OPR_MultiLineCount));
			DisplayChar(19, ')');
		}
		return(OPR_END);
	}

	/* ホスト・オプション両方とも通信 （ホスト・オプションの通信状態を順番に表示させる） */
	if (((i = MultiLineBusy()) != 0xFF)
	 && (OPR_MultiDisplayFlag == 1)
	 && (i == 0)
	 && (MultiOptAllLineBusy() != 0)) {
		if ((i == 0) && (OPT_GetMultiLinrNumber(i) == OPR_MultiLineCount)) {
			OverWriteDisplayData(i);
		}
		else {
			for (i = 1; i <= SYS_OPTION_BOARD_MAX; i++ ) {
				if (CHK_OptionLineBusy(i) != 0) {
					if (OPT_GetMultiLinrNumber(i) == OPR_MultiLineCount) {
						OverWriteDisplayData(i);
						break;
					}
				}
			}
		}
		DisplayFaxCom();

		if (CHK_UNI_MultiDisplayLineNumber() != 0) {
			DisplayChar(17, '(');
			DisplayChar(18, ChangeNumberToASC_Code((UBYTE)OPR_MultiLineCount));
			DisplayChar(19, ')');
		}
		return(OPR_END);
	}

	return(OPR_CONTINUE);
}
#endif	/* (PRO_MULTI_LINE == ENABLE) */

/*************************************************************************
	module		:[電源たち上げ時の初期表示]
	function	:[
		1.パワーオンの時の表示ｰ>プリンタのウォームアップ中の表示？
	]
	return		:[なし]
	common		:[D2W_PleaseWaitAMinute]
	condition	:[]
	comment		:[皐ではイニシャルカット時の表示、ラベンダーではインクリボンの巻き取り時に使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/10]
	author		:[江口]
*************************************************************************/
void DisplayWaitAMinutes(void)
{
	/* [                    ] */
	/* [ ** Please Wait **  ] */
	ClearDisplayHigh();
	DisplayStringLow(0, D2W_Wait);
/*	DisplayStringLow(0, D2W_PleaseWaitAMinute); 1997/02/22 M.Tachibana */
}

/*************************************************************************
	module		:[日付表示]
	function	:[
		1.カレンダー表示
		JPN:「'95y10m10d(w)  10:27」
		USA:「  May 10 95    10:27」
		EUR:「  10 May 95    10:27」
	]
	return		:[なし]
	common		:[
				CurrentTimeInBCD
				D2W_January
	]
	condition	:[]
	comment		:[\SRC\RICE\H8\SRC\DSP_DATE.Cを流用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/24]
	author		:[江口]
*************************************************************************/
void DisplayCalender(void)
{
	UBYTE year;
	UBYTE month;
	UBYTE day;
	UBYTE hour;
	UBYTE minute;

	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	year = CMN_BCD_ToDecimal(CurrentTimeInBCD.Year);
	month = CMN_BCD_ToDecimal(CurrentTimeInBCD.Month);
	day = CMN_BCD_ToDecimal(CurrentTimeInBCD.Date);
	hour = CMN_BCD_ToDecimal(CurrentTimeInBCD.Hour);
	minute = CMN_BCD_ToDecimal(CurrentTimeInBCD.Minute);

	/* 日付のセット */
	switch (DateTypeGet()) {
	case JPN_CLOCK_TYPE:	/* 日本 */
		/* ＣＧＲＡＭが書き換えられている可能性があるので、日付表示用のＣＧＲＡＭに設定します */
		InitializeCGRAM_Data();

		/* [ＹＹＹＹ年ＭＭ月ＤＤ日（Ｗ）　　　　　　] */
		if ( year >= 92 ) {
			DisplayBufferLow[0] = '1';
			DisplayBufferLow[1] = '9';
		}
		else {
			DisplayBufferLow[0] = '2';
			DisplayBufferLow[1] = '0';
		}
		CMN_UnsignedIntToASC(&DisplayBufferLow[2], (UWORD)year, 2, '0');
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		DisplayBufferLow[4] = 0xF7;											/* 年 */
#endif
		DisplayBufferLow[4] = OPR_FONT_YEAR;										/* 年 */
		CMN_UnsignedIntToASC(&DisplayBufferLow[5], (UWORD)month, 2, ' ');
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		DisplayBufferLow[7] = 0xF1;											/* 月 */
#endif
		DisplayBufferLow[7] = OPR_FONT_MONTH;										/* 月 */
		CMN_UnsignedIntToASC(&DisplayBufferLow[8], (UWORD)day, 2, ' ');
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		DisplayBufferLow[10] = 0xF0;										/* 日 */
#endif
		DisplayBufferLow[10] = OPR_FONT_DAY;										/* 日 */
		DisplayBufferLow[11] = 0x28;										/* ( */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		DisplayBufferLow[12] = (UBYTE)(CurrentTimeInBCD.Week + 0xF0 - 1);	/* 曜日 */
#endif
#if defined(HINOKI3)	/* LCDドライバ変更対応 by K.Watanabe 2004/10/22 */
		if (CurrentTimeInBCD.Week == 1) {	/* 日曜日の時 */
			DisplayBufferLow[12] = OPR_FONT_DAY;
		}
		else {								/* 月～土曜日の時 */
			DisplayBufferLow[12] = (UBYTE)(CurrentTimeInBCD.Week - 2 + OPR_FONT_MONTH);
		}
#else
		DisplayBufferLow[12] = (UBYTE)(CurrentTimeInBCD.Week - 1 + OPR_FONT_DAY);	/* 曜日 */
#endif
		DisplayBufferLow[13] = 0x29;										/* ) */
		break;

	case USA_CLOCK_TYPE:	/* アメリカ */
		/* [　　ＭＭＭ　ＤＤ　ＹＹＹＹ　　　　　　　］ */
		if ( year >= 92 ) {
			DisplayBufferLow[9] = '1';
			DisplayBufferLow[10] = '9';
		}
		else {
			DisplayBufferLow[9] = '2';
			DisplayBufferLow[10] = '0';
		}
		CMN_UnsignedIntToASC(&DisplayBufferLow[11], (UWORD)year, 2, '0');
		CMN_StringCopy(&DisplayBufferLow[2], D2W_January + (month - 1) * 4);
		CMN_UnsignedIntToASC(&DisplayBufferLow[6], (UWORD)day, 2, ' ');
		break;

	case EUR_CLOCK_TYPE:	/* ヨーロッパ */
		/* [　　ＤＤ　ＭＭＭ　ＹＹＹＹ　　　　　　　］ */
		if ( year >= 92 ) {
			DisplayBufferLow[9] = '1';
			DisplayBufferLow[10] = '9';
		}
		else {
			DisplayBufferLow[9] = '2';
			DisplayBufferLow[10] = '0';
		}
		CMN_UnsignedIntToASC(&DisplayBufferLow[11], (UWORD)year, 2, '0');
		CMN_StringCopy(&DisplayBufferLow[5], D2W_January + (month - 1) * 4);
		CMN_UnsignedIntToASC(&DisplayBufferLow[2], (UWORD)day, 2, ' ');
		break;
	}

	/* 時間のセット */
	/* [　　　　　　　　　　　　　　　ＨＨ：ＭＭ］ */
	CMN_UnsignedIntToASC(&DisplayBufferLow[15], (UWORD)hour, 2, ' ');
	DisplayBufferLow[17] = ':';
	CMN_UnsignedIntToASC(&DisplayBufferLow[18], (UWORD)minute, 2, '0');

	DisplayStringLow(0, DisplayBufferLow);
}

/*************************************************************************
	module		:[原稿排出中の表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/07/24]
	author		:[江口]
*************************************************************************/
void DisplayFeedOut(void)
{
	/*--------------------------------*/
	/* 原稿セット時の表示のままにする */
	/*--------------------------------*/

	/* 上段表示 */
	DisplayDocumentOnFeeder();

	/* 下段表示 */
	/* DisplayDocumentSet(CMN_GetDocumentScanSize()); T.Nose 1997/05/19 */
	DisplayDocumentSet();
}

/*************************************************************************
	module		:[待機状態中のＬＣＤ表示]
	function	:[
		1.上段：待機モード表示。予約原稿があれば予約中表示
		2.下段：カレンダー表示
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/13]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayIdle(void)
{
	UBYTE	is_document_set;
	
#if defined (KEISATSU)		/* 警察FAX DVT Modify by SMuratec K.W.Q 2005/11/17 */
	UWORD	queue_no;
 #if (1)		/* 警察FAX QAT_ID2 Added by SMuratec K.W.Q 2005/12/06 */
	UBYTE	is_redial_or_reserve;
	
	is_redial_or_reserve = FALSE;
 #endif
#endif

	is_document_set = FALSE;

#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1997/12/26 */
	/* ミラーキャリッジ輸送モードの時 */
	if (SYB_ScannerTransportMode == TRUE) {
		DisplayStringHigh(0, D2W_ScannerTransportReady);	/* "ﾐﾗｰｷｬﾘｯｼﾞ ﾕｿｳﾓｰﾄﾞ   " */
		if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
			ClearDisplayLow();
		}
		return;
	}
#endif

#if (PRO_NOT_AUTO_RX_DISP == ENABLE)	/* by K.Watanabe 1998/06/08 */
	if (!(OPR_DispInfo & OPR_DSP_ERROR)) {	/* エラー未表示の時 */
		if (CMN_CheckAutoCalledEnable() == FALSE) {	/* 自動受信不可能な時(ﾒﾓﾘ残量64K以下 or 代行受信管理ﾃｰﾌﾞﾙに空きなし) */
			DisplayStringHigh(0, D2W_MemoryFull);		/* "ﾒﾓﾘ ｶﾞ ｲｯﾊﾟｲﾃﾞｽ     " */
			DisplayStringLow(0, D2W_NotAutoReceive);	/* "ｼﾞﾄﾞｳｼﾞｭｼﾝ ﾃﾞｷﾏｾﾝ   " */
			return;
		}
	}
#endif

#if (PRO_COPY_FAX_MODE == ENABLE)
	/* コピーモードの時 */
	if (CHK_ReadyModeCopy()) {
 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/28  T.Nose */
		if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
			DisplayStringHigh(0, D2W_RemoteDiagMode);	/* "ｻｰﾋﾞｽﾓｰﾄﾞ           " */
			DisplayStringLow(0, D2W_Wait);				/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
			return;
		}
 #endif
		/* 現状、上段にのみエラー表示をするというのが無いので、下段のエラー表示チェックしかしません */
		if (OPR_DispInfo & OPR_DSP_ERROR_LOW) {	/* 下段にエラー表示をしている時 */
			DisplayCopyModeHigh();
		}
		else {									/* エラー未表示の時 */
			DisplayCopyMode();
			OPR_CopyParamCheck = OPR_NO_PARAM_CHK;	/* 用紙・倍率確認状態に、確認必要なしをセット by K.Watanabe 1997/12/16 */
		}
		return;
	}
#endif

#if defined (KEISATSU)		/* 警察FAX QAT_ID2 Modify by SMuratec K.W.Q 2005/12/06 */
	if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
		if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_IDLE) && CheckIsKanyuLine()) {
			DisplayRxMode();
			DisplayStringLow(0, D2W_IsseiShireiKido);
			return;
		}
	}

#if 0 /* 警察FAX DVT_ID77 Modified By SMuratec 李 2005/12/19 */
@@	queue_no = SYS_CurrentExecQueueNo;
@@
@@	/** 上段表示 */
@@	if (((SYB_ExecQueueKeisatsu[queue_no].Line == SYS_LINE_KANYU) && CheckIsKanyuLine()) ||
@@		((SYB_ExecQueueKeisatsu[queue_no].Line != SYS_LINE_KANYU) && !CheckIsKanyuLine())) {
@@		if (CMN_CheckFeederCommandEmpty() == FALSE) {	/** スキャナーコマンドがある時 */
@@			if (((SYB_ExecQueue[queue_no].Status == SYS_EXEC_WAITING) ||
@@				(SYB_ExecQueue[queue_no].Status == SYS_EXEC_FORWARD_WAITING)) &&
@@				(SYB_ExecQueue[queue_no].RedialTime > 0)) {
@@
@@				DisplayStringHigh(0, D2W_AutoRedial);
@@			}
@@			else {									/** スキャナーコマンドが予約中の時 */
@@				DisplayStringHigh(0, D2W_Reserving);
@@			}
@@			is_document_set = TRUE;
@@			is_redial_or_reserve = TRUE;
@@		}
@@		else {											/** スキャナーコマンドがない時 */
@@			if ((CMN_CheckDocumentOnFeeder() == TRUE)
@@				 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中ではなく、*/
@@				 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)	/* 蓄積中ではなく、*/
@@				 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {	/* FEED OUT SCANNER BUSYではない*/
@@				DisplayDocumentOnFeeder();
@@				is_document_set = TRUE;
@@			}
@@			else {
@@				if ((CheckReservedCommandExist() == TRUE)
@@				 || (CheckReservedBatchExist() == TRUE)
@@				 || (CheckReservedContPollingExist() == TRUE)) {
@@					if (((SYB_ExecQueue[queue_no].Status == SYS_EXEC_WAITING) ||
@@						(SYB_ExecQueue[queue_no].Status == SYS_EXEC_FORWARD_WAITING)) &&
@@						(SYB_ExecQueue[queue_no].RedialTime > 0)) {
@@
@@						DisplayStringHigh(0, D2W_AutoRedial);
@@					}
@@					else {									/** コマンドが予約中の時 */
@@						DisplayStringHigh(0, D2W_Reserving);
@@					}
@@					is_redial_or_reserve = TRUE;
@@				}
@@				else {
@@					DisplayRxMode();
@@				}
@@			}
@@		}
@@	}
@@	else {
@@		if ((CMN_CheckDocumentOnFeeder() == TRUE) &&
@@			!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) &&	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中ではなく、*/
@@		 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) && 	/* 蓄積中ではなく、*/
@@		 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {		/* FEED OUT SCANNER BUSYではない*/
@@			DisplayDocumentOnFeeder();
@@			is_document_set = TRUE;
@@		}
@@		else {
@@			DisplayRxMode();
@@		}
@@	}
#else /* DVT_ID77 */
	if (CMN_CheckFeederCommandEmpty() == FALSE) {
		if (CheckRedialQueueExist() == TRUE) {	/** スキャナーコマンドがリダイアル待ちの時 */
			DisplayStringHigh(0, D2W_AutoRedial);
		}
		else {									/** スキャナーコマンドが予約中の時 */
			DisplayStringHigh(0, D2W_Reserving);
		}
		if (CMN_CheckFeederCommandEmpty() == FALSE) {
			is_document_set = TRUE;
		}
		is_redial_or_reserve = TRUE;
	}
	else if ((CMN_CheckDocumentOnFeeder() == TRUE)
		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中ではなく、*/
	 	&& !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)	/* 蓄積中ではなく、*/
	 	&& !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {	/* FEED OUT SCANNER BUSYではない*/
	 	DisplayDocumentOnFeeder();
		is_document_set = TRUE;
	}
	else if ((CheckReservedCommandExist() == TRUE)
	 || (CheckReservedBatchExist() == TRUE)
	 || (CheckReservedContPollingExist() == TRUE)) {
		if (CheckRedialQueueExist() == TRUE) {	/** スキャナーコマンドがリダイアル待ちの時 */
			DisplayStringHigh(0, D2W_AutoRedial);
		}
		else {									/** スキャナーコマンドが予約中の時 */
			DisplayStringHigh(0, D2W_Reserving);
		}
		is_redial_or_reserve = TRUE;
	}
	else {
		DisplayRxMode();
	}
#endif /* DVT_ID77 */
	
	/** 下段表示 */
	if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
		if (SYS_CalledLineNumber) {
			if ((SYS_CalledLineNumber == SYS_STD_LINE_IN_CI) && !(CheckIsKanyuLine()) && (!HDST_RelaySetting())) {
				DisplayTelBell(0);
				return;
			}
			else if ((SYS_CalledLineNumber == SYS_EXT_LINE_IN_CI) && (CheckIsKanyuLine()) && HDST_RelaySetting()){
				DisplayTelBell(1);
				return;
			}
	 		else if ((SYS_CalledLineNumber == SYS_TWICE_LINE_IN_CI) && (CheckIsKanyuLine()) && HDST_RelaySetting()){
				DisplayTelBell(1);
				return;
			}
		}
		
		if (is_document_set) {
			DisplayDocumentSet();
		}
		else if (is_redial_or_reserve) {
			CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');	
			DisplayKeisatsuSettings(FunctionDisplayBufferLow);
			DisplayStringLow(0 , FunctionDisplayBufferLow);
		}
		else {
			DisplayCalender();
		}
	}
	
	return;
#endif		/* End of (defined (KEISATSU)) */


#if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */

#if defined (KEISATSU)		/* 警察FAX DVT Modify by SMuratec K.W.Q 2005/11/19 */
	if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
		if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_IDLE) && CheckIsKanyuLine()) {
 			ClearDisplayHigh();
			ClearDisplayLow();
			DisplayRxMode();
			DisplayStringLow(0, D2W_IsseiShireiKido);
			return;
		}
	}
	
	queue_no = SYS_CurrentExecQueueNo;


	if (((SYB_ExecQueueKeisatsu[queue_no].Line == SYS_LINE_KANYU) && CheckIsKanyuLine()) ||
		((SYB_ExecQueueKeisatsu[queue_no].Line != SYS_LINE_KANYU) && !CheckIsKanyuLine())) {
		if (CMN_CheckFeederCommandEmpty() == FALSE) {	/** スキャナーコマンドがある時 */
			
			ClearDisplayHigh();
			if (((SYB_ExecQueue[queue_no].Status == SYS_EXEC_WAITING) ||
				(SYB_ExecQueue[queue_no].Status == SYS_EXEC_FORWARD_WAITING)) &&
				(SYB_ExecQueue[queue_no].RedialTime > 0)) {

				DisplayStringHigh(0, D2W_AutoRedial);
			}
			else {									/** スキャナーコマンドが予約中の時 */
				DisplayStringHigh(0, D2W_Reserving);
			}

			if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
				ClearDisplayLow();
				DisplayDocumentSet();
			}
		}
		else {											/** スキャナーコマンドがない時 */
			if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
				ClearDisplayLow();
				if ((CMN_CheckDocumentOnFeeder() == TRUE) &&
					!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) &&	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中ではなく、*/
				 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) && 	/* 蓄積中ではなく、*/
				 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {		/* FEED OUT SCANNER BUSYではない*/
					DisplayDocumentSet();
				}
				else {
					DisplayCalender();
				}
			}

			ClearDisplayHigh();
			if ((CheckReservedCommandExist() == TRUE)
			 || (CheckReservedBatchExist() == TRUE)
			 || (CheckReservedContPollingExist() == TRUE)) {
				if (((SYB_ExecQueue[queue_no].Status == SYS_EXEC_WAITING) ||
					(SYB_ExecQueue[queue_no].Status == SYS_EXEC_FORWARD_WAITING)) &&
					(SYB_ExecQueue[queue_no].RedialTime > 0)) {

					DisplayStringHigh(0, D2W_AutoRedial);

				}
				else {									/** コマンドが予約中の時 */
					DisplayStringHigh(0, D2W_Reserving);
				}

					ClearDisplayLow();
				if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
					if ((CMN_CheckDocumentOnFeeder() == TRUE) &&
						!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) &&	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中ではなく、*/
					 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) && 	/* 蓄積中ではなく、*/
					 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {		/* FEED OUT SCANNER BUSYではない*/
						DisplayDocumentSet();
					}
					else {
						CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');	
						DisplayKeisatsuSettings(FunctionDisplayBufferLow);
						DisplayStringLow(0 , FunctionDisplayBufferLow);
					}
				}
			}
			else {
				DisplayRxMode();
			}
		}
	}
	else {
		if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
			ClearDisplayLow();
			if ((CMN_CheckDocumentOnFeeder() == TRUE) &&
				!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) &&	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中ではなく、*/
			 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) && 	/* 蓄積中ではなく、*/
			 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {		/* FEED OUT SCANNER BUSYではない*/
				DisplayDocumentSet();
			}
			else {
				DisplayCalender();
			}
		}

		ClearDisplayHigh();
		if ((CheckReservedCommandExist() == TRUE)
		 || (CheckReservedBatchExist() == TRUE)
		 || (CheckReservedContPollingExist() == TRUE)) {
			DisplayStringHigh(0, D2W_Reserving);
			
			if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
				ClearDisplayLow();
				if ((CMN_CheckDocumentOnFeeder() == TRUE) &&
					!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) &&	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中ではなく、*/
				 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) && 	/* 蓄積中ではなく、*/
				 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {		/* FEED OUT SCANNER BUSYではない*/
					DisplayDocumentSet();
				}
				else {
					CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');	
					DisplayKeisatsuSettings(FunctionDisplayBufferLow);
					DisplayStringLow(0 , FunctionDisplayBufferLow);
				}
			}
		}
		else {
			DisplayRxMode();
			if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
				if ((CMN_CheckDocumentOnFeeder() == TRUE) &&
					!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) &&	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中ではなく、*/
				 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) && 	/* 蓄積中ではなく、*/
				 	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {		/* FEED OUT SCANNER BUSYではない*/
		
					is_document_set = TRUE;
				 	if (!SYS_CalledLineNumber) {
						DisplayDocumentSet();
					}
				}
				else {
				 	if (!SYS_CalledLineNumber) {
						DisplayCalender();
					}
				}
			}
		}

	}
#endif /* keisatsu */
#endif

#if !defined(KEISATSU)
	/* ファクスモードの時 */

	/* 原稿セット中の表示をここに追加 */
	/* 原稿がセットされていてかつ、それがスキャナ送信コマンドの場合、上段は予約中の表示になる */

	/** 上段表示 */
	if (CMN_CheckFeederCommandEmpty() == FALSE) {	/** スキャナーコマンドがある時 */
		if (CheckRedialQueueExist() == TRUE) {	/** スキャナーコマンドがリダイアル待ちの時 */
			DisplayStringHigh(0, D2W_AutoRedial);
		}
		else {									/** スキャナーコマンドが予約中の時 */
			DisplayStringHigh(0, D2W_Reserving);
		}

#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* (紙の初期繰り込みの時に表示するはF200と同じくなります) Modify by SMuratec L.Z.W 2003/10/21 */
		is_document_set = TRUE;
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	}
	else {											/** スキャナーコマンドがない時 */
#if (PRO_DISPLAY_STOP_KEY_OPR == ENABLE) /* By H.Fujimura 1999/01/18 */
		if ((CMN_CheckDocumentOnFeeder() == TRUE)
		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中ではなく、*/
		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)	/* 蓄積中ではなく、*/
		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {	/* FEED OUT SCANNER BUSYではない*/
#else
		if (CMN_CheckDocumentOnFeeder() == TRUE) {	/** ＡＤＦに原稿がセットされている時 */
#endif
			DisplayDocumentOnFeeder();
			is_document_set = TRUE;
		}
		else {										/** ＡＤＦに原稿がセットされていない時 */
			if ((CheckReservedCommandExist() == TRUE)
			 || (CheckReservedBatchExist() == TRUE)
			 || (CheckReservedContPollingExist() == TRUE)) {
				if (CheckRedialQueueExist() == TRUE) {	/** コマンドがリダイアル待ちの時 */
					DisplayStringHigh(0, D2W_AutoRedial);

				}
				else {									/** コマンドが予約中の時 */
					DisplayStringHigh(0, D2W_Reserving);
				}
			}
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto */
			else if (CheckReservedMailComExist() == TRUE) {
				if (CheckRedialMailComExist() == TRUE) {
					DisplayStringHigh(0, D2W_AutoRedial);
				}
				else {
					DisplayStringHigh(0, D2W_Reserving);
				}
			}
#endif	/* by Y.Tanimoto PRO_DIALUP_INTERNET_FAX == ENABLE */
			else {
				DisplayRxMode();
			}
		}
	}

	/** 下段表示 */
	if (!(OPR_DispInfo & OPR_DSP_ERROR_LOW)) {	/* 下段エラー未表示の時 */
		if (is_document_set) {
			/* DisplayDocumentSet(CMN_GetDocumentScanSize()); T.Nose 1997/05/19 */
			DisplayDocumentSet();
		}
		else {
			DisplayCalender();
		}

#if (PRO_MULTI_LINE == ENABLE)
		/*----------------------*/
		/**	 マルチ表示 		*/
		/*----------------------*/
		/* ユニットｓｗのｉ３の１ビット目を有効にすると通信中でなくても右上に回線表示 */
		if ((CHK_UNI_MultiDisplayLineNumber() != 0) && (OPT_CountModems() > 1)) {
			DisplayChar(17, '(');
			DisplayChar(18, ChangeNumberToASC_Code((UBYTE)OPR_MultiLineCount));
			DisplayChar(19, ')');
			/* タイマー表示のビットを０にしたとき、ラインカウントに１以外の数が入ってる可能性があるため */
			if (OPR_MultiDisplayFlag == 0) {
				DisplayChar(18, '1');
			}
		}
#endif
	}
#endif
	
#if 0	/* 警察FAX DVT Deleted by SMuratec 夏 2005/12/20 */
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/01 */
	/** 電話呼出中の表示 */
/*************************
	呼出回線値
	0ｘ01　標準回線
	0ｘ02　拡張回線
#define SYS_STD_LINE_IN_CI	0x01
#define SYS_EXT_LINE_IN_CI	0x02
#define SYS_TWICE_LINE_IN_CI	(SYS_STD_LINE_IN_CI | SYS_EXT_LINE_IN_CI)
*************************/
/* 警察FAX DVT_ID23 Modify by SMuratec K.W.Q 2005/11/07 */
 #if (1)
	if (SYS_CalledLineNumber) {
		if ((SYS_CalledLineNumber == SYS_STD_LINE_IN_CI) && !(CheckIsKanyuLine()) && (!HDST_RelaySetting())) {
			DisplayTelBell(0);
		}
		else if ((SYS_CalledLineNumber == SYS_EXT_LINE_IN_CI) && (CheckIsKanyuLine()) && HDST_RelaySetting()){
			DisplayTelBell(1);
		}
   #if (0)		/* 警察FAX DVT_ID Modify by SMuratec K.W.Q 2005/12/02 */
 		else if ((SYS_CalledLineNumber == SYS_TWICE_LINE_IN_CI) && (CheckIsKanyuLine())){
   #else
 		else if ((SYS_CalledLineNumber == SYS_TWICE_LINE_IN_CI) && (CheckIsKanyuLine()) && HDST_RelaySetting()){
   #endif
			DisplayTelBell(1);
		}
	}
 #else
	if (SYS_CalledLineNumber) {
		if ((SYS_CalledLineNumber == SYS_STD_LINE_IN_CI) && !(CheckIsKanyuLine()) ) {
			DisplayTelBell(0);
		}
		else if ((SYS_CalledLineNumber == SYS_EXT_LINE_IN_CI) && (CheckIsKanyuLine())){
			DisplayTelBell(1);
		}
		else if ((SYS_CalledLineNumber == SYS_TWICE_LINE_IN_CI) && (CheckIsKanyuLine())){
			DisplayTelBell(1);
		}
		return;
	}
 #endif
#endif		/* End of (defined (KEISATSU)) */
#endif		/* if 0 */
}

/*************************************************************************
	module		:[受信モードの表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/04]
	author		:[江口]
*************************************************************************/
void DisplayRxMode(void)
{
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/27 */
 #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
	ClearDisplayHigh();
 #endif
	/* 表示用バッファの初期化 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');	

	DisplayKeisatsuSettings(FunctionDisplayBufferHigh);
	DisplayStringHigh(0 , FunctionDisplayBufferHigh);
#else

	UBYTE	*wording;
	switch (CMN_PresentReceiveMode()) {
	case SYS_TEL_READY:
		wording = D2W_TelReady;
		break;
	case SYS_FAX_READY:
		wording = D2W_FaxReady;
		break;
	case SYS_FAX_TEL_READY:
		wording = D2W_FaxTelReady;
		break;
	case SYS_TEL_FAX_READY:
		wording = D2W_TelFaxReady;
		break;
	case SYS_ANS_FAX_READY:
		wording = D2W_AnsFaxReady;
		break;
#if (PRO_DIALIN == ENABLE) /* By H.Fujimura 1999/01/29 */
	case SYS_DIAL_IN_READY:
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/18 */
	case SYS_MODEM_DIALIN_READY:
 #endif
		wording = D2W_DialInReady;
		break;
#endif
	default:
		wording = NULL;
		break;
	}

	DisplayStringHigh(0 , wording);
#endif		/* End of (defined (KEISATSU)) */	
}


/*************************************************************************
	module		:[コピー中の表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/13]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayCopy(UBYTE is_dsp_low_enable)
{
#if (PRO_COPY_FAX_MODE == ENABLE)
	struct	SYS_MultiCopyData_t *copy_ptr;	/* コピー用ファイルのポインター */

	CMN_StringCopy(DisplayBufferHigh, D2W_SF_Copy);	/* "ｺﾋﾟｰ                " */

	/* コピーファイルのポインターのセット */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_MANUAL_COPY) {	/* 手差しコピー中の時 */
		copy_ptr = &SYB_ManualCopyFile;							/* 手差しコピー用ファイルのポインターのセット */
	}
	else {																	/* カセットの記録紙にコピーする時 */
		copy_ptr = &SYB_MultiCopyFile[SYB_MultiCopyReadPoint];	/* コピー用ファイルのポインターのセット */
	}

	/* 蓄積完了後、排出中に原稿カバーをあけるとコピー管理ファイルが消去されるため、
	** "ｺﾋﾟｰ        00/00 00" 表示防止のために、ステータスをチェックします
	*/
	if (copy_ptr->Status != SYS_MCOPY_EMPTY) {
		/* プリント中枚数／蓄積合計枚数 */
		if (copy_ptr->ScanType == SYS_ADF_SCAN) {	/* ＡＤＦからの読み取りの時 */
			if (copy_ptr->StorePage < 100) {
				/* "            99/99   " */
				/* 何枚目の原稿をプリント中か */
				CMN_UnsignedIntToASC(&DisplayBufferHigh[12], copy_ptr->PrintPage, 2, '0');
				DisplayBufferHigh[14] = '/';
				/* 蓄積合計枚数 */
				CMN_UnsignedIntToASC(&DisplayBufferHigh[15], copy_ptr->StorePage, 2, '0');
			}
			else {
				/* "          999/999   " */
				/* 何枚目の原稿をプリント中か */
				CMN_UnsignedIntToASC(&DisplayBufferHigh[10], copy_ptr->PrintPage, 3, '0');
				DisplayBufferHigh[13] = '/';
				/* 蓄積合計枚数 */
				CMN_UnsignedIntToASC(&DisplayBufferHigh[14], copy_ptr->StorePage, 3, '0');
			}
		}

		/* プリント部数 */
		CMN_UnsignedIntToASC(&DisplayBufferHigh[18], copy_ptr->ExecutiveNumber, 2, '0');
	}

	/*------------*/
	/* 上段の表示 */
	/*------------*/
	DisplayStringHigh(0, DisplayBufferHigh);	/* "ｺﾋﾟｰ        99/99 99" */
												/*                 ↓     */
										/* プリント中枚数／蓄積合計枚数　プリント部数 */
#else
	DisplayStringHigh(0, D2W_SF_Copy);			/* "ｺﾋﾟｰ                " */
#endif	/* (PRO_COPY_FAX_MODE == ENABLE) */

	/*------------*/
	/* 下段の表示 */
	/*------------*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/10/16 */
 #if (PRO_DISPLAY_STOP_KEY_OPR == ENABLE) /* By H.Fujimura 1999/01/18 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)				/* ｽｷｬﾅｰ･ｺﾋﾟｰ中で、*/
	 && !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_SCANNER_COPY)) {	/* ｽｷｬﾅｰ･ｺﾋﾟｰ停止要求ではない*/
 #else
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) { /** スキャナー・コピー中なら */
 #endif
		CMN_MemorySetNULL(&DisplayBufferHigh[16], 4, ' ');
		DisplayDocumentSet();	/* スキャナ送信実行中で濃度、画質を設定するできます。 */
	}
	else{
		if (is_dsp_low_enable) {	/* 下段表示可能な時 */
	#if (PRO_PRINT_TYPE == LED)
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_WARMUP) {	/* プリンターウォームアップ中の時 */
				DisplayStringLow(0, D2W_Wait);		/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
			}
			else {
				DisplayStringLow(0, D2W_Printing);	/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
			}
	#else
			DisplayStringLow(0, D2W_Printing);		/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
	#endif
		}
	}
#else
	if (is_dsp_low_enable) {	/* 下段表示可能な時 */
#if (PRO_PRINT_TYPE == LED)
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_WARMUP) {	/* プリンターウォームアップ中の時 */
			DisplayStringLow(0, D2W_Wait);		/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
		}
		else {
			DisplayStringLow(0, D2W_Printing);	/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
		}
#else
		DisplayStringLow(0, D2W_Printing);		/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
#endif
	}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[ジャムリカバー中の表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/07/15]
	author		:[江口]
*************************************************************************/
void DisplayJamRecover(void)
{
	ClearDisplayHigh();
	DisplayStringLow(0, D2W_Wait);	/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
}

/*************************************************************************
	module		:[ウォームアップ中の表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/07/15]
	author		:[江口]
*************************************************************************/
void DisplayPrinterWarmUp(void)
{
#if (0)	/* by K.Watanabe 1998/04/30 */
//#if (PRO_KEYPANEL == PANEL_POPLAR_B)
//	/* 電源ONした時に、何も押していないのにNackが鳴る現象のデバッグ用に追加 by K.Watanabe 1998/04/28 */
//	UBYTE	key_type;
//	UBYTE	key_code;
//
//	/* 電源ＯＮのウォームアップの時 */
//	if ((DBG_Sw) && (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_POWER_ON)) {
//		key_type = GetInputKeyType();
//		key_code = GetInputKeyCode();
//
//		if (key_type == OPR_NO_KEY) {	/* キー未入力の時 */
//			return;
//		}
//
//		CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');
//
//		switch (key_type) {
//		case	SINGLE:
//		case	HOOK:
//		case	FUNCTION:
//		case	LEFT_ARROW:
//		case	ENTER:
//		case	REVIEW:
//		case	CLEAR:
//		case	DIALMARK:
//		case	BROADCAST:
//		case	SPECIAL:
//		case	GROUP:
//		case	SPEED:
//		case	STOP:
//		case	START:
//		case	COPY_FAX:
//		case	REDIAL:
//		case	REDUCTION:
//		case	MAGNIFICATION:
//		case	BOOK_DOC_SIZE:
//		case	COPY_RESET:
//			DisplayStringLow(0, D2W_SF_Receive + (OPR_WORDING_LEN * (key_code - 1)));
//			return;
//		case	SHARP:
//		case	AST:
//		case	NUMBER:
//			DisplayBufferLow[0] = key_code;
//			break;
//		case	ONETOUCH:
//			SetOnetouchCode(DisplayBufferLow, key_code, OPR_SET_ONETOUCH_CODE);
//			break;
//		case	PROGRAM:
//			DisplayBufferLow[0] = OPR_PROGRAM_MARK_LEFT;
//			CMN_UnsignedIntToASC(&DisplayBufferLow[1], (UBYTE)(key_code - ONETOUCH_73_KEY + OPR_PRG_NUMBER_MIN), 2, '0');
//			DisplayBufferLow[3] = OPR_PROGRAM_MARK_RIGHT;
//			break;
//		default:
//			CMN_StringCopy(DisplayBufferLow, (UBYTE *)("KeyType:    Key:    "));
//			CMN_HexToASC(&DisplayBufferLow[8], (UDWORD)key_type, 2);
//			CMN_HexToASC(&DisplayBufferLow[16], (UDWORD)key_code, 2);
//			break;
//		}
//
//		ClearDisplayLow();
//		DisplayStringLow(0, DisplayBufferLow);
//	}
//	/* プリント開始のウォームアップの時 */
//	else {
//		ClearDisplayHigh();
//		DisplayStringLow(0, D2W_Wait);	/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
//	}
//#else
//	ClearDisplayHigh();
//	DisplayStringLow(0, D2W_Wait);	/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
//#endif
#endif

	ClearDisplayHigh();
	DisplayStringLow(0, D2W_Wait);	/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
}

/*************************************************************************
	module		:[イメージプリント中表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[SYS_DocumentPrintItem]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayImagePrint(void)
{
	switch (SYS_DocumentPrintClass) {
	case SYS_PRINT_CLASS_INITIAL:
#if (PRO_PRINT_TYPE == THERMAL) /* By H.Fujimura 1999/01/18 */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) && (PRO_DISPLAY_PRN_INITIALIZE == ENABLE) /* Modify by SMuratec 李 2004/07/06 */
		DisplayPrinterWarmUp();
#else 
		DisplayIdle();	/* 待機状態中のＬＣＤ表示 */
#endif
#endif
		return;

	case SYS_PRINT_CLASS_LIST_MEMORY:		/* 原稿付きチェックメッセージ */
		DisplayStringHigh(0, D2W_CheckMessage);	/* "ﾁｪｯｸ ﾒｯｾｰｼﾞ         " */
		break;

	case SYS_PRINT_CLASS_LIST_MONITOR:		/* モニターレポート（原稿付き） */
		DisplayStringHigh(0, D2W_TCR);			/* "ｿｳｼﾝｼｮｳ             " */
		break;

	case SYS_PRINT_CLASS_LIST_BA_MEMORY:	/* 一括送信チェックメッセージ(原稿付き） */
		DisplayStringHigh(0, D2W_CheckMessage);	/* "ﾁｪｯｸ ﾒｯｾｰｼﾞ         " */
		break;

	case SYS_PRINT_CLASS_LIST_BA_MONITOR:	/* 一括送信モニターレポート(原稿付き) */
		DisplayStringHigh(0, D2W_TCR);			/* "ｿｳｼﾝｼｮｳ             " */
		break;

#if (PRO_CIPHER == ENABLE)	/* Add By T.Fukumoto 98/01/28 */
	case SYS_PRINT_CLASS_LIST_CIPHER:		/* 暗号化受信原稿通知(原稿付き) */
		ClearDisplayHigh();
		break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	case SYS_PRINT_CLASS_RETURNED_MAIL:
		DisplayStringHigh(0 , D2W_PrintReceiveMail);
		break;
#endif

	default:
		switch(SYS_DocumentPrintItem) {	/** 印字原稿の種類を調べる */
		case SYS_MEM_REMOTE_TX_FILE:	/* リモート送信原稿 */
		case SYS_MEM_FIP_FILE:			/* ＦＩＰ原稿 */
			ClearDisplayHigh();
			break;
		case SYS_MEM_RX_FILE:			/* メモリ受信原稿 */
			DisplayStringHigh(0, D2W_MemoryRxDocument);/*未定*/
			break;
		case SYS_MEM_TX_FILE:			/* 送信原稿 */
			DisplayStringHigh(0, D2W_CommandDocument);		/* "ｿｳｼﾝ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ    " */
			break;
		case SYS_MEM_BATCH_TX_FILE1:	/* バッチ送信原稿 */
		case SYS_MEM_BATCH_TX_FILE2:	/* バッチ送信原稿 */
		case SYS_MEM_BATCH_TX_FILE3:	/* バッチ送信原稿 */
		case SYS_MEM_BATCH_TX_FILE4:	/* バッチ送信原稿 */
		case SYS_MEM_BATCH_TX_FILE5:	/* バッチ送信原稿 */
			DisplayStringHigh(0, D2W_BatchTxDocument);		/* "ｲｯｶﾂｿｳｼﾝ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ" */
			break;
		case SYS_MEM_POLLING_FILE:		/* ポーリング原稿 */
		case SYS_MEM_DB_POLLING_FILE:	/* 検索ポーリング原稿 */
			DisplayStringHigh(0, D2W_PollingDocument);		/* "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ       " */
			break;
		case SYS_MEM_SECURE_RX_FILE:	/* 親展受信原稿 */
			DisplayStringHigh(0, D2W_SecureMailDocument);	/* "ｼﾝﾃﾝｼﾞｭｼﾝ ﾌﾟﾘﾝﾄ     " */
			break;
#if (PRO_CLASS1 == ENABLE) /* 1996/09/13 Eguchi */
		case SYS_MEM_CL1_RX_FILE:		/* ローカルプリント原稿 */
			DisplayStringHigh(0, D2W_PC_FAX_Print);			/* "PC-FAX ﾌﾟﾘﾝﾄ        " */
			break;
#endif
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 1996/09/30 by K.Watanabe */
		case SYS_MEM_PC_RX_FILE:		/* ＰＣプリントファイル */
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/31 Y.Matsukuma */
			MinoltaTestPatternDisplay();
 #else
			DisplayStringHigh(0, D2W_PC_Print);				/* "PC                  " */
 #endif
			break;
#endif
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/01/21 */
		case SYS_MEM_DECIPHER_FILE:		/* 受信暗号化原稿 */
			DisplayStringHigh(0, D2W_DecipherDocument);		/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ｹﾞﾝｺｳ " */
			break;
		case SYS_MEM_TX_DECIPHER_FILE:	/* 暗号化送信原稿 */
			DisplayStringHigh(0, D2W_CommandDocument);		/* "ｿｳｼﾝ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ    " */
			break;
#endif
#if (PRO_F_CODE == ENABLE)	/* Add By T.Fukumoto 98/01/29 */
		case SYS_MEM_SUB_SECURE_FILE:	/* Ｆコード蓄積原稿(親展受信原稿) */
		case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード蓄積原稿(掲示板原稿)   */
			CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(DisplayBufferHigh, &D2W_PrintFcodeStoreDocMode[3]);	/* "   ﾁｸｾｷ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ " */
			DisplayStringHigh(0, DisplayBufferHigh);							/* "ﾁｸｾｷ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ    " */
			break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		case SYS_MEM_MAIL_RX_FILE:
			DisplayStringHigh(0 , D2W_PrintReceiveMail);
			break;
		case SYS_MEM_MAIL_TX_FILE:
			DisplayStringHigh(0 , D2W_PrintStoredMail);
			break;
#endif
		default:
			break;
		}
		break;
	}

#if (PRO_PRINT_TYPE == LED)
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_WARMUP) {	/* プリンターウォームアップ中の時 */
		DisplayStringLow(0, D2W_Wait);		/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
	}
	else {
		DisplayStringLow(0, D2W_Printing);	/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
	}
#else
#if (PRO_KEYPANEL == PANEL_STOCKHM2) && (PRO_DISPLAY_PRN_INITIALIZE == ENABLE) /* Modify by SMuratec 李 2004/07/06 */
	if ( SYS_DocumentPrintClass != SYS_PRINT_CLASS_INITIAL) {
		DisplayStringLow(0, D2W_Printing);		/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
	}
#else /* (PRO_PAPER_TYPE != CUT_PAPER) || !defined(STOCKHM2) */
	DisplayStringLow(0, D2W_Printing);		/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
#endif
}

/*************************************************************************
	module		:[リストプリント中表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[SYS_DocumentPrintItem]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/13]
	author		:[江口]
*************************************************************************/
void DisplayListPrint(void)
{
	/*------------------------------*/
	/* 上段表示						*/
	/* リストの種類を表示			*/
	/*------------------------------*/
	switch (SYS_DocumentPrintItem) {
	case LST_ONETOUCHDIAL_LIST:			/* ワンタッチダイヤルリスト							*/
		DisplayStringHigh(0, D2W_PrintOneTouch);	/* "ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ﾘｽﾄ      " */
		break;
	case LST_SPEEDDIAL_LIST:			/* 短縮ダイヤルリスト								*/
		DisplayStringHigh(0, D2W_PrintSpeedDial);	/* "ﾀﾝｼｭｸﾀﾞｲﾔﾙ ﾘｽﾄ      " */
		break;
	case LST_PROGRAM_LIST:				/* プログラムワンタッチリスト						*/
		DisplayStringHigh(0, D2W_PrintProgramOneTouch);	/* "ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ ﾘｽﾄ    " */
		break;
	case LST_MAILBOX_LIST:				/* 親展者リスト										*/
		DisplayStringHigh(0, D2W_PrintSecureMailList);	/* "ｼﾝﾃﾝｼｬ ﾘｽﾄ          " */
		break;
	case LST_RESERVECMD_LIST:			/* 通信予約リスト									*/
		DisplayStringHigh(0, D2W_PrintCommands);	/* "ﾂｳｼﾝﾖﾔｸ ﾘｽﾄ         " */
		break;
	case LST_JOURNAL_LIST:				/* 通信管理レポート									*/
	case LST_TXJOURNAL_LIST:			/* 通信管理レポート（送信）							*/
	case LST_RXJOURNAL_LIST:			/* 通信管理レポート（受信）							*/
#if defined(STOCKHM2)	/* Added by SMuratec C.P 2004/06/07 */
		switch (SYS_JournalPrintType) {
		case TXTYPE:
			DisplayStringHigh(0, D2W_JournalTx);
			break;
		case RXTYPE:
			DisplayStringHigh(0, D2W_JournalRx);
			break;
		case BOTHTYPE:
			DisplayStringHigh(0, D2W_JournalTxRx);
			break;
		default:
			break;
		}
#elif (PRO_JOURNAL_VER_UP == ENABLE)	/* by K.Watanabe 2004/10/28 */
		switch (SYS_JournalPrintType) {
		case TXTYPE:
			DisplayStringHigh(0, D2W_PrintJournalTx);	/* "ｿｳｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ       " */
			break;
		case RXTYPE:
			DisplayStringHigh(0, D2W_PrintJournalRx);	/* "ｼﾞｭｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ      " */
			break;
		case BOTHTYPE:
			DisplayStringHigh(0, D2W_PrintJournalTxRx);	/* "ｿｳｼﾞｭｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ    " */
			break;
		default:
			DisplayStringHigh(0, D2W_PrintJournal);		/* "ﾂｳｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ       " */
			break;
		}
#else
		DisplayStringHigh(0, D2W_PrintJournal);	/* "ﾂｳｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ       " */
#endif
		break;
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
	case LST_AUTO_ALL_JOURNAL:			/* 通信管理記録自動プリント */
		DisplayStringHigh(0, D2W_PrintAllJournal);	/* "ｽﾍﾞﾃﾉﾂｳｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ  " */
		break;
	case LST_DAILY_REPORT:				/* 通信管理記録日報プリント */
		DisplayStringHigh(0, D2W_PrintDailyReport);	/* "ﾂｳｼﾝﾆｯﾎﾟｳ ﾌﾟﾘﾝﾄ     " */
		break;
#endif
	case LST_GROUP_LIST:				/* グループリスト									*/
		DisplayStringHigh(0, D2W_GroupList);	/* "ｸﾞﾙｰﾌﾟ ﾘｽﾄ          " */
		break;
	case LST_PARAMETER_LIST:			/* 機器設定リスト									*/
		DisplayStringHigh(0, D2W_SetPrintSettings);	/* "ｷｷｾｯﾃｲ ﾘｽﾄ          " */
		break;
	case LST_BLOCK_JUNK_LIST:			/* ジャンクメール防止ダイヤルリスト					*/
		DisplayStringHigh(0, D2W_PrintBlockJunkMailDialList);	/* "ﾀﾞｲﾚｸﾄﾒｰﾙ ﾀﾞｲﾔﾙ ﾘｽﾄ " */
		break;
	case LST_COVERPAGE_LIST:			/* カバーページプリント								*/
		DisplayStringHigh(0, D2W_MessageList);	/* "ﾒｯｾｰｼﾞ ﾘｽﾄ          " */
		break;
	case LST_BATCHTXBOX_LIST:			/* 一括送信ＢＯＸリスト								*/
		DisplayStringHigh(0, D2W_PrintBatchBoxMode);	/* "ｲｯｶﾂ ｿｳｼﾝ ﾎﾞｯｸｽ ﾘｽﾄ " */
		break;
	case LST_BATCHTXDOC_LIST:			/* 一括送信原稿リスト								*/
		DisplayStringHigh(0, D2W_PrintBatchDocListMode);	/* "ｲｯｶﾂ ｿｳｼﾝ ｹﾞﾝｺｳ ﾘｽﾄ " */
		break;
#if (PRO_F_CODE == ENABLE)
	case LST_F_CODE_BOX_LIST:			/* Ｆコードボックスリスト							*/
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(DisplayBufferHigh, &D2W_PrintFcodeBoxListMode[3]);	/* "   ﾎﾞｯｸｽ ﾘｽﾄ        " */
		DisplayStringHigh(0, DisplayBufferHigh);							/* "ﾎﾞｯｸｽ ﾘｽﾄ           " */
		break;
	case LST_F_CODE_DOC_LIST:			/* Ｆコード蓄積原稿リスト							*/
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(DisplayBufferHigh, &D2W_PrintFcodeStoreDocListMode[3]);	/* "   ﾁｸｾｷ ｹﾞﾝｺｳ ﾘｽﾄ   " */
		DisplayStringHigh(0, DisplayBufferHigh);								/* "ﾁｸｾｷ ｹﾞﾝｺｳ ﾘｽﾄ      " */
		break;
#endif
#if (PRO_CIPHER == ENABLE)
	case LST_SCRAMBLE_KEY:				/* 暗号化キーリスト									*/
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(DisplayBufferHigh, &D2W_PrintCipherKeyMode[3]);	/* "   ｷｰﾜｰﾄﾞ ﾌﾟﾘﾝﾄ     " */
		DisplayStringHigh(0, DisplayBufferHigh);						/* "ｷｰﾜｰﾄﾞ ﾌﾟﾘﾝﾄ        " */
		break;
	case LST_SCRAMBLE_KEY_LIST:			/* 暗号化キーブックリスト							*/
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(DisplayBufferHigh, &D2W_PrintCipherKeyBookListMode[3]);	/* "   ｷｰﾊﾞﾝｸ ﾘｽﾄ       " */
		DisplayStringHigh(0, DisplayBufferHigh);								/* "ｷｰﾊﾞﾝｸ ﾘｽﾄ          " */
		break;
#endif
	case LST_T30MONITOR:				/* Ｔ３０モニタ										*/
		DisplayStringHigh(0, D2W_SF_T30MonitorPrint);	/* "T30ﾓﾆﾀ              " */
		break;
	case LST_FUNCTION_LIST:				/* 機能リスト										*/
		DisplayStringHigh(0, D2W_SF_ProgramListPrint);	/* "ｷﾉｳ ﾘｽﾄ             " */
		break;
	case LST_PATTERN_PRINT:				/* パターンプリント									*/
		DisplayStringHigh(0, D2W_SF_TestPatternPrint);	/* "ﾃｽﾄ ﾊﾟﾀｰﾝ ﾌﾟﾘﾝﾄ     " */
		break;
	case LST_MEM_SW:					/* メモリスイッチ									*/
		DisplayStringHigh(0, D2W_SF_MemorySwitchMode);	/* "ﾒﾓﾘ ｽｲｯﾁ            " */
		break;
	case LST_FACT_MENU:					/* 工場ファンクションリスト							*/
		DisplayStringHigh(0, D2W_SF_FactoryFunctionList);	/* "ｺｳｼﾞｮｳ ﾌｧﾝｸｼｮﾝ ﾘｽﾄ  " */
		break;
	case LST_SERVICE_LIST:				/* サービスレポート									*/
		DisplayStringHigh(0, D2W_SF_ServicePrint);	/* "ｻｰﾋﾞｽﾚﾎﾟｰﾄ          " */
		break;
	case LST_MEMORY_DUMP:				/* メモリダンプリスト								*/
		DisplayStringHigh(0, D2W_SF_MemoryDump);	/* "ﾒﾓﾘﾀﾞﾝﾌﾟ            " */
		break;
	case LST_CL1_ONLINE_MONITOR:		/* クラス１オンラインモニター						*/
		DisplayStringHigh(0, D2W_SF_OnLineMonitor);	/* "ｵﾝﾗｲﾝ ﾓﾆﾀ           " */
		break;
	case LST_TXCONF_REPORT:				/* 送信証											*/
	case LST_MONITOR_REPORT:			/* モニターレポート（ＯＮの原稿無し時）				*/
	case LST_MANUAL_TXCONF_REPORT:		/* 手動送信送信証 By H.Fujimura 1999/02/19			*/
		DisplayStringHigh(0, D2W_TCR);	/* "ｿｳｼﾝｼｮｳ             " */
		break;
	case LST_DOC_CHECKMSG:				/* チェックメッセージＡ（原稿添付）					*/
	case LST_COMMERR_CHECKMSG:			/* チェックメッセージＢ（交信エラー）				*/
	case LST_MRYOVER_CHECKMSG:			/* チェックメッセージＣ（メモリオーバー）			*/
	case LST_MRYINIT_CHECKMSG:			/* チェックメッセージＤ（メモリイニシャル）			*/
	case LST_MNLERR_CHECKMSG:			/* チェックメッセージＥ（手動送信エラー）			*/
	case LST_RXMRYOVER_CHECKMSG:		/* チェックメッセージＦ（受信メモリオーバー）		*/
	case LST_CATCHPHONE_CHKMSG:			/* チェックメッセージＧ（キャッチホン）				*/
	case LST_LOSTPAGE_CHKMSG:			/* チェックメッセージＩ（受信ページ紛失）			*/
	case LST_SEC_RX_MEMOVER_CHKMSG:		/* セキュリティ受信モード中の受信メモリーオーバー	*/
	case LST_POWEROFF_NOTICE:			/* 停電検出通知										*/
	case LST_DELRESERVECMD_NOTICE:		/* 通信予約消去通知									*/
	case LST_DELMEMORYRCV_NOTICE:		/* 代行受信消去通知									*/
	case LST_DELSECURE_NOTICE:			/* 親展受信消去通知									*/
	case LST_DELPOLLING_NOTICE:			/* ポーリング原稿消去通知							*/
	case LST_DELBATCHTXDOC_NOTICE:		/* 一括送信原稿消去通知								*/
		DisplayStringHigh(0, D2W_CheckMessage);	/* "ﾁｪｯｸ ﾒｯｾｰｼﾞ         " */
		break;
	case LST_COMMERR_BATCH_CHECKMSG:	/* 一括送信チェックメッセージＢ（交信エラー）		*/
		 /* ワーディングが変わる可能性がある */
		 /* 取り敢えずＴＣＲと同じにしておく */
		 /* TBD 1996/05/24 Eguchi */
#if (0)
		 DisplayStringHigh(0, D2W_CheckMessage);	/* "ﾁｪｯｸ ﾒｯｾｰｼﾞ         " */
#endif
		 DisplayStringHigh(0, D2W_TCR);	/* "ｿｳｼﾝｼｮｳ             " */
		 break;
	case LST_SECURERCV_NOTICE:			/* 親展受信通知										*/
		DisplayStringHigh(0, D2W_PrintSecureMail);	/* "ｼﾝﾃﾝｼﾞｭｼﾝ ﾌﾟﾘﾝﾄ     " */
		break;
#if (PRO_F_CODE == ENABLE)
	case LST_FCODE_BOXRCV_NOTICE:		/* Ｆコード受信通知									*/
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
/*		CMN_StringCopy(DisplayBufferHigh, &D2W_PrintFcodeBoxListMode[3]);	/* "" */
		DisplayStringHigh(0, DisplayBufferHigh);							/* "" */
		break;
	case LST_DEL_FCODE_BOX_DOC_NOTICE:	/* Ｆコード原稿消去通知								*/
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
/*		CMN_StringCopy(DisplayBufferHigh, &D2W_PrintFcodeBoxListMode[3]);	/* "" */
		DisplayStringHigh(0, DisplayBufferHigh);							/* "" */
		break;
#endif
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/01/21 */
 #if (0)	/* 暗号化受信原稿通知はイメージプリントに移動しました 98/01/28 T.Fukumoto */
//	case LST_SCRAMBLE_RCV_NOTICE:		/* 暗号化受信通知									*/
 #endif
	case LST_DEL_SCRAMBLE_RX_NOTICE:	/* 暗号化受信原稿消去通知							*/
	case LST_DEL_SCRAMBLEING_DOC_NOTICE:/* 暗号化中原稿消去通知								*/
	case LST_DEL_DESCRAMBLE_DOC_NOTICE:	/* 暗号化復元原稿消去通知							*/
		ClearDisplayHigh();
		break;
#endif
	case LST_CONSUMERORDER_SHEET:		/* 消耗品発注票										*/
		DisplayStringHigh(0, D2W_SF_OrderForm);	/* "ﾊｯﾁｭｳﾖｳｼ            " */
		break;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	case LST_INF_TEXT_MAIL:
		DisplayStringHigh(0 , D2W_PrintReceiveMail);
		break;
	case LST_INF_JOURNAL_LIST:
		DisplayStringHigh(0, D2W_PrintMailJournal);
		break;
	case LST_INF_SETTING_LIST:
		DisplayStringHigh(0, D2W_PrintUserData);
		break;
	case LST_INF_ADDRESS_LIST:
		DisplayStringHigh(0, D2W_PrintMailAddress);
		break;
	case LST_INF_GROUP_LIST:
		DisplayStringHigh(0, D2W_PrintMailGroup);
		break;
	case LST_INF_MAILCOM_LIST:
		DisplayStringHigh(0, D2W_PrintMailCom);
		break;
	case LST_INF_SECURE_NOTICE:	/* 1998/05/15 by Y.Tanimoto */
		DisplayStringHigh(0, D2W_INF_PrintRcvReport);
		break;
	case LST_INF_ERROR_NOTICE:		/*　チェックメッセージプリント中の表示追加　by Y.Tanimoto 1998/03/23 */
	case LST_INF_ERASED_MAIL_NOTICE:
	case LST_INF_ERASED_COMMAND_NOTICE:
		DisplayStringHigh(0, D2W_CheckMessage);	/* "ﾁｪｯｸ ﾒｯｾｰｼﾞ         " */
		break;
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/18 */
	case LST_ND_LIST:					/* ナンバーディスプレイリスト						*/
		DisplayStringHigh(0, D2W_PrintNumberDisplay);	/* "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘｽﾄ   " */
		break;
	case LST_INF_ND_LIST:				/* ナンバーディスプレイ着信履歴						*/
		DisplayStringHigh(0, D2W_Print_ND_Journal);		/* "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾘﾚｷ   " */
		break;
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE) /* By H.Fujimura 1999/01/18 */
	case LST_WARP_LIST:					/* ＦＡＸワープリスト								*/
		DisplayStringHigh(0, D2W_PrintFaxWarp);	/* "FAXﾜｰﾌﾟ ﾘｽﾄ         " */
		break;
#endif
#if (PRO_DEPART_NEW_LIST == ENABLE) /* By H.Fujimura 1999/02/09 */
	case LST_DEPARTMANAGE_LIST:			/* 部門管理リスト									*/
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(DisplayBufferHigh, &D2W_PrintDepartTimeList[3]);	/* "   ﾌﾞﾓﾝｶﾝﾘﾘｽﾄ ﾌﾟﾘﾝﾄ " */
		DisplayStringHigh(0, DisplayBufferHigh);						/* "ﾌﾞﾓﾝｶﾝﾘﾘｽﾄ ﾌﾟﾘﾝﾄ    " */
		break;
#endif
	default:
		ClearDisplayHigh();
		break;
	}

	/*-------------------------*/
	/* 下段表示				   */
	/*-------------------------*/
#if (PRO_PRINT_TYPE == LED)
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_WARMUP) {	/* プリンターウォームアップ中の時 */
		DisplayStringLow(0, D2W_Wait);		/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
	}
	else {
		DisplayStringLow(0, D2W_Printing);	/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
	}
#else
	DisplayStringLow(0, D2W_Printing);		/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
#endif
}

/*************************************************************************
	module		:[原稿蓄積中の表示]
	function	:[
		1.
	]
	return		:[
		OPR_CONTINUE	:表示未更新
		OPR_END			:表示更新
	]
	common		:[
		SYS_DocumentStoreItem
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/13]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE DisplayDocumentStore(void)
{
#if (PRO_COPY_FAX_MODE == ENABLE)
	/* コピーモードの時はコピーの蓄積表示、ファクスモードの時はコピー以外の蓄積表示しか行いません */
	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		if ((SYS_DocumentStoreItem != SYS_MEM_MULTI_COPY_FILE)
		 && (SYS_DocumentStoreItem != SYS_MEM_MANUAL_COPY_FILE)) {	/* 蓄積中の原稿がコピー原稿以外の時 */
			return(OPR_CONTINUE);
		}
	}
	else {						/* ファクスモードの時 */
		if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
		 || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {	/* 蓄積中の原稿がコピー原稿の時 */
			return(OPR_CONTINUE);
		}
	}
#endif

	/*-----------------------*/
	/* 上段表示				 */
	/* 蓄積原稿種別			 */
	/*-----------------------*/
	DisplayDocumentStoreHigh();

	/*--------------------------*/
	/* 下段表示					*/
	/* 原稿サイズ＋メモリ残量	*/
	/* [A4           ﾒﾓﾘ100%]	*/
	/*--------------------------*/
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_PREPARATION_ADF) {
		DisplayStringLow(0, D2W_ScanPreparing);	/* "ﾖﾐﾄﾘ ｼﾞｭﾝﾋﾞﾁｭｳ ﾃﾞｽ  " */
	}
	else {
#if (PRO_KEYPANEL == PANEL_HINOKI) /*|| (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)*/  /* SATSUKI2で原稿サイズとメモリー残量の表示するこどです(By SMuratec L.Z.W 2003/10/08) */  /* By H.Fujimura 1999/01/18 */
 #if (0)
 ** 			/* 原稿蓄積中の動作をあらわす「＊＊＊＊＊」の点滅＆メモリ残量の点滅が一般ユーザーにとって
 ** 			** わかりにくいとの指摘を受け、表示内容を変更します。
 ** 			** 尚、ＴＷＮの関係で現状のタイプも残しておくことにします。
 ** 			** by O.Kimoto 1999/02/25
 ** 			*/
 **		FlashDisplayStringLow(D2W_MemoryAreaLong2);	/* "   *****     ﾒﾓﾘ   %" */
 #else
 		if (SYB_MaintenanceSwitch[MNT_SW_H5] & DISPLAY_STORING_TYPE) {
 			FlashDisplayStringLow(D2W_MemoryAreaLong2);	/* "   *****     ﾒﾓﾘ   %" */
 		}
 		else {
 			FlashDisplayStringLow(D2W_MemoryAreaShort2);	/* "   *****     ﾒﾓﾘ   %" */
 		}
 #endif

#else
		/* DisplayDocumentSet(SCN_Control.DocumentSize); 1997/05/19 @* <-SCN_Control.DocumentSize T.Nose 1997/03/19 */
		DisplayDocumentSet();
		/* Added by SMuratec L.Z.W 2003/11/07 */
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/11/07 */
		IsDocumentStoring = TRUE;
 #endif
#endif
	}

	return(OPR_END);
}

/*************************************************************************
	module		:[蓄積原稿種類の上段表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		SYS_DocumentStoreItem
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/29]
	author		:[渡辺一章]
*************************************************************************/
void DisplayDocumentStoreHigh(void)
{
	switch (SYS_DocumentStoreItem) {	/** 原稿の種別を解析 */
	case SYS_MEM_TX_FILE:			/** メモリー送信ファイル *//*相手先表示*/
#if (PRO_CIPHER == ENABLE)/* By Y.Suzuki 97/12/9 */
	case SYS_MEM_CIPHER_FILE:		/** 暗号化前原稿 */
#endif

#if 0 /* 警察FAX DVT_ID57 復活 by SMuratec 夏 2005/12/06 */
 #if defined (KEISATSU)		/* 警察FAX DVT_ID Modify by SMuratec K.W.Q 2005/11/04 */
		ClearDisplayHigh();								/* 上段表示クリア */
 #else
		DisplayStoreMemTxDocument();
 #endif		/* End of (defined (KEISATSU)) */
#else
		DisplayStoreMemTxDocument();
#endif

		break;
#if (PRO_BATCH_TX == ENABLE)
	case SYS_MEM_BATCH_TX_FILE1:
	case SYS_MEM_BATCH_TX_FILE2:
	case SYS_MEM_BATCH_TX_FILE3:
	case SYS_MEM_BATCH_TX_FILE4:
	case SYS_MEM_BATCH_TX_FILE5:
		DisplayStoreBatcTxDocument();
		break;
#endif
	case SYS_MEM_MULTI_COPY_FILE:	/** マルチコピーファイル */
	case SYS_MEM_MANUAL_COPY_FILE:	/** 手差しコピー原稿 */
		DisplayStringHigh(0, D2W_SF_Copy);	/* "ｺﾋﾟｰ                " */
		break;
	case SYS_MEM_POLLING_FILE:		/** ポーリング原稿 */
	case SYS_MEM_DB_POLLING_FILE:	/** 検索ポーリング原稿 */
		DisplayStringHigh(0, D2W_PollingDocument);	/* "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ       " */
		break;
#if (PRO_CLASS1 == ENABLE)
	case SYS_MEM_CLASS1_TX_FILE:	/** ローカルスキャン原稿 *//*1996/09/13 Eguchi */
		DisplayStringHigh(0, D2W_PC_FAX_Scan);
		break;
#endif
#if (PRO_F_CODE == ENABLE)
	case SYS_MEM_SUB_BULLETIN_FILE:	/** 掲示板蓄積原稿（サブアドレス通信原稿） */
		CMN_StringCopy(DisplayBufferHigh, D2W_StoreFcodeDocument);	/* "ｹﾞﾝｺｳ ﾁｸｾｷ   ﾌｧｲﾙ:  " */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* WORDINGは"ｹﾞﾝｺｳ ﾁｸｾｷ   ﾌｧｲﾙ:  "を"ｹﾞﾝｺｳ ﾁｸｾｷ F:       "に変更しだので表示位置は調整必要がある by SMuratec L.Z.W 2003/11/13 */
		CMN_UnsignedIntToASC(&DisplayBufferHigh[13], SYS_DocumentStoreNo, 2, ' ');
#else
		CMN_UnsignedIntToASC(&DisplayBufferHigh[18], SYS_DocumentStoreNo, 2, ' ');
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		DisplayStringHigh(0, DisplayBufferHigh);					/* "ｹﾞﾝｺｳ ﾁｸｾｷ   ﾌｧｲﾙ:99" */
		break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/03 by K.Okada */
	case SYS_MEM_MAIL_TX_FILE:	/** Internet FAXメール送信原稿 */
		DisplayStoreMailMemTxDocument();
		break;
#endif
	case SYS_MEM_FIP_FILE:
	default:
		break;
	}
}

/*************************************************************************
	module		:[メモリ送信原稿蓄積時の上段表示]
	function	:[
		1.ＬＣＤ上段に送信先番号を表示する。
		2.コマンドファイルに登録されている電話番号を表示用バッファに入るだけ展開する。
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/04]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayStoreMemTxDocument(void)
{
	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	SetDialDataToDispBuffer(OPR_TX_DISPLAY, &SYB_CommandFile[SYS_DocumentStoreNo], DisplayBufferHigh);

#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/11/12 */
	ChangeDisplayBuffer(DisplayBufferHigh);
#endif

	DisplayStringHigh(0, DisplayBufferHigh);
}

/*************************************************************************
	module		:[メール送信原稿蓄積時の上段表示]
	function	:[
		1.ＬＣＤ上段に送信先アドレスを表示する。
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/04/03]
	author		:[K.Okada]
*************************************************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/03 by K.Okada */
void DisplayStoreMailMemTxDocument(void)
{
	/* 初期化 */
	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	OPR_INF_TempAddressInput.Offset = 0;
	CMN_MemorySet(&OPR_INF_TempAddressInput.Buffer[0], OPR_INPUT_BUFFER_MAX, ' ');

	/** FAX番号をGet */
	if (SYS_INF_MixedTxFaxCommandNo != 0xFF) {
		GetFaxNumberInputBuffer(OPR_TX_DISPLAY,
								&SYB_CommandFile[SYS_INF_MixedTxFaxCommandNo],
								&OPR_INF_TempAddressInput.Buffer[0]);
	}

	/** メールアドレスをGet */
	GetAddressInputBuffer(SYS_DocumentStoreNo);

	/** 表示用バッファにコピー */
	CMN_StringCopyNumNotNULL(DisplayBufferHigh, &OPR_INF_TempAddressInput.Buffer[0], OPR_DISPLAY_MAX);

	DisplayStringHigh(0, DisplayBufferHigh);
}
#endif

/*************************************************************************
	module		:[一括送信原稿蓄積中の表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/04]
	author		:[江口,渡辺一章]
*************************************************************************/
#if (PRO_BATCH_TX == ENABLE)
void DisplayStoreBatcTxDocument(void)
{
	CMN_MemorySetNULL(DisplayBufferHigh , OPR_DISPLAY_MAX , ' ');

	/**************** 変更します。 1997/03/27 Eguchi *************/
	CMN_StringCopy(DisplayBufferHigh , D2W_BatchBoxIndexNumber);	/* "ﾎﾞｯｸｽ:    ﾌｧｲﾙ:     " */
	CMN_UnsignedIntToASC(&DisplayBufferHigh[7],
						 (UWORD)((SYS_DocumentStoreItem - SYS_MEM_BATCH_TX_FILE1) + OPR_BATCH_FILE_MIN),
						 1,
						 ' ');
	CMN_UnsignedIntToASC(&DisplayBufferHigh[17], (UWORD)SYS_DocumentStoreNo, 2, '0');

	DisplayStringHigh(0 , DisplayBufferHigh);	/* "ﾎﾞｯｸｽ: 9  ﾌｧｲﾙ:  99 " */
}
#endif

/*************************************************************************
	module		:[原稿サイズ、メモリー残量の表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/05/06]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayDocumentSet(void)
{
	UBYTE	paper_size;
	UBYTE	*wording;
	UWORD	mem_area;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/31 */
	IsDocumentSet = TRUE; 
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/* メモリー残量セット */
#if (PRO_FBS == ENABLE)
	if (CheckCopyDocStore()) {	/* コピー原稿の蓄積中の時 */
		CMN_StringCopy(DisplayBufferLow, D2W_MemoryAreaLong);	/* "             ﾒﾓﾘ   %" */
	}
	else {
		CMN_StringCopy(DisplayBufferLow, D2W_MemoryAreaShort);	/* "             ﾒﾓﾘ   %" */
	}
#else
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/18 *//* Add By O.Kimoto 2002/07/23 */
  #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
	if (!((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) && (!CHK_ReadyModeCopy()))) { /* (通信中でﾒﾓﾘ表示しない) Modify by SMuratec L.Z.W 2003/10/16 */
   #if (PRO_DISPLAY_STOP_KEY_OPR == ENABLE) 
		if (!((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)				/* ｽｷｬﾅｰ･ｺﾋﾟｰ中でﾒﾓﾘ表示しない */
		 && !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_SCANNER_COPY))) {	
   #else
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)) { /** ｽｷｬﾅｰ･ｺﾋﾟｰ中でﾒﾓﾘ表示しない */
   #endif
			if (SYB_MaintenanceSwitch[MNT_SW_H5] & DISPLAY_STORING_TYPE) {
				CMN_StringCopy(&DisplayBufferHigh[16], &D2W_MemoryAreaLong[16]);	/* "             ﾒﾓﾘ   %" */
			}
			else {
				CMN_StringCopy(&DisplayBufferHigh[16], &D2W_MemoryAreaShort[16]);	/* "             ﾒﾓﾘ   %" */
			}
		}
	}
  #else
	if (SYB_MaintenanceSwitch[MNT_SW_H5] & DISPLAY_STORING_TYPE) {
		CMN_StringCopy(DisplayBufferLow, D2W_MemoryAreaLong);	/* "             ﾒﾓﾘ   %" */
	}
	else {
		CMN_StringCopy(DisplayBufferLow, D2W_MemoryAreaShort);	/* "             ﾒﾓﾘ   %" */
	}
  #endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
 #else
	CMN_StringCopy(DisplayBufferLow, D2W_MemoryAreaLong);	/* "             ﾒﾓﾘ   %" */
 #endif
#endif
	mem_area = (UWORD)MEM_CountEmptyBlockRate();
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
	if (!((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) && (!CHK_ReadyModeCopy()))) { /* (通信中でﾒﾓﾘ表示しない) Modify by SMuratec L.Z.W 2003/10/16 */
   #if (PRO_DISPLAY_STOP_KEY_OPR == ENABLE) 
		if (!((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)				/* ｽｷｬﾅｰ･ｺﾋﾟｰ中でﾒﾓﾘ表示しない */
		 && !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_SCANNER_COPY))) {	
   #else
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)) { /** ｽｷｬﾅｰ･ｺﾋﾟｰ中でﾒﾓﾘ表示しない */
   #endif
			CMN_UnsignedIntToASC(&DisplayBufferHigh[16], mem_area, 3, ' ');
		}
	}
#else
	CMN_UnsignedIntToASC(&DisplayBufferLow[16], mem_area, 3, ' ');
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if (PRO_FBS == ENABLE)
	/* 次原稿のあり／なし */
	if (SYS_NextBookDocument == TRUE) {
		CMN_StringCopy(&DisplayBufferLow[5], D2W_NextDocument);	/* "ｼﾞｹﾞﾝｺｳ" */
	}
#endif

	/* 原稿サイズワーディングセット */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {	/* 原稿蓄積中の時 */
#if (PRO_FBS == ENABLE)
		/* コピー原稿の蓄積の時 */
		/* 注）蓄積開始時点では、マシンステータスのコピー中は立っていないので、SYS_DocumentStoreItemで判断します */
		if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)		/* マルチコピー原稿蓄積	*/
		 || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {	/* 手差しコピー原稿蓄積	*/
			/* 仕様変更により、コピー原稿の蓄積中だけは、原稿サイズを表示しません
			** 注）読み取りサイズを表示する仕様のままだと、例えばハガキを１００％でコピーする場合、
			** 　　読み取りサイズはＡ５Ｒなので、コピーするサイズと違うサイズを表示してしまい、
			** 　　誤解を生む恐れがあるため
			*/
			if (SYB_MaintenanceSwitch[MNT_SW_B4] & DSP_SCAN_DOC_SIZE) {	/* 原稿読み取りｻｲｽﾞを表示する時（ﾃﾞﾊﾞｯｸﾞ用） */
				SetRegularDocumentSizeWording(DisplayBufferLow);
			}
		}
		/* コピー以外の原稿蓄積の時 */
		else {
			if (SYS_ScannerExecMode == SCN_ADF) {	/* ＡＤＦから読み取る時 */
				SetDocumentScanSizeWording(DisplayBufferLow, SYS_DocumentScanSize);
			}
			else {									/* ＦＢＳから読み取る時 */
				SetRegularDocumentSizeWording(DisplayBufferLow);
			}
		}
#else
		SetDocumentScanSizeWording(DisplayBufferLow, SYS_DocumentScanSize);
#endif /* (PRO_FBS == ENABLE) */
	}
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/12/17 */
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) ||	/* スキャナコピー中 */
			 ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) && (SYS_FaxComTxType == SYS_SCANNER_TX) && (CMN_CheckDocumentOnFeeder() == FALSE))) { /* スキャナ送信実行中 */
		SetDocumentScanSizeWording(DisplayBufferLow, SYS_DocumentScanSize);
	}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
	else {															/* 原稿セット・繰り込み・排出中の時 */
		SetDocumentScanSizeWording(DisplayBufferLow, CMN_GetDocumentScanSize());
	}

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (「＊」を点滅させます) Modify by SMuratec L.Z.W 2003/08/01 */
	SetDocumentSetWording(DisplayBufferLow);
	/* Added by SMuratec L.Z.W 2003/08/04 */
	DisplayStringHigh(16, &DisplayBufferHigh[16]);

	/* 原稿サイズワーディングセット */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {	/* 原稿蓄積中の時 */
		FlashDisplayStringLow(DisplayBufferLow);
	}
	else {
		/* 原稿サイズ・ブック次原稿のあり／なし・メモリー残量表示 */
		DisplayStringLow(0, DisplayBufferLow);
	}
#else

	/* 原稿サイズ・ブック次原稿のあり／なし・メモリー残量表示 */
	DisplayStringLow(0, DisplayBufferLow);
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[ＡＤＦ原稿サイズワーディングセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/20]
	author		:[渡辺一章]
*************************************************************************/
void SetDocumentScanSizeWording(UBYTE *set_buf, UBYTE scan_size)
{
	UBYTE	*wording_ptr;

	switch (scan_size) {
	case SYS_DOCUMENT_A4_SIZE:
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用読取りサイズ表示対応] By S.Fukui Aug.25,1998  */
		wording_ptr = D2W_PaperSize_LtLg; 
#else
		wording_ptr = D2W_PaperSize_A4;
#endif
		break;
	case SYS_DOCUMENT_B4_SIZE:
		wording_ptr = D2W_PaperSize_B4;
		break;
	case SYS_DOCUMENT_A3_SIZE:
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用読取りサイズ表示対応] By S.Fukui Aug.25,1998  */
		wording_ptr = D2W_PaperSize_Ledger;
#else
		wording_ptr = D2W_PaperSize_A3;
#endif
		break;
	default:
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用読取りサイズ表示対応] By S.Fukui Aug.25,1998  */
		wording_ptr = D2W_PaperSize_Letter; 
#else
		wording_ptr = D2W_PaperSize_A4;
#endif
		break;
	}

	CMN_StringCopy(set_buf, wording_ptr);
}

/*************************************************************************
	module		:[ＦＢＳ読み取り原稿サイズワーディングセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/20]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_FBS == ENABLE)	/* 1997/11/14 Y.Matsukuma */
void SetRegularDocumentSizeWording(UBYTE *set_buf)
{
	UBYTE	*wording_ptr;

	switch (SCN_RegularDocumentSize) {
	case SYS_REGULAR_SIZE_B4:
		wording_ptr = D2W_PaperSize_B4;
		break;
	case SYS_REGULAR_SIZE_A4:
		wording_ptr = D2W_PaperSize_A4;
		break;
	case SYS_REGULAR_SIZE_B5R:
		wording_ptr = D2W_PaperSize_B5R;
		break;
	case SYS_REGULAR_SIZE_A5R:
		wording_ptr = D2W_PaperSize_A5R;
		break;
	case SYS_REGULAR_SIZE_LETTER:             /* added by honda 1997/11/14 レター USAで必要？ */
		wording_ptr = D2W_PaperSize_Letter;
		break;
	case SYS_REGULAR_SIZE_LEGAL:              /* added by honda 1997/11/14 リーガル USAで必要？ */
		wording_ptr = D2W_PaperSize_Legal;
		break;
	case SYS_REGULAR_SIZE_HALFLETTER_R:       /* added by honda 1997/11/14 ハーフレター横 */
	    wording_ptr = D2W_PaperSize_HalfLetterR;
	    break;
	case SYS_REGULAR_SIZE_F4:				/* POPLAR_B AUS bythonda1998/05/12 F4対応 */
	    wording_ptr = D2W_PaperSize_F4;
	    break;
	default:
		wording_ptr = D2W_PaperSize_A4;
		break;
	}

	CMN_StringCopy(set_buf, wording_ptr);
}
#endif

/*************************************************************************
	module		:[完了表示実行]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/05/06]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayComplete(void)
{
	/** 通信完了表示 */
#if (PRO_MULTI_LINE == DISABLE)
	if ((tskno_faxcom_complete != 0xFFFF) && (!CHK_ReadyModeCopy())) {
 /* 警察FAX DVT Modify by SMuratec 夏 2005/12/06
 ** 通信完了のメッセージは実際通信回線側だけ表示を制限
 */
 #if defined(KEISATSU)
  #if 0 /* 警察FAX DVT_ID74 Deleted by SMuratec 夏 2005/12/17 */
 		/* 警察FAX DVT_ID69 Added by SMuratec 夏 2005/12/15 */
 		if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON){
			return;
		}
  #endif
		if (((SYS_InternalLineNumber == SYS_STD_LINE_COM) && CheckIsKanyuLine()) ||
			((SYS_InternalLineNumber == SYS_EXT_LINE_COM) && !CheckIsKanyuLine())) {
	 		if (FaxComTXorRX_Sign == TX_COM_MODE) { /** 送信終了 */
				DisplayStringLow(0, D2W_TransmitComplete);	/* " **  ｿｳｼﾝ ｶﾝﾘｮｳ  ** " */
			}
			else if (FaxComTXorRX_Sign == RX_COM_MODE) { /** 受信終了 */
				DisplayStringLow(0, D2W_ReceiveComplete);	/* " **  ｼﾞｭｼﾝｶﾝﾘｮｳ  ** " */
			}
		}
 #else	
		if (FaxComTXorRX_Sign == TX_COM_MODE) { /** 送信終了 */
			DisplayStringLow(0, D2W_TransmitComplete);	/* " **  ｿｳｼﾝ ｶﾝﾘｮｳ  ** " */
		}
		else if (FaxComTXorRX_Sign == RX_COM_MODE) { /** 受信終了 */
			DisplayStringLow(0, D2W_ReceiveComplete);	/* " **  ｼﾞｭｼﾝｶﾝﾘｮｳ  ** " */
		}
 #endif
	}
#else
	if ((tskno_faxcom_complete != 0xFFFF) && (!CHK_ReadyModeCopy())) {
		if (FaxComCompleteDisplaySign == TX_COM_MODE) { /** 送信終了 */
			DisplayStringLow(0, D2W_TransmitComplete);	/* " **  ｿｳｼﾝ ｶﾝﾘｮｳ  ** " */
		}
		else if (FaxComCompleteDisplaySign == RX_COM_MODE) { /** 受信終了 */
			DisplayStringLow(0, D2W_ReceiveComplete);	/* " **  ｼﾞｭｼﾝｶﾝﾘｮｳ  ** " */
		}
	}
#endif

	/** コピー原稿蓄積完了表示 */
#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1997/11/20 */
	if ((timer_store_copy_complete != 0xFF) && (CHK_ReadyModeCopy())) {
		DisplayStringLow(0, D2W_StoreComplete);	/* " **  ﾖﾐﾄﾘ ｶﾝﾘｮｳ  ** " */
		return;
	}
#else
	if (timer_store_copy_complete != 0xFF) { /* <- tskno_store_complete T.Nose 1997/03/11 */
		DisplayStringLow(0, D2W_StoreComplete);	/* " **  ﾖﾐﾄﾘ ｶﾝﾘｮｳ  ** " */
		return;
	}
#endif

	/** メモリー送信原稿蓄積完了表示 by K.Watanabe 1997/11/19 */
	if ((timer_store_fax_complete != 0xFF) && (!CHK_ReadyModeCopy())) {
		/* 次原稿確認中に１分間放置された場合、上段が確認のメッセージのままなので、上段を更新する処理を追加します */
		ClearDisplayHigh();
		DisplayDocumentStoreHigh();				/* 蓄積原稿種類の上段表示 */
		DisplayStringLow(0, D2W_StoreComplete);	/* " **  ﾖﾐﾄﾘ ｶﾝﾘｮｳ  ** " */
		return;
	}

	/** プリント完了表示 */
	if (tskno_print_complete != 0xFFFF) {
#if (PRO_COPY_FAX_MODE == ENABLE)
		if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
			if ((SYS_DocumentPrintItem == SYS_MEM_MULTI_COPY_FILE)
			 || (SYS_DocumentPrintItem == SYS_MEM_MANUAL_COPY_FILE)) {	/* プリント完了した原稿が、コピー原稿の時 */
				/* 上段右端のページ表示、部数表示しない T.Nose 1997/12/29 */
				DisplayStringHigh(0, D2W_SF_Copy);	    /* "ｺﾋﾟｰ                " */
				DisplayStringLow(0, D2W_PrintComplete);	/* " **  ﾌﾟﾘﾝﾄｶﾝﾘｮｳ  ** " */
			}
			/* コピーモードでも、コピー以外でＰＣプリント原稿のプリント中表示だけは行います by K.Watanabe 1998/01/29 */
			else if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) {
				DisplayStringLow(0, D2W_PrintComplete);	/* " **  ﾌﾟﾘﾝﾄｶﾝﾘｮｳ  ** " */
			}
		}
		else {						/* ファクスモードの時 */
			if ((SYS_DocumentPrintItem != SYS_MEM_MULTI_COPY_FILE)
			 && (SYS_DocumentPrintItem != SYS_MEM_MANUAL_COPY_FILE)) {	/* プリント完了した原稿が、コピー原稿以外の時 */
				DisplayStringLow(0, D2W_PrintComplete);	/* " **  ﾌﾟﾘﾝﾄｶﾝﾘｮｳ  ** " */
			}
		}
#else
		DisplayStringLow(0, D2W_PrintComplete);			/* " **  ﾌﾟﾘﾝﾄｶﾝﾘｮｳ  ** " */
#endif
		return;
	}

#if (PRO_CLASS1 == ENABLE) /* 1996/09/13 Eguchi */
	/** ＰＣＦＡＸ完了表示 */
	if ((tskno_pc_fax_complete != 0xFFFF) && (!CHK_ReadyModeCopy())) {
		DisplayStringLow(0, D2W_PC_FAX_Complete);		/* " ** PC-FAX ｶﾝﾘｮｳ ** " */
		return;
	}
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
	if (tskno_inf_complete != 0xffff && (!CHK_ReadyModeCopy())) {	/** ｲﾝﾀｰﾈｯﾄFAX　通信完了表示　by Y.Tanimoto */
		DisplayStringLow(0, D2W_INF_Complete);
		return;
	}
#endif

}

/*************************************************************************
	module		:[原稿挿入・排出時の上段表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/27]
	author		:[渡辺一章]
*************************************************************************/
void DisplayDocumentOnFeeder(void)
{
#if (PRO_COPY_FAX_MODE == ENABLE)
	/* 現状では、ファクスモードの時しか原稿排出中の表示をしないので、これで問題ありませんが、
	** 仕様変更でコピーモードでも表示を行うようになれば条件を追加する必要があります
	*/
	DisplayStringHigh(0, D2W_TransmitReady);	/* "ﾂｳｼﾝ ﾃﾞｷﾏｽ          " */
#else
 #if (PRO_UPPER_COVER == ENABLE)	/* トップカバーの条件追加 by K.Watanabe 1998/01/23 */
	/** プリンターに異常なし、かつコピー禁止ＯＦＦ、かつトップカバーが閉じている時のみ、コピーできます表示を行います */
	if ((CMN_CheckNoPrinterError() == TRUE)
	 && (!CHK_CopyProtectON())
	 && (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN))) {
		DisplayStringHigh(0, D2W_TransmitOrCopyReady);	/* "ﾂｳｼﾝ/ｺﾋﾟｰ ﾃﾞｷﾏｽ     " */
	}
	else {
		DisplayStringHigh(0, D2W_TransmitReady);		/* "ﾂｳｼﾝ ﾃﾞｷﾏｽ          " */
	}
 #else

  /*
  // ファネットの指摘があったが，最終的には対応せずとした by J.Kishida 2002/12/05
  */
  #if (0)/*defined(HINOKI2) && defined(JPNNTT)*/
//  /* ファネット指摘事項(No.13)
//  ** 紙なしでかつメモリフル時に「ﾂｳｼﾝ/ｺﾋﾟｰ ﾃﾞｷﾏｽ」表示は動作と一致していないという指摘があった
//  ** by O.Kimoto 2002/10/30
//  */
//	/** プリンターに異常なし、かつコピー禁止ＯＦＦ->２個目の条件はいらん */
//	if ((CMN_CheckNoPrinterError() == TRUE) && (!CHK_CopyProtectON())) {
//		if ((CMN_CheckPaperExist() == FALSE) && (CMN_CheckAutoCalledEnable() == FALSE)) {
//			DisplayStringHigh(0, D2W_TransmitReady);		/* "ﾂｳｼﾝ ﾃﾞｷﾏｽ          " */
//		}
//		else {
//			DisplayStringHigh(0, D2W_TransmitOrCopyReady);	/* "ﾂｳｼﾝ/ｺﾋﾟｰ ﾃﾞｷﾏｽ     " */
//		}
//	}
//	else {
//		DisplayStringHigh(0, D2W_TransmitReady);		/* "ﾂｳｼﾝ ﾃﾞｷﾏｽ          " */
//	}
  #else
   #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/27 */
	/* 表示用バッファの初期化 */
    #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
	ClearDisplayHigh();
    #endif
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');	

	DisplayKeisatsuSettings(FunctionDisplayBufferHigh);
   	DisplayStringHigh(0,FunctionDisplayBufferHigh);
   #else
    /** プリンターに異常なし、かつコピー禁止ＯＦＦ->２個目の条件はいらん */
	if ((CMN_CheckNoPrinterError() == TRUE) && (!CHK_CopyProtectON())) {
		DisplayStringHigh(0, D2W_TransmitOrCopyReady);	/* "ﾂｳｼﾝ/ｺﾋﾟｰ ﾃﾞｷﾏｽ     " */
	}
	else {
		DisplayStringHigh(0, D2W_TransmitReady);		/* "ﾂｳｼﾝ ﾃﾞｷﾏｽ          " */
	}
   #endif		/* End of (defined (KEISATSU)) */
  #endif
 #endif
#endif
}

/*************************************************************************
	module		:[クラス１動作中の表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[初期化中などクラス１モジュールの動作状態ごとで表示を変えたい場合は
				　SYS_CL1_Statusを参照したらできるはず]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/09/13]
	author		:[江口]
*************************************************************************/
#if (PRO_CLASS1 == ENABLE)
void DisplayClass1(void)
{
	DisplayStringHigh(0, D2W_PC_FAX_Connect);	/* "PC-FAX ｾﾂｿﾞｸ        " */
	ClearDisplayLow();
}
#endif

/*************************************************************************
	module		:[ＰＣプリント原稿受信中の表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/09/30]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_PC_PRINT == ENABLE)
void DisplayPcPrint(void)
{
	DisplayStringHigh(0, D2W_PC_Print);		/* "PC                  " */
	DisplayStringLow(0, D2W_PC_Receiving);	/* "  ** Receiving **   " */
}
#endif

/*************************************************************************
	module		:[暗号化・復号化の進捗度表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/04]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_CIPHER == ENABLE)
void DisplayCipherProcess(UBYTE *exec_wording)
{
#if (0)	/* スクランブル解除中の進捗率が一定度合で表示できないので、進捗度の表示を止めます by K.Watanabe 1998/02/17 */
//	UBYTE	i;				/* ループ変数 */
//	UBYTE	set_pos;		/* ＣＧセット開始位置 */
//	UBYTE	process_dot;	/* 処理進捗度（％） */
#endif

#if (0)	/* スクランブル解除中の進捗率が一定度合で表示できないので、進捗度の表示を止めます by K.Watanabe 1998/02/17 */
//	WriteCGRAM((UBYTE *)CG_RamTableCopyModeDensity);	/* 暗号化進行度表示用のデータをＣＧＲＡＭに書き込みます */
#endif

	/* 上段表示内容をセット（処理内容・処理ページ数） */
	CMN_StringCopyNULL(DisplayBufferHigh, exec_wording);						/* 処理内容のワーディングをセット */
	CMN_UnsignedIntToASC(&DisplayBufferHigh[15], CipherWritePageNo, 2, '0');	/* 処理中のページ数 */
	CMN_UnsignedIntToASC(&DisplayBufferHigh[18], CipherData.PageNo, 2, '0');	/* 全処理枚数 */

#if (0)	/* スクランブル解除中の進捗率が一定度合で表示できないので、進捗度の表示を止めます by K.Watanabe 1998/02/17 */
//	/* 下段表示内容をセット（進捗度） */
//	CMN_StringCopyNULL(DisplayBufferLow, D2W_ProgressRate);	/* " 0%            100% " */
//	set_pos = 4;											/* ＣＧセット開始位置をセット */
//	process_dot = (UBYTE)(SYS_CipherPercent / 10);			/* 進捗度を表示用に０～１０にします */
//	CMN_MemorySet(&DisplayBufferLow[set_pos], 10, 0xF6);	/* 全進捗度を表すＣＧ（四角）をセットします */
//	for (i = 0; i < process_dot ; i++) {	/* 現在の進捗度を表すＣＧ（全黒）をセットします */
//		DisplayBufferLow[set_pos + i] = 0xF7;
//	}
#endif

	/* 上下段の表示 */
#if (0)	/* スクランブル解除中の進捗率が一定度合で表示できないので、進捗度の表示を止めます by K.Watanabe 1998/02/17 */
//	DisplayStringHigh(0, DisplayBufferHigh);	/* "スクランフ゛ル　　　　　　　　０１／１０" */
//	DisplayStringLow(0, DisplayBufferLow);		/* "　０％　■■■□□□□□□□　１００％　" */
#endif
	/* 日本以外も同様に下段表示を行います by K.Watanabe 1998/06/04 */
	DisplayStringHigh(0, DisplayBufferHigh);	/* "ｽｸﾗﾝﾌﾞﾙ        01/10" */
#if (0)	/* ｽｸﾗﾝﾌﾞﾙ中はﾀｽｸが解放されない為に、正しく点滅ができないので、点滅表示を止めます by K.Watanabe 1998/03/04 */
//	FlashDisplayStringLow(D2W_Wait);			/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
#endif
	DisplayStringLow(0, D2W_Wait);				/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
}
#endif

#if (PRO_COPY_FAX_MODE == ENABLE)
/*************************************************************************
	module		:[コピーモード時の待機表示]
	function	:[
		1.コピーモード時の待機表示を行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/18]
	author		:[渡辺一章]
*************************************************************************/
void DisplayCopyMode(void)
{
	/** 上段の表示 */
	DisplayCopyModeHigh();

	/** 下段の表示 */
	DisplayCopyModeLow();

	/* カーソルの表示 */
	/* 注）DisplayString()の中でカーソルがOFFされるので、最後にカーソル表示を行います */
	if (OPR_CopyNumberInputFigure != 0) {	/* 数字入力中の時 */
		if (OPR_NumberKeyInputMode == OPR_COPY_NUMBER_INPUT_MODE) {	/* コピー部数入力モードの時 */
			/* 倍率が適正範囲外の時は、上段にエラー表示を行っているので、カーソル表示は出来ません */
			if (CheckCopyMagnifiLimit(OPR_CopyData.Reduction) == OPR_MAGNIFI_OK) {	/* 倍率が適正範囲内の時 */
				CursorOn(19);
			}
		}
		else {														/* コピー倍率入力モードの時 */
			CursorOn(38);
		}
	}
}

/*************************************************************************
	module		:[コピーモード時の待機表示（上段）]
	function	:[
		1.倍率入力中の時は、入力中の表示を行います
		2.倍率が適正範囲外の時は、エラー表示を行います
		3.部数入力中で倍率が適正値の時は、コピーモード・部数の表示を行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/24]
	author		:[渡辺一章]
*************************************************************************/
void DisplayCopyModeHigh(void)
{
	/* 倍率を直接入力中の時 */
	if (OPR_NumberKeyInputMode == OPR_COPY_MAGNIFI_INPUT_MODE) {
		DisplayStringHigh(0, D2W_InputCopyMagnifi);						/* "ﾊﾞｲﾘﾂ ﾆｭｳﾘｮｸ(50-200)" */
	}
	/* 倍率が適正範囲外の時
	** 注）０％は、設定はできないので除きます（ＡＤＦコピーでの、コピー不可能エラーの意味です）
	*/
	else if ((CheckCopyMagnifiLimit(OPR_CopyData.Reduction) != OPR_MAGNIFI_OK) && (OPR_CopyData.Reduction != 0)) {
		FlashDisplayStringHigh(D2W_CopyMagnifiError);					/* "50-200% ｦ ﾄﾞｳｿﾞ     " */
	}
	/* コピー不可能（読み取り不可能・プリント不可能）なエラー表示をしている時 */
	else if (OPR_DispInfo & (OPR_DSP_SCAN_DISABLE | OPR_DSP_PRINT_DISABLE)) {
		ClearDisplayHigh();												/* 上段クリア */
	}
	/* 部数入力モードで倍率が適正値の時 */
	else {
		/* ・コピー不可能（読み取り不可能・プリント不可能）な機器状態の時
		** ・コピー中にカセットの記録紙がなくなった時
		** 以上の場合は、コピー出来ません
		** 注）プリント不可能な時のチェックは、CMN_CheckPrinterError()で行っても問題ありませんが、
		** 　　読み取り不可能な時のチェックを CheckScanStartEnable()で行うと、スタートキーを押すと
		** 　　すぐに、｢ｺﾋﾟｰ ﾃﾞｷﾏｽ｣が消えてしまい変な感じなので、機器的なエラーが起こっている時のみ
		** 　　｢ｺﾋﾟｰ ﾃﾞｷﾏｽ｣表示を消すようにします（よって、スキャナ送信予約中等の時は、｢ｺﾋﾟｰ ﾃﾞｷﾏｽ｣
		** 　　表示はします）
		*/
		if ((DisplayMachineErrorLow(OPR_ERROR_CHK) & (OPR_DSP_SCAN_DISABLE | OPR_DSP_PRINT_DISABLE))
		 || (DisplayMachineErrorLow2(OPR_ERROR_CHK) & (OPR_DSP_SCAN_DISABLE | OPR_DSP_PRINT_DISABLE))
		 || (CheckPossibleCopyReserve() == FALSE)) {
			CMN_StringCopy(DisplayBufferHigh, D2W_CopyImpossibleReady);	/* "             ﾌﾞｽｳ:  " */
		}
		/* コピー可能な時 */
		else {
			if (OPR_CopyData.Cassette == SYS_MANUAL_CASSETTE) {	/* 手差しトレイが選択されている時 */
				CMN_StringCopy(DisplayBufferHigh, D2W_ManualCopyReady);	/* "ｺﾋﾟｰ ﾃｻﾞｼ    ﾌﾞｽｳ:  " */
			}
			else {												/* カセット選択の時 */
				CMN_StringCopy(DisplayBufferHigh, D2W_CopyReady);		/* "ｺﾋﾟｰ ﾃﾞｷﾏｽ   ﾌﾞｽｳ:  " */
			}
		}

		/* コピー部数のセット */
		CMN_UnsignedIntToASC(&DisplayBufferHigh[18], (UWORD)OPR_CopyData.ReserveNumber, OPR_COPY_NUMBER_FIGURE_MAX, ' ');

		DisplayStringHigh(0, DisplayBufferHigh);
	}
}

/*************************************************************************
	module		:[コピーモード時の待機表示（下段）]
	function	:[
		1.原稿濃度・記録紙サイズ・コピー倍率を表示します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/24]
	author		:[渡辺一章]
*************************************************************************/
void DisplayCopyModeLow(void)
{
	/* ＣＧＲＡＭが書き換えられている可能性があるので、コピーモード表示用のＣＧＲＡＭに設定します */
	InitializeCGRAM_Data();

	/** 表示用バッファの初期化 */
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/** 下段表示内容をセット */
	if (!IsCassetteManualChange) {	/* カセットか手差しが選択されている時 */
		/* 倍率を直接入力中の時は、倍率しか表示しません */
		if (OPR_NumberKeyInputMode != OPR_COPY_MAGNIFI_INPUT_MODE) {	/* 倍率入力中でない時 */
			if (IsMagnifiKeyInput) {	/* 拡大・縮小キーで固定倍率に変更されている時 */
				SetDocumentSize();							/* 記録紙・倍率に対する原稿サイズのセット */
			}
			else {
				SetCopyModePaperDensity();					/* 原稿濃度のセット */
			}
			SetCassettePaperSize(&DisplayBufferLow[7]);		/* カセット段数・記録紙サイズのセット */
		}
		SetCopyModeMagnification(&DisplayBufferLow[16]);	/* 倍率のセット */
	}
	else {							/* カセット→手差しへの変更確認の時 */
		CMN_StringCopy(DisplayBufferLow, D2W_ChangeManual);	/* "      ﾃｻﾞｼ → ｾｯﾄｷｰ  " */
	}

	/** 下段の表示 */
	DisplayStringLow(0, DisplayBufferLow);
}

/*************************************************************************
	module		:[コピーモード時の原稿濃度セット]
	function	:[
		1.設定されている原稿濃度をセットします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/26]
	author		:[渡辺一章]
*************************************************************************/
void SetCopyModePaperDensity(void)
{
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//	DisplayBufferLow[0] = 0xF0;
//	DisplayBufferLow[4] = 0xF4;
#endif
	DisplayBufferLow[0] = OPR_CG_FONT_0;
	DisplayBufferLow[4] = OPR_CG_FONT_4;

	switch (SYB_CopyDensitySw) {
	case SYS_LIGHT_DENSITY:			/* 薄く */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		DisplayBufferLow[1] = 0xF1;
#endif
		DisplayBufferLow[1] = OPR_CG_FONT_1;
		break;
	case SYS_LIGHT_NORMAL_DENSITY:	/* 薄く－普通の間 */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		DisplayBufferLow[1] = 0xF2;
#endif
		DisplayBufferLow[1] = OPR_CG_FONT_2;
		break;
	case SYS_NORMAL_DENSITY:		/* 普通 */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		DisplayBufferLow[1] = 0xF2;
//		DisplayBufferLow[2] = 0xF3;
#endif
		DisplayBufferLow[1] = OPR_CG_FONT_2;
		DisplayBufferLow[2] = OPR_CG_FONT_3;
		break;
	case SYS_DARK_NORMAL_DENSITY:	/* 濃く－普通の間 */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		DisplayBufferLow[1] = 0xF2;
//		DisplayBufferLow[2] = 0xF3;
//		DisplayBufferLow[3] = 0xF1;
#endif
		DisplayBufferLow[1] = OPR_CG_FONT_2;
		DisplayBufferLow[2] = OPR_CG_FONT_3;
		DisplayBufferLow[3] = OPR_CG_FONT_1;
		break;
	case SYS_DARK_DENSITY:			/* 濃く */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		DisplayBufferLow[1] = 0xF2;
//		DisplayBufferLow[2] = 0xF3;
//		DisplayBufferLow[3] = 0xF2;
#endif
		DisplayBufferLow[1] = OPR_CG_FONT_2;
		DisplayBufferLow[2] = OPR_CG_FONT_3;
		DisplayBufferLow[3] = OPR_CG_FONT_2;
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[コピーモード時の記録紙サイズセット]
	function	:[
		1.選択されているカセットの段数・記録紙サイズのワーディングをセットします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/17]
	author		:[渡辺一章]
*************************************************************************/
void SetCassettePaperSize(UBYTE *dsp_buf_ptr)
{
	UBYTE	*buf_ptr;

 #if (PRO_ADF_AUTO_CASSETTE == ENABLE)
	/* (自動カセット選択時はここで表示設定します。 By S.Fukui Jan.23,1998 */
	if (OPR_CopyData.Cassette == SYS_AUTO_CASSETTE) {
		CMN_StringCopy(dsp_buf_ptr,D2W_PaperSize_Auto);
		return;
	}
 #endif


	/* カセットの段数をセットします */
	buf_ptr = SetCassetteCharacter(dsp_buf_ptr, OPR_CopyData.Cassette);

	*(buf_ptr++) = ':';

	/* 選択されているカセットの記録紙サイズのワーディングをセットします */
	SetPaperSizeWording(buf_ptr, GetPaperSize(OPR_CopyData.Cassette), OPR_CopyData.OHPMode);
}

/*************************************************************************
	module		:[カセット段数文字セット]
	function	:[
		1.指定のカセット段数を文字にして、指定のバッファにセットします
	]
	return		:[カセット段数セット後のアドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/16]
	author		:[渡辺一章]
*************************************************************************/
UBYTE *SetCassetteCharacter(UBYTE *dsp_buffer, UBYTE cassette)
{
	UBYTE	cassette_str[3];	/* 指定カセットの段数 */

	CMN_MemorySetNULL(cassette_str, 2, ' ');

	/* 選択されているカセット段数をセットします */
	switch (cassette) {
	case SYS_AUTO_CASSETTE:		/* 自動選択・指定なし */
		/* ポプラＢでは自動選択・指定なしは選択できません */
		/* (ｺﾒﾝﾄのみ追加 By S.Fukui Jan.23,1998 )
		** ＡＤＦ時に自動カセット選択された場合の表示に関しては上位関数で対応します。
        */
		break;
	case SYS_1ST_CASSETTE:		/* １段目カセット選択 */
		cassette_str[0] = 'C';
		cassette_str[1] = '1';
		break;
	case SYS_2ND_CASSETTE:		/* ２段目カセット選択 */
		cassette_str[0] = 'C';
		cassette_str[1] = '2';
		break;
	case SYS_3RD_CASSETTE:		/* ３段目カセット選択 */
		cassette_str[0] = 'C';
		cassette_str[1] = '3';
		break;
	case SYS_MANUAL_CASSETTE:	/* 手差しカセット選択 */
 #if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
		cassette_str[1] = *CalculateStringAddress(&D2W_HeadCharacter_Tray);
 #else
		cassette_str[1] = 'T';
 #endif
		break;
	default:
		break;
	}
	CMN_StringCopy(dsp_buffer, cassette_str);
	dsp_buffer += 2;	/* バッファをカセット段数格納後の位置へ進めます */

	return(dsp_buffer);
}

/*************************************************************************
	module		:[カセット段数ワーディング　セット]
	function	:[
		1.指定のカセット段数を表すワーディングを、指定のバッファにセットします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/16]
	author		:[渡辺一章]
*************************************************************************/
void SetCassetteWording(UBYTE *dsp_buffer, UBYTE cassette)
{
	switch (cassette) {
	case SYS_1ST_CASSETTE:	/* １段目カセット選択 */
		CMN_StringCopy(dsp_buffer, D2W_Cassette1);	/* "ｶｾｯﾄ1               " */
		break;
	case SYS_2ND_CASSETTE:	/* ２段目カセット選択 */
		CMN_StringCopy(dsp_buffer, D2W_Cassette2);	/* "ｶｾｯﾄ2               " */
		break;
	case SYS_3RD_CASSETTE:	/* ３段目カセット選択 */
		CMN_StringCopy(dsp_buffer, D2W_Cassette3);	/* "ｶｾｯﾄ3               " */
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[コピーモード時の倍率セット]
	function	:[
		1.設定されている倍率をセットします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/20]
	author		:[渡辺一章]
*************************************************************************/
void SetCopyModeMagnification(UBYTE *dsp_buf_ptr)
{
	/* コピー倍率入力モードでの０％は、入力値なので”０％”を表示します */
	if ((OPR_CopyData.Reduction != 0) || (OPR_NumberKeyInputMode == OPR_COPY_MAGNIFI_INPUT_MODE)) {
		CMN_UnsignedIntToASC(dsp_buf_ptr, (UWORD)OPR_CopyData.Reduction, 3, ' ');
		dsp_buf_ptr += 3;
	}
	/* コピー部数入力モードで倍率が０％の時は、”－－－％”を表示します
	** 注）コピー部数入力モードで倍率が０％になるのは、
	** 　　ＡＤＦの原稿と記録紙の組み合わせでコピーが不可能な時です
	*/
	else {
		*(dsp_buf_ptr++) = '-';
		*(dsp_buf_ptr++) = '-';
		*(dsp_buf_ptr++) = '-';
	}
	*dsp_buf_ptr = '%';
}

/*************************************************************************
	module		:[記録紙・固定倍率に該当する原稿サイズセット]
	function	:[
		1.固定倍率変更で、記録紙・固定倍率に該当する原稿があれば、
		　そのサイズのワーディングをセットします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/25]
	author		:[渡辺一章]
*************************************************************************/
void SetDocumentSize(void)
{
	/* 該当する原稿サイズがあった時のみ、ワーディングをセットします */
	if (OPR_FixedMagnifiDocSize != SYS_NO_PAPER) {
		/* 原稿サイズのワーディングをセットします */
		SetPaperSizeWording(&DisplayBufferLow[0], OPR_FixedMagnifiDocSize, FALSE);
		DisplayBufferLow[5] = RIGHT_ARROW;	/* → */
	}
}

/*************************************************************************
	module		:[紙無し時カセット段数・記録紙サイズ表示]
	function	:[
		1.紙無しエラーの時、エラーメッセージと共に、カセット段数・記録紙サイズを表示します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/26]
	author		:[渡辺一章]
*************************************************************************/
void DisplayReplacePaperSize(UBYTE cassette)
{
	UBYTE	*buf_address;

	/** 表示用バッファの初期化 */
	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	if (cassette != SYS_MANUAL_CASSETTE) {	/* カセットが選択されている時 */
 #if (0)
		/* カセットの記録紙サイズは、表示できない場合が存在するので、表示する仕様を止めます
		**                           ￣￣￣￣￣￣￣￣
		**                                  ↓
		** 記録紙が無くなった時は、サイズが検出出来なくなるので、前もってサイズを覚えておく
		** 必要がありますが、記録紙無しの違うサイズのカセットに入れ替えられると、入れ替え前の
		** カセットの記録紙サイズしか表示出来ません。（違うサイズを表示してしまう可能性がある）
		** 同様に、１番始めに電源を入れた時に記録紙が無い時も、サイズが表示出来ません。
		*/
 //		buf_address = CMN_StringCopy(DisplayBufferHigh, D2W_ReplaceCassettePaper);	/* "ｶｾｯﾄ" */
 //		/* カセットの記録紙サイズのワーディングをセットします */
 //		SetCassettePaperSize(buf_address, cassette);
 #endif

		/* カセットの段数をセットします */
		SetCassetteWording(DisplayBufferHigh, cassette);
	}
	else {									/* 手差しが選択されている時 */
		buf_address = CMN_StringCopy(DisplayBufferHigh, D2W_ManualCassette);	/* "ﾃｻﾞｼ:   " */
 #if (PRO_PC_PRINT == ENABLE)
		if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) {	/* ＰＣプリントの時 */
			/* ＰＣで指定された、手差しの記録紙サイズのワーディングをセットします */
		/*	SetPaperSizeWording(buf_address, SYS_PC_PrintSize);	By M.Tachibana 1997/11/14 */
			SetPaperSizeWording(buf_address, PRN_PC_Size, FALSE);
		}
		else {												/* 手差しコピーの時 */
			/* 手差しの記録紙サイズのワーディングをセットします */
  #if (0)	/* コピー中のコピー予約が可能になったので、表示元の変数を変更します by K.Watanabe 1997/10/03 */
  //		SetPaperSizeWording(buf_address, GetPaperSize(cassette));
  #endif
			SetPaperSizeWording(buf_address, SYB_ManualCopyFile.Size, SYB_ManualCopyFile.OHPMode);
		}
 #else
		/* 手差しの記録紙サイズのワーディングをセットします */
  #if (0)	/* コピー中のコピー予約が可能になったので、表示元の変数を変更します by K.Watanabe 1997/10/03 */
  //	SetPaperSizeWording(buf_address, GetPaperSize(cassette));
  #endif
		SetPaperSizeWording(buf_address, SYB_ManualCopyFile.Size, SYB_ManualCopyFile.OHPMode);
 #endif
	}

	DisplayStringHigh(0, DisplayBufferHigh);
	DisplayStringLow(0, D2W_ReplaceRxPaper);	/* "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ " */
}
#endif	/* (PRO_COPY_FAX_MODE == ENABLE) */

/*************************************************************************
	module		:[紙サイズワーディングセット]
	function	:[
		1.指定のバッファに紙サイズのワーディングをセットします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		（変更履歴）
		・1998/02/23 by K.Watanabe
			ポプラＬ（ＰＣプリント）でも使用する可能性があるので、(PRO_COPY_FAX_MODE == ENABLE)
			の条件コンパイルをはずします
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/20]
	author		:[渡辺一章]
*************************************************************************/
void SetPaperSizeWording(UBYTE *dsp_buffer, UBYTE paper_size, UBYTE ohp_mode)
{
/*	if (paper_size == SYS_NO_PAPER) {	*//* 紙なしの時 */
	/* 紙なし または カセットなし の時  By S.Fukui Feb.20,1998 */
	if ((paper_size == SYS_NO_PAPER) || (paper_size == SYS_NO_CASSETTE)) {
		CMN_StringCopy(dsp_buffer, D2W_PaperSize_None);		/* "ﾅｼ   " */
	}
	else {								/* 表示するサイズがある時 */
		if (ohp_mode == FALSE) {	/* ＯＨＰ以外の時 */
			CMN_StringCopy(dsp_buffer, D2W_PaperSize_A5 + (paper_size * 6));	/* "A5   " ～ "User " */
		}
		else {						/* ＯＨＰの時 */
			CMN_StringCopy(dsp_buffer, D2W_PaperSize_OHP);	/* "OHP  " */
		}
	}
}

#if (PRO_MULTI_LINE == ENABLE)
/*************************************************************************
	module		:[通信表示データのコピー]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/12/24]
	author		:[村田]
*************************************************************************/
void OverWriteDisplayData(UBYTE stack_number)
{
	UBYTE	num;
	UWORD	i;

	num = stack_number;

	/*----------------------------------------*/
	/*---表示データの各メンバをコピーします---*/
	/*----------------------------------------*/
	if (num == 0) {
		SYS_Display.SYS_FaxCommStage		= SYS_FaxCommStage;			/* 通信遷移状態 define */
		SYS_Display.SYS_CurrentExecQueueNo	= SYS_CurrentExecuteNoSave;	/* Grape実行ExecQueueの番号 */
		SYS_Display.SYS_DocBlock_Src_Size	= SYS_DocBlock.Src.Size;	/* 元原稿パラメータ define */
		SYS_Display.SYS_DocBlock_Src_Mode	= SYS_DocBlock.Src.Mode;	/* 元原稿パラメータ define */
		SYS_Display.SYS_DocBlock_Dst_Size	= SYS_DocBlock.Dst.Size;	/* 先原稿パラメータ define */
		SYS_Display.SYS_DocBlock_Dst_Mode	= SYS_DocBlock.Dst.Mode;	/* 先原稿パラメータ define */
		SYS_Display.GrayModeFlag			= GrayModeFlag;				/* ファイン、中間調の場合--YES yes/no */
		SYS_Display.FaxComTXorRX_Sign		= FaxComTXorRX_Sign;		/* 送信／受信識別フラグ　送信、受信、リモート診断識別 define */
		SYS_Display.SYS_FaxComType			= SYS_FaxComType;			/* 交信種別 define */
		SYS_Display.SYS_FaxComTxType		= SYS_FaxComTxType;			/* 送信原稿種別 define */
		SYS_Display.TxBaudRate				= TxBaudRate;				/* 確定送信ボーレイト define */
		SYS_Display.RxBaudRate				= RxBaudRate;				/* 確定受信ボーレイト define */
		SYS_Display.TxECM_Mode				= TxECM_Mode;				/* 確定ＥＣＭ送信指定 yes/no */
		SYS_Display.RxECM_Mode				= RxECM_Mode;				/* 確定ＥＣＭ受信指定 yes/no */
		SYS_Display.FinalRxMode				= FinalRxMode;				/* 確定受信モード define */
		SYS_Display.SYS_TxTotalPage			= SYS_TxTotalPage;			/* 全送信ページ数 */
		SYS_Display.SYS_RxTotalPage			= SYS_RxTotalPage;			/* 全受信ページ数 */
		SYS_Display.TxMemoryFilePage		= TxMemoryFilePage;			/* メモリ送信を行う原稿のファイルページ */
		SYS_Display.MDM_RxTotalLine			= MDM_RxTotalLine;			/* 受信トータルライン */
		SYS_Display.MDM_RxErrorTotalLine	= MDM_RxErrorTotalLine;		/* 受信エラートータルライン */
		SYS_Display.BatchTxFinishPage		= BatchTxFinishPage;		/* 一括送信送信済み頁数 */
		for (i = 0; i < SYS_TTI_ID_MAX ; i++) {
			SYS_Display.NonStandardID[i] = NonStandardID[i];			/* 交信相手機の村田ＩＤ */
		}
		for (i = 0; i < SYS_ID_MAX ; i++) {
			SYS_Display.StandardID[i] = StandardID[i];					/* 交信相手機の標準ＩＤ */
		}
	}
	else {
		SYS_Display.SYS_FaxCommStage		= SYS_Opt[num].SYS_FaxCommStage;		/* 通信遷移状態 define */
		SYS_Display.SYS_CurrentExecQueueNo	= SYS_Opt[num].SYS_CurrentExecQueueNo;	/* Grape実行ExecQueueの番号 */
		SYS_Display.SYS_DocBlock_Src_Size	= SYS_Opt[num].SYS_DocBlock_Src_Size;	/* 元原稿パラメータ define */
		SYS_Display.SYS_DocBlock_Src_Mode	= SYS_Opt[num].SYS_DocBlock_Src_Mode;	/* 元原稿パラメータ define */
		SYS_Display.SYS_DocBlock_Dst_Size	= SYS_Opt[num].SYS_DocBlock_Dst_Size;	/* 先原稿パラメータ define */
		SYS_Display.SYS_DocBlock_Dst_Mode	= SYS_Opt[num].SYS_DocBlock_Dst_Mode;	/* 先原稿パラメータ define */
		SYS_Display.GrayModeFlag			= SYS_Opt[num].GrayModeFlag;			/* ファイン、中間調の場合--YES yes/no */
		SYS_Display.FaxComTXorRX_Sign		= SYS_Opt[num].FaxComTXorRX_Sign;		/* 送信／受信識別フラグ　送信、受信、リモート診断識別 define */
		SYS_Display.SYS_FaxComType			= SYS_Opt[num].SYS_FaxComType;			/* 交信種別 define */
		SYS_Display.SYS_FaxComTxType		= SYS_Opt[num].SYS_FaxComTxType;		/* 送信原稿種別 define */
		SYS_Display.TxBaudRate				= BaudRateCompatible(SYS_Opt[num].TxBaudRate);/* 確定送信ボーレイト define */
		SYS_Display.RxBaudRate				= BaudRateCompatible(SYS_Opt[num].RxBaudRate);/* 確定受信ボーレイト define */
		SYS_Display.TxECM_Mode				= SYS_Opt[num].TxECM_Mode;				/* 確定ＥＣＭ送信指定 yes/no */
		SYS_Display.RxECM_Mode				= SYS_Opt[num].RxECM_Mode;				/* 確定ＥＣＭ受信指定 yes/no */
		SYS_Display.FinalRxMode				= SYS_Opt[num].FinalRxMode;				/* 確定受信モード define */
		SYS_Display.SYS_TxTotalPage			= SYS_Opt[num].SYS_TxTotalPage;			/* 全送信ページ数 */
		SYS_Display.SYS_RxTotalPage			= SYS_Opt[num].SYS_RxTotalPage;			/* 全受信ページ数 */
		SYS_Display.TxMemoryFilePage		= SYS_Opt[num].TxMemoryFilePage;		/* メモリ送信を行う原稿のファイルページ */
		SYS_Display.MDM_RxTotalLine			= SYS_Opt[num].MDM_RxTotalLine;			/* 受信トータルライン */
		SYS_Display.MDM_RxErrorTotalLine	= SYS_Opt[num].MDM_RxErrorTotalLine;	/* 受信エラートータルライン */
		SYS_Display.BatchTxFinishPage		= SYS_Opt[num].BatchTxFinishPage;		/* 一括送信送信済み頁数 */
		for (i = 0; i < SYS_TTI_ID_MAX ; i++) {
			SYS_Display.NonStandardID[i] = SYS_Opt[num].NonStandardID[i];			/* 交信相手機の村田ＩＤ */
		}
		for (i = 0; i < SYS_ID_MAX ; i++) {
			SYS_Display.StandardID[i] = SYS_Opt[num].StandardID[i];					/* 交信相手機の標準ＩＤ */
		}
	}
}

/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[]
	author		:[]
*************************************************************************/
/* オプションボードとホストで通信速度のdefine が異なるのであわせます */
UBYTE BaudRateCompatible(UBYTE speed)
{
	UBYTE	result;

	result = 0;
	switch (speed) {	/* R288F config value */
	case 0xA8:
		result = BPS300_V21;
		break;
	case 0x01:
		result = BPS2400_V27;
		break;
	case 0x02:
		result = BPS4800_V27;
		break;
	case 0x12:
		result = BPS7200_V29;
		break;
	case 0x14:
		result = BPS9600_V29;
		break;
	case 0xB8:
		result = BPS7200_V17;
		break;
	case 0xB4:
		result = BPS9600_V17;
		break;
	case 0xB2:
		result = BPS12000_V17;
		break;
	case 0xB1:
		result = BPS14400_V17;
		break;
	case 0xC1:
		result = BPS2400_V34;
		break;
	case 0xC2:
		result = BPS4800_V34;
		break;
	case 0xC3:
		result = BPS7200_V34;
		break;
	case 0xC4:
		result = BPS9600_V34;
		break;
	case 0xC5:
		result = BPS12000_V34;
		break;
	case 0xC6:
		result = BPS14400_V34;
		break;
	case 0xC7:
		result = BPS16800_V34;
		break;
	case 0xC8:
		result = BPS19200_V34;
		break;
	case 0xC9:
		result = BPS21600_V34;
		break;
	case 0xCA:
		result = BPS24000_V34;
		break;
	case 0xCB:
		result = BPS26400_V34;
		break;
	case 0xCC:
		result = BPS28800_V34;
		break;
	case 0xCD:
		result = BPS31200_V34;
		break;
	case 0xCE:
		result = BPS33600_V34;
		break;
	default:
		break;
	}
	return(result);
}

/*************************************************************************
	module		:[チェッカー用表示関数]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/12]
	author		:[木元修]
*************************************************************************/
UBYTE	tx_line = 0;
UBYTE	rx_line = 0;
UBYTE	test1 = 0;
void UpdateCheckerDisplay(void)
{
	/************************/
	/**	ブザー鳴動			*/
	/************************/
	if (tskno_faxcom_complete != 0xFFFF) { /* 通信・プリント終了 */
		EndBuzzer();
	}
	else {
		StopEndBuzzer();
		test1 = 0;
	}

	/************************/
	/**	LED制御				*/
	/************************/
	if (OPT_CHK_FaxComExecute()) { /* どっか通信中 */
		FaxComLedOn();
	}
	else {
		FaxComLedOff();
	}

	/************************/
	/**	動作状態表示	    */
	/************************/
	if (tskno_faxcom_complete != 0xffff) {	/**通信完了 */
		if (test1 == 0) {
			test1 = 1;
			DisplayBufferHigh[7] = 'O';
			DisplayBufferHigh[8] = 'K';

			DisplayBufferLow[7] = 'O';
			DisplayBufferLow[8] = 'K';

			DisplayStringLow(0, DisplayBufferLow);
			DisplayStringHigh(0, DisplayBufferHigh);

			while (1) {
				wai_tsk(100/10);
				if (!(inpw(0x100) & 0x0020)) {
				break;
				}
			}
			ClearDisplayLow();
			ClearDisplayHigh();
			DisplayStringHigh(0, D2W_TransmitReady);	/* "ﾂｳｼﾝ ﾃﾞｷﾏｽ          " */

			if (tskno_faxcom_complete != 0xffff) {
				del_tsk(&tskno_faxcom_complete);
			}
		}
	}
	else if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_FAXCOM)) {/** 通信エラー */
		if (tx_line == 1) {
			DisplayBufferHigh[7] = 'T';
			DisplayBufferLow[7] = 'R';
		}
		else {
			DisplayBufferHigh[7] = 'R';
			DisplayBufferLow[7] = 'T';
		}

		CMN_BCD_ToASC_StringNum(&DisplayBufferHigh[8], (UBYTE *)&SYS_Opt[1].FaxComResult, 2);
		CMN_BCD_ToASC_StringNum(&DisplayBufferLow[8], (UBYTE *)&SYS_Opt[2].FaxComResult, 2);

		DisplayStringLow(0, DisplayBufferLow);
		DisplayStringHigh(0, DisplayBufferHigh);

		while (1) {
			wai_tsk(100/10);
			if (!(inpw(0x100) & 0x0020)) {
				break;
			}
		}

		ClearDisplayLow();
		ClearDisplayHigh();
		DisplayStringHigh(0, D2W_TransmitReady);	/* "ﾂｳｼﾝ ﾃﾞｷﾏｽ          " */
	}
	else if (MultiLineBusy() != 0xFF) { /* どれか通信中 */
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

		DisplayBufferHigh[0] = '(';
		DisplayBufferHigh[1] = '1';
		DisplayBufferHigh[2] = ')';

		DisplayBufferLow[0] = '(';
		DisplayBufferLow[1] = '2';
		DisplayBufferLow[2] = ')';

		OverWriteDisplayData(1);
		if ((SYS_Opt[1].SYS_FaxComType == SYS_COMMAND_EXECUTE)) {
			tx_line = 1;
			DisplayBufferHigh[4] = 'T';
			DisplayBufferHigh[5] = 'X';

			rx_line = 2;
			DisplayBufferLow[4] = 'R';
			DisplayBufferLow[5] = 'X';
		}
		else {
			tx_line = 2;
			DisplayBufferHigh[4] = 'R';
			DisplayBufferHigh[5] = 'X';

			rx_line = 1;
			DisplayBufferLow[4] = 'T';
			DisplayBufferLow[5] = 'X';

			OverWriteDisplayData(2);
		}

		if (SYS_Display.SYS_FaxCommStage == FCM_TRANSMIT_SET ) {
			CMN_UnsignedIntToASC(&DisplayBufferHigh[11], GetCommunicationSpeed(SYS_Display.TxBaudRate), 5, ' ');
			DisplayBufferHigh[16] = 'b';
			DisplayBufferHigh[17] = 'p';
			DisplayBufferHigh[18] = 's';
		}

		DisplayStringLow(0, DisplayBufferLow);
		DisplayStringHigh(0, DisplayBufferHigh);
	}
	else {
		ClearDisplayLow();
		ClearDisplayHigh();
		DisplayStringHigh(0, D2W_TransmitReady);	/* "ﾂｳｼﾝ ﾃﾞｷﾏｽ          " */
	}
}
#endif	/* (PRO_MULTI_LINE == ENABLE) */

/*************************************************************************
	module		:[アイドルカウンタ表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/12]
	author		:[松隈]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_ANZU_L) /* デバッグモード、アイドルカウンタ表示 1997/11/13 Y.Matsukuma */
void	IdleCountDisplay(UDWORD idle_cnt)
{
	if (IsIdleDisplay == 1){
		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

		FunctionDisplayBufferLow[0] = 'I';
		FunctionDisplayBufferLow[1] = 'D';
		FunctionDisplayBufferLow[2] = 'L';
		FunctionDisplayBufferLow[3] = 'E';
		FunctionDisplayBufferLow[4] = ':';
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[5], idle_cnt, 4, ' ');

		FunctionDisplayBufferLow[10] = '?';
		FunctionDisplayBufferLow[11] = ':';
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[12], MAN_DebugCounter, 8, ' ');

		DisplayStringLow(0, FunctionDisplayBufferLow);
	}
}
#endif

/*************************************************************************
	module		:[復号化原稿プリント中の表示]
	function	:[
		1.暗号化原稿を復号化した原稿の、プリント中の表示を行います。
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/01/20]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_CIPHER == ENABLE)
void DisplayDecipherPrint(void)
{
	switch(SYS_DocumentPrintItem) {	/** 印字原稿の種類を調べる */
	case SYS_MEM_DECIPHER_FILE:		/* 受信暗号化原稿 */
		DisplayStringHigh(0, D2W_DecipherDocument);	/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ｹﾞﾝｺｳ " */
		break;
	case SYS_MEM_TX_DECIPHER_FILE:	/* 暗号化送信原稿 */
		DisplayStringHigh(0, D2W_CommandDocument);	/* "ｿｳｼﾝ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ    " */
		break;
	default:
		break;
	}

 #if (PRO_PRINT_TYPE == LED)
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_WARMUP) {	/* プリンターウォームアップ中の時 */
		DisplayStringLow(0, D2W_Wait);		/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
	}
	else {
		DisplayStringLow(0, D2W_Printing);	/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
	}
 #else
	DisplayStringLow(0, D2W_Printing);		/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
 #endif
}
#endif


#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/14 Y.Matsukuma */
/*************************************************************************
	module		:[ミノルタ用プリンタ詳細エラー表示]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/07/14]
	author		:[松隈]
*************************************************************************/
void	MinoltaPrinterErrorDisplay(void)
{
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	FunctionDisplayBufferLow[0]  = 'E';
	FunctionDisplayBufferLow[1]  = 'r';
	FunctionDisplayBufferLow[2]  = 'r';
	FunctionDisplayBufferLow[3]  = 'o';
	FunctionDisplayBufferLow[4]  = 'r';
	FunctionDisplayBufferLow[5]  = ':';

	if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_FAN_ABNORMAL) {
		FunctionDisplayBufferLow[6]   = 'F';
		FunctionDisplayBufferLow[7]   = 'a';
		FunctionDisplayBufferLow[8]   = 'n';
	}
	if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_RESET_ERROR) {
		FunctionDisplayBufferLow[6]   = 'I';
		FunctionDisplayBufferLow[7]   = 'n';
		FunctionDisplayBufferLow[8]   = 'i';
		FunctionDisplayBufferLow[9]   = 't';
	}
	if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_FUSER_ABNORMAL) {
		FunctionDisplayBufferLow[6]   = 'F';
		FunctionDisplayBufferLow[7]   = 'u';
		FunctionDisplayBufferLow[8]   = 's';
		FunctionDisplayBufferLow[9]   = 'e';
		FunctionDisplayBufferLow[10]  = 'r';
	}
	if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_MOTOR_ABNORMAL) {
		FunctionDisplayBufferLow[6]   = 'M';
		FunctionDisplayBufferLow[7]   = 'o';
		FunctionDisplayBufferLow[8]   = 't';
		FunctionDisplayBufferLow[9]   = 'o';
		FunctionDisplayBufferLow[10]  = 'r';
	}
	if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_LASER_ABNORMAL) {
		FunctionDisplayBufferLow[6]   = 'L';
		FunctionDisplayBufferLow[7]   = 'a';
		FunctionDisplayBufferLow[8]   = 's';
		FunctionDisplayBufferLow[9]   = 'e';
		FunctionDisplayBufferLow[10]  = 'r';
	}
	if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_SERIAL_ERROR) {
		FunctionDisplayBufferLow[6]   = 'S';
		FunctionDisplayBufferLow[7]   = 'e';
		FunctionDisplayBufferLow[8]   = 'r';
		FunctionDisplayBufferLow[9]   = 'i';
		FunctionDisplayBufferLow[10]  = 'a';
		FunctionDisplayBufferLow[11]  = 'l';
	}

	DisplayStringLow(0, FunctionDisplayBufferLow);	/* "Error:*****         " */

}
#endif


/************************************************/
/*	インターネットＦＡＸ用の表示モジュール群	*/
/*												*/
/*	1998/03/13 by Y.Tanimoto					*/
/************************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/*************************************************************************
	module		:[ｲﾝﾀｰﾈｯﾄFAX通信中断表示]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	DisplayINF_Terminate(void)
{
	DisplayStringLow(0 , D2W_INF_Abort);
}

/*************************************************************************
	module		:[ｲﾝﾀｰﾈｯﾄFAX通信新着メール無し表示]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	DisplayINF_NoNewMail(void)
{
	DisplayStringLow(0 , D2W_INF_NoNewMail);
}

/*************************************************************************
	module		:[ｲﾝﾀｰﾈｯﾄFAX動作中の表示]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	DisplayInternetFax(void)
{
	if (SYS_INF_ExecStatus == SYS_INF_STATUS_UPDATE) {
		return;
	}
	/*-----------------*
	 * 上段表示
	 * 実行動作種別表示
	 *-----------------*/
	DisplayINF_ExecKind();
	/*-------------------*
	 * 下段表示
	 * 実行状態表示
 	 *-------------------*/
	DisplayINF_ExecStatus();
}

/*************************************************************************
	module		:[ｲﾝﾀｰﾈｯﾄFAX動作中の上段表示]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	DisplayINF_ExecKind(void)
{
	CMN_MemorySetNULL((UBYTE *)DisplayBufferHigh , OPR_DISPLAY_MAX , ' ');
	if (SYS_INF_ExecStatus == SYS_INF_STATUS_INITIAL) {
		CMN_StringCopy((UBYTE *)DisplayBufferHigh , D2W_InitEngineBoard);
	}
	else {
		CMN_StringCopy((UBYTE *)DisplayBufferHigh , GetMailComKindStrAddress(SYS_INF_MailCommand[SYS_INF_ExecMailCommandNo].Kind));
	}
	DisplayStringHigh(0 , (UBYTE *)DisplayBufferHigh);
}

/*************************************************************************
	module		:[ｲﾝﾀｰﾈｯﾄFAX通信種別取得]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/04]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	*GetMailComKindStrAddress(UBYTE kind)
{
	UBYTE	*wrd_address;

	switch (kind) {
	case SYS_INF_MAIL_TX:
	case SYS_INF_MAIL_TXRX:
		/*[Send Mail           ]*/
		wrd_address = D2W_SendingMail;
		break;
	case SYS_INF_MAIL_MANUAL_RX:
	case SYS_INF_MAIL_AUTO_RX:
	case SYS_INF_MAIL_AUTO_CHK:
		/*[Receive Mail        ]*/
		wrd_address = D2W_ReceivingMail;
		break;
	default:
		wrd_address = D2W_Null;
		break;
	}
	return (wrd_address);
}

/*************************************************************************
	module		:[ｲﾝﾀｰﾈｯﾄFAX通信状況の表示]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	DisplayINF_ExecStatus(void)
{
	switch (SYS_INF_ExecStatus) {
	case SYS_INF_STATUS_CREATING:
		/*[** Creating Email **]*/
		DisplayStringLow(0 , D2W_INF_Creating);
		break;
	case SYS_INF_STATUS_DIALING:
		/*[   ** Dialing **    ]*/
		DisplayStringLow(0 , D2W_INF_Dialing);
		break;
	case SYS_INF_STATUS_CONNECTING:
		/*[  ** Connecting **  ]*/
		DisplayStringLow(0 , D2W_INF_Connecting);
		break;
	case SYS_INF_STATUS_SENDING:
		/*[   ** Sending **    ]*/
		DisplayStringLow(0 , D2W_INF_Sending);
		break;
	case SYS_INF_STATUS_CHECKING:
		/*[   ** Checking **   ]*/
		DisplayStringLow(0 , D2W_INF_Checking);
		break;
	case SYS_INF_STATUS_RECEIVING:
		/*[   ** Receving **   ]*/
		DisplayStringLow(0 , D2W_INF_Receiving);
		break;
	default:
		/*[                    ]*/
		ClearDisplayLow();
		break;
	}
}

UBYTE	CheckReservedMailComExist(void)
{
	UBYTE	cmd_no;
	for (cmd_no = 0; cmd_no < SYS_INF_MAIL_COM_MAX; cmd_no++) {
		if ((SYS_INF_MailCommand[cmd_no].Status == SYS_INF_MAIL_CMD_WAITING)
			|| (SYS_INF_MailCommand[cmd_no].Status == SYS_INF_MAIL_CMD_REDIAL)) {
			return (TRUE);
		}
	}
	return (FALSE);
}

UBYTE	CheckRedialMailComExist(void)
{
	UBYTE	cmd_no;
	for (cmd_no = 0; cmd_no < SYS_INF_MAIL_COM_MAX; cmd_no++) {
		if (SYS_INF_MailCommand[cmd_no].Status == SYS_INF_MAIL_CMD_REDIAL) {
			return (TRUE);
		}
	}
	return (FALSE);
}

#endif	/* by Y.Tanimoto end of "PRO_DIALUP_INTERNET_FAX == ENABLE" */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/18 */
/*************************************************************************
	module		:[ナンバーディスプレイ着信履歴の発信者番号表示]
	function	:[
			一行目左寄りに発信者番号、発信者名、非通知理由を表示します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1999/01/18]
	author		:[藤村春夫]
*************************************************************************/
void	DisplayND_CallerID(void)
{
	UBYTE	point;		/*データ位置*/

	point = 0; /* added by H.Kubo 1998/11/28 */

	/* 最新履歴のポインタセット */
	if (SYB_NumberDisplayJournalPoint == 0) {
		if(SYB_NumberDisplayJournal[SYS_ND_JRNL_MAX - 1].Status == SYS_ND_SET) {	/* 使用済み */
			point = SYS_ND_JRNL_MAX - 1;
		}
	}
	else {
		point = SYB_NumberDisplayJournalPoint - 1;
	}

	/* 発信者番号を表示 */
	if (SYB_NumberDisplayJournal[point].Dial[0] == NULL) { /* 非通知の時 */
		/** 非通知理由を表示 */
		switch (SYB_NumberDisplayJournal[point].Reason) {
		case	'P':	/* ユーザ拒否 『非通知』表示 */
			DisplayStringHigh(0, D2W_ND_NoNotice);
			break;
		case	'O':	/* サービス不可 『表示圏外』表示 */
			DisplayStringHigh(0, D2W_ND_OutOfDisp);
			break;
		case	'C':	/* 公衆電話 『公衆電話』表示 */
			DisplayStringHigh(0, D2W_ND_PublicTel);
			break;
		case	'S':	/* サービス競合 『表示圏内』表示 */
			DisplayStringHigh(0, D2W_ND_OutOfDisp);
			break;
		default:
			ClearDisplayHigh();
			break;
		}
	}
	else {	/* 通知有りの時 */
		if (SYB_NumberDisplayJournal[point].Name[0] == NULL) {	/* 名前登録されていない時 */
			/** 発信者番号を表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopyNumNotNULL(FunctionDisplayBufferHigh,
									 SYB_NumberDisplayJournal[point].Dial, 
									 OPR_DISPLAY_MAX);
			DisplayStringHigh(0, FunctionDisplayBufferHigh);
		}
		else {
			/** 発信者名を表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopyNumNotNULL(FunctionDisplayBufferHigh,
									 SYB_NumberDisplayJournal[point].Name, 
									 OPR_DISPLAY_MAX);
			DisplayStringHigh(0, FunctionDisplayBufferHigh);
		}
	}
}
#endif	/* (PRO_NUMBER_DISPLAY == ENABLE) */
#endif	/* (PRO_ANK_TO_KANJI == DISABLE) */

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)
/*************************************************************************
	module		:[ＡＤＦ原稿設定ワーディングセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/08/01]
	author		:[SMuratec L.Z.W]
*************************************************************************/
void SetDocumentSetWording(UBYTE *set_buf)
{	
	switch (SYB_ModeSw) {
	case SYS_NORMAL:	/** ノーマルの場合				*/
		CMN_StringCopyNum(&set_buf[4], &D2W_PrimaryModeNormal[11], 9);
		break;
	case SYS_FINE:		/** ファインの場合				*/
		CMN_StringCopyNum(&set_buf[4], &D2W_PrimaryModeFine[11], 9);
		break;
	case SYS_SFINE:		/** スーパーファインの場合		*/
		CMN_StringCopyNum(&set_buf[4], &D2W_PrimaryModeSFine[11], 9);
		break;
	case SYS_GRAY16:	/** １６階調					*/
	case SYS_GRAY16_SEP:/** １６階調：像域分離			*/
	case SYS_GRAY64:	/** ６４階調					*/
	case SYS_GRAY64_SEP:/** ６４階調：像域分離			*/
		CMN_StringCopyNum(&set_buf[4], &D2W_PrimaryModeGray[11], 9);
		break;
	default:
		CMN_StringCopyNum(&set_buf[4], &D2W_PrimaryModeNormal[11], 9);
		break;
	}
	
	switch (SYB_DensitySw) {
	case SYS_NORMAL_DENSITY:	/* Normalの時 */
		CMN_StringCopyNum(&set_buf[14], &D2W_PrimaryContrastNormal[13], 6);
		break;
	case SYS_DARK_DENSITY:		/* Darkの時 */
		CMN_StringCopyNum(&set_buf[14], &D2W_PrimaryContrastDark[13], 6);
		break;
	case SYS_LIGHT_DENSITY:		/* Lightの時 */
		CMN_StringCopyNum(&set_buf[14], &D2W_PrimaryContrastLight[13], 6);
		break;
	default:
		CMN_StringCopyNum(&set_buf[14], &D2W_PrimaryContrastNormal[13], 6);
		break;
	}
}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/24 */
void	DisplayKeisatsuSettings(UBYTE *wording)
{
	UBYTE	Display_Settings;

	Display_Settings = SYB_SettingStatus[SETTING_STATUS_31];

	CMN_MemorySetNULL(wording, OPR_DISPLAY_MAX, ' ');

 	if (Display_Settings & SETTING_LINE){
		CMN_StringCopyNumNotNULL(wording, D2W_Kanyu,5);

		if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
			CMN_StringCopyNumNotNULL(&wording[6], &D2W_Issei,4);
		}
		else {
			CMN_StringCopyNumNotNULL(&wording[6], &D2W_Kobetsu,4);
		}
		
		if (CMN_CheckScrambleSwOn() == TRUE) {
			if (Display_Settings & SETTING_SCRAMBLE_KANYU){
				CMN_StringCopyNumNotNULL(&wording[11], D2W_S_Off,5);
			}
			else{
				CMN_StringCopyNumNotNULL(&wording[11], D2W_S_On,5);
				if (Display_Settings & SETTING_SENYOU){
					CMN_StringCopyNumNotNULL(&wording[16], D2W_Senyo,4);
				}
			}
		}
	}
	else{
		CMN_StringCopyNumNotNULL(wording, D2W_Keiden,5);
		if (Display_Settings & SETTING_MODE){
			CMN_StringCopyNumNotNULL(&wording[6], &D2W_Kobetsu,4);
		}
		else{
			CMN_StringCopyNumNotNULL(&wording[6], D2W_Issei,4);
		}

 		if (CMN_CheckScrambleSwOn() == TRUE) {
			if (Display_Settings & SETTING_SCRAMBLE_KEIDEN){
				CMN_StringCopyNumNotNULL(&wording[11], D2W_S_Off,5);
			}
			else{
				CMN_StringCopyNumNotNULL(&wording[11], D2W_S_On,5);

				if (Display_Settings & SETTING_SENYOU){
					CMN_StringCopyNumNotNULL(&wording[16], D2W_Senyo,4);
				}
			}
		}
	}
	
	return;
}

void	DisplayFaxComKeisatsu(UBYTE *wording)
{
	CMN_MemorySetNULL(wording, OPR_DISPLAY_MAX, ' ');
	
 	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
		CMN_StringCopyNumNotNULL(wording, D2W_Kanyu,5);
	
		if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
			CMN_StringCopyNumNotNULL(&wording[6], &D2W_Issei,4);
		}
		else {
			CMN_StringCopyNumNotNULL(&wording[6], &D2W_Kobetsu,4);
		}
	}
	else{
		CMN_StringCopyNumNotNULL(wording, D2W_Keiden,5);
		
		if (FCM_ExecutingS1Info.Protocol == SYS_PROTOCOL_ISSEI) {
			CMN_StringCopyNumNotNULL(&wording[6], &D2W_Issei,4);
		}
		else {
			CMN_StringCopyNumNotNULL(&wording[6], &D2W_Kobetsu,4);
		}
	}
	
 	if (CMN_CheckScrambleSwOn() == TRUE) {
		if (FCM_ExecutingS1Info.Available == FALSE){
			CMN_StringCopyNumNotNULL(&wording[11], D2W_S_Off,5);
		}
		else{
			CMN_StringCopyNumNotNULL(&wording[11], D2W_S_On,5);

			if (FCM_ExecutingS1Info.Method == SYS_S1_SENYO){
				CMN_StringCopyNumNotNULL(&wording[16], D2W_Senyo,4);
			}
		}
	}
	return;
}

void	DisplayTelBell(UBYTE line_flag)
{
 #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
	ClearDisplayLow();
 #endif
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	if (line_flag){
		/*	ヨヒタ゛シチュウ（ケイデン）*/
	DisplayStringLow(0, D2W_KeidenTelBell);
	}
	else{
	/*	ヨヒタ゛シチュウ（カニュウ）*/
	DisplayStringLow(0, D2W_KanyuTelBell);
	}
}
#endif		/* End of (defined (KEISATSU)) */
