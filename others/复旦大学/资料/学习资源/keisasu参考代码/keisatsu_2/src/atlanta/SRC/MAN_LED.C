/************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: MAN_LED.C
*	Author		: 渡辺一章
*	Date		: 1997/02/13
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ＬＥＤ制御
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By H.Fujimura 1998/12/09 */ /* Add by Y.Kano 2003/07/11 */
#include	"\src\atlanta\define\fcm_def.h"
#endif
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\syslocal.h"
#include	"\src\atlanta\define\sysrxsw.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\stng_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\io_pro.h"
#endif

#if (PRO_CLASS1 == ENABLE)
#include	"\src\atlanta\define\cl1_def.h"
#endif

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\mlt_pro.h"
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
#include	"\src\atlanta\define\sys_infd.h"
#include	"\src\atlanta\ext_v\sys_inf.h"
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/19*/
#include	"\src\atlanta\define\mntsw_g.h"
#include	"\src\atlanta\define\cmn_def.h"
#endif

/* Prototype
void	UpdateLED(void);
*/

/*************************************************************************
	module		:[ＬＥＤ制御]
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
	author		:[江口,渡辺一章]
*************************************************************************/
void UpdateLED(void)
{
	UBYTE	count;
#if (PRO_CLASS1 == ENABLE) /* 1996/09/20 Eguchi */
	struct SYS_MemoryRxPrintData_t *mem_rx;
#endif
#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/19*/
static UBYTE EcoAllLedOn = 0;
#endif
	/*------------------------------------------------------------------
	** ＬＥＤテスト中であればＬＥＤは更新しません
	** By M.Tachibana 1997/06/09
	*/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_LED_TEST) {
		return;
	}

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/19*/
	/*if (SYB_MaintenanceSwitch[MNT_SW_B5] & ECO_ALL_LED_ON) {	->SW変更 2003/02/05 M.Iida */
	if (SYB_MaintenanceSwitch[MNT_SW_G8] & ECO_ALL_LED_ON) {
		if (SYS_EcoModeStatus == ECO_MODE_ON) {
			AllLedOn();
			EcoAllLedOn = 1;
			return;
		}
		else {
			if (EcoAllLedOn == 1) {
				AllLedOff();
			}
			EcoAllLedOn = 0;
		}
	}
#endif

	/*---------------------------*/
	/** アラームＬＥＤ			 */
	/*---------------------------*/
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & (SYS_PRINTER_ERROR_ALARM1 & ~SYS_PRINTER_NO_ALL_PAPER))
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_SIZE_ERROR)
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_ERROR_ALARM3)
	 || (SYS_MachineStatus[SYS_SCANNER_STATUS]  & SYS_SCANNER_ERROR_ALARM)
 #if (PRO_UPPER_COVER == ENABLE)	/* 1998/01/26  By T.Yamaguchi */
	 || (SYS_MachineStatus[SYS_COVER_STATUS])
 #else
	 || (SYS_MachineStatus[SYS_COVER_STATUS]    & ~SYS_COVER_BOOK_OPEN)
 #endif
	 || (SYS_MachineStatus[SYS_ERROR_STATUS])
 #if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/06/15 */
	 || (SYS_MachineStatus[SYS_CIPHER_STATUS]   & SYS_CIPHER_ERROR_ALARM)
 #endif
	 || (SYS_MachineStatus[SYS_WARNING_STATUS]  & SYS_WARNING_DRUM_REPLACE)) {	/* 機器エラー */
		AlarmLedOn();
	}
	else {
		AlarmLedOff();
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	/* プリンターに関係するエラーの場合はアラームＬＥＤは点灯しない */
	if ((SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR)
	 || (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_LAMP_ERROR)
	 || (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER)
	 || (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER_OPR)
	 || (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_PAGE_ERROR)
	 || (SYS_MachineStatus[SYS_ERROR_STATUS])) {	/* 機器エラー */
		AlarmLedOn();
	}
	else if (SYS_MachineStatus[SYS_COVER_STATUS] != 0) {
		if ((SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE2_OPEN) && (SYS_SecondCassetteFlag == 0)) {
		/* カバーにエラーがありそのエラーが下段カセットオープンだが実は下段カセットは装着されていない場合 */
		/* エラーにはならない */
		/* カセットが未装着の場合はカセットオープンがセットされないのであれば不要なパス TBD */
			AlarmLedOff();
		}
		else {
			AlarmLedOn();
		}
	}
	else {
		AlarmLedOff();
	}
#endif
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
	if (
		(SYS_MachineStatus[SYS_PRINTER_STATUS1] & (SYS_PRINTER_NO_PAPER))
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Added by SMuratec 李 2004/7/6 */
		|| (SYS_MachineStatus[SYS_PRINTER_STATUS1] & (SYS_PRINTER_NO_INK))
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
		|| (SYS_MachineStatus[SYS_PRINTER_STATUS2] & (
													SYS_PRINTER_PAPER_JAM		|	/* ﾍﾟｰﾊﾟｰｼﾞｬﾑ */
													SYS_PRINTER_CUTTER_ERROR	|	/* ｶｯﾀｰｴﾗｰ *//* SAKAKI */
													SYS_PRINTER_HIGH_TEMP			/* サーマルヘッド異常温度 *//* SAKAKI */
												))
		|| (SYS_MachineStatus[SYS_SCANNER_STATUS] & (
													SYS_SCANNER_FEED_ERROR		|	/* 繰り込み不良 Clear Sensor & Main */
													SYS_SCANNER_LAMP_ERROR		|	/* 光量不足 Clear Sensor & Main */
													SYS_SCANNER_MEMORY_OVER		|	/* メモリ・オーバー Clear Initial & Opr. */
													SYS_SCANNER_PAGE_ERROR		|	/* 指定ページ枚数と原稿枚数不一致 Clear Opr */
													SYS_SCANNER_MEMORY_OVER_OPR 	/* メモリ・オーバー オペレーション */
												))
		|| (SYS_MachineStatus[SYS_COVER_STATUS] & (
													SYS_COVER_SCANNER_OPEN	|	/* スキャナカバーオープン*/
													SYS_COVER_PRINTER_OPEN		/* プリンターカバーオープン*/
												))
		|| (SYS_MachineStatus[SYS_ERROR_STATUS])) {
		AlarmLedOn();
	}
	else {
		AlarmLedOff();
	}
#endif

	/*---------------------------*/
	/** 通信中ＬＥＤ			 */
	/*---------------------------*/
#if (PRO_MULTI_LINE == DISABLE)
 #if (PRO_CLASS1 == DISABLE) /* 1996/09/20 Eguchi */
  #if defined (KEISATSU) /* 警察FAX Modified by SMuratec 李 2005/08/25 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)	/* 通信中 */
		|| (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON)) { /* 指令回線ﾓｰﾄﾞ */
		FaxComLedOn();
	}
  #else /* defined (KEISATSU) */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {	/* 通信中 */
		FaxComLedOn();
	}
  #endif /* defined (KEISATSU) */
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_DIALUP_INTERNET_FAX)
			&& (SYS_INF_ExecStatus != SYS_INF_STATUS_INITIAL)
			&& (SYS_INF_ExecStatus != SYS_INF_STATUS_UPDATE)) {
		FaxComLedOn();
	}
  #endif
	else {
		FaxComLedOff();
	}
 #else
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {	/* 通信中 */
		FaxComLedOn();
	}
	else if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM) {	/* PC-FAX動作中 */
		if (SYS_CL1_Status & (CL1_CALLED | CL1_FNET_CALLED | CL1_DIALIN_CALLED | CL1_RECEIVE | CL1_SEND)) {
			/* PC-FAX 通信中 */
			FaxComLedOn();
		}
		else {
			FaxComLedOff();
		}
	}
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_DIALUP_INTERNET_FAX)
			&& (SYS_INF_ExecStatus != SYS_INF_STATUS_INITIAL)
			&& (SYS_INF_ExecStatus != SYS_INF_STATUS_UPDATE)) {
		FaxComLedOn();
	}
  #endif
	else {
		FaxComLedOff();
	}
 #endif

#else
	if (OPT_CHK_FaxComExecute()) {	/* どっか通信中 */
		FaxComLedOn();
	}
 #if (PRO_CLASS1 == ENABLE)
	else if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM) {	/* PC-FAX動作中 */
		if (SYS_CL1_Status & (CL1_CALLED | CL1_FNET_CALLED | CL1_DIALIN_CALLED | CL1_RECEIVE | CL1_SEND)) {
			/* PC-FAX 通信中 */
			FaxComLedOn();
		}
		else {
			FaxComLedOff();
		}
	}
 #endif
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
	else if ((SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_DIALUP_INTERNET_FAX)
			&& (SYS_INF_ExecStatus != SYS_INF_STATUS_INITIAL)
			&& (SYS_INF_ExecStatus != SYS_INF_STATUS_UPDATE)) {
		FaxComLedOn();
	}
 #endif
	else {
		FaxComLedOff();
	}
#endif	/* (PRO_MULTI_LINE == DISABLE) */

	/*--------------------------*/
	/** 記録紙なしＬＥＤ		*/
	/*--------------------------*/
#if (PRO_KEYPANEL == PANEL_SAKAKI)
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#elif (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* For HINOKI By O.Kimoto 1998/09/07 */
																			/* Add by Y.Kano 2003/07/11 */
#else
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_ALL_PAPER) {
		/* カセットオープン・サイドカバーオープンの時は、同時に記録紙なしがＯＮしてしまうので、
		** 優先順位の高いカバーオープンだけを知らせるために、記録紙なしＬＥＤは点灯しません
		** by K.Watanabe 1997/12/24
		*/
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & (SYS_COVER_JAM_OPEN			/* ジャム除去カバーオープン			*/
												   | SYS_COVER_CASSETTE1_OPEN	/* カセット１オープン				*/
												   | SYS_COVER_CASSETTE2_OPEN	/* カセット２オープン				*/
												   | SYS_COVER_CASSETTE3_OPEN	/* カセット３オープン				*/
												   | SYS_COVER_2JAM_OPEN		/* ２ｎｄジャム処理カバーオープン	*/
												   | SYS_COVER_3JAM_OPEN))) {	/* ３ｎｄジャム処理カバーオープン	*/
			ReplacePaperLedOn();
		}
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	/* 上段記録紙なし又は、下段カセットユニット有りで記録紙なしの場合 */
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER)
	 || ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) && (SYS_SecondCassetteFlag == 1))) {
		/* SYS_SecondCassetteFlag == 1  下段カセット装着状態 By S.Kawasaki 1996/03/15 */
		/* 下段カセット無しの時は下段紙ﾅｼステータスがセットされないのであれば、条件を見直す TBD Eguchi */
		ReplacePaperLedOn();
	}
#endif
	else {
		ReplacePaperLedOff();
	}
	/*--------------------------*/
	/** ジャムＬＥＤ			*/
	/*--------------------------*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_ERROR_JAM) {	/* ペーパージャム */
		PaperJamLedOn();
	}
	else {
		PaperJamLedOff();
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	/*---------------------------*/
	/** プリンターエラー		 */
	/*---------------------------*/
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & (SYS_PRINTER_NO_CARTRIDGE    |
												   SYS_PRINTER_NO_INK          |
												   SYS_PRINTER_FEW_TONER))
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS2] & (SYS_PRINTER_SIZE_ERROR))
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS3] & (SYS_PRINTER_FUSER_ABNORMAL  |
												   SYS_PRINTER_FAN_ABNORMAL    |
												   SYS_PRINTER_MOTOR_ABNORMAL  |
												   SYS_PRINTER_LASER_ABNORMAL  |
												   SYS_PRINTER_SERIAL_ERROR    |
												   SYS_PRINTER_RESET_ERROR))) {	/* プリンターエラー */
		PrinterAlarmLedOn();
	}
	else {
		if (SYS_MachineStatus[SYS_WARNING_STATUS] & SYS_WARNING_DRUM_REPLACE) {	/* プリンターのドラム交換ﾜｰﾆﾝｸﾞ 追加1996/06/20　Eguchi */
			PrinterAlarmLedOn();
		}
		else {
			PrinterAlarmLedOff();
		}
	}
#endif

	/*---------------------------*/
	/** フックＬＥＤ			 */
	/*---------------------------*/
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/09/15 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) {
		HookLedOn();
	}
	else {
		HookLedOff();
	}

	/*---------------------------*/
	/** 会話ＬＥＤ				 */
	/*---------------------------*/
	if (SYS_VoiceSwitch == 1) {
		ReservationLedOn();
	}
	else {
		ReservationLedOff();
	}
#else
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) || (SYS_VoiceSwitch == 1)) {
	/* フックキーオフフック或いは会話予約 */
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
		HookLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	}
	else {
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
		HookLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	}
#endif

	/*---------------------------*/
	/** 代行受信ＬＥＤ			 */
	/*---------------------------*/
#if (PRO_MULTI_LINE == DISABLE)
 #if (PRO_CLASS1 == DISABLE) /*1996/09/20 Eguchi */
	for (count = 0; count < SYS_MEMORY_RX_MAX; count++) {
		if (SYB_MemoryRxPrint[count].Status >= SYS_MEMORY_RX_STORE) {
			MemoryRxLedOn();
			break;
		}
	}
	if (count == SYS_MEMORY_RX_MAX) {
		MemoryRxLedOff();
	}
 #else
	/* 通常の代行受信の有無とローカルプリント原稿の有無を調べる */
	for (count = 0; count < (UBYTE)(SYS_MEMORY_RX_MAX + SYS_MEMORY_RX_MAX); count++) {
		if (count < SYS_MEMORY_RX_MAX) {
			/* 代行受信管理テーブルを調べる */
			mem_rx = &SYB_MemoryRxPrint[count];
		}
		else {
			/* ローカルプリント管理用テーブルを調べる */
			mem_rx = &SYB_CL1_MemoryRxPrint[(UBYTE)(count - SYS_MEMORY_RX_MAX)];
		}
		if (mem_rx->Status >= SYS_MEMORY_RX_STORE) {
			MemoryRxLedOn();
			break;
		}
	}
	if (count == (UBYTE)(SYS_MEMORY_RX_MAX + SYS_MEMORY_RX_MAX)) {
		MemoryRxLedOff();
	}
 #endif

#else
	/*------------*/
	/* ２回線仕様 */
	/*------------*/
 #if (PRO_CLASS1 == DISABLE)
	for (count = 0; count < SYS_MEMORY_RX_MAX; count++) {
  #if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/26 */
		if ((SYB_MemoryRxPrint[count].Status == SYS_MEMORY_RX_STORE)
		 || (SYB_MemoryRxPrint[count].Status == SYS_MEMORY_RX_PRINT)
		 || (SYB_MemoryRxPrint[count].Status == SYS_MEMORY_RX_POWEROFF)) {
  #else	/* Status >= SYS_MEMORY_RX_STOREの条件ではいけないのか？ */
		if ((SYB_MemoryRxPrint[count].Status == SYS_MEMORY_RX_STORE)
		 || (SYB_MemoryRxPrint[count].Status == SYS_MEMORY_RX_PRINT)
		 || (SYB_MemoryRxPrint[count].Status == SYS_MEMORY_RX_STORE_PRINT)
		 || (SYB_MemoryRxPrint[count].Status == SYS_MEMORY_RX_FAST_PRINT)
		 || (SYB_MemoryRxPrint[count].Status == SYS_MEMORY_RX_POWEROFF)) {
  #endif
			MemoryRxLedOn();
			break;
		}
	}
	if (count == SYS_MEMORY_RX_MAX) {
		MemoryRxLedOff();
	}
 #else
	/* 通常の代行受信の有無とローカルプリント原稿の有無を調べる */
	for (count = 0; count < (UBYTE)(SYS_MEMORY_RX_MAX + SYS_MEMORY_RX_MAX); count++) {
		if (count < SYS_MEMORY_RX_MAX) { 
			/* 代行受信管理テーブルを調べる */
			mem_rx = &SYB_MemoryRxPrint[count]; 
		}
		else {
			/* ローカルプリント管理用テーブルを調べる */
			mem_rx = &SYB_CL1_MemoryRxPrint[(UBYTE)(count - SYS_MEMORY_RX_MAX)];
		}

  #if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/26 */
		if ((mem_rx->Status == SYS_MEMORY_RX_STORE)
		 || (mem_rx->Status == SYS_MEMORY_RX_PRINT)
		 || (mem_rx->Status == SYS_MEMORY_RX_POWEROFF)) {
  #else	/* Status >= SYS_MEMORY_RX_STOREの条件ではいけないのか？ */
		if ((mem_rx->Status == SYS_MEMORY_RX_STORE)
		 || (mem_rx->Status == SYS_MEMORY_RX_PRINT)
		 || (mem_rx->Status == SYS_MEMORY_RX_STORE_PRINT)
		 || (mem_rx->Status == SYS_MEMORY_RX_FAST_PRINT)
		 || (mem_rx->Status == SYS_MEMORY_RX_POWEROFF)) {
  #endif
			MemoryRxLedOn();
			break;
		}
	}

	if (count == (UBYTE)(SYS_MEMORY_RX_MAX + SYS_MEMORY_RX_MAX)) {
		MemoryRxLedOff();
	}
 #endif
#endif	/* (PRO_MULTI_LINE == DISABLE) */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
	for (count = 0; count < SYS_INF_MAIL_BOX_MAX; count++) {
		if (SYS_INF_RxMailBox[count].Status == SYS_INF_RX_MAIL_RECEIVED) {
			MemoryRxLedOn();
			break;
		}
	}
#endif

	/*---------------------------*/
	/** メモリー送信ＬＥＤ		 */
	/*---------------------------*/
	if (CMN_CheckMemoryTxSetting() == TRUE) {	/* メモリ送信 */
		MemoryTxLedOn();
	}
	else {
		MemoryTxLedOff();
	}

	/*---------------------------*/
	/* 済みスタンプＬＥＤ		 */
	/*---------------------------*/
#if defined(KEISATSU)	/* 警察FAX対応 Modify start by SMuratec K.W.Q 2005/07/01 */
	/* 警察FAX中済スタンプ機能を削除 */
	StampLedOff();	/* TEMP 設定です。別機能LEDになります */
	
#else
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By H.Fujimura 1999/01/05 */
																		/* Add by Y.Kano 2003/07/11 */
 #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	if (CHK_UNI_RedScanModeEnable() && !CHK_UNI_CSDR_ConfirmOprEnable() && !CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_LocalStatus[0] & SYS_RED_SCAN) {
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		else {
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
	}
	/*【CSDR-No.111】通信証ON/OFF有効時 */
	else if (!CHK_UNI_RedScanModeEnable() && CHK_UNI_CSDR_ConfirmOprEnable() && !CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_ConfirmationReportSwitch == NO_CONFIRMATION_REPORT) {
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		else {
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
	}
	/*【CSDR-No.102】発信元ON/OFF有効時 */
	else if (!CHK_UNI_RedScanModeEnable() && !CHK_UNI_CSDR_ConfirmOprEnable() && CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_LocalStatus[0] & SYS_TTI_TX_AVAILABLE_ON) {
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		else {
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
	}
	else {
		if (SYB_LocalStatus[0] & SYS_STAMP_ON) {
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		else {
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
	}
 #else
	/*【CSDR-No.111】通信証ON/OFF有効時 */
	if (CHK_UNI_CSDR_ConfirmOprEnable() && !CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_ConfirmationReportSwitch == NO_CONFIRMATION_REPORT) {
			StampLedOff();
		}
		else {
			StampLedOn();
		}
	}
	/*【CSDR-No.102】発信元ON/OFF有効時 */
	else if (!CHK_UNI_CSDR_ConfirmOprEnable() && CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_LocalStatus[0] & SYS_TTI_TX_AVAILABLE_ON) {
			StampLedOn();
		}
		else {
			StampLedOff();
		}
	}
	else {
		if (SYB_LocalStatus[0] & SYS_STAMP_ON) {
			StampLedOn();
		}
		else {
			StampLedOff();
		}
	}
 #endif
#else
 #if (PRO_EXT_SEC_RX == ENABLE) /* ｾｷｭﾘﾃｨ受信(単一ｷｰ対応) By H.Fujimura 1999/11/26 */
	if (CHK_UNI_ExtSecurityRxOperation()) {
		if (SYB_SecurityRxModeFlag == 1) {
			StampLedOn();
		}
		else {
			StampLedOff();
		}
	}
	else {
		if (SYB_LocalStatus[0] & SYS_STAMP_ON) {
			StampLedOn();
		}
		else {
			StampLedOff();
		}
	}
 #else
	if (SYB_LocalStatus[0] & SYS_STAMP_ON) {
		StampLedOn();
	}
	else {
		StampLedOff();
	}
 #endif
#endif
#endif		/* 警察FAX対応 Modify end by SMuratec K.W.Q 2005/07/01 */

	/*---------------------------*/
	/** 画質ＬＥＤ				 */
	/*---------------------------*/
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
	ModeLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI) || (defined(POPLAR_H) && defined(JP0)) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)																		/* Add by Y.Kano 2003/07/11 */
	/*---------------------------*/
	/** 濃度ＬＥＤ				 */
	/*---------------------------*/
 #if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
	DensityLedOn();
 #endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
#endif

	/*---------------------------*/
	/* 自動受信ＬＥＤ			 */
	/*---------------------------*/
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 1998/11/16 H.Yoshikawa */
																		/* Add by Y.Kano 2003/07/11 */
  #if defined (KEISATSU) /* 警察FAX Modified by SMuratec 李 2005/08/25 */
  	if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
		if ( CheckIsKanyuLine() ){
			AutoRxLedOn();
		}
		else{
			AutoRxLedOff();
		}
	}
   	else if ( CheckIsKanyuLine() && (SYB_RxModeSwitch & SYS_AUTO_CALLED_SW) ){
		AutoRxLedOn();
	}
	else if ( !CheckIsKanyuLine() && (SYB_RxModeSwitchExt & SYS_AUTO_CALLED_SW) ) {
		AutoRxLedOn();
	}
	else{
		AutoRxLedOff();
	}
  #else /* defined (KEISATSU) */
	if (CMN_PresentReceiveMode() == SYS_TEL_READY) {
		AutoRxLedOff();
	}
	else {
		AutoRxLedOn();
	}
  #endif /* defined (KEISATSU) */
#else
 #if defined(POPLAR_F)	/* 2000/02/10 Y.Murata */
	if (CMN_PresentReceiveMode() == SYS_TEL_READY) {
		AutoRxLedOff();
	}
	else {
		AutoRxLedOn();
	}
 #else
	if (CHK_AutoRxSwitch()) {
		AutoRxLedOn();
	}
	else {
		AutoRxLedOff();
	}
 #endif
#endif

#if (PRO_COPY_FAX_MODE == ENABLE)
	/*---------------------------*/
	/** コピー／ファクスＬＥＤ	 */
	/*---------------------------*/
	if (CHK_ReadyModeCopy()) {
		CopyModeLedOn();
	}
	else {
		FaxModeLedOn();
	}
#endif
}
