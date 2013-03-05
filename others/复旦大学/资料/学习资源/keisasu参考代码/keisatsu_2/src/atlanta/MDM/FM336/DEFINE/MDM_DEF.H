#ifndef mdm_def_h
	#define mdm_def_h 1

#include "\src\atlanta\define\mem_def.h"

#if (PRO_MODEM_R288F_VERSION != FM336_VERSION_12P)
#error "PRO_MODEM is not set to FM336!! Check the source code again."
#endif


/* 送信結果(MDM_TxPix()ﾘﾀｰﾝ値) */
/*												MG3	MECM	SG3	SECM		*/
#define TX_PAGE_END					0		/*	○	○					1ﾍﾟｰｼﾞ送信完了 				*/
#define TX_BLOCK_END				1		/*	×	○					64KByte送信完了 				*/
#define TX_STOPPED					2		/*	○	○					停止ＳＷ　ＯＮ 				*/
#define TX_DOC_ERR					3		/*	×	×					原稿繰り込み不良 			*/
#define TX_LAMP_ERR					4		/*	×	×					ﾗﾝﾌﾟｴﾗｰ 						*/
#define TX_FILE_ERR					5		/*	△	△					該当するﾒﾓﾘﾌｧｲﾙが存在しない 	*/
#define TX_MEM_ERR					6		/*	○	○					画像ﾒﾓﾘ画品質不良 			*/
#define TX_1M_OVER					7 		/*	×	×					ｽｷｬﾅ送信が１ｍを越えた 		*/
#define TX_SEPARATE					8 		/*	○	○					F網設定時、送信がA4 2枚分に達した 		*/
											/*							村田は相手側の記録紙長は無視する仕様なので、分割送信はなし	*/
	/* 以下３項目FCMで使用 by S.T */
#define TX_END						9		/* 全ページ送信終了                 */
#define TX_PAGE_END_MODE_CHANGE		10		/* １ページ送信終了モード変更あり   */
#define TX_PAGE_END_RCR				11		/* １ページ送信終了，受領証要求あり */
#define TX_PIX_OPEN_ERR				12		/* 送信オープンエラー */ /* 1996/05/17 Y.Murata */
#define TX_NEXT_FILE				13		/* １ファイル送信終了、次ファイルあり 1997/05/12  By T.Yamaguchi */

/* 受信結果(MDM_RxPix()ﾘﾀｰﾝ値) 					MG3 MECM	PG3	PECM	*/
#define RX_CONTINUE					0		/*	×	○					Now Recieving 				*/
#define RX_PAGE_END					1		/*	○	○					1ﾍﾟｰｼﾞ受信完了 				*/
#define RX_BLOCK_END				2		/*	×	○					64KByte受信完了 				*/
#define RX_STOPPED					3		/*	○	○					停止ＳＷ　ＯＮ 				*/
#define RX_MEM_OVER					4		/*	○	○					画像ﾒﾓﾘ･ｵｰﾊﾞｰ 				*/
#define RX_CARRIER_DOWN				5		/*	○	×					ｷｬﾘｱ断(EOL未検出) 			*/
#define RX_ERROR					6		/*	○	○					画品質不良 					*/
#define RX_TMOUT					7		/*	×	○					Time Out 					*/
#define RX_STUP_ERR					8		/*	○	○					Set Up Error 				*/
#define RX_PRT_ERR					9		/*	×	×					Printer Error 				*/
#define RX_CONTI_ERR				10		/*	×	×					連続ｴﾗｰﾗｲﾝ数がMAX値を越えた 	*/
#define RX_OVER						11      /*	○	○					１枚の受信ﾃﾞｰﾀ長がA4(B4)+10%を越えた*/
#define RX_PAPER_END				12      /*	○	○					黒エンドマークを検出した	*/

/* 送信種別(MDM_TxPix()の引き数) */
#define TX_SCAN						0
#define TX_MEMORY					1
#define TX_RCR						2
#define TX_CVR						3
#define TX_REMOTE_FAX_MSG			4
#define TX_BKUPRAM					5	/* ●ICHOU追加 by T.Soneoka 1996/06/17 */
#define TX_RELAYED_TX_REPORT		6 /* 不達通知のため。 H.Kubo 1998/01/17 */

/* 受信種別(MDM_RxPix()の引き数) */
#define RX_PRINTER		0
#define RX_MEMORY		1
#define RX_BKUPRAM		2	/* ●ICHOU追加 by T.Soneoka 1996/06/17 */ /* Added by H.Kubo 1997/07/15  */

/* ＥＣＭステータス配列サイズ 8*32=256*/
#define ECM_STATUS_MAX	32

/* モデムバッファサイズ	*/
#define MODEM_BUFFER_LENGTH		(256+8)		/** R288モデムはフラグコードを出力する為１バイト足りない By O.K Jan.23,1996 **/

/* モデムバッファサイズ	*/
#define MODEM_FRAMING_CODE_LENGTH	7	/* フラグ／アドレス／コントロール／ＦＣＳ（２バイト）／フラグ By O.K Feb.17,1996 */

/* モデムバッファ本数	*/
#define	MODEM_BUFFER_MAX		8

/*	命令受信／応答受信のフラグ検出タイマ値引き数　単位は１０ｍｓ	*/
#define	TIME_OVER_3SEC			300		/* ３．０秒 　CNG送出しまがらの命令受信及び通常の応答受信 */
#define	TIME_OVER_45SEC			450		/* ４．５秒　手動受信時の１発目のＤＣＳ受信まで */
#define	TIME_OVER_48SEC			480		/* ４．８秒　ECM応答４．８秒設定時 */
#define	TIME_OVER_6SEC			600		/* ６．０秒　通常命令受信及びﾘﾓｰﾄ診断時 */
#define	TIME_OVER_10SEC			1000	/* １０．０秒　R.4.2対策 */

/* 命令／応答受信／会話予約用命令受信／高低速識別戻り値 */
#define	FSK_RECEIVE			0
#define FSK_ERROR			1
#define	TEL1_OH_DETECT		2
#define	TEL2_OH_DETECT		3
#define	HOOK_KEY_OH_DETECT	4
#define	T3_TIME_OVER		5
#define T1_TIME_OVER		6	/*	'94.4.7 add by T.Soneoka	*/
#define TRN_RECEIVE			7
#define TIME_OVER			8
#define	CALL_INDICATOR_RECEIVE	9	/* 起呼表示信号受信 とりあえずｺﾝﾊﾟｲﾙ通すため追加 1995/11/21 Y.Murata */
#define	TURN_OFF_RECEIVE		10	/* 起呼表示信号受信 とりあえずｺﾝﾊﾟｲﾙ通すため追加 1995/12/12 Y.Murata */
#define CC_RETRAIN				11	/* コントロールチャンネルリトレイン検出 By O.Kimoto 1996/05/17 */

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/11 */
#define	PHB1_DETECT_BUSY_TONE	12	/* ビジートーン検出 新Ｌ４００ */
 #endif
#endif
#if defined (KEISATSU) /* 警察FAX 05/09/16 石橋正和 */
#define MDM_DETECT_CNG			13 /* CNG検出 */
#define MDM_ISSEI_TX			14 /* 一斉送信へ移行 */
#define MDM_SHIREI_OFF			15 /* 指令起動信号OFF */
#endif

/*	送信側会話予約処理用引き数	*/
#define MODE_T3_TIMER		0	/*	ポストメッセージがＥＯＰの時	'94.4.7 add by T.Soneoka */
#define MODE_T3_T1_TIMER	1	/*	ポストメッセージがＥＯＰ以外の時	'94.4.7 add by T.Soneoka	*/

/*------------------------------------------------------*/
/* ﾄｰﾝｾﾚｸﾄ ﾃｰﾌﾞﾙ No. << MDM_ToneTx() 第一引き数 >>      */
/*------------------------------------------------------*/
#define TONE_462HZ        0       		/* 462 Hz   */
#define TONE_1080HZ       1       		/* 1080 Hz  */
#define TONE_1300HZ       2       		/* 1300 Hz  */
#define TONE_1650HZ       3       		/* 1650 Hz  */
#define TONE_1700HZ       4       		/* 1700 Hz  */
#define TONE_1800HZ       5       		/* 1800 Hz  */
#define TONE_1850HZ       6       		/* 1850 Hz  */
#define TONE_2100HZ       7       		/* 2100 Hz  */
#define TONE_415HZ_SWE		8			/* 415Hz(RBT) for SWE */ /* add by M.HARADA 95.07.07 */
#define TONE_640HZ			9			/* 640Hz(RBT) for FRA *//* add by H.Kubo 1007/07/23 */

/*****************************************************
 * DTMF 送出ﾃｰﾌﾞﾙ No. << MDM_DTMF_Tx() 第一引き数 >> *
******************************************************/
#define DTMF_0		0				/*  " 0 "					*/
#define DTMF_1		1				/*  " 1 "					*/
#define DTMF_2		2				/*  " 2 "					*/
#define DTMF_3		3				/*  " 3 "					*/
#define DTMF_4		4				/*  " 4 "					*/
#define DTMF_5		5 				/*  " 5 "					*/
#define DTMF_6		6				/*  " 6 "					*/
#define DTMF_7		7				/*  " 7 "					*/
#define DTMF_8		8				/*  " 8 "					*/
#define DTMF_9		9				/*  " 9 "					*/
#define DTMF_ASTA	10				/*  " * "					*/
#define DTMF_SHARP	11				/*  " # "					*/
#define DTMF_A		12				/*  " A "					*/
#define DTMF_B		13				/*  " B "					*/
#define DTMF_C		14				/*  " C "					*/
#define DTMF_D		15				/*  " D "					*/
#define ROW_1		16				/*	低群６９７Ｈｚ			*/
#define ROW_2		17				/*	低群７７０Ｈｚ			*/
#define ROW_3		18				/*	低群８５２Ｈｚ			*/
#define ROW_4		19				/*	低群９４１Ｈｚ			*/
#define COL_1		20				/*	高群１２０９Ｈｚ		*/
#define COL_2		21				/*	高群１３３６Ｈｚ		*/
#define COL_3		22				/*	高群１４７７Ｈｚ		*/
#define COL_4		23				/*	高群１６３３Ｈｚ		*/

/*******************************************************************
 * サービスファンクション用ＦＳＫ送出 << MDM_FskTxTask() 第一引き数 >> *
********************************************************************/
#define FSK_WHITE	0				/*	オール０送出	*/
#define FSK_BLACK	1				/*	オール１送出	*/
#define FSK_W1_B1	2				/*	白黒１：１		*//* FSK_W1_B1 1999/12/27 Y.Murata */

/****************************************
* サービスファンクション用画データ送出　*
* MDM_PixTxTaskを生成する時の引数		*
*****************************************/
struct ServiceFuncPixData_t {
	UBYTE baud_rate;
	UBYTE pix_retio;
};

/*********************************************
 * 画データ送出 pix_retio
**********************************************/
#define W1_B0			0
#define W1_B1			1
#define W1_B4			2
#define W0_B1			3
#define W4_B1			4

/* 1996/12/11 Y.Murata */
	/*********************************/
	/* サービス・ファンクション DTMF */
	/*********************************/
	#define	MDM_DTMF_ROW1		0	/*  697Hz */
	#define	MDM_DTMF_ROW2		1	/*  770Hz */
	#define	MDM_DTMF_ROW3		2	/*  852Hz */
	#define	MDM_DTMF_ROW4		3	/*  941Hz */
	#define	MDM_DTMF_COL1		4	/* 1209Hz */
	#define	MDM_DTMF_COL2		5	/* 1336Hz */
	#define	MDM_DTMF_COL3		6	/* 1477Hz */
	#define	MDM_DTMF_COL4		7	/* 1633Hz */

	/***************************************************/
	/* サービス・ファンクション DTMFテーブルオフセット */
	/***************************************************/
	#define	MDM_DTMF_ROW1_OFFSET	1	/*  697Hz */
	#define	MDM_DTMF_ROW2_OFFSET	4	/*  770Hz */
	#define	MDM_DTMF_ROW3_OFFSET	7	/*  852Hz */
	#define	MDM_DTMF_ROW4_OFFSET	10	/*  941Hz */
	#define	MDM_DTMF_COL1_OFFSET	1	/* 1209Hz */
	#define	MDM_DTMF_COL2_OFFSET	2	/* 1336Hz */
	#define	MDM_DTMF_COL3_OFFSET	3	/* 1477Hz */
	#define	MDM_DTMF_COL4_OFFSET	12	/* 1633Hz */

/*----------------------------------------*/
/* ﾌｨﾙﾀ番号  << MDM_FilterSet() 引き数 >> */
/*----------------------------------------*/
#define BEFORE_DIAL_FILTER		0		/* ﾀﾞｲｱﾙ前(for DT,BT,CT検出用)         */
#define AFTER_DIAL_FILTER		1		/* ﾀﾞｲｱﾙ後(for BT,CT,CED,DIS検出用)    */
#define DIALTONE_2ND_FILTER		2		/* 2nd ﾀﾞｲﾔﾙﾄｰﾝ                        */
#define CNG_FILTER				3		/* CNG検出                             */
#define FSK_FILTER				4		/* FSK検出                             */
#define VOICE_FILTER			5		/* 無音検出                            */
#define F_NET_FILTER			6		/* F網着信(1300Hz)検出                 */
#define CNG_BT_FILTER			7		/* CNGとBusyTone検出             (H8)  */
#define TAD_CNG_FILTER			8		/* 留守番電話音声応答中のCNG検出 (H8)  */
#define SPECIAL_DIAL_FILTER		9		/* ﾀﾞｲｱﾙﾄｰﾝ検出(ｽﾍﾟｲﾝのみ)       (H8)  */
#define FSK_PIX_FILTER			10		/* FSK/PIX検出  Add 1995/07/28   (H8)  */

#define	FIRST_DIALTONE_FILTER	11		/* 1stDT検出時のフィルター            */
#define	SECOND_DIALTONE_FILTER	12		/* 2ndDT検出時のフィルター            */
#define	SP_DIALTONE_FILTER		13		/* SpecialDT検出時のフィルター        */
#define	CED_DIS_FILTER			14		/* 接続監視(CED/DIS)検出時のフィルター*/

#define BEFORE_NLD_DIAL_FILTER	15		/* ﾀﾞｲｱﾙ前(for DT,BT,CT検出用) for NLD  */

#define V8_TONE_FILTER			16		/*  By O.Kimoto 1996/02/28 */
#define TX_V8_TONE_FILTER		17		/*  By O.Kimoto 1996/07/16 */
#define RX_V8_TONE_FILTER		18		/*  By O.Kimoto 1996/07/16 */
#define V8_MODE_FSK_TONE_FILTER	19		/*  1996/10/23 Y.Murata */

#define RX_V23_TONE_FILTER		20 		/* For (PRO_CALLER_ID_PROTOCOL == V23). by H.Kubo 1998/08/12 */

/* #if defined(POPLAR_F) */	/* HINOKI2でも使用するので条件変えました 2001/12/17 T.Takagi */
/* #if (PRO_BT_DET_WHILE_RBT == ENABLE) */			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
#if defined(POPLAR_F) || defined (HINOKI2) || defined(POPLAR_H) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)	/* 上記変更が不適切でしたので修正いたします 2002/04/04 T.Takagi */
/* POPLAR_H By Y.Suzuki 2002/06/11 */
#define CNG_BUSY_FILTER		 	21		/* 2000/02/02 Y.Murata */
#endif


/*
** 受信エラーラインセーブデータＭＡＸ値
*/
#define MDM_ERR_LINE_DATA_MAX	10

/***********************************************************************************************/
/* MDM_DEF.HV                                                                                  */
/***********************************************************************************************/

/*------------------------------*/
/*	モデムバッファＲ／Ｗ管理	*/
/*------------------------------*/
typedef struct mdm_btbl_t {
	UBYTE	*TopAddress;		/* バッファ先頭絶対アドレス	*/
	UWORD	 DataCount;			/* ＤＭＡ転送カウント		*/
}MDMBUF;

/*--------------------------------------*/
/*	モデムバッファコントロールブロック	*/
/*--------------------------------------*/
struct mdmcntl_t {
	UWORD	Status;						/* モデムステータス			*/
	UBYTE 	WritePoint;					/* 入力バッファポインタ		*/
	UBYTE	ReadPoint;					/* 出力バッファポインタ		*/
	UBYTE	UsedCount;					/*	モデムバッファ使用本数	*/
	MDMBUF  BufferControl[MODEM_BUFFER_MAX];	/* バッファ管理				*/
};

/*--------------------------*/
/*	モデムＩ／Ｆブロック	*/
/*--------------------------*/
struct	mdmblk_t {
	UBYTE	Type;			/* モデム種別	*/
	UBYTE	Speed;			/* モデムスピード	*/
	UBYTE	Mode;			/* モデム交信モード	*/
	UBYTE	Training;		/* トレーニング種別	*/
	UBYTE	Chain;			/* チェーン有無	*/
	UBYTE	TxAttenuation;	/* 送信アッテネータレベル	*/
	UBYTE	RxCheck;		/* '94.11.16 */
	UBYTE	Config;			/* CONF Register Data **/
};

/*--------------------------*/
/* MDM_CRC.C				*/
/*--------------------------*/
/* Ported from orange\define\mdm_def.c by H. Kubo, 1997/06/17 */
struct b_data_t {
	UBYTE h_data;
	UBYTE l_data;
};

union w_data_t {
	UWORD word_data;
	struct b_data_t byte_data;
};


/*----------------------------------*/
/*	モデムバッファＲ／Ｗ管理マクロ	*/
/*----------------------------------*/
#define	MDMWPNT	ModemControl.BufferControl[ModemControl.WritePoint]
#define MDMRPNT ModemControl.BufferControl[ModemControl.ReadPoint]

/*----------------------*/
/*	モデム交信モード	*/
/*----------------------*/
#define	MODE_TX_FSK			1
#define	MODE_TX_ECM			2
#define MODE_TX_G3			3
#define MODE_TX_TCF			4
#define MODE_RX_FSK			5
#define MODE_RX_ECM			6
#define MODE_RX_G3			7
#define MODE_RX_TCF			8
#define MODE_CL1_RX			9	/* CLASS 1 用に追加 96/05/21 Y.Tanimoto */
#define MODE_CC_RETRAIN		10		/* R288F Internal Monitor By O.Kimoto 1996/05/21 *//** Class1用define追加のため、値を変更( 9 -> 10) */
#define MODE_PC_RETRAIN		11		/* R288F Internal Monitor By O.Kimoto 1996/05/21 *//** Class1用define追加のため、値を変更(10 -> 11) */
#define SPEED_HANDSHAKE_BIT	0x80	/* R288F Internal Monitor By O.Kimoto 1996/05/21 */
#define MODE_TX_ND			12		/* ナンバーディスプレイ対応。added by H.Kubo  1998/06/23 */
#define MODE_RX_ND			13		/* ナンバーディスプレイ対応。added by H.Kubo  1998/06/23 */
#define MODE_CC_OFF			14		/* コントロールチャンネルＴｕｒｎＯｆｆ by O.Kimoto 1998/12/01 */
#define MODE_PC_OFF			15		/* コントロールチャンネルＴｕｒｎＯｆｆ by O.Kimoto 1998/12/01 */

#define MODE_NULL			MODE_PC_OFF	/* これはモデムステータスモニタープリント時の空白に使用しています。追加する場合は最大値を代入してください。 by O.Kimoto 1998/12/01 */

/*------------------*/
/*	モデムタイプ	*/
/*------------------*/
/** Ｖ．３４用に再定義しました｡ By O.K Dec,05,1995 **/
#define TYPE_V8				 0 		/*	Ｖ８モデム			*//** V.34 By O.K Dec.05,1995 **/
#define	TYPE_V27			 1 		/*	Ｖ２７ｔｅｒモデム	*/
#define	TYPE_V29			 2		/*	Ｖ２９モデム		*/
#define	TYPE_V17			 3		/*	Ｖ１７モデム		*/
#define	TYPE_V33			 4		/*	Ｖ３３モデム		*/
#define TYPE_V34			 5		/*	Ｖ３４モデム		*//** V.34 By O.K Dec.05,1995 **/
#define TYPE_FSK			 6		/*	ＦＳＫモード		*/
#define	TYPE_V21			 6		/*	Ｖ２１モード（＝ＦＳＫモード） */
#define	TYPE_G2  			 7		/*	Ｇ２モード			*/
#define	TYPE_TONE			 8		/*	ＴＯＮＥモード		*/
#define	TYPE_DTMF			 9		/*	ＤＴＭＦモード		*/
#define TYPE_MELODY			10		/*	保留音	( 未使用 )	*/
#define	TYPE_V23			11		/* ナンバーディスプレイモード  */ /* added by H.Kubo  1998/06/23 */

/*------------------*/
/*	モデムスピード	*/
/*------------------*/
/** Ｖ．３４用に再定義しました｡ By O.K Dec,05,1995 **/
#define SPEED_2400			 0		/*	２４００ｂｐｓ		*/
#define SPEED_4800			 1 		/*	４８００ｂｐｓ		*/
#define SPEED_7200			 2		/*	７２００ｂｐｓ		*/
#define SPEED_9600			 3		/*	９６００ｂｐｓ		*/
#define SPEED_12000			 4		/*	１２．０Ｋｂｐｓ	*/
#define SPEED_14400			 5		/*	１４．４Ｋｂｐｓ	*/
#define SPEED_16800			 6		/*	１６．８Ｋｂｐｓ	*//** V.34 By O.K Dec.05,1995 **/
#define SPEED_19200			 7		/*	１９．２Ｋｂｐｓ	*//** V.34 By O.K Dec.05,1995 **/
#define SPEED_21600			 8		/*	２１．６Ｋｂｐｓ	*//** V.34 By O.K Dec.05,1995 **/
#define SPEED_24000			 9		/*	２４．０Ｋｂｐｓ	*//** V.34 By O.K Dec.05,1995 **/
#define SPEED_26400			10		/*	２６．４Ｋｂｐｓ	*//** V.34 By O.K Dec.05,1995 **/
#define SPEED_28800			11		/*	２８．８Ｋｂｐｓ	*//** V.34 By O.K Dec.05,1995 **/
#define SPEED_31200			12		/*	３１．２Ｋｂｐｓ	*//** V.34 By O.K Dec.05,1995 **/
#define SPEED_33600			13		/*	３３．６Ｋｂｐｓ	*//** V.34 By O.K Dec.05,1995 **/
#define SPEED_300			14		/*	３００ｂｐｓ		*/
#define SPEED_1200			15		/*	１２００ｂｐｓ		*/ /* ナンバーディスプレイ対応。added by H.Kubo  1998/06/23 */


/*
 * モデムバージョン		#if (PRO_MODEM_R288F_VERSION)
 *
 ** 暫定的に \SRC\NAGANO\HIIRAGI\DEFINE\PRODUCT1.H から移してあります 99/07/06 by J.Kishida
*/
#define		R288F_VERSION_INVALID		0				/* 村田製オレンジ3 */
#define		R288F_VERSION_20P			1				/* ROCKWELL製 28.8K */
#define		R288F_VERSION_22P			2				/* ROCKWELL製 28.8K */
#define		R288F_VERSION_24P			3				/* ROCKWELL製 28.8K */
#define		R288F_VERSION_26P			4				/* ROCKWELL製 28.8K */
#define		FM336_VERSION_12P			5				/* CONEXANT(旧Rockwell)製 33.6K *//* 99/07/06 by J.Kishida */

/* コンパイルを通す為に本当に暫定的にここに入れます */
	#define	PRO_MODEM_R288F_VERSION FM336_VERSION_12P /* FM336 モデムのバージョン by H.Kubo 1998/09/07 */


/*----------------------*/
/*	トレーニング種別	*/
/*----------------------*/
#define	TRAINING_LONG		0		/*	ロングトレーニングモード	*/
#define	TRAINING_SHORT		1		/*	ショートトレーニングモード	*/

/*	モデムフェーズ指定
 *	ModemBlock.Chain
 */
#define	CHAIN_ON			0		/*	高速指定			*/
#define	CHAIN_OFF			1		/*	手順 指定			*/
#define SET_COMPL			2		/*	送信データ設定完了	*/
#define	SPTX_MODE			3		/*	ＴＣＦ送出時トレリス拡張プログラム転送指定	*/

#define	CHECK_OFF	0				/* ﾃﾞﾌｫﾙﾄ時間指定				*/
#define	RX_CHKONLY	1				/* 受信有無ﾁｪｯｸ ( 無時:即時復帰 )*/

/*------------------------------*/
/*	モデムデバイスステータス	*/
/*	ModemControl.Status			*/
/*------------------------------*/
#define STAT_IDLE			0x0000	/*	モデムデバイス　アイドル		*/
#define	STAT_ACT			0x0001	/*	モデムデバイス　アクティブ	*/
#define STAT_ACTOFF			0xfffe
#define STAT_FLGWAIT		0x0002	/*	ＨＤＬＣ同期信号待ち			*/
#define	STAT_RXMOD			0x0000	/*	Ｔｘ／Ｒｘモードフラグ（Ｒｘ）	*/
#define	STAT_TXMOD			0x0004	/*	Ｔｘ／Ｒｘモードフラグ (Ｔｘ)	*/
#define	STAT_FRSTON			0x0008	/*	フラグ送出中		*/
#define	STAT_FRSTOFF		0xfff7	/*	フラグ送出停止	*/
#define	STAT_SYNCMOD		0x0000	/*	同期モード	*/
#define	STAT_HDLCMOD		0x0010	/*	ＨＤＬＣモード	*/
#define	STAT_ANALMOD		0x0020	/*	Ｇ２モード	*/
#define STAT_VOICEACK		0x0040	/*	音声応答モード	*/
#define STAT_ECMMODE		0x0080	/*	ＥＣＭモード（Ｒｘのみ）*/
#define	STAT_REQRES			0x0100	/*	単独コマンド／レスポンス	*/
#define	STAT_LAST			0x0200	/*	ﾗｽﾄPOST用    ( HDLCﾓｰﾄﾞ )  	*/
#define STAT_EMPTYPT		0x0400	/*	送信バッファ空き状態	*/
#define STAT_FSTFG			0x0800	/*	受信終結フラグ検出待ち	   ( Rx )	*/
#define	STAT_UNDRUN			0x1000	/*	送信アンダーランステータス待ち  ( Tx )	*/
#define STAT_ALSENT			0x2000	/*	送信オールセントステータス待ち  ( Tx )	*/
#define STAT_FLGDET			0x4000	/*	受信初期フラグ検出待ち  ( Rx )	*/
#define STAT_FCSDET			0x8000	/*	受信フレームチェックシーケンス検出待ち( Rx )	*/

/*----------------------*/
/*	ＤＭＡ起動サイズ	*/
/*----------------------*/
#define MODEM_DMA_SIZE	256						/* 同期式ＤＭＡサイズ		*/
#define RX_FSK_HDLC_LENGTH	(MODEM_DMA_SIZE + MODEM_FRAMING_CODE_LENGTH+1)	/* 受信サイズ（ＦＣＳとフラグ含む）By O.K Jan.23,1996 **/

/*------------------------------*/
/*	ＨＤＬＣ最終フレームビット	*/
/*------------------------------*/
#define LAST_FRAME	0x10			/* 最終フレームビット		*/

/*------------------------------*/
/*	受信フレーム監視時間設定	*/
/*------------------------------*/
#define	TOUT_FRAME	6000			/*	１フレーム監視時間（ｍｓ）	*/
#define FRAME_WAIT	10				/*	１ウェイト時間				*/

/*--------------------------------------*/
/*	モデムステータスチェックフェーズ	*/
/*--------------------------------------*/
#define PHS_STAT_CHECK_SEQ_BIT		0x8000			/* シーケンス信号チェック	*/
#define	PHS_STAT_EQZHON_WAIT		0x4000			/* イコライザホールド指示	*/
#define	PHS_STAT_FCSRESET_PHASE		0x2000			/* ＦＣＳリセット			*/
#define	PHS_STAT_CHECK_TRDETON		0x0001			/* ＴＲＤＥＴチェックＯＮ	*/
#define	PHS_STAT_OFF_TRDETON		0x7ffe			/* ＴＲＤＥＴチェックＯＦＦ	*/
#define	PHS_STAT_CHECK_RLSDON 		0x0002			/* ＲＬＳＤ　ＯＮチェック			*/
#define	PHS_STAT_OFF_RLSDON 		0x7ffd			/* ＲＬＳＤ　ＯＮチェックＯＦＦ		*/
#define	PHS_STAT_CHECK_RLSDOFF		0x0003			/* ＲＬＳＤ　ＯＦＦチェック			*/
#define	PHS_STAT_OFF_RLSDOFF		0x7ffc			/* ＲＬＳＤ　ＯＦＦチェックＯＦＦ	*/
#define	PHS_STAT_CHECK_CCR			0x0002
#define	PHS_STAT_CHECK_CCR_OFF		0xfffd
#define PHS_STAT_CHECK_TN_BIT		0x4000			/* 周波数チェック	*/

/*----------------------*/
/*	モデムＲ／Ｗモード	*/
/*----------------------*/
#define WRITE_MODE		1
#define READ_MODE		2

/*--------------------------*/
/*	ＨＤＬＣフォーマット	*/
/*--------------------------*/
#define HDLC_A		0xff	/* アドレス */
#define HDLC_C		0x03	/* コントロール */
#define HDLC_FCD	0x06	/* ファクシミリ符号データ */
#define HDLC_RCP	0x86	/* 部分ページ制御復帰 */

/*------------------*/
/*	ＨＤＬＣ位置	*/
/*------------------*/
#define ADR_FLD		0	/* アドレスフィールド */
#define CTRL_FLD	1	/* 制御フィールド */
#define FCF_FLD		2	/* ファクシミリ符号データフィールド */
#define FIF_FLD		3	/* ファクシミリ情報フィールド */
#define FDF_FLD		4	/* ファクシミリ符号化データフィールド */

/*----------*/
/* 送信種別 */
/*----------*/
#define TX_INVALID_TYPE  0 /* Added by H.Kubo 1997/07/16. Invalid value for CommunicateType */
#define TX_G3_SCAN	1
#define TX_G3_MEM	2
#define TX_G3_CVR	3
#define TX_G3_RCR	4
#define TX_ECM_SCAN	5
#define TX_ECM_MEM	6
#define TX_ECM_CVR 	7
#define TX_ECM_RCR	8
#define TX_ECM_BKUPRAM 9	/* ●ICHOU追加 by T.Soneoka 1996/06/17 */ /* Added by H.Kubo 1997/07/16 */
#define TX_ECM_RELAYED_TX_REPORT 10 /* added by H.Kubo 1998/01/19 */
#define TX_G3_RELAYED_TX_REPORT  11 /* added by H.Kubo 1998/01/19 */
/*----------*/
/* 受信種別 */
/*----------*/
#define RX_G3_PRT	1
#define RX_G3_MEM	2
#define RX_ECM_PRT	3
#define RX_ECM_MEM	4
#define RX_ECM_BKUPRAM	5	/* ●ICHOU変更 by T.Soneoka 1996/06/18 */ /* Added by H.Kubo 1997/07/15  */

/*------------------------------*/
/* 回線ダウンを検出する時間(秒) */
/*------------------------------*/
#define NO_CARRY_MAXTIME	5

/*--------------------------------*/
/* Ｇ３送信前ダミーデータ送出時間 */
/*--------------------------------*/
#define PIX_DUMMY_TIME	800
#define DUMMY_BLOCK_TIME	50

/*--------------*/
/* ＲＣＰサイズ */
/*--------------*/
#define	RCP_SIZE			3

/*----------------------*/
/* ＥＣＭバッファサイズ	*/
/*----------------------*/
#define ECM_BUFFER_LENGTH	256

/*----------------------*/
/*	ＥＣＭバッファ本数	*/
/*----------------------*/
#define ECM_BUFFER_MAX		256
 #if defined(SATSUKI2)  || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3) || defined(KEISATSU)/* SCD_CNTL.cで使用しているので復活させる　SMuratec H.C.H 2003.07.11 */
#define ECM_BUFFER_DATA_MAX		(ECM_BUFFER_MAX * ECM_BUFFER_LENGTH)
 #else
/* #define ECM_BUFFER_DATA_MAX		(ECM_BUFFER_MAX * ECM_BUFFER_LENGTH) */
 #endif

/*----------------------------------*/
/* 符号変換Ｖ５３　ＤＭＡ転送サイズ */
/*----------------------------------*/
#define	CODEC_DMA_SIZE		256

/*-------------------------------------*/
/* 最大１ライン符号化データ数（バイト）*/
/*-------------------------------------*/	/* 1997/03/14 Y.Murata */
#define MAX_1LINE_ENCODE_DATA	4096

/*------------------*/
/* ＭＳＥ処理ライン */
/*------------------*/
#define MSE_LINE			32

/*--------------*/
/*	Ｔ２タイマ	*/
/*--------------*/
#define T2_TIME			6000

/*------------------------------*/
/* フレーム検出制御				*/
/*	MDM_RxFskFrameControlTask()	*/
/*------------------------------*/
#define	PHASE_FLAG_DETECT			0
#define PHASE_FRAME_DETECT			1
#define PHASE_MULTI_FRAME_DETECT	2

/*------------------------------*/
/*	フレーム検出結果			*/
/*	MDM_RxFskFrameControlTask()	*/
/*------------------------------*/
#define	FRAME_DETECT			0
#define	FLAG_TIME_OVER			1
#define	CRP_RECEIVE				2
#define	ECHO_RECEIVE			3
#define	TIME_OVER_30SEC			4
#define	RECEIVE_OVER			5
#define HIGH_SPEED_RECEIVE		6
#define DMA_STOP				7
#define CC_RETRAIN_DETECT		8	/* CC Retrain By O.Kimoto 1996/05/16 */

/*--------------------------------------*/
/*	Ｇ３／ＥＣＭ受信モデムリード		*/
/*	RxG3_Read()/RxEcmRead()/RxTcfRead()	*/
/*--------------------------------------*/
#define	RCV_BLOCK				0
#define RCV_STOP				1
#define RCV_TMOUT				2
#define RCV_OPEN_ERR			3
#define RCV_TURNOFF				4	/** V.34 By O.K Feb.06,1996 **/
/*------------------------------*/
/* フレーム監視全体タイマ		*/
/*	MDM_RxFskFrameControlTask()	*/
/*------------------------------*/
#define	FRAME_CONTROL_TIMER		30000
/*----------------------*/
/* フレーム監視ウェイト	*/
/*	MDM_FcsDetectTask()	*/
/*----------------------*/
#define RX_FRAME_WAIT			50
/*------------------------------*/
/*	Ｔ３タイマ					*/
/*	MDM_TxVoiceReqAndRcvCmd()	*/
/*------------------------------*/
#define T3_TIME					10000
/*------------------------------*/
/*	Ｔ３タイマ					*/
/*	MDM_TxVoiceReqAndRcvCmd()	*/
/*------------------------------*/
#define T1_TIME					35000
/*--------------------------------------------------------------------------*/
/*	モデムＶ５３ＤＭＡチャンネル＝外付けＤＭＡ１のチャンネル１　ＤＲＱ＝４	*/
/*--------------------------------------------------------------------------*/
/*	#define MODEM_DMAU_CHANNEL	1	"v53\define\cdc_def.h"にモデム用Ｖ５３ＤＭＡを#defineしました	竹内 Jul.08.1994	*/

/*--------------------------*/
/*	トレーニング送出時間	*/
/*	MDM_TransmitTCF()		*/
/*--------------------------*/
#define	TRAINING_TIME	1500
/*--------------------------*/
/*	ＥＹＥ＿Ｑチェック時間	*/
/*	MDM_ReceiveTCF()		*/
/*--------------------------*/
#define	EYE_Q_TIME		1000
/*--------------------------*/
/*	ＴＣＦチェック時間		*/
/*	MDM_ReceiveTCF()		*/
/*--------------------------*/
#define	TCF_TIME		1500
/*--------------------------*/
/*	ＴＣＦ　ＥＮＤ時間		*/
/*	MDM_ReceiveTCF()		*/
/*--------------------------*/
#define	TCF_END_TIME	2000
/*--------------------------*/
/*	ＴＣＦ　ＲＥＡＤ時間		*/
/*	MDM_ReceiveTCF()		*/
/*--------------------------*/
#define	TCF_READ_TIME	10
/*--------------*/
/* ＥＯＬ検出用	*/
/*--------------*/
#define EOL_FRAME1			0x00
#define EOL_FRAME2_MASK		0x0f
#define EOL_FRAME2			0x08
/*----------------------------------*/
/**	ＲＣＰフレーム数				*/
/*	EcmTx()/MDM_TxEcmPatialPage()	*/
/*----------------------------------*/
#define RCP_COUNT			3
/*----------------------------------*/
/*	ＦＳＫ送出　フレーム間フラグ数	*/
/*	MDM_TxFskFrameControlTask()		*/
/*----------------------------------*/
#define	FLAG_DATA			1

/*--------------------------*/
/*	コーデックステータス	*/
/*--------------------------*/
#define		CDC_READY			0
#define		CDC_CONTINUE		1
#define		CDC_RTC_DET			2
#define		CDC_DECODE_ERROR	3
#define		CDC_STOPPED			4
#define		CDC_PAGE_SEPARATE	5
#define		CDC_BLOCK_END		6
#define		CDC_PRINTER_ERROR	7
#define		CDC_CONTI_ERROR		8
#define		CDC_CARRIER_DOWN	9
#define		CDC_MEM_OVER		10
#define		CDC_DOC_OVER		11
#define		CDC_LAMP_ERROR		12
#define		CDC_DOC_ERROR		13
#define		CDC_CMD_END			14

/* Bellow 8 lines were ported from ORANGE by H.Kubo 1997/07/18 */
/* For RISC T.Nose 1996.03.26 */ 
 /* ここのアドレスを変更する時は、ＤＭＡの現在のアドレスを取ってくる関数に注意
    DMA_CheckDMA_CurrentAddress() 1997/04/11  By T.Yamaguchi */
/* #define		ECM_BUFFER_AREA_START_ADDRESS	0x1000000 */ /* Changed by H.Kubo 1997/10/18 */

#define		ECM_BUFFER_AREA_START_ADDRESS	MEM_ECM_BUFFER_START_ADDRESS

/******************************/
/* モデムのDTMFシンボルコード */
/******************************/
#define	MDM_DTMF_0_CODE		0x00	/* DTMFの0      */
#define	MDM_DTMF_1_CODE		0x01	/* DTMFの1      */
#define	MDM_DTMF_2_CODE		0x02	/* DTMFの2      */
#define	MDM_DTMF_3_CODE		0x03	/* DTMFの3      */
#define	MDM_DTMF_4_CODE		0x04	/* DTMFの4      */
#define	MDM_DTMF_5_CODE		0x05	/* DTMFの5      */
#define	MDM_DTMF_6_CODE		0x06	/* DTMFの6      */
#define	MDM_DTMF_7_CODE		0x07	/* DTMFの7      */
#define	MDM_DTMF_8_CODE		0x08	/* DTMFの8      */
#define	MDM_DTMF_9_CODE		0x09	/* DTMFの9      */
#define	MDM_DTMF_AS_CODE	0x0A	/* DTMFのAST    */
#define	MDM_DTMF_SP_CODE	0x0B	/* DTMFのSHARP  */
#define	MDM_DTMF_A_CODE		0x0C	/* DTMFのA      */
#define	MDM_DTMF_B_CODE		0x0D	/* DTMFのB      */
#define	MDM_DTMF_C_CODE		0x0E	/* DTMFのC      */
#define	MDM_DTMF_D_CODE		0x0F	/* DTMFのD      */

/************/
/* DTMF種類 */
/************/
#define	MDM_DTMF_0	0x30	/* DTMFの0      */
#define	MDM_DTMF_1	0x31	/* DTMFの1      */
#define	MDM_DTMF_2	0x32	/* DTMFの2      */
#define	MDM_DTMF_3	0x33	/* DTMFの3      */
#define	MDM_DTMF_4	0x34	/* DTMFの4      */
#define	MDM_DTMF_5	0x35	/* DTMFの5      */
#define	MDM_DTMF_6	0x36	/* DTMFの6      */
#define	MDM_DTMF_7	0x37	/* DTMFの7      */
#define	MDM_DTMF_8	0x38	/* DTMFの8      */
#define	MDM_DTMF_9	0x39	/* DTMFの9      */
#define	MDM_DTMF_AS	0x2a	/* DTMFのAST    */
#define	MDM_DTMF_SP	0x23	/* DTMFのSHARP  */
#define	MDM_DTMF_A	0x41	/* DTMFのA      */
#define	MDM_DTMF_B	0x42	/* DTMFのB      */
#define	MDM_DTMF_C	0x43	/* DTMFのC      */
#define	MDM_DTMF_D	0x44	/* DTMFのD      */

/* ﾄｰﾝｾﾚｸﾄ設定 */
#define MDMCMD1_HZ462       	0x00    	/* 000:  462 Hz             */
#define MDMCMD1_HZ1080          0x02    	/* 001: 1080 Hz             */
#define MDMCMD1_HZ1300          0x04    	/* 010: 1300 Hz             */
#define MDMCMD1_HZ1650          0x06    	/* 011: 1650 Hz             */
#define MDMCMD1_HZ1700          0x08    	/* 100: 1700 Hz             */
#define MDMCMD1_HZ1800          0x0a    	/* 101: 1800 Hz             */
#define MDMCMD1_HZ1850          0x0c    	/* 110: 1850 Hz             */
#define MDMCMD1_HZ2100          0x0e    	/* 111: 2100 Hz             */

/*---------------------------------------------*/
/* ﾒｯｾｰｼﾞ関連定義　とりあえず（移動するつもり）*/
/*---------------------------------------------*/
#define MSG_TX_COMPLETE					0
#define MSG_FLAG_DETECT					1
#define MSG_T2_TIME_OVER				2
#define MSG_3SEC_TIME_OVER				3
#define MSG_30SEC_TIME_OVER				4
#define MSG_DMA_STOP					6
#define	MSG_FRAME_DETECT				7
/* NCU タスク(H8/V53 共通)の戻り値とかぶってるので使わない
	1994/9/1 Y.Suzuki
#define MSG_FSK_RECEIVE					8
#define MSG_FSK_ERROR					9
--------------------------------------------*/


#define MSG_FSK_RECEIVE					10
#define MSG_FSK_ERROR					11
#define MSG_OFF_HOOK					12
#define MSG_T3_TIME_OVER				13
#define MSG_T1_TIME_OVER				14
/*------------------------------*/
/*	MDM_TxFskFrameControlTask	*/
/*------------------------------*/
#define MSG_FSK_TIME_OVER				14
#define MSG_TXFRAME_END					15
/*--------------*/
/*	MODE_TX_FSK	*/
/*--------------*/
#define	MSG_TX_FSK_START				16
/*------------------------------*/
/* MDM_TxEcmFrameControlTask	*/
/*------------------------------*/
#define MSG_ECM_TIME_OVER				17
/*--------------------------*/
/* MDM_TxPix()/MDM_RxPix()	*/
/*--------------------------*/
#define MSG_CODE_CONVERT_START			20
#define MSG_CODE_CONVERT_STOP			21
#define MSG_FROM_CODE_CONVERT_TASK		22
#define MSG_FROM_DEVICE_CONTROL_TASK	23
#define MSG_FROM_DECODEDMA_TC_TASK		24
#define MSG_ENCODE_DMA_START			25
#define MSG_CODEC_ENCODE_START			26
#define MSG_MEMORY_OVER					27
#define MSG_TTI_COMPLETE				28
#define MSG_MEMORY_OK					29
/*------------------*/
/* MDM_ReceiveTCF()	*/
/*------------------*/
#define MSG_EYE_Q_TIME					30
#define MSG_TCF_TIME					31
#define MSG_TCF_END_TIME				32
#define MSG_TCF_READ_TIME				33
#define MSG_RLSD_OFF					34
#define MSG_TRAINING_DETECT_END_TIME 	35
#define MSG_ENABLE_MODEM_STATUS			36
/*--------------*/
/*	MDM_RxPix()	*/
/*--------------*/
#define MSG_RX_DECODE_START				40
#define MSG_1BLOCK_DATA_RECEIVED		41	/* 竹内 Jul.14.1994 */
#define MSG_FORCED_DECODE_START			42	/* 追加 by T.Soneoka 1998/03/02 */
#define MSG_CIL_COMPLETE				43	/* DATE_SET_RXDOC 1998/05/11  B/*----------------------------------*/
/*	MDM_RxDeviceWriteControlTask()	*/
/*----------------------------------*/
#define MSG_OK							50
#define	MSG_NG							51
/* TxPix()	*/
#define MSG_DUMMY_PIX_TIME_OVER			60

/*--------------------------*/
/*	短縮ハンドシェーク用	*/
/*--------------------------*/
#define MSG_RX_SPEED_TIME_OVER			70
#define EQZ_TIME_OVER					71
#define TIME_2SEC_OVER					72

/* For RICHO */
#define MSG_MUTE_ON_TIME_OVER			75


/*---------------------------------------*/
/* 縮小率設定用入力画素数（ワード）      */
/* EncInpStatusの値 97/10/28 T.Yamaguchi */
/*---------------------------------------*/
#if (PRO_CCD == DPI400)
 #define	INPUT_A4_SIZE 216
 #define	INPUT_B4_SIZE 256
 #define	INPUT_A3_SIZE 304
#endif
#if (PRO_CCD == DPI300)
 #define	INPUT_A4_SIZE 2592 / 16	/* 162 Word */
 #define	INPUT_B4_SIZE 3072 / 16	/* 192 Word */
 #define	INPUT_A3_SIZE 3648 / 16	/* 228 Word */
#endif
#if (PRO_CCD == DPI200)
 #define	INPUT_A4_SIZE 108
 #define	INPUT_B4_SIZE 128
 #define	INPUT_A3_SIZE 152
#endif

/*------------------------------------------------------*/
/*	Ｖ．３４　コントロール　チャンネル　リトレイン用	*/
/*------------------------------------------------------*/
#define MSG_CC_RETRAIN_DETECT			80

/*------------------------------*/
/*	サービスファンクション用	*/
/*------------------------------*/
#define MSG_MODEM_STOP					99

/***********************************************************************************************/
/* MDM_DEF.HV                                                                                  */
/***********************************************************************************************/
struct	EcmControl_t {
	UWORD	WriteNo;			/*  0: ＥＣＭメモリのライト位置 */
	UWORD	ReadNo;				/*  2: ＥＣＭメモリのリード位置 */
	UWORD	UseBlock;			/*  4: 使用ブロック数 */
	UBYTE	*WritePtr;			/*  6: ライトアドレス */
	UBYTE	*ReadPtr;			/* 10: リードアドレス */
	UBYTE	*Offset;			/* 12: ライト用オフセットアドレス */
	UWORD	DataSize;			/* 18: 転送バイト数 */
};

	/* 100ms 送出Byte数 */
	#define	MDM_TCF_MIN_14400BPS	180
	#define	MDM_TCF_MIN_12000BPS	150
	#define	MDM_TCF_MIN_9600BPS		120
	#define	MDM_TCF_MIN_7200BPS		 90
	#define	MDM_TCF_MIN_4800BPS		 60
	#define	MDM_TCF_MIN_2400BPS		 30

	/* 1400ms 送出Byte数 */
	#define	MDM_TCF_MAX_14400BPS	2520
	#define	MDM_TCF_MAX_12000BPS	2100
	#define	MDM_TCF_MAX_9600BPS		1680
	#define	MDM_TCF_MAX_7200BPS		1260
	#define	MDM_TCF_MAX_4800BPS		 840
	#define	MDM_TCF_MAX_2400BPS		 420

	/***************************/
	/* EYEスライス・テーブル値 */
	/***************************/
	/*#define	MDM_EYE_SPEED_TYPE		6 */ /* 1996/10/25 Y.M */
	#define	MDM_EYE_SPEED_TYPE		8
	#define	MDM_EYE_SLICE			5

	/**************/
	/* 送出レベル */
	/**************/
	#define	MDM_TX_LEVEL_0		0	/* 送出レベル値:  0dBm */
	#define	MDM_TX_LEVEL_2		2	/* 送出レベル値: -2dBm */
	#define	MDM_TX_LEVEL_4		4	/* 送出レベル値: -4dBm */
	#define	MDM_TX_LEVEL_6		6	/* 送出レベル値: -6dBm */
	#define	MDM_TX_LEVEL_8		8	/* 送出レベル値: -8dBm */
	#define	MDM_TX_LEVEL_10		10	/* 送出レベル値:-10dBm */
	#define	MDM_TX_LEVEL_12		12	/* 送出レベル値:-12dBm */
	#define	MDM_TX_LEVEL_14		14	/* 送出レベル値:-14dBm */

/*******************************/
/* トーン検出タスク パラメータ */
/*******************************/
struct FilterData_t {
	UWORD SendMBX;
	WORD          ReturnValue;
};

	/******************/
	/* フィルター番号 */
	/******************/
	#define	MDM_FILTER1		0x01
	#define	MDM_FILTER2		0x02
	#define	MDM_FILTER3		0x04

/* フィルターテーブル構造体定義 */
/* 24 byte */
struct	FilterTable_t {
	UWORD	b1_a3;
	UWORD	b1_a2;
	UWORD	b1_a1;
	UWORD	b1_b2;
	UWORD	b1_b1;

	UWORD	b2_a3;
	UWORD	b2_a2;
	UWORD	b2_a1;
	UWORD	b2_b2;
	UWORD	b2_b1;
};

/* フィルターレベル検出テーブル構造体定義 */
/* 8 byte */
struct	FilterLevelTable_t {
	UWORD	lpfbk;
	UWORD	lpgain;
	UWORD	threshu;
	UWORD	threshl;
};

	/*-----------------------*/
	/* 送出レベル(All Modes) */
	/*-----------------------*/
	#define MDM_TX_OUTPUT_LEVEL_ALL_MAX	50
	#define MDM_TX_OUTPUT_LEVEL_FSK_MAX	22

	#define MDM_TX_OUTPUT_LEVEL_ADJUST_MAX	21
	#define MDM_ADJUST_MIN			0x1A
	#define MDM_ADJUST_MAX			0x0A
	#define MDM_ADJUST_SIGN_FLAG	0x10

	/********************/
	/* 単一トーン周波数 */
	/********************/
	/* 462,1080,1300,1650,1700,1800,1850,2100 */ /*plus  415, 640 by H.Kubo 1997/07/23 */
	/* #define	MDM_SINGLE_MAX	8 */
	#define	MDM_SINGLE_MAX	10

/**************/
/* DTMF周波数 */
/**************/
/* 0～9, *, #, A, B, C, D */
#define	MDM_DTMF_FREQ_MAX	16

struct	DTMF_FrequencyTable_t {
	UWORD HighFreq;			/* DTMF高周波数 */
	UWORD LowFreq;			/* DTMF低周波数 */
};

/**************/
/* DTMFレベル */
/**************/
/* 0dBm ～ -15.0dBm */
#define	MDM_DTMF_LVL_MAX	16

struct	DTMF_LevelTable_t {
	UWORD HighLevel;		/* DTMFの高群レベル */
	UWORD LowLevel;			/* DTMFの低群レベル */
};

	/*--------------------------------------*/
	/* ＡＲＡ  Ｔｈｒｅｓｈｏｌｄ  テーブル */
	/*--------------------------------------*/
	#define DATA_RATE_MAX	14

/************************/
/* 国別フィルタテーブル */
/************************/

#define CTR_COUNTRY_MAX 8

/****************/
/*	ﾌｨﾙﾀｰ･ﾃｰﾌﾞﾙ	*/
/*	(80Byte)	*/
/****************/

struct	CountryFilterTbl_t {
	struct	FilterTable_t filter[3];			/* ﾌｨﾙﾀｰ係数               */
	UBYTE DialTone1st_Level;			/* 1stﾀﾞｲｱﾙﾄｰﾝ検出のﾚﾍﾞﾙ   */
	UBYTE DialTone2nd_Level;			/* 2ndﾀﾞｲｱﾙﾄｰﾝ検出のﾚﾍﾞﾙ   */
	UBYTE DialToneSpecial_Level;		/* SPﾀﾞｲｱﾙﾄｰﾝ検出のﾚﾍﾞﾙ    */
	UBYTE Connect_Level;				/* 接続検出のﾚﾍﾞﾙ          */
};

/* モデムＤＭＡステータス */
#define MDM_DMA_READY		0x00
#define MDM_DMA_GO			0x01
#define MDM_DMA_CONTINUE	0x02
#define MDM_DMA_MASK		0xFF

/*
** モデム内部遷移ステータス監視テーブル
** 1レコード：９バイトです。
*/
struct	ModemInternalStatusTable_t {
	UBYTE	Tx_Phase;
	UBYTE	Rx_Phase;
	/* 以下のビットフィールドは、 V53 に合わせる必要がある。*/
/* Changed by H.Kubo 1998/01/26. sys_opt.h の定義を参照。*/
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
#define PNDET_OFF_STATUS			0x03
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


/* モデム内部ステータス用イベント割付ビット
** 実際のイベントは１０ｍｓ割り込みから発生します。
** BY O.Kimoto 1996/05/17
**/
#define MDM_EVT_CC_RETRAIN_DETECT_BIT	0x0001
#define MDM_EVT_ABORT_CODE_DETECT_BIT	0x0002
#define MDM_EVT_MDM_TURNOFF_BIT			0x0004	/* Add By O.Kimoto 1996/10/16 */
#define MDM_EVT_SHIFT_100PPM_1			0x0008	/* Add By O.Kimoto 1998/02/03 */
#define MDM_EVT_SHIFT_100PPM_2			0x0010	/* Add By O.Kimoto 1998/02/03 */
#define MDM_EVT_SHIFT_100PPM_3			0x0020	/* Add By O.Kimoto 1998/02/03 */
#define MDM_EVT_RTH_CHANGE				0x0040	/* Add By O.Kimoto 1998/02/03 */

/* モデム割り込み用イベント割付ビット
** By O.Kimoto 1996/10/12
*/
#define MDM_EVT_ATV25_DETECT_BIT		0x0001
#define MDM_EVT_MDM_PNSUC_BIT			0x0002
#define MDM_EVT_TX_FCS_COMPLETE_BIT		0x0004
#define MDM_EVT_RX_FLG_DETECT_BIT		0x0008
#define MDM_EVT_RX_RDBF_BIT				0x0010 /* For V23 Rx added by H.Kubo 1998/08/04 */
#define MDM_EVT_PCOFF_DETECT_BIT		0x0020 /* For 26P V34 added by H.Kubo 1998/10/30 */
/************************************************************
 * モデムバージョン											*
 * L6713-13P(L8152-A) 52									*
 * L6713-14P(L8153-?) 53									*
 * 1996/10/04												*
 * 木元  修													*
 ************************************************************/
#define MDM_L6713_13P	0x52
#define MDM_L6713_14P	0x53
#define MDM_L6713_20P	0x54
#define MDM_L6713_22P	0x55	/* added by H.Kubo 1998/10/05 */
#define MDM_L6713_24P	0x56	/* added by H.Kubo 1998/07/06 */
#define MDM_L6713_26P	0x57	/* added by H.Kubo 1998/10/01 */
/* #define MDM_L6719_12P	0x81 */	/* For FM336, added by H.Kubo 1999/04/08 */
#define MDM_L6719_12P_ES	0x81	/**/
#define MDM_L6719_12P_CS	0x82	/**/

/* the followings are the counter that NEWC bit leave the ON status.
** When this counter count up, $4802-2 on  set.
** Then the NEWC bit will be become the off condition.
**
** 15ms 1284
** 20ms 1712
** 40ms 3425
** 50ms 4281
**
** by O.Kimoto 1997/02/07
*/
#if (0) /* For SH2 1999/09/21 by K.Okada */
//#define V33_14400_NEWC_TIME		1712	/* 15ms(1284) -> 20ms(1712) 1997/04/25 Y.Murata */
//#define V33_12000_NEWC_TIME		1712	/* 15ms(1284) -> 20ms(1712) 1997/04/25 Y.Murata */
//#define V33_9600_NEWC_TIME		1712	/* 15ms(1284) -> 20ms(1712) 1997/04/25 Y.Murata */
//#define V33_7200_NEWC_TIME		1712	/* 15ms(1284) -> 20ms(1712) 1997/04/25 Y.Murata */

//#define V17_14400_NEWC_TIME		2140	/* 20ms(1712) -> 25ms(2140) 1997/04/25 Y.Murata */
//#define V17_12000_NEWC_TIME		2140	/* 20ms(1712) -> 25ms(2140) 1997/04/25 Y.Murata */
//#define V17_9600_NEWC_TIME		2140	/* 20ms(1712) -> 25ms(2140) 1997/04/25 Y.Murata */
//#define V17_7200_NEWC_TIME		2140	/* 20ms(1712) -> 25ms(2140) 1997/04/25 Y.Murata */

//#define V29_9600_NEWC_TIME		1712	/* 20ms */
//#define V29_7200_NEWC_TIME		1712	/* 20ms */
//#define V29_4800_NEWC_TIME		1712	/* 20ms */

//#define V27_4800_NEWC_TIME		4281	/* 50ms */
//#define V27_2400_NEWC_TIME		4281	/* 50ms */

//#define V21_300_NEWC_TIME		3425	/* 40ms */

#else /* For SH2 1999/09/21 by K.Okada */

#define V33_14400_NEWC_TIME		0x5000	/* 20ms */
#define V33_12000_NEWC_TIME		0x5000	/* 20ms */
#define V33_9600_NEWC_TIME		0x5000	/* 20ms */
#define V33_7200_NEWC_TIME		0x5000	/* 20ms */

#define V17_14400_NEWC_TIME		0x6400	/* 25ms */
#define V17_12000_NEWC_TIME		0x6400	/* 25ms */
#define V17_9600_NEWC_TIME		0x6400	/* 25ms */
#define V17_7200_NEWC_TIME		0x6400	/* 25ms */

#define V29_9600_NEWC_TIME		0x5000	/* 20ms */
#define V29_7200_NEWC_TIME		0x5000	/* 20ms */
#define V29_4800_NEWC_TIME		0x5000	/* 20ms */

#define V27_4800_NEWC_TIME		0xC800	/* 50ms */
#define V27_2400_NEWC_TIME		0xC800	/* 50ms */

#define V21_300_NEWC_TIME		0xA000	/* 40ms */

#endif /* For SH2 1999/09/21 by K.Okada */

/* Ported from ORANGE\SRC\MDM_DEF.H by H.Kubo 1997/07/17 */
/* 高速 RDS 用 */
struct	HighRdsTable_t {
	UBYTE *BackupDataAddress;
	UWORD BackupDataLength;
};

#if defined(POPLAR_F)
#define HIGH_RDS_DATA_MAX	30
#elif defined (HINOKI2) || defined (SATSUKI2)  || defined(STOCKHM2)
#define HIGH_RDS_DATA_MAX	32
#elif (defined(POPLAR_H) && defined(JP0)) || (defined(POPLAR_H) && defined(JP1))	/* 55転送 By O.Kimoto 2003/02/05 */
	#if (PRO_COST == ENABLE) /* #if is added by H.Kubo 1997/11/13 */
	#if (PRO_EXT_ROM == ENABLE)		/* By H.Kubo 1998/03/12 */
	#define HIGH_RDS_DATA_MAX	(26 + 2 + 3 + 2 + 1 + 1) /* Changed by H.Kubo 1998/01/28 */
	#else
	#define HIGH_RDS_DATA_MAX	(26 + 2 + 3 + 2 + 1) /* Changed by H.Kubo 1998/01/28 */
	#endif
	#else /* (PRO_COST == ENABLE) */
	#define HIGH_RDS_DATA_MAX	(26 + 3 + 2 + 1)
	#endif /* (PRO_COST == ENABLE) */
#elif (defined(SAKAKI) && defined(JP0)) /* 2002/09/12 By M.Maeda */
	#if (PRO_COST == ENABLE) /* #if is added by H.Kubo 1997/11/13 */
	#if (PRO_EXT_ROM == ENABLE)		/* By H.Kubo 1998/03/12 */
	#define HIGH_RDS_DATA_MAX	(26 + 2 + 3 + 2 + 1 + 1) /* Changed by H.Kubo 1998/01/28 */
	#else
	#define HIGH_RDS_DATA_MAX	(26 + 2 + 3 + 2 + 1) /* Changed by H.Kubo 1998/01/28 */
	#endif
	#else /* (PRO_COST == ENABLE) */
	#define HIGH_RDS_DATA_MAX	(26 + 3 + 2 + 1)
	#endif /* (PRO_COST == ENABLE) */
#endif


#define WRITE_DISABLE_DATA_MAX	4

/*DMA channel for R288F. Added by H. Kubo 1997/06/23 */
#define DMA_CH_TX 	DMA_MDMBUF_MDM_CH /* Changed by H.Kubo 1998/07/15 */
#define DMA_CH_RX 	DMA_MDM_MDMBUF_CH
#define DMA_CH_DEC	DMA_DRAM_COMCDC_CH
#define DMA_CH_ENC	DMA_COMCDC_DRAM_CH

/*
** DMA channel for modem-to-memory and memory-to-modem are the same. 
** So, events for them are actually identical.
*/
#define	EVT_DMA_MDMBUF_MDM 	EVT_DMA_MDM_MDMBUF

/* See \src\nagano\def_v\dma_data.c. */
#define		IsSCNCDC_ToMemoryXferDone		DMA0_TC0Flag 	/* A flag of Scanner CODEC to memory transfer. */
#define 	IsCOMCDC_ToMemoryXferDone		DMA0_TC2Flag	/* A flag of Communication CODEC to memory transfer */
#define		IsMemoryToCOMCDC_XferDone		DMA0_TC3Flag	/* A flag of memoey to Communication CODEC transfer */

/*flag ON OFF for R288F. Added by H. Kubo 1997/06/23 */
#define	ON				1
#define	OFF				0

/* Ｒ２８８ＦのＤＭＡのリクエスト端子の切替え用
**       ＴＸ：０
**       ＲＸ：１
** By O.Kimoto 1997/10/08
*/
#define TX_DMA		0x00
#define RX_DMA		0x01


/* 22P 以降のモデム割り込み処理用構造体 added by H.Kubo 1998/11/10 */
struct MDM_ModemStatusRegister_t {
	UBYTE MDM_REG_0A;
	UBYTE MDM_REG_0B;
	UBYTE MDM_REG_0C;
	UBYTE MDM_REG_0D;
	UBYTE MDM_REG_0E;
	UBYTE MDM_REG_0F;
	UBYTE MDM_REG_12;
	UBYTE MDM_REG_14;
	UBYTE MDM_REG_16;
	UBYTE MDM_REG_17;
	UBYTE MDM_REG_1E;
	UBYTE MDM_REG_1F;
};

/*
** ECMバッファ -> CDC -> DRAMパスチェック用
** 1999/05/18 by K.Okada
*/
#define ECM_BUFFER_DATA_SIZE	0x1480	/* 2で割り切れる数 */

/* 
** モデム／ソフトのどちらでCRCチェックNGかを表示
** 1999/07/22 by K.Okada
*/
#define MDM_NO_ERROR			0x00
#define MDM_HARD_FE				0x10
#define MDM_HARD_OE				0x20
#define MDM_HARD_PE				0x40
#define MDM_SOFT_CRC_NG			0x80


/*
** 受信３Ｍオーバチェック処理追加
** 1999/02/02 by T.Soneoka
** ported by H.Kubo 1999/09/14
*/
#define DECODE_MAX_LINE		61600	/* １５．４×４０００ｍｍ コーデックのデコードライン数が１６ＢＩＴの為、ＳＦＩＮＥで最高４２５５ｍｍまでしかみれません */
#define DECODE_3M_NORM		11550	/* ３．８５×３０００（ｍｍ） */
#define DECODE_3M_FINE		23100	/* ７．７  ×３０００（ｍｍ） */
#define DECODE_3M_SFINE		46200	/* １５．４×３０００（ｍｍ） */


/*
 * 音声関連
*/
#define VOICE_A                                      1
#define VOICE_B                                      2
#define VOICE_C                                      3
#define VOICE_D                                      4
#define VOICE_E                                      5
#define VOICETEST                                    6

/* Voice送出用ROMﾃｰﾌﾞﾙ */
struct VoiceData_t {
    UBYTE * StartAddr;		/* VOICE ﾒﾓﾘｴﾘｱ上の送出開始ｱﾄﾞﾚｽ */
    UWORD   	  Size;		/* VOICE DATA の DMA転送ｻｲｽﾞ	 */
    UBYTE       Level1;		/* 送出ﾚﾍﾞﾙ (ATT)				 */
    UBYTE       Level2;		/* 送出ﾚﾍﾞﾙ (in MODEM)			 */
};

/*
 * とりあえずこのファイルに追記、
 * あとで移動するのかな？
*/
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/11 */
#define		MSG_MELODY_FRASE_START		1
#define		MSG_SILENT_FRASE_START		2
#define		NAR_TIMEUP			3
 #endif
#endif

/*-----------------------------------------------------------
 * 2001/11/26 Y.Murata		YAWARAより移植 2002/01/17 T.Takagi
 * MDM_LOOP_BUG_FIX の内容は以下のとおり
 * １．ＤＳＰＲＡＭのアクセスで、MEACCが落ちるまで無限に待っていたのをソフトカウンターで抜けるようにした。
 *
 * ２．拡張ＦＩＦＯの有効／無効設定をアクセスしない。
 *          この拡張FIFOの設定のためのDSPRAMライトでモデムのステータスが返ってこずループする時がある。
 *          モデムをコンフィグするタイミング(ModemConfig()関数内)毎に行われていたが、
 *          拡張ＦＩＦＯは使用しないし、初期値もOFFなのでさわならい。
 *
 *
 *
 * MDM_INT_DMA_BUG_FIX の内容は以下のとおり
 * １．割り込み許可のアクセス方法修正。
 *          FM336とR288Fではアクセス方法が違います。FM336は全てメソッド１です。
 *
 * ２．割り込みマスクレジスタの見直し。
 *          モデム割り込みに中で要因を見ているにも関わらず、割り込みが許可されていないのがいくつかあった。
 *
 * ３．ＭＤＭの割り込み要因信号がきてるにもかかわらず、割り込みが入らない件対策。
 *          これにより割り込みが入らずポストメッセージ一発目取り逃がす時がある。
 *          モデム割り込みを抜ける時NEWSがたっていたらNSIEをOFF/ONする。
 *          NSIEをOFF/ONすることによりモデムからの割り込み要因もOFF/ONしエッジができるため割り込みが入るようになった。
 *          モデム割り込みを抜けるときに、NEWSがたっていなかっても、モデム<->モデムバッファ間のDMAが起動される前にRDBIAがたっているときがある。
 *          このときも、同様にモデムの割り込み要因がきてるにもかかわずモデム割り込みが入ってこない。
 *          モデム割り込みを抜けるときに、モデムDMAをかける前にRDBIAがたっていたら、RBUFFERをリードしてRDBIAを落とすようにした。
 *
 * ４．ＭＤＭ<->ＭＤＭバッファ間のＤＭＡ起動を変更。
 *          受信データバッファ割り込みが許可されない時があり、
 *          受信データFULL状態になっても割り込みが入らずDMAの起動が遅れ、これによりフレームのデータを取りこぼす時がある。
 *          受信時、NSSの17バイト目だけを取りこぼすことがあった。
 *
 * ５．フレーム間フラグの送出をタイマのみで行う。
 *          ＤＳＰＲＡＭをアクセスしてのフレーム間フラグ送出数の設定と、タイマーと２つで行っていたためＦＳＫの終結フラグの数が多かった。
 *
 * AMSのQATおよびメルボルン、ローマのDVT/QATがとおったらLONDON、ANT、NAGANO\FM336にも反映させる予定。
*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0))/*For FM336P By Y.Suzuki 2002/06/11*/ || (defined(SAKAKI) && defined(JP0)) || defined (SATSUKI2)  || defined(STOCKHM2)
#define MDM_INT_DMA_BUG_FIX
#define MDM_LOOP_BUG_FIX
#endif

#endif	/* End of File */
