/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_DATA.H
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: リストタスク大域変数
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef	LST_DATA_H
	#define	LST_DATA_H	1

#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\time.h"
#include	"\src\atlanta\define\lst_def.h"
#include	"\src\atlanta\define\sysjrnl.h"
#include	"\src\atlanta\define\timer10.h" /* By H.H 1996/08/23 */
#include	"\src\atlanta\define\sys_opt.h"

/*-----------------------------------------------*/
/* リストプリント用バッファ　　　　　　　　    　*/
/*-----------------------------------------------*/
extern  union LstBuffer_t List;

/*-----------------------------------------------*/
/* オペレーションテーブル待避用バッファ    　　　*/
/*-----------------------------------------------*/
extern UBYTE FuncTableSw[];	/* さつき */

/*-----------------------------------------------*/
/* ジャーナル１件待避用バッファ    　　　　　　　*/
/*-----------------------------------------------*/
extern struct SYS_JournalData_t BKJournalFile[10];

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/20 */
extern UBYTE BKJournalPoint[10];
#endif

/*-----------------------------------------------*/
/* 日時変換バッファ 				   　　　　　*/
/*-----------------------------------------------*/
extern TIME_DATA_t ListTime;

/************************************************************************
*          BY:	石橋正和
*        DATE:	1994/06/02
* DESCRIPTION:	キャラクタ送信用文字列バッファ(V53専用)
************************************************************************/
extern struct LST_CharacterTxData_t LST_CharacterTx;

/************************************************************************
*               BY:  M.Kotani
*             DATE:  May.30,1994
*        FILE NAME:  cdc_data.c
*       Task ID No:  Not Valid
*      DESCRIPTION:  キャラクタ送信，プリント用のフォント展開イメージバッファ
*        REFERENCE:  文字列のフォントイメージがセットされる
************************************************************************/
extern union FontImageBufferData_t FontImageBuffer;

/************************************************************************
*               BY:  M.Kotani
*             DATE:  Jun.8,1994
*        FILE NAME:  cdc_data.c
*       Task ID No:  Not Valid
*      DESCRIPTION:  キャラクタ送信，プリント用のフォント展開イメージバッファの情報
*                     0:展開禁止
*                    !0:展開するアドレス
*        REFERENCE:  文字列のフォントイメージがセットされる
************************************************************************/
extern UBYTE *FontImageBufferAddress;

/************************************************************************
*               BY:  M.Kotani
*             DATE:  May.30,1994
*        FILE NAME:  cdc_data.c
*       Task ID No:  Not Valid
*      DESCRIPTION:  リスト縮小率
*        REFERENCE:
************************************************************************/
extern UBYTE LST_Reduction;

/************************************************************************
*          BY:	H.Hirao
*        DATE:	1996/06/07
* DESCRIPTION:	送信証・原稿付きチェックメッセージ用、キャラクタプリント部のライン数
************************************************************************/
extern UBYTE LST_CharacterLine;

/************************************************************************
*          BY:	H.Hirao
*        DATE:	1996/08/23
* DESCRIPTION:	標準10msタイマーイベント発生タスク用
************************************************************************/
extern struct Timer10msEventData_t	LST10msEventTimer;

/************************************************************************
*          BY:	H.Hirao
*        DATE:	1996/08/24
* DESCRIPTION:	標準10msタイマータスクＩＤ
************************************************************************/
extern UWORD tskno_cmn_watchtimer10msevent;

/************************************************************************
*          BY:	M.Tachibana
*        DATE:	1997/04/17
* DESCRIPTION:	ページカウンタ
************************************************************************/
extern UBYTE LST_PageCounter;

/************************************************************************
*          BY:	M.Tachibana
*        DATE:	1997/09/09
* DESCRIPTION:	１ライン転送監視タイマ
************************************************************************/
extern UWORD LST_JAM_DetectCounter;

/************************************************************************
*          BY:	Y.Murata
*        DATE:	1997/06/12
* DESCRIPTION:	マルチ回線達 
************************************************************************/
extern UBYTE LST_T30_JournalType;
extern UBYTE LST_T30_Index;
extern UBYTE T30PrintStackNumber;
extern UBYTE T30PrintFaxComPerforming;
extern UBYTE T30PrintCompatiError;
extern UBYTE T30PrintLineNumber;
extern UBYTE JournalLineNumber;
extern UWORD T30PrintFaxComResult;
extern UWORD LST_RxTotalLineSave[OPT_ERR_LINE_DATA_MAX];
extern UWORD LST_RxErrorTotalLineSave[OPT_ERR_LINE_DATA_MAX];
extern struct LST_CharacterTxData_t  MLT_CharacterTx;


extern UWORD LST_DebugData;

extern UBYTE DialCheckPointer;		/** 現在調べているダイヤル種別  97/08/29 Add By M.Kuwahara */
extern UBYTE DialCheckBitPointer;	/** 現在調べているダイヤル種別のオフセット */

extern UBYTE LST_Debug1;


#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  H.Kubo 1998/01/19  */
extern UBYTE LST_TxPageFinishStatus; /* added by H.Kubo 1998/01/19 */
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
extern UBYTE InternalLineNumber;	/* 0:標準回線 1:拡張回線 */
#endif

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/09 */
extern UBYTE LST_T30ConfNumber;		/* Ｔ３０プリント指定番号 */
#endif

#endif	/* End of File */

