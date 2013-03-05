/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATALNTA	  ANZUを移植									 */
/*	ファイル名	 : FCM_DIAG.C												 */
/*	モジュール	 : MakeCommonDiagNSS()										 */
/*				 : WriteROMVersionDiagNSS()									 */
/*				 : RxDiagSemiCompatibleCheck()								 */
/*				 : AnalizeMakeServiceUtilitySb()							 */
/*				 : AnalizeMakeServiceUtility()								 */
/*				 : RemoteDiagnostic											 */
/*	作成者		 : 山口														 */
/*	日	付		 :	1996/11/19												 */
/*	概	要		 : リモート診断												 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\man_pro.h"

#include "\src\atlanta\define\syscomf.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\apl_msg.h"	/* 竹内 Feb.24.1995 */
#include "\src\atlanta\define\std.h"		/* 1997/02/05  By T.Yamaguchi */

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\rom_tbl.h"

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"
#include	"\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif

#if (PRO_DIAG == ENABLE) /* added by H.Kubo 1998/04/02 */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/03/31  By T.Yamaguchi */
UWORD	AD_Battery(void);
#include "\src\atlanta\define\mlt_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\mntsw_e.h"
#endif
#include "\src\atlanta\define\mon_pro.h"

/*************************************************************************
	module		:[リモート診断用ＮＳＳ共通部分の作成]
	function	:[]
	commom		:[
		MDM_ModemBuffer[][]		: モデムバッファ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	MakeCommonDiagNSS(void)
{
	MDM_ModemBuffer[0][0] = ADDRESS_FIELD_DATA;		/** アドレスフィールド (0xff)*/

/*	MDM_ModemBuffer[0][1] = NON_LAST_FRAME_DATA;	** 制御フィールド(非最終フレーム 0x03 ) */
	/* NSS + DIS の DIS がシスネット側で検出できないため NSS のみ送出する 94/11/28 Y.Suzuki */
	MDM_ModemBuffer[0][1] = LAST_FRAME_DATA;		/** 制御フィールド(最終フレーム 0x13 ) */

	MDM_ModemBuffer[0][2] = NSS_F;					/** ＦＣＦ NSS */

	MDM_ModemBuffer[0][3] = 0x00;					/** ＦＩＦ */
	MDM_ModemBuffer[0][4] = 0x00;

	MDM_ModemBuffer[0][5] = 0x45;			/** メーカーコードフィールド(0x45) */

	MDM_ModemBuffer[0][6] = EXPAND_FIELD_BIT;		/** (0x80) 基本設定フィールド : 機能拡張フィールド(1) セット */

	MDM_ModemBuffer[0][7] = EXPAND_FIELD_BIT;		/** (0x80) 機能拡張フィールド（１）: 機能拡張フィールド(2) セット */

	MDM_ModemBuffer[0][8] = SERVICE_UTIL_ON_BIT;	/** (0x20) 機能拡張フィールド（２）: サービスユーティリティフィールド セット */

	return;
}

/*************************************************************************
	module		:[リモート診断バージョン読み出し]
	function	:[]
	commom		:[
		MDM_ModemBuffer[][]		: モデムバッファ
		ROM_Revision[]			: ＲＯＭバージョン
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	WriteROMVersionDiagNSS(void)
{
	UWORD		read_pointer;
	UWORD		write_pointer;

	MDM_ModemBuffer[0][10] = 0;			/**アドレス */
	MDM_ModemBuffer[0][11] = 0;
	MDM_ModemBuffer[0][12] = 0;			/** オフセット */
	MDM_ModemBuffer[0][13] = 0;
	MDM_ModemBuffer[0][14] = 0x10;		/** バイト数 */

	write_pointer = 15;

	for( read_pointer = 0; read_pointer < 16; read_pointer++ ){
		MDM_ModemBuffer[0][write_pointer] = ROM_Revision[read_pointer];
		write_pointer++;
	}
	return;
}

/*************************************************************************
	module		:[相手機がリモート診断ホスト機かどうかチェックする]
	function	:[]
	commom		:[
		MDM_ModemBuffer[]		: モデムバッファ
		FCF_Point		: 最終フレームポイント
		DiagPoint		: モデムバッファのリモート診断フィールドポイント
	]
	condition	:[]
	comment		:[]
	return		:[相手側機がホスト機である(1) でない(0)]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
UBYTE	   RxDiagSemiCompatibleCheck(void)
{
	UWORD	   point;
	WORD		   i;
	UBYTE	   pass_code;

	point = 1;

	if ((MDM_ModemBuffer[FCF_Point][point] & 0x13) == 0x13){		/** 最終フレーム判断 */
		point += 4;
	}
	else{
		return(0);
	}

	if ((MDM_ModemBuffer[FCF_Point][point] & 0x45) == 0x45){		/** 自社機判断 */
		point += 1;
	}
	else{
		return(0);
	}

	if ((MDM_ModemBuffer[FCF_Point][point] & 0x80) != 0x80){		/** 機能拡張フィールド(1)有無 */
		return(0);
	}

	if ((MDM_ModemBuffer[FCF_Point][point] & 0x01) == 0x01){		/** 局名表示フィールド有無 */
		point += 17;
	}
	else{
		point += 1;
	}

	if (MDM_ModemBuffer[FCF_Point][2] == NSC_F){					/** パスコードフィールド( NSC Only ) */
		point += 4;
	}

	if ((MDM_ModemBuffer[FCF_Point][point] & 0x80) != 0x80){		/** 機能拡張フィールド(2)有無 */
	return(0);
	}

	if ((MDM_ModemBuffer[FCF_Point][point] & 0x01) == 0x01){		/** メモリ残量フィールド(1)有無 */

		if ((MDM_ModemBuffer[FCF_Point][point] & 0x08) == 0x80){	/** 親展フィールド有無 */
			point += 5;
		}
		else{
			point += 3;
		}
	}
	else{

		if ((MDM_ModemBuffer[FCF_Point][point] & 0x08) == 0x80){	/** 親展フィールド有無 */
			point += 2;
		}
		else{
			point += 1;
		}
	}

	if ((MDM_ModemBuffer[FCF_Point][point] & 0x20) == 0x20){	/** サービスユーティリティフィールド機能有無 */

		if ((MDM_ModemBuffer[FCF_Point][point] & 0x03) != 0x00){	/** メモリ残量フィールド(2)有無 */
			point += 4;
		}
		else{
			point += 1;
		}
	}
	else{
		return(0);
	}

	DiagPoint = point;

	/*---------------------------------*/
	/** リモート診断パスコードチェック */
	/*---------------------------------*/
	if (MDM_ModemBuffer[FCF_Point][2] == NSC_F){
		for(i = 0; i < 4; i++) {		/** 自機にパスコードがセットされているかどうか？ */
			if (SYB_DiagPasscodeNumber[i] != '0') {
				break;
			}
		}
		if (i == 4) {		/**	自機にパスコードがセットされていない 0000 がセットされている	*/
			for (i = 0; i < 4; i++) {	/** ホスト側パスコードチェック */
				pass_code = MDM_ModemBuffer[FCF_Point][i+7];
				if (pass_code < '0' || pass_code > '9') {	/** ホスト側パスコードチェック */
					break;
				}
			}
			if (i == 4) {	/** ホスト側にパスコードがセットされている */
				for (i = 0; i < 4; i++) {
					SYB_DiagPasscodeNumber[i] = MDM_ModemBuffer[FCF_Point][i+7];	/** パスコードコピー */
				}
			}
		}
		else {			/** 自機にパスコードがセットされている */
			for (i = 0; i < 4; i++) {
				pass_code = MDM_ModemBuffer[FCF_Point][i+7];
				if (pass_code != SYB_DiagPasscodeNumber[i]) {
					if (MDM_ModemBuffer[FCF_Point][7]  == 'R' &&
						MDM_ModemBuffer[FCF_Point][8]  == 'I' &&
						MDM_ModemBuffer[FCF_Point][9]  == 'C' &&
						MDM_ModemBuffer[FCF_Point][10] == 'E') {	/** ホスト側のパスコードが"Ｒ" "Ｉ" "Ｃ" "Ｅ"なら自機のパスコードクリア */

						SYB_DiagPasscodeNumber[0] = '0';
						SYB_DiagPasscodeNumber[1] = '0';
						SYB_DiagPasscodeNumber[2] = '0';
						SYB_DiagPasscodeNumber[3] = '0';
						break;
					}
					else {
						return(0);
					}
				}
			}
		}
	}

	return(1);
}

/*************************************************************************
	module		:[リモート診断ホスト機から送られて来た「ＮＳＣ」「ＦＩＦ」
				　を解析し、ホスト局の要求に従って、自機のメモリの読だし／
				　書き込みを行う。
				　ホスト機が「保護領域」の読みだし／書き込みを求めてきた場
				　合には、プロテクト処理を行う。
	function	:[]
	commom		:[
		TxID_FrameByteCount				: IDフレームバイト数
		TxNonStandardFrameByteCount		: 非標準IDフレームバイト数
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	AnalizeMakeServiceUtilitySb( UBYTE	diag_mode )
{
	/*--------------*/
	/**	 Make NSS  **/
	/*--------------*/
	switch( diag_mode ){	/** リモート診断を行う項目を判別 */
		case   DIAG_DIS_ONLY_TX :
								  MakeDIS_FIF();					/** Make DIS */
								  MakeNSF_FIF();					/** Make NSF 16.Jun'94 */
								  TxID_FrameByteCount = 0;
								  TxNonStandardFrameByteCount = 0;
								  break;
		case   DIAG_REVISION_TX :
							/*---------------------*/
							/** バージョン読みだし */
							/*---------------------*/
							/*	  MakeDIS_FIF();					** Make DIS 94/11/28 Y.S */
								  MakeNSF_FIF();					/** Make NSF 16.Jun'94 Y.Suzuki */
								  TxID_FrameByteCount = 0;
								  TxStandardFrameByteCount = 0;		/* 94/11/28 Y.S */
								  MakeCommonDiagNSS();				/** NSS 共通部分作成 */
								  MDM_ModemBuffer[0][9]	 = 0x04;	/** サービスユーティリティ（１）フィールド バージョン読みだし */
								  WriteROMVersionDiagNSS();			/** バージョン読みだし */
								  TxNonStandardFrameByteCount = 31;
								  break;
		case   DIAG_DATA_READ	:
							/*---------------*/
							/** データ読出し */
							/*---------------*/
							/*	  MakeDIS_FIF();					** Make DIS 94/11/28 Y.S */
								  MakeNSF_FIF();					/** Make NSF 16.Jun'94 Y.Suzuki */
								  TxID_FrameByteCount = 0;
								  TxStandardFrameByteCount = 0;		/* 94/11/28 Y.S */
								  MakeCommonDiagNSS();				/** NSS 共通部分作成 */

								  if ((CHK_RemoteDiagON() == 0)
								  && (DiagJudgeProtectAddress() == 1)){
								  /** リモート診断ＯＦＦでプロテクト領域 */

									  MDM_ModemBuffer[0][9] = 0x08;		/** サービスユーティリティ（１）フィールド	データリード アクセス禁止 */
									  TxNonStandardFrameByteCount = 10;
								  }
								  else{	/* リモート診断ＯＮまたはリモート診断ＯＦＦでプロテクト領域 */
									  MDM_ModemBuffer[0][9]	 = 0x00;	/** サービスユーティリティ（１）フィールド	データリード アクセス可 */
									  ReadFIF_DiagNSS();
									  TxNonStandardFrameByteCount++;
								  }

								  break;
		case   DIAG_DATA_WRITE	:
							/*-----------------*/
							/** データ書き込み */
							/*-----------------*/
								  if ((CHK_RemoteDiagON() == 0)
								  && (DiagJudgeProtectAddress() == 1)){
								/* プロテクトしなければならない */

								/*	  MakeDIS_FIF();				** Make DIS 94/11/28 Y.S */
									  MakeNSF_FIF();				/** Make NSF 16.Jun'94 Y.Suzuki */
									  TxStandardFrameByteCount = 0;	/* 94/11/28 Y.S */
									  TxID_FrameByteCount = 0;
									  MDM_ModemBuffer[0][9] = 0x0a;		/** サービスユーティリティ（１）フィールド	データライト アクセス禁止 */
								  }
								  else{
									  DiagPoint += 5;
									  WriteFIF_DiagNSS();
								/*	  MakeDIS_FIF();				** Make DIS 94/11/28 Y.S */
									  MakeNSF_FIF();				/** Make NSF 16.Jun'94 Y.Suzuki */
									  TxID_FrameByteCount = 0;
									  TxStandardFrameByteCount = 0;	/* 94/11/28 Y.S */
									  MDM_ModemBuffer[0][9] = 0x02;		/** サービスユーティリティ（１）フィールド	データライト アクセス可 */
								  }
								  MakeCommonDiagNSS();

								  TxNonStandardFrameByteCount = 10;

								  break;
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/03/31  By T.Yamaguchi */
		case	DIAG_ROM_WRITE_ERROR:
			MakeCommonDiagNSS();
			MDM_ModemBuffer[0][9] = 0xCA;		/** サービスユーティリティ（１）フィールド	ＲＯＭ書換え拒否 */
			MDM_ModemBuffer[0][10] = DiagErrorDetails;
			TxNonStandardFrameByteCount = 11;
			break;
		case	DIAG_ROM_WRITE_OK:
			break;
#endif
		case   DIAG_ERROR		:
		default					:
								  break;
	}
	return;
}

/*************************************************************************
	module		:[リモート診断を行う項目チェックする]
	function	:[]
	commom		:[
		MDM_ModemBuffer[]		: モデムバッファ
		FCF_Point		: 最終フレームポイント
		DiagPoint		: モデムバッファのリモート診断フィールドポイント
	]
	condition	:[]
	comment		:[]
	return		:[
		DIAG_REVISION_TX	: バージョン読み込み
		DIAG_DATA_READ		: データ読み込み
		DIAG_DATA_WRITE		: データ書き込み
		DIAG_ERROR			: エラー
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
UBYTE	AnalizeMakeServiceUtility(void)
{
	UBYTE	diag_mode;
	UBYTE	diag_fcf;
	UBYTE	diag_fif;

	if (RxDiagSemiCompatibleCheck() == 1){	/** リモートホスト機かどうかのチェック */

		diag_fcf = MDM_ModemBuffer[FCF_Point][2];
		diag_fif = MDM_ModemBuffer[FCF_Point][DiagPoint];
		if ( NSC_F != diag_fcf){
			diag_fcf &=	 0xfe ;				/** Rmove X bit */
		}

		if (( NSC_F == diag_fcf) && ( 0x04	== diag_fif)){			/** バージョン読みだし */
			diag_mode = DIAG_REVISION_TX;
		}
		else{
			if (( NSC_F == diag_fcf) && ( 0x00	== diag_fif)){		/** データ読みだし */
				ReadStartAddress();
				diag_mode = DIAG_DATA_READ;
			}
			else{
				if (( NSS_F == diag_fcf) && ( 0x02 == diag_fif)){	/** データ書き込み */
					ReadStartAddress();
					diag_mode =	 DIAG_DATA_WRITE;
				}
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/03/31  By T.Yamaguchi */
				else if (( NSC_F == diag_fcf) && ( 0xC2	== diag_fif)){	/** ﾌﾗｯｼｭROM書換え要求 */
					DiagErrorDetails = FlashRomWriteCheck();
					if (DiagErrorDetails) {
						diag_mode =	 DIAG_ROM_WRITE_ERROR;
					}
					else {
						diag_mode =	 DIAG_ROM_WRITE_OK;
					}
				}
#endif
				else{
					if ( DCN_F != diag_fcf){
						FaxPhaseE(5);
					}
					else{								/** DCN Rx */
						FaxPhaseE(4);
					}
					diag_mode =	 DIAG_ERROR;
					ReceiveError( 0x12 );			/** R.1.2 */
				}
			}
		}
	}
	else{
		if ( DCN_F != diag_fcf){
			FaxPhaseE(5);
		}
		else{											/** DCN Rx */
			FaxPhaseE(4);
		}
		diag_mode =	 DIAG_ERROR;
		ReceiveError( 0x12 );						/** R.1.2 */
	}
	return( diag_mode );
}


/*************************************************************************
	module		:[リモート診断を行う]
	function	:[]
	commom		:[
		FaxComPerformingflag		: 通信中フラグ
		FaxComTXorRX_Sign			: 送受信チェックフラグ
		FaxComType					: 交信種別
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	RemoteDiagnostic(void)
{
	UBYTE	command;
	UWORD				T1_timer;
	UWORD				T1_timer_max;
	UBYTE	rxmode_flag;
	UBYTE	diag_mode;
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
	UBYTE	debug_sw;
	debug_sw = 0;
#endif

#if (PRO_PRINTER_RX == ENABLE)
	/* リモート診断中にプリンタが使用できないので */
	/* 着信時に通信がつかんだプリンタを開放する	  */
	/*							 竹内 Feb.24.1995 */
	SendMsgFaxComToMain( MSG_FAXCOM_TX_START );		/* とりあえずこのメッセージ */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.26 K.Kawata */
/* リモート診断中にプリンタが使用できないので着信時に通信がつかんだプリンタを開放する */
	SendMsgFaxComToMain(MSG_FAXCOM_TX_START);
#endif
	while(FaxComPerformingFlag == 1){				/** 通信中 */
		diag_mode = AnalizeMakeServiceUtility();		/** サービスユーティリティフィールド処理部位 */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
		if (diag_mode == DIAG_ROM_WRITE_OK) {
			FaxComTXorRX_Sign = DIAG_MODE;
			SYS_FaxComType	  = SYS_REMOTE_DIAG;
			return;
		}
#endif
		/*----------------*/
		/** T1 Timer Set **/
		/*----------------*/
		T1_timer_max = (UWORD)( 35000 / 10 );
		T1_timer	 = SYS_GeneralTimer;
		rxmode_flag	 = 0;
		/*------------------------------*/
		/** 被診断機 － 診断機交信部位 **/
		/*------------------------------*/
		while((FaxComPerformingFlag == 1)
		&& (( UWORD )( SYS_GeneralTimer - T1_timer ) < T1_timer_max )
		&& (rxmode_flag == 0)
		&& (SYS_FaxComStopSwitch() == 0)){
			AnalizeMakeServiceUtilitySb( diag_mode );		/** Make NSS/DIS */
			diag_mode = DIAG_DIS_ONLY_TX;
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/04 */
			FCM_TransmitCommand();								/** NSS Tx */
			if (FCM_ReceiveResponse((UBYTE)0, NON_CCRETRAIN) == FSK_RECEIVE){				/** 応答受信 */
				command = CheckHDLC_Command();				/** NSC/NSS Rx */
				rxmode_flag = 1;
				if (( NSC_F != command ) && ( NSS_F != command )){
					if ( DCN_F != command ){
						FaxPhaseE(5);
						ReceiveError( 0x23 );			/** R.2.3 */
					}
					else{									/** DCN Rx */
						FaxPhaseE(4);
					}
				}
			}
#else /*(PRO_TX_SPEED == V34)*/
 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
			if (debug_sw == 2) {
				TimerCutStatus = 1;
			}
			if (debug_sw == 1) {
				wai_tsk(10);		/* TEST モデムによって、低速信号を受信できないので */
			}
 #endif
			MDM_TransmitCommand();								/** NSS Tx */
			if (MDM_ReceiveResponse(FCM_ReceiveResponseTime) == FSK_RECEIVE){				/** 応答受信 */
				command = CheckHDLC_Command();				/** NSC/NSS Rx */
				rxmode_flag = 1;
				if (( NSC_F != command ) && ( NSS_F != command )){
					if ( DCN_F != command ){
						FaxPhaseE(5);
						ReceiveError( 0x23 );			/** R.2.3 */
					}
					else{									/** DCN Rx */
						FaxPhaseE(4);
					}
				}
			}
 #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
			else {
				TimerCutStatus = 1;
			}
 #endif
#endif /*(PRO_TX_SPEED == V34)*/
		}

		if (FaxComPerformingFlag == 1){					/** 通信中 */
			if ((SYS_FaxComStopSwitch() == 0) && (rxmode_flag == 0)){	/** T1 Time Over */
				FaxPhaseE(5);
				ReceiveError(0x11);						/** R.1.1 */
			}
			else{
				if (SYS_FaxComStopSwitch() == 1){
					FaxPhaseE(5);
					ReceiveError(0x14);						/** R.1.4 */
				}
			}
		}
	}

	FaxComTXorRX_Sign = DIAG_MODE;
	SYS_FaxComType	  = SYS_REMOTE_DIAG; /* ここでしか書き換えられない */
	return;
}

/*************************************************************************	これよりした　95.11.08　追加
	module		:[リモート診断ＮＳＳ／ＮＳＣ開始アドレス・バイト数読込]
	function	:[]
	commom		:[
		FCF_Point			: 最終フレームポイント
		DiagPoint			: サービスユーティリティフィールドポイント
		DiagReadAddress		: アドレス（オフセット）
		DiagReadSegment		: セグメント
		DiagByteCounter		: バイト数
		MDM_ModemBuffer[]	: モデムバッファ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53]
	language	:[]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void			ReadStartAddress(void)
{
	UWORD low, high;

	low = (UWORD)MDM_ModemBuffer[FCF_Point][DiagPoint+1];	/* 下位 */
	high = (UWORD)MDM_ModemBuffer[FCF_Point][DiagPoint+2];	/* 上位 */
	DiagReadAddress = (0x100 * high) + low;

	low = (UWORD)MDM_ModemBuffer[FCF_Point][DiagPoint+3];	/* 下位 */
	high = (UWORD)MDM_ModemBuffer[FCF_Point][DiagPoint+4];	/* 上位 */
	DiagReadSegment = (0x100 * high) + low;

	DiagByteCounter = MDM_ModemBuffer[FCF_Point][DiagPoint+5];
}


/*************************************************************************
	module		:[リモート診断ＮＳＳのＦＩＦにホスト側から読みだし
			  要求されたデータを読み込みます。
	]
	function	:[]
	commom		:[
		DiagReadAddress			: アドレス（オフセット）
		DiagReadSegment			: セグメント
		DiagByteCounter			: バイト数
		TxNonStandardFrameByteCount	: 非標準フレームバイト数
		MDM_ModemBuffer			: モデムバッファ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53]
	language	:[]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void			ReadFIF_DiagNSS(void)
{
	UBYTE	i;
	UWORD	low, high, pos;
	UBYTE	*pointer;

	low = DiagReadAddress & 0x00FF;
	high = (DiagReadAddress & 0xFF00)/0x100;
	MDM_ModemBuffer[0][10] = (UBYTE)low;
	MDM_ModemBuffer[0][11] = (UBYTE)high;

	low = DiagReadSegment & 0x00FF;
	high = (DiagReadSegment & 0xFF00)/0x100;
	MDM_ModemBuffer[0][12] = (UBYTE)low;
	MDM_ModemBuffer[0][13] = (UBYTE)high;
	MDM_ModemBuffer[0][14] = DiagByteCounter;

	pos = 14;
	pointer = (UBYTE *)(DiagReadSegment * 0x10000 + DiagReadAddress);
	for (i = 0; i < DiagByteCounter; i++) {
		pos++;
		MDM_ModemBuffer[0][pos] = *(pointer++);
	}
	TxNonStandardFrameByteCount = pos;
}


/*************************************************************************
	module		:[ホスト側から書き込み要求されたデータを書き込みま
			  す。
	]
	function	:[]
	commom		:[
		FCF_Point		: 最終フレームポイント
		DiagPoint		: サービスユーティリティフィールドポイント
		DiagReadSegment		: セグメント
		DiagByteCounter		: バイト数
		DiagReadAddress		: アドレス（オフセット）
		MDM_ModemBuffer		: モデムバッファ
		SettingStatus		: セッティングステータス
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53]
	language	:[]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void			WriteFIF_DiagNSS(void)
{
	UBYTE	i;
	UWORD	pos;
	UBYTE	*pointer;

	pointer = (UBYTE far *)(DiagReadSegment * 0x10000 + DiagReadAddress);
	pos = DiagPoint;

	for (i = 0; i < DiagByteCounter; i++) {
		pos++;
		*(pointer + i) = MDM_ModemBuffer[FCF_Point][pos];
	}
}


/*************************************************************************
	module		:[]
	function	:[]
	commom		:[リモート診断にて診断（ﾎｽﾄ）側が読みだし／書き込み
			  を求めてきたアドレスが保護領域であるかどうかを判断します。
	]
	condition	:[]
	comment		:[]
	return		:[
		保護領域	:1
		非保護領域	:0
	]
	machine		:[V53]
	language	:[]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
UWORD	DiagJudgeProtectAddress(void)
{
	UBYTE	*pointer;
	UBYTE	*protect_start_address;
	UBYTE	*protect_end_address;

	protect_start_address = &SYB_DiagRW_UserSelectAddress;
	protect_end_address = &SYB_DiagRW_Address;
	pointer = (UBYTE *)(DiagReadSegment * 0x10000 + DiagReadAddress);

	if ((pointer >= protect_start_address) && (pointer <= protect_end_address)) {
		return(1);
	}
	else {
		return(0);
	}
}
/* ●ICHOU追加 by T.Soneoka 1996/06/14 */
/*************************************************************************
	module		:[相手機がリモート診断ホスト機かどうかチェックする]
	function	:[
		１．相手機が村田機であるか
		２．機能拡張フィールド（１）があるか
		３．機能拡張フィールド（２）があるｋ
		４．サービスユーティリティーフィールドがあるか
		５．ＲＤＳプロトコルが新プロトコルであるか
		６．ＮＳＣ・・・データリード／ＮＳＳ・・・データライトであるか
	]
	commom		:[
		MDM_ModemBuffer[]		: モデムバッファ
	]
	condition	:[]
	comment		:[]
	return		:[相手側機がホスト機である(1) でない(0)]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[1996/06/14]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE HighSpeedRDS_CompatibleCheck(void)
{
	UWORD	pos;
	UWORD	std_pos;
	UWORD	ext1_pos;
	UWORD	ext2_pos;
	UWORD	diag_pos;
	UWORD	passcode_pos;
	WORD	i;
	UBYTE	pass_code;

	GetMultiFrameLine();		/**	受信フレームの取り込み	*/

	pos = 5;
	passcode_pos = 0;

	if ((MDM_ModemBuffer[NonStdFrmPos][pos] & 0x45) == 0x45){		/** 自社機判断 */
		pos += 1;
	}
	else{
		return(DIAG_FALSE);
	}
	std_pos = pos;	/* 基本機能設定フィールドポジション */

	if ((MDM_ModemBuffer[NonStdFrmPos][std_pos] & 0x80) != 0x80){		/** 機能拡張フィールド(1)有無 */
		return(DIAG_FALSE);
	}

	if (MDM_ModemBuffer[NonStdFrmPos][2] == NSC_F){	/** パスコードフィールド( NSC Only ) */
		passcode_pos = std_pos+1;		/* パスコードフィールドのポジションを保存 */
		pos += 4;
	}

	if ((MDM_ModemBuffer[NonStdFrmPos][std_pos] & 0x01) == 0x01){		/** 局名表示フィールド有無 */
		pos += 16;
	}
	pos += 1;

	ext1_pos = pos;	/* 機能拡張フィールド（１）ポジション */

	if ((MDM_ModemBuffer[NonStdFrmPos][ext1_pos] & 0x80) != 0x80) {		/** 機能拡張フィールド(2)有無 */
		return(DIAG_FALSE);
	}
	else {
		if ((MDM_ModemBuffer[NonStdFrmPos][2] & ~X_BIT) == NSS_F){
			if ((MDM_ModemBuffer[NonStdFrmPos][ext1_pos] & 0x01) == 0x01) {	/** メモリ残量フィールド(1)有無 */
				pos += 3;
			}
			if ((MDM_ModemBuffer[NonStdFrmPos][ext1_pos] & 0x08) == 0x08) {	/** 親展フィールド有無 */
				pos += 2;
			}
			if ((MDM_ModemBuffer[NonStdFrmPos][ext1_pos] & 0x10) == 0x10) {	/** 中継指示フィールド有無 */
				pos += 4;
			}
			if ((MDM_ModemBuffer[NonStdFrmPos][ext1_pos] & 0x40) == 0x40) {	/** パスコードフィールド有無 */
				passcode_pos = pos+1;	/* パスコードフィールドのポジションを保存 */
				pos += 4;
			}
			pos += 1;
		}
		else if (MDM_ModemBuffer[NonStdFrmPos][2] == NSC_F) {
			if ((MDM_ModemBuffer[NonStdFrmPos][ext1_pos] & 0x01) == 0x01) {	/** メモリ残量フィールド(1)有無 */
				pos += 3;
			}
			if ((MDM_ModemBuffer[NonStdFrmPos][ext1_pos] & 0x04) == 0x04) {	/** 検索ポーリングフィールド有無 */
				/* pos += 2; */
				for (i = 0; i < (SYS_DATA_BASE_MAX-1); i++) {/** 取り出せるファイルNOの数、最大１０個 */
					if (!(MDM_ModemBuffer[NonStdFrmPos][pos+(i*2)+2] & 0x80)) {	/**	継続ビットＯＮ	*/
						break;
					}
				}
				pos += ((i*2)+2);
			}
			pos += 1;
		}
		else {
			return(DIAG_FALSE);
		}
	}

	ext2_pos = pos;	/* 機能拡張フィールド（２）ポジション */

	if ((MDM_ModemBuffer[NonStdFrmPos][ext2_pos] & 0x20) != 0x20) {	/** サービスユーティリティフィールド機能有無 */
		return(DIAG_FALSE);
	}
	if ((MDM_ModemBuffer[NonStdFrmPos][ext2_pos] & 0x01) == 0x01){	/** メモリ残量フィールド（２）有無 */
		pos += 3;
	}
	pos += 1;

	diag_pos = pos;

	if ((MDM_ModemBuffer[NonStdFrmPos][diag_pos] & 0x80) != 0x80) {	/* 新プロトコルかチェック */
		return(DIAG_FALSE);
	}
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/03/31  By T.Yamaguchi */
	if ((MDM_ModemBuffer[NonStdFrmPos][diag_pos] & 0x40) == 0x40) {	/* ＲＯＭデータ書換え要求 */
	}
#else
	if ((MDM_ModemBuffer[NonStdFrmPos][diag_pos] & 0x40) == 0x40) {	/* データ種別がバックアップかチェック */
		return(DIAG_ERR);
	}
#endif
	if (MDM_ModemBuffer[NonStdFrmPos][2] == NSC_F){
		if ((MDM_ModemBuffer[NonStdFrmPos][diag_pos] & 0x02) == 0x02) {	/* アクセスモードがデータリードかチェック */
			return(DIAG_ERR);
		}
		/** 高速ＲＤＳはＥＣＭ Ｏｎで動作するように変更します by T.Soneoka 1997/07/10 */
		/* SetTxECM_Mode();
		** if (TxECM_Mode == ECM_OFF) {
		**	return(DIAG_FALSE);
		** }
		*/
	}
	else if ((MDM_ModemBuffer[NonStdFrmPos][2] & ~X_BIT) == NSS_F){
		if ((MDM_ModemBuffer[NonStdFrmPos][diag_pos] & 0x02) != 0x02) {	/* アクセスモードがデータライトかチェック */
			return(DIAG_ERR);
		}
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
		if ((MDM_ModemBuffer[NonStdFrmPos][diag_pos] & 0x40) == 0x40) {	/* ＲＯＭデータ書換え要求 */
			FCM_ROMDataSum = 0;
			SYB_ROM_DataSumcheck = 0x0000;
			SYB_ROM_DataSumcheck |= (UWORD)(MDM_ModemBuffer[NonStdFrmPos][diag_pos+1]);
			SYB_ROM_DataSumcheck |= (UWORD)(MDM_ModemBuffer[NonStdFrmPos][diag_pos+2]) << 8;
		}
		else {
#endif
			/*
			** 高速ＲＤＳはＥＣＭ Ｏｎで動作するように変更します by T.Soneoka 1997/07/10
			**
			** SetRxECM_Mode();
			** if (RxECM_Mode == ECM_OFF) {
			** 	return(DIAG_FALSE);
			** }
			*/
			BackUpDataLength = 0x0000;
			BackUpDataLength |= (UDWORD)(MDM_ModemBuffer[NonStdFrmPos][diag_pos+1]);
			BackUpDataLength |= (UDWORD)(MDM_ModemBuffer[NonStdFrmPos][diag_pos+2]) << 8;
			BackUpDataLength |= (UDWORD)(MDM_ModemBuffer[NonStdFrmPos][diag_pos+3]) << 16;
			BackUpDataLength |= (UDWORD)(MDM_ModemBuffer[NonStdFrmPos][diag_pos+4]) << 24;
			if (BackUpDataLength == 0) {
				return(DIAG_ERR);
			}
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
		}
#endif
	}
	else {
		return(DIAG_ERR);
	}
	/* 最後にパスコードの判定を行います */
	if (passcode_pos) {
		for(i = 0; i < 4; i++) {		/** 自機にパスコードがセットされているかどうか？ */
			if (SYB_DiagPasscodeNumber[i] != '0') {
				break;
			}
		}
		if (i == 4) {		/**	自機にパスコードがセットされていない 0000 がセットされている	*/
			for (i = 0; i < 4; i++) {	/** ホスト側パスコードチェック */
				pass_code = MDM_ModemBuffer[NonStdFrmPos][i+passcode_pos];
				if (pass_code < '0' || pass_code > '9') {	/** ホスト側パスコードチェック */
					break;
				}
			}
			if (i == 4) {	/** ホスト側にパスコードがセットされている */
				for (i = 0; i < 4; i++) {
					SYB_DiagPasscodeNumber[i] = MDM_ModemBuffer[NonStdFrmPos][i+passcode_pos];	/** パスコードコピー */
				}
			}
		}
		else {			/** 自機にパスコードがセットされている */
			for (i = 0; i < 4; i++) {
				pass_code = MDM_ModemBuffer[NonStdFrmPos][i+passcode_pos];
				if (pass_code != SYB_DiagPasscodeNumber[i]) {
					if (MDM_ModemBuffer[NonStdFrmPos][passcode_pos]   == 'R' &&
						MDM_ModemBuffer[NonStdFrmPos][passcode_pos+1] == 'I' &&
						MDM_ModemBuffer[NonStdFrmPos][passcode_pos+2] == 'C' &&
						MDM_ModemBuffer[NonStdFrmPos][passcode_pos+3] == 'E') {	/** ホスト側のパスコードが"Ｒ" "Ｉ" "Ｃ" "Ｅ"なら自機のパスコードクリア */

						SYB_DiagPasscodeNumber[0] = '0';
						SYB_DiagPasscodeNumber[1] = '0';
						SYB_DiagPasscodeNumber[2] = '0';
						SYB_DiagPasscodeNumber[3] = '0';
						break;
					}
					else {
						return(DIAG_ERR);
					}
				}
			}
		}
	}
	else {
		return(DIAG_ERR);
	}
	FaxComTXorRX_Sign = DIAG_MODE;
	SYS_FaxComType = SYS_REMOTE_DIAG;
	return(DIAG_TRUE);
}

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/03/31  By T.Yamaguchi */
/*************************************************************************
	module		:[]
	function	:[]
	commom		:[リモート診断でのフラッシュＲＯＭの書き込み可能な状態かチェックする
	]
	condition	:[]
	comment		:[]
	return		:[
	]
	machine		:[SH7043]
	language	:[]
	keyword		:[SHC]
	date		:[]
	author		:[山口]
*************************************************************************/
UBYTE	FlashRomWriteCheck(void)
{
	UBYTE error_status;
	UBYTE i;
	
	error_status = 0;
	
	error_status = RomFileModel_NameCheck();

	/* スキャナ送信予約がある場合にも、リモート書き換えを行なわないようにする 1998/11/04  By T.Yamaguchi */
	for (i = 0; i < SYS_COM_FILE_MAX; i ++)	 {	/* 最悪値424us poplar_l */
		if (SYB_CommandFile[i].Status != SYS_CMD_EMPTY) {
			if (CheckScannerCommand(i)) {	/* スキャナ送信コマンドなら */
				error_status |= 0x08;	/* SCANNER_USED_ERROR */
				break;
			}
		}
	}

	/* ＤＲＡＭ充電容量チェック */
	if (AD_Battery() <= 0x200){
		/* デバッグのため */
		if (SYB_MaintenanceSwitch[MNT_SW_E2] & 0x80) {
			error_status |= 0x00;	/* DRAM_BACKUP_ERROR */
		}
		else {
			error_status |= 0x20;	/* DRAM_BACKUP_ERROR */
		}
	}
	
	CMN_DisableInterrupt();	/* 割込み禁止 72us */

	/* 蓄積原稿状態チェック */
	if (MEM_TotalStoreBlockCounter) {
		error_status |= 0x02;	/* MEMORY_USED_ERROR */
	}

	/* リソース状況チェック */
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY) {
		error_status |= 0x08;	/* SCANNER_USED_ERROR */
	}
	
	/* if (CMN_CheckFaxComPrinterEnable() == FALSE) { */	/* 通信以外でプリンタが獲得されている */
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンターが使用中？ */
		error_status |= 0x04;	/* PRINTER_USED_ERROR */
	}

	if (CMN_CheckOptionBoardExecuting() == TRUE) {	/* ２回線／ＰＣプリント／回転ボード実行中 */
		error_status |= 0x10;	/* MULTI_LINE_USED_ERROR */
	}

	/* リソースの獲得 */
	if (error_status == 0) {
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
		SYS_DocumentPrintItem = SYS_MEM_FILE_EMPTY;	/* ROMデータ受信中に、PCﾌﾟﾘﾝﾄでｴﾗｰを返すため */
		SYB_FlashROM_WriteStatus = ROM_DATA_RXING;
		SYS_FaxCommStage = FCM_FLASH_ROM_WRITING;
	}

	CMN_EnableInterrupt();	/* 割り込み許可 72us */
	
	return (error_status);
}

/*************************************************************************
	module		:[]
	function	:[]
	commom		:[リモート診断でのフラッシュＲＯＭの書き込み可能な状態かチェックする
	]
	condition	:[]
	comment		:[]
	return		:[  0:OK
					1:NG
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DIAG]
	date		:[98/03/24]
	author		:[山口]
*************************************************************************/
UBYTE	RomFileModel_NameCheck(void)
{
	UBYTE check_point;
	UBYTE i;
	
	check_point = DiagPoint + 1;
	
	for (i = 0; i < 6;i++) {
		if (ROM_Revision[i] != MDM_ModemBuffer[FCF_Point][check_point + i]) {
			return(1);
		}
	}
	return(0);
}
#endif

#endif /* (PRO_DIAG == ENABLE) */ /* added by H.Kubo 1998/04/02 */
