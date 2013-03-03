/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMNSF.C													 */
/*	モジュール	 :															 */
/*				 : MakeNSF_FIF()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 : ＮＳＦ作成												 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\ext_v\ROM_TBL.H"	/* 1997/02/05  By T.Yamaguchi */
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\MEM_PRO.H"
#include "\src\atlanta\define\CTRY_PRO.H"
#include "\src\atlanta\define\CMN_PRO.H"
#include "\src\atlanta\define\STNG_PRO.H"

#include "\src\atlanta\define\SYSMAX.H"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\UNI_PRO.H"

#if (PRO_CIPHER == ENABLE)
#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif

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
	module		:[MML用NSF 作成]
	function	:[
		1.NSFフレームセット
		2.モデムバッファにセットしたバイト数セット
	]
	return		:[]
	common		:[
				TxNonStandardFrameByteCount
				MDM_ModemBuffer
				InNS
				AvailableRxCodingMethod
				TxReceiptRequestFllag
				SYS_FaxComFIP_RxActiveFlag
				RxWidth
				RxECM_Ability
				AvailableRxResolution
				AvailableRxMSE_Method
	]
	condition	:[]
	comment		:[
				ミランも，リモート診断時MML NSFを使用する
					ＳＭＳＥ受信---紅葉のプリンタ受信のみなし
				修正履歴
				94/9/7 後手順ハンドシェーク追加　鈴木郁二
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/03]
	author		:[鈴木 郁二]
*************************************************************************/
void MakeNSF_FIF(void)
{
	WORD pos;
	WORD ex1_pos;
	WORD ex2_pos;
	WORD ex3_pos;
	WORD basic_pos;
	BYTE memory;
	BYTE i;

	i = 0;
	pos = 0;
	ex1_pos = 0;
	ex2_pos = 0;
	ex3_pos = 0;
	basic_pos = 0;
	memory = NO;
	TxNonStandardFrameByteCount = 0;
	/*	ＮＳＦフレーム作成	*/
	MDM_ModemBuffer[InNS][0] = ADDRESS_FIELD_DATA;
	MDM_ModemBuffer[InNS][1] = NON_LAST_FRAME_DATA;
	MDM_ModemBuffer[InNS][2] = NSF_F;
	/**	NSF FIF 1-2バイトクリア	*/
	MDM_ModemBuffer[InNS][3] = BIT_CLEAR;
	MDM_ModemBuffer[InNS][4] = BIT_CLEAR;
	/**	NSF FIF ３バイト目メーカーコード	*/
	SetMakerCodeFrame();
	pos = 5;
	/**	NSF FIF ４バイト目クリア	*/
	pos++;
	basic_pos = pos;
	MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
	if (CheckTransmitterID_Buf() == YES) {		/**	カナIDあり	*/
		/**	カナIDビットNO	*/
		MDM_ModemBuffer[InNS][pos] |= TTI_ON_BIT;
	}
	/* バッファリング受信のある機種は、受領証送信機能削除する 31.Jly'94 Y.Suzuki */
	/**	受領証ビットON	*/
	MDM_ModemBuffer[InNS][pos] |= RCR_ON_BIT;
#if(PRO_FIP == ENABLE)
	if (SYS_FaxComFIP_RxActiveFlag == YES) {		/**	ＦＩＰ受信	*/
		/**	NO MSE	*/;
	}
	else {
#endif
	/*	紅葉のプリンタ受信時のみＳＭＳＥなし	*/
	/*	MSE2 がセットされることはない。*/
	switch (AvailableRxMSE_Method) {		/**	受信可能MSE方式	*/
		case MSE1:	/**	ＭＳＥ１	*/
			/**	ＭＳＥ１ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= MSE1_MODE_BIT;
			break;
		case MSE2:	/**	ＭＳＥ２	*/
			/**	ＭＳＥ１ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= MSE1_MODE_BIT;
			/**	ＭＳＥ２ビットON	*/
			/*MDM_ModemBuffer[InNS][pos] |= MSE2_MODE_BIT;*/
			break;
		case SMSE:	/**	ＳＭＳＥ	*/
			/**	ＭＳＥ１ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= MSE1_MODE_BIT;
			/**	ＭＳＥ２ビットON	*/
			/*MDM_ModemBuffer[InNS][pos] |= MSE2_MODE_BIT;*/
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
		case SYS_HFINE: /** (400 * 400m)  */
		case SYS_E_HFINE: /** ANZU (R12 * 15.4L/mm)	 */
		case SYS_SFINE:	/**	Ｓファイン(R8 * 15.4mm/l)	*/
			/**	Ｓファイン１ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= SFINE_MODE_BIT;
			break;
		default:
			break;
	}
	/**	ＳＣＦＲビットON	*/
	if(SpeedHandshakeRomCheck() == TRUE) {
#if(PRO_SPEED_EX == ENABLE)						/* 95.12.04 By t.yamaguchi */
		if (CHK_UNI_SpeedHandshakeEx() == 0) {		/* 極反検出方式短縮ハンドシェーク */
			MDM_ModemBuffer[InNS][pos] |= SCFR_MODE_BIT;
		}
#else
		MDM_ModemBuffer[InNS][pos] |= SCFR_MODE_BIT;
#endif
	}
	/**	拡張フィールド１ON	*/
	MDM_ModemBuffer[InNS][pos] |= EXPAND_FIELD_BIT;
	if (MDM_ModemBuffer[InNS][pos] & TTI_ON_BIT) {		/**	カナIDビットON	*/
		/**	カナIDまたは、ＴＴＩセット	*/
		pos++;
		pos = SetTransmitterID_Frame(pos);
	}
	/*	拡張フィールド１セット	*/
	/**	拡張フィールド１クリア	*/
	pos++;
	ex1_pos = pos;
	MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
	/*	メモリ残量フィールドビットON	*/

/*----------------------------------------------*/
/* メモリなし機は、NSF内のﾒﾓﾘﾋﾞｯﾄONしない		*/
/*							29.Jun'94 Y.Suzuki	*/
/*----------------------------------------------*/
 #if (PRO_MEM_RX_REJECT == ENABLE)/* 沖電気仕様紅葉のみ 17.Oct'94 Y.Suzuki */
	if(CHK_MemoryReceiveReject()) {	/* メモリスイッチはなくなった */
		memory = NO;
	}
	else{
		if ((CMN_CheckMemoryReceiveEnable() == TRUE) || (RxECM_Ability == ECM_ON)) {	/**	メモリ残量、代行バッファあり または､ＥＣＭあり	*/
			memory = YES;
			MDM_ModemBuffer[InNS][pos] |= MEMORY_OK_BIT;/*桐以外は、基本はプリンタ受信*/
		}
		else{
			memory = NO;
		}
	}
 #else
	if ((CMN_CheckMemoryReceiveEnable() == TRUE) || (RxECM_Ability == ECM_ON)) {		/**	メモリ残量、代行バッファあり または､ＥＣＭあり	*/
		/*	メモリ残量がなくてもＥＣＭなら０ｍｓで受信する。	*/
		/* さつきは、プリンタ受信、メモリ受信切り替えＳＷあり QAT 940706 SATUKI_H 13.Jly'94 Y.Suzuki */
		if(CHK_PrinterRxON() != 0) {/** プリンタ受信スイッチON	メモリスイッチはないので注意 */
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
    #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/22 K.Kawata*/
			if (!((CHK_UNI_V34ReceiveType() == V34_PRX_TO_PRX) || (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX))) {
				MDM_ModemBuffer[InNS][pos] |= MEMORY_OK_BIT;
			}
    #else
			MDM_ModemBuffer[InNS][pos] |= MEMORY_OK_BIT;/*桐以外は、基本はプリンタ受信*/
    #endif
  #endif
		}
	}
	else {
		memory = NO;
	}
 #endif
	if (SYB_DB_PollingDocumentStatus == YES){	/**	検索ポーリングファイルあり	*/
		/**	検索ポーリングビットON	*/
		MDM_ModemBuffer[InNS][pos] |= DATABASE_POLLING_BIT;
	}
	if(CTRY_SecureRx()) {
#if(PRO_MAKER == MML)
 #if(PRO_MEM_RX_REJECT == DISABLE)
	/* リモート診断時 MakeNSF_FIF() FX使用 下記の処理 UNDEF なのではずす 8.Jly'94 Y.Suzuki */
		if ((CheckSecureMailBox() == YES) && (memory == YES)) {		/**	親展ＢＯＸ登録、メモリ残量あり	*/
			/**	親展フィールドビットON	*/
			MDM_ModemBuffer[InNS][pos] |= SECUREMAIL_BIT;
		}
 #else /* 沖電気仕様紅葉のみ */
		if (CheckSecureMailBox() == YES) {		/**	親展ＢＯＸ登録のみチェック、メモリ残量フィールドチェックしない	*/
			/**	親展フィールドビットON	*/
			MDM_ModemBuffer[InNS][pos] |= SECUREMAIL_BIT;
		}
 #endif
#endif
	}
	/*if (CTRY_RelayTx() *	OperationOfCountry[MachineParameter[0]].RelayBroadcastHost == YES	* ) ｺｰﾙする共通関数名を間違えていた */
	/*	↓↓↓↓↓↓↓以下のように修正 24.Apr'95 Y.Suzuki */
	if (CTRY_RelayedTx()/*	OperationOfCountry[MachineParameter[0]].RelayBroadcastHost == YES	*/) {		/**	中継機の機能がある	*/
#if(PRO_MAKER == MML)
 #if(PRO_MEM_RX_REJECT == DISABLE)
	/* リモート診断時 MakeNSF_FIF() FX使用 下記の処理 UNDEF なのではずす 8.Jly'94 Y.Suzuki */
		if ((CheckRelayedBroadcastGroup() == YES) && (memory == YES)) {		/**	中継同報用グループNO、メモリ残量あり	*/
			/**	中継配信ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= RELAYED_BROADCAST_BIT;
		}
 #else /* 沖電気仕様紅葉のみ */
		if (CheckRelayedBroadcastGroup() == YES) {		/**	中継同報用グループNOのみチェック、メモリ残量フィールドチェックなし	*/
			/**	中継配信ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= RELAYED_BROADCAST_BIT;
		}
 #endif
#endif
	}
#if (PRO_FIP == ENABLE)
	if (SYS_FaxComFIP_RxActiveFlag == NO) {		/**	ＦＩＰ受信	*/
#endif
		switch (AvailableRxCodingMethod) {		/**	受信可能符号化方式	*/
#if (PRO_JBIG == ENABLE)
			case SYS_JBIG_CODE:	/** JBIG	*/
#endif
			case SYS_MMR_CODE:	/**	ＭＭＲ	*/
				/**	ＭＭＲ符号化方式ビットON	*/
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
	/*	Ｆ７００との互換を保つためメモリ残量フィールドにＦＦをライト 必ずプリンタ受信する (００ をかいていた）4.Oct'94	*/
	if(MDM_ModemBuffer[InNS][ex1_pos] & MEMORY_OK_BIT) {/**	メモリビットＯＮ	*/
		for (i = 0; i < 3; i++) {
			pos++;
			MDM_ModemBuffer[InNS][pos] = 0xFF;/**	メモリ残ブロック、残ページ共に０ 1.May'94	*/
		}
	}
	if (MDM_ModemBuffer[InNS][ex1_pos] & SECUREMAIL_BIT) {		/**	親展ビットON	*/
#if(PRO_MAKER == MML)
	/* リモート診断時 MakeNSF_FIF() FX使用 下記の処理 UNDEF なのではずす 8.Jly'94 Y.Suzuki */
	/**	親展フィールドセット	*/
		pos++;
		pos = SetSecureMailFieldFrame(NSF_F, pos);
#endif
	}
	/*	拡張フィールド２セット	*/
	pos++;
	ex2_pos = pos;
	/**	拡張フィールド１クリア	*/
	MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
#if (PRO_PRINTER_RX == ENABLE)
	/* 
	** 強制プリンタ受信設定の場合、プリンタ受信優先設定の場合は、メモリビットＯＦＦであるが、
	** 親展ビットと、中継配信ビットをＯＮにするために、memoryはYESになっているので、
	** メモリビットのＯＮ／ＯＦＦで判断します by H.Hirao 1998/12/25
	*/
	if (MDM_ModemBuffer[InNS][ex1_pos] & MEMORY_OK_BIT) {	/** メモリビットＯＮ */
#else
  #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/22 K.Kawata*/
	if (MDM_ModemBuffer[InNS][ex1_pos] & MEMORY_OK_BIT) {	/** メモリビットＯＮ */
  #else
	if (memory == YES) {		/**	メモリ受信かＥＣＭ受信	*/
  #endif
#endif
		/**	拡張フィールド２ありビットON	*/
		MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
#if(PRO_FIP == ENABLE)
		if (SYS_FaxComFIP_RxActiveFlag == YES) {		/**	ＦＩＰ受信	*/
			/**	ＭＨ蓄積ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= MH_IN_MEMORY_BIT;
		}
		else {
#endif
		switch (AvailableRxCodingMethod) {		/**	受信可能符号化方式	*/
#if (PRO_JBIG == ENABLE)
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
				break;
		}
#if(PRO_FIP == ENABLE)
		}
#endif
	}

	if(CHK_UNI_PostSpeedHandshake()) {/** 後手順短縮ハンドシェークあり *//* 7.Sep'94 Y.Suzuki */
		/**	拡張フィールド２ありビットON	*/
		MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
		MDM_ModemBuffer[InNS][ex2_pos] |= POST_MSG_SPEED_BIT;
	}
#if(PRO_SPEED_EX == ENABLE)				/* 95.12.04 By t.yamaguchi */
	/* 受信モードがＦＡＸ待機で着信トーンを出す設定の場合 */
	if ((AttemptRxModeSwitch == SYS_FAX_READY) && (CHK_UNI_SpeedHandshakeEx() != 0) && (SpeedHandshakeRomCheck() == TRUE)) {  /* (CHK_SpeedHandshake() != 0)) */
		/**	拡張フィールド２ありビットON	*/
		MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
		MDM_ModemBuffer[InNS][ex2_pos] |= SPEED_EX_BIT;		/* 着信トーン検出方式短縮ハンドシェーク有効ビットＯＮ */
	}
#endif
#if (PRO_CCD == DPI300)
	if (AvailableRxResolution == SYS_E_HFINE) {
		/**	拡張フィールド２ありビットON	*/
		MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
		MDM_ModemBuffer[InNS][ex2_pos] |= TX300DPI_BIT;		/* 主走査３００ｄｐｉ受信 */
		SYB_T30_TxFrame300dpiFlag = YES;				/** T30モニタにHｰFine(R12*15.4l/mm)表示に使用 1996/04/10 By T.Y	 */
	}
#endif
#if (PRO_DIAG == ENABLE)
	/**	リモート診断ビットＯＮ	*/
	MDM_ModemBuffer[InNS][basic_pos] |= EXPAND_FIELD_BIT;
	MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
	MDM_ModemBuffer[InNS][pos] |= SERVICE_UTIL_BIT;
#endif

	/**	メモリ残量フィールドセット	*/
	if (MDM_ModemBuffer[InNS][ex2_pos] & MMR_IN_MEMORY_BIT) {		/**	メモリ蓄積ビットON	*/
		/**	メモリ残量セット	*/
		pos++;
		pos = SetRestMemoryFrame(NSF_F, pos);
	}
	/*	拡張フィールド3セット	*/
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
	if (SpeedModeChangeRomCheck() == TRUE) {	/* 96/05/24 By T.Yamaguchi */
		pos++;
		ex3_pos = pos;
		/**	拡張フィールド3	クリア	*/
		MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
		/**	拡張フィールド３ありビットON	*/
		MDM_ModemBuffer[InNS][ex2_pos] |= EXPAND_FIELD_BIT;
		MDM_ModemBuffer[InNS][ex3_pos] |= SPEED_MODE_CHANGE_BIT;
	}
#endif
	if (AvailableRxResolution == SYS_E_HFINE) {
		if (ex3_pos == 0) {
			pos++;
			ex3_pos = pos;
			/**	拡張フィールド3	クリア	*/
			MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
			/**	拡張フィールド３ありビットON	*/
			MDM_ModemBuffer[InNS][ex2_pos] |= EXPAND_FIELD_BIT;
		}
		MDM_ModemBuffer[InNS][ex3_pos] |= EFINE_MODE_BIT;
	}
#if (PRO_DIAG == ENABLE)
	if (CHK_RemoteDiagON()) {
		if (ex3_pos == 0) {
			pos++;
			ex3_pos = pos;
			MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
			MDM_ModemBuffer[InNS][ex2_pos] |= EXPAND_FIELD_BIT;
		}
		MDM_ModemBuffer[InNS][ex3_pos] |= NSF_SERVICE_UTIL_ON_BIT;

		pos++;
		MDM_ModemBuffer[InNS][pos++] = 0x84;		/* リモート診断モード 新プロトコル＋バージョンリード */
		MDM_ModemBuffer[InNS][pos++] = 0x00;		/* アドレス */
		MDM_ModemBuffer[InNS][pos++] = 0x00;
		MDM_ModemBuffer[InNS][pos++] = 0x00;		/* オフセット */
		MDM_ModemBuffer[InNS][pos++] = 0x00;
		MDM_ModemBuffer[InNS][pos++] = 0x10;	/* バイト数 */

		for (i = 0; i < (ROM_REVISION_MAX-1); i++ ){
			MDM_ModemBuffer[InNS][pos++] = ROM_Revision[i];
		}
		pos--;	/* 現在のセットした配列のオフセットにセットしなおす */
	}
#endif
#if (PRO_CIPHER == ENABLE)
	if (ScrambleOn) { /* 暗号化通信機能ありなら */
		/* 暗号化受信能力ビットＯＮ */
		if (ex3_pos == 0) {
			pos++;
			ex3_pos = pos;
			MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
			MDM_ModemBuffer[InNS][ex2_pos] |= EXPAND_FIELD_BIT;
		}
		MDM_ModemBuffer[InNS][ex3_pos] |= CIPHER_COM_BIT;
	}
#endif
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/03/31  By T.Yamaguchi */
	if (ex3_pos == 0) {
		pos++;
		ex3_pos = pos;
		MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
		MDM_ModemBuffer[InNS][ex2_pos] |= EXPAND_FIELD_BIT;
	}
	MDM_ModemBuffer[InNS][ex3_pos] |= FLASH_ROM_WRITE_BIT;
#endif
	/**	モデムバッファにセットしたバイト数をセット	*/
	pos++;
	TxNonStandardFrameByteCount = pos;
	return;
}

