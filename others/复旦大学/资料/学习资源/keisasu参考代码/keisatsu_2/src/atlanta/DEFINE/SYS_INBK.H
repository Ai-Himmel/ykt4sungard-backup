/*************************************************************************
	System		:ANZU_L InternetFAX
				:POPLAR_B InternetFAX
				:POPLAR_H InternetFAX
	FileName	:SYS_INFD.H
	Author		:Y.Tanimoto
	Date		:1998/01/26
	RealTimeOS	:RISC Monitor
	Description	:
	Module		:
	Language	:SHC
	CPU			:SH7043
	Maintenance	:

	Copyright(C) 1997 Murata Machinery Ltd. All rights reserved
*************************************************************************/
#ifndef	SYS_INFD_H
 #define	SYS_INFD_H

#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\sysmax.h"

/*	FAX本体に登録できるユーザー数	*/
#define		SYS_INF_USER_MAX		10	/*	10ユーザー	*/

/************************
 **	宛先アドレス
 ************************/
/*	アドレス登録時の最大文字数	*/
#define		SYS_INF_MAIL_ADDRESS_MAX	51	/*	50char + NULL			*/

/*	宛先名登録時の最大文字数	*/
#define		SYS_INF_MAIL_NAME_MAX		21	/*	20char + NULL			*/

/*	ワンタッチの使用状況	*/
#define		SYS_INF_ONETOUCH_NO_ENTRY		0	/*	未登録					*/
#define		SYS_INF_ONETOUCH_FAXNUMBER		1	/*	FAX番号登録済み			*/
#define		SYS_INF_ONETOUCH_MAILADDRESS	2	/*	メールアドレス登録済み	*/

/*	プログラムワンタッチ登録状態	*/
#define		SYS_INF_P_ONETOUCH_NO_ENTRY		0	/*	未登録					*/
#define		SYS_INF_P_ONETOUCH_PROGRAM		1	/*	FAXのPﾜﾝﾀｯﾁとして使用中	*/
#define		SYS_INF_P_ONETOUCH_MAILGROUP	2	/*	ｱﾄﾞﾚｽのｸﾞﾙｰﾌﾟ登録中		*/

/*	ワンタッチ登録用の構造体	*/
struct	SYS_INF_OnetouchData_t		{
		UBYTE	MailAddress[SYS_INF_MAIL_ADDRESS_MAX];
		UBYTE	Name[SYS_INF_MAIL_NAME_MAX];
};


/************************
 **	アドレスのヒストリ
 ************************/
/*	アドレスのヒストリ記憶件数	*/
#define		SYS_INF_HISTORY_MAX		5

/*	ヒストリ記憶用の構造体	*/
struct	SYS_INF_MailAddressHistory_t		{
		UBYTE	TopBox;
		struct	HistoryBox_t	{
				UBYTE	Status;
				UBYTE	Address[SYS_INF_MAIL_ADDRESS_MAX];
				UBYTE	NextBox;
		}HistoryBox[SYS_INF_HISTORY_MAX];
};

/*	Status	*/
#define		SYS_INF_HISTORY_EMPTY		0
#define		SYS_INF_HISTORY_SETTING		1
#define		SYS_INF_HISTORY_RELEASE		2
#define		SYS_INF_HISTORY_STORED		3

/************************
 **	ユーザーデータ登録
 ************************/
/*	ユーザーデータ	*/
#define		SYS_INF_USER_CODE_MAX			20
#define		SYS_INF_USER_NAME_MAX			21
#define		SYS_INF_SUB_DIAL_MAX			3
#define		SYS_INF_ISP_NAME_MAX			21
#define		SYS_INF_PPP_ID_MAX				31
#define		SYS_INF_PPP_PASSWORD_MAX		31
#define		SYS_INF_POP_ID_MAX				31
#define		SYS_INF_POP_PASSWORD_MAX		31
#define		SYS_INF_IP_ADDRESS_OCTET_MAX	4
#define		SYS_INF_POP_SERVER_NAME_MAX		51
#define		SYS_INF_SMTP_SERVER_NAME_MAX	51

/*	ユーザーデータ登録用の構造体	*/
struct	SYS_INF_UserData_t		{
		UBYTE	UserCodeNumber[SYS_INF_USER_CODE_MAX];
		UBYTE	UserName[SYS_INF_USER_NAME_MAX];
		UBYTE	TelNumber[SYS_INF_SUB_DIAL_MAX][SYS_TEL_2DIGIT_MAX];
		UBYTE	PIN_Number[SYS_PIN_MAX];
		UBYTE	ISP_Name[SYS_INF_ISP_NAME_MAX];		
		UBYTE	PPP_LoginID[SYS_INF_PPP_ID_MAX];		
		UBYTE	PPP_Password[SYS_INF_PPP_PASSWORD_MAX];	
		UBYTE	PPP_Authentication;			
		UBYTE	POP_LoginID[SYS_INF_POP_ID_MAX];		
		UBYTE	POP_Password[SYS_INF_POP_PASSWORD_MAX];
		UBYTE	IP_Address[SYS_INF_IP_ADDRESS_OCTET_MAX];
		UBYTE	MailAddress[SYS_INF_MAIL_ADDRESS_MAX];	
		UBYTE	ISP_ServerAddress[SYS_INF_IP_ADDRESS_OCTET_MAX];
		UBYTE	POP_Server[SYS_INF_POP_SERVER_NAME_MAX];
		UBYTE	SMTP_Server[SYS_INF_SMTP_SERVER_NAME_MAX];
		UBYTE	Primary_DNS_Server[SYS_INF_IP_ADDRESS_OCTET_MAX];
		UBYTE	Secondary_DNS_Server[SYS_INF_IP_ADDRESS_OCTET_MAX];
		UBYTE	GatewayAddress[SYS_INF_IP_ADDRESS_OCTET_MAX];
		UBYTE	OptionalSetting;
		UWORD	StartTime;
		UWORD	EndTime;
		UWORD	IntervalTime;
		UWORD	HoldTime;
};

/*	PPP_Authentication	*/
#define		SYS_INF_PPP_AUTH_PAP			0
#define		SYS_INF_PPP_AUTH_CHAP			1
#define		SYS_INF_PPP_AUTH_NONE			2

/*	OptionalSetting	*/
#define		SYS_INF_TXRX_ON					0x01
#define		SYS_INF_AUTO_RX_ON				0x02
#define		SYS_INF_AUTO_PRINT_ON			0x04
#define		SYS_INF_SECURE_RX_ON			0x08	/*　親展受信の有効無効（初期値無効）*/

/************************
 **	ユーザーデータ更新状態
 ************************/
struct	SYS_INF_UserDataStatus_t		{
		UBYTE	Status;				/*　0:通常　1:編集中　*/
		UBYTE	ChangeMailBox;		/*　0:MailBox変更なし　1:MailBox変更有り　*/
		UBYTE	UserCodeNumber;
		UBYTE	UserName;
		UBYTE	TelNumber;
		UBYTE	PIN_Number;
		UBYTE	ISP_Name;
		UBYTE	PPP_LoginID;
		UBYTE	PPP_Password;
		UBYTE	PPP_Authentication;
		UBYTE	POP_LoginID;
		UBYTE	POP_Password;
		UBYTE	IP_Address;
		UBYTE	MailAddress;
		UBYTE	ISP_ServerAddress;
		UBYTE	POP_Server;
		UBYTE	SMTP_Server;
		UBYTE	Primary_DNS_Server;
		UBYTE	Secondary_DNS_Server;
		UBYTE	GatewayAddress;
};

/************************
 **	自動受信データ登録
 ************************/

/*	自動受信コマンド作成用の構造体	*/
struct	SYS_INF_AutoRcvData_t	{
		UBYTE	Status;
		UDWORD	StartTime;
		UDWORD	EndTime;
		UWORD	IntervalTimer;
};

/*	Status	*/
#define		SYS_INF_AUTO_RCV_OFF		0	/*	自動受信OFF						*/
#define		SYS_INF_AUTO_RCV_READY		1	/*	データがセットされ開始時間待ち	*/
#define		SYS_INF_AUTO_RCV_WAITING	2	/*	次の実行まで待機中				*/
#define		SYS_INF_AUTO_RCV_EXECUTE	3	/*	自動受信を実行中				*/

/**************************
 **	メール用コマンドデータ
 **************************/
/*	コマンドファイル、Ｐワンタッチで使用	*/
#define		SYS_INF_ONETOUCH_POSITION_MAX		9	/*	9byte×8bitでワンタッチ72個分	*/

/*	ダイレクト入力できるアドレスの件数	*/
#define		SYS_INF_MAIL_DIRECT_COUNT_MAX	5

/*	コマンドファイルの数（通信予約の最大件数）	*/
#define		SYS_INF_MAIL_COM_MAX	99

struct	SYS_INF_MailCommandData_t		{
		UBYTE	Status;
		UBYTE	Kind;
		UBYTE	UserNumber;
		UBYTE	SubDialPosition;
		UDWORD	ExecTime;
		UBYTE	RedialCount;
		UBYTE	RedialInterval;
		UBYTE	Direct[SYS_INF_MAIL_DIRECT_COUNT_MAX][SYS_INF_MAIL_ADDRESS_MAX];
		UBYTE	Onetouch[SYS_INF_ONETOUCH_POSITION_MAX];
		UBYTE	FoundJunkMail;
		UBYTE	ListPrintRequest;
		UBYTE	Result;
};

/*	Status	*/
#define		SYS_INF_MAIL_CMD_EMPTY		0	/*	未使用				*/
#define		SYS_INF_MAIL_CMD_SETTING	1	/*	設定中				*/
#define		SYS_INF_MAIL_CMD_WAITING	2	/*	実行待ち			*/
#define		SYS_INF_MAIL_CMD_EXECUTE	3	/*	実行中				*/
#define		SYS_INF_MAIL_CMD_REDIAL		4	/*	リダイアル待ち		*/
#define		SYS_INF_MAIL_CMD_ERASED		5	/*	消去中				*/
#define		SYS_INF_MAIL_CMD_COMPLETED	6	/*	実行終了			*/

/*	Kind	*/
#define		SYS_INF_NO_JOB			0
#define		SYS_INF_MAIL_TX			1
#define		SYS_INF_MAIL_TXRX		2
#define		SYS_INF_MAIL_MANUAL_RX	3
#define		SYS_INF_MAIL_AUTO_RX	4
#define		SYS_INF_MAIL_AUTO_CHK	5

/*	ListPrintRequest	*/
#define		SYS_INF_LST_ERROR_PRINT		0x01 /*	チェックメッセージ		*/
#define		SYS_INF_LST_JUNK_PRINT		0x02 /*	メールボックス状況通知	*/
#define		SYS_INF_LST_SECURE_PRINT	0x04 /*	親展受信通知			*/

/*	Result	*/
#define		SYS_INF_RESULT_OK			0	/*	エラーなし。正常終了						*/
#define		SYS_INF_RESULT_DIALBUSY		1	/*	BUSY										*/
#define		SYS_INF_RESULT_NODIALTONE	2	/*	NO　DIALTONE								*/
#define		SYS_INF_RESULT_DIALTIMEOUT	3	/*	DIAL　TIMEOUT								*/
#define		SYS_INF_RESULT_NOCARRIER	4	/*	NO　CARRIER									*/
#define		SYS_INF_RESULT_INIT_ERR		5	/*	発呼前のボード初期化時にエラーコード		*/
#define		SYS_INF_RESULT_COM_ERR		6	/*	通信中にボードからエラーコード				*/
#define		SYS_INF_RESULT_CDC_ERR		7	/*	原稿蓄積・読み出しでコーデックエラー		*/
#define		SYS_INF_RESULT_INIT_NORES	8	/*	発呼前のボード初期化時にボードから応答無し	*/
#define		SYS_INF_RESULT_COM_NORES	9	/*	通信中にボードから応答無し					*/
#define		SYS_INF_RESULT_MEM_OVER		10	/*	メモリオーバー								*/
#define		SYS_INF_RESULT_BOX_FULL		11	/*	受信管理テーブルフル						*/
#define		SYS_INF_RESULT_NO_MAIL		12	/*	新着メールなし								*/
#define		SYS_INF_RESULT_ILL_ERR		13	/*	その他のエラー								*/
#define		SYS_INF_RESULT_ABORT		14	/*	ユーザーによる通信中断終了					*/
#define		SYS_INF_RESULT_POWEROFF		15	/*	実行中に電源断								*/

/**************************
 **	通信予約管理データ
 **************************/
struct	SYS_INF_MailCommandStatus_t		{
		UBYTE		Status;			/*	コマンドのStatus	*/
		UBYTE		UserNumber;		/*	コマンドを所有しているユーザー番号	*/
};

/**************************
 **	受信メール管理データ
 **************************/
/*	送信元名	*/
#define		SYS_INF_MAIL_BOX_MAX		100	/*	親展・代行受信は最大100件	*/

struct	SYS_INF_RxMailBoxTable_t		{
		UBYTE	Status;
		UBYTE	UserNumber;
		UBYTE	CommandNo;
		UBYTE	PrintPolicy;
		UBYTE	DocumentType;
		UBYTE	From[SYS_INF_MAIL_ADDRESS_MAX];
		UBYTE	NextBoxNo;
		UWORD	HoldTime;
};

/*	Status	*/
/*	メールボックスの使用状況	*/
#define		SYS_INF_RX_MAIL_EMPTY			0	/*	未使用	*/
#define		SYS_INF_RX_MAIL_RESERVED		1	/*	使用するために予約済み	*/
#define		SYS_INF_RX_MAIL_RECEIVING		2	/*	受信中		*/
#define		SYS_INF_RX_MAIL_RECEIVED		3	/*	受信済み	*/
#define		SYS_INF_RX_MAIL_RELEASED		4	/*	プリント終了しリンクから外された（消去予定）	*/
#define		SYS_INF_RX_MAIL_POWEROFF		5	/*	電源断検出	*/
/*	以下は更新の際に、|=でセットされるステータス	*/
#define		SYS_INF_RX_MAIL_RENEWAL			0x10	/*	プリントの順序を更新中		*/
#define		SYS_INF_RX_MAIL_TOP_RELEASE		0x20	/*	先頭のBOXをリンクからはずす	*/
#define		SYS_INF_RX_MAIL_RELEASE			0x40	/*	BOXをリンクからはずす		*/

/*	PrintPolicy		*/
#define		SYS_INF_AUTO_PRINT		0
#define		SYS_INF_MANUAL_PRINT	1

/*	DocumentType	*/
/*	原稿の種類		*/
#define		SYS_INF_TEXT_MAIL	0	/*	TEXTメール	*/
#define		SYS_INF_FAX_MAIL	1	/*	FAXメール	*/
#define		SYS_INF_RET_MAIL	2	/*	Returnedメール	*/

/******************************
 **	受信管理テーブル管理データ
 ******************************/
struct	SYS_INF_RxMailBoxStatus_t		{
		UBYTE	Status;			/*	受信管理テーブルのStatus	*/
		UBYTE	UserNumber;		/*	所有しているユーザー番号	*/
};

/******************************
 **	プリント順序管理データ
 ******************************/
struct	SYS_INF_PrintPositionTable_t		{
		UBYTE	PrintTop;
		UBYTE	PrintEnd;
};

/******************************
 **	通信管理記録用データ
 ******************************/
#define		SYS_INF_LOG_MAX		50	/*	送受信合わせて５０件　*/
struct	SYS_INF_MailJournalData_t		{
		UWORD	ConnectTime;	/* 1ヶ月の通信時間（単位　分）　*/
		UWORD	ConnectCount;	/* 1ヶ月の接続回数（単位　回）　*/
		UBYTE	ReadPoint;
		struct	LogData_t		{
				UBYTE	Status;
				UWORD	Number;	/* 通番000～999　*/
				UBYTE	Address[SYS_INF_MAIL_ADDRESS_MAX];	/*　受信したメールのFrom　*/
				UDWORD	StartTime;	/*　通信開始時間　*/
				UWORD	TotallTime;	/*　通信時間　*/
				UBYTE	Result;		/*　通信結果　*/
				UBYTE	Kind;		/*　通信種別　*/
		}Log[SYS_INF_LOG_MAX];
};

/******************************
 **	TEXTﾃﾞｰﾀﾌﾟﾘﾝﾄ用Define
 ******************************/
#define		SYS_INF_READ_CHAR_START		1
#define		SYS_INF_READ_CHAR_CR		2
#define		SYS_INF_READ_CHAR_PAGE		3
#define		SYS_INF_READ_CHAR_END		4

/***************************
** PTTテスト信号種類用Define
***************************/
struct SYS_INF_PTT_Parameter_t {
	UBYTE SignalKind;
	UBYTE GuardTone;
	UBYTE Mode;
	UBYTE DataRate;
	UBYTE SymbolRate;
	UBYTE CarrierBias;
	UBYTE SecondChannel;
	UBYTE UpperBandEdge;
};

/* SignalKind */
/********************************************************
** define名と実際に送出される信号とはずれがありますので、
** 注意してください
********************************************************/
#define SYS_INF_TONAL_SIGNAL_NONE			0
#define SYS_INF_DTMF_TONE_0					1	/* %TT00 */
#define SYS_INF_DTMF_TONE_1					2	/* %TT01 */
#define SYS_INF_DTMF_TONE_2					3	/* %TT02 */
#define SYS_INF_DTMF_TONE_3					4	/* %TT03 */
#define SYS_INF_DTMF_TONE_4					5	/* %TT04 */
#define SYS_INF_DTMF_TONE_5					6	/* %TT05 */
#define SYS_INF_DTMF_TONE_6					7	/* %TT06 */
#define SYS_INF_DTMF_TONE_7					8	/* %TT07 */
#define SYS_INF_DTMF_TONE_8					9	/* %TT08 */
#define SYS_INF_DTMF_TONE_9					10	/* %TT09 */
#define SYS_INF_DTMF_TONE_AST				11	/* %TT0A */
#define SYS_INF_DTMF_TONE_SHARP				12	/* %TT0B */
#define SYS_INF_DTMF_TONE_A					13	/* %TT0C */
#define SYS_INF_DTMF_TONE_B					14	/* %TT0D */
#define SYS_INF_DTMF_TONE_C					15	/* %TT0E */
#define SYS_INF_DTMF_TONE_D					16	/* %TT0F */
#define SYS_INF_V21_CH1_MK_SYMBOL			17	/* %TT10 */
#define SYS_INF_V21_CH2_MK_SYMBOL			18	/* %TT11 */
#define SYS_INF_V23_BWARD_CH_MK_SYMBOL		19	/* %TT12 */
#define SYS_INF_V23_FWARD_CH_MK_SYMBOL		20	/* %TT13 */
#define SYS_INF_V22_CALL_MK_600BPS			21	/* %TT14 */
#define SYS_INF_V22_CALL_MK_1200BPS			22	/* %TT15 */
#define SYS_INF_V22BIS_CALL_MK_2400BPS		23	/* %TT16 */
#define SYS_INF_V22_ANSWER_SIGNAL			24	/* %TT17 */
#define SYS_INF_V22BIS_ANSWER_SIGNAL		25	/* %TT18 */
#define SYS_INF_V21_CH1_SP_SYMBOL			26	/* %TT19 */
#define SYS_INF_V21_CH2_SP_SYMBOL			27	/* %TT1A */
#define SYS_INF_V23_BWARD_CH_SP_SYMBOL		28	/* %TT1B */
#define SYS_INF_V23_FWARD_CH_SP_SYMBOL		29	/* %TT1C */
#define SYS_INF_V32_9600BPS					30	/* %TT20 */
#define SYS_INF_V32BIS_14400BPS				31	/* %TT21 */
#define SYS_INF_V32_TCM_9600BPS				32	/* %TT22 */
#define SYS_INF_V32_TCM_14400BPS			33	/* %TT23 */
#define SYS_INF_V32BIS_TCM_7200BPS			34	/* %TT24 */
#define SYS_INF_V32_4800BPS					35	/* %TT25 */
#define SYS_INF_OFF_FOOK					36	/* %TT30 */
#define SYS_INF_V25_ANSWER_TONE				37	/* %TT31 */
#define SYS_INF_1800HZ_GUARD_TONE			38	/* %TT32 */
#define SYS_INF_V25_SEND_1300HZ				39	/* %TT33 */
#define SYS_INF_FAX_SEND_1100HZ				40	/* %TT34 */
#define SYS_INF_BELL_ANSWER_2225HZ			41	/* %TT35 */
#define SYS_INF_V21_CH2						42	/* %TT40 */
#define SYS_INF_V27TER_2400BPS				43	/* %TT41 */
#define SYS_INF_V27TER_4800BPS				44	/* %TT42 */
#define SYS_INF_V29_7200BPS					45	/* %TT43 */
#define SYS_INF_V29_9600BPS					46	/* %TT44 */
#define SYS_INF_V17_7200BPS_L_TRAIN			47	/* %TT45 */
#define SYS_INF_V17_7200BPS_S_TRAIN			48	/* %TT46 */
#define SYS_INF_V17_9600BPS_L_TRAIN			49	/* %TT47 */
#define SYS_INF_V17_9600BPS_S_TRAIN			50	/* %TT48 */
#define SYS_INF_V17_12000BPS_L_TRAIN		51	/* %TT49 */
#define SYS_INF_V17_12000BPS_S_TRAIN		52	/* %TT4A */
#define SYS_INF_V17_14400BPS_L_TRAIN		53	/* %TT4B */
#define SYS_INF_V17_14400BPS_S_TRAIN		54	/* %TT4C */
#define SYS_INF_VFC_MODULATION				55
#define SYS_INF_V34_MODULATION				56

/* GuardTone */
/* %TT17,18で選択 */
#define SYS_INF_NO_GUARD_TONE				0
#define SYS_INF_GUARD_TONE_550				1
#define SYS_INF_GUARD_TONE_1800				2

/* Mode */
/* %TT2x, %TT4xで選択 */
#define SYS_INF_NO_MODE						0
#define SYS_INF_ORIGINATE_MODE				1
#define SYS_INF_ANSWER_MODE					2

/*
** SignalKindがSYS_INF_VFC_MODULATIONか
** SYS_INF_V34_MODULATIONのときのみ他のメンバ有効
*/
/* DataRate */
#define SYS_V34_DRATE_2400BPS			0
#define SYS_V34_DRATE_4800BPS			1
#define SYS_V34_DRATE_7200BPS			2
#define SYS_V34_DRATE_9600BPS			3
#define SYS_V34_DRATE_12000BPS			4
#define SYS_VFC_OR_V34_DRATE_14400BPS	5
#define SYS_VFC_OR_V34_DRATE_16800BPS	6
#define SYS_VFC_OR_V34_DRATE_19200BPS	7
#define SYS_VFC_OR_V34_DRATE_21600BPS	8
#define SYS_VFC_OR_V34_DRATE_24000BPS	9
#define SYS_VFC_OR_V34_DRATE_26400BPS	10
#define SYS_VFC_OR_V34_DRATE_28800BPS	11

/* SymbolRate */
#define SYS_VFC_OR_V34_SRATE_2400		0
#define SYS_VFC_OR_V34_SRATE_RESERVE	1
#define SYS_VFC_OR_V34_SRATE_2800		2
#define SYS_VFC_OR_V34_SRATE_3000		3
#define SYS_VFC_OR_V34_SRATE_3200		4
#define SYS_VFC_OR_V34_SRATE_3429		5

/* CarrierBias */
/* 値を直に代入 */
/* -100 ～ -10, -5, 0, 5, 10 ～ 100 */

/* SecondChannel */
#define SYS_VFC_OR_V34_2ND_CH_DISABLE	0
#define SYS_VFC_OR_V34_2ND_CH_ENABLE	1

/* UpperBandEdge */
/* V.FCは値を直に代入 */
/* 0,1,2,3,4,5,6,7,8,9,10,12,13,14,15,22 */
/* V.34は選択 */
#define SYS_V34_BAND_EDGE_0DB	0
#define SYS_V34_BAND_EDGE_2DB	1
#define SYS_V34_BAND_EDGE_4DB	2
#define SYS_V34_BAND_EDGE_6DB	3
#define SYS_V34_BAND_EDGE_8DB	4
#define SYS_V34_BAND_EDGE_10DB	5
#define SYS_V34_BAND_EDGE_G1DB	6
#define SYS_V34_BAND_EDGE_G2DB	7
#define SYS_V34_BAND_EDGE_G3DB	8
#define SYS_V34_BAND_EDGE_G4DB	9
#endif
