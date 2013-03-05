/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_CTRY.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_ctry.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\param.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\cmn_tbl.h"
#include "\src\atlanta\ext_v\atd_tbl.h"
#include "\src\atlanta\ext_v\ncu_tbl.h"
#include "\src\atlanta\ext_v\rom_tbl.h"

#if (PRO_RING_MASTER == ENABLE)
#include "\src\atlanta\define\status.h"
#endif

/*************************************************************************
	module		:[中継指示送信機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[ＦＣＭ、ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RelayTx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_0] & RELAY_TX));
}

/*************************************************************************
	module		:[中継配信機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[ＦＣＭでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RelayedTx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_0] & RELAYED_TX));
}

/*************************************************************************
	module		:[検索ポーリング受信機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_DB_PolingRx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_0] & DB_POLING_RX));
}

/*************************************************************************
	module		:[検索ポーリング送信機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[ＦＣＭ、ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_DB_PolingTx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_0] & DB_POLING_TX));
}

/*************************************************************************
	module		:[親展送信機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[ＦＣＭ、ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_SecureTx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_0] & SECURE_TX));
}

/*************************************************************************
	module		:[親展受信機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[ＦＣＭでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_SecureRx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_0] & SECURE_RX));
}

/*************************************************************************
	module		:[親展受信原稿保持時間機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_SecureDocHoldTime(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_0] & SECURE_DOC_HOLD_TIME));
}

/*************************************************************************
	module		:[電話回線設定機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_PhoneType(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_0] & PHONE_TYPE));
}

/*************************************************************************
	module		:[ポーズ機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_Pause(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_1] & PAUSE));
}

/*************************************************************************
	module		:[ベル回数設定機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_BellCount(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_1] & BELL_COUNT));
}

/*************************************************************************
	module		:[子電話接続設定機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_Connecting2Tel(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_1] & CONNECTING_2TEL));
}

/*************************************************************************
	module		:[リモート診断機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RemoteDiag(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_1] & REMOTE_DIAG));
}

/*************************************************************************
	module		:[リダイヤル回数設定機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RedialNumber(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_1] & REDIAL_NUMBER));
}

/*************************************************************************
	module		:[リダイヤル間隔設定機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RedialInterval(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_1] & REDIALINTERVAL));
}

/*************************************************************************
	module		:[保留メロディ設定機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_HoldMelody(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_1] & HOLD_MELODY));
}

/*************************************************************************
	module		:[閉域通信設定機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_ClosedNetwork(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_1] & CLOSED_NETWORK));
}

/*************************************************************************
	module		:[Tel/Fax優先設定機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_TelFaxPrimary(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_2] & TELFAX_PRIMARY));
}

/*************************************************************************
	module		:[パスワード送信機能有効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_SecurityTx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_2] & SECURITY_TX));
}

/*************************************************************************
	module		:[ダイレクトメール防止機能有効/機能の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_BlockJunkFax(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_2] & BLOCK_JUNK_FAX));
}

/*************************************************************************
	module		:[済スタンプ機能有効/機能の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_Stamp(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_2] & STAMP));
}

/*************************************************************************
	module		:[メッセージ送信機能有効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_MessageTx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_2] & MESSAGE_TX));
}

/*************************************************************************
	module		:[RS232C設定機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RS232C(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_2] & RS232C));
}

/*************************************************************************
	module		:[ダイヤルイン設定機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_Dialin(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_2] & DIALIN));
}

/*************************************************************************
	module		:[部門管理機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_Department(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_2] & DEPARTMENT));
}

/*************************************************************************
	module		:[料金管理機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_Cost(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_3] & COST));
}

/*************************************************************************
	module		:[一括送信機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_BatchTx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_3] & BATCH_TX));
}

/*************************************************************************
	module		:[受領証機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RCR(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_3] & RCR));
}

/*************************************************************************
	module		:[代行受信無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_NonePaperRx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_3] & NONE_PAPER_RX));
}

/*************************************************************************
	module		:[転送受信機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RemoteRx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_3] & REMOTE_RX));
}

/*************************************************************************
	module		:[Tel/Fax待機機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_TelFaxReady(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_3] & TELFAX_READY));
}

/*************************************************************************
	module		:[Ans/Fax待機機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_AnsFaxReady(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_3] & ANSFAX_READY));
}

/*************************************************************************
	module		:[保留キー機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_HoldKey(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_3] & HOLD_KEY_ENABLE));
}

/*************************************************************************
	module		:[リダイヤルキー機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RedialKey(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_4] & REDIAL_KEY_ENABLE));
}

/*************************************************************************
	module		:[フックキー機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_HookKey(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_4] & HOOK_KEY_ENABLE));
}

/*************************************************************************
	module		:[オフフック状態での電話機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_OffhookTel(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_4] & OFFHOOK_TEL));
}

/*************************************************************************
	module		:[ポーズキー機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_PauseKey(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_4] & PAUSE_KEY_ENABLE));
}

/*************************************************************************
	module		:[シグナルチェンジ機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_SignalChange(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_4] & TONE_KEY_ENABLE));
}

/*************************************************************************
	module		:[第1発信音検出機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_1DT_Detect(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_4] & FIRST_DT_DETECT));
}

/*************************************************************************
	module		:[第2発信音検出機能無効/有効の確認]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_2DT_Detect(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_4] & SECOND_DT_DETECT));
}

/*************************************************************************
	module		:[キャッチホン対応機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_Catchphone(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_4] & CATCH_PHONE));
}

/*************************************************************************
	module		:[リモート取出し機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RemoteTakeOut(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_5] & REMOTE_TAKEOUT));
}

/*************************************************************************
	module		:[ブランチ転送機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_BranchRx(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_5] & BRANCH_RX));
}

/*************************************************************************
	module		:[ポケベル呼出機能無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_PocketBell(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_5] & POCKET_BELL));
}


/*************************************************************************
	module		:[ＤＩＳ受信まで回線モニタＯＮ]
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
	date		:[1994/06/27]
	author		:[村田]
*************************************************************************/
UBYTE	CTRY_MonitorOnToDIS(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_5] & MONITOR_ON_TO_DIS));
}


/*************************************************************************
	module		:[最大ポーズ動作回数の獲得]
	function	:[
		1.
	]
	return		:[1～255:1～255回]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_PauseCount(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_6]);
}

/*************************************************************************
	module		:[ポーズ時間の最小値の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255秒]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_PauseTimeMin(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_7]);
}

/*************************************************************************
	module		:[ポーズ時間の最大値の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255秒]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_PauseTimeMax(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_8]);
}

/*************************************************************************
	module		:[ベル回数の最小値の獲得]
	function	:[
		1.
	]
	return		:[1～255:1～255回]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RingCountMin(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_9]);
}

/*************************************************************************
	module		:[ベル時間の最大値の獲得]
	function	:[
		1.
	]
	return		:[1～255:1～255回]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RingCountMax(void)
{
#if (PRO_CSDR_ITEM == ENABLE)	/* Add By O.Kimoto 1998/12/15 */
	if (CHK_UNI_ExtendedCallCount()) {
		return((UBYTE)15);
	}
	else {
		return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_10]);
	}
#else
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_10]);
#endif
}

/*************************************************************************
	module		:[リダイヤル回数の最小値の獲得]
	function	:[
		1.
	]
	return		:[1～254:1～254回]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RedialNumberMin(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_11]);
}

/*************************************************************************
	module		:[リダイヤル回数の最大値の獲得]
	function	:[
		1.
	]
	return		:[1～254:1～254回]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RedialNumberMax(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_12]);
}

/*************************************************************************
	module		:[リダイヤル間隔の最小値の獲得]
	function	:[
		1.
	]
	return		:[1～255:1～255分]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RedialIntervalMin(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_13]);
}

/*************************************************************************
	module		:[リダイヤル間隔の最大値の獲得]
	function	:[
		1.
	]
	return		:[1～255:1～255回]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_RedialIntervalMax(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_14]);
}

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
/*************************************************************************
	module		:[マーキュリーポーズ時間の最小値の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255秒]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
	1996/06/24 H,Yagi
*************************************************************************/
UBYTE	CTRY_MercuryPauseTimeMin(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_22]);
}

/*************************************************************************
	module		:[マーキュリーポーズ時間の最大値の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255秒]
	common		:[]
	condition	:[]
	comment		:[ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
	1996/06/24 H,Yagi
*************************************************************************/
UBYTE	CTRY_MercuryPauseTimeMax(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_23]);
}
#endif

/*************************************************************************
	module		:[トーンアッテネータの初期値の獲得]
	function	:[
		1.
	]
	return		:[0～15:0～15dB]
	common		:[]
	condition	:[]
	comment		:[未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_InitToneAttenation(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15]);
}

/*************************************************************************
	module		:[親展原稿保持時間の初期値の獲得]
	function	:[
		1.
	]
	return		:[1～255:1～255日]
	common		:[]
	condition	:[]
	comment		:[ＣＭＮでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_InitSecureMailRxTime(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_16]);
}

/*************************************************************************
	module		:[回線種別の初期値の獲得]
	function	:[
		1.
	]
	return		:[0:DP
				  1:PB
	]
	common		:[]
	condition	:[]
	comment		:[ＣＭＮでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_InitPhoneType(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_17]
											& (INIT_PHONE_TYPE_10PPS |
											   INIT_PHONE_TYPE_20PPS |
											   INIT_PHONE_TYPE_TONE)));
}

/*************************************************************************
	module		:[ワーディング番号の初期値の獲得]
	function	:[
		1.
	]
	return		:[1:第1ワーディング
				  2:第2ワーディング
				  3:第3ワーディング
	]
	common		:[]
	condition	:[]
	comment		:[ＣＭＮでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_InitWordingNumber(void)
{
	return((UBYTE)((CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_17]
											& (INIT_WORDING_NUMBER_0 |
											   INIT_WORDING_NUMBER_1 |
											   INIT_WORDING_NUMBER_2)) >> 2));
}

/*************************************************************************
	module		:[マルチワーディング数]
	function	:[
		1.
	]
	return		:[2:2ヶ国語
				  3:3ヶ国語
	]
	common		:[]
	condition	:[]
	comment		:[ＣＭＮ、ＯＰＲでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_WordingNumberMax(void)
{
	return((UBYTE)((CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_17]
											& (WORDING_NUMBER_MAX_1 |
											   WORDING_NUMBER_MAX_2 |
											   WORDING_NUMBER_MAX_3)) >> 4));
}

/*************************************************************************
	module		:[日本仕様／ＵＳＡ仕様]
	function	:[
		1.
	]
	return		:[0:日本仕様
				  それ以外:ＵＳＡ仕様
	]
	common		:[]
	condition	:[]
	comment		:[未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/14]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CTRY_CountryType(void)
{
	return((UBYTE)(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_17] & USA_MODEL));
}

/*************************************************************************
	module		:[ポーズ時間の初期値の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255秒]
	common		:[]
	condition	:[]
	comment		:[ＣＭＮでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_InitPauseTime(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_18]);
}

/*************************************************************************
	module		:[ベル回数の初期値の獲得]
	function	:[
		1.
	]
	return		:[1～255:1～255回]
	common		:[]
	condition	:[]
	comment		:[ＣＭＮでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_InitRingCount(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_19]);
}

/*************************************************************************
	module		:[リダイヤル回数の初期値の獲得]
	function	:[
		1.
	]
	return		:[1～254:1～254回]
	common		:[]
	condition	:[]
	comment		:[ＣＭＮでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_InitRedialNumber(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_20]);
}

/*************************************************************************
	module		:[リダイヤル間隔の初期値の獲得]
	function	:[
		1.
	]
	return		:[1～255:1～255分]
	common		:[]
	condition	:[]
	comment		:[ＣＭＮでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CTRY_InitRedialInterval(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_21]);
}

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
/*************************************************************************
	module		:[マーキュリーポーズ時間の初期値の獲得]
	function	:[
		1.
	]
	return		:[0～255:0～255秒]
	common		:[]
	condition	:[]
	comment		:[ＣＭＮでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/17]
	author		:[吉川弘康]
	1996/06/24  H,Yagi
*************************************************************************/
UBYTE	CTRY_InitMercuryPauseTime(void)
{
	return(CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_24]);
}
#endif

/*************************************************************************
	module		:[ダイヤルに関する制御テーブルの獲得]
	function	:[
		1.
	]
	return		:[テーブルのアドレス]
	common		:[]
	condition	:[]
	comment		:[ＡＴＤ、ＣＭＮでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/02/18]
	author		:[吉川弘康]
*************************************************************************/
struct DialParameters_t * CTRY_DialTable(void)
{
	return(&DialTable[SYB_MachineParameter[COUNTRY_CODE]]);
}

/*************************************************************************
	module		:[第1発信音のパラメータテーブルの獲得]
	function	:[
		1.
	]
	return		:[テーブルのアドレス]
	common		:[]
	condition	:[]
	comment		:[ＡＴＤでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/02/18]
	author		:[吉川弘康]
*************************************************************************/
struct ToneParameters_t * CTRY_DialTone(void)
{
	return(&DialTone[SYB_MachineParameter[COUNTRY_CODE]]);
}

/*************************************************************************
	module		:[第2発信音のパラメータテーブルの獲得]
	function	:[
		1.
	]
	return		:[テーブルのアドレス]
	common		:[]
	condition	:[]
	comment		:[ＡＴＤでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/02/18]
	author		:[吉川弘康]
*************************************************************************/
struct ToneParameters_t * CTRY_Dial2ndTone(void)
{
	return(&Dial2ndTone[SYB_MachineParameter[COUNTRY_CODE]]);
}

/*************************************************************************
	module		:[話中音のパラメータテーブルの獲得]
	function	:[
		1.
	]
	return		:[テーブルのアドレス]
	common		:[]
	condition	:[]
	comment		:[ＡＴＤでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/02/18]
	author		:[吉川弘康]
*************************************************************************/
struct ToneParameters_t * CTRY_BusyTone(void)
{
	return(&BusyTone[SYB_MachineParameter[COUNTRY_CODE]]);
}

/*************************************************************************
	module		:[交換機話中音のパラメータテーブルの獲得]
	function	:[
		1.
	]
	return		:[テーブルのアドレス]
	common		:[]
	condition	:[]
	comment		:[ＡＴＤでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/02/18]
	author		:[吉川弘康]
*************************************************************************/
struct ToneParameters_t * CTRY_CongestionTone(void)

{
	return(&CongestionTone[SYB_MachineParameter[COUNTRY_CODE]]);
}

/*************************************************************************
	module		:[呼出ベルに関する制御テーブルの獲得]
	function	:[
		1.
	]
	return		:[テーブルのアドレス]
	common		:[]
	condition	:[]
	comment		:[ＮＣＵでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/05/21]
	author		:[坂本直史]
*************************************************************************/
struct RingData_t * CTRY_RingTable(void)
{
	return(&RingTime[SYB_MachineParameter[COUNTRY_CODE]]);
}

/*************************************************************************
	module		:[リング・マスタに関する制御テーブルの獲得]
	function	:[
		1.
	]
	return		:[テーブルのアドレス]
	common		:[]
	condition	:[]
	comment		:[ＮＣＵでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/05/21]
	author		:[坂本直史]
*************************************************************************/
struct RingMaster_t * CTRY_RingMasterTable(void)
{
	UBYTE	pattern_number;

	pattern_number =  CHK_RingMasterPattern();

	if( pattern_number ){
#if (PRO_RING_MASTER == ENABLE)		/* For MBS	Add by TH92115	1995/05/24 */
		if (((pattern_number == RING_MASTER_PATTERN_7) && SYB_RingG_SetNumber)
		 || ((pattern_number == RING_MASTER_PATTERN_8) && SYB_RingH_SetNumber)) {
/*			return ((struct RingMaster_t *)&SYB_TeachingPattern[pattern_number - 7]);	1996/07/09 By N.Sakamoto */
			return ((struct RingMaster_t *)&SYB_TeachingPattern[pattern_number - 6]);
		}
#endif
/*		return(&RingPattern[ pattern_number - 1 ]);		1996/07/09 By N.Sakamoto */
		return(&RingPattern[ pattern_number ]);
	}
	else{
		return(&RingPattern[ 0 ]);
	}
}

/*************************************************************************
	module		:[疑似ＲＢＴに関する制御テーブルの獲得]
	function	:[
		1.
	]
	return		:[テーブルのアドレス]
	common		:[]
	condition	:[]
	comment		:[ＮＣＵでコール]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/05/21]
	author		:[坂本直史]
*************************************************************************/
struct RingBackToneData_t * CTRY_RBTTable(void)
{
/*	return(&RBT[SYB_MachineParameter[COUNTRY_CODE]]);	*/
	return(&RBT);
}


/*************************************************************************
	module		:[記録設定の有無の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[未使用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/11/07]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE	CTRY_RecordPaper(void)
{
#if (PRO_CPU==SH7043) /* By S.Kawasaki 1996/03/07 */
 #if (PRO_PRINT_TYPE == THERMAL_TRANS)			/** 椛用ＲＯＭスイッチ By O.K Oct,20,1994 **/
	return(1);
 #else
 	return(0);
 #endif
#else
	return(0);
#endif
}
