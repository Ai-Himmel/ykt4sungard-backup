/***********************************************************************
*          BY:   O.Kimoto
*        DATE:   Nov.11,1996
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   オプションボード関係のＤｅｆｉｎｅ群
************************************************************************/
#ifndef sys_opt_h
	#define	sys_opt_h

#include	"\src\atlanta\define\sysmax.h"

/***********************************************************************
*          BY:   O.Kimoto
*        DATE:   Nov.11,1996
*        TYPE:   DEFINE
* VAR TO HOLD:   UWORD SYS_PollingDocExclusiveFlag
* DESCRIPTION:   ポーリング原稿があるかどうかの変数
************************************************************************/
#define SYS_POLL_DOC_NO_EXIST			0xffff
#define SYS_EXIST_AND_NO_SENDING		0x0100
#define SYS_ERASE_REQUEST_POLLING_DOC	0x8000
#define SYS_ERR_POLLING_COM_EXIST		0x4000

/* 下記ｄｅｆｉｎｅは、回線を識別するときに使用します。
** ＤＰＲとは、オプションボード番号の扱いが異なりますので、注意してください。
**
** １ＳＴ＿ＬＩＮＥ～８ＴＨ＿ＬＩＮＥ＝ＤＰＲでの番号＋１
**
** By O.Kimoto 1996/12/02
*/
#define SYS_SEND_INTERNAL_LINE			0x0000	/* F-120:内蔵回線、F-150:ありえない */
#define SYS_SEND_1ST_LINE				0x0001
#define SYS_SEND_2ND_LINE				0x0002
#define SYS_SEND_3RD_LINE				0x0003
#define SYS_SEND_4TH_LINE				0x0004
#define SYS_SEND_5TH_LINE				0x0005
#define SYS_SEND_6TH_LINE				0x0006
#define SYS_SEND_7TH_LINE				0x0007
#define SYS_SEND_8TH_LINE				0x0008

/*
 * モデム内部遷移ステータス監視テーブル
 *
 *  警告！！！
 *  ビットフィールドを使用する場合、Ｖ５３とＳＨではビット配置が異なります。
 *  よってＡＬ１００のステータスモニタは正しく印字されません。
 *  ビットフィールドは今後使用しないようにしましょう。
 *  このステータスモニタはすでににＡＬ１００がでてるのでしかたなくこうします。
*/
struct	ModemInternalStatusTable_def	{
	UBYTE	Tx_Phase;
	UBYTE	Rx_Phase;

	/* ちょう、勝手にかえんといてや */
#if 0
	UBYTE	DTR_Status:2;
	UBYTE	RTS_Status:2;
	UBYTE	CTS_Status:2;
	UBYTE	RLSD_Status:2;

	UBYTE	FED_Status:2;
	UBYTE	PNDET_Status:2;
	UBYTE	PNSUC_Status:2;
	UBYTE	DMY4_Status:2;
#endif

	UBYTE	RLSD_Status:2;
	UBYTE	CTS_Status:2;
	UBYTE	RTS_Status:2;
	UBYTE	DTR_Status:2;

	UBYTE	DMY4_Status:2;
	UBYTE	PNSUC_Status:2;
	UBYTE	PNDET_Status:2;
	UBYTE	FED_Status:2;

	UBYTE	T30Status;
	UBYTE	AbortCode;

	UDWORD	Timer;
};

#define MODEM_STATUS_TABLE_MAX	200

#define DTR_ON_STATUS			0x01
#define DTR_OFF_STATUS			0x03
#define DTR_NO_CHANGE_STATUS	0x03

#define RTS_ON_STATUS			0x01
#define RTS_OFF_STATUS			0x03
#define RTS_NO_CHANGE_STATUS	0x03

#define CTS_ON_STATUS			0x01
#define CTS_OFF_STATUS			0x03
#define CTS_NO_CHANGE_STATUS	0x03

#define RLSD_ON_STATUS			0x01
#define RLSD_OFF_STATUS			0x03
#define RLSD_NO_CHANGE_STATUS	0x03

#define FED_ON_STATUS			0x01
#define FED_OFF_STATUS			0x03
#define FED_NO_CHANGE_STATUS	0x03

#define PNDET_ON_STATUS			0x01
#define PNDET_OFF_STATUS		0x03
#define PNDET_NO_CHANGE_STATUS	0x03

#define PNSUC_ON_STATUS			0x01
#define PNSUC_OFF_STATUS		0x03
#define PNSUC_NO_CHANGE_STATUS	0x03

#define DMY4_ON_STATUS			0x01
#define DMY4_OFF_STATUS			0x03
#define DMY4_NO_CHANGE_STATUS	0x03

#define TX_CONTROL_CHANNEL			0x01
#define RX_CONTROL_CHANNEL			0x02
#define TX_PRIMARY_CHANNEL			0x04
#define RX_PRIMARY_CHANNEL			0x08
#define CONTROL_CHANNEL_RETRAIN		0x10
#define PRIMARY_CHANNEL_RETRAIN		0x20


/*--------------------------------------*/
/* 受信エラーラインセーブデータＭＡＸ値 */
/*--------------------------------------*/
#define OPT_ERR_LINE_DATA_MAX	10

/************************************************************************
*               BY:  Y.Murata
*             DATE:  96/12/09
*             TYPE:  struct
*      VAR TO HOLD:
*      DESCRIPTION:  オプションモデムデータ転送用バッファ定義
************************************************************************/
struct SYS_OptionModemData_t {
	UBYTE SYS_FaxCommStage;				/* 通信遷移状態 				define */
	UBYTE SYS_CurrentExecQueueNo;		/* Grape実行ExecQueueの番号 	value */
	UBYTE SYS_DocBlock_Src_Size;		/* 元原稿パラメータ 			define */
	UBYTE SYS_DocBlock_Src_Mode;		/* 元原稿パラメータ 			define */
	UBYTE SYS_DocBlock_Dst_Size;		/* 先原稿パラメータ 			define */
	UBYTE SYS_DocBlock_Dst_Mode;		/* 先原稿パラメータ 			define */
	UBYTE GrayModeFlag;					/* ファイン、中間調の場合--YES	yes/no */
	UBYTE FaxComTXorRX_Sign;			/* 送信／受信識別フラグ 		define */
	UBYTE SYS_FaxComType;				/* 交信種別 					define */
	UBYTE SYS_FaxComTxType;				/* 送信原稿種別 				define */
	UBYTE TxBaudRate;					/* 確定送信ボーレイト 			define */
	UBYTE RxBaudRate;					/* 確定受信ボーレイト 			define */
	UBYTE TxECM_Mode;					/* 確定ＥＣＭ送信指定 			yes/no */
	UBYTE RxECM_Mode;					/* 確定ＥＣＭ受信指定 			yes/no */
	UBYTE FinalRxMode;					/* 確定受信モード 				define */
	UBYTE SYS_RxMemoryFileItem;			/* メモリ受信アイテム 			define */
	UBYTE TxMemoryFileItem;				/* メモリ送信アイテム 			define */
	UBYTE RxMode;						/* 受信モード 					define */
	UBYTE TxMode;						/* 送信モード 					deifne */
	UBYTE FaxCompatibleErrorCode;		/* ｺﾝﾊﾟﾁｴﾗｰｺｰﾄﾞ 				define */
	UBYTE SYS_ManualFaxCommErrRequest;	/* 手動ﾁｪｯｸﾒｯｾｰｼﾞ印字要求 		yes/no */
	UBYTE SYS_VoiceCallAccepted;		/* 会話予約						yes/no */
	UBYTE SYS_TensouJushinFlag;			/* 転送受信						yes/no */
	UBYTE FirstTxMode;					/* １枚目送信モード				define */
	UBYTE SYS_V34ProcedureExecutingFlag;/* Ｖ３４実行フラグ				yes/no */
	UBYTE CommandFileOptionItem;		/* 通信種別						define */
	UBYTE CommandFilePage;				/* メモリ送信総ページ			valye  */
	UBYTE FCM_DataBasePollingNumber;	/* 検索ポーリング番号			value  */
	UWORD SYS_TxTotalPage;						/* 全送信ページ数 				value */
	UWORD SYS_RxTotalPage;						/* 全受信ページ数 				value */
	UWORD TxMemoryFilePage;						/* メモリ送信を行う原稿のファイルページ value */
	UWORD MDM_RxTotalLine;						/* 受信トータルライン 			value */
	UWORD MDM_RxErrorTotalLine;					/* 受信エラートータルライン 	value */
	UWORD BatchTxFinishPage;					/* 一括送信送信済み頁数 		value */
	UWORD FaxComResult;							/* 通信結果 					define */
	UWORD BackUpFaxComResult;					/* 通信結果 					define */
	UWORD JournalTxTotalCount;					/* ＰＡＴジャーナル通番			value  */
	UWORD JournalRxTotalCount;					/* ＰＡＴジャーナル通番			value  */
	UWORD SYS_RxMemoryFileNo;
	UWORD TxMemoryFileBoxNumber;				/* ＢＯＸ番号 */
	UBYTE NonStandardID[SYS_TTI_ID_MAX];			/* 交信相手機の村田ＩＤ 17byte */
	UBYTE StandardID[SYS_ID_MAX];					/* 交信相手機の標準ＩＤ 21byte */
	UBYTE BackUpStandardID[SYS_ID_MAX];				/* 交信相手機の標準ＩＤ 21byte */
	UBYTE TxResponsedRTN_PageSign[SYS_ERROR_PAGE];	/* RTN/PIN を応答された送信ページ（ビット指定）6byte */
	UWORD MDM_RxTotalLineSave[OPT_ERR_LINE_DATA_MAX];		/* 受信トータルラインセーブ */
	UWORD MDM_RxErrorTotalLineSave[OPT_ERR_LINE_DATA_MAX];	/* 受信エラートータルラインセーブ */
};


/* 1998/02/03 Y.Murata	CHAR_JOURNAL
 * キャラクタジャーナル記載用
*/
struct SYS_OptionModemData2_t {
	UBYTE	QueueKind;				/* キューの種類 */
	UBYTE	QueueDialItem;			/* ダイアル種類 */
	UWORD	QueueDialOffset;		/* ﾜﾝﾀｯﾁ/短縮のｵﾌｾｯﾄ */
	UWORD	CommandDepartmentCode;	/* 部門コード */
	UBYTE	CommandDirectDial[SYS_DIRECT_DIAL_MAX];	/* ダイレクトダイアル *//* 21byte */
};


/************************************************************************
*               BY:  Y.Murata
*             DATE:  96/12/09
*             TYPE:  DEFINE
*      VAR TO HOLD:
*      DESCRIPTION:  回線テスト定義
************************************************************************/
struct SYS_FactoryOptModemData_t {
	UWORD	Item;			/* ﾘﾚｰﾃｽﾄ、ﾄｰﾅﾙﾃｽﾄ、DTMFﾃｽﾄ */
	UWORD	Kind;			/* ﾃｽﾄ項目種別 */
	UWORD	BaudRate;		/* PIX Symbol Rate */
	UWORD	DataRate;		/* PIX Speed */
	UWORD	PIX_Pattern;	/* PIX のﾊﾟﾀｰﾝ V17以下のみ有効 */
	UWORD	StackNumber;	/* ｽﾀｯｸﾅﾝﾊﾞｰ */
};


/* 回線テスト・アイテム  SYS_FactoryOptModemData.Item */
#define OPT_MDM_FACTORY_TEST_END		0
#define OPT_MDM_FACTORY_TEST_START		1
#define SYS_OPT_MDM_RELAY_TEST			2
#define SYS_OPT_MDM_TONAL_TEST			3
#define SYS_OPT_MDM_DTMF_TEST			4
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/25 */
/* 警察FAX Added start DVT_ID15 by SMuratec K.W.Q 2005/11/05 */
#define SYS_OPT_MDM_KEIDEN_RELAY_TEST	5
#define SYS_OPT_MDM_KEIDEN_TONAL_TEST	6
#define SYS_OPT_MDM_KEIDEN_DTMF_TEST	7
/* 警察FAX Added end DVT_ID15 by SMuratec K.W.Q 2005/11/05 */
#endif		/* End of (defined (KEISATSU)) */

/* 回線テスト・テスト項目種別  SYS_FactoryOptModemData.Kind */
  /* ﾘﾚｰﾃｽﾄ */
	#define OPT_MDM_RELAY_CML_ON			0				/* CML */
	#define OPT_MDM_RELAY_CML_OFF			1
	#define OPT_MDM_RELAY_S_ON				2				/* S */
	#define OPT_MDM_RELAY_S_OFF				3
	#define OPT_MDM_RELAY_DP_ON				4				/* DP */
	#define OPT_MDM_RELAY_DP_OFF			5
	#define OPT_MDM_RELAY_H_ON				6				/* H */
	#define OPT_MDM_RELAY_H_OFF				7
	#define OPT_MDM_RELAY_L_ON				8				/* L */
	#define OPT_MDM_RELAY_L_OFF				9
	#define OPT_MDM_RELAY_CONT24_ON			10				/* CONT24 */
	#define OPT_MDM_RELAY_CONT24_OFF		11
	#define OPT_MDM_RELAY_RI_ON				12				/* RI(GK) */
	#define OPT_MDM_RELAY_RI_OFF			13

  /* ﾄｰﾅﾙﾃｽﾄ */
	#define OPT_MDM_TONAL_NONE				0
	#define OPT_MDM_TONAL_462HZ				1
	#define OPT_MDM_TONAL_1080HZ			2
	#define OPT_MDM_TONAL_1300HZ			3
	#define OPT_MDM_TONAL_1650HZ			4
	#define OPT_MDM_TONAL_1700HZ			5
	#define OPT_MDM_TONAL_1800HZ			6
	#define OPT_MDM_TONAL_1850HZ			7
	#define OPT_MDM_TONAL_2100HZ			8
	#define OPT_MDM_TONAL_FSK_WHITE			9
	#define OPT_MDM_TONAL_FSK_BLACK			10
	#define OPT_MDM_TONAL_V27_1200_2400		11
	#define OPT_MDM_TONAL_V27_1600_4800		12
	#define OPT_MDM_TONAL_V29_2400_7200		13
	#define OPT_MDM_TONAL_V29_2400_9600		14
	#define OPT_MDM_TONAL_V17_2400_7200		15
	#define OPT_MDM_TONAL_V17_2400_9600		16
	#define OPT_MDM_TONAL_V17_2400_12000	17
	#define OPT_MDM_TONAL_V17_2400_14400	18

	#define OPT_MDM_TONAL_V34_2400_2400		19
	#define OPT_MDM_TONAL_V34_2400_4800		20
	#define OPT_MDM_TONAL_V34_2400_7200		21
	#define OPT_MDM_TONAL_V34_2400_9600		22
	#define OPT_MDM_TONAL_V34_2400_12000	23
	#define OPT_MDM_TONAL_V34_2400_14400	24
	#define OPT_MDM_TONAL_V34_2400_16800	25
	#define OPT_MDM_TONAL_V34_2400_19200	26
	#define OPT_MDM_TONAL_V34_2400_21600	27

	#define OPT_MDM_TONAL_V34_2800_4800		28
	#define OPT_MDM_TONAL_V34_2800_7200		29
	#define OPT_MDM_TONAL_V34_2800_9600		30
	#define OPT_MDM_TONAL_V34_2800_12000	31
	#define OPT_MDM_TONAL_V34_2800_14400	32
	#define OPT_MDM_TONAL_V34_2800_16800	33
	#define OPT_MDM_TONAL_V34_2800_19200	34
	#define OPT_MDM_TONAL_V34_2800_21600	35
	#define OPT_MDM_TONAL_V34_2800_24000	36
	#define OPT_MDM_TONAL_V34_2800_26400	37

	#define OPT_MDM_TONAL_V34_3000_4800		38
	#define OPT_MDM_TONAL_V34_3000_7200		39
	#define OPT_MDM_TONAL_V34_3000_9600		40
	#define OPT_MDM_TONAL_V34_3000_12000	41
	#define OPT_MDM_TONAL_V34_3000_14400	42
	#define OPT_MDM_TONAL_V34_3000_16800	43
	#define OPT_MDM_TONAL_V34_3000_19200	44
	#define OPT_MDM_TONAL_V34_3000_21600	45
	#define OPT_MDM_TONAL_V34_3000_24000	46
	#define OPT_MDM_TONAL_V34_3000_26400	47
	#define OPT_MDM_TONAL_V34_3000_28800	48

	#define OPT_MDM_TONAL_V34_3200_4800		49
	#define OPT_MDM_TONAL_V34_3200_7200		50
	#define OPT_MDM_TONAL_V34_3200_9600		51
	#define OPT_MDM_TONAL_V34_3200_12000	52
	#define OPT_MDM_TONAL_V34_3200_14400	53
	#define OPT_MDM_TONAL_V34_3200_16800	54
	#define OPT_MDM_TONAL_V34_3200_19200	55
	#define OPT_MDM_TONAL_V34_3200_21600	56
	#define OPT_MDM_TONAL_V34_3200_24000	57
	#define OPT_MDM_TONAL_V34_3200_26400	58
	#define OPT_MDM_TONAL_V34_3200_28800	59
	#define OPT_MDM_TONAL_V34_3200_31200	60

	#define OPT_MDM_TONAL_V34_3429_4800		61
	#define OPT_MDM_TONAL_V34_3429_7200		62
	#define OPT_MDM_TONAL_V34_3429_9600		63
	#define OPT_MDM_TONAL_V34_3429_12000	64
	#define OPT_MDM_TONAL_V34_3429_14400	65
	#define OPT_MDM_TONAL_V34_3429_16800	66
	#define OPT_MDM_TONAL_V34_3429_19200	67
	#define OPT_MDM_TONAL_V34_3429_21600	68
	#define OPT_MDM_TONAL_V34_3429_24000	69
	#define OPT_MDM_TONAL_V34_3429_26400	70
	#define OPT_MDM_TONAL_V34_3429_28800	71
	#define OPT_MDM_TONAL_V34_3429_31200	72
	#define OPT_MDM_TONAL_V34_3429_33600	73
	#define OPT_MDM_TONAL_VOICE				74
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/10 */
	#define OPT_MDM_TONAL_VOICE2			75
 #endif
#endif
#if defined(POPLAR_F) || defined(HINOKI2) || defined (HINOKI3) || defined (KEISATSU) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || (defined(POPLAR_H) && defined(JP1)) || defined(SATSUKI2) || defined(STOCKHM2)	/* 55転送 By O.Kimoto 2003/02/05 */
	#define OPT_MDM_TONAL_FSK_W1_B1			76	/* FSK_W1_B1 1999/12/27 Y.Murata */
#endif
	#define OPT_MDM_TONAL_STOP				98

  /* DTMFﾃｽﾄ */
	#define OPT_MDM_DTMF_0					0
	#define OPT_MDM_DTMF_1					1
	#define OPT_MDM_DTMF_2					2
	#define OPT_MDM_DTMF_3					3
	#define OPT_MDM_DTMF_4					4
	#define OPT_MDM_DTMF_5					5
	#define OPT_MDM_DTMF_6					6
	#define OPT_MDM_DTMF_7					7
	#define OPT_MDM_DTMF_8					8
	#define OPT_MDM_DTMF_9					9
	#define OPT_MDM_DTMF_AST				10
	#define OPT_MDM_DTMF_SHARP				11
	#define OPT_MDM_DTMF_ROW1				12
	#define OPT_MDM_DTMF_ROW2				13
	#define OPT_MDM_DTMF_ROW3				14
	#define OPT_MDM_DTMF_ROW4				15
	#define OPT_MDM_DTMF_COL1				16
	#define OPT_MDM_DTMF_COL2				17
	#define OPT_MDM_DTMF_COL3				18
	#define OPT_MDM_DTMF_COL4				19
	#define OPT_MDM_DTMF_STOP				98

/* 回線テスト・ＰＩＸ送出パターン SYS_FactoryOptModemData.PIX_Pattern */
	#define OPT_MDM_PIX_W1_B0				0
	#define OPT_MDM_PIX_W1_B1				1
	#define OPT_MDM_PIX_W1_B4				2
	#define OPT_MDM_PIX_W0_B1				3
	#define OPT_MDM_PIX_W4_B1				4


/* 下記ｄｅｆｉｎｅは、回線を識別するときに使用します。
** By O.Kimoto 1996/12/02
*/
#define OPT_INTERNAL_LINE			0x0001
#define OPT_1ST_LINE				0x0002
#define OPT_2ND_LINE				0x0004
#define OPT_3RD_LINE				0x0008
#define OPT_4TH_LINE				0x0010
#define OPT_5TH_LINE				0x0020
#define OPT_6TH_LINE				0x0040
#define OPT_7TH_LINE				0x0080
#define OPT_8TH_LINE				0x0100


#define OPT_TX_ENABLE				0x01
#define OPT_PBX_ENABLE				0x02
#define OPT_PSTN_ENABLE				0x04
#define OPT_PSTN_ACCESS_ENABLE		0x08
#define OPT_288_ENABLE				0x10
#define OPT_144_ENABLE				0x20

#define INTERNAL_NUMBER		0x80
#define OTHER_NUMBER		0x00

#define V8_START_DISABLE	0x00
#define V8_START_ENABLE		0x10	/** OPT_288_ENABLEと同じ値です */


#define OUTWARD		0	/** 内蔵   －＞ 外付け **/
#define INWARD		1	/** 外付け －＞ 内蔵   **/

/* オプションモデム時刻監視 */
struct SYS_OptionModemTimeData_t {
	UDWORD	StartTime;
	UDWORD	EndTime;
};


/*--------------------------------------------------------*/
/* 機器設定、メモリＳＷ、機器パラの内容が変わった事を通知 */
/*--------------------------------------------------------*/
#define OPT_CHANGED_SETTEING_STATUS		0x0001
#define OPT_CHANGED_MEMORY_SWITCH		0x0002
#define OPT_CHANGED_UNI_SWITCH			0x0004
#define OPT_CHANGED_MENTE_SWITCH		0x0008
#define OPT_CHANGED_MACHINE_PARA		0x0010
#define OPT_CHANGED_SPEAKER_LEVEL		0x0020
#define OPT_CHANGED_DRD_TEADCHING_BUF	0x0040	/* Teaching Buffer Clear 1997/05/26 Y.Murata */


/* 受信可能かどうかを判断する時に、送信専用設定になっていても
** 手動受信の場合は、着信させます。
** by O.Kimoto 1997/02/08
*/
#define AUTO_RECEIVE	0x00
#define MANUAL_RECEIVE	0x01


#endif	/* End of File */
