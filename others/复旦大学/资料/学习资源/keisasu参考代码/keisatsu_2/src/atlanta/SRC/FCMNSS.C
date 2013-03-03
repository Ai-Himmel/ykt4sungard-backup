/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMNSS.C													 */
/*	モジュール	 :															 */
/*				 : MakeNSS_FIF()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 : ＮＳＳ作成												 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
/* このファイルは、ＭＭＬ専用です */
#if(PRO_MAKER == MML)
/*---------------------------------*/
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\SYSCOMF.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\define\UNI_PRO.H"

/* MDM */
#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/07/25 */
#include "\src\atlanta\mdm\orange\define\MDM_DEF.H"
#include "\src\atlanta\mdm\orange\ext_v\MDM_DATA.H"
#include "\src\atlanta\mdm\orange\define\MDM_PRO.H"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/07/25 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\MDM_DEF.H"
#include "\src\atlanta\mdm\r288f\ext_v\MDM_DATA.H"
#include "\src\atlanta\mdm\r288f\define\MDM_PRO.H"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

/*************************************************************************
	module		:[NSSフレーム作成]
	function	:[
		1.NSSフレームセット
		2.モデムバッファにセットしたバイト数セット
	]
	return		:[]
	common		:[
					TxNonStandardFrameByteCount		:
					TxSpeedHandshakeFlag			:
					TxMode							:
					TxCodingMethod					:
					TxMSE_Method					:
					MakerCodeRxFlag					:
					MDM_ModemBuffer				:
					InNS							:
					RxReceiptRequestFlag			:
					TxInterMemoryFlag				:
					CommandFileOptionItem			:
				]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/02]
	author		:[鈴木 郁二]
*************************************************************************/
void MakeNSS_FIF(void)
{
	WORD pos;
	WORD ex1_pos;
	WORD ex2_pos;
	WORD ex3_pos;
	UBYTE i;

	pos = 0;
	ex1_pos = 0;
	ex2_pos = 0;
	ex3_pos = 0;
	i = 0;

	/**	送信バイト数変数初期化	*/			/* 相手機が他社機の場合送信バイト数がクリアされないので外にもってきましょう。そうしないと桐からさつきのポーリング原稿を取り出せない */
	TxNonStandardFrameByteCount = 0;		/* 1995/01/12 Y.Murata */

	if(MakerCodeRxFlag == YES) {
		/**	送信バイト数変数初期化	*/
		TxNonStandardFrameByteCount = 0;

		/**	ＮＳＳアドレスフィールド､制御フィールド､ＦＣＦをモデムバッファにセット	*/
		MDM_ModemBuffer[InNS][0] = ADDRESS_FIELD_DATA;
		MDM_ModemBuffer[InNS][1] = NON_LAST_FRAME_DATA;
		MDM_ModemBuffer[InNS][2] = NSS_F;
		if (DIS_ReceivedFlag == YES) {		/**	ＤＩＳを受信	*/
			MDM_ModemBuffer[InNS][2] |= X_BIT;
		}
		/**	NSS FIF 1,2バイト目クリア	*/
		MDM_ModemBuffer[InNS][3] = BIT_CLEAR;
		MDM_ModemBuffer[InNS][4] = BIT_CLEAR;
		/**	NSS FIF 3 バイト目村田コードセット	*/
		SetMakerCodeFrame();
		/**	モデムバッファライトポインタセット	*/
		pos = 5;
		/**	NSS FIF 4 バイト目クリア	*/
		pos++;	/* pos == 6 */
		MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
		if (CheckTransmitterID_Buf() == YES) {		/**	カナＩＤあり	*/
			/**	TTIビットON	*/
			MDM_ModemBuffer[InNS][pos] |= TTI_ON_BIT;
		}
		if (SYS_RxReceiptRequestFlag == YES) {		/**	受領証要求あり	*/
			/**	受領証要求ビットON	*/
			MDM_ModemBuffer[InNS][pos] |= RCR_ON_BIT;
		}
		switch (TxMSE_Method) {		/**	送信MSEモード	*/
			case MSE1:	/**	MSE1	*/
				/**	MSE1ビットON	*/
				MDM_ModemBuffer[InNS][pos] |= MSE1_MODE_BIT;
				break;
			case MSE2:	/**	MSE2	*/
				/**	MSE2ビットON	*/
				MDM_ModemBuffer[InNS][pos] |= MSE2_MODE_BIT;
				break;
			case SMSE:	/**	SMSE	*/
				/**	SMSEビットON	*/
				MDM_ModemBuffer[InNS][pos] |= SMSE_MODE_BIT;
				break;
			default:
				break;
		}
		if (TxMode == SYS_SFINE) {
			/**	ＳファインビットON	*/
			MDM_ModemBuffer[InNS][pos] |= SFINE_MODE_BIT;
		}
		/* ANZU 短縮ハンドシェークで H-FINE で送る時は、S-FINEもたてる 96/08/12 */
		if ((TxSpeedHandshakeFlag == YES) && ((TxMode == SYS_HFINE) || (TxMode == SYS_E_HFINE)) ) {		/**	送信モードＳファイン	*/
			/**	ＳファインビットON	*/
			MDM_ModemBuffer[InNS][pos] |= SFINE_MODE_BIT;
		}
		if (TxSpeedHandshakeFlag == YES) {		/**	短縮ハンドシェークあり	*/
			/**	短縮ハンドシェークビットON	*/
			MDM_ModemBuffer[InNS][pos] |= SCFR_MODE_BIT;
		}
		/**	拡張ビットON（３２ビット）	*/
		MDM_ModemBuffer[InNS][pos] |= EXPAND_FIELD_BIT;

		if (MDM_ModemBuffer[InNS][pos] & TTI_ON_BIT) {		/**	カナIDビットON	*/
			pos++;
			/**	モデムバッファにカナIDまたは、ＴＴＩをセットする	*/
			pos = SetTransmitterID_Frame(pos);
		}
		/*	拡張フィールド１クリア	*/
		pos++;
		ex1_pos = pos;
		MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
	
		/* F-51に短縮ハンドシェークで送ると、プリンター受信してしまうので条件追加 1997/05/23  By T.Yamaguchi */
		if (TxSpeedHandshakeFlag == YES) {		/**	短縮ハンドシェークあり	*/
			if ((SYS_FaxComTxType == SYS_MEMORY_TRANSMIT)  /**	メモリ送信	*/
			 && (!FCM_PtnrChk_TxToPrinterRxEnable())) {
				MDM_ModemBuffer[InNS][pos] |= MEMORY_OK_BIT;
			}
		}
		else {
			if (TxInterMemoryFlag == YES) {			/**	メモリ送信フラグON	*/
				/**	メモリ容量フィールドビットON	*/
				MDM_ModemBuffer[InNS][pos] |= MEMORY_OK_BIT;
			}
		}
#if 0	/* F-51に短縮ハンドシェークで送ると、プリンター受信してしまうので、モード変更時、エラー */
//		/*--- <Change  May/15/93  for F830 Trouble >---*/
//		if (TxInterMemoryFlag == YES) {			/**	メモリ送信フラグON	*/
//			/**	メモリ容量フィールドビットON	*/
//			MDM_ModemBuffer[InNS][pos] |= MEMORY_OK_BIT;
//		}
//		/*---------------------------------------------*/
#endif

		if (TxCodingMethod == SYS_MMR_CODE) {		/**	送信符号化方式ＭＭＲ	*/
			/**	MMRビットON	*/
			MDM_ModemBuffer[InNS][pos] |= MMR_USE_BIT;
		}
		/**	パスコードフィールドビットON	*/
		MDM_ModemBuffer[InNS][pos] |= PASSCODE_SET_BIT;
		if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {		/**	交信種別 コマンド実行	*/
			if ((CommandFileOptionItem == SYS_SCANNER_SECURE_TX) ||
				(CommandFileOptionItem == SYS_MEMORY_SECURE_TX)) {		/**	コマンドアイテム親展送信	*/
				/**	親展送信ビットON	*/
				MDM_ModemBuffer[InNS][pos] |= SECUREMAIL_BIT;
			}
			else if ((CommandFileOptionItem == SYS_SCANNER_RELAY_BROADCAST) ||
					(CommandFileOptionItem == SYS_MEMORY_RELAY_BROADCAST)) {	/**	コマンドアイテム中継同報指示	*/
				/**	中継同報指示ビットON	*/
				MDM_ModemBuffer[InNS][pos] |= RELAYED_BROADCAST_BIT;
			}
		}
		if (MDM_ModemBuffer[InNS][ex1_pos] & MEMORY_OK_BIT) {		/**	メモリ容量フィールドビットON	*/
			/**	メモリ容量フィールドに００を３バイトセットする　蓄積原稿容量最大	*/
			for (i = 0; i < 3; i++) {
				pos++;
				MDM_ModemBuffer[InNS][pos] = 0x00;/*	700/800 に対してメモリ受信させる 4.Oct'94	*/
			}
		}
		if (MDM_ModemBuffer[InNS][ex1_pos] & SECUREMAIL_BIT) {		/**	親展送信ビットON	*/
			/**	親展フィールドセット	*/
			pos++;
			pos = SetSecureMailFieldFrame(NSS_F, pos);
		}
		if (MDM_ModemBuffer[InNS][ex1_pos] & RELAYED_BROADCAST_BIT) {		/**	中継同報指示ビットON	*/
			/**	中継同報フィールドセット	*/
			pos++;
			pos = SetRelayedBroadcastGroupFrame(pos);
		}
		if (MDM_ModemBuffer[InNS][ex1_pos] & PASSCODE_SET_BIT) {		/**	パスコードフィールドビットON	*/
			/**	パスコードフィールドセット	*/
			pos++;
			pos = SetPasscodeFrame(NSS_F, pos);
		}
		if (TxInterMemoryFlag == YES) {		/**	メモリ送信	*/
			/**	拡張ビット2ON	*/
			MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
			pos++;
			MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
			ex2_pos = pos;
			switch (TxCodingMethod) {		/**	送信符号化方式	*/
				case SYS_MMR_CODE:	/**	MMR	*/
					/**	MMR符号化方式ビットON	*/
					MDM_ModemBuffer[InNS][pos] |= MMR_IN_MEMORY_BIT;
					break;
				case SYS_MR_CODE:	/**	MR	*/
					/**	MR符号化方式ビットON	*/
					MDM_ModemBuffer[InNS][pos] |= MR_IN_MEMORY_BIT;
					break;
				case SYS_MH_CODE:	/**	MH	*/
					/**	MH符号化方式ビットON	*/
					MDM_ModemBuffer[InNS][pos] |= MH_IN_MEMORY_BIT;
					break;
				default:
					/**	符号化方式ビットOFF	*/
					MDM_ModemBuffer[InNS][pos] |= NO_IN_MEMORY_BIT;
					break;
			}
			if ((MDM_ModemBuffer[InNS][ex2_pos] & MASK_MEMORY_MODE) != NO_IN_MEMORY_BIT) {
				/**	メモリ容量フィールドセット	*/
				pos++;
				pos = SetDocumentMemorySizeFrame(pos);/**	原稿のメモリ容量をセット 2.May'94	*/
			}
		}
		if(PostSpeedHandshakeFlag) {/** 後手順短縮ハンドシェークあり *//* 8.Sep'94 Y.Suzuki */
			/**	拡張フィールド２ありビットON	*/
			MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
			if(!ex2_pos) {
				pos++;
				MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
				ex2_pos = pos;
			}
			MDM_ModemBuffer[InNS][ex2_pos] |= POST_MSG_SPEED_BIT;
		}
		if (FCM_HFineCheck() == SYS_E_HFINE) {
			/**	拡張フィールド２ありビットON	*/
			MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
			if(!ex2_pos) {
				pos++;
				MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
				ex2_pos = pos;
			}
			MDM_ModemBuffer[InNS][ex2_pos] |= TX300DPI_BIT;		/* 主走査３００ｄｐｉ送信 */
			SYB_T30_TxFrame300dpiFlag = YES;				/** T30モニタにHｰFine(R12*15.4l/mm)表示に使用 1996/04/10 By T.Y	 */
		}
#if (PRO_DIAG == ENABLE) /* #if is added by H.Kubo 1998/04/02 */
		/* ●ICHOU変更 高速リモート診断 データリード by T.Soneoka 1996/06/17 */
		if (SYS_FaxComType == SYS_REMOTE_DIAG) {
			/**	拡張フィールド２ありビットON	*/
			MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
			if(!ex2_pos) {
				pos++;
				MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
				ex2_pos = pos;
			}
			MDM_ModemBuffer[InNS][ex2_pos] |= SERVICE_UTIL_ON_BIT;
			MDM_ModemBuffer[InNS][ex2_pos] |= SERVICE_UTIL_BIT;
			pos++;
			MDM_ModemBuffer[InNS][pos] = 0x80;
			pos++;
			/* バックアップデータ長を求める＆ＥＣＭバッファにバックアップデータコピー */
			CopyBackUpRAM_ToEcmBuffer();
			MDM_ModemBuffer[InNS][pos] = (UBYTE)(BackUpDataLength & 0x000000ff);
			pos++;
			MDM_ModemBuffer[InNS][pos] = (UBYTE)((BackUpDataLength & 0x0000ff00) >> 8);
			pos++;
			MDM_ModemBuffer[InNS][pos] = (UBYTE)((BackUpDataLength & 0x00ff0000) >> 16);
			pos++;
			MDM_ModemBuffer[InNS][pos] = (UBYTE)((BackUpDataLength & 0xff000000) >> 24);
		}
		if (FCM_HFineCheck() == SYS_EFINE) {
			MDM_ModemBuffer[InNS][ex1_pos] |= EXPAND_FIELD_BIT;
			if(!ex2_pos) {
				pos++;
				MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
				ex2_pos = pos;
			}
			/**	拡張フィールド3ありビットON	*/
			MDM_ModemBuffer[InNS][ex2_pos] |= EXPAND_FIELD_BIT;
			if(!ex3_pos) {
				pos++;
				MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
				ex3_pos = pos;
			}
			MDM_ModemBuffer[InNS][ex3_pos] |= EFINE_MODE_BIT;		/* 300*300送信 */
/*			SYB_T30_TxFrame300dpiFlag = YES;				/@@ T30モニタにHｰFine(R12*15.4l/mm)表示に使用 1996/04/10 By T.Y	 */
		}
#endif /* (PRO_DIAG == ENABLE) */
#if (PRO_CIPHER == ENABLE)
		if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {		/**	交信種別 コマンド実行	*/
			if (CommandFileOptionItem == SYS_CIPHER_TX) {	/* 暗号化送信なら */
				/* 暗号化送信ビットＯＮ */
				if (ex3_pos == 0) {
					pos++;
					ex3_pos = pos;
					MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
					MDM_ModemBuffer[InNS][ex2_pos] |= EXPAND_FIELD_BIT;
				}
				MDM_ModemBuffer[InNS][ex3_pos] |= CIPHER_COM_BIT;
			}
		}
#endif
		/**	独自フレーム送信バイト数セット	*/
		pos++;
		TxNonStandardFrameByteCount = pos;
	}
}


/*************************************************************************
	module		:[HFINE送信]
	function	:[
		1.短縮ハンドシェーク送信、且つ、スキャナ送信、且つ、中間調はＨーＦＩＮＥ

	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/05/15]
	author		:[山口　哲治]
*************************************************************************/
UBYTE FCM_HFineCheck()
{
	if (TxSpeedHandshakeFlag == YES) {		/**	短縮ハンドシェーク送信の時	*/
		if ((SYS_FaxComTxType == SYS_SCANNER_TRANSMIT)
		&& (FirstTxMode == SYS_GRAY64)) {	/* スキャナ送信で且つ中間調のとき */
#if (PRO_CCD == DPI400)
			return (SYS_HFINE);
#endif
#if (PRO_CCD == DPI300)
			return (SYS_E_HFINE);
#endif
#if (PRO_CCD == DPI200)
			return (TxMode);
#endif
		}
	}
	return (TxMode);
}
/* このファイルは、ＭＭＬ専用です */
#endif
