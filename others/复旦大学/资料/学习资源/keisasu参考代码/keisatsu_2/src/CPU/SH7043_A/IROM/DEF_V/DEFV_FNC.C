/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : defv_fnc.c                                                */
/*  作成者       : 野瀬敏弘                                                  */
/*  日  付       : 1997/01/14                                                */
/*  概  要       : モニタコールアドレステーブル                              */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

#include "\src\atlanta\sh7043\define\mon_func.h"

void InitializeSystem(void);

#pragma section MONVEC /* locate section name "CMONVEC" */

/****************************/
/*  タスク管理  関連        */
/****************************/
CONST void (* CONST cre_tsk_vec)() = (void (*)())cre_tsk_irom;
CONST void (* CONST del_tsk_vec)() = (void (*)())del_tsk_irom;
CONST void (* CONST exi_tsk_vec)() = (void (*)())exi_tsk_irom;
#if (0) /* 新ﾏｽｸ変更 SCDから参照しているため"mon_tbl"c へ移動 */
** CONST void (* CONST wai_tsk_vec)() = (void (*)())wai_tsk_irom;
** CONST void (* CONST wai_oneshot_vec)() = (void (*)())wai_oneshot_irom;
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
CONST UBYTE (* CONST chk_semvl_vec)() = (UBYTE (*)())chk_semvl_irom;

/*******************************/
/*  メールボックス管理  関連   */
/*******************************/
CONST void (* CONST cre_mbx_vec)() = (void (*)())cre_mbx_irom;
CONST void (* CONST del_mbx_vec)() = (void (*)())del_mbx_irom;
CONST void (* CONST snd_msg_vec)() = (void (*)())snd_msg_irom;
#if (0) /* 新ﾏｽｸ変更 SCDから参照しているため"mon_tbl"c へ移動 */
** CONST void (* CONST rcv_msg_vec)() = (void (*)())rcv_msg_irom;
#endif
CONST WORD (* CONST chk_mbx_vec)() = (WORD (*)())chk_mbx_irom;
CONST WORD (* CONST chk_rcv_vec)() = (WORD (*)())chk_rcv_irom;

/******************************/
/*  イベントフラグ管理  関連  */
/******************************/
CONST void (* CONST wai_evt_vec)() = (void (*)())wai_evt_irom;
CONST void (* CONST det_evt_vec)() = (void (*)())det_evt_irom;
CONST void (* CONST idet_evt_vec)() = (void (*)())idet_evt_irom;

#if (0) /* mon_tbl.c へ移動 */
** /******************************/
** /*  モニターサブルーチン      */
** /******************************/
** CONST void (* CONST cre_ready_link_vec)() = (void (*)())cre_ready_link_irom;
** CONST void (* CONST del_ready_link_vec)() = (void (*)())del_ready_link_irom;
** CONST void (* CONST rescheduler_vec)() = (void (*)())rescheduler_irom;
** CONST void (* CONST ready_func_vec)() = (void (*)())ready_func_irom;
** CONST void (* CONST monitor_error_vec)() = (void (*)())monitor_error;
** CONST void (* CONST SetOneshotTimer_vec)() = (void (*)())SetOneshotTimer;
** 
** /******************************/
** /* システム初期化ルーチン     */
** /******************************/
** CONST void (* CONST InitializeSystem_vec)() = (void (*)())InitializeSystem;
** 
#endif

#pragma section
