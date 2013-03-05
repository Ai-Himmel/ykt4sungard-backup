/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_TCMP.C												 */
/*	モジュール	 :															 */
/*				 : TxCompatibleCheck()										 */
/*				 : TxOriginalModeCheck()									 */
/*	作成者		 : 山口														 */
/*	日	付		 :															 */
/*	概	要		 : 送信側コンパチチェック									 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\CTRY_PRO.H"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\STNG_PRO.H"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\sh7043\define\io_pro.h"

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

#if (PRO_FIP == ENABLE)
/* #include "\src\atlanta\ext_v\fip_data.h" By M.Tachibana */
#endif
/* #if(PRO_HQ_MODE == ENABLE) */ /* 高画質モードあり */
 #include "\src\atlanta\define\SCN_PRO.H"
/* #endif */
#if (PRO_PRINTER_RX == ENABLE)
 #include "\src\atlanta\define\unisw_c.h"
#endif

#if defined (KEISATSU) /* 警察FAX 05/09/08 石橋正和 */
#include "\src\atlanta\define\s1_def.h"
#endif


/*************************************************************
	module		:[TxCompatibleCheck()]
	function	:[T30標準機能
		1.２ページ目の場合(EOM 送信後のハンドシェーク)、フレーム取り込み
		2.DIS/DTC受信の場合、各標準機能の確定を行う
			トレーニングボーレート
			送信符号化方式
			送信モード
			送信原稿幅
			最少電送時間(ECM送信の場合0ms)
			原稿長
		3.モード表示用フラグセット(オペレーション担当者と相談要　野瀬)
	]
	return		:[]
	common		:[
					SYS_TxTotalPage
					FaxCompatibleErrorCode
					FaxComPerformingFlag
					FaxTxMaxLength
					***DisplyFirstMode***
					StdFrmName
	]
]	condition	:[]
	comment		:[
		修正履歴
		94/10/19 KIRIのみスキャナ送信時別処理 Y.Suzuki
	]
	keyword		:[FCM]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	date		:[1993/11/16]
	author		:[鈴木 郁二]
*************************************************************/
void TxCompatibleCheck(void)
{
	/*	マルチフレームの取り込み	*/
	GetMultiFrameLine();/* Test Test 23.Jan'95 Y.Suzuki */
#if defined(DEU) || defined(EC1)	/* add by M.H '97/03/21 FIFが00 00 00のDIS、DTCを受信した場合回線断する。*/
									/* add by M.H '97/04/16 for ITA */
	if((StdFrmName == DIS_F) || (StdFrmName == DTC_F)){
		if ((MDM_ModemBuffer[StdFrmPos][3] == 0) &&
			(MDM_ModemBuffer[StdFrmPos][4] == 0) &&
			(MDM_ModemBuffer[StdFrmPos][5] == 0)){
				FaxCompatibleErrorCode = RECEIVE_INCRRECT_DIS;
				FaxComPerformingFlag = NO;
				return;
		}
	}
#endif
#if defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/15 */
					/* FIFが00 00 00のDIS、DTCを受信した場合回線断する。*/
	if (CHK_ForeignApprovalDEU()) {		/* DEU bitがOnの時のみ動作する */
		if((StdFrmName == DIS_F) || (StdFrmName == DTC_F)){
			if ((MDM_ModemBuffer[StdFrmPos][3] == 0) &&
				(MDM_ModemBuffer[StdFrmPos][4] == 0) &&
				(MDM_ModemBuffer[StdFrmPos][5] == 0)){
					FaxCompatibleErrorCode = RECEIVE_INCRRECT_DIS;
					FaxComPerformingFlag = NO;
					return;
			}
		}
	}
#endif
	if(StdFrmName != NO) {	/**	標準フレーム受信	*/
		/* V34で交信中ﾃﾞｰﾀﾚｲﾄのﾁｪｯｸはいらない、でも一応ﾁｪｯｸしときます */
#if defined (KEISATSU) /* 警察FAX 05/09/08 石橋正和 */
		if (FCM_S1_Scramble == TRUE) { /* スクランブル通信の場合 */
			if (AvailableTxBaudRate > S1_BAUD_RATE_MAX) {
				AvailableTxBaudRate = S1_BAUD_RATE_MAX;
			}
		}
#endif
		if(SetTxBaudRate() == NO) {	/**	トレーニングボーレート確定?	*/
			/**	エラー処理	*/
			FaxCompatibleErrorCode = COMMUNICATE_BAUDRATE_ERROR;
			FaxComPerformingFlag = NO;
			return;
		}
		SetTxCode();	/**	送信符号の確定?	*/
		if(SetTxMode() == NO) {	/**	送信モードの確定?	*/
			/**	エラー処理	*/
			FaxCompatibleErrorCode = COMMUNICATE_MODE_ERROR;
			FaxComPerformingFlag = NO;
			return;
		}
		SetTxPaperWidth();	/**	送信幅の確定?	*/
		if((TxECM_Mode == ECM_ON) || (TxInterMemoryFlag == YES)) {	/**	ECM送信かメモリ送信	*/
			/**	最少電送時間 = 0ms	*/
			TxMinimumScanningTime = SCAN_MINIMUM_TIME0;
		}
		else {		/* スキャナ送信＆Ｇ３送信 */
			SetTxMinimumCommunicationTime();	/**	最少電送時間の確定?	*/
		}
		SetTxPaperLength();/**	原稿長の確定	*/
#if (PRO_F_CODE == ENABLE)
		if(( SYS_TxTotalPage == 0 ) && (SYS_FaxComType == SYS_COMMAND_EXECUTE))  {		/* 最初の送信 ポーリング送信でない */
			if(SetTxF_CODE() == NO) {				/* F_CODE ﾋﾞｯﾄﾁｪｯｸ */
				FaxComPerformingFlag = NO;
				return;
			}
		}
#endif
#if (PRO_CIPHER == ENABLE)
		/* 暗号化送信可能かチェックする */
		if (CommandFileOptionItem == SYS_CIPHER_TX) {
			if (CheckCipherTx() == NO) {
				FaxComPerformingFlag = NO;
				return;
			}
		}
#endif
	}
	else {
		/**	標準フレームエラー	*/
		FaxCompatibleErrorCode = STANDARD_FRAME_ERROR;
		FaxComPerformingFlag = NO;
		return;
	}

/* #if (PRO_MULTI_LINE == ENABLE) */
	/* Ｖ８ビットチェック 1997/01/13 */
	if (MDM_ModemBuffer[StdFrmPos][3] & 0x20) {	/* Recommendation V8 capabilities ON ? */
		PartnerV8Capable = 1;
	}
	else {	/* else 追加 1996/08/03 Y.M */
		PartnerV8Capable = 0;
	}
/* #endif */

	return;
}

/* ここから下は、ＭＭＬ専用 */
#if(PRO_MAKER == MML)
/************************************************************
	module		:[TxOriginalModeCheck()]
	function	:[村田独自機能
		NSF を解析し独自機能を確定する
		1.受信フレームの取り込み
		2.CSI 取り込み(標準機能)
		3.ECM 送信確定(標準機能)
		4.パスワード送信のためのIDチェック(ＦＸ桐は、無し)
		5.MSE 方式確定
		6.カナID 取り込み
		7.受領証設定確定
		8.短縮ハンドシェーク設定確認
		10.メモリ送信フラグセット
		11.親展送信確定(ラベンダーＬは、スキャナーのみ)
		12.中継同報指示確定
		13.後手順短縮ハンドシェークの処理
		14.送信タイプ別処理
	]
	return		:[]
	common		:[
					MakerCodeRxFlag
					SYS_RxReceiptRequestFlag		:相手機受領証能力フラグ(送信側より受信側の能力をチェック)
					ID_FrmName
					SYB_ID_Buffer
					SYS_FaxComType
					DialingNumber.:Buffer
					MDM_ModemBuffer
					NonStdFrmPos
					PartnerSpeedHandshakeAbility
					TxInterMemoryFlag				:メモリ受信要求フラグ
					SYS_FaxComTxType
					CommandP->Option.:Item
					FaxTxCommand
	]
	condition	:[]
	comment		:[]
	keyword		:[FCM]
	machine		:[V53A]
	language	:[MS-C Ver.6]
	date		:[1993/11/16]
	author		:[鈴木 郁二]
*************************************************************/
void TxOriginalModeCheck(void)
{
	WORD ex1_pos;
	WORD ex2_pos;
	WORD ex3_pos;
	WORD secure_pos;
	WORD pos;
	WORD memory2_bit;
	UWORD page;
	UWORD block;

	ex1_pos = NO;
	ex2_pos = NO;
	ex3_pos = NO;
	secure_pos = NO;
	pos = 0;
	memory2_bit = NO;
	page = 0;
	block = 0;

	/**	フレーム取り込み	*/
	GetMultiFrameLine();
	if(MakerCodeRxFlag == NO) {	/**	他社機?	*/
		ReceiptRequestToTCRRequest();	/* 受領証要求 －＞ 送信証要求へ	  1996/12/02  By T.Yamaguchi */
	}
	if((ID_FrmName != NO) && (StandardID[0] == NULL)) {	/**	CSI 受信	*/
		/**	ID 取り込み	*/
		GetPartnerID();
	}

	SetTxECM_Mode();	/**	ECM 送信確定?	*/

	if( (CHK_SecurityTxON())	/**	パスワード送信	*/
	  &&(SYS_FaxComType == SYS_COMMAND_EXECUTE)) {	/**	FaxComType コマンド実行	*/
		if (SecurytyTxCompatibleCheck() != OK) {
			return;		/* パスワード送信不成立 */
		}
	}
	if(MakerCodeRxFlag == YES) {	/**	MML機である	*/
		/**	MSE モード確定	*/
		SetTxMSE_Mode();
		/* 局名表示フィールド解析 1996/12/02  By T.Yamaguchi */
		ex1_pos = CheckPartnerTTI_Func(7);

 #if (PRO_PRINTER_RX == ENABLE)
		/* ＨＩＮＯＫＩプリンタ受信仕様では受領証は受信できない不具合
		** 受領証は、すべて、プリンタ受信とします
		** by H.Hirao 1999/06/11
		*/
		if ((CHK_UNI_V34ReceiveType() == V34_PRX_TO_PRX) || (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX)) {
			if (SYS_V34ProcedureExecuting() && (CHK_UNI_V34ReceiveType() == V34_PRX_TO_PRX)) {
				ReceiptRequestToTCRRequest();	/* 受領証要求 －＞ 送信証要求へ */
			}
			else if (!SYS_V34ProcedureExecuting() && (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX)) {
				ReceiptRequestToTCRRequest();	/* 受領証要求 －＞ 送信証要求へ */
			}
			else {
				if(CheckPartnerRCR_Func() != YES) {	/**	相手機受領証機能なし	*/
					ReceiptRequestToTCRRequest();	/* 受領証要求 －＞ 送信証要求へ	  1996/12/02  By T.Yamaguchi */
				}
			}
		}
		else {
			if(CheckPartnerRCR_Func() != YES) {	/**	相手機受領証機能なし	*/
				ReceiptRequestToTCRRequest();	/* 受領証要求 －＞ 送信証要求へ	  1996/12/02  By T.Yamaguchi */
			}
		}
 #else
		if(CheckPartnerRCR_Func() != YES) {	/**	相手機受領証機能なし	*/
			ReceiptRequestToTCRRequest();	/* 受領証要求 －＞ 送信証要求へ	  1996/12/02  By T.Yamaguchi */
		}
 #endif
		/**	相手機短縮ハンドシェーク機能有りの場合フラグセット	*/
		CheckPartnerSCFR_Func();
	}
	if((MakerCodeRxFlag == YES) && (ex1_pos != NO)) {	/**	MML機でかつ拡張フィールド1 有り */
		/* NSF リード用ポインター インクリメント	*/
		pos = ex1_pos + 1;

		if(MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & MEMORY_OK_BIT) {	/**	メモリ残量フィールド ON	*/
			/**	NSF リード用ポインター +3	*/
			pos = pos + 3;
			/**	メモリ送信フラグ YES セット	*/
			if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {	/**	メモリ送信	*/
				/* 旧メモリ機に対しては、メモリチェックをせずにメモリ送信する */
				TxInterMemoryFlag = YES;
			}
		}

		if(CheckPartnerSecureMailFunc(ex1_pos) == YES) {	/**	相手機親展受信機能あり	*/
			/**	親展フィールドのポインターセット	*/
			secure_pos = pos;
		}

		if(MDM_ModemBuffer[NonStdFrmPos][ex1_pos] & EXPAND_FIELD_BIT) {	/**	NSF 拡張フィールド2 ON	*/
			if(secure_pos != NO) {	/**	親展送信あり	*/
				/**	NSF リード用ポインター セット	*/
				ex2_pos = pos + 2;
			}
			else {
				/**	NSF リード用ポインター セット	*/
				ex2_pos = pos;
			}
			if((MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MASK_MEMORY_MODE) != NO_IN_MEMORY_BIT) {	/**	メモリ蓄積ビット ON	*/
				memory2_bit = YES;
				/**	受信機のﾒﾓﾘ容量と送信原稿ﾒﾓﾘｻｲｽﾞを比較してメモり送信フラグセット */
				TxMemoryFlagSet(ex2_pos);
			}
			/** 後手順短縮ハンドシェーク */
			if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & POST_MSG_SPEED_BIT)	{
				if(CHK_UNI_PostSpeedHandshake()) {
					/* フラグセット */
					PostSpeedHandshakeFlag = YES;
				}
			}
#if (PRO_SPEED_EX == ENABLE)   /* 95.12.04 Add By t.yamaguchi */
			/**	短縮ハンドシェーク（着信トーン検出方式）*/
			if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {		/**	通信種別コマンド実行である	*/
				if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & SPEED_EX_BIT) {
				/* フラグセット */
					PartnerSpeedHandshakeExAbility = YES;
				}
				else {
					PartnerSpeedHandshakeExAbility = NO;
				}
			}
			else {
				PartnerSpeedHandshakeExAbility = NO;
			}
#endif
			if(MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & TX300DPI_BIT)	{		/* 300*400 受信能力 '96.01.26 By t.yamaguchi */
				/* フラグセット */
				Partner300dpiAbility = YES;
				SYB_T30_RxFrame300dpiFlag = YES;			/** T30モニタにHｰFine(R12*15.4l/mm)表示に使用 */
			}
			else {
				Partner300dpiAbility = NO;
			}
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
				if(MDM_ModemBuffer[NonStdFrmPos][ex3_pos] & EFINE_MODE_BIT) {
					PartnerEFineAbility = YES;
				}
				else {
					PartnerEFineAbility = NO;
				}
				if(MDM_ModemBuffer[NonStdFrmPos][ex3_pos] & CIPHER_COM_BIT) {	/* 1997/06/18  By T.Yamaguchi */
					PartnerCipherAbility = YES;
				}
				else {
					PartnerCipherAbility = NO;
				}
			}
		}
	}

	switch(SYS_FaxComTxType) {	/**	送信タイプ	*/
	case SYS_SCANNER_TRANSMIT:	/**	スキャナ送信	*/
#if (0) /* atlanta 削除 T.Nose 1997/11/28 */
//		/* ランプ点灯,原稿の先端セット追加 1996/06/13 T.Yamaguchi */
//		/* ランプ点灯 */
//		LampOn();
//		SCN_SetScanEndStep(SYB_MachineParameter[18]);	/* 1996/08/13 By N.Sakamoto */
#endif
		TxInterMemoryFlag = NO;	   /* 7.Apr'94 */
		break;
	case SYS_MEMORY_TRANSMIT:	/**	メモリ送信	*/
		break;
	default:
		/**	通信中フラグ NO セット	*/
		FaxCompatibleErrorCode = UNEXPECTED_ERROR;
		/**	エラー処理	*/
		FaxComPerformingFlag = NO;
		return;
	}

	if(SYS_FaxComType == SYS_COMMAND_EXECUTE) {	/**	FaxComType	コマンド実行	*/
		switch(CommandFileOptionItem) {	/**	コマンドタイプ(CommandFileOptionItem)	*/
		case SYS_SCANNER_SECURE_TX:	/**	スキャナ親展送信	*/
		case SYS_MEMORY_SECURE_TX:	/**	メモリ親展送信	*/
			if (SecureTxCompatibleCheck(secure_pos) != OK) {
				return;
			}
			break;
		case SYS_SCANNER_RELAY_BROADCAST:	/**	スキャナ中継同報指示送信	*/
		case SYS_MEMORY_RELAY_BROADCAST:	/**	メモリ中継同報指示送信	*/
			RelayTxCompatibleCheck(ex1_pos);
			break;
#if (PRO_CIPHER == ENABLE)
		case SYS_CIPHER_TX:
			if (PartnerCipherAbility == YES) {	/* 暗号化受信能力がある場合、強制的にＥＣＭで送信する 1997/10/01  By T.Yamaguchi */
				TxECM_Mode = ECM_ON;
				FcomEcmSize = ECM_256_OCT;
			}
			else {	/* 暗号化受信能力なし */	/* 1997/12/08  By T.Yamaguchi */
				if (CHK_UNI_Error_NonCiperRx()) {	/* 暗号化受信能力なしの機種に対して送信しない */
					FaxCompatibleErrorCode = CIPHER_ABILITY_ERROR;
					FaxComPerformingFlag = NO;
				}
				else  {	/* 暗号化受信能力なしの機種に対しても送信する */
					/* 何もせずに抜ける */
				}
			}
			break;
#endif
		default:
			break;
		}
	}
	return;
}

/*************************************************************************
	module		:[パスワード送信ｺﾝﾊﾟﾁﾁｪｯｸ]
	function	:[
		1.パスワード送信が成立するかチェックする
		  ダイヤルバッファの最終４桁と受信ＣＳＩの最終４桁が一致するか
		  ＣＳＩを受信していない場合はエラー
	]
	return		:[OK:パスワード送信成立
				  NG:パスワード送信不成立
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/12/02]
	author		:[山口　哲治]
*************************************************************************/
UBYTE SecurytyTxCompatibleCheck(void)
{
	if(ID_FrmName == NO) {	/**	CSIフレーム受信せず	*/
		/**	親展送信IDなしエラー	*/
		FaxCompatibleErrorCode = SECURITY_TX_NO_ID_ERROR;
		FaxComPerformingFlag = NO;
		return(NG);
	}
	else if(StandardID[0] == NULL) {	/**	CSI 受信したがスペースだった	*/
		/**	親展送信IDスペースエラー	*/
		FaxCompatibleErrorCode = SECURITY_TX_ID_SPACE_ERROR;
		FaxComPerformingFlag = NO;
		return(NG);
	}
	else{
		/* if(CheckASCII_DialAndStandardID(SYS_DialingNumber.Buffer) == NO) { 1997/10/20  By T.Yamaguchi	/@@	CSI と相手先ダイヤルナンバーが不一致	*/
		if(CheckASCII_DialAndStandardID(SYS_DialingNumber.Buffer, &StandardID[0]) == NO) {	/**	CSI と相手先ダイヤルナンバーが不一致	*/
			/*	Buffer 内のダイヤルデータはアスキー	*/
			/**	パスワード送信エラー	*/
			FaxCompatibleErrorCode = SECURITY_TX_ERROR;
			FaxComPerformingFlag = NO;
			return(NG);
		}
	}
	return(OK);
}

/*************************************************************************
	module		:[親展送信ｺﾝﾊﾟﾁﾁｪｯｸ]
	function	:[
		1.親展送信が成立するかチェックする
		  村田機独自の送信
	]
	return		:[OK:親展送信成立
				  NG:親展送信不成立
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/12/02]
	author		:[山口　哲治]
*************************************************************************/
UBYTE SecureTxCompatibleCheck(WORD secure_pos)
{
	if(secure_pos != NO) {	/**	親展送信可 */
		/**	メモリ送信フラグ YES セット */
		if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT)	{ /**	メモリ送信	*/
			TxInterMemoryFlag = YES;
		}
		if(CTRY_SecureTx()) {/* 21.Feb'94 Y.Suzuki */
			if(SetUpSecureMailTx(secure_pos) == NO) {	/**	親展送信セットアップ 失敗	*/
				/**	親展送信エラー	*/
				FaxCompatibleErrorCode = SECURE_MAILBOX_ERROR;
				FaxComPerformingFlag = NO;
				return(NG);
			}
		}
	}
	else {	/**	相手機他社機または親展機能なし	*/
		if(MakerCodeRxFlag == YES) {	/**	MML 機	*/
			/**	親展送信エラー	*/
			FaxCompatibleErrorCode = SECURE_FUNCTION_ERROR;
		}
		else {	/**	他社機	*/
			/**	親展送信エラー	*/
			FaxCompatibleErrorCode = SECURE_NOT_MURATA_ERROR;
		}
		/**	通信中フラグ NO セット	*/
		FaxComPerformingFlag = NO;
		return(NG);
	}
	return(OK);
}

/*************************************************************************
	module		:[中継同報指示送信ｺﾝﾊﾟﾁﾁｪｯｸ]
	function	:[
		1.中継同報指示送信が成立するかチェックする
		  村田機独自の送信
		  中継同報指示の場合、相手機に中継配信能力がなくても送信する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/12/02]
	author		:[山口　哲治]
*************************************************************************/
void RelayTxCompatibleCheck(WORD pos)
{
	if(MakerCodeRxFlag == YES) {	/**	相手機 MML 機	*/
		if(CTRY_RelayTx()) {/* 21.Feb'94 Y.Suzuki */
			if(CheckPartnerRelayBroadCastFunc(pos) == YES) {	/**	相手機中継配信機能確認 YES	*/
				/**	送信コマンド確定フラグ YES	*/
				FaxTxCommand = YES;
				/**	メモリ送信フラグ YES セット	*/
				if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT)	{ /**	メモリ送信	*/
					TxInterMemoryFlag = YES;
				}
			}
		}
	}
}

/*************************************************************************
	module		:[受領証要求時、相手機に受領証送信能力がないときの処理]
	function	:[
		1.受領証送信機能が無いときは送信証をプリントするように
		  コマンドファイルと実行キューにセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/12/02]
	author		:[山口　哲治]
*************************************************************************/
void ReceiptRequestToTCRRequest(void)
{
	if (SYS_RxReceiptRequestFlag == YES ) {		/* 受領証要求設定で相手機に受領証送信機能がない場合,送信証をプリントする */
		if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {				/** コマンド通信 */
			CommandP->Option.ConfirmationReport |= SYS_TCR_AND_RCR;		/* 96/06/19 By T.Yamaguchi */
			SYS_CurrentExecutingCommand->Option |= SYS_PARTNER_NOT_RCR; /* 96/06/20 */
		}
		/**	受領証不要	*/
		SYS_RxReceiptRequestFlag = NO;
	}
}

/*************************************************************************
	module		:[メモり送信フラグをセット]
	function	:[
		1.受信機のメモり容量と送信原稿のﾒﾓﾘｻｲｽﾞを比較して
		  メモリ送信フラグをセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/12/02]
	author		:[山口　哲治]
*************************************************************************/
void TxMemoryFlagSet(WORD ex2_pos)
{
	WORD memory_pos;

	/**	メモリ送信フラグ YES セット	*/
	if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT)	{ /**	メモリ送信	*/
		/* 受信機のメモリ容量と送信原稿のメモリサイズを比較 */
		/* memory_pos = ex2_pos; 1997/07/08  By T.Yamaguchi */
		memory_pos = ex2_pos + 1;
#if(PRO_MEM_RX_REJECT == ENABLE)/* 15.Dec'94 */
		if((MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MASK_MEMORY_MODE) == MMR_IN_MEMORY_BIT) {
			/**	MMR 蓄積ならメモリ残量チェックする */
			if(CheckTxMemorySize(memory_pos) == YES) {/** 送信原稿 < 受信機メモリ残量ならメモリ送信する */
				TxInterMemoryFlag = YES;
			}
			else {
				TxInterMemoryFlag = NO;
			}
		}
#else
/*		if((MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MASK_MEMORY_MODE) == MR_IN_MEMORY_BIT) {	*//**	MR 蓄積ならメモリ残量チェックする */
		if((MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MASK_MEMORY_MODE) == MMR_IN_MEMORY_BIT) {
			if(CheckTxMemorySize(memory_pos) == YES) {/** 送信原稿 < 受信機メモリ残量ならメモリ送信する */
				TxInterMemoryFlag = YES;
			}
			else {
				TxInterMemoryFlag = NO;
			}
		}
#endif
		else {
			TxInterMemoryFlag = YES;
		}
	}
	if((MDM_ModemBuffer[NonStdFrmPos][6] & MSE2_MODE_BIT) && (MDM_ModemBuffer[NonStdFrmPos][ex2_pos] & MR_IN_MEMORY_BIT)) {
		/**	メモリ蓄積ビット NO	*/
		TxInterMemoryFlag = NO;
	}
	/*	シリウスなどメモリ容量の少ない機種に対してプリンタ受信をさせる処理	*/
	if(FCM_PtnrChk_TxToPrinterRxEnable()) {	/* 属性をみるように変更 '96.04.15 BY T.Y */
		/**	メモリ送信フラグ NO セット	*/
		TxInterMemoryFlag = NO;
	}
}

/* TxOriginalModeCheck() よりここまでＭＭＬ専用 */
#endif

