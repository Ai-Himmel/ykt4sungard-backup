#ifndef sysfcode_h
	#define sysfcode_h

/*#if (PRO_F_CODE == ENABLE)*/
/***************************************************************
 サブアドレスＢＯＸ
 ***************************************************************/
/* struct SYS_SubAddressBox_t SYB_SubAddressBoxTable[SUB_ADDRESS_BOX_MAX]; */

#define	SUB_ADDRESS_BOX_MAX 50		/* ５０個まで管理 */

struct SYS_SubAddressBoxData_t {
UBYTE	Status;							/* 管理テーブルの登録状態 */
UBYTE	BoxName[SYS_BOX_NAME_MAX];		/* ＢＯＸ名 */
UBYTE	SubAddress[SYS_ID_MAX];	/* サブアドレス ２０桁＋NULL */
UBYTE	PassWord[SYS_ID_MAX];	/* 通信パスワード ２０桁＋NULL */
UBYTE	DataStatus;						/* 受信・蓄積原稿状態 */
UBYTE	MessageStatus;					/* メッセージ出力状態 */
UBYTE	RemoteName[SYS_REMOTE_NAME_MAX];/* 受信相手先名(NULL含む) */
UBYTE	HoldTime;						/* 保持期間 */
UBYTE	Option;							/* オプション設定 */
UBYTE	ScnStoringNo;					/* 蓄積中のＮｏ */
UBYTE	RxStoringNo;					/* 蓄積中のＮｏ */
UBYTE	Dummy;							/* ダミー */
UWORD	PassCode;						/* パスコード(暗証番号) */
UDWORD	ErasedTime;						/* 消去時間 */
UDWORD	StoredDocBit;					/* 蓄積されている原稿をﾋﾞｯﾄで管理 */
#if (PRO_FCODE_RELAY == ENABLE) /* Add 3 Member By H.Hirao 1998/08/21 */
	UBYTE Onetouch[SYS_ONETOUCH_BIT_FIELD_MAX];	/* 中継配信先（ワンタッチ）*/
	UBYTE Speed[SYS_SPEED_BIT_FIELD_MAX];		/* 中継配信先（短縮）*/
	UDWORD Group;								/* 中継配信先（グループ）*/
#endif
};

#define	SUB_ADDRESS_BOX_EMPTY		0x00	/* ボックス未使用 */
#define	SUB_ADDRESS_BULLETIN_BOX	0x01	/* 掲示板登録	*/
#define	SUB_ADDRESS_SECURE_BOX		0x02	/* 親展登録	*/
#define	SUB_ADDRESS_RELAY_BOX		0x03	/* 中継登録 */

/************************************************************************
 * サブアドレスＢＯＸの受信状態											*
 ************************************************************************/
#define SYS_SUB_ADDRESS_BOX_NO_SET		0	/* 未蓄積 */
#define SYS_SUB_ADDRESS_BOX_STORED		1	/* 蓄積原稿あり */
#define SYS_SUB_ADDRESS_BOX_STORING		2	/* 蓄積中原稿あり */
#define SYS_SUB_ADDRESS_BOX_RECEIVE		3	/* 受信原稿有り */
#define SYS_SUB_ADDRESS_BOX_RECEIVING	4	/* 受信中原稿有り */
#define SYS_SUB_ADDRESS_BOX_TXING		5	/* ﾎﾟｰﾘﾝｸﾞ送信中 */
#define SYS_SUB_ADDRESS_BOX_DELETING	6	/* 蓄積原稿消去中 */
#define SYS_SUB_ADDRESS_BOX_PRINTING	7	/* 蓄積原稿プリント中 */


#define SYS_SUB_ADDRESS_BOX_PRT_RX		10	/* プリント中且つ 受信中 */
#define SYS_SUB_ADDRESS_BOX_PRT_TX		11	/* プリント中且つ 送信中 */
#define SYS_SUB_ADDRESS_BOX_STR_TX		12	/* 蓄積中且つ 送信中 */


/************************************************************************
 * サブアドレスＢＯＸのメッセージの出力状態								*
 ************************************************************************/
#define SYS_SUB_ADDRESS_BOX_MSG_EMPTY	0	/* 無し */
#define SYS_SUB_ADDRESS_BOX_RCV_MSG		1	/* 親展受信通知メッセージ */
#define SYS_SUB_ADDRESS_BOX_ERASED_MSG	2	/* 消去メッセージ */

/********************************************************************
 * オプション設定													*
 ********************************************************************/
#define	SUB_ADDRESS_OPTION_NONE		0x00	/* オプション設定なし */
#define	SUB_ADDRESS_OPTION_RECEIVE	0x01	/* 受信禁止	*/
#define	SUB_ADDRESS_OPTION_PRINT	0x02	/* 掲示板受信時のプリント、中継配信局の同報原稿プリント */
#define	SUB_ADDRESS_OPTION_ERASE	0x04	/* 送信時原稿消去 */
#define	SUB_ADDRESS_OPTION_DOC_ADD	0x08	/* 原稿蓄積時、追加／上書き */
#define SUB_ADDRESS_OPTION_TTI_AVAIL	0x10	/* 中継配信時に配信局の発信元を付ける */
#define SUB_ADDRESS_OPTION_TTI_INSIDE	0x20	/* 中継配信時に配信局の発信元を上書きで付ける（SUB_ADDRESS_OPTION_TTI_AVAILABLEが有効時に有効） */

/**************************************************************
 *	Ｆコード登録データの構造体
 **************************************************************/
struct	SYS_FcodeNumberData_t	{
	UBYTE	SYS_SubAddressNumber[SUB_ADDRESS_NUMBER_MAX];	/* ＳＵＢの値を格納、選択ﾎﾟｰﾘﾝｸﾞ時はＳＥＰの値を格納 */
	UBYTE	SYS_PassWordNumber[PASSWORD_NUMBER_MAX];		/* ＰＷＤの値を格納 */
};

/*	#define	SUB_ADDRESS_NUMBER_MAX		11	/@ ＳＵＢ  BCDで20桁、終端ｺｰﾄﾞ0xff */
/*	#define	PASSWORD_NUMBER_MAX			11	/@ ＰＷＤ  BCDで20桁、終端ｺｰﾄﾞ0xff */
#define SYS_SUBADDRESS_BOX_INDEX_MAX	30	/* １ＢＯＸにつきの最大原稿数 */

#define FULL_STORED		0xFF	/* 原稿最大まで蓄積されている */

/*#endif*/

#endif
