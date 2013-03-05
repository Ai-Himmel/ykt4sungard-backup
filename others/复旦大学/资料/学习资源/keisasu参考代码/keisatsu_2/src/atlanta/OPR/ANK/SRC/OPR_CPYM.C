/************************************************************************
*	System		: POPLAR_B
*	File Name	: OPR_CPYM.C
*	Author		: 渡辺一章
*	Date		: 1997/02/17
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: コピーオペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\sysmcopy.h"
#include	"\src\atlanta\define\sysscan.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\mntsw_g.h"		/* 仕様決定後削除します by K.Watanabe 1997/11/26 */
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\scn_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

#if (PRO_PRINT_TYPE == LED)
#include	"\src\atlanta\prt\ph3\define\prn_pro.h"
#include	"\src\atlanta\prt\ph3\ext_v\prn_tbl.h"
#endif

/* Prototype
#if (PRO_COPY_FAX_MODE == ENABLE)
UBYTE	CopyOperation(UBYTE, UBYTE, UBYTE);
void	CopyFaxKeyOperation(void);
void	CopyMagnifiDecreaseOperation(void);
void	CopyMagnifiIncreaseOperation(void);
void	CopyModeSetKeyOperation(void);
void	CopyNumberClearOperation(void);
void	MagnificationKeyOperation(UBYTE);
void	SortKeyOperation(UBYTE);
void	PaperSelectKeyOperation(void);
void	CopyResetKeyOperation(void);
void	CopyStartOperation(void);
void	CopyNumberKeyOperation(UBYTE);
void	ChangeNumberKeyInputMode(void);
UBYTE	CheckCopyMagnifiLimit(UWORD);
void	ResetCopyMagnifi(void);
void	ClearCopyParameter(void);
UBYTE	ClearCopyCassette(void);
UBYTE	ClearCopyMagnifi(void);
void	ClearCopyNumber(void);
UBYTE	CheckCopyToFaxChangeEnable(void);
UBYTE	CheckFaxToCopyChangeEnable(void);
void	CopyMagnificationOperation(UBYTE);
void	CopyReductionOperation(UBYTE);
void	GetNextManualPaperSize(void);
UBYTE	CheckCopyFileStatus(void);
void	SetCopyParameter(void);
UBYTE	GetDocumentSize(struct OPR_MAGNIFI_PAPER_TABLE_t *, UBYTE);
UBYTE	GetBookCopyDocumentSize(void);
void	ModifyCopyMagnifi(UBYTE);
UBYTE	GetADF_CopyMaxMagnifi(void);
#if (0)	/ by K.Watanabe 1997/12/25 /
//UBYTE	CheckCopyEnablePaperCombi(UBYTE, UBYTE);
#endif
UBYTE	CheckADF_CopyMagnifi(void);
UBYTE	CheckPossibleCopyReserve(void);
void	StopParamDispTask(void);
UBYTE	ConfirmCopyParam(void);
UBYTE	CheckChangeCassette(void);
UBYTE	CheckFixedMagnification(struct OPR_FIXED_MAGNIFI_TABLE_t *);
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)	/ By S.Fukui Jan.23,1998 /
void	ClearAutoCassetteAndMagnifi(void);
#endif
#endif	/ (PRO_COPY_FAX_MODE == ENABLE) /
*/

#if (PRO_COPY_FAX_MODE == ENABLE)
/*************************************************************************
	module		:[コピーオペレーション]
	function	:[
		1.
	]
	return		:[
		TRUE	:処理実行
		FALSE	:未処理
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/17]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CopyOperation(UBYTE key_code, UBYTE key_type, UBYTE last_key)
{
	UBYTE	old_casette;	/* カセット段数の退避用 */
	UBYTE	old_magnifi;	/* 倍率の退避用 */
	UBYTE	ret;			/* リターン値 */

	old_casette = OPR_CopyData.Cassette;	/* 現在のカセット段数を退避 */
	old_magnifi = OPR_CopyData.Reduction;	/* 現在の倍率を退避 */
	ret = TRUE;
	IsPriorityParamDisplay = TRUE;	/* コピーパラメーター表示を優先させます */

	switch (key_type) {
	case COPY_FAX:			/* コピー／ファクスキー		*/
		CopyFaxKeyOperation();
		break;
	case LEFT_ARROW:		/* 左矢印キー				*/
		CopyMagnifiDecreaseOperation();
		break;
	case FUNCTION:			/* 機能／右矢印キー			*/
		CopyMagnifiIncreaseOperation();
		break;
	case ENTER:				/* セットキー				*/
		CopyModeSetKeyOperation();
		break;
	case CLEAR:				/* クリアキー				*/
		CopyNumberClearOperation();
		break;
	case MAGNIFICATION:		/* 拡大キー					*/
	case REDUCTION:			/* 縮小キー					*/
		MagnificationKeyOperation(key_type);
		break;
	case SORT:				/* ソート・ダイヤル記号キー	*/
		SortKeyOperation(last_key);
		break;
	case PAPER_SELECT:		/* 用紙選択キー				*/
		PaperSelectKeyOperation();
		break;
	case COPY_RESET:		/* コピーリセットキー		*/
		CopyResetKeyOperation();
		break;
	case START:				/* スタートキー				*/
		CopyStartOperation();
		break;
	case NUMBER:			/* 数字キー（０～９）		*/
		CopyNumberKeyOperation(key_code);
		break;
	case SHARP:				/* テンキー ＃				*/
		ChangeNumberKeyInputMode();
		break;
	case NO_EFFECT:
		IsPriorityParamDisplay = FALSE;	/* コピーパラメーター表示を優先させません */
		break;
	case STOP:				/* ストップキー				*/
	case SINGLE:			/* 単一オペレーションキー	*/
	case HOOK:				/* フックキー				*/
	case KEY_TIME_UP:		/* キー待ちタイムオーバー	*/
	case ERROR_OPERATION:	/* 現在の状態では無効なキー	*/
	/* コピーモード専用でない機能は、オペレーションのメインで処理を行います */
		IsPriorityParamDisplay = FALSE;	/* コピーパラメーター表示を優先させません */
		ret = FALSE;
		break;
	default:
		NackBuzzer();
		IsPriorityParamDisplay = FALSE;	/* コピーパラメーター表示を優先させません */
		break;
	}

	/* コピー倍率入力値の確定処理 */
	if (((key_type == COPY_FAX) && (!CHK_ReadyModeCopy())) || (key_type == START)) {
		/* ファクスモードへの切り替え又は、スタートキーが押された時、コピー倍率を無条件に確定状態にします */
		OPR_CopyNumberInputFigure = 0;	/* 入力値を確定状態にします */
	}

	/* 動作中又は、エラー表示中のコピーパラメーターの割り込み表示制御 */
	if ((IsPriorityParamDisplay) && !(OPR_DispInfo & OPR_DSP_IDLE)) {	/* ｺﾋﾟｰﾊﾟﾗﾒｰﾀｰ表示を優先させる時(待機中は除く) */
		/* コピーパラメーター優先表示中の時は、一度止めます */
		StopParamDispTask();

		/* コピーパラメーター優先表示用タイマーを起動します */
		cre_tsk(&tskno_OPR_ParamDispTask, TSK_CMN_MAN_TIMER10MSTASK, &ParamDispTimer);
	}

	if ((OPR_CopyParamCheck == OPR_PARAM_CHK)			/* 用紙・倍率の確認必要ありの時 */
	 && ((old_casette != OPR_CopyData.Cassette)			/* 用紙選択が押された */
	  || (old_magnifi != OPR_CopyData.Reduction))) {	/* 倍率が変更された */
		OPR_CopyParamCheck = OPR_CHANGE_PARAM;	/* 用紙・倍率確認状態に、確認必要なしをセット */
	}

	return(ret);
}

/*************************************************************************
	module		:[コピー／ファクスキー　オペレーション]
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
	date		:[1997/02/19]
	author		:[渡辺一章]
*************************************************************************/
void CopyFaxKeyOperation(void)
{
	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		if (CheckCopyToFaxChangeEnable()) {	/* コピーモードからファクスモードに変更可能な時 */
			/* モードをファクスモードにする */
			SYB_SettingStatus[SETTING_STATUS_26] &= ~READY_MODE_COPY;

			/* コピーパラメーター優先表示を止めます */
			StopParamDispTask();
		}
	}
	else {						/* ファクスモードの時 */
		if (CheckFaxToCopyChangeEnable()) {	/* ファクスモードからコピーモードに変更可能な時 */
			/* モードをコピーモードにする */
			SYB_SettingStatus[SETTING_STATUS_26] |= READY_MODE_COPY;
		}
	}

	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/10
	** ＬＥＤの更新
	** 注）元々は OPR_Task()でしかコピー・ファクスの切り替えが出来なかったので、
	** 　　ＬＥＤの更新は OPR_Task()の最後でメインにメッセージを送っている所で、
	** 　　自然に行われていたので、ここでは行っていなかったが、TelOperation()では
	** 　　更新が行われないので、ここで更新する処理を追加します
	*/
	UpdateLED();

	IsPriorityParamDisplay = FALSE;	/* コピーパラメーター表示を優先させません */
}

/*************************************************************************
	module		:[コピー倍率　減少オペレーション]
	function	:[
		1.最小１％まで、１％ずつ倍率を減少させます
		2.最小縮小率（５０％）より小さくなったら、連続キー入力を禁止します
		3.最大拡大率（２００％）より大きい倍率の時、最大拡大率（２００％）に戻します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/25]
	author		:[渡辺一章]
*************************************************************************/
void CopyMagnifiDecreaseOperation(void)
{
	if (CheckCopyMagnifiLimit(OPR_CopyData.Reduction) == OPR_MAGNIFI_OVER) { /* 現在の倍率が、最大拡大率より大きい時 */
		/* 最大拡大率（２００％）より大きい倍率の時は、無条件に最大倍率まで戻します */
		OPR_CopyData.Reduction = OPR_COPY_MAGNIFICATION_MAX;
		ContinuousKeyInputEnable = TRUE;	/* 連続キー入力を許可します */
	}
	else {																	 /* 現在の倍率が、０～最大拡大率の間の時 */
		if (OPR_CopyData.Reduction > 1) {
			OPR_CopyData.Reduction--;

			/* 最小縮小率（５０％）より小さくなったらナックを鳴らし、有効範囲に戻されるまで連続キー入力を禁止します */
			if ((ContinuousKeyInputEnable == TRUE)
			 && (CheckCopyMagnifiLimit(OPR_CopyData.Reduction) == OPR_MAGNIFI_UNDER)) {
				NackBuzzer();
				ContinuousKeyInputEnable = FALSE;	/* 連続キー入力を禁止します */
				if (ContinuousKeyHit == TRUE) {	/* 連続キー入力中の時 */
					ContinuousKeyHit = FALSE;		/* 連続キー入力を停止します */
				}
			}

			/* 原稿表示をしている時は、濃度表示に戻します by K.Watanabe 1997/11/26 */
			IsMagnifiKeyInput = FALSE;	/* 拡大・縮小キー押下チェック用変数ＯＦＦ */
		}
		else {
			NackBuzzer();
		}
	}
}

/*************************************************************************
	module		:[コピー倍率　増加オペレーション]
	function	:[
		1.最大２５５％まで、１％ずつ倍率を増加させます
		2.最大拡大率（２００％）より大きくなったら、連続キー入力を禁止します
		3.最小縮小率（５０％）より小さい倍率の時、最小縮小率（５０％）に戻します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/25]
	author		:[渡辺一章]
*************************************************************************/
void CopyMagnifiIncreaseOperation(void)
{
	if (CheckCopyMagnifiLimit(OPR_CopyData.Reduction) == OPR_MAGNIFI_UNDER) { /* 現在の倍率が、０～最大縮小率の間の時 */
		/* 最小縮小率（５０％）より小さい倍率の時は、無条件に最小倍率まで戻します */
		OPR_CopyData.Reduction = OPR_COPY_REDUCTION_MIN;
		ContinuousKeyInputEnable = TRUE;	/* 連続キー入力を許可します */
	}
	else {																	  /* 現在の倍率が、最大縮小率より大きい時 */
		if (OPR_CopyData.Reduction < 0xFF) {
			OPR_CopyData.Reduction++;

			/* 最大拡大率（２００％）を超えたらナックを鳴らし、有効範囲に戻されるまで連続キー入力を禁止します */
			if ((ContinuousKeyInputEnable == TRUE)
			 && (CheckCopyMagnifiLimit(OPR_CopyData.Reduction) == OPR_MAGNIFI_OVER)) {
				NackBuzzer();
				ContinuousKeyInputEnable = FALSE;	/* 連続キー入力を禁止します */
				if (ContinuousKeyHit == TRUE) {	/* 連続キー入力中の時 */
					ContinuousKeyHit = FALSE;		/* 連続キー入力を停止します */
				}
			}

			/* 原稿表示をしている時は、濃度表示に戻します by K.Watanabe 1997/11/26 */
			IsMagnifiKeyInput = FALSE;	/* 拡大・縮小キー押下チェック用変数ＯＦＦ */
		}
		else {
			NackBuzzer();
		}
	}
}

/*************************************************************************
	module		:[コピーモード　セットキーオペレーション]
	function	:[
		1.用紙選択で、カセット→手差しに変更確認の時、手差しに変更します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/10]
	author		:[渡辺一章]
*************************************************************************/
void CopyModeSetKeyOperation(void)
{
	if (IsCassetteManualChange) {	/* カセット→手差しへの変更確認の時 */
		IsCassetteManualChange = FALSE;					/* 手差しに変更 */
		OPR_CopyData.Cassette = SYS_MANUAL_CASSETTE;	/* カセットに手差しをセット */

		/* 手差しの記録紙サイズを獲得します */
		PaperSelectKeyOperation();
	}
	else {							/* カセット又は、手差しが選択されている時 */
		NackBuzzer();
		IsPriorityParamDisplay = FALSE;	/* コピーパラメーター表示を優先させません */
	}
}

/*************************************************************************
	module		:[コピー部数クリア　オペレーション]
	function	:[
		1.コピー部数が入力されていた時は、初期値に戻します
		2.コピー部数が入力されていない時は、ナックを鳴らします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/23]
	author		:[渡辺一章]
*************************************************************************/
void CopyNumberClearOperation(void)
{
	/* コピー部数が初期値（１部・未入力）でない時、部数のクリアを行います */
	if ((OPR_NumberKeyInputMode == OPR_COPY_NUMBER_INPUT_MODE)
	 && ((OPR_CopyData.ReserveNumber != 1) || (OPR_CopyNumberInputFigure != 0))) {
		ClearCopyNumber();
	}
	else {
		NackBuzzer();
		IsPriorityParamDisplay = FALSE;	/* コピーパラメーター表示を優先させません */
	}
}

/*************************************************************************
	module		:[拡大・縮小キー　オペレーション]
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
	date		:[1997/03/24]
	author		:[渡辺一章]
*************************************************************************/
void MagnificationKeyOperation(UBYTE key_type)
{
	UBYTE	paper_size;	/* 選択されているカセットの記録紙サイズ */

	/** 選択されているカセットの記録紙サイズを獲得します */
	paper_size = GetPaperSize(OPR_CopyData.Cassette);

	if (key_type == MAGNIFICATION) {	/* 拡大キー */
		CopyMagnificationOperation(paper_size);
	}
	else {								/* 縮小キー */
		CopyReductionOperation(paper_size);
	}

	/* 連続キー入力が禁止の時（コピー倍率が適正範囲外）は、連続キー入力を許可状態に戻します */
	if (ContinuousKeyInputEnable == FALSE) {
		ContinuousKeyInputEnable = TRUE;	/* 連続キー入力を許可します */
	}

	/* 仕様決定後、どちらかのロジックにします */
	if (SYB_MaintenanceSwitch[MNT_SW_G8] & 0x02) {	/* 原稿サイズをチャイルド表示する時 */
		/** 表示用バッファの初期化 */
		CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

		/** 下段表示内容のセット */
		SetDocumentSize();									/* 記録紙・倍率に対する原稿サイズのセット */
		SetCassettePaperSize(&DisplayBufferLow[7]);			/* カセット段数・記録紙サイズのセット */
		SetCopyModeMagnification(&DisplayBufferLow[16]);	/* 倍率のセット */

		/** 上段の表示 */
		/* 注）コピー中にテンキー等が押されると、一時的に上下段ともコピーモードの表示を行っていますが、
		** 　　拡大・縮小・ソートキーだけは、下段のみをチャイルド表示していたため（コピー中のコピー予約
		** 　　がなかった時は、コピー中はキーを受け付けていなかったので上段を書き換える必要がなかった）、
		** 　　上段はコピー表示のままだったので、他と合わせて上段も表示します
		*/
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/18 */
		DisplayCopyModeHigh();
 #else
		DisplayCopyMode2();
 #endif

		/** 下段のチャイルド表示 */
		ParamChildDisplayStringLow(DisplayBufferLow);

		IsPriorityParamDisplay = FALSE;	/* コピーパラメーター表示を優先させません */
	}
	else {											/* 原稿サイズをそのまま表示する時 */
		IsMagnifiKeyInput = TRUE;	/* 拡大・縮小キー押下チェック用変数ＯＮ */
	}
}

/*************************************************************************
	module		:[ソートキー　オペレーション]
	function	:[
		1.ソートキーが連続して押された時は、ソート／ノンソートを切り替えます
		2.現在のソーティングの状態を表示します
		3.ソートキーが１回押されただけの時は、現在の状態を表示するだけで、
		　ソート／ノンソートの切り替えは行いません
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
void SortKeyOperation(UBYTE last_key)
{
	/* ソートキーが１回押されただけの時は、現在の状態を表示するだけです（ソーティングの切り替えは行いません）
	** ソートキーが連続して押された時は、ソート／ノンソートを押されるたびに切り替えます
	*/
	if (last_key == SORT_KEY) {	/* 連続してソートキーが押された時 */
		if (OPR_CopyData.SortType == SYS_NONE_SORT) {	/* ノンソートコピーの時 */
			OPR_CopyData.SortType = SYS_SORT;		/* ソートコピーをセット */
		}
		else {											/* ソートコピーの時 */
			OPR_CopyData.SortType = SYS_NONE_SORT;	/* ノンソートコピーをセット */
		}
	}

	/** 下段表示内容のセット */
	if (OPR_CopyData.SortType == SYS_NONE_SORT) {	/* ノンソートコピーの時 */
		CMN_StringCopy(FunctionDisplayBufferLow, D2W_Off1);				/* "                Off " */
	}
	else {											/* ソートコピーの時 */
		CMN_StringCopy(FunctionDisplayBufferLow, D2W_On1);				/* "                On  " */
	}
	CMN_StringCopy(FunctionDisplayBufferLow, D2W_SelectSortingCopy);	/* "ｿｰﾃｨﾝｸﾞｺﾋﾟｰ:        " */

	/** 上段の表示 */
	/* 注）コピー中にテンキー等が押されると、一時的に上下段ともコピーモードの表示を行っていますが、
	** 　　拡大・縮小・ソートキーだけは、下段のみをチャイルド表示していたため（コピー中のコピー予約
	** 　　がなかった時は、コピー中はキーを受け付けていなかったので上段を書き換える必要がなかった）、
	** 　　上段はコピー表示のままだったので、他と合わせて上段も表示します
	*/
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/18 */
	DisplayCopyModeHigh();
 #else
	DisplayCopyMode2();
 #endif

	/** 下段のチャイルド表示 */
	ParamChildDisplayStringLow(FunctionDisplayBufferLow);

	IsPriorityParamDisplay = FALSE;	/* コピーパラメーター表示を優先させません */
}

/*************************************************************************
	module		:[用紙選択キー　オペレーション]
	function	:[
		1.カセット又は、手差しの用紙を選択します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/21]
	author		:[渡辺一章]
*************************************************************************/
void PaperSelectKeyOperation(void)
{
	UBYTE	last_cassette;		/* 変更前のカセット段数 */
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)
	UBYTE	i;					/* カウンター 			*/
	UBYTE	valid_cassette_num;	/* 印刷可能なカセットをカウントする為 */
#endif

	if (OPR_CopyData.Cassette != SYS_MANUAL_CASSETTE) {	/* カセットが選択されている時 */
		if (IsCassetteManualChange) {	/* カセット→手差しへの変更確認の時 */
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)
			 /* ADFに原稿がセットされている時 ｶｾｯﾄ1 -> 自動選択 とします。
			 ** ﾃｻﾞｼ -> ｶｾｯﾄ 移行時に原稿有り検出期間(200ms)より短い間で抜き差しされるとAUTO表示残る為、
			 ** ２重確認とします。By S.Fukui Jan.23,1998
			 */
			if ((CMN_CheckDocumentOnFeeder() == TRUE) && (CMN_CheckDS1Status() == TRUE)) {
				/* カセットオプション(２段以上)あり、紙有りのカセットが２つ以上あれば自動カセット選択とする By S.Fukui Feb.19,1998 */
				valid_cassette_num = 0;
				for (i = PRN_1ST_CASSETTE; i <= PRN_3RD_CASSETTE; i++) {
					if ((*PaperSizeTable[i] != SYS_NO_PAPER) && (*PaperSizeTable[i] != SYS_NO_CASSETTE)) {
						valid_cassette_num++;
					}
				}
				if (valid_cassette_num > 1) {
					OPR_CopyData.Cassette = SYS_AUTO_CASSETTE;;
				}
			}
#endif
			IsCassetteManualChange = FALSE;	/* 手差しには変更されませんでした */
		}
		else {
			last_cassette = OPR_CopyData.Cassette;	/* 現在のカセット段数を退避しておきます */
			OPR_CopyData.Cassette++;				/* 次のカセットに進めます */

			/* 進めた次のカセットが存在するかどうかをチェックします */
			switch (OPR_CopyData.Cassette) {
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)
			case SYS_AUTO_CASSETTE:	/* 自動カセット選択 By S.Fukui Jan.23,1998 */
				break;
#endif
			case SYS_1ST_CASSETTE:	/* １段目カセット選択 */
				/* １段もカセットがない状態は考えません */
				break;
			case SYS_2ND_CASSETTE:	/* ２段目カセット選択 */
				if (!(SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_2ND_UNIT)) {	/* ２段目カセットが未装着の時 */
					OPR_CopyData.Cassette = SYS_1ST_CASSETTE;
				}
				break;
			case SYS_3RD_CASSETTE:	/* ３段目カセット選択 */
				if (!(SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_3RD_UNIT)) {	/* ３段目カセットが未装着の時 */
					OPR_CopyData.Cassette = SYS_1ST_CASSETTE;
				}
				break;
			default:
				OPR_CopyData.Cassette = SYS_1ST_CASSETTE;
				break;
			}

			/* 選択できるカセットが１周した時（カセットが１段しかない時も含む）は、手差しへの変更確認を行います */
			if (OPR_CopyData.Cassette <= last_cassette) {
				IsCassetteManualChange = TRUE;
			}
		}
	}
	else {												/* 手差しが選択されている時 */
		/* 次の手差しの記録紙サイズを獲得します */
		GetNextManualPaperSize();
	}

	if (!IsCassetteManualChange) {	/* カセット又は、手差しが選択されている時 */
		/* ＡＤＦに原稿がセットされていれば、倍率の変更を行います */
		ModifyCopyMagnifi(OPR_PAPER_SELECT);
	}
}

/*************************************************************************
	module		:[コピーリセットキー　オペレーション]
	function	:[
		1.コピーパラメータが変更されていた時は、初期値に戻します
		2.コピーパラメータが変更されていない時は、ナックを鳴らします
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
void CopyResetKeyOperation(void)
{
	/* コピーパラメータが初期値かを調べ、初期値でなかったらクリアをします */
	if ((OPR_CopyData.Cassette != ClearCopyCassette())					/* カセットの段数が変更されている		*/
#if (0)	/* 機種固有SWでソートの初期値を変更できるようになったので、初期値判断も変更します by K.Watanabe 1999/05/26 */
//	 || (OPR_CopyData.SortType != SYS_NONE_SORT)						/* ソートに設定されている				*/
#endif
	 || ((CHK_UNI_SortCopyOn()) && (OPR_CopyData.SortType != SYS_SORT))			/* 初期値ｿｰﾄでｿｰﾄでない			*/
	 || (!(CHK_UNI_SortCopyOn()) && (OPR_CopyData.SortType != SYS_NONE_SORT))	/* 初期値ﾉﾝｿｰﾄでﾉﾝｿｰﾄでない		*/
	 || (OPR_CopyData.Reduction != ClearCopyMagnifi())					/* 倍率が変更されている					*/
	 || (OPR_CopyData.ReserveNumber != 1)								/* 部数が１部でない						*/
	 || (OPR_CopyNumberInputFigure != 0)								/* 部数・倍率が未入力でない				*/
#if (0)	/* コピーモードでも画質の初期値を変更できるようにします by K.Watanabe 1999/01/21 */
//	 || ((!CHK_UNI_HyperFineON()) && (SYB_CopyModeSw != SYS_SFINE))		/* 画質が初期値でない（ｽｰﾊﾟｰﾌｧｲﾝ）		*/
//	 || ((CHK_UNI_HyperFineON()) && (SYB_CopyModeSw != SYS_HFINE))		/*                   （ﾊｲﾊﾟｰﾌｧｲﾝ）		*/
#endif
	 || (SYB_CopyModeSw != CHK_UNI_CopyPrimaryMode())					/* 画質が初期値でない					*/
	 || (SYB_CopyDensitySw != CHK_PrimaryDensity())						/* 濃度が初期値でない					*/
	 || (OPR_NumberKeyInputMode != OPR_COPY_NUMBER_INPUT_MODE)			/* 部数入力モードでない					*/
	 || (IsCassetteManualChange)										/* カセット→手差しへの変更確認中		*/
	 || (IsMagnifiKeyInput)) {											/* 拡大・縮小キーが押されている			*/
		ClearCopyParameter();
	}
	else {
#if (0)	/* by K.Watanabe 1997/12/16 */
//		/* コピー中は、コピーパラメーターの初期化をしていなくても、プリント中の表示を止めて
//		** コピーパラメーターの表示をさせます（コピー予約の仕様追加により）
//		*/
//		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_MULTI_COPY)				/* マルチコピー中でない	*/
//		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_MANUAL_COPY)) {	/* 手差しコピー中でない	*/
//			NackBuzzer();
//			IsPriorityParamDisplay = FALSE;	/* コピーパラメーター表示を優先させません */
//		}
#endif
		/* 実際には、コピーパラメーターの初期化をしなくても、コピーパラメーターの表示をさせます
		** （エラー中にパラメータの確認を行う時に、これがないと何かの値を変更しないと確認できなかったため）
		*/
		NackBuzzer();
	}
}

/*************************************************************************
	module		:[コピースタート　オペレーション]
	function	:[
		1.コピーが行える状態かをチェックし、ＯＫならコピーを開始します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/19]
	author		:[渡辺一章]
*************************************************************************/
void CopyStartOperation(void)
{
	UBYTE	chk_copy_magnifi;	/* ＡＤＦコピーで、倍率確認の結果 */

	/* エラー表示中にコピーが開始されたら、記録紙サイズ・倍率の確認をする仕様に変わりました
	** しかし、ＡＤＦコピーで倍率確認を行った時には必要ないので判断用に変数を追加しました
	** by K.Watanabe 1997/12/10
	*/
	chk_copy_magnifi = OPR_MAGNIFI_CHK_OK;

	/* コピー部数のチェック */
	if (OPR_CopyData.ReserveNumber == 0) {	/* 部数が０でスタートが押された時 */
		ClearCopyNumber();
		NackBuzzer();
		return;
	}

	/* コピー倍率のチェック */
	if (CheckCopyMagnifiLimit(OPR_CopyData.Reduction) != OPR_MAGNIFI_OK) {	/* コピー倍率が適正範囲外の時 */
		NackBuzzer();
		return;
	}

	/* コピー管理テーブル　ステータスチェック */
	if (CheckCopyFileStatus() == FALSE) {	/* コピーの予約が一杯で、コピー不可能な時 */
		NackBuzzer();
		return;
	}

 #if (0)	/* コピー以外のプリント中の時は、原稿の読み取りは行う必要があるので、プリント中のチェックをはずします */
 //	/* プリント可能かのチェック（記録紙の有無・プリンターエラー・プリント中） */
 //	if (CheckPrintOperationEnable() == FALSE) {
 //		/* NackBuzzer()は、チェック関数の中で鳴らしています */
 //		return;
 //	}
 #endif
	/* プリント可能かのチェック（記録紙の有無） */
	/* 注）記録紙の有無は、手差しでは無関係です（ＡＤＦ・ＦＢＳ共に指定のカセットからのみ引き当て） */
	if ((OPR_CopyData.Cassette != SYS_MANUAL_CASSETTE) && (GetPaperSize(OPR_CopyData.Cassette) == SYS_NO_PAPER)) {
		NackBuzzer();
		return;
	}

	/* プリント可能かのチェック（プリンターエラー） */
	if (CMN_CheckPrinterError() == TRUE) {
		NackBuzzer();
		return;
	}

	/* スキャナーが使用可能かのチェック */
	if (CheckScanStartEnable(OPR_DOC_SET_NO_CHK) != OPR_SCAN_ENABLE) {

#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/21 */
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {
			/* 待機状態表示へ戻す T.Nose 1999/01/25 */
			IsPriorityParamDisplay = FALSE;
			StopParamDispTask();
		}
#endif

		NackBuzzer();
		return;
	}

	/* メモリオーバーやＪＡＭが起こっている時は、読み取りを禁止します *//* Add By O.Kimoto 1999/07/19 */
	if ((CheckMemoryOver() == TRUE) || (CheckScanDisableCondition() == TRUE)) {
		NackBuzzer();
		return;
	}

	/* コピー中のカセットの記録紙がなくなった場合は、コピー予約を禁止します */
	if (CheckPossibleCopyReserve() == FALSE) {
		NackBuzzer();
		return;
	}

	/* ＡＤＦコピー時のチェック */
	if (CMN_CheckDocumentOnFeeder() == TRUE) {	/* ＡＤＦに原稿がセットされている時 */
		/* ＡＤＦに原稿があっても、DS2()がONしている時（読み取り途中でのメモリオーバー等）は、
		** 原稿の読み取りを行いません
		*/
		if (CMN_CheckScanDocOnFeeder() == FALSE) {	/* ＡＤＦに読み取り可能な原稿がセットされていない時 */
			NackBuzzer();
			return;
		}

		/* 通常コピー不可能な組み合わせの時（B4->ﾊｶﾞｷ等）は、倍率が０％（---%）になっているので
		** コピー倍率のチェックでエラーになりますが、倍率だけを変更されてスタートされると、
		** 倍率チェックはＯＫなので倍率確認のオペレーションに入ってしまうので、先に原稿サイズ・
		** 記録紙サイズを元にコピー可能かをチェックします
		*/
#if (0)	/* by K.Watanabe 1997/12/25 */
//		if (CheckCopyEnablePaperCombi(CMN_GetDocumentScanSize(), GetPaperSize(OPR_CopyData.Cassette)) == FALSE) {
//			/* コピー不可能な組み合わせの時 */
//			NackBuzzer();
//			return;
//		}
#endif
		/* Ａ４→ハガキもコピー禁止になり（実際は５０％以下なので）、結局ＡＤＦからハガキにはコピー
		** できなくなった為に、テーブルを使用してのチェックは必要ないので、サイズだけで判断します
		*/
		if (GetPaperSize(OPR_CopyData.Cassette) == SYS_POST_PAPER) {	/* コピー不可能な組み合わせの時 */
			NackBuzzer();
			return;
		}

		/* 設定されている倍率が、コピー可能最大倍率を超えている時は、倍率の確認を行います */
		chk_copy_magnifi = CheckADF_CopyMagnifi();
		if (chk_copy_magnifi == OPR_MAGNIFI_CHG_NG) {	/* 倍率確認で中止・タイムアップの時 */
			return;
		}
	}

	if ((chk_copy_magnifi == OPR_MAGNIFI_CHK_OK)	/* ＡＤＦコピーで倍率確認を行っていない時 */
	 && (OPR_CopyParamCheck == OPR_PARAM_CHK)) {	/* 用紙・倍率の確認必要ありの時 */
		if (ConfirmCopyParam() == OPR_END) {	/* 用紙・倍率確認の中止・タイムアップの時 */
			return;
		}
	}

	/* 今回は、エラー後に用紙・倍率を変更していて倍率確認がなかっても、次のコピー開始時に
	** エラーが残っていれば、倍率確認を行います（今回行った、用紙・倍率変更は無効です）
	*/
	OPR_CopyParamCheck = OPR_NO_PARAM_CHK;	/* 用紙・倍率確認状態に、確認必要なしをセット */

	/* コピーパラメータのセット */
	SetCopyParameter();

	/* メインタスクにマルチコピー起動メッセージを送信 */
	snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
	MainTaskExecWait();

#if (0)	/* by K.Watanabe 1997/12/17 */
	/* 待機状態からスタートキーを押した時に、コピーパラメーター優先表示用タイマーを起動してしまうと、
	** すぐに原稿読み取り中の表示をしてくれないので、タイマーの起動を禁止します
	** 注）原稿読み取り中の表示の所で、タイマーを無視してしまうと、読み取り中に数字キー等が押されても
	** 　　表示が更新されなくなってしまうので、こうします
	** by K.Watanabe 1997/11/14
	*/
	if (OPR_DispInfo & OPR_DSP_IDLE) {	/* 動作中・エラー中でなく、コピーパラメーター表示をしている時 */
		IsPriorityParamDisplay = FALSE;	/* コピーパラメーター表示を優先させません */
	}
#endif
}

/*************************************************************************
	module		:[コピー数字キー入力オペレーション]
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
	date		:[1997/02/20]
	author		:[渡辺一章]
*************************************************************************/
void CopyNumberKeyOperation(UBYTE key_code)
{
	UWORD	input_magnifi;	/* コピー倍率入力値 */

	if (OPR_NumberKeyInputMode == OPR_COPY_NUMBER_INPUT_MODE) {	/* コピー部数入力モードの時 */

		/* コピー倍率が適正範囲外の時は、上段はエラー表示のため、部数の入力を行っても
		** 表示できないので、コピー倍率が適正範囲内になるまでは、部数の入力を禁止します
		*/
		if (CheckCopyMagnifiLimit(OPR_CopyData.Reduction) != OPR_MAGNIFI_OK) {
			NackBuzzer();
			return;
		}

		OPR_CopyNumberInputFigure++;
		switch (OPR_CopyNumberInputFigure) {
		case 1:		/* １桁目の入力 */
			OPR_CopyData.ReserveNumber = (UBYTE)(key_code - TEN_0_KEY);
			break;
		case 2:		/* ２桁目の入力 */
			OPR_CopyData.ReserveNumber = (UBYTE)((OPR_CopyData.ReserveNumber * 10) + (key_code - TEN_0_KEY));
			break;
		default:	/* 最大桁数以上の入力 */
			NackBuzzer();
			ClearCopyNumber();
			break;
		}
	}
	else {														/* コピー倍率入力モードの時 */
		OPR_CopyNumberInputFigure++;
		switch (OPR_CopyNumberInputFigure) {
		case 1:		/* １桁目の入力 */
			OPR_CopyData.Reduction = (UBYTE)(key_code - TEN_0_KEY);
			break;
		case 2:		/* ２桁目の入力 */
			OPR_CopyData.Reduction = (UBYTE)((OPR_CopyData.Reduction * 10) + (key_code - TEN_0_KEY));
			break;
		case 3:		/* ３桁目の入力 */
			/* 注）OPR_CopyData.Reduction(SYS_MultiCopyData_tのReduction)がBYTEで定義されているため、
			** 　　入力値によりOverFlowを起こすので、一時的にWORDの変数にセットします
			*/
			input_magnifi = (OPR_CopyData.Reduction * 10) + (key_code - TEN_0_KEY);

			/* 倍率が適正範囲内かどうかを調べます */
			if (CheckCopyMagnifiLimit(input_magnifi) == OPR_MAGNIFI_OK) {	/* 適正範囲内の時 */
				OPR_CopyData.Reduction = (UBYTE)input_magnifi;
			}
			else {															/* 適正範囲外の時 */
				NackBuzzer();
				ResetCopyMagnifi();	/* 入力前の倍率に戻します */
			}
			break;
		default:	/* 最大桁数以上の入力 */
			NackBuzzer();
			ResetCopyMagnifi();	/* 入力前の倍率に戻します */
			break;
		}
	}
}

/*************************************************************************
	module		:[テンキー入力モード変更処理]
	function	:[
		1.テンキーが入力された時の入力内容を変更します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/06]
	author		:[渡辺一章]
*************************************************************************/
void ChangeNumberKeyInputMode(void)
{
	if (OPR_NumberKeyInputMode == OPR_COPY_NUMBER_INPUT_MODE) {	/* コピー部数入力モード */
		OPR_NumberKeyInputMode = OPR_COPY_MAGNIFI_INPUT_MODE;	/* コピー倍率入力モードに変更 */

		/* コピー倍率入力で、適正範囲外が入力された時のために、現在の倍率を覚えておきます */
		OPR_OldMagnification = OPR_CopyData.Reduction;

		/* 原稿表示をしている時は、濃度表示に戻します by K.Watanabe 1997/11/26 */
		IsMagnifiKeyInput = FALSE;	/* 拡大・縮小キー押下チェック用変数ＯＦＦ */
	}
	else {														/* コピー倍率入力モード */
		/* コピー倍率が入力途中で適正範囲外の時は、倍率を入力前の値に戻します */
		if ((OPR_CopyNumberInputFigure != 0) && (CheckCopyMagnifiLimit(OPR_CopyData.Reduction) != OPR_MAGNIFI_OK)) {
			NackBuzzer();
			ResetCopyMagnifi();	/* 入力前の倍率に戻します */
		}
		/* コピー倍率が入力されていないか、適正範囲内の時は、入力モードを切り替えます */
		else {
			OPR_NumberKeyInputMode = OPR_COPY_NUMBER_INPUT_MODE;	/* コピー部数入力モードに変更 */

			/* 倍率が"---%"（ＡＤＦに原稿セットかつ記録紙なしのカセット選択）の状態で、
			** 倍率入力モードに切り替え、記録紙だけ補給して、部数入力モードに戻した時に、
			** 倍率がそのままなのはまずいので、セットするようにします
			** by K.Watanabe 1998/09/09
			*/
			if (OPR_CopyData.Reduction == 0) {
				OPR_CopyData.Reduction = ClearCopyMagnifi();	/* 倍率の初期化 */
			}
		}

		/* コピー倍率を適正範囲外から適正範囲内にした時、連続キー入力を許可状態に戻しておきます
		** 注）ここで適正範囲外なのは、もともと適正範囲外の状態で倍率入力モードにした時のみです
		*/
		if (CheckCopyMagnifiLimit(OPR_CopyData.Reduction) == OPR_MAGNIFI_OK) {
			if (ContinuousKeyInputEnable == FALSE) {
				ContinuousKeyInputEnable = TRUE;	/* 連続キー入力を許可します */
			}
		}
	}
	OPR_CopyNumberInputFigure = 0;	/* 入力値を確定状態にします */
}

/*************************************************************************
	module		:[コピー倍率範囲内検査]
	function	:[
		1.コピー倍率が適正範囲内かどうかを調べます
	]
	return		:[
		OPR_MAGNIFI_OK		:適正範囲内
		OPR_MAGNIFI_UNDER	:適正範囲より小さい
		OPR_MAGNIFI_OVER	:適正範囲より大きい
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/06]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckCopyMagnifiLimit(UWORD copy_magnifi)
{
	UBYTE	ret;

	ret = OPR_MAGNIFI_OK;

	/* 倍率が最小倍率（５０％）より小さいかのチェック */
	if (copy_magnifi < OPR_COPY_REDUCTION_MIN) {
		ret = OPR_MAGNIFI_UNDER;
	}

	/* 倍率が最大倍率（２００％）より大きいかのチェック */
	if (copy_magnifi > OPR_COPY_MAGNIFICATION_MAX) {
		ret = OPR_MAGNIFI_OVER;
	}

	return(ret);
}

/*************************************************************************
	module		:[コピー倍率リセット]
	function	:[
		1.コピー倍率を前の倍率に戻します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/06]
	author		:[渡辺一章]
*************************************************************************/
void ResetCopyMagnifi(void)
{
	OPR_CopyData.Reduction = OPR_OldMagnification;	/* コピー倍率					*/
	OPR_CopyNumberInputFigure = 0;					/* コピー倍率入力桁数（未入力）	*/
}

/*************************************************************************
	module		:[コピーパラメータ　クリア]
	function	:[
		1.コピーモード用の設定値を初期化します
	]
	return		:[なし]
	common		:[]
	condition	:[
		コピー画質の初期化　→　機種固有スイッチを参照
		コピー濃度の初期化　→　機器設定の値を参照
		のため、必ずCMN_InitializeAllBackUpRAM()が実行された後、
		この関数をCallすること

		コピー倍率を初期値に戻すので、連続キー入力が合わせて許可状態に戻します
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/20]
	author		:[渡辺一章]
*************************************************************************/
void ClearCopyParameter(void)
{
	OPR_CopyData.Cassette		= ClearCopyCassette();			/* 自動／各段カセット							*/
	OPR_CopyData.ManualSelect	= YES;							/* 手動でカセット選択されたか（Ｙｅｓ）			*/
	/*ソートコピーの初期値をUNISWで変更できるようにする By Y.Suzuki 1999/02/15 */
	if (CHK_UNI_SortCopyOn()) {
		OPR_CopyData.SortType	= SYS_SORT;
	}
	else {
		OPR_CopyData.SortType	= SYS_NONE_SORT;				/* ソート／ノンソート（ノンソート）				*/
	}
	OPR_CopyData.Reduction		= ClearCopyMagnifi();			/* 倍率											*/
	OPR_CopyData.OHPMode		= FALSE;						/* ＯＨＰモード（オフ：記録紙）					*/
	ClearCopyNumber();											/* コピー部数のクリア							*/
	CMN_ResetPrimaryCopyMode();									/* コピー画質の初期化							*/
	CMN_ResetPrimaryCopyContrast();								/* コピー濃度の初期化							*/
	SYS_ManualPaperSize			= SYS_NO_PAPER;					/* 手差し記録紙サイズ（記録紙なし）				*/
	ContinuousKeyInputEnable	= TRUE;							/* 連続キー入力を許可します						*/
	OPR_NumberKeyInputMode		= OPR_COPY_NUMBER_INPUT_MODE;	/* テンキー入力モード（コピー部数入力モード）	*/
	IsCassetteManualChange		= FALSE;						/* 用紙選択時　カセット／手差しの切り替え用		*/
	IsMagnifiKeyInput			= FALSE;						/* 拡大・縮小キー押下チェック用					*/
	OPR_FixedMagnifiDocSize		= SYS_NO_PAPER;					/* 固定倍率原稿サイズ							*/
}

/*************************************************************************
	module		:[カセット段数初期化]
	function	:[
		1.ＡＤＦに原稿がセットされている時は、原稿サイズと記録紙サイズから
		　等倍に近い倍率でコピーできる記録紙のカセット段数を返します
		2.ＦＢＳに原稿がセットされている時は、カセットの１段目から順番に
		　記録紙がセットされているかを調べ、セットされていればそのカセットの
		　段数を返します
		　もし全てのカセットの記録紙がなかった場合は、１段目を返します
	]
	return		:[
		記録紙がセットされているカセット段数
			SYS_1ST_CASSETTE:	１段目カセット
			SYS_2ND_CASSETTE:	２段目カセット
			SYS_3RD_CASSETTE:	３段目カセット
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/27]
	author		:[渡辺一章]
*************************************************************************/
UBYTE ClearCopyCassette(void)
{
	UBYTE	ret;	/* リターン値 */
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)
	UBYTE	i;					/* カウンター 			*/
	UBYTE	valid_cassette_num;	/* 印刷可能なカセットをカウントする為 */
#endif

	if (CMN_CheckDocumentOnFeeder() == TRUE) {	/* ADFに原稿がセットされている時 */
		/* 原稿サイズとカセットの記録紙サイズを元に、等倍に近い倍率でコピーできる記録紙のカセットを獲得します */
		ret = PRN_GetPrintCassette(CMN_GetDocumentScanSize());
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)
		/* 自動カセット選択 	By S.Fukui Jan.23,1998 */
		/* カセットオプション(２段以上)あり、紙有りのカセットが２つ以上あれば自動カセット選択とする By S.Fukui Feb.19,1998 */
		valid_cassette_num = 0;
		for (i = PRN_1ST_CASSETTE; i <= PRN_3RD_CASSETTE; i++) {
			if ((*PaperSizeTable[i] != SYS_NO_PAPER) && (*PaperSizeTable[i] != SYS_NO_CASSETTE)) {
				valid_cassette_num++;
			}
		}
		if (valid_cassette_num > 1) {
			ret = SYS_AUTO_CASSETTE;
		}
#endif
	}
	else {										/* ﾌﾞｯｸに原稿がセットされている（ADFに原稿がｾｯﾄされていない）時 */
		ret = SYS_1ST_CASSETTE;

		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {	/* １段目ｶｾｯﾄ記録紙なし */
			if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_2ND_UNIT) {		/* ２段目ｶｾｯﾄが装着されている時 */
				if (!(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2)) {/* ２段目ｶｾｯﾄ記録紙あり */
					ret = SYS_2ND_CASSETTE;
				}
				else {																	/* ２段目ｶｾｯﾄ記録紙なし */
					if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_3RD_UNIT) {		/* ３段目ｶｾｯﾄが装着されている時 */
						if (!(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER3)) {/* ３段目ｶｾｯﾄ記録紙あり */
							ret = SYS_3RD_CASSETTE;
						}
					}
				}
			}
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[コピー倍率初期化]
	function	:[
		1.ＡＤＦに原稿がセットされている時は、原稿サイズと記録紙サイズから
		　コピー可能最大倍率を求め、等倍以下の倍率を返します
		2.ＦＢＳに原稿がセットされている時は、１００％を返します
	]
	return		:[コピー倍率]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/11]
	author		:[渡辺一章]
*************************************************************************/
UBYTE ClearCopyMagnifi(void)
{
	UBYTE	ret;	/* リターン値 */

	if (CMN_CheckDocumentOnFeeder() == TRUE) {	/* ADFに原稿がセットされている時 */
		/* 原稿サイズと記録紙サイズから、コピーできる最大の倍率を獲得します */
		ret = GetADF_CopyMaxMagnifi();

		/* 最大倍率が１００％より大きい時は、１００％をセットします */
		if (ret > 100) {
			ret = 100;
		}
	}
	else {										/* ﾌﾞｯｸに原稿がセットされている（ADFに原稿がｾｯﾄされていない）時 */
		ret = 100;
	}

	return(ret);
}

/*************************************************************************
	module		:[コピー部数クリア]
	function	:[
		1.コピー部数をクリアします
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
void ClearCopyNumber(void)
{
	OPR_CopyData.ReserveNumber = 1;	/* 指定部数（１部）				*/
	OPR_CopyNumberInputFigure = 0;	/* コピー部数入力桁数（未入力）	*/
}

/*************************************************************************
	module		:[コピーモードからファクスモードへ切り替え可能か否か]
	function	:[
		1.コピーモードからファクスモードへ切り替え可能かを調べます
	]
	return		:[
		TRUE	:コピーモード → ファクスモードへ切り替え可能
		FALSE	:コピーモード → ファクスモードへ切り替え不可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/19]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckCopyToFaxChangeEnable(void)
{
	/* 手差しコピー中は、切り替え不可能 */
	if (((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)
	  && (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE))
	 || (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_MANUAL_COPY)) {
		/* 注）手差しの原稿読み取り中は、SYS_MANUAL_COPYのステータスはまだ立っていません
		** 　　上記、判断は if (SYB_ManualCopyFile.Status != SYS_MCOPY_EMPTY) { だけでも可能です
		*/
		NackBuzzer();
		OPR_ChildErrorFlag = NOT_COMPLETE_COPY_ERROR;	/* "ｺﾋﾟｰ ｶﾝﾘｮｳ ｼﾃｲﾏｾﾝ   " */
		return(FALSE);
	}
	return(TRUE);
}

/*************************************************************************
	module		:[ファクスモードからコピーモードへ切り替え可能か否か]
	function	:[
		1.ファクスモードからコピーモードへ切り替え可能かを調べます
	]
	return		:[
		TRUE	:ファクスモード → コピーモードへ切り替え可能
		FALSE	:ファクスモード → コピーモードへ切り替え不可能
	]
	common		:[]
	condition	:[]
	comment		:[
		注）この関数の内容を変更した時は、
			・MAN_AutoReadyModeChangeEnable()の、ファクスモードからコピーモードに
			　自動切替できるかをチェックしている所
			・MAN_InitializeRAM()の待機モードの初期化をしている所
			も合わせて変更する事
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/19]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckFaxToCopyChangeEnable(void)
{
	/* 原稿蓄積中で次原稿ありの時は、切り替え不可能 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) && (SYS_NextBookDocument == TRUE)) {
		NackBuzzer();
		OPR_ChildErrorFlag = NOT_COMPLETE_STORED_ERROR;		/* "ﾁｸｾｷ ｶﾝﾘｮｳ ｼﾃｲﾏｾﾝ   " */
		return(FALSE);
	}

	/* コピー禁止中は、切り替え不可能 */
	if (CHK_CopyProtectON()) {
		NackBuzzer();
		OPR_ChildErrorFlag = COPY_PROTECT_ERROR;			/* "ｺﾋﾟｰｷﾝｼ ﾁｭｳﾃﾞｽ      " */
		return(FALSE);
	}

	/* ミラーキャリッジ輸送モード中は、切り替え不可能
	** （コピーモードに入ってしまうと、パラメーター変更できないキーだけを弾くようにするか、
	** 　輸送モード表示中でもエラー表示中と同じ扱いにして、数秒間だけパラメーター表示を行うか等
	** 　仕様がややこしくなるので、ここでモード変更事体を禁止してしまいます）
	** by K.Watanabe 1997/12/26
	*/
	if (SYB_ScannerTransportMode == TRUE) {
		NackBuzzer();
		return(FALSE);
	}

	return(TRUE);
}

/*************************************************************************
	module		:[固定倍率　拡大処理]
	function	:[
		1.１１５％から順番に固定倍率（１００％～２００％）に拡大します
		2.２００％になったら１００％に戻します
		3.変更した固定倍率と選択されているカセットの記録紙サイズより
		  該当する原稿サイズがあるかを調べる
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
void CopyMagnificationOperation(UBYTE paper_size)
{
	UBYTE	magnifi_cnt;	/* 固定倍率テーブルの配列番号 */

	/* （特許対策）
	** 現在の倍率から一番近い固定倍率にしてはいけないので、固定倍率以外で拡大キーを押された時は、
	** 無条件で等倍の次の固定倍率にします（合わせてロジックも変更します）
	** 例）110% → 115%, 120% → 122%, 130% → 141%		：特許
	** 　　110% → 115%, 120% → 115%, 130% → 115%		：ＯＫ
	*/
 #if (0)
 //	struct OPR_MAGNIFI_PAPER_TABLE_t	*magnifi_paper_tbl_ptr;
 //
 //	/* このロジックでは、最大倍率（２００％）より大きい時は正しく動作しません */
 //	magnifi_cnt = 0;
 //	while (OPR_FixedMagnificationTable[magnifi_cnt].Magnification != NULL) {
 //
 //		/* 現在の倍率より固定倍率テーブルの倍率の方が大きくなった時、該当する記録紙サイズを調べます */
 //		if (OPR_CopyData.Reduction <= OPR_FixedMagnificationTable[magnifi_cnt].Magnification) {
 //			if (OPR_CopyData.Reduction == OPR_FixedMagnificationTable[magnifi_cnt].Magnification) {
 //				/* 現在の倍率と同じ固定倍率の時 */
 //				if (OPR_CopyData.Reduction == OPR_COPY_MAGNIFICATION_MAX) {	/* 現在が最大倍率（２００％）の時 */
 //					magnifi_cnt = 0;	/* 倍率を１００％に戻します */
 //				}
 //				else {
 //					magnifi_cnt += 1;	/* 次の固定倍率をセットします */
 //				}
 //			}
 //			/* 固定倍率のセット */
 //			OPR_CopyData.Reduction = OPR_FixedMagnificationTable[magnifi_cnt].Magnification;
 //			/* 固定倍率に対する原稿・記録紙サイズのテーブルのポインターのセット */
 //			magnifi_paper_tbl_ptr = OPR_FixedMagnificationTable[magnifi_cnt].MagnifiTablePtr;
 //
 //			/* 変更された固定倍率と記録紙サイズに該当する原稿サイズがあるかを調べます */
 //			OPR_FixedMagnifiDocSize = GetDocumentSize(magnifi_paper_tbl_ptr, paper_size);
 //			break;
 //		}
 //		magnifi_cnt++;
 //	}
 #endif

	/* 現在の倍率から、次の固定倍率用の配列番号を取得します */
	magnifi_cnt = CheckFixedMagnification((struct OPR_FIXED_MAGNIFI_TABLE_t *)&OPR_FixedMagnificationTable[0].Magnification);
	if (magnifi_cnt == 0xFF) {	/* 現在の倍率が、固定倍率以外の時 */
		magnifi_cnt = 1;
	}
	else {						/* 現在の倍率が、固定倍率の時 */
		if (OPR_CopyData.Reduction == OPR_COPY_MAGNIFICATION_MAX) {	/* 倍率が最大倍率（２００％）の時 */
			magnifi_cnt = 0;
		}
		else {														/* 倍率が最大倍率以外の時 */
			magnifi_cnt++;
		}
	}

	/* 固定倍率のセット */
	OPR_CopyData.Reduction = OPR_FixedMagnificationTable[magnifi_cnt].Magnification;
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)	/* 自動カセット選択追加 By S.Fukui Jan.23,1998 */
	if (OPR_CopyData.Cassette != SYS_AUTO_CASSETTE) {
	/* 変更された固定倍率と記録紙サイズに該当する原稿サイズがあればセットします */
		OPR_FixedMagnifiDocSize = GetDocumentSize(OPR_FixedMagnificationTable[magnifi_cnt].MagnifiTablePtr, paper_size);
	}
	/* 自動の場合、"Ltr -> Auto  100%"と表示されるのを "     Auto  100%"とします。 */
	else {
		OPR_FixedMagnifiDocSize = SYS_NO_PAPER;
	}
#else
	/* 変更された固定倍率と記録紙サイズに該当する原稿サイズがあればセットします */
	OPR_FixedMagnifiDocSize = GetDocumentSize(OPR_FixedMagnificationTable[magnifi_cnt].MagnifiTablePtr, paper_size);
#endif
}

/*************************************************************************
	module		:[固定倍率　縮小処理]
	function	:[
		1.８６％から順番に固定倍率（５０％～１００％）に縮小します
		2.５０％になったら１００％に戻します
		3.変更した固定倍率と選択されているカセットの記録紙サイズより
		  該当する原稿サイズがあるかを調べる
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
void CopyReductionOperation(UBYTE paper_size)
{
	UBYTE	magnifi_cnt;	/* 固定倍率テーブルの配列番号 */

	/* （特許対策）
	** 現在の倍率から一番近い固定倍率にしてはいけないので、固定倍率以外で縮小キーを押された時は、
	** 無条件で等倍の１つ前の固定倍率にします（合わせてロジックも変更します）
	** 例）90% → 86%, 85% → 81%, 80% → 70%	：特許
	** 　　90% → 86%, 85% → 86%, 80% → 86%	：ＯＫ
	*/
 #if (0)
 //	struct OPR_MAGNIFI_PAPER_TABLE_t	*magnifi_paper_tbl_ptr;
 //
 //	/* このロジックでは、最小倍率（５０％）より小さい時は正しく動作しません */
 //	magnifi_cnt = 0;
 //	while (OPR_FixedReductionTable[magnifi_cnt].Magnification != NULL) {
 //
 //		/* 現在の倍率より固定倍率テーブルの倍率の方が大きくなった時、該当する記録紙サイズを調べます */
 //		if (OPR_CopyData.Reduction >= OPR_FixedReductionTable[magnifi_cnt].Magnification) {
 //			if (OPR_CopyData.Reduction == OPR_FixedReductionTable[magnifi_cnt].Magnification) {
 //				/* 現在の倍率と同じ固定倍率の時 */
 //				if (OPR_CopyData.Reduction == OPR_COPY_REDUCTION_MIN) {	/* 現在が最小倍率（５０％）の時 */
 //					magnifi_cnt = 0;	/* 倍率を１００％に戻します */
 //				}
 //				else {
 //					magnifi_cnt += 1;	/* 次の固定倍率をセットします */
 //				}
 //			}
 //			/* 固定倍率のセット */
 //			OPR_CopyData.Reduction = OPR_FixedReductionTable[magnifi_cnt].Magnification;
 //			/* 固定倍率に対する原稿・記録紙サイズのテーブルのポインターのセット */
 //			magnifi_paper_tbl_ptr = OPR_FixedReductionTable[magnifi_cnt].MagnifiTablePtr;
 //
 //			/* 変更された固定倍率と記録紙サイズに該当する原稿サイズがあるかを調べます */
 //			OPR_FixedMagnifiDocSize = GetDocumentSize(magnifi_paper_tbl_ptr, paper_size);
 //			break;
 //		}
 //		magnifi_cnt++;
 //	}
 #endif

	/* 現在の倍率から、次の固定倍率用の配列番号を取得します */
	magnifi_cnt = CheckFixedMagnification((struct OPR_FIXED_MAGNIFI_TABLE_t *)&OPR_FixedReductionTable[0].Magnification);
	if (magnifi_cnt == 0xFF) {	/* 現在の倍率が、固定倍率以外の時 */
		magnifi_cnt = 1;
	}
	else {						/* 現在の倍率が、固定倍率の時 */
		if (OPR_CopyData.Reduction == OPR_COPY_REDUCTION_MIN) {	/* 倍率が最小倍率（５０％）の時 */
			magnifi_cnt = 0;
		}
		else {													/* 倍率が最小倍率以外の時 */
			magnifi_cnt++;
		}
	}

	/* 固定倍率のセット */
	OPR_CopyData.Reduction = OPR_FixedReductionTable[magnifi_cnt].Magnification;

#if (PRO_ADF_AUTO_CASSETTE == ENABLE)	/* 自動カセット選択追加 By S.Fukui Jan.23,1998 */
	if (OPR_CopyData.Cassette != SYS_AUTO_CASSETTE) {
	/* 変更された固定倍率と記録紙サイズに該当する原稿サイズがあればセットします */
		OPR_FixedMagnifiDocSize = GetDocumentSize(OPR_FixedReductionTable[magnifi_cnt].MagnifiTablePtr, paper_size);
	}
	/* 自動の場合、"Ltr -> Auto  100%"と表示されるのを "     Auto  100%"とします。*/
	else {
		OPR_FixedMagnifiDocSize = SYS_NO_PAPER;
	}
#else
	/* 変更された固定倍率と記録紙サイズに該当する原稿サイズがあればセットします */
	OPR_FixedMagnifiDocSize = GetDocumentSize(OPR_FixedReductionTable[magnifi_cnt].MagnifiTablePtr, paper_size);
#endif
}

/*************************************************************************
	module		:[手差し記録紙サイズ獲得]
	function	:[
		1.手差しで次に選択できる記録紙サイズを獲得します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/07]
	author		:[渡辺一章]
*************************************************************************/
void GetNextManualPaperSize(void)
{
	UBYTE	i;			/* ループ変数 */
	UBYTE	tbl_pos;	/* 手差し記録紙サイズ選択用テーブル配列番号 */

	/* カセットから手差しに変更された時・選択できる手差しが一周した時は、
	** 先頭の手差しを表示するので、初期値として先頭の配列番号をセットします
	*/
	tbl_pos = 0;

	if (SYS_ManualPaperSize != SYS_NO_PAPER) {	/* 手差しが選択されている時 */
		for (i = 0; i <= (UBYTE)(SYS_LAST_PAPER_SIZE + 1); i++) {
			if ((OPR_SelectManualPaperTable[i].PaperSize == SYS_ManualPaperSize)
			 && (OPR_SelectManualPaperTable[i].OHP_Mode == OPR_CopyData.OHPMode)) {
				/* 現在選択している記録紙が見つかった時 */
				if (OPR_SelectManualPaperTable[i + 1].PaperSize != SYS_NO_PAPER) {
					/* 現在のサイズの後にも、選択できるサイズがある時 */
					tbl_pos = (UBYTE)(i + 1);
				}
				break;
			}
		}
	}

	SYS_ManualPaperSize = OPR_SelectManualPaperTable[tbl_pos].PaperSize;	/* 手差しの記録紙サイズをセット */
	OPR_CopyData.OHPMode = OPR_SelectManualPaperTable[tbl_pos].OHP_Mode;	/* ＯＨＰモードをセット */
}

/*************************************************************************
	module		:[コピー管理テーブル　ステータスチェック]
	function	:[
		1.カセットが選択されている時は、マルチコピー管理テーブルに空きがあるかを調べます
		2.手差しが選択されている時は、手差しコピー管理テーブルが未使用かを調べます
		3.それぞれで、空きがあればTRUEを返します
	]
	return		:[
		TRUE	:空きあり
		FALSE	:空きなし
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/07]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckCopyFileStatus(void)
{
	UBYTE	i;		/* ループ変数 */
	UBYTE	ret;	/* リターン値 */

	ret = FALSE;

	if (OPR_CopyData.Cassette != SYS_MANUAL_CASSETTE) {	/** カセットが選択されている時 */
		for (i = 0; i < SYS_MULTI_COPY_MAX; i ++) {
			/* マルチコピー管理テーブルに未使用の物があれば、処理を終えます */
			if (SYB_MultiCopyFile[i].Status == SYS_MCOPY_EMPTY) {
				ret = TRUE;
				break;
			}
		}
	}
	else {												/** 手差しが選択されている時 */
		if (SYB_ManualCopyFile.Status == SYS_MCOPY_EMPTY) {
			ret = TRUE;
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[コピーパラメータ　セット]
	function	:[
		1.コピー開始メッセージのセット
		2.コピーパラメータのセット
	]
	return		:[なし]
	common		:[
		SYB_MultiCopyFile
		SYB_MultiCopyWritePoint
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/06]
	author		:[渡辺一章]
*************************************************************************/
void SetCopyParameter(void)
{
 #if (0)	/* 指定カセットからしかコピーできなくなったので削除します by K.Watanabe 1997/10/03 */
 //	UBYTE	cassette;						/* カセット段数セット用ワーク変数 */
 #endif
	struct	SYS_MultiCopyData_t *copy_ptr;	/* コピー用ファイルのポインター */

 #if (0)	/* 指定カセットからしかコピーできなくなったので削除します by K.Watanabe 1997/10/03 */
 //	/* 現在選択されているカセット段数をワーク変数にコピーします */
 //	cassette = OPR_CopyData.Cassette;
 #endif

	/* 選択されている記録紙の格納先による処理 */
	if (OPR_CopyData.Cassette == SYS_MANUAL_CASSETTE) {	/* 手差しが選択されている時 */
		copy_ptr = &SYB_ManualCopyFile;								/* コピー用ファイルのポインターのセット */
		OPR_CopyData.Size = SYS_ManualPaperSize;					/* 手差し原稿サイズのセット */
		OperationMessageToMain.Message = MSG_STORE_MANUAL_COPY_DOC;	/* コピー開始メッセージのセット */
	}
	else {												/* カセットが選択されている時 */
		copy_ptr = &SYB_MultiCopyFile[SYB_MultiCopyWritePoint];		/* コピー用ファイルのポインターのセット */
/*		OPR_CopyData.Size = SYS_NO_PAPER;							@* 手差し原稿サイズのセット */
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)
		/* 自動カセット選択時、原稿幅から抽出したカセットサイズを返します。 By S.Fukui Apr.1,1998 */
		if (OPR_CopyData.Cassette == SYS_AUTO_CASSETTE) {
			OPR_CopyData.Size = *PaperSizeTable[PRN_GetPrintCassette(CMN_GetDocumentScanSize()) - 1];
		}
		else {
#endif
			OPR_CopyData.Size = *PaperSizeTable[OPR_CopyData.Cassette - 1];	/* Add By M.Tachibana 1997/09/25 */
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)
		}			/* By S.Fukui Apr.1,1998 */
#endif

		OperationMessageToMain.Message = MSG_STORE_MULTI_COPY_DOC;	/* コピー開始メッセージのセット */
	}

	/* スキャン種別のチェック */
	if (CMN_CheckScanDocOnFeeder() == TRUE) {	/* ＡＤＦに原稿がセットされている時 */
		OPR_CopyData.ScanType = SYS_ADF_SCAN;
		OPR_CopyData.ScanSize = CMN_GetDocumentScanSize();	/* ＡＤＦの読み取りサイズのセット By M.Tachibana 1997/12/01	*/
 #if (0)	/* 指定カセットから By M.Tachibana 1997/08/09 */
 //		/* ＡＤＦからのコピー時は、選択されているカセット（手差しは除く）は無効で、
 //		** 原稿サイズから自動的にカセットが選択されます
 //		*/
 //		if (OPR_CopyData.Cassette != SYS_MANUAL_CASSETTE) {	/* カセットが選択されている時 */
 //			cassette = SYS_AUTO_CASSETTE;	/* カセット自動選択をワーク変数にセット */
 //		}
 #endif
	}
	else {										/* ＦＢＳに原稿がセットされている（ADFに原稿がｾｯﾄされていない）時 */
		OPR_CopyData.ScanType = SYS_FBS_SCAN;

		/* 指定カセットの記録紙サイズと倍率から、該当する原稿サイズを獲得します */
		SCN_RegularDocumentSize = GetBookCopyDocumentSize();
		OPR_CopyData.ScanSize = SCN_RegularDocumentSize;	/* ＦＢＳの読み取りサイズのセット	*/
	}

	/* オペレーションで設定されたコピーパラメータをセットする */
	copy_ptr->ReserveNumber	= OPR_CopyData.ReserveNumber;	/* コピー部数のセット				*/
 #if (0)	/* 指定カセットからしかコピーできなくなったので削除します by K.Watanabe 1997/10/03 */
 //	copy_ptr->Cassette		= cassette;						/* カセット段数のセット				*/
 #endif
	copy_ptr->Cassette		= OPR_CopyData.Cassette;		/* カセット段数のセット				*/
	copy_ptr->Size			= OPR_CopyData.Size;			/* 手差し原稿サイズのセット			*/
	copy_ptr->SortType		= OPR_CopyData.SortType;		/* ソート種別のセット				*/
	copy_ptr->Reduction		= OPR_CopyData.Reduction;		/* 倍率のセット						*/
	copy_ptr->ScanType		= OPR_CopyData.ScanType;		/* スキャン種別のセット				*/
	copy_ptr->ScanSize		= OPR_CopyData.ScanSize;		/* 読み取りサイズのセット			*/
	copy_ptr->OHPMode		= OPR_CopyData.OHPMode;			/* ＯＨＰモードのセット				*/
}

/*************************************************************************
	module		:[原稿サイズ獲得]
	function	:[
		1.指定された記録紙サイズに対する原稿があればそのサイズを返します
	]
	return		:[原稿サイズ（SYSDOC.Hに定義されている記録紙サイズの値です）]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/25]
	author		:[渡辺一章]
*************************************************************************/
UBYTE GetDocumentSize(struct OPR_MAGNIFI_PAPER_TABLE_t *magnifi_paper_tbl_ptr, UBYTE paper_size)
{
	UBYTE	ret;	/* 原稿サイズ */

	ret = SYS_NO_PAPER;

	/* 変更された固定倍率と記録紙サイズに該当する原稿サイズがあるかを調べます */
	while (magnifi_paper_tbl_ptr->PaperSize != SYS_NO_PAPER) {
		if (paper_size == magnifi_paper_tbl_ptr->PaperSize) {
			/* 該当する原稿があった時 */
			ret = magnifi_paper_tbl_ptr->DocumentSize;
			break;
		}
		magnifi_paper_tbl_ptr++;
	}

	return(ret);
}

/*************************************************************************
	module		:[ブックコピー原稿サイズ獲得]
	function	:[
		1.指定カセットの記録紙サイズと倍率から、該当する原稿サイズを獲得します
	]
	return		:[ブック原稿サイズ]
	common		:[]
	condition	:[
		この関数を実行する時は、選択されているカセットの記録紙が必ずある事
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/04]
	author		:[渡辺一章]
*************************************************************************/
UBYTE GetBookCopyDocumentSize(void)
{
	UBYTE	paper_cnt;	/* ループ変数 */
	UBYTE	paper_size;	/* 記録紙サイズ */
	UBYTE	ret;		/* リターン値 */
	struct OPR_PRINT_PAPER_TABLE_t *paper_tbl_ptr;	/* 記録紙テーブルポインター */

	paper_cnt = 0;
	ret = SYS_REGULAR_SIZE_UNKNOWN;

	paper_size = GetPaperSize(OPR_CopyData.Cassette);	/* 現在選択されているカセットの記録紙サイズの獲得 */

	while (OPR_BookCopyDocumentSizeTable[paper_cnt].PaperSize != SYS_NO_PAPER) {	/* 記録紙サイズの種類が無くなるまで検索 */
		/* 記録紙サイズに対する原稿サイズを求めるテーブルがあるかを調べます */
		if (paper_size == OPR_BookCopyDocumentSizeTable[paper_cnt].PaperSize) {	/* 記録紙サイズのテーブルが見つかった時 */
			paper_tbl_ptr = OPR_BookCopyDocumentSizeTable[paper_cnt].PrintPaperTablePtr;
			while (paper_tbl_ptr->Magnification != NULL) {	/* 最大倍率まで調べます */
				/* 現在の倍率と、原稿サイズ獲得テーブルの倍率とを比較して、原稿サイズを獲得します
				** 例）記録紙サイズ：Ａ４，コピー倍率：８６％の時
				** 　　原稿サイズ獲得テーブルより、８１％以上１００％未満は原稿サイズはＢ４なのでＢ４を返します
				*/
				if ((paper_tbl_ptr + 1)->Magnification != NULL) {	/* 原稿サイズ獲得テーブルの倍率が最大倍率以外の時 */
					if ((OPR_CopyData.Reduction >= paper_tbl_ptr->Magnification)
					 && (OPR_CopyData.Reduction < (paper_tbl_ptr + 1)->Magnification)) {
						ret = paper_tbl_ptr->BookDocumentSize;	/* 獲得した原稿サイズをセットします */
						break;
					}
				}
				else {												/* 原稿サイズ獲得テーブルの倍率が最大倍率の時 */
					if (OPR_CopyData.Reduction == paper_tbl_ptr->Magnification) {
						ret = paper_tbl_ptr->BookDocumentSize;	/* 獲得した原稿サイズをセットします */
						break;
					}
				}
				paper_tbl_ptr++;	/* 次の倍率に進めます */
			}
			break;
		}
		paper_cnt++;	/* 次の記録紙に進めます */
	}

	return(ret);
}

/*************************************************************************
	module		:[コピー倍率変更処理]
	function	:[
		1.用紙選択キーが押された時、ＡＤＦに原稿がセットされていれば、
		　原稿・記録紙のサイズより、等倍以下で適切な倍率に変更します
		2.ＡＤＦに原稿がセットされた時、倍率変更可能な状態で、倍率が
		　１００％であれば、原稿・記録紙のサイズより、等倍以下で適切な
		　倍率に変更します
		3.ＡＤＦにセットされた原稿が抜かれた時、2.で倍率が変更されていて、
		　倍率変更可能な状態であれば、倍率：１００％、カセット：記録紙が
		　セットされている１段めに近いカセットに変更します
		4.カセットが閉められた時、固定倍率で原稿表示をしていて、倍率変更
		　可能な状態の時、記録紙のサイズが変更されていたら、表示している
		　原稿サイズが食い違ってくるので、ＡＤＦの原稿セット状態・記録紙
		　サイズ・倍率から、適切な状態に変更します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/03]
	author		:[渡辺一章]
*************************************************************************/
void ModifyCopyMagnifi(UBYTE call_place)
{
	/* この関数が呼ばれた時の動作により、実際に倍率変更を行うかどうかをチェックします */
	switch (call_place) {
	case OPR_PAPER_SELECT:		/* 用紙選択キーが押された時 */
		/* ＡＤＦに原稿がセットされていない時は、倍率変更を行いません */
		if (CMN_CheckDocumentOnFeeder() == TRUE) {
			OPR_CopyData.Reduction = ClearCopyMagnifi();	/* 倍率の変更 */
		}

		/* 原稿表示をしていたら濃度表示に戻します */
		IsMagnifiKeyInput = FALSE;	/* 拡大・縮小キー押下チェック用変数ＯＦＦ */
		break;
	case OPR_ADF_DOC_IN:		/* ＡＤＦに原稿がセットされた時 */
		if ((OPR_NumberKeyInputMode != OPR_COPY_MAGNIFI_INPUT_MODE)	/* コピー倍率入力モードでない時				*/
		 && (!IsCassetteManualChange)) {							/* カセット又は、手差しが選択されている時	*/
			/* 倍率が変更されている時は、設定されている倍率を優先するので、倍率変更は行いません */
			if (OPR_CopyData.Reduction != 100) {	/* 倍率が変更されている時 */
				/* 原稿が抜かれても、倍率・カセットを初期値に戻さないようにしておきます */
				IsModifyCopyMagnifi = FALSE;
			}
			else {									/* 倍率が変更されていない時 */
				if (OPR_CopyData.Cassette != SYS_MANUAL_CASSETTE) {	/* カセットが選択されている時 */
					/* 原稿ｻｲｽﾞとｶｾｯﾄの記録紙ｻｲｽﾞを元に、等倍に近い倍率でｺﾋﾟｰできる記録紙のｶｾｯﾄを獲得します */
					OPR_CopyData.Cassette = ClearCopyCassette();	/* カセット段数の変更 */
				}
				OPR_CopyData.Reduction = ClearCopyMagnifi();	/* 倍率の変更 */

				/* 原稿が抜かれた時に、倍率・カセットを初期値に戻してくれるようにしておきます */
				IsModifyCopyMagnifi = TRUE;

				/* 原稿表示をしていたら濃度表示に戻します */
				IsMagnifiKeyInput = FALSE;	/* 拡大・縮小キー押下チェック用変数ＯＦＦ */
			}
		}
		break;
	case OPR_ADF_DOC_OUT:		/* ＡＤＦの原稿が抜かれた時 */
		if (IsModifyCopyMagnifi) {	/* 原稿セット時に、倍率変更がされている時 */
			/* ＡＤＦに原稿がセットされると、自動的に倍率を変更しているので、
			** 逆に原稿が抜かれた場合は、倍率を初期値に戻します
			*/
			if ((OPR_NumberKeyInputMode != OPR_COPY_MAGNIFI_INPUT_MODE)	/* コピー倍率入力モードでない時		*/
#if (0)	/* 送信用原稿の読み取りでも、倍率がそのまま残るので条件を変更 by K.Watanabe 1998/01/27 */
//			 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)) {	/* 原稿読み取り中でない時		*/
#endif
			 && !(CheckCopyDocStore())) {								/* コピー原稿の読み取り中でない時	*/
				if (OPR_CopyData.Cassette != SYS_MANUAL_CASSETTE) {	/* カセットが選択されている時 */
					OPR_CopyData.Cassette = ClearCopyCassette();	/* カセット段数の初期化 */
				}
				OPR_CopyData.Reduction = ClearCopyMagnifi();	/* 倍率の初期化 */

				/* 原稿表示をしている時は、濃度表示に戻します */
				IsMagnifiKeyInput = FALSE;	/* 拡大・縮小キー押下チェック用変数ＯＦＦ */
			}
			IsModifyCopyMagnifi = FALSE;	/* 一応、初期化しておきます */
		}

#if (PRO_ADF_AUTO_CASSETTE == ENABLE)	/* By S.Fukui Jan.23,1998 */
		/* 自動カセット選択の場合、は倍率、カセットを初期化します。*/
		ClearAutoCassetteAndMagnifi();
#endif
		break;
	case OPR_CASSETTE_CLOSE:	/* カセットが閉められた時 */
		if ((OPR_FixedMagnifiDocSize != SYS_NO_PAPER)				/* 固定倍率で原稿表示をしている時			*/
		 && (OPR_NumberKeyInputMode != OPR_COPY_MAGNIFI_INPUT_MODE)	/* コピー倍率入力モードでない時				*/
		 && (!IsCassetteManualChange)) {							/* カセット又は、手差しが選択されている時	*/
			/* 現在の倍率が固定倍率で原稿表示をしている時に、記録紙ｻｲｽﾞが変更されたら、ｶｾｯﾄ・倍率の初期化を行います */
			if (CheckChangeCassette() == TRUE) {	/* 記録紙サイズが変更された時 */
				OPR_CopyData.Cassette = ClearCopyCassette();	/* カセット段数の初期化 */
				OPR_CopyData.Reduction = ClearCopyMagnifi();	/* 倍率の初期化 */

				/* 原稿表示をしていたら濃度表示に戻します */
				IsMagnifiKeyInput = FALSE;	/* 拡大・縮小キー押下チェック用変数ＯＦＦ */
			}
		}
		/* 倍率が"---%"（ＡＤＦに原稿セットかつ記録紙なしのカセット選択）の時に、選択されているカセットに
		** 記録紙を補給しても倍率がそのままなのはまずいので、セットするようにします
		** by K.Watanabe 1998/09/09
		*/
		else if ((OPR_CopyData.Reduction == 0) && (OPR_NumberKeyInputMode != OPR_COPY_MAGNIFI_INPUT_MODE)) {
			OPR_CopyData.Reduction = ClearCopyMagnifi();	/* 倍率の初期化 */
		}
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[ＡＤＦコピー最大倍率獲得]
	function	:[
		1.ＡＤＦの原稿サイズと記録紙サイズから、コピーできる最大の倍率を獲得します
	]
	return		:[最大倍率]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/03]
	author		:[渡辺一章]
*************************************************************************/
UBYTE GetADF_CopyMaxMagnifi(void)
{
	UBYTE	paper_size;		/* カセット・手差しの記録紙サイズ */
	UBYTE	adf_doc_size;	/* ＡＤＦ原稿サイズ */
	UBYTE	ret;			/* リターン値 */

	ret = 0;	/* 倍率設定不可能 */

	/* カセット・手差しにセットされている記録紙サイズを獲得します */
	paper_size = GetPaperSize(OPR_CopyData.Cassette);

	/* ＡＤＦにセットされている原稿サイズを獲得します */
	adf_doc_size = CMN_GetDocumentScanSize();

	/* 原稿と記録紙のサイズの組み合わせによっては、倍率が小さくなりすぎてコピー不可能なので、チェックします
	** 注）PRN_GetReduction()の中でチェックした方が、プログラム的にはスマートになるが、他でも使用されて
	** 　　いるため、この中でのチェックは出来ないので、先に必ずチェックを行う必要があります
	*/
#if (0)	/* by K.Watanabe 1997/12/25 */
//	if (((paper_size >= SYS_FIRST_PAPER_SIZE) && (paper_size <= SYS_LAST_PAPER_SIZE))	/* 指定の記録紙がある時 */
//	 && (CheckCopyEnablePaperCombi(adf_doc_size, paper_size) == TRUE)) {				/* コピー可能な組み合わせの時 */
//		/* 原稿と記録紙のサイズより、コピーできる最大の倍率を獲得します */
//		ret = PRN_GetReduction(adf_doc_size, paper_size);
//	}
#endif
	/* Ａ４→ハガキもコピー禁止になり（実際は５０％以下なので）、結局ＡＤＦからハガキにはコピー
	** できなくなった為に、テーブルを使用してのチェックは必要ないので、サイズだけで判断します
	*/
	if (((paper_size >= SYS_FIRST_PAPER_SIZE) && (paper_size <= SYS_LAST_PAPER_SIZE))	/* 指定の記録紙がある時 */
	 && (paper_size != SYS_POST_PAPER)) {												/* ハガキ以外の時 */
		/* 原稿と記録紙のサイズより、コピーできる最大の倍率を獲得します */
		ret = PRN_GetReduction(adf_doc_size, paper_size);
	}

	return(ret);
}

/*************************************************************************
	module		:[コピー可能な原稿・記録紙の組み合わせのチェック]
	function	:[
		1.原稿と記録紙の組み合わせによっては、倍率が小さくなりすぎてコピー
		　が不可能になるので、コピー可能な組み合わせかをチェックします
	]
	return		:[
		TRUE	:コピー可能
		FALSE	:コピー不可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/03]
	author		:[渡辺一章]
*************************************************************************/
/* Ａ４→ハガキもコピー禁止になり（実際は５０％以下なので）、結局ＡＤＦからハガキには
** コピーできなくなった為に、テーブルを使用してのチェックは必要ないので、削除します
*/
#if (0)	/* by K.Watanabe 1997/12/25 */
//UBYTE CheckCopyEnablePaperCombi(UBYTE doc_size, UBYTE paper_size)
//{
//	UBYTE	i;		/* ループ変数 */
//	UBYTE	ret;	/* リターン値 */
//
//	i = 0;
//	ret = TRUE;
//
//	while (OPR_CopyImposPaperCombiTable[i].DocumentSize != SYS_NO_PAPER) {
//		/* 指定の原稿サイズと記録紙サイズが、チェックテーブルの内容と一致した時は、コピー不可能です */
//		if ((doc_size == OPR_CopyImposPaperCombiTable[i].DocumentSize)
//		 && (paper_size == OPR_CopyImposPaperCombiTable[i].PaperSize)) {
//			ret = FALSE;
//			break;
//		}
//		i++;
//	}
//
//	return(ret);
//}
#endif

/*************************************************************************
	module		:[ＡＤＦコピー可能倍率検査]
	function	:[
		1.設定されている倍率が、コピー可能最大倍率を超えているかを調べます
		2.コピー可能最大倍率を超えている時は、コピー可能最大倍率でコピーして
		　良いかの確認を行います
		3.確認がＯＫの時、倍率をコピー可能最大倍率に更新し、念のために、
		　もう一度倍率のチェックを行います
		4.確認がＮＧの時、そのまま終了します
	]
	return		:[
		OPR_MAGNIFI_CHK_OK	:設定倍率が、コピー可能最大倍率未満
		OPR_MAGNIFI_CHG_OK	:倍率変更確認ＯＫ（設定倍率が、ｺﾋﾟｰ可能最大倍率より大きい）
		OPR_MAGNIFI_CHG_NG	:倍率変更確認ＮＧ（設定倍率が、ｺﾋﾟｰ可能最大倍率より大きい）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/04]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckADF_CopyMagnifi(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	max_magnifi;		/* 現在の状況での最大倍率 */
	UBYTE	magnifi_dsp_byte;	/* 倍率表示位置 */
	UBYTE	is_loop_end;		/* ループ終了で使用 */
	UBYTE	ret;				/* リターン値 */

	ret = OPR_MAGNIFI_CHK_OK;

	/* 原稿サイズと記録紙サイズから、コピーできる最大の倍率を獲得します */
	max_magnifi = GetADF_CopyMaxMagnifi();

	/* 設定されている倍率が、コピー可能最大倍率を超えている時は、倍率確認を行います */
	if (max_magnifi < OPR_CopyData.Reduction) {
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_ConfirmCopyMagnifi);	/* "999% ﾃﾞ ｺﾋﾟｰ ｼﾏｽｶ?  " */

		/* 国別のワーディングの違いを吸収するために、倍率の表示位置を求めます */
		magnifi_dsp_byte = (UBYTE)GetStringGapPoint(FunctionDisplayBufferHigh, '9');

		/* 倍率をアスキーに変換して、表示用バッファにセットします */
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[magnifi_dsp_byte], (UWORD)max_magnifi, 3, ' ');

		/* 上下段の表示 */
		DisplayStringHigh(0, FunctionDisplayBufferHigh);	/* "999% ﾃﾞ ｺﾋﾟｰ ｼﾏｽｶ?  " */
		FlashDisplayStringLow(D2W_StartStop);				/* "         ｽﾀｰﾄ/ｽﾄｯﾌﾟ " */

		is_loop_end = FALSE;
		while (is_loop_end != TRUE) {
			OPR_GetKey(KEY_WAIT_ONE_MINUTE);	/* キー待ち１分 */
			key = GetInputKeyCode();
			keytype = GetInputKeyType();

			switch (keytype) {
			case START:			/* スタートキー				*/
				OPR_CopyData.Reduction = max_magnifi;	/* 倍率をコピー可能最大倍率に更新します */
				ret = OPR_MAGNIFI_CHG_OK;

				/* 確認待ちの間に、ＡＤＦの原稿を変えられた場合のために、もう一度倍率のチェックをします */
				if ((CMN_CheckScanDocOnFeeder() == TRUE) && (GetADF_CopyMaxMagnifi() < OPR_CopyData.Reduction)) {
					NackBuzzer();
					ret = OPR_MAGNIFI_CHG_NG;
				}
				is_loop_end = TRUE;
				break;
			case STOP:			/* ストップキー				*/
			case KEY_TIME_UP:	/* キー待ちタイムオーバー	*/
				ret = OPR_MAGNIFI_CHG_NG;
				is_loop_end = TRUE;
				break;
			case NO_EFFECT:
				break;
			default:
				NackBuzzer();
				break;
			}
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[コピー予約可能検査]
	function	:[
		1.コピープリント中に、そのカセットが紙なしになった場合は、コピー予約を禁止します
	]
	return		:[
		TRUE	:コピー予約可能
		FALSE	:コピー予約不可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/10/03]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckPossibleCopyReserve(void)
{
	UBYTE	i;
	UBYTE	paper_size;

	for (i = 0; i < SYS_MULTI_COPY_MAX; i ++) {
		if (SYB_MultiCopyFile[i].Status != SYS_MCOPY_EMPTY) {
			break;
		}
	}
	if (i < SYS_MULTI_COPY_MAX) {
		switch (SYB_MultiCopyFile[i].Cassette) {
		case SYS_1ST_CASSETTE:
			paper_size = SYS_Paper1Size;
			break;
		case SYS_2ND_CASSETTE:
			paper_size = SYS_Paper2Size;
			break;
		case SYS_3RD_CASSETTE:
			paper_size = SYS_Paper3Size;
			break;
		default:
			break;
		}
		if ((paper_size == SYS_NO_CASSETTE) || (paper_size == SYS_NO_PAPER)) {
			return(FALSE);
		}
	}
	return(TRUE);
}

/*************************************************************************
	module		:[コピーパラメーター優先表示停止]
	function	:[
		1.コピーパラメーター優先表示用タイマーが起動中かチェックし、起動中ならタイマーを停止します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/29]
	author		:[渡辺一章]
*************************************************************************/
void StopParamDispTask(void)
{
	if (tskno_OPR_ParamDispTask != 0xffff) {	/* コピーパラメーター優先表示中の時 */
		/* コピーパラメーター優先表示用タイマーを停止します */
		del_tsk(&tskno_OPR_ParamDispTask);
	}
}

/*************************************************************************
	module		:[用紙・倍率確認処理]
	function	:[
		1.
	]
	return		:[
		OPR_CONTINUE	:オペレーション続行
		OPR_END			:オペレーション終了／完了
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/05]
	author		:[渡辺一章]
*************************************************************************/
UBYTE ConfirmCopyParam(void)
{
	UBYTE	ret;	/* リターン値 */

	ret = OPR_END;

	/** 表示用バッファの初期化 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	SetCassettePaperSize(&FunctionDisplayBufferHigh[7]);		/* カセット段数・記録紙サイズのセット */
	SetCopyModeMagnification(&FunctionDisplayBufferHigh[16]);	/* 倍率のセット */

	if (ConfirmKeyInputOperation(FunctionDisplayBufferHigh,	/* "       C1:A4    100%" */
								 D2W_CheckStartStop,		/* "ｶｸﾆﾝ     ｽﾀｰﾄ/ｽﾄｯﾌﾟ " */
								 START,
								 STOP) == CONFIRM_EXEC) {	/* 実行が選択された時 */
		ret = OPR_CONTINUE;
	}

	return(ret);
}

/*************************************************************************
	module		:[カセット交換（記録紙サイズ変更）検査]
	function	:[
		1.現在の倍率が固定倍率の時、固定倍率テーブルからカセットの記録紙サイズが
		　変更されたかを調べます
	]
	return		:[
		TRUE	:カセット交換
		FALSE	:カセット未交換・現在の倍率が固定倍率でない
	]
	common		:[]
	condition	:[]
	comment		:[
		元々は、ＡＤＦに原稿がセットされている時に、カセットが閉められると
		無条件に倍率を変更していましたが、拡大・縮小キーが押された後にカセ
		ットが閉められた時は、固定倍率表示をそのまま表示しておく（倍率変更
		しない）仕様に変わりました。
		　しかし、記録紙サイズが変更された時に、表示をそのままにしておくと
		、矛盾が起こるため、表示を更新する必要があります。
		例）"B4 -> C1:A4 81%"の後、記録紙をB4に変更すると"B4 -> C1:B4 81%"
		　そこで、カセットが閉められた時に、記録紙サイズが変更されていない
		かをチェックする必要がありますが、メインの方でカセットが開けられた
		時にサイズを覚えておこうとすると、記録紙が無くなった後に開けられた
		時、カセットが開けられた状態で電源ＯＮされた時等、サイズの獲得が困
		難な場合があるので、代わりに現在の倍率が固定倍率の時のみ、テーブル
		を利用してチェックするようにこの関数を作成しました。

		注）倍率が固定倍率でないか、固定倍率でも原稿表示をしていない時は、
		　　表示を変更する必要がないので、無条件にカセット未交換を返します
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/08]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckChangeCassette(void)
{
	UBYTE	magnifi_cnt;								/* 固定倍率テーブルの配列番号 */
	UBYTE	fixed_magnifi_doc_size;						/* 固定倍率対応原稿サイズ */
	UBYTE	ret;										/* リターン値 */
	struct OPR_FIXED_MAGNIFI_TABLE_t *magnifi_tbl_ptr;	/* 固定倍率テーブルポインター */

	ret = FALSE;

	/* 現在の倍率が、固定倍率（拡大）かを調べます */
	magnifi_tbl_ptr = (struct OPR_FIXED_MAGNIFI_TABLE_t *)&OPR_FixedMagnificationTable[0].Magnification;
	magnifi_cnt = CheckFixedMagnification(magnifi_tbl_ptr);
	if (magnifi_cnt == 0xFF) {	/* 現在の倍率が、固定倍率（拡大）でなかった時 */
		/* 現在の倍率が、固定倍率（縮小）かを調べます */
		magnifi_tbl_ptr = (struct OPR_FIXED_MAGNIFI_TABLE_t *)&OPR_FixedReductionTable[0].Magnification;
		magnifi_cnt = CheckFixedMagnification(magnifi_tbl_ptr);
	}

	if (magnifi_cnt != 0xFF) {	/* 現在の倍率が、固定倍率の時 */
		magnifi_tbl_ptr += magnifi_cnt;	/* 一致した固定倍率まで、ポインターを進めます */

		/* 現在の固定倍率と記録紙サイズに対応する原稿サイズを取得します */
		fixed_magnifi_doc_size = GetDocumentSize(magnifi_tbl_ptr->MagnifiTablePtr, GetPaperSize(OPR_CopyData.Cassette));

		/* 表示している原稿と、取得した原稿のサイズが違う場合は、記録紙サイズが変更されたと判断します */
		if (fixed_magnifi_doc_size != OPR_FixedMagnifiDocSize) {
			ret = TRUE;
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[固定倍率検査]
	function	:[
		1.現在の倍率が、固定倍率かどうかをチェックします
	]
	return		:[
		0xFF	:固定倍率以外
		0xFF以外:固定倍率（固定倍率テーブルの配列番号）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/08]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckFixedMagnification(struct OPR_FIXED_MAGNIFI_TABLE_t *magnifi_tbl_ptr)
{
	UBYTE	magnifi_tbl_cnt;	/* 固定倍率テーブルの配列番号 */
	UBYTE	is_loop_end;		/* ループ終了で使用 */

	magnifi_tbl_cnt = 0;
	is_loop_end = FALSE;

	while (is_loop_end != TRUE) {
		if (magnifi_tbl_ptr->Magnification == NULL) {	/* 一致する固定倍率が見つからなかった時 */
			magnifi_tbl_cnt = 0xFF;
			is_loop_end = TRUE;
		}
		else if (magnifi_tbl_ptr->Magnification == OPR_CopyData.Reduction) {	/* 現在の倍率が、固定倍率の時 */
			is_loop_end = TRUE;
		}
		else {
			magnifi_tbl_ptr++;	/* 固定倍率テーブルを次の固定倍率に進めます */
			magnifi_tbl_cnt++;	/* 固定倍率テーブルの配列番号を＋１します */
		}
	}

	return(magnifi_tbl_cnt);
}

 #if (PRO_ADF_AUTO_CASSETTE == ENABLE)
/*************************************************************************
	module		:[自動カセット選択時コピー後のカセット段数／倍率の初期化]
	function	:[
		1.自動カセットモードでコピー終了 又は 原稿引抜きの際、カセット段数及び倍率の初期化を行います。
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/01/23]
	author		:[福井知史]
*************************************************************************/
void ClearAutoCassetteAndMagnifi(void)
{
	if (OPR_CopyData.Cassette == SYS_AUTO_CASSETTE) {
		OPR_CopyData.Cassette  = ClearCopyCassette();	/* カセット段数の初期化 */
		OPR_CopyData.Reduction = ClearCopyMagnifi();	/* 倍率の初期化 */
	}
}
 #endif	/* (PRO_ADF_AUTO_CASSETTE == ENABLE) */


#endif	/* (PRO_COPY_FAX_MODE == ENABLE) */
