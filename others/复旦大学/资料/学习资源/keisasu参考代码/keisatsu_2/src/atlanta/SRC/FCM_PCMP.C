/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_PCMP.C												 */
/*	モジュール	 :															 */
/*				 : TxOriginalPollingModeCheck()								 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : ポーリング時コンパチチェック								 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
/* このファイルは、ＭＭＬ専用です */
#if(PRO_MAKER == MML)

#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\mem_def.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\CTRY_PRO.H"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\MEM_PRO.H"
#include "\src\atlanta\define\uni_pro.h"

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


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[TxOriginalPollingModeCheck()]
	function	:[村田独自機能ポーリング時コンパチチェック
		NSC を解析し独自機能を確定する
		1.受信フレームの取り込み
		2.受領証送信の処理（メモリ送信しない）
		3.ポーリング原稿のチェック
		4.CSI 取り込み(標準機能)
		5.ECM 送信確定(標準機能)
		6.DBポーリングパスコードチェック
		7.MSE 方式確定
		8.カナID 取り込み
		9.メモリ送信チェック
		10.受信原稿ポーリング送信の処理
		11.検索ポーリング時の処理
		12.メモリ送信チェック
		13.ポーリング処理
		14.原稿情報を大域変数にセット
	]
	return		:[なし]
	common		:[
		TxRCR_Flag					:受領証送信フラグ
		TxReceiptRequestFlag		:受領証送信有り
		MakerCodeRxFlag
		TxInterMemoryFlag
		FaxCompatibleErrorCode
		FaxComPerformingFlag
		IDFrmName
		SYB_ID_Buffer
		MDM_ModemBuffer
		NonStdFrmPos
		SYB_TTI_ID_Buffer
		RxReceiptRequestFlag
		FaxComTxType				:ポーリング送信時は、SCANER_TX,またはMEMORY_TXがセットされる。
		TxMemoryFilePage
		SYS_TxTotalPage
		PollingTxType
		TxMemoryFileItem
		TxMemoryFileNo
		PollingTxFilePage
		RxDocumentPollingTxFlag		:受信原稿ポーリング送信タイプ
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/26]
	author		:[鈴木 郁二]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void TxOriginalPollingModeCheck(void)
{
	WORD ex1_pos;
	WORD ex2_pos;
	WORD ex3_pos;
	WORD db_pos;
	WORD memory_pos;
	WORD memory2_bit;
	WORD pos;
	WORD i;
	UBYTE txrcr;
#if (PRO_F_CODE == ENABLE)
	UBYTE select_polling_tx;

	select_polling_tx = NO;
#endif

	ex1_pos = NO;
	ex2_pos = NO;
	ex3_pos = NO;
	db_pos = NO;
	memory_pos = 0;
	pos = 0;
	memory2_bit = NO;
	i = 0;
	txrcr = 0;

	/**	受信フレームの取り込み	*/
	GetMultiFrameLine();
	if ((TxRCR_Flag == YES) && (TxReceiptRequestFlag == YES) && (MakerCodeRxFlag == YES)) {		/**	受領証送信時相手機　Ｆ－５１の場合	*/
		/**	メモリ送信フラグNO 受領証送信	*/
		TxInterMemoryFlag = NO;/* F51対策 0msで出したら受信してくれない */
		txrcr = 1;/* 受領証送信時、コンパチスキップ処理のために使用 */
	}
	SetTxECM_Mode();		/**	ECM モード確定せず	*/
	if(txrcr == 0) {	/* 受領証送信でない */
#if (PRO_F_CODE == ENABLE)
		select_polling_tx = SetTxF_CODE();		/* F_CODE ﾋﾞｯﾄﾁｪｯｸ */
		if (select_polling_tx == YES) {
			GetF_CODE_ID();		/* ここに入れた場合最初のコンパチでしか取ってこない 1997/01/13	By T.Yamaguchi */
		}
#endif
		RxDocumentPollingTxFlag = CheckPollingTxType();
#if (PRO_F_CODE == ENABLE)
		if ((!CheckPollingDocuments()) && (!CheckDatabasePollingData()) && !RxDocumentPollingTxFlag && (select_polling_tx == NO)) {		/**	ポーリング原稿セット済みではない	*/
#else
		if ((!CheckPollingDocuments()) && (!CheckDatabasePollingData()) && !RxDocumentPollingTxFlag) {		/**	ポーリング原稿セット済みではない	*/
#endif
			/**	ポーリング原稿なしエラー T3.1	*/
			TxMemoryFileItem = SYS_MEM_POLLING_FILE;	/* ジャーナル用にセットしておく 1997/08/30  By T.Yamaguchi */
			FaxCompatibleErrorCode = TX_NO_POLLING_DOC_ERROR;
			FaxComPerformingFlag = NO;
			return;
		}
		if ((ID_FrmName != NO) && (StandardID[0] == NULL)) {		/**	CIG 受信	*/
			/**	ID 取り込み	*/
			GetPartnerID();
		}
#if (PRO_F_CODE == ENABLE)
		if ((CheckPasscodeBuf() == YES) && (select_polling_tx == NO)) {	/* 選択ﾎﾟｰﾘﾝｸﾞ送信時は、ﾎﾟｰﾘﾝｸﾞﾊﾟｽﾜｰﾄﾞ無視する */
#else
		if (CheckPasscodeBuf() == YES) {		/**	ＤＢポーリングパスコードあり "0000"以外	*/
#endif
			if (MakerCodeRxFlag == YES) {		/**	MML機	*/
				if (CheckPassCodeMatching(7) == NO) {		/**	パスコード不一致	*/
					/**	ポーリングパスコードエラー	*/
					FaxCompatibleErrorCode = POLLING_PASSCODE_ERROR;
					FaxComPerformingFlag = NO;
					return;
				}
			}
			else {		/**	他社機	*/
				/**	Not 村田エラー	*/
				FaxCompatibleErrorCode = POLLING_NOT_MURATA_ERROR;
				FaxComPerformingFlag = NO;
				return;
			}
		}
	}
	if (MakerCodeRxFlag == YES) {		/**	相手機MML機	*/
		/**	MSE モード確定	*/
		SetTxMSE_Mode();
		if(txrcr == 1) {/* 受領証送信の場合MSE,ECMのみ確定する */
			return;
		}
		/* 局名表示フィールド解析 */
		ex1_pos = CheckPartnerTTI_Func(11);
	}
	if(RxDocumentPollingTxFlag) {	/**	受信原稿ポーリングセットアップ	*/
		if(!SetUpRxDocumentPollingTx()) {	/**	ポーリング原稿エラー T3.1	*/
			TxMemoryFileItem = SYS_MEM_POLLING_FILE;	/* ジャーナル用にセットしておく 1997/08/30  By T.Yamaguchi */
			FaxCompatibleErrorCode = NO_RX_DOC_POLLING_DOC_ERROR;
			FaxComPerformingFlag = NO;
			return;
		}
	}
	/*	拡張フィールド１の解析	*/
	if ((MakerCodeRxFlag == YES) && (ex1_pos != NO)) {		/**	相手機MML機でかつ拡張フィールド1あり	*/

		if (MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & MEMORY_OK_BIT) {		/**	独自フレームメモリビットON	*/
			/**	独自フレームリードポインタセット	*/
			pos = ex1_pos + 4;/* DB Field or ex2_pos */
			/**	メモリ送信フラグ ON	*/
			TxInterMemoryFlag = YES;
			if(FCM_PtnrChk_TxToPrinterRxEnable()) {
				TxInterMemoryFlag = NO;
			}
		}
		else {
			pos = ex1_pos + 1;/* DB Field or ex2_pos  10.Nov'94 */
		}

		if(CTRY_DB_PolingTx() && !RxDocumentPollingTxFlag) {/* 21.Feb'94 Y.Suzuki */
#if(PRO_DB_POLLING_TX == ENABLE)
			if (CheckPartnerDB_PollingFunc(ex1_pos) == YES) {		/**	検索ポーリング要求あり	*/
				db_pos = pos;
				/**	検索ポーリング送信時のメモリファイル設定	*/
				TxMemoryFileItem = SYS_MEM_DB_POLLING_FILE;
				TxMemoryFilePage = SYS_TxTotalPage + 1;
				/**	ローカル変数に検索ポーリングフィールドのリードポインタセット	*/
				pos = GetDatabasePollingFileNumber(db_pos) + 1;
				if (pos == 1) {		/**	要求されたファイルが蓄積されていない	*/
					/**	データーベースポーリング原稿エラー	*/
					FaxCompatibleErrorCode = NO_DB_POLLING_DOC_ERROR;
					FaxComPerformingFlag = NO;
					return;
				}
			}
#endif
		}
		if (MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & EXPAND_FIELD_BIT) {		/**	独自フレーム拡張フィールド2ON	*/
			ex2_pos = pos;
			if((MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MASK_MEMORY_MODE) != NO_IN_MEMORY_BIT) {		/**	メモリ残量フィールドON	*/
				memory2_bit = YES;
#if(PRO_MEM_RX_REJECT == ENABLE)/* ﾓﾐｼﾞ 95/4/28 Y.Suzuki */
				if((MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MASK_MEMORY_MODE) == MMR_IN_MEMORY_BIT) {		/**	メモリ残量フィールドON	*/
#else/* ﾗﾍﾞﾝﾀﾞ、ｻﾂｷ */
				if((MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MASK_MEMORY_MODE) == MR_IN_MEMORY_BIT) {/**	MR 蓄積ならメモリ残量チェックする */
#endif
					/**	メモリ送信フラグ ON	*/
					/* 受信機のメモリ容量と送信原稿のメモリサイズを比較 */
					pos++;
					memory_pos = pos;
					TxInterMemoryFlag = YES;/* 取り敢えずﾒﾓﾘ送信ONする */
					/*----- ここではまだSYS_Docblock がｾｯﾄされてない !! 95/4/27 Y.Suzuki
					if(CheckTxMemorySize(memory_pos) == YES) {
						TxInterMemoryFlag = YES;
					}
					-------------------------------------------------*/
					/*	以下の二つの条件で相手機F50を判断	*/
					if ((MDM_ModemBuffer[NonStdFrmPos][6] & MSE2_MODE_BIT) &&
					(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MR_IN_MEMORY_BIT)) {		/**	相手機Ｆー５０	*/
						/**	メモリ送信フラグ OFF	*/
						TxInterMemoryFlag = NO;
					}
					if(FCM_PtnrChk_TxToPrinterRxEnable()) {
						TxInterMemoryFlag = NO;
					}
				}
			}
			/** 後手順短縮ハンドシェーク */
			if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & POST_MSG_SPEED_BIT)	{
				if(CHK_UNI_PostSpeedHandshake()) {
					/* フラグセット */
					PostSpeedHandshakeFlag = YES;
				}
			}
#if (PRO_CCD == DPI300)
			if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & TX300DPI_BIT)	{
				/* フラグセット */
				Partner300dpiAbility = YES;
				SYB_T30_RxFrame300dpiFlag = YES;		/** T30モニタにHｰFine(R12*15.4l/mm)表示に使用 */
			}
			else {
				Partner300dpiAbility = NO;
			}
#endif
			if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & EXPAND_FIELD_BIT) {	/**	NSF 拡張フィールド3 ON	*/
				if(memory2_bit != NO) {	/**	メモリ残量ﾌｨｰﾙﾄﾞ２あり	*/
					/**	NSF リード用ポインター セット	*/
					ex3_pos = ex2_pos + 4;
				}
				else {
					/**	NSF リード用ポインター セット	*/
					ex3_pos = ex2_pos + 1;
				}
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
				if (SpeedModeChangeRomCheck() == TRUE) {
					if(MDM_ModemBuffer[NonStdFrmPos][ex3_pos] & SPEED_MODE_CHANGE_BIT) {
						PartnerSpeedModeChangeAbility = YES;
					}
					else {
						PartnerSpeedModeChangeAbility = NO;
					}
				}
#endif
				/* if (	  ) {ﾒﾓﾘｽｲｯﾁを追加すること */
					if(MDM_ModemBuffer[NonStdFrmPos][ex3_pos] & EFINE_MODE_BIT) {
						PartnerEFineAbility = YES;
					}
					else {
						PartnerEFineAbility = NO;
					}
				/* } */
			}
		}
	}
#if (PRO_F_CODE == ENABLE)
	if ((db_pos == NO) && !RxDocumentPollingTxFlag && (select_polling_tx == NO)) {		/**	検索ポーリング送信ではない？	*/
#else
	if ((db_pos == NO) && !RxDocumentPollingTxFlag) {		/**	検索ポーリング送信ではない？	*/
#endif

#if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/01/30 */
			/* 1997/01/30
			 * マルチ回線でポーリング送信と検索ポーリング送信が重なった場合
			 * ステータスはポーリング原稿なしにしてガードしているがメモリには
			 * ポーリング原稿はある
			 * 再度ポーリング送信可能か否かのチェックをする
			*/
			if (!CheckPollingDocuments()) {
				FaxCompatibleErrorCode = TX_NO_POLLING_DOC_ERROR;
				FaxComPerformingFlag = NO;
				return;
			}
#endif
		if (PollingTxType == SYS_MEMORY_TRANSMIT)	{	/**	1996/11/28	By T.Yamaguchi */
			/**	メモリファイル設定 アイテム、ファイルNO、ページNO	*/
			TxMemoryFileItem = SYS_MEM_POLLING_FILE;
			TxMemoryFileNo[0] = 0;
			TxMemoryFileNo[1] = 0xFFFF;
			TxMemoryFilePage = SYS_TxTotalPage + 1;
			/**	ポーリング送信ページ数セット	*/
			PollingTxFilePage[0] = MEM_CountTotalPage(SYS_MEM_POLLING_FILE, 0, MEM_IGNORE_BOX_NUMBER);
			if (PollingTxFilePage[0] == MEM_NO_INDEX) { /* add by T.Yamaguchi 1997/08/30 */
				/**	ポーリング原稿なしエラー T3.1	*/
				FaxCompatibleErrorCode = TX_NO_POLLING_DOC_ERROR;
				FaxComPerformingFlag = NO;
				return;
			}
			PollingTxFilePage[1] = 0xFFFF;
			/**	交信種別 メモリ送信	*/
			SYS_FaxComTxType = SYS_MEMORY_TRANSMIT;		/* 1996/11/28  By T.Yamaguchi */
		}
		else {		/**	メモリ送信ではない	*/
			/**	交信種別 スキャナポーリング送信	*/
			SYS_FaxComTxType = SYS_SCANNER_TRANSMIT;
		}
	}
#if (PRO_F_CODE == ENABLE)
	if (select_polling_tx == YES) {	/* 選択ポーリング送信の場合 */
		if (SetUpSubaddressBoxPollingTx() == NO) {
			FaxComPerformingFlag = NO;
			return;
		}
		/**	交信種別 メモリ送信	*/
		SYS_FaxComTxType = SYS_MEMORY_TRANSMIT;
		PollingTxType = SYS_MEMORY_TRANSMIT;
		TxMemoryFilePage = SYS_TxTotalPage + 1;
	}
#endif
	/**	大域変数に原稿の情報をセット	*/
	GetFirstTxDocumentData();
	/* 上から移動 95/4/27 Y.Suzuki ----------------------*/
	if(memory_pos != 0) {/* MakerCode ON && Memory_Bit ON */
		if(CheckTxMemorySize(memory_pos) != YES) {
			TxInterMemoryFlag = NO;
		}
	}
}

/* このファイルは、ＭＭＬ専用 */
#endif
