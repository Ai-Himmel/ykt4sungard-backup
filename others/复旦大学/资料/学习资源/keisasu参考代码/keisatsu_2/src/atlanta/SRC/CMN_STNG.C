/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_STNG.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_stng.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\define\sys_remo.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\memsw\define\mems_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mntsw_e.h"	/*	By Y.Suzuki 1996/11/09	*/
#if defined(FRA) 	/* by M.H.  8 Dec 97 */
#include "\src\atlanta\ext_v\ini_tbl.h"
#include "\src\atlanta\sh7043\define\sh_port.h"
#endif

#if defined(TWN) 	/* by M.H  17 Feb '98 */
#include "\src\atlanta\ext_v\ini_tbl.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"
#endif

#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/27 */
#include	"\src\atlanta\hinoki\define\m_param.h"
#include	"\src\atlanta\define\sys_stat.h"
/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
#include	"\src\atlanta\define\sysnd.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\ext_v\ncu_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#endif /* defined (KEISATSU) */


/*************************************************************************
	module		:[ダイヤル種別の獲得]
	function	:[
		1.
	]
	return		:[0               :DP10PPS
				  DIAL_SPEED_20PPS:DP20PPS
				  LINE_TYPE_TONE  :PB
	]
	common		:[]
	condition	:[]
	comment		:[
		1.\src\atlanta\define\status.h"をインクルードすること
		2.戻り値の確認は#define値で行うこと

	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_DialType(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_0] & (DIAL_SPEED_20PPS | LINE_TYPE_TONE)));
}


#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
/*************************************************************************
	module		:[拡張回線ダイヤル種別の獲得]
	function	:[
		1.
	]
	return		:[0                   :DP10PPS
				  DIAL_SPEED_20PPS_EXT:DP20PPS
				  LINE_TYPE_TONE_EXT  :PB
	]
	common		:[]
	condition	:[]
	comment		:[
		1.\src\atlanta\define\status.h"をインクルードすること
		2.戻り値の確認は#define値で行うこと

	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/27]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE	CHK_DialTypeExt(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_29] & (DIAL_SPEED_20PPS_EXT | LINE_TYPE_TONE_EXT)));
}
#endif


/*************************************************************************
	module		:[有効読取りサイズの獲得]
	function	:[
		1.
	]
	return		:[0:A4	(SYS_DOCUMENT_A4_SIZE)
				  1:B4	(SYS_DOCUMENT_B4_SIZE)
				  2:A3	(SYS_DOCUMENT_A3_SIZE)
	]
	common		:[]
	condition	:[]
	comment		:[
		1.\src\atlanta\define\sysdoc.h"をインクルードすること
		2.戻り値の確認は#define値で行うこと
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_ScanningWidth(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_1] & (SCANNING_WIDTH_B4 | SCANNING_WIDTH_A3)));
}

/*************************************************************************
	module		:[優先モードの獲得]
	function	:[
		1.
	]
	return		:[0:Normal		(SYS_NORMAL)
				  1:Fine		(SYS_FINE)
				  2:SuperFine	(SYS_SFINE)
				  3:GRAY		(SYS_GRAYxx)
	]
	common		:[]
	condition	:[]
	comment		:[
		1.\src\atlanta\define\sysdoc.h"をインクルードすること
		2.戻り値の確認は#define値で行うこと
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康、石橋正和(94/07/12)]
*************************************************************************/
UBYTE	CHK_PrimaryMode(void)
{
	switch (SYB_SettingStatus[SETTING_STATUS_1] & (PRIMARY_MODE_NORMAL
												 | PRIMARY_MODE_FINE
												 | PRIMARY_MODE_SFINE
												 | PRIMARY_MODE_GRAY)) {
	case PRIMARY_MODE_NORMAL:
		return(SYS_NORMAL);
	case PRIMARY_MODE_FINE:
		return(SYS_FINE);
	case PRIMARY_MODE_SFINE:

		if( SYB_MaintenanceSwitch[40] & 0x02 ){		/* 1996/06/17 By N.Sakamoto */
			return(SYS_EFINE);
		}
		else{
			if (CHK_UNI_HyperFineON()) { /** ハイパーファインである場合 '96,04,15 UNI By N.S.*/
				return(SYS_HFINE);
			}
			else { /** スーパーファインである場合 */
				return(SYS_SFINE);
			}
		}
	default:	/* case PRIMARY_MODE_GRAY: */
		if (CHK_Halftone64ON()) {		/** 64階調である場合 */
			if (CHK_Halftone2ON()) {	/** 写真2である場合 */
				return(SYS_GRAY64_SEP);
			}
			else {						/** 写真1である場合 */
				return(SYS_GRAY64);
			}
		}
		else {							/** 16階調である場合 */
			if (CHK_Halftone2ON()) {	/** 写真2である場合 */
				return(SYS_GRAY16_SEP);
			}
			else {						/** 写真1である場合 */
				return(SYS_GRAY16);
			}
		}
	}
}

/*************************************************************************
	module		:[優先濃度の獲得]
	function	:[
		1.
	]
	return		:[0:薄く			(SYS_LIGHT_DENSITY)
				  1:薄く－普通の間	(SYS_LIGHT_NORMAL_DENSITY)
				  2:普通			(SYS_NORMAL_DENSITY)
				  3:濃く－普通の間	(SYS_DARK_NORMAL_DENSITY)
				  4:濃く			(SYS_DARK_DENSITY)
	]
	common		:[]
	condition	:[]
	comment		:[
		1.\src\atlanta\define\sysdoc.h"をインクルードすること
		2.戻り値の確認は#define値で行うこと
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康,渡辺一章]
*************************************************************************/
UBYTE	CHK_PrimaryDensity(void)
{
	return((UBYTE)((SYB_SettingStatus[SETTING_STATUS_26] & (PRIMARY_CONTRAST_LIGHT        |
															PRIMARY_CONTRAST_LIGHT_NORMAL |
															PRIMARY_CONTRAST_NORMAL       |
															PRIMARY_CONTRAST_DARK_NORMAL  |
															PRIMARY_CONTRAST_DARK)) >> 4));
}

/*************************************************************************
	module		:[中間調16/64階調の獲得]
	function	:[
		1.
	]
	return		:[0    :16階調
				  0以外:64階調
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_Halftone64ON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_1] & HALFTONE_MODE_64));
}

/*************************************************************************
	module		:[写真1/2の獲得]
	function	:[
		1.
	]
	return		:[0    :写真1
				  0以外:写真2(像域分離)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/07/12]
	author		:[石橋正和]
*************************************************************************/
UBYTE	CHK_Halftone2ON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_1] & HALFTONE_MODE_2));
}

/*************************************************************************
	module		:[熱転写マルチパスリボン使用ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_MultiPassLibbonON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_2] & MULTI_PASS_INK_RIBBON));
}

/*************************************************************************
	module		:[熱転写/感熱印字方式の獲得]
	function	:[
		1.
	]
	return		:[0    :感熱
				  0以外:熱転写
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_HeatTransferON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_2] & HEAT_TRANSFER_ON));
}

/*************************************************************************
	module		:[ノンソートコピーの状態を獲得]
	function	:[
		1.
	]
	return		:[
				0:ノンソートコピー
				1:ソーティングコピー
				]
	common		:[SYB_SettingStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/26]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_NonSortCopy(void)
{
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_2] & STNG_NON_SORT_COPY));
}

/*************************************************************************
	module		:[ジャーナル自動出力設定の獲得]
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
	date		:[1995/12/12]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_JournalAutoPrintON(void)
{
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_2] & JOURNAL_AUTO_PRINT_ON));
}

/*************************************************************************
	module		:[ジャンクメール防止設定の獲得]
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
	date		:[1997/05/12]
	author		:[山口]
*************************************************************************/
UBYTE	CHK_BlockJunkFaxMode(void)
{
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_2] & BLOCK_JUNK_FAX_MODE3));
}

/*************************************************************************
	module		:[子電話(PHONE2)接続ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_Connecting2TelON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_3] & CONNECTING_2ND_TEL));
}

/*************************************************************************
	module		:[留守番電話のPHONE1/PHONE2接続の獲得]
	function	:[
		1.
	]
	return		:[0    :PHONE2
				  0以外:PHONE1
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_AnsMachinePhone1(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_3] & ANS_MACHINE_PHONE1));
}

/*************************************************************************
	module		:[保留メロディON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_HoldMelodyON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_3] & HOLD_MELODY_ON));
}

/*************************************************************************
	module		:[ブランチ検出ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/07/20]
	author		:[渡辺一章]
*************************************************************************/
UBYTE	CHK_BranchON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_3] & BRANCH_ON));
}

/*************************************************************************
	module		:[ダイヤルインON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_DialinModeON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_3] & DIAL_IN_ON));
}

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/06/16 By M.Kuwahara */
/*************************************************************************
	module		:[ナンバーディスプレイ設定ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/06/16]
	author		:[桑原美紀]
*************************************************************************/
UBYTE	CHK_NumberDisplayON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_30] & ND_MODE_ON));
}

/*************************************************************************
	module		:[ダイヤルイン設定ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/06/16]
	author		:[桑原美紀]
*************************************************************************/
UBYTE	CHK_DialinON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_30] & ND_DIAL_IN_ON));
}

/*************************************************************************
	module		:[モデムダイヤルイン設定ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/10/14]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_ModemDialinON(void)
{
	if ((SYB_SettingStatus[SETTING_STATUS_30] & ND_MODE_ON) &&
		(SYB_SettingStatus[SETTING_STATUS_3] & DIAL_IN_ON)) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[TEL2 のナンバーディスプレイ対応電話でナンバーディスプレイ処理をするかどうか獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/10/22]
	author		:[久保博]
*************************************************************************/
UBYTE	CHK_NumberDisplayByExtPhoneON(void)
{
	if (CHK_ModemDialinON()) { /* 暫定ですが、モデムダイヤルインのときは、TEL2 未接続とします。added by H.Kubo 1998/11/09 */
		return FALSE;
	}
	if ((SYB_SettingStatus[SETTING_STATUS_30] & ND_MODE_ON) &&
		(SYB_SettingStatus[SETTING_STATUS_30] & ND_TEL2_ND_ON)) {
		return (TRUE);
	}
	return (FALSE);
}

#endif	/* PRO_NUMBER_DISPLAY == ENABLE */

/*************************************************************************
	module		:[Tel/Fax待機時の優先モードの獲得]
	function	:[
		1.
	]
	return		:[0    :Tel優先
				  0以外:Fax優先
	]
	common		:[]
	condition	:[]
	comment		:[ANZUでは未使用となる]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
#if (0)	/* TEL待機を追加のためこのﾋﾞｯﾄを削除します（待機ﾓｰﾄﾞに吸収されているので問題はなし）by K.Watanabe 1997/03/22 */
//UBYTE	CHK_PrimaryFax(void)
//{
//	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_3] & PRIMARY_FAX));
//}
#endif

/*************************************************************************
	module		:[自動受信モードの獲得]
	function	:[
		1.
	]
	return		:[
		0:Tel待機
		1:Fax待機
		2:Fax/Tel待機
		3:Tel/Fax待機
		4:Ans/Fax待機
		5:Dialin 待機/*PRO_DIALIN_SW == DISABLE By Y.Suzuki 2002/08/08
	]
	common		:[]
	condition	:[]
	comment		:[
		ＡＮＺＵからＦａｘ／Ｔｅｌ待機が追加になるので変更

		POPLAR_BでＴｅｌ待機が追加になるので変更
		注）あわせてCMN_PresentReceiveMode()の戻り値と値を同じになるようにした（SYS_TEL_READY等）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康,渡辺一章]
*************************************************************************/
UBYTE	CHK_AutoRxMode(void)
{
 #if (0) /* For ANZU 1995/12/04 Eguchi */
//	return((UBYTE)((SYB_SettingStatus[SETTING_STATUS_3] & (AUTO_RX_MODE_TELFAX | AUTO_RX_MODE_ANSFAX)) >> 6));
 #endif
 #if (0)	/* For POPLAR_B 1997/03/22 by K.Watanabe */
//	return((UBYTE)((SYB_SettingStatus[SETTING_STATUS_3] & (AUTO_RX_MODE_FAXTEL | AUTO_RX_MODE_TELFAX)) >> 6));
 #endif
 #if (PRO_DIALIN_SW == DISABLE)/*By Y.Suzuki 2002/08/07*/
	if (SYB_SettingStatus[SETTING_STATUS_3] & DIAL_IN_ON) {
		return(5);
	}
	return((UBYTE)((SYB_SettingStatus[SETTING_STATUS_3] & (MANUAL_RX_MODE      |
														   AUTO_RX_MODE_FAX    |
														   AUTO_RX_MODE_FAXTEL |
														   AUTO_RX_MODE_TELFAX |
														   AUTO_RX_MODE_ANSFAX)) >> 5));
 #else
	return((UBYTE)((SYB_SettingStatus[SETTING_STATUS_3] & (MANUAL_RX_MODE      |
														   AUTO_RX_MODE_FAX    |
														   AUTO_RX_MODE_FAXTEL |
														   AUTO_RX_MODE_TELFAX |
														   AUTO_RX_MODE_ANSFAX)) >> 5));
 #endif
}

/*************************************************************************
	module		:[閉域通信ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_ClosedNetworkON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_4] & CLOSED_NETWORK_ON));
}

/*************************************************************************
	module		:[パスワード送信ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_SecurityTxON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_4] & SECURITY_TRANSMISSION));
}

/*************************************************************************
	module		:[ダイレクトメール防止ON/OFFの獲得]
	function	:[
		1.1997/05/15  By T.Yamaguchi 未使用
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_BlockJunkFaxON(void)
{
	/* 注．SYB_SettingStatus[SETTING_STATUS_2]に変更 CHK_BlockJunkFaxMode()を参照してください */
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_4] & BLOCK_JUNK_FAX_ON));
}

/*************************************************************************
	module		:[メッセージ(カバーページ)送信ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_MessageTxON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_4] & MESSAGE_TRANSMIT_ON));
}

/*************************************************************************
	module		:[ページ合成ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_PageCompoundON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_4] & PRINTER_NO_FORM_FEED));
}

/*************************************************************************
	module		:[固定値による受信縮小率の獲得]
	function	:[
		1.
	]
	return		:[0:縮小率0(最小)
				  1:縮小率1
				  2:縮小率2
				  3:縮小率3
				  4:縮小率4
				  5:縮小率5
				  6:縮小率6
				  7:縮小率7(最大)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/06]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RxFixedReduction(void)
{
	return((UBYTE)((SYB_SettingStatus[SETTING_STATUS_4] & (RX_REDUCTION_1 | RX_REDUCTION_2 |
														   RX_REDUCTION_3 | RX_REDUCTION_4 |
														   RX_REDUCTION_5 | RX_REDUCTION_6 |
														   RX_REDUCTION_7 )) >> 5));
}

/*************************************************************************
	module		:[RS232Cスピードの獲得]
	function	:[
		1.
	]
	return		:[0: AUTO bps
				  1:  600 bps
				  2: 1200 bps
				  3: 2400 bps
				  4: 4800 bps
				  5: 9600 bps
				  6:19200 bps
]
	common		:[]
	condition	:[]
	comment		:[
		1.\src\atlanta\define\sysrs.h"をインクルードすること
		2.戻り値の確認は#define値で行うこと

		300 ppsのところをVARIABLE(AUTO)に変えました。1996/08/07 Y.matsukuma

	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE	CHK_RS232C_SpeedFlsRom(void)
#else
UBYTE	CHK_RS232C_Speed(void)
#endif
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_5] & (RS232C_SPEED_VARIABLE |
														  RS232C_SPEED_600 |
														  RS232C_SPEED_1200 |
														  RS232C_SPEED_2400 |
														  RS232C_SPEED_4800 |
														  RS232C_SPEED_9600 |
														  RS232C_SPEED_19200)));
}

/*************************************************************************
	module		:[RS232Cデータ長の獲得]
	function	:[
		1.
	]
	return		:[0    :7ビット
				  0以外:8ビット
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RS232C_DataLength8(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_5] & RS232C_DATA_LENGTH_8));
}

/*************************************************************************
	module		:[RS232Cパリティの獲得]
	function	:[
		1.
	]
	return		:[0:NONE
				  1:ODD
				  2:EVEN
	]
	common		:[]
	condition	:[]
	comment		:[
		1.\src\atlanta\define\sysrs.h"をインクルードすること
		2.戻り値の確認は#define値で行うこと
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RS232C_Parity(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_5] & (RS232C_PARITY_NONE |
														  RS232C_PARITY_ODD |
														  RS232C_PARITY_EVEN)));
}

/*************************************************************************
	module		:[RS232Cストップビット長の獲得]
	function	:[
		1.
	]
	return		:[0    :1ビット
				  0以外:2ビット
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RS232C_StopLength2(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_5] & RS232C_STOP_LENGTH_2));
}

/*************************************************************************
	module		:[済スタンプのdefault値ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_StampON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_6] & DOCUMENT_STAMP_ON));
}

/*************************************************************************
	module		:[メモリ送信のdefault値ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_MemoryTxON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_6] & MEMORY_TRANSMISSION_ON));
}

/*************************************************************************
	module		:[部門管理ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_DepartmentON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_6] & SECTION_CHECK_ON));
}

/*************************************************************************
	module		:[通信証ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_ConfirmationReportON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_6] & CONFIRM_ON));
}

/*************************************************************************
	module		:[受領証ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RCR_ON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_6] & CONFIRM_TYPE_RCR));
}

/*************************************************************************
	module		:[ECMON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_ECM_ON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_6] & ECM_SETTING));
}

/*************************************************************************
	module		:[コピー禁止ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_CopyProtectON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_6] & COPY_PROTECT_ON));
}

/*************************************************************************
	module		:[リモート診断ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RemoteDiagON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_6] & REMOTE_DIAG_ON));
}

/*************************************************************************
	module		:[しきい値の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255mm]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RxMargin(void)
{
	return((UBYTE)SYB_SettingStatus[RX_MARGIN]);
}

/*************************************************************************
	module		:[リダイヤル回数の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255回]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RedialCount(void)
{
	return((UBYTE)SYB_SettingStatus[NUMBER_OF_REDIAL]);
}

/*************************************************************************
	module		:[リダイヤル間隔の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255分]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RedialInterval(void)
{
	return((UBYTE)SYB_SettingStatus[REDIAL_INTERVAL]);
}

/*************************************************************************
	module		:[ポーズ時間の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255秒]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_PauseTime(void)
{
	return((UBYTE)SYB_SettingStatus[DIALING_PAUSE]);
}

/*************************************************************************
	module		:[呼出ベル回数の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255回]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/06/08]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RingNumber(void)
{
	return((UBYTE)SYB_SettingStatus[NUMBER_OF_RINGS]);
}

/*************************************************************************
	module		:[呼出ベル回数の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255回]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RingCount(void)
{
#if (PRO_REMOTE_FAX == ENABLE)
	UBYTE	rxmode;
#endif

#if (PRO_REMOTE_FAX == DISABLE)
/*-------------------------*/
/** リモートＦＡＸ機能無し */
/*-------------------------*/

	return((UBYTE)SYB_SettingStatus[NUMBER_OF_RINGS]);

#endif
#if (PRO_REMOTE_FAX == ENABLE)
/*-------------------------*/			/** リモートＦＡＸ，ＴＡＤ関係のベル回数を追加 1994/04/08 Y.M */
/** リモートＦＡＸ機能有り */
/*-------------------------*/

	rxmode = CMN_PresentReceiveMode();

 #if (PRO_BUILTIN_TAD == ENABLE)
	/*-------------*/
	/** 内蔵ＴＡＤ */
	/*-------------*/

	if ((rxmode == SYS_ANS_FAX_READY) 	||
		(rxmode == SYS_DIALIN_TAD_READY) ||
		(rxmode == SYS_TAD_READY)) {

		if ((!SYS_RemoteFaxTAD_DataRecFlag) ||
			(SYS_RemoteFaxTAD_DataRecFlag == REMOTE_FAX_DATA) && (!CHK_RemoteFaxON())) {
			return((UBYTE)SYB_SettingStatus[TOLL_SAVER_BELL_COUNT]);
		}
		else {
			return((UBYTE)CHK_TollSarver1stBellNum());
		}
	}
	else{
		return((UBYTE)SYB_SettingStatus[NUMBER_OF_RINGS]);
	}
 #endif
 #if (PRO_BUILTIN_TAD == DISABLE)
	/*---------------*/
	/** 外付けＴＡＤ */
	/*---------------*/
	if ((rxmode == SYS_FAX_READY) && (CHK_RemoteFaxON())) {
		if (SYS_RemoteFaxTAD_DataRecFlag) {
			return(CHK_TollSarver1stBellNum());
		}
		else {
			return((UBYTE)SYB_SettingStatus[TOLL_SAVER_BELL_COUNT]);
		}
	}
	else {
		return((UBYTE)SYB_SettingStatus[NUMBER_OF_RINGS]);
	}
 #endif
#endif
}

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/12 */
/*************************************************************************
	module		:[拡張回線によって呼出ベル回数の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255回]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/07/12]
	author		:[SMuratec 李]
*************************************************************************/
UBYTE	CHK_ExtRingCount(void)
{
	return((UBYTE)SYB_SettingStatus[NUMBER_OF_RINGS_EXT]);
}
#endif /* defined (KEISATSU) */

/*************************************************************************
	module		:[親展受信原稿保持期間]
	function	:[
		1.
	]
	return		:[0～255:0～255日]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_SecureMailHoldTime(void)
{
	return((UBYTE)SYB_SettingStatus[SECURE_MAIL_HOLD_TIME]);
}

/*************************************************************************
	module		:[任意受信縮小率]
	function	:[
		1.
	]
	return		:[0～255:0～255%]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_FreeReduction(void)
{
	return((UBYTE)SYB_SettingStatus[FREE_REDUCTION]);
}

/*************************************************************************
	module		:[リモートFaxON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RemoteFaxON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_15] & REMOTE_FAX_ON));
}

/*************************************************************************
	module		:[リモートFax取出し時の原稿消去ON/OFF]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RemoteFaxDEL(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_15] & REMOTE_FAX_DEL));
}

/*************************************************************************
	module		:[リモートFax設定時の受信原稿プリントON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RemoteFaxPRN(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_15] & REMOTE_FAX_PRN));
}

/*************************************************************************
	module		:[ポケベル呼び出しON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/02/01]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_TAD_PocketBellON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_15] & TAD_POCKET_BELL_ON));
}

/*************************************************************************
	module		:[内蔵TADメッセージの固定/ユーザメッセージの獲得]
	function	:[
		1.
	]
	return		:[0    :固定メッセージ
				  0以外:ユーザメッセージ
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/02/01]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_TAD_OGM_UserMessage(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_15] & TAD_OGM_USER_MESSAGE));
}

/*************************************************************************
	module		:[中中継ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/02/01]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RelayedRelayTxON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_15] & RELAYED_RELAY_TX_ON));
}

/*************************************************************************
	module		:[キャッチホンON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/03]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_CatchPhoneON(void)
{
/*	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_15] & CATCH_PHONE_ON));	下記変更 By M.Tachibana 1998/11/09 */
	return((UBYTE)CHK_UNI_CatchPhoneON());
}

/*************************************************************************
	module		:[リングマスタON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/03]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_RingMasterON(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_15] & RING_MASTER_ON));
}

/*************************************************************************
	module		:[リングマスタのベルパターンの獲得]
	function	:[
		1.
	]
	return		:[1～6:1～6回]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/03]
	author		:[吉川弘康]
				:	リングマスタパターン設定を16から13に移動。'95.03/23 By J.Miyazaki
*************************************************************************/
UBYTE	CHK_RingMasterPattern(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_13] & (RING_MASTER_PATTERN_1 |
														   RING_MASTER_PATTERN_2 |
														   RING_MASTER_PATTERN_3 |
														   RING_MASTER_PATTERN_4 |
														   RING_MASTER_PATTERN_5 |
														   RING_MASTER_PATTERN_6 |
														   RING_MASTER_PATTERN_7 |
														   RING_MASTER_PATTERN_8)));
}

/*************************************************************************
	module		:[コピー用固定縮小率の獲得]
	function	:[
		1.
	]
	return		:[0:縮小率0(最小)
				  1:縮小率1
				  2:縮小率2
				  3:縮小率3
				  4:縮小率4
				  5:縮小率5
				  6:縮小率6
				  7:縮小率7(最大)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/03]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_CopyFixedReduction(void)
{
	return((UBYTE)((SYB_SettingStatus[SETTING_STATUS_16] & (COPY_FIXED_REDUCTION_1 | COPY_FIXED_REDUCTION_2 |
															COPY_FIXED_REDUCTION_3 | COPY_FIXED_REDUCTION_4 |
															COPY_FIXED_REDUCTION_5 | COPY_FIXED_REDUCTION_6 |
											 				COPY_FIXED_REDUCTION_7 )) >> 3));
}

/*************************************************************************
	module		:[PRINTER受信のdefault値ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0    :OFF
				  0以外:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/06/22]
	author		:[吉川弘康]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE	CHK_PrinterRxONFlsRom(void)
#else
UBYTE	CHK_PrinterRxON(void)
#endif
{
#if(PRO_PAPER_TYPE == ROLL_PAPER)
  #if (0) /* (PRO_PRINTER_RX == ENABLE) comment by H.Hirao 1998/12/24 */
	/* UNISWでON/OFFできるようにする
	** added by H.Hirao 1998/11/11
	*/
	return((UBYTE)CHK_UNI_V17PrinterRx());
  #else
	/* 紅葉、さつきのみ有効 13.Jly'94 Y.Suzuki */
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_16] & PRINTER_RECEIVE_ON));
  #endif
#else
	return(0);
#endif
}

/*************************************************************************
	module		:[サイレントモードの設定状態の獲得]
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
	date		:[1996/04/15]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_SilentOperation(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_16] & STG_SILENT_OPERATION));
}

/*************************************************************************
	module		:[遠隔操作で留守モードにしない/するの獲得]
	function	:[
		1.
	]
	return		:[0    :留守モードにしない
				  0以外:留守モードにする
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/11]
	author		:[吉川弘康]
*************************************************************************/
#if (0)	/* Delete By Eguchi 1994/06/20 */
//UBYTE CHK_AllModeToAnsMode(void)
//{
//	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_16] & ALL_MODE_TO_ANS_MODE));
//}
#endif

/*************************************************************************
	module		:[コピー用しきい値の獲得]
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
	date		:[1994/03/03]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_CopyMargin(void)
{
	return((UBYTE)SYB_SettingStatus[COPY_MARGIN]);
}

/*************************************************************************
	module		:[トールセーバ用ベル回数の獲得]
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
	date		:[1994/03/03]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_TollSaverBellCount(void)
{
	return((UBYTE)SYB_SettingStatus[TOLL_SAVER_BELL_COUNT]);
}

/*************************************************************************
	module		:[手動記録紙選択の上段サイズの獲得]
	function	:[
		1.
	]
	return		:[0:UPPER_SIZE_NONE
				  1:UPPER_SIZE_A4
				  2:UPPER_SIZE_B4
				  3:UPPER_SIZE_LETTER
				  4:UPPER_SIZE_LEGAL
				  5:UPPER_SIZE_F4
				]
	common		:[]
	condition	:[]
	comment		:[
		1.\src\atlanta\define\status.h"をインクルードすること
		2.戻り値の確認は#define値で行うこと
		94/11/11 By j.masuda
			F4 ｻｲｽﾞ ﾂｲｶ
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/03]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_UpperManualCassete(void)
{
	return((UBYTE)(SYB_SettingStatus[UPPER_SIZE] & (UPPER_SIZE_A4 |
													UPPER_SIZE_B4 |
													UPPER_SIZE_LETTER |
													UPPER_SIZE_LEGAL |
													UPPER_SIZE_F4)));
}

/*************************************************************************
	module		:[手動記録紙選択の上段サイズの獲得（ＰＣプリント対応用）]
	function	:[
		1.
	]
	return		:[
		 0:PCR_MANUAL_SIZE_NONE	 1:PCR_MANUAL_SIZE_A5	 2:PCR_MANUAL_SIZE_LT
		 3:PCR_MANUAL_SIZE_A4	 4:PCR_MANUAL_SIZE_LG	 5:PCR_MANUAL_SIZE_B5R
		 6:PCR_MANUAL_SIZE_B4	 7:PCR_MANUAL_SIZE_A3	 8:PCR_MANUAL_SIZE_A4R
		 9:PCR_MANUAL_SIZE_LTR	10:PCR_MANUAL_SIZE_F4	11:PCR_MANUAL_SIZE_A5R
		12:PCR_MANUAL_SIZE_POST	13:PCR_MANUAL_SIZE_LD	14:PCR_MANUAL_SIZE_GLTR
		15:PCR_MANUAL_SIZE_EXER	16:PCR_MANUAL_SIZE_INVR	17:PCR_MANUAL_SIZE_GLG
		18:PCR_MANUAL_SIZE_GLT	19:PCR_MANUAL_SIZE_CARD	20:PCR_MANUAL_SIZE_EXE
		21:PCR_MANUAL_SIZE_B5	22:PCR_MANUAL_SIZE_C5	23:PCR_MANUAL_SIZE_HLT
		24:PCR_MANUAL_SIZE_INV	25:PCR_MANUAL_SIZE_B6	26:PCR_MANUAL_SIZE_DL
		27:PCR_MANUAL_SIZE_CM10	28:PCR_MANUAL_SIZE_A6	29:PCR_MANUAL_SIZE_MNK
		30:PCR_MANUAL_SIZE_35	31:PCR_MANUAL_SIZE_USER
	]
	common		:[]
	condition	:[]
	comment		:[
		1.\src\atlanta\define\status.h"をインクルードすること
		2.戻り値の確認は#define値で行うこと
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/10/09]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
#if (0)	/* By M.Tachibana 1997/06/30 */
UBYTE	CHK_PCR_UpperManualCassete(void)
{
	return((UBYTE)(SYB_SettingStatus[PCR_MANUAL_SIZE] & (PCR_MANUAL_SIZE_A5   | PCR_MANUAL_SIZE_LT   |
														PCR_MANUAL_SIZE_A4   | PCR_MANUAL_SIZE_LG   |
														PCR_MANUAL_SIZE_B5R  | PCR_MANUAL_SIZE_B4   |
														PCR_MANUAL_SIZE_A3   | PCR_MANUAL_SIZE_A4R  |
														PCR_MANUAL_SIZE_LTR  | PCR_MANUAL_SIZE_F4   |
														PCR_MANUAL_SIZE_A5R  | PCR_MANUAL_SIZE_POST |
														PCR_MANUAL_SIZE_LD   | PCR_MANUAL_SIZE_GLTR |
														PCR_MANUAL_SIZE_EXER | PCR_MANUAL_SIZE_INVR |
														PCR_MANUAL_SIZE_GLG  | PCR_MANUAL_SIZE_GLT  |
														PCR_MANUAL_SIZE_CARD | PCR_MANUAL_SIZE_EXE  |
														PCR_MANUAL_SIZE_B5   | PCR_MANUAL_SIZE_C5   |
														PCR_MANUAL_SIZE_HLT  | PCR_MANUAL_SIZE_INV  |
														PCR_MANUAL_SIZE_B6   | PCR_MANUAL_SIZE_DL   |
														PCR_MANUAL_SIZE_CM10 | PCR_MANUAL_SIZE_A6   |
														PCR_MANUAL_SIZE_MNK  | PCR_MANUAL_SIZE_35   |
														PCR_MANUAL_SIZE_USER)));
}
#endif
UBYTE	CHK_PCR_ManualCassetteSize(void)
{
	return((UBYTE)(SYB_SettingStatus[PCR_MANUAL_SIZE]));
}
#endif

/*************************************************************************
	module		:[手動記録紙選択の下段サイズの獲得]
	function	:[
		1.
	]
	return		:[0:LOWER_SIZE_NONE
				  1:LOWER_SIZE_A4
				  2:LOWER_SIZE_B4
				  3:LOWER_SIZE_LETTER
				  4:LOWER_SIZE_LEGAL
				  5:LOWER_SIZE_F4
			]
	common		:[]
	condition	:[]
	comment		:[
		1.\src\atlanta\define\status.h"をインクルードすること
		2.戻り値の確認は#define値で行うこと
		94/11/11 By j.masuda
			F4 ｻｲｽﾞ ﾂｲｶ
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/03]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_LowerManualCassete(void)
{
	return((UBYTE)(SYB_SettingStatus[LOWER_SIZE] & (LOWER_SIZE_A4 |
													LOWER_SIZE_B4 |
													LOWER_SIZE_LETTER |
													LOWER_SIZE_LEGAL |
													LOWER_SIZE_F4)));
}

/*************************************************************************
	module		:[受信完了アラーム機能ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0:	OFF
				  0以外 ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/07/21]
	author		:[渡辺一章]
*************************************************************************/
#if (0)
//#if defined(GBR)
//UBYTE	CHK_GBR_RxAlarm(void)
//{
//	return((UBYTE)(SYB_SettingStatus[UPPER_SIZE] & (GBR_RX_ALARM)));
//}
//#endif
#endif

/*************************************************************************
	module		:[GBR Scurity Receive機能ON/OFFの獲得]
	function	:[
		1.
	]
	return		:[0:	OFF
				  0以外 ON
				]
	common		:[]
	condition	:[]
	comment		:[この関数は杏では未使用.杏のセキュリティ受信は別
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/01/26]
	author		:[原田]
*************************************************************************/
#if (0)
//#if defined(GBR)
//UBYTE	CHK_GBR_SecurityRx(void)
//{
//	return((UBYTE)(SYB_SettingStatus[UPPER_SIZE] & (GBR_SECURITY_RX)));
//}
//#endif
#endif

/*************************************************************************
	module		:[受信原稿のプリント枚数の獲得]
	function	:[
		1.
	]
	return		:[0:	 1
				  1～255:1～255
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/06/26]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CHK_NumberOfPrintingRxDocuments(void)
{

	if (SYB_SettingStatus[NUMBER_OF_PRINTING_RX_DOCUMENTS]) {
		return((UBYTE)(SYB_SettingStatus[NUMBER_OF_PRINTING_RX_DOCUMENTS]));
	}
	else {
		return(1);
	}
}

/*************************************************************************
	module		:[回転受信しきい値の獲得]
	function	:[
		1.
	]
	return		:[0～85:0～85mm]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/08/30]
	author		:[渡辺一章]
*************************************************************************/
UBYTE	CHK_RotateMargin(void)
{
	return((UBYTE)SYB_SettingStatus[ROTATE_RX_MARGIN]);
}

/*************************************************************************
	module		:[夏時間自動切り替え設定の獲得]
	function	:[
		1.
	]
	return		:[
				0:OFF
				0以外：ON
				]
	common		:[SYB_SettingStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keywor		:[CMN]
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_DayLightSavingAuto(void)
{
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_23] & DAYLIGHT_SAVING_AUTO));
}

/*************************************************************************
	module		:[メモリー受信原稿プリントプロテクト設定の獲得]
	function	:[
		1.
	]
	return		:[
				0:OFF
				0以外：ON
				]
	common		:[SYB_SettingStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keywor		:[CMN]
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_SecurityReceiveON(void)
{
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_23] & SECURITY_RX_ON));
}

/*************************************************************************
	module		:[オペレーションプロテクト設定の獲得]
	function	:[
		1.
	]
	return		:[
				0:OFF
				0以外：ON
				]
	common		:[SYB_SettingStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keywor		:[CMN]
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_OperationProtect(void)
{
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_23] & OPERATION_PROTECT_ON));
}

/*************************************************************************
	module		:[部門管理プロテクト設定の獲得]
	function	:[
		1.
	]
	return		:[
				0:OFF
				0以外：ON
				]
	common		:[SYB_SettingStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keywor		:[CMN]
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_SectionCheckProtect(void)
{
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_23] & SECTION_CHECK_PROTECT_ON));
}

/*************************************************************************
	module		:[ＰＩＮアクセスモード設定の獲得]
	function	:[
		1.
	]
	return		:[
				0:OFF
				0以外：ON
				]
	common		:[SYB_SettingStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keywor		:[CMN]
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_PIN_AccessMode(void)
{
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_23] & (PIN_ACCESS_MODE1 | PIN_ACCESS_MODE2)));
}

/*************************************************************************
	module		:[受信完了アラーム設定の獲得]
	function	:[
		1.
	]
	return		:[
				0:OFF
				0以外:ON
				]
	common		:[]
	condition	:[]
	comment		:[GBRのみ有効な機能である]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/08/14]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_AudibleAlarmON(void)
{
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_23] & AUDIBLE_ALARM));
}

/*************************************************************************
	module		:[リモート受信設定の獲得]
	function	:[
		1.
	]
	return		:[
				0:OFF
				0以外:ON
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/01/24]
	author		:[山口]
*************************************************************************/
UBYTE	CHK_RemoteRxON(void)
{
#if (PRO_REMOTE_RX == ENABLE)	/* 1998/01/24  By T.Yamaguchi */
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_23] & REMOTE_RX_ON));
#else
	return(0);
#endif
}

/*************************************************************************
	module		:[音声応答設定の獲得]
	function	:[
		1.TEL/FAX待機時の音声応答メッセージ１の有無
	]
	return		:[
				0:OFF
				0以外:ON
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[山口]
*************************************************************************/
UBYTE	CHK_VoiceMessageON(void)
{
#if (PRO_VOICE_ANSWER == ENABLE)
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_2] & VOICE_MESSAGE_ON));
#else
	return(0);
#endif
}

#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
/*************************************************************************
	module		:[オンフック受信設定の獲得]
	function	:[
		1.
	]
	return		:[
				0:OFF
				0以外:ON
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/03/13]
	author		:[福本貴吉]
*************************************************************************/
UBYTE	CHK_OnHookRX_ON(void)
{
	return ((UBYTE)(SYB_SettingStatus[SETTING_STATUS_26] & ONHOOK_RX_ON));
}
#endif

/*************************************************************************
	module		:[プリンタ時間の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255分]
	common		:[]
	condition	:[]
	comment		:[MATSU用のためRICEでは未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/05]
	author		:[吉川弘康]
*************************************************************************/
#if (0)
//UBYTE	CHK_PrinterTime(void)
//{
//	return((UBYTE)SYB_SettingStatus[PRINTER_TIME]);
//}
#endif

/*************************************************************************
	module		:[待機モードの獲得]
	function	:[
		1.
	]
	return		:[
		0    :ファクスモード
		0以外:コピーモード
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/06/11]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CHK_ReadyModeCopy(void)
{
#if (PRO_COPY_FAX_MODE == ENABLE)
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_26] & (READY_MODE_COPY)));
#else
	return(0);	/* ＦＡＸモード固定 */
#endif
}

/*************************************************************************
	module		:[自動受信キーの状態獲得（受信モードの獲得）]
	function	:[
		1.
	]
	return		:[
		TRUE	:自動受信
		FALSE	:手動受信
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/03/22]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CHK_AutoRxSwitch(void)
{
	UBYTE	ret;	/* リターン値 */

#if (PRO_AUTO_RX_SWITCH == ENABLE)
 	ret = (UBYTE)(SYB_RxModeSwitch & SYS_AUTO_CALLED_SW);
#else
	if (CHK_AutoRxMode() == MANUAL_RX_MODE) {
		ret = FALSE;
	}
	else {
		ret = TRUE;
	}
#endif

	return(ret);
}


/*************************************************************************
	module		:[Phoneタイプの獲得]
	function	:[
		1.
	]
	return		:[
				]
	common		:[二回線仕様にて新規追加]
	condition	:[]
	comment		:[
		1997/11/4 ＰＯＰＬＡＲ＿Ｈは標準で２回線（標準／拡張）のため、判断追加 by O.Kimoto
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/12/12]
	author		:[松隈]
*************************************************************************/
UBYTE CHK_MultiPhoneType(UBYTE Board)
{
	switch (Board ) {
	case 0:	/* （ホスト）*/
		return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_0] & (DIAL_SPEED_20PPS | LINE_TYPE_TONE)));
		break;
	case 1:	/* （オプションボード１）*/
		return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_0] & (DIAL_SPEED_20PPS_1 | LINE_TYPE_TONE_1)));
		break;
	case 2:	/* （オプションボード２）*/
		return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_0] & (DIAL_SPEED_20PPS_2 | LINE_TYPE_TONE_2)));
		break;
	case 3:	/* （オプションボード３）*/
		return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_28] & (DIAL_SPEED_20PPS_3 | LINE_TYPE_TONE_3)));
		break;
	case 4:	/* （オプションボード４）*/
		return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_28] & (DIAL_SPEED_20PPS_4 | LINE_TYPE_TONE_4)));
		break;
	case 5:	/* （オプションボード５）*/
		return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_28] & (DIAL_SPEED_20PPS_5 | LINE_TYPE_TONE_5)));
		break;
	case 6:	/* （オプションボード６）*/
		return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_29] & (DIAL_SPEED_20PPS_6 | LINE_TYPE_TONE_6)));
		break;
	case 7:	/* （オプションボード７）*/
		return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_29] & (DIAL_SPEED_20PPS_7 | LINE_TYPE_TONE_7)));
		break;
	case 8:	/* （オプションボード８）*/
		return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_29] & (DIAL_SPEED_20PPS_8 | LINE_TYPE_TONE_8)));
		break;

	/* ＰＯＰＬＡＲ＿Ｈは標準で２回線収容（標準／拡張）の為、追加 By O.Kimoto 1997/11/04 */
	case 0x10:	/* 内蔵（拡張）*/
		return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_29] & (DIAL_SPEED_20PPS_EXT | LINE_TYPE_TONE_EXT)));
		break;

	}
}



/*************************************************************************
	module		:[ラインタイプ獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		1997/11/4 ＰＯＰＬＡＲ＿Ｈは標準で収容回線が2回線（標準／拡張）のため、追加
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/12/27]
	author		:[松隈]
*************************************************************************/
UBYTE CHK_MultiLineType(UBYTE Board)
{
	switch (Board) {
	case 0:	/* （ホスト）*/
		return((UBYTE)CHK_PBX());
		break;
	case 1:	/* （オプションボード１）*/
		return((UBYTE)CHK_PBX1());
		break;
	case 2:	/* （オプションボード２）*/
		return((UBYTE)CHK_PBX2());
		break;
	case 3:	/* （オプションボード３）*/
		return((UBYTE)CHK_PBX3());
		break;
	case 4:	/* （オプションボード４）*/
		return((UBYTE)CHK_PBX4());
		break;
	case 5:	/* （オプションボード５）*/
		return((UBYTE)CHK_PBX5());
		break;
	case 6:	/* （オプションボード６）*/
		return((UBYTE)CHK_PBX6());
		break;
	case 7:	/* （オプションボード７）*/
		return((UBYTE)CHK_PBX7());
		break;
	case 8:	/* （オプションボード８）*/
		return((UBYTE)CHK_PBX8());
		break;

	/* ＰＯＰＬＡＲ＿Ｈは標準で２回線収容（標準／拡張）の為、追加 By O.Kimoto 1997/11/04 */
	case 0x10:	/* 内蔵（拡張）*/
		return((UBYTE)CHK_PBX_EXT());
		break;
	}
}

/*************************************************************************
	module		:[送受信タイプ獲得]
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
	date		:[1997/1/18]
	author		:[松隈]
*************************************************************************/
UBYTE CHK_MultiTxRxType(UBYTE Board)
{
	switch (Board) {
	case 0:	/* （ホスト）*/
		return((UBYTE)CHK_UNI_Line0_TxRx());
		break;
	case 1:	/* （オプションボード１）*/
		return((UBYTE)CHK_UNI_Line1_TxRx());
		break;
	case 2:	/* （オプションボード２）*/
		return((UBYTE)CHK_UNI_Line2_TxRx());
		break;
	case 3:	/* （オプションボード３）*/
		return((UBYTE)CHK_UNI_Line3_TxRx());
		break;
	case 4:	/* （オプションボード４）*/
		return((UBYTE)CHK_UNI_Line4_TxRx());
		break;
	case 5:	/* （オプションボード５）*/
		return((UBYTE)CHK_UNI_Line5_TxRx());
		break;
	case 6:	/* （オプションボード６）*/
		return((UBYTE)CHK_UNI_Line6_TxRx());
		break;
	case 7:	/* （オプションボード７）*/
		return((UBYTE)CHK_UNI_Line7_TxRx());
		break;
	case 8:	/* （オプションボード８）*/
		return((UBYTE)CHK_UNI_Line8_TxRx());
		break;
	/* ＰＯＰＬＡＲ＿Ｈは標準で２回線収容（標準／拡張）の為、追加 By O.Kimoto 1997/11/04 */
	case 0x10:	/* 内蔵（拡張）*/
		return((UBYTE)CHK_UNI_Line_EXT_TxRx());
		break;
	}
}


#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/11 */
/*************************************************************************
	module		:[擬似2回線のPHONE2状態の獲得]
	function	:[
		1.疑似２回線設定のPHONE2の接続状態をチェックします
	]
	return		:[
		0    :LINE側
		0以外:EXT.LINE側
	]
	common		:[]
	condition	:[
		POPLAR_Hで使用します
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/11]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CHK_Phone2ExtLineOn(void)
{
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/22 */
	return TRUE;
#else /* !defined (KEISATSU) */
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_26] & PHONE2_EXTLINE_ON));
#endif /* defined (KEISATSU) */
}
#endif

#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
/*************************************************************************
	module		:[擬似2回線によって回線設定値の獲得]
	function	:[
	]
	return		:[
		0    :EXT.LINE側
		0以外:LINE側
	]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/06/27]
	author		:[SMuratec 李]
*************************************************************************/
UBYTE CHK_LineSetting(void)
{
	return((UBYTE)(SYB_SettingStatus[SETTING_STATUS_31] & SETTING_LINE));
}
/*************************************************************************
	module		:[警電優先受信機能は有効かどうかの判断]
	function	:[
	]
	return		:[
		0    :無効
		0以外:有効
	]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/06/28]
	author		:[SMuratec 李]
*************************************************************************/
UBYTE CHK_KEIDENRxPriority(void)
{
	if ( !(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) ) {	/* 指令起動信号OFFの場合 */
		/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
		if ((NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
			|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
			return FALSE;
		}
		return((UBYTE)(SYB_MachineParameter[M_PARA_SW_I0] & KEIDEN_RX_PRIORITY));
	}
	return (FALSE);
}
#endif /* defined (KEISATSU) */

/*************************************************************************
	module		:[Get the status of hard dip switch for the protection of servise function.]
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
	date		:[1997/12/08]
	author		:[M.Harada]
*************************************************************************/
#if defined(FRA) || defined(TWN)
UBYTE CHK_HardDipProtection(void)
{
	unsigned char	sw_status;

	if (HardDIP_SwitchEnable){
		sw_status = ~(DSW());
		if ((sw_status & IO_BIT_DSW3) == IO_BIT_DSW3){
			return(YES);	/* set to ON */
		}
		return(NO);			/* set to Off */
	}
	return(NO);				/* disable Hard Dip Switch */
}   
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)
/*************************************************************************
	module		:[ワープ機能の獲得]
	function	:[
	]
	return		:[
		０    :ＯＦＦ
		０以外:ＯＮ
	]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/06/26]
	author		:[桑原美紀]
*************************************************************************/
UBYTE CHK_WarpFunctionON(void)
{
	return(SYB_SettingStatus[SETTING_STATUS_30] & WARP_MODE_ON);
}
#endif

#if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
/*************************************************************************
	module		:[ＮＤワープＯＮ／ＯＦＦの獲得]
	function	:[
	]
	return		:[
		０    :ＯＦＦ
		０以外:ＯＮ
	]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
UBYTE CHK_ND_WarpON(void)
{
	return(SYB_SettingStatus[SETTING_STATUS_30] & ND_WARP_ON);
}
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/24 */
void CMN_CheckKeidenSettings(UBYTE *Keisatsu)
{
	*Keisatsu = 0x00;

	*Keisatsu |= SYS_KEISATSU_KEIDEN;

	if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_COM_METHOD_KOBETSU) {
		*Keisatsu |= SYS_KEISATSU_KOBETSU;
	}
	else{
		*Keisatsu |= SYS_KEISATSU_ISSEI;
	}
	
	if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_KEIDEN_SCRAMLE_ON) {
		*Keisatsu |= SYS_KEISATSU_SCRAMBLE_ON;
	}
	else{
		*Keisatsu |= SYS_KEISATSU_SCRAMBLE_OFF;
	}
	
	if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SENYOU){
		*Keisatsu |= SYS_KEISATSU_SENYO;
	}
	else{
		*Keisatsu |= SYS_KEISATSU_KYOTSU;
	}

	return;
}
void CMN_CheckKanyuSettings(UBYTE *Keisatsu)
{
	*Keisatsu = 0x00;

	*Keisatsu |= SYS_KEISATSU_KANYU;
	*Keisatsu |= SYS_KEISATSU_KOBETSU;
	
	if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_KEIDEN_SCRAMLE_ON) {
		*Keisatsu |= SYS_KEISATSU_SCRAMBLE_OFF;
	}
	else{
		*Keisatsu |= SYS_KEISATSU_SCRAMBLE_ON;
	}

	if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_KANYU_SCRAMLE_ON) {
		*Keisatsu |= SYS_KEISATSU_SCRAMBLE_ON;
	}
	else{
		*Keisatsu |= SYS_KEISATSU_SCRAMBLE_OFF;
	}
	
	if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SENYOU){
		*Keisatsu |= SYS_KEISATSU_SENYO;
	}
	else{
		*Keisatsu |= SYS_KEISATSU_KYOTSU;
	}

	return;
}

void CMN_SetKeisatsuSettings(UBYTE Keisatsu)
{
	UBYTE	setting_temp;
	setting_temp = SYB_SettingStatus[SETTING_STATUS_31] &
										(~SETTING_LINE  |
										 ~SETTING_MODE |
										 ~SETTING_SCRAMBLE_KEIDEN |
										 ~SETTING_SENYOU );
	
	if (Keisatsu & SYS_KEISATSU_KANYU){
		setting_temp |= SETTING_LINE;
	}
	
	if (Keisatsu & SYS_KEISATSU_KOBETSU){
		setting_temp |= SETTING_MODE;
	}

	if (Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
		setting_temp |= SETTING_SCRAMBLE_KEIDEN;
	}

	if (Keisatsu & SYS_KEISATSU_SENYO){
		setting_temp |= SETTING_SENYOU;
	}

	SYB_SettingStatus[SETTING_STATUS_31] = setting_temp;
	
	return;
}

/**************************************************************************************************/
/**
	@brief		専用/共通の状態取得
	
	@li			
	@param		
	@return		TRUE:	専用
				FALSE:	共通
	@note		
	@date		2005/09/08 作成
	@author		石橋正和
*/
/**************************************************************************************************/
BOOL CHK_SenyoOn(void)
{
	if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SENYOU) {
		return(TRUE);
	}
	else {
		return(FALSE);
	}
}

#endif		/* End of (defined (KEISATSU)) */

