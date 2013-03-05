/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMTXD.C													 */
/*	モジュール	 :															 */
/*				 : FaxTxPhaseD()											 */
/*				 : TxPostMessageHandshake()									 */
/*				 : AnalyzeReceivedPostMessage()								 */
/*	作成者		 : 山口														 */
/*	日	付		 :19996/11/19												 */
/*	概	要		 : 送信側フェーズＤ											 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\syst30.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\memsw\define\mem_sw_b.h" /*1996/04/17 Eguchi*/
#include	"\src\atlanta\define\sys_stat.h"

#include	"\src\atlanta\define\man_pro.h"
#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\define\mon_pro.h"

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#include	"\src\atlanta\sh7043\define\io_pro.h"

#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\fcm_data.h"

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

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mntsw_i.h"	/* 1997/09/10  By T.Yamaguchi */

#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1998/01/19 */
 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
	#include "\src\atlanta\ext_v\cdc_data.h"
 #endif
#endif

#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/12/18 */
/* POPLAR_H では、コードサイズを小さくする最適化コンパイルをしますが、
** そのままだと大量のスタックを消費します。そこで以下の #pragma によって
** 関数先頭での不要なレジスタ待避をさけます。
** 呼出し元で、#pragma noregalloc を宣言していることを確認してください。
** (SuperH RISC engine ファミリ C コンパイラ編 2-34 参照)
** 1997/12/18 H.Kubo 
*/
#pragma noregalloc(FaxTxPhaseD,TxPostMessageHandshake,AnalyzeReceivedPostMessage)
#endif /* (PRO_MODEM == R288F) */


/*************************************************************************
	module		:[送信フェーズＤ]
	function	:[
		1.	ＥＣＭ送信，会話予約キー入力を確認する
		2.	画データ送信の結果によってポストメッセージの
		.	フレームをセットし，ハンドシェークする
	]
	return		:[]
	common		:[
		TxECM_Mode			FaxComPerformingFlag
		TxFCF				TxOptionFCF
		ECM_FrameCounter	ECM_PageCounter		ECM_BlockCounter
		UpdateTxPageMode	UpdatePageInformationFlag
		FirstTxMode			DocWidth
		TxMemoryFilePage	TxPageFinishStatus
		SYS_VoiceSwitch		:会話予約キー入力フラグ
		MDM_EcmFrameNumber	:ＥＣＭフレーム数
	]
	condition	:[]
	comment		:[
		Apr.29.1995
		.	１ページエンコード完了後から命令送信までに
		.	停止キーが押された時もＴ．１．４エラーで
		.	送信を停止する(今まではＯＫになっていた)
		.	但しＥＣＭブロックエンドの場合は,停止キー
		.	は無視して,次ブロックで停止する
		Jul.19.1995 (沖からの要求→RICE共通)
		.	通信中止(StopSw)で相手機をエラー終了させる
		.	処理(MemorySwitch)を追加
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/18]
	author		:[竹内茂樹]
*************************************************************************/
void	FaxTxPhaseD( void )
{
	UpdatePageInformationFlag = 1;
	UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;

	/**	ＥＣＭ送信フレームカウンタにドライバのＥＣＭフレーム数をセット	*/
	ECM_FrameCounter = MDM_EcmFrameNumber;

	/**	送信ＦＣＦをクリア	*/
	TxOptionFCF = 0;
	TxFCF = 0;

	if (TxECM_Mode == ECM_ON) {		/**	ＥＣＭ通信	*/
		/**	ＥＣＭ用オプションＦＣＦにＰＰＳをセット	*/
		TxOptionFCF = PPS_F;
	}

#if defined (JPN)	/* 各国対応の為変更 by T.Soneoka 1997/07/26 */
#else	/*----	★日本仕様以外の場合★	----*/
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1998/01/08 */
	if (CMN_GetVoiceSwitch()) {		/**	会話予約キー入力ありかつ V34 でない*/
		/**	送信ＦＣＦのＰＲＩ－Ｑビットを立てる	*/
		TxFCF = PRI_Q_F;
	}
#else
	if (SYS_VoiceSwitch == 1) {		/**	会話予約キー入力あり	*/
		/**	送信ＦＣＦのＰＲＩ－Ｑビットを立てる	*/
		TxFCF = PRI_Q_F;
	}
#endif /* (PRO_TX_SPEED == V34) */
#endif

	/* メモリ送信最適化処理を実行する為、今送信したページを覚えておきます 1997/06/02  By T.Yamaguchi */
	EraseIndexData.Item = SYS_DocBlock.Index.Item;
	EraseIndexData.No   = SYS_DocBlock.Index.No;
	EraseIndexData.Page = SYS_DocBlock.Index.Page;
	EraseIndexData.BoxNumber = SYS_DocBlock.Index.BoxNumber;

	/**	フェーズＣの結果をフェーズＤ用に変換	*/
	TxPageFinishStatus = ResetTxPageFinishStatus();

	switch (TxPageFinishStatus) {		/**	画データ送信結果	*/

	/*--------------------------*/
	/*	ＥＣＭブロックエンド	*/
	/*--------------------------*/
	case	TX_BLOCK_END:		/**	ＥＣＭブロックエンド	*/
		TxFCF = NULL_FF;				/**	ＦＣＦにＮＵＬＬをセット	*/		/* Apr.29.1995 */
		ECM_FrameCounter = 0xFF;		/**	ＥＣＭフレームカウンタにＦＦをセット	*/
		TxPostMessageHandshake();	/**	ポストメッセージのハンドシェーク	*/
		ECM_BlockCounter++;			/**	ＥＣＭブロックカウンタを＋１	*/
		break;

	/*----------------------*/
	/*	原稿長制限オーバー	*/
	/*----------------------*/
	case	TX_SEPARATE:		/**	原稿長制限オーバー	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	ストップキー入力あり	*/
			TxFCF = EOP_F;				/**	ＦＣＦにＥＯＰをセット	*/
			FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
			TransmitError( 0x14, 1 );	/**	Ｔ．１．４をセット	*/	/* Apr.29.1995 */
		}
		else {
			/**	SYS_TxTotalPage と TxMemoryFilePage を更新するにセット	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;
			TxFCF |= MPS_F;				/**	ＦＣＦにＭＰＳを(orで)セット	*/
		}
		ECM_FrameCounter = MDM_EcmFrameNumber;	/**	ＥＣＭフレームカウンタにドライバのフレーム数をセット	*/
		TxPostMessageHandshake();	/**	ポストメッセージのハンドシェーク	*/
		ECM_PageCounter++;			/**	ＥＣＭページカウンタを＋１	*/
		ECM_BlockCounter = 0;		/**	ＥＣＭブロックカウンタを０クリア	*/
		break;

	/*----------------------------------*/
	/*	１ページ終了（モード変更なし）	*/
	/*----------------------------------*/
	case	TX_PAGE_END:		/**	１ページ終了（モード変更なし）	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	ストップキー入力あり	*/
			TxFCF = EOP_F;				/**	ＦＣＦにＥＯＰをセット	*/
			FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
			TransmitError( 0x14, 1 );	/**	Ｔ．１．４をセット	*/	/* Apr.29.1995 */
		}
		else {
			/**	SYS_TxTotalPage と TxMemoryFilePage を更新するにセット	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;
#if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
			if ((TxSmType == TX_RELAYED_TX_REPORT) && (CDC_ReadPageCount == 0)) {
				UpdateTxPageMode = UPDATE_TOTAL_PAGE;
			}
#endif
			TxPageDataSetFlag = 0;		/**	送信ページデータセット済みフラグをクリア	*/
			TxFCF |= MPS_F;				/**	ＦＣＦにＭＰＳを(orで)セット	*/
		}
		ECM_FrameCounter = MDM_EcmFrameNumber;	/**	ＥＣＭフレームカウンタにドライバのフレーム数をセット	*/
		TxPostMessageHandshake();	/**	ポストメッセージのハンドシェーク	*/
		ECM_PageCounter++;			/**	ＥＣＭページカウンタを＋１	*/
		ECM_BlockCounter = 0;		/**	ＥＣＭブロックカウンタを０クリア	*/
		if (UpdatePageInformationFlag == 1) {		/**	ページ番号更新が必要	*/
			UpdateTxPageInformation();				/**	送信ページ番号を更新	*/
		}
		else {
			GetNextTxPageData( TxMemoryFilePage );	/**	現ページのパラメータを再セット	*/
		}
		break;

	/*----------------------------------*/
	/*	１ページ終了，モード変更あり	*/
	/*----------------------------------*/
	case	TX_PAGE_END_MODE_CHANGE:	/**	１ページ終了，モード変更あり	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	ストップキー入力あり	*/
			TxFCF = EOP_F;				/**	ＦＣＦにＥＯＰをセット	*/
			FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
			TransmitError( 0x14, 1 );	/**	Ｔ．１．４をセット	*/	/* Apr.29.1995 */
		}
		else {
			/**	SYS_TxTotalPage と TxMemoryFilePage を更新するにセット	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;
#if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
			if ((TxSmType == TX_RELAYED_TX_REPORT) && (CDC_ReadPageCount == 0)) {
				UpdateTxPageMode = UPDATE_TOTAL_PAGE;
			}
#endif
			TxPageDataSetFlag = 0;		/**	送信ページデータセット済みフラグをクリア	*/
			TxFCF |= EOM_F;				/**	ＦＣＦにＥＯＭを(orで)セット	*/
			TxModeChangedFlag = 1;		/**	送信モード変更フラグをセット	*/
			TxRetrainingFlag = 1;		/**	再トレーニングフラグをセット	*/
		}
		ECM_FrameCounter = MDM_EcmFrameNumber;	/**	ＥＣＭフレームカウンタにドライバのフレーム数をセット	*/
		TxPostMessageHandshake();	/**	ポストメッセージのハンドシェーク	*/
		ECM_PageCounter++;			/**	ＥＣＭページカウンタを＋１	*/
		ECM_BlockCounter = 0;		/**	ＥＣＭブロックカウンタを０クリア	*/
		if (UpdatePageInformationFlag == 1) {	/**	ページ番号更新が必要	*/
			UpdateTxPageInformation();			/**	送信ページ番号を更新	*/
			if ((TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE)
			|| ((TxMemoryFileItem >= SYS_MEM_BATCH_TX_FILE1) && (TxMemoryFileItem <= SYS_MEM_BATCH_TX_FILE5))
#if (PRO_F_CODE == ENABLE)
			||	(TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)	/*	掲示板ﾎﾟｰﾘﾝｸﾞ原稿 */
			||	(TxMemoryFileItem == SYS_MEM_SUB_SECURE_FILE)	/* Fｺｰﾄﾞ親展原稿 ﾎﾟｰﾘﾝｸﾞできる場合 */
#endif
			||	(RxDocumentPollingTxFlag != 0)) {		/**	ＤＢポーリング送信||受信原稿ポーリング送信 || バッチ送信	*/
				/*----------------------------------------------------------*/
				/*	ＤＢ／受信原稿ポーリング送信では，送信モードとサイズを	*/
				/*	原稿制御ブロックより再度セットする						*/
				/*		(複数指定でファイル毎にモードが違う場合のため)		*/
				/*----------------------------------------------------------*/
				FirstTxMode = SYS_DocBlock.Src.Mode;	/**	１ページ目の送信モードに原稿制御ブロックのモードをセット	*/
				DocWidth = SYS_DocBlock.Src.Size;		/**	原稿サイズに原稿制御ブロックのサイズをセット	*/
			}
		}
		else {
			GetNextTxPageData( TxMemoryFilePage );	/**	再度，現ページのパラメータをセット	*/
			FirstTxMode = SYS_DocBlock.Src.Mode;	/**	１ページ目の送信モードに原稿制御ブロックのモードをセット	*/
			DocWidth = SYS_DocBlock.Src.Size;		/**	原稿サイズに原稿制御ブロックのサイズをセット	*/
		}
		break;

	/*--------------------------------------*/
	/*	全ページ送信終了，受領証要求あり	*/
	/*--------------------------------------*/
	case	TX_PAGE_END_RCR:		/**	全ページ送信終了，受領証要求あり	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	ストップキー入力あり	*/
			TxFCF = EOP_F;				/**	ＦＣＦにＥＯＰをセット	*/
			FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
			TransmitError( 0x14, 1 );	/**	Ｔ．１．４をセット	*/	/* Apr.29.1995 */
		}
		else {
			/**	SYS_TxTotalPage を更新するにセット	*/
/*			UpdateTxPageMode = UPDATE_TOTAL_PAGE;		送信済みページをセットする際に、正常終了した場合１引いた場合がセットされるためTxMemoryPageも	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;			/*		ｲﾝｸﾘﾒﾝﾄするように変更 By T.Yamaguchi Apr.27'96 */
			TxPageDataSetFlag = 0;		/**	送信ページデータセット済みフラグをクリア	*/
			TxFCF |= EOM_F;				/**	ＦＣＦにＥＯＭを(orで)セット	*/
			TxModeChangedFlag = 1;		/**	送信モード変更フラグをセット	*/
			TxRetrainingFlag = 1;		/**	再トレーニングフラグをセット	*/
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.12 K.Kawata */
			PRN_ChechRxPrintCallProc();
#endif
		}
		ECM_FrameCounter = MDM_EcmFrameNumber;	/**	ＥＣＭフレームカウンタにドライバのフレーム数をセット	*/
		TxPostMessageHandshake();	/**	ポストメッセージのハンドシェーク	*/
		ECM_PageCounter++;			/**	ＥＣＭページカウンタを＋１	*/
		ECM_BlockCounter = 0;		/**	ＥＣＭブロックカウンタを０クリア	*/
		/*
		** ディスプレイはTxMemoryFilePage、SYS_TxTotalPageをそのまま表示しているので
		** ページ数 2/1のようになってしまう
		** そこで、ここの処理以降はページ数を表示しないようにSYS_FaxCommStageを変更します
		** by T.Soneoka 1998/01/09
		*/
		SYS_FaxCommStage = FCM_TRANSMIT;
		if (UpdatePageInformationFlag == 1) {	/**	ページ番号更新が必要	*/
			UpdateTxPageInformation();			/**	送信ページ番号を更新	*/
			FaxComTxPerformingFlag = 0;			/**	送信中フラグをクリアし，ＲＣＲ受信(ポーリング)へ移る	*/
		}
		else {
			GetNextTxPageData( TxMemoryFilePage );	/**	再度，現ページのパラメータをセット	*/
			FirstTxMode = SYS_DocBlock.Src.Mode;	/**	１ページ目の送信モードに原稿制御ブロックのモードをセット	*/
			DocWidth = SYS_DocBlock.Src.Size;		/**	原稿サイズに原稿制御ブロックのサイズをセット	*/
		}
		break;

	/*----------------------*/
	/*	全ページ送信終了	*/
	/*----------------------*/
	case	TX_END:		/**	全ページ送信終了	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	ストップキー入力あり	*/
			TxFCF = EOP_F;				/**	ＦＣＦにＥＯＰをセット	*/
			FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
		}
		else {
			/**	SYS_TxTotalPage を更新するにセット	*/
/*			UpdateTxPageMode = UPDATE_TOTAL_PAGE;		送信済みページをセットする際に、正常終了した場合１引いた場合がセットされるためTxMemoryPageも	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;			/*		ｲﾝｸﾘﾒﾝﾄするように変更 By T.Yamaguchi Apr.27'96 */
#if defined (JPN)	/*----	★日本仕様★	----*/
#if (PRO_TX_SPEED == V34) /* Changed by H.Kubo 1998/01/08 */
			if (CMN_GetVoiceSwitch()) {		/**	会話予約キー入力ありかつ V34 でない*/
				TxFCF = PRI_Q_F;		/**	送信ＦＣＦのＰＲＩ－Ｑビットを立てる	*/
			}
#else
			if (SYS_VoiceSwitch == 1) {	/**	会話予約キー入力あり	*/
				TxFCF = PRI_Q_F;		/**	送信ＦＣＦのＰＲＩ－Ｑビットを立てる	*/
			}
#endif /* (PRO_TX_SPEED == V34) */
#endif
			TxPageDataSetFlag = 0;		/**	送信ページデータセット済みフラグをクリア	*/
			TxFCF |= EOP_F;				/**	ＦＣＦにＥＯＰを(orで)セット	*/
			TxRetrainingFlag = 1;		/**	再トレーニングフラグをセット	*/
		}
		ECM_FrameCounter = MDM_EcmFrameNumber;	/**	ＥＣＭフレームカウンタにドライバのフレーム数をセット	*/
		TxPostMessageHandshake();	/**	ポストメッセージのハンドシェーク	*/
		ECM_PageCounter++;			/**	ＥＣＭページカウンタを＋１	*/
		ECM_BlockCounter = 0;		/**	ＥＣＭブロックカウンタを０クリア	*/
		/*
		** ディスプレイはTxMemoryFilePage、SYS_TxTotalPageをそのまま表示しているので
		** ページ数 2/1のようになってしまう
		** そこで、ここの処理以降はページ数を表示しないようにSYS_FaxCommStageを変更します
		** by T.Soneoka 1998/01/09
		*/
		SYS_FaxCommStage = FCM_TRANSMIT;
		if (UpdatePageInformationFlag == 1) {		/**	ページ番号更新が必要	*/
			UpdateTxPageInformation();				/**	送信ページ番号を更新	*/
		}
		else {
			GetNextTxPageData( TxMemoryFilePage );	/**	再度，現ページのパラメータをセット	*/
		}
		break;

	/*----------------------*/
	/*	ストップキーで停止	*/
	/*----------------------*/
	case	TX_STOPPED:		/**	ストップキーで停止	*/
		/*----------------------------------------------------------------------*/
		/*	画データ送信中にストップキーが押された場合の処理を変更	Sep.13.1994	*/
		/*		1)	強制終了設定の場合は，即ＤＣＮを送出する					*/
		/*		2)	通常終了の場合は，ＥＯＰを送出し，応答受信する				*/
		/*			(全ページ終了の場合と同じ処理．)							*/
		/*			ページ数はカウントしない						Nov.28.1994	*/
		/*		3)	Ｔ．１．４で終了する  (Oct.18.1994)							*/
		/*----------------------------------------------------------------------*/
		if (CHK_TxForceStop() != 0) {	/**	強制終了する場合 (RTCなし)	*/
			FaxPhaseE( 5 );					/**	ＤＣＮ送出し，通信中フラグをクリア (応答受信しない)	*/
		}
		else {							/**	強制終了しない (RTC付けて正常終了)	*/
			/**	SYS_TxTotalPage を更新するにセット	*/
/*			UpdateTxPageMode = UPDATE_TOTAL_PAGE;		送信済みページをセットする際に、正常終了した場合１引いた場合がセットされるためTxMemoryPageも	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;			/*		ｲﾝｸﾘﾒﾝﾄするように変更 By T.Yamaguchi Apr.27'96 */
#if defined (JPN)	/*----	★日本仕様★	----*/
#if (PRO_TX_SPEED == V34) /* Changed by H.Kubo 1998/01/08 */
			if (CMN_GetVoiceSwitch()) {		/**	会話予約キー入力ありかつ V34 でない*/
				TxFCF = PRI_Q_F;		/**	送信ＦＣＦのＰＲＩ－Ｑビットを立てる	*/
			}
#else
			if (SYS_VoiceSwitch == 1) {	/**	会話予約キー入力あり	*/
				TxFCF = PRI_Q_F;		/**	送信ＦＣＦのＰＲＩ－Ｑビットを立てる	*/
			}
#endif /* (PRO_TX_SPEED == V34) */
#endif
			TxPageDataSetFlag = 0;		/**	送信ページデータセット済みフラグをクリア	*/
			TxFCF |= EOP_F;				/**	ＦＣＦにＥＯＰを(orで)セット	*/
			/*	TxRetrainingFlag = 1;	**	再トレーニングフラグをセット	*/
			ECM_FrameCounter = MDM_EcmFrameNumber;	/**	ＥＣＭフレームカウンタにドライバのフレーム数をセット	*/
			TxPostMessageHandshake();	/**	ポストメッセージのハンドシェーク	*/
			ECM_PageCounter++;			/**	ＥＣＭページカウンタを＋１	*/
			ECM_BlockCounter = 0;		/**	ＥＣＭブロックカウンタを０クリア	*/
#if 0		/* ストップキーありの時にページをカウントしない	 Nov.28.1994 */
//			if (UpdatePageInformationFlag == 1) {		/**	ページ番号更新が必要	*/
//				UpdateTxPageInformation();				/**	送信ページ番号を更新	*/
//			}
//			else {
//				GetNextTxPageData( TxMemoryFilePage );	/**	再度，現ページのパラメータをセット	*/
//			}
#endif
		}
		TransmitError( 0x14, 1 );	/**	Ｔ．１．４をセット	*/	/* Oct.18.1994 */
		break;

	/*------------------*/
	/*	１ｍオーバー	*/
	/*------------------*/
	case	TX_1M_OVER:		/**	１ｍオーバー	*/
#if 0	/* その他のエラー(default)と同じ処理にする Sep.13.1994 */
//		FaxHDLC_Transmit( EOP_F, PPS_F );				/**	命令送信（（ＰＰＳ－）ＥＯＰ）	*/
//		/**	応答受信し，ＯＫなら応答受信済フラグをセット	*/
//		if (MDM_ReceiveResponse(FCM_ReceiveResponseTime) == FSK_RECEIVE) {
//			ReceiveResponseFlag = 1;
//		}
//		else {
//			ReceiveResponseFlag = 0;
//		}
//		FaxPhaseE( 5 );									/**	ＤＣＮ送出し，通信中フラグをクリア	*/
//		TransmitError( 0x31, 1 );						/**	Ｔ．３．１をセット	*/
//		break;
#endif	/* Sep.13.1994 */

	/*----------------------------------*/
	/*	TX_DOC_ERR		原稿エラー		*/
	/*	TX_LAMP_ERR		ランプエラー	*/
	/*	TX_FILE_ERR		ファイルなし	*/
	/*----------------------------------*/
	default:		/**	その他のエラー	*/
/* #if defined(DEU)	1997/06/02  By T.Yamaguchi */ /* by M.H '97/03/21 for timing between pix and DCN */
		TimerCutStatus = 1;
/* #endif */
		FaxPhaseE( 5 );					/**	ＤＣＮ送出し，通信中フラグをクリア	*/
		TransmitError( 0x31, 1 );		/**	Ｔ．３．１をセット	*/

		/* ここからデバッグ用 */
#if 0	/* 外します 1997/10/30 T.Yamaguchi */
//		if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {
//			/* T3.1 デバッグ ここで止まったら教えて 1997/09/09  By T.Yamaguchi */
//			SYB_MaintenanceSwitch[MNT_SW_I7] = (UBYTE)SYS_DocBlock.Index.Item;
//			SYB_MaintenanceSwitch[MNT_SW_I8] = (UBYTE)SYS_DocBlock.Index.No;
//			SYB_MaintenanceSwitch[MNT_SW_I9] = (UBYTE)SYS_DocBlock.Index.Page; */
//			outp((unsigned long)0,(unsigned char)0);/* WriteProtectError for ICE */
//			wai_tsk(0xffff); */	/* loop */
//		}
#endif
		/* ここまでデバッグ用 */
		break;
	}
}


/*************************************************************************
	module		:[送信ポストメッセージハンドシェーク]
	function	:[
		1.	命令送信
		2.	応答受信（ＲＮＲは読み飛ばし，Ｔ５タイマー内でＲＲ送出）
		3.	ＰＰＲ受信でのＥＣＭエラーフレーム再送
		4.	応答受信の解析
	]
	return		:[]
	common		:[
		TxFCF	TxOptionFCF		RxFCF
		ReceiveResponseFlag		TxBaudRate
		FaxECM_ResponseTimeFlag	:ＥＣＭ応答受信待ち時間フラグ（3/4.8秒）
		FaxComPerformingFlag
		SYS_GeneralTimer		:全体のタイマー
	]
	condition	:[
		最初に送信するＦＣＦと拡張ＦＣＦは上位でセットしておく
	]
	comment		:[
		Nov.17.1994	 プリアンブル短縮フラグの一時キャンセル
		Dec.28.1994	 上記内容を再度修正
		1996/06/20	EOR-Qを送出後、更にPPRを受けた時は
					フロー通りに回線断するように修正
		1996/06/20	CTC送出しCTR以外受信/タイムアウトで
					DCNを2回送出するのを修正
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[竹内茂樹]
*************************************************************************/
void	TxPostMessageHandshake( void )
{
	UWORD	t5_timer;				/*	ＲＲ－ＲＮＲ処理用Ｔ５タイマ	*/
#if (PRO_TX_SPEED == V34) /* POPLAR_H のスタック節約のため、削除 H.Kubo 1997/12/18 */
#else
	UWORD	timer;
#endif /* (PRO_TX_SPEED == V34) */
	BYTE	ecm_retransmit_count;	/*	誤り訂正再送残り回数	*/
	UBYTE	completed_flag;			/*	全フレーム送信完了(or送信中断)フラグ	*/
	UBYTE	f_post_spd_hs;			/* 後手順短縮の一時キャンセル用 */	/* Dec.28.1994 */
	UBYTE	is_eor_txed;			/* 1996/06/20 s.takeuchi */
	UBYTE	ecm_all_frame_error_count; /* V17_FALLBACK_PATTERN 2000/1/6 Y.Murata */

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/04 */
	UBYTE	data_rate_change_req = 0; /* Added by H.Kubo 1997/08/04 */
#endif /* (PRO_TX_SPEED == V34) */

	completed_flag = 0;
	is_eor_txed = 0;	/* 1996/06/20 s.takeuchi */

	/**	誤り再送回数（メモリスイッチ）を再送残り回数カウンタにセット	*/
	ecm_retransmit_count = (BYTE) CHK_UNI_PPR_Count();
	ecm_all_frame_error_count = 0; /* V17_FALLBACK_PATTERN 2000/1/6 Y.Murata */
	while (completed_flag == 0) {	/**	全フレーム送信終了まで	*/
		ReceiveResponseFlag = 0;	/**	応答受信済みフラグをクリア	*/
		if (TxECM_Mode == ECM_ON) {	/**	ＥＣＭ送信の場合	*/
			/**	ＥＣＭ応答受信待ち時間をセットする（３or４．８秒）	*/
			FCM_ReceiveResponseTime	= FCM_PtnrChkECM_ResponseTime();	/* ECM応答受信時間の獲得 */
		}

		/**	命令送信（フレームは上位でセット），応答受信	*/
/* #if defined(DEU) 1997/06/02  By T.Yamaguchi */	/* '97/02/21 M.HARADA */
		TimerCutStatus = 1;
/* #endif */
		ReceiveResponseFlag = TxCommandAndRxResponse( TxFCF, TxOptionFCF );

		/** おかしな信号を受けっとた場合ReceiveResponseFlagをこかしてT4.1をセットする */
		if (ReceiveResponseFlag == 1) {		/**	応答を受信できた	*/
			PreAnalyzePostMessage();	/* 1997/06/12  By T.Yamaguchi */
		}

		if (ReceiveResponseFlag == 1) {		/**	応答を受信できた	*/
			/**	受信フレームの解析	*/
			AnalyzeRxPostMessageFrame();
		}
		else {
			/**	Ｔ．４．１をセット	*/
			TransmitError( 0x41, 1 );
		}

		/**	プリアンブル短縮を一旦キャンセルする	*/	/* Dec.15.1994 */
		/* ShorteningPreambleFlag = 0; * Dec.15.1994 */	/* Dec.28.1994 */
		f_post_spd_hs = PostSpeedHandshakeFlag;			/* Dec.28.1994 */
		PostSpeedHandshakeFlag = 0;						/* Dec.28.1994 */

		/*----------------------*/
		/*	ＲＮＲ－ＲＲ処理	*/
		/*----------------------*/
		t5_timer = SYS_GeneralTimer;		/**	Ｔ５タイマースタート	*/
		while ((RxFCF == RNR_F) && (ReceiveResponseFlag == 1)) {	/**	ＲＮＲ受信 && 応答受信あり	*/
#if 0 /* T5 タイマーを機種固有スイッチで延ばせるようにします。プリンタ受信救済用。 by H.Kubo 1999/03/09 */
@@			if ((UWORD)(SYS_GeneralTimer - t5_timer) < T5_TIMER) {	/**	Ｔ５タイマー以内	*/
#else
			if ((UWORD)(SYS_GeneralTimer - t5_timer) < (60 * (1000/10) * CHK_UNI_T5_Timer())) {	/**	Ｔ５タイマー以内	*/
#endif
				/**	命令送信（ＲＲ），応答受信	*/
				ReceiveResponseFlag = TxCommandAndRxResponse( RR_F, NULL_FF );
				if (ReceiveResponseFlag == 1) {		/**	応答を受信できた	*/
					/**	受信フレームの解析	*/
					AnalyzeRxPostMessageFrame();
				}
				else {		/**	ＲＲに対して応答なし	*/
					/**	Ｔ．５．１をセット	*/
					TransmitError( 0x51, 1 );
				}
			}
			else {		/**	Ｔ５タイムオーバー	*/
				/**	Ｔ．４．１をセットし，通信中フラグをクリア	*/
				TransmitError( 0x41, 1 );
				/**	応答受信ありフラグをクリア	*/
				ReceiveResponseFlag = 0;
			}
		}

		/**	プリアンブル短縮を再度セットする	*/			/* Dec.15.1994 */
		/* ShorteningPreambleFlag = PostSpeedHandshakeFlag; ** Dec.15.1994 */	/* Dec.28.1994 */
		PostSpeedHandshakeFlag = f_post_spd_hs;				/* Dec.28.1994 */

		/*--------------*/
		/*	ＰＰＲ受信	*/
		/*--------------*/
		if ((RxFCF == PPR_F) && (ReceiveResponseFlag == 1)) {	/**	ＰＰＲ受信 && 応答受信あり	*/
			ecm_retransmit_count--;		/**	再送残り回数を減算	*/

			if (FCM_CheckAllFrameError()) {
				ecm_all_frame_error_count++; /* V17_FALLBACK_PATTERN 2000/1/6 Y.Murata */
			}
/*==== V34 ====*/
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/04 */
			if (SYS_V34ProcedureExecuting() == 0) {	/** Ｖ３４でない */
				if (ecm_retransmit_count <= 0) {	/**	再送残り回数≦０	*/

					/*------------*/
					/* 通常Ｔ３０ */
					/*------------*/
					if (TxBaudRate == BPS2400_V27) {	/**	2400bpsで送信	*/
						/* ここから追加	 1996/06/20 s.takeuchi */
						if (is_eor_txed) {
							ReceiveResponseFlag = 0;
							break;
						}
						is_eor_txed = 1;
						/* ここまで	 1996/06/20 s.takeuchi */
						TxOptionFCF = EOR_F;			/**	送信拡張ＦＣＦにＥＯＲをセット	*/
						MemorizeTxErrorPage();			/**	エラーページを記憶	*/	/*	May.06.1994	*/
						TransmitError( 0x53, 0 );		/**	通信結果にＴ．５．３をセット	*/
#if defined(DEU) || defined(EUR)	/* by M.H '97/03/21 */
									/* 欧州仕様追加 by M.H 1999/09/16 */
						wai_tsk(15);
#endif
						continue;						/**	ループの先頭へ…	*/
					}
					else {		/**	ボーレイト＞２４００ＢＰＳ	*/
						/**	ボーレイトを１つ下げる	*/
#if 0
**						FallBackByPPR();
#endif
						FallBackByPPR(ecm_all_frame_error_count);	/* V17_FALLBACK_PATTERN 2000/1/6 Y.Murata */
						/*--------------------------------------------------------------
						** 低速な交信速度で大量の送信を行うと、通信時間が大幅に増加してしまう。
						** それならば、一旦回線断してリダイヤルして再送したほうが通信料金削減になります。
						** 2001/04/25 H.Yoshikawa
						*/
						/* ここから追加	 2001/04/25 H.Yoshikawa */
						if (FCM_CheckBaudRate(AttemptTxBaudRate) == FAXCOM_STOP) {
							if (is_eor_txed) {
								ReceiveResponseFlag = 0;
								break;
							}
							is_eor_txed = 1;
							TxOptionFCF = EOR_F;			/**	送信拡張ＦＣＦにＥＯＲをセット	*/
							MemorizeTxErrorPage();			/**	エラーページを記憶	*/	/*	May.06.1994	*/
							TransmitError( 0x53, 0 );		/**	通信結果にＴ．５．３をセット	*/
#if defined(DEU) || defined(EUR)	/* by M.H '97/03/21 */
										/* 欧州仕様追加 by M.H 1999/09/16 */
							wai_tsk(15);
#endif
							continue;						/**	ループの先頭へ…	*/
						}
						/* ここまで追加	 2001/04/25 H.Yoshikawa */


						ecm_all_frame_error_count = 0;

						/**	誤り再送回数を再送残り回数カウンタに再セット	*/
						ecm_retransmit_count = CHK_UNI_PPR_Count();
						/**	命令送信（ＣＴＣ），応答受信	*/
						ReceiveResponseFlag = TxCommandAndRxResponse( CTC_F, 0 );
						if (ReceiveResponseFlag == 1) {		/**	応答を受信できた	*/
							AnalyzeRxPostMessageFrame();	/**	受信フレームの解析	*/
							if (RxFCF == DCN_F) {			/**	ＤＣＮ受信	*/
								FaxPhaseE( 4 );				/**	通信中フラグをクリア（ＤＣＮ送出しない）	*/
								completed_flag = 1;			/**	ループ脱出	*/
							}
							else if (RxFCF != CTR_F) {		/**	ＣＴＲ以外を受信	*/
								/* DCNが2回送出されるため削除  1996/06/20 s.takeuchi
								** FaxPhaseE( 1 );				@**	ＤＣＮ送出し，通信終了	*@
								*/
								TransmitError( 0x52, 1 );	/**	Ｔ．５．２をセット，通信中フラグをクリア	*/
								completed_flag = 1;			/**	ループ脱出	*/
								/* DCNが2回送出されエラーコードが変るため1行追加  1996/06/20 s.takeuchi */
								ReceiveResponseFlag = 0;
							}
						}
						else {
							/* DCNが2回送出されるため削除  1996/06/20 s.takeuchi
							** FaxPhaseE( 1 );				@**	ＤＣＮ送出し，通信終了	*@
							*/
							TransmitError( 0x52, 1 );	/**	Ｔ．５．２をセット，通信中フラグをクリア	*/
							completed_flag = 1;			/** ループ脱出	*/
						}
					}
				}
			}
			else {
				/*--------------*/
				/* Ｖ３４モード */
				/*--------------*/
				/* Ｖ３４にＣＴＣはない */
				if (FCM_CheckMinimumDataRate()) {	/**	最小速度で送信	*/
#if 0 /* 最初から最低速度で送信時、PPR 3 回で EOR を出すので修正。 Changed by H.Kubo 1998/12/08 */
@@					if (ecm_retransmit_count <= 1) {	/**	再送残り回数≦０	*/
#else
					if (ecm_retransmit_count <= 0) {	/**	再送残り回数≦０	*/
#endif
						TxOptionFCF = EOR_F;			/**	送信拡張ＦＣＦにＥＯＲをセット	*/
						MemorizeTxErrorPage();			/**	エラーページを記憶	*/	/*	May.06.1994	*/
						TransmitError( 0x53, 0 );		/**	通信結果にＴ．５．３をセット	*/
						data_rate_change_req = 0;	/* 1996/02/14 */
						continue;						/**	ループの先頭へ…	*/
					}
				}
				else {
#if 0 /* 最初から最低速度で送信時、PPR 3 回で EOR を出すので修正。 Changed by H.Kubo 1998/12/08 */
@@					if (ecm_retransmit_count <= 1) {	/**	再送残り回数≦１	*/
@@						ecm_retransmit_count = CHK_UNI_PPR_Count() + (UBYTE)1;	/* 1996/08/28 */
@@						/* データレイト変更要求 */
@@						data_rate_change_req = 1;
@@					}
#else
					if (ecm_retransmit_count == 1) {	/**	データレイト変更を決めても、実際に変更できるのは次の次の PC. よって再送残り回数 == １	*/
						data_rate_change_req = 1;
					}
					else if (ecm_retransmit_count <= 0) {
						ecm_retransmit_count = CHK_UNI_PPR_Count();
						ecm_all_frame_error_count = 0; /* V17_FALLBACK_PATTERN 2000/1/6 Y.Murata */
						if (ecm_retransmit_count <= 1) { /** PPR 回数設定がもともと 1 以下だったときにデータレートが変更されるようにする*/
							data_rate_change_req = 1;
						}
					}
#endif
				}
			}
#else /* (PRO_TX_SPEED == V34) */
/*==== V33 or lower ====*/
			if (ecm_retransmit_count <= 0) {	/**	再送残り回数≦０	*/
				if (TxBaudRate == BPS2400_V27) {	/**	2400bpsで送信	*/
					/* ここから追加	 1996/06/20 s.takeuchi */
					if (is_eor_txed) {
						ReceiveResponseFlag = 0;
						break;
					}
					is_eor_txed = 1;
					/* ここまで	 1996/06/20 s.takeuchi */
					TxOptionFCF = EOR_F;			/**	送信拡張ＦＣＦにＥＯＲをセット	*/
					MemorizeTxErrorPage();			/**	エラーページを記憶	*/	/*	May.06.1994	*/
					TransmitError( 0x53, 0 );		/**	通信結果にＴ．５．３をセット	*/
#if defined(DEU) || defined(EUR)	/* by M.H '97/03/21 */
									/* 欧州仕様追加 by M.H 1999/09/16 */
					wai_tsk(15);
#endif
					continue;						/**	ループの先頭へ…	*/
				}
				else {		/**	ボーレイト＞２４００ＢＰＳ	*/
					/**	ボーレイトを１つ下げる	*/
#if 0
**					FallBackByPPR();
#endif
					FallBackByPPR(ecm_all_frame_error_count);	/* V17_FALLBACK_PATTERN 2000/1/6 Y.Murata */
					/*--------------------------------------------------------------
					** 低速な交信速度で大量の送信を行うと、通信時間が大幅に増加してしまう。
					** それならば、一旦回線断してリダイヤルして再送したほうが通信料金削減になります。
					** 2001/04/25 H.Yoshikawa
					*/
					/* ここから追加	 2001/04/25 H.Yoshikawa */
					if (FCM_CheckBaudRate(AttemptTxBaudRate) == FAXCOM_STOP) {
						if (is_eor_txed) {
							ReceiveResponseFlag = 0;
							break;
						}
						is_eor_txed = 1;
						TxOptionFCF = EOR_F;			/**	送信拡張ＦＣＦにＥＯＲをセット	*/
						MemorizeTxErrorPage();			/**	エラーページを記憶	*/	/*	May.06.1994	*/
						TransmitError( 0x53, 0 );		/**	通信結果にＴ．５．３をセット	*/
#if defined(DEU) || defined(EUR)	/* by M.H '97/03/21 */
										/* 欧州仕様追加 by M.H 1999/09/16 */
						wai_tsk(15);
#endif
						continue;						/**	ループの先頭へ…	*/
					}
					/* ここまで追加	 2001/04/25 H.Yoshikawa */

					ecm_all_frame_error_count = 0;

					/**	誤り再送回数を再送残り回数カウンタに再セット	*/
					ecm_retransmit_count = CHK_UNI_PPR_Count();
					/**	命令送信（ＣＴＣ），応答受信	*/
					ReceiveResponseFlag = TxCommandAndRxResponse( CTC_F, 0 );
					if (ReceiveResponseFlag == 1) {		/**	応答を受信できた	*/
						AnalyzeRxPostMessageFrame();	/**	受信フレームの解析	*/
						if (RxFCF == DCN_F) {			/**	ＤＣＮ受信	*/
							FaxPhaseE( 4 );				/**	通信中フラグをクリア（ＤＣＮ送出しない）	*/
							completed_flag = 1;			/**	ループ脱出	*/
						}
						else if (RxFCF != CTR_F) {		/**	ＣＴＲ以外を受信	*/
							/* DCNが2回送出されるため削除  1996/06/20 s.takeuchi
							** FaxPhaseE( 1 );				@**	ＤＣＮ送出し，通信終了	*@
							*/
							TransmitError( 0x52, 1 );	/**	Ｔ．５．２をセット，通信中フラグをクリア	*/
							completed_flag = 1;			/**	ループ脱出	*/
							/* DCNが2回送出されエラーコードが変るため1行追加  1996/06/20 s.takeuchi */
							ReceiveResponseFlag = 0;
						}
					}
					else {
						/* DCNが2回送出されるため削除  1996/06/20 s.takeuchi
						** FaxPhaseE( 1 );				@**	ＤＣＮ送出し，通信終了	*@
						*/
						TransmitError( 0x52, 1 );	/**	Ｔ．５．２をセット，通信中フラグをクリア	*/
						completed_flag = 1;			/** ループ脱出	*/
					}
				}
			}
#endif /* (PRO_TX_SPEED == V34) */
/*==== end of V33 or lower ====*/

			if (completed_flag == 0) {	/**	残りフレームあり	*/
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/04 */
				if (SYS_V34ProcedureExecuting() == 0) {	/** Ｖ３４でない */
					/*----------------------------------*/
					/*	ＥＣＭエラーフレーム再送処理	*/
					/*----------------------------------*/
					/**	２００／４００msのＥＣＭ再送間隔をあける	**
					***	（通信開始時のメモリスイッチより決定）		*/
					FaxTimer( FCM_PtnrChkECM_TxInterval() );
				} /* end of if (SYS_V34ProcedureExecuting() == 0) */
#else /* (PRO_TX_SPEED == V34) */
				/*----------------------------------*/
				/*	ＥＣＭエラーフレーム再送処理	*/
				/*----------------------------------*/
				/**	２００／４００msのＥＣＭ再送間隔をあける	**
				***	（通信開始時のメモリスイッチより決定）		*/
				timer = FCM_PtnrChkECM_TxInterval();
				FaxTimer( timer );
#endif /* (PRO_TX_SPEED == V34) */

				SaveT30Data( SYS_T30_TX_PIX, &MDM_ModemBuffer[0][0], 0 );

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/04 */
				FaxComPhaseStatus = FAX_TX_PH_C_RPIX;

				/*--------------------------------------*/
				/* コントロールチャネルｔｕｒｎ－ｏｆｆ */
				/*--------------------------------------*/
				if (SYS_V34ProcedureExecuting() == 1) {	/* CTC ONの時にﾘｰﾄﾞ 1996/03/04 */
					TxBaudRate = FCM_CheckTxDataRate();
				}
				if (FCM_ControlChanelTurnOff()) {
					FCM_SetTxDataRate();
				}
				else {
					FaxPhaseE( 1 );				/**	ＤＣＮ送出し，通信終了	*/
					TransmitError( 0x32, 1 );	/* とりあえず */
					break;
				}
#endif /* (PRO_TX_SPEED == V34) */

				/**	ＥＣＭエラーフレーム再送信（画データオープン／クローズ）	*/
				MDM_TxPixOpen( TxBaudRate, TxECM_Mode );
				ECM_FrameCounter = MDM_TxEcmPartialPage();
				MDM_TxPixClose( TxECM_Mode );

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/04 */
				FaxComPhaseStatus = FAX_TX_PH_C_AFTER_RPIX;
				/*------------------------------------*/
				/* プライマリチャネルｔｕｒｎ－ｏｆｆ */
				/*------------------------------------*/
				if (data_rate_change_req == 1) {	/* データレイト変更要求 */
					data_rate_change_req = 0;
					/* データレイト変更 */
					/*FCM_ChangeDataRate(TxBaudRate);*/
					/*FCM_DataRateChangExecute = 1;*/	/* 1996/08/28 */

					FCM_DataRateChangExecute = FCM_ChangeDataRate(TxBaudRate);	/* 1996/09/10 Y.M */
				}
				FCM_PrimaryChanelTurnOff();
				FCM_DataRateChangExecute = 0;		/* 1996/08/28 */

				if (SYS_V34ProcedureExecuting() == 0) {	/** Ｖ３４でない */
					/* 追加  May.20.1995 */
					/**	ＥＣＭ再送ＰＩＸ－ポストメッセージ間のウェイト（９０ms）	*/
#if defined(DEU) || defined(EUR)	/* by M.H '97/03/21 */
									/* 欧州仕様追加 by M.H 1999/09/16 */
					FaxTimer( 70 );
#else
					FaxTimer( 90 );
#endif
				}
#else /* (PRO_TX_SPEED == V34) */
				/* 追加	 May.20.1995 */
				/**	ＥＣＭ再送ＰＩＸ－ポストメッセージ間のウェイト（９０ms）	*/
#if defined(DEU) || defined(EUR)	/* by M.H '97/03/21 */
									/* 欧州仕様追加 by M.H 1999/09/16 */
				FaxTimer( 70 );
#else
				FaxTimer( 90 );
#endif
#endif /* (PRO_TX_SPEED == V34) */
			}
		}
		else {		/**	ＰＰＲ以外を受信 || 応答受信なし	*/
			completed_flag = 1;		/**	ループ脱出	*/
		}
	}

	if (ReceiveResponseFlag == 1) {		/**	応答受信あり	*/
		AnalyzeReceivedPostMessage();		/**	受信ポストメッセージの解析	*/
	}
	else {								/**	応答受信なし	*/
		UpdatePageInformationFlag = 0;		/**	ページ更新フラグをクリア	*/
		FaxPhaseE( 1 );						/**	ＤＣＮ送出し，通信終了	*/
	}
}


/*************************************************************************
	module		:[ポストメッセージ応答受信フレームの解析]
	function	:[
		1.	送信した命令フレームと，受信した応答メッセージに応じて，
		.	各処理を行う
		2.	おかしな応答の場合はＴ．４．１とする
	]
	return		:[]
	common		:[
		TxFCF	TxOptionFCF		RxFCF	RxOptionFCF
		SYS_FaxComTxType		FaxComResult
		TxPageFinishStatus		UpdatePageInformationFlag
		TxModeChangedFlag		TxRetrainingFlag
		TxCoverPageFlag
		RTN_ReceiveCounter		:ＲＴＮ／ＰＩＮ受信回数（ドイツ仕様のみ）
		SYS_VoiceCallAccepted
	]
	condition	:[
		送信したポストメッセージは，送信ＦＣＦと送信拡張ＦＣＦに入っていること
		受信したポストメッセージは，受信ＦＣＦと受信拡張ＦＣＦに入っていること
	]
	comment		:[
		全機種共通の大バグ修正 (Sep.20.1994)
		.	最終ページ送信後，受領証要求でＥＯＭを送信後に
		.	ＰＩＰ／ＰＩＮを受信した時は，Ｔ３タイマで会話
		.	予約処理し，Ｔ３タイムオーバーの時は正常パスで
		.	ＤＩＳ受信しＤＴＣ送出する
		.	但しＰＩＮ受信時は通信速度を落として受領証の受
		.	信可能速度とする
			RTN/PIN自動再送ON/OFFの追加	 1996/11/09 s.takeuchi
		.	FCM_PtnrChkRTN_NoReTransmit
			FCM_PtnrChkRTN_AutoReTransmit()のある部分
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/26]
	author		:[竹内茂樹]
*************************************************************************/
void	AnalyzeReceivedPostMessage( void )
{
	UBYTE	tmp_tx_fcf;			/*	PRI-QビットをマスクしたTxFCF	*/

	/*---------------------------------------------------
	*	FaxTxPhaseD()でセットしてるから，いらへんはず	*
	*	%**	ページ更新フラグをセット	*%				*
	*	UpdatePageInformationFlag = 1;					*
	---------------------------------------------------*/

	/**	PRI-Qビットをマスクしてテンポラリにセット	*/
	tmp_tx_fcf = TxFCF & (UBYTE)~PRI_Q_F;

#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  Feb.23.1995 */
	/* 不達通知送信の場合は受信側からの会話予約を無視する */
	/* 条件変更↓(CommandFileOptionItem == SYS_RELAYED_TX_REPORT)  Apr.27.1995 */
	if (TxRelayReport) {
		switch (RxFCF) {
		case	PIP_F:
			RxFCF = MCF_F;
			break;
		case	PIN_F:
			RxFCF = RTN_F;
			break;
		}
	}
#endif

	/*--------------*/
	/*	ＰＩＰ受信	*/
	/*--------------*/
	if (RxFCF == PIP_F) {	/**	ＰＩＰ受信	*/
#if defined(STOCKHM2)	/*QAT:会や予約対応 by SMuratec 夏 2004/11/03 */

		if( CHK_VoiceCallEnable() ){
			FCM_PIP_Received(tmp_tx_fcf);			/* PIPを受信した時の処理を関数化 1996/12/05	 By T.Yamaguchi */
		}
		else{
			FaxPhaseE( 3 );			
		}
#else
		FCM_PIP_Received(tmp_tx_fcf);			/* PIPを受信した時の処理を関数化 1996/12/05	 By T.Yamaguchi */
#endif	

	}
	/*--------------*/
	/*	ＰＩＮ受信	*/
	/*--------------*/
	else if (RxFCF == PIN_F) {	/**	ＰＩＮ受信	*/
		FCM_PIN_Received(tmp_tx_fcf);			/* PINを受信した時の処理を関数化 1996/12/05	 By T.Yamaguchi */
	}
	/*------------------------------------------*/
	/*	ＥＲＲ受信（ＥＯＲ－Ｑに対する応答）	*/
	/*------------------------------------------*/
	else if (RxFCF == ERR_F) {	/**	ＥＲＲ受信	*/
		if ((TxOptionFCF == EOR_F)
		&&	(tmp_tx_fcf == EOP_F)) {	/**	EOR-(PRI-)EOPに対してＥＲＲを受信	*/
			/*	MemorizeTxErrorPage(); EOR-Qを出す時に行う May.06.1994	**	エラーページを記憶	*/
			FaxPhaseE( 2 );				/**	通信終了（ＤＣＮあり）	*/
		}
		else if ((TxOptionFCF == EOR_F)
		&&	((tmp_tx_fcf == NULL_FF) || (tmp_tx_fcf == MPS_F) || (tmp_tx_fcf == EOM_F))) {	/**	EOR-(PRI-)(NULL,MPS,EOM)に対してＥＲＲを受信	*/
			/*	MemorizeTxErrorPage(); EOR-Qを出す時に行う May.06.1994	**	エラーページを記憶	*/
			if (CHK_AfterEOR() != 0) {	/**	ＥＯＲ－Ｑ送信後，中断する設定	*/
				FaxPhaseE( 2 );			/**	通信終了（ＤＣＮあり）	*/
			}
		}
		else {		/**	おかしな応答を受信（Ｇ３送信でＥＲＲを受信など）	*/
			/*
			** リダイヤル時に、次のページから送ってしまうためページ更新フラグをクリア
			**	1997/10/23 By T.Yamaguchi
			*/
			UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
			TransmitError( 0x41, 1 );	/**	Ｔ．４．１をセット	*/
			FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
		}
	}
	/*--------------*/
	/*	ＭＣＦ受信	*/
	/*--------------*/
	else if (RxFCF == MCF_F) {	/**	ＭＣＦ受信	*/
		/*----	★ドイツ仕様★	------------*/
		/*	RTN_ReceiveCounter をクリアする	*/
		/*----------------------------------*/
		TxCoverPageFlag = 0;		/**	カバーページ送信フラグをクリア	*/
#if (PRO_STAMP==ENABLE)
		/*----------------------*/
		/*	済みスタンプ処理	*/
		/*----------------------*/
		if (!((TxOptionFCF == PPS_F) && (TxFCF == NULL_FF))) {	/**	ページ途中ではない	*/
			if ((TxSmType == TX_SCAN)		/* (SYS_FaxComTxType == SYS_SCANNER_TX) スキャナ送信の見方を変更  Nov.17.1994 */
			&&	(MDM_PhaseC_Status == TX_PAGE_END)
			&&	(CheckErrorPage() == 0)) {		/**	スキャナ送信でエラーページではない	*/
				CMN_PushStamp();					/**	済みスタンプ押す	*/
			}
		}
#endif
		if (((TxOptionFCF == PPS_F) || (TxOptionFCF == 0))
		&&	(tmp_tx_fcf == EOP_F)) {	/**	(PPS-)(PRI-)EOPに対してＭＣＦを受信	*/
			FaxPhaseE( 5 );					/**	通信終了（ＤＣＮあり）	*/
		}
	}
	/*--------------*/
	/*	ＲＴＰ受信	*/
	/*--------------*/
	else if (RxFCF == RTP_F) {	/**	ＲＴＰ受信	*/
		/*----	★ドイツ仕様★	------------*/
		/*	RTN_ReceiveCounter をクリアする	*/
		/*----------------------------------*/
		TxCoverPageFlag = 0;				/**	カバーページ送信フラグをクリア	*/
		if ((TxOptionFCF == 0) && (tmp_tx_fcf == EOP_F)) {	/**	(PRI-)EOPに対してＲＴＰを受信	*/
#if (PRO_STAMP==ENABLE)
			/*----------------------*/
			/*	済みスタンプ処理	*/
			/*----------------------*/
			if ((TxSmType == TX_SCAN)		/* (SYS_FaxComTxType == SYS_SCANNER_TX) スキャナ送信の見方を変更  Nov.17.1994 */
			&&	(MDM_PhaseC_Status == TX_PAGE_END)) {	/**	スキャナ送信	*/
				CMN_PushStamp();						/**	済みスタンプ押す	*/
			}
#endif
			FaxPhaseE( 5 );					/**	通信終了（ＤＣＮあり）	*/
		}
		else if ((TxOptionFCF == 0)
		&&	((tmp_tx_fcf == MPS_F) || (tmp_tx_fcf == EOM_F))) {	/**	(PRI-)(MPS,EOM)に対してＲＴＰを受信	*/
#if (PRO_STAMP==ENABLE)
			/*----------------------*/
			/*	済みスタンプ処理	*/
			/*----------------------*/
			if ((TxSmType == TX_SCAN)		/* (SYS_FaxComTxType == SYS_SCANNER_TX) スキャナ送信の見方を変更  Nov.17.1994 */
			&&	(MDM_PhaseC_Status == TX_PAGE_END)) {	/**	スキャナ送信	*/
				CMN_PushStamp();						/**	済みスタンプ押す	*/
			}
#endif
			TxRetrainingFlag = 1;			/**	再トレーニングフラグをセット	*/
		}
		else {		/**	おかしな応答を受信（ＥＣＭでＲＴＰを受信など）	*/
			/*
			** リダイヤル時に、次のページから送ってしまうためページ更新フラグをクリア
			**	1997/10/23 By T.Yamaguchi
			*/
			UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
			TransmitError( 0x41, 1 );	/**	Ｔ．４．１をセット	*/
			FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
		}
	}
	/*--------------*/
	/*	ＲＴＮ受信	*/
	/*--------------*/
	else if (RxFCF == RTN_F) {	/**	ＲＴＮ受信	*/
		/*----	★ドイツ仕様★	----------------------------*/
		/*	メモリ送信の時，RTN_ReceiveCounter を +1 する	*/
		/*--------------------------------------------------*/
		if ((TxOptionFCF == 0) && (tmp_tx_fcf == EOP_F)) {	/**	(PRI-)EOPに対してＲＴＮを受信	*/
			if ((SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) /**	メモリ送信	*/
			 && (TxBaudRate != BPS2400_V27)		/**	メモリ送信で4800bps以上	*/
			 &&	(!FCM_PtnrChkRTN_NoReTransmit())) {	/* Nov.12.1996	By T.Yamaguchi */
				/*----	★ドイツ仕様★	------------------------------------*/
				/*	上記条件かつ RTN_ReceiveCounter<=3 の時は，ここを通る	*/
				/*----------------------------------------------------------*/
				FallBackByRTN();				/**	ボーレイトを下げる	*/
				/*--------------------------------------------------------------
				** 低速な交信速度で大量の送信を行うと、通信時間が大幅に増加してしまう。
				** それならば、一旦回線断してリダイヤルして再送したほうが通信料金削減になります。
				** 2001/04/25 H.Yoshikawa
				*/
				/* ここから追加	 2001/04/25 H.Yoshikawa */
				if (FCM_CheckBaudRate(AttemptTxBaudRate) == FAXCOM_STOP) {
					MemorizeTxErrorPage();			/**	エラーページを記憶	*/
					FaxPhaseE( 1 );					/**	通信終了（ＤＣＮあり）	*/
				}
				else {
					TxRetrainingFlag = 1;			/**	再トレーニングフラグをセット	*/
					UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
				}
				/* ここまで追加	 2001/04/25 H.Yoshikawa */
#if (0)	/* 2001/04/25 H.Yoshikawa */
//				TxRetrainingFlag = 1;			/**	再トレーニングフラグをセット	*/
//				UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
#endif
			}
			else {				/**	メモリ送信で2400bps，スキャナ送信	*/
				MemorizeTxErrorPage();			/**	エラーページを記憶	*/
				FaxPhaseE( 1 );					/**	通信終了（ＤＣＮあり）	*/
				/*----	★ドイツ仕様★	------------*/
				/*	RTN_ReceiveCounter をクリアする	*/
				/*----------------------------------*/
			}
		}
		else if ((TxOptionFCF == 0)
		&& ((tmp_tx_fcf == MPS_F) || (tmp_tx_fcf == EOM_F))) {	/**	(PRI-)(MPS,EOM)に対してＲＴＮを受信	*/
			if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {	/**	メモリ送信	*/
				if (TxBaudRate != BPS2400_V27) {		/**	4800bps以上	*/
					FallBackByRTN();				/**	ボーレイトを下げる	*/
					TxRetrainingFlag = 1;			/**	再トレーニングフラグをセット	*/
					if (!FCM_PtnrChkRTN_NoReTransmit()) {	/* Nov.12.1996	By T.Yamaguchi */
						UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
					}
					else {
						MemorizeTxErrorPage();
					}
					/*----	★ドイツ仕様★	--------------------------------------------*/
					/*	RTN_ReceiveCounter<=3 の時は，ページ情報を更新しない			*/
					/*					  > 3 の時は，エラーページを記憶してクリアして	*/
					/*								  ページ情報を更新する				*/
					/*------------------------------------------------------------------*/
				}
				else {		/**	2400bps	*/
					MemorizeTxErrorPage();			/**	エラーページを記憶	*/
					TxRetrainingFlag = 1;			/**	再トレーニングフラグをセット	*/
					/*----	★ドイツ仕様★	------------*/
					/*	RTN_ReceiveCounter をクリアする	*/
					/*----------------------------------*/
				}
			}
			else {		/**	スキャナ送信	*/
				MemorizeTxErrorPage();			/**	エラーページを記憶	*/
				FallBackByRTN();				/**	ボーレイトを下げる	*/
				TxRetrainingFlag = 1;			/**	再トレーニングフラグをセット	*/
			}
			
			/*--------------------------------------------------------------
			** 低速な交信速度で大量の送信を行うと、通信時間が大幅に増加してしまう。
			** それならば、一旦回線断してリダイヤルして再送したほうが通信料金削減になります。
			** 2001/04/25 H.Yoshikawa
			*/
			/* ここから追加	 2001/04/25 H.Yoshikawa */
			if (FCM_CheckBaudRate(AttemptTxBaudRate) == FAXCOM_STOP) {
				FaxPhaseE( 1 );					/**	通信終了（ＤＣＮあり）	*/
				TxRetrainingFlag = 0;			/**	再トレーニングフラグをクリア	*/
			}
			/* ここまで追加	 2001/04/25 H.Yoshikawa */
			
		}
		else {		/**	おかしな応答を受信（ＥＣＭでＲＴＮを受信など）	*/
			/*
			** リダイヤル時に、次のページから送ってしまうためページ更新フラグをクリア
			**	1997/10/23 By T.Yamaguchi
			*/
			UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
			TransmitError( 0x41, 1 );	/**	Ｔ．４．１をセット	*/
			FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
		}
	}
	/*--------------*/
	/*	ＤＣＮ受信	*/
	/*--------------*/
	else if (RxFCF == DCN_F) {	/**	ＤＣＮ受信	*/
		/*
		** ポストメッセージに対してＤＣＮを受信したとき、Ｔ４．１になるが
		** リダイヤル時に、次のページから送ってしまうためページ更新フラグをクリア
		**	1997/10/23 By T.Yamaguchi
		*/
		UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
		TransmitError( 0x41, 1 );	/**	Ｔ．４．１をセット	*/
		FaxPhaseE( 4 );				/**	通信終了（ＤＣＮなし）	*/
	}
	/*--------------------------*/
	/*	その他のフレームを受信	*/
	/*--------------------------*/
	else {		/**	その他のフレームを受信	*/
		/*
		** ポストメッセージに対してＤＣＮを受信したとき、Ｔ４．１になるが
		** リダイヤル時に、次のページから送ってしまうためページ更新フラグをクリア
		**	1997/10/23 By T.Yamaguchi
		*/
		UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
		TransmitError( 0x41, 1 );	/**	Ｔ．４．１をセット	*/
		FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
	}
}


/*************************************************************************
	module		:[ＰＩＰ受信時の処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/12/05]
	author		:[山口　哲治]
*************************************************************************/
void FCM_PIP_Received(UBYTE tmp_tx_fcf)
{
	UBYTE	voice_result;		/*	被会話予約結果	*/
	UBYTE	tmp_fcm_stage;		/*	被会話予約での通信状態遷移の待避用	*/
	UBYTE	voice_tout_mode;	/*	会話予約処理時のタイムアウト処理指定	*/
				/*	MODE_T3_TIMER		:Ｔ３タイムアウトのみ				*/
				/*	MODE_T3_T1_TIMER	:Ｔ３の後，Ｔ１タイマで命令受信待ち	*/

	/*--------------*/
	/*	ＰＩＰ受信	*/
	/*--------------*/
	if (!((TxOptionFCF == PPS_F) && (TxFCF == NULL_FF))) {	/**	PPS-NULL以外に対してＰＩＰを受信	*/
		TxCoverPageFlag = 0;	/**	カバーページ送信フラグをクリア	*/	/* Nov.22.1994 */
#if (PRO_STAMP==ENABLE)
		/*----------------------*/
		/*	済みスタンプ処理	*/
		/*----------------------*/
		if ((TxSmType == TX_SCAN)		/* (SYS_FaxComTxType == SYS_SCANNER_TX) スキャナ送信の見方を変更  Nov.17.1994 */
		&&	(MDM_PhaseC_Status == TX_PAGE_END)
		&&	(CheckErrorPage() == 0)) {		/**	スキャナ送信でエラーページではない	*/
			CMN_PushStamp();					/**	済みスタンプ押す	*/
		}
#endif
		/*------------------------------*/
		/**	表示切替指示(会話予約中)	*/
		/*------------------------------*/
		tmp_fcm_stage = SYS_FaxCommStage;
		SYS_FaxCommStage = FCM_VOICE_CALLED;
		SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );
		/*--------------------------*/
		/**	送信側被会話予約処理	*/
		/*--------------------------*/
		if (tmp_tx_fcf == EOP_F) {	/*	EOP送出時	*/
			voice_tout_mode = MODE_T3_TIMER;
		}
		else if (TxPageFinishStatus == TX_PAGE_END_RCR) {	/*	受領証要求へ	*/	/* Sep.20.1994 */
			voice_tout_mode = MODE_T3_TIMER;
		}
		else {						/*	MPS/EOM送出時	*/
			voice_tout_mode = MODE_T3_T1_TIMER;
		}
#if (PRO_LINENUMBER == TWICE_LINE) && !defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/15 */
/* 
** 疑似２回線仕様
** 拡張ラインには会話予約処理がないためPIPの処理を変えます
** PIPを受信したらすぐにFSK送出処理に移ります
** by T.Soneoka 1997/11/20
*/
		if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	標準ラインにてPIPを受信した場合	*/
			voice_result = MDM_TxVoiceReqRcvCmd( voice_tout_mode );	/**	疑似ベル鳴動・FSK受信等処理	*/
		}
		else {	/**	拡張ラインにてPIP受信時	*/
			voice_result = T3_TIME_OVER;	/**	T3タイムオーバ	*/
		}
#else
		voice_result = MDM_TxVoiceReqRcvCmd( voice_tout_mode );
#endif
		switch (voice_result) {	/**	会話予約結果	*/
		case	TEL1_OH_DETECT:		/**	ＴＥＬ１オフフック検出	*/
		case	TEL2_OH_DETECT:		/**	ＴＥＬ２オフフック検出	*/
		case	HOOK_KEY_OH_DETECT:	/**	オフフックキー検出	*/
			SYS_VoiceCallAccepted = voice_result;	/**	会話予約成立(ＯＨ識別)	*/
			/* Sep.16.1994 */
			if (voice_result == TEL1_OH_DETECT) {
				FaxTelOffHookTEL1Flag = 1;
			}
			else if (voice_result == TEL2_OH_DETECT) {
				FaxTelOffHookTEL2Flag = 1;
			}
			/**	前回のＦＣＦをＰＲＩ－Ｑにして送出 (ＰＰＳ－なし)	*/
			FaxHDLC_Transmit( (UBYTE)(TxFCF | PRI_Q_F), 0 );
			if (!(((TxOptionFCF == 0) || (TxOptionFCF == PPS_F)) && (tmp_tx_fcf == EOP_F))
			&&	(TxPageFinishStatus != TX_PAGE_END_RCR)) {	/**	(PPS-)(PRI-)EOPを送出していない(次ページあり)	**
															***	&&次ページが受領証の要求ではない				*/
				TransmitError( 0x44, 1 );	/**	Ｔ．４．４をセット	*/
			}
			FaxPhaseE( 4 );		/**	通信終了（ＤＣＮなし）	*/
			break;
		case	FSK_RECEIVE:		/**	命令受信した	*/
			AnalyzeRxPostMessageFrame();		/**	受信フレームの解析	*/
			tmp_tx_fcf = TxFCF & (UBYTE)~PRI_Q_F;
			if (((TxOptionFCF == PPS_F) || (TxOptionFCF == 0))
			&&	(tmp_tx_fcf == EOP_F)) {		/**	(PPS-)(PRI-)EOPを送信した(次ページなし)	*/
				if (RxFCF == DCN_F) {	/**	ＤＣＮ受信	*/
					FaxPhaseE( 4 );		/**	通信終了（ＤＣＮなし）	*/
				}
				else {
					FaxPhaseE( 2 );		/**	通信終了（ＤＣＮあり）	*/
				}
			}
			else {		/**	(PPS-)(PRI-)EOP以外を送信した(次ページあり)	*/
				if (RxFCF == DCN_F) {	/**	ＤＣＮ受信	*/
					TransmitError( 0x44, 1 );	/**	Ｔ．４．４をセット	*/
					FaxPhaseE( 4 );				/**	通信終了（ＤＣＮなし）	*/
				}
				else if (RxFCF == DIS_F) {	/**	ＤＩＳ受信	*/
					TxRetrainingFlag  = 1;		/**	再トレーニングフラグをセット	*/
					TxModeChangedFlag = 0;		/**	モード変更フラグをクリア	*/
				}
				else {
					TransmitError( 0x44, 1 );	/**	Ｔ．４．４をセット	*/
					FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
				}
			}
			break;
		case	T3_TIME_OVER:	/**	Ｔ３タイムアウト (EOPを送出した時 / 受領証を要求する時)	*/
		case	T1_TIME_OVER:	/**	Ｔ３の後，Ｔ１タイムアウト (MPS/EOMを送出した時)	*/
			/* Sep.20.1994 */
			if (TxPageFinishStatus == TX_PAGE_END_RCR) {	/*	受領証要求へ	*/
				/**	今の通信速度を，受領証受信時の受信可能ボーレイトにする	*/
				AvailableRxBaudRate = TxBaudRate;
#if 0
				TxRetrainingFlag = 1;
				FRA_PIP_PIN_Rx_Flag = 1;
#endif
			}
			else {
				if (((TxOptionFCF == PPS_F) || (TxOptionFCF == 0))
				&&	(tmp_tx_fcf == EOP_F)) {	/**	次ページなし (Ｔ３タイムアウト)	*/
					FaxPhaseE( 3 );				/**	通信終了（ＤＣＮあり）	*/
				}
				else {							/**	次ページあり (Ｔ３＋Ｔ１タイムアウト)	*/
#if defined(FRA)
					TxRetrainingFlag = 1;
					FRA_PIP_PIN_Rx_Flag = 1;
#else
					TransmitError( 0x11, 1 );	/**	Ｔ．１．１をセット	*/
					FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
#endif
				}
			}
			break;
		default:				/**	エラー検出 (FSK_ERROR)	*/
			if (((TxOptionFCF == PPS_F) || (TxOptionFCF == 0))
			&&	(tmp_tx_fcf == EOP_F)) {	/**	次ページなし	*/
				FaxPhaseE( 2 );				/**	通信終了（ＤＣＮあり）	*/
			}
			else {		/**	次ページあり	*/
				TransmitError( 0x44, 1 );	/**	Ｔ．４．４をセット	*/
				FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
			}
			break;
		}
		SYS_FaxCommStage = tmp_fcm_stage;
	}
	else {		/**	おかしな応答を受信（PPS-NULLに対してＰＩＰを受信など）	*/
		/*
		** リダイヤル時に、次のページから送ってしまうためページ更新フラグをクリア
		**	1997/10/23 By T.Yamaguchi
		*/
		UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
		TransmitError( 0x41, 1 );	/**	Ｔ．４．１をセット	*/
		FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
	}
}


/*************************************************************************
	module		:[ＰＩＮ受信時の処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/12/05]
	author		:[山口　哲治]
*************************************************************************/
void FCM_PIN_Received(UBYTE tmp_tx_fcf)
{
	UBYTE	voice_result;		/*	被会話予約結果	*/
	UBYTE	tmp_fcm_stage;		/*	被会話予約での通信状態遷移の待避用	*/
	UBYTE	voice_tout_mode;	/*	会話予約処理時のタイムアウト処理指定	*/
				/*	MODE_T3_TIMER		:Ｔ３タイムアウトのみ				*/
				/*	MODE_T3_T1_TIMER	:Ｔ３の後，Ｔ１タイマで命令受信待ち	*/


	if (!((TxOptionFCF == PPS_F) && (TxFCF == NULL_FF))) {	/**	PPS-NULL以外に対してＰＩＮを受信	*/
		/*----	★ドイツ仕様★	----------------------------*/
		/*	メモリ送信の時は RTN_ReceiveCounter を +1 する	*/
		/*--------------------------------------------------*/
		/*------------------------------*/
		/**	表示切替指示(会話予約中)	*/
		/*------------------------------*/
		/*	SYS_VoiceCallExecuting = 1;	*/
		tmp_fcm_stage = SYS_FaxCommStage;
		SYS_FaxCommStage = FCM_VOICE_CALLED;
		SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );
		/*--------------------------*/
		/**	送信側被会話予約処理	*/
		/*--------------------------*/
		/* Sep.20.1994 */
		if (TxPageFinishStatus == TX_PAGE_END_RCR) {	/*	次は受領証要求の時	*/
			voice_tout_mode = MODE_T3_TIMER;			/*	ＤＩＳはAutoFax()で受ける	*/
		}
		else {
			voice_tout_mode = MODE_T3_T1_TIMER;
		}
#if (PRO_LINENUMBER == TWICE_LINE) && !defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/15 */
/* 
** 疑似２回線仕様
** 拡張ラインには会話予約処理がないためPINの処理を変えます
** PINを受信したらすぐにFSK送出処理に移ります
** by T.Soneoka 1997/11/20
*/
		if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	標準ラインにてPINを受信した場合	*/
			voice_result = MDM_TxVoiceReqRcvCmd( voice_tout_mode );
		}
		else {	/**	拡張ラインにてPIN受信時	*/
			voice_result = T3_TIME_OVER;	/**	T3タイムオーバ	*/
		}
#else
		voice_result = MDM_TxVoiceReqRcvCmd( voice_tout_mode );
#endif
		switch (voice_result) {	/**	会話予約結果	*/
		case	TEL1_OH_DETECT:		/**	ＴＥＬ１オフフック検出	*/
		case	TEL2_OH_DETECT:		/**	ＴＥＬ２オフフック検出	*/
		case	HOOK_KEY_OH_DETECT:	/**	オフフックキー検出	*/
			SYS_VoiceCallAccepted = voice_result;	/**	会話予約成立(ＯＨ識別)	*/
			/* Sep.16.1994 */
			if (voice_result == TEL1_OH_DETECT) {
				FaxTelOffHookTEL1Flag = 1;
			}
			else if (voice_result == TEL2_OH_DETECT) {
				FaxTelOffHookTEL2Flag = 1;
			}
			/**	前回のＦＣＦをＰＲＩ－Ｑにして送出 (ＰＰＳ－なし)	*/
			FaxHDLC_Transmit( (UBYTE)(TxFCF | PRI_Q_F), 0 );
			if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {		/**	メモリ送信	*/
				UpdatePageInformationFlag = 0;			/**	ページ更新フラグをクリア	*/
			}
			MemorizeTxErrorPage();	/**	エラーページを記憶	*/
			FaxPhaseE( 4 );			/**	通信終了（ＤＣＮなし）	*/
			break;
		case	FSK_RECEIVE:		/**	命令受信した	*/
			AnalyzeRxPostMessageFrame();	/**	受信フレームの解析	*/
			tmp_tx_fcf = TxFCF & (UBYTE)~PRI_Q_F;
			if (RxFCF == DCN_F) {			/**	ＤＣＮ受信	*/
				MemorizeTxErrorPage();		/**	エラーページを記憶	*/
				FaxPhaseE( 4 );				/**	通信終了（ＤＣＮなし）	*/
			}
			else if (RxFCF == DIS_F) {	/**	ＤＩＳ受信	*/
				if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {	/**	スキャナ送信	*/
					if (tmp_tx_fcf == EOP_F) {	/**	(PPS-/EOR-)(PRI-)EOPを送信した(次ページなし)	*/
						MemorizeTxErrorPage();		/**	エラーページを記憶	*/
						FaxPhaseE( 3 );				/**	通信終了（ＤＣＮあり）	*/
					}
					else {						/**	ＥＯＰ以外を送信した(次ページあり)	*/
						if (TxOptionFCF == EOR_F) {	/**	ＥＯＲ－Ｑを送信した	*/
							if (CHK_AfterEOR() == 0) {	/**	ＥＯＲ－Ｑ送信後，継続する	*/
								FallBackByRTN();			/**	ボーレイトを下げる	*/
								TxRetrainingFlag  = 1;		/**	再トレーニングフラグをセット	*/
								TxModeChangedFlag = 0;		/**	モード変更フラグをクリア	*/
							}
							else {						/**	中断する	*/
								FaxPhaseE( 2 );			/**	通信終了（ＤＣＮあり）	*/
							}
							/* MemorizeTxErrorPage(); May.07.1994	**	エラーページを記憶	*/
						}
						else {						/**	ＥＯＲ－Ｑ以外を送信した	*/
							FallBackByRTN();			/**	ボーレイトを下げる	*/
							MemorizeTxErrorPage();		/**	エラーページを記憶	*/
							TxRetrainingFlag  = 1;		/**	再トレーニングフラグをセット	*/
							TxModeChangedFlag = 0;		/**	モード変更フラグをクリア	*/
						}
					}
				}
				else {		/**	メモリ送信	*/
					if (tmp_tx_fcf == EOP_F) {		/**	(PPS-/EOR-)(PRI-)EOPを送信した(次ページなし)	*/
						if ((TxBaudRate == BPS2400_V27)		/**	2400bpsで送信	*/
						||	(FCM_PtnrChkRTN_NoReTransmit())) {	/* Nov.12.1996	By T.Yamaguchi */
							/*----	★ドイツ仕様★	--------------------------------*/
							/*	RTN_ReceiveCounter>3 の時もここを通し，クリアする	*/
							/*------------------------------------------------------*/
							MemorizeTxErrorPage();			/**	エラーページを記憶	*/
							FaxPhaseE( 3 );					/**	通信終了（ＤＣＮあり）	*/
						}
						else {							/**	4800bps以上で送信	*/
							FallBackByRTN();				/**	ボーレイトを下げる	*/
							TxRetrainingFlag  = 1;			/**	再トレーニングフラグをセット	*/
							TxModeChangedFlag = 0;			/**	モード変更フラグをクリア	*/
							UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
						}
					}
					else {		/**	ＥＯＰ以外を送信した(次ページあり)	*/
						if (TxBaudRate == BPS2400_V27) {	/**	2400bpsで送信	*/
							if (TxOptionFCF == EOR_F) {		/**	ＥＯＲ－Ｑを送信した	*/
								if (CHK_AfterEOR() == 0) {		/**	ＥＯＲ－Ｑ送信後，継続する	*/
									TxRetrainingFlag  = 1;		/**	再トレーニングフラグをセット	*/
									TxModeChangedFlag = 0;		/**	モード変更フラグをクリア	*/
								}
								else {							/**	中断する	*/
									FaxPhaseE( 2 );				/**	通信終了（ＤＣＮあり）	*/
								}
								/* MemorizeTxErrorPage(); May.07.1994	**	エラーページを記憶	*/
								/*----	★ドイツ仕様★	------------*/
								/*	RTN_ReceiveCounter をクリアする	*/
								/*----------------------------------*/
							}
							else {							/**	ＥＯＲ－Ｑ以外を送信した	*/
								MemorizeTxErrorPage();			/**	エラーページを記憶	*/
								TxRetrainingFlag  = 1;			/**	再トレーニングフラグをセット	*/
								TxModeChangedFlag = 0;			/**	モード変更フラグをクリア	*/
							}
						}
						else {		/**	4800bps以上で送信	*/
							FallBackByRTN();				/**	ボーレイトを下げる	*/
							TxRetrainingFlag  = 1;			/**	再トレーニングフラグをセット	*/
							TxModeChangedFlag = 0;			/**	モード変更フラグをクリア	*/

							if (!FCM_PtnrChkRTN_NoReTransmit()) {	/* Nov.12.1996	By T.Yamaguchi */
								UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
							}
							else {
								MemorizeTxErrorPage();
							}

							/*----	★ドイツ仕様★	--------------------------------------------*/
							/*	RTN_ReceiveCounter<=3 の時は，ページ情報を更新しない			*/
							/*					  > 3 の時は，エラーページを記憶してクリアして	*/
							/*								  ページ情報を更新する				*/
							/*------------------------------------------------------------------*/
						}
					}
				}
			}
			else {		/**	ＤＣＮ／ＤＩＳ以外を受信	*/
				MemorizeTxErrorPage();	/**	エラーページを記憶	*/
				FaxPhaseE( 2 );			/**	通信終了（ＤＣＮあり）	*/
			}
			break;
		case	T3_TIME_OVER:	/**	Ｔ３タイムアウト	*/
			/*------------------------------------------------------------------*/
			/*	次に受領証を要求する時だけここを通る			Sep.20.1994		*/
			/*	以下の処理の後，フェーズＢでＤＩＳを受けＤＴＣ送出する			*/
			/*		1)	エラーページとして登録する (最終ページでも再送しない)	*/
			/*		2)	2400bpsなら通信終了し，それ以上ならフォールバックする	*/
			/*------------------------------------------------------------------*/
			MemorizeTxErrorPage();			/**	エラーページを記憶	*/
			if (TxBaudRate == BPS2400_V27) {	/**	2400bpsで送信	*/
				FaxPhaseE( 1 );					/**	通信終了（ＤＣＮあり）	*/
			}
			else {								/**	4800bps以上で送信	*/
				/**	ボーレイトを下げ，受領証受信時の受信可能ボーレイトにする	*/
				FallBackByRTN();
				AvailableRxBaudRate = AvailableTxBaudRate;
			}
			break;
		case	T1_TIME_OVER:	/**	Ｔ３の後，Ｔ１タイムアウト	*/
			MemorizeTxErrorPage();	/**	エラーページを記憶	*/
#if defined(FRA)				/* 1995/95/06 by M.HARADA */
			if (TxPageFinishStatus == TX_END) {
				FaxPhaseE( 2 );			/**	通信終了（ＤＣＮあり）	*/
			}
			else {
				TxRetrainingFlag = 1;
				FRA_PIP_PIN_Rx_Flag = 1;
				FallBackByRTN();			/* 95/05/15 BY M.HARADA */
			}
#else
			FaxPhaseE( 2 );			/**	通信終了（ＤＣＮあり）	*/
#endif
			break;
		default:				/**	エラー検出 (FSK_ERROR)	*/
			MemorizeTxErrorPage();	/**	エラーページを記憶	*/
			FaxPhaseE( 2 );			/**	通信終了（ＤＣＮあり）	*/
			if ((SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) /**	メモリ送信	*/
			&&	((TxOptionFCF == PPS_F) || (TxOptionFCF == 0))
			&&	(tmp_tx_fcf == EOP_F)) {	/**	メモリ送信&&(PPS-)(PRI-)EOPを送信した	*/
				UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
			}
			break;
		}
		SYS_FaxCommStage = tmp_fcm_stage;
	}
	else {		/**	おかしな応答を受信（PPS-NULLに対してＰＩＮを受信など）	*/
		/*
		** リダイヤル時に、次のページから送ってしまうためページ更新フラグをクリア
		**	1997/10/23 By T.Yamaguchi
		*/
		UpdatePageInformationFlag = 0;	/**	ページ更新フラグをクリア	*/
		TransmitError( 0x41, 1 );	/**	Ｔ．４．１をセット	*/
		FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
	}
}


/*************************************************************************
	module		:[おかしな信号受信時の処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/06/12]
	author		:[山口　哲治]
*************************************************************************/
void PreAnalyzePostMessage(void)
{
	UBYTE	tmp_tx_fcf;			/*	PRI-QビットをマスクしたTxFCF	*/
	UBYTE	fcf_1;

	/*------------------------------*/
	/*	RxFCF / RxOptionFCF セット	*/
	/*------------------------------*/
	fcf_1 = CheckReceivedFCF();		/**	受信フレームを確認し，セットする	*/

	/**	PRI-Qビットをマスクしてテンポラリにセット	*/
	tmp_tx_fcf = TxFCF & (UBYTE)~PRI_Q_F;

	/* check invalid signal */
	if(TxECM_Mode == ECM_ON){	/* ECM mode */
		/*
		** ＥＯＲ信号に対して、RNR、ERR、PIN以外の信号を受信した場合回線断する
		*/
		if(TxOptionFCF == EOR_F) {
			switch (RxFCF) {
			case	RNR_F:
			case	ERR_F:
			case	DCN_F:			/* 1999/09/03 Y.Murata NAGANOより1999/10/21 Y.Murata */
				break;
			case	PIN_F:
				if (tmp_tx_fcf == NULL_FF) {
					ReceiveResponseFlag = 0;	/* go to out of 'while' as 'R.4.1' */
				}
				break;
			default:
				ReceiveResponseFlag = 0;	/* go to out of 'while' as 'R.4.1' */
				break;
			}
		}
	} 
	else {		/* non-ECM mode */
		/*
		** Ｇ３送信の時におかしな信号を受け取った場合回線断する
		*/
		switch (RxFCF) {
		case	PIN_F:
		case	PIP_F:
		case	MCF_F:
		case	RTP_F:
		case	RTN_F:
		case	DCN_F:			/* 1999/09/03 Y.Murata NAGANOより 1999/10/21 Y.Murata */
			/* 何もしない */
			break;
		default:
			ReceiveResponseFlag = 0;	/* go to out of 'while' as 'R.4.1' */
			break;
		}
	}
}
