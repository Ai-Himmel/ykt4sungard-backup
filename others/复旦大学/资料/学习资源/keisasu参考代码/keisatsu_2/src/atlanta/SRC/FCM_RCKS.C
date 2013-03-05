/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATALNAT		ANZUを移植									 */
/*	ファイル名	 : FCM_RCKS.C												 */
/*	モジュール	 :															 */
/*				 : SetRxBaudRate()											 */
/*				 : SetRxCode()												 */
/*				 : SetRxMode()												 */
/*				 : SetRxPaperLength()										 */
/*				 : CheckRxModeUpperFine()									 */
/*				 : SetRxMinimumCommunicationTime()							 */
/*				 : SetRxECM_Mode()											 */
/*				 : SetRxMSE_Mode()											 */
/*				 : SetRxPaperWidth()										 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : 受信時ＦＩＦセット										 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\CL1_DATA.H"
#endif
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\UNI_PRO.H"

#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/06 */
#include "\src\atlanta\define\man_pro.h"
#endif /* (PRO_TX_SPEED == V34) */


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
#include "\src\atlanta\define\mntsw_c.h"		/* 1997/12/16  By T.Yamaguchi */

/*************************************************************
	module		:[受信ボーレートの確定]
	function	:[
		ＤＣＳのビットと受信能力より受信ボーレートを確定する
	]
	return		:[
		受信ボーレート確定 YES/受信ボーレート確定できず NO
	]
	common		:[
		MDM_ModemBuffer
		AvailableRxBaudRate
		AttemptRxBaudRate
		fcom_v17exe
		StdFrmPos
	]
	condition	:[]
	comment		:[桐、紅葉--14400-2400　さつき、ラベンダー--9600-2400 受信可能ボーレートに皐月　ラベンダーは、12000､14400は入らないはず、なので特に条件コンパイルはいれない]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE  SetRxBaudRate(void)
{
#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/06 */
	if (SYS_V34ProcedureExecuting() == 1) {	/** Ｖ３４で交信中はＤＣＳのデータレイトビットは０固定 */
		if (MDM_ModemBuffer[StdFrmPos][4] & MASK_BAUDRATE) {
			/* 無視 */
			return(YES);
		}
		else {
			return(YES);
		}
	}
#endif /* (PRO_TX_SPEED == V34) */

	switch (MDM_ModemBuffer[StdFrmPos][4] & MASK_BAUDRATE) {		/**	DCS FIF ボーレートビットチェック	*/
		case DATA_V17_14400BPS_BIT:	/**	V17-14400	*/
			if (AvailableRxBaudRate == BPS14400_V17) {		/**	受信可能ボーレート V17-14400	*/
				/**	確定受信ボーレート V17-14400	*/
				AttemptRxBaudRate = BPS14400_V17;
				break;
			}
		case DATA_V17_12000BPS_BIT:	/**	V17-12000	*/
			if ((AvailableRxBaudRate == BPS14400_V17) ||
				(AvailableRxBaudRate == BPS12000_V17)) {		/**	受信可能ボーレート V17-14400または、V17-12000	*/
				/**	確定受信ボーレート V17-12000	*/
				AttemptRxBaudRate = BPS12000_V17;
				break;
			}
		case DATA_V33_14400BPS_BIT:	/**	V33-14400	*/
			if ((AvailableRxBaudRate == BPS14400_V17) ||
				(AvailableRxBaudRate == BPS14400_V33)) {		/**	受信可能ボーレート V17-14400または、V17-14400	*/
				/**	確定受信ボーレート V33-14400	*/
				AttemptRxBaudRate = BPS14400_V33;
				break;
			}
		case DATA_V33_12000BPS_BIT:	/**	V33-12000	*/
			if ((AvailableRxBaudRate == BPS14400_V17) ||
				(AvailableRxBaudRate == BPS12000_V17) ||
				(AvailableRxBaudRate == BPS14400_V33) ||
				(AvailableRxBaudRate == BPS12000_V33)) {		/**	受信可能ボーレート V17-14400または、V33-14400または、V17-12000または、V33ー12000	*/
				/**	確定受信ボーレート V33-12000	*/
				AttemptRxBaudRate = BPS12000_V33;
				break;
			}
		case DATA_V17_9600BPS_BIT:	/**	V17-9600	*/
			if ((AvailableRxBaudRate == BPS14400_V17) ||
				(AvailableRxBaudRate == BPS12000_V17) ||
				(AvailableRxBaudRate == BPS14400_V33) ||
				(AvailableRxBaudRate == BPS12000_V33) ||
				(AvailableRxBaudRate == BPS9600_V17)) {		/**	受信可能ボーレート V17-14400または、V33-14400または、V17-12000または、V33ー12000または、V17-9600	*/
				/**	確定受信ボーレート V17-9600	*/
				AttemptRxBaudRate = BPS9600_V17;
				break;
			}
		case DATA_V17_7200BPS_BIT:	/**	V17-7200	*/
			if ((AvailableRxBaudRate == BPS14400_V17) ||
				(AvailableRxBaudRate == BPS12000_V17) ||
				(AvailableRxBaudRate == BPS14400_V33) ||
				(AvailableRxBaudRate == BPS12000_V33) ||
				(AvailableRxBaudRate == BPS9600_V17)  ||
				(AvailableRxBaudRate == BPS7200_V17)) {		/**	受信可能ボーレート V17-14400または、V33-14400または、V17-12000または、V33ー12000または、V17-9600または、V17-7200	*/
				/**	確定受信ボーレート V17-7200	*/
				AttemptRxBaudRate = BPS7200_V17;
				break;
			}
		case DATA_V29_9600BPS_BIT:	/**	V29-9600	*/
			if ((AvailableRxBaudRate == BPS14400_V17) ||
				(AvailableRxBaudRate == BPS12000_V17) ||
				(AvailableRxBaudRate == BPS14400_V33) ||
				(AvailableRxBaudRate == BPS12000_V33) ||
				(AvailableRxBaudRate == BPS9600_V17)  ||
				(AvailableRxBaudRate == BPS7200_V17)  ||
				(AvailableRxBaudRate == BPS9600_V29)) {		/**	受信可能ボーレート V17-14400または、V33-14400または、V17-12000または、V33ー12000または、V17-9600または、V17-7200または、V29-9600	*/
				/**	確定受信ボーレート V29-9600	*/
				AttemptRxBaudRate = BPS9600_V29;
				/**	V17ビット クリア	*/
				/* com_v17exe = 0; */
				break;
			}
		case DATA_V29_7200BPS_BIT:	/**	V29-7200	*/
			if ((AvailableRxBaudRate == BPS14400_V17) ||
				(AvailableRxBaudRate == BPS12000_V17) ||
				(AvailableRxBaudRate == BPS14400_V33) ||
				(AvailableRxBaudRate == BPS12000_V33) ||
				(AvailableRxBaudRate == BPS9600_V17)  ||
				(AvailableRxBaudRate == BPS7200_V17)  ||
				(AvailableRxBaudRate == BPS9600_V29)  ||
				(AvailableRxBaudRate == BPS7200_V29)) {		/**	受信可能ボーレート V17-14400または、V33-14400または、V17-12000または、V33ー12000または、V17-9600または、V17-7200または、V29-9600	または、V29-7200	*/
				/**	確定受信ボーレート V29-7200	*/
				AttemptRxBaudRate = BPS7200_V29;
				break;
			}
		case DATA_V27_4800BPS_BIT:	/**	V27-4800	*/
			if ((AvailableRxBaudRate == BPS14400_V17) ||
				(AvailableRxBaudRate == BPS12000_V17) ||
				(AvailableRxBaudRate == BPS14400_V33) ||
				(AvailableRxBaudRate == BPS12000_V33) ||
				(AvailableRxBaudRate == BPS9600_V17)  ||
				(AvailableRxBaudRate == BPS7200_V17)  ||
				(AvailableRxBaudRate == BPS9600_V29)  ||
				(AvailableRxBaudRate == BPS7200_V29)  ||
				(AvailableRxBaudRate == BPS4800_V27)) {		/**	受信可能ボーレート V17-14400または、V33-14400または、V17-12000または、V33ー12000または、V17-9600または、V17-7200または、V29-9600	または、V29-7200または、4800	*/
				/**	確定受信ボーレート 4800	*/
				AttemptRxBaudRate = BPS4800_V27;
				break;
			}
		case DATA_V27_2400BPS_BIT:	/**	V27-2400	*/
			if ((AvailableRxBaudRate == BPS14400_V17) ||
				(AvailableRxBaudRate == BPS12000_V17) ||
				(AvailableRxBaudRate == BPS14400_V33) ||
				(AvailableRxBaudRate == BPS12000_V33) ||
				(AvailableRxBaudRate == BPS9600_V17)  ||
				(AvailableRxBaudRate == BPS7200_V17)  ||
				(AvailableRxBaudRate == BPS9600_V29)  ||
				(AvailableRxBaudRate == BPS7200_V29)  ||
				(AvailableRxBaudRate == BPS4800_V27)	  ||
				(AvailableRxBaudRate == BPS2400_V27)) {		/**	受信可能ボーレート V17-14400または、V33-14400または、V17-12000または、V33ー12000または、V17-9600または、V17-7200または、V29-9600	または、V29-7200または、4800または、2400	*/
				/**	確定受信ボーレート 2400	*/
				AttemptRxBaudRate = BPS2400_V27;
				break;
			}
		default:
			return(NO);
	}
	return(YES);
}

/*************************************************************
	module		:[受信符号化方式確定]
	function	:[
		ＤＣＳのビット受信側復号化方式を確定する
	]
	return		:[
		復号化方式確定---YES／復号化方式確定せず---NO
	]
	common		:[
		RxCodingMethod
		MDM_ModemBuffer
		RxStandardFrameByteCount
		StdFrmPos
		AvailableRxCodingMethod
		RxSpeedHandshakeFlag
		RxECM_Mode
		MakerCodeRxFlag
		NonStdFrmPos
		SYS_DocBlock.Src.Code
		SYS_DocBlock.Dst.Code
	]
	condition	:[]
	comment		:[桐、紅葉-MH、MR、MMR	さつき、ラベンダー-MH、MR　受信可能符号化方式に自分の処理できない符号化方式が入ることはないので条件コンパイルは入れない]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE	SetRxCode(void)
{
	WORD pos;
	WORD code;

	pos = 0;
	code = 0;

#if 0	/* (PRO_CIPHER == ENABLE) 暗号化受信時においても相手機の送信能力で受信する 1998/04/21  By T.Yamaguchi */
//	/* 暗号化受信の場合は強制的にＥＣＭのＭＭＲで受信する 1997/10/01  By T.Yamaguchi */
//	if (SYS_RxMemoryFileItem == SYS_MEM_CIPHER_RX_FILE) {	/* 暗号化受信 */
//#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */
//		RxCodingMethod = AvailableRxCodingMethod;
//#else
//		/**	確定復号化方式 MMR	*/
//		RxCodingMethod = SYS_MMR_CODE;
//#endif
//		/**	コマンドsrc.d_code に確定復号化方式セット	*/
//		SYS_DocBlock.Src.Code = (BYTE)RxCodingMethod;
//		/**	コマンドdst.d_code に確定復号化方式セット	*/
//		SYS_DocBlock.Dst.Code = (BYTE)RxCodingMethod;
//		return(YES);
//	}
#endif
	/**	確定復号化方式 MH	*/
	RxCodingMethod = SYS_MH_CODE;
	if (MDM_ModemBuffer[StdFrmPos][4] & SET_MR_BIT) {		/**	DCS MRビットON	*/
		switch (AvailableRxCodingMethod) {		/**	受信可能復号化方式	*/
			case SYS_MH_CODE:	/**	MH	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
					return(NO);
				}
				break;
			case SYS_MR_CODE:	/**	MR	*/
			case SYS_MMR_CODE:	/**	MMR	*/
#if (PRO_JBIG == ENABLE)	/*  by H.Kubo 1998/01/07 */
			case SYS_JBIG_CODE: /** JBIG */
			default:
#endif
				/**	確定復号化方式 MR	*/
				RxCodingMethod = SYS_MR_CODE;
				break;
		}
	}
	if ((RxStandardFrameByteCount > 6) &&
		(MDM_ModemBuffer[StdFrmPos][6] & SET_MMR_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT)) {		/**	 MMRビットON	*/
		if (RxECM_Mode == ECM_OFF) {		/**	受信ECMモード OFF	*/
			if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
				return(NO);
			}
		}
		switch (AvailableRxCodingMethod) {		/**	受信可能復号化方式	*/
			case SYS_MH_CODE:	/**	MH	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
				break;
			case SYS_MR_CODE:	/**	MR	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
				break;
			case SYS_MMR_CODE:	/**	MMR	*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */
			case SYS_JBIG_CODE:
#endif
				/**	確定復号化方式 MMR	*/
				RxCodingMethod = SYS_MMR_CODE;
				break;
		}
	}
#if(PRO_MAKER == MML)
	/* 標準ﾌﾚｰﾑMMRﾋﾞｯﾄﾁｪｯｸのif文の中で見ていた。標準でMMRの能力を持ってなければ、MMLのMMRﾁｪｯｸに入ってこれなかった。	*/
	/* F-51 とMMRで交信できなかった点を修正 13.Mar'95 Y.Suzuki														*/
	if ((MakerCodeRxFlag == YES) &&
		(MDM_ModemBuffer[NonStdFrmPos][6] & EXPAND_FIELD_BIT) &&
		(RxNonStandardFrameByteCount > 7)) {		/**	独自フレーム受信チェック	*/
		if (MDM_ModemBuffer[NonStdFrmPos][6] & TTI_ON_BIT) {		/**	独自フレームTTIビットON	*/
			/**	独自フレームリードポインター 23	*/
			pos = 7 + 16;
		}
		else {		/**	独自フレームTTIビットOFF	*/
			/**	独自フレームリードポインター 7	*/
			pos = 7;
		}
		if (CheckMMRinNonStandardFrame(pos) == YES) {		/**	独自MMRビットON	*/
			if (RxECM_Mode == ECM_OFF) {		/**	受信ECMモード OFF	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			switch (AvailableRxCodingMethod) {		/**	受信可能復号化方式	*/
				case SYS_MH_CODE:	/**	MH	*/
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
						return(NO);
					}
					break;
				case SYS_MR_CODE:	/**	MR	*/
					/**	確定復号化方式 MR	*/
					RxCodingMethod = SYS_MR_CODE;
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなけらばエラー	*/
						return(NO);
					}
					break;
				case SYS_MMR_CODE:	/**	MMR	*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */
				case SYS_JBIG_CODE:
#endif
					/**	確定復号化方式 MMR	*/
					RxCodingMethod = SYS_MMR_CODE;
					break;
			}
		}
	}
#endif
#if (PRO_FIP == ENABLE)
	if (SYS_FaxComFIP_RxActiveFlag == YES) {		/**	FIP受信中	*/
		/**	確定復号化方式 MH	*/
		RxCodingMethod = SYS_MH_CODE;
	}
#endif
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */
	if ((RxStandardFrameByteCount > 12) &&
		(MDM_ModemBuffer[StdFrmPos][12] & JBIG_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][11] & EXPAND_FIELD_BIT) &&
		(RxECM_Mode == ECM_ON) &&
		(AvailableRxCodingMethod == SYS_JBIG_CODE)) {
		RxCodingMethod = SYS_JBIG_CODE;
	}
#endif

	/**	コマンドsrc.d_code に確定復号化方式セット	*/
	SYS_DocBlock.Src.Code = (BYTE)RxCodingMethod;
	/**	コマンドdst.d_code に確定復号化方式セット	*/
	SYS_DocBlock.Dst.Code = (BYTE)RxCodingMethod;
	return(YES);
}

/*************************************************************
	module		:[SetRxMode()]
	function	:[
		受信側線密度を確定する
	]
	return		:[
		線密度確定---YES/確定せず---NO
	]
	common		:[
		RxMode
		AvailableRxResolution
		RxStandardFrameByteCount
		MDM_ModemBuffer
		StdFrmPos
		MakerCodeRxFlag
		RxSpeedHandshakeFlag
		RxNonStandardFrameByteCount
		SYS_DocBlock:.Src.Mode
		SYS_DocBlock:.Dst.Mode
	]
	condition	:[]
	comment		:[
					ANZUの受信は、ミリのみ
					ビットをチェックする所を関数に変更 By T.Y
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/31]
	author		:[t.yamaguchi]
*************************************************************/
UBYTE	SetRxMode(void)
{
	/*	確定受信モード ノーマルセット	*/
	RxMode = SYS_NORMAL;/* ページ毎のモードチェンジのため */
	/**	インチ／ミリビットにミリセット	*/
	RxModeMethod = SYS_METRIC;

	switch (AvailableRxResolution) {		/**	受信可能モード	*/
		case SYS_HFINE	:	/**	ハイパーファイン	*/
			if (RxStdFrame_FineBitCheck() == 1) {
				/**	受信モードファイン	*/
				RxMode = SYS_FINE;
			}
			if (RxStdFrame_SuperFineBitCheck()) {
				/**	受信モードスーパーファイン	*/
				RxMode = SYS_SFINE;
			}
			if (RxStdFrame_OtherFineBitCheck()) {
				/**	確定受信モード OTHER-FINE	*/
				/* RxMode = SYS_OFINE; */
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);	/* 現在ＡＮＺＵは対応していないのでコンパチエラーにする */
				}
				RxMode = SYS_SFINE;	/* SCFRで宣言しているモードをセットする 96/08/09 By T.Yamaguchi */
			}
			if (RxStdFrame_HyperFineBitCheck() == 1) {	/** 400*400dpi ビットチェック */
				/** 受信モードハイパーファイン	*/
				RxMode = SYS_HFINE;
			}
			if (Partner300dpiAbility == YES) {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			if (PartnerEFineAbility == YES) {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			break;
		case SYS_E_HFINE	:	/**	杏ハイパーファイン R12*15.4L/mm	*/
			if (RxStdFrame_FineBitCheck() == 1) {
				/**	受信モードファイン	*/
				RxMode = SYS_FINE;
			}
			if (RxStdFrame_SuperFineBitCheck()) {
				/**	確定受信モード スーパーファイン	*/
				RxMode = SYS_SFINE;
			}
			if (RxStdFrame_OtherFineBitCheck()) {
				/**	確定受信モード OTHER-FINE	*/
				/* RxMode = SYS_OFINE; */
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);	/* 現在ＡＮＺＵは対応していないのでコンパチエラーにする */
				}
				RxMode = SYS_SFINE;	/* SCFRで宣言しているモードをセットする 96/08/09 By T.Yamaguchi */
			}
			if (RxStdFrame_HyperFineBitCheck() == 1) {	/** 400*400dpi ビットチェック */
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
				RxMode = SYS_SFINE;	/* SCFRで宣言しているモードをセットする 96/08/09 By T.Yamaguchi */
			}
			if (Partner300dpiAbility == YES) {
				RxMode = SYS_E_HFINE;		/**	杏ハイパーファイン R12*15.4L/mm	*/
			}
			if (PartnerEFineAbility == YES) {
				RxMode = SYS_EFINE;		/**	杏エクセレントファイン R12*11.55L/mm	*/
			}
			break;
		case SYS_SFINE:	/**	スーパーファイン	*/
			if (RxStdFrame_FineBitCheck() == 1) {
				/**	受信モードファイン	*/
				RxMode = SYS_FINE;
			}
			if (RxStdFrame_SuperFineBitCheck() == 1) {
				/**	送信モードスーパーファイン	*/
				RxMode = SYS_SFINE;
			}
			if (Partner300dpiAbility == YES) {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			if (PartnerEFineAbility == YES) {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			if (RxStdFrame_OtherFineBitCheck()) {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);	/* 現在ＡＮＺＵは対応していないのでコンパチエラーにする */
				}
				RxMode = SYS_SFINE;	/* SCFRで宣言しているモードをセットする 96/08/09 By T.Yamaguchi */
			}
			if (RxStdFrame_HyperFineBitCheck() == 1) {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
				RxMode = SYS_SFINE;	/* SCFRで宣言しているモードをセットする 96/08/09 By T.Yamaguchi */
			}
			break;
#if (PRO_FORCE_FINE_RX_SWITCH == ENABLE) /* 試験的にサカキで入れます。 by H.Kubo 1998/10/06 */
		case SYS_FINE:	/**	ファイン	*/
			if (RxStdFrame_FineBitCheck() == 1) {
				/**	受信モードファイン	*/
				RxMode = SYS_FINE;
			}
			if (RxStdFrame_SuperFineBitCheck()) {
				/**	受信モードスーパーファイン	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			if (Partner300dpiAbility == YES) {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			if (PartnerEFineAbility == YES) {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			if (RxStdFrame_OtherFineBitCheck()) {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);	/* 現在ＡＮＺＵは対応していないのでコンパチエラーにする */
				}
			}
			if (RxStdFrame_HyperFineBitCheck() == 1) {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			break;
#endif
		default:
			return(NO);
	}
#if (0)	/* (PRO_HQ_MODE == ENABLE) */	/* POPLARの場合はインチで送って来てもミリで受ける 1997/01/13  By T.Yamaguchi */
** 	if ((CHK_UNI_Inch_TRx()) &&	/* インチ受信能力ありの時 且つ インチビットＯＮ */
** 		(RxStdFrame_InchBitOnCheck() != 0)) {
** 		/**	インチ／ミリにインチセット（インチに変換）	*/
** 		RxModeMethod = SYS_INCH;
** 	}
** 	else {
** 		/**	インチ／ミリビットにミリセット（ミリに変換）	*/
** 		RxModeMethod = SYS_METRIC;
** 	}
#endif

	/**	コマンド.src.d_mode に確定受信モードセット	*/
	SYS_DocBlock.Src.Mode = RxMode;
	/**	コマンド.dst.d_mode に確定受信モードセット	*/
	SYS_DocBlock.Dst.Mode = RxMode;

	SYS_DocBlock.ModeMethod = RxModeMethod;

	return(YES);
}


#if 0	/* ↑に修正 '96.01.31 By t.yamaguchi */
/*************************************************************
	module		:[SetRxMode()]
	function	:[
		受信側線密度を確定する
	]
	return		:[
		線密度確定---YES/確定せず---NO
	]
	common		:[
		RxMode
		AvailableRxResolution
		RxStandardFrameByteCount
		MDM_ModemBuffer
		StdFrmPos
		MakerCodeRxFlag
		RxSpeedHandshakeFlag
		RxNonStandardFrameByteCount
		SYS_DocBlock:.Src.Mode
		SYS_DocBlock:.Dst.Mode
	]
	condition	:[]
	comment		:[	桐、紅葉--16/64階調　さつき、ラベンダー--16/32　SEPは、像域分離をあらわす
					受信モード能力にハイパーファインがセットされることはない。条件コンパイル不要。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE	SetRxMode(void)
{
	/*	確定受信モード ノーマルセット	*/
	RxMode = SYS_NORMAL;/* ページ毎のモードチェンジのため */
#if(PRO_HQ_MODE == ENABLE)
	/**	インチ／ミリビットにインチセット	*/
	RxModeMethod = SYS_INCH;
#else
	RxModeMethod = SYS_METRIC;
#endif
	switch (AvailableRxResolution) {		/**	受信可能モード	*/
		case SYS_HFINE	:	/**	ハイパーファイン	*/
			if ((RxStandardFrameByteCount > 4) &&
				(MDM_ModemBuffer[StdFrmPos][4] & SET_FINE_BIT)) {		/**	DCS ファインビット ON	*/
				/**	受信モードファイン	*/
				RxMode = SYS_FINE;
			}
#if(PRO_MAKER == MML)
			if ((MakerCodeRxFlag == YES) &&
				(RxNonStandardFrameByteCount > 6) &&
				(MDM_ModemBuffer[NonStdFrmPos][6] & SFINE_MODE_BIT)) {		/**	NSS スーパーファインビットON	*/
				/**	確定受信モード スーパーファイン	*/
				RxMode = SYS_SFINE;
			}
#endif
			if ((RxStandardFrameByteCount > 8) &&
				(MDM_ModemBuffer[StdFrmPos][8] & SUPER_FINE_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	DCS スーパーファインビット ON	*/
				/**	受信モードスーパーファイン	*/
				RxMode = SYS_SFINE;
			}
			if ((RxStandardFrameByteCount > 8) &&
				(MDM_ModemBuffer[StdFrmPos][8] & HYPER_FINE_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	DCS ハイパーファインビット ON	*/
				/** 受信モードハイパーファイン	*/
				RxMode = SYS_HFINE;
			}
			break;
		case SYS_SFINE:	/**	スーパーファイン	*/
			if ((RxStandardFrameByteCount > 8) &&
				(MDM_ModemBuffer[StdFrmPos][8] & HYPER_FINE_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	DCS ハイパーファインビット ON	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			if ((RxStandardFrameByteCount > 4) &&
				(MDM_ModemBuffer[StdFrmPos][4] & SET_FINE_BIT)) {		/**	DCS ファインビット ON	*/
				/**	受信モードファイン	*/
				RxMode = SYS_FINE;
			}
#if(PRO_MAKER == MML)
			if ((MakerCodeRxFlag == YES) &&
				(RxNonStandardFrameByteCount > 6) &&
				(MDM_ModemBuffer[NonStdFrmPos][6] & SFINE_MODE_BIT)) {		/**	NSS スーパーファインビットON	*/
				/**	確定受信モード スーパーファイン	*/
				RxMode = SYS_SFINE;
			}
#endif
			if ((RxStandardFrameByteCount > 8) &&
				(MDM_ModemBuffer[StdFrmPos][8] & SUPER_FINE_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	 DCS スーパーファインビット ON	*/
				/**	送信モードスーパーファイン	*/
				RxMode = SYS_SFINE;
			}
			break;
		case SYS_FINE:	/**	ファイン	*/
		case SYS_GRAY16:	/**	中間調16	*/
		case SYS_GRAY16_SEP:	/**	中間調16SEP	*/
		case SYS_GRAY32:	/**	中間調32	*/
		case SYS_GRAY32_SEP:	/**	中間調32SEP	*/
		case SYS_GRAY64:	/**	中間調64	*/
		case SYS_GRAY64_SEP:	/**	中間調64SEP	*/
		case	SYS_GRAY128:
		case	SYS_GRAY128_SEP:
		/* 皐月:32階調　桐紅葉ラベンダー:64階調 */
			if ((RxStandardFrameByteCount > 8) &&
				(MDM_ModemBuffer[StdFrmPos][8] & HYPER_FINE_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	 DCS ハイパーファインビット ON	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			if ((RxStandardFrameByteCount > 8) &&
				(MDM_ModemBuffer[StdFrmPos][8] & SUPER_FINE_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	DCSスーパーファインビット ON	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
 #if(PRO_MAKER == MML)
			if ((MakerCodeRxFlag == YES) &&
				(RxNonStandardFrameByteCount > 6) &&
				(MDM_ModemBuffer[NonStdFrmPos][6] & SFINE_MODE_BIT)) {		/**	NSS スーパーファインビットON	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
 #endif
			if ((RxStandardFrameByteCount > 4) &&
				(MDM_ModemBuffer[StdFrmPos][4] & SET_FINE_BIT)) {		/**	標準フレーム受信バイト数5バイト以上 DCS FIF ファインビット ON	*/
				/**	受信モードファイン	*/
				RxMode = SYS_FINE;
			}
			break;
		case SYS_NORMAL:	/**	ノーマル	*/
			if ((RxStandardFrameByteCount > 8) &&
				(MDM_ModemBuffer[StdFrmPos][8] & HYPER_FINE_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	DCS ハイパーファインビット ON	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
					return(NO);
				}
			}
			if ((RxStandardFrameByteCount > 8) &&
				(MDM_ModemBuffer[StdFrmPos][8] & SUPER_FINE_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	DCS SFINEビット ON	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
#if(PRO_MAKER == MML)
			if ((MakerCodeRxFlag == YES) &&
				(RxNonStandardFrameByteCount > 6) &&
				(MDM_ModemBuffer[NonStdFrmPos][6] & SFINE_MODE_BIT)) {		/**	NSS フレームSFINEビットON	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
#endif
			if ((RxStandardFrameByteCount > 4) &&
				(MDM_ModemBuffer[StdFrmPos][4] & SET_FINE_BIT)) {		/**	 DCS FINEビット ON	*/
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
			break;
		default:
			return(NO);
	}
#if(PRO_HQ_MODE == ENABLE)
	if ((RxStandardFrameByteCount > 8) &&
				(!(MDM_ModemBuffer[StdFrmPos][8] & INCH_BASE_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
				(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT))) {		/**	標準フレームミリビットONかつインチビットOFF	*/
		/**	インチ／ミリビットにミリセット（ミリに変換）	*/
		RxModeMethod = SYS_METRIC;
	}
	else if ((RxStandardFrameByteCount < 9) ||
				(!(MDM_ModemBuffer[StdFrmPos][8] & INCH_BASE_BIT) &&
				!(MDM_ModemBuffer[StdFrmPos][8] & METRIC_BASE_BIT))) {		/**	標準フレームミリビットOFFかつインチビットOFF	*/
		/**	インチ／ミリビットにミリセット（ミリに変換）	*/
		RxModeMethod = SYS_METRIC;
		/* FX Special!! */
		/*					Default Value */
		/* Norm,Fine,Sfine --> mm */
		/* Hfine ------------> inch */
		if(RxMode == SYS_HFINE) {
			TxModeMethod = SYS_INCH;
		}
	}
#endif
	/**	コマンド.src.d_mode に確定受信モードセット	*/
	SYS_DocBlock.Src.Mode = RxMode;
	/**	コマンド.dst.d_mode に確定受信モードセット	*/
	SYS_DocBlock.Dst.Mode = RxMode;
#if(PRO_HQ_MODE == ENABLE)
	SYS_DocBlock.ModeMethod = RxModeMethod;
#endif
	return(YES);
}
#endif

/*************************************************************
	module		:[受信原稿長確定]
	function	:[
		ＤＣＳビットと受信能力より記録紙長を確定する
	]
	return		:[
		記録紙長確定---YES／記録紙長確定せず---NO
	]
	common		:[
		MDM_ModemBuffer
		StdFrmPos
		FaxRxMaxLength
		FaxRxAvailableLength
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/25]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE	SetRxPaperLength(void)
{
	switch (MDM_ModemBuffer[StdFrmPos][5] & MASK_RX_LENGTH_BIT) {		/**	標準フレーム受信長ビットチェック	*/
		case LENGTH_A4_BIT:	/**	A4長	*/
			/**	確定受信長A4長	*/
			FaxRxMaxLength = SYS_A4_LENGTH;
			break;
		case LENGTH_B4_BIT:	/**	B4長	*/
			if (FaxRxAvailableLength == SYS_A4_LENGTH) {		/**	設定可能受信長A4	*/

				return(NO);
			}
			/**	確定受信長B4長	*/
			FaxRxMaxLength = SYS_B4_LENGTH;
			break;
		case LENGTH_UNLIMITED_BIT:	/**	無限長	*/
		default:
			if ((FaxRxAvailableLength == SYS_A4_LENGTH) ||
				(FaxRxAvailableLength == SYS_B4_LENGTH)) {		/**	設定可能受信長A4またはB4	*/
				return(NO);
			}
			/**	確定受信長無限長	*/
			FaxRxMaxLength = SYS_NO_LIMIT;
	}
	return(YES);
}


/*************************************************************
	module		:[受信時の線密度をチェックする]
	function	:[
		受信時確定線密度がファイン／スーパーファインであることを確認する
		ラベンダー,紅葉プリンター受信　スーパーファイン5ms/l受信能力有り
	]
	return		:[
		確定線密度がファイン---YES(1)／確定線密度がスーパーファイン---(2)／確定線密度ファインではない---NO(0)
	]
	common		:[
		TxMode
	]
	condition	:[]
	comment		:[サブルーチン化することないか？]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE	CheckRxModeUpperFine(void)
{
	switch (RxMode) {		/**	確定受信モード	*/
		case SYS_NORMAL:	/**	3.85 l/mm	*/
			return(NO);
		case SYS_SFINE:/** 15.4 l/mm	*/
		case SYS_HFINE:
			return(2);		/**	スーパーファイン	*/
		default:		/**	7.7 l/mm	*/
			return(YES);
	}
}


/*************************************************************
	module		:[受信側最少電送時間を確定]
	function	:[
		ＤＣＳのビットと受信能力より受信側最少伝送時間を確定する
	]
	return		:[
		最少伝送時間確定---YES／最少伝送時間確定せず---NO
	]
	common		:[
		MDM_ModemBuffer
		StdFrmPos
		RxMinimumScanningTime
		AvailableRxMinimumScanningTime
		RxMinimumScanningTime
		RxSpeedHandshakeFlag
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/25]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE	SetRxMinimumCommunicationTime(void)
{
	UBYTE fine_f;

	fine_f = 0;
	/**	ファインフラグ(ローカル変数)セット	*/
	fine_f = CheckRxModeUpperFine();
	switch (MDM_ModemBuffer[StdFrmPos][5] & MASK_MINIMUM_SCANNING_TIME) {		/**	DCS FIF 最少伝送時間ビットチェック	*/
		case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
			/*if (AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME0) 受信能力0ms 強制的に0msにする。26.Oct'94 Y.S*/
			RxMinimumScanningTime = SCAN_MINIMUM_TIME0;
			break;
		case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
#if 0 /* (PRO_PRINT_TIME == TIME2) /@	ラベンダー、紅葉	*/
			if ((AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME0) ||
				(AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME5) ||
				((AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME10_2) && (fine_f == YES)) ||
				((AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME20_2) && (fine_f == 2))) {		/**	受信可能最少伝送時間0ms または 5ms または 10_2ms でかつモードがファインである ラベンダー、紅葉はスーパーファインの場合に限り５ｍｓで受信可	*/
#endif /* #else 　ポプラ－－－－ここのプログラムは要変更　*/
			if ((AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME0) ||
				(AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME5) ||
				((AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME10_2) && (fine_f != NO))) {		/**	受信可能最少伝送時間0ms または 5ms または 10_2ms でかつモードがファインである	*/
					/* スーパーファインのときも 1/2(3.85Time) にする様修正 QAT SATUKI_H 20.Jly'94 Y.Suzuki */
/* #endif */
				/**	最少伝送時間5ms	*/
				RxMinimumScanningTime = SCAN_MINIMUM_TIME5;
			}
			else {		/**	10ms,20ms,40ms	*/
				/**	最少伝送時間に受信可能最少伝送時間をセット	*/
				RxMinimumScanningTime = AvailableRxMinimumScanningTime;
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
					return(NO);
				}
			}
			break;
		case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
			if ((AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME0) ||
				(AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME5) ||
				(AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME10) ||
				(AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME10_2) ||
				((AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME20_2) && (fine_f != NO))) {		/**	受信可能最少伝送時間0ms または 5ms または 10ms または 10_2ms または 20_2ms でかつモードがファインである	*/
				/* スーパーファインのときも 1/2(3.85Time) にする様修正 QAT SATUKI_H 20.Jly'94 Y.Suzuki */
				/**	最少伝送時間10ms	*/
				RxMinimumScanningTime = SCAN_MINIMUM_TIME10;
			}
			else {		/**		*/
				/**	最少伝送時間に受信可能最少伝送時間をセット	*/
				RxMinimumScanningTime = AvailableRxMinimumScanningTime;
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
					return(NO);
				}
			}
			break;
		case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
			if ((AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME0) ||
				(AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME5) ||
				(AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME10) ||
				(AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME20) ||
				(AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME10_2) ||
				(AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME20_2) ||
				((AvailableRxMinimumScanningTime == SCAN_MINIMUM_TIME40_2) && (fine_f != NO))) {		/**	受信可能最少伝送時間0ms または 5ms または 10ms または 20ms または 10_2ms または 20_2ms または 40_2ms でかつモードがファインである	*/
				/* スーパーファインのときも 1/2(3.85Time) にする様修正 QAT SATUKI_H 20.Jly'94 Y.Suzuki */
				/**	最少伝送時間20ms	*/
				RxMinimumScanningTime = SCAN_MINIMUM_TIME20;
			}
			else {		/**		*/
				/**	最少伝送時間に受信可能最少伝送時間をセット	*/
				RxMinimumScanningTime = AvailableRxMinimumScanningTime;
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
					return(NO);
				}
			}
			break;
		case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
			/**	最少伝送時間40ms	*/
			RxMinimumScanningTime = SCAN_MINIMUM_TIME40;
			break;
		default:
			return(NO);
	}
	return(YES);
}

/*************************************************************
	module		:[受信ＥＣＭモード確定]
	function	:[
		ＤＣＳのビットと受信能力より受信側ECMモードありなしを確定
		1.ＤＣＳのＥＣＭビットチェック
		2.ＥＣＭ受信能力確認
		3.フレームサイズセット
	]
	return		:[
		ＥＣＭ交信ではない || ＥＣＭ交信成立 あり---YES
		ＥＣＭなし（ＥＣＭ不成立なし && 短縮ハンドシェークではない）---NO
	]
	common		:[
		RxECM_Mode
		FaxComResult
		RxStandardFrameByteCount
		MDM_ModemBuffer
		StdFrmPos
		RxECMAbility
		FCM_EcmSize
		RxSpeedHandshakeFlag
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/25]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE	SetRxECM_Mode(void)
{
	/**	交信結果ECMなし	*/
	FaxComResult &= ~ECM_MODE_SET;

	if (RxStdFrame_ECMAbilityCheck()) {		/* 受信フレームＥＣＭ能力解析 */
		if (RxECM_Ability == ECM_ON) {		/**	受信側ECM能力あり	*/
			/**	確定ECMモード ON*/
			RxECM_Mode = ECM_ON;
			/**	交信結果ECMあり	*/
			FaxComResult |= ECM_MODE_SET;
			if((MDM_ModemBuffer[StdFrmPos][6] & ECM_FRAMESIZE_64_BIT) != ECM_FRAMESIZE_64_BIT) {		/**	DCS ECMフレームサイズ64バイトビットOFF	*/
				/**	ECMフレームサイズ256セット	*/
				FcomEcmSize = ECM_256_OCT;
			}
		}
		else {		/**	受信側ECM能力なし	*/
#if (PRO_CIPHER == ENABLE) /* 1997/12/08 T.Yamaguchi */
			/* スクランブルはここでエラーにしない */
#else
			if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
			}
#endif
		}
	}
	else {
#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/06 */
		if (SYS_V34ProcedureExecuting()) {	/* V34なら強制的にECMｵﾝ 1996/05/30 Y.M */
			RxECM_Mode = ECM_ON;
			/**	交信結果ECMあり	*/
			FaxComResult |= ECM_MODE_SET;
			if((MDM_ModemBuffer[StdFrmPos][6] & ECM_FRAMESIZE_64_BIT) != ECM_FRAMESIZE_64_BIT) {		/**	DCS ECMフレームサイズ64バイトビットOFF	*/
				/**	ECMフレームサイズ256セット	*/
				FcomEcmSize = ECM_256_OCT;
			}
		}
		else {
			RxECM_Mode = ECM_OFF;/* SpeedHandshake受信時必須? 25.May'94 Y.Suzuki */
		}
#else /* (PRO_TX_SPEED == V34) */
		RxECM_Mode = ECM_OFF;/* SpeedHandshake受信時必須? 25.May'94 Y.Suzuki */
#endif /* (PRO_TX_SPEED == V34) */
	}
	return(YES);
}

#if (PRO_CIPHER == ENABLE) /* 1997/12/08 T.Yamaguchi */
/*************************************************************
	module		:[暗号化受信ＥＣＭモード確定]
	function	:[
		ＤＣＳのビットと受信能力より受信側ECMモードありなしを確定
		1.ＤＣＳのＥＣＭビットチェック
		2.ＥＣＭモードＯＦＦのときに呼ばれる
		3.フレームサイズセット
	]
	return		:[
		暗号化受信時にＥＣＭ ＯＦＦ設定でも強制的にＥＣＭで受信する
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/12/08]
	author		:[山口]
*************************************************************/
UBYTE	SetCipherRxECM_Mode(void)
{
	if (RxStdFrame_ECMAbilityCheck()) {		/* 受信フレームＥＣＭ能力解析 */
		if (RxECM_Ability == ECM_ON) {		/**	受信側ECM能力あり	*/
			/* ここにはこないはず */
		}
		else {		/**	受信側ECM能力なし	*/
			if (SYS_RxMemoryFileItem == SYS_MEM_CIPHER_RX_FILE) {
				/* 暗号化受信能力ありの場合は、ECMｵﾌ設定でもECMで暗号化を受信可能 1997/10/01  By T.Yamaguchi */
				/**	確定ECMモード ON*/
				RxECM_Mode = ECM_ON;
				/**	交信結果ECMあり	*/
				FaxComResult |= ECM_MODE_SET;
				if((MDM_ModemBuffer[StdFrmPos][6] & ECM_FRAMESIZE_64_BIT) != ECM_FRAMESIZE_64_BIT) {		/**	DCS ECMフレームサイズ64バイトビットOFF	*/
					/**	ECMフレームサイズ256セット	*/
					FcomEcmSize = ECM_256_OCT;
				}
			}
			else {
				if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信でなければエラー	*/
					return(NO);
				}
			}
		}
	}
	return(YES);
}
#endif

/*************************************************************
	module		:[受信時ＭＳＥモード確定]
	function	:[
		ＮＳＳのビットと受信能力より受信側ＭＳＥモードを確定する
		ＭＳＥ２は、なにもしない
		ＳＭＳＥ＋ＭＳＥ１のＮＳＳがきたとき、両方の能力があればＳＭＳＥをセットする 27.Jun'94
		ＡＮＺＵの能力はＭＳＥ１のみ
	]
	return		:[
	]
	common		:[
		MDM_ModemBuffer
		NonStdFrmPos
		AvailableRxMSE_Method
		SYS_DocBlock.MSE_Method
		RxSpeedHandshakeFlag
	]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/30]
	author		:[t.yamaguchi]
*************************************************************/
void	 far	SetRxMSE_Mode(void)
{
	switch (AvailableRxMSE_Method) {		/**	受信側MSE能力	*/
		case MSE1:	/**	MSE1	*/
			switch (MDM_ModemBuffer[NonStdFrmPos][6] & MASK_MSE_MODE) {		/**	NSS FIF MSEビットチェック	*/
				case MSE1_MODE_BIT:	/**	 MSE1	*/
				case SMSE_MODE_BIT:	/**	 SMSE		ありえないパス */
				case 0x0C:			/**	MSE1+MSE2	ありえないパス */
				case MSE1_SMSE_MODE_BIT:	/** MSE1+SMSE	ありえないパス */
				case 0x4C:			/**	MSE1+MSE2+SMSE	ありえないパス */
					/**	コマンドmse_method にMSE1セット	*/
					SYS_DocBlock.MSE_Method = MSE1;
					break;
				case NOMSE:			/**	NO MSE	*/
				case MSE2_MODE_BIT:	/**	 MSE2		ありえないパス */
				case 0x48:			/**	MSE2+SMSE	ありえないパス */
				default:
					/**	コマンドmse_method にMSEなしセット	*/
					SYS_DocBlock.MSE_Method = NOMSE;
					break;
			}
		case NOMSE:	/**	MSEなし	*/
		default:
			/**	コマンドmse_method にMSEなしセット	*/
			SYS_DocBlock.MSE_Method = NOMSE;
			break;
	}
}

#if 0		/* ANZU用↑に修正 By T.YAMAGUCHI '96.01.30 */
/*************************************************************
	module		:[受信時ＭＳＥモード確定]
	function	:[
		ＮＳＳのビットと受信能力より受信側ＭＳＥモードを確定する
		ＭＳＥ２は、なにもしない
		ＳＭＳＥ＋ＭＳＥ１のＮＳＳがきたとき、両方の能力があればＳＭＳＥをセットする 27.Jun'94
	]
	return		:[
		MSEあり---YES／MSEなし---NO
	]
	common		:[
		MDM_ModemBuffer
		NonStdFrmPos
		AvailableRxMSE_Method
		SYS_DocBlock.MSE_Method
		RxSpeedHandshakeFlag
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/25]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE	SetRxMSE_Mode(void)
{
#if defined(MOMIJI)
	if (SYS_RxMemoryFileItem == NULL){	/* プリンタ受信 26.Apr'94	*/
		AvailableRxMSE_Method = MSE1;
	}
#endif
	switch (MDM_ModemBuffer[NonStdFrmPos][6] & MASK_MSE_MODE) {		/**	NSS FIF MSEビットチェック	*/
		case NOMSE:	/**	NO MSE	*/
			switch (AvailableRxMSE_Method) {		/**	受信側MSE能力	*/
				case NOMSE:	/**	MSEなし	*/
				case MSE1:	/**	MSE1	*/
				/* case MSE2:	**	MSE2	*/
				case SMSE:	/**	SMSE	*/
					/**	コマンドmse_method にMSEなしセット	*/
					SYS_DocBlock.MSE_Method = NOMSE;
					break;
				default:
					break;
			}
			break;
		case MSE1_MODE_BIT:	/**	 MSE1	*/
			switch (AvailableRxMSE_Method) {		/**	受信側MSE能力	*/
				case MSE1:	/**	MSE1	*/
				/* case MSE2:	**	MSE2	*/
				case SMSE:	/**	SMSE	*/
					/**	コマンドmse_method にMSE1セット	*/
					SYS_DocBlock.MSE_Method = MSE1;
					break;
				case NOMSE:	/**	MSEなし	*/
				default:
					/**	コマンドmse_method にMSEなしセット	*/
					SYS_DocBlock.MSE_Method = NOMSE;
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
							return(NO);
					}
					break;
			}
			break;
		case MSE2_MODE_BIT:	/**	 MSE2	*/
			switch (AvailableRxMSE_Method) {		/**	受信側MSE能力	*/
				/*
				case MSE2:	@**	MSE2	*@
				*/
				case SMSE:	/**	SMSE	*/
					/*	コマンドmse_method にMSE2セット	*
					SYS_DocBlock.MSE_Method = MSE2;
					break;*/
				case MSE1:	/**	MSE1	*/
					/**	コマンドmse_method にMSE1セット	*/
					SYS_DocBlock.MSE_Method = MSE1;
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
							return(NO);
					}
					break;
				case NOMSE:	/**	MSEなし	*/
					/**	コマンドmse_method にMSEなしセット	*/
					SYS_DocBlock.MSE_Method = NOMSE;
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
							return(NO);
					}
					break;
				default:
					return(NO);
			}
			break;
		case SMSE_MODE_BIT:	/**	 SMSE	*/
			switch (AvailableRxMSE_Method) {		/**	受信側MSE能力	*/
				case SMSE:	/**	SMSE	*/
					/**	コマンドmse_method にSMSEセット	*/
					SYS_DocBlock.MSE_Method = SMSE;
					break;
				/*-------------------------
				case MSE2:	@**	MSE2	*@
					@**	コマンドmse_method にMSE2セット	*@
					SYS_DocBlock.MSE_Method = MSE2;
					if (RxSpeedHandshakeFlag != YES) {		@**	短縮ハンドシェーク受信ではない	*@
							return(NO);
					}
					break;
				---------------------------*/
				case MSE1:	/**	MSE1	*/
					/**	コマンドmse_method にMSE1セット	*/
					SYS_DocBlock.MSE_Method = MSE1;
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
							return(NO);
					}
					break;
				case NOMSE:	/**	MSEなし	*/
					/**	コマンドmse_method にMSEなしセット	*/
					SYS_DocBlock.MSE_Method = NOMSE;
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
							return(NO);
					}
					break;
				default:
					return(NO);
			}
		case MSE1_SMSE_MODE_BIT:
			switch (AvailableRxMSE_Method) {		/**	受信側MSE能力	*/
				case SMSE:	/**	SMSE	*/
					/**	コマンドmse_method にSMSEセット	*/
					SYS_DocBlock.MSE_Method = SMSE;
					break;
				case MSE1:	/**	MSE1	*/
					/**	コマンドmse_method にMSE1セット	*/
					SYS_DocBlock.MSE_Method = MSE1;
					break;
				case NOMSE:	/**	MSEなし	*/
					/**	コマンドmse_method にMSEなしセット	*/
					SYS_DocBlock.MSE_Method = NOMSE;
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
							return(NO);
					}
					break;
			}
			break;
		default:
			return(NO);
	}
	return(YES);
}
#endif

/*************************************************************
	module		:[SetRxPaperWidth()]
	function	:[
		受信側記録紙幅を確定する
	]
	return		:[
		記録紙幅確定 YES／記録紙幅確定できず NO
	]
	common		:[
		MDM_ModemBuffer
		StdFrmPos
		SYS_DocBlock.Src.:Size
		SYS_DocBlock.Dst.:Size
		RxWidth
		RxSpeedHandshakeFlag
	]
	condition	:[]
	comment		:[桐、紅葉--Ａ３あり　さつき、ラベンダー--Ｂ４であるが自分の能力外の記録紙幅は、CheckDocPaperSize()から返らない（条件コンパイルは、CheckDocPaperSize()内で行う]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/25]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE	SetRxPaperWidth(void)
{
	UBYTE rx_paper_size;
	
	if (SYB_MaintenanceSwitch[MNT_SW_C9] & BUCKUP_PAPER_SIZE_FCM_RCMP) {
		rx_paper_size = FCM_BuckUpPaperSize;	/* DIS/DTC宣言時点の記録紙サイズ */
	}
	else {
		rx_paper_size = CheckDocPaperSize();	/* DCS解析時点の記録紙サイズ */
	}
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/7/20 K.Kawata */
	if (CL1_ExtFunctionEnableFlag == 1) {
		rx_paper_size = SYS_A3_PAPER;
	}
#endif
	switch (MDM_ModemBuffer[StdFrmPos][5] & RX_ALL_PAPER_BIT) {		/**	DCS 原稿幅ビットチェック	*/
		case RX_A4_PAPER_BIT:	/**	A4	*/
			/* switch (CheckDocPaperSize()) { 1997/12/16  By T.Yamaguchi */	/**	記録紙幅チェック	*/
			switch (rx_paper_size) {		/**	記録紙幅チェック	*/
				case SYS_A3_PAPER:	/**	A3	*/
				case SYS_A4_PAPER:	/**	A4	*/
				case SYS_B4_PAPER:	/**	B4	*/
					/**	確定記録紙幅 にA4セット	*/
					RxWidth = SYS_DOCUMENT_A4_SIZE;
					break;
				default:
					return(NO);
			}
			break;
		case RX_B4_PAPER_BIT:	/**	B4	*/
			/* switch (CheckDocPaperSize()) { 1997/12/16  By T.Yamaguchi */	/**	記録紙幅チェック	*/
			switch (rx_paper_size) {		/**	記録紙幅チェック	*/
				case SYS_A3_PAPER:	/**	A3	*/
				case SYS_B4_PAPER:	/**	B4	*/
					/**	確定記録紙幅 にB4セット	*/
					RxWidth = SYS_DOCUMENT_B4_SIZE;
					break;
				case SYS_A4_PAPER:	/**	A4	*/
#if defined (KEISATSU) /* 警察FAX 05/11/07 石橋正和 */
					if (FCM_ExecutingS1Info.Protocol == SYS_PROTOCOL_ISSEI) {
						RxWidth = SYS_DOCUMENT_B4_SIZE;
						break;
					}
#endif
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
						return(NO);
					}
					/**	確定記録紙幅 にA4セット	*/
					RxWidth = SYS_DOCUMENT_A4_SIZE;
					break;
				default:
					return(NO);
			}
			break;
		case RX_A3_PAPER_BIT:	/**	A3	*/
			/* switch (CheckDocPaperSize()) { 1997/12/16  By T.Yamaguchi */	/**	記録紙幅チェック	*/
			switch (rx_paper_size) {		/**	記録紙幅チェック	*/
				case SYS_A3_PAPER:	/**	A3	*/
					/**	確定記録紙幅 にA3セット	*/
					RxWidth = SYS_DOCUMENT_A3_SIZE;
					break;
				case SYS_B4_PAPER:	/**	B4	*/
#if defined (KEISATSU) /* 警察FAX 05/11/07 石橋正和 */
					if (FCM_ExecutingS1Info.Protocol == SYS_PROTOCOL_ISSEI) {
						RxWidth = SYS_DOCUMENT_A3_SIZE;
						break;
					}
#endif
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
						return(NO);
					}
					/**	確定記録紙幅 にB4セット	*/
					RxWidth = SYS_DOCUMENT_B4_SIZE;
					break;
				case SYS_A4_PAPER:	/**	A4	*/
#if defined (KEISATSU) /* 警察FAX 05/11/07 石橋正和 */
					if (FCM_ExecutingS1Info.Protocol == SYS_PROTOCOL_ISSEI) {
						RxWidth = SYS_DOCUMENT_A3_SIZE;
						break;
					}
#endif
					if (RxSpeedHandshakeFlag != YES) {		/**	短縮ハンドシェーク受信ではない	*/
						return(NO);
					}
					/**	確定記録紙幅 にA4セット	*/
					RxWidth = SYS_DOCUMENT_A4_SIZE;
					break;
				default:
					return(NO);
			}
			break;
		default:
			return(NO);
	}
	/**	コマンドsrc.d_size に受信幅セット	*/
	SYS_DocBlock.Src.Size = RxWidth;
	/**	コマンドdst.d_size に受信幅セット	*/
	SYS_DocBlock.Dst.Size = RxWidth;
	return(YES);
}

