/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMNSC.C													 */
/*	モジュール	 :															 */
/*				 : MakeNSC_FIF()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :															 */
/*	概	要		 : ＮＳＣ作成												 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
/* このファイルは、ＭＭＬ専用です */
#if(PRO_MAKER == MML)
/*--------------------------------*/
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\define\SYSCOMF.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\CMN_PRO.H"
#include "\src\atlanta\define\STNG_PRO.H"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\UNI_PRO.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"

/* MDM */
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
#if (PRO_PRINTER_RX == ENABLE)
	#include "\src\atlanta\define\unisw_c.h"	/* added by H.Hirao 1998/12/25 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/5 K.Kawata*/
#include "\src\atlanta\define\unisw_c.h"
#endif
/*************************************************************************
	module		:[NSC 作成]
	function	:[
		1.ＮＳＣフレームセット
		2.モデムバッファにセットしたバイト数を記憶
	]
	return		:[]
	common		:[
			TxNonStandardFrameByteCount
			MDM_ModemBuffer
			InNS
			AvailableRxCodingMethod
			AvailableRxMinimumScanningTime
			SYS_FaxComFIP_RxActiveFlag
			AvailableRxResolution
			RxECM_Ability
			AvailableRxMSE_Method
			SYS_FaxComType
			CommandP->Option.:Item
	]
	condition	:[]
	comment		:[
				ミランは，別ファイルにする　条件コンパイルは、紅葉とさつき、ラベンダー間で使用
					ＳＭＳＥ受信---紅葉のプリンタ受信のみなし
		修正履歴
			1.94/10/31	MSE 能力 MSE2 がONしていた。ポーリング受信時、相手機(SAKURA，RICE)メモリ送信してこない。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/06/11]
	author		:[鈴木 郁二]
*************************************************************************/
/* void far MakeNSC_FIF(void) */
void MakeNSC_FIF(void)
{
	WORD pos;
	WORD ex1_pos;
	WORD ex2_pos;
	WORD ex3_pos;
	BYTE i;
	BYTE memory;

	pos = 0;
	ex1_pos = 0;
	ex2_pos = 0;
	ex3_pos = 0;
	i = 0;
	memory = NO;

	/**	送信バイト数変数初期化	*/
	TxNonStandardFrameByteCount = 0;

	/*	ＮＳＣセット	*/
	MDM_ModemBuffer[InNS][0] = ADDRESS_FIELD_DATA;
	MDM_ModemBuffer[InNS][1] = NON_LAST_FRAME_DATA;
	MDM_ModemBuffer[InNS][2] = NSC_F;
	/**	NSC FIF 1-2バイトクリア	*/
	MDM_ModemBuffer[InNS][3] = BIT_CLEAR;
	MDM_ModemBuffer[InNS][4] = BIT_CLEAR;
	/**	NSC FIF ３バイト目メーカーコード	*/
	SetMakerCodeFrame();
	pos = 5;
	/**	NSC FIF ４バイト目クリア	*/
	pos++;
	MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
	if (CheckTransmitterID_Buf() == YES) {		/**	カナIDあり	*/
		/**	カナIDビットON	*/
		MDM_ModemBuffer[InNS][pos] |= TTI_ON_BIT;
	}
	/**	受領証ビットON	*/
	MDM_ModemBuffer[InNS][pos] |= RCR_ON_BIT;

#if(PRO_FIP == ENABLE)
	if (SYS_FaxComFIP_RxActiveFlag == YES) {		/**	ＦＩＰ受信	*/
		/**	NO MSE	*/;
	}
	else {
#endif
	switch (AvailableRxMSE_Method) {		/**	受信可能MSE方式	*/
			case MSE1:	/**	ＭＳＥ１	*/
			/**	ＭＳＥ１ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= MSE1_MODE_BIT;
			break;
		case MSE2:	/**	ＭＳＥ２	*/
			/**	ＭＳＥ１ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= MSE1_MODE_BIT;
			/**	ＭＳＥ２ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= MSE2_MODE_BIT;
			break;
		case SMSE:	/**	ＳＭＳＥ	*/
			/**	ＭＳＥ１ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= MSE1_MODE_BIT;
			/**	ＭＳＥ２ビットON	*/
			/*MDM_ModemBuffer[InNS][pos] |= MSE2_MODE_BIT; MSE2 ON & MR 蓄積 == F-51 と判断されメモリ送信してこない。 SAKURA RICE 31.Oct'94 Y.Suzuki */
			/**	ＳＭＳＥビットON	*/
			MDM_ModemBuffer[InNS][pos] |= SMSE_MODE_BIT;
			break;
		case NOMSE:	/**	ＮＯ ＭＳＥ	*/
		default:
			break;
	}
#if(PRO_FIP == ENABLE)
	}
#endif

	switch (AvailableRxResolution) {		/**	受信可能線密度	*/
		case SYS_HFINE:	/**	Ｓファイン桐は２種類400*400､R16*15.4l/m	*/
		case SYS_E_HFINE:	/** ANZUの、H-FINEはＳファインビットセットする By t.yamaguchi */
		case SYS_SFINE:	/**	Ｓファイン(8*15.4)	*/
			/**	ＳファインビットON	*/
			MDM_ModemBuffer[InNS][pos] |= SFINE_MODE_BIT;
			break;
		default:
			break;
	}
	/**	ＳＣＦＲビットON	*/
	MDM_ModemBuffer[InNS][pos] |= SCFR_MODE_BIT;
	/**	拡張フィールド１ON	*/
	MDM_ModemBuffer[InNS][pos] |= EXPAND_FIELD_BIT;
	/**	パスコードフレームセット	*/
	pos++;
	pos = SetPasscodeFrame(NSC_F, pos);

	if (MDM_ModemBuffer[InNS][pos-4] & TTI_ON_BIT) {		/**	カナID表示ビットON	*/
		/**	カナIDまたは、ＴＴＩをモデムバッファにセット	*/
		pos++;
		pos = SetTransmitterID_Frame(pos);
	}
	/*	拡張フィールド１	*/
	pos++;
	ex1_pos = pos;
	/**	ビットクリア	*/
	MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
	/**	メモリ残量フィールドビットON	*/
 #if (PRO_MEM_RX_REJECT == ENABLE)/* 沖電気仕様紅葉のみ 17.Oct'94 Y.Suzuki */

 #if (0)	/* modifiedbythonda1999/02/25 */
	if(CHK_MemoryReceiveReject()) {	/*MEM_SWはなくなった */
		memory = NO;
	}
	else{
 #endif

		if ((CMN_CheckMemoryReceiveEnable() == TRUE) || (RxECM_Ability == ECM_ON)) {		/**	メモリ残量、代行バッファあり または､ＥＣＭあり	*/
			memory = YES;
			MDM_ModemBuffer[InNS][pos] |= MEMORY_OK_BIT;/*桐以外は、基本はプリンタ受信*/
		}
		else{
			memory = NO;
		}

 #if (0)	/* modifiedbythonda1999/02/25 */
	}
 #endif

 #else
	if ((CMN_CheckMemoryReceiveEnable() == TRUE) || (RxECM_Ability == ECM_ON)) {		/**	メモリ残量あり	*/
		/* さつきは、プリンタ受信、メモリ受信切り替えＳＷあり QAT 940706 SATUKI_H 21.Jly'94 Y.Suzuki */
		if(CHK_PrinterRxON() != 0) {/** プリンタ受信スイッチON */
			memory = NO;
		}
		else {
			memory = YES;
  #if (PRO_PRINTER_RX == ENABLE)
  			/*
  			** 強制メモリ受信設定の場合、または、メモリ受信優先設定の場合、メモリビットをセット
  			** added by H.Hirao 1998/12/25
  			*/
  			if ((CHK_UNI_V17ReceiveType() == V17_MRX_TO_MRX) || (CHK_UNI_V17ReceiveType() == V17_MRX_TO_PRX)) {
				MDM_ModemBuffer[InNS][pos] |= MEMORY_OK_BIT;
			}
  #else
    #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/5 K.Kawata*/
			if (!((CHK_UNI_V34ReceiveType() == V34_PRX_TO_PRX) || (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX))) {
				MDM_ModemBuffer[InNS][pos] |= MEMORY_OK_BIT;
			}
    #else
			MDM_ModemBuffer[InNS][pos] |= MEMORY_OK_BIT;
    #endif
  #endif
		}
	}
	else {
		memory = NO;
	}
 #endif
	if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {		/**	交信種別 コマンド実行	*/
		if (CommandFileOptionItem == SYS_DB_POLLING_RX) {		/**	データベースポーリング	*/
			/**	データベースポーリングビットON	*/
			MDM_ModemBuffer[InNS][pos] |= DATABASE_POLLING_BIT;
		}
	}
#if (PRO_FIP == ENABLE)
	if (SYS_FaxComFIP_RxActiveFlag == NO) {		/**	ＦＩＰ受信ではない	*/
#endif
		switch (AvailableRxCodingMethod) {		/**	受信符号化方式	*/
#if (PRO_JBIG == ENABLE) /* JBIG 利用可能のときは、MMR も利用可能であるとします。Added by H.Kubo 1998/05/11 */
			case SYS_JBIG_CODE:	/** JBIG	*/
#endif
			case SYS_MMR_CODE:	/**	ＭＭＲ	*/
				/**	MMRビットON	*/
				MDM_ModemBuffer[InNS][pos] |= MMR_USE_BIT;
				break;
			case SYS_MR_CODE:	/**	ＭＲ	*/
			case SYS_MH_CODE:	/**	ＭＨ	*/
			default:
				break;
		}
#if (PRO_FIP == ENABLE)
	}
#endif
	/**	モデムバッファにＦＦ３バイトセット(F700との互換を保つため) 4.Oct'94 FF に変更	*/
	if(MDM_ModemBuffer[InNS][ex1_pos] & MEMORY_OK_BIT) {/**	メモリビットＯＮ	*/
		for ( i = 0; i < 3; i++) {
			pos++;
			MDM_ModemBuffer[InNS][pos] = 0xFF;/* 必ずプリンタ受信 */
		}
	}
	if (MDM_ModemBuffer[InNS][ex1_pos] & DATABASE_POLLING_BIT) {		/**	検索ポーリングビットON	*/
		/**	検索ポーリングフィールドセット	*/
		pos++;
		pos = SetDatabasePollingDataFrame(pos);
	}
	/*	拡張フィールド２	*/
	pos++;
	ex2_pos = pos;
	MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
#if (PRO_PRINTER_RX == ENABLE)
	/* 
	** 強制プリンタ受信設定の場合、プリンタ受信優先設定の場合は、メモリビットＯＦＦであるが、
	** 親展ビットと、中継配信ビットをＯＮにするために、memoryはYESになっているので、
	** メモリビットのＯＮ／ＯＦＦで判断します by H.Hirao 1998/12/25
	*/
	if (MDM_ModemBuffer[InNS][ex1_pos] & MEMORY_OK_BIT) {	/** メモリビットＯＮ */
#else
  #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/5 K.Kawata*/
	if (MDM_ModemBuffer[InNS][ex1_pos] & MEMORY_OK_BIT) {	/** メモリビットＯＮ */
  #else
	if (memory == (BYTE)YES) {		/**	メモリ受信かＥＣＭ受信	*/
  #endif
#endif
		/**	拡張フィールド２ビットON	*/
		MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
		switch (AvailableRxCodingMethod) {		/**	受信可能符号化方式	*/
#if (PRO_JBIG == ENABLE) /* JBIG 利用可能のときは、MMR も利用可能であるとします。Added by H.Kubo 1998/05/11 */
			case SYS_JBIG_CODE:	/** JBIG	*/
#endif
			case SYS_MMR_CODE:	/**	ＭＭＲ	*/
				/**	ＭＭＲ蓄積ビットON	*/
				MDM_ModemBuffer[InNS][pos] |= MMR_IN_MEMORY_BIT;
				break;
			case SYS_MR_CODE:	/**	ＭＲ	*/
				/**	ＭＲ蓄積ビットON	*/
				MDM_ModemBuffer[InNS][pos] |= MR_IN_MEMORY_BIT;
				break;
			case SYS_MH_CODE:	/**	ＭＨ	*/
				/**	ＭＨ蓄積ビットON	*/
				MDM_ModemBuffer[InNS][pos] |= MH_IN_MEMORY_BIT;
				break;
			default:
				/**	蓄積ＮＯ	*/
				MDM_ModemBuffer[InNS][pos] |= NO_IN_MEMORY_BIT;
		}
		if (MDM_ModemBuffer[InNS][ex2_pos] & MMR_IN_MEMORY_BIT) {		/**	ＭＭＲ蓄積ビットON	*/
			/**	メモリ残量セット	*/
			pos++;
			pos = SetRestMemoryFrame(NSC_F, pos);
		}
	}
	if(CHK_UNI_PostSpeedHandshake()) {/** 後手順短縮ハンドシェークあり *//* 8.Sep'94 Y.Suzuki */
		/**	拡張フィールド２ありビットON	*/
		MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
		MDM_ModemBuffer[InNS][ex2_pos] |= POST_MSG_SPEED_BIT;
	}
 #if (PRO_CCD == DPI300)
	if (AvailableRxResolution == SYS_E_HFINE) {
		/**	拡張フィールド２ありビットON	*/
		MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
		MDM_ModemBuffer[InNS][ex2_pos] |= TX300DPI_BIT;
		SYB_T30_TxFrame300dpiFlag = YES;				/** T30モニタにHｰFine(R12*15.4l/mm)表示に使用 1996/04/10 By T.Y	 */
	}
 #endif
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
	if (SpeedModeChangeRomCheck() == TRUE) {	/* 96/05/24 By T.Yamaguchi */
		/*	拡張フィールド3セット	*/
		pos++;
		ex3_pos = pos;
		/**	拡張フィールド3	クリア	*/
		MDM_ModemBuffer[InNS][ex3_pos] = BIT_CLEAR;
		/**	拡張フィールド３ありビットON	*/
		MDM_ModemBuffer[InNS][ex2_pos] |= EXPAND_FIELD_BIT;
		MDM_ModemBuffer[InNS][ex3_pos] |= SPEED_MODE_CHANGE_BIT;
	}
#endif
	if (CHK_UNI_ExcellentFIne()) {
		if (ex3_pos == 0) {
			pos++;
			ex3_pos = pos;
			/**	拡張フィールド3	クリア	*/
			MDM_ModemBuffer[InNS][ex3_pos] = BIT_CLEAR;
			/**	拡張フィールド３ありビットON	*/
			MDM_ModemBuffer[InNS][ex2_pos] |= EXPAND_FIELD_BIT;
		}
		MDM_ModemBuffer[InNS][ex3_pos] |= EFINE_MODE_BIT;
	}
	/**	モデムバッファにセットしたバイト数をセット	*/
	pos++;
	TxNonStandardFrameByteCount = pos;
	return;
}

/* このファイルは、ＭＭＬ専用です */
#endif
