/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMTXC.C													 */
/*	モジュール	 :															 */
/*				 : FaxTxPhaseC()											 */
/*				 : SetTxPageData()											 */
/*				 : CheckMinimumLineSize()									 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 : 送信側フェーズＣ											 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\syst30.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\sysscan.h"

#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\message.h"

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */
#include	"\src\atlanta\ext_v\bkupram.h"	/* 1996/07/25 By N.Sakamoto */

#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\define\def_tib.h" /* By S.Kawsaki 1996/03/07 */

#if (PRO_COM_CODEC_TYPE == MN86063)
	#include	"\src\atlanta\define\scn_pro.h"	/* For SCN_DecideReductionPattern(); Y.Suzuki Aug.25.1994 */
#endif

#include	"\src\atlanta\define\sysexec.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\fcm_data.h"

#include	"\src\atlanta\define\mntsw_b.h"	/* 96/08/14 add By T.Yamaguchi */
#if (PRO_SCN_CODEC_TYPE == IDP301)
#include	"\src\atlanta\define\idp_pro.h"	/* 96/08/14 add By T.Yamaguchi */
#include	"\src\atlanta\define\idp301.h"	/* 96/08/14 add By T.Yamaguchi */
#include	"\src\atlanta\define\idp_def.h"	/* 96/08/14 add By T.Yamaguchi */
#include	"\src\atlanta\define\std.h"		/* 96/08/14 add By T.Yamaguchi */
#endif

#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE)  96/1/11 Y.S */
#include	"\src\atlanta\scd\define\scdpro.h"
#endif /* 96/1/11 Y.S */

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

#include	"\src\atlanta\define\scn_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"

/* test 1997/12/09 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
#include	"\src\atlanta\ext_v\scn_data.h"
#endif

#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1998/01/19 */
#include "\src\atlanta\ext_v\lst_data.h"
 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* 不達通知に蓄積原稿をつける場合 added by H.Kubo 1998/12/18 */
#include "\src\atlanta\ext_v\cdc_data.h"
 #endif
#endif

#if (PRO_SCN_CODEC_TYPE == SOFTWARE) /* added by H.Hirao 1998/10/29 */
 #if defined(SATSUKI2)  /* 他の機種との共用ソースなのでSATSUKI2で切ります。O.Oshima 2003/11/07 Smuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
 #elif defined(STOCKHM2)
#include "\src\atlanta\stockhm2\ext_v\scn_dath.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
 #endif
#endif
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/12/18 */
/* POPLAR_H では、コードサイズを小さくする最適化コンパイルをしますが、
** そのままだと大量のスタックを消費します。そこで以下の #pragma によって
** 関数先頭での不要なレジスタ待避をさけます。
** (SuperH RISC engine ファミリ C コンパイラ編 2-34 参照)
** 1997/12/18 H.Kubo 
*/
#pragma noregalloc(FaxTxPhaseC)
#endif /* (PRO_MODEM == R288F) */


/************************************************************************
	module		:[送信フェーズＣ]
	function	:[
		以下の処理を１通信分繰り返す
		(送信終了，モード変更，ＲＣＲ要求でフェーズＢに戻る)
		1.	画データ送信を起動する
		2.	送信フェーズＤを起動する
	]
	return		:[なし]
	common		:[
		FaxComPhaseStatus		FaxComPerformingFlag
		TxModeChangedFlag		TxRetrainingFlag
		SYS_FaxComTxType		TxPageDataSetFlag
		TxPageFinishStatus
		TxSmType				TxBaudRate
		*SYS_CurrentExecutingCommand	:現在実行中のキューのポインタ
		SYS_MachineStatus[SYS_SENSOR_STATUS] & SYS_SENSOR_DS1_ON	:原稿有無チェック
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/12]
	author		:[竹内茂樹]
************************************************************************/
void	FaxTxPhaseC( void )
{
#if (PRO_MODEM != R288F ) /* deleted by H.Kubo 1997/12/15 */
	WORD	timer;
#endif /* (PRO_MODEM != R288F ) */

	UBYTE	is_scn_page_start = 0;		/* 1996/08/13 By N.Sakamoto */

	FaxComPhaseStatus = FAX_TX_PH_C_BEFORE_PIX;

	/**	ページオープンのフラグを初期化	*/
	TxPageDataSetFlag	= 0;

	/* コーデックステータスを初期化 Aug.18.1994 */
	CodecPageStatus = CDC_READY;

	while ((FaxComPerformingFlag == 1)
	&&	   (TxModeChangedFlag == 0)
	&&	   ((SYS_FaxComStopSwitch() == 0)
		 || (TxPageFinishStatus == TX_BLOCK_END))	/* ﾌﾞﾛｯｸｴﾝﾄﾞのときｽﾄｯﾌﾟｷｰを押すと通信エラーになるため条件追加 96/07/02 By T.Yamaguchi */
	&&	   (TxRetrainingFlag == 0)) {	/** 通信中&&モード変更なし&&ストップ入力なし&&再トレーニングなし	*/

		/*----------------------*/
		/*	ページデータセット	*/
		/*----------------------*/
		if (TxPageDataSetFlag == 0) {	/**	送信ページデータ未セット	*/
			SetTxPageData();	/**	送信ページデータセット	*/

			/**	表示切替指示(画データ送信中)	*/
			SYS_FaxCommStage = FCM_TRANSMIT_SET;		/* May.30.1994 */
			SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );	/* Nov.01.1994 */
		}

/* #if(PRO_COM_CODEC_TYPE == MN86063) /@ 桐ｽｷｬﾅｰ送信縮小処理のため 1994/11/9 Y.Suzuki */
		if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
			SCN_DecideReductionPattern();
		}
/* #endif */
		if (FaxComPerformingFlag == 1) {		/** 通信中	*/

			if (SYS_V34ProcedureExecuting() == 0) {  /* Added by H.Kubo */
				/**	ＣＦＲ－ＰＩＸ間のウェイト	*/
				/*------------------------------------------------------*/
				/*	通常			:	７５ms							*/
				/*	Ｔ．４．１対策	:	メモリスイッチＢ７(10ms単位)	*/
				/*------------------------------------------------------*/
#if (PRO_MODEM != R288F ) /* Changed by H.Kubo 1997/12/15 R288F のドライバはスタックを食うので、無駄にスタックを使わないため。*/
				timer = (UWORD)(FCM_PtnrCHK_T41CFR_AfterPIX() * 10);
				FaxTimer( timer );
#else /* (PRO_MODEM != R288F ) */
				FaxTimer(  (UWORD)(FCM_PtnrCHK_T41CFR_AfterPIX() * 10) );
#endif /* (PRO_MODEM != R288F ) */

#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
				if (CHK_DisasterPreventionFaxEnable()) {
					if (SYS_MemorySwitch[MEMORY_SW_B8]) {
						timer = (UWORD)(SYS_MemorySwitch[MEMORY_SW_B8]*10);	/* SYS_MemorySwitch[MEMORY_SW_B8] */
					}
					FaxTimer( timer );
				}
#endif	/* End of (PRO_DISASTER_PREVENTION_FAX == ENABLE) */

			} /* end of (SYS_V34ProcedureExecuting() == 0) */
		
			/** Ｔ３０モニタ用データセット	*/
			SaveT30TimingData( SYS_T30_START_TIME );
			SaveT30Data( SYS_T30_TX_PIX, &MDM_ModemBuffer[0][0], 0 );

			FaxComPhaseStatus = FAX_TX_PH_C_PIX;
#if (0) /* SCN_Open の中でセットしているので削除  T.Nose 1997/06/17 */
			/*----------------------------------------------------------*/
			/* 読取開始・終了ステップ数セット(１頁目と２頁目以降で区別) */
			/*								1996/07/25	  By N.Sakamoto */
			/*----------------------------------------------------------*/
#endif
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/04 */
			/*-----------------------------------------------*/
			/** コントロールチャネルｔｕｒｎ－ｏｆｆ         */
			/*  連続「１」を送信し相手機からの無音を受信する */
			/*-----------------------------------------------*/
			if (SYS_V34ProcedureExecuting() == 1) {	/* CTC ONの時にﾘｰﾄﾞ 1996/03/04 */
				TxBaudRate = FCM_CheckTxDataRate();
			}
			if (FCM_ControlChanelTurnOff()) {
				FCM_SetTxDataRate();
			}
			else {	/* CFRを受信したが正常にﾌﾗｸﾞ終了（無音）を検出できなかった時 多分無いと思うけど・・*/
				/** 送信エラーセット */ /* T.3.2でも新規追加しましょうか？ */
				TransmitError(0x32,1);
				/**	フェーズＥ（ＤＣＮ送出，回線断）	*/
				FaxPhaseE( 1 );
				break;
			}
#endif /* (PRO_TX_SPEED == V34) */

			/*--------------------------------------*/
			/**	画データ送信（オープン，クローズ）	*/
			/*--------------------------------------*/
			MDM_TxPixOpen( TxBaudRate, TxECM_Mode );

/*==== V34 ====*/
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/04 */
			/* 1996/05/17 Y.Murata
			 * PixOpen でｱﾎﾞｰﾄの時は強制的に抜け、TxPageFinishStatusにｵｰﾌﾟﾝｴﾗｰをｾｯﾄする
			*/
			if (FCM_CheckModemAbort() == 0) {

 #if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
				if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {
					/* ソフトコーデックＧ３，ＥＣＭ送信 */
					TxPageFinishStatus = SCDC_TxPix( TxECM_Mode, TxSmType );
				}
				else {
					TxPageFinishStatus = MDM_TxPix( TxECM_Mode, TxSmType );
				}
 #else /* 96/1/11 Y.S */
				TxPageFinishStatus = MDM_TxPix( TxECM_Mode, TxSmType );
 #endif /* 96/1/11 Y.S */
				MDM_TxPixClose( TxECM_Mode );

				FaxComPhaseStatus = FAX_TX_PH_C_AFTER_PIX;	/* Jun.29.1994 */
				/*-----  プライマリチャネルｔｕｒｎ－ｏｆｆ ---- */
				FCM_PrimaryChanelTurnOff();

				/*--------------------------------------------------*/
				/*	画データ送信結果が「１ページ送信終了」の場合は	*/
				/*	次ページがある可能性があるので，再度セットする	*/
				/*--------------------------------------------------*/
				FCM_TxEndSet();	/* 送信データが残っているか判断する */

				FaxComPhaseStatus = FAX_TX_PH_D;

 #if (0)
**				/* 1997/08/12 Y.Murata
**				** ＰＩＸ－ＥＯＰ間の信号間タイミングが現状270msなので70±20msになるよう調整します
**				*/
**				/**	ＰＩＸ－ポストメッセージ間のウェイト（９０ms）	*/
**				if (SYS_V34ProcedureExecuting() == 0) {
**					FaxTimer( 90 );
**				}
 #endif

			} /* end of if (FCM_CheckModemAbort() == 0) */
			else {	/* CTS Abort */
				TxPageFinishStatus = TX_PIX_OPEN_ERR;
				MDM_TxPixClose( TxECM_Mode );	/* 1996/09/10 Y.M */
			}
#else /* (PRO_TX_SPEED == V34) */
/*==== V17 ====*/
 #if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
			if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {
				/* ソフトコーデックＧ３，ＥＣＭ送信 */
				TxPageFinishStatus = SCDC_TxPix( TxECM_Mode, TxSmType );
			}
			else {
				TxPageFinishStatus = MDM_TxPix( TxECM_Mode, TxSmType );

	/* test 1997/12/09 */
  #if (PRO_KEYPANEL == PANEL_ANZU_L)
				if (TxPageFinishStatus == TX_STOPPED) {
					SCN_DocumentStatus = SCN_DOC_END_OF_SCAN;
				}
  #endif
			}
 #else /* 96/1/11 Y.S */
			TxPageFinishStatus = MDM_TxPix( TxECM_Mode, TxSmType );
 #endif /* 96/1/11 Y.S */
			MDM_TxPixClose( TxECM_Mode );

			FaxComPhaseStatus = FAX_TX_PH_C_AFTER_PIX;	/* Jun.29.1994 */

			/*--------------------------------------------------*/
			/*	画データ送信結果が「１ページ送信終了」の場合は	*/
			/*	次ページがある可能性があるので，再度セットする	*/
			/*--------------------------------------------------*/
			FCM_TxEndSet();	/* 送信データが残っているか判断する */

			FaxComPhaseStatus = FAX_TX_PH_D;

			/**	ＰＩＸ－ポストメッセージ間のウェイト（９０ms）	*/
			FaxTimer( 80 );			/* 90 --> 80  by M.HARADA 27 Nov 97 */
#endif /* (PRO_TX_SPEED == V34) */
/*==== end of V33 ====*/
			if (MDM_PhaseC_Status == TX_DOC_ERR) { /* 原稿エラーの時、ランプ消灯 T.Nose 1997/09/20 */
				LampOff();
			}

			/*------------------*/
			/**	送信フェーズＤ	*/
			/*------------------*/
			FaxTxPhaseD();
		}
		else {		/**	回線断	*/
			/**	フェーズＥ（ＤＣＮ送出，回線断）	*/
			FaxPhaseE( 1 );
		}

		/*-----------------------------------------------------------------
		** 原稿排出＋次原稿繰り込み処理
		** MOMIJIから移植した
		** 1998/08/25 H.Yoshikawa
		*/
#if (PRO_SCN_CLUTCH == ENABLE) /*(PRO_SCN_CODEC_TYPE == IDP301)*/ /* スキャナクラッチ有りの場合 by H.Hirao 1998/11/19 */
  /*
  ** スキャナをクローズする時にtskno_SCN_STxStoreTaskを消しときたい
  ** HINOKIだけの処理です by H.Hirao 1998/11/19
  */
  #if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		if (TxSmType == TX_SCAN) {	/**	スキャナ送信	*/
			if (!FaxComPerformingFlag || ((TxPageFinishStatus != TX_BLOCK_END) && (TxPageFinishStatus != TX_SEPARATE) && (TxPageFinishStatus != TX_PAGE_END) && (TxPageFinishStatus != TX_PAGE_END_MODE_CHANGE))) {
				if (tskno_SCN_STxStoreTask != 0xffff) {
					del_tsk(&tskno_SCN_STxStoreTask);
				}
/*
** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
** 1999/02/01 by T.Soneoka
*/
#if (0)
**				SCN_Close((UBYTE)0);
#else
				SCN_Close((UBYTE)FROM_FAXCOM);
#endif
			}
		}
  #else
		if (TxSmType == TX_SCAN) {	/**	スキャナ送信	*/
			if ((TxPageFinishStatus != TX_BLOCK_END) && (TxPageFinishStatus != TX_SEPARATE)) {	/**	１ページ終了 */
				SCN_Close((UBYTE)0);
			}
		}
  #endif
#endif

		if ((SYS_FaxComType == SYS_COMMAND_EXECUTE)
		&&	(TxSmType == TX_CVR)
		&&	(TxCoverPageFlag == 0)) {	/**	カバーページ送信完了	*/
			/*----------------------------------------------------------------------*/
			/*	カバーページ送信ＯＫならTxSmTypeはTX_CVRのままでTxCoverPageFlagは	*/
			/*	フェーズＤでクリアされるので，この条件でいいはず					*/
			/*----------------------------------------------------------------------*/
			/**	コマンドキューのカバーページ送信ビットをセット	*/
			SYS_CurrentExecutingCommand->Option |= SYS_COVER_PAGE;
		}
	}

	/*--------------------------------------------------------------*/
	/*	部分ページエンドでデコード中のまま手順に戻ってきた場合に	*/
	/*	ポストメッセージハンドシェークで異常終了した時の処理		*/
	/*--------------------------------------------------------------*/
	if ((TxPageFinishStatus == TX_BLOCK_END) || (TxPageFinishStatus == TX_SEPARATE)) {	/**	ブロックエンド||Ａ４の２枚分に達した	*/
		/* ↑「ストップなし」の条件を削除 Aug.20.1994 */
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE) 96/1/11 Y.S */
		if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {
			SCDC_BreakTxTask();	/**	ＥＣＭタスク終了	*/
		}
		else {
			MDM_BreakTxTask();
		}
#else /* 96/1/11 Y.S */
		MDM_BreakTxTask();	/**	ＥＣＭタスク終了	*/
#endif /* 96/1/11 Y.S */

		/*-----------------------------------------------------------------
		** MOMIJIから移植した
		** 1998/08/25 H.Yoshikawa
		*/
#if (PRO_SCN_CLUTCH == ENABLE) /*(PRO_SCN_CODEC_TYPE == IDP301)*/ /* スキャナクラッチ有りの場合 by H.Hirao 1998/11/19 */
  /*
  ** スキャナをクローズする時にtskno_SCN_STxStoreTaskを消しときたい
  ** HINOKIだけの処理です by H.Hirao 1998/11/19
  */
  #if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		if ((TxSmType == TX_SCAN) && (FaxComPerformingFlag == 0)) {
			if (tskno_SCN_STxStoreTask != 0xffff) {
				del_tsk(&tskno_SCN_STxStoreTask);
			}
/*
** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
** 1999/02/01 by T.Soneoka
*/
#if (0)
**			SCN_Close((UBYTE)0);
#else
			SCN_Close((UBYTE)FROM_FAXCOM);
#endif
		}

  #else
		/*----------------------------------------------------------*/
		/**	スキャナ送信のページ途中(TX_BLOCK_END / TX_SEPARATE)で	**
		***	エラーした場合にスキャナをクローズする					*/
		/*----------------------------------------------------------*/
		if ((TxSmType == TX_SCAN) && (FaxComPerformingFlag == 0)) {
			SCN_Close((UBYTE)0);
		}
  #endif
#endif
	}
}


/************************************************************************
	module		:[送信ページデータセット]
	function	:[
		1.	送信原稿タイプをセットする
		.	(TX_SCAN/TX_MEMORY/TX_RCR/TX_CVR)
		2.	送信原稿制御ブロックにパラメータをセットする
		.	1)	送信ページ
		.	2)	独自モード符号化方式
		.	3)	１ページ最大ライン数
		.	4)	最少１ラインバイト長
		3.	データセット済みフラグをセットする
	]
	return		:[なし]
	common		:[
		SYS_FaxComTxType		TxSmType
		TxBaudRate				TxMinimumScanningTime
		TxMSE_Method			TxMemoryFilePage
		TxCoverPageOpenFlag		TxRCR_Flag
		TxPageDataSetFlag		FaxTxMaxLength
		SYS_DocBlock
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/12]
	author		:[竹内茂樹]
************************************************************************/
void	SetTxPageData( void )
{
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/04 */
	if (SYS_V34ProcedureExecuting() == 1) {
		TxBaudRate = FCM_CheckTxDataRate();
	}
#endif /* (PRO_TX_SPEED == V34) */
	/*----------------------------------*/
	/*	送信原稿種別(TxSmType)をセット	*/
	/*----------------------------------*/
	/* ●ICHOU追加 by T.Soneoka 1996/06/18 */
	if (SYS_FaxComType == SYS_REMOTE_DIAG) {
		TxSmType = TX_BKUPRAM;
	}
	else {
		if (TxRCR_Flag == 1) {				/**	受領証送信フラグＯＮ	*/
			TxSmType = TX_RCR;				/**	受領証	*/
		}
#if (PRO_REMOTE_FAX == ENABLE)	/* Jun.24.1994 */
		else if (TxRemoteFaxCheckMsgFlag == 1) {
			TxSmType = TX_REMOTE_FAX_MSG;	/**	リモートＦＡＸチェックメッセージ	*/
		}
#endif
		else {
			if (TxCoverPageFlag == 1) {		/**	カバーページ送信フラグＯＮ	*/
				TxSmType = TX_CVR;			/**	カバーページ	*/
			}
			else {
				if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {	/**	スキャナ送信（自動／手動）	*/
					TxSmType = TX_SCAN;		/**	スキャナ送信原稿	*/
				}
#if (PRO_RELAYED_REPORT == ENABLE) /* H.Kubo 1998/01/19 */
 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
				else if (CommandFileOptionItem == SYS_RELAYED_TX_REPORT) {
					TxSmType = TX_RELAYED_TX_REPORT;
				}
 #else
				else if (CommandFileOptionItem == SYS_RELAYED_TX_REPORT 
						&& LST_TxPageFinishStatus != TX_END) {
					TxSmType = TX_RELAYED_TX_REPORT;
				}
 #endif
#endif /* (PRO_RELAYED_REPORT == ENABLE) */
				else {						/**	メモリ送信	*/
					TxSmType = TX_MEMORY;	/**	メモリ送信原稿	*/
				}
			}
		}
	}

	if (TxSmType == TX_MEMORY) {	/**	メモリ送信原稿	*/
		/**	原稿制御ブロックに送信ページをセット	*/
		SYS_DocBlock.Index.Page = TxMemoryFilePage;
	}

	/*----------------------------------------------------
	コンパチチェックSetTxMSE_Mode()で設定されるから，いらない
	%**	原稿制御ブロックに独自モード符号化方式をセット	*%
	SYS_DocBlock.MSE_Method = TxMSE_Method;
	----------------------------------------------------*/

	/**	原稿制御ブロックに最少１ラインバイト長をセット	*/
	SYS_DocBlock.MinimumLineSize = CheckMinimumLineSize( TxMinimumScanningTime, TxBaudRate );

	/**	原稿制御ブロックに最大原稿長をセット	*/
	switch (FaxTxMaxLength) {
	case	SYS_A4_LENGTH:
		SYS_DocBlock.DocLength = SYS_A4_PAGE_LENGTH;
		break;
	case	SYS_B4_LENGTH:
		SYS_DocBlock.DocLength = SYS_B4_PAGE_LENGTH;
		break;
	case	SYS_A3_LENGTH:
		SYS_DocBlock.DocLength = SYS_A3_PAGE_LENGTH;
		break;
	case	SYS_NO_LIMIT:
	default:
		if (CHK_F_NetSubscriber() != 0) {	/**	Ｆ網設定	*/
			SYS_DocBlock.DocLength = SYS_A4_2PAGE_LENGTH;	/**	Ａ４×２	*/
			/*	日本仕様以外で 0 以外(Ｆ網加入)が返ってきた場合は，知らない ^^;	*/
			/*	勝手にメモリスイッチを変えた人が悪い!!							*/
		}
		else {
			SYS_DocBlock.DocLength = SYS_NO_LIMIT_PAGE_LENGTH;	/**	無制限	*/
		}
		break;
	}
#if 0 /* defined(FRA) */	/* del by M.HARADA '96/11/15 */
	/**	送信原稿長を＋５％する	*/
	SYS_DocBlock.DocLength = (SYS_DocBlock.DocLength * 105) / 100;
#endif

	/* Fine→Gray / Gray→Fine の場合に表示とジャーナルでモードが変わらなかった	 Oct.28.1994 */
	switch (SYS_DocBlock.Src.Mode) {
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
	case	SYS_GRAY128:
	case	SYS_GRAY128_SEP:
		GrayModeFlag = 1;
		break;
	default:
		GrayModeFlag = 0;
		break;
	}

	/** データセット済みフラグをセット	*/
	TxPageDataSetFlag = 1;
}


/*************************************************************************
	module		:[最少１ラインバイト長を決定]
	function	:[
		１ライン最少伝送時間とボーレイトから，最少１ラインバイト長を決定する
		POPLAR変更
		計算の値が小数点以下の場合は切り上げる処理を追加 1997/07/15  By T.Yamaguchi
		計算方法
		 ex. 7200BPSの場合
		  7200b/s ÷ 8bit × (最少伝送時間ms/1000ms)
		  7200bps/8bit ÷ 5ms/1000ms = 4.5Byte
		  切り上げて5Byteがreturn値になる
	]
	return		:[
		最少１ラインバイト長
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/27]
	author		:[竹内茂樹]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UWORD		CheckMinimumLineSizeFlsRom(
	UBYTE	min_scan_time,		/*	最少伝送時間	*/
	UBYTE	baudrate )			/*	ボーレイト	*/
#else
UWORD		CheckMinimumLineSize(
	UBYTE	min_scan_time,		/*	最少伝送時間	*/
	UBYTE	baudrate )			/*	ボーレイト	*/
#endif
{
	UWORD	tmp_scan_time = 0;
	UWORD	min_line_size = 0;

	/*------------------------------------------*/
	/*	１ライン最少伝送時間とボーレイトから	*/
	/*	最少１ラインバイト長を決定する			*/
	/*------------------------------------------*/
	switch (min_scan_time) {
	case	SCAN_MINIMUM_TIME20:
	case	SCAN_MINIMUM_TIME20_2:
		tmp_scan_time = 20;
		break;
	case	SCAN_MINIMUM_TIME40:
	case	SCAN_MINIMUM_TIME40_2:
		tmp_scan_time = 40;
		break;
	case	SCAN_MINIMUM_TIME10:
	case	SCAN_MINIMUM_TIME10_2:
		tmp_scan_time = 10;
		break;
	case	SCAN_MINIMUM_TIME5:
		tmp_scan_time = 5;
		break;
	case	SCAN_MINIMUM_TIME0:
		tmp_scan_time = 0;
		break;
	}

	switch (baudrate) {
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/04 */
	case	BPS33600_V34:
		min_line_size = (tmp_scan_time * 21) / 5;
		break;
	case	BPS31200_V34:
		min_line_size = (tmp_scan_time * 39) / 10;
		break;
	case	BPS28800_V34:
		min_line_size = (tmp_scan_time * 18) / 5;
		break;
	case	BPS26400_V34:
		min_line_size = (tmp_scan_time * 33) / 10;
		break;
	case	BPS24000_V34:
		min_line_size = (tmp_scan_time * 3) / 1;
		break;
	case	BPS21600_V34:
		min_line_size = (tmp_scan_time * 27) / 10;
		break;
	case	BPS19200_V34:
		min_line_size = (tmp_scan_time * 12) / 5;
		break;
	case	BPS16800_V34:
		min_line_size = (tmp_scan_time * 21) / 10;
		break;
	case	BPS14400_V34:
	case	BPS14400_V17:
	case	BPS14400_V33:
		min_line_size = (tmp_scan_time * 9) / 5;
		break;
	case	BPS12000_V34:
	case	BPS12000_V17:
	case	BPS12000_V33:
		min_line_size = (tmp_scan_time * 3) / 2;
		/* 最少伝送時間の計算で小数点以下の値がでる場合に切り上げる1997/07/15  By T.Yamaguchi */
		if ((tmp_scan_time * 3) % 2){
			min_line_size++;
		}
		break;
	case	BPS9600_V34:
	case	BPS9600_V17:
	case	BPS9600_V29:
		min_line_size = (tmp_scan_time * 6) / 5;
		break;
	case	BPS7200_V34:
	case	BPS7200_V17:
	case	BPS7200_V29:
		min_line_size = (tmp_scan_time * 9) / 10;
		/* 最少伝送時間の計算で小数点以下の値がでる場合に切り上げる1997/07/15  By T.Yamaguchi */
		if ((tmp_scan_time * 9) % 10){
			min_line_size++;
		}
		break;
	case	BPS4800_V34:
	case	BPS4800_V27:
		min_line_size = (tmp_scan_time * 3) / 5;
		break;
	case	BPS2400_V34:
	case	BPS2400_V27:
		min_line_size = (tmp_scan_time * 3) / 10;
		/* 最少伝送時間の計算で小数点以下の値がでる場合に切り上げる1997/07/15  By T.Yamaguchi */
		if ((tmp_scan_time * 3) % 10){
			min_line_size++;
		}
		break;
#else /* (PRO_TX_SPEED == V34) */
	case	BPS14400_V17:
	case	BPS14400_V33:
		min_line_size = (tmp_scan_time * 9) / 5;
		break;
	case	BPS12000_V17:
	case	BPS12000_V33:
		min_line_size = (tmp_scan_time * 3) / 2;
		/* 最少伝送時間の計算で小数点以下の値がでる場合に切り上げる1997/07/15  By T.Yamaguchi */
		if ((tmp_scan_time * 3) % 2){
			min_line_size++;
		}
		break;
	case	BPS9600_V17:
	case	BPS9600_V29:
		min_line_size = (tmp_scan_time * 6) / 5;
		break;
	case	BPS7200_V17:
	case	BPS7200_V29:
		min_line_size = (tmp_scan_time * 9) / 10;
		/* 最少伝送時間の計算で小数点以下の値がでる場合に切り上げる1997/07/15  By T.Yamaguchi */
		if ((tmp_scan_time * 9) % 10){
			min_line_size++;
		}
		break;
	case	BPS4800_V27:
		min_line_size = (tmp_scan_time * 3) / 5;
		break;
	case	BPS2400_V27:
		min_line_size = (tmp_scan_time * 3) / 10;
		/* 最少伝送時間の計算で小数点以下の値がでる場合に切り上げる1997/07/15  By T.Yamaguchi */
		if ((tmp_scan_time * 3) % 10){
			min_line_size++;
		}
		break;
#endif /* (PRO_TX_SPEED == V34) */
	}

	return (min_line_size);
}


/*************************************************************************
	module		:[送信原稿が最終のページ]
	function	:[
		送信原稿が最終のページかどうか判断して、画データ送信結果を「送信完了」をセットする
				TxPageFinishStatus = TX_END;
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/12/04]
	author		:[山口 哲治]
*************************************************************************/
void FCM_TxEndSet(void)
{
	UBYTE debug_sw;	/* 1997/05/08  By T.Yamaguchi */

	debug_sw = 0;
	
	if (TxPageFinishStatus == TX_PAGE_END) {	/**	画データ送信結果が「１ページ送信終了」	*/
		if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {	/**	スキャナ送信（自動／手動）	*/
#if (PRO_FBS == ENABLE) /* FBSからのスキャナー送信の場合は連続ページ送信なし T.Nose 1997/10/13 */
			if (!CMN_CheckDS1Status() /**	フィーダーの残り原稿なし	*/
			 || (SYS_ScannerExecMode == SCN_FBS))
#else

 #if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
			/* 仕様変更
			** 読み取り中において、ＤＳ２がＯＦＦした時点でＤＳ１もＯＦＦしていれば、今読んだ原稿が
			** 最終原稿であるという風に変更
			** by O.kimoto 1999/03/08
			*/
			if ((NoNextDocument == TRUE) || (!CMN_CheckDS1Status())) /**	フィーダーの残り原稿なし	*/
 #else
			if (!CMN_CheckDS1Status()) /**	フィーダーの残り原稿なし	*/
 #endif
#endif
			{
				/**	画データ送信結果を「送信完了」に変更	*/
				TxPageFinishStatus = TX_END;
			}
		}
		else {										/**	各種メモリ送信	*/
			if ((TxMemoryFileItem == SYS_MEM_POLLING_FILE)
			||	(TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE)
			||	((TxMemoryFileItem >= SYS_MEM_BATCH_TX_FILE1) && (TxMemoryFileItem <= SYS_MEM_BATCH_TX_FILE5))
			||	(RxDocumentPollingTxFlag != 0)) {	/**	ポーリング送信||ＤＢポーリング送信||バッチ送信||受信原稿ポーリング送信	*/
				/* ↑バッチ送信の条件を追加 Aug.20.1994 */
				if (TxMemoryFilePage >= PollingTxFilePage[TxMemoryFileCurrentExecutingNo]) {	/**	現ページ≧ポーリング送信要求ページ	*/
					/**	画データ送信結果を「送信完了」に変更	*/
					TxPageFinishStatus = TX_END;
				}
			}
			else if ((TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)	/*	掲示板ﾎﾟｰﾘﾝｸﾞ原稿 */
			  ||	 (TxMemoryFileItem == SYS_MEM_SUB_SECURE_FILE)) {	/* Fｺｰﾄﾞ親展原稿 ﾎﾟｰﾘﾝｸﾞできる場合 */

				if (TxMemoryFilePage >= PollingTxFilePage[TxMemoryFileCurrentExecutingNo]) {	/**	現ページ≧ポーリング送信要求ページ	*/
					if (!(SYB_MaintenanceSwitch[MNT_SW_B4] & FCODE_POLLING_TX_METHOD))	{	/* ﾒﾝﾃﾅﾝｽSWB4-2 */
						if (TxMemoryFileNo[TxMemoryFileCurrentExecutingNo+1] != 0xffff) {	/**	次ファイルあり	*/
							TxMemoryFileNextExecutingNo++;	/**	次回送信予定「ファイル番号」格納配列を更新	*/
							TxPageFinishStatus = TX_NEXT_FILE;
						}
						else {	/* ファイル最終原稿 */
							TxPageFinishStatus = TX_END;
						}
					}
					else {
						TxPageFinishStatus = TX_END;
					}
				}
			}
			else {				/**	ポーリング送信||バッチ送信以外のメモリ送信	*/
				if (TxSmType == TX_RCR) {	/**	受領証送信	*/
					/**	画データ送信結果を「送信完了」に変更	*/
					TxPageFinishStatus = TX_END;
				}
				/* ●ICHOU追加 高速ＲＤＳデータリード by T.Soneoka 1996/06/18 */
				else if (TxSmType == TX_BKUPRAM) {
					TxPageFinishStatus = TX_END;
				}
#if (PRO_REMOTE_FAX == ENABLE)	/* Jul.05.1994 */
				if (TxSmType == TX_REMOTE_FAX_MSG) {	/**	リモートＦＡＸチェックメッセージ送信した	*/
					/**	画データ送信結果を「送信完了」に変更	*/
					TxPageFinishStatus = TX_END;
				}
#endif
				else if (TxSmType == TX_MEMORY) {	/**	メモリ送信	*/
#if (0) /* ICHOU変更 送信最適化処理 by T.Soneoka 1996/10/01 */
//					if ((TxMemoryFilePage >= MEM_CountTotalPage( TxMemoryFileItem, TxMemoryFileNo[TxMemoryFileCurrentExecutingNo], TxMemoryFileBoxNumber ))	/**	現ページ≧送信要求蓄積ページ	*/
//					 && (MEM_CountTotalPage( TxMemoryFileItem, TxMemoryFileNo[TxMemoryFileCurrentExecutingNo], TxMemoryFileBoxNumber ) != MEM_NO_INDEX)) {
//						/**	画データ送信結果を「送信完了」に変更	*/
//						TxPageFinishStatus = TX_END;
//					}
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/14 Y.Murata for KAKI */
					if (SYS_CurrentExecutingCommand->Kind == SYS_COMMAND_TRX) {
						if (CheckNextPage() == 0) {
							/**	画データ送信結果を「送信完了」に変更	*/
							TxPageFinishStatus = TX_END;
						}
					}
					else {
						if ((TxMemoryFilePage >= TxFinalPageNumber) && (TxFinalPageNumber != MEM_NO_INDEX))   {
							/**	画データ送信結果を「送信完了」に変更	*/
							TxPageFinishStatus = TX_END;
						}
					}
#else
					if ((TxMemoryFilePage >= TxFinalPageNumber) && (TxFinalPageNumber != MEM_NO_INDEX))   {
					/**	画データ送信結果を「送信完了」に変更	*/
						TxPageFinishStatus = TX_END;
					}
 #if 0 /* (PRO_RELAYED_REPORT == ENABLE)*/	/* 中継配信不達通知のため  竹内 Feb.14.1995 */
					/* 条件変更↓(CommandFileOptionItem == SYS_RELAYED_TX_REPORT)  Apr.27.1995 */
					else if (TxRelayReport) {	/**	不達通知は１ページ目だけ送信	*/
						/**	画データ送信結果を「送信完了」に変更	*/
						TxPageFinishStatus = TX_END;
					}
 #endif
#endif
				}
#if (PRO_RELAYED_REPORT == ENABLE) /* 中継配信不達通知のため  H.Kubo 1998/01/19 */
				else if (TxSmType == TX_RELAYED_TX_REPORT) {
#if (PRO_LIST_TX_WITH_IMG == ENABLE) /* 不達通知に蓄積原稿をつける場合 added by H.Kubo 1998/12/16 */
					if (LST_TxPageFinishStatus == TX_END) {
						if ((CDC_ReadPageCount >= 1) && (TxFinalPageNumber != MEM_NO_INDEX))   { /* 画データ１ページつけたら */
							/**	画データ送信結果を「送信完了」に変更	*/
							TxPageFinishStatus = TX_END;
						}
					}
#else
					/**	LST_RelayedTxReportImageTask で設定した値を使う。*/
					TxPageFinishStatus = LST_TxPageFinishStatus; /* */
					/* 画データを後に付けるなら、ここは要修正。*/
#endif
				}
#endif
				/*	カバーページ送信で「１ページ送信終了」の場合は，そのまま	*/
			}
		}
	}
}


#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/21 Y.Murata for KAKI */
UBYTE CheckNextPage(void)
{
	UBYTE	ret;
	struct MEM_IndexData_t index_data;

	ret = 0;

	/*
	 * 次に送信すべき原稿の有無をインデックを検索して判断する。
	 * インデック検索にはＲＩＳＣで最大７ｍｓ処理がかかるが問題ないと判断。
	 * INDEX MAX = 1024
	*/
	index_data.Item = TxMemoryFileItem;
	index_data.No = TxMemoryFileNo[TxMemoryFileCurrentExecutingNo];
	index_data.Page = (TxMemoryFilePage + 1);
	index_data.BoxNumber = TxMemoryFileBoxNumber;
	if (MEM_CheckIndexNo(&index_data) == MEM_NO_INDEX) {
		ret = 0;
	}
	else {
		ret = 1;
	}
	return(ret);
}

#endif
