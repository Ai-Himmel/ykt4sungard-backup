/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_DATA.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 帳票関係大域変数ﾌｧｲﾙ
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\lst_def.h"
#include	"\src\atlanta\define\sysjrnl.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\time.h"
#include	"\src\atlanta\define\timer10.h" /* By H.H 1996/08/23 */
#include	"\src\atlanta\define\sys_opt.h"

/*-----------------------------------------------*/
/* リストプリント用バッファ　　　　　　　　    　*/
/*-----------------------------------------------*/
union LstBuffer_t List = {0};

/*-----------------------------------------------*/
/* ジャーナル１件待避用バッファ    　　　　　　　*/
/*-----------------------------------------------*/
/*通信管理ﾚﾎﾟｰﾄ印刷中について。ﾎﾟｲﾝﾀ計算を行った後、印刷を行うが、ﾎﾟｲﾝﾀ計算*/
/*から、１件目の印刷まで間隔が空くため、この間に通信が終了して、データが*/
/*更新される可能性がある。これを防ぐ為、１０件目の印刷ﾃﾞｰﾀのみﾃﾞｰﾀを退避*/
/*しておく為のﾊﾞｯﾌｧ*/

struct SYS_JournalData_t BKJournalFile[10] = {0};

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/20 */
UBYTE BKJournalPoint[10] = {0};
#endif

/*-----------------------------------------------*/
/* 日時変換バッファ 				   　　　　　*/
/*-----------------------------------------------*/
TIME_DATA_t ListTime = {0};

/************************************************************************
*          BY:	石橋正和
*        DATE:	1994/06/02
* DESCRIPTION:	キャラクタ送信用文字列バッファ(V53専用)
************************************************************************/
struct LST_CharacterTxData_t LST_CharacterTx = {0};

/************************************************************************
*               BY:  M.Kotani
*             DATE:  May.30,1994
*        FILE NAME:  cdc_data.c
*       Task ID No:  Not Valid
*      DESCRIPTION:  キャラクタ送信，プリント用のフォント展開イメージバッファ
*        REFERENCE:  文字列のフォントイメージがセットされる
************************************************************************/
#if (PRO_CPU == SH7043) /* By S.Kawasaki 1996/03/11 */
	/*
	** RISCコンパイラー用のデータセクションを設定します。
	** MEMINDEXはDMEMINDEXの名前が自動的に設定されます。
	** 86系のセグメント名に相当する。
	** By S.Kawasaki 1996/07/05
	*/
	#pragma	section	FONTIMAGE
#endif

union FontImageBufferData_t FontImageBuffer = {0};

#if (PRO_CPU == SH7043) /* By S.Kawasaki 1996/03/11 */
	#pragma	section
#endif

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
UBYTE *FontImageBufferAddress = 0;

/************************************************************************
*               BY:  M.Kotani
*             DATE:  May.30,1994
*        FILE NAME:  cdc_data.c
*       Task ID No:  Not Valid
*      DESCRIPTION:  リスト縮小率
*        REFERENCE:
************************************************************************/
UBYTE LST_Reduction = 0;

/************************************************************************
* DESCRIPTION:	送信証・原稿付きチェックメッセージ用、キャラクタプリント部のライン数
************************************************************************/
UBYTE LST_CharacterLine = 0;

/************************************************************************
* DESCRIPTION:	標準10msタイマーイベント発生タスク用
************************************************************************/
struct Timer10msEventData_t	LST10msEventTimer = {0};

/************************************************************************
* DESCRIPTION:	標準10msタイマータスクＩＤ
************************************************************************/
UWORD tskno_cmn_watchtimer10msevent = 0xffff;

/************************************************************************
*          BY:	M.Tachibana
*        DATE:	1997/04/17
* DESCRIPTION:	ページカウンタ
************************************************************************/
UBYTE LST_PageCounter = 0;

/************************************************************************
*          BY:	M.Tachibana
*        DATE:	1997/09/09
* DESCRIPTION:	１ライン転送監視タイマ
************************************************************************/
UWORD LST_JAM_DetectCounter = 0;


/************************************************************************
*          BY:	Y.Murata
*        DATE:	1997/06/12
* DESCRIPTION:	マルチ回線達 
************************************************************************/
UBYTE LST_T30_JournalType = 0;
UBYTE LST_T30_Index = 0;
UBYTE T30PrintStackNumber = 0;
UBYTE T30PrintFaxComPerforming = 0;
UBYTE T30PrintCompatiError = 0;
UBYTE T30PrintLineNumber = 0;
UBYTE JournalLineNumber = 0;
UWORD T30PrintFaxComResult = 0;
UWORD LST_RxTotalLineSave[OPT_ERR_LINE_DATA_MAX] = {0};
UWORD LST_RxErrorTotalLineSave[OPT_ERR_LINE_DATA_MAX] = {0};
struct LST_CharacterTxData_t  MLT_CharacterTx = {0};

UWORD LST_DebugData = 0;

UBYTE DialCheckPointer = 0;	
UBYTE DialCheckBitPointer = 0;

UBYTE LST_Debug1 = 0;

#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  H.Kubo 1998/01/19  */
UBYTE LST_TxPageFinishStatus = 0; /* added by H.Kubo 1998/01/19 */
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
UBYTE InternalLineNumber = 0;	/* 0:標準回線 1:拡張回線 */
#endif

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/09 */
UBYTE LST_T30ConfNumber = 0;	/* Ｔ３０プリント指定番号 */
#endif
