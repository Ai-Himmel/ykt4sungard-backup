/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMDCS.C													 */
/*	モジュール	 :															 */
/*				 : MakeDCS_FIF()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :	1996/11/19												 */
/*	概	要		 : ＤＣＳ＋ＮＳＳ＋ＴＳＩフレーム作成						 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\SYSCOMF.H"

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/07/25 */
#include "\src\atlanta\mdm\orange\define\MDM_DEF.H"
#include "\src\atlanta\mdm\orange\ext_v\MDM_DATA.H"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/07/25 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\MDM_DEF.H"
#include "\src\atlanta\mdm\r288f\ext_v\MDM_DATA.H"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\define\FCM_PRO.H"

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/25 */
#include "\src\atlanta\define\man_pro.H"
#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_F_CODE == ENABLE) /* Added by H.Kubo 1997/10/23 */
#include "\src\atlanta\define\uni_pro.h"
#endif /* (PRO_F_CODE == ENABLE) */


/*************************************************************************
	module		:[DCS+NSS+TSIフレーム作成]
	function	:[
		1.短縮ハンドシェークのための変数セット
		2.アドレス､制御､ファクシミリ制御データセット
		3.TSIフレームセット
		4.モデムバッファにセットしたバイト数セット
		5.Xビットセット
		6.DCSフレームセット
		7.DCS送信バイト数決定（7--9）
		8.モデムバッファにセットしたバイト数セット
	]
	return		:[]
	common		:[
					TxID_FrameByteCount				:
					TxStandardFrameByteCount		:
					TxSpeedHandshakeFlag			:
					AttemptTxBaudRate				:
					AvailableTxBaudRate				:
					TxECM_Mode						:
					TxECM_Ability					:
					FcomEcmSize						:
					TxMode							:
					TxWidth							:
					SYS_DocBlock.Src.:Mode			:
					SYS_DocBlock.Src.:Size			:
					FaxComTxType					:
					AvailableTxCodingMethod			:
					TxMinimumScanningTime			:
					AvailableTxMinimumScanningTime	:
					TxCodingMethod					:
					SYS_FaxComTxType				:
					SYS_DocBlock.Src.Code			:
					MakerCodeRxFlag					:
					MDM_ModemBuffer					:
					InID							:
					InSTD							:
					FaxTxMaxLength					:
					RxStandardFrameByteCount		:
					RxReceiptRequestFlag			:
					TxInterMemoryFlag				:
					CommandFileOptionItem			:
				]
	condition	:[]
	comment		:[さつき､ラベンダー ボーレート　9600-2400BPS（紅葉）
									線密度		ﾉｰﾏﾙ､ﾌｧｲﾝ､Sﾌｧｲﾝ（紅葉）
									符号化方式	MH,MR
				桐､					ボーレート	14400-2400BPS
									線密度		ﾉｰﾏﾙ､ﾌｧｲﾝ､Sﾌｧｲﾝ､400DPI
									符号化方式	MH､MR､MMR
				紅葉				ボーレート	14400-2400BPS
									線密度		ﾉｰﾏﾙ､ﾌｧｲﾝ､Sﾌｧｲﾝ
									符号化方式	MH､MR､MMR
									]
	machine		:[V53,H8/300,SH7043]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/02]
	author		:[鈴木 郁二]
*************************************************************************/
void MakeDCS_FIF(void)
{
	/**	送信バイト数変数初期化	*/
	TxID_FrameByteCount = 0;
	TxStandardFrameByteCount = 0;

	if (TxSpeedHandshakeFlag == YES) {		/**	短縮ハンドシェーク有り	*/
		if (SYS_TxTotalPage == 0) {		/**	最初のページである	96/05/30 条件追加 By T.Yamaguchi */
			/**	試行送信ボーレートセット	*/
			AttemptTxBaudRate = AvailableTxBaudRate;
			/**	ＥＣＭモードセット	*/
			TxECM_Mode = TxECM_Ability;

			if (TxECM_Mode == ECM_ON) {		/**	ＥＣＭモードあり	*/
				/**	ＥＣＭフレームサイズ２５６バイトセット	*/
				FcomEcmSize = ECM_256_OCT;
			}
			else {
				/**	ＥＣＭフレームサイズ６４バイトセット	*/
				FcomEcmSize = ECM_64_OCT;
			}
		}
		/**	送信モードに送信側で送りたいモードをセット	*/
		TxMode = (UBYTE)SYS_DocBlock.Src.Mode;
		/**	送信原稿幅に送信側で送りたい原稿幅をセット	*/
		TxWidth = (UBYTE)SYS_DocBlock.Src.Size;
		if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {		/**	スキャナ送信	*/
			if (SYS_TxTotalPage == 0) {		/**	最初のページである	96/05/30 条件追加 By T.Yamaguchi */
				/**	送信符号化方式に送信可能な符号化方式をセット	*/
				TxCodingMethod =  AvailableTxCodingMethod;
				/**	送信最少伝送時間に送信可能な最少伝送時間をセット	*/
				TxMinimumScanningTime = AvailableTxMinimumScanningTime;
			}
		}
		else {
			/**	送信符号化方式に蓄積されている符号化方式をセット	*/
			TxCodingMethod = (UBYTE)SYS_DocBlock.Src.Code;
			/* MG3の時はMMRに変える 1996/06/05 T.Yamaguchi */
			if (TxCodingMethod == SYS_MG3_CODE) {
#if (PRO_JBIG == ENABLE) /* added by H.Kubo 1998/01/08 */
				if (AvailableTxCodingMethod == SYS_JBIG_CODE) {
					TxCodingMethod = SYS_JBIG_CODE;
				}
				else {
					TxCodingMethod = SYS_MMR_CODE;
				}
#else
				TxCodingMethod = SYS_MMR_CODE;
#endif
			}
			/**	最少伝送時間０ｍｓセット	*/
			TxMinimumScanningTime = SCAN_MINIMUM_TIME0;
#if (PRO_JBIG == ENABLE) /* added by H.Kubo 1998/01/08 */
			if ( ((TxCodingMethod == SYS_MMR_CODE) || (TxCodingMethod == SYS_JBIG_CODE) )
			 && (TxECM_Mode == ECM_OFF)) {		/**	送信符号化方式 ＭＭＲもしくはJBIGでかつＥＣＭ送信ではない	*/
				/**	送信符号化方式ＭＲセット	*/
				TxCodingMethod = SYS_MR_CODE;
			}
#else
			if ((TxCodingMethod == SYS_MMR_CODE) && (TxECM_Mode == ECM_OFF)) {		/**	送信符号化方式 ＭＭＲでかつＥＣＭ送信ではない	*/
				/**	送信符号化方式ＭＲセット	*/
				TxCodingMethod = SYS_MR_CODE;
			}
#endif
		}
		/**	ＭＳＥモードに送信可能なＭＳＥモードセット	*/
		TxMSE_Method = AvailableTxMSE_Method;
		/**	村田メーカーコード受信フラグセット	*/
		MakerCodeRxFlag = YES;
	}
	/**	ＤＣＳのアドレスフィールド､制御フィールド､ＦＣＦをモデムバッファにセット	*/
	MDM_ModemBuffer[InSTD][0] = ADDRESS_FIELD_DATA;
	MDM_ModemBuffer[InSTD][1] = LAST_FRAME_DATA;
	MDM_ModemBuffer[InSTD][2] = DCS_F;

	if (CheckSubscriberID_Buf() == YES) {		/**	自機ＮＯあり	*/
		/**	ＴＳＩのアドレスフィールド､制御フィールド､ＦＣＦをモデムバッファにセット	*/
		MDM_ModemBuffer[InID][0] = ADDRESS_FIELD_DATA;
		MDM_ModemBuffer[InID][1] = NON_LAST_FRAME_DATA;
		MDM_ModemBuffer[InID][2] = TSI_F;
		/**	自機ＮＯをモデムバッファにセット	*/
		SetSubscriberID_Frame();
		/**	モデムバッファにセットしたバイト数を大域変数にセット	*/
		TxID_FrameByteCount = 23;
	}
	/*	ＤＣＳＦＩＦビットセット	*/
	if (DIS_ReceivedFlag == YES) {		/**	ＤＩＳを受信	*/
		/**	Ｘビットをセット	*/
		MDM_ModemBuffer[InNS][2] |= X_BIT;
		MDM_ModemBuffer[InID][2] |= X_BIT;
		MDM_ModemBuffer[InSTD][2] |= X_BIT;
	}
	/**	ＤＣＳ ＦＩＦ１バイト目クリア	*/
	MDM_ModemBuffer[InSTD][3] = BIT_CLEAR;
	/**	Ｔ４ビットセット	*/
	MDM_ModemBuffer[InSTD][4] = BIT_CLEAR;
	MDM_ModemBuffer[InSTD][4] |= JT_T4_BIT;

	/*	試行送信ボーレートセット	*/
	switch (AttemptTxBaudRate) {		/**	試行送信ボーレート	*/
		case BPS2400_V27:	/**	2400BPS	*/
			/**	V27-2400BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V27_2400BPS_BIT;
			break;
		case BPS4800_V27:	/**	4800BPS	*/
			/**	V27-4800BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V27_4800BPS_BIT;
			break;
		case BPS7200_V29:	/**	V29-7200BPS	*/
			/**	V29-7200BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V29_7200BPS_BIT;
			break;
		case BPS9600_V29:	/**	V29-9600BPS	*/
			/**	V29-9600BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V29_9600BPS_BIT;
			break;
		case BPS7200_V17:	/**	V17-7200BPS	*/
			/**	V17-7200BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V17_7200BPS_BIT;
			break;
		case BPS9600_V17:	/**	V17-9600BPS	*/
			/**	V17-9600BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V17_9600BPS_BIT;
			break;
		case BPS12000_V17:	/**	V17-12000BPS	*/
			/**	V17-1200BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V17_12000BPS_BIT;
			break;
		case BPS14400_V17	:	/**	V17-14400BPS	*/
			/**	V17-14400BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V17_14400BPS_BIT;
			break;
		case  BPS12000_V33:	/**	V33-12000BPS	*/
			/**	V33-12000BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V33_12000BPS_BIT;
			break;
		case  BPS14400_V33:	/**	V33-14400BPS	*/
			/**	V33-14400BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V33_14400BPS_BIT;
			break;
	}
	
#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/07/25 */
	/*----------------------------------------------------*/
	/* Ｖ３４で交信時はＤＣＳのデータレイトビットは０固定 */
	/*----------------------------------------------------*/
	if (SYS_V34ProcedureExecuting() == 1) {
		MDM_ModemBuffer[InSTD][4] &= ~MASK_BAUDRATE;
	}
#endif /* (PRO_TX_SPEED == V34) */

	/**	DCS FIF ５バイト目クリア	*/
	MDM_ModemBuffer[InSTD][8] = BIT_CLEAR;
	switch (TxMode) {		/**	送信線密度	*/
		case SYS_NORMAL:	/**	ノーマル	*/
			break;
		case SYS_SFINE:	/**	Ｓファイン(R8*15.4mm)､	*/
			/**	Ｓファイン(R8*15.4mm)ビットON	*/
			MDM_ModemBuffer[InSTD][8] |= SUPER_FINE_BIT;
			break;
		/* 300*400の送信／ＡＮＺＵ＿Ｌ */
		case SYS_E_HFINE: /** ANZUのE_H-FINEは(300*400)ミリ S-FINEビットON By t.yamaguchi */
			/**	Ｓファイン(R8*15.4mm)ビットON	*/
			MDM_ModemBuffer[InSTD][8] |= SUPER_FINE_BIT;
			break;

#if 0
		case SYS_OFINE: /** O-FINEは(300*300dpi)インチのみ O-FINEビットON By t.yamaguchi */
			/**	Ｏファイン(300*300dpi)ビットON	*/
			MDM_ModemBuffer[InSTD][8] |= OTHER_FINE_BIT;
			break;
#endif
		case SYS_HFINE:	/**	Ｓファイン３(400*400)	*/
			/**	Ｓファイン３(400*400 OR R16*15.4l/mm)ビットON	*/
			MDM_ModemBuffer[InSTD][8] |= HYPER_FINE_BIT;
			break;
		case SYS_GRAY16:		/**	中間調１６	*/
		case SYS_GRAY16_SEP:	/**	中間調１６_SEP	*/
		case SYS_GRAY32:		/**	中間調３２	*/
		case SYS_GRAY32_SEP:	/**	中間調３２_SEP	*/
		case SYS_GRAY64:		/**	中間調６４	*/
		case SYS_GRAY64_SEP:	/**	中間調６４_SEP	*/
		case SYS_GRAY128:
		case SYS_GRAY128_SEP:
		case SYS_FINE:			/**	ファイン	*/
		case SYS_EFINE: /** E-FINE(R12*11.55L/mm)は、FINEﾋﾞｯﾄＯＮ 96/06/14 By t.yamaguchi */
			/**	ファインビットON	*/
			MDM_ModemBuffer[InSTD][4] |= SET_FINE_BIT;
			break;
		default:
			break;
	}
	if(TxModeMethod == SYS_INCH) {	/**	インチベース	*/
	/* 23.Jun'94 変更 Y.Suzuki */
		MDM_ModemBuffer[InSTD][8] |= INCH_BASE_BIT;
	}
	/*------------ 15.Dec'94 Mistake This Bit don't used in DCS !!!
	else {
		MDM_ModemBuffer[InSTD][8] |= METRIC_BASE_BIT;
	}
	----------------------------------*/
	/**	DCS FIF 4 バイト目クリア	*/
	MDM_ModemBuffer[InSTD][6] = BIT_CLEAR;
	switch (TxCodingMethod) {		/**	送信符号化方式	*/
		case SYS_MH_CODE:	/**	ＭＨ	*/
			break;
		case SYS_MR_CODE:	/**	ＭＲ	*/
			/**	ＭＲビットON	*/
			MDM_ModemBuffer[InSTD][4] |= SET_MR_BIT;
			break;
		case SYS_MMR_CODE:	/**	ＭＭＲ	*/
			/**	ＭＭＲビットON	*/
			MDM_ModemBuffer[InSTD][6] |= SET_MMR_BIT;
			break;
		case SYS_JBIG_CODE:
			/** ＪＢＩＧビットは最後にセットする	*/
			break;
	}
	if (TxSpeedHandshakeFlag == YES) {	/**	短縮ハンドシェーク時，ＭＲセット　 Dec/15/93  for F-51 Trouble */
		MDM_ModemBuffer[InSTD][4] |= SET_MR_BIT;
#if (PRO_JBIG == ENABLE) /* added by H.Kubo 1998/01/08 */
		if (TxCodingMethod == SYS_JBIG_CODE) { /** 短縮ハンドシェーク時、 MMR も選択肢に入れておかなあかんよね。 by H.Kubo  */
			MDM_ModemBuffer[InSTD][6] |= SET_MMR_BIT;
		}
#endif /* (PRO_JBIG == ENABLE) */
	}
	/**	DCS FIF 3 バイト目クリア	*/
	MDM_ModemBuffer[InSTD][5] = BIT_CLEAR;
	switch (TxWidth) {		/**	送信原稿幅	*/
		case SYS_DOCUMENT_A4_SIZE:	/**	Ａ４	*/
			/**	Ａ４幅ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= RX_A4_PAPER_BIT;
			break;
		case SYS_DOCUMENT_B4_SIZE:	/**	Ｂ４	*/
			/**	Ｂ４幅ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= RX_B4_PAPER_BIT;
			break;
		case SYS_DOCUMENT_A3_SIZE:	/**	Ａ３	*/
			/**	Ａ３幅ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= RX_A3_PAPER_BIT;
			break;
	}
	switch (FaxTxMaxLength) {		/**	送信原稿長	*/
		case SYS_A4_LENGTH:	/**	Ａ４	*/
			/**	Ａ４長ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= LENGTH_A4_BIT;
			break;
		case SYS_B4_LENGTH:	/**	Ｂ４	*/
			/**	Ｂ４長ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= LENGTH_B4_BIT;
			break;
		case SYS_NO_LIMIT:	/**	無限長	*/
			/**	無限長ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= LENGTH_UNLIMITED_BIT;
			break;
	}
	switch (TxMinimumScanningTime) {		/**	送信最少伝送時間	*/
		case SCAN_MINIMUM_TIME20:	/**	TIME20ms	*/
			/**	TIME20msビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME20;
			break;
		case SCAN_MINIMUM_TIME40:	/**	TIME40ms	*/
			/**	TIME40msビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME40;
			break;
		case SCAN_MINIMUM_TIME10:	/**	TIME10ms	*/
			/**	TIME10msビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME10;
			break;
		case SCAN_MINIMUM_TIME5:	/**	TIME5ms	*/
			/**	TIME5msビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME5;
			break;
		case SCAN_MINIMUM_TIME0:	/**	TIME0ms	*/
			/**	TIME0msビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME0;
			break;
	}
	/**	拡張ビットON（２４ビット）	*/
	MDM_ModemBuffer[InSTD][5] |= EXPAND_FIELD_BIT;
	if (TxECM_Mode == ECM_ON) {		/**	送信ＥＣＭモードON	*/
		/**	ＥＣＭビットON	*/
		MDM_ModemBuffer[InSTD][6] |= ECM_MODE_BIT;
		if (FcomEcmSize == ECM_64_OCT) {		/**	フレームサイズ６４	*/
			/**	ＥＣＭフレームサイズ６４ビットON	*/
			MDM_ModemBuffer[InSTD][6] |= ECM_FRAMESIZE_64_BIT;
		}
	}
	/**	拡張ビットON（３２ビット）	*/
	MDM_ModemBuffer[InSTD][6] |= EXPAND_FIELD_BIT;
	/**	DCS FIF 5バイト目クリア	*/
	MDM_ModemBuffer[InSTD][7] = BIT_CLEAR;
	/**	拡張ビットON（４０ビット）	*/
	MDM_ModemBuffer[InSTD][7] |= EXPAND_FIELD_BIT;

	if (TxSpeedHandshakeFlag == YES) {		/**	短縮ハンドシェーク有り	*/
		/**	DCSフレーム送信バイト数 9バイトセット	*/
		TxStandardFrameByteCount = 9;
	}
	else {
		if (RxStandardFrameByteCount < 8) {		/**	受信フレームバイト数 ７バイト以下	*/
			/**	拡張フィールドOFF（３２ビット）	*/
			MDM_ModemBuffer[InSTD][6] &= ~EXPAND_FIELD_BIT;
			/**	DCS FIF 5,6 バイト目クリア	*/
			MDM_ModemBuffer[InSTD][7] = BIT_CLEAR;
			MDM_ModemBuffer[InSTD][8] = BIT_CLEAR;
			/**	DCSフレーム送信バイト数 7バイトセット	*/
			TxStandardFrameByteCount = 7;
		}
		else if (RxStandardFrameByteCount == 8) {	/**	受信フレームバイト数 ８バイト	*/
			/**	拡張フィールドOFF（４０ビット）	*/
			MDM_ModemBuffer[InSTD][7] &= ~EXPAND_FIELD_BIT;
			/**	DCS FIF 6 バイト目クリア	*/
			MDM_ModemBuffer[InSTD][8] = BIT_CLEAR;
			/**	DCSフレーム送信バイト数 8バイトセット	*/
			TxStandardFrameByteCount = 8;
		}
		else {
			/**	DCSフレーム送信バイト数 9バイトセット	*/
			TxStandardFrameByteCount = 9;

#if (PRO_F_CODE == ENABLE)
			/**	ＤＩＳ ＦＩＦ７バイト目クリア	*/
			MDM_ModemBuffer[InSTD][9] = BIT_CLEAR;

			if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {		/**	交信種別 コマンド実行	*/
				if ((CommandFileOptionItem == SYS_MEMORY_SUB_ADDRESS_TX)
				 || (CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX)) {	/* サブアドレスポーリング受信 */

					if(( SYS_TxTotalPage == 0 ) || (!CHK_UNI_SUB_Frame_Off())) {	/* UNI_SW_B6-4 条件追加 1997/10/06 By T.Yamaguchi */
						/**	拡張フィールドセット（４８ビット）	*/
						MDM_ModemBuffer[InSTD][8] |= EXPAND_FIELD_BIT;
						MDM_ModemBuffer[InSTD][9] |= SUBADDRESSING_BIT;	/* サブアドレス能力 */

						if ((PartnerT_PWD_Ability) && (OwnPasswordFrameID[0] != NULL)) {
							MDM_ModemBuffer[InSTD][9] |= PASSWORD_BIT;		/* パスワード能力 */
						}
						/**	ＤＩＳ送信バイト数１０セット	*/
						TxStandardFrameByteCount = 10;
					}
				}
			}
 #if (PRO_JBIG == ENABLE) /* Changed by H.Kubo 1998/05/11 */
			if (TxCodingMethod == SYS_JBIG_CODE) {		/* ＪＢＩＧ能力があるなら */
				MDM_ModemBuffer[InSTD][10] = BIT_CLEAR;
				MDM_ModemBuffer[InSTD][11] = BIT_CLEAR;
				MDM_ModemBuffer[InSTD][12] = BIT_CLEAR;

				MDM_ModemBuffer[InSTD][8] |= EXPAND_FIELD_BIT;
				MDM_ModemBuffer[InSTD][9] |= EXPAND_FIELD_BIT;
				MDM_ModemBuffer[InSTD][10] |= EXPAND_FIELD_BIT;
				MDM_ModemBuffer[InSTD][11] |= EXPAND_FIELD_BIT;

				MDM_ModemBuffer[InSTD][12] |= JBIG_BIT;
				TxStandardFrameByteCount = 13;
			}
 #endif /* (PRO_JBIG == ENABLE) */
#else /* code without F-code added by H.Kubo 1998/05/11 */
 #if (PRO_JBIG == ENABLE) /* Changed by H.Kubo 1998/05/11 */
			if (TxCodingMethod == SYS_JBIG_CODE) {		/* ＪＢＩＧ能力があるなら */
				MDM_ModemBuffer[InSTD][9] = BIT_CLEAR;
				MDM_ModemBuffer[InSTD][10] = BIT_CLEAR;
				MDM_ModemBuffer[InSTD][11] = BIT_CLEAR;
				MDM_ModemBuffer[InSTD][12] = BIT_CLEAR;

				MDM_ModemBuffer[InSTD][8] |= EXPAND_FIELD_BIT;
				MDM_ModemBuffer[InSTD][9] |= EXPAND_FIELD_BIT;
				MDM_ModemBuffer[InSTD][10] |= EXPAND_FIELD_BIT;
				MDM_ModemBuffer[InSTD][11] |= EXPAND_FIELD_BIT;

				MDM_ModemBuffer[InSTD][12] |= JBIG_BIT;
				TxStandardFrameByteCount = 13;
			}
 #endif /* (PRO_JBIG == ENABLE) */
#endif /* (PRO_F_CODE == ENABLE) */
		}
	}
}
