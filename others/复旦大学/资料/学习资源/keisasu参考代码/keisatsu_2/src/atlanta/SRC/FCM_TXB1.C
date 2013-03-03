/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_TXB1.C												 */
/*	モジュール	 :															 */
/*				 : FaxTxPhaseB1()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :															 */
/*	概	要		 : 送信側フェーズＢ１										 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------
	File Name	:  FCM_TXB1.C
	Coded By	:  M.HARADA
	Module Name :  FaxTxPhaseB1()
				   FaxDIS_SemiCompatibleCheck()
				   FaxTxBeforeVoiceMode(void)		for FRA	'95.02.09

	Note		:  送信側フェーズＢ１
-----------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"

#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"

#include	"\src\memsw\define\mem_sw_b.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\sysscan.h"

#include	"\src\atlanta\sh7043\define\sh_port.h"

#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"

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

extern CONST unsigned char far CRTN_Debug;			/* Control chanel retrain test 1996/4/25 Y.M */
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\ext_v\bkupram.h"	/* 96/08/08 add By T.Yamaguchi */
#include	"\src\atlanta\define\mntsw_b.h"	/* 96/08/08 add By T.Yamaguchi */
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
 #endif
#endif

/*************************************************************************
	module		:[送信フェーズＢ１]
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
	date		:[1993/12/22]
	author		:[原田]
	変更履歴	:
*************************************************************************/
void	FaxTxPhaseB1( void )
{
	UWORD		  T1_timer;
	UBYTE		  txmode_flag;
	UBYTE		  feederror_flag;
	UBYTE		  command;
	UBYTE		  dis_counter;
	UBYTE		  receive_command_counter;	/* MDM_ReceiveCommand()を何回通ったかカウントする 96/08/12 By T.Yamaguchi for Debag */

#if 0	/* defined(FRA) */
	UBYTE		voice_result;
#endif
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
	UBYTE	  mode_change_tx_cng_flag;	/* add By T.Yamaguchi 96/05/22 */
	mode_change_tx_cng_flag = 0;				/* add By T.Yamaguchi 96/05/22 */
#endif
	/**************/
	/** Phase B1 **/
	/**************/
	FaxComPhaseStatus = FAX_TX_PH_B1;

	txmode_flag		  = 0;
	feederror_flag	  = 0;
	dis_counter		  = 0;
	T1_timer		  = SYS_GeneralTimer;

	/* for Debag 96/08/12 By T.Yamaguchi */
	/* receive_command_counter = 0; */

	if(( TxSpeedHandshakeFlag == 0 )
#if defined(FRA)|| defined(DEU)	|| defined(EUR)					/* 95/03/17 by M.HARADA */
												/* 欧州仕様追加 by M.H 1999/09/16 */
	/* 手動送信時、スタートキーを押下後1.5±1ｓ以内にＣＮＧを出す */
	&& (( AD_Result != AD_OK_CED) && ( AD_Result != AD_OK_DIS))
#if (PRO_TX_SPEED == V34 ) /* Added by H.Kubo 1997/08/07 */
#if (PRO_MODEM == R288F)
	&& ( AD_Result != AD_OK_ANSWER_TONE)
#endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34 ) */
#else
	&& ( AD_Result == AD_OK_DSE)
#if ((PRO_TX_SPEED == V34 ) && (PRO_MODEM == R288F))
#if 0 /* Changed by H.Kubo 1998/05/25 */
@@	&& ( FCM_ToneAfterDetectDCE != AD_OK_DIS)
@@	&& ( FCM_ToneAfterDetectDCE != AD_OK_CED)
@@	&& ( FCM_ToneAfterDetectDCE != AD_OK_ANSWER_TONE)
#else
	&& ( !FCM_CheckToneDetectedInV8Mode() )
#endif
#endif /* ((PRO_TX_SPEED == V34 ) && (PRO_MODEM == R288F)) */
#endif
	&& ( SYS_FaxComStopSwitch() == 0 )){			/** 短縮ハンドシェイクなし & 極反検出(着信検出)
															& StopSwitchなし */
		if (FSK_FirstReceivedFlag == 0) {			/* モード変更の時にＣＮＧがでる可能性があるので条件追加	96/08/12 By T.Yamaguchi */
			/*-----------*/
			/*	CNG Tx	 */
			/*-----------*/
#if defined(POPLAR_H) && defined(JP1)/*関電専用線仕様By Y.Suzuki 2003/06/19 */
			if (CHK_TransmitBy1300Hz()) {
				FaxTransmit1300Hz();
			}
			else {
				FaxTransmitCNG();							/** CNG送出 */
			}
#else
			FaxTransmitCNG();							/** CNG送出 */
#endif
		}
	}


	/* ＥＯＭ送出後、ＭＣＦを受け取って、再度ＰｈａｓｅＢ１に戻ってきた時に、
	** 以下の処理でMDM_ReceiveCommand()が呼ばれるが、オレンジモデムの反応（ＲＬＳＤ）が
	** 遅いため、ＭＣＦの終結フラグを次のＦＳＫの先頭のフラグと誤検出してしまい、
	** 結果的にReceiveCommandから帰ってくるのが約6.5sもかかってしまう。（この約6秒が、
	** モードチェンジ時のT2タイマーとほぼ同等なため、本来のNSF/CSI/DISとCNGがぶつかってしまい
	** NSFがとれないとい不具合が出たため、本来はこの約6秒になるのを修正しなければならないのですが、
	** 暫定対策として、RLSDがON->OFFになる公証値50msの倍の時間だけウエイトします。
	** By O.Kimoto 1997/05/14
	*/
#if (PRO_MODEM == ORANGE3)
	if (TxModeChangedFlag == 1) {
		wai_tsk(100/10);
	}
#endif /* (PRO_MODEM == ORANGE3) */

	TxSpeedHandshakeFlag = 0;			/** 短縮ハンドシェイク送信フラグクリア クリアする場所を検討すること By T.Y */

	while(( FaxComPerformingFlag == 1 )
	&& (( UWORD )( SYS_GeneralTimer - T1_timer ) < ( 35000 / 10 ))
	&& ( txmode_flag == 0 )
	&& ( SYS_FaxComStopSwitch() == 0 )){								/** 通信中 & T1タイムオーバーなし
																& DCN送出なし設定 & StopSwitchなし */
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
		if (ModeChangeMethodCheck() == CNG_MODE) {
			/** 相手がＦＡＸであると確定した ＭＣＦ受信後１回目 村田機 */
			if ((mode_change_tx_cng_flag == 0) && (FSK_FirstReceivedFlag == 1)) {
				FaxTransmitCNG();							/** CNG送出 */
			}
			mode_change_tx_cng_flag = 1;
		}
#endif

#if (PRO_FBS == ENABLE)
		/* POPLAR_B 条件追加 T.Nose 1997/04/08
		** ADF送信のときだけ、スキャナ送信の原稿エラーを見る
		*/
		if (SYS_ScannerExecMode == SCN_ADF) {
			if( ((CMN_CheckDS1Status() == FALSE) || (CMN_CheckScannerCoverClose() == FALSE))			/* 原稿がないまたは、ｽｷｬﾅｶﾊﾞｰがｵｰﾌﾟﾝ */
			&& (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT)) {	/* スキャナ送信 */
				/*--------------*/
				/*	Feed Error	*/
				/*--------------*/
				feederror_flag	= 1;
				break;
			}
		}
#else
		if( ((CMN_CheckDS1Status() == FALSE) || (CMN_CheckScannerCoverClose() == FALSE))			/* 原稿がないまたは、ｽｷｬﾅｶﾊﾞｰがｵｰﾌﾟﾝ */
		&& (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT)) {	/* スキャナ送信 */
/* 移植 by SMuratec L.Z.W 2003/07/24 */
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
  #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
if (ROM_SW_SpecialDoctorReport) {
				if ((CommandFileTitleMessage & 0xf0) == 0x00) {
		  			/*--------------*/
					/*	Feed Error	*/
					/*--------------*/
					feederror_flag	= 1;
					break;
				}
}
else {
	  			/*--------------*/
				/*	Feed Error	*/
				/*--------------*/
				feederror_flag	= 1;
				break;
}
  #else
  			/*--------------*/
			/*	Feed Error	*/
			/*--------------*/
			feederror_flag	= 1;
			break;
  #endif
 #else
  			/*--------------*/
			/*	Feed Error	*/
			/*--------------*/
			feederror_flag	= 1;
			break;
 #endif
		}
#endif

		/*-----------*/
		/*	FSK	 Rx	 */
		/*-----------*/
		/* receive_command_counter++; */ /* for debag 96/08/12 By T.Yamaguchi */

#if (PRO_TX_SPEED == V34 ) /* Added by H.Kubo 1997/08/07 */
		if( FCM_ReceiveCommand(TIME_OVER_3SEC, NON_CCRETRAIN) == FSK_RECEIVE ){	/** 命令受信 */
#else /* (PRO_TX_SPEED == V34 ) */
		if( MDM_ReceiveCommand((UWORD)TIME_OVER_3SEC) == FSK_RECEIVE ){						/** 命令受信 */
#endif /* (PRO_TX_SPEED == V34 ) */
			command = CheckHDLC_Command();				/** HDLCコマンド受信 */

			switch( command ){
			/*-------------------*/
			/*	DIS/DTC/SCFR Rx	 */
			/*-------------------*/
			case  DIS_F :								/** DIS受信 */
			case  DTC_F :								/** DTC受信 */
			case  CFR_F :								/** CFR受信 */
				FSK_FirstReceivedFlag = 1;	/** 相手がＦＡＸであると確定した */
				FaxComUntilRecDISLineOFF();	/** ＤＩＳ受信で回線モニタをＯＦＦする */

				if((!(FCM_PtnrChkOverride1stDIS()))
				|| ( 1 == dis_counter )
				|| ( CFR_F == command )
				|| ( DTC_F == command )){	/** DISを１かい無視なし or DIS受信２回目
											or CFR受信 or DTC受信 */
#if 0	/* defined(FRA) */
//					/**********************/
//					/**	 通信前会話予約	 **/
//					/**********************/
//					voice_result = 0;
//					if ((1 == SYS_VoiceSwitch) && (0 == VoiceFlag)) {
//						voice_result = FaxTxBeforeVoiceMode();
//						VoiceFlag = 1;
//						if(voice_result == B1_OH_DETECT){
//							txmode_flag		 = 1;
//						}
//					}
//					if((B1_DIS_DETECT == voice_result)
//						|| ((voice_result == 0) && (command == DIS_F)) ){
//
#endif
					if(( 0 == dis_counter )					/* 1回目のDIS */
						&& ( CFR_F != command )
						&& ( DTC_F != command )){	/** DISを０回受信 & CFR受信せず
												& DTC受信せず */
		/*-----------「NSFを検出できない場合もう一度DISを受信する」.--- for 応用通信用に復活 96/08/08 By T.Yamaguchi */
 						if( FaxDIS_SemiCompatibleCheck() == 0 ){			/** 受信フレームにNSFなし */
							dis_counter = 1;			/** DIS１回受信フラグセット */
							/* ＣＥＤ検出でﾀﾞｲﾔﾗｰを抜けてきてＮＳＦ検出できないとき有り */
#if 0
//							if (SYB_MaintenanceSwitch[MNT_SW_B8] & 0x80) {
//								SYB_MaintenanceSwitch[MNT_SW_B6]++;
//								SYB_MaintenanceSwitch[MNT_SW_B7] |= ((0x7f) & AD_Result);
//								SYB_MaintenanceSwitch[MNT_SW_B8] |= receive_command_counter;	/* ２になるはず */
//								if (SYB_MaintenanceSwitch[MNT_SW_B7] & 0x80) {
//									wai_tsk(0xffff);
//								}
//							}
#endif
							break;	/* detect dis once more */
						}
			/*--------------------------------------------------------------------------------------*/
					}

					DIS_ReceivedFlag = 1;	/*????*/						/** DIS受信フラグセット */
					txmode_flag		= 1;		/** DCN送出なし設定フラグセット */
					FinalTxMode		= G3MODE;		/** 確定送信モード */
#if 0	/* defined(FRA) */
//					}
#endif
				}
				else {
					dis_counter = 1;				/** DIS１回受信フラグセット */

#if (PRO_TX_SPEED == V34) /* this #if is added by H.Kubo 1997/10/24 */
#if (PRO_MODEM == R288F) /* Ported from Clover by H.Kubo 1997/08/07 */
					if (CRTN_Debug & 0x01) {	/* test 1996/04/25 */
						MDM_SetControlChannelRetrain(); /* V.34 コントロールチャンネル・リトレイン実行 PANAできてない*/
					}
#endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */
				}
				break;
			/*------------*/
			/*	 DCN Rx	  */
			/*------------*/
			case DCN_F	:							/** DCN受信 */
				dis_counter = 1;
				txmode_flag = 1;							/** DCN送出なし設定フラグセット */
				TransmitError( 0x11,1 );
				break;
			default		:									/** デフォルト */
				FaxComPerformingFlag = 0;			/** 通信中でないフラグセット */
				break;
			}
		}

		if (dis_counter != 0) {
			/* CNGは送出しない	add by M.H 1994/11/20 */
		}
		else {
			if(( txmode_flag == 0 )
			&& ( FaxComPerformingFlag == 1 )){					/** DCN送出なし設定 & 通信中 */
				/*-----------*/
				/*	CNG Tx	 */
				/*-----------*/
 #if defined(FRA)										/* CED受信後CNGを送出しない 95.05/16  by M.HARADA */
  #if (PRO_TX_SPEED == V34 ) /* Added by H.Kubo 1997/08/07 */
	#if (PRO_MODEM == R288F)
				if ((AD_Result != AD_OK_CED)
				&& (AD_Result != AD_OK_ANSWER_TONE)
				) {
				 /* 極反検出後 ANS, ANSam, CED, V21フラグ検出せず by H.Kubo 1997/11/29  */
	#endif /* (PRO_MODEM == R288F) */
  #else /* (PRO_TX_SPEED == V34 ) */
				if(AD_Result != AD_OK_CED){
  #endif /* (PRO_TX_SPEED == V34 ) */
 #endif
					if (FSK_FirstReceivedFlag == 0) { /* 96/05/17 By T.Yamaguchi FSK信号を一回でも受け取るとＣＮＧを出さない様にした */
 #if defined(POPLAR_H) && defined(JP1)/*関電専用線仕様By Y.Suzuki 2003/06/19 */
						if (CHK_TransmitBy1300Hz()) {
							FaxTransmit1300Hz();
						}
						else {
							FaxTransmitCNG();							/** CNG送出 */
						}
 #else
						FaxTransmitCNG();
 #endif
#if (0)		/*2003/02/03 M.Iida このByteのBIt7-5が、ほかの機能とかぶって使用されているためカウント機能を削除します*/
//						/**
//							連続交信でＮＳＳがとれないときがあるので、ﾒﾝﾃﾅﾝｽｽｲｯﾁでNSFがとれないﾀｲﾐﾝｸﾞがあるのを調べる
//							結果 ﾀﾞｲﾔﾗｰを抜けてきて、１回目のMDM_ReceiveCommandでとれない場合があることが判明した
//							 CNGを出しているときに、ＮＳＦがくるととれないときあり
//						 96/08/12 for debag add 1line By T.Yamaguchi
//						*/
//						SYB_MaintenanceSwitch[MNT_SW_B5]++;
#endif	/* #if (0)	2003/02/03 M.Iida このByteのBIt7-5が、ほかの機能とかぶって使用されているためカウント機能を削除します*/
					}
 #if defined(FRA)										/* 95.05/16	 by M.HARADA */
				}
 #endif
			}
		}
	}

	if(( txmode_flag == 0 )
	&& ( SYS_FaxComStopSwitch() == 0 )){						/** DCN送出なし設定 & StopSwitchなし */
		/*-----------------------------*/
		/*	PhaseE	FTZ18TR53 Fig13-1  */
		/*-----------------------------*/
		FaxPhaseE(1);
		if( feederror_flag == 1 ){						/** フィードエラーあり */
			/*--------------*/
			/*	Feed Error	*/
			/*--------------*/
            TransmitError( 0x31,1 );	/** エラーセット */	/* 原稿エラー(T.3.1)  1997/05/09 s.takeuchi */
			/* TransmitError( 0x12,1 );	/@@ エラーセット */
		}
		else{
			/*----------------*/
			/*	T1 Time Over  */
			/*----------------*/
			TransmitError( 0x11,1 );						/** エラーセット */
		}
	}

	if( SYS_FaxComStopSwitch() == 1 ){							/** StopSwitchあり */
		/*---------------*/
		/*	STOP DCN Tx	 */
		/*---------------*/
		FaxPhaseE(5);															/** フェーズＥ */
		TransmitError( 0x14,1 );											/** エラーセット */
	}
}

/*************************************************************************
	module		:[NSFの有無チェック]
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
	date		:[1996/08/08]
	author		:[t.yamaguchi]
	変更履歴	:96/08/08	送信種別に関係なくNSFが取れない場合に０を返す様に変更
				:96/09/02	応用通信でＮＳＦが必ず必要時のみ、ＮＳＦが取れない場合に０を返す様に変更
*************************************************************************/
UBYTE			FaxDIS_SemiCompatibleCheck(void)
{
	UWORD	search_point;
	UWORD	counter;

	if (OriginalCommunicationNeedNSF()) {		/* 村田独自の応用通信で、ＮＳＦが必要である */
		search_point = FCF_Point;

		if( search_point != 0){
			for( counter = 0; counter <= FCF_Point; counter++){
				if( NSF_F == MDM_ModemBuffer[search_point][2] ){
					return(1);
				}
				search_point--;
			}
		}
		return(0);
	}
	return(1);
}


/*************************************************************************
	module		:[ＮＳＦが必要かどうかチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[応用通信で、ＮＳＦがとれないときエラーになる]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/08/08]
	author		:[山口　哲治]
*************************************************************************/
UBYTE		OriginalCommunicationNeedNSF(void)
{
	switch (SYS_FaxComType) {		/**	交信種別	*/
	case SYS_COMMAND_EXECUTE:				/**	コマンド実行	*/
		switch (CommandFileOptionItem) {	/**	コマンド種別	*/
		case SYS_MEMORY_SECURE_TX:			/**	メモリ親展送信	*/
		case SYS_MEMORY_RELAY_BROADCAST:	/**	メモリ中継指示送信	*/
		case SYS_SCANNER_SECURE_TX:			/**	スキャナ親展送信	*/
		case SYS_SCANNER_RELAY_BROADCAST:	/**	スキャナ中継指示送信	*/
		case SYS_DB_POLLING_RX:				/**	検索ポーリング受信	*/
		case SYS_CIPHER_TX:					/** 暗号化送信 1997/06/18  By T.Yamaguchi */
			return(1);
		default:
			break;
		}
		break;
	default:
		break;
	}
#if 0
//	/* for Debag By T.Yamaguchi */
//	if (SYB_MaintenanceSwitch[MNT_SW_B8] & 0x80) {
//		return(1);
//	}
#endif


#if (PRO_CSDR_ITEM == ENABLE)
	/* 【CSDR-No.83】手動送信時、１回目にＮＳＦが検出されなくても非自社機モードで通信する。
	** By O.Kimoto 1998/12/14
	*/
	if (CHK_UNI_NoNeedNsfToManualTx()) {
#if (0) /* デファイン修正 1999/02/02 by T.Soneoka */
**		if (SYS_FaxComType == SYS_MANUAL_TRANSMIT) {	/*	手動送信		 */
#else
		if (SYS_FaxComType == SYS_MANUAL_TX) {	/*	手動送信		 */
#endif
			return(0);
		}
	}
#endif

	/* NSFが取れない場合、もう一度取りに行く By M.Tachibana 1998/04/22 */
	if (CHK_UNI_CommunicationNeedNSF()) {
#if (PRO_TX_SPEED == V34) /* added by H.Kubo 1998/05/14 */
		/* ここで NSF をもう一度取りに行く判断をするのは、 DIS トーンを検出して着信した後、
		** NSF を取り逃がすことがあるため。 V34 では、V8 手順で着信処理をしているので、
		** ここで再度 NSF を取りに行く必要はない。つまり、ここで NSF が取れないということは、
		** NSF は送られてきていないということ。
		*/
		if (!SYS_V34ProcedureExecuting()) {
			return (1);
		}
#else
		return(1);
#endif
	}

	return(0);
}
