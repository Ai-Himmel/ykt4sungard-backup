/************************************************************************
*	System		: SATSUKI2
*	File Name	: OPR_VOL.C
*	Author		: 加納  義彦
*	Date		: 2003/08/29
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ボリューム設定オペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\unisw_h.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\cmn_def.h"

#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/09/01 */
#include	"\src\atlanta\ext_v\sys_data.h"
#endif

/* Prototype
void	VolumeKeyOperation(void);
UBYTE 	ChangeBuzzerVolume(void)
void 	DisplayHighBuzzerVolume(void)
UBYTE 	ChangeMonitorVolume(void)
void 	DisplayHighMonitorVolume(void)
UBYTE 	SetRingerControl(void)
*/


#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By Y.Kano 2003/08/29 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)/* DVT : mod by SMuratec C.P 2004/09/06 */
/*************************************************************************
	module		:[ボリューム設定オペレーション]
	function	:[
		1.ブザー音量調整を行う
		2.モニター音量調整を行う
		3.リンガー制御設定を行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/05]
	author		:[加納]
*************************************************************************/
void VolumeKeyOperation(void)
{
	UBYTE	key;				/* 入力ｷｰﾃﾞｰﾀ 	*/
	UBYTE	keytype;			/* 入力ｷｰﾀｲﾌﾟ 	*/
	UBYTE	select;				/* 選択ﾌﾗｸﾞ   	*/
	UBYTE	result;

	select = 0x00;				/* ﾌﾞｻﾞｰﾎﾞﾘｭｰﾑ選択をｾｯﾄ */
	result = OK;
	DispChangeFlag = FALSE;

	/* 上段表示 */
	DisplayStringHigh(0, D2W_BuzzerVolume);			/* "01.ﾌﾞｻﾞｰ ｷｰﾀｯﾁ ｵﾝﾘｮｳ" */

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_BuzzerVolumeEnter);	/* "            ←/→/ｾｯﾄ " */

	while(1) {
		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case LEFT_ARROW:	/* 左矢印キー */
			switch(select) {
			case 0x00:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_RingerControl);	/* "03.ﾁｬｸｼﾝ ﾍﾞﾙ        " */
				select = 0x02;								/* ﾓﾆﾀｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			case 0x01:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.ﾌﾞｻﾞｰ､ｷｰﾀｯﾁ ｵﾝﾘｮｳ" */
				select = 0x00;								/* ﾓﾆﾀｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			case 0x02:
			default:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.ﾓﾆﾀｰ ｵﾝﾘｮｳ       " */
				select = 0x01;								/* ﾌﾞｻﾞｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			}
			break;
		case FUNCTION:		/* 機能／＞キー */
		case VOLUME:		/* 音量調整キー */
			switch(select) {
			case 0x00:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.ﾓﾆﾀｰ ｵﾝﾘｮｳ       " */
				select = 0x01;								/* ﾌﾞｻﾞｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			case 0x01:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_RingerControl);	/* "03.ﾁｬｸｼﾝ ﾍﾞﾙ        " */
				select = 0x02;								/* ﾓﾆﾀｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			case 0x02:
			default:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.ﾌﾞｻﾞｰ､ｷｰﾀｯﾁ ｵﾝﾘｮｳ" */
				select = 0x00;								/* ﾓﾆﾀｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			}
			break;
		case ENTER:
			switch(select) {
			case 0x00:
				result = ChangeBuzzerVolume();				/* ﾌﾞｻﾞｰ音量調整 */
				break;
			case 0x01:
				result = ChangeMonitorVolume();				/* ﾓﾆﾀｰ音量調整 */
				break;
			case 0x02:
			default:
				result = SetRingerControl();				/* ﾘﾝｶﾞｰ制御設定 */
				break;
			}
			break;
		case STOP:
		case KEY_TIME_UP:
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
		if (DispChangeFlag) {		/* ボリューム調整中でENTERキー押下された場合、表示切替が必要 */
			DispChangeFlag = FALSE;

			switch(select) {
			case 0x00:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.ﾓﾆﾀｰ ｵﾝﾘｮｳ       " */
				select = 0x01;								/* ﾌﾞｻﾞｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			case 0x01:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_RingerControl);	/* "03.ﾁｬｸｼﾝ ﾍﾞﾙ        " */
				select = 0x02;								/* ﾓﾆﾀｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			case 0x02:
			default:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.ﾌﾞｻﾞｰ､ｷｰﾀｯﾁ ｵﾝﾘｮｳ" */
				select = 0x00;								/* ﾓﾆﾀｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			}
		}
		if (result == NG) {
			return;
		}
	}
}
#else /* (PRO_KEYPANEL == PANEL_STOCKHM2) */
/*************************************************************************
	module		:[ボリューム設定オペレーション]
	function	:[
		1.ブザー音量調整を行う
		2.モニター音量調整を行う
		3.リンガー制御設定を行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/05]
	author		:[加納]
*************************************************************************/
void VolumeKeyOperation(void)
{
	UBYTE	key;				/* 入力ｷｰﾃﾞｰﾀ 	*/
	UBYTE	keytype;			/* 入力ｷｰﾀｲﾌﾟ 	*/
	UBYTE	select;				/* 選択ﾌﾗｸﾞ   	*/
	UBYTE	result;

	select = 0x00;				/* ﾌﾞｻﾞｰﾎﾞﾘｭｰﾑ選択をｾｯﾄ */
	result = OK;
	DispChangeFlag = FALSE;

	/* 上段表示 */
	DisplayStringHigh(0, D2W_BuzzerVolume);			/* "01.ﾌﾞｻﾞｰ ｷｰﾀｯﾁ ｵﾝﾘｮｳ" */

	while(1) {

		/* 下段点滅表示 */
		FlashDisplayStringLow(D2W_ProgramEnter);		/* "            ｷﾉｳ/ｾｯﾄ " */

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case LEFT_ARROW:	/* 左矢印キー */
			switch(select) {
			case 0x00:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.ﾓﾆﾀｰ ｵﾝﾘｮｳ       " */
				select = 0x01;								/* ﾓﾆﾀｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			case 0x01:
			default:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.ﾌﾞｻﾞｰ､ｷｰﾀｯﾁ ｵﾝﾘｮｳ" */
				select = 0x00;								/* ﾓﾆﾀｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			}
			break;
		case FUNCTION:		/* 機能／＞キー */
		case VOLUME:		/* 音量調整キー */
			switch(select) {
			case 0x00:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.ﾓﾆﾀｰ ｵﾝﾘｮｳ       " */
				select = 0x01;								/* ﾌﾞｻﾞｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			case 0x01:
			default:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.ﾌﾞｻﾞｰ､ｷｰﾀｯﾁ ｵﾝﾘｮｳ" */
				select = 0x00;								/* ﾓﾆﾀｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			}
			break;
		case ENTER:
			switch(select) {
			case 0x00:
				result = ChangeBuzzerVolume();				/* ﾌﾞｻﾞｰ音量調整 */
				break;
			case 0x01:
			default:
				result = ChangeMonitorVolume();				/* ﾓﾆﾀｰ音量調整 */
				break;
			}
			break;
		case STOP:
		case KEY_TIME_UP:
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
		if (DispChangeFlag) {		/* ボリューム調整中でENTERキー押下された場合、表示切替が必要 */
			DispChangeFlag = FALSE;

			switch(select) {
			case 0x00:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.ﾓﾆﾀｰ ｵﾝﾘｮｳ       " */
				select = 0x01;								/* ﾌﾞｻﾞｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			case 0x01:
			default:
				/* 上段表示 */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.ﾌﾞｻﾞｰ､ｷｰﾀｯﾁ ｵﾝﾘｮｳ" */
				select = 0x00;								/* ﾓﾆﾀｰﾎﾞﾘｭｰﾑ選択に切換え */
				break;
			}
		}
		if (result == NG) {
			return;
		}
	}
}
#endif 
/*************************************************************************
	module		:[ブザー音量調整]
	function	:[
		1.ブザー音量調整画面表示
		2.ブザー音量調整と同時にブザーも鳴動させる.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/08/29]
	author		:[江口]
*************************************************************************/
UBYTE ChangeBuzzerVolume(void)
{
	UBYTE	key;				/* 入力ｷｰﾃﾞｰﾀ 	*/
	UBYTE	key_type;			/* 入力ｷｰﾀｲﾌﾟ 	*/
	UBYTE	is_loop_end;

	is_loop_end = FALSE;

	/* 上段表示ワーディングのセット */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_ChangeVolume);			/* "  ﾎﾞﾘｭｰﾑ:           " */

	while (is_loop_end == FALSE) {

		SYS_KeyTouchFrequencySetting = 1;	/* キータッチ音色設定オペレーション中判別フラグ */

		/* キーブザーボリューム調整中表示 */
		DisplayHighBuzzerVolume();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		key_type = GetInputKeyType();

		switch (key_type) {
		case FUNCTION:		/* 機能／＞キー */
		case VOLUME:		/* 音量調整キー */
			/* ボリュームアップ */
			if (SYB_BuzzerOutLevel >= KEY_BUZZER_VOLUME_MAX) {	/* ブザー定数変更 by Y.Kano 2003/10/10 */
				SYB_BuzzerOutLevel = KEY_BUZZER_VOLUME_MAX;
/*			if (SYB_BuzzerOutLevel >= BUZZER_VOLUME_MAX) {
				SYB_BuzzerOutLevel = BUZZER_VOLUME_MAX;*/
				NackBuzzer();
			}
			else {
				SYB_BuzzerOutLevel++;

				/* ブザー制御をここでやる。by Y.Kano 2003/09/01 */
				SYS_KeyTouchFrequencySetting = 0;	/* キータッチ音色設定オペレーション中判別フラグ */
				SYS_AckBuzzerFlag = 0;	/* AckBuzzerをONに */
				/** アックブザーを鳴らす */
				AckBuzzer();
			}
			break;
		case LEFT_ARROW:	/* 左矢印キー */
			/* ボリュームダウン */
			if (SYB_BuzzerOutLevel <= KEY_BUZZER_VOLUME_OFF) {	/* ブザー定数変更 by Y.Kano 2003/10/10 */
				SYB_BuzzerOutLevel = KEY_BUZZER_VOLUME_OFF;
/*			if (SYB_BuzzerOutLevel <= BUZZER_VOLUME_OFF) {
				SYB_BuzzerOutLevel = BUZZER_VOLUME_OFF;*/
				NackBuzzer();
			}
			else {
				SYB_BuzzerOutLevel--;

				/* ブザー制御をここでやる。by Y.Kano 2003/09/01 */
				SYS_KeyTouchFrequencySetting = 0;	/* キータッチ音色設定オペレーション中判別フラグ */
				SYS_AckBuzzerFlag = 0;	/* AckBuzzerをONに */
				/** アックブザーを鳴らす */
				AckBuzzer();
			}
			break;
		case NO_EFFECT:
			break;
		case ENTER:
			/* ブザー制御をここでやる。by Y.Kano 2003/09/01 */
			SYS_KeyTouchFrequencySetting = 0;	/* キータッチ音色設定オペレーション中判別フラグ */
			SYS_AckBuzzerFlag = 0;	/* AckBuzzerをONに */
			/** アックブザーを鳴らす */
			AckBuzzer();

			DispChangeFlag = TRUE;
			is_loop_end = TRUE;
			return(OK);
		case STOP:
			/* ブザー制御をここでやる。by Y.Kano 2003/09/01 */
			SYS_KeyTouchFrequencySetting = 0;	/* キータッチ音色設定オペレーション中判別フラグ */
			SYS_AckBuzzerFlag = 0;	/* AckBuzzerをONに */
			/** アックブザーを鳴らす */
			AckBuzzer();

			is_loop_end = TRUE;
			return(NG);
		case KEY_TIME_UP: /* キー待ちタイムオーバー */
			SYS_KeyTouchFrequencySetting = 0;	/* キータッチ音色設定オペレーション中判別フラグ */
			SYS_AckBuzzerFlag = 0;	/* AckBuzzerをONに */
			is_loop_end = TRUE;
			return(NG);
		default:
			NackBuzzer();
			break;
		}
	}
}


/*************************************************************************
	module		:[ブザーボリューム調整中表示]
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
	date		:[2003/08/29]
	author		:[加納]
*************************************************************************/
void DisplayHighBuzzerVolume(void)
{
	/* ボリューム表示変更 by Y.Kano 2003/09/08 */
	CMN_MemorySet(&FunctionDisplayBufferHigh[7], 12, ' ');
/*	CMN_MemorySet(&FunctionDisplayBufferHigh[9], 6, ' ');*/

	switch (SYB_BuzzerOutLevel) {
	case KEY_BUZZER_VOLUME_OFF:		/* ボリューム OFF 	*/ /* ブザー定数変更 by Y.Kano 2003/10/10 */
/*	case BUZZER_VOLUME_OFF:*/		/* ボリューム OFF 	*/
		break;
	case KEY_BUZZER_VOLUME_MIN:		/* ボリューム小		*/ /* ブザー定数変更 by Y.Kano 2003/10/10 */
/*	case BUZZER_VOLUME_MIN:*/		/* ボリューム小		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		break;
	case KEY_BUZZER_VOLUME_MID:		/* ボリューム中		*/ /* ブザー定数変更 by Y.Kano 2003/10/10 */
/*	case BUZZER_VOLUME_MID:*/		/* ボリューム中		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		FunctionDisplayBufferHigh[11] = 0x2B;
		FunctionDisplayBufferHigh[12] = 0x2B;
		FunctionDisplayBufferHigh[13] = 0x2B;
		FunctionDisplayBufferHigh[14] = 0x2B;
		break;
	case KEY_BUZZER_VOLUME_MAX:		/* ボリューム大		*/ /* ブザー定数変更 by Y.Kano 2003/10/10 */
/*	case BUZZER_VOLUME_MAX:*/		/* ボリューム大		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++++++++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		FunctionDisplayBufferHigh[11] = 0x2B;
		FunctionDisplayBufferHigh[12] = 0x2B;
		FunctionDisplayBufferHigh[13] = 0x2B;
		FunctionDisplayBufferHigh[14] = 0x2B;
		FunctionDisplayBufferHigh[15] = 0x2B;
		FunctionDisplayBufferHigh[16] = 0x2B;
		FunctionDisplayBufferHigh[17] = 0x2B;
		FunctionDisplayBufferHigh[18] = 0x2B;
		break;
	default:
		break;
	}
	/* 上段表示 */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

 #if defined(STOCKHM2) /* DVT : Mod by SMuratec C.P 2004/09/06 */
	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_BuzzerVolumeEnter);	/* "            ←/→/ｾｯﾄ " */
 #endif


}

/*************************************************************************
	module		:[モニター音量調整]
	function	:[
		1.モニター音量調整画面表示
		2.上段表示のみ更新する.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/08/29]
	author		:[江口]
*************************************************************************/
UBYTE ChangeMonitorVolume(void)
{
	UBYTE	key;				/* 入力ｷｰﾃﾞｰﾀ 	*/
	UBYTE	key_type;			/* 入力ｷｰﾀｲﾌﾟ 	*/
	UBYTE	is_loop_end;

	is_loop_end = FALSE;

	/* 上段表示ワーディングのセット */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_ChangeVolume);			/* "  ﾎﾞﾘｭｰﾑ:           " */

	while (is_loop_end == FALSE) {

		/* スピーカーボリューム調整中表示 */
		DisplayHighMonitorVolume();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		key_type = GetInputKeyType();

		switch (key_type) {
		case FUNCTION:		/* 機能／＞キー */
		case VOLUME:		/* 音量調整キー */
			/* ボリュームアップ */
			if (SYB_MonitorSpeakerOutLevel == SYS_VOLUME_MAXIMUM) {
				NackBuzzer();
			}
			else {
				SYB_MonitorSpeakerOutLevel++;
			}
			break;
		case LEFT_ARROW:	/* 左矢印キー */
			/* ボリュームダウン */
			if (SYB_MonitorSpeakerOutLevel == SYS_VOLUME_OFF) {
				NackBuzzer();
			}
			else {
				SYB_MonitorSpeakerOutLevel--;
			}
			break;
		case NO_EFFECT:
			break;
		case ENTER:
			DispChangeFlag = TRUE;
			is_loop_end = TRUE;
			return(OK);
		case STOP:
		case KEY_TIME_UP: /* キー待ちタイムオーバー */
			is_loop_end = TRUE;
			return(NG);

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[モニターボリューム調整中表示]
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
	date		:[2003/08/29]
	author		:[加納]
*************************************************************************/
void DisplayHighMonitorVolume(void)
{
	CMN_MemorySet(&FunctionDisplayBufferHigh[7], 12, ' ');

	switch (SYB_MonitorSpeakerOutLevel) {
	case SYS_VOLUME_OFF:		/* ボリュームOFF	*/
		break;
	case SYS_VOLUME_MINIMUM:	/* ボリューム小		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		break;
	case SYS_VOLUME_MIDDLE:		/* ボリューム中		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		FunctionDisplayBufferHigh[11] = 0x2B;
		FunctionDisplayBufferHigh[12] = 0x2B;
		FunctionDisplayBufferHigh[13] = 0x2B;
		FunctionDisplayBufferHigh[14] = 0x2B;
		break;
	case SYS_VOLUME_MAXIMUM:	/* ボリューム大		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++++++++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		FunctionDisplayBufferHigh[11] = 0x2B;
		FunctionDisplayBufferHigh[12] = 0x2B;
		FunctionDisplayBufferHigh[13] = 0x2B;
		FunctionDisplayBufferHigh[14] = 0x2B;
		FunctionDisplayBufferHigh[15] = 0x2B;
		FunctionDisplayBufferHigh[16] = 0x2B;
		FunctionDisplayBufferHigh[17] = 0x2B;
		FunctionDisplayBufferHigh[18] = 0x2B;
		break;
	default:
		break;
	}
	/* 上段表示 */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

 #if defined(STOCKHM2) /* DVT : Mod by SMuratec C.P 2004/09/06 */
	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_BuzzerVolumeEnter);	/* "            ←/→/ｾｯﾄ " */
 #endif
}

/*************************************************************************
	module		:[リンガー制御設定]
	function	:[
		1.リンガー制御設定画面表示
		2.機能キーでリンガーON/OFFの選択。
		3.SETキーでリンガー制御設定。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/09/18]
	author		:[加納義彦]
*************************************************************************/
UBYTE SetRingerControl(void)
{
	UBYTE	key;				/* 入力ｷｰﾃﾞｰﾀ 	*/
	UBYTE	key_type;			/* 入力ｷｰﾀｲﾌﾟ 	*/
	UBYTE	is_loop_end;

	is_loop_end = FALSE;

	/* 上段表示ワーディングのセット */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	if (SYB_RingOut) {
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_RingerControlOn);		/* "ﾁｬｸｼﾝ ﾍﾞﾙ  : ON     " */
	}
	else {
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_RingerControlOff);	/* "ﾁｬｸｼﾝ ﾍﾞﾙ  : OFF    " */
	}
	/* 上段表示 */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	while (is_loop_end == FALSE) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		key_type = GetInputKeyType();

		switch (key_type) {
		case FUNCTION:		/* 機能／＞キー */
		case LEFT_ARROW:	/* 左矢印キー */
		case VOLUME:		/* 音量調整キー */
			/* ON→OFF、OFF→ON */
			if (SYB_RingOut) {
				CMN_StringCopy(FunctionDisplayBufferHigh, D2W_RingerControlOff);	/* "ﾁｬｸｼﾝ ﾍﾞﾙ  : OFF    " */
				/* 上段表示 */
				DisplayStringHigh(0, FunctionDisplayBufferHigh);
				SYB_RingOut = FALSE;
			}
			else {
				CMN_StringCopy(FunctionDisplayBufferHigh, D2W_RingerControlOn);		/* "ﾁｬｸｼﾝ ﾍﾞﾙ  : ON     " */
				/* 上段表示 */
				DisplayStringHigh(0, FunctionDisplayBufferHigh);
				SYB_RingOut = TRUE;
			}
			break;
		case NO_EFFECT:
			break;
		case ENTER:
			if (SYB_RingOut) {
				RingerControlSet();		/* リンガー制御ＯＮ 	*/
			}
			else {
				RingerControlReset();	/* リンガー制御ＯＦＦ 	*/
			}
			DispChangeFlag = TRUE;
			is_loop_end = TRUE;
			return(OK);
		case STOP:
		case KEY_TIME_UP: /* キー待ちタイムオーバー */
			is_loop_end = TRUE;
			return(NG);

		default:
			NackBuzzer();
			break;
		}
	}
}



#endif
