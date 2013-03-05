/**********************************************************************
* ANZU
*
*	File   Name:	NCU_MAIN.C
*	Coded    by:	坂本直史
*	Module Name:	NCU_Task()
*					NCUTaskExit()
*					NCU_TaskExit()
*	Note		:	待機状態時回線監視
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
#include	"\src\memsw\define\mems_pro.h"
#include	"\src\atlanta\define\message.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\define\sys_remo.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\atd_pro.h"	/* for ATD Debug '95,12,13 */
#include	"\src\atlanta\define\buzzer.h"
#include	"\src\atlanta\define\cmn_def.h" /* 1996/02/22 Eguchi @SYS_SPK_OUT_FAKEBUZZER@ */

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
#include	"\src\atlanta\ext_v\man_data.h"

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/11/18 */
#include "\src\atlanta\mdm\orange\define\MDM_DEF.H"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/11/18 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#endif

#include	"\src\atlanta\ext_v\sys_port.h"

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include	"\src\atlanta\sh7043\define\def_tib.h"


#if (PRO_CLASS1 == ENABLE)	/* 96.04.28 by Y.T */
#include	"\src\atlanta\define\cl1_def.h"
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/19 By M.Maeda */
#include	"\src\atlanta\define\man_pro.h"
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/21 */
#include	"\src\atlanta\define\sys_line.h"
#endif /* defined (KEISATSU) */

#if (PRO_LINENUMBER == SINGLE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
static	UWORD		tskno_DetectCalledTask			=	0xFFFF;
#endif
static	UWORD		tskno_TelephoneHookCheckTask	=	0xFFFF;

#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
	static	UWORD	tskno_DetectFnetTimerTask = 0xFFFF;
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/08/21 */
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
	UWORD	tskno_NCU_ND_Rx		= 0xffff;
#else /* !defined (KEISATSU) */
	static UWORD	tskno_NCU_ND_Rx		= 0xffff;
#endif /* defined (KEISATSU) */
#endif

#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
	static UWORD	tskno_CI_TimerTask = 0xffff; /* added by H.Hirao 1998/12/28 */
#endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[待機状態時回線監視MAINタスク]
	function	:[
		1.着信検出・ＨＯＯＫ状態変化監視タスクの起動・削除
		2.回線監視モジュール使用変数の初期化
		3.着信情報・ＨＯＯＫ状態変化情報の子タスクよりメイン・タスクへの中継
		4.着信情報・ＨＯＯＫ情報の相関関係調整（同時発生の場合）
		5.発着衝突防止
	]
	return		:[なし]
	common		:[
		NCUStatus						:回線監視モジュール動作状態を記憶
		SYS_RingCounter					:呼出ベル鳴動回数をカウント
		SYS_HoldKeyInputFlag			:保留キー入力情報
		SYS_HookKeyInputFlag			:回線捕捉キー入力情報
		HoldKeyInputFlag 				:保留キー入力検出同期フラグ
		HookKeyInputFlag 				:回線捕捉キー入力同期フラグ
		SYS_BRC_OnHook_DetectFlag		:回線電圧チェック済記憶フラグ
		BRC_TelephoneOhProtectFlag		:ブランチ電話ＯＨ検出排他情報
		BRC_OhDetectFlag 				:ブランチ電話ＨＯＯＫ状態検出設定を記憶
		BranchTelData.OnOffHookLevel	:待機状態・内線通話状態時のブランチ電話のＯＮ／ＯＦＦ　ＨＯＯＫ状態回線電圧しきい値
		BranchTelData.CurrentLoopLevel	:回線未接続時の回線電圧レベル
		BranchTelData.CiInputLevel		:内線通話状態時のＣＩ入力による回線電圧変動のしきい値
		BranchTelData.TADOffHookLevel	:保留状態・内蔵留守番電話着信状態時のブランチ電話のＯＮ／ＯＦＦ　ＨＯＯＫ状態回線電圧しきい値
	] 
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void			NCU_Task( void )
{
	MESSAGE_t    			*RxNCUTaskMsg;
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
	struct Timer10msData_t	fnet_timer;
#endif
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
	struct Timer10msData_t	ci_timer; /* added by H.Hirao 1998/12/28 */
#endif
	UWORD					comp_min_on_time;	/* 1999/12/06 by K.Okada */

	/*---------------------------*/
	/** 回線監視使用変数の初期化 */
	/*---------------------------*/
	TxNCUTaskMsg.Item   			 			 = FROM_NCU_TASK;

	NCUStatus    				 				 = 0;
	SYS_HoldKeyInputFlag			 			 = 0;
	SYS_DialChange	 							 = 0;
	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS]	&= ~SYS_STOP_TELEPHONE;
	SYS_HookKeyInputFlag = 0;

	SYB_RedialBufWritePointer					 = 0;

	TADStatus								 	 = 0;
	TransferReceiveAvailableTime				 = 0;
	TransferReceiveFlag							 = 0;
	RingingOnTime								 = 0;
	SamplingBuff[0]								 = 0;	/* for NCU_Ring.C */
	HookKeyInputFlag 							 = 0;
	HoldKeyInputFlag 							 = 0;
	NumberKeyInputFlag 							 = 0;
	OhPortStatus				                 = 0;
#if (PRO_MODEM == ORANGE3)
	FaxTadDetectCNGFlag							 = 0;
#endif
#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
	NCU_IsDetRemotePulse						 = 0;
	NCU_IsRemotePulseRx							 = 0;
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/29 */
	if (SYS_HookKeyFlagBk) { /* 強制終了によってフックキーを押下場合 */
		SYS_HookKeyFlagBk						= FALSE;
		SYS_HookKeyInputFlag					= TRUE;
	}
#endif /* defined (KEISATSU) */


#if defined(EC1)	/* '98/04/9 M.H. HookKey timer for BEL */
	if (SYB_MachineParameter[0] == 0) {		/* BEL */
		HookKeyTimer		 = 0;
	}
#endif
	/*-----------------------------------------------------*/
	/** 待機状態時回線監視タスク起動時の受信モードを保持   */
	/*-----------------------------------------------------*/
	NCU_RxModeSwitch 							 = CMN_PresentReceiveMode();
	/*-------------------------------*/
	/** リレー／フィルター設定初期化 */
	/*-------------------------------*/
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/25 */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/08/21 */ /* Moved from before while loop 1998/10/23 */
	if (DEBUG_NumberDisplay) {
		if (!SYS_LineNDStatus) {
			tskno_NCU_ND_Rx		= 0xffff;
			NCU_ND_InitializeStatus();
		}
		InitializeRelay();
	}
	else {
		InitializeRelay();
		tskno_NCU_ND_Rx		= 0xffff;
		NCU_ND_InitializeStatus();
	}
#else
	InitializeRelay();
#endif
#else /* defined (KEISATSU) */
	InitializeRelay();
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/08/21 */ /* Moved from before while loop 1998/10/23 */
	tskno_NCU_ND_Rx		= 0xffff;
	NCU_ND_InitializeStatus();
#endif
#endif /* defined (KEISATSU) */
#if defined(JPN)
	/*-------------------------------------------------------*/
	/** Ｆ網着信－受信不可の際の回線断処理(ANZUにて追加処理) */
	/*-------------------------------------------------------*/
	if( SYS_F_Net_AutoCalledDisableFlag ){
		F_Net_DisconnectRelayControl();
	}
	SYS_F_Net_AutoCalledDisableFlag = 0;
#endif
	/*--------------------------------------------------------------------*/
	/** 待機状態時回線監視モジュール子タスク生成（着信検出・HOOK状態監視) */
	/*--------------------------------------------------------------------*/
	tskno_TelephoneHookCheckTask 				= 0xFFFF;
	cre_tsk(&tskno_TelephoneHookCheckTask, TSK_NCU_TELEPHONEHOOKCHECKTASK, &(mbxno.NCU_Task));
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/14 */
	/* ここではない */
	/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/25 */
	if (DEBUG_NumberDisplay) {
		if (SYS_LineNDStatus == ND_READY) { /* ナンバーディスプレイ機能起動しない場合 */
			if (tskno_DetectCalledTask == 0xFFFF) {
				cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
			}
			if (tskno_Detect2ndCalledTask == 0xFFFF) {
				cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
			}
		}
	}
 #else /* defined (KEISATSU) */
	tskno_DetectCalledTask 						= 0xFFFF;
	cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
 #endif /* defined (KEISATSU) */

#if (PRO_CL1_TELFAX_LAN == ENABLE) /* Class1 F網対応 S.Fukui June 19,1998  */
	/*
	* F網でClass1呼び出し中ならタイマをスタートする
	*/
	fnet_timer.Time = 3000/10;
	fnet_timer.SendMBX = mbxno.NCU_Task;
	fnet_timer.ReturnValue = DETECT_F_NET_TIMEOUT;
	tskno_DetectFnetTimerTask = 0xFFFF;
	if (SYS_CL1_Status & CL1_FNET_CALLED) {
		cre_tsk(&tskno_DetectFnetTimerTask, TSK_CMN_MAN_TIMER10MSTASK, &fnet_timer);
	}
#endif
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
	/*
	** 原稿蓄積中のＣＩ検出中なら、タイマーをスタートする added by H.Hirao 1998/12/28
	*/
	ci_timer.Time = 3000/10; /* ３秒 */
	ci_timer.SendMBX = mbxno.NCU_Task;
	ci_timer.ReturnValue = DETECT_CI_TIMEUP;
	tskno_CI_TimerTask = 0xffff;
	if (SYS_CalledRequestForDocStore) {
		cre_tsk(&tskno_CI_TimerTask, TSK_CMN_MAN_TIMER10MSTASK, &ci_timer);
	}
#endif

				/*-------------------------------------------*/
	while(1){	/** 着信／ＯＦＦ　ＨＯＯＫ検出するまでループ */
				/*-------------------------------------------*/
		/*---------------*/
		/** 事象の待合せ */
		/*---------------*/
		rcv_msg(mbxno.NCU_Task, &RxNCUTaskMsg);
										/*-----------------------*/
		switch(RxNCUTaskMsg->Message){	/** 発生事象の処理を行う */
										/*-----------------------*/
													/*-----------------------------*/
			case	DETECT_CI					:	/**       ＣＩ検出の場合       */
			case	DETECT_CI_TIMEUP			:	/** ＣＩ検出ＴｉｍｅＵｐの場合 */
													/*-----------------------------*/
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)	/* added by H.Hirao 1998/12/28 */
				if (tskno_CI_TimerTask != 0xffff) {
					del_tsk(&tskno_CI_TimerTask);
				}
 #if (PRO_NUMBER_DISPLAY == DISABLE) /* added by H.Hirao 1999/01/30 */
				/* ナンバーディスプレイ機能が無い場合、NCU_DetectCalledTask以外のタスクからのメッセージでも
				** NCU_DetectCalledTaskにメッセージを送信してしまい、snd_msg()がぶつかる by H.Hirao 1999/01/30
				*/
				if (RxNCUTaskMsg->Item == FROM__NCU_RING) {
 #endif
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/27 */
				if (RxNCUTaskMsg->Item == FROM__NCU_RING) {
#endif
					TxNCUTaskMsg.Message = OK_CONT;
					snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/27 */
				}
#endif
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
 #if (PRO_NUMBER_DISPLAY == DISABLE)
				}	/* added by H.Hirao 1999/01/30 */
 #endif
#endif
				/*---------------------------------------*/
				/** メイン・タスクへ通知（発着衝突回避） */
				/*---------------------------------------*/
				if(RxNCUTaskMsg->Message == DETECT_CI){
					NCUStatus |= DETECT_CI_STATE;
					TxNCUTaskMsg.Message = MSG_DETECT_CI;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/14 */
#if !defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modified by SMuratec 李 2005/12/07 */
					if (NCU_ND_Status & ND_COUNTING_2ND_RING) {
						if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了メッセージを投げさせない */
							del_tsk(&tskno_NCU_ND_Rx);
						}
					}
#endif /* !defined (KEISATSU) */
#endif
				}
				else{
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/12 */
					if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
						del_tsk(&tskno_NCU_ND_Rx);
					}
					NCU_ND_InitializeStatus();
 #endif
					NCUStatus &= ~DETECT_CI_STATE;
					TxNCUTaskMsg.Message = MSG_DETECT_CI_TIMEUP;
				}

				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);

				break;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
			case	DETECT_CALLED_REQUEST_EXT:	/** 拡張ライン着信検出の場合 */
			case	DETECT_F_NET_CALLED_SIGNAL_EXT:	/** 拡張ライン(1300Hz)着信検出の場合 */
				NCUStatus |=  DETECT_CALL;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/15 */
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
				if (DEBUG_NumberDisplay) {
					if (SYS_LineNDStatus == ND_USED_IN_EXT) {
						NCU_ND_SetCallDetectedStatus();
					}
				}
#else /* defined (KEISATSU) */
				NCU_ND_SetCallDetectedStatus();
#endif /* defined (KEISATSU) */
#endif
				/*---------------------------------*/
				/** メイン・タスクへ着信検出を通知 */
				/*---------------------------------*/
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/12 */
				if (RxNCUTaskMsg->Item == FROM__NCU_RING) {
					TxNCUTaskMsg.Message = OK_CONT;
					snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
				}
 #endif /* defined (KEISATSU) */
				if( DETECT_CALLED_REQUEST_EXT == RxNCUTaskMsg->Message ){
					TxNCUTaskMsg.Message = MSG_DETECT_CALL_TO_FAX_EXT;
				}
				else{
					TxNCUTaskMsg.Message = MSG_DETECT_F_NET_EXT;
				}
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
				/*---------------------------------------*/
				/** 待機状態時回線監視モジュール終了処理 */
				/*---------------------------------------*/
				NCUTaskExit();

				break;
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/08/04 */
			case	DETECT_ND_CAR_CALLED_SIGNAL:
				if (!CHK_NumberDisplayByExtPhoneON() && !(NCU_ND_Status & ND_CAR_DETECTED)) {
					NCU_ND_SetCarDetectedStatus();
					NCU_TaskKillChildTasks();
					TxNCUTaskMsg.Message = MSG_DETECT_ND_CAR;
					snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
					/*-----------------------------------*/
					/** ナンバーディスプレイ情報受信処理 */
					/*-----------------------------------*/
					cre_tsk(&tskno_NCU_ND_Rx, TSK_NCU_ND_RXPROCEDURETASK, &mbxno.NCU_Task);
					snd_msg(mbxno.NCU_ND, &TxNCUTaskMsg); /* なんでもいいから一つ NCU_ND_RxProcedureTask にメッセージをほる。*/
				}
				else {
					NCU_ND_SetCarDetectedStatus();
					TxNCUTaskMsg.Message = OK_CONT;
					snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
				}
				break;
			case	DETECT_ND_OH_1ST_RESPONSE:
				if (CHK_NumberDisplayByExtPhoneON() && ((NCU_ND_Status & (ND_CI_SEQUENCE_DETECTED| ND_CAR_DETECTED)))) {
					NCU_ND_SetCarDetectedStatus();
					NCU_TaskKillChildTasks();
					TxNCUTaskMsg.Message = MSG_DETECT_ND_CAR;
					snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
					/*-----------------------------------*/
					/** ナンバーディスプレイ情報受信処理 */
					/*-----------------------------------*/
					cre_tsk(&tskno_NCU_ND_Rx, TSK_NCU_ND_RXPROCEDURETASK, &mbxno.NCU_Task);
					snd_msg(mbxno.NCU_ND, &TxNCUTaskMsg); /* なんでもいいから一つ NCU_ND_RxProcedureTask にメッセージをほる。*/
				}
				/*-------------------------------------------*/
				/* NCU_TelephoneHookCheckTask へメッセージ。 */
				/*-------------------------------------------*/
				TxNCUTaskMsg.Message = OK_CONT;
				snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxNCUTaskMsg);
				break;
			case DETECT_ND_NUMBER:
				snd_msg(mbxno.NCU_ND, &TxNCUTaskMsg); /* NCU_ND_RxProcedureTask と同期を取る */
				TxNCUTaskMsg.Message = MSG_DETECT_ND_NUMBER;
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
				break;
			case 	MADE_ND_RX_RESPONSE:
				/* cre_tsk(&tskno_TelephoneHookCheckTask, TSK_NCU_TELEPHONEHOOKCHECKTASK, &(mbxno.NCU_Task)); */
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
				if (DEBUG_NumberDisplay) {
					if (tskno_DetectCalledTask == 0xFFFF) {
						cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
					}
					else if (tskno_Detect2ndCalledTask == 0xFFFF) {
						cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
					}
				}
				else {
					cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
				}
#else /* !defined (KEISATSU) */
				cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
#endif /* defined (KEISATSU) */
				/* NCU_ND_AfterNdRxRelaySetting(); */ /* NCU_ND_RxProcedureTask へ移動 by H.Kubo 1998/10/23 */
				break;
			case IGNORE_ND_INFO_ARRIVAL: /* added by H.Kubo 1998/11/21 */
				/* ND 受信中にメインに通知しなかったオフフック通知をここでします。 */
				if( NCUStatus & HOOK_KEY_ON_STATE){
					TxNCUTaskMsg.Message  = MSG_DETECT_INPUT_HOOK_KEY;
				}
				else if( NCUStatus & TELEPHONE1_OFF_HOOK ){
					TxNCUTaskMsg.Message  = MSG_DETECT_TEL1_OFF_HOOK;
				}
				else if( NCUStatus & TELEPHONE2_OFF_HOOK ){
					TxNCUTaskMsg.Message  = MSG_DETECT_TEL2_OFF_HOOK;
				}
				else {
					TxNCUTaskMsg.Message = MSG_NCU_RESTART;
				}
				NCU_ND_AfterNdRxRelaySetting(); /* added by H.Kubo 1998/11/26 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/26 */
				if (DEBUG_NumberDisplay) {
					if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
						del_tsk(&tskno_NCU_ND_Rx);
					}
					tskno_NCU_ND_Rx		= 0xffff;
					NCU_ND_InitializeStatus();
 					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
					if (tskno_DetectCalledTask == 0xFFFF) {
						cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
					}
					else if (tskno_Detect2ndCalledTask == 0xFFFF) {
						cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
					}
				}
				else {
#if 0 /* 警察FAX DVT_ID92 (ナンバーディスプレイ) Modified by SMuratec 李 2005/12/01 */
@@					NCU_ND_SetCallDetectedStatus(); /* added by H.Kubo 1998/11/26 */
#else
					NCU_ND_InitializeStatus();
#endif
				}
 #else /* !defined (KEISATSU) */
				NCU_ND_SetCallDetectedStatus(); /* added by H.Kubo 1998/11/26 */
 #endif /* defined (KEISATSU) */
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
				/*---------------------------------------*/
				/** 待機状態時回線監視モジュール終了処理 */
				/*---------------------------------------*/
				NCUTaskExit();
				break;
			case 	DETECT_2ND_RING: /* added by H.Kubo 1998/10/12 */
				/*---------------------------------------*/
				/** メイン・タスクへ通知（発着衝突回避） */
				/*---------------------------------------*/
#if 0 /* メモリオーバーなどによるモデムダィヤルイン FAX 着信拒否の処理を追加。 by H.Kubo 1999/02/25 */
@				TxNCUTaskMsg.Message = MSG_DETECT_RING;
@				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
@				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
@				NCU_ND_AfterNdRxRelaySetting();
@				cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
#else
				if (NCU_ND_Status & ND_MODEM_DIALIN_FAX_DIAL) {
					TxNCUTaskMsg.Message = MSG_DETECT_TRANSFER_MODEM_D_IN;
					snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg); /* 着信してもいいかどうかのメッセージ待ち */
					if (RxNCUTaskMsg->Message == MSG_EXIT) { /* 着信 */
						NCU_ND_SetCallDetectedStatus();
						NCUStatus |=  DETECT_CALL;
						NCUTaskExit();
					}
					else { /* 着信不可 */
						TxNCUTaskMsg.Message = OK_CONT;
						snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
					}
				}
				else {
 #if (PRO_CLASS1 == ENABLE)	/* クラス１をナンバーディスプレイに対応させます by H.Hirao 1999/05/12 */
					TxNCUTaskMsg.Message = MSG_DETECT_RING_DUMMY;
 #else
					TxNCUTaskMsg.Message = MSG_DETECT_RING;
 #endif
					snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
					NCU_ND_AfterNdRxRelaySetting();
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
					if (DEBUG_NumberDisplay) {
						NCU_ND_InitializeStatus();
						if (tskno_DetectCalledTask == 0xFFFF) {
							cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
						}
						else if (tskno_Detect2ndCalledTask == 0xFFFF) {
							cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
						}
					}
					else {
						cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
					}
#else /* !defined (KEISATSU) */
					cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
#endif /* defined (KEISATSU) */
				}
#endif
				break;
			case 	DETECT_MODEM_DIALIN_FAX_CALL: /* 使わなくなります。 by H.Kubo 1999/02/25 */
				/*---------------------------------------*/
				/* モデムダイヤルインで FAX 番号に着信 */
				/*---------------------------------------*/
#if 0 /* メモリオーバーなどによるモデムダィヤルイン FAX 着信拒否の処理を追加。 by H.Kubo 1999/02/25 */
				TxNCUTaskMsg.Message = MSG_DETECT_TRANSFER_D_IN;
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
				NCU_ND_SetCallDetectedStatus();
				NCUTaskExit();
#else
	/* メモリオーバーなどによるモデムダィヤルイン FAX 着信拒否の処理を追加。 by H.Kubo 1999/02/25 */
				if (NCU_ND_Status & ND_MODEM_DIALIN_FAX_DIAL) {
					TxNCUTaskMsg.Message = MSG_DETECT_TRANSFER_MODEM_D_IN;
					snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg); /* 着信してもいいかどうかのメッセージ待ち */
					if (RxNCUTaskMsg->Message == MSG_EXIT) { /* 着信 */
						NCU_ND_SetCallDetectedStatus();
						NCUStatus |=  DETECT_CALL;
						NCUTaskExit();
					}
					else { /* 着信不可 */
						/* ここで NCU_ND_RxProcedureTask を殺すと、呼出音停止検出ができない。
						** DETECT_CALLED_REQUEST_ND の処理の部分で殺すことにします。
						*/
#if 0  /* Deleted by H.Kubo 1999/03/18 */
@@						if (tskno_NCU_ND_Rx != 0xFFFF) { /* ND 制御終了。 IR 検出へ移行 */
@@							del_tsk(&tskno_NCU_ND_Rx);
@@						}
#endif
						NCU_ND_AfterNdRxRelaySetting();
						cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
					}
				}
				else {
 #if (PRO_CLASS1 == ENABLE)	/* クラス１をナンバーディスプレイに対応させます by H.Hirao 1999/05/12 */
					TxNCUTaskMsg.Message = MSG_DETECT_RING_DUMMY;
 #else
					TxNCUTaskMsg.Message = MSG_DETECT_RING;
 #endif
					snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
					NCU_ND_AfterNdRxRelaySetting();
					cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
				}
#endif
				break;
			case 	DETECT_2ND_RING_TIMEUP:
				if (RxNCUTaskMsg->Item == FROM__NCU_RING) {  /* 1998/10/20 */
					TxNCUTaskMsg.Message = OK_CONT;
					snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
				}
				else {
					if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待強制終了 */
						del_tsk(&tskno_NCU_ND_Rx);
					}
				}

				/*---------------------------------------------------------------------
				** NDの処理を行った後は、必ず、NCU_Taskを再起動します。
				** ここでは、TEL鳴動したが、オフフックする前に、発信者が受話器を置いた場合にきます。
				** 1998/11/14 H.Yoshikawa
				*/
#if (0)	/* 1998/11/14 H.Yoshikawa */
				NCU_ND_InitializeStatus();
				InitializeRelay();
				/* ナンバーディスプレイ表示消去メッセージ送出 by H.Kubo 1998/10/23 */
				NCUStatus &= ~DETECT_CI_STATE;
				TxNCUTaskMsg.Message = MSG_DETECT_CI_TIMEUP;
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
#endif
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/26 */
				if (DEBUG_NumberDisplay) {
					if (SYS_LineNDStatus == ND_USED_IN_EXT) {
						SYS_RingCounterExt = 0; /* 着信拒否処理の追加に伴い、呼出音停止後の転送受信をここで防止。 by H.Kubo 1999/02/26 */
						if (tskno_Detect2ndCalledTask != 0xFFFF) {
							del_tsk(&tskno_Detect2ndCalledTask);
						}
					}
					else {
						SYS_RingCounter = 0; /* 着信拒否処理の追加に伴い、呼出音停止後の転送受信をここで防止。 by H.Kubo 1999/02/26 */
						if (tskno_DetectCalledTask != 0xFFFF) {
							del_tsk(&tskno_DetectCalledTask);
						}
					}
					if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待強制終了 */
						del_tsk(&tskno_NCU_ND_Rx);
					}
					tskno_NCU_ND_Rx		= 0xffff;
					NCU_ND_InitializeStatus();
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
					if (tskno_DetectCalledTask == 0xFFFF) {
						cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
					}
					else if (tskno_Detect2ndCalledTask == 0xFFFF) {
						cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
					}
				}
				else {
					if (tskno_DetectCalledTask != 0xFFFF) {
						del_tsk(&tskno_DetectCalledTask);
					}
					/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
					tskno_DetectCalledTask 						= 0xFFFF;
					cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
					SYS_RingCounter = 0; /* 着信拒否処理の追加に伴い、呼出音停止後の転送受信をここで防止。 by H.Kubo 1999/02/26 */
				}
#else /* !defined (KEISATSU) */
				SYS_RingCounter = 0; /* 着信拒否処理の追加に伴い、呼出音停止後の転送受信をここで防止。 by H.Kubo 1999/02/26 */
#endif /* defined (KEISATSU) */
				TxNCUTaskMsg.Message = MSG_NCU_RESTART;
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
				/*---------------------------------------*/
				/** 待機状態時回線監視モジュール終了処理 */
				/*---------------------------------------*/
				NCUTaskExit();

				break;
			case DETECT_TEL1_ONHOOK:
				NCUStatus	&= ~TELEPHONE1_OFF_HOOK;
				if(!( Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){ /* added by H.Kubo 1998/11/23 */
					Tel1OhCounter			= 40;
				}
				TxNCUTaskMsg.Message = OK_CONT;
				snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxNCUTaskMsg.Message);
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/21 */
				if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) != STD_READY) {
					/* 秘話機能起動した場合 */
					SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
					SYS_LineTelStatus |= STD_READY;
				}
				H_RelayOff();
				SYS_RingCounter = 0;
				TxNCUTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT;
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
#endif /* defined (KEISATSU) */
				break;
			case DETECT_TEL2_ONHOOK:
				NCUStatus	&= ~TELEPHONE2_OFF_HOOK;
				if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){  /* added by H.Kubo 1998/11/23 */
					Tel2OhCounter			= 40;
				}
				TxNCUTaskMsg.Message = OK_CONT;
				snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxNCUTaskMsg.Message);
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/21 */
				if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) != EXT_READY) {
					/* 秘話機能起動した場合 */
					SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
					SYS_LineTelStatus |= EXT_READY;
				}
				L_RelayOff();
				SYS_RingCounterExt = 0;
				TxNCUTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_TEL2;
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
#endif /* defined (KEISATSU) */
				break;
			case DETECT_CALLED_REQUEST_ND: /* ND でメモリーオーバーで着信拒否を考慮。Added by H.Kubo 1999/02/26 */ 
				TxNCUTaskMsg.Message = MSG_DETECT_CALLED_REQUEST_ND;
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg); /* 着信してもいいかどうかのメッセージ待ち */
				/* Added by H.Kubo 1999/03/18 */
				if (tskno_NCU_ND_Rx != 0xFFFF) { /* ND 制御終了。added by H.Kubo 1999/03/18 */
					del_tsk(&tskno_NCU_ND_Rx);
				}
				if (RxNCUTaskMsg->Message == MSG_EXIT) { /* 着信 */
					NCU_ND_SetCallDetectedStatus();
					NCUStatus |=  DETECT_CALL;
					NCUTaskExit();
				}
				else { /* 着信不可 */
					TxNCUTaskMsg.Message = OK_CONT;
					snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
				}
				break;
#endif
													/*-----------------------------*/
			case	DETECT_CALLED_REQUEST		:	/**       着信検出の場合       */
			case	DETECT_F_NET_CALLED_SIGNAL	:	/** Ｆ網(1300Hz)着信検出の場合 */
													/*-----------------------------*/
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/15 */
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/08 */
				if (DEBUG_NumberDisplay) {
					if (SYS_LineNDStatus == ND_USED_IN_STD) {
						NCU_ND_SetCallDetectedStatus();
					}
				}
				else {
					NCU_ND_InitializeStatus();
				}
#else /* defined (KEISATSU) */
				NCU_ND_SetCallDetectedStatus();
#endif /* defined (KEISATSU) */
#endif
				NCUStatus |=  DETECT_CALL;
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/12 */
				if (RxNCUTaskMsg->Item == FROM__NCU_RING) {
					TxNCUTaskMsg.Message = OK_CONT;
					snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
				}
 #endif /* defined (KEISATSU) */
				/*---------------------------------*/
				/** メイン・タスクへ着信検出を通知 */
				/*---------------------------------*/
				if( DETECT_CALLED_REQUEST == RxNCUTaskMsg->Message ){
					TxNCUTaskMsg.Message = MSG_DETECT_CALL_TO_FAX;
				}
				else{
					TxNCUTaskMsg.Message = MSG_DETECT_F_NET;
#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
					if (CHK_DisasterPreventionFaxEnable()) {
						if (SYS_MemorySwitch[MEMORY_SW_D8]) {	/* SYS_MemorySwitch[MEMORY_SW_D8] */
							FaxTimer((UWORD)SYS_MemorySwitch[MEMORY_SW_D8] * 10);
						}
						else {
							FaxTimer(200);
						}
					}
					else {
							FaxTimer(200);
					}
#endif	/* End of (PRO_DISASTER_PREVENTION_FAX == ENABLE) */
				}
#if (0) /* (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103) @* added by H.Hirao 1998/12/26 comment by H.Hirao 1998/12/28 */
**				if ((SYS_DualRestrictionStatus & 0x02) != 0x02) {	/* 原稿蓄積中でなければ */
**					snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
**					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
**					/*---------------------------------------*/
**					/** 待機状態時回線監視モジュール終了処理 */
**					/*---------------------------------------*/
**					NCUTaskExit();
**				}
#else
 #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/05/11 added (PRO_CLASS1 == ENABLE) 1999/05/28 */
				if (RxNCUTaskMsg->Message == DETECT_F_NET_CALLED_SIGNAL) {
					snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
					NCUTaskExit();
				}
				else {
					if ((CL1_CheckReceiveByFaxOrPC() != NO_RECEIVING_SCANNER_IN_USE)
					 && (CL1_CheckReceiveByFaxOrPC() != NO_RECEIVING_PRINTER_IN_USE)) {
						snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
						rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
						NCUTaskExit();
					}
				}
 #else
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
				/*---------------------------------------*/
				/** 待機状態時回線監視モジュール終了処理 */
				/*---------------------------------------*/
				NCUTaskExit();
 #endif
#endif
				break;
													/*---------------------------------------*/
			case    DETECT_TEL1_OFF_HOOK		:	/** 付属電話の    ＯＦＦ　ＨＯＯＫを検出 */
			case    DETECT_TEL2_OFF_HOOK		:	/** 外付電話の    ＯＦＦ　ＨＯＯＫを検出 */
			case    DETECT_INPUT_HOOK_KEY		:	/** 回線補足キー　ＯＮ            を検出 */
													/*---------------------------------------*/
#if (PRO_ECO_MODE == ENABLE) /* 2002/09/25 By M.Maeda */
				MAN_ChangeEcoMode(0);
#endif
#if defined (KEISATSU) /* 警察FAX Modified by SMuratec 李 2005/09/02 */
				/*-----------------------------------------------------*/
				/** 着信検出とＨＯＯＫ状態変化検出の同時発生の際の調整 */
				/*-----------------------------------------------------*/
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

#if 0 /* 警察FAX DVT_ID18&25&26 Modify by SMuratec 李 2005/11/12 */
@@				if(!SYS_RingCounter){
@@#if 0	/* 警察FAX (ナンバーディスプレイ) Deleted by SMuratec 李 2005/10/24 */
@@@					if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) {
@@@					}
@@#else
@@					if (DEBUG_NumberDisplay && (SYS_LineNDStatus == ND_USED_IN_STD)
@@						&& (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE))) {
@@					}
@@					else if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) {
@@					}
@@#endif
@@					else {
@@						if (RingStatus & CI_EXT_LINE) { /**	CI検出状態が拡張ラインの場合	*/
@@							if(( RingingOnTime2nd   >= comp_min_on_time )
@@							|| ( SamplingBuff2nd[0] >= comp_min_on_time )){
@@								SYS_RingCounter++;
@@							}
@@						}
@@						else {
@@							if(( RingingOnTime   >= comp_min_on_time )
@@							|| ( SamplingBuff[0] >= comp_min_on_time )){
@@								SYS_RingCounter++;
@@							}
@@						}
@@					}
@@				}
@@				if(!SYS_RingCounterExt){
@@#if 0	/* 警察FAX (ナンバーディスプレイ) Deleted by SMuratec 李 2005/10/24 */
@@@					if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) {
@@@					}
@@#else
@@					if (DEBUG_NumberDisplay && (SYS_LineNDStatus == ND_USED_IN_EXT)
@@						&& (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE))) {
@@					}
@@					else if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) {
@@					}
@@#endif
@@					else{
@@						if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
@@		  					if(( RingingOnTime2nd   >= comp_min_on_time )
@@							|| ( SamplingBuff2nd[0] >= comp_min_on_time )){
@@								SYS_RingCounterExt++;
@@							}
@@						}
@@						else {
@@		  					if(( RingingOnTime   >= comp_min_on_time )
@@							|| ( SamplingBuff[0] >= comp_min_on_time )){
@@								SYS_RingCounterExt++;
@@							}
@@						}
@@					}
@@				}
#else
				if (((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_TRANSMIT)
					|| ((DETECT_INPUT_HOOK_KEY == RxNCUTaskMsg->Message)
					&& CHK_LineSetting())) {
					if(!SYS_RingCounter){
						if (DEBUG_NumberDisplay && (SYS_LineNDStatus == ND_USED_IN_STD)
							&& (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE))) {
						}
						else if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) {
						}
						else {
							if (RingStatus & CI_STD_LINE) { /**	CI検出状態が拡張ラインの場合	*/
								if(( RingingOnTime   >= comp_min_on_time )
								|| ( SamplingBuff[0] >= comp_min_on_time )){
									SYS_RingCounter++;
									if ((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_TRANSMIT) {
										NCU_LineStatus &= ~STD_LINE_STATUS;
										NCU_LineStatus |= (STD_LINE_STATUS & STD_TEL_RECEIVE);
									}
								}
							}
						}
					}
				}
				if (((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT)
					|| ((DETECT_INPUT_HOOK_KEY == RxNCUTaskMsg->Message)
					&& !CHK_LineSetting())) {
					if(!SYS_RingCounterExt){
						if (DEBUG_NumberDisplay && (SYS_LineNDStatus == ND_USED_IN_EXT)
							&& (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE))) {
						}
						else if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) {
						}
						else{
							if (RingStatus2nd & CI_EXT_LINE) {	/**	CI検出状態が標準ラインの場合	*/
			  					if(( RingingOnTime2nd   >= comp_min_on_time )
								|| ( SamplingBuff2nd[0] >= comp_min_on_time )){
									SYS_RingCounterExt++;
									if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT) {
										NCU_LineStatus &= ~EXT_LINE_STATUS;
										NCU_LineStatus |= (EXT_LINE_STATUS & EXT_TEL_RECEIVE);
									}
								}
							}
						}
					}
				}
#endif
#else /* defined (KEISATSU) */
				/*-----------------------------------------------------*/
				/** 着信検出とＨＯＯＫ状態変化検出の同時発生の際の調整 */
				/*-----------------------------------------------------*/
				if(!SYS_RingCounter){
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

#if (PRO_NUMBER_DISPLAY == ENABLE) /* by H.Kubo 1998/11/26 */
					if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) {
					}
					else
#endif

#if (0) /* 1999/12/06 by K.Okada */
//					if(( RingingOnTime   >= CTRY_RingTable()->MinOnTime )
//					|| ( SamplingBuff[0] >= CTRY_RingTable()->MinOnTime )){
//						SYS_RingCounter++;
//					}
#else
					if(( RingingOnTime   >= comp_min_on_time )
					|| ( SamplingBuff[0] >= comp_min_on_time )){
						SYS_RingCounter++;
					}
#endif
				}
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
				if(!SYS_RingCounterExt){
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* by H.Kubo 1998/11/26 */
					if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) {
					}
					else
 #endif
  #if (0) /* 1999/12/06 by K.Okada */
//					if(( RingingOnTime   >= CTRY_RingTable()->MinOnTime )
//					|| ( SamplingBuff[0] >= CTRY_RingTable()->MinOnTime )){
//						SYS_RingCounterExt++;
//					}
  #else
  					if(( RingingOnTime   >= comp_min_on_time )
					|| ( SamplingBuff[0] >= comp_min_on_time )){
   #if (0) /* 拡張回線のリングカウンターをインクリメントしなければならない 多分手がすべってしまったのかOkada君 */
   **					SYS_RingCounter++;
   #else
						SYS_RingCounterExt++;
   #endif
					}
  #endif
  
				}
#endif
#endif /* defined (KEISATSU) */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 着信状態へ遷移 added by H.Kubo 1998/10/15 */
				/* モデムダイヤルイン TEL1, TEL2 の処理 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
				if (((DETECT_TEL1_OFF_HOOK == RxNCUTaskMsg->Message)
					&& (SYS_LineNDStatus == ND_USED_IN_EXT))
					|| ((DETECT_TEL2_OFF_HOOK == RxNCUTaskMsg->Message)
					&& (SYS_LineNDStatus == ND_USED_IN_STD))) {
				}
				else if ((DETECT_INPUT_HOOK_KEY == RxNCUTaskMsg->Message)
						&& ((CHK_LineSetting() && (SYS_LineNDStatus == ND_USED_IN_EXT))
						|| (!CHK_LineSetting() && (SYS_LineNDStatus == ND_USED_IN_STD)))) {
				}
				else
 #endif /* defined (KEISATSU) */
				if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CAR_DETECTED)) { /*  | ND_WAIT_FOR_2ND_RING | ND_DETECT_CI_AFTER_RX_RES is deleted by H.Kubo 1998/11/14 */
#if 1  /* 試験中 */ /* addded by H.Kubo 1998/11/21 */
					if( DETECT_TEL1_OFF_HOOK == RxNCUTaskMsg->Message ){
						NCUStatus			|= TELEPHONE1_OFF_HOOK;
						if(!( Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){
							Tel1OhCounter			= 40;
						}
					}
					else if( DETECT_TEL2_OFF_HOOK == RxNCUTaskMsg->Message ){
						NCUStatus        |=  TELEPHONE2_OFF_HOOK;
						if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){
							Tel2OhCounter			= 40;
						}
					}
					else{
						if( DETECT_INPUT_HOOK_KEY == RxNCUTaskMsg->Message ){
							if (NCUStatus & HOOK_KEY_ON_STATE) {
								NCUStatus        &= ~HOOK_KEY_ON_STATE;
							}
							else {
								NCUStatus        |= HOOK_KEY_ON_STATE;
							}
						}
					}
#endif
					TxNCUTaskMsg.Message = OK_CONT;
					if (RxNCUTaskMsg->Item == FROM__NCU_SUB) { /* if is added by H.Kubo 1998/11/21 */
						snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxNCUTaskMsg.Message);
					}
					else {
						snd_msg(mbxno.NCU_ND, &TxNCUTaskMsg); /* なんでもいいから一つ NCU_ND_RxProcedureTask にメッセージをほる。*/
					}
					break;
				}
				/* else if (NCU_ModemDialinHandsetBehavior() && (NCU_ND_Status & ND_MODEM_DIALIN_DIAL)) { */ /* Changed by H.Kubo 1998/11/12 */
				else if (NCU_ModemDialinHandsetBehavior() && (NCU_ND_Status & ( ND_MODEM_DIALIN_TEL1_DIAL | ND_MODEM_DIALIN_TEL2_DIAL ))) {
					if ((RxNCUTaskMsg->Message == DETECT_TEL1_OFF_HOOK)
					||   (RxNCUTaskMsg->Message == DETECT_INPUT_HOOK_KEY)) {
						if (RxNCUTaskMsg->Message == DETECT_TEL1_OFF_HOOK) {
							NCUStatus			|= TELEPHONE1_OFF_HOOK;
						}
						else  {
							AfterCI_HL_RelayOn = 10; /* Hook key を無視するときは、CI 検出のために短くします。 */
						}
						if (!(NCU_ND_Status & ND_MODEM_DIALIN_TEL1_DIAL)) {
							TxNCUTaskMsg.Message = OK_CONT;
							if (RxNCUTaskMsg->Item == FROM__NCU_SUB) { /* if is added by H.Kubo 1998/11/21 */
								if(!( Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){ /* added by H.Kubo 1998/11/23 */
									Tel1OhCounter			= 40;
								}
								snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxNCUTaskMsg.Message);
							}
							else {
								snd_msg(mbxno.NCU_ND, &TxNCUTaskMsg); /* なんでもいいから一つ NCU_ND_RxProcedureTask にメッセージをほる。*/
							}
							break;
						}
					}
					if (RxNCUTaskMsg->Message == DETECT_TEL2_OFF_HOOK) {
						if (!(NCU_ND_Status & ND_MODEM_DIALIN_TEL2_DIAL)) {
							NCUStatus        |=  TELEPHONE2_OFF_HOOK;
							TxNCUTaskMsg.Message = OK_CONT;
							if (RxNCUTaskMsg->Item == FROM__NCU_SUB) { /* if is added by H.Kubo 1998/11/21 */
								if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){ /* added by H.Kubo 1998/11/23 */
									Tel2OhCounter			= 40;
								}
								snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxNCUTaskMsg.Message);
							}
							else {
								snd_msg(mbxno.NCU_ND, &TxNCUTaskMsg); /* なんでもいいから一つ NCU_ND_RxProcedureTask にメッセージをほる。*/
							}
							break;
						}
					}
				}
				else if (NCU_ND_Status & ND_MODEM_DIALIN_FAX_DIAL) { /* added by H.Kubo 1998/11/12 */
					TxNCUTaskMsg.Message = OK_CONT;
					if (RxNCUTaskMsg->Item == FROM__NCU_SUB) { /* if is added by H.Kubo 1998/11/21 */
						if(!( Tel1OhCounter = Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){ /* added by H.Kubo 1998/11/23 */
							Tel1OhCounter			= 40;
							Tel2OhCounter			= 40;
						}
						snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxNCUTaskMsg.Message);
					}
					else {
						snd_msg(mbxno.NCU_ND, &TxNCUTaskMsg); /* なんでもいいから一つ NCU_ND_RxProcedureTask にメッセージをほる。*/
					}
 #if 0 /* モデムダイヤルインで着信できない時は、受話器やフックキーで回線をつかみます by H.Kubo 1999/02/26 */
					break;
 #else
					if (!(NCU_ND_Status & ND_COUNTING_2ND_RING)) {
						break;
					}
 #endif
				}
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
				if (DEBUG_NumberDisplay) {
					NCU_ND_SetCallDetectedStatus();
				}
 #else /* !defined (KEISATSU) */
				NCU_ND_SetCallDetectedStatus();
 #endif /* defined (KEISATSU) */
#endif
				/*---------------------------------------------*/
				/** メイン・タスクへＨＯＯＫ状態変化情報を通知 */
				/*---------------------------------------------*/
				if( DETECT_TEL1_OFF_HOOK == RxNCUTaskMsg->Message ){
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
					if (SYS_LineNDStatus == ND_USED_IN_STD) {
						if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
							del_tsk(&tskno_NCU_ND_Rx);
						}
						NCU_ND_InitializeStatus();
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
					}
 #endif /* defined (KEISATSU) */
					NCUStatus			|= TELEPHONE1_OFF_HOOK;
					TxNCUTaskMsg.Message	 = MSG_DETECT_TEL1_OFF_HOOK;
				}
				else{
					if( DETECT_TEL2_OFF_HOOK == RxNCUTaskMsg->Message ){
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
					if (SYS_LineNDStatus == ND_USED_IN_EXT) {
						if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
							del_tsk(&tskno_NCU_ND_Rx);
						}
						NCU_ND_InitializeStatus();
	 					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
					}
 #endif /* defined (KEISATSU) */
						NCUStatus        |=  TELEPHONE2_OFF_HOOK;
						TxNCUTaskMsg.Message  = MSG_DETECT_TEL2_OFF_HOOK;
					}
					else{
						if( DETECT_INPUT_HOOK_KEY == RxNCUTaskMsg->Message ){
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/31 */
							if (CHK_LineSetting() && /* 回線設定 == 標準回線 */
 #if 0 /* 警察FAX QAT対応 Modified by SMuratec 李 2005/12/08 */
@@								(SYS_LineNDStatus == ND_USED_IN_EXT)) {
 #else
								(SYS_LineNDStatus == ND_USED_IN_STD)) {
 #endif
								if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
									del_tsk(&tskno_NCU_ND_Rx);
								}
								NCU_ND_InitializeStatus();
							}
							else if (!CHK_LineSetting() && /* 回線設定 == 拡張回線 */
 #if 0 /* 警察FAX QAT対応 Modified by SMuratec 李 2005/12/08 */
@@								(SYS_LineNDStatus == ND_USED_IN_STD)) {
 #else
								(SYS_LineNDStatus == ND_USED_IN_EXT)) {
 #endif
								if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
									del_tsk(&tskno_NCU_ND_Rx);
								}
								NCU_ND_InitializeStatus();
							}
 #endif /* defined (KEISATSU) */
							NCUStatus        |= HOOK_KEY_ON_STATE;
							TxNCUTaskMsg.Message  = MSG_DETECT_INPUT_HOOK_KEY;
						}
					}
				}
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
				/*---------------------------------------*/
				/** 待機状態時回線監視モジュール終了処理 */
				/*---------------------------------------*/
				NCUTaskExit();

				break;

#if (PRO_CLASS1 == ENABLE) || (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By Y.Tanimoto 96.04.08 */ /* ND by H.Kubo 1998/10/21 */
													/*-----------------*/
			case	DETECT_RING			:			/** １波検出の場合 */
													/*-----------------*/
#if (PRO_NUMBER_DISPLAY == ENABLE) /* by H.Kubo 1998/11/27 */
				if (NCU_ND_ShuldSwitchToDialin()) { /* モデムダィヤルイン設定で IR が来た時、ダイヤルイン着信するか。added by H.Kubo 1998/11/27 */
					CMN_DisableInterrupt();
					NCUStatus |=  DETECT_CALL;
					SYB_ND_CarPattern[SYS_ND_LAST_NCU_ND_STATUS] = NCU_ND_Status;
					NCU_ND_Status |= ND_CALL_ACCEPTED;
					SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
					CMN_EnableInterrupt();
					/*---------------------------------*/
					/** メイン・タスクへ着信検出を通知 */
					/*---------------------------------*/
					TxNCUTaskMsg.Message = MSG_DETECT_CALL_TO_FAX;
					snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
					rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
					/*---------------------------------------*/
					/** 待機状態時回線監視モジュール終了処理 */
					/*---------------------------------------*/
					NCUTaskExit();
					break;
				}
#endif
				TxNCUTaskMsg.Message = OK_CONT;
				snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* by H.Kubo 1998/10/21 */
				CMN_DisableInterrupt();
				if (NCU_ND_Status & ND_CAR_DETECTED) { /* added by H.Kubo 1998/10/23 */
					NCU_ND_Status |= ND_COUNTING_2ND_RING;
					NCU_ND_Status &= ~(ND_BEFORE_INFO_RECEIVED | ND_WAIT_FOR_2ND_RING | ND_DETECT_CI_AFTER_RX_RES);
					NCU_ND_Status &= ~ND_MODEM_DIALIN_DIAL; /* by H.Kubo 1998/10/26 */
				}
				else if (NCU_ND_Status & ND_WAIT_FOR_IR) { /* CAR 待ちで IR が来た時の処理。 added by H.Kubo 1998/10/26 */
					NCU_ND_Status |= ND_COUNTING_2ND_RING;
					NCU_ND_Status &= ~(ND_BEFORE_INFO_RECEIVED);
					NCU_ND_Status &= ~ND_MODEM_DIALIN_DIAL; /* by H.Kubo 1998/10/26 */
				}
				CMN_EnableInterrupt();
				NCU_ND_AfterNdRxRelaySetting();
#endif
#if (PRO_CLASS1 == ENABLE)	/* Add By Y.Tanimoto 96.04.08 */
				/*---------------------------------------*/
				/** メイン・タスクへ通知（発着衝突回避） */
				/*---------------------------------------*/
				TxNCUTaskMsg.Message = MSG_DETECT_RING;
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);

#endif
#if (PRO_CLASS1 == ENABLE) || (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By Y.Tanimoto 96.04.08 */ /* ND by H.Kubo 1998/10/21 */
				break;
#endif
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
			case	IGNORE_RING:
				TxNCUTaskMsg.Message = OK_CONT;
				snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
				/*---------------------------------------*/
				/** メイン・タスクへ通知（発着衝突回避） */
				/*---------------------------------------*/
				TxNCUTaskMsg.Message = MSG_DETECT_CI;
				snd_msg(mbxno.MAN_Task, &TxNCUTaskMsg);
				rcv_msg(mbxno.NCU_TaskSub, &RxNCUTaskMsg);
				break;
 #endif /* PRO_CL1_TELFAX_LAN == ENABLE */

			default:

				break;
		}
	}
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[待機状態時回線監視モジュール終了処理ルーチン]
	function	:[
		1.待機状態時回線監視モジュール・メインにて起動した子タスクを強制終了する。
	]
	return		:[なし]
	common		:[
		NCUStatus					:回線監視モジュール動作状態を記憶
		SYS_HookKeyInputFlag		:回線捕捉キー入力情報
		HookKeyInputFlag 			:回線捕捉キー入力同期フラグ
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		NCUTaskExit( void )
{
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
	MESSAGE_t    			*RxNCUTaskMsg;

	/*---------------------------*/
	/** 回線監視使用変数の初期化 */
	/*---------------------------*/
	TxNCUTaskMsg.Item   			 			 = FROM_NCU_TASK;
#endif /* defined (KEISATSU) */
	/*---------------------*/
	/** 子タスクの強制終了 */
	/*---------------------*/
	if (tskno_TelephoneHookCheckTask != 0xFFFF) {
		del_tsk(&tskno_TelephoneHookCheckTask);
	}
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/14 */
	/* ここではない */
	if (IsCiSndMsg == TRUE) {
		rcv_msg(mbxno.NCU_Task, &RxNCUTaskMsg);
		TxNCUTaskMsg.Message = OK_CONT;
		snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
	}
	/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
	if (DEBUG_NumberDisplay) {
		if (IsNDSndMsg == TRUE) {
			IsNDSndMsg = FALSE;
			rcv_msg(mbxno.NCU_Task, &RxNCUTaskMsg);
		}
	}
 #else /* defined (KEISATSU) */
	if (tskno_DetectCalledTask != 0xFFFF) {
		del_tsk(&tskno_DetectCalledTask);
	}
 #endif /* defined (KEISATSU) */
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* Class1 F網対応  S.Fukui Jun 19,1998 (ICHOU より) */
	if (tskno_DetectFnetTimerTask != 0xFFFF) {
		del_tsk(&tskno_DetectFnetTimerTask);
	}
#endif
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
	if (tskno_CI_TimerTask != 0xffff) {
		del_tsk(&tskno_CI_TimerTask);
	}
#endif

	/*------------------------------------------------------*/
	/** HOOK KEY 入力のオペレーションとの同期フラグのクリア */
	/*------------------------------------------------------*/
	SYS_HookKeyInputFlag	= 0;
	HookKeyInputFlag 		= 0;
	/*-------------------------------------*/
	/** 回線監視モジュール状態変数のセット */
	/*-------------------------------------*/
	NCUStatus &= ~DETECT_CI_STATE;
	/*----------------*/
	/* 自タスクの終了 */
	/*----------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
	tskno_NCU_Task = 0xffff;
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/12 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Deleted by SMuratec 李 2005/10/30 */
 	if (!DEBUG_NumberDisplay) {
		if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
			del_tsk(&tskno_NCU_ND_Rx);
		}
	}
 #else /* defined (KEISATSU) */
	if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
		del_tsk(&tskno_NCU_ND_Rx);
	}
 #endif /* defined (KEISATSU) */
#endif
	exi_tsk();
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[NCU_Task強制終了処理ルーチン]
	function	:[
		1.待機状態時回線監視モジュール・メインの強制終了処理
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
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void        NCU_TaskExit( void )
{
	/*-----------------*/
	/** 子タスクの削除 */
	/*-----------------*/
	NCUTaskExit();
}


#if (PRO_NUMBER_DISPLAY == ENABLE)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[NCU_Task の子タスク強制終了処理]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/08/21]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void NCU_TaskKillChildTasks(void)
{
	/*---------------------*/
	/** 子タスクの強制終了 */
	/*---------------------*/
#if 0 /* OH 監視タスクは起動したままにします。 Deleted by H.Kubo 1998/10/22 */
	 /* AfterCI_HL_RelayOn を減らすため。HOOK 監視タスクは立ちあげます。 H.Kubo 1998/10/15 */
	if (tskno_TelephoneHookCheckTask != 0xFFFF) {
		del_tsk(&tskno_TelephoneHookCheckTask);
	}
#endif
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
	if (DEBUG_NumberDisplay) {
		if (SYS_LineNDStatus == ND_USED_IN_STD) {
			if (tskno_DetectCalledTask != 0xFFFF) {
				del_tsk(&tskno_DetectCalledTask);
			}
		}
		else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
			if (tskno_Detect2ndCalledTask != 0xFFFF) {
				del_tsk(&tskno_Detect2ndCalledTask);
			}
		}
	}
	else {
		if (tskno_DetectCalledTask != 0xFFFF) {
			del_tsk(&tskno_DetectCalledTask);
		}
	}
#else /* !defined (KEISATSU) */
	if (tskno_DetectCalledTask != 0xFFFF) {
		del_tsk(&tskno_DetectCalledTask);
	}
#endif /* defined (KEISATSU) */
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* Class1 F網対応  S.Fukui Jun 19,1998 (ICHOU より) */
	if (tskno_DetectFnetTimerTask != 0xFFFF) {
		del_tsk(&tskno_DetectFnetTimerTask);
	}
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/12 */
	if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
		del_tsk(&tskno_NCU_ND_Rx);
	}
#endif
	/*------------------------------------------------------*/
	/** HOOK KEY 入力のオペレーションとの同期フラグのクリア */
	/*------------------------------------------------------*/
	SYS_HookKeyInputFlag	= 0;
	HookKeyInputFlag 		= 0;

}
#endif
