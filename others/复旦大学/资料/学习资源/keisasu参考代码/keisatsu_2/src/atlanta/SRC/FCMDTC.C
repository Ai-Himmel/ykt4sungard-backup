/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_DTC.C												 */
/*	モジュール	 :															 */
/*				 : MakeDTC_FIF()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :															 */
/*	概	要		 : ＤＴＣ＋ＣＩＧ作成										 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\define\SYSCOMF.H"
#include "\src\atlanta\define\STD.H"

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
#include "\src\atlanta\ext_v\bkupram.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\CMN_PRO.H"

#if (PRO_F_CODE == ENABLE) /* Added by H.Kubo 1997/10/23 */
#include "\src\atlanta\define\uni_pro.h"
#endif /* (PRO_F_CODE == ENABLE) */

/*************************************************************************
	module		:[DTC+CIG作成]
	function	:[
		1.アドレス､制御､ファクシミリ制御データセット(DTC,NSC,CIG)
		2.ＤＩＧフレーム作成
		3.モデムバッファにセットしたバイト数を記憶
		4.ＤＴＣフレーム作成
		5.モデムバッファにセットしたバイト数を記憶
	]
	return		:[]
	common		:[
			TxID_FrameByteCount
			TxStandardframeByteCount
			MDM_ModemBuffer
			InSTD
			InID
			AvailableRxCodingMethod
			AvailableRxMinimumScanningTime
			SYS_FaxComFIP_RxActiveFlag
			AvailableRxResolution
			RxECM_Ability
			SYS_FaxComType
			CommandP->Option.:Item
	]
	condition	:[]
	comment		:[
				ミランは，別ファイルにする　条件コンパイルは、紅葉とさつき、ラベンダー間で使用
					ＳＭＳＥ受信---紅葉のプリンタ受信のみなし
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/06]
	author		:[鈴木 郁二]
*************************************************************************/
void MakeDTC_FIF(void)
{
	/**	送信バイト数変数初期化	*/
	TxID_FrameByteCount = 0;
	TxStandardFrameByteCount = 0;

	/**	ＤＴＣのアドレスフィールド､制御フィールド､ＦＣＦをモデムバッファにセット	*/
	MDM_ModemBuffer[InSTD][0] = ADDRESS_FIELD_DATA;
	MDM_ModemBuffer[InSTD][1] = LAST_FRAME_DATA;
	MDM_ModemBuffer[InSTD][2] = DTC_F;

	if (CheckSubscriberID_Buf() == YES) {		/**	自機ＮＯあり	*/
		/**	ＣＩＧのアドレスフィールド､制御フィールド､ＦＣＦをモデムバッファにセット	*/
		MDM_ModemBuffer[InID][0] = ADDRESS_FIELD_DATA;
		MDM_ModemBuffer[InID][1] = NON_LAST_FRAME_DATA;
		MDM_ModemBuffer[InID][2] = CIG_F;
		/**	自機ＮＯをモデムバッファにセット	*/
		SetSubscriberID_Frame();
		/**	モデムバッファにセットしたバイト数を大域変数にセット	*/
		TxID_FrameByteCount = 23;
	}

	/*-------------------*/
	/* DTC フレームセット*/
	/*-------------------*/
	/**	ＤＴＣ ＦＩＦ１バイト目クリア	*/
	MDM_ModemBuffer[InSTD][3] = BIT_CLEAR;
#if (PRO_TX_SPEED == V34) /* Ported from \src\clover\src\fcmdis.c by H.Kubo 1997/07/25 */
	/*-----------------*/
	/** Ｖ８能力セット */
	/*-----------------*/	/* 正式勧告がでるまで BIT6 BIT81 両方たてる 1995/12/22 */
	if ((CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT) == DATA_SIGNALING_RATE_V34_BIT) {/** Ｖ３４リソース有り */
		MDM_ModemBuffer[InSTD][3] |= 0x20;
	}
#endif /* (PRO_TX_SPEED == V34 )  */

	/**	ＤＴＣ ＦＩＦ２バイト目クリア	*/
	MDM_ModemBuffer[InSTD][4] = BIT_CLEAR;
	/**	Ｔ４ビットセット	*/
	MDM_ModemBuffer[InSTD][4] |= JT_T4_BIT;
	/**	ファインビットON	*/
	MDM_ModemBuffer[InSTD][4] |= SET_FINE_BIT;
#if (PRO_FIP == ENABLE)
	if (SYS_FaxComFIP_RxActiveFlag == NO) {		/**	ＦＩＰ受信ではない	*/
#endif
#if (PRO_JBIG == ENABLE) /* added by H.Kubo 1998/01/19 */
		if ((AvailableRxCodingMethod == SYS_JBIG_CODE) ||
		    (AvailableRxCodingMethod == SYS_MMR_CODE) ||	/* Modify by NOBUKO	 Aug/30/93 */
			(AvailableRxCodingMethod == SYS_MR_CODE)) {		/**	受信可能符号化方式ＭＭＲまたは､ＭＲ	*/
			/**	ＭＲビットON	*/
			MDM_ModemBuffer[InSTD][4] |= SET_MR_BIT;
		}
#else
		if ((AvailableRxCodingMethod == SYS_MMR_CODE) ||	/* Modify by NOBUKO	 Aug/30/93 */
			(AvailableRxCodingMethod == SYS_MR_CODE)) {		/**	受信可能符号化方式ＭＭＲまたは､ＭＲ	*/
			/**	ＭＲビットON	*/
			MDM_ModemBuffer[InSTD][4] |= SET_MR_BIT;
		}
#endif
#if (PRO_FIP == ENABLE)
	}
#endif
	switch (AvailableRxBaudRate) {		/**	受信可能ボーレート	*/
		/* V17-144 V29-96 ONLY 松竹桜もなぜかこうなっている --> ADD V33-144,V27-48 8.Aug'94 Y.Suzuki */
		case BPS14400_V17:	/**	V17_14400	*/
			/**	V17ビットON	*/
			MDM_ModemBuffer[InSTD][4] |= CCITT_V17_BIT;
			break;
		case BPS14400_V33:	/**	V33_14400	*/
			/**	V33ビットON	*/
			MDM_ModemBuffer[InSTD][4] |= CCITT_V33_BIT;
			break;
		case BPS9600_V29:	/**	V29_9600	*/
			/**	V29ビットON	*/
			MDM_ModemBuffer[InSTD][4] |= CCITT_V29_BIT;
			break;
		case BPS4800_V27:	/**	4800	*/
			/**	V27ビットON	*/
			MDM_ModemBuffer[InSTD][4] |= CCITT_V27_BIT;
			break;
		case BPS2400_V27:	/**	2400	add By T.Y 96/04/26 */
			/**	V27ビットON	*/
			MDM_ModemBuffer[InSTD][4] |= CCITT_V27F_BIT;
			break;
	}
	/**	ＤＴＣ ＦＩＦ３バイト目クリア	*/
	MDM_ModemBuffer[InSTD][5] = BIT_CLEAR;
	FCM_BuckUpPaperSize = CheckDocPaperSize();
/*	switch (CheckDocPaperSize()) {		/@@	原稿幅チェック	*/
	switch (FCM_BuckUpPaperSize) {		/**	原稿幅チェック	*/
		case SYS_A4_PAPER:	/**	Ａ４	*/
			/**	受信紙Ａ４ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= RX_A4_PAPER_BIT;
			/**	記録紙幅セット	*/
			RxWidth = SYS_DOCUMENT_A4_SIZE;
			break;
		case SYS_A3_PAPER:	/**	Ａ３	*/
			/**	受信紙Ａ３ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= RX_A3_PAPER_BIT;
			/**	記録紙幅セット	*/
			RxWidth = SYS_DOCUMENT_A3_SIZE;
			break;
		case SYS_B4_PAPER:	/**	Ｂ４	*/
			/**	受信紙Ｂ４ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= RX_B4_PAPER_BIT;
			/**	記録紙幅セット	*/
			RxWidth = SYS_DOCUMENT_B4_SIZE;
			break;
	}
/*	カット紙なら記録幅の最大記録長をセット	*/	/* This function is not mandatory for French regulation. */
	MDM_ModemBuffer[InSTD][5] |= LENGTH_UNLIMITED_BIT;	  /* 最大記録長の設定 */

	switch (AvailableRxMinimumScanningTime) {		/**	受信可能最少伝送時間	*/
	case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
		/**	TIME20ビットON	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME20;
		break;
	case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
		/**	TIME40ビットON	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME40;
		break;
	case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
		/**	TIME10ビットON	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME10;
		break;
	case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
		/**	TIME5ビットON	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME5;
		break;
	case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
		/**	TIME0ビットON	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME0;
		break;
	case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
		/**	TIME10_2ビットON	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME10_2;
		break;
	case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
		/**	TIME20_2ビットON	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME20_2;
		break;
	case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
		/**	TIME40_2ビットON	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME40_2;
		break;
	}
	/**	拡張フィールドセット（２４ビット）	*/
	MDM_ModemBuffer[InSTD][5] |= EXPAND_FIELD_BIT;
	/**	ＤＩＳ ＦＩＦ４バイト目クリア	*/
	MDM_ModemBuffer[InSTD][6] = BIT_CLEAR;
#if (PRO_FIP == ENABLE)
	if (SYS_FaxComFIP_RxActiveFlag == NO) {		/**	ＦＩＰ受信	*/
#endif
		switch (AvailableRxCodingMethod) {		/**	受信可能符号化方式	*/
#if (PRO_JBIG == ENABLE) /* added by H.Kubo 1998/01/19 */
			case SYS_JBIG_CODE:
#endif
			case SYS_MMR_CODE:	/**	ＭＭＲ	*/
				/**	MMRビットON	*/
				MDM_ModemBuffer[InSTD][6] |= SET_MMR_BIT;
				break;
			case SYS_MR_CODE:	/**	ＭＲ	*/
			case SYS_MH_CODE:	/**	ＭＨ	*/
			default:
				break;
		}
#if (PRO_FIP == ENABLE)
	}
#endif
	if (RxECM_Ability == ECM_ON) {		/**	ＥＣＭ受信能力あり	*/
		/**	ＥＣＭビットON	*/
		MDM_ModemBuffer[InSTD][6] |= ECM_MODE_BIT;
	}
	/**	拡張フィールドセット（３２ビット）	*/
	MDM_ModemBuffer[InSTD][6] |= EXPAND_FIELD_BIT;
	/**	ＤＩＳ ＦＩＦ５バイト目クリア	*/
	MDM_ModemBuffer[InSTD][7] = BIT_CLEAR;
	/**	拡張フィールドセット（４０ビット）	*/
	MDM_ModemBuffer[InSTD][7] |= EXPAND_FIELD_BIT;
	/**	ＤＩＳ ＦＩＦ６バイト目クリア	*/
	MDM_ModemBuffer[InSTD][8] = BIT_CLEAR;
	switch (AvailableRxResolution) {		/**	受信可能線密度	*/
		case SYS_HFINE:	/**	ハイパーファイン桐は２種類400*400(ｲﾝﾁ/ﾐﾘ)	*/
			/**	ハイパーファインビットセット	*/
			MDM_ModemBuffer[InSTD][8] |= HYPER_FINE_BIT;
#if 0
		case SYS_OFINE:/* 300×300/25.4mm */
			MDM_ModemBuffer[InSTD][8] |= OTHER_FINE_BIT;	/* OTHER_FINE ﾋﾞｯﾄだけセットすると、このビットを見ていない機種があるので		 */
															/* S-FINE ﾋﾞｯﾄもセットするようにしなければならない！！要確認  '96.01.31 By T.Y	 */
#endif
		case SYS_E_HFINE:	/** ANZUの、H-FINEはＳファインビットセットする By t.yamaguchi */
		case SYS_SFINE:	/**	Ｓファインは､R8*15.4l/m(ﾐﾘ)	*/
			/**	Ｓファインビットセット	*/
			MDM_ModemBuffer[InSTD][8] |= SUPER_FINE_BIT;
			break;
		default:
			break;
	}
	/**	インチ／メトリックベース　インチビットON	*/
/* #if (PRO_HQ_MODE == ENABLE)		/@ 杏はインチでも受けれるが基本的にｍｍで受ける	 t.yamaguchi */
/*	if (CHK_UNI_Inch_TRx()) { */
/*		MDM_ModemBuffer[InSTD][8] |= INCH_BASE_BIT; */
/*	}	*/
/* #endif */
	MDM_ModemBuffer[InSTD][8] |= METRIC_BASE_BIT;
	if (CHK_DIS_ExpandFrameTx()) {		/**	DIS FIF ５バイト以上送出しない(SOFT SW)	*/
		/**	拡張フィールドOFF（３２ビット）	*/
		MDM_ModemBuffer[InSTD][6] &= ~EXPAND_FIELD_BIT;
		/**	DIS FIF ６バイト目以降クリア	*/
		MDM_ModemBuffer[InSTD][7] = BIT_CLEAR;
		MDM_ModemBuffer[InSTD][8] = BIT_CLEAR;
		/**	ＤＩＳ送信バイト数７セット	*/
		TxStandardFrameByteCount = 7;
	}
	else {
#if (PRO_F_CODE == ENABLE)
		/*--------*/
		/* F_CODE */
		/*--------*/
		/**	ＤＩＳ送信バイト数9セット	*/
		TxStandardFrameByteCount = 9;

		if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {		/**	交信種別 コマンド実行	*/
			if (CommandFileOptionItem == SYS_SELECT_POLLING_RX) {	/* サブアドレスポーリング受信 */

				if(( SYS_RxTotalPage == 0 ) || (!CHK_UNI_SUB_Frame_Off())) {	/* UNI_SW_B6-4 */

					MDM_ModemBuffer[InSTD][8] |= SELECTIVE_POLLING_BIT;	/* 選択ポーリング能力 */

					if ((PartnerP_PWD_Ability) && (OwnPasswordFrameID[0] != NULL)) {
						/**	拡張フィールドセット（４８ビット）	*/
						MDM_ModemBuffer[InSTD][8] |= EXPAND_FIELD_BIT;
						/**	ＤＩＳ ＦＩＦ７バイト目クリア	*/
						MDM_ModemBuffer[InSTD][9] = BIT_CLEAR;

						MDM_ModemBuffer[InSTD][9] |= PASSWORD_BIT;		/* パスワード能力 */
						/**	ＤＩＳ送信バイト数１０セット	*/
						TxStandardFrameByteCount = 10;
					}
				}
			}
		}
#if (PRO_JBIG == ENABLE) /* by H.Kubo 1998/05/11 */
#if (0) /* Changed by H.Kubo 1998/05/11 */
@@		if (AvailableTxCodingMethod == SYS_JBIG_CODE) {		/* ＪＢＩＧ能力があるなら */
#else
		if (AvailableRxCodingMethod == SYS_JBIG_CODE) {		/* ＪＢＩＧ受信能力があるなら */
#endif
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
#endif
#else
		/**	ＤＩＳ送信バイト数９セット	*/
		TxStandardFrameByteCount = 9;

#if (PRO_JBIG == ENABLE) /* by H.Kubo 1998/05/11 */
#if (0) /* Changed by H.Kubo 1998/05/11 */
@@		if (AvailableTxCodingMethod == SYS_JBIG_CODE) {		/* ＪＢＩＧ能力があるなら */
#else
		if (AvailableRxCodingMethod == SYS_JBIG_CODE) {		/* ＪＢＩＧ受信能力があるなら */
#endif
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
#endif
	}
}
