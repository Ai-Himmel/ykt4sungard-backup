/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANTA																	*/
/*		ﾓｼﾞｭｰﾙ	:UBYTE CNG_ToneDetect(void)									*/
/*				:void CNG_ToneDetectTaskExit(void)											*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_CNG.Cを流用しました										*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\ctry_pro.h"	/* CTRY_?Tone() */
#include	"\src\atlanta\define\mon_pro.h"	/* モニタコール	 */

#if (PRO_MODEM == R288F) /* Changed by H.Kubo 1997/07/19 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"	/* MDM_FilterSet() */
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"	/* MDM_FilterSet() */
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == ORANGE3)
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"	/* MDM_FilterSet() */
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"	/* MDM_FilterSet() */
#endif

#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
/*#include	"\src\memsw\define\mem_sw_g.h" @* 1994.11.28 M.H. 1996/04/17 Eguchi*/

#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\define\message.h"

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/06 */

#include	"\src\atlanta\sh7043\define\def_tib.h"

#include	"\src\atlanta\ext_v\atd_tbl.h"
#include	"\src\atlanta\ext_v\atd_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\bkupram.h"	/* Add by T.Nose 1995/12/14 */
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/10 */
#include	"\src\atlanta\ext_v\fcm_data.h"
 #endif
#endif
#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 *//* Add By O.Kimoto 2002/03/11 */
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\ncu_data.h"
#endif

/*************************************************************************
	module		:[CNG検出]
	function	:[
		1.CNGトーン検出
		2.検出したトーン、事象に対する値をリターン
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[
		TONE_DET_OK			:CNGトーンを検出した
		TONE_DET_TIMEUP		:トーン検出制限時間オーバー
		TONE_DET_BUSY		:BUSYトーンを検出した 1998/03/11  By T.Yamaguchi
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/6]
	author		:[原田　学]
	履歴		:cng検出中ｏｎの後次のｏｎがこないときタスクが殺されないバグ
				:タイマタスクをクリエートして殺すようにした Ｂｙ Ｔ．Ｙ
*************************************************************************/
/*-----------------------------------------------*/
/*CNGﾄｰﾝを検出，ﾄｰﾝの有無FaxTelAutoSwitch()にﾘﾀｰﾝ*/
/*-----------------------------------------------*/
UBYTE	CNG_ToneDetect(void)
{

	MESSAGE_t		*ad_receive;			/*rcv_msg()で受信データをｾｯﾄする*/

	struct	Timer10msData_t	TimeUp;
	struct	Timer10msData_t	DetectingTimeUp;	/* CNG検出中のﾀｲﾑｱｯﾌﾟ add By Ｔ．Ｙ'96.04.02 */
	struct	ToneDetectMailBoxData_t	CNG_ToneDetectMailBox;
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
	struct	ToneDetectMailBoxData_t Busy_ToneDetectMailBox;
#endif
#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	struct	ToneDetectMailBoxData_t Busy_ToneDetectMailBox;
#endif

	UWORD message = 0;
	UBYTE ring_time_up = 0;
	UBYTE time_up_cnt = 0;		/* Add by TH92115 1996/01/25 */

#if (PRO_MODEM == ORANGE3)
	UBYTE tone_detect_type;

	tone_detect_type = CNG_DETECT;

	tskno_cng_freq_check = 0xffff;
#endif
	tskno_cng_detect = 0xffff;
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */

 #if (PRO_MODEM == ORANGE3)	/* add #if 1999/09/28 Y.Murata */
	tone_detect_type = CNG_BUSY_DETECT;
 #endif
	tskno_busy_detect = 0xffff;
#endif

#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	tskno_busy_detect = 0xffff;
#endif

/*	tskno_cng_timeup = 0xffff;	*/
/*	tskno_cng_det_timeup = 0xffff;		@ Add By T.Y 96.04.02 */
	tskno_cng_timeup = 0xff;
	tskno_cng_det_timeup = 0xff;		/* Add By T.Y 96.04.02 */

	SYS_RingToneStopFlag = 0;

	/*------------------------------*/
	/*ﾌｨﾙﾀｰのﾄｰﾝ周波数検出範囲を設定*/
	/*------------------------------*/
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
 /* #if defined(POPLAR_F) */
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Mod. by J.Kishida 2002/09/05 */

#if (0)	/* NTT仕様で音声応答中のBusyTone検出の可否スイッチ対応 By O.Kimoto 2003/12/01 */
** 	MDM_FilterSet(CNG_BUSY_FILTER);		/* 2000/02/02 Y.Murata */
#else
	if (CHK_UNI_IgnoreBusyTone()) {
		/* BusyToneは検出しない！！*/
		MDM_FilterSet(CNG_FILTER);
	}
	else {
		/* BusyToneは検出する！！*/
		MDM_FilterSet(CNG_BUSY_FILTER);
	}
#endif

 #else
	MDM_FilterSet(CNG_FILTER);	/* CNG_BT_FILTERやったら誤検出してしまう。*/
 #endif
#else
 #if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
#if(0)	/* 擬似リングを1回鳴らしてからのBT検出に対応。BT_DELAY O.Oshima 2001/12/21 *//* Add By O.Kimoto 2002/03/11 */
** 	MDM_FilterSet(CNG_BUSY_FILTER);
#else
	if (IsDetectBusyTone) {
		MDM_FilterSet(CNG_BUSY_FILTER);
	}
	else {
		MDM_FilterSet(CNG_FILTER);
	}
#endif
 #else
	MDM_FilterSet(CNG_FILTER);
 #endif
#endif

	for (;;) {
		/*------------------*/
		/*ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
		/*------------------*/
		if( SYS_FaxTelTimeUpTimeFlag ){			/* add by HARADA '94/9/9 */
			ring_time_up = CHK_UNI_RingBackToneWaitTime();	/* ANZU個別のﾒﾓﾘｽｲｯﾁ */
			switch(ring_time_up){
				case 1:
					TimeUp.Time = 330;
					break;
				case 2:
					TimeUp.Time = 360;
					break;
				case 3:
					TimeUp.Time = 390;
					break;
				case 0:
				default:
					TimeUp.Time = 300;
					break;
			}
			SYS_FaxTelTimeUpTimeFlag = 0;
		}
		else{
#if (0)/*By Y.Suzuki 1998/09/21*/
//#if defined(SWE)							/* add by M.HARADA 95.07.07 */
//			TimeUp.Time			= 500;		/* 擬似ベルOff時間　5sec */
//#else
//			TimeUp.Time			= CNG_Tone.MaxDetectTime;	/* 1.8sec */
#endif
			TimeUp.Time			= CNG_Tone.MaxDetectTime;	/* 1.8sec */
		}
		TimeUp.SendMBX		= mbxno.NCU_TransRBTAndDetCNGTask;
		TimeUp.ReturnValue	= TIMEUP;
/*		cre_tsk(&tskno_cng_timeup, TSK_CMN_MAN_TIMER10MSTASK, &TimeUp);	*/
		CMN_MultiTimer10msStart(&tskno_cng_timeup, &TimeUp);
		/*-------------------*/
		/*CNGﾄｰﾝ検出ﾀｽｸ生成*/
		/*-------------------*/
		SYS_RingSignalStopFlag = 1;
		if (tskno_cng_detect == 0xFFFF) {
			CNG_ToneDetectMailBox.ToneType = CNG_TONE;
			CNG_ToneDetectMailBox.SendMBX = mbxno.NCU_TransRBTAndDetCNGTask;
			cre_tsk(&tskno_cng_detect, TSK_ATD_TONEDETECTPATTERN1TASK, &CNG_ToneDetectMailBox);
		}
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
		/*-------------------*/
		/*BUSYﾄｰﾝ検出ﾀｽｸ生成*/
		/*-------------------*/
	/* #if defined(POPLAR_F) */
	#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Mod. by J.Kishida 2002/09/05 */

#if (0)
** 		/* 擬似ベル鳴動中のBusyTone検出処理追加 By O.Kimoto 2002/11/01 */
** 		if (CMN_CheckAnswerEnable()) {
** 			SYS_RingSignalStopFlag = 1;
** 			if (tskno_busy_detect == 0xFFFF) {
** 				/* PhaseB1時のBUSYトーンはON/OFF/ON/OFF検出 */
** 				Busy_ToneDetectMailBox.ToneType = PHA1_BUSY;
** 				Busy_ToneDetectMailBox.SendMBX = mbxno.NCU_TransRBTAndDetCNGTask;
** 				cre_tsk(&tskno_busy_detect, TSK_ATD_TONEDETECTPATTERN1TASK, &Busy_ToneDetectMailBox);
** 			}
** 		}
#else
#if (0)	/* NTT仕様で音声応答中のBusyTone検出の可否スイッチ対応 By O.Kimoto 2003/12/01 */
** 		SYS_RingSignalStopFlag = 1;
** 		if (tskno_busy_detect == 0xFFFF) {
** 			/* PhaseB1時のBUSYトーンはON/OFF/ON/OFF検出 */
** 			Busy_ToneDetectMailBox.ToneType = PHA1_BUSY;
** 			Busy_ToneDetectMailBox.SendMBX = mbxno.NCU_TransRBTAndDetCNGTask;
** 			cre_tsk(&tskno_busy_detect, TSK_ATD_TONEDETECTPATTERN1TASK, &Busy_ToneDetectMailBox);
** 		}
#else
		if (!CHK_UNI_IgnoreBusyTone()) {
			SYS_RingSignalStopFlag = 1;
			if (tskno_busy_detect == 0xFFFF) {
				/* PhaseB1時のBUSYトーンはON/OFF/ON/OFF検出 */
				Busy_ToneDetectMailBox.ToneType = PHA1_BUSY;
				Busy_ToneDetectMailBox.SendMBX = mbxno.NCU_TransRBTAndDetCNGTask;
				cre_tsk(&tskno_busy_detect, TSK_ATD_TONEDETECTPATTERN1TASK, &Busy_ToneDetectMailBox);
			}
		}
#endif
#endif

	#else
		/* 上記メモリスイッチ対応がいるかも・・・動作確認終了後実装すること！！！ By O.Kimoto 2003/12/01 */*/
		SYS_RingSignalStopFlag = 1;
		if (tskno_busy_detect == 0xFFFF) {
			/* PhaseB1時のBUSYトーンはON/OFF/ON/OFF検出 */
			Busy_ToneDetectMailBox.ToneType = PHB1_BUSY;
			Busy_ToneDetectMailBox.SendMBX = mbxno.NCU_TransRBTAndDetCNGTask;
			cre_tsk(&tskno_busy_detect, TSK_ATD_TONEDETECTPATTERN1TASK, &Busy_ToneDetectMailBox);
		}
	#endif
#endif

#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
#if (0)	/* Add By O.Kimoto 2002/03/11 */
** 		if (tskno_busy_detect == 0xFFFF) {
** 			Busy_ToneDetectMailBox.ToneType = PHA1_BUSY;
** 			Busy_ToneDetectMailBox.SendMBX = mbxno.NCU_TransRBTAndDetCNGTask;
** 			cre_tsk(&tskno_busy_detect, TSK_ATD_TONEDETECTPATTERN1TASK, &Busy_ToneDetectMailBox);
** 		}
#else
  		/* 擬似リングを1回鳴らしてからのBT検出に対応。BT_DELAY O.Oshima 2001/12/21 *//* Add By O.Kimoto 2002/03/11 */
		if ((IsDetectBusyTone && CHK_UNI_DetectBusySameTime()) /* 擬似ベルを待たない */
			||  (IsDetectBusyTone && IsTelFaxRingSend)){ /* 鳴ってから検出開始 */
			if (tskno_busy_detect == 0xFFFF) {
				Busy_ToneDetectMailBox.ToneType = PHA1_BUSY;
				Busy_ToneDetectMailBox.SendMBX = mbxno.NCU_TransRBTAndDetCNGTask;
				cre_tsk(&tskno_busy_detect, TSK_ATD_TONEDETECTPATTERN1TASK, &Busy_ToneDetectMailBox);
			}
		}
#endif
#endif
		/*-------------------------------------*/
		/*	Frequency check Only Orange3 Modem */
		/*-------------------------------------*/
#if (PRO_MODEM == ORANGE3)
		if (tskno_cng_freq_check == 0xFFFF) {
			cre_tsk(&tskno_cng_freq_check, TSK_ATD_FILTERONOFFDETECTTASK, &tone_detect_type);
		}
#endif
		/*----------*/
		/*ﾒｯｾｰｼﾞ受信*/
		/*----------*/
		rcv_msg(mbxno.NCU_TransRBTAndDetCNGTask, &ad_receive);
		/*------------------*/
		/*ﾒｯｾｰｼﾞに対する処理*/
		/*------------------*/
		message = ad_receive->Message;
		SpeedToneOnTime = message;	/* for Debag */
		if (message == CNG_TONE) {
			/*--------------------------*/
			/*ﾄｰﾝ検出で使用したﾀｽｸを削除*/
			/*--------------------------*/
			CNG_ToneDetectTaskExit();
			SYS_RingSignalStopFlag = 0;		/* クリアしても良いのか要確認 '96.04.01 */
			return(TONE_DET_OK);
		}
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/03  By T.Yamaguchi */
	/* #if defined(POPLAR_F) */
	#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Mod. by J.Kishida 2002/09/05 */
		else if (message == PHA1_BUSY) {
			/*--------------------------*/
			/*ﾄｰﾝ検出で使用したﾀｽｸを削除*/
			/*--------------------------*/
			CNG_ToneDetectTaskExit();
			SYS_RingSignalStopFlag = 0;		/* クリアしても良いのか要確認 '96.04.01 */
			return(TONE_DET_BUSY);
		}
	#else
		else if (message == PHB1_BUSY) {
			/*--------------------------*/
			/*ﾄｰﾝ検出で使用したﾀｽｸを削除*/
			/*--------------------------*/
			CNG_ToneDetectTaskExit();
			SYS_RingSignalStopFlag = 0;		/* クリアしても良いのか要確認 '96.04.01 */
			return(TONE_DET_BUSY);
		}
	#endif
#endif

#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
		else if (message == PHA1_BUSY) {
			/*--------------------------*/
			/*ﾄｰﾝ検出で使用したﾀｽｸを削除*/
			/*--------------------------*/
			CNG_ToneDetectTaskExit();
			SYS_RingSignalStopFlag = 0;		/* クリアしても良いのか要確認 '96.04.01 */
			return(TONE_DET_BUSY);
		}
#endif

		else if (message == TIMEUP) {
			if(!SYS_RingToneStopFlag){
				/*--------------------------*/
				/*ﾄｰﾝ検出で使用したﾀｽｸを削除*/
				/*--------------------------*/
				CNG_ToneDetectTaskExit();
				SYS_RingSignalStopFlag = 0;
				return(TONE_DET_TIMEUP);
			}
			else {
/*				if (tskno_cng_timeup != 0xFFFF) {1996/12/12	 By T.Yamaguchi	*/
				if (tskno_cng_timeup != 0xFF) {
					CMN_MultiTimer10msStop(&tskno_cng_timeup);
/*					del_tsk(&tskno_cng_timeup);	*/
				}
/*				if (tskno_cng_det_timeup == 0xffff) {	1996/12/12	By T.Yamaguchi */
				if (tskno_cng_det_timeup == 0xff) {
					DetectingTimeUp.Time		= 450;		/* CNG_MAX_Off時間　4.5sec */
					DetectingTimeUp.SendMBX		= mbxno.NCU_TransRBTAndDetCNGTask;
					DetectingTimeUp.ReturnValue	= DET_TIMEUP;
/*					CMN_MultiTimer10msStart(&tskno_cng_det_timeup, &TimeUp); */ /* 引数が間違い。 Fixed by H.Kubo 1998/05/22 */
					CMN_MultiTimer10msStart(&tskno_cng_det_timeup, &DetectingTimeUp);
/*					cre_tsk(&tskno_cng_det_timeup , TSK_CMN_MAN_TIMER10MSTASK, &DetectingTimeUp);	*/
				}
			}
		}
		else if (message == DET_TIMEUP) {	/* detecting_timeup */
			/*-----------------------------------------------------------*/
			/** トーン検出途中であっても、タイムアウトで検出を中断します */
			/*-----------------------------------------------------------*/
			CNG_ToneDetectTaskExit();	/* 次のON-OFFを検出するまで最高４秒かかる */
			SYS_RingSignalStopFlag = 0;
			return(TONE_DET_TIMEUP);
		}
	}
}

/*--------------------------*/
/*CNG検出で生成したﾀｽｸを削除*/
/*--------------------------*/
void	CNG_ToneDetectTaskExit(void)
{
	if (tskno_cng_detect != 0xFFFF) {
		del_tsk(&tskno_cng_detect);
	}
/*	if (tskno_cng_timeup != 0xFFFF) {1996/12/12	 By T.Yamaguchi	*/
	if (tskno_cng_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_cng_timeup);
/*		del_tsk(&tskno_cng_timeup);	*/
	}
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
	if (tskno_busy_detect != 0xFFFF) {
		del_tsk(&tskno_busy_detect);
	}
#endif
#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	if (tskno_busy_detect != 0xFFFF) {
		del_tsk(&tskno_busy_detect);
	}
#endif
#if (PRO_MODEM == ORANGE3)
	if (tskno_cng_freq_check != 0xFFFF) {
		del_tsk(&tskno_cng_freq_check);
	}
#endif
/*	if (tskno_cng_det_timeup != 0xFFFF) {		*/
	if (tskno_cng_det_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_cng_det_timeup);
/*		del_tsk(&tskno_cng_det_timeup);	*/
	}
}


#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
/*************************************************************************
	module		:[BUSY検出]
	function	:[
		1.BUSYトーン/フラグ検出
		2.検出したトーン、事象に対する値をリターン
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[
		BUSY_TONE_DET_OK	:BUSYトーンを検出した
		TONE_FLAG_DETECT	:フラグを検出した
		TONE_DET_TIMEUP		:トーン検出制限時間オーバー
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[ATD]
	date		:[1998/03/11]
	author		:[山口]
	履歴		:ＮＴＴ仕様でフェーズＢ１の時に、ＢＵＳＹトーンを検出しなければならない
				:ので、ＤＩＳ送出後ＢＵＳＹとＦｌａｇを検出しに行く
				:Ｆｌａｇ検出で、ＦＳＫ受信に行く
*************************************************************************/
UBYTE	Busy_ToneDetect(void)
{
	MESSAGE_t		*ad_receive;					/*	rcv_msg()で受信データをｾｯﾄする*/
	UWORD		ad_message = 0;
	UBYTE		return_value = 0xFF;			/*	ﾄｰﾝ検出結果	*/

	struct	Timer10msData_t	TimeUp;
	struct	ToneDetectMailBoxData_t	BusyToneDetectMailBox;
	struct	ToneDetectMailBoxData_t	DisToneDetectMailBox;

	UWORD tskno_busy_tone;
	UWORD tskno_dis_tone;
	UWORD tskno_busy_freq_check;
	UBYTE tskno_timeup;

 #if (PRO_MODEM == ORANGE3)
	UBYTE	tone_detect_type;
	tone_detect_type = FSK_OR_BUSY_DETECT;
	tskno_busy_freq_check = 0xffff;
 #endif
	tskno_busy_tone = 0xffff;
	tskno_dis_tone = 0xffff;
	tskno_timeup = 0xff;

	CNG_StopFlag = 0;		/*CNG送出:0	   CNG停止:1*/

 /* #if defined(POPLAR_F) */
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Mod. by J.Kishida 2002/09/05 */
	MDM_ToneModeConfig();
	MDM_FilterSet(AFTER_DIAL_FILTER);
 #else
	/*------------------------------*/
	/*ﾌｨﾙﾀｰのﾄｰﾝ周波数検出範囲を設定*/
	/*------------------------------*/
	MDM_FilterSet(AFTER_DIAL_FILTER);
 #endif

	/*------------------*/
	/*ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
	/*------------------*/
	if (tskno_timeup == 0xFF) {
		TimeUp.Time = 300;	/*着信検出時間 3s*/
		TimeUp.SendMBX		= mbxno.FCM_BusyToneDetect;
		TimeUp.ReturnValue	= TIMEUP;
		CMN_MultiTimer10msStart(&tskno_timeup, &TimeUp);
	}

#if (0)	/* NTT仕様で音声応答中のBusyTone検出の可否スイッチ対応 By O.Kimoto 2003/12/01 */
** 	/*-------------------*/
** 	/*ﾋﾞｼﾞ-ﾄｰﾝ検出ﾀｽｸ生成*/
** 	/*-------------------*/
** 	if (tskno_busy_tone == 0xFFFF) {
** 		BusyToneDetectMailBox.ToneType = PHB1_BUSY;
** 		BusyToneDetectMailBox.SendMBX = mbxno.FCM_BusyToneDetect;
** 		/* PhaseB1時のBUSYトーンはON/OFF/ON/OFF検出 */
** 		cre_tsk(&tskno_busy_tone, TSK_ATD_TONEDETECTPATTERN1TASK, &BusyToneDetectMailBox);
** 	}
#else
	/*-------------------*/
	/*ﾋﾞｼﾞ-ﾄｰﾝ検出ﾀｽｸ生成*/
	/*-------------------*/
	if (!CHK_UNI_IgnoreBusyTone()) {
		if (tskno_busy_tone == 0xFFFF) {
			BusyToneDetectMailBox.ToneType = PHB1_BUSY;
			BusyToneDetectMailBox.SendMBX = mbxno.FCM_BusyToneDetect;
			/* PhaseB1時のBUSYトーンはON/OFF/ON/OFF検出 */
			cre_tsk(&tskno_busy_tone, TSK_ATD_TONEDETECTPATTERN1TASK, &BusyToneDetectMailBox);
		}
	}
#endif

	/*-----------------*/
	/*DISﾄｰﾝ検出ﾀｽｸ生成*/
	/*-----------------*/
	if (tskno_dis_tone == 0xFFFF) {
		DisToneDetectMailBox.ToneType = DIS_TONE;
		DisToneDetectMailBox.SendMBX = mbxno.FCM_BusyToneDetect;
		cre_tsk(&tskno_dis_tone, TSK_ATD_TONEDETECTPATTERN0TASK, &DisToneDetectMailBox);
	}
	/*-------------------------------------*/
	/*	Frequency check Only Orange3 Modem */
	/*-------------------------------------*/
 #if (PRO_MODEM == ORANGE3)
	if (tskno_busy_freq_check == 0xFFFF) {
		cre_tsk(&tskno_busy_freq_check, TSK_ATD_FILTERONOFFDETECTTASK, &tone_detect_type);
	}
 #endif

	/*----------*/
	/*ﾒｯｾｰｼﾞ受信*/
	/*----------*/
	if (SYS_PhaseB1Flag) {	/* TEL/FAX待機中のFaseB1でのBUSY検出時 */	/* NTT BUSY検出 */
		SYS_Busy_detecting = 1;
		rcv_msg(mbxno.FCM_BusyToneDetect, &ad_receive);
		SYS_Busy_detecting = 0;
	}
	else {
		rcv_msg(mbxno.FCM_BusyToneDetect, &ad_receive);
	}
	ad_message = ad_receive->Message;

	/*------------------*/
	/*ﾒｯｾｰｼﾞに対する処理*/
	/*------------------*/
	switch (ad_message) {
	case	PHB1_BUSY:
		return_value = BUSY_TONE_DET_OK;
		break;
	case	TIMEUP:
	case	BUSY_DETECT_STOP:	/* TEL1/TEL2のOH検出 */
		return_value = DETECT_TIMEUP;
		break;
	case	DIS_TONE:	/* DIS */
		return_value = TONE_FLAG_DETECT;
 /* #if defined(POPLAR_F) */
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Mod. by J.Kishida 2002/09/05 */
		FCM_DetectFSK = 1;
 #endif
		break;
	}
	/*--------------------------------*/
	/*return_valueに値がｾｯﾄされていたら*/
	/*--------------------------------*/
 #if (PRO_MODEM == ORANGE3)
	if (tskno_busy_freq_check != 0xFFFF) {
		del_tsk(&tskno_busy_freq_check);
	}
 #endif
	if (tskno_busy_tone != 0xFFFF) {
		del_tsk(&tskno_busy_tone);
	}
	if (tskno_dis_tone != 0xFFFF) {
		del_tsk(&tskno_dis_tone);
	}
	if (tskno_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_timeup);
	}
	return(return_value);
}
#endif
