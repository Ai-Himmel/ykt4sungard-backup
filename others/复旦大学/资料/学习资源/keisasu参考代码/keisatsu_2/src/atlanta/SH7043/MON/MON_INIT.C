/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : MON_INT.C                                                */
/*  作成者       : 野瀬敏弘                                                 */
/*  日  付       : 96.10.11                                                 */
/*  概  要       : モニタ初期化                                             */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\ext_v\bkupram.h"

#include "\src\atlanta\define\mntsw_a.h"
#include "\src\atlanta\define\mntsw_j.h"
#include "\src\atlanta\sh7043\define\def_mon.h"
#include "\src\atlanta\sh7043\ext_v\extv_mon.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\sh7043\ext_v\extv_sem.h"

#include "\src\atlanta\sh7043\ext_v\mon_tbl.h"


/*****************************************************************************
	module		:[モニタの初期化]
	function	:[
		1.
		2.
	]
	return		:[なし]
	common		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MON]
	date		:[1996/10/11]
	author		:[野瀬敏弘]
*****************************************************************************/
void InitializeMonitor(void)
{
	UWORD count;
	UWORD count_limit;

	UBYTE *b_ptr;
	WORD *ptr;
	UDWORD *address;
	UDWORD address_value;
	struct tcb_table_data_t *tcbptr;
	struct scb_table_data_t *scbptr;

	UDWORD initial_value;	/* スタック使用量調査 T.Nose 1998/02/20 */

	/* スタックチェックテーブルの作成
	** MON_StackCheckTable[0]  = H'804000 小タスクスタックスタートアドレス
	** MON_StackCheckTable[32] = H'802000 小タスク大タスク分界点
	** MON_StackCheckTable[48] = H'800000 大タスクスタックエンドアドレス
	*/
	address = MON_StackCheckTable_p;
	*address = MON_STACK_START_ADDR;
	for (count = 0; count < (UWORD)MON_MAX_TCB; count++) {
		address_value = *address;
		address++;
		if (count < MON_MAX_SMALL_TCB) {
			*address = address_value - (UDWORD)MON_SIZE_SMALL_STACK;
		}
		else {
			*address = address_value - (UDWORD)MON_SIZE_LARGE_STACK;
		}
	}

	/* スタック使用量調査 T.Nose 1998/02/20 */
	initial_value = (UDWORD)0xA5A5A5A5;

	/* スタッククリア
	** メンテナンススイッチＡ１～Ａ４に０がセットされていれば全スタック領域クリア
	** ０でなければアイドルタスクのスタックのみクリア
	** Ｊ１～Ｊ４（ＣＰＵ例外処理アドレス）追加 T.Nose 1998/04/16
	*/
	if (((SYB_MaintenanceSwitch[MNT_SW_A1] == 0)
	  && (SYB_MaintenanceSwitch[MNT_SW_A2] == 0)
	  && (SYB_MaintenanceSwitch[MNT_SW_A3] == 0)
	  && (SYB_MaintenanceSwitch[MNT_SW_A4] == 0))		/* メンテナンススイッチＡ１～Ａ４が全て０か？ */
	 && ((SYB_MaintenanceSwitch[MNT_SW_J1] == 0)
	  && (SYB_MaintenanceSwitch[MNT_SW_J2] == 0)
	  && (SYB_MaintenanceSwitch[MNT_SW_J3] == 0)
	  && (SYB_MaintenanceSwitch[MNT_SW_J4] == 0))) {	/* メンテナンススイッチＪ１～Ｊ４が全て０か？ 1998/04/16 */

		/* 小スタック領域のクリア */
		address = small_stack_area_p;
		count_limit = (UWORD)(MON_MAX_SMALL_TCB * (MON_SIZE_SMALL_STACK / 4));
		for (count = 0; count < count_limit; count++) {
/*			*address++ = (UDWORD)0; スタック使用量調査 T.Nose 1998/02/20 */
			*address++ = initial_value;
		}

		/* 大スタック領域のクリア */
		address = large_stack_area_p;
		count_limit = (UWORD)(MON_MAX_LARGE_TCB * (MON_SIZE_LARGE_STACK / 4));
		for (count = 0; count < count_limit; count++) {
/*			*address++ = (UDWORD)0; スタック使用量調査 T.Nose 1998/02/20 */
			*address++ = initial_value;
		}
	}
	else {
		/* アイドルタスクのスタッククリア */
		address = initial_task_stack_area_p;
		count_limit = (UWORD)(MON_SIZE_SMALL_STACK / 4);
		for (count = 0; count < count_limit; count++) {
/*			*address++ = (UDWORD)0; スタック使用量調査 T.Nose 1998/02/20 */
			*address++ = initial_value;
		}
	}

	/* スタック使用量調査 T.Nose 1998/02/20 */
	address = (UDWORD *)MON_TOP_SMALL_ADDR;
	for (count = 0; count < (STACK_PUSH_SIZE/4); count++) {
		*address++ = (UDWORD)0;
	}

	/*****************************************/
	/* システムテーブルの初期化              */
	/*****************************************/
	top_ready_tid = INIT_TID;
	real_run_tid = 0xFF;
	wai_tsk_tid = 0xFF;
	wai_1shot_tid = 0xFF;

	/*****************************************/
	/* イニシャルタスクＴＣＢの初期化        */
	/*****************************************/
	tcbptr = tcb_p;
	tcbptr->tsk_stat		= READY;
	tcbptr->prog_no			= TSK_INITIAL;
	tcbptr->priority		= tib[TSK_INITIAL].priority; /* tib はアドレス固定 */
	tcbptr->tsk_link		= 0xFF;
	tcbptr->run_link		= 0xFF;
	tcbptr->tsk_stat_tpo	= 0;
	tcbptr->reserve			= 0xFFFF;
	tcbptr->wait_param.sndmsg = 0;
	tcbptr->stack_addr		= (UDWORD *)MON_TOP_SMALL_ADDR;
	address = (UDWORD *)(MON_TOP_SMALL_ADDR + STACK_PC_POSITION);
	*address = (UDWORD)tib[TSK_INITIAL].start_addr;

	/*****************************************/
	/* ＴＣＢの初期化                        */
	/*****************************************/
	/* tcbptr は初期化ずみ */
	for (count = 1; count < MON_MAX_TCB; count++) {
		tcbptr++;
		tcbptr->tsk_stat	= NOT_USED;
		tcbptr->prog_no		= 0xFF;
		tcbptr->priority	= 0xFF;
		tcbptr->tsk_link	= 0xFF;
		tcbptr->run_link	= 0xFF;
		tcbptr->tsk_stat_tpo	= 0xFF;
		tcbptr->reserve		= 0xFFFF;
		tcbptr->wait_param.sndmsg = (MESSAGE_t *)0xFFFFFFFF;
		tcbptr->stack_addr	= (void *)0xFFFFFFFF;
	}

	/*****************************************/
	/* ＭＣＢの初期化                        */
	/*****************************************/
	b_ptr = mcb_p;
	for (count = 0; count < MON_MAX_MCB; count++) {
		*b_ptr = 0xFF;
		b_ptr++;
	}

	/*****************************************/
	/* メールボックス管理テーブルの初期化    */
	/* mbxno.XXX = 0xFFFF                    */
	/*****************************************/
	ptr = (WORD *)mbxno_p;
	for (count = 0; count < (UWORD)MON_MAX_MBXNO; count++) {
		*ptr = 0xFFFF;
		ptr++;
	}

	/*****************************************/
	/* ＳＣＢの初期化                        */
	/*****************************************/
	scbptr = scb_p;
	for (count = 0; count < MON_MAX_SCB; count++) {
		scbptr->stat = 0xFF;
		scbptr->tid = 0xFF;
		scbptr++;
	}

	/*****************************************/
	/* セマフォ管理テーブルの初期化          */
	/* semno.XXX = 0xFFFF                    */
	/*****************************************/
	ptr = (WORD *)semno_p;
	for (count = 0; count < MON_MAX_SEMNO; count++) {
		*ptr = 0xFFFF;
		ptr++;
	}

	/*****************************************/
	/* ＥＣＢの初期化                        */
	/*****************************************/
	b_ptr = ecb_p;
	for (count = 0; count < MON_MAX_ECB; count++) {
		*b_ptr = 0xFF;
		b_ptr++;
	}

}

