/* ichou をベースにANZU での追加分をプラスしました	By Y.Suzuki 1996/10/14 */
/* Original File : jun\usr2:\src\ichou\define\syscomf.h */
#ifndef syscomf_h
	#define syscomf_h

#include "\src\atlanta\define\sysdial.h"
#if defined (KEISATSU) /* 警察FAX 05/06/22 石橋正和 */
#include "\src\atlanta\define\fcm_def.h"
#endif

/************************************************************************
 * 通信予約																*
 * struct SYS_CommandData_t far SYB_CommandFile[SYS_COM_FILE_MAX]		*
 * syscomf.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 * SYSCOMF.JAW に基づきFX機能追加 Y.Suzuki 19.Apr'94					*
 ************************************************************************/
struct SYS_OptionData_t	{
	UBYTE Item;					/* 通信種別 */
	union {
		WORD SecureNumber;		/* 親展番号 */
								/* スカラー値 */
		UDWORD RelayGroupNumber;
								/* 中継指示グループ番号 */
								/* 1ビットが1グループに対応 */
								/* LSB:グループ1､MSB:グループ32 */
								/* 最大10グループまで指定可 */
		UBYTE RelaySourceID[SYS_SRC_ID_MAX];
								/* 中継配信親機の発信元番号(NULL含む) */
		UWORD DatabaseNumber[SYS_DATA_BASE_MAX];
								/* 検索ポーリングファイル番号 */
								/* 各ファイル番号をスカラー値でセット */
								/* 最終ファイル番号に続く配列に-1をセット */
/*#if (PRO_F_CODE == ENABLE)*/
		UBYTE FcodeDataPosition[F_CODE_DATA_MAX + 1];
								/* Ｆコードに使用されるﾊﾟｽﾜｰﾄﾞ、ｻﾌﾞｱﾄﾞﾚｽ等の登録されているポジション */
								/* 最終ｻﾌﾞｱﾄﾞﾚｽﾎﾟｼﾞｼｮﾝに続く配列に-1をセット */
/*#endif*/
		UBYTE BatchNumber;		/* 一括送信番号  */
#if (PRO_MAKER == FX)
		struct FX_RelayData_t {
			UBYTE Passcode;					/* 中継指示用パスコードＮＯ．（指示機のTELNO．の登録された中継機の短縮NO.*/
			UBYTE Number[SYS_FX_RELAY_MAX];	/* 中継機にセットされている、短縮、グループNO.*/
			UBYTE DocumentPrint;			/* 中継機でのプリントの有無 */
		} FX_Relay;
		struct FX_SecureData_t {
			UWORD Passcode;					/* 0000--9999 スカラー値 */
			UBYTE Number;					/* 1--10 スカラー値 */
		} FX_Secure;
#endif
	} OptionNumber;
	UBYTE ConfirmationReport;		/* 通信証 */
};


struct SYS_CommandData_t {
	UBYTE Status;						/* 使用状況 */
	struct SYS_DialData_t DialNumber;	/* 電話番号 */
	UDWORD ExecTime;					/* 発信時間 */
										/* 1992年1月1日0時0分0秒からの蓄積秒数 */
	struct SYS_OptionData_t Option;		/* 応用通信機能 */
	UWORD DepartmentCode;				/* 部門管理コード */
	UWORD Page;							/* ページ数 */
										/* 原稿枚数指定がある場合はその値をセット */
	UBYTE Type;							/* 送受信一体型時の送受の識別 */
	UBYTE TitleMessage;					/* タイトルメッセージ */
										/* メッセージの配列オフセット値 */
										/* 未使用時はｰ1 */
#if 0	/* UWORDに変更 1997/05/09  By T.Yamaguchi */
**	UBYTE Page;							/* ページ数 */
**										/* 原稿枚数指定がある場合はその値をセット */
#endif
	UBYTE Ability;						/* 付加属性 */
/*#if (PRO_PIN_ACCESS == ENABLE)*/
	UBYTE PIN_AccessMode;				/** ＰＩＮアクセスモード。コマンド登録時のSYS_SettingStatusに値 1996/01/08 Eguchi */
	UBYTE PIN_Number[SYS_PIN_MAX];		/** PIN番号登録ＢＣＤコードで８桁まで。 By S.K Sep.21,1995 ANZU */
/*#endif*/
#if (PRO_RX_DOC_TRANSFER == ENABLE)		/* 受信原稿の転送(FAXワープ) H.Yoshikawa 1998/09/29 */
	UWORD PrintPage;					/* 転送エラー発生時には、チェックメッセージとして全ページプリントする */
#endif
}
;

/************************************************************************
 * 通信予約の使用状況													*
 * struct SYS_CommandData_t.Status										*
 * syscomf.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_CMD_EMPTY		0	/* 未使用 */
#define SYS_CMD_SETTING		1	/* セット中 */
#define SYS_CMD_WAITING		2	/* 予約中 */
#define SYS_CMD_EXECUTE		3	/* 予約実行中 */
#define SYS_CMD_ERASED		4	/* 予約取消 */
#define SYS_CMD_POWER_OFF	5	/* 電源断 */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/14 Y.Murata for KAKI */
#define SYS_CMD_WAITING_QUICK		6	/* クイック送信予約中 */
#define SYS_CMD_EXECUTE_QUICK		7	/* クイック送信予約実行中 */
#endif

/************************************************************************
 * 通信予約の付加情報													*
 * struct SYS_CommandData_t.Ability										*
 * syscomf.jsw参照														*
 * 1993/11/19															*
 * ＜SYS_OPTION_PRINTがONのとき＞										*
 * 送信エラーとなり、中継機でチェックメッセージをプリントするときに		*
 * このBitが１のときは、すでに中継機で同時プリント済みなので、			*
 * 従来と同じリスト＋画像１ページ一体型チェックメッセージをプリントする *
 * このBitが０のときは、中継機ではプリントされていないので、			*
 * リスト・画像分離型チェックメッセージをプリントする。					*
 * 画像は全ページプリントするものとする。								*
 * 1998/09/25															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_OVERSEA				0x01	/* MemorySwitch[10]のビット4をローカ
										 * ル的に有効とする
										 */
#define	SYS_WARP_PRINT			0x02	/* ワープの同時プリント */
#define	SYS_TTI_TX_AVAILABLE	0x04	/*【CSDR-No.102】発信元ON/OFF By H.Fujimura 1998/12/17 */

/************************************************************************
 * 通信予約の通信種別													*
 * struct SYS_CommandData_t.Item											*
 * syscomf.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_CHAR_TX					0	/* キャラクタ送信 */
#define SYS_SCANNER_TX				1	/* 即時スキャナ送信 */
#define SYS_MEMORY_TX				2	/* 即時メモリ送信 */
#define SYS_DELAYED_SCANNER_TX		3	/* 時刻指定スキャナ送信 */
#define SYS_DELAYED_MEMORY_TX		4	/* 時刻指定メモリ送信 */
#define SYS_SCANNER_SECURE_TX		5	/* スキャナ親展送信 */
#define SYS_MEMORY_SECURE_TX		6	/* メモリ親展送信 */
#define SYS_SCANNER_RELAY_BROADCAST	7	/* スキャナ中継指示送信 */
#define SYS_MEMORY_RELAY_BROADCAST	8	/* メモリ中継指示送信 */
#define SYS_DELAYED_BROADCAST		9	/* 順次同報送信 */
#define SYS_RELAYED_TX				10	/* 中継配信送信 */
#define SYS_POLLING_RX				11	/* ポーリング受信 */
#define SYS_DB_POLLING_RX			12	/* 検索ポーリング受信 */
#define SYS_SEQUENTIAL_POLLING		13	/* マルチポーリング受信 */
#define SYS_FX_MEMORY_RELAY_TX		14	/*	FX用メモリ中継指示送信	 1994/04/25 石橋正和 */
#define SYS_FX_SCANNER_RELAY_TX		15	/*	FX用スキャナ中継指示送信 1994/04/25 石橋正和 */
#define SYS_FX_MEMORY_SECURE_TX		16	/*	FX用メモリ親展送信		 1994/04/25 石橋正和 */
#define SYS_FX_SCANNER_SECURE_TX	17	/*	FX用スキャナ親展送信	 1994/04/25 石橋正和 */

#define SYS_POLLING_TX				18	/*	ﾎﾟｰﾘﾝｸﾞ送信		 */
#define SYS_DB_POLLING_TX			19	/*	検索ﾎﾟｰﾘﾝｸﾞ送信	 */
#define SYS_MANUAL_RECEIVE			20	/*	手動受信		 */
#define SYS_MANUAL_TRANSMIT			21	/*	手動送信		 */
#define SYS_FIP_TRANSMIT			22	/*	FIP送信			 */
#define SYS_FIP_RECEIVE				23	/*	FIP受信			 */
#define SYS_FIP_POLLING				24	/*	FIPﾎﾟｰﾘﾝｸﾞ		 */
#define SYS_FIP_SECURE				25	/*	FIP親展受信		 */
#define SYS_NO_PAPER_RX				26	/*	代行受信		 */
#define SYS_SECURE_RX				27	/*	親展受信		 */
#define SYS_RELAY_RX				28	/*	中継受信		 */
#define SYS_REMOTE_RX				29	/*	ﾘﾓｰﾄFAX受信		 */
#define SYS_REMOTE_TX				30	/*	ﾘﾓｰﾄFAX送信		 */
#define SYS_BATCH_MEMORY_TX			31	/*	一括送信 By Murata Jan.15,1994 */
#define	SYS_RELAYED_TX_REPORT		32	/*	配信用不達通知	 Nov.24,1994 */
#define SYS_SECURE_DIALIN_RX		33	/*	ダイヤルイン親展受信 */
#define SYS_CONTINUOUS_POLLING_RX	34	/*	連続ポーリング	 */

/*	 F-Codeの追加により新たに設ける通信種別	 */
#define SYS_SELECT_POLLING_RX		35	/*	選択ﾎﾟｰﾘﾝｸﾞ受信(掲示板を受信）*/
#define SYS_SELECT_POLLING_TX		36	/*	選択ﾎﾟｰﾘﾝｸﾞ送信				  */
#define SYS_SCANNER_SUB_ADDRESS_TX	37	/*	Ｆｺｰﾄﾞｽｷｬﾅ送信(親展・掲示板に送信） */
#define SYS_MEMORY_SUB_ADDRESS_TX	38	/*	Ｆｺｰﾄﾞﾒﾓﾘ送信(親展・掲示板に送信） */
#define SYS_SUBADDRESS_SECURE_RX	39	/*	Ｆｺｰﾄﾞ親展受信				  */
#define SYS_MEMORY_RELAY_BOX_RX		40	/*	中継ﾎﾞｯｸｽ受信				  */
#define SYS_SUB_ADDRESS_RELAYED_TX	41	/*	中々継ﾎﾞｯｸｽ送信（中継配信）	  */

#define SYS_CIPHER_TX				42	/*	暗号化送信 By Y.Suzuki 1997/06/03	*/
#define SYS_CIPHER_RX				43	/*	暗号化受信 1997/06/20  By T.Yamaguchi */
#define SYS_SUBADDRESS_BULLETIN		44	/*  Fｺｰﾄﾞ掲示板受信				*/

/************************************************************************
 * 通信予約の通信証														*
 * struct SYS_CommandData_t.ConfirmationReport							*
 * syscomf.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_CFR_PRINT	0x01	/* 通信証を要求有 */
#define SYS_RCR_SELECT	0x02	/* 1の時受領証を選択 */
								/* 0の時送信証を選択 */
#define SYS_TCR_REQUESTED 0x01	/* 通信証要求有、且つ 受領証ＯＦＦのとき送信証選択 1997/09/12  By T.Yamaguchi */
#define SYS_RCR_REQUESTED 0x03	/* 通信証要求有、且つ 受領証を選択 1996/11/29  By T.Yamaguchi */
/* ICHOU変更 ANZUよりコピー by T.Soneoka 1996/08/26 */
#define SYS_TCR_AND_RCR 0x80	/* 受領証要求で相手機が受領証を持っていない場合に
								   送信証をプリントするためのビット 96/06/19 BY T.Yamaguchi */

/***********************************************************************
*		   BY:	 鈴木郁二
*		 DATE:	 Tue 21 Dec 1993
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 UWORD FaxComType;
* DESCRIPTION:	 通信種類
************************************************************************/
#define		SYS_COMMAND_EXECUTE		0
#define		SYS_MANUAL_TX			1
#define		SYS_MANUAL_RX			2
#define		SYS_AUTO_CALLED			3
#define		SYS_FIP_CALLED			4
#define		SYS_RESPONSE_VOICE		5
#define		SYS_FIP_SEND			6
#define		SYS_FIP_POLL			7
#define		SYS_REMOTE_FAX_TX		8	/* ﾘﾓｰﾄFAX取り出し機能 蓄積原稿送信 */
#define		SYS_REMOTE_FAX_RX		9	/* ﾘﾓｰﾄFAX取り出し機能 受信原稿蓄積 */
#define		SYS_REMOTE_DIAG			10	/* ﾘﾓｰﾄ診断 */
#define		SYS_TRANSFER_AUTO_CALLED	11	/* 転送受信 */
#define		SYS_FNET_AUTO_CALLED	12	/* Fﾈｯﾄ受信 */
#define		SYS_MANUAL_POLLING		13	/* 手動ポーリング By MURATA 7/12/1994 */
#define		SYS_CLASS1_PRINT		14 /* ﾛｰｶﾙﾌﾟﾘﾝﾄ起動	by Y.Tanimoto 1996/06/26	*/
#define		SYS_CLASS1_SCAN			15 /* ﾛｰｶﾙｽｷｬﾝ起動	by Y.Tanimoto 1996/06/26	*/
#define		SYS_CLASS1_SCAN_SCANNER	16 /* ﾛｰｶﾙｽｷｬﾝ ｽｷｬﾅｰ送信(ANZUはない)by Y.Tanimoto 1996/06/26	*/
#define		SYS_CLASS1_SCAN_MEMORY	17 /* ﾛｰｶﾙｽｷｬﾝ ﾒﾓﾘｰ送信	by Y.Tanimoto 1996/06/26	*/
#if defined (KEISATSU) /* 警察FAX 05/07/01 石橋正和 */
#define		SYS_ISSEI_TX			18 /* 一斉指令送信 */
#define		SYS_ISSEI_RX			19 /* 一斉指令受信 */
#define		SYS_ISSEI_KIDO_TX		20 /* 指令起動信号による一斉指令送信 */
#define		SYS_ISSEI_KIDO_RX		21 /* 指令起動信号による一斉指令受信 */
#endif


/*************************************************************************
*		   BY:	 山口哲治
*		 DATE:	 Nov.28.1996
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 UWORD FaxComTxType;
* DESCRIPTION:	 送信原稿種別
*			  :従来機までは、通信予約の通信種別(SYS_SCANNER_TX、SYS_MEMORY_TX)の定義を利用
*			  :していたが、区別しにくいので、新たに定義する。
************************************************************************/
#define		SYS_SCANNER_TRANSMIT	1
#define		SYS_MEMORY_TRANSMIT		2



#if defined (KEISATSU)
/************************************************************************
	通信予約コマンドの警察FAX属性
											2005/06/22 石橋正和
************************************************************************/
struct SYS_CommandKeisatsu_t {
	UBYTE Line;		/* SYS_LINE_KANYU:加入 SYS_LINE_KEIDEN:警電 */
	BOOL Scramble;	/* TRUE:スクランブル通信 FALSE:非スクランブル通信 */
	BOOL Senyo;		/* TRUE:専用 FALSE:共通 */
};

#endif

#endif
