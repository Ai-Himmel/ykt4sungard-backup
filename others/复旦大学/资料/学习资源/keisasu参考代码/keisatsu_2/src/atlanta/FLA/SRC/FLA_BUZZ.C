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
#include "\src\atlanta\define\buzzer.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\\ext_v\sys_port.h"
#include "\src\atlanta\sh7043\define\io_pro.h"

#include "\src\ATLANTA\FLA\define\sys_pro.h"
/* #include "\src\ATLANTA\FLA\ext_v\sys_data.h" */

#pragma section FLASHWRITE /*  "PFLASHWRITE" */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)

#if 0 /* 未使用 1998/04/17  By T.Yamaguchi */
///*************************************************************************
//	module		:[アックブザーを鳴動させる]
//	function	:[
//		1.ON-OFF・・・・OFF-ON のパターンでならす
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[CMN]
//	date		:[1996/05/08]
//	author		:[江口]
//*************************************************************************/
//void	FLA_AckBuzzerSound(void)
//{
//	UBYTE cycle;
//
//	cycle = ACK_BUZZER_CYCLE;
//	FLA_SCN_SetBuzzerFrequency(ACK_BUZZER_FREQ);
//	FLA_BuzzerOnSetting(SYS_SPK_OUT_KEYBUZZER);
//
//	while (1) {
//		FLA_SCN_SetBuzzer(SCN_ENABLE);
//		FLA_wait_timer(ACK_BUZZER_LENGTH);
//		if (--cycle == 0) {
//			break;
//		}
//		FLA_SCN_SetBuzzer(SCN_DISABLE);
//		FLA_wait_timer(ACK_BUZZER_LENGTH);
//	}
//	FLA_BuzzerOffSetting(SYS_SPK_OUT_KEYBUZZER);
//}
//
//
///*************************************************************************
//	module		:[ナックブザーを鳴動される]
//	function	:[
//		1.OFF-ON-・・・・OFF-ON-OFF のパターンで鳴動させる
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[CMN]
//	date		:[1996/05/08]
//	author		:[江口]
//*************************************************************************/
//void	FLA_NackBuzzerSound(void)
//{
//	UBYTE cycle;
//
//	cycle = NACK_BUZZER_CYCLE;
//	FLA_SCN_SetBuzzerFrequency(NACK_BUZZER_FREQ);
//	FLA_BuzzerOnSetting(SYS_SPK_OUT_KEYBUZZER);
//
//	while (1) {
//		FLA_SCN_SetBuzzer(SCN_DISABLE);
//		FLA_wait_timer(NACK_BUZZER_LENGTH);
//		if (cycle == 0) {
//			break;
//		}
//		FLA_SCN_SetBuzzer(SCN_ENABLE);
//		FLA_wait_timer(NACK_BUZZER_LENGTH);
//		cycle--;
//	}
//	FLA_BuzzerOffSetting(SYS_SPK_OUT_KEYBUZZER);
//}
#endif

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
/*void	CMN_EndBuzzerTask(void)*/
void	FLA_EndBuzzerSound(void)
{
	FLA_BuzzerOnSetting(SYS_SPK_OUT_ENDBUZZER);
	FLA_SCN_SetBuzzerFrequency(END_BUZZER_FREQ);

	FLA_SCN_SetBuzzer(SCN_ENABLE);
	FLA_wait_timer(END_BUZZER_LENGTH);

	FLA_BuzzerOffSetting(SYS_SPK_OUT_ENDBUZZER);

/*	wai_tsk(0xffff);	*/
}

#if 0 /* 未使用 1998/04/17  By T.Yamaguchi  */
///*************************************************************************
//	module		:[保留アラーム鳴動タスク]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[CMN]
//	date		:[1996/05/08]
//	author		:[江口]
//*************************************************************************/
///*void	CMN_HoldAlarmTask(void)*/
//void	FLA_HoldAlarmSound(void)
//{
//	UBYTE cycle;
//	UBYTE buzzer_status;
//
//	buzzer_status = SCN_DISABLE;
//	cycle = HOLD_ALARM_CYCLE*2;
//
//	FLA_SCN_SetBuzzerFrequency(HOLD_ALARM_FREQ);
//	FLA_BuzzerOnSetting(SYS_SPK_OUT_HOLDALARM);
//
//	while (cycle--) {
//		FLA_SCN_SetBuzzer(buzzer_status);
//		FLA_wait_timer(HOLD_ALARM_LENGTH);
//
//		if (buzzer_status == SCN_ENABLE) {
//			buzzer_status = SCN_DISABLE;
//		}
//		else {
//			buzzer_status = SCN_ENABLE;
//		}
//	}
//	FLA_BuzzerOffSetting(SYS_SPK_OUT_HOLDALARM);
///*	exi_tsk();*/
//}
#endif

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
/*void	CMN_ErrorAlarmTask(void)*/
void	FLA_ErrorAlarmSound(void)
{

	UBYTE cycle;
	UBYTE buzzer_status;

	buzzer_status = SCN_DISABLE;
	cycle = ERROR_ALARM_CYCLE*2;

	FLA_BuzzerOnSetting(SYS_SPK_OUT_ALARMBUZZER);

	FLA_SCN_SetBuzzerFrequency(ERROR_ALARM_FREQ);
	while (cycle--) {
		FLA_SCN_SetBuzzer(buzzer_status);
		FLA_wait_timer(ERROR_ALARM_LENGTH);

		if (buzzer_status == SCN_ENABLE) {
			buzzer_status = SCN_DISABLE;
		}
		else {
			buzzer_status = SCN_ENABLE;
		}
	}

	FLA_BuzzerOffSetting(SYS_SPK_OUT_ALARMBUZZER);

/*	wai_tsk(0xffff);*/
}

#if 0	/* 未使用 1998/04/17  By T.Yamaguchi */
///*************************************************************************
//	module		:[エラーエンドレスアラーム鳴動タスク]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[CMN]
//	date		:[1996/05/08]
//	author		:[江口]
//*************************************************************************/
///*void	CMN_ErrorEndlessAlarmTask(void)*/
//void	FLA_ErrorEndlessAlarmSound(void)
//{
//	UBYTE buzzer_status;
//
//	buzzer_status = SCN_DISABLE;
//	FLA_BuzzerOnSetting(SYS_SPK_OUT_ENDLESSALARM);
//	FLA_SCN_SetBuzzerFrequency(ERROR_ENDLESS_ALARM_FREQ);
//
//	while (1) {
//		FLA_SCN_SetBuzzer(buzzer_status);
//		FLA_wait_timer(ERROR_ENDLESS_ALARM_LENGTH);
//		if (buzzer_status == SCN_ENABLE) {
//			buzzer_status = SCN_DISABLE;
//		}
//		else {
//			buzzer_status = SCN_ENABLE;
//		}
//	}
//}
///*************************************************************************
//	module		:[受話器ハングアップエラーアラーム鳴動タスク]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[CMN]
//	date		:[1996/05/08]
//	author		:[江口]
//*************************************************************************/
///*void	CMN_HungUpErrorAramTask(void)*/
//void	FLA_HungUpErrorAramSound(void)
//{
//	UBYTE buzzer_status;
//
//	buzzer_status = SCN_DISABLE;
//	FLA_SCN_SetBuzzerFrequency(ERROR_ENDLESS_ALARM_FREQ);
//	FLA_BuzzerOnSetting(SYS_SPK_OUT_HUNGUP);
//
//	while (1) {
//		FLA_SCN_SetBuzzer(buzzer_status);
//		FLA_wait_timer(ERROR_ENDLESS_ALARM_LENGTH);
//		if (buzzer_status == SCN_ENABLE) {
//			buzzer_status = SCN_DISABLE;
//		}
//		else {
//			buzzer_status = SCN_ENABLE;
//		}
//	}
//}
//
//
///*************************************************************************
//	module		:[保留終了ブザー鳴動タスク]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[CMN]
//	date		:[1996/05/08]
//	author		:[江口]
//*************************************************************************/
///*void	CMN_HoldEndBuzzerTask(void)*/
//void	FLA_HoldEndBuzzerSound(void)
//{
//	FLA_BuzzerOnSetting(SYS_SPK_OUT_HOLDEND);
//
//	FLA_SCN_SetBuzzerFrequency(END_BUZZER_FREQ);
//	FLA_SCN_SetBuzzer(SCN_ENABLE);
//	FLA_wait_timer(END_BUZZER_LENGTH);
//
//	FLA_BuzzerOffSetting(SYS_SPK_OUT_HOLDEND);
///*	exi_tsk();*/
//}
#endif

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
void	FLA_BuzzerOnSetting(UWORD	buzzer_type)
{
/*	SYS_SpeakerOutputStatus |= buzzer_type;*/		/** 指定されたブザー鳴動中のステータスをセット */
	FLA_SpeakerOutBuzzer();							/** スピーカー出力をブザー側に切り替える　*/
	FLA_BuzzerVolumeControl();						/** ボリュームセット */
	FLA_SpeakerMuteOff();							/** スピーカーのミュート状態を解除する */
	buzzer_type = 0;	/* for Warning */
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
void	FLA_BuzzerOffSetting(UWORD	buzzer_type)
{
	FLA_SCN_SetBuzzer(SCN_DISABLE);					/** ブザー鳴動終了 */
	FLA_SpeakerMuteOn();							/** スピーカー出力をミュートする */
/*	SYS_SpeakerOutputStatus &= ~buzzer_type;*/
	buzzer_type = 0;	/* for Warning */
}


void FLA_wait_timer(UWORD wait_time)
{
/*	UWORD	time;	*/

/*
	time = SYS_GeneralTimer;

	while ((UWORD)(SYS_GeneralTimer - time) < wait_time) {
	}
*/
	while (wait_time) {
		FLA_wait10ms_timer();
		wait_time--;
	}
}

void FLA_wait10ms_timer(void)
{
	UWORD timer10ms;

	timer10ms = 0x6e70;		/* 28272 約１０ｍｓ */
	
	while (timer10ms) {
		timer10ms--;
	}
}
#endif

#pragma section

