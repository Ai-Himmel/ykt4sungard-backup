/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_PTNR.C												 */
/*	モジュール	 :															 */
/*				 :															 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : 個別設定獲得モジュール									 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\memsw\define\mem_sw_b.h"
#include "\src\atlanta\define\sysdial.h"
#include "\src\atlanta\define\sysspeed.h"
#include "\src\atlanta\define\sysonet.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\ext_v\sys_data.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\fcm_data.h"

/*************************************************************************
	module		:[送信速度の獲得]
	function	:[
		1.
	]
	return		:[0: 2400bps
				  1: 4800bps
				  2: 7200bps
				  3: 9600bps
				  4:12000bps
				  5:14400bps
				  6:16800bps
				  7:19200bps
				  8:21600bps
				  9:24000bps
				 10:26400bps
				 11:28800bps
				 12:31200bps
				 13:33600bps]
	]
	common		:[]
	condition	:[]
	comment		:[InitializeBaudrate()で呼ばれる]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE FCM_PtnrChkTxBPS(void)
{
	return((UBYTE)(PartnerAbility0 & MEM_TX_BPS));
}

/*************************************************************************
	module		:[V29EPトーン付きの獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[ModemConfig()で呼ばれる]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE FCM_PtnrChkV29EPtoneAvailable(void)
{
	return((UBYTE)(PartnerAbility0 & V29_EPTONE_AVAILABLE));
}

/*************************************************************************
	module		:[DIS1回無視無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[FaxTxPhaseB1()で呼ばれる]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE FCM_PtnrChkOverride1stDIS(void)
{
	return((UBYTE)(PartnerAbility0 & OVERRIDE_1ST_DIS));
}

/*************************************************************************
	module		:[フォールバックパターンの獲得]
	function	:[
		1.
	]
	return		:[0	   :2-2-2-2-2回
				  0以外:1-1-1-1-4回
	]
	common		:[パターンは14.4K-12.0K-9.6K-4.8K-2.4Kの順]
	condition	:[]
	comment		:[FaxTxTraining()で呼ばれる]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE FCM_PtnrChkFallbackPattern(void)
{
	return((UBYTE)(PartnerAbility0 & FALLBACK_PATTERN));
}


/*************************************************************************
	module		:[Busy Tone検出無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[ATDから呼ばれる]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE FCM_PtnrChkBusyToneDetect(void)
{
	return((UBYTE)(PartnerAbility0 & MEM_BUSYTONE_DETECT));
}

/*************************************************************************
	module		:[アッテネータ値の獲得]
	function	:[
		1.
	]
	return		:[0～15:0～15dB]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[]
	keyword		:[]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
***************************************************************************/
UBYTE FCM_PtnrChk_T23Attenation(void)
{
	return((UBYTE)(PartnerAbility1 & ATTENATION));
}

/***************************************************************************
	module		:[DCS送出終了からTCF送出開始までの時間の獲得]
	function	:[]
	return		:[
			   0: 75m秒
			  30:300m秒
			  45:450m秒
			  60:600m秒
			 ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[]
	keyword		:[]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
*****************************************************************************/
UBYTE FCM_PtnrChk_T23DCS_AfterTCF(void)
{
	switch (PartnerAbility1 & DCS_AFTER_TCF) {
	case 0x00:
		return(0);
	case 0x10:
		return(30);
	case 0x20:
		return(45);
	case 0x30:
		return(60);
	}
}

/*****************************************************************************
	module		:[CFR受信終了からPIX送出開始までの時間の獲得]
	function	:[]
	return		:[
			   10: 250m秒
			   50: 500m秒
			   75: 750m秒
			  100:1000m秒]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[]
	keyword		:[]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
*****************************************************************************/
UWORD  FCM_PtnrCHK_T41CFR_AfterPIX(void)
{
	switch (PartnerAbility1 & CFR_AFTER_PIX) {
	case 0x00:
		return(25);
	case 0x40:
		return(50);
	case 0x80:
		return(75);
	case 0xC0:
		return(100);
	}
}

/*****************************************************************************
	module		:[DIS受信終了からDCS送出開始までの時間の獲得]
	function	:[]
	return		:[
				0:	 0m秒
			   50: 500m秒
			  100:1000m秒
			  150:1500m秒]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[]
	keyword		:[]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
*****************************************************************************/
UBYTE FCM_PtnrChk_DIS_AfterDCS(void)
{
	switch (PartnerAbility2 & DIS_AFTER_DCS) {
	case 0x00:
		return(0);
	case 0x01:
		return(50);
	case 0x02:
		return(100);
	case 0x03:
		return(150);
	}
}

/*************************************************************************
	module		:[ECMエラー再送間隔の獲得]
	function	:[
		1.
	]
	return		:[200:200m秒
				  400:400m秒
	]
	common		:[]
	condition	:[]
	comment		:[TxPostMessageHandshake()で呼ばれる]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
*************************************************************************/
UWORD  FCM_PtnrChkECM_TxInterval(void)
{
	if (PartnerAbility2 & ECM_TX_INTERVAL) {
		return(400);
	} else {
		return(200);
	}
}

/*************************************************************************
	module		:[ECM応答受信時間の獲得]
	function	:[
		1.
	]
	return		:[TIME_OVER_3SEC:3000ミリ秒
				  TIME_OVER_48SEC:4800ミリ秒
	]
	common		:[]
	condition	:[]
	comment		:[TxPostMessageHandshake()で呼ばれる]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
*************************************************************************/
UWORD  FCM_PtnrChkECM_ResponseTime(void)
{
	if (PartnerAbility2 & ECM_RESPONSE_TIME) {
		return(TIME_OVER_48SEC);
	} else {
		return(TIME_OVER_3SEC);
	}
}


/*************************************************************************
	module		:[TTI送信無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[lst_ctx.cでメモリスイッチを見ている]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
*************************************************************************/
UBYTE FCM_PtnrChkTTI_TxAvailable(void)
{
	return((UBYTE)(PartnerAbility2 & TTI_TX_AVAILABLE));
}


/*************************************************************************
	module		:[カレンダタイプ切替え無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[lst_data.cでメモリスイッチを見ている]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
*************************************************************************/
UBYTE FCM_PtnrChkCalendarTypeChange(void)
{
	return((UBYTE)(PartnerAbility2 & TTI_CALENDAR_TYPE_CHANGE));
}

/*************************************************************************
	module		:[相手側機にプリンタ受信]
	function	:[
		1.
	]
	return		:[０	:させない
				  ０以外:させる
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
**************************************************************************/
UBYTE FCM_PtnrChk_TxToPrinterRxEnable(void)
{
	return((UBYTE)(PartnerAbility2 & PARTNER_PRINTER_RX_ENABLE));
}

/*************************************************************************
	module		:[全てＶ１７／３３ＤＣＳ宣言]
	function	:[
		1.
	]
	return		:[０	:しない
				  ０以外:する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[]
	keyword		:[]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
**************************************************************************/
UBYTE FCM_PtnrChk_DCS_V33AllHold(void)
{
	return((UBYTE)(PartnerAbility2 & DCS_V33_ALL_HOLD));
}

/*************************************************************************
	module		:[14.4K(V17)短縮ハンドシェイク無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[fcm_getd.c fcm_last.c で呼ばれる ]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
*************************************************************************/
UBYTE FCM_PtnrChkSpeedHandshake144(void)
{
	return((UBYTE)(PartnerAbility3 & SPEED_HANDSHAKE_144));
}

/*************************************************************************
	module		:[9.6K(V29)短縮ハンドシェイク無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[fcm_getd.c fcm_last.c で呼ばれる]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/04/08]
	author		:[T.Yamaguchi]
*************************************************************************/
UBYTE FCM_PtnrChkSpeedHandshake96(void)
{
	return((UBYTE)(PartnerAbility3 & SPEED_HANDSHAKE_96));
}

/*************************************************************************
	module		:[Ｖ８短縮ハンドシェイク無効/有効の獲得]
	function	:[]
	return		:[0:無効
			  0以外:有効]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[]
	keyword		:[]
	date		:[1996/04/08]
	author		:[T.Yamaguchi]
*************************************************************************/
UBYTE FCM_PtnrChkSpeedHandshakeV8(void)
{
	return((UBYTE)(PartnerAbility3 & SPEED_HANDSHAKE_V8));
}

/*************************************************************************
	module		:[RTN,PINを受信しても自動ページ再送無効/有効の獲得]
	function	:[]
	return		:[0:再送する
			  0以外:再送しない]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[]
	keyword		:[]
	date		:[1996/11/09]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE FCM_PtnrChkRTN_NoReTransmit(void)
{
	return((UBYTE)(PartnerAbility3 & RTN_AUTO_RETRANSMIT_DISABLE));
}

/*************************************************************************
	module		:[ＥＣＭ送信をＯＮ/ＯＦＦの獲得]
	function	:[]
	return		:[0:ＥＣＭ送信がＯＮ
			  0以外:ＥＣＭ送信がＯＦＦ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[]
	keyword		:[]
	date		:[1998/10/06]
	author		:[吉川弘康]
*************************************************************************/
UBYTE FCM_ECM_TxOFF(void)
{
	return((UBYTE)(PartnerAbility3 & ECM_TX_OFF));
}

/*************************************************************************
	module		:[端末識別信号送出禁止をＯＮ/ＯＦＦの獲得]
	function	:[]
	return		:[0：送出する(禁止しない)
				0以外:送出しない(禁止する）]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[]
	keyword		:[]
	date		:[1999/04/20]
	author		:[木元修]
*************************************************************************/
UBYTE FCM_TerminalInformationNotTx(void)
{
	return((UBYTE)(PartnerAbility3 & NO_TERMINAL_INFORMATION_TX));
}

/*************************************************************************
	module		:[スーパーＧ３送信有効／無効の獲得]
	function	:[
		1.送信時、スーパーＧ３を有効にするか無効にするかのＳＷです。
	]
	return		:[
			0		:有効
			0以外	:無効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[1999/04/20]
	author		:[木元修]
*************************************************************************/
UBYTE FCM_V34TransmitDisable(void)
{
	return((UBYTE)(PartnerAbility3 & SUPER_G3_TX_MASK));
}

/*************************************************************************
	module		:[ＡＮＳａｍ検出有効／無効の獲得]
	function	:[
		1.ダイヤル後の信号検出でＡＮＳａｍを検出するかしないかのＳＷです。
	]
	return		:[
			0		:検出する
			0以外	:検出しない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[1999/04/20]
	author		:[木元修]
*************************************************************************/
UBYTE FCM_OverrideANSam(void)
{
	return((UBYTE)(PartnerAbility3 & INHIBIT_DETECT_ANSAM));
}

