/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_RST.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_rst.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\syslocal.h"
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"

/*************************************************************************
	module		:[優先モードのリセット]
	function	:[
		1.
	]
	return		:[]
	common		:[SYB_ModeSw]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_ResetPrimaryMode(void)
{
	SYB_ModeSw = CHK_PrimaryMode();
}

/*************************************************************************
	module		:[優先濃度のリセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_ResetPrimaryContrast(void)
{
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/15 Y.Matsukuma */
	/* ミノルタテストROMは、濃度SWをカセット選択に使用するため */
 #if (PRO_PRINT_TYPE == LASER)	/* M.Tachibana 1998/10/08 */
	SYB_DensitySw = SYS_DARK_DENSITY;
 #else
	SYB_DensitySw = CHK_PrimaryDensity();
 #endif
#else
	SYB_DensitySw = CHK_PrimaryDensity();
#endif
}

#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1999/01/21 */
/*************************************************************************
	module		:[コピー優先モードのリセット]
	function	:[
		1.
	]
	return		:[]
	common		:[SYB_CopyModeSw]
	condition	:[]
	comment		:[オールクリアキーが押下されるまでモードは保持する]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/02/27]
	author		:[橘正樹]
*************************************************************************/
void	CMN_ResetPrimaryCopyMode(void)
{
#if (0)	/* コピーモードでも画質の初期値を変更できるようにします by K.Watanabe 1999/01/21 */
//	if (CHK_UNI_HyperFineON()) { /** ハイパーファインである場合.*/
//		SYB_CopyModeSw = SYS_HFINE;
//	}
//	else { /** スーパーファインである場合 */
//		SYB_CopyModeSw = SYS_SFINE;
//	}
#endif

	SYB_CopyModeSw = CHK_UNI_CopyPrimaryMode();
}

/*************************************************************************
	module		:[コピー優先濃度のリセット]
	function	:[
		1.
	]
	return		:[]
	common		:[SYB_CopyDensitySw]
	condition	:[]
	comment		:[オールクリアキーが押下されるまで濃度は保持する]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/02/27]
	author		:[橘正樹]
*************************************************************************/
void	CMN_ResetPrimaryCopyContrast(void)
{
	SYB_CopyDensitySw = CHK_PrimaryDensity();
}
#endif	/* (PRO_COPY_FAX_MODE == ENABLE) */

/*************************************************************************
	module		:[メモリ／フィーダ送信のリセット]
	function	:[
		1.
	]
	return		:[]
	common		:[SYB_LocalStatus[]]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_ResetMemoyFeederTx(void)
{
	if (CHK_MemoryTxON()) {
		SYB_LocalStatus[0] |= SYS_MEMORY_TX_ON;
	}
	else {
		SYB_LocalStatus[0] &= ~SYS_MEMORY_TX_ON;
	}
}

/*************************************************************************
	module		:[済スタンプのリセット]
	function	:[
		1.
	]
	return		:[]
	common		:[SYB_LocalStatus[]]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_ResetStamp(void)
{
	if (CHK_StampON()) {
		SYB_LocalStatus[0] |= SYS_STAMP_ON;
	}
	else {
		SYB_LocalStatus[0] &= ~SYS_STAMP_ON;
	}
}

/*************************************************************************
	module		:[読取りサイズのリセット]
	function	:[
		1.
	]
	return		:[]
	common		:[SYS_DocumentScanSize]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_ResetPrimaryDocumentSize(void)
{
	SYS_DocumentScanSize = CHK_ScanningWidth();
}

/*************************************************************************
	module		:[通信証のリセット]
	function	:[
		1.
	]
	return		:[]
	common		:[SYB_LocalStatus[]]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康、石橋正和(1994/06/29)]
*************************************************************************/
void	CMN_ResetConfirmationReport(void)
{
	if (CHK_ConfirmationReportON()) {
#if(PRO_MEM_RX_REJECT == ENABLE)			/* メモリ受信拒絶機能 '94,10,14 By N.S. */
		if(( CMN_CheckAutoCalledEnable( 0 )						   )
		&& ( SYB_SettingStatus[SETTING_STATUS_6] & CONFIRM_TYPE_RCR )){		/** 受信証を選択 */
#else
		if (SYB_SettingStatus[SETTING_STATUS_6] & CONFIRM_TYPE_RCR) { /** 受信証を選択 */
#endif
			SYB_ConfirmationReportSwitch = RCR_REQUEST;
		}
		else { /** 送信証を選択 */
			SYB_ConfirmationReportSwitch = TCR_REQUEST;
		}
	}
	else {
		SYB_ConfirmationReportSwitch = NO_CONFIRMATION_REPORT;
	}
}

#if (PRO_RED_SCAN == ENABLE)
/*************************************************************************
	module		:[朱色読み取りのリセット]
	function	:[
		1.
	]
	return		:[]
	common		:[SYB_LocalStatus[]]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/03/05]
	author		:[高木智史 T.Takagi]
*************************************************************************/
void	CMN_ResetRedScan(void)
{
	SYB_LocalStatus[0] &= ~SYS_RED_SCAN;
}
#endif

