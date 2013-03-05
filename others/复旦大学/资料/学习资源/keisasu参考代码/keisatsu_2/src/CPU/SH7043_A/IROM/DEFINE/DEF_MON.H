#ifndef def_mon_h
	#define def_mon_h 1
/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : DEF_MON.H                                                */
/*  作成者       : 野瀬敏弘                                                 */
/*  日  付       : 96.10.11                                                 */
/*  概  要       : モニタ定義                                               */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 タスク イニシャルプログラムNo.
-----------------------------------------------------------------------------*/
#define INIT_TID		0 /* イニシャルタスクのＴＣＢオフセット */
#define TSK_INITIAL		0 /* イニシャルタスクのＴＩＢオフセット */

/*-----------------------------------------------------------------------------
 モニタ システム
-----------------------------------------------------------------------------*/
#define LARGE_STACK_MAX		22 /* <- 16 1997/04/24 T.Nose */
#define SMALL_STACK_MAX		44 /* <- 32 1997/04/24 T/Nose */
#define TOTAL_STACK_MAX		(SMALL_STACK_MAX+LARGE_STACK_MAX)

/*  スタック512->640に増やします（１２８増） もうかつかつです by T.Soneoka 1997/12/18 */
#if defined(POPLAR_H)
#define LARGE_STACK			640
#elif defined(POPLAR_B) || defined(POPLR_BN) || defined (POPLAR_L) || defined (POPLAR_N)
#define LARGE_STACK			584
#elif defined(SAKAKI)	/* 1998/10/09 H.Yoshikawa */
#define LARGE_STACK			720		/* 1998/11/24(640->720) H.Yoshikawa */
#elif defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined(KEISATSU) || defined(SATSUKI2) || defined(STOCKHM2)	/* For HINOKI By O.Kimoto 1998/09/07 */ /* HINOKI2 2001/11/12 T.Takagi */
#define LARGE_STACK			640
#else
#define LARGE_STACK			512
#endif

#if defined(POPLAR_B) || defined(POPLA_BN) || defined (POPLAR_L) || defined (POPLAR_N)
#define SMALL_STACK			288
#elif defined(POPLAR_H)
/* 子タスクスタックあふれの為、スタックを２５６－＞２８８に変更します。 By O.Kimoto 1998/03/02 */
#define SMALL_STACK			288	/* Change 256 to 288 By O.Kimoto 1998/03/02 */
#elif defined(SAKAKI)	/* 1998/10/09 H.Yoshikawa */
#define SMALL_STACK			288
#elif defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined(KEISATSU) || defined(SATSUKI2) || defined(STOCKHM2)	/* For HINOKI By O.Kimoto 1998/09/07 */ /* HINOKI2 2001/11/12 T.Takagi */
#if (0) /* 子タスクを128増やします 288->288+128=416 1999/01/19 by T.Soneoka */
**	#define SMALL_STACK			288
#else
	#define SMALL_STACK			416
#endif
#else
#define SMALL_STACK			256
#endif

/* #define TASK_STACK_START	0x00809800 */
/* 下行の"0x00805800"を変更するときはロケートファイルも変更すること T.Nose */
#if defined(POPLAR_H)
/* 子タスクスタックあふれの為、スタックを２５６－＞２８８に変更します。
** と同時に、スタックの先頭アドレスを６００H繰り上げます。
** By O.Kimoto 1998/03/02
*/
#define TASK_STACK_START	0x00805200+(LARGE_STACK_MAX*LARGE_STACK)+(SMALL_STACK_MAX*SMALL_STACK)
#elif defined(SAKAKI)	/* 1998/10/09 H.Yoshikawa */
#define TASK_STACK_START	0x00806800+(LARGE_STACK_MAX*LARGE_STACK)+(SMALL_STACK_MAX*SMALL_STACK)
#elif defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined(KEISATSU) || defined(SATSUKI2) || defined(STOCKHM2)	/* For HINOKI By O.Kimoto 1998/09/07 */ /* HINOKI2 2001/11/12 T.Takagi */
#if (0) /* 子タスクを128増やししたため、アドレス調整によって先頭アドレスも変更します 1999/01/19 by T.Soneoka */
**	/* #define TASK_STACK_START	0x00805200+(LARGE_STACK_MAX*LARGE_STACK)+(SMALL_STACK_MAX*SMALL_STACK) By H.Hirao 1998/09/18 */
**	#define TASK_STACK_START	0x00406800+(LARGE_STACK_MAX*LARGE_STACK)+(SMALL_STACK_MAX*SMALL_STACK)
#else
	#define TASK_STACK_START	0x00405000+(LARGE_STACK_MAX*LARGE_STACK)+(SMALL_STACK_MAX*SMALL_STACK)
#endif
#else
#define TASK_STACK_START	0x00206800+(LARGE_STACK_MAX*LARGE_STACK)+(SMALL_STACK_MAX*SMALL_STACK)
#endif

#define STACK_PUSH_SIZE		88 /* スタック退避 88byte使用 */
#define STACK_PC_POSITION	80
#define TOP_LARGE_ADDR 		(TASK_STACK_START-(SMALL_STACK*SMALL_STACK_MAX)-STACK_PUSH_SIZE)
#define TOP_SMALL_ADDR 		(TASK_STACK_START-STACK_PUSH_SIZE)

/***************************************************************************
 タスク ステータス
***************************************************************************/
#define WAIT				0x00
#define READY				0x40
#define NOT_USED			0xC0

#define SND_WAIT			0x01
#define RCV_WAIT			0x02
#define WAIT_SEM			0x03
#define WAIT_TIMER			0x04
#define WAIT_EVENT			0x05
#define WAIT_ONESHOT		0x06

/***************************************************************************
 セマフォ
***************************************************************************/
/* #define SEMNO_MAX			32 *//* scb max *//* T.Nose 1997/07/04 */
#define SEMNO_MAX			64 /* scb max */

/* SCB Status */
#define SCB_INIT			0x7F
#define SCB_FREE			0x3F

/***************************************************************************
 メイルボックス
***************************************************************************/
#define MBXNO_MAX			256 /* mcb max */

/* MCB Status */
#if (0) /* Task MAX Change 1996/10/31 */
#define NO_WAIMBX			0xBF	/* 待ちタスク無し     */
#define SND_MBX				0x00	/* 送信待ちタスク有りステータス */
#define RCV_MBX				0x40	/* 受信待ちタスク有りステータス */
#define BLNK_MBX			0x80	/* 待ちタスク無しステータス     */
#endif

#define MBX_NOT_CREATE		0xFF	/* メイルボックスがクリエイトされていない */
#define NO_WAIMBX			0x7F	/* 待ちタスク無し     */

/***************************************************************************
 イベントフラグ
***************************************************************************/
/* #define EVENT_MAX			75 */ /* ecb max */
/* #define EVENT_MAX			95 */ /* ecb max */ /* Changed with def_evtn.h for R288F by H.Kubo 1997/06/30 */
#define EVENT_MAX			256 /* ecb max */ /* T.Nose 1997/06/30 */

/***************************************************************************
 ワンショットタイマー最大値（ＭＴＵ設定に依存します)
***************************************************************************/
#define ONESHOT_VALUE_MAX	26

#endif
