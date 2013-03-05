/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_LAST.C												 */
/*	モジュール	 :															 */
/*				 : FaxComAfterCheck()										 */
/*				 : SpeedHandshakeAttributeChange()							 */
/*				 : SpeedHandshakeAttributeDel()								 */
/*	作成者		 : 山口														 */
/*	日	付		 :															 */
/*	概	要		 : ＦＡＸ通信後処理モジュール								 */
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
#include "\src\atlanta\define\stng_pro.h"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\atlanta\define\mem_pro.h"

#if (PRO_DIRECTORY == ENABLE)	/* For Remote Diag 1995.04.21 T.Nose */
 #if (PRO_PANEL == ANK)
#include "\src\atlanta\opr\ank\define\opr_pro.h"	/* For Remote Diag 1995.04.21 1995.10.18 T.Y */
 #endif
 #if (PRO_PANEL == KANJI)
#include "\src\atlanta\opr\kanji\define\opr_pro.h"	/* For Remote Diag 1995.04.21 1995.10.18 T.Y */
 #endif
#endif

#include "\src\atlanta\define\syscomf.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\memsw\define\mem_sw_b.h" /*1996/04/17 Eguchi*/
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\sys_remo.h"
#include "\src\atlanta\define\std.h"			/* 96/06/06 */
#include "\src\atlanta\define\sys_opt.h"	/* 97/06/13 */

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\atd_tbl.h"			/* 96/06/06 */

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/05 */
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/05 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
 #endif
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/05 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_TX_SPEED == V34) */
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif

#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\mlt_pro.h"

#if 0  /* defined(FRA) */
void			ClearSpeedRecord(UWORD SpeedNumber );	/*短縮番号*/
void			ClearOnetouchRecord(UBYTE OnetouchSw );	/*ワンタッチキー番号*/
#endif
#include  "\src\atlanta\define\mon_pro.h"	/* 1997/04/26  By T.Yamaguchi */
#if (PRO_FBS == ENABLE) /* 1997/06/09  By T.Yamaguchi */
	#include "\src\atlanta\define\sysscan.h"
#endif

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
#include  "\src\atlanta\define\sys_stat.h"
#include  "\src\atlanta\define\mntsw_e.h"	/*	デバッグ用 */
void RestartSystem(void);
void FLA_ClearSumROMData(void);
void FLA_ClearModelROMData(void);
#endif
/* 代行受信原稿をポーリング原稿にするSWを落とす。Naganoより移植 O.Oshima 2005/02/08 */
#include  "\src\atlanta\define\unisw_h.h"


/************************************************************************
	module		:[通信後処理]
	function	:[
		1. 送信及び受信項目を解析し後処理を行う
		2. 通信結果によりリダイアル及びチェックメッセージ印字の設定を行う
		3. 通信結果によりジャーナルにデータを登録する
	]
	return		:[]
	common		:[
		FaxComTXorRX_Sign				: 送信受信判別フラグ
		SYB_MailBox						: 親展受信メイルボックス
		SYB_CommandFile					: コマンドファイル
		RelayedCommandNo				: 中継送信コマンドファイル番号
		SYS_RxMemoryFileNo				: メモリ受信ファイル番号
		RemoteFaxON_Flag				: リーモートＦＡＸフラグ
		SYS_RemoteFaxTAD_DataRecFlag	: データ有無フラグ
		SYS_RemoteFaxReceiveCount		: 受信件数
		SYS_TadPocketBellFlag			: ボケベルフラグ
		FaxComResult					: 通信結果
		TxMemoryFileItem				: 送信項目
		SYB_PollingDocumentStatus		: ポーリング原稿ステータス
		SYS_FaxComType					: 通信タイプ
		AD_Result						: ダイアラー結果
		SYS_ManualFaxCommErrRequest		: 手動通信エラーフラグ
		BackUpFaxComResult				: 通信結果バックアップ
		*SYS_CurrentExecutingCommand	: 発信スケジューラーポインター
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/03/04]
	author		:[村田]
************************************************************************/
void		FaxComAfterCheck(void)
{
	UBYTE		i;
	
#if (PRO_TX_SPEED == V34)
	UBYTE		reset_journal;		/* モデム不具合はジャーナルにのせない 1996/10/29 */

	reset_journal = 0;		/* モデム不具合はジャーナルにのせない 1996/10/29 */
#endif

#if defined(STOCKHM2) /* QAT : 通信FLAGの初期化 Add by SMuratec C.P 2004/11/01 */
	SYS_ConfirmTxRxFlag = 0;
#endif

#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 夏 2005/11/01 */
	if ( (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)
		&& (FaxComTXorRX_Flag == TX_COM_MODE) && (SYS_FaxComType == SYS_COMMAND_EXECUTE)) {
		if ((TxPageFinishStatus != TX_PAGE_END_RCR)	
 #if 0 /* 警察FAX DVT Deleted by SMuratec 夏 2005/11/21 */
			&& (TxPageFinishStatus != TX_STOPPED)
 #endif
			&& (TxPageFinishStatus != TX_END)) {
			TransmitError( 0x91, 1 ); /* T.9.1 */
		}
	}
#endif /* defined (KEISATSU) */

	/* 中継指示を受けSYS_RxTotalPageが0であった時は、SYB_CommandFile[].StatusはCMD_EMPTY */
	if (FaxComTXorRX_Sign == RX_COM_MODE) {		/** 受信 */
		switch (SYS_RxMemoryFileItem) {					/** メモリ受信項目判定 */
			case SYS_MEM_SECURE_RX_FILE:				/** 親展受信 **/
				if (SYS_RxTotalPage >= 1) {				/** 親展受信処理（１枚以上受信） */
					/*----------------------------------------------------------------*/
					/** 親展受信後の親展受信ﾒｯｾｰｼﾞ印字用ﾃﾞｰﾀｾｯﾄ						  */
					/** 親展受信時は１枚でも受信していれば２枚目がｴﾗｰでもﾒｯｾｰｼﾞを印字 */
					/*----------------------------------------------------------------*/
					/* SYB_MailBox[SYS_RxMemoryFileNo].Status		 = SYS_MAILBOX_RECEIVE;		順番変更 1994/11/09 ** 親展受信原稿有り */
					SYB_MailBox[SYS_RxMemoryFileNo].MessageStatus = SYS_MAILBOX_RCV_MSG;		/** 親展受信通知メッセージ */
					SYB_MailBox[SYS_RxMemoryFileNo].ErasedTime	  = ( SYB_CurrentTime ) +
															( (UDWORD)CHK_SecureMailHoldTime() * 24L * 60L * 60L );	/** 消去時間 現在時間（秒）＋ 保持期間（日）× ２４時間×６０分×６０秒 */
					SYB_MailBox[SYS_RxMemoryFileNo].Status		  = SYS_MAILBOX_RECEIVE;		/** 親展受信原稿有り */
				}
				else {
					/*------------------------------------------------------------------*/
					/* 親展受信失敗時のクリア											*/
					/* 親展受信で１枚も受信していなくても過去に親展受信の原稿がある時は */
					/* ステータスを有りにセットする										*/
					/*------------------------------------------------------------------*/
					if(SYS_RxMemoryFileNo != 0xFF) {
						/* ﾎﾞｯｸｽなし、ﾊﾟｽｺｰﾄﾞｴﾗｰ時は、以下の処理を行わない。95/03/31 Y.Suzuki */
						SYB_MailBox[SYS_RxMemoryFileNo].MessageStatus = SYS_MAILBOX_MSG_EMPTY;	/** 親展受信通知メッセージ出力しない */
						if (MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,SYS_RxMemoryFileNo, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX) {	/** 以前にも親展受信原稿がない */
							SYB_MailBox[SYS_RxMemoryFileNo].Status	  = SYS_MAILBOX_SET;		/** 親展受信原稿無し */
						}
						else {	/** 以前に親展受信をしている */
							SYB_MailBox[SYS_RxMemoryFileNo].Status	  = SYS_MAILBOX_RECEIVE;	/** 親展受信原稿有り */
						}
					}
					/* 順番変更 1994/11/11 SYB_MailBox[SYS_RxMemoryFileNo].MessageStatus = SYS_MAILBOX_MSG_EMPTY;	@** 親展受信通知メッセージ出力しない */
				}
				break;

			case SYS_MEM_TX_FILE:					/** 中継指示送信、Ｆコード中継配信、ワープ転送 */

				if (SYS_RxTotalPage >= 1) {			/** 中継指示を受けた場合の処理（１枚以上受信） */
					/* SYB_CommandFile[RelayedCommandNo].Status	  = SYS_CMD_WAITING;	順番変更（ＤＲＡＭバックアップのため 1994/10/25 *//** 予約確定 */
					SYB_CommandFile[RelayedCommandNo].ExecTime = SYB_CurrentTime;			/** 発信時刻（秒）*/
					SYB_CommandFile[RelayedCommandNo].Page	   = (UBYTE)SYS_RxTotalPage;	/** 送信ページ */
					SYB_CommandFile[RelayedCommandNo].Status   = SYS_CMD_WAITING;			/** 予約確定 */
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
					SYB_CommandStatus[RelayedCommandNo] = SYS_CMD_WAITING;
#endif
				}
				else {	/** 中継指示失敗時のｸﾘｱｰ */
					/* RelayedCommandNo がｾｯﾄされる前にｴﾗｰとなった場合以下の処理は行わない。95/03/31 Y.Suzuki */
					if(RelayedCommandNo != 0xFF) {
						SYB_CommandFile[RelayedCommandNo].Status   = SYS_CMD_EMPTY;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
						SYB_CommandStatus[RelayedCommandNo] = SYS_CMD_EMPTY;
#endif
					}
				}
				break;

#if (PRO_REMOTE_FAX == ENABLE) /* By T.Y Oct.18,1995 */
			case SYS_MEM_REMOTE_TX_FILE:			/** リモートＦＡＸ受信 */

				if (SYS_RxTotalPage >= 1) {	/** リモートＦＡＸで一枚以上受信 */
					SYS_RemoteFaxTAD_DataRecFlag |= REMOTE_FAX_DATA;	/** リモートＦＡＸ取り出し用原稿蓄積有無フラグセット */
					++SYS_RemoteFaxReceiveCount;						/** リモートＦＡＸ蓄積原稿数カウントアップ */
				}
				break;
#endif
#if (PRO_F_CODE == ENABLE)
			case SYS_MEM_SUB_SECURE_FILE:
			case SYS_MEM_SUB_BULLETIN_FILE:
				FCM_SetRxSubAddressBox((UWORD)SYS_RxMemoryFileItem, (UWORD)SYS_RxMemoryFileNo, (UWORD)SYS_RxTotalPage, (UWORD)SYS_RxMemoryFileBoxNumber);
				break;
#endif
#if (PRO_CIPHER == ENABLE)
			case SYS_MEM_CIPHER_RX_FILE:
				if (SYS_RxTotalPage >= 1) {		/** 暗号化受信処理（１枚以上受信） */
					/*----------------------------------------------------------------*/
					/** 暗号化受信後の暗号化受信ﾒｯｾｰｼﾞ印字用ﾃﾞｰﾀｾｯﾄ					  */
					/** 暗号化受信時は１枚でも受信していれば２枚目がｴﾗｰでもﾒｯｾｰｼﾞを印字 */
					/*----------------------------------------------------------------*/
					SYB_CipherBox[SYS_RxMemoryFileNo].MessageStatus = SYS_CIPHERBOX_RCV_MSG;	/** 暗号化受信通知メッセージ */
					SYB_CipherBox[SYS_RxMemoryFileNo].Status  = SYS_CIPHERBOX_RECEIVE;		/** 親展受信原稿有り */
				}
				else {
					/*------------------------------------------------------------------*/
					/* 暗号化受信失敗時のクリア											*/
					/*------------------------------------------------------------------*/
					if(SYS_RxMemoryFileNo < SYS_CIPHERBOX_MAX) {
						SYB_CipherBox[SYS_RxMemoryFileNo].Status  = SYS_CIPHERBOX_NO;	/** ステータスをクリア */
					}
				}
				break;
#endif
		}
#if (PRO_F_CODE == ENABLE)
		/* ターンアラウンドＦコードポーリングの時の処理追加 1998/05/28  By T.Yamaguchi */
		if ( (TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)
		  || (TxMemoryFileItem == SYS_MEM_SUB_SECURE_FILE) ) {

			FCM_SetTxSubAddressBox((UWORD)TxMemoryFileItem, (UWORD)TxMemoryFileBoxNumber, (UWORD)FaxComResult);
		}
#endif
	}

	else if (FaxComTXorRX_Sign == TX_COM_MODE) {					/** 送信 */
		if (((FaxComResult&0x0C00) == NO_ERROR)&&					/** NO ERROR && POLLING && FILE ERASE */
			(TxMemoryFileItem == SYS_MEM_POLLING_FILE)&&
			(CHK_DocumentEraseAfterPolling() != 0)) {				/** 正常交信でポーリング送信で原稿消去 */
			SYB_PollingDocumentStatus = 0;							/** ポーリング原稿蓄積状態管理データ エンプティ */

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == DISABLE)	/* Add By O.Kimoto 1996/11/11 */
** 			MEM_ClearDoc(SYS_MEM_POLLING_FILE, 0, MEM_IGNORE_BOX_NUMBER);					/** ポーリング原稿消去 */
** #else
** 			CMN_ErasePollingDoc(SYS_SEND_INTERNAL_LINE);
** #endif
#else
			CMN_ErasePollingDoc(SYS_SEND_INTERNAL_LINE);
#endif

		}

#if (PRO_REMOTE_FAX == ENABLE) /* By T.Y Oct.18,1995 */
		/*--------------------------------------*/
		/* リモートＦＡＸ送信でメモリオーバーの */
		/* チェックメッセージ送信でエラーの時は */
		/* 原稿及びフラグをクリアする			*/
		/*--------------------------------------*/
		else if ((((FaxComResult & 0x0C00) == NO_ERROR)		  &&
				(TxMemoryFileItem == SYS_MEM_REMOTE_TX_FILE)) ||

				(((FaxComResult & 0x0C00) != NO_ERROR)		  &&
				(TxMemoryFileItem == SYS_MEM_REMOTE_TX_FILE)  &&
				(SYS_RemoteFaxMemoryOverFlag == 1)			  &&
				(TxSmType == TX_REMOTE_FAX_MSG))) {

				SYS_RemoteFaxMemoryOverFlag = 0;					/** リモートＦＡＸメモリオーバーチェックメッセージ送信要求 */

				if (RemoteFaxDEL_Flag == 1) {
					SYS_RemoteFaxTAD_DataRecFlag &= ~REMOTE_FAX_DATA;	/** リモートＦＡＸ取り出し原稿クリア */
					SYS_RemoteFaxReceiveCount = 0;						/** リモートＦＡＸ蓄積原稿数クリア */
					MEM_ClearDoc(SYS_MEM_REMOTE_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER);			/** リモートＦＡＸ原稿消去 */
				}
		}
#endif
#if (PRO_F_CODE == ENABLE)
		else if ((TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)
		  || 	 (TxMemoryFileItem == SYS_MEM_SUB_SECURE_FILE)) {

			FCM_SetTxSubAddressBox((UWORD)TxMemoryFileItem, (UWORD)TxMemoryFileBoxNumber, (UWORD)FaxComResult);
		}
#endif
	}
	else if (FaxComTXorRX_Sign == DIAG_MODE) {						/** リモート診断 */
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)	/* 1998/03/31  By T.Yamaguchi */
		if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
			if((FaxComResult&0x0C00) == NO_ERROR) {
				/* 正常にＲＯＭデータを受信完了 */
				FlashRomWriteAfterCheck(0);
			}
			else {
				/* ＲＯＭデータ受信エラー */
				FlashRomWriteAfterCheck(1);
			}
		}
		else {
 #if (PRO_DIRECTORY == ENABLE)	/* For Remote Diag 1995.04.21 T.Nose */
			ResortTelephoneBookData();
 #endif
			SetJunkOwnDial();	/* ジャンクメール用ダイヤルバッファセット 1997/10/22  By T.Yamaguchi  */
		}
#else
 #if (PRO_DIRECTORY == ENABLE)	/* For Remote Diag 1995.04.21 T.Nose */
		ResortTelephoneBookData();
 #endif
		SetJunkOwnDial();	/* ジャンクメール用ダイヤルバッファセット 1997/10/22  By T.Yamaguchi  */
#endif
	}

	/*---------------------------------------------------*/
	/** ここからｼﾞｬｰﾅﾙのｾｯﾄを行います。					 */
	/** 課金されない通信の時には、ｼﾞｬｰﾅﾙには載せません。 */
	/*---------------------------------------------------*/

	/*--------------*/
	/* コマンド通信 */
	/*--------------*/
	if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {				/** コマンド通信 */

		/*----------------------*/
		/* 画質不良ページセット */
		/*----------------------*/
		for (i = 0; i < SYS_ERROR_PAGE; i++) {
			SYS_CurrentExecutingCommand->ErrorPage[i] = TxResponsedRTN_PageSign[i];		/** 画質不良ページ */
		}

		/*--------------------------------*/
		/**		 送信済ページセット		  */
		/*	 ﾘﾀﾞｲｱﾙ送信時はPage+1から送信 */
		/*--------------------------------*/
		if ((CommandFileOptionItem == SYS_MEMORY_TX) ||						/* 即時メモリ送信	  */
			(CommandFileOptionItem == SYS_DELAYED_MEMORY_TX) ||				/* 時刻指定メモリ送信 */
			(CommandFileOptionItem == SYS_MEMORY_SECURE_TX) ||				/* メモリ親展送信	  */
			(CommandFileOptionItem == SYS_MEMORY_RELAY_BROADCAST) ||		/* メモリ中継指示送信 */
			(CommandFileOptionItem == SYS_DELAYED_BROADCAST) ||				/* 順次同報送信		  */
			(CommandFileOptionItem == SYS_MEMORY_SUB_ADDRESS_TX) ||			/* #if (PRO_F_CODE == ENABLE) */
			(CommandFileOptionItem == SYS_CIPHER_TX) ||						/* #if (PRO_CIPHER == ENABLE) */
			(CommandFileOptionItem == SYS_RELAYED_TX)) {					/* 中継配信送信		  */
			SYS_CurrentExecutingCommand->Page = (TxMemoryFilePage - 1);		/** 送信済ページ */
		}
#if(PRO_BATCH_TX == ENABLE)
		else if (CommandFileOptionItem == SYS_BATCH_MEMORY_TX) {
			/* 2回以上送信エラーによるリダイヤルになった場合に送信済み頁を記憶 94/9/22 Y.Suzuki */
			SYS_CurrentExecutingCommand->Page = BatchTxFinishPage;		/* 送信済ページ */
		}
#endif
		if(SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
			SYS_CurrentExecutingCommand->Page = (TxMemoryFilePage - 1);		/** 送信済ページ */
		}
		/* ---------------------------------------------------------- */
		/* 送信証に MODE,START_TIME,TORTAL_TIME を載せるため8line追加 */
		/* -----------------------------96/04/23 By t.yamaguchi-----  */
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.8 K.Kawata */
/* 新送信証 */
		/*
		** Set Start time & Total time by H.Hirao 2000/02/03
		** Mode init in nomal.
		*/
		if ((FaxComResult & 0x0C00) == DIALERROR) {		/** ダイアル・エラー */
			SYB_ExecQueue[SYS_CurrentExecQueueNo].StartTime = SYB_CurrentTime;
			SYB_ExecQueue[SYS_CurrentExecQueueNo].TotalTime = 0;
			SYB_ExecQueue[SYS_CurrentExecQueueNo].Mode = 0;
		}
		else {
			if ( GrayModeFlag == 1 ) {
				SYS_CurrentExecutingCommand->Mode = FirstTxMode;			/** 通信モード */
			}
			else{
				SYS_CurrentExecutingCommand->Mode = TxMode;					/** 通信モード */
			}
			SYS_CurrentExecutingCommand->StartTime = FaxComStartTime;		/** 通信開始時間 */
			SYS_CurrentExecutingCommand->TotalTime = FaxComPeriod;			/** 通信時間 */
		}
#else
		if ( GrayModeFlag == 1 ) {
			SYS_CurrentExecutingCommand->Mode = FirstTxMode;			/** 通信モード */
		}
		else{
			SYS_CurrentExecutingCommand->Mode = TxMode;					/** 通信モード */
		}
		SYS_CurrentExecutingCommand->StartTime = FaxComStartTime;		/** 通信開始時間 */
		SYS_CurrentExecutingCommand->TotalTime = FaxComPeriod;			/** 通信時間 */
#endif

#if (1) /* 受領証ＯＮで通信エラー時、送信証が出ずにチェックメッセージが出る。By H.Fujimura 2002/08/21 */
		/* 1997/11/01 Y.Murata
		 * 受領証ＯＮの時の送信で、受領証をとれなかった時（交信ｴﾗｰ,ﾒﾓﾘない時とか）は送信証を書くんです
		 * 他の場所で、ちまちま送信証を書くように処理はいってますが、実はここだけでＯＫ。
		*/
		/*
		// 一括送信の場合にもCommandPを読み書きしに行っていました．
		// 一括送信時には，CommandPの値は前のコマンド送信のコマンドファイルを指しているか
		// もしくは不定な値が入っているので，送信予約が書き替えられて「送信証OFFなのに
		// 送信証をプリントした」等の不具合が発生していた可能性があります．2001/05/21 by J.Kishida
		*/
 #if(0)
//		/*if ((FaxComResult & 0x00FF) != 0x0014) {*/	/* 停止じゃなくて */
//			if (FaxComTXorRX_Sign == TX_COM_MODE) {	/* 送信で */
//				if ((CommandP->Option.ConfirmationReport & 0x03) == 0x03) {	/* 受領証設定にもかかわらず */
//					if (SYS_RxTotalPage < 1) {	/* １枚もうけてない */
//						CommandP->Option.ConfirmationReport |= SYS_TCR_AND_RCR;
//						SYS_CurrentExecutingCommand->Option |= SYS_PARTNER_NOT_RCR;
//					}
//				}
//			}
//		/*}*/
 #else
		if (FaxComTXorRX_Sign == TX_COM_MODE) {	/* 送信で */
			if ((CommandFileConfirmationReport & SYS_RCR_REQUESTED) == SYS_RCR_REQUESTED) {	/* 受領証設定 */
				if (SYS_RxTotalPage < 1) {	/* １枚もうけてない */
					CommandP->Option.ConfirmationReport |= SYS_TCR_AND_RCR;
					SYS_CurrentExecutingCommand->Option |= SYS_PARTNER_NOT_RCR;
				}
			}
		}
 #endif
#endif

		/*------------------*/
		/* 通信結果チェック */
		/*------------------*/
		if ((FaxComResult & 0x0C00) == NO_ERROR) {		/** 通信エラー無し */
			/*----------------*/
			/*	交信正常終了  */
			/*----------------*/ /* 条件追加 By t.yamaguchi '96.01.23 */
			if ((CommandFileOptionItem != SYS_POLLING_RX) &&				/* ポーリング受信 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
				(CommandFileOptionItem != SYS_CONTINUOUS_POLLING_RX) &&		/* 連続ポーリング受信 */
#endif
#if (PRO_F_CODE == ENABLE)
				(CommandFileOptionItem != SYS_SELECT_POLLING_RX) &&			/* 選択ポーリング */
#endif
				(CommandFileOptionItem != SYS_DB_POLLING_RX)) {				/* 検索ポーリング受信 */
				SpeedHandshakeAttributeChange();							/** ダイアルの属性(短縮ハンドシェーク)を変更 */
			}
			SYS_CurrentExecutingCommand->Result = FaxComResult;		/** 発信スケジューラ 通信結果 */
			SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;		/** 発信スケジューラ 正常終了 */
#if (PRO_TX_SPEED == V34) /* added by H.Kubo 1998/01/23 */
			if (SYS_V34ProcedureExecuting()) {	/* V34交信時 1996/09/03 Y.Murata */
				SYS_CurrentExecutingCommand->Result |= V34_MODE_SET;				/** 交信結果 */
			}
#endif /* (PRO_SPEED_TX == V34) */
			SetJournal();										/** コマンド通信 正常終了時 ジャーナルセット */
#if (PRO_SGP_TEST_ROM == ENABLE) /** By S.Wang 98/07/25 */
			SetSgpPerformanceData();
#endif
		}
		else if ((FaxComResult & 0x0C00) == DIALERROR) {		/** ダイアル・エラー */
		/*--------------------*/
		/* ダイアルエラー処理 */
		/*--------------------*/

			switch (AD_Result) {			/** オート・ダイアル結果判定 */

				/*-------------*/
				/* ダイアル OK */
				/*-------------*/
				case AD_OK:				/** OK	  */
				case AD_OK_DSE:			/** 極反  */
				case AD_OK_CED:			/** CED	  */
				case AD_OK_DIS:			/** DIS	  */
#if (PRO_SPEED_EX == ENABLE)
				case AD_OK_SPD_TONE:
#endif
#if (PRO_TX_SPEED == V34) /* Ported from Clover\src\fcm_last.c by H.Kubo 1997/08/05 */
#if (PRO_MODEM == R288F)
				case AD_OK_ANSWER_TONE:	/** ATV25 */
#endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34) */
					break;

				/*--------------*/
				/* ﾀﾞｲｱﾙ前のｴﾗｰ */
				/*--------------*/
				case AD_LOCAL_BUSY:		/** D.0.1 */
				case AD_NO_DIAL_TONE:	/** D.0.8 */
#if (PRO_FBS == ENABLE)	/* 1997/06/09  By T.Yamaguchi */
					/* BOOKのスキャナ送信はリダイヤルを行ないませんエラーのチェックメッセージをプリントする 1997/06/09  By T.Yamaguchi */
					if ((SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) && (SYS_ScannerExecMode == SCN_FBS)) {
						/* ﾁｪｯｸ･ﾒｯｾｰｼﾞのﾌﾟﾘﾝﾄを行う。 */
						SYS_CurrentExecutingCommand->Result = FaxComResult;				/** 交信結果 */
						SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;			/** エラー終了 */
						break;
					}
#endif

				/* ﾀﾞｲｱﾙ前のｴﾗｰは従来は、DEU,FRA以外 ﾘﾀﾞｲｱﾙ回数の減算を行っていませんでしたが、 */
				/* 今回からは 国対応に関わらず、ﾘﾀﾞｲｱﾙ回数を減算します			1995/12/15	*/
				/* （！、/）がダイヤルの最後の桁にはいっていて、AD_NO_DIAL_TONEで返ってくると無限に減算しないため */
					DecrementRedialCount();				/** リダイアル・カウントを減算し転送電話番号をSETする */
					break;

				/*--------------*/
				/* ﾀﾞｲｱﾙ時のｴﾗｰ */
				/*--------------*/
				case AD_STOPPED:		/* D.0.3 */

#if defined(DEU)	/* ﾄﾞｲﾂ仕様 */
			/*		DecrementRedialCount();		*/
					SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;				/** 正常終了 */
#else
	#if (PRO_MONITOR_REPORT == ENABLE)	/* モニター・レポート機能 By H.Y 1994/12/19 */
					SYS_CurrentExecutingCommand->Result = FaxComResult;				/** 交信結果 */
	#endif
					SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;				/** 正常終了 */
#endif
					if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {						/** 送信証を出さない */
/*					if (SYS_FaxComTxType == SYS_SCANNER_TX) {	1996/11/28	By T.Yamaguchi	/@@ 送信証を出さない */
/*						CommandP->Option.ConfirmationReport &= ~(TCR_REQUEST | SYS_TCR_AND_RCR);/@ 1997/09/12  By T.Yamaguchi */
						CommandP->Option.ConfirmationReport &= ~(SYS_TCR_REQUESTED | SYS_TCR_AND_RCR);/* 96/06/19 By T.Yamaguchi */
					}
					break;

				case AD_DIAL_EMPTY:		/* D.0.6 */

#if defined(DEU)	/* ﾄﾞｲﾂ仕様 */
					DecrementRedialCount();
#else
					/* ﾁｪｯｸ･ﾒｯｾｰｼﾞのﾌﾟﾘﾝﾄを行う。 */
					SYS_CurrentExecutingCommand->Result = FaxComResult;				/** 交信結果 */
 #if defined(KEISATSU)	/* 警察FAX DVT_ID67 Modify by SMuratec 夏 2005/12/15 */
 					if ((FaxComResult & 0x00FF) == 0x0091){
						SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;			/* 強制終了メッセージ印字して、通信エラー印字必要ない */
					}
					else{
						SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;		/** エラー終了 */
					}
 #else
					SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;			/** エラー終了 */
 #endif /* defined(KEISATSU) */
#endif
					if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {	/* 1997/09/12  By T.Yamaguchi 送信証を出さない */
/*					if (SYS_FaxComTxType == SYS_SCANNER_TX) {						/** 送信証を出さない */
/*						CommandP->Option.ConfirmationReport &= ~(TCR_REQUEST | SYS_TCR_AND_RCR); /@ 96/06/19 By T.Yamaguchi */
						CommandP->Option.ConfirmationReport &= ~(SYS_TCR_REQUESTED | SYS_TCR_AND_RCR);/* 1997/09/12  By T.Yamaguchi */
						SYS_CurrentExecutingCommand->Option &= ~(SYS_PARTNER_NOT_RCR);
					}
					break;

				/*--------------*/
				/* ﾀﾞｲｱﾙ後のｴﾗｰ */
				/*--------------*/
				case AD_TIME_OVER:		/* D.0.7 */
				case AD_REMOTE_BUSY:	/* D.0.2 */
				case AD_NO_CURRENT_LOOP:/* D.0.9 */

#if (PRO_FBS == ENABLE) /* 1997/06/09  By T.Yamaguchi */
					/* BOOKのスキャナ送信はリダイヤルを行ないませんエラーのチェックメッセージをプリントする */
					if ((SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) && (SYS_ScannerExecMode == SCN_FBS)) {
						/* ﾁｪｯｸ･ﾒｯｾｰｼﾞのﾌﾟﾘﾝﾄを行う。 */
						SYS_CurrentExecutingCommand->Result = FaxComResult;				/** 交信結果 */
						SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;			/** エラー終了 */
						break;
					}
#endif

					DecrementRedialCount();					/** リダイアル・カウントを減算し転送電話番号をSETする */
					break;
#if 0 /* defined(FRA) */			/* '95/02/27	by M.HARADA	*/
				case AD_DETECT_RINGBACKTONE:/* D.?.? */

					if (CHK_UNI_HumanAnswerClear()) {
						switch (DialKind) {
						case SYS_SPEED_DIAL:
							ClearSpeedRecord(SpeedDialPosition);
							break;
						case SYS_ONETOUCH_DIAL:
							ClearOnetouchRecord(OnetouchDialPosition);
							break;
						default:
							break;
						}
					}
					SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;
					break;
#endif
				default:/* 通常有りえない '96.01.17 By T.Y */
					/* ﾁｪｯｸ･ﾒｯｾｰｼﾞのﾌﾟﾘﾝﾄを行う。 */
					SYS_CurrentExecutingCommand->Result = FaxComResult;				/** 交信結果 */
					SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;			/** エラー終了 */
					break;
			}
#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* 日立特許回避 1998/10/28 Y.Matsukuma */
			/* 送信証にのせるため、ダイアルエラーも通信開始時間をいれます。*/
			SYS_CurrentExecutingCommand->StartTime = SYB_CurrentTime;		/** 通信開始時間 */
#endif

#if defined (KEISATSU) /* 警察FAX DVT_ID46 Modify by SMuratec 夏 2005/11/24 */
 			if ((FaxComResult & 0x00FF) == 0x0091) {
				SetJournal();
			}
#endif	
		}
		else if ((FaxComResult & 0x0C00) == TRANSMITERROR) {		/** 送信エラー */
		/*----------------*/
		/* 送信エラー処理 */
		/*----------------*/
			SpeedHandshakeAttributeDel();		/** ダイアルの属性(短縮ハンドシェーク)を削除 */

#if (PRO_RELAYED_REPORT == ENABLE)	/* 1995/02/10 */
			/*-------------------------------------*/
			/* 不達通知送信時のｴﾗｰは何でも再送する */
			/*-------------------------------------*/
			if (CommandFileOptionItem == SYS_RELAYED_TX_REPORT) {
				DecrementRedialCount();
			}
			else {	/* 不達通知でない */
#endif
				/*--------------*/
				/* ECM_MODE_SET */
				/*--------------*/
				switch (FaxComResult&~ECM_MODE_SET) {		/** 交信結果 */
#if defined(KEISATSU)	/* 警察FAX DVT_ID67 Added start by SMuratec 夏 2005/12/15 */
					case TRANSMITERROR|0x0091:			/* T.9.1 */
						/*------------------------------------*/
						/* スキャナ送信エラー全て再送しません */
						/*------------------------------------*/
						if ((CommandFileOptionItem == SYS_SCANNER_TX) ||				/* 即時スキャナ送信 */
							(CommandFileOptionItem == SYS_SCANNER_SECURE_TX) ||			/* スキャナ親展送信 */
							(CommandFileOptionItem == SYS_SCANNER_RELAY_BROADCAST) ||	/* スキャナ中継指示送信 */
#if (PRO_F_CODE == ENABLE)
							(CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX) ||	/* スキャナサブアドレス送信 */
#endif
							(CommandFileOptionItem == SYS_DELAYED_SCANNER_TX)) {		/* 時刻指定スキャナ送信 */ /** スキャナ送信 */
 /* 警察FAX DVT_ID79 Modify by SMuratec 夏 2005/12/21 
 ** スキャナ送信のﾘﾀﾞｲﾔﾙ場合、警察属性違いになる。
 ** 実行コマンドのStatus値はマルチ回設置するから、
 ** DecrementRedialCount()では不正確Statusからチックします。
 */
 #if 0 
							SYS_CurrentExecutingCommand->Result = FaxComResult;
							SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;
							if (SYS_TxTotalPage == 0) {	
								DecrementRedialCount();				/* リダイアル・カウントを減算し転送電話番号をSET */
							}
 #else
							if (SYS_TxTotalPage == 0) {	
								DecrementRedialCount();				/* リダイアル・カウントを減算し転送電話番号をSET */
							}
							else{
								SYS_CurrentExecutingCommand->Result = FaxComResult;
								SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;
							}
 #endif
						}
						else{
							DecrementRedialCount();				/* リダイアル・カウントを減算し転送電話番号をSET */
						}
						break;
#endif	/* 警察FAX DVT_ID67 Added end by SMuratec 夏 2005/12/15 */
					case TRANSMITERROR|0x0014:			/* T.1.4 */
						SYS_CurrentExecutingCommand->Result = FaxComResult;		/** 交信結果 */
						SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;		/** 正常終了 */
						/* 3line add By T.Yamaguchi 96/08/09 */
						if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {			/** 送信証を出さない */
/*							CommandP->Option.ConfirmationReport &= ~(TCR_REQUEST | SYS_TCR_AND_RCR);/@ 96/06/19 By T.Yamaguchi */
							CommandP->Option.ConfirmationReport &= ~(SYS_TCR_REQUESTED | SYS_TCR_AND_RCR);/* 1997/09/12  By T.Yamaguchi */
							SYS_CurrentExecutingCommand->Option &= ~(SYS_PARTNER_NOT_RCR);	/* Add By O.Kimoto 1997/09/05 */
						}
						break;

					case TRANSMITERROR|0x0041:			/* T.4.1 */
					case TRANSMITERROR|0x0044:			/* T.4.4 */
#if 0	/* 警察FAX DVT_ID67 Deleted by SMuratec 夏 2005/12/15 */
@@#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 李 2005/11/19 */
@@					case TRANSMITERROR|0x0091:			/* T.9.1 */
@@#endif /* defined (KEISATSU) */
#endif
						/*------------------------------------*/
						/* スキャナ送信エラー全て再送しません */
						/*------------------------------------*/
						if ((CommandFileOptionItem == SYS_SCANNER_TX) ||				/* 即時スキャナ送信 */
							(CommandFileOptionItem == SYS_SCANNER_SECURE_TX) ||			/* スキャナ親展送信 */
							(CommandFileOptionItem == SYS_SCANNER_RELAY_BROADCAST) ||	/* スキャナ中継指示送信 */
#if (PRO_F_CODE == ENABLE)
							(CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX) ||	/* スキャナサブアドレス送信 */
#endif
							(CommandFileOptionItem == SYS_DELAYED_SCANNER_TX)) {		/* 時刻指定スキャナ送信 */ /** スキャナ送信 */
							SYS_CurrentExecutingCommand->Result = FaxComResult;
							SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
						}
						/*------------------*/
						/* メモリ送信エラー */
						/*------------------*/
						else {/* T.4.1/T.4.4ｴﾗｰ時は再送します。 */
							if (CHK_ErrorRedialAvailble() != 0) {		/** 通信エラー時に再送する */
								DecrementRedialCount();				/* リダイアル・カウントを減算し転送電話番号をSET */
							}
							else  {
								SYS_CurrentExecutingCommand->Result = FaxComResult;
								SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
							}
						}
						break;

					case TRANSMITERROR|0x0011:			/* T.1.1 */
						if (SYS_TxTotalPage > 0) {		/** １枚以上送信 */
							/*------------------------------------*/
							/* スキャナ送信エラー全て再送しません */
							/*------------------------------------*/
							if ((CommandFileOptionItem == SYS_SCANNER_TX) ||				/* 即時スキャナ送信 */
								(CommandFileOptionItem == SYS_SCANNER_SECURE_TX) ||			/* スキャナ親展送信 */
								(CommandFileOptionItem == SYS_SCANNER_RELAY_BROADCAST) ||	/* スキャナ中継指示送信 */
#if (PRO_F_CODE == ENABLE)
								(CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX) ||	/* スキャナサブアドレス送信 */
#endif
								(CommandFileOptionItem == SYS_DELAYED_SCANNER_TX)) {		/* 時刻指定スキャナ送信 */ /** スキャナ送信 */
								SYS_CurrentExecutingCommand->Result = FaxComResult;
								SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
							}
							/*------------------*/
							/* メモリ送信エラー */
							/*------------------*/
							else {/* T.1.1 & if MCF has been received ｴﾗｰ時は再送します。 */
								DecrementRedialCount();			/** リダイアル・カウントを減算し転送電話番号をSET */
							}
						}
						else {		/** １枚も送れない */
						/* Ported from Clover\src\fcm_last.c by H.Kubo 1997/08/05 */
						/* V34ｽﾀｰﾄｱｯﾌﾟ時のｴﾗｰはﾘﾀﾞｲｱﾙ 1996/09/04 */
							if (SYS_V34ProcedureExecuting()) {
#if (PRO_TX_SPEED == V34) /* changed by H.Kubo 1997/10/23 */
								DecrementRedialCount();			/** リダイアル・カウントを減算し転送電話番号をSET */
								SYS_CurrentExecutingCommand->Option |= SYS_V34_STUP_RECOVER;
								reset_journal = 1;	/* モデム不具合はジャーナルにのせない 1996/10/29 */
#endif /* (PRO_TX_SPEED == V34) */
							}
							else { /* V33, V17, V29, V27 always comes here. */
								SYS_CurrentExecutingCommand->Result = FaxComResult;		/** 交信結果 */
								SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;	/** エラー終了 */
							}
						}
						break;
#if (PRO_TX_SPEED == V34) /* Ported from Clover\src\fcm_last.c by H.Kubo 1997/08/05 */
					/* V34ｽﾀｰﾄｱｯﾌﾟ時のｴﾗｰはﾘﾀﾞｲｱﾙ 1996/09/04 */
					case TRANSMITERROR|0x008A:	/* ﾌﾟﾛｰﾋﾞﾝｸﾞｴﾗｰ */
					case TRANSMITERROR|0x008B:	/* TRNｴﾗｰ */
						if (SYS_TxTotalPage > 0) {		/** １枚以上送信 */
							/* １枚以上送信してｽﾀｰﾄｱｯﾌﾟｴﾗｰということは受領証時のｴﾗｰ */
							SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;		/** 正常終了 */
						}
						else {
							DecrementRedialCount();			/** リダイアル・カウントを減算し転送電話番号をSET */
							SYS_CurrentExecutingCommand->Option |= SYS_V34_STUP_RECOVER;
							reset_journal = 1;	/* モデム不具合はジャーナルにのせない 1996/10/29 */
						}
						break;
#endif /* (PRO_TX_SPEED == V34) */

					default:
						SYS_CurrentExecutingCommand->Result = FaxComResult;
						SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
						break;
				}
#if (PRO_TX_SPEED == V34)
				if (SYS_V34ProcedureExecuting()) {	/* V34交信時 1996/09/03 Y.Murata */
					SYS_CurrentExecutingCommand->Result |= V34_MODE_SET;				/** 交信結果 */
				}
				/* モデム不具合はジャーナルにのせない 1996/10/29 */
 #if defined(KEISATSU) /* 警察FAX DVT_ID46 Modify by SMuratec 夏 2005/11/24 */
				if ((reset_journal == 0) || ((FaxComResult & 0x00FF) == 0x0091)) {
 #else
 				if (reset_journal == 0) {
 #endif
					SetJournal();
				}
#else
				SetJournal();				/** コマンド通信 送信エラー ジャーナル・セット */
#endif

#if (PRO_RELAYED_REPORT == ENABLE)	/* 1995/02/10 */
			}	/* End of 不達通知でない */
#endif
		}
		/*------------------------------------------*/
		/* ｺﾏﾝﾄﾞ通信でも受信ｴﾗｰの時は再発呼しません */
		/*------------------------------------------*/
		else if ((FaxComResult & 0x0C00) == RECEIVEERROR) {			/** 受信エラー */
			SYS_CurrentExecutingCommand->Result = FaxComResult;			/** 交信結果 */
			if ((FaxComTXorRX_Sign == RX_COM_MODE) &&			/* ﾎﾟｰﾘﾝｸﾞ時のｴﾗｰ */
				((FaxComResult&~ECM_MODE_SET) != (RECEIVEERROR|0x0014))) {	/* R.1.4 エラーでない */
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997\08\05 */
				switch (FaxComResult&~ECM_MODE_SET) {		/** 交信結果 */
 #if defined(KEISATSU)	/* 警察FAX DVT_ID67 Added start by SMuratec 夏 2005/12/15 */
 				case RECEIVEERROR|0x0091:
 					SYS_CurrentExecutingCommand->Result = FaxComResult;		/** 交信結果 */
					SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;	
 					break;
 #endif
				case RECEIVEERROR|0x008A:	/* ﾌﾟﾛｰﾋﾞﾝｸﾞｴﾗｰ */
				case RECEIVEERROR|0x008B:	/* TRNｴﾗｰ */
					DecrementRedialCount();			/** リダイアル・カウントを減算し転送電話番号をSET */
					SYS_CurrentExecutingCommand->Option |= SYS_V34_STUP_RECOVER;
					reset_journal = 1;	/* モデム不具合はジャーナルにのせない 1996/10/29  */
					break;
				case RECEIVEERROR|0x0011:
					if (SYS_RxTotalPage > 0) {		/** １枚以上受信 */
						SYS_CurrentExecutingCommand->Result = FaxComResult;		/** 交信結果 */
						SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;	/** エラー終了 */
					}
					else {
						if (SYS_V34ProcedureExecuting()) {
							DecrementRedialCount();			/** リダイアル・カウントを減算し転送電話番号をSET */
							SYS_CurrentExecutingCommand->Option |= SYS_V34_STUP_RECOVER;
							reset_journal = 1;	/* モデム不具合はジャーナルにのせない 1996/10/29 */
						}
						else {
							SYS_CurrentExecutingCommand->Result = FaxComResult;		/** 交信結果 */
							SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;	/** エラー終了 */
						}
					}
					break;
				default:
					SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;	/** エラー終了 */
					break;
				}
#else /* (PRO_TX_SPEED == V34) */
				SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;		/** エラー終了 */
#endif /* (PRO_TX_SPEED == V34) */
			}
			else { /** 受領証時のエラー */
				SYS_CurrentExecutingCommand->Status = SYS_EXEC_OK;		/** 正常終了 */

				/* 1997/01/31 Y.Murata
				 * 受領証受信にいって、受信できなっかた時は送信証を書きます
				*/
				if (FaxComTXorRX_Sign == TX_COM_MODE) {	/* 受領証受信 */
					CommandP->Option.ConfirmationReport |= SYS_TCR_AND_RCR;
					SYS_CurrentExecutingCommand->Option |= SYS_PARTNER_NOT_RCR;
				}

				/* 2000/02/07 Y.Murata
				 *
				*/
				if ((FaxComResult&~ECM_MODE_SET) == (RECEIVEERROR|0x0014)) {	/* R.1.4 エラー */
					if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {			/** 送信証を出さない */
						CommandP->Option.ConfirmationReport &= ~(SYS_TCR_REQUESTED | SYS_TCR_AND_RCR);/* 1997/09/12  By T.Yamaguchi */
						SYS_CurrentExecutingCommand->Option &= ~(SYS_PARTNER_NOT_RCR);	/* Add By O.Kimoto 1997/09/05 */
					}
				}

			}

#if (PRO_TX_SPEED == V34)
			if (SYS_V34ProcedureExecuting()) {	/* V34交信時 1996/09/03 Y.Murata */
				SYS_CurrentExecutingCommand->Result |= V34_MODE_SET;				/** 交信結果 */
			}
			/* モデム不具合はジャーナルにのせない 1996/10/29 */
 #if defined(KEISATSU) /* 警察FAX DVT_ID46 Modify by SMuratec 夏 2005/11/24 */
				if ((reset_journal == 0) || ((FaxComResult & 0x00FF) == 0x0091)) {
 #else
 				if (reset_journal == 0) {
 #endif
				SetJournal();				/** コマンド通信 受信エラー ジャーナルセット */
			}
#else
			SetJournal();				/** コマンド通信 受信エラー ジャーナルセット */
#endif

		}
		
#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 夏 2005/11/01 */
		if ( FaxComTXorRX_Flag == TX_COM_MODE ) {
			if ((FaxComResult&~ECM_MODE_SET) == (TRANSMITERROR|0x0091)) {
				SYS_CurrentExecutingCommand->RedialTime = 0;
				SYS_CurrentExecutingCommand->RedialCount = CHK_RedialCount() + (UBYTE)0x01;
			}
		}
#endif /* defined (KEISATSU) */


		/*------------------*/
		/* Ｖ８属性のセット */
		/*------------------*/
		V8CapableAttributeSet();

#if (0) /* 受領証ＯＮで通信エラー時、送信証が出ずにチェックメッセージが出る。By H.Fujimura 2002/08/21 */
//		/* 1997/11/01 Y.Murata
//		 * 受領証ＯＮの時の送信で、受領証をとれなかった時（交信ｴﾗｰ,ﾒﾓﾘない時とか）は送信証を書くんです
//		 * 他の場所で、ちまちま送信証を書くように処理はいってますが、実はここだけでＯＫ。
//		*/
//		/*
//		// 一括送信の場合にもCommandPを読み書きしに行っていました．
//		// 一括送信時には，CommandPの値は前のコマンド送信のコマンドファイルを指しているか
//		// もしくは不定な値が入っているので，送信予約が書き替えられて「送信証OFFなのに
//		// 送信証をプリントした」等の不具合が発生していた可能性があります．2001/05/21 by J.Kishida
//		*/
//#if(0)
////		/*if ((FaxComResult & 0x00FF) != 0x0014) {*/	/* 停止じゃなくて */
////			if (FaxComTXorRX_Sign == TX_COM_MODE) {	/* 送信で */
////				if ((CommandP->Option.ConfirmationReport & 0x03) == 0x03) {	/* 受領証設定にもかかわらず */
////					if (SYS_RxTotalPage < 1) {	/* １枚もうけてない */
////						CommandP->Option.ConfirmationReport |= SYS_TCR_AND_RCR;
////						SYS_CurrentExecutingCommand->Option |= SYS_PARTNER_NOT_RCR;
////					}
////				}
////			}
////		/*}*/
//#else
//		if (FaxComTXorRX_Sign == TX_COM_MODE) {	/* 送信で */
//			if ((CommandFileConfirmationReport & SYS_RCR_REQUESTED) == SYS_RCR_REQUESTED) {	/* 受領証設定 */
//				if (SYS_RxTotalPage < 1) {	/* １枚もうけてない */
//					CommandP->Option.ConfirmationReport |= SYS_TCR_AND_RCR;
//					SYS_CurrentExecutingCommand->Option |= SYS_PARTNER_NOT_RCR;
//				}
//			}
//		}
//#endif
#endif

	}
	/*----------*/
	/* 手動送信 */
	/*----------*/
	else if(SYS_FaxComType == SYS_MANUAL_TX) {		/* 手動送信時のｴﾗｰ処理 */
		if (((FaxComResult & 0x0C00) == TRANSMITERROR) &&
			(CHK_CheckMessagePrint() != 0) &&
			((FaxComResult&~ECM_MODE_SET) != (TRANSMITERROR|0x0014))) {		/** 送信エラーでチェックメッセージプリントでT.1.4エラーでない */
			BackUpFaxComResult = FaxComResult;
			CMN_StringCopyNumOrNULL(BackUpStandardID, NonStandardID, 20);		/** ID バックアップ */
/* 
** 送信証とチェックメッセージを両方プリントする不具合、
** PRO_MULTI_LINE == ENABLEと同じパスにします 1999/1/26 by T.Soneoka 
*/
#if (0)
**#if (PRO_MULTI_LINE == ENABLE)
**			SYS_BackUpManualFaxCommErrReq = 1;
**#else
**			SYS_ManualFaxCommErrRequest = 1;					/** 手動通信チェックメッセージのプリント要求 */
**#endif
#else
			SYS_BackUpManualFaxCommErrReq = 1;
#endif
		}
		SetJournal();				/** 手動送信 ジャーナルセット */
	}
	/*----------*/
	/* 自動着信 */
	/*----------*/
	else if(SYS_FaxComType == SYS_AUTO_CALLED) {/* 自動受信時のｴﾗｰ処理 */
		if ((FaxComResult&~ECM_MODE_SET) == (RECEIVEERROR|0x11)&&
			(SYS_RxTotalPage == 0)) {
			/*-------------------------------------------------------*/
			/** R.1.1で受信ページ数0の場合はジャーナルには載せません */
			/*-------------------------------------------------------*/
		}
#if defined (KEISATSU) /* 警察FAX 05/11/21 石橋正和 */
		else if (FCM_ShireiOff == TRUE) {
			/* 指令起動信号をOFFにしただけの場合 */
		}
#endif
		else {/* 自動受信時ﾁｪｯｸ･ﾒｯｾｰｼﾞは出しません。 */

#if (PRO_TX_SPEED == V34)
			/* モデム不具合はジャーナルにのせない 1996/10/29 */
			if (FaxComTXorRX_Sign == RX_COM_MODE) {	/* 受信 */
				switch (FaxComResult&~ECM_MODE_SET) {		/** 交信結果 */
				case RECEIVEERROR|0x008A:	/* ﾌﾟﾛｰﾋﾞﾝｸﾞｴﾗｰ */
				case RECEIVEERROR|0x008B:	/* TRNｴﾗｰ */
					if (SYS_RxTotalPage == 0) {
						reset_journal = 1;
					}
					break;
				default:
					break;
				}
			}
#endif

#if (PRO_TX_SPEED == V34)
			if (SYS_V34ProcedureExecuting()) {	/* V34交信時 1996/09/03 Y.Murata */
				/* SYS_CurrentExecutingCommand->Result |= V34_MODE_SET; */	/* Deleted by H.Kubo 1998/01/29 */
			}
			/* モデム不具合はジャーナルにのせない 1996/10/29 */
 #if defined(KEISATSU) /* 警察FAX DVT_ID46 Modify by SMuratec 夏 2005/11/24 */
				if ((reset_journal == 0) || ((FaxComResult & 0x00FF) == 0x0091)) {
 #else
 				if (reset_journal == 0) {
 #endif
				SetJournal();			/** 自動着信 ジャーナルセット */
			}
#else
			SetJournal();			/** 自動着信 ジャーナルセット */
#endif

		}
	}
	/*----------*/
	/* 手動受信 */
	/*----------*/
#if defined (KEISATSU) /* 警察FAX 05/12/02 石橋正和 */
	else if((SYS_FaxComType == SYS_MANUAL_RX) && (FCM_ShireiOff == FALSE)) {/* 手動受信時のｴﾗｰ処理 */
#else
	else if(SYS_FaxComType == SYS_MANUAL_RX) {/* 手動受信時のｴﾗｰ処理 */
#endif
		if (((FaxComResult&0x0C00) != NO_ERROR) && (CHK_CheckMessagePrint() != 0)) {
			if (((FaxComResult&~ECM_MODE_SET) != (RECEIVEERROR|0x0014)) &&
				((FaxComResult&~ECM_MODE_SET) != (TRANSMITERROR|0x0014))) {		/** 通信エラーでチェックメッセージプリントでT.1.1 / R.1.4でない */
				BackUpFaxComResult = FaxComResult;							/** 交信結果バックアップ */
				CMN_StringCopyNumOrNULL(BackUpStandardID, NonStandardID, 20);	/** ID バックアップ */
/* 
** 送信証とチェックメッセージを両方プリントする不具合、
** PRO_MULTI_LINE == ENABLEと同じパスにします 1999/1/26 by T.Soneoka 
*/
#if (0)
**#if (PRO_MULTI_LINE == ENABLE)
**				SYS_BackUpManualFaxCommErrReq = 1;
**#else
**				SYS_ManualFaxCommErrRequest = 1;			/** 手動通信チェックメッセージのプリント要求 */
**#endif
#else
				SYS_BackUpManualFaxCommErrReq = 1;
#endif
			}
		}
		SetJournal();			/** 手動受信 ジャーナルセット */
	}
	/*--------------------*/
	/* リモートＦＡＸ送信 */
	/*--------------------*/
#if (PRO_REMOTE_FAX == ENABLE)
	else if ( SYS_FaxComType == SYS_REMOTE_FAX_TX ) {	/** リモートＦＡＸ送信時のエラー処理 */
		if (((FaxComResult & 0x0C00) == TRANSMITERROR) &&
			(CHK_CheckMessagePrint() != 0) &&
			((FaxComResult&~ECM_MODE_SET) != (TRANSMITERROR|0x0014))) {		/** 送信エラーでチェックメッセージプリントで T.1.4 でない */
			BackUpFaxComResult = FaxComResult;				/** 交信結果バックアップ */
			CMN_StringCopyNumOrNULL(BackUpStandardID, NonStandardID, 20);	/** ID バックアップ */
/* 
** 送信証とチェックメッセージを両方プリントする不具合、
** PRO_MULTI_LINE == ENABLEと同じパスにします 1999/1/26 by T.Soneoka 
*/
#if (0)
**#if (PRO_MULTI_LINE == ENABLE)
**				SYS_BackUpManualFaxCommErrReq = 1;
**#else
**				SYS_ManualFaxCommErrRequest = 1;			/** 手動通信チェックメッセージのプリント要求 */
**#endif
#else
				SYS_BackUpManualFaxCommErrReq = 1;
#endif
		}
		SetJournal();			/** リモートＦＡＸ ジャーナルセット */
	}
#endif
	/*--------------------*/
	/* 手動ポーリング受信 */
	/*--------------------*/
	else if ( SYS_FaxComType == SYS_MANUAL_POLLING ) {	/** 手動ポーリング受信時のエラー処理 1994/11/16 */
		if (((FaxComResult & 0x0C00) == TRANSMITERROR) &&
			(CHK_CheckMessagePrint() != 0) &&
			((FaxComResult&~ECM_MODE_SET) != (TRANSMITERROR|0x0014))) {		/** 送信エラーでチェックメッセージプリントで T.1.4 でない */
			BackUpFaxComResult = FaxComResult;				/** 交信結果バックアップ */
			CMN_StringCopyNumOrNULL(BackUpStandardID, NonStandardID, 20);	/** ID バックアップ */
/* 
** 送信証とチェックメッセージを両方プリントする不具合、
** PRO_MULTI_LINE == ENABLEと同じパスにします 1999/1/26 by T.Soneoka 
*/
#if (0)
**#if (PRO_MULTI_LINE == ENABLE)
**				SYS_BackUpManualFaxCommErrReq = 1;
**#else
**				SYS_ManualFaxCommErrRequest = 1;			/** 手動通信チェックメッセージのプリント要求 */
**#endif
#else
				SYS_BackUpManualFaxCommErrReq = 1;
#endif
		}
		SetJournal();			/** 手動ポーリング受信 ジャーナルセット */
	}

	/*--------*/
	/* その他 */
	/*--------*/
	else if ((SYS_FaxComType == SYS_REMOTE_DIAG) ||
			 (SYS_FaxComType == SYS_FIP_SEND) ||
			 (SYS_FaxComType == SYS_FIP_POLL) ||
			 (SYS_FaxComType == SYS_FIP_CALLED)) {
			if ((FaxComResult & DIALERROR) == DIALERROR) {		/** ダイアルエラー */
				FaxComPeriod = 0;	/* if (DIALERROR)  FaxComPeriod = 0sec. */
			}
#if 0
			SetJournal();				/** その他のジャーナルセット */
#endif
			else {			/* 1995/01/19 条件追加 ダイアルエラーはジャーナルに乗せない */
				SetJournal();
			}

	}

	/*-------------------------------------------*/
	/** Ｔ－３０プロトコル・モニタの自動印字設定 */
	/*-------------------------------------------*/
	if( (CHK_PmonitorAutoPrint())				&&
		(FaxTelResult != FCOM_TEL1_OFF_HOOK)	&&
		(FaxTelResult != FCOM_TEL2_OFF_HOOK)	&&
		(FaxTelResult != FCOM_HOOK_KEY)			&&
		(FaxTelResult != TMOUT_RESP)			&&
#if defined (KEISATSU) /* 警察FAX 05/12/05 石橋正和 */
		(FCM_ShireiOff == FALSE)				&&
#endif
		((FaxComResult&0x0C00) != DIALERROR)) {		/** T30プリント設定でダイアルエラーでない */

#if (PRO_MULTI_LINE == ENABLE)
		SYS_BackUpProtocolMonitorReq = 1;
#else
		SYS_ProtocolMonitorPrintRequest = 1;		/** プロトコルモニタのプリント要求 セット */
#endif
	}
	/* 通信エラー時にＴ３０自動印字の処理を追加	 竹内 Jun.29.1995 */
	else if (((FaxComResult & DIALERROR) != DIALERROR)
		&&	 (FaxComResult & 0x00FF)
		&&	 CHK_ErrorPmonitorAutoPrint()) {	/**	通信エラー時(D.x.x以外)でＴ３０自動印字ＯＮ */

#if (PRO_MULTI_LINE == ENABLE)
		SYS_BackUpProtocolMonitorReq = 1;
#else
		SYS_ProtocolMonitorPrintRequest = 1;		/** プロトコルモニタのプリント要求 セット */
#endif
	}
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/05 */
	else if ((CHK_ErrorPmonitorAutoPrint())
		&&  (SYS_V34ProcedureExecuting()) && (MDM_AbortCode != 0)) { /* 1996/09/13 */

#if (PRO_MULTI_LINE == ENABLE)
		SYS_BackUpProtocolMonitorReq = 1;
#else
		SYS_ProtocolMonitorPrintRequest = 1;
#endif
	}
#endif /* (PRO_TX_SPEED == V34) */
	else {
#if (PRO_MULTI_LINE == ENABLE)
		SYS_BackUpProtocolMonitorReq = 0;
#else
		SYS_ProtocolMonitorPrintRequest = 0;		/** プロトコルモニタのプリント要求 クリア */
#endif
	}
#if (PRO_MODEM == R288F)
	/* もしCTSがｵﾝしなかったら、ｺﾝﾊﾟﾁｺｰﾄﾞに予期せぬｴﾗｰをｾｯﾄ */ /* 1996/09/13 Y.M */
	/* ｷｬﾘｱ断の時もｺﾝﾊﾟﾁｺｰﾄﾞに追加 1996/09/20 */
	if (FaxCompatibleErrorCode == 0) {	/* add if() 1997/05/17 */
		if (MDM_FedOffFlag == 1) {
			FaxCompatibleErrorCode = MDM_CARRIER_OFF1;
			MDM_FedOffFlag = 0;
		}
		else if (MDM_FedOffFlag == 2) {
			FaxCompatibleErrorCode = MDM_CARRIER_OFF2;
			MDM_FedOffFlag = 0;
		}
		else {
			if (FCM_CheckModemAbort()) {
				FaxCompatibleErrorCode = MDM_CTS_ABORT;
			}
		}
	}
#endif

	MsgFromFaxComToMain.Item	= FROM_FAXCOM;
	MsgFromFaxComToMain.Message = MSG_FAXCOM_END;

	/* if( VoiceCallFormedFlag == 1 ){ */			/* 1994/06/20 */
	if (SYS_VoiceCallAccepted) {	/** 会話予約成立 */
		/* ＬＣＤ表示　リダイアル */
		MsgFromFaxComToMain.Message = MSG_FAXCOM_END_OFF_HOOK;
		MsgFromFaxComToMain.SubMessage1 = FAXCOM_REDIAL;

		if (SYS_VoiceCallAccepted == TEL1_OH_DETECT) {
			MsgFromFaxComToMain.SubMessage2 = MSG_FCOM_TEL1_OH;
		}
		else if (SYS_VoiceCallAccepted == TEL2_OH_DETECT) {
			MsgFromFaxComToMain.SubMessage2 = MSG_FCOM_TEL2_OH;
		}
		else if (SYS_VoiceCallAccepted == HOOK_KEY_OH_DETECT) {
			MsgFromFaxComToMain.SubMessage2 = MSG_FCOM_HOOK_KEY_OH;
		}
	}
	else if ((FaxTelResult == FCOM_TEL1_OFF_HOOK) ||
			(FaxTelResult == FCOM_TEL2_OFF_HOOK)  ||
			(FaxTelResult == FCOM_HOOK_KEY)) {		/** TEL/FAX待機で疑似ベル鳴動中にオペレーター介入 */
		/* ＬＣＤ表示　リダイアル */
		MsgFromFaxComToMain.Message = MSG_FAXCOM_END_OFF_HOOK;
		MsgFromFaxComToMain.SubMessage1 = FAXCOM_REDIAL;
		SYS_VoiceCallAccepted = 1;							/* 1994/07/18 HungUp Debug */

		if (FaxTelResult == FCOM_TEL1_OFF_HOOK) {
			MsgFromFaxComToMain.SubMessage2 = MSG_FCOM_TEL1_OH;
		}
		else if (FaxTelResult == FCOM_TEL2_OFF_HOOK) {
			MsgFromFaxComToMain.SubMessage2 = MSG_FCOM_TEL2_OH;
		}
		else if (FaxTelResult == FCOM_HOOK_KEY) {
			MsgFromFaxComToMain.SubMessage2 = MSG_FCOM_HOOK_KEY_OH;
		}
	}
	else{
		switch (FaxComResult&~(ECM_MODE_SET)) {
			case NO_ERROR:
				/* ＬＣＤ表示 ＯＫ */
				MsgFromFaxComToMain.SubMessage1 = FAXCOM_OK;
				break;
			case RECEIVEERROR|0x11:
				if (SYS_FaxComType == SYS_MANUAL_RX) {
					/* ＬＣＤ表示　ＬＥＤアラーム */
					MsgFromFaxComToMain.SubMessage1 = FAXCOM_ERROR;
				}
				else if (SYS_FaxComType == SYS_AUTO_CALLED) {

/****** ｵﾝﾌｯｸ転送T1ﾀｲﾑｱｳﾄ時ｴﾗｰｱﾗｰﾑを無くすため削除　95.12.20 BY M.HARADA ********
#if defined(DEU)	/@ ﾄﾞｲﾂ @/
					if( FaxTelOffHookFlag == 1 ) {
						/@ リダイアル表示 @/
						MsgFromFaxComToMain.SubMessage1 = FAXCOM_REDIAL;
					}
					else{
						/@ ＬＣＤ表示 アラーム @/
						MsgFromFaxComToMain.SubMessage1 = FAXCOM_ERROR;
					}
#else
********************************************************************************/
					/* ＬＣＤ表示　リダイアル */
					MsgFromFaxComToMain.SubMessage1 = FAXCOM_REDIAL;
/* #endif */
				}
				else {
					/* ＬＣＤ表示　ＬＥＤアラーム */
					MsgFromFaxComToMain.SubMessage1 = FAXCOM_ERROR;
				}
				break;
			case RECEIVEERROR|0x14:
			case RECEIVEERROR|0x21:						/* ｼﾞｬﾝｸﾒｲﾙ受信ｺﾝﾊﾟﾁｴﾗｰ */
			case TRANSMITERROR|0x14:
			case TRANSMITERROR|0x29:					/*	ﾎﾟｰﾘﾝｸﾞﾊﾟｽﾜｰﾄﾞ不一致 */
			case DIALERROR|0x03:
				/* ＬＣＤ表示　リダイアル */
				MsgFromFaxComToMain.SubMessage1 = FAXCOM_REDIAL;
				break;
			default:
				if ((SYS_FaxComType == SYS_AUTO_CALLED) || (SYS_FaxComType == SYS_MANUAL_RX)) {
					if (RxJunkMailFlag == 1) {
						/* ＬＣＤ表示　リダイアル */
						MsgFromFaxComToMain.SubMessage1 = FAXCOM_REDIAL;
					}
					else {
						/* ＬＣＤ表示　ＬＥＤアラーム */
						MsgFromFaxComToMain.SubMessage1 = FAXCOM_ERROR;
					}
				}
				else {
					switch(SYS_CurrentExecutingCommand->Status) {
						case SYS_EXEC_WAITING:
						case SYS_EXEC_FORWARD_WAITING:
							/* ＬＣＤ表示　リダイアル */
							MsgFromFaxComToMain.SubMessage1 = FAXCOM_REDIAL;
							break;
						case SYS_EXEC_ERROR:
							/* ＬＣＤ表示　ＬＥＤアラーム */
							MsgFromFaxComToMain.SubMessage1 = FAXCOM_ERROR;
							break;
						default:
							/* ＬＣＤ表示　ＬＥＤアラーム */
							MsgFromFaxComToMain.SubMessage1 = FAXCOM_ERROR;
							break;
					}
				}
				break;
		}
#if (PRO_CONTINUOUS_POLLING == ENABLE)			/* Oct.18.1996	By T.Yamaguchi */
		if (CommandFileOptionItem == SYS_CONTINUOUS_POLLING_RX) {
			switch (FaxComResult&~(ECM_MODE_SET)) {
			case NO_ERROR:
				/* ＬＣＤ表示 ＯＫ */
				MsgFromFaxComToMain.SubMessage1 = FAXCOM_OK;
				break;
			default:
				/* ＬＣＤ表示 ＯＫ	連続ポーリング受信の時はエラーでもＬＣＤはつけない 会話予約はできる */
				MsgFromFaxComToMain.SubMessage1 = FAXCOM_REDIAL;
				break;
			}
		}

 #if (PRO_MODEM == R288F)
		/* モデム不具合はジャーナルにのせない 1996/10/29 */
		if (SYS_FaxComType == SYS_AUTO_CALLED) {
			if (reset_journal == 1) {
				MsgFromFaxComToMain.SubMessage1 = FAXCOM_REDIAL;
			}
		}
 #endif

#endif
		/* 
		** ﾘﾓｰﾄ診断時のエラーはチェックメッセージがでないので、ＬＥＤがつきっぱなしになる
		** 強制的にリダイアルをセットする 1998/04/07  By T.Yamaguchi
		*/
		if (SYS_FaxComType == SYS_REMOTE_DIAG) {
			MsgFromFaxComToMain.SubMessage1 = FAXCOM_REDIAL;
		}

	}

#if (PRO_MODEM == R288F)	/* Add By O.Kimoto 1997/12/02 */
	/* もしCTSがｵﾝしなかったら、ｺﾝﾊﾟﾁｺｰﾄﾞに予期せぬｴﾗｰをｾｯﾄ */ /* 1996/05/17 Y.M */
	if (FaxCompatibleErrorCode == 0) {	/* add if() 1997/04/25 */
		if (MDM_FedOffFlag == 1) {
			FaxCompatibleErrorCode = MDM_CARRIER_OFF1;
			MDM_FedOffFlag = 0;
		}
		else if (MDM_FedOffFlag == 2) {
			FaxCompatibleErrorCode = MDM_CARRIER_OFF2;
			MDM_FedOffFlag = 0;
		}
		else {
			if (FCM_CheckModemAbort()) {
				FaxCompatibleErrorCode = MDM_CTS_ABORT;
			}
		}
	}
#endif
#if (PRO_TX_SPEED == V34) /* H.Kubo 1998/01/29 */
	if (SYS_V34ProcedureExecuting()) {	/* V34交信時 1996/09/03 Y.Murata */
		 FaxComResult |= V34_MODE_SET;				/** 交信結果 */
	}
#endif
	/* 通信エラーモニタをセット */
	FCM_SetFaxComErrorMonitor((UWORD)FaxComResult, (UWORD)MakerCodeRxFlag, (UWORD)0);	/* By M.Tachibana 1997/06/23 */

	SYB_MachineUniqSwitch[UNIQ_SW_H1] &= ~RX_DOC_TO_POLLING_DOC;	/* 代行受信原稿をポーリング原稿にするSWを落とす。Naganoより移植 O.Oshima 2005/02/08 */
}




/*************************************************************************
	module		:[短縮ハンドシェイクの属性を変更する]
	function	:[
		変更条件
		１．交信正常終了をした
		２．相手機がムラタ機である
		３．相手機に短縮ハンドシェイクの機能がある
		４．送信ボーレイトが１．４４Ｋｂｐｓ／９６００ｂｐｓであった
		５．以上の条件がすべてみたされた時属性はセットされる

		また
		６．ワンタッチ／短縮 ダイアルの属性２の 短縮ハンドシェイクが有効に設定されている場合
			１、２．３．４．の条件をすべて満たしていても
			送信したボーレイトが、ワンタッチ／短縮 ダイアルの属性２の 短縮ハンドシェイク・
			ボーレイトと同じでないときは属性は削除される
		また
		７．正常交信しても相手機が他社機なら属性はクリアする
	]
	return		:[]
	common		:[
		SYB_SpeedDial[]					: スピード・ダイアル
		SYB_OnetouchDial[]				: ワンタッチ・ダイアル
		SYB_2ndSpeedDial[]				: 第２スピード・ダイアル
		SYB_2ndOnetouchDial[]			: 第２ワンタッチ・ダイアル
		MakerCodeRxFlag					: 自社機フラグ
		PartnerSpeedHandshakeAbility	: 相手機の短縮ハンドシェーク機能の有無フラグ
		TxBaudRate						: 送信ボーレイト
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/28]
	author		:[村田]
*************************************************************************/
void		SpeedHandshakeAttributeChange(void)
{
	if ( !SYS_V34ProcedureExecuting()
#if (PRO_TX_SPEED == V34 ) /* Added by H.Kubo 1997/08/05 */
		&& (CommandFileOptionItem != SYS_POLLING_RX)
 		&& (CommandFileOptionItem != SYS_DB_POLLING_RX)
#endif /* (PRO_TX_SPEED == V34 ) */
 	) {	/** ポーリングでない */
#if(PRO_SPEED_EX == ENABLE)			/* Add By t.yamaguchi 95.12.04 */
		if ((MakerCodeRxFlag == 1) && (SpeedHandshakeRomCheck() == TRUE)			  /* 96/06/06 (CHK_SpeedHandshake() != 0) */
		&& (((PartnerSpeedHandshakeAbility == 1) && (CHK_UNI_SpeedHandshakeEx() == 0) && (AD_Result == AD_OK_DSE))
		|| ((PartnerSpeedHandshakeExAbility == 1) && (CHK_UNI_SpeedHandshakeEx() != 0) && (AD_Result == AD_OK_SPD_TONE)))) {	/** 相手機がムラタ機で短縮ハンドシェーク有り */
#else
		if ((MakerCodeRxFlag == 1) && (PartnerSpeedHandshakeAbility == 1) && (AD_Result == AD_OK_DSE)) {	/** 相手機が	ムラタ機で短縮ハンドシェーク有り */
#endif
			if (DialKind == SYS_SPEED_DIAL) {		/** 短縮ダイアル */
				if ( SpeedDialPosition < SYS_SPEED_DIAL_MAX ) {		/** 第２短縮の判別 */
					/*----------------------------*/
					/* 第１短縮ダイアルの属性変更 */
					/*----------------------------*/
					if ((TxBaudRate == BPS14400_V17) ||
						(TxBaudRate == BPS14400_V33)) {	/** 送信ボーレイト14400BPS */
	
						SYB_SpeedDial[SpeedDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_96;
						SYB_SpeedDial[SpeedDialPosition].Attribute4 |= SPEED_HANDSHAKE_144;	/** 短縮ハンドシェーク 送信ボーレイト14400BPS SET */
					}
					else if (TxBaudRate == BPS9600_V29) {	/** 送信ボーレイト9600BPS */
						SYB_SpeedDial[SpeedDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_144;
						SYB_SpeedDial[SpeedDialPosition].Attribute4 |= SPEED_HANDSHAKE_96;		/** 短縮ハンドシェーク 送信ボーレイト9600BPS SET */
					}
				}
			}
			else if (DialKind == SYS_ONETOUCH_DIAL) {	/** ワンタッチ・ダイアル */
				if ((TxBaudRate == BPS14400_V17) ||
					(TxBaudRate == BPS14400_V33)) {	/** 送信ボーレイト14400BPS */
	
					SYB_OnetouchDial[OnetouchDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_96;
					SYB_OnetouchDial[OnetouchDialPosition].Attribute4 |= SPEED_HANDSHAKE_144; /** 短縮ハンドシェーク 送信ボーレイト14400BPS SET */
				}
				else if (TxBaudRate == BPS9600_V29) {	/** 送信ボーレイト9600BPS */
					SYB_OnetouchDial[OnetouchDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_144;
					SYB_OnetouchDial[OnetouchDialPosition].Attribute4 |= SPEED_HANDSHAKE_96;		/** 短縮ハンドシェーク 送信ボーレイト9600BPS SET */
				}
			}

			/*================================================================================*/
			/* 送信したボーレイトが、ワンタッチ／短縮 ダイアルの属性２の 短縮ハンドシェイク・ */
			/* ボーレイトと同じでないときは属性は削除しなければならないのでそれのチェックを	  */
			/* 行う(9600 14.4K は特別処理)													  */
			/*================================================================================*/

			if (((FCM_PtnrChkSpeedHandshake144()) &&
				(TxBaudRate != BPS14400_V17) && (TxBaudRate != BPS14400_V33) && (TxBaudRate != BPS9600_V29))
			|| ((FCM_PtnrChkSpeedHandshake96())
				&& (TxBaudRate != BPS9600_V29) && (TxBaudRate != BPS14400_V17) && (TxBaudRate != BPS14400_V33))) {

				if (DialKind == SYS_SPEED_DIAL) {	/** 短縮ダイアル */
					if ( SpeedDialPosition < SYS_SPEED_DIAL_MAX ) {		/** 第２短縮の判別 */
						SYB_SpeedDial[SpeedDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_96;
						SYB_SpeedDial[SpeedDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_144;
					}
				}
				else if (DialKind == SYS_ONETOUCH_DIAL) {	/** ワンタッチ・ダイアル */
					SYB_OnetouchDial[OnetouchDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_96;
					SYB_OnetouchDial[OnetouchDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_144;
				}
			}
		}
		else {	/* 1995/01/20 正常交信しても相手機が他社機なら属性ｸﾘｱ */
			SpeedHandshakeAttributeDel();
		}
	}
}


/*************************************************************************
	module		:[短縮ハンドシェイクの属性を削除する]
	function	:[
		削除条件
		１．送信エラーである
		２．相手機がムラタ機である
		３．相手機に短縮ハンドシェイク機能があった
		４．ワンタッチ／短縮 ダイアルの属性３の短縮ハンドシェイクが有効であった
															(1.44Kbps/9600bps)
		５．以上の条件をすべて満たしているとき
	]
	return		:[]
	common		:[
		SYB_SpeedDial[]					: スピード・ダイアル
		SYB_OnetouchDial[]				: ワンタッチ・ダイアル
		SYB_2ndSpeedDial[]				: 第２スピード・ダイアル
		SYB_2ndOnetouchDial[]			: 第２ワンタッチ・ダイアル
		MakerCodeRxFlag					: 自社機フラグ
		PartnerSpeedHandshakeAbility	: 相手機の短縮ハンドシェーク機能の有無フラグ
		TxBaudRate						: 送信ボーレイト
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/28]
	author		:[村田]
*************************************************************************/
void		SpeedHandshakeAttributeDel(void)
{
	if (  ( !SYS_V34ProcedureExecuting() )
#if (PRO_TX_SPEED == V34 ) /* Added by H.Kubo 1997/08/05 */
		 && (CommandFileOptionItem != SYS_POLLING_RX)
 		 && (CommandFileOptionItem != SYS_DB_POLLING_RX)
#endif /* (PRO_TX_SPEED == V34 ) */ /* Above #if is hanged by H.Kubo 1997/10/23 */
 	) {	/** ポーリングでない */
		if (DialKind == SYS_SPEED_DIAL) {		/** 短縮ダイアル */

			if ( SpeedDialPosition < SYS_SPEED_DIAL_MAX ) {		/** 第２短縮の判別 */
				/*----------------------*/
				/* 第１短縮ダイアル属性 */
				/*----------------------*/
				if (SYB_SpeedDial[SpeedDialPosition].Attribute4 & SPEED_HANDSHAKE_144) {	/** 短縮ハンドシェーク １．４４Ｋ */
					SYB_SpeedDial[SpeedDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_144;		/** 属性クリア */
				}
				else if (SYB_SpeedDial[SpeedDialPosition].Attribute4 & SPEED_HANDSHAKE_96) {	/** 短縮ハンドシェーク ９６００ */
					SYB_SpeedDial[SpeedDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_96;			/** 属性クリア */
				}
			}
		}
		else if (DialKind == SYS_ONETOUCH_DIAL) {		/** ワンタッチ・ダイアル */
			if (SYB_OnetouchDial[OnetouchDialPosition].Attribute4 & SPEED_HANDSHAKE_144) {	/** 短縮ハンドシェーク １．４４Ｋ */
				SYB_OnetouchDial[OnetouchDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_144;		/** 属性クリア */
			}
			else if (SYB_OnetouchDial[OnetouchDialPosition].Attribute4 & SPEED_HANDSHAKE_96) {	/** 短縮ハンドシェーク ９６００ */
				SYB_OnetouchDial[OnetouchDialPosition].Attribute4 &= ~SPEED_HANDSHAKE_96;			/** 属性クリア */
			}
		}
	} 	/* end of if ((SYS_V34ProcedureExecuting() == 0) &&
		*				(CommandFileOptionItem != SYS_POLLING_RX) &&
 		*				(CommandFileOptionItem != SYS_DB_POLLING_RX)) 
 		*/
}

/*-----------------------------------------------------------------------------------------*/
/* リダイアル・チェックメッセージのプリント												   */
/*																						   */
/*	 １）コマンド通信																	   */
/*		   ダイアルエラー  ダイアル前 D.0.1 LOCAL_BUSY		  --> リダイアル			   */
/*									  D.0.8 NO_DIAL_TGONE	  --> リダイアル			   */
/*						   ダイアル時 D.0.3 STOP SWITCH		  --> 正常終了				   */
/*									  D.0.6 DIAL_EMPTY		  --> チェックメッセージ	   */
/*						   ダイアル後 D.0.2 REMOTE_BUSY		  --> リダイアル			   */
/*									  D.0.7 TIME_OVER		  --> リダイアル			   */
/*									  D.0.9 NO_CURRENT_LOOP	  --> リダイアル			   */
/*																						   */
/*		   送信エラー  T.1.4 ﾊﾝﾄﾞｼｪｰｸ中に停止ﾎﾞﾀﾝ			  --> 正常終了				   */
/*					   T.4.1 MCF/RTN/RTP/PIP/PINを受信しない  --> スキャナ送信時		   */
/*					   T.4.4 送信原稿が残っている時に				チェックメッセージ	   */
/*							 PIP/PINを受信し連送中断			  メモリ送信時			   */
/*																	 B:8-4 ON  ﾘﾀﾞｲｱﾙ	   */
/*																	 B:8-4 OFF ﾁｪｯｸﾒｯｾｰｼﾞ  */
/*					   T.1.1 T1ﾀｲﾑｵｰﾊﾞｰ						  --> １枚以上送信			   */
/*																	 ｽｷｬﾅTx ﾁｪｯｸﾒｯｾｰｼﾞ	   */
/*																	 ﾒﾓﾘTx	ﾘﾀﾞｲｱﾙ		   */
/*																  ０枚送信				   */
/*																	 ﾁｪｯｸﾒｯｾｰｼﾞ			   */
/*					   上記送信エラー以外					  --> チェックメッセージ	   */
/*																						   */
/*		   受信エラー  ﾎﾟｰﾘﾝｸﾞ受信でR.1.4以外				  --> チェックメッセージ	   */
/*					   ﾎﾟｰﾘﾝｸﾞ受信でR.1.4 or 受領証時ｴﾗｰ	  --> 正常終了				   */
/*																						   */
/*	 ２）手動送信																		   */
/*					   T.1.4								  --> 正常終了				   */
/*					   T.1.4 以外							  --> I:0-0 ON	ﾁｪｯｸﾒｯｾｰｼﾞ	   */
/*																  I:0-0 OFF ｴﾗｰ表示のみ	   */
/*	 ３）自動受信																		   */
/*					   全エラー								  --> 表示のみ				   */
/*	 ４）手動受信																		   */
/*					   T.1.4 or R1.4						  --> 正常終了				   */
/*					   T.1.4 or R.1.4 以外					  --> I:0-0 ON	ﾁｪｯｸﾒｯｾｰｼﾞ	   */
/*																  I:0-0 OFF ｴﾗｰ表示のみ	   */
/*	 ５）リモートＦＡＸ送信																   */
/*					   T.1.4								  --> 正常終了				   */
/*					   T.1.4 以外							  --> I:0-0 ON	ﾁｪｯｸﾒｯｾｰｼﾞ	   */
/*																  I:0-0 OFF ｴﾗｰ表示のみ	   */
/*																						   */
/*	 ６）メモリ送信原稿蓄積時メモリオーバー												   */
/*															  --> I:3-0 ON	ﾁｪｯｸﾒｯｾｰｼﾞC	   */
/*																  I:3-0 OFF ｴﾗｰ表示のみ	   */
/*-----------------------------------------------------------------------------------------*/


#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
/*************************************************************************
	module		:[フラッシュＲＯＭ書き込み中にエラーが起こったときの処理]
	function	:[
		１．フラッシュ書き込みステータスをクリア
		２．スキャナ／プリンタのマシンステータスをクリア
		３．書き込みに使ったＤＲＡＭをクリア
	]
	return		:[]
	common		:[
		SYB_FlashROM_WriteStatus
		SYS_MachineStatus[SYS_RESOURCE_STATUS]
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1998/04/07]
	author		:[山口]
*************************************************************************/
void	FlashRomWriteAfterCheck(UBYTE error)
{
#if (0) /* デバッグ用 */
//	UWORD *address;		/* デバッグ T.Nose */
//	address = (UBYTE *)ROM_DATA_WRITE_ADDRESS;
#endif

	if (error == 1) {
		SYB_FlashROM_WriteStatus = NO_STATUS;
		/* InitializeDRAM_Parameter(); */
		FLA_ClearSumROMData(); /* ROMイメージデータのチェックサムクリア */
		FLA_ClearModelROMData(); /* ROMイメージデータのモデル名クリア */
		MEM_ClearAll();	/** Initialize Memory Control Table */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY | SYS_PRINTER_BUSY);
	}
	else {
		SYB_FlashROM_WriteStatus = ROM_DATA_RECEIVED;
#if (0) /* デバッグ用 */
//		if (SYB_MaintenanceSwitch[MNT_SW_E2] & 0x04) {
//			SYB_ROM_DataSumcheck = 0xffff;		/* 強制的にサムチェックエラーにする */
//		}
//		if (SYB_MaintenanceSwitch[MNT_SW_E2] & 0x08) {
//			*address -= 1; /* 強制的にモデル名エラーにする "V930 " → "V830 " */
//			SYB_ROM_DataSumcheck -= 1; /* サムチェックをあわせる */
//		}
#endif
		CML_RelayOff();					/** ＣＭＬリレー OFF */
		/* ここでリセットに飛ばす */
		RestartSystem();
	}
}
#endif

#if (PRO_SGP_TEST_ROM == ENABLE) /** By S.Wang 98/07/25 */

#if 0  
void SetSgpPerformanceData(void)
{
	struct SYS_PerformanceData_t *Report;
	
		if ( ++SYB_NumberTotalCount > 99999 ) {				/** 送信通番が99999を越えた */
		SYB_NumberTotalCount = 1;				/** 送信通番１セット */
	}
	SYB_NumberTotalCount ++;
	Report = &SYB_PerformanceFile[SYB_AutoSgpReportCounter];		/** ポインタセット */
	/* 各メンバー初期化 */
	
	/* 通番 */
	Report->number = SYB_NumberTotalCount;
	/* ①ダイアル番号 */
	CMN_StringCopyNum(&Report->RemoteID, &SYS_DialingNumber.Buffer[0], 20);
	/* ②メーカーコード */
	Report->maker = CMN_MSB_LSB_Invert(MDM_ModemBuffer[NonStdFrmPos][MAKERCODE_POS]);
	/* ③モデム能力 */
	Report->Baudrate = BaudRate();
	/* ④符号化方式 */
	Report->Code = CodingMethod();
	/* ⑤記録幅 */
	Report->Size = PaperWidth();
	/* ⑥最小電送時間 */
	Report->ScanningTime = MinimumCommunicationTime();
	/* ⑦受信線密度 */
	Report->Mode = ReceiveModeAbility();
	/* ⑧ＥＣＭの有無 */
	Report->EcmMode = ECMAbilityCheck();
	/* ⑨結果 */
	Report->Result = ResultCheck();
	
	++SYB_AutoSgpReportCounter; /** レポート書き込みポイント更新 */
	if ( ++SYB_AutoSgpReportCounter >= SYS_SGP_REPORT_MAX ) {	    /** 記録位置を更新し最大数を越えた */
		SYB_AutoSgpReportCounter = 0;								/** 記録位置を初期化 */
	}
	
void SetSgpDialingData(void)
{
	struct SYS_PerformanceData_t *Report;
	
	Report = &SYB_PerformanceFile[SYB_NumberTotalCount];		/** ポインタセット */
	
	if ( ++SYB_NumberTotalCount > 99999 ) {				/** 送信通番が99999を越えた */
		SYB_NumberTotalCount = 1;				/** 送信通番１セット */
	}
	SYB_NumberTotalCount ++;
	Report->number = SYB_NumberTotalCount;
	CMN_StringCopyNum(&Report->RemoteID, &SYS_DialingNumber.Buffer[0], 20);
	Report->Result = FaxComResult;
}

UBYTE BaudRate(void)
{
	#define PER_MODEM_BAUDRATE_V8		1
	#define PER_MODEM_BAUDRATE_V17		2
	#define PER_MODEM_BAUDRATE_V33		3
	#define PER_MODEM_BAUDRATE_V29		4
	#define PER_MODEM_BAUDRATE_V27		5

	UBYTE baud;
	baud = 0;
	if (MDM_ModemBuffer[StdFrmPos][3] & 0x20) {	/* Recommendation V8 capabilities ON ? */
		baud = PER_MODEM_BAUDRATE_V8;
	}
	else {
		switch (MDM_ModemBuffer[StdFrmPos][4] & MASK_BAUDRATE) {	/**	DIS/DTC FIF ボーレートビットチェック	*/
		case CCITT_V17_BIT:/**	V17ビット	*/
			baud = PER_MODEM_BAUDRATE_V17;
			break;
		case CCITT_V33_BIT:	/**	V33ビット	*/
			baud = PER_MODEM_BAUDRATE_V33;
			break;
		default:
			switch(MDM_ModemBuffer[StdFrmPos][4] & CCITT_V29_BIT) {
			case CCITT_V29_BIT:	/**	V29ビット	*/
			case CCITT_V29ONLY_BIT:	/**	V29Onlyビット	*/
				baud = PER_MODEM_BAUDRATE_V29;
				break;
			case CCITT_V27_BIT:	/**	V27ビット	*/
			case CCITT_V27F_BIT:	/**	V27フォールバックビット	*/
				baud = PER_MODEM_BAUDRATE_V27;
				break;
			default:
				break;
			}
			break;
		}
	}
	return(baud);
}

UBYTE CodingMethod(void)
{
	#define PER_CODE_MH			1
	#define PER_CODE_MR			2
	#define PER_CODE_MMR		3
	#define PER_CODE_JBIG		4

	UBYTE	code;
	code = 0;

	if (MDM_ModemBuffer[StdFrmPos][4] & SET_MR_BIT) {	/**	DIS/DCS FIF MRビット ON	*/
		code = PER_CODE_MR;
	}
	else {
		code = PER_CODE_MH;
	}
	if ((RxStandardFrameByteCount > 6) &&
		(MDM_ModemBuffer[StdFrmPos][6] & SET_MMR_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT)) {	/**	 DIS/DTC FIF MMRビット ON	*/

		code = PER_CODE_MMR;
	}
	if ((RxStandardFrameByteCount > 12)
	&& (MDM_ModemBuffer[StdFrmPos][12] & JBIG_BIT)
	&& (MDM_ModemBuffer[StdFrmPos][11] & EXPAND_FIELD_BIT)) {	/**	 DIS/DTC FIF JBIGビット ON

		code = PER_CODE_JBIG;
	}
	return(code);
}

UBYTE PaperWidth(void)
{
	#define PER_SIZE_A4		1
	#define PER_SIZE_B4		2
	#define PER_SIZE_A3		3

	UBYTE	size;
	size = 0;

	switch (MDM_ModemBuffer[StdFrmPos][5] & RX_ALL_PAPER_BIT) {		/**	ＤＩＳ／ＤＴＣ 記録幅ビットチェック	*/
	case RX_A4_PAPER_BIT:	/**	記録紙A4	*/
		size = PER_SIZE_A4;
		break;
	case RX_B4_PAPER_BIT:	/**	記録紙B4	*/
		size = PER_SIZE_B4;
		break;
	case RX_A3_PAPER_BIT:	/**	記録紙A3	*/
	case RX_ALL_PAPER_BIT:	/**	A4、B4,A3	*/
		size = PER_SIZE_A3;
		break;
	default:
		break;
	}
	return(size);
}

UBYTE MinimumCommunicationTime(void)
{
	#define PER_SCAN_TIME40		1
	#define PER_SCAN_TIME20		2
	#define PER_SCAN_TIME10		3
	#define PER_SCAN_TIME5		4
	#define PER_SCAN_TIME0		5

	UBYTE time;
	time = 0;

	switch (MDM_ModemBuffer[StdFrmPos][5] & MASK_MINIMUM_SCANNING_TIME) {		/**	DIS/DTC FIF 最少伝送時間ビットチェック	*/
	case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
		time = PER_SCAN_TIME0;
		break;
	case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
		time = PER_SCAN_TIME10;
		break;
	case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
		time = PER_SCAN_TIME20;
		break;
	case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
		time = PER_SCAN_TIME40;
		break;
	case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
		time = PER_SCAN_TIME5;
		break;
	case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
		time = PER_SCAN_TIME10;
		break;
	case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
		time = PER_SCAN_TIME20;
		break;
	case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
		time = PER_SCAN_TIME40;
		break;
	default:
		break;
	}
	return(time);
}


UBYTE ReceiveModeAbility(void)
{
	#define PER_MODE_NORMAL		1		/* 200-100 */
	#define PER_MODE_FINE		2		/* 200-200 */
	#define PER_MODE_S_FINE		3		/* 200-400 */
	#define PER_MODE_O_FINE		4		/* 300-300 */
	#define PER_MODE_H_FINE		5		/* 400-400 */

	UBYTE	mode;
	mode = 0;

	if (RxStdFrame_FineBitCheck()) {
		mode = PER_MODE_FINE;
	}
	else {
		mode = PER_MODE_NORMAL;
	}
	if (RxStdFrame_SuperFineBitCheck()) {
		mode = PER_MODE_S_FINE;
	}
	if (RxStdFrame_OtherFineBitCheck()) {
		mode = PER_MODE_O_FINE;
	}
	if (RxStdFrame_HyperFineBitCheck()) {
		mode = PER_MODE_H_FINE;
	}
	return(mode);
}


UBYTE ECMAbilityCheck(void)
{
	UBYTE	ecm_mode;

	if (RxStdFrame_ECMAbilityCheck()) {
		ecm_mode = 1;
	}
	else {
		ecm_mode = 0;
	}
	return(ecm_mode);
}


UBYTE ResultCheck(void)
{
	UWORD	result;
	result = 0;

	if ((FaxComResult & 0x0C00) == DIALERROR) {
		result = FaxComResult;
	}
	else {
		result = 0;
	}
	return(result);
}
#endif /** #if 0 */
#endif
