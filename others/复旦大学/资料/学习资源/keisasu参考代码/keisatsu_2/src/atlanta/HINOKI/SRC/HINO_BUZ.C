/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_BUZZ.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_buzz.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"

#if (PRO_KEYPANEL == PANEL_HINOKI)	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */

#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\buzzer.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\atlanta\\ext_v\sys_port.h"	/****/
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\sys_port.h"
#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"

void bell_on(void);
void bell_off(void);

/*************************************************************************
	module		:[アック・ナックブザー鳴動タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		1.このタスクは起動されるタスク(OPR等)より、優先順位が高くないといけない
				]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_BuzzerTask(void)
{
	MESSAGE_t *CMN_Buzzer;

	while (1) {
		rcv_msg(mbxno.CMN_BuzzerTask, &CMN_Buzzer);
		switch (CMN_Buzzer->Message) {
		case ACK_BUZZER:				/** アックブザー処理 **/
			AckBuzzerSound();
			break;
		case NACK_BUZZER:				/** ナックブザー処理 **/
			NackBuzzerSound();
			break;
		default:
			break;
		}
	}
}

/*************************************************************************
	module		:[アックブザーを鳴動させる]
	function	:[
		1.ON-OFF・・・・OFF-ON のパターンでならす
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	AckBuzzerSound(void)
{
	UBYTE cycle;

	cycle = ACK_BUZZER_CYCLE;
	BuzzerOnSetting(SYS_SPK_OUT_KEYBUZZER);

	while (1) {
		bell_on();
		wai_tsk(ACK_BUZZER_LENGTH);
		if (--cycle == 0) {
			break;
		}
		bell_off();
		wai_tsk(ACK_BUZZER_LENGTH);
	}
	BuzzerOffSetting(SYS_SPK_OUT_KEYBUZZER);
}

/*************************************************************************
	module		:[ナックブザーを鳴動される]
	function	:[
		1.OFF-ON-・・・・OFF-ON-OFF のパターンで鳴動させる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	NackBuzzerSound(void)
{
	UBYTE cycle;

	cycle = NACK_BUZZER_CYCLE;
	BuzzerOnSetting(SYS_SPK_OUT_KEYBUZZER);

	while (1) {
		bell_off();
		wai_tsk(NACK_BUZZER_LENGTH);
		if (cycle == 0) {
			break;
		}
		bell_on();
		wai_tsk(NACK_BUZZER_LENGTH);
		cycle--;
	}
	BuzzerOffSetting(SYS_SPK_OUT_KEYBUZZER);
}


/*************************************************************************
	module		:[終了ブザー鳴動タスク]
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
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_EndBuzzerTask(void)
{
	BuzzerOnSetting(SYS_SPK_OUT_ENDBUZZER);

	bell_on();
	wai_tsk(END_BUZZER_LENGTH);

	BuzzerOffSetting(SYS_SPK_OUT_ENDBUZZER);

	wai_tsk(0xffff);
}



/*************************************************************************
	module		:[終了ブザー鳴動タスク終了処理]
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
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_EndBuzzerExit(void)
{
	BuzzerOffSetting(SYS_SPK_OUT_ENDBUZZER);
	exi_tsk();
}


/*************************************************************************
	module		:[保留アラーム鳴動タスク]
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
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_HoldAlarmTask(void)
{
	UBYTE cycle;
	UBYTE buzzer_status;

	buzzer_status = SCN_DISABLE;
	cycle = HOLD_ALARM_CYCLE*2;

	BuzzerOnSetting(SYS_SPK_OUT_HOLDALARM);

	while (cycle--) {
		if (buzzer_status == SCN_ENABLE) {
			bell_on();
			buzzer_status = SCN_DISABLE;
		}
		else {
			bell_off();
			buzzer_status = SCN_ENABLE;
		}
		wai_tsk(HOLD_ALARM_LENGTH);
	}
	BuzzerOffSetting(SYS_SPK_OUT_HOLDALARM);
	exi_tsk();
}



/*************************************************************************
	module		:[エラーアラーム鳴動タスク]
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
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_ErrorAlarmTask(void)
{

	UBYTE cycle;
	UBYTE buzzer_status;

	buzzer_status = SCN_DISABLE;
	cycle = ERROR_ALARM_CYCLE*2;

	BuzzerOnSetting(SYS_SPK_OUT_ALARMBUZZER);

	while (cycle--) {
		if (buzzer_status == SCN_ENABLE) {
			bell_on();
			buzzer_status = SCN_DISABLE;
		}
		else {
			bell_off();
			buzzer_status = SCN_ENABLE;
		}
		wai_tsk(ERROR_ALARM_LENGTH);
	}

	BuzzerOffSetting(SYS_SPK_OUT_ALARMBUZZER);

	wai_tsk(0xffff);
}



/*************************************************************************
	module		:[エラーアラーム鳴動タスク終了処理]
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
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_ErrorAlarmExit(void)
{
	BuzzerOffSetting(SYS_SPK_OUT_ALARMBUZZER);
	exi_tsk();
}


/*************************************************************************
	module		:[エラーエンドレスアラーム鳴動タスク]
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
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_ErrorEndlessAlarmTask(void)
{
	UBYTE buzzer_status;

	buzzer_status = SCN_DISABLE;
	BuzzerOnSetting(SYS_SPK_OUT_ENDLESSALARM);

	while (1) {
		if (buzzer_status == SCN_ENABLE) {
			bell_on();
			buzzer_status = SCN_DISABLE;
		}
		else {
			bell_off();
			buzzer_status = SCN_ENABLE;
		}
		wai_tsk(ERROR_ENDLESS_ALARM_LENGTH);
	}
}


/*************************************************************************
	module		:[エラーエンドレスアラーム鳴動タスク終了処理]
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
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_ErrorEndlessAlarmExit(void)
{
	BuzzerOffSetting(SYS_SPK_OUT_ENDLESSALARM);
	exi_tsk();
}

/*************************************************************************
	module		:[受話器ハングアップエラーアラーム鳴動タスク]
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
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_HungUpErrorAramTask(void)
{
	UBYTE buzzer_status;

	buzzer_status = SCN_DISABLE;
	BuzzerOnSetting(SYS_SPK_OUT_HUNGUP);

	while (1) {
		if (buzzer_status == SCN_ENABLE) {
			bell_on();
			buzzer_status = SCN_DISABLE;
		}
		else {
			bell_off();
			buzzer_status = SCN_ENABLE;
		}
		wai_tsk(ERROR_ENDLESS_ALARM_LENGTH);
	}
}


/*************************************************************************
	module		:[ハングアップエラーアラーム鳴動タスク終了処理]
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
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_HungUpErrorAramExit(void)
{
	BuzzerOffSetting(SYS_SPK_OUT_HUNGUP);
	exi_tsk();
}

/*************************************************************************
	module		:[保留終了ブザー鳴動タスク]
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
	date		:[1996/05/08]
	author		:[江口]
*************************************************************************/
void	CMN_HoldEndBuzzerTask(void)
{
	BuzzerOnSetting(SYS_SPK_OUT_HOLDEND);

	bell_on();
	wai_tsk(END_BUZZER_LENGTH);

	BuzzerOffSetting(SYS_SPK_OUT_HOLDEND);
	exi_tsk();
}


/*************************************************************************
	module		:[ブザー鳴動開始処理]
	function	:[
		1.スピーカ出力状態を保持する変数(SYS_SpeakerOutPutSource）にブザー出力状態をセットする。
		2.スピーカー出力をブザーに切り替える。
		3:スピーカーボリュームにブザー鳴動時のボリューム値をセットする。
	]
	return		:[]
	common		:[SYS_SpeakerOutputStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/02/21]
	author		:[江口]
*************************************************************************/
void	BuzzerOnSetting(UWORD	buzzer_type)
{
	SYS_SpeakerOutputStatus |= buzzer_type;		/** 指定されたブザー鳴動中のステータスをセット */
	SpeakerOutBuzzer();							/** スピーカー出力をブザー側に切り替える　*/
	SpeakerMuteOff();							/** スピーカーのミュート状態を解除する */
}


/*************************************************************************
	module		:[ブザー鳴動終了処理]
	function	:[
		1.鳴動終了するブザー以外のブザーが鳴っていないか調べる。
		2.鳴っていなければ、ブザー鳴動を停止して回線モニター中であるか調べる。
		3.回線モニター中であれば、以下の処理を実行.
		,　・ボリュームの値を回線モニター時のボリューム値にセットする。
		,　・スピーカ出力をＲＸＡに切り替える。
		,　・スピーカ出力のミュートを解除する。
		4.回線モニター中でなければ、スピーカー出漁をミュートする。
		5.スピーカ出力状態を保持する変数の、鳴動終了するブザーに対するビットをクリアする。
	]
	return		:[]
	common		:[SYS_SpeakerOutputStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/21]
	author		:[江口]
*************************************************************************/
void	BuzzerOffSetting(UWORD	buzzer_type)
{
	if (CheckOtherBuzzerSound(buzzer_type) == FALSE) {	/** 他のブザーは鳴動していない */
		bell_off();						/** ブザー鳴動終了 */
		if (SYS_SpeakerOutputStatus &  SYS_SPK_OUT_MONITOR) {	/** 回線モニター中にブザーを鳴らした場合、*/
			MonitorSpeakerVolumeControl();	/** ボリュームの値をモニター時のボリュームに戻す */
			SpeakerOutRXA();				/** スピーカ出力をRXA（回線モニター）に切り替えておく	 */
			SpeakerMuteOff();			  /** スピーカ出力ｏｎ */
		}
		else {		/** 回線モニター中でない */
			SpeakerMuteOn();				/** スピーカー出力をミュートする */
		}
	}
	SYS_SpeakerOutputStatus &= ~buzzer_type;
}


/*************************************************************************
	module		:[指定されたブザー以外のブザーが鳴動中か調べる]
	function	:[
		1.
	]
	return		:[
				TRUE:他のブザーが鳴動中
				FALSE:他のブザーは鳴動していない
				]
	common		:[SYS_SpeakeroutputStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/21]
	author		:[江口]
*************************************************************************/
UBYTE	CheckOtherBuzzerSound(UWORD	buzzer_type)
{
	if (SYS_SpeakerOutputStatus & (buzzer_type ^ SYS_CHKBUZZER_MASK_BIT)) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[ブザー鳴動中か調べる]
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
	date		:[1996/02/21]
	author		:[江口]
*************************************************************************/
UWORD	CheckBuzzerSound(void)
{
	return ((UBYTE)(SYS_SpeakerOutputStatus & SYS_CHKBUZZER_MASK_BIT));
}

/*************************************************************************
	module		:[手差し用紙補給要求ブザー鳴動]
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
	date		:[1997/05/26]
	author		:[橘正樹]
*************************************************************************/
void	CMN_PaperSupplyBuzzer(void)
{
	UBYTE cycle;
	UBYTE buzzer_status;

	buzzer_status = SCN_DISABLE;
	cycle = PAPER_SUPPLY_BUZZER_CYCLE*2;

	BuzzerOnSetting(SYS_SPK_OUT_PAPERSUPPLY);

	while (cycle--) {
		if (buzzer_status == SCN_ENABLE) {
			bell_on();
			buzzer_status = SCN_DISABLE;
		}
		else {
			bell_off();
			buzzer_status = SCN_ENABLE;
		}
		wai_tsk(PAPER_SUPPLY_BUZZER_LENGTH);
	}

	BuzzerOffSetting(SYS_SPK_OUT_PAPERSUPPLY);
}

/*-----------------------------------------------------------------------*
	module		:[ベル／ブザーを鳴動させる]
	function	:[ＭＴＵの設定を行う]
	return		:[]
	common		:[]
	comment		:[ＭＴＵチャネル１を使用､ＰＷＭモード１]
*-----------------------------------------------------------------------*/
void	bell_on(void)
{
	/*----------------------------------------------------------------------*/
	/* ＴＣＲの設定			 												*/
	/* ・ＴＧＲＡのコンペアマッチ/インプットキャプチャでＴＣＮＴをクリア 	*/
	/* ・立ち上がりエッジでカウント											*/
	/* ・内部クロックφ/16でカウント										*/
	/*----------------------------------------------------------------------*/
	MTU__TCR3 = 0x22;		/* Output(MTU_TCR1, 0x22); */
	/*--------------------------------------*/
	/* 波形出力レベルの選択 				*/
	/* TGR1B:出力禁止､TGR1A:ﾄｸﾞﾙ出力		*/
	/*--------------------------------------*/
	MTU__TIOR3H = 0x03;		/* Output(MTU_TIOR1, 0x03); */
	/*--------------------------------------*/
	/* ＴＧＲの設定(1,000Hz)				*/
	/*--------------------------------------*/
	MTU__TGR3A = 875;		/* OutputWORD(MTU_TGR1A, 875); */
	/*--------------------------------------*/
	/* ＴＭＤＲの設定			 			*/
	/* ・動作モード：ＰＷＭモード１			*/
	/*--------------------------------------*/
	MTU__TMDR3 = 0x02;		/* Output(MTU_TMDR1, 0x02); */
	/*--------------------------------------*/
	/* ＣＨ１カウンタスタート				*/
	/*--------------------------------------*/
	MTU__TSTR |= TSTR_START_CH3;	/* (Output(MTU_TSTR, (Input(MTU_TSTR) | TSTR_START_CH1)); */
}

/*-----------------------------------------------------------------------*
	module		:[ベル／ブザーの鳴動を停止させる]
	function	:[]
	return		:[]
	common		:[]
	comment		:[]
*-----------------------------------------------------------------------*/
void	bell_off(void)
{
	MTU__TSTR &= ~TSTR_START_CH3;	/* Output(MTU_TSTR, (Input(MTU_TSTR) & ~TSTR_START_CH1)); */
}


#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) */

