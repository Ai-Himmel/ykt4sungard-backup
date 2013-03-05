/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_TXB.C												 */
/*	モジュール	 :															 */
/*				 : FaxTransmit()											 */
/*				 : FaxTxNegotiate()											 */
/*				 : FaxTxDCSTCF()											 */
/*				 : FaxTxTraining()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :															 */
/*	概	要		 : 送信側フェーズＢ											 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------------------------------------------------------
	File Name	:  FCM_TXB.C
	Coded By	:  M.HARADA
	Module Name :  FaxTransmit()
				   FaxTxNegotiate()
				   FaxTxDCSTCF()
				   FaxTxTraining()
	Note		:  送信側フェーズＢ
-------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#include	"\src\atlanta\sh7043\define\def_tib.h"

/* #if (PRO_COM_CODEC_TYPE == MN86063)1996/12/12  By T.Yamaguchi */
	#include	"\src\atlanta\define\scn_def.h"
	#include	"\src\atlanta\define\scn_pro.h"
/* #endif */

#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\fcm_def.h"
/*#include	"\src\memsw\define\mem_sw_b.h" @*1996/04/17 Eguchi*/
/*#include	"\src\memsw\define\mem_sw_d.h" @*1996/04/17 Eguchi*/
#include	"\src\atlanta\define\syst30.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\man_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\define\mntsw_b.h"	/* 96/07/29 add By T.Yamaguchi */
#include "\src\atlanta\define\sysscan.h"	/* ADF/FBS識別  97/05/22 */

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
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"
#include	"\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif

#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/07 */
#include	"\src\atlanta\define\cmn_pro.h"
#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 1998/11/17 by T.Soneoka */
 #if defined(SATSUKI2)  /* 他の機種との共用ソースなのでSATSUKI2で切ります。O.Oshima 2003/11/07 Smuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scn_data.h"
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
 #elif defined(STOCKHM2)
#include "\src\atlanta\stockhm2\ext_v\scn_data.h"
#include "\src\atlanta\stockhm2\ext_v\scn_dath.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scn_data.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
 #endif
#include "\src\atlanta\ext_v\cdc_data.h"
#endif

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* added by H.Kubo 1997/12/18 */
/* POPLAR_H では、コードサイズを小さくする最適化コンパイルをしますが、
** そのままだと大量のスタックを消費します。そこで以下の #pragma によって
** 関数先頭での不要なレジスタ待避をさけます。
** 呼出し元で、#pragma noregalloc を宣言していることを確認してください。
** (SuperH RISC engine ファミリ C コンパイラ編 2-34 参照)
** 1997/12/18 H.Kubo 
*/
#pragma noregalloc(FaxTransmit,FaxTxNegotiate)
#endif /* (PRO_MODEM == R288F) */

/* スキャナー送信 左端影が出る テスト T.Nose 1998/03/25 */
#if (PRO_SCN_CODEC_TYPE != SOFTWARE)
#include "\src\atlanta\define\mntsw_c.h"
#include "\src\atlanta\define\idp_def.h"
#include "\src\atlanta\define\idp_pro.h"
#include "\src\atlanta\define\sysshad.h"
#include "\src\atlanta\ext_v\scn_data.h"
#endif

#if defined(STOCKHM2)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
#include	"\src\memsw\define\mem_sw_d.h"
#endif

/*************************************************************************
	module		:[送信側フェーズＢ]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
				]
	condition	:[]
	comment		:[
		修正履歴
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/21]
	author		:[原田]
*************************************************************************/
void	FaxTransmit( void )
{
	UBYTE	command;

	SYS_TxTotalPage		= 0;							/** 送信ページ数ゼロクリア */
	FaxComTxPerformingFlag = 1;						/** 送信中フラグセット */
	while((FaxComPerformingFlag == 1)
	&& (FaxComTxPerformingFlag ==1)
	&& (SYS_FaxComStopSwitch() == 0)){					/** 通信中 & 送信中 & StopSwitch なし */
		DIS_ReceivedFlag = 0;		/*????*/		/** DIS受信フラグ ゼロクリア */
		/*------------*/
		/*	Phase B1  */
		/*------------*/
		if( PollingTxFirstPageFlag == 1 ){				/** ポーリング1枚目送信 */
			/* ●ICHOU変更 by T.Soneoka 1996/06/17 */
#if (PRO_DIAG == ENABLE) /* by H.Kubo 1998/04/02 */
			switch (HighSpeedRDS_CompatibleCheck()) {	/* 高速ＲＤＳデータリードコンパチチェック */
			case DIAG_TRUE:	/* 高速リモート診断の場合 */
				/*
				** 高速ＲＤＳはＥＣＭ Ｏｎで動作するように変更します by T.Soneoka 1997/07/10
				*/
				FcomEcmSize = ECM_256_OCT;
				TxECM_Mode = ECM_ON;
				break;
			case DIAG_FALSE:	/* 高速リモート診断でない場合 */
				TxOriginalPollingModeCheck();			/** 非標準コンパチチェック(ポーリング時) */
				break;
			case DIAG_ERR:	/* 高速リモートのコンパチエラー */
				FaxComPerformingFlag = NO;
				break;
			}
#endif /* (PRO_DIAG == ENABLE) */
			PollingTxFirstPageFlag = 0;			/** ポーリング１枚目チェック後 ゼロクリア */
			if( FaxComPerformingFlag == 0 ){		/** コンパチチェック NG */
				FaxPhaseE(1);					/** フェーズＥ */
				if((FaxCompatibleErrorCode == NO_RX_DOC_POLLING_DOC_ERROR) || (FaxCompatibleErrorCode == TX_NO_POLLING_DOC_ERROR)) {
					TransmitError( 0x31,1 );/* 送信原稿なしエラー 17.Jun'94 Y.Suzuki */
				}
				else {
					TransmitError( 0x22,1 );
				}
			}
#if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/01/31 */
			/* 受信タスクを起動時に獲得したポーリング原稿を開放する為に使用する。
			** By O.Kimoto 1996/11/13
			*/
			MsgFromFaxComToMain.Item = FROM_FAXCOM;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_TX_START;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
			rcv_msg(mbxno.FCM_Task, &FcomMsg);		/* メインよりメッセージ受信 */
#endif
		}
		else{
			FaxTxPhaseB1();							/* CNG出してDISとか見る */
			if(( SYS_TxTotalPage == 0 )
			&& ( FaxComPerformingFlag == 1 )){		/** 最初の送信 & 通信中	 */
#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/07 */
#if defined (KEISATSU) /* 警察FAX 05/09/08 石橋正和 */
				/*--------------------*/
				/* Ｖ３４能力チェック */
				/*--------------------*/
				if (FCM_S1_Scramble == FALSE) { /* スクランブル通信でない場合 */
					if (FCM_CheckPartnerV8Capable()) {	/** Ｖ８能力有り */
						if (SYS_V34ProcedureExecuting() == 0) {
							if ((CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT) == DATA_SIGNALING_RATE_V34_BIT) {	/** Ｖ３４リソースがある */
								V8ProcedureRequestFlag = TRUE;		/** Ｖ８移行要求セット */
								break;							/* ループ脱出 */
							}
						}
					}
				}
#else
				/*--------------------*/
				/* Ｖ３４能力チェック */
				/*--------------------*/
				if (FCM_CheckPartnerV8Capable()) {	/** Ｖ８能力有り */
					if (SYS_V34ProcedureExecuting() == 0) {
						if ((CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT) == DATA_SIGNALING_RATE_V34_BIT) {	/** Ｖ３４リソースがある */
							V8ProcedureRequestFlag = TRUE;		/** Ｖ８移行要求セット */
							break;							/* ループ脱出 */
						}
					}
				}
#endif /* defined (KEISATSU) */
#endif /* (PRO_TX_SPEED == V34) */
				TxOriginalModeCheck();		/** 非標準機能コンパチチェック */
				if( FaxComPerformingFlag == 0 ){	/** コンパチチェック NG */
					FaxPhaseE(1);				/** フェーズＥ */
					TransmitError( 0x22,1 );
				}
			}
		}
		if( FaxComPerformingFlag == 1 ){			/** 非標準コンパチチェック OK */
			/*------------*/
			/*	Phase B2  */
			/*------------*/
			FaxComPhaseStatus = FAX_TX_PH_B2;
			FaxComTxPerformingFlag = 1;				/** 送信中フラグセット */

			/*---------*/
			/*	G3 Tx  */
			/*---------*/
			TxModeChangedFlag = 0;					/** 送信モードチェンジフラグゼロクリア */
			while( ( FaxComPerformingFlag == 1 )
			&& ( TxModeChangedFlag == 0 )
			&& ( SYS_FaxComStopSwitch() == 0 )){				/** 通信中 & モードチェンジなし & StopSwitch なし */
				command = CheckHDLC_Command();		/** HDLCコマンドチェック */
				FaxTxNegotiate( command );			/** 相手機能、回線状況解析、送信属性を確定*/
				TxRetrainingFlag = 0;					/** リトレーニングなしフラグセット */
				if(( FaxComPerformingFlag == 1 )
				&& ( SYS_FaxComStopSwitch() == 0 )){						/** 通信中 & StopSwitchなし */
					MsgFromFaxComToMain.Item = FROM_FAXCOM;
					MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
				/*	MsgFromFaxComToMain.SubMessage1 = DISP_IMAGE_TX_START;	del Y.M */
				/*	snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);			del 1994/05/30 Y.M */

				/*	rcv_msg( mbxno.FCM_Task, &FcomMsg ); */		/* メインよりメッセージ受信 */
				}
				else{
					break;
				}
				/*-----------*/
				/*	Phase C	 */
				/*-----------*/
				FaxTxPhaseC();								/** フェーズＣ */
			}
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
			FaxTimer( 100 );	/* CNG又は、SDCSを出すﾀｲﾐﾝｸﾞをずらす 96/05/21 */
			if (ModeChangeMethodCheck() == HIGH_SPEED_MODE) {				/* By T.Yamaguchi 96/05/24 */
				if ((TxModeChangedFlag == 1) && (FaxComTxPerformingFlag == 1)) {
					TxSpeedHandshakeFlag = 1;
					FaxTxSpeedHandshake();			/** (SNSS)(STSI)SDCS Tx **/
					TxSpeedHandshakeFlag = 0;
				}
			}
#endif
		}
	}

	if(( 1 == FaxComPerformingFlag )
	&& ( 1 == SYS_FaxComStopSwitch() )){						/** 通信中 & StopSwitch あり */
		/*---------------*/
		/*	STOP DCN Tx	 */
		/*---------------*/
		FaxPhaseE(5);								/** フェーズＥ */
		TransmitError( 0x14,1 );
	}

#if (PRO_PANEL == KANJI)
	/* ＩＣＨＯＵからのフィードバック By O.Kimoto 1998/03/30 */
	/* 送信終了後に送信ページ+1のページ数が表示されるため  1997/10/10 s.takeuchi */
	SYS_FaxCommStage = FCM_TRANSMIT;
	SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );
#endif

#if (PRO_TX_SPEED == V34)
	/* ＡＮＳａｍを取りこぼしても、ＤＩＳのビット６をチェックして相手がＶ８能力を持っていたら、
	** ＣＩを送出して、再度Ｖ８に戻る準備をする。（移植もれ）
	** 尚、下記処理が有りますが、変更が汚くなりますので、下記フラグがたっている時は、そのままリターンさせます。
	** By O.Kimoto 1998/03/31
	*/
	if (V8ProcedureRequestFlag == 1) {		/** Ｖ８移行要求? */
		return;			/* Nothing to do 1996/06/19 Y.Murata */
	}
#endif

#if (PRO_SCN_CLUTCH == ENABLE) /*(PRO_SCN_CODEC_TYPE == IDP301)*/ /* 1998/08/25 H.Yoshikawa */ /* 1998/09/29 */
	/*
	** スキャナクラッチ有りの場合 by H.Hirao 1998/11/19
	*/
	/* なにもしない */
#else

/* #if (PRO_COM_CODEC_TYPE == MN86063)	1996/12/05	By T.Yamaguchi	*/
	/*----------------------------------------------------------------------------------*/
	/*	桐のスキャナ送信で最終原稿を排出するために，送信の最後でスキャナクローズする	*/
	/*	但し，通信エラーがあった場合はクローズしない	Oct.18.1994						*/
	/*----------------------------------------------------------------------------------*/
	/* FBS 条件追加 1997/05/22 By T.Yamaguchi */
/*	if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) { */
#if (PRO_FBS == ENABLE)
	if (SYS_ScannerExecMode == SCN_ADF) {
#endif
		if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
			if ((TxPageFinishStatus != TX_DOC_ERR)
			&&	(TxPageFinishStatus != TX_STOPPED)
			&&	(TxPageFinishStatus != TX_1M_OVER)) {	/**	スキャナオープン済	*/
				if (((FaxComResult & 0x00ff) == NO_ERROR)
				||	((FaxComResult & 0x00ff) == 0x0014)		/* 2000/02/03 Y.Murata */
				||	((FaxComResult & 0x00ff) == 0x0041)) {	/**	通信エラーなしor最終原稿でT.4.1 */
					if (!DS1()) {	/** ADF上に残り原稿なし */
						/*	正常終了でADFに残り原稿がない(DS1 OFF)場合のみ排出する
						**	(セット枚数＞指定枚数の時に残りをADF上に残すため)
						**		1997/03/13 s.takeuchi
						*/
						/**	スキャナクローズ (最終原稿を排出)	*/
#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 1998/11/17 by T.Soneoka */
						if (tskno_SCN_STxStoreTask != 0xffff) {
							del_tsk(&tskno_SCN_STxStoreTask);
						}
#endif
						if (SCN_Close(SCN_DOC_EXITING) != SCN_DOC_EXIT_OK) {	/**	結果ＮＧ	*/
							/**	原稿排出ＮＧをメインタスクへ通知	*/
							MsgFromFaxComToMain.Item	= FROM_FAXCOM;
							MsgFromFaxComToMain.Message = MSG_FAXCOM_CLOSE_ERROR;
							snd_msg( mbxno.MAN_Task, &MsgFromFaxComToMain );
							rcv_msg( mbxno.FCM_Task, &FcomMsg );
						}
					}
					/* ブロックエンド（PPS-NULL)中にT.4.1エラーになった場合、ランプが消えない不具合修正 1998/05/25 by T.Soneoka */
					else {
						LampOff();
					}

#if (PRO_SCN_CODEC_TYPE != SOFTWARE)	/* 1998/11/17 by T.Soneoka */
					/* スキャナー送信 左端影が出る テスト T.Nose 1998/03/25 */
					if (SYB_MaintenanceSwitch[MNT_SW_C9] & CHECK_SHADING_RAM) { /* 薄読みデバッグ用 */
						UBYTE i; /* added by H.Kubo 1998/03/25 */
						DIPP_SetBitDIPPST(IDP_BIT_OFF);	/* Shading RAMを読むため */
						DIPP_ReadShadingRAM( &SCN_DebugShadingRAM[0] );	/* 1997/04/25 */
						for (i=0; i<SYS_SHADING_MAX; i++) {
							if (SYB_ShadingRAM[i] != SCN_DebugShadingRAM[i]) {
								/* 違ったらmnt swにセット */
								SYB_MaintenanceSwitch[MNT_SW_C9] |= SHADING_RAM_ERROR1;
								break;
							}
						}
						/* 初期値RAMもコンペアする  1997/04/25 */
						DIPP_ReadInitialRAM( &SCN_DebugInitialRAM1[0] );
						for (i=0; i<SYS_INITIAL_MAX; i++) {
							if ((SYB_InitialRAM[i] != SCN_DebugInitialRAM0[i])
							||	(SYB_InitialRAM[i] != SCN_DebugInitialRAM1[i])) {
								/* 初期値RAMが違ったらmntB6-0にセット */
								SYB_MaintenanceSwitch[MNT_SW_C9] |= SHADING_RAM_ERROR0;
								break;
							}
						}
						DIPP_SetBitDIPPST(IDP_BIT_ON);	/* Shading RAMを読むため */
					}
#endif
				}
				else if ((FaxComResult & 0x00ff) == 0x0012) {	/** 送信枚数＜指定枚数 */
					/*	枚数指定エラー(T.1.2)の時は排出ローラーに噛んだ最終原稿を排出する
					**		1997/03/13 s.takeuchi
					*/

#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 1998/11/17 by T.Soneoka */
					if (tskno_SCN_STxStoreTask != 0xffff) {
						del_tsk(&tskno_SCN_STxStoreTask);
					}
#endif
					/**	スキャナクローズ (最終原稿を排出)	*/
					if (SCN_Close(SCN_DOC_EXITING) != SCN_DOC_EXIT_OK) {	/**	結果ＮＧ	*/
						/**	原稿排出ＮＧをメインタスクへ通知	*/
						MsgFromFaxComToMain.Item    = FROM_FAXCOM;
						MsgFromFaxComToMain.Message = MSG_FAXCOM_CLOSE_ERROR;
						snd_msg( mbxno.MAN_Task, &MsgFromFaxComToMain );
						rcv_msg( mbxno.FCM_Task, &FcomMsg );
					}
				}
			}
		}
#if (PRO_FBS == ENABLE)
	}
#endif
/* #endif */
#endif	/* 1998/08/25 H.Yoshikawa */
}





/*************************************************************************
	module		:[送信方式を確定]
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
	date		:[1993/12/21]
	author		:[原田]
*************************************************************************/
void   FaxTxNegotiate(UBYTE	  command)
{
	TxMethodFlag			 = 0;							/** 送信方法確定フラグゼロクリア */
	BaudrateFlag			 = 0;							/** ボーレート確定フラグ */
	DCS_TxCount				 = 4;							/*	 */

	/*------------*/
	/*	Phase B2  */
	/*------------*/
#if 0 /* RTN, RTP のあと、DCS を最大四回だす不具合の修正。 Ported from CLOVER2 By H.Kubo 1998/07/09 */
@@#if defined(DEU)			/* add by M.HARADA 95.09.13 for pre test */
@@	if(( DIS_F == command ) || ( DTC_F == command ) || ( RTN_F == command ) || ( RTP_F == command )){		/** 受信コマンドが DIS_F or DTC_F or RTN_F or RTP_F */
@@#else
@@	if(( DIS_F == command ) || ( DTC_F == command )){		/** 受信コマンドが DIS_F or DTC_F */
@@#endif
@@			DCS_TxCount--;									/** DCS送信カウンター インクリメント */
@@	}
#else
	/* 1998/07/03 Y.Murata
	*/
	if(( DIS_F == command ) || ( DTC_F == command ) || ( RTN_F == command ) || ( RTP_F == command )){ /** 受信コマンドが DIS_F or DTC_F or RTN_F or RTP_F */
		DCS_TxCount--;									/** DIS送信カウンター デクリメント */
    }
#endif

	while( ( FaxComPerformingFlag == 1 )
	&& ( TxMethodFlag == 0 )
	&& ( BaudrateFlag == 0 )
	&& ( SYS_FaxComStopSwitch() == 0 )){								/** 通信中 & 送信方法未確定
															  & ボーレイト未確定 & StopSwitchなし */
#if defined(FRA)		/* 1995/05/06  by .M.HARADA */
	  if(FRA_PIP_PIN_Rx_Flag == 1){
		TxMethodFlag = 1;								/** 送信方法確定フラグセット */
		FRA_PIP_PIN_Rx_Flag = 0;						/* flag clear */
	  }
	  else{
#endif
		switch( command ){
			/*----------*/
			/*	DIS Rx	*/
			/*----------*/
			case  DIS_F	 :									/** DIS受信 */
				TxCompatibleCheck();					/** DIS(NSF)/DTC(NSC)の解析 */
/**				ResultECM_ModeSet();	*/
				if( FaxComPerformingFlag == 0 ){			/** コンパチチェック NG */
					FaxPhaseE(1);						/** フェーズＥ */
					TransmitError( 0x22,1 );
					break;
				}
				TxMethodFlag = 1;							/** 送信方式確定フラグセット */
				break;
			/*-----------*/
			/*	SCFR Rx	 */										/* 短縮ハンドシェイク */
			/*-----------*/
			case  CFR_F	 :										/** SCFR 受信 */
				TxCompatibleCheck();						/** DIS(NSF)/DTC(NSC)の解析 */
				ResultECM_ModeSet();
				if( FaxComPerformingFlag == 0 ){				/** コンパチチェック NG */
					FaxPhaseE(1);
					TransmitError( 0x22,1 );
					break;
				}
				TxMethodFlag = 1;								/** 送信方式確定フラグセット */
				TxBaudRate = AttemptTxBaudRate;					/** 送信ボーレイトセット */
				BaudrateFlag = 1;								/** ボーレイト確定フラグセット */
				break;
			/*----------*/
			/*	DTC Rx	*/
			/*----------*/
			case  DTC_F	 :										/** DTC受信 */
				TxCompatibleCheck();						/** DIS(NSF)/DTC(NSC)の解析 */
				ResultECM_ModeSet();

#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/07 */
				/* 1996/09/13
				 * V8でのﾌﾟﾗｲﾏﾘﾁｬﾈﾙの指示と違った場合は回線断
				*/
				if (SYS_V34ProcedureExecuting()) {
					if (V34PrimaryChannelDirection == RX_COM_MODE) {	/* ﾌﾟﾗｲﾏﾘﾁｬﾈﾙの指示が受信だった */
						if (FaxComPerformingFlag == 1) {
							FaxComPerformingFlag = 0;
							if (FaxCompatibleErrorCode == NO_ERROR) {
								FaxCompatibleErrorCode = POLLING_TX_DIRECTION_ERROR;
							}
						}
					}
				}
#endif /* (PRO_TX_SPEED == V34) */

#if 0 /* (PRO_F_CODE == ENABLE)	TxOriginalPollingModeCheck()のなかでチェックするが */
/*				EOSでマルチポーリングの場合は、ここで見たほうがよい */
/*				CheckPollingTxF_CODE();						/@@ F_CODEﾋﾞｯﾄﾁｪｯｸ */
#endif
				if( FaxComPerformingFlag == 0 ){				/** コンパチチェック NG */
					FaxPhaseE(3);							/** フェーズＥ */
					TransmitError( 0x22,1 );
					break;
				}
				TxMethodFlag = 1;								/** 送信方法確定フラグセット */
				break;
			/*--------------*/
			/*	RTP/RTN Rx	*/
			/*--------------*/
			case RTP_F	 :										/** RTP受信 */
			case RTN_F	 :										/** RTN受信 */
#if defined(FRA)		/* 1995/05/06  by .M.HARADA */
			case PIN_F	  :
			case PIP_F	  :
#endif
				TxMethodFlag = 1;								/** 送信方法確定フラグセット */
				break;
			/*----------*/
			/*	DCN Rx	*/
			/*----------*/
			case DCN_F	 :										/** DCN受信 */
				FaxPhaseE(4);								/** フェーズＥ */
				TransmitError( 0x11,1 );
				break;
			default		 :										/** デフォルト */
				FaxPhaseE(1);								/** フェーズＥ */
				TransmitError( 0x11,1 );
				break;
		}

#if defined(FRA)		/* 1995/05/06  by .M.HARADA */
	  }
#endif
		if(( FaxComPerformingFlag == 0 )
		|| ( command == CFR_F )){								/** 通信中でない or CFR受信 */
			break;
		}
		command = FaxTxTraining();							/** (NSS)(TSI)DCS･TCF送出 */
	}
}




/*************************************************************************
	module		:[DCS･TCF送信]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[DCS-TCF間の値がV27の場合に７５ｍ以下になるためＴＣＦを相手機が検出できない可能性があるため
				　７５－＞８０に変更　1996/08/07 By T.Yamaguchi
	  －－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	｜	オシロで測定したDCSｰTCF間の時間		変更前(75ms)	変更後(80ms)｜
	｜				Ｖ１７						126ms					｜
	｜				Ｖ３３						142ms					｜
	｜				Ｖ２９						 88ms					｜
	｜				Ｖ２７						 70ms					｜
	 －－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
				]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/21]
	author		:[原田]
*************************************************************************/
void   FaxTxDCSTCF(void)
{
	UWORD	  timer;


	/*--------------------------*/
	/*	 DIS Rx - DCS Tx  Wait	*/
	/*--------------------------*/
#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
	if (SYS_MemorySwitch[MEMORY_SW_D7]) {				/* DIS Rx ～ DCS Tx 迄の時間を可変にする */
		timer = ((unsigned int)(((unsigned int)SYS_MemorySwitch[MEMORY_SW_D7])*10));
	}
	else {
		timer = (UWORD)(FCM_PtnrChk_DIS_AfterDCS()*10);
	}
#else
	timer = (UWORD)(FCM_PtnrChk_DIS_AfterDCS()*10);
#endif
	FaxTimer(timer);

	/*--------------------*/
	/*	(NSS)(TSI)DCS Tx  */
	/*--------------------*/
	MakeDCS_FIF();									/** DCS TSIのFIF作成 */
	MakeNSS_FIF();									/** NSSのFIF作成 */
#if (PRO_F_CODE == ENABLE)
	if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {				/** コマンド通信 */
		if ((CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX) ||
			(CommandFileOptionItem == SYS_MEMORY_SUB_ADDRESS_TX)) {
			if(( SYS_TxTotalPage == 0 ) || (!CHK_UNI_SUB_Frame_Off())) {	/* UNI_SW_B6-4 */
				MakeSUB_FIF();
				MakeTX_PWD_FIF();
			}
		}
	}
#endif

#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/07 */
	FCM_TransmitCommand();			/** DCS送信 */
#else /* (PRO_TX_SPEED == V34) */
	MDM_TransmitCommand();							/** DCS送信 */
#endif /* (PRO_TX_SPEED == V34) */

	if (SYS_V34ProcedureExecuting() == 1) { /* Ported from Clover by H.Kubo 1997/08/07 */
		return;
	}
		
	/** 通常Ｔ３０ */
	/*--------------------------------------------------*/
	/*	 DCS - TCF	Wait  75±20ms[CCITT],75±5ms[FTZ]	*/
	/*--------------------------------------------------*/
	if (FCM_PtnrChk_T23DCS_AfterTCF()) {
		if ((AttemptTxBaudRate == BPS7200_V17)
		 || (AttemptTxBaudRate == BPS9600_V17)
		 || (AttemptTxBaudRate == BPS12000_V17)
		 || (AttemptTxBaudRate == BPS14400_V17)) {		/**	試行送信ボーレート V17	*/
			if (SYB_MaintenanceSwitch[MNT_SW_B9] & 0x0f) {
				timer = ( UWORD )(( UWORD )((FCM_PtnrChk_T23DCS_AfterTCF()*10) - ((SYB_MaintenanceSwitch[MNT_SW_B9] & 0x0f) * 5)));
			}
			else {
				timer = ( UWORD )(FCM_PtnrChk_T23DCS_AfterTCF()*10);
			}
		}
		else if ((AttemptTxBaudRate == BPS12000_V33)
			  || (AttemptTxBaudRate == BPS14400_V33)) {	/* 試行送信ボーレート V33 */
			if (SYB_MaintenanceSwitch[MNT_SW_B9] & 0xf0) {
				timer = ( UWORD )(( UWORD )((FCM_PtnrChk_T23DCS_AfterTCF()*10) - (((SYB_MaintenanceSwitch[MNT_SW_B9] & 0xf0) >> 4)*5)));
			}
			else {
				timer = ( UWORD )(FCM_PtnrChk_T23DCS_AfterTCF()*10);
			}
		}
		else {
			timer = ( UWORD )(FCM_PtnrChk_T23DCS_AfterTCF()*10);
		}
	}
	else {
		if ((AttemptTxBaudRate == BPS7200_V17)
		 || (AttemptTxBaudRate == BPS9600_V17)
		 || (AttemptTxBaudRate == BPS12000_V17)
		 || (AttemptTxBaudRate == BPS14400_V17)) {		/**	試行送信ボーレート V17	*/
			if (SYB_MaintenanceSwitch[MNT_SW_B9] & 0x0f) {
				timer = ( UWORD )(( UWORD )(80 - ((SYB_MaintenanceSwitch[MNT_SW_B9] & 0x0f) * 5)));
			}
			else {
				timer = ( UWORD )80;	/* change 75->80 By T.Yamaguchi 96/08/07 */
			}
		}
		else if ((AttemptTxBaudRate == BPS12000_V33)
			  || (AttemptTxBaudRate == BPS14400_V33)) {	/* 試行送信ボーレート V33 */
			if (SYB_MaintenanceSwitch[MNT_SW_B9] & 0xf0) {
				timer = ( UWORD )(( UWORD )(80 - (((SYB_MaintenanceSwitch[MNT_SW_B9] & 0xf0) >> 4)*5)));
			}
			else {
				timer = ( UWORD )80;	/* change 75->80 By T.Yamaguchi 96/08/07 */
			}
		}
		/* V29の時の時間調整追加 */
		else if ((AttemptTxBaudRate == BPS9600_V29)
			  || (AttemptTxBaudRate == BPS7200_V29)) {	/* 試行送信ボーレート V29 */
			if (SYB_MaintenanceSwitch[MNT_SW_B8] & 0xf0) {
				timer = ( UWORD )(( UWORD )(80 - (((SYB_MaintenanceSwitch[MNT_SW_B8] & 0xf0) >> 4)*5)));
			}
			else {
				timer = ( UWORD )80;	/* change 75->80 By T.Yamaguchi 96/08/07 */
			}
		}
		else {
			timer = ( UWORD )80;	/* change 75->80 By T.Yamaguchi 96/08/07 */
		}
	}

#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
	if (CHK_DisasterPreventionFaxEnable()) {
		timer = (UWORD)(SYS_MemorySwitch[MEMORY_SW_B7]*10);	/* SYS_MemorySwitch[MEMORY_SW_B7] */
	}
#endif	/* End of (PRO_DISASTER_PREVENTION_FAX == ENABLE) */

	FaxTimer( timer );									/** DCS TxからTCF Txまでの時間 */
	/*--------------------*/
	/*		 TCF Tx		  */
	/*--------------------*/
	MDM_TransmitTCF( AttemptTxBaudRate );					/** TCF 送出 */
#if ((PRO_MODEM == R288F) && (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P)) || (PRO_MODEM == MN195006) /* by H.Kubo 1998/10/06  */
	/* TCF で何を送ったか、 T30 モニタで表示するようにします。 1998/10/06 */
	SaveT30Data(SYS_T30_TX_TCF, &MDM_TrueConfValue, 1);
	SaveT30TimingData(SYS_T30_END_TIME);
#else
	SaveT30Data(SYS_T30_TX_TCF, &MDM_ModemBuffer[0][0], 0);
	SaveT30TimingData(SYS_T30_END_TIME);
#endif
}




/*************************************************************************
	module		:[相手の機能、回線状況を解析し、送信属性を確定]
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
	date		:[1993/12/21]
	author		:[原田]
*************************************************************************/
BYTE	FaxTxTraining(void)
{
	UBYTE	command;
	UBYTE	ftt_rxcount;
	UBYTE	ftt_rxcount_max;

	if(FCM_PtnrChkFallbackPattern()) {
		ftt_rxcount_max = 1;
	}
	else{
		ftt_rxcount_max = 2;
	}
	ftt_rxcount = 0;

	while( ( FaxComPerformingFlag == 1 )
	&& ( TxMethodFlag == 1 )
	&& ( BaudrateFlag == 0 )
	&& ( SYS_FaxComStopSwitch() == 0 )){												/** 通信中 & 送信方法確定
																				& ボーレイト未確定 & StopSwitchなし */
		/*------------------------*/
		/*	(NSS)(TSI)DCS,TCF Tx  */
		/*------------------------*/
		FaxTxDCSTCF();														/** (NSS)(TSI)DCS,TCF Tx */
		/*------------------------*/
		/*	 CFR/FTT/DIS/DTC Rx	  */
		/*------------------------*/
#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/07 */
		if ( FCM_ReceiveResponse((UBYTE) 0, NON_CCRETRAIN) == FSK_RECEIVE ){										/** 応答受信あり */
#else /* (PRO_TX_SPEED == V34) */
		if ( MDM_ReceiveResponse(FCM_ReceiveResponseTime) == FSK_RECEIVE ){		/** 応答受信あり */
#endif /* (PRO_TX_SPEED == V34) */
			command = CheckHDLC_Command();									/** HDLCコマンドチェック */
			switch(command){
			case CFR_F :												/** CFR受信 */
				if (SYS_V34ProcedureExecuting() == 0) { /* Ported from Clover by H.Kubo 1997/08/07 */
					TxBaudRate = AttemptTxBaudRate;		/** 送信ボーレイトセット */
				} /* ﾃﾞｰﾀﾚｲﾄはturn-offが終了してからﾘｰﾄﾞする */
				BaudrateFlag = 1;								/** ボーレイト確定フラグセット */
				break;

			/*----------------------------------*/
			/* Ｖ３４ではＦＴＴはかえってこない */
			/*----------------------------------*/
			case FTT_F :												/** FTT受信 */
				DCS_TxCount = 3;
				ftt_rxcount++;									/** FTT受信カウンターインクリメント */
				if( ftt_rxcount_max == ftt_rxcount ){			/** FTTを１or２回受信 */
					ftt_rxcount = 0;							/** FTT受信カウンタークリアー */
					switch ( AttemptTxBaudRate ){
					case BPS14400_V17:						/** 試行ボーレイトがBPS14400_V17 */
						AttemptTxBaudRate = BPS12000_V17;		/** 試行ボーレイトをBPS12000_V17にセット */
						break;
					case BPS12000_V17:						/** 試行ボーレイトがBPS12000_V17 */
						AttemptTxBaudRate = BPS9600_V17;		/** 試行ボーレイトをBPS9600_V17にセット */
						break;
					case BPS9600_V17 :						/** 試行ボーレイトがBPS9600_V17 */
						AttemptTxBaudRate = BPS7200_V17;		/** 試行ボーレイトをBPS7200_V17にセット */
						break;
					case BPS7200_V17 :						/** 試行ボーレイトがBPS7200_V17 */
#if defined(DEU)	/* by M.H '97/03/21 ﾌｫｰﾙﾊﾞｯｸ時に72から24の間に48を追加 */ 
						AttemptTxBaudRate = BPS4800_V27;			/** 試行ボーレイトをBPS4800にセット */
#else
 #if defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
						if (CHK_ForeignApprovalDEU()) {
							AttemptTxBaudRate = BPS4800_V27;			/** 試行ボーレイトをBPS4800にセット */
						}
						else {
							AttemptTxBaudRate = BPS2400_V27;			/** 試行ボーレイトをBPS2400にセット */
							if( 1 == ftt_rxcount_max ){
								ftt_rxcount_max = 4;
							}
						}
 #else
						AttemptTxBaudRate = BPS2400_V27;			/** 試行ボーレイトをBPS2400にセット */
						if( 1 == ftt_rxcount_max ){
							ftt_rxcount_max = 4;
						}
 #endif
#endif
						break;
					case BPS14400_V33:						/** 試行ボーレイトがBPS14400_V33 */
						AttemptTxBaudRate = BPS12000_V33;		/** 試行ボーレイトをBPS12000_V33にセット */
						break;
					case BPS12000_V33:						/** 試行ボーレイトがBPS12000_V33 */
						AttemptTxBaudRate = BPS9600_V29;		/** 試行ボーレイトをBPS9600_V29にセット */
						break;
					case BPS9600_V29 :						/** 試行ボーレイトがBPS9600_V29 */
						AttemptTxBaudRate = BPS7200_V29;		/** 試行ボーレイトをBPS7200_V29にセット */
						break;
					case BPS7200_V29 :						/** 試行ボーレイトがBPS7200_V29 */
						AttemptTxBaudRate = BPS4800_V27;			/** 試行ボーレイトをBPS4800にセット */
						break;
					case BPS4800_V27 :						/** 試行ボーレイトがBPS7200_V29 */
						AttemptTxBaudRate = BPS2400_V27;			/** 試行ボーレイトをBPS2400にセット */
						if( ftt_rxcount_max == 1 ){
							ftt_rxcount_max = 4;
						}
						break;
					case BPS2400_V27 :						/** 試行ボーレイトがBPS2400 */
					default		  :						/** デフォルト */
						FaxPhaseE(1);		/** フェーズＥ */
						TransmitError( 0x23,1 );
						break;
					}
					/*--------------------------------------------------------------
					** 低速な交信速度で大量の送信を行うと、通信時間が大幅に増加してしまう。
					** それならば、一旦回線断してリダイヤルして再送したほうが通信料金削減になります。
					** 2001/04/25 H.Yoshikawa
					*/
					/* ここから追加	 2001/04/25 H.Yoshikawa */
					if (FCM_CheckBaudRate(AttemptTxBaudRate) == FAXCOM_STOP) {
						FaxPhaseE(1);		/** フェーズＥ */
						TransmitError( 0x23,1 );
					} 
					/* ここまで追加	 2001/04/25 H.Yoshikawa */
				}
				break;
			case DIS_F :												/** DIS受信 */
			case DTC_F :												/** DTC受信 */
				 TxMethodFlag = 0;								/** 送信確定フラグゼロクリア */
				 DCS_TxCount--;									/** DCS送信カウンターインクリメント */
				 if( DCS_TxCount == 0 ){						/** DCS送信カウンターが０ */
					 FaxPhaseE(1);								/** フェーズＥ */
					 TransmitError( 0x21,1 );
				 }
				 break;
			case DCN_F :												/** DCN受信 */
				 FaxPhaseE(4);									/** フェーズＥ */
				 TransmitError( 0x21,1 );
				 break;
			default	   :												/** デフォルト */
				 FaxPhaseE(1);									/** フェーズＥ */
				 TransmitError( 0x21,1 );
				 break;
			}
		}
		else{
#if defined(FRA)		/* 1995/05/07  by M.HARADA */
			if ( 1 == CRPReceiveFlag ){
				CRPReceiveFlag = 0;
			}
			else{
#endif
				DCS_TxCount--;													/** DCS送信カウンターインクリメント */
				if ( DCS_TxCount == 0 ){										/** DCS送信カウントが０ */
					FaxPhaseE(1);												/** フェーズＥ */
					TransmitError( 0x21,1 );
				}
#if defined(FRA)		/* 1995/05/07  by M.HARADA */
			}
#endif
		}
	}
	return(command);														/** リターン（応答受信コマンド） */
}

/*************************************************************************
	module		:[指定した送信速度で送信を継続するか否かを獲得する]
	function	:[
		1.
	]
	return		:[
		1．FAXCOM_STOP	送信中止
		2．BPS_XXXXXXX	このボーレートで送信継続する
	]
	common		:[]
	condition	:[]
	comment		:[
		1.戻り値はfcm_def.hに定義されている
		2.この関数は、次の目的に使用します
			低速な交信速度で大量の送信を行うと、通信時間が大幅に増加してしまう。
			それならば、一旦回線断してリダイヤルして再送したほうが通信料金削減になります。
		3.V17以下の通信時のみ使用する。
		4.V34通信時は、FCM_CheckMinimumDataRate(void)で同様の処理を行う。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[2001/04/25]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	FCM_CheckBaudRate(UBYTE baudrate)
{

	switch (baudrate) {
	case BPS4800_V29:
	case BPS4800_V27:
		if (CHK_TxSpeedUpper7200bps()) {
			return(FAXCOM_STOP);
		}
		break;
	case BPS2400_V27:
		if (CHK_TxSpeedUpper7200bps() || CHK_TxSpeedUpper4800bps()) {
			return (FAXCOM_STOP);
		}
		break;
	default:
		break;
	}
	return (baudrate);
}
