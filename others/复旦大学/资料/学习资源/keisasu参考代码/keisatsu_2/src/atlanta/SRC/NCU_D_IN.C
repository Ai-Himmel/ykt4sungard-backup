/**********************************************************************
* RICE
*
*    File   Name:  NCU_D_IN.C
*    Coded    by:  坂本直史
*    Module Name:  NCU_DetectDSETask()
*				   NCU_DialInAutoSwitchTask()
*				   DialInAutoSwitchExit()
*
*    Note       :  ダイヤル・イン着信後処理
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
#include    "\src\atlanta\define\product.h"
#include    "\src\atlanta\define\message.h"
#include    "\src\atlanta\define\apl_msg.h"
#include    "\src\atlanta\define\sysrxsw.h"

#include    "\src\atlanta\define\ncu_stat.h"
#include    "\src\atlanta\define\ncu_msg.h"
#include    "\src\atlanta\define\ncu_ret.h"
#include    "\src\atlanta\define\ncu_cnst.h"
#include    "\src\atlanta\define\ncu_def.h"

#include    "\src\atlanta\define\ncu_pro.h"
#include    "\src\atlanta\define\mon_pro.h"
#include    "\src\atlanta\define\cmn_pro.h"
#include    "\src\atlanta\define\uni_pro.h"
#include	"\src\memsw\define\mems_pro.h"
#if (PRO_MODEM == ORANGE3) /* added by H.Kubo 1997/07/23 */
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#endif /* (PRO_MODEM == ORANGE3)  */
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/07/23 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
 #endif
#endif /* (PRO_MODEM == R288F)  */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#endif


#include    "\src\atlanta\ext_v\bkupram.h"

#include    "\src\atlanta\ext_v\ncu_data.h"
#include    "\src\atlanta\ext_v\ncu_tbl.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#if (PRO_CLASS1 == ENABLE)
#include	"\src\atlanta\ext_v\cl1_data.h"
#endif

#include    "\src\atlanta\sh7043\ext_v\extv_mbx.h"

#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\define\sh_port.h"

#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\cl1_def.h"
#endif
#include  "\src\atlanta\define\std.h"	/* S.Fukui June 19,1998 */

#if (PRO_NCU_TYPE == HINOKI_TYPE) /* 1999/02/22 by T.Soneoka */
 #if defined(POPLAR_F)
	#include "\src\atlanta\sh7043\ext_v\extv_mon.h"
 #else
	#include "\src\cpu\sh7043_a\irom\ext_v\extv_mon.h"
 #endif
#endif


#if ( PRO_DIALIN == ENABLE )
static	UWORD		tskno_ReceiveDTMFTask			= 0xFFFF;
static	UWORD		tskno_GenerateRingSignalTask	= 0xFFFF;
static	UWORD		tskno_CMN_WatchTimer10msTask	= 0xFFFF;
static	UWORD		tskno_DetectDSETask				= 0xFFFF;
 #if defined (HINOKI2) || defined(HINOKI3)	/* 2002/01/10 by T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)/* By M.Maeda 2002/09/18 */
 	extern UWORD BackupReceiveLevel;
 #endif
#endif
#if (PRO_PRINTER_RX == ENABLE) /* changed by H.Hirao 1998/12/28 */
 #include  "\src\atlanta\define\man_pro.h"
#endif
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル・イン着信後ＤＳＥ監視タスク]
	function	:[
		1.疑似ベル鳴動中、発個側の回線断を検出する為に１ｍｓ割込でＤＳＥ（極性反転）を監視する。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1994/02/26]
	author		:[坂本直史, 平岡徹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	NCU_DetectDSETask( WORD *tx_mail_box_no )
{
#if (PRO_DIALIN == ENABLE)

	UBYTE	 wait_timer;

	TxDetectDSETaskMsg.Item = FROM__NCU_D_IN;
	wait_timer = 3;

	/*----------------------------*/
	/** DSEの検出周期を決定します */	/* サービスからの要求	Add by TH92115 1994/10/11 */
	/*----------------------------*/
	if (!(NCUStatus & DIALIN_RECEIVE_STATE)) {
		switch (CHK_UNI_DSE_DetectCycle()) {
		case 0x20:
			wait_timer = 5;
			break;
		case 0x40:
			wait_timer = 10;
			break;
		case 0x60:
			wait_timer = 15;
			break;
		default:
			break;
		}
		wai_tsk(90);			/** 900msec wait	1994/09/16 TH92115 */
	}
	/*---------------------------------*/
	/** 疑似ベル鳴動前の回線極性の記憶 */
	/*---------------------------------*/
#if (0)	/* By M.Tachibana 1997/02/14 */
//	SYS_DSE1 = (UWORD)(inpw(MODEM_PORT) & IO_BIT_XDSE1_VC );
//	SYS_DSE2 = (UWORD)(inpw(MODEM_PORT) & IO_BIT_XDSE2_LC );
#endif
	SYS_DSE1 = DSE1();
	SYS_DSE2 = DSE2();

	/*-----------------------------------*/
	/** ＤＳＥの反転を検出するまでループ */
	/*-----------------------------------*/
	if ((NCUStatus & DIALIN_RECEIVE_STATE)
	 || (CHK_UNI_GenerateRingStopCond())) {	/** ダイヤルインか瞬断検出の時 */
		while (1) {
/*
** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
** 確認して使用することにする
** 1999/02/22 by T.Soneoka
*/
#if (PRO_NCU_TYPE == HINOKI_TYPE)
			if (wai_1shot_tid == 0xFF) {
				wai_oneshot(wait_timer);
			}
			else {
				wai_tsk((UWORD)((wait_timer / 10) + 1));
			}
#else
			wai_oneshot(wait_timer);
#endif
#if (0)	/* By M.Tachibana 1997/02/14 */
//			if (( SYS_DSE1 != (UWORD)( inpw(MODEM_PORT) & IO_BIT_XDSE1_VC ))
//			|| (  SYS_DSE2 != (UWORD)( inpw(MODEM_PORT) & IO_BIT_XDSE2_LC ))) {
#endif
			if ((SYS_DSE1 != DSE1()) || (SYS_DSE2 != DSE2())) {
 				break;
			}
		}
	}
	else {										/** TEL/FAXで極反検出の時 */
		while (1) {
/*
** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
** 確認して使用することにする
** 1999/02/22 by T.Soneoka
*/
#if (PRO_NCU_TYPE == HINOKI_TYPE)
			if (wai_1shot_tid == 0xFF) {
				wai_oneshot(wait_timer);
			}
			else {
				wai_tsk((UWORD)((wait_timer / 10) + 1));
			}
#else
			wai_oneshot(wait_timer);
#endif
#if (0)	/* By M.Tachibana 1997/02/14 */
//			if (( SYS_DSE1 != (UWORD)( inpw(MODEM_PORT) & IO_BIT_XDSE1_VC ))
//			&& (  SYS_DSE2 != (UWORD)( inpw(MODEM_PORT) & IO_BIT_XDSE2_LC ))) {
#endif
			if ((SYS_DSE1 != DSE1()) && (SYS_DSE2 != DSE2())) {
				break;
			}
		}
	}
	wai_tsk(100);

	/*-----------------------------------------------*/
	/** ダイヤル・イン着信後処理メイン・タスクへ通知 */
	/*-----------------------------------------------*/
	if (!OffHook1() && !OffHook2()) {
		if (CHK_UNI_DetectDSE_Available() && CHK_DialInGRSOffLRelayOff()) {		/** QAT1 1994/08/12 by TH92115 */
			TxDetectDSETaskMsg.Message = DETECT_D_IN_DSE;
			snd_msg( *tx_mail_box_no, &TxDetectDSETaskMsg);
		}
	}
	wai_tsk(0xFFFF);
#else
	wai_tsk(0xFFFF);
#endif
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル・イン着信後処理MAINタスク]
	function	:[
		1.ダイヤル・イン仮着信の為の一次応答を行なう。
		2.内線指定信号を検出する。
		3.二次応答（本当は、内線指定受信完了信号）を行なう。
		4.電話に対する呼び出しの場合、疑似ベルを鳴動させる。
		5.ＤＴＭＦ検出・疑似ベル鳴動期間設定の為のタイマを起動する。
		6.以上の機能を実行する子タスクの生成・削除等を行なう。
	]
	return		:[なし]
	common		:[
		NCUStatus	:回線監視モジュール動作状態を記憶
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1993/12/06]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void        NCU_DialInAutoSwitchTask( void )
{
#if ( PRO_DIALIN == ENABLE )

	MESSAGE_t	*RxDialInAutoSwitchTaskMsg;
	struct GenerateRingData_t general_ring_data;
	UBYTE	 	i;

 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
	UBYTE	is_class1_rx_enable;
 #endif
 #if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)	 /* added by H.Hirao 1998/12/28 */
	UBYTE	wait_timer;
	UWORD	count;
 #endif
	/*------------------------*/
	/**  使用大域変数初期化   */
    /*------------------------*/
	NCUStatus       				&= ~DETECT_CALL;
	NCUStatus       				|= DIALIN_RECEIVE_STATE;
	TxDialInAutoSwitchTaskMsg.Item	 = FROM_NCU_DIALINAUTOSWITCHTASK;
	DTMF_ReceiverCounter			 = 0;
	DTMF_ReceiverDV_OnOff			 = 0;

	for( i = 0; i < 4;){
		DTMF_ReceiverBuffer[i] = 0;
		i++;
	}

#if defined (HINOKI2) || defined(HINOKI3)	/* 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)/* By M.Maeda 2002/09/18 */
	MDM_ConfigDTMF_ReceiverMode();
#endif

 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
    /* Class1ダイヤルイン対応 */
		is_class1_rx_enable = CL1_CheckReceiveByFaxOrPC();
 #endif

	tskno_ReceiveDTMFTask 			 = 0xFFFF;
	tskno_GenerateRingSignalTask	 = 0xFFFF;
	tskno_CMN_WatchTimer10msTask	 = 0xFFFF;
	tskno_DetectDSETask				 = 0xFFFF;
	/*------------------------------------*/
	/**  ＤＴＭＦ検出時間Ｔｉｍｅｒセット */
	/*------------------------------------*/
	NCU10msTimer.Time			= 650;
	NCU10msTimer.SendMBX		= mbxno.NCU_DialInAutoSwitchTask;
	NCU10msTimer.ReturnValue	= DETECT_D_IN_DTMF_RCV_TIMEUP;

	cre_tsk(&tskno_CMN_WatchTimer10msTask, TSK_CMN_MAN_TIMER10MSTASK, &NCU10msTimer);
	/*---------------------------*/
	/** ＤＴＭＦ検出タスク生成   */
	/*---------------------------*/
	cre_tsk(&tskno_ReceiveDTMFTask, TSK_NCU_RECEIVEDTMFTASK, &(mbxno.NCU_DialInAutoSwitchTask));
	/*---------------------------*/
	/**   一次応答リレー制御     */
	/*---------------------------*/
	DialIn1stAnswerRealyControl();
				/*---------------------------------------------------------------------------------*/
	while(1){	/** ＦＡＸ着信／ＯＦＦ　ＨＯＯＫ検出／ＤＳＥ検出／ＣＩ検出／ＴｉｍｅＵｐまでループ */
				/*---------------------------------------------------------------------------------*/
		/*-------------------*/
		/** 事象の待ち合わせ */
		/*-------------------*/
		rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
													/*-----------------------*/
		switch(RxDialInAutoSwitchTaskMsg->Item){	/** 発生事象に対する処理 */
													/*-----------------------*/
												/*---------------------------------------------------------*/
			case    FROM__NCU_SUB		:		/** 回線監視補助タスク群（ＮＣＵ＿ＳＵＢ）からのメッセージ */
												/*---------------------------------------------------------*/
																/*-----------------------*/
				switch(RxDialInAutoSwitchTaskMsg->Message){		/** 発生事象に対する処理 */
																/*-----------------------*/
															/*---------------------------------------*/
					case	DETECT_D_IN_DTMF_RCV	:		/**            ＤＴＭＦ受信完了          */
															/*---------------------------------------*/
							del_tsk(&tskno_CMN_WatchTimer10msTask);
							/*-----------------------------------------*/
							/**       ＤＴＭＦ検出タスクとの同期       */
							/*-----------------------------------------*/
							TxDialInAutoSwitchTaskMsg.Message = OK_CONT;
							snd_msg(mbxno.NCU_ReceiveDTMFTask, &TxDialInAutoSwitchTaskMsg);
							break;
															/*---------------------------------------*/
					case	DETECT_D_IN_UNMATCH		:		/**    受信ＤＴＭＦと登録番号が不一致    */
															/*---------------------------------------*/
							/*-------------------------------------*/
							/** ダイヤル・イン　モジュール終了処理 */
							/*-------------------------------------*/
							SYB_DialInNoNumberSignal = 0;
							DialInAutoSwitchExit();
							/*---------------------------*/
							/**   二次応答リレー制御     */
							/*---------------------------*/
							DialIn2ndAnswerRelayControl( DIAL_IN_UNMATCH );
							/*-----------------------*/
							/** メイン・タスクへ通知 */
							/*-----------------------*/
							TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
							snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
							rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
							/*-----------------*/
							/** 自タスクの終了 */
							/*-----------------*/
							SYS_RingCounter = 0;
							exi_tsk();

							break;
															/*---------------------------------------*/
					case	DETECT_INPUT_STOP_KEY   :		/**            ＳＴＯＰキーＯＮ　　　　　*/
															/*---------------------------------------*/
							/*-------------------------------------*/
							/** ダイヤル・イン　モジュール終了処理 */
							/*-------------------------------------*/
							SYB_DialInNoNumberSignal = 0;
							DialInAutoSwitchExit();
							/*---------------------------*/
							/**   二次応答リレー制御     */
							/*---------------------------*/
							DialIn2ndAnswerRelayControl( DIAL_IN_STOP );
							/*-----------------------*/
							/** メイン・タスクへ通知 */
							/*-----------------------*/
							TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
							snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
							rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
							/*-----------------*/
							/** 自タスクの終了 */
							/*-----------------*/
							SYS_RingCounter = 0;
							exi_tsk();
							break;
															/*-------------------------------------*/
					case	DETECT_D_IN_FAX			:		/**           ＦＡＸ  着信             */
															/*-------------------------------------*/
							/*-------------------------------------*/
							/** ダイヤル・イン　モジュール終了処理 */
							/*-------------------------------------*/
							SYB_DialInNoNumberSignal = 0;
							DialInAutoSwitchExit();
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
  #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/6 K.Kawata */
							if (CL1_ExtFunctionEnableFlag == 0) {
								if (CHK_UNI_Class1_EXT_Function()) {
									if ((CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK)
									   /*&& (SYS_CL1_Status == 0)*/ && (CL1_ExtFunctionEnableFlag == 0)) {
										if (CMN_CheckMultiLineReceiveEnable() == FALSE) {	/** 代行受信不可 */
											/*-----------------------------------------------*/
											/**   二次応答リレー制御  			     */
											/*-----------------------------------------------*/
											DialIn2ndAnswerRelayControl( DIAL_IN_UNMATCH );
											/*-----------------------*/
											/** メイン・タスクへ通知 */
											/*-----------------------*/
											TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
											snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
											rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
 											/*-----------------*/	
											/** 自タスクの終了 */
											/*-----------------*/
											SYS_RingCounter = 0;
											exi_tsk();
										}
										else {
											SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM;	/* CLASS1動作中セット */
											CL1_ExtFunctionEnableFlag = 1;
											SYS_CL1_Status &= (~CL1_DIALIN_CALLED);
											/*---------------------------*/
											/**   二次応答リレー制御     */
											/*---------------------------*/
											DialIn2ndAnswerRelayControl( DIAL_IN_FAX );
											/*-----------------------*/
											/** メイン・タスクへ通知 */
											/*-----------------------*/
											TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_TRANSFER_D_IN;
											snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
											rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
											/*-----------------*/
											/** 自タスクの終了 */
											/*-----------------*/
											exi_tsk();
										}
									}
									else {
										/*-----------------------------------------------*/
										/**   二次応答リレー制御  			     */
										/*-----------------------------------------------*/
										DialIn2ndAnswerRelayControl( DIAL_IN_UNMATCH );
										/*-----------------------*/
										/** メイン・タスクへ通知 */
										/*-----------------------*/
										TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
										snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
										rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
										/*-----------------*/	
										/** 自タスクの終了 */
										/*-----------------*/
										SYS_RingCounter = 0;
										exi_tsk();
									}
								}
								else {
									/* Class1ダイヤルイン対応  */
									if (is_class1_rx_enable == PC_RECEIVE_OK ) {	/* 通常ダイヤルイン回線でClass1受信可能 */
										/** Class1疑似RING送出用のリレーに設定する */
										DialIn2ndAnswerRelayControl( DIAL_IN_CLASS1_CALL );
										/** 極反検出タスク起動 */
										NCUStatus |= DIALIN_RECEIVE_STATE;	/* 極反検出タスクで必要 */
										tskno_DetectDSETask = 0xFFFF;
										cre_tsk( &tskno_DetectDSETask, TSK_NCU_DETECTDSETASK,
												&(mbxno.NCU_DialInAutoSwitchTask));
										/** Class1ダイヤルイン呼び出しをMAN_Taskへ通知 */
										TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_CL1_D_IN;
										/* 削除 SYS_KeyInputInhibit = 1; */
										snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
										rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
										/*
										* 極反検出タスクを起動するため、引き続きrcv_msgする
										* (CL1_Task側でRINGタイマを起動するためここでは極反検出だけする)
										*/
										break;
									}
									else if ((is_class1_rx_enable == NO_RECEIVING)
										||  (CMN_CheckMultiLineReceiveEnable() == FALSE)) {		/* 代行受信不可 */
										/*-----------------------------------------------*/
										/**   二次応答リレー制御  					     */
										/*-----------------------------------------------*/
										DialIn2ndAnswerRelayControl( DIAL_IN_UNMATCH );
										/*-----------------------*/
										/** メイン・タスクへ通知 */
										/*-----------------------*/
										TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
										snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
										rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
 										/*-----------------*/
										/** 自タスクの終了 */
										/*-----------------*/
										SYS_RingCounter = 0;
										exi_tsk();
									}
  #if (PRO_RS_INTERNAL == ENABLE)	/* added by H.Hirao 1999/05/12 */
									else if ((is_class1_rx_enable == NO_RECEIVING_SCANNER_IN_USE)
										  || (is_class1_rx_enable == NO_RECEIVING_PRINTER_IN_USE)) {	/* 原稿蓄積中じゃなければ、従来のパス */
										DialIn2ndAnswerRelayControl(DIAL_IN_FAX_FOR_DOC_STORE);
										/*
										** DSE検出か、原稿蓄積中じゃなくなるまで、ループ（こんな所で、ループしてごめんなさい）
										*/
										switch (CHK_UNI_DSE_DetectCycle()) {
										case 0x20:
									wait_timer = 5;
												break;
										case 0x40:
											wait_timer = 10;
											break;
										case 0x60:
											wait_timer = 15;
											break;
										default:
											wait_timer = 3;
											break;
										}
										wai_tsk(90);			/** 900msec wait	1994/09/16 TH92115 */
										SYS_DSE1 = DSE1();
										SYS_DSE2 = DSE2();
										count = (UWORD)((UWORD)(SYB_Dialin.BellTime * 1000) / wait_timer);
										while (count--) {
/*
** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
** 確認して使用することにする
** 1999/02/22 by T.Soneoka
*/
#if (PRO_NCU_TYPE == HINOKI_TYPE)
											if (wai_1shot_tid == 0xFF) {
												wai_oneshot(wait_timer);
											}
											else {
												wai_tsk((UWORD)((wait_timer / 10) + 1));
											}
#else
											wai_oneshot(wait_timer);
#endif
											if ((SYS_DSE1 != DSE1()) || (SYS_DSE2 != DSE2())) {
							 					TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
												snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
												rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
												exi_tsk();
											}
											if (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK) {
												AnalogSwitchRXA_Set();
												CML_RelayOn();
												TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_CL1_D_IN;
												snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
												rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
												break;
											}
										}
										if (!count) {
											TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
											snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
											rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
											exi_tsk();
										}
									}
  #endif
								}
							}
							else {
								/*-----------------------------------------------*/
								/**   二次応答リレー制御  			     */
								/*-----------------------------------------------*/
								DialIn2ndAnswerRelayControl( DIAL_IN_UNMATCH );
								/*-----------------------*/
								/** メイン・タスクへ通知 */
								/*-----------------------*/
								TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
								snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
								rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
								/*-----------------*/	
								/** 自タスクの終了 */
								/*-----------------*/
								SYS_RingCounter = 0;
								exi_tsk();
							}
  #else
							/* Class1ダイヤルイン対応  */
							if (is_class1_rx_enable == PC_RECEIVE_OK ) {	/* 通常ダイヤルイン回線でClass1受信可能 */
								/** Class1疑似RING送出用のリレーに設定する */
								DialIn2ndAnswerRelayControl( DIAL_IN_CLASS1_CALL );
								/** 極反検出タスク起動 */
								NCUStatus |= DIALIN_RECEIVE_STATE;	/* 極反検出タスクで必要 */
								tskno_DetectDSETask = 0xFFFF;
								cre_tsk( &tskno_DetectDSETask, TSK_NCU_DETECTDSETASK,
										&(mbxno.NCU_DialInAutoSwitchTask));
								/** Class1ダイヤルイン呼び出しをMAN_Taskへ通知 */
								TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_CL1_D_IN;
								/* 削除 SYS_KeyInputInhibit = 1; */
								snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
								rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
								/*
								* 極反検出タスクを起動するため、引き続きrcv_msgする
								* (CL1_Task側でRINGタイマを起動するためここでは極反検出だけする)
								*/
								break;
							}
							else if ((is_class1_rx_enable == NO_RECEIVING)
								||  (CMN_CheckMultiLineReceiveEnable() == FALSE)) {		/* 代行受信不可 */
								/*-----------------------------------------------*/
								/**   二次応答リレー制御  					     */
								/*-----------------------------------------------*/
								DialIn2ndAnswerRelayControl( DIAL_IN_UNMATCH );
								/*-----------------------*/
								/** メイン・タスクへ通知 */
								/*-----------------------*/
								TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
								snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
								rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
 								/*-----------------*/
								/** 自タスクの終了 */
								/*-----------------*/
								SYS_RingCounter = 0;
								exi_tsk();
							}
  #if (PRO_RS_INTERNAL == ENABLE)	/* added by H.Hirao 1999/05/12 */
 							else if ((is_class1_rx_enable == NO_RECEIVING_SCANNER_IN_USE)
 								  || (is_class1_rx_enable == NO_RECEIVING_PRINTER_IN_USE)) {	/* 原稿蓄積中じゃなければ、従来のパス */
								DialIn2ndAnswerRelayControl(DIAL_IN_FAX_FOR_DOC_STORE);
								/*
								** DSE検出か、原稿蓄積中じゃなくなるまで、ループ（こんな所で、ループしてごめんなさい）
								*/
								switch (CHK_UNI_DSE_DetectCycle()) {
								case 0x20:
									wait_timer = 5;
									break;
								case 0x40:
									wait_timer = 10;
									break;
								case 0x60:
									wait_timer = 15;
									break;
								default:
									wait_timer = 3;
									break;
								}
								wai_tsk(90);			/** 900msec wait	1994/09/16 TH92115 */
								SYS_DSE1 = DSE1();
								SYS_DSE2 = DSE2();
								count = (UWORD)((UWORD)(SYB_Dialin.BellTime * 1000) / wait_timer);
								while (count--) {
/*
** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
** 確認して使用することにする
** 1999/02/22 by T.Soneoka
*/
#if (PRO_NCU_TYPE == HINOKI_TYPE)
									if (wai_1shot_tid == 0xFF) {
										wai_oneshot(wait_timer);
									}
									else {
										wai_tsk((UWORD)((wait_timer / 10) + 1));
									}
#else
									wai_oneshot(wait_timer);
#endif
									if ((SYS_DSE1 != DSE1()) || (SYS_DSE2 != DSE2())) {
						 				TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
										snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
										rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
										exi_tsk();
									}
									if (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK) {
										AnalogSwitchRXA_Set();
										CML_RelayOn();
										TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_CL1_D_IN;
										snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
										rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
										break;
									}
								}
								if (!count) {
					 				TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
									snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
									rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
									exi_tsk();
								}
							}
  #endif
  #endif	/* PRO_CLASS1_EXT_FUNC */
 #else		/* 代行受信不可の時のダイヤルインFAX番号への受信は回線を切る S.Fukui Jun.19,1998 */
  #if (PRO_PRINTER_RX == ENABLE) /* changed by H.Hirao 1998/12/28 */
  							if ((CMN_CheckMultiLineReceiveEnable() == FALSE) && (QueryPRxEnable() == FALSE)) {
  #else
    #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.1 K.Kawata */
  							if ((CMN_CheckMultiLineReceiveEnable() == FALSE) && (QueryPRxEnable() == FALSE)) {
    #else
							if (CMN_CheckMultiLineReceiveEnable() == FALSE)  {	/** 代行受信不可 */
    #endif
  #endif
								/*-----------------------------------------------*/
								/**   二次応答リレー制御  					     */
								/*-----------------------------------------------*/
								DialIn2ndAnswerRelayControl( DIAL_IN_UNMATCH );
								/*-----------------------*/
								/** メイン・タスクへ通知 */
								/*-----------------------*/
								TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
								snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
								rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
 								/*-----------------*/
								/** 自タスクの終了 */
								/*-----------------*/
								SYS_RingCounter = 0;
								exi_tsk();
							}
 #endif	/* PRO_CL1_TELFAX_LAN */
 #if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103) /* added by H.Hirao 1998/12/28 */
 							else if ((SYS_DualRestrictionStatus & 0x02) != 0x02) {	/* 原稿蓄積中じゃなければ、従来のパス */
	 							/*---------------------------*/
								/**   二次応答リレー制御     */
								/*---------------------------*/
								DialIn2ndAnswerRelayControl( DIAL_IN_FAX );
								/*-----------------------*/
								/** メイン・タスクへ通知 */
								/*-----------------------*/
								TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_TRANSFER_D_IN;
								snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
								rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
								/*-----------------*/
								/** 自タスクの終了 */
								/*-----------------*/
								exi_tsk();
 							}
 							else {
								DialIn2ndAnswerRelayControl(DIAL_IN_FAX_FOR_DOC_STORE);
								/*
								** DSE検出か、原稿蓄積中じゃなくなるまで、ループ（こんな所で、ループしてごめんなさい）
								*/
								switch (CHK_UNI_DSE_DetectCycle()) {
								case 0x20:
									wait_timer = 5;
									break;
								case 0x40:
									wait_timer = 10;
									break;
								case 0x60:
									wait_timer = 15;
									break;
								default:
									wait_timer = 3;
									break;
								}
								wai_tsk(90);			/** 900msec wait	1994/09/16 TH92115 */
								SYS_DSE1 = DSE1();
								SYS_DSE2 = DSE2();
								count = (UWORD)((UWORD)(SYB_Dialin.BellTime * 1000) / wait_timer);
								while (count--) {
/*
** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
** 確認して使用することにする
** 1999/02/22 by T.Soneoka
*/
#if (PRO_NCU_TYPE == HINOKI_TYPE)
									if (wai_1shot_tid == 0xFF) {
										wai_oneshot(wait_timer);
									}
									else {
										wai_tsk((UWORD)((wait_timer / 10) + 1));
									}
#else
									wai_oneshot(wait_timer);
#endif
									if ((SYS_DSE1 != DSE1()) || (SYS_DSE2 != DSE2())) {
						 				TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
										snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
										rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
										exi_tsk();
									}
									if ((SYS_DualRestrictionStatus & 0x02) != 0x02) {	/* 原稿蓄積中じゃなければ */
										AnalogSwitchRXA_Set();
										CML_RelayOn();
										TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_TRANSFER_D_IN;
										snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
										rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
										exi_tsk();
									}
								}
				 				TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
								snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
								rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
								exi_tsk();
							}
 #else
 							/*---------------------------*/
							/**   二次応答リレー制御     */
							/*---------------------------*/
							DialIn2ndAnswerRelayControl( DIAL_IN_FAX );
							/*-----------------------*/
							/** メイン・タスクへ通知 */
							/*-----------------------*/
							TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_TRANSFER_D_IN;
							snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
							rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
							/*-----------------*/
							/** 自タスクの終了 */
							/*-----------------*/
							exi_tsk();
 #endif
							break;
															/*-------------------------------------*/
					case	DETECT_D_IN_TEL1		:		/**           ＴＥＬ１着信             */
					case	DETECT_D_IN_TEL2		:		/**			  ＴＥＬ２着信             */
					case	DETECT_D_IN_TEL1_TEL2	:		/**		  ＴＥＬ１・ＴＥＬ２着信       */
															/*-------------------------------------*/
								/*---------------------------*/
								/** ＤＴＭＦ検出タスクの削除 */
								/*---------------------------*/
								del_tsk(&tskno_ReceiveDTMFTask);
								SYB_DialInNoNumberSignal   = 0;
								/*-------------------------------------*/
								/**  擬似ベル鳴動時間Ｔｉｍｅｒセット  */
								/*-------------------------------------*/
								NCU10msTimer.Time			= ( SYB_Dialin.BellTime * 100 );
								NCU10msTimer.SendMBX		= mbxno.NCU_DialInAutoSwitchTask;
								NCU10msTimer.ReturnValue	= DETCTT_D_IN_TEL_TIMEUP;

								tskno_CMN_WatchTimer10msTask = 0xFFFF;
								cre_tsk(&tskno_CMN_WatchTimer10msTask, TSK_CMN_MAN_TIMER10MSTASK, &NCU10msTimer);
								/*---------------------------------*/
								/**   内線指定受信完了リレー制御   */
								/*---------------------------------*/
								if( RxDialInAutoSwitchTaskMsg->Message == DETECT_D_IN_TEL1 ){
									DialIn2ndAnswerRelayControl( DIAL_IN_TEL1 );
								}
								else if (RxDialInAutoSwitchTaskMsg->Message == DETECT_D_IN_TEL2) {
									DialIn2ndAnswerRelayControl( DIAL_IN_TEL2 );
								}
								else{		/** DETECT_D_IN_TEL1_TEL2 */
									DialIn2ndAnswerRelayControl( DIAL_IN_TEL1_TEL2 );
								}
								/*---------------------------*/
								/**  ＤＳＥ検出タスク生成    */
								/*---------------------------*/
								tskno_DetectDSETask = 0xFFFF;
								cre_tsk(&tskno_DetectDSETask, TSK_NCU_DETECTDSETASK, &(mbxno.NCU_DialInAutoSwitchTask));
								/*---------------------------*/
								/**     擬似ベル鳴動開始     */
								/*---------------------------*/
								general_ring_data.SendMBX   = mbxno.NCU_DialInAutoSwitchTask;
								general_ring_data.StartTime = 0;
								if (RxDialInAutoSwitchTaskMsg->Message == DETECT_D_IN_TEL1) {
									general_ring_data.RingingTel = TEL1_RINGING;
								}
								else if (RxDialInAutoSwitchTaskMsg->Message == DETECT_D_IN_TEL2) {
									general_ring_data.RingingTel = TEL2_RINGING;
								}
								else {		/** DETECT_D_IN_TEL1_TEL2 */
									general_ring_data.RingingTel = ALL_TEL_RINGING;
								}
								tskno_GenerateRingSignalTask = 0xFFFF;
								cre_tsk(&tskno_GenerateRingSignalTask, TSK_NCU_GENERATERINGSIGNALTASK, &general_ring_data);
							break;
															/*-------------------------------*/
					case	DETECT_TEL1_OFF_HOOK	:		/** 付属電話ＯＦＦ　ＨＯＯＫ検出 */
					case	DETECT_TEL2_OFF_HOOK    :		/** 外付電話ＯＦＦ　ＨＯＯＫ検出 */
					case	DETECT_INPUT_HOOK_KEY	:		/**   回線補足キー入力状態検出   */
															/*-------------------------------*/
							/*-------------------------------------*/
							/** ダイヤル・イン　モジュール終了処理 */
							/*-------------------------------------*/
							DialInAutoSwitchExit();
							/*---------------------------*/
							/**   二次応答リレー制御     */
							/*---------------------------*/
							DialIn2ndAnswerRelayControl(DIAL_IN_OFF_HOOK);
							/*-----------------------*/
							/** メイン・タスクへ通知 */
							/*-----------------------*/
							if( RxDialInAutoSwitchTaskMsg->Message == DETECT_TEL1_OFF_HOOK ){
								NCUStatus						    |= TELEPHONE1_OFF_HOOK;
								TxDialInAutoSwitchTaskMsg.Message	 = MSG_DETECT_TEL1_OFF_HOOK;
							}
							else{
								if( RxDialInAutoSwitchTaskMsg->Message == DETECT_TEL2_OFF_HOOK ){
									NCUStatus							|=  TELEPHONE2_OFF_HOOK;
									TxDialInAutoSwitchTaskMsg.Message	 = MSG_DETECT_TEL2_OFF_HOOK;
								}
								else{
									NCUStatus							|= HOOK_KEY_ON_STATE;
									TxDialInAutoSwitchTaskMsg.Message 	 = MSG_DETECT_INPUT_HOOK_KEY;
								}
							}
							
							snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
							rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
							SYS_HookKeyInputFlag	= 0;
							HookKeyInputFlag	    = 0;
							/*-----------------*/
							/** 自タスクの終了 */
							/*-----------------*/
							exi_tsk();

							break;

					default:

							break;
				}

				break;

													/*---------------------------------------------------------------*/
			case	FROM__NCU_D_IN			:		/** ダイヤル・イン実行タスク（ＮＣＵ＿Ｄ＿ＩＮ）からのメッセージ */
													/*---------------------------------------------------------------*/
																/*-----------------------*/
				switch(RxDialInAutoSwitchTaskMsg->Message){		/** 発生事象に対する処理 */
																/*-----------------------*/
															/*---------------------------------*/
					case	DETECT_D_IN_DSE			:		/**           ＤＳＥ検出           */
															/*---------------------------------*/
							/*-------------------------------------*/
							/** ダイヤル・イン　モジュール終了処理 */
							/*-------------------------------------*/
 							DialInAutoSwitchExit();
							/*-----------------------*/
							/** メイン・タスクへ通知 */
							/*-----------------------*/
						 	TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;

 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
							if (is_class1_rx_enable == PC_RECEIVE_OK) {		/* Class1で呼び出し中の極反検出 */
							 	TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_CL1_D_IN_DSE;
							}
 #endif
							snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
							rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
							/*-----------------*/
							/** 自タスクの終了 */
							/*-----------------*/
							SYS_RingCounter = 0;
							exi_tsk();

							break;

					default:

							break;
				}

				break;
													/*-------------------------------------------------*/
			case	FROM_10MS_TIMER			 :		/**   １０ｍｓタイマー・タスクからのメッセージ     */
													/*-------------------------------------------------*/
																/*-----------------------*/
				switch(RxDialInAutoSwitchTaskMsg->Message){		/** 発生事象に対する処理 */
																/*-----------------------*/
															/*-------------------------------------*/
					case	DETECT_D_IN_DTMF_RCV_TIMEUP	:	/**           ＤＴＭＦ未検出           */
															/*-------------------------------------*/
							/*-------------------------------------*/
							/** ダイヤル・イン　モジュール終了処理 */
							/*-------------------------------------*/
							DialInAutoSwitchExit();
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
							if(( SYB_DialInNoNumberSignal )						/**    非ダイヤルイン回線接続			*/
							 && (is_class1_rx_enable == PC_RECEIVE_OK )) {		/*     且つ、ＰＣ受信可能な場合			*/
									TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_CL1_NON_D_IN;
									SYS_RingCounter = 0;
							}
							else if ((SYB_DialInNoNumberSignal) 				/**    非ダイヤルイン回線接続			*/
							 && ((is_class1_rx_enable == FAX_RECEIVE_ONLY)		/*     且つ、ＦＡＸ受信可能 			*/
							   ||(is_class1_rx_enable == FAX_RECEIVE_ENABLE))
							 && (CMN_CheckMultiLineReceiveEnable() == TRUE)) {	/* 	   且つ、代行受信可能な場合			*/
								TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_TRANSFER_D_IN;
							}
 #else /* PRO_CL1_TELFAX_LAN */
																/*--------------------------------------*/
							if( SYB_DialInNoNumberSignal ){		/**    非ダイヤル・イン回線接続の場合	*/
																/*--------------------------------------*/
								TxDialInAutoSwitchTaskMsg.Message = MSG_DETECT_TRANSFER_D_IN;
							}
 #endif
							else{
								/*---------------------------*/
								/**   二次応答リレー制御     */
								/*---------------------------*/
								DialIn2ndAnswerRelayControl( DIAL_IN_UNMATCH );
								/*-----------------------*/
								/** メイン・タスクへ通知 */
								/*-----------------------*/
						 		TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
								SYS_RingCounter = 0;
							}
							snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
							rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
							/*-----------------*/
							/** 自タスクの終了 */
							/*-----------------*/
							exi_tsk();
							break;
															/*-----------------------------------*/
					case	DETCTT_D_IN_TEL_TIMEUP	:		/**   擬似ベル鳴動期間ＴｉｍｅＵｐ   */
															/*-----------------------------------*/
							/*-------------------------------------*/
							/** ダイヤル・イン　モジュール終了処理 */
							/*-------------------------------------*/
 							DialInAutoSwitchExit();
							/*-----------------------*/
							/** メイン・タスクへ通知 */
							/*-----------------------*/
							TxDialInAutoSwitchTaskMsg.Message = MSG_D_IN_TIMEUP;
							snd_msg(mbxno.MAN_Task, &TxDialInAutoSwitchTaskMsg);
							rcv_msg(mbxno.NCU_DialInAutoSwitchTask, &RxDialInAutoSwitchTaskMsg);
							/*-----------------*/
							/** 自タスクの終了 */
							/*-----------------*/
							exi_tsk();

							break;

					default:
							break;
				}
				break;

 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* Class1ダイヤルイン対応  (ICHOUより) S.Fukui Jul 8,1998 */
			case	FROM_MAIN:
				switch (RxDialInAutoSwitchTaskMsg->Message) {
				case	MSG_CL1_DIALIN_EXIT:
					/*
					* このダイヤルインタスクは子タスクがあるため外部からdel_tskできないために
					* このメッセージでタスクを終了する
					*/
 					DialInAutoSwitchExit();		/* 子タスク終了 */
					exi_tsk();					/* 自タスク終了 */
				default:
					break;
				}
				break;
 #endif
			default:

				break;
		}
	}
#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[DialInAutoSwitchTask処理ルーチン]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		必ず入力してください
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1993/12/06]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void        DialInAutoSwitchExit( void )
{
#if ( PRO_DIALIN == ENABLE )
	S_RelayOff();											/* '94,12,21 By N.S. */
 #if defined (HINOKI2) || defined(HINOKI3)	 /* 2002/01/10 by T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)/* By M.Maeda 2002/09/18 */
/*
** [ダイヤルイン外線でDTMFをたまにとりこぼす不具合 2000/12/12 by K.Okada]
** ダイヤルインDTMF検出時のみ、受信信号レベルゲインを下げている。
** ここでもとの値に戻す
*/
	 	DspRamAccessWriteMethod3(0x0B3C, BackupReceiveLevel, 0x0000);
 #endif
	/*---------------------------------------------*/
	/** ダイヤル・イン　モジュールの子タスクの削除 */
	/*---------------------------------------------*/
	if( tskno_GenerateRingSignalTask != 0xFFFF ){
		del_tsk(&tskno_GenerateRingSignalTask);
	}
	if( tskno_CMN_WatchTimer10msTask != 0xFFFF ){
		del_tsk(&tskno_CMN_WatchTimer10msTask);
	}
	if( tskno_DetectDSETask != 0xFFFF ){
		del_tsk(&tskno_DetectDSETask);
	}
	if( tskno_ReceiveDTMFTask != 0xFFFF ){
		del_tsk(&tskno_ReceiveDTMFTask);
	}

	NCUStatus		&= ~DIALIN_RECEIVE_STATE;
#endif
}

/*************************************************************************
	module		:[ダイヤルインＣＰＵ初期化]
	function	:[
		1.ＤＡＴＡポートへ１を１０ｍＳ以上出力し、ダイヤルインＣＰＵを
		  ＳＴＯＰモードから復帰させる
		2.１０ｍＳ経過後、ナンバーディスプレイ設定を出力する
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		電源ＯＮ時、機器初期化部からコールする
	]
	comment		:[
		停電時ダイヤルインＣＰＵの新規設計に伴う追加処理です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[NCU]
	date		:[1998/10/20]
	auther		:[野瀬敏弘]
*************************************************************************/
#if (PRO_DIALIN == ENABLE) && (PRO_NCU_TYPE == HINOKI_TYPE)
void NCU_DICPU_Initialize(void)
{
	SetDICPU_Disable();	/* ＤＡＴＡポート１出力 */

	/* 少なくとも１０ｍＳの保持が必要なので
	** wai_tsk は２０ｍＳとします。
	*/
	wai_tsk(2);

#if defined(POPLAR_F)
	SetDICPU_Enable();
#else
	if (CHK_NumberDisplayON()) {	/* ナンバーディスプレイＯＮ */
		SetDICPU_Disable();
	}
	else {	/* ナンバーディスプレイＯＦＦ */
		SetDICPU_Enable();
	}
#endif
}
#endif
