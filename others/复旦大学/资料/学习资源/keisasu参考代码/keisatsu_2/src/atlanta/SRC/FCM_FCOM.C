/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_FCOM.C												 */
/*	モジュール	 :															 */
/*				 : AutoFax()												 */
/*				 : ManualTransmit()											 */
/*				 : ManualReceive()											 */
/*				 : AutoCalled()												 */
/*				 : FipFaxCom()												 */
/*				 : ManualPollingReceive() -- FX仕様							 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 : ＦＡＸ通信モジュール										 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"

#include "\src\atlanta\define\fcm_pro.h"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\atd_pro.h"

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/07/24 */
#include "\src\atlanta\mdm\orange\define\mdm_pro.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/07/24 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#endif

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"

#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\sysdoc.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\scn_data.h"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\cl1_data.h"
#endif
#if (PRO_LINENUMBER == TWICE_LINE)||(PRO_CIPHER == ENABLE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
#include "\src\atlanta\define\sys_stat.h"
#endif
#if (PRO_CLASS1 == ENABLE)	/* S.Fukui Jun.19,1998 */
 #if (PRO_RS_INTERNAL == ENABLE)	/* SH7043内蔵のシリアル有効 */
#include  "\src\atlanta\ext_v\cl1_data.h"	/* added by H.Hirao 1999/03/09 */
#include  "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#include  "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\cl1_def.h"
#endif
#if (PRO_FIP == ENABLE)
	#include "\src\atlanta\define\fip_def.h"
#endif

#if (PRO_PAT_JOURNAL == ENABLE)			/* 1995/01/27 */
	#include "\src\atlanta\define\pat_def.h"	/* Add by T.Nose 1995/12/15 */
	#include "\src\atlanta\define\pat_pro.h"
#endif
#include "\src\atlanta\define\std.h"		/* 96/06/06 */

#if (PRO_TX_SPEED == V34)
#include "\src\atlanta\define\man_pro.h" /* 1997/07/25 by H.Kubo */
#endif /* (PRO_TX_SPEED == V34) */

/* FCMタスクが生成されてからここにいたるまでに呼びしがくる場合がある（モデムの初期化に時間がかかりすぎ！！！）
** よって、ここにくる前に本当に呼び出し信号がきていないかを判断し、
** 　　きていない===>従来どおり発呼
** 　　きていた  ===>リダイヤルへ
** という風にする
** by O.Kimoto 2002/07/05
*/
#include "\src\atlanta\ext_v\ncu_data.h"

#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/12/18 */
/* POPLAR_H では、コードサイズを小さくする最適化コンパイルをしますが、
** そのままだと大量のスタックを消費します。そこで以下の #pragma によって
** 関数先頭での不要なレジスタ待避をさけます。
** 呼出し元で、#pragma noregalloc を宣言していることを確認してください。
** (SuperH RISC engine ファミリ C コンパイラ編 2-34 参照)
** 1997/12/18 H.Kubo
*/
#pragma noregalloc(AutoFax,AutoCalled,ManualTransmit,ManualReceive,ManualPollingReceive)
#if (PRO_FIP == ENABLE)
#pragma noregalloc(FipFaxCom)
#endif /* (PRO_FIP == ENABLE) */
#endif /* (PRO_MODEM == R288F) */


#if (0) /* コンパイルできる為　Smuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\r288f\define\mdm_io.h"		/* for test 2003/01/11 Y.Murata*/
#endif /* (PRO_MODEM == R288F) */

#if defined (KEISATSU) /* 警察FAX 05/09/21 石橋正和 */
#include "\src\atlanta\define\s1_def.h"
#endif


/*************************************************************************
	module		:[自動ダイアル通信]
	function	:[
		1. 発信スケジューラーに展開された通信時にコールされる
		2. ダイアル番号を取得しオート・ダイアラーをコールする
		3. 回線がつながったらＧ３モードで送信する
	]
	commom		:[
		SYB_DEUDialerFaultCounter		: ダイアル失敗カウンター（ドイツ仕様）
		SYS_RxReceiptRequestFlag		: 通信証受信要求
		AD_Result						: オートダイアラー戻り値
		FaxComStartTime					: 通信開始時刻
		FaxComPerformingFlag			: 通信中フラグ
		FaxComResult					: 通信結果
		CommandFileOptionItem			: 通信種別
		FaxComTXorRX_Sign				: 送信受信判別
		CommandFileTitleMessage			: カバーページ
		TxCoverPageFlag					: カバーページフラグ
		CommandFileConfirmationReport	: 通信証
		PollingTxFirstPageFlag			: ポーリング送信先頭ページフラグ
		TxSpeedHandshakeFlag			: 短縮ハンドシェークフラグ
		FaxComRxPerformingFlag			: 受信要求フラグ
		RxEOM_ReceiveFlag				: ＥＯＭ受信フラグ
		struct	DialingData_t		SYS_DialingNumber	: 多機能電話用バッファ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[1994/01/24]
	author		:[村田]
*************************************************************************/
void	AutoFax(void)
{
	UBYTE	rcr_check_flag;
	UWORD	timer;
#if (PRO_TX_SPEED == V34)
	UBYTE	loop; /* Added by H.Kubo 1997/07/24 */
	UBYTE ret_value;
#endif /* (PRO_TX_SPEED == V34) */
#if defined(DEU)
	UBYTE	is_autodialer_ok;
	is_autodialer_ok = 0;
#endif

	rcr_check_flag = 0;

#if (PRO_TX_SPEED == V34)	/**	Add by O.Kimoto 1997/11/21 */
	loop = 0;
#endif

/*	FaxcomRelayControl(); 2002/07/08 T.Takagi 移動 */			/** リレ～セット */
/*	FaxComUntilRecDISLineON();		/@ FaxcomRelayControlの中でモニタＯＮしているので削除する 95/12/07 t.yamaguchi */	/** ＤＩＳ受信まで回線モニタをＯＮする */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
	FaxComQuickTxLineON();
#endif

	/*---------------------------------------------------------------------
	** SAKAKIスキャナECM送信時には、MMRで送信するので、
	** SYS_FaxComTypeの値が決まった後に、再度符号化方式を決める関数を再度Callします
	** 1998/10/27 H.Yoshikawa
	*/
#if (PRO_SCN_CODEC_TYPE == IDP301)	/* SAKAKIではJBIGスキャナ送信なし 1998/10/27 H.Yoshikawa */
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
#endif
#if defined(POPLAR_F)	/* POPLAR_FではJBIGスキャナ送信なし */
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
#endif

	GetDialNumber();					/** ダイアル・ナンバー取得 */
	
#if defined (KEISATSU) /* 警察FAX 05/09/21 石橋正和 */
	FCM_S1_Scramble = FCM_ExecutingS1Info.Available;
	if (CMN_CheckScrambleSwOn() == FALSE) { /* 背面スイッチがOFFの場合 */
		FCM_S1_Scramble = FALSE;
	}
	
	if (FCM_ExecutingS1Info.Method == SYS_S1_SENYO) {
		FCM_S1_Senyo = TRUE;
	}
	else {
		FCM_S1_Senyo = FALSE;
	}
	
	if (SYS_FaxCommStage == FCM_POLLING) { /* ポーリングの場合 */
		FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;
		FCM_ExecutingS1Info.Available = FALSE;
		FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
		
		FCM_S1_Scramble = FALSE;
		FCM_S1_Senyo = FALSE;
	}
	
	if (FCM_S1_Scramble == TRUE) { /* スクランブル通信する場合 */
		CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
		if (AvailableTxBaudRate > S1_BAUD_RATE_MAX) {
			AvailableTxBaudRate = S1_BAUD_RATE_MAX; /* 送信可能ボーレイト */
		}
		AttemptTxBaudRate = AvailableTxBaudRate; /* 試行送信ボーレイト */
		V8ProcedureRequestFlag = 0; /* V8手順移行要求クリア */
	}
	
#endif

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/11/21 */
	MDM_SetOriginateMode();		/** モデムモードセット */
#endif

	FaxComTXorRX_Sign = TX_COM_MODE; /** 送信コマンド */ /* 1996/06/05 Y.Murata */
	
#if defined(STOCKHM2) /* DVT : add by SMuratec C.P 2004/09/08 */
	SYS_ConfirmTxRxFlag = 1;
#endif
	/*----------------------*/
	/** オート・ダイアラー **/
	/*----------------------*/
#if 0
** 	/* FCMタスクが生成されてからここにいたるまでに呼びしがくる場合がある（モデムの初期化に時間がかかりすぎ！！！）
** 	** よって、ここにくる前に本当に呼び出し信号がきていないかを判断し、
** 	** 　　きていない===>従来どおり発呼
** 	** 　　きていた  ===>リダイヤルへ
** 	** という風にする
** 	** by O.Kimoto 2002/07/05 YAWARAより移植 by T.Takagi 2002/07/08
** 	*/
	switch(AD_Result = AutoDial(SYS_DialingNumber.Buffer))]	 /* ﾀﾞｲｱﾙﾃﾞｰﾀﾊﾞｯﾌｧｰのﾎﾟｲﾝﾀｰ */
#else
	CMN_DisableInterrupt();
	if (CI_Counter_for_FCM <= 1) {
		/* CIは来ていなかった */
		CMN_EnableInterrupt();
		FaxcomRelayControl();				/** リレ～セット *//* 2001/08/06 Y.Murata 移動 */
	/*	FaxComUntilRecDISLineON();	*/		/** ＤＩＳ受信まで回線モニタをＯＮする */

		AD_Result = AutoDial(SYS_DialingNumber.Buffer);
	}
	else {
		CMN_EnableInterrupt();
		/* CIが来てた！！！！ */
		AD_Result = AD_REMOTE_BUSY;
	}

	switch (AD_Result) {
#endif

	case AD_OK				:
	case AD_OK_DSE			:
	case AD_OK_CED			:
	case AD_OK_DIS			:						/* CED/DIS どちらで検出したか区別するため追加 96/04/26 BY T.Y */
#if (PRO_SPEED_EX == ENABLE)
	case AD_OK_SPD_TONE		:
#endif
#if (PRO_TX_SPEED == V34)
#if (PRO_MODEM == R288F)
	case AD_OK_ANSWER_TONE	: /* Added by H.Kubo 1997/07/24 */
#endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */
		FaxComStartTime = SYB_CurrentTime;	/** 交信開始時間（秒） */
		/*
		** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
		** By S.Kawasaki 1996/09/02
		*/
		SYS_FCM_StartTime = SYS_1SecGeneralTimer;

		/* ジャーナルセット関数化 1996/11/29  By T.Yamaguchi */
		SetPatJournalDataAtAutoFax();

		FaxComPerformingFlag = 1;				/** 通信中フラグ */
#if defined(DEU)
		is_autodialer_ok = 1;
#endif
#if (PRO_TX_SPEED == V34)
		if ( (AD_Result == AD_OK) || (AD_Result == AD_OK_DIS) ) {	/* DIS only */
			V8ProcedureRequestFlag = 0;		/** Ｖ８モード移行要求クリア */
		}
 #if defined (KEISATSU) /* 警察FAX 05/06/24 石橋正和 */
		if (FCM_S1_Scramble == TRUE) { /* スクランブル通信の場合 */
			V8ProcedureRequestFlag = 0; /* V8モード移行要求クリア */
		}
 #endif
#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
		FaxComQuickTxLineOFF();
#endif

		break;
	case AD_LOCAL_BUSY		:
		DialError(0x01);
		break;
	case AD_REMOTE_BUSY		:
		DialError(0x02);
		break;
	case AD_TIME_OVER		:
		DialError(0x07);
		break;
	case AD_NO_DIAL_TONE	:
		DialError(0x08);
		break;
	case AD_NO_CURRENT_LOOP :
		DialError(0x09);
		break;
	case AD_STOPPED			:
		DialError(0x03);
		break;
	case AD_DIAL_EMPTY		:
		DialError(0x06);
		break;
#if 0	/* defined(FRA) *//* del by M.HARADA '96/11/15 *//* 95/01/21 by M.HARADA */
	case AD_DETECT_RINGBACKTONE	:
		DialError(0x06);
		break;
#endif
	default					:
		FaxComResult |= DIALERROR;
		FaxComPerformingFlag = 0;
		break;
	}

#if defined(DEU)
	if (is_autodialer_ok == 0) {	/* AD_ResultがＯＫでない場合 */
		SYS_CurrentExecutingCommand->Result = FaxComResult;
		SYB_DEUDialerFaultCounter++;
	}
#endif

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
	if (FCM_CheckV8ProcedureRequest()) {
		if (AD_Result == AD_OK_DSE) { /* オートダイヤラが極反検出なら */
#if defined(POPLAR_F)
			/*------------------------*/
			/*	 Dial - CNG Tx Wait	  */
			/*------------------------*/
			timer = ( UWORD )500;
			FaxTimer( timer );
#endif
			ret_value = FCM_AfterToneCheck(); /* トーン検出。(V25 ANS, CED, DIS)*/

			/* Ｖ．８ハンドシェーク中のノイズ対策で、最初の ANSam 検出の有効／無効の判断を追加。
			** ANSam 検出無効の場合は、極反検出後 DIS を見つけてもまだここでは V34 能力を無効にしない。
			** by H.Kubo 1999/04/26
			*/
 #if 0 /* Changed by H.Kubo 1999/04/26 */
@@			if (ret_value == T30_PROCEDURE) {
@@				FCM_CommunicationV8toT30();
@@			}
 #else
			if (ret_value == T30_PROCEDURE) {
				if ((FCM_ToneAfterDetectDCE != AD_OK_DIS) || !FCM_OverrideANSam() ) {
					FCM_CommunicationV8toT30();
				}
			}
 #endif
		}
	}

	/*--------------*/
	/* 通信開始処理 */
	/*--------------*/
	do {
		/*----------------------------*/
		/* Ｖ８モード移行要求チェック */
		/*----------------------------*/
		if (FCM_CheckV8ProcedureRequest()) {	/** Ｖ８移行要求がたっている？ */
			if (loop == 0) {
				StartUpData.Item = V34_STANDARD;
				StartUpData.Option.TransmitCI = 0;
			}
			else {
				StartUpData.Item = V34_MANUAL;
				StartUpData.Option.TransmitCI = TRANSMIT_CI_IN_V8;	/* CI transmit */
			}
			if (CheckCommnadFileTxItem()) {
				StartUpData.Direction = TX_COM_MODE;
				FaxComTXorRX_Sign = TX_COM_MODE;	/* 1996/10/04 Y.Murata    MURATTCH */
			}
			else {
				StartUpData.Direction = RX_COM_MODE;
				FaxComTXorRX_Sign = RX_COM_MODE;	/* 1996/10/04 Y.Murata    MURATTCH */
			}
			StartUpData.Allowed = StartUpData.Direction;
			ret_value = FCM_CallStartUpProcedure();	/** スタートアップ起呼処理 */
			V8ProcedureRequestFlag = 0;
			switch (ret_value) {
				case V34_PROCEDURE:

					/* Ｖ３４はＥＣＭ必須？ */
					TxECM_Ability = ECM_ON;					/** ＥＣＭ送信ＯＮ指定 */
					RxECM_Ability = ECM_ON;					/** ＥＣＭ受信ＯＮ指定 */
#if 0 /* Changed by H.Kubo 1998/01/27 */
@@					AvailableTxCodingMethod		= SYS_MR_CODE;				/** 機器の送信可能な符号化方式 */
@@					AvailableRxCodingMethod		= SYS_MR_CODE;				/** 機器の受信可能な符号化方式 */
@@					if (CHK_UNI_StoredMethodMMR()) {
@@						AvailableTxCodingMethod		= SYS_MMR_CODE;				/** 機器の送信可能な符号化方式 */
@@						AvailableRxCodingMethod		= SYS_MMR_CODE;				/** 機器の受信可能な符号化方式 */
@@					}
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */
@@					if (CHK_UNI_JBIG_TX_Enable()) {
@@						AvailableTxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
@@					}
@@					if (CHK_UNI_JBIG_RX_Enable()) {
@@						AvailableRxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
@@					}
#endif
#else
					SetAvailableCodingMethodEcmOn();
#endif /* 0 */
#if (0)
**					AvailableTxCodingMethod = FCM_GetMaxTxCodeForECM();	/** 機器の送信可能な符号化方式 */
**					AvailableRxCodingMethod = FCM_GetMaxRxCodeForECM();	/** 機器の受信可能な符号化方式 */
#endif
					SYS_V34ProcedureExecutingFlag = 1;
					break;
				case T30_PROCEDURE:
#if (PRO_JBIG == ENABLE)	/*  by H.Kubo 1998/10/01 */
 #if (PRO_SCN_CODEC_TYPE == IDP301)	/* SYS_FaxComType が確定してから改めて設定し直します。 1998/09/30 H.Kubo */
					if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
						if (CHK_UNI_StoredMethodMMR()) {
							AvailableTxCodingMethod = SYS_MMR_CODE;		/** 機器の送信可能な符号化方式 */
						}
						else {
							AvailableTxCodingMethod = SYS_MR_CODE;		/** 機器の送信可能な符号化方式 */
						}
					}
 #endif
 #if defined(POPLAR_F)	/* SYS_FaxComType が確定してから改めて設定し直します。*/
					if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
						if (CHK_UNI_StoredMethodMMR()) {
							AvailableTxCodingMethod = SYS_MMR_CODE;		/** 機器の送信可能な符号化方式 */
						}
						else {
							AvailableTxCodingMethod = SYS_MR_CODE;		/** 機器の送信可能な符号化方式 */
						}
					}
 #endif
#endif
					SYS_V34ProcedureExecutingFlag = 0;
					FCM_CommunicationV8toT30();
					break;

				/* 日立特許回避（ＣＥＤ検出） By O.Kimoto 1998/04/15 */
				case TONE_CHECK_TIME_OUT:
					AD_Result = AD_TIME_OVER;	/* とりあえず、タイムアップにしておきます。 */
					DialError(0x07);	/* Change 02 -> 07 by O.Kimoto 1998/04/22 */
					break;

				default:
					FaxComPerformingFlag = 0;
					break;
			}
		}
		loop = 0;
#endif /* (PRO_TX_SPEED == V34) */

		/*------*/
		/* 送信 */
		/*------*/

		if ((FaxComPerformingFlag == 1) && ( FCM_CheckCommandTRx() == COMMAND_KIND_TX)) {
			/*---------*/
			/*	G3 Tx  */
			/*---------*/
			FaxComTXorRX_Sign = TX_COM_MODE;	/** 送信コマンド */

			/**	スキャナ送信ならメインタスクにスキャナ送信起動メッセージを送り、
			**	メインタスクで読み取り装置(ADF/FBS)を決定して、ミラーキャリッジを移動させる
			*/	/* ICHOU用  1996/07/09 s.takeuchi */
			/* if (SYS_FaxComTxType == SYS_SCANNER_TX) { 1997/10/17  By T.Yamaguchi */
			if(SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
				MsgFromFaxComToMain.Message = MSG_FAXCOM_SCANNER_DECIDE;
				snd_msg( mbxno.MAN_Task, &MsgFromFaxComToMain );
				rcv_msg( mbxno.FCM_Task, &FcomMsg );

				SCN_Control.ScanPage = 0; /* 読取りページの初期化 T.Nose 1997/09/20 */
			}

			if ((CommandFileTitleMessage != 0xff) && !(SYS_CurrentExecutingCommand->Option & SYS_COVER_PAGE)) {		/** タイトル・メッセージ */
				/* １度送信したカバーページは、送信しない。判断追加 Y.Suzuki 94.10.5 */
				TxCoverPageFlag = 1;			/** カバーページ送信フラグ セット */
			}
			else {
				TxCoverPageFlag = 0;			/** カバーページ送信フラグ クリア */
			}

			/*--------------------------------------------------------------------*/
			/* メモリ残量が無い時はプリンタ受信をする機種でも受領証を要求しません -> 送信証をプリントする */
			/*--------------------------------------------------------------------*/
#if 0
//			if ( (((CommandFileConfirmationReport & SYS_RCR_REQUESTED) == SYS_RCR_REQUESTED)
//				 ||((CommandFileConfirmationReport & SYS_TCR_AND_RCR) == SYS_TCR_AND_RCR))		/* 条件追加 96/06/19 By T.Yamaguchi */
//			 && (CMN_CheckMemoryReceiveEnable() == 1) ) {	/** 受領証要求でメモリ受信可能 */
//				SYS_RxReceiptRequestFlag = 1;			/** 「受領証」要求フラグセット */
//			}
#endif
			if ( ((CommandFileConfirmationReport & SYS_RCR_REQUESTED) == SYS_RCR_REQUESTED)
			   ||((CommandFileConfirmationReport & SYS_TCR_AND_RCR) == SYS_TCR_AND_RCR))	{	/* 条件追加 96/06/19 By T.Yamaguchi */
				if (CMN_CheckMemoryReceiveEnable() == TRUE) {	/** 受領証要求でメモリ受信可能 代行受信件数とメモリ容量をチェック */
					SYS_RxReceiptRequestFlag = 1;			/** 「受領証」要求フラグセット */
				}
				else {	/* 受領証設定で、受信メモリがない場合は送信証プリントする add 1997/01/28  By T.Yamaguchi */
					CommandP->Option.ConfirmationReport |= SYS_TCR_AND_RCR;		/* 96/06/19 By T.Yamaguchi */
					SYS_CurrentExecutingCommand->Option |= SYS_PARTNER_NOT_RCR; /* 96/06/20 */
				}
			}

			PollingTxFirstPageFlag = 0;				/** ポーリング送信先頭ページフラグ */

#if (PRO_SPEED_EX == ENABLE)
			if ( (TxSpeedHandshakeFlag == 1)
			   &&( ((CHK_UNI_SpeedHandshakeEx() != 0) && (AD_Result == AD_OK_SPD_TONE))	/** 新短縮ハンドシェーク（着信トーン検出方式）*/
				|| ((CHK_UNI_SpeedHandshakeEx() == 0) && (AD_Result == AD_OK_DSE)) ) ) {/** 短縮ハンドシェーク（極反検出方式）*/

				FaxTxSpeedHandshake();				/** (SNSS)(STSI)SDCS Tx **/
			}
#else
			if ((TxSpeedHandshakeFlag == 1) &&
				 (AD_Result == AD_OK_DSE)) {		/** 短縮ハンドシェイク有効 */
					FaxTxSpeedHandshake();				/** (SNSS)(STSI)SDCS Tx **/
					/* TxSpeedHandshakeFlag = 0;*/ /** 短縮ハンドシェイク送信フラグクリア クリアする場所を検討すること By T.Y */ /* Deleted by H.Kubo 1998/02/20 */
			}
#endif
			else{
				if (TxSpeedHandshakeFlag == 1) {/* SDCS を送出しなくても、94/11/28 Y.Suzuki */
					TxSpeedHandshakeFlag = 0;		/** 短縮ハンドシェイク送信フラグクリア */
				}
				/*------------------------*/
				/*	 Dial - CNG Tx Wait	  */
				/*------------------------*/
#if (PRO_TX_SPEED == V34) && (PRO_MODEM == R288F) /* Modified by H.Kubo 1997/11/29 */
#if 0 /* Changed by H.Kubo 1998/05/25 */
@@				if ((AD_Result != AD_OK_ANSWER_TONE) && (AD_Result != AD_OK_DIS)
@@					&& (!TxSpeedHandshakeFlag) /* added by H.Kubo 1998/02/20 */
@@					) {		/* DIS検出でﾀﾞｲﾔﾗを抜けてきた場合ＮＳＦがとれない 96/04/25 By T.Y */
#else
				if ( ( ((AD_Result != AD_OK_ANSWER_TONE) && (AD_Result != AD_OK_DIS) )	/* ダイヤラーでトーン検出しなかったか、 */
				 ||    (( AD_Result == AD_OK_DSE) && !FCM_CheckToneDetectedInV8Mode() ) )	/* ダイヤラーで極反検出後、 ANSam 待ちでトーン検出しなかったか */
				 && (!TxSpeedHandshakeFlag) /* added by H.Kubo 1998/02/20 */
					) {		/* DIS検出でﾀﾞｲﾔﾗを抜けてきた場合ＮＳＦがとれない 96/04/25 By T.Y */
#endif
					timer = ( UWORD )500;
					FaxTimer( timer );
				}
#else /* (PRO_TX_SPEED == V34) && (PRO_MODEM == R288F) */
				if (AD_Result != AD_OK_DIS) {		/* DIS検出でﾀﾞｲﾔﾗを抜けてきた場合ＮＳＦがとれない 96/04/25 By T.Y */
					timer = ( UWORD )500;
					FaxTimer( timer );
				}
#endif /* (PRO_TX_SPEED == V34) && (PRO_MODEM == R288F) */
			}
			/*--------------*/
			/*	Tx Phase B	*/
			/*--------------*/
			FaxTransmit();							/** Ｇ３モードで送信 */
#if (PRO_TX_SPEED == V34) /* Changed by H.Kubo 1997/07/24 */
			if (FCM_CheckV8ProcedureRequest()) {	/** Ｖ８再度起動 */
				SYS_RxReceiptRequestFlag = 0;
				loop = 1;
			}
			else {
				rcr_check_flag = 1;
			}
#else /* (PRO_TX_SPEED == V34) */
			rcr_check_flag = 1;
#endif /* (PRO_TX_SPEED == V34) */
		}

		if ( (FaxComPerformingFlag == 1)
		&&	 ((FCM_CheckCommandTRx() == COMMAND_KIND_RX) || (SYS_RxReceiptRequestFlag == 1)) ) {
			/*----------------------------------------------------------*/
			/* ポーリング受信原稿及び受領証はリモートＦＡＸ原稿ではない */
			/*----------------------------------------------------------*/
			RemoteFaxON_Flag	= 0;
			RemoteFaxPRN_Flag	= 0;
			RemoteFaxDEL_Flag	= 0;

			/*------------------------*/
			/*	RCR Rx / Polling Rx	  */
			/*------------------------*/
			if(rcr_check_flag != 1){
				/*---------------*/
				/*	Polling Rx	 */
				/*---------------*/
				FaxComTXorRX_Sign = RX_COM_MODE;		/** 受信コマンドセット */
			}

#if (PRO_PANEL == KANJI)
			/* ＩＣＨＯＵからのフィードバック By O.Kimoto 1998/03/30 */
			/** 受領証 受信中表示に変えるため  1997/10/10 s.takeuchi */
			if (SYS_RxReceiptRequestFlag == 1) {
				SYS_FaxCommStage = FCM_RECEIVE;
				SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );
			}
#endif

			/*---------------*/
			/*	Rx Phase B1	 */
			/*---------------*/
			FaxPollingRxPhaseB1();						/** ポーリング受信フェーズＢ１ */
#if (PRO_TX_SPEED == V34) /* Changed by H.Kubo 1997/07/24 */
			if (FCM_CheckV8ProcedureRequest()) {	/** Ｖ８再度起動 */
				loop = 1;
			}
			else {
				while ((FaxComPerformingFlag == 1) && (FaxComRxPerformingFlag == 1)) {		/** 通信中で受信要求 */
					/*---------------*/
					/*	Rx Phase B2	 */
					/*---------------*/
					FaxReceive();							/** Ｇ３モードで受信 */
					if ((FaxComPerformingFlag == 1) && (RxEOM_ReceiveFlag == 1)) {		/** 通信中でＥＯＭ受信 */
						/*---------------*/
						/*	Rx Phase B1	 */
						/*---------------*/
						FaxRxPhaseB1();				/** 受信フェーズＢ１ */
					}
				}
			}
#else /* (PRO_TX_SPEED == V34) */
			while ((FaxComPerformingFlag == 1) && (FaxComRxPerformingFlag == 1)) {		/** 通信中で受信要求 */
				/*---------------*/
				/*	Rx Phase B2	 */
				/*---------------*/
				FaxReceive();							/** Ｇ３モードで受信 */
				if ((FaxComPerformingFlag == 1) && (RxEOM_ReceiveFlag == 1)) {		/** 通信中でＥＯＭ受信 */
					/*---------------*/
					/*	Rx Phase B1	 */
					/*---------------*/
					FaxRxPhaseB1();				/** 受信フェーズＢ１ */
				}
			}
#endif /* (PRO_TX_SPEED == V34) */
		} /* end of if (... (FCM_CheckCommandTRx() == COMMAND_KIND_RX)... ) */
#if (PRO_TX_SPEED == V34) /* Changed by H.Kubo 1997/07/24 */
	}while (loop == 1);
#endif /* (PRO_TX_SPEED == V34) */
}


/*************************************************************************
	module		:[手動送信]
	function	:[
		1. 回線につながった状態で送信を行う
	]
	commom		:[
		FaxComPerformingFlag			: 通信中フラグ
		FaxComStartTime					: 通信開始時刻
		FaxComTXorRX_Sign				: 送信受信判別
		TxCoverPageFlag					: カバーページフラグ
		TxReceiptRequestFlag			: 受領証送信要求
		SYB_ConfirmationReportSwitch	: 通信証スイッチ
		SYS_RxReceiptRequestFlag		: 受領証要求フラグ
		PollingTxFirstPageFlag			: ポーリング送信先頭ページフラグ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[1994/01/24]
	author		:[村田]
*************************************************************************/
void	ManualTransmit(void)
{
	UWORD	   timer;
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
	UBYTE	kind_of_procedure;
	UBYTE	loop;
#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_TX_SPEED == V34)	/**	Add by O.Kimoto 1997/11/21 */
	loop = 0;
#endif
	
#if defined (KEISATSU) /* 警察FAX 05/09/20 石橋正和 */
	/* SYS_InternalLineNumber = SYB_CommandKeisatsu[SYS_CurrentExecutingCommand->Number.Command].Line; */
	
	FCM_S1_Scramble = FCM_ExecutingS1Info.Available;
	if (CMN_CheckScrambleSwOn() == FALSE) { /* 背面スイッチがOFFの場合 */
		FCM_S1_Scramble = FALSE;
	}
	
	if (FCM_ExecutingS1Info.Method == SYS_S1_SENYO) {
		FCM_S1_Senyo = TRUE;
	}
	else {
		FCM_S1_Senyo = FALSE;
	}
	
	if (FCM_S1_Scramble == TRUE) { /* スクランブル通信する場合 */
		CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
		if (AvailableTxBaudRate > S1_BAUD_RATE_MAX) {
			AvailableTxBaudRate = S1_BAUD_RATE_MAX; /* 送信可能ボーレイト */
		}
		AttemptTxBaudRate = AvailableTxBaudRate; /* 試行送信ボーレイト */
		V8ProcedureRequestFlag = 0; /* V8手順移行要求クリア */
	}
#endif
	
	/*---------------------------------------------------------------------
	** SAKAKIスキャナECM送信時には、MMRで送信するので、
	** SYS_FaxComTypeの値が決まった後に、再度符号化方式を決める関数を再度Callします
	** 1998/10/27 H.Yoshikawa
	*/
#if (PRO_SCN_CODEC_TYPE == IDP301)	/* SAKAKIではJBIGスキャナ送信なし 1998/10/27 H.Yoshikawa */
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
#endif
#if defined(POPLAR_F)	/* POPLAR_FではJBIGスキャナ送信なし */
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
#endif
#if defined(POPLAR_F)	/* 1999/11/29 */
	SYS_BackUpConfirmationReport = SYB_ConfirmationReportSwitch;
#endif

	FaxComPerformingFlag = 1;

	/**	スキャナ送信ならメインタスクにスキャナ送信起動メッセージを送り、
	**	メインタスクで読み取り装置(ADF/FBS)を決定して、ミラーキャリッジを移動させる
	*/	/* ICHOU用  1996/07/09 s.takeuchi */
	/* if (SYS_FaxComTxType == SYS_SCANNER_TX) { 1997/10/17  By T.Yamaguchi */
	if(SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
		MsgFromFaxComToMain.Message = MSG_FAXCOM_SCANNER_DECIDE;
		snd_msg( mbxno.MAN_Task, &MsgFromFaxComToMain );
		rcv_msg( mbxno.FCM_Task, &FcomMsg );
	}

	FaxcomRelayControl();						/** リレ～セット */
#if defined(POPLAR_F)
	MDM_SetOriginateMode();		/** モデムモードセット */
#endif
	FaxComStartTime = SYB_CurrentTime;			/** 交信開始時刻 （秒） */

	/*
	** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
	** By S.Kawasaki 1996/09/02
	*/
	SYS_FCM_StartTime = SYS_1SecGeneralTimer;

	/*-----------------------*/
	/** ジャーナル通番セーブ */
	/*-----------------------*//* 1994/09/30 */
	JournalTxTotalCount				= SYB_TxTotalCount;			/* 通信開始時間と終了時間で日付が変わった場合は、 */
	JournalRxTotalCount				= SYB_RxTotalCount;			/* 通信開始時の日付に合わせるためにセーブしておく */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
	JournalTxTotalCountExt			= SYB_TxTotalCountExt;
	JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_JournalWorkFile.Number = JournalTxTotalCount;
	PAT_JournalWorkFile.StartTime = FaxComStartTime;
	if (SYS_FaxComType == SYS_MANUAL_TX) {
		PAT_JournalWorkFile.Kind = SYS_MANUAL_TRANSMIT;
	}
	else if (SYS_FaxComType == SYS_REMOTE_FAX_TX) {
		PAT_JournalWorkFile.Kind = SYS_REMOTE_TX;
	}

	PAT_JournalDataToImage(NUMBER);
	PAT_JournalDataToImage(START);
	PAT_JournalDataToImage(NOTE);
#endif

	FaxComTXorRX_Sign = TX_COM_MODE;			/** 送信コマンドセット */
	
#if defined(STOCKHM2) /* DVT : add by SMuratec C.P 2004/09/08 */
	SYS_ConfirmTxRxFlag = 1;
#endif

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
	/*------------------------------*/
	/* CNG TX or Detect ANSWER TONE *//* 1996/03/21 */
	/*------------------------------*/
	if (FCM_CheckV8ProcedureRequest()) {
		kind_of_procedure = FCM_AfterToneCheck();
		if (kind_of_procedure == T30_PROCEDURE) {
			FCM_CommunicationV8toT30();
		}
	}
#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
	do {
		/*----------------------------*/
		/* Ｖ８モード移行要求チェック */
		/*----------------------------*/
		if (FCM_CheckV8ProcedureRequest()) {	/** Ｖ８移行要求がたっている？ */
			if (loop == 0) {
				StartUpData.Item = V34_STANDARD;
				StartUpData.Option.TransmitCI = 0;
			}
			else {
				StartUpData.Item = V34_MANUAL;
				StartUpData.Option.TransmitCI = TRANSMIT_CI_IN_V8;	/* CI transmit */
			}
			StartUpData.Direction = TX_COM_MODE;
			StartUpData.Allowed = StartUpData.Direction;
			kind_of_procedure = FCM_CallStartUpProcedure();	/** スタートアップ起呼処理 */
			V8ProcedureRequestFlag = 0;
			switch (kind_of_procedure) {
				case V34_PROCEDURE:

					/* Ｖ３４はＥＣＭ必須？ */
					TxECM_Ability = ECM_ON;					/** ＥＣＭ送信ＯＮ指定 */
					RxECM_Ability = ECM_ON;					/** ＥＣＭ受信ＯＮ指定 */
					AvailableTxCodingMethod		= SYS_MR_CODE;				/** 機器の送信可能な符号化方式 */
					AvailableRxCodingMethod		= SYS_MR_CODE;				/** 機器の受信可能な符号化方式 */
					if (CHK_UNI_StoredMethodMMR()) {
						AvailableTxCodingMethod		= SYS_MMR_CODE;				/** 機器の送信可能な符号化方式 */
						AvailableRxCodingMethod		= SYS_MMR_CODE;				/** 機器の受信可能な符号化方式 */
					}
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */
  #if (PRO_SCN_CODEC_TYPE == IDP301)	/* SAKAKIではJBIGスキャナ送信なし 1998/09/30 H.Yoshikawa */
					SetAvailableCodingMethodEcmOn();	/* 1998/10/27 H.Yoshikawa */
#if (0)	/* 1998/10/27 */
//					if (CHK_UNI_JBIG_RX_Enable()) {
//						AvailableRxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
//					}
#endif
  #else
  	#if defined(POPLAR_F)
					SetAvailableCodingMethodEcmOn();
  	#else
					if (CHK_UNI_JBIG_TX_Enable()) {
						AvailableTxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
					}
					if (CHK_UNI_JBIG_RX_Enable()) {
						AvailableRxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
					}
	#endif
  #endif
#endif
#if (0)
**					AvailableTxCodingMethod = FCM_GetMaxTxCodeForECM();	/** 機器の送信可能な符号化方式 */
**					AvailableRxCodingMethod = FCM_GetMaxRxCodeForECM();	/** 機器の受信可能な符号化方式 */
#endif
					SYS_V34ProcedureExecutingFlag = 1;
					break;
				case T30_PROCEDURE:
#if (0)	/* たぶん、不要です。後で削除します 1998/10/27 H.Yoshikawa */
//#if (PRO_JBIG == ENABLE)	/*  by H.Kubo 1998/10/23 */
// #if (PRO_SCN_CODEC_TYPE == IDP301)	/* SYS_FaxComType が確定してから改めて設定し直します。 1998/09/30 H.Kubo */
//					if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
//						if (CHK_UNI_StoredMethodMMR()) {
//							AvailableTxCodingMethod = SYS_MMR_CODE;		/** 機器の送信可能な符号化方式 */
//						}
//						else {
//							AvailableTxCodingMethod = SYS_MR_CODE;		/** 機器の送信可能な符号化方式 */
//						}
//					}
// #endif
//#endif
#endif

					SYS_V34ProcedureExecutingFlag = 0;
					FCM_CommunicationV8toT30();
					break;
				default:
					FaxComPerformingFlag = 0;
					break;
			}
		}
		loop = 0;

		if (FaxComPerformingFlag == 1) {
#endif /* (PRO_TX_SPEED == V34) */


			if( CHK_MessageTxON() != 0 ) {				/** メッセージ送信要求 */
				TxCoverPageFlag = 1;					/** カバーページフラグ セット */
			}
			else {
				TxCoverPageFlag = 0;					/** カバーページフラグ クリア */
			}

			/*---------*/
			/*	G3 Tx  */
			/*---------*/
			TxReceiptRequestFlag = 0;					/** 受領証送信フラグ クリア */

#if 0	/* POPLAR変更 1997/03/07  By T.Yamaguchi */
//	if((SYB_ConfirmationReportSwitch == RCR_REQUEST)
//	&& (CMN_CheckMemoryReceiveEnable() == 1)) {			/** メモリ受信可能 */
//		SYS_RxReceiptRequestFlag = 1;					/** 「受領証」要求フラグセット */
//		}
#endif

#if defined(POPLAR_F)
#else
			SYS_BackUpConfirmationReport = SYB_ConfirmationReportSwitch;
#endif
			if(SYS_BackUpConfirmationReport == RCR_REQUEST) {
				if(CMN_CheckMemoryReceiveEnable() == TRUE) {	/** メモリ受信可能 */
					SYS_RxReceiptRequestFlag = 1;					/** 「受領証」要求フラグセット */
				}
			}

			/*----------------------------------------------*/
			/* リモートＦＡＸ送信では受領証の要求はしません */
			/*						 カバーページ送信しない */
			/*----------------------------------------------*/
#if (PRO_REMOTE_FAX == ENABLE)
			if (SYS_FaxComType == SYS_REMOTE_FAX_TX) {	/** リモートＦＡＸ送信 */
				SYS_RxReceiptRequestFlag = 0;					/** 「受領証」要求フラグ強制クリア */
				TxCoverPageFlag = 0;							/** カバーページフラグ クリア */
			}
#endif

			SYS_CurrentExecutingCommand = 0x00;		/* NULL */
			PollingTxFirstPageFlag = 0;
			/*------------------------*/
			/*	 Dial - CNG Tx Wait	  */
			/*------------------------*/
#if defined(DEU) || defined(EUR)	/* by M.H '97/03/21 for CNG Tx timing from holding the line (1.5 +- 1sec) */
									/* 欧州仕様追加 by M.H 1999/09/16 */
			timer = ( UWORD )1500;
#else
			timer = ( UWORD )500;
#endif
			FaxTimer( timer );
			/*-----------*/
			/*	Phase B	 */
			/*-----------*/
			FaxTransmit();						/** Ｇ３モードで送信 */
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
			if (FCM_CheckV8ProcedureRequest()) {	/** Ｖ８再度起動 */
				SYS_RxReceiptRequestFlag = 0;
				loop = 1;
			}
			else {
				loop = 0;
			}
		}

	}while(loop == 1);
#endif /* (PRO_TX_SPEED == V34) */

	if ((FaxComPerformingFlag == 1) && (SYS_RxReceiptRequestFlag == 1)) {	/** 受領証要求 */
		/*------------------------------------*/
		/* 受領証はリモートＦＡＸ原稿ではない */
		/*------------------------------------*/
		RemoteFaxON_Flag	= 0;
		RemoteFaxPRN_Flag	= 0;
		RemoteFaxDEL_Flag	= 0;

#if (PRO_PANEL == KANJI)
		/* ＩＣＨＯＵからのフィードバック By O.Kimoto 1998/03/30 */
		/** 受領証 受信中表示に変えるため  1997/10/10 s.takeuchi */
		SYS_FaxCommStage = FCM_RECEIVE;
		SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );
#endif

		/*----------*/
		/*	RCR Rx	*/
		/*----------*/
		FaxPollingRxPhaseB1();			/** ポーリング受信フェーズＢ１ */
		while ((FaxComPerformingFlag == 1) && (FaxComRxPerformingFlag == 1)) {		/** 通信中で受信要求 */
			FaxReceive();				/** Ｇ３モードで受信 */
			if ((FaxComPerformingFlag == 1) && (RxEOM_ReceiveFlag == 1)) {		/** 通信中でＥＯＭ受信 */
				FaxRxPhaseB1();				/** 受信フェーズＢ１ */
			}
		}
	}
}


/*************************************************************************
	module		:[手動受信]
	function	:[
		1. 回線につながった状態で受信処理をおこなう
	]
	commom		:[
		FaxComPerformingFlag		: 通信中フラグ
		FaxComStartTime				: 通信開始時刻
		FaxComTXorRX_Sign			: 送信受信判別
		FinalRxMode					: 確定受信モード
		RxEOM_ReceiveFlag			: ＥＯＭ受信フラグ
		PollingTxFirstPageFlag		: ポーリング送信先頭ページフラグ
		FaxComTxPerformingFlag		: 送信要求フラグ
		TxReceiptRequestFlag		: 受領証要求フラグ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[1994/01/24]
	author		:[村田]
*************************************************************************/
void	ManualReceive(void)
{
#if (PRO_TX_SPEED == V34) /* POPLAR_H のスタック節約のために変更。H.Kubo 1997/12/18  */
#else /* (PRO_TX_SPEED == V34) */
	UWORD		timer;
#endif /* (PRO_TX_SPEED == V34) */
	UBYTE		rcr_check_flag;
	UBYTE	debug_yama;
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
	UBYTE		loop;
	UBYTE		ret_value;
	UBYTE	counter;
	counter = 0;
	loop = 0; 	/**	Add by O.Kimoto 1997/11/21 */
#endif /* (PRO_TX_SPEED == V34) */
	debug_yama = 0;

	/*---------------------------------------------------------------------
	** SAKAKIスキャナECM送信時には、MMRで送信するので、
	** SYS_FaxComTypeの値が決まった後に、再度符号化方式を決める関数を再度Callします
	** 1998/10/27 H.Yoshikawa
	*/
#if (PRO_SCN_CODEC_TYPE == IDP301)	/* SAKAKIではJBIGスキャナ送信なし 1998/10/27 H.Yoshikawa */
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
#endif
#if defined(POPLAR_F)	/* POPLAR_FではJBIGスキャナ送信なし */
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
#endif

	rcr_check_flag		 = 0;
	FaxComPerformingFlag = 1;		/** 通信中フラグセット */
	FCM_ReceiveResponseTime = TIME_OVER_45SEC;	/* T4_Timer Set 1995/12/19 */

	FaxcomRelayControl();						/** リレ～セット */
#if defined(POPLAR_F)
	MDM_SetAnswerMode();			/** モデムモードセット */
#endif
	FaxComStartTime = SYB_CurrentTime;		/** 交信開始時刻（秒） */

	/*
	** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
	** By S.Kawasaki 1996/09/02
	*/
	SYS_FCM_StartTime = SYS_1SecGeneralTimer;

	/*-----------------------*/
	/** ジャーナル通番セーブ */
	/*-----------------------*//* 1994/09/30 */
	JournalTxTotalCount				= SYB_TxTotalCount;			/* 通信開始時間と終了時間で日付が変わった場合は、 */
	JournalRxTotalCount				= SYB_RxTotalCount;			/* 通信開始時の日付に合わせるためにセーブしておく */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
	JournalTxTotalCountExt			= SYB_TxTotalCountExt;
	JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_JournalWorkFile.Number = JournalRxTotalCount;
	PAT_JournalWorkFile.StartTime = FaxComStartTime;
	PAT_JournalWorkFile.Kind = SYS_MANUAL_RECEIVE;

	PAT_JournalDataToImage(NUMBER);
	PAT_JournalDataToImage(START);
	PAT_JournalDataToImage(NOTE);
#endif

	FaxComTXorRX_Sign = RX_COM_MODE;		/** 受信コマンドセット */
	
#if defined(STOCKHM2) /* DVT : add by SMuratec C.P 2004/09/08 */
	SYS_ConfirmTxRxFlag = 0;
#endif

	/*--------------------------------------*/
	/* 手動受信ではリモートＦＡＸ受信は無効 */
	/*--------------------------------------*/
	RemoteFaxON_Flag	= 0;
	RemoteFaxPRN_Flag	= 0;
	RemoteFaxDEL_Flag	= 0;

	/*---------------------------------------------------*/
	/*	CALLED - CED Wait [FTZ TR2 Vol.2,3.2.6.2.1.1.7]	 */
	/*---------------------------------------------------*/
#if (PRO_TX_SPEED == V34) /* POPLAR_H のスタック節約のために変更。H.Kubo 1997/12/18  */
	FaxTimer(  ( UWORD )2000 );
#else /* (PRO_TX_SPEED == V34) */
	timer = ( UWORD )2000;
	FaxTimer( timer );
#endif /* (PRO_TX_SPEED == V34) */
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
/*==== only for V34 ===*/

	do {
		if (FCM_CheckV8ProcedureRequest()) {	/** Ｖ８実行可能 */
			if (loop == 0) {
				StartUpData.Item = V34_STANDARD;
				StartUpData.Option.TransmitCI = 0;
			}
			else {
				StartUpData.Item = V34_MANUAL;
				StartUpData.Option.TransmitCI = 0;
					counter++;
					if (counter > 5) {
						/* SYS_DataSignalingRate &= 0xFFFE; */
						CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
					}
			}
			StartUpData.Direction = TX_COM_MODE;
#if (0)	/* 1998/1/29 by T.Soneoka */
//			if ((SYB_PollingDocumentStatus == 1) || (SYB_DB_PollingDocumentStatus == 1)) {
#endif
#if (0)	/*  by H.Kubo 1998/04/27 */
** 	/* メモリスイッチＨ：２－１を０にしたときに、ポーリング原稿の権利を放さないと
** 	** いう不具合が発生したので
** 	** By O.Kimoto 1997/07/07
** 	*/
** 			if ((SYB_PollingDocumentStatus == 1)
#else

#if (0)
** 			/* PRO_MULTI_LINE == DISABLEの処理が入っていない。 By O.Kimoto 1998/06/24 */
** 		 	if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
#else

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
** 	#if (PRO_MULTI_LINE == ENABLE)
** 		 	if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
** 	#else
** 			if ((SYB_PollingDocumentStatus == 1)
** 	#endif
#else
		 	if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
#endif

#endif

#endif
			|| (SYB_DB_PollingDocumentStatus == 1)
			|| (SYB_SelectPollDocumentStatus == 1)
			|| (CheckPollingTxType() != 0) /* added by H.Kubo 1998/04/27 */
			|| (CHK_UNI_FcodeSecureDocPollTx())) {
				StartUpData.Allowed = (TX_COM_MODE | RX_COM_MODE);
			}
			else {
				StartUpData.Allowed = TX_COM_MODE;
			}
			ret_value = FCM_AnswerStartUpProcedure();	/** スタートアップ応答処理 */
			V8ProcedureRequestFlag = 0;
			switch (ret_value) {
				case V34_PROCEDURE:
					/* Ｖ３４はＥＣＭ必須？ */
					TxECM_Ability = ECM_ON;					/** ＥＣＭ送信ＯＮ指定 */
					RxECM_Ability = ECM_ON;					/** ＥＣＭ受信ＯＮ指定 */
					AvailableTxCodingMethod		= SYS_MR_CODE;				/** 機器の送信可能な符号化方式 */
					AvailableRxCodingMethod		= SYS_MR_CODE;				/** 機器の受信可能な符号化方式 */
					if (CHK_UNI_StoredMethodMMR()) {
						AvailableTxCodingMethod		= SYS_MMR_CODE;				/** 機器の送信可能な符号化方式 */
						AvailableRxCodingMethod		= SYS_MMR_CODE;				/** 機器の受信可能な符号化方式 */
					}
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */
  #if (PRO_SCN_CODEC_TYPE == IDP301)	/* SAKAKIではJBIGスキャナ送信なし 1998/09/30 H.Yoshikawa */
					SetAvailableCodingMethodEcmOn();	/* 1998/10/27 H.Yoshikawa */
#if (0)	/* 1998/10/27 */
//					if (CHK_UNI_JBIG_RX_Enable()) {
//						AvailableRxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
//					}
#endif
  #else
  	#if defined(POPLAR_F)
					SetAvailableCodingMethodEcmOn();
  	#else
					if (CHK_UNI_JBIG_TX_Enable()) {
						AvailableTxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
					}
					if (CHK_UNI_JBIG_RX_Enable()) {
						AvailableRxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
					}
	#endif
  #endif
#endif
#if (0)
**					AvailableTxCodingMethod = FCM_GetMaxTxCodeForECM();	/** 機器の送信可能な符号化方式 */
**					AvailableRxCodingMethod = FCM_GetMaxRxCodeForECM();	/** 機器の受信可能な符号化方式 */
#endif
					SYS_V34ProcedureExecutingFlag = 1;
					break;
				case T30_PROCEDURE:
					SYS_V34ProcedureExecutingFlag = 0;
					FCM_CommunicationV8toT30();
					break;
				default:
					FaxComPerformingFlag = 0;
					break;
			}
		}
		else {
			/*----------*/
			/*	CED Tx	*/
			/*----------*/
			FaxTransmitCED();				/** ＣＥＤ送出 */
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/07/24 */
			MDM_ConfigReset();				/** モデム・リセット */
#endif /* (PRO_MODEM == ORANGE3) */

		}

		if (FaxComPerformingFlag == 1) {
			if (SYS_V34ProcedureExecuting() == 0) {
				/* if (FSKCONFIG_DEBUG == 0) { /@ for debug. FSKCONFIG_DEBUG was in mdm.c */
			/*----------------------------------------------------*/
			/*	CED - NSF Wait 75±20ms[CCITT/FTZ18TR53 Fig11-1]  */
			/*----------------------------------------------------*/
#if (0) /* Modified by H.Kubo 1997/12/18 */
@@			timer = CHK_WaitAfterDIS();		/** CED送出後NSF送出までの時間75m秒/1000m秒の獲得 */
@@/* #if defined(DEU)1997/06/02  By T.Yamaguchi */	/* by M.H '97/03/21 for timing between CED and DIS */
@@			TimerCutStatus = 1;
@@/* #endif */
@@			FaxTimer( timer );
#else
/* #if defined(DEU)1997/06/02  By T.Yamaguchi */	/* by M.H '97/03/21 for timing between CED and DIS */
			TimerCutStatus = 1;
/* #endif */
			FaxTimer( (UWORD) CHK_WaitAfterDIS() ); /** CED送出後NSF送出までの時間75m秒/1000m秒の獲得 */
#endif /* (0) */
				/* }
				else {
					MDM_InitialConfig2(2);
				} /@ for debug. If you use FSKCONFIG_DEBUG, delete the comments. */
			}

			/*------------*/
			/*	Phase B1  */
			/*------------*/
			FaxRxPhaseB1();						/** 受信フェーズＢ１ */
			loop = 1;
		}
	}while(FCM_CheckV8ProcedureRequest());

#else /* (PRO_TX_SPEED == V34) */
/*==== V33 or lower ===*/

	/*----------*/
	/*	CED Tx	*/
	/*----------*/
	if (debug_yama == 1) {
		FCM_ReceiveResponseTime = TIME_OVER_3SEC;
		MDM_ReceiveResponse(FCM_ReceiveResponseTime);
	}

	FaxTransmitCED();				/** ＣＥＤ送出 */
#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/07/24 */
	MDM_ConfigReset();				/** モデム・リセット */
#endif /* (PRO_MODEM == ORANGE3) */

	/*----------------------------------------------------*/
	/*	CED - NSF Wait 75±20ms[CCITT/FTZ18TR53 Fig11-1]  */
	/*----------------------------------------------------*/
	timer = CHK_WaitAfterDIS();		/** CED送出後NSF送出までの時間75m秒/1000m秒の獲得 */
/* #if defined(DEU)1997/06/02  By T.Yamaguchi */	/* by M.H '97/03/21 for timing between CED and DIS */
	TimerCutStatus = 1;
/* #endif */
	FaxTimer( timer );

	if (debug_yama == 2) {
		FCM_ReceiveResponseTime = TIME_OVER_3SEC;
		MDM_ReceiveResponse(FCM_ReceiveResponseTime);
	}

	/*------------*/
	/*	Phase B1  */
	/*------------*/
	FaxRxPhaseB1();						/** 受信フェーズＢ１ */
#endif /* (PRO_TX_SPEED == V34) */
/*=== end of V33 or lower ====*/


	while ((FaxComPerformingFlag == 1) && (FaxComRxPerformingFlag == 1)) {		/** 通信中で受信要求 */
		switch (FinalRxMode){		/** 確定受信モード */
			case G2MODE :
						   /*----------------*/
						   /*  G2 / Mini Rx	 */
						   /*----------------*/
						   break;
			case G3MODE :
						   /*--------------*/
						   /**	Ｇ３モード */
						   /*--------------*/
						   rcr_check_flag = 1;
						   FaxReceive();				/** Ｇ３モードで受信 */
						   break;
			/* 手動受信のリモート診断のパス追加 1997/06/25  By T.Yamaguchi */
#if (PRO_DIAG == ENABLE) /* by H.Kubo 1998/04/02 */
			case DIAGMODE :
							/*-------------------------*/
							/*	Remote Diagnostics Rx  */
							/*-------------------------*/
							RemoteDiagnostic();		/** リモート診断 */
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)	/* 1998/03/31  By T.Yamaguchi */
							if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
								RxEOM_ReceiveFlag = 1;		/** Ｇ３モードで受信 */
							}
#endif
							break;
#endif /* (PRO_DIAG == ENABLE) */
			default		:
						   break;
		}

		if ((FaxComPerformingFlag == 1) && (RxEOM_ReceiveFlag == 1)) {		/** 通信中でＥＯＭ受信 */
			/*---------------*/
			/*	Rx Phase B1	 */
			/*---------------*/
			FaxRxPhaseB1();								/** 受信フェーズＢ１ */
		}
	}

	PollingTxFirstPageFlag = 0;

	if ((FaxComPerformingFlag == 1)
	&&	(FaxComTxPerformingFlag == 1)) {
		/*------------------------------------------------------------------*/
		/** 受領証送信用通信時間算出										*/
		/* (受領証に通信時間をのせるため受領証送信前までの通信時間を求める) */
		/*------------------------------------------------------------------*/
		FaxComPeriod = (UWORD)(SYB_CurrentTime - FaxComStartTime);

		/*
		** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
		** By S.Kawasaki 1996/09/02
		*/
		FaxComPeriod = (UWORD)(SYS_1SecGeneralTimer - SYS_FCM_StartTime);

		/*-----------------------*/
		/*	Polling Tx / RCR Tx	 */
		/*-----------------------*/
		PollingTxFirstPageFlag = 1;
		if( rcr_check_flag == 1 ){
			/*----------*/
			/*	RCR Tx	*/
			/*----------*/
			/* 他社機からターンアラウンドポーリング要求があった時
			** ポーリング原稿が蓄積されていたら、受領証を送出していた
			** 受領証要求のときのみ出す様に変更
			*/
			if (TxReceiptRequestFlag) {	/* 受領証要求有りなら Oct.15.1997  By T.Yamaguchi */
				TxRCR_Flag = 1;
			}
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
			if (SYS_V34ProcedureExecuting() == 1) {

				/*---------------------------------------*/
				/* コントロールチャネル ｔｕｒｎ－ｏｆｆ */
				/*---------------------------------------*/
				/*if (V34_ControlChanelTurnOff()) {*/
				if (FCM_ControlChTurnaroundTurnOff()) {
					/*-------------------------*/
					/** スタートアップ応答処理 */
					/*-------------------------*/
					StartUpData.Item = V34_TURNAROUND;
					StartUpData.Direction = RX_COM_MODE;
					StartUpData.Allowed = RX_COM_MODE;
					StartUpData.Option.TransmitCI = 0;

					ret_value = FCM_AnswerStartUpProcedure();
					switch (ret_value) {
						case V34_PROCEDURE:
							break;
						case T30_PROCEDURE:
							FaxComPerformingFlag = 0;
							break;
						default:
							FaxComPerformingFlag = 0;
							break;
					}
				}
				else {
					FaxComPerformingFlag = 0;
					ReceiveError(0x16);
				}
			}
#endif /* (PRO_TX_SPEED == V34) */
		}
		else {
			/*--------------*/
			/*	Polling Tx	*/
			/*--------------*/
			/* 手動着信からのDBﾎﾟｰﾘﾝｸﾞ送信 でﾘｾｯﾄに飛ぶ不具合があった */
			/* 下記のﾊﾟﾗﾒｰﾀがｾｯﾄされてませんでした。 By Y.Suzuki 2000/02/01 */
			SYS_FaxComTxType = SYS_MEMORY_TRANSMIT;/* By Y.Suzuki 2000/02/01 */
			
			FaxComTXorRX_Sign = TX_COM_MODE;		/** 送信コマンドセット */

#if (PRO_PAT_JOURNAL == ENABLE)	/* 1996/09/04 Y.M */
			PAT_JournalWorkFile.Number = JournalTxTotalCount;
			PAT_JournalDataToImage(NUMBER);
#endif

#if (PRO_MEM_RX_REJECT == ENABLE) || (PRO_PRINTER_RX == ENABLE) /* changed by H.Hirao 1998/12/25 */
/* #if(PRO_MEM_RX_REJECT == ENABLE) @* MOMIJI のみ 94/11/7 Y.Suzuki */
			/* MOMIJI プリンタ開放のため 94/11/7 Y.Suzuki */
			MsgFromFaxComToMain.Item = FROM_FAXCOM;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_TX_START;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
			rcv_msg(mbxno.FCM_Task, &FcomMsg);		/* メインよりメッセージ受信 */
#endif

#if defined (KEISATSU) /* 警察FAX 05/12/01 石橋正和 */
			/* ポーリングはノンスクランブル */
			FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;
			FCM_ExecutingS1Info.Available = FALSE;
			FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
			
			FCM_S1_Scramble = FALSE;
			FCM_S1_Senyo = FALSE;
#endif
		}
		SYS_CurrentExecutingCommand = 0x00;		/* NULL */
		/*--------------*/
		/*	Tx Phase B	*/
		/*--------------*/
		FaxTransmit();					/** Ｇ３モードで送信 */
		TxRCR_Flag = 0;
	}
	TxReceiptRequestFlag = 0;				/** 受領証要求フラグ */
}


/*************************************************************************
	module		:[自動着信]
	function	:[
		1. 受信処理を行う

	]
	commom		:[
		FaxComPerformingFlag		: 通信中フラグ
		FaxComTXorRX_Sign			: 送信受信判別
		ForwardReceiveFlag			: オンフックで着信
		FaxNetReceiveFlag			: Ｆネット
		SYB_DialInNoNumberSignal	: ダイヤル・イン回線接続
		AttemptRxModeSwitch			: 待機モード
		SYS_RingCounter				: リングカウンター
		FaxTelOffHookFlag			: オフフックフラグ
		RxSpeedHandshakeFlag		: 短縮ハンドシェーク受信フラグ
		FaxComStartTime				: 通信開始時刻
		FaxComRxPerformingFlag		: 受信要求フラグ
		FinalRxMode					: 受信モード
		RxEOM_ReceiveFlag			: ＥＯＭ受信フラグ
		FaxComTxPerformingFlag		: 送信要求フラグ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[1994/01/24]
	author		:[村田]
*************************************************************************/
void	AutoCalled(void)
{

	UWORD	   timer;
	UBYTE	   rcr_check_flag;
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/03  By T.Yamaguchi */
	UBYTE	   receive_dcs_flag;
#endif

#if (PRO_TX_SPEED == V34 ) /* Added by H.Kubo for V8/V34 1997/07/24 */
	UBYTE	ret_value;
	UBYTE	loop;
	UBYTE	counter;

	loop = 0;
	counter = 0;
#endif
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/03  By T.Yamaguchi */
	receive_dcs_flag = 0;
#endif

	/*---------------------------------------------------------------------
	** SAKAKIスキャナECM送信時には、MMRで送信するので、
	** SYS_FaxComTypeの値が決まった後に、再度符号化方式を決める関数を再度Callします
	** 1998/10/27 H.Yoshikawa
	*/
#if (PRO_SCN_CODEC_TYPE == IDP301)	/* SAKAKIではJBIGスキャナ送信なし 1998/10/27 H.Yoshikawa */
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
#endif
#if defined(POPLAR_F)	/* POPLAR_FではJBIGスキャナ送信なし */
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
#endif

	rcr_check_flag		 = 0;
	FaxComPerformingFlag = 1;			/** 通信中フラグセット */

	FaxcomRelayControl();				/** リレ～セット */
#if defined(POPLAR_F)
	MDM_SetAnswerMode();			/** モデムモードセット */
#endif
	FaxComTXorRX_Sign = RX_COM_MODE;	/** 受信コマンドセット */
	
#if defined(STOCKHM2) /* DVT : add by SMuratec C.P 2004/09/08 */
	SYS_ConfirmTxRxFlag = 0;
#endif

	/*-----------*/
	/*	Rx Mode	 */
	/*-----------*/
	/* ＴＥＬ／ＦＡＸ待機　ダイヤルイン待機でダイヤルイン回線接続　留守／ＦＡＸ待機でＦＡＸ／ＴＥＬ待機の様に着信させる場合	 */
	if (!ForwardReceiveFlag &&
		!FaxNetReceiveFlag &&
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
		(SYS_InternalLineNumber == SYS_STD_LINE_COM) &&		/**	標準ラインにて受信時	*/
#endif
		((AttemptRxModeSwitch == SYS_TEL_FAX_READY)

		|| (AttemptRxModeSwitch == SYS_FAX_TEL_READY) /* '95,12,27 By N.S. */

#if (PRO_DIALIN == ENABLE)
		|| (AttemptRxModeSwitch == SYS_DIAL_IN_READY && SYB_DialInNoNumberSignal)
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/15 */
		|| ( AttemptRxModeSwitch == SYS_MODEM_DIALIN_READY && SYB_DialInNoNumberSignal)
#endif
#if 0 /* (PRO_BUILTIN_TAD == DISABLE) 1997/02/15  By T.Yamaguchi ポプラ／ＡＮＺＵは要らない */
		|| (AttemptRxModeSwitch == SYS_ANS_FAX_READY && SYS_TadToTelFaxChangeModeFlag)
#endif
		)) {
		/*----------------*/
		/*	TEL/FAX Mode  */
		/*----------------*/
		 FaxTelResult = FaxTelAutoSwitch();		/** ＴＥＬ／ＦＡＸ切替え処理 */

		FCM_Is_ToneDetecting = NO;	/* CNG検出終了 */

#if 0 /* (PRO_NCU_TYPE == LAVENDER_USA_TYPE) */
		if (CHK_LineMonitor()) {			/* 1994/08/10 GenerateRingSignal Debug */
			SpeakerOutSelectMonitor();
			MonitorSpeakerOn();
		}
#endif

		if (( FaxTelResult == FCOM_TEL1_OFF_HOOK)
		||	( FaxTelResult == FCOM_TEL2_OFF_HOOK)
/*
** ＴＥＬ／ＦＡＸ待機で着信した後、タイムオーバで抜けてきた場合、
** 次にＴＥＬオフフック・オンフックで転送受信してしまう不具合
** SYS_RingCounterがリセットされないので発生しています－＞リセットするように変更します
** by T.Soneoka 1997/11/07
*/
#if (0)
//		||	( FaxTelResult == TMOUT_RESP)
#endif
		||	( FaxTelResult == FCOM_HOOK_KEY )) {
			FaxTelAutoSWAfterTransaction();
		}
/* ここに上記処理をいれます */
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
		else if ((FaxTelResult == TMOUT_RESP) || (FaxTelResult == CL1_IGNORE_CNG)) {
#else
		else if (FaxTelResult == TMOUT_RESP) {
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
			if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {		/**	標準ラインにて受信時	*/
				SYS_RingCounter = 0;
			}
			else {
				SYS_RingCounterExt = 0;
			}
#else
			SYS_RingCounter = 0;
#endif
			FaxTelAutoSWAfterTransaction();
		}
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
		else if (FaxTelResult == CL1_DETECT_CNG) {
 #if (PRO_RS_INTERNAL == ENABLE)	/* SH7043内蔵のシリアル有効 */
			/*
			** FAX/TEL, TEL/FAX待機の時に以下のタスクがdel_tskされない
			** ported from \src\nagano\src\fcm_fcom.c by H.Hirao 1999/12/13
			*/
			if (tskno_MDM_ModemRecoverTask != 0xffff) {	/* モデム救済タスク 99/07/20 */
				del_tsk(&tskno_MDM_ModemRecoverTask);
			}
 #endif
			MsgFromFaxComToMain.Item = FROM_FAXCOM;
			MsgFromFaxComToMain.Message = MSG_CL1_CNG_DETECT;
			SYS_RingCounter = 0;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
			rcv_msg(mbxno.FCM_Task, &FcomMsg);
			exi_tsk();
		}
#endif
		else{
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
			if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {		/**	標準ラインにて受信時	*/
				SYS_RingCounter = 0;
			}
			else {
				SYS_RingCounterExt = 0;
			}
#else
			SYS_RingCounter = 0;
#endif
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/12/29 */
			AnalogSwitchRXA_Set(); /* モデムアナログ端子の入力をトーン検出用から通常に切替 */
#endif /* (PRO_MODEM == R288F) */

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/03  By T.Yamaguchi */
 /* #if defined(POPLAR_F) */
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Mod. by J.Kishida 2002/09/09 */
			if (FaxTelResult == RECEIVE) {
				if (FCM_DetectCIbyVoiceAnswer == 0) {
					receive_dcs_flag = 1;
				}
			}
 #else
			if(FaxTelResult == RECEIVE){
				receive_dcs_flag = 1;
			}
 #endif
#endif

#if defined(DEU)
			FaxTelOffHookFlag = 1;
#endif
		}
	}
	else{
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
		if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {		/**	標準ラインにて受信時	*/
			SYS_RingCounter = 0;
		}
		else {
			SYS_RingCounterExt = 0;
		}
#else
		SYS_RingCounter = 0;
#endif

		if ((ForwardReceiveFlag == 0) &&
			(FaxNetReceiveFlag == 0) &&
			(MuratecRxSpeedHandshakeEnable() == 1)) {	/** 転送受信でない && Ｆネット着信でない && 短縮ハンド可能である */
			/*----------------------*/
			/*	FAX Mode / SDCS Rx	*/
			/*----------------------*/
#if (PRO_SPEED_EX == ENABLE)
			/* 着信から着信トーン送出迄の時間を可変にする	95.11.07 By T.Y*/
			if ((SpeedHandshakeRomCheck() == TRUE) &&
				(CHK_UNI_SpeedHandshakeEx() != 0)) {		/* 新短縮ハンドシェーク　着信トーンを出す */
				ArrivalSignalToneTransmitFlag = 1;
				FaxTimer(CHK_UNI_SPDToneWaitTime());	/* 着信から着信トーン送出迄のウェイト*/
				ArrivalSignalToneTransmit();			/* 着信後トーン送出	 1995.10.20 By.T.Y*/
			}
#endif
			FaxRxSpeedHandshake();						/** 短縮ハンドシェーク受信 */
#if (PRO_SPEED_EX == ENABLE)
			ArrivalSignalToneTransmitFlag = 0;
#endif
			if(RxSpeedHandshakeFlag == 1){
				FaxComStartTime = SYB_CurrentTime;

				/*
				** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
				** By S.Kawasaki 1996/09/02
				*/
				SYS_FCM_StartTime = SYS_1SecGeneralTimer;

				/*-----------------------*/
				/** ジャーナル通番セーブ */
				/*-----------------------*//* 1994/09/30 */
				JournalTxTotalCount				= SYB_TxTotalCount;			/* 通信開始時間と終了時間で日付が変わった場合は、 */
				JournalRxTotalCount				= SYB_RxTotalCount;			/* 通信開始時の日付に合わせるためにセーブしておく */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
				JournalTxTotalCountExt			= SYB_TxTotalCountExt;
				JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
				PAT_JournalWorkFile.Number = JournalRxTotalCount;
				PAT_JournalWorkFile.StartTime = FaxComStartTime;

				PAT_JournalDataToImage(NUMBER);
				PAT_JournalDataToImage(START);
#endif

				FaxComRxPerformingFlag = 1;
#if (PRO_TX_SPEED == V34 ) /* Added by H.Kubo for V8/V34 1997/07/24 */
				V8ProcedureRequestFlag = 0;		/* 短縮ﾊﾝﾄﾞｼｪｰｸSDCSを受信すれば１発目はV8は行わない */
#endif /* (PRO_TX_SPEED == V34 ) */
			}
		}
		else{
			/*----------------------------------------------------------------------*/
			/*	TAD/FAX,転送 Mode  CALLED - CED Wait [FTZ TR2 Vol.2,3.2.6.2.1.1.7]	*/
			/*----------------------------------------------------------------------*/
			timer = ( UWORD )2000;
			FaxTimer( timer );
		}
	}

	if (( FaxComPerformingFlag == 1 )

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/03  By T.Yamaguchi */
	&&	(receive_dcs_flag == 0)
#endif

	&&	( RxSpeedHandshakeFlag != 1 )) {
		FaxComStartTime = SYB_CurrentTime;

		/*
		** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
		** By S.Kawasaki 1996/09/02
		*/
		SYS_FCM_StartTime = SYS_1SecGeneralTimer;

		/*-----------------------*/
		/** ジャーナル通番セーブ */
		/*-----------------------*//* 1994/09/30 */
		JournalTxTotalCount				= SYB_TxTotalCount;			/* 通信開始時間と終了時間で日付が変わった場合は、 */
		JournalRxTotalCount				= SYB_RxTotalCount;			/* 通信開始時の日付に合わせるためにセーブしておく */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
		JournalTxTotalCountExt			= SYB_TxTotalCountExt;
		JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
		PAT_JournalWorkFile.Number = JournalRxTotalCount;
		PAT_JournalWorkFile.StartTime = FaxComStartTime;

		PAT_JournalDataToImage(NUMBER);
		PAT_JournalDataToImage(START);
#endif

/*==== V34 ====*/
#if (PRO_TX_SPEED == V34 ) /* Added by H.Kubo for V8/V34 1997/07/24 */
 #if (PRO_CL1_TELFAX_LAN == ENABLE)	/* added by H.Hirao 1999/03/09 */
		if( ( ForwardReceiveFlag == 0 )
		 || ((ForwardReceiveFlag == 1) && (CHK_UNI_OnhookTransferCED_Tx() != 0))	/* 転送受信時のＣＥＤ送出 */
		 || ( AttemptRxModeSwitch == SYS_ANS_FAX_READY) ){
			switch ( CL1_CheckReceiveByFaxOrPC() ) {
			case PC_RECEIVE_OK:
  #if (PRO_RS_INTERNAL == ENABLE)	/* SH7043内蔵のシリアル有効 */
				CMN_DisableInterrupt();
				CL1_DualRestrictionStatus |= CL1_CLASS1_IN_USE;	/* クラス１受信中セット */
				SYS_CalledRequestForDocStore = 0;	/* 着信要求フラグリセット */
				CMN_EnableInterrupt();
				/*
				** FAX/TEL, TEL/FAX待機の時に以下のタスクがdel_tskされない
				** ported from \src\nagano\src\fcm_fcom.c by H.Hirao 1999/12/13
				*/
 				if (tskno_MDM_ModemRecoverTask != 0xffff) {	/* モデム救済タスク 99/07/20 */
					del_tsk(&tskno_MDM_ModemRecoverTask);
				}
 #endif
				MsgFromFaxComToMain.Item = FROM_FAXCOM;
				MsgFromFaxComToMain.Message = MSG_CL1_CNG_DETECT;
				SYS_RingCounter = 0;
				snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
				rcv_msg(mbxno.FCM_Task, &FcomMsg);		/* メインよりメッセージ受信 */
				exi_tsk();
				break;
  #if (PRO_RS_INTERNAL == ENABLE)	/* SH7043内蔵のシリアル有効 */
			case NO_RECEIVING_SCANNER_IN_USE:
			case NO_RECEIVING_PRINTER_IN_USE:
  #endif
			case NO_RECEIVING:
				/* SYS_ANS_FAX_READY 設定時は上位からコールされない筈 */
  #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_RS_INTERNAL == ENABLE) /* by H.Hirao 1999/05/12 */
				CL1_DualRestrictionStatus &= ~CL1_CLASS1_IN_USE;	/* クラス１受信中リセット */
  #endif
				break;
			default:	/* (FAX_RECEIVE_ENABLE,FAX_RECEIVE_ONLY) ＦＡＸ受信処理に移行する */
  #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_RS_INTERNAL == ENABLE) /* by H.Hirao 1999/05/12 */
				CL1_DualRestrictionStatus &= ~CL1_CLASS1_IN_USE;	/* クラス１受信中リセット */
  #endif
				break;
			}
		}
 #endif
		do {
			if (FCM_CheckV8ProcedureRequest()) {	/** Ｖ８実行可能 */
				if (loop == 0) {
					StartUpData.Item = V34_STANDARD;
					StartUpData.Option.TransmitCI = 0;
				}
				else {
					StartUpData.Item = V34_MANUAL;
					StartUpData.Option.TransmitCI = 0;
					counter++;
					if (counter > 5) {
						/* SYS_DataSignalingRate &= 0xFFFE; */
						CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT); /* Changed by H.Kubo 1997/07/25 */
					}
				}
				StartUpData.Direction = TX_COM_MODE;
#if (0)	/* 1998/1/29 by T.Soneoka */
//				if ((SYB_PollingDocumentStatus == 1) || (SYB_DB_PollingDocumentStatus == 1)) {
#endif
#if (0)	/*  By O.Kimoto 1998/04/24 */
** 	/* メモリスイッチＨ：２－１を０にしたときに、ポーリング原稿の権利を放さないと
** 	** いう不具合が発生したので
** 	** By O.Kimoto 1997/07/07
** 	*/
** 				if ((SYB_PollingDocumentStatus == 1)
#else

#if (0)
** 				/* PRO_MULTI_LINE == DISABLEの処理が入っていない By O.Kimoto 1998/06/24 */
** 			 	if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
#else

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
** 	#if (PRO_MULTI_LINE == ENABLE)
** 			 	if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
** 	#else
** 				if ((SYB_PollingDocumentStatus == 1)
** 	#endif
#else
			 	if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
#endif

#endif

#endif
				|| (SYB_DB_PollingDocumentStatus == 1)
				|| (SYB_SelectPollDocumentStatus == 1)
				|| (CheckPollingTxType() != 0) /* added by H.Kubo 1998/04/24 */
				|| (CHK_UNI_FcodeSecureDocPollTx())) {
					StartUpData.Allowed = (TX_COM_MODE | RX_COM_MODE);
				}
				else {
					StartUpData.Allowed = TX_COM_MODE;
				}
				ret_value = FCM_AnswerStartUpProcedure();	/** スタートアップ応答処理 */
				V8ProcedureRequestFlag = 0;
				switch (ret_value) {
					case V34_PROCEDURE:
						/* Ｖ３４はＥＣＭ必須？ */
						TxECM_Ability = ECM_ON;					/** ＥＣＭ送信ＯＮ指定 */
						RxECM_Ability = ECM_ON;					/** ＥＣＭ受信ＯＮ指定 */
						AvailableTxCodingMethod		= SYS_MR_CODE;				/** 機器の送信可能な符号化方式 */
						AvailableRxCodingMethod		= SYS_MR_CODE;				/** 機器の受信可能な符号化方式 */
						if (CHK_UNI_StoredMethodMMR()) {
							AvailableTxCodingMethod		= SYS_MMR_CODE;				/** 機器の送信可能な符号化方式 */
							AvailableRxCodingMethod		= SYS_MMR_CODE;				/** 機器の受信可能な符号化方式 */
						}
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */
  #if (PRO_SCN_CODEC_TYPE == IDP301)	/* SAKAKIではJBIGスキャナ送信なし 1998/09/30 H.Yoshikawa */
						SetAvailableCodingMethodEcmOn();	/* 1998/10/27 H.Yoshikawa */
#if (0)	/* 1998/10/27 */
//						if (CHK_UNI_JBIG_RX_Enable()) {
//							AvailableRxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
//						}
#endif
  #else
  	#if defined(POPLAR_F)
						SetAvailableCodingMethodEcmOn();
  	#else
						if (CHK_UNI_JBIG_TX_Enable()) {
							AvailableTxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
						}
						if (CHK_UNI_JBIG_RX_Enable()) {
							AvailableRxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
						}
	#endif
  #endif
#endif
#if (0)
**						AvailableTxCodingMethod = FCM_GetMaxTxCodeForECM();	/** 機器の送信可能な符号化方式 */
**						AvailableRxCodingMethod = FCM_GetMaxRxCodeForECM();	/** 機器の受信可能な符号化方式 */
#endif
						SYS_V34ProcedureExecutingFlag = 1;
						break;
					case T30_PROCEDURE:
						SYS_V34ProcedureExecutingFlag = 0;
						FCM_CommunicationV8toT30();
						break;
					default:
						FaxComPerformingFlag = 0;
						break;
				}
			}
			else {
				/*----------*/
				/*	CED Tx	*/
				/*----------*/
				if( ( ForwardReceiveFlag == 0 )
				 || ((ForwardReceiveFlag == 1) && (CHK_UNI_OnhookTransferCED_Tx() != 0))	/* 転送受信時のＣＥＤ送出 */
				 || ( AttemptRxModeSwitch == SYS_ANS_FAX_READY) ){
					FaxTransmitCED();

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/07/24 */
					MDM_ConfigReset();				/** モデム・リセット */
#endif /* (PRO_MODEM == ORANGE3) */
				}
			}
			if (FaxComPerformingFlag == 1) {
				if (SYS_V34ProcedureExecuting() == 0) {
		/*----------------------------------------------------*/
		/*	CED - NSF Wait 75±20ms[CCITT/FTZ18TR53 Fig11-1]  */
		/*----------------------------------------------------*/
					timer = CHK_WaitAfterDIS();		/** CED送出後NSF送出までの時間75m秒/1000m秒の獲得 */
/* #if defined(DEU) 1997/06/02  By T.Yamaguchi */	/* '97/02/21 M.HARADA */
					TimerCutStatus = 1;
/* #endif */
					FaxTimer( timer );

				}
				else {
					MDM_InitialConfig2(2);
				}

				/*------------*/
				/*	Phase B1  */
				/*------------*/
				FaxRxPhaseB1();					/** 受信フェーズＢ１ */
				loop = 1;
			}
		} while (FCM_CheckV8ProcedureRequest());

#else /* (PRO_TX_SPEED == V34 ) /* /* Added by H.Kubo for V8/V34 1997/07/24 */
/*==== V33 or lower ====*/
		/*----------*/
		/*	CED Tx	*/
		/*----------*/
		if( ( ForwardReceiveFlag == 0 )
		 || ((ForwardReceiveFlag == 1) && (CHK_UNI_OnhookTransferCED_Tx() != 0))	/* 転送受信時のＣＥＤ送出 */
		 || ( AttemptRxModeSwitch == SYS_ANS_FAX_READY) ){
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
  #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/7/27 K.Kawata */
	if (ForwardReceiveFlag == 1) {
		if (CHK_UNI_Class1_EXT_Function()) {
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM;	/* CLASS1動作中セット */
			CL1_ExtFunctionEnableFlag = 1;
			FaxTransmitCED();
		}
		else {
			switch ( CL1_CheckReceiveByFaxOrPC() ) {
			case PC_RECEIVE_OK:
				MsgFromFaxComToMain.Item = FROM_FAXCOM;
				MsgFromFaxComToMain.Message = MSG_CL1_CNG_DETECT;
				SYS_RingCounter = 0;
				snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
				rcv_msg(mbxno.FCM_Task, &FcomMsg);		/* メインよりメッセージ受信 */
				exi_tsk();
				break;
			case NO_RECEIVING:
				/* SYS_ANS_FAX_READY 設定時は上位からコールされない筈 */
				break;
			default:	/* (FAX_RECEIVE_ENABLE,FAX_RECEIVE_ONLY) ＦＡＸ受信処理に移行する */
				break;
			}
			FaxTransmitCED();
		}
	}
	else {
		switch ( CL1_CheckReceiveByFaxOrPC() ) {
		case PC_RECEIVE_OK:
			MsgFromFaxComToMain.Item = FROM_FAXCOM;
			MsgFromFaxComToMain.Message = MSG_CL1_CNG_DETECT;
			SYS_RingCounter = 0;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
			rcv_msg(mbxno.FCM_Task, &FcomMsg);		/* メインよりメッセージ受信 */
			exi_tsk();
			break;
		case NO_RECEIVING:
			/* SYS_ANS_FAX_READY 設定時は上位からコールされない筈 */
			break;
		default:	/* (FAX_RECEIVE_ENABLE,FAX_RECEIVE_ONLY) ＦＡＸ受信処理に移行する */
			break;
		}
		FaxTransmitCED();
	}
  #else
			switch ( CL1_CheckReceiveByFaxOrPC() ) {
			case PC_RECEIVE_OK:
				MsgFromFaxComToMain.Item = FROM_FAXCOM;
				MsgFromFaxComToMain.Message = MSG_CL1_CNG_DETECT;
				SYS_RingCounter = 0;
				snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
				rcv_msg(mbxno.FCM_Task, &FcomMsg);		/* メインよりメッセージ受信 */
				exi_tsk();
				break;
			case NO_RECEIVING:
				/* SYS_ANS_FAX_READY 設定時は上位からコールされない筈 */
				break;
			default:	/* (FAX_RECEIVE_ENABLE,FAX_RECEIVE_ONLY) ＦＡＸ受信処理に移行する */
				break;
			}
			FaxTransmitCED();
  #endif	/* PRO_CLASS1_EXT_FUNC */
 #else
			FaxTransmitCED();
 #endif

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/07/24 */
			MDM_ConfigReset();				/** モデム・リセット */
#endif /* (PRO_MODEM == ORANGE3) */
		}
		/*----------------------------------------------------*/
		/*	CED - NSF Wait 75±20ms[CCITT/FTZ18TR53 Fig11-1]  */
		/*----------------------------------------------------*/
		timer = CHK_WaitAfterDIS();		/** CED送出後NSF送出までの時間75m秒/1000m秒の獲得 */
/* #if defined(DEU) 1997/06/02  By T.Yamaguchi */	/* '97/02/21 M.HARADA */
		TimerCutStatus = 1;
/* #endif */
		FaxTimer( timer );

		/*------------*/
		/*	Phase B1  */
		/*------------*/
		FaxRxPhaseB1();					/** 受信フェーズＢ１ */
#endif /* (PRO_TX_SPEED == V34 ) */
/*==== end of V33 or lower ====*/
	}

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/03  By T.Yamaguchi */
	if	(receive_dcs_flag == 1) {
		FaxComStartTime = SYB_CurrentTime;
		SYS_FCM_StartTime = SYS_1SecGeneralTimer;

		/*-----------------------*/
		/** ジャーナル通番セーブ */
		/*-----------------------*//* 1994/09/30 */
		JournalTxTotalCount				= SYB_TxTotalCount;			/* 通信開始時間と終了時間で日付が変わった場合は、 */
		JournalRxTotalCount				= SYB_RxTotalCount;			/* 通信開始時の日付に合わせるためにセーブしておく */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
		JournalTxTotalCountExt			= SYB_TxTotalCountExt;
		JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif
	}
#endif



	while ((FaxComPerformingFlag == 1)
	&& (FaxComRxPerformingFlag == 1)) {
		switch (FinalRxMode) {
			case G2MODE	  :
							/*-------------------------*/
							/*			G2	Rx		   */
							/*-------------------------*/
							break;
			case G3MODE	  :
							/*-------------------------*/
							/*			G3	Rx		   */
							/*-------------------------*/
							rcr_check_flag = 1;
							FaxReceive();			/** Ｇ３モードで受信 */
							break;
#if (PRO_DIAG == ENABLE) /* by H.Kubo 1998/04/02 */
			case DIAGMODE :
							/*-------------------------*/
							/*	Remote Diagnostics Rx  */
							/*-------------------------*/
							RemoteDiagnostic();		/** リモート診断 */
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)	/* 1998/03/31  By T.Yamaguchi */
							if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
								RxEOM_ReceiveFlag = 1;		/** Ｇ３モードで受信 */
							}
#endif
							break;
#endif /* (PRO_DIAG == ENABLE) */
			default		  :
							break;
		}

		if ((FaxComPerformingFlag == 1)
		&& (RxEOM_ReceiveFlag == 1)){
			FaxRxPhaseB1();
		}
	}

	SYS_CurrentExecutingCommand = 0x00;		/* NULL */
	PollingTxFirstPageFlag = 0;

	if ((FaxComPerformingFlag	== 1)
	&&	(FaxComTxPerformingFlag == 1)) {
		/*-----------------------*/
		/*	Polling Tx / RCR Tx	 */
		/*-----------------------*/
		PollingTxFirstPageFlag = 1;
		if( rcr_check_flag == 1 ){
			/*------------------------------------------------------------------*/
			/** 受領証送信用通信時間算出										*/
			/* (受領証に通信時間をのせるため受領証送信前までの通信時間を求める) */
			/*------------------------------------------------------------------*/
			FaxComPeriod = (UWORD)(SYB_CurrentTime - FaxComStartTime);

			/*
			** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
			** By S.Kawasaki 1996/09/02
			*/
			FaxComPeriod = (UWORD)(SYS_1SecGeneralTimer - SYS_FCM_StartTime);

			/* 他社機からターンアラウンドポーリング要求があった時
			** ポーリング原稿が蓄積されていたら、受領証を送出していた
			** 受領証要求のときのみ出す様に変更
			*/
			if (TxReceiptRequestFlag) {	/* 受領証要求有りなら Oct.15.1997  By T.Yamaguchi */
				TxRCR_Flag = 1;
			}
#if ( PRO_TX_SPEED == V34 ) /* Added by H.Kubo for V8/V34 1997/07/24 */
			if (SYS_V34ProcedureExecuting() == 1) {

				/*---------------------------------------*/
				/* コントロールチャネル ｔｕｒｎ－ｏｆｆ */
				/*---------------------------------------*/
				/*if (V34_ControlChanelTurnOff()) {*/
				if (FCM_ControlChTurnaroundTurnOff()) {
					/*-------------------------*/
					/** スタートアップ応答処理 */
					/*-------------------------*/
					StartUpData.Item = V34_TURNAROUND;
					StartUpData.Direction = RX_COM_MODE;
					StartUpData.Allowed = RX_COM_MODE;
					StartUpData.Option.TransmitCI = 0;

					ret_value = FCM_AnswerStartUpProcedure();
					switch (ret_value) {
						case V34_PROCEDURE:
							break;
						case T30_PROCEDURE:
							FaxComPerformingFlag = 0;
							break;
						default:
							FaxComPerformingFlag = 0;
							break;
					}
				}
				else {
					FaxComPerformingFlag = 0;
					ReceiveError(0x15);
				}
			}
#endif /* (PRO_TX_SPEED == V34 ) */
		}
		else {
			FaxComTXorRX_Sign = TX_COM_MODE;

#if (PRO_PAT_JOURNAL == ENABLE)
			PAT_JournalWorkFile.Number = JournalTxTotalCount;
			PAT_JournalDataToImage(NUMBER);
#endif

#if (PRO_MEM_RX_REJECT == ENABLE) || (PRO_PRINTER_RX == ENABLE) /* changed by H.Hirao 1998/12/25 */
/* #if(PRO_MEM_RX_REJECT == ENABLE) @* MOMIJI のみ 94/11/7 Y.Suzuki */
			/* MOMIJI プリンタ開放のため 94/11/7 Y.Suzuki */
			MsgFromFaxComToMain.Item = FROM_FAXCOM;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_TX_START;
			snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
			rcv_msg(mbxno.FCM_Task, &FcomMsg);		/* メインよりメッセージ受信 */
#endif

#if (PRO_FIP == ENABLE)	/* ﾎﾟｰﾘﾝｸﾞ Tx */
			SYS_FIP_Status &= ~FIP_DURING_RX;
			SYS_FaxComFIP_RxActiveFlag = 0;
			SYS_FaxComType = SYS_AUTO_CALLED;
#endif

#if defined (KEISATSU) /* 警察FAX 05/12/01 石橋正和 */
			/* ポーリングはノンスクランブル */
			FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;
			FCM_ExecutingS1Info.Available = FALSE;
			FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
			
			FCM_S1_Scramble = FALSE;
			FCM_S1_Senyo = FALSE;
#endif
		}
		FaxTransmit();					/** Ｇ３モードで送信 */
		TxRCR_Flag = 0;
	}
	TxReceiptRequestFlag = 0;
}


/*************************************************************************
	module		:[ＦＩＰ自動ダイアル通信]
	function	:[]
	commom		:[
		FaxComPerformingFlag		: 通信中フラグ
		AD_Result_Flag				: オートダイアラー結果フラグ
		AD_Result					: オートダイアラー戻り値
		FipDialNumber				: ダイアル番号
		FaxComStartTime				: 通信開始時刻
		FaxComResult				: 通信結果
		SYS_FaxComType				: 通信タイプ
		FaxComTXorRX_Sign			: 送信受信判別
		PollingTxFirstPageFlag		: ポーリング送信先頭ページフラグ
		FaxComRxPerformingFlag		: 受信要求フラグ
		RxEOM_ReceiveFlag			: ＥＯＭ受信フラグ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[1994/01/24]
	author		:[村田]
*************************************************************************/
void	FipFaxCom(void)
{
#if (PRO_FIP == ENABLE)

	UBYTE	   rcr_check_flag;

	rcr_check_flag		 = 0;
	FaxComPerformingFlag = 0;

	/*---------------------------------------------------------------------
	** SAKAKIスキャナECM送信時には、MMRで送信するので、
	** SYS_FaxComTypeの値が決まった後に、再度符号化方式を決める関数を再度Callします
	** 1998/10/27 H.Yoshikawa
	*/
  #if (PRO_SCN_CODEC_TYPE == IDP301)	/* SAKAKIではJBIGスキャナ送信なし 1998/10/27 H.Yoshikawa */
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
  #endif
  #if defined(POPLAR_F)
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
  #endif

	FaxcomRelayControl();						/** リレ～セット */

	/* ｵｰﾄ･ﾀﾞｲｱﾗｰへ渡す引き数はFIP用のﾊﾞｯﾌｧ･ﾎﾟｲﾝﾀｰをｾｯﾄしなければならない。 */
	/*---------------*/
	/*	Auto Dialer	 */
	/*---------------*/

	switch (AD_Result = AutoDial(SYS_FIP_DialNumber)) {	/* ﾀﾞｲｱﾙﾃﾞｰﾀﾊﾞｯﾌｧｰのﾎﾟｲﾝﾀｰ */

		case AD_OK:
		case AD_OK_DSE:
		case AD_OK_CED:
		case AD_OK_DIS:		/* 96/04/26 by T.YAMAGUCHI */
						FaxComStartTime = SYB_CurrentTime;

						/*
						** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
						** By S.Kawasaki 1996/09/02
						*/
						SYS_FCM_StartTime = SYS_1SecGeneralTimer;

						/*-----------------------*/
						/** ジャーナル通番セーブ */
						/*-----------------------*//* 1994/09/30 */
						JournalTxTotalCount				= SYB_TxTotalCount;			/* 通信開始時間と終了時間で日付が変わった場合は、 */
						JournalRxTotalCount				= SYB_RxTotalCount;			/* 通信開始時の日付に合わせるためにセーブしておく */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
						JournalTxTotalCountExt			= SYB_TxTotalCountExt;
						JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

	#if (PRO_PAT_JOURNAL == ENABLE)
						if (SYS_FaxComType == SYS_FIP_SEND) {
							PAT_JournalWorkFile.Number = JournalTxTotalCount;
							PAT_JournalWorkFile.Kind = SYS_FIP_TRANSMIT;
						}
						else {	/** ＦＩＰポーリング */
							PAT_JournalWorkFile.Number = JournalRxTotalCount;
							PAT_JournalWorkFile.Kind = SYS_FIP_POLLING;
						}
						PAT_JournalWorkFile.StartTime = FaxComStartTime;

						PAT_JournalDataToImage(NUMBER);
						PAT_JournalDataToImage(START);
						PAT_JournalDataToImage(NOTE);
	#endif

						FaxComPerformingFlag = 1;		/* 通信中 */
						break;
		case AD_LOCAL_BUSY:
						DialError(0x01);
						break;
		case AD_REMOTE_BUSY:
						DialError(0x02);
						break;
		case AD_STOPPED:
						DialError(0x03);
						break;
		case AD_DIAL_EMPTY:
						DialError(0x06);
						break;
		case AD_TIME_OVER:
						DialError(0x07);
						break;
		case AD_NO_DIAL_TONE:
						DialError(0x08);
						break;
		case AD_NO_CURRENT_LOOP:
						DialError(0x09);
						break;
		default:
						FaxComResult |= DIALERROR;
						break;
	}

	if ((FaxComPerformingFlag == 1) && (SYS_FaxComType == SYS_FIP_SEND)) {
		FaxComTXorRX_Sign		= TX_COM_MODE;
		PollingTxFirstPageFlag	= 0;
		FaxTransmit();
		rcr_check_flag			= 1;
	}

	if ((FaxComPerformingFlag == 1) && (SYS_FaxComType == SYS_FIP_POLL)) {
		if( rcr_check_flag != 1 ){
			FaxComTXorRX_Sign = RX_COM_MODE;
		}
		FaxPollingRxPhaseB1();
		while ((FaxComPerformingFlag == 1) && (FaxComRxPerformingFlag == 1)) {
			FaxReceive();
			if ((FaxComPerformingFlag == 1) && (RxEOM_ReceiveFlag == 1)) {
				FaxRxPhaseB1();
			}
		}
	}
#endif
}


/*************************************************************************
	module		:[手動ポーリング受信処理]
	function	:[
		1. ＦＸ仕様にのみ有効な機能
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1994/07/07]
	author		:[村田]
*************************************************************************/
void	ManualPollingReceive(void)
{
	/*---------------------------------------------------------------------
	** SAKAKIスキャナECM送信時には、MMRで送信するので、
	** SYS_FaxComTypeの値が決まった後に、再度符号化方式を決める関数を再度Callします
	** 1998/10/27 H.Yoshikawa
	*/
#if (PRO_SCN_CODEC_TYPE == IDP301)	/* SAKAKIではJBIGスキャナ送信なし 1998/10/27 H.Yoshikawa */
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
#endif
#if defined(POPLAR_F)
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		SetAvailableCodingMethodEcmOn();
	}
#endif

	FaxcomRelayControl();						/** リレ～セット */

	TxReceiptRequestFlag = 0;					/** 受領証送信フラグ クリア */
	FaxComStartTime	  = SYB_CurrentTime;		/** 交信開始時刻（秒） */

	/*
	** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
	** By S.Kawasaki 1996/09/02
	*/
	SYS_FCM_StartTime = SYS_1SecGeneralTimer;

	/*-----------------------*/
	/** ジャーナル通番セーブ */
	/*-----------------------*//* 1994/09/30 */
	JournalTxTotalCount				= SYB_TxTotalCount;			/* 通信開始時間と終了時間で日付が変わった場合は、 */
	JournalRxTotalCount				= SYB_RxTotalCount;			/* 通信開始時の日付に合わせるためにセーブしておく */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
	JournalTxTotalCountExt			= SYB_TxTotalCountExt;
	JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_JournalWorkFile.Number = JournalRxTotalCount;
	PAT_JournalWorkFile.StartTime = FaxComStartTime;
	PAT_JournalWorkFile.Kind = SYS_POLLING_RX;

	PAT_JournalDataToImage(NUMBER);
	PAT_JournalDataToImage(START);
	PAT_JournalDataToImage(NOTE);
#endif

	FaxComTXorRX_Sign = RX_COM_MODE;			/** 受信コマンドセット */
	
#if defined(STOCKHM2) /* DVT : add by SMuratec C.P 2004/09/08 */
	SYS_ConfirmTxRxFlag = 0;
#endif

	/*------------------------------------------------*/
	/* ポーリング受信原稿はリモートＦＡＸ原稿ではない */
	/*------------------------------------------------*/
	RemoteFaxON_Flag	= 0;
	RemoteFaxPRN_Flag	= 0;
	RemoteFaxDEL_Flag	= 0;

	/*---------------*/
	/*	Rx Phase B1	 */
	/*---------------*/
	FaxPollingRxPhaseB1();						/** ポーリング受信フェーズＢ１ */
	while ((FaxComPerformingFlag == 1) && (FaxComRxPerformingFlag == 1)) {		/** 通信中で受信要求 */
		/*---------------*/
		/*	Rx Phase B2	 */
		/*---------------*/
		FaxReceive();							/** Ｇ３モードで受信 */
		if ((FaxComPerformingFlag == 1) && (RxEOM_ReceiveFlag == 1)) {		/** 通信中でＥＯＭ受信 */
			/*---------------*/
			/*	Rx Phase B1	 */
			/*---------------*/
			FaxRxPhaseB1();				/** 受信フェーズＢ１ */
		}
	}
}

