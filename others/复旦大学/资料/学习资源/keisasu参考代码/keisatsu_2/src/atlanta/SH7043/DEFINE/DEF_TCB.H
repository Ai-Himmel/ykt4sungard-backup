/*--------------------------------------------------------------------------*/
/*プロジェクト: POPLAR/ANZU_L                                               */
/*モジュ-ル名 : DEF_TCB.H                                                   */
/*作成者名 	  : 野瀬                                                        */
/*日  付   	  : 96.10.12                                                    */
/*概  要   	  : TCB定義                                                     */
/*修正履歴    :                                                             */
/*--------------------------------------------------------------------------*/
#include "\src\atlanta\define\message.h"

/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\def_tcb.h"
#else

#ifndef def_tcb_h
	#define def_tcb_h	1

#define TCB_TBL_SIZE 	16

union wait_param_data_t {
	MESSAGE_t *sndmsg;	/* メッセージ送信待ち時、メッセージデータポインタ             */
	MESSAGE_t **rcvmsg;	/* メッセージ受信待ち時、メッセージデータポインタポインタ     */
	UWORD semno;		/* セマフォ待ち時、セマフォ番号                               */
	UWORD timer[2];		/* タイマー待ち時、０：タイマー設定値、１：タイマーカウント値 */
};

struct tcb_table_data_t {
	UBYTE tsk_stat;						/* +0 */
	UBYTE prog_no;						/* +1 */
	UBYTE priority;						/* +2 */
	UBYTE tsk_link;						/* +3 */
	UBYTE run_link;						/* +4 */
	UBYTE tsk_stat_tpo;					/* +5 */
	UWORD reserve;						/* +6 */
	union wait_param_data_t wait_param;	/* +8 */
	UDWORD *stack_addr;					/* +12 */
};

#endif

#endif
