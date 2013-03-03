/**********************************************************************************************************************
	@(#)$Id: fcm_srrx.c,v 1.22 2006/01/10 09:34:05 mi93007 Exp $
	Create        : 2005/07/10
	Author        : 石橋正和
	Description   : 一斉指令受信
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#if !defined (KEISATSU)
	UBYTE NoIsseiRx; 
#else
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\hinoki\define\mpr_pro.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\define\m_param.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"

BOOL IsseiRxDCN_Received; /* DCNを受信したか否か */

/**************************************************************************************************/
/**
	@brief		一斉指令受信
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/10 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiRx(
			BOOL bshirei) /* 指令起動信号の有無 */
{
#if defined (KEISATSU) /* 警察FAX 05/09/20 石橋正和 */
	/* 指令起動受信の場合、属性が不定だった 06/01/10 石橋正和 */
	if (bshirei == TRUE) {
		FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_ISSEI;
		if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SCRAMBLE_KANYU) {
			FCM_ExecutingS1Info.Available = FALSE;
		}
		else {
			FCM_ExecutingS1Info.Available = TRUE;
		}
		if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SENYOU) {
			FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
		}
		else {
			FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
		}
	}
	
	FCM_S1_Scramble = FCM_ExecutingS1Info.Available;
	if (CMN_CheckScrambleSwOn() == FALSE) { /* 背面スイッチがOFFの場合 */
		FCM_S1_Scramble = FALSE;
	}
	
	if (FCM_ExecutingS1Info.Method == SYS_S1_SENYO) {
		FCM_S1_Senyo = TRUE;
	}
	else {
		FCM_S1_Senyo = FALSE;
	}
#endif
	
	/* SYS_TRANSFER_AUTO_CALLEDの動きを参照 */
	
	/* ForwardReceiveFlag = 1; */					/** 転送受信フラグセット */
	/* BackUpForwardReceiveFlag = 1; */			/** 転送受信バックアップフラグセット */
	
	
	
	/* SYS_FaxComType = SYS_AUTO_CALLED; */		/* 交信種別再設定 */
	SYS_FaxComType = SYS_MANUAL_RX;


	/* GetFaxComTxType(); */						/** 送信タイプ確定 */
	SYS_FaxComTxType = SYS_MEMORY_TRANSMIT; /* なぜかこうなっている */
	
	
	
	/*-------------*/
	/** ＬＣＤ表示 */
	/*-------------*/
	SYS_FaxCommStage = FCM_CALLED;
	MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
	snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

	rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

	/* 警察FAX DVT_ID81 Added By SMuratec 李 2005/12/21 */
	if (bshirei == TRUE) {
		IsSHIREIKido = FALSE;
	}

	FCM_IsseiRxBody(bshirei);

	if (bshirei == TRUE) {
		SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_FAXCOM;
		if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
			SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_SHIREI_IDLE;
		}
		else {
			SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_IDLE;
		}
	}
	
	/* ﾎﾟｰﾘﾝｸﾞ送信でRTN受信した時T.4.2にする 1996/10/30 Y.Murata */
	CheckAllErrorPage();					/** T.4.2エラーを出すかどうかチェック */
}

/**************************************************************************************************/
/**
	@brief		一斉指令受信本体
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはAutoCalled() + FaxReceive()
	@date		2005/07/11 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiRxBody(
				BOOL bshirei) /* 指令起動信号の有無 */
{
	UBYTE ring_time; /* 一斉鳴動時間 */
	UBYTE result;
	
	IsseiRxDCN_Received = FALSE;
	
	FaxComPerformingFlag = 1;			/** 通信中フラグセット */

	FaxcomRelayControl();				/** リレ～セット */
#if defined(POPLAR_F)
	MDM_SetAnswerMode();			/** モデムモードセット */
#endif
	FaxComTXorRX_Sign = RX_COM_MODE;	/** 受信コマンドセット */
	
	
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {		/**	標準ラインにて受信時	*/
		SYS_RingCounter = 0;
	}
	else {
		SYS_RingCounterExt = 0;
	}
#else
	SYS_RingCounter = 0;
#endif
	
	if (FaxComPerformingFlag != 1) {
		goto END;
	}
	
	FaxComStartTime = SYB_CurrentTime;
	
	SYS_FCM_StartTime = SYS_1SecGeneralTimer; /* ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用 */

	/* ジャーナル通番セーブ */
	JournalTxTotalCount				= SYB_TxTotalCount;			/* 通信開始時間と終了時間で日付が変わった場合は、 */
	JournalRxTotalCount				= SYB_RxTotalCount;			/* 通信開始時の日付に合わせるためにセーブしておく */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
	JournalTxTotalCountExt			= SYB_TxTotalCountExt;
	JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_JournalWorkFile.Number = JournalRxTotalCount;
	PAT_JournalWorkFile.StartTime = FaxComStartTime;

	PAT_JournalDataToImage(NUMBER);
	PAT_JournalDataToImage(START);
#endif
	
	MonitorSpeakerOn(); /* モニタースピーカON */
	FCM_S1_Preamble3S = TRUE; /* 最初のDCSのプリアンブルは3秒 */
	
	if (bshirei == TRUE) {
		result = FCM_IsseiRxPhaseB1(FCM_ISSEI_RX_WAIT_OPR); /* フェーズB1 */
		FaxComStartTime = SYB_CurrentTime;
		
		
		
		/* 指令起動受信の場合は、FCMタスク起動後に属性が変わることがある 06/01/10 石橋正和 */
		FCM_S1_Bypass = CHK_BypassS1();
		S1_BypassS1(FCM_S1_Bypass); /* S1バイパスのセット */
		S1_SetScrambleAvailable(CHK_ScrambleAvailabe()); /* スクランブラの有効/無効のセット */
		
		FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_ISSEI;
		
		if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SCRAMBLE_KANYU) {
			FCM_ExecutingS1Info.Available = FALSE;
		}
		else {
			FCM_ExecutingS1Info.Available = TRUE;
		}
		FCM_S1_Scramble = FCM_ExecutingS1Info.Available;
		if (CMN_CheckScrambleSwOn() == FALSE) { /* 背面スイッチがOFFの場合 */
			FCM_S1_Scramble = FALSE;
		}
		
		if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SENYOU) {
			FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
			FCM_S1_Senyo = TRUE;
		}
		else {
			FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
			FCM_S1_Senyo = FALSE;
		}
		
		
		
	}
	else {
		result = FCM_IsseiRxPhaseB1(FCM_ISSEI_RX_WAIT_CNG); /* フェーズB1 */
	}
	
	FCM_S1_Preamble3S = FALSE;
	if (!CHK_LineMonitor()) {
		MonitorSpeakerOff(); /* モニタースピーカOFF */
	}
	
	switch (result) {
	case FCM_ISSEI_RX_DETECT_CNG: /* CNG検出 */
		FCM_S1_Scramble = FALSE;
		FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;
		FCM_ExecutingS1Info.Available = FALSE;
		AutoCalled();
		return;
	case FCM_ISSEI_RX_START_TX: /* スタートキー押下 */
		SYS_FaxComType = SYS_ISSEI_KIDO_TX;
		FCM_IsseiTx(TRUE); /* 一斉指令送信 */
		return;
	default:
		break;
	}
	
	while ((FaxComPerformingFlag == 1) && (FaxComRxPerformingFlag == 1)) {
		
		/**********************************************************************/
		/* FaxReceive()の部分 */
		
		RxEOM_ReceiveFlag  = 0;			/*「ＥＯＭ受信」フラグ	*/
		
		if ((FaxComPerformingFlag == 1) && (SYS_FaxComStopSwitch() == 0)) { /* 通信中 & StopSwitchなし */
			FaxComPhaseStatus = FAX_RX_PH_B2; /* Phase B */
			
			FCM_IsseiRxNegotiate(); /* 受信方法確定 */
			RxModeChangeRequestedFlag = 0; /* 受信モード変更要求なし */
			
			FaxTimer(50); /* R.3.3対策 FSK->PIX時のS1経由への切り替え 05/12/22 石橋正和 */
			
			while( ( FaxComPerformingFlag == 1 )
				&& ( RxModeChangeRequestedFlag == 0 )
				&& ( SYS_FaxComStopSwitch() == 0 )){			/** 通信中 & 受信モード変更要求なし & StopSwitchなし */
				
				/****************************************************/
				FCM_IsseiRxPhaseC(); /* フェーズC */
				
				if (FaxComPerformingFlag == 1) {	/**	通信中 (画データ受信結果ＯＫ)	*/
					FCM_IsseiRxPostMessage(); /* 命令受信 */
				}
				if (FaxComPerformingFlag == 1) { /* 画データ受信，ポストメッセージ受信ＯＫ */
					FCM_IsseiRxPhaseD(); /* 受信フェーズＤ */
				}
				else {		/**	画データ受信ＮＧ／ポストメッセージ受信ＮＧ	*/
					/* メモリ受信ページを削除(但し設定により受信原稿を印字する) */
					if (RxPmType == RX_MEMORY) {	/**	メモリ受信	*/
						if (((RxPageFinishStatus == RX_PAGE_END) || (RxPageFinishStatus == RX_ERROR))
							&& (SYS_RxMemoryFileItem == SYS_MEM_RX_FILE)	/* 通常の受信原稿のみ 1998/05/11  By T.Yamaguchi */
							&&	(CHK_PostMsgErrRxDocPrint() != 0)) {		/**	命令受信ＮＧでも受信原稿プリントする時	*/
							/**	受信ページを登録 (メインタスクへ通知)	*/
							SendMsgFaxComToMain( MSG_RX_PRINT_PAGE );
						}
						else {
							if (SYS_FaxComIndexConflictStatus == 0) {
								MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );
							}
						}
					}
				}
				
				/****************************************************/
				
				/* RxModeChangeRequestedFlag = 1; */
				/* RxEOM_ReceiveFlag  = 1; */
			}
		}
		
		if ((FaxComPerformingFlag == 1) && ( SYS_FaxComStopSwitch() == 1 )) { /* 通信中 & StopSwitchあり */
			FaxPhaseE(5); /* フェーズE */
			ReceiveError(0x14);
		}
		/**********************************************************************/
		
		if ((FaxComPerformingFlag == 1) && (RxEOM_ReceiveFlag == 1)) {
			FCM_IsseiRxPhaseB1(FCM_ISSEI_RX_WAIT_NORMAL);
		}
	}
	
END:
	SYS_CurrentExecutingCommand = 0x00;		/* NULL */
	PollingTxFirstPageFlag = 0;
	
	TxReceiptRequestFlag = 0;
	
	FCM_IsseiFixRxDocStatus(); /* 受信原稿のステイタスを確定させる */
	
	if (bshirei == FALSE) {
		if (IsseiRxDCN_Received == TRUE) { /* DCNを受信した場合 */
			ring_time = SYB_MachineParameter[M_PARA_SW_I2]; /* 一斉鳴動時間 */
			if (ring_time > 0) {
				MonitorSpeakerOn(); /* モニタースピーカON */
				
				FCM_IsseiVoiceReq((UWORD)ring_time); /* 会話予約動作 */
				
				if (!CHK_LineMonitor()) {
					MonitorSpeakerOff(); /* モニタースピーカOFF */
				}
			}
		}
	}
	
	IsseiRxDCN_Received = FALSE;
}

/**************************************************************************************************/
/**
	@brief		一斉指令受信 フェーズB1
	
	@li			
	@param		
	@return		FCM_ISSEI_RX_CONTINUE:		一斉受信継続
				FCM_ISSEI_RX_DETECT_CNG:	CNG検出(G3受信へ移行)
				FCM_ISSEI_RX_START_TX:		スタートキー押下
	@note		オリジナルはFaxRxPhaseB1()
	@date		2005/07/11 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE FCM_IsseiRxPhaseB1(
					UBYTE type) /* 種別(FCM_ISSEI_RX_WAIT_NORMAL/FCM_ISSEI_RX_WAIT_CNG/FCM_ISSEI_RX_WAIT_OPR */
{
	UWORD	T1_timer;
	UWORD	T1_timer_max;
	UBYTE	command;
	UBYTE	rxmode_flag;
	UBYTE	afterfaxtransfer_flag;
	UBYTE mdm_ret;
	UBYTE result;
#if (PRO_MULTI_LINE == ENABLE)	/* 1997/01/21 Y.Murata */
	/* UBYTE		i; */
#endif
	
	T1_timer_max = 0;
	result = FCM_ISSEI_RX_CONTINUE;
	
	/*------------*/
	/*	Phase B1  */
	/*------------*/
	FaxComPhaseStatus			  = FAX_RX_PH_B1;
	FaxComTxPerformingFlag		  = 0;
	FaxComRxPerformingFlag		  = 0;
	rxmode_flag					  = 0;
	afterfaxtransfer_flag		  = 0;
	SYS_TensouJushinFlag		  = 0;	/* By HARADA 1994年6月22日 */

	/*----------------*/
	/*	T1 Timer Set  */
	/*----------------*/
	if (ForwardReceiveFlag) { /* 94/10/6 by T.O */ /* 転送受信あり */
		SYS_TensouJushinFlag = 1;
		ForwardReceiveFlag = 0;										/** 転送受信フラグゼロクリア */
		
		afterfaxtransfer_flag  = 1;
	}
	
	if (type == FCM_ISSEI_RX_WAIT_CNG) {
		T1_timer_max = (UWORD)(CHK_IsseiRxTimeout() * 100);
	}
	else if (type == FCM_ISSEI_RX_WAIT_NORMAL) {
		T1_timer_max = (UWORD)(FCM_ISSEI_RX_D_B_TIME / 10);
	}
	T1_timer = SYS_GeneralTimer;

	while( ( FaxComPerformingFlag == 1 )
		&& ( FaxComTxPerformingFlag == 0 )
		&& ( FaxComRxPerformingFlag == 0 )
		&& ( rxmode_flag == 0  )
		&& ( SYS_FaxComStopSwitch() == 0 )){	/** 通信中 & タイムアップなし & 送信中フラグなし
													& 受信中フラグなし & DCN送出設定 & StopSwitch なし */
		if (type != FCM_ISSEI_RX_WAIT_OPR) {
			if ((UWORD)(SYS_GeneralTimer - T1_timer) >= T1_timer_max) {
				break;
			}
		}

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
		
		switch (type) {
		case FCM_ISSEI_RX_WAIT_CNG: /* CNGも待つ */
			mdm_ret = MDM_ReceiveResponseOrCNG(FCM_ReceiveResponseTime);
			break;
		case FCM_ISSEI_RX_WAIT_OPR: /* スタートキー押下、指令起動信号OFFも待つ */
			 mdm_ret = MDM_ReceiveResponseOrIsseiOpr();
			 break;
		case FCM_ISSEI_RX_WAIT_NORMAL: /* FSKのみ待つ */
		default:
			mdm_ret = MDM_ReceiveResponse(FCM_ReceiveResponseTime);
			break;
		}
		
		if (mdm_ret == MDM_DETECT_CNG) { /* CNG受信 */
			result = FCM_ISSEI_RX_DETECT_CNG;
			goto END;
		}
		if (mdm_ret == MDM_ISSEI_TX) { /* スタートキー押下 */
			result = FCM_ISSEI_RX_START_TX;
			goto END;
		}
		if (mdm_ret == MDM_SHIREI_OFF) { /* 指令起動信号OFF */
			FCM_ShireiOff = TRUE;
			FaxComPerformingFlag = 0;
			goto END;
		}
		if (mdm_ret == FSK_RECEIVE) { /** 応答受信あり & Receiving */
			command = CheckHDLC_Command(); /* HDLCコマンドチェック */
			switch(command){
			case  DCS_F		:									/** DCS受信 */
				FaxRxDCS_SemiCompatibleCheck();	/** 相手送信機指定ＴＣＦ受信ボーレイト設定 */
				FinalRxMode			 = G3MODE;	/** 確定受信モードセット */
				FaxComRxPerformingFlag = 1;		/** 受信中フラグセット */
				DIS_ReceivedFlag		  = 0;		/** DIS受信フラグ */
				rxmode_flag			 = 1;		/** DCN送出フラグ 未送出設定 */
				
				if (type == FCM_ISSEI_RX_WAIT_OPR) {
					SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_IDLE;
					SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_SHIREI_FAXCOM;
				}
				
				MsgFromFaxComToMain.Item	  = FROM_FAXCOM;
				MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
				SYS_FaxCommStage = FCM_RECEIVE;								/* 1994/05/30 Y.M */
				snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
				rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

				FCM_ReceiveResponseTime = TIME_OVER_3SEC;	/* 1995/12/19 */
				FSK_FirstReceivedFlag = 1;	/** 相手がＦＡＸであると確定した */
				break;
			case DCN_F		:												/** DCN受信 */
				rxmode_flag		   = 1;						/** DCN送出フラグ 未送出設定 */
				FaxComPerformingFlag = 0;						/** 通信中フラグ ゼロクリア */
				ReceiveError(0x12);
				
				IsseiRxDCN_Received = TRUE;
				
				break;
			default			:												/** デフォルト */
				FaxComPerformingFlag = 0;						/** 通信中フラグ ゼロクリア */
				break;
			}
		}
	}
	
	if ((FaxComTxPerformingFlag == 0)
		&& (FaxComRxPerformingFlag == 0)
		&& (SYS_FaxComStopSwitch() == 0)
		&& (rxmode_flag == 0)){ /** 送信中フラグなし & 受信中フラグなし & StopSwitchなし & DCN送出あり設定 */
		/*----------------*/
		/*	T1 Time Over  */
		/*----------------*/
			if(afterfaxtransfer_flag == 0){ /* 転送受信なし */
				FaxPhaseE(1); /* フェーズＥ */
			}
			ReceiveError(0x11);
	}
	
	if(SYS_FaxComStopSwitch() == 1) { /* StopSwitchあり */
		/*---------------*/
		/*	STOP DCN Tx	 */
		/*---------------*/
		FaxPhaseE(5); /* フェーズＥ */
		ReceiveError(0x14);
	}
	
END:
	return result;
}

/**************************************************************************************************/
/**
	@brief		一斉指令受信 受信方法の確定
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはFaxRxNegotiate()
	@date		2005/07/11 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiRxNegotiate(void)
{
	FaxRxDCS_SemiCompatibleCheck(); /* 相手送信機指定ＴＣＦ受信ボーレイト設定[DCS/CTC] */
	
	if(RxFirstTimeCompatibleCheckFlag == 1) {
		FCM_IsseiRxModeCheck(); /* 機能確定 */
		RxFirstTimeCompatibleCheckFlag = 0;
	}
	else {
		GetMultiFrameLine();
	}
	
	RxECM_Mode = ECM_OFF;
	TxECM_Mode = ECM_OFF;
	
	RxCompatibleCheck();
	ResultECM_ModeSet();
}

/**************************************************************************************************/
/**
	@brief		一斉指令受信 機能の確定
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはRxOriginalModeCheck()
	@date		2005/09/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiRxModeCheck(void)
{
	Partner300dpiAbility = NO;
	PartnerEFineAbility = NO;

	/**	フレーム取り込み	*/
	GetMultiFrameLine();

	if((ID_FrmName != NO) && (StandardID[0] == NULL)) {	/**	TSI 受信	*/
		/**	ID 取り込み	*/
		GetPartnerID();
	}

	FaxComResult &= ~ECM_MODE_SET;

	/*	代行受信の処理	*/
	if(SYS_RxMemoryFileItem == NULL) {
		/* プリンタ受信/メモリ受信を決定 */
		switch (QueryReceiveType()) {
		case MEMORY_RX:
			SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
			break;
		case PRINTER_RX:
			break;
		case SUBSTITUTE_PRINTER_ERROR:
			FaxCompatibleErrorCode = SUBSTITUTE_PRINTER_ERROR;
			FaxComPerformingFlag = NO;
			return;
		case PRINTER_ERROR:
			FaxCompatibleErrorCode = PRINTER_ERROR;
			FaxComPerformingFlag = NO;
			return;
		default:
			break;
		}
	}
	
	if (SYS_RxMemoryFileItem == SYS_MEM_RX_FILE) { /* 通常のメモリ受信 */
		if(SetUpMemoryRx() == NO) {/**	空きがなければ、エラー処理	*/
			FaxCompatibleErrorCode = SUBSTITUTE_PRINTER_ERROR/*	代行受信バッファフルエラー	*/;
			FaxComPerformingFlag = NO;
			return;
		}
	}
	
	if(SYS_RxMemoryFileItem != NULL) { /* メモリ受信実行 */
		/*SetMemoryRxDocFile();	*/
		SYS_DocBlock.Index.Item	 = SYS_RxMemoryFileItem;
		SYS_DocBlock.Index.No	 = SYS_RxMemoryFileNo;
		SYS_DocBlock.Index.Page	 = SYS_RxMemoryFilePage;
		SYS_DocBlock.Index.BoxNumber = SYS_RxMemoryFileBoxNumber; /* 1997/01/13  By T.Yamaguchi */
	}
#if (PRO_PRINTER_RX == ENABLE)/* 13.Apr'94 */
	else{/**	プリンタ受信	*/
		PRN_PreOpen();				/**	プリンタプリオープン	*/
		PrinterRxPreOpenFlag = 1;
	}
#endif
	
	/**	通信の開始を MAN_TSK に知らせる	*/
	MsgFromFaxComToMain.Item = FROM_FAXCOM;
	MsgFromFaxComToMain.Message = MSG_FAXCOM_RX_START;
	snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
	rcv_msg(mbxno.FCM_Task, &FcomMsg);		/* メインよりメッセージ受信 */
}

/**************************************************************************************************/
/**
	@brief		一斉指令受信 フェーズC
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはFaxRxPhaseC()
	@date		2005/07/11 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiRxPhaseC(void)
{
	FaxComPhaseStatus = FAX_RX_PH_C_BEFORE_PIX;

	FCM_SetIsseiRxPageData(); /* 受信ページデータセット */

	/**	変数初期化	*/
	RxPageFinishStatus = RX_PAGE_END;
	RxWholePageCompletedFlag = 0;
	RxEOR_ReceiveFlag = 0;
	PRI_Q_RxFlag = 0;
	PRI_Q_RxCount = 0;
	DEU_Return_Flag = 0; /* 1997/06/02  By T.Yamaguchi DEU条件削除 */
	PIP_TX_Flag = 0;	/* 1997/06/02  By T.Yamaguchi DEU条件削除 */ /* 97/04/26 by M.H. */

	if (FaxComPerformingFlag != 1) {
		return;
	}
	/* (RxWholePageCompletedFlag == 0) */
	
	RxECM_PixTimeoutFlag = 0;	/**	ＥＣＭタイムアウト回避フラグをクリア	*/	/* Oct.13.1994 */
	
	FCM_StartIsseiRxPix(); /* 高速画データ受信待ち */
	
	if (FaxComPerformingFlag != 1) { /* 高速画データ受信ＮＧ */
		/* 部分ページ受信途中での高低速識別で、交信が途絶えた時(PPS_NULL受信後)、中途半端なインデックスが残ってしまう。
		 * ここで、中途半端なのがあれば、そのページを削除します。*/
		if (RxPmType == RX_MEMORY) {	/**	メモリ受信	*/
			/**	メモリファイルクローズし，受信ページ削除	*/
			if (SYS_FaxComIndexConflictStatus == 0) {
				MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );
			}
		}
		return;
	}
	
	/** Ｔ３０モニタ用データセット	*/
	SaveT30TimingData( SYS_T30_START_TIME );
	SaveT30Data( SYS_T30_RX_PIX, &MDM_ModemBuffer[0][0], 0 );

	/**	表示切替指示(画データ受信中)	*/
	SYS_FaxCommStage = FCM_RECEIVE_SET;		/*	May.30.1994	*/
	SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );

	/*------------------*/
	/**	画データ受信	*/
	/*------------------*/
	FaxComPhaseStatus = FAX_RX_PH_C_PIX;
#if (PRO_COM_CODEC_TYPE == SOFTWARE)
	RxPageFinishStatus = SCDC_RxPix(ECM_OFF, RxPmType );
#else
	RxPageFinishStatus = MDM_RxPix(ECM_OFF, RxPmType );
#endif
	MDM_RxPixClose(ECM_OFF);
	FaxComPhaseStatus = FAX_RX_PH_C_AFTER_PIX;
	
	/*--------------------------------------------------*/
	/**	画データ受信結果を確認 (エラーコードをセット)	*/
	/*--------------------------------------------------*/
	if (RxPageFinishStatus == RX_TMOUT) { /* 受信フレームタイムアウト */
		ReceiveError( 0x52 ); /* Ｒ．５．２ */
	}
	else {
		CheckRxPixResultSub(); /* 画データ受信結果を確認 */
	}
#if 0
//	if (FaxComPerformingFlag == 1) {	/**	通信中 (画データ受信結果ＯＫ)	*/
//		FCM_IsseiRxPostMessage(); /* 命令受信 */
//	}
//	if (FaxComPerformingFlag == 1) { /* 画データ受信，ポストメッセージ受信ＯＫ */
//		FCM_IsseiRxPhaseD(); /* 受信フェーズＤ */
//	}
//	else {		/**	画データ受信ＮＧ／ポストメッセージ受信ＮＧ	*/
//		/* メモリ受信ページを削除(但し設定により受信原稿を印字する) */
//		if (RxPmType == RX_MEMORY) {	/**	メモリ受信	*/
//			if (((RxPageFinishStatus == RX_PAGE_END) || (RxPageFinishStatus == RX_ERROR))
//				&& (SYS_RxMemoryFileItem == SYS_MEM_RX_FILE)	/* 通常の受信原稿のみ 1998/05/11  By T.Yamaguchi */
//				&&	(CHK_PostMsgErrRxDocPrint() != 0)) {		/**	命令受信ＮＧでも受信原稿プリントする時	*/
//				/**	受信ページを登録 (メインタスクへ通知)	*/
//				SendMsgFaxComToMain( MSG_RX_PRINT_PAGE );
//			}
//			else {
//				if (SYS_FaxComIndexConflictStatus == 0) {
//					MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );
//				}
//			}
//		}
//	}
#endif
}

/**************************************************************************************************/
/**
	@brief		一斉指令受信 受信ページデータセット
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはSetRxPageData()
	@date		2005/07/11 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_SetIsseiRxPageData(void)
{
	RxPmType = RX_MEMORY; /* メモリ受信を指定 */
	
	/* 原稿制御ブロックに最少１ラインバイト長をセット */
	SYS_DocBlock.MinimumLineSize = CheckMinimumLineSize( RxMinimumScanningTime, RxBaudRate );

	SYS_DocBlock.DocLength = SYS_NO_LIMIT_PAGE_LENGTH; /* 原稿制御ブロックに最大受信原稿長(無制限)をセット */

	/*　原稿制御ブロックにファイルインデックスをセットする */
	SYS_DocBlock.Index.No	= SYS_RxMemoryFileNo;				/*	受信メモリファイル番号		*/
	SYS_DocBlock.Index.Page = SYS_RxMemoryFilePage;				/*	受信メモリページ			*/
	SYS_DocBlock.Index.Item = SYS_RxMemoryFileItem;				/*	受信メモリファイルアイテム	*/
	SYS_DocBlock.Index.BoxNumber = SYS_RxMemoryFileBoxNumber;	/*	受信メモリファイルアイテム	*/
}

/**************************************************************************************************/
/**
	@brief		一斉指令受信 高速画データ受信待ち
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはStartRxPix()
	@date		2005/07/11 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_StartIsseiRxPix(void)
{
	UBYTE fcf;
	
	if (FaxComPerformingFlag != 1) {
		return;
	}
	
	if (SYS_FaxComStopSwitch()) { /* ストップキー入力ありの時 */
		FaxComPerformingFlag = 0;
		return;
	}
	
	switch (MDM_FskHighSpeedCheck(RxBaudRate, ECM_OFF)) { /* 高低速識別 */
	case TRN_RECEIVE: /* 高速信号受信 */
		break;
	case FSK_RECEIVE: /* ＦＳＫ受信 */
		fcf = CheckReceivedFCF();
		
		FaxPhaseE(4); /* 通信終了(DCNなし) */
		ReceiveError(0x31); /* R.3.1 */
		break;
	default: /* タイムアウト */
		FaxPhaseE(4); /* 通信終了(DCNなし) */
		ReceiveError(0x31); /* R.3.1 */
		break;
	}
}

/**************************************************************************************************/
/**
	@brief		一斉指令受信 ポストメッセージ受信
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはRxECM_PixData()
	@date		2005/07/11 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiRxPostMessage(void)
{
	UBYTE rx_fcf;
	UBYTE ret;

	if (FaxComPerformingFlag != 1) { /* 通信中でない場合 */
		return;
	}
	if (SYS_FaxComStopSwitch()) { /* ストップキー入力ありの場合 */
		FaxComPerformingFlag = 0;
		return;
	}
	
	ret = MDM_ReceiveCommand((UWORD)TIME_OVER_6SEC); /* コマンド受信 */
	
	if (ret != FSK_RECEIVE) { /* コマンドを受信しなかった場合 */
		FaxPhaseE(4); /* 通信終了(DCNなし) */
		ReceiveError(0x42); /* R.4.2 */
		return;
	}
	
	rx_fcf = CheckReceivedFCF();	/**	受信命令ＦＣＦ確認	*/
	AnalyzeRxPostMessageFrame();	/* ＰＲＩ－Ｑ受信数をカウントするため  Oct.31.1994 */
	
	if (rx_fcf == DCN_F) { /* DCN受信 */
		FaxPhaseE(4); /* 通信終了(DCNなし) */
		ReceiveError(0x31); /* R.3.1 */
		
		IsseiRxDCN_Received = TRUE;
	}
	
#if 0
// #if (PRO_PAPER_TYPE == ROLL_PAPER)
// 	if (RxPmType == RX_PRINTER) {
// 		if (WaitRxPaperCut( 25 ) == 0) {	/**	記録紙カット中→２．５秒経過	*/
// 			
// 		}
// 		CheckRxPrinterError();				/**	プリンタエラーの種類を確認	*/
// 	}
// #endif
#endif
}

/**************************************************************************************************/
/**
	@brief		一斉指令受信フェーズD
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはFaxRxPhaseD()
	@date		2005/07/11 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiRxPhaseD(void)
{
	UBYTE tmp_rx_fcf;

	FaxComPhaseStatus = FAX_RX_PH_D;

	/**	表示切替指示(ポストメッセージ受信)	*/
	SYS_FaxCommStage = FCM_ERROR_LINE;		/*	"エラーライン／受信ライン"表示用	Jul.14.1994	*/
	SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );

	/**	PRI-Qビットをマスクしてテンポラリにセット	*/
	tmp_rx_fcf = RxFCF & (UBYTE)~PRI_Q_F;

	/* 既に受信しているコマンドをチェック */
	if ((tmp_rx_fcf == MPS_F) || (tmp_rx_fcf == EOM_F) || (tmp_rx_fcf == EOP_F)) { /* MPS/EOM/EOP受信 */
		if (tmp_rx_fcf == EOM_F) { /* ＥＯＭ */
			RxModeChangeRequestedFlag = 1;
			RxEOM_ReceiveFlag = 1;
		}
		else if (tmp_rx_fcf == EOP_F) {	/**	ＥＯＰ	*/
			RxModeChangeRequestedFlag = 1;
			RxEOP_ReceiveFlag = 1;
		}
		
		RxWholePageCompletedFlag = 1; /* 物理ページ受信完了 */
		
		if ((RxPageFinishStatus == RX_PAGE_END)
			||	(RxPageFinishStatus == RX_ERROR)
			||	(RxPageFinishStatus == RX_PRT_ERR)) {	/**	ページエンド,画質エラー,プリンタエラー	*/
			/**	受信ページ数，メモリファイルページ数を＋１	*/
			SYS_RxTotalPage++;
			SYS_RxMemoryFilePage++;
			SYS_RxPrintFilePage++;
			if ((SYS_RxMemoryFileItem == SYS_MEM_RX_FILE)
				|| (SYS_RxPrintFileItem == SYS_MEM_RX_FILE)) { /** 標準メモリ受信||メモリデュアルオープン原稿||バッファリング受信 */
				SendMsgFaxComToMain( MSG_RX_PRINT_PAGE ); /* メモリ受信１ページ終了をメインタスクへ通知 */
			}
		}
		else {
			/**	メモリ受信で異常ページの場合は，受信ページを削除	*/
			if (RxPmType == RX_MEMORY) {
				if (SYS_FaxComIndexConflictStatus == 0) {
					MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );	/* Jul.04.1994 */
				}
			}
			CheckRxPixResultSub(); /* エラーコードをセット */
		}
	}
	else { /* 他のコマンドを受信した場合 */
		ReceiveError( 0x42 );	/**	Ｒ．４．２	*/
		if (RxFCF == DCN_F) {	/**	ＤＣＮを受信	*/
			
			FaxPhaseE( 4 );		/**	通信終了（ＤＣＮなし）	*/
			
			IsseiRxDCN_Received = TRUE;
		}
		else {
			/* FaxPhaseE( 1 ); */		/**	通信終了（ＤＣＮあり）	*/
			FaxPhaseE( 4 );		/**	通信終了（ＤＣＮなし）	*/
		}
	}
	
	if (tmp_rx_fcf == EOP_F) { /* EOPを受信した場合 */
		FCM_IsseiRxReceiveDCN(); /* DCN受信 */
	}
}

/**************************************************************************************************/
/**
	@brief		DCN受信
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはReceiveDCS()
	@date		2005/07/23 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiRxReceiveDCN(void)
{
	if (FaxComPerformingFlag != 1) { /* 通信中でない場合 */
		return;
	}
	
	if (MDM_ReceiveCommand((UWORD)TIME_OVER_6SEC) == FSK_RECEIVE) { /* 命令受信ＯＫ */
		/* 受信ポストメッセージを解析 */
		ReceiveResponseFlag = 1;
		AnalyzeRxPostMessageFrame();
		
		if (RxFCF == DCN_F) {		/**	ＤＣＮを受信	*/
			FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
			
			IsseiRxDCN_Received = TRUE;
		}
		else {							/**	その他のフレームを受信	*/
			FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）add 96/06/25 S.Takeuchi	*/
			ReceiveError( 0x11 );			/**	Ｒ．１．１	*/
		}
	}
	else {		/**	Ｔ２タイムアウト	*/
		ReceiveResponseFlag = 0;
		FaxPhaseE( 4 );				/**	通信終了（ＤＣＮなし）	*/
		ReceiveError( 0x11 );		/**	Ｒ．１．１	*/
	}
}

/**************************************************************************************************/
/**
	@brief		受信原稿のステイタスを確定させる
	
	@li			
	@param		
	@return		なし
	@note		擬似ベル鳴動中にプリント排出させるため
	@date		2005/09/16 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiFixRxDocStatus(void)
{
	UWORD memory_rx_num;
	
	/* add 1997/03/07  By T.Yamaguchi */
	for (memory_rx_num = 0; memory_rx_num < SYS_MEMORY_RX_MAX; memory_rx_num++) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
		if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
		 || (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)) {
#else
		if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
		 || (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)
		 || (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE_PRINT)) {
#endif

#if (PRO_LINENUMBER == TWICE_LINE)
			/* ＱＡＴ不具合
			** 拡張回線で受信ができない不具合修正
			** 拡張回線の処理が抜けていた（ "& 0x7f")
			** by O.Kimoto 1998/04/13
			*/
			if ((SYB_MemoryRxPrint[memory_rx_num].StackNumber & 0x7f) == (UBYTE)0) {
				break;
			}
#else
			if (SYB_MemoryRxPrint[memory_rx_num].StackNumber == (UBYTE)0) {
				break;
			}
#endif
			}
	}
	/* 受信原稿ポーリング取り出し修正分にて追加します by T.Soneoka 1997/02/21
	** ポーリング取り出しモード（機種固有Ｓｗ）で代行受信満杯でアクセスされた場合、プリントライト位置を更新しない
	*/
	if (memory_rx_num < SYS_MEMORY_RX_MAX) {
		MemoryRxPrintPoint = &SYB_MemoryRxPrint[memory_rx_num];
		if (MemoryRxPrintPoint->StorePage > 0) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_PRINT; /* By H.Y 1994/11/17 */
#else
			if (MemoryRxPrintPoint->Status == SYS_MEMORY_RX_STORE_PRINT) {
				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_FAST_PRINT;
			}
			else {
				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_PRINT;
				if (CHK_UNI_RxDocReversePrint()) {
					MemoryRxPrintPoint->PrintPage = MemoryRxPrintPoint->StorePage;
					MemoryRxPrintPoint->RotatePage = MemoryRxPrintPoint->StorePage;
				}
			}
#endif
			/* 1997/02/10 Y.Murata
			 * プリンタが今、受信している原稿をプリントしている場合のみイベントを発行します
			*/
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
				if ((SYS_DocumentPrintItem == SYS_MEM_RX_FILE)
				&& (SYS_DocumentPrintNo == memory_rx_num)) {
					CMN_DisableInterrupt();	/**	割り込み禁止	*/
					PRN_1PageReceived = 1;
					det_evt(EVT_PRN_RESTART);
					CMN_EnableInterrupt();	/**	割り込み許可	*/
				}
			}
		}
		else  {
			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
			MemoryRxPrintPoint->StorePage = 0;
			MemoryRxPrintPoint->RotatePage = 1;
			MemoryRxPrintPoint->PrintPage = 1;
			MemoryRxPrintPoint->ErasePage = 1;
			MemoryRxPrintPoint->Protect	  = SYS_PROTECT_OFF; /**受信原稿プリントプロテクト初期化 */
			/* 3Line add 1997/03/07  By T.Yamaguchi */
			MemoryRxPrintPoint->StackNumber = 0;
			MemoryRxPrintPoint->ReceiveTime = 0;
			MemoryRxPrintPoint->JournalPoint = 0;
		}
	}
}

#endif /* KEISATSU */

