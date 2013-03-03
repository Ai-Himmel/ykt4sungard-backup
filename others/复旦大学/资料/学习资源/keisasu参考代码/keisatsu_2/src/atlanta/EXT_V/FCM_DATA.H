/*************************************************************************
	module		:[通信大域変数]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		1)	松竹桜の<faxdata.c>と<g3_d.c>からコピーして，ＮＴＴ仕様の部分を削除
		2)	大機能間大域変数は"SYS_"をつけて"sys_data.c"へ移動
		3)	大域変数をサイズ別に確保
		4)	SATSUKI/LAVENDRでは内蔵RAM(512Byte)に実体があります
		修正履歴
		1.一括送信送信済み頁数追加 94/9/22 鈴木
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/15]
	author		:[竹内茂樹]
*************************************************************************/

/*########################################################*/
/* 警告！！												  */
/* １バイトデータとそうでないデータをちゃんと分けましょう */
/*--------------------------------------------------------*/

/*--------------------------*/
/*	インクルードファイル達	*/
/*--------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\sysmax.h"			/* 最大値 */
#include	"\src\atlanta\define\message.h"			/* メッセージ構造体 */
#include	"\src\atlanta\define\sysbatch.h"		/* バッチ・ファイル構造体 */
#include	"\src\atlanta\define\syscomf.h"			/* コマンド・ファイル構造体 */
#include	"\src\atlanta\define\sysjrnl.h"			/* ジャーナル構造体 */
#include	"\src\atlanta\define\mem_def.h"			/* メモリ・ファイル構造体 */
#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998  */
#include	"\src\atlanta\define\cl1expro.h"
#endif

/*------------*/
/* デバッグ用 */
/*------------*/

/* extern unsigned char	FaxDebugDCSSW;			*/	/** もういらない **/
/* extern unsigned char	FaxTelDebugSW;			*/	/** もういらない **/
/* extern unsigned char	VoiceReceiveDebugFlag;	*/
/* extern UWORD		FaxPhaseC_D_Time;	*/		/** もういらない **/
extern UWORD		FaxComPhaseStatus;
/* extern UWORD		FaxDebugPIXStartTime;	*/
/* extern UWORD		FaxDebugPIXENDTime;		*/
/* extern WORD				mpl_address;			*/

/*==========================================*/
/*		  １バイトデータ達					*/
/*==========================================*/

extern UBYTE	OwnMakerCode;					/*	自機メーカーコード	村田A2	ＦＸ45	*/

extern UBYTE	PollingTxType;					/*	ポーリング送信原稿種別	皐月はセット不要	*/

extern UBYTE	FaxComRxType;					/*	受信原稿種別				*/

extern UBYTE	FaxTxCommand;					/*	確定送信コマンド	相手機中継同報機能あり-->YES	*/

extern UBYTE	FinalTxMode;					/*	確定送信モード				*/
extern UBYTE	FinalRxMode;					/*	確定受信モード				*/

extern UBYTE	TxSmType;						/*	送信方法	スキャナ、メモリ、カバー、ＲＣＲ	*/
extern UBYTE	RxPmType;						/*	受信方法	プリンタ、メモリ	*/

extern UBYTE	DisplayFirstMode;				/*	送信モードを表示させるためのフラグ	YES/NO	*/

extern UBYTE	FirstTxMode;					/*	送信モード（次ページ目のモード）	*/
extern UBYTE	TxMode;							/*	送信モード（最後に送ったページのモード）	*/
extern UBYTE	RxMode;							/*	受信モード（最後に受けたページのモード）	*/
extern UBYTE	TxModeMethod;					/*	送信モード（インチ／ミリ）23.Mar'94 Y.Suzuki	*/
extern UBYTE	RxModeMethod;					/*	受信モード（インチ／ミリ）23.Mar'94 Y.Suzuki	*/

extern UBYTE	TxWidth;						/*	確定送信原稿幅	*/
extern UBYTE	RxWidth;						/*	確定受信原稿幅	*/
extern UBYTE	DocWidth;						/*	原稿幅			*/

extern UBYTE	FaxRxAvailableLength;			/*	受信可能最大原稿長	*/
extern UBYTE	FaxTxMaxLength;					/*	確定送信原稿長		*/
extern UBYTE	FaxRxMaxLength;					/*	確定受信原稿長		*/

/*	extern UBYTE	VoiceCallModeRequest;		**	会話予約指示	** 竹内 Jul.07.1994 */
/*	extern UBYTE	VoiceCallFormedFlag;		**	会話予約成立	** 竹内 Jul.07.1994 */

extern UBYTE	TxRCR_Flag;						/*	相手機からの「受領証要求」フラグ	YES/NO 受領証送信時--YES	*/
														/*	TxReceiptConfirmationReportFlag → TxRCR_Flagに変更	by Bamboo,Jan.6'94	*/
extern UBYTE	TxReceiptRequestFlag;			/*	「受領証送信」フラグ(受信側から送信側の能力をチェック)	*/

extern UBYTE	FaxComPerformingFlag;			/*	「通信中」フラグ	YES/NO	*/
extern UBYTE	FaxComTxPerformingFlag;			/*	「送信中」フラグ	*/
extern UBYTE	FaxComRxPerformingFlag;			/*	「受信中」フラグ	*/

extern UBYTE	TxECM_Mode;						/*	確定ＥＣＭ送信指定	*/
extern UBYTE	RxECM_Mode;						/*	確定ＥＣＭ受信指定	*/
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui Jun.19,1998  */
extern UBYTE	TxECM_Ability;					/*	ＥＣＭ送信ＯＮ／ＯＦＦ指定	*/
extern UBYTE	RxECM_Ability;					/*	ＥＣＭ受信	*/
#endif

extern UBYTE	RxFirstTimeCompatibleCheckFlag;	/*	受信コンパチブルチェック回数	フレーム取り込み要/不要に使用	*/

extern UBYTE	TxRetrainingFlag;				/*	「再トレーニング」フラグ	*/

extern UBYTE	TxRetransmitFlag;				/*	「再送信」フラグ	*/

extern UBYTE	TxModeChangedFlag;				/*	「モード変更」フラグ	*/
extern UBYTE	RxModeChangeRequestedFlag;		/*	「受信モード変更要求」フラグ	*/

extern UBYTE	TxPageDataSetFlag;				/*	「ページオープン中（済み）」フラグ	*/

extern UBYTE	RxWholePageCompletedFlag;		/*	「１物理ページ受信完了」フラグ	*/

extern UBYTE	RxEOM_ReceiveFlag;				/*	「ＥＯＭ受信」フラグ	*/
extern UBYTE	RxEOP_ReceiveFlag;				/*	「交信終了許可（ＥＯＰ受信）」フラグ	*/
extern UBYTE	RxEOR_ReceiveFlag;				/*	ＥＯＲ受信済みフラグ	*/

extern UBYTE	TxCoverPageFlag;				/*	カバーページ送信フラグ	*/

extern UBYTE	AttemptTxBaudRate;				/*	試行送信ボーレイト	*/
extern UBYTE	AttemptRxBaudRate;				/*	試行受信ボーレイト	*/

extern UBYTE	TxBaudRate;						/*	確定送信ボーレイト	*/
extern UBYTE	RxBaudRate;						/*	確定受信ボーレイト	*/

extern UBYTE	AvailableTxBaudRate;			/*	機器の送信可能なボーレイト	*/
extern UBYTE	AvailableRxBaudRate;			/*	機器の受信可能なボーレイト	*/

extern UBYTE	TxInterMemoryFlag;				/*	メモリ間通信を示す	YES/NO	*/
extern UBYTE	RxPrinterDirectFlag;			/*	ダイレクトプリンタ受信を示す	*/

/*	extern UBYTE	TxPageOpenedFlag;	*/	/*	送信ファイルオープン済みフラグ	*/
/*	extern UBYTE	RxPageOpenedFlag;	*/	/*	受信ファイルオープン済みフラグ (0:Closed/1:Opened/2:DualOpened)	*/

extern UBYTE	TxCodingMethod;					/*	確定送信符号化方式	*/
extern UBYTE	RxCodingMethod;					/*	確定受信符号化方式	*/
extern UBYTE	AvailableTxCodingMethod;		/*	機器の送信可能な符号化方式	*/
extern UBYTE	AvailableRxCodingMethod;		/*	機器の受信可能な符号化方式	*/

extern UBYTE	TxMSE_Method;					/*	確定送信ＭＳＥ方式	*/
extern UBYTE	AvailableTxMSE_Method;			/*	機器の送信可能なMSE方式	*/
extern UBYTE	AvailableRxMSE_Method;			/*	機器の受信可能なＭＳＥ方式	*/

extern UBYTE	JBIG_Ability;					/* TEST JBIG符号化能力 1997/01/28	By T.Yamaguchi */

extern UBYTE	NextScanningMode;				/*	送信原稿の指定線密度　int-->char 鈴木 94/1/19	*/

extern UBYTE	AttemptRxModeSwitch;			/*	受信モード	*/

extern UBYTE	AvailableTxMinimumScanningTime;	/*	機器の送信可能な1ライン最小電送時間	*/
extern UBYTE	AvailableRxMinimumScanningTime;	/*	機器の受信可能な１ライン最小電送時間	*/
extern UBYTE	TxMinimumScanningTime;			/*	確定１ライン最小電送時間（送信）	*/
extern UBYTE	RxMinimumScanningTime;			/*	確定１ライン最小電送時間（受信）	*/

extern UBYTE	TxPageFinishStatus;				/*	送信終了の状況	*/
extern UBYTE	RxPageFinishStatus;				/*	受信終了の状況	*/

/* extern UBYTE	RxRTN_Flag;	 * 竹内 Feb.13'94 */	/*	現在受信ページの画質不良フラグ（画質不良のときセットする）	*/

extern UBYTE	ECM_PageCounter;				/*	ＥＣＭポストメッセージのページカウンタ	*/
extern UBYTE	ECM_BlockCounter;				/*	ＥＣＭポストメッセージのブロックカウンタ	*/
extern UBYTE	ECM_FrameCounter;				/*	ＥＣＭポストメッセージのフレームカウンタ	*/
extern UBYTE	ECM_FirstFrameCounter;			/*	受信した１部分ページのフレーム数　現在受信中の部分ページの全フレーム数 */
														/*	（１部分ページの初回のみＰＰＳのＦＣをコピー）	*/
extern UBYTE	FaxECM_ResponseTimeFlag;		/*	ＥＣＭ応答受信の待ち時間切り替えフラグ	*/
extern UBYTE	RxECM_RetransmittedFlag;		/*	ＥＣＭの１部分ページ１回目受信フラグ	*/
extern UBYTE	RxECM_PixTimeoutFlag;			/*	ＥＣＭ受信でノイズによるタイムアウト対策(回線断しないで再送要求する)	*/

extern UBYTE	AvailableRxResolution;			/*	機器の受信可能な受信線密度	*/

extern UBYTE	TxMemoryFileItem;				/*	メモリ送信を行う原稿のファイルアイテム	*/
extern UBYTE	TxMemoryFileBoxNumber;			/*	1997/02/24	By T.Yamaguchi	*/

extern UBYTE	FaxComFileItem;					/*	通信ファイルアイテム	*/
extern UBYTE	FaxComFileNumber;				/*	通信ファイルナンバー	*/
extern UBYTE	FaxComFilePage;					/*	通信ファイルページ	*/

extern UBYTE	RelayedCommandNo;				/*	中継配信指示受信（中継同報の子機）の時に */
														/*	展開したコマンドファイルナンバー	*/
extern UBYTE	NonStdFrmName;					/*	MDM_Buffer[][]上へ受信した非標準各フレームの名前	*/
extern UBYTE	ID_FrmName;						/*	MDM_Buffer[][]上へ受信したＩＤ各フレームの名前	*/
extern UBYTE	StdFrmName;						/*	MDM_Buffer[][]上へ受信した標準各フレームの名前	*/


extern UBYTE	DIS_ReceivedFlag;				/*	ＤＩＳ（ＤＣＳ）関係	*/

extern UBYTE	DiagByteCounter;				/*	リモート診断関係	*/

extern UBYTE	TxMethodFlag;					/*	送信方式確定	*/
extern UBYTE	BaudrateFlag;					/*	ボーレイト確定	*/

/* extern UBYTE	CNG_DetectFlag;					*//*	擬似リングバックトーン送出中のＣＮＧ検出済みフラグ	*/
extern UBYTE	FaxTelOffHook;					/*	会話予約中にオフフック検出済みフラグ	*/
extern UBYTE	FaxTelOffHookTEL1Flag;			/*	TEL1 オフフック検出フラグ */
extern UBYTE	FaxTelOffHookTEL2Flag;			/*	TEL2 オフフック検出フラグ */
extern UBYTE	OffHookDetectStopFlag;			/*	オフフック検出ストップフラグ 1994/01/19 Y.Murata */
/* extern UBYTE	GenerateRingSignalStopFlag;	*/	/*	擬似ベル鳴動中のストップキー入力フラグ	*/

extern UBYTE	TxSpeedHandshakeFlag;			/*	短縮ハンドシェーク用(短縮ハンドシェーク送信を実行する送信) YES/NO */
extern UBYTE	RxSpeedHandshakeFlag;			/*	短縮ハンドシェーク用(短縮ハンドシェーク受信をおこなった) */
extern UBYTE	SDCS_TransmitFlag;				/*	短縮ハンドシェーク用(モデムに短縮ハンドシェーク送信であることを示す) */
extern UBYTE	PartnerSpeedHandshakeAbility;	/*	短縮ハンドシェーク用(相手機に短縮ハンドシェーク機能がある) */
#if (PRO_SPEED_EX == ENABLE)
extern UBYTE	PartnerSpeedHandshakeExAbility;	/** 相手機が新短縮ハンドシェーク機能の有無を示すフラグ */
extern UBYTE	ArrivalSignalToneTransmitFlag ; /** 着信トーン送出を示すフラグ */
#endif
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
extern UBYTE	EOM_received;
extern UBYTE	PartnerSpeedModeChangeAbility;	/*	相手機が短縮ハンドシェーク（モード変更）受信能力の有無を示す 96/06/01 By T.Yamaguchi */
#endif
extern UBYTE	Partner300dpiAbility;			/** 相手機がR12*15.4L/mm受信能力の有無を示すフラグ */
extern UBYTE	PartnerEFineAbility;			/** 相手機がR12*11.55L/mm受信能力の有無を示すフラグ */
extern UBYTE	PartnerCipherAbility;			/** 相手機暗号化能力の有無を示すフラグ	1997/06/18  By T.Yamaguchi */
extern UBYTE	FaxComTXorRX_Sign;				/*	送信／受信識別フラグ　送信、受信、リモート診断識別	*/

#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 夏 2005/11/01 */
extern UBYTE	FaxComTXorRX_Flag;				/*	送信／受信識別フラグ　送信、受信、リモート診断識別	*/
#endif /* defined (KEISATSU) */

extern UBYTE	PartnerAbility0;				/*	メモリスイッチＢ０(SYS_MemorySwitch[10])のコピー	*/
extern UBYTE	PartnerAbility1;				/*	メモリスイッチＢ１(SYS_MemorySwitch[11])のコピー	*/
extern UBYTE	PartnerAbility2;				/*	メモリスイッチＢ２(SYS_MemorySwitch[12])のコピー	*/
extern UBYTE	PartnerAbility3;				/*	メモリスイッチＢ3(SYS_MemorySwitch[14])のコピー	*/

extern UBYTE	AD_Result;						/*	オートダイアラー戻り値	*/
extern UBYTE	AD_Result_Flag;					/*	???		*/

extern UBYTE	RxJunkMailFlag;					/*	ジャンクメイル受信フラグ　YES/NO　ジャンクメイルエラー時--YES	*/

extern UBYTE	HurryUpFaxComFlag;				/*	通信の優先順位を強制的に高くするフラグ	*/

extern UBYTE	GrayModeFlag;					/*	ファイン、中間調の場合--YES	*/

extern UBYTE	ScanTxGrayMode;					/* スキャナ送信 でかつ相手の能力 KIRI 400DPI ｲﾝﾁ なら H_FINE 94/10/19 Y.S */

extern UBYTE	UpdateTxPageMode;				/*	ページ数更新時の更新項目			*/
extern UBYTE	FaxCompatibleErrorCode;			/*	詳しいコンパチエラーコード			*/

extern UBYTE	TxOptionFCF;					/*	ポストメッセージ送信拡張ＦＣＦフレーム	*/
extern UBYTE	TxFCF;							/*	ポストメッセージ送信ＦＣＦフレーム		*/
extern UBYTE	RxOptionFCF;					/*	ポストメッセージ受信拡張ＦＣＦフレーム	*/
extern UBYTE	RxFCF;							/*	ポストメッセージ受信ＦＣＦフレーム		*/

extern UBYTE	RxFrameMessage1;				/*	受信フレーム種別	*/
extern UBYTE	PRI_Q_RxFlag;					/*	ＰＲＩ＿Ｑ受信フラグ	*/
extern UBYTE	PRI_Q_RxCount;					/*	ＰＲＩ＿Ｑ受信カウンタ	*/

extern UBYTE	ReceiveResponseFlag;			/*	応答受信ありなしフラグ		*/
extern UBYTE	ReceiveCommandFlag;				/*	命令受信ありなしフラグ		*/

extern UBYTE	UpdatePageInformationFlag;		/*	送信ページ情報を更新する／しないフラグ	*/

extern UBYTE	FSK_FirstReceivedFlag;			/* 相手機がＦＡＸであると確定した 96/05/17 By T.Yamaguchi */

extern UBYTE	TimerFlag;						/*	タイマー	*/
extern UBYTE	ReceiveCommandFlagDetectFlag;	/*	HDLC関係	*/
extern UBYTE	TransmitCommandFlag;			/*	HDLC関係	*/
extern UBYTE	ReceiveCommandTimerStartFlag;	/*	HDLC関係	*/

extern UBYTE	ForwardReceiveFlag;				/* 転送受信 */
extern UBYTE	BackUpForwardReceiveFlag;		/* 転送受信バックアップ */
extern UBYTE	FaxNetReceiveFlag;				/* Ｆネット着信 */

extern UBYTE	DelWaitFlag;					/* FaxTel 1994年6月8日 */
extern UBYTE	FaxTelDelCheckFlag;				/* FaxTel 1994年6月8日 */

extern UBYTE	DCS_TxCount;					/*	unsigned short -> UBYTEに変更		*/

/*--------------------------------------------------------------------*/
/*	 ｺﾏﾝﾄﾞﾌｧｲﾙ,ﾊﾞｯﾁﾌｧｲﾙの内容をｾｰﾌﾞしとくためのもの					  */
/*		通信起動時(FCM_Main())にセットされる						  */
/*						   1994/01/19  Y.Murata						  */
/*--------------------------------------------------------------------*/
extern UBYTE	CommandFileStatus;				/*	使用状況	*/
extern UBYTE	CommandFileOptionItem;			/*	通信種別	*/
extern UBYTE	CommandFileConfirmationReport;	/*	通信証	*/
extern UBYTE	CommandFileTitleMessage;		/*	タイトルメッセージ	*/
extern UBYTE	*CommandFileDirectDial;			/*	直接ダイヤル番号	*/
#if (PRO_PIN_ACCESS == ENABLE)
extern UBYTE	*CommandFilePinNumber;			/*	ｺﾏﾝﾄﾞﾌｧｲﾙのＰＩＮ番号 '95.12.22 t.yamaguchi */
extern UBYTE	CommandFilePinAccessMode;		/* ＰＩＮアクセスモード 1996.01.09 T.yamaguchi */
#endif
/* extern UBYTE	CommandFilePage;				/@ 送信ページ 1997/05/09  By T.Yamaguchi */
extern UWORD	CommandFilePage;				/* 送信ページ */
extern UWORD	CommandFileDepartmentCode;		/* 部門管理コード */
extern UBYTE	CommandFileAbility;				/* 通信予約の付加情報(FX) 1994/11/01 Y.Murata */
/*#if (PRO_F_CODE == ENABLE)*/
extern UBYTE	CommandFileFcodePosition;		/* ｺﾏﾝﾄﾞﾌｧｲﾙのＦコードﾃﾞｰﾀの格納されているﾎﾟｼﾞｼｮﾝを格納 */
/*#endif*/

/* extern UBYTE	T30PrintStopFlag;			*/	/*	Ｔ３０モニタ印字禁止フラグ	(松竹桜のバグの対応) */

/*---------------------------------------------------------------------*/
/*	 リモートＦＡＸ設定状態フラグ									   */
/*		通信起動時 FCM_initializeFaxCom()で CHK_RemoteFaxON()の値を	   */
/*		セーブする。												   */
/*	 1994/01/19	 Y.Murata											   */
/*---------------------------------------------------------------------*/
extern UBYTE	RemoteFaxON_Flag;				/*	リモートＦＡＸ設定状態 */

/*---------------------------------------------------------------------*/
/*	 リモートＦＡＸ自動プリント設定状態フラグ						   */
/*		通信起動時 FCM_initializeFaxCom()で CHK_RemoteFaxPRN()の値を   */
/*		セーブする。												   */
/*	 1994/02/04	 Y.Murata											   */
/*---------------------------------------------------------------------*/
extern UBYTE	RemoteFaxPRN_Flag;				/*	リモートＦＡＸ自動プリント設定状態 */

/*---------------------------------------------------------------------*/
/*	 リモートＦＡＸ自動メモリ消去設定状態フラグ						   */
/*		通信起動時 FCM_initializeFaxCom()で CHK_RemoteFaxDEL()の値	  */
/*		セーブする。												   */
/*	 1994/02/04	 Y.Murata											   */
/*---------------------------------------------------------------------*/
extern UBYTE	RemoteFaxDEL_Flag;				/*	リモート自動メモリ消去ＦＡＸ設定状態 */


/*---------------------------------------------------*/
/*	ＦＸ 村田独自機能有無の判断に使用				 */
/*---------------------------------------------------*/
extern UBYTE	MakerCodeRxFlag;				/*	「村田メーカコード受信」フラグ	YES/NO	*/
extern UBYTE	FX_CodeRxFlag;					/*	「ＦＸメーカコード受信」フラグ	YES/NO	*/

extern UBYTE	NonStandardID[SYS_TTI_ID_MAX];				/*	交信相手機の村田（／ＯＥＭ）ＩＤ		*/
extern UBYTE	StandardID[SYS_ID_MAX];						/*	交信相手機の標準ＩＤ					*/
extern UBYTE	BackUpStandardID[SYS_ID_MAX];				/*	交信相手機の標準ＩＤ（バックアップ）	*/
extern UBYTE	TxResponsedRTN_PageSign[SYS_ERROR_PAGE];	/*	RTN/PIN を応答された送信ページ（ビット指定）	*/
extern UBYTE	RelayedTxDocumentStatus[SYS_COM_FILE_MAX];	/*	中継配信原稿の状態を表す'94/1/26鈴木	*/
extern UBYTE	RelayedReportPrintStatus[SYS_COM_FILE_MAX];	/*	不達通知のプリント状況	竹内 Apr.07.1995	*/

/*----------------------------------------------------------*/
/*	受信原稿ポーリング送信種別								*/
/*	受信原稿ﾎﾟｰﾘﾝｸﾞではない		0							*/
/*	RX_DOC_POLLING_TX			1							*/
/*	SECURE_DOC_POLLING_TX		2							*/
/*	FIP_DOC_POLLING_TX			3							*/
/*----------------------------------------------------------*/
extern UBYTE	RxDocumentPollingTxFlag;

/*------------------------------------------*/
/*	PRN_PreOpen()済かどうかの識別フラグ		*/
/*		竹内	Apr.22.1994					*/
/*------------------------------------------*/
#if (PRO_PRINTER_RX == ENABLE)
	extern UBYTE	PrinterRxPreOpenFlag;	/*	プリンタ受信でのＰｒｅオープン済フラグ	*/
#endif

/*----------------------------------------------------------------------*/
/*	後手順短縮ハンドシェークフラグ	(Jun.14.1994)						*/
/*		自機と相手機の間で「後手順の短縮ハンドシェーク」を行うことが	*/
/*		決まった時に，セットする										*/
/*	プリアンブル短縮フラグ			(Aug.31.1994)						*/
/*		ポストメッセージの命令送信，応答送信時に「後手順短縮フラグ」	*/
/*		の状態によってセット／クリアする (ＭＤＭはこのフラグを見る)		*/
/*			竹内														*/
/*----------------------------------------------------------------------*/
extern	UBYTE	PostSpeedHandshakeFlag;			/*	後手順短縮ハンドシェークフラグ	*/
extern	UBYTE	ShorteningPreambleFlag;			/*	プリアンブル短縮フラグ			*/

/*----------------------------------------------------------------------*/
/*	リモートＦＡＸチェックメッセージ送信フラグ							*/
/*		リモートＦＡＸ送信での最終ページで，次ページにメモリオーバーの	*/
/*		チェックメッセージを送信する時にセットする						*/
/*			竹内	Jun.24.1994											*/
/*----------------------------------------------------------------------*/
extern	UBYTE	TxRemoteFaxCheckMsgFlag;		/*	リモートＦＡＸチェックメッセージ送信フラグ	*/

/*----------------------------------------------------------------------*/
/*	プリンタ受信時のプリンタエラーフラグ								*/
/*		プリンタエラーが発生した時にセットする							*/
/*		これを見て，次ページからプリンタ受信をメモリ受信に切り替える	*/
/*			竹内	Jul.21.1994											*/
/*----------------------------------------------------------------------*/
extern	UBYTE	RxPrinterErrorFlag;				/*	プリンタ受信時のプリンタエラーフラグ	*/

/*------------------------------------------*/
/*	料金管理フラグ							*/
/* ==1　なら料金計算する 25.Aug'94 Y.Suzuki */
/*------------------------------------------*/
#if(PRO_COST == ENABLE)
extern	UBYTE	CheckCostFlag;
#endif

#if(PRO_BATCH_TX == ENABLE)
/*--------------------------------------------------*/
/**	一括送信１頁以上送信後、エラー終了した場合		*/
/*	のリダイヤル送信頁セットの際に使用 Y.Suzuki		*/
/*										94/9/28		*/
/*--------------------------------------------------*/
extern UBYTE	BatchRedialFirstPage;
#endif

#if defined(DEU) || defined(AUT)
	extern UBYTE	FaxTelOffHookFlag;			/*	???		*/
#endif

#if defined(DEU)	/*----	★ドイツ仕様★	----*/
	extern UBYTE	RTN_ReceiveCounter;			/*	ＲＴＮ受信回数	(ReceiveRTN_Count)	*/
#endif

#if defined(FRA)	/*----	★フランス仕様★	----*/
	extern UBYTE	FaxRingingPeriodFlag;			/*	無制限:0／一定期間:1	*/
	extern UBYTE	VoiceFlag;						/*	「会話予約受付」フラグ	*/
	extern UBYTE	GenerateRingSignalHLRelayFlag;	/*	???	（フランスのみ）	*/
	extern UBYTE	VoiceTxFlag;					/*	???	（フランスのみ）	*/
	extern UBYTE	GenerateRingSignalFlag;			/*	???						*/
	extern UBYTE	GenerateRingSignalMessage;		/*	???						*/
	extern UBYTE	FRA_PIP_PIN_Rx_Flag;			/*	1995/05/06	by M.HARADA */
	extern UBYTE	CRPReceiveFlag;					/*	1995/05/07	by M.HARADA */
#endif

/*------------------------------------------------------*/
/*	ＥＣＭ受信時のＲＮＲ処理，ロール紙カット待ちの状態	*/
/*		2=デコード待ち → 1=カット待ち → 0=終了		*/
/*								竹内	Jun.24.1994		*/
/*------------------------------------------------------*/
extern	UBYTE	EcmWaitPhase;						/*	ＥＣＭ受信時のデコード待ち／カット待ち状態	*/


/* By S.K extern UBYTE	SYS_FaxComType;				*/	/*	交信種別 */
/* By S.K extern UBYTE	SYS_FaxComTxType;			*/	/*	送信原稿種別 */
/* By S.K extern UBYTE	SYS_VoiceCallAccepted;		*/	/*	「会話予約受付」フラグ	*/
/* By S.K extern UBYTE	SYS_RxReceiptRequestFlag;	*/	/*	「受領証要求」フラグ(送信側から受信側の能力をチェック)	*/
/* By S.K extern UBYTE	SYS_FaxComFIP_RxActiveFlag; */	/*	通信で使用するＦＩＰ受信中フラグ */

/* 未使用 extern UBYTE	RxPostMessageEORRxContinueFlag;	*/
/* 未使用 extern UBYTE	CountUpTo100;				*/
/* 未使用 extern UBYTE	SetTransmitterID;			*/	/* 「発信元送出」のＯＮ／ＯＦＦを示す */
/* 未使用 extern UBYTE	DCSReceivedFlag;			*/	/* ＤＣＳ関係	*/
/* 未使用 extern UBYTE	LastFCF;					*/	/*	最後に受信したＦＣＦ	*/
/* 未使用 extern UBYTE	GI2AvailableFlag;			*/	/*	???		*/
/* 未使用 extern UBYTE	OverSeaDial1stDISFlag;		*/	/*	???		*/
/* 未使用 extern UBYTE	GCAvailableFlag;			*/	/*	???		*/
/* 未使用 extern UBYTE	FarBssData;					*/	/*	???		*/
/*----	★松ＡＰ　ＵＳＡ仕様★	----------------------------------------*/
/*	extern UBYTE	FaxComTemporaryCalledFlag;	%*	仮着信	*%		*/
/*----------------------------------------------------------------------*/

/*-------------------------------------------------------
  ダイヤル種別、ダイヤルナンバー配列のオフセット用データ
  ------------------------------------------------------- */
extern UBYTE	DialKind;							/* ダイヤル種別 */
extern UBYTE	DirectNumberPosition;				/* 直接ﾀﾞｲﾔﾙのﾎﾟｼﾞｼｮﾝ */
extern UBYTE	OnetouchDialPosition;				/* ワンタッチﾀﾞｲﾔﾙのﾎﾟｼﾞｼｮﾝ */
extern UWORD	SpeedDialPosition;					/* 短縮ﾀﾞｲﾔﾙのﾎﾟｼﾞｼｮﾝ */

/*==============================================*/
/*		 ２バイト・４バイトデータ達				*/
/*==============================================*/

extern UWORD		FaxComResult;					/*	交信結果					*/
extern UWORD		BackUpFaxComResult;				/*	交信結果（バックアップ）	*/

extern UDWORD		FaxComStartTime;				/*	交信開始時刻	*/
extern UWORD		FaxComPeriod;					/*	交信時間	*/

/* 以下２データ移動 19.Mar'94	Y.Suzuki */
/* extern UWORD		SYS_TxTotalPage;					*//*	全送信ページ数 OPRタスク参照するため，SYS_DATA.H に移動	*/
/* extern UWORD		SYS_RxTotalPage;					*//*	全受信ページ数 OPRタスク参照するため，SYS_DATA.H に移動	*/
extern UDWORD		TxPageTotalLineCount;			/*	送信トータルライン数（スキャナ送信用）	*/

extern WORD				RxPageIndexNo;					/*	メモリ受信時のファイルインデックス番号	*/

extern UWORD		PollingTxFirstPageFlag;			/*	ポーリング送信先頭ページフラグ	*/

extern UWORD		PRI_Q_Count;					/*	ＰＲＩ－Ｑカウント	*/

extern UWORD		TxMemoryFileCurrentExecutingNo;	/*	現在実行中のメモリ送信原稿のファイルナンバー　通常送信--１ */
														/*	  マルチファイルＤＢポーリング--送信中のファイルNO	*/
extern UWORD	TxMemoryFileNextExecutingNo;		/*	次送信予定ののメモリ送信原稿のファイルナンバー　通常送信--１ */

extern UWORD		TxMemoryFilePage;				/*	メモリ送信を行う原稿のファイルページ	*/

extern UWORD	FCM_ReceiveResponseTime;	/* T4_timer Set add by t.yamaguchi 95.12.18 */

/*---------------------------------------------------*/
/*	デュアルオープンメモリ受信されるプリント用原稿	 */
/*	のためのパラメータ								 */
/*	By Y.SUZUKI	17.Feb'94	SYS_DATA.H に移動		 */
/*---------------------------------------------------*/
/*extern UWORD		SYS_RxPrintFilePage;				*	デュアルオープンメモリ受信されるプリント用原稿(中継配信指示受信、リモートＦＡＸ同時プリント)のファイルページ	*/
/*extern UWORD		SYS_RxPrintFileNo;					*	デュアルオープンメモリ受信されるプリント用原稿(中継配信指示受信、リモートＦＡＸ同時プリント)のファイルＮＯ．	*/
/*extern UBYTE		SYS_RxPrintFileItem;				*	デュアルオープンメモリ受信されるプリント用原稿(中継配信指示受信、リモートＦＡＸ同時プリント)のファイルアイテム	*/

extern WORD				TxNonStandardFrameByteCount;	/*	MDM_Buffer[][]上へセットした送信非標準フレームのバイト数		*/
extern WORD				TxID_FrameByteCount;			/*	MDM_Buffer[][]上へセットした送信ＩＤフレームのバイト数		*/
extern WORD				TxStandardFrameByteCount;		/*	MDM_Buffer[][]上へセットした送信標準フレームのバイト数		*/
extern WORD				RxNonStandardFrameByteCount;	/*	MDM_Buffer[][]上へセットされた受信非標準フレームのバイト数	*/
extern WORD				RxID_FrameByteCount;			/*	MDM_Buffer[][]上へセットされた受信ＩＤフレームのバイト数		*/
extern WORD				RxStandardFrameByteCount;		/*	MDM_Buffer[][]上へセットされた受信標準フレームのバイト数		*/

extern WORD				NonStdFrmPos;					/*	MDM_Buffer[][]上へ受信した非標準フレームの位置	*/
extern WORD				ID_FrmPos;						/*	MDM_Buffer[][]上へ受信したＩＤフレームの位置		*/
extern WORD				StdFrmPos;						/*	MDM_Buffer[][]上へ受信した標準フレームの位置		*/
extern UDWORD			FaxTM;							/*	タイマー	*/



extern UWORD		FCF_Point;						/*	HDLC関係　HDLCフレーム受信時モデムバッファ内のＦＣＦの位置	*/

extern UWORD		DiagPoint;						/*	リモート診断関係　サービスユーティリティフィールドポイント	*/
extern UWORD		DiagReadAddress;				/*	リモート診断関係	*/
extern UWORD		DiagReadSegment;				/*	リモート診断関係	*/
#if defined(POPLAR_F)
extern UWORD	DiagTxBackUpPointer;			/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
extern UDWORD	DiagTxLength;					/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
extern UWORD	DiagTxBackUpSize;				/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
extern UWORD	DiagRxBackUpPointer;			/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
extern UDWORD	DiagRxLength;					/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
extern UWORD	DiagRxBackUpSize;				/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
#endif
extern UWORD		RelayedDocumentReceiveNo;		/*	中継指示時プリントするファイルナンバー	*/
extern UWORD		ErrorMessageSet;				/*	エラーメッセージ内容	*/

#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui Jun.19,1998  */
extern UWORD		FcomEcmSize;					/*	ＥＣＭフレームサイズ（６４／２５６oct）種別	*/
#endif

extern WORD				FaxTelResult;					/* FaxTel戻り値 */

#if (0) /*By Y.Suzuki 1998/09/11*/
//#if(PRO_BATCH_TX == DISABLE)
//extern UWORD		TxMemoryFileNo[SYS_TX_MEMORY_FILE_NO_MAX];		/*	メモリ送信を行う原稿のファイルナンバー	*/
//extern UWORD		PollingTxFilePage[SYS_TX_MEMORY_FILE_NO_MAX];	/*	ポーリング送信の際の総送信ページ数	*/
//#else
//extern UWORD		TxMemoryFileNo[SYS_BATCH_INDEX_MAX];				/*	バッチ,メモリ送信を行う原稿のファイルナンバー 20.Aug'94 Y.Suzuki	*/
//extern UWORD		PollingTxFilePage[SYS_BATCH_INDEX_MAX];				/*	バッチ,ポーリング送信の際の総送信ページ数 20.Aug'94 Y.Suzuki	*/
//#endif
#endif /* #if (0) By Y.Suzuki 1998/09/11 */

/*受信原稿ポーリング取り出しに対応するため 最大代行受信数にあわせる By Y.Suzuki 1998/09/11 */
extern UWORD	TxMemoryFileNo[SYS_MEMORY_RX_MAX+1];	/*	メモリ送信を行う原稿のファイルナンバー	*/
extern UWORD	PollingTxFilePage[SYS_MEMORY_RX_MAX+1];	/*	ポーリング送信の際の総送信ページ数	*/

/*---------------------------------------------------------------------*/
/*	 第２ワンタッチ／短縮ダイアルの配列オフセット					   */
/*	   FCM_SetPartnerAbility() でセットされる						   */
/*																	   */
/* if ( SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Speed < SYS_SPEED_DIAL_MAX )
 *		Offset_2ndDial = SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Speed - SYS_SPEED_DIAL_MAX
 *																	   *
 * if ( SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Onetouch < SYS_2ND_ONETOUCH_MAX )
 *		Offset_2ndDial = SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Onetouch - SYS_2ND_ONETOUCH_MAX
 *																	   */
/* 1994/02/17 Y.Murata												   */
/*---------------------------------------------------------------------*/
extern UWORD		Offset_2ndDial;					/* 第２ワンタッチ／短縮ダイアルの配列オフセット */

/*------------------------------------------------------------------------*/
/* ジャーナル通番									  1994/06/07 Y.Murata */
/*			 通信開始時にジャーナルカウント(SYB_TxTotalCount)をセーブする */
/*------------------------------------------------------------------------*/
extern UWORD	JournalTxTotalCount;
extern UWORD	JournalRxTotalCount;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/03/11 */
extern UWORD	JournalTxTotalCountExt;
extern UWORD	JournalRxTotalCountExt;
#endif

extern	UWORD	EcmOneFrameTime;	/*	ＥＣＭ受信タイムアウト回避用の１フレーム分の時間(msec)	*/

/*--------------------------------------------------------------------------*/
/*	一括送信送信済み頁数	94/9/22 Y.Suzuki								*/
/*--------------------------------------------------------------------------*/
extern	UWORD	BatchTxFinishPage;

/* extern const UWORD	FaxComAvailableModeMaster;	*/	/*	受信モード （有効受信モード）ロムテーブル	*/
/* By S.K extern UWORD	SYS_RxMemoryFileItem;		*/	/*	メモリ受信を行う原稿のファイルアイテム	*/
/* By S.K extern UWORD	SYS_RxMemoryFileNo;			*/	/*	メモリ受信を行う原稿のファイルナンバー	*/
/* By Y.S extern UWORD	SYS_RxMemoryFilePage;		*/		/*	メモリ受信を行う原稿のファイルページ	10.May'94*/
/* 未使用 extern UWORD	FaxComAvailableMode;		*/	/*	受信モード（有効受信モード）int-->char 鈴木94/1/19	*/
/* 未使用 extern UWORD	FaxComStartTimeInSecond;	*/	/*	交信時間	交信開始時のタイマー値をセーブしておき交信時間を求める	*/
/* 未使用 extern UWORD	FaxComTotalLine;			*/	/*	受信トータルライン　画データ受信側でセット	*/
/* 未使用 extern UWORD	FaxComErrorTotalLine;		*/	/*	受信エラートータルライン　画データ受信側デセット	*/
/* 未使用 extern UWORD	PhaseDTxPageFinishStatus;	*/	/*	フェーズＤで再セットした送信結果	*/
/* 未使用 extern UWORD	MDM_RxTotalLine;			*/	/* by T.S '94.1.14 受信トータルライン　画データ受信側でセット	*/
/* 未使用 extern UWORD	MDM_RxErrorTotalLine;		*/	/* by T.S '94.1.14 受信エラートータルライン　画データ受信側デセット	*/



/*--------------------------------------------------------------------*/
/* メッセージ用ポインター											  */
/*--------------------------------------------------------------------*/
extern MESSAGE_t			FaxTelTxMessage;				/*	ＴＥＬ／ＦＡＸ用	*/
extern MESSAGE_t			*FaxTelRxMessage;				/*	ＴＥＬ／ＦＡＸ用	*/
/* extern MESSAGE_t			*DetCNG_Message;			*/	/*	ＴＥＬ／ＦＡＸ用	*/
/* extern MESSAGE_t			*DetRcvComMessage;			*/	/*	ＴＥＬ／ＦＡＸ用	*/
/* extern MESSAGE_t			*TxComMessage;				*/	/*	ＴＥＬ／ＦＡＸ用	*/
/* extern MESSAGE_t			*OffHookMessage;			*/	/*	ＴＥＬ／ＦＡＸ用	*/
extern MESSAGE_t			MsgFromFaxComToMain;			/*	通信～＞メイン用	*/
extern MESSAGE_t			*FcomMsg;						/** メイン～＞通信用メッセージ */


/*---------------------------------------------------------------------*/
/* コマンドファイル用ポインター										   */
/* 94/01/06	   Y.Murata												   */
/*---------------------------------------------------------------------*/
extern struct	SYS_CommandData_t		*CommandP;				/*	コマンドファイル用ポインター	*/

/*---------------------------------------------------------------------*/
/* 一括送信用ポインター												   */
/* 94/01/06	   Y.Murata												   */
/*---------------------------------------------------------------------*/
extern struct	SYS_BatchTxData_t		*BatchP;				/*	一括送信用ポインター	*/


#if (PRO_CONTINUOUS_POLLING == ENABLE)
/*---------------------------------------------------------------------*/
/* 連続ポーリング用ポインター										   */
/* Oct.18.1996	By T.Yamaguchi										   */
/*---------------------------------------------------------------------*/
extern struct	SYS_ContinuousPollingData_t *ContPollingP;
#endif

/*---------------------------------------------------------------------*/
/* ジャーナル用ポインタ												   */
/* 94/01/17	   Y.Murata												   */
/*---------------------------------------------------------------------*/
extern struct	SYS_JournalData_t			*Journal;				/* ジャーナル用ポインタ		*/

/*----------------------------------------------------------------------*/
/*	メモリファイルのオープン実行用データ								*/
/*		MEM_WriteOpen()/MEM_DualOpen()の実行時使用						*/
/*		竹内茂樹	Jan.21'94											*/
/*		Mar.02.1994		struct MEM_ExecData_t FaxMemoryExecData やめ！	*/
/*		May.12.1994		struct MEM_StoreData_t FaxMemoryStoreData 削除！	*/
/*----------------------------------------------------------------------*/
/*	extern struct	MEM_StoreData_t			FaxMemoryStoreData;	*/	/*	メモリへの蓄積実行用データ	*/

/*---------------------------------------------------------------------*/
/*	デュアルオーブン時インデックス指定データ						   */
/*		MEM_DualWriteOpen()の実行時使用								   */
/*		中継配信指示受信、リモートＦＡＸ受信(同時プリント有り)の場合に */
/*		使用														   */
/*		Y.SUZUKI	Feb.17'94										   */
/*---------------------------------------------------------------------*/
extern struct	MEM_IndexData_t			FaxMemoryIndexData;	/*	デュアルオーブン時インデックス指定データ	*/

#if defined(FRA)				/* 95/02/21 by M.HARADA */
extern	UBYTE				FRA_GRS_StartFlag;				/*	DIS 3回TX後擬似ベルタスクの起動時に参照　*/
extern	UWORD				tskno_B1_Bell;
#endif

extern WORD			DammyDataforMurata1;				/* 内蔵ＲＡＭに移動のための保健 */
extern WORD			DammyDataforMurata2;
extern WORD			DammyDataforMurata3;
extern WORD			DammyDataforMurata4;
extern WORD			DammyDataforMurata5;

#if(PRO_RELAYED_REPORT == ENABLE)
/* 椛不達通知用 不達通知送信時は、会話予約キーの入力を拒否する。95/03/17 Y.Suzuki */
extern UBYTE	 TxRelayReport;
#endif
#if defined(GBR)	/* add by M.HARADA 95.09.09 for NLD */
extern UBYTE	 NLD_DT_Detecting_Flag;
#endif
/* 1997/06/02  By T.Yamaguchi DEU条件削除 */
extern UBYTE	 DEU_Return_Flag;

/*----------------------------------------------------------*/
/*	TSI による中々継時に中継指示ｸﾞﾙｰﾌﾟNO.とは、				*/
/*	別に中継指示配信送信宛先用ｸﾞﾙｰﾌﾟNO.をTSIにｾｯﾄさせる。	*/
/*	受信したTSI:000-2-3-4--10 の場合						*/
/*						  ↑を示す。						*/
/*											Y.Suzuki 950929 */
/*----------------------------------------------------------*/
#if(PRO_TSI_RELAY_COM == ENABLE)
extern UBYTE	 TSI_Ptr;
#endif
/* #if defined(FRA) || defined(DEU) 1997/06/02  By T.Yamaguchi */
extern UBYTE	 TimerCutStatus;
extern UBYTE	 PIP_TX_Flag;	/* 1997/06/02  By T.Yamaguchi DEU条件削除 */
/* #endif */

extern MESSAGE_t			BackupFcomMsg;		/** メイン～＞通信用メッセージ保存 1996/03/04 */

/* ICHOU からもってきた 1997/06/02  By T.Yamaguchi */
/* extern UBYTE	 AddPBX_DialingNumber[];	未使用 */
extern struct	MEM_IndexData_t		EraseIndexData;				/*	ファイルインデックス	*/
extern UWORD 	TxFinalPageNumber;	/* ICHOU変更 送信最適化処理 by T.Soneoka 1996/10/01 */

/* コンパチの途中で記録紙サイズが変更されるとエラーにならないためバックアップ変数 */
extern UBYTE	FCM_BuckUpPaperSize;	/* 1997/12/16  By T.Yamaguchi */

/*---------------------------------*/
/* Ｆコードのためのもの 1996/06/14 */
/*---------------------------------*/
extern WORD				TxPasswordFrameByteCount;	/*	MDM_Buffer[][]上へセットした送信ＰＷＤフレームのバイト数	*/
extern WORD				TxSelectiveFrameByteCount;	/*	MDM_Buffer[][]上へセットした送信ＳＥＰフレームのバイト数	*/
extern WORD				TxSubaddressFrameByteCount;	/*	MDM_Buffer[][]上へセットした送信ＳＵＢフレームのバイト数	*/
extern WORD				RxPasswordFrameByteCount;	/*	MDM_Buffer[][]上へセットされた受信ＰＷＤフレームのバイト数	*/
extern WORD				RxSelectiveFrameByteCount;	/*	MDM_Buffer[][]上へセットされた受信ＳＥＰフレームのバイト数	*/
extern WORD				RxSubaddressFrameByteCount;	/*	MDM_Buffer[][]上へセットされた受信ＳＵＢフレームのバイト数	*/
extern UBYTE			PasswordFrameID[SYS_ID_MAX];			/* PWDﾊﾞｯﾌｧ */
extern UBYTE			SelectivePollingFrameID[SYS_ID_MAX];	/* SEPﾊﾞｯﾌｧ */
extern UBYTE			SubaddressFrameID[SYS_ID_MAX];		/* SUBﾊﾞｯﾌｧ */

extern UBYTE			OwnPasswordFrameID[SYS_ID_MAX];			/* PWDﾊﾞｯﾌｧ */
extern UBYTE			OwnSelectivePollingFrameID[SYS_ID_MAX];	/* SEPﾊﾞｯﾌｧ */
extern UBYTE			OwnSubaddressFrameID[SYS_ID_MAX];		/* SUBﾊﾞｯﾌｧ */

extern UBYTE			PartnerPasswordFrameID[SYS_ID_MAX];			/* PWDﾊﾞｯﾌｧ */
extern UBYTE			PartnerSelectivePollingFrameID[SYS_ID_MAX];	/* SEPﾊﾞｯﾌｧ */
extern UBYTE			PartnerSubaddressFrameID[SYS_ID_MAX];		/* SUBﾊﾞｯﾌｧ */

extern UBYTE			PWD_FrmName;
extern UBYTE			SEP_FrmName;
extern UBYTE			SUB_FrmName;
extern WORD				PWD_FrmPos;
extern WORD				SEP_FrmPos;
extern WORD				SUB_FrmPos;

extern UBYTE			PartnerT_PWD_Ability;
extern UBYTE			PartnerP_PWD_Ability;
extern UBYTE			PartnerSEP_Ability;
extern UBYTE			PartnerSUB_Ability;

extern UBYTE			PWDT_BitEnable;
extern UBYTE			PWDP_BitEnable;
extern UBYTE			SUB_BitEnable;
extern UBYTE			SEP_BitEnable;

#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/*------------------------------------------------------------------------------------------------
	ソフトコーデック使用時のＧ３メモリ送信 Ａ３，ＨＦＩＮＥ －－＞ (Ｂ４以下）&&（ＳＦＩＮＥ以下）
	が発生するとき 最小伝送時間 ０ｍｓから１０ｍｓにする				 By Y.Suzuki 1997/05/09
--------------------------------------------------------------------------------------------------*/
extern UBYTE	AddMinLineTime;
#endif

/* #if (PRO_MULTI_LINE == ENABLE)	/@ 1997/01/13 Y.Murata */
extern UBYTE	PartnerV8Capable;				/* 相手機Ｖ８能力有り */
/* #endif */

/***********************************************************************/
/* Ｖ８／Ｖ３４仕様にともない新規追加                                  */
/***********************************************************************/
/* Ported from Clover by H. Kubo 1997/06/27 */
/*------------------*/
/* １バイトデータ達 */
/*------------------*/
extern UBYTE	V8ProcedureRequestFlag;			/* Ｖ８モード移行要求 */
extern UBYTE	V34FirstDataRate;				/* Ｖ３４データレイト(最初) */
extern UBYTE	V34CurrentDataRate;				/* Ｖ３４データレイト(現在) */
extern UBYTE	V34BaudDataRate;				/* Ｖ３４ボーレイト */
/* extern UBYTE	PartnerV8Capable;	*/			/* 相手機Ｖ８能力有り */
extern UBYTE	V34PrimaryChannelDirection;		/* プライマリチャネル指示 */
#if (0) /* Deleted by H.Kubo 1997/10/07 使われていない */
extern UBYTE	V8FrmName;						/* Ｖ８フレームの名前 */
#endif /* (0) */
extern UBYTE	FCM_CallFunctionData;
extern UBYTE	V34ErrorCode;					/* ＡＢＣＯＤＥ */
extern UBYTE	V8ConfigMode;					/* Ｖ８終了時のCONF の値 */
extern UBYTE	FCM_V8MonitorFlag;				/* V8 Octet Monitor Flag */
extern UBYTE	FCM_SampleBufPoint;				/* data rate sample for debug */
extern UBYTE	FCM_CONF_Value;					/* conf data for debug 1996/02/19 */
extern UBYTE	FCM_SPEED_Value;				/* tx speed for debug 1996/02/19 */
extern UBYTE	FCM_384_Value;					/* rx speed for debug 1996/02/19 */
extern UBYTE	FCM_DataRateChangExecute;		/* 通信速度変更中 1996/08/28 */

extern UBYTE	V8_ANSamDetectFlag;		/* 1996/08/07 */

/*----------------------*/
/* ２、４バイトデータ達 */
/*----------------------*/
extern UWORD			V34PhaseStatus;					/* Ｖ３４スタートアップフェーズステータス */
extern WORD				TxInformationCategoryByteCount;	/* 送信情報カテゴリバイト数 */
extern WORD				RxInformationCategoryByteCount;	/* 受信情報カテゴリバイト数 */
extern UWORD			ExecDialNumber;					/* ワンタッチ／短縮番号 */
extern WORD				V8FrmPos;						/* Ｖ８フレームのポインター */
extern WORD				V8CallFunctionPos;				/* 起呼機能の位置 */
/* extern UWORD	FCM_ReceiveResponseTime;	*/  /* 応答受信ﾀｲﾏｰ */ /* T4_timer Set add by t.yamaguchi 95.12.18 */
extern UWORD			FCM_SignalToNoiseRatio;			/* Signal to Noise Ratio */
extern UWORD			FCM_LowBandEdgeFrequency;		/* Low Band Edge Frequency */
extern UWORD			FCM_HighBandEdgeFrequency;		/* High Band Edge Frequency */
#if (0) /* Deleted by H.Kubo 1997/10/07 */
extern UWORD			FCM_MemoryBlockSize;			/* １ブロックのサイズ 1996/03/07 */
#endif /* (0) */
extern UWORD			FCM_SavedRxTotalFrameLine;		/* トータルフレーム数記憶 1996/05/16 */
extern UWORD			FCM_SavedRxErrorFrameLine;		/* エラーフレーム数記憶 1996/05/16 */
extern UWORD			FCM_SavedRxPartialFrameLine;	/* 部分ページフレーム数記憶 1996/05/20 */
extern UWORD			FCM_SavedRxNonErrContinuePage;	/* 連続エラーなしページ数記憶 1996/05/20 */
extern UWORD			ECM_PageCounterBackUp;			/*	ＥＣＭポストメッセージのページカウンタ	*/
extern UWORD			ECM_BlockCounterBackUp;			/*	ＥＣＭポストメッセージのブロックカウンタ	*/
extern UWORD			FCM_PhaseJitterFrequencyValue;	/* 位相ジッタリード値 */
extern UWORD			FCM_PhaseJitterAmplitudeValue;	/* 位相ジッタリード値 */


extern UBYTE			FCM_ToneAfterDetectDCE; /* H.Kubo 1997/11/29 */

/*----------------*/
/* 配列、構造体達 */
/*----------------*/
#include "\src\atlanta\define\timer10.h" /* Added for def. of Timer10msData_t by H.Kubo 1997/06/30 */
#include "\src\atlanta\define\fcm_def.h" /* Added by H.Kubo 1997/06/30 */

extern struct	StartUpDataFile_t			StartUpData;			/* スタートアップデータ */
extern struct	FCM_MemoryClearIndexData_t	FCM_MemoryClearIndex;	/* 原稿消去指示用インデックス */
extern UBYTE								V34SavedCM_Data[SAVE_CATEGORY_BUF_MAX];
extern UBYTE 								V34SavedJM_Data[SAVE_CATEGORY_BUF_MAX];
extern UBYTE								V34SavedAvailableJM_Data[SAVE_CATEGORY_BUF_MAX];
extern struct	FCM_V8ControlData_t			FCM_V8Control;
extern struct	Timer10msData_t				FCM_TimeUp;
extern UBYTE								FCM_MonitorData[50];

#if 0 /* メモリ節約のため、削除します。 deleted by H.Kubo 1999/01/26 */
@@ extern UBYTE	FCM_SpeedBuf[16];
@@ extern UBYTE	FCM_ConfBuf[16];
@@ extern UBYTE	FCM_RateBuf[16];
#endif

extern UWORD	FCM_EQM_MonitorBuf[100];	/* TEST 1996/02/23 */
extern UBYTE	FCM_EQM_MonitorPoint;		/* TEST 1996/02/23 */

/* extern MESSAGE			BackupFcomMsg;		*/ /** メイン～＞通信用メッセージ保存 1996/03/04 */

extern UWORD 	FCM_PreEmphasisFilter;	/* Add By O.Kimoto 1996/04/18 */
extern UWORD 	FCM_TxLevelReduction;		/* Add By O.Kimoto 1996/07/25 */

extern UBYTE	FCM_Is_ToneDetecting;	/* 1997/09/11  By T.Yamaguchi */

#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1998/01/19 */
extern	UWORD				tskno_LST_RelayedTxReportImage;
#endif

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)	/* 1998/03/31  By T.Yamaguchi */
extern UBYTE DiagErrorDetails;
extern UWORD FCM_ROMDataSum;
#endif

#if (PRO_MODEM == R288F) && (PRO_MODEM_R288F_VERSION >= R288F_VERSION_26P) /* PhaseJitter。by H.Kubo 1998/10/07  */
extern UWORD	FCM_PhaseJitterFrequency;
extern UWORD	FCM_PhaseJitterAmplitude;
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
extern UBYTE	FCM_QuickMemoryTxExecute;
#endif

#if (PRO_TX_SPEED == V34)
/* 松下 Ｂ－５６がＣＩを検出しないため、Ｔ．１．１エラーが必ず発生する。
** よって、その防御策として、ＣＩ送出回数を限定する。
** By O.Kimoto 1999/03/11
*/
extern UBYTE	FCM_CI_TransmitCount;
#endif

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/10 */
extern UBYTE	FCM_DetectFSK;
extern UBYTE	FCM_DetectCIbyVoiceAnswer;
extern UBYTE	FCM_BusyToneDetectStatus;
 #endif
#endif

#if (PRO_BT_DET_WHILE_RBT == ENABLE) /* 疑似ベル鳴動中のBusyTone検出 2001/10/03 M.Matsumoto *//* Add By O.Kimoto 2002/03/11 */
extern UBYTE	IsDetectBusyTone;
#endif



/*********************************************************************
	警察FAX関連
										05/06/16 石橋正和
*********************************************************************/
#if defined (KEISATSU)

extern BOOL FCM_S1_Scramble; /* S1によるスクランブル通信か否か */
extern BOOL FCM_S1_Senyo; /* TRUE:専用 FALSE:共通 */

extern BOOL FCM_S1_Bypass; /* S1をバイパスするか否か */

extern struct FCM_ExecutingS1Info_t FCM_ExecutingS1Info; /* 実行中のスクランブル通信の状態 */

extern BOOL FCM_S1_Preamble3S; /* 最初のDCSのプリアンブルを3秒にする */

extern BOOL FCM_ShireiKidoWaitFor1stDCS; /* 一斉指令起動で最初のDCSを待っている */

extern const UWORD DBG_DelayAfterS1Open;		/* S1オープン送出後のウェイト[ms] */
extern const UWORD DBG_DelayAfterRTC;			/* RTC送出後のウェイト[ms] */
extern const UBYTE DBG_G3_TCF_OriginalPosition;	/* G3、TCF送信におけるRTCを本来のタイミングで送出する */
extern const UBYTE DBG_ECM_OriginalPosition;	/* ECM送信におけるRTCを本来のタイミングで送出する */

extern BOOL FCM_ISSEI_TX;		/* 警察FAX DVT_ID17 一斉モード送信中 by SMuratec 夏 2005/11/05 */

extern BOOL FCM_ShireiOff;	/* 指令信号がオフされた */

#endif /* defined (KEISATSU) */
