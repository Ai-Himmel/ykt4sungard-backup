/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMRXD.C													 */
/*	モジュール	 :															 */
/*				 : FaxRxPhaseD()											 */
/*				 : AnalyzeRxPostMessageFrame()								 */
/*				 : CheckReceivedFCF()										 */
/*				 : TransmitRNR()											 */
/*				 : RxRespondPostMessage()									 */
/*				 : ReceiveDCS()												 */
/*				 : RxRequestedVoiceMode()									 */
/*				 : TransmitPIP()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 :															 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\syst30.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\sysdoc.h"

#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */

#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\fcm_data.h"

#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE) 96/1/11 Y.S */
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

#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\message.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\ext_v\atd_tbl.h"
#include	"\src\atlanta\ext_v\atd_data.h"
#include	"\src\atlanta\define\uni_pro.h"

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
#include	"\src\atlanta\ext_v\bkupram.h"	/* Add by 1998/03/31  By T.Yamaguchi */
#endif
#if (PRO_PRINTER_RX == ENABLE)
	#include "\src\atlanta\define\unisw_c.h"	/* added by H.Hirao 1998/12/25 */
 #if (PRO_PRINT_TYPE == THERMAL)	/* Add By O.Kimoto 1998/10/28 */
	#include "\src\atlanta\define\mntsw_h.h"	/* Endmark3 by O.Kimoto 1999/02/19 */
  #if defined(STOCKHM2)
  	#include "\src\atlanta\prt\lv_therm\ext_v\prt_data.h"	/* Endmark3 by O.Kimoto 1999/02/19 */
  #else
 	#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"	/* Endmark3 by O.Kimoto 1999/02/19 */
  #endif
 #endif
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/17 K.Kawata */
#include "\src\atlanta\define\unisw_c.h"
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#endif

/*************************************************************************
	module		:[受信フェーズＤ]
	function	:[
		1.	送信側からの受信命令を解析する
		2.	ＰＲＩ－Ｑ受信による被会話予約処理を行う
		3.	ＲＮＲ送信－ＲＲ受信を行う
		4.	受信ページをクローズする(メモリ受信では，印字開始指示する)
		5.	受信側の会話予約処理を行う
		.	(この場合ポストメッセージのハンドシェーク(6)には移らない)
		6.	応答送信する
		※	プリンタ受信→代行受信不可の場合は会話予約をかける	Jun.22.1994
	]
	return		:[]
	common		:[
		FaxComPerformingFlag		RxPageFinishStatus
		RxFCF		RxOptionFCF		RxECM_Mode
		PRI_Q_RxFlag				RxEOR_ReceiveFlag
		RxEOM_ReceiveFlag			RxEOP_ReceiveFlag
		RxModeChangeRequestedFlag	RxWholePageCompletedFlag
		SYS_DocBlock				MDM_PhaseC_Status
		SYS_VoiceSwitch				SYS_VoiceCallAccepted
	]
	condition	:[]
	comment		:[
		次ページをメモリ受信続行不可の場合は
		会話予約をかける	(Aug.22.1994)
		FX 独自ポストメッセージ EOMX の処理追加（受信のみ）(Sep.17.1994) Y.Suzuki
		1.EOMX の FCF フォーマットは、 EOR(0x73) と同じ テーブルは、EOMX_F を使用
		2.EOMX 受信時の動作は、EOM 受信時と同じ
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/20]
	author		:[竹内茂樹]
*************************************************************************/
void FaxRxPhaseD( void )
{
	UBYTE	tmp_rx_fcf;
	UBYTE	voice_result;		/*	会話予約結果	*/
	UBYTE	voice_chk_flag;
	UBYTE	tmp_fcm_stage;		/*	被会話予約での通信状態遷移の待避用	*/
	UBYTE	f_mem_rx_continue;	/*	メモリ受信続行可能フラグ	*/
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
	UWORD	debug_sum;
#endif

	FaxComPhaseStatus = FAX_RX_PH_D;
	voice_chk_flag = 0;
	f_mem_rx_continue = 1;

	/**	表示切替指示(ポストメッセージ受信)	*/
	SYS_FaxCommStage = FCM_ERROR_LINE;		/*	"エラーライン／受信ライン"表示用	Jul.14.1994	*/
	SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );

#if 0	/* フェーズＣのRxECM_PixData()内に移動	Oct.31.1994 */
	/**	受信ポストメッセージの解析	*/
	AnalyzeRxPostMessageFrame();
#endif
	/**	PRI-Qビットをマスクしてテンポラリにセット	*/
	tmp_rx_fcf = RxFCF & (UBYTE)~PRI_Q_F;

	/*--------------------------------------*/
	/*	ＰＰＳ－ＮＵＬＬ／ＥＯＲ－ＮＵＬＬ	*/
	/*--------------------------------------*/
	if (((RxOptionFCF == PPS_F) || (RxOptionFCF == EOR_F))
	&&	(RxFCF == NULL_FF)) {	/**	PPS-NULL / EOR-NULL受信	*/
		if (RxEOR_ReceiveFlag == 0) {		/**	PPS-NULL受信	*/
			TransmitRNR();		/**	ＲＮＲ送信－ＲＲ受信	*/
			/*------------------------------------------------------*/
			/*	EOR-NULLを受信した時は,既にPPRを送出しているので	*/
			/*	デコードは止まっているはず							*/
			/*------------------------------------------------------*/
		}

		/*	ＲＴＣがＥＣＭのブロック間にまたがった時で，現ブロック内に	*/
		/*	規定数のＥＯＬを検出しＲＴＣ検出した場合に，次のブロックの	*/
		/*	残りのＥＯＬを受け捨てるためにフラグを立てる	Sep.16.1994	*/
		if (RxPageFinishStatus == RX_PAGE_END) {	/**	ＥＣＭ６４Ｋ間ＲＴＣ股裂きの時	*/
			MDM_RTC_SeparateFlag = 1;				/**	ＲＴＣ股裂き処理フラグをセット	*/
		}

		if (((RxPageFinishStatus == RX_BLOCK_END) || (RxPageFinishStatus == RX_PAGE_END) || (RxEOR_ReceiveFlag == 1))
		&&	(FaxComPerformingFlag == 1)) {		/**	ブロックエンド||ＥＯＲ受信	*/
			/* Sep.22.1994 */
			/**	応答送信し，ＥＯＲ受信フラグをクリア	*/
			RxRespondPostMessage();
			RxEOR_ReceiveFlag = 0;

#if (PRO_PRINTER_RX == ENABLE)	/*	もみじ／さつき／ラベンダ	*/
			/*--------------------------------------------------------------*/
			/*	部分ページでプリンタエラーの時は RxRespondPostMessage() で	*/
			/*	ＤＣＮを送出し回線断するので MDM_BreakRxTask() が必要		*/
			/*--------------------------------------------------------------*/
			if ((RxPmType == RX_PRINTER)
			&&	(RxPageFinishStatus == RX_BLOCK_END)
			&&	(FaxComPerformingFlag == 0)) {		/**	ＥＣＭプリンタ受信でプリンタエラーの時	*/
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE)  96/1/11 Y.S */
				SCDC_BreakRxTask();					/**	ＥＣＭタスク停止	*/
#else /* 96/1/11 Y.S */
				MDM_BreakRxTask();					/**	ＥＣＭタスク停止	*/
#endif /* 96/1/11 Y.S */
			}
#endif
		}
		else {		/**	部分ページ受信時のエラー	*/
			/*------------------*/
			/*	ページクローズ	*/
			/*------------------*/
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE)  96/1/11 Y.S */
			SCDC_BreakRxTask();					/**	ＥＣＭタスク停止	*/
#else /* 96/1/11 Y.S */
			MDM_BreakRxTask();					/**	ＥＣＭタスク停止	*/
#endif /* 96/1/11 Y.S */
			/*	↑これは後(RxCの最後)でする Jul.11.1994	← やっぱり必要 Jul.25.1994 */
			if (RxPmType == RX_MEMORY) {	/**	メモリ受信	*/
				/**	メモリファイルクローズし，受信ページ削除	*/
/* #if (PRO_MULTI_LINE == ENABLE)	/@ 1997/01/10 Y.Murata */
				if (SYS_FaxComIndexConflictStatus == 0) {
					MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );	/* Jul.04.1994 */
				}
/* #else */
/*				MEM_ClearPageAndFATArea( &SYS_DocBlock.Index ); */
/* #endif */
			}
			/**	エラーコードをセット	*/
			CheckRxPixResultSub();
			/*	↓を↑に変更 Jul.20.1994	RX_CONTINUEの時は，TransmitRNR()でR.5.1にするので	*/
			/*	CheckRxPixResultPhaseD();	*/

			/* 2000/02/12 Y.Murata
			 * デコードエラーでも手順が継続してしまう
			*/
			if (FaxComPerformingFlag == 1) {	/**	通信中	*/
				/*--------------*/
				/**	応答送信	*/
				/*--------------*/
				if (RxPageFinishStatus == RX_ERROR) {			/**	画質不良	*/
					RxRespondPostMessage();
				}
			}

		}
	}
	/*------------------------------------------------------*/
	/*	（ＰＰＳ／ＥＯＲ／ＰＲＩ－）ＭＰＳ，ＥＯＭ，ＥＯＰ	*/
	/*------------------------------------------------------*/
	else if ((tmp_rx_fcf == MPS_F) || (tmp_rx_fcf == EOM_F) || (tmp_rx_fcf == EOP_F) || (tmp_rx_fcf == EOMX_F)) {	/**	MPS / EOM /EOMX / EOP受信	*/
		if (tmp_rx_fcf == MPS_F) {		/**	ＭＰＳ受信	*/
			/**	ＤＩＳ受信フラグクリア	*/
			/* DIS_ReceivedFlag = 0;	ここでクリアするのはまずい 1997/06/12  By T.Yamaguchi */
		}
		else if ((tmp_rx_fcf == EOM_F) || (tmp_rx_fcf == EOMX_F)) {	/**	ＥＯＭまたはＥＯＭＸ	*/
			/**	モード変更要求フラグと		**
			***	ＥＯＭ受信フラグをセット	*/
			RxModeChangeRequestedFlag = 1;
			RxEOM_ReceiveFlag = 1;
		}
		else if (tmp_rx_fcf == EOP_F) {	/**	ＥＯＰ	*/
			/**	モード変更要求フラグ(フェーズＢのループ脱出のため)と	**
			***	ＥＯＰ受信フラグをセット								*/
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/03/31  By T.Yamaguchi */
			if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
				/* debug_sum = SumCheck((UWORD *)0x1000000,(UDWORD)0x80000);	*/ /* 1700msかかっている */
				/* debug_sum = SumCheck((UWORD *)ROM_DATA_WRITE_ADDRESS,(UDWORD)0x80000);	*/	/* 1700msかかっている */
				/* if (SYB_ROM_DataSumcheck != debug_sum) {	*/
				if (FCM_ROMDataSum != SYB_ROM_DataSumcheck) {
					MDM_PhaseC_Status = RX_ERROR;
					FaxComResult = RECEIVEERROR;
				}
			}
			if (SYS_FaxComType == SYS_REMOTE_DIAG) {	/* ﾘﾓｰﾄ診断時は会話予約しない 1998/04/07  By T.Yamaguchi */
				voice_chk_flag = 1;
			}
#endif
			RxModeChangeRequestedFlag = 1;
			RxEOP_ReceiveFlag = 1;
		}

	#if 0 /*(PRO_CODEC_TYPE == IDP301) */
		EcmPageEndFlag = 1;		/* RNR Bug.	 Nov.25.1994 */
	#endif

		if (PRI_Q_RxFlag) {		/**	ＰＲＩ－Ｑ受信	*/
			/*------------------------------*/
			/**	表示切替指示(会話予約中)	*/
			/*------------------------------*/
			tmp_fcm_stage = SYS_FaxCommStage;
			SYS_FaxCommStage = FCM_VOICE_CALLED;
			SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );
			/*--------------------------*/
			/**	受信側被会話予約処理	*/
			/*--------------------------*/
			voice_result = MDM_RxVoiceReqFromTxRcvCmd();
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
#if (PRO_PAPER_TYPE == ROLL_PAPER)
				/*	ＰＲＩ－Ｑ受信時は，ここでカット待ちと		*/
				/*	プリンタエラーのチェックをする	Oct.31.1994	*/
				if (RxPmType == RX_PRINTER) {		/**	プリンタ受信の場合	*/
					WaitRxPaperCut( 25 );				/**	記録紙カット待ち(２．５秒)	*/
					CheckRxPrinterError();				/**	プリンタエラーの種類を確認	*/
				}
#endif
				/*----------------------------------------------*/
				/**	ＰＩＰ／ＰＩＮ送出し，通信終了(ＤＣＮなし)	*/
				/*----------------------------------------------*/
				TransmitPIP();
				FaxPhaseE( 4 );
				/*------------------------------------------*/
				/**	３００msウェイト後，Ｈ／ＬリレーＯＦＦ	*/
				/*------------------------------------------*/
				FaxTimer( 300 );
				FaxTelAutoSWAfterTransaction();
				break;
			case	FSK_RECEIVE:		/**	ＰＲＩ－Ｑ３回／その他命令受信	*/
				/*--------------------------------------------------------------*/
				/**	ＰＲＩ－Ｑ３回受信の場合は，最初の受信命令に対して処理する	*/
				/*--------------------------------------------------------------*/
				break;
			default:					/**	ＦＳＫエラー／Ｔ３タイムアウト	*/
				/*--------------------------------------*/
				/**	Ｒ．４．２で，ＤＣＮ送出し通信終了	*/
				/*--------------------------------------*/
				ReceiveError( 0x42 );
				FaxPhaseE( 1 );
				break;
			}
			SYS_FaxCommStage = tmp_fcm_stage;
			/*------------------------------------------------------*/
			/*	被会話予約処理を行った場合は						*/
			/*	受信側会話予約要求の処理は行わない (松竹桜と同じ)	*/
			/*------------------------------------------------------*/
			voice_chk_flag = 1;
		}

		RxWholePageCompletedFlag = 1;	/**	物理ページ受信完了フラグセット	*/

		if (RxEOR_ReceiveFlag == 1) {	/**	ＥＯＲ－Ｑを受信した	*/
			RxEOR_ReceiveFlag = 0;		/**	ＥＯＲ受信フラグクリア	*/
		}
		else {							/**	ＥＯＲ－Ｑを受信していない	*/
			/*--------------------------*/
			/**	ＲＮＲ送信－ＲＲ受信	*/
			/*--------------------------*/
			TransmitRNR();

			/*--------------------------*/
			/*	ＥＣＭ受信タスクを停止	*/
			/*--------------------------*/
			if ((RxECM_Mode == ECM_ON)
			&&	((RxPageFinishStatus == RX_CONTINUE) || (RxPageFinishStatus == RX_BLOCK_END))) {		/**	ＥＣＭタスク動作中	*/
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE) 96/1/11 Y.S */
				SCDC_BreakRxTask();					/**	ＥＣＭタスク停止	*/
#else /* 96/1/11 Y.S */
				MDM_BreakRxTask();					/**	ＥＣＭタスク停止	*/
#endif /* 96/1/11 Y.S */
#if 0			/* 上記条件に RX_CONTINUE を追加 (↓の場合RxCでMDM_BreakRxTaskしないので)	Aug.18.1994 */
				/*	RX_CONTINUEの時は，TransmitRNR()でR.5.1になっているので	**
				**	この場合はRxCの最後でMDM_BreakRxTask()する	Jul.20.1994	*/
#endif
			}

			if ((RxPageFinishStatus == RX_PAGE_END)
			||	(RxPageFinishStatus == RX_BLOCK_END)
			||	((RxPageFinishStatus == RX_TMOUT) && (RxECM_PixTimeoutFlag == 1))
				/* ↑この条件は要確認 (ＥＣＭタイムアウトではカウントするのはおかしい？)  Nov.24.1994 */
			||	((RxPageFinishStatus == RX_ERROR) && (RxECM_Mode == ECM_OFF))	/* ←にＧ３の条件をandで追加  Oct.15.1994 */
			||	(RxPageFinishStatus == RX_PRT_ERR)) {	/**	ページエンド,画質エラー,プリンタエラー	*/
				/*	↑ＥＣＭ受信タイムアウト回避設定でタイムアウトした時の条件を追加			*/
				/*	タイムアウト回避の処理で，フレームは正常でＲＣＰだけ壊れて	*/
				/*	タイムアウトした時の対応 (橘氏より)			Sep.16.1994		*/
				/**	受信ページ数，メモリファイルページ数を＋１	*/
				SYS_RxTotalPage++;
				SYS_RxMemoryFilePage++;
				SYS_RxPrintFilePage++;
				if ((SYS_RxMemoryFileItem == SYS_MEM_RX_FILE)
				||	(SYS_RxPrintFileItem == SYS_MEM_RX_FILE)) {		/**	標準メモリ受信||メモリデュアルオープン原稿||バッファリング受信	*/
					/*	デュアルオープンの条件追加		Jun.14.1994	*/
					/*	バッファリング受信の条件追加	Jul.06.1994	*/
					/**	メモリ受信１ページ終了をメインタスクへ通知	*/
					SendMsgFaxComToMain( MSG_RX_PRINT_PAGE );
				}
			}
			else {
				/* Oct.15.1994	以下の処理をif()の外から移動 */
				/**	メモリ受信で異常ページの場合は，受信ページを削除	*/
				if (RxPmType == RX_MEMORY) {
/* #if (PRO_MULTI_LINE == ENABLE)	/@ 1997/01/10 Y.Murata */
					if (SYS_FaxComIndexConflictStatus == 0) {
						MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );	/* Jul.04.1994 */
					}
/* #else */
/*					MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );  */
/* #endif */
				}

				/**	エラーコードをセット	*/
				CheckRxPixResultSub();
				/*	↓を↑に変更 Jul.20.1994	RX_CONTINUEの時は，TransmitRNR()でR.5.1にするので	*/
				/*	CheckRxPixResultPhaseD();	*/
			}
		}

		/*--------------------------------------------------------------*/
		/**	次ページをメモリ(バッファリング)受信続行できるかのチェック	*/
		/*--------------------------------------------------------------*/
		if	(tmp_rx_fcf != EOP_F) {		/**	次ページ有り	*/

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/14 Y.Murata for KAKI */
			if (((SYS_RxMemoryFileItem == SYS_MEM_RX_FILE) || (SYS_RxPrintFileItem == SYS_MEM_RX_FILE))
			&&	((CMN_CheckMemoryForMemRx() == 0) || (MEM_CountTotalEmptyPage() <= 0))){	/*	代行受信続行不可	*/
				if (CHK_UNI_MemoryOverRx()) {
					f_mem_rx_continue = 0;
				}
				else {
					/* 次ページをメモり受信できない場合 会話予約していたが、通常のメモリオーバー時の処理と同じにする */
					f_mem_rx_continue = 1;
				}
			}
#else
			if (((SYS_RxMemoryFileItem == SYS_MEM_RX_FILE) || (SYS_RxPrintFileItem == SYS_MEM_RX_FILE))
			&&	(((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) <= SYS_MEMORY_EMPTY_BLOCK) || (MEM_CountTotalEmptyPage() <= 0))){	/*	代行受信続行不可	*/
				if (CHK_UNI_MemoryOverRx()) {
					f_mem_rx_continue = 0;
				}
				else {
					/* 次ページをメモり受信できない場合 会話予約していたが、通常のメモリオーバー時の処理と同じにする */
					f_mem_rx_continue = 1;
				}
			}
#endif
#if (PRO_PRINTER_RX == ENABLE)
			else if ((RxPrinterErrorFlag == 1)
			&&		 (RxECM_Mode == ECM_OFF)
			&&		 (!CMN_CheckMemoryReceiveEnable())) {	/*	プリンタ受信→代行受信切り替え不可 (Ｇ３のみ)	*/
				f_mem_rx_continue = 0;
				/*	ＥＣＭ受信では，この場合でも会話予約しない	Sep.08.1994	*/
			}
			/*
			** 強制プリンタ受信設定の場合、プリンタ受信から代行受信の切り替え不可（Ｇ３のみ）
			** added by H.Hirao 1998/12/25
			*/
			else if ((RxPrinterErrorFlag)
				  && (RxECM_Mode == ECM_OFF)
				  && (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX)) {
				f_mem_rx_continue = 0;
			}
#endif
#if (PRO_MEM_RX_REJECT == ENABLE)		/* Oct.19.1994 */
			else if ((RxPrinterErrorFlag == 1)
			&&		 (CHK_MemoryReceiveReject())) {		/*	プリンタ受信エラーでメモリ受信拒否設定	ﾒﾓﾘｽｲｯﾁ削除 '96.04.15 */
				f_mem_rx_continue = 0;
			}
#endif
		}
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/10 K.Kawata */
			if (((CHK_UNI_V34ReceiveType() == V34_PRX_TO_PRX) || (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX))
				&& (RxECM_Mode == ECM_OFF)
				&& (PRN_Control.Error)) {
				f_mem_rx_continue = 0;
			}
#endif
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1998/01/08 */
		if (((CMN_GetVoiceSwitch()) && (voice_chk_flag == 0))
		||	(!SYS_V34ProcedureExecuting() && (f_mem_rx_continue == 0)) ) {		/**	会話予約キー||メモリ受信続行不可	*/
		/* The above condition for V34 is added by H.Kubo 1998/02/14 */
			/*--------------------------------------*/
			/**	受信側会話予約要求処理し，リターン	*/
			/*--------------------------------------*/
			RxRequestedVoiceMode( f_mem_rx_continue );
			return;
		}
#else
		if (((SYS_VoiceSwitch == 1) && (voice_chk_flag == 0))
		||	(f_mem_rx_continue == 0)) {		/**	会話予約キー||メモリ受信続行不可	*/
			/*--------------------------------------*/
			/**	受信側会話予約要求処理し，リターン	*/
			/*--------------------------------------*/
			RxRequestedVoiceMode( f_mem_rx_continue );
			return;
		}
#endif /* (PRO_TX_SPEED == V34) */

		if (FaxComPerformingFlag == 1) {	/**	通信中	*/
			/*--------------*/
			/**	応答送信	*/
			/*--------------*/
			RxRespondPostMessage();
		}
	}
	/*--------------------------*/
	/*	ＤＣＮ，その他の命令	*/
	/*--------------------------*/
	else {
		if (((RxPageFinishStatus == RX_CONTINUE) || (RxPageFinishStatus == RX_BLOCK_END))
		&&	(RxECM_Mode == ECM_ON)) {		/**	ＥＣＭタスク動作中	*/
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE) 96/1/11 Y.S */
			SCDC_BreakRxTask();					/**	ＥＣＭタスク停止	*/
#else /* 96/1/11 Y.S */
			MDM_BreakRxTask();					/**	ＥＣＭタスク停止	*/
#endif /* 96/1/11 Y.S */
			/*	↑これは後(RxCの最後)でする Jul.11.1994	← やっぱり必要 Jul.25.1994 */

			/*------------------*/
			/*	ページクローズ	*/
			/*------------------*/
			if (RxPmType == RX_MEMORY) {	/**	メモリ受信	*/
/* #if (PRO_MULTI_LINE == ENABLE)	/@ 1997/01/10 Y.Murata */
				if (SYS_FaxComIndexConflictStatus == 0) {
					MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );	/* Jul.04.1994 */
				}
/* #else */
				/**	受信ページ削除	*/
/*				MEM_ClearPageAndFATArea( &SYS_DocBlock.Index ); */
/* #endif */
			}
		}
		ReceiveError( 0x42 );	/**	Ｒ．４．２	*/
		if (RxFCF == DCN_F) {	/**	ＤＣＮを受信	*/
			FaxPhaseE( 4 );		/**	通信終了（ＤＣＮなし）	*/
		}
		else {
			FaxPhaseE( 1 );		/**	通信終了（ＤＣＮあり）	*/
		}
	}

	if ((FaxComPerformingFlag == 1)
	&&	(RxModeChangeRequestedFlag == 1)) {		/**	通信中&&モード変更要求あり	*/
		ReceiveDCS();							/**	ＤＣＳ受信待ち	*/
	}
}


/*************************************************************************
	module		:[受信ポストメッセージ（命令／応答）解析]
	function	:[
		1.	受信フレームをＦＣＦにセットする
		2.	ＰＰＲの場合は，ＦＩＦで指定されたフレームをエラーフレームの
		.	配列"MDM_EcmStatus"にコピーする
		3.	ＰＲＩ－Ｑメッセージの場合は，ＰＲＩ－Ｑフラグをセットする
	]
	return		:[]
	common		:[
		RxFCF		RxOptionFCF
		PRI_Q_RxFlag		:ＰＲＩ－Ｑメッセージ受信フラグ
		PRI_Q_RxCount		:ＰＲＩ－Ｑメッセージ受信カウンタ
		FCF_Point			:モデムバッファ内のＦＣＦの位置
		MDM_ModemBuffer
		MDM_EcmStatus
	]
	condition	:[]
	comment		:[
		修正履歴
		94/12/05 (桐のみ)ＦＸ手順ＲＴＮ返送時、ＤＣＳと同様の待ち方でＮＳＳを待たねばならない。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/22]
	author		:[竹内茂樹]
*************************************************************************/
void	AnalyzeRxPostMessageFrame( void )

{
	UBYTE	count;
	UBYTE	fcf_1;

	/*------------------------------*/
	/*	RxFCF / RxOptionFCF セット	*/
	/*------------------------------*/
	fcf_1 = CheckReceivedFCF();		/**	受信フレームを確認し，セットする	*/

	/*------------------------------------------*/
	/*	ＰＰＲのＦＩＦをMDM_EcmStatus[]にセット	*/
	/*------------------------------------------*/
	if (fcf_1 == PPR_F) {		/**	ＰＰＲ受信	*/
		/**	ＥＣＭエラーフレームをMDM_EcmStatus[]にコピー	*/
		for (count = 0; count < ECM_STATUS_MAX; count++) {
			MDM_EcmStatus[count] = MDM_ModemBuffer[FCF_Point][count+3];
		}
	}

	/*----------------------*/
	/**	ＦＣＦ種別チェック	*/
	/*----------------------*/
	switch (RxFCF) {
	case	DIS_F:
		RxFrameMessage1 = INITIAL_IDENTIFICATION;
		break;
	case	DTC_F:
		RxFrameMessage1 = COMMAND_TO_SEND;
		break;
	case	DCS_F:
#if(PRO_MAKER == FX)
	case	NSS_F:
#endif
		RxFrameMessage1 = COMMAND_TO_RECEIVE;
		break;
	case	CFR_F:
	case	FTT_F:
		RxFrameMessage1 = PRE_MESSAGE_RESPONSE_SIGNALS;
		break;
	case	EOM_F:
	case	EOMX_F:
	case	MPS_F:
	case	EOP_F:
	case	PRI_EOM_F:
	case	PRI_EOMX_F:
	case	PRI_MPS_F:
	case	PRI_EOP_F:
	case	RR_F:
		RxFrameMessage1 = POST_MESSAGE_COMMANDS;
		break;
	case	MCF_F:
	case	RTP_F:
	case	RTN_F:
	case	PIP_F:
	case	PIN_F:
	case	RNR_F:
	case	ERR_F:
		RxFrameMessage1 = POST_MESSAGE_RESPONSES;
		break;
	case	DCN_F:
	case	CRP_F:
		RxFrameMessage1 = OTHER_LINE_CONTROL_SIGNALS;
		break;
	}

	/*--------------------------------------*/
	/*	ＰＲＩ－Ｑフレームかどうかチェック	*/
	/*--------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE) && !defined (KEISATSU)
/*
** 疑似２回線仕様
** 拡張ラインには会話予約処理がないためPIPの処理を変えます
** PIPを受信したらすぐにFSK送出処理に移ります
** by T.Soneoka 1997/11/20
*/
	if ((SYS_InternalLineNumber == SYS_STD_LINE_COM)	/**	標準ラインにてPIPを受信した場合	*/
	&& ((RxFCF == PRI_MPS_F)
	||	(RxFCF == PRI_EOM_F)
	||	(RxFCF == PRI_EOMX_F)
	||	(RxFCF == PRI_EOP_F))) {	/**	受信フレームがＰＲＩ－Ｑ			**
								***	(PPS-)(PRI-MPS / PRI-EOM / PRI-EOMX / PRI-EOP)	*/
#else
	if ((RxFCF == PRI_MPS_F)
	||	(RxFCF == PRI_EOM_F)
	||	(RxFCF == PRI_EOMX_F)
	||	(RxFCF == PRI_EOP_F)) {	/**	受信フレームがＰＲＩ－Ｑ			**
								***	(PPS-)(PRI-MPS / PRI-EOM / PRI-EOMX / PRI-EOP)	*/
#endif
/**/
#if defined(STOCKHM2)	/* QAT:会話予約変更対応 by SMuratec 夏 2004/11/03 */
	if (CHK_VoiceCallEnable()){
#endif
		PRI_Q_RxFlag = 1;		/**	ＰＲＩ－Ｑ受信フラグをセット	*/
		PRI_Q_RxCount++;		/**	ＰＲＩ－Ｑ回数カウントアップ	*/
#if defined(STOCKHM2)	/* QAT:会話予約変更対応 by SMuratec 夏 2004/11/03 */
	}else{
		PRI_Q_RxFlag  = 0;		/**	ＰＲＩ－Ｑ受信フラグをクリア	*/
		PRI_Q_RxCount = 0;		/**	ＰＲＩ－Ｑ回数クリア	*/
	}
#endif

	}
	else {
		PRI_Q_RxFlag  = 0;		/**	ＰＲＩ－Ｑ受信フラグをクリア	*/
		PRI_Q_RxCount = 0;		/**	ＰＲＩ－Ｑ回数クリア	*/
	}
}


/*************************************************************************
	module		:[受信フレームを変数にセット]
	function	:[
		1.	受信フレームを確認し，RxFCF にセットし，RxOptionFCF はクリアする
		2.	ＰＰＳ－ＱとＥＯＲ－Ｑの場合，ＦＣＦ１は RxOptionFCF にセットし，
		.	ＦＣＦ２は RxFCF にセットする
		3.	ＦＣＦ１をリターンする
	]
	return		:[
		ＦＣＦ１のフレーム
	]
	common		:[
		RxFCF	RxOptionFCF
		MDM_ModemBuffer
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/02/07]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE		CheckReceivedFCF( void )
{
	UBYTE	fcf;

	fcf = CheckHDLC_Command();	/**	受信ＦＣＦ１を確認	*/
	/* 95/03/23 Y.Suzuki */
	if (((fcf == PPS_F) || (fcf == EOR_F)) && (RxECM_Mode == ECM_ON)) {		/**	PPS-? / EOR-? 受信	*/
		/**	ＦＣＦ１を受信拡張ＦＣＦに，
			ＦＣＦ２はＸビットをマスクして受信ＦＣＦにセット	*/
		RxOptionFCF = fcf;
		RxFCF		= MDM_ModemBuffer[FCF_Point][3] & (UBYTE)~X_BIT;
	}
	else {
		/**	ＦＣＦを受信ＦＣＦにセット
			(受信拡張ＦＣＦはクリア)	*/
		RxOptionFCF = 0;
		RxFCF		= fcf;
	}

	/**	ＦＣＦ１をリターン	*/
	return (fcf);
}


/*************************************************************************
	module		:[ＲＮＲ送信－ＲＲ受信]
	function	:[
		1.	ＥＣＭ受信タスクがデコード終了するまで，ＲＮＲ送信－ＲＲ受信
		.	を繰り返す
		2.	ＲＲ／ＰＰＳ－Ｑ以外を受信した場合，または命令受信タイムアウト
		.	の場合はＲ．５．１エラーとする
		3.	上位で既に通信中フラグがクリアされていた場合は，デコード終了
		.	まで３０msごとにＥＣＭタスクの状態をチェックする
		4.	プリンタ受信では，カット待ちとプリンタエラーのチェックをする
		5.	ＥＣＭ受信でないときは何もしない
	]
	return		:[]
	common		:[
		FaxComPerformingFlag	RxECM_Mode
		RxFCF					RxOptionFCF
		ReceiveResponseFlag		RxEOR_ReceiveFlag
		RxPageFinishStatus		MDM_PhaseC_Status
	]
	condition	:[
		ＥＯＲ－Ｑ命令を受信していた場合は，デコードは終わっているので
		これをコールしないこと
	]
	comment		:[
		Nov.17.1994	 プリアンブル短縮フラグの一時キャンセル
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/22]
	author		:[竹内茂樹]
*************************************************************************/
void	TransmitRNR( void )
{
	/*	UBYTE	wait_phase;		*	2=デコード待ち → 1=カット待ち → 0=終了	*/
	/* 上記ローカル変数 wait_phase を大域変数 EcmWaitPhase に変更  Oct.13.1994	*/
	UBYTE	tmp_rx_fcf;

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	UBYTE i;
#endif

	if (RxECM_Mode == ECM_ON) {		/**	ＥＣＭ受信	*/
		/*----------------------------------*/
		/*	待ち状態(EcmWaitPhase)を初期化	*/
		/*----------------------------------*/
		if (MDM_PhaseC_Status == RX_CONTINUE) {	/**	デコード中なら	*/
			EcmWaitPhase = 2;						/**	デコード待ち	*/
		}
		else {
			EcmWaitPhase = 1;						/**	カット待ち	*/
		}

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */

		/* ＪＢＩＧ ＮＥＷＬＥＮ検出遅れ対策 by T.Soneoka 1998/02/19 */
		if (SYS_DocBlock.Src.Code == SYS_JBIG_CODE) {	/** 符号がＪＢＩＧの場合	*/
			tmp_rx_fcf = RxFCF & (UBYTE)~PRI_Q_F;
			if ((tmp_rx_fcf == MPS_F) || (tmp_rx_fcf == EOM_F) || (tmp_rx_fcf == EOP_F) || (tmp_rx_fcf == EOMX_F)) {	/**	MPS / EOM /EOMX / EOP受信	*/
/*
** ちょうどデコードタスクがフレームの最後にエンドマーカがあるフレームをデコード中に
** このＲＮＲ－ＲＲのパスに入ってきた場合、MDM_ForcedDecodeStartフラグを立ててしまう
** １ページの最終フレームの場合だけ、MDM_ForcedDecodeStartフラグを立てないと、デコードエラーを起こす
** （デコードタスクでコーデックへのＤＭＡアドレスとカウンタの設定がおかしくなる）
** if (ECM_FrameCounter == DecodeEcmFrameNum) 文追加
** 1999/03/26 by T.Soneoka
*/
				if (DecodeEcmFrameNum >= MDM_EcmFrameNumber) {
					if (IsDetEndMaker) {
						MDM_ForcedDecodeStart = 1;
					}
					if (IsDetLastFrameEndMaker) {
	/*
	** ＪＢＩＧ受信ループ不具合
	** １ページのデータがちょうど６４ｋｂｙｔｅで、フレーム再送が発生した場合に、
	** 受信フレームコントロールタスクが先に死んでしまい、そうとは知らずにメッセージを
	** 送信してしまうために、ループしてしまう。
	** 対策はメッセージ送信前に受け側がいるかどうかをチェックしてからに変更
	** by Soneoka 1999/03/16
	*/
	#if (0)
	**					MDM_PhaseC_Status = RX_CONTINUE;
	**					ModemMessage.Message = MSG_FORCED_DECODE_START;
	**					snd_msg(mbxno.MDM_RxEcmControlTask, &ModemMessage);
	#else
						if (chk_rcv(mbxno.MDM_RxEcmControlTask)) {
							MDM_PhaseC_Status = RX_CONTINUE;
							ModemMessage.Message = MSG_FORCED_DECODE_START;
							snd_msg(mbxno.MDM_RxEcmControlTask, &ModemMessage);
						}
	#endif
					}
				}
			}
		}
#endif

		/**	プリアンブル短縮を一旦キャンセルする	*/	/* Dec.15.1994 */
		ShorteningPreambleFlag = 0;						/* Dec.15.1994 */

		/*------------------------------*/
		/*	デコード待ち／カット待ち	*/
		/*------------------------------*/
		while (EcmWaitPhase) {		/**	デコード中||カット中	*/

			/*--------------*/
			/*	カット待ち	*/
			/*--------------*/
			if (EcmWaitPhase == 1) {	/**	カット待ち (デコードは終わっている)	*/
#if (PRO_PAPER_TYPE == ROLL_PAPER)	/* 1998/06/02 by T.Soneoka */
				if (RxPmType == RX_PRINTER) {	/**	プリンタ受信の場合	*/
					if (WaitRxPaperCut( 0 ) == 1) {	/**	記録紙カット終了	*/
						/**	ループ(カット待ち)終了	*/
						break;
					}
					/* 6 line  Nov.18.1994 */
					/**	プリンタエラーの種類を確認	*/
					CheckRxPrinterError();
					if (RxPageFinishStatus == RX_PRT_ERR) {	/**	プリンタエラー	*/
						/**	ループ終了	*/
						break;
					}
				}
				else {
					/**	メモリ受信はカット待ちしないのでループ終了	*/
					break;
				}
#else
				break;
#endif
				/*	その他(ループ終了以外)はＲＮＲ－ＲＲ処理へ…	*/
			}
			/*------------------*/
			/*	デコード待ち	*/
			/*------------------*/
			else if (EcmWaitPhase == 2) {	/**	デコード待ち	*/

				if (MDM_PhaseC_Status != RX_CONTINUE) {	/**	デコード終了	*/

					/* 受信ライン0000/0000となる件修正	Nov.25.1994 */
					/**	表示切替指示(ポストメッセージ受信)	*/
					SYS_FaxCommStage = FCM_ERROR_LINE;		/*	"エラーライン／受信ライン"表示用	*/

					SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );

					/**	デコード待ちは終了 (ＲＮＲ－ＲＲ処理せずにループの先頭へ)	*/
					EcmWaitPhase = 1;
					continue;
					/*	ロール紙のプリンタ受信の場合はカット待ちへ…	*/
				}

#if (PRO_PAPER_TYPE == ROLL_PAPER)
				/* Next 10 line 追加 1998/11/25 by T.Soneoka */
				else {
					if (RxPmType == RX_PRINTER) {	/**	プリンタ受信の場合	*/
						/**	プリンタエラーの種類を確認	*/
						CheckRxPrinterError();
						if (RxPageFinishStatus == RX_PRT_ERR) {	/**	プリンタエラー	*/
							/**	ループ終了	*/
							break;
						}
					}
				}
#endif
				if (FaxComPerformingFlag == 0) {	/**	通信終了	*/
					/**	３０msウェイト	*/
					FaxTimer( 30 );
				}
			}

			/*----------------------*/
			/*	ＲＮＲ－ＲＲ処理	*/
			/*----------------------*/
			if (FaxComPerformingFlag == 1) {	/**	通信中	*/
				/*------------------*/
				/**	ＲＮＲ応答送信	*/
				/*------------------*/
				FaxHDLC_Transmit( RNR_F, 0 );

				/*------------------*/
				/**	ＲＲ命令受信	*/
				/*------------------*/
#if (PRO_TX_SPEED == V34) /* Ported from clover\src\fcmcomd.c by H.Kubo 1997/08/04 */
				if (FCM_ReceiveCommand( TIME_OVER_6SEC, CONTINUE_CCRETRAIN ) == FSK_RECEIVE) {		/**	命令受信ＯＫ	*/
					ReceiveResponseFlag = 1;
					AnalyzeRxPostMessageFrame();	/**	受信ポストメッセージ解析	*/
					if ((RxFCF != RR_F) && (RxOptionFCF != PPS_F)) {	/**	（ＲＲ，ＰＰＳ－Ｑ）以外	*/
						/* フェーズＥのコールを追加 1996/02/07 */
						FaxPhaseE( 4 );				/**	通信終了（ＤＣＮなし）	*/
						ReceiveError( 0x51 );		/**	Ｒ．５．１	*/
						break;						/**	終了	*/
					}
				}
#else /* (PRO_TX_SPEED == V34) */
				if (MDM_ReceiveCommand((UWORD)TIME_OVER_6SEC) == FSK_RECEIVE) {		/**	命令受信ＯＫ	*/
					ReceiveResponseFlag = 1;
					AnalyzeRxPostMessageFrame();	/**	受信ポストメッセージ解析	*/
					if ((RxFCF != RR_F) && (RxOptionFCF != PPS_F)) {	/**	（ＲＲ，ＰＰＳ－Ｑ）以外	*/
						ReceiveError( 0x51 );		/**	Ｒ．５．１	*/
						break;						/**	終了	*/
					}
				}
#endif /* (PRO_TX_SPEED == V34) */
				else {		/**	Ｔ２(6s)タイムアウト	*/
					ReceiveResponseFlag = 0;
					/**	送信した応答が正常に受信されなかったとして，プリアンブル短縮フラグをクリア	*/
					ShorteningPreambleFlag = 0;
#if defined (DEU) || defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
					FaxPhaseE( 1 );					/**	通信終了（ＤＣＮあり）	*/
#else
					FaxPhaseE( 4 );					/**	通信終了（ＤＣＮなし）	*/
#endif
					ReceiveError( 0x51 );			/**	Ｒ．５．１	*/
					break;							/**	終了	*/
				}
			}
		}

		/**	(最新の)画データ受信結果を再セット	*/
		RxPageFinishStatus = MDM_PhaseC_Status;

#if (PRO_PRINTER_RX == ENABLE)
		if (RxPmType == RX_PRINTER) {	/**	プリンタ受信	*/
			/**	プリンタエラーの種類を確認	*/
			CheckRxPrinterError();

 #if (PRO_PRINT_TYPE == THERMAL)	/* Endmark3 By O.Kimoto 1999/02/19 */
			/* Endmark3 by O.Kimoto 1999/02/19 */
			if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {
				if (EndMarkDetect == TRUE) {
					RxPageFinishStatus = RX_PRT_ERR;
					RxPrinterErrorFlag = 1;
				}
			}
 #endif
		}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/9 K.Kawata*/
		if (RxPmType == RX_PRINTER) {	/**	プリンタ受信	*/
			CheckRxPrinterError();	/* プリンタエラーの種類を確認 */
		}
#endif
		/**	プリアンブル短縮を再度セットする	*/			/* Dec.15.1994 */
		ShorteningPreambleFlag = PostSpeedHandshakeFlag;	/* Dec.15.1994 */
	}

	EcmWaitPhase = 0;	/**	デコード待ち状態をクリア	*/
}


/*************************************************************************
	module		:[受信側のポストメッセージ応答]
	function	:[
		1.	ＥＣＭ受信では，画質良好ならＭＣＦを送出し，画質不良ならＲ．３．３で
		.	終了する
		2.	ポストメッセージでＥＯＲを受信した場合はＥＲＲを送出する
		3.	Ｇ３受信では，画質良好ならＭＣＦを送出し，画質不良ならＲＴＮを送出する
	]
	return		:[]
	common		:[
		RxECM_Mode			RxModeChangeRequestedFlag
		TxFCF				TxOptionFCF
		RxEOR_ReceiveFlag	RxPageFinishStatus
	]
	condition	:[]
	comment		:[
		ＥＣＭ受信でプリンタエラーの場合は
		ＮＧの応答ができないので，ＤＣＮで
		強制終了する
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/22]
	author		:[竹内茂樹]
*************************************************************************/
void	RxRespondPostMessage( void )
{
	if (RxECM_Mode == ECM_ON) {		/**	ＥＣＭ受信	*/
		if (RxOptionFCF == EOR_F) {	/**	ＥＯＲ－Ｑを受信した	*/
			/**	ＥＲＲ応答送信	*/
			TxFCF = ERR_F;
			TxOptionFCF = 0;
			FaxHDLC_Transmit( TxFCF, TxOptionFCF );
/*
** ＥＲＲを出したとき、通信ジャーナルに、枚数０ 結果ＯＫとなる不具合
** 下記ＤＥＵだけ結果がＲ５．２になっていたが、共通でいれるようにします
** 1999/02/09 by T.Soneoka
*/
#if (0)
**#if defined(DEU)	/* by M.H '97/03/23 DEU仕様に追加 */
**			FaxComResult = RECEIVEERROR | 0x52;
**#endif
#else
			/*ReceiveError(0x52); 1999/10/21 Y.Murata */
#endif

			/* 1999/08/27 Y.Murata NAGANOより 1999/10/21 Y.Murata
			 * ここではエラーコードをセットするだけ。通信手順は続けます。
			*/
			FaxComResult = RECEIVEERROR | 0x52;
			if (RxECM_Mode == ECM_ON) {		/**	ECM受信	*/
				/**	交信結果を記憶する大域変数にECMモードをセット	*/
				FaxComResult |= ECM_MODE_SET;
			}


		}
		else {
			if (RxPageFinishStatus == RX_ERROR) {			/**	画質不良	*/
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/03/31  By T.Yamaguchi */
				if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
					FaxPhaseE( 1 );								/**	ＤＣＮ送出	*/
				}
#endif
				ReceiveError( 0x33 );						/**	Ｒ．３．３	*/
			}
#if (PRO_PRINTER_RX == ENABLE)	/*	もみじ／さつき／ラベンダ	*/
			else if (RxPageFinishStatus == RX_PRT_ERR) {	/**	プリンタエラー (印字ＮＧ)	*/
				FaxPhaseE( 1 );								/**	ＤＣＮ送出	*/
				ReceiveError( 0x45 );						/**	Ｒ．４．５	*/
			}
			else if ((RxPageFinishStatus == RX_BLOCK_END)
			&&		 (RxPrinterErrorFlag == 1)) {			/**	ブロックエンド&&プリンタエラー	*/
				FaxPhaseE( 1 );								/**	ＤＣＮ送出	*/
				ReceiveError( 0x45 );						/**	Ｒ．４．５	*/
			}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/9 K.Kawata*/
			else if (RxPageFinishStatus == RX_PRT_ERR) {	/**	プリンタエラー (印字ＮＧ)	*/
				FaxPhaseE( 1 );								/**	ＤＣＮ送出	*/
				ReceiveError( 0x45 );						/**	Ｒ．４．５	*/
			}
			else if ((RxPageFinishStatus == RX_BLOCK_END)
			&&		 (RxPrinterErrorFlag == 1)) {			/**	ブロックエンド&&プリンタエラー	*/
				FaxPhaseE( 1 );								/**	ＤＣＮ送出	*/
				ReceiveError( 0x45 );						/**	Ｒ．４．５	*/
			}
#endif
			else {		/**	画質ＯＫ	*/
				/**	ＭＣＦ応答送信	*/
				TxFCF = MCF_F;
				TxOptionFCF = 0;
				FaxHDLC_Transmit( TxFCF, TxOptionFCF );
			}
		}
	}
	else {		/**	Ｇ３受信	*/
		if ((RxPageFinishStatus == RX_ERROR)
		||	(RxPageFinishStatus == RX_PRT_ERR)) {	/**	画質不良||プリンタエラー	*/
			/**	ＲＴＮ応答送信	*/
			TxFCF = RTN_F;
			TxOptionFCF = 0;
			FaxHDLC_Transmit( TxFCF, TxOptionFCF );
			RxModeChangeRequestedFlag = 1;	/**	モード変更要求フラグをセット	*/
/*#if defined (ESP) || defined(DEU)	@*	スペインの申請時に必要	*//* by M.H '97/03/23 DEU仕様にも追加 */
#if defined(DEU) || defined(EUR)	/*	スペインの申請時に必要	*//* by M.H '97/03/23 DEU仕様にも追加 By Y.Suzuki 1998/09/18 */
									/* 欧州仕様追加 by M.H 1999/09/16 */
			FaxComResult = RECEIVEERROR | 0x42;
#endif
		}
		else {		/**	画質ＯＫ	*/
			/**	ＭＣＦ応答送信	*/
			TxFCF = MCF_F;
			TxOptionFCF = 0;
			FaxHDLC_Transmit( TxFCF, TxOptionFCF );
		}
	}
}


/*************************************************************************
	module		:[ポストメッセージＤＣＳ受信待ち]
	function	:[
		1.	命令受信し，解析する
		2.	ポストメッセージ命令の場合は，もう一度命令受信(1.)に戻る
		3.	ＤＣＳを受信した場合は，ＥＯＭ受信フラグをクリアしてリターンする
		.	（フェーズＢのコンパチチェックへ戻る）
		4.	ＥＯＰを受信している場合以外でＤＣＮを受信した場合と，
		.	その他のフレームを受信した場合と，命令受信タイムアウトの場合は
		.	Ｒ．１．１とする
	]
	return		:[]
	common		:[
		FaxComPerformingFlag	ReceiveResponseFlag
		RxEOM_ReceiveFlag		RxEOP_ReceiveFlag
		RxFCF					RxFrameMessage1
		PRI_Q_RxFlag			:ＰＲＩ－Ｑメッセージ受信フラグ
	]
	condition	:[
		受信フェーズＤの最後で，モード変更要求(RxModeChangeRequestedFlag)
		ありの場合にコールする
	]
	comment		:[
		FaxRxRetraining():g3rxd.c のこと
		修正履歴
		94/12/05 (桐のみ)ＦＸ手順ＲＴＮ返送時、ＤＣＳと同様の待ち方でＮＳＳを待たねばならない。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/25]
	author		:[竹内茂樹]
*************************************************************************/
void	ReceiveDCS( void )
{
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
	UBYTE mode_change_speed_flag;
	UBYTE receive_command;
#endif

	while (FaxComPerformingFlag == 1) {		/**	通信中	*/

#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
		mode_change_speed_flag = 0;
		receive_command = FSK_RECEIVE;
		EOM_received = 0;

		if ((RxEOM_ReceiveFlag == 1) && (MakerCodeRxFlag == YES)) {		/* 相手機が村田機 */
			if (SpeedModeChangeRomCheck() == TRUE) {		/* 96/05/24 */
				FaxRxSpeedHandshake();						/** 短縮ハンドシェーク受信 */
				if (RxSpeedHandshakeFlag == 1) {
					RxEOM_ReceiveFlag = 0;				/* SDCSを受け取ったら抜ける */
					break;
				}
				if (EOM_received == 0) {
					break;
				}
			}
		}
		switch (EOM_received) {		/* 96/05/29 By T.Y */
		case	0:		/* EOM_TONE */
			receive_command = MDM_ReceiveCommand((UWORD)TIME_OVER_6SEC);	/** 命令受信OK */
			break;
		case	1:		/* FaxRxSpeedHandshake()の中で、FSKを受信した */
		default:
			break;
		}
		if (receive_command == FSK_RECEIVE) {
#else
#if (PRO_TX_SPEED == V34) /* Ported from clover\src\fcmrxd.c by H.Kubo 1997/08/04 */
		if (FCM_ReceiveCommand( TIME_OVER_6SEC , CONTINUE_CCRETRAIN) == FSK_RECEIVE) {	/**	命令受信ＯＫ	*/
#else /* (PRO_TX_SPEED == V34)  */
		if (MDM_ReceiveCommand((UWORD)TIME_OVER_6SEC) == FSK_RECEIVE) {	/**	命令受信ＯＫ	*/
#endif /* (PRO_TX_SPEED == V34) */
#endif /* (PRO_SPD_MODE == ENABLE) */
			/*------------------------------*/
			/**	受信ポストメッセージを解析	*/
			/*------------------------------*/
			ReceiveResponseFlag = 1;
			AnalyzeRxPostMessageFrame();

			if (RxFrameMessage1 == POST_MESSAGE_COMMANDS) {		/**	ポストメッセージを受信	*/
				FaxHDLC_Transmit( TxFCF, TxOptionFCF );			/**	前回と同じ応答送出	*/
			}
			else if (RxFCF == DCN_F) {		/**	ＤＣＮを受信	*/
				if (RxEOP_ReceiveFlag == 1) {	/**	ＥＯＰ受信済み（交信終了許可あり）	*/
					FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
				}
				else {
					ReceiveError( 0x11 );		/**	Ｒ．１．１	*/
				}
			}
#if(PRO_MAKER == FX)
			else if ((RxFCF == DCS_F) || (RxFCF == NSS_F)) {		/**	ＤＣＳ/ＮＳＳを受信	*/
#else
			else if (RxFCF == DCS_F) {		/**	ＤＣＳを受信	*/
#endif
				RxEOM_ReceiveFlag = 0;			/**	ＥＯＭ受信フラグをクリア	*/
				ReceiveResponseFlag = 0;		/**	ポストメッセージ受信フラグをクリア	*/
				break;							/**	リターン	*/
				/*	受信フェーズＢのコンパチチェックへ行くはず	*/
			}
			else {							/**	その他のフレームを受信	*/
				FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）add 96/06/25 S.Takeuchi	*/
				ReceiveError( 0x11 );			/**	Ｒ．１．１	*/
				break;							/**	リターン	*/
			}
		}
		else {		/**	Ｔ２タイムアウト	*/
			ReceiveResponseFlag = 0;
			if (RxEOM_ReceiveFlag == 1) {	/**	ＥＯＭを受信して命令受信なし	*/
				break;						/**	リターン (ＤＩＳ送出へ…)	*/
			}
			else {							/**	ＥＯＭ受信なし	*/

#if defined(POPLAR_F)
				/* 1997/02/06  1999/12/10 Y.M クローバーから移植
				 * ＤＣＮがとれなかってもＥＯＰを受信していたらＯＫ
				*/
				if (RxEOP_ReceiveFlag == 1) {	/**	ＥＯＰ受信済み（交信終了許可あり）	*/
					FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
  #if defined (DEU) || defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
					FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
  #else
					FaxPhaseE( 4 );				/**	通信終了（ＤＣＮなし）	*/
  #endif
				}
				else {
  #if defined (DEU) || defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
					FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
  #else
					FaxPhaseE( 4 );				/**	通信終了（ＤＣＮなし）	*/
  #endif
					ReceiveError( 0x11 );		/**	Ｒ．１．１	*/
				}
#else

  #if defined (DEU) || defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
				FaxPhaseE( 1 );				/**	通信終了（ＤＣＮあり）	*/
  #else
				FaxPhaseE( 4 );				/**	通信終了（ＤＣＮなし）	*/
  #endif
				ReceiveError( 0x11 );		/**	Ｒ．１．１	*/
#endif
			}
		}
	}
}

/*************************************************************************
	module		:[受信側会話予約要求の処理]
	function	:[
		1.	受信画質によって，ＰＩＰ／ＰＩＮを送出し，命令受信する
		2.	ＰＲＩ－Ｑ受信後，オペレータを呼び出し，通信終了する
		3.	Ｔ３タイムオーバーの時は，ＤＩＳ送出に戻る
		.	(但し，上位から「続行しない」の指定の場合はR.4.2で終了する)
	]
	return		:[]
	common		:[
		TxFCF	TxOptionFCF		RxECM_Mode
		FaxComPerformingFlag
		RxEOR_ReceiveFlag		ReceiveResponseFlag
		RxFrameMessage1			PRI_Q_RxFlag
		RxEOM_ReceiveFlag		RxModeChangeRequestedFlag
		RxWholePageCompletedFlag
		SYS_GeneralTimer		SYS_VoiceCallAccepted
	]
	condition	:[
		送信機からの受信被会話予約が成立していない時で，
		自機の会話予約要求がある場合にコールする
	]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/04/06]
	author		:[竹内茂樹]
*************************************************************************/
void	RxRequestedVoiceMode(UBYTE	f_rx_continue)	/*	タイムアウトの時の処理：1=ＲｘＢに戻り続行／0=R.4.2で終了	*/
{
	UWORD	t3_timer;
	UBYTE	voice_result;

	while ((FaxComPerformingFlag == 1)
	&&	   (SYS_VoiceCallAccepted == 0)) {		/**	回線断or会話予約成立するまで	*/
		/*--------------------------------------*/
		/**	画質チェックし，応答送信(PIP/PIN)	*/
		/*--------------------------------------*/
		TransmitPIP();
#if defined(DEU) || defined(EUR)	/* by M.H '97/03/23 DEU仕様に追加 */
									/* 欧州仕様追加 by M.H 1999/09/16 */
		if (TxFCF == PIN_F){
			FaxComResult = RECEIVEERROR | 0x42;
		}
#endif

		/*------------------------------*/
		/**	命令受信(Ｔ３タイマ以内)	*/
		/*------------------------------*/
		ReceiveResponseFlag = 0;
		t3_timer = SYS_GeneralTimer;
		while ((UWORD)(SYS_GeneralTimer - t3_timer) < T3_TIMER) {
#if (PRO_TX_SPEED == V34) /* Ported from clover\src\fcmrxd.c by H.Kubo 1997/08/04 */
			if (FCM_ReceiveCommand( TIME_OVER_6SEC, NON_CCRETRAIN ) == FSK_RECEIVE) {
				ReceiveResponseFlag = 1;
				break;
			}
#else /* (PRO_TX_SPEED == V34) */
			if (MDM_ReceiveCommand((UWORD)TIME_OVER_6SEC) == FSK_RECEIVE) {
				ReceiveResponseFlag = 1;
				break;
			}
#endif /* (PRO_TX_SPEED == V34) */
		}

		/*----------------------*/
		/*	ＰＲＩ－Ｑ受信待ち	*/
		/*----------------------*/
		if (ReceiveResponseFlag == 1) {		/**	命令受信ＯＫ	*/
			AnalyzeRxPostMessageFrame();
			if (RxFrameMessage1 == POST_MESSAGE_COMMANDS) {		/**	ポストメッセージ受信	*/
				if (PRI_Q_RxFlag == 1) {						/**	ＰＲＩ－Ｑ		*/
					break;		/**	オペレータ呼び出しへ…	*/
				}
				/*--------------------------------------------------*/
				/**	ＰＲＩ－Ｑ以外を受信した時は，ループの先頭へ…	**
				***	(もう一度，応答送信／命令受信する)				*/
				/*--------------------------------------------------*/
			}
			else {
				if (RxFCF == DCN_F) {		/**	ＤＣＮ受信	*/
					FaxPhaseE( 4 );			/**	通信終了(ＤＣＮなし)	*/
				}
				else {
					ReceiveError( 0x42 );	/**	Ｒ．４．２	*/
					FaxPhaseE( 1 );			/**	ＤＣＮ送出し，通信終了	*/
				}
				return;		/**	リターン	*/
			}
		}
		else {		/**	Ｔ３タイマ以内に，命令受信なし	*/
			break;
		}
	}

	if ((ReceiveResponseFlag == 1) && (PRI_Q_RxFlag == 1)) {	/**	ＰＲＩ－Ｑ受信	*/
		/*----------------------*/
		/**	オペレータ呼び出し	*/
		/*----------------------*/
		voice_result = MDM_RxVoiceReq();
		switch (voice_result) {		/**	会話予約結果	*/
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
			/*----------------------------------------------*/
			/**	ＰＩＰ／ＰＩＮ送出し，通信終了(ＤＣＮなし)	*/
			/*----------------------------------------------*/
			FaxHDLC_Transmit( TxFCF, TxOptionFCF );
			FaxPhaseE( 4 );
			/*------------------------------------------*/
			/**	３００msウェイト後，Ｈ／ＬリレーＯＦＦ	*/
			/*------------------------------------------*/
			FaxTimer( 300 );
			FaxTelAutoSWAfterTransaction();
			break;
		default:
			break;
		}
	}

	/*------------------------------*/
	/*	Ｔ３タイムオーバー時の処理	*/
	/*------------------------------*/
	if (SYS_VoiceCallAccepted == 0) {	/**	Ｔ３タイムオーバー	*/
		if (f_rx_continue == 1) {			/**	続行する	*/
#if defined(DEU) || defined(EUR)	/* 95/08/09 Y.Suzuki */
									/* 欧州仕様追加 by M.H 1999/09/16 */
			RxWholePageCompletedFlag = 1;		/*	FaxRxPhaseC()のループ脱出用	*/
			RxModeChangeRequestedFlag = 1;		/*	FaxReceive()の内ループ脱出用	*/
			RxEOM_ReceiveFlag = 1;				/*	FaxReceive()の外ループ脱出用	*/
			/**	フェーズＢのＤＩＳ送出(FaxRxPhaseB1())へ…	*/
#else
			/*----------------------------------------------------------------------*/
			/*	以下の処理を追加 (さつきＱＡＴでのトラブル)		Sep.12.1994			*/
			/*	受信側からの会話予約で，相手機で人が出てＰＲＩ－ＥＯＰを受信し，	*/
			/*	自機でタイムオーバーした場合はフェーズＢへ戻らずに，通信終了する	*/
			/*----------------------------------------------------------------------*/
			if (RxEOP_ReceiveFlag == 1) {	/**	ＥＯＰを受信していた	*/
				FaxPhaseE( 4 );				/**	通信終了	*/
			}
			else {							/**	ＭＰＳ，ＥＯＭを受信していた	*/
				RxWholePageCompletedFlag = 1;		/*	FaxRxPhaseC()のループ脱出用	*/
				RxModeChangeRequestedFlag = 1;		/*	FaxReceive()の内ループ脱出用	*/
				RxEOM_ReceiveFlag = 1;				/*	FaxReceive()の外ループ脱出用	*/
				/**	フェーズＢのＤＩＳ送出(FaxRxPhaseB1())へ…	*/
			}
#endif
		}
		else {								/**	終了する	*/
			ReceiveError( 0x42 );	/**	Ｒ．４．２	*/
			FaxPhaseE( 1 );			/**	ＤＣＮ送出し，通信終了	*/
		}
	}
}


/*************************************************************************
	module		:[ＰＩＰ／ＰＩＮ送出]
	function	:[
		画質をチェックし，ＰＩＰまたはＰＩＮを送出する
	]
	return		:[]
	common		:[
		RxECM_Mode
		TxOptionFCF		TxFCF		RxOptionFCF
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/04/07]
	author		:[竹内茂樹]
*************************************************************************/
void	TransmitPIP( void )
{
	/*--------------------------------------*/
	/**	画質チェックし，応答送信(PIP/PIN)	*/
	/*--------------------------------------*/
	if (RxECM_Mode == ECM_ON) {		/*	ＥＣＭ	*/
		if (RxOptionFCF == EOR_F) {		/*	画質不良(ＥＯＲ受信時)	*/
			TxFCF = PIN_F;
		}
		else {
			TxFCF = PIP_F;
		}
	}
	else {						/*	Ｇ３	*/
		if ((RxPageFinishStatus == RX_ERROR)
		||	(RxPageFinishStatus == RX_PRT_ERR)) {	/*	画質不良||プリンタエラー	*/
			/*	↑プリンタエラーの条件追加	Jun.20.1994	*/
			TxFCF = PIN_F;
		}
		else {
			TxFCF = PIP_F;
		}
	}
	TxOptionFCF = 0;
	FaxHDLC_Transmit( TxFCF, TxOptionFCF );
/* #if defined(DEU) 1997/06/02  By T.Yamaguchi */	/* 97/04/26 by M.H. */
	PIP_TX_Flag = 1;
/* #endif */
}
