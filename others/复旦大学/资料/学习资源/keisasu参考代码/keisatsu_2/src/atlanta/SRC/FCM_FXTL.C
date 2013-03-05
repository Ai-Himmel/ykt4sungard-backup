/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_FXTL.C												 */
/*	モジュール	 :															 */
/*				 : FaxTelAutoSwitch()										 */
/*				 : FaxTelAutoSWAfterTransaction()							 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : ＦＡＸ／ＴＥＬ											 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"

#include "\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\define\uni_pro.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\ncu_cnst.h"
#include "\src\atlanta\define\ncu_def.h"
#include "\src\atlanta\define\unisw_c.h"

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
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


#include "\src\atlanta\define\ncu_msg.h"
#if 0 /* (PRO_NCU_TYPE == SATSUKI_TYPE) || (PRO_NCU_TYPE == MOMIJI_TYPE) || (PRO_NCU_TYPE == LAVENDER_JPN_TYPE)	/@ Add by TH92115 1995/03/14 */
			/* Tel/Fax動作中の極反検出処理追加,↑もみじの条件を追加	 竹内 Dec.21.1994 */
#include "\src\memsw\define\mem_sw_c.h"
#endif

#include "\src\atlanta\ext_v\fcm_data.h"
#if 0 /* (PRO_NCU_TYPE == SATSUKI_TYPE) || (PRO_NCU_TYPE == LAVENDER_JPN_TYPE)	/@ Add by TH92115	'95/03/08 BY M.HARADA -> 1995/03/14 */
	#include	"\src\atlanta\ext_v\bkupram.h"
#endif
#include "\src\atlanta\ext_v\sys_data.h"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\cl1_data.h"
#endif

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/01/27  By T.Yamaguchi */
 #include	"\src\atlanta\define\sysrxsw.h"
 void	VoicePrompt(UBYTE);
#endif
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
#include	"\src\atlanta\define\cl1_def.h"
#endif
void	GenerateRingStartRelayControl( void );
void	GenerateRingEndRelayControl( void );

/**************************************************************
*				BY:
*			  DATE:
*	  ROUTINE NAME:	 FaxTelAutoSwitch()
*	   DESCRIPTION:	 ＴＥＬ／ＦＡＸ自動受信
*		   RETURNS:
*		 CALLED BY:
*		　変更履歴:
**************************************************************/
WORD	  FaxTelAutoSwitch( void )
{
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	WORD	result;
	if (CMN_CheckAnswerEnable()) {
		result = FaxTelAutoSwitchForAnswer();
	}
	else {
		result = FaxTelAutoSwitchForNoAnswer();
	}
	return (result);

#else	/* NTT音声応答が入ってない機種 || ORANGEモデムを使っている音声応答対応の機種 */


	WORD		result;
/*	UWORD		tskno_timeup;	1996/12/12	By T.Yamaguchi */
	UWORD		tskno_rbt_cng;
	UWORD		tskno_ringsignal;
	UWORD		tskno_dse;					/* add by M.HARADA '94.12.21 */
	UBYTE		tskno_timeup;

	struct		Timer10msData_t	fax_tel_timeup;
	struct		GenerateRingData_t ring_data;


#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/01/27  By T.Yamaguchi */
	UWORD timer;
	MESSAGE_t		send_message;
#endif

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

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/01/27  By T.Yamaguchi */
    if( AttemptRxModeSwitch == SYS_FAX_TEL_READY ){
		fax_tel_timeup.Time	 = 9300;		/* 93sec */
		ring_data.StartTime	= 35;
	}
	else if( AttemptRxModeSwitch == SYS_TEL_FAX_READY ){
		ring_data.StartTime	= 4;
		fax_tel_timeup.Time	 = 3500;		/* 35sec */
	}
#endif

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
#if 0	/* この部分上に移動 1998/02/04  By T.Yamaguchi */
//	switch (CHK_UNI_GenerateBellWait()) {
//		case 0x00:
//			ring_data.StartTime	= 5;
//			break;
//		case 0x01:
//			ring_data.StartTime	= 6;
//			break;
//		case 0x02:
//			ring_data.StartTime	= 8;
//			break;
//		case 0x03:
//			ring_data.StartTime	= 10;
//			break;
//	}
#endif
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
/*	del_tsk(&tskno_timeup);					/@@ タイマータスク 停止 */

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
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
  #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/7/27 K.Kawata */
			if (CL1_ExtFunctionEnableFlag == 0) {
				if (CHK_UNI_Class1_EXT_Function()) {
					if ((CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK)
					   && (SYS_CL1_Status == 0) && (CL1_ExtFunctionEnableFlag == 0)) {	/* ｸﾗｽ1拡張が動作中 */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM;	/* CLASS1動作中セット */
						CL1_ExtFunctionEnableFlag = 1;
						del_tsk(&tskno_ringsignal);
						del_tsk(&tskno_rbt_cng);
						break;
					}
					else {
						result = CL1_IGNORE_CNG; 
					}
				}
				else {
					if (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK) {	/* ＰＣ受信 */
						del_tsk(&tskno_ringsignal);
						del_tsk(&tskno_rbt_cng);
						result = CL1_DETECT_CNG;
						break;
					}
					if (CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING) {	/* 電話に吹き替え*/
						result = CL1_IGNORE_CNG; 
					}
				}
			}
			else {
				result = CL1_IGNORE_CNG; 
				break;
			}
  #else
			if ( CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK) {	/* ＰＣ受信 */
				del_tsk(&tskno_ringsignal);
				del_tsk(&tskno_rbt_cng);
				result = CL1_DETECT_CNG;
				break;
			}
			if (CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING) {	/* 電話に吹き替え*/
				result = CL1_IGNORE_CNG; 
			}
  #endif
			/* その他(FAX_RECEIVE_ENABLE,FAX_RECEIVE_ONLY)は ＦＡＸ受信動作に移行 */
			if( !CMN_CheckMemoryReceiveEnable() || result == CL1_IGNORE_CNG ){	/** 自動受信不可（メモリー，プリンター）*/
 #else
  #if (PRO_PRINTER_RX == ENABLE)
			if (!CMN_CheckMemoryReceiveEnable() && !QueryPRxEnableWholeCNGDetect()) {	/** by H.Hirao 1999/02/27 */
  #else
    #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.1 K.Kawata */
			if (!CMN_CheckMemoryReceiveEnable() && !QueryPRxEnableWholeCNGDetect()) {
    #else
			if (!CMN_CheckMemoryReceiveEnable()) {	/** 自動受信不可（メモリー，プリンター）**/
    #endif
  #endif
 #endif
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
/*				cre_tsk( &tskno_timeup,TSK_CMN_MAN_TIMER10MSTASK,&fax_tel_timeup );	/@@ タイマータスク起動　＆　データセット　*/
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
 #if (PRO_CL1_TELFAX_LAN == ENABLE) 		/* S.Fukui June 19,1998 */
				|| ( FCOM_STOP_KEY == result ) || CL1_IGNORE_CNG == result) {
 #else
				|| (FCOM_STOP_KEY == result)) {
 #endif
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
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
		case	DETECT_BUSY:
#endif
			if (result == FCOM_TEL1_OFF_HOOK){
				FaxTelOffHookTEL1Flag = 1;
			}
			if(result == FCOM_TEL2_OFF_HOOK){
				FaxTelOffHookTEL2Flag = 1;
			}

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/03  By T.Yamaguchi */
			if (SYS_PhaseB1Flag) {
				/*
				** 音声応答処理でPhaseB1の時に、オフフックされた場合ＦＳＫ送出中 又は
				** ＦＳＫ受信中の場合、PhaseB1を抜けて来てから次の処理に移行する
				*/
				SYS_PhaseB1StopWaitFlag = 1;
				FaxComPerformingFlag = 0;
				if (SYS_Busy_detecting) {
					send_message.Item = FROM__NCU_SUB;	/* Itemは見ていない */
					send_message.Message = BUSY_DETECT_STOP;
					snd_msg( mbxno.FCM_BusyToneDetect, &send_message);
				}
				do {
					rcv_msg( mbxno.FCM_Task ,&FaxTelRxMessage );
				} while (FaxTelRxMessage->Message != OK_SLEEP);
			}
			/* 音声応答中ならクリアする */
			if (SYS_VoiceTxFlag) {
				VoiceReset();
			}
#endif
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
#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
		case	DETECT_BUSY:
#endif
			del_tsk(&tskno_rbt_cng);
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/03  By T.Yamaguchi */
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
			ReceiveError(0x11);			 /*===========================================
											 このReceiveErrorをコメントにすると、
											 FaxComPerformingFlagが0にならないために
											 疑似ベル鳴動の後に受信フェーズb1にはいる。
										   ===========================================*/
			del_tsk(&tskno_ringsignal);
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

#endif	/* End of (PRO_VOICE_ANSWER == ENABLE) && (PRO_MODEM == R288F) */
}



/*****************************************************************************
*				BY:	 harada
*	  ROUTINE NAME:	 FaxTelAutoSWAfterTransaction()
*	   DESCRIPTION:	 疑似ﾍﾞﾙ鳴動・OFF HOOK検出ﾀｽｸ[GenerateRingSignal()]でONさ
*					 れたH,LﾘﾚｰをOFFします。FaxTelAutoSwitch()で同ﾀｽｸが起動さ
*　　　　　　　　　　れた場合、終了処理ﾙｰﾁﾝとしてCALLして下さい。
*		   RETURNS:	 無し
*		 CALLED BY:	 AutoCalled()				 [	   FAX_TEL_MODE		]
*			 TSKID:
*		  PRIORITY:
*		MAILBOX ID:
******************************************************************************/
void		FaxTelAutoSWAfterTransaction( void )
{
	UWORD		timer;

	/*************/
	/** 24V OFF **/
	/*************/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/05/18 */
	CONT_24V_Off();					/** '93,07,27 **/
#else
	/*CONT_24V_On();なぜか、ＯＮになってる By Y.Suzuki 1998/03/31 */
	/*L400 NTTﾌｧﾈｯﾄの指摘事項にて、TEL/FAXからの受信中に外付けTELのフックをON/OFFすると*/
	/*付属TELのｽﾋﾟｰｶｰからﾌｯｷﾝｸﾞの音がするといわれた。OFFにしときます。昔は、ＯＦＦだった？*/
	/*CONT_24V_Off();					* '93,07,27 **/
	/* CONT_24V_Off でもハンドセット、外付け電話には、なお、２４Ｖの電圧がかかっている。*/
	/*この２４Ｖがかかってるおかげで、TEL/FAX受信中の外付けTELの受話器から送話器から入り込んだ*/
	/*音が聞こえてくる。ＮＴＴ立会検査事前検査で指摘されたため、TEL1,TEL2に電圧がかからないよう*/
	/*CONT_24V_ON ＋ RI_OFFにする。（福間氏のアドバイスによる）By Y.Suzuki 1998/05/13 */
	/*CONT_24V_ON の内容を変更し疑似電圧０Ｖとしました。 */
	CONT_24V_On();/* By Y.Suzuki 1998/05/14 */
#endif
	/*******************/
	/** H,L Relay OFF **/
	/*******************/
	if( 1 == FaxTelOffHookTEL1Flag ){
			H_RelayOff();
	}
	if( 1 == FaxTelOffHookTEL2Flag ){
			L_RelayOff();	/* for SATUKI & KIRI & MOMIJI & LAVENDER JPN */
	}
#if defined(FRA)
	GenerateRingSignalHLRelayFlag = 0;
#endif
	/****************************************/
	/** H,L Relay OFF - CML Relay OFF Wait **/
	/****************************************/
	timer = ( UWORD )50;
	FaxTimer( timer );
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/07 */
	MDM_ConfigReset();
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/12/19 */
	AnalogSwitchRXA_Set(); /* モデムアナログ端子の入力をトーン検出用から通常に切替 */
#endif /* (PRO_MODEM == R288F) */
}

#if (PRO_MODEM == R288F)
/* Ported from Clover by H.Kubo 1997/07/08 */
/*************************************************************************
	module		:[ホスト擬似ベル鳴動タスク削除指示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/02/24]
	author		:[村田]
*************************************************************************/
void FCM_DeleteRingSignal(void)
{
	MESSAGE_t		*receive_msg;
	MESSAGE_t		send_message;

	send_message.Item = FROM_FAXCOM_DUMMY;
	send_message.Message = MSG_FAXCOM_DELETE_GRS_TASK;
	snd_msg(mbxno.MAN_Task, &send_message);
	rcv_msg(mbxno.FCM_Dummy, &receive_msg);
}
#endif /* (PRO_MODEM == R288F) */
