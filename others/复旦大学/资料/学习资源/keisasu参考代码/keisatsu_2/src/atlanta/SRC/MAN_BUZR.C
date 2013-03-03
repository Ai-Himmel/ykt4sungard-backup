/************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: MAN_BUZR.C
*	Author		: 渡辺一章
*	Date		: 1996/10/30
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ブザー制御
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\mntsw_f.h"			/* MNT_SW_F8, MNT_SW_F9 */
#include	"\src\atlanta\define\unisw_f.h"			/* UNI_SW_F5, UNI_SW_F6 */
#include	"\src\atlanta\sh7043\define\def_tib.h"

#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\mon_pro.h"			/* cre_tsk(), del_tsk() */
#include	"\src\atlanta\define\stng_pro.h"		/* CHK_SilentOperation() */
#include	"\src\atlanta\define\uni_pro.h"			/* CHK_UNI_SilentOperation() */

#include	"\src\atlanta\ext_v\bkupram.h"			/* SYB_MachineUniqSwitch */
#include	"\src\atlanta\ext_v\man_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"			/* SYS_MachineStatus, SYS_SecondCassetteFlag */
#if (PRO_CLASS1 == ENABLE)
#include	"\src\atlanta\ext_v\cl1_data.h"
#endif

#if (PRO_PANEL == ANK)
#include	"\src\atlanta\opr\ank\define\opr_pro.h"	/* UpdateLCD() */
#endif
#if (PRO_PANEL == KANJI)
#include  "\src\atlanta\opr\kanji\define\opr_pro.h" /* UpdateLCD() */
#endif

#if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/08/23 */
#include  "\src\atlanta\define\cmn_def.h"
#endif

/* Prototype
void	UpdateDisplay(void);
void	UpdateBuzzer(void);
void	EndBuzzer(void);
void	StopEndBuzzer(void);
void	AlarmBuzzer(void);
void	StopAlarmBuzzer(void);
void	HoldBuzzer(void);
void	HungUpBuzzer(void);
void	StopHungUpBuzzer(void);
void	HoldEndBuzzer(void);
#if defined(GBR)
void	AudibleAlarmBuzzer(void);
void	StopAudibleAlarmBuzzer(void);
#endif
*/

/*************************************************************************
	module		:[動作状態表示]
	function	:[
		1.メインタスクが１周する毎に実行される
		2.ブザー鳴動／停止
		3.ＬＥＤ点灯／消灯
		4.機器状態表示
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/05/10]
	author		:[江口]
*************************************************************************/
void UpdateDisplay(void)
{
	/************************/
	/** ブザー鳴動			*/
	/************************/
#if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/08/23 */
	if (SYS_CheckerMode != CHECKER_MAIN_TEST) {
		UpdateBuzzer();
	}
#else
	UpdateBuzzer();
#endif

	/************************/
	/** LED制御				*/
	/************************/
	UpdateLED();

	/************************/
	/** 動作状態表示	    */
	/************************/
	UpdateLCD();

#if (PRO_PRINT_TYPE == LASER)	/**FEMの為*/
	/*
	 * プリンターステータスを機種固有スイッチＦ５，６にコピーする
	 * プリンターエラー発生時の詳細データの獲得のため
	 */
	/* UNIQ_SW_F5に下位バイトをセット*/
	/* UNIQ_SW_F6に上位バイトをセット*/
	/* 上位／下位を反転 */
	SYB_MachineUniqSwitch[UNIQ_SW_F5] = (UBYTE)(SYS_MachineStatus[SYS_PRINTER_STATUS3] & 0x00FF);
	SYB_MachineUniqSwitch[UNIQ_SW_F6] = (UBYTE)((SYS_MachineStatus[SYS_PRINTER_STATUS3] & 0xFF00) >> 8);
#else
#if (0)	/* POPLARでは使用しない */
	/*
	 * プリンターステータスをメンテスイッチＦ８，９にコピーする
	 * プリンターエラー発生時の詳細データの獲得のため
	 */
	/* MNT_SW_F8に下位バイトをセット*/
	/* MNT_SW_F9に上位バイトをセット*/
	/* 上位／下位を反転 */
	/* とりあえずサービスコールの３番目だけセットする（必要によって１，２番目もセットする） */
//	SYB_MaintenanceSwitch[MNT_SW_F8] = (UBYTE)((SYS_MachineStatus[SYS_PRINTER_STATUS3] & 0xFF00) >> 8);
//	SYB_MaintenanceSwitch[MNT_SW_F9] = (UBYTE)(SYS_MachineStatus[SYS_PRINTER_STATUS3] & 0x00FF);
#endif
#endif
}

/*************************************************************************
	module		:[ブザー鳴動]
	function	:[
		1.機器状態にあわせたブザーを鳴動する。
		2.プリンターカバーオープン、カセットオープンはアラームは鳴動しない。（桐にあわす)
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[アック・ナック以外のブザーは総てここで鳴動するようにしたい]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/12/05]
	author		:[江口]
*************************************************************************/
void UpdateBuzzer(void)
{
	UWORD	prn_status1;
	UWORD	prn_status2;
	UWORD	prn_status3;
	UWORD	scn_status;
	UWORD	cover_status;
	UWORD	error_status;
	UWORD	warning_status;	/* 1996/06/20 Eguchi */
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/12 */
	UWORD	cipher_status;
#endif
	UBYTE	printer_alarm_enable;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
	UBYTE	end_buzzer;
#endif

#if defined(STOCKHM2) /* 本体鳴動のテスト :by SMuratec C.P 2004/09/24 呼び出しブザー */
	if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRE_LINE_BUSY)) {
		StopCallingBuzzer();
	}
#endif

	/*------------------------*/
	/** エンドブザー鳴動	  */
	/*------------------------*/
#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
#if (PRO_CLASS1 == DISABLE) /*1996/09/13 Eguchi */
	if (tskno_faxcom_complete != 0xFFFF || timer_print_complete != 0xFF) /* 通信・プリント終了 */
		EndBuzzer();
	else
		StopEndBuzzer();
#endif
#if (PRO_CLASS1 == ENABLE) /*1996/09/13 Eguchi */
	if (tskno_faxcom_complete != 0xFFFF || timer_print_complete != 0xFF || tskno_pc_fax_complete != 0xFFFF)
		EndBuzzer();
	else
		StopEndBuzzer();
#endif
#else
 #if (PRO_DIALUP_INTERNET_FAX == DISABLE)	/* by Y.Tanimoto 1998/03/12 */
  #if (PRO_CLASS1 == DISABLE) /*1996/09/13 Eguchi */
	if (tskno_faxcom_complete != 0xFFFF || tskno_print_complete != 0xFFFF) /* 通信・プリント終了 */
		EndBuzzer();
	else
		StopEndBuzzer();
  #endif
  #if (PRO_CLASS1 == ENABLE) /*1996/09/13 Eguchi */
   #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/18 K.Kawata */
	if (tskno_faxcom_complete != 0xFFFF || tskno_print_complete != 0xFFFF || (tskno_pc_fax_complete != 0xFFFF) && (CL1_ExtLocalPrtRejectCnt == 0))
		EndBuzzer();
	else
		StopEndBuzzer();
   #else
	if (tskno_faxcom_complete != 0xFFFF || tskno_print_complete != 0xFFFF || tskno_pc_fax_complete != 0xFFFF)
		EndBuzzer();
	else
		StopEndBuzzer();
   #endif
  #endif
 #endif
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
  #if (PRO_CLASS1 == ENABLE)
	end_buzzer = 0;
	if (tskno_faxcom_complete != 0xFFFF || tskno_print_complete != 0xFFFF || tskno_pc_fax_complete != 0xFFFF)
		end_buzzer = 1;
	if ( (tskno_inf_complete != 0xFFFF) || (tskno_inf_nomail != 0xFFFF) )
		end_buzzer = 1;
  #endif
  #if (PRO_CLASS1 == DISABLE) /*1996/09/13 Eguchi */
	if (tskno_faxcom_complete != 0xFFFF || tskno_print_complete != 0xFFFF)
		end_buzzer = 1;
	if ( (tskno_inf_complete != 0xFFFF) || (tskno_inf_nomail != 0xFFFF) )
		end_buzzer = 1;
  #endif
	if (end_buzzer == 1)
		EndBuzzer();
	else
		StopEndBuzzer();
 #endif

#endif
	/*----------------------------------------------------------*/
	/* アラームブザー 			 								*/
	/* マシンステータスに変化があり､かつ０から１への変化の場合 	*/
	/* (セットされた場合）アラームを鳴動						*/
	/*----------------------------------------------------------*/
	/* アラームを鳴動するロジックに関しては桐にあわせます		*/
	/* 1:カバーオープン時はアラーム鳴動しない 					*/
	/* 2:プリンターカバーオープン時またはカセットオープン時に	*/
	/*   プリンターエラーが生じてもアラーム鳴動しない			*/
	/* 3:スキャナーカバーオープン時に、プリンターエラーが生じた */
	/*   場合はアラーム鳴動する.								*/
	/*----------------------------------------------------------*/

	prn_status1    = SYS_MachineStatus[SYS_PRINTER_STATUS1] ^ BackUpStatusPrinter1;
	prn_status2    = SYS_MachineStatus[SYS_PRINTER_STATUS2] ^ BackUpStatusPrinter2;
	prn_status3    = SYS_MachineStatus[SYS_PRINTER_STATUS3] ^ BackUpStatusPrinter3;
	scn_status     = SYS_MachineStatus[SYS_SCANNER_STATUS]  ^ BackUpStatusScanner;
	cover_status   = SYS_MachineStatus[SYS_COVER_STATUS]    ^ BackUpStatusCover;
	error_status   = SYS_MachineStatus[SYS_ERROR_STATUS]    ^ BackUpStatusError;
	warning_status = SYS_MachineStatus[SYS_WARNING_STATUS]  ^ BackUpStatusWarning;
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/12 */
	cipher_status  = SYS_MachineStatus[SYS_CIPHER_STATUS]   ^ BackUpStatusCipher;
#endif

	printer_alarm_enable = TRUE;
 /* カバーを開く時、鳴る。Modify start by SMurtaec 夏 2004/6/15 */
 #if 0	
	if (cover_status & SYS_MachineStatus[SYS_COVER_STATUS]) {	/* カバー・カセットオープン */
 		if (cover_status & SYS_COVER_ERROR_ALARM_STOP) {
			printer_alarm_enable = FALSE;
		}
	}
 #else
 	if (cover_status & SYS_MachineStatus[SYS_COVER_STATUS]) {
	 	if (((cover_status & SYS_MachineStatus[SYS_COVER_STATUS]) & SYS_COVER_SCANNER_OPEN)
	 	 	||((cover_status & SYS_MachineStatus[SYS_COVER_STATUS]) & SYS_COVER_PRINTER_OPEN)){	/* カバー・カセットオープン */
			StopAlarmBuzzer();
			AlarmBuzzer();
		}
		else{
			
			printer_alarm_enable = FALSE;
		}
	}
 #endif
 /* Modify end by SMurtaec 夏 2004/6/15 */		

	/*---------------------------------------------------------------------
	** トップカバーオープン状態の時は、記録紙エラー発生ではアラーム鳴動させません。
	** 1998/10/26 H.Yoshikawa
	*/
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL) 
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_ERROR_ALARM_STOP) {
		printer_alarm_enable = FALSE;
	}
#endif

	if (((prn_status1 & SYS_MachineStatus[SYS_PRINTER_STATUS1]) & SYS_PRINTER_ERROR_ALARM1)
	 || ((prn_status2 & SYS_MachineStatus[SYS_PRINTER_STATUS2]) & SYS_PRINTER_ERROR_ALARM2)
	 || ((prn_status3 & SYS_MachineStatus[SYS_PRINTER_STATUS3]) & SYS_PRINTER_ERROR_ALARM3)) {	/* プリンターエラー */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) && (SYS_SecondCassetteFlag == 0)) {
		/* 下段カセット記録紙なしだが実は下段カセットが装着されていない場合 */
		/* 下段カセット未装着の場合、紙なしのステータスがセットされないならこのパスはいらん TBD 1996/03/15 Eguchi */
			printer_alarm_enable = FALSE;
		}
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 紙つまり時、2回目鳴動の不具合の為、追加します。 by Smuratec 2003/11/24 */
		if ((SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM)
			&& (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_CUTTER_ERROR)
			&& !(prn_status2 & SYS_PRINTER_CUTTER_ERROR)) {
			/* 1回目カッターエラー、2回目ジャムエラー場合 */
			printer_alarm_enable = FALSE;
		}
#endif
		if (printer_alarm_enable) {
			StopAlarmBuzzer();
			AlarmBuzzer();
		}
	}
	/* スキャナーエラー */
	else if ((scn_status & SYS_MachineStatus[SYS_SCANNER_STATUS]) & SYS_SCANNER_ERROR_ALARM) {
		StopAlarmBuzzer();
		AlarmBuzzer();
	}
	else if (error_status & SYS_MachineStatus[SYS_ERROR_STATUS]) {
		/* ハングアップエラー */
/*		if ((error_status & SYS_ERROR_HUNG_UP) && (CHK_HANGUP_ALARM_AVAILABLE())) {ここにいれたら表示はする */
		if (error_status & SYS_ERROR_HUNG_UP) {
			StopHungUpBuzzer();	/* いったん止めてから鳴らす */
			HungUpBuzzer();
		}
		else {
			StopAlarmBuzzer();
			AlarmBuzzer();
		}
	}
	else if ((warning_status & SYS_MachineStatus[SYS_WARNING_STATUS]) & SYS_WARNING_DRUM_REPLACE) {
		StopAlarmBuzzer();
		AlarmBuzzer();
	}
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/12 */
	else if ((cipher_status & SYS_MachineStatus[SYS_CIPHER_STATUS]) & SYS_CIPHER_ERROR_ALARM) {
		StopAlarmBuzzer();
		AlarmBuzzer();
	}
#endif

	/*--------------------------------------*/
	/**   保留ブザー 1995/12/04 Eguchi		*//*旧機種はオペレーションタスクで鳴らしていた */
	/*--------------------------------------*/
	if (HoldBuzzerRequest) {	/* 保留警告ブザー鳴動要求 */
		HoldBuzzerRequest = 0;
		HoldBuzzer();
	}
	if (HoldEndBuzzerRequest) { /* いらないかも（Ｖ５３ではならしていない */
		HoldEndBuzzerRequest = 0;
		HoldEndBuzzer();
	}

#if defined(GBR)
	/*----------------------------------------*
	 * 受信完了アラーム
	 *----------------------------------------*/
	if (SYS_AudibleAlarmStatus & 0x01) { /** 受信アラーム鳴動要求あり */
		SYS_AudibleAlarmStatus |= 0x02;  /** 受信アラーム鳴動中セット */
		AudibleAlarmBuzzer();	/** 受信アラーム鳴動 */
	}
	else { /** 受信アラーム鳴動要求なし */
		SYS_AudibleAlarmStatus &= ~0x02; /** 受信アラーム鳴動中クリア */
		StopAudibleAlarmBuzzer();	/** 受信アラーム停止 */
	}
#endif

	/* ブザー停止 */
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/12 */
	if (!(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_ERROR_ALARM1)
	 && !(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_ERROR_ALARM2)
	 && !(SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_ERROR_ALARM3)
	 && !(SYS_MachineStatus[SYS_SCANNER_STATUS]  & SYS_SCANNER_ERROR_ALARM)
	 && !SYS_MachineStatus[SYS_COVER_STATUS]
	 && !SYS_MachineStatus[SYS_ERROR_STATUS]
	 && !(SYS_MachineStatus[SYS_WARNING_STATUS]  & SYS_WARNING_DRUM_REPLACE)
	 && !(SYS_MachineStatus[SYS_CIPHER_STATUS]   & SYS_CIPHER_ERROR_ALARM)) {	/* 機器エラーなし */
		StopAlarmBuzzer();
	}
#else
	if (!(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_ERROR_ALARM1)
	 && !(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_ERROR_ALARM2)
	 && !(SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_ERROR_ALARM3)
	 && !(SYS_MachineStatus[SYS_SCANNER_STATUS]  & SYS_SCANNER_ERROR_ALARM)
	 && !SYS_MachineStatus[SYS_COVER_STATUS]
	 && !SYS_MachineStatus[SYS_ERROR_STATUS]
	 && !(SYS_MachineStatus[SYS_WARNING_STATUS]  & SYS_WARNING_DRUM_REPLACE)) {	/* 機器エラーなし */
		StopAlarmBuzzer();
	}
#endif

	if (!(SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP)) {	/* ハングアップエラー解除 */
		StopHungUpBuzzer();
	}

	/* マシンステータスをセーブ */
	BackUpStatusPrinter1 = SYS_MachineStatus[SYS_PRINTER_STATUS1];
	BackUpStatusPrinter2 = SYS_MachineStatus[SYS_PRINTER_STATUS2];
	BackUpStatusPrinter3 = SYS_MachineStatus[SYS_PRINTER_STATUS3];
	BackUpStatusScanner  = SYS_MachineStatus[SYS_SCANNER_STATUS];
	BackUpStatusError    = SYS_MachineStatus[SYS_ERROR_STATUS];
	BackUpStatusCover    = SYS_MachineStatus[SYS_COVER_STATUS];
	BackUpStatusWarning  = SYS_MachineStatus[SYS_WARNING_STATUS];
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/12 */
	BackUpStatusCipher   = SYS_MachineStatus[SYS_CIPHER_STATUS];
#endif
}

/*************************************************************************
	module		:[エンドブザー鳴動]
	function	:[
		1.通信終了／プリント終了時にブザーを鳴らす
		2.通信終了／プリント終了状態の監視はこの関数をコールするまえに行うこと
		　,(UpdateDisplay中でフラグを監視）
		3.ブザー鳴動は１秒ＯＮ１秒ＯＦＦ
	]
	return		:[]
	common		:[tskno_EndBuzzer]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/03/18]
	author		:[江口]
*************************************************************************/
void EndBuzzer(void)
{
	if (CHK_SilentOperation()) {	/** サイレントモードであれば */
		return;
	}
	if (CHK_UNI_SilentOperation()) {	/** サイレントモードであれば By M.Tachibana 1997/12/03 */
		return;
	}

	if (tskno_end_buzzer == 0xFFFF) {	/* ブザー鳴動中でない */
		cre_tsk(&tskno_end_buzzer, TSK_CMN_ENDBUZZERTASK, 0);
	}
}

/*************************************************************************
	module		:[エンドブザー鳴動終了]
	function	:[
		1.エンドブザーを停止する
		2.通信完了／プリント完了の表示が終了する時にブザーも止める
		3.完了表示終了はチャイルド表示終了で判断する
	]
	return		:[]
	common		:[tskno_end_buzzer]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/03/18]
	author		:[江口]
*************************************************************************/
void StopEndBuzzer(void)
{
	if (tskno_end_buzzer != 0xffff) {	/* エンドブザー鳴動中であれば */
		del_tsk(&tskno_end_buzzer);
	}
}

/*************************************************************************
	module		:[アラームブザー鳴動]
	function	:[
		1.機械にエラーが起こったときのブザー
		2.ブザー鳴動する条件判断はこのモジュールの外で行うこと
		3.４秒間鳴動した後、ブザーはとまる、がタスクは存在する
	]
	return		:[]
	common		:[tskno_error_alarm]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/03/18]
	author		:[江口]
*************************************************************************/
void AlarmBuzzer(void)
{
	if (CHK_SilentOperation()) {	/** サイレントモードであれば */
		return;
	}
	if (CHK_UNI_SilentOperation()) {	/** サイレントモードであれば By M.Tachibana 1997/12/03 */
		return;
	}

	if (tskno_error_alarm == 0xFFFF) {	/* ブザー鳴動中でないなら */
		cre_tsk(&tskno_error_alarm, TSK_CMN_ERRORALARMTASK, 0);
	}
}

/*************************************************************************
	module		:[アラームブザー鳴動停止]
	function	:[
		1.アラームブザーを止める
	]
	return		:[]
	common		:[tskno_error_alarm]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/03/18]
	author		:[江口]
*************************************************************************/
void StopAlarmBuzzer(void)
{
	if (tskno_error_alarm != 0xffff) {	/* アラームブザー鳴動中 */
		del_tsk(&tskno_error_alarm);
	}
}

/*************************************************************************
	module		:[保留アラーム鳴動]
	function	:[
		1.
	]
	return		:[]
	common		:[tskno_hold_buzzer]
	condition	:[]
	comment		:[保留ブザー停止はいらん->保留ブザー鳴動タスクはexi_tskで終了するから。
				　タスク起動時の条件もいらん->exi_tskはTIDを初期化しない]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/03/18]
	author		:[江口]
*************************************************************************/
void HoldBuzzer(void)
{
	if (CHK_SilentOperation()) {	/** サイレントモードであれば */
		return;
	}
	if (CHK_UNI_SilentOperation()) {	/** サイレントモードであれば By M.Tachibana 1997/12/03 */
		return;
	}

	cre_tsk(&tskno_hold_alarm, TSK_CMN_HOLDALARMTASK, 0);
}

/*************************************************************************
	module		:[ハングアップブザー鳴動]
	function	:[
		1.
	]
	return		:[]
	common		:[tskno_HungUpBuzzer]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/03/18]
	author		:[江口]
*************************************************************************/
void HungUpBuzzer(void)
{
	if (CHK_SilentOperation()) {	/** サイレントモードであれば */
		return;
	}
	if (CHK_UNI_SilentOperation()) {	/** サイレントモードであれば By M.Tachibana 1997/12/03 */
		return;
	}

	if (tskno_hunguperror == 0xFFFF) {	/* ブザー鳴動中でない */
		cre_tsk(&tskno_hunguperror, TSK_CMN_HUNGUPERRORARAMTASK, 0);
	}
}

/*************************************************************************
	module		:[ハングアップブザー停止]
	function	:[
		1.受話器下がりを検出することにより停止
	]
	return		:[]
	common		:[tskno_HungUpBuzzer]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/03/18]
	author		:[江口]
*************************************************************************/
void StopHungUpBuzzer(void)
{
	if (tskno_hunguperror != 0xFFFF) {
		del_tsk(&tskno_hunguperror);
	}
}

/*************************************************************************
	module		:[保留終了ブザー鳴動]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/12/05]
	author		:[江口]
*************************************************************************/
void HoldEndBuzzer(void)
{
	if (CHK_SilentOperation()) {	/** サイレントモードであれば */
		return;
	}
	if (CHK_UNI_SilentOperation()) {	/** サイレントモードであれば By M.Tachibana 1997/12/03 */
		return;
	}

	cre_tsk(&tskno_hold_end, TSK_CMN_HOLDENDBUZZERTASK, 0);
}

#if defined(GBR)
/*************************************************************************
	module		:[受信アラームブザー鳴動 ]
	function	:[
		1.受信完了アラームの鳴動を行う。
		2.仕様はまだ
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[GBRのみ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/07/07]
	author		:[江口]
*************************************************************************/
void AudibleAlarmBuzzer(void)
{
	if (CHK_SilentOperation()) {	/* サイレントオペレーション TBD*/
		return;
	}
	if (CHK_UNI_SilentOperation()) {	/** サイレントモードであれば By M.Tachibana 1997/12/03 */
		return;
	}

	if (tskno_audible_alarm == 0xFFFF) {
		cre_tsk(&tskno_audible_alarm, TSK_CMN_ERRORENDLESSALARMTASK, 0);
	}
}

/*************************************************************************
	module		:[受信アラームブザー停止]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/07/07]
	author		:[江口]
*************************************************************************/
void StopAudibleAlarmBuzzer(void)
{
	if (tskno_audible_alarm != 0xFFFF) {
		del_tsk(&tskno_audible_alarm);
	}
}
#endif	/* defined(GBR) */

#if defined(STOCKHM2) /* 本体鳴動のテスト : by SMuratec C.P 2004/09/24 */
/*************************************************************************
	module		:[呼出ブザー鳴動]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[MAN]
	date		:[2001/06/28]
	author		:[高木 智史]
*************************************************************************/
void	CallingBuzzer(void)
{
	if (!CHK_CallingBuzzerMode()) {
		return;
	}

	if (tskno_callingbuzzer == 0xFFFF) {	/* ブザー鳴動中でない */
		cre_tsk(&tskno_callingbuzzer, TSK_CMN_CALLINGBUZZERTASK, 0);
	}
}
/*************************************************************************
	module		:[呼出ブザー停止]
	function	:[]
	return		:[]
	common		:[tskno_callingbuzzer]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[MAN]
	date		:[2001/06/28]
	author		:[高木 智史]
*************************************************************************/
void	StopCallingBuzzer(void)
{
	if (tskno_callingbuzzer != 0xFFFF) {
		del_tsk(&tskno_callingbuzzer);
	}
}
#endif
