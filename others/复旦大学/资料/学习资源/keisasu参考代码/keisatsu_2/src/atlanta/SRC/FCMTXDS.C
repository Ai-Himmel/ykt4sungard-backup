/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMTXDS.C												 */
/*	モジュール	 :															 */
/*				 : ResetTxPageFinishStatus()								 */
/*				 : CheckRCR_Request()										 */
/*				 : CheckNextDB_File()										 */
/*				 : CompareTxMode()											 */
/*				 : MemorizeTxErrorPage()									 */
/*				 : UpdateTxPageInformation()								 */
/*				 : FallBackByRTN()											 */
/*				 : FallBackByPPR()											 */
/*				 : CheckErrorPage()											 */
/*				 : CheckAllErrorPage()										 */
/*				 : TxCommandAndRxResponse()									 */
/*	作成者		 : 山口														 */
/*	日	付		 :	1996/11/19												 */
/*	概	要		 :															 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\syslocal.h"
#include	"\src\atlanta\define\syst30.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\mem_def.h"

#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mntsw_b.h"	/* 96/07/29 add By T.Yamaguchi */

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\fcm_data.h"

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
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1998/01/19 */
#include	"\src\atlanta\ext_v\lst_data.h"
#endif

#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1998/01/19 */
 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
	#include "\src\atlanta\ext_v\cdc_data.h"
 #endif
#endif
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
 #endif
#endif

#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/12/18 */
/* POPLAR_H では、コードサイズを小さくする最適化コンパイルをしますが、
** そのままだと大量のスタックを消費します。そこで以下の #pragma によって
** 関数先頭での不要なレジスタ待避をさけます。
** 呼出し元で、#pragma noregalloc を宣言していることを確認してください。
** (SuperH RISC engine ファミリ C コンパイラ編 2-34 参照)
** 1997/12/18 H.Kubo 
*/
#pragma noregalloc(TxCommandAndRxResponse)
#endif /* (PRO_MODEM == R288F) */


/*************************************************************************
	module		:[送信フェーズＣの結果を再セット]
	function	:[
		1.	送信フェーズＣでの画データ送信結果が「送信完了」および，
		.	「１ページ終了」の場合に，次ページの有無などを確認する
		2.	次ページによって，以下の状態にセットする
		.	1)	送信完了
		.	2)	送信終了，受領証要求あり
		.	3)	１ページ終了
		.	4)	１ページ終了，モード変更あり
		3.	「送信完了」，「１ページ終了」以外の場合はそのままリターン
	]
	return		:[
		画データ送信結果(\src\atlanta\define\mdm_def.h)
		TX_PAGE_END					:１ページ送信完了
		TX_BLOCK_END				:64KByte送信完了
		TX_STOPPED					:停止スイッチＯＮ
		TX_DOC_ERR					:原稿繰り込み不良
		TX_LAMP_ERR					:ランプエラー
		TX_FILE_ERR					:該当するメモリファイルが存在しない
		TX_MEM_ERR					:画像メモリ画品質不良
		TX_1M_OVER					:スキャナ送信が１ｍを越えた
		TX_SEPARATE					:Ｆ網設定時，送信がＡ４原稿２枚分に達した
		TX_END						:全ページ送信終了
		TX_PAGE_END_MODE_CHANGE		:１ページ送信終了，モード変更あり
		TX_PAGE_END_RCR				:１ページ送信終了，受領証要求あり
	]
	common		:[
		TxPageFinishStatus		TxSmType			FaxComType
		SYS_FaxComTxType		TxModeChangedFlag	SYS_TxTotalPage
		CommandFilePage		:指定送信ページ数
	]
	condition	:[
		次ページの有無は，画データ送信終了後に送信フェーズＣでチェック済みとする
	]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/20]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE		ResetTxPageFinishStatus( void )
{
	/**	送信モード変更フラグをクリア	*/
	TxModeChangedFlag = 0;
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
if (ROM_SW_SpecialDoctorReport) {

#if (0)
** 		/* 医師会特ＲＯＭで、通常の送信が出来ない不具合修正 CSH-004-D86-001 by O.Kimoto 1999/10/16 */
** 		/* 医師会特ＲＯＭは、専用メッセージを送信すればそれで送信終了とする。*/
** 		if ((CommandFileTitleMessage & 0xf0) != 0x00) {
** 			return (TX_END);
** 		}
#else
		if ((CommandFileTitleMessage == 0x11) || (CommandFileTitleMessage == 0x21)) {
			return (TX_END);
		}
#endif

}
 #endif
#endif

	switch (TxPageFinishStatus) {	/**	画データ送信結果	*/

	/*------------------*/
	/*	１ページ終了	*/
	/*------------------*/
	case	TX_PAGE_END:	/**	１ページ終了	*/
		CompareTxMode();		/**	送信モードの変更をチェック	*/
		if ((SYS_FaxComType == SYS_COMMAND_EXECUTE)
		&&	(SYS_FaxComTxType == SYS_SCANNER_TRANSMIT)) {	/**	自動送信&&スキャナ送信	*/
			if (TxSmType == TX_CVR) {		/**	カバーページ	*/
				if (TxModeChangedFlag == 1) {		/**	モード変更あり	*/
					/**	「１ページ終了，モード変更あり」をリターン	*/
					return (TX_PAGE_END_MODE_CHANGE);
				}
				/**	「１ページ終了」をリターン	*/
				return (TX_PAGE_END);
			}
			if (CommandFilePage != 0) {		/**	原稿枚数指定あり	*/
				if (SYS_TxTotalPage+1 >= CommandFilePage) {	/**	送信ページ数≧指定ページ数	*/
					if (CheckRCR_Request() == 1) {	/**	受領証要求あり	*/
						/**	「送信終了，受領証要求あり」をリターン	*/
						return (TX_PAGE_END_RCR);
					}
					/**	「送信完了」をリターン	*/
					return (TX_END);
				}
				else {		/**	送信ページの残りあり	*/
					if (TxModeChangedFlag == 1) {	/**	モード変更あり	*/
						/**	「１ページ終了，モード変更あり」をリターン	*/
						return (TX_PAGE_END_MODE_CHANGE);
					}
					/**	「１ページ終了」をリターン	*/
					return (TX_PAGE_END);
				}
			}
			else {
				if (TxModeChangedFlag) {		/**	モード変更あり	*/
					/**	「１ページ終了，モード変更あり」をリターン	*/
					return (TX_PAGE_END_MODE_CHANGE);
				}
				/**	「１ページ終了」をリターン	*/
				return (TX_PAGE_END);
			}
		}
		else {		/**	メモリ送信||手動送信	*/
			if (TxModeChangedFlag == 1) {		/**	モード変更あり	*/
				/**	「１ページ終了，モード変更あり」をリターン	*/
				return (TX_PAGE_END_MODE_CHANGE);
			}
			/**	「１ページ終了」をリターン	*/
			return (TX_PAGE_END);
		}
		break;

	/*------------------------------------*/
	/* １ファイル送信終了、次ファイルあり */
	/*------------------------------------*/
	case TX_NEXT_FILE:	/* 追加 1997/05/12  By T.Yamaguchi */
		CompareTxMode();		/**	送信モードの変更をチェック	*/
		if (TxModeChangedFlag == 1) {		/**	モード変更あり	*/
			/**	「１ページ終了，モード変更あり」をリターン	*/
			return (TX_PAGE_END_MODE_CHANGE);
		}
		else {
			/**	「１ページ終了」をリターン	*/
			return (TX_PAGE_END);
		}
		break;
	

	/*--------------*/
	/*	送信完了	*/
	/*--------------*/
	case	TX_END:			/**	送信完了	*/
		/*----------*/
		/*	受領証	*/
		/*----------*/
		if (TxSmType == TX_RCR) {		/**	原稿タイプが受領証	*/
			/**	そのまま（送信完了）リターン	*/
			return (TX_END);
		}
#if (PRO_REMOTE_FAX == ENABLE)	/* Jun.24.1994 */
		/*------------------------------------------------------------------*/
		/*	リモートＦＡＸメモリオーバーチェックメッセージ送信に切り替える	*/
		/*------------------------------------------------------------------*/
		if ((TxMemoryFileItem == SYS_MEM_REMOTE_TX_FILE)
		&&	(SYS_RemoteFaxMemoryOverFlag == 1)
		&&	(TxRemoteFaxCheckMsgFlag == 0)) {	/**	リモートＦＡＸ送信&&メモリオーバーしていた	*/
			/**	次にリモートＦＡＸチェックメッセージを送信するので	**
			***	フラグをセットして，「１ページ終了」をリターン		*/
			TxRemoteFaxCheckMsgFlag = 1;
			return (TX_PAGE_END);
		}
#endif
		/*----------------------*/
		/*	自動スキャナ送信	*/
		/*----------------------*/
		if ((SYS_FaxComType == SYS_COMMAND_EXECUTE)
		&&	(SYS_FaxComTxType == SYS_SCANNER_TRANSMIT)) {	/**	自動送信&&スキャナ送信	*/
			if (CommandFilePage != 0) {						/**	原稿枚数指定あり	*/
				/*--------------------------*/
				/*	指定ページ分を送信終了	*/
				/*--------------------------*/
				if (SYS_TxTotalPage+1 == CommandFilePage) {	/**	送信ページ数＝指定ページ数	*/
					if (CheckRCR_Request() == 1) {			/**	受領証要求あり	*/
						/**	「送信終了，受領証要求あり」をリターン	*/
						return (TX_PAGE_END_RCR);
					}
					/**	「送信完了」をリターン	*/
					return (TX_END);
				}
				/*------------------------------------------------------*/
				/*	指定ページ数に達していないのにＡＤＦに次原稿がない	*/
				/*------------------------------------------------------*/
				if (SYS_TxTotalPage+1 < CommandFilePage) {	/**	送信ページ数＜指定ページ数	*/
					TransmitError( 0x12, 0 );			/**	Ｔ．１．２エラーをセット	*/
					if (CheckRCR_Request() == 1) {		/**	受領証要求あり	*/
						/**	「送信終了，受領証要求あり」をリターン	*/
						return (TX_PAGE_END_RCR);
					}
					/**	「送信完了」をリターン	*/
					return (TX_END);
				}
			}
			else {		/**	枚数指定なし	*/
				if (CheckRCR_Request() == 1) {			/**	受領証要求あり	*/
					/**	「送信終了，受領証要求あり」をリターン	*/
					return (TX_PAGE_END_RCR);
				}
				/**	「送信完了」をリターン	*/
				return (TX_END);
			}
		}
		/*--------------------------*/
		/*	メモリ送信，手動送信	*/
		/*--------------------------*/
		else {		/**	メモリ送信||手動送信	*/
			if (CheckNextDB_File() == 1) {		/**	ＤＢ／受信原稿ポーリング送信の次ファイルあり	*/
												/* 一括送信原稿／Ｆコードポーリング原稿 */
				/**	「１ページ終了，モード変更あり」をリターン	*/
				/*------------------------------------------*/
				/*	ＤＢポーリングなどでファイルの境目では	*/
				/*	必ずＥＯＭでモード変更する				*/
				/*------------------------------------------*/
				return (TX_PAGE_END_MODE_CHANGE);
			}
			else {	/**	次ファイルなし||ＤＢポーリング以外	*/
				if (CheckRCR_Request() == 1) {			/**	受領証要求あり	*/
					/**	「送信終了，受領証要求あり」をリターン	*/
					return (TX_PAGE_END_RCR);
				}
				/**	「送信完了」をリターン	*/
				return (TX_END);
			}
		}
		break;

	/*------------------------------------------------------------------*/
	/*	その他															*/
	/*	TX_BLOCK_END	TX_STOPPED		TX_DOC_ERR		TX_LAMP_ERR		*/
	/*	TX_FILE_ERR		TX_MEM_ERR		TX_1M_OVER		TX_SEPARATE		*/
	/*------------------------------------------------------------------*/
	default:				/**	その他の場合	*/
		/**	そのままリターン	*/
		return (TxPageFinishStatus);
		break;
	}
}


/*************************************************************************
	module		:[自機の受領証要求を確認]
	function	:[
		自機の「受領証」要求状況と相手機の「受領証発行」能力を確認する
		1.	自動送信の場合は，コマンドファイルの「受領証要求」を確認する
		2.	手動送信の場合は，「通信証キー」と「送信証／受領証」の現在の
		.	設定状況を確認する
	]
	return		:[
		1		受領証要求する
		0		受領証要求しない
	]
	common		:[
		FaxComType		SYS_RxReceiptRequestFlag
		SYB_LocalStatus		:現在の受領証要求状況(0 & SYS_CONFIRM_ON)
	]
	condition	:[]
	comment		:[
		コマンドファイルの展開とコンパチチェックでフラグ(SYS_RxReceiptRequestFlag)
		がセットされる
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/02/16]
	author		:[竹内茂樹]
*************************************************************************/
BYTE		CheckRCR_Request( void )
{
	/*--------------*/
	/*	自動送信	*/
	/*--------------*/
	if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {	/**	自動送信	*/
		if (SYS_RxReceiptRequestFlag == 1) {		/**	自機の「受領証」要求ありで相手機に「発行能力」あり	*/
			return (1);		/**	「受領証要求する」でリターン	*/
		}
		else {
			return (0);		/**	「受領証要求しない」でリターン	*/
		}
	}
	/*--------------*/
	/*	手動送信	*/
	/*--------------*/
	else if (SYS_FaxComType == SYS_MANUAL_TX) {	/**	手動送信	*/
		if (SYS_RxReceiptRequestFlag == 1) {	/**	自機の「受領証」要求ありで相手機に「発行能力」あり	**/
			return (1);		/**	「受領証要求する」でリターン	*/
		}
		else {
			return (0);		/**	「受領証要求しない」でリターン	*/
		}
	}

	/*------------------*/
	/*	その他の通信	*/
	/*------------------*/
	SYS_RxReceiptRequestFlag = 0;
	return (0);		/**	「受領証要求しない」でリターン	*/
}


/*************************************************************************
	module		:[ポーリング送信の次ファイル確認]
	function	:[
		ＤＢポーリング送信または受信原稿ポーリング送信で，次ファイル指定の有無をチェックする
	]
	return		:[
		1	:次ファイルあり
		0	:次ファイルなし，またはＤＢポーリング以外
	]
	common		:[
		TxMemoryFileItem	TxMemoryFileNo
		TxMemoryFileCurrentExecutingNo
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/17]
	author		:[竹内茂樹]
*************************************************************************/
BYTE		CheckNextDB_File( void )
{
	if ((TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE)
	||	((TxMemoryFileItem >= SYS_MEM_BATCH_TX_FILE1) && (TxMemoryFileItem <= SYS_MEM_BATCH_TX_FILE5))
	||	(RxDocumentPollingTxFlag != 0)) {		/**	ＤＢポーリング送信||バッチ送信||受信原稿ポーリング送信	*/
		/* ↑バッチ送信の条件を追加 Aug.20.1994 */
		if (TxMemoryFileNo[TxMemoryFileCurrentExecutingNo+1] != 0xffff) {	/**	最終ファイルではない	*/
			return (1);		/**	次ファイルありをリターン	*/
		}
	}
#if (PRO_F_CODE == ENABLE)
	else if ((TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)	/* 掲示板ﾎﾟｰﾘﾝｸﾞ原稿 */
	 || (TxMemoryFileItem == SYS_MEM_SUB_SECURE_FILE)) {	/* Fｺｰﾄﾞ親展ﾎﾟｰﾘﾝｸﾞ原稿 */
		if (TxMemoryFileNo[TxMemoryFileCurrentExecutingNo+1] != 0xffff) {	/**	最終ファイルではない	*/
			if (!(SYB_MaintenanceSwitch[MNT_SW_B4] & FCODE_POLLING_TX_METHOD)){	/* ﾒﾝﾃﾅﾝｽSWB4-2 */
				return (0);		/**	次ファイルなしをリターン	*/
			}
			else {	/* ﾒﾝﾃﾅﾝｽSWB4-2 */
				return (1);		/**	次ファイルありをリターン	*/
			}
		}
	}
#endif
	return (0);		/**	次ファイルなしをリターン	*/
}


/*************************************************************************
	module		:[送信モードの変更をチェック]
	function	:[
		1.	今送信した原稿のモード／サイズを，次ページと比較し，
		.	違えばモード変更フラグをセットする
		2.	原稿制御ブロックのモード／サイズを，次ページの情報に更新する
	]
	return		:[]
	common		:[
		TxSmType		TxMemoryFilePage
		TxMode				:ＤＣＳで指定した原稿のモード
		FirstTxMode			:今送信したページの原稿モード
		DocWidth			:今送信したページの原稿サイズ
		TxModeChangedFlag	:モード変更フラグ
		SYS_DocBlock		:送信ページの原稿モード(.Src.Mode)/原稿サイズ(.Src.Size)
	]
	condition	:[
		必ず次ページがあること
	]
	comment		:[
		FirstTxMode		「今送信したモード」から「次ページのモード」に変わる GrayModeFlag を ON するためちょっと変更した。鈴木
		DocWidth		「今送信したサイズ」から「次ページのサイズ」に変わる
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[竹内茂樹]
*************************************************************************/
void		CompareTxMode( void )
{
	UWORD			file_page;				/**	次ページのファイルナンバー	*/
	UBYTE	next_mode, next_size;	/**	次ページのモード，幅	*/
	UBYTE gray_flag_on;
	gray_flag_on = 0;
	/**	原稿制御ブロックを次ページの情報に更新	*/
	if (TxSmType == TX_CVR) {
		file_page = TxMemoryFilePage;
	}
#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1998/01/19 */
	else if (TxSmType == TX_RELAYED_TX_REPORT) {
		if (LST_TxPageFinishStatus == TX_PAGE_END) {
			return; /* 蓄積原稿は送らないので、何も更新しない。*/
		}
		else {
#if (PRO_LIST_TX_WITH_IMG == ENABLE) /* 不達通知に蓄積原稿をつける場合 added by H.Kubo 1998/12/16 */
			if (CDC_ReadPageCount > 0) {
				file_page = TxMemoryFilePage + 1;
			}
			else {
				file_page = TxMemoryFilePage;
			}
#else
			file_page = TxMemoryFilePage;
			return; /* 今の仕様では蓄積原稿は送らないので、何も更新しない。*/
			/* 蓄積原稿を送るなら、上の return ははずすべし。 */
#endif
		}
	}
#endif
	else {
		file_page = TxMemoryFilePage + 1;
	}
	if (TxPageFinishStatus == TX_NEXT_FILE) {
		file_page = 1;
	}
	GetNextTxPageData( file_page );

	/**	次ページのモードを取り込む (GRAY??はFINEにする)	*/
	next_mode = SYS_DocBlock.Src.Mode;
	gray_flag_on = next_mode;
	switch (next_mode) {
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
	case	SYS_GRAY128:
	case	SYS_GRAY128_SEP:
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
	case	SYS_HGRAY:		/* ここは通らない筈だが念の為 */
#endif
		/* スキャナ送信 でかつ相手の能力 400DPI ｲﾝﾁ なら H_FINE */
		next_mode = ScanTxGrayMode;
		break;
	default:
		break;
	}

	/**	現ページのモードの SYS_GRAY?? を SYS_FINE にする	*/
	switch (FirstTxMode) {
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
	case	SYS_GRAY128:
	case	SYS_GRAY128_SEP:
		FirstTxMode = ScanTxGrayMode;
		break;
	default:
		break;
	}

	if ((FirstTxMode != next_mode)
	&&	(TxMode != next_mode)) {	/**	(今送信したモード≠次ページのモード)&&(送信モード≠次ページのモード)	*/
		/**	モード変更フラグをセットする	*/
		TxModeChangedFlag = 1;
	}

	/**	次ページのサイズを取り込む	*/
	next_size= SYS_DocBlock.Src.Size;

	if (DocWidth != next_size) {	/**	送信した原稿サイズ≠次ページのサイズ	*/
		/**	モード変更フラグをセットする	*/
		TxModeChangedFlag = 1;
	}

	/**	次ページの原稿モードをセットする	*/
	FirstTxMode = gray_flag_on;/* 中間調表示 Set Gray Too! */
	/**	次ページの原稿サイズをセットする	*/
	DocWidth = next_size;
}


/*************************************************************************
	module		:[エラーページ記憶]
	function	:[
		1.	今送信したページをエラーページとして記憶する
		2.	スキャナ送信は実送信ページ，メモリ送信はファイルページを記憶する
		*.	エラーページはバッファのサイズ内のみ有効
	]
	return		:[]
	common		:[
		SYS_TxTotalPage		TxMemoryFilePage
		TxResponsedRTN_PageSign		:エラーページ番号の記憶バッファ
		SYS_FaxComTxType			:送信種別（メモリ送信／スキャナ送信）
	]
	condition	:[
		否定応答を受信した時にコールする
		（ＲＴＮ，ＰＩＮ，ＥＲＲ）
	]
	comment		:[
		エラーページ記憶バッファはビットで指定
		カバーページでcallされると、１ページ目のビットを立ててしまう 1996/11/22
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/03]
	author		:[竹内茂樹]
*************************************************************************/
void		MemorizeTxErrorPage( void )
{
	UWORD	error_page;
	UWORD	byte_point, bit_point;

	if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {	/**	スキャナ送信	*/
		error_page = SYS_TxTotalPage + 1;
		/*	ＲＴＮを受けたページはまだインクリメントしていない	*/
	}
	else {		/**	メモリ送信	*/
		error_page = TxMemoryFilePage;
	}

	/**	記憶バッファ内の位置計算	*/
	byte_point = (error_page - 1) / 8;
	bit_point  = (error_page - 1) % 8;

	if (byte_point < SYS_ERROR_PAGE) {		/**	バッファのサイズ内	*/
		TxResponsedRTN_PageSign[byte_point] |= (0x01 << bit_point);		/**	ビットを立てる	*/
	}
}


/*************************************************************************
	module		:[送信ページ／ファイルのカウンタ更新]
	function	:[
		1.	送信ページのページカウンタとファイルカウンタを更新する
		.	ただし，カバーページ送信と，リモートＦＡＸチェックメッセージ
		.	では更新しない
		2.	どのカウンタを更新するかは，UpdateTxPageModeで指定する
		.		UPDATE_TOTAL_PAGE	0x01
		.		UPDATE_MEMORY_PAGE	0x02
		.		両方の場合はorでセットする
	]
	return		:[]
	common		:[
		UpdateTxPageMode	SYS_TxTotalPage		TxMemoryFilePage
		SYS_FaxComType
		*SYS_CurrentExecutingCommand	:前回のコマンドでの送信済みページ(初回は０)(->Page)
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/10]
	author		:[竹内茂樹]
*************************************************************************/
void			UpdateTxPageInformation( void )
{
	/*--------------------------------------*/
	/*	直前に送信したページがカバーページ	*/
	/*--------------------------------------*/
	if (TxSmType == TX_CVR) {					/**	カバーページ	*/
		/**	先頭の原稿を送信原稿に指定	*/
		SYS_TxTotalPage = 0;
		if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {		/* 条件追加 '96.04.23 By T.Y */
			TxMemoryFilePage = SYS_CurrentExecutingCommand->Page + 1;
		}
		/*	RTN/PIN自動再送OFFにするとカバーページを延々送ってしまうため追加
		**		1996/11/20 s.takeuchi
		*/
		TxCoverPageFlag = 0;
	}
	/*----------------------------------------------*/
	/*	リモートＦＡＸチェックメッセージを送信した	*/
	/*----------------------------------------------*/
	else if (TxSmType == TX_REMOTE_FAX_MSG) {	/**	リモートＦＡＸチェックメッセージ	*/
		/**	ページ数更新せずにリターン	*/
		return;
	}
	/*--------------*/
	/*	手動送信	*/
	/*--------------*/
	else if (SYS_FaxComType== SYS_MANUAL_TX) {	/**	手動送信	*/
		/**	次の原稿を送信原稿に指定	*/
		SYS_TxTotalPage++;
	}
	/*------------------*/
	/*	各種自動送信	*/
	/*------------------*/
	else {										/**	自動送信	*/
		/* ●ICHOU追加 メモリ送信最適化処理 by T.Soneoka 1996/06/11 */
		/* FCM_EraseTxMemoryDoc();	２回線対応 1997/09/17  By T.Yamaguchi */
		/* ICHOU二回線用(同時実行可能)の送信済メモリ消去 */
		/* 受領証送信時に受信した原稿を消去してしまうため、メモリ送信だけとする  1997/09/18 s.takeuchi */
		if (TxSmType == TX_MEMORY) {
			FCM_EraseTxMemoryPage( SYS_CurrentExecuteNoSave,	/* 実行中のExecQueue番号 */
								&EraseIndexData);		/* 送信中のMemoryのIndex */
		}
		/*--------------------------------------*/
		/*	ポーリング送信，ＤＢポーリング送信	*/
		/*	受信原稿ポーリング送信				*/
		/*--------------------------------------*/
		if ((TxMemoryFileItem == SYS_MEM_POLLING_FILE)
		||	(TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE)
		||	((TxMemoryFileItem >= SYS_MEM_BATCH_TX_FILE1) && (TxMemoryFileItem <= SYS_MEM_BATCH_TX_FILE5))
#if (PRO_F_CODE == ENABLE)
		||	(TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)	/*	掲示板ﾎﾟｰﾘﾝｸﾞ原稿 */
		||	(TxMemoryFileItem == SYS_MEM_SUB_SECURE_FILE)	/* Fｺｰﾄﾞ親展原稿 ﾎﾟｰﾘﾝｸﾞできる場合 */
#endif
		||	(RxDocumentPollingTxFlag != 0)) {		/**	ポーリング送信||ＤＢポーリング送信||受信原稿ポーリング送信	*/
			/* ↑バッチ送信の条件を追加 Aug.20.1994 */
			/*----------------------------------*/
			/*	ポーリングの最終ページでない	*/
			/*----------------------------------*/
			if (TxMemoryFilePage < PollingTxFilePage[TxMemoryFileCurrentExecutingNo]) {	/**	最終ページでない	*/
				/**	送信ページを＋１	*/
				if (UpdateTxPageMode & UPDATE_TOTAL_PAGE) {
					SYS_TxTotalPage++;
					/* 一括送信頁表示、リダイヤル頁指定に使用 94/9/28 Y.Suzuki */
					if((TxMemoryFileItem >= SYS_MEM_BATCH_TX_FILE1) && (TxMemoryFileItem <= SYS_MEM_BATCH_TX_FILE5)) {
						BatchTxFinishPage++;
					}
				}
				/**	送信メモリファイルを＋１	*/
				if (UpdateTxPageMode & UPDATE_MEMORY_PAGE) {
					TxMemoryFilePage++;
				}
			}
			/*--------------------------*/
			/*	ポーリングの最終ページ	*/
			/*--------------------------*/
			else {
				/*--------------------------------------*/
				/*	次の送信ファイルが指定されている	*/
				/*--------------------------------------*/
				if (TxMemoryFileNo[TxMemoryFileCurrentExecutingNo+1] != 0xffff) {	/**	次ファイルあり	*/
					TxMemoryFileCurrentExecutingNo++;	/**	「ファイル番号」格納配列を更新	*/
					/**	送信ページを＋１	*/
					switch (UpdateTxPageMode) {		/**	ページ情報の更新項目	*/
					case	UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE:	/**	両方	*/
						/**	トータルページ数を＋１し，ファイルページを１にする	*/
						TxMemoryFilePage = 1;
						SYS_TxTotalPage++;
						/* 一括送信頁表示、リダイヤル頁指定に使用 94/9/28 Y.Suzuki */
						if((TxMemoryFileItem >= SYS_MEM_BATCH_TX_FILE1) && (TxMemoryFileItem <= SYS_MEM_BATCH_TX_FILE5)) {
							BatchTxFinishPage++;
						}
						break;
					case	UPDATE_MEMORY_PAGE:		/**	送信メモリファイル	*/
						/**	ファイルページを１にする	*/
						TxMemoryFilePage = 1;
						break;
					case	UPDATE_TOTAL_PAGE:		/**	送信ページ数	*/
						SYS_TxTotalPage = 0;
						/* 一括送信頁表示、リダイヤル頁指定に使用 94/9/28 Y.Suzuki */
						if((TxMemoryFileItem >= SYS_MEM_BATCH_TX_FILE1) && (TxMemoryFileItem <= SYS_MEM_BATCH_TX_FILE5)) {
							BatchTxFinishPage = 0;
						}
						break;
					}
					GetNextTxPageData( TxMemoryFilePage );	/**	原稿制御ブロックを次ページのデータに更新	*/
				}
				/*------------------------------*/
				/*	次の送信ファイルがない時	*/
				/*------------------------------*/
				else {
					SYS_TxTotalPage++;
					/* 一括送信頁表示、リダイヤル頁指定に使用 94/9/28 Y.Suzuki */
					if((TxMemoryFileItem >= SYS_MEM_BATCH_TX_FILE1) && (TxMemoryFileItem <= SYS_MEM_BATCH_TX_FILE5)) {
						BatchTxFinishPage++;
					}
				}
			}
		}
		/*------------------------------*/
		/*	ポーリング以外のメモリ送信	*/
		/*------------------------------*/
		else {	/**	その他メモリ送信	*/
			/**	送信ページを＋１	*/
			if (UpdateTxPageMode & UPDATE_TOTAL_PAGE) {
				SYS_TxTotalPage++;
			}
#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1008/01/19 */
 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
			if (UpdateTxPageMode & UPDATE_MEMORY_PAGE) {
				TxMemoryFilePage++;
			}
 #else
			if (TxSmType != TX_RELAYED_TX_REPORT) {
				/**	送信メモリファイルを＋１	*/
				if (UpdateTxPageMode & UPDATE_MEMORY_PAGE) {
					TxMemoryFilePage++;
				}
			}
 #endif
#else
			/**	送信メモリファイルを＋１	*/
			if (UpdateTxPageMode & UPDATE_MEMORY_PAGE) {
				TxMemoryFilePage++;
			}
#endif
		}
	}
}


/*************************************************************************
	module		:[メモリ送信時の送信済みページの判断消去]
	function	:[
		1.	実行中のExecQueueの番号(引数)からExecQueueのポインタを得る
		2.	実行中のメモリIndex(引数)からItemを調べる
		3.	通常送信、ポーリング送信の場合は1ページ目以外を削除する
		4.	同報の場合は同じCommandFileの別のExecQueueが待機中/実行中
		.	ではない場合に1ページ目を除く現在ページまでを削除する
	]
	return		:[]
	common		:[]
	condition	:[
		１ページ（物理ページ）送信し、相手からＭＣＦ等の
		肯定応答を受信したあとに実行する
	]
	comment		:[
		二回線仕様のために大域変数を使わないようにして
		引数で指定して、同時にcallできるように変更
		(外付回線からはdpr_func.c経由でこの関数を実行する)
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/07/25]
	author		:[曽根岡拓/竹内茂樹]
*************************************************************************/
void	FCM_EraseTxMemoryPage(
	UWORD					exec_no,		/* 実行中のExecQueue番号 */
	struct MEM_IndexData_t	*mem_index)		/* 送信中のMemoryのIndex */
{
	struct SYS_ExecQueueData_t	*exec_queue;
	struct SYS_ExecQueueData_t	*work_queue;
	struct MEM_IndexData_t		work_index;
	UWORD						number;

	exec_queue = &SYB_ExecQueue[exec_no];

	/* 代行受信原稿ポーリング取り出し時に、受信原稿が消えてしまう 2004/02/20 Y.Murata */
	if (mem_index->Item == SYS_MEM_RX_FILE) {
		return;
	}

	if (mem_index->Item == SYS_MEM_POLLING_FILE) {
#if (0)	/* ポーリング送信は消さない 1997/09/18 s.takeuchi */
//		if (CHK_DocumentEraseAfterPolling()) {
//			if (mem_index->Page > 1) {	/* １ページ目は消さない */
//				MEM_ClearPage(mem_index);
//			}
//		}
#endif
		return;
	}
	else if (mem_index->Item == SYS_MEM_DB_POLLING_FILE) {
		return;
	}
	else if ((mem_index->Item >= SYS_MEM_BATCH_TX_FILE1)
	&&	(mem_index->Item <= SYS_MEM_BATCH_TX_FILE5)) {
		return;
	}
#if (PRO_F_CODE == ENABLE)
	else if ((mem_index->Item == SYS_MEM_SUB_BULLETIN_FILE)
	    ||   (mem_index->Item == SYS_MEM_SUB_SECURE_FILE)) {	/*	掲示板ﾎﾟｰﾘﾝｸﾞ原稿 */
		return;
	}
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)
	/*-----------------------------------------------------------------
	** ＜SYS_OPTION_PRINTがONのとき＞
	** 送信エラーとなり、中継機でチェックメッセージをプリントするときに
	** このBitが１のときは、すでに中継機で同時プリント済みなので、
	** 従来と同じリスト＋画像１ページ一体型チェックメッセージをプリントする
	** 		→２ページ目以降は送信終了後にメモリ消去します。
	** このBitが０のときは、中継機ではプリントされていないので、
	** リスト・画像分離型チェックメッセージをプリントする。
	** 画像は全ページプリントするものとする。
	** 		→全てのページをメモリ消去しません。
	** 1998/10/01 H.Yoshikawa
	*/
	if (SYB_CommandFile[exec_queue->Number.Command].Ability & SYS_WARP_PRINT) {
		return;
	}
#endif
	else {
		/* 1997/10/10 s.takeuchi  add 1998/03/05  By T.Yamaguchi
		** メモリバックアップされている状態で送信中に電源OFFすると
		** 1ページ目から再送して消去済みページでエラーになるため
		** ExecQueueに送信済みページ数を書き込んでおく
		** ※注意:MEM_Indexしか情報がないのでこれを使う
		*/
		exec_queue->Page = mem_index->Page;
	
		switch (SYB_CommandFile[exec_queue->Number.Command].Option.Item) {	/** 指定されたCommandFileのItem */
		case	SYS_MEMORY_TX:					/**	メモリ送信	*/
		case	SYS_DELAYED_MEMORY_TX:			/**	時刻指定メモリ送信	*/
			if (mem_index->Page > 1) {		/** 1ページ目以外 */
				MEM_ClearPage(mem_index);	/** 現在のページを消去 */
			}
			break;

		/* 同報の場合は他に待ち/実行中のExecQueueがない場合に2ページ目以降を消去する */
		case	SYS_MEMORY_SECURE_TX:			/**	メモリ親展送信	*/
		case	SYS_MEMORY_RELAY_BROADCAST:		/**	メモリ中継指示送信	*/
		case	SYS_DELAYED_BROADCAST:			/**	順次同報送信	*/
		case	SYS_RELAYED_TX:					/**	中継配信	*/
		case    SYS_MEMORY_SUB_ADDRESS_TX:		/**	Ｆｺｰﾄﾞﾒﾓﾘ送信(親展・掲示板に送信） */
			/* ICHOU二回線でのメモリ送信最適化処理を追加  1997/07/24 s.takeuchi
			** 1)二回線仕様では、同時に2つ実行中が存在するので、
			**   同じCommandFileで自分以外のExecQueueが実行/待機中の時は消去しない
			** 2)外付回線からはdpr_func.c経由でこの関数を実行する
			**   (グレープで追加機能として対応)
			** 3)現在の送信ページを消去する時に、それ以前のページ(1ページ目以外)も
			**   IndexTableを検索して消去する
			*/
			for (number = 0; number < SYS_EXEC_QUEUE_MAX; number++) {	/** 全ExecQueue検索 */
				work_queue = &SYB_ExecQueue[number];
				if ((work_queue->Number.Command == exec_queue->Number.Command)
				&&	(exec_no != number)) {		/** 同じCommandFileで違うExecQueueがある */
					if ((work_queue->Status == SYS_EXEC_WAITING)
					||	(work_queue->Status == SYS_EXEC_FORWARD_WAITING)) {	/** 待ちQueueあり */
						break;
					}
					if ((work_queue->Status == SYS_EXEC_EXECUTE)
					||	(work_queue->Status == SYS_EXEC_FORWARD_EXECUTE)) {	/** 実行中Queueあり */
						break;
					}
				}
			}
			if (number >= SYS_EXEC_QUEUE_MAX) {	/** 他に待ち/実行中のQueueなし */
				if (mem_index->Page > 1) {		/** 1ページ目以外 */
					MEM_ClearPage(mem_index);	/** 現在のページを消去 */

					/* 更に、現在ページまでで残っているページをがあれば消去する */
					work_index.Item = mem_index->Item;
					work_index.No = mem_index->No;
					work_index.Page = 2;				/* 2ページ目以降 */
					work_index.BoxNumber = MEM_IGNORE_BOX_NUMBER;
					while (work_index.Page < mem_index->Page) {	/** 現在ページ-1まで */
						if (MEM_CheckIndexNo( &work_index ) != MEM_NO_INDEX) {	/** 残っているページあり */
							MEM_ClearPage( &work_index );	/** 消去 */
						}
						else {
							break;
						}
						work_index.Page++;
					}
				}
			}
			break;
		case	SYS_SCANNER_TX:					/**	スキャナ送信	*/
		case	SYS_DELAYED_SCANNER_TX:			/**	時刻指定スキャナ送信	*/
		case	SYS_SCANNER_SECURE_TX:			/**	スキャナ親展送信	*/
		case	SYS_SCANNER_RELAY_BROADCAST:	/**	スキャナ中継指示送信	*/
		case	SYS_RELAYED_TX_REPORT:			/** 中継配信不達通知 */
		case    SYS_SCANNER_SUB_ADDRESS_TX:  	/**	Ｆｺｰﾄﾞｽｷｬﾅ送信(親展・掲示板に送信） */
		default:
			break;
		}
		return;
	}
}


/* ●ICHOU追加 by T.Soneoka 1996/06/11 */
#if 0	/* FCM_EraseTxMemoryPage()上の関数（２回線対応）に変更 1997/10/01  By T.Yamaguchi	*/
/*************************************************************************
//	module		:[メモリ送信時の送信済みページの消去判断]
//	function	:[
//		コマンドの種別／最終宛先で今送信したページを消去してよいかどうか判断し、
//		消去する場合はフェーズＤに入ったところで覚えていたページに基づいて消去処理を実行します
//	]
//	return		:[
//	]
//	common		:[
//		CommandFileOptionItem, SYS_DocBlock.Index, SYS_ExecQueue[],EraseIndexData
//	]
//	condition	:[
//		１ページ（物理ページ）送信し、相手からＭＣＦ等の肯定応答を受信したあとに実行する
//	]
//	comment		:[]
//	machine		:[V53]
//	language	:[MS-C(Ver.6.0)]
//	keyword		:[FCM]
//	date		:[1996/06/11]
//	author		:[曽根岡拓]
//*************************************************************************/
//void FCM_EraseTxMemoryDoc(void)
//{
//	UWORD	exec_num;
//	
//	if (TxMemoryFileItem == SYS_MEM_POLLING_FILE) {
//#if (0)	/* ポーリング送信は消さない 1997/09/18 s.takeuchi */
//		if (CHK_DocumentEraseAfterPolling()) {
//			if (EraseIndexData.Page > 1) {	/* １ページ目は消さない */
//				MEM_ClearPage(&EraseIndexData);
//			}
//		}
//#endif
//		return;
//	}
//	else if (TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE) {
//		return;
//	}
//	else if ((TxMemoryFileItem >= SYS_MEM_BATCH_TX_FILE1) && (TxMemoryFileItem <= SYS_MEM_BATCH_TX_FILE5)) {
//		return;
//	}
//	/* Ｆコード原稿 */
//	else if ((TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)
//	    ||   (TxMemoryFileItem == SYS_MEM_SUB_SECURE_FILE)) {	/*	掲示板ﾎﾟｰﾘﾝｸﾞ原稿 */
//		return;
//	}
//	else {
//		switch (CommandFileOptionItem) {
//		case SYS_MEMORY_TX:					/**	メモリ送信	*/
//		case SYS_DELAYED_MEMORY_TX:			/**	時刻指定メモリ送信	*/
//			if (EraseIndexData.Page > 1) {	/* １ページ目は消さない */
//				MEM_ClearPage(&EraseIndexData);
//			}
//			break;
//		/* 同報かチェックし、最終宛先の場合、送信したページを消去する */
//		case SYS_MEMORY_SECURE_TX:			/**	メモリ親展送信	*/
//		case SYS_MEMORY_RELAY_BROADCAST:	/**	メモリ中継指示送信	*/
//		case SYS_DELAYED_BROADCAST:			/**	順次同報送信	*/
//		case SYS_RELAYED_TX:				/**	中継配信	*/
//		case SYS_MEMORY_SUB_ADDRESS_TX:		/**	Ｆｺｰﾄﾞﾒﾓﾘ送信(親展・掲示板に送信） */
//			/* 実行待ちの実行ファイルのコマンドファイル番号と、今、実行中の実行ファイルのコマンドファイル番号と同じものを探す */
//			for (exec_num = 0; exec_num < SYS_EXEC_QUEUE_MAX; exec_num++) {
//				if ((SYB_ExecQueue[exec_num].Status == SYS_EXEC_WAITING) ||
//				    (SYB_ExecQueue[exec_num].Status == SYS_EXEC_FORWARD_WAITING)) {
//				    if (SYS_CurrentExecutingCommand->Number.Command == SYB_ExecQueue[exec_num].Number.Command) {
//						break;
//					}
//				}
//			}
//			/* この実行ファイルが最後実行ファイルのときは消去する */
//			if (exec_num >= SYS_EXEC_QUEUE_MAX) {
//				if (EraseIndexData.Page > 1) {	/* １ページ目は消さない */
//					MEM_ClearPage(&EraseIndexData);
//				}
//			}
//			break;
//		case SYS_SCANNER_TX:				/**	スキャナ送信	*/
//		case SYS_DELAYED_SCANNER_TX:		/**	時刻指定スキャナ送信	*/
//		case SYS_SCANNER_SECURE_TX:			/**	スキャナ親展送信	*/
//		case SYS_SCANNER_RELAY_BROADCAST:	/**	スキャナ中継指示送信	*/
//		case SYS_RELAYED_TX_REPORT:			/** 中継配信不達通知 */
//		case SYS_SCANNER_SUB_ADDRESS_TX:	/**	Ｆｺｰﾄﾞｽｷｬﾅ送信(親展・掲示板に送信） */
//		default:
//			break;
//		}
//		return;
//	}
//}
#endif

/*************************************************************************
	module		:[ＲＴＮ受信でのフォールバック]
	function	:[
		画質不良応答(RTN,PIN)を受信した場合にボーレイトを１つ下げる
	]
	return		:[]
	common		:[
		TxBaudRate		AttemptTxBaudRate		AvailableTxBaudRate
	]
	condition	:[
		送信ページが画質不良でＲＴＮ，ＰＩＮを受信した時に実行する
	]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/12]
	author		:[竹内茂樹]
*************************************************************************/
void			FallBackByRTN( void )
{
	switch (TxBaudRate) {
	case	BPS14400_V33:
		AttemptTxBaudRate	= BPS12000_V33;
		AvailableTxBaudRate = BPS12000_V33;
		break;
	case	BPS12000_V33:
		AttemptTxBaudRate	= BPS9600_V29;
		AvailableTxBaudRate = BPS9600_V29;
		break;
	case	BPS14400_V17:
		AttemptTxBaudRate	= BPS12000_V17;
		AvailableTxBaudRate = BPS12000_V17;
		break;
	case	BPS12000_V17:
		AttemptTxBaudRate	= BPS9600_V17;
		AvailableTxBaudRate = BPS9600_V17;
		break;
	case	BPS9600_V17:
		AttemptTxBaudRate	= BPS7200_V17;
		AvailableTxBaudRate = BPS7200_V17;
		break;
	case	BPS9600_V29:
		AttemptTxBaudRate	= BPS7200_V29;
		AvailableTxBaudRate = BPS7200_V29;
		break;
	case	BPS7200_V29:
		AttemptTxBaudRate	= BPS4800_V27;
		AvailableTxBaudRate = BPS4800_V27;
		break;
	case	BPS7200_V17:					/* 変更	 '96.01.10 By t.yamaguchi */
#if defined(DEU)	/* by M.H '97/11/27 順番にﾎﾞｰﾚｰﾄを落とす */
		TxBaudRate			= BPS4800_V27;
		AttemptTxBaudRate	= BPS4800_V27;
		AvailableTxBaudRate = BPS4800_V27;
		break;
#endif
#if defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
		if (CHK_ForeignApprovalDEU()) {	/* DEU bitがOnの時のみ動作する */
			TxBaudRate			= BPS4800_V27;
			AttemptTxBaudRate	= BPS4800_V27;
			AvailableTxBaudRate = BPS4800_V27;
			break;
		}
#endif
	case	BPS4800_V27:
		AttemptTxBaudRate	= BPS2400_V27;
		AvailableTxBaudRate = BPS2400_V27;
		break;
	case	BPS2400_V27:
		AttemptTxBaudRate	= BPS2400_V27;
		AvailableTxBaudRate = BPS2400_V27;
		break;
	default:
		break;
	}
}


/*************************************************************************
	module		:[ＰＰＲ受信でのフォールバック]
	function	:[
		ＰＰＲ応答を受信した場合のボーレイトを１つ下げる
	]
	return		:[]
	common		:[
		TxBaudRate		AttemptTxBaudRate		AvailableTxBaudRate
	]
	condition	:[
		ＰＰＲ応答を設定回数分連続で受信した時に実行する
	]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/12]
	author		:[竹内茂樹]
*************************************************************************/
#if 0 /* V17 ECM 送信中全フレームエラーでフォールバックする場合、V29 にする処理を追加 V17_FALLBACK_PATTERN 2000/1/6 Y.Murata */
**void		FallBackByPPR( void )
#endif

void	FallBackByPPR( UBYTE ecm_all_frame_error_count )
{
	switch (TxBaudRate) {
	case	BPS14400_V33:
		TxBaudRate			= BPS12000_V33;
		AttemptTxBaudRate	= BPS12000_V33;
		AvailableTxBaudRate = BPS12000_V33;
		break;
	case	BPS12000_V33:
		TxBaudRate			= BPS9600_V29;
		AttemptTxBaudRate	= BPS9600_V29;
		AvailableTxBaudRate = BPS9600_V29;
		break;
	case	BPS14400_V17:
#if 0 /* V17 ECM 送信中全フレームエラーでフォールバックする場合、V29 にする処理を追加 V17_FALLBACK_PATTERN 2000/1/6 Y.Murata */
**		TxBaudRate			= BPS12000_V17;
**		AttemptTxBaudRate	= BPS12000_V17;
**		AvailableTxBaudRate = BPS12000_V17;
#endif
		if (CHK_V17FallBackPattern() || (ecm_all_frame_error_count < (BYTE) CHK_UNI_PPR_Count())) {
			TxBaudRate			= BPS12000_V17;
			AttemptTxBaudRate	= BPS12000_V17;
			AvailableTxBaudRate = BPS12000_V17;
		}
		else { /* 全フレームエラーが４回続くと V17 => V29 に変更。 */
			TxBaudRate			= BPS9600_V29;
			AttemptTxBaudRate	= BPS9600_V29;
			AvailableTxBaudRate = BPS9600_V29;
		}
		break;
	case	BPS12000_V17:
#if 0 /* V17 ECM 送信中全フレームエラーでフォールバックする場合、V29 にする処理を追加 V17_FALLBACK_PATTERN 2000/1/6 Y.Murata */
**		TxBaudRate			= BPS9600_V17;
**		AttemptTxBaudRate	= BPS9600_V17;
**		AvailableTxBaudRate = BPS9600_V17;
#endif
		if (CHK_V17FallBackPattern() || (ecm_all_frame_error_count < (BYTE) CHK_UNI_PPR_Count())) {
			TxBaudRate			= BPS9600_V17;
			AttemptTxBaudRate	= BPS9600_V17;
			AvailableTxBaudRate = BPS9600_V17;
		}
		else { /* 全フレームエラーが４回続くと V17 => V29 に変更。 */
			TxBaudRate			= BPS7200_V29; /* 耐ノイズ性能がほぼ同等な V29 7200bps にします。 by H.Kubo 2000/01/05 */
			AttemptTxBaudRate	= BPS7200_V29;
			AvailableTxBaudRate = BPS7200_V29;
		}
		break;
	case	BPS9600_V17:
#if 0 /* V17 ECM 送信中全フレームエラーでフォールバックする場合、V29 にする処理を追加 V17_FALLBACK_PATTERN 2000/1/6 Y.Murata */
**		TxBaudRate			= BPS7200_V17;
**		AttemptTxBaudRate	= BPS7200_V17;
**		AvailableTxBaudRate = BPS7200_V17;
#endif
		if (CHK_V17FallBackPattern() || (ecm_all_frame_error_count < (BYTE) CHK_UNI_PPR_Count())) {
			TxBaudRate			= BPS7200_V17;
			AttemptTxBaudRate	= BPS7200_V17;
			AvailableTxBaudRate = BPS7200_V17;
		}
		else { /* 全フレームエラーが４回続くと V17 => V29 に変更。 */
			TxBaudRate			= BPS4800_V27; /* 耐ノイズ性能がほぼ同等な V27ter 4800bps にします。 by H.Kubo 2000/01/05 */
			AttemptTxBaudRate	= BPS4800_V27;
			AvailableTxBaudRate = BPS4800_V27;
		}
		break;
	case	BPS9600_V29:
		TxBaudRate			= BPS7200_V29;
		AttemptTxBaudRate	= BPS7200_V29;
		AvailableTxBaudRate = BPS7200_V29;
		break;
	case	BPS7200_V29:
		TxBaudRate			= BPS4800_V27;
		AttemptTxBaudRate	= BPS4800_V27;
		AvailableTxBaudRate = BPS4800_V27;
		break;
	case	BPS7200_V17:					/* 変更 7200 → 2400 におとす '96.01.10	 By t.yamaguchi */
#if defined(DEU)	/* by M.H '97/11/27 順番にﾎﾞｰﾚｰﾄを落とす */
		TxBaudRate			= BPS4800_V27;
		AttemptTxBaudRate	= BPS4800_V27;
		AvailableTxBaudRate = BPS4800_V27;
		break;
#endif
#if defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
		if (CHK_ForeignApprovalDEU()) {	/* DEU bitがOnの時のみ動作する */
			TxBaudRate			= BPS4800_V27;
			AttemptTxBaudRate	= BPS4800_V27;
			AvailableTxBaudRate = BPS4800_V27;
			break;
		}
#endif
	case	BPS4800_V27:
		TxBaudRate			= BPS2400_V27;
		AttemptTxBaudRate	= BPS2400_V27;
		AvailableTxBaudRate = BPS2400_V27;
		break;
	case	BPS2400_V27:
		TxBaudRate			= BPS2400_V27;
		AttemptTxBaudRate	= BPS2400_V27;
		AvailableTxBaudRate = BPS2400_V27;
		break;
	default:
		break;
	}
}


/*************************************************************************
	module		:[エラーページのチェック]
	function	:[
		1.	現在ページがエラーページかどうかをチェックする
		*.	エラーページはバッファのサイズ内のみ有効
		*.	ＥＣＭ送信で済みスタンプを押すページかどうかの判断に使う
		.	（ＥＲＲを受けたページは肯定応答を受けてもスタンプは押さない）
	]
	return		:[
		0	正常ページ
		1	エラーページ
	]
	common		:[
		SYS_FaxComTxType	SYS_TxTotalPage		TxMemoryFilePage
		TxResponsedRTN_PageSign		:ＲＴＮ／ＰＩＮ／ＥＲＲ応答された送信ページを示す
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/12]
	author		:[竹内茂樹]
*************************************************************************/
BYTE		CheckErrorPage( void )
{
	UWORD	current_page;
	UWORD	byte_point, bit_point;

	if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {	/**	スキャナ送信	*/
		current_page = SYS_TxTotalPage + 1;
		/*	ＲＴＮを受けたページはまだインクリメントしていない	*/
	}
	else {		/*	メモリ送信	*/
		current_page = TxMemoryFilePage;
	}

	/**	記憶バッファ内の位置計算	*/
	byte_point = (current_page - 1) / 8;
	bit_point  = (current_page - 1) % 8;

	if (byte_point < SYS_ERROR_PAGE) {		/**	バッファのサイズ内	*/
		if (TxResponsedRTN_PageSign[byte_point] & (0x01 << bit_point)) {	/**	エラーページ	*/
			/**	エラーありをリターン	*/
			return (1);
		}
	}

	/**	エラーなしをリターン	*/
	return (0);
}


/*************************************************************************
	module		:[全ページのエラーページをチェック]
	function	:[
		1.	現送信での全ページで画質不良応答(RTN,PIN,ERR)を受信した
		.	ページの有無を確認する
		2.	エラーページがあればＴ．４．２エラーにする
	]
	return		:[
		1	エラーページあり
		0	エラーページなし
	]
	common		:[
		FaxComResult	TxResponsedRTN_PageSign
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/19]
	author		:[竹内茂樹]
*************************************************************************/
BYTE		CheckAllErrorPage( void )
{
	UBYTE	count;

	if ((FaxComResult & 0x0C00) != TRANSMITERROR) {
		for (count = 0; count < SYS_ERROR_PAGE; count++) {
			if (TxResponsedRTN_PageSign[count] != 0) {
				FaxComResult |= (TRANSMITERROR | 0x0042);
				return (1);
			}
		}
	}

	return (0);
}


/*************************************************************************
	module		:[命令送信，応答受信]
	function	:[
		1.	命令送信し，応答受信を待つ
		2.	応答受信がないときは，３回試行する
	]
	return		:[
		1	応答受信あり
		0	３回試行で応答受信なし
	]
	common		:[
		PostSpeedHandshakeFlag		: コンパチで決定するフラグ
		ShorteningPreambleFlag		: プリアンブル短縮フラグ
	]
	condition	:[]
	comment		:[
		後手順短縮の処理を追加 (Aug.31.1994)
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/02/21]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE		TxCommandAndRxResponse(
	UBYTE	fcf,			/*	送信ＦＣＦ	*/
	UBYTE	option_fcf)		/*	送信拡張ＦＣＦ	*/
{
	UBYTE	count;
	UBYTE	ret_code;

	/**	プリアンブル短縮フラグをセット	*/
	ShorteningPreambleFlag = PostSpeedHandshakeFlag;

	count = 0;		/**	試行カウンタを初期化	*/
	ret_code = 0;	/**	リターン値を初期化		*/

#if (PRO_MODEM == R288F) /* Ported from Clover by H.Kubo 1998/02/03 */
	/* 1997/10/07 Y.Murata
	 * 受信ﾚﾍﾞﾙが-39dBmで遅延がない時にﾘﾄﾚｰﾝが発生する
	 * ２発目のﾎﾟｽﾄﾒｯｾｰｼﾞとﾘﾄﾚｰﾝがかぶってしまう時がある。
	 * その後、ﾌﾗｸﾞ誤検出して３秒の遅延時間がはたらいて、結果ﾎﾟｽﾄﾒｯｾｰｼﾞが
	 * ６秒後にでてしまう。この３秒の遅延を行うかをどうかのＳＷです。
	*/
	if (SYS_V34ProcedureExecuting()) {
		if (CHK_V34_PostExpired() == 0) {	/* 0で有効 UNISW_D7:2 */
			MDM_V34_CC_RetrainTimeCutFlag = 1;
		}
	}
#endif /* (PRO_MODEM == R288F) */

	while (++count <= 3) {	/**	試行３回以内	*/

		/**	３回目なら，プリアンブル短縮フラグをクリア (普通の長さで)	*/
		if (count == 3) {
			ShorteningPreambleFlag = 0;
		}

		if (fcf == CTC_F) {	/**	ＣＴＣ	*/
			MakeCTC_FIF();	/**	ＣＴＣフレーム作成	*/
		}
		else {
			MakeHDLC_Frame( fcf, option_fcf );	/**	指定フレーム作成	*/
		}

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/04 */
		FCM_TransmitCommand();		/**	命令送信	*/
		if (FCM_ReceiveResponse((UBYTE) 0, NON_CCRETRAIN) == FSK_RECEIVE) {	/**	応答受信ＯＫ	*/
			ret_code = 1;	/**	ＯＫでループ終了	*/
			break;
		}
#else /* (PRO_TX_SPEED == V34) */
		MDM_TransmitCommand();		/**	命令送信	*/
		if (MDM_ReceiveResponse(FCM_ReceiveResponseTime) == FSK_RECEIVE) {	/**	応答受信ＯＫ	*/
			ret_code = 1;	/**	ＯＫでループ終了	*/
			break;
		}
#endif /* (PRO_TX_SPEED == V34) */
	}

	/**	プリアンブル短縮フラグをクリア	*/
	ShorteningPreambleFlag = 0;

#if (PRO_TX_SPEED == V34)
	MDM_V34_CC_RetrainTimeCutFlag = 0;		/* 抜けてた。あ～びっくり 1999/10/26 Y.Murata */
#endif

	return (ret_code);		/**	結果をリターン	*/
}

/*************************************************************************
	module		:[ECM 送信の PPR で全フレームエラーが返されているか]
	function	:[
		ECM 送信の PPR で全フレームエラーが返されているかを検査
	]
	return		:[
		TRUE		全フレームエラーである
		FALSE		全フレームエラーでない
	]
	common		:[
		ECM_FrameCounter
		MDM_EcmStatus[]
	]
	condition	:[
		AnalyzeRxPostMessageFrame() でポストメッセージ応答の解析が終わっていること。
	]
	comment		:[
	]
	machine		:[SH704x]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1999/12/22]
	author		:[久保博]
*************************************************************************/
UBYTE FCM_CheckAllFrameError(void)
{
#if 0 /* 実際に送出したフレーム数とエラーフレーム数を比較するよう変更。 Changed by H.Kubo 2000/01/11 */
	UWORD count;
	if (ECM_FrameCounter == 0) { /* もともと１フレームしか送っていない場合は全フレームエラーに数えない。 */
		return 0;
	}
	for (count = 0; count < ECM_STATUS_MAX; count++) {
		if ((MDM_EcmStatus[count] & 0xFF) != 0xFF) {
			return 0;
		}
	}
	return 1;
#else
	UWORD fm_cnt;
	UWORD fld;
	UBYTE check_index;
	UBYTE check_bit;

	fm_cnt = 0;
	check_index = 0;
	/*	エラーフレーム検索処理	*/
	for (fld = 0, check_bit = 0x01; fld <= (UWORD)LastEcmFrameNumber; fld++, check_bit <<= 1) {	/**	今送出したフレーム数までＦＩＦをチェック */
		if ((check_bit & 0xff) == 0) {
			check_index++;
			check_bit = 0x01;
		}
		if (MDM_EcmStatus[check_index] & check_bit) { /**	ＦＩＦステータスが有効／無効をチェック	*/
			fm_cnt++;	/**	ＥＣＭ送信フレーム数を更新	*/
		}
	}
	if (fm_cnt > ECM_FrameCounter) { /* 送出フレーム数 (ECM_FrameCounter + 1) エラーフレームがある？ */
		return 1;	/* 全フレームエラー */
	}
	else {
		return 0;
	}
#endif
}

