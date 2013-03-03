/**********************************************************************
* ANZU
*
*	 File	Name:  NCU_RING.C
*	 Coded	  by:  坂本直史
*	 Module Name:  NCU_DetectFnetTask()
*				   FnetChildTaskExit()
*				   NCU_FrequencyCheckTask()
*				   NCU_TimeUpTask()
*				   SetTimerValue()
*				   SetRingCounter()
*				   SetSamplingCounter()
*				   CompareSamplingTone()
*				   InitializeGrovalData()
*				   StoreRingingOnTime()
*				   StoreRingingOffTime()
*				   StopOneshotTimer()
*				   CheckContinueAndDoubleRing()
*				   DetectRingTone()
*				   CiCheckRequest()
*				   NCU_DetectCalledTask()
*				   DetCallChildTaskExit()
*				   NCU_DetectCalledExit()
*
*	 Note		:  呼出信号検出
*
***********************************************************************/
/*
 * ATLANTAに移植 1996/12/02 Eguchi
 * (1)インクルードファイルのパス変更
 * (2)不要なパスを削除
 *    内線通話、内蔵ＴＡＤ、ブランチ、Ｈ８、Ｖ５３・・・
 * (3)far/near削除
 * (4)unsigned char -> UBYTE
 * (5)構造体の定義->けつに"_t"を付ける
 */
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\message.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\uni_pro.h"
#if (PRO_LINENUMBER == TWICE_LINE)/* V851 By Y.Suzuki 2002/09/19 */
#include	"\src\atlanta\define\unisw_g.h"
#endif


#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\define\ncu_pro.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\define\ncu_msg.h"
#include	"\src\atlanta\define\ncu_ret.h"
#include	"\src\atlanta\define\ncu_cnst.h"
#include	"\src\atlanta\define\ncu_def.h"
#include	"\src\atlanta\define\param.h" /* By S.Kawasaki 1996/06/11 For GBR */

#if (PRO_MODEM == ORANGE3) /* added by H.Kubo 1997/07/23 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/07/23 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#endif

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#if (PRO_CLASS1 == ENABLE)
#include	"\src\atlanta\ext_v\cl1_data.h"
#endif

#include	"\src\atlanta\ext_v\ncu_data.h"
#include	"\src\atlanta\ext_v\ncu_tbl.h"
#include	"\src\atlanta\ext_v\sys_port.h"

#include	"\src\atlanta\sh7043\define\sh_sys.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\define\def_evtn.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include	"\src\atlanta\sh7043\define\def_tib.h"
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/23 */
#include	"\src\atlanta\define\cmn_nd.h"
#endif

#if (PRO_CLASS1 == ENABLE)
 #if (PRO_RS_INTERNAL == ENABLE)
#include "\src\atlanta\define\mntsw_b.h"	/* added by H.Hirao 1999/03/03 */
#include "\src\atlanta\ext_v\cl1_data.h"	/* added by H.Hirao 1999/03/04 */
 #endif
#include	"\src\atlanta\define\cl1_def.h"
#endif

#if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
#include	"\src\atlanta\define\mntsw_f.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\opr\kanji\define\opr_pro.h"
#endif

#if (PRO_NCU_TYPE == HINOKI_TYPE) /* 1999/02/22 by T.Soneoka */
 #if defined(POPLAR_F)
	#include "\src\atlanta\sh7043\ext_v\extv_mon.h"
 #else
	#include "\src\cpu\sh7043_a\irom\ext_v\extv_mon.h"
 #endif
#endif

#if defined(SATSUKI2) /* CI割込み救済 O.Oshima 2003/11/26 */
#include "\src\atlanta\satsuki2\define\satsport.h"
#endif

#if defined(STOCKHM2)
#include "\src\atlanta\stockhm2\define\lvndport.h"
#endif

#if (PRO_RING_MASTER == ENABLE)
static	UBYTE	TeachingStartFlag = 0;
#endif

#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
static	UWORD	CR_RingStartTime = 0;
#endif

#if defined (KEISATSU) /* Added by SMuratec 李 2005/07/14 */
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sys_line.h"
#include "\src\atlanta\ext_v\man_data.h"

/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
extern UWORD	tskno_NCU_ND_Rx;
#endif /* defined (KEISATSU) */

#if defined(JPN)
static	UWORD		tskno_DetectFnetTask		 = 0xFFFF;
static	UWORD		tskno_ToneDetectPattern0Task = 0xFFFF;
static	UWORD		tskno_FilterOnOffDetectTask	 = 0xFFFF;
#endif
static	UWORD		tskno_TimeUpTask			 = 0xFFFF;
static	UWORD		tskno_FrequencyCheckTask	 = 0xFFFF;

#if defined (KEISATSU) /* Added by SMuratec 李 2005/07/01 */
static	UWORD		tskno_DBCITimeUpTask		 = 0xFFFF;
static	UWORD		tskno_DBCIFreqCheckTask		 = 0xFFFF;

UBYTE IsCiSndMsg = 0;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[CIの周波数チェック用タイマ]
	function	:[
		1.大域変数にセットされたタイマ値分ウェイトする
		2.ステータスとイベントをセットし、強制終了を待つ
		3.周波数チェックの時間は、以下の通り

		・CI周波数チェック厳 又は、リングマスター設定
			  NG1	OK			 NG2				 TIMEUP
			┣━╋━━━╋━━━━━━━━━╋━━━━━━━━━━━
			0	16		70					670				  (msec)
			 <-->
			CiMinCycleTime
			 <----------><------------------>
			CiMaxCycleTime	  CiOffTime

		・CI周波数チェック簡
			  OK		OK				 NG2			 TIMEUP
			┣━╋━━━━━━━╋━━━━━━━━━╋━━━━━━━
			0	16				600				   1200		  (msec)
			 <-->
			CiMinCycleTime
			 <------------------><------------------>
				CiMaxCycleTime		  CiOffTime

		 (NG1: WITHIN_MIN_CYCLE, OK: OK_CI_CYCLE, NG2: OVER_MAX_CYCLE)
	]
	return		:[なし]
	common		:[
		UWORD		  RingStatus
		UBYTE TimeStatus
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/07/07]
	author		:[SMUratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_DBCIFreqCheckTask(void)
{
	UWORD timer;
	UBYTE available_ci_det;

	TimeStatus2nd = WITHIN_MIN_CYCLE;
	timer = CiMinCycleTime2nd;						/** CI最小サイクル時間 */

	while (1) {
		/* 疑似２回線で、多機能電話実行中にて、ダイヤルパルス送出にてワンショットタイマを使用するため
		** ダイヤル送出する状態では、ワンショットを使用しません（周波数チェックできない）
		*/
		available_ci_det = 1;
		if (RingStatus2nd & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
			if (((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE) 	/* 標準回線には受話中 */
				|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE) 	/* 標準回線には通信中 */
				|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ){	/* 標準回線には本体使用中 */
				available_ci_det = 0;
			}
		}
		else {	/**	CI検出状態が拡張ラインの場合	*/
			if (((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE) 	/* 拡張回線には受話中 */
				|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE) 	/* 拡張回線には通信中 */
				|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) ){	/* 拡張回線には本体使用中 */
				available_ci_det = 0;
			}
		}
		if (available_ci_det == 0) {
			wai_tsk(1);
			continue;
		}
		/*------------------------------------------------------------*/
		/** まだCIのイベントがセットされていない時､タイマを更新します */
		/*------------------------------------------------------------*/
		wai_tsk((UWORD)((timer / 10) + 1));
		if (TimeStatus2nd == WITHIN_MIN_CYCLE) {
			timer = CiMaxCycleTime2nd;			/** CI最大サイクル時間 */
		}
		else if (TimeStatus2nd == OK_CI_CYCLE) {
			timer = CiOffTime2nd;				/** CI休止時間 */
		}
		else {	/** OVER_MAX_CYCLE */
			RingStatus2nd |= CI_CYCLE_TIMEUP;
			det_evt(EVT_2ND_CI_CHECK);
			wai_tsk(0xFFFF);
		}
		TimeStatus2nd++;
	}
	wai_tsk(0xFFFF);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[CI検出期間のタイマ]
	function	:[
		1.最大検出有効時間ウェイトする
		2.イベントをセットし、強制終了を待つ
	]
	return		:[なし]
	common		:[
		UWORD RingStatus
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/07/07]
	author		:[SMUratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_DBCITimeUpTask(void)
{
	UWORD timer;
	UBYTE detect_time;

	timer = CTRY_RingTable()->DetectTime;		/** 最大検出有効時間 */
	wai_tsk(timer);
	RingStatus2nd |= CI_DETECT_TIMEUP;

	det_evt(EVT_2ND_CI_CHECK);
	wai_tsk(0xFFFF);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[検出リングON時間の取得]
	function	:[
		1.検出リングON時間をバッファにセットする
		2.バッファ･カウンタをインクリメントする
	]
	return		:[なし]
	common		:[
		UWORD SamplingBuff
		UWORD RingingOnTime
	]
	condition	:[]
	comment		:[
		ON期間は物理的に偶数番目にセットされる
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/07/07]
	author		:[SMUratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  Store2ndRingingOnTime(UBYTE *counter)
{
	UWORD					comp_min_on_time;	/* 1999/12/06 by K.Okada */
	
	if (!((*counter) % 2)) {
		if((*counter) < BUFF_MAX ){		/* '96,03,22 By N.S. 1lines insert BUFF_MAX=10 */
			/*--------------------------------------------------------------------------------
			** ・ANS/FAX待機
			** ・TEL2にNTT IM-2400を接続し、着ベル回数1回に設定
			** 上記条件のとき、CNG検出できない不具合が発生。
			** 本体側は最小ON期間中(200ms)、CIが入ってきているとき、呼び出し信号と認識するが、
			** 200msに満たないうちに、TEL2電話器が着信してしまう。
			** よって、最小ON期間を10ms単位で微調整可能にする
			** 1999/12/06 by K.Okada
			*/
			comp_min_on_time = NCU_CI_MinOnTime(); /* 最小ON期間を獲得 */
		
			/*------------------------------------------*/
			/** 200ms以上でないとON期間とは見なしません */		/* 1995/04/21 -> 05/16(Make) */
			/*------------------------------------------*/
			if (RingingOnTime2nd >= comp_min_on_time) {
				SamplingBuff2nd[*counter] = RingingOnTime2nd;
				(*counter)++;
			}
			else {
				if ((*counter) > 0) {	/** OFF期間と見なします */
					SamplingBuff2nd[(*counter) - 1] += (UWORD)(RingingOnTime2nd + RingingOffTime2nd);
				}
			}
		}								/* '96,03,22 By N.S. 1lines insert */
	}
	RingingOnTime2nd = 0;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[検出リングOFF時間の取得]
	function	:[
		1.検出リングON時間をバッファにセットする
		2.バッファ･カウンタをインクリメントする
	]
	return		:[なし]
	common		:[
		UWORD SamplingBuff
		UWORD RingingOffTime
	]
	condition	:[]
	comment		:[
		OFF期間は物理的に奇数番目にセットされる
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/07/07]
	author		:[SMUratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  Store2ndRingingOffTime(UBYTE *counter)
{
	if (RingingOffTime2nd && ((*counter) % 2)) {
		if((*counter) < (BUFF_MAX - 1)){	/* '96,03,22 By N.S. 1lines insert BUFF_MAX=10 */
			SamplingBuff2nd[*counter] = RingingOffTime2nd;
			(*counter)++;
		}									/* '96,03,22 By N.S. 1lines insert */
	}
	RingingOffTime2nd = 0;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[タイマ値の取得]
	function	:[
		1.着信設定状況により、タイマ値をセットする
	]
	return		:[なし]
	common		:[
		UBYTE RingMasterFlag
		UWORD  CiOffTime
		UWORD  CiMaxCycleTime
		UWORD  CiMinCycleTime
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/07/07]
	author		:[SMUratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  Set2ndTimerValue(void)
{
	CiMinCycleTime2nd = CTRY_RingTable()->MinCycle;											/**	 16ms */
	/*-------------------------------------------------*/
	/** CI周波数チェック厳、又はリングマスター設定なら */
	/*-------------------------------------------------*/
	if (CHK_RingFreqAvailable()){
		CiMaxCycleTime2nd = CTRY_RingTable()->MaxCycle - CTRY_RingTable()->MinCycle;			/**	 54ms */
	}
	else {
		CiMaxCycleTime2nd = (CTRY_RingTable()->MaxOffTime)*10 - CTRY_RingTable()->MinCycle;	/** 584ms */
	}
	CiOffTime2nd = (CTRY_RingTable()->MaxOffTime)*10;											/** 600ms */
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[検出リングとマスターリングとのマッチング]
	function	:[
		1.検出リングの合否をリターンする
	]
	return		:[
		#define		NG_RING		リングＮＧ
		#define		OK_RING		リングＯＫ
	]
	common		:[
		UBYTE RingMasterFlag
		UBYTE SYS_RingCounter
	]
	condition	:[]
	comment		:[
		リングマスター検出で、サンプルパターンがＮＧであっても、検出ON期間が
		最小ON期間よりも長ければ、リングカウンターを立てます
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/07/07]
	author		:[SMUratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	 Compare2ndSamplingTone(void)
{
	UBYTE sampling_count;
	UWORD comp_min_on_time;						/* 1999/12/06 by K.Okada */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* CAR を IR と誤検出しないようにする処理。 H.Kubo 1998/10/16 */
	if (SYB_ND_CarPattern[SYS_ND_CAR_IR_MARK_THRESHOLD] > 0) {
		if (SYB_ND_CarPattern[SYS_ND_CAR_IR_MARK_THRESHOLD] < SamplingBuff2nd[0]) {
			if ((NCU_ND_Status & ND_WAIT_FOR_CAR) && (SYS_LineNDStatus == ND_USED_IN_EXT)) {
				return NG_RING;
			}
		}
	}
#endif

	sampling_count = SetSamplingCounter();		/** 検出リングの個数を得る */
												/* sampling_count < BUFF_MAX の関係が
												StoreRingingOn/OffTime()の内部で実現されている。
												 '96,03,22 By N.S. */
/*--------------------------------------------------------------------------------
** ・ANS/FAX待機
** ・TEL2にNTT IM-2400を接続し、着ベル回数1回に設定
** 上記条件のとき、CNG検出できない不具合が発生。
** 本体側は最小ON期間中(200ms)、CIが入ってきているとき、呼び出し信号と認識するが、
** 200msに満たないうちに、TEL2電話器が着信してしまう。
** よって、最小ON期間を10ms単位で微調整可能にする
** 1999/12/06 by K.Okada
*/
	comp_min_on_time = NCU_CI_MinOnTime(); /* 最小ON期間を獲得 */

	/*-----------------------*/
	/** 最小ON期間よりも長い */
	/*-----------------------*/
	if (SamplingBuff2nd[0] >= comp_min_on_time) {
		return (OK_RING);
	}
	return (NG_RING);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信ベル回数の取得]
	function	:[
		1.現待機状態での着信ベル回数をリターンする
	]
	return		:[
		CHK_AllModeToAnsMode()	一般で、内蔵TAD有のTEL待機
		f0						一般で、内蔵TAD無のTEL待機／ANS/FAX待機
		1						サイレント・オペレーション／TADオペレーション中
		CHK_RingCount()			一般
	]
	common		:[
		UBYTE NCU_RxModeSwitch
	]
	condition	:[]
	comment		:[
		ダブルリング着信不許可かつダブルリング検出の時はリターン値に１加えます
		（TEL/FAX待機で着信させないため）
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/07/07]
	author		:[SMUratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE  GetRingCounter(UBYTE line_no)
{
	UBYTE value;

	if (line_no){	/* 拡張回線 */
		if ( SYB_RxModeSwitchExt & SYS_AUTO_CALLED_SW) {
			value = CHK_ExtRingCount();
		}
		else {
			value = 0xf0;
		}
	}
	else{			/* 標準回線 */
		if ( SYB_RxModeSwitch & SYS_AUTO_CALLED_SW ) {
			value = CHK_RingCount();
		}
		else {
			value = 0xf0;
		}
	}

	if (CHK_DoubleRingAvailable() && DoubleRingStatus) {	/* QAT1 1994/08/07 by TH92115 */
		value++;
	}
	return (value);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[他の鳴動回線によって着信ベル回数の取得]
	function	:[
		1.現待機状態での着信ベル回数をリターンする
	]
	return		:[
		CHK_AllModeToAnsMode()	一般で、内蔵TAD有のTEL待機
		f0						一般で、内蔵TAD無のTEL待機／ANS/FAX待機
		1						サイレント・オペレーション／TADオペレーション中
		CHK_RingCount()			一般
	]
	common		:[
		UBYTE NCU_RxModeSwitch
	]
	condition	:[]
	comment		:[
		ダブルリング着信不許可かつダブルリング検出の時はリターン値に１加えます
		（TEL/FAX待機で着信させないため）
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/07/07]
	author		:[SMUratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE  Get2ndRingCounter(UBYTE line_no)
{
	UBYTE value;

	if (line_no){	/* 拡張回線 */
		if ( SYB_RxModeSwitchExt & SYS_AUTO_CALLED_SW) {
			value = CHK_ExtRingCount();
		}
		else {
			value = 0xf0;
		}
	}
	else{			/* 標準回線 */
		if ( SYB_RxModeSwitch & SYS_AUTO_CALLED_SW ) {
			value = CHK_RingCount();
		}
		else {
			value = 0xf0;
		}
	}

	if (CHK_DoubleRingAvailable() && DoubleRingStatus2nd) {	/* QAT1 1994/08/07 by TH92115 */
		value++;
	}
	return (value);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[サンプリング･データの初期化]
	function	:[
		1.着信検出のためのバッファ及びデータを初期化する
	]
	return		:[なし]
	common		:[
		UWORD  SamplingBuff[]
		UBYTE DoubleRingStatus
		UWORD  RingingOnTime
		UWORD  RingingOffTime
		UBYTE Ringing
		UWORD  CI_Counter
		UWORD  CI_OK_Counter
		UWORD  CI_NG_Counter
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/07/07]
	author		:[SMUratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  Initialize2ndGrovalData(void)
{
	UBYTE i;

	for (i = 0; i < BUFF_MAX; i++) {
		SamplingBuff2nd[i] = 0;
	}
	DoubleRingStatus2nd = OFF;		/* Moved by TH92115 1994/09/12 */
	RingingOnTime2nd  = 0;
	RingingOffTime2nd = 0;
	Ringing2nd		   = OFF;
	CI_Counter_2nd	   = 0;
	CI_OK_Counter_2nd  = 0;
	CI_NG_Counter_2nd  = 0;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[連続ベルorダブルリングの判定]
	function	:[
		1.連続ベル着信を判定します
		2.ダブルリングを判定します
	]
	return		:[
		0			連続ベル着信でない
		1			連続ベル着信
	]
	common		:[
		UBYTE DoubleRingStatus
		UWORD  RingingOnTime
		UWORD  RingingOffTime
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/07/07]
	author		:[SMUratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE  Check2ndContinueAndDoubleRing(void)
{
	if ((CHK_ContinueRing())
	 && (RingingOnTime2nd >= CTRY_RingTable()->ContinueTime)) {		/** 連続ベル着信対策 */
		return (1);
	}
	if ((RingingOffTime2nd >= CTRY_RingTable()->DoubleDetect)
	 && (RingingOffTime2nd <= CTRY_RingTable()->MaxOffTime)) {			/** ダブルリング対策 */
		DoubleRingStatus2nd = ON;
	}
	return (0);
}

/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[DetectRingTone のサブルーチン。 CAR 検出用]
	function	:[

	]
	return		:[
		DETECT_CAR
		DETECT_IR_STOP
		FALSE
	]
	common		:[
		NCU_ND_CarPattern
		SYB_ND_CarPattern[]
	]
	condition	:[
			SamplingBuff に、最新の ON 期間が格納されていること。
			OFF 期間状態であること。
	]
	comment		:[
		 DetectRingTone の中での CAR 検出は、二重になった while ループの内側で行うのが基本です。
		なぜなら、 内側のループを抜けるには、 CI_CYCLE_TIMEUP になることが条件ですが、理想的な
		CAR 信号に対しては、その条件が成立しないからです。
		 ところが、 CAR のスペース期間が 60ms より長く見えると、CI_CYCLE_TIMEUP の条件が成立し、
		内側のループは抜けてしまいます。
		 このサブルーチンは、そのような場合に、内側のループから抜けた直後に CAR を検出する処理をします。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/12]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE NCU_CheckCarAt2ndCiCycleTimeup(UWORD ci_end_time, UWORD *ci_start_time, UBYTE *counter)
{
	struct Timer10msEventData_t car_timer;
	UDWORD	timer;
	UBYTE rtn = FALSE;
	

	if (NCU_ND_Status && (SYS_LineNDStatus == ND_USED_IN_EXT)) {
		timer = SYB_ND_CarPattern[SYS_ND_IR_STOP_DETECTION_TIMER] * 10;

		if (*counter > 1) { /* 2 回以上記録している => OffTime のデータが残っている。 */
			if (NCU_IsCarReceived(SamplingBuff2nd[*counter - 1], SamplingBuff2nd[*counter - 2])) {
				rtn = DETECT_CAR;
			}
		}
		else {
			RingStatus2nd &= ~CI_ON;
			car_timer.Time = SYB_ND_CarPattern[SYS_ND_CAR_MAX_OFF_TIME];  /* */
			car_timer.Event = EVT_2ND_CI_CHECK;
			cre_tsk( &tskno_CarOffTimer, TSK_CMN_WATCHTIMER10MSEVENTTASK, &car_timer); /* 最大許容 OFF 期間を過ぎたら、イベントをなげます。 */
			CMN_DisableInterrupt();
			if (!(RingStatus2nd & CI_ON)) {
				wai_evt(EVT_2ND_CI_CHECK);		/** CI､又はタイムアップのイベント待ち */
			}
			CMN_EnableInterrupt();


			if (RingStatus2nd & CI_ON) { /* 最大許容 OFF 期間内に CI が検出された */
				*ci_start_time = SYS_GeneralTimer;
				RingingOffTime2nd = (UWORD) (*ci_start_time - ci_end_time);
				/* 既に OnTime は記録されているはずだから、ここで試してみる。 */
				if (NCU_IsCarReceived(SamplingBuff2nd[*counter - 1], RingingOffTime2nd)) {
					rtn = DETECT_CAR;
				}
				Store2ndRingingOffTime(counter);
			}
			else if (RingStatus2nd & CI_DETECT_TIMEUP) {		/** リングトーン検出時間のタイムアップ */
				rtn = FALSE;
			}
			else if ( (NCU_ND_Status & (ND_CAR_DETECTED | ND_COUNTING_2ND_RING)) && (timer > 0)) { /* ND_CAR_DETECTED を付け加える。 1998/10/22 */
				CMN_DisableInterrupt();
				if ( timer > (UWORD) (SYS_GeneralTimer - ci_end_time) ) {
				/* 呼出音が止まったことを仮検出します。 1998/10/20 */
					car_timer.Time = (UWORD) (timer - ((UWORD) (SYS_GeneralTimer- ci_end_time)));  /* 最初は５秒のタイマー*/
					CMN_EnableInterrupt();
					car_timer.Event = EVT_2ND_CI_CHECK;
					if (tskno_CarOffTimer != 0xffff) {
						del_tsk( &tskno_CarOffTimer);
					}
					cre_tsk( &tskno_CarOffTimer, TSK_CMN_WATCHTIMER10MSEVENTTASK, &car_timer); /* 最大許容 OFF 期間を過ぎたら、イベントをなげます。	 */
					CMN_DisableInterrupt();
					if (!(RingStatus & CI_ON)) {
						wai_evt(EVT_2ND_CI_CHECK);		/** CI､又はタイムアップのイベント待ち */
					}
					CMN_EnableInterrupt();
					if (RingStatus2nd & CI_ON) { /* 最大許容 OFF 期間内に CI が検出された */
						*ci_start_time = SYS_GeneralTimer;
						RingingOffTime2nd = (UWORD) (*ci_start_time - ci_end_time);
						Store2ndRingingOffTime(counter);
						/* 既に OnTime は記録されているはずだから、ここで試してみる。 */
						if (NCU_IsCarReceived(SamplingBuff2nd[*counter - 1], RingingOffTime2nd)) {
							rtn = DETECT_CAR;
						}
					}
					else {
						rtn = DETECT_IR_STOP; /* CAR 停止検出も兼用。 1998/10/22 */
					}
				}
				else {
					rtn = DETECT_IR_STOP;
				}
				CMN_EnableInterrupt();
			}

			if (tskno_CarOffTimer != 0xffff) {
				del_tsk( &tskno_CarOffTimer);
			}
		}
	}
	return rtn;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信検出の実行]
	function	:[
		1.着信条件の合否をリターンする
	]
	return		:[
		#define		RING_NOT_AVAILABLE		着信不可
		#define		CALLED_REQUEST			着信可能
	]
	common		:[
		UWORD  SYS_GeneralTimer
		UWORD  RingingOnTime
		UWORD  RingingOffTime
		UWORD  RingStatus
		UWORD  NCUStatus
		UBYTE Ringing
		UWORD  BranchDetectCounter
		UBYTE FreqStatus
		UWORD  SamplingBuff[]
		UBYTE DoubleRingStatus
		UWORD  CI_OK_Counter
		UWORD  CI_NG_Counter
	]
	condition	:[]
	comment		:[
		一部ブランチ検出に関する処理があります
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_NUMBER_DISPLAY == ENABLE)  /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/20 */	
UBYTE  Detect2ndRingToneAndCar( UWORD mailbox )
#else
UBYTE  Detect2ndRingTone(void)
#endif
{
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
	MESSAGE_t *RxDetectCalledTaskMsg;
#endif
	UWORD  current_time_2nd;
	UWORD  ci_time_2nd;
	UWORD  ci_start_time_2nd;
	UWORD  ci_end_time_2nd;
	UBYTE buff_counter_2nd;
	UBYTE ci_freq_ok_2nd; /* 周期の短い CI 誤検出対策 by H.Kubo 1998/02/09 */
	UBYTE ci_check_2nd;
	UBYTE ci_control_2nd;
	UBYTE wait_ci;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
	UBYTE car_detection_result;
#endif

	ci_freq_ok_2nd	= TRUE; /* 周期の短い CI 誤検出対策 by H.Kubo 1998/02/09 */
	
	ci_start_time_2nd = ci_end_time_2nd = SYS_GeneralTimer;			/** CIスタートorエンド時間の確保 */
	Set2ndTimerValue();										/** 検出リングのタイマ値を得る */
	
	/** タイマタスクの起動 (CiDetectTime and CiMinCycleTime) */
	cre_tsk(&tskno_DBCIFreqCheckTask, TSK_NCU_DBCIFREQCHECKTASK, 0);
	cre_tsk(&tskno_DBCITimeUpTask, TSK_NCU_DBCITIMEUPTASK, 0);

	while (1) {
		Initialize2ndGrovalData();
		buff_counter_2nd = 0;
		ci_freq_ok_2nd = TRUE;

		while (1) {
			wai_evt(EVT_2ND_CI_CHECK);		/** CI､又はタイムアップのイベント待ち */
			/* ここでは呼出中回線によって、他の回線は呼び出し発生させるかどうかの判断です。 */

			current_time_2nd = SYS_GeneralTimer;

			if (tskno_DBCIFreqCheckTask != 0xFFFF) {	/** 周波数チェックタスクの強制終了 */
				del_tsk(&tskno_DBCIFreqCheckTask);
			}
			
			if (RingStatus2nd & CI_DETECT_TIMEUP) {		/** リングトーン検出時間のタイムアップ */
				/*--------------------------------------------------------*/
				/** リングカウンタを初期化し､リングトーン検出を終了します */
				/*--------------------------------------------------------*/
				if (RingStatus2nd & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
					if ( ((NCU_LineStatus & STD_LINE_STATUS) != STD_TEL_RECEIVE)	/* 標準回線には受話中ではない */
						&& ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) ) {	/* 標準回線には本体使用中ではない */
						SYS_RingCounter = 0;
					}
					if ((NCU_LineStatus & STD_LINE_STATUS) == STD_CI_IN) {
						NCU_LineStatus &= ~STD_LINE_STATUS;
						NCU_LineStatus  |= (STD_LINE_STATUS & STD_NOT_USE);
					}
					H_RelayOff();	/**	Hリレー戻します	*/
					if ( !ModemRelaySetting() ) {	/* モデムリレーを標準回線に接続している場合 */
						CONT_24V_Off();
					}
				}
				else {
					if ( ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_TEL_RECEIVE)	/* 拡張回線には受話中ではない */
						&& ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) ) {	/* 拡張回線には本体使用中ではない */
						/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/26 */
						if (DEBUG_NumberDisplay) {
							if ((SYS_LineNDStatus == ND_USED_IN_EXT) && (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR | ND_CALL_ACCEPTED))) {
								NCU_ND_InitializeStatus(); /* 初期状態に戻す */
							}
						}
						SYS_RingCounterExt = 0;
					}
					if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_CI_IN) {
						NCU_LineStatus &= ~EXT_LINE_STATUS;
						NCU_LineStatus  |= (EXT_LINE_STATUS & EXT_NOT_USE);
					}
					L_RelayOff();	/**	Lリレーも戻します	*/
					if ( ModemRelaySetting() ) {	/* モデムリレーを拡張回線に接続している場合 */
						CONT_24V_Off();
					}
				}
				RingStatus2nd &= ~CI_DETECT_TIMEUP;
				return (RING_NOT_AVAILABLE);
			}

			if (RingStatus2nd & CI_CYCLE_TIMEUP) {			/** 周波数チェックのタイムアップ */
				/*-----------------------------------------------*/
				/** CIのOFF期間TIMEUPで､サンプリングを停止します */
				/*-----------------------------------------------*/
				Store2ndRingingOnTime(&buff_counter_2nd);					/** リングON期間の確保 */
				RingStatus2nd &= ~CI_CYCLE_TIMEUP;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
				/* NCU_ND_Status の ND_SUSPICIOUS_CI_DETECTED だけが立ってる時にタイムアップしたら、
				** リセットﾉ処理を追加。
				** by H.Kubo 1998/11/16 */
				if (DEBUG_NumberDisplay) {
					if (NCU_IsCarWaitedFor() && (SYS_LineNDStatus == ND_USED_IN_EXT)) {
						CMN_DisableInterrupt();
						if ((NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR)
						&&   (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED)
						&& !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED)) {
							NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED; /* 偽の CI だったので、落とします。 */
						}
						CMN_EnableInterrupt();
						if  (!(NCU_ND_Status & ~ND_WAIT_FOR_CAR_AND_IR)
						&& ((NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR) == ND_WAIT_FOR_CAR)) {
							/* IR で着信してはいけない */
							cre_tsk(&tskno_DBCIFreqCheckTask, TSK_NCU_DBCIFREQCHECKTASK, 0);
							continue;
						}
					}
				}
#endif
				break;			/** 抜けます */
			}

			if (RingStatus2nd & CI_ON) {					/** とにかくＣＩらしきものを検出 */
				ci_time_2nd = current_time_2nd;								/** CI時間の確保 */
				if ((FreqStatus2nd == WITHIN_MIN_CYCLE) && !CHK_RingFreqAvailable()) {
					FreqStatus2nd = OK_CI_CYCLE;						/** 周波数チェック無の場合は、0～584(ms)をOKの範囲とします */
				}
				/*-------------------------------------------------*/
				/** CIと断定(周波数チェックOK)：ON期間を更新します */
				/*-------------------------------------------------*/
				if (FreqStatus2nd == OK_CI_CYCLE) {
					ci_end_time_2nd = ci_time_2nd;							/** CIエンド時間の更新 */
					RingingOnTime2nd = (UWORD)(ci_end_time_2nd - ci_start_time_2nd);	/** リングON期間の更新 */
					if (Ringing2nd) {		/** 鳴動中 */
						if (Check2ndContinueAndDoubleRing()	/** 連続ベルorダブルリングの判定 */
						||  !CHK_RingFreqAvailable() ) {	/* 周波数検査しない */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
							if (DEBUG_NumberDisplay && NCU_IsCarWaitedFor() && !(NCU_ND_Status & ND_WAIT_FOR_IR)
								&& (SYS_LineNDStatus == ND_USED_IN_EXT)) {
								/* IR で着信してはいけない */
							}
							else
#endif
							if (RingStatus2nd & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
								if ( ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE)	/* 拡張回線には通信中 */
									|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) 	/* 拡張回線には本体使用中 */
									|| (CHK_KEIDENRxPriority() && ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)) ){ /* 警電優先受信ＯＮ及び警電受話中 */
									/* ここで動作しない */
								}
								else {
									return (CALLED_REQUEST);	/**	標準ライン着信	*/
								}
							}
							else {
								if ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE)	/* 標準回線には通信中 */
									|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ){ 	/* 標準回線には本体使用中 */
									if ( (CHK_KEIDENRxPriority())	/* 警電優先受信機能が有効されている場合 */
										&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
										/* 通信中断していない場合 */
										SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
										while ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE)	/* 標準回線には通信中 */
												/* 警察FAX DVT Added by SMuratec 李 2005/12/17 */
												|| (IsJournalCompleted == FALSE)
												|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ){ 	/* 標準回線には本体使用中 */
											wai_tsk(1);
										}
										wai_tsk(1);
										return (CALLED_REQUEST_EXT);	/**	拡張ライン着信	*/
									}
								}
								else {
									return (CALLED_REQUEST_EXT);	/**	拡張ライン着信	*/
								}
							}
						}
					}
					else {				/** 鳴り始めなら */
						Store2ndRingingOffTime(&buff_counter_2nd);			/** リングマスター検出時のOFF期間の確保 */
						Ringing2nd = ON;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
							/* ナンバーディスプレイの CAR を検出 */
						if (DEBUG_NumberDisplay) {
							if (NCU_IsCarWaitedFor() && (SYS_LineNDStatus == ND_USED_IN_EXT)) {
								if (NCU_IsCarReceived(SamplingBuff2nd[buff_counter_2nd-2], SamplingBuff2nd[buff_counter_2nd-1])) {
									SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter_2nd;
									return DETECT_CAR;
								}
								if (SYB_ND_CarPattern[SYS_ND_CAR_COUNTER_THRESHOLD] <= buff_counter_2nd) { /* 呼出し音でないベルが続いたら、 CAR とする。*/
									SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter_2nd;
									return DETECT_CAR;
								}
								ci_start_time_2nd = ci_time_2nd;
							}
						}
#endif
					}
					CI_OK_Counter_2nd++;								/** OKのCIカウンタ */
				}
				/*--------------------------------------------------*/
				/** CIでない(周波数チェックNG)：OFF時間を更新します */
				/*--------------------------------------------------*/
				else {

					RingingOffTime2nd = (UWORD)(ci_time_2nd - ci_end_time_2nd);			/** リングOFF時間の更新 */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
							/* ナンバーディスプレイの CAR を検出 */
					if (DEBUG_NumberDisplay) {
						if (NCU_IsCarWaitedFor() && (SYS_LineNDStatus == ND_USED_IN_EXT)) {  /* CAR 検出してよいか */
							if (NCU_IsCarReceived(RingingOnTime2nd, RingingOffTime2nd)) {
								SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter_2nd;
								return DETECT_CAR;
							}
						}
					}
#endif
					if (Ringing2nd) {		/** 鳴動中 */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
						if (DEBUG_NumberDisplay) {
							if (NCU_IsCarWaitedFor() && (SYS_LineNDStatus == ND_USED_IN_EXT)) {  /* CAR 検出してよいか */
								if (FreqStatus2nd == OVER_MAX_CYCLE) {
									Store2ndRingingOnTime(&buff_counter_2nd);		/** リングマスター検出時のON期間の確保 */
									ci_start_time_2nd = ci_time_2nd;				/** CIスタート時間の更新 */
									Ringing2nd = OFF;
								}
							}
						}
#endif
					}
					else {				/** 鳴り始めなら */
						ci_start_time_2nd = ci_time_2nd;					/** CIスタート時間の更新 */
						Set2ndTimerValue();							/** 検出リングのタイマ値を得る */
					}
					CI_NG_Counter_2nd++;								/** NGのCIカウンタ */
				}
				RingStatus2nd &= ~CI_ON;
				cre_tsk(&tskno_DBCIFreqCheckTask, TSK_NCU_DBCIFREQCHECKTASK, 0);
			}
			continue;
		}

		/*--------------------------------------*/
		/** サンプリング･データの結果判定を行う */
		/*--------------------------------------*/
		/* 呼出し音の検出*/
		if (OK_RING == Compare2ndSamplingTone()) {					/** OKのリングと判断 */
			if (!CHK_DoubleRingAvailable() || !DoubleRingStatus2nd) {
				if (RingStatus2nd & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
					SYS_CalledLineNumber |= SYS_STD_LINE_IN_CI;
					if (!SYS_RingCounter) {
						UpdateLCD();
					}
					SYS_RingCounter++;								/** リングカウンタの更新 */
					if ( (NCU_LineStatus & STD_LINE_STATUS) == STD_NOT_USE ) { /* 標準回線は呼出中ではない */
						NCU_LineStatus &= ~STD_LINE_STATUS;
						NCU_LineStatus  |=  (STD_LINE_STATUS & STD_CI_IN);
					}
 					if (!(SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI)) {
						if ( HDST_RelaySetting() && !(NCU_LineStatus & EXT_HDST_OFFHOOK) ) {	/* 付属電話は拡張回線でオフフックではない */
							if (!(NCUStatus & (HOOK_KEY_ON_STATE | DIALING_STATE))) {
								HDST_RelayOff(); 		/* ハンドセットを標準回線に接続する */
							}
						}
					}
					if (SYS_RingCounter >= 0xf0) {					/** TEL待機､ANS/FAX待機(内蔵TAD無)の対策 */
						SYS_RingCounter = 1;
					}
				}
				else {
					SYS_CalledLineNumber |= SYS_EXT_LINE_IN_CI;
					if (!SYS_RingCounterExt) {
						UpdateLCD();
					}
					SYS_RingCounterExt++;
					if ( (NCU_LineStatus & EXT_LINE_STATUS) == EXT_NOT_USE ) { /* 拡張回線は呼出中ではない */
						NCU_LineStatus &= ~EXT_LINE_STATUS;
						NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_CI_IN);
					}
					/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/30 */
					if ((CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE))
						|| (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
						|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
					}
					else
					if ( !HDST_RelaySetting() && !(NCU_LineStatus & STD_HDST_OFFHOOK) ) {	/* 付属電話は標準回線でオフフックではない */
						if (!(NCUStatus & (HOOK_KEY_ON_STATE | DIALING_STATE))) {
							HDST_RelayOn(); 		/* ハンドセットを拡張回線に接続する */
							/* 警察FAX Added by SMuratec 李 2005/11/09 */
							/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
							UpdateLCD();
						}
					}
					if (SYS_RingCounterExt >= 0xf0) {					/** TEL待機､ANS/FAX待機(内蔵TAD無)の対策 */
						SYS_RingCounterExt = 1;
					}
				}
			}
			else {
				if (RingStatus2nd & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
					SYS_CalledLineNumber |= SYS_STD_LINE_IN_CI;
					if (!SYS_RingCounter) {
						UpdateLCD();
					}
					SYS_RingCounter = 1;
					if ( (NCU_LineStatus & STD_LINE_STATUS) == STD_NOT_USE ) { /* 標準回線は呼出中ではない */
						NCU_LineStatus &= ~STD_LINE_STATUS;
						NCU_LineStatus  |=  (STD_LINE_STATUS & STD_CI_IN);
					}
 					if (!(SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI)) {
						if ( HDST_RelaySetting() && !(NCU_LineStatus & EXT_HDST_OFFHOOK) ) {	/* 付属電話は拡張回線でオフフックではない */
							if (!(NCUStatus & (HOOK_KEY_ON_STATE | DIALING_STATE))) {
								HDST_RelayOff(); 		/* ハンドセットを標準回線に接続する */
							}
						}
					}
				}
				else {
					SYS_CalledLineNumber |= SYS_EXT_LINE_IN_CI;
					if (!SYS_RingCounterExt) {
						UpdateLCD();
					}
					SYS_RingCounterExt = 1;
					if ( (NCU_LineStatus & EXT_LINE_STATUS) == EXT_NOT_USE ) { /* 拡張回線は呼出中ではない */
						NCU_LineStatus &= ~EXT_LINE_STATUS;
						NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_CI_IN);
					}
					/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/30 */
					if ((CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE))
						|| (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
						|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
					}
					else
					if ( !HDST_RelaySetting() && !(NCU_LineStatus & STD_HDST_OFFHOOK) ) {	/* 付属電話は標準回線でオフフックではない */
						if (!(NCUStatus & (HOOK_KEY_ON_STATE | DIALING_STATE))) {
							HDST_RelayOn(); 		/* ハンドセットを拡張回線に接続する */
							/* 警察FAX Added by SMuratec 李 2005/11/09 */
							/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
							UpdateLCD();
						}
					}
				}
			}
			/* 警察FAX DVT_ID18&ID25&ID26 Added by SMuratec 李 2005/11/07 */
			if (SYS_RingCounterExt == 1) {
				UpdateLCD();
			}
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/14 */
			if (DEBUG_NumberDisplay) {
				if (NCU_IsCarWaitedFor() && (SYS_LineNDStatus == ND_USED_IN_EXT)) {  /* CAR 検出してよいか */
					if (SYS_RingCounterExt > 1) { /*ND ON で一般回線接続時、無条件に無鳴動着信しないように。 added by H.Kubo 1998/11/24 */
						CMN_DisableInterrupt();
						NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED;
						CMN_EnableInterrupt();
					}
				}
				if (NCU_ND_Status && (SYS_LineNDStatus == ND_USED_IN_EXT)) {
					if ((NCU_ND_Status & ND_WAIT_FOR_2ND_RING) == ND_WAIT_FOR_2ND_RING) {
						if (SYS_RingCounterExt > 0) {
							return DETECT_FIRST_RING;			/* 呼出し音検出 */
						}
					}
					/* CAR 待ちでいきなり IR が来た場合は、呼出し音二回で DETECT_RING メッセージ送出 1998/10/26 */
					else if (((NCU_ND_Status & ND_WAIT_FOR_IR) && (SYS_RingCounterExt == 1)) /* 2 => 1 by H.Kubo 1998/11/26 /* CAR 待ちで IR がきた時の処理 */
					 || ((NCU_ND_Status & ND_CAR_DETECTED)&& ((SYS_RingCounterExt == 1)))) { /* CAR 検出後にいきなり IR がきた時の処理(OH が来ないときの対策。) added by H.Kubo 1998/10/23 */
						if (!((NCU_ND_Status & ND_CAR_DETECTED) && (SYS_RingCounterExt == 1))) {
							NCU_ND_InitializeStatus();
						}
						else {
							TxDetectCalledTaskMsg.Message = DETECT_RING;
							while (IsCiSndMsg){
								wai_tsk(1);
							}
							if (mailbox == mbxno.NCU_ND) {
								IsCiSndMsg = OK_CONT;
							}
							else {
								IsCiSndMsg = TRUE;
							}
							if (mailbox == mbxno.NCU_ND) {
								snd_msg(mailbox, &TxDetectCalledTaskMsg);
							}
							else if (tskno_NCU_TelephoneOperation != 0xFFFF) {
								snd_msg(mbxno.NCU_TelephoneOperationTask, &TxDetectCalledTaskMsg);
							}
							else {
								snd_msg(mailbox, &TxDetectCalledTaskMsg);
							}
							rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
							IsCiSndMsg = FALSE;
						}
					}
				}
			}
#endif
			if ( (!ci_freq_ok_2nd) && CHK_RingFreqAvailable()) {
				/* Nothing to do.  */
			}
			else if (!CHK_ContinueRing()
				&& ( (SamplingBuff2nd[0] > CTRY_RingTable()->ContinueTime )
					|| (SamplingBuff2nd[0] < CTRY_RingTable()->MinOnTime )
				) ) {
				/* 連続呼出しベル着信でないときは、不正なベルパターンで着信しない。 by H.Kubo 1998/02/10 */
			}
			else {
				if (RingStatus2nd & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
					if (SYS_RingCounter >= SetRingCounter()) {			/** 着信条件を満たした */
						if ( ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE)	/* 拡張回線には通信中 */
							|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) 	/* 拡張回線には本体使用中 */
							|| (CHK_KEIDENRxPriority() && ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)) ){ /* 警電優先受信ＯＮ及び警電受話中 */
							/* ここで動作しない */
						}
						else {
							return (CALLED_REQUEST);	/**	標準ライン着信	*/
						}
					}
				}
				else {
					/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
					if ((NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
						|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
					}
					else
					if (SYS_RingCounterExt >= Get2ndRingCounter(1)) {			/** 着信条件を満たした */
						if ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE)	/* 標準回線には通信中 */
							|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ){ 	/* 標準回線には本体使用中 */
							if ( (CHK_KEIDENRxPriority())	/* 警電優先受信機能が有効されている場合 */
								&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
								/* 通信中断していない場合 */
								SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
								/* 警察FAX DVT_ID42 Added by SMuratec 李 2005/11/16 */
								UpdateLCD();
								while ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE)	/* 標準回線には通信中 */
										|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ){ 	/* 標準回線には本体使用中 */
									wai_tsk(1);
								}
								wai_tsk(1);
								return (CALLED_REQUEST_EXT);	/**	拡張ライン着信	*/
							}
						}
						else {
							return (CALLED_REQUEST_EXT);	/**	拡張ライン着信	*/
						}
					}
				}
			}
		}

#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
		if (DEBUG_NumberDisplay) {
			if (SYS_LineNDStatus == ND_USED_IN_EXT) {  /* CAR 検出してよいか */
				/* CI_CYCLE_TIMEUP で抜けてきた場合の CAR 検出と呼出音停止の検出 */
				car_detection_result = NCU_CheckCarAt2ndCiCycleTimeup(ci_end_time_2nd, &ci_start_time_2nd, &buff_counter_2nd);
				switch (car_detection_result) {
				case DETECT_CAR:
					return DETECT_CAR;
					break;
				case DETECT_IR_STOP:
					/* */ 
					TxDetectCalledTaskMsg.Message = DETECT_2ND_RING_TIMEUP;
					while (IsCiSndMsg){
						wai_tsk(1);
					}
					if (mailbox == mbxno.NCU_ND) {
						IsCiSndMsg = OK_CONT;
					}
					else {
						IsCiSndMsg = TRUE;
					}
					if (mailbox == mbxno.NCU_ND) {
						snd_msg(mailbox, &TxDetectCalledTaskMsg); /* 呼出音検出やめさせる。 */
					}
					else if (tskno_NCU_TelephoneOperation != 0xFFFF) {
						snd_msg(mbxno.NCU_TelephoneOperationTask, &TxDetectCalledTaskMsg);
					}
					else {
						snd_msg(mailbox, &TxDetectCalledTaskMsg); /* 呼出音検出やめさせる。 */
					}
					rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
					IsCiSndMsg = FALSE;
					break;
				default:
#if 0 /* 警察FAX (ナンバーディスプレイ) Modified by SMuratec 李 2005/12/02 */
@@					if (RingStatus & CI_DETECT_TIMEUP) {		/** リングトーン検出時間のタイムアップ */
@@						/*--------------------------------------------------------*/
@@						/** リングカウンタを初期化し､リングトーン検出を終了します */
@@						/*--------------------------------------------------------*/
@@						if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
#else
					if (RingStatus2nd & CI_DETECT_TIMEUP) {		/** リングトーン検出時間のタイムアップ */
						/*--------------------------------------------------------*/
						/** リングカウンタを初期化し､リングトーン検出を終了します */
						/*--------------------------------------------------------*/
						if (RingStatus2nd & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
#endif
							if ( ((NCU_LineStatus & STD_LINE_STATUS) != STD_TEL_RECEIVE)	/* 標準回線には受話中ではない */
								&& ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) ) {	/* 標準回線には本体使用中ではない */
								SYS_RingCounter = 0;
							}
							if ((NCU_LineStatus & STD_LINE_STATUS) == STD_CI_IN) {
								NCU_LineStatus &= ~STD_LINE_STATUS;
								NCU_LineStatus  |=  (STD_LINE_STATUS & STD_NOT_USE);
							}
							H_RelayOff();	/**	Hリレー戻します	*/
							if ( !ModemRelaySetting() ) {	/* モデムリレーを標準回線に接続している場合 */
								CONT_24V_Off();
							}
						}
						else {
							if ( ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_TEL_RECEIVE)	/* 拡張回線には受話中ではない */
								&& ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) ) {	/* 拡張回線には本体使用中ではない */
								/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
								if (DEBUG_NumberDisplay) {
									if ((SYS_LineNDStatus == ND_USED_IN_EXT) && (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR | ND_CALL_ACCEPTED))) {
										NCU_ND_InitializeStatus(); /* 初期状態に戻す */
									}
								}
								SYS_RingCounterExt = 0;
							}
							if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_CI_IN) {
								NCU_LineStatus &= ~EXT_LINE_STATUS;
								NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_NOT_USE);
							}
							L_RelayOff();	/**	Lリレーも戻します	*/
							if ( ModemRelaySetting() ) {	/* モデムリレーを拡張回線に接続している場合 */
								CONT_24V_Off();
							}
						}
#if 0 /* 警察FAX (ナンバーディスプレイ) Modified by SMuratec 李 2005/12/02 */
@@						RingStatus &= ~CI_DETECT_TIMEUP;
#else
						RingStatus2nd &= ~CI_DETECT_TIMEUP;
#endif
						return (RING_NOT_AVAILABLE);
					}
					break;
				}
			}
		}
#endif

		/** ２波目以降の検出タイマの再起動 */
		del_tsk(&tskno_DBCITimeUpTask);
		cre_tsk(&tskno_DBCITimeUpTask, TSK_NCU_DBCITIMEUPTASK, 0);
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信検出をしてもよい条件]
	function	:[
		1.ＣＩ検出の許可を判定し、リターンします
	]
	return		:[
		0			着信禁止
		1			着信許可
	]
	common		:[
		UBYTE RingBuzzerFlag
		UBYTE CI_DummyFlag
		UWORD  NCUStatus
		UWORD  SYS_RingCounter
		UWORD  OhPortStatus
		UWORD  Tel1OhCounter
		UWORD  Tel2OhCounter
		UWORD  BRCOhTelCounter
		UWORD  AfterCI_HL_RelayOn
	]
	condition	:[]
	comment		:[
		Ｈ８の場合、内線通話中及びCI_DummyFlagがONの時は、
		無条件で検出許可をリターンします
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE  CiCheckRequest2nd(void)
{
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
	if (DEBUG_NumberDisplay) {
		if (NCU_ND_Status && (SYS_LineNDStatus == ND_USED_IN_EXT))  { /* CHK_NumberDisplayON() is Changed by H.Kubo 1998/11/28 */
			if ((NCU_ND_Status  & ND_WAIT_FOR_CAR_AND_IR)) {
				SYS_RingCounterExt = 0;
			}
			else if ((SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & (SYS_ND_SILENT_WHILE_IR_DETECT | SYS_ND_COUNT_HEARABLE_IR))
					 == (SYS_ND_SILENT_WHILE_IR_DETECT | SYS_ND_COUNT_HEARABLE_IR)) {
				SYS_RingCounterExt = 0; /* added by H.Kubo 1998/11/28 */
			}
			else {
			}
		}
		else {
			SYS_RingCounterExt = 0;
		}
	}
	else {
		SYS_RingCounterExt = 0;
	}
#else
	SYS_RingCounterExt = 0;
#endif

 	if (RingStatus2nd & CI_STD_LINE) {
		if (NCUStatus & TELEPHONE1_OFF_HOOK) {
			if (!(Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
				Tel1OhCounter = 40;
			}
			CI_Counter_2nd = 0;
			return (0);
		}
		if (!ModemRelaySetting()){ /* モデムを標準回線に接続されている場合 */
			/** CMLリレーがOFFで、リレー動作直後でないなら */
			if (!CML_RelaySetting() && !AfterCI_HL_RelayOn) {
				return (1);			/** CI検出許可	*/
			}
		}
		else {
			return (1);			/** CI検出許可	*/
		}
	}
	else {
		if (CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が拡張ラインの場合	*/
			if (NCUStatus & TELEPHONE2_OFF_HOOK) {
				if (!(Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))) {	/* '96,04,15 10ms単位--->100ms単位 NEWMEM By N.S. *//* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
					Tel2OhCounter = 40;
				}
				CI_Counter_2nd = 0;
				return (0);
			}
		}
#if 0 /* 警察FAX DVT_ID65 Added by SMuratec 李 2005/12/13 */
@@		if (ModemRelaySetting()){ /* モデムを拡張回線に接続されている場合 */
#else
		if (SYS_InternalLineNumber == SYS_EXT_LINE_COM) {
#endif
			/** CMLリレーがOFFで、リレー動作直後でないなら */
			if (!CML_RelaySetting() && !AfterCI_HL_RelayOn) {
				return (1);			/** CI検出許可	*/
			}
		}
		else {
			return (1);			/** CI検出許可	*/
		}
	}
	CI_Counter_2nd = 0;				/* 1994/10/25 */
	return (0);					/** CI検出不許可  */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信検出タスク]
	function	:[
		1.１発目のＣＩ、又はＦネット着信のイベントを待つ
		2.親タスクに着信検出状況を通知する
	]
	return		:[なし]
	common		:[
		UBYTE CI_DummyFlag
		UWORD  RingStatus
	]
	condition	:[]
	comment		:[
		Ｈ８の場合、タスクのクリエイト時にＣＩのタイムアップ時間、
		SYS_RingCounterを保持します
		この間の自動発呼は不可となります
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_Detect2ndCalledTask(WORD *tx_mail_box_no)
{
	MESSAGE_t *RxDetectCalledTaskMsg;

	RingStatus2nd = RING_STATUS_INITIAL;

	TxDetectCalledTaskMsg.Item = FROM__NCU_RING;

	tskno_DBCITimeUpTask		 = 0xFFFF;
	tskno_DBCIFreqCheckTask		 = 0xFFFF;

	Initialize2ndGrovalData();

	while (1) {
		/*--------------------------------------------------------------------------------*/
		/** 以下を実現するために追加							1994/08/20	  TH92115	  */
		/** ・着信不可ではじかれている間に受話器をオフフックされてもSYS_RingCounterを保存 */
		/** ・着信不可ではじかれた直後にＣＩがなくてもSYS_RingCounterをタイムアップで消去 */
		/** 但し、一度待機に戻ると約１０秒間は自動発呼しません(PRE_LINE_BUSYが立っている) */
		/*--------------------------------------------------------------------------------*/
		wai_evt(EVT_2ND_CI_CHECK);		/**	１発目のＣＩ、又はＦネット着信のイベントを待つ */

		if (RingStatus2nd & CI_ON) {					/** １発目のＣＩを検出 */
			if (CiCheckRequest2nd()) {					/** ＣＩチェックをしてもよい条件なら */
 				if (!(NCUStatus & DETECT_CI_STATE)) {
					NCUStatus |= DETECT_CI_STATE;
					/*-----------------------------*/
					/** ＣＩ検出中であることを通知 */
					/*-----------------------------*/
					TxDetectCalledTaskMsg.Message = DETECT_CI;
					while (IsCiSndMsg){
						wai_tsk(1);
					}
					if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
						IsCiSndMsg = TRUE;
						if (tskno_NCU_TelephoneOperation != 0xFFFF) {
							snd_msg(mbxno.NCU_TelephoneOperationTask, &TxDetectCalledTaskMsg);
						}
						else {
							snd_msg(*tx_mail_box_no, &TxDetectCalledTaskMsg);
						}
						rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
						IsCiSndMsg = FALSE;
					}
				}
				/*---------------------------------*/
				/**	２発目以降のＣＩ検出を行います */		/* 1994/10/24 */
				/*---------------------------------*/
#if (PRO_NUMBER_DISPLAY == ENABLE)  /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
				switch (Detect2ndRingToneAndCar(*tx_mail_box_no)) {
#else
				switch (Detect2ndRingTone()) {
#endif
				case CALLED_REQUEST:		/** 着信!! */
					TxDetectCalledTaskMsg.Message = DETECT_CALLED_REQUEST;
					break;
				case CALLED_REQUEST_EXT:		/** 疑似２回線 拡張ライン着信 by T.Soneoka 1997/11/21 */
					TxDetectCalledTaskMsg.Message = DETECT_CALLED_REQUEST_EXT;
					break;
				case RING_NOT_AVAILABLE:	/** タイムアップ */
					if (!(RingStatus & (CI_STD_LINE | CI_EXT_LINE))) {
						AfterCI_TimerSet();
					}
					TxDetectCalledTaskMsg.Message = DETECT_CI_TIMEUP;
					break;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
				case DETECT_CAR:
					if (DEBUG_NumberDisplay) {
						TxDetectCalledTaskMsg.Message = DETECT_ND_CAR_CALLED_SIGNAL;
					}
					break;
				case DETECT_FIRST_RING:     /** IR の第一波を検出 added by H.Kubo 1998/09/18 */
					if (DEBUG_NumberDisplay) {
						TxDetectCalledTaskMsg.Message = DETECT_RING;
					}
					break;
#endif
				default:
					break;
				}
				Det2ndCallChildTaskExit();					/* 1994/09/26 */
				while (IsCiSndMsg){
					wai_tsk(1);
				}
				if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)
					&& !((RingStatus & (CI_STD_LINE | CI_EXT_LINE))
					&& (TxDetectCalledTaskMsg.Message == DETECT_CI_TIMEUP))) {
#if 0 /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/20 */
**					IsCiSndMsg = TRUE;
#else
					if (DEBUG_NumberDisplay) {
						if (*tx_mail_box_no == mbxno.NCU_ND) {
							IsCiSndMsg = OK_CONT;
						}
						else {
							IsCiSndMsg = TRUE;
						}
					}
					else {
						IsCiSndMsg = TRUE;
					}
					if (DEBUG_NumberDisplay && (*tx_mail_box_no == mbxno.NCU_ND)) {
						snd_msg(*tx_mail_box_no, &TxDetectCalledTaskMsg);
					}
					else
#endif
					if (tskno_NCU_TelephoneOperation != 0xFFFF) {
						snd_msg(mbxno.NCU_TelephoneOperationTask, &TxDetectCalledTaskMsg);
					}
					else {
						snd_msg(*tx_mail_box_no, &TxDetectCalledTaskMsg);
					}
					rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
					IsCiSndMsg = FALSE;
				}
				else {
					/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/04 */
					if (DEBUG_NumberDisplay) {
						if (TxDetectCalledTaskMsg.Message == DETECT_CI_TIMEUP) {
							if (SYS_LineNDStatus != ND_USED_IN_EXT) {	/**	標準回線	*/
								SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
							}
						}
					}
					UpdateLCD();
				}
			}
			/* 2回線呼出監視仕様変更 Deleted by SMuratec 李 2005/10/19 */
			else {
				if ( ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_COM_IN_USE)	/* 拡張回線には通信中 */
					&& ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) ){ 	/* 拡張回線には本体使用中 */
					L_RelayOff();	/**	Lリレー戻します	*/
				}
			}
		}
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信検出タスクの子タスク終了ルーチン]
	function	:[
		1.子タスクを強制終了し、ステータスを戻す
	]
	return		:[なし]
	common		:[
		UWORD  NCUStatus
		UWORD  RingStatus
		UBYTE Ringing
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  Det2ndCallChildTaskExit(void)
{
	if (tskno_DBCIFreqCheckTask != 0xFFFF) {
		del_tsk(&tskno_DBCIFreqCheckTask);
	}
	if (tskno_DBCITimeUpTask != 0xFFFF) {
		del_tsk(&tskno_DBCITimeUpTask);
	}
	Ringing2nd = OFF;
	CI_Counter_2nd = 0;			/* 1994/10/25 */
#if 0 /* 警察FAX DVT_ID18&25&26 Modify by SMuratec 李 2005/11/14 */
@@	if (RingStatus2nd & CI_STD_LINE) {
@@		SYS_CalledLineNumber &= ~SYS_STD_LINE_IN_CI;
@@	}
@@	else {
@@		SYS_CalledLineNumber &= ~SYS_EXT_LINE_IN_CI;
@@	}
#else
		SYS_CalledLineNumber &= ~SYS_EXT_LINE_IN_CI;
#endif
#if 0 /* 2回線呼出監視仕様変更 Modified by SMuratec 李 2005/10/19 */
**	if (SYS_CalledLineNumber & SYS_TWICE_LINE_IN_CI) {
**		RingStatus2nd = RING_STATUS_INITIAL;
**	}
**	else {
**		RingStatus		= RING_STATUS_INITIAL;
**		RingStatus2nd 	= RING_STATUS_INITIAL;
**	}
#else
	if (IsCiSndMsg = OK_CONT) { /* ナンバーディスプレイ Modified by SMuratec 李 2005/10/20 */
		IsCiSndMsg = FALSE;
	}
	RingStatus2nd 	= RING_STATUS_INITIAL;
#endif
	if ( !(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK)) ) {	/* 付属電話はフフックではない */
		NCU_HdstShift();
	}

	if (!(SYS_CalledLineNumber & SYS_TWICE_LINE_IN_CI)) {
		NCUStatus &= ~(DETECT_CI_STATE | DETECT_INTER_CI_STATE);
	}
	
	Initialize2ndGrovalData();
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
	if (DEBUG_NumberDisplay) {
		if (tskno_CarOffTimer != 0xFFFF) {
			del_tsk(&tskno_CarOffTimer);
		}
	}
#endif
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信検出タスクの強制終了ルーチン]
	function	:[
		1.見ての通りです
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/10/26]
	author		:[SMuratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_Detect2ndCalledExit(void)
{
	Det2ndCallChildTaskExit();
	exi_tsk();
}

#endif /* defined (KEISATSU) */



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[Ｆ網(1300Hz)着信監視タスク]
	function	:[
		1.ATD_ToneDetectPattern0Taskからのメッセージを待ちます
		2.ATD_FilterOnOffDetectTaskは､V53のみ起動させます
	]
	return		:[なし]
	common		:[
		UBYTE RingStatus;
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_MODEM == R288F)
CONST UBYTE NCU_DEBUG_FilterTest = 0;
#endif
void	NCU_DetectFnetTask(void)
{
#if defined(JPN)
	MESSAGE_t *rx_message;
	struct ToneDetectMailBoxData_t f_net_data;
	UBYTE	  detect_tone_type;

	detect_tone_type	= F_NET_TONE_DETECT;		/** ATD_FilterOnOffDetectTaskのトーンタイプをセット */
	f_net_data.ToneType = F_NET_TONE;				/** ATD_ToneDetectPattern0Taskの返り値をセット */
	f_net_data.SendMBX	= mbxno.NCU_DetectFnetTask;

#if (PRO_MODEM == R288F)
	if ( NCU_DEBUG_FilterTest) {
		AnalogSwitchRXA_Set();
		MDM_FilterSetCNG();
		f_net_data.ToneType = CNG_TONE;	/** ATD_ToneDetectPattern0Taskの返り値をセット */
	}
	else {
		/* MDM_ToneModeConfig(); */	/* add 1998/02/10 by O.Kimoto */ /* Deleted by H.Kubo 1998/02/18 */
		MDM_FilterSet(F_NET_FILTER);					/** Ｆネット検出用フィルターセット */
	}
#endif

	cre_tsk(&tskno_ToneDetectPattern0Task, TSK_ATD_TONEDETECTPATTERN0TASK, &f_net_data);

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1007/09/05 */
	cre_tsk(&tskno_FilterOnOffDetectTask, TSK_ATD_FILTERONOFFDETECTTASK, &detect_tone_type);
#endif /* (PRO_MODEM == ORANGE3) */

	while (1) {
		rcv_msg(mbxno.NCU_DetectFnetTask, &rx_message);
		switch (rx_message->Message) {
		case F_NET_TONE:
			FnetChildTaskExit();

#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/12/29 */
			if ( (CHK_1300RxAvailable() || CHK_F_NetSubscriber())
				&& !DTMF_Decision()		/* DTMF を 1300Hz と誤検出する対策 */
			) {
				RingStatus |= F_NET_CALLED_SIGNAL;
				det_evt(EVT_CI_CHECK);
				wai_tsk(0xFFFF);
			}
#else
			if (CHK_1300RxAvailable() || CHK_F_NetSubscriber()) {
				RingStatus |= F_NET_CALLED_SIGNAL;
				det_evt(EVT_CI_CHECK);
				wai_tsk(0xFFFF);
			}
#endif /* (PRO_MODEM == R288F) */
			else {
				cre_tsk(&tskno_ToneDetectPattern0Task, TSK_ATD_TONEDETECTPATTERN0TASK, &f_net_data);
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1007/09/05 */
				cre_tsk(&tskno_FilterOnOffDetectTask, TSK_ATD_FILTERONOFFDETECTTASK, &detect_tone_type);
#endif /* (PRO_MODEM == ORANGE3) */
			}
			break;
		default:
			break;
		}
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/12/29 */
		while (DTMF_Decision()) {		/* DTMF を 1300Hz と誤検出する対策 */
			wai_tsk(1); /* DTMF が検出されていれば、10ms 待ってみる */
		}
#endif /* (PRO_MODEM == R288F) */


	}	/* while (1) */

#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[Ｆネット検出タスクの子タスク終了ルーチン]
	function	:[
		1.子タスクを強制終了する
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  FnetChildTaskExit(void)
{
#if defined(JPN)
	if (tskno_ToneDetectPattern0Task != 0xFFFF) {
		del_tsk(&tskno_ToneDetectPattern0Task);
	}
	if (tskno_FilterOnOffDetectTask != 0xFFFF) {
		del_tsk(&tskno_FilterOnOffDetectTask);
	}
#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[CIの周波数チェック用タイマ]
	function	:[
		1.大域変数にセットされたタイマ値分ウェイトする
		2.ステータスとイベントをセットし、強制終了を待つ
		3.周波数チェックの時間は、以下の通り

		・CI周波数チェック厳 又は、リングマスター設定
			  NG1	OK			 NG2				 TIMEUP
			┣━╋━━━╋━━━━━━━━━╋━━━━━━━━━━━
			0	16		70					670				  (msec)
			 <-->
			CiMinCycleTime
			 <----------><------------------>
			CiMaxCycleTime	  CiOffTime

		・CI周波数チェック簡
			  OK		OK				 NG2			 TIMEUP
			┣━╋━━━━━━━╋━━━━━━━━━╋━━━━━━━
			0	16				600				   1200		  (msec)
			 <-->
			CiMinCycleTime
			 <------------------><------------------>
				CiMaxCycleTime		  CiOffTime

		 (NG1: WITHIN_MIN_CYCLE, OK: OK_CI_CYCLE, NG2: OVER_MAX_CYCLE)
	]
	return		:[なし]
	common		:[
		UWORD		  RingStatus
		UBYTE TimeStatus
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_FrequencyCheckTask(void)
{
	UWORD timer;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/3 */
	UBYTE available_ci_det;
#endif

	TimeStatus = WITHIN_MIN_CYCLE;
	timer = CiMinCycleTime;						/** CI最小サイクル時間 */

	while (1) {
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/3 */
		/* 疑似２回線で、多機能電話実行中にて、ダイヤルパルス送出にてワンショットタイマを使用するため
		** ダイヤル送出する状態では、ワンショットを使用しません（周波数チェックできない）
		*/
		available_ci_det = 1;
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/08 */
		if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
			if (((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE) 	/* 標準回線には受話中 */
				|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE) 	/* 標準回線には通信中 */
				|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ){	/* 標準回線には本体使用中 */
				available_ci_det = 0;
			}
		}
		else {	/**	CI検出状態が拡張ラインの場合	*/
			if (((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE) 	/* 拡張回線には受話中 */
				|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE) 	/* 拡張回線には通信中 */
				|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) ){	/* 拡張回線には本体使用中 */
				available_ci_det = 0;
			}
		}
		if (available_ci_det == 0) {
			wai_tsk(1);
			continue;
		}
 #else /* !defined (KEISATSU) */
		if (!CHK_Phone2ExtLineOn()) {
			if (CHK_UNI_TEL2_TEL1Action()) {
				if ((OhPortStatus & (TEL1_OFF_HOOK | TEL2_OFF_HOOK))
				||  (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK))) {
					available_ci_det = 0;
				}
			}
			else {
				if ((OhPortStatus & TEL1_OFF_HOOK)
				||  (NCUStatus & TELEPHONE1_OFF_HOOK)) {
					available_ci_det = 0;
				}
			}
			if (NCUStatus & HOOK_KEY_ON_STATE) {
				available_ci_det = 0;
			}
		}
		else {
			if ((OhPortStatus & TEL1_OFF_HOOK)
			||  (NCUStatus & TELEPHONE1_OFF_HOOK)) {
				available_ci_det = 0;
			}
			if (NCUStatus & HOOK_KEY_ON_STATE) {
				available_ci_det = 0;
			}
		}
		if ((available_ci_det == 0)
		&& (CHK_UNI_TelOpeDialTx())) {
			wai_tsk(1);
			continue;
		}
 #endif /* defined (KEISATSU) */
#endif
		/*------------------------------------------------------------*/
		/** まだCIのイベントがセットされていない時､タイマを更新します */
		/*------------------------------------------------------------*/
/*
** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
** 確認して使用することにする
** 1999/02/22 by T.Soneoka
*/
#if (PRO_NCU_TYPE == HINOKI_TYPE)
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/15 */
		wai_tsk((UWORD)((timer / 10) + 1));
#else /* defined (KEISATSU) */
		if (wai_1shot_tid == 0xFF) {
			wai_oneshot(timer);
		}
		else {
			wai_tsk((UWORD)((timer / 10) + 1));
		}
#endif /* defined (KEISATSU) */
#else
		wai_oneshot(timer);
#endif
		if (TimeStatus == WITHIN_MIN_CYCLE) {
			timer = CiMaxCycleTime;			/** CI最大サイクル時間 */
		}
		else if (TimeStatus == OK_CI_CYCLE) {
			timer = CiOffTime;				/** CI休止時間 */
		}
		else {	/** OVER_MAX_CYCLE */
			RingStatus |= CI_CYCLE_TIMEUP;
			det_evt(EVT_CI_CHECK);
			wai_tsk(0xFFFF);
		}
		TimeStatus++;
	}
	wai_tsk(0xFFFF);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[CI検出期間のタイマ]
	function	:[
		1.最大検出有効時間ウェイトする
		2.イベントをセットし、強制終了を待つ
	]
	return		:[なし]
	common		:[
		UWORD RingStatus
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_TimeUpTask(void)
{
	UWORD timer;
	UBYTE detect_time;

#if defined(POPLAR_H) && defined(JP0)/*V851 CI検出から早く抜ける。  By Y.Suzuki 2002/09/19*/
	if (detect_time = CHK_UNI_CHG_CI_DetectTime()) {/* CI 検出時間を短縮する。 */
		if(detect_time == CI_DETECT_TIME_7S) {
			timer = 700;
		}
		else {
			timer = 500;
		}
	}
	else {
		timer = CTRY_RingTable()->DetectTime;		/** 最大検出有効時間 */
	}
#else
	timer = CTRY_RingTable()->DetectTime;		/** 最大検出有効時間 */
#endif
	/*timer = CTRY_RingTable()->DetectTime;		@** 最大検出有効時間 */
	wai_tsk(timer);
	RingStatus |= CI_DETECT_TIMEUP;

	det_evt(EVT_CI_CHECK);
	wai_tsk(0xFFFF);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[タイマ値の取得]
	function	:[
		1.着信設定状況により、タイマ値をセットする
	]
	return		:[なし]
	common		:[
		UBYTE RingMasterFlag
		UWORD  CiOffTime
		UWORD  CiMaxCycleTime
		UWORD  CiMinCycleTime
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  SetTimerValue(void)
{
#if (PRO_RING_MASTER == ENABLE)
 #if defined(AUS)	/* DUET 1997/05/21 Y.Murata */
	if (CMN_PresentReceiveMode() == SYS_FAX_READY) {
		RingMasterFlag = CHK_RingMasterON();
	}
	else {
		RingMasterFlag = 0;
	}
 #else
	RingMasterFlag = CHK_RingMasterON();
 #endif
#endif
	CiMinCycleTime = CTRY_RingTable()->MinCycle;											/**	 16ms */
	/*-------------------------------------------------*/
	/** CI周波数チェック厳、又はリングマスター設定なら */
	/*-------------------------------------------------*/
#if (PRO_RING_MASTER == ENABLE)
	if (CHK_RingFreqAvailable() || RingMasterFlag) {
		CiMaxCycleTime = CTRY_RingTable()->MaxCycle - CTRY_RingTable()->MinCycle;			/**	 54ms */
	}
#else
	if (CHK_RingFreqAvailable()){
		CiMaxCycleTime = CTRY_RingTable()->MaxCycle - CTRY_RingTable()->MinCycle;			/**	 54ms */
	}
#endif
	else {
		CiMaxCycleTime = (CTRY_RingTable()->MaxOffTime)*10 - CTRY_RingTable()->MinCycle;	/** 584ms */
	}
	CiOffTime = (CTRY_RingTable()->MaxOffTime)*10;											/** 600ms */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信ベル回数の取得]
	function	:[
		1.現待機状態での着信ベル回数をリターンする
	]
	return		:[
		CHK_AllModeToAnsMode()	一般で、内蔵TAD有のTEL待機
		f0						一般で、内蔵TAD無のTEL待機／ANS/FAX待機
		1						サイレント・オペレーション／TADオペレーション中
		CHK_RingCount()			一般
	]
	common		:[
		UBYTE NCU_RxModeSwitch
	]
	condition	:[]
	comment		:[
		ダブルリング着信不許可かつダブルリング検出の時はリターン値に１加えます
		（TEL/FAX待機で着信させないため）
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE  SetRingCounter(void)
{
	UBYTE value;

	/*--------------------------------------------------------------------*/
	/** TAD動作中はリングカウンタ１回で返し、待機状態より再検出を行います */
	/*--------------------------------------------------------------------*/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TAD) {
		value = 1;
	}
#if (PRO_NUMBER_DISPLAY == ENABLE) /* モデムダィヤルイン時の呼出音停止検出処理変更により。added by H.Kubo 1998/12/14 */
	else if (NCU_ND_Status & (ND_MODEM_DIALIN_TEL1_DIAL | ND_MODEM_DIALIN_TEL2_DIAL)) {
		value = 0xf0;
	}
#endif
	else {
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/20 */
		if ( SYB_RxModeSwitch & SYS_AUTO_CALLED_SW ) {
			NCU_RxModeSwitch = SYS_FAX_READY;
		}
		else {
			NCU_RxModeSwitch = SYS_TEL_READY;
		}
#else /* !defined (KEISATSU) */
		NCU_RxModeSwitch = CMN_PresentReceiveMode();
#endif /* defined (KEISATSU) */
		if ((NCU_RxModeSwitch == SYS_TEL_READY)
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/27 */
		 || ((NCU_RxModeSwitch == SYS_MODEM_DIALIN_READY) 
		 	&& !(NCU_ND_Status & ND_MODEM_DIALIN_DIAL) && (SYB_DialInNoNumberSignal == 0))
#endif
		 || (NCU_RxModeSwitch == SYS_ANS_FAX_READY)) {
#if (PRO_BUILTIN_TAD == ENABLE)
			if (CHK_TelModeToAnsMode() && CHK_AllModeToAnsMode()) {
				value = CHK_TAD_RemoteAnsBellNum();
			}
			else {
				value = 0xf0;
			}
#else
			value = 0xf0;
#endif
		}
		else {
			if (SilentReceiveRequest()) {	/** サイレントオペレーション */
/* #if defined(GBR) || defined(NLD) || defined(EC1)			@* Add by Th92115 1995/07/26 */
#if defined(GBR) || defined(EC1)			/* By Y.Suzuki 1998/09/18 */
/*				if (SYS_MachineParameter[COUNTRY_CODE] == 7) {  */
 #if defined(EC1)
				if (SYB_MachineParameter[COUNTRY_CODE] == 0 || SYB_MachineParameter[COUNTRY_CODE] == 7) {  /* for BEL/DNK 98/04/09 */
 #else
				if (SYB_MachineParameter[COUNTRY_CODE] == 7) {  /* とりあえずSYS_ をSYB_ に変更。DipSwitchの値は検討要 By S.Fukui Sep.17,1997 */
 #endif
					value = 2;
				}
				else {
					value = 1;
				}
/* 1996/10/17 By N.Sakamoto
@elif defined(AUS)  @* 1996/08/29 by H.Yagi *@
				value = 2;
------------------------------------------------*/
#else
	#if defined(AUS)	/* 1996/10/17 By N.Sakamoto */
				if (SYB_MachineParameter[0] == 0 ) {	/* AUS */
					value = 2;
				}
				else{									/* THA,SGP */
					value = 1;
				}
	#else
		#if defined(FRA)		/* add by M.HARADA '96/10/31 AnzuFra */
				value = 2;
		#else
				value = 1;
		#endif
	#endif
#endif
			}
			else {
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/14 */
				value = GetRingCounter(0);
#else /* (!defined(LVNDR2)) */
				value = CHK_RingCount();
#endif /* defined (KEISATSU) */
			}
		}
	}
	if (CHK_DoubleRingAvailable() && DoubleRingStatus) {	/* QAT1 1994/08/07 by TH92115 */
		value++;
	}
	return (value);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ＣＩのON/OFFパターンをサンプリングする個数の取得]
	function	:[
		1.リングマスター設定の時、リングのON/OFF個数をリターンする
		2.一般の場合、(便宜的に)１をリターンする
	]
	return		:[
		1			一般
		3			リングマスターのパターンＡ／Ｄ
		5			リングマスターのパターンＢ／Ｃ／Ｅ／Ｆ
	]
	common		:[
		UBYTE RingMasterFlag
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	SetSamplingCounter(void)
{
#if (PRO_RING_MASTER == ENABLE)
	if (RingMasterFlag) {
 #if defined(AUS)	/* DUET 1997/05/21 Y.Murata */
			return (5);
 #else
		switch (CHK_RingMasterPattern()) {
		case RING_MASTER_PATTERN_1:
		case RING_MASTER_PATTERN_4:
			return (3);
			break;
		case RING_MASTER_PATTERN_2:
		case RING_MASTER_PATTERN_3:
		case RING_MASTER_PATTERN_5:
		case RING_MASTER_PATTERN_6:
			return (5);
			break;
		case RING_MASTER_PATTERN_7:		/* 1995/05/24 */
			if (SYB_RingG_SetNumber) {
				return (SYB_RingG_SetNumber);

	/* SYB_RingG_SetNumber < BUFF_MAX の関係がStoreRingingOn/OffTime()の内部で実現されている。'96,03,22 By N.S. */
			}
			return (3);
			break;
		case RING_MASTER_PATTERN_8:		/* 1995/05/24 */
			if (SYB_RingH_SetNumber) {
				return (SYB_RingH_SetNumber);

	/* SYB_RingH_SetNumber < BUFF_MAX の関係がStoreRingingOn/OffTime()の内部で実現されている。'96,03,22 By N.S. */
			}
			return (3);
			break;
		default:
			return (1);
			break;
		}
 #endif
	}
	else {
#endif
		return (1);
#if (PRO_RING_MASTER == ENABLE)
	}
#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[検出リングとマスターリングとのマッチング]
	function	:[
		1.検出リングの合否をリターンする
	]
	return		:[
		#define		NG_RING		リングＮＧ
		#define		OK_RING		リングＯＫ
	]
	common		:[
		UBYTE RingMasterFlag
		UBYTE SYS_RingCounter
	]
	condition	:[]
	comment		:[
		リングマスター検出で、サンプルパターンがＮＧであっても、検出ON期間が
		最小ON期間よりも長ければ、リングカウンターを立てます
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	 CompareSamplingTone(void)
{
#if (PRO_RING_MASTER == ENABLE)					/* '96/10/01 By N.Sakamoto */
	UBYTE i;
#endif
	UBYTE sampling_count;
	UWORD comp_min_on_time;						/* 1999/12/06 by K.Okada */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* CAR を IR と誤検出しないようにする処理。 H.Kubo 1998/10/16 */
	if (SYB_ND_CarPattern[SYS_ND_CAR_IR_MARK_THRESHOLD] > 0) {
		if (SYB_ND_CarPattern[SYS_ND_CAR_IR_MARK_THRESHOLD] < SamplingBuff[0]) {
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
			if (DEBUG_NumberDisplay) {
				if ((NCU_ND_Status & ND_WAIT_FOR_CAR) && (SYS_LineNDStatus == ND_USED_IN_STD)) {
					return NG_RING;
				}
			}
			else {
				if (NCU_ND_Status & ND_WAIT_FOR_CAR) {
					return NG_RING;
				}
			}
#else /* !defined (KEISATSU) */
			if (NCU_ND_Status & ND_WAIT_FOR_CAR) {
				return NG_RING;
			}
#endif /* defined (KEISATSU) */
		}
	}
#endif

	sampling_count = SetSamplingCounter();		/** 検出リングの個数を得る */
												/* sampling_count < BUFF_MAX の関係が
												StoreRingingOn/OffTime()の内部で実現されている。
												 '96,03,22 By N.S. */
/*--------------------------------------------------------------------------------
** ・ANS/FAX待機
** ・TEL2にNTT IM-2400を接続し、着ベル回数1回に設定
** 上記条件のとき、CNG検出できない不具合が発生。
** 本体側は最小ON期間中(200ms)、CIが入ってきているとき、呼び出し信号と認識するが、
** 200msに満たないうちに、TEL2電話器が着信してしまう。
** よって、最小ON期間を10ms単位で微調整可能にする
** 1999/12/06 by K.Okada
*/
	comp_min_on_time = NCU_CI_MinOnTime(); /* 最小ON期間を獲得 */

#if (PRO_RING_MASTER == ENABLE)					/* '96/10/01 By N.Sakamoto */
	if (RingMasterFlag) {
		for (i = 0; i < sampling_count; i++) {
			/*-----------------------------------------------------*/
			/** 最小ON/OFF期間より短いか、最大ON/OFF期間よりも長い */
			/*-----------------------------------------------------*/
			if ((SamplingBuff[i] < CTRY_RingMasterTable()->RingMinCycle[i])
			 || (SamplingBuff[i] > CTRY_RingMasterTable()->RingMaxCycle[i])) {
				/*-----------------------------------------------*/
				/** 検出パターンはNGであるが最小ON期間よりも長い */
				/*-----------------------------------------------*/
#if (0) /* 1999/12/06 by K.Okada */
//				if (SamplingBuff[0] >= CTRY_RingTable()->MinOnTime) {
//#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
//					if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
//						SYS_RingCounter = 1;
//					}
//					else {
//						SYS_RingCounterExt = 1;
//					}
//#else
//					SYS_RingCounter = 1;
//#endif
//				}
#else
				if (SamplingBuff[0] >= comp_min_on_time) {
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
					if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
						SYS_RingCounter = 1;
					}
					else {
						SYS_RingCounterExt = 1;
					}
 #else
					SYS_RingCounter = 1;
 #endif
				}
#endif
				return (NG_RING);
			}
		}
		return (OK_RING);
	}
	else {
#endif											/* '96/10/01 By N.Sakamoto */

#if 0 /* (PRO_NUMBER_DISPLAY == ENABLE) */ /* H.Kubo 1998/07/02 */ /* Deleted by H.Kubo 1998/10/15 */
@@		if (NCU_ND_Status & ND_WAIT_FOR_2ND_RING) {
@@			if (SamplingBuff[0] >= NCU_ND_CarTime.MinOnTime
@@			&&  SamplingBuff[1] <= NCU_ND_CarTime.MaxOffTime) {
@@				return (OK_RING);
@@			}
@@			return (NG_RING);
@@		}
#endif

		/*-----------------------*/
		/** 最小ON期間よりも長い */
		/*-----------------------*/
#if (0) /* 1999/12/06 by K.Okada */
//		if (SamplingBuff[0] >= CTRY_RingTable()->MinOnTime) {
//			return (OK_RING);
//		}
#else
		if (SamplingBuff[0] >= comp_min_on_time) {
			return (OK_RING);
		}
#endif
		return (NG_RING);
#if (PRO_RING_MASTER == ENABLE)					/* '96/10/01 By N.Sakamoto */
	}
#endif											/* '96/10/01 By N.Sakamoto */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[サンプリング･データの初期化]
	function	:[
		1.着信検出のためのバッファ及びデータを初期化する
	]
	return		:[なし]
	common		:[
		UWORD  SamplingBuff[]
		UBYTE DoubleRingStatus
		UWORD  RingingOnTime
		UWORD  RingingOffTime
		UBYTE Ringing
		UWORD  CI_Counter
		UWORD  CI_OK_Counter
		UWORD  CI_NG_Counter
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  InitializeGrovalData(void)
{
	UBYTE i;

	for (i = 0; i < BUFF_MAX; i++) {
		SamplingBuff[i] = 0;
	}
	DoubleRingStatus = OFF;		/* Moved by TH92115 1994/09/12 */
	RingingOnTime  = 0;
	RingingOffTime = 0;
	Ringing		   = OFF;
	CI_Counter	   = 0;
	CI_OK_Counter  = 0;
	CI_NG_Counter  = 0;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[検出リングON時間の取得]
	function	:[
		1.検出リングON時間をバッファにセットする
		2.バッファ･カウンタをインクリメントする
	]
	return		:[なし]
	common		:[
		UWORD SamplingBuff
		UWORD RingingOnTime
	]
	condition	:[]
	comment		:[
		ON期間は物理的に偶数番目にセットされる
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  StoreRingingOnTime(UBYTE *counter)
{
	UWORD					comp_min_on_time;	/* 1999/12/06 by K.Okada */
	
	if (!((*counter) % 2)) {
		if((*counter) < BUFF_MAX ){		/* '96,03,22 By N.S. 1lines insert BUFF_MAX=10 */
/*--------------------------------------------------------------------------------
** ・ANS/FAX待機
** ・TEL2にNTT IM-2400を接続し、着ベル回数1回に設定
** 上記条件のとき、CNG検出できない不具合が発生。
** 本体側は最小ON期間中(200ms)、CIが入ってきているとき、呼び出し信号と認識するが、
** 200msに満たないうちに、TEL2電話器が着信してしまう。
** よって、最小ON期間を10ms単位で微調整可能にする
** 1999/12/06 by K.Okada
*/
			comp_min_on_time = NCU_CI_MinOnTime(); /* 最小ON期間を獲得 */
		
			/*------------------------------------------*/
			/** 200ms以上でないとON期間とは見なしません */		/* 1995/04/21 -> 05/16(Make) */
			/*------------------------------------------*/
#if (0) /* 1999/12/06 by K.Okada */
//			if (RingingOnTime >= CTRY_RingTable()->MinOnTime) {
//				SamplingBuff[*counter] = RingingOnTime;
//				(*counter)++;
//			}
#else
			if (RingingOnTime >= comp_min_on_time) {
				SamplingBuff[*counter] = RingingOnTime;
				(*counter)++;
			}
#endif
			else {
				if ((*counter) > 0) {	/** OFF期間と見なします */
					SamplingBuff[(*counter) - 1] += (UWORD)(RingingOnTime + RingingOffTime);
				}
			}
		}								/* '96,03,22 By N.S. 1lines insert */
	}
	RingingOnTime = 0;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[検出リングOFF時間の取得]
	function	:[
		1.検出リングON時間をバッファにセットする
		2.バッファ･カウンタをインクリメントする
	]
	return		:[なし]
	common		:[
		UWORD SamplingBuff
		UWORD RingingOffTime
	]
	condition	:[]
	comment		:[
		OFF期間は物理的に奇数番目にセットされる
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  StoreRingingOffTime(UBYTE *counter)
{
	if (RingingOffTime && ((*counter) % 2)) {
		if((*counter) < (BUFF_MAX - 1)){	/* '96,03,22 By N.S. 1lines insert BUFF_MAX=10 */
			SamplingBuff[*counter] = RingingOffTime;
			(*counter)++;
		}									/* '96,03,22 By N.S. 1lines insert */
	}
	RingingOffTime = 0;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ワンショットタイマの停止]
	function	:[
		1.ランニングカウンタを停止する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  StopOneshotTimer(void)
{
#if (PRO_CPU == SH7043)

	/*  内蔵タイマーチャネル１ */
	MTU__TSTR &= ~TSTR_START_CH1;	/* タイマーストップ */
	MTU__TCNT1 = 0;

#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[連続ベルorダブルリングの判定]
	function	:[
		1.連続ベル着信を判定します
		2.ダブルリングを判定します
	]
	return		:[
		0			連続ベル着信でない
		1			連続ベル着信
	]
	common		:[
		UBYTE DoubleRingStatus
		UWORD  RingingOnTime
		UWORD  RingingOffTime
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE  CheckContinueAndDoubleRing(void)
{
	if ((CHK_ContinueRing())
	 && (RingingOnTime	>= CTRY_RingTable()->ContinueTime)) {		/** 連続ベル着信対策 */
		return (1);
	}
	if ((RingingOffTime >= CTRY_RingTable()->DoubleDetect)
	 && (RingingOffTime <= CTRY_RingTable()->MaxOffTime)) {			/** ダブルリング対策 */
		DoubleRingStatus = ON;
	}
	return (0);
}


#if (PRO_RING_MASTER == ENABLE)		/* For MBS	1995/05/24 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[自動検出パターンの記憶]
	function	:[
		1.バッファを初期化する
		2.ＯＮ／ＯＦＦパターンを記憶する
	]
	return		:[なし]
	common		:[
		struct SubRingMaster TeachingPattern[];
		UWORD  SamplingBuff[]
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  SetTeachingPattern(UBYTE number)
{
	UBYTE i;
	UBYTE ring_number;

	if( number == RING_MASTER_PATTERN_7 ){	/* '96,03,22 By N.S. 6lines insert */
		ring_number = 0;
	}
	else{
		ring_number = 1;
	}

	for(i = 0; i < BUFF_MAX; i++){				/* '96,03,22 By N.S. */

		if(!(SamplingBuff[i])){	/* '96,03,22 By N.S. 3lines insert */
			break;
		}

		SYB_TeachingPattern[ring_number].RingMinCycle[i] = (UWORD)(SamplingBuff[i] - 10);
		SYB_TeachingPattern[ring_number].RingMaxCycle[i] = (UWORD)(SamplingBuff[i] + 10);

	}

	for(; i < BUFF_MAX; i++){	/* '96,03,22 By N.S. */
		SYB_TeachingPattern[ring_number].RingMinCycle[i] = 0;
		SYB_TeachingPattern[ring_number].RingMaxCycle[i] = 0;
	}
}
#endif


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信検出の実行]
	function	:[
		1.着信条件の合否をリターンする
	]
	return		:[
		#define		RING_NOT_AVAILABLE		着信不可
		#define		CALLED_REQUEST			着信可能
	]
	common		:[
		UWORD  SYS_GeneralTimer
		UWORD  RingingOnTime
		UWORD  RingingOffTime
		UWORD  RingStatus
		UWORD  NCUStatus
		UBYTE Ringing
		UWORD  BranchDetectCounter
		UBYTE FreqStatus
		UWORD  SamplingBuff[]
		UBYTE DoubleRingStatus
		UWORD  CI_OK_Counter
		UWORD  CI_NG_Counter
	]
	condition	:[]
	comment		:[
		一部ブランチ検出に関する処理があります
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_NUMBER_DISPLAY == ENABLE)  /* modified by H.Kubo 1998/10/20 */
UBYTE	DetectRingToneAndCar( UWORD mailbox )
#else
UBYTE  DetectRingTone(void)
#endif
{
#if (PRO_CLASS1 == ENABLE) || (PRO_NUMBER_DISPLAY == ENABLE) /* Add By Y.Tanimoto 96.04.08 */ /* ND is added by H.Kubo 1998/10/20 */
	MESSAGE_t *RxDetectCalledTaskMsg;
#endif
	UWORD  current_time;
	UWORD  ci_time;
	UWORD  ci_start_time;
	UWORD  ci_end_time;
	UBYTE buff_counter;
	UBYTE ci_freq_ok; /* 周期の短い CI 誤検出対策 by H.Kubo 1998/02/09 */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/20 */
	UBYTE car_detection_result;
#endif

#if (PRO_RING_MASTER == ENABLE)		/* For MBS	1995/05/24 */
	UBYTE pattern;

	TeachingStartFlag = 0;
#endif

#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
	CR_RingStartTime = 600;
#endif

	ci_freq_ok = TRUE; /* 周期の短い CI 誤検出対策 by H.Kubo 1998/02/09 */

	ci_start_time = ci_end_time = SYS_GeneralTimer;			/** CIスタートorエンド時間の確保 */
	SetTimerValue();										/** 検出リングのタイマ値を得る */

#if (PRO_NCU_TYPE == HINOKI_TYPE) /* 1999/02/22 by T.Soneoka */
	/*
	** ここで仮着信状態にしておきます
	** 現在のところ原因は分かっていないが、メインタスクの中で仮着信状態にした場合、
	** 正確に発着信衝突がみれないタイミングが発生するのを防ぎます
	*/
	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRE_LINE_BUSY;
#endif
	
	/** タイマタスクの起動 (CiDetectTime and CiMinCycleTime) */
	cre_tsk(&tskno_FrequencyCheckTask, TSK_NCU_FREQUENCYCHECKTASK, 0);
	cre_tsk(&tskno_TimeUpTask, TSK_NCU_TIMEUPTASK, 0);

	while (1) {
		/** サンプリング・バッファ、ローカル・データの初期化 */
		InitializeGrovalData();
		buff_counter = 0;
#if defined(FRA)	/* by M.H 98/07/15  ﾊﾟﾗ接続の10ppsのﾀﾞｲﾔﾙで誤着信する対策 */
	/* リングトーンのカウントが不正確になるので量産機には入れません By Y.Suzuki 98/09/04*/
	/*	ci_start_time = ci_end_time = SYS_GeneralTimer;			@** CIスタートorエンド時間の確保 */
#endif

#if 1 /* 周期の短い CI 誤検出対策 by H.Kubo 1998/02/09 */
		ci_freq_ok = TRUE;
#endif

		while (1) {
			wai_evt(EVT_CI_CHECK);		/** CI､又はタイムアップのイベント待ち */
#if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
			/*EVT_CI_CHECK確認*/
			if (SYB_MaintenanceSwitch[MNT_SW_F0] & 0x01) {
				SYB_DensitySw = SYS_NORMAL_DENSITY;
				DensityLedOn();
			}
#endif
			current_time = SYS_GeneralTimer;

			if (tskno_FrequencyCheckTask != 0xFFFF) {	/** 周波数チェックタスクの強制終了 */
#if !defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/15 */
				StopOneshotTimer();									/** ワンショットタイマの停止 */
#endif /* defined (KEISATSU) */
				del_tsk(&tskno_FrequencyCheckTask);
			}

	#if defined(JPN)
			if (RingStatus & F_NET_CALLED_SIGNAL) {		/** Ｆネット検出	1994/10/24 */
				/*--------------------------------------------------------*/
				/** リングカウンタを初期化し､リングトーン検出を終了します */
				/*--------------------------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
				if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
					SYS_RingCounter = 0;
				}
				else {
					SYS_RingCounterExt = 0;
				}
#else
				SYS_RingCounter = 0;
#endif
				RingStatus &= ~F_NET_CALLED_SIGNAL;
				return (DETECT_F_NET);
			}
	#endif
			if (RingStatus & CI_DETECT_TIMEUP) {		/** リングトーン検出時間のタイムアップ */
				/*--------------------------------------------------------*/
				/** リングカウンタを初期化し､リングトーン検出を終了します */
				/*--------------------------------------------------------*/
#if (1) /* (PRO_CR_RINGING==ENABLE) /* モデムダイヤルインIR対応 O.Oshima2005/07/20 */
 #if (PRO_NUMBER_DISPLAY == ENABLE)
				if ((CHK_ModemDialinON()) && (SYS_RingCounter >= CHK_RingCount())) {
					CR_Ringing = OFF; /* 10sec 以上のCI OFF */
				}
 #endif
 				if (!RingingOnTime) { /* 10秒以上10.2秒以下でCRが止まった場合にクリアされない対策 2005/08/31 */
					CR_Ringing = OFF; /* 10sec 以上のCI OFF */
				}
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
				if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/11 */
					if ( ((NCU_LineStatus & STD_LINE_STATUS) != STD_TEL_RECEIVE)	/* 標準回線には受話中ではない */
						&& ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) ) {	/* 標準回線には本体使用中ではない */
						/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/26 */
						if (DEBUG_NumberDisplay) {
							if ((SYS_LineNDStatus == ND_USED_IN_STD) && (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR | ND_CALL_ACCEPTED))) {
								NCU_ND_InitializeStatus(); /* 初期状態に戻す */
							}
						}
						SYS_RingCounter = 0;
					}
					if ((NCU_LineStatus & STD_LINE_STATUS) == STD_CI_IN) {
						NCU_LineStatus &= ~STD_LINE_STATUS;
						NCU_LineStatus  |=  (STD_LINE_STATUS & STD_NOT_USE);
					}
					H_RelayOff();	/**	Hリレー戻します	*/
					if ( !ModemRelaySetting() ) {	/* モデムリレーを標準回線に接続している場合 */
						CONT_24V_Off();
					}
#else /* !defined (KEISATSU) */
					SYS_RingCounter = 0;
#endif /* defined (KEISATSU) */
				}
				else {
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/11 */
					if ( ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_TEL_RECEIVE)	/* 拡張回線には受話中ではない */
						&& ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) ) {	/* 拡張回線には本体使用中ではない */
						SYS_RingCounterExt = 0;
					}
					if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_CI_IN) {
						NCU_LineStatus &= ~EXT_LINE_STATUS;
						NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_NOT_USE);
					}
					L_RelayOff();	/**	Lリレーも戻します	*/
					if ( ModemRelaySetting() ) {	/* モデムリレーを拡張回線に接続している場合 */
						CONT_24V_Off();
					}
#else /* !defined (KEISATSU) */
					SYS_RingCounterExt = 0;
#endif /* defined (KEISATSU) */
				}
#else
				SYS_RingCounter = 0;
#endif
				RingStatus &= ~CI_DETECT_TIMEUP;
#if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
				/*写真LED ON*/
				if (SYB_MaintenanceSwitch[MNT_SW_F0] & 0x01) {
					SYB_ModeSw = SYS_GRAY16;
					ModeLedOn();
				}
#endif
				return (RING_NOT_AVAILABLE);
			}

			if (RingStatus & CI_CYCLE_TIMEUP) {			/** 周波数チェックのタイムアップ */
				/*-----------------------------------------------*/
				/** CIのOFF期間TIMEUPで､サンプリングを停止します */
				/*-----------------------------------------------*/
				StoreRingingOnTime(&buff_counter);					/** リングON期間の確保 */
				RingStatus &= ~CI_CYCLE_TIMEUP;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/14 */
				/* NCU_ND_Status の ND_SUSPICIOUS_CI_DETECTED だけが立ってる時にタイムアップしたら、
				** リセットﾉ処理を追加。
				** by H.Kubo 1998/11/16 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
 				if (DEBUG_NumberDisplay) {
					if (NCU_IsCarWaitedFor() && (SYS_LineNDStatus == ND_USED_IN_STD)) {
						CMN_DisableInterrupt();
						if ((NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR)
						&&   (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED)
						&& !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED)) {
							NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED; /* 偽の CI だったので、落とします。 */
						}
						CMN_EnableInterrupt();
						if  (!(NCU_ND_Status & ~ND_WAIT_FOR_CAR_AND_IR)
						&& ((NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR) == ND_WAIT_FOR_CAR)) {
							/* IR で着信してはいけない */
							cre_tsk(&tskno_FrequencyCheckTask, TSK_NCU_FREQUENCYCHECKTASK, 0);
							continue;
						}
					}
				}
				else {
					if (NCU_IsCarWaitedFor() ) {
						CMN_DisableInterrupt();
						if ((NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR)
						&&   (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED)
						&& !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED)) {
							NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED; /* 偽の CI だったので、落とします。 */
						}
						CMN_EnableInterrupt();
						if  (!(NCU_ND_Status & ~ND_WAIT_FOR_CAR_AND_IR)
						&& ((NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR) == ND_WAIT_FOR_CAR)) {
							/* IR で着信してはいけない */
							cre_tsk(&tskno_FrequencyCheckTask, TSK_NCU_FREQUENCYCHECKTASK, 0);
							continue;
						}
					}
				}
 #else /* !defined (KEISATSU) */
				if (NCU_IsCarWaitedFor() ) {
					CMN_DisableInterrupt();
					if ((NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR)
					&&   (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED)
					&& !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED)) {
						NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED; /* 偽の CI だったので、落とします。 */
					}
					CMN_EnableInterrupt();
					if  (!(NCU_ND_Status & ~ND_WAIT_FOR_CAR_AND_IR)
					&& ((NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR) == ND_WAIT_FOR_CAR)) {
						/* IR で着信してはいけない */
						cre_tsk(&tskno_FrequencyCheckTask, TSK_NCU_FREQUENCYCHECKTASK, 0);
						continue;
					}
				}
 #endif /* defined (KEISATSU) */
#endif
#if defined(POPLAR_H) && defined(JP0) /*V851 By Y.Suzuki 2002/09/15 */
				if (SYB_MaintenanceSwitch[MNT_SW_F0] & 0x02) {
					/*CIｻｲｸﾙでﾘﾝｸﾞﾄｰﾝの検出をぬける。*/
					return (RING_NOT_AVAILABLE);
				}
#endif
#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
 #if (PRO_NUMBER_DISPLAY == ENABLE)
				if (!((CHK_ModemDialinON()) && (SYS_RingCounter >= CHK_RingCount()))) { /* モデムダイヤルインIR対応 */
					CR_Ringing = OFF; /* 600msec 以上のCI OFF */
				}
 #endif
#endif
				break;			/** 抜けます */
			}

			if (RingStatus & CI_ON) {					/** とにかくＣＩらしきものを検出 */
				ci_time = current_time;								/** CI時間の確保 */
				if ((FreqStatus == WITHIN_MIN_CYCLE) && !CHK_RingFreqAvailable()) {
					FreqStatus = OK_CI_CYCLE;						/** 周波数チェック無の場合は、0～584(ms)をOKの範囲とします */
				}
				/*-------------------------------------------------*/
				/** CIと断定(周波数チェックOK)：ON期間を更新します */
				/*-------------------------------------------------*/
				if (FreqStatus == OK_CI_CYCLE) {
					ci_end_time = ci_time;							/** CIエンド時間の更新 */
					RingingOnTime = (UWORD)(ci_end_time - ci_start_time);	/** リングON期間の更新 */
					if (Ringing) {		/** 鳴動中 */
#if (PRO_LINENUMBER == TWICE_LINE) /* 条件追加 by H.Kubo 1998/02/09 */
						if (CheckContinueAndDoubleRing()	/** 連続ベルorダブルリングの判定 */
						||  !CHK_RingFreqAvailable() ) {	/* 周波数検査しない */
#else
						if (CheckContinueAndDoubleRing()) {			/** 連続ベルorダブルリングの判定 */
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/13 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
							if (DEBUG_NumberDisplay && NCU_IsCarWaitedFor() && !(NCU_ND_Status & ND_WAIT_FOR_IR)
								&& (SYS_LineNDStatus == ND_USED_IN_STD)) {
							}
							else if (NCU_IsCarWaitedFor() && !(NCU_ND_Status & ND_WAIT_FOR_IR)) {
								/* IR で着信してはいけない */
							}
 #else /* !defined (KEISATSU) */
							if (NCU_IsCarWaitedFor() && !(NCU_ND_Status & ND_WAIT_FOR_IR)) {
								/* IR で着信してはいけない */
							}
 #endif /* defined (KEISATSU) */
							else
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/08 */
							if (RingStatus2nd & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
								if ( ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE)	/* 拡張回線には通信中 */
									|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) 	/* 拡張回線には本体使用中 */
									|| (CHK_KEIDENRxPriority() && ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)) ){ /* 警電優先受信ＯＮ及び警電受話中 */
									/* ここで動作しない */
								}
								else {
									return (CALLED_REQUEST);	/**	標準ライン着信	*/
								}
							}
							else {
								if ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE)	/* 標準回線には通信中 */
									|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ){ 	/* 標準回線には本体使用中 */
									if ( (CHK_KEIDENRxPriority())	/* 警電優先受信機能が有効されている場合 */
										&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
										/* 通信中断していない場合 */
										SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
										while ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE)	/* 標準回線には通信中 */
												|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ){ 	/* 標準回線には本体使用中 */
											wai_tsk(1);
										}
										wai_tsk(1);
										return (CALLED_REQUEST_EXT);	/**	拡張ライン着信	*/
									}
								}
								else {
									return (CALLED_REQUEST_EXT);	/**	拡張ライン着信	*/
								}
							}
 #else /* !defined (KEISATSU) */
							if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
								return (CALLED_REQUEST);	/**	標準ライン着信	*/
							}
							return (CALLED_REQUEST_EXT);	/**	拡張ライン着信	*/
 #endif /* defined (KEISATSU) */
#else
							return (CALLED_REQUEST);
#endif
						}
#if (1) /* (PRO_CR_RINGING==ENABLE)  CR対応 O.Oshima2005/07/20 */
						if (RingingOnTime >= CR_RingStartTime) { /* 6sec */
							if (CR_Ringing == OFF) {
								CR_Ringing = ON;
								ReverseRelayControl();
							}
						}
#endif
					}
					else {				/** 鳴り始めなら */
						StoreRingingOffTime(&buff_counter);			/** リングマスター検出時のOFF期間の確保 */
						Ringing = ON;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/08/11 */
							/* ナンバーディスプレイの CAR を検出 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
 						if (DEBUG_NumberDisplay) {
							if (NCU_IsCarWaitedFor() && (SYS_LineNDStatus == ND_USED_IN_STD)) {
								if (NCU_IsCarReceived(SamplingBuff[buff_counter-2], SamplingBuff[buff_counter-1])) {
									SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter;
									return DETECT_CAR;
								}
								if (SYB_ND_CarPattern[SYS_ND_CAR_COUNTER_THRESHOLD] <= buff_counter) { /* 呼出し音でないベルが続いたら、 CAR とする。*/
									SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter;
									return DETECT_CAR;
								}
								ci_start_time = ci_time;
							}
						}
						else {
							if (NCU_IsCarWaitedFor()) {
								if (NCU_IsCarReceived(SamplingBuff[buff_counter-2], SamplingBuff[buff_counter-1])) {
									SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter;
									return DETECT_CAR;
								}
								if (SYB_ND_CarPattern[SYS_ND_CAR_COUNTER_THRESHOLD] <= buff_counter) { /* 呼出し音でないベルが続いたら、 CAR とする。*/
									SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter;
									return DETECT_CAR;
								}
								ci_start_time = ci_time;
							}
						}
 #else /* !defined (KEISATSU) */
						if (NCU_IsCarWaitedFor()) {
							if (NCU_IsCarReceived(SamplingBuff[buff_counter-2], SamplingBuff[buff_counter-1])) {
								SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter;
								return DETECT_CAR;
							}
							if (SYB_ND_CarPattern[SYS_ND_CAR_COUNTER_THRESHOLD] <= buff_counter) { /* 呼出し音でないベルが続いたら、 CAR とする。*/
								SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter;
								return DETECT_CAR;
							}
							ci_start_time = ci_time;
						}
 #endif /* defined (KEISATSU) */
#endif
					}
					CI_OK_Counter++;								/** OKのCIカウンタ */
				}
				/*--------------------------------------------------*/
				/** CIでない(周波数チェックNG)：OFF時間を更新します */
				/*--------------------------------------------------*/
				else {

#if (0) /* 削除：SYS_RingCounterを満足する条件でも、最小時間に満たないパルスが存在する場合、その１ベル期間中では設定回数
        **       とSYS_RingCounterとの比較がなされない為、ベル設定回数に達してもベルが鳴動する。
        **       「ベル鳴動期間のパルスをカウントし、周波数換算しＯＫならSYS_RingCouterと比較する」等の緩和処置をとれば
        **       正常動作すると思われます。今回は十分な評価時間がとれないのでご勘弁を！   By S.Fukui Mar.6,1998
        */
 #if 1 /* 条件追加 by H.Kubo 1998/02/09 */
					if (FreqStatus == WITHIN_MIN_CYCLE) {
						ci_freq_ok = FALSE;
					}
 #endif
#endif
					RingingOffTime = (UWORD)(ci_time - ci_end_time);			/** リングOFF時間の更新 */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/07/23 */
							/* ナンバーディスプレイの CAR を検出 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
					if (DEBUG_NumberDisplay) {
						if (NCU_IsCarWaitedFor() && (SYS_LineNDStatus == ND_USED_IN_STD)) {  /* CAR 検出してよいか */
							if (NCU_IsCarReceived(RingingOnTime, RingingOffTime)) {
								SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter;
								return DETECT_CAR;
							}
						}
					}
					else {
						if (NCU_IsCarWaitedFor()) { /* CAR 検出してよいか */
							if (NCU_IsCarReceived(RingingOnTime, RingingOffTime)) {
								SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter;
								return DETECT_CAR;
							}
						}
					}
 #else /* !defined (KEISATSU) */
					if (NCU_IsCarWaitedFor()) { /* CAR 検出してよいか */
						if (NCU_IsCarReceived(RingingOnTime, RingingOffTime)) {
							SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = buff_counter;
							return DETECT_CAR;
						}
					}
 #endif /* defined (KEISATSU) */
#endif
					if (Ringing) {		/** 鳴動中 */
#if (PRO_RING_MASTER == ENABLE)					/* '96/10/16 By N.Sakamoto */
						if (RingMasterFlag && (FreqStatus == OVER_MAX_CYCLE)) {
							StoreRingingOnTime(&buff_counter);		/** リングマスター検出時のON期間の確保 */
							ci_start_time = ci_time;				/** CIスタート時間の更新 */
							Ringing = OFF;
						}
#endif											/* '96/10/16 By N.Sakamoto */
#if defined(FRA)	/* by M.H 98/07/15  ﾊﾟﾗ接続の10ppsのﾀﾞｲﾔﾙで誤着信する対策 */
						/* リングトーンのカウントが不正確になるので量産機には入れません By Y.Suzuki 98/09/04*/
						/*	ci_start_time = ci_time;				@** CIスタート時間の更新 */
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/07/23 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
						if (DEBUG_NumberDisplay) {
							if (NCU_IsCarWaitedFor() && (SYS_LineNDStatus == ND_USED_IN_STD)) {  /* CAR 検出してよいか */
								if (FreqStatus == OVER_MAX_CYCLE) {
									StoreRingingOnTime(&buff_counter);		/** リングマスター検出時のON期間の確保 */
									ci_start_time = ci_time;				/** CIスタート時間の更新 */
									Ringing = OFF;
								}
							}
						}
						else {
							if (NCU_IsCarWaitedFor()) { /* CAR 検出してよいか *//* 条件が抜けている by O.Kimoto 2002/11/12 */
								if (FreqStatus == OVER_MAX_CYCLE) {
									StoreRingingOnTime(&buff_counter);		/** リングマスター検出時のON期間の確保 */
									ci_start_time = ci_time;				/** CIスタート時間の更新 */
									Ringing = OFF;
								}
							}
						}
 #else /* !defined (KEISATSU) */
						if (NCU_IsCarWaitedFor()) { /* CAR 検出してよいか *//* 条件が抜けている by O.Kimoto 2002/11/12 */
							if (FreqStatus == OVER_MAX_CYCLE) {
								StoreRingingOnTime(&buff_counter);		/** リングマスター検出時のON期間の確保 */
								ci_start_time = ci_time;				/** CIスタート時間の更新 */
								Ringing = OFF;
							}
						}
 #endif /* defined (KEISATSU) */
#endif
					}
					else {				/** 鳴り始めなら */
						ci_start_time = ci_time;					/** CIスタート時間の更新 */
						SetTimerValue();							/** 検出リングのタイマ値を得る */
					}
					CI_NG_Counter++;								/** NGのCIカウンタ */
				}
				RingStatus &= ~CI_ON;
				cre_tsk(&tskno_FrequencyCheckTask, TSK_NCU_FREQUENCYCHECKTASK, 0);
			}
			continue;
		}

#if 0 /* (PRO_NUMBER_DISPLAY == ENABLE) */ /* added by H.Kubo 1998/10/16 */ /* 下へ移動します。 by H.Kubo 1998/11/17 */
** 		/* CI_CYCLE_TIMEUP で抜けてきた場合の CAR 検出と呼出音停止の検出 */
** 		car_detection_result = NCU_CheckCarAfterCiCycleTimeup(ci_end_time, &ci_start_time, &buff_counter);
** 		switch (car_detection_result) {
** 		case DETECT_CAR:
** 			return DETECT_CAR;
** 			break;
** 		case DETECT_IR_STOP:
** 			/* */ 
** 			TxDetectCalledTaskMsg.Message = DETECT_2ND_RING_TIMEUP;
** 			snd_msg(mailbox, &TxDetectCalledTaskMsg); /* 呼出音検出やめさせる。 */
** 			rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
** 			break;
** 		default:
** 			break;
** 		}
#endif /* defined (KEISATSU) */

		/*--------------------------------------*/
		/** サンプリング･データの結果判定を行う */
		/*--------------------------------------*/
			/* 呼出し音の検出*/
#if (PRO_RING_MASTER == ENABLE)		/* For MBS	1995/05/24 */
		if (SYS_TeachingModeFlag) {
			if (!TeachingStartFlag) {
				pattern = CHK_RingMasterPattern();
				TeachingStartFlag = ON;
			}
			else {
				if (pattern == RING_MASTER_PATTERN_7) {
					SYB_RingG_SetNumber = buff_counter;
					SetTeachingPattern(pattern);
				}
				else if (pattern == RING_MASTER_PATTERN_8) {
					SYB_RingH_SetNumber = buff_counter;
					SetTeachingPattern(pattern);
				}
				SYS_TeachingModeFlag = OFF;
			}
		}
		else {
			TeachingStartFlag = OFF;
#endif
		if (OK_RING == CompareSamplingTone()) {					/** OKのリングと判断 */
			if (!CHK_DoubleRingAvailable() || !DoubleRingStatus) {
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
				if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/15 */
					SYS_CalledLineNumber |= SYS_STD_LINE_IN_CI;
					if (!SYS_RingCounter) {
						/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/25 */
						/* ナンバーディスプレイONの場合、CIを検出したら、すぐ電話リレーを回線に戻す */
						if (CHK_NumberDisplayON()) {
							H_RelayOff();
						}
						UpdateLCD();
					}
 #endif /* defined (KEISATSU) */
					SYS_RingCounter++;								/** リングカウンタの更新 */
 #if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
					if (SYB_MaintenanceSwitch[MNT_SW_F0] & 0x01) {
						/*ﾘﾝｸﾞｶｳﾝﾀ確認*/
						AckBuzzer();
 					}
 #endif
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/15 */
					if ( (NCU_LineStatus & STD_LINE_STATUS) == STD_NOT_USE ) { /* 標準回線は呼出中ではない */
						NCU_LineStatus &= ~STD_LINE_STATUS;
						NCU_LineStatus  |=  (STD_LINE_STATUS & STD_CI_IN);
					}
 					if (!(SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI)) {
						if ( HDST_RelaySetting() && !(NCU_LineStatus & EXT_HDST_OFFHOOK) ) {	/* 付属電話は拡張回線でオフフックではない */
							if (!(NCUStatus & (HOOK_KEY_ON_STATE | DIALING_STATE))) {
								HDST_RelayOff(); 		/* ハンドセットを標準回線に接続する */
								/* 警察FAX Added by SMuratec 李 2005/11/09 */
								/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
								UpdateLCD();
							}
						}
					}
 #endif /* defined (KEISATSU) */
					if (SYS_RingCounter >= 0xf0) {					/** TEL待機､ANS/FAX待機(内蔵TAD無)の対策 */
						SYS_RingCounter = 1;
					}
				}
				else {
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/15 */
					SYS_CalledLineNumber |= SYS_EXT_LINE_IN_CI;
					if (!SYS_RingCounterExt) {
						UpdateLCD();
					}
 #endif /* defined (KEISATSU) */
					SYS_RingCounterExt++;
 #if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
					if (SYB_MaintenanceSwitch[MNT_SW_F0] & 0x01) {
						/*ﾘﾝｸﾞｶｳﾝﾀ確認*/
						AckBuzzer();
					}
 #endif
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/15 */
					SYS_CalledLineNumber |= SYS_EXT_LINE_IN_CI;
					if ( (NCU_LineStatus & EXT_LINE_STATUS) == EXT_NOT_USE ) { /* 拡張回線は呼出中ではない */
						NCU_LineStatus &= ~EXT_LINE_STATUS;
						NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_CI_IN);
					}
					if ( !HDST_RelaySetting() && !(NCU_LineStatus & STD_HDST_OFFHOOK) ) {	/* 付属電話は標準回線でオフフックではない */
						if (!(NCUStatus & (HOOK_KEY_ON_STATE | DIALING_STATE))) {
							HDST_RelayOn(); 		/* ハンドセットを拡張回線に接続する */
						}
					}
 #endif /* defined (KEISATSU) */
					if (SYS_RingCounterExt >= 0xf0) {					/** TEL待機､ANS/FAX待機(内蔵TAD無)の対策 */
						SYS_RingCounterExt = 1;
					}
				}
#else
				SYS_RingCounter++;								/** リングカウンタの更新 */
				if (SYS_RingCounter >= 0xf0) {					/** TEL待機､ANS/FAX待機(内蔵TAD無)の対策 */
					SYS_RingCounter = 1;
				}
#endif
			}
			else {
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
				if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/15 */
					SYS_CalledLineNumber |= SYS_STD_LINE_IN_CI;
					if (!SYS_RingCounter) {
						UpdateLCD();
					}
 #endif /* defined (KEISATSU) */
					SYS_RingCounter = 1;
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/15 */
					SYS_CalledLineNumber |= SYS_STD_LINE_IN_CI;
					if ( (NCU_LineStatus & STD_LINE_STATUS) == STD_NOT_USE ) { /* 標準回線は呼出中ではない */
						NCU_LineStatus &= ~STD_LINE_STATUS;
						NCU_LineStatus  |=  (STD_LINE_STATUS & STD_CI_IN);
					}
 					if (!(SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI)) {
						if ( HDST_RelaySetting() && !(NCU_LineStatus & EXT_HDST_OFFHOOK) ) {	/* 付属電話は拡張回線でオフフックではない */
							if (!(NCUStatus & (HOOK_KEY_ON_STATE | DIALING_STATE))) {
								HDST_RelayOff(); 		/* ハンドセットを標準回線に接続する */
								/* 警察FAX Added by SMuratec 李 2005/11/09 */
								/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
								UpdateLCD();
							}
						}
					}
 #endif /* defined (KEISATSU) */
				}
				else {
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/15 */
					SYS_CalledLineNumber |= SYS_EXT_LINE_IN_CI;
					if (!SYS_RingCounterExt) {
						UpdateLCD();
					}
 #endif /* defined (KEISATSU) */
					SYS_RingCounterExt = 1;
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/15 */
					SYS_CalledLineNumber |= SYS_EXT_LINE_IN_CI;
					if ( (NCU_LineStatus & EXT_LINE_STATUS) == EXT_NOT_USE ) { /* 拡張回線は呼出中ではない */
						NCU_LineStatus &= ~EXT_LINE_STATUS;
						NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_CI_IN);
					}
					if ( !HDST_RelaySetting() && !(NCU_LineStatus & STD_HDST_OFFHOOK) ) {	/* 付属電話は標準回線でオフフックではない */
						if (!(NCUStatus & (HOOK_KEY_ON_STATE | DIALING_STATE))) {
							HDST_RelayOn(); 		/* ハンドセットを拡張回線に接続する */
						}
					}
 #endif /* defined (KEISATSU) */
				}
#else
				SYS_RingCounter = 1;
#endif
			}
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/14 */
 #if (1) /* (PRO_CR_RINGING==ENABLE) モデムダイヤルインIR対応 O.Oshima2005/07/20 */
			if ((CHK_ModemDialinON()) && (NCU_ND_Status & ND_WAIT_FOR_CAR)) {
				if (SYS_RingCounter >= CHK_RingCount()) { /* 着信ベル回数。初期値6秒相当。*/
					if (CR_Ringing == OFF) {
						CR_Ringing = ON;
						ReverseRelayControl();
					}
				}
			}
 #endif
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
			/* 警察FAX DVT_ID18&ID25&ID26 Added by SMuratec 李 2005/11/07 */
			if (SYS_RingCounter == 1) {
				UpdateLCD();
			}
			if (DEBUG_NumberDisplay) {
				if (NCU_IsCarWaitedFor() && (SYS_LineNDStatus == ND_USED_IN_STD)) {  /* CAR 検出してよいか */
					if (SYS_RingCounter > 1) { /*ND ON で一般回線接続時、無条件に無鳴動着信しないように。 added by H.Kubo 1998/11/24 */
						CMN_DisableInterrupt();
						NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED;
						CMN_EnableInterrupt();
					}
				}
			}
			else {
				if (NCU_IsCarWaitedFor()) { /* CAR 検出してよいか *//* 条件が抜けている by O.Kimoto 2002/11/12 */
					if (SYS_RingCounter > 1) { /*ND ON で一般回線接続時、無条件に無鳴動着信しないように。 added by H.Kubo 1998/11/24 */
						CMN_DisableInterrupt();
						NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED;
						CMN_EnableInterrupt();
					}
				}
			}
 #else /* !defined (KEISATSU) */
			if (NCU_IsCarWaitedFor()) { /* CAR 検出してよいか *//* 条件が抜けている by O.Kimoto 2002/11/12 */
				if (SYS_RingCounter > 1) { /*ND ON で一般回線接続時、無条件に無鳴動着信しないように。 added by H.Kubo 1998/11/24 */
					CMN_DisableInterrupt();
					NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED;
					CMN_EnableInterrupt();
				}
			}
 #endif /* defined (KEISATSU) */
			if (NCU_ND_Status & ND_MODEM_DIALIN_DIAL) {
#if 0 /* NCU_IsCarWaitedFor() の仕様を変更したことに伴い、ここも変更します。Changed by H.Kubo 1998/12/04 */
@@				if (NCU_IsCarWaitedFor() && (NCU_ND_Status & ND_WAIT_FOR_2ND_RING) == ND_WAIT_FOR_2ND_RING) {
#else
				if ((NCU_ND_Status & ND_WAIT_FOR_2ND_RING) == ND_WAIT_FOR_2ND_RING) {
#endif
					if (SYS_RingCounter > 0) {
						return DETECT_FIRST_RING;			/* 呼出し音検出 */
					}
				}
#if 0 /* モデムダィヤルインの呼出し音停止検出処理修正のため、TEL1, TEL2 での着信防止処理を SetRingCounter() に移します。Deleted by H.Kubo 1998/12/14 */
@@				/** ２波目以降の検出タイマの再起動 */
@@				del_tsk(&tskno_TimeUpTask);
@@				cre_tsk(&tskno_TimeUpTask, TSK_NCU_TIMEUPTASK, 0);
@@				continue; /* モデムダイヤルイン着信処理では、リングカウンタを増やすだけで着信しない */
#endif
			}
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
			/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/12/06 */
			else if (NCU_ND_Status && (!DEBUG_NumberDisplay || (SYS_LineNDStatus == ND_USED_IN_STD))) {
 #else /* !defined (KEISATSU) */
			else if (NCU_ND_Status) { /* NCU_IsCarWaitedFor() is changed by H.Kubo 1998/11/26 */
 #endif /* defined (KEISATSU) */
				if ((NCU_ND_Status & ND_WAIT_FOR_2ND_RING) == ND_WAIT_FOR_2ND_RING) {
					if (SYS_RingCounter > 0) {
						return DETECT_FIRST_RING;			/* 呼出し音検出 */
					}
				}
				/* CAR 待ちでいきなり IR が来た場合は、呼出し音二回で DETECT_RING メッセージ送出 1998/10/26 */
				else if (((NCU_ND_Status & ND_WAIT_FOR_IR) && (SYS_RingCounter == 1)) /* 2 => 1 by H.Kubo 1998/11/26 /* CAR 待ちで IR がきた時の処理 */
				 || ((NCU_ND_Status & ND_CAR_DETECTED)&& ((SYS_RingCounter == 1)))) { /* CAR 検出後にいきなり IR がきた時の処理(OH が来ないときの対策。) added by H.Kubo 1998/10/23 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/26 */
 					if (DEBUG_NumberDisplay) {
						if (!((NCU_ND_Status & ND_CAR_DETECTED) && (SYS_RingCounterExt == 1))) {
							NCU_ND_InitializeStatus();
						}
						else {
							TxDetectCalledTaskMsg.Message = DETECT_RING;
							while (IsCiSndMsg){
								wai_tsk(1);
							}
							if (mailbox == mbxno.NCU_ND) {
								IsCiSndMsg = OK_CONT;
							}
							else {
								IsCiSndMsg = TRUE;
							}
							if (mailbox == mbxno.NCU_ND) {
								snd_msg(mailbox, &TxDetectCalledTaskMsg);
							}
							else if (tskno_NCU_TelephoneOperation != 0xFFFF) {
								snd_msg(mbxno.NCU_TelephoneOperationTask, &TxDetectCalledTaskMsg);
							}
							else {
								snd_msg(mailbox, &TxDetectCalledTaskMsg);
							}
							rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
							IsCiSndMsg = FALSE;
						}
					}
					else {
						/* 警察FAX (ナンバーディスプレイ) Modified by SMuratec 李 2005/11/25 */
						if (!((NCU_ND_Status & ND_CAR_DETECTED) && (SYS_RingCounter == 1))) {
							NCU_ND_InitializeStatus();
						}
						else {
							TxDetectCalledTaskMsg.Message = DETECT_RING;
							snd_msg(mailbox, &TxDetectCalledTaskMsg);
							rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
						}
					}
 #else /* !defined (KEISATSU) */
					TxDetectCalledTaskMsg.Message = DETECT_RING;
					snd_msg(mailbox, &TxDetectCalledTaskMsg);
					rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
 #endif /* defined (KEISATSU) */
				}
			}
#endif
/* 以下はナンバーディスプレイと共存不可。  mbxno.NCU_Task に直接メッセージを送っているので、整合が取れない by H.Kubo 1998/09/18 */
#if (PRO_CLASS1 == ENABLE)	/* Add Y.Tanimoto 96.04.08 */
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
			/* FAX待機の時はＰＣ側のベル鳴動を優先とし、ＰＣ受信可能な時は直ぐに RINGを出す事とする */
			if ((CMN_PresentReceiveMode() == SYS_FAX_READY)			/* FAX待機 */
			&&	(CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK)) {	/* PC受信可能である */
  #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/06/18 K.Kawata */
				if (CHK_UNI_Class1_EXT_Function()) {
			   		if ((!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM))	/* CLASS1動作中? */
					   && (SYS_CL1_Status == 0) && (CL1_ExtFunctionEnableFlag == 0)) {	/* ｸﾗｽ1拡張が動作中 */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM;	/* CLASS1動作中セット */
						CL1_ExtFunctionEnableFlag = 1;
                        #if (PRO_NUMBER_DISPLAY == ENABLE)	/* クラス１をナンバーディスプレイに対応させます by H.Hirao 1999/05/12 */
						if (mailbox == mbxno.NCU_Task) {
							return (CALLED_REQUEST);	/** 標準ライン着信 **/
						/*******1999.8.19 K.Kawata
							TxDetectCalledTaskMsg.Message = DETECT_RING;
							snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
							rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
						**************************/
						}
                        #else
						return (CALLED_REQUEST);	/** 標準ライン着信 **/
					/*******1999.8.19 K.Kawata
						TxDetectCalledTaskMsg.Message = DETECT_RING;
						snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
						rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
					*************************/
                        #endif
					}
				}
				else {
    #if (PRO_NUMBER_DISPLAY == ENABLE)	/* クラス１をナンバーディスプレイに対応させます by H.Hirao 1999/05/12 */
					if (mailbox == mbxno.NCU_Task) {
						TxDetectCalledTaskMsg.Message = DETECT_RING;
						snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
						rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
					}
    #else
					TxDetectCalledTaskMsg.Message = DETECT_RING;
					snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
					rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
    #endif
				}
  #else
    #if (PRO_NUMBER_DISPLAY == ENABLE)	/* クラス１をナンバーディスプレイに対応させます by H.Hirao 1999/05/12 */
				if (mailbox == mbxno.NCU_Task) {
					TxDetectCalledTaskMsg.Message = DETECT_RING;
					snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
					rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
				}
    #else
				TxDetectCalledTaskMsg.Message = DETECT_RING;
				snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
				rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
    #endif
  #endif
			}
  #if (PRO_DIALIN == ENABLE) /* Class1ダイヤルイン対応   */
   #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* デュアル制限のためＰＣ受信できへん場合も一時応答させる by H.Hirao 1999/05/12 */
			else if (CHK_DialinModeON() && !CHK_NumberDisplayON()			/* ダイヤルイン待機 *//* ナンバーディスプレイではない */
  			 &&	!(SYS_CL1_Status & CL1_DIALIN_CALLED)						/* ダイヤルイン呼び出し中でない */
			 && ((CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK)				/* ＰＣ受信可能である */
			  || (CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING_SCANNER_IN_USE)		/* スキャナ使用中やからＰＣ受信できへん */
			  || (CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING_PRINTER_IN_USE))) {	/* プリンタ使用中やからＰＣ受信できへん */
				return (CALLED_REQUEST);	/* ダイヤルイン一時応答させる */
			}
   #else
			else if (CHK_DialinModeON()										/* ダイヤルイン待機 */
  			 &&	!(SYS_CL1_Status & CL1_DIALIN_CALLED)						/* ダイヤルイン呼び出し中でない */
			 && (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK)) {			/* ＰＣ受信可能である */
				return (CALLED_REQUEST);	/* ダイヤルイン一時応答させる */
			}
   #endif
  #endif
			else {
 #else
		/* 下記条件のときＰＣ－ＦＡＸ受信を行います */
			if ((CHK_AutoRxSwitch() == TRUE)			/* 自動受信待機である */
			 && (CHK_DialinModeON() == 0)				/* ダイアルイン待機でない */
			 && (SYS_CL1_RxEnableFlag == 1)				/* Class1着信可能である */
			 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM)	/* PC-FAX SCAN原稿蓄積中でない */
			 && !(SYS_CL1_Status & CL1_LOCALSCAN)		/* PC-FAX SCAN中でない　*/
			 && !(SYS_CL1_Status & CL1_AUTOINIT)		/* PC-FAX INITIAL中でない */
			 && !(SYS_CL1_Status & CL1_LOCALPRINT)) {	/* PC-FAX PRINT中でない */
				TxDetectCalledTaskMsg.Message = DETECT_RING;
				snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
				rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
			}
			else {
 #endif /* PRO_CL1_TELFAX_LAN == ENABLE */
#endif
#if 1 /* This part is added by H.Kubo 1998/02/09 */
			if ( (!ci_freq_ok) && CHK_RingFreqAvailable()) {
				/* Nothing to do.  */
			}
#if (PRO_RING_MASTER == DISABLE)  /* added by H.Kubo 1998/02/10 */
			else if (!CHK_ContinueRing()
				&& ( (SamplingBuff[0] > CTRY_RingTable()->ContinueTime )
					|| (SamplingBuff[0] < CTRY_RingTable()->MinOnTime )
				) ) {
				/* 連続呼出しベル着信でないときは、不正なベルパターンで着信しない。 by H.Kubo 1998/02/10 */
			}
#endif
			else
#endif /* */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* メモリオーバーなどによるモデムダィヤルイン FAX 着信拒否の処理を追加。 by H.Kubo 1999/02/25 */
			if ((NCU_ND_Status & ND_MODEM_DIALIN_FAX_DIAL) && (NCU_ND_Status & ND_COUNTING_2ND_RING)) {
				TxDetectCalledTaskMsg.Message = DETECT_2ND_RING;
				snd_msg(mailbox, &TxDetectCalledTaskMsg); /*  呼び出し音検出。*/
				rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
			}
			else
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/08 */
				if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
					if (SYS_RingCounter >= SetRingCounter()) {			/** 着信条件を満たした */
						if ( ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE)	/* 拡張回線には通信中 */
							|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) 	/* 拡張回線には本体使用中 */
							|| (CHK_KEIDENRxPriority() && ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)) ){ /* 警電優先受信ＯＮ及び警電受話中 */
							/* ここで動作しない */
						}
						else {
							return (CALLED_REQUEST);	/**	標準ライン着信	*/
						}
					}
				}
				else {
					if (SYS_RingCounterExt >= GetRingCounter(1)) {			/** 着信条件を満たした */
						if ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE)	/* 標準回線には通信中 */
							|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ){ 	/* 標準回線には本体使用中 */
							if ( (CHK_KEIDENRxPriority())	/* 警電優先受信機能が有効されている場合 */
								&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
								/* 通信中断していない場合 */
								SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
								/* 警察FAX DVT_ID42 Added by SMuratec 李 2005/11/16 */
								UpdateLCD();
								while ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE)	/* 標準回線には通信中 */
										|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ){ 	/* 標準回線には本体使用中 */
									wai_tsk(1);
								}
								wai_tsk(1);
								return (CALLED_REQUEST_EXT);	/**	拡張ライン着信	*/
							}
						}
						else {
							return (CALLED_REQUEST_EXT);	/**	拡張ライン着信	*/
						}
					}
				}
 #else /* !defined (KEISATSU) */
			if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
				if (SYS_RingCounter >= SetRingCounter()) {			/** 着信条件を満たした */
					return (CALLED_REQUEST);	/**	標準ライン着信	*/
				}
			}
			else {
				if (SYS_RingCounterExt >= CHK_RingCount()) {			/** 着信条件を満たした */
					return (CALLED_REQUEST_EXT);	/**	拡張ライン着信	*/
				}
			}
 #endif /* defined (KEISATSU) */
#else
			if (SYS_RingCounter >= SetRingCounter()) {			/** 着信条件を満たした */
 /* 以下はナンバーディスプレイと共存不可。  mbxno.NCU_Task に直接メッセージを送っているので、整合が取れない by H.Kubo 1998/09/18 */
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
				/* FAX待機の時はＰＣ側のベル鳴動を優先とし、ＰＣ受信可能な時は直ぐに RINGを出す事とする */
				if ((CMN_PresentReceiveMode() == SYS_FAX_READY)			/* FAX待機 */
				&&	(CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK)) {	/* PC受信可能である */
  #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/06/18 K.Kawata */
					if (CHK_UNI_Class1_EXT_Function()) {
				   		if ((!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM))	/* CLASS1動作中? */
						   && (SYS_CL1_Status == 0) && (CL1_ExtFunctionEnableFlag == 0)) {	/* ｸﾗｽ1拡張が動作中 */
							SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM;	/* CLASS1動作中セット */
							CL1_ExtFunctionEnableFlag = 1;
                        #if (PRO_NUMBER_DISPLAY == ENABLE)	/* クラス１をナンバーディスプレイに対応させます by H.Hirao 1999/05/12 */
							if (mailbox == mbxno.NCU_Task) {
								return (CALLED_REQUEST);	/** 標準ライン着信 **/
							/*******1999.8.19 K.Kawata
								TxDetectCaledTaskMsg.Message = DETECT_RING;
								snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
								rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
							************************/
							}
                        #else
							return (CALLED_REQUEST);	/** 標準ライン着信 **/
						/*******1999.8.19 K.Kawata
							TxDetectCalledTaskMsg.Message = DETECT_RING;
							snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
							rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
						*************************/
                        #endif
						}
					}
					else {
    #if (PRO_NUMBER_DISPLAY == ENABLE)	/* クラス１をナンバーディスプレイに対応させます by H.Hirao 1999/05/12 */
						if (mailbox == mbxno.NCU_Task) {
							TxDetectCalledTaskMsg.Message = DETECT_RING;
							snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
							rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
						}
    #else
						TxDetectCalledTaskMsg.Message = DETECT_RING;
						snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
						rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
    #endif
					}
  #else
    #if (PRO_NUMBER_DISPLAY == ENABLE)	/* クラス１をナンバーディスプレイに対応させます by H.Hirao 1999/05/12 */
					if (mailbox == mbxno.NCU_Task) {
						TxDetectCalledTaskMsg.Message = DETECT_RING;
						snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
						rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
					}
    #else
					TxDetectCalledTaskMsg.Message = DETECT_RING;
					snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
					rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
    #endif
  #endif
				}
				else if ((CMN_PresentReceiveMode() == SYS_FAX_READY)			/* FAX待機である */
				   && (CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING)) {			/* ＰＣ受信／ＦＡＸ受信とも不可である */
					TxDetectCalledTaskMsg.Message = IGNORE_RING;
					snd_msg(mbxno.NCU_Task, &TxDetectCalledTaskMsg);
					rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
				}
   #if (PRO_NUMBER_DISPLAY == ENABLE) /* ND でメモリーオーバーで着信拒否を考慮。changed by H.Kubo 1999/02/26 */
    #if (PRO_RS_INTERNAL == ENABLE)	/* デュアル制限のためＰＣ受信できへん場合、ＣＩ検出中をセットする by H.Hirao 1999/05/12 */
				else if ((CHK_AutoRxSwitch() == TRUE)
				   && (CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING_SCANNER_IN_USE)) {
					SYS_CalledRequestForDocStore = 1;
				}
				else if ((CHK_AutoRxSwitch() == TRUE)
				   && (CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING_PRINTER_IN_USE)) {
					SYS_CalledRequestForDocStore = 1;
				}
    #endif
				else if (NCU_ND_Status & (ND_COUNTING_2ND_RING | ND_WAIT_FOR_2ND_RING)) {
					TxDetectCalledTaskMsg.Message = DETECT_CALLED_REQUEST_ND;
					snd_msg(mailbox, &TxDetectCalledTaskMsg); /*  呼び出し音検出。*/
					rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
				}
   #endif
				else {
					return (CALLED_REQUEST);
				}
 #else
  #if (PRO_NUMBER_DISPLAY == ENABLE) /* ND でメモリーオーバーで着信拒否を考慮。changed by H.Kubo 1999/02/26 */
				if (NCU_ND_Status & (ND_COUNTING_2ND_RING | ND_WAIT_FOR_2ND_RING)) {
					TxDetectCalledTaskMsg.Message = DETECT_CALLED_REQUEST_ND;
					snd_msg(mailbox, &TxDetectCalledTaskMsg); /*  呼び出し音検出。*/
					rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
				}
				else {
					return (CALLED_REQUEST);
				}
  #else
				return (CALLED_REQUEST);
  #endif
 #endif
			}
#endif
	#if (PRO_CLASS1 == ENABLE)	/* Add By Y.Tanimoto 96.04.08 */
			}
	#endif

		}
#if (PRO_RING_MASTER == ENABLE)		/* For MBS	1995/05/24 */
		}
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/16 */ /* 上から移動してきました。 by H.Kubo 1998/11/17 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
		if (!DEBUG_NumberDisplay || SYS_LineNDStatus == ND_USED_IN_STD) {  /* CAR 検出してよいか */
 #endif /* defined (KEISATSU) */
		/* CI_CYCLE_TIMEUP で抜けてきた場合の CAR 検出と呼出音停止の検出 */
		car_detection_result = NCU_CheckCarAfterCiCycleTimeup(ci_end_time, &ci_start_time, &buff_counter);
		switch (car_detection_result) {
		case DETECT_CAR:
			return DETECT_CAR;
			break;
		case DETECT_IR_STOP:
			/* */ 
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
 			if (DEBUG_NumberDisplay) {
				TxDetectCalledTaskMsg.Message = DETECT_2ND_RING_TIMEUP;
				while (IsCiSndMsg){
					wai_tsk(1);
				}
				if (mailbox == mbxno.NCU_ND) {
					IsCiSndMsg = OK_CONT;
				}
				else {
					IsCiSndMsg = TRUE;
				}
				if (mailbox == mbxno.NCU_ND) {
					snd_msg(mailbox, &TxDetectCalledTaskMsg); /* 呼出音検出やめさせる。 */
				}
				else if (tskno_NCU_TelephoneOperation != 0xFFFF) {
					snd_msg(mbxno.NCU_TelephoneOperationTask, &TxDetectCalledTaskMsg);
				}
				else {
					snd_msg(mailbox, &TxDetectCalledTaskMsg); /* 呼出音検出やめさせる。 */
				}
				rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
				IsCiSndMsg = FALSE;
			}
			/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/29 */
			else {
				/* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/12/02 */
				RingStatus &= ~CI_DETECT_TIMEUP;
				/* 警察FAX (QAT対応) Modified by SMuratec 李 2005/12/08 */
				if ( ((NCU_LineStatus & STD_LINE_STATUS) != STD_TEL_RECEIVE)	/* 標準回線には受話中ではない */
					&& ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) ) {	/* 標準回線には本体使用中ではない */
					SYS_RingCounter = 0;
				}
				if ((NCU_LineStatus & STD_LINE_STATUS) == STD_CI_IN) {
					NCU_LineStatus &= ~STD_LINE_STATUS;
					NCU_LineStatus  |=  (STD_LINE_STATUS & STD_NOT_USE);
				}
				/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/12/07 */
				while (IsCiSndMsg){
					wai_tsk(1);
				}
				IsCiSndMsg = TRUE;
				TxDetectCalledTaskMsg.Message = DETECT_2ND_RING_TIMEUP;
				snd_msg(mailbox, &TxDetectCalledTaskMsg); /* 呼出音検出やめさせる。 */
				rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
				IsCiSndMsg = FALSE;
				break;
			}
			break;
 #else /* defined (KEISATSU) */
			TxDetectCalledTaskMsg.Message = DETECT_2ND_RING_TIMEUP;
			snd_msg(mailbox, &TxDetectCalledTaskMsg); /* 呼出音検出やめさせる。 */
			rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
			break;
 #endif /* defined (KEISATSU) */
		default:
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/09/08 */
/* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/12/02 */
#if 1 /* 警察FAX DVT_ID18&25&26 Modify by SMuratec 李 2005/11/14 */
			if (RingStatus & CI_DETECT_TIMEUP) {		/** リングトーン検出時間のタイムアップ */
				/*--------------------------------------------------------*/
				/** リングカウンタを初期化し､リングトーン検出を終了します */
				/*--------------------------------------------------------*/
				if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
#else
@@				if (RingStatus2nd & CI_DETECT_TIMEUP) {		/** リングトーン検出時間のタイムアップ */
@@				/*--------------------------------------------------------*/
@@				/** リングカウンタを初期化し､リングトーン検出を終了します */
@@				/*--------------------------------------------------------*/
@@				if (RingStatus2nd & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
#endif
					if ( ((NCU_LineStatus & STD_LINE_STATUS) != STD_TEL_RECEIVE)	/* 標準回線には受話中ではない */
						&& ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) ) {	/* 標準回線には本体使用中ではない */
						/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
						if (DEBUG_NumberDisplay) {
							if ((SYS_LineNDStatus == ND_USED_IN_STD) && (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR | ND_CALL_ACCEPTED))) {
								NCU_ND_InitializeStatus(); /* 初期状態に戻す */
							}
						}
						SYS_RingCounter = 0;
					}
					if ((NCU_LineStatus & STD_LINE_STATUS) == STD_CI_IN) {
						NCU_LineStatus &= ~STD_LINE_STATUS;
						NCU_LineStatus  |=  (STD_LINE_STATUS & STD_NOT_USE);
					}
					H_RelayOff();	/**	Hリレー戻します	*/
					if ( !ModemRelaySetting() ) {	/* モデムリレーを標準回線に接続している場合 */
						CONT_24V_Off();
					}
				}
				else {
					if ( ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_TEL_RECEIVE)	/* 拡張回線には受話中ではない */
						&& ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) ) {	/* 拡張回線には本体使用中ではない */
						SYS_RingCounterExt = 0;
					}
					if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_CI_IN) {
						NCU_LineStatus &= ~EXT_LINE_STATUS;
						NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_NOT_USE);
					}
					L_RelayOff();	/**	Lリレーも戻します	*/
					if ( ModemRelaySetting() ) {	/* モデムリレーを拡張回線に接続している場合 */
						CONT_24V_Off();
					}
				}
				RingStatus &= ~CI_DETECT_TIMEUP;
				return (RING_NOT_AVAILABLE);
			}
#endif /* defined (KEISATSU) */
			break;
		}
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
		}
 #endif /* defined (KEISATSU) */
#endif

/*#if (PRO_LINENUMBER == TWICE_LINE)@* V851着信不可対策 By Y.Suzuki 2002/09/10 */
/* 効き目なし*/
#if(0)
//		RingStatus &= ~(CI_STD_LINE | CI_EXT_LINE);
#endif

		/** ２波目以降の検出タイマの再起動 */
		del_tsk(&tskno_TimeUpTask);
		cre_tsk(&tskno_TimeUpTask, TSK_NCU_TIMEUPTASK, 0);
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信検出をしてもよい条件]
	function	:[
		1.ＣＩ検出の許可を判定し、リターンします
	]
	return		:[
		0			着信禁止
		1			着信許可
	]
	common		:[
		UBYTE RingBuzzerFlag
		UBYTE CI_DummyFlag
		UWORD  NCUStatus
		UWORD  SYS_RingCounter
		UWORD  OhPortStatus
		UWORD  Tel1OhCounter
		UWORD  Tel2OhCounter
		UWORD  BRCOhTelCounter
		UWORD  AfterCI_HL_RelayOn
	]
	condition	:[]
	comment		:[
		Ｈ８の場合、内線通話中及びCI_DummyFlagがONの時は、
		無条件で検出許可をリターンします
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE  CiCheckRequest(void)
{
#if (PRO_NUMBER_DISPLAY == ENABLE) /* Changed by H.Kubo 1998/10/12 */
 #if 0 /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/20 */
**#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/11 */
**	if (!(SYS_CalledLineNumber & SYS_TWICE_LINE_IN_CI)) {
**#endif /* defined (KEISATSU) */
 #endif
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/11/23 */
 	if (DEBUG_NumberDisplay) {
		if (NCU_ND_Status && (SYS_LineNDStatus == ND_USED_IN_STD))  { /* CHK_NumberDisplayON() is Changed by H.Kubo 1998/11/28 */
			if ((NCU_ND_Status  & ND_WAIT_FOR_CAR_AND_IR)) {
				SYS_RingCounter = 0;
			}
			else if ((SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & (SYS_ND_SILENT_WHILE_IR_DETECT | SYS_ND_COUNT_HEARABLE_IR))
					 == (SYS_ND_SILENT_WHILE_IR_DETECT | SYS_ND_COUNT_HEARABLE_IR)) {
				SYS_RingCounter = 0; /* added by H.Kubo 1998/11/28 */
			}
			else {
			}
		}
		else {
			SYS_RingCounter = 0;
		}
	}
	else {
		if (NCU_ND_Status)  { /* CHK_NumberDisplayON() is Changed by H.Kubo 1998/11/28 */
			if ((NCU_ND_Status  & ND_WAIT_FOR_CAR_AND_IR)) {
				SYS_RingCounter = 0;
			}
			else if ((SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & (SYS_ND_SILENT_WHILE_IR_DETECT | SYS_ND_COUNT_HEARABLE_IR))
					 == (SYS_ND_SILENT_WHILE_IR_DETECT | SYS_ND_COUNT_HEARABLE_IR)) {
				SYS_RingCounter = 0; /* added by H.Kubo 1998/11/28 */
			}
			else {
			}
		}
		else {
			SYS_RingCounter = 0;
		}
	}
 #else /* !defined (KEISATSU) */
	if (NCU_ND_Status)  { /* CHK_NumberDisplayON() is Changed by H.Kubo 1998/11/28 */
		if ((NCU_ND_Status  & ND_WAIT_FOR_CAR_AND_IR)) {
			SYS_RingCounter = 0;
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
			SYS_RingCounterExt = 0;
 #endif
		}
		else if ((SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & (SYS_ND_SILENT_WHILE_IR_DETECT | SYS_ND_COUNT_HEARABLE_IR))
				 == (SYS_ND_SILENT_WHILE_IR_DETECT | SYS_ND_COUNT_HEARABLE_IR)) {
			SYS_RingCounter = 0; /* added by H.Kubo 1998/11/28 */
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 */
			SYS_RingCounterExt = 0;
 #endif
		}
		else {
		}
	}
	else {
		SYS_RingCounter = 0;
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
		SYS_RingCounterExt = 0;
 #endif
	}
 #if 0 /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/20 */
**#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/11 */
**	}
**#endif /* defined (KEISATSU) */
 #endif
 #endif /* defined (KEISATSU) */
#else
	SYS_RingCounter = 0;
 #if !defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/20 */
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
	SYS_RingCounterExt = 0;
 #endif
 #endif /* !defined (KEISATSU) */
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/27 */
	if (RingStatus & CI_STD_LINE) {
		if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
			if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)) {
				if (!(Tel1OhCounter = Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
					Tel1OhCounter = 40;
					Tel2OhCounter = 40;
				}
				CI_Counter = 0;
				return (0);
			}
		}
		else {
			if (NCUStatus & TELEPHONE1_OFF_HOOK) {
				if (!(Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
					Tel1OhCounter = 40;
				}
				CI_Counter = 0;
				return (0);
			}
		}
	}
	else {
		if (CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が拡張ラインの場合	*/
			if (NCUStatus & TELEPHONE2_OFF_HOOK) {
				if (!(Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))) {	/* '96,04,15 10ms単位--->100ms単位 NEWMEM By N.S. *//* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
					Tel2OhCounter = 40;
				}
				CI_Counter = 0;
				return (0);
			}
		}
	}
#if defined (KEISATSU)
	if (RingStatus & CI_STD_LINE) {
#if 0 /* 警察FAX DVT_ID65 Added by SMuratec 李 2005/12/13 */
@@		if (!ModemRelaySetting()){ /* モデムを標準回線に接続されている場合 */
#else
		if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
#endif
			/** CMLリレーがOFFで、リレー動作直後でないなら */
			if (!CML_RelaySetting() && !AfterCI_HL_RelayOn) {
				return (1);			/** CI検出許可	*/
			}
		}
		else {
			return (1);			/** CI検出許可	*/
		}
	}
	else {
		if (ModemRelaySetting()){ /* モデムを拡張回線に接続されている場合 */
			/** CMLリレーがOFFで、リレー動作直後でないなら */
			if (!CML_RelaySetting() && !AfterCI_HL_RelayOn) {
				return (1);			/** CI検出許可	*/
			}
		}
		else {
			return (1);			/** CI検出許可	*/
		}
	}
#else /* !defined (KEISATSU) */
	/** CMLリレーがOFFで、リレー動作直後でないなら */
	if (!CML_RelaySetting() && !AfterCI_HL_RelayOn) {
		return (1);			/** CI検出許可	*/
	}
#endif /* defined (KEISATSU) */
	CI_Counter = 0;				/* 1994/10/25 */
	return (0);					/** CI検出不許可  */
#else
	/** TEL1/TEL2/ブランチがオフフックなら、OHカウンタを初期化し、"CI検出不許可"でリターン */
	if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)) {
		if (!(Tel1OhCounter = Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))) {	/* '96,04,15 10ms単位--->100ms単位 NEWMEM By N.S. *//* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
			Tel1OhCounter = 40;
			Tel2OhCounter = 40;
		}
	}
	else {
		/** CMLリレーがOFFで、リレー動作直後でないなら */
		if (!CML_RelaySetting() && !AfterCI_HL_RelayOn) {
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
 #if (PRO_NUMBER_DISPLAY == ENABLE)	/* by H.Hirao 1999/05/07 */
			return (1);			/** CI検出許可	*/
 #else
			/*
			** スキャン中とプリント中にＣＩを検出した場合、スキャンとプリントをページ間で停止させてからクラス１受信させる
			** by H.Hirao 1999/03/03
			*/
			
			if ((CHK_AutoRxSwitch() == TRUE)			/* 自動受信待機である */
			 && (SYS_CL1_RxEnableFlag == 1)				/* Class1着信可能である */
			 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM)	/* PC-FAX SCAN原稿蓄積中でない */
			 && !(SYS_CL1_Status & CL1_LOCALSCAN)		/* PC-FAX SCAN中でない　*/
			 && !(SYS_CL1_Status & CL1_AUTOINIT)		/* PC-FAX INITIAL中でない */
			 && !(SYS_CL1_Status & CL1_LOCALPRINT)) {	/* PC-FAX PRINT中でない */
			 	/* by H.Hirao 1999/04/02 */
				CMN_DisableInterrupt();
				SYS_CalledRequestForDocStore = 1;	/* スキャンとプリントをページ間で停止させるための着信要求有りのフラグセット */
				if (((CL1_DualRestrictionStatus & CL1_SCANNER_IN_USE) != CL1_SCANNER_IN_USE)		/* スキャン中でない場合 */
				 && ((CL1_DualRestrictionStatus & CL1_PRINTER_IN_USE) != CL1_PRINTER_IN_USE)) {		/* プリント中でない場合 */
				 	CL1_DualRestrictionStatus |= CL1_CLASS1_IN_USE;	/* クラス１受信中セット */
				 	CMN_EnableInterrupt();
					return (1);	/* CI検出許可 */
				}
				else {
					CMN_EnableInterrupt();
					return (0);	/* CI検出不許可 */
				}
			}
			else {
				return (1);	/* CI検出許可 */
			}
 #endif
#else
			return (1);			/** CI検出許可	*/
#endif
		}
	}
	CI_Counter = 0;				/* 1994/10/25 */
	return (0);					/** CI検出不許可  */
#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信検出タスク]
	function	:[
		1.１発目のＣＩ、又はＦネット着信のイベントを待つ
		2.親タスクに着信検出状況を通知する
	]
	return		:[なし]
	common		:[
		UBYTE CI_DummyFlag
		UWORD  RingStatus
	]
	condition	:[]
	comment		:[
		Ｈ８の場合、タスクのクリエイト時にＣＩのタイムアップ時間、
		SYS_RingCounterを保持します
		この間の自動発呼は不可となります
	]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_DetectCalledTask(WORD *tx_mail_box_no)
{
	MESSAGE_t *RxDetectCalledTaskMsg;

	RingStatus = RING_STATUS_INITIAL;

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/14 */
	RingStatus2nd = RING_STATUS_INITIAL;
#endif /* defined (KEISATSU) */

	TxDetectCalledTaskMsg.Item = FROM__NCU_RING;

#if defined(JPN)
	tskno_DetectFnetTask		 = 0xFFFF;
	tskno_ToneDetectPattern0Task = 0xFFFF;
	tskno_FilterOnOffDetectTask	 = 0xFFFF;
#endif
	tskno_TimeUpTask			 = 0xFFFF;
	tskno_FrequencyCheckTask	 = 0xFFFF;
	ToneDetectTaskInitial();	/** ATDタスクIDの初期化 */

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/14 */
#else /* defined (KEISATSU) */
#if defined(JPN)
	cre_tsk(&tskno_DetectFnetTask, TSK_NCU_DETECTFNETTASK, 0);
#endif
#endif /* defined (KEISATSU) */

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/11 */
#if 0 /* 2回線呼出監視仕様変更 Deleted by SMuratec 李 2005/10/19 */
**	tskno_Detect2ndCalledTask 	= 0xFFFF;
**	cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, tx_mail_box_no);
#endif
	
	InitializeGrovalData();
#endif /* defined (KEISATSU) */

#if defined(SATSUKI2) || defined(STOCKHM2) /* CI割込み救済 O.Oshima 2003/11/26 */
	if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
		OutputWORD(GA_INT_REC, IO_BIT_CI_INT);	/* 割込み受領のみ出す。 */
	}
#endif

#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
	CR_Ringing = OFF;
#endif

	while (1) {
		/*--------------------------------------------------------------------------------*/
		/** 以下を実現するために追加							1994/08/20	  TH92115	  */
		/** ・着信不可ではじかれている間に受話器をオフフックされてもSYS_RingCounterを保存 */
		/** ・着信不可ではじかれた直後にＣＩがなくてもSYS_RingCounterをタイムアップで消去 */
		/** 但し、一度待機に戻ると約１０秒間は自動発呼しません(PRE_LINE_BUSYが立っている) */
		/*--------------------------------------------------------------------------------*/
		wai_evt(EVT_CI_CHECK);		/**	１発目のＣＩ、又はＦネット着信のイベントを待つ */

#if defined(JPN)
		if (RingStatus & F_NET_CALLED_SIGNAL) {		/** Ｆネット着信検出 */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
			if (!CHK_UNI_F_NET_ExtLineEnable()) {	/**	MODEMリレーが標準ライン側のとき	*/
				TxDetectCalledTaskMsg.Message = DETECT_F_NET_CALLED_SIGNAL;	/**	標準ラインでのF網検出	*/
			}
			else {	/**	MODEMリレーが拡張ライン側のとき	*/
				TxDetectCalledTaskMsg.Message = DETECT_F_NET_CALLED_SIGNAL_EXT;	/**	拡張ラインでのF網検出	*/
			}
#else
			TxDetectCalledTaskMsg.Message = DETECT_F_NET_CALLED_SIGNAL;
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 着信履歴に記録します。 added by H.Kubo 1998/11/28 */
			if (SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & SYS_ND_FNET_CALL_MEMORIZE) {
 #if (PRO_NCU_TYPE == HINOKI_TYPE)
 				/*
 				** ＮＤがＯＮでＦ網着信した時に、備考欄にファックスが印字されない
 				** SYS_ND_CurrentJournalPointをもらった後、NCU_TaskでNCU_ND_StatusのND_CALL_ACCEPTEDを立てる前にSYS_ND_CurrentJournalPoint
 				** を初期化するパスを通るためここで、ND_CALL_ACCEPTEDを立ててからSYS_ND_CurrentJournalPointをもらってきます by H.Hirao 1999/03/01
 				*/
				NCU_ND_Status |= ND_CALL_ACCEPTED;
 #endif
				SYS_ND_CurrentJournalPoint = CMN_ND_SetFnetHistory();
			}
#endif
			DetCallChildTaskExit();					/* 1994/09/26 */
			snd_msg(*tx_mail_box_no, &TxDetectCalledTaskMsg);
			rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
			if (OK_EXIT == RxDetectCalledTaskMsg->Message) {
				wai_tsk(0xFFFF);
			}
			else {		/* 1994/09/15 */
				cre_tsk(&tskno_DetectFnetTask, TSK_NCU_DETECTFNETTASK, 0);
			}
		}
#endif
		if (RingStatus & CI_ON) {					/** １発目のＣＩを検出 */
			if (CiCheckRequest()) {					/** ＣＩチェックをしてもよい条件なら */
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/07 */
 #if 0				/* 警察FAX (ナンバーディスプレイ) Modified by SMuratec 李 2005/12/06 */
@@ 				if (!(NCUStatus & DETECT_CI_STATE)) {
 #else
				if (NCU_ND_Status & ND_COUNTING_2ND_RING) {
					if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了メッセージを投げさせない */
						del_tsk(&tskno_NCU_ND_Rx);
					}
				}
 				if (!(NCUStatus & DETECT_CI_STATE) || (*tx_mail_box_no == mbxno.NCU_ND)) {
 #endif
					NCUStatus |= DETECT_CI_STATE;
					/*-----------------------------*/
					/** ＣＩ検出中であることを通知 */
					/*-----------------------------*/
					TxDetectCalledTaskMsg.Message = DETECT_CI;
					while (IsCiSndMsg){
						wai_tsk(1);
					}
					if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
						IsCiSndMsg = TRUE;
						if (tskno_NCU_TelephoneOperation != 0xFFFF) {
							snd_msg(mbxno.NCU_TelephoneOperationTask, &TxDetectCalledTaskMsg);
						}
						else {
							snd_msg(*tx_mail_box_no, &TxDetectCalledTaskMsg);
						}
						rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
						IsCiSndMsg = FALSE;
					}
				}
				/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/12/06 */
				else if (NCU_ND_Status & ND_COUNTING_2ND_RING) {
					if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了メッセージを投げさせない */
						del_tsk(&tskno_NCU_ND_Rx);
					}
				}
 #else /* !defined (KEISATSU) */
				NCUStatus |= DETECT_CI_STATE;
				/*-----------------------------*/
				/** ＣＩ検出中であることを通知 */
				/*-----------------------------*/
				TxDetectCalledTaskMsg.Message = DETECT_CI;
				snd_msg(*tx_mail_box_no, &TxDetectCalledTaskMsg);
				rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
 #endif /* defined (KEISATSU) */
				/*---------------------------------*/
				/**	２発目以降のＣＩ検出を行います */		/* 1994/10/24 */
				/*---------------------------------*/
#if (PRO_NUMBER_DISPLAY == ENABLE)  /* modified by H.Kubo 1998/10/20 */
				switch (DetectRingToneAndCar(*tx_mail_box_no)) {
#else
				switch (DetectRingTone()) {
#endif
				case CALLED_REQUEST:		/** 着信!! */
					TxDetectCalledTaskMsg.Message = DETECT_CALLED_REQUEST;
#if 0 /* (PRO_NUMBER_DISPLAY == ENABLE) */ /* added by H.Kubo 1998/07/02 */
@@					if (CHK_NumberDisplayON() && !(SYB_SettingStatus[SETTING_STATUS_30] & ND_TEL2_ND_ON)
@@					&& 	!(NCU_ND_Status & ND_WAIT_FOR_2ND_RING)) {
@@						TxDetectCalledTaskMsg.Message = DETECT_ND_CAR_CALLED_SIGNAL;
@@					}
@@					else {
@@						TxDetectCalledTaskMsg.Message = DETECT_CALLED_REQUEST;
@@					}
#endif
					break;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
				case CALLED_REQUEST_EXT:		/** 疑似２回線 拡張ライン着信 by T.Soneoka 1997/11/21 */
					TxDetectCalledTaskMsg.Message = DETECT_CALLED_REQUEST_EXT;
					break;
#endif
#if defined(JPN)
				case DETECT_F_NET:			/** Ｆネット着信! */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
					if (!CHK_UNI_F_NET_ExtLineEnable()) {	/**	MODEMリレーが標準ライン側のとき	*/
						TxDetectCalledTaskMsg.Message = DETECT_F_NET_CALLED_SIGNAL;	/**	標準ラインでのF網検出	*/
					}
					else {	/**	MODEMリレーが拡張ライン側のとき	*/
						TxDetectCalledTaskMsg.Message = DETECT_F_NET_CALLED_SIGNAL_EXT;	/**	拡張ラインでのF網検出	*/
					}
#else
					TxDetectCalledTaskMsg.Message = DETECT_F_NET_CALLED_SIGNAL;
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 着信履歴に記録します。 added by H.Kubo 1998/10/23 */
					if (SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & SYS_ND_FNET_CALL_MEMORIZE) { /* added by H.Kubo 1998/11/28 */
						SYS_ND_CurrentJournalPoint = CMN_ND_SetFnetHistory();
					}
#endif
					break;
#endif
				case RING_NOT_AVAILABLE:	/** タイムアップ */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/07 */
 #else /* !defined (KEISATSU) */
					/* V851 tel2(拡張回線)ｵﾌﾌｯｸ中にtel1で通話、保留、保留解除、通話終了
					 * 再度tel1で通話、保留すると保留がすぐ解除されてしまう。By Y.Suzuki 2002/09/13
					 */
					/*H_RelayOff();By Y.Suzuki 2002/09/13*/
					if(!(NCUStatus & HOLD_STATE)) {
						H_RelayOff();	/**	Hリレー戻します	*/
					}
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
						L_RelayOff();	/**	Lリレーも戻します	*/
					}
 #endif /* defined (KEISATSU) */
#else
					H_RelayOff();
					L_RelayOff();
#endif
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/07 */
					if (!(RingStatus2nd & (CI_STD_LINE | CI_EXT_LINE))) {
						AfterCI_TimerSet();
					}
					/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
					if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
						del_tsk(&tskno_NCU_ND_Rx);
					}
					NCU_ND_InitializeStatus();
 #else /* !defined (KEISATSU) */
					CONT_24V_Off();
					AfterCI_TimerSet();
 #endif /* defined (KEISATSU) */
					TxDetectCalledTaskMsg.Message = DETECT_CI_TIMEUP;
					break;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* CAR 検出 added by H.Kubo 1998/08/04 */
				case DETECT_CAR:
					TxDetectCalledTaskMsg.Message = DETECT_ND_CAR_CALLED_SIGNAL;
					break;
				case DETECT_FIRST_RING:     /** IR の第一波を検出 added by H.Kubo 1998/09/18 */
					TxDetectCalledTaskMsg.Message = DETECT_RING;
					break;
#endif
				default:
					break;
				}
				DetCallChildTaskExit();					/* 1994/09/26 */
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/07 */
				while (IsCiSndMsg) {
					wai_tsk(1);
				}
				if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)
					&& !((RingStatus2nd & (CI_STD_LINE | CI_EXT_LINE)) 
					&& (TxDetectCalledTaskMsg.Message == DETECT_CI_TIMEUP))) {
#if 0 /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/20 */
**					IsCiSndMsg = TRUE;
#else
					if (DEBUG_NumberDisplay) {
						if (*tx_mail_box_no == mbxno.NCU_ND) {
							IsCiSndMsg = OK_CONT;
						}
						else {
							IsCiSndMsg = TRUE;
						}
					}
					else {
						IsCiSndMsg = TRUE;
					}
					if (DEBUG_NumberDisplay && (*tx_mail_box_no == mbxno.NCU_ND)) {
						snd_msg(*tx_mail_box_no, &TxDetectCalledTaskMsg);
					}
					else
#endif
					if (tskno_NCU_TelephoneOperation != 0xFFFF) {
						snd_msg(mbxno.NCU_TelephoneOperationTask, &TxDetectCalledTaskMsg);
					}
					else {
						snd_msg(*tx_mail_box_no, &TxDetectCalledTaskMsg);
					}
					rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
					IsCiSndMsg = FALSE;
				}
				else {
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/04 */
					if (DEBUG_NumberDisplay) {
						if (TxDetectCalledTaskMsg.Message == DETECT_CI_TIMEUP) {
							if (SYS_LineNDStatus != ND_USED_IN_STD) {	/**	拡張回線	*/
								SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
							}
						}
					}
#endif
					UpdateLCD();
				}
 #else /* !defined (KEISATSU) */
				snd_msg(*tx_mail_box_no, &TxDetectCalledTaskMsg);
				rcv_msg(mbxno.NCU_DetectCalledTask, &RxDetectCalledTaskMsg);
				if (OK_EXIT == RxDetectCalledTaskMsg->Message) {
					wai_tsk(0xFFFF);
				}
#if defined(JPN)
				else {		/* 1994/09/15 */
					cre_tsk(&tskno_DetectFnetTask, TSK_NCU_DETECTFNETTASK, 0);
				}
#endif
 #endif /* defined (KEISATSU) */
			}
			else {
#if defined (KEISATSU) /* 2回線呼出監視仕様変更 Deleted by SMuratec 李 2005/10/19 */
				if ( ((NCU_LineStatus & STD_LINE_STATUS) != STD_COM_IN_USE)	/* 標準回線には通信中 */
					&& ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) ){ 	/* 標準回線には本体使用中 */
					H_RelayOff();	/**	Hリレー戻します	*/
				}
#else /* !defined (KEISATSU) */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
				H_RelayOff();	/**	Hリレー戻します	*/
				if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
					L_RelayOff();	/**	Lリレーも戻します	*/
				}
#else
				H_RelayOff();
				L_RelayOff();
#endif
				CONT_24V_Off();
				AfterCI_TimerSet();
#endif /* defined (KEISATSU) */
			}
		}
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信検出タスクの子タスク終了ルーチン]
	function	:[
		1.子タスクを強制終了し、ステータスを戻す
	]
	return		:[なし]
	common		:[
		UWORD  NCUStatus
		UWORD  RingStatus
		UBYTE Ringing
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  DetCallChildTaskExit(void)
{
#if defined(JPN)
	FnetChildTaskExit();
	if (tskno_DetectFnetTask != 0xFFFF) {
		del_tsk(&tskno_DetectFnetTask);
	}
#endif
	if (tskno_FrequencyCheckTask != 0xFFFF) {
		del_tsk(&tskno_FrequencyCheckTask);
	}
	if (tskno_TimeUpTask != 0xFFFF) {
		del_tsk(&tskno_TimeUpTask);
	}
	Ringing = OFF;
	CI_Counter = 0;			/* 1994/10/25 */
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/11 */
#if 0 /* 警察FAX DVT_ID18&25&26 Modify by SMuratec 李 2005/11/14 */
@@	if (RingStatus & CI_STD_LINE) {
@@		SYS_CalledLineNumber &= ~SYS_STD_LINE_IN_CI;
@@	}
@@	else {
@@		SYS_CalledLineNumber &= ~SYS_EXT_LINE_IN_CI;
@@	}
#else
		SYS_CalledLineNumber &= ~SYS_STD_LINE_IN_CI;
#endif
#if 0 /* 2回線呼出監視仕様変更 Modified by SMuratec 李 2005/10/19 */
**	if (SYS_CalledLineNumber & SYS_TWICE_LINE_IN_CI) {
**		RingStatus &= (CI_STD_LINE | CI_EXT_LINE);
**	}
**	else {
**		RingStatus = RING_STATUS_INITIAL;
**	}
#else
	 /* ナンバーディスプレイ Modified by SMuratec 李 2005/10/20 */
	if (IsCiSndMsg = OK_CONT) {
		IsCiSndMsg = FALSE;
	}
	RingStatus = RING_STATUS_INITIAL;
#endif
	if ( !(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK)) ) {	/* 付属電話はフフックではない */
		NCU_HdstShift();
	}

	InitializeGrovalData();
#else /* defined (KEISATSU) */
	RingStatus = RING_STATUS_INITIAL;
#endif /* defined (KEISATSU) */

#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/11 */
	if (!(SYS_CalledLineNumber & SYS_TWICE_LINE_IN_CI)) {
		NCUStatus &= ~(DETECT_CI_STATE | DETECT_INTER_CI_STATE);
	}
#else /* !defined (KEISATSU) */
	NCUStatus &= ~(DETECT_CI_STATE | DETECT_INTER_CI_STATE);
#endif /* defined (KEISATSU) */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/16 */
	if (tskno_CarOffTimer != 0xFFFF) {
		del_tsk(&tskno_CarOffTimer);
	}
#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信検出タスクの強制終了ルーチン]
	function	:[
		1.見ての通りです
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(HS),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/21]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_DetectCalledExit(void)
{
	DetCallChildTaskExit();
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/11 */
#if 0 /* 2回線呼出監視仕様変更 Deleted by SMuratec 李 2005/10/19 */
**	if (tskno_Detect2ndCalledTask != 0xFFFF) {
**		del_tsk(&tskno_Detect2ndCalledTask);
**	}
#endif
#endif /* defined (KEISATSU) */
#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
	CR_Ringing = OFF;
#endif
	exi_tsk();
}


#if (PRO_NUMBER_DISPLAY == ENABLE)
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信前情報の CAR を検出してよいかどうか判断する]
	function	:[
	]
	return		:[TRUE/FALSE]
	common		:[
		SYB_SettingStatus[]
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/07/23]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE NCU_IsCarWaitedFor(void)
{

#if 0 /* Changed by H.Kubo 1998/11/25 */
	if (CHK_NumberDisplayON()) {
		return TRUE;
	}
#else
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
	if (DEBUG_NumberDisplay) {
		if (SYS_LineNDStatus == ND_USED_IN_STD) {
			if (CHK_NumberDisplayON() && (SYS_RingCounter == 0)) {
				if ( ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE)	/* 拡張回線には通信中 */
					|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) 	/* 拡張回線には本体使用中 */
					|| (CHK_KEIDENRxPriority() && ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)) ){ /* 警電優先受信ＯＮ及び警電受話中 */
					/* ここで動作しない */
				}
				else {
					return TRUE;
				}
			}
		}
		else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
			if (CHK_NumberDisplayON() && (SYS_RingCounterExt == 0)) {
				if ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE)	/* 拡張回線には通信中 */
					|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) 	/* 拡張回線には本体使用中 */
					){
					/* ここで動作しない */
				}
				else {
					return TRUE;
				}
			}
		}
	}
	else {
		/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
 		if ( !CHK_LineSetting()											/* 回線設定 == 拡張回線 */
 			|| CHK_KEIDENRxPriority() 									/* 警電優先受信ONの場合 */
			/* 警察FAX DVT_ID65 Added by SMuratec 李 2005/12/13 */
			|| (!SYS_LineNDStatus && CHK_NumberDisplayON() && (RingStatus & CI_STD_LINE) && (SYS_RingCounter == 0 ))
 			|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_CI_IN)		/* 拡張回線には呼出中 */
			|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)	/* 拡張回線には受話中 */
			|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT) /* 拡張回線には送話中 */
			|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE) 	/* 拡張回線には通信中 */
			|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) ) {	/* 拡張回線には本体使用中 */
			/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/12/06 */
			if (NCU_ND_Status & ND_WAIT_FOR_2ND_RING) {
				if (CHK_NumberDisplayON() && (SYS_RingCounter == 0)) {
					return TRUE;
				}
			}
		}
		else
		if (CHK_NumberDisplayON() && (SYS_RingCounter == 0)) {
			return TRUE;
		}
	}
#else /* !defined (KEISATSU) */
	if (CHK_NumberDisplayON() && (SYS_RingCounter == 0)) {
		return TRUE;
	}
#endif /* defined (KEISATSU) */
#endif
	return FALSE;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信前情報の CAR かどうかを判断する。]
	function	:[
			オン時間が CAR のパターンにあっているか
			オフ時間が CAR のパターンにあっているか
			オンオフ合わせた時間が CAR のパターンにあっているか
		以上の条件を満たしたリングパターンならば、CAR を見つけたとみなす。

	]
	return		:[TRUE/FALSE]
	common		:[
		NCU_ND_CarPattern
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/07/23]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE NCU_IsCarReceived(UWORD on_time, UWORD off_time)
{
	UBYTE i;
	UBYTE error_count;
	UBYTE error_status;
	if ((on_time > 2) && (off_time > 2)) { /* on_time と off_time がゴミでなければ */
		/* マーク、スペースのパターンを記憶。 */
		for (i = SYS_ND_CAR_HISTORY_START; i < SYS_ND_CAR_PATTERN_MAX; i++) {
			if (SYB_ND_CarPattern[i] == 0) {
				SYB_ND_CarPattern[i] = on_time; /* ON Time 記憶 */
				if (++i  >= SYS_ND_CAR_PATTERN_MAX) {
					i = SYS_ND_CAR_HISTORY_START;
				}
				SYB_ND_CarPattern[i] = off_time; /* OFF Time 記憶 */
				if (++i  >= SYS_ND_CAR_PATTERN_MAX) {
					i = SYS_ND_CAR_HISTORY_START;
				}
				SYB_ND_CarPattern[i] = 0; /* 次の書き込み位置を設定。 */
				break;
			}
		}
	}

	/* 既に CAR が検出されているときは、 CAR 検出をしません。 */
	if (NCU_ND_Status & ND_CAR_DETECTED) {
		return FALSE;
	}

 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/29 */
	if ( !CHK_LineSetting()											/* 回線設定 == 拡張回線 */
		/* 警察FAX DVT_ID65 Added by SMuratec 李 2005/12/13 */
		|| !FaxComCompleted
		/* 警察FAX DVT_ID65 Added by SMuratec 李 2005/12/13 */
		|| (!SYS_LineNDStatus && CHK_NumberDisplayON() && (RingStatus & CI_STD_LINE) && (SYS_RingCounter == 0 ))
		|| CHK_KEIDENRxPriority() 									/* 警電優先受信ONの場合 */
		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_CI_IN)		/* 拡張回線には呼出中 */
		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)	/* 拡張回線には受話中 */
		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT) /* 拡張回線には送話中 */
		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE) 	/* 拡張回線には通信中 */
		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) ) {	/* 拡張回線には本体使用中 */
		return FALSE;
	}
 #endif /* defined (KEISATSU) */

#if 0 /* 止めます。 by H.Kubo 1998/10/22 */
	/* NCU_TelephoneHookCheckTask が走っていないと、ここはうまく働きません。 */
	if ((SYB_SettingStatus[SETTING_STATUS_30] & ND_TEL2_ND_ON) 
	&& OffHook2()) {
		/* CAR 検出をする前に外付け電話が一次応答を返した。早急に V23 受信へ移る。 */
		if (!(SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_IGNORE_OH2_IN_CAR)) {
			return TRUE;
		}
	}
#endif

	/* 正統派の検出処理 */
	error_status = 0;
	if (on_time < SYB_ND_CarPattern[SYS_ND_CAR_MIN_ON_TIME]) {
		error_status |= SYS_ND_CAR_MIN_ON_BIT;
	}
	if (on_time > SYB_ND_CarPattern[SYS_ND_CAR_MAX_ON_TIME]) {
		error_status |= SYS_ND_CAR_MAX_ON_BIT;
	}
	if (off_time < SYB_ND_CarPattern[SYS_ND_CAR_MIN_OFF_TIME]) {
		error_status |= SYS_ND_CAR_MIN_OFF_BIT;
	}
	if (off_time > SYB_ND_CarPattern[SYS_ND_CAR_MAX_OFF_TIME]) {
		error_status |= SYS_ND_CAR_MAX_OFF_BIT;
	}
	if (on_time + off_time < SYB_ND_CarPattern[SYS_ND_CAR_MIN_ON_OFF_TIME]) {
		error_status |= SYS_ND_CAR_MIN_ON_OFF_BIT;
	}
	if (on_time + off_time > SYB_ND_CarPattern[SYS_ND_CAR_MAX_ON_OFF_TIME]) {
		error_status |= SYS_ND_CAR_MAX_ON_OFF_BIT;
	}
	SYB_ND_CarPattern[SYS_ND_CAR_DETECTION_REPORT] = i;  /* CAR の検査結果を記録 */
	/* CAR パターンの学習。学習係数は 0.1 で決めうちです。by H.Kubo 1998/10/16 */
	if (SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_CAR_PATTERN_TRAIN) {
		NCU_ND_AdaptToReceivedCAR(on_time , off_time);
	}
	error_count = 0;
	for (i = 0; i < 8; i++) { /* 1 の個数を数え上げる */
		if (error_status & ((UBYTE) (1 << i))) {
			error_count++;
		}
	}
	if (error_count <=  SYB_ND_CarPattern[SYS_ND_CAR_ACCEPTABLE_ERROR]) {
		return TRUE;
	}

	/* CAR パターンの学習。学習係数は 0.1 で決めうちです。by H.Kubo 1998/10/16 */
	if (SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_CAR_PATTERN_TRAIN) {
		NCU_ND_AdaptToReceivedCAR(on_time , off_time);
	}
	/* Quick & Dirty な検出処理。間違いもしやすい */
	if (SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_CAR_DETECT_QUICKLY) {
		if (on_time > SYB_ND_CarPattern[SYS_ND_CAR_MIN_ON_TIME]) {
			return (TRUE);
		}
	}
	return (FALSE);

}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信前情報の CAR のパターンを学習する]
	function	:[

	]
	return		:[]
	common		:[
		SYB_ND_CarPattern[]
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/16]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void NCU_ND_AdaptToReceivedCAR(UWORD on_time, UWORD off_time)
{
	UWORD new_value;

	/* 最小 ON 時間 */
	new_value = (on_time * 8) / 10; /* 着信した on_time の 80% */
	new_value += 9 * SYB_ND_CarPattern[SYS_ND_CAR_MIN_ON_TIME];
	new_value /= 10;
	SYB_ND_CarPattern[SYS_ND_CAR_MIN_ON_TIME] = new_value;

	/* 最大 ON 時間 */
	new_value = (on_time * 12) / 10; /* 着信した on_time の 120% */
	new_value += 9 * SYB_ND_CarPattern[SYS_ND_CAR_MAX_ON_TIME];
	new_value /= 10;
	SYB_ND_CarPattern[SYS_ND_CAR_MAX_ON_TIME] = new_value;

	/* 最小 OFF 時間 */
	new_value = (off_time * 8) / 10; /* 着信した off_time の 80% */
	new_value += 9 * SYB_ND_CarPattern[SYS_ND_CAR_MIN_OFF_TIME];
	new_value /= 10;
	SYB_ND_CarPattern[SYS_ND_CAR_MIN_OFF_TIME] = new_value;

	/* 最大 OFF 時間 */
	new_value = (off_time * 12) / 10; /* 着信した off_time の 120% */
	new_value += 9 * SYB_ND_CarPattern[SYS_ND_CAR_MAX_OFF_TIME];
	new_value /= 10;
	SYB_ND_CarPattern[SYS_ND_CAR_MAX_OFF_TIME] = new_value;

	/* 最小 ON 時間 */
	new_value = ((on_time + off_time) * 8) / 10; /* 着信した on_time + off_time の 80% */
	new_value +=  9 * SYB_ND_CarPattern[SYS_ND_CAR_MIN_ON_OFF_TIME];
	new_value /= 10;
	SYB_ND_CarPattern[SYS_ND_CAR_MIN_ON_OFF_TIME] = new_value;

	/* 最大 ON 時間 */
	new_value = ((on_time + off_time) * 12) / 10; /* 着信した on_time + off_time の 120% */
	new_value += 9 * SYB_ND_CarPattern[SYS_ND_CAR_MAX_ON_OFF_TIME];
	new_value /= 10;
	SYB_ND_CarPattern[SYS_ND_CAR_MAX_ON_OFF_TIME] = new_value;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[DetectRingTone のサブルーチン。 CAR 検出用]
	function	:[

	]
	return		:[
		DETECT_CAR
		DETECT_IR_STOP
		FALSE
	]
	common		:[
		NCU_ND_CarPattern
		SYB_ND_CarPattern[]
	]
	condition	:[
			SamplingBuff に、最新の ON 期間が格納されていること。
			OFF 期間状態であること。
	]
	comment		:[
		 DetectRingTone の中での CAR 検出は、二重になった while ループの内側で行うのが基本です。
		なぜなら、 内側のループを抜けるには、 CI_CYCLE_TIMEUP になることが条件ですが、理想的な
		CAR 信号に対しては、その条件が成立しないからです。
		 ところが、 CAR のスペース期間が 60ms より長く見えると、CI_CYCLE_TIMEUP の条件が成立し、
		内側のループは抜けてしまいます。
		 このサブルーチンは、そのような場合に、内側のループから抜けた直後に CAR を検出する処理をします。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/12]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE NCU_CheckCarAfterCiCycleTimeup(UWORD ci_end_time, UWORD *ci_start_time, UBYTE *counter)
{
	struct Timer10msEventData_t car_timer;
	UDWORD	timer;
	UBYTE rtn = FALSE;
	

#if 0 /* NCU_IsCarWaitedFor() の仕様が変わったので、変更します。Changed by H.Kubo 1998/12/05 */
@@	if (NCU_IsCarWaitedFor()) {
#else
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
	/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
#if 0 /* 警察FAX (ナンバーディスプレイ) Deleted by SMuratec 李 2005/12/07 */
@@	if ( !CHK_LineSetting()											/* 回線設定 == 拡張回線 */
@@		|| CHK_KEIDENRxPriority() 									/* 警電優先受信ONの場合 */
@@		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_CI_IN)		/* 拡張回線には呼出中 */
@@		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)	/* 拡張回線には受話中 */
@@		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT) /* 拡張回線には送話中 */
@@		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE) 	/* 拡張回線には通信中 */
@@		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) ) {	/* 拡張回線には本体使用中 */
@@	}
@@	else
#endif
	if (NCU_ND_Status && (!DEBUG_NumberDisplay || SYS_LineNDStatus == ND_USED_IN_STD)) {
#else /* !defined (KEISATSU) */
	if (NCU_ND_Status) {
#endif /* defined (KEISATSU) */
#endif
		timer = SYB_ND_CarPattern[SYS_ND_IR_STOP_DETECTION_TIMER] * 10;

		if (*counter > 1) { /* 2 回以上記録している => OffTime のデータが残っている。 */
			if (NCU_IsCarReceived(SamplingBuff[*counter - 1], SamplingBuff[*counter - 2])) {
				rtn = DETECT_CAR;
			}
		}
#if 0 /* DetectRingTone の中の SYS_RingCounter での着信検出判断の後呼ばれるようにしたので、なくてもすばやく着信できるはず。Deleted by H.Kubo 1998/11/17 */
		else if ((SYS_RingCounter > 0) && (NCU_ND_Status & ND_COUNTING_2ND_RING)) { /* added by H.Kubo 1998/11/16 */
			rtn = FALSE;	/* 呼出し音待ちで既に IR が一波以上検出されている時は、すぐに抜けます。 */
		}
#endif
		else {
			RingStatus &= ~CI_ON;
			car_timer.Time = SYB_ND_CarPattern[SYS_ND_CAR_MAX_OFF_TIME];  /* */
			car_timer.Event = EVT_CI_CHECK;
			cre_tsk( &tskno_CarOffTimer, TSK_CMN_WATCHTIMER10MSEVENTTASK, &car_timer); /* 最大許容 OFF 期間を過ぎたら、イベントをなげます。 */
			CMN_DisableInterrupt();
			if (!(RingStatus & CI_ON)) {
				wai_evt(EVT_CI_CHECK);		/** CI､又はタイムアップのイベント待ち */
			}
			CMN_EnableInterrupt();


			if (RingStatus & CI_ON) { /* 最大許容 OFF 期間内に CI が検出された */
				*ci_start_time = SYS_GeneralTimer;
				RingingOffTime = (UWORD) (*ci_start_time - ci_end_time);
				/* 既に OnTime は記録されているはずだから、ここで試してみる。 */
				if (NCU_IsCarReceived(SamplingBuff[*counter - 1], RingingOffTime)) {
					rtn = DETECT_CAR;
				}
				StoreRingingOffTime(counter);
			}
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/09/08 */
			else if (RingStatus & CI_DETECT_TIMEUP) {		/** リングトーン検出時間のタイムアップ */
				rtn = FALSE;
			}
#endif /* defined (KEISATSU) */
			else if ( (NCU_ND_Status & (ND_CAR_DETECTED | ND_COUNTING_2ND_RING)) && (timer > 0)) { /* ND_CAR_DETECTED を付け加える。 1998/10/22 */
				CMN_DisableInterrupt();
				if ( timer > (UWORD) (SYS_GeneralTimer - ci_end_time) ) {
				/* 呼出音が止まったことを仮検出します。 1998/10/20 */
					car_timer.Time = (UWORD) (timer - ((UWORD) (SYS_GeneralTimer- ci_end_time)));  /* 最初は５秒のタイマー*/
					CMN_EnableInterrupt();
					car_timer.Event = EVT_CI_CHECK;
					if (tskno_CarOffTimer != 0xffff) {
						del_tsk( &tskno_CarOffTimer);
					}
					cre_tsk( &tskno_CarOffTimer, TSK_CMN_WATCHTIMER10MSEVENTTASK, &car_timer); /* 最大許容 OFF 期間を過ぎたら、イベントをなげます。	 */
					CMN_DisableInterrupt();
					if (!(RingStatus & CI_ON)) {
						wai_evt(EVT_CI_CHECK);		/** CI､又はタイムアップのイベント待ち */
					}
					CMN_EnableInterrupt();
					if (RingStatus & CI_ON) { /* 最大許容 OFF 期間内に CI が検出された */
						*ci_start_time = SYS_GeneralTimer;
						RingingOffTime = (UWORD) (*ci_start_time - ci_end_time);
						StoreRingingOffTime(counter);
						/* 既に OnTime は記録されているはずだから、ここで試してみる。 */
						if (NCU_IsCarReceived(SamplingBuff[*counter - 1], RingingOffTime)) {
							rtn = DETECT_CAR;
						}
					}
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/12/08 */
					else if (RingStatus & CI_DETECT_TIMEUP) {		/** リングトーン検出時間のタイムアップ */
						rtn = FALSE;
					}
					else if (OhPortStatus & TEL1_OFF_HOOK) {
						wai_tsk( 40 );
						if (NCU_LineStatus & STD_HDST_OFFHOOK) {
							RingStatus |= CI_DETECT_TIMEUP;
							rtn = FALSE;
						}
						else {
							rtn = DETECT_IR_STOP; /* CAR 停止検出も兼用。 1998/10/22 */
						}
					}
#endif /* defined (KEISATSU) */
					else {
						rtn = DETECT_IR_STOP; /* CAR 停止検出も兼用。 1998/10/22 */
					}
				}
				else {
					rtn = DETECT_IR_STOP;
				}
				CMN_EnableInterrupt();
			}

			if (tskno_CarOffTimer != 0xffff) {
				del_tsk( &tskno_CarOffTimer);
			}
		}
	}
	return rtn;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[着信前情報の CAR のパターンを初期化する]
	function	:[

	]
	return		:[]
	common		:[
		NCU_ND_CarPattern
		SYB_ND_CarPattern[]
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/12]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void NCU_ND_InitializeCarPattern(void)
{
	UBYTE i;
	SYB_ND_CarPattern[SYS_ND_CAR_MIN_ON_TIME] = NCU_ND_CarPattern.MinOnTime;
	SYB_ND_CarPattern[SYS_ND_CAR_MAX_ON_TIME] = NCU_ND_CarPattern.MaxOnTime;
	SYB_ND_CarPattern[SYS_ND_CAR_MIN_OFF_TIME] = NCU_ND_CarPattern.MinOffTime;
	SYB_ND_CarPattern[SYS_ND_CAR_MAX_OFF_TIME] = NCU_ND_CarPattern.MaxOffTime;
	SYB_ND_CarPattern[SYS_ND_CAR_MIN_ON_OFF_TIME] = NCU_ND_CarPattern.MinOnOffTime;
	SYB_ND_CarPattern[SYS_ND_CAR_MAX_ON_OFF_TIME] = NCU_ND_CarPattern.MaxOnOffTime;
	SYB_ND_CarPattern[SYS_ND_CAR_COUNTER_THRESHOLD] = NCU_ND_CarCounterThreshold;

	SYB_ND_CarPattern[SYS_ND_CAR_MODE] = 0;
	SYB_ND_CarPattern[SYS_ND_CAR_MODE] &= (~SYS_ND_CAR_DETECT_STRICT & ~SYS_ND_CAR_PATTERN_TRAIN);

	SYB_ND_CarPattern[SYS_ND_CAR_IR_MARK_THRESHOLD] = 0;	/* CAR と IR を区別するマークの時間長の閾値 */

	SYB_ND_CarPattern[SYS_ND_CAR_ACCEPTABLE_ERROR] = 0;	/* 厳しい CAR 検出アルゴリズムで受理できるエラー数 */

	SYB_ND_CarPattern[SYS_ND_CAR_DETECTION_REPORT] = 0;
	SYB_ND_CarPattern[SYS_ND_CAR_COUNT_REPORT] = 0;
	SYB_ND_CarPattern[SYS_ND_LAST_NCU_ND_STATUS] = 0;
	SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = 0;
	SYB_ND_CarPattern[SYS_ND_IR_STOP_DETECTION_TIMER] = ND_IR_STOP_DETECTION_TIMER / 10;
	SYB_ND_CarPattern[SYS_ND_CI_COUNTER_THRESHOLD] = 2; 	/* 1998/10/22 */
	/* SYB_ND_CarPattern[SYS_ND_OH_TO_V23_RX_TIMER] = 9; */ /* 1st response to V23 signal wait. 90ms */
	SYB_ND_CarPattern[SYS_ND_OH_TO_V23_RX_TIMER] = 3; /* 1st response to V23 signal wait. 30ms changed by H.Kubo 1998/11/21 */
	SYB_ND_CarPattern[SYS_ND_CAR_TIMEUP_TIMER] = 600; /* 1st response to V23 signal wait. 6 s */
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/20 */
	SYB_ND_CarPattern[SYS_ND_MODEM_DIALIN_MODE] = 0;
	SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] = SYS_ND_COUNT_HEARABLE_IR;
#else /* !defined (KEISATSU) */
	SYB_ND_CarPattern[SYS_ND_MODEM_DIALIN_MODE] = SYS_ND_SWITCH_TO_NORMAL_DIALIN; /* 0 => SYS_ND_SWITCH_TO_NORMAL_DIALIN by H.Kubo 1999/01/05 */

#if (0)	/* V.23信号受信後の1発目のＣＩが鳴動しない件(D86-066) By O.Kimoto 2002/11/18 */
** 	SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] = (SYS_ND_SILENT_WHILE_IR_DETECT | SYS_ND_COUNT_HEARABLE_IR | SYS_ND_FNET_CALL_MEMORIZE); /* added by H.Kubo 1998/11/28 */
#else
	SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] = (SYS_ND_COUNT_HEARABLE_IR | SYS_ND_FNET_CALL_MEMORIZE);
#endif
#endif /* defined (KEISATSU) */
	for (i = SYS_ND_CAR_HISTORY_START; i < SYS_ND_CAR_PATTERN_MAX; i++) {
		SYB_ND_CarPattern[i] = 0;
	}
}
#endif
/*************************************************************************
	module		:[CIの最小ON期間を獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1999/12/06]
	author		:[K.Okada]
*************************************************************************/
UWORD NCU_CI_MinOnTime(void)
{
	UWORD comp_min_on_time;

	if (CHK_AddToMinOnTime()) { /* CI最小ON期間に対して値を加える MEMSW G:5-3 */
		comp_min_on_time = CTRY_RingTable()->MinOnTime + (UWORD)(CHK_ValueAddedToMinOnTime());
	}
	else {	/* CI最小ON期間に対して値を減じる */
		if ((CTRY_RingTable()->MinOnTime) > (UWORD)(CHK_ValueAddedToMinOnTime())) {/* MEMSW G:5-4～7 */
			comp_min_on_time = CTRY_RingTable()->MinOnTime - (UWORD)(CHK_ValueAddedToMinOnTime());
		}
		else {  
			comp_min_on_time = (UWORD)0; /* 指定値がデフォルト値をこえる場合０とする */
		}
	}
	return (comp_min_on_time);
}
