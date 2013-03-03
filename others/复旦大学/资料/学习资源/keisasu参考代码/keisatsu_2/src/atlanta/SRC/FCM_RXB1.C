/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_RXB1.C												 */
/*	モジュール	 :															 */
/*				 : FaxRxPhaseB1()											 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : 受信フェーズＢ１											 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------
	File Name	:  FCM_RXB1.C
	Coded By	:  M.HARADA
	Module Name :  FaxRxPhaseB1
	Note		:  受信フェーズＢ１
------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"

#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\ncu_pro.h"	/* 1994.6.23 */
#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */

#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\apl_msg.h"
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
 #include	"\src\atlanta\define\atd_pro.h"
 #include	"\src\atlanta\define\atd_def.h"
#endif
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#if (PRO_CLASS1 == ENABLE)
#include	"\src\atlanta\ext_v\cl1_data.h"
#endif
#include	"\src\atlanta\define\uni_pro.h"

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif

CONST unsigned char far CRTN_Debug = 0;			/* Control chanel retrain test 1996/04/10 Y.M */
#include	"\src\atlanta\define\cmn_pro.h"
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

/* 移植 by SMuratec L.Z.W 2003/07/24 */
#include	"\src\atlanta\define\mlt_pro.h"


#include	"\src\atlanta\ext_v\bkupram.h"
#if 0	/* defined(FRA) */
	void	FaxTelAutoSWAfterTransaction( void );
#endif



/*************************************************************************
	module		:[FaxRxPhaseB1]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/24]
	author		:[原田]
*************************************************************************/
void   FaxRxPhaseB1(void)
{
	UWORD	T1_timer;
	UWORD	T1_timer_max;
	UBYTE	command;
	UBYTE	rxmode_flag;
	UBYTE	afterfaxtransfer_flag;
	UBYTE	DebugFlag;			   /* By S.K 2/22/93 */
	UBYTE	point;
#if 0	/* defined(FRA) */
	UBYTE	voice_result;	/* 95.02.07 by M.HARADA */
	UBYTE	dis_tx_counter;
#endif
#if (PRO_MULTI_LINE == ENABLE)	/* 1997/01/21 Y.Murata */
	UBYTE		i;
#endif
#if (1) /* 特ROM対応	*/
	UBYTE	pos;	/* 2001/04/02 by T.Soneoka */
	UBYTE	name;	/* 2001/04/02 by T.Soneoka */
#endif
#if (PRO_TX_SPEED == V34) /* Modified by H.Kubo 1997/08/06 */
	UBYTE	ret = 0;
#endif /* (PRO_TX_SPEED == V34) */
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
	UBYTE	result_busy_detect;
	result_busy_detect = 0;
#endif
	point = 0;

#if (PRO_CIPHER == ENABLE)
	/* 受信優先のためスクランブルを中断していた場合
	** ここでスクランブル再起動をセットします By Y.Suzuki 1998/06/17
	*/
	if ((SYS_CipherInterruptionOn) && (SYS_CipherRestartEnable != 1)) {
			/*スクランブル中のＦ網着信の場合*/
		while((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_EXEC)
		|| (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_EXEC)){
			/*スクランブル処理が中断されるまで待つ*/
			wai_tsk(10);
		}
		SYS_CipherRestartEnable = 1;
	}
#endif

	/*------------*/
	/*	Phase B1  */
	/*------------*/
	FaxComPhaseStatus			  = FAX_RX_PH_B1;
	FaxComTxPerformingFlag		  = 0;
	FaxComRxPerformingFlag		  = 0;
	rxmode_flag					  = 0;
	afterfaxtransfer_flag		  = 0;
	SYS_TensouJushinFlag		  = 0;	/* By HARADA 1994年6月22日 */
#if 0	/* defined(FRA) */
	dis_tx_counter = 0;
	FRA_GRS_StartFlag = 0;
#endif

	/*----------------*/
	/*	T1 Timer Set  */
	/*----------------*/
	if (ForwardReceiveFlag /* && AttemptRxModeSwitch != SYS_ANS_FAX_READY */ ) { /* 94/10/6 by T.O */
																	/** 転送受信あり & 留守ＦＡＸ待機でない */
		SYS_TensouJushinFlag = 1;
		ForwardReceiveFlag = 0;										/** 転送受信フラグゼロクリア */

#if (PRO_CSDR_ITEM == ENABLE)
		/* 【CSDR-No.12】転送受信時のＴ１タイマーを伸ばす By O.Kimoto 1998/12/15 */
		T1_timer_max = (UWORD)(CHK_UNI_RemoteRxT1Timer()*200);		/* チェック関数をみるようにする	*/
#else
		T1_timer_max = (UWORD)(CHK_UNI_RemoteRxT1Timer()*100);		/* チェック関数をみるようにする	*/
#endif
		afterfaxtransfer_flag  = 1;
	}
	else {
		T1_timer_max = (UWORD)(CHK_T1_Timer()*100);		/* チェック関数をみるようにする	*/
	}
	
	T1_timer = SYS_GeneralTimer;

	while( ( FaxComPerformingFlag == 1 )
	&&( ( UWORD )( SYS_GeneralTimer - T1_timer ) < T1_timer_max )
	&& ( FaxComTxPerformingFlag == 0 )
	&& ( FaxComRxPerformingFlag == 0 )
	&& ( rxmode_flag == 0  )
#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/06 */
	&& ( V8ProcedureRequestFlag == 0 )
#endif /* (PRO_TX_SPEED == V34) */
	&& ( SYS_FaxComStopSwitch() == 0 )){										/** 通信中 & タイムアップなし & 送信中フラグなし
																		& 受信中フラグなし & DCN送出設定 & StopSwitch なし */

		/*----------------------*/
		/*	 (NSF)(CSI)DIS Tx	*/
		/*----------------------*/
		DIS_ReceivedFlag		  = 0;						/** DIS受信フラグをクリアしておく 1997/10/06 T.Yamaguchi */
		MakeDIS_FIF();										/** DISのFIF作成 */
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/6/29 K.Kawata */
		if (CL1_ExtFunctionEnableFlag == 0) {
			MakeNSF_FIF();
		}
#else
		MakeNSF_FIF();									/** NSFのFIF作成  16.Jun'94 Y.Suzuki*/
#endif
#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/06 */
		FCM_TransmitCommand();		/** コマンド送信 */
#else /* (PRO_TX_SPEED == V34) */
		MDM_TransmitCommand();		/** コマンド送信 */
#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/27 */
		if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
			if (SYS_TensouJushinFlag
			&& (CHK_TEL1FaxTransferAvailable()|| CHK_TEL2FaxTransferAvailable())
			&& !(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_INTER_COM)
			&& (AttemptRxModeSwitch != SYS_ANS_FAX_READY) /* ADD BY M.H '94/10/15 */){
				OhPortStatusRead();	/*	OhPortBarrier();	'95,11,16 By N.S. */
				HookTensouOffHookCheck();
			}
		}
#else
		if (SYS_TensouJushinFlag
		&& (CHK_TEL1FaxTransferAvailable()|| CHK_TEL2FaxTransferAvailable())
		&& !(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_INTER_COM)
		&& (AttemptRxModeSwitch != SYS_ANS_FAX_READY) /* ADD BY M.H '94/10/15 */){
			OhPortStatusRead();	/*	OhPortBarrier();	'95,11,16 By N.S. */
			HookTensouOffHookCheck();
		}
#endif

#if 0	/* defined(FRA) */											/* 95/01/21 by M.HARADA */
		dis_tx_counter++;
		if (3 == dis_tx_counter){
			FRA_GRS_StartFlag = 1;
		}
#endif

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
 /* #if defined(POPLAR_F) */
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
		FCM_BusyToneDetectStatus = 0;
		if (CMN_CheckAnswerEnable()) {
			if (SYS_V34ProcedureExecuting() == 0) {
				if ((AttemptRxModeSwitch == SYS_TEL_FAX_READY)
				 || (AttemptRxModeSwitch == SYS_FAX_TEL_READY)
				 || (AttemptRxModeSwitch == SYS_ANS_FAX_READY)) {

					if ((CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT) != DATA_SIGNALING_RATE_V34_BIT) {	/** Ｖ３４リソースが無い */
						if (FCM_DetectFSK == 0) {
							if (FaxComPerformingFlag != 0) {
								result_busy_detect = Busy_ToneDetect();
								if (result_busy_detect == DETECT_TIMEUP) {
									continue;
								}
								else if (result_busy_detect == BUSY_TONE_DET_OK) {
									SYS_PhaseB1StopWaitFlag = 2;	/* BUSY検出 */
									FaxComPerformingFlag = 0;
									afterfaxtransfer_flag  = 1;	/* DCN出さない */
								}
							}
							/* Flagを検出した場合はＦＳＫ受信にいく */
						}
					}
					else {

#if (0)	/* NTT仕様で音声応答中のBusyTone検出の可否スイッチ対応 By O.Kimoto 2003/12/01 */
** 						FCM_BusyToneDetectStatus = 1;
#else
						if (CHK_UNI_IgnoreBusyTone()) {
							FCM_BusyToneDetectStatus = 0;
						}
						else {
							FCM_BusyToneDetectStatus = 1;
						}
#endif

					}
				}
			}
		}
 #else
		if ((AttemptRxModeSwitch == SYS_TEL_FAX_READY)
		 || (AttemptRxModeSwitch == SYS_FAX_TEL_READY )
		 || (AttemptRxModeSwitch == SYS_ANS_FAX_READY)) {	/* for NTT */
		 	if (FaxComPerformingFlag != 0) {
				result_busy_detect = Busy_ToneDetect();
				if (result_busy_detect == DETECT_TIMEUP) {
					continue;
				}
				else if (result_busy_detect == BUSY_TONE_DET_OK) {
					SYS_PhaseB1StopWaitFlag = 2;	/* BUSY検出 */
					FaxComPerformingFlag = 0;
					afterfaxtransfer_flag  = 1;	/* DCN出さない */
				}
			}
			/* Flagを検出した場合はＦＳＫ受信にいく */
		}
 #endif
#endif

#if 0	/* defined(FRA) */
		if( (MDM_ReceiveResponseAndOffHook() == FSK_RECEIVE)
#endif

#if (PRO_TX_SPEED == V34) /* Modified by H.Kubo 1997/08/06 */
 #if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))	/* Add By O.Kimoto 2002/10/15 */

		if (FaxComPerformingFlag) {
			ret = FCM_ReceiveResponse(FCM_CheckDetectCI(), NON_CCRETRAIN);
			FCM_BusyToneDetectStatus = 0;
			if (ret == PHB1_DETECT_BUSY_TONE) {
				if (SYS_PhaseB1StopWaitFlag == 0) {
					SYS_PhaseB1StopWaitFlag = 2;	/* BUSY検出 */
				}
				FaxComPerformingFlag = 0;
				afterfaxtransfer_flag  = 1;	/* DCN出さない */
			}
		}
		FCM_BusyToneDetectStatus = 0;
 #else
		ret = FCM_ReceiveResponse(FCM_CheckDetectCI(), NON_CCRETRAIN);
 #endif
		if ((FaxComPerformingFlag == 1) && (ret == CALL_INDICATOR_RECEIVE)) {
			V8ProcedureRequestFlag = 1;
		}
		else if ((FaxComPerformingFlag == 1) && (ret == FSK_RECEIVE) ) {
#else /* (PRO_TX_SPEED == V34) */
		if( FaxComPerformingFlag && (MDM_ReceiveResponse(FCM_ReceiveResponseTime) == FSK_RECEIVE) ){		/** 応答受信あり & Receiving */
#endif /* (PRO_TX_SPEED == V34) */

			command = CheckHDLC_Command();							/** HDLCコマンドチェック */

			DebugFlag = 0;						 /* By S.K 2/22/93 */
			if(DebugFlag) {
				if(MDM_RxSize[0] == 0) {
					DebugFlag = 1;
				}
				if ((MDM_ModemBuffer[0][2] & NSS_F) != NSS_F) {
					DebugFlag = 1;
				}
			}

#if (1) /* 特ROM対応	*/
			/*
			** リコー(Rifax1200からV850(AL100)に通常の受信を行うと、中継配信してしまう不具合
			** 現象）本来ここではＮＳＳｏｒＮＳＣフレームを受信するところであるが、ＮＳＦフレームを送出してくる
			**       そのＮＳＦフレームは、Ｖ８５０が送出したＮＳＦ＋αである
			**       そのＮＳＦフレームをＮＳＳフレームとして動作（メーカコードのみで動作している）ため、村田の独自機能をチェックし、
			**       こん回は中継配信がおこなわれてしまうという不具合になった
			** 対策）原因はまだ不明であるが、ＮＳＦを送信して、受信したのがＮＳＦフレームの場合、そのフレームを無効とするようにします
			** 2001/04/02 by T.Soneoka
			*/
			pos = 0;
			name = 0;
			while (pos < 8) {		/**	モデムバッファポインター < 8	*/
				if (MDM_RxSize[pos] > FCF_POS) {		/**	受信バイト数 は FCF までより多いか？	*/
					name = MDM_ModemBuffer[pos][FCF_POS];
					if (name == NSF_F) {	/**	NSF	(NSFはXビットは考慮いれてはダメ)*/
						MDM_RxSize[pos] = 0;	/* 受信フレームを無効にする */
					}
				}
				/**	リードポインターインクリメント	*/
				pos++;
			}
			/* ここまで */
#endif

			switch( command ){
				/*------------*/
				/*	 DCS Rx	  */
				/*------------*/
				case  DCS_F		:									/** DCS受信 */
					/* 受信原稿ポーリング取り出し（機種固有Ｓｗ） 念の為、代行受信満杯でポーリング取り出し中、受信を受けたときエラーにする by T.Soneoka 1997/02/21 */
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/19 */
					if ((CheckPollingTxType())
					&&  (SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_PRINT)) {
#else
					if ((CheckPollingTxType())
					&&  ((SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_PRINT)
					  || (SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_FAST_PRINT))) {
#endif
						FaxComPerformingFlag = 0;
					}
					FaxRxDCS_SemiCompatibleCheck();	/** 相手送信機指定ＴＣＦ受信ボーレイト設定 */
					FinalRxMode			 = G3MODE;	/** 確定受信モードセット */
					FaxComRxPerformingFlag = 1;		/** 受信中フラグセット */
					DIS_ReceivedFlag		  = 0;		/** DIS受信フラグ */
					rxmode_flag			 = 1;		/** DCN送出フラグ 未送出設定 */

					MsgFromFaxComToMain.Item	  = FROM_FAXCOM;
					MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
					/*	MsgFromFaxComToMain.SubMessage1 = DISP_AUTO_RX_START;	del Y.M */
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
					if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {
						SYS_FaxCommStage = FCM_FLASH_ROM_WRITING;
					}
					else {
						SYS_FaxCommStage = FCM_RECEIVE;								/* 1994/05/30 Y.M */
					}
#else
					SYS_FaxCommStage = FCM_RECEIVE;								/* 1994/05/30 Y.M */
#endif
					snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
					rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

					FCM_ReceiveResponseTime = TIME_OVER_3SEC;	/* 1995/12/19 */
					FSK_FirstReceivedFlag = 1;	/** 相手がＦＡＸであると確定した */
					break;
				/*------------*/
				/*	 DTC Rx	  */
				/*------------*/
				case  DTC_F		:									/** DTC受信 */
#if defined(FIP)
					if( SYS_FIP_Status & ( FIP_FILLIN_CMD | FIP_LOCALSCAN_CMD
															| FIP_RETRIEVE_CMD )){
						FaxPhaseE(1);
						TransmitError( 0x14, 1 );
					}
#endif
					FinalTxMode			 = G3MODE;		/** 確定受信モードセット */
					FaxComTxPerformingFlag = 1;			/** 送信中フラグセット */
					DIS_ReceivedFlag		 = 0;			/** DIS受信フラグ ゼロクリア */
					rxmode_flag			 = 1;			/** DCN送出フラグ 未送出設定 */
					FSK_FirstReceivedFlag = 1;	/** 相手がＦＡＸであると確定した */
					break;
				/*------------*/
				/*	 NSC Rx	  */
				/*------------*/
				case NSC_F		:										/** NSC受信 */
					if(( RxFirstTimeCompatibleCheckFlag == 1 )
					 && (( SYS_FaxComType == SYS_AUTO_CALLED )	
					  || ( SYS_FaxComType == SYS_MANUAL_RX ))) {			/** 受信コンパチチェック１回目 */
					  	/* 手動受信時のリモート診断の処理追加 1997/06/25  By T.Yamaguchi */
#if (PRO_DIAG == ENABLE) /* by H.Kubo 1998/04/02 */
						if( RxDiagSemiCompatibleCheck() == 1){ /** 相手機がリモート診断ホスト機である */
							FinalRxMode			 = DIAGMODE;	/** 確定受信モード */
							FaxComRxPerformingFlag = 1;			/** 受信中フラグセット */
							DIS_ReceivedFlag		  = 0;			/** DIS受信フラグゼロクリア */
							rxmode_flag			 = 1;			/** DCN送出フラグ 未送出設定 */

							FCM_ReceiveResponseTime = TIME_OVER_6SEC;	/* 1995/12/19 */

#if (PRO_MULTI_LINE == ENABLE)	/* 1997/01/21 Y.Murata */
							for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {		/* 第１回線目かどうか */
								if (CHK_OptionLineBusy((UBYTE)i)) {
									FaxComRxPerformingFlag = 0;
									FaxComPerformingFlag = 0;
									rxmode_flag = 0;
								}
							}
#endif
							break;
						}
						/* break; RDSﾊﾟｽｺｰﾄﾞエラー時に回線断しない 2line上に移動 1998/06/22  By T.Yamaguchi */
#endif /* (PRO_DIAG == ENABLE) */
					}
 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
					else if ((SYS_FaxComType == SYS_REMOTE_DIAG)
						&& (SYB_FlashROM_WriteStatus == ROM_DATA_RXING)) {		/* フラッシュＲＯＭデータ受信中 */
						break;	/* NSF/DISを再送する 1998/05/27  By T.Yamaguchi */
					}
 #endif /* (PRO_RDS_FLASH_ROM_WRITE == ENABLE) */
					
					FaxComPerformingFlag = 0;						/** 通信中フラグ ゼロクリア */
					break;
				/*---------------*/
				/*	 PRI_EOM Rx	 */
				/*---------------*/
#if defined(FRA)
				case PRI_EOM_F	:
					FaxHDLC_Transmit( MCF_F, 0 );	/**	ＭＣＦ送出	*/
					/******************/
					/**	  T2  Timer	 **/
					/******************/
					FaxTimer( 6000 );
					/******************/
					/** T1 TimerReset */
					/******************/
					T1_timer	= SYS_GeneralTimer;
					break;
#endif
				/*------------*/
				/*	 DCN Rx	  */
				/*------------*/
				case DCN_F		:												/** DCN受信 */
					rxmode_flag		   = 1;						/** DCN送出フラグ 未送出設定 */
					FaxComPerformingFlag = 0;						/** 通信中フラグ ゼロクリア */
					ReceiveError(0x12);
					break;
				default			:												/** デフォルト */
					FaxComPerformingFlag = 0;						/** 通信中フラグ ゼロクリア */
					break;
			}
		}
#if (PRO_TX_SPEED == V34) /* this #if is added by H.Kubo 1997/10/24 */
#if (PRO_MODEM == R288F) /* Ported from Clover by H.Kubo 1997/08/06 */
		else { /* V.34 コントロールチャンネル・リトレイン実行 */
			if (CRTN_Debug & 0x01) {
				MDM_SetControlChannelRetrain();
			}
		}
#endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */
	}

#if 0	/* defined(FRA) */
	if (tskno_B1_Bell != 0xFFFF){
		del_tsk(&tskno_B1_Bell);
	}
	GenerateRingEndRelayControl();
#endif


#if (PRO_TX_SPEED == V34) /* Modified by H.Kubo 1997/08/06 */
	if (V8ProcedureRequestFlag == 0) {
#endif /* (PRO_TX_SPEED == V34) */
	if (( FaxComTxPerformingFlag == 0 )
	&&	( FaxComRxPerformingFlag == 0 )
	&&	( SYS_FaxComStopSwitch() == 0 )
	&&	( rxmode_flag == 0	)){													/** 送信中フラグなし & 受信中フラグなし
																					& StopSwitchなし & DCN送出あり設定 */
		/*----------------*/
		/*	T1 Time Over  */
		/*----------------*/
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/05  By T.Yamaguchi */
 /* #if defined(POPLAR_F) */
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
			if (CMN_CheckAnswerEnable()) {
				/* 音声応答中にオフフック検出した場合ＤＣＮ出さない */
				if ((SYS_PhaseB1StopWaitFlag == 1) && ( afterfaxtransfer_flag == 0 )) {
					afterfaxtransfer_flag  = 1;
				}
			}
 #else
			/* 音声応答中にオフフック検出した場合ＤＣＮ出さない */
			if ((SYS_PhaseB1StopWaitFlag == 1) && ( afterfaxtransfer_flag == 0 )) {
				afterfaxtransfer_flag  = 1;
			}
 #endif
#endif
			if( afterfaxtransfer_flag == 0 ){									/** 転送受信なし */
				FaxPhaseE(1);													/** フェーズＥ */
			}
#if defined(DEU) || defined(EUR)	/* 97/04/26 by M.H. */
									/* 欧州仕様追加 by M.H 1999/09/16 */
			if((PIP_TX_Flag == 1) && (RxEOP_ReceiveFlag == 1)){
				FaxComPerformingFlag = 0;
			}else{
				ReceiveError(0x11);
			}
#else
			ReceiveError(0x11);
#endif
	}

	if( SYS_FaxComStopSwitch() == 1 ){													/** StopSwitchあり */
		/*---------------*/
		/*	STOP DCN Tx	 */
		/*---------------*/
		FaxPhaseE(5);															/** フェーズＥ */
		ReceiveError(0x14);
	}
#if (PRO_TX_SPEED == V34) /* Modified by H.Kubo 1997/08/06 */
	} /* end of if (V8ProcedureRequestFlag == 0) */
#endif /* (PRO_TX_SPEED == V34) */
}

