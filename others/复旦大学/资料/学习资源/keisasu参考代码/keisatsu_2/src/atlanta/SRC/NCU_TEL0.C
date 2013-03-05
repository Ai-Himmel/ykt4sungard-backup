/**********************************************************************
* ANZU
*
*	 File	Name:  NCU_TEL0.C
*	 Coded	  by:  坂本直史
*	 Module Name:  NCU_TelephoneOperationTask()
*				   TelephoneOperationTaskExit()
*				   NCU_TelephoneExecuteTask()
*
*	 Note		:  多機能電話制御
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
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\stng_pro.h"

#include "\src\atlanta\define\ncu_pro.h"
#include "\src\atlanta\define\ncu_stat.h"
#include "\src\atlanta\define\ncu_msg.h"
#include "\src\atlanta\define\ncu_ret.h"
#include "\src\atlanta\define\ncu_cnst.h"
#include "\src\atlanta\define\ncu_def.h"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\define\cl1_def.h"
#endif
#include "\src\atlanta\define\ctry_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\atd_data.h"
#include "\src\atlanta\ext_v\ncu_data.h"
#include "\src\atlanta\ext_v\ncu_tbl.h"
#include "\src\atlanta\ext_v\man_data.h"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\cl1_data.h"
#endif

#if (PRO_MODEM == ORANGE3) /* added by H.Kubo 1997/07/23 */
#include "\src\atlanta\mdm\orange\define\mdm_pro.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/07/23 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
 #else
#include "\src\atlanta\mdm\r288F\define\mdm_pro.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#endif

#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\sh7043\define\def_tib.h"

#if (PRO_LINENUMBER == TWICE_LINE)/* V851 By Y.Suzuki 2002/08/22*/
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\ext_v\sys_data.h"
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/07 */
#include	"\src\atlanta\define\sys_line.h"

extern UWORD	tskno_NCU_ND_Rx;
#endif /* defined (KEISATSU) */

static UWORD tskno_TelephoneExecuteTask		= 0xFFFF;
static UWORD tskno_TelephoneHookCheckTask	= 0xFFFF;
static UWORD tskno_FaxTadAutoSwitchTask		= 0xFFFF;
#if (PRO_REMOTE_RX == ENABLE) || (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* 1998/01/24  By T.Yamaguchi */ /* REMOTE_RX_FUNC */
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/17 */
UWORD tskno_RemoteRxSignalDetTask	= 0xFFFF;	/* 1998/01/24  By T.Yamaguchi */
 #else /* defined (KEISATSU) */
static UWORD tskno_RemoteRxSignalDetTask	= 0xFFFF;	/* 1998/01/24  By T.Yamaguchi */
 #endif /* defined (KEISATSU) */
#endif
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[多機能電話制御タスク]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		必ず入力してください
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	   NCU_TelephoneOperationTask( void )
{
	MESSAGE_t				*RxTelephoneOperationTaskMsg;
	
#if defined (KEISATSU) /* 警察FAX DVT_ID18&25&26 Added by SMuratec 李 2005/11/14 */
	UWORD					comp_min_on_time;	/* 1999/12/06 by K.Okada */
#endif /* defined (KEISATSU) */
	/*-------------------*/
	/** 使用変数の初期化 */
	/*-------------------*/
	TxTelephoneOperationTaskMsg.Item			 = FROM_NCU_TELEPHONEOPERATIONTASK;
	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS]	&= ~SYS_STOP_TELEPHONE;
	SYS_HookKeyInputFlag						 = 0;
	SYS_HoldKeyInputFlag						 = 0;
	SYS_DialChange								 = 0;
	HookKeyInputFlag							 = 0;
	HoldKeyInputFlag							 = 0;
	NumberKeyInputFlag							 = 0;
	PIN_NumberRedialProtectFlag					 = 0;		/* '96,03,07 By N.S. for ANZU PIN Operation */
	TADStatus									 = 0;
	tskno_TelephoneExecuteTask					 = 0xFFFF;
	tskno_TelephoneHookCheckTask				 = 0xFFFF;
	tskno_FaxTadAutoSwitchTask					 = 0xFFFF;
	tskno_ad_lc_timeup							 = 0xFFFF;
	tskno_ad_loop_current						 = 0xFFFF;
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* 1996/07/04 By N.Sakamot For Mercury *//* by K.Watanabe 2004/10/12 */
 #if (PRO_MODEM == ORANGE3)
	tskno_ATD_freq_check						 = 0xFFFF;
 #endif
#endif
#if (PRO_REMOTE_RX == ENABLE) || (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* 1998/01/24  By T.Yamaguchi */ /* REMOTE_RX_FUNC */	/* 1998/01/24  By T.Yamaguchi */
	tskno_RemoteRxSignalDetTask	= 0xFFFF;
#endif
	/*---------------------------------------------*/
	/** 多機能電話タスク起動時のＦＡＸ設定条件保持 */
	/*---------------------------------------------*/
	NCU_RxModeSwitch = CMN_PresentReceiveMode();

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/27 */
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/14 */
	IsDailing = FALSE;
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
	cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_TelephoneOperationTask));
 #endif /* defined (KEISATSU) */
#endif
				/*-----------------------------------*/
	while(1){	/** 多機能電話機能が全て終了するまで */
				/*-----------------------------------*/
		/*-------------------*/
		/** 事象の待ち合わせ */
		/*-------------------*/
		rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
													/*-----------------------*/
		switch(RxTelephoneOperationTaskMsg->Item){	/** 発生事象に対する処理 */
													/*-----------------------*/
												/*-------------------------------------*/
			case FROM_MAIN				:		/** ＭＡＩＮ　タスク  からのメッセージ */
												/*-------------------------------------*/
																/*-----------------------*/
				switch(RxTelephoneOperationTaskMsg->Message){	/** 発生事象に対する処理 */
																/*-----------------------*/
																/*-----------------------*/
					case	 MSG_TELEPHONE_OPERATION		:	/** 狭義の多機能電話機能 */
						/*---------------------------------*/	/*-----------------------*/
						/** 転送受信許容時間タイマーセット */
						/*---------------------------------*/
						TransferReceiveAvailableTime = 0;	/* CHK_OnhookTransferTime() * 100;	'96,04,16 By N.S.MEM_SW整理 */
						TransferReceiveFlag	 = 1;
						NCUStatus &= ~(DETECT_CALL | TRANSFER_RECIVE | BRANCH_TRNS_RCV);
						if( NCUStatus & HOOK_KEY_ON_STATE ){		/** 回線補足キーがＯＮ状態の場合  */
							/*------------------------------------------------------------------------*/
							/** 回線補足キーによる回線補足の為のリレー制御 */
							/*---------------------------------------------*/
							HookKeyOnRelayControl();
#if defined(EC1)	/* '98/04/9 M.H. HookKey timer for BEL */
							if (SYB_MachineParameter[0] == 0) {		/* BEL */
								HookKeyTimer		 = 8000;		/* 80sec */
							}
#endif
						}
						else{											/*------------------------------------*/
							if( NCUStatus & TELEPHONE1_OFF_HOOK ){		/** 付属電話がＯＦＦ　ＨＯＯＫの場合  */
																		/*------------------------------------*/
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)	/* ＴＥＬ１とＴＥＬ２のＯＨを区別する場合 1997/11/08  By T.Yamaguchi */
								/*-----------------------------*/
								/**			 秘話機能 		   */
								/*-----------------------------*/
								TelIndependentRelayControl();
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/14 */
								if (SYS_RingCounter && NCU_RemoteTransferDial()) {
									/*-----------------------------------------*/
									/**		リモート受信信号検出準備		   */
									/*-----------------------------------------*/
									/* TADStatus |= FAX_TAD_STATE; */
									tskno_RemoteRxSignalDetTask = 0xFFFF;
									cre_tsk(&tskno_RemoteRxSignalDetTask, TSK_NCU_REMOTERXSIGNALDETTASK, &(mbxno.NCU_TelephoneOperationTask));
								}
 #endif /* defined (KEISATSU) */
#else
 #if (defined(HINOKI2)&&(TWN)) /* F76(HINOKI2 TWN)ANS待機不具合 対応テスト テスト後外します。O.Oshima 2004/05/13 */
								if (!CHK_UNI_TEL2_TEL1Action()) {
									TelIndependentRelayControl();
								}
								else {
																						/*------------------------------------*/
									if(( SYS_ANS_FAX_READY == NCU_RxModeSwitch	 )		/**	  留守／ＦＡＸ待機モードの場合	  */
									&& ( SYS_RingCounter						 )){	/**		   ＣＩ検出済の場合			  */
										/*-----------------------------------------*/	/*------------------------------------*/
										/**		外付留守番電話着信／ＣＮＧ検出準備 */
										/*-----------------------------------------*/
										TADStatus |= FAX_TAD_STATE;
										tskno_FaxTadAutoSwitchTask = 0xFFFF;
										cre_tsk(&tskno_FaxTadAutoSwitchTask, TSK_NCU_FAXTADAUTOSWITCHTASK, &(mbxno.NCU_TelephoneOperationTask));
									}
									else{
										/*-----------------------------*/
										/**			 秘話機能 		   */
										/*-----------------------------*/
										TelIndependentRelayControl();
									}
								}
 #else
																					/*------------------------------------*/
								if(( SYS_ANS_FAX_READY == NCU_RxModeSwitch	 )		/**	  留守／ＦＡＸ待機モードの場合	  */
								&& ( SYS_RingCounter						 )){	/**		   ＣＩ検出済の場合			  */
									/*-----------------------------------------*/	/*------------------------------------*/
									/**		外付留守番電話着信／ＣＮＧ検出準備 */
									/*-----------------------------------------*/
									TADStatus |= FAX_TAD_STATE;
									tskno_FaxTadAutoSwitchTask = 0xFFFF;
									cre_tsk(&tskno_FaxTadAutoSwitchTask, TSK_NCU_FAXTADAUTOSWITCHTASK, &(mbxno.NCU_TelephoneOperationTask));
								}
								else{
									/*-----------------------------*/
									/**			 秘話機能 		   */
									/*-----------------------------*/
									TelIndependentRelayControl();
								}
 #endif
#endif
							}
							else{
																					/*------------------------------------*/
								if(( SYS_ANS_FAX_READY == NCU_RxModeSwitch	 )		/**	  留守／ＦＡＸ待機モードの場合	  */
								&& ( SYS_RingCounter						 )){	/**		   ＣＩ検出済の場合			  */
									/*-----------------------------------------*/	/*------------------------------------*/
									/**		外付留守番電話着信／ＣＮＧ検出準備 */
									/*-----------------------------------------*/
									if (CHK_UNI_SecretTelAnsFax()) {
										TelIndependentRelayControl();	/* 1998/03/31  By T.Yamaguchi */
									}
									TADStatus |= FAX_TAD_STATE;
									tskno_FaxTadAutoSwitchTask = 0xFFFF;
									cre_tsk(&tskno_FaxTadAutoSwitchTask, TSK_NCU_FAXTADAUTOSWITCHTASK, &(mbxno.NCU_TelephoneOperationTask));
	#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2)		/* ANS待機での55転送 移植 by SMuratec 李 2004/08/27 */
									if (NCU_RemoteTransferDial() && CHK_TAD_FaxReadyOnhookTransfer()) {
										/*-----------------------------*/
										/**			 秘話機能 		   */
										/*-----------------------------*/
										TelIndependentRelayControl();	/* 1998/03/25  By T.Yamaguchi */
										/*-----------------------------------------*/
										/**		リモート受信信号検出準備		   */
										/*-----------------------------------------*/
										/* TADStatus |= FAX_TAD_STATE; */
										tskno_RemoteRxSignalDetTask = 0xFFFF;
										cre_tsk(&tskno_RemoteRxSignalDetTask, TSK_NCU_REMOTERXSIGNALDETTASK, &(mbxno.NCU_TelephoneOperationTask));
									}
	#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
								}
#if (PRO_REMOTE_RX == ENABLE)	/* 1998/01/24  By T.Yamaguchi */
																						/*------------------------------------*/
								else if(( SYS_ANS_FAX_READY != NCU_RxModeSwitch	 )		/* 留守／ＦＡＸ待機以外のモードの場合 */
								&& ( SYS_RingCounter )									/*		   ＣＩ検出済の場合			  */
								&& ( CHK_RemoteRxON())                           ) {	/*		   リモート受信ＯＮ			  */
									/*-----------------------------*/					/*------------------------------------*/
									/**			 秘話機能 		   */
									/*-----------------------------*/
									TelIndependentRelayControl();	/* 1998/03/25  By T.Yamaguchi */
									/*-----------------------------------------*/
									/**		リモート受信信号検出準備		   */
									/*-----------------------------------------*/
									/* TADStatus |= FAX_TAD_STATE; */
									tskno_RemoteRxSignalDetTask = 0xFFFF;
									cre_tsk(&tskno_RemoteRxSignalDetTask, TSK_NCU_REMOTERXSIGNALDETTASK, &(mbxno.NCU_TelephoneOperationTask));
								}
#elif (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
	#if (PRO_MODEM == R288F)
								else if(( SYS_ANS_FAX_READY != NCU_RxModeSwitch	 )		/* 留守／ＦＡＸ待機以外のモードの場合 */
		#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 2003/02/13 */
								&& (((!CHK_Phone2ExtLineOn()) && (SYS_RingCounter)) || ((CHK_Phone2ExtLineOn()) && (SYS_RingCounterExt)))
		#else
								&& ( SYS_RingCounter )									/*		   ＣＩ検出済の場合			  */
		#endif
								&& ( NCU_RemoteTransferDial())                      ) {	/*		   リモート受信ＯＮ			  */
									/*-----------------------------*/					/*------------------------------------*/
									/**			 秘話機能 		   */
									/*-----------------------------*/
									TelIndependentRelayControl();	/* 1998/03/25  By T.Yamaguchi */
									/*-----------------------------------------*/
									/**		リモート受信信号検出準備		   */
									/*-----------------------------------------*/
									/* TADStatus |= FAX_TAD_STATE; */
									tskno_RemoteRxSignalDetTask = 0xFFFF;
									cre_tsk(&tskno_RemoteRxSignalDetTask, TSK_NCU_REMOTERXSIGNALDETTASK, &(mbxno.NCU_TelephoneOperationTask));
								}
	#endif
#endif
								else{
									/*-----------------------------*/
									/**			 秘話機能 		   */
									/*-----------------------------*/
									TelIndependentRelayControl();
								}
							}
						}
						/*-----------------------------*/
						/** 多機能電話実行タスクの起動 */
						/*-----------------------------*/
						tskno_TelephoneExecuteTask =0xFFFF;
						cre_tsk(&tskno_TelephoneExecuteTask, TSK_NCU_TELEPHONEEXECUTETASK, &(mbxno.NCU_TelephoneOperationTask));
						/*-------------------------------*/
						/** ＨＯＯＫ状態監視タスクの起動 */
						/*-------------------------------*/
						tskno_TelephoneHookCheckTask = 0xFFFF;
						cre_tsk(&tskno_TelephoneHookCheckTask, TSK_NCU_TELEPHONEHOOKCHECKTASK, &(mbxno.NCU_TelephoneOperationTask));

						break;
					default:

						break;
				}

				break;
												/*---------------------------------------------------------*/
			case	FROM__NCU_SUB		:		/** 回線監視補助タスク群（ＮＣＵ＿ＳＵＢ）からのメッセージ */
												/*---------------------------------------------------------*/
																/*-----------------------*/
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/30 */
 #if (PRO_NUMBER_DISPLAY == ENABLE)
			case	FROM_NCU_TASK		:
 #endif
 #endif /* defined (KEISATSU) */
				switch(RxTelephoneOperationTaskMsg->Message){	/** 発生事象に対する処理 */
																/*-----------------------*/
																/*-----------------------------*/
	#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
	#if (PRO_NUMBER_DISPLAY == ENABLE)
				case	DETECT_ND_OH_1ST_RESPONSE:
					if (DEBUG_NumberDisplay) {
						if (CHK_NumberDisplayByExtPhoneON() && ((NCU_ND_Status & (ND_CI_SEQUENCE_DETECTED| ND_CAR_DETECTED)))) {
							NCU_ND_SetCarDetectedStatus();
							NCU_TaskKillChildTasks();
							TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ND_CAR;
							snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
							rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							/*-----------------------------------*/
							/** ナンバーディスプレイ情報受信処理 */
							/*-----------------------------------*/
							cre_tsk(&tskno_NCU_ND_Rx, TSK_NCU_ND_RXPROCEDURETASK, &(mbxno.NCU_Task));
							snd_msg(mbxno.NCU_ND, &TxTelephoneOperationTaskMsg); /* なんでもいいから一つ NCU_ND_RxProcedureTask にメッセージをほる。*/
						}
						/*-------------------------------------------*/
						/* NCU_TelephoneHookCheckTask へメッセージ。 */
						/*-------------------------------------------*/
						TxTelephoneOperationTaskMsg.Message = OK_CONT;
						snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
					}
					break;
				case DETECT_ND_NUMBER:
					if (DEBUG_NumberDisplay) {
						snd_msg(mbxno.NCU_ND, &TxTelephoneOperationTaskMsg); /* NCU_ND_RxProcedureTask と同期を取る */
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ND_NUMBER;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
					}
					break;
				case 	MADE_ND_RX_RESPONSE:
					if (DEBUG_NumberDisplay) {
						/* cre_tsk(&tskno_TelephoneHookCheckTask, TSK_NCU_TELEPHONEHOOKCHECKTASK, &(mbxno.NCU_Task)); */
						if (tskno_DetectCalledTask == 0xFFFF) {
							cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
						}
						else if (tskno_Detect2ndCalledTask == 0xFFFF) {
							cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
						}
						/* NCU_ND_AfterNdRxRelaySetting(); */ /* NCU_ND_RxProcedureTask へ移動 by H.Kubo 1998/10/23 */
					}
					break;
				case IGNORE_ND_INFO_ARRIVAL: /* added by H.Kubo 1998/11/21 */
					if (DEBUG_NumberDisplay) {
						NCU_ND_AfterNdRxRelaySetting(); /* added by H.Kubo 1998/11/26 */
						/*---------------------------------------*/
						/** 待機状態時回線監視モジュール終了処理 */
						/*---------------------------------------*/
						if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
							del_tsk(&tskno_NCU_ND_Rx);
						}
						tskno_NCU_ND_Rx		= 0xffff;
						if (tskno_DetectCalledTask == 0xFFFF) {
							cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
						}
						else if (tskno_Detect2ndCalledTask == 0xFFFF) {
							cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
						}
						if (SYS_LineNDStatus == ND_USED_IN_STD) {
							if ((NCUStatus & TELEPHONE1_OFF_HOOK) 
								|| ((NCUStatus & HOOK_KEY_ON_STATE) && CHK_LineSetting())) { 
								if (NCUStatus & HOOK_KEY_ON_STATE) {
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_HKEY;
									snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
									rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
									/*---------------------------------------------------------------*/
									/** 多機能電話実行タスクへ回線捕捉キーが入力されたことを通知する */
									/*---------------------------------------------------------------*/
									TxTelephoneOperationTaskMsg.Message = NOTICE_INPUT_HOOK_KEY;
									snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
								}
								else if (NCUStatus & TELEPHONE1_OFF_HOOK) {
									/*-------------------------------*/
									/**		メイン・タスクへ通知	 */
									/*-------------------------------*/
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TEL1_OFF_HOOK;
									snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
									rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
									/*-------------------------------------*/
									/**		多機能電話実行タスクへ通知	   */
									/*-------------------------------------*/
									if (IsDailing) {	/* 本体ダイヤル中 */
										if (!ModemRelaySetting()){	/* モデムリレーを標準回線に接続している場合 */
											NCUStatus &= ~HOOK_KEY_ON_STATE;
											SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
											UpdateLED();
										}
									}
									else {
										TxTelephoneOperationTaskMsg.Message = NOTICE_TEL1_OFF_HOOK;
										snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
									}
								}
							}
						}
						else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
							if ((NCUStatus & TELEPHONE2_OFF_HOOK) 
								|| ((NCUStatus & HOOK_KEY_ON_STATE) && !CHK_LineSetting())) {
								if (NCUStatus & HOOK_KEY_ON_STATE) {
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_HKEY;
									snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
									rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
									/*---------------------------------------------------------------*/
									/** 多機能電話実行タスクへ回線捕捉キーが入力されたことを通知する */
									/*---------------------------------------------------------------*/
									TxTelephoneOperationTaskMsg.Message = NOTICE_INPUT_HOOK_KEY;
									snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
								}
								else if (NCUStatus & TELEPHONE2_OFF_HOOK) {
									/*-------------------------------*/
									/**		メイン・タスクへ通知	 */
									/*-------------------------------*/
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TEL2_OFF_HOOK;
									snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
									rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
									/*---------------------------------*/
									/**	  多機能電話実行タスクへ通知   */
									/*---------------------------------*/
									/*-----------------------------------------------------------
									** ＴＥＬ２もＴＥＬ１の処理に統一  By M.Tachibana 1997/09/25
									*/
									if (IsDailing) {	/* 本体ダイヤル中 */
										if (ModemRelaySetting()){	/* モデムリレーを拡張回線に接続している場合 */
											NCUStatus &= ~HOOK_KEY_ON_STATE;
											SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
											UpdateLED();
										}
									}
									else {
										TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_OFF_HOOK;
										snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
									}
								}
							}
						}
						NCU_ND_InitializeStatus();
	 					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
					}
					break;
	#endif
	#endif /* defined (KEISATSU) */
					case	DETECT_INPUT_TEL_NO				:	/** 多機能電話ダイヤル開始要求 */
						NumberKeyInputFlag = 1;					/*-----------------------------*/
						TxTelephoneOperationTaskMsg.Message = OK_CONT;
						snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
						/*-------------------------------------------*/
						/** 多機能電話実行タスクへダイヤル実行の指示 */
						/*-------------------------------------------*/
						TxTelephoneOperationTaskMsg.Message = NOTICE_INPUT_DIAL_KEY;
						snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);

						break;
																/*-------------------------------*/
					case	DETECT_INPUT_HOLD_KEY			:	/**		   保留キー入力			 */
						HoldKeyInputFlag = 1;					/*-------------------------------*/
						TxTelephoneOperationTaskMsg.Message = OK_CONT;
						snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
						/*-------------------------------*/
						/**		メイン・タスクへ通知	 */
						/*-------------------------------*/
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_INPUT_HOLD_KEY;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						/*-----------------------------------------------*/
						/** 多機能電話実行タスクへ保留キー入力検出を通知 */
						/*-----------------------------------------------*/
						TxTelephoneOperationTaskMsg.Message = NOTICE_INPUT_HOLD_KEY;
						snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						break;
																/*-------------------------*/
					case	DETECT_INPUT_STOP_KEY			:	/**		 停止キー入力	   */
																/*-------------------------*/
						if(( NCUStatus & DIALING_STATE	   )	/*-------------------------------------------------------*/
						|| ( NCUStatus & HOOK_KEY_ON_STATE )){	/** ダイヤリング状態・回線捕捉キーにて改選捕捉状態の場合 */
							NCUStatus &= ~DIALING_STATE;		/*-------------------------------------------------------*/
							/*-----------------------------------*/
							/** 多機能電話制御モジュール終了処理 */
							/*-----------------------------------*/
							TelephoneOperationTaskExit();
							/*-------------------------------*/
							/**		メイン・タスクへ通知	 */
							/*-------------------------------*/
							TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
							snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
							rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							/*-------------------------*/
							/**	  自タスク終了処理	   */
							/*-------------------------*/
							SYS_HookKeyInputFlag		 = 0;
							TransferReceiveAvailableTime = 0;
							TransferReceiveFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
#else
							SYS_RingCounter				 = 0;
#endif
							SYS_RxDetectFlag = 0;
							NumberKeyInputFlag =  0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/26 */
							tskno_NCU_TelephoneOperation = 0xffff;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
							if (IsCiSndMsg == TRUE) {
								rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
							}
							/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
							if (DEBUG_NumberDisplay) {
								if (IsNDSndMsg == TRUE) {
									IsNDSndMsg = FALSE;
									rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
								}
							}
#endif /* defined (KEISATSU) */
#endif
							exi_tsk();
						}
						else{
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
						}

						break;

																/*---------------------------------*/
					case	DETECT_TEL1_OFF_HOOK			:	/** 付属電話　ＯＦＦ　ＨＯＯＫ検出 */
																/*---------------------------------*/
#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE)
					/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 *//* SAKAKI追加 By M.Maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */

					/* 2000/01/13 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG
					 * 新Ｌ４００で、ＮＴＴファネットからの指摘項目
					 * フックキー押下してダイアルし、ダイアル送出中にＴＥＬ１を上げてさらにダイアルし、
					 * ダイアル送出中に、ＴＥＬ１を戻すとＬＣＤで電話中のまま。もう一度ＴＥＬ１を上げ下げするまで戻らない。
					 * なぜか知らんけど、旧Ｌ４００はダイアル送出しおわったらタイキに戻ったが、サカキ、ポプラは戻らない。
					 * 対策として、
					 * ここにきたときに、ダイアル中ならダイアル送出終了までウエイトしていたが、ヤメル。
					 * 単純にやめると、電話実行タスクはダイアル中で、電話実行タスクへのメッセージが届かず、
					 * ここで、snd_msg()待ちになってまうので、電話実行タスクがOFF_HOOKのメッセージを受けた時にする処理を
					 * ここでやってしまって、電話実行タスクにはメッセージは送信しないようにします。
					*/
#if defined (KEISATSU) /* 警察FAX DVT_ID18&25&26 Added by SMuratec 李 2005/11/14 */
						comp_min_on_time = NCU_CI_MinOnTime(); /* 最小ON期間を獲得 */
						if ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) {
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
												SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_STD_LINE_IN_RECEIVE; 
											}
										}
									}
								}
							}
						}
#endif
						NCUStatus |=  TELEPHONE1_OFF_HOOK;
						/*-------------------------------------*/
						/**	   ＨＯＯＫ状態監視タスクと同期	   */
						/*-------------------------------------*/
 #if defined (KEISATSU) && (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/30 */
 						if (DEBUG_NumberDisplay) {
							if (RxTelephoneOperationTaskMsg->Item == FROM__NCU_SUB) {  /* 1998/10/20 */
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
							}
							else {
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_ND, &TxTelephoneOperationTaskMsg);
							}
						}
						else {
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
						}
 #else /* !defined (KEISATSU || (PRO_NUMBER_DISPLAY != ENABLE) */
						TxTelephoneOperationTaskMsg.Message = OK_CONT;
						snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
 #endif /* defined (KEISATSU) */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/25 */
 #if (PRO_NUMBER_DISPLAY == ENABLE)
						if (DEBUG_NumberDisplay) {
	 						if ((SYS_LineNDStatus == ND_USED_IN_STD) && 
								(NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CAR_DETECTED))) {
								if(!( Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){
									Tel1OhCounter			= 40;
								}
								break;
							}
							if (SYS_LineNDStatus == ND_USED_IN_STD) {
								NCU_ND_SetCallDetectedStatus();
							}
						}
 #endif
 #endif /* defined (KEISATSU) */
						/*-------------------------------*/
						/**		メイン・タスクへ通知	 */
						/*-------------------------------*/
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TEL1_OFF_HOOK;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						/*-------------------------------------*/
						/**		多機能電話実行タスクへ通知	   */
						/*-------------------------------------*/
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/09/07 */
						if (IsDailing) {	/* 本体ダイヤル中 */
							if (!ModemRelaySetting()){	/* モデムリレーを標準回線に接続している場合 */
								NCUStatus &= ~HOOK_KEY_ON_STATE;
								SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
								UpdateLED();
							}
							/* 警察FAX DVT_ID24 Added by SMuratec 李 2005/11/07 */
							else {
								if (tskno_DetectCalledTask != 0xFFFF) {
									del_tsk(&tskno_DetectCalledTask);
								}
								cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
							}
						}
#else /* !defined (KEISATSU) */
						if ( NCUStatus & DIALING_STATE ){
							NCUStatus &= ~HOOK_KEY_ON_STATE;
							/*HookKeyOffRelayControl(); 2000/03/01 Y.Murata */
						}
#endif /* defined (KEISATSU) */
						else {
							TxTelephoneOperationTaskMsg.Message = NOTICE_TEL1_OFF_HOOK;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						}
						break;
#else

						while( NCUStatus & DIALING_STATE ){
							wai_tsk(1);
						}
						NCUStatus |=  TELEPHONE1_OFF_HOOK;
						/*-------------------------------------*/
						/**	   ＨＯＯＫ状態監視タスクと同期	   */
						/*-------------------------------------*/
						TxTelephoneOperationTaskMsg.Message = OK_CONT;
						snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
						/*-------------------------------*/
						/**		メイン・タスクへ通知	 */
						/*-------------------------------*/
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TEL1_OFF_HOOK;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						/*-------------------------------------*/
						/**		多機能電話実行タスクへ通知	   */
						/*-------------------------------------*/
						TxTelephoneOperationTaskMsg.Message = NOTICE_TEL1_OFF_HOOK;
						snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						break;
#endif
																/*---------------------------------*/
					case	DETECT_TEL2_OFF_HOOK			:	/** 外付電話　ＯＦＦ　ＨＯＯＫ検出 */
																/*---------------------------------*/
#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE)
					/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 *//* SAKAKI追加 By M.Maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */

					/* 2000/01/13 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG
					 * 新Ｌ４００で、ＮＴＴファネットからの指摘項目
					 * フックキー押下してダイアルし、ダイアル送出中にＴＥＬ１を上げてさらにダイアルし、
					 * ダイアル送出中に、ＴＥＬ１を戻すとＬＣＤで電話中のまま。もう一度ＴＥＬ１を上げ下げするまで戻らない。
					*/
#if defined (KEISATSU) /* 警察FAX DVT_ID18&25&26 Added by SMuratec 李 2005/11/14 */
						comp_min_on_time = NCU_CI_MinOnTime(); /* 最小ON期間を獲得 */
						if ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) {
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
												SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_EXT_LINE_IN_RECEIVE; 
											}
										}
									}
								}
							}
						}
#endif
						NCUStatus |= TELEPHONE2_OFF_HOOK;
						/*-----------------------------------*/
						/**	  ＨＯＯＫ状態監視タスクと同期	 */
						/*-----------------------------------*/
 #if defined (KEISATSU) && (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/30 */
 						if (DEBUG_NumberDisplay) {
							if (RxTelephoneOperationTaskMsg->Item == FROM__NCU_SUB) {  /* 1998/10/20 */
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
							}
							else {
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_ND, &TxTelephoneOperationTaskMsg);
							}
						}
						else {
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
						}
 #else /* !defined (KEISATSU || (PRO_NUMBER_DISPLAY != ENABLE) */
						TxTelephoneOperationTaskMsg.Message = OK_CONT;
						snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
 #endif /* defined (KEISATSU) */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/25 */
 #if (PRO_NUMBER_DISPLAY == ENABLE)
						if (DEBUG_NumberDisplay) {
	 						if ((SYS_LineNDStatus == ND_USED_IN_EXT) && 
								(NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CAR_DETECTED))) {
								if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){
									Tel2OhCounter			= 40;
								}
								break;
							}
							if (SYS_LineNDStatus == ND_USED_IN_EXT) {
								NCU_ND_SetCallDetectedStatus();
							}
						}
 #endif
 #endif /* defined (KEISATSU) */
						/*-------------------------------*/
						/**		メイン・タスクへ通知	 */
						/*-------------------------------*/
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TEL2_OFF_HOOK;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						/*---------------------------------*/
						/**	  多機能電話実行タスクへ通知   */
						/*---------------------------------*/
						/*-----------------------------------------------------------
						** ＴＥＬ２もＴＥＬ１の処理に統一  By M.Tachibana 1997/09/25
						*/
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/09/07 */
						if (IsDailing) {	/* 本体ダイヤル中 */
							if (ModemRelaySetting()){	/* モデムリレーを拡張回線に接続している場合 */
								NCUStatus &= ~HOOK_KEY_ON_STATE;
								SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
								UpdateLED();
							}
							/* 警察FAX DVT_ID24 Added by SMuratec 李 2005/11/07 */
							else {
								if (tskno_Detect2ndCalledTask != 0xFFFF) {
									del_tsk(&tskno_Detect2ndCalledTask);
								}
								cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
							}
						}
#else /* !defined (KEISATSU) */
						if ((CHK_UNI_TEL2_TEL1Action()) && ( NCUStatus & DIALING_STATE )) {
							NCUStatus &= ~HOOK_KEY_ON_STATE;
							/*HookKeyOffRelayControl(); 2000/03/01 Y.Murata */
						}
#endif /* defined (KEISATSU) */
						else {
							TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_OFF_HOOK;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						}
						break;
#else
						/*-----------------------------------------------------------
						** ＴＥＬ２もＴＥＬ１の処理に統一  By M.Tachibana 1997/09/25
						*/
						if (CHK_UNI_TEL2_TEL1Action()) {
							while( NCUStatus & DIALING_STATE ){
								wai_tsk(1);
							}
						}

						NCUStatus |= TELEPHONE2_OFF_HOOK;
						/*-----------------------------------*/
						/**	  ＨＯＯＫ状態監視タスクと同期	 */
						/*-----------------------------------*/
						TxTelephoneOperationTaskMsg.Message = OK_CONT;
						snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
						/*-------------------------------*/
						/**		メイン・タスクへ通知	 */
						/*-------------------------------*/
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TEL2_OFF_HOOK;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						/*---------------------------------*/
						/**	  多機能電話実行タスクへ通知   */
						/*---------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* V851 標準回線保留中に、拡張回線に接続されたTEL2をｵﾌﾌｯｸすると保留が解除されたBy Y.Suzuki 2002/08/22 */
						if (NCUStatus & HOLD_STATE) {
							if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
								TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_OFF_HOOK;
								snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
							}
						}
						else {
							TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_OFF_HOOK;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						}
#else

						TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_OFF_HOOK;
						snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
#endif
						break;
#endif
																/*------------------------------------*/
					case	DETECT_INPUT_HOOK_KEY			:	/**			 回線補足キー入力		  */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
						if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
							HookKeyInputFlag = 1;
							if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)) {
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
							}
							else{
								del_tsk(&tskno_TelephoneHookCheckTask);
							}

							if( NCUStatus & DIALING_STATE ){
								NCUStatus &= ~DIALING_STATE;
								/*-----------------------------------*/
								/** 多機能電話制御モジュール終了処理 */
								/*-----------------------------------*/
								TelephoneOperationTaskExit();
								/*-------------------------------*/
								/**		メイン・タスクへ通知	 */
								/*-------------------------------*/
								TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
								snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
								rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
								/*-------------------------*/
								/**	  自タスク終了処理	   */
								/*-------------------------*/
								SYS_HookKeyInputFlag		 = 0;
								TransferReceiveAvailableTime = 0;
								TransferReceiveFlag			 = 0;
								SYS_RxDetectFlag			 = 0;
								tskno_NCU_TelephoneOperation = 0xffff;
								exi_tsk();
							}
							else{
								/*---------------------------------------------------------------*/
								/** 多機能電話実行タスクへ回線捕捉キーが入力されたことを通知する */
								/*---------------------------------------------------------------*/
								TxTelephoneOperationTaskMsg.Message = NOTICE_INPUT_HOOK_KEY;
								snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
							}
						}
						else {
							HookKeyInputFlag = 1;
#if defined (KEISATSU) /* 警察FAX DVT_ID18&25&26 Added by SMuratec 李 2005/11/14 */
							comp_min_on_time = NCU_CI_MinOnTime(); /* 最小ON期間を獲得 */
							if( !(NCUStatus & HOOK_KEY_ON_STATE) ){
								if (CHK_LineSetting() && !(NCUStatus & TELEPHONE1_OFF_HOOK)) {
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
								else if (!CHK_LineSetting() && !(NCUStatus & TELEPHONE2_OFF_HOOK)) {
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
							}
#endif
							if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)) {
 #if defined (KEISATSU) && (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/30 */
 								if (DEBUG_NumberDisplay) {
									if (RxTelephoneOperationTaskMsg->Item == FROM__NCU_SUB) {  /* 1998/10/20 */
										TxTelephoneOperationTaskMsg.Message = OK_CONT;
										snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
									}
									else {
										TxTelephoneOperationTaskMsg.Message = OK_CONT;
										snd_msg(mbxno.NCU_ND, &TxTelephoneOperationTaskMsg);
									}
								}
								else {
									TxTelephoneOperationTaskMsg.Message = OK_CONT;
									snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
								}
 #else /* !defined (KEISATSU || (PRO_NUMBER_DISPLAY != ENABLE) */
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
 #endif /* defined (KEISATSU) */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/25 */
 #if (PRO_NUMBER_DISPLAY == ENABLE)
								if (DEBUG_NumberDisplay) {
		 							if( !(NCUStatus & HOOK_KEY_ON_STATE) ){
										if (CHK_LineSetting() && /* 回線設定 == 標準回線 */
											(SYS_LineNDStatus == ND_USED_IN_STD)) {
											if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CAR_DETECTED)) { 
												NCUStatus        |= HOOK_KEY_ON_STATE;
												break;
											}
										}
										else if (!CHK_LineSetting() && /* 回線設定 == 拡張回線 */
											(SYS_LineNDStatus == ND_USED_IN_EXT)) {
											if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CAR_DETECTED)) { 
												NCUStatus        |= HOOK_KEY_ON_STATE;
												break;
											}
										}
									}
								}
 #endif
 #endif /* defined (KEISATSU) */
								if( NCUStatus & HOOK_KEY_ON_STATE ){		/** 回線補足キーがＯＮ状態の場合  */
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_HKEY;
								}
								else {
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_INPUT_HOOK_KEY;
								}
								snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
								rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							}
							else {
								if (tskno_TelephoneHookCheckTask != 0xffff) {
									del_tsk(&tskno_TelephoneHookCheckTask);
								}
							}
							/*---------------------------------------------------------------*/
							/** 多機能電話実行タスクへ回線捕捉キーが入力されたことを通知する */
							/*---------------------------------------------------------------*/
							TxTelephoneOperationTaskMsg.Message = NOTICE_INPUT_HOOK_KEY;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
#if (0)
//							HookKeyInputFlag = 1;
//							if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)) {
//								TxTelephoneOperationTaskMsg.Message = OK_CONT;
//								snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
//							}
//							else{
//								if (tskno_TelephoneHookCheckTask != 0xffff) {
//									del_tsk(&tskno_TelephoneHookCheckTask);
//								}
//							}
//							/*---------------------------------------------------------------*/
//							/** 多機能電話実行タスクへ回線捕捉キーが入力されたことを通知する */
//							/*---------------------------------------------------------------*/
//							TxTelephoneOperationTaskMsg.Message = NOTICE_INPUT_HOOK_KEY;
//							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
#endif
						}
#else
						HookKeyInputFlag = 1;

/*
** ＴＥＬ２がＴＥＬ１と同じ動作の場合、
** ＴＥＬ２をオフフックした状態でオフフックキーを押したとき、
** フッキング動作をせず、待機状態に戻る不具合
** ＨＩＮＯＫＩ ＱＡＴ 1999/02/09 by T.Soneoka
*/
#if (0)
**						if( NCUStatus & TELEPHONE1_OFF_HOOK ){
#else
						if ((NCUStatus & TELEPHONE1_OFF_HOOK)
						|| ((NCUStatus & TELEPHONE2_OFF_HOOK) && CHK_UNI_TEL2_TEL1Action())) {
#endif
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
						}
						else{
							del_tsk(&tskno_TelephoneHookCheckTask);
						}

						if( NCUStatus & DIALING_STATE ){
							NCUStatus &= ~DIALING_STATE;
							/*-----------------------------------*/
							/** 多機能電話制御モジュール終了処理 */
							/*-----------------------------------*/
							TelephoneOperationTaskExit();
							/*-------------------------------*/
							/**		メイン・タスクへ通知	 */
							/*-------------------------------*/
							TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
							snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
							rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							/*-------------------------*/
							/**	  自タスク終了処理	   */
							/*-------------------------*/
							SYS_HookKeyInputFlag		 = 0;
							TransferReceiveAvailableTime = 0;
							TransferReceiveFlag			 = 0;
							SYS_RingCounter				 = 0;
							SYS_RxDetectFlag			 = 0;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
							tskno_NCU_TelephoneOperation = 0xffff;
							if (IsCiSndMsg == TRUE) {
								rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
							}
							 /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
							if (DEBUG_NumberDisplay) {
								if (IsNDSndMsg == TRUE) {
									IsNDSndMsg = FALSE;
									rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
								}
							}
#endif /* defined (KEISATSU) */
							exi_tsk();
						}
						else{
							/*---------------------------------------------------------------*/
							/** 多機能電話実行タスクへ回線捕捉キーが入力されたことを通知する */
							/*---------------------------------------------------------------*/
							TxTelephoneOperationTaskMsg.Message = NOTICE_INPUT_HOOK_KEY;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						}
#endif
						break;
																/*-------------------------------*/
					case	DETECT_TEL1_ONHOOK				:	/** 付属電話　ＯＮ　ＨＯＯＫ検出 */
																/*-------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
						if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
							if( NCUStatus & DIALING_STATE ){
								NCUStatus &= ~DIALING_STATE;
								/*-----------------------------------*/
								/** 多機能電話制御モジュール終了処理 */
								/*-----------------------------------*/
								TelephoneOperationTaskExit();
								/*-------------------------------*/
								/**		メイン・タスクへ通知	 */
								/*-------------------------------*/
								TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
								snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
								rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
								/*-------------------------*/
								/**	  自タスク終了処理	   */
								/*-------------------------*/
								SYS_HookKeyInputFlag		 = 0;
								TransferReceiveAvailableTime = 0;
								TransferReceiveFlag			 = 0;
								SYS_RxDetectFlag			 = 0;
								NumberKeyInputFlag			 = 0;
								tskno_NCU_TelephoneOperation = 0xffff;
								exi_tsk();
							}
							else{
								if( NCUStatus & HOLD_STATE ){
									TxTelephoneOperationTaskMsg.Message = OK_CONT;
									snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
									/*-------------------------------*/
									/**		メイン・タスクへ通知	 */
									/*-------------------------------*/
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT;
									snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
									rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
								}
								else{
									if (tskno_TelephoneHookCheckTask != 0xffff) {
										del_tsk(&tskno_TelephoneHookCheckTask);
									}
									if( TADStatus & FAX_TAD_STATE ){				/** 外付留守番電話着信中の場合 */
										/*---------------------------------------*/	/*-----------------------------*/
										/** 外付留守番電話着信後処理タスクの削除 */
										/*---------------------------------------*/
										del_tsk(&tskno_FaxTadAutoSwitchTask);
										TADStatus &= ~FAX_TAD_STATE;
									}
								}

								/*-----------------------------------------------------------*/
								/** 多機能電話実行タスクへ付属電話のＯＮ　ＨＯＯＫ検出を通知 */
								/*-----------------------------------------------------------*/
								TxTelephoneOperationTaskMsg.Message = NOTICE_TEL1_ON_HOOK;
								snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
							}
						}
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/09/07 */
						else if (ModemRelaySetting()	/* モデムリレーを拡張回線に接続している場合 */
							&& IsDailing) {	/* 本体ダイヤル中 */
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
							/*-------------------------------*/
							/**		メイン・タスクへ通知	 */
							/*-------------------------------*/
							TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT;
							snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
							rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							/* 秘話機能起動 */
							if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) != STD_READY) {
								/* 秘話機能起動した場合 */
								SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
								SYS_LineTelStatus |= STD_READY;
								H_RelayOff();
							}
							if (!(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK))) {
								NCU_HdstShift();
							}
							NCUStatus &= (~TELEPHONE1_OFF_HOOK);
							SYS_RingCounter = 0;
						}
#endif /* defined (KEISATSU) */
						else {
							if ((NCUStatus & HOLD_STATE)
							||  (NCUStatus & TELEPHONE2_OFF_HOOK)
							||  (NCUStatus & HOOK_KEY_ON_STATE)) {
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
								/*-------------------------------*/
								/**		メイン・タスクへ通知	 */
								/*-------------------------------*/
								TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT;
								snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
								rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							}
							else{
								if (tskno_TelephoneHookCheckTask != 0xffff) {
									del_tsk(&tskno_TelephoneHookCheckTask);
								}
							}
							/*-----------------------------------------------------------*/
							/** 多機能電話実行タスクへ付属電話のＯＮ　ＨＯＯＫ検出を通知 */
							/*-----------------------------------------------------------*/
							TxTelephoneOperationTaskMsg.Message = NOTICE_TEL1_ON_HOOK;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						}
#else
						if( NCUStatus & DIALING_STATE ){
							NCUStatus &= ~DIALING_STATE;
							/*-----------------------------------*/
							/** 多機能電話制御モジュール終了処理 */
							/*-----------------------------------*/
							TelephoneOperationTaskExit();
							/*-------------------------------*/
							/**		メイン・タスクへ通知	 */
							/*-------------------------------*/
							TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
							snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
							rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							/*-------------------------*/
							/**	  自タスク終了処理	   */
							/*-------------------------*/
							SYS_HookKeyInputFlag		 = 0;
							TransferReceiveAvailableTime = 0;
							TransferReceiveFlag			 = 0;
							SYS_RingCounter				 = 0;
							SYS_RxDetectFlag			 = 0;
							NumberKeyInputFlag			 = 0;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
							tskno_NCU_TelephoneOperation = 0xffff;
							if (IsCiSndMsg == TRUE) {
								rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
							}
							/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
							if (DEBUG_NumberDisplay) {
								if (IsNDSndMsg == TRUE) {
									IsNDSndMsg = FALSE;
									rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
								}
							}
#endif /* defined (KEISATSU) */
							exi_tsk();
						}
						else{
							if( NCUStatus & HOLD_STATE ){
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
								/*-------------------------------*/
								/**		メイン・タスクへ通知	 */
								/*-------------------------------*/
								TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT;
								snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
								rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							}
							else{
								del_tsk(&tskno_TelephoneHookCheckTask);
								if( TADStatus & FAX_TAD_STATE ){				/** 外付留守番電話着信中の場合 */
									/*---------------------------------------*/	/*-----------------------------*/
									/** 外付留守番電話着信後処理タスクの削除 */
									/*---------------------------------------*/
									del_tsk(&tskno_FaxTadAutoSwitchTask);
									TADStatus &= ~FAX_TAD_STATE;
								}
							}

							/*-----------------------------------------------------------*/
							/** 多機能電話実行タスクへ付属電話のＯＮ　ＨＯＯＫ検出を通知 */
							/*-----------------------------------------------------------*/
							TxTelephoneOperationTaskMsg.Message = NOTICE_TEL1_ON_HOOK;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						}
#endif
						break;
																/*-------------------------------*/
					case	DETECT_TEL2_ONHOOK				:	/** 外付電話　ＯＮ　ＨＯＯＫ検出 */
																/*-------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
 #if (PRO_CIPHER == ENABLE)
						/* スクランブル処理中、受信優先設定、で留守/FAXの場合外付けTELをオンフックした場合に
						** スクランブルを再起動許可する。留守/FAX待機でスクランブル中止された場合に通信に
						** 入らなかったときのための処置です By Y.Suzuki 1998/06/15 */
						if (NCU_RxModeSwitch == SYS_ANS_FAX_READY) {
							if ((SYS_CipherInterruptionOn) && (SYS_CipherRestartEnable != 1)) {
								SYS_CipherRestartEnable = 1;
							}
						}
 #endif
						if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
							if (CHK_UNI_TEL2_TEL1Action()) {
								if( NCUStatus & DIALING_STATE ){
									NCUStatus &= ~DIALING_STATE;
									/*-----------------------------------*/
									/** 多機能電話制御モジュール終了処理 */
									/*-----------------------------------*/
									TelephoneOperationTaskExit();
									/*-------------------------------*/
									/**		メイン・タスクへ通知	 */
									/*-------------------------------*/
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
									snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
									rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
									/*-------------------------*/
									/**	  自タスク終了処理	   */
									/*-------------------------*/
									SYS_HookKeyInputFlag		 = 0;
									TransferReceiveAvailableTime = 0;
									TransferReceiveFlag			 = 0;
									SYS_RxDetectFlag			 = 0;
									NumberKeyInputFlag			 = 0;
									tskno_NCU_TelephoneOperation = 0xffff;
									exi_tsk();
								}
								else{
									if( NCUStatus & HOLD_STATE ){
										TxTelephoneOperationTaskMsg.Message = OK_CONT;
										snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
										/*-------------------------------*/
										/**		メイン・タスクへ通知	 */
										/*-------------------------------*/
										TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_TEL2;		/* メッセージ追加 1997/09/25 */
										snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
										rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
									}
									else{
										if (tskno_TelephoneHookCheckTask != 0xffff) {
											del_tsk(&tskno_TelephoneHookCheckTask);
										}
										if( TADStatus & FAX_TAD_STATE ){				/** 外付留守番電話着信中の場合 */
											/*---------------------------------------*/	/*-----------------------------*/
											/** 外付留守番電話着信後処理タスクの削除 */
											/*---------------------------------------*/
											del_tsk(&tskno_FaxTadAutoSwitchTask);
											TADStatus &= ~FAX_TAD_STATE;
										}
									}

									/*-----------------------------------------------------------*/
									/** 多機能電話実行タスクへ付属電話のＯＮ　ＨＯＯＫ検出を通知 */
									/*-----------------------------------------------------------*/
									TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_ON_HOOK;
									snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
								}

							}
							else {
								if (tskno_TelephoneHookCheckTask != 0xffff) {
									del_tsk(&tskno_TelephoneHookCheckTask);
								}
																				/*-----------------------------*/
								if( TADStatus & FAX_TAD_STATE ){				/** 外付留守番電話着信中の場合 */
									/*---------------------------------------*/	/*-----------------------------*/
									/** 外付留守番電話着信後処理タスクの削除 */
									/*---------------------------------------*/
									del_tsk(&tskno_FaxTadAutoSwitchTask);
									TADStatus &= ~FAX_TAD_STATE;
								}
								/*-----------------------------------------------------------*/
								/** 多機能電話実行タスクへ外付電話のＯＮ　ＨＯＯＫ検出を通知 */
								/*-----------------------------------------------------------*/
								TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_ON_HOOK;
								snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);

							}
						}
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/09/07 */
						else if (!ModemRelaySetting()	/* モデムリレーを標準回線に接続している場合 */
							&& IsDailing) {	/* 本体ダイヤル中 */
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
							/*-------------------------------*/
							/**		メイン・タスクへ通知	 */
							/*-------------------------------*/
							TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_TEL2;
							snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
							rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							/* 秘話機能起動 */
							if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) != EXT_READY) {
								/* 秘話機能起動した場合 */
								SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
								SYS_LineTelStatus |= EXT_READY;
								L_RelayOff();
							}
							if (!(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK))) {
								NCU_HdstShift();
							}
							NCUStatus &= (~TELEPHONE2_OFF_HOOK);
							SYS_RingCounterExt = 0;
						}
#endif /* defined (KEISATSU) */
						else {	/**	PHONE2リレー設定が拡張ラインの場合	*/
							if ((NCUStatus & TELEPHONE1_OFF_HOOK)
							||  (NCUStatus & HOOK_KEY_ON_STATE)) {
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
								/*-------------------------------*/
								/**		メイン・タスクへ通知	 */
								/*-------------------------------*/
								TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_TEL2;		/* メッセージ追加 1997/09/25 */
								snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
								rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							}
							else {
#if (0)	/* V851 標準回線保留中に拡張回線に接続されたTEL2をｵﾌﾌｯｸすると保留が解除される。 By Y.Suzuki 2002/08/12 */
								if (tskno_TelephoneHookCheckTask != 0xffff) {
									del_tsk(&tskno_TelephoneHookCheckTask);
								}
#else
								if (!(NCUStatus & HOLD_STATE)) {
									if (tskno_TelephoneHookCheckTask != 0xffff) {
										del_tsk(&tskno_TelephoneHookCheckTask);
									}
								}
								else {
									TxTelephoneOperationTaskMsg.Message = OK_CONT;
									snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
									/*-------------------------------*/
									/**		メイン・タスクへ通知	 */
									/*-------------------------------*/
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_TEL2;		/* メッセージ追加 1997/09/25 */
									snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
									rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
								}
#endif
							}
							/*-----------------------------------------------------------*/
							/** 多機能電話実行タスクへ外付電話のＯＮ　ＨＯＯＫ検出を通知 */
							/*-----------------------------------------------------------*/
							TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_ON_HOOK;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						}
#else
 #if (PRO_CIPHER == ENABLE)
						/* スクランブル処理中、受信優先設定、で留守/FAXの場合外付けTELをオンフックした場合に
						** スクランブルを再起動許可する。留守/FAX待機でスクランブル中止された場合に通信に
						** 入らなかったときのための処置です By Y.Suzuki 1998/06/15 */
						if (NCU_RxModeSwitch == SYS_ANS_FAX_READY) {
							if ((SYS_CipherInterruptionOn) && (SYS_CipherRestartEnable != 1)) {
								SYS_CipherRestartEnable = 1;
							}
						}
 #endif
						/*-----------------------------------------------------------
						** ＴＥＬ２もＴＥＬ１の処理に統一  By M.Tachibana 1997/09/25
						*/
						if (CHK_UNI_TEL2_TEL1Action()) {

							if( NCUStatus & DIALING_STATE ){
								NCUStatus &= ~DIALING_STATE;
								/*-----------------------------------*/
								/** 多機能電話制御モジュール終了処理 */
								/*-----------------------------------*/
								TelephoneOperationTaskExit();
								/*-------------------------------*/
								/**		メイン・タスクへ通知	 */
								/*-------------------------------*/
								TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
								snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
								rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
								/*-------------------------*/
								/**	  自タスク終了処理	   */
								/*-------------------------*/
								SYS_HookKeyInputFlag		 = 0;
								TransferReceiveAvailableTime = 0;
								TransferReceiveFlag			 = 0;
								SYS_RingCounter				 = 0;
								SYS_RxDetectFlag			 = 0;
								NumberKeyInputFlag			 = 0;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
								tskno_NCU_TelephoneOperation = 0xffff;
								if (IsCiSndMsg == TRUE) {
									rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
									TxTelephoneOperationTaskMsg.Message = OK_CONT;
									snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
								}
								/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
								if (DEBUG_NumberDisplay) {
									if (IsNDSndMsg == TRUE) {
										IsNDSndMsg = FALSE;
										rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
									}
								}
#endif /* defined (KEISATSU) */
								exi_tsk();
							}
							else{
								if( NCUStatus & HOLD_STATE ){
									TxTelephoneOperationTaskMsg.Message = OK_CONT;
									snd_msg(mbxno.NCU_TelephoneHookCheckTask, &TxTelephoneOperationTaskMsg);
									/*-------------------------------*/
									/**		メイン・タスクへ通知	 */
									/*-------------------------------*/
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_TEL2;		/* メッセージ追加 1997/09/25 */
									snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
									rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
								}
								else{
									del_tsk(&tskno_TelephoneHookCheckTask);
									if( TADStatus & FAX_TAD_STATE ){				/** 外付留守番電話着信中の場合 */
										/*---------------------------------------*/	/*-----------------------------*/
										/** 外付留守番電話着信後処理タスクの削除 */
										/*---------------------------------------*/
										del_tsk(&tskno_FaxTadAutoSwitchTask);
										TADStatus &= ~FAX_TAD_STATE;
									}
								}

								/*-----------------------------------------------------------*/
								/** 多機能電話実行タスクへ付属電話のＯＮ　ＨＯＯＫ検出を通知 */
								/*-----------------------------------------------------------*/
								TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_ON_HOOK;
								snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
							}

						}
						else {

							del_tsk(&tskno_TelephoneHookCheckTask);
																			/*-----------------------------*/
							if( TADStatus & FAX_TAD_STATE ){				/** 外付留守番電話着信中の場合 */
								/*---------------------------------------*/	/*-----------------------------*/
								/** 外付留守番電話着信後処理タスクの削除 */
								/*---------------------------------------*/
								del_tsk(&tskno_FaxTadAutoSwitchTask);
								TADStatus &= ~FAX_TAD_STATE;
							}
							/*-----------------------------------------------------------*/
							/** 多機能電話実行タスクへ外付電話のＯＮ　ＨＯＯＫ検出を通知 */
							/*-----------------------------------------------------------*/
							TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_ON_HOOK;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);

						}
#endif
						break;
#if (PRO_REMOTE_RX == ENABLE)	/* 1998/01/24  By T.Yamaguchi */
																/*-------------------------------*/
					case	DETECT_REMOTE_RX_SIGNAL:			/** リモート受信信号検出         */
																/*-------------------------------*/
							del_tsk(&tskno_RemoteRxSignalDetTask);
																			/*-----------------------------*/
							if( TADStatus & FAX_TAD_STATE ){				/** 外付留守番電話着信中の場合 */
								/*---------------------------------------*/	/*-----------------------------*/
								/** 外付留守番電話着信後処理タスクの削除 */
								/*---------------------------------------*/
								del_tsk(&tskno_FaxTadAutoSwitchTask);
								TADStatus &= ~FAX_TAD_STATE;
							}
							TADStatus |= REMOTE_RECEIVE;	/* リモート受信起動 */
							/*-----------------------------------------------------------*/
							/** 多機能電話実行タスクへ外付電話のＯＮ　ＨＯＯＫ検出を通知 */
							/*-----------------------------------------------------------*/
							TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_ON_HOOK;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						break;
#elif (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
	#if (PRO_MODEM == R288F)
																/*-------------------------------*/
					case	DETECT_REMOTE_RX_SIGNAL:			/** リモート受信信号検出         */
																/*-------------------------------*/
#if defined (KEISATSU)  /* Added by SMuratec 李 2005/06/24 */
							if( tskno_RemoteRxSignalDetTask != 0xFFFF ){
								del_tsk(&tskno_RemoteRxSignalDetTask);
							}
#else /* defined (KEISATSU) */
							del_tsk(&tskno_RemoteRxSignalDetTask);
#endif /* defined (KEISATSU) */
							OneDigitDiallingExecute = 0;
						 	DspRamAccessWriteMethod3(0x0B3C, BackupReceiveLevel, 0x0000);
							NCU_IsDetRemotePulse = 0;
							NCU_IsRemotePulseRx = 0;
																			/*-----------------------------*/
							if( TADStatus & FAX_TAD_STATE ){				/** 外付留守番電話着信中の場合 */
								/*---------------------------------------*/	/*-----------------------------*/
								/** 外付留守番電話着信後処理タスクの削除 */
								/*---------------------------------------*/
								del_tsk(&tskno_FaxTadAutoSwitchTask);
								TADStatus &= ~FAX_TAD_STATE;
							}
							TADStatus |= REMOTE_RECEIVE;	/* リモート受信起動 */
							/*-----------------------------------------------------------*/
							/** 多機能電話実行タスクへ外付電話のＯＮ　ＨＯＯＫ検出を通知 */
							/*-----------------------------------------------------------*/
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/07/01 */
							/* 転送受信の確認音仕様 警察FAX Added by SMuratec 李 2005/10/12 */
							DP_RelayOn();
							wai_tsk(1);

							S_RelayOn();	/* Relay Spike Niose For Switching(FRA DEU) 1996/11/26 */

							AnalogSwitchRXA_Set();

							CML_RelayOn();
							wai_tsk(10);	/* 100ms */
							S_RelayOff();				/* Add by TH92115 1994/08/29 */

							MDM_SingleToneOff();
							/* ソフトリセット */
							MDM_SoftResetModem();
							MDM_TransmitLevelSet((UBYTE) FCM_PtnrChk_T23Attenation());
							MDM_SingleToneOn((UBYTE)(OPT_MDM_TONAL_1800HZ - 1));
							wai_tsk(50);
							MDM_SingleToneOff();
							MDM_SoftResetModem();
							CML_RelayOff();
							CONT_24V_Off();
							S_RelayOff();
							DP_RelayOff();
							AnalogSwitchRXA_Set();
							

							if (!ModemRelaySetting()) {	/* モデムリレーを標準回線に接続している場合 */
								TxTelephoneOperationTaskMsg.Message = NOTICE_TEL1_ON_HOOK;
							}
							else {
								TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_ON_HOOK;
							}
#else /* !defined (KEISATSU) */
							TxTelephoneOperationTaskMsg.Message = NOTICE_TEL2_ON_HOOK;
#endif /* defined (KEISATSU) */
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						break;
	#endif
#endif
					default:

						break;
				}

				break;

												/*---------------------------------------------------------*/
			case	FROM__NCU_TEL			:	/** 多機能電話実行タスク（ＮＣＵ＿ＴＥＬ）からのメッセージ */
												/*---------------------------------------------------------*/
				switch(RxTelephoneOperationTaskMsg->Message){
																/*-------------------------------------*/
					case	DETECT_HOLD_1_SEC_PASS			:	/** 保留状態１分ＴｉｍｅｒＴｉｍｅＵｐ */
																/*-------------------------------------*/
						TxTelephoneOperationTaskMsg.Message = OK_CONT;
						snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
						/*-------------------------------------------------*/
						/** メイン・タスクへ保留状態へ遷移後の１分毎の通知 */
						/*-------------------------------------------------*/
						TxTelephoneOperationTaskMsg.Message = MSG_HOLD_ELAPSE_1MIN;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);

						break;
																/*-------------------------------------*/
					case	DETECT_HOLD_TIMEUP				:	/**		   保留状態ＴｉｍｅＵｐ		   */
																/*-------------------------------------*/
						NCUStatus &= ~HOLD_STATE;
																/*-----------------------------*/
						if( NCUStatus & TELEPHONE1_OFF_HOOK ){	/** 付属電話OFF HOOK状態の場合 */
																/*-----------------------------*/
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_TelephoneExecuteTask, &TxTelephoneOperationTaskMsg);
							/*---------------------------------------------*/
							/** メイン・タスクへ保留状態ＴｉｍｅＵｐを通知 */
							/*---------------------------------------------*/
							TxTelephoneOperationTaskMsg.Message = MSG_HOLD_TIMEUP;
							snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
							rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						}
						else{
							/*-----------------------------------*/
							/** 多機能電話制御モジュール終了処理 */
							/*-----------------------------------*/
							TelephoneOperationTaskExit();
							/*---------------------------------------------*/
							/** メイン・タスクへ保留状態ＴｉｍｅＵｐを通知 */
							/*---------------------------------------------*/
							TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
							snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
							rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							/*---------------------*/
							/**	  自タスクの終了   */
							/*---------------------*/
							SYS_HookKeyInputFlag		 = 0;
							TransferReceiveAvailableTime = 0;
							TransferReceiveFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
#else
							SYS_RingCounter				 = 0;
#endif
							SYS_RxDetectFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/26 */
							tskno_NCU_TelephoneOperation = 0xffff;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
							if (IsCiSndMsg == TRUE) {
								rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
							}
							/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
							if (DEBUG_NumberDisplay) {
								if (IsNDSndMsg == TRUE) {
									IsNDSndMsg = FALSE;
									rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
								}
							}
#endif /* defined (KEISATSU) */
#endif
							exi_tsk();
						}

						break;
																/*-----------------------*/
					case	DETECT_ON_HOOK_MANAGE_END		:	/**		待機状態移行	 */
																/*-----------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/26 */
						if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
							NCUStatus &=   ~( TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK );
						}
#else
						NCUStatus &=   ~( TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK );
#endif
						/*-----------------------------------*/
						/** 多機能電話制御モジュール終了処理 */
						/*-----------------------------------*/
						TelephoneOperationTaskExit();
						/*---------------------------------------------------------*/
						/** メイン・タスクへ付属・外付電話ＯＮ　ＨＯＯＫ検出を通知 */
						/*---------------------------------------------------------*/
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						/*---------------------*/
						/**	  自タスクの終了   */
						/*---------------------*/
						SYS_HookKeyInputFlag		 = 0;
						TransferReceiveAvailableTime = 0;
						TransferReceiveFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
#else
						SYS_RingCounter				 = 0;
#endif
						SYS_RxDetectFlag			 = 0;
						NumberKeyInputFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/26 */
						tskno_NCU_TelephoneOperation = 0xffff;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
						if (IsCiSndMsg == TRUE) {
							rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
						}
						/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
						if (DEBUG_NumberDisplay) {
							if (IsNDSndMsg == TRUE) {
								IsNDSndMsg = FALSE;
								rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
							}
						}
#endif /* defined (KEISATSU) */
#endif
						exi_tsk();

						break;
																/*---------------------------------*/
					case	DETECT_TRANSFER_RECEIVE			:	/** 転送受信検出・キャッチホン対策 */
																/*---------------------------------*/
						NCUStatus |= TRANSFER_RECIVE;
						/*-----------------------------------*/
						/** 多機能電話制御モジュール終了処理 */
						/*-----------------------------------*/
						TelephoneOperationTaskExit();
						/*---------------------------------------*/
						/** 転送受信／キャッチホン対策リレー制御 */
						/*---------------------------------------*/
						if( NCUStatus & TELEPHONE1_OFF_HOOK ){
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/7/27 K.Kawata */
							if (TelephoneToFaxcomRelayControl(TRNS_RX,CHK_TEL1FaxTransferAvailable)
							   && ((!CHK_UNI_Class1_EXT_Function()) || (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK) )
							   && (SYS_CL1_Status == 0)
							   && (CL1_ExtFunctionEnableFlag == 0)) {
#else
							if(TelephoneToFaxcomRelayControl( TRNS_RX, CHK_TEL1FaxTransferAvailable )){
#endif
								TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TRANSFER_TEL_EXIT;
							}
							else{
								TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
								NCUStatus &= ( ~(TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK ));		/* '94,08,23 By N.S. */
							}
						}
						else{
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/7/27 K.Kawata */
							if (TelephoneToFaxcomRelayControl(TRNS_RX,CHK_TEL1FaxTransferAvailable)
							   && ((!CHK_UNI_Class1_EXT_Function()) || (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK) )
							   && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM))
							   && (SYS_CL1_Status == 0)
							   && (CL1_ExtFunctionEnableFlag == 0)) {
#else
							if(TelephoneToFaxcomRelayControl( TRNS_RX, CHK_TEL2FaxTransferAvailable )){
#endif
								TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TRANSFER_TEL_EXIT;
							}
							else{
								TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
								NCUStatus &= ( ~(TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK ));		/* '94,08,23 By N.S. */
							}
						}
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						/*---------------------*/
						/**	  自タスクの終了   */
						/*---------------------*/
						SYS_HookKeyInputFlag		 = 0;
						TransferReceiveAvailableTime = 0;
						TransferReceiveFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
#else
						SYS_RingCounter				 = 0;			/* 桐のキャッチ・ホンの対応が決まるまで一応ここでクリアする。 */
#endif
						SYS_RxDetectFlag			 = 0;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
						tskno_NCU_TelephoneOperation = 0xffff;
						if (IsCiSndMsg == TRUE) {
							rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
						}
						/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
						if (DEBUG_NumberDisplay) {
							if (IsNDSndMsg == TRUE) {
								IsNDSndMsg = FALSE;
								rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
							}
						}
#endif /* defined (KEISATSU) */
						exi_tsk();

						break;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/26 */
					case	DETECT_TRANSFER_RECEIVE1:
					case	DETECT_TRANSFER_RECEIVE2:
						NCUStatus |= TRANSFER_RECIVE;
						/*-----------------------------------*/
						/** 多機能電話制御モジュール終了処理 */
						/*-----------------------------------*/
						TelephoneOperationTaskExit();
						/*---------------------------------------*/
						/** 転送受信／キャッチホン対策リレー制御 */
						/*---------------------------------------*/
						if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
							if( NCUStatus & TELEPHONE1_OFF_HOOK ){
								if(TelephoneToFaxcomRelayControl( TRNS_RX, CHK_TEL1FaxTransferAvailable )){
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TRANSFER_TEL_EXIT;
								}
								else{
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
									NCUStatus &= ( ~(TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK ));		/* '94,08,23 By N.S. */
								}
							}
							else{
								if(TelephoneToFaxcomRelayControl( TRNS_RX, CHK_TEL2FaxTransferAvailable )){
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TRANSFER_TEL_EXIT;
								}
								else{
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
									NCUStatus &= ( ~(TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK ));		/* '94,08,23 By N.S. */
								}
							}
						}
						else {
							if (RxTelephoneOperationTaskMsg->Message == DETECT_TRANSFER_RECEIVE1) {
								if (TelToFaxRelayControlTel2Ext(1)) {
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TRANSFER_TEL_EXIT;
								}
								else{
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
								}
								NCUStatus &= (~TELEPHONE1_OFF_HOOK);
							}
							else {
								if (TelToFaxRelayControlTel2Ext(2)) {
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TRANSFER_TEL_EXIT;
								}
								else{
									TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_EXIT;
								}
								NCUStatus &= (~TELEPHONE2_OFF_HOOK);
							}
						}
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						/*---------------------*/
						/**	  自タスクの終了   */
						/*---------------------*/
						SYS_HookKeyInputFlag		 = 0;
						TransferReceiveAvailableTime = 0;
						TransferReceiveFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
#else
						SYS_RingCounter				 = 0;			/* 桐のキャッチ・ホンの対応が決まるまで一応ここでクリアする。 */
#endif
						SYS_RxDetectFlag			 = 0;
						tskno_NCU_TelephoneOperation = 0xffff;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
						if (IsCiSndMsg == TRUE) {
							rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
						}
						/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
						if (DEBUG_NumberDisplay) {
							if (IsNDSndMsg == TRUE) {
								IsNDSndMsg = FALSE;
								rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
							}
						}
#endif /* defined (KEISATSU) */
						exi_tsk();
						break;
#endif

					default:

						break;
				}

				break;

												/*---------------------------------------------------------*/
			case FROM__NCU_TAD				:	/** 外付留守番電話着信後処理／リモートＦＡＸ　ＤＴＭＦ検出 */
			case FROM_BUILTIN_TAD			:	/**					 タスクからのメッセージ				   */
												/*---------------------------------------------------------*/
				switch(RxTelephoneOperationTaskMsg->Message){
															/*--------------------------*/
					case	DETECT_TAD_CNG_OR_SILENT	:	/**	   ＣＮＧ／無音検出		*/
															/*--------------------------*/
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/6 K.Kawata */
						if (((!CHK_UNI_Class1_EXT_Function()) || (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK))
						   && (SYS_CL1_Status == 0)
						   && (CL1_ExtFunctionEnableFlag == 0)) {

							NCUStatus |=  DETECT_CALL;
							TADStatus &= ~FAX_TAD_STATE;
							/*-----------------------------------*/
							/** 多機能電話制御モジュール終了処理 */
							/*-----------------------------------*/
							TelephoneOperationTaskExit();

							TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TRANSFER_TEL_EXIT;
							snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
							rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							/*---------------------*/
							/**	  自タスクの終了   */
							/*---------------------*/
							SYS_HookKeyInputFlag		 = 0;
							TransferReceiveAvailableTime = 0;
							TransferReceiveFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
#else
							SYS_RingCounter				 = 0;
#endif
							SYS_RxDetectFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/26 */
							tskno_NCU_TelephoneOperation = 0xffff;
#endif
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
							if (IsCiSndMsg == TRUE) {
								rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
								TxTelephoneOperationTaskMsg.Message = OK_CONT;
								snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
							}
							/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
							if (DEBUG_NumberDisplay) {
								if (IsNDSndMsg == TRUE) {
									IsNDSndMsg = FALSE;
									rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
								}
							}
#endif /* defined (KEISATSU) */
							exi_tsk();
						}
						break;
 #else
						NCUStatus |=  DETECT_CALL;
						TADStatus &= ~FAX_TAD_STATE;
						/*-----------------------------------*/
						/** 多機能電話制御モジュール終了処理 */
						/*-----------------------------------*/
						TelephoneOperationTaskExit();

						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TRANSFER_TEL_EXIT;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						/*---------------------*/
						/**	  自タスクの終了   */
						/*---------------------*/
						SYS_HookKeyInputFlag		 = 0;
						TransferReceiveAvailableTime = 0;
						TransferReceiveFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
						/* 必ず標準回線からで受信する。By Y.Suzuki 2002/08/22 */
						SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	拡張ライン通信中	*/
#else
						SYS_RingCounter				 = 0;
#endif
						SYS_RxDetectFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/26 */
						tskno_NCU_TelephoneOperation = 0xffff;
#endif
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
						if (IsCiSndMsg == TRUE) {
							rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
						}
						/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
						if (DEBUG_NumberDisplay) {
							if (IsNDSndMsg == TRUE) {
								IsNDSndMsg = FALSE;
								rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
							}
						}
#endif /* defined (KEISATSU) */
						exi_tsk();
						break;
 #endif	/** PRO_CLASS1_EXT_FUNC == ENABLE **/
														/*---------------------------------------*/
					case	DETECT_TAD_TIMEUP		:	/** 外付留守番電話着信後処理ＴｉｍｅＵｐ */
														/*---------------------------------------*/
						TADStatus &= ~FAX_TAD_STATE;

						del_tsk(&tskno_FaxTadAutoSwitchTask);
	#if (PRO_MODEM == ORANGE3)
						if( tskno_TelephoneHookCheckTask != 0xFFFF ){
							del_tsk(&tskno_TelephoneHookCheckTask);
						}
						tskno_TelephoneHookCheckTask	= 0xFFFF;
						cre_tsk(&tskno_TelephoneHookCheckTask, TSK_NCU_TELEPHONEHOOKCHECKTASK, &(mbxno.NCU_TelephoneOperationTask));
	#endif
						break;
					default:

						break;
				}

				break;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
			case	FROM__NCU_RING:
				switch(RxTelephoneOperationTaskMsg->Message){
														/*-----------------------------*/
				case	DETECT_CI					:	/**       ＣＩ検出の場合       */
				case	DETECT_CI_TIMEUP			:	/** ＣＩ検出ＴｉｍｅＵｐの場合 */
														/*-----------------------------*/
					TxTelephoneOperationTaskMsg.Message = OK_CONT;
					snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
					/*---------------------------------------*/
					/** メイン・タスクへ通知（発着衝突回避） */
					/*---------------------------------------*/
					if(RxTelephoneOperationTaskMsg->Message == DETECT_CI){
						NCUStatus |= DETECT_CI_STATE;
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_CI;
					}
					else{
						NCUStatus &= ~DETECT_CI_STATE;
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_CI_TIMEUP;
					}
					snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
					rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
					break;
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/30 */
				case	DETECT_ND_CAR_CALLED_SIGNAL:
					if (DEBUG_NumberDisplay) {
						if (!CHK_NumberDisplayByExtPhoneON() && !(NCU_ND_Status & ND_CAR_DETECTED)) {
							NCU_ND_SetCarDetectedStatus();
							NCU_TaskKillChildTasks();
							TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ND_CAR;
							snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
							rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
							/*-----------------------------------*/
							/** ナンバーディスプレイ情報受信処理 */
							/*-----------------------------------*/
							cre_tsk(&tskno_NCU_ND_Rx, TSK_NCU_ND_RXPROCEDURETASK, &(mbxno.NCU_Task));
							snd_msg(mbxno.NCU_ND, &TxTelephoneOperationTaskMsg); /* なんでもいいから一つ NCU_ND_RxProcedureTask にメッセージをほる。*/
						}
						else {
							NCU_ND_SetCarDetectedStatus();
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
						}
					}
					break;
				case	DETECT_RING			:			/** １波検出の場合 */
														/*-----------------*/
					TxNCUTaskMsg.Message = OK_CONT;
					snd_msg(mbxno.NCU_DetectCalledTask, &TxNCUTaskMsg);
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
					break;
				case 	DETECT_2ND_RING: /* added by H.Kubo 1998/10/12 */
					if (DEBUG_NumberDisplay) {
						/*---------------------------------------*/
						/** メイン・タスクへ通知（発着衝突回避） */
						/*---------------------------------------*/
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_RING;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						NCU_ND_AfterNdRxRelaySetting();
						NCU_ND_InitializeStatus();
						if (tskno_DetectCalledTask == 0xFFFF) {
							cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
						}
						else if (tskno_Detect2ndCalledTask == 0xFFFF) {
							cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
						}
					}
					break;
				case 	DETECT_2ND_RING_TIMEUP:
					if (DEBUG_NumberDisplay) {
						if (RxTelephoneOperationTaskMsg->Item == FROM__NCU_RING) {  /* 1998/10/20 */
							TxTelephoneOperationTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
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
						if (SYS_LineNDStatus == ND_USED_IN_STD) {
							SYS_RingCounter = 0; /* 着信拒否処理の追加に伴い、呼出音停止後の転送受信をここで防止。 by H.Kubo 1999/02/26 */
							if (tskno_DetectCalledTask != 0xFFFF) {
								del_tsk(&tskno_DetectCalledTask);
							}
						}
						else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
							SYS_RingCounterExt = 0; /* 着信拒否処理の追加に伴い、呼出音停止後の転送受信をここで防止。 by H.Kubo 1999/02/26 */
							if (tskno_Detect2ndCalledTask != 0xFFFF) {
								del_tsk(&tskno_Detect2ndCalledTask);
							}
						}
						/*---------------------------------------*/
						/** 待機状態時回線監視モジュール終了処理 */
						/*---------------------------------------*/
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
					break;
	#endif /* defined (KEISATSU) */
				case	DETECT_CALLED_REQUEST_EXT:	/** 拡張ライン着信検出の場合 */
				case	DETECT_F_NET_CALLED_SIGNAL_EXT:	/** 拡張ライン(1300Hz)着信検出の場合 */
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
#if (PRO_NUMBER_DISPLAY == ENABLE)
					if (DEBUG_NumberDisplay) {
						if (SYS_LineNDStatus == ND_USED_IN_EXT) {
							NCU_ND_SetCallDetectedStatus();
						}
					}
#endif
#endif /* defined (KEISATSU) */
					NCUStatus |=  DETECT_CALL;
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/12 */
					TxTelephoneOperationTaskMsg.Message = OK_CONT;
					snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
 #endif /* defined (KEISATSU) */
					/*---------------------------------*/
					/** メイン・タスクへ着信検出を通知 */
					/*---------------------------------*/
					if( DETECT_CALLED_REQUEST_EXT == RxTelephoneOperationTaskMsg->Message ){
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_CALL_TO_FAX_EXT;
					}
					else{
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_F_NET_EXT;
					}
					snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
					rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
					break;
														/*-----------------------------*/
				case	DETECT_CALLED_REQUEST		:	/**       着信検出の場合       */
				case	DETECT_F_NET_CALLED_SIGNAL	:	/** Ｆ網(1300Hz)着信検出の場合 */
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
#if (PRO_NUMBER_DISPLAY == ENABLE)
					if (DEBUG_NumberDisplay) {
						if (SYS_LineNDStatus == ND_USED_IN_STD) {
							NCU_ND_SetCallDetectedStatus();
						}
					}
					else {
						NCU_ND_InitializeStatus();
					}
#endif
#endif /* defined (KEISATSU) */
														/*-----------------------------*/
					NCUStatus |=  DETECT_CALL;
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/12 */
					TxTelephoneOperationTaskMsg.Message = OK_CONT;
					snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
 #endif /* defined (KEISATSU) */
					/*---------------------------------*/
					/** メイン・タスクへ着信検出を通知 */
					/*---------------------------------*/
					if( DETECT_CALLED_REQUEST == RxTelephoneOperationTaskMsg->Message ){
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_CALL_TO_FAX;
					}
					else{
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_F_NET;
					}
					snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
					rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
					break;
				default:
					break;
				}
				break;
#endif
			default:

				break;
		}
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[TelephoneOperationTask終了処理ルーチン]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		必ず入力してください
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		TelephoneOperationTaskExit( void )
{
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/20 */
	MESSAGE_t				*RxTelephoneOperationTaskMsg;
	
	/*-------------------*/
	/** 使用変数の初期化 */
	/*-------------------*/
	TxTelephoneOperationTaskMsg.Item			 = FROM_NCU_TELEPHONEOPERATIONTASK;
#endif /* defined (KEISATSU) */
	if( tskno_TelephoneExecuteTask != 0xFFFF ){
		del_tsk(&tskno_TelephoneExecuteTask);
	}
	if( tskno_TelephoneHookCheckTask != 0xFFFF ){
		del_tsk(&tskno_TelephoneHookCheckTask);
	}
	if( tskno_FaxTadAutoSwitchTask != 0xFFFF ){
		del_tsk(&tskno_FaxTadAutoSwitchTask);
	}
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/27 */
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/14 */
	if ( !(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK)) ) {	/* 付属電話はフフックではない */
		NCU_HdstShift();
	}
	IsDailing = FALSE;
	/* 転送受信の確認音仕様 Modify by Smuratec 李 2005/10/12 */
	TADStatus &= ~REMOTE_RECEIVE;
 #else /* defined (KEISATSU) */
	if (tskno_DetectCalledTask != 0xFFFF) {
		del_tsk(&tskno_DetectCalledTask);
	}
 #endif /* defined (KEISATSU) */
#endif
#if (PRO_REMOTE_RX == ENABLE)	/* 1998/01/24  By T.Yamaguchi */
	if( tskno_RemoteRxSignalDetTask != 0xFFFF ){
		del_tsk(&tskno_RemoteRxSignalDetTask);
	}
#elif (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
 #if (PRO_MODEM == R288F)
	if( tskno_RemoteRxSignalDetTask != 0xFFFF ){
		del_tsk(&tskno_RemoteRxSignalDetTask);
	}
	OneDigitDiallingExecute = 0;
	DspRamAccessWriteMethod3(0x0B3C, BackupReceiveLevel, 0x0000);
	NCU_IsDetRemotePulse = 0;
	NCU_IsRemotePulseRx = 0;
 #endif
#endif
#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
	if ( ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE)			 /* 拡張回線は本体で使用している時 */
		 || ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT)	 /* 拡張回線は送話中 */
		 || ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE) ){ /* 拡張回線は受話中 */
		NCU_LineStatus &= ~EXT_LINE_STATUS;
		NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_NOT_USE);
	}
	if ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE)		 /* 標準回線は本体で使用している時 */
		 || ((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_TRANSMIT)	 /* 標準回線は送話中 */
		 || ((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE) ){ /* 標準回線は受話中 */
		NCU_LineStatus &= ~STD_LINE_STATUS;
		NCU_LineStatus  |=  (STD_LINE_STATUS & STD_NOT_USE);
	}
	if (IsCiSndMsg == TRUE) {
		rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
		TxTelephoneOperationTaskMsg.Message = OK_CONT;
		snd_msg(mbxno.NCU_DetectCalledTask, &TxTelephoneOperationTaskMsg);
	}
	/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
	if (DEBUG_NumberDisplay) {
		if (IsNDSndMsg == TRUE) {
			IsNDSndMsg = FALSE;
			rcv_msg(mbxno.NCU_TelephoneOperationTask, &RxTelephoneOperationTaskMsg);
		}
	}
#endif /* defined (KEISATSU) */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[TelephoneOperationTask強制終了処理ルーチン]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		必ず入力してください
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		   NCU_TelephoneOperationExit( void )
{
#if (0) /* 1998/05/8 by T.Soneoka */
**#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
**	NCUStatus &= (~(TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK));
**#else
**	NCUStatus				 = 0;
**#endif
#else
	NCUStatus				 = 0;
#endif

	/* フックキーでダイヤル後、スタートキーを押すタイミングによって、モニタースピーカー
	** がＯＮの状態で、通信される。
	** 原因：TelephoneOperationTaskの強制終了処理で、子タスクを殺す前に、先にリレーや、モニタースピーカＯＦＦを行なっている
	** ため、TelephoneToFaxcomRelayControl()内でモニタースピーカーをＯＦＦしても、子タスク内で、ダイヤル送出後のタイムアウト
	** のメッセージを受信すると、回線モニターをＯＮするタイミングがある。NCU_TelephoneExecuteTask()/DialEndRelayControl()
	** 先に子タスクを殺してから、TelephoneToFaxcomRelayControl()を呼ぶ様に修正 2000/02/23  By T.Yamaguchi
	*/
	TelephoneOperationTaskExit();					/** 多機能電話制御モジュールの終了処理 */
	TelephoneToFaxcomRelayControl( FCM_TxRx, 0 );	/** 手動送受信の為のリレー制御 */
#if 0	/* 2000/02/24 Y.Murata NAGANOより */
//	TelephoneToFaxcomRelayControl( FCM_TxRx, 0 );	/** 手動送受信の為のリレー制御 */
//	TelephoneOperationTaskExit();					/** 多機能電話制御モジュールの終了処理 */
#endif

	SYS_HookKeyInputFlag		 = 0;
	TransferReceiveAvailableTime = 0;
	TransferReceiveFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
#else
	SYS_RingCounter				 = 0;
#endif
	SYS_RxDetectFlag			 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/26 */
	tskno_NCU_TelephoneOperation = 0xffff;
#endif
	exi_tsk();
}
