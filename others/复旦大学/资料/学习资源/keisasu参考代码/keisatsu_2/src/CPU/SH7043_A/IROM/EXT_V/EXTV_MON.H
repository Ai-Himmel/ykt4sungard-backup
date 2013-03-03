/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : extv_mon.h                                               */
/*  作成者       : 野瀬敏弘                                                 */
/*  日  付       : 96/10/11                                                 */
/*  概  要       : モニタテーブル                                           */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#ifndef EXTV_MON_H
	#define EXTV_MON_H 1

#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\def_mon.h"
#include "\src\cpu\sh7043_a\irom\define\def_tcb.h"
#include "\src\cpu\sh7043_a\irom\define\def_scb.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#else
#include "\src\atlanta\sh7043\define\def_mon.h"
#include "\src\atlanta\sh7043\define\def_tcb.h"
#include "\src\atlanta\sh7043\define\def_scb.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#endif

extern UBYTE real_run_tid;
extern UBYTE top_ready_tid;
extern UBYTE wai_tsk_tid;
extern UBYTE wai_1shot_tid;
extern struct tcb_table_data_t tcb[];
extern struct tib_table_data_t tib[];
extern struct scb_table_data_t scb[];
extern UBYTE mcb[];
extern UBYTE ecb[];

extern UDWORD MON_StackCheckTable[];

extern UDWORD small_stack_area[][SMALL_STACK/4];
extern UDWORD large_stack_area[][LARGE_STACK/4];

extern UBYTE MON_DebugSwitch;

#endif
