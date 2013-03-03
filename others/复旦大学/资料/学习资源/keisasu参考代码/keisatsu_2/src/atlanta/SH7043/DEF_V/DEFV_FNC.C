/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : defv_fnc.c.h                                              */
/*  作成者       : 野瀬敏弘                                                  */
/*  日  付       : 1997/01/14                                                */
/*  概  要       : モニタコールアドレステーブル                              */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\def_v\defv_fnc.c"
#else

#include "\src\atlanta\sh7043\define\mon_func.h"

#pragma section MONVEC /* locate section name "CMONVEC" */

/****************************/
/*  タスク管理  関連        */
/****************************/
CONST void (* CONST cre_tsk_vec)() = (void (*)())cre_tsk_irom;
CONST void (* CONST del_tsk_vec)() = (void (*)())del_tsk_int;	/* バグ吸収 */
CONST void (* CONST exi_tsk_vec)() = (void (*)())exi_tsk_irom;
CONST void (* CONST wai_tsk_vec)() = (void (*)())wai_tsk_irom;
#if(0)/* V851 誤ﾀﾞｲﾔﾙ対策 By Y.Suzuki 2002/10/03 */
CONST void (* CONST wai_oneshot_vec)() = (void (*)())wai_oneshot_irom;
#else
CONST void (* CONST wai_oneshot_vec)() = (void (*)())wai_oneshot_erom;
#endif
CONST void (* CONST wup_tsk_vec)() = (void (*)())wup_tsk_irom;

/*****************************/
/*  セマフォ管理  関連       */
/*****************************/
CONST void (* CONST cre_sem_vec)() = (void (*)())cre_sem_irom;
CONST void (* CONST del_sem_vec)() = (void (*)())del_sem_irom;
CONST void (* CONST sig_sem_vec)() = (void (*)())sig_sem_irom;
CONST void (* CONST wai_sem_vec)() = (void (*)())wai_sem_irom;
CONST WORD (* CONST chk_sem_vec)() = (WORD (*)())chk_sem_irom;

/*******************************/
/*  メールボックス管理  関連   */
/*******************************/
CONST void (* CONST cre_mbx_vec)() = (void (*)())cre_mbx_irom;
CONST void (* CONST del_mbx_vec)() = (void (*)())del_mbx_irom;
CONST void (* CONST snd_msg_vec)() = (void (*)())snd_msg_irom;
CONST void (* CONST rcv_msg_vec)() = (void (*)())rcv_msg_irom;
CONST WORD (* CONST chk_mbx_vec)() = (WORD (*)())chk_mbx_int; /* バグ吸収 */
CONST WORD (* CONST chk_rcv_vec)() = (WORD (*)())chk_rcv_int; /* バグ吸収 */

/******************************/
/*  イベントフラグ管理  関連  */
/******************************/
CONST void (* CONST wai_evt_vec)() = (void (*)())wai_evt_irom;
CONST void (* CONST det_evt_vec)() = (void (*)())det_evt_irom;
CONST void (* CONST idet_evt_vec)() = (void (*)())idet_evt_int; /* バグ吸収 */

/******************************/
/*  モニターサブルーチン      */
/******************************/
CONST void (* CONST cre_ready_link_vec)() = (void (*)())cre_ready_link_irom;
CONST void (* CONST del_ready_link_vec)() = (void (*)())del_ready_link_irom;
CONST void (* CONST rescheduler_vec)() = (void (*)())rescheduler_irom;
CONST void (* CONST ready_func_vec)() = (void (*)())ready_func_irom;


#pragma section

#endif
