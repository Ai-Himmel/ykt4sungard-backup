/*-----------------------------------------------------------------------*/
/*	プロジェクト : POPLAR_F                                              */
/*	ファイル名   : mdmtxpix.c                                            */
/*	作成者       :                                                       */
/*	日  付       : 1999/10/06                                            */
/*	概  要       : 画データ送信関連処理                                  */
/*	修正履歴     :                                                       */
/*	keyword			:[MDM]                                               */
/*	machine			:[SH7043,V53]                                        */
/*	language		:[MS-C(Ver.6.0)]                                     */
/*---------------------------------------------------------------------- */

/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\dma_def.h"
/* #include "\src\atlanta\define\idp_def.h" */ /* シラカバではidp_*.cは使用しない */
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\sysscan.h" /* Added by H.Kubo for SCN_ADF 1997/07/25 */
#include "\src\atlanta\define\idp_def.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\scn_pro.h" /* Added by H.Kubo 1997/07/08 */
#include "\src\memsw\define\mems_pro.h" /* Added by H.Kubo 1997/07/08 */
#include "\src\atlanta\define\cmn_pro.h" /* Added by H.Kubo 1997/07/08 */
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\sh7043\define\io_pro.h"


/*******
** ext_v
*******/
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\scn_data.h" /* Added by H. Kubo 1997/06/26. For SCN_MotorSpeedControl */
#include "\src\atlanta\ext_v\bkupram.h"

#if defined(POPLAR_F)
#include "\src\atlanta\sh7043\ext_v\extv_mon.h"
#include "\src\atlanta\sh7043\define\def_tcb.h"
#include "\src\atlanta\sh7043\define\def_mon.h"
#endif

#if (PRO_SCN_CODEC_TYPE == SOFTWARE) /* added by H.Hirao 1998/10/29 */ /* ported by T.Takagi 2001/12/17 */
 #if defined(SATSUKI2)  /* 他の機種との共用ソースなのでSATSUKI2で切ります。O.Oshima 2003/11/07 Smuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
 #elif defined(STOCKHM2)
#include "\src\atlanta\stockhm2\ext_v\scn_dath.h" 
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
 #endif
#endif

extern UWORD DebugZeroCnt;
extern UWORD tskno_SCN_ScanningTask;	/* 1998/08/12 H.Yoshikawa */

UWORD	MDM_DebugDataWaitCnt = 0;
UWORD	next_mbf_set_cnt = 0;	/*	モデムバッファ書き込みデータ数	*/
UDWORD	ebr_cnt = 0;	/**	ＥＣＭバッファ読み出しバイト数	*/

/*************************************************************************
	module		:[送信開始もしくは送信エラー待ち]
	function	:[
		1.送信開始のイベントと送信エラーを監視し、どちらかが発生すれば、エラーの状態を返り値に返る。
	]
	return		:[UBYTE rtn :
		0 				送信開始
		TX_LAMP_ERR
		TX_DOC_ERR
		TX_1M_OVER		原稿長オーバー
		TX_MEM_ERR 		メモリエラー
	]
	common		:[
		ModemBlock
	]
	condition	:[]
	comment		:[	このファイル (mdmtxpix.c) 以外にある関数から呼出されるべきでない。 (by H.Kubo)
	]
	ProtoType	:[UBYTE	MDM_WaitForTxStartOrError(void){}]
	date		:[1997/07/16]
	update		:[1997/07/16]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_WaitForTxStartOrTxError(void)
{
	/*	符号変換完了待ち
	**	（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）
	*/
	int loop_flg = 1;	/**	ループ制御フラグ１に設定	*/
	UBYTE rtn = 0; /* Not error for initial value */
	while (loop_flg) {	/**	ループ制御フラグが１の時	*/
		if (TxStartFlag == 1) {	/**	画データ送出フラグが１の時（エンコードデータが揃った時）	*/
			loop_flg = 0;	/**	ループ制御フラグを０に設定	*/
		}
		else {	/**	その他の時	*/
			rtn = CheckTxSystemError();	/**	送信異常チェック	*/
			if (rtn) {	/**	送信異常有りの時	*/
				return (rtn);	/**	送信異常の戻り値セット	*/
			}
		}
		wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/
	}
	return rtn;
}

/*************************************************************************
	module		:[送信ＰＩＸオープン]
	function	:[
		1.各送信モデムオープン処理実行
	]
	return		:[なし]
	common		:[
		ModemBlock
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void far	MDM_TxPixOpen(unsigned char ,unsigned char ){}]
	date		:[1993/12/21]
	update		:[1995/12/12]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void 	MDM_TxPixOpen(	UBYTE speed,
							UBYTE ecm_type)
{
	struct	Timer10msData_t DummyPixTimer;

	DebugZeroCnt = 0;
	MDM_DebugDataWaitCnt = 0;
	InitializeModemWork();	/**	モデム変数初期化	*/
	ModemTypeSet(speed);	/**	モデムタイプ／スピード設定	*/

	if (ModemBlock.Type == TYPE_V17) {	/**	モデムタイプがＶ１７の時	*/
#if 0 /* CTC/CTR の後最初の PIX はロングトレーニングで送信する。 changed by H.Kubo 1998/09/22 */
@@		ModemBlock.Training = TRAINING_SHORT;	/**	モデムＩ／Ｆトレーニングタイプをトレーニングショート設定	*/
#else
		if (RxFCF == CTR_F) {
			ModemBlock.Training = TRAINING_LONG;	/**	モデムＩ／Ｆトレーニングタイプをトレーニングロング設定	*/
		}
		else {
			ModemBlock.Training = TRAINING_SHORT;	/**	モデムＩ／Ｆトレーニングタイプをトレーニングショート設定	*/
		}
#endif
	}
	else {	/**	その他の時	*/
		ModemBlock.Training = TRAINING_LONG;	/**	モデムＩ／Ｆトレーニングタイプをトレーニングロング設定	*/
	}

	ModemBlock.Chain = CHAIN_ON;

	if (ecm_type == ECM_ON) {	/**	ＥＣＭ送信の時	*/
		/* ＥＣＭ送信モデムオープン */
		ModemBlock.Mode = MODE_TX_ECM;	/**	モデムＩ／Ｆ交信モードをＥＣＭ送信設定	*/
		TxEcmOpen();	/**	ＥＣＭ送信モデムオープン	*/
		MDM_NewT30Status = MODE_TX_ECM;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */
	}
	else {	/**	Ｇ３送信の時	*/
		/* Ｇ３送信モデムオープン */
		ModemBlock.Mode = MODE_TX_G3;	/**	モデムＩ／Ｆ交信モードをＧ３送信に設定	*/
		TxG3_Open();	/**	Ｇ３送信モデムオープン	*/
		MDM_NewT30Status = MODE_TX_G3;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */

		/* ダミーデータ送出監視タイマ起動 */
		DummyPixTimer.Time = (PIX_DUMMY_TIME / 10);
		DummyPixTimer.SendMBX = mbxno.MDM_PixDummy;
		DummyPixTimer.ReturnValue = MSG_DUMMY_PIX_TIME_OVER;
		timerID_DummyPixTimer = 0xff; /* Changed by H.Kubo 1997/07/14 */
		CMN_MultiTimer10msStart(&timerID_DummyPixTimer, &DummyPixTimer);	/**	ダミーデータ送出監視タイマ起動	*/
	}
}



/*************************************************************************
	module		:[交信タイプ決定]
	function	:[
		1.ECM の有無、送信種別から交信タイプを判断し、返す。
	]
	return		:[UBYTE com_type :
		TX_G3_SCAN
		TX_G3_MEM
		TX_G3_CVR
		TX_G3_RCR
		TX_ECM_SCAN
		TX_ECM_MEM
		TX_ECM_CVR
		TX_ECM_RCR
		TX_ECM_BKUPRAM
		TX_INVALID_TYPE
	]
	common		:[
		ModemBlock
	]
	condition	:[]
	comment		:[	MDM_TxPix() から呼出されることを意図して作成した関数。
					グローバル変数は参照も書き換えもしない。
					このファイル (mdmtxpix.c) 以外にある関数から呼出されるべきでない。 (by H.Kubo)
	]
	ProtoType	:[UBYTE	MDM_DecideTxCommunicateType(UBYTE ,UBYTE ){}]
	date		:[1997/07/16]
	update		:[1997/07/16]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_DecideTxCommunicateType(UBYTE	ecm_type, UBYTE sm_type)
{
	UBYTE cm_type;
	/*	送信種別設定	*/
	if (ecm_type == ECM_OFF) {	/**	Ｇ３送信の時	*/
		switch (sm_type) {	/**	送信種別	*/
		case	TX_SCAN:	/**	スキャナ送信の時	*/
			cm_type = TX_G3_SCAN;	/**	交信タイプをＧ３スキャナにセット	*/
			break;
		case	TX_MEMORY:	/**	メモリ送信の時	*/
			cm_type = TX_G3_MEM;	/**	交信タイプをＧ３メモリにセット	*/
			break;
		case	TX_CVR:	/**	カバーページ送信の時	*/
			cm_type = TX_G3_CVR;	/**	交信タイプをＧ３カバーページにセット	*/
			break;
		case	TX_RCR:	/**	受領証送信の時	*/
			cm_type = TX_G3_RCR;	/**	交信タイプをＧ３受領証にセット	*/
			break;
		case	TX_RELAYED_TX_REPORT:	/**	不達通知送信の時	*/
			cm_type = TX_G3_RELAYED_TX_REPORT;	/**	交信タイプをＧ３受領証にセット	*/
			break;
		default: /* 無効な交信タイプ */
			cm_type = TX_INVALID_TYPE;
			break;
		}
	}
	else {	/**	ＥＣＭ送信の時	*/
		switch (sm_type) {	/**	送信種別	*/
		case	TX_SCAN:	/**	スキャナ送信の時	*/
			cm_type = TX_ECM_SCAN;	/**	交信タイプをＥＣＭスキャナにセット	*/
			break;
		case	TX_MEMORY:	/**	メモリ送信の時	*/
			cm_type = TX_ECM_MEM;	/**	交信タイプをＥＣＭメモリにセット	*/
			break;
		case	TX_CVR:	/**	カバーページ送信の時	*/
			cm_type = TX_ECM_CVR;	/**	交信タイプをＥＣＭカバーページにセット	*/
			break;
		case	TX_RCR:	/**	受領証送信の時	*/
			cm_type = TX_ECM_RCR;	/**	交信タイプをＥＣＭ受領証にセット	*/
			break;
		case	TX_RELAYED_TX_REPORT:	/**	不達通知送信の時	*/
			cm_type = TX_ECM_RELAYED_TX_REPORT;	/**	交信タイプをＧ３受領証にセット	*/
			break;
		case	TX_BKUPRAM: /** 高速リモート診断バックアップデータ送信の時	*/
			cm_type = TX_ECM_BKUPRAM;	/** 交信タイプを高速リモート診断データ	*/
			break;
		default: /* 無効な交信タイプ */
			cm_type = TX_INVALID_TYPE;
			break;
		}
	}
	return cm_type;
}

/*************************************************************************
	module		:[送信ＰＩＸ]
	function	:[
		1.送信コントロールタスクを起動（エンコード制御）
	]
	return		:[
												MG3	MECM	SG3	SECM
		TX_PAGE_END					0			○	○		○	○		1ﾍﾟｰｼﾞ送信完了
		TX_BLOCK_END				1			×	○		×	○		64KByte送信完了
		TX_STOPPED					2			○	○		○	○		停止ＳＷ　ＯＮ
		TX_DOC_ERR					3			×	×		○	○		原稿繰り込み不良
		TX_LAMP_ERR					4			×	×		○	○		ﾗﾝﾌﾟｴﾗｰ
		TX_FILE_ERR					5			○	○		×	×		該当するﾒﾓﾘﾌｧｲﾙが存在しない
		TX_MEM_ERR					7			○	○		×	×		画像ﾒﾓﾘ画品質不良
		TX_1M_OVER					8 			×	×		○	○		ｽｷｬﾅ送信が１ｍを越えた
		TX_SEPARATE					9 			○	○		○	○		F網設定時、送信がA4 2枚分に達した
			○：戻り値あり
			×：戻り値なし
			△：未定
	]
	common		:[]
	condition	:[]
	comment		:[
		もみじでは"エンコードV53DMA終了割り込み監視タスク"
		のクリエイトはしません (MDM_EncodeDMA_TC_DetectTask)
	]
	date		:[1993/12/21]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE  MDM_TxPix(UBYTE	ecm_type,UBYTE	sm_type)
{
	MESSAGE_t *MDM_Msg;
	UBYTE rtn;
	UWORD	check_tskno;
	UBYTE	debug;

	debug = 0;
	TxStartFlag = 0;	/**	送信開始フラグ（エンコードデータ準備ＯＫ）	*/

	rtn = 0;	/*** (この関数内をDOC_ERROR_MAINTEで検索してください)** 2000/12/19 by K.Okada */

	/*	通信の最初でCodecPageStatus = CDC_READYに設定しておく	*/
	MDM_OptionTTiSize = (UDWORD)(0);	/* Add By O.Kimoto 1997/02/25 */

	/*	送信種別設定	*/
	CommunicateType = MDM_DecideTxCommunicateType(ecm_type, sm_type); 	/* Rewritten by H.Kubo 1997/07/16. */

	/*	送信種別各タスク起動処理	*/
	switch (sm_type) {	/**	送信種別	*/
	case TX_MEMORY:	/**	メモリ送信の時	*/
		switch (CodecPageStatus) {	/**	コーデックの状態	*/
		case CDC_BLOCK_END:	/**	ブロックエンドの時	*/
			/*	エンコード開始（ＤＭＡ起動）メッセージ送信	*/
			ModemMessage.Message = MSG_ENCODE_DMA_START;	/**	エンコード開始（ＤＭＡ起動）メッセージ送信	*/
			snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);
			break;

		default:	/**	送信コントロール監視タスクが終了状態の時	*/

			if (rtn = CheckTxSystemError()) { /* DOC_ERROR_MAINTE 2000/12/19 by K.Okada */
				break;
			}

			/*	送信１ページ符号変換タスク起動	*/
			tskno_CDC_MTxCodeConvertTask = 0xffff;
			cre_tsk(&tskno_CDC_MTxCodeConvertTask, TSK_CDC_MTXCODECONVERTPAGETASK, NULL);	/**	送信１ページ符号変換タスク起動	*/
			do {
				rcv_msg(mbxno.MDM_TaskSub, &MDM_Msg);	/**	エンコード開始（ＴＴＩをＥＣＭバッファにセット完了）メッセージ待ち	*/
			} while ( MDM_Msg->Message != MSG_TTI_COMPLETE );

			/*	エンコードＤＭＡ終了監視タスク起動	*/
			tskno_EncodeDMA_End = 0xffff;
			cre_tsk(&tskno_EncodeDMA_End, TSK_MDM_ENCODEDMA_TC_DETECTTASK, NULL);	/**	エンコードＤＭＡ終了監視タスク起動	*/

			/*	エンコード開始（ＤＭＡ起動）メッセージ送信	*/
			ModemMessage.Message = MSG_ENCODE_DMA_START;
			snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);	/**	エンコード開始（ＤＭＡ起動）メッセージ送信	*/

			/*	メモリリードタスク起動処理（Ｖ５３ＤＭＡ・ＳＬＡＶＥ　ＣＨ１起動）	*/
			tskno_MTxReadDMA_Task = 0xffff;
			cre_tsk(&tskno_MTxReadDMA_Task, TSK_MDM_MTXREADDMA_TASK, NULL);	/**	メモリリードＤＭＡ終了監視タスク起動	*/
			do {
				rcv_msg(mbxno.MDM_MTxReadDMA_Task, &MDM_Msg);	/**	オープン結果メッセージ受信	*/
			} while (!((MDM_Msg->Message == MEM_OK) ||
			          (MDM_Msg->Message == MEM_NO_INDEX)));
			if (MDM_Msg->Message != MEM_OK) {	/**	メモリリードオープンＮＧの時	*/
				MDM_BreakTxTask();
				MDM_PhaseC_Status = TX_FILE_ERR;
				return (MDM_PhaseC_Status);	/**	戻り値ファイルエラーセット	*/
			}
			break;
		}
		break;
	case TX_SCAN:	/**	スキャナ送信の時	*/
		switch (CodecPageStatus) {	/**	コーデックの状態	*/
		case CDC_BLOCK_END:	/**	ブロックエンドの時	*/
			/*----------------------------------------------------------------------------------*/
			/*	エンコード開始（ＤＭＡ起動）メッセージ送信	*/
			/*----------------------------------------------------------------------------------*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* ECM_BUFFER_OVER */
			CMN_DisableInterrupt();	/**	割り込み禁止	*/
			MDM_EcmBufferOverEncodeStop = 0;
			det_evt(EVT_DMA_SCNCDC_DRAM);
			CMN_EnableInterrupt();	/**	割り込み許可	*/
#endif
			ModemMessage.Message = MSG_ENCODE_DMA_START;	/**	エンコードＤＭＡ開始メッセージ送信	*/
			snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);
			break;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* ECM_BUFFER_OVER */
		case CDC_RTC_DET:
			CMN_DisableInterrupt();	/**	割り込み禁止	*/
			MDM_EcmBufferOverEncodeStop = 0;
			det_evt(EVT_DMA_SCNCDC_DRAM);
			CMN_EnableInterrupt();	/**	割り込み許可	*/
			ModemMessage.Message = MSG_ENCODE_DMA_START;	/**	エンコードＶ５３ＤＭＡ開始メッセージ送信	*/
			snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);
			break;
#endif
		default:	/**	送信コントロール監視タスクが終了状態の時	*/
			if (rtn = CheckTxSystemError()) { /* DOC_ERROR_MAINTE 2000/12/19 by K.Okada */
				break;
			}

			/*
			** Ported from ORANGE\src\MDMTXPIX.C by H.Kubo 1997/07/07
			*/
			/*--------------------------------------*/
			/* スキャナオープンパラメータをセット	*/
			/*--------------------------------------*/
			SetScannerTxParam();	/** スキャナオープンパラメータをセット	*/

  #if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* ported by T.Takagi 2001/12/17 T.Takagi */
			/*---------------------------------------------------------------------
			** HINOKIでは通信コーデック(MN86064)を使用してスキャナ送信します
			** 1998/10/09 H.Hirao
			*/
			SCN_DocumentChanged = FALSE;
			if (!SYS_TxTotalPage) { /* １ページ目 */
				cre_tsk(&tskno_SCN_STxStoreTask, TSK_SCN_STXSTORETASK, NULL);
			}
			else {
				ModemMessage.Message = MSG_ENCODE_DMA_START;
				snd_msg(mbxno.SCN_Task, &ModemMessage);
			}
			/*-------------------------------------------------------------*/
			/* 送信１ページ符号変換タスク・ＴＴＩエンコードデータ完了待ち */
			/*-------------------------------------------------------------*/
			tskno_CDC_EncodePageTask = 0xffff;	/* 関数の頭にも追加	96/07/24 */
			cre_tsk(&tskno_CDC_EncodePageTask, TSK_CDC_STXENCODEPAGETASK, 0);	/** スキャナ送信エンコードタスク起動 */
			do {
				rcv_msg(mbxno.MDM_TaskSub, &MDM_Msg);	/** エンコード開始メッセージ待ち */
			} while ( MDM_Msg->Message != MSG_TTI_COMPLETE );
			/*------------------------------------*/
			/* エンコードＤＭＡ終了監視タスク起動 */
			/*------------------------------------*/
			tskno_EncodeDMA_End = 0xffff;	/* 関数の頭にも追加	96/07/24 */
			cre_tsk(&tskno_EncodeDMA_End, TSK_MDM_ENCODEDMA_TC_DETECTTASK, NULL); /** エンコードＤＭＡ終了割り込み監視タスク */

			ModemMessage.Message = MSG_ENCODE_DMA_START;
			snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);	/** エンコードＤＭＡ開始メッセージ送信 */
  #elif (PRO_SCN_CODEC_TYPE == IDP301) /* 2002/09/18 By M.Maeda */
			/*-------------------------------------------------------------
			** SAKAKIのようなIDP301/DICEPを使用した読取り方式の場合には
			** SCN_Open()の後に各種タスクを起動するようにします
			** 1998/08/12 H.Yoshikawa
			*/
			/*--------------------------*/
			/*	スキャナオープン		*/
			/*--------------------------*/
			if (SCN_Open() < 0) {	/**	スキャナオープンＮＧの時		*/
				MDM_BreakTxTask();	/**	各子タスク終了処理	*/
				MDM_PhaseC_Status = TX_DOC_ERR;
				/*
				**	スキャナ送信でのランプチェックNGの時の処理を追加  1997/03/31 s.takeuchi
				*/
				if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_LAMP_ERROR) {	/** ランプエラー */
					MDM_PhaseC_Status = TX_LAMP_ERR;	/** ランプエラーをセット */
				}
				return (MDM_PhaseC_Status);	/**	戻り値ファイルエラーセット	*/
			}
			/*--------------------------------------------------------------*/
			/*	送信１ページ符号変換タスク・ＴＴＩエンコードデータ完了待ち	*/
			/*--------------------------------------------------------------*/
			tskno_CDC_EncodePageTask = 0xffff;	/* 関数の頭にも追加	96/07/24 */
			cre_tsk(&tskno_CDC_EncodePageTask, TSK_CDC_STXCODECONVERTPAGETASK, 0);	/**	スキャナ送信エンコードタスク起動	*/
			do {
				rcv_msg(mbxno.MDM_TaskSub, &MDM_Msg);	/**	エンコード開始メッセージ待ち	*/
			} while ( MDM_Msg->Message != MSG_TTI_COMPLETE );
			/*----------------------------------------------*/
			/*	エンコードＤＭＡ終了監視タスク起動			*/
			/*----------------------------------------------*/
			tskno_EncodeDMA_End = 0xffff;	/* 関数の頭にも追加	96/07/24 */
			cre_tsk(&tskno_EncodeDMA_End, TSK_MDM_ENCODEDMA_TC_DETECTTASK, NULL); /** エンコードＤＭＡ終了割り込み監視タスク	*/

			ModemMessage.Message = MSG_ENCODE_DMA_START;
			snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);	/**	エンコードＤＭＡ開始メッセージ送信	*/

			/*-------------------------------------------------------------
			** 読み取りタスクを起動する
			** 1998/08/12 H.Yoshikawa
			*/
			tskno_SCN_ScanningTask = 0xffff;
			cre_tsk(&tskno_SCN_ScanningTask, TSK_SCN_SCANNINGTASK, 0);
			
  #else
			/*--------------------------------------------------------------*/
			/*	送信１ページ符号変換タスク・ＴＴＩエンコードデータ完了待ち	*/
			/*--------------------------------------------------------------*/
			tskno_CDC_EncodePageTask = 0xffff;	/* 関数の頭にも追加	96/07/24 */
			cre_tsk(&tskno_CDC_EncodePageTask, TSK_CDC_STXCODECONVERTPAGETASK, 0);	/**	スキャナ送信エンコードタスク起動	*/
			do {
				rcv_msg(mbxno.MDM_TaskSub, &MDM_Msg);	/**	エンコード開始メッセージ待ち	*/
			} while ( MDM_Msg->Message != MSG_TTI_COMPLETE );
			/*----------------------------------------------*/
			/*	エンコードＤＭＡ終了監視タスク起動			*/
			/*----------------------------------------------*/
			tskno_EncodeDMA_End = 0xffff;	/* 関数の頭にも追加	96/07/24 */
			cre_tsk(&tskno_EncodeDMA_End, TSK_MDM_ENCODEDMA_TC_DETECTTASK, NULL); /** エンコードＤＭＡ終了割り込み監視タスク	*/

			ModemMessage.Message = MSG_ENCODE_DMA_START;
			snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);	/**	エンコードＤＭＡ開始メッセージ送信	*/
			/*--------------------------*/
			/*	スキャナオープン		*/
			/*--------------------------*/
			if (SCN_Open() == SCN_OPEN_ERROR) {		/**	スキャナオープンＮＧの時	S.Fukui Feb.23,1999	*/
				MDM_BreakTxTask();	/**	各子タスク終了処理	*/
				MDM_PhaseC_Status = TX_DOC_ERR;
				/*
				**	スキャナ送信でのランプチェックNGの時の処理を追加  1997/03/31 s.takeuchi
				*/
				if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_LAMP_ERROR) {	/** ランプエラー */
					MDM_PhaseC_Status = TX_LAMP_ERR;	/** ランプエラーをセット */
				}
				return (MDM_PhaseC_Status);	/**	戻り値ファイルエラーセット	*/
			}
  #endif /* (PRO_SCN_CODEC_TYPE == SOFTWARE) */
			break; /* switch (CodecPageStatus) */
		}
		break;
	case TX_BKUPRAM:
		cre_tsk(&tskno_MDM_BackupRamToEcmBufTask, TSK_MDM_BACKUPRAMTOECMBUFTASK, NULL);
		break;
	case TX_RELAYED_TX_REPORT:	/**	(複数ページにまたがるような)キャラクタ送信の時	*/
		switch (CodecPageStatus) {	/**	コーデックの状態	*/
		case CDC_BLOCK_END:	/**	ブロックエンドの時	*/
			/*	エンコード開始（ＤＭＡ起動）メッセージ送信	*/
			ModemMessage.Message = MSG_ENCODE_DMA_START;	/**	エンコード開始（ＤＭＡ起動）メッセージ送信	*/
			snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);
			break;

		default:	/**	送信コントロール監視タスクが終了状態の時	*/
			if (rtn = CheckTxSystemError()) { /* DOC_ERROR_MAINTE 2000/12/19 by K.Okada (PARIS仕様外)*/
				break;
			}


			/*	送信１ページ符号変換タスク起動	*/
			tskno_CDC_CTxCodeConvertTask = 0xffff;
			cre_tsk(&tskno_CDC_CTxCodeConvertTask, TSK_CDC_CTXCODECONVERTPAGETASK, NULL);	/**	送信１ページ符号変換タスク起動	*/
			do {
				rcv_msg(mbxno.MDM_TaskSub, &MDM_Msg);	/**	エンコード開始（ＴＴＩをＥＣＭバッファにセット完了）メッセージ待ち	*/
			} while ( MDM_Msg->Message != MSG_TTI_COMPLETE );

			/*	エンコードＤＭＡ終了監視タスク起動	*/
			tskno_EncodeDMA_End = 0xffff;
			cre_tsk(&tskno_EncodeDMA_End, TSK_MDM_ENCODEDMA_TC_DETECTTASK, NULL);	/**	エンコードＤＭＡ終了監視タスク起動	*/
			/*	エンコード開始（ＤＭＡ起動）メッセージ送信	*/
			ModemMessage.Message = MSG_ENCODE_DMA_START;
			snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);	/**	エンコード開始（ＤＭＡ起動）メッセージ送信	*/
			break;
		}
		break;
	case TX_CVR:	/**	カバーページ送信の時	*/
	case TX_RCR:	/**	受領証送信の時	*/
	default:
		/*	キャラクタ送信エンコードタスク	*/
		tskno_CDC_CTxCodeConvertTask = 0xffff;
		cre_tsk(&tskno_CDC_CTxCodeConvertTask, TSK_CDC_CTXCODECONVERTPAGETASK, NULL); /** キャラクタ送信エンコードタスク	*/
		break;
	}

	if (rtn) { /* DOC_ERROR_MAINTE 2000/12/19 by K.Okada */
		MDM_BreakTxTask();
		return (rtn);
	}

	/*	画データ送出処理	*/
	if (ecm_type == ECM_OFF) {	/**	Ｇ３送信時	*/
		rtn = G3_Tx();	/**	Ｇ３送信	*/
	}
	else {	/**	ＥＣＭ送信時	*/
		rtn = EcmTx();	/**	ＥＣＭ送信	*/
	}
	MDM_PhaseC_Status = rtn;	/**	フェーズＣステータスに戻り値セット	*/
	return(rtn);
}


/*************************************************************************
	module		:[Ｇ３送信]
	function	:[
		1.読み出すエンコードデータの先頭アドレスを獲得
		2.送出エンコードデータの残りバイト数を獲得する
		3.モデムバッファの書き込みアドレスを獲得する
		4.送出エンコードデータのバイト数を獲得する（通常２５６ｂｙｔｅ）
		5.モデムバッファ書き込み位置に送出エンコードデータを転送する
		6.Ｇ３モデムライト処理
	]
	return		:[
												MG3	MECM	SG3	SECM
		TX_PAGE_END					0			○	○		○	○		1ﾍﾟｰｼﾞ送信完了
		TX_BLOCK_END				1			×	○		×	○		64KByte送信完了
		TX_STOPPED					2			○	○		○	○		停止ＳＷ　ＯＮ
		TX_DOC_ERR					3			×	×		○	○		原稿繰り込み不良
		TX_LAMP_ERR					4			×	×		○	○		ﾗﾝﾌﾟｴﾗｰ
		TX_FILE_ERR					5			○	○		×	×		該当するﾒﾓﾘﾌｧｲﾙが存在しない
		TX_MEM_ERR					7			○	○		×	×		画像ﾒﾓﾘ画品質不良
		TX_1M_OVER					8 			×	×		○	○		ｽｷｬﾅ送信が１ｍを越えた
		TX_SEPARATE					9 			○	○		○	○		F網設定時、送信がA4 2枚分に達した
			○：戻り値あり
			×：戻り値なし
			△：未定
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/21]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE 	G3_Tx(void)
{
	/* ローカル変数宣言 */
	MESSAGE_t	*MDM_Msg;
	UBYTE		*ebf_base_rp;	/*	ＥＣＭバッファ先頭読み出しポインタ	*/
	UWORD	mse_line_cnt;	/*	ＭＳＥ処理用、ラインカウンタ	*/
	UWORD	mse_byte_cnt;	/*	ＭＳＥ処理用、３２ラインのバイト数	*/
	UBYTE	rtn;	/*	リターンコード	*/
	UBYTE	page_loop;	/*	１ページ完了フラグ　ループ制御用	*/
	UWORD	detect_eol_p;	/*	ＥＯＬ検出位置	*/
	UWORD	i;
	UWORD	w_cnt;	/*	送出データ数ワーク	*/
	UWORD	fill_cnt;	/*	フィル挿入データ数	*/
	UWORD	min_mse_cnt;	/*	ＭＳＥ総データ数	*/
	UBYTE		*ebf_tmp_rp;	/*	ＥＣＭバッファＥＯＬチェック用テンポラリ読み出しポインタ	*/
	UBYTE	cdc_stat;
#if defined (KEISATSU) /* 警察FAX 05/08/20 石橋正和 */
	BOOL brts; /* RTSを送出するか */
	
	brts = TRUE;
#endif
	
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* ECM_BUFFER_OVER */

	if (CommunicateType == TX_G3_SCAN) {
		return(G3_TxSub());
	}
#endif

	/*	変数初期化処理	*/
	mse_line_cnt = 0;	/**	ＭＳＥライン数初期化	*/
	mse_byte_cnt = 0;	/**	ＭＳＥ処理用符号量初期化	*/
	ebf_base_rp = (UBYTE *)&EcmBuffer[0][0];	/**	ＥＣＭバッファ読み出し先頭アドレス設定	*/
	ebr_cnt = 0;	/**	ＥＣＭバッファ読み出しバイト数	*/
	rtn = 0;	/**	リターンコード初期化	*/
	page_loop = 1;	/**	１ページ完了フラグ初期化	*/

	/*	ダミーデータ送出監視	*/
	do {
		rcv_msg(mbxno.MDM_PixDummy, &MDM_Msg);	/**	ダミーデータ送出終了メッセージ受信	*/
	} while ( MDM_Msg->Message != MSG_DUMMY_PIX_TIME_OVER );
	if (timerID_DummyPixTimer != 0xff) {
		CMN_MultiTimer10msStop(&timerID_DummyPixTimer);	/**	ダミーデータ監視タイマタスク終了	*/
	}

	/*	符号変換完了待ち
	**	（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）
	*/
	rtn = MDM_WaitForTxStartOrTxError();
	switch (rtn) {
	case TX_LAMP_ERR:
	case TX_DOC_ERR:
	case TX_1M_OVER:
	case TX_MEM_ERR:
		MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
		return rtn;
		break;
	default:
		break;
	}


	/*	送出未処理のエンコードデータ数取得	*/
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	RemainEncodeData = EncodeDataCount;	/**	送出未処理のエンコードデータ数取得	*/
	cdc_stat = CodecPageStatus;
	TxStartFlag = 0;	/**	画データ送出フラグをクリア	*/
	CMN_EnableInterrupt();	/**	割り込み許可	*/

	/*	画データ送出ループ　*/
	while (page_loop) {	/**	エンコードデータがなくなり、ＲＴＣ（その他）を検出するまでループ	*/
		/*	送出データ数（モデムバッファ書き込み数）設定	*/
#if (PRO_CLASS1 == ENABLE) /* Added by H.Kubo 1998/03/04 */
		next_mbf_set_cnt = GetCount(RemainEncodeData, MDM_ModemDmaSize);	/**	１ブロック送出バイト数取得（２５６ｂｙｔｅ以下）	*//** 256 Bytes **/
#else
		next_mbf_set_cnt = GetCount(RemainEncodeData, MODEM_DMA_SIZE);	/**	１ブロック送出バイト数取得（２５６ｂｙｔｅ以下）	*//** 256 Bytes **/
#endif
		/*	トータルライン数、ＭＳＥライン数、（次送出バイト数再設定）処理
		**	符号化データのＥＯＬはバイト単位でないとできません
		*/
		if ((SYS_DocBlock.Dst.Code != SYS_MMR_CODE) &&
		    (SYS_DocBlock.Dst.Code != SYS_MG3_CODE) &&
		    (SYS_DocBlock.Dst.Code != SYS_JBIG_CODE) &&
		    (SYS_DocBlock.MSE_Method == MSE1) &&
		    (SYS_DocBlock.MinimumLineSize != 0)) {	/**	符号化方式がＭＨとＭＲでＭＳＥで最小伝送時間が０ｍｓでない時	*/
		    ebf_tmp_rp = ebf_base_rp + ebr_cnt;	/**	現在のＥＣＭバッファ読み出し位置設定 */
			detect_eol_p = 0;	/**	ＥＯＬ検出位置クリア	*/
			for (i = 0; i < next_mbf_set_cnt;) {	/**	１ブロック（２５６ｂｙｔｅ以下）分、ＥＯＬチェック	*/
				if (*ebf_tmp_rp == EOL_FRAME1) {	/**	ＥＯＬ、１バイト目検出時	*/
					i++;	/**	チェックカウントインクリメント	*/
					ebf_tmp_rp++;	/**	ＥＯＬ検出位置インクリメント	*/
					if (((*ebf_tmp_rp)&EOL_FRAME2_MASK) == EOL_FRAME2) {	/**	ＥＯＬ、２バイト目検出時	*/
						detect_eol_p = i-1;	/**	ＥＯＬ検出位置設定	*/
						mse_line_cnt++;	/**	ＭＳＥライン数更新	*/
						if (mse_line_cnt == (MSE_LINE+1)) {	/**	ＭＳＥ処理有りの時 ＆＆　ＭＳＥラインの時	*/
							break;
						}
						i++;	/**	チェックカウントインクリメント	*/
						ebf_tmp_rp++;	/**	ＥＯＬ検出位置インクリメント	*/
					}
				}
				else {	/**	ＥＯＬでないとき	*/
					i++;	/**	チェックカウントインクリメント	*/
					ebf_tmp_rp++;	/**	ＥＯＬ検出位置インクリメント	*/
				}
			}
			if (detect_eol_p != 0) {
				if (mse_line_cnt == (MSE_LINE+1)) {
					next_mbf_set_cnt = detect_eol_p;	/**	送出データ数（モデムバッファ書き込み数）設定	*/
				}
				else {
					next_mbf_set_cnt = detect_eol_p;	/**	送出データ数（モデムバッファ書き込み数）設定	*/
					mse_line_cnt--;	/**	ＭＳＥライン数デクリメント	*/
				}
			}
			else {
				mse_line_cnt--;	/**	ＭＳＥライン数デクリメント	*/
			}
			mse_byte_cnt += next_mbf_set_cnt;	/**	ＭＳＥ用バイト数設定	*/
		}

		/*	画データ終了判定処理	*/
		if ( RemainEncodeData == next_mbf_set_cnt ) {	/**	送出エンコードデータがない時	*/
			switch (cdc_stat) {	/**	コーデック状態	*/
			case CDC_RTC_DET:	/**	ＲＴＣ検出時	*/
			case CDC_DECODE_ERROR:	/**	デコードエラー時	*/
			case CDC_STOPPED:	/**	ストップＳｗ時	*/
			case CDC_DOC_OVER:	/**	1mオーバーの時	*/
				ModemBlock.Chain = SET_COMPL; /* 送信データセット完了		*/
				break;
			default:	/**	その他	*/
				break;
			}
		}

		/*	フレーム書き込みモデムバッファ獲得処理	*/
		while (ModemControl.UsedCount == MODEM_BUFFER_MAX) {	/**	モデムバッファ使用本数が８本の時	*/
			wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/
		}

		/*	ＥＣＭバッファからモデムバッファにプログラム転送	*/
		/* メモリ－メモリの DMA 転送にしてみます。by H.Kubo 1998/02/05 */
		MemoryMove((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0],
		           (UBYTE *)(ebf_base_rp+ebr_cnt), next_mbf_set_cnt);	/**	ＥＣＭバッファからモデムバッファにプログラム転送	*/
		/*	Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／バイト数登録）	*/
		if (ModemBlock.Chain == SET_COMPL) {	/**	最終ブロック送出時	*/
#if defined (KEISATSU) /* 警察FAX 05/08/20 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && (DBG_G3_TCF_OriginalPosition == 0)) {
				TxG3_WriteWithRTS_Sent((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0], next_mbf_set_cnt + 7, brts); /* Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／バイト数登録）	*/
				brts = FALSE;
			}
			else {
				TxG3_Write((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0], next_mbf_set_cnt + 7); /* Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／バイト数登録）	*/
			}
#else
			TxG3_Write((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0], next_mbf_set_cnt + 7); /* Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／バイト数登録）	*/
#endif
		}
		else {	/**	その他の時	*/
#if defined (KEISATSU) /* 警察FAX 05/08/20 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && (DBG_G3_TCF_OriginalPosition == 0)) {
				TxG3_WriteWithRTS_Sent((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0], next_mbf_set_cnt, brts); /* Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／バイト数登録）	*/
				brts = FALSE;
			}
			else {
				TxG3_Write((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0], next_mbf_set_cnt); /* Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／バイト数登録）	*/
			}
#else
			TxG3_Write((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0], next_mbf_set_cnt); /* Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／バイト数登録）	*/
#endif
		}

		/*	ＥＣＭバッファ読み出し数更新	*/
		ebr_cnt += (UDWORD)next_mbf_set_cnt;	/**	ＥＣＭバッファ読み出しバイト数更新	*/

		/*	タスクウェイト	*/
		wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/

		/*	送出未処理エンコードデータ数更新処理	*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		RemainEncodeData = EncodeDataCount - ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/
		cdc_stat = CodecPageStatus;
		TxStartFlag = 0;	/**	画データ送出フラグをクリア	*/
		CMN_EnableInterrupt();	/**	割り込み許可	*/

		/*	強制終了処理(ストップ処理）		*/
		if (MDM_TxStopSwFlag == 0) {	/**	画データ用ストップＳｗがＯＦＦの時	*/
			if (SYS_FaxComStopSwitch()) {	/**	ストップＳｗＯＮの時	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				if (MDM_TxForceStop()) {	/**	強制終了時 PRO_QUICK_TX */
					rtn = TX_STOPPED;	/**	戻り値ストップＳｗＯＮ設定	*/

					if ((CommunicateType == TX_ECM_SCAN) ||
					    (CommunicateType == TX_G3_SCAN)) {	/**	交信タイプがスキャナ送信の時	*/
						if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {	/**	スキャナモータがストップしていない時	*/
							SCN_StopMotor();	/**	スキャナモータストップ	*/
							SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
							LampOff();	/**	ランプＯＦＦ	*/
						}
					}
				}
				MDM_TxStopSwFlag = 1;	/**	画データ用ストップＳｗをＯＮに設定	*/
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_FAXCOM;	/**	マシンステータスの通信ストップ解除	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
			else {
				rtn = CheckTxSystemError();	/**	送信異常チェック	*/
			}
			if (rtn) {	/**	送信異常有りの時	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				return (rtn);
			}
		}

		/*	ＭＳＥ処理	*/
		if ((SYS_DocBlock.Dst.Code != SYS_MMR_CODE) &&
		    (SYS_DocBlock.Dst.Code != SYS_MG3_CODE) &&
		    (SYS_DocBlock.Dst.Code != SYS_JBIG_CODE) && /* added by H.Kubo 1998/06/22 */
		    (SYS_DocBlock.MSE_Method == MSE1) &&
		    (SYS_DocBlock.MinimumLineSize != 0) &&
		    (mse_line_cnt == (MSE_LINE + 1 ) )) { /** ＭＳＥ処理有りの時＆＆ＭＭＲ・ＭＧ３以外＆＆ＭＳＥライン＆＆最小伝送時間が０以外の時	*/
			min_mse_cnt = (UWORD)(SYS_DocBlock.MinimumLineSize * 32); /** ＭＳＥ（３２ラインの最小伝送符号量）総データ数計算	*/
			if (min_mse_cnt > mse_byte_cnt) {	/**	フィル挿入する時	*/
				fill_cnt = (min_mse_cnt-mse_byte_cnt);	/**	ＭＳＥ　フィル挿入データ数取得	*/
				do {	/**	フィル送出データがなくなるまでループ	*/
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
					w_cnt = GetCount(fill_cnt, MDM_ModemDmaSize);	/**	フィル送出バイト数設定（２５６ｂｙｔｅ） */ /** 256 Bytes **/
#else
					w_cnt = GetCount(fill_cnt, MODEM_DMA_SIZE);	/**	フィル送出バイト数設定（２５６ｂｙｔｅ） */ /** 256 Bytes **/
#endif
					while (ModemControl.UsedCount == MODEM_BUFFER_MAX) {	/**	モデムバッファ使用本数が８本の時	*/
						wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/
					}
#if defined (KEISATSU) /* 警察FAX 05/08/20 石橋正和 */
					if ((FCM_S1_Scramble == TRUE) && (DBG_G3_TCF_OriginalPosition == 0)) {
						TxG3_WriteWithRTS_Sent(&ModemZeroBuffer[0], w_cnt, brts);	/**	送出処理	*/
						brts = FALSE;
					}
					else {
						TxG3_Write(&ModemZeroBuffer[0], w_cnt);	/**	送出処理	*/
					}
#else
					TxG3_Write(&ModemZeroBuffer[0], w_cnt);	/**	送出処理	*/
#endif
					fill_cnt -= w_cnt;	/**	フィル送出バイト数更新	*/
				} while (fill_cnt > 0);
			}
			mse_byte_cnt = 0;	/**	ＭＳＥ符号量（バイト数）クリア	*/
			mse_line_cnt = 0;	/**	ＭＳＥライン数クリア	*/
		}

		/*	送出終了判定／子タスク終了処理	*/
		if (RemainEncodeData == (UDWORD)0) {	/**	エンコードデータがない時	*/
			switch (cdc_stat) {	/**	エンコードステータス	*/
			case CDC_CONTINUE:	/**	エンコード中の時	*/
				MDM_DebugDataWaitCnt++;

				/*	エンコードデータ（２５６ｂｙｔｅ）が揃うよりもモデムバッファにセットする方が速い時
				**	符号変換完了待ち（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）
				*/
				rtn = MDM_WaitForTxStartOrTxError();
				switch (rtn) {
				case TX_LAMP_ERR:
				case TX_DOC_ERR:
				case TX_1M_OVER:
				case TX_MEM_ERR:
					MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
					return rtn;
					break;
				default:
					break;
				}

				/*	送出未処理のエンコードデータ数取得	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				RemainEncodeData = EncodeDataCount - ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/
				cdc_stat = CodecPageStatus;
				TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				break;
			case CDC_BLOCK_END:	/**	ブロックエンドの時	*/
				/*	エンコード開始メッセージ送信	*/
				if( CommunicateType == TX_G3_SCAN ) {
				ModemMessage.Message = MSG_ENCODE_DMA_START;
				snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);	/*	エンコード開始メッセージ送信	*/
				}
				else{
					ModemMessage.Message = MSG_ENCODE_DMA_START;
					snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);	/*	エンコード開始メッセージ送信	*/
				}
				/*	符号化完了待ち（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）	*/
					rtn = MDM_WaitForTxStartOrTxError();
					switch (rtn) {
					case TX_LAMP_ERR:
					case TX_DOC_ERR:
					case TX_1M_OVER:
					case TX_MEM_ERR:
						MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
						return rtn;
						break;
					default:
						break;
					}

				/**	送出未処理のエンコードデータ数取得	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
				RemainEncodeData = EncodeDataCount;	/**	送出未処理エンコードデータ数更新	*/
				cdc_stat = CodecPageStatus;
				CMN_EnableInterrupt();	/**	割り込み許可	*/

				/*	ＥＣＭバッファ読み出し数初期化	*/
				ebr_cnt = 0;	/**	ＥＣＭバッファ読み出し数初期化	*/
				break;
			case CDC_RTC_DET:	/**	ＲＴＣ検出の時	*/
				page_loop = 0;	/**	１ページループフラグセット	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				rtn = TX_PAGE_END;	/**	戻り値１ページ送信完了設定	*/
				break;
			case CDC_STOPPED:	/**	正常終了（ストップＳｗＯｎ）の時	*/
				page_loop = 0;	/**	１ページループフラグセット	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				rtn = TX_STOPPED;	/**	戻り値ストップＳＷ設定	*/
				break;
			case CDC_DOC_OVER:	/**	1mオーバーの時	*/
				page_loop = 0;	/**	１ページループフラグセット	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				rtn = TX_1M_OVER;	/**	戻り値1mオーバー	*/
				break;
			default:	/**	その他	*/
				page_loop = 0;
				MDM_BreakTxTask();
				rtn = TX_1M_OVER;	/* T.3.1 error */
				break;
			}
		}
	}
	return (rtn);
}


/*************************************************************************
	module		:[ＥＣＭ送信]
	function	:[
		1.
	]
	return		:[
												MG3	MECM	SG3	SECM
		TX_PAGE_END					0			○	○		○	○		1ﾍﾟｰｼﾞ送信完了
		TX_BLOCK_END				1			×	○		×	○		64KByte送信完了
		TX_STOPPED					2			○	○		○	○		停止ＳＷ　ＯＮ
		TX_DOC_ERR					3			×	×		○	○		原稿繰り込み不良
		TX_LAMP_ERR					4			×	×		○	○		ﾗﾝﾌﾟｴﾗｰ
		TX_FILE_ERR					5			○	○		×	×		該当するﾒﾓﾘﾌｧｲﾙが存在しない
		TX_MEM_ERR					7			○	○		×	×		画像ﾒﾓﾘ画品質不良
		TX_1M_OVER					8 			×	×		○	○		ｽｷｬﾅ送信が１ｍを越えた
		TX_SEPARATE					9 			○	○		○	○		F網設定時、送信がA4 2枚分に達した
			○：戻り値あり
			×：戻り値なし
			△：未定
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/24]
	author		:[曽根岡拓]
*************************************************************************/
#if defined (SAKAKI)	/* 1998/11/19 *//* 2002/09/18 By M.Maeda */
UBYTE	ECM_ReadPageCounter = 0;
#endif
UBYTE 	EcmTx(void)
{
	/* ローカル変数宣言 */
	UBYTE	rtn;	/*	リターンコード	*/
	UBYTE	i;
	UBYTE	page_loop;
	UBYTE	cdc_stat;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* ECM_BUFFER_OVER */

	if (CommunicateType == TX_ECM_SCAN) {
		return(EcmTxSub());
	}
#endif


	/*	変数初期化処理	*/
	ebr_cnt = 0;	/**	ＥＣＭバッファ読み出しバイト数	*/
	rtn = 0;	/**	リターンコード初期化	*/
	MDM_EcmFrameNumber = 0;	/**	ＥＣＭフレームナンバー初期化	*/

#if defined (SAKAKI)	/* 1998/11/19 *//* 2002/09/18 By M.Maeda */
	ECM_ReadPageCounter ++;
#endif
    /*----------------------*/
    /*  同期信号待ち処理    */
    /*----------------------*/
	/* 日立メールシステムにて画データ前同期信号が短いと受信できないという不具合（ＫＩＲＩにて発生）があるので反映させます */
	/* 1998/06/02 by T.Soneoka */
	wai_tsk(200/10);	/**	タスクウェイト２００ｍｓ	*/

	/*	先頭２５６ｂｙｔｅブロック送出処理待ち処理（ＤＭＡ終了割り込み　ＯＲ　１ページ符号変換タスクより）	*/
	rtn = MDM_WaitForTxStartOrTxError();
	switch (rtn) {
	case TX_LAMP_ERR:
	case TX_DOC_ERR:
	case TX_1M_OVER:
	case TX_MEM_ERR:
		MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
		return rtn;
		break;
	default:
		break;
	}

	/*
	**  by T.Soneoka 1997/12/17
	*/
	if (SYS_DocBlock.Dst.Code == SYS_JBIG_CODE) {
		MDM_JBG_ReadBIH();
	}

	/*	送出未処理のエンコードデータ数取得	*/
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	RemainEncodeData = EncodeDataCount;	/**	送出未処理エンコードデータ数更新	*/
	cdc_stat = CodecPageStatus;
	TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
	CMN_EnableInterrupt();	/**	割り込み許可	*/

	/*	ＦＣＤフレーム送信登録／送出処理	*/
	page_loop = 1;	/**	１ページ完了フラグ設定	*/
	while (page_loop) {	/**	１ページ送信ループ（エンコードデータがなくなり、ＲＴＣ（その他）を検出するまで）*/
		/*	送出バイト数取得処理、通常１ブロック２５６ｂｙｔｅ
		**	次送出バイト数更新
		*/
		next_mbf_set_cnt = GetCount(RemainEncodeData, FcomEcmSize);	/**	１ブロック送出バイト数切り出し（２５６ｂｙｔｅ以下）	*/

		/*	フレーム書き込みモデムバッファ獲得処理	*/
		ModemBufferWaiSem(ModemControl.WritePoint);	/**	フレーム書き込みモデムバッファ獲得	*/
		SetClear(MDM_ModemBuffer[ModemControl.WritePoint], MODEM_BUFFER_LENGTH, 0x00);

		/*	ＦＣＤフレーム送信登録（ＥＣＭバッファからモデムバッファにプログラム転送）／送出処理	*/
		WriteFCD(MDM_EcmFrameNumber, &MDM_ModemBuffer[ModemControl.WritePoint][0], (UBYTE *)&EcmBuffer[0][0] + ebr_cnt, next_mbf_set_cnt);

		/*	ＥＣＭフレームナンバー更新	*/
		MDM_EcmFrameNumber++;	/**	ＥＣＭフレームナンバーインクリメント	*/

		/*	ＥＣＭバッファ読み出し数更新	*/
		ebr_cnt += (UDWORD)next_mbf_set_cnt;	/**	ＥＣＭバッファ読み出しバイト数更新	*/

		/*	送出未処理エンコードデータ数取得処理	*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		RemainEncodeData = EncodeDataCount - ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/
		cdc_stat = CodecPageStatus;
		TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
		CMN_EnableInterrupt();	/**	割り込み許可	*/

		/*	強制終了処理(ストップ処理）		*/
		if (MDM_TxStopSwFlag == 0) {	/**	画データ用ストップＳｗがＯＦＦの時	*/
			if (SYS_FaxComStopSwitch()) {	/**	ストップＳｗ　ＯＮの時	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/

				if (MDM_TxForceStop()) {	/**	強制終了時 PRO_QUICK_TX	*/
					rtn = TX_STOPPED;	/**	戻り値ストップＳｗＯＮ設定	*/
					if ((CommunicateType == TX_ECM_SCAN) ||
					    (CommunicateType == TX_G3_SCAN)) {	/**	交信タイプがスキャナ送信の時	*/
						if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {	/**	スキャナモータがストップしていない時	*/
							SCN_StopMotor();	/**	スキャナモータストップ	*/
							SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
							LampOff();	/**	ランプＯＦＦ	*/
						}
					}
				}
				MDM_TxStopSwFlag = 1;	/**	画データ用ストップＳｗをＯＮに設定	*/
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_FAXCOM;	/**	マシンステータスの通信ストップ解除	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
			else {
				rtn = CheckTxSystemError();	/**	送信異常チェック	*/
			}
			if (rtn) {	/**	送信異常有りの時	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				return (rtn);
			}
		}

		/*	送出終了／子タスク終了処理	*/
		if (RemainEncodeData == (UDWORD)0) {	/**	エンコードエンコードデータがないとき	*/
			switch (cdc_stat) {	/**	コーデックの状態	*/
			case CDC_CONTINUE:	/**	エンコード中	*/
				MDM_DebugDataWaitCnt++;
				/*	モデムバッファにセットする方が速い時
				**	符号変換完了待ち（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）
				*/
				rtn = MDM_WaitForTxStartOrTxError();
				switch (rtn) {
				case TX_LAMP_ERR:
				case TX_DOC_ERR:
				case TX_1M_OVER:
				case TX_MEM_ERR:
					MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
					return rtn;
					break;
				default: /* 送信開始 */
					break; /* 処理続行 */
				}

				/*	送出未処理のエンコードデータ数取得	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				RemainEncodeData = EncodeDataCount - ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/
				cdc_stat = CodecPageStatus;
				TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				break;
			case CDC_BLOCK_END:	/**	ＥＣＭバッファオーバの時	*/
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				rtn = TX_BLOCK_END;	/**	戻り値ブロックエンド設定	*/
				break;
			case CDC_RTC_DET:	/**	ＲＴＣ検出の時	*/
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				MDM_BreakTxTask();	/**	各子タスク終了処理	*/
				rtn = TX_PAGE_END;	/**	戻り値１ページ送信完了設定	*/
				break;
			case CDC_STOPPED:	/**	正常ストップＳｗ終了の時	*/
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				rtn = TX_STOPPED;	/**	戻り値ストップＳＷ設定	*/
				MDM_BreakTxTask();	/**	各子タスク終了処理	*/
				break;
			case CDC_DOC_OVER:	/**	1mオーバーの時	*/
				page_loop = 0;	/**	１ページループフラグセット	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				rtn = TX_1M_OVER;	/**	戻り値1mオーバー	*/
				break;
			default:
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				MDM_BreakTxTask();	/**	各子タスク終了処理	*/
				rtn = TX_1M_OVER;	/* T.3.1 error */
				break;
			}
		}

		/*	ＴＴＩ送出と画データとの間で２５６ｂｙｔｅそろわない時	 */
		else if (RemainEncodeData < (UDWORD)FcomEcmSize) {	/**	エンコードエンコードデータがないとき	*/
			switch (cdc_stat) {	/**	コーデックの状態	*/
			case	CDC_CONTINUE:	/**	エンコード中の時	*/
				MDM_DebugDataWaitCnt++;
				/*	モデムバッファにセットする方が速い時
				**	符号変換完了待ち（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）
				*/
				rtn = MDM_WaitForTxStartOrTxError();
				switch (rtn) {
				case TX_LAMP_ERR:
				case TX_DOC_ERR:
				case TX_1M_OVER:
				case TX_MEM_ERR:
					MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
					return rtn;
					break;
				default:
					break;
				}

				/*	送出未処理のエンコードデータ数取得	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				RemainEncodeData = EncodeDataCount - ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/
				cdc_stat = CodecPageStatus;
				TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				break;
			default:	/**	その他の時	*/
				break;
			}
		}
	}
	MDM_EcmFrameNumber--;	/**	ＥＣＭフレームナンバーデクリメント	*/
	LastEcmFrameNumber = MDM_EcmFrameNumber;	/**	最終ＥＣＭフレームナンバー設定	*/
	LastEcmFrameLength = next_mbf_set_cnt;	/**	最終ＥＣＭフレームサイズ設定	*/

	/*	ＲＣＰフレーム送信登録／送出処理	*/
	for (i = 0; i < RCP_COUNT; i++) {	/**	ＲＣＰフレーム３個送出するまで	*/
		/*	フレーム書き込みモデムバッファ獲得処理	*/
		ModemBufferWaiSem(ModemControl.WritePoint);	/**	フレーム書き込みモデムバッファ獲得	*/

		/*	最終フレーム登録	*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/

		/**	ＲＣＰフレーム送信登録／送出処理	*/
		WriteRCP(&MDM_ModemBuffer[ModemControl.WritePoint][0]);		/**	ＲＣＰフレーム登録	*/

		/*	最終フレーム登録	*/
		if (i == (RCP_COUNT - 1)) {	/**	最後のＲＣＰかチェック	*/
			ModemBlock.Chain = SET_COMPL;	/**	最終フレーム登録	*/
		}
		CMN_EnableInterrupt();	/**	割り込み許可	*/

#if (0)	/** 上でモデムバッファはセマフォ管理をしているのでこのウエイトはいらない By O.K Feb.06,1996 **/
		/*	タスクウェイト	*/
		wai_tsk(50/10);	/**	タスクウェイト５０ｍｓ	*/
#endif

	}
	return (rtn);
}


/*************************************************************************
	module		:[メモリ送信メモリリードＤＭＡ監視タスク]
	function	:[
		1.コーデックに対してデータをＤＭＡ転送する（オープン／リード処理）
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_MTxReadDMA_Task(void){}]
	date		:[1994/03/02]
	update		:[1995/12/12]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void  MDM_MTxReadDMA_Task(void)
{
	UWORD	open_result;
	UBYTE 	read_result;

	/*	メモリリードオープン	*/
	open_result = MEM_ReadOpen(&SYS_DocBlock.Index, &MDM_MemoryExecData);	/**	メモリリードオープン */

	/*	メモリオープン結果メッセージ送信（ＥＣＭ受信監視タスクへ）	*/
	ModemMessage.Message = open_result;
	snd_msg(mbxno.MDM_MTxReadDMA_Task, &ModemMessage);	/**	メモリリードオープン結果メッセージ送信	*/

	/* 1997/01/15 Y.Murata
	 * もし、メモリリードオープンでＮＧが返ってきたらどうなる？
	 * ブレープの場合動作がおかしくなる。ＤＰＲでリセット及びイリーガルアクセスがでてしまう。
	 * オープンでＮＧの時はメモリリードをオープンしない。
	*/

	if (open_result == MEM_OK) {
		/*	メモリリード	*/
		read_result = MEM_Read(MEM_MODEM, &MDM_MemoryExecData);	/**	メモリリード	*/  /* Modified by H.Kubo 1997/07/07 */
	}
	else {
		/* To stop the emulator, use the following code. by H.Kubo 1997/07/11 */

			outp((UDWORD)0,(UBYTE)0); /* WriteProtectError for ICE */	/**オプションボードをリセットしてください*/
	}
	wai_tsk(0xffff);	/**	タスクウェイト無限	*/
}


/*************************************************************************
	module		:[ＥＣＭ送信部分ページ要求]
	function	:[
		1.ＥＣＭステータスが無効のフレームを再送する
		2.ＲＣＰフレームを送信する
	]
	return		:[
		送出フレーム番号（数）　０～２５５
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/26]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE		MDM_TxEcmPartialPage(void)
{
	WORD	fm_cnt;	/*	送信フレーム数	*/
	UWORD	fld;	/*	モデム	*/
	UWORD	i;

	fm_cnt = -1;	/**	送信フレーム数初期化	*/

	/* 復活させます。日立メールシステムにて画データ前同期信号が短いと受信できないという不具合（ＫＩＲＩにて発生）があるので反映させます */
	wai_tsk(210/10);	/**	タスクウェイト２１０ｍｓ	*/

	/*	エラーフレーム検索処理	*/
	for (fld = 0; fld <= (UWORD)LastEcmFrameNumber; fld++) {	/**	今送出したフレーム数までＦＩＦをチェック	*/

		/*	ＦＩＦステータスが有効／無効をチェック	*/
		if (CheckEcmStatusExtRom(fld) == 1) {	/**	ＦＩＦステータスが有効／無効をチェック	*/
			/*	フレーム書き込みモデムバッファ獲得処理	*/
			ModemBufferWaiSem(ModemControl.WritePoint);	/**	フレーム書き込みモデムバッファ獲得	*/
			SetClear(MDM_ModemBuffer[ModemControl.WritePoint], MODEM_BUFFER_LENGTH, 0x00);

			/**	ＦＣＤフレーム送信登録／送出処理	*/
			if (fld == (UWORD)LastEcmFrameNumber) {	/**	最終フレームの時	*/
				WriteFCD(fld, &MDM_ModemBuffer[ModemControl.WritePoint][0],(UBYTE *)&EcmBuffer[fld][0], LastEcmFrameLength);	/**	ＦＣＤフレーム登録・送出	*/
			}
			else {	/**	その他の時	*/
				WriteFCD(fld, &MDM_ModemBuffer[ModemControl.WritePoint][0],(UBYTE *)&EcmBuffer[fld][0], FcomEcmSize);	/**	ＦＣＤフレーム登録・送出	*/
			}

			/*	ＥＣＭ送信フレーム数を更新	*/
			fm_cnt++;	/**	ＥＣＭ送信フレーム数を更新	*/

#if (0)	/** 上でモデムバッファはセマフォ管理をしているのでこのウエイトはいらない By O.K Feb.06,1996 **/
//			/*	タスクウェイト	*/
//			wai_tsk(50/10);	/**	タスクウェイト５０ｍｓ	*/
#endif

		}
	}

	/**	ＲＣＰフレーム送信登録／送出処理（３個送出）	*/
	for (i = 0; i < RCP_COUNT; i++) {
		/*	フレーム書き込みモデムバッファ獲得処理	*/
		ModemBufferWaiSem(ModemControl.WritePoint);	/**	フレーム書き込みモデムバッファ獲得	*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/

		/*	ＲＣＰフレーム送信登録／送出処理	*/
		WriteRCP(&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/**	ＲＣＰフレーム送信登録／送出処理	*/

		/*	最終フレーム登録	*/
		if (i == (RCP_COUNT - 1)) {	/**	最後のＲＣＰかチェック	*/
			ModemBlock.Chain = SET_COMPL;	/**	最終フレーム登録	*/
		}
		CMN_EnableInterrupt();	/**	割り込み許可	*/
	}
	return ((UBYTE)fm_cnt);
}


/*************************************************************************
	module		:[ＦＣＤフレーム送信登録]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void near	WriteFCD(UWORD ,unsigned char far *,unsigned char far *,UWORD ){}]
	date		:[1993/12/24]
	update		:[1995/12/12]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void 	WriteFCD(
	UWORD 	frame_number,	/**	ＥＣＭフレームナンバー	*/
	UBYTE	*mbfwp,	/**	モデムバッファ書き込みポインタ	*/
	UBYTE	*ebfrp,	/**	ＥＣＭバッファ読み出しポインタ	*/
	UWORD 	size)	/**	書き込みサイズ	*/
{
	/*	各フィールドモデムバッファ設定	*/
	*mbfwp = HDLC_A;	/**	ＨＤＬＣ　アドレスフィールド設定	*/
	mbfwp[1] = HDLC_C;	/**	ＨＤＬＣ　制御フィールド設定	*/
	mbfwp[2] = HDLC_FCD;	/**	ＨＤＬＣ　ファクシミリ制御フィールド（ＦＣＦ）設定	*/
	mbfwp[3] = (UBYTE) frame_number; /**	ＨＤＬＣ　ファクシミリ情報フィールド（ＦＩＦ）　フレーム番号設定	*/

	/*	ＥＣＭバッファからモデムバッファにプログラム転送	*/
	/* メモリ－メモリの DMA 転送にしてみます。by H.Kubo 1998/02/05 */
	MemoryMove((mbfwp+4), ebfrp, size);	/**	ＨＤＬＣ　ファクシミリ情報フィールド（ＦＩＦ）	データフィールド設定	*/

	/*----------------------*/
	/*	モデムライト処理	*/
	/*----------------------*/
	/*	モデムライト処理	*/
	/*----------------------*/
	/* Ported from ORANGE\SRC\MDMTXPIX.C by H.Kubo 1997/07/16 */
	if (CommunicateType == TX_ECM_BKUPRAM) {   /** 高速リモート診断データ  */
		TxEcmWrite(mbfwp, (size+4));			/** 可変で送信 */
	}
	else {
		TxEcmWrite(mbfwp, (FcomEcmSize+4));	/**	送信ＦＣＤフレームライト処理	*/
	}
}


/*************************************************************************
	module		:[ＲＣＰフレーム送信登録]
	function	:[
		1.モデムバッファに各ＨＤＬＣフィールド（ＲＣＰ）を設定する
		2.モデムライト実行する
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void near	WriteRCP(unsigned char	far *){}]
	date		:[1993/12/24]
	update		:[1995/12/12]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void 	WriteRCP(UBYTE			*mbfwp)	/**	モデムバッファ書き込みポインタ	*/
{
	/*	各フィールドモデムバッファ設定	*/
	*mbfwp = HDLC_A;	/**	ＨＤＬＣ　アドレスフィールド設定	*/
	mbfwp[1] = HDLC_C;	/**	ＨＤＬＣ　制御フィールド設定	*/
	mbfwp[2] = HDLC_RCP;	/**	ＨＤＬＣ　ファクシミリ制御フィールド（ＦＣＦ）設定	*/

	/*	モデムライト処理	*/
	TxEcmWrite(mbfwp, RCP_SIZE);	/**	送信ＲＣＰフレームライト処理	*/

}


/*************************************************************************
	module		:[送信ＰＩＸクローズ]
	function	:[
		1.Ｇ３／ＥＣＭモードに応じて、各クローズ処理を実行する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/25]
	author		:[曽根岡拓]
*************************************************************************/
void 	MDM_TxPixClose(UBYTE ecm_type)
{
	/*	各モード送信クローズ関数処理	*/
	switch (ecm_type) {	/**	ＥＣＭタイプ	*/
	case ECM_OFF:	/**	Ｇ３送信の時	*/
		TxG3_Close();	/**	Ｇ３送信クローズ処理	*/
		break;
	case ECM_ON:	/**	ＥＣＭ送信の時	*/
		TxEcmClose();	/**	ＥＣＭ送信クローズ処理	*/
		break;
	}
}

/*************************************************************************
	module		:[送信コントロールタスク強制終了処理]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/24]
	author		:[曽根岡拓]
*************************************************************************/
void  MDM_BreakTxTask(void)
{
	switch (CommunicateType) {	/**	交信種別	*/

	/* The follows are chinged by O.Kimoto
	** Becase #if paragraph is not neccesary.
	** By O.Kimoto 1997/02/27
	*/
	case TX_G3_SCAN:	/**	スキャナＧ３送信の時	*/
		if (timerID_DummyPixTimer != 0xff) {
			CMN_MultiTimer10msStop(&timerID_DummyPixTimer);	/**	ダミーデータ監視タイマタスク終了	*/
		}
	case TX_ECM_SCAN:	/**	スキャナＥＣＭ送信の時	*/
		/*------------------------------------------*/
		/*	スキャナ送信１ページ符号化タスク終了	*/
		/*------------------------------------------*/
		if (tskno_CDC_EncodePageTask != 0xffff) {
			del_tsk(&tskno_CDC_EncodePageTask);	/**	１ページエンコードタスク終了	*/
		}
#if (0)	/* 下記処理ではスキャナ送信でリセットがかかる可能性があるので対策します 1998/03/31 by T.Soneoka */
//		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
//			if (!ReleaseCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {	/**	通信コーデックを解放（できない時）	*/
//				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
//			}
//		}
#else
		CMN_DisableInterrupt();
		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
			GetCodecFlag = NO;
			CMN_EnableInterrupt();
  #if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 2001/12/17 T.Takagi */
			/*---------------------------------------------------------------------
			** HINOKIでは通信コーデック(MN86064)を使用してスキャナ送信します
			** 1998/10/13 H.Hirao
			*/
			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_SCANNER_TX)) {	/**	通信コーデックを解放（できない時）	*/
				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
			}
  #else

			if (!ReleaseCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {	/**	通信コーデックを解放（できない時）	*/
				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
			}
  #endif
		}
		CMN_EnableInterrupt();
#endif
		/*--------------------------------------------------*/
		/*	送信エンコードＤＭＡ監視タスク終了処理	*/
		/*--------------------------------------------------*/
		if (tskno_EncodeDMA_End != 0xffff) {
			del_tsk(&tskno_EncodeDMA_End);	/**	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		}

  #if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* ported by T.Takagi 2001/12/17 T.Takagi */
		/*---------------------------------------------------------------------
		** HINOKIでは通信コーデック(MN86064)を使用してスキャナ送信します
		** 1998/10/13 H.Hirao
		*/
		DMA_RequestMask(DMA_CH_ENC);
  #else
		DMA_RequestMask(DMA_SCNCDC_DRAM_CH);
  #endif
  #if (PRO_SCN_CODEC_TYPE == IDP301) /* 2002/09/18 By M.Maeda */
		/*-------------------------------------------------------------
		** SAKAKIのようなIDP301/DICEPを使用した読取り方式の場合には
		** 読み取りタスクを起動していますので、ここで削除します
		** 1998/08/12 H.Yoshikawa
		*/
		if (tskno_SCN_ScanningTask != 0xffff) {
			del_tsk(&tskno_SCN_ScanningTask);
		}
  #endif

		break;
	case TX_G3_MEM:	/**	メモリＧ３送信の時	*/
		if (timerID_DummyPixTimer != 0xff) {
			CMN_MultiTimer10msStop(&timerID_DummyPixTimer);	/**	ダミーデータ監視終了	*/
		}
		if (tskno_CDC_MTxCodeConvertTask != 0xffff) {
			del_tsk(&tskno_CDC_MTxCodeConvertTask);	/**	メモリ送信１ページ符号変換タスク終了	*/
		}
#if (0)	/* 下記処理ではメモリ送信でリセットがかかる可能性があるので対策します 1998/03/31 by T.Soneoka */
//		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
//			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {	/**	通信コーデックを解放（できない時）	*/
//				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
//			}
//		}
#else
		CMN_DisableInterrupt();
		if (GetCodecFlag == YES) {
			GetCodecFlag = NO;
			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {	/**	通信コーデックを解放（できない時）	*/
				CMN_EnableInterrupt();
				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
			}
		}
		CMN_EnableInterrupt();
#endif
		/*	メモリ送信メモリリードタスク終了	*/
		if (tskno_MTxReadDMA_Task != 0xffff) {
			del_tsk(&tskno_MTxReadDMA_Task);	/**	メモリ送信メモリリードタスク終了	*/
		}
		DMA_RequestMask(DMA_CH_DEC); /* 1st argmument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/23 */

		/*	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		if (tskno_EncodeDMA_End != 0xffff) {
			del_tsk(&tskno_EncodeDMA_End);	/**	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		}
		DMA_RequestMask(DMA_CH_ENC); /* 1st argmument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/23 */
		break;

	case TX_ECM_MEM:	/**	メモリＥＣＭ送信の時	*/
		/*	メモリ送信１ページ符号変換タスク終了	*/
		if (tskno_CDC_MTxCodeConvertTask != 0xffff) {
			del_tsk(&tskno_CDC_MTxCodeConvertTask);	/**	メモリ送信１ページ符号変換タスク終了	*/
		}
#if (0)	/* 下記処理ではメモリ送信でリセットがかかる可能性があるので対策します 1998/03/31 by T.Soneoka */
//		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
//			/* Modified by H.Kubo 1997/07/01 */
//			/* if (!ReleaseCodec(CODEC_MEMORY_TX)) [*/	/**	通信コーデックを解放（できない時）	*/
//			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {	/**	通信コーデックを解放（できない時）	*/
//				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
//			}
//		}
#else
		CMN_DisableInterrupt();
		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
			GetCodecFlag = NO;
			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {	/**	通信コーデックを解放（できない時）	*/
				CMN_EnableInterrupt();
				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
			}
		}
		CMN_EnableInterrupt();
#endif
		/*	メモリ送信メモリリードタスク終了	*/
		if (tskno_MTxReadDMA_Task != 0xffff) {
			del_tsk(&tskno_MTxReadDMA_Task);	/**	メモリ送信メモリリードタスク終了	*/
		}
		DMA_RequestMask(DMA_CH_DEC); /* 1st argmument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/23 */

		/*	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		if (tskno_EncodeDMA_End != 0xffff) {
			del_tsk(&tskno_EncodeDMA_End);	/**	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		}
		DMA_RequestMask(DMA_CH_ENC); /* 1st argmument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/23 */
		break;
	case TX_ECM_BKUPRAM: /* Ported from ORANGE\SRC\MDMTXPIX.C by H.Kubo 1997/07/16 */
		if (tskno_MDM_BackupRamToEcmBufTask != 0xffff) {
			del_tsk(&tskno_MDM_BackupRamToEcmBufTask);	/** キャラクタ送信１ページ符号化タスク終了	*/
		}
		break;
	case TX_G3_RELAYED_TX_REPORT:	/**	メモリＧ３送信の時	*/
		if (timerID_DummyPixTimer != 0xff) {
			CMN_MultiTimer10msStop(&timerID_DummyPixTimer);	/**	ダミーデータ監視終了	*/
		}
		if (tskno_CDC_CTxCodeConvertTask != 0xffff) {
			del_tsk(&tskno_CDC_CTxCodeConvertTask);	/**	メモリ送信１ページ符号変換タスク終了	*/
		}
#if (0)	/* 下記処理ではメモリ送信でリセットがかかる可能性があるので対策します 1998/03/31 by T.Soneoka */
//		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
//			/* Modified by H.Kubo 1997/07/01 */
//			/* if (!ReleaseCodec(CODEC_MEMORY_TX)) [*/	/**	通信コーデックを解放（できない時）	*/
//			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {	/**	通信コーデックを解放（できない時）	*/
//				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
//			}
//		}
#else
		CMN_DisableInterrupt();
		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
			GetCodecFlag = NO;
			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {	/**	通信コーデックを解放（できない時）	*/
				CMN_EnableInterrupt();
				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
			}
		}
		CMN_EnableInterrupt();
#endif
		DMA_RequestMask(DMA_CH_DEC); /* 1st argmument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/23 */

		/*	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		if (tskno_EncodeDMA_End != 0xffff) {
			del_tsk(&tskno_EncodeDMA_End);	/**	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		}
		DMA_RequestMask(DMA_CH_ENC); /* 1st argmument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/23 */
		break;

	case TX_ECM_RELAYED_TX_REPORT:	/**	メモリＥＣＭ送信の時	*/
		/*	メモリ送信１ページ符号変換タスク終了	*/
		if (tskno_CDC_CTxCodeConvertTask != 0xffff) {
			del_tsk(&tskno_CDC_CTxCodeConvertTask);	/**	メモリ送信１ページ符号変換タスク終了	*/
		}
#if (0)	/* 下記処理ではメモリ送信でリセットがかかる可能性があるので対策します 1998/03/31 by T.Soneoka */
//		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
//			/* Modified by H.Kubo 1997/07/01 */
//			/* if (!ReleaseCodec(CODEC_MEMORY_TX)) [*/	/**	通信コーデックを解放（できない時）	*/
//			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {	/**	通信コーデックを解放（できない時）	*/
//				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
//			}
//		}
#else
		CMN_DisableInterrupt();
		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
			GetCodecFlag = NO;
			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {	/**	通信コーデックを解放（できない時）	*/
				CMN_EnableInterrupt();
				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
			}
		}
		CMN_EnableInterrupt();
#endif
		DMA_RequestMask(DMA_CH_DEC); /* 1st argmument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/23 */

		/*	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		if (tskno_EncodeDMA_End != 0xffff) {
			del_tsk(&tskno_EncodeDMA_End);	/**	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		}
		DMA_RequestMask(DMA_CH_ENC); /* 1st argmument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/23 */
		break;
	case TX_G3_CVR:	/**	Ｇ３カバーページ送信の時	*/
	case TX_G3_RCR:	/**	Ｇ３受領証送信の時	*/
	case TX_ECM_CVR:	/**	ＥＣＭカバーページ送信の時	*/
	case TX_ECM_RCR:	/**	ＥＣＭ受領証送信の時	*/
	default:
		/*	キャラクタ送信１ページ符号化タスク終了	*/
		if (tskno_CDC_CTxCodeConvertTask != 0xffff) {
			del_tsk(&tskno_CDC_CTxCodeConvertTask);	/**	キャラクタ送信１ページ符号化タスク終了	*/
		}
		break;
	}

#if defined(POPLAR_F)
	BackUpCodecPageStatus = CodecPageStatus;	/* for debug */
#endif

	CodecPageStatus = CDC_READY;	/**	コーデックステータスクリア	*/
}



/*************************************************************************
	module		:[送信異常チェック]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/24]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE  CheckTxSystemError(void)
{
	UBYTE	rtn;

	rtn = 0;

	switch (CommunicateType) {	/**	交信タイプ	*/
	case	TX_ECM_SCAN:	/**	スキャナＥＣＭ送信の時	*/
	case	TX_G3_SCAN:	/**	スキャナＧ３送信の時	*/
		if (SYS_GetScannerLampError()) {	/**	ランプエラーの時	*/
			rtn = TX_LAMP_ERR;	/**	戻り値ランプエラーセット	*/
		}

		/* Ported from ORANGE by H.Kubo 1997/07/16 */
#if (PRO_FBS == ENABLE)
		if (SYS_ScannerExecMode == SCN_ADF) {
		/* FBSスキャナー送信の時はスキャナーカバーオープンは見ない T.Nose 1997/06/11 */
			if ((SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)
			 || (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN) /* added by H.Kubo 1999/09/14 */
			 || (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)) {	/**	スキャナカバーまたはプリンタカバーオープンの時	*/
				rtn = TX_DOC_ERR;	/**	戻り値繰り込み不良セット	*/
			}
		}
		else {
			if (
#if defined (HIIRAGI)
			(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) || /* added by H.Kubo 1999/09/14 */
#endif
			SYS_GetCoverScannerOpen()) {	/**	スキャナカバーオープンの時	*/
				rtn = TX_DOC_ERR;	/**	戻り値繰り込み不良セット	*/
			}
		}
#else  /* !(PRO_FBS == ENABLE) */
		if (SYS_GetCoverScannerOpen()) {	/**	スキャナカバーオープンの時	*/
			rtn = TX_DOC_ERR;	/**	戻り値繰り込み不良セット	*/
		}
#endif  /* (PRO_FBS == ENABLE) */
		switch (CodecPageStatus) {	/**	コーデックステータス	*/
		/* F351で長尺原稿で１ｍエラーの判断が抜けている為、ループする By O.Kimoto 2003/01/29 */
#if defined(HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* SAKAKI2で二次障害が出たため、とりあえずHINOKI2だけにします。T.Takagi */
		case	CDC_DOC_OVER:	/**	原稿長オーバ	*/
			rtn = TX_1M_OVER;	/**	戻り値１ｍ原稿長オーバセット	*/
			break;
#endif
		case	CDC_DOC_ERROR:	/**	フィードエラー	*/
			rtn = TX_DOC_ERR;	/**	戻り値原稿繰り込み不良エラーセット	*/
			break;
		case	CDC_DECODE_ERROR:	/**	デコードエラー時	*/
			rtn = TX_MEM_ERR;	/**	戻り値メモリエラーセット	*/
			break;
		default:
			break;
		}
		break;
	case	TX_ECM_MEM:	/**	メモリＥＣＭ送信の時	*/
	case	TX_G3_MEM:	/**	メモリＧ３送信の時	*/
	case	TX_G3_RELAYED_TX_REPORT:
	case	TX_ECM_RELAYED_TX_REPORT:
	default:
		switch (CodecPageStatus) {	/**	コーデックステータス	*/
		case	CDC_DECODE_ERROR:	/**	デコードエラー時	*/
			rtn = TX_MEM_ERR;	/**	戻り値メモリエラーセット	*/
			break;
		default:
			break;
		}
		break;
	}

	if (rtn == 0) {
		if (MDM_MemReadStatus) {
			rtn = TX_MEM_ERR;
			FaxCompatibleErrorCode = 77;	/* test */
		}
	}

	return (rtn);
}

/*************************************************************************
	module		:[高速ＲＤＳ データリードデータ送出データ長セット]
	function	:[バックアップＲＡＭデータ長を送出データ長にセットする
	]
	return		:[なし]
	common		:[EncodeDataCount, CodecPageStatus, TxStartFlag]
	condition	:[
	]
	comment		:[
		64KB以上のバックアップRAMデータ送信に対応 1999/04/29 by K.Okada
		(ただし、1個のバックアップRAMデータで64KB以上を扱うことはできない）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1999/04/29]
	author		:[K.Okada]
*************************************************************************/
void MDM_BackupRamToEcmBufTask(void)
{
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/22 by T.Soneoka */
	/* ＰＩＸ送信前のフラグが短いので受信できないモデムがある */
	wai_tsk(10);
#endif

	EncodeDataCount = BackUpDataLength;
	CodecPageStatus = CDC_RTC_DET;
	TxStartFlag = 1;
	det_evt(EVT_TX_START);
	wai_tsk(0xffff);
}

/*************************************************************************
	module		:[高速ＲＤＳ データリードデータ送出データ長セット終了処理]
	function	:[
	]
	return		:[なし]
	common		:[]
	condition	:[
	]
	comment		:[
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CDC]
	date		:[1996/6/17]
	author		:[曽根岡拓]
*************************************************************************/
void MDM_BackupRamToEcmBufTaskExit(void)
{
	exi_tsk();
}

/*************************************************************************
	module		:[バックアップRAM送出データ長セット]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		64KB以上のバックアップRAMデータ送信に対応 1999/04/29 by K.Okada
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1999/04/29]
	author		:[K.Okada]
*************************************************************************/
void SetBackUpDataLength(void)
{
	UWORD i;

	BackUpDataLength = 0; /* FTTを受信すると、レングス値がおかしくなるため 2000/08/11 by K.Okada */

	for (i = 0; i < HIGH_RDS_DATA_MAX; i++) {
		BackUpDataLength += HighRDS_Table[i].BackupDataLength;
	}
}


/************************************************************************
	module		:[スキャナオープンのパラメータセット]
	function	:[
		1.	ランプを点灯する
		2.	スキャナの読み取りパラメータをセットする
		.	1)	読み取り原稿サイズ
		.	2)	読み取り縮小率
		.	3)	読み取りモード
	]
	return		:[]
	common		:[
		TxPageFinishStatus		:画データ送信終了結果
		FaxComResult			:通信結果
		FaxComPerformingFlag	:通信中フラグ
		SYS_DocBlock			:送信原稿制御ブロック
		SCN_Control				:スキャナオープンのパラメータ(構造体)
	]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1994/2/24(1994/06/15)]
	author		:[曽根岡拓(竹内茂樹)]
************************************************************************/
void	SetScannerTxParam( void )
{
#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* ported by T.Takagi 2001/12/17 */
	/*---------------------------------------------------------------------
	** HINOKIでは通信コーデック(MN86064)を使用してスキャナ送信します
	** 1998/10/31 H.Hirao
	*/
	SYS_DocumentWidthFullFlag = 1;
	SYS_DocumentLengthLimitFlag = CHK_DocumentLengthLimit();
	
#elif (PRO_SCN_CODEC_TYPE == IDP301) /* 2002/09/18 By M.Maeda */
	/*---------------------------------------------------------------------
	** SAKAKIではIDP/DICEPを使用してスキャナ送信します
	** 定型縮小はIDPで行います
	** 1998/08/21 H.Yoshikawa
	*/
	/*	ICHOUのADF繰り込み制御変更のため、
	**	1ページ目の時はMAN_Task()でセットしたSCN_DOC_ADF_1ST_PAGEのままで、
	**	2ページ目以降の時はここでSCN_DOC_READYにする
	*/
	if (SCN_DocumentStatus != SCN_DOC_ADF_1ST_PAGE) {
		SCN_DocumentStatus = SCN_DOC_READY;
	}

	SCN_Control.UseType = IDP_SCANNER_TX; /**	スキャナ送信を指定	Aug.18,1994 */
	SCN_Control.DocumentDensity = SYB_DensitySw;
	SCN_Control.DocumentSize	= SYS_DocBlock.Src.Size; /** TBD */

	/*--------------------------------------*/
	/* 縮小率セット							*/
	/*--------------------------------------*/
	switch (SYS_DocBlock.Src.Size) {	/**	自機の原稿サイズ */
	case	SYS_DOCUMENT_A3_SIZE:		/**	Ａ３	*/
		/**	スキャナの縮小率セット	*/
		if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_A3_SIZE) {
			SCN_Control.ScanReduction = 1000;				/* Ａ３→１００％ */
		}
		else if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_B4_SIZE) {
			SCN_Control.ScanReduction = SYS_A3_TO_B4;		/* Ａ３→Ｂ４ */
		}
		else {
			SCN_Control.ScanReduction = SYS_A3_TO_A4;		/* Ａ３→Ａ４ */
		}
		break;
	case	SYS_DOCUMENT_B4_SIZE:		/**	Ｂ４	*/
		/**	スキャナの縮小率セット */
		if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_A4_SIZE) {
			SCN_Control.ScanReduction = SYS_B4_TO_A4;		/* Ｂ４→Ａ４ */
		}
		else{
			SCN_Control.ScanReduction = 1000;				/* Ｂ４→１００％ */
		}
		break;
	default:
		/**	スキャナの縮小率 */
		SCN_Control.ScanReduction = 1000;					/* Ａ４→１００％ */
		break;
	}
	/*------------------------------*/
	/**	読み取り原稿モードセット	*/
	/*------------------------------*/
	switch (SYS_DocBlock.Src.Mode) {	/**	自機の原稿モード */
	case	SYS_GRAY16:					/**	各種ハーフトーン */
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
		if (SYS_DocBlock.Dst.Mode == SYS_NORMAL) {		/**	相手機がノーマル */
			/**	読み取りモードに相手機の受信モードをセット */
			SCN_Control.DocumentMode = SYS_NORMAL;
		}
		else {
			/**	読み取りモードに自機の原稿モードをセット */
			SCN_Control.DocumentMode = SYS_DocBlock.Src.Mode;
		}
		break;
	default:
		/**	読み取りモードに相手機の原稿モードをセット */
		SCN_Control.DocumentMode = SYS_DocBlock.Dst.Mode;	/* Src→Dst  竹内 Dec.08.1994 */
		break;
	}

	/*---------------------------------------------------------------------
	** SAKAKIでもFull固定とします。
	** このFlagの値でB4→A4の縮小率が変わります。
	** 一部読み取り（値が０）の時、80.5%
	** 全部読み取り（値が１）の時、81.9%
	** 現在、メモリ送信は全部読み時の縮小率(81.9%)を使用し、
	** スキャナ送信（初期値一部読み）では、80.5%となっており、
	** 送信方式が異なると縮小率が異なることになります。
	** メモリ送信は、中継配信等の機能があるために、全部読みの縮小率を使用する必要がある。
	** というわけで、スキャナ送信も全部読みの縮小率固定とします。
	** 1998/11/23 H.Yoshikawa
	** この処理をすると、読み取り幅も全部読み取り固定となってしまうので、この処理は中止し、
	** MOMIJIと同じ仕様とします。
	*/
/* #if (0)	1998/11/28 *//* 1998/11/23 H.Yoshikawa */
	if (CHK_DocumentWidthFull()) {	/* 1998/09/01 H.Yoshikawa */
		SYS_DocumentWidthFullFlag = 1;
	}
	else {
		SYS_DocumentWidthFullFlag = 0;
	}
/* #endif 1998/11/28 */
/*	SYS_DocumentWidthFullFlag = 1;	1998/11/28 */

	SYS_DocumentLengthLimitFlag = CHK_DocumentLengthLimit();
	SCN_ModeSw = SYS_DocBlock.Src.Mode;			/** 読み取りモードをスキャナー用グローバルにページ毎に待避 */
	SCN_StoreData.Mode = SYS_DocBlock.Src.Mode;	/* メインができしだい" SYS_ModeSw; "に変更します TBD *//* SAKAKI では未使用？ */
	SCN_StoreData.Size = SYS_DocBlock.Src.Size;	/* SAKAKI では未使用？ */
	SYS_DocumentScanSize        = SCN_Control.DocumentSize;	/* 表示の為(らしい)追加	Jul.29.1994 *//* MOMIJIから移植 */

	/*---------------------------------------------------------------------
	** スキャナ送信時に原稿読み取り開始位置が前回の送信時の設定で動作してしまう件
	** スキャナ送信時にＴＴＩインサイド/アウトサイドの初期化を行う。
	** 1998/11/28 H.Yoshikawa
	*/
	CDC_GetTTI_SkipLine();

#else
#if (PRO_DOC_IN == ENABLE)
	SCN_DocumentStatus = SCN_DOC_READY;
#else
	/*	ICHOUのADF繰り込み制御変更のため、
	**	1ページ目の時はMAN_Task()でセットしたSCN_DOC_ADF_1ST_PAGEのままで、
	**	2ページ目以降の時はここでSCN_DOC_READYにする
	*/
	if (SCN_DocumentStatus != SCN_DOC_ADF_1ST_PAGE) {
		SCN_DocumentStatus = SCN_DOC_READY;
	}
#endif

	SCN_Control.UseType = IDP_SCANNER_TX; /**	スキャナ送信を指定	Aug.18,1994 */
	SCN_Control.DocumentDensity = SYB_DensitySw;
	SCN_Control.DocumentMode	= SYS_DocBlock.Src.Mode;
	SCN_Control.DocumentSize	= SYS_DocBlock.Src.Size; /** TBD */
	SCN_Control.ScanReduction	= 100 * 10;			   /** 原稿蓄積では、縮小率１００％をセットします */
	SYS_DocumentWidthFullFlag = 1;					/** TBD CHK_DocumentWidthFull(); */
	SYS_DocumentLengthLimitFlag = CHK_DocumentLengthLimit();
	SCN_ModeSw = SYS_DocBlock.Src.Mode;			/** 読み取りモードをスキャナー用グローバルにページ毎に待避 */
	SCN_StoreData.Mode = SYS_DocBlock.Src.Mode;	/* メインができしだい" SYS_ModeSw; "に変更します TBD */
	SCN_StoreData.Size = SYS_DocBlock.Src.Size;
#endif
}

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* ECM_BUFFER_OVER */
UBYTE	G3_TxSub(void)
{
	/* ローカル変数宣言 */
	MESSAGE_t	*MDM_Msg;
	UBYTE		*ebf_base_rp;	/*	ＥＣＭバッファ先頭読み出しポインタ	*/
	UWORD	mse_line_cnt;	/*	ＭＳＥ処理用、ラインカウンタ	*/
	UWORD	mse_byte_cnt;	/*	ＭＳＥ処理用、３２ラインのバイト数	*/
	UBYTE	rtn;	/*	リターンコード	*/
	UBYTE	page_loop;	/*	１ページ完了フラグ　ループ制御用	*/
	UWORD	detect_eol_p;	/*	ＥＯＬ検出位置	*/
	UWORD	i;
	UWORD	w_cnt;	/*	送出データ数ワーク	*/
	UWORD	fill_cnt;	/*	フィル挿入データ数	*/
	UWORD	min_mse_cnt;	/*	ＭＳＥ総データ数	*/
	UBYTE	*ebf_tmp_rp;	/*	ＥＣＭバッファＥＯＬチェック用テンポラリ読み出しポインタ	*/
	UBYTE	cdc_stat;
	UWORD	g3_debug_count;
	UBYTE	dummy;
	UWORD	loop_timer;

	/*	変数初期化処理	*/
	mse_line_cnt = 0;	/**	ＭＳＥライン数初期化	*/
	mse_byte_cnt = 0;	/**	ＭＳＥ処理用符号量初期化	*/
	ebf_base_rp = (UBYTE *)&EcmBuffer[0][0];	/**	ＥＣＭバッファ読み出し先頭アドレス設定	*/
	ebr_cnt = 0;	/**	ＥＣＭバッファ読み出しバイト数	*/
	rtn = 0;	/**	リターンコード初期化	*/
	page_loop = 1;	/**	１ページ完了フラグ初期化	*/

	MDM_EcmBufferOverEncodeStop = 0;

	/*	ダミーデータ送出監視	*/
	do {
		rcv_msg(mbxno.MDM_PixDummy, &MDM_Msg);	/**	ダミーデータ送出終了メッセージ受信	*/
	} while ( MDM_Msg->Message != MSG_DUMMY_PIX_TIME_OVER );
	if (timerID_DummyPixTimer != 0xff) {
		CMN_MultiTimer10msStop(&timerID_DummyPixTimer);	/**	ダミーデータ監視タイマタスク終了	*/
	}

	/*	符号変換完了待ち
	**	（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）
	*/
	rtn = MDM_WaitForTxStartOrTxError();
	switch (rtn) {
	case TX_LAMP_ERR:
	case TX_DOC_ERR:
	case TX_1M_OVER:
	case TX_MEM_ERR:
		MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
		return rtn;
		break;
	default:
		break;
	}


	/*	送出未処理のエンコードデータ数取得	*/
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	RemainEncodeData = EncodeDataCount;	/**	送出未処理のエンコードデータ数取得	*/
	cdc_stat = CodecPageStatus;
	TxStartFlag = 0;	/**	画データ送出フラグをクリア	*/
	CMN_EnableInterrupt();	/**	割り込み許可	*/

	/*	画データ送出ループ　*/
	while (page_loop) {	/**	エンコードデータがなくなり、ＲＴＣ（その他）を検出するまでループ	*/
		/*	送出データ数（モデムバッファ書き込み数）設定	*/
#if (PRO_CLASS1 == ENABLE) /* Added by H.Kubo 1998/03/04 */
		next_mbf_set_cnt = GetCount(RemainEncodeData, MDM_ModemDmaSize);	/**	１ブロック送出バイト数取得（２５６ｂｙｔｅ以下）	*//** 256 Bytes **/
#else
		next_mbf_set_cnt = GetCount(RemainEncodeData, MODEM_DMA_SIZE);	/**	１ブロック送出バイト数取得（２５６ｂｙｔｅ以下）	*//** 256 Bytes **/
#endif
		/*	トータルライン数、ＭＳＥライン数、（次送出バイト数再設定）処理
		**	符号化データのＥＯＬはバイト単位でないとできません
		*/
		if ((SYS_DocBlock.Dst.Code != SYS_MMR_CODE) &&
		    (SYS_DocBlock.Dst.Code != SYS_MG3_CODE) &&
		    (SYS_DocBlock.Dst.Code != SYS_JBIG_CODE) &&
		    (SYS_DocBlock.MSE_Method == MSE1) &&
		    (SYS_DocBlock.MinimumLineSize != 0)) {	/**	符号化方式がＭＨとＭＲでＭＳＥで最小伝送時間が０ｍｓでない時	*/
		    ebf_tmp_rp = ebf_base_rp + ebr_cnt;	/**	現在のＥＣＭバッファ読み出し位置設定 */
			detect_eol_p = 0;	/**	ＥＯＬ検出位置クリア	*/
			for (i = 0; i < next_mbf_set_cnt;) {	/**	１ブロック（２５６ｂｙｔｅ以下）分、ＥＯＬチェック	*/
				if (*ebf_tmp_rp == EOL_FRAME1) {	/**	ＥＯＬ、１バイト目検出時	*/
					i++;	/**	チェックカウントインクリメント	*/
					ebf_tmp_rp++;	/**	ＥＯＬ検出位置インクリメント	*/
					if (((*ebf_tmp_rp)&EOL_FRAME2_MASK) == EOL_FRAME2) {	/**	ＥＯＬ、２バイト目検出時	*/
						detect_eol_p = i-1;	/**	ＥＯＬ検出位置設定	*/
						mse_line_cnt++;	/**	ＭＳＥライン数更新	*/
						if (mse_line_cnt == (MSE_LINE+1)) {	/**	ＭＳＥ処理有りの時 ＆＆　ＭＳＥラインの時	*/
							break;
						}
						i++;	/**	チェックカウントインクリメント	*/
						ebf_tmp_rp++;	/**	ＥＯＬ検出位置インクリメント	*/
					}
				}
				else {	/**	ＥＯＬでないとき	*/
					i++;	/**	チェックカウントインクリメント	*/
					ebf_tmp_rp++;	/**	ＥＯＬ検出位置インクリメント	*/
				}
			}
			if (detect_eol_p != 0) {
				if (mse_line_cnt == (MSE_LINE+1)) {
					next_mbf_set_cnt = detect_eol_p;	/**	送出データ数（モデムバッファ書き込み数）設定	*/
				}
				else {
					next_mbf_set_cnt = detect_eol_p;	/**	送出データ数（モデムバッファ書き込み数）設定	*/
					mse_line_cnt--;	/**	ＭＳＥライン数デクリメント	*/
				}
			}
			else {
				mse_line_cnt--;	/**	ＭＳＥライン数デクリメント	*/
			}
			mse_byte_cnt += next_mbf_set_cnt;	/**	ＭＳＥ用バイト数設定	*/
		}

		/*	画データ終了判定処理	*/
		if ( RemainEncodeData == next_mbf_set_cnt ) {	/**	送出エンコードデータがない時	*/
			switch (cdc_stat) {	/**	コーデック状態	*/
			case CDC_RTC_DET:	/**	ＲＴＣ検出時	*/
			case CDC_DECODE_ERROR:	/**	デコードエラー時	*/
			case CDC_STOPPED:	/**	ストップＳｗ時	*/
			case CDC_DOC_OVER:	/**	1mオーバーの時	*/
				ModemBlock.Chain = SET_COMPL; /* 送信データセット完了		*/
				break;
			default:	/**	その他	*/
				break;
			}
		}

		/*	フレーム書き込みモデムバッファ獲得処理	*/
		loop_timer = 0;
		while (ModemControl.UsedCount == MODEM_BUFFER_MAX) {	/**	モデムバッファ使用本数が８本の時	*/
			wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/
			loop_timer++;
			if (loop_timer > 18000) {
				SaveReturnAddressAndJumpBegin();	/**リセットする*/
			}
		}

		/*	ＥＣＭバッファからモデムバッファにプログラム転送	*/
		/* メモリ－メモリの DMA 転送にしてみます。by H.Kubo 1998/02/05 */
		MemoryMove((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0],
		           (UBYTE *)(ebf_base_rp+ebr_cnt), next_mbf_set_cnt);	/**	ＥＣＭバッファからモデムバッファにプログラム転送	*/
		/*	Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／バイト数登録）	*/
		if (ModemBlock.Chain == SET_COMPL) {	/**	最終ブロック送出時	*/
			TxG3_Write((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0], next_mbf_set_cnt + 7); /* Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／バイト数登録）	*/
		}
		else {	/**	その他の時	*/
			TxG3_Write((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0], next_mbf_set_cnt); /* Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／バイト数登録）	*/
		}

		/*	ＥＣＭバッファ読み出し数更新	*/
		ebr_cnt += (UDWORD)next_mbf_set_cnt;	/**	ＥＣＭバッファ読み出しバイト数更新	*/

		/*	タスクウェイト	*/
		wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/

		/*	送出未処理エンコードデータ数更新処理	*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		RemainEncodeData = EncodeDataCount - ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/
		cdc_stat = CodecPageStatus;
		TxStartFlag = 0;	/**	画データ送出フラグをクリア	*/
		CMN_EnableInterrupt();	/**	割り込み許可	*/

		/*	強制終了処理(ストップ処理）		*/
		if (MDM_TxStopSwFlag == 0) {	/**	画データ用ストップＳｗがＯＦＦの時	*/
			if (SYS_FaxComStopSwitch()) {	/**	ストップＳｗＯＮの時	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				if (MDM_TxForceStop()) {	/**	強制終了時 PRO_QUICK_TX */
					rtn = TX_STOPPED;	/**	戻り値ストップＳｗＯＮ設定	*/

					if ((CommunicateType == TX_ECM_SCAN) ||
					    (CommunicateType == TX_G3_SCAN)) {	/**	交信タイプがスキャナ送信の時	*/
						if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {	/**	スキャナモータがストップしていない時	*/
							SCN_StopMotor();	/**	スキャナモータストップ	*/
							SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
							LampOff();	/**	ランプＯＦＦ	*/
						}
					}
				}
				MDM_TxStopSwFlag = 1;	/**	画データ用ストップＳｗをＯＮに設定	*/
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_FAXCOM;	/**	マシンステータスの通信ストップ解除	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
			else {
				rtn = CheckTxSystemError();	/**	送信異常チェック	*/
			}
			if (rtn) {	/**	送信異常有りの時	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				return (rtn);
			}
		}

		/*	ＭＳＥ処理	*/
		if ((SYS_DocBlock.Dst.Code != SYS_MMR_CODE) &&
		    (SYS_DocBlock.Dst.Code != SYS_MG3_CODE) &&
		    (SYS_DocBlock.Dst.Code != SYS_JBIG_CODE) && /* added by H.Kubo 1998/06/22 */
		    (SYS_DocBlock.MSE_Method == MSE1) &&
		    (SYS_DocBlock.MinimumLineSize != 0) &&
		    (mse_line_cnt == (MSE_LINE + 1 ) )) { /** ＭＳＥ処理有りの時＆＆ＭＭＲ・ＭＧ３以外＆＆ＭＳＥライン＆＆最小伝送時間が０以外の時	*/
			min_mse_cnt = (UWORD)(SYS_DocBlock.MinimumLineSize * 32); /** ＭＳＥ（３２ラインの最小伝送符号量）総データ数計算	*/
			if (min_mse_cnt > mse_byte_cnt) {	/**	フィル挿入する時	*/
				fill_cnt = (min_mse_cnt-mse_byte_cnt);	/**	ＭＳＥ　フィル挿入データ数取得	*/
				do {	/**	フィル送出データがなくなるまでループ	*/
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
					w_cnt = GetCount(fill_cnt, MDM_ModemDmaSize);	/**	フィル送出バイト数設定（２５６ｂｙｔｅ） */ /** 256 Bytes **/
#else
					w_cnt = GetCount(fill_cnt, MODEM_DMA_SIZE);	/**	フィル送出バイト数設定（２５６ｂｙｔｅ） */ /** 256 Bytes **/
#endif
					loop_timer = 0;
					while (ModemControl.UsedCount == MODEM_BUFFER_MAX) {	/**	モデムバッファ使用本数が８本の時	*/
						wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/
						loop_timer++;
						if (loop_timer > 18000) {
							SaveReturnAddressAndJumpBegin();	/**リセットする*/
						}
					}
					TxG3_Write(&ModemZeroBuffer[0], w_cnt);	/**	送出処理	*/
					fill_cnt -= w_cnt;	/**	フィル送出バイト数更新	*/
				} while (fill_cnt > 0);
			}
			mse_byte_cnt = 0;	/**	ＭＳＥ符号量（バイト数）クリア	*/
			mse_line_cnt = 0;	/**	ＭＳＥライン数クリア	*/
		}

		/*	送出終了判定／子タスク終了処理	*/
		if (RemainEncodeData == (UDWORD)0) {	/**	エンコードデータがない時	*/
			switch (cdc_stat) {	/**	エンコードステータス	*/
			case CDC_CONTINUE:	/**	エンコード中の時	*/
				MDM_DebugDataWaitCnt++;
				g3_debug_count = 0;

				/*	エンコードデータ（２５６ｂｙｔｅ）が揃うよりもモデムバッファにセットする方が速い時
				**	符号変換完了待ち（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）
				*/
				rtn = MDM_WaitForTxStartOrTxError();
				switch (rtn) {
				case TX_LAMP_ERR:
				case TX_DOC_ERR:
				case TX_1M_OVER:
				case TX_MEM_ERR:
					MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
					return rtn;
					break;
				default:
					break;
				}

				/*	送出未処理のエンコードデータ数取得	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				RemainEncodeData = EncodeDataCount - ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/
				cdc_stat = CodecPageStatus;
				TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				break;
			case CDC_BLOCK_END:	/**	ブロックエンドの時	*/
				/*	エンコード開始メッセージ送信	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				MDM_EcmBufferOverEncodeStop = 0;
				det_evt(EVT_DMA_SCNCDC_DRAM);
				CMN_EnableInterrupt();	/**	割り込み許可	*/

				if( CommunicateType == TX_G3_SCAN ) {
					ModemMessage.Message = MSG_ENCODE_DMA_START;
					snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);	/*	エンコード開始メッセージ送信	*/
				}
				else{
					ModemMessage.Message = MSG_ENCODE_DMA_START;
					snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);	/*	エンコード開始メッセージ送信	*/
				}
				/*	符号化完了待ち（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）	*/
					rtn = MDM_WaitForTxStartOrTxError();
					switch (rtn) {
					case TX_LAMP_ERR:
					case TX_DOC_ERR:
					case TX_1M_OVER:
					case TX_MEM_ERR:
						MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
						return rtn;
						break;
					default:
						break;
					}

				/**	送出未処理のエンコードデータ数取得	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
				cdc_stat = CodecPageStatus;
				if (cdc_stat == CDC_RTC_DET) {
					if (EncodeDataCount >= 0x10000) {
						EncodeDataCount -= 0x10000;
						MDM_EcmRemainCount = EncodeDataCount;
						RemainEncodeData = EncodeDataCount;	/**	送出未処理エンコードデータ数更新	*/

						/* 2000/02/08 Y.Murata */
						CMN_EnableInterrupt();	/**	割り込み許可	*/
						if (MDM_EcmRemainCount) {
							MemoryMove((UBYTE *)&EcmBuffer[0][0], (UBYTE *)&EcmBuffer2[0][0], MDM_EcmRemainCount);
							MDM_EcmRemainCount = 0;
						}
					}
					else {
						RemainEncodeData = EncodeDataCount;	/**	送出未処理エンコードデータ数更新	*/
					}
				}
				else {
					RemainEncodeData = EncodeDataCount;	/**	送出未処理エンコードデータ数更新	*/
				}
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				/*----------------------------------*/
				/*	ＥＣＭバッファ読み出し数初期化	*/
				/*----------------------------------*/
				ebr_cnt = 0;	/**	ＥＣＭバッファ読み出し数初期化	*/

#if 0	/* 2000/02/07 Y.Murata */
** 				if (MDM_EcmRemainCount) {
** 					MemoryMove((UBYTE *)&EcmBuffer[0][0], (UBYTE *)&EcmBuffer2[0][0], MDM_EcmRemainCount);
** 					MDM_EcmRemainCount = 0;
** 				}
#endif
				if (g3_debug_count >= 1500) {
					outp((unsigned long)0,(unsigned char)0);/* WriteProtectError for ICE */
				}

				break;
			case CDC_RTC_DET:	/**	ＲＴＣ検出の時	*/
				page_loop = 0;	/**	１ページループフラグセット	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				rtn = TX_PAGE_END;	/**	戻り値１ページ送信完了設定	*/
				break;
			case CDC_STOPPED:	/**	正常終了（ストップＳｗＯｎ）の時	*/
				page_loop = 0;	/**	１ページループフラグセット	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				rtn = TX_STOPPED;	/**	戻り値ストップＳＷ設定	*/
				break;
			case CDC_DOC_OVER:	/**	1mオーバーの時	*/
				page_loop = 0;	/**	１ページループフラグセット	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				rtn = TX_1M_OVER;	/**	戻り値1mオーバー	*/
				break;
			default:	/**	その他	*/
				page_loop = 0;
				MDM_BreakTxTask();
				rtn = TX_1M_OVER;	/* T.3.1 error */
				break;
			}
		}
	}
	return (rtn);
}

UBYTE	EcmTxSub(void)
{
	/* ローカル変数宣言 */
	UBYTE	rtn;	/*	リターンコード	*/
	UBYTE	i;
	UBYTE	page_loop;
	UBYTE	cdc_stat;
	UDWORD	real_remain_encode_data;
	UWORD	ecm_debug_count;
	UBYTE	dummy;

	/*	変数初期化処理	*/

	ebr_cnt = 0;	/**	ＥＣＭバッファ読み出しバイト数	*/
	rtn = 0;	/**	リターンコード初期化	*/
	MDM_EcmFrameNumber = 0;	/**	ＥＣＭフレームナンバー初期化	*/

    /*----------------------*/
    /*  同期信号待ち処理    */
    /*----------------------*/
	/* 日立メールシステムにて画データ前同期信号が短いと受信できないという不具合（ＫＩＲＩにて発生）があるので反映させます */
	/* 1998/06/02 by T.Soneoka */
	wai_tsk(200/10);	/**	タスクウェイト２００ｍｓ	*/

	/*	先頭２５６ｂｙｔｅブロック送出処理待ち処理（ＤＭＡ終了割り込み　ＯＲ　１ページ符号変換タスクより）	*/
	rtn = MDM_WaitForTxStartOrTxError();
	switch (rtn) {
	case TX_LAMP_ERR:
	case TX_DOC_ERR:
	case TX_1M_OVER:
	case TX_MEM_ERR:
		MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
		return rtn;
		break;
	default:
		break;
	}

	/*
	**  by T.Soneoka 1997/12/17
	*/
	if (SYS_DocBlock.Dst.Code == SYS_JBIG_CODE) {
		MDM_JBG_ReadBIH();
	}

	/*	送出未処理のエンコードデータ数取得	*/
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	cdc_stat = CodecPageStatus;
	TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
	if (cdc_stat == CDC_RTC_DET) {
		if (EncodeDataCount >= 0x10000) {
			EncodeDataCount -= 0x10000;
			MDM_EcmRemainCount = EncodeDataCount;
			RemainEncodeData = EncodeDataCount;	/**	送出未処理エンコードデータ数更新	*/

			/* 2000/02/08 Y.Murata */
			CMN_EnableInterrupt();	/**	割り込み許可	*/
			if (MDM_EcmRemainCount) {
				MemoryMove((UBYTE *)&EcmBuffer[0][0], (UBYTE *)&EcmBuffer2[0][0], MDM_EcmRemainCount);
				MDM_EcmRemainCount = 0;
			}

		}
		else {
			RemainEncodeData = EncodeDataCount;	/**	送出未処理エンコードデータ数更新	*/
		}
	}
	else {
		RemainEncodeData = EncodeDataCount;	/**	送出未処理エンコードデータ数更新	*/
	}
	CMN_EnableInterrupt();	/**	割り込み許可	*/

#if 0	/* 2000/02/07 Y.Murata */
** 	if (MDM_EcmRemainCount) {
** 		MemoryMove((UBYTE *)&EcmBuffer[0][0], (UBYTE *)&EcmBuffer2[0][0], MDM_EcmRemainCount);
** 		MDM_EcmRemainCount = 0;
** 	}
#endif

	/*	ＦＣＤフレーム送信登録／送出処理	*/
	page_loop = 1;	/**	１ページ完了フラグ設定	*/
	while (page_loop) {	/**	１ページ送信ループ（エンコードデータがなくなり、ＲＴＣ（その他）を検出するまで）*/
		/*	送出バイト数取得処理、通常１ブロック２５６ｂｙｔｅ
		**	次送出バイト数更新
		*/
		next_mbf_set_cnt = GetCount(RemainEncodeData, FcomEcmSize);	/**	１ブロック送出バイト数切り出し（２５６ｂｙｔｅ以下）	*/

		/*	フレーム書き込みモデムバッファ獲得処理	*/
		ModemBufferWaiSem(ModemControl.WritePoint);	/**	フレーム書き込みモデムバッファ獲得	*/
		SetClear(MDM_ModemBuffer[ModemControl.WritePoint], MODEM_BUFFER_LENGTH, 0x00);

		/*	ＦＣＤフレーム送信登録（ＥＣＭバッファからモデムバッファにプログラム転送）／送出処理	*/
		WriteFCD(MDM_EcmFrameNumber, &MDM_ModemBuffer[ModemControl.WritePoint][0], (UBYTE *)&EcmBuffer[0][0] + ebr_cnt, next_mbf_set_cnt);

		/*	ＥＣＭフレームナンバー更新	*/
		MDM_EcmFrameNumber++;	/**	ＥＣＭフレームナンバーインクリメント	*/

		/*	ＥＣＭバッファ読み出し数更新	*/
		ebr_cnt += (UDWORD)next_mbf_set_cnt;	/**	ＥＣＭバッファ読み出しバイト数更新	*/

		/*	送出未処理エンコードデータ数取得処理	*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		RemainEncodeData = EncodeDataCount - ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/

		if (EncodeDataCount > (UDWORD)0x10000) {
			if (ebr_cnt < 0x10000) {
				RemainEncodeData = ((UDWORD)0x10000 - ebr_cnt);
			}
			else {
				RemainEncodeData = 0;
			}
		}

		cdc_stat = CodecPageStatus;
		TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
		CMN_EnableInterrupt();	/**	割り込み許可	*/

		/*	強制終了処理(ストップ処理）		*/
		if (MDM_TxStopSwFlag == 0) {	/**	画データ用ストップＳｗがＯＦＦの時	*/
			if (SYS_FaxComStopSwitch()) {	/**	ストップＳｗ　ＯＮの時	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/

				if (MDM_TxForceStop()) {	/**	強制終了時 PRO_QUICK_TX	*/
					rtn = TX_STOPPED;	/**	戻り値ストップＳｗＯＮ設定	*/
					if ((CommunicateType == TX_ECM_SCAN) ||
					    (CommunicateType == TX_G3_SCAN)) {	/**	交信タイプがスキャナ送信の時	*/
						if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {	/**	スキャナモータがストップしていない時	*/
							SCN_StopMotor();	/**	スキャナモータストップ	*/
							SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
							LampOff();	/**	ランプＯＦＦ	*/
						}
					}
				}
				MDM_TxStopSwFlag = 1;	/**	画データ用ストップＳｗをＯＮに設定	*/
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_FAXCOM;	/**	マシンステータスの通信ストップ解除	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
			else {
				rtn = CheckTxSystemError();	/**	送信異常チェック	*/
			}
			if (rtn) {	/**	送信異常有りの時	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				return (rtn);
			}
		}

		/*	送出終了／子タスク終了処理	*/
		if (RemainEncodeData == (UDWORD)0) {	/**	エンコードエンコードデータがないとき	*/
			switch (cdc_stat) {	/**	コーデックの状態	*/
			case CDC_CONTINUE:	/**	エンコード中	*/
				MDM_DebugDataWaitCnt++;
				/*	モデムバッファにセットする方が速い時
				**	符号変換完了待ち（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）
				*/
				rtn = MDM_WaitForTxStartOrTxError();
				switch (rtn) {
				case TX_LAMP_ERR:
				case TX_DOC_ERR:
				case TX_1M_OVER:
				case TX_MEM_ERR:
					MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
					return rtn;
					break;
				default: /* 送信開始 */
					break; /* 処理続行 */
				}

				/*	送出未処理のエンコードデータ数取得	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				RemainEncodeData = EncodeDataCount - ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/

				if (EncodeDataCount > (UDWORD)0x10000) {
					if (ebr_cnt < 0x10000) {
						RemainEncodeData = ((UDWORD)0x10000 - ebr_cnt);
					}
					else {
						RemainEncodeData = 0;
					}
				}

				cdc_stat = CodecPageStatus;
				TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/

				if (ecm_debug_count >= 1500) {
					ecm_debug_count++;
				}

				break;
			case CDC_BLOCK_END:	/**	ＥＣＭバッファオーバの時	*/
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				rtn = TX_BLOCK_END;	/**	戻り値ブロックエンド設定	*/
				break;
			case CDC_RTC_DET:	/**	ＲＴＣ検出の時	*/
				if (MDM_EcmBufferOverEncodeStop) {
					page_loop = 0;	/**	１ページ送信ループ抜ける	*/
					rtn = TX_BLOCK_END;	/**	戻り値ブロックエンド設定	*/
				}
				else {
					page_loop = 0;	/**	１ページ送信ループ抜ける	*/
					MDM_BreakTxTask();	/**	各子タスク終了処理	*/
					rtn = TX_PAGE_END;	/**	戻り値１ページ送信完了設定	*/
				}

				break;
			case CDC_STOPPED:	/**	正常ストップＳｗ終了の時	*/
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				rtn = TX_STOPPED;	/**	戻り値ストップＳＷ設定	*/
				MDM_BreakTxTask();	/**	各子タスク終了処理	*/
				break;
			case CDC_DOC_OVER:	/**	1mオーバーの時	*/
				page_loop = 0;	/**	１ページループフラグセット	*/
				MDM_BreakTxTask();	/**	送信子タスク終了	*/
				rtn = TX_1M_OVER;	/**	戻り値1mオーバー	*/
				break;
			default:
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				MDM_BreakTxTask();	/**	各子タスク終了処理	*/
				rtn = TX_1M_OVER;	/* T.3.1 error */
				break;
			}
		}

		/*	ＴＴＩ送出と画データとの間で２５６ｂｙｔｅそろわない時	 */
		else if (RemainEncodeData < (UDWORD)FcomEcmSize) {	/**	エンコードエンコードデータがないとき	*/
			switch (cdc_stat) {	/**	コーデックの状態	*/
			case	CDC_CONTINUE:	/**	エンコード中の時	*/
				MDM_DebugDataWaitCnt++;
				/*	モデムバッファにセットする方が速い時
				**	符号変換完了待ち（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）
				*/
				rtn = MDM_WaitForTxStartOrTxError();
				switch (rtn) {
				case TX_LAMP_ERR:
				case TX_DOC_ERR:
				case TX_1M_OVER:
				case TX_MEM_ERR:
					MDM_BreakTxTask();	/**	送信各子タスク終了処理	*/
					return rtn;
					break;
				default:
					break;
				}

				/*	送出未処理のエンコードデータ数取得	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				RemainEncodeData = EncodeDataCount - ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/

				if (EncodeDataCount > (UDWORD)0x10000) {
					if (ebr_cnt < 0x10000) {
						RemainEncodeData = ((UDWORD)0x10000 - ebr_cnt);
					}
					else {
						RemainEncodeData = 0;
					}
				}

				cdc_stat = CodecPageStatus;
				TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/

				break;
			default:	/**	その他の時	*/
				break;
			}
		}
	}
	MDM_EcmFrameNumber--;	/**	ＥＣＭフレームナンバーデクリメント	*/
	LastEcmFrameNumber = MDM_EcmFrameNumber;	/**	最終ＥＣＭフレームナンバー設定	*/
	LastEcmFrameLength = next_mbf_set_cnt;	/**	最終ＥＣＭフレームサイズ設定	*/

	/*	ＲＣＰフレーム送信登録／送出処理	*/
	for (i = 0; i < RCP_COUNT; i++) {	/**	ＲＣＰフレーム３個送出するまで	*/
		/*	フレーム書き込みモデムバッファ獲得処理	*/
		ModemBufferWaiSem(ModemControl.WritePoint);	/**	フレーム書き込みモデムバッファ獲得	*/

		/*	最終フレーム登録	*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/

		/**	ＲＣＰフレーム送信登録／送出処理	*/
		WriteRCP(&MDM_ModemBuffer[ModemControl.WritePoint][0]);		/**	ＲＣＰフレーム登録	*/

		/*	最終フレーム登録	*/
		if (i == (RCP_COUNT - 1)) {	/**	最後のＲＣＰかチェック	*/
			ModemBlock.Chain = SET_COMPL;	/**	最終フレーム登録	*/
		}
		CMN_EnableInterrupt();	/**	割り込み許可	*/

#if (0)	/** 上でモデムバッファはセマフォ管理をしているのでこのウエイトはいらない By O.K Feb.06,1996 **/
		/*	タスクウェイト	*/
		wai_tsk(50/10);	/**	タスクウェイト５０ｍｓ	*/
#endif

	}
	return (rtn);
}
#endif /* End of PRO_CODEC_NUMBER */


#if (PRO_DIAG == ENABLE) /* #if is added by H.Kubo 1998/04/02 */
/*************************************************************************
	module		:[バックアップＲＡＭからＥＣＭバッファにコピーする]
	function	:[
		・機器パラメータ
		・機種共通メモリＳｗ
		・機種固有メモリＳｗ
		・ワンタッチダイヤル
		・短縮ダイヤル
		・プログラムワンタッチ
		・転送先番号
		・部門別料金
		・一括送信
		・料金管理
		・市外料金
		・コメント
		・発信元番号
		・発信元名
		・カナＩＤ
		・親展ボックス
		・受信モード
		・ワーディング
		・ライフモニタ
		のデータの順番にＥＣＭバッファにコピーする
	]
	return		:[なし]
	common		:[]
	condition	:[
	]
	comment		:[
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CDC]
	date		:[1996/6/17]
	author		:[曽根岡拓]
*************************************************************************/
void CopyBackUpRAM_ToEcmBuffer(void)
{
	UBYTE i;
	UBYTE *start_address;
	UBYTE *current_address;
	UWORD size;

	start_address = (UBYTE *)&EcmBuffer[0][0];
	current_address = start_address;

	for (i = 0; i < HIGH_RDS_DATA_MAX; i++) {
		size = HighRDS_Table[i].BackupDataLength;
		MemoryMove((UBYTE *)current_address, (UBYTE *)HighRDS_Table[i].BackupDataAddress, size);
		current_address += size;
	}
	BackUpDataLength = current_address - start_address;

#if (0)
//	/* 機器パラメータの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_MachineParameter);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_MachineParameter, size);
//	current_address += size;
//
//	/* 機種共通メモリＳｗの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_MemorySwitch);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_MemorySwitch, size);
//	current_address += size;
//
//	/* 機種固有メモリＳｗの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_MachineUniqSwitch);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_MachineUniqSwitch, size);
//	current_address += size;
//
//	/* ワンタッチダイヤルの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_OnetouchDial);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_OnetouchDial, size);
//	current_address += size;
//
//	/* 短縮ダイヤルの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_SpeedDial);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_SpeedDial, size);
//	current_address += size;
//
//	/* プログラムワンタッチの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_ProgramOnetouch);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_ProgramOnetouch, size);
//	current_address += size;
//
//	/* 転送先番号の全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_SubDial);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_SubDial, size);
//	current_address += size;
//
//	/* 部門別料金の全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_DepartFile);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_DepartFile, size);
//	current_address += size;
//
//	/* 一括送信の全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_BatchTxFile);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_BatchTxFile, size);
//	current_address += size;
//
//	/* 料金管理の全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_CostTable);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_CostTable, size);
//	current_address += size;
//
//	/* 市外料金の全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_NTT_AccessFile);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_NTT_AccessFile, size);
//	current_address += size;
//
//	/* コメントの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_CoverPageMessage);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_CoverPageMessage, size);
//	current_address += size;
//
//	/* 発信元番号の全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_ID_Buffer);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_ID_Buffer, size);
//	current_address += size;
//
//	/* 発信元名の全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_TTI_Buffer);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_TTI_Buffer, size);
//	current_address += size;
//
//	/* カナＩＤの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_TTI_ID_Buffer);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_TTI_ID_Buffer, size);
//	current_address += size;
//
//	/* 親展ボックスの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_MailBox);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_MailBox, size);
//	current_address += size;
//
//	/* 受信モードの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_RxModeSwitch);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_RxModeSwitch, size);
//	current_address += size;
//
//	/* ワーディングの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_WordingNumber);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_WordingNumber, size);
//	current_address += size;
//
//	/* ライフモニタの全データをＥＣＭバッファに転送 */
//	size = sizeof(SYS_LifeMonitor);
//	MemoryMove((UBYTE *)current_address, (UBYTE *)&SYS_LifeMonitor, size);
//	current_address += size;
//
//	BackUpDataLength = current_address - start_address;
#endif
}
#endif	/* End of PRO_DIAG */


