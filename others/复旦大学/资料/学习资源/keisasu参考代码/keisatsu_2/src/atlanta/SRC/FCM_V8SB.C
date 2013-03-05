/*---------------------------------------------------------------------------*/
/*  プロジェクト : Jun/CLOVER                                                */
/*  ファイル名   : FCM_V8SB.C                                                */
/*  モジュール   :                                                           */
/*               : FCM_AfterToneCheck()                                      */
/*               : FCM_AfterToneCheckDelTask()                               */
/*  作成者       : 村田                                                      */
/*  日  付       : 1996/03/21                                                */
/*  概  要       : ＦＡＸ通信モジュール                                      */
/*               :                                                           */
/*  修正履歴     :                                                           */
/*               : 1996/10/04 ﾎﾟｰﾘﾝｸﾞ受信した時、相手機にﾎﾟｰﾘﾝｸﾞ原稿が無い時 */
/*               :            のｼﾞｬｰﾅﾙの通番がおかしくなる                   */
/*               : 1997/08/08 POPLAR_H に移植 by H.Kubo                      */
/*---------------------------------------------------------------------------*/

#include "\src\atlanta\define\product.h"
#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/08 */

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\atd_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\man_pro.h"		/* 1996/08/27 */

#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\define\fcm_def.h"
/* #include "\src\atlanta\define\sys_spd.h"*/
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\cmn_def.h"		/* 1996/09/19 */

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\atd_data.h"

/* #include "\src\atlanta\define\sys_pro.h"	/* test 1996/08/19 */

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/07 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\r288f\define\mdm_io.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\define\mdm_io.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#include "\src\atlanta\mdm\pana\ext_v\mdmudata.h"
#endif


static UWORD tskno_ced_tsk = 0;
static UWORD tskno_dis_tsk = 0;
static UWORD tskno_timeup_tsk = 0;
static UWORD tskno_cngoff_timeup_tsk = 0;
static UWORD tskno_stop_tsk = 0;
static UWORD tskno_tonekeep_timeup_tsk = 0;
static UWORD tskno_answer_tone_tsk = 0;
static UWORD tskno_bt_tsk = 0; /* by H.Kubo 1998/01/09 */

/*************************************************************************
	module		:[CNG TX or Detect2100Hz DetectDIS_Tone]
	function	:[
		1. Be called Before V8 Mode
	]
	commom		:[
			CED Tone Detect Time = 300ms, because into V8 Mode
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53]
	language	:[MS-C(Ver6.0)]
	keyword		:[FCM]
	date		:[1996/03/21]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_AfterToneCheck(void)
{
	MESSAGE_t		*receive;					/*	rcv_msg()で受信データをｾｯﾄする*/
	struct	Timer10msData_t			TimeUp;
	struct	Timer10msData_t			CNG_OFF_TimeUp;
	struct	Timer10msData_t			ToneKeepTimeUp;
	struct	ToneDetectMailBoxData_t	DisToneDetectMailBox;
#if 0 /* Deleted by H.Kubo 1997/08/08 */
//	struct	ToneDetectMailBoxData_t	CedToneDetectMailBox;
#endif /* 0 */
	WORD			message;
	UBYTE 	ReturnValue;			/*	ﾄｰﾝ検出結果	*/
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1998/01/08 */
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
	struct	ToneDetectMailBoxData_t	BusyToneDetectMailBox; /* 1998/01/09 */
	UBYTE	filter_type;

	/*	filter_type = FSK_FILTER; */ /* 後ろに移します。 by H.Kubo 1998/05/21 */
#endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */


#if (PRO_MODEM == MN195006)	/* 松下モデム評価用 *//* 2002/01/25 K.Doukuni */
	UBYTE	debug1_start;
	UBYTE	debug2_start;
	UBYTE	debug_end;
	UBYTE	debug_memorize1;
	UBYTE	debug_memorize2;
	UBYTE	debug_memorize3;
	UBYTE	debug_memorize4;
	UBYTE	debug_memorize5;
#endif

	tskno_ced_tsk = 0xFFFF;
	tskno_dis_tsk = 0xFFFF;
	tskno_timeup_tsk = 0xFFFF;
	tskno_cngoff_timeup_tsk = 0xFFFF;
	tskno_stop_tsk = 0xFFFF;
	tskno_tonekeep_timeup_tsk = 0xFFFF;
	tskno_answer_tone_tsk = 0xFFFF;
	tskno_bt_tsk = 0xFFFF;  /* by H.Kubo 1998/01/09 */

	CNG_StopFlag = 0;		/*CNG送出:0	   CNG停止:1*/
	ReturnValue = 0xFF;
	message = 0;

	/* 極反検出後に検出されたトーンの種類を記録する。*/
	FCM_ToneAfterDetectDCE = AD_NOT_YET_DETECTED; /* added by H.Kubo 1997/11/29 */


	SYS_V8DetectATV25Flag = 0;	/** V25 Answer Tone Flag */ /* 1996/05/10 ﾓﾃﾞﾑ初期化時に一瞬[ATV25] Bitがたつためここでｸﾙｱする */
	ToneDetectTaskInitial();	/** ATDタスクIDの初期化 */

#if (0) /* for ループの中でやっている。 deleted by H.Kubo 1997/11/29 */
@@	MDM_FilterSet(FSK_FILTER);	/* T.B.D detect CED ? */
#endif /* (0) */
	for (;;) {
		FaxTransmit1080Hz();

#if (PRO_MODEM == MN195006)	/* 松下モデム評価用 *//* 2002/01/25 K.Doukuni */
		/*
		** 松下モデム テストルーチン1 : トーン検出テスト
		*/
		debug1_start = 0;
		if (debug1_start) { /* defaultフィルタによるTONAL/DTMF検出 */
			debug_end = 0;
			debug_memorize1 = debug_memorize2 = debug_memorize3 = debug_memorize4 = debug_memorize5 = 0;
			MDM_ToneModeConfig(); /* TONAL-5 ORG */
			while (!debug_end) {
				if (debug_memorize1 != DEBUG_IsToneDetected) { /* トーン検出したか */
					debug_memorize1  = DEBUG_IsToneDetected;
				}
				if (debug_memorize2 != DEBUG_ToneFreqDetectedByMN) { /* トーナル信号の周波数情報 */
					debug_memorize2  = DEBUG_ToneFreqDetectedByMN;
				}
				if (debug_memorize3 != DEBUG_IsDTMFDetected) { /* DTMF検出したか */
					debug_memorize3  = DEBUG_IsDTMFDetected;
				}
				if (debug_memorize4 != DEBUG_DTMFDetectedByMN_H) { /* DTMF（高域）周波数情報 */
					debug_memorize4  = DEBUG_DTMFDetectedByMN_H;
				}
				if (debug_memorize5 != DEBUG_DTMFDetectedByMN_L) { /* DTMF（低域）周波数情報 */
					debug_memorize5  = DEBUG_DTMFDetectedByMN_L;
				}
				MDM_MeasureReceiveLevel = (UWORD)MDMD_GetRES_AGCVAL();
				wai_tsk(2);
				debug_end = 0;
			}
			MDM_SetToneDetectModeExit();
			wai_tsk(100);
			outp(0,0);	/* debug終わり */
		}
		
		/*
		** 松下モデム テストルーチン2 : カスタムフィルタテスト
		*/
		debug2_start = 0;
		if (debug2_start) {
			debug_end = 0;
			
			/*
			** custom filter セット
			*/
			MDM_FilterSet(0xFF);	/* 0xFF : テスト時しか使いません */
			MDM_ToneModeConfig();
			
			while (!debug_end) {
				if (debug_memorize1 != DEBUG_IsToneDetected) { /* トーン検出したか */
					debug_memorize1  = DEBUG_IsToneDetected;
				}
				if (debug_memorize2 != DEBUG_ToneFreqDetectedByMN) { /* トーナル信号の周波数情報 */
					debug_memorize2  = DEBUG_ToneFreqDetectedByMN;
				}
				MDM_MeasureReceiveLevel = (UWORD)MDMD_GetRES_AGCVAL();
				wai_tsk(2);
				debug_end = 0;
			}
			MDM_SetToneDetectModeExit();
			wai_tsk(100);
			outp(0,0);	/* debug終わり */
		}
#endif

		/* ＣＮＧの間隔が４秒周期になっている不具合修正
		** ＣＮＧのＯＮ送出後、フィルターのセットをしてからＯＦＦのタイマー（３秒）を起動しているが、
		** フィルターのセットにかなり時間がかかっており、結果的に４秒周期ぐらいになっている。
		** よって、ＯＦＦタイマータスクの起動をＯＮ送出直後に移動します。
		** by O.Kimoto 1999/04/23
		*/
		/*-----------------------------*/
		/*CNG OFF 3秒ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
		/*-----------------------------*/
		if (tskno_cngoff_timeup_tsk == 0xFFFF) {
			CNG_OFF_TimeUp.Time	= 300;		/*	3秒	*/
			CNG_OFF_TimeUp.SendMBX		= mbxno.FCM_Task;
			CNG_OFF_TimeUp.ReturnValue	= TIMEUP_CNGOFF;
			cre_tsk(&tskno_cngoff_timeup_tsk, TSK_CMN_MAN_TIMER10MSTASK, &CNG_OFF_TimeUp);
		}

#if (PRO_MODEM == MN195006)
		MDM_ToneModeConfig();	/* TONAL-5 config */
#else
/* #if 0	/@ 1996/03/27 V21ｺﾝﾌｨｸﾞでもATV25は反応するので削除 */

/* 1996/04/08 外線で、ATV25が検出しにくかったので、やっぱり、とりあえず
*			  ﾄｰﾝﾓｰﾄﾞにｺﾝﾌｨｸﾞするようにした
*/
		MDM_SetIO(POS_CONF, TX_SINGLE_TONE);
		MDM_SetIO(POS_NEWC, ON);/* re config tone mode for ATV25detector */
/* #endif */
		/*------------------------------*/
		/*ﾌｨﾙﾀｰのﾄｰﾝ周波数検出範囲を設定*/
		/*------------------------------*/
#if 0	/* 1998/03/27 Y.Murata */
//		MDM_FilterSet(FSK_FILTER);		/* T.B.D detect CED ? */
#endif
		/* ATV25の誤検出を吸収するため、ﾌｨﾙﾀｰCで、2100成分を検出するので、こっちが正解 */
#if 0 /* filter_type に正しいフィルタを設定しなくてはいけない。 Changed by H.Kubo 1998/05/21 */
@@		MDM_FilterSet(AFTER_DIAL_FILTER);
#else
		filter_type = AFTER_DIAL_FILTER;
		MDM_FilterSet(filter_type);
 #endif
#endif
		/*------------------*/
		/*ｽﾄｯﾌﾟｷｰ検出ﾀｽｸ	*/
		/*------------------*/
		if (tskno_stop_tsk == 0xFFFF) {
			cre_tsk(&tskno_stop_tsk, TSK_ATD_CHECKSTOPTASK, 0);
		}
		/*------------------*/
		/*ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
		/*------------------*/
		if (tskno_timeup_tsk == 0xFFFF) {
			TimeUp.Time			= 3500;		/* T1 Time Over */
			TimeUp.SendMBX		= mbxno.FCM_Task;
			TimeUp.ReturnValue	= TIMEUP;
			cre_tsk(&tskno_timeup_tsk, TSK_CMN_MAN_TIMER10MSTASK, &TimeUp);
		}

#if (0)
** 		/* ＣＮＧの間隔が４秒周期になっている不具合修正
** 		** ＣＮＧのＯＮ送出後、フィルターのセットをしてからＯＦＦのタイマー（３秒）を起動しているが、
** 		** フィルターのセットにかなり時間がかかっており、結果的に４秒周期ぐらいになっている。
** 		** よって、ＯＦＦタイマータスクの起動をＯＮ送出直後に移動します。
** 		** by O.Kimoto 1999/04/23
** 		*/
** 		/*-----------------------------*/
** 		/*CNG OFF 3秒ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
** 		/*-----------------------------*/
** 		if (tskno_cngoff_timeup_tsk == 0xFFFF) {
** 			CNG_OFF_TimeUp.Time	= 300;		/*	3秒	*/
** 			CNG_OFF_TimeUp.SendMBX		= mbxno.FCM_Task;
** 			CNG_OFF_TimeUp.ReturnValue	= TIMEUP_CNGOFF;
** 			cre_tsk(&tskno_cngoff_timeup_tsk, TSK_CMN_MAN_TIMER10MSTASK, &CNG_OFF_TimeUp);
** 		}
#endif

		/*-------------------------------*/
		/*2100Hzﾄｰﾝ検出ﾀｽｸ生成（連続ﾄｰﾝ）*/
		/*-------------------------------*/
		/* T.B.D */
#if (0)
** 		/* 日立の特許回避（ＣＥＤ検出）
** 		** 下記タスクの生成は元々コメントになっていましたが、念のために！
** 		** By O.Kimoto 1998/04/14
** 		*/
** 		if (tskno_ced_tsk == 0xFFFF) {
** 			CedToneDetectMailBox.ToneType = CED_TONE;
** 			CedToneDetectMailBox.SendMBX = mbxno.FCM_Task;
** 			cre_tsk(&tskno_ced_tsk, TSK_ATD_TONEDETECTPATTERN0TASK, &CedToneDetectMailBox);
** 		}
#endif
		/*-----------------*/
		/*DISﾄｰﾝ検出ﾀｽｸ生成*/
		/*-----------------*/
		if (tskno_dis_tsk == 0xFFFF) {
			DisToneDetectMailBox.ToneType = DIS_TONE;
			DisToneDetectMailBox.SendMBX = mbxno.FCM_Task;
			cre_tsk(&tskno_dis_tsk, TSK_ATD_TONEDETECTPATTERN0TASK, &DisToneDetectMailBox);
		}
		/*---------------------------------*/
		/** Ｖ２５アンサートーンタスク生成 */
		/*---------------------------------*/
		/* Ｖ．８ハンドシェーク中のノイズ対策で、最初の ANSam 検出の有効／無効の判断を追加。 by H.Kubo 1999/04/26 */
		if (!FCM_OverrideANSam()) { /* 短縮ダイヤルにある最初の ANSam を無視する属性 (MEM_SW B:3-7) ならば */
			if (tskno_answer_tone_tsk == 0xffff) { /* CED も検出。 */
#if 0 /* Changed by H.Kubo 1998/01/08 */
@@				cre_tsk(&tskno_answer_tone_tsk, TSK_ATD_DETECTANSWERTONEV25TASK, 0);
#else
				cre_tsk(&tskno_answer_tone_tsk, TSK_ATD_DETECTANSWERTONEV25TASK, &filter_type);
#endif /* 0 */
			}
		}
		/* by H.Kubo 1998/01/09 */
		/*-------------------*/
		/*ﾋﾞｼﾞ-ﾄｰﾝ検出ﾀｽｸ生成*/
		/*-------------------*/
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
		/* Nothing 2000/02/10 Y.Murata */
#else
		if(FCM_PtnrChkBusyToneDetect()) {
			if (((struct ToneParameters_t far *)CTRY_BusyTone())->DetectCycle) {
				if (tskno_bt_tsk == 0xFFFF) {
					BusyToneDetectMailBox.ToneType = BUSYTONE;
					BusyToneDetectMailBox.SendMBX = mbxno.FCM_Task;
					switch (((struct ToneParameters_t *)CTRY_BusyTone())->TonePattern) {
					case	0:		/*ﾄｰﾝのﾊﾟﾀｰﾝが連続の時*/
						cre_tsk(&tskno_bt_tsk, TSK_ATD_TONEDETECTPATTERN0TASK, &BusyToneDetectMailBox);
						break;
					case	1:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF の時*/
					case	2:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF の時*/
					case	3:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF-ON-OFF の時*/
						cre_tsk(&tskno_bt_tsk, TSK_ATD_TONEDETECTPATTERN1TASK, &BusyToneDetectMailBox);
						break;
					}
				}
			}
		}
#endif

		for(;;) {
		/*----------*/
		/*ﾒｯｾｰｼﾞ受信*/
		/*----------*/
			rcv_msg(mbxno.FCM_Task, &receive);
			message = receive->Message;
			/*------------------------*/
			/*CNG OFF時間が3秒経った時*/
			/*------------------------*/
			if (message == TIMEUP_CNGOFF) {
				del_tsk(&tskno_cngoff_timeup_tsk);
				/*-----------------------------------------*/
				/*CNG送出を止める時						   */
				/*(CNG_StopFlagはﾄｰﾝ検出ﾀｽｸの中でｾｯﾄされる)*/
				/*-----------------------------------------*/
				if (CNG_StopFlag) {
					CNG_StopFlag = 0;
					/*-----------------------------*/
					/*ﾄｰﾝ検出続行ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
					/*-----------------------------*/
					if(tskno_tonekeep_timeup_tsk == 0xFFFF){
						ToneKeepTimeUp.Time			= 500;/*トーン検出続行時間(5秒)*/
						ToneKeepTimeUp.SendMBX		= mbxno.FCM_Task;
						ToneKeepTimeUp.ReturnValue	= TIMEUP_TONE0;
						cre_tsk(&tskno_tonekeep_timeup_tsk, TSK_CMN_MAN_TIMER10MSTASK, &ToneKeepTimeUp);
					}
				}
				/*---------------*/
				/*CNG送出を続ける*/
				/*---------------*/
				else {
					break;
				}
			}
			else {
				/*------------------------------*/
				/*(*receive) == TIMEUP_TONE0の時*/
				/*------------------------------*/
				if (tskno_tonekeep_timeup_tsk != 0xFFFF) {
					del_tsk(&tskno_tonekeep_timeup_tsk);
				}
				break;
			}
		}
		/*------------------*/
		/*ﾒｯｾｰｼﾞに対する処理*/
		/*------------------*/
		switch (message) {
		case	TIMEUP_CNGOFF:
		case	TIMEUP_TONE0:
			break;
		case	BUSYTONE: /* H.Kubo 1998/01/09 */
			FCM_ToneAfterDetectDCE = AD_REMOTE_BUSY;
			V8ProcedureRequestFlag = 0;		/** Ｖ８モード移行要求クリア */

			FaxPhaseE(1);		/* 2002/08/05 Y.Murata DCNを送出する */

			TransmitError( 0x11,1 );
			FaxComPerformingFlag = 0;
			ReturnValue = NG;
			break;
		case	TIMEUP:
			FCM_ToneAfterDetectDCE = AD_TIME_OVER; /* added by H.Kubo 1997/11/29 */
			V8ProcedureRequestFlag = 0;		/** Ｖ８モード移行要求クリア */

			FaxPhaseE(1);		/* 2002/08/05 Y.Murata DCNを送出する */

			TransmitError( 0x11,1 );
			FaxComPerformingFlag = 0;
			ReturnValue = NG;
			break;
		case	MSG_DETECT_STOP:
			FCM_ToneAfterDetectDCE = AD_STOPPED; /* added by H.Kubo 1997/11/29 */
			V8ProcedureRequestFlag = 0;		/** Ｖ８モード移行要求クリア */
			TransmitError( 0x14,1 );
			FaxComPerformingFlag = 0;
			ReturnValue = NG;
			break;
		case	CED_TONE:	/* 2100Hz */
			FCM_ToneAfterDetectDCE = AD_OK_CED; /* added by H.Kubo 1997/11/29 */
			V8ProcedureRequestFlag = 1;		/** Ｖ８モード移行要求セット */
			ReturnValue = V34_PROCEDURE;
			break;
		case	MSG_DETECT_V25_ANSWER_TONE:
			FCM_ToneAfterDetectDCE = AD_OK_ANSWER_TONE; /* added by H.Kubo 1997/11/29 */
			V8ProcedureRequestFlag = 1;		/** Ｖ８モード移行要求セット */
			ReturnValue = V34_PROCEDURE;
			break;
		default:	/* DIS */
			FCM_ToneAfterDetectDCE = AD_OK_DIS; /* added by H.Kubo 1997/11/29 */
			V8ProcedureRequestFlag = 0;		/** Ｖ８モード移行要求クリア */
			ReturnValue = T30_PROCEDURE;
		}
		/*--------------------------------*/
		/*ReturnValueに値がｾｯﾄされていたら*/
		/*--------------------------------*/
		if (ReturnValue != 0xFF) {
			FCM_AfterToneCheckDelTask();
#if (PRO_MODEM == MN195006)
			/* MDM を V34H-ORG,V17TXに戻す場合のパス 2001/12/13 K.Doukuni */
			MDM_SetToneDetectModeExit(); /* 一旦idleに 2001/12/13 K.Doukuni */
#endif
			return(ReturnValue);
		}
#if (PRO_MODEM == MN195006)
		/* MDM を TONAL1に戻す場合のパス 2001/12/13 K.Doukuni */
		MDM_SetToneDetectModeExit(); /* 一旦idleに */
#endif
	}
}

void	FCM_AfterToneCheckDelTask(void)
{
	if (tskno_ced_tsk != 0xFFFF) {
		del_tsk(&tskno_ced_tsk);
	}
	if (tskno_dis_tsk != 0xFFFF) {
		del_tsk(&tskno_dis_tsk);
	}
	if (tskno_timeup_tsk != 0xFFFF) {
		del_tsk(&tskno_timeup_tsk);
	}
	if (tskno_cngoff_timeup_tsk != 0xFFFF) {
		del_tsk(&tskno_cngoff_timeup_tsk);
	}
	if (tskno_stop_tsk != 0xFFFF) {
		del_tsk(&tskno_stop_tsk);
	}
	if (tskno_tonekeep_timeup_tsk != 0xFFFF) {
		del_tsk(&tskno_tonekeep_timeup_tsk);
	}
	if (tskno_answer_tone_tsk != 0xFFFF) {
		del_tsk(&tskno_answer_tone_tsk);
	}
	if (tskno_bt_tsk != 0xFFFF) {
		del_tsk(&tskno_bt_tsk);
	}
	
}



/*************************************************************************
	module		:[V8 Error Code Set]
	function	:[
		1.
	]
	commom		:[
		ERROR CODE is TBD
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53]
	language	:[MS-C(Ver6.0)]
	keyword		:[FCM]
	date		:[1996/03/21]
	author		:[村田]
*************************************************************************/
void 	FCM_SetV8Error(UWORD err_phase, UBYTE type)
{
	UBYTE	error_code;

	error_code = 0;

	if (SYS_FaxComStopSwitch()) {
		error_code = (UBYTE)0x14;	/* 1996/08/27 */
	}
	else {
		switch (err_phase) {
		case V34_PHASE_1:
			error_code = (UBYTE)0x81;
			break;
		case V34_PHASE_2:
			error_code = (UBYTE)0x8A;
			break;
		case V34_PHASE_3:
			error_code = (UBYTE)0x8B;
			break;
		default:
			break;
		}
	}

#if 0	/* 1996/10/04            MURATTCH */
//	if (type == TX_COM_MODE) {
//		TransmitError(error_code, 1);
//	}
//	else {
//		ReceiveError(error_code);
//	}
#endif

	if (FaxComTXorRX_Sign == TX_COM_MODE) {
		TransmitError(error_code, 1);
	}
	else if (FaxComTXorRX_Sign == RX_COM_MODE) {
		ReceiveError(error_code);
	}
	else {
		/* 絶対ありえないけど 気持ちだけいれとく */
		if (type == TX_COM_MODE) {
			TransmitError(error_code, 1);
		}
		else {
			ReceiveError(error_code);
		}
	}

}

/*************************************************************************
	module		:[ Determin whether some tonal signal was detected while waiting for ANSam ]
	function	:[
		FCM の ANSam 検出で、トーン (V25 answer tone, CED, DIS) が検出されたかを判断する。
	]
	commom		:[
		FCM_ToneAfterDetectDCE
	]
	condition	:[
		FCM_Task の初期化処理が終わっていること。
	]
	comment		:[]
	return		:[
		TRUE
		FALSE
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1998/05/25]
	author		:[久保博]
*************************************************************************/
UBYTE FCM_CheckToneDetectedInV8Mode(void)
{
	if (   ( FCM_ToneAfterDetectDCE != AD_OK_DIS)
		&& ( FCM_ToneAfterDetectDCE != AD_OK_CED)
		&& ( FCM_ToneAfterDetectDCE != AD_OK_ANSWER_TONE)
	) {
		return ((UBYTE) FALSE);
	}
	return ((UBYTE) TRUE);
}
#endif /* (PRO_TX_SPEED == V34) */
