/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATALNTA	  ANZUを移植									 */
/*	ファイル名	 : FCM_TCKS.C												 */
/*	モジュール	 :															 */
/*				 : GetMultiFrameLine()										 */
/*				 : GetFaxComTxType()										 */
/*				 : GetNextTxPageData()										 */
/*				 : GetFirstTxDocumentData()									 */
/*				 : SetTxBaudRate()											 */
/*				 : SetTxCode()												 */
/*				 : SetTxMode()												 */
/*				 : SetTxPaperLength()										 */
/*				 : CheckTxModeUpperFine()									 */
/*				 : SetTxMinimumCommunicationTime()							 */
/*				 : SetTxECM_Mode()											 */
/*				 : SetTxMSE_Mode()											 */
/*				 : SetTxPaperWidth()										 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 :															 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\mem_def.H"
#include "\src\atlanta\define\SYSBATCH.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
#include "\src\atlanta\ext_v\ini_tbl.h"
 #endif
#endif
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\CMN_PRO.H"
#include "\src\atlanta\define\MEM_PRO.H"
#include "\src\atlanta\define\STNG_PRO.H"/* CHKで始まる関数 */
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\UNI_PRO.H"
#include	"\src\atlanta\define\mntsw_b.h"	/* 1997/05/12  By T.Yamaguchi */

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

#if (1) /* (PRO_TX_SPEED == V34 ) */ /* Added by H.Kubo 1997/08/06 */
#include "\src\atlanta\define\MAN_PRO.H"
#endif /* (1) */ /* (PRO_TX_SPEED == V34 ) */


/*************************************************************
	module		:[フレーム取り込み]
	function	:[
		1.非標準フレーム、IDフレーム、標準フレームのリードポインター初期化
		2.非標準フレーム、IDフレーム、標準フレームの名前パラメータ初期化
		3.フレーム名、リードポインター、受信バイト数セット
	]
	return		:[なし]
	common		:[
					NonStdFrmPos
					ID_FrmPos
					MDM_ModemBuffer
					StdFrmPos
					NonStdFrmName
					ID_FrmName
					StdFrmName
					MDM_RxSize
					MakerCodeRxFlag
					RxID_FrameByteCount
					RxStandardFrameByteCount
					RxNonStandardFrameByteCount
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/19]
	author		:[鈴木 郁二]
*************************************************************/
void GetMultiFrameLine(void)
{
	UBYTE name;
	WORD pos;

	name = 0;
	pos = 0;

	/**	各フレームのリードポインター初期化	*/
	NonStdFrmPos = 0;
	ID_FrmPos = 0;
	StdFrmPos = 0;
	PWD_FrmPos = 0;
	SEP_FrmPos = 0;
	SUB_FrmPos = 0;

	/**	各フレーム名初期化	*/
	NonStdFrmName = NO;
	ID_FrmName = NO;
	StdFrmName = NO;
	PWD_FrmName = NO;
	SEP_FrmName = NO;
	SUB_FrmName = NO;

	/* 1996/11/05 Y.Murata
	 * もし、ﾓｰﾄﾞ変更時にNSSがとれなっからﾌｧｲﾝがｽｰﾊﾟｰﾌｧｲﾝになってしまうので受信ﾊﾞｲﾄｶｳﾝﾀｰをｸﾘｱする
	*/
	RxNonStandardFrameByteCount = 0;
	RxID_FrameByteCount = 0;
	RxStandardFrameByteCount = 0;
	RxPasswordFrameByteCount	= 0;
	RxSelectiveFrameByteCount	= 0;
	RxSubaddressFrameByteCount	= 0;

	while (pos < 8) {		/**	モデムバッファポインター < 8	*/
#if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* added by H.Kubo 1998/10/19 */
		if (MDM_RxSize[pos] > FCF_POS) {		/**	受信バイト数 は FCF までより多いか？	*/
#else
		if (MDM_RxSize[pos] != 0) {		/**	受信バイト数 > 0	*/
#endif
			switch (MDM_ModemBuffer[pos][FCF_POS]) {		/**	フレーム名	*/
			case (NSS_F | X_BIT):	/**	NSS|X_BIT	*/
			case (TSI_F | X_BIT):	/**	TSI|X_BIT	*/
			case (DCS_F | X_BIT):	/**	DCS|X_BIT	*/
			case (T_PWD_F | X_BIT):	/** PWD|X_BIT	*/
			case (SUB_F | X_BIT):	/** SUB|X_BIT	*/
				/**	ローカル変数にフレーム名セット	*/
				/**	ローカル変数にＸビットを取り除いたものをセット	*/
				name = (UBYTE)(~X_BIT & MDM_ModemBuffer[pos][FCF_POS]);
				break;
			default:	/* NSF,NSS,NSC,CSI,TSI,CIG,DIS,DCS,DTC,CFR,PWD,SEP,SUB */
				/**	ローカル変数にフレーム名セット	*/
				name = MDM_ModemBuffer[pos][FCF_POS];
				break;
			}

			switch (name) {		/**	フレーム名	*/
			case NSF_F:	/**	NSF	*/
			case NSS_F:	/**	NSS	*/
			case NSC_F:	/**	NSC	*/
				/**	大域変数にフレーム名、リードポインター、受信バイト数セット	*/
				NonStdFrmName = name;
				NonStdFrmPos = pos;
				RxNonStandardFrameByteCount = MDM_RxSize[NonStdFrmPos];
				if ((MDM_ModemBuffer[NonStdFrmPos][START_HDLC_FIF_POS] == 0x00) &&
					(MDM_ModemBuffer[NonStdFrmPos][START_HDLC_FIF_POS + 1] == 0x00) &&
					(MDM_ModemBuffer[NonStdFrmPos][MAKERCODE_POS] == OwnMakerCode)) {		/**	メーカーコード村田	*/
					/**	村田コード受信フラグ YES	*/
#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
					if (CHK_DisasterPreventionFaxEnable()) {
						MakerCodeRxFlag = NO;
					}
					else {
						MakerCodeRxFlag = YES;
					}
#else
					MakerCodeRxFlag = YES;
#endif	/* End of (PRO_DISASTER_PREVENTION_FAX == ENABLE) */
				}
				else {
					/* 過去に短縮ハンドシェーク属性 ON とした相手先に他社機がつながっていた場合,不具合発生 28.Jly'94 Y.Suzuki */
					MakerCodeRxFlag = NO;
				}
				break;
			case CSI_F:	/**	CSI	*/
			case TSI_F:	/**	TSI	*/
			case CIG_F:	/**	CIG	*/
				/**	大域変数にフレーム名、リードポインター、受信バイト数セット	*/
				ID_FrmName = name;
				ID_FrmPos = pos;
				RxID_FrameByteCount = MDM_RxSize[ID_FrmPos];
				break;
			case DIS_F:	/**	DIS	*/
			case DCS_F:	/**	DCS	*/
			case DTC_F:	/**	DTC	*/
				/**	大域変数にフレーム名、リードポインター、受信バイト数セット	*/
				StdFrmName = name;
				StdFrmPos = pos;
				RxStandardFrameByteCount = MDM_RxSize[StdFrmPos];
				break;
			case CFR_F:	/**	CFR	*/
				/**	大域変数にフレーム名、リードポインター、受信バイト数セット	*/
				StdFrmName = DIS_F;
				StdFrmPos = pos;
				RxStandardFrameByteCount = MDM_RxSize[StdFrmPos];
				break;
/* F_CODE */
			case P_PWD_F:	/** PWD	*/
			case T_PWD_F:	/** PWD	*/
				PWD_FrmName = name;
				PWD_FrmPos = pos;
				RxPasswordFrameByteCount = MDM_RxSize[PWD_FrmPos];
				break;
			case SEP_F:		/** SEP	*/
				SEP_FrmName = name;
				SEP_FrmPos = pos;
				RxSelectiveFrameByteCount = MDM_RxSize[SEP_FrmPos];
				break;
			case SUB_F:		/** SUB	*/
				SUB_FrmName = name;
				SUB_FrmPos = pos;
				RxSubaddressFrameByteCount = MDM_RxSize[SUB_FrmPos];
				break;
			}
			if (MDM_ModemBuffer[pos][LAST_FRAME_POS] == LAST_FRAME_DATA) {		/**	最終フレーム	*/
				break;	/* whileを抜ける */
			}
		}
		/**	リードポインターインクリメント	*/
		pos++;
	}
	return;
}


/*************************************************************
	module		:[送信タイプ確定]
	function	:[
		交信種別とコマンド種別から送信タイプ(大域変数)をスキャナー送信とメモリ送信に分類する
	]
	return		:[削除	1996/11/28	By T.Yamaguchi
	]
	common		:[
					SYS_FaxComType
					CommandFileOptionItem
					SYS_FaxComTxType
					FaxCompatibleErrorCode
					FaxComPerformingFlag
	]
	condition	:[]
	comment		:[
				リターン値を返しても無駄なのでvoidに変更する1996/11/28	By T.Yamaguchi
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/20]
	author		:[鈴木 郁二]
*************************************************************/
void GetFaxComTxType(void)
/* UBYTE GetFaxComTxType(void)	1996/11/28	By T.Yamaguchi */
{
	switch (SYS_FaxComType) {		/**	交信種別	*/
	case SYS_COMMAND_EXECUTE:	/**	コマンド実行	*/
		switch (CommandFileOptionItem) {		/**	  コマンド種別	*/
		case SYS_MEMORY_TX:					/**	メモリ送信	*/
		case SYS_DELAYED_MEMORY_TX:			/**	時刻指定メモリ送信	*/
		case SYS_MEMORY_SECURE_TX:			/**	メモリ親展送信	*/
		case SYS_MEMORY_RELAY_BROADCAST:	/**	メモリ中継指示送信	*/
		case SYS_DELAYED_BROADCAST:			/**	順次同報送信	*/
		case SYS_RELAYED_TX:				/**	中継配信	*/
		case SYS_BATCH_MEMORY_TX:			/** FX一括送信	*/
		case SYS_RELAYED_TX_REPORT:			/** RELAYED TX REPORT */
#if (PRO_F_CODE == ENABLE)
		case SYS_MEMORY_SUB_ADDRESS_TX:		/** Ｆｺｰﾄﾞﾒﾓﾘ送信(親展・掲示板に送信） */
#endif
#if (PRO_CIPHER == ENABLE)
		case SYS_CIPHER_TX:					/** 暗号化送信(メモリ送信しかない) */
#endif
			/**	送信タイプ メモリ送信	*/
			SYS_FaxComTxType = SYS_MEMORY_TRANSMIT;
			break;
		case SYS_SCANNER_TX:				/**	スキャナ送信	*/
		case SYS_DELAYED_SCANNER_TX:		/**	時刻指定スキャナ送信	*/
		case SYS_SCANNER_SECURE_TX:			/**	スキャナ親展送信	*/
		case SYS_SCANNER_RELAY_BROADCAST:	/**	スキャナ中継指示送信	*/
#if (PRO_F_CODE == ENABLE)
		case SYS_SCANNER_SUB_ADDRESS_TX:	/**	Ｆｺｰﾄﾞｽｷｬﾅ送信(親展・掲示板に送信） */
#endif
			/**	送信タイプ スキャナ送信	*/
			SYS_FaxComTxType = SYS_SCANNER_TRANSMIT;
			break;
		case SYS_POLLING_RX:				/**	ポーリング受信	*/
		case SYS_DB_POLLING_RX:				/**	検索ポーリング受信	*/
#if (PRO_CONTINUOUS_POLLING == ENABLE)
		case SYS_CONTINUOUS_POLLING_RX:		/* 連続ポーリング受信 Oct.18.1996  By T.Yamaguchi */
#endif
#if (PRO_F_CODE == ENABLE)
		case SYS_SELECT_POLLING_RX:			/**	選択ﾎﾟｰﾘﾝｸﾞ受信(掲示板を受信）*/
#endif
			break;
		case SYS_POLLING_TX:				/**	ポーリング送信	*/
		case SYS_DB_POLLING_TX:				/**	検索ポーリング送信	*/
		default:
			/**	エラー処理	*/
			/*	コマンドとしてポーリング送信は、ありえない	*/
			FaxCompatibleErrorCode = UNEXPECTED_ERROR;
			FaxComPerformingFlag = NO;
			break;
		}
		break;
	case SYS_REMOTE_FAX_TX: /** リモートＦＡＸ送信 */
	case SYS_AUTO_CALLED:	/**	自動受信	*/
	case SYS_FIP_CALLED:	/**	FIP受信	*/
	case SYS_FIP_SEND:						/** FIP送信コマンド **/
		/**	送信タイプ メモリ送信	*/
		SYS_FaxComTxType = SYS_MEMORY_TRANSMIT;
		break;
	case SYS_MANUAL_TX:						/** 手動送信 **/
		SYS_FaxComTxType = SYS_SCANNER_TRANSMIT;
		break;
	default:
		/**	エラー処理	*/
		FaxCompatibleErrorCode = UNEXPECTED_ERROR;
		FaxComPerformingFlag = NO;
	}
}


/*************************************************************
	module		:[GetNextTxPageData(UWORD page)]
	function	:[
		送信原稿の情報をSYS_DocBlockにセットする
	]
	return		:[なし]
	common		:[
		SYS_FaxComTxType
		SYS_DocBlock.Src.:Mode
		SYS_DocBlock.Src.:Size
		SYS_DocBlock.Src.:Code
		SYB_ModeSw
		SYS_DocBlock.Index.:item
		TxMemoryFileItem
		SYS_DocBlock.Index.:no
		SYS_DocBlock.Index.:page
		TxMemoryFileNo
		TxMemoryFileCurrentExecutingNo
	]
	condition	:[]
	comment		:[
				バッチ送信リダイヤル時、送信開始頁セット処理追加
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/22]
	author		:[鈴木 郁二]
*************************************************************/
void GetNextTxPageData(UWORD page)	/*	TxMemoryFilePage もしくは +1 がセット	*/
{
#if(PRO_BATCH_TX == ENABLE)
	UWORD	i_data;
	UWORD	k_data;
	UBYTE	j_data;

	i_data = 0;
	j_data = 0;
	k_data = 0;
#endif
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
if (ROM_SW_SpecialDoctorReport) {

#if (0)
** 		/* 医師会特ＲＯＭで、通常の送信が出来ない不具合修正 CSH-004-D86-001 by O.Kimoto 1999/10/06 */
** 		if ((CommandFileTitleMessage & 0xf0) != 0x00) {
** 			SYS_DocBlock.Src.Mode = (BYTE)SYS_NORMAL;
** 			SYS_DocBlock.Src.Size = (BYTE)SYS_DOCUMENT_A4_SIZE;
** 			return;
** 		}
#else
		if ((CommandFileTitleMessage == 0x11) || (CommandFileTitleMessage == 0x21)) {
			SYS_DocBlock.Src.Mode = (BYTE)SYS_NORMAL;
			SYS_DocBlock.Src.Size = (BYTE)SYS_DOCUMENT_A4_SIZE;
			return;
		}
#endif

}
 #endif
#endif

	if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
		/**	送信原稿情報 モード サイズセット	*/
		SYS_DocBlock.Src.Mode = (BYTE)SYB_ModeSw;
#if (PRO_CCD == DPI300) /* ANZU_L 300d*400 対応します by T.Soneoka 1997/11/13 */
		if (SYB_ModeSw == SYS_SFINE) {
			SYS_DocBlock.Src.Mode = SYS_E_HFINE;
		}
#endif
		SYS_DocBlock.Src.Size = (BYTE)CMN_GetDocumentScanSize();
	}
	else {		/**	その他の送信	*/
		/**	送信原稿情報 メモリアイテム NO ページ　モード コード サイズセット	*/
		SYS_DocBlock.Index.Item = (UBYTE)TxMemoryFileItem;
#if(PRO_BATCH_TX == ENABLE)
		if(SYS_CurrentExecutingCommand->Kind == SYS_BATCH_TX) {/** 一括送信 */
			if(!BatchRedialFirstPage && (SYS_TxTotalPage == 0)) {/** １ページ以上送信後のリダイヤル実行 */
				BatchRedialFirstPage = 1;
				for(i_data = 0,j_data = 0; j_data < SYS_BATCH_INDEX_MAX; j_data++) {
					i_data += PollingTxFilePage[j_data];
					if(i_data >= page) {/** 送信開始メモリファイルインデックスとページ取り出し */
						TxMemoryFileCurrentExecutingNo = j_data;
						if(i_data == page) {
							page = PollingTxFilePage[j_data];
							/* フェーズ C で再度セットしているのでここで更新しておく */
							TxMemoryFilePage = page;
							break;
						}
						else{
							k_data = PollingTxFilePage[j_data];
							while(i_data > page) {
								i_data--;
								k_data--;
							}
							page = k_data;
							/* フェーズ C で再度セットしているのでここで更新しておく */
							TxMemoryFilePage = page;
							break;
						}
					}
				}
			}
		}
#endif
		if ( ((TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)		/*	掲示板ﾎﾟｰﾘﾝｸﾞ原稿 */
		   || (TxMemoryFileItem == SYS_MEM_SUB_SECURE_FILE)) 		/* Fｺｰﾄﾞ親展原稿 ﾎﾟｰﾘﾝｸﾞできる場合 */
		 &&	(!(SYB_MaintenanceSwitch[MNT_SW_B4] & FCODE_POLLING_TX_METHOD)))	{	/* ﾒﾝﾃﾅﾝｽSWB4-2 0 */
			SYS_DocBlock.Index.No = TxMemoryFileNo[TxMemoryFileNextExecutingNo];
		}
		else {
			SYS_DocBlock.Index.No = TxMemoryFileNo[TxMemoryFileCurrentExecutingNo];
		}
		SYS_DocBlock.Index.Page = page;
		SYS_DocBlock.Index.BoxNumber = TxMemoryFileBoxNumber;
		SYS_DocBlock.Src.Code = MEM_CheckStoreCode(&SYS_DocBlock.Index);
		SYS_DocBlock.Src.Mode = MEM_CheckStoreMode(&SYS_DocBlock.Index);
		SYS_DocBlock.Src.Size = MEM_CheckStoreSize(&SYS_DocBlock.Index);
	}
	return;
}


/*************************************************************
	module		:[原稿情報セット]
	function	:[
		送信の最初に原稿の情報を大域変数にセット
		1.メモリ送信
			ファイルアイテム ファイルNO ファイルページをセット
			リモートFAX送信追加 25.Mar'94 Y.Suzuki
		2.スキャナ送信
			ページに１をセット
	]
	return		:[なし]
	common		:[
					SYS_FaxComTxType
					SYS_FaxComType
					TxMemoryFileItem
					TxMemoryFileNo
					TxMemoryFilePage
					SYS_CurrentExecutingCommand->:CommandNumber
					PollingTxFilePage
					FirstTxMode
					SYS_DocBlock.Src.:Mode
					SYS_DocBlock.Src.:Size
					DocWidth
					TxMode
					FipMailBoxNo
	]
	condition	:[]
	comment		:[
				修正履歴
				1.一括送信送信済み頁初期化 94/9/22 Y.Suzuki
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/22]
	author		:[鈴木 郁二]
*************************************************************/
void GetFirstTxDocumentData(void)
{
	UWORD index_no;
	UWORD buf_no;

	index_no = 0;
	buf_no = 0;

	switch (SYS_FaxComTxType) {		/**	送信タイプ	*/
	case SYS_MEMORY_TRANSMIT:	/**	メモリ送信	*/
#if(PRO_FIP == ENABLE)
		if (SYS_FaxComType == SYS_FIP_SEND) {		/**	FIP送信	*/
			/**	アイテム ファイルNO ファイルページ セット	*/
			TxMemoryFileItem = SYS_MEM_FIP_FILE;
			TxMemoryFileNo[0] = SYS_FIP_MailBoxNo;
			TxMemoryFileNo[1] = (UWORD)0xFFFF;
			PollingTxFilePage[0] = MEM_CountTotalPage(TxMemoryFileItem, TxMemoryFileNo[0], MEM_IGNORE_BOX_NUMBER);
			PollingTxFilePage[1] = (UWORD)0xFFFF;
			TxMemoryFilePage  = SYS_FIP_FilePage;
		}
		else {		/**	その他のメモリ送信	*/
#endif
			/*	ポーリング送信は含まない 自動受信は含む	*/
			/**	アイテム ファイルNO ファイルページ セット	*/
			if (SYS_FaxComType == SYS_REMOTE_FAX_TX) {/**	リモートＦＡＸ送信	*/
				TxMemoryFileItem = SYS_MEM_REMOTE_TX_FILE;/*SYS_MEM_TX_FILE;2.May'94*/
				TxMemoryFileCurrentExecutingNo = 0;/* リモートＦＡＸ送信は必ず '0' 11.Jun'94 */
				TxMemoryFileNo[TxMemoryFileCurrentExecutingNo] = 0;
				TxMemoryFileNo[1] = (UWORD)0xFFFF;
				TxMemoryFilePage = 1;/* 次に送るページをセット 再送を考慮していません　Y.Suzuki*/
			}
#if(PRO_BATCH_TX == ENABLE)
			if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {		/*ポーリング送信でも通ってしまうため 条件追加 '96.04.23 By t.yamaguchi */
				if (SYS_CurrentExecutingCommand->Kind == (UBYTE)SYS_BATCH_TX) {/**	一括送信	*/
					TxMemoryFileItem = (UBYTE)(SYS_CurrentExecutingCommand->Number.Batch + SYS_MEM_BATCH_TX_FILE1);/* SYB_BatchTxFile[]の配列オフセット値を足す */
					for(index_no = 0,buf_no = 0;  index_no < SYS_BATCH_INDEX_MAX; index_no++) {
						if(BatchP->IndexNo[index_no] == SYS_BAT_DOC_STORE) {
							TxMemoryFileNo[buf_no] = index_no;
/* 変更 1997/06/02  By T.Yamaguchi */
/*							PollingTxFilePage[buf_no] = MEM_CountTotalPage(TxMemoryFileItem, index_no, MEM_IGNORE_BOX_NUMBER); */
							PollingTxFilePage[buf_no] = MEM_CountFinalPage(TxMemoryFileItem, index_no,MEM_IGNORE_BOX_NUMBER);
							buf_no++;
						}
					}
					TxMemoryFileNo[buf_no] = (UWORD)0xFFFF;
					PollingTxFilePage[buf_no] = (UWORD)0xFFFF;
					/** バッチ送信総ページ数をセット */
					CommandFilePage = 0;
					for(buf_no = 0; PollingTxFilePage[buf_no] != 0xFFFF; buf_no++) {
						CommandFilePage += PollingTxFilePage[buf_no];
					}
					/* 以下の行を一括送信のときのみセットする様に変更 1996/11/28  By T.Yamaguchi */
					if((SYS_CurrentExecutingCommand -> Page) == 0) {/** 送信済み頁が0ページ */
						/* 一括送信頁表示、リダイヤル頁指定に使用 */
						BatchTxFinishPage = 0;
						BatchRedialFirstPage = 1;
					}
					else {/* 1頁以上送信済みでエラー後，リダイヤル */
						BatchRedialFirstPage = 0;

						/* 1998/04/17 Y.Murata
						 * 一括送信で、２つ以上のBOXが登録されていて、ﾘﾀﾞｲｱﾙ等で一括送信が交互に行われた場合
						 * 発信元のﾍﾟｰｼﾞが、おかしくなる
						*/
						BatchTxFinishPage = SYS_CurrentExecutingCommand -> Page;

					}
				}	/* 1996/11/28  By T.Yamaguchi */
			}
#endif
			if (TxMemoryFileItem == NO) {
				TxMemoryFileItem = SYS_MEM_TX_FILE;
			}
			if (TxMemoryFileNo[0] == 0xFFFF) {
				if(SYS_CurrentExecutingCommand ->Kind == SYS_COMMAND_TRX) {
					/*---------------------------------------------------ｰｰｰ---------*/
					/** 不達通知のときは、エラーとなった配信のコマンドNOをセットする */
					/*										  Y.Suzuki	  21.Feb'95	 */
					/*---------------------------------------------------------------*/
					if (CommandFileOptionItem == SYS_RELAYED_TX_REPORT) {
						TxMemoryFileNo[0] = (UWORD)CommandP->Option.OptionNumber.RelaySourceID[0];
					}
					else {
						TxMemoryFileNo[0] = (UWORD)SYS_CurrentExecutingCommand -> Number.Command;
					}
				}
				TxMemoryFileNo[1] = (UWORD)0xFFFF;
			}
			if (TxMemoryFilePage == 0) {
				TxMemoryFilePage = (UWORD)((SYS_CurrentExecutingCommand -> Page) + 1); /* 次に送信するページ数をセット */
				/* ●ICHOU追加 メモリ送信最適化処理で最終ページ番号を取得 by T.Soneoka 1996/06/11 */
				TxFinalPageNumber = MEM_CountFinalPage(TxMemoryFileItem, TxMemoryFileNo[TxMemoryFileCurrentExecutingNo] ,TxMemoryFileBoxNumber);
			}
#if(PRO_FIP == ENABLE)
		}
#endif
		break;
	case SYS_SCANNER_TRANSMIT:	/**	スキャナ送信	*/
		/**	ファイルページに 1 をセット	*/
		TxMemoryFilePage = 1;
		break;
	}
	/**	送信原稿の情報を SYS_DocBlock にセット	*/
	GetNextTxPageData(TxMemoryFilePage);
#if (PRO_RELAYED_REPORT == ENABLE) /* Changed by H.Kubo 1998/01/19 */
	if (CommandFileOptionItem == SYS_RELAYED_TX_REPORT) { /* Fixed by H.Kubo 1998/02/17 */
	/* if (SYS_FaxComType == SYS_RELAYED_TX_REPORT) { */
		/* 不達通知では、蓄積原稿とは無関係に原稿巾とモードを指定します。 */
		/**	1ページ目の送信モードセット	*/
		FirstTxMode = SYS_NORMAL;
		/**	原稿幅セット	*/
		DocWidth = SYS_DOCUMENT_A4_SIZE;
	}
	else {
		/**	1ページ目の送信モードセット	*/
		FirstTxMode = (UBYTE)SYS_DocBlock.Src.Mode;
		/**	原稿幅セット	*/
		DocWidth = (UBYTE)SYS_DocBlock.Src.Size;
	}
	/**	最後に送るページのモードセット	*/
	TxMode = (UBYTE)SYS_DocBlock.Src.Mode;
#else
	FirstTxMode = (UBYTE)SYS_DocBlock.Src.Mode;
	/**	最後に送るページのモードセット	*/
	TxMode = (UBYTE)SYS_DocBlock.Src.Mode;
	/**	原稿幅セット	*/
	DocWidth = (UBYTE)SYS_DocBlock.Src.Size;
#endif
	return;
}


/*************************************************************
	module		:[送信ボーレートを確定]
	function	:[
		DIS/DTC 受信時送信ボーレートを確定する
	]
	return		:[
		OK--YES／NG--NO
	]
	common		:[
		StdFrmName
		MDM_ModemBuffer
		StdFrmPos
		MakerCodeRxFlag				:ポーリング受信時、自動受信（ＳＤＣＳ受信時）ON(1)となる。
		OwnMakerCode
		AvailableTxBaudRate
		SYS_TxTotalPage
	]
	condition	:[]
	comment		:[
		さつき、ラベンダーは、9600---2400BPS
		桐、紅葉は、14400---2400BPS
		MakerCodeRxFlag ---
		松下 UF-150対策(DISのボーレートビットをすべてONしてくる。) 95/03/14 Y.Suzuki
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/22]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE SetTxBaudRate(void)
{
/*	if((MDM_ModemBuffer[StdFrmPos][4] & 0x30) == 0x30) {松下UF-150 対策 14.Mar'95 Y.Suzuki */
/*		MDM_ModemBuffer[StdFrmPos][4] &= 0xCF;	 V17 + V33 OFF */
/*	}*/

/* #if defined(ITA)	1997/09/24  By T.Yamaguchi */
	/* ＵＳＡで機種Ｔ４能力ビットをみていないため交信エラーになる機種があったためＩＴＡの条件
	**	コンパイルを外す	1997/09/24  By T.Yamaguchi
	*/
	if(!(MDM_ModemBuffer[StdFrmPos][4] & JT_T4_BIT)) {	/**	DIS 10ﾋﾞｯﾄ目のﾁｪｯｸ */
		FaxCompatibleErrorCode = COMMUNICATE_T4BIT_ERROR;
		return(NO);
	}
/* #endif */
	switch (MDM_ModemBuffer[StdFrmPos][4] & MASK_BAUDRATE) {		/**	DIS/DTC FIF ボーレートビットチェック	*/
		case CCITT_V17_BIT:/**	V17ビット	*/
#if (PRO_TX_SPEED == V33) || (PRO_TX_SPEED == V34) /* V34 is added by H.Kubo 1997/11/05 */
			if (!FCM_PtnrChk_DCS_V33AllHold()) {
				if (AvailableTxBaudRate == BPS14400_V17) {		/**	送信可能ボーレートV17-14400	*/
					if (SYS_TxTotalPage == 0) {		/**	最初のページである	*/
						/**	V17-14400セット	*/
						AttemptTxBaudRate = BPS14400_V17;
					}
					break;
				}
				else if (AvailableTxBaudRate == BPS12000_V17) {		/**	V17-12000	*/
					if (SYS_TxTotalPage == 0) {		/**	最初のページである	*/
						/**	V17-12000セット	*/
						AttemptTxBaudRate = BPS12000_V17;
					}
					break;
				}
				else if (AvailableTxBaudRate == BPS9600_V17) {		/**	V17-9600	*/
					if (SYS_TxTotalPage == 0) {		/**	最初のページである	*/
						/**	V17-9600セット	*/
						AttemptTxBaudRate = BPS9600_V17;
					}
					break;
				}
#if (PRO_PROHIBIT_V29_TX_SWITCH == ENABLE) /* 試験的にサカキで入れます。 by H.Kubo 1998/10/06 */
				else if (AvailableTxBaudRate == BPS7200_V17) {		/**	V17-7200	*/
					if (SYS_TxTotalPage == 0) {		/**	最初のページである	*/
						/**	V17-7200セット	*/
						AttemptTxBaudRate = BPS7200_V17;
					}
					break;
				}
#endif
			}
#endif
		case CCITT_V33_BIT:	/**	V33ビット	*/
#if (PRO_TX_SPEED == V33) || (PRO_TX_SPEED == V34) /* V34 is added by H.Kubo 1997/11/05 */
			if ((AvailableTxBaudRate == BPS14400_V17) ||
				(AvailableTxBaudRate == BPS14400_V33)) {		/**	送信可能ボーレートV17-14400 または V33-14400	*/
				if (SYS_TxTotalPage == 0) {		/**	最初のページである	*/
					/**	V33-14400セット	*/
					AttemptTxBaudRate = BPS14400_V33;
				}
				break;
			}
			else if ((AvailableTxBaudRate == BPS12000_V17) ||
				(AvailableTxBaudRate == BPS12000_V33)) {	/**	送信可能ボーレートV17-12000 または V33-12000	*/
				if (SYS_TxTotalPage == 0) {		/**	最初のページである	*/
					/**	V33-12000セット	*/
					AttemptTxBaudRate = BPS12000_V33;
				}
				break;
			}
			/*break;*/
#endif
		/** USA にて UF-150 以外の不正DIS送出機と遭遇 松、竹、桜と同じ修正にする。95/07/07 Y.Suzuki */
		default:
			switch(MDM_ModemBuffer[StdFrmPos][4] & CCITT_V29_BIT) {
			case CCITT_V29_BIT:	/**	V29ビット	*/
			case CCITT_V29ONLY_BIT:	/**	V29Onlyビット	*/
				if ((AvailableTxBaudRate == BPS14400_V17) ||
					(AvailableTxBaudRate == BPS12000_V17) ||
					(AvailableTxBaudRate == BPS9600_V17)  ||
					(AvailableTxBaudRate == BPS14400_V33) ||
					(AvailableTxBaudRate == BPS12000_V33) ||
					(AvailableTxBaudRate == BPS9600_V29)) {		/**	送信可能ボーレート9600以上	*/
					if (SYS_TxTotalPage == 0) {		/**	最初のページである	*/
						/**	V29-9600セット	*/
						AttemptTxBaudRate = BPS9600_V29;
					}
					break;
				}
				else if ((AvailableTxBaudRate == BPS7200_V29) ||
						 (AvailableTxBaudRate == BPS7200_V17)) {	/**	送信可能ボーレートV17-7200またはV29-7200	*/
					if (SYS_TxTotalPage == 0) {		/**	最初のページである	*/
						/**	V29-7200セット	*/
						AttemptTxBaudRate = BPS7200_V29;
					}
					break;
				}
			case CCITT_V27_BIT:	/**	V27ビット	*/
				if ((AvailableTxBaudRate == BPS14400_V17) ||
					(AvailableTxBaudRate == BPS12000_V17) ||
					(AvailableTxBaudRate == BPS9600_V17)  ||
					(AvailableTxBaudRate == BPS7200_V17)  ||
					(AvailableTxBaudRate == BPS14400_V33) ||
					(AvailableTxBaudRate == BPS12000_V33) ||
					(AvailableTxBaudRate == BPS9600_V29)  ||
					(AvailableTxBaudRate == BPS7200_V29)  ||
					(AvailableTxBaudRate == BPS4800_V27)) {		/**	送信可能ボーレート4800以上	*/
					if (SYS_TxTotalPage == 0) {		/**	最初のページである	*/
						/**	4800セット	*/
						AttemptTxBaudRate = BPS4800_V27;
					}
					break;
				}
				else {		/**	送信可能ボーレート2400	*/
					/**	2400セット	*/
					AttemptTxBaudRate = BPS2400_V27;
					break;
				}
			case CCITT_V27F_BIT:	/**	V27フォールバックビット	*/
				/**	2400セット	*/
				AttemptTxBaudRate = BPS2400_V27;
				break;
			default:
				return(NO);
			}/*	 USA にて UF-150 以外の不正DIS送出機と遭遇 松、竹、桜と同じ修正にする 95/07/07 Y.Suzuki */
	}
	return(YES);
}

/*************************************************************
	module		:[送信符号化方式の確定]
	function	:[
		ＤＩＳ／ＤＴＣのビットと送信能力より符号化方式を確定する
	]
	return		:[]
	common		:[
				TxCodingMethod
				SYS_FaxComTxType
				AvailableTxCodingMethod
				TxReceiptConfirmationReportFlag
				MDM_ModemBuffer
				StdFrmPos
				TxECM_Mode
				MakerCodeRxFlag
				NonStdFrmPos
				RxNonStandardFrameByteCount
				NonStdFrmName
				SYS_DocBlock.Src.:Code			:蓄積されている原稿の符合化方式、スキャナ送信時(確定送信符号化方式)
				SYS_DocBlock.Dst.:Code			:確定送信符号化方式
	]
	condition	:[]
	comment		:[桐、紅葉-MH、MR、MMR	さつき、ラベンダーＨ-MH、MR　ラベンダーＬ-MH
				MH機、MR機、MMR機の区別（条件コンパイル）は、送信可能符号化方式を決定するところで記述すること
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/22]
	author		:[鈴木 郁二]
*************************************************************/
void SetTxCode(void)
{
	WORD pos;
	WORD code;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	UBYTE jbig_scanner_tx;
	jbig_scanner_tx = 1;
#endif

	pos = 0;
	code = 0;
	/**	MH コードセット	*/
	TxCodingMethod = SYS_MH_CODE;
	if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
		/**	送信可能コードをローカル変数にセット	*/
		code = (WORD)AvailableTxCodingMethod;
	}
#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1998/01/19 */
	if (CommandFileOptionItem == SYS_RELAYED_TX_REPORT) { /* Fixed by H.Kubo 1998/02/17 */
	/* if (SYS_FaxComTxType == SYS_RELAYED_TX_REPORT) [ */ 
		/**	送信可能コードをローカル変数にセット	*/
		if (TxSmType == TX_RELAYED_TX_REPORT) {
			code = (WORD)AvailableTxCodingMethod;
		}
	}
#endif /* (PRO_RELAYED_REPORT == ENABLE) */
	if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
		/**	送信可能コードをローカル変数にセット	*/
		code = (WORD)AvailableTxCodingMethod;
	}
	else {		/**	メモリ送信	*/
		if (TxRCR_Flag != YES) {		/**	受領証送信しない	*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
			code = AvailableTxCodingMethod;
#else
			/**	送信可能コードとしてコマンドのコードをセット	*/
			code = (WORD)SYS_DocBlock.Src.Code;
#endif
		}
		else {		/**	受領証送信する	*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
			code = AvailableTxCodingMethod;
#else
			/**	送信可能コード MR	*/
			/* code = SYS_MR_CODE; MMRで送れるのでMMRを入れておく 1997/10/17  By T.Yamaguchi */
			code = SYS_MMR_CODE;
#endif
		}
	}
	if (MDM_ModemBuffer[StdFrmPos][4] & SET_MR_BIT) {		/**	DIS/DCS FIF MRビット ON	*/
		switch (code) {		/**	送信可能コード	*/
			case SYS_MH_CODE:	/**	MH	*/
				/**	送信符号化方式 MH	*/
				TxCodingMethod = SYS_MH_CODE;
				break;
			case SYS_MR_CODE:	/**	MR	*/
			case SYS_MMR_CODE:	/**	MMR	*/
			case SYS_MG3_CODE:	/**	松下CODEC 20.Jly'94 Y.Suzuki	*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
			case SYS_JBIG_CODE:
#endif
				/**	送信符号化方式 MR	*/
				TxCodingMethod = SYS_MR_CODE;
				break;
		}
	}
	if ((RxStandardFrameByteCount > 6) &&
		(MDM_ModemBuffer[StdFrmPos][6] & SET_MMR_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT)) {		/**	 DIS/DTC FIF MRRビット ON	*/
		switch (code) {		/**	送信可能コード	*/
			case SYS_MH_CODE:	/**	MH	*/
			case SYS_MR_CODE:	/**	MR	*/
				break;
			case SYS_MMR_CODE:	/**	MMR	*/
			case SYS_MG3_CODE:	/**	松下CODEC 20.Jly'94 Y.Suzuki	*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
			case SYS_JBIG_CODE:
#endif
				if (TxECM_Mode == ECM_ON) {		/**	ECM送信	*/
					/**	送信符号化方式 MMR	*/
					TxCodingMethod = SYS_MMR_CODE;
				}
				break;
		}
	}
#if(PRO_MAKER == MML)
	if ((MakerCodeRxFlag == YES) &&
		(MDM_ModemBuffer[NonStdFrmPos][6] & EXPAND_FIELD_BIT) &&
		(RxNonStandardFrameByteCount > 7)) {		/**	独自フレームチェック	*/
		if (MDM_ModemBuffer[NonStdFrmPos][6] & TTI_ON_BIT) {		/*	NSF/NSC FIF TTIビットON	*/
			/**	独自フレームリードポインター 23 セット	*/
			pos = 7 + 16;
		}
		else {		/**	ＴＴＩなし	*/
			/**	独自フレームリードポインター 7 セット	*/
			pos = 7;
		}
		if (NonStdFrmName == NSC_F) {		/**	NSC	*/
			/*	独自フレームリードポインター +4 セット(パスコードフィールド)	*/
			pos = pos + 4;
		}
		if (CheckMMRinNonStandardFrame(pos) == YES) {		/**	独自MMRビットＯＮ	*/
			switch (code) {		/**	送信可能コード	*/
				case SYS_MH_CODE:	/**	MH	*/
				case SYS_MR_CODE:	/**	MR	*/
					break;
				case SYS_MMR_CODE:	/**	MMR	*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
				case SYS_JBIG_CODE:
#endif
					if (TxECM_Mode == ECM_ON) {		/**	ECM送信	*/
						/**	送信符号化方式 MMR	*/
						TxCodingMethod = SYS_MMR_CODE;
					}
					break;
			}
		}
	}
#else
	if((MilanCodeRxFlag == YES) && (CheckFxPartnerMG3Func() == YES)) {/** MG3 BIT チェック */
		/* 28.Jly'94 Y.Suzuki */
		switch (code) {		/**	送信可能コード	*/
			case SYS_MH_CODE:	/**	MH	*/
			case SYS_MR_CODE:	/**	MR	*/
			case SYS_MMR_CODE:	/**	MMR	*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
			case SYS_JBIG_CODE:
#endif
				break;
			case SYS_MG3_CODE:	/**	MG3	*/
				/**	送信符号化方式 MMR	*/
				TxCodingMethod = SYS_MG3_CODE;
		}
	}
#endif

/*
** 相手がＭＲ・ＥＣＭ Ｏｎの場合、ＭＭＲで送ってしまいますのでこの処理はずします
** 1998/04/09 by T.Soneoka
*/
#if (0)
//#if (PRO_CIPHER == ENABLE)
//	/* 暗号化送信は強制的にＥＣＭで送信する */
//	if ((TxECM_Mode == ECM_ON)
//	 && (CommandFileOptionItem == SYS_CIPHER_TX)) {
//		/**	ECM送信	*/
//		/**	送信符号化方式 MMR	*/
//#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
//		TxCodingMethod = code;
//#else
//		TxCodingMethod = SYS_MMR_CODE;
//#endif
//	}
//#endif
#endif

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	if ((TxECM_Mode == ECM_ON)
	&& (RxStandardFrameByteCount > 12)
	&& (MDM_ModemBuffer[StdFrmPos][12] & JBIG_BIT)
	&& (MDM_ModemBuffer[StdFrmPos][11] & EXPAND_FIELD_BIT)
	&& (jbig_scanner_tx == 1)) {
		switch (code) {		/**	送信可能コード	*/
		case SYS_MH_CODE:	/**	MH	*/
		case SYS_MR_CODE:	/**	MR	*/
		case SYS_MMR_CODE:	/**	MMR	*/
		case SYS_MG3_CODE:	/**	MG3	*/
			break;
		case SYS_JBIG_CODE:
			TxCodingMethod = SYS_JBIG_CODE;
			break;
		}
	}
#endif
	if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {		/**	スキャナ送信 */
		/**	コマンドsrc.d_code に送信符号化方式セット	*/
		SYS_DocBlock.Src.Code = (BYTE)TxCodingMethod;
	}
	/**	コマンドdst.d_code に送信符号化方式セット	*/
	SYS_DocBlock.Dst.Code = (BYTE)TxCodingMethod;
}

/*************************************************************
	module		:[中間調送信線密度確定]
	function	:[
		ＤＩＳのビットと送信能力より中間調送信線密度を確定する
	]
	return		:[]
	common		:[
				RxStandardFrameByteCount
				MDM_ModemBuffer
				StdFrmPos
				TxModeMethod
				ScanTxGrayMode
	]
	condition	:[]
	comment		:[	TxModeMethod にインチ／ミリセット
					ScanTxGrayModeに中間調モードをセット
		修正履歴
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/29]
	author		:[t.yamaguchi]
*************************************************************/
void  SetTxGrayMode(void)
{
#if (PRO_CCD == DPI400)
	/* if(SYS_FaxComTxType == SYS_SCANNER_TX) {/@ 相手の能力、400DPI/ｲﾝﾁ なら 400DPI その他は、FINE 19.Oct'94 */
	if(SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) {
		if (RxStdFrame_HyperFineBitCheck()) {
			/**	送信モードハイパーファイン	*/
			ScanTxGrayMode = SYS_HFINE;
		}
		else if (RxStdFrame_FineBitCheck()) {
			/**	送信モードファイン	*/
			ScanTxGrayMode = SYS_FINE;
		}
		else{
			ScanTxGrayMode = SYS_NORMAL;
		}
	}
	else {	/* メモリ送信 */
		if (RxStdFrame_FineBitCheck()) {
			/**	送信モードファイン	*/
			ScanTxGrayMode = SYS_FINE;
		}
		else{
			ScanTxGrayMode = SYS_NORMAL;
		}
	}
#endif
#if (PRO_CCD == DPI300)	/* ANZU_L E_H_FINE対応 1997/11/11  By T.Yamaguchi */
	if(SYS_FaxComTxType == SYS_SCANNER_TX) {/* 相手の能力、300DPI/ｲﾝﾁ なら 300DPI その他は、FINE 19.Oct'94 */
		if ((Partner300dpiAbility == YES) &&
			(CHK_UNI_ExcellentFIne() == 0)) {
			/**	送信モードハイパーファイン	*/
			ScanTxGrayMode = SYS_E_HFINE;	/* ＳＣＤがE_HFINE対応時ここのコメント外して下さい	*/
/* 			ScanTxGrayMode = SYS_FINE;	*/
		}
		else if ((PartnerEFineAbility == YES) &&
				 (CHK_UNI_ExcellentFIne() != 0)) {
			/**	送信モードファイン	*/
			ScanTxGrayMode = SYS_EFINE;	/* ＳＣＤがE_FINE送信対応時ここのコメントを外して下さい	*/
/*			ScanTxGrayMode = SYS_FINE;	*/
		}
		else if (RxStdFrame_FineBitCheck() == 1) {		/**	DIS/DTC FIF ファインビットON	*/
			/**	送信モードファイン	*/
			ScanTxGrayMode = SYS_FINE;
		}
		else{
			ScanTxGrayMode = SYS_NORMAL;
		}
	}
	else {	/* メモリ送信 */
		if (RxStdFrame_FineBitCheck()) {
			/**	送信モードファイン	*/
			ScanTxGrayMode = SYS_FINE;
		}
		else{
			ScanTxGrayMode = SYS_NORMAL;
		}
	}
#endif
#if (PRO_CCD == DPI200)
	if (RxStdFrame_FineBitCheck() == 1) {		/**	DIS/DTC FIF ファインビットON	*/
			/**	送信モードファイン	*/
		ScanTxGrayMode = SYS_FINE;
	}
	else{
		ScanTxGrayMode = SYS_NORMAL;
	}
#endif
}

/*************************************************************
	module		:[送信線密度確定]
	function	:[
		ＤＩＳのビットと送信能力より送信線密度を確定する
	]
	return		:[
		OK--YES／NG--NO
	]
	common		:[
				TxMode
				GrayModeFlag						:ﾃﾞｨｽﾌﾟﾚｲ表示用、ｼﾞｬｰﾅﾙ表示用ﾌﾗｸﾞ
				FirstTxMode							:初期値 SYS_FINE
				RxStandardFrameByteCount
				MDM_ModemBuffer
				NonStdFrmPos
				SYS_DocBlock.Dst.:Mode				:確定送信線密度
				SYS_DocBlock.:ModeMethod
				Partner300dpiAbility				:相手機,300*400受信
	]
	condition	:[]
	comment		:[	･
					･ポプラはミリでしか送信しない
					･ポプラの中間調メモリ送信はFINEかNORMAL
					･ポプラの中間調スキャナ送信は相手機がH-FINE能力ありならH-FINEで送信
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/02/16]
	author		:[山口 哲治]
*************************************************************/
UBYTE SetTxMode(void)
{
	/*	送信モード NORMAL	*/
	TxMode = SYS_NORMAL;/*	EOM送出の場合のため	*/

	TxModeMethod = SYS_METRIC;	/* ミリにセット */

	SetTxGrayMode();	/** 中間調送信モード確定 */
	/**	中間調フラグ NO	*/
	GrayModeFlag = NO;
	switch (FirstTxMode) {		/**	最初のページのモード */
		case SYS_HFINE:	/**	ハイパーファイン	*/
			if (RxStdFrame_FineBitCheck() == 1) {		/**	DIS/DTC FIF ファインビットON	*/
				/**	送信モードファイン	*/
				TxMode = SYS_FINE;
			}
			if (RxStdFrame_SuperFineBitCheck() == 1) {
				/**	送信モード スーパーファイン	*/
				TxMode = SYS_SFINE;
			}
			if (RxStdFrame_HyperFineBitCheck()) {
/*			if (Partner300dpiAbility == YES) {	*/
				/**	送信モードハイパーファイン	*/
				TxMode = SYS_HFINE;		/* R16*15.4L/mm */
			}
			break;
#if (PRO_CCD == DPI300) /* ソフトコーデック対応のため３００能力追加 1997/11/11  By T.Yamaguchi */
		/* ＡＮＺＵ＿ＬはＥ－ＨＦＩＮＥなし */
		case SYS_E_HFINE: /** ＥＨファイン */
			if (RxStdFrame_FineBitCheck() == 1) {		/**	DIS/DTC FIF ファインビットON	*/
				/**	送信モードファイン	*/
				TxMode = SYS_FINE;
			}
			if (RxStdFrame_SuperFineBitCheck() == 1) {
				/**	送信モード スーパーファイン	*/
				TxMode = SYS_SFINE;
			}
			if (Partner300dpiAbility == YES) {
				/**	送信モードエクセレントハイパーファイン	*/
				TxMode = SYS_E_HFINE;		/* R12*15.4L/mm */
			}
			break;
		/* ポプラ／ＡＮＺＵ＿ＬはＥ－ＦＩＮＥなし */
		case SYS_EFINE: /** エクセレントファイン */
			if (RxStdFrame_FineBitCheck() == 1) {		/**	DIS/DTC FIF ファインビットON	*/
				/**	送信モードファイン	*/
				TxMode = SYS_FINE;
			}
			if (PartnerEFineAbility == YES) {
				/**	送信モードエクセレントファイン	*/
				TxMode = SYS_EFINE;		/* R12*11.55L/mm */
			}
			break;
#endif
		case SYS_SFINE:	/**	スーパーファイン	*/
			if (RxStdFrame_FineBitCheck() == 1) {		/**	DIS/DTC FIF ファインビットON	*/
				/**	送信モードファイン	*/
				TxMode = SYS_FINE;
			}
			if (RxStdFrame_SuperFineBitCheck() == 1) {
				/**	送信モード スーパーファイン	*/
				TxMode = SYS_SFINE;
			}
			break;
		case SYS_FINE:				/**	ファイン		*/
		case SYS_GRAY16:			/**	中間調16		*/
		case SYS_GRAY16_SEP:		/**	中間調16_SEP	*/
		case SYS_GRAY32:			/**	中間調32		*/
		case SYS_GRAY32_SEP:		/**	中間調32_SEP	*/
		case SYS_GRAY64:			/**	中間調64		*/
		case SYS_GRAY64_SEP:		/**	中間調64_SEP	*/
		case SYS_GRAY128:
		case SYS_GRAY128_SEP:
		/* 皐月:32階調　桐紅葉ラベンダーＡＮＺＵ:64階調 */
			if(FirstTxMode != SYS_FINE) {	/** 中間調なら */
				TxMode = ScanTxGrayMode;
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
				if ((ScanTxGrayMode != SYS_FINE) && (ScanTxGrayMode != SYS_NORMAL)) {	
					FirstTxMode = SYS_HGRAY;
				}
#endif
				/**	中間調フラグ ON	*/
				GrayModeFlag = YES;			/** 相手機がFINEの能力がない場合はNORMALで送る(表示は中間調)	*/
			}
			else {					/** ファイン		*/
				if (RxStdFrame_FineBitCheck() == 1) {		/**	DIS/DTC FIF ファインビットON	*/
					/**	送信モードファイン	*/
					TxMode = SYS_FINE;
				}
			}
			break;
		case SYS_NORMAL:	/**	ノーマル	*/
			TxMode = SYS_NORMAL;/* 9.Mar'94 */
			break;
		default:
			return(NO);
	}

#if (0) /* ポプラ／ＡＮＺＵ＿Ｌはミリのみ(PRO_HQ_MODE == ENABLE) */
** 	if ((CHK_UNI_Inch_TRx()) &&	/* インチ送信能力ありの時 且つ インチビットＯＮ */
** 		(RxStdFrame_InchBitOnCheck() != 0)) {
** 		switch (TxMode) {
** 			case SYS_FINE:
** /*			case SYS_OFINE:			/@ FINE,O-FINEモードなら */
** 				/**	インチ／ミリビットにインチセット（インチに変換）	*/
** 				TxModeMethod = SYS_INCH;
** 				break;
** 			case SYS_NORMAL:
** 			case SYS_SFINE:
** 			case SYS_HFINE:
** 				if (RxStdFrame_MiliBitOnCheck() == 0) { /* インチビットがＯＮ、且つ ミリビットＯＦＦ */
** 					/**	インチ／ミリビットにインチセット（インチに変換）	*/
** 					TxModeMethod = SYS_INCH;
** 				}
** 				break;
** 		}
** 	}
** 	else {
** 		TxModeMethod = SYS_METRIC;
** 	}
#endif

#if (0) /* ANZUはＭＳＥ１能力しかないので削除 By t.yamaguchi */
** 	/* ノーマルモード以外では、SMSE　は無効 27.Sep'94 */
** 	if((TxMode != SYS_NORMAL) && (TxMSE_Method == SMSE)) {
** 		TxMSE_Method = MSE1;
** 		SYS_DocBlock.MSE_Method = MSE1;
** 	}
#endif

	/**	コマンドdst。d_modeに送信モードセット	*/
	SYS_DocBlock.Dst.Mode = TxMode;

	SYS_DocBlock.ModeMethod = TxModeMethod; /* ANZUの場合はミリ／インチ変換可能なので残しておく */

	return(YES);
}

/*************************************************************
	module		:[送信原稿長を確定する]
	function	:[
		ＤＩＳ／ＤＣＳのビットと送信能力より原稿長を確定する
	]
	return		:[なし]
	common		:[
				MDM_ModemBuffer
				StdFrmPos
				FaxTxMaxLength
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[鈴木 郁二]
*************************************************************/
void SetTxPaperLength(void)
{
	switch (MDM_ModemBuffer[StdFrmPos][5] & MASK_RX_LENGTH_BIT) {		/**	DIS 記録紙長ビットチェック	*/
		case LENGTH_A4_BIT:	/**	A4の記録紙長	*/
			/**	確定送信長　A4	*/
			FaxTxMaxLength = SYS_A4_LENGTH;
			break;
		case LENGTH_B4_BIT:	/**	B4の記録紙長	*/
			/**	確定送信長　B4	*/
			FaxTxMaxLength = SYS_B4_LENGTH;
			break;
		case LENGTH_UNLIMITED_BIT:	/**	無限長	*/
		default:
			/**	確定送信長　無限長	*/
			FaxTxMaxLength = SYS_NO_LIMIT;
	}
#if (PRO_RELAYED_REPORT == ENABLE) /* Changed by H.Kubo 1998/01/19 */
	if (CommandFileOptionItem == SYS_RELAYED_TX_REPORT) {/**		*/
		if (FaxTxMaxLength == SYS_NO_LIMIT) {
			FaxTxMaxLength = CHK_RelayedTxReportPaperLength();
		}
		else if (FaxTxMaxLength == SYS_B4_LENGTH) {
			if (CHK_RelayedTxReportPaperLength() == SYS_A4_LENGTH) {
				FaxTxMaxLength = SYS_A4_LENGTH;
			}
		}
	}
#endif
}


/*************************************************************
	module		:[送信時線密度をチェックする]
	function	:[
		送信時確定線密度がファインであることを確認する
	]
	return		:[
		確定線密度がファイン---YES／確定線密度ファインではない---NO
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
UBYTE  CheckTxModeUpperFine(void)
{
	switch (TxMode) {		/**	確定送信モード	*/
		case SYS_NORMAL:	/**	ノーマル	*/
			return(NO);
		case SYS_SFINE:		/* ANZUにも対応 */
		case SYS_HFINE:
		case SYS_EFINE:		/* 96/06/15 By T.Yamaguchi */
			return(2);	/* 23.Jun'94 Y.Suzuki */
		default:		/**	ノーマル以外	*/
			return(YES);
	}
}


/*************************************************************
	module		:[ＤＩＳのビットと送信能力より最少電送時間を確定する]
	function	:[
		最少電送時間を確定する
		高解像度の最少走査線時間能力の確定追加 23.Jun'94
	]
	return		:[
		確定--YES/ＮＧ--NO
	]
	common		:[
				MDM_ModemBuffer
				StdFrmPos
				SYS_FaxComTxType
				TxMinimumScanningTime
				AvailableTxMinimumScanningTime
	]
	condition	:[]
	comment		:[AvailableTxMinimumScanningTime 桐--０ｍｓ　他--プリンタの能力(20ms)]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[鈴木 郁二]
*************************************************************/
void SetTxMinimumCommunicationTime(void)
{
	UBYTE fine_f;
	UBYTE speed_flag;

	speed_flag = 0;
	fine_f = 0;

	/**	ファインフラグ(ローカル変数)セット	*/
	fine_f = CheckTxModeUpperFine();/* Fine : 1,S_Fine H_Fine : 2 */
	if((MDM_ModemBuffer[StdFrmPos][8] & HIGH_SCAN_TIME_BIT) && /* 拡張ビットも同時にチェックする 28.Jly'94 Y.Suzuki */
		(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	標準フレームミリビットONかつインチビットOFF	*/
		speed_flag = YES;
	}
	/* 3Line 追加ＰＯＰＬＡＲ 1997/07/14  By T.Yamaguchi */
	if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {	/**	メモリ送信	*/
		/* メモリ送信の場合は０ｍｓにする 1997/07/14  By T.Yamaguchi */
		AvailableTxMinimumScanningTime = SCAN_MINIMUM_TIME0;
	}
	switch (MDM_ModemBuffer[StdFrmPos][5] & MASK_MINIMUM_SCANNING_TIME) {		/**	DIS/DTC FIF 最少伝送時間ビットチェック	*/
		case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
			if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {		/**	メモリ送信	*/
		/*	if (SYS_FaxComTxType == SYS_MEMORY_TX) {			/@@	メモリ送信	*/
				/**	最少伝送時間0ms	*/
				TxMinimumScanningTime = SCAN_MINIMUM_TIME0;
				break;
			}
			else {		/**	メモリ送信ではない	*/
				switch (AvailableTxMinimumScanningTime) {		/**	送信可能最少伝送時間	*/
					case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
					case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
					case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
					case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
					case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
						/**	最少伝送時間にTIME0,5,10,20,40セット	*/
						TxMinimumScanningTime = AvailableTxMinimumScanningTime;
						break;
					case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
						if (fine_f) {		/**	ファイン	*/
							/**	最少伝送時間5ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME5;
						}
						else {		/**	ノーマル	*/
							/**	最少伝送時間10ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
						}
						break;
					case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
						if (fine_f) {		/**	ファイン	*/
							/**	最少伝送時間10ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
						}
						else {		/**	ノーマル	*/
							/**	最少伝送時間20ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
						}
						break;
					case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
						if (fine_f) {		/**	ファイン	*/
							/**	最少伝送時間20ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
						}
						else {		/**	ノーマル	*/
							/**	最少伝送時間40ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
						}
						break;
				}
			}
			break;
		case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
			switch (AvailableTxMinimumScanningTime) {		/**	送信可能最少伝送時間	*/
				case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
				case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
				case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
					/**	最少伝送時間に送信可能最少伝送時間セット	*/
					TxMinimumScanningTime = AvailableTxMinimumScanningTime;
					break;
				case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
				case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
				case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
						if (fine_f) {		/**	ファイン	*/
							/**	最少伝送時間5ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME5;
						}
						else {		/**	ノーマル	*/
							/**	最少伝送時間10ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
						}
						break;
				case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
						if (fine_f) {		/**	ファイン	*/
							/**	最少伝送時間10ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
						}
						else {		/**	ノーマル	*/
							/**	最少伝送時間20ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
						}
						break;
				case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
						if (fine_f) {		/**	ファイン	*/
							/**	最少伝送時間20ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
						}
						else {		/**	ノーマル	*/
							/**	最少伝送時間40ms	*/
							TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
						}
						break;
			}
			break;
		case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
			switch (AvailableTxMinimumScanningTime) {		/**	送信可能最少伝送時間	*/
				case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
				case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
					/**	最少伝送時間にTIME20,40セット	*/
					TxMinimumScanningTime = AvailableTxMinimumScanningTime;
					break;
				case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
				case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
				case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
					if((fine_f == 2) && (speed_flag == YES)) {
						TxMinimumScanningTime = SCAN_MINIMUM_TIME5;
					}
/*					if (fine_f) {		@	ファイン	96/4/16 Y.Suzuki */
/*					else if (fine_f == 1) {		/**	ファイン	*/
					else if ((fine_f == 1) || (fine_f == 2)) {		/**	ファインとS,H-FINE1997/07/18  By T.Yamaguchi	*/
						/**	最少伝送時間10ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
					}
					else {		/**	ノーマル	*/
						/**	最少伝送時間20ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					break;
				case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
				case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
					if (fine_f) {		/**	ファイン or S-FINE or H-FINE	*/
						/**	最少伝送時間10ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
					}
					else {		/**	ノーマル	*/
						/**	最少伝送時間20ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					break;
				case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
					if (fine_f) {		/**	ファイン	*/
						/**	最少伝送時間20ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					else {		/**	ノーマル	*/
						/**	最少伝送時間40ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
					}
					break;
			}
			break;
		case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
			switch (AvailableTxMinimumScanningTime) {		/**	送信可能最少伝送時間	*/
				case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
					/**	最少伝送時間にTIME40時間セット	*/
					TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
					break;
				case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
				case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
				case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
				case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
				case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
				case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
					if((fine_f == 2) && (speed_flag == YES)) {
						TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
					}
/*					if (fine_f) {		@*	ファイン	96/4/16 Y.Suzuki */
/*					else if (fine_f == 1) {		/**	ファイン	*/
					else if ((fine_f == 1) || (fine_f == 2)) {		/**	ファインとS,H-FINE1997/07/18  By T.Yamaguchi	*/
						/**	最少伝送時間20ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					else {		/**	ノーマル	*/
						/**	最少伝送時間40ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
					}
					break;
				case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
					if (fine_f) {		/**	ファイン or S-FINE or H-FINE	*/
						/**	最少伝送時間20ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					else {		/**	ノーマル	*/
						/**	最少伝送時間40ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
					}
					break;
			}
			break;
		case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
			switch (AvailableTxMinimumScanningTime) {		/**	送信可能最少伝送時間	*/
				case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
					/**	最少伝送時間TIME5	*/
					TxMinimumScanningTime = SCAN_MINIMUM_TIME5;
					break;
				case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
				case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
				case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
				case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
					/**	最少伝送時間にTIME5,10,20,40セット	*/
					TxMinimumScanningTime = AvailableTxMinimumScanningTime;
					break;
				case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
					if (fine_f) {		/**	ファイン	*/
						/**	最少伝送時間5ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME5;
					}
					else {		/**	ファインフラグNO	*/
						/**	最少伝送時間10ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
					}
					break;
				case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
					if (fine_f) {		/**	ファイン	*/
						/**	最少伝送時間10ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
					}
					else {		/**	ノーマル	*/
						/**	最少伝送時間20ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					break;
				case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
					if (fine_f) {		/**	ファイン	*/
						/**	最少伝送時間20ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					else {		/**	ノーマル	*/
						/**	最少伝送時間40ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
					}
					break;
			}
			break;
		case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
			switch (AvailableTxMinimumScanningTime) {		/**	送信可能最少伝送時間	*/
				case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
				case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
				case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
					/**	最少伝送時間にTIME10,20,40セット	*/
					TxMinimumScanningTime = AvailableTxMinimumScanningTime;
					break;
				case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
				case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
				case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
					/* 15.4 l/mm T = 1/2 7.7 l/mm T 追加 20.Jly'94 Y.Suzuki */
					if((fine_f == 2) && (speed_flag == YES)) {
						/**	最少伝送時間TIME5	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME5;
					}
					else {
						/**	最少伝送時間TIME10	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
					}
					break;
				case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
					if (fine_f) {		/**	ファイン	*/
						/**	最少伝送時間10ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
					}
					else {		/**	ノーマル	*/
						/**	最少伝送時間20ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					break;
				case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
					if (fine_f) {		/**	ファイン	*/
						/**	最少伝送時間20ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					else {		/**	ノーマル	*/
						/**	最少伝送時間40ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
					}
					break;
			}
			break;
		case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
			switch (AvailableTxMinimumScanningTime) {		/**	送信可能最少伝送時間	*/
				case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
				case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
					/**	最少伝送時間にTIME20,40	*/
					TxMinimumScanningTime = AvailableTxMinimumScanningTime;
					break;
				case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
				case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
				case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
				case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
				case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
					/* 15.4 l/mm T = 1/2 7.7 l/mm T 追加 20.Jly'94 Y.Suzuki */
					if((fine_f == 2) && (speed_flag == YES)) {
						/**	最少伝送時間TIME10	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME10;
					}
					else {
						/**	最少伝送時間TIME20	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					break;
				case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
					if (fine_f) {		/**	ファイン	*/
						/**	最少伝送時間20ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					else {		/**	ノーマル	*/
						/**	最少伝送時間40ms	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
					}
					break;
			}
			break;
		case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
			switch (AvailableTxMinimumScanningTime) {		/**	送信可能最少伝送時間	*/
				case SCAN_MINIMUM_TIME0:	/**	TIME0	*/
				case SCAN_MINIMUM_TIME5:	/**	TIME5	*/
				case SCAN_MINIMUM_TIME10:	/**	TIME10	*/
				case SCAN_MINIMUM_TIME20:	/**	TIME20	*/
				case SCAN_MINIMUM_TIME10_2:	/**	TIME10_2	*/
				case SCAN_MINIMUM_TIME20_2:	/**	TIME20_2	*/
				case SCAN_MINIMUM_TIME40_2:	/**	TIME40_2	*/
					/* 15.4 l/mm T = 1/2 7.7 l/mm T 追加 20.Jly'94 Y.Suzuki */
					if((fine_f == 2) && (speed_flag == YES)) {
						/**	最少伝送時間TIME20	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME20;
					}
					else {
						/**	最少伝送時間TIME40	*/
						TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
					}
					break;
				case SCAN_MINIMUM_TIME40:	/**	TIME40	*/
					/**	最少伝送時間TIME40	*/
					TxMinimumScanningTime = SCAN_MINIMUM_TIME40;
					break;
			}
			break;
		default:
			;/*return(NO);*/
	}
}


/*************************************************************
	module		:[SetTxECM_Mode()]
	function	:[
		送信側ECMモードありなしを確定
		1.ＤＩＳのＥＣＭビットチェック
		2.ＥＣＭ送信能力確認
		3.フレームサイズセット
	]
	return		:[]
	common		:[
		TxECM_Mode
		FaxComResult
		fcom_ecmsize
		RxStandardFrameByteCount
		MDM_ModemBuffer
	]
	condition	:[]
	comment		:[
		ラベンダーには、ECMなし仕様がある 村田仕様は、フレームサイズ256バイトのみ ECMなしとの区別（条件コンパイル）は、送信可能ECMモードをセットするところで記述する
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[鈴木 郁二]
*************************************************************/
void SetTxECM_Mode(void)
{
	/**	交信結果ECMなし	*/
	FaxComResult &= ~ECM_MODE_SET;

	if (RxStdFrame_ECMAbilityCheck()) {		/* 受信フレームＥＣＭ能力解析 */
		if (TxECM_Ability == ECM_ON) {		/**	送信側ECM能力あり	*/
			/**	確定ECMモード ON*/
			TxECM_Mode = ECM_ON;
			/**	交信結果ECMあり	*/
			FaxComResult |= ECM_MODE_SET;

			/* ＤＩＳの宣言には２５６／６４の指定はなく０固定なので２５６　ＯＣＴ　をセット '95.11.22 By T.yamaguchi */
			/**	ECMフレームサイズ256セット	*/
			FcomEcmSize = ECM_256_OCT;
		}
	}
	else {
		if (SYS_V34ProcedureExecuting()) {	/* V34なら強制的にECMｵﾝ 1996/05/30 Y.M */
#if (PRO_TX_SPEED == V34) /* Modified by H.Kubo 1997/08/06 */
			TxECM_Mode = ECM_ON;
			/**	交信結果ECMあり	*/
			FaxComResult |= ECM_MODE_SET;
			/**	ECMフレームサイズ256セット	*/
			FcomEcmSize = ECM_256_OCT;
#endif /* (PRO_TX_SPEED == V34) */
		}
		else {
			TxECM_Mode = ECM_OFF;/* SpeedHandshake送信時必須 25.May'94 Y.Suzuki */
		}
	}
}

/*************************************************************
	module		:[送信ＭＳＥモード確定]
	function	:[
		ＮＳＦ／ＮＳＣのビットと送信能力より送信側MSEモードを確定する
	]
	return		:[]
	common		:[
		MDM_ModemBuffer				:
		NonStdFrmPos				:
		TxMSE_Method				:確定MSE方式
		AvailableTxMSE_Method		:送信MSE能力
		SYS_DocBlock.:MSE_Method	:
		TxModeMethod
	]
	condition	:[]
	comment		:[ANZU用に変更
				  (SMSE,MSE2の能力はないので削除) By T.Y ]
				  ポプラもＳＭＳＥ送信能力なし（ｿﾌﾄｺｰﾃﾞｯｸは可能性はあるが対応しない）
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/29]
	author		:[t.yamguchi]
*************************************************************/
void SetTxMSE_Mode(void)
{
	if (SYS_FaxComTxType != SYS_SCANNER_TRANSMIT) {/**	メモリ送信 ＲＣＲ送信時もとおる	*/
/*	if (SYS_FaxComTxType != SYS_SCANNER_TX) {	1996/11/28	By T.Yamaguchi /@@	メモリ送信	*/
		AvailableTxMSE_Method = MSE1;
	}
	switch (AvailableTxMSE_Method) {		/**	送信側 MSE能力	ANZUはMSE1しかない*/
		case MSE1:	/**	MSE1	*/
			switch (MDM_ModemBuffer[NonStdFrmPos][6] & MASK_MSE_MODE) {		/**	NSF／NSCフレームMSEビットチェック	*/
				case MSE1_MODE_BIT:	/**	MSE1	*/
				case MSE2_MODE_BIT:	/**	MSE2	*/
				case SMSE_MODE_BIT:	/**	SMSE	*/
				case 0x0C:			/**	MSE1+MSE2	*/
				case MSE1_SMSE_MODE_BIT:	/**	MSE1+SMSE	*/
				case 0x48:			/**	MSE2+SMSE	*/
				case 0x4C:			/**	MSE1+MSE2+SMSE	*/
					/**	MSE1確定	*/
					TxMSE_Method = MSE1;
					break;
				default:
					/**	MSEなし確定	*/
					TxMSE_Method = NOMSE;
					break;
			}
			break;
		case NOMSE:	/**	MSEなし	*/
		default:
			/**	MSEなし確定	*/
			TxMSE_Method = NOMSE;
			break;
	}
	/**	コマンドmse_method に確定MSEモードをセット	*/
	SYS_DocBlock.MSE_Method = (UBYTE)TxMSE_Method;
}

#if 0	/* ↑に変更 ANZU用 */
/*************************************************************
	module		:[送信ＭＳＥモード確定]
	function	:[
		ＮＳＦ／ＮＳＣのビットと送信能力より送信側MSEモードを確定する
	]
	return		:[]
	common		:[
		MDM_ModemBuffer				:
		NonStdFrmPos				:
		TxMSE_Method				:確定MSE方式
		AvailableTxMSE_Method		:送信MSE能力
		SYS_DocBlock.:MSE_Method	:
		TxModeMethod
	]
	condition	:[]
	comment		:[MSE2の能力はないので削除 By T.Y ]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[鈴木 郁二]
*************************************************************/
void  SetTxMSE_Mode(void)
{
	if (SYS_FaxComTxType != SYS_SCANNER_TRANSMIT) {/**	メモリ送信 ＲＣＲ送信時もとおる	*/
/*	if (SYS_FaxComTxType != SYS_SCANNER_TX) {	1996/11/28	By T.Yamaguchi	メモリ送信	*/
		AvailableTxMSE_Method = MSE1;
	}
	switch (MDM_ModemBuffer[NonStdFrmPos][6] & MASK_MSE_MODE) {		/**	NSF／NSCフレームMSEビットチェック	*/
		case NOMSE:	/**	MSEなし	*/
			/**	MSEなし確定	*/
			TxMSE_Method = NOMSE;
			break;
		case MSE1_MODE_BIT:	/**	MSE1	*/
			switch (AvailableTxMSE_Method) {		/**	送信側MSE能力	*/
				case NOMSE:	/**	MSEなし	*/
					/**	MSEなし確定	*/
					TxMSE_Method = NOMSE;
					break;
				case MSE1:	/**	MSE1	*/
				case MSE2:	/**	MSE2	*/
				case SMSE:	/**	SMSE	*/
					/**	MSE1確定	*/
					TxMSE_Method = MSE1;
					break;
			}
			break;
		case MSE2_MODE_BIT:	/**	MSE2	*/
			switch (AvailableTxMSE_Method) {		/**	送信側MSE能力	*/
				case NOMSE:	/**	MSEなし	*/
					/**	MSEなし確定	*/
					TxMSE_Method = NOMSE;
					break;
				case MSE1:	/**	MSE1	*/
					/**	MSE1確定	*/
					TxMSE_Method = MSE1;
					break;
				case SMSE:	/**	SMSE	*/
					/**	SMSE確定	*/
					TxMSE_Method = SMSE;
					break;
			}
			break;
		case SMSE_MODE_BIT:	/**	SMSE	*/
			switch (AvailableTxMSE_Method) {		/**	送信側MSE能力	*/
				case  NOMSE:	/**	MSEなし	*/
					/**	MSEなし確定	*/
					TxMSE_Method = NOMSE;
					break;
				case MSE1:	/**	MSE1	*/
					/**	MSE1確定	*/
					TxMSE_Method = MSE1;
					break;
				case SMSE:	/**	SMSE	*/
					/**	SMSE確定	*/
					TxMSE_Method = SMSE;
					break;
			}
			break;
		case 0x0C:	/**	MSE1+MSE2	*/
			switch (AvailableTxMSE_Method) {		/**	送信側MSE能力	*/
				case NOMSE:	/**	MSEなし	*/
					/**	MSEなし確定	*/
					TxMSE_Method = NOMSE;
					break;
				case MSE1:	/**	MSE1	*/
					/**	MSE1確定	*/
					TxMSE_Method = MSE1;
					break;
				case SMSE:	/**	SMSE	*/
					/**	MSE2確定	*/
					TxMSE_Method = MSE1;/*MSE2;*/
					break;
			}
			break;
		case 0x44:	/**	MSE1+SMSE	*/
			switch (AvailableTxMSE_Method) {		/**	送信側MSE能力	*/
				case NOMSE:	/**	MSEなし	*/
					/**	MSEなし確定	*/
					TxMSE_Method = NOMSE;
					break;
				case MSE1:	/**	MSE1	*/
					TxMSE_Method = MSE1;
					break;
				case SMSE:	/**	SMSE	*/
					/**	SMSE確定	*/
					TxMSE_Method = SMSE;
					break;
			}
			break;
		case 0x48:	/**	MSE2+SMSE	*/
			switch (AvailableTxMSE_Method) {		/**	送信側MSE能力	*/
				case NOMSE:	/**	MSEなし	*/
				case MSE1:	/**	MSE1	*/
					/**	MSEなし確定	*/
					TxMSE_Method = NOMSE;
					break;
				case SMSE:	/**	SMSE	*/
					/**	SMSE確定	*/
					TxMSE_Method = SMSE;
					break;
			}
			break;
		case 0x4C:	/**	MSE1+MSE2+SMSE	*/
			switch (AvailableTxMSE_Method) {		/**	送信側MSE能力	*/
				case NOMSE:	/**	MSEなし	*/
					/**	MSEなし確定	*/
					TxMSE_Method = NOMSE;
					break;
				case MSE1:	/**	MSE1	*/
					/**	MSE1確定	*/
					TxMSE_Method = MSE1;
					break;
				case SMSE	:	/**	SMSE	*/
					/**	SMSE確定	*/
					TxMSE_Method = SMSE;
					break;
			}
			break;
		default:
			/**	MSEなし確定	*/
			TxMSE_Method = NOMSE;
			break;
	}
	/**	コマンドmse_method に確定MSEモードをセット	*/
	SYS_DocBlock.MSE_Method = (UBYTE)TxMSE_Method;
}
#endif

/*************************************************************
	module		:[送信原稿幅確定]
	function	:[
		送信側原稿幅を確定する
	]
	return		:[
		原稿幅確定 YES／原稿幅確定できず NO
	]
	common		:[
		MDM_ModemBuffer				:
		DocWidth					:
		TxWidth						:
		SYS_DocBlock.Dst.:Size		:確定送信原稿幅
	]
	condition	:[]
	comment		:[ロール紙(さつき)とカット紙(桐)共通にする？
				桐、紅葉ーA3 B4 A4	さつき、ラベンダーーB4 A4
				紅葉、皐月－ロール紙　桐、ラベンダー－カセット
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/24]
	author		:[鈴木 郁二]
*************************************************************/
UBYTE SetTxPaperWidth(void)
{
	switch (MDM_ModemBuffer[StdFrmPos][5] & RX_ALL_PAPER_BIT) {		/**	ＤＩＳ／ＤＴＣ 記録幅ビットチェック	*/
		case RX_A4_PAPER_BIT:	/**	記録紙A4	*/
			switch (DocWidth) {		/**	原稿幅	*/
				/*	皐月、ラベンダーは、Ａ３がセットされることはないはず	*/
				case SYS_DOCUMENT_A4_SIZE:	/**	A4	*/
				case SYS_DOCUMENT_B4_SIZE:	/**	B4	*/
				case SYS_DOCUMENT_A3_SIZE:	/**	A3	*/
					/**	確定原稿幅 A4	*/
					TxWidth = SYS_DOCUMENT_A4_SIZE;
					break;
			}
			break;
		case RX_B4_PAPER_BIT:	/**	記録紙B4	*/
			switch (DocWidth) {		/**	原稿幅	*/
				case SYS_DOCUMENT_A4_SIZE:	/**	A4	*/
					/**	確定原稿幅 A4	*/
					TxWidth = SYS_DOCUMENT_A4_SIZE;
					break;
				case SYS_DOCUMENT_B4_SIZE:	/**	B4	*/
				case SYS_DOCUMENT_A3_SIZE:	/**	A3	*/
					/**	確定原稿幅 B4	*/
					TxWidth = SYS_DOCUMENT_B4_SIZE;
					break;
			}
			break;
		case RX_A3_PAPER_BIT:	/**	記録紙A3	*/
		case RX_ALL_PAPER_BIT:	/**	A4、B4,A3	*/
			switch (DocWidth) {		/**	原稿幅	*/
				case SYS_DOCUMENT_A4_SIZE:	/**	A4	*/
					/**	確定原稿幅 A4	*/
					TxWidth = SYS_DOCUMENT_A4_SIZE;
					break;
				case SYS_DOCUMENT_B4_SIZE:	/**	B4	*/
					/**	確定原稿幅 B4	*/
					TxWidth = SYS_DOCUMENT_B4_SIZE;
					break;
				case SYS_DOCUMENT_A3_SIZE:	/**	A3	*/
					/**	確定原稿幅 A3	*/
					TxWidth = SYS_DOCUMENT_A3_SIZE;
					break;
			}
			break;
		default:
			return(NO);
	}
	/**	コマンド.dst.d_sizeに確定原稿幅セット	*/
	SYS_DocBlock.Dst.Size = (BYTE)TxWidth;
	return (YES);
}



/*************************************************************************
	module		:[相手機ﾊｲﾊﾟｰﾌｧｲﾝ受信能力ﾁｪｯｸ]
	function	:[
		1.
	]
	return		:[]
	common		:[	RxStandardFrameByteCount
					MDM_ModemBuffer
					TxMode
				 ]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/29]
	author		:[山口]
*************************************************************************/
UBYTE		RxStdFrame_HyperFineBitCheck(void)
{
	if ((RxStandardFrameByteCount > 8) &&
/*		(MDM_ModemBuffer[StdFrmPos][8] & METRIC_BASE_BIT) &&	/@ Del 1997/01/13  By T.Yamaguchi */
		(MDM_ModemBuffer[StdFrmPos][8] & HYPER_FINE_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	DIS/DTC FIF ハイパーファインビットON	*/
		/**	送信モードハイパーファイン	*/
		return(1);
	}
	else {
		return(0);
	}
}
/*************************************************************************
	module		:[相手機ｱｻﾞｰﾌｧｲﾝ受信能力ﾁｪｯｸ]
	function	:[
		1.
	]
	return		:[]
	common		:[	RxStandardFrameByteCount
					MDM_ModemBuffer
					TxMode
				 ]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/29]
	author		:[山口]
*************************************************************************/
UBYTE		RxStdFrame_OtherFineBitCheck(void)
{
	if ((RxStandardFrameByteCount > 8) &&
		(MDM_ModemBuffer[StdFrmPos][8] & OTHER_FINE_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	DIS/DTC FIF ハイパーファインビットON	*/
		/**	送信モードハイパーファイン	*/
		return(1);
	}
	else {
		return(0);
	}
}
/*************************************************************************
	module		:[相手機ｽｰﾊﾟｰﾌｧｲﾝ受信能力ﾁｪｯｸ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/29]
	author		:[山口]
*************************************************************************/
UBYTE		RxStdFrame_SuperFineBitCheck(void)
{
	if ((MakerCodeRxFlag == YES) &&
		(RxNonStandardFrameByteCount > 6) &&
		(MDM_ModemBuffer[NonStdFrmPos][6] & SFINE_MODE_BIT)) {		/**	相手機MML機でかつ独自フレーム受信バイト数 7 バイト以上でかつ独自 スーパーファインビットON	*/
		/**	送信モード スーパーファイン	*/
		return(1);
	}
	if ((RxStandardFrameByteCount > 8) &&
		(MDM_ModemBuffer[StdFrmPos][8] & SUPER_FINE_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT)) {		/**	標準フレーム受信バイト数 9 バイト以上でかつ DIS/DTC FIF	 スーパーファインビットON	*/
		/**	送信モード スーパーファイン	*/
		return(1);
	}
	else {
		return(0);
	}
}

/*************************************************************************
	module		:[相手機ﾌｧｲﾝ受信能力ﾁｪｯｸ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/29]
	author		:[山口]
*************************************************************************/
UBYTE		RxStdFrame_FineBitCheck(void)
{
	if ((RxStandardFrameByteCount > 4) &&
		(MDM_ModemBuffer[StdFrmPos][4] & SET_FINE_BIT)) {		/**	DIS/DTC FIF ファインビットON	*/
		/**	送信モードファイン	*/
		return(1);
	}
	else {
		return(0);
	}
}

#if 0
/*************************************************************************
	module		:[相手機インチ送受信能力ﾁｪｯｸ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/29]
	author		:[山口]
*************************************************************************/
UBYTE		RxStdFrame_InchBitOnCheck(void)
{
	if ((RxStandardFrameByteCount > 8) &&
		((MDM_ModemBuffer[StdFrmPos][8] & INCH_BASE_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT))) {		/**	標準フレームミリビットONかつインチビットOFF	*/
		return(1);
	}
	else {
		return(0);
	}
}
#endif

/*************************************************************************
	module		:[相手機ミリ受信能力ﾁｪｯｸ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/29]
	author		:[山口]
*************************************************************************/
UBYTE		RxStdFrame_MiliBitOnCheck(void)
{
	if ((RxStandardFrameByteCount > 8) &&
		((MDM_ModemBuffer[StdFrmPos][8] & METRIC_BASE_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][6] & EXPAND_FIELD_BIT) &&
		(MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT))) {		/**	標準フレームミリビットONかつインチビットOFF	*/
		return(1);
	}
	else {
		return(0);
	}
}

/*************************************************************************
	module		:[相手機ECM通信能力ﾁｪｯｸ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/12/02]
	author		:[山口]
*************************************************************************/
UBYTE		RxStdFrame_ECMAbilityCheck(void)
{
	if ( (RxStandardFrameByteCount > 6)
	   &&(MDM_ModemBuffer[StdFrmPos][6] & ECM_MODE_BIT)
	   &&(MDM_ModemBuffer[StdFrmPos][5] & EXPAND_FIELD_BIT) ) {		/**	DCS ECMビットON	*/
		return(1);
	}
	return(0);
}

/*************************************************************
	module		:[暗号化送信確定]
	function	:[
		暗号化送信可能かを確定する
	]
	return		:[
		送信可能 YES／送信不可 NO
	]
	common		:[
	]
	condition	:[]
	comment		:[暗号化送信可能なケースは、ＥＣＭ送信で、モードNORMAL,FINE
				送信原稿Ｂ４、Ａ４でサイズ変更なしの場合のみ
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/06/18]
	author		:[山口 哲治]
*************************************************************/
UBYTE CheckCipherTx(void)
{
#if (PRO_CIPHER == ENABLE)
	/* ＥＣＭ送信 */
	if (TxECM_Mode != ECM_ON) {
		FaxCompatibleErrorCode = CIPHER_ECM_ERROR;
		return (NO);
	}
	/* 送信モード */
	if (FirstTxMode != TxMode) {
		if (GrayModeFlag != YES) {		/* 中間調でない */	/* 1997/12/08  By T.Yamaguchi */
			FaxCompatibleErrorCode = CIPHER_MODE_ERROR;
			return (NO);
		}
		else {
			if (TxMode != SYS_FINE) {	/* 中間調で解像度がＦＩＮＥでないなら */
				FaxCompatibleErrorCode = CIPHER_MODE_ERROR;
				return (NO);
			}
		}
	}
	/* 送信モード ＮＯＲＭＬ，ＦＩＮＥのみ */
	if ((TxMode != SYS_NORMAL)
	 && (TxMode != SYS_FINE)) {
		FaxCompatibleErrorCode = CIPHER_MODE_ERROR;
		return (NO);
	}
	/* 原稿幅 */
	if (DocWidth != TxWidth) {
		FaxCompatibleErrorCode = CIPHER_SIZE_ERROR;
		return (NO);
	}
	/* 原稿幅、Ａ４、Ｂ４ のみ */
	if ((TxWidth != SYS_DOCUMENT_A4_SIZE)
	 && (TxWidth != SYS_DOCUMENT_B4_SIZE)) {
		FaxCompatibleErrorCode = CIPHER_SIZE_ERROR;
		return (NO);
	}
#endif
	return (YES);
}

/*************************************************************
	module		:[ＤＩＳのＴ４能力チェックする]
	function	:[
		ＤＩＳ２バイト目の受信能力をチェックする
	]
	return		:[
		送信可能 YES／送信不可 NO
	]
	common		:[
	]
	condition	:[]
	comment		:[ＵＳＡの機種で、Ｔ４が立っていない機種に送信して交信エラーになる
				　ことがあったためＴ４能力ビットもチェックする様にする
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/09/24]
	author		:[山口 哲治]
*************************************************************/
UBYTE SetT4Ability(void)
{
	if (MDM_ModemBuffer[StdFrmPos][4] & MASK_BAUDRATE) {		/**	DIS/DTC FIF ボーレートビットチェック	*/
	}
	return (YES);
}
