/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_PRM.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 機器設定オペレーション
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\param.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\syslocal.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mntsw_e.h"		/* 97/10/17 T.Fukumoto */
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\mon_pro.h"		/* 97/07/03 Add by M.Kuwahara */
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"		/* 1997/06/25 Y.Matsukuma */
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"	/* 97/07/03 Add by M.Kuwahara */
#endif

#if (PRO_PRINT_TYPE == LASER)
#include	"\src\atlanta\prt\sp322\define\prn_pro.h"
/*#include	"\src\atlanta\prt\sp322\ext_v\prn_tbl.h"	/* 追加されたらﾒｲｸﾌｧｲﾙの推論規則にも追加（現時点では存在していません） */
extern CONST UWORD	PRN_DrumPrintMax;
#endif

#if (PRO_PRINT_TYPE == LED)
#include	"\src\atlanta\prt\ph3\define\prn_pro.h"
#include	"\src\atlanta\prt\ph3\ext_v\prn_tbl.h"
#endif

#if (PRO_PC_PRINT == ENABLE)
#include	"\src\atlanta\ext_v\dpr_data.h"
#endif

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\sys_opt.h"
#include	"\src\atlanta\define\man_pro.h"
#endif

#if defined	(KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/16 */
#include	"\src\memsw\define\mem_sw_a.h"
#include	"\src\memsw\define\mem_sw_g.h"
#include	"\src\atlanta\hinoki\define\m_param.h"
#endif		/* End of (defined (KEISATSU)) */

/* Protype
void	SetScanParameters(void);
UBYTE	CheckGrayModeSetting(void);
void	SetRxPrintParameters(void);
#if (PRO_COPY_FAX_MODE == DISABLE)	/ by K.Watanabe 1998/08/18 /
void	SetCopyParameters(void);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
void	SetPaperSize(void);
#if (PRO_PC_PRINT == ENABLE)
void 	Set_PCR_PaperSize(void);
#endif
#endif
void	SetCopyProtect(void);
void	SetDialingPause(void);
void	SetNumberOfRings(void);
void	SetRedial(void);
void	SetECMMode(void);
void	SetPasscode(void);
void	SetClosedNetwork(void);
void	SetSecurityTx(void);
void	SetBlockJunkFax(void);
void	SetRemoteDiagnostic(void);
void	SetMemoryTransmission(void);
void	SetSilentOperation(void);
void	SetProtectPasscode(void);
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
void	SaveProtectPasscode();
#endif
void	AllProtectClear(void);
UBYTE	EraseProtectPasscodeEnable(void);
void	SetOperationProtect(void);
void	SetPINAccessMode(void);
void	SetRingMaster(void);
void	SetStamp(void);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/ by K.Watanabe 1998/08/18 /
void	ResetDrumLife(void);
#endif
#if defined(GBR)
void	SetRxAlarm(void);
#endif
void	FixedNumberInputRangeSet(UWORD, UWORD, UBYTE, UBYTE *);
#if (PRO_DIALIN == ENABLE)
void	SetDialIn(void);
UBYTE	InputDialInNumber(UBYTE *, UBYTE *);
#endif
UBYTE	BlockJunkCommandOperation(void);
UBYTE	SetJunkMailDial(void);
UBYTE	SetJunkMailCodeSelect(UBYTE);
void	SettingJunkMailDial(void);
void	JunkMailSelectDisplay(void);
UBYTE	GetJunkMailDialCount(void);
void	Del_BlockJunkDuplication(UBYTE *, UBYTE);
UBYTE	PrintBlockJunkList(void);
#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
void	SetHoldMelody(void);
#endif
#if (PRO_REMOTE_RX == ENABLE)
void	SetRemoteReceive(void);
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
void	PrintSettingList(void);
#endif
*/

/*************************************************************************
	module		:[読み取りパラメーターセット]
	function	:[
		1.以下の項目のセットを行う。
		, 優先モード
		，優先濃度
		，ハーフトーンセット
		，原稿読み取り幅
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J01]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetScanParameters(void)
{
	/*--------------------*/
	/** 優先モードセット  */
	/*--------------------*/
	if (EnterSettingStatus(D2W_SelectPrimaryMode,
						   D2W_PrimaryModeNormal,
						   4,
						   SETTING_STATUS_1,
						   OPR_PRIMARY_MODE,
						   (PRIMARY_MODE_FINE | PRIMARY_MODE_SFINE)) == NG) {
		return;
	}

#if (0)	/* 64階調固定となったので削除 1996/04/24 Eguchi */
//	/* 写真にセットされた場合、ハーフトーンモードの設定を行う */
//	if (CheckGrayModeSetting() == TRUE) {
//		/*-----------------------------*/
//		/** ハーフトーンモードセット   */
//		/*-----------------------------*/
//		if (EnterSettingStatus(D2W_Null,
//							   D2W_Gray16,
//							   2,
//							   SETTING_STATUS_1,
//							   OPR_VALID_CHECK_NOT_NEED,
//							   HALFTONE_MODE_64) == NG) {
//			return;
//		}
//	}
#endif
	CMN_ResetPrimaryMode();
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
	ModeLedOn();
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	/*-----------------*/
	/** 優先濃度セット */
	/*-----------------*/
	if (EnterSettingStatus(D2W_SelectPrimaryContrast,	/* "ﾖﾐﾄﾘ ﾉｳﾄﾞ   :       " */
						   D2W_PrimaryContrastLight,	/* "             ｳｽｸ    " */
						   5,
						   SETTING_STATUS_26,
						   OPR_PRIMARY_CONTRAST,
						   (PRIMARY_CONTRAST_LIGHT  | PRIMARY_CONTRAST_LIGHT_NORMAL |
							PRIMARY_CONTRAST_NORMAL | PRIMARY_CONTRAST_DARK_NORMAL  |
							PRIMARY_CONTRAST_DARK)) == NG) {
		return;
	}
	CMN_ResetPrimaryContrast();
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
	DensityLedOn();
 #endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
#endif

	/*------------------------*/
	/** 原稿読み取り幅セット  */
	/*------------------------*/
#if (PRO_SCAN_WIDTH == A4WIDTH)
	/** 完了 */
	ChildDisplaySetCompleted(D2W_SetScanParameters);
#else
	if (EnterSettingStatus(D2W_SelectScanWidth,
						   D2W_ScanA4,
						   3,
						   SETTING_STATUS_1,
						   OPR_SCAN_WITDH,
						   (SCANNING_WIDTH_B4 | SCANNING_WIDTH_A3)) == NG) {
		return;
	}

	/** 完了 */
	ChildDisplaySetCompleted(D2W_SetScanParameters);
#endif
}

/*************************************************************************
	module		:[優先モードで写真がセットされたかチェックする]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
UBYTE CheckGrayModeSetting(void)
{
	if ((SYB_SettingStatus[SETTING_STATUS_1] & PRIMARY_MODE_GRAY) == PRIMARY_MODE_GRAY) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[プリントパラメータセット]
	function	:[
		1.以下の項目をセットする。
		. ページ合成プリント設定
		，受信縮小率
		，受信原稿プリント閾値
		，（回転受信用しきい値）
		, ページ合成プリント設定
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J02]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetRxPrintParameters(void)
{
	UWORD	margin;

	/*---------------------*/
	/** 受信縮小率のセット */
	/*---------------------*/
	if (EnterSettingStatus(D2W_SelectReceiveReduction,	/* "ｼｭｸｼｮｳﾘﾂ:           " */
						   D2W_AutoReduction,			/* "              ｼﾞﾄﾞｳ " */
						   6,
						   SETTING_STATUS_4,
						   OPR_RX_REDUCTION,
						   (RX_REDUCTION_1 | RX_REDUCTION_2 |
							RX_REDUCTION_3 | RX_REDUCTION_4 |
							RX_REDUCTION_5 | RX_REDUCTION_6 | RX_REDUCTION_7)) == NG) {
		return;
	}

	/*---------------*/
	/** 閾値のセット *//*もし128mm以上の値がセット可能になるのであれば修正せないかん*/
	/*---------------*/
	margin = FixedLengthNumberInput((UWORD)SYB_SettingStatus[RX_MARGIN], 0, 85, (UBYTE)18, D2W_InputThresholdValue0_85);
																							/* "ｼｷｲﾁ  (0-85mm):     " */
	if (margin == 0xFFFF) {	/* 途中でストップキー */
		return;
	}
	/* 閾値をセッティングステータスにセット */
	SYB_SettingStatus[RX_MARGIN] = (UBYTE)margin;

#if (PRO_ROTATE == ENABLE)
	/*-----------------------------*/
	/** 回転受信用しきい値のセット */
	/*-----------------------------*/
	if (DPR_CheckRotateBoardExist() == TRUE) {	/* 回転ボードが接続されている時 */
		DisplayStringHigh(0, D2W_SetRotateMargin);	/* "ｶｲﾃﾝ ｼﾞｭｼﾝ          " */
		margin = FixedLengthNumberInput((UWORD)SYB_SettingStatus[ROTATE_RX_MARGIN],
										0,
										85,
										(UBYTE)18,
										D2W_InputThresholdValue0_85);	/* "ｼｷｲﾁ  (0-85mm):     " */
		if (margin == 0xFFFF) {	/* 途中でストップキー */
			return;
		}
		/* 閾値をセッティングステータスにセット */
		SYB_SettingStatus[ROTATE_RX_MARGIN] = (UBYTE)margin;
	}
#endif

#if !defined(STOCKHM2)		/* Modify by SMuratec K.W.Q 2004/05/27 */
	/*---------------------*/
	/** ページ合成のセット */
	/*---------------------*/
	if (EnterSettingStatus(D2W_SelectPageCompound,
						   D2W_Off3,
						   2,
						   SETTING_STATUS_4,
						   OPR_VALID_CHECK_NOT_NEED,
						   PRINTER_NO_FORM_FEED) == NG) {
		return;
	}
#endif			/* End of (!defined (STOCKHM2)) */

	/* 完了 */
	ChildDisplaySetCompleted(D2W_SetPrintParameters);
}

/*************************************************************************
	module		:[コピーパラメーターセット]
	function	:[
		1.以下の項目をセットする。
		，ソーティングコピーセット --> 削除。1996/05/24　TBD
		，コピー縮小率セット
		，コピー閾値セット
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J03]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
#if (PRO_COPY_FAX_MODE == DISABLE)
void SetCopyParameters(void)
{
	UWORD	margin;

	margin = 0;

 #if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* POPLAR_L はここでコピー禁止をセット 97/11/13 T.Fukumoto */
	/*-------------------------------*/
	/** コピー禁止					 */
	/*-------------------------------*/
	if (EnterSettingStatus(D2W_SelectCopyProtect,	/* "ｺﾋﾟｰｷﾝｼ        :    " */
						   D2W_Off2,				/* "                OFF " */
						   2,
						   SETTING_STATUS_6,
						   OPR_VALID_CHECK_NOT_NEED,
						   COPY_PROTECT_ON) == NG) {
		return;
	}

	/* POPLAR_L はソート／ノンソート切り替えあり 97/11/13 T.Fukumoto */
	/*-------------------------------*/
	/** ソート／ノンソートの切り替え */
	/*-------------------------------*/
	if (EnterSettingStatus(D2W_SelectSortingCopy,
						   D2W_On1,
						   2,
						   SETTING_STATUS_2,
						   OPR_VALID_CHECK_NOT_NEED,
						   STNG_NON_SORT_COPY) == NG) {
		return;
	}
 #endif

	/*-----------------------*/
	/** コピー縮小率のセット */
	/*-----------------------*/
	if (EnterSettingStatus(D2W_SelectCopyReduction,	/* "ｼｭｸｼｮｳﾘﾂ:           " */
						   D2W_AutoReduction,		/* "              ｼﾞﾄﾞｳ " */
						   6,
						   SETTING_STATUS_16,
						   OPR_COPY_REDUCTION,
						   (COPY_FIXED_REDUCTION_1 | COPY_FIXED_REDUCTION_2 |
							COPY_FIXED_REDUCTION_3 | COPY_FIXED_REDUCTION_4 |
	 						COPY_FIXED_REDUCTION_5 | COPY_FIXED_REDUCTION_6 |
							COPY_FIXED_REDUCTION_7)) == NG) {
		return;
	}

	/*-----------------*/
	/** マージンの設定 */
	/*-----------------*/
	margin = FixedLengthNumberInput((UWORD)CHK_CopyMargin(), 0, 85, (UBYTE)18, D2W_InputThresholdValue0_85);
																			/* "ｼｷｲﾁ  (0-85mm):     " */
	if (margin == 0xFFFF) {/*STOP*/
		return;
	}
	/* 閾値をセッティングステータスにセット？ */
	SYB_SettingStatus[COPY_MARGIN] = (UBYTE)margin;

	/* 完了 */
	ChildDisplaySetCompleted(D2W_SetCopyParameters);
}
#endif	/* (PRO_COPY_FAX_MODE == DISABLE) */


#if (PRO_KEYPANEL == PANEL_ANZU_L)
/*************************************************************************
	module		:[記録紙サイズセット]
	function	:[
		1.ＭＰトレーにセットされる記録紙サイズのセットを行う
		2. セット可能（サポートする）記録紙サイズ
		,USA	 :LETTER/LEGAL(下段カセットがinch仕様)
		,SEA	 :F4/A4(下段カセットがmetric仕様の場合）、LETTER/LEGAL(下段カセットがinch仕様の場合)
		,GBR	 :A4
		,JPN	 :A4
		
		,USA以外は未定です
		,国による違いはテーブルで吸収 
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J04
		ＡＮＺＵは上段の手差しの記録紙サイズの認識ができないため
		この設定が必要になる。
		<懸案事項>
		・GBRの場合、セット可能な記録紙のサイズが１種類しかないということでファンクション
		　テーブルから削除してしまうと、サイズエラー発生時のエラー解除の方法がＵＳＡなど
		　他の国と異なってくる。
		・SEAの場合、ラベンダーのようにメモリースイッチの設定によりA4/F4とLETTER/LEGALの組み合わせを
		　変更することはできない。1996/07/09
		　→プリンター基盤のジャンパーの設定により下段カセットにセットされている記録紙のサイズの認識がことなる
		よって、ジャンパーの設定がinchの場合、Letterしか認識できず、この時にトレーの記録紙をＡ４にセット
		されたら、正しい記録紙選択ができない。1996/07/09
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetPaperSize(void)
{
	/*---------------------------------------------------------------------------*
	 * プリント中に記録紙を変更してもプリンターはそれを認識することはできない。
	 * 連続プリント時の最大スループットを出す場合, ページ間でＭＰトレイの
	 * 用紙サイズ指定のコマンドを送出している時間がないから。
	 * またオペレーションでシリアルを行い、コマンドを送出しても、タイミングによっては
	 * シリアルできない場合がある。（ページ間のシリアル禁止期間)
	 * よってプリント中は記録紙サイズの変更はできないようにするのがいいかも
	 * またプリント中に記録紙だけ前回とはことなるサイズのものに変更された場合
	 * サイズエラーでプリント停止する
	 *-----------------------------------------------------------------------------*/
	if (CMN_CheckPrinting() == TRUE) {/* プリント中である */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_CLEANING) {
			OPR_ChildErrorFlag = PRINTER_CLEANING_ERROR;	/* "ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ      " */
		}
		else {
			OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;		/* "ﾌﾟﾘﾝﾄﾁｭｳ ﾃﾞｽ        " */
		}
		NackBuzzer();
		return;
	}

	if (CMN_CheckAramcoSuportA4Paper()) {	/* 1998/06/03 Y.Murata ｱﾗﾑｺ特殊対応 LT,LG,A4対応 ARM_A4*/

		if (EnterSettingStatus(D2W_EnterPaperSize,
							   D2W_PaperSizeNone,
							   6,
							   UPPER_SIZE,
							   OPR_UPPER_PAPER_ARM,
							   (UPPER_SIZE_NONE   | UPPER_SIZE_A4    | UPPER_SIZE_B4 |
								UPPER_SIZE_LETTER | UPPER_SIZE_LEGAL | UPPER_SIZE_F4)) == NG) {/*STOP*/
			return;
		}
	}
	else {

		if (EnterSettingStatus(D2W_EnterPaperSize,
							   D2W_PaperSizeNone,
							   6,
							   UPPER_SIZE,
							   OPR_UPPER_PAPER,
							   (UPPER_SIZE_NONE   | UPPER_SIZE_A4    | UPPER_SIZE_B4 |
								UPPER_SIZE_LETTER | UPPER_SIZE_LEGAL | UPPER_SIZE_F4)) == NG) {/*STOP*/
			return;
		}
	}

	/* 記録紙サイズがセットされた場合 */
	/* サイズエラーが発生している場合、用紙長コマンドをプリンターに送出する */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_SIZE_ERROR) {	/** サイズエラー */
#if (PRO_PRINT_TYPE == LASER)
		/* ミスプリント解除コマンドを送る *//* サイズエラー解除 */
		PRN_ResetMisPrint();
#endif
	}

	ChildDisplaySetCompleted(D2W_SetPaperSize);
}


/*************************************************************************
	module		:[記録紙サイズセット（ＰＣプリント対応用）]
	function	:[
		1.ＭＰトレーにセットされる記録紙サイズのセットを行う
		2.セット可能（サポートする）記録紙サイズ（機種による違いはテーブルで吸収）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＡＮＺＵは上段の手差しの記録紙サイズの認識ができないためこの設定が必要になる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/09/17]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能あり */
void Set_PCR_PaperSize(void)
{
	if (DPR_CheckOptionPrintBoardExist()/*DPR_PCR_Enable 1997/01/14 By J.Miyazaki*/) {	/** プリンタオプションボードが装着されている時 1996/10/08 by K.Watanabe */
		/*---------------------------------------------------------------------------*
		 * プリント中に記録紙を変更してもプリンターはそれを認識することはできない。
		 * 連続プリント時の最大スループットを出す場合, ページ間でＭＰトレイの
		 * 用紙サイズ指定のコマンドを送出している時間がないから。
		 * またオペレーションでシリアルを行い、コマンドを送出しても、タイミングによっては
		 * シリアルできない場合がある。（ページ間のシリアル禁止期間)
		 * よってプリント中は記録紙サイズの変更はできないようにするのがいいかも
		 * またプリント中に記録紙だけ前回とはことなるサイズのものに変更された場合
		 * サイズエラーでプリント停止する
		 *-----------------------------------------------------------------------------*/
		if (CMN_CheckPrinting() == TRUE) {	/* プリント中である */
			OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;
			NackBuzzer();
			return;
		}

		if (EnterSettingStatusToLong(D2W_EnterPaperSize,		/* "Paper Size:         " */
									 D2W_SelectPaperSizeNone,	/* "             None   " */
									 32,
									 PCR_MANUAL_SIZE,
									 OPR_PCR_UPPER_PAPER,
									 (PCR_MANUAL_SIZE_NONE | PCR_MANUAL_SIZE_A5   | PCR_MANUAL_SIZE_LT   |
									  PCR_MANUAL_SIZE_A4   | PCR_MANUAL_SIZE_LG   | PCR_MANUAL_SIZE_B5R  |
									  PCR_MANUAL_SIZE_B4   | PCR_MANUAL_SIZE_A3   | PCR_MANUAL_SIZE_A4R  |
									  PCR_MANUAL_SIZE_LTR  | PCR_MANUAL_SIZE_F4   | PCR_MANUAL_SIZE_A5R  |
									  PCR_MANUAL_SIZE_POST | PCR_MANUAL_SIZE_LD   | PCR_MANUAL_SIZE_GLTR |
									  PCR_MANUAL_SIZE_EXER | PCR_MANUAL_SIZE_INVR | PCR_MANUAL_SIZE_GLG  |
									  PCR_MANUAL_SIZE_GLT  | PCR_MANUAL_SIZE_CARD | PCR_MANUAL_SIZE_EXE  |
									  PCR_MANUAL_SIZE_B5   | PCR_MANUAL_SIZE_C5   | PCR_MANUAL_SIZE_HLT  |
									  PCR_MANUAL_SIZE_INV  | PCR_MANUAL_SIZE_B6   | PCR_MANUAL_SIZE_DL   |
									  PCR_MANUAL_SIZE_CM10 | PCR_MANUAL_SIZE_A6   | PCR_MANUAL_SIZE_MNK  |
									  PCR_MANUAL_SIZE_35   | PCR_MANUAL_SIZE_USER))
			== NG) {	/* STOP */
			return;
		}

		/* サイズエラーが発生している場合、用紙長コマンドをプリンターに送出する */
		if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_SIZE_ERROR) {	/** サイズエラー */
			PRN_ResetMisPrint();	/* ミスプリント解除コマンドを送る（サイズエラー解除） */
		}

		ChildDisplaySetCompleted(D2W_SetPaperSize);	/* "Set Paper Size      " */
	}
	else {					/** プリンタオプションボードが未装着の時 1996/10/08 by K.Watanabe*/
	/* プリンタオプションボードが未装着の時は、通常の記録紙サイズ設定の時と同じです */
		SetPaperSize();
	}
}
#endif

#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */

/*************************************************************************
	module		:[コピー禁止セット]
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
	date		:[1997/08/25]
	author		:[渡辺一章]
*************************************************************************/
void SetCopyProtect(void)
{
	if (EnterSettingStatus(D2W_SelectCopyProtect,	/* "ｺﾋﾟｰｷﾝｼ        :    " */
						   D2W_Off2,				/* "                OFF " */
						   2,
						   SETTING_STATUS_6,
						   OPR_VALID_CHECK_NOT_NEED,
						   COPY_PROTECT_ON) == OK) {
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_SettingCopyProtect[4]);	/* "    ｺﾋﾟｰｷﾝｼ         " */
		ChildDisplaySetCompleted(FunctionDisplayBufferHigh);					/* "ｺﾋﾟｰｷﾝｼ             " */
	}
}

/*************************************************************************
	module		:[ポーズ時間セット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J05]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetDialingPause(void)
{
	UBYTE	disp_position;
	UWORD	pause_min;
	UWORD	pause_max;
	UWORD	pause_time;

	pause_min = (UWORD)CTRY_PauseTimeMin();
	pause_max = (UWORD)CTRY_PauseTimeMax();
	CMN_MemorySetNULL(SubTitleDisplayBuffer, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(SubTitleDisplayBuffer, D2W_PauseTime);
	FixedNumberInputRangeSet(pause_min, pause_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(pause_max));
	DisplayStringHigh(0, D2W_SetDialingPause);
	pause_time = FixedLengthNumberInput((UWORD)SYB_SettingStatus[DIALING_PAUSE],
										pause_min,
										pause_max,
										disp_position,
										SubTitleDisplayBuffer);
	if (pause_time != 0xFFFF) { /* 入力済み */
		SYB_SettingStatus[DIALING_PAUSE] = (UBYTE)pause_time;
#if (PRO_MULTI_LINE == ENABLE)
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_SETTEING_STATUS);
#endif
		ChildDisplaySetCompleted(D2W_SetDialingPause);		/*"ﾎﾟｰｽﾞｼﾞｶﾝ ｾｯﾄ     "*/
	}
}

/*************************************************************************
	module		:[着信ベル回数セット]
	function	:[
		1.	ＦＡＸ待機及び電話／ＦＡＸ待機時の着信ベル回数をセット
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J06]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetNumberOfRings(void)
{
	UBYTE	disp_position;
	UWORD	ring_min;
	UWORD	ring_max;
	UWORD	ring_count;

	ring_count = 0;
	ring_min = (UWORD)CTRY_RingCountMin();
	ring_max = (UWORD)CTRY_RingCountMax();
	CMN_MemorySetNULL(SubTitleDisplayBuffer, OPR_DISPLAY_MAX, ' ');

/* 警電回線と加入回線の呼出回数 を別々設定 Added by SMuratec 夏 2005/06/22 */
#if defined(KEISATSU)
	CMN_StringCopy(SubTitleDisplayBuffer, D2W_NumberOfRings_Keiden);
	FixedNumberInputRangeSet(ring_min, ring_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(ring_max));

	DisplayStringHigh(0, D2W_SetNumberOfRings);	/* 警電回線を設定 */
	ring_count = FixedLengthNumberInput((UWORD)SYB_SettingStatus[NUMBER_OF_RINGS_EXT],
										ring_min,
										ring_max,
										disp_position,
										SubTitleDisplayBuffer);

	if (ring_count != 0xFFFF) { /* 入力済み */
		SYB_SettingStatus[NUMBER_OF_RINGS_EXT] = (UBYTE)ring_count;
	}
	else
		return;
		
	CMN_StringCopy(SubTitleDisplayBuffer, D2W_NumberOfRings_Kanyu);
	FixedNumberInputRangeSet(ring_min, ring_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(ring_max));
	DisplayStringHigh(0, D2W_SetNumberOfRings);	/* 加入回線を設定 */
	ring_count = FixedLengthNumberInput((UWORD)SYB_SettingStatus[NUMBER_OF_RINGS],
										ring_min,
										ring_max,
										disp_position,
										SubTitleDisplayBuffer);

	if (ring_count != 0xFFFF) { /* 入力済み */
		SYB_SettingStatus[NUMBER_OF_RINGS] = (UBYTE)ring_count;
		ChildDisplaySetCompleted(D2W_SetNumberOfRings);	/* "ﾖﾋﾞﾀﾞｼﾍﾞﾙｶｲｽｳｾｯﾄ    " */
	}	

#else

	CMN_StringCopy(SubTitleDisplayBuffer, D2W_NumberOfRings);
	FixedNumberInputRangeSet(ring_min, ring_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(ring_max));

	DisplayStringHigh(0, D2W_SetNumberOfRings);
	ring_count = FixedLengthNumberInput((UWORD)SYB_SettingStatus[NUMBER_OF_RINGS],
										ring_min,
										ring_max,
										disp_position,
										SubTitleDisplayBuffer);

	if (ring_count != 0xFFFF) { /* 入力済み */
		SYB_SettingStatus[NUMBER_OF_RINGS] = (UBYTE)ring_count;
 #if (PRO_MULTI_LINE == ENABLE)
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_SETTEING_STATUS);
 #endif
		ChildDisplaySetCompleted(D2W_SetNumberOfRings);	/* "ﾖﾋﾞﾀﾞｼﾍﾞﾙｶｲｽｳｾｯﾄ    " */
	}
#endif	
}

/*************************************************************************
	module		:[リダイアル設定]
	function	:[
		1.以下のものを設定する。
		，リダイアル回数
		，リダイアル間隔
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J07]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetRedial(void)
{
	UBYTE	disp_position;
	UWORD	redial_min;
	UWORD	redial_max;
	UWORD	redial_count;
	UWORD	interval;

	/*----------------------*/
	/* リダイアル回数セット */
	/*----------------------*/
	redial_min = (UWORD)CTRY_RedialNumberMin();
	redial_max = (UWORD)CTRY_RedialNumberMax();
	CMN_MemorySetNULL(SubTitleDisplayBuffer, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(SubTitleDisplayBuffer, D2W_RedialCount);
	FixedNumberInputRangeSet(redial_min, redial_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(redial_max));

	DisplayStringHigh(0, D2W_SetNumberOfRedials);
	/* リダイアル回数入力 */
	redial_count = FixedLengthNumberInput((UWORD)SYB_SettingStatus[NUMBER_OF_REDIAL],
										  redial_min,
										  redial_max,
										  disp_position,
										  SubTitleDisplayBuffer);
	if (redial_count != 0xFFFF)
		/* 入力された値をセット */
		SYB_SettingStatus[NUMBER_OF_REDIAL] = (UBYTE)redial_count;
	else 
		return;

	/*--------------------------*/
	/* リダイアル間隔セット 	*/
	/*--------------------------*/
	redial_min = (UWORD)CTRY_RedialIntervalMin();
	redial_max = (UWORD)CTRY_RedialIntervalMax();
	CMN_MemorySetNULL(SubTitleDisplayBuffer, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(SubTitleDisplayBuffer, D2W_RedialInterval);
	FixedNumberInputRangeSet(redial_min, redial_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(redial_max));

	DisplayStringHigh(0, D2W_SetRedialInterval);		/*"ｻｲﾀﾞｲﾔﾙｶﾝｶｸ_ｾｯﾄ_____"*/
	interval = FixedLengthNumberInput((UWORD)SYB_SettingStatus[REDIAL_INTERVAL],
									   redial_min,
									   redial_max,
									   disp_position,
									   SubTitleDisplayBuffer);
	if (interval != 0xFFFF) {
		/* 入力された値をセット */
		SYB_SettingStatus[REDIAL_INTERVAL] = (UBYTE)interval;
	}
	else {
		return;
	}

	/* 完了表示 */
	ChildDisplaySetCompleted(D2W_SetRedial);
}

/*************************************************************************
	module		:[ＥＣＭモードセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J08]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetECMMode(void)
{
	if (EnterSettingStatus(D2W_SelectECMMode,
						   D2W_Off2,
						   2,
						   SETTING_STATUS_6 ,
						   OPR_VALID_CHECK_NOT_NEED,
						   ECM_SETTING) == OK) {
		ChildDisplaySetCompleted(D2W_SetECMMode);/*"ECM_ﾓｰﾄﾞ_ｾｯﾄ________"*/
	}
}

/*************************************************************************
	module		:[パスコードセット]
	function	:[
		1.閉域通信、ポーリング時に参照するパスコードの登録を行う。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J09]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetPasscode(void)
{
	UWORD	current_passcode;
	UWORD	passcode;

	passcode = current_passcode = 0;

	current_passcode = CMN_ASC_ToUnsignedInt(SYB_PasscodeNumber, SYS_PASSCODE_MAX);
	DisplayStringHigh(0, D2W_SetPasscode);
	/* 入力 */
	passcode = FixedLengthNumberInput(current_passcode, 0, 9999, (UBYTE)16, D2W_InputPasscode);
	if (passcode != 0xFFFF) { /* セットされた */
		/* 古いパスコードを消去して、新しいパスコードをセット */
		CMN_MemorySet(SYB_PasscodeNumber, SYS_PASSCODE_MAX, NULL);
		CMN_UnsignedIntToASC(SYB_PasscodeNumber, passcode, 4, '0');
		ChildDisplaySetCompleted(D2W_SetPasscode); 
	}
}

/*************************************************************************
	module		:[閉域通信セット]
	function	:[
		1.閉域通信ＯＮ／ＯＦＦ切り替え
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J10]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetClosedNetwork(void)
{
	if (EnterSettingStatus(D2W_SelectClosedNetwork,
						   D2W_Off2,
						   2,
						   SETTING_STATUS_4,
						   OPR_VALID_CHECK_NOT_NEED,
						   CLOSED_NETWORK_ON) == OK) {
		ChildDisplaySetCompleted(D2W_SetClosedNetwork);	/*"ﾍｲｲｷﾂｳｼﾝ_ｾｯﾄ________"*/
	}
}

/*************************************************************************
	module		:[パスワード送信セット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J11]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetSecurityTx(void)
{
	if (EnterSettingStatus(D2W_SelectSecurityTransmission,
						   D2W_Off2,
						   2,
						   SETTING_STATUS_4 ,
						   OPR_VALID_CHECK_NOT_NEED,
						   SECURITY_TRANSMISSION) == OK) {
		ChildDisplaySetCompleted(D2W_SetSecurityTransmission);
	}
}

/*************************************************************************
	module		:[ダイレクトメール防止セット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J12]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口,桑原]
*************************************************************************/
void SetBlockJunkFax(void)
{
	UBYTE	ret;

	if(!CHK_UNI_JunkMailProtectDial()){		/* メモリスイッチで普通のﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄにするか決める */
		if (EnterSettingStatus(D2W_SelectBlockJunkMail,
							   D2W_Off2,
							   2,
							   SETTING_STATUS_4,
							   OPR_VALID_CHECK_NOT_NEED,
							   BLOCK_JUNK_FAX_ON) == OK) {
			ChildDisplaySetCompleted(D2W_SetBlockJunkMail);	/*"ﾀﾞｲﾚｸﾄﾒｰﾙ ﾎﾞｳｼ______"*/
		}
	}
	else{
		if (EnterSettingStatus(D2W_SelectBlockJunkMail,
							   D2W_ModeOff,
							   4,
							   SETTING_STATUS_2,
							   OPR_JUNK_MAIL,
							   (BLOCK_JUNK_FAX_OFF | BLOCK_JUNK_FAX_MODE1 |
								BLOCK_JUNK_FAX_MODE2 | BLOCK_JUNK_FAX_MODE3)) == NG) {
			return;
		}
/*		if(( SYB_SettingStatus[ SETTING_STATUS_2 ] == BLOCK_JUNK_FAX_OFF ) ||	@* OFF､ﾓｰﾄﾞ1の時ｾｯﾄ完了 */
/*		   ( SYB_SettingStatus[ SETTING_STATUS_2 ] == BLOCK_JUNK_FAX_MODE1 )){*//* 97/10/21 By M.Kuwahara */
		if(( CHK_BlockJunkFaxMode() == BLOCK_JUNK_FAX_OFF ) ||	/* OFF､ﾓｰﾄﾞ1の時ｾｯﾄ完了 */
		   ( CHK_BlockJunkFaxMode() == BLOCK_JUNK_FAX_MODE1 )) {
			ChildDisplaySetCompleted(D2W_SetBlockJunkMail);	/*"ﾀﾞｲﾚｸﾄﾒｰﾙ ﾎﾞｳｼ______"*/
			return;
		}
		/* ﾘｽﾄ､ﾀﾞｲﾔﾙｾｯﾄの選択 */
#if (0)
//		if(( ret = (UBYTE)BlockJunkCommandOperation()) == STOP ){
//			return;
//		}
#endif
		if (( ret = ConfirmKeyInputOperation( D2W_SetBlockJunkMailDial, 
											  D2W_ProgramEnter,
											  ENTER, FUNCTION )) == OPR_END ) {
			return;
		}
		/* ﾀﾞｲﾔﾙｾｯﾄの選択時 */
/*		if( ret == ENTER ){*/	/* 97/11/17 By M.Kuwahara */
		if ( ret == CONFIRM_EXEC ) {
			/* 番号登録 */
			if( SetJunkMailDial() == KEY_TIME_UP ){	/* 時間切れの時は初期画面へ */
				return;
			}
		}
		/* ﾘｽﾄを出力するか */
		if( PrintBlockJunkList() == NG ){
			return;
		}
	}
}

/*************************************************************************
	module		:[リモート診断セット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J13]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetRemoteDiagnostic(void)
{
	if (EnterSettingStatus(D2W_SelectRemoteDiagnostic,
						   D2W_Off2,
						   2,
						   SETTING_STATUS_6,
						   OPR_VALID_CHECK_NOT_NEED,
						   REMOTE_DIAG_ON) == OK) {
		ChildDisplaySetCompleted(D2W_SetRemoteDiagnostic);
	}
}

/*************************************************************************
	module		:[メモリー送信セット]
	function	:[
		1.メモリー送信の設定のデフォルト値の設定
	]
	return		:[]
	common		:[]
	comment		:[PRG-J14]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetMemoryTransmission(void)
{
	if (EnterSettingStatus(D2W_SelectMemoryTransmission,
						   D2W_Off2,
						   2,
						   SETTING_STATUS_6,
						   OPR_VALID_CHECK_NOT_NEED,
						   MEMORY_TRANSMISSION_ON) == OK) {
		MemoryTxLedSet();
		ChildDisplaySetCompleted(D2W_SetMemoryTransmission);
	}
}

/*************************************************************************
	module		:[サイレントオペレーションセット]
	function	:[
		1.無音オペレーションの設定を行う。
		2.サイレントモード：
		，アックブザー　　　：鳴動する。
		，ナックブザー　　　：鳴動する。
		，エンドブザー　　　：鳴動しない。
		，アラームブザー　　：鳴動しない。
		，保留警告ブザー　　：鳴動しない。
		，保留終了ブザー　　：鳴動しない。
		，ハングアップブザー：鳴動しない。
		，着信ベル			：鳴動しない。
		，会話予約のベル	：鳴動する。
		，ＴＥＬ／ＦＡＸの疑似ベル：鳴動する。
		, 受信完了アラーム（GBR）：鳴動しない？TBD
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J15]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetSilentOperation(void)
{
	if (EnterSettingStatus(D2W_SelectSilentOperation,
						   D2W_Off2,
						   2,
						   SETTING_STATUS_16,
						   OPR_VALID_CHECK_NOT_NEED,
						   STG_SILENT_OPERATION) == OK) {
		ChildDisplaySetCompleted(D2W_SetSilentOperation);	/*"ｻｲﾚﾝﾄ ｵﾍﾟﾚｰｼｮﾝ ｾｯﾄ"*/
	}
}

/*************************************************************************
	module		:[プロテクトパスコードセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J17]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetProtectPasscode(void)
{
	UWORD	passcode;

	passcode = 0;

	/** 古いパスコードを入力させる */
	DisplayStringHigh(0, D2W_ProtectPasscode);
	if ((passcode = EnterPassCode(SYB_ProtectPasscode, CHK_PASS_CODE_ENTER, D2W_OldProtectPasscode)) == 0xFFFF) {
		/* 入力終了 */
		return;
	}

	/** パスコードチェックを行う */
	if (passcode != SYB_ProtectPasscode) { /** パスコード不一致 */
		OPR_ChildErrorFlag = INVALID_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ" */
		NackBuzzer();
		return;
	}

	/**新しいパスコードの入力を行う */
	if ((passcode = EnterPassCode(SYB_ProtectPasscode, PASS_CODE_ENTER_ZERO_OK, D2W_NewProtectPasscode)) == 0xFFFF) {
		/* 入力終了 */
		return;
	}

	if (passcode == 0) {/* パスコード消去 */
		if (EraseProtectPasscodeEnable() == TRUE) {
			/* プロテクトを全て解除する */
			AllProtectClear();
			SYB_ProtectPasscode = passcode;
			ChildDisplaySetCompleted(D2W_SetProtectPasscode);	/* "ﾌﾟﾛﾃｸﾄ ﾊﾟｽｺｰﾄﾞ ｾｯﾄ  " */
		}
		else {/*消去不可能であれば。1：終了、２：再入力 --> とりあえず終了 */
			NackBuzzer();
			OPR_ChildErrorFlag = PROTECT_DOCUMENT_STORED_ERROR;
		}
	}
	else { /* ００００以外がセットされた */
		SYB_ProtectPasscode = passcode;
		ChildDisplaySetCompleted(D2W_SetProtectPasscode);		/* "ﾌﾟﾛﾃｸﾄ ﾊﾟｽｺｰﾄﾞ ｾｯﾄ  " */
	}
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	/* メンテナンススイッチに保存する 97/10/17 T.Fukumoto */
	SaveProtectPasscode();
#endif
}

/*************************************************************************
	module		:[プロテクトパスコードをメンテナンススイッチに記録]
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
	date		:[1997/10/17]
	author		:[福本貴吉]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
void SaveProtectPasscode(void)
{
	UWORD	code;
	UBYTE	buffer[5];

	/* プロテクトパスコードを ＡＳＣＩＩに変換 */
	CMN_UnsignedIntToASC(&buffer[0], SYB_ProtectPasscode, 4, '0');

	/* ＡＳＣＩＩコード から Ｈｅｘコードに変換 */
	code = CMN_ASC_ToUnsignedIntHex(&buffer[0], 4);

	/* メンテナンススイッチに記録 */
	SYB_MaintenanceSwitch[MNT_SW_E8] = (UBYTE)(code >> 8);			/* 上位バイトをE8 */
	SYB_MaintenanceSwitch[MNT_SW_E9] = (UBYTE)(code & 0x00FF);		/* 下位バイトをE9 */
}
#endif

/*************************************************************************
	module		:[プロテクトを強制的に解除する]
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
	date		:[1995/12/08]
	author		:[江口]
*************************************************************************/
void AllProtectClear(void)
{
	/** オペレーションプロテクトクリア */
	/** 受信原稿プリントプロテクトクリア */
	/* 以上の２つのみとする */
	SYB_SettingStatus[SETTING_STATUS_23] &= ~(SECURITY_RX_ON | OPERATION_PROTECT_ON);

#if (PRO_DEPARTMENT == ENABLE)
	/* T-340ファネット指摘事項(No.114)
	** プロテクトコードを登録し、部門管理プロテクトをONにする。その後、プロテクトコードのみを消去しても
	** 部門管理プロテクトがONのままとなり、プロテクトコードを要求するが、実際は未登録の為矛盾する。
	** よって、プロテクトコードを消去された場合は上記２つのセキュリティー機能と一緒に部門管理プロテクトもOFFにする
	** By O.Kimoto 2002/10/30
	*/
	SYB_SettingStatus[SETTING_STATUS_23] &= ~SECTION_CHECK_PROTECT_ON;
#endif

	/* セキュリティ受信モードを解除する */
	SYB_SecurityRxModeFlag = 0;
	return;
}

/*************************************************************************
	module		:[プロテクトパスコード消去可能か調べる]
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
	date		:[1995/12/08]
	author		:[江口]
*************************************************************************/
UBYTE EraseProtectPasscodeEnable(void)
{
#if (PRO_SECURITY_RX == ENABLE)
	/* プロテクトONの状態でプリントされずにメモリー内にある場合、
	   プロテクト解除できない */
	if ((CheckProtectedDocStored() == TRUE) || (CheckProtectedDocStoring() == TRUE)) {
		return (FALSE);
	}
#endif
	return (TRUE);
}

/*************************************************************************
	module		:[オペレーションプロテクトセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J18]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetOperationProtect(void)
{
	UWORD	passcode;

	passcode = 0;

	DisplayStringHigh(0, D2W_SetOperationProtect);

	/* プロテクトのパスコードの有無をチェックする */
	if (CheckProtectPasscodeSet() == FALSE) { /* パスコードが登録されていない */
		OPR_ChildErrorFlag = NO_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ﾐﾄｳﾛｸﾃﾞｽ " */
		NackBuzzer();
		return;
	}

	/* パスコードの入力 */
	if ((passcode = EnterPassCode(SYB_ProtectPasscode, CHK_PASS_CODE_ENTER, D2W_EnterProtectPasscode)) == 0xFFFF) {
		return;
	}
	/* パスコードチェック */
	if (passcode != SYB_ProtectPasscode) { /* パスコード不一致 */
		OPR_ChildErrorFlag = INVALID_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ" */
		NackBuzzer();
		return;
	}

	/* パスコードが一致した場合、プロテクトの設定を行う */
	if (EnterSettingStatus(D2W_OperationProtectOnOff,
						   D2W_Off2,
						   2,
						   SETTING_STATUS_23,
						   OPR_VALID_CHECK_NOT_NEED,
						   OPERATION_PROTECT_ON) == OK) {
		ChildDisplaySetCompleted(D2W_SetOperationProtect);
	}
}

/*************************************************************************
	module		:[ＰＩＮアクセスモード切り替え]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J19]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetPINAccessMode(void)
{
#if (PRO_PIN_ACCESS == ENABLE)
	UWORD	passcode;

	DisplayStringHigh(0, D2W_SetPINAccessMode);
	/* プロテクトのパスコードの有無をチェックする */
	if (CheckProtectPasscodeSet() == FALSE) { /* パスコードが登録されていない */
		OPR_ChildErrorFlag = NO_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ﾐﾄｳﾛｸﾃﾞｽ " */
		NackBuzzer();
		return;
	}

	/* パスコードの入力 */
	if ((passcode = EnterPassCode(SYB_ProtectPasscode, CHK_PASS_CODE_ENTER, D2W_EnterProtectPasscode)) == 0xFFFF) {
		return;
	}
	/* パスコードチェック */
	if (passcode != SYB_ProtectPasscode) { /* パスコード不一致 */
		OPR_ChildErrorFlag = INVALID_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ" */
		NackBuzzer();
		return;
	}

	/* ＰＩＮアクセスモードのセット */
	if (EnterSettingStatus(D2W_PINAccessMode,
#if (0)	/* 同一内容の為、ﾜｰﾃﾞｨﾝｸﾞを1つにします by K.Watanabe 1998/08/24 */
//						   D2W_PinAccessOff,
#endif
						   D2W_ModeOff,
						   3,
						   SETTING_STATUS_23,
						   OPR_PIN_MODE,
						   (PIN_ACCESS_MODE1 | PIN_ACCESS_MODE2)) == OK) {
		ChildDisplaySetCompleted(D2W_SetPINAccessMode);
	}
#endif
#if (PRO_PIN_ACCESS == DISABLE)
	NackBuzzer();
	return;
#endif
}

/*************************************************************************
	module		:[リングマスターセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J20]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetRingMaster(void)
{
#if (PRO_RING_MASTER == ENABLE)
 #if defined(AUS)	/* DUET 1997/05/21 Y.Murata */
	if (SYB_MachineParameter[0] == 0x00) {	/* AUS */
		if (EnterSettingStatus(	D2W_SelectRingMaster  ,
								D2W_Off2,
								2 ,
								SETTING_STATUS_15,
								OPR_VALID_CHECK_NOT_NEED,
								RING_MASTER_ON) == OK) {

			ChildDisplaySetCompleted(D2W_SetRingMaster);
			return;	
		}
	}
	else {
		NackBuzzer();
		return;
	}
 #else
	if (EnterSettingStatus(D2W_SelectRingMaster,
						   D2W_Off2,
						   2,
						   SETTING_STATUS_15,
						   OPR_VALID_CHECK_NOT_NEED,
						   RING_MASTER_ON) == OK) {

		if (CHK_RingMasterON() != 0) {
			/* リングパターンセット */
			if (EnterSettingStatus(D2W_SelectRingPattern,
								   D2W_RingPattern_A,
								   8,
								   SETTING_STATUS_13,
								   OPR_RING_PATTERN,
								   (RING_MASTER_PATTERN_1 | RING_MASTER_PATTERN_2 |
									RING_MASTER_PATTERN_3 | RING_MASTER_PATTERN_4 |
									RING_MASTER_PATTERN_5 | RING_MASTER_PATTERN_6 |
									RING_MASTER_PATTERN_7 | RING_MASTER_PATTERN_8 )) == OK) {

				ChildDisplaySetCompleted(D2W_SetRingMaster);
				return;
			}
		}
		ChildDisplaySetCompleted(D2W_SetRingMaster);
		return;	
	}
 #endif
#endif	/* (PRO_RING_MASTER == ENABLE) */
#if (PRO_RING_MASTER == DISABLE)
	NackBuzzer();
	return;
#endif
}

/*************************************************************************
	module		:[スタンプセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J21]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void SetStamp(void)
{
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1998/12/28 */
 #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/04/03 T.Takagi */
	if ((CHK_UNI_RedScanModeEnable() && !CHK_UNI_CSDR_ConfirmOprEnable() && !CHK_UNI_CSDR_TtiTxOprEnable())
	 || (!CHK_UNI_RedScanModeEnable() && CHK_UNI_CSDR_ConfirmOprEnable() && !CHK_UNI_CSDR_TtiTxOprEnable())
	 || (!CHK_UNI_RedScanModeEnable() && !CHK_UNI_CSDR_ConfirmOprEnable() && CHK_UNI_CSDR_TtiTxOprEnable())) {
		NackBuzzer();
		return;
	}
 #else
	/*【CSDR-No.111】通信証ON/OFF、【CSDR-No.102】発信元ON/OFF有効時 */
	if ((CHK_UNI_CSDR_ConfirmOprEnable() && !CHK_UNI_CSDR_TtiTxOprEnable())
	 || (!CHK_UNI_CSDR_ConfirmOprEnable() && CHK_UNI_CSDR_TtiTxOprEnable())) {
		NackBuzzer();
		return;
	}
 #endif
#endif
	if (EnterSettingStatus(D2W_StampOnOff,
						   D2W_Off2,
						   2,
						   SETTING_STATUS_6,
						   OPR_VALID_CHECK_NOT_NEED,
						   DOCUMENT_STAMP_ON) == OK) {
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
		StampLedSet();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		ChildDisplaySetCompleted(D2W_SetStamp);
	}
}

/*************************************************************************
	module		:[ドラム寿命カウンタークリア]
	function	:[
		1.ライフモニターのドラム寿命のカウンターをクリアする
		2.ライフモニターのドラム交換回数をインクリメントする
		3.ドラム寿命のカウンターの値がドラムの寿命に達していなかったら(ドラム交換のワーニング
		,　メッセージが表示されてなかったら）このオペレーションは拒否される。
		4.ユーザーがドラムを交換した時に必ず実行する必要がある
		5.ユニークＳＷのF-7-1をたてるとドラム寿命のカウンターの値が
		,	ドラムの寿命に達していなくてもクリアできる	1997/12/02 Y.Matsukuma
	]
	return		:[]
	common		:[
					SYB_LifeMonitor
					PRN_DrumPrintMax
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/06/25]
	author		:[江口]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* by K.Watanabe 1998/08/18 */
void ResetDrumLife(void)
{
	/* ドラム寿命に達していないか調べる */
	if (SYB_LifeMonitor.DrumLifeCount < (UDWORD)PRN_DrumPrintMax) {	/* UDWORDキャスト By M.Tachibana 1997/12/09 */
		if (CHK_UNI_ResetDrumLife() == 0) { /* 1997/12/02 Y.Matsukuma */
			NackBuzzer();
			return;
		}
	}

	if (ConfirmKeyInputOperation(D2W_ResetDrumLife, D2W_CheckProgramEnter, ENTER, FUNCTION) == CONFIRM_EXEC) {
		SYB_LifeMonitor.DrumLifeCount = 0;
		SYB_LifeMonitor.DrumReplaceCount++;
		SYS_MachineStatus[SYS_WARNING_STATUS] &= ~SYS_WARNING_DRUM_REPLACE;
		DisplayStringHigh(0, D2W_ResetDrumLife);	/* "ﾄﾞﾗﾑ ﾗｲﾌ ｶｳﾝﾀｰ ｸﾘｱ  " */
		ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
}
#endif

/*************************************************************************
	module		:[受信完了アラームセット]
	function	:[
		1.

	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[GBRのみ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/07/07]
	author		:[江口]
*************************************************************************/
#if defined(GBR)
void SetRxAlarm(void)
{
	if (EnterSettingStatus(D2W_RxAlarm,
						   D2W_Off2,
						   2,
						   SETTING_STATUS_23,
						   OPR_VALID_CHECK_NOT_NEED,
						   AUDIBLE_ALARM) == OK) {
		ChildDisplaySetCompleted(D2W_SetRxAlarm);
	}
}
#endif

/*************************************************************************
	module		:[数値入力の入力範囲のセット]
	function	:[
		1.入力範囲に国別等の違いがある場合、それを計算し表示形式に変換
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/19]
	author		:[江口]
*************************************************************************/
void FixedNumberInputRangeSet(UWORD min_value,
							  UWORD max_value,
							  UBYTE tail_position,
							  UBYTE *set_buffer)
{
	/* 変更する必要あり 1995/10/03 Eguchi */
	UBYTE	figure;
	UBYTE	set_position;

	figure = FigureCalculation(max_value);
	/* 固定文字列の最終位置(１２）から(-)と入力範囲の表示用の領域をひいたもの */
	set_position = (UBYTE)(tail_position - (UBYTE)(figure * 2 + 3));

	set_buffer[set_position++] = '(';
	CMN_UnsignedIntToASC(&set_buffer[set_position], min_value, figure, '0');
	set_position += figure;
	set_buffer[set_position++] = '-';
	CMN_UnsignedIntToASC(&set_buffer[set_position], max_value, figure, '0');
	set_position += figure;
	set_buffer[set_position++] = ')';
	set_buffer[set_position  ] = ':';
}

#if (PRO_DIALIN == ENABLE)
/*************************************************************************
	module		:[ダイヤルインセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[JPN のみ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/21]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetDialIn(void)
{
	UBYTE	i;					/* ループ変数 */
	UBYTE	is_number_input;	/* ダイヤル番号が入力されたか */
	UBYTE	*dialin_number;		/* ダイヤルイン番号格納ポインター */
	UWORD	bell_time;			/* ダイヤルイン回数 */
	UWORD	current_number;		/* 登録済みのダイヤルイン番号 */
	UWORD	input_number;		/* 入力された番号 */

	DisplayStringHigh(0, D2W_SetDialIn);	/* "ﾀﾞｲﾔﾙｲﾝ ｾｯﾄ         " */

	/*---------------------*/
	/** ダイアル番号の登録 */
	/*---------------------*/
	for (i = 0; i < 3; i++) {
		switch (i) {
		case 0:	/* ダイヤルインＦＡＸ番号 */
			dialin_number = &SYB_Dialin.FaxNumber[0];
			break;
		case 1:	/* ダイヤルインＴＥＬ１番号 */
			dialin_number = &SYB_Dialin.Tel1Number[0];
			break;
		case 2:	/* ダイヤルインＴＥＬ２番号 */
			dialin_number = &SYB_Dialin.Tel2Number[0];
			break;
		}

		/* ダイヤルイン番号の入力 */
		is_number_input = InputDialInNumber(dialin_number, D2W_DialInFax + (OPR_WORDING_LEN * i));
		if (is_number_input) {	/* ダイヤルイン番号が入力された時 */
			/* 入力された番号をセットします */
			CMN_StringCopy(dialin_number, CharacterInput.Buffer);
			if (CharacterInput.Buffer[0] != '*') {	/* ダイヤル番号が登録された時 */
				SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_NO_DIAL_IN_NUMBER; /* 番号未登録エラーを解除しておく */
			}
		}
		else {					/* 入力中止・タイムアップの時 */
			break;
		}
	}

	/** 入力チェック */
#if defined(SATSUKI2) || defined(STOCKHM2) /* SATSUKI2は待機モードでダイヤルイン待機を持ちます。O.Oshima 2003/06/25 */
	if (!CMN_CheckInputDialInNumber()) {
#else
	if ((DialIn()) && (!CMN_CheckInputDialInNumber())) {
#endif
		/* ダイヤルイン待機で、ダイヤルイン番号が１つも登録されていない時 */
		SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_NO_DIAL_IN_NUMBER;	/* ダイヤルインエラーをセット */
	}

	/*-----------------*/
	/** ベル回数の登録 */
	/*-----------------*/
	if (is_number_input) {	/* ダイヤルイン番号が全て入力されている時 */
		DisplayStringHigh(0, D2W_DialInRings);	/* "ﾍﾞﾙｼﾞｶﾝ ｾｯﾄ         " */
		bell_time = FixedLengthNumberInput((UWORD)SYB_Dialin.BellTime, 10, 60,(UBYTE)18, D2W_DialInRings10_60);
		if (bell_time != 0xFFFF) {
			SYB_Dialin.BellTime = (UBYTE)bell_time;
			ChildDisplaySetCompleted(D2W_SetDialIn);	/* "ﾀﾞｲﾔﾙｲﾝ ｾｯﾄ         " */
		}
	}
}

/*************************************************************************
	module		:[ダイヤルイン番号入力]
	function	:[
		1.
	]
	return		:[
		TRUE	:登録完了
		FALSE	:登録中止・タイムアップ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/20]
	author		:[渡辺一章]
*************************************************************************/
UBYTE InputDialInNumber(UBYTE *dialin_number, UBYTE *item_wording)
{
	UBYTE	i;				/* ループ変数				*/
	UBYTE	key;			/* キー入力					*/
	UBYTE	keytype;		/* キー入力					*/
	UBYTE	length; 		/* 桁数						*/
	UBYTE	ast_cnt; 		/* 入力内容チェックカウント	*/
	UBYTE	is_loop_end;	/* ループ終了で使用			*/
	UBYTE	ret;			/* リターン値				*/
	UWORD	input_value;	/* 入力された数値			*/

	/* ワークエリア初期化 */
	length = 4;
	ClearCharacterInput();
	CharacterInput.WritePosition = (UBYTE)(length - 1);
	CharacterInput.LcdDisplayPosition = 16;
	CharacterInput.FixedWordingLow = item_wording;
	CMN_StringCopy(CharacterInput.Buffer, dialin_number);

	/* 下段表示ワーディングのセット */
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferLow, CharacterInput.FixedWordingLow);

	ret = FALSE;
	is_loop_end = FALSE;
	while (is_loop_end != TRUE) {

		/** 下段表示 */
		CMN_StringCopy(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition], CharacterInput.Buffer);
		DisplayStringLow(0, FunctionDisplayBufferLow);
		CursorOn((UBYTE)(CharacterInput.LcdDisplayPosition + CharacterInput.CursorPosition + OPR_LCD_LOWER_ADD));

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理 */
		switch (keytype) {
		case STOP:			/** ストップキー */
		case KEY_TIME_UP:	/** １分間キー入力なし */
			CursorOff();
			is_loop_end = TRUE;
			break;
		case ENTER:			/** セットキー */
			/* ダイヤル番号の中にいくつ'＊'があるかをチェックします */
			ast_cnt = 0;
			for (i = 0; i < length; i++ ){
				if (CharacterInput.Buffer[i] == '*') {
					ast_cnt++;
				}
			}
			if ((ast_cnt == 0) || (ast_cnt == 4)) {	/* ４桁とも数字か、'＊'（ダイヤル番号クリア）の時だけ登録可能 */
				/* 数字の入力しか受け付けなく、かつ００００～９９９９までＯＫなので、入力範囲のチェックは省きます */
				CursorOff();
				ret = TRUE;
				is_loop_end = TRUE;
			}
			else {
				NackBuzzer();
			}
			break;
		case CLEAR:			/** クリアキー */
			CMN_MemorySet(CharacterInput.Buffer, 4 , '*');
			CharacterInput.CursorPosition = 0;
			break;
		case NUMBER:		/** 数字キー */
			FixedNumberDataSet(key);
			break;
		case FUNCTION:		/** ＞キー */
			CursorRightRotation();
			break;
		case LEFT_ARROW: 	/** ＜キー */
			CursorLeftRotation();
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}

	return(ret);
}

#endif	/* (PRO_DIALIN == ENABLE) */

/*************************************************************************
	module		:[ダイレクトメールダイヤルセット、リスト出力選択オペレーション]
	function	:[
		1.機能キーで、リスト出力選択、セットでダイヤルセット選択
		2.ストップキー又はキー待ちタイムオーバーで終了
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/16]
	author		:[桑原美紀]
*************************************************************************/
#if (0)
//UBYTE BlockJunkCommandOperation(void)
//{
//	UBYTE	key;
//	UBYTE	keytype;
//
//	DisplayStringHigh(0, D2W_SetBlockJunkMailDial);		/* "ﾀﾞｲﾚｸﾄﾒｰﾙ ﾀﾞｲﾔﾙ ｾｯﾄ"*/
//	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */
//	while (1) {
//		/** キー取り込み */
//		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
//		key = GetInputKeyCode();
//		keytype = GetInputKeyType();
//
//		switch (keytype) {
//		case STOP:		/* 停止キー */
//		case KEY_TIME_UP:	/* １分間キー入力なし */
//			return( STOP );
//		case ENTER:		/* セットキー */
//			return( ENTER );
//		case FUNCTION:	/* 機能キー */
//			return( FUNCTION );
//		case NO_EFFECT:
//			break;
//		default:
//			NackBuzzer();
//			break;
//		}
//	}
//}
#endif

/*************************************************************************
	module		:[ジャンクメール防止ダイヤルセット]
	function	:[
		1.４～８桁の数字を入力する。
		2.未登録は、空白。
		3.消去方法は、番号選択時にクリアキーで一括消去。
		4.未登録場所でセットキーで番号選択表示。
		5.終了は番号選択表示にストップキー
		6.番号上書きセット後は番号選択表示
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/03]
	author		:[桑原美紀]
*************************************************************************/
UBYTE SetJunkMailDial(void)
{
	UBYTE	set_cnt;		/* 登録番号 */
	UBYTE	ret;

	/* セット番号の初期化 */
	OPR_Buf.JunkMailSelectNumber	= 0;

	while( 1 ){
		set_cnt	= GetJunkMailDialCount();				/* 件数をｶｳﾝﾄ */
		if( set_cnt > 0 ){		/* 登録番号存在時 */
			ret = SetJunkMailCodeSelect( set_cnt );		/* セット番号選択 */
			if(( ret == KEY_TIME_UP ) ||			/* 終了時 */
			   ( ret == STOP )){
/*				Del_BlockJunkDuplication();			/* 重複番号詰め */
				return( ret );
			}
		}
		/** ストップキーで初期画面に戻るように変更	97/09/16 By M.Kuwahara */
		if (SettingJunkMailDial() == NG) {		/* 部門コード登録 */
/*			Del_BlockJunkDuplication();			/* 重複番号詰め */
			return( STOP );
		}
		if( GetJunkMailDialCount() == 0 ){			/* １件も登録されずにｽﾄｯﾌﾟされた場合、初期画面に戻るようにする */
			return( STOP );
		}
	}
}

/*************************************************************************
	module		:[ジャンクメール防止ダイヤル登録番号選択の入力]
	function	:[
	]
	return		:[ キータイプ ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/03]
	author		:[桑原美紀]
*************************************************************************/
UBYTE				SetJunkMailCodeSelect(
						 UBYTE	SetMax)		/* セット番号最大値 */
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	set_no;
	UBYTE	loop;
	UBYTE	set_cnt;

	ClearCharacterInput();
	CharacterInput.WritePosition = 2;
	CharacterInput.LcdDisplayPosition = 0;
	set_cnt	= SetMax;
	while (1) {
		JunkMailSelectDisplay();				/* 表示処理 */
/*		CursorOn((UBYTE)(CharacterInput.LcdDisplayPosition + CharacterInput.CursorPosition + OPR_LCD_LOWER_ADD));*/

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
			return( keytype );
		case STOP:
			return( keytype );
		case ENTER:
			if (CharacterInput.CursorPosition > 0) {
				NackBuzzer();
			}
			else {
				return( keytype );
			}
			break;
		case FUNCTION:
			/* 選択番号を進める */
			if (CharacterInput.CursorPosition > 0) {
				/* 選択番号をテンキーで入力中 */
				NackBuzzer();
			}
			else {
				if((UBYTE)(OPR_Buf.JunkMailSelectNumber+1) > set_cnt ){	/* 最大値以上は進まない */
					OPR_Buf.JunkMailSelectNumber	= 0;
				}
				else{
					if((OPR_Buf.JunkMailSelectNumber+1) >= SYS_JUNK_DIAL_MAX ){	/* ｶｰｿﾙが最大件数目の時 */
						OPR_Buf.JunkMailSelectNumber	= 0;
					}
					else{
						OPR_Buf.JunkMailSelectNumber++;
					}
				}
			}
			break;
		case LEFT_ARROW:
			/* 選択番号を戻す */
			if (CharacterInput.CursorPosition > 0) {
				/* 選択番号をテンキーで入力中 */
				NackBuzzer();
			}
			else {
				if( OPR_Buf.JunkMailSelectNumber <= 0 ){	/* 最小値以下は進まない */
					if( set_cnt == SYS_JUNK_DIAL_MAX ){
						OPR_Buf.JunkMailSelectNumber	= set_cnt - (UBYTE)1;	/* add (UBYTE) 1997/06/25 Y.Matsukuma */
					}
					else{
						OPR_Buf.JunkMailSelectNumber	= set_cnt;
					}
				}
				else{
					OPR_Buf.JunkMailSelectNumber--;
				}
			}
			break;
		case CLEAR:
			/* ﾃﾞｰﾀ自体クリア */
			if (CharacterInput.CursorPosition > 0) {
				/* 選択番号をテンキーで入力中 */
/*				NackBuzzer();*/
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.CursorPosition] = NULL;
			}
			else {
				if( SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber][0] == 0xFF ){	/* データ無しの時 */
					NackBuzzer();
					break;
				}
				for (loop = OPR_Buf.JunkMailSelectNumber; loop < SYS_JUNK_DIAL_MAX; loop++ ){
					if( SYB_JunkMailProtectDialBuffer[loop][0] == 0xFF) {
						break;
					}
					CMN_StringCopyNum( &SYB_JunkMailProtectDialBuffer[loop][0], 
									   &SYB_JunkMailProtectDialBuffer[loop+1][0], 
									   SYS_JUNK_DIAL_NUMBER_MAX );
				}
				if( loop == SYS_JUNK_DIAL_MAX ){		/* 最大値のみ */
				 	SYB_JunkMailProtectDialBuffer[loop-1][0] = 0xFF;
				}
				CharacterInput.CursorPosition	= 0;
				if((set_cnt	= GetJunkMailDialCount()) == 0 ){					/* 件数をｶｳﾝﾄ */
					return(keytype);
				}
			}
			break;
		case NUMBER:
			if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {	/* 桁数オーバー(あり得ない) */
				NackBuzzer();
			}
			else {
				CharacterInput.Buffer[CharacterInput.CursorPosition++] = key;
				CharacterInput.Buffer[CharacterInput.CursorPosition] = NULL;

				if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {
					set_no	= (UBYTE)CMN_ASC_ToUnsignedInt( CharacterInput.Buffer,
														   	CharacterInput.CursorPosition);
					if(( set_no == 0 ) ||
					   ( set_no > SYS_JUNK_DIAL_MAX ) ||
					   ((set_no - (UBYTE)1) > set_cnt )){	/* add (UBYTE) 1997/06/25 Y.Matsukuma */
						NackBuzzer();
					}
					else {
						OPR_Buf.JunkMailSelectNumber = set_no - (UBYTE)1;	/* add (UBYTE) 1997/06/25 Y.Matsukuma */
					}
					CharacterInput.CursorPosition = 0;
				}
			}
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
	return( OK );
}

/*************************************************************************
	module		:[ジャンクメール防止ダイヤルの登録]
	function	:[]
	return		:[	OK:	正常終了
					NG: 異常終了（ＳＴＯＰキー）
]
	common		:[
		OPR_Buf:
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/06/03]
	author		:[桑原美紀]
*************************************************************************/
UBYTE			SettingJunkMailDial( void )
{
	UBYTE	is_new;			/* 新規/上書き入力 */
	UBYTE	i;
	UBYTE	loop;
	UBYTE	buffer[SYS_JUNK_DIAL_NUMBER_MAX];
	UBYTE	ret;

	if( SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber][0] == 0xFF ){	/* 新規入力か？ */
		is_new = 1;
	}
	else{
		is_new = 0;
	}

#if (0)
//	/* ワークエリア初期化 */
//	ClearCharacterInput();
//	CharacterInput.WritePosition = 0;
//	CharacterInput.MaxFigure = JUNK_CODE_MAX;
///	CharacterInput.LcdDisplayPosition = 3;
//	CMN_BCD_ToASC_String(CharacterInput.Buffer, 
//						 SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber]);
#endif
	CharacterInput.Buffer[0]	= NULL;
	while( 1 ){
		if((ret	= InputNumberRotation(OPR_JUNK_MAIL_NUMBER_INPUT)) == NG ){		/* ダイヤルの入力 */
/*			break;*/
			return( NG );
		}
		/*--------------------------------*/ /* 97/10/28 Add By M.Kuwahara */
		/* 入力された値のチェックを行う	  */
		/*--------------------------------*/
		if (CheckCharacterInputEmpty() != TRUE) { /* 入力されていない */
			/** チェック用のバッファにチェックする番号をセットする */
			SetToCheckBuffer(&CharacterInput.Buffer[0], NULL);
			if (CheckDirectDialNumberInput() == NG) {
				OPR_ChildErrorFlag = OPR_NO_ERROR;		/* エラーは表示させない */
				NackBuzzer();
				continue;
			}
		}
/*		i = (UBYTE)CMN_StringLength(CharacterInput.Buffer);		/* 文字数のｶｳﾝﾄ */
		i	= 0;
		for ( loop = 0; loop < JUNK_CODE_MAX; loop++ ) {		/* 数字のみｶｳﾝﾄを取る 98/01/29 By M.Kuwahara */
			if ( CMN_isdigit( CharacterInput.Buffer[loop] ) == 1 ) {
				i++;
			}
		}

		if( i == 0 ){							/* 全ての文字がクリアされた時,番号を詰める */
			for (loop = OPR_Buf.JunkMailSelectNumber; loop < SYS_JUNK_DIAL_MAX; loop++ ){
				if( SYB_JunkMailProtectDialBuffer[loop][0] == 0xFF) {
					break;
				}
				CMN_StringCopyNum( &SYB_JunkMailProtectDialBuffer[loop][0], 
								   &SYB_JunkMailProtectDialBuffer[loop+1][0], 
								   SYS_JUNK_DIAL_NUMBER_MAX );
			}
			if( loop == SYS_JUNK_DIAL_MAX ){		/* 最大値のみ */
			 	SYB_JunkMailProtectDialBuffer[loop-1][0] = 0xFF;
			}
			break;								/* 入力無しでセットされた時,選択画面へ */
		}
		else if (( i >= JUNK_CODE_MIN ) &&		/* 入力ＯＫの時 */
			     ( i <= JUNK_CODE_MAX )){
			/* 一件毎に重複チェックを行う	 97/11/07 By M.Kuwahara */
			CMN_MemorySet( buffer, SYS_JUNK_DIAL_NUMBER_MAX, 0xff );	
			CMN_ASC_ToBCD_String( buffer, CharacterInput.Buffer );
			if ( Del_BlockJunkDuplication( buffer, OPR_Buf.JunkMailSelectNumber ) == NG ) {	/* 重複番号チェック */
				NackBuzzer();
				ChildDisplayStringLow(D2W_SetSameNumber);	/* "ﾊﾞﾝｺﾞｳ ｶﾞ ﾄｳﾛｸｻﾚﾃｲﾏｽ" */
				continue;
			}

			CMN_MemorySet( &SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber][0], 
						   SYS_JUNK_DIAL_NUMBER_MAX, 
						   0xff );
			CMN_ASC_ToBCD_String( &SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber][0], 
								  CharacterInput.Buffer );
			if (OPR_Buf.JunkMailSelectNumber >= SYS_JUNK_DIAL_MAX - 1) {	 	/* 最大値 */
				OPR_Buf.JunkMailSelectNumber = 0;
 			}
			else {
				OPR_Buf.JunkMailSelectNumber++;
			}
			if( is_new == 0 ){			/* 上書き入力の時,選択画面へ */
				break;
			}
/*			CharacterInput.CursorPosition	= 0;		/* 97/11/07 By M.Kuwahara */
			CharacterInput.Buffer[0]	= NULL;
		}
		else{
			NackBuzzer();
		}
	}
	if( is_new == 1 ){				/* 新規入力の時 */
		OPR_Buf.JunkMailSelectNumber	= 0;
	}
	return( OK );
}

/*************************************************************************
	module		:[ジャンクメール防止ダイヤル選択表示]
	function	:[ジャンクメール防止ダイヤルの選択表示を行う。]
	return		:[なし]
	common		:[
		OPR_Buf:
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/06/03]
	author		:[桑原美紀]
*************************************************************************/
void 		JunkMailSelectDisplay(void)
{
	/* 上段「ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ 」*/
	/* 下段「001:                」「001:1234            」「1                  」*/

	CMN_StringCopy(FunctionDisplayBufferHigh,D2W_BlockJunkMailSelectNumber);		/*"ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ"*/
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/** 通常入力中 */
	if (CharacterInput.CursorPosition == 0) {
		/* 注）表示は001から始める */
		CMN_UnsignedIntToASC(CharacterInput.Buffer,
							 (UWORD)OPR_Buf.JunkMailSelectNumber + 1,
							 2,
							 '0');
		CMN_StringCopy(FunctionDisplayBufferLow, CharacterInput.Buffer);
		FunctionDisplayBufferLow[2] = ':';
		/** 部門コード番号を取り出し、ASCIIになおして表示バッファにコピー */
		if (SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber][0] != 0xFF) {	/* ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙが登録してあるか */
			CMN_BCD_ToASC_String(&FunctionDisplayBufferLow[3], 
								 SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber]);
		}
	}
	else {
		CMN_StringCopy(&FunctionDisplayBufferLow[0], CharacterInput.Buffer);
	}

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	ClearDisplayLow();
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙ数取得]
	function	:[
				ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙ登録数を取得する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/06/03]
	author		:[桑原]
*************************************************************************/
UBYTE GetJunkMailDialCount(void)
{
	UBYTE	i;

	for (i = 0; i < SYS_JUNK_DIAL_MAX; i++) {
		if( SYB_JunkMailProtectDialBuffer[i][0] == 0xff ){	/* 検索終了 */
			break;
		}
	}
	return(i);
}

/*************************************************************************
	module		:[ジャンクメール防止ダイヤル番号重複分削除]
	function	:[
	]
	return		:[
				]
	common		:[
				]
	condition	:[]
	comment		:[	ダイヤルセット終了時に重複分を削除していたのを、
					一件登録毎に同じコードが無いかチェックするように変更	* 97/11/07 By M.Kuwahara 
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/17]
	author		:[桑原美紀]
*************************************************************************/
#if (0)
//void	 Del_BlockJunkDuplication( void )
//{
//	UBYTE	point;		/* */
//	UBYTE	search;		/* 件数用ﾙｰﾌﾟ */
//	UBYTE	loop;		/* 文字列用ﾙｰﾌﾟ */
//	UBYTE	is_junk;	/* 文字列ﾁｪｯｸ用ﾌﾗｸﾞ */
//	UBYTE	buffer[SYS_JUNK_DIAL_NUMBER_MAX];	/* 検索BCD用ﾊﾞｯﾌｧ */
//	UBYTE	ret;
//
//	point	= 0;
//	while( point < SYS_JUNK_DIAL_MAX ){
//		if( SYB_JunkMailProtectDialBuffer[point][0] == 0xff ){	/* 検索終了 */
//			break;
//		}
//		CMN_StringCopyNum( buffer, &SYB_JunkMailProtectDialBuffer[point][0], SYS_JUNK_DIAL_NUMBER_MAX );
//		is_junk	= 0;
//		for( search = point + (UBYTE)1; search < SYS_JUNK_DIAL_MAX; search++ ){	/* add (UBYTE) 1997/06/25 Y.Matsukuma *///
//			if( SYB_JunkMailProtectDialBuffer[search][0] == 0xff ){
//				break;
//			}
//			/* ＢＣＤ形式の文字列の比較 */
//			ret = Check_BCD_StringCompare( buffer, &SYB_JunkMailProtectDialBuffer[search][0], JUNK_CODE_MAX );
//			if( ret == OK ){
//				is_junk	= 1;
//				break;
//			}
//		}
//		if( is_junk == 1 ){		/* 同じ文字列存在時 */
//			for( loop = search; loop < SYS_JUNK_DIAL_MAX; loop++ ){		/* 同じ文字列の所を詰める */
//				if( SYB_JunkMailProtectDialBuffer[loop][0] == 0xff ){	/* 移動終了 */
//					break;
//				}
//				CMN_StringCopyNum( &SYB_JunkMailProtectDialBuffer[loop][0], 
//								   &SYB_JunkMailProtectDialBuffer[loop+1][0], 
//								   SYS_JUNK_DIAL_NUMBER_MAX );
//			}
//			if( loop == SYS_JUNK_DIAL_MAX ){		/* 最大値のみ */
//			 	SYB_JunkMailProtectDialBuffer[loop-1][0] = 0xFF;
//			}
//		}		/* 同じ文字列が存在しない時 */
//		else{
//			point++;
//		}
//	}
//}
#endif

UBYTE	 Del_BlockJunkDuplication( 
				UBYTE	*Buffer,
				UBYTE	Point )
{
	UBYTE	point;		/* */
	UBYTE	search;		/* 件数用ﾙｰﾌﾟ */
	UBYTE	loop;		/* 文字列用ﾙｰﾌﾟ */
	UBYTE	is_junk;	/* 文字列ﾁｪｯｸ用ﾌﾗｸﾞ */
	UBYTE	buffer[SYS_JUNK_DIAL_NUMBER_MAX];	/* 検索BCD用ﾊﾞｯﾌｧ */
	UBYTE	ret;

	loop	= 0;
	while( loop < SYS_JUNK_DIAL_MAX ){
		if( SYB_JunkMailProtectDialBuffer[loop][0] == 0xff ){	/* 検索終了 */
			break;
		}
		if ( loop == Point ) {
			loop++;
			continue;
		}
		/* ＢＣＤ形式の文字列の比較 */
		ret = Check_BCD_StringCompare( Buffer, &SYB_JunkMailProtectDialBuffer[loop][0], JUNK_CODE_MAX );
		if( ret == OK ){
			return( NG );
		}
		loop++;
	}
	return( OK );	/* 1997/11/11 Y.Matsukuma */
}

/*************************************************************************
	module		:[ジャンクメール防止ダイヤルリスト]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/16]
	author		:[桑原美紀]
*************************************************************************/
UBYTE PrintBlockJunkList(void)
{
	UBYTE	junk_no;

	if (ConfirmKeyInputOperation(D2W_PrintBlockJunkMailDialList, D2W_EnterStop, ENTER, STOP) == CONFIRM_EXEC) {
	/* ジャンクメール専用ダイヤルテーブルをサーチ */
		for (junk_no = 0; junk_no < SYS_JUNK_DIAL_MAX; junk_no++) {
			if ( SYB_JunkMailProtectDialBuffer[junk_no][0] != 0xff ){
				FinalListPrintOperation(LST_BLOCK_JUNK_LIST); /* メインにリスト起動メッセージ送信 1995/04/04 Egu*/
				return(OK);
			}
		}
		/*登録データなし*/
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
		return( NG );
	}
	return( NG );
}

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
/*************************************************************************
	module		:[ジャンクメール防止ダイヤルリスト]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/12/28]
	author		:[藤村春夫]
*************************************************************************/
void PrintBlockJunkList2(void)
{
	UBYTE	junk_no;

	/* ジャンクメール専用ダイヤルテーブルをサーチ */
	for (junk_no = 0; junk_no < SYS_JUNK_DIAL_MAX; junk_no++) {
		if ( SYB_JunkMailProtectDialBuffer[junk_no][0] != 0xff ){
			FinalListPrintOperation(LST_BLOCK_JUNK_LIST); /* メインにリスト起動メッセージ送信 1995/04/04 Egu*/
			return;
		}
	}
	/*登録データなし*/
	NackBuzzer();
	OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
}
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/*************************************************************************
	module		:[保留メロディーセット]
	function	:[
		1.保留メロディーＯＮ／ＯＦＦ切り替え
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/06]
	author		:[福本貴吉]
*************************************************************************/
void SetHoldMelody(void)
{
	if (EnterSettingStatus(D2W_SelectHoldMelody,	/* "ﾎﾘｭｳﾒﾛﾃﾞｨｰ ｾｯﾄ :    " */
						   D2W_Off2,				/* "                OFF " */
						   2,
						   SETTING_STATUS_3,
						   OPR_VALID_CHECK_NOT_NEED,
						   HOLD_MELODY_ON) == OK) {
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_SettingHoldMelody[4]);	/* "    ﾎﾘｭｳﾒﾛﾃﾞｨｰ ｾｯﾄ  " */
		ChildDisplaySetCompleted(FunctionDisplayBufferHigh);					/* "ﾎﾘｭｳﾒﾛﾃﾞｨｰ ｾｯﾄ      " */
	}
}
#endif

#if (PRO_REMOTE_RX == ENABLE)
/*************************************************************************
	module		:[]
	function	:[
		1.リモート受信ＯＮ／ＯＦＦ切り替え
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＮＴＴ仕様のポプラＬ用に作成しました。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/01/26]
	author		:[福本貴吉]
*************************************************************************/
void SetRemoteReceive(void)
{
	if (EnterSettingStatus(D2W_SelectRemoteReceive,	/* "ﾘﾓｰﾄｼﾞｭｼﾝ      :    " */
						   D2W_Off2,				/* "                OFF " */
						   2,
						   SETTING_STATUS_23,
						   OPR_VALID_CHECK_NOT_NEED,
						   REMOTE_RX_ON) == OK) {
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_SettingRemoteReceive[4]);	/* "    ﾘﾓｰﾄｼﾞｭｼﾝ ｾｯﾄ   " */
		ChildDisplaySetCompleted(FunctionDisplayBufferHigh);						/* "ﾘﾓｰﾄｼﾞｭｼﾝ ｾｯﾄ       " */
	}
}
#endif

#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
/*************************************************************************
	module		:[オンフック受信ＯＮ／ＯＦＦ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＮＴＴ仕様のポプラＬ用に作成しました。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/13]
	author		:[福本貴吉]
*************************************************************************/
void SetOnHookReceive(void)
{
	if (EnterSettingStatus(D2W_SelectOnHookReceive,	/* "ｵﾝﾌｯｸ ｼﾞｭｼﾝ    :    " */
						   D2W_Off2,				/* "                OFF " */
						   2,
						   SETTING_STATUS_26,
						   OPR_VALID_CHECK_NOT_NEED,
						   ONHOOK_RX_ON) == OK) {
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_SettingOnHookReceive[4]);	/* "    ｵﾝﾌｯｸ ｼﾞｭｼﾝ ｾｯﾄ " */
		ChildDisplaySetCompleted(FunctionDisplayBufferHigh);						/* "ｵﾝﾌｯｸ ｼﾞｭｼﾝ         " */
	}
}
#endif

/*************************************************************************
	module		:[機器設定リスト]
	function	:[
		1.機器設定リストをプリントします
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/10]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
void PrintSettingList(void)
{
	FinalListPrintOperation(LST_PARAMETER_LIST);
}
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/08 */
void SetRemoteRxParameters(void)
{
	if (SetRemoteRxDialMumIssei() == NG){
		return;
	}
	if (SetRemoteRxDialMumKobetsu() == NG){
		return;
	}
	
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_SettingRemoteRxParameters[4]); 		/* "リモート特番設定         " */
	ChildDisplaySetCompleted(FunctionDisplayBufferHigh);
	return;
}

UBYTE SetRemoteRxDialMumIssei(void)
{
	UBYTE	key;
	UBYTE	keytype;	
	UBYTE	dial_code[2];
	UBYTE	memsw;
	
	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_Issei); 
	CMN_StringCopy(&FunctionDisplayBufferHigh[5], &D2W_SettingRemoteRxParameters[4]); 

	if (CHK_TEL2FaxTransferAvailable()) {	/* 外付け電話の転送受信機能 */
		if (CHK_RemoteTransferDial()) {			/* リモートダイアル転送を行うか(転送受信有効設定の時のみ有効) */
			/* リモートダイアル転送検出番号チェック */
			dial_code[0] = (SYS_MemorySwitch[MEMORY_SW_G9] & REMOTE_TRANSFER_DIAL_NUM1) >> 4;
			dial_code[1] = SYS_MemorySwitch[MEMORY_SW_G9] & REMOTE_TRANSFER_DIAL_NUM2;
		}
	}

	switch (dial_code[0]){
	case 7:
		CMN_StringCopy(&FunctionDisplayBufferHigh[16], "77"); 
		memsw = 7;
		break;
	case 8:
		CMN_StringCopy(&FunctionDisplayBufferHigh[16], "88"); 
		memsw = 8;
		break;
	case 9:
		CMN_StringCopy(&FunctionDisplayBufferHigh[16], "99"); 
		memsw = 9;
		break;
	default:
		CMN_StringCopy(&FunctionDisplayBufferHigh[16], "99"); 
		memsw = 9;
		break;
	}

	if (CHK_RemoteTransferDialOne()){
		FunctionDisplayBufferHigh[17] = ' ';
	}
	
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	
	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {
	
		/** キー取り込み */	
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
		
		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {		
		case FUNCTION:		/* 機能キー／右矢印キー*/
			switch(memsw){
				case 7:
					DisplayStringHigh(16, "88");
					memsw = 8;
					break;
				case 8:
					DisplayStringHigh(16, "99");
					memsw = 9;
					break;
				case 9:
					DisplayStringHigh(16, "77");
					memsw = 7;
					break;
				default:
					DisplayStringHigh(16, "99");
					memsw = 9;
					break;
			}
			
			if (CHK_RemoteTransferDialOne()){
				DisplayStringHigh(17, " ");
			}
			
			break;
		case LEFT_ARROW:	/* 左矢印キー */
			switch(memsw){
				case 7:
					DisplayStringHigh(16, "99");
					memsw = 9;
					break;
				case 8:
					DisplayStringHigh(16, "77");
					memsw = 7;
					break;
				case 9:
					DisplayStringHigh(16, "88");
					memsw = 8;
					break;
				default:
					DisplayStringHigh(16, "99");
					memsw = 9;
					break;
			}
			
			if (CHK_RemoteTransferDialOne()){
				DisplayStringHigh(17, " ");
			}
			
			break;
		case ENTER:
			SYS_MemorySwitch[MEMORY_SW_G9] = memsw | (memsw << 4);

			return (OK);
		case STOP:
		case KEY_TIME_UP:	
			return (NG);
			
		case NO_EFFECT:
			break;
			
		default:
			NackBuzzer();
			break;
		}
	}
}

UBYTE SetRemoteRxDialMumKobetsu(void)
{
	UBYTE	key;
	UBYTE	keytype;	
	UBYTE	dial_code[2];
	UBYTE	memsw;
	
	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_Kobetsu); 
	CMN_StringCopy(&FunctionDisplayBufferHigh[5], &D2W_SettingRemoteRxParameters[4]); 

	if (CHK_TEL2FaxTransferAvailable()) {	/* 外付け電話の転送受信機能 */
		if (CHK_RemoteTransferDial()) {			/* リモートダイアル転送を行うか(転送受信有効設定の時のみ有効) */
			/* リモートダイアル転送検出番号チェック */
			dial_code[0] = (SYS_MemorySwitch[MEMORY_SW_G7] & REMOTE_TRANSFER_DIAL_NUM1) >> 4;
			dial_code[1] = SYS_MemorySwitch[MEMORY_SW_G7] & REMOTE_TRANSFER_DIAL_NUM2;
		}
	}
	
	switch (dial_code[0]){
	case 1:
		CMN_StringCopy(&FunctionDisplayBufferHigh[16], "11"); 
		memsw = 1;
		break;
	case 2:
		CMN_StringCopy(&FunctionDisplayBufferHigh[16], "22"); 
		memsw = 2;
		break;
	case 3:
		CMN_StringCopy(&FunctionDisplayBufferHigh[16], "33"); 
		memsw = 3;
		break;
	default:
		CMN_StringCopy(&FunctionDisplayBufferHigh[16], "33"); 
		memsw = 3;
		break;
	}

	if (CHK_RemoteTransferDialOne()){
		FunctionDisplayBufferHigh[17] = ' ';
	}
	
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	
	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {
		/** キー取り込み */	
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
		
		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {		
		case FUNCTION:		/* 機能キー／右矢印キー*/
			switch(memsw){
				case 1:
					DisplayStringHigh(16, "22");
					memsw = 2;
					break;
				case 2:
					DisplayStringHigh(16, "33");
					memsw = 3;
					break;
				case 3:
					DisplayStringHigh(16, "11");
					memsw = 1;
					break;
				default:
					DisplayStringHigh(16, "33");
					memsw = 3;
					break;
			}
			
			if (CHK_RemoteTransferDialOne()){
				DisplayStringHigh(17, " ");
			}
			
			break;
		case LEFT_ARROW:	/* 左矢印キー */
			switch(memsw){
				case 1:
					DisplayStringHigh(16, "33");
					memsw = 3;
					break;
				case 2:
					DisplayStringHigh(16, "11");
					memsw = 1;
					break;
				case 3:
					DisplayStringHigh(16, "22");
					memsw = 2;
					break;
				default:
					DisplayStringHigh(16, "33");
					memsw = 3;
					break;
			}
			
			if (CHK_RemoteTransferDialOne()){
				DisplayStringHigh(17, " ");
			}
			
			break;
		case ENTER:
			SYS_MemorySwitch[MEMORY_SW_G7] = memsw | (memsw << 4);

			return (OK);
		case STOP:
		case KEY_TIME_UP:	
			return (NG);
			
		case NO_EFFECT:
			break;
			
		default:
			NackBuzzer();
			break;
		}
	}
}
#endif		/* End of (defined (KEISATSU)) */
