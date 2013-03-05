/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMDIS.C													 */
/*	モジュール	 :															 */
/*				 : MakeDIS_FIF()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 : ＤＩＳ＋ＣＳＩ作成										 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\SYSDOC.H"

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
#include "\src\atlanta\define\mlt_pro.h"


#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\CL1_DATA.H"
#endif
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\STNG_PRO.H"
#include "\src\atlanta\define\CMN_PRO.H"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\uni_pro.h" /*1996/04/17 Eguchi */

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/25 */
#include "\src\atlanta\define\cmn_def.h"
#endif /* (PRO_TX_SPEED == V34) */

/* #if (PRO_MULTI_LINE == ENABLE)	/@ 1996/11/13 */
#include "\src\atlanta\define\sys_opt.h"
/* #endif */

/*************************************************************************
	module		:[DIS+CSI作成]
	function	:[
		1.アドレス､制御､FCFデータセット
		2.CSIフレームセット
		3.モデムバッファにセットしたバイト数セット
		4.DISフレーム作成
		5.モデムバッファにセットしたバイト数セット
	]
	return		:[]
	common		:[
				TxID_FrameByteCount
				TxStandardframeByteCount
				MDM_ModemBuffer
				InSTD
				InID
				AvailableRxCodingMethod
				OwnMakerCode
				SYS_FaxComFIP_RxActiveFlag
				AvailableRxBaudRate
				RxWidth
				RxECM_Ability
				AvailableRxMinimumScanningTime
				AvailableRxResolution
	]
	condition	:[]
	comment		:[
		修正履歴	94/10/13	村田メモリ間受信後のリトレーニング時、さつき、ラベンダ、紅葉 の DIS 最少電送時間が 0ms になる。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/03]
	author		:[鈴木 郁二]
*************************************************************************/
void MakeDIS_FIF(void)
{
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/7/1 K.Kawata */
	UWORD	i;
#endif

#if (PRO_F_CODE == ENABLE)
	UBYTE subaddress_box_setting;

	subaddress_box_setting = 0;
#endif

	/**	送信バイト数変数初期化	*/
	TxID_FrameByteCount = 0;
	TxStandardFrameByteCount = 0;

	/**	ＤＩＳのアドレスフィールド､制御フィールド､ＦＣＦをモデムバッファにセット	*/
	MDM_ModemBuffer[InSTD][0] = ADDRESS_FIELD_DATA;
	MDM_ModemBuffer[InSTD][1] = LAST_FRAME_DATA;
	MDM_ModemBuffer[InSTD][2] = DIS_F;

	if (CheckSubscriberID_Buf() == YES) {		/**	自機ＮＯあり	*/
		/**	ＣＳＩのアドレスフィールド､制御フィールド､ＦＣＦをモデムバッファにセット	*/
		MDM_ModemBuffer[InID][0] = ADDRESS_FIELD_DATA;
		MDM_ModemBuffer[InID][1] = NON_LAST_FRAME_DATA;
		MDM_ModemBuffer[InID][2] = CSI_F;
		/**	自機電話番号をモデムバッファにセット	*/
		SetSubscriberID_Frame();
		/**	モデムバッファにセットしたバイト数を大域変数にセット	*/
		TxID_FrameByteCount = 23;
	}

	/*-------------------*/
	/* DIS フレームセット*/
	/*-------------------*/
	/**	ＤＩＳ ＦＩＦ１，２バイト目クリア	*/
	MDM_ModemBuffer[InSTD][3] = BIT_CLEAR;
	MDM_ModemBuffer[InSTD][4] = BIT_CLEAR;

#if (PRO_TX_SPEED == V34) /* Ported from \src\clover\src\fcmdis.c by H.Kubo 1997/07/25 */
	/*-----------------*/
	/** Ｖ８能力セット */
	/*-----------------*/	/* 正式勧告がでるまで BIT6 BIT81 両方たてる 1995/12/22 */
	if ((CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT) == DATA_SIGNALING_RATE_V34_BIT) {/** Ｖ３４リソース有り */
		MDM_ModemBuffer[InSTD][3] |= 0x20;
	}
#endif /* (PRO_TX_SPEED == V34 )  */

	/**	Ｔ４ビットセット	*/
	MDM_ModemBuffer[InSTD][4] |= JT_T4_BIT;/* T4受信能力あり */
	/**	ファインビットON	*/
	MDM_ModemBuffer[InSTD][4] |= SET_FINE_BIT;

#if (PRO_FIP == ENABLE)
	if (SYS_FaxComFIP_RxActiveFlag == NO) {		/**	ＦＩＰ受信ではない	*/
#endif
#if (PRO_JBIG == ENABLE) /* Modified by H.Kubo 1997/12/24 */
		if ((AvailableRxCodingMethod == SYS_JBIG_CODE) ||
			(AvailableRxCodingMethod == SYS_MMR_CODE) ||
		 (AvailableRxCodingMethod == SYS_MR_CODE)) {		/**	受信可能符号化方式ＭＭＲまたは､ＭＲ	*/
#else
		if ((AvailableRxCodingMethod == SYS_MMR_CODE) || (AvailableRxCodingMethod == SYS_MR_CODE)) {		/**	受信可能符号化方式ＭＭＲまたは､ＭＲ	*/
#endif /* (PRO_JBIG == ENABLE) */
			/**	ＭＲビットON	*/
			MDM_ModemBuffer[InSTD][4] |= SET_MR_BIT;
		}
#if (PRO_FIP == ENABLE)
	}
#endif

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == DISABLE)	/* Add By O.Kimoto 1996/11/12 */
** 	if ((SYB_PollingDocumentStatus || SYB_DB_PollingDocumentStatus)
** #else
** #if (0)	/*  By O.Kimoto 1997/07/07 */
** ** 	/* メモリスイッチＨ：２－１を０にしたときに、ポーリング原稿の権利を放さないと
** ** 	** いう不具合が発生したので
** ** 	** By O.Kimoto 1997/07/07
** ** 	*/
** ** 	if ((((SYS_PollingDocumentStatus) && ((SYS_PollingDocExclusiveFlag & 0x000F) == SYS_SEND_INTERNAL_LINE)) || SYS_DB_PollingDocumentStatus)
** #endif
** 
**  	if (((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE) || SYB_DB_PollingDocumentStatus)
** 
** #endif
#else
 	if (((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE) || SYB_DB_PollingDocumentStatus)
#endif

	 ||((TxReceiptRequestFlag == YES) && (OwnMakerCode == MURATA_CODE))
	 || (CheckPollingTxType() != 0)
	 || ((SYB_SelectPollDocumentStatus == 1) || (CHK_UNI_FcodeSecureDocPollTx()) ) ){
/*	 || ((CHK_UNI_PollingBitOn()) && ((SYB_SelectPollDocumentStatus == 1) || (CHK_UNI_FcodeSecureDocPollTx())) ) ){ */
		/**	ポーリング原稿ありまたは､受領証送信でかつ自機コード村田、または、受信原稿ポーリングON(27.Jly'94 Y.Suzuki)	*/
		/**	ポーリング原稿ありビットON	*/
		MDM_ModemBuffer[InSTD][4] |= SET_POLLING_DOC_BIT;
	}

	switch (AvailableRxBaudRate) {		/**	受信可能ボーレート	*/
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

	/**	ＤＩＳ ＦＩＦ３バイト目クリア	*/
	MDM_ModemBuffer[InSTD][5] = BIT_CLEAR;
	FCM_BuckUpPaperSize = CheckDocPaperSize();
/*	switch (CheckDocPaperSize()) {		/@@	記録紙幅	*/
	switch (FCM_BuckUpPaperSize) {		/**	記録紙幅	*/
		case SYS_A4_PAPER:	/**	Ａ４	*/
			/**	記録紙A4ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= RX_A4_PAPER_BIT;
			/**	受信幅A4セット	*/
			RxWidth = SYS_DOCUMENT_A4_SIZE;
			break;
		case SYS_A3_PAPER:	/**	Ａ３	*/
			/**	記録紙A3ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= RX_A3_PAPER_BIT;
			/**	受信幅A3セット	*/
			RxWidth = SYS_DOCUMENT_A3_SIZE;
			break;
		case  SYS_B4_PAPER:	/**	Ｂ４	*/
			/**	記録紙B4ビットON	*/
			MDM_ModemBuffer[InSTD][5] |= RX_B4_PAPER_BIT;
			/**	受信幅B4セット	*/
			RxWidth = SYS_DOCUMENT_B4_SIZE;
			break;
	}
	/**	記録紙長無限長セット	*/
	MDM_ModemBuffer[InSTD][5] |= LENGTH_UNLIMITED_BIT;	  /* 最大記録長の設定 */

/*----------- さつき、ラベンダー、紅葉は、0msのDIS出しません ---- 25.Jun'94 Y.Suzuki */
	/* AvailableRxMinimumScanningTime	= SCAN_MINIMUM_TIME20_2; この変数を直接変更しない 28.Oct'94 Y.Suzuki */
	switch (AvailableRxMinimumScanningTime) {		/**	受信可能最少伝送時間	*/
		case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
			/**	最少伝送時間２０ｍｓビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME20;
			break;
		case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
			/**	最少伝送時間４０ｍｓビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME40;
			break;
		case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
			/**	最少伝送時間１０ｍｓビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME10;
			break;
		case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
			/**	最少伝送時間５ｍｓビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME5;
			break;
		case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
			/**	最少伝送時間０ｍｓビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME0;
			break;
		case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
			/**	最少伝送時間１０＿２ｍｓビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME10_2;
			break;
		case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
			/**	最少伝送時間２０＿２ｍｓビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME20_2;
			break;
		case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
			/**	最少伝送時間４０＿２ｍｓビットON	*/
			MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME40_2;
			break;
	}
	/**	拡張フィールドセット（２４ビット）	*/
	MDM_ModemBuffer[InSTD][5] |= EXPAND_FIELD_BIT;

	/**	ＤＩＳ ＦＩＦ４バイト目クリア	*/
	MDM_ModemBuffer[InSTD][6] = BIT_CLEAR;
#if (PRO_FIP == ENABLE)
	if (SYS_FaxComFIP_RxActiveFlag == NO) {
#endif
		switch (AvailableRxCodingMethod) {		/**	受信可能符号化方式	*/
#if (PRO_JBIG == ENABLE) /* Added by H.Kubo 1997/12/24 */
			case SYS_JBIG_CODE:	/** JBIG	*/
#endif /* (PRO_JBIG == ENABLE) */
			case SYS_MMR_CODE:	/**	ＭＭＲ	*/
				/**	ＭＭＲビットON	*/
				MDM_ModemBuffer[InSTD][6] = SET_MMR_BIT;
				break;
			case SYS_MR_CODE:	/**	ＭＲ	*/
			case SYS_MH_CODE:	/**	ＭＨ	*/
			default:
				break;
		}
#if (PRO_FIP == ENABLE)
	}
#endif
	if (RxECM_Ability == ECM_ON) {		/**	受信ＥＣＭ能力有り	*/
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

	switch (AvailableRxResolution) {		/**	受信可能線密度(ハイパーファイン、スーパーファインビットのセット)	*/
		case SYS_HFINE:	/**	Ｓファイン桐は２種類400*400､R16*15.4l/m	*/
			/**	Ｈファインビットセット	*/
			MDM_ModemBuffer[InSTD][8] |= HYPER_FINE_BIT;
#if 0
		case SYS_OFINE:/* 300×300dpi インチのみ */
			MDM_ModemBuffer[InSTD][8] |= OTHER_FINE_BIT;	/* OTHER_FINE ﾋﾞｯﾄだけセットすると、このビットを見ていない機種があるので		 */
															/* S-FINE ﾋﾞｯﾄもセットするようにしなければならない！！要確認  '96.01.31 By T.Y	 */
#endif
		case SYS_E_HFINE:	/** ANZUの、H-FINEはＳファインビットセットする By t.yamaguchi */
		case SYS_SFINE:/**	R8*15.4l/mm	*/
			/**	Ｓファインビットセット	*/
			MDM_ModemBuffer[InSTD][8] |= SUPER_FINE_BIT;
			break;
		default:
			break;
	}
	/**	インチ／メトリックベース　ミリビットON	*/
	MDM_ModemBuffer[InSTD][8] |= METRIC_BASE_BIT;

#if 0 /* (PRO_PRINT_TIME == TIME2) */
	MDM_ModemBuffer[InSTD][8] |= HIGH_SCAN_TIME_BIT; /* 紅葉、ラベンダーのみ */
#endif

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
		TxStandardFrameByteCount = 9;
		/*--------*/
		/* F_CODE */
		/*--------*/
		if ((SYB_SelectPollDocumentStatus) || (CHK_UNI_FcodeSecureDocPollTx()) ) {	/* 選択ポーリング蓄積原稿あり */
			MDM_ModemBuffer[InSTD][8] |= SELECTIVE_POLLING_BIT;	/* 選択ポーリング能力 */
		}

		/**	ＤＩＳ ＦＩＦ７バイト目クリア	*/
		MDM_ModemBuffer[InSTD][9] = BIT_CLEAR;

		subaddress_box_setting = CheckSubaddressBox();	/**	サブアドレスＢＯＸ登録のみチェック	*/

		if (subaddress_box_setting) {	/* サブアドレスボックスが登録されているなら */
			/**	拡張フィールドセット（４８ビット）	*/
			MDM_ModemBuffer[InSTD][8] |= EXPAND_FIELD_BIT;

			if (subaddress_box_setting & SUB_SET) {			/* サブアドレスＢＯＸにＳＵＢが登録されている */
				MDM_ModemBuffer[InSTD][9] |= SUBADDRESSING_BIT;	/* サブアドレス能力 */
			}
			if (subaddress_box_setting & PWD_SET) {			/* サブアドレスＢＯＸにＰＷＤが登録されている */
				MDM_ModemBuffer[InSTD][9] |= PASSWORD_BIT;		/* パスワード能力 */
			}
			/**	ＤＩＳ送信バイト数１０セット	*/
			TxStandardFrameByteCount = 10;
		}

#if (0)	/*  by T.Soneoka 1997/12/17 */
//		if (JBIG_Ability) {		/* ＪＢＩＧ能力があるなら */
#endif
		if (AvailableRxCodingMethod == SYS_JBIG_CODE) {		/* ＪＢＩＧ能力があるなら */
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

#else
		/**	ＤＩＳ送信バイト数９セット	*/
		TxStandardFrameByteCount = 9;

#if (0) /*  by T.Soneoka 1997/12/17 */
//		if ((JBIG_Ability) && (RxECM_Ability == ECM_ON)) {		/* ＪＢＩＧ能力があるなら */
#endif
		if ((AvailableRxCodingMethod == SYS_JBIG_CODE)		/* ＪＢＩＧ能力があるなら */
		&& (RxECM_Ability == ECM_ON)) {
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
#endif
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/9/17 K.Kawata */
		if (CL1_ExtFunctionEnableFlag == 1) {
			for (i = 0; i < 9; i++) {
				MDM_ModemBuffer[InSTD][i+3] = CL1_Ext_PC_RxAbility[i+1];
			}
			MDM_ModemBuffer[InSTD][6] &= (~SET_MMR_BIT);
			MDM_ModemBuffer[InSTD][8] &= (~SELECTIVE_POLLING_BIT);

			TxStandardFrameByteCount = 5;
			for (i = 3; i < 10; i++) {	/** 1999.9.17 K.Kawata 2-->3 OCT**/
				if (!(CL1_Ext_PC_RxAbility[i] & 0x80)) {
					break;
				}
				TxStandardFrameByteCount++;
			}
		}
#endif
	}
}
