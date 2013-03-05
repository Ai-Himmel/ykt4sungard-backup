/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_RCMP.C												 */
/*	モジュール	 :															 */
/*				 : RxCompatibleCheck()										 */
/*				 : RxOriginalModeCheck()									 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : 受信時コンパチチェック									 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#include  "\src\atlanta\sh7043\define\def_tib.h"
#if defined(POPLAR_F)
#else
#include  "\src\cpu\sh7043_a\irom\define\sh_sys.h"
#endif

#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\define\mem_def.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\CL1_DATA.H"
#endif
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\MEM_PRO.H"
#include "\src\atlanta\define\APL_MSG.H"
#include "\src\atlanta\define\MON_PRO.H"
#include "\src\atlanta\define\CTRY_PRO.H"
#include "\src\atlanta\define\STNG_PRO.H"
#include "\src\atlanta\define\CMN_PRO.H"
#include "\src\atlanta\define\SYS_STAT.H"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\status.h"	/* 1997/05/12  By T.Yamaguchi */

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#if(PRO_TSI_RELAY_COM == ENABLE)
 /*-------------------------------------*/
 /* TSI による中々継指示（椛）15.Feb'95 */
 /*-------------------------------------*/
 #include "\src\atlanta\ext_v\ROM_TBL.H"
#endif
#if (PRO_CIPHER == ENABLE)
#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif

#if (PRO_MEM_RX_REJECT == ENABLE)
 UBYTE	CHK_MemoryReceiveReject(void);
#endif

#if (PRO_PRINTER_RX == ENABLE)
 #include "\src\atlanta\define\unisw_c.h" /* added by H.Hirao 1998/12/24 */
 #if (PRO_PRINT_TYPE == THERMAL)
  #include "\src\atlanta\define\sysprint.h" /* added by H.Hirao 1998/11/06 */
  #include "\src\atlanta\ext_v\man_data.h" /* added by H.Hirao 1998/11/06 */
 #endif
#endif

/**#if (PRO_KEYPANEL == PANEL_HINOKI)**/	/* 折り返し特ＲＯＭ By H.Fujimura 1999/04/15 */
/**他の機種も特ＲＯＭ対応 1999.4.21 K.Kawata **/
#include "\src\atlanta\ext_v\ini_tbl.h"
/**#endif**/

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.2.25 K.Kawata */
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\unisw_c.h"
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#include "\src\atlanta\prt\thermal\define\prn_pro.h"
#endif

/*************************************************************
	module		:[RxCompatibleCheck() (T30標準機能)]
	function	:[
		1.2ページ目以降の場合(EOM 受信後のハンドシェーク)、フレーム取り込み
		2.DCS受信の場合、各標準機能の確定を行う
			トレーニングボーレート
			受信符号化方式
			受信モード
			受信原稿幅
			受信最少伝送時間能力セット（受信方式による違いを吸収）
			最少電送時間
			記録紙長
	]
	return		:[]
	common		:[
			SYS_RxTotalPage					:受信ページ
			StdFrmName					:標準フレーム名
			FaxCompatibleErrorCode		:コンパチエラーコード
			FaxComPerformingFlag		:通信中フラグ
			RxMinimumScanningTime		:確定受信最少伝送時間
	]
	keyword		:[FCM]
	condition	:[]
	comment		:[RICE機種間で異なる点なし]
	machine		:[V53A]
	language	:[]
	date		:[1993/11/18]
	author		:[鈴木 郁二]
*************************************************************/
void RxCompatibleCheck(void)
{
	/*	マルチフレームの取り込み	*/
	if(RxFirstTimeCompatibleCheckFlag == NO) {	/**	送信最初のコンパチチェックでない	*/
		/**	フレーム取り込み */
		GetMultiFrameLine();
	}
	if(StdFrmName != NO) {	/**	標準フレーム受信	*/
		if(SetRxBaudRate() == NO) {	/**	トレーニングボーレート確定?	*/
			/**	エラー処理	*/
			FaxComPerformingFlag = NO;
			return;
		}
		if(SetRxCode() == NO) {	/**	受信符号の確定?	*/
			/**	エラー処理	*/
			FaxCompatibleErrorCode = COMMUNICATE_CODE_ERROR;
			FaxComPerformingFlag = NO;
			return;
		}
		if(SetRxMode() == NO) {	/**	受信モードの確定?	*/
			/**	エラー処理	*/
			FaxCompatibleErrorCode = COMMUNICATE_MODE_ERROR;
			FaxComPerformingFlag = NO;
			return;
		}
		if(SetRxPaperWidth() == NO) {	/**	受信幅の確定?	*/
			/**	エラー処理	*/
			FaxCompatibleErrorCode = COMMUNICATE_SIZE_ERROR;
			FaxComPerformingFlag = NO;
			return;
		}

		if(RxECM_Mode == ECM_ON) {
			/**	ECM受信	*/
			/**	最少電送時間 = 0ms	*/
			RxMinimumScanningTime = SCANNING_TIME0;
		}
		else {
			if(SetRxMinimumCommunicationTime() == NO) {	/**	最少電送時間の確定?	*/
				/**	エラー処理	*/
				FaxCompatibleErrorCode = COMMUNICATE_TIME_ERROR;
				FaxComPerformingFlag = NO;
				return;
			}
		}
		if(SetRxPaperLength() == NO) {	/**	原稿長の確定	*/
/*	#if defined(FRA)		@* del by M.HARADA 95/01/21 *@
			@**	エラー処理	*@
			FaxCompatibleErrorCode = COMMUNICATE_LENGTH_ERROR;
			FaxComPerformingFlag = NO;
			return;
#endif	*/
			return;
		}
	}
	else {
		/**	標準フレームエラー	*/
		FaxCompatibleErrorCode = STANDARD_FRAME_ERROR;
		FaxComPerformingFlag = NO;
	}
	return;
}

/* ここより下、ＭＭＬ専用 */
#if (PRO_MAKER == MML)
/*************************************************************
	module		:[受信時の独自機能確定（村田仕様）]
	function	:[
		NSSを解析し独自機能を確定する
		1.メモリ受信時に必要なパラメータを仮設定
		2.FIP受信時の処理
		3.受信フレームの取り込み
		4.TSI 取り込み(標準機能)
		5.ECM 受信確定(標準機能)
		6.ジャンクメイル防止IDチェック
		7.MSE 方式確定
		8.カナID 取り込み
		9.受領証送信設定
		10.短縮ハンドシェーク設定確認
		11.中継同報機能確認(中継機としての機能は、さつき、ラベンダーはなし)
		12.親展機能確認(ラベンダーＬは、なし)
		13.MML機からのメモリ受信要求の処理(バッファリング受信ありの機種は、バッファリング受信となる)
		14.リモートＦＡＸ受信の処理(親展受信は、リモートＦＡＸ受信にならない)
		15.パスコード確認
		16.中継指示受信の処理
		17.親展受信の処理
		18.代行受信の処理(バッファリング受信ありの機種は、バッファリング受信となる)
		19.後手順短縮ハンドシェークの処理
		20.閉域通信の処理
		21.プリンター受信とメモリ受信の区別（桐は、必ずメモリ受信する）
		22.受信開始をメインタスクへ、メッセージ送信。
	]
	argument	:[]
	return		:[]
	common		:[
				SYS_RxMemoryFileItem			:メモリ受信時の種別（メモリ受信、プリンタ受信の区別にも使用）
				SYS_RxMemoryFileNo
				SYS_RxMemoryFilePage
				SYB_MemoryRxPrintWritePoint
				SYS_RxTotalPage
				FaxComType
				FaxComFIP_RxActiveFlag
				FipFileItem
				FipMailBoxNo
				ID_FrmName
				SYB_TTI_Buffer
				FaxCompatibleErrorCode
				FaxComPerformingFlag
				RxJunkMailFlag
				MakerCodeRxFlag
				MDM_ModemBuffer
				SYB_TTI_ID_Buffer
				NonStdFrmPos
				TxReceiptRequestFlag			:相手機受領証機能フラグ(受信側より送信側の能力をチェック)
				RxSpeedHandshakeFlag
				SYS_RxTotalPage
				SYB_MemoryRxPrint.JournalPoint->:Number
				SYB_MemoryRxPrint.JournalPoint->:RemoteID_TTI
				SYB_MemoryRxPrint.JournalPoint->:Mode
				SYB_MemoryRxPrint.JournalPoint->:StartTime
				SYB_MemoryRxPrint.JournalPoint->:TotalTime
				SYB_MemoryRxPrint.JournalPoint->:DepartmentCode
				SYB_MemoryRxPrint.JournalPoint->:Type
				SYB_MemoryRxPrint.JournalPoint->:Result
				SYB_MemoryRxPrint.JournalPoint->:Kind
				SYB_MemoryRxPrint.JournalPoint->:Option
	]
	keyword		:[FCM]
	condition	:[]
	comment		:[]
	language	:[MS-C Ver.6]
	date		:[1993/11/18]
	author		:[鈴木 郁二]
*************************************************************/
void RxOriginalModeCheck(void)
{
	WORD ex1_pos;
	WORD ex2_pos;
	WORD ex3_pos;
	WORD passcode_pos;
	WORD serch_pos;
	WORD pos;
	/*int memory_pos;*/
	UBYTE i;
	UBYTE j;
	UBYTE junk_mode;
	UWORD	value;	/* 1997/09/14 Y.Murata */
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/11/18 K.Kawata */
	UBYTE data;
#endif
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
	/* ＴＳＩを判断し、その番号にＦＡＸを折り返す特ＲＯＭ (RDC-D83-002) by H.Hirao 1999/04/01 */
	UBYTE is_relay_trans;
 #endif
#else	/**他の機種も特ＲＯＭ対応 1999.4.21 K.Kawata **/
 #if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
	UBYTE is_relay_trans;
 #endif
#endif
	ex1_pos = NO;
	ex2_pos = NO;
	ex3_pos = NO;
	passcode_pos = NO;
	serch_pos = NO;
	pos = 0;
	i = 0;
	j = 0;
	Partner300dpiAbility = NO;
	PartnerEFineAbility = NO;
	junk_mode = CHK_BlockJunkFaxMode();
	value = 0;

#if (PRO_FIP == ENABLE)
	/**	FIP 受信時の処理	*/
	if((SYS_FaxComType == SYS_FIP_CALLED) ||
		((SYS_FaxComType == SYS_MANUAL_RX) && (SYS_FaxComFIP_RxActiveFlag == YES))) {	/**	FIP 受信	*/
		/**	メモリ受信に必要なパラメータを仮設定	*/
		SYS_RxMemoryFileItem = SYS_MEM_FIP_FILE;
		SYS_RxMemoryFileNo = (UWORD)0;
		SYS_RxMemoryFilePage = (UWORD)(SYS_RxTotalPage + 1);
	}
	else if(SYS_FaxComType == SYS_FIP_POLL) {	/**	FIPポーリング	*/
		/**	メモリ受信に必要なパラメータを仮設定	*/
		SYS_RxMemoryFileItem = SYS_MEM_FIP_FILE;
		SYS_RxMemoryFileNo = SYS_FIP_MailBoxNo;
		SYS_RxMemoryFilePage = (UWORD)(SYS_RxTotalPage + 1);
	}
#endif
	/**	フレーム取り込み	*/
	GetMultiFrameLine();

	if((ID_FrmName != NO) && (StandardID[0] == NULL)) {	/**	TSI 受信	*/
		/**	ID 取り込み	*/
		GetPartnerID();
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/11/18 K.Kawata */
	data = 0;
	i = 0;
	j = (UBYTE)(RxID_FrameByteCount - 1);
	for (; ((i < (SYS_ID_MAX - 1) && (j >= START_HDLC_FIF_POS))); j--) {
		data = MDM_ModemBuffer[ID_FrmPos][j];
		if (((data >= '0') && (data <= '9')) || (data == '+') || (data == '*') || (data == '#')) {
			CL1_TSI_SaveStandardID[i] = data;
			i++;
		}
	}
	CL1_TSI_SaveStandardID[i] = NULL;
#endif
	}
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/11/18 K.Kawata */
	else {
		CL1_TSI_SaveStandardID[0] = NULL;	/* 1999/11/18 K.Kawata */
	}
#endif
#if (PRO_F_CODE == ENABLE)
	GetF_CODE_ID();		/* ここに入れた場合最初のコンパチでしか取ってこない 1997/01/13	By T.Yamaguchi */
#endif

	if(SetRxECM_Mode() == NO) {	/**	ECM 受信確定?	*/
		/**	エラー処理	*/
		SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
		FaxCompatibleErrorCode = COMMUNICATE_ECM_ERROR;
		FaxComPerformingFlag = NO;
		return;
	}

	/**	ジャンクメイル防止	*/
/*	if((SYS_FaxComType == SYS_AUTO_CALLED) && (CHK_BlockJunkFaxON())) {	/@@	自動受信でかつジャンクメイル防止機能ON	*/
	if((SYS_FaxComType == SYS_AUTO_CALLED) && (junk_mode != (UBYTE)BLOCK_JUNK_FAX_OFF)) {/**	自動受信でかつジャンクメイル防止機能ON	*/

		value = FCM_CompJunkFax((UWORD)ID_FrmName, &StandardID[0]);

#if 0
//		if(ID_FrmName == NO) {	/**	TSI 受信せず	*/
//			if ((junk_mode != (UBYTE)BLOCK_JUNK_FAX_MODE2)
//			 && (!CHK_UNI_JunkMode2_Rx_No_TSI())) {		/* 1997/10/18  By T.Yamaguchi */
#endif
		if (value == 1) {		/**	TSI 受信せずｴﾗｰ	*/
			/* ＭＯＤＥ２の時は、ＴＳＩがこない場合は受信する */
			/**	エラー処理	*/
			SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
			FaxCompatibleErrorCode = BLOCKJUNKFAX_NO_ID_ERROR;
			FaxComPerformingFlag = NO;
			/**	ジャンクメイルフラグON	*/
			RxJunkMailFlag = YES;
			return;
		}
#if 0
//		else if(StandardID[0] == NULL) {	/**	標準IDなし(受信したがスペースだった）	*/
//			if ((junk_mode != (UBYTE)BLOCK_JUNK_FAX_MODE2)
//			 && (!CHK_UNI_JunkMode2_Rx_No_TSI())) {	/* 1997/10/18  By T.Yamaguchi */
#endif
		else if (value == 2) {		/**	標準IDなし(受信したがスペースだった）ｴﾗｰ	*/
			/* ＭＯＤＥ２の時は、ＴＳＩがこない場合は受信する */
			/**	エラー処理	*/
			SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
			FaxCompatibleErrorCode = BLOCKJUNKFAX_ID_SPACE_ERROR;
			FaxComPerformingFlag = NO;
			/**	ジャンクメイルフラグON	*/
			RxJunkMailFlag = YES;
			return;
		}
#if 0
// /*		else if (RxCheckOwnDialAndID() == NO) {	/@@	TSIと自機NOのチェック	*/
//		else if ((RxCheckOwnDialAndID(&StandardID[0]) == NO) || (RxCheckJunkDialAndID(&StandardID[0]) == NO )) {	/**	TSIと自機NOのチェック	*/
#endif
		else if (value == 3) {		/**	TSIと自機NOのチェックｴﾗｰ	*/
			/**	エラー処理	*/
			SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
			FaxCompatibleErrorCode = BLOCKJUNKFAX_ERROR;
			FaxComPerformingFlag = NO;
			/**	ジャンクメイルフラグON	*/
			RxJunkMailFlag = YES;
			return;
		}
		else {
			/* Nothing */
			/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止OK or ﾀﾞｲﾚｸﾄﾒｰﾙ防止設定でない */
		}
	}
	if(MakerCodeRxFlag == YES) {	/**	MML機である	*/
		/*	MSE モード確定
		SetRxMSE_Mode();14.May'94 移動 Y.Suzuki
		------------------*/
		/* 局名表示フィールド解析 */
		ex1_pos = CheckPartnerTTI_Func(7);

		if(CheckPartnerRCR_Func() == YES) {	/**	相手機受領証機能あり	*/
			/**	受領証送信フラグ ON	*/
			TxReceiptRequestFlag = YES;
		}
		else {
			/**	受領証送信フラグ OFF	*/
			TxReceiptRequestFlag = NO;
		}
		if(MDM_ModemBuffer[NonStdFrmPos][6] & SCFR_MODE_BIT) {	/**	NSS FIF 短縮ハンドシェークSDCSフラグ ON	*/
			SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
		}
		else {
			/**	短縮ハンドシェークフラグ OFF	*/
			RxSpeedHandshakeFlag = NO;
		}
	}
	if((MakerCodeRxFlag == YES) && (ex1_pos != NO)) {	/**	MML機でかつ拡張フィールド1 有り */
		/* NSS リード用ポインター インクリメント	*/

		pos = ex1_pos + 1;
		if(MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & MEMORY_OK_BIT) {	/**	メモリ残量フィールド ON	*/
			/**	NSS リード用ポインター +3	*/
			pos = pos + 3;
		}

		if(CheckPartnerRelayBroadCastFunc(ex1_pos) == YES) {	/**	相手機中継同報指示あり	*/
#if (PRO_FIP == ENABLE)
			SYS_FaxComFIP_RxActiveFlag = NO;
			SYS_FaxComType = SYS_AUTO_CALLED;
#endif
			/*if(CTRY_RelayTx()) ﾌｧｲﾙ名が間違ってた 26.Apr'95 Y.Suzuki */
			if(CTRY_RelayedTx()) {	/**	中継配信の機能がある	*/
#if (PRO_RELAY_BROADCAST == ENABLE)
				SYS_RxMemoryFileItem = SYS_MEM_TX_FILE;
				serch_pos = pos;
				if(MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & EXPAND_FIELD_BIT) {	/**	拡張フィールド2あり	*/
					/**	拡張フィールド2のリードポインターセット	*/
					ex2_pos = pos + 4;
				}
				pos = pos + 4;
#endif
			}
			else {				/* ここできってもよいのか要確認	 96/06/18 By T.Yamaguchi */
				/**	エラー処理	*/
				SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
				FaxCompatibleErrorCode = RELAYED_RX_FUNCTION_ERROR;
				FaxComPerformingFlag = NO;
				return;
			}
		}
		else if ((CheckPartnerSecureMailFunc(ex1_pos) == YES) && CTRY_SecureRx()/* 21.Feb'94 Y.Suzuki */){		/**	相手機親展送信指示	*/
			SYS_RxMemoryFileItem = SYS_MEM_SECURE_RX_FILE;
			serch_pos = pos;
			if(MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & EXPAND_FIELD_BIT) {	/**	拡張フィールド2あり	*/
				/**	拡張フィールド2のリードポインターセット	*/
				ex2_pos = pos + 2;
			}
			pos = pos + 2;
		}
		if (CheckPartnerPassCodeSetting(ex1_pos) == YES) {		/**	相手機パスコード登録済み	*/
			passcode_pos = pos;
			if(MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & EXPAND_FIELD_BIT) {	/**	拡張フィールド2あり	*/
				/**	拡張フィールド2のリードポインターセット	*/
				ex2_pos = pos + 4;
			}
		}
		pos = ex2_pos + 1;				/* 96/06/15 By T.Yamaguchi */
		if(ex2_pos != 0) {
			if(((MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MASK_MEMORY_MODE) != NO_IN_MEMORY_BIT) && (SYS_RxMemoryFileItem == NULL)) {	/**	メモリ蓄積ビット ON	*/
			/* NSSのメモリビットがONなら、メモリ受信(さつき、紅葉)またはバッファリング受信(ラベンダ) */
				/** Memory Rx SetUp */
				/*11.May'94 Y.Suzuki */
				SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;

				if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & EXPAND_FIELD_BIT) {	/**	拡張フィールド3あり	*/
					ex3_pos = pos + 3;
				}
			}
			/** 後手順短縮ハンドシェーク */
			if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & POST_MSG_SPEED_BIT)	{
				if(CHK_UNI_PostSpeedHandshake()) {
					/* フラグセット */
					PostSpeedHandshakeFlag = YES;
				}
			}
			if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & TX300DPI_BIT)	{
				/* フラグセット */
				Partner300dpiAbility = YES;
				SYB_T30_RxFrame300dpiFlag = YES;		/** T30モニタにHｰFine(R12*15.4l/mm)表示に使用 */
			}
			else {
				Partner300dpiAbility = NO;
			}
			if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & EXPAND_FIELD_BIT) {	/**	拡張フィールド3あり	*/
				if((MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MASK_MEMORY_MODE) != NO_IN_MEMORY_BIT) {	/**	メモリ蓄積ビット ON	*/
					ex3_pos = pos + 3;
				}
				else {
					ex3_pos = pos;
				}
			}
			if(ex3_pos != 0) {
				if(MDM_ModemBuffer[NonStdFrmPos][ex3_pos] & EFINE_MODE_BIT)	{
					/* フラグセット */
					PartnerEFineAbility = YES;
/*					SYB_T30_RxFrame300dpiFlag = YES;		/@@ T30モニタにHｰFine(R12*15.4l/mm)表示に使用 */
				}
				else {
					PartnerEFineAbility = NO;
				}
#if (PRO_CIPHER == ENABLE)
				if (ScrambleOn) { /* 暗号化通信機能ありなら 1997/12/08  By T.Yamaguchi */
					if(MDM_ModemBuffer[NonStdFrmPos][ex3_pos] & CIPHER_COM_BIT)	{
						SYS_RxMemoryFileItem = SYS_MEM_CIPHER_RX_FILE;
					}
				}
#endif
			}
		}
	}
#if (PRO_RELAY_BROADCAST == ENABLE)
 #if (PRO_TSI_RELAY_COM == ENABLE)
	else if((MakerCodeRxFlag == NO) && (StandardID[0] != NULL) && (TSI_Relay == 1)) {
		/*-----------------------------------------*/
		/* TSI による中々継指示 14.Feb'95 Y.Suzuki */
		/*-----------------------------------------*/
		if((StandardID[0] == '0') && (StandardID[1] == '0') && (StandardID[2] == '0')) {
  #if (PRO_FIP == ENABLE)
			SYS_FaxComFIP_RxActiveFlag = NO;
			SYS_FaxComType = SYS_AUTO_CALLED;
  #endif
			/*if(CTRY_RelayTx()) ﾌｧｲﾙ名が間違ってた 26.Apr'95 Y.Suzuki	*/
			if(CTRY_RelayedTx()) {	/**	中継配信の機能がある	*/
				SYS_RxMemoryFileItem = SYS_MEM_TX_FILE;
			}
			else {
				/**	エラー処理	*/
				SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
				FaxCompatibleErrorCode = RELAYED_RX_FUNCTION_ERROR;
				FaxComPerformingFlag = NO;
				return;
			}
		}
	}
 #endif
#endif
#if (PRO_CIPHER == ENABLE)
	/* 暗号化受信能力有りでＥＣＭオフ設定の時、ＥＣＭで受信させる処理のため上で見ていた
	** もう一回呼ぶ 1997/10/01
	*/
	/* 暗号化受信能力ありの場合は、ECMｵﾌ設定でもECMで暗号化を受信可能 1997/10/01  By T.Yamaguchi */
	if (RxECM_Mode == ECM_OFF) {	/* 1997/12/08  By T.Yamaguchi */
		if(SetCipherRxECM_Mode() == NO) {	/**	ECM 受信確定?	*/
			/**	エラー処理	*/
			SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
			FaxCompatibleErrorCode = COMMUNICATE_ECM_ERROR;
			FaxComPerformingFlag = NO;
			return;
		}
	}
#endif
	/******************************
	** サブアドレス通信をチェック		注．マルチｻﾌﾞｱﾄﾞﾚｽ通信の場合はここに持って来てはまずい
	******************************/
#if (PRO_F_CODE == ENABLE)
	if (CheckRxF_CODE() == NO) {
		SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
		FaxCompatibleErrorCode = COMMUNICATE_FCODE_RX_ERROR;
		FaxComPerformingFlag = NO;
		return;
	}
	if ( SUB_BitEnable != 0) {
		SYS_RxMemoryFileItem = SYS_MEM_SUB_BULLETIN_FILE;	/* 取り敢えず掲示板をセット */
	}
#endif

	if((RemoteFaxON_Flag == YES) && ((SYS_RxMemoryFileItem == SYS_MEM_RX_FILE) || (SYS_RxMemoryFileItem == NULL)
		|| (SYS_RxMemoryFileItem == SYS_MEM_BUFFERING_RX_FILE))) {	/**	リモートＦＡＸ取り出しあり	*/
		/*	中継指示受信、親展受信がセットアップされていたらリモートFAX受信しない 18.May'94 Y.Suzuki	*/
		/* バッファリング受信の場合もリモートFAX受信する QAT SATUKI_H 940706 7.Jly'94 Y.Suzuki */
		/**	メモリ受信ファイルアイテムセット	*/
		if (SetUpRemoteFaxRx() == NO) {/**	同時プリントあり && 代行受信用バッファがフル	*/
			FaxCompatibleErrorCode = MEMORY_CAPACITY_ERROR;
			FaxComPerformingFlag = NO;
			return;
		}
	}
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
	is_relay_trans = FALSE;
	if (ROM_SW_SpecialRelayTrans) {
	/* ＴＳＩを判断し、その番号にＦＡＸを折り返す特ＲＯＭ (RDC-D83-002) by H.Hirao 1999/04/01 */
		if (SYS_RxMemoryFileItem == NULL || SYS_RxMemoryFileItem == SYS_MEM_RX_FILE) {
			if (CHK_UNI_TSI_RelayTrans()) {
				if (CHK_UNI_TSI_MurataRelayTrans()) {	/* 村田以外のメーカで折り返ししない */
					if (MakerCodeRxFlag == YES) {
						is_relay_trans = TRUE;
						SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
					}
				}
				else {	/* 村田以外のメーカで折り返しする */
					is_relay_trans = TRUE;
					SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
				}
			}
		}
	}
 #endif
#else	/**他の機種も特ＲＯＭ対応 1999.4.21 K.Kawata **/
 #if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
	is_relay_trans = FALSE;
	if (ROM_Switch[ROM_SW_SPECIAL_RELAY_TRANS]) {
		if (SYS_RxMemoryFileItem == NULL || SYS_RxMemoryFileItem == SYS_MEM_RX_FILE) {
			if (CHK_UNI_TSI_MurataRelayTrans()) {	/* 村田以外のメーカで折り返しする */
				is_relay_trans = TRUE;
				SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
			}
			else {	/* 村田以外のメーカで折り返ししない */
				if (MakerCodeRxFlag == YES) {
					is_relay_trans = TRUE;
					SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
				}
			}
		}
	}
 #endif
#endif
	/*	代行受信の処理	*/
	if(SYS_RxMemoryFileItem == NULL) {
#if(PRO_MEM_RX_REJECT == DISABLE)
  #if (PRO_PRINTER_RX == ENABLE)
	/*
	** ワープ機能が有効で、ワープ時間内の場合もメモリ受信する
	** セキュリティー受信モードの時もメモリ受信する
	** by H.Hirao 1998/12/16
	*/
	#if (PRO_RX_DOC_TRANSFER == ENABLE)
	 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
		if ((CHK_WarpFunctionON() || CHK_ND_WarpON()) && CheckWarpRx()) {
	 #else
		if (CHK_WarpFunctionON() && CheckWarpRx()) {
	 #endif
			SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
		}
	#endif
	#if (PRO_SECURITY_RX == ENABLE)
		if (SYB_SecurityRxModeFlag == 1) {/** セキュリティ受信モード中 */
			SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
		}
	#endif
		/*
		** プリンタ受信 or メモリ受信を決定
		** by H.Hirao 1998/12/24
		*/
		if (SYS_RxMemoryFileItem == NULL) {
			switch (QueryReceiveType()) {
			case MEMORY_RX:
				SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
				break;
			case PRINTER_RX:
				break;
			case SUBSTITUTE_PRINTER_ERROR:
				FaxCompatibleErrorCode = SUBSTITUTE_PRINTER_ERROR;
				FaxComPerformingFlag = NO;
				return;
			case PRINTER_ERROR:
				FaxCompatibleErrorCode = PRINTER_ERROR;
				FaxComPerformingFlag = NO;
				return;
			default:
				break;
			}
  #else
    #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/25 K.Kawata*/
		if (QueryWarpAndSecurityDisable() == FALSE) {	/* ワープ機能が有効でワープ時間内とセキュリティー受信モードの時もメモリ受信する */
			SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
		}
		if (SYS_RxMemoryFileItem == NULL) {	/* プリンタ受信 or メモリ受信を決定 */
			switch (QueryReceiveType()) {
			case MEMORY_RX:
				SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
				break;
			case PRINTER_RX:
				SYS_RxMemoryFileItem = NULL;
				break;
			case PRINTER_ERROR:
				FaxCompatibleErrorCode = PRINTER_ERROR;
				FaxComPerformingFlag = NO;
				return;
			default:
				break;
			}
    #else
		if ((CMN_CheckFaxComPrinterError() == TRUE) || (CMN_CheckFaxComPrinterEnable() != TRUE)
			|| (CHK_PrinterRxON() == 0)) {
			/* 強制プリンタ受信/メモリ受信ビット追加 QAT SATUKI_H 940706 13.Jly'94 Y.Suzuki */
			/**	プリンタエラーまたは、プリンタビジー	*/
			/** Memory Rx SetUp */
			/*13.Jly'94 Y.Suzuki */
			SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
    #endif
  #endif
#else /* 紅葉で且つメモリ受信拒否設定（沖電気仕様）の場合 17.Oct'94 Y.Suzuki */
		if (CHK_MemoryReceiveReject() != NO) {/* メモリ受信不可 紅葉で且つメモリ受信拒否設定（沖電気仕様）メモリスイッチは削除されたので注意 */
			if ((CMN_CheckFaxComPrinterError() == TRUE) || (CMN_CheckFaxComPrinterEnable() != TRUE)) {/* プリンタエラー */
				FaxCompatibleErrorCode = PRINTER_ERROR;/*	代行受信できてもしない。	*/
				FaxComPerformingFlag = NO;
				return;
			}
			/** プリンタ受信セットアップ */
		}
		else {/* プリンタ受信、メモリ受信どちらもＯＫ */
			if ((CMN_CheckFaxComPrinterError() == TRUE) || (CMN_CheckFaxComPrinterEnable() != TRUE)
			/*	|| (!CHK_PreferPrinterToScanner() && !CMN_CheckScanEnable())) {	プリンタエラーまたは、プリンタビジーまたは、 スキャナー優先かつスキャナ使用中	*/
				/* ↑↑↑このスイッチを↓↓のスイッチに変更 16.Feb'95 Y.Suzuki */
				|| (CHK_MemoryReceiveType() != 0)) {	/**	プリンタエラーまたは、プリンタビジーまたは、全メモリ受信ON このMEMスイッチはない */
				/** メモリ受信セットアップ */
				SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
			}
			/** プリンタ受信セットアップ */
#endif
		}
	}

#if(PRO_MEMORY_RX == DISABLE)
	/* メモリプリント中のバッファリング受信、メモリ受信は不可 ラベンダ、さつき QAT SATUKI_H 940706 13.Jly'94 Y.Suzuki */
	if((SYS_RxMemoryFileItem != NULL) && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)) {
		SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
		FaxCompatibleErrorCode = MEMORY_RX_REQUEST_ERROR;/*	メモリプリント中にメモリ受信要求ありエラー	*/
		FaxComPerformingFlag = NO;
		return;
	}
#endif
	switch (SYS_RxMemoryFileItem) {		/**	受信タイプ別処理	*/
		case SYS_MEM_TX_FILE:	/**	中継指示受信	*/
#if (PRO_RELAY_BROADCAST == ENABLE)
			switch (SetUpRelayBroadCastRx(serch_pos)) {		/**	中継指示受信セットアップ	*/
				case SYS_RELAY_RX:	/**	セットアップ完了	*/
					break;
				case YES:	/**	メモリ受信のみ	*/
					/**	受信ファイルitemセット	*/
					SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;/* 通信で使用中にしたプリンタを開放するため */
					if(SetUpMemoryRx() == NO) {/**	空きがなければ、エラー処理	*/
						FaxCompatibleErrorCode = SUBSTITUTE_PRINTER_ERROR/*	代行受信バッファフルエラー	*/;
						FaxComPerformingFlag = NO;
						return;
					}
					break;
							/*------------------------------------------------------*/
				case TSI_NG:/** 中継配信不達通知ON 設定、TSI 不良 9.Feb'95 Y.Suzuki */
							/*------------------------------------------------------*/
					SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
					FaxCompatibleErrorCode = RELAYED_RX_TSI_ERROR;
					FaxComPerformingFlag = NO;
					return;
				case NO:	/**	コマンドファイルフルまたは、プリントバッファフル	*/
				default:
					/**	エラー処理	*/
					SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
					FaxCompatibleErrorCode = RELAYED_RX_COMMAND_ERROR;
					FaxComPerformingFlag = NO;
					return;
			}
#endif
			break;
		case SYS_MEM_SECURE_RX_FILE:	/**	親展受信	*/
			if (SetUpSecureMailRx(serch_pos) == NO) {		/**	親展受信セットアップ不可	*/
				/**	エラー処理	*/
				SYS_RxMemoryFileItem = NULL;/* 通信で使用中にしたプリンタを開放するため */

				if (FaxCompatibleErrorCode == 0) {	/* 1997/10/20 SYS_MAILBOX_RCV_TO_RECEVING */
					FaxCompatibleErrorCode = SECURE_MAILBOX_ERROR;
				}

				FaxComPerformingFlag = NO;
				return;
			}
			break;
#if (PRO_FIP == ENABLE)
		case SYS_MEM_FIP_FILE:	/** FIP受信の時はMailBox=0に上書き受信される	*/
				MEM_ClearDocAndFATArea(SYS_MEM_FIP_FILE,(UWORD)0, MEM_IGNORE_BOX_NUMBER);
				break;
#endif
		case SYS_MEM_RX_FILE:	/**	通常のメモリ受信	*/
			if(SetUpMemoryRx() == NO) {/**	空きがなければ、エラー処理	*/
				FaxCompatibleErrorCode = SUBSTITUTE_PRINTER_ERROR/*	代行受信バッファフルエラー	*/;
				FaxComPerformingFlag = NO;
				return;
			}
 /* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
			/* ＴＳＩを判断し、その番号にＦＡＸを折り返す特ＲＯＭ (RDC-D83-002) by H.Hirao 1999/04/01 */
			if (ROM_SW_SpecialRelayTrans && is_relay_trans) {
				SetUpSpecialReplayTrans();
			}
			else
 #endif
#else	/**他の機種も特ＲＯＭ対応 1999.4.21 K.Kawata **/
 #if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
			if (ROM_Switch[ROM_SW_SPECIAL_RELAY_TRANS] && is_relay_trans) {
				SetUpSpecialReplayTrans();
			}
			else
 #endif
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE) /* ワープ機能 By H.Hirao 1998/08/31 */
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
			/* 
			** 受領証を受信時にコマンドファイルをセット中のままほったらかしにし
			** インデックスも送信原稿として登録されてしまう不具合 by H.Hirao 1999/10/10
			** ported from \src\nagano\src\fcm_rcmp.c by H.Hirao 1999/12/10
			*/
			/* if (CHK_WarpFunctionON() || CHK_ND_WarpON()) { */
			if ((CHK_WarpFunctionON() || CHK_ND_WarpON()) && (FaxComTXorRX_Sign == RX_COM_MODE)) {
 #else
			/* if (CHK_WarpFunctionON()) { */
			if (CHK_WarpFunctionON() && (FaxComTXorRX_Sign == RX_COM_MODE)) {
 #endif
				SetUpWarpRx();
			}
#endif
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/6/24 K.Kawata */
			if (CL1_ExtFunctionEnableFlag == 1) {	/* ｸﾗｽ1拡張が動作中 */
				SYS_RxMemoryFileItem = SYS_MEM_CLASS1_TX_FILE;
				SYS_RxMemoryFileNo = 0;
				SYS_RxMemoryFilePage = 1;
				SYS_MultiProgramFlag = 0;
				CL1_TxMemoryFileItem = SYS_MEM_CLASS1_TX_FILE;
				CL1_TxMemoryFileNo[0] = 0;
				CL1_TxMemoryFilePage = 1;
			}
#endif
			break;
		case SYS_MEM_REMOTE_TX_FILE:	/**	リモートＦＡＸ受信	*/
			break;
#if (PRO_F_CODE == ENABLE)
		case SYS_MEM_SUB_BULLETIN_FILE:
		case SYS_MEM_SUB_SECURE_FILE:
 #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/7/5 K.Kawata */
			if (CL1_ExtFunctionEnableFlag == 1) {	/* ｸﾗｽ1拡張が動作中 */
				SYS_RxMemoryFileItem = SYS_MEM_CLASS1_TX_FILE;
				SYS_RxMemoryFileNo = 0;
				SYS_RxMemoryFilePage = 1;
				SYS_MultiProgramFlag = 0;
				CL1_TxMemoryFileItem = SYS_MEM_CLASS1_TX_FILE;
				CL1_TxMemoryFileNo[0] = 0;
				CL1_TxMemoryFilePage = 1;
			}
			else {
				if (SetUpSubaddressBoxRx() == NO) {
					SYS_RxMemoryFileItem = NULL;/* 通信で使用中にしたプリンタを開放するため */
					FaxComPerformingFlag = NO;
					return;
				}
			}
			break;
 #else
			if (SetUpSubaddressBoxRx() == NO) {
				SYS_RxMemoryFileItem = NULL;/* 通信で使用中にしたプリンタを開放するため */
				FaxComPerformingFlag = NO;
				return;
			}
			break;
 #endif
#endif
#if (PRO_CIPHER == ENABLE)
		case SYS_MEM_CIPHER_RX_FILE:	/* 暗号化受信 */
			if (SetUpCipherRx() == NO) {
				SYS_RxMemoryFileItem = NULL;/* 通信で使用中にしたプリンタを開放するため */
				FaxComPerformingFlag = NO;
			}
			break;
#endif
		default:	/**	プリンタ受信、バッファリング受信	*/
			break;
	}
	if(MakerCodeRxFlag == YES) {
		/**	MSE モード確定	*/
		SetRxMSE_Mode();/* メモリ受信、プリンタ受信が確定してから確定する 18.May'94 Y.Suzuki*/
	}
	if(CHK_ClosedNetworkON() == YES) {		/**	閉域通信ON	*/
		if(MakerCodeRxFlag == YES) {		/**	MML機	*/
			if(passcode_pos != NO) {		/**	送信機パスコードあり	*/
				if(CheckPassCodeMatching(passcode_pos) == NO) {		/**	パスコード不一致	*/
					SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
					FaxCompatibleErrorCode = PASSCODE_ERROR_2;
					FaxComPerformingFlag = NO;
					return;
				}
			}
			else {/**	送信機パスコードなし	*/
				if(CheckPasscodeBuf() == YES) {	/**	受信機パスコードあり	*/
					SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
					FaxCompatibleErrorCode = PASSCODE_ERROR_1;
					FaxComPerformingFlag = NO;
					return;
				}
			}
		}
		else {		/**	他社機	*/
			/**	エラー処理	*/
			SYS_RxMemoryFileItem = NULL;/* メインでプリンタ開放するため */
			FaxCompatibleErrorCode = CLOSED_NETWORK_ERROR;
			FaxComPerformingFlag = NO;
			return;
		}
	}
	/*	SYS_RxMemoryFileItem == NULLならプリンター受信	*/
	if(SYS_RxMemoryFileItem != NULL) {
		/**	メモリ受信実行	*/
		/*SetMemoryRxDocFile();	*/
		SYS_DocBlock.Index.Item	 = SYS_RxMemoryFileItem;
		SYS_DocBlock.Index.No	 = SYS_RxMemoryFileNo;
		SYS_DocBlock.Index.Page	 = SYS_RxMemoryFilePage;
		SYS_DocBlock.Index.BoxNumber = SYS_RxMemoryFileBoxNumber; /* 1997/01/13  By T.Yamaguchi */
	}
#if (PRO_PRINTER_RX == ENABLE)/* 13.Apr'94 */
	else{/**	プリンタ受信	*/
		PRN_PreOpen();				/**	プリンタプリオープン	*/
		PrinterRxPreOpenFlag = 1;
	}
#endif
	/**	通信の開始を MAN_TSK に知らせる	*/
	MsgFromFaxComToMain.Item = FROM_FAXCOM;
	MsgFromFaxComToMain.Message = MSG_FAXCOM_RX_START;
	snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
	rcv_msg(mbxno.FCM_Task, &FcomMsg);		/* メインよりメッセージ受信 */
	return;
}

/*****************************************************************
	module		:[モード変更時２回目以降のNSS受信時の独自機能確定]
	function	:[
		拡張フレーム２の位置を確定する。
		NSSを解析し独自R12*15.4L/mm送信機能を確定する
					   R12*11.55L/mm痩身機能を確定する
	]
	argument	:[]
	return		:[]
	common		:[]
	keyword		:[FCM]
	condition	:[]
	comment		:[]
	language	:[MS-C Ver.6]
	date		:[1996/05/17]
	author		:[山口 哲治]
******************************************************************/
void OriginalHyperFineModeCheck(void)
{
	WORD ex1_pos;
	WORD ex2_pos;
	WORD ex3_pos;
	WORD pos;

	ex1_pos = NO;
	ex2_pos = NO;
	ex3_pos = NO;
	pos = 0;
	Partner300dpiAbility = NO;
	PartnerEFineAbility = NO;

	GetMultiFrameLine();

	if(MakerCodeRxFlag == YES) {	/**	MML機である	*/
		if(MDM_ModemBuffer[NonStdFrmPos][6] & TTI_ON_BIT) {	/**	NSS 局名表示フィールドON	*/
			if(MDM_ModemBuffer[NonStdFrmPos][6] & EXPAND_FIELD_BIT) {	/**	拡張フィールド1ON	*/
				/**	NSS FIFリード用ポインター 23 をセット	*/
				ex1_pos = 23;
			}
		}
		else if(MDM_ModemBuffer[NonStdFrmPos][6] & EXPAND_FIELD_BIT) {	/**	拡張フィールド1ON	*/
			/**	NSS FIFリード用ポインター 7 をセット	*/
			ex1_pos = 7;
		}
	}
	if((MakerCodeRxFlag == YES) && (ex1_pos != NO)) {	/**	MML機でかつ拡張フィールド1 有り */
		/* NSS リード用ポインター インクリメント	*/
		pos = ex1_pos + 1;
		if(MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & MEMORY_OK_BIT) {	/**	メモリ残量フィールド ON	*/
			/**	NSS リード用ポインター +3	*/
			pos = pos + 3;
		}
		if(CheckPartnerRelayBroadCastFunc(ex1_pos) == YES) {	/**	相手機中継同報指示あり	*/
#if (PRO_RELAY_BROADCAST == ENABLE)
				if(MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & EXPAND_FIELD_BIT) {	/**	拡張フィールド2あり	*/
					/**	拡張フィールド2のリードポインターセット	*/
					ex2_pos = pos + 4;
				}
				pos = pos + 4;
#endif
		}
		else if ((CheckPartnerSecureMailFunc(ex1_pos) == YES) && CTRY_SecureRx()/* 21.Feb'94 Y.Suzuki */){		/**	相手機親展送信指示	*/
			if(MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & EXPAND_FIELD_BIT) {	/**	拡張フィールド2あり	*/
				/**	拡張フィールド2のリードポインターセット	*/
				ex2_pos = pos + 2;
			}
			pos = pos + 2;
		}
		if (CheckPartnerPassCodeSetting(ex1_pos) == YES) {		/**	相手機パスコード登録済み	*/
			if(MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & EXPAND_FIELD_BIT) {	/**	拡張フィールド2あり	*/
				/**	拡張フィールド2のリードポインターセット	*/
				ex2_pos = pos + 4;
			}
		}
		pos = ex2_pos + 1;
		if(ex2_pos != 0) {
			if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & EXPAND_FIELD_BIT) {	/**	拡張フィールド3あり	*/
				if(((MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MASK_MEMORY_MODE) != NO_IN_MEMORY_BIT)) { /** && (SYS_RxMemoryFileItem == NULL)) {	/@	メモリ蓄積ビット ON	*/
					ex3_pos = pos + 3;
				}
				else {
					ex3_pos = pos;
				}
			}
/* #if (PRO_HQ_MODE == ENABLE) 1997/11/21  By T.Yamaguchi */
#if (PRO_CCD == DPI300)
			if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & TX300DPI_BIT)	{
				/* フラグセット */
				Partner300dpiAbility = YES;
				SYB_T30_RxFrame300dpiFlag = YES;		/** T30モニタにHｰFine(R12*15.4l/mm)表示に使用 */
			}
			else {
				Partner300dpiAbility = NO;
			}
			if(ex3_pos != 0) {
				if(MDM_ModemBuffer[NonStdFrmPos][ex3_pos] & EFINE_MODE_BIT)	{
					/* フラグセット */
					PartnerEFineAbility = YES;
/*					SYB_T30_RxFrame300dpiFlag = YES;		/@@ T30モニタにHｰFine(R12*15.4l/mm)表示に使用 */
				}
				else {
					PartnerEFineAbility = NO;
				}
			}
#endif
		}
	}
}

/*************************************************************************
	module		:[受信方式の獲得]
	function	:[
		1.
	]
	return		:[MEMORY_RX					: メモリ受信
				  PRINTER_RX				: プリンタ受信
				  SUBSTITUTE_PRINTER_ERROR	: 代行受信バッファフルエラー
				  PRINTER_ERROR				: プリンタエラー]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH704x]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1998/12/22]
	author		:[H.Hirao]
*************************************************************************/
  #if (PRO_PRINTER_RX == ENABLE)
UBYTE QueryReceiveType (void)
{
	if (SYS_V34ProcedureExecutingFlag) {	/* Ｖ３４の場合 */
		switch (CHK_UNI_V34ReceiveType()) {
		case V34_MRX_TO_PRX:	/* メモリ受信優先 メモリ受信不可の場合、プリンタ受信 */
			if (CMN_CheckMemoryReceiveEnable()) {
				return (MEMORY_RX);
			}
			else {
				if (!CMN_CheckFaxComPrinterError() && CMN_CheckFaxComPrinterEnable()) {
					return (PRINTER_RX);
				}
				else {
					return (SUBSTITUTE_PRINTER_ERROR);
				}
			}
			break;
		case V34_MRX_TO_MRX:	/* 強制メモリ受信 */
			if (CMN_CheckMemoryReceiveEnable()) {
				return (MEMORY_RX);
			}
			else {
				return (SUBSTITUTE_PRINTER_ERROR);
			}
			break;
		case V34_PRX_TO_MRX:	/* プリンタ受信優先 プリンタ受信不可の場合、メモリ受信 */
			if (!CMN_CheckFaxComPrinterError() && CMN_CheckFaxComPrinterEnable()) {
				return (PRINTER_RX);
			}
			else {
				if (CMN_CheckMemoryReceiveEnable()) {
					return (MEMORY_RX);
				}
				else {
					return (PRINTER_ERROR);
				}
			}
			break;
		case V34_PRX_TO_PRX:	/* 強制プリンタ受信 */
			if (!CMN_CheckFaxComPrinterError() && CMN_CheckFaxComPrinterEnable()) {
				return (PRINTER_RX);
			}
			else {
				return (PRINTER_ERROR);
			}
			break;
		default:
			break;
		}
	}
	else {									/* Ｖ１７以下の場合 */
		switch (CHK_UNI_V17ReceiveType()) {
		case V17_MRX_TO_PRX:	/* メモリ受信優先 メモリ受信不可の場合、プリンタ受信 */
			if (CMN_CheckMemoryReceiveEnable()) {
				return (MEMORY_RX);
			}
			else {
				if (!CMN_CheckFaxComPrinterError() && CMN_CheckFaxComPrinterEnable()) {
					return (PRINTER_RX);
				}
				else {
					return (SUBSTITUTE_PRINTER_ERROR);
				}
			}
			break;
		case V17_MRX_TO_MRX:	/* 強制メモリ受信 */
			if (CMN_CheckMemoryReceiveEnable()) {
				return (MEMORY_RX);
			}
			else {
				return (SUBSTITUTE_PRINTER_ERROR);
			}
			break;
		case V17_PRX_TO_MRX:	/* プリンタ受信優先 プリンタ受信不可の場合、メモリ受信 */
			if (!CMN_CheckFaxComPrinterError() && CMN_CheckFaxComPrinterEnable()) {
				return (PRINTER_RX);
			}
			else {
				if (CMN_CheckMemoryReceiveEnable()) {
					return (MEMORY_RX);
				}
				else {
					return (PRINTER_ERROR);
				}
			}
			break;
		case V17_PRX_TO_PRX:	/* 強制プリンタ受信 */
			if (!CMN_CheckFaxComPrinterError() && CMN_CheckFaxComPrinterEnable()) {
				return (PRINTER_RX);
			}
			else {
				return (PRINTER_ERROR);
			}
			break;
		default:
			break;
		}
	}
}
  #endif
  #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/22 K.Kawata*/
UBYTE QueryReceiveType(void)
{
	if (SYS_V34ProcedureExecutingFlag) {	/* Ｖ３４の場合 */
		if (CHK_UNI_V34ReceiveType() == V34_PRX_TO_PRX) {
			if ((PRN_PrintRxErrorHaltREQ() == OK) && CMN_CheckFaxComPrinterEnable()) {
				return (PRINTER_RX);
			}
			return (PRINTER_ERROR);
		}
		return(MEMORY_RX);
	}
	else {									/* Ｖ１７以下の場合 */
		if (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX) {
			if ((PRN_PrintRxErrorHaltREQ() == OK) && CMN_CheckFaxComPrinterEnable()) {
				return (PRINTER_RX);
			}
			return (PRINTER_ERROR);
		}
		return(MEMORY_RX);
	}
}
  #endif
#endif
/* RxOriginalModeCheck(void) よりここまでＭＭＬ専用 */
