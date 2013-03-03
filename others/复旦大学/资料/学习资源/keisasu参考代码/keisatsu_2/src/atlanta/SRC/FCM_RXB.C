/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_RXB.C												 */
/*	モジュール	 :															 */
/*				 : FaxReceive()												 */
/*				 : FaxRxNegotiate()											 */
/*				 : FaxTxSCFR()												 */
/*	作成者		 : 山口														 */
/*	日	付		 :															 */
/*	概	要		 : 受信側フェーズＢ											 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\uni_pro.h"

#include "\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#include "\src\atlanta\sh7043\define\def_tib.h" /* By S.Kawsaki 1996/03/07 */

#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\define\sysdoc.h" /* 1996/06/13 Eguchi */
#include "\src\atlanta\define\sysdial.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\memsw\define\mem_sw_b.h"
#include "\src\memsw\define\mem_sw_c.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\std.h"
#include	"\src\atlanta\define\uni_pro.h"

#if (PRO_FIP == ENABLE)
	#include "\src\atlanta\ext_v\fip_data.h"
#endif

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"

#if defined (KEISATSU) /* 警察FAX 05/06/16 石橋正和 */
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\define\s1_pro.h"
#endif

/*************************************************************************
	module		:[Ｇ３モードで受信]
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
*************************************************************************/
void   FaxReceive(void)
{
	ECM_PageCounter	 = 0;			/*ＥＣＭポストメッセージのページカウンタ	*/
	ECM_BlockCounter = 0;			/*ＥＣＭポストメッセージのブロックカウンタ	*/
	ECM_FrameCounter = 0;			/*ＥＣＭポストメッセージのフレームカウンタ	*/
	RxEOM_ReceiveFlag  = 0;			/*「ＥＯＭ受信」フラグ	*/

	while( ( FaxComPerformingFlag == 1 )
	&& ( RxEOM_ReceiveFlag == 0 )
	&& ( SYS_FaxComStopSwitch() == 0 )){				/** 通信中 & EOM受信なし & StopSwitchなし */
		/*-------------*/
		/*	 Phase B   */
		/*-------------*/
		FaxComPhaseStatus = FAX_RX_PH_B2;

		FaxRxNegotiate();								/** 受信方法確定 */
		RxModeChangeRequestedFlag = 0;					/** 受信モード変更要求なしにフラグセット */

		while( ( FaxComPerformingFlag == 1 )
		&& ( RxModeChangeRequestedFlag == 0 )
		&& ( SYS_FaxComStopSwitch() == 0 )){			/** 通信中 & 受信モード変更要求なし & StopSwitchなし */
			/*-------------*/
			/*	 Phase C   */
			/*-------------*/
			FaxRxPhaseC();								/** 受信フェーズＣ */
		}
	}

	if(( FaxComPerformingFlag == 1 )
	&& ( SYS_FaxComStopSwitch() == 1 )){				/** 通信中 & StopSwitchあり */
		/*---------------*/
		/*	STOP DCN Tx	 */
		/*---------------*/
		FaxPhaseE(5);									/** フェーズＥ */
		ReceiveError(0x14);								/** 受信エラーセット */
	}
}

/*************************************************************************
	module		:[受信方法を確定]
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
*************************************************************************/
void   FaxRxNegotiate(void)
{
	UBYTE	ftt_tx_flag;	 /* Add by NOBUKO  Apr/26/93 */
	UBYTE	rxbaudrate_flag;
	WORD	result;
	UBYTE	command;

#if defined (KEISATSU) /* 警察FAX 05/06/16 石橋正和 */
	BOOL bscramble;		/* スクランブル受信か否か */
	BOOL s1_possible;	/* S1でトレーニングをするか否か */
	
	s1_possible = FALSE;
	bscramble = FALSE;
#endif

	ftt_tx_flag	 = 0;				  /* by NOBUKO */

	if( RxSpeedHandshakeFlag == 1 ){							/** 受信短縮ハンドシェイク設定 */
		/*-------------*/
		/*	 SDCS Rx   */
		/*-------------*/
		RxBaudRate = AttemptRxBaudRate;							/** 確定受信ボーレイト */
		/*--------------------*/
		/*	受信ｺﾝﾊﾟﾁﾌﾞﾙﾁｪｯｸ  */
		/*--------------------*/
		if( RxFirstTimeCompatibleCheckFlag == 1 ){	/** 最初の受信コンパチチェック */
			RxOriginalModeCheck();					/** 相手機の NSSの解析 */
			RxFirstTimeCompatibleCheckFlag = 0;		/** 最初の受信コンパチチェックフラグゼロクリア */
		}
		else {
			OriginalHyperFineModeCheck();
		}
		RxCompatibleCheck();									/** 相手機の DCSの解析 */
		RxSpeedHandshakeFlag = 0;								/** 受信短縮ハンドシェイクフラグゼロクリア */
		if(FaxComPerformingFlag == 1){							/** 通信中 */
			ResultECM_ModeSet();
			/*------------*/
			/*	SCFR  Tx  */
			/*------------*/
#if (PRO_SPEED_EX == ENABLE)
			/* SDCS Rx ～ SCFR(FTT) Tx迄の時間を可変にする	95.11.07 By T.Y*/
			FaxTimer(CHK_UNI_SCFRWaitTime());	/* メモリースイッチの場所は未定 */
#endif
			FaxTxSCFR();										/** SCFR送出 */
		}
		else{
			/*--------------------------*/
			/*	受信ｺﾝﾊﾟﾁﾌﾞﾙﾁｪｯｸ ERROR	*/
			/*--------------------------*/
			FaxPhaseE(1);											/** フェーズＥ */
			if(FaxCompatibleErrorCode == MEMORY_CAPACITY_ERROR) {
				ReceiveError(0x11);/** リモートFAX受信代行バッファ、メモリフルエラー時は、チェックメッセージをださない 21.Jun'94 Y.Suzuki*/
			}
			else {
				ReceiveError(0x12);
			}
		}
	}
	else {
		rxbaudrate_flag = 0;

		while( ( FaxComPerformingFlag == 1 )
		&& ( rxbaudrate_flag == 0 )
		&& ( SYS_FaxComStopSwitch() == 0 )){									/** 通信中 & ???? & StopSwitchなし */
			/*--------------------*/
			/*	受信ｺﾝﾊﾟﾁﾌﾞﾙﾁｪｯｸ  */
			/*--------------------*/
			FaxRxDCS_SemiCompatibleCheck();							/** 相手送信機指定ＴＣＦ受信ボーレイト設定[DCS/CTC] */

			/* R12*15.4L/mmの受信を行なうためのビットを見るようにした	96/05/18 BY T.Yamaguchi */
			if( RxFirstTimeCompatibleCheckFlag == 1 ){
				/* ●ICHOU変更 高速ＲＤＳ by T.Soneoka 1996/06/18 */
#if (PRO_DIAG == ENABLE) /* by H.Kubo 1998/04/02 */
				switch (HighSpeedRDS_CompatibleCheck()) {	/* 高速ＲＤＳデータライトコンパチチェック */
				case DIAG_TRUE:	/* 高速リモート診断の場合 */
				/*
				** 高速ＲＤＳはＥＣＭ Ｏｎで動作するように変更します by T.Soneoka 1997/07/10
				*/
					FcomEcmSize = ECM_256_OCT;
					RxECM_Mode = ECM_ON;
					break;
				case DIAG_FALSE:	/* 高速リモート診断でない場合 */
		            RxOriginalModeCheck();
					break;
				case DIAG_ERR:	/* 高速リモートのコンパチエラー */
					FaxComPerformingFlag = NO;
					break;
				}
#endif /* (PRO_DIAG == ENABLE) */
	            RxFirstTimeCompatibleCheckFlag = 0;
			}
			else {
				OriginalHyperFineModeCheck();
			}

			RxCompatibleCheck();
			ResultECM_ModeSet();
			
			/*----------*/
			/*	TCF RX	*/
			/*----------*/
#if defined (KEISATSU) /* 警察FAX 05/06/16 石橋正和 */
			/* S1でトレーニングをするかチェック */
			if (CMN_CheckScrambleSwOn() == FALSE) { /* 背面スイッチがOFFの場合 */
				s1_possible = FALSE;
			}
			else if (SYS_V34ProcedureExecuting() == 1) { /* V34で交信中 */
				s1_possible = FALSE;
			}
			else {
				s1_possible = S1_CheckScramblePossibility(RxBaudRate);
			}
			
			if (s1_possible == FALSE) { /* S1でトレーニングしない場合 */
				result = FCM_ReceiveTCF(RxBaudRate);
				
				FCM_ExecutingS1Info.Available = FALSE;
				FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
			}
			else {
				FCM_S1_Scramble = TRUE;
				result = S1_ReceiveTCF(RxBaudRate, FCM_S1_Bypass, &bscramble); /* S1でトレーニング */
				
				if ((result == OK) && (bscramble == TRUE)) {
					FCM_S1_Scramble = TRUE;
					FCM_ExecutingS1Info.Available = TRUE;
					if (FCM_ExecutingS1Info.Method == SYS_S1_SENYO) {
						FCM_S1_Senyo = TRUE;
					}
				}
				else {
					FCM_S1_Scramble = FALSE;
					
					FCM_ExecutingS1Info.Available = FALSE;
					FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
					
					/* MDM_SetIO(POS_TPDM, ON); */
					/* MDM_SetIO(POS_HDLC, ON); */
				}
			}
#else
 #if (PRO_TX_SPEED == V34) /* Modified by H.Kubo 1997/08/06 */
			result = FCM_ReceiveTCF( RxBaudRate );
 #else /* (PRO_TX_SPEED == V34)  */
			result = MDM_ReceiveTCF( RxBaudRate );
 #endif /* (PRO_TX_SPEED == V34) */
#endif /* defined (KEISATSU) */

			/* EYE_Q Value をT30バッファにセット */

			if(FaxComPerformingFlag == 1){
				FaxTimer((UWORD)(CHK_TCF_AfterCFR()*10));
				if(result == OK){
					/*------------*/
					/*	 CFR TX	  */
					/*------------*/
					FaxHDLC_Transmit( CFR_F, 0 );
					rxbaudrate_flag = 1;
				}
				else{
					/*------------*/
					/*	 FTT TX	  */
					/*------------*/
					FaxHDLC_Transmit( FTT_F, 0 );

#if (PRO_TX_SPEED == V34) /* Modified by H.Kubo 1997/08/06 */
					if(FCM_ReceiveCommand(TIME_OVER_6SEC, CONTINUE_CCRETRAIN) == FSK_RECEIVE){
#else /* (PRO_TX_SPEED == V34)  */
					if(MDM_ReceiveCommand((UWORD)TIME_OVER_6SEC) == FSK_RECEIVE){
#endif
						command = CheckHDLC_Command();
						/* FX NSS 受信時の処理追加 21.Jly'94 Y.Suzuki */
						if((command == DCS_F) || (command == NSS_F)){
							/*---------------------------------------*/
							/*	DCS Rx	FX NSS Rx／受信ｺﾝﾊﾟﾁﾌﾞﾙﾁｪｯｸ	 */
							/*---------------------------------------*/
							if(command == DCS_F) {
								FaxRxDCS_SemiCompatibleCheck();
							}
						}
						else{
							if( command == DCN_F ){
								/*------------*/
								/*	 DCN Rx	  */
								/*------------*/
								FaxPhaseE(4);
								ReceiveError(0x34);
							}
							else{
#if defined(FIP)
								if( SYS_FIP_Status
								& (	 FIP_FILLIN_CMD | FIP_LOCALSCAN_CMD | FIP_RETRIEVE_CMD )){
									FaxPhaseE(1);
									TransmitError( 0x14, 1 );
								}
#endif

								FaxPhaseE(1);
								ReceiveError(0x23);
							}
						}
					}
					else{
						/*----------------------------*/
						/*	Receive Command TIME OUT  */
						/*----------------------------*/
						/*	 FaxPhaseE(4);						  '93,12,07 By N.S. */
						FaxPhaseE(1);					/*	 '93,12,07 By N.S. */
						ReceiveError(0x23);
					}
					ftt_tx_flag = 1; /* by NOBUKO */
				}
			}
			else{
				/*--------------------------*/
				/*	受信ｺﾝﾊﾟﾁﾌﾞﾙﾁｪｯｸ ERROR	*/
				/*--------------------------*/
				FaxPhaseE(1);			  /* Change by NOBUKO  Apr/25/93 */
				if(FaxCompatibleErrorCode == MEMORY_CAPACITY_ERROR) {
					ReceiveError(0x11);/** リモートFAX受信代行バッファ、メモリフルエラー時は、チェックメッセージをださない 21.Jun'94 Y.Suzuki*/
				}
				else {
					ReceiveError(0x12);
				}
			}
		}
	}
}


/*************************************************************************
	module		:[FaxTxSCFR.C]
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
void   FaxTxSCFR(void)
{
	/*-------------*/
	/*	 SCFR Tx   */
	/*-------------*/
	MakeDIS_FIF();									/** DISのFIFを作成 */
	MakeNSF_FIF();									/** NSFのFIFを作成 16.Jun'94 Y.Suzuki */
	MDM_ModemBuffer[InSTD][2] = CFR_F;
#if (PRO_TX_SPEED == V34) /* Modified by H.Kubo 1997/08/06 */
	FCM_TransmitCommand();				/** コマンド送出 */
#else /* (PRO_TX_SPEED == V34)  */
	MDM_TransmitCommand();									/** コマンド送出 */
#endif /* (PRO_TX_SPEED == V34) */
}

