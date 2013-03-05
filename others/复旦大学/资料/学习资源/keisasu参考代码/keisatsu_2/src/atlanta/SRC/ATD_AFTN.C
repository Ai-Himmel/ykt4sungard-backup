/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANTA																		*/
/*		ﾓｼﾞｭｰﾙ	:UBYTE AfterDial_ToneDetect(void)											*/
/*				:void Del_AfterTone_Task(void)												*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_AFTN.Cを流用しました								*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"		/*	モニタシステムコール	*/
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\ctry_pro.h"		/*	CTRY_?Tone()*/
#include "\src\atlanta\define\atd_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\memsw\define\mem_sw_b.h" /*1996/04/17 Eguchi */

#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\uni_pro.h"

#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\std.h"			/* 96/06/06 */

#if (PRO_MODEM == R288F) /* Changed by H.Kubo 1997/07/19 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"	/* TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"	/* MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\ext_v\sys_data.h" 			/* Added by H.Kubo 1997/07/19 for SYS_V8DetectATV25Flag */
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"	/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\r288f\define\mdm_io.h"
#include "\src\atlanta\ext_v\sys_data.h" 			/* Added by H.Kubo 1997/07/19 for SYS_V8DetectATV25Flag */
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\orange\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\ext_v\sys_data.h" 			/* Added by H.Kubo 1997/07/19 for SYS_V8DetectATV25Flag */
#include "\SRC\ATLANTA\MDM\PANA\DEFINE\MDM_IO.H"
#endif

#include "\src\atlanta\define\timer10.h"		/*	struct Timer10msData_t {}	*/
#include "\src\atlanta\define\message.h"

#include "\src\atlanta\SH7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#if defined(FRA)
 #include "\src\atlanta\ext_v\bkupram.h"
#endif

#include "\src\atlanta\ext_v\atd_data.h"
#include "\src\atlanta\ext_v\atd_tbl.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\sh7043\define\def_tib.h"

#if (PRO_TX_SPEED == V34)

#include "\src\atlanta\ext_v\bkupram.h"	/* Ｖ．８ハンドシェーク中のノイズ対策 by O.Kimoto 1999/04/13 */

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
#include "\src\atlanta\sh7043\define\def_evtn.h" /* by H.Kubo 1997/07/22 */
#endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */

static UWORD tskno_bt = 0;
static UWORD tskno_ct = 0;
static UWORD tskno_ced = 0;
static UWORD tskno_dis = 0;
static UWORD tskno_ad_dse = 0;
/* static UWORD tskno_ad_timeup = 0;	*/
/* static UWORD tskno_cngoff_timeup = 0;	*/
/* static UWORD tskno_tonekeep_timeup = 0;	*/
static UBYTE tskno_ad_timeup = 0;
static UBYTE tskno_cngoff_timeup = 0;
static UBYTE tskno_tonekeep_timeup = 0;
static UWORD tskno_ad_stop = 0;
#if (PRO_MODEM == ORANGE3)
static UWORD tskno_freq_check = 0;
#endif

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/19 */
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
static UWORD tskno_ad_answer_tone = 0;
#endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */


static UBYTE detect_end_flag = 0;/* 96.01.25 By T.Y */

#if(PRO_SPEED_EX == ENABLE)
static UWORD tskno_as_tn = 0; /* 着信後トーン検出 */
#endif

static UBYTE debug_debug = 0;

/*************************************************************************
	module		:[オートダイアラー発呼後のトーン検出]
	function	:[
		1.ＣＮＧ送出
		2.トーン検出
		3.検出したトーン，事象に対する値をリターン
	]
	common		:[
		CNG_StopFlag	:CNG送出を止めるかどうかの判断ﾌﾗｸﾞ
	]
	condition	:[]
	comment		:[
		下位のトーンパターン検出タスクでCNG_StopFlagをセット
		するタイミングに注意
	]
	return		:[
		AD_OK			:CED,DISトーン検出、或は極性反転検出
		AD_STOPPED		:停止ボタンが押された
		AD_TIME_OVER	:トーン検出制限時間オーバー
		AD_REMOTE_BUSY	:相手先が話中
		
		AD_OK_DSE
		AD_OK_SPD_TONE
		AD_DETECT_RINGBACKTONE
		AD_OK_CED
		AD_OK_DIS
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/6]
	author		:[奥村明]
*************************************************************************/


/*-----------------------------------------------*/
/* ﾀﾞｲｱﾙ後のﾄｰﾝ検出, ﾄｰﾝの種類をAutoDial()にﾘﾀｰﾝ */
/* BT|CT|DSE|CED|DIS|STOP|SPD & CNG送出				 */
/*-----------------------------------------------*/
UBYTE AfterDial_ToneDetect(void)
{
	MESSAGE_t		*ad_receive;					/*	rcv_msg()で受信データをｾｯﾄする*/
	UWORD		ad_message = 0;
	UBYTE		return_value = 0xFF;			/*	ﾄｰﾝ検出結果	*/
#if defined(FRA)
	UBYTE FRA_RBT_Det_Flag;
#endif

	struct	Timer10msData_t	TimeUp;
	struct	Timer10msData_t	CNG_OFF_TimeUp;
	struct	Timer10msData_t	ToneKeepTimeUp;
	struct	ToneDetectMailBoxData_t	BusyToneDetectMailBox;
	struct	ToneDetectMailBoxData_t	ConToneDetectMailBox;
	struct	ToneDetectMailBoxData_t	DisToneDetectMailBox;
	struct	ToneDetectMailBoxData_t	CedToneDetectMailBox;
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1998/01/08 */
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
	UBYTE filter_type;
#endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */
#if (PRO_SPEED_EX == ENABLE)
	struct	ToneDetectMailBoxData_t	ASToneDetectMailBox; /*			 | SendMBX | ToneType |	 */
#endif

#if (PRO_MODEM == ORANGE3)
	/* ATD_FilterOnOffDetectTaskへの引き数の型が合っていない T.Nose 1996/06/01 */
	UBYTE	tone_detect_type;
	tone_detect_type = AFTER_DIAL_DETECT;
	tskno_freq_check = 0xffff;
#endif
	tskno_bt = 0xffff;
	tskno_ct = 0xffff;
	tskno_ced = 0xffff;
	tskno_dis = 0xffff;
	tskno_ad_dse = 0xffff;
	tskno_ad_timeup = 0xff;
	tskno_cngoff_timeup = 0xff;
	tskno_tonekeep_timeup = 0xff;
/*	tskno_ad_timeup = 0xffff;	*/
/*	tskno_cngoff_timeup = 0xffff;	*/
/*	tskno_tonekeep_timeup = 0xffff;	*/
	tskno_ad_stop = 0xffff;
#if (PRO_SPEED_EX == ENABLE)
	tskno_as_tn = 0xffff;	/* 着信トーン検出 */
#endif
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/19 */
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
	tskno_ad_answer_tone = 0xffff;
	filter_type = AFTER_DIAL_FILTER;
 #endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */

	CNG_StopFlag = 0;		/*CNG送出:0	   CNG停止:1*/
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/19 */
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
	SYS_V8DetectATV25Flag = 0;	/** V25 Answer Tone Flag */
 #endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */
/* #if defined(DEU) */	/* by M.H '97/03/21 for CNG Tx timing from holding the line (1.5 +- 1sec) */
	/*
	** ダイヤル後一発目のＣＮＧを出すまでの時間は１．５ｓ±１．０ｓ
	** ＤＥＵのみの規格だが標準で入れておく Jun.12.1997  By T.Yamaguchi
	*/
	wai_tsk(130);
/* #endif */

	/*------------------------------*/
	/*ﾌｨﾙﾀｰのﾄｰﾝ周波数検出範囲を設定*/
	/*------------------------------*/
	MDM_FilterSet(AFTER_DIAL_FILTER);
	/*---------------*/
	/*ﾄｰﾝ検出&CNG送出*/
	/*---------------*/
	for (;;) {
		/*--------------*/
		/*CNG送出(500ms)*/
		/*--------------*/
		MDM_ToneTx(TONE_1080HZ, 500);

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* Added by H.Kubo 1997/07/19 */

		/* ＣＮＧの送出間隔が正しくＯＮ／ＯＦＦ＝０．５秒／３秒にならない。
		** 原因は、ＣＮＧのＯＮを送出後、ＯＦＦのタイマーを起動するまでに時間がかかりすぎている為
		** よって、ＣＮＧのＯＦＦタイマーの起動はＯＮ送出直後に移動させます。
		** By O.Kimoto 1999/04/22
		*/
		if (tskno_cngoff_timeup == 0xFF) {
#if defined(FRA) || defined(DEU) || defined(EUR)	/* add by M.HARADA '97/1/8 */
													/* 欧州仕様追加 by M.H 1999/09/16 */
			CNG_OFF_TimeUp.Time	= 280;		/*	close to 3秒	*/
#else
			CNG_OFF_TimeUp.Time	= 300;		/*	3秒	*/
#endif
			CNG_OFF_TimeUp.SendMBX		= mbxno.FCM_Task;
			CNG_OFF_TimeUp.ReturnValue	= TIMEUP_CNGOFF;
			CMN_MultiTimer10msStart(&tskno_cngoff_timeup, &CNG_OFF_TimeUp);
		}
#if defined(FRA)
		else{
			debug_debug = 0;
		}
#endif

		/* ダイヤルトーン検出用フィルターをセットする前に
		** ＣＯＮＦの値をＶ．８からＶ．２１に戻しておきます。
		** 1997/05/27 Y.Murata
		*/
		/*---------------------------------------*/
		/* re config tone mode for ATV25detector */
		/*---------------------------------------*/
		MDM_ToneModeConfig();
#endif /* (PRO_MODEM == R288F) */

		/*------------------------------*/
		/*ﾌｨﾙﾀｰのﾄｰﾝ周波数検出範囲を設定*/
		/*------------------------------*/
		MDM_FilterSet(AFTER_DIAL_FILTER);
		/*------------------*/
		/*ｽﾄｯﾌﾟｷｰ検出ﾀｽｸ	*/
		/*------------------*/
		if (tskno_ad_stop == 0xFFFF) {
			cre_tsk(&tskno_ad_stop, TSK_ATD_CHECKSTOPTASK, 0);
		}
		/*------------------*/
		/*ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
		/*------------------*/
/*		if (tskno_ad_timeup == 0xFFFF) {	1996/12/12	By T.Yamaguchi */
		if (tskno_ad_timeup == 0xFF) {
			if (CHK_AFTER_DIAL_DELAY_TIME()) {	/* By M.Tachibana 1997/06/09 */
	            TimeUp.Time = ((UWORD)CHK_AFTER_DIAL_DELAY_TIME()*100);   /*着信検出時間*/
			}
			else {
				TimeUp.Time = ((struct ToneParameters_t *)CTRY_BusyTone())->MaxDetectTime;	/*着信検出時間*/
			}
			TimeUp.SendMBX		= mbxno.FCM_Task;
			TimeUp.ReturnValue	= TIMEUP;
			CMN_MultiTimer10msStart(&tskno_ad_timeup, &TimeUp);
/*			cre_tsk(&tskno_ad_timeup, TSK_CMN_MAN_TIMER10MSTASK, &TimeUp);	*/
		}
		/*-----------------------------*/
		/*CNG OFF 3秒ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
		/*-----------------------------*/

#if (PRO_MODEM != R288F) && (PRO_MODEM == MN195006)	/* Add By O.Kimoto 1999/04/22 */
/*		if (tskno_cngoff_timeup == 0xFFFF) {	*/
			if (tskno_cngoff_timeup == 0xFF) {
 #if defined(FRA) || defined(DEU) || defined(EUR)	/* add by M.HARADA '97/1/8 */
													/* 欧州仕様追加 by M.H 1999/09/16 */
			CNG_OFF_TimeUp.Time	= 280;		/*	close to 3秒	*/
 #else
			CNG_OFF_TimeUp.Time	= 300;		/*	3秒	*/
 #endif
			CNG_OFF_TimeUp.SendMBX		= mbxno.FCM_Task;
			CNG_OFF_TimeUp.ReturnValue	= TIMEUP_CNGOFF;
			CMN_MultiTimer10msStart(&tskno_cngoff_timeup, &CNG_OFF_TimeUp);
/*			cre_tsk(&tskno_cngoff_timeup, TSK_CMN_MAN_TIMER10MSTASK, &CNG_OFF_TimeUp);	*/
		}
 #if defined(FRA)
		else{
			debug_debug = 0;
		}
 #endif
#endif

		/*-------------------*/
		/*ﾋﾞｼﾞ-ﾄｰﾝ検出ﾀｽｸ生成*/
		/*-------------------*/
		if(FCM_PtnrChkBusyToneDetect()) {
			if (((struct ToneParameters_t far *)CTRY_BusyTone())->DetectCycle) {
				if (tskno_bt == 0xFFFF) {
					BusyToneDetectMailBox.ToneType = BUSYTONE;
					BusyToneDetectMailBox.SendMBX = mbxno.FCM_Task;
					switch (((struct ToneParameters_t far *)CTRY_BusyTone())->TonePattern) {
					case	0:		/*ﾄｰﾝのﾊﾟﾀｰﾝが連続の時*/
						cre_tsk(&tskno_bt, TSK_ATD_TONEDETECTPATTERN0TASK, &BusyToneDetectMailBox);
						break;
					case	1:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF の時*/
					case	2:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF の時*/
					case	3:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF-ON-OFF の時*/
						cre_tsk(&tskno_bt, TSK_ATD_TONEDETECTPATTERN1TASK, &BusyToneDetectMailBox);
						break;
					}
				}
			}
		}
		/*-----------------------*/
		/*ｺﾝｼﾞｪｽｼｮﾝﾄｰﾝ検出ﾀｽｸ生成*/
		/*-----------------------*/
#if defined(FRA)
		if (CHK_UNI_HumanAnswerClear()) {
#endif
			if(CHK_UNI_ConToneDetect()) {
				if (((struct ToneParameters_t far *)CTRY_CongestionTone())->DetectCycle) {
					if (tskno_ct == 0xFFFF) {
						ConToneDetectMailBox.ToneType = CONTONE;
						ConToneDetectMailBox.SendMBX = mbxno.FCM_Task;
						switch (((struct ToneParameters_t far *)CTRY_CongestionTone())->TonePattern) {
						case	0:		/*ﾄｰﾝのﾊﾟﾀｰﾝが連続の時*/
							cre_tsk(&tskno_ct, TSK_ATD_TONEDETECTPATTERN0TASK, &ConToneDetectMailBox);
							break;
						case	1:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF の時*/
						case	2:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF の時*/
						case	3:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF-ON-OFF の時*/
							cre_tsk(&tskno_ct, TSK_ATD_TONEDETECTPATTERN1TASK, &ConToneDetectMailBox);
							break;
						}
					}
				}
			}
#if defined(FRA)
		}
#endif

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/19 */
		/*---------------------------------*/
		/** Ｖ２５アンサートーンタスク生成 */
		/* CEDﾄｰﾝ検出ﾀｽｸ生成（連続ﾄｰﾝ）    */
		/*---------------------------------*/
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)

  #if (0)
** /* Ｖ．８ハンドシェーク中のノイズ対策 by O.Kimoto 1999/04/13 */
**   #if (PRO_CED_DETECT == ENABLE) /* 日立特許回避。Clover2 から移植。By H.Kubo 1998/07/08 */
** 		if (CHK_CED_Detect()) {
**   #else
** 		if (CHK_CED_Detect() && (CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT)) {
**   #endif
  #else
   #if (PRO_CED_DETECT == ENABLE) /* 日立特許回避。Clover2 から移植。By H.Kubo 1998/07/08 */
		if (CHK_CED_Detect() && (SYB_MemorySwitch[MEMORY_SW_B3] & INHIBIT_DETECT_ANSAM)) {
   #else
		if (CHK_CED_Detect() && (CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT) && !FCM_OverrideANSam()) {
   #endif
  #endif

			if (tskno_ad_answer_tone == 0xffff) {
				cre_tsk(&tskno_ad_answer_tone, TSK_ATD_DETECTANSWERTONEV25TASK, &filter_type);
			}
		}
 #else /* (PRO_MODEM == R288F) */
	#error "Need a method to detect V25 answer tone and CED."
 #endif /* (PRO_MODEM == R288F) */
#else /* (PRO_TX_SPEED == V34) */
		/*----------------------------*/
		/*CEDﾄｰﾝ検出ﾀｽｸ生成（連続ﾄｰﾝ）*/
		/*----------------------------*/
 #if (PRO_CED_DETECT == ENABLE)	/* 日立特許回避 By M.Tachibana 1998/04/14 */
		if (CHK_CED_Detect()) {
			if (tskno_ced == 0xFFFF) {
				CedToneDetectMailBox.ToneType = CED_TONE;
				CedToneDetectMailBox.SendMBX = mbxno.FCM_Task;
				cre_tsk(&tskno_ced, TSK_ATD_TONEDETECTPATTERN0TASK, &CedToneDetectMailBox);
			}
		}
 #endif
#endif /* (PRO_TX_SPEED == V34) */
		/*-----------------*/
		/*DISﾄｰﾝ検出ﾀｽｸ生成*/
		/*-----------------*/
		if (tskno_dis == 0xFFFF) {
			DisToneDetectMailBox.ToneType = DIS_TONE;
			DisToneDetectMailBox.SendMBX = mbxno.FCM_Task;
			cre_tsk(&tskno_dis, TSK_ATD_TONEDETECTPATTERN0TASK, &DisToneDetectMailBox);
		}
#if (PRO_SPEED_EX == ENABLE)
		/*------------------------*/
		/*極性反転(DSE)検出ﾀｽｸ生成*/
		/*------------------------*/
		if ((CHK_UNI_SpeedHandshakeEx() == 0)
			&&(CHK_UNI_DSE_Detect())) {		/* 個別Ａ０ */
			if (tskno_ad_dse == 0xFFFF) {
				cre_tsk(&tskno_ad_dse, TSK_ATD_CHECKDSETASK, 0);
			}
		}
		/*--------------------------*/
		/*着信後トーン検出（短縮用）*/
		/*--------------------------*/
		if ((SpeedHandshakeRomCheck() == TRUE) &&
		   (CHK_UNI_SpeedHandshakeEx() != 0)) {
			if (tskno_as_tn == 0xFFFF) {
				ASToneDetectMailBox.ToneType = SPD_TONE;
				ASToneDetectMailBox.SendMBX = mbxno.FCM_Task;
				cre_tsk(&tskno_as_tn, TSK_ATD_CHECKTONETASK, &ASToneDetectMailBox);
			}
		}
#else
		/*------------------------*/
		/*極性反転(DSE)検出ﾀｽｸ生成*/
		/*------------------------*/
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* Ported from CLOVER by H.Kubo 1997/11/04 */
		/* Class1動作時は極反検出は行いません By O.Kimoto 1997/06/02 */
		if (!CMN_CheckActiveClass1()) {
			if (CHK_UNI_DSE_Detect()) {
				if (tskno_ad_dse == 0xFFFF) {
					cre_tsk(&tskno_ad_dse, TSK_ATD_CHECKDSETASK, 0);
				}
			}
		}
#else /* (PRO_MODEM == R288F) */
		/* Class1動作時は極反検出は行いません 暫定処置 S.Fukui Jun.29,1998 */
		if (!CMN_CheckActiveClass1()) {
			if (CHK_UNI_DSE_Detect()) {		/* 個別Ａ０ */
				if (tskno_ad_dse == 0xFFFF) {
						cre_tsk(&tskno_ad_dse, TSK_ATD_CHECKDSETASK, 0);
				}
			}
		}
 #if (0)
		if (CHK_UNI_DSE_Detect()) {		/* 個別Ａ０ */
			if (tskno_ad_dse == 0xFFFF) {
					cre_tsk(&tskno_ad_dse, TSK_ATD_CHECKDSETASK, 0);
			}
		}
 #endif
#endif /* (PRO_MODEM == R288F) */
#endif


		/*-------------------------------------*/
		/*	Frequency check Only Orange3 Modem */
		/*-------------------------------------*/
#if (PRO_MODEM == ORANGE3)
		if (tskno_freq_check == 0xFFFF) {
			cre_tsk(&tskno_freq_check, TSK_ATD_FILTERONOFFDETECTTASK, &tone_detect_type);
		}
#endif

		for(;;) {
		/*----------*/
		/*ﾒｯｾｰｼﾞ受信*/
		/*----------*/
			rcv_msg(mbxno.FCM_Task, &ad_receive);
			ad_message = ad_receive->Message;
#if defined(FRA)						/* 95/01/20 by M.HARADA */
			/*-----------------*/
			/* RBTを検出した時 */
			/*-----------------*/
			if(ad_message == CONTONE){
				if (tskno_ct != 0xFFFF) {					/* del RBT検出タスク */
					del_tsk(&tskno_ct);
				}
			}
#endif
			/*------------------------*/
			/*CNG OFF時間が3秒経った時*/
			/*------------------------*/
			if (ad_message == TIMEUP_CNGOFF) {
				if (tskno_cngoff_timeup != 0xFF) {
					CMN_MultiTimer10msStop(&tskno_cngoff_timeup);
				}
/*				del_tsk(&tskno_cngoff_timeup);	1996/12/12	By T.Yamaguchi */
				/*-----------------------------------------*/
				/*CNG送出を止める時						   */
				/*(CNG_StopFlagはﾄｰﾝ検出ﾀｽｸの中でｾｯﾄされる)*/
				/*-----------------------------------------*/
				if (CNG_StopFlag) {
					CNG_StopFlag = 0;
					/*-----------------------------*/
					/*ﾄｰﾝ検出続行ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
					/*-----------------------------*/
/*					if(tskno_tonekeep_timeup == 0xFFFF){	1996/12/12	By T.Yamaguchi */
					if(tskno_tonekeep_timeup == 0xFF){
						ToneKeepTimeUp.Time			= 500;/*トーン検出続行時間(5秒)*/
						ToneKeepTimeUp.SendMBX		= mbxno.FCM_Task;
						ToneKeepTimeUp.ReturnValue	= TIMEUP_TONE0;
						CMN_MultiTimer10msStart(&tskno_tonekeep_timeup, &ToneKeepTimeUp);
/*						cre_tsk(&tskno_tonekeep_timeup, TSK_CMN_MAN_TIMER10MSTASK, &ToneKeepTimeUp);	*/
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
				/*---------------------------------*/
				/*(*ad_receive) == TIMEUP_TONE0の時*/
				/*---------------------------------*/
/*				if (tskno_tonekeep_timeup != 0xFFFF) {	1996/12/12	By T.Yamaguchi */
				if (tskno_tonekeep_timeup != 0xFF) {
					CMN_MultiTimer10msStop(&tskno_tonekeep_timeup);
/*					del_tsk(&tskno_tonekeep_timeup);	*/
				}
				break;
			}
		}
		/*------------------*/
		/*ﾒｯｾｰｼﾞに対する処理*/
		/*------------------*/
		switch (ad_message) {
		case	TIMEUP_CNGOFF:
		case	TIMEUP_TONE0:
			break;
		case	BUSYTONE:
#if !defined(FRA)							/* FRA以外 by M.HARADA 95/01/20 */
		case	CONTONE:
#endif
			return_value = AD_REMOTE_BUSY;
			break;
		case	TIMEUP:
			return_value = AD_TIME_OVER;
			break;
		case	MSG_DETECT_STOP:
			return_value = AD_STOPPED;
			break;
		case	MSG_DETECT_DSE:
			return_value = AD_OK_DSE;
			break;
#if (PRO_SPEED_EX == ENABLE)
		case	SPD_TONE:
			return_value = AD_OK_SPD_TONE;
			break;
#endif
#if defined(FRA)						/* 95/01/20 by M.HARADA */
		case	CONTONE:
			break;
		case	MSG_TIMEUP_AFTER_RBT:
			return_value = AD_DETECT_RINGBACKTONE;
			break;
#endif
		case	CED_TONE:
			return_value = AD_OK_CED;
			break;
#if (PRO_TX_SPEED == V34)  /* Added by H.Kubo 1997/07/19 */
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
		case	MSG_DETECT_V25_ANSWER_TONE:
			return_value = AD_OK_ANSWER_TONE;
			break;
 #endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */
		default:	/* DIS */
			return_value = AD_OK_DIS;
			break;
		}
		detect_end_flag = 0;
		/*--------------------------------*/
		/*return_valueに値がｾｯﾄされていたら*/
		/*--------------------------------*/
		if (return_value != 0xFF) {
			detect_end_flag = 1;
			Del_AfterTone_Task();
			return(return_value);
		}
		else {
			Del_AfterTone_Task();
		}
	}
}


/*---------------------------------*/
/*ﾀﾞｲｱﾙ後ﾄｰﾝ検出で使用したﾀｽｸを削除*/
/*---------------------------------*/
void	Del_AfterTone_Task(void)
{
	if (tskno_bt != 0xFFFF) {
		del_tsk(&tskno_bt);
	}
	if (tskno_ct != 0xFFFF) {
		del_tsk(&tskno_ct);
	}
	if (tskno_ced != 0xFFFF) {
		del_tsk(&tskno_ced);
	}
	if (tskno_dis != 0xFFFF) {
		del_tsk(&tskno_dis);
	}
#if (PRO_SPEED_EX == ENABLE)
	if (tskno_as_tn != 0xFFFF){
		del_tsk(&tskno_as_tn);
	}
#endif
/*	if (tskno_cngoff_timeup != 0xFFFF) {	*/
	if (tskno_cngoff_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_cngoff_timeup);
/*		del_tsk(&tskno_cngoff_timeup);	*/
	}
/*	if (tskno_tonekeep_timeup != 0xFFFF) {	*/
	if (tskno_tonekeep_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_tonekeep_timeup);
/*		del_tsk(&tskno_tonekeep_timeup);	*/
	}
#if defined(FRA)
/*	if (tskno_after_rbt_timeup !=0xFFFF) {	*/
	if (tskno_after_rbt_timeup !=0xFF) {		/* 1996/12/12  By T.Yamaguchi */
		CMN_MultiTimer10msStop(&tskno_after_rbt_timeup);
/*		del_tsk(&tskno_after_rbt_timeup);	*/
	}
#endif
#if (PRO_MODEM == ORANGE3)
	if (tskno_freq_check != 0xFFFF) {
		del_tsk(&tskno_freq_check);
	}
#endif
	if (detect_end_flag) {
		if (tskno_ad_dse != 0xFFFF) {
			del_tsk(&tskno_ad_dse);
		}
/*		if (tskno_ad_timeup != 0xFFFF) {	*/
		if (tskno_ad_timeup != 0xFF) {
			CMN_MultiTimer10msStop(&tskno_ad_timeup);
/*			del_tsk(&tskno_ad_timeup);	*/
		}
		if (tskno_ad_stop != 0xFFFF) {
			del_tsk(&tskno_ad_stop);
		}
	}
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/19 */
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
	/*---------------------------------*/
	/** Ｖ２５アンサートーンタスク削除 */
	/*---------------------------------*/
	if (tskno_ad_answer_tone != 0xffff) {
		del_tsk(&tskno_ad_answer_tone);
	}
 #endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */
}


#if (PRO_TX_SPEED == V34)
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
/* Ported from Clover\src\astn.c by H.Kubo 1997/07/22 */
/*************************************************************************
	module		:[Ｖ２５アンサートーン検出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[ATD]
	date		:[1995/10/24]
	author		:[村田]
*************************************************************************/
/* void ATD_DetectAnswerToneV25Task(void) */ /* ビジートーン誤検出対策用に引数を加えた。*/
void ATD_DetectAnswerToneV25Task(UBYTE *filter_type)
{
	MESSAGE_t msg;

	UWORD			atv25_on_cnt;
	UWORD			atv25_off_cnt;
	unsigned char	ret;
	UWORD detect_time;	/* ANSam対策 By O.Kimoto 1997/06/02 */
	
	ret = 0;
	
	CMN_DisableInterrupt();		/** 割り込み禁止 */
	if (SYS_V8DetectATV25Flag == 0) {
		wai_evt(EVT_MDM_ATV25);	/* ATV25 */
	}
	CMN_EnableInterrupt();		/** 割り込み許可 */
	SYS_V8DetectATV25Flag = 0;

	/* Class1動作時は、ATV25の監視タイマーを1秒にします。 By O.Kimoto 1997/06/02 */
	if (CMN_CheckActiveClass1()) {
		detect_time = 1000/10;
	}
	else {
		detect_time = 100/10;
	}

	/* 1997/01/26 Y.Murata
	 * ＡＴＶ２５が誤検出してT.1.1になる可能性がるため
	 * 再度検出
	*/
	atv25_on_cnt = 0;
	atv25_off_cnt = 0;
	while (1) {
		if (MDM_GetIO(POS_ATV25)) {
			if (*filter_type == (UBYTE) AFTER_DIAL_FILTER) { /* Busy tone 誤検出対策 */
  #if (0)
				if (MDM_GetIO(POS_TONEA)) { /* BUSY Tone 検出用フィルタフラグ監視 */
					atv25_off_cnt++;
					if (atv25_off_cnt > 4) {	/* 30ms */
						atv25_on_cnt = 0;
					}
				}
  #else

   #if defined(USA) /* 音声メッセージ誤検出対策（試し） by H.Kubo 1998/05/28 */
				if (MDM_GetIO(POS_TONEA) || MDM_GetIO(POS_TONEB)) { /* BUSY Tone 検出用フィルタフラグ監視 */
					atv25_off_cnt++;
					if ((atv25_off_cnt > 4) && (atv25_on_cnt > 0) ) {	/* 30ms */
						atv25_on_cnt--;
					}
				}
   #endif

				/* AFTER_DIAL_FILTER では、 TONEC で CED (2100Hz) の監視をしています。 */
				if (MDM_GetIO(POS_TONEC)) { /* 2100Hz 検出用フィルタフラグ監視 */
					atv25_on_cnt++;
					atv25_off_cnt = 0;
					if (atv25_on_cnt > detect_time) {	/* 90ms *//* Change 直値(10) to 変数 By O.Kimoto 1997/06/02 */
						break;
					}
				}
				else {
					atv25_off_cnt++;
					if (atv25_off_cnt > 4) {	/* 30ms */
						atv25_on_cnt = 0;
					}
				}
  #endif
			}
			else {
				atv25_on_cnt++;
				atv25_off_cnt = 0;
				if (atv25_on_cnt > detect_time) {	/* 90ms *//* Change 直値(10) to 変数 By O.Kimoto 1997/06/02 */
					break;
				}
			}
		}
		else {
			atv25_off_cnt++;
			if (atv25_off_cnt > 4) {	/* 30ms */
				atv25_on_cnt = 0;
			}
		}
		wai_tsk(1);		/* 10ms */
	}

	/*-----------------*/
	/** メッセージ送信 */
	/*-----------------*/
	msg.Message = MSG_DETECT_V25_ANSWER_TONE;
	snd_msg(mbxno.FCM_Task, &msg);
	wai_tsk(0xFFFF);		/** 無限ループ */

}
 #endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */

