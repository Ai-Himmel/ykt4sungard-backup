/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMRXCS.C												 */
/*	モジュール	 :															 */
/*				 : TransmitPPR()											 */
/*				 : JudgeECM_RxErrorFrame()									 */
/*				 : MemorizePPS_Frame()										 */
/*				 : WaitRxPaperCut()											 */
/*				 : CheckRxPrinterError()									 */
/*				 : GetRxPrinterErrorStatus()								 */
/*				 : CheckRxPixResultPhaseC()									 */
/*				 : CheckRxPixResultPhaseD()									 */
/*				 : CheckRxPixResultSub()									 */
/*				 : FaxRxTimeOutEvade()										 */
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
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\mem_def.h"

#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#if (PRO_PANEL == ANK) /* #if is added by H.Kubo 199/709/08 */
#include	"\src\atlanta\opr\ank\define\opr_pro.h"	/* 1996/06/28 add By T.Yamaguchi*/
#endif /* */
#if (PRO_PANEL == KANJI) /* #if is added by H.Kubo 199/709/08 */
#include	"\src\atlanta\opr\kanji\define\opr_pro.h"	/* 1996/06/28 add By T.Yamaguchi*/
#endif /* */
#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\fcm_data.h"

#if (PRO_MODEM == ORANGE3)
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F)
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

#if (PRO_PRINTER_RX == ENABLE)			/*	プリンタ受信機	*/
 #if (PRO_PRINT_TYPE == THERMAL)	/* Add By O.Kimoto 1998/10/28 */
  #if defined(STOCKHM2)
#include "\src\atlanta\prt\lv_therm\define\prt_drv.h"
#include "\src\atlanta\prt\lv_therm\ext_v\prt_data.h"
  #else
#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
  #endif
#include "\src\atlanta\define\mntsw_h.h"	/* Endmark3 By O.Kimoto 1999/02/19 */
 #endif
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/17 K.Kawata */
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#endif
/*************************************************************************
	module		:[ＰＰＲ作成，送出]
	function	:[
		1.	ＰＰＲフレームを作成し，送出する
	]
	return		:[]
	common		:[
		TxBaudRate
		TxStandardFrameByteCount		TxNonStandardFrameByteCount
		TxIDFrameByteCount
		MDM_ModemBuffer		MDM_EcmStatus
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/16]
	author		:[竹内茂樹]
*************************************************************************/
void	TransmitPPR(BYTE error_frame )		/*	0=エラーフレームのみ／1=全フレーム	*/
{
	UWORD	count;
	UBYTE	*modem_buf;

	count = 0;

	modem_buf = &MDM_ModemBuffer[InSTD][0];

	/**	モデムバッファにＰＰＲフレームのＦＣＦをセット	*/
	*modem_buf++ = ADDRESS_FIELD_DATA;
	*modem_buf++ = LAST_FRAME_DATA;
	*modem_buf++ = PPR_F;

	if (error_frame == 1) {		/**	全フレーム指定のＰＰＲのＦＩＦ	*/
		/**	モデムバッファに全フレームＦＦをセット	**
		***	(全フレームを再送要求するため)			*/
		for (count=0; count < ECM_STATUS_MAX; count++) {
			*modem_buf++ = 0xFF;
		}
	}
	else {						/**	通常のＰＰＲのＦＩＦ	*/
		/**	モデムバッファにＥＣＭフレーム情報をコピー	*/
		for (count=0; count < ECM_STATUS_MAX; count++) {
			*modem_buf++ = MDM_EcmStatus[count];
		}
	}

	/**	応答送信（ＰＰＲ）	*/
	TxStandardFrameByteCount	= 3 + ECM_STATUS_MAX;
	TxNonStandardFrameByteCount = 0;
	TxID_FrameByteCount			= 0;
	MDM_TransmitCommand();

	/* ＰＰＲを出した時は，ＰＲＩ－Ｑを受信した回数を初期化する	 Nov.25.1994 */
	PRI_Q_RxFlag  = 0;		/**	ＰＲＩ－Ｑ受信フラグをクリア	*/
	PRI_Q_RxCount = 0;		/**	ＰＲＩ－Ｑ回数クリア	*/
}


/*************************************************************************
	module		:[ＥＣＭ受信エラーフレーム確認]
	function	:[
		1.	ＥＣＭ受信のエラーフレームの有無を判定する
	]
	return		:[
		0	エラーフレームなし
		1	エラーフレームあり
	]
	common		:[
		RxFCF		RxOptionFCF
		ECM_FirstFrameCounter
		RxECM_RetransmittedFlag		:ＥＣＭ再送受信初回フラグ
		MDM_ModemBuffer		MDM_EcmStatus
	]
	condition	:[
		必ずＰＰＳを受信していること
	]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/16]
	author		:[竹内茂樹]
*************************************************************************/
BYTE	JudgeECM_RxErrorFrame( void )
{
	WORD	fc;
	UBYTE	mask;
	UBYTE	*ecm_status;

	if (RxECM_RetransmittedFlag == 1) {		/**	初回のＥＣＭ再送受信	*/
		/**	１部分ページのＥＣＭフレームカウンタを記憶する	*/
		ECM_FirstFrameCounter = MDM_ModemBuffer[FCF_Point][6];
		/**	ＥＣＭ再送受信初回フラグをクリアする	*/
		RxECM_RetransmittedFlag = 0;
	}

	fc = (WORD)ECM_FirstFrameCounter;
	ecm_status = &MDM_EcmStatus[0];
	mask = 0x01;

#if (PRO_TX_SPEED == V34) /* Add By O.Kimoto 1997/12/02 */
	FCM_GetRxErrorFrame();		/* エラーフレーム獲得（セーブ） 1996/05/16 Y.Murata */
#endif

	while (fc >= 0) {	/**	ＰＰＳでのフレームカウンタ分繰り返す	*/
		if ((*ecm_status & mask) != 0) {	/**	エラーフレームあり	*/
			return (1);				/**	リターン１	*/
		}
		mask <<= 1;
		fc--;
		if (mask == 0x00) {
			mask = 0x01;
			ecm_status++;
		}
	}

	return (0);		/**	リターン０	*/
}


/*************************************************************************
	module		:[ＰＰＳのカウンタ記憶]
	function	:[
		1.	ＰＰＳフレームのＰＣ，ＢＣ，ＦＣを各々の変数にコピーする
	]
	return		:[]
	common		:[
		ECM_PageCounter		ECM_BlockCounter		ECM_FrameCounter
		FCF_Point				:モデムバッファ内の，ＦＣＦの位置
		MDM_ModemBuffer
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/17]
	author		:[竹内茂樹]
*************************************************************************/
void	MemorizePPS_Frame( void )
{
	ECM_PageCounter	 = MDM_ModemBuffer[FCF_Point][4];		/**	ページカウンタを変数にセット	*/
	ECM_BlockCounter = MDM_ModemBuffer[FCF_Point][5];		/**	ブロックカウンタを変数にセット	*/
	ECM_FrameCounter = MDM_ModemBuffer[FCF_Point][6];		/**	フレームカウンタを変数にセット	*/
}


/*************************************************************************
	module		:[プリンタ受信でカット待ち]
	function	:[
		1.	受信記録紙カットの終了を待つ (カット紙では即リターン)
		2.	指定時間を経過した場合は一旦リターンする
		3.	指定時間が０の場合は，カット中かどうかのみチェック
	]
	return		:[
		1	カット終了 (ＯＫ／ＮＧ問わない)
		0	カット中　 (指定時間経過)
	]
	common		:[
		PRN_Control
	]
	condition	:[
		プリンタ受信の場合で，命令受信と
		応答送信の間に実行すること
	]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[FCM]
	date		:[1994/06/20]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	WaitRxPaperCut(UBYTE	time)	/*	タイムアウト時間(0～255)を指定 (100ms単位)	*/
{
#if (0)	/* 1998.6.3 K.Kawata*/
** #if (PRO_PAPER_TYPE == ROLL_PAPER)	/*	もみじ／さつき	*/
** 	/*----------------------*/
** 	/*	記録紙カット待ち	*/
** 	/*----------------------*/
** 	while (PRN_Control.Status == PRN_PAGE_CUT) {	/**	記録紙カット中	*/
** 		if (time-- > 0) {	/**	指定時間経過 (time * 0.1sec)	*/
** 			wai_tsk( 10 );		/**	１００msウェイト	*/
** 		}
** 		else {
** 			return( 0 );		/**	タイムアウトで一旦リターン	*/
** 		}
** 	}
** #endif
#else
 #if (PRO_PRINT_TYPE == THERMAL)	/* Add By O.Kimoto 1998/10/28 */
	/*----------------------*/
	/*	記録紙カット待ち	*/
	/*----------------------*/
#if (0)	/* 1998/11/11 by T.Soneoka */
**	while (Paper.Position == PAPER_POS_MOVE_TO_CUT) {	/**	記録紙カット中	*/
#endif
	while (Paper.Position != PAPER_POS_PRINTING) {	/**	記録紙カット中－＞印字位置にくるまで	*/
		if (time-- > 0) {	/**	指定時間経過 (time * 0.1sec)	*/
			wai_tsk( 10 );		/**	１００msウェイト	*/
		}
		else {
			return( 0 );		/**	タイムアウトで一旦リターン	*/
		}
	}
	/**	カット終了リターン	*/
	return( 1 );
 #endif
 #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.4.6 K.Kawata	*/
	while (PRN_Control.PageCutPhase < 2) {
		if (time-- > 0) {	/**	指定時間経過 (time * 0.1sec)	*/
			wai_tsk( 10 );		/**	１００msウェイト	*/
		}
		else {
			return( 0 );		/**	タイムアウトで一旦リターン	*/
		}
	}
	return( 1 );
 #endif
#endif
}

/*************************************************************************
	module		:[プリンタエラーの内容を確認]
	function	:[
		1.	MachineStatusのプリンタエラー，画データ受信結果，
		.	PRN_ControlのプリンタエラーをＯＲで見て，エラーなら
		.	プリンタ受信エラーフラグをセットする
		.	(このフラグで次ページからメモリ受信に切り替える)
		2.	黒エンド，カッターエラー，リボンエンド以外の場合は
		.	印字がＮＧだとして，画データ受信結果をプリンタエラー
		.	とする
	]
	return		:[]
	common		:[
		RxPageFinishStatus		RxECM_Mode
		RxPrinterErrorFlag		PRN_Control
	]
	condition	:[
		バッファリング受信は除く (Aug.03.1994)
	]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[FCM]
	date		:[1994/07/21]
	author		:[竹内茂樹]
*************************************************************************/
void	CheckRxPrinterError( void )
{
#if (PRO_PRINTER_RX == ENABLE)			/*	プリンタ受信機	*/
 #if (PRO_PRINT_TYPE == THERMAL)	/* Add By O.Kimoto 1998/10/28 */
	if (CMN_CheckFaxComPrinterError()
	||	(RxPageFinishStatus == RX_PRT_ERR)
	||	(PrinterError)) {			/**	プリンタエラーあり	*/

		/**	プリンタエラーフラグをセット (メモリ受信切り替え用)	*/
		RxPrinterErrorFlag = 1;

		if (RxECM_Mode == ECM_OFF) {	/**	Ｇ３受信	*/
			if (PrinterError & ~(PRT_ERROR_NO_PAPER
									 | PRT_ERROR_CUT_ERROR)) {	/**	プリンタエラー(印字もＮＧ)	*/
				/**	画データ受信結果をプリンタエラーとする	*/
				RxPageFinishStatus = RX_PRT_ERR;

				/*	紙切れとカッタージャム（－＞ＲＴＮで次ページから代行受信）*/
				/*	そのページは印字できたものとして，受信結果はそのまま	*/
			}
		}
		else {		/**	ＥＣＭ受信	*/
#if (0) /* 1998/11/28 by T.Soneoka */
**			if ((RxPageFinishStatus == RX_PAGE_END)
**			&&	(PrinterError & ~( PRT_ERROR_NO_PAPER
**									  | PRT_ERROR_CUT_ERROR))) {	/**	１ページ受信終了&&プリンタエラー(印字もＮＧ)	*/
**				/**	画データ受信結果をプリンタエラーとする	*/
**				RxPageFinishStatus = RX_PRT_ERR;
**			}
#endif
			RxPageFinishStatus = RX_PRT_ERR;
		}
	}

	/* EndMark3
	** by O.Kimoto 1999/02/19
	*/
	else if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {
		if (RxECM_Mode == ECM_OFF) {	/**	Ｇ３受信	*/
			if (EndMarkDetect == TRUE) {
				RxPageFinishStatus = RX_PRT_ERR;
				RxPrinterErrorFlag = 1;
			}
		}
		/* ＥＣＭ時は上位で判断します */
	}
	
 #else
	if (CMN_CheckFaxComPrinterError()
	||	(RxPageFinishStatus == RX_PRT_ERR)
	||	(PRN_Control.Error)) {			/**	プリンタエラーあり	*/

		/**	プリンタエラーフラグをセット (メモリ受信切り替え用)	*/
		RxPrinterErrorFlag = 1;

		if (RxECM_Mode == ECM_OFF) {	/**	Ｇ３受信	*/
			if (PRN_Control.Error & ~( PRN_ENDMARK_ERROR
									 | PRN_CUTTER_ERROR
									 | PRN_NO_INK_ERROR)) {	/**	プリンタエラー(印字もＮＧ)	*/
				/**	画データ受信結果をプリンタエラーとする	*/
				RxPageFinishStatus = RX_PRT_ERR;

				/*	黒エンド，カッタージャム，インクリボン切れの場合は		*/
				/*	そのページは印字できたものとして，受信結果はそのまま	*/
			}
		}
		else {		/**	ＥＣＭ受信	*/
			if ((RxPageFinishStatus == RX_PAGE_END)
			&&	(PRN_Control.Error & ~( PRN_ENDMARK_ERROR
									  | PRN_CUTTER_ERROR
									  | PRN_NO_INK_ERROR))) {	/**	１ページ受信終了&&プリンタエラー(印字もＮＧ)	*/
				/**	画データ受信結果をプリンタエラーとする	*/
				RxPageFinishStatus = RX_PRT_ERR;
			}
		}
	}
 #endif
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/9 K.Kawata*/
	if ((PRN_Control.Error) || (RxPageFinishStatus == RX_PRT_ERR)) {
		if (RxECM_Mode == ECM_OFF) {	/**	Ｇ３受信	*/
				RxPageFinishStatus = RX_PRT_ERR;
		}
		else {		/**	ＥＣＭ受信	*/
			if (RxPageFinishStatus == RX_PAGE_END) {
				RxPageFinishStatus = RX_PRT_ERR;
			}
		}
	}
#endif
}


/*************************************************************************
	module		:[プリンタ受信エラー種類を取得]
	function	:[
		プリンタエラーをチェックして，対応するメインへのSubMessage1を返す
	]
	return		:[
		**	SubMessage1	 **
		MSG_FAXCOM_NO_PAPER			1	記録紙切れ／黒エンドマーク
		MSG_FAXCOM_CUTTER_ERROR		2	カッターエラー
		MSG_FAXCOM_PAPER_JAM		3	ジャム
		MSG_FAXCOM_COVER_OPEN		4	カバーオープン
		MSG_FAXCOM_NO_INK			5	ドナー切れ
		MSG_FAXCOM_TH_HI_TEMP		6	Ｔ／Ｈハイテンプ

		**							0	エラーなし
	]
	common		:[
		PRN_Control
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[FCM]
	date		:[1994/07/20]
	author		:[竹内茂樹]
*************************************************************************/
UWORD		GetRxPrinterErrorStatus( void )
{
#if (PRO_PRINTER_RX == ENABLE)	/*	もみじ／さつき／ラベンダ	*/
 #if (PRO_PRINT_TYPE == THERMAL)	/* Add By O.Kimoto 1998/10/28 */
	/*--------------------------*/
	/*	受信原稿長オーバ		*/
	/*--------------------------*/
	if (PrinterError & PRT_ERROR_3M_OVER) {
		/* ↓暫定です 平尾殿適当な値をいれてください  1998/12/15 by T.Soneoka */
		/* いれました by H.Hirao 1998/12/16 */
		return (MSG_FAXCOM_3M_OVER);
	}
	/*--------------------------*/
	/*	カバーオープン			*/
	/*--------------------------*/
	if (PrinterError & PRT_ERROR_COVER_OPEN) {
		return (MSG_FAXCOM_COVER_OPEN);		/**	カバーオープン	*/
	}
	/*--------------------------*/
	/*	紙切れ (黒エンドマーク)	*/
	/*--------------------------*/
	else if (PrinterError & PRT_ERROR_NO_PAPER) {
		return (MSG_FAXCOM_NO_PAPER);		/**	紙切れ			*/
	}
	/*--------------------------*/
	/*	カッターエラー			*/
	/*--------------------------*/
	else if (PrinterError & PRT_ERROR_CUT_ERROR) {
		return (MSG_FAXCOM_CUTTER_ERROR);	/**	カッターエラー	*/
	}
	/*--------------------------*/
	/*	ジャム					*/
	/*--------------------------*/
	else if (PrinterError & PRT_ERROR_JAM) {
		return (MSG_FAXCOM_PAPER_JAM);		/**	ジャム			*/
	}
	/*--------------------------*/
	/*	Ｔ／Ｈハイテンプ		*/
	/*--------------------------*/
	else if (PrinterError & PRT_ERROR_HIGH_TEMP) {
		return (MSG_FAXCOM_TH_HI_TEMP);		/**	Ｔ／Ｈハイテンプ	*/
	}
 #else
	/*--------------------------*/
	/*	カバーオープン			*/
	/*--------------------------*/
	if (PRN_Control.Error & PRN_COVER_OPEN_ERROR) {
		return (MSG_FAXCOM_COVER_OPEN);		/**	カバーオープン	*/
	}
	/*--------------------------*/
	/*	紙切れ (黒エンドマーク)	*/
	/*--------------------------*/
	else if (PRN_Control.Error & ( PRN_NO_PAPER_ERROR
								| PRN_ENDMARK_ERROR)) {
		return (MSG_FAXCOM_NO_PAPER);		/**	紙切れ			*/
	}
	/*--------------------------*/
	/*	カッターエラー			*/
	/*--------------------------*/
	else if (PRN_Control.Error & PRN_CUTTER_ERROR) {
		return (MSG_FAXCOM_CUTTER_ERROR);	/**	カッターエラー	*/
	}
	/*--------------------------*/
	/*	ジャム					*/
	/*--------------------------*/
	else if (PRN_Control.Error & PRN_JAM_ERROR) {
		return (MSG_FAXCOM_PAPER_JAM);		/**	ジャム			*/
	}
	/*--------------------------*/
	/*	ドナー切れ				*/
	/*--------------------------*/
	else if (PRN_Control.Error & PRN_NO_INK_ERROR) {
		return (MSG_FAXCOM_NO_INK);			/**	ドナー切れ		*/
	}
	/*--------------------------*/
	/*	Ｔ／Ｈハイテンプ		*/
	/*--------------------------*/
	else if (PRN_Control.Error & PRN_THERMALTMP_ERROR) {
		return (MSG_FAXCOM_TH_HI_TEMP);		/**	Ｔ／Ｈハイテンプ	*/
	}
 #endif
#endif

	return (0);		/**	エラーなしをリターン	*/
}


/*************************************************************************
	module		:[画データ受信結果チェック(フェーズＣ)]
	function	:[
		1.	画データ受信結果を確認する
		2.	エラーなら通信結果にエラーコードをセットし，通信中フラグをクリアする
		3.	ＥＣＭタイムアウトの場合，タイムアウト回避設定を確認しフラグをセットする
	]
	return		:[]
	common		:[
		RxPageFinishStatus
		FaxComPerformingFlag
		RxECM_PixTimeoutFlag	:ＥＣＭタイムアウト回避フラグ
	]
	condition	:[]
	comment		:[
		CHK_ECM_RxTM_OutEvade()		ＥＣＭタイムアウト回避設定
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/02/07]
	author		:[竹内茂樹]
*************************************************************************/
void		CheckRxPixResultPhaseC( void )
{
	switch (RxPageFinishStatus) {	/**	画データ受信結果	*/
	case	RX_TMOUT:				/**	受信フレームタイムアウト	*/
		if ((RxECM_Mode == ECM_ON)
		&&	(CHK_UNI_ECM_RxTM_OutEvade() != 0)) {	/**	ＥＣＭ受信タイムアウト回避する	UNI_SW_C0-0 */
			/**	ＥＣＭタイムアウト回避フラグをセットする	*/
			RxECM_PixTimeoutFlag = 1;
		}
		else {
			/*	MDM_BreakRxTask();	**	ＥＣＭタスク停止	*/
			/*	↑これは後(RxCの最後)でする Jul.11.1994	*/
			ReceiveError( 0x52 );	/**	Ｒ．５．２	*/
#if defined(DEU) || defined(EUR)	/* by M.H '97/03/23 ﾀｲﾑｱｳﾄ時にDCNを送出して終了する */
									/* 欧州仕様追加 by M.H 1999/09/16 */
			FaxPhaseE(1);
#endif
		}
		break;
	default:						/**	フェーズＣ／Ｄ共通処理	*/
		CheckRxPixResultSub();	/**	画データ受信結果を確認	*/
		break;
	}
}


/*************************************************************************
	module		:[画データ受信結果チェック(フェーズＤ)]
	function	:[
		1.	画データ受信結果を確認する
		2.	エラーなら通信結果にエラーコードをセットし，通信中フラグをクリアする
		3.	ＦＣＳエラーの場合，Ｒ．５．１エラーとする
	]
	return		:[]
	common		:[
		RxPageFinishStatus
	]
	condition	:[]
	comment		:[
		デコード中はR.5.1に変更
		.			Jul.20.1994
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/06]
	author		:[竹内茂樹]
*************************************************************************/
void	CheckRxPixResultPhaseD( void )
{
	switch (RxPageFinishStatus) {	/**	画データ受信結果	*/
	case	RX_CONTINUE:			/**	ＦＣＳエラーでデコード中	*/
		ReceiveError( 0x51 );		/**	Ｒ．５．１	*/
		break;
	default:						/**	フェーズＣ／Ｄ共通処理	*/
		CheckRxPixResultSub();		/**	画データ受信結果を確認	*/
		break;
	}
}


/*************************************************************************
	module		:[画データ受信結果チェック(フェーズＣ／Ｄ共通部分)]
	function	:[
		1.	画データ受信結果を確認する
		2.	エラーなら通信結果にエラーコードをセットし，通信中フラグをクリアする
		*.	ＥＣＭタイムアウトの場合，フェーズＣでは上位で処理
		*.	ＦＣＳエラーの場合，フェーズＤでは上位で処理
	]
	return		:[]
	common		:[
		RxPageFinishStatus		FaxComPerformingFlag
		FaxComResult			SYS_RemoteFaxMemoryOverFlag
		RxECM_PixTimeoutFlag	:ＥＣＭタイムアウト回避フラグ
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/06]
	author		:[竹内茂樹]
*************************************************************************/
void	CheckRxPixResultSub( void )
{
	switch (RxPageFinishStatus) {	/**	画データ受信結果	*/
	case	RX_PAGE_END:	/**	受信ＯＫ	*/
	case	RX_BLOCK_END:	/**	ＥＣＭブロックエンド	*/
	case	RX_CONTINUE:	/**	ＦＣＳエラーでデコード中	*/
	case	RX_ERROR:		/**	デコードエラー／画質不良	*/
	case	RX_PAPER_END:	/**	黒エンドマーク検出	*/	/* Jul.20.1994 */
		/**	何もしない	*/
		break;
	case	RX_STUP_ERR:	/**	コーデック資源エラー	*/
		ReceiveError( 0x35 );	/**	Ｒ．３．５	*/
		break;
	case	RX_PRT_ERR:		/**	プリンタエラー	*/
		/*	ReceiveError( 0x45 );	**	Ｒ．４．５	*/
		/*	プリンタエラーの場合は，次のページから代行受信するため，受信終了せずに	*/
		/*	Ｒ．４．５とする (通信中フラグはクリアしない)			Jun.20.1994		*/
		/**	Ｒ．４．５ (回線断しない)	*/
		FaxComResult = RECEIVEERROR | 0x0045;
		if (RxECM_Mode == ECM_ON) {
			FaxComResult |= ECM_MODE_SET;
		}
		break;
	case	RX_MEM_OVER:	/**	画像メモリオーバー	*/
/* #if (PRO_MULTI_LINE == DISABLE)	/@ 1997/01/10 Y.Murata */
/*		ReceiveError( 0x44 );	*//**	Ｒ．４．４	*/
/* #else */
		if (SYS_FaxComIndexConflictStatus == 1) {
			ReceiveError( 0x46 );	/**	Ｒ．４．６	*/
			FaxCompatibleErrorCode = SECURE_INDEX_CONFLICT_ERROR;
		}
		else {
			ReceiveError( 0x44 );	/**	Ｒ．４．４	*/
		}
/* #endif */
#if (PRO_REMOTE_FAX == ENABLE)	/* Jul.05.1994 */
		if (SYS_RxMemoryFileItem == SYS_MEM_REMOTE_TX_FILE) {	/**	リモートＦＡＸ受信原稿	*/
			/**	リモートＦＡＸチェックメッセージフラグをセットする	*/
			SYS_RemoteFaxMemoryOverFlag = 1;
		}
#endif
#if (PRO_SECURITY_RX == ENABLE)
		/* セキュリティー受信時のメモリオーバーのチェックメッセージプリント要求 */
		SetSecurityRxChkMsgPrint();			/* add By T.Yamaguchi 96/06/28 */
#endif
		break;
	case	RX_TMOUT:		/**	受信フレームタイムアウト	*/
		/*	MDM_BreakRxTask();	**	ＥＣＭタスク停止	*/
		/*	↑これは後(RxCの最後)でする Jul.11.1994	*/
		ReceiveError( 0x52 );	/**	Ｒ．５．２	*/
		break;
	case	RX_STOPPED:		/**	停止キー押下	*/
		ReceiveError( 0x14 );	/**	Ｒ．１．４	*/
#if defined(DEU) || defined(EUR)		/* add by M.HARADA 95.09.20 for PTT test */
										/* 欧州仕様追加 by M.H 1999/09/16 */
		FaxPhaseE(3);									/** フェーズＥ */
#endif
		break;
	case	RX_CARRIER_DOWN:	/**	ＥＯＬ未検出でキャリア断	*/
	case	RX_CONTI_ERR:		/**	連続エラーライン数オーバー	*/
		ReceiveError( 0x33 );	/**	Ｒ．３．３	*/
#if defined(DEU) || defined(EUR)		/* add by M.HARADA 95.09.20 for PTT test */
										/* 欧州仕様追加 by M.H 1999/09/16 */
		FaxPhaseE(3);									/** フェーズＥ */
#endif
		break;
#if defined (FRA)	/*	フランスのみ	*/
	case	RX_OVER:			/**	受信長Ａ４（Ｂ４）＋１０％オーバー	*/
		ReceiveError( 0x41 );	/**	Ｒ．４．１	*/
		break;
#else
 /*
 ** 受信３Ｍオーバチェック処理追加
 ** 1999/02/02 by T.Soneoka
 */
 #if (PRO_RX_3M_OVER == ENABLE)
	case	RX_OVER:			/*	受信長３ｍオーバー	*/
		ReceiveError( 0x41 );	/**	Ｒ．４．１	*/
		break;
 #endif
#endif
	default:
		/**	リセット	*/
		break;
	}
}


/*************************************************************************
	module		:[ＥＣＭタイムアウト回避の監視時間]
	function	:[
		現在の通信速度で，ＥＣＭの１フレーム分(256/64)を受信するのに
		要する時間を求める (単位：msec)
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		松竹桜の FaxRxTimeOutEvade() : faxresp.c を改造
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[FCM]
	date		:[1994/08/31]
	author		:[竹内茂樹]
*************************************************************************/
void		FaxRxTimeOutEvade( void )
{
	UWORD	byte_per_sec;

	switch (RxBaudRate) {
#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/07/26 */
	case	BPS33600_V34:
		byte_per_sec = 33600 / 8;		/*  byte/sec */
		break;
	case	BPS31200_V34:
		byte_per_sec = 31200 / 8;		/*  byte/sec */
		break;
	case	BPS28800_V34:
		byte_per_sec = 28800 / 8;		/*  byte/sec */
		break;
	case	BPS26400_V34:
		byte_per_sec = 26400 / 8;		/*  byte/sec */
		break;
	case	BPS24000_V34:
		byte_per_sec = 24000 / 8;		/*  byte/sec */
		break;
	case	BPS21600_V34:
		byte_per_sec = 21600 / 8;		/*  byte/sec */
		break;
	case	BPS19200_V34:
		byte_per_sec = 19200 / 8;		/*  byte/sec */
		break;
	case	BPS16800_V34:
		byte_per_sec = 16800 / 8;		/*  byte/sec */
		break;
	case	BPS14400_V34:
	case	BPS14400_V17:
	case	BPS14400_V33:
		byte_per_sec = 14400 / 8;		/* 1800 byte/sec */
		break;
	case	BPS12000_V34:
	case	BPS12000_V17:
	case	BPS12000_V33:
		byte_per_sec = 12000 / 8;		/* 1500 byte/sec */
		break;
	case	BPS9600_V34:
	case	BPS9600_V17:
	case	BPS9600_V29:
		byte_per_sec =  9600 / 8;		/* 1200 byte/sec */
		break;
	case	BPS7200_V34:
	case	BPS7200_V17:
	case	BPS7200_V29:
		byte_per_sec =  7200 / 8;		/*  900 byte/sec */
		break;
	case	BPS4800_V34:
	case	BPS4800_V27:
		byte_per_sec =  4800 / 8;		/*  600 byte/sec */
		break;
	case	BPS2400_V34:
	case	BPS2400_V27:
	default:
		byte_per_sec =  2400 / 8;		/*  300 byte/sec */
		break;

#else /* (PRO_TX_SPEED == V34) */
	case	BPS14400_V17:
	case	BPS14400_V33:
		byte_per_sec = 14400 / 8;		/* 1800 byte/sec */
		break;
	case	BPS12000_V17:
	case	BPS12000_V33:
		byte_per_sec = 12000 / 8;		/* 1500 byte/sec */
		break;
	case	BPS9600_V17:
	case	BPS9600_V29:
		byte_per_sec =	9600 / 8;		/* 1200 byte/sec */
		break;
	case	BPS7200_V17:
	case	BPS7200_V29:
		byte_per_sec =	7200 / 8;		/*	900 byte/sec */
		break;
	case	BPS4800_V27:
		byte_per_sec =	4800 / 8;		/*	600 byte/sec */
		break;
	case	BPS2400_V27:
	default:
		byte_per_sec =	2400 / 8;		/*	300 byte/sec */
		break;
#endif /* (PRO_TX_SPEED == V34) */
	}

	/*	単位は[msec]	*/
	EcmOneFrameTime = (UWORD)(((unsigned long)FcomEcmSize * 1000) / byte_per_sec);
}
