/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMFXTL2.C												 */
/*	モジュール	 :															 */
/*				 : FaxTelAutoSwitch()										 */
/*				 : FaxTelAutoSWAfterTransaction()							 */
/*	作成者		 : Y.Murata													 */
/*	日	付		 : 1999/10/18												 */
/*	概	要		 : ＦＡＸ／ＴＥＬ											 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"

#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"

#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\define\uni_pro.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\ncu_cnst.h"
#include "\src\atlanta\define\ncu_def.h"
#include "\src\atlanta\define\unisw_c.h"

#if (PRO_MODEM == ORANGE3)
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#endif
#if (PRO_MODEM == R288F)
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
 #endif
#endif

#include "\src\atlanta\define\ncu_msg.h"

#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\cl1_data.h"
#endif

/*#if (PRO_VOICE_ANSWER == ENABLE)*//* 1998/01/27  By T.Yamaguchi */
 #include	"\src\atlanta\define\sysrxsw.h"
 void	VoicePrompt(UBYTE);
/*#endif*/

/*#if defined(POPLAR_F)*/
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\ext_v\sys_data.h"
/*#endif*/
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Add by J.Kishida 2002/11/14 */
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif

void	GenerateRingStartRelayControl( void );
void	GenerateRingEndRelayControl( void );


#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/12 */
/*
// \src\atlanta\poplar_f\src\fcmfxtl2.cでL400A専用ファイルとして
// 作られたのをコピーしてきました．
// まだHINOKI2しか使ってませんが，他の機種でNTT仕様を作るときは
// こっちのファイルを音声応答に使うのがいいと思います．
*/
/**************************************************************
*				BY:
*			  DATE:
*	  ROUTINE NAME:	 FaxTelAutoSwitch()
*	   DESCRIPTION:	 ＴＥＬ／ＦＡＸ自動受信
*		   RETURNS:
*		 CALLED BY:
*		　変更履歴:
**************************************************************/
WORD	  FaxTelAutoSwitchForAnswer( void )
{
	WORD		result;
	UWORD		tskno_rbt_cng;
	UWORD		tskno_ringsignal;
	UWORD		tskno_dse;					/* add by M.HARADA '94.12.21 */
	UBYTE		tskno_timeup;

	struct		Timer10msData_t	fax_tel_timeup;
	struct		GenerateRingData_t ring_data;


/*#if (PRO_VOICE_ANSWER == ENABLE)*//* 1998/01/27  By T.Yamaguchi */
	UWORD timer;
	MESSAGE_t		send_message;
/*#endif*/

	DelWaitFlag = 0;
	FaxTelTxMessage.Item	= FROM_FAXCOM;
	SYS_FaxTelTimeUpTimeFlag = 1;		/* add by HARADA '94/9/9 */
	/*-------------------------------------*/
	/*	SensorTask OFF HOOK 検出 STOP	   */
	/*-------------------------------------*/
	OffHookDetectStopFlag = 1;
	SYS_RingSignalStopFlag = 0;
	/*---------------*/
	/*	Moniter OFF	 */
	/*---------------*/
#if (1)/*defined(POPLAR_F)*/
	if (CHK_LineMonitor() == 0) {
		MonitorSpeakerOff();
	}
#else
	//MonitorSpeakerOff();									/** モニタースピーカー OFF */
#endif
	/*----------------*/
	/* TEL関係ﾘﾚｰ制御 */
	/*----------------*/
	GenerateRingStartRelayControl();
	/*--------------*/
	/*	タスク起動	*/
	/*--------------*/
	SYS_RingSignalStopFlag = 1;												/** リングシグナル停止フラグセット */

	/*------------------------------------*/
	/*	30 sec Timer  mode: FAX_TEL_MODE  */
	/*------------------------------------*/
	switch (CHK_UNI_GenerateBellWait()) {
	case 0x00:
		fax_tel_timeup.Time	 = 3000;		/* 30sec */
		ring_data.StartTime	= 5;
		break;
	case 0x01:
		fax_tel_timeup.Time	 = 3000;		/* 30sec */
		ring_data.StartTime	= 6;
		break;
	case 0x02:
		fax_tel_timeup.Time	 = 4000;		/* 40sec */
		ring_data.StartTime	= 8;
		break;
	case 0x03:
		fax_tel_timeup.Time	 = 4000;		/* 40sec */
		ring_data.StartTime	= 10;
		break;
	}

	/*---------------------------------------------------------------------
	** 【CSDR-No.27】疑似ベル鳴動時間の可変
	** 30/40/50/60secの切替えを追加する
	** 1998/10/05 H.Yoshikawa
	*/
	switch (CHK_UNI_GenerateBellPeriod()) {
	case GENERATE_BELL_PERIOD_40SEC:
		fax_tel_timeup.Time	 = 4000;		/* 40sec */
		break;
	case GENERATE_BELL_PERIOD_50SEC:
		fax_tel_timeup.Time	 = 5000;		/* 50sec */
		break;
	case GENERATE_BELL_PERIOD_60SEC:
		fax_tel_timeup.Time	 = 6000;		/* 60sec */
		break;
	case GENERATE_BELL_PERIOD_30SEC:
	default:
		/*-----------------------------------------------------------------
		** 上のCHK_UNI_GenerateBellWait()のところで、値がセットされているので、
		** ここではセットしません
		** ALTANTAでは、初期値00
		*/
		break;
	}

/*#if (PRO_VOICE_ANSWER == ENABLE)*//* 1998/01/27  By T.Yamaguchi */
    if( AttemptRxModeSwitch == SYS_FAX_TEL_READY ){
		fax_tel_timeup.Time	 = 9300;		/* 93sec */
		ring_data.StartTime	= 35;
	}
	else if( AttemptRxModeSwitch == SYS_TEL_FAX_READY ){
		ring_data.StartTime	= 4;
		fax_tel_timeup.Time	 = 3500;		/* 35sec */
	}
/*#endif*/

	fax_tel_timeup.SendMBX = mbxno.FCM_Task;
	fax_tel_timeup.ReturnValue = TMOUT_RESP;
	CMN_MultiTimer10msStart(&tskno_timeup,&fax_tel_timeup);

#if defined(JPN)	/* NCUによってはDSEを検出できない場合があるので注意 */
	cre_tsk( &tskno_dse, TSK_NCU_DETECTDSETASK, &(mbxno.FCM_Task));		/** ＤＳＥ検出タスクを起動 */
#endif
	cre_tsk(  &tskno_rbt_cng,TSK_NCU_TRANSRBTANDDETCNGTASK, &(mbxno.FCM_Task));					/** CNG検出・疑似リングバックトーン送出タスク スタート */
	/*-----------------------*/
	/*	疑似ﾍﾞﾙ鳴動動作設定	 */
	/*-----------------------*/
	ring_data.SendMBX		= mbxno.FCM_Task;
	ring_data.RingingTel	= ALL_TEL_RINGING;
	cre_tsk(  &tskno_ringsignal,TSK_NCU_GENERATERINGSIGNALTASK, &ring_data );				/** OH検出・呼び出しベル鳴動タスク スタート */
	/*--------------------*/
	/*	 事象の待合せ(1)  */
	/*--------------------*/
	rcv_msg( mbxno.FCM_Task, &FaxTelRxMessage );
	result = FaxTelRxMessage->Message;

	/*-------------------*/
	/*	Timer Task 停止	 */
	/*-------------------*/
	if (tskno_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_timeup);
	}

#if defined(JPN)
	del_tsk(&tskno_dse);					/** ＤＳＥ検出タスクを強制終了 */
#endif

	/*-----------------------------------------------------------------*/
	/*	タスク終了／事象に対する処理								   */
	/*																   */
	/*	#define		FCS_ERROR		   -1		FCSエラー	 検出	   */
	/*	#define		DETECT_COMMAND		1		コマンド	 検出	   */
	/*	#define		DETECT_DCS			2		DCS		  検出(NTT)	   */
	/*	#define		DETECT_CNG			3		CNG		  検出		from NCU_TransRBTAndDetCNGTask */
	/*	#define		DETECT_BUSY			4		Busy Tone 検出(NTT)	   */
	/*	#define		FCOM_STOP_KEY		5		Stop Key  検出		   */
	/*	#define		RECEIVE				6		コマンド	 検出	   */
	/*	#define		FCOM_TEL1_OFF_HOOK	7		TEL1 OFF HOOK  検出 from NCU_GENERATERINGSIGNALTASK */
	/*	#define		FCOM_TEL2_OFF_HOOK	8		TEL2 OFF HOOK  検出	from NCU_GENERATERINGSIGNALTASK */
	/*	#define		FCOM_HOOK_KEY		9		HOOK Key 入力  検出	from NCU_GENERATERINGSIGNALTASK */
	/*	#define		RING_TMOUT		   10		Ring Time Out		   */
	/*	#define		DETECT_TMOUT	   11		CNG検出部Time Out(NTT) */
	/*	#define		DETECT_STOP		   12		CNG検出部STOP検出	   */
	/*	#define		TX_COMMAND		   13		PhaeB1TxCom中(NTT)	   */
	/*	#define		DETECT_MEMORY_FULL 14		MemoryFull検出		   */
	/*	#define		OK_SLEEP		   15		子タスク 終了同期	   */
	/*	#define		OK_RESET		   16		T2タイマーReset		   */
	/*	#define		FLAG_RECEIVE	   17		Flag Receive		   */
	/*	#define		TMOUT_RESP		  265		Time Out			   */
	/*-----------------------------------------------------------------*/
	switch( result ){
	case	DETECT_CNG:
	case	RECEIVE:	/* どっから来るのかわからん */
		if (!CMN_CheckMemoryReceiveEnable()) {	/** 自動受信不可（メモリー，プリンター）**/
			/*---------------------*/
			/*	Timer Task 次起動  */
			/*---------------------*/
			/*------------------------------------*/
			/*	例外処理('93,05,21)				  */
			/*	ﾒﾓﾘ ﾌﾙ／ﾌﾟﾘﾝﾀ ｴﾗｰの状態で		  */
			/*				   発呼側がFAXの場合  */
			/*	疑似ﾍﾞﾙ鳴動でｵﾍﾟﾚｰﾀに注意を促す。 */
			/*	20 sec Timer  mode: FAX_TEL_MODE  */
			/*------------------------------------*/
			fax_tel_timeup.Time	 = 2000;		/* 20sec */
			fax_tel_timeup.SendMBX = mbxno.FCM_Task;
			fax_tel_timeup.ReturnValue = TMOUT_RESP;
			CMN_MultiTimer10msStart(&tskno_timeup,&fax_tel_timeup);
			/*--------------------*/
			/*	 事象の待合せ(2)  */
			/*--------------------*/
			rcv_msg( mbxno.FCM_Task ,&FaxTelRxMessage );
			result = FaxTelRxMessage->Message;
				if (tskno_timeup != 0xFF) {
				CMN_MultiTimer10msStop(&tskno_timeup);
			}
			if(( FCOM_TEL1_OFF_HOOK == result )
			|| ( FCOM_TEL2_OFF_HOOK == result )
			|| ( FCOM_HOOK_KEY == result )
			|| (FCOM_STOP_KEY == result)) {
				del_tsk(&tskno_ringsignal);
			}
			else{
				del_tsk(&tskno_ringsignal);
				result = DETECT_MEMORY_FULL;
			}
			FaxPhaseE(1);
			ReceiveError(0x11);
		}
		else{
			del_tsk(&tskno_ringsignal);
		}
		del_tsk(&tskno_rbt_cng);

		/* YAWARAより移植 by O.Kimoto 2002/11/14 */
		if (MDM_IsSingleToneON == 1) {
			MDM_ToneOff();
		}

		break;
	case	FCOM_TEL1_OFF_HOOK	 :
	case	FCOM_TEL2_OFF_HOOK	 :
	case	FCOM_STOP_KEY		 :
	case	DETECT_D_IN_DSE		 :			/* 94/12/21 ADD MOMOJI BY M.HARADA */
/*#if (PRO_VOICE_ANSWER == ENABLE)*//* 1998/03/11  By T.Yamaguchi */
	case	DETECT_BUSY:
/*#endif*/
		if (result == FCOM_TEL1_OFF_HOOK){
			FaxTelOffHookTEL1Flag = 1;
		}
		if(result == FCOM_TEL2_OFF_HOOK){
			FaxTelOffHookTEL2Flag = 1;
		}

/*#if (PRO_VOICE_ANSWER == ENABLE)*//* 1998/02/03  By T.Yamaguchi */
		if (SYS_PhaseB1Flag) {
			/*
			** 音声応答処理でPhaseB1の時に、オフフックされた場合ＦＳＫ送出中 又は
			** ＦＳＫ受信中の場合、PhaseB1を抜けて来てから次の処理に移行する
			*/
			CMN_DisableInterrupt();
			SYS_PhaseB1StopWaitFlag = 1;
			FaxComPerformingFlag = 0;
			CMN_EnableInterrupt();

	#if (1)/*defined(POPLAR_F)*/
			if (SYS_Busy_detecting) {
				if ((CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT) == DATA_SIGNALING_RATE_V34_BIT) {	/** Ｖ３４ */
					send_message.Item = FROM__NCU_SUB;	/* Itemは見ていない */
					send_message.Message = BUSY_DETECT_STOP;
					snd_msg( mbxno.FCM_V34Task, &send_message);
				}
				else {
					send_message.Item = FROM__NCU_SUB;	/* Itemは見ていない */
					send_message.Message = BUSY_DETECT_STOP;
					snd_msg( mbxno.FCM_BusyToneDetect, &send_message);
				}
			}
	#else
			//if (SYS_Busy_detecting) {
			//	send_message.Item = FROM__NCU_SUB;	/* Itemは見ていない */
			//	send_message.Message = BUSY_DETECT_STOP;
			//	snd_msg( mbxno.FCM_BusyToneDetect, &send_message);
			//}
	#endif

			do {
				rcv_msg( mbxno.FCM_Task ,&FaxTelRxMessage );
			} while (FaxTelRxMessage->Message != OK_SLEEP);
		}
		/* 音声応答中ならクリアする */
		if (SYS_VoiceTxFlag) {
			VoiceReset();
		}
	/*#if defined(POPLAR_F)*/
		/* 保留音送出中ならとめる */
		if (SYS_FaxMelodyFlag) {
			StopSendingMelodyToLine();
			SYS_FaxMelodyFlag = NO;
		}
	/*#endif*/
/*#endif*/
		del_tsk(&tskno_rbt_cng);

		/* YAWARAより移植 by O.Kimoto 2002/11/14 */
		if (MDM_IsSingleToneON == 1) {
			MDM_ToneOff();
		}

		ReceiveError(0x11);
		del_tsk(&tskno_ringsignal);

		FaxComPerformingFlag = 0;
		break;
	case	FCOM_HOOK_KEY	:
		del_tsk(&tskno_rbt_cng);

		/* YAWARAより移植 by O.Kimoto 2002/11/14 */
		if (MDM_IsSingleToneON == 1) {
			MDM_ToneOff();
		}

		ReceiveError(0x11);
		del_tsk(&tskno_ringsignal);

		FaxComPerformingFlag = 0;
		break;
	case	FCS_ERROR				 :
	case	TMOUT_RESP			 :
		del_tsk(&tskno_rbt_cng);

		/* YAWARAより移植 by O.Kimoto 2002/11/14 */
		if (MDM_IsSingleToneON == 1) {
			MDM_ToneOff();
		}

#if (1)/*(PRO_VOICE_ANSWER == ENABLE)*/	/* 1998/02/03  By T.Yamaguchi */
		if( AttemptRxModeSwitch == SYS_FAX_TEL_READY ){
			/******************************/
			/** 疑似ベル・呼出ブザー停止 **/
			/******************************/
			if (tskno_ringsignal != 0xffff) {
				del_tsk(&tskno_ringsignal);
			}
			/*****************************************/
			/** 保留音 - 音声ﾒｯｾｰｼﾞ③ Wait 75±20ms **/
			/*****************************************/
			timer = ( UWORD )75;
			FaxTimer( timer );
			/***************************/
			/** 音声ﾒｯｾｰｼﾞ③  6.4 sec **/
			/***************************/
			/*------------------------------------------------------*/
			/* 呼び出しましたが,近くにおりません｡申し訳ございません	*/
			/* が,後程おかけ直し下さい｡								*/
			/*------------------------------------------------------*/
			VoicePrompt(VOICE_C);
			ReceiveError(0x11);
			if (tskno_ringsignal != 0xffff) {
				del_tsk(&tskno_ringsignal);
			}
		}
		else if( AttemptRxModeSwitch == SYS_TEL_FAX_READY ){
			/******************************/
			/** 疑似ベル・呼出ブザー停止 **/
			/******************************/
			if (tskno_ringsignal != 0xffff) {
				del_tsk(&tskno_ringsignal);
			}
			/******************************************/
			/** 疑似RBT - 音声ﾒｯｾｰｼﾞ② Wait 75±20ms **/
			/******************************************/
			timer = ( UWORD )75;
			FaxTimer( timer );
			/***************************/
			/** 音声ﾒｯｾｰｼﾞ②  8.0 sec **/
			/***************************/
			/*--------------------------------------------------------------*/
			/* 呼び出しましたが,近くにおりません｡ﾌｧｸｼﾐﾘをご利用の方は,ﾋﾟｰと	*/
			/* いう音の後に送信して下さい｡									*/
			/*--------------------------------------------------------------*/
			VoicePrompt(VOICE_E);
			/*************************************/
			/** 音声ﾒｯｾｰｼﾞ② - CED Tx Wait 4sec **/
			/*************************************/
			timer = ( UWORD )4000;
			FaxTimer( timer );
			/*
			** AutoCalledに戻ったとき、２４ＶをＯＮにしてしまう。
			*/
			result = DETECT_CNG;	/* 1998/03/27  By T.Yamaguchi */
		}
		else{
			ReceiveError(0x11);
			if (tskno_ringsignal != 0xffff) {
				del_tsk(&tskno_ringsignal);
			}
		}
#else
		//ReceiveError(0x11);			 /*===========================================
		//								 このReceiveErrorをコメントにすると、
		//								 FaxComPerformingFlagが0にならないために
		//								 疑似ベル鳴動の後に受信フェーズb1にはいる。
		//							   ===========================================*/
		//del_tsk(&tskno_ringsignal);
#endif
		break;
	default	 :
		break;
	}
	GenerateRingEndRelayControl();
	SYS_RingSignalStopFlag = 0;		  /** '93,08,30 By N.S. **/
	/*-------------------------------------*/
	/*	SensorTask OFF HOOK 検出 START	   */
	/*-------------------------------------*/
	OffHookDetectStopFlag = 0;
	/*--------------*/
	/*	Moniter ON	*/
	/*--------------*/
	if ((FCOM_TEL1_OFF_HOOK != result)
	&& ((FCOM_TEL2_OFF_HOOK != result)
	&& (result != FCOM_HOOK_KEY )
	&& (CHK_LineMonitor()))) {	 /* CHK_LineMonitor() == 1になっていたのを修正しました 1996/08/24 Eguchi */
		MonitorSpeakerOn();
	}

	DelWaitFlag = 0;

	return( result );
}


/**************************************************************
*				BY:
*			  DATE:
*	  ROUTINE NAME:	 FaxTelAutoSwitch()
*	   DESCRIPTION:	 ＴＥＬ／ＦＡＸ自動受信
*		   RETURNS:
*		 CALLED BY:
*		　変更履歴:
**************************************************************/
WORD	  FaxTelAutoSwitchForNoAnswer( void )
{
	WORD		result;
	UWORD		tskno_rbt_cng;
	UWORD		tskno_ringsignal;
	UWORD		tskno_dse;					/* add by M.HARADA '94.12.21 */
	UBYTE		tskno_timeup;

	struct		Timer10msData_t	fax_tel_timeup;
	struct		GenerateRingData_t ring_data;

	DelWaitFlag = 0;
	FaxTelTxMessage.Item	= FROM_FAXCOM;
	SYS_FaxTelTimeUpTimeFlag = 1;		/* add by HARADA '94/9/9 */
	/*-------------------------------------*/
	/*	SensorTask OFF HOOK 検出 STOP	   */
	/*-------------------------------------*/
	OffHookDetectStopFlag = 1;
	SYS_RingSignalStopFlag = 0;
	/*---------------*/
	/*	Moniter OFF	 */
	/*---------------*/
	MonitorSpeakerOff();									/** モニタースピーカー OFF */
	/*----------------*/
	/* TEL関係ﾘﾚｰ制御 */
	/*----------------*/
	GenerateRingStartRelayControl();
	/*--------------*/
	/*	タスク起動	*/
	/*--------------*/
	SYS_RingSignalStopFlag = 1;												/** リングシグナル停止フラグセット */

	/*------------------------------------*/
	/*	30 sec Timer  mode: FAX_TEL_MODE  */
	/*------------------------------------*/
	switch (CHK_UNI_GenerateBellWait()) {
	case 0x00:
		fax_tel_timeup.Time	 = 3000;		/* 30sec */
		ring_data.StartTime	= 5;
		break;
	case 0x01:
		fax_tel_timeup.Time	 = 3000;		/* 30sec */
		ring_data.StartTime	= 6;
		break;
	case 0x02:
		fax_tel_timeup.Time	 = 4000;		/* 40sec */
		ring_data.StartTime	= 8;
		break;
	case 0x03:
		fax_tel_timeup.Time	 = 4000;		/* 40sec */
		ring_data.StartTime	= 10;
		break;
	}

	/*---------------------------------------------------------------------
	** 【CSDR-No.27】疑似ベル鳴動時間の可変
	** 30/40/50/60secの切替えを追加する
	** 1998/10/05 H.Yoshikawa
	*/
	switch (CHK_UNI_GenerateBellPeriod()) {
	case GENERATE_BELL_PERIOD_40SEC:
		fax_tel_timeup.Time	 = 4000;		/* 40sec */
		break;
	case GENERATE_BELL_PERIOD_50SEC:
		fax_tel_timeup.Time	 = 5000;		/* 50sec */
		break;
	case GENERATE_BELL_PERIOD_60SEC:
		fax_tel_timeup.Time	 = 6000;		/* 60sec */
		break;
	case GENERATE_BELL_PERIOD_30SEC:
	default:
		/*-----------------------------------------------------------------
		** 上のCHK_UNI_GenerateBellWait()のところで、値がセットされているので、
		** ここではセットしません
		** ALTANTAでは、初期値00
		*/
		break;
	}

	fax_tel_timeup.SendMBX = mbxno.FCM_Task;
	fax_tel_timeup.ReturnValue = TMOUT_RESP;
	CMN_MultiTimer10msStart(&tskno_timeup,&fax_tel_timeup);

#if defined(JPN)	/* NCUによってはDSEを検出できない場合があるので注意 */
	cre_tsk( &tskno_dse, TSK_NCU_DETECTDSETASK, &(mbxno.FCM_Task));		/** ＤＳＥ検出タスクを起動 */
#endif
	cre_tsk(  &tskno_rbt_cng,TSK_NCU_TRANSRBTANDDETCNGTASK, &(mbxno.FCM_Task));					/** CNG検出・疑似リングバックトーン送出タスク スタート */
	/*-----------------------*/
	/*	疑似ﾍﾞﾙ鳴動動作設定	 */
	/*-----------------------*/
	ring_data.SendMBX		= mbxno.FCM_Task;
	ring_data.RingingTel	= ALL_TEL_RINGING;
	cre_tsk(  &tskno_ringsignal,TSK_NCU_GENERATERINGSIGNALTASK, &ring_data );				/** OH検出・呼び出しベル鳴動タスク スタート */
	/*--------------------*/
	/*	 事象の待合せ(1)  */
	/*--------------------*/
	rcv_msg( mbxno.FCM_Task, &FaxTelRxMessage );
	result = FaxTelRxMessage->Message;

	/*-------------------*/
	/*	Timer Task 停止	 */
	/*-------------------*/
	if (tskno_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_timeup);
	}

#if defined(JPN)
	del_tsk(&tskno_dse);					/** ＤＳＥ検出タスクを強制終了 */
#endif

	/*-----------------------------------------------------------------*/
	/*	タスク終了／事象に対する処理								   */
	/*																   */
	/*	#define		FCS_ERROR		   -1		FCSエラー	 検出	   */
	/*	#define		DETECT_COMMAND		1		コマンド	 検出	   */
	/*	#define		DETECT_DCS			2		DCS		  検出(NTT)	   */
	/*	#define		DETECT_CNG			3		CNG		  検出		from NCU_TransRBTAndDetCNGTask */
	/*	#define		DETECT_BUSY			4		Busy Tone 検出(NTT)	   */
	/*	#define		FCOM_STOP_KEY		5		Stop Key  検出		   */
	/*	#define		RECEIVE				6		コマンド	 検出	   */
	/*	#define		FCOM_TEL1_OFF_HOOK	7		TEL1 OFF HOOK  検出 from NCU_GENERATERINGSIGNALTASK */
	/*	#define		FCOM_TEL2_OFF_HOOK	8		TEL2 OFF HOOK  検出	from NCU_GENERATERINGSIGNALTASK */
	/*	#define		FCOM_HOOK_KEY		9		HOOK Key 入力  検出	from NCU_GENERATERINGSIGNALTASK */
	/*	#define		RING_TMOUT		   10		Ring Time Out		   */
	/*	#define		DETECT_TMOUT	   11		CNG検出部Time Out(NTT) */
	/*	#define		DETECT_STOP		   12		CNG検出部STOP検出	   */
	/*	#define		TX_COMMAND		   13		PhaeB1TxCom中(NTT)	   */
	/*	#define		DETECT_MEMORY_FULL 14		MemoryFull検出		   */
	/*	#define		OK_SLEEP		   15		子タスク 終了同期	   */
	/*	#define		OK_RESET		   16		T2タイマーReset		   */
	/*	#define		FLAG_RECEIVE	   17		Flag Receive		   */
	/*	#define		TMOUT_RESP		  265		Time Out			   */
	/*-----------------------------------------------------------------*/
	switch( result ){
	case	DETECT_CNG:
	case	RECEIVE:	/* どっから来るのかわからん */
		if (!CMN_CheckMemoryReceiveEnable()) {	/** 自動受信不可（メモリー，プリンター）**/
			/*---------------------*/
			/*	Timer Task 次起動  */
			/*---------------------*/
			/*------------------------------------*/
			/*	例外処理('93,05,21)				  */
			/*	ﾒﾓﾘ ﾌﾙ／ﾌﾟﾘﾝﾀ ｴﾗｰの状態で		  */
			/*				   発呼側がFAXの場合  */
			/*	疑似ﾍﾞﾙ鳴動でｵﾍﾟﾚｰﾀに注意を促す。 */
			/*	20 sec Timer  mode: FAX_TEL_MODE  */
			/*------------------------------------*/
			fax_tel_timeup.Time	 = 2000;		/* 20sec */
			fax_tel_timeup.SendMBX = mbxno.FCM_Task;
			fax_tel_timeup.ReturnValue = TMOUT_RESP;
			CMN_MultiTimer10msStart(&tskno_timeup,&fax_tel_timeup);
			/*--------------------*/
			/*	 事象の待合せ(2)  */
			/*--------------------*/
			rcv_msg( mbxno.FCM_Task ,&FaxTelRxMessage );
			result = FaxTelRxMessage->Message;
				if (tskno_timeup != 0xFF) {
				CMN_MultiTimer10msStop(&tskno_timeup);
			}
			if(( FCOM_TEL1_OFF_HOOK == result )
			|| ( FCOM_TEL2_OFF_HOOK == result )
			|| ( FCOM_HOOK_KEY == result )
			|| (FCOM_STOP_KEY == result)) {
				del_tsk(&tskno_ringsignal);
			}
			else{
				del_tsk(&tskno_ringsignal);
				result = DETECT_MEMORY_FULL;
			}
			FaxPhaseE(1);
			ReceiveError(0x11);
		}
		else{
			del_tsk(&tskno_ringsignal);
		}
		del_tsk(&tskno_rbt_cng);
		break;
	case	FCOM_TEL1_OFF_HOOK	 :
	case	FCOM_TEL2_OFF_HOOK	 :
	case	FCOM_STOP_KEY		 :
	case	DETECT_D_IN_DSE		 :			/* 94/12/21 ADD MOMOJI BY M.HARADA */
		if (result == FCOM_TEL1_OFF_HOOK){
			FaxTelOffHookTEL1Flag = 1;
		}
		if(result == FCOM_TEL2_OFF_HOOK){
			FaxTelOffHookTEL2Flag = 1;
		}
		del_tsk(&tskno_rbt_cng);

		ReceiveError(0x11);
		del_tsk(&tskno_ringsignal);

		FaxComPerformingFlag = 0;
		break;
	case	FCOM_HOOK_KEY	:
		del_tsk(&tskno_rbt_cng);

		ReceiveError(0x11);
		del_tsk(&tskno_ringsignal);

		FaxComPerformingFlag = 0;
		break;
	case	FCS_ERROR:
	case	TMOUT_RESP:
	case	DETECT_BUSY:					/* 擬似ベル鳴動中のBusyTone検出処理追加 By O.Kimoto 2002/11/01 */
		del_tsk(&tskno_rbt_cng);
		ReceiveError(0x11);			 /*===========================================
										 このReceiveErrorをコメントにすると、
										 FaxComPerformingFlagが0にならないために
										 疑似ベル鳴動の後に受信フェーズb1にはいる。
									   ===========================================*/
		del_tsk(&tskno_ringsignal);
		break;
	default	 :
		break;
	}
	GenerateRingEndRelayControl();
	SYS_RingSignalStopFlag = 0;		  /** '93,08,30 By N.S. **/
	/*-------------------------------------*/
	/*	SensorTask OFF HOOK 検出 START	   */
	/*-------------------------------------*/
	OffHookDetectStopFlag = 0;
	/*--------------*/
	/*	Moniter ON	*/
	/*--------------*/
	if ((FCOM_TEL1_OFF_HOOK != result)
	&& ((FCOM_TEL2_OFF_HOOK != result)
	&& (result != FCOM_HOOK_KEY )
	&& (CHK_LineMonitor()))) {	 /* CHK_LineMonitor() == 1になっていたのを修正しました 1996/08/24 Eguchi */
		MonitorSpeakerOn();
	}

	DelWaitFlag = 0;

	return( result );

}

#else
void	FaxTelDummySwitch(void)
{
	/* 音声応答の無い機種の為のダミー関数 */
}
#endif

