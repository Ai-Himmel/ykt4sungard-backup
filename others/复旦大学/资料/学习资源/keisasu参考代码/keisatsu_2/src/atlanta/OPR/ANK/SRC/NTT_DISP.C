/************************************************************************
*	System		: POPLAR_B NTT
*	File Name	: NTT_DISP.C
*	Author		: 渡辺一章
*	Date		: 1999/06/16
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
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* MDM_RxTotalLine, MDM_RxErrorTotalLine */
#else
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"	/* MDM_RxTotalLine, MDM_RxErrorTotalLine */
 #else
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"	/* MDM_RxTotalLine, MDM_RxErrorTotalLine */
 #endif
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
#if (PRO_PC_PRINT == ENABLE)	/* by K.Watanabe 1998/02/23 */
#include	"\src\atlanta\ext_v\dpr_data.h"
#endif
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
 #include	"\src\atlanta\ext_v\bkupram.h"
#endif

#if (PRO_DRUM_PRT_CNT == ENABLE)/* NTT のみ By Y.Suzuki 1998/07/06*/
#include "\src\atlanta\prt\ph3\ext_v\prn_tbl.h"
#endif

/* Prototype
void	UpdateLCD(void);
void	DisplayMachineError(void);
UBYTE	DisplayMachineErrorLow(UBYTE);
void	DisplayMachineError2(void);
UBYTE	DisplayMachineErrorLow2(UBYTE);
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
#if (PRO_PC_PRINT == ENABLE)
void	DisplayPcPrint(void);
#endif
void	DisplayCopyMode(void);
void	DisplayCopyMode0(void);
void	DisplayCopyMode1(void);
void	DisplayCopyMode2(void);
void	DisplayCopyMode3(void);
void	SetCopyModePaperDensity(void);
void	SetCassettePaperSize(UBYTE *);
UBYTE	*SetCassetteCharacter(UBYTE *, UBYTE);
void	SetCopyModeMagnification(UBYTE *);
void	SetDocumentSize(void);
void	DisplayReplacePaperSize(UBYTE);
void	SetPaperSizeWording(UBYTE *, UBYTE, UBYTE);
#if (PRO_MULTI_LINE == ENABLE)
void	OverWriteDisplayData(UBYTE);
UBYTE	BaudRateCompatible(UBYTE);
#endif
void	DisplayDensity(void);
*/

#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/16 */
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
	OPR_DispInfo = OPR_DSP_NO_ERROR;	/* エラー未表示をセット */

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

	/*--------------*/
	/** 完了表示	*/
	/*--------------*/
	if ((tskno_faxcom_complete     != 0xffff)		/** 通信完了 */
	 || (timer_store_copy_complete != 0xff)			/** コピー原稿蓄積完了 <- tskno_store_complete T.Nose 1997/03/11 */
	 || (timer_store_fax_complete  != 0xff)			/** メモリー送信原稿蓄積完了 by K.Watanabe 1997/11/19 */
	 || (tskno_print_complete      != 0xffff)) {	/** 印字完了 */
		DisplayComplete();
		return;
	}

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

	/*------------------*/
	/** 動作状態の表示	*/
	/*------------------*/
	/** 通信時の表示 */
#if (PRO_MULTI_LINE == DISABLE)
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) && (!CHK_ReadyModeCopy())) {
		DisplayFaxCom();
		return;
	}
#else
	if (DisplayMultiLineFaxCom() == OPR_END) {	/* 表示を行った時 */
		return;
	}
#endif

	/** ジャムリカバー中の表示 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_JAM_RECOVER) {
		DisplayJamRecover();
		return;
	}

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

	/** メモリ・プリント時の表示 */
	/* ポプラＢで、ＰＣプリント受信原稿のプリントだけは、コピーモードでも表示します by K.Watanabe 1998/01/28 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)
	 && ((!CHK_ReadyModeCopy()) || (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE))) {
		DisplayImagePrint();
		return;
	}

	/** リスト・プリント時の表示 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT) && (!CHK_ReadyModeCopy())) {
		DisplayListPrint();
		return;
	}

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

#if (PRO_PC_PRINT == ENABLE)
	/** ＰＣプリント原稿受信中の表示 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PC_PRINTDATA_RX) {
		DisplayPcPrint();
		return;
	}
#endif

	/** 原稿繰り込み中の表示（ＡＤＦに原稿をセットした時に、少しだけ繰り込む仕様の時のみ） */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN) {
		/* DisplayDocumentSet(CMN_GetDocumentScanSize()); T.Nose 1997/05/19 */
		DisplayDocumentSet();
		return;
	}

	/** 原稿排出中の表示 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT) && (!CHK_ReadyModeCopy())) {
		DisplayFeedOut();
		return;
	}

#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/21 */
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {
		DisplayWaitAMinutes();	/* "** ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ **" */
		return;
	}
#endif

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

	if (OPR_DispInfo & OPR_DSP_ERROR) {	/* エラー表示時 */
		if (OPR_CopyParamCheck == OPR_NO_PARAM_CHK) {	/* コピー開始，用紙・倍率変更前の時 */
			OPR_CopyParamCheck = OPR_PARAM_CHK;	/* 用紙・倍率確認状態に、確認必要ありをセット */
		}
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
		OPR_DSP_SCAN_DISABLE	:　　〃　　（読み取り不可能エラー）
		OPR_DSP_PRINT_DISABLE	:　　〃　　（プリント不可能エラー）
	]
	common		:[
		SYS_MachineStatus
		FaxComTXorRX_Sign
	]
	condition	:[]
	comment		:[]
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

	/** 手差し記録紙なし */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_MANUAL_PAPER) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayReplacePaperSize(SYS_MANUAL_CASSETTE);
		}
		return(ret);
	}

	/** メモリーオーバー */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_MemoryOverFlow);				/* "ﾒﾓﾘ ｵｰﾊﾞｰです                 " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		return(ret);
	}

 #if (PRO_PC_PRINT == ENABLE)
	/** ＰＣプリントメモリオーバー */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_PC_MEMORY_OVER) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PC_MemoryOverFlow);				/* "PC ﾒﾓﾘ ｵｰﾊﾞｰです              " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		return(ret);
	}
 #endif

	/** 通信エラー */
	if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_FAXCOM) && (!CHK_ReadyModeCopy())) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CommunicationError);			/* "通信ｴﾗｰ                       " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		return(ret);
	}

	/** ハングアップエラー */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) {
		/* 通信エラーとハングアップが同時に発生した場合は、アラームはハングアップブザーだが表示は通信エラー表示になる
		** ハングアップの優先順位をあげると、通信エラーの表示が一瞬ちらつく様に見えるのでこのようにしている
		** （桐／椛と同じです）
		*/
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_HungUpPhone);					/* "受話器が上がっています        " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		return(ret);
	}

	/** ランプ確認 */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_LAMP_ERROR) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CallForService);				/* "ﾗﾝﾌﾟ確認                      " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}

	/** プリンターカバーオープン */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseCloseTopCover);			/* "ﾄｯﾌﾟｶﾊﾞｰを閉じて下さい        " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}

	/** プリンターカバーオープン（ＲＸＩＬ瞬断） by K.Watanabe 1998/03/05 */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_MOMENT_TOP_COVER_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseCloseTopCover);			/* "ﾄｯﾌﾟｶﾊﾞｰを閉じて下さい        " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}

	/** スキャナーカバー */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseCloseScannerCover);		/* "原稿ｶﾊﾞｰを閉じて下さい        " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		return(ret);
	}

	/** 繰り込み不良 */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringHigh(0, D2W_PleaseOpenCloseScanCover);		/* "原稿ｶﾊﾞｰを開閉して            " */
			DisplayStringLow(0, D2W_ResetDocument);					/* "原稿ｾｯﾄをやり直して下さい     " */
			DisplayUsingCondition |= (OPR_LCD_LINE3 | OPR_LCD_LINE4);
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}

	/** 枚数エラー */
	if ((SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_PAGE_ERROR) && (!CHK_ReadyModeCopy())) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CheckDocument);					/* "枚数を確認して下さい          " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		return(ret);
	}

	/** ミラーキャリッジエラー */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_ERROR) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_MirrorCarrigeError);			/* "ﾐﾗｰｷｬﾘｯｼﾞ ｴﾗｰ                 " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_SCAN_DISABLE;	/* エラー表示（読み取り不可能エラー）をセット */
		return(ret);
	}

	/** ジャムカバーオープン（１段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_JAM_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose1stJamCover);		/* "1段ｶｾｯﾄｻｲﾄﾞｶﾊﾞｰを閉じて下さい " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** ジャムカバーオープン（２段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_2JAM_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose2ndJamCover);		/* "2段ｶｾｯﾄｻｲﾄﾞｶﾊﾞｰを閉じて下さい " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** ジャムカバーオープン（３段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_3JAM_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose3rdJamCover);		/* "3段ｶｾｯﾄｻｲﾄﾞｶﾊﾞｰを閉じて下さい " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** 排出ジャム・搬送ジャム */
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_EXIT_JAM)
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_REG_JAM)) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringHigh(0, D2W_PleaseOpenTopCover);			/* "ﾄｯﾌﾟｶﾊﾞｰを開けて              " */
			DisplayStringLow(0, D2W_PleaseRemovePaper);				/* "記録紙を取り除いて下さい      " */
			DisplayUsingCondition |= (OPR_LCD_LINE3 | OPR_LCD_LINE4);
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** 給紙ジャム（手差し） */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_MANUAL_FEED_JAM) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringHigh(0, D2W_RemoveManualPaper);			/* "手差し用紙を取り除いて        " */
			DisplayStringLow(0, D2W_PleaseOpenCloseTopCover);		/* "ﾄｯﾌﾟｶﾊﾞｰを開閉して下さい      " */
			DisplayUsingCondition |= (OPR_LCD_LINE3 | OPR_LCD_LINE4);
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** 給紙ジャム（カセット） */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_MISS_FEED_JAM) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_1ST_FEED_JAM) {
				DisplayStringHigh(0, D2W_PleaseOpen1stJamCover);	/* "ｻｲﾄﾞｶﾊﾞｰ1を開けて             " */
			}
			else if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_2ND_FEED_JAM) {
				DisplayStringHigh(0, D2W_PleaseOpen2ndJamCover);	/* "ｻｲﾄﾞｶﾊﾞｰ2を開けて             " */
			}
			else if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_3RD_FEED_JAM) {
				DisplayStringHigh(0, D2W_PleaseOpen3rdJamCover);	/* "ｻｲﾄﾞｶﾊﾞｰ3を開けて             " */
			}
			DisplayStringLow(0, D2W_PleaseRemovePaper);				/* "記録紙を取り除いて下さい      " */
			DisplayUsingCondition |= (OPR_LCD_LINE3 | OPR_LCD_LINE4);
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** カセットオープン（１段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE1_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose1stCassette);		/* "1段ｶｾｯﾄを閉じて下さい         " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** カセットオープン（２段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE2_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose2ndCassette);		/* "2段ｶｾｯﾄを閉じて下さい         " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** カセットオープン（３段目） */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE3_OPEN) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseClose3rdCassette);		/* "3段ｶｾｯﾄを閉じて下さい         " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** 原稿サイズエラー */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_SIZE_ERROR) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringHigh(0, D2W_CheckPaperSize);				/* "記録紙ｻｲｽﾞを確認して          " */
			DisplayStringLow(0, D2W_PleaseOpenCloseTopCover);		/* "ﾄｯﾌﾟｶﾊﾞｰを開閉して下さい      " */
			DisplayUsingCondition |= (OPR_LCD_LINE3 | OPR_LCD_LINE4);
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** ドラム交換：プリント不可 */
 #if (PRO_DRUM_PRT_CNT == ENABLE)/* NTT のみ By Y.Suzuki 1998/07/06*/
	/* NTT 仕様は、ドラムの寿命がきてもプリントを続ける。表示は、コウカンの表示とする */
	if (SYB_PrinterLifeMonitor.DrumLifeCount > (UDWORD)PRN_DrumPrintStopMax) {
 #else
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_END_DRUM) {
 #endif
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_ReplaceDrum);					/* "ﾄﾞﾗﾑを交換して下さい          " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** トナー交換：プリント不可 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_END_TONER) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseReplaceToner);			/* "ﾄﾅｰを交換して下さい           " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** サービスコールエラー */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_ERROR_ALARM3) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_PleaseCallService);				/* "点検をお受け下さい            " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

 #if (PRO_PC_PRINT == ENABLE)
	/** 指定サイズ記録紙なし（ＰＣプリント自動カセット選択時） */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PC_NO_SAME_DOCUMENT) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			CMN_StringCopyNULL(DisplayBufferHigh, D2W_PC_Print);	/* "PC                  " */
			DisplayBufferHigh[2] = ':';
			SetPaperSizeWording(&DisplayBufferHigh[3], DPR_PCR_NoSameDocumentSize, FALSE);
			DisplayStringHigh(0, DisplayBufferHigh);				/* "PC:A4               " */
			DisplayStringLow(0, D2W_NoSamePaper);					/* "ｼﾃｲﾖｳｼ ｶﾞ ｱﾘﾏｾﾝ     " */
			DisplayUsingCondition |= (OPR_LCD_LINE3 | OPR_LCD_LINE4);
		}
		ret |= OPR_DSP_ERROR_HIGH;	/* エラー表示（上段を使用）をセット */
		return(ret);
	}
 #endif

	/** 記録紙なし（すべてのカセット） */
	if (CMN_CheckPaperExist() == FALSE) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_ReplaceRxPaper);				/* "記録紙を補給して下さい        " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		return(ret);
	}

	/* コピーモードで、コピー中でない時 */
	if ((CHK_ReadyModeCopy())
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_MULTI_COPY)
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_MANUAL_COPY)) {
		/** １段目カセット記録紙なし */
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {
			if (is_error_disp) {	/* エラー表示を行う時 */
				DisplayStringLow(0, D2W_RepRxPaper1stCassette);		/* "1段ｶｾｯﾄ記録紙を補給して下さい " */
				DisplayUsingCondition |= OPR_LCD_LINE4;
			}
			return(ret);
		}

		/** ２段目カセット記録紙なし */
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) {
			if (is_error_disp) {	/* エラー表示を行う時 */
				DisplayStringLow(0, D2W_RepRxPaper2ndCassette);		/* "2段ｶｾｯﾄ記録紙を補給して下さい " */
				DisplayUsingCondition |= OPR_LCD_LINE4;
			}
			return(ret);
		}

		/** ３段目カセット記録紙なし */
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER3) {
			if (is_error_disp) {	/* エラー表示を行う時 */
				DisplayStringLow(0, D2W_RepRxPaper3rdCassette);		/* "3段ｶｾｯﾄ記録紙を補給して下さい " */
				DisplayUsingCondition |= OPR_LCD_LINE4;
			}
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
				DisplayStringLow(0, D2W_ReplaceRxPaper);			/* "記録紙を補給して下さい        " */
				DisplayUsingCondition |= OPR_LCD_LINE4;
			}
			return(ret);
		}
	}

	/** ドラムユニットなし */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_DRUM) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CheckDrum);						/* "ﾄﾞﾗﾑがありません              " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** カートリッジなし */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_CARTRIDGE) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_NoToner);						/* "ﾄﾅｰｶｰﾄﾘｯｼﾞがありません        " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		ret |= OPR_DSP_PRINT_DISABLE;	/* エラー表示（プリント不可能エラー）をセット */
		return(ret);
	}

	/** ダイアルイン番号確認 */
	if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_NO_DIAL_IN_NUMBER) && (!CHK_ReadyModeCopy())) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_NoStoredDialInNumber);			/* "ﾀﾞｲﾔﾙｲﾝ番号がｾｯﾄされていません" */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		return(ret);
	}

	/** エラーの状態ではあるが、表示を書き換えない場合 */
	/* POPLAR_Bでは、記録紙なしのエラーはそのカセットが選択されていないと
	** 表示しないのでこの処理を追加しました
	** 注）この関数をCALLする時点で判断したいが、同時にエラーが立っている時の
	** 　　優先順位の関係があるので難しい
	*/
	ret = OPR_DSP_NO_ERROR;	/* エラー未表示をセット */
	return(ret);
}

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

	if (OPR_DispInfo & OPR_DSP_ERROR) {	/* エラー表示時 */
		if (OPR_CopyParamCheck == OPR_NO_PARAM_CHK) {	/* コピー開始，用紙・倍率変更前の時 */
			OPR_CopyParamCheck = OPR_PARAM_CHK;	/* 用紙・倍率確認状態に、確認必要ありをセット */
		}
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
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NEAREND_DRUM) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CheckDrumLife);					/* "ﾄﾞﾗﾑを準備して下さい          " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		return(ret);
	}

	/** トナーなし：プリント可(トナー残量少ない) */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_FEW_TONER) {
		if (is_error_disp) {	/* エラー表示を行う時 */
			DisplayStringLow(0, D2W_CheckTonerLevel);				/* "ﾄﾅｰが残りわずかです           " */
			DisplayUsingCondition |= OPR_LCD_LINE4;
		}
		return(ret);
	}

	ret = OPR_DSP_NO_ERROR;	/* エラー未表示をセット */
	return(ret);
}

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
		DisplayTransmit();
		break;
	case FCM_CALLED:		/**着信*/
		ClearDisplay0();
		ClearDisplay1();
		DisplayString(20, D2W_Called);	/* " 着信     " */
		DisplayUsingCondition |= (OPR_LCD_LINE1 | OPR_LCD_LINE2);
		break;
	case FCM_RECEIVE:		/**受信*/
		ClearDisplay0();
		ClearDisplay1();
		DisplayString(20, D2W_Receive);	/* " 受信中   " */
		DisplayUsingCondition |= (OPR_LCD_LINE1 | OPR_LCD_LINE2);
		break;
	case FCM_ERROR_LINE:	/** エラーラインの表示 */
	case FCM_RECEIVE_SET:	/** 相手先名の表示 */
		DisplayReceive();
		break;
	case FCM_POLLING:		/** ポーリング */
		ClearDisplay0();
		ClearDisplay1();
		DisplayString(20, D2W_PollingRx);	/* " ﾎﾟｰﾘﾝｸﾞ  " */
		DisplayUsingCondition |= (OPR_LCD_LINE1 | OPR_LCD_LINE2);
		break;
	case FCM_REMOTE_FAX_TRANSMIT:	/** ソウシン */
		ClearDisplay0();
		ClearDisplay1();
		DisplayString(20, D2W_Transmit);	/* " 送信中   " */
		DisplayUsingCondition |= (OPR_LCD_LINE1 | OPR_LCD_LINE2);
		break;
	case FCM_VOICE_CALLED:	/** 会話予約の表示 */ /*相手が会話予約を掛けてきた場合である*/
		DisplayString(20, D2W_CallReservation);	/* " 会話予約 " */
		DisplayUsingCondition |= OPR_LCD_LINE1_RIGHT;
		break;
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
	case FCM_FLASH_ROM_WRITING:
		DisplayString0(D2W_RemoteDiagMode);	/* "ｻｰﾋﾞｽﾓｰﾄﾞ           " */
		DisplayString1(D2W_Wait);			/* "しばらくお待ち下さい" */
		DisplayUsingCondition |= (OPR_LCD_LINE1_LEFT | OPR_LCD_LINE2_LEFT);
		break;
#endif
	default:
		break;
	}
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

#if (PRO_MULTI_LINE == DISABLE)
	/*-----------------------*/
	/* 上段表示				 */
	/*-----------------------*/

	/* 実行きゅうのポインターを獲得 */
	ep = &SYB_ExecQueue[SYS_CurrentExecQueueNo];

	/* 表示バッファクリア*/
	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	if ((SYS_FaxCommStage == FCM_TRANSMIT_SET) && CHK_CommunicationSpeedDisplay()) {
		CMN_UnsignedIntToASC(DisplayBufferHigh, GetCommunicationSpeed(TxBaudRate), 5, ' ');
		DisplayBufferHigh[5] = 'b';
		DisplayBufferHigh[6] = 'p';
		DisplayBufferHigh[7] = 's';
	}
	else {
		if (NonStandardID[0] != NULL) {
			CMN_StringCopyNumNotNULL(DisplayBufferHigh, NonStandardID, OPR_DISPLAY_MAX);
		}
		else if (StandardID[0] != NULL) {
			CMN_StringCopyNumNotNULL(DisplayBufferHigh, StandardID, OPR_DISPLAY_MAX);
		}
		else if ((ep->Status == SYS_EXEC_EXECUTE) || (ep->Status == SYS_EXEC_FORWARD_EXECUTE)){
 #if (PRO_BATCH_TX == ENABLE)
			if (ep->Kind == SYS_BATCH_TX) {
				CMN_StringCopyNumNotNULL(DisplayBufferHigh, SYB_BatchTxFile[ep->Number.Batch].Name, OPR_DISPLAY_MAX);
			}
 #endif
			if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) {
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
					/** 相手先名を表示 */
					CMN_StringCopyNumNotNULL(DisplayBufferHigh,
											 SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Name,
											 OPR_DISPLAY_MAX);
					if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) {	/** ダイアル番号がない場合 */
#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
						/** FAX番号を表示 */
						CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
												SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Dial,
												OPR_DISPLAY_MAX);
#else
						if (ep->Status == SYS_EXEC_FORWARD_EXECUTE) {	/** 転送中の場合 */
							/** 転送先番号を表示 */
							if (SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].SubDialPosition != 0xFF) {
								CMN_BCD_ToASC_StringNum(
									DisplayBufferHigh,
									SYB_SubDial[SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].SubDialPosition],
									OPR_DISPLAY_MAX);
							}
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
					/** 相手先名を表示 */
					CMN_StringCopyNumNotNULL(DisplayBufferHigh,
											 SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Name,
											 OPR_DISPLAY_MAX);
					if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) {	/** ダイアル番号がない場合 */
#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
						/** FAX番号を表示 */
						CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
												SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Dial,
												OPR_DISPLAY_MAX);
#else
						if (ep->Status == SYS_EXEC_FORWARD_EXECUTE) {	/** 転送中の場合 */
							/** 転送先番号を表示 */
							if (SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition != 0xFF) {
								CMN_BCD_ToASC_StringNum(
									DisplayBufferHigh,
									SYB_SubDial[SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition],
									OPR_DISPLAY_MAX);
							}
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
		}
		else { /* 手動送信？？？ */
#if (0)	/* DEBUG */
			CMN_StringCopy(DisplayBufferHigh, D2W_Transmit);	/* " 送信中   " */
#endif
		}
	}
	DisplayString0(DisplayBufferHigh);
	DisplayUsingCondition |= OPR_LCD_LINE1_LEFT;

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
				mode = SYS_GRAY64; /*写真モードやったらなんでもいい */
			}
			else {
				mode = SYS_DocBlock.Dst.Mode;
			}
		}
	}

	/* 原稿サイズ */
	switch (size) {
	case SYS_DOCUMENT_A4_SIZE:
		size_word = D2W_PaperSize_A4;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		size_word = D2W_PaperSize_B4;
		break;
	case SYS_DOCUMENT_A3_SIZE:
		size_word = D2W_PaperSize_A3;
		break;
	default:
		size_word = D2W_PaperSize_B4;
		break;
	}
	CMN_StringCopy(DisplayBufferLow, size_word);

	/* 原稿モード */
	CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(mode), 10);
	DisplayString1(0, DisplayBufferLow);
	DisplayUsingCondition |= OPR_LCD_LINE2_LEFT;

#else
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

	if (SYS_Display.SYS_FaxCommStage == FCM_TRANSMIT_SET && CHK_CommunicationSpeedDisplay()) {
		CMN_UnsignedIntToASC(DisplayBufferHigh, GetCommunicationSpeed(SYS_Display.TxBaudRate), 5, ' ');
		DisplayBufferHigh[5] = 'b';
		DisplayBufferHigh[6] = 'p';
		DisplayBufferHigh[7] = 's';
	}
	else {
		if (SYS_Display.NonStandardID[0] != NULL) {
			CMN_StringCopyNumNotNULL(DisplayBufferHigh, SYS_Display.NonStandardID, OPR_DISPLAY_MAX);
		}
		else if (SYS_Display.StandardID[0] != NULL) {
			CMN_StringCopyNumNotNULL(DisplayBufferHigh, SYS_Display.StandardID, OPR_DISPLAY_MAX);
		}
		else if ((ep->Status == SYS_EXEC_EXECUTE) || (ep->Status == SYS_EXEC_FORWARD_EXECUTE)){
 #if (PRO_BATCH_TX == ENABLE)
			if (ep->Kind == SYS_BATCH_TX) {
				CMN_StringCopyNumNotNULL(DisplayBufferHigh, SYB_BatchTxFile[ep->Number.Batch].Name, OPR_DISPLAY_MAX);
			}
 #endif
			if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) {
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
					/** 相手先名を表示 */
					CMN_StringCopyNumNotNULL(DisplayBufferHigh,
											 SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Name,
											 OPR_DISPLAY_MAX);
					if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) {	/** ダイアル番号がない場合 */
#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
						/** FAX番号を表示 */
						CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
												SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].Dial,
												OPR_DISPLAY_MAX);
#else
						
						if (ep->Status == SYS_EXEC_FORWARD_EXECUTE) {	/** 転送中の場合 */
							/** 転送先番号を表示 */
							if (SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].SubDialPosition != 0xFF) {
								CMN_BCD_ToASC_StringNum(
									DisplayBufferHigh,
									SYB_SubDial[SYB_OnetouchDial[ep->ExecDial.ExecNumber.Onetouch].SubDialPosition],
									OPR_DISPLAY_MAX);
							}
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
					/** 相手先名を表示 */
					CMN_StringCopyNumNotNULL(DisplayBufferHigh,
											 SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Name,
											 OPR_DISPLAY_MAX);
					if (DisplayBufferHigh[0] == ' ' || DisplayBufferHigh[0] == NULL) {	/** ダイアル番号がない場合 */
#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
						/** FAX番号を表示 */
						CMN_BCD_ToASC_StringNum(DisplayBufferHigh,
												SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].Dial,
												OPR_DISPLAY_MAX);
#else
						if (ep->Status == SYS_EXEC_FORWARD_EXECUTE) {	/** 転送中の場合 */
							/** 転送先番号を表示 */
							if (SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition != 0xFF) {
								CMN_BCD_ToASC_StringNum(
									DisplayBufferHigh,
									SYB_SubDial[SYB_SpeedDial[ep->ExecDial.ExecNumber.Speed].SubDialPosition],
									OPR_DISPLAY_MAX);
							}
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
		}
		else { /* 手動送信？？？ */
#if (0)	/* DEBUG */
			CMN_StringCopy(DisplayBufferHigh, D2W_Transmit);	/* " 送信中   " */
#endif
		}

	}
	DisplayString0(DisplayBufferHigh);
	DisplayUsingCondition |= OPR_LCD_LINE1_LEFT;

	/*--------------------------*/
	/* 下段表示					*/
	/*--------------------------*/
	/* 表示バッファクリア*/
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	if (SYS_Display.SYS_FaxCommStage == FCM_TRANSMIT) {	/* フェーズＢ */
		size = SYS_Display.SYS_DocBlock_Src_Size;
		mode = SYS_Display.SYS_DocBlock_Src_Mode;
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
				mode = SYS_GRAY64;	/* 写真モードやったらなんでもいい */
			}
			else {
				mode = SYS_Display.SYS_DocBlock_Dst_Mode;
			}
		}
	}

	/* 原稿サイズ */
	switch (size) {
	case SYS_DOCUMENT_A4_SIZE:
		size_word = D2W_PaperSize_A4;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		size_word = D2W_PaperSize_B4;
		break;
	case SYS_DOCUMENT_A3_SIZE:
		size_word = D2W_PaperSize_A3;
		break;
	default:
		size_word = D2W_PaperSize_B4;
		break;
	}
	CMN_StringCopy(DisplayBufferLow, size_word);

	/* 原稿モード */
	CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(mode), 10);
	DisplayString1(DisplayBufferLow);
	DisplayUsingCondition |= OPR_LCD_LINE2_LEFT;
#endif	/* (PRO_MULTI_LINE == DISABLE) */
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
		if (NonStandardID[0] != NULL) {		/*相手機のＴＴＩあり。(NSSに相手先名がセットされている) */
			CMN_StringCopy(DisplayBufferHigh, NonStandardID);
		}
		else if (StandardID[0] != NULL) {	/*相手機のＩＤあり。(TSIに相手先番号がセットされている) */
			CMN_StringCopy(DisplayBufferHigh, StandardID);
		}
		else {
		}
	}
	if (disp_error_line && MDM_RxTotalLine) {
		CMN_UnsignedIntToASC(&DisplayBufferHigh[9], MDM_RxErrorTotalLine, 5, '0');
		DisplayBufferHigh[14] = 0x2F;	/* ' /' */
		CMN_UnsignedIntToASC(&DisplayBufferHigh[15], MDM_RxTotalLine, 5, '0');
	}

 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
	if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(DisplayBufferHigh, D2W_RemoteDiagMode);	/* "ｻｰﾋﾞｽﾓｰﾄﾞ           " */
	}
 #endif
	DisplayString0(DisplayBufferHigh);
	DisplayUsingCondition |= OPR_LCD_LINE1_LEFT;

	/*------------------------------------*/
	/* 下段表示 						  */
	/*------------------------------------*/
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
	if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
#if (0)	/* DEBUG */
		DisplayString1(D2W_Wait);	/* "しばらくお待ち下さい" */
#endif
	}
	else {
		CMN_StringCopy(DisplayBufferLow, D2W_Receive);	/* " 受信中   " */

		CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(SYS_DocBlock.Src.Mode), 10);
	}
 #else
	CMN_StringCopy(DisplayBufferLow, D2W_Receive);	/* " 受信中   " */

	CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(SYS_DocBlock.Src.Mode), 10);
 #endif

	DisplayString1(DisplayBufferLow);
	DisplayUsingCondition |= OPR_LCD_LINE2_LEFT;

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
	}

	if (disp_error_line && SYS_Display.MDM_RxTotalLine) {
		CMN_UnsignedIntToASC(&DisplayBufferHigh[9], SYS_Display.MDM_RxErrorTotalLine, 5, '0');
		DisplayBufferHigh[14] = 0x2F;  /*  /  */
		CMN_UnsignedIntToASC(&DisplayBufferHigh[15], SYS_Display.MDM_RxTotalLine, 5, '0');
	}
 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
	if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
		CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(DisplayBufferHigh, D2W_RemoteDiagMode);	/* "ｻｰﾋﾞｽﾓｰﾄﾞ           " */
	}
 #endif

	DisplayString0(DisplayBufferHigh);
	DisplayUsingCondition |= OPR_LCD_LINE1_LEFT;

	/*------------------------------------*/
	/* 下段表示 						  */
	/*------------------------------------*/
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
	if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
		CMN_StringCopy(DisplayBufferLow, D2W_Wait);	/* "しばらくお待ち下さい" */
	}
	else {
		CMN_StringCopy(DisplayBufferLow, D2W_Receive);	/* " 受信中   " */

		CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(SYS_Display.SYS_DocBlock_Src_Mode), 10);
	}
 #else
	CMN_StringCopy(DisplayBufferLow, D2W_Receive);	/* " 受信中   " */

	CMN_StringCopyNumNotNULL(&DisplayBufferLow[10], GetCommunicationResolution(SYS_Display.SYS_DocBlock_Src_Mode), 10);
 #endif

	DisplayString1(DisplayBufferLow);
	DisplayUsingCondition |= OPR_LCD_LINE2_LEFT;
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
	case SYS_HFINE:
	case SYS_EFINE:
	case SYS_E_HFINE:
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
		return (D2W_DocSFine);
	case SYS_GRAY16:
	case SYS_GRAY16_SEP:
	case SYS_GRAY64:
	case SYS_GRAY64_SEP:
		return (D2W_DocGray);
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
#if (PRO_MULTI_LINE == DISABLE)
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
	DisplayStringLow(0, D2W_Wait);	/* "しばらくお待ち下さい" */
	DisplayUsingCondition |= OPR_LCD_LINE4_LEFT;
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
		DisplayBufferLow[4] = OPR_FONT_YEAR;										/* 年 */
		CMN_UnsignedIntToASC(&DisplayBufferLow[5], (UWORD)month, 2, ' ');
		DisplayBufferLow[7] = OPR_FONT_MONTH;										/* 月 */
		CMN_UnsignedIntToASC(&DisplayBufferLow[8], (UWORD)day, 2, ' ');
		DisplayBufferLow[10] = OPR_FONT_DAY;										/* 日 */
		DisplayBufferLow[11] = 0x28;										/* ( */
		DisplayBufferLow[12] = (UBYTE)(CurrentTimeInBCD.Week - 1 + OPR_FONT_DAY);	/* 曜日 */
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

	DisplayString1(DisplayBufferLow);
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
	/* ミラーキャリッジ輸送モードの時 */
	if (SYB_ScannerTransportMode == TRUE) {
		DisplayString0(D2W_ScannerTransportReady);	/* "ﾐﾗｰｷｬﾘｯｼﾞ輸送ﾓｰﾄﾞ   " */
		if (!(DisplayUsingCondition & OPR_LCD_LINE2_LEFT)) {	/* ＬＣＤ２段目未表示の時 */
			ClearString1();
		}
		if (!(DisplayUsingCondition & OPR_LCD_LINE3_LEFT)) {	/* ＬＣＤ３段目未表示の時 */
			ClearString2();
		}
		if (!(DisplayUsingCondition & OPR_LCD_LINE4_LEFT)) {	/* ＬＣＤ４段目未表示の時 */
			ClearString3();
		}
/*		ClearString3();	/* メモリ残表示を消します */
		return;
	}

	/*--------------------*/
	/* ＬＣＤ１段目の表示 */
	/*--------------------*/
	if (!(DisplayUsingCondition & OPR_LCD_LINE1_LEFT)) {	/* ＬＣＤ１段目が未使用の時 */
		if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
			DisplayCopyMode0();	/* 部数表示 */
		}
		else {						/* ファクスモードの時 */
			DisplayRxMode();	/* 受信モード表示 */
		}
	}

	if (!(DisplayUsingCondition & OPR_LCD_LINE1_RIGHT)) {	/* 状態未表示の時 */
		if ((CheckReservedCommandExist() == TRUE)
		 || (CheckReservedBatchExist() == TRUE)
		 || (CheckReservedContPollingExist() == TRUE)) {	/* 実行待ちのコマンドがある時 */
			if (CheckRedialQueueExist() == TRUE) {	/** コマンドがリダイアル待ちの時 */
				DisplayString(20, D2W_AutoRedial);	/* " ﾘﾀﾞｲﾔﾙ待 " */
			}
			else {									/** コマンドが予約中の時 */
				DisplayString(20, D2W_Reserving);	/* " 予約中   " */
			}
		}
	}

	/*--------------------*/
	/* ＬＣＤ２段目の表示 */
	/*--------------------*/
	if (!(DisplayUsingCondition & OPR_LCD_LINE2_LEFT)) {	/* ＬＣＤ２段目が未使用の時 */
		if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
			DisplayCopyMode1();	/* カセット段数・記録紙サイズ */
		}
		else {						/* ファクスモードの時 */
			DisplayCalender();	/* カレンダー表示 */
		}
	}

	/*--------------------*/
	/* ＬＣＤ３段目の表示 */
	/*--------------------*/
	if (!(DisplayUsingCondition & (OPR_LCD_LINE3_LEFT | OPR_LCD_LINE4_LEFT))) {	/* ＬＣＤ３段目かつ４段目が未使用の時 */
#if (PRO_NOT_AUTO_RX_DISP == ENABLE)
		if (CMN_CheckAutoCalledEnable() == FALSE) {	/* 自動受信不可能な時(ﾒﾓﾘ残量64K以下 or 代行受信管理ﾃｰﾌﾞﾙに空きなし) */
			DisplayString2(D2W_MemoryFull);		/* "ﾒﾓﾘが一杯です                 " */
			DisplayString3(D2W_NotAutoReceive);	/* "自動受信できません            " */
			return;
		}
#endif

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
		if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {	/* フラッシュＲＯＭデータ受信中 */
			if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
				DisplayString2(D2W_RemoteDiagMode);	/* "ｻｰﾋﾞｽﾓｰﾄﾞ           " */
				DisplayString3(D2W_Wait);			/* "しばらくお待ち下さい" */
				return;
			}
		}
#endif
	}

	if (!(DisplayUsingCondition & OPR_LCD_LINE3_LEFT)) {	/* ＬＣＤ３段目が未使用の時 */
		if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
			DisplayCopyMode2();
		}
		else {						/* ファクスモードの時 */
			DisplayString2(D2W_TransmitReady);	/* "通信できます        " */
		}
	}

	/*--------------------*/
	/* ＬＣＤ４段目の表示 */
	/*--------------------*/
	if (!(DisplayUsingCondition & OPR_LCD_LINE4_LEFT)) {	/* ＬＣＤ４段目が未使用の時 */
		if (!CHK_ReadyModeCopy() && CMN_CheckDocumentOnFeeder()) {	/* ファクスモードでＡＤＦに原稿がセットされている時 */
			DisplayDocumentSet();
		}
		else {
			DisplayDensity();	/* 濃度表示 */
		}
	}

#if (0)	/* DEBUG */
/*#if (PRO_MULTI_LINE == ENABLE)*/
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
		wording = D2W_DialInReady;
		break;
#endif
	default:
		wording = NULL;
		break;
	}

	DisplayString0(wording);
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

	/*------------*/
	/* 下段の表示 */
	/*------------*/
	if (is_dsp_low_enable) {	/* 下段表示可能な時 */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_WARMUP) {	/* プリンターウォームアップ中の時 */
			DisplayStringLow(0, D2W_Wait);		/* "しばらくお待ち下さい" */
		}
		else {
			DisplayStringLow(0, D2W_Printing);	/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
		}
	}
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
	DisplayStringLow(0, D2W_Wait);	/* "しばらくお待ち下さい" */
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
	ClearDisplayHigh();
	DisplayStringLow(0, D2W_Wait);	/* "しばらくお待ち下さい" */
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
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 1996/09/30 by K.Watanabe */
		case SYS_MEM_PC_RX_FILE:		/* ＰＣプリントファイル */
			DisplayStringHigh(0, D2W_PC_Print);				/* "PC                  " */
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
		default:
			break;
		}
		break;
	}

	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_WARMUP) {	/* プリンターウォームアップ中の時 */
		DisplayStringLow(0, D2W_Wait);		/* "しばらくお待ち下さい" */
	}
	else {
		DisplayStringLow(0, D2W_Printing);	/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
	}
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
		DisplayStringHigh(0, D2W_PrintJournal);	/* "ﾂｳｼﾝｷﾛｸ ﾌﾟﾘﾝﾄ       " */
		break;
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
	case LST_CONSUMERORDER_SHEET:		/* 消耗品発注票										*/
		DisplayStringHigh(0, D2W_SF_OrderForm);	/* "ﾊｯﾁｭｳﾖｳｼ            " */
		break;
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
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_WARMUP) {	/* プリンターウォームアップ中の時 */
		DisplayStringLow(0, D2W_Wait);		/* "しばらくお待ち下さい" */
	}
	else {
		DisplayStringLow(0, D2W_Printing);	/* "   ** ﾌﾟﾘﾝﾄﾁｭｳ **   " */
	}
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
		DisplayDocumentSet();
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
		DisplayStoreMemTxDocument();
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
#if (PRO_F_CODE == ENABLE)
	case SYS_MEM_SUB_BULLETIN_FILE:	/** 掲示板蓄積原稿（サブアドレス通信原稿） */
		CMN_StringCopy(DisplayBufferHigh, D2W_StoreFcodeDocument);	/* "ｹﾞﾝｺｳ ﾁｸｾｷ   ﾌｧｲﾙ:  " */
		CMN_UnsignedIntToASC(&DisplayBufferHigh[18], SYS_DocumentStoreNo, 2, ' ');
		DisplayStringHigh(0, DisplayBufferHigh);					/* "ｹﾞﾝｺｳ ﾁｸｾｷ   ﾌｧｲﾙ:99" */
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

	DisplayStringHigh(0, DisplayBufferHigh);
}

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

	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

#if (0)	/* DEBUG */
** 	/* メモリー残量セット */
** 	if (CheckCopyDocStore()) {	/* コピー原稿の蓄積中の時 */
** 		CMN_StringCopy(DisplayBufferLow, D2W_MemoryAreaLong);	/* "             ﾒﾓﾘ   %" */
** 	}
** 	else {
** 		CMN_StringCopy(DisplayBufferLow, D2W_MemoryAreaShort);	/* "             ﾒﾓﾘ   %" */
** 	}
** 	mem_area = (UWORD)MEM_CountEmptyBlockRate();
** 	CMN_UnsignedIntToASC(&DisplayBufferLow[16], mem_area, 3, ' ');
#endif

	/* 次原稿のあり／なし */
	if (SYS_NextBookDocument == TRUE) {
		CMN_StringCopy(&DisplayBufferLow[5], D2W_NextDocument_Ari);		/* "次原稿あり     " */
	}
	else {
		CMN_StringCopy(&DisplayBufferLow[5], D2W_NextDocument_Nashi);	/* "次原稿なし     " */
	}

	/* 原稿サイズワーディングセット */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {	/* 原稿蓄積中の時 */
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
	}
	else {															/* 原稿セット・繰り込み・排出中の時 */
		SetDocumentScanSizeWording(DisplayBufferLow, CMN_GetDocumentScanSize());
	}

	/* 原稿サイズ・ブック次原稿のあり／なし・メモリー残量表示 */
	DisplayStringLow(0, DisplayBufferLow);
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
		wording_ptr = D2W_PaperSize_A4;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		wording_ptr = D2W_PaperSize_B4;
		break;
	case SYS_DOCUMENT_A3_SIZE:
		wording_ptr = D2W_PaperSize_A3;
		break;
	default:
		wording_ptr = D2W_PaperSize_A4;
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
		if (FaxComTXorRX_Sign == TX_COM_MODE) { /** 送信終了 */
			DisplayStringLow(0, D2W_TransmitComplete);	/* " **  ｿｳｼﾝ ｶﾝﾘｮｳ  ** " */
		}
		else if (FaxComTXorRX_Sign == RX_COM_MODE) { /** 受信終了 */
			DisplayStringLow(0, D2W_ReceiveComplete);	/* " **  ｼﾞｭｼﾝｶﾝﾘｮｳ  ** " */
		}
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
	if ((timer_store_copy_complete != 0xFF) && (CHK_ReadyModeCopy())) {
		DisplayStringLow(0, D2W_StoreComplete);	/* " **  ﾖﾐﾄﾘ ｶﾝﾘｮｳ  ** " */
		return;
	}

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
		return;
	}
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
	DisplayStringHigh(0, D2W_TransmitReady);	/* "ﾂｳｼﾝ ﾃﾞｷﾏｽ          " */
}

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
/*	DisplayCopyModeHigh();*/

	/** 下段の表示 */
/*	DisplayCopyModeLow();*/

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
	module		:[コピーモード時の待機表示（１段目）]
	function	:[
		1.コピーモード・部数の表示を行います
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
void DisplayCopyMode0(void)
{
	/* コピー不可能（読み取り不可能・プリント不可能）なエラー表示をしている時 */
	if (OPR_DispInfo & (OPR_DSP_SCAN_DISABLE | OPR_DSP_PRINT_DISABLE)) {
		CMN_StringCopy(DisplayBuffer0, D2W_CopyImpossibleReady);		/* "             部数:  " */
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
			CMN_StringCopy(DisplayBuffer0, D2W_CopyImpossibleReady);	/* "             部数:  " */
		}
		/* コピー可能な時 */
		else {
			CMN_StringCopy(DisplayBuffer0, D2W_CopyReady);				/* "ｺﾋﾟｰできます 部数:  " */
		}
	}

	/* コピー部数のセット */
	CMN_UnsignedIntToASC(&DisplayBuffer0[18], (UWORD)OPR_CopyData.ReserveNumber, OPR_COPY_NUMBER_FIGURE_MAX, ' ');

	DisplayString0(DisplayBuffer0);
}

/*************************************************************************
	module		:[コピーモード時の待機表示（２段目）]
	function	:[
		1.カセット段数・記録紙サイズを表示します
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
void DisplayCopyMode1(void)
{
	/** 表示用バッファの初期化 */
	CMN_MemorySetNULL(DisplayBuffer1, OPR_DISPLAY_MAX, ' ');

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
	module		:[コピーモード時の待機表示（１段目）]
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
void DisplayCopyMode2(void)
{
	/* 倍率を直接入力中の時 */
	if (OPR_NumberKeyInputMode == OPR_COPY_MAGNIFI_INPUT_MODE) {
		DisplayString2(D2W_InputCopyMagnifi);						/* "倍率入力(50-200)    " */
	}
	/* 倍率が適正範囲外の時
	** 注）０％は、設定はできないので除きます（ＡＤＦコピーでの、コピー不可能エラーの意味です）
	*/
	else if ((CheckCopyMagnifiLimit(OPR_CopyData.Reduction) != OPR_MAGNIFI_OK) && (OPR_CopyData.Reduction != 0)) {
		FlashDisplayStringHigh(D2W_CopyMagnifiError);					/* "50-200%をどうぞ     " */
	}
	/* コピー不可能（読み取り不可能・プリント不可能）なエラー表示をしている時 */
	else if (OPR_DispInfo & (OPR_DSP_SCAN_DISABLE | OPR_DSP_PRINT_DISABLE)) {
		ClearString0();												/* 上段クリア */
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
			CMN_StringCopy(DisplayBufferHigh, D2W_CopyImpossibleReady);	/* "             部数:  " */
		}
		/* コピー可能な時 */
		else {
			CMN_StringCopy(DisplayBufferHigh, D2W_CopyReady);			/* "ｺﾋﾟｰできます 部数:  " */
		}

		/* コピー部数のセット */
		CMN_UnsignedIntToASC(&DisplayBufferHigh[18], (UWORD)OPR_CopyData.ReserveNumber, OPR_COPY_NUMBER_FIGURE_MAX, ' ');

		DisplayString0(DisplayBufferHigh);
	}
}

/*************************************************************************
	module		:[コピーモード時の待機表示（４段目）]
	function	:[
		1.濃度表示
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/06/18]
	author		:[渡辺一章]
*************************************************************************/
void DisplayCopyMode3(void)
{
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

	buf_address = CMN_StringCopy(DisplayBufferHigh, D2W_ManualCassette);	/* "手差し: " */
 #if (PRO_PC_PRINT == ENABLE)
	if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) {	/* ＰＣプリントの時 */
		/* ＰＣで指定された、手差しの記録紙サイズのワーディングをセットします */
		SetPaperSizeWording(buf_address, PRN_PC_Size, FALSE);
	}
	else {												/* 手差しコピーの時 */
		/* 手差しの記録紙サイズのワーディングをセットします */
		SetPaperSizeWording(buf_address, SYB_ManualCopyFile.Size, SYB_ManualCopyFile.OHPMode);
	}
 #else
	/* 手差しの記録紙サイズのワーディングをセットします */
	SetPaperSizeWording(buf_address, SYB_ManualCopyFile.Size, SYB_ManualCopyFile.OHPMode);
 #endif

	DisplayString0(DisplayBufferHigh);		/* "手差し:A4           " */
	DisplayString1(D2W_ReplaceManualPaper);	/* "記録紙をどうぞ      " */
	DisplayUsingCondition |= (OPR_LCD_LINE1_LEFT | OPR_LCD_LINE2_LEFT);
}

/*************************************************************************
	module		:[紙サイズワーディングセット]
	function	:[
		1.指定のバッファに紙サイズのワーディングをセットします
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
void SetPaperSizeWording(UBYTE *dsp_buffer, UBYTE paper_size, UBYTE ohp_mode)
{
	/* 紙なし又は、カセットなしの時 */
	if ((paper_size == SYS_NO_PAPER) || (paper_size == SYS_NO_CASSETTE)) {
		CMN_StringCopy(dsp_buffer, D2W_PaperSize_None);		/* "なし " */
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
#endif	/* (PRO_MULTI_LINE == ENABLE) */

/*************************************************************************
	module		:[濃度表示]
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
	date		:[1999/06/22]
	author		:[渡辺一章]
*************************************************************************/
void DisplayDensity(void)
{
	UBYTE	density_switch;

	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		density_switch = SYB_CopyDensitySw;
	}
	else {						/* ファクスモードの時 */
		density_switch = SYB_DensitySw;
	}

	/* 濃度表示用ワーディングのセット */
	CMN_StringCopyNULL(DisplayBuffer3, D2W_ContrastLightDark);	/* "濃度:薄く       濃く" */

	/* 現在の設定値以外のフォントをセット */
	DisplayBuffer3[9]  = OPR_FONT_DEN_LEFT;
	DisplayBuffer3[10] = OPR_FONT_DEN_TEN;
	DisplayBuffer3[11] = OPR_FONT_DEN_TEN;
	DisplayBuffer3[12] = OPR_FONT_DEN_NOR;
	DisplayBuffer3[13] = OPR_FONT_DEN_TEN;
	DisplayBuffer3[14] = OPR_FONT_DEN_TEN;
	DisplayBuffer3[15] = OPR_FONT_DEN_RIGHT;

	/* 現在設定されている濃度をセットします */
	switch (density_switch) {
	case SYS_LIGHT_DENSITY:			/* 薄く */
		DisplayBuffer3[10] = OPR_FONT_DEN_SET;
		break;
	case SYS_LIGHT_NORMAL_DENSITY:	/* やや薄く */
		DisplayBuffer3[11] = OPR_FONT_DEN_SET;
		break;
	case SYS_NORMAL_DENSITY:		/* 普通 */
		DisplayBuffer3[12] = OPR_FONT_DEN_SET;
		break;
	case SYS_DARK_NORMAL_DENSITY:	/* やや濃く */
		DisplayBuffer3[13] = OPR_FONT_DEN_SET;
		break;
	case SYS_DARK_DENSITY:			/* 濃く */
		DisplayBuffer3[14] = OPR_FONT_DEN_SET;
		break;
	default:
		break;
	}

	DisplayString3(DisplayBuffer3);
}
#endif	/* (PRO_ANK_TO_KANJI == ENABLE) */
