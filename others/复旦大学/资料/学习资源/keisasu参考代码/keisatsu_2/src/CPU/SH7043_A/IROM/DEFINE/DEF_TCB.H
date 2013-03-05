/*--------------------------------------------------------------------------*/
/*プロジェクト: POPLAR/ANZU_L                                               */
/*モジュ-ル名 : DEF_TCB.H                                                   */
/*作成者名 	  : 野瀬                                                        */
/*日  付   	  : 96.10.12                                                    */
/*概  要   	  : TCB定義                                                     */
/*修正履歴    :                                                             */
/*--------------------------------------------------------------------------*/
#ifndef def_tcb2_h
	#define def_tcb2_h	1

#include "\src\atlanta\define\message.h"

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
