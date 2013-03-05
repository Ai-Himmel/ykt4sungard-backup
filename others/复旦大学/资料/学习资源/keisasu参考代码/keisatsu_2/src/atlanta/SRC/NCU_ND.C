/************************************************************************
*				BY:	 H.Kubo
*			  DATE:	 1998/06/22
*		 FILE NAME:	 ncu_nd.c
*	   DESCRIPTION:	 「通信前情報通知サービス」の処理
*  PUBLIC ROUTINES:	 NCU_
* PRIVATE ROUTINES:	 
*		 REFERENCE:	 SH7043 for SAKAKI
*************************************************************************/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\sh7043\define\def_mbxn.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\define\ncu_stat.h"
#include "\src\atlanta\define\ncu_pro.h"
#include "\src\atlanta\define\ncu_msg.h"
#include "\src\atlanta\ext_v\ncu_data.h"
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\cmn_nd.h"
#include "\src\atlanta\define\mntsw_e.h"
#include "\src\atlanta\define\ctry_pro.h"
#include "\src\atlanta\define\ncu_ret.h"

#if (PRO_MODEM == R288F)
 #if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)	/* 2002/01/21 T.Takagi */
  #include "\src\atlanta\mdm\fm336\define\mdm_def.h"
  #include "\src\atlanta\mdm\fm336\define\mdmnddef.h"
  #include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
  #include "\src\atlanta\mdm\r288f\define\mdm_def.h"
  #include "\src\atlanta\mdm\r288f\define\mdmnddef.h"
  #include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdmnddef.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/22 */
#include "\src\atlanta\define\sys_line.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\ext_v\man_data.h"
#endif /* defined (KEISATSU) */

#if 0 /* Changed by H.Kubo 1999/01/05 */
void NCU_ND_Make1stResponse(void);
UBYTE	NCU_ND_ReceiveInformation(UBYTE **rx_buffer_ptr, UWORD *rx_byte_ptr);
void NCU_ND_RxProcKillChildTasks(void);
void NCU_ND_RxProcedureTaskExit(void);
UBYTE NCU_ND_CheckWaitForCAR(void);
void	NCU_ND_CheckDSETask(UWORD *message_box);
void NCU_ND_InitializeVariables(void);
void NCU_ND_MakeFinalResponse(void);
void NCU_ND_SetModemDialinStatus(UBYTE din_status);
UBYTE NCU_ND_IsRxProcedureFinished(void);
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* added by H.Hirao 1999/01/12 */

#define 	NCU_ND_MAX_CAR_DETECTION	3

UWORD	tskno_ND_DetectCalledTask;

UBYTE NCU_ND_WaitForRingAfterRxRes(UBYTE car_loop, UWORD v23_signal_ending_time, UWORD rx_accepting_signal_time, UWORD mail_box, MESSAGE_t *tx_msg)
{
	MESSAGE_t tx_to_ring_task_msg; /* added by H.Kubo 1998/11/13 */
	MESSAGE_t *receive_msg;
	struct	Timer10msData_t	nd_2nd_ring_timer;
	struct	Timer10msData_t	sleep_after_ack_res_timer; /* added by H.Kubo 1998/11/25 */
	UWORD 	ci_timer;
	UBYTE 	rcv_msg_loop = 1;

#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
	if (DEBUG_NumberDisplay) {
		if (SYS_LineNDStatus == ND_USED_IN_STD) {
			cre_tsk(&tskno_ND_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_ND));
		}
		else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
			cre_tsk(&tskno_ND_DetectCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_ND));
		}
	}
	else {
		cre_tsk(&tskno_ND_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_ND));
	}
#else /* !defined (KEISATSU) */
	cre_tsk(&tskno_ND_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_ND));
#endif /* defined (KEISATSU) */
	nd_2nd_ring_timer.SendMBX		= mbxno.NCU_ND;
	nd_2nd_ring_timer.ReturnValue	= DETECT_CI_TIMEUP;
	ci_timer = CTRY_RingTable()->DetectTime;  /* ND 専用のパラメータがよい ? 1998/10/14 */

	if (timerID_ND_SleepAfterAck!= 0xff) {
		CMN_MultiTimer10msStop(&timerID_ND_SleepAfterAck);
	}
	sleep_after_ack_res_timer.SendMBX		= mbxno.NCU_ND;
	sleep_after_ack_res_timer.ReturnValue	= MSG_ND_ACK_RESPONSE_TIMEUP;
	sleep_after_ack_res_timer.Time = NCU_ND_2ndResponseTime(v23_signal_ending_time, rx_accepting_signal_time);
	CMN_MultiTimer10msStart(&timerID_ND_SleepAfterAck, &sleep_after_ack_res_timer);

	rcv_msg_loop = 1;
	do {
		nd_2nd_ring_timer.Time = ci_timer;
		CMN_MultiTimer10msStart(&timerID_ND_2ndCallTimer, &nd_2nd_ring_timer); /* CI 待ちタイマー再起動 */
		rcv_msg(mbxno.NCU_ND, &receive_msg); /* 受信処理起動メッセージ待ち */
		switch (receive_msg->Message) {
		case	DETECT_ND_CAR_CALLED_SIGNAL:
			/* もう一度一次応答処理へ戻ります。 */
			NCU_ND_Status = ND_CAR_DETECTED;
			car_loop++;
			rcv_msg_loop = 0;
			break;
		case	DETECT_RING: /* 呼出し音第一波検出 */
			CMN_DisableInterrupt();
			if (NCU_ND_Status & ND_MODEM_DIALIN_FAX_DIAL) {
 #if 0 /* メモリオーバーなどによるモデムダィヤルイン FAX 着信拒否の処理を追加。 by H.Kubo 1999/02/25 */
				NCU_ND_Status |= ND_CALL_ACCEPTED; /* NCU_Task でセットします。 */
 #endif
				tx_msg->Message = DETECT_MODEM_DIALIN_FAX_CALL;
			}
			else {
				tx_msg->Message = DETECT_2ND_RING;
			}
			NCU_ND_Status |= ND_COUNTING_2ND_RING;
			NCU_ND_Status &= ~(ND_WAIT_FOR_2ND_RING | ND_DETECT_CI_AFTER_RX_RES);
			SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
			CMN_EnableInterrupt();
			rcv_msg_loop = 0;
			car_loop = 0; /* added by H.Kubo 1998/11/16 */
			break;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
		case	DETECT_CALLED_REQUEST_EXT:	/** 拡張ライン着信検出の場合 */
		case	DETECT_F_NET_CALLED_SIGNAL_EXT:	/** 拡張ライン(1300Hz)着信検出の場合 */
#endif
		case	DETECT_CALLED_REQUEST		:	/**       着信検出の場合       */
		case	DETECT_F_NET_CALLED_SIGNAL	:	/** Ｆ網(1300Hz)着信検出の場合 */
												/*-----------------------------*/
		/* 通常の着信処理へ。 */
			tx_msg->Message = receive_msg->Message;
			CMN_DisableInterrupt();
			NCU_ND_Status |= ND_COUNTING_2ND_RING;
			NCU_ND_Status &= ~(ND_WAIT_FOR_2ND_RING | ND_DETECT_CI_AFTER_RX_RES);
			SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
			CMN_EnableInterrupt();
			rcv_msg_loop = 0;
			car_loop = 0; /* added by H.Kubo 1998/11/16 */
			break;
		case	DETECT_CI					:	/**       ＣＩ検出の場合       */
		case	DETECT_CI_TIMEUP			:	/** ＣＩ検出ＴｉｍｅＵｐの場合 */
#if 0 /* ここでやったらだめ。 receive_msg の内容が変わるかもしれない。 by H.Kubo 1999/02/25 */
@			if (receive_msg->Item == FROM__NCU_RING) { /* タイマータスクには返事しない。 1998/10/16 */
@#if 0 /* 他と共有すると気持ち悪い。 changed by H.Kubo 1998/11/13 */
@@@				transmit_msg.Message = OK_CONT;
@@@				snd_msg(mbxno.NCU_DetectCalledTask, &tx_to_ring_task_msg); /* TxNCUTaskMsg => transmit_msg by H.Kubo 1998/11/13 */
@#else
@				tx_to_ring_task_msg.Item = FROM_NCU_TASK;
@				tx_to_ring_task_msg.Message = OK_CONT;
@				snd_msg(mbxno.NCU_DetectCalledTask, &tx_to_ring_task_msg); /* TxNCUTaskMsg => transmit_msg by H.Kubo 1998/11/13 */
@#endif
@			}
#endif
			if(receive_msg->Message == DETECT_CI){
				NCUStatus |= DETECT_CI_STATE;
				tx_msg->Message = DETECT_CI; /* MSG_DETECT_CI is changed by H.Kubo 1998/11/25 */
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
				if (DEBUG_NumberDisplay) {
					IsNDSndMsg = TRUE;
					if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
						snd_msg(mbxno.NCU_TelephoneOperationTask, tx_msg);
					}
					else {
						snd_msg(mail_box, tx_msg);
					}
					if (!IsNDSndMsg) {
						wai_tsk(50); /* タスクにメッセージ送出を待ち */
						if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
							snd_msg(mbxno.NCU_TelephoneOperationTask, tx_msg);
						}
						else {
							snd_msg(mail_box, tx_msg);
						}
					}
					IsNDSndMsg = FALSE;
				}
				else {
					snd_msg(mail_box, tx_msg);
				}
#else /* !defined (KEISATSU) */
				snd_msg(mail_box, tx_msg);
#endif /* defined (KEISATSU) */
				CMN_DisableInterrupt(); /* CI 検出では、タイマー時間をリセットしません。 1998/10/16 */
				if ( ci_timer > ((UWORD) (SYS_GeneralTimer - rx_accepting_signal_time)) ) {
					ci_timer -= (UWORD) (SYS_GeneralTimer - rx_accepting_signal_time);
				}
				else { /* TIMEUP の処理。 1998/10/26 */
					NCUStatus &= ~DETECT_CI_STATE;
					tx_msg->Message = DETECT_2ND_RING_TIMEUP; /*DETECT_CI_TIMEUP; */ /* MSG_DETECT_CI_TIMEUPis changed by H.Kubo 1998/11/25 */
					rcv_msg_loop = 0;
					car_loop = 0; /* added by H.Kubo 1998/11/16 */
				}
				CMN_EnableInterrupt();
			}
			else{
				NCUStatus &= ~DETECT_CI_STATE;
				tx_msg->Message = DETECT_2ND_RING_TIMEUP; /* DETECT_CI_TIMEUP; */ /* MSG_DETECT_CI_TIMEUP is changed by H.Kubo 1998/11/25 */
				rcv_msg_loop = 0;
				car_loop = 0; /* added by H.Kubo 1998/11/20 */
			}
			/* Moved from above by H.Kubo 1999/02/25 */
			if (receive_msg->Item == FROM__NCU_RING) { /* タイマータスクには返事しない。 1998/10/16 */
				tx_to_ring_task_msg.Item = FROM_NCU_TASK;
				tx_to_ring_task_msg.Message = OK_CONT;
				snd_msg(mbxno.NCU_DetectCalledTask, &tx_to_ring_task_msg); /* TxNCUTaskMsg => transmit_msg by H.Kubo 1998/11/13 */
			}
			break;
		case MSG_ND_ACK_RESPONSE_TIMEUP: /* added by H.Kubo 19998/11/25 */
			if (receive_msg->Item == FROM_MULTI_TIMER) {
				CMN_DisableInterrupt();
				NCU_ND_Status &= ~ND_SLEEP_AFTER_ACK_RESPONSE;
				/*  ND 二次応答禁止期間終了検出では、タイマー時間をリセットしません。 Added by H.Kubo 1998/12/05 */
				if ( ci_timer > ((UWORD) (SYS_GeneralTimer - rx_accepting_signal_time)) ) {
					ci_timer -= (UWORD) (SYS_GeneralTimer - rx_accepting_signal_time);
				}
				else { /* TIMEUP の処理。 1998/10/26 */
					NCUStatus &= ~DETECT_CI_STATE;
					tx_msg->Message = DETECT_2ND_RING_TIMEUP; /*DETECT_CI_TIMEUP; */ /* MSG_DETECT_CI_TIMEUPis changed by H.Kubo 1998/11/25 */
					rcv_msg_loop = 0;
					car_loop = 0; /* added by H.Kubo 1998/11/16 */
				}
				CMN_EnableInterrupt();
			}
			break;
		default: /* ここにはこないはず */
			tx_msg->Item = FROM_NCU_TASK;
			tx_msg->Message = FAIL_ND_NUMBER_RX;
			car_loop = 0; /* added by H.Kubo 1998/11/16 */
			break;
		}
		/* 何がきても、タイマーは止めます。 */
		if (timerID_ND_2ndCallTimer != 0xff) {
			CMN_MultiTimer10msStop(&timerID_ND_2ndCallTimer);
		}
	} while (rcv_msg_loop);
	NCU_ND_WaitFor2ndResponseTime(v23_signal_ending_time, rx_accepting_signal_time);
	if (tskno_ND_DetectCalledTask != 0xffff) { /* if is added by H.Kubo 1998/11/25 */
		del_tsk(&tskno_ND_DetectCalledTask);
	}
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
	if (DEBUG_NumberDisplay) {
		if (SYS_LineNDStatus == ND_USED_IN_STD) {
			if (tskno_DetectCalledTask == 0xFFFF) {
				cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
			}
		}
		else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
			if (tskno_Detect2ndCalledTask == 0xFFFF) {
				cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
			}
		}
	}
#endif /* defined (KEISATSU) */
	if (timerID_ND_2ndCallTimer != 0xff) {
		CMN_MultiTimer10msStop(&timerID_ND_2ndCallTimer);
	}
	if (timerID_ND_SleepAfterAck!= 0xff) {
		CMN_MultiTimer10msStop(&timerID_ND_SleepAfterAck);
	}
	CMN_DisableInterrupt();
	SYB_ND_CarPattern[SYS_ND_LAST_NCU_ND_STATUS] = NCU_ND_Status; /* added by H.Kubo 1998/11/25 */
	NCU_ND_Status &= ~(ND_SLEEP_AFTER_ACK_RESPONSE | ND_WAIT_FOR_2ND_RING | ND_DETECT_CI_AFTER_RX_RES); /* changed by H.Kubo 1998/11/25 */
	SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
	CMN_EnableInterrupt();
	return car_loop;
}


/*************************************************************************
	module		:[ナンバーディスプレイ受信処理タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/08]
	author		:[久保博]
*************************************************************************/
void NCU_ND_RxProcedureTask(WORD *mailbox)
{
	MESSAGE_t transmit_msg;
	MESSAGE_t *receive_msg;
	UBYTE	*rx_buffer;
	UWORD	v23_signal_ending_time;
	UWORD	rx_accepting_signal_time;
	UWORD	rx_byte;
	UBYTE car_loop_counter = 0;
	UBYTE dialin_status;
	UBYTE	v23_rx_status;

	NCU_ND_InitializeVariables(); /* added by H.Kubo 1998/10/27 */

	rcv_msg(mbxno.NCU_ND, &receive_msg); /* 受信処理起動メッセージ待ち */

	if (SYB_MaintenanceSwitch[MNT_SW_E6] & ND_RX_SPEAKER_ON) {
		MonitorSpeakerOn(); /* モニタースピーカーＯＮ*/
	}

#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
	ModemRelay_Off();	/**	モデムリレーOFF	*/
#endif /* defined (KEISATSU) */

	/*** ナンバーディスプレイ情報受信開始 ***/
	do {
		/* 情報受信処理 */
		switch ((v23_rx_status = NCU_ND_ReceiveInformation(&rx_buffer, &rx_byte))) {
		case ND_V23_DATA_RECEIVED:

#if (0)
** 			/* T-340 ファネット指摘項目（No.15)
** 			** ナンバーディスプレーで網側から送られてくるデータが「42,03,13,01,30」の場合、先頭の"42"は無鳴動情報通知サービス（Ｌモードのメッセージ消去通知）
** 			** を示すものであるが、この値を判断せずにモデムでNDデータが受信できればなんでも処理していた。
** 			** 現状実装しているNDは「発信者番号通知」にしか対応しておらずそれ以外のパターンに対してはノーガードである。
** 			** =>対策としては「発信者情報通知」データ以外のNDデータを受信した場合は有効データを受信できなかったということで捨てることにする。
** 			**   今後、村田として「ネームディスプレー」等に対応する場合は更なる対策が必要となるのでそのときは注意が必要！   By O.Kimoto 2002/11/01
** 			*/
** 			NCU_ND_Status |= ND_INFO_RECEIVED;
** 			v23_signal_ending_time = SYS_GeneralTimer;
** 			/* 受信したデータ列を解析し、電話番号情報などを取り出す。*/
** 			SYS_ND_CurrentJournalPoint = CMN_ND_AnalizeRxInformation(rx_buffer, rx_byte, &dialin_status);
** 			NCU_ND_SetModemDialinStatus(dialin_status);
** 			/* 親タスクにメッセージ送出 (発呼番号表示などのため) */
** 			transmit_msg.Item = FROM_NCU_TASK;
** 			transmit_msg.Message = DETECT_ND_NUMBER;
** 			snd_msg(*mailbox, &transmit_msg);
** 			rcv_msg(mbxno.NCU_ND, &receive_msg); /* NCU タスクとの同期  */
#else
			if (CMN_ND_GetMessageLengthIndex(rx_buffer, rx_byte) == 0 ) {
				/* 空の着信履歴データをセットします */
				SYS_ND_CurrentJournalPoint = CMN_ND_SetV23ErrorHistory(ND_V23_ILLEGAL_FORMAT);
			}
			else {
				NCU_ND_Status |= ND_INFO_RECEIVED;
				v23_signal_ending_time = SYS_GeneralTimer;
				/* 受信したデータ列を解析し、電話番号情報などを取り出す。*/
				SYS_ND_CurrentJournalPoint = CMN_ND_AnalizeRxInformation(rx_buffer, rx_byte, &dialin_status);
				NCU_ND_SetModemDialinStatus(dialin_status);
				/* 親タスクにメッセージ送出 (発呼番号表示などのため) */
				transmit_msg.Item = FROM_NCU_TASK;
				transmit_msg.Message = DETECT_ND_NUMBER;
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
				if (DEBUG_NumberDisplay) {
					IsNDSndMsg = TRUE;
					if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
						snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
					}
					else {
						snd_msg(*mailbox, &transmit_msg);
					}
					if (!IsNDSndMsg) {
						wai_tsk(50); /* タスクにメッセージ送出を待ち */
						if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
							snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
						}
						else {
							snd_msg(*mailbox, &transmit_msg);
						}
					}
					IsNDSndMsg = FALSE;
				}
				else {
					snd_msg(*mailbox, &transmit_msg);
				}
#else /* !defined (KEISATSU) */
				snd_msg(*mailbox, &transmit_msg);
#endif /* defined (KEISATSU) */
				rcv_msg(mbxno.NCU_ND, &receive_msg); /* NCU タスクとの同期  */
			}
#endif

			break;
		case ND_V23_TONE_NOT_DETECTED:
		case ND_V23_ABORT:
		case ND_V23_RECEIVE_ERROR:
		case ND_V23_ILLEGAL_FORMAT:
		case ND_V23_TONE_WITH_NO_DATA:
		default:
			/* 空の着信履歴データをセットします */
			SYS_ND_CurrentJournalPoint = CMN_ND_SetV23ErrorHistory(v23_rx_status);
			break;
		}
#if 0 /* changed by H.Kubo 1998/11/21 */
@@		NCU_ND_MakeFinalResponse(); 		/* 受信完了処理信号送出 */
#else
		if (!NCU_ND_MakeAckResponse()) { 	/* 受信完了処理信号送出 */
			/* 受信完了信号を送出せず、着信拒否し場合 */
			transmit_msg.Item = FROM_NCU_TASK;
			transmit_msg.Message = IGNORE_ND_INFO_ARRIVAL;
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
			if (DEBUG_NumberDisplay) {
				IsNDSndMsg = TRUE;
				if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
					snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
				}
				else {
					snd_msg(*mailbox, &transmit_msg);
				}
				if (!IsNDSndMsg) {
					wai_tsk(50); /* タスクにメッセージ送出を待ち */
					if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
						snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
					}
					else {
						snd_msg(*mailbox, &transmit_msg);
					}
				}
				IsNDSndMsg = FALSE;
			}
			else {
				snd_msg(*mailbox, &transmit_msg);
			}
#else /* !defined (KEISATSU) */
			snd_msg(*mailbox, &transmit_msg);
#endif /* defined (KEISATSU) */
			wai_tsk(0xffff);
		}
#endif
		rx_accepting_signal_time = SYS_GeneralTimer;
#if 0 /* Moved to inside of NCU_ND_MakeAckResponse() by H.Kubo 1998/11/23 */
@		CMN_DisableInterrupt();
@		NCU_ND_Status |= ND_WAIT_FOR_2ND_RING;
@		NCU_ND_Status &= ~ND_BEFORE_INFO_RECEIVED;
@		SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
@		/* CI の状態を初期化 */
@		RingStatus &= ~CI_ON;
@	
@		/* 受信完了信号から 0.3 秒、情報受信から 0.6 秒待たなくてはいけないのですが、 
@		** 呼出音検出でそれ以上かかるので、とくに何もしません。
@		*/
@		/* 呼出し音待ち。*/
@		SYS_RingCounter = 0;
@
@		CMN_EnableInterrupt();
#endif
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/22 */
		if (DEBUG_NumberDisplay) {
			if (SYS_LineNDStatus == ND_USED_IN_STD) {
				if ((NCUStatus & TELEPHONE1_OFF_HOOK) 
					|| ((NCUStatus & HOOK_KEY_ON_STATE) && CHK_LineSetting())) { 
					/* すぐに電話を取るときは、二次応答まで明示的に待ち時間処理が必要。 */
					NCU_ND_WaitFor2ndResponseTime(v23_signal_ending_time, rx_accepting_signal_time);
					transmit_msg.Item = FROM_NCU_TASK;
					if (NCUStatus & HOOK_KEY_ON_STATE) {
						transmit_msg.Message = DETECT_INPUT_HOOK_KEY;
						H_RelayOff(); /* by H.Kubo 1998/11/27 */
					}
					else if (NCUStatus & TELEPHONE1_OFF_HOOK) {
						transmit_msg.Message = DETECT_TEL1_OFF_HOOK;
						H_RelayOff(); /* by H.Kubo 1998/11/27 */
					}
					else {
						transmit_msg.Message = DETECT_ND_NUMBER;
					}
					IsNDSndMsg = TRUE;
					if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
						if (transmit_msg.Message == DETECT_INPUT_HOOK_KEY) {
							NCUStatus &= ~HOOK_KEY_ON_STATE;
						}
						snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
					}
					else {
						snd_msg(*mailbox, &transmit_msg);
					}
					if (!IsNDSndMsg) {
						wai_tsk(50); /* タスクにメッセージ送出を待ち */
						if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
							snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
						}
						else {
							if (transmit_msg.Message == DETECT_INPUT_HOOK_KEY) {
								NCUStatus |= HOOK_KEY_ON_STATE;
							}
							snd_msg(*mailbox, &transmit_msg);
						}
					}
					IsNDSndMsg = FALSE;
					rcv_msg(mbxno.NCU_ND, &receive_msg); /* NCU タスクとの同期  */
				}
			}
			else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
				if ((NCUStatus & TELEPHONE2_OFF_HOOK) 
					|| ((NCUStatus & HOOK_KEY_ON_STATE) && !CHK_LineSetting())) {
					/* すぐに電話を取るときは、二次応答まで明示的に待ち時間処理が必要。 */
					NCU_ND_WaitFor2ndResponseTime(v23_signal_ending_time, rx_accepting_signal_time);
					transmit_msg.Item = FROM_NCU_TASK;
					if (NCUStatus & HOOK_KEY_ON_STATE) {
						transmit_msg.Message = DETECT_INPUT_HOOK_KEY;
						L_RelayOff(); /* by H.Kubo 1998/11/27 */
					}
					else if (NCUStatus & TELEPHONE2_OFF_HOOK) {
						transmit_msg.Message = DETECT_TEL2_OFF_HOOK;
						L_RelayOff(); /* by H.Kubo 1998/11/27 */
					}
					else {
						transmit_msg.Message = DETECT_ND_NUMBER;
					}
					IsNDSndMsg = TRUE;
					if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
						if (transmit_msg.Message == DETECT_INPUT_HOOK_KEY) {
							NCUStatus &= ~HOOK_KEY_ON_STATE;
						}
						snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
					}
					else {
						snd_msg(*mailbox, &transmit_msg);
					}
					if (!IsNDSndMsg) {
						wai_tsk(50); /* タスクにメッセージ送出を待ち */
						if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
							snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
						}
						else {
							if (transmit_msg.Message == DETECT_INPUT_HOOK_KEY) {
								NCUStatus |= HOOK_KEY_ON_STATE;
							}
							snd_msg(*mailbox, &transmit_msg);
						}
					}
					IsNDSndMsg = FALSE;
					rcv_msg(mbxno.NCU_ND, &receive_msg); /* NCU タスクとの同期  */
				}
			}
		}
		else {
			if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK | HOOK_KEY_ON_STATE)) { /* added by H.Kubo 1998/11/21 */
				/* すぐに電話を取るときは、二次応答まで明示的に待ち時間処理が必要。 */
				NCU_ND_WaitFor2ndResponseTime(v23_signal_ending_time, rx_accepting_signal_time);
				transmit_msg.Item = FROM_NCU_TASK;
				if (NCUStatus & HOOK_KEY_ON_STATE) {
					transmit_msg.Message = DETECT_INPUT_HOOK_KEY;
					H_RelayOff(); /* by H.Kubo 1998/11/27 */
					L_RelayOff(); /* by H.Kubo 1998/11/27 */
				}
				else if (NCUStatus & TELEPHONE1_OFF_HOOK) {
					transmit_msg.Message = DETECT_TEL1_OFF_HOOK;
					H_RelayOff(); /* by H.Kubo 1998/11/27 */
				}
				else if (NCUStatus & TELEPHONE2_OFF_HOOK) {
					transmit_msg.Message = DETECT_TEL2_OFF_HOOK;
					L_RelayOff(); /* by H.Kubo 1998/11/27 */
				}
				else {
					transmit_msg.Message = DETECT_ND_NUMBER;
				}
				snd_msg(*mailbox, &transmit_msg);
				rcv_msg(mbxno.NCU_ND, &receive_msg); /* NCU タスクとの同期  */
			}
		}
#else /* !defined (KEISATSU) */
		if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK | HOOK_KEY_ON_STATE)) { /* added by H.Kubo 1998/11/21 */
			/* すぐに電話を取るときは、二次応答まで明示的に待ち時間処理が必要。 */
			NCU_ND_WaitFor2ndResponseTime(v23_signal_ending_time, rx_accepting_signal_time);
			transmit_msg.Item = FROM_NCU_TASK;
			if (NCUStatus & HOOK_KEY_ON_STATE) {
				transmit_msg.Message = DETECT_INPUT_HOOK_KEY;
				H_RelayOff(); /* by H.Kubo 1998/11/27 */
				L_RelayOff(); /* by H.Kubo 1998/11/27 */
			}
			else if (NCUStatus & TELEPHONE1_OFF_HOOK) {
				transmit_msg.Message = DETECT_TEL1_OFF_HOOK;
				H_RelayOff(); /* by H.Kubo 1998/11/27 */
			}
			else if (NCUStatus & TELEPHONE2_OFF_HOOK) {
				transmit_msg.Message = DETECT_TEL2_OFF_HOOK;
				L_RelayOff(); /* by H.Kubo 1998/11/27 */
			}
			else {
				transmit_msg.Message = DETECT_ND_NUMBER;
			}
			snd_msg(*mailbox, &transmit_msg);
			rcv_msg(mbxno.NCU_ND, &receive_msg); /* NCU タスクとの同期  */
		}
#endif /* defined (KEISATSU) */

		if (!NCU_ND_SilentAfterAckResponse()) { /* IR or CAR がはっきりする前にベルを鳴らす by H.Kubo 1998/11/27 */
			NCU_ND_AfterNdRxRelaySetting();
		}
		/* 受信応答したらすぐに終了し、通常の着信処理に移行する場合。 */
		if (NCU_ND_IsRxProcedureFinished()) {
			NCU_ND_WaitFor2ndResponseTime(v23_signal_ending_time, rx_accepting_signal_time);
			CMN_DisableInterrupt();
			NCU_ND_Status |= ND_COUNTING_2ND_RING;
			NCU_ND_Status &= ~(ND_WAIT_FOR_2ND_RING| ND_DETECT_CI_AFTER_RX_RES);
			SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
			CMN_EnableInterrupt();
			car_loop_counter = 0; /* added by H.Kubo 1998/11/18 */
			transmit_msg.Message = MADE_ND_RX_RESPONSE;
#if 0 /* Deleted by H.Kubo 1998/11/18 */
@@			snd_msg(*mailbox, &transmit_msg);
@@
@@			wai_tsk(CTRY_RingTable()->DetectTime);
@@			transmit_msg.Message = DETECT_2ND_RING_TIMEUP;
@@			snd_msg(*mailbox, &transmit_msg); 
@@			wai_tsk(0xffff); /* ND 情報受信手順終了 */
#endif
		}
		else {
			/*  無鳴動着信でもTEL2 に IR を供給する added by H.Kubo 1998/11/28 */
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/22 */
			if (DEBUG_NumberDisplay) {
				if (CHK_NumberDisplayByExtPhoneON() && (SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & SYS_ND_SUPPLY_FIRST_IR)) {
						if (SYS_LineNDStatus == ND_USED_IN_STD) {
							RelayPortStatus |= IO_BIT_L; /* 外付電話を回線から分離にします */
							OutputWORD(GA_PGADR, RelayPortStatus);
						}
						else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
							IO__PADRL |= IO_BIT_K_L;  /* 外付電話を回線から分離にします */
					}
				}
			}
			else {
 #if 0 /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/30 */
@@				if (CHK_NumberDisplayByExtPhoneON() && (SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & SYS_ND_SUPPLY_FIRST_IR)) {
@@					L_RelayOff();
@@				}
 #else
				if (CHK_NumberDisplayByExtPhoneON() && (SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & SYS_ND_SUPPLY_FIRST_IR)) {
					H_RelayOff();
				}
 #endif
			}
#else /* !defined (KEISATSU) */
			if (CHK_NumberDisplayByExtPhoneON() && (SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & SYS_ND_SUPPLY_FIRST_IR)) {
				L_RelayOff();
			}
#endif /* defined (KEISATSU) */
			car_loop_counter = NCU_ND_WaitForRingAfterRxRes(car_loop_counter, v23_signal_ending_time, rx_accepting_signal_time, *mailbox, &transmit_msg);
		}
	} while ((car_loop_counter > 0) && (NCU_ND_MAX_CAR_DETECTION > car_loop_counter));

	if (NCU_ND_MAX_CAR_DETECTION <= car_loop_counter) {
		/* こんなに CAR が来るなんて、何か間違っている。 */
		transmit_msg.Message = DETECT_2ND_RING_TIMEUP; /* 強制終了 */
	}

	if (NCU_ND_SilentAfterAckResponse()) { /* IR or CAR がはっきりした時点でベルを鳴らす added by H.Kubo 1998/11/27 */
		NCU_ND_AfterNdRxRelaySetting();
	}

#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
	if (DEBUG_NumberDisplay) {
		IsNDSndMsg = TRUE;
		if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
			snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
		}
		else {
			snd_msg(*mailbox, &transmit_msg);
		}
		if (!IsNDSndMsg) {
			wai_tsk(50); /* タスクにメッセージ送出を待ち */
			if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
				snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
			}
			else {
				snd_msg(*mailbox, &transmit_msg);
			}
		}
		IsNDSndMsg = FALSE;
	}
	else {
		snd_msg(*mailbox, &transmit_msg);  /* NCU_DetectCalldedTask を殺してからメッセージを送る。 */
	}
#else /* !defined (KEISATSU) */
	snd_msg(*mailbox, &transmit_msg);  /* NCU_DetectCalldedTask を殺してからメッセージを送る。 */
#endif /* defined (KEISATSU) */



	/* ２波目以降の検出を中断するタイマー。 */
#if 0 /* 一波目の呼出し音の後、 CI が来なかった時のCI 待ちタイマーが長すぎた。Changed by H.Kubo 1998/11/20 */
@@	wai_tsk(CTRY_RingTable()->DetectTime);
#else
	wai_tsk(((UWORD) SYB_ND_CarPattern[SYS_ND_IR_STOP_DETECTION_TIMER]) * 10);
#endif
	transmit_msg.Message = DETECT_2ND_RING_TIMEUP;
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
	if (DEBUG_NumberDisplay) {
		IsNDSndMsg = TRUE;
		if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
			snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
		}
		else {
			snd_msg(*mailbox, &transmit_msg);
		}
		if (!IsNDSndMsg) {
			wai_tsk(50); /* タスクにメッセージ送出を待ち */
			if (tskno_NCU_TelephoneOperation != 0xFFFF ) {
				snd_msg(mbxno.NCU_TelephoneOperationTask, &transmit_msg);
			}
			else {
				snd_msg(*mailbox, &transmit_msg);
			}
		}
		IsNDSndMsg = FALSE;
	}
	else {
		snd_msg(*mailbox, &transmit_msg);  /* NCU_DetectCalldedTask を殺してからメッセージを送る。 */
	}
#else /* !defined (KEISATSU) */
	snd_msg(*mailbox, &transmit_msg);  /* NCU_DetectCalldedTask を殺してからメッセージを送る。 */
#endif /* defined (KEISATSU) */

	wai_tsk(0xffff);
}


/*************************************************************************
	module		:[外付けナンバーディスプレイ対応電話の一次応答の OH2 の監視]
	function	:[
			(timer * 10) ms が経過するまで OH2 を監視。
	]
	common		:[
	]
	condition	:[]
	comment		:[
	]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/21]
	author		:[久保博]
*************************************************************************/
UBYTE NCU_ND_CheckOH2(UWORD timer, UWORD oh_times)
{
	UBYTE i;
	i = 0;
	do {
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/22 */
		if (SYS_LineNDStatus == ND_USED_IN_STD) {
			if (OffHook2()) {
				if (++i > oh_times) {
					return TRUE;
				}
			}
			else {
				i = 0;
			}
		}
		else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
			if (OffHook3()) {
				if (++i > oh_times) {
					return TRUE;
				}
			}
			else {
				i = 0;
			}
		}
		else {
			return FALSE;
		}
#else /* !defined (KEISATSU) */
		OhPortStatusRead();
		if (OhPortStatus & TEL2_OFF_HOOK) {
			if (++i > oh_times) {
				return TRUE;
			}
		}
		else {
			i = 0;
		}
#endif /* defined (KEISATSU) */
		wai_tsk(10/10);
	} while (timer-- > 0);
	return FALSE;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[Number Display 一次応答処理]
	function	:[
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/07/03]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void NCU_ND_Make1stResponse(void)
{
	if (CHK_NumberDisplayByExtPhoneON()) {
#if 0 /*(PRO_MODEM == R288F)  */ /* Moved from upper task by H.Kubo 1998/10/29 */ /* moved by H.Kubo 1998/11/20 */
@@		AnalogSwitchTONE_Set(); /* R288F モデムの入力を TONE にする。*/
#endif
		/* 外付け ND 電話の一次応答はここに来るまでに OH 検出によって終了していますので、時刻の記録だけします。 */
		AfterCI_TimerSet(); /* added by H.Kubo 1998/10/26 */
		NCU_ND_FirstResponseTime = SYS_GeneralTimer; /* 一次応答送出時刻を記憶。 H.Kubo 1998/10/06 */
	}
	else {
#if 0 /* (PRO_MODEM == R288F) */  /* Moved from upper task by H.Kubo 1998/10/29 */ /* moved by H.Kubo 1998/11/20 */
@@		AnalogSwitchRXA_Set();					/* R288F モデムの入力を RXA にする。*/
#endif
		AfterCI_TimerSet();
		H_RelayOn();
 #if !defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Deleted by SMuratec 李 2005/12/06 */
		L_RelayOn();
 #endif /* defined (KEISATSU) */
		CML_RelayOn();	/** 直流ループ閉結 == 一次応答 */
		NCU_ND_FirstResponseTime = SYS_GeneralTimer; /* 一次応答送出時刻を記憶。 H.Kubo 1998/10/06 */
		wai_tsk(100/10); 	/* V23 フィルタ誤動作防止用タイマー。 どうせ 100ms は V23 信号が来ないのでこれでよい。 */
	}
	return;
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[Number Display 一次応答から受信応答までの処理]
	function	:[
	]
	return		:[
			ナンバーディスプレイ情報受信状態
	]
	common		:[
		NCU_ND_Status
		SYB_ND_CarPattern
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/07/03]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	NCU_ND_ReceiveInformation(UBYTE **rx_buffer_ptr, UWORD *rx_byte_ptr)
{
	MESSAGE_t	*message_ptr;
	UWORD	first_response_time;
	UBYTE 	loop;
	UBYTE 	is_v23opened;
	UBYTE	is_v23_rx_successful;

	
	struct ToneDetectMailBoxData_t	v23_tone;
	struct ToneDetectMailBoxData_t	busy_tone;
	struct	Timer10msData_t			v23_arrival_timeup;
	
	loop = TRUE;
	is_v23opened = FALSE;
	is_v23_rx_successful = FALSE;

	v23_tone.SendMBX = mbxno.NCU_ND;
	v23_tone.ToneType = V23_TONE;
	busy_tone.SendMBX = mbxno.NCU_ND;
	busy_tone.ToneType = BUSYTONE;


#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
	if (CHK_NumberDisplayByExtPhoneON()) { /* Moved from NCU_ND_Make1stResponse by H.Kubo 1998/11/20 */
		AnalogSwitchTONE_Set(); /* R288F モデムの入力を TONE にする。*/
	}
	else {
		AnalogSwitchRXA_Set();					/* R288F モデムの入力を RXA にする。*/
	}

	/* MDM_ToneModeConfig(); */ /* R288F の 7200Hz のサンプリング周波数にする。 */ /* Deleted by H.Kubo 1998/10/29 */
	if (CHK_NumberDisplayByExtPhoneON()
	|| (SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_SKIP_V23_TONE_DETEDCT)) { /* Phone2 ND 電話接続でV23 オープンが遅れる対策。changed by H.Kubo 1998/11/20 */
	}
	else {
		MDM_FilterSet(RX_V23_TONE_FILTER);		/* フィルタ設定 */
	}

	MDM_RxV23Open(); /* V23 受信準備 */
	is_v23opened = TRUE;
	/* MDM_FilterSet(RX_V23_TONE_FILTER);	*/	/* フィルタ設定 */
#else
 #error "The modem kind is not supported."
#endif

	/* 一次応答信号送出 */
	NCU_ND_Make1stResponse();

	if (CHK_NumberDisplayByExtPhoneON()
	|| (SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_SKIP_V23_TONE_DETEDCT)) { /* Phone2 ND 電話接続でV23 オープンが遅れる対策。changed by H.Kubo 1998/11/20 */
		cre_tsk(&tskno_V23RxTask, TSK_MDM_ND_RXV23TASK, &mbxno.NCU_ND);
	}
	else {
		cre_tsk(&tskno_V23ToneTask, TSK_ATD_TONEDETECTPATTERN0TASK, &v23_tone);		/*  V23 トーンの検出タスク起動 */
	}
#if 0 /* Moved to above by H.Kubo 1998/11/20 */
@@	cre_tsk(&tskno_V23ToneTask, TSK_ATD_TONEDETECTPATTERN0TASK, &v23_tone);		/*  V23 トーンの検出タスク起動 */
#endif
	cre_tsk(&tskno_BusyToneTask, TSK_ATD_TONEDETECTPATTERN1TASK, &busy_tone);	/* ビジートーン検出タスクの起動 */
	if (SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_DETECT_DSE_V23_RX) {
		cre_tsk(&tskno_DetectDseTask, TSK_NCU_ND_DETECTDSETASK, &mbxno.NCU_ND);			/* 極反検出タスク起動 */
	}

	/* 5 秒 (ダイヤルインの場合は 8 秒) タイマーの設定 */
	v23_arrival_timeup.SendMBX		= mbxno.NCU_ND;
	v23_arrival_timeup.ReturnValue	= TIMEUP;
	v23_arrival_timeup.Time = NCU_ND_GetDataTimerInterval();
	CMN_MultiTimer10msStart(&timerID_v23_arrival, &v23_arrival_timeup); 	/* V23 トーン待ちタイマ起動  */

	do {
		rcv_msg(mbxno.NCU_ND, &message_ptr);
		switch (message_ptr->Item) {
		case FROM_AUTODIAL:
			if (message_ptr->Message == V23_TONE) {		/* もし、 V23 のトーンを検出したら、 */
				/* V23 受信タスク起動 */
				if (tskno_V23RxTask == 0xffff) { /* Changed by H.Kubo 1998/11/20 */
					cre_tsk(&tskno_V23RxTask, TSK_MDM_ND_RXV23TASK, &mbxno.NCU_ND);
				}
				/* V23 トーン検出タスク終了 */
				if (tskno_V23ToneTask != 0xffff) {
					del_tsk(&tskno_V23ToneTask);
				}
				if (timerID_v23_arrival != 0xff) { /* V23 受信タスクがタイマーを持っているので、このタイマーは終了。 by H.Kubo 1998/10/26 */
					CMN_MultiTimer10msStop(&timerID_v23_arrival);
				}
				is_v23_rx_successful = ND_V23_TONE_WITH_NO_DATA;
			}
			else { /* ビジートーン検出 */
				loop = FALSE;
				is_v23_rx_successful = ND_V23_ABORT;
			}
			break;	
		case FROM_MULTI_TIMER: /* Time up */
			loop = FALSE;
			if (is_v23_rx_successful == FALSE) {
				is_v23_rx_successful = ND_V23_TONE_NOT_DETECTED;
			}
			break;
		case FROM_NCU_ND:
			loop = FALSE;
			switch (message_ptr->Message) {
			case MSG_NCU_ND_DETECT_DSE:  /* 極反 */
				is_v23_rx_successful = ND_V23_ABORT;
				break;
			case MSG_NCU_ND_RX_V23_SUCCESS:/* Rx V23 success */
				is_v23_rx_successful = ND_V23_DATA_RECEIVED;
				*rx_buffer_ptr = (UBYTE *) EcmBufferBaseWritePoint; /* 有効なデータの EcmBuffer のオフセット値 */
				*rx_byte_ptr = message_ptr->SubMessage1;
				break;
			case MSG_NCU_ND_RX_V23_FAIL: /* Rx V23 fail */
				is_v23_rx_successful = ND_V23_RECEIVE_ERROR; /* CRC エラー、パリティエラーなど */
				break;
			case ND_RX_STATUS_RX_TIMEOUT:
				is_v23_rx_successful = ND_V23_ILLEGAL_FORMAT; /* データが途中で途切れた、 <DLE><ETX> が見つからなかった */
				break;
			case MSG_NCU_ND_RX_V23_NO_DATA:
				is_v23_rx_successful = ND_V23_TONE_WITH_NO_DATA; /* データが一つも来なかった by H.Kubo 1998/10/26 */
			default:
				break;
				/* ありえない */
			}
			break;
		default:
			break;
		}
	} while (loop);

	if (is_v23opened) {
		MDM_RxV23Close();
	}
	
	NCU_ND_RxProcKillChildTasks();

	/* ECM バッファにナンバーディスプレイのデータ列を受信 */

	/* 終了状態
	** 		ND_V23_DATA_RECEIVED		受信正常終了
	** 		ND_V23_TONE_NOT_DETECTED	信号検出されず (V23  の 1300Hz トーンなし、ビジートーン検出)
	** 		ND_V23_ABORT				V23 信号が途中で途切れた (タイムアウト、ビジートーン検出)
	** 		ND_V23_ILLEGAL_FORMAT		受信データが不正なフォーマットだった、CRC エラーを起こしていた
	**
	*/
	return is_v23_rx_successful;
}

void NCU_ND_RxProcKillChildTasks(void)
{
	if (tskno_ND_DetectCalledTask != 0xffff) {
		del_tsk(&tskno_ND_DetectCalledTask);
	}
	if (tskno_V23ToneTask != 0xffff) {
		del_tsk(&tskno_V23ToneTask);
	}
	
	if (tskno_BusyToneTask != 0xffff) {
		del_tsk(&tskno_BusyToneTask);
	}
	if (tskno_DetectDseTask != 0xffff) {
		del_tsk(&tskno_DetectDseTask);
	}
	if (tskno_V23RxTask != 0xffff) {
		del_tsk(&tskno_V23RxTask);
	}
	if (timerID_v23_arrival != 0xff) {
		CMN_MultiTimer10msStop(&timerID_v23_arrival);
	}
	if (timerID_ND_2ndCallTimer != 0xff) {
		CMN_MultiTimer10msStop(&timerID_ND_2ndCallTimer);
	}
	if (timerID_ND_SleepAfterAck!= 0xff) { /* added by H.Kubo 1998/11/25 */
		CMN_MultiTimer10msStop(&timerID_ND_SleepAfterAck);
	}

}

void NCU_ND_RxProcedureTaskExit(void)
{
	NCU_ND_RxProcKillChildTasks();
	exi_tsk();
}

#if 1  /*  by H.Kubo 1998/11/21 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[Number Display 受信応答処理をしないか]
	function	:[]
	return		:[
			TRUE or FALSE
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/12/16]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE NCU_ND_SuspendAckResponse(void)
{
	if (SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & SYS_ND_ACK_WITH_OFF_HOOK) { /* added by H.Kubo 1998/11/26 */
		return FALSE; /* LCV_Status() is changed by H.Kubo 1998/11/27 */ /* TEL1, TEL2 があがっていても、受信完了応答は返す。 */
	}
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/11/23 */
	if (SYS_LineNDStatus == ND_USED_IN_STD) { /* ナンバーディスプレイ起動回線は標準回線 */
		return (LCV_Status() && ((NCU_LineStatus & STD_HDST_OFFHOOK) || (SYS_LineTelStatus & STD_TEL2_OFFHOOK)));
	}
	else if (SYS_LineNDStatus == ND_USED_IN_EXT) { /* ナンバーディスプレイ起動回線は拡張回線 */
		return (LCV_Status() && ((NCU_LineStatus & EXT_HDST_OFFHOOK) || (SYS_LineTelStatus & EXT_TEL2_OFFHOOK)));
	}
	else {
		return FALSE;
	}
 #else /* !defined (KEISATSU) */
	return (LCV_Status() && (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK | HOOK_KEY_ON_STATE)));
 #endif /* defined (KEISATSU) */
}
#endif

#if 0 /* Deleted by H.Kubo 1999/01/05 */
@/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
@	module		:[Number Display 受信応答処理]
@	function	:[
@	]
@	return		:[なし]
@	common		:[]
@	condition	:[]
@	comment		:[]
@	machine		:[SH7043]
@	language	:[SHC]
@	keyword		:[NCU]
@	date		:[1998/07/03]
@	author		:[久保博]
@++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
@void NCU_ND_MakeFinalResponse(void)
@{
@	if (CHK_NumberDisplayByExtPhoneON()) {
@		/* 外付け電話での ND 応答のときは、 OH ポートを監視します。 */
@		UWORD timer;
@		timer = (CHK_ModemDialinON()) ? ND_DIALIN_RX_RESPONSE_TIMER : ND_RX_RESPONSE_TIMER;
@		for (; timer > 0; timer--) {
@			OhPortStatusRead();
@			if (!(OhPortStatus & TEL2_OFF_HOOK)) { /* TEL2 の直流ループ断 */
@				break;
@			}
@			wai_tsk(10/10);
@		}
@		AfterCI_HL_RelayOn = 5; /* added by H.Kubo 1998/10/23 */
@		if (timer == 0) {
@			/* 自機で直流ループ断。 */
@			L_RelayOn(); /* TEL2 で直流ループを形成してたので、 TEL2 を切り離す。*/
@		}
@
@	}
@	CML_RelayOff();	/** 直流ループ開放 */
@}
#endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[Number Display 受信応答処理]
	function	:[
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/12/16]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE NCU_ND_MakeAckResponse(void)
{
	struct	Timer10msData_t			busy_tone_timeup;
	struct	Timer10msData_t			hook_check_timer;
	struct ToneDetectMailBoxData_t	busy_tone;
	MESSAGE_t	*message_ptr;
	UWORD timer;
	UBYTE timerID_hookcheck;
	UBYTE loop = TRUE;
	UBYTE rtn;
#if 0 /* 試作コード。 by H.Kubo 1998/12/16 */
	UBYTE junk_number_match;
	junk_number_match = CMN_ND_CheckJunkMail(SYS_ND_CurrentJournalPoint); /* ジャンクメール番号と照合 */
#endif
	rtn = FALSE;

	if (CHK_NumberDisplayByExtPhoneON()) {
		/* 外付け電話での ND 応答のときは、 OH ポートを監視します。 */
		UWORD timer;
		timer = (CHK_ModemDialinON()) ? ND_DIALIN_RX_RESPONSE_TIMER : ND_RX_RESPONSE_TIMER;
		for (; timer > 0; timer--) {
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/31 */
			if (SYS_LineNDStatus == ND_USED_IN_STD) {
				if (!OffHook2()) {
					break;
				}
			}
			else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
				if (!OffHook3()) {
					break;
				}
			}
			wai_tsk(10/10);
#else /* !defined (KEISATSU) */
			OhPortStatusRead();
			if (!(OhPortStatus & TEL2_OFF_HOOK)) { /* TEL2 の直流ループ断 */
				break;
			}
			wai_tsk(10/10);
#endif /* defined (KEISATSU) */
		}
		AfterCI_HL_RelayOn = 5; /* added by H.Kubo 1998/10/23 */
		if (timer == 0) {
			rtn = FALSE;
		}
		else {
			rtn = TRUE;
		}		
	}
	else {
		 if (NCU_ND_SuspendAckResponse()) {
			/* ビジートーン検出 */
			busy_tone.SendMBX = mbxno.NCU_ND;
			busy_tone.ToneType = BUSYTONE;
			cre_tsk(&tskno_BusyToneTask, TSK_ATD_TONEDETECTPATTERN1TASK, &busy_tone);	/* ビジートーン検出タスクの起動 */
			/* タイマー検出 */
			timer = (CHK_ModemDialinON()) ? ND_DIALIN_RX_RESPONSE_TIMER : ND_RX_RESPONSE_TIMER;
			timer += 50; /* マージン 0.5 秒 */
			busy_tone_timeup.SendMBX		= mbxno.NCU_ND;
			busy_tone_timeup.ReturnValue	= MSG_ND_SUSPEND_RESPONSE_TIMEUP;
			busy_tone_timeup.Time = 	timer;
			CMN_MultiTimer10msStart(&timerID_v23_arrival, &busy_tone_timeup); 	/* V23 トーン待ちタイマ起動  */
	
			hook_check_timer.SendMBX		= mbxno.NCU_ND;
			hook_check_timer.ReturnValue	= MSG_ND_WATCH_OH;
			hook_check_timer.Time = 	40; /* 400ms */
			CMN_MultiTimer10msStart(&timerID_hookcheck, &hook_check_timer); 	/* V23 トーン待ちタイマ起動  */
	
			/* OH 検出 */
			loop = TRUE;
			do {
				rcv_msg(mbxno.NCU_ND, &message_ptr);
				switch (message_ptr->Item) {
				case FROM_AUTODIAL: /* ビジートーン検出 */
					loop = FALSE;
					rtn = FALSE;
					break;
				case FROM_MULTI_TIMER: /* Time up */
					if (message_ptr->Message == MSG_ND_WATCH_OH) {
						if (! NCU_ND_SuspendAckResponse()) {
							loop = FALSE;
							rtn = TRUE;
						}
						else {
							if (timerID_hookcheck != 0xff) {
								CMN_MultiTimer10msStop(&timerID_hookcheck);
							}
							CMN_MultiTimer10msStart(&timerID_hookcheck, &hook_check_timer); 	/* V23 トーン待ちタイマ起動  */
						}
					}
					else {
						loop = FALSE;
						rtn = FALSE;
					}
					break;
				default:
					loop = FALSE;
					break;
				}
			} while (loop);
			if (timerID_v23_arrival != 0xff) {
				CMN_MultiTimer10msStop(&timerID_v23_arrival);
			}
			if (timerID_hookcheck != 0xff) {
				CMN_MultiTimer10msStop(&timerID_hookcheck);
			}
			if (tskno_BusyToneTask != 0xffff) {
				del_tsk(&tskno_BusyToneTask);	/* ビジートーン検出タスクの終了 */
			}
		}
		else {
			rtn = TRUE;
		}
	}
	/* moved by H.Kubo 1998/11/23 */
	CMN_DisableInterrupt();
	SYB_ND_CarPattern[SYS_ND_LAST_NCU_ND_STATUS] = NCU_ND_Status; /* 状態を保存 */
	NCU_ND_Status |= (ND_SLEEP_AFTER_ACK_RESPONSE | ND_WAIT_FOR_2ND_RING); /* changed by H.Kubo 1998/11/25 */
	NCU_ND_Status &= ~ND_BEFORE_INFO_RECEIVED;
	SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
	/* CI の状態を初期化 */
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
	if (DEBUG_NumberDisplay) {
		if (SYS_LineNDStatus == ND_USED_IN_STD) {
			RingStatus &= ~CI_ON;
			SYS_RingCounter = 0;
		}
		else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
			RingStatus2nd &= ~CI_ON;
			SYS_RingCounterExt = 0;
		}
	}
	else {
		RingStatus &= ~CI_ON;
		SYS_RingCounter = 0;
	}
#else /* !defined (KEISATSU) */
	RingStatus &= ~CI_ON;
	SYS_RingCounter = 0;
#endif /* defined (KEISATSU) */
	if (CML_RelaySetting()) {
		CML_RelayOff();	/** 直流ループ開放 */
	}
	CMN_EnableInterrupt();
	return rtn;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[Number Display の CAR を検出処理をするかどうか判断する。]
	function	:[
		SettingStatus
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/07/03]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE NCU_ND_CheckWaitForCAR(void)
{
	return (CHK_NumberDisplayON());
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[Number Display の処理手順を示す大域変数を初期状態に設定する]
	function	:[
		Number Display の処理手順を示す大域変数 NCU_ND_Status を初期状態に設定する
	]
	return		:[なし]
	common		:[
		NCU_ND_Status
		SYB_ND_CarPattern
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/07/03]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void NCU_ND_InitializeStatus(void)
{
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
	if (DEBUG_NumberDisplay) {
 #if 0 /* 警察FAX (仕様変更) Modified by SMuratec 李 2005/11/23 */
@@		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
 #else
 	}
 	else if (DEBUG_NumberDisplay == 0) {
 		if ( !CHK_LineSetting()											/* 回線設定 == 拡張回線 */
			/* 警察FAX DVT_ID65 Added by SMuratec 李 2005/12/13 */
			|| (!SYS_LineNDStatus && CHK_NumberDisplayON() && (RingStatus & CI_STD_LINE) && (SYS_RingCounter == 0 ))
 			|| CHK_KEIDENRxPriority() 									/* 警電優先受信ONの場合 */
 			|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_CI_IN)		/* 拡張回線には呼出中 */
			|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)	/* 拡張回線には受話中 */
			|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT) /* 拡張回線には送話中 */
			|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE) 	/* 拡張回線には通信中 */
			|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) ) {	/* 拡張回線には本体使用中 */
 #endif
			NCU_ND_Status = 0;
			SYS_LineNDStatus = 0;
		}
 #if 0 /* 警察FAX (仕様変更) Modified by SMuratec 李 2005/11/23 */
@@		else if (CHK_KEIDENRxPriority() && ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)) {
@@			NCU_ND_Status = 0;
@@			SYS_LineNDStatus = 0;
@@		}
 #endif
		else if (CHK_NumberDisplayON()) {
			SYB_ND_CarPattern[SYS_ND_LAST_NCU_ND_STATUS] = NCU_ND_Status; /* 状態を保存 */
			if (SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_DETECT_ONLY_CAR) {
				NCU_ND_Status = ND_WAIT_FOR_CAR;
			}
			else {
				NCU_ND_Status = ND_WAIT_FOR_CAR_AND_IR;
			}
 #if 0 /* 警察FAX (仕様変更) Modified by SMuratec 李 2005/11/23 */
			if (!SYS_LineNDStatus || !(SYS_CalledLineNumber & SYS_TWICE_LINE_IN_CI)) {
				if (CHK_LineSetting()) { /* 回線設定 == 標準回線 */
					if ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) 	/* 標準回線には本体使用中 */
					|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) 	/* 拡張回線には本体使用中 */
					|| (CHK_KEIDENRxPriority() && ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)) ){ /* 警電優先受信ＯＮ及び警電受話中 */
						/* ここで動作しない */
					}
					else {
						SYS_LineNDStatus = ND_USED_IN_STD;
					}
				}
				else {	/* 回線設定 == 拡張回線 */
					if ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) 	/* 標準回線には本体使用中 */
					|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) ){	/* 拡張回線には本体使用中 */
						/* ここで動作しない */
					}
					else {
						SYS_LineNDStatus = ND_USED_IN_EXT;
					}
				}
			}
 #else
 			SYS_LineNDStatus = ND_USED_IN_STD;
			SYS_LineTelStatus &= ~(STD_TEL2_OFFHOOK | EXT_TEL2_OFFHOOK);
 #endif
		}
		else {
			NCU_ND_Status = 0;
			SYS_LineNDStatus = 0;
		}
	}
	else {
		if (CHK_NumberDisplayON()) {
			SYB_ND_CarPattern[SYS_ND_LAST_NCU_ND_STATUS] = NCU_ND_Status; /* 状態を保存 */
			if (SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_DETECT_ONLY_CAR) {
				NCU_ND_Status = ND_WAIT_FOR_CAR;
			}
			else {
				NCU_ND_Status = ND_WAIT_FOR_CAR_AND_IR;
			}
		}
		else {
			NCU_ND_Status = 0;
		}
	}
#else /* !defined (KEISATSU) */
	if (CHK_NumberDisplayON()) {
		SYB_ND_CarPattern[SYS_ND_LAST_NCU_ND_STATUS] = NCU_ND_Status; /* 状態を保存 */
		if (SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_DETECT_ONLY_CAR) {
			NCU_ND_Status = ND_WAIT_FOR_CAR;
		}
		else {
			NCU_ND_Status = ND_WAIT_FOR_CAR_AND_IR;
		}
	}
	else {
		NCU_ND_Status = 0;
	}
#endif /* defined (KEISATSU) */
	SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
	SYS_ND_CurrentJournalPoint = SYS_ND_NO_JOURNAL;
}


/*************************************************************************
	module		:[極性反転検出タスク]
	function	:[
		極性が反転したらメッセージを送信する
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/08/26]
	author		:[久保博]
*************************************************************************/
void	NCU_ND_DetectDSETask(UWORD *message_box)
{
	MESSAGE_t	 msg;
	UBYTE		dse1[3];
	UBYTE		dse2[3];

	dse1[0] = dse1[1];
	dse2[0] = dse2[1];
	dse1[1] = dse1[2];
	dse2[1] = dse2[2];
	dse1[2] = DSE1();
	dse2[2] = DSE2();


	while(1) {
		wai_tsk(50);	/* 50ms */
		if ((dse1[1] != dse1[2]) && (dse1[0] == dse1[1]) && (dse1[2] == DSE1())) {
			break;
		}
		if ( (dse2[1] != dse2[2]) && (dse2[0] == dse2[1]) && (dse2[2] == DSE2())) {
			break;
		}
		dse1[0] = dse1[1];
		dse2[0] = dse2[1];
		dse1[1] = dse1[2];
		dse2[1] = dse2[2];
		dse1[2] = DSE1();
		dse2[2] = DSE2();
	}

	msg.Item = FROM_NCU_ND;
	msg.Message = MSG_NCU_ND_DETECT_DSE;
	snd_msg(*message_box, &msg);
	wai_tsk(0xffff);
}


void NCU_ND_InitializeVariables(void)
{
	tskno_ND_DetectCalledTask = 0xffff;
	tskno_V23ToneTask = 0xffff;
	tskno_BusyToneTask = 0xffff;
	tskno_DetectDseTask = 0xffff;
	tskno_V23RxTask = 0xffff;
	timerID_v23_arrival = 0xff;
	timerID_ND_2ndCallTimer = 0xff;
	timerID_ND_SleepAfterAck = 0xff; /* added by H.Kubo 1998/11/25 */
}


/*************************************************************************
	module		:[一次応答から異常終了までのタイマー時間]
	function	:[
	]
	common		:[
		SYS_GeneralTimer
		NCU_ND_FirstResponseTime
	]
	condition	:[
		NCU_ND_Make1stResponse() で一次応答送出が終わっていること。
	]
	comment		:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/06]
	author		:[久保博]
*************************************************************************/
UWORD NCU_ND_GetDataTimerInterval(void)
{
	UWORD timer;

	timer =  (UWORD) (SYS_GeneralTimer - NCU_ND_FirstResponseTime); /* 一次応答から現在までの時間 */
	if (CHK_ModemDialinON()) {
		if (timer < NCU_ND_DIALIN_DATA_TIMER) {
			return (UWORD) (NCU_ND_DIALIN_DATA_TIMER - timer);
		}
	}
	else {
		if (timer < NCU_ND_DATA_TIMER) {
			return (UWORD) (NCU_ND_DATA_TIMER - timer);
		}
	}
	return 0;
}


/*************************************************************************
	module		:[二次応答まで待つ]
	function	:[
	]
	common		:[
		SYS_GeneralTimer
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/06]
	author		:[久保博]
*************************************************************************/
void NCU_ND_WaitFor2ndResponseTime(UWORD data_end_time, UWORD rx_accepting_signal_time)
{
#if 0 /* Changed by H.Kubo 1998/11/27 */
@@	while ( ((UWORD)(SYS_GeneralTimer - data_end_time) < ND_DATA_END_TO_2ND_RES_TIME)
@@	|| ((UWORD)(SYS_GeneralTimer - rx_accepting_signal_time) < ND_ACC_TO_2ND_RES_TIME) ) {
@@		wai_tsk(10/10);
@@	}
#else
	UWORD timer;
	timer = NCU_ND_2ndResponseTime(data_end_time, rx_accepting_signal_time);
	if (timer > 0) {
		wai_tsk(timer);
	}
#endif
	CMN_DisableInterrupt();
	NCU_ND_Status &= ~ND_SLEEP_AFTER_ACK_RESPONSE; /* added by H.Kubo 1998/11/25 */
	CMN_EnableInterrupt();
	return;
}

/*************************************************************************
	module		:[受信完了応答から二次応答まで待つ時間]
	function	:[
	]
	common		:[
		SYS_GeneralTimer
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/11/25]
	author		:[久保博]
*************************************************************************/
UWORD NCU_ND_2ndResponseTime(UWORD data_end_time, UWORD rx_accepting_signal_time)
{
	UWORD data_time;
	UWORD ack_signal_time;
	
	CMN_DisableInterrupt();
	data_time = (UWORD) (SYS_GeneralTimer - data_end_time);
	ack_signal_time = (UWORD) (SYS_GeneralTimer - rx_accepting_signal_time);
	CMN_EnableInterrupt();

	if (data_time >  ND_DATA_END_TO_2ND_RES_TIME) {
		data_time = 0;
	}
	else {
		data_time = (UWORD) (ND_DATA_END_TO_2ND_RES_TIME - data_time);
	}

	if (ack_signal_time > ND_ACC_TO_2ND_RES_TIME) {
		ack_signal_time = 0;
	}
	else {
		ack_signal_time = (UWORD) (ND_ACC_TO_2ND_RES_TIME - ack_signal_time);
	}
	return (data_time > ack_signal_time) ? data_time : ack_signal_time;
}



/*************************************************************************
	module		:[ダイヤルイン情報を取得した状態に遷移]
	function	:[
	]
	common		:[
		NUC_ND_Status
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/14]
	author		:[久保博]
*************************************************************************/
void NCU_ND_SetModemDialinStatus(UBYTE din_status)
{
	if (CHK_ModemDialinON()) {
		CMN_DisableInterrupt(); /* added by H.Kubo 1998/12/14 */
		switch (din_status) {
		case D_IN_FAX:
			NCU_ND_Status |= ND_MODEM_DIALIN_FAX_DIAL;
			break;
		case D_IN_TEL1:
	    	NCU_ND_Status |= ND_MODEM_DIALIN_TEL1_DIAL;
			break;
		 case D_IN_TEL2:
		    NCU_ND_Status |= ND_MODEM_DIALIN_TEL2_DIAL;
			break;
		case D_IN_TEL1_TEL2:
			NCU_ND_Status |= (ND_MODEM_DIALIN_TEL1_DIAL | ND_MODEM_DIALIN_TEL2_DIAL);
		 default:
			break;
		}
		if (NCU_ND_Status & ND_MODEM_DIALIN_DIAL) {
			SYB_DialInNoNumberSignal = 0; /* 着番号つきで着信があったらクリアする。 */
		}
		CMN_EnableInterrupt(); /* added by H.Kubo 1998/12/14 */
	}
	CMN_DisableInterrupt(); /* added by H.Kubo 1998/12/14 */
	SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
	CMN_EnableInterrupt(); /* added by H.Kubo 1998/12/14 */
}

/*************************************************************************
	module		:[ND 手順は二次応答で終了か]
	function	:[
			Ｖ２３に対する受信応答後、すぐに ND 受信手順を抜けるかどうか判断する
	]
	common		:[
		NUC_ND_Status
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/14]
	author		:[久保博]
*************************************************************************/
UBYTE NCU_ND_IsRxProcedureFinished(void)
{
	SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status; /* NCU_ND_Status をデバッグ用に記録。 */
	if (NCU_ND_Status & (ND_WAIT_FOR_2ND_RING | ND_DETECT_CI_AFTER_RX_RES)) {
		if (NCU_ND_Status & ND_MODEM_DIALIN_FAX_DIAL) {
			return FALSE;
		}
		else if (NCU_ND_Status & (ND_MODEM_DIALIN_TEL1_DIAL|ND_MODEM_DIALIN_TEL2_DIAL)) {
			return TRUE;
		}
		/* 普通のナンバーディスプレイ */
		else if (SYB_ND_CarPattern[SYS_ND_CAR_MODE] & SYS_ND_EXIT_AFTER_RX_RESPONSE) {
			return TRUE;
		}
		return FALSE;
	}
	else if (NCU_ND_Status & (ND_COUNTING_2ND_RING | ND_CALL_ACCEPTED)) {
		return TRUE;
	}
	return FALSE;
}

/*************************************************************************
	module		:[ND 手順で呼出し音計数処理から着信状態へ遷移]
	function	:[
			ND 手順で呼出し音計数処理から着信状態へ遷移
	]
	common		:[
		NUC_ND_Status
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/15]
	author		:[久保博]
*************************************************************************/
void NCU_ND_SetCallDetectedStatus(void)
{
	CMN_DisableInterrupt();
	SYB_ND_CarPattern[SYS_ND_LAST_NCU_ND_STATUS] = NCU_ND_Status;
	NCU_ND_Status |= ND_CALL_ACCEPTED;
	NCU_ND_Status &= ~(ND_BEFORE_INFO_RECEIVED |ND_SLEEP_AFTER_ACK_RESPONSE | ND_COUNTING_2ND_RING | ND_DETECT_CI_AFTER_RX_RES | ND_WAIT_FOR_2ND_RING); /* changed by H.Kubo 1998/11/25 */
	SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[ND 手順で CAR 検出状態へ遷移]
	function	:[
	]
	common		:[
		NUC_ND_Status
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/15]
	author		:[久保博]
*************************************************************************/
void NCU_ND_SetCarDetectedStatus(void)
{
	CMN_DisableInterrupt();
	SYB_ND_CarPattern[SYS_ND_LAST_NCU_ND_STATUS] = NCU_ND_Status;
	NCU_ND_Status = ND_CAR_DETECTED;
	SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[ND モデムダィヤルインで鳴動していないハンドセットをとったときの動作の選択]
	function	:[
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	return		:[
		0			TEL1 鳴動中、 TEL2 をとると、回線をつかめる。 TEL1 の鳴動は停止する。
		0 以外		TEL1 鳴動中、 TEL2 をとっても回線をつかめない。 TEL1 は引き続き鳴動する。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/28]
	author		:[久保博]
*************************************************************************/
UBYTE NCU_ModemDialinHandsetBehavior(void)
{
	return (SYB_ND_CarPattern[SYS_ND_MODEM_DIALIN_MODE] & SYS_ND_DIALIN_TEL_EXCLUSIVE);
}

/*************************************************************************
	module		:[CAR 待ちで呼出音検出の設定]
	function	:[
			ND 手順でCAR 待ちから呼出し音を受けながらの待機状態へ遷移
	]
	common		:[
		NUC_ND_Status
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/15]
	author		:[久保博]
*************************************************************************/
void NCU_ND_SetRingDetectedStatus(void)
{
	CMN_DisableInterrupt();
	SYB_ND_CarPattern[SYS_ND_LAST_NCU_ND_STATUS] = NCU_ND_Status;
	NCU_ND_Status |= ND_COUNTING_2ND_RING;
	NCU_ND_Status &= ~(ND_BEFORE_INFO_RECEIVED | ND_DETECT_CI_AFTER_RX_RES | ND_WAIT_FOR_2ND_RING);
	SYB_ND_CarPattern[SYS_ND_CURRENT_NCU_ND_STATUS] = NCU_ND_Status;
	CMN_EnableInterrupt();
}


/*************************************************************************
	module		:[モデムダィヤルイン着信からダイヤルインに切り替わるべきか]
	function	:[
			ND 手順でCAR 待ちから呼出し音を受けながらの待機状態へ遷移
	]
	common		:[
		NUC_ND_Status
		SYS_RingCounter
	]
	condition	:[]
	comment		:[
		CMN_PresentReceiveMode() の返り値が SYS_MODEM_DIALIN_READY の時のみ意味があります。
	]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/11/27]
	author		:[久保博]
*************************************************************************/
UBYTE NCU_ND_ShuldSwitchToDialin(void)
{
	UBYTE rtn;
	if (SYB_ND_CarPattern[SYS_ND_MODEM_DIALIN_MODE] & SYS_ND_SWITCH_TO_NORMAL_DIALIN) {
		if (CHK_ModemDialinON()) {
			if ((NCU_ND_Status & ND_WAIT_FOR_IR) 
			&& !(NCU_ND_Status & (ND_CAR_DETECTED | ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING | ND_MODEM_DIALIN_DIAL))
			&& (SYS_RingCounter > 0) ) {
				rtn = TRUE;
			}
			else {
				rtn = FALSE;
			}
		}
		else {
			rtn = FALSE;
		}
	}
	else {
		rtn = FALSE;
	}
	return rtn;
}

/*************************************************************************
	module		:[IR 待ちで CAR と IR の判別がつくまで無鳴動にするか]
	function	:[
	]
	common		:[
		NUC_ND_Status
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/15]
	author		:[久保博]
*************************************************************************/
UBYTE  NCU_ND_SilentAfterAckResponse(void)
{
	return (SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & SYS_ND_SILENT_WHILE_IR_DETECT);
}


#if 0
** void NCU_ND_DetectPhoneResponseTask()
** {
** 	while (1) {
** 		wai_evt(EVT_CI_CHECK);
** 		if (!(RingStatus & CI_ON)) {
** 			continue;
** 		}
** 		
** 		while (--timer > 0) {
** 			OhPortStatusRead();
** 			if (OhPortStatus & TEL2_OFF_HOOK) { /* TEL2 の直流ループ断 */
** 				/* ND 受信手順へ移るべし。 */
** 			}
** 			current_time = SYS_GeneralTimer;
** 			else {
** 			}
** 			wai_tsk(10/10);
** 		}
** 	}
** }
#endif
#else	/* #if (PRO_NUMBER_DISPLAY == ENABLE) added by H.Hirao 1999/01/12 */
/* dummy TASK */
void NCU_ND_RxProcedureTask(WORD *mailbox)
{
	wai_tsk(0xffff);
}
void NCU_ND_DetectDSETask(UWORD *message_box)
{
	wai_tsk(0xffff);
}
/* dummy function */
void NCU_ND_RxProcedureTaskExit(void)
{
	exi_tsk();
}
#endif
