/**********************************************************************
* ANZU
*
*	 File	Name:  NCU_TAD.C
*	 Coded	  by:  坂本直史
*	 Module Name:  NCU_DetectNoiseTask()
*				   NCU_DetectSilentTask()
*				   SilentChildTaskExit()
*				   NCU_DetectSilentExit()
*				   NCU_FaxTadAutoSwitchTask()
*				   FaxTadChildTaskExit()
*				   NCU_FaxTadDetectCNGExit()
*
*	 Note		:  外付留守番電話着信後処理
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
#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\memsw\define\mems_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\define\ncu_pro.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\define\ncu_msg.h"
#include	"\src\atlanta\define\ncu_ret.h"
#include	"\src\atlanta\define\ncu_cnst.h"
#include	"\src\atlanta\define\ncu_def.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\ncu_data.h"
#include	"\src\atlanta\ext_v\ncu_tbl.h"

#if (PRO_MODEM == ORANGE3) /* added by H.Kubo 1997/07/23 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/07/23 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"

#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"

#if (PRO_NCU_TYPE == ANZU_GBR_TYPE)
 #if defined(HINOKI) || defined(HINOKI2) || defined (HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)  /* HINOKI2 2001/11/13 T.Takagi */

 #endif
#endif

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2)		/* ANS待機での55転送 移植 by SMuratec 李 2004/08/27 */
#include	"\src\atlanta\define\status.h"
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

#if defined(HINOKI3)	/* QAT不具合対策 by Y.Kano 2005/01/28 */
#include	"\src\atlanta\define\mntsw_h.h"
#endif

static UWORD tskno_WatchTimerSilentTask	 = 0;
static UWORD tskno_DetectNoiseTask		 = 0;
static UWORD tskno_FilterOnOffTask		 = 0;
static UWORD tskno_DetectSilentTask		 = 0;
static UWORD tskno_WatchTimerFaxTadTask	 = 0;
static UWORD tskno_ToneDetectPattern1Task = 0;
static UWORD tskno_receive_dtmfTask		  = 0;	/* add 1997/11/13  By T.Yamaguchi */

#if (PRO_MODEM == ORANGE3)
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ノイズ検出タスク]
	function	:[
		1.50ms毎にフィルターをチェックする
		2.ノイズ検出したらメッセージ通知する
	]
	return		:[なし]
	common		:[
		UBYTE MDM_LevelWriteRAM:ゼロクロス値
	]
	condition	:[ゼロクロス値は50ms毎に更新されます]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	NCU_DetectNoiseTask(struct NoiseData_t *noise_data)
{
	while (1) {
		wai_tsk(5);
		if (MDM_LevelWriteRAM <= CHK_TAD_DetectLevel()){
			break;
		}
	}
	TxDetectNoiseTaskMsg.Message = noise_data->ReturnValue;
	snd_msg(noise_data->SendMBX, &TxDetectNoiseTaskMsg);
	wai_tsk(0xFFFF);
}
#endif

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/09/08 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[無音検出タスク]
	function	:[
		1.ノイズ検出用フィルタータスクとタイマタスクを起動
		2.ノイズ検出なら各タスクを再起動、タイムアップなら無音検出を通知する
	]
	return		:[なし]
	common		:[
		UWORD			CHK_TAD_SilentTime()	:無音検出時間
		UBYTE	NoiseLimit			:無視するノイズの個数(テーブル)
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	NCU_DetectSilentTask(UWORD *mbx_no)
{
	MESSAGE_t *rx_message;
	UWORD noise_counter = 0;
	struct Timer10msData_t timer_data;
	struct NoiseData_t  filter_data;

	/** タイマタスクの起動 */
	if (!CHK_TAD_SilentTime()) {
		timer_data.Time	   = 1;
	}
	else {
		timer_data.Time	   = (UWORD)(CHK_TAD_SilentTime()*100);	/** 無音検出時間(10sec) */
	}
	timer_data.SendMBX	   = mbxno.NCU_DetectSilentTask;
	timer_data.ReturnValue = TIME_UP;
	cre_tsk(&tskno_WatchTimerSilentTask, TSK_CMN_MAN_TIMER10MSTASK, &timer_data);

	/** フィルタータスク／ノイズタスクの戻り値データのセット */
	filter_data.ReturnValue = DET_NOISE;
	filter_data.SendMBX		= mbxno.NCU_DetectSilentTask;

	while (1) {			/** タイムアップを検出するまでループ */
		cre_tsk(&tskno_DetectNoiseTask, TSK_NCU_DETECTNOISETASK, &filter_data);
		rcv_msg(mbxno.NCU_DetectSilentTask, &rx_message);

		switch (rx_message->Message) {
							/*------------------------------------------------*/
		case DET_NOISE:		/**	 ノイズ検出(1) (300～1625Hz間/1625～2125Hz間) */
							/*------------------------------------------------*/
			SilentChildTaskExit();			/** フィルター1タスク,フィルター2タスクの強制終了 */
			noise_counter++;
			/*------------------------------------------------------------*/
			/** ノイズカウンタがテーブル値を越えた時､タイマを再起動します */
			/*------------------------------------------------------------*/
			if (noise_counter > NoiseLimit) {
				del_tsk(&tskno_WatchTimerSilentTask);
				cre_tsk(&tskno_WatchTimerSilentTask, TSK_CMN_MAN_TIMER10MSTASK, &timer_data);
				noise_counter = 0;
			}
			break;
							/*------------------------------*/
		case TIME_UP:		/** 無音検出時間タイムアップ(0) */
							/*------------------------------*/
			TxDetectSilentTaskMsg.Message = DETECT_SILENT;
			snd_msg(*mbx_no, &TxDetectSilentTaskMsg);
			wai_tsk(0xFFFF);
			break;

		default:
			break;
		}
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[無音検出タスクの子タスク強制終了ルーチン]
	function	:[
		1.子タスクを強制終了する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void 	SilentChildTaskExit(void)
{
	if (tskno_DetectNoiseTask != 0xFFFF) {
		del_tsk(&tskno_DetectNoiseTask);
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[無音検出タスク強制終了処理ルーチン]
	function	:[
		1.子タスクを強制終了後、自タスクを終了する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_DetectSilentExit(void)
{
	SilentChildTaskExit();
	if (tskno_WatchTimerSilentTask != 0xFFFF) {
		del_tsk(&tskno_WatchTimerSilentTask);
	}
	exi_tsk();
}
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* Ported from Clover by H.Kubo 1997/09/08 */

static UWORD tskno_DetectFilter1Task	  = 0;
static UWORD tskno_DetectFilter2Task	  = 0;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[無音検出タスク]
	function	:[
		1.ノイズ検出用フィルタータスクとタイマタスクを起動
		2.ノイズ検出なら各タスクを再起動、タイムアップなら無音検出を通知する
	]
	return		:[なし]
	common		:[
		UWORD CHK_TAD_SilentTime()	:無音検出時間
		unsigned char NoiseLimit			:無視するノイズの個数(テーブル)
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1994/01/26]
	author		:[平岡徹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void far NCU_DetectSilentTask(UWORD *mbx_no)
{
	UWORD	timer;
	UWORD	cnt;
	UWORD	comp_time;
#if defined(POPLAR_F)
	UBYTE	*point;	/* for debug */
	UWORD	i;	/* for debug */
#endif

#if defined(POPLAR_F)	/* for debug */
	point = (UBYTE *)&EcmBuffer[0][0];
	for (i = 0; i < 0xFFFE; i++) {
		*point = 0xFF;
		point++;
	}
	point = (UBYTE *)&EcmBuffer[0][0];
	i = 0;
#endif

	/*
	** このタスクは実際使用されていませんが、タスク終了ルーチンでdel_tskされるので
	** 初期化しないといけません、抜けてた！
	*/
	tskno_DetectFilter1Task = 0xFFFF;
	tskno_DetectFilter2Task = 0xFFFF;
	
#if 0 /* by H.Kubo 1998/02/03 */
	if (CHK_V34_AnsFaxCNGPriorty()) {
		/* ソフトでＣＮＧと無音を検出するためのセットアップ */
		MDM_SetUpAnsFaxSilent(0);
	}
	else {
		/* ソフトで無音のみ検出し、ハードでＣＮＧを検出するためのセットアップ */
		MDM_SetUpAnsFaxSilent(1);
	}
#else
	/* 本体内蔵モデムでは、ソフトで CNG を検出します。オプションボードで
	** ハードで  CNG 検出する場合、設定が食い違うことになるので、ここでは
	** 常にソフトで CNG を検出するようにします。
	*/
	/* ソフトで無音のみ検出し、ハードでＣＮＧを検出するためのセットアップ */
 #if (PRO_NCU_TYPE == ANZU_GBR_TYPE)
  #if defined(HINOKI) || defined(HINOKI2) || defined (HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)  /* HINOKI2 2001/11/13 T.Takagi */
  /*
  ** HINOKI TWN のTONE側の入力が小さいため、無音検出優先にすると、留守番電話録音中に
  ** 着信してしまうことがあります。
  ** 受信レベルゲインを下げるのを止めます。by H.Hirao 1999/05/26
  */
	MDM_SetUpAnsFaxSilent(0);
  #endif
 #endif
 #if defined(POPLAR_F) || (defined(POPLAR_H) && defined(JP0))/*V851 無音検出調整 By Y.Suzuki 2002/08/28*/
	MDM_SetUpAnsFaxSilent(0);
 #else
  /*
  ** HINOKI3 で、無音検出をあまくすると、留守番電話録音中に雑音でも
  ** 無音検出して着信してしまうＱＡＴでの不具合があった。（サンヨーの留守番電話（ＴＥＬ－Ｌ７０））で発生。
  ** 対策として、無音検出を厳しくするように設定します。設定値は保守用SWで持ち、初期値を０とします。by Y.Kano 2005/01/28
  */
  #if defined(HINOKI3)
	MDM_SetUpAnsFaxSilent((UBYTE)((SYB_MaintenanceSwitch[MNT_SW_H5] & ANS_FAX_SILENT_SW) >> 4));
  #else
	MDM_SetUpAnsFaxSilent(1);
  #endif
 #endif
#endif
	/* 無音検出時間獲得 */
	comp_time = (UWORD)((UWORD)CHK_TAD_SilentTime() * 100);
	cnt = 0;
	timer = SYS_GeneralTimer;

	while (1) {
		wai_tsk(1);

		if ((UWORD)(SYS_GeneralTimer - timer) > comp_time) {	/* 無音検出時間経過 *//*cast by M.Kotani 97/10/08*/
			break;
		}
		if (MDM_GetAnsFaxSilentLevel()) {	/* 無音でない */

#if defined(POPLAR_F)	/* for debug */
			if (i < 0xFFFE) {
				*point = 1;
				point++;
				i++;
			}
#endif
			cnt++;
			if (cnt > 5) {	/* 50ms */
				timer = SYS_GeneralTimer;
				cnt = 0;
			}
		}
		else {	/* 無音だ */

#if defined(POPLAR_F)	/* for debug */
			if (i < 0xFFFE) {
				*point = 0;
				point++;
				i++;
			}
#endif
			cnt = 0;
		}
	}
	TxDetectSilentTaskMsg.Message = DETECT_SILENT;
	snd_msg(*mbx_no, &TxDetectSilentTaskMsg);
	wai_tsk(0xFFFF);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[無音検出タスクの子タスク強制終了ルーチン]
	function	:[
		1.子タスクを強制終了する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1994/01/26]
	author		:[平岡徹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_MODEM == MN195006)
void  SilentChildTaskExit(void)
#else
void near SilentChildTaskExit(void)
#endif
{
	if (tskno_DetectFilter1Task != 0xFFFF) {
		del_tsk(&tskno_DetectFilter1Task);
	}
	if (tskno_DetectFilter2Task != 0xFFFF) {
		del_tsk(&tskno_DetectFilter2Task);
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[無音検出タスク強制終了処理ルーチン]
	function	:[
		1.子タスクを強制終了後、自タスクを終了する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1994/01/26]
	author		:[平岡徹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void far NCU_DetectSilentExit(void)
{
	SilentChildTaskExit();
	if (tskno_WatchTimerSilentTask != 0xFFFF) {
		del_tsk(&tskno_WatchTimerSilentTask);
	}
	exi_tsk();
}
#endif /* (PRO_MODEM == R288F) */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[外付留守番電話着信後処理タスク]
	function	:[
		1.メモリスイッチの設定状況により、CNG検出／無音検出／タイマタスクを起動する
		2.CNG／無音／タイムアップを検出すれば、親タスクに通知する
	]
	return		:[なし]
	common		:[
		UBYTE CHK_TAD_CNG_DetectAvailable()		: CNG検出有効/無効設定
		UBYTE CHK_UNI_SilentDetectAvailable()	: 無音検出有効/無効設定
		UWORD  CHK_CNG_DetectPeriod()					: CNGのみ検出期間
		UWORD  CHK_CNG_SilentDetectPeriod()				: CNG/無音検出期間
		UWORD  CHK_TAD_SilentPeriod()					: 無音のみ検出期間
		UBYTE FaxTadDetectCNGFlag
	]
	condition	:[]
	comment		:['94,11,17 V53 CNGと無音検出両方を検出する際の方法を変更]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_FaxTadAutoSwitchTask(WORD *tx_mail_box_no)
{
	MESSAGE_t *RxFaxTadAutoSwitchTaskMsg;


	UBYTE	end_flag = ON;
	struct Timer10msData_t		 timer_data;
	struct ToneDetectMailBoxData_t tone_data;
	UBYTE	detect_type;

	detect_type = CNG_DETECT;
	tskno_FilterOnOffTask = 0xffff;

	TxFaxTadAutoSwitchTaskMsg.Item = FROM__NCU_TAD;

	tskno_WatchTimerFaxTadTask	 = 0xFFFF;
	tskno_ToneDetectPattern1Task = 0xFFFF;
	tskno_DetectSilentTask		 = 0xFFFF;
	tskno_WatchTimerSilentTask	 = 0xFFFF;
	tskno_DetectNoiseTask		 = 0xFFFF;
	tskno_receive_dtmfTask		 = 0xFFFF;	/* add 1997/11/13  By T.Yamaguchi */

	if (!CHK_TAD_CNG_DetectAvailable()
	 && (!CHK_UNI_AnsFaxDTMFDetect())	/* 1997/11/13  By T.Yamaguchi */
	 && !CHK_UNI_SilentDetectAvailable()) {			/** CNG・無音検出が無効設定なら '96,04,15 UNI By N.S.*/
		wai_tsk(0xFFFF);
	}
	if( NCUStatus & HOLD_STATE ){	/* 保留中なら、検出しない 1998/04/03  By T.Yamaguchi */
		wai_tsk(0xFFFF);
	}

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/12/19 */
 #if (PRO_NCU_TYPE == ANZU_GBR_TYPE)
  #if defined(HINOKI) || defined(HINOKI2) || defined (HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)  /* HINOKI2 2001/11/13 T.Takagi */
  /*
  ** HINOKI TWNにおいて、ANS/FAX待機で、留守番電話に録音中に着信してしまう。
  ** HINOKI TWNのNCUには、RXAからしかモデムに対する入力がなくCMLを引いていない
  ** 状態では、信号を検出できない よって、ハードリワークを行い、この時だけ、
  ** AFEをTONEに設定します。 by H.Hirao 1999/05/25
  */
	AnalogSwitchTONE_Set2();
  #endif
 #endif
	AnalogSwitchTONE_Set();
#endif /* (PRO_MODEM == R288F) */
	MDM_FilterSetCNG();

	/** タイマタスクの起動 */
	if (!CHK_CNG_DetectPeriod()) {
		timer_data.Time	   = 1;
	}
	else {
		timer_data.Time	   = (UWORD)(CHK_CNG_DetectPeriod()*1000);	/** CNGのみ検出期間(10sec) */
	}
	timer_data.ReturnValue = CNG_TIME_UP;
	timer_data.SendMBX	   = mbxno.NCU_FaxTadAutoSwitchTask;
	cre_tsk(&tskno_WatchTimerFaxTadTask, TSK_CMN_MAN_TIMER10MSTASK, &timer_data);

	/** CNG検出が有効設定なら、CNG検出タスクを起動 */
	if (CHK_TAD_CNG_DetectAvailable()) {
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1007/09/05 */
		/* '95,12,27 By N.S. ANZU CNG検出方法変更 ここから*/
		if (tskno_FilterOnOffTask == 0xFFFF) {
			detect_type = ANS_FAX_CNG_DETECT;
			cre_tsk(&tskno_FilterOnOffTask, TSK_ATD_FILTERONOFFDETECTTASK, &detect_type);
		}
#endif /* (PRO_MODEM == ORANGE3) */
		if (tskno_ToneDetectPattern1Task == 0xFFFF) {
			tone_data.ToneType = CNG_TONE1;
			tone_data.SendMBX  = mbxno.NCU_FaxTadAutoSwitchTask;
			cre_tsk(&tskno_ToneDetectPattern1Task, TSK_ATD_TONEDETECTPATTERN1TASK, &tone_data);
		}
	/* '95,12,27 By N.S. ANZU CNG検出方法変更 ここまで*/
	}

	/* DTMF検出設定ならＤＴＭＦ検出タスクを起動 1997/11/13  By T.Yamaguchi */
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2)		/* ANS待機での55転送 移植 by SMuratec 李 2004/08/27 */
	if (!((NCU_RemoteTransferDial() && CHK_TAD_FaxReadyOnhookTransfer())			/* 55転送条件 */
	 && (CHK_DialType()==LINE_TYPE_TONE || CHK_RemoteTransferForcedDTMF()))) {	/* DTMF検出条件 */
		if ( CHK_UNI_AnsFaxDTMFDetect()) {
			tskno_receive_dtmfTask 			 = 0xFFFF;
			/*---------------------------*/
			/** ＤＴＭＦ検出タスク生成   */
			/*---------------------------*/
			cre_tsk(&tskno_receive_dtmfTask, TSK_NCU_DETECTREMOTEDTMFTASK, 0);
		}
	}
#else
	if ( CHK_UNI_AnsFaxDTMFDetect()) {
		tskno_receive_dtmfTask 			 = 0xFFFF;
		/*---------------------------*/
		/** ＤＴＭＦ検出タスク生成   */
		/*---------------------------*/
		cre_tsk(&tskno_receive_dtmfTask, TSK_NCU_DETECTREMOTEDTMFTASK, 0);
	}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

	while (end_flag) {		/** CNG検出、無音検出、タイムアップ検出するまでループする */
		rcv_msg(mbxno.NCU_FaxTadAutoSwitchTask, &RxFaxTadAutoSwitchTaskMsg);

		switch (RxFaxTadAutoSwitchTaskMsg->Message) {

		case CNG_TONE:				/** CNG検出(7) */
		case CNG_TONE1:				/** CNG検出(8)			'95,12,27 By N.S. ANZU CNG検出方法変更 */
		case DETECT_SILENT:			/** 無音検出(41) */
			/** 起動中タスクの強制終了 */
			FaxTadChildTaskExit();

			/** CNG/無音検出でループを抜ける */
			TxFaxTadAutoSwitchTaskMsg.Message = DETECT_TAD_CNG_OR_SILENT;
			end_flag = OFF;
			break;

		case CNG_TIME_UP:			/** CNGのみ検出期間タイムアップ(3) */
			/** タイマタスクを強制終了 */
			del_tsk(&tskno_WatchTimerFaxTadTask);

			/** タイマタスクの更新 (CNG→CNG/無音) */
			if (!CHK_CNG_SilentDetectPeriod()) {
				timer_data.Time	   = 1;
			}
			else {
				timer_data.Time	   = (UWORD)(CHK_CNG_SilentDetectPeriod()*1000);	/** CNG/無音検出期間(30sec) */
			}
			timer_data.ReturnValue = CNG_SILENT_TIME_UP;
			cre_tsk(&tskno_WatchTimerFaxTadTask, TSK_CMN_MAN_TIMER10MSTASK, &timer_data);
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1007/09/05 */
		/* '95,12,27 By N.S. ANZU CNG検出方法変更 ここから*/
			if (tskno_FilterOnOffTask != 0xFFFF) {
				del_tsk(&tskno_FilterOnOffTask);
			}
#endif /* (PRO_MODEM == ORANGE3) */
			if (tskno_ToneDetectPattern1Task != 0xFFFF) {
				del_tsk(&tskno_ToneDetectPattern1Task);
			}
		/* '95,12,27 By N.S. ANZU CNG検出方法変更 ここまで*/

			/* 保留中なら、検出しに行くと、保留メロディがとまる */
			if( NCUStatus & HOLD_STATE ){	/* 保留中なら、検出しない 1998/04/03  By T.Yamaguchi */
				/** 起動中タスクの強制終了 */
				FaxTadChildTaskExit();
				/** タイムアップ検出でループを抜ける */
				TxFaxTadAutoSwitchTaskMsg.Message = DETECT_TAD_TIMEUP;
				end_flag = OFF;
				break;
			}

#if (PRO_MODEM == ORANGE3)	/* Add By O.Kimoto 1998/04/29 */
			MDM_FilterStandbyMode();
#endif

			if (CHK_TAD_CNG_DetectAvailable()) {
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1007/09/05 */
				if (tskno_FilterOnOffTask == 0xFFFF) {
					detect_type = CNG_DETECT;				/* '95,12,27 By N.S. ANZU CNG検出方法変更 */
					cre_tsk(&tskno_FilterOnOffTask, TSK_ATD_FILTERONOFFDETECTTASK, &detect_type);
				}
#endif /* (PRO_MODEM == ORANGE3) */
				if (tskno_ToneDetectPattern1Task == 0xFFFF) {
#if (0)
** 					/* このタスクの先頭で使用しているＴｏｎｅＴｙｐｅとここで再セットするＴｏｎｅＴｙｐｅが違う。
** 					** その為、ＰＯＰＬＡＲ＿ＨではＣＮＧ検出が出来ない場合が発生していたので、
** 					** 上記と同じＴｏｎｅＴｙｐｅを使用するように変更
** 					**  By O.Kimoto 1998/04/29
** 					*/
** 					tone_data.ToneType = CNG_TONE;
#else
					tone_data.ToneType = CNG_TONE1;
#endif
					tone_data.SendMBX  = mbxno.NCU_FaxTadAutoSwitchTask;
					cre_tsk(&tskno_ToneDetectPattern1Task, TSK_ATD_TONEDETECTPATTERN1TASK, &tone_data);
				}
			}
			/** 無音検出が有効設定なら、無音検出タスクを起動 */
			if (CHK_UNI_SilentDetectAvailable()) {			/* '96,04,15 UNI By N.S.*/
				FilterTONE_Set();
				MDM_FilterSet(VOICE_FILTER);					/** モデムによる無音検出用フィルターセット */
				cre_tsk(&tskno_DetectSilentTask, TSK_NCU_DETECTSILENTTASK, &mbxno.NCU_FaxTadAutoSwitchTask);
			}
			break;

		case CNG_SILENT_TIME_UP:	/** CNG/無音検出期間タイムアップ(2) */
			/** タイマタスクの強制終了及び、CNG検出タスクが起動中なら、CNG検出タスクを強制終了 */
			del_tsk(&tskno_WatchTimerFaxTadTask);
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1007/09/05 */
			if (tskno_FilterOnOffTask != 0xFFFF) {
				del_tsk(&tskno_FilterOnOffTask);
			}
#endif /* (PRO_MODEM == ORANGE3) */
			if (tskno_ToneDetectPattern1Task != 0xFFFF) {
				del_tsk(&tskno_ToneDetectPattern1Task);
			}
			/* 保留中なら、検出しに行くと、保留メロディがとまる */
			if( NCUStatus & HOLD_STATE ){	/* 保留中なら、検出しない 1998/04/03  By T.Yamaguchi */
				/** 起動中タスクの強制終了 */
				FaxTadChildTaskExit();
				/** タイムアップ検出でループを抜ける */
				TxFaxTadAutoSwitchTaskMsg.Message = DETECT_TAD_TIMEUP;
				end_flag = OFF;
				break;
			}

			if (tskno_DetectSilentTask != 0xFFFF) {		/** 無音検出を実行中なら */
				/** タイマタスクの更新 (CNG/無音→無音) */
#if (0)	/* M.Tachibana 1997/04/03 */
//				if (((UWORD )( CHK_TAD_SilentPeriod())) > (( UWORD )( CHK_CNG_SilentDetectPeriod()))) {	/* '94,07,14 By N.S. */
//					timer_data.Time	   = (UWORD)((CHK_TAD_SilentPeriod() - CHK_CNG_SilentDetectPeriod())*1000);	/** 無音のみ検出期間(30sec) */
#endif
				if (((UWORD )( CHK_TAD_SilentPeriod())) > (( UWORD )( CHK_CNG_SilentDetectPeriod()*10))) {	/* '94,07,14 By N.S. */
					timer_data.Time	   = (UWORD)((CHK_TAD_SilentPeriod() - (CHK_CNG_SilentDetectPeriod()*10))*100);	/** 無音のみ検出期間(30sec) */
				}
				else {
					timer_data.Time	   = 1;
				}
				timer_data.ReturnValue = SILENT_TIME_UP;
				cre_tsk(&tskno_WatchTimerFaxTadTask, TSK_CMN_MAN_TIMER10MSTASK, &timer_data);
			}
			else {										/** 無音検出が無効なら */
				/** タイムアップ検出でループを抜ける */
				TxFaxTadAutoSwitchTaskMsg.Message = DETECT_TAD_TIMEUP;
				end_flag = OFF;
			}
			break;

		case DETECT_REMOTE_DTMF:	/** ＤＴＭＦ検出タスク 1997/11/13  By T.Yamaguchi */
		case SILENT_TIME_UP:		/** 無音検出期間タイムアップ(1) */
			/** 起動中タスクの強制終了 */
			FaxTadChildTaskExit();

			/** タイムアップ検出でループを抜ける */
			TxFaxTadAutoSwitchTaskMsg.Message = DETECT_TAD_TIMEUP;
			end_flag = OFF;
			break;

		default:
			break;
		}
	}
	/** 多機能電話制御タスクに通知メッセージを送信 */
	snd_msg(*tx_mail_box_no, &TxFaxTadAutoSwitchTaskMsg);
	wai_tsk(0xFFFF);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[NCU_FaxTadAutoSwitchTaskの子タスク終了ルーチン]
	function	:[
		1.子タスクを強制終了する
	]
	return		:[なし]
	common		:[
			UBYTE FaxTadDetectCNGFlag
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	FaxTadChildTaskExit(void)
{
	if (tskno_WatchTimerFaxTadTask != 0xFFFF) {
		del_tsk(&tskno_WatchTimerFaxTadTask);
	}
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1007/09/05 */
	if (tskno_FilterOnOffTask != 0xFFFF) {
		del_tsk(&tskno_FilterOnOffTask);
	}
#endif /* (PRO_MODEM == ORANGE3) */
	if (tskno_ToneDetectPattern1Task != 0xFFFF) {
		del_tsk(&tskno_ToneDetectPattern1Task);
	}
	if (tskno_DetectSilentTask != 0xFFFF) {
		del_tsk(&tskno_DetectSilentTask);
	}
	if (tskno_receive_dtmfTask != 0xFFFF) {	/* 1997/11/13  By T.Yamaguchi */
		del_tsk(&tskno_receive_dtmfTask);
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[NCU_FaxTadAutoSwitchTask強制終了処理ルーチン]
	function	:[
		1.子タスクを強制終了後、自タスクを終了する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void  NCU_FaxTadAutoSwitchExit(void)
{
	FaxTadChildTaskExit();
	exi_tsk();
}
