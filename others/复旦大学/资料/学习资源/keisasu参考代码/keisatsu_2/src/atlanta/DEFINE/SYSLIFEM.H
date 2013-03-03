/* By Y.Suzuki 1996/10/15 */
/* Original File : jun\usr2:\src\anzu\define\syslifem.h */
#ifndef	syslifem_h
	#define	syslifem_h

/************************************************************************
 * ライフモニタ															*
 * struct SYS_LifeMonitorData_t SYB_LifeMonitor							*
 * syslifem.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_LifeMonitorData_t {	/* UWORD -> UDWORD に変更 By M.Tachibana 1997/12/09 */
	UDWORD ScanCount;			/* 読取り枚数 */
	UDWORD PrintCount;			/* プリント枚数 */
	UDWORD PrintCountCopy;		/* コピープリント枚数 By M.Tachibana 1997/09/08 */
	UDWORD PrintCountReceive;	/* 受信プリント枚数   By M.Tachibana 1997/09/08 */
	UDWORD PrintCountPC;			/* ＰＣプリント枚数   By M.Tachibana 1997/09/08 */
	UDWORD TransmitCount;		/* 送信枚数 */
	/*------------------------------------------------------------------*/
	/* 受信枚数の印字はＲ仕様に関るため、外しておきましょう、           */
	/* コンパイル時エラーが出たら、プログラムを消去して下さい。         */
	/* By S.K Sep.21,1995                                               */
	/*------------------------------------------------------------------*/
	/* UDWORD ReceiveCount;	*/	/* 受信枚数 */
	UDWORD DrumReplaceCount;		/* プリンタードラム交換回数 By S.Kawasaki 1996/06/19 */
	UDWORD DrumLifeCount;		/* プリンタードラム寿命カウンター（１個のドラムにおけるプリント枚数） 1996/06/24 Eguchi */
};

/************************************************************************
 * プリンタ管理用ライフモニタ											*
 * struct SYS_PrinterLifeMonitorData_t SYB_PrinterLifeMonitor			*
 * 1996/12/19															*
 * 橘正樹																*
 ************************************************************************/
#define	SYS_LIFE_TONER_DATA_MAX			10
#define	SYS_TONER_DATA_AREA_MAX			40
#define	SYS_HEATER_TROUBLE				0x0001
#define	SYS_HEATER_DISCONNECT			0x0002
#define	SYS_HEATER_SHORT				0x0004
#define	SYS_FAN_MOTOR_TROUBLE			0x0008
#define	SYS_RX_MOTOR_TROUBLE			0x0010
#define	SYS_DRUM_TROUBLE				0x0020
#define	SYS_PS_FAN_MOTOR_TROUBLE		0x0040
#define	SYS_HV_FUSE_DISCONNECT			0x0080


struct SYS_PrinterLifeMonitorData_t {
	UDWORD TotalPageCount;				/* 総印字枚数						*/
	UWORD  DrumReplaceCount;			/* ドラム交換回数					*/
	UWORD  TonerReplaceCount;			/* トナー（現像器）交換回数			*/
	UWORD  TransferReplaceCount;		/* 転写器（ローラー）交換回数		*/
	UWORD  FuserReplaceCount;			/* 定着器交換回数					*/
	UDWORD DrumLifeCount;				/* ドラム印字枚数					*/
	UWORD  TonerLifeCount;				/* トナー残り印字枚数				*/
	UWORD  reserve1;					/* リザーブ							*/
	UDWORD TransferLifeCount;			/* 転写器（ローラー）印字枚数		*/
	UDWORD FuserLifeCount;				/* 定着器印字枚数					*/
	UWORD  Jam1Cassette1Count;			/* ジャム１回数（カセット１）		*/
	UWORD  Jam1Cassette2Count;			/* ジャム１回数（カセット２）		*/
	UWORD  Jam1Cassette3Count;			/* ジャム１回数（カセット３）		*/
	UWORD  Jam1ManualCount;				/* ジャム１回数（手差し）			*/
	UWORD  Jam2Count;					/* ジャム２回数						*/
	UWORD  Jam3Count;					/* ジャム３回数						*/
	UDWORD A6_TotalCount;				/* Ａ６総印字枚数					*/
	UDWORD A5_TotalCount;				/* Ａ５総印字枚数					*/
	UDWORD A5R_TotalCount;				/* Ａ５Ｒ総印字枚数					*/
	UDWORD A4_TotalCount;				/* Ａ４総印字枚数					*/
	UDWORD B5_TotalCount;				/* Ｂ５総印字枚数					*/
	UDWORD B5R_TotalCount;				/* Ｂ５Ｒ総印字枚数					*/
	UDWORD B4_TotalCount;				/* Ｂ４総印字枚数					*/
	UDWORD LT_TotalCount;				/* レター総印字枚数					*/
	UDWORD LG_TotalCount;				/* リーガル総印字枚数				*/
	UDWORD F4_TotalCount;				/* Ｆ４総印字枚数					*/
	UDWORD Other1TotalCount;			/* その他１総印字枚数				*/
	UDWORD Other2TotalCount;			/* その他２総印字枚数				*/
	UDWORD ManualTotalCount;			/* 手差し総印字枚数					*/
	UBYTE  A6_PreCount;					/* Ａ６総印字枚数プリスケーラ		*/
	UBYTE  A5_PreCount;					/* Ａ５総印字枚数プリスケーラ		*/
	UBYTE  A5R_PreCount;				/* Ａ５Ｒ総印字枚数プリスケーラ		*/
	UBYTE  B5_PreCount;					/* Ｂ５総印字枚数プリスケーラ		*/
	UBYTE  B5R_PreCount;				/* Ｂ５Ｒ総印字枚数プリスケーラ		*/
	UBYTE  B4_PreCount;					/* Ｂ４総印字枚数プリスケーラ		*/
	UBYTE  LT_PreCount;					/* レター総印字枚数プリスケーラ		*/
	UBYTE  LG_PreCount;					/* リーガル総印字枚数プリスケーラ	*/
	UBYTE  F4_PreCount;					/* Ｆ４総印字枚数プリスケーラ		*/
	UBYTE  HLTR_PreCount;				/* ハーフレター総印字枚数プリスケーラ	*//* By M.Tachibana 1998/03/02 */
	UBYTE  EXE_PreCount;				/* エグゼクティブ総印字枚数プリスケーラ	*//* By M.Tachibana 1998/03/02 */
	UBYTE  DL_PreCount;					/* ＤＬ総印字枚数プリスケーラ	*//* By M.Tachibana 1998/03/02 */
	UBYTE  CM10_PreCount;				/* ＣＭ１０総印字枚数プリスケーラ	*//* By M.Tachibana 1998/03/02 */
	UBYTE  MNC_PreCount;				/* モナーク総印字枚数プリスケーラ	*//* By M.Tachibana 1998/03/02 */
	UBYTE  Other6PreCount;				/* その他６総印字枚数プリスケーラ	*/
	UBYTE  Other7PreCount;				/* その他７総印字枚数プリスケーラ	*/
	UBYTE  Other8PreCount;				/* その他８総印字枚数プリスケーラ	*/
	UBYTE  TonerDataCount;				/* トナーデータカウンタ				*/
	UBYTE  TonerData[SYS_LIFE_TONER_DATA_MAX];	/* トナーデータ格納領域			*/
	UWORD  ErrorStatus;					/* エラー状態						*/
	UBYTE  OrderListRequest;			/* 消耗品発注票プリント要求			*/
	UBYTE  TonerFewLevelCount;			/* トナーなしレベルの検出回数		*/
	UBYTE  TonerSupplyLevelCount;		/* トナーありレベルの検出回数		*/
	UBYTE  reserve4;					/* リザーブ							*/
	UBYTE  reserve5;					/* リザーブ							*/
	UBYTE  reserve6;					/* リザーブ							*/
	UDWORD reserve7;					/* リザーブ							*/
	UDWORD reserve8;					/* リザーブ							*/
	UDWORD reserve9;					/* リザーブ							*/
	UDWORD reserve10;					/* リザーブ							*/
	UDWORD reserve11;					/* リザーブ							*/
	UDWORD reserve12;					/* リザーブ							*/
	UDWORD reserve13;					/* リザーブ							*/
};

/************************************************************************
 * 通信エラーモニタ														*
 * struct SYS_FaxComErrorMonitorData_t SYB_FaxComErrorMonitor[]			*
 * 1997/06/23															*
 * 橘正樹																*
 ************************************************************************/
struct SYS_FaxComErrorMonitorData_t {
	UWORD MML_Count;	/* 自社機との交信エラー回数 */
	UWORD OtherCount;	/* 他社機との交信エラー回数 */
};

#endif
