/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA			\src\kobe\anzu\src\fcm_main.cを移植		 */
/*	ファイル名	 : FCM_MAIN.C												 */
/*	モジュール	 :															 */
/*				 : FCM_Task()												 */
/*	作成者		 : 山口														 */
/*	日	付		 :															 */
/*	概	要		 : ＦＡＸ通信モジュール										 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\std.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */
#include "\src\atlanta\sh7043\define\io_pro.h"	 /* For CMN_EvacuateStampSetting() 1994/8/25 Y.Suzuki */
#include "\src\atlanta\sh7043\define\def_tib.h" /* By S.Kawsaki 1996/03/07 */

#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\define\sysdoc.h" /*1996/06/13 Eguchi */
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\atd_def.h"	/* 料金管理のため 1994/8/25 Y.Suzuki */

#include "\src\atlanta\define\sysfcode.h"

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
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

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997\10/14 */
#include "\src\atlanta\define\uni_pro.h"
#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_FIP == ENABLE)
	#include "\src\atlanta\define\fip_def.h"
#endif

#include "\src\atlanta\ext_v\scn_data.h"	/* For SCN_MotorStopRequest 1994/8/25 Y.Suzuki */
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
#include "\src\atlanta\ext_v\man_data.h"
#endif

#if (PRO_FBS == ENABLE)
#include "\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif

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

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.2.26 K.Kawata */
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\unisw_c.h"
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#include "\src\atlanta\prt\thermal\define\prn_pro.h"
#include "\src\atlanta\prt\thermal\define\prn_def.h"
#endif

#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
 #if defined(SATSUKI2)  /* 他の機種との共用ソースなのでSATSUKI2で切ります。O.Oshima 2003/11/07 Smuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"	/* Add by T.Soneoka 1999/03/12 */
 #elif defined(STOCKHM2)
#include "\src\atlanta\stockhm2\ext_v\scn_dath.h"	/* Add by T.Soneoka 1999/03/12 */ 
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"	/* Add by T.Soneoka 1999/03/12 */
 #endif
#endif

#if defined(POPLAR_F)
#include "\src\atlanta\sh7043\ext_v\extv_mon.h"
#include "\src\atlanta\sh7043\define\def_tcb.h"
#include "\src\atlanta\sh7043\define\def_mon.h"
#include "\src\atlanta\define\cdc_pro.h"
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/18*/
#include "\src\atlanta\define\man_pro.h"
#endif

#if defined (KEISATSU) /* 警察FAX 05/06/27 石橋正和 */
#include "\src\atlanta\define\s1_def.h"

#endif

#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/12/18 */
/* POPLAR_H では、コードサイズを小さくする最適化コンパイルをしますが、
** そのままだと大量のスタックを消費します。そこで以下の #pragma によって
** 関数先頭での不要なレジスタ待避をさけます。
** (SuperH RISC engine ファミリ C コンパイラ編 2-34 参照)
** 1997/12/18 H.Kubo 
*/
#pragma noregalloc(FCM_Task)
#endif /* (PRO_MODEM == R288F) */
/*************************************************************************
	module		:[ＦＡＸ通信制御メイン]
	function	:[
		1. メインタスクより起動される
		2. 通信種別を解析し 送信／受信処理を行う
		3. 通信終了後、通信時間を算出し通信結果をジャーナルにセットする
		4. メインタスクにメッセージを送信し自爆する
	]
	commom		:[
		SYS_FaxComType					: 通信種別
		SYS_FaxComTxType				: 送信タイプ
		SYB_CurrentTime					: トータル・タイマ
		SYS_FIP_Status					: ＦＩＰステータス
		SYS_FaxComFIP_RxActiveFlag		: ＦＩＰ通信中フラグ
		FaxComTXorRX_Sign				: 送受信コマンド
		FaxComResult					: 通信結果
		FaxComPeriod					: 通信時間
		FaxComStartTime					: 通信開始時刻
		FaxComPerformingFlag			: 通信中グラグ
		SYS_TxTotalPage					: 送信ページ
		SYS_RxTotalPage					: 受信ページ
		TxBaudRate						: 送信ボーレイト
		RxBaudRate						: 受信ボーレイト
		FipComBaudRate					: ＦＩＰボーレイト
		FipTotalPage					: ＦＩＰトータルページ
		FipComTime						: ＦＩＰ通信時間
		FipComResult					: ＦＩＰ結果
		struct	SYS_ExecQueueData_t	  *SYS_CurrentExecutingCommand	: 発信スケジューラー
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[1994/01/24]
	author		:[村田]
*************************************************************************/
void	FCM_Task(void)
{
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.7.8 K.Kawata */
	BYTE	send_end_message;
#endif
#if defined(POPLAR_F)
	UWORD	check_tskno;
#endif
#if(PRO_COST == ENABLE)
	/* 料金管理のため追加 1994/8/12 Y.Suzuki */
	UBYTE cost_data; /* SYB_NTT_AccessFile[] のオフセット */
	UBYTE exec_no;	/* 料金管理のマルチ回線対応のため  1997/09/19 s.takeuchi */

	cost_data = 0;
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
	if (tskno_NCU_FaxComTelHookChkTask == 0xffff) {
		cre_tsk(&tskno_NCU_FaxComTelHookChkTask, TSK_NCU_FAXCOMTELHOOKCHKTASK, 0);
	}
#endif

	/* 警察FAX DVT_ID46 Added by SMuratec 夏 2005/11/25 */
 #if defined(KEISATSU)	
 	/* 警察FAX DVT_ID78 Modified by SMuratec 李 2005/12/19 */
 	if (IsJournalCompleted == FALSE) {
		/*---------------------------*/
		/** メインよりメッセージ待ち */
		/*---------------------------*/
		rcv_msg( mbxno.FCM_Task, &FcomMsg );
		CMN_DisableInterrupt();			/* DI */
		BackupFcomMsg.Item = FcomMsg->Item;							/* FROM_MAIN */
		BackupFcomMsg.Message = FcomMsg->Message;					/* 交信種別 */
		BackupFcomMsg.SubMessage1 = FcomMsg->SubMessage1;			/* コマンド番号 */
		BackupFcomMsg.SubMessage2 = FcomMsg->SubMessage2;
		BackupFcomMsg.SubMessage3 = FcomMsg->SubMessage3;
		BackupFcomMsg.SubMessage4 = FcomMsg->SubMessage4;
		FcomMsg = &BackupFcomMsg;		/* 一応ｾｰﾌﾞし直す */
		CMN_EnableInterrupt();			/* EI */

		while (!IsJournalCompleted){ 
			wai_tsk(10);	/* 通信履歴を作成の待ち */
		}
		/*-------------*/
		/** 変数初期化 */
		/*-------------*/
		InitializeFaxCom();

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2002/03/07 T.Takagi */
		/*-------------*/
		/** Clock供給  */
		/*-------------*/
		if (SYS_HaltClock == FALSE) {		/* この時点でクロックが供給されていなければ */
			HaltClockOn();
			wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
			CMN_DisableInterrupt();			/**	割り込み禁止 2002/03/07 T.Takagi */
			SubResetOff();
			SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
			CMN_EnableInterrupt();			/**	割り込み許可 */
		}
#endif

		/*---------------*/
		/** モデム初期化 */
		/*---------------*/
		MDM_ModemInitialize();

	#if (PRO_MODEM == R288F)				/* ROCKWELL製 28.8K */
		/* モデム救済タスク起動 By O.Kimoto 1998/02/03 */
		if (tskno_MDM_ModemRecoverTask == 0xffff) {
			cre_tsk(&tskno_MDM_ModemRecoverTask, TSK_MDM_MODEMRECOVERTASK, 0);
		}
	#endif

	}
	else {
 #endif
 
	/*-------------*/
	/** 変数初期化 */
	/*-------------*/
	InitializeFaxCom();

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2002/03/07 T.Takagi */
	/*-------------*/
	/** Clock供給  */
	/*-------------*/
	if (SYS_HaltClock == FALSE) {		/* この時点でクロックが供給されていなければ */
		HaltClockOn();
		wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
		CMN_DisableInterrupt();			/**	割り込み禁止 2002/03/07 T.Takagi */
		SubResetOff();
		SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
		CMN_EnableInterrupt();			/**	割り込み許可 */
	}
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
 #if (1) /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
	MAN_ChangeEcoMode(0);
 #else
//	MAN_ChangeEcoMode(FALSE);
 #endif
#endif

	/*---------------*/
	/** モデム初期化 */
	/*---------------*/
	MDM_ModemInitialize();

#if (PRO_MODEM == R288F)				/* ROCKWELL製 28.8K */
	/* モデム救済タスク起動 By O.Kimoto 1998/02/03 */
	if (tskno_MDM_ModemRecoverTask == 0xffff) {
		cre_tsk(&tskno_MDM_ModemRecoverTask, TSK_MDM_MODEMRECOVERTASK, 0);
	}
#endif


	/*---------------------------*/
	/** メインよりメッセージ待ち */
	/*---------------------------*/
	rcv_msg( mbxno.FCM_Task, &FcomMsg );
	CMN_DisableInterrupt();			/* DI */
	BackupFcomMsg.Item = FcomMsg->Item;							/* FROM_MAIN */
	BackupFcomMsg.Message = FcomMsg->Message;					/* 交信種別 */
	BackupFcomMsg.SubMessage1 = FcomMsg->SubMessage1;			/* コマンド番号 */
	BackupFcomMsg.SubMessage2 = FcomMsg->SubMessage2;
	BackupFcomMsg.SubMessage3 = FcomMsg->SubMessage3;
	BackupFcomMsg.SubMessage4 = FcomMsg->SubMessage4;
	FcomMsg = &BackupFcomMsg;		/* 一応ｾｰﾌﾞし直す */
	CMN_EnableInterrupt();			/* EI */

 #if defined(KEISATSU)	/* 警察FAX DVT_ID74 Added by SMuratec 李 2005/12/17 */
 	}
 #endif /* defined(KEISATSU) */
#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/19*/
	MAN_ExecEcoWakeUp();
#endif

	/*---------------*/
	/** 交信種別取得 */
	/*---------------*/
	SYS_FaxComType = (UBYTE)FcomMsg->Message;

	MsgFromFaxComToMain.Item = FROM_FAXCOM;

	SYS_BackupFaxComType = SYS_FaxComType;	/* 1997/12/05 */

	/* 回線モニターの設定は RelaySetting() のなかでやっていいる */


#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
	/* Ｃｌｏｖｅｒとは構造が異なるので仕方なくここに入れておきます。
	** Ｖ．８手動送・受信勧告違反対策
	** by O.Kimoto 1997/10/07
	*/
	if ((SYS_FaxComType == SYS_MANUAL_TX) || (SYS_FaxComType == SYS_MANUAL_RX)) {
		if (!CHK_ManualFaxComV8Enable()) {
			CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
			V8ProcedureRequestFlag = 0;					/** Ｖ８手順移行要求クリア */
		}
	}
#endif

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Mod. by J.Kishida 2002/09/09 */
	if ((AttemptRxModeSwitch == SYS_TEL_FAX_READY)
	 || (AttemptRxModeSwitch == SYS_FAX_TEL_READY )
	 || (AttemptRxModeSwitch == SYS_ANS_FAX_READY)) {	/* for NTT */
		if (CHK_TelFax_AnsFaxV34Mask()) {
			CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
			V8ProcedureRequestFlag = 0;					/** Ｖ８手順移行要求クリア */
		}
	}
 #endif
#endif

	/*----------------*/
	/* 交信種別の判定 */
	/*----------------*/
	switch (SYS_FaxComType) {			/** 交信種別判定 **/

		case SYS_COMMAND_EXECUTE:				/** コマンド通信 **/

			/* キュー番号をセーブしておきます */
			SYS_CurrentExecuteNoSave = (UBYTE)FcomMsg->SubMessage1;

#if (PRO_COST == ENABLE)	/* 料金管理のマルチ回線対応のため  1997/09/19 s.takeuchi */
			exec_no = (UBYTE)FcomMsg->SubMessage1;
#endif

			/*------------------------*/
			/** コマンド通信情報取得 **/
			/*------------------------*/
			GetCommandFileData();
			
			/*
			** 受領証設定でT4.1/T4.4でﾘﾀﾞｲﾔﾙで受領証受信した時に、送信証もでてくる
			** ためクリアしておく	1998/04/21  By T.Yamaguchi
			*/
			SYS_CurrentExecutingCommand->Option &= ~(SYS_PARTNER_NOT_RCR);

			/*--------------------------------------------------*/
			/** 発信スケジューラー(SYS_ExecQueue) 使用状況 Set **/
			/*--------------------------------------------------*/
#if 0	/* メインで行う 1999/10/21 Y.Murata NAGANOより */
//			if (SYS_CurrentExecutingCommand->Status == SYS_EXEC_FORWARD_WAITING) {		/** 転送予約中 */
//				SYS_CurrentExecutingCommand->Status = SYS_EXEC_FORWARD_EXECUTE;				/** 転送実行中 */
//			}
//			else {
//				SYS_CurrentExecutingCommand->Status = SYS_EXEC_EXECUTE;						/** 実行中 */
//			}
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/02/05 */
			if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
				SYS_CurrentExecutingCommand->Option &= ~SYS_EXT_LINE_TX;
			}
			else {
				SYS_CurrentExecutingCommand->Option |= SYS_EXT_LINE_TX;
			}
#endif
			GetFaxComTxType();						/** 送信タイプ確定 */
			GetFirstTxDocumentData();				/** 送信原稿情報設定 */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
			FCM_QuickMemoryTxExecute = FCM_CheckQucikMemoryTx();
#endif

			if(SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
				/** V53 スキャナー送信時済みスタンプ初期化処理 1994/8/25 Y.Suzuki */
				CMN_EvacuateStampSetting();
/* #if(PRO_PRINT_TYPE == LASER)	ＬＥＤプリンタでも必要？	1996/11/27	By T.Yamaguchi */
				SCN_MotorStopRequest = 1; /**  原稿読み取り終了時にモーター停止を行うにセット */
/* #endif */
#if (PRO_FBS == ENABLE)
				/* FBS原稿サイズ選択済みフラグ初期化 T.Nose 1997/06/23 */
				IsBookDocSizeSet = FALSE;
#endif
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
				/* 仕様変更
				** 読み取り中において、ＤＳ２がＯＦＦした時点でＤＳ１もＯＦＦしていれば、今読んだ原稿が
				** 最終原稿であるという風に変更
				** カバーページ送信Ｏｎでスキャナ送信時、カバーページしか送らない不具合
				** 1999/03/12 by T.Soneoka
				*/
				NoNextDocument = FALSE;
#endif
			}
#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
			/* V34ｽﾀｰﾄｱｯﾌﾟｴﾗｰが出たときのﾘﾀﾞｲｱﾙはV17で交信 */ /* 1997/05/20 */
			if (SYS_CurrentExecutingCommand->Option & SYS_V34_STUP_RECOVER) {
				/* SYS_DataSignalingRate &= 0xFFFE; */
				CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
			}
#endif /* (PRO_TX_SPEED == V34) */

			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			if ((CommandFileOptionItem == SYS_POLLING_RX)		 ||
				(CommandFileOptionItem == SYS_DB_POLLING_RX)	 ||
#if (PRO_CONTINUOUS_POLLING == ENABLE)
				(CommandFileOptionItem == SYS_CONTINUOUS_POLLING_RX) ||		/* Oct.21.1996	By T.Yamaguchi */
#endif
#if (PRO_F_CODE == ENABLE)
				(CommandFileOptionItem == SYS_SELECT_POLLING_RX) ||		/* 1997/01/09  By T.Yamaguchi */
#endif
				(CommandFileOptionItem == SYS_SEQUENTIAL_POLLING)) {	/** ポーリング受信 */
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/5 K.Kawata*/
				PRN_ChechRxPrintCallProc();
#endif
				SYS_FaxCommStage = FCM_POLLING;
			}
			else {
				SYS_FaxCommStage = FCM_TRANSMIT;
			}
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

#if(PRO_RELAYED_REPORT == ENABLE)/* 95/03/17 Y.Suzuki */
			if(CommandFileOptionItem == SYS_RELAYED_TX_REPORT) {
				TxRelayReport = 1;/* 不達通知送信時、会話予約キーを入力しない */
				/* TSK_LST_RELAYEDTXREPORTIMAGETASKは文字数オーバでワーニングがでるので短くします */
				if (tskno_LST_RelayedTxReportImage == 0xffff) { /* by H.Kubo 1998/01/19 */
					cre_tsk(&tskno_LST_RelayedTxReportImage, TSK_LST_RLYTXREPORTIMAGETASK, 0);
				}
			}
			AutoFax();								/** 自動ダイアル通信処理 */
			TxRelayReport = 0;						/* 不達通知送信時、会話予約キーを入力しない クリア */

			if (tskno_LST_RelayedTxReportImage != 0xffff) { /* by H.Kubo 1998/01/19 */
				del_tsk(&tskno_LST_RelayedTxReportImage);
			}

#else
			AutoFax();								/** 自動ダイアル通信処理 */
#endif
			CheckAllErrorPage();					/** T.4.2エラーを出すかどうかチェック */
			break;

		case SYS_MANUAL_TX:						/** 手動送信 **/

			/* 手動送信は、部門管理扱いではない 94/11/16 Y.Suzuki */
			/** オートダイヤラーからの発信時のみ使用するコストテーブルを決定 */

			GetFaxComTxType();						/** 送信タイプ確定 */
			GetFirstTxDocumentData();				/** 送信原稿情報取得 */

			/** V53 スキャナー送信時済みスタンプ初期化処理 1994/8/25 Y.Suzuki */
			CMN_EvacuateStampSetting();
/* #if(PRO_PRINT_TYPE == LASER)	ＬＥＤプリンタでも必要？	1996/11/27	By T.Yamaguchi */
			SCN_MotorStopRequest = 1; /**  原稿読み取り終了時にモーター停止を行うにセット */
/* #endif */

#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
			/* 仕様変更
			** 読み取り中において、ＤＳ２がＯＦＦした時点でＤＳ１もＯＦＦしていれば、今読んだ原稿が
			** 最終原稿であるという風に変更
			** カバーページ送信Ｏｎでスキャナ送信時、カバーページしか送らない不具合
			** 1999/03/12 by T.Soneoka
			*/
			NoNextDocument = FALSE;
#endif

			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			SYS_FaxCommStage = FCM_TRANSMIT;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */
			ManualTransmit();						/** 手動送信処理 */
			CheckAllErrorPage();					/** T.4.2エラーを出すかどうかチェック */
			break;

		case SYS_MANUAL_RX:						/** 手動受信 **/

#if (PRO_FIP == ENABLE)
			if ((SYB_FIP_ReceiveEnableFlag == 1) && (SYS_FIP_Status == FIP_IDLE)) {
				SYS_FIP_Status |= FIP_DURING_RX;
				SYS_FaxComFIP_RxActiveFlag = 1;				/** ＦＩＰ受信中フラグ */
			}
#endif
			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			SYS_FaxCommStage = FCM_RECEIVE;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

			ManualReceive();						/** 手動受信処理 */
			/* ﾎﾟｰﾘﾝｸﾞ送信でRTN受信した時T.4.2にする 1996/10/30 Y.Murata */
			CheckAllErrorPage();					/** T.4.2エラーを出すかどうかチェック */

			break;

		case SYS_AUTO_CALLED:					/** 自動着信 **/

#if (PRO_FIP == ENABLE)		/* Add By M.Tachibana 94/02/13 */
			if ((SYB_FIP_ReceiveEnableFlag == 1) && (SYS_FIP_Status == FIP_IDLE)) {
				SYS_FIP_Status |= FIP_DURING_RX;
				SYS_FaxComFIP_RxActiveFlag = 1;				/** ＦＩＰ受信中フラグ */
				SYS_FaxComType = SYS_FIP_CALLED;			/* 交信種別再設定 */
			}
#endif

			GetFaxComTxType();						/** 送信タイプ確定 */

			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			SYS_FaxCommStage = FCM_CALLED;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

			AutoCalled();							/** 自動着信処理 */

			/* ﾎﾟｰﾘﾝｸﾞ送信でRTN受信した時T.4.2にする 1996/10/30 Y.Murata */
			CheckAllErrorPage();					/** T.4.2エラーを出すかどうかチェック */
			break;

		case SYS_TRANSFER_AUTO_CALLED:					/** 転送受信 **/

			ForwardReceiveFlag = 1;					/** 転送受信フラグセット */
			BackUpForwardReceiveFlag = 1;			/** 転送受信バックアップフラグセット */
			SYS_FaxComType = SYS_AUTO_CALLED;		/* 交信種別再設定 */

#if (PRO_FIP == ENABLE)		/* Add By M.Tachibana 94/02/13 */
			if ((SYB_FIP_ReceiveEnableFlag == 1) && (SYS_FIP_Status == FIP_IDLE)) {
				SYS_FIP_Status |= FIP_DURING_RX;
				SYS_FaxComFIP_RxActiveFlag = 1;				/** ＦＩＰ受信中フラグ */
				SYS_FaxComType = SYS_FIP_CALLED;			/* 交信種別再設定 */
			}
#endif

			GetFaxComTxType();						/** 送信タイプ確定 */

			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			SYS_FaxCommStage = FCM_CALLED;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

			AutoCalled();							/** 自動着信処理 */

			/* ﾎﾟｰﾘﾝｸﾞ送信でRTN受信した時T.4.2にする 1996/10/30 Y.Murata */
			CheckAllErrorPage();					/** T.4.2エラーを出すかどうかチェック */

			break;

		case SYS_FNET_AUTO_CALLED:					/** Ｆネット着信 **/

			FaxNetReceiveFlag = 1;					/** Ｆネット着信フラグセット */
			SYS_FaxComType = SYS_AUTO_CALLED;		/* 交信種別再設定 */

#if (PRO_FIP == ENABLE)		/* Add By M.Tachibana 94/02/13 */
			if ((SYB_FIP_ReceiveEnableFlag == 1) && (SYS_FIP_Status == FIP_IDLE)) {
				SYS_FIP_Status |= FIP_DURING_RX;
				SYS_FaxComFIP_RxActiveFlag = 1;				/** ＦＩＰ受信中フラグ */
				SYS_FaxComType = SYS_FIP_CALLED;			/* 交信種別再設定 */
			}
#endif

			GetFaxComTxType();						/** 送信タイプ確定 */

			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			SYS_FaxCommStage = FCM_CALLED;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

			AutoCalled();							/** 自動着信処理 */

			/* ﾎﾟｰﾘﾝｸﾞ送信でRTN受信した時T.4.2にする 1996/10/30 Y.Murata */
			CheckAllErrorPage();					/** T.4.2エラーを出すかどうかチェック */

			break;

#if (PRO_FIP == ENABLE)

		case SYS_FIP_SEND:						/** FIP送信コマンド **/

			/* 部門管理扱いではない。94/11/16 Y.Suzuki */
			/** オートダイヤラーからの発信時のみ使用するコストテーブルを決定 */

			GetFaxComTxType();						/** 送信タイプ確定 */

			GetFirstTxDocumentData();				/** 送信原稿情報取得 */

			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			SYS_FaxCommStage = FCM_TRANSMIT;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

			FipFaxCom();							/** FIPコマンド送信処理 */
			break;

		case SYS_FIP_POLL:						/** FIPポーリング受信コマンド **/

			SYS_FaxComFIP_RxActiveFlag = 1;

			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			SYS_FaxCommStage = FCM_RECEIVE;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

			FipFaxCom();							/** FIPコマンド送信処理 */
			break;

		case SYS_FIP_CALLED:					/** FIP自動受信 **/
			/* このパスは通りません	 By M.Tachibana 94/02/13 */
			/* MANからMessageがSYS_?_AUTO_CALLEDがきた時	 */
			/* その中でFIP受信かどうか判断します			 */

			GetFaxComTxType();						/** 送信タイプ確定 */
			SYS_FaxComFIP_RxActiveFlag = 1;

			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			SYS_FaxCommStage = FCM_CALLED;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

			AutoCalled();							/** 自動着信処理 */
			break;
#endif

#if (PRO_REMOTE_FAX == ENABLE)

		case SYS_REMOTE_FAX_TX:

			GetFaxComTxType();						/** 送信タイプ確定 */
			GetFirstTxDocumentData();				/** 送信原稿情報取得 */

			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			SYS_FaxCommStage = FCM_REMOTE_FAX_TRANSMIT;		/* 1994/09/06 FCM_TRANSMIT -> FCM_REMOTE_FAX_TRANSMIT */
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

	#if (PRO_DRAM_BACKUP == ENABLE)
			SYS_RemoteFaxTxPerformingFlag = 1;		/* 1994/12/19 */
	#endif

			ManualTransmit();						/** 手動送信処理 */
			CheckAllErrorPage();					/** T.4.2エラーを出すかどうかチェック */
			break;

#endif

		case SYS_MANUAL_POLLING:			/** 手動ポーリング受信 */
			/*-------------*/
			/** ＬＣＤ表示 */
			/*-------------*/
			SYS_FaxCommStage = FCM_POLLING;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

			rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* メインよりメッセージ受信 */

			ManualPollingReceive();						/** 手動ポーリング受信処理 */

			break;
#if defined (KEISATSU) /* 警察FAX 05/07/01 石橋正和 */
		case SYS_ISSEI_TX: /* 一斉指令送信 */
			FCM_IsseiTx(FALSE);
			break;
		case SYS_ISSEI_RX: /* 一斉指令受信 */
			FCM_IsseiRx(FALSE);
			break;
		case SYS_ISSEI_KIDO_RX: /* 指令起動信号による一斉指令受信 */
			FCM_IsseiRx(TRUE);
			break;
#endif
		default:
			break;
	}
	
#if defined (KEISATSU) /* 警察FAX 05/11/21 石橋正和 */
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE) { /* 警電着信による強制終了の場合 */
		FaxComResult = (FaxComResult & 0xFF00) | 0x0091;
 #if 0	/* 警察FAX DVT_ID63 Deleted by SMuratec 夏 2005/12/13 */
		IsJournalCompleted = FALSE;			/* 警察FAX DVT_ID46 Added by SMuratec 夏 2005/11/25 */
 #endif
	}
#endif
	
	/*----------------------------------------------------------------------------*/
	/* プリンターエラーがこの時点までたっていいると言う事は、受信最終ページで	  */
	/* プリンターエラーが起こったということになるのでメインにメッセージをかえして */
	/* エラーをセットしてもらう						1994/11/02					  */
	/*----------------------------------------------------------------------------*/
#if (PRO_PRINTER_RX == ENABLE)
	if (RxPrinterErrorFlag == 1) {	/** プリンターエラーがたっている */
		MsgFromFaxComToMain.SubMessage1 = GetRxPrinterErrorStatus();	/** プリンターエラーセット */
		SendMsgFaxComToMain( MSG_FAXCOM_PRINTER_ERROR );				/** メインにメッセージ送信 */
	}
#endif

	/*----------------*/
	/** 通信時間算出 **/
	/*----------------*/
	FaxComPeriod = (UWORD)( SYB_CurrentTime - FaxComStartTime );			/** 通信時間（秒） */

	/*
	** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
	** By S.Kawasaki 1996/09/02
	*/
	FaxComPeriod = (UWORD)(SYS_1SecGeneralTimer - SYS_FCM_StartTime);


	/* 警察FAX DVT_ID46 Added by SMuratec 夏 2005/11/25 
	** 強制中断中、通信開始時間SYS_FCM_StartTime設置しない（通信起動失敗)の場合
	** 今回中断通信のTotal時間は０になる
	*/
#if defined(KEISATSU)
	if ((SYS_FCM_StartTime == 0) && ((FaxComResult & 0x00FF) == 0x0091)){

		FaxComStartTime = SYB_CurrentTime;	/** 交信開始時間（秒） */
		/*
		** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
		** By S.Kawasaki 1996/09/02
		*/
		SYS_FCM_StartTime = SYS_1SecGeneralTimer;

		/* ジャーナルセット関数化 1996/11/29  By T.Yamaguchi */
		SetPatJournalDataAtAutoFax();
		
		FaxComPeriod = 0;
	}
#endif	

	/*------------------*/
	/** 料金管理の処理	*/
	/*------------------*/
#if(PRO_COST == ENABLE)
#if (0) /* マルチ回線に対応するため統一する  1997/09/19 s.takeuchi */
** 	/* 料金管理のため場所移動 1994/12/26 Y.Suzuki */
** 	/** 使用するコストテーブルを決定 */
** 	/* 中継指示受信した原稿を送信する場合、料金管理がON していても計算しない。28.Dec'94 */
** 	if((SYS_FaxComType == SYS_COMMAND_EXECUTE)
** 	&& (CommandFileOptionItem != SYS_RELAYED_TX)
** 	&& (CommandFileOptionItem != SYS_RELAYED_TX_REPORT)
** 	&& (CommandFileOptionItem != SYS_BATCH_MEMORY_TX)) {	/** 交信種別判定 **/
** 		cost_data = FCM_GetCostTable(SYS_DialingNumber.Buffer);
** 		if(CheckCostTable(cost_data)) { /** 部門管理がONの場合 */
** 			CheckCostFlag = 1;
** 		}
** 		else {
** 			CheckCostFlag = 0;
** 		}
** 		if(CheckCostFlag && ((AD_Result == AD_OK_CED) || (AD_Result == AD_OK_DIS) || (AD_Result == AD_OK_DSE))) { /** 部門管理がONで受信機と接続できた場合 */
** 			FCM_CostCalculate(CommandFileDepartmentCode,SYB_NTT_AccessFile[cost_data].CostTable);
** 		}
** 	}
#else
	/** 自動送信で相手に繋がっていたら料金計算する */
	if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {
		if ((AD_Result == AD_OK)
#if 1 /* 回線が相手側とつながる条件をすべていれる。Added by H.Kubo 1998/04/24 */
		||	(AD_Result == AD_OK_DIS)
		||	(AD_Result == AD_OK_CED)
		||	(AD_Result == AD_OK_ANSWER_TONE)
 #if (PRO_SPEED_EX == ENABLE)
		||	(AD_Result == AD_OK_SPD_TONE)
 #endif
#endif /* 1 */
		||	(AD_Result == AD_OK_DSE)) {
			FCM_SetCostData( exec_no, SYS_DialingNumber.Buffer );
		}
	}
#endif
#endif

	/*-------------*/
	/** 通信後処理 */
	/*-------------*/
	FaxComAfterCheck();

	/* 2000/02/10 Y.Murata
	 *
	*/
/*#if defined(POPLAR_F)*/
	if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
		if (((FaxComResult & 0x0C00) == TRANSMITERROR)
		|| ((FaxComResult & 0x0C00) == RECEIVEERROR)) {	/* ダイアルエラーでない時 */
			/** モーター励磁OFFする */
			SCN_MotorCurrentStopCounter = 10;
		}
	}
/*#endif*/


#if (PRO_FIP == ENABLE)
	/*-----------------------*/
	/** ＦＩＰデータ・セーブ */
	/*-----------------------*/
	if (FaxComTXorRX_Sign == TX_COM_MODE) {		/** 送信時 */
		SYS_FIP_ComBaudRate = TxBaudRate;				/** 送信ボーレイト */
		SYS_FIP_TotalPage = SYS_TxTotalPage;			/** 送信ページ */
	}
	else {										/** 受信時 */
		SYS_FIP_ComBaudRate = RxBaudRate;				/** 受信ボーレイト */
		SYS_FIP_TotalPage = SYS_RxTotalPage;			/** 受信ページ */
	}
	SYS_FIP_ComTime = FaxComPeriod;						/** 通信時間 */
	SYS_FIP_ComResult = FaxComResult;					/** 通信結果 */
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
	SYS_InternalLineNumberSave = SYS_InternalLineNumber;	/* ジャーナル用に待避しておきます by T.Soneoka 1998/03/11 */
#endif

	/*-------------------*/
	/** リレー関係初期化 */
	/*-------------------*/
	FaxComRelaySetting();

#if (PRO_PRINTER_RX == ENABLE)
	if (PrinterRxPreOpenFlag == 1) {	/**	ロール紙機でプリンタのＰｒｅオープン済み	*/
		PRN_PostClose();			/**	プリンタポストクローズ	*/
	}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.2.26 K.Kawata */
	send_end_message = 0;
	if (PRN_Control.PrinterRxMode != PRINT_RX_CANCEL) {
		if (PRN_Control.PrinterRxMode != PRINT_RX_PROC) {
			if (!CHK_HANGUP_ALARM_AVAILABLE()) {	/** 1999.7.8 K.Kawata **/
				send_end_message = 1;
				snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
				rcv_msg( mbxno.FCM_Task, &FcomMsg );
			}
			PRN_PrintToStandby();
			PRN_ImagePrintEndClose();
			if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)) {
				PRN_MD9402_INT_Timing();
			}
		}
		if ((SYS_RxMemoryFileItem == NULL) && (CMN_CheckFaxComPrinterEnable() == TRUE)) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRINTER_BUSY);
		}
		SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_HIGH_TEMP;
		PRN_Control.PrinterRxMode = PRINT_RX_CANCEL;
		SYS_SCN_StopRequest = FALSE;
	}
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.7.8 K.Kawata */
	if (send_end_message == 0) {
#endif
		/*--------------------------*/
		/** ﾒｲﾝ･ﾀｽｸへ通信終了を通知 */
		/*--------------------------*/
		snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
		/*---------------------------*/
		/** ﾒｲﾝﾀｽｸからのﾒｯｾｰｼﾞを待つ */
		/*---------------------------*/
		rcv_msg( mbxno.FCM_Task, &FcomMsg );
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.7.8 K.Kawata */
	}
#endif
#if (PRO_FIP == ENABLE)
	SYS_FIP_Status &= ~FIP_DURING_RX;	/* Add By M.Tachibana 94/02/13 */
#endif

#if (PRO_REMOTE_FAX == ENABLE)
 #if (PRO_DRAM_BACKUP == ENABLE)
	SYS_RemoteFaxTxPerformingFlag = 0;		/* 1994/12/19 */
 #endif
#endif

	FaxComPerformingFlag = 0;		/** 通信中フラグクリア */

	SYS_FaxCommStage = 0;			/** 通信ディスプレイ用クリア */

	/*------------------------------------------------------------*/
	/** マシーンステータス(SYS_MachineStatus)の通信停止情報クリア */
	/* 通信初期化時にクリアしているがここでもクリアせなあかん	  */
	/*------------------------------------------------------------*/
	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_FAXCOM;

	FCM_Is_ToneDetecting = YES;	/* for Debug 1997/09/11  By T.Yamaguchi */

	SYS_FaxCommStage = 0;							/* 通信遷移状態 *//* 1997/11/29 */

#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 1998/11/17 by T.Soneoka */
	if (tskno_SCN_STxStoreTask != 0xffff) {
		del_tsk(&tskno_SCN_STxStoreTask);
	}
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
	if (tskno_NCU_FaxComTelHookChkTask != 0xffff) {
		del_tsk(&tskno_NCU_FaxComTelHookChkTask);
	}
#endif

#if (PRO_MODEM == R288F)				/* ROCKWELL製 28.8K */
	/* モデム救済タスク起動 By O.Kimoto 1998/02/03 */
	if (tskno_MDM_ModemRecoverTask != 0xffff) {
		del_tsk(&tskno_MDM_ModemRecoverTask);
	}
#endif

	/*-----------------*/
	/** 通信タスク終了 */
	/*-----------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* モデム使用中かどうかの判断に使用します */
	tskno_FCM_Task = 0xffff;
#endif

	exi_tsk();						/** 通信タスク自滅 */

}	/* End of FCM_Task */
