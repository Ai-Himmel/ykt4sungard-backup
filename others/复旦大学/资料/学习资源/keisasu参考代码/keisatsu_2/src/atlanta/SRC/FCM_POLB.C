/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_POLB.C												 */
/*	モジュール	 :															 */
/*				 : FaxPollingRxPhaseB1()									 */
/*				 : FaxPollDISSemiCompatibleCheck()							 */
/*				 : FaxPollNSFSemiCompatibleCheck()							 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : ポーリング受信フェーズＢ１								 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------------------------------------------------------
	File Name	:  FCM_POLB.C
	Coded By	:  M.HARADA
	Module Name :  FaxPollingRxPhaseB1()
	Note		:  ポーリング受信フェーズＢ１
-------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\mon_pro.h"	/*	Jun.09.1994 竹内	*/

#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\apl_msg.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"	/* By S.Kawasaki 1996/03/07 *//*	Jun.09.1994 竹内	*/

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
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
#include	"\src\atlanta\define\cmn_pro.h"
#endif /* (PRO_TX_SPEED == V34) */


/*************************************************************************
	module		:[FaxPollingRxPhaseB1()]
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
void   FaxPollingRxPhaseB1(void)
{
	UBYTE	command;
	UWORD	T1_timer;
	UBYTE	pollingmode0_flag;
	UBYTE	pollingmode1_flag;
	UBYTE	dcs_received_flag;
	UBYTE	mode_change_tx_cng_flag;	/* add By T.Yamaguchi 96/05/22 */
	UBYTE	dis_count;

#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
	UBYTE	detect_turn_off_flag = 0; /* Added by H.Kubo 1997/08/06 */
	UBYTE	ret_value;
#endif /* (PRO_TX_SPEED == V34) */


	DIS_ReceivedFlag		= 0;			/*????*/
	FaxComRxPerformingFlag = 0;
	pollingmode0_flag	   = 0;
	pollingmode1_flag	   = 0;
	T1_timer			   = SYS_GeneralTimer;
	mode_change_tx_cng_flag = 0;				/* add By T.Yamaguchi 96/05/22 */
	dis_count = 0;

	while (( FaxComPerformingFlag == 1 )
	&& ((UWORD)( SYS_GeneralTimer - T1_timer ) < (35000 / 10) )
	&& ( pollingmode0_flag == 0 )
	&& ( SYS_FaxComStopSwitch() == 0 )
	&& ( DIS_ReceivedFlag == 0	)){		/*????*/				/** 通信中 & タイムアップなし &	 */
	  /*---------------------*/
	  /*	   CNG Tx		 */
	  /*---------------------*/
#if (0)
** /* Ｖ．８ハンドシェーク中のノイズ対策 by O.Kimoto 1999/04/13 */
** 		if (FSK_FirstReceivedFlag == 0) { /* 96/05/17 By T.Yamaguchi FSK信号を一回でも受け取るとＣＮＧを出さない様にした */
** 			FaxTransmitCNG();
** 		}
#else
 #if (PRO_TX_SPEED == V34 )
		if (( AD_Result == AD_OK_DSE) && ( !FCM_CheckToneDetectedInV8Mode() )) {
			if (FSK_FirstReceivedFlag == 0) { /* 96/05/17 By T.Yamaguchi FSK信号を一回でも受け取るとＣＮＧを出さない様にした */
				FaxTransmitCNG();
			}
		}
 #else
		if (FSK_FirstReceivedFlag == 0) { /* 96/05/17 By T.Yamaguchi FSK信号を一回でも受け取るとＣＮＧを出さない様にした */
			FaxTransmitCNG();
		}
 #endif /* ((PRO_TX_SPEED == V34 ) && (PRO_MODEM == R288F)) */
#endif

#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
		if ( (!CHK_UNI_SDCSModeChange())
		  && (((CHK_UNI_SpeedModeChange()) && (MakerCodeRxFlag == YES))
		   || (PartnerSpeedModeChangeAbility == YES)) ) {
			/** 相手がＦＡＸであると確定した ＭＣＦ受信後１回目 村田機 */
			if ((mode_change_tx_cng_flag == 0) && (FSK_FirstReceivedFlag == 1)) {
				FaxTransmitCNG();							/** CNG送出 */
			}
			mode_change_tx_cng_flag = 1;
		}
#endif
	  /*--------------------*/
	  /*  (NSF)(CSI)DIS Rx	*/
	  /*--------------------*/
#if (PRO_MODEM == MN195006)					/* tanaka unko */
		if( 1 ){							/** コマンド受信あり */
#else
		if( MDM_ReceiveCommand((UWORD)TIME_OVER_3SEC) == FSK_RECEIVE ){							/** コマンド受信あり */
#endif
			command = CheckHDLC_Command();						/** HDLCコマンドチェック */
			pollingmode0_flag = 1;
			if( command == DIS_F){								/** DIS受信 */

				if (dis_count == 0) {		/* 6line add By T.Yamaguchi 96/09/03 */
					if(FCM_PtnrChkOverride1stDIS()) {
						FSK_FirstReceivedFlag = 1;
						pollingmode0_flag = 0;
						dis_count = 1;
						continue;
					}
				}
#if (PRO_F_CODE == ENABLE)	/* Fコードは、ﾎﾟｰﾘﾝｸﾞﾋﾞｯﾄは見ずにSEPﾋﾞｯﾄをﾁｪｯｸする */
				if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) &&
					(CommandFileOptionItem == SYS_SELECT_POLLING_RX)) {
					if (SetPollF_CODE() == NG) {;	/* Fｺｰﾄﾞﾋﾞｯﾄﾁｪｯｸ */
						FaxPhaseE(3);									/** フェーズＥ */
						ReceiveError(0x12);
					}
				}
#endif
				if (FaxPollDISSemiCompatibleCheck() == 0) {		/** DIS 相手機ポーリング送信能力判定 */
					if (((SYS_FaxComType == SYS_COMMAND_EXECUTE)
					  && ((CommandFileOptionItem != SYS_DB_POLLING_RX)
					  && (CommandFileOptionItem != SYS_SELECT_POLLING_RX)))
					 ||(SYS_FaxComType == SYS_FIP_POLL)) {				/** (自動送信 & 検索ポーリング受信でない) or FIPポーリング */
						if (FaxCompatibleErrorCode == NO_ERROR) {		/** for DEBUG コンパチエラー内容チェック */
							FaxCompatibleErrorCode = RX_NO_POLLING_DOC_ERROR;	/** for DEBUG コンパチエラー内容セット */
						}
						FaxPhaseE(3);									/** フェーズＥ */
						ReceiveError(0x12);
					}
				}
				if(( CommandFileOptionItem == SYS_DB_POLLING_RX )
				&& (SYS_FaxComType == SYS_COMMAND_EXECUTE)) {					/** 検索ポーリング受信 & 自動送信 */
					/*-----------「NSFを検出できない場合もう一度DISを受信する」for 検索ﾎﾟｰﾘﾝｸﾞ時 96/09/02 By T.Yamaguchi */
					if (dis_count == 0) {
						if( FaxDIS_SemiCompatibleCheck() == 0 ){			/** 受信フレームにNSFなし */
							FSK_FirstReceivedFlag = 1;
							pollingmode0_flag = 0;
							dis_count = 1;
							continue;				/* detect dis once more */
						}
					}
					if( FaxPollNSFSemiCompatibleCheck() == 0 ){			/** NSF 相手機特殊ポーリング送信能力なし */
						if (MakerCodeRxFlag == 1) {						/** MMLメーカーコード受信 */
							FaxCompatibleErrorCode = NO_DB_POLLING_FUNCTION_ERROR;		/** エラーコードセット */
						}
						else {
							FaxCompatibleErrorCode = DB_POLLING_NOT_MURATA_ERROR;
						}
						FaxPhaseE(3);								/** フェーズＥ */
						ReceiveError(0x12);
					}
				}
				DIS_ReceivedFlag = 1;								/** DIS受信フラグ */
				FSK_FirstReceivedFlag = 1;							/** 相手がＦＡＸであると確定した */
#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
				/*------------------------*/
				/* 相手機Ｖ８能力チェック */
				/*------------------------*/
				if (FCM_CheckPartnerV8Capable()) {/** Ｖ８能力有り */
					/*PartnerV8Capable = 1; del 1996/08/03 Y.M */
					if ((SYS_V34ProcedureExecuting() == 0) && (FaxComPerformingFlag == 1)) {
#if (0) /* Changed by H.Kubo 1997/10/07 */
** 						if ((CMN_GetDataSignalingRate() & 0x0001) == 0x0001) {	/** Ｖ３４リソース有り */
** 							V8ProcedureRequestFlag = 1;
** 						}
#else /* 0 */
						if ((CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT) == DATA_SIGNALING_RATE_V34_BIT) {	/** Ｖ３４リソース有り */
							V8ProcedureRequestFlag = TRUE;
						}
#endif /* 0 */
					}
				}
#endif /* (PRO_TX_SPEED == V34) */
			}
			else{
				FaxPhaseE(1);															/** フェーズＥ */
				ReceiveError(0x11);
			}
		}
	}

	dcs_received_flag = 0;

	while( ( FaxComPerformingFlag == 1 )
	&& ( (UWORD)( SYS_GeneralTimer - T1_timer ) < (35000 / 10) )
	&& ( pollingmode0_flag == 1 )
	&& ( pollingmode1_flag == 0 )
	&& ( SYS_FaxComStopSwitch() == 0 )
#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
	&& ( V8ProcedureRequestFlag  == 0 )
#endif /* (PRO_TX_SPEED == V34) */
	&& ( dcs_received_flag == 0 )){									/** 通信中 & T1タイムオーバー
															& ポーリング受信フラグあり & ポーリング送信フラグ
															& StopSwitchなし & DCS受信なし */
#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
		if (detect_turn_off_flag == 0) {	/** ｔｕｒｎ－ｏｆｆ未検出 */
#endif /* (PRO_TX_SPEED == V34) */

		/*--------------------*/
		/*	(NSC)(CIG)DTC Tx  */
		/*--------------------*/
		MakeDTC_FIF();											/** DTCのFIF作成 */
		MakeNSC_FIF();											/** NSCのFIF作成 */
#if (PRO_F_CODE == ENABLE)
		/* SEPを２回出すことは、現在ないがパスは残しておく */
		if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) &&
			(CommandFileOptionItem == SYS_SELECT_POLLING_RX)) {
			if(( SYS_RxTotalPage == 0 ) || (!CHK_UNI_SUB_Frame_Off())) {	/* UNI_SW_B6-4 */
				MakePOL_PWD_FIF();
				MakeSEP_FIF();
			}
		}
#endif

#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
		FCM_TransmitCommand();			/** コマンド送信 */
		if ((SYS_V34ProcedureExecuting() == 1)  && (SYS_RxReceiptRequestFlag == 1)){	/** Ｖ３４モード実行中 */
			/*------------------------------*/
			/* V34ﾀｰﾝｱﾗｳﾝﾄﾞﾎﾟｰﾘﾝｸﾞ turn-off */
			/*------------------------------*/
			ret_value = FCM_ControlChanelDetectTurnOff();
			if (ret_value == TURN_OFF_RECEIVE) {	/** ｔｕｒｎ－ｏｆｆ検出 */
				detect_turn_off_flag = 1;
				/*---------------------------------*/
				/** 起呼スタートアップ処理(RX FAX) */
				/*---------------------------------*/
				StartUpData.Item = V34_TURNAROUND;
				StartUpData.Option.TransmitCI = 0;
				StartUpData.Direction = RX_COM_MODE;
				StartUpData.Allowed = RX_COM_MODE;
				ret_value = FCM_CallStartUpProcedure();	/** スタートアップ起呼処理 */
				V8ProcedureRequestFlag = 0;
				switch (ret_value) {
					case V34_PROCEDURE:
						break;
					case T30_PROCEDURE:
					default:
						FaxComPerformingFlag = 0;
						break;
				}
			}
			else if (ret_value == FSK_RECEIVE) {
				ReceiveError(0x12);
#if defined(DEU) || defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
				FaxPhaseE(3);		/** フェーズＥ */
#endif
			}
			else {
				ReceiveError(0x12);
#if defined(DEU) || defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
				FaxPhaseE(3);		/** フェーズＥ */
#endif
			}
		}
#else /* (PRO_TX_SPEED == V34) */
		MDM_TransmitCommand();											/** コマンド送信 */
#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
		} /* end of if (detect_turn_off_flag == 0) */
#endif /* (PRO_TX_SPEED == V34) */

		/*------------------------------*/
		/*	(NSS)(TSI)DCS,FX NSS Rx		*/
		/*------------------------------*/

#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
		if ( FCM_ReceiveResponse((UBYTE)0, NON_CCRETRAIN) == FSK_RECEIVE){		/** 応答受信あり */
#else /* (PRO_TX_SPEED == V34) */
		if ( MDM_ReceiveResponse(FCM_ReceiveResponseTime) == FSK_RECEIVE){					/** 応答受信あり */
#endif /* (PRO_TX_SPEED == V34) */

			pollingmode1_flag = 1;									/** ポーリング受信フラグセット */
			if((CheckHDLC_Command() == DCS_F) || (CheckHDLC_Command() == NSS_F)){						/** DCS受信 */
				/* FX NSS RX の処理追加 21.Jly'94 Y.Suzuki */
				dcs_received_flag = 1;								/** DCS受信フラグセット */
				FaxComRxPerformingFlag = 1;							/** 受信中フラグセット */
				MsgFromFaxComToMain.Item	= FROM_FAXCOM;			/*	add by harada 1994.6.9 */
				MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
				SYS_FaxCommStage = FCM_RECEIVE;
				snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
				rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */
				/* Xﾋﾞｯﾄが立たないので消去する  1997/06/05  By T.Yamaguchi */
				/* DIS_ReceivedFlag = 0; 94/12/15 Y.Suzuki */
			}
			else{
				ReceiveError(0x12);
#if defined(DEU) || defined(EUR)		/* add by M.HARADA 95.09.20 for PTT test */
										/* 欧州仕様追加 by M.H 1999/09/16 */
				FaxPhaseE(3);							/** フェーズＥ */
#endif
			}
		}
	}

#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
	if (V8ProcedureRequestFlag == 0) {	/** Ｖ８移行要求なし */
#endif /* (PRO_TX_SPEED == V34) */

	if((( pollingmode0_flag == 0 ) || ( pollingmode1_flag == 0 ))
	&& ( FaxComPerformingFlag == 1 )
	&& ( SYS_FaxComStopSwitch() == 0 )){				/** （ポーリング受信フラグなし or ポーリング送信フラグなし）
										& 通信中 & StopSwitchなし */
		/*-----------------------------*/
		/*	PhaseE	FTZ18TR53 Fig13-1  */
		/*-----------------------------*/
		FaxPhaseE(1);							/** フェーズＥ */
		/*----------------*/
		/*	T1 Time Over  */
		/*----------------*/
		ReceiveError(0x11);
	}

	if( SYS_FaxComStopSwitch() == 1 ){					/** StpoSwitchあり */
		/*---------------*/
		/*	STOP DCN Tx	 */
		/*---------------*/
		FaxPhaseE(5);													/** フェーズＥ */
		ReceiveError(0x14);
	}
#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
	} /* end of if (V8ProcedureRequestFlag == 0) */
#endif /* (PRO_TX_SPEED == V34) */
}


/***********************************************************
*				BY:	 M.HARADA
*	  ROUTINE NAME:	 FaxPollDISSemiCompatibleCheck()
*	   DESCRIPTION:	 DIS 相手機ポーリング送信能力判定
*		   RETURNS:	 ポーリング送信能力	  有(1)無(0)
*		 CALLED BY:	 FaxPollingRxPhaseB1()
************************************************************/
UBYTE	FaxPollDISSemiCompatibleCheck(void)
{
	if (RxStdFrame_ECMAbilityCheck()) {		/* 受信フレームＥＣＭ能力解析 */
		if (RxECM_Ability == ECM_ON) {
			RxECM_Mode = ECM_ON;
		}
	}
#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
	else {
		if (SYS_V34ProcedureExecuting()) {	/* V34なら強制的にECMｵﾝ 1996/05/30 Y.M */
			RxECM_Mode = ECM_ON;
		}
	}
#endif /* (PRO_TX_SPEED == V34) */

/* #if (PRO_MULTI_LINE == ENABLE) */
	/*--------------------*/
	/* Ｖ８ビットチェック */
	/*--------------------*/	/* 1997/01/13 Y.M */
	if (MDM_ModemBuffer[FCF_Point][3] & 0x20) {	/* Recommendation V8 capabilities ON ? */
		PartnerV8Capable = 1;
	}
	else {
		PartnerV8Capable = 0;
	}
/* #endif */

	return( ( UBYTE )( MDM_ModemBuffer[FCF_Point][4] & 0x01 ) ); /*DIS FIF2ndByte*/
}

/*@H********************************************************
*				BY:	 M.HARADA
*	   ROUTINE NAME:	 FaxPollNSFSemiCompatibleCheck()
*	   DESCRIPTION:	 NSF 相手機特殊ポーリング送信能力判定
*		   RETURNS:	 特殊ポーリング送信能力	  有(4)無(0)
*		 CALLED BY:	 FaxPollingRxPhaseB1()
************************************************************/
UBYTE		  FaxPollNSFSemiCompatibleCheck(void)
{
	UWORD	   point;
	UWORD	   counter;


	point = 0;

	for( counter = 0; counter <= FCF_Point; counter++){
		if(NSF_F == (MDM_ModemBuffer[point][2] & 0xfe)){
			break;
		}
		point++;
	}

	/************************************/
	/** FIF3rd 通工会指定MMLｺｰﾄﾞ(0x45) **/
	/************************************/
	if(0x45 == (MDM_ModemBuffer[point][5] & 0x45)){
		MakerCodeRxFlag = 1;
		/*************************************/
		/** FIF4th 拡張ﾌｨｰﾙﾄﾞ  有(80H)無(0) **/
		/*************************************/
		if(0x80 == (MDM_ModemBuffer[point][6] & 0x80)){
			/************************************/
			/** FIF4th TTIﾌｨｰﾙﾄﾞ  有(01H)無(0) **/
			/************************************/
			if(0x01 == (MDM_ModemBuffer[point][6] & 0x01)){
				/******************************/
				/** 検索ﾎﾟｰﾘﾝｸﾞ 有(04H)無(0) **/
				/******************************/
				return( ( UBYTE )( MDM_ModemBuffer[point][23] & 0x04 ));
			}
			else{
				return( ( UBYTE )( MDM_ModemBuffer[point][7] & 0x04 ));
			}
		}
		else{
			return(0);
		}
	}
	else{
		return(0);
	}
}

