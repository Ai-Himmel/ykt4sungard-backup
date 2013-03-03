/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : mon_func.h                                                */
/*  作成者       : 野瀬敏弘                                                  */
/*  日  付       : 1997/01/14                                                */
/*  概  要       : モニタシステムコールプロトタイプ宣言                      */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/

/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\mon_func.h"
#else
/**********************************************/
/** ＳＨ７０４１内蔵ＲＯＭ上のモニターコール **/
/**********************************************/
/****************************/
/*  タスク管理  関連        */
/****************************/
void cre_tsk_irom(UWORD *, UWORD, void *);
void del_tsk_irom(UWORD *);
void exi_tsk_irom(void);
void wai_tsk_irom(UWORD);
void wai_oneshot_irom(UWORD);
void wup_tsk_irom(UWORD *);
/*****************************/
/*  セマフォ管理  関連       */
/*****************************/
void cre_sem_irom(WORD *);
void del_sem_irom(WORD *);
void sig_sem_irom(UWORD);
void wai_sem_irom(UWORD);
WORD chk_sem_irom(UWORD);
/*******************************/
/*  メールボックス管理  関連   */
/*******************************/
void cre_mbx_irom(WORD *);
void del_mbx_irom(WORD *);
void snd_msg_irom(UWORD, void *);
void rcv_msg_irom(UWORD, void *);
WORD chk_mbx_irom(UWORD);
WORD chk_rcv_irom(UWORD);
/******************************/
/*  イベントフラグ管理  関連  */
/******************************/
void wai_evt_irom(UWORD);
void det_evt_irom(UWORD);
void idet_evt_irom(UWORD);
/******************************/
/*  モニターサブルーチン      */
/******************************/
void cre_ready_link_irom(void);
void del_ready_link_irom(void);
void ready_func_irom(void);
void rescheduler_irom(void);

/**********************************************/
/**      外付けＲＯＭ上のモニターコール      **/
/**********************************************/
/****************************/
/*  タスク管理  関連        */
/****************************/
void cre_tsk_erom(UWORD *, UWORD, void *);
void del_tsk_erom(UWORD *);
void exi_tsk_erom(void);
void wai_tsk_erom(UWORD);
void wai_oneshot_erom(UWORD);
void wup_tsk_erom(UWORD *);
/*****************************/
/*  セマフォ管理  関連       */
/*****************************/
void cre_sem_erom(WORD *);
void del_sem_erom(WORD *);
void sig_sem_erom(UWORD);
void wai_sem_erom(UWORD);
WORD chk_sem_erom(UWORD);
/*******************************/
/*  メールボックス管理  関連   */
/*******************************/
void cre_mbx_erom(WORD *);
void del_mbx_erom(WORD *);
void snd_msg_erom(UWORD, void *);
void rcv_msg_erom(UWORD, void *);
WORD chk_mbx_erom(UWORD);
WORD chk_rcv_erom(UWORD);
/******************************/
/*  イベントフラグ管理  関連  */
/******************************/
void wai_evt_erom(UWORD);
void det_evt_erom(UWORD);
void idet_evt_erom(UWORD);
/******************************/
/*  モニターサブルーチン      */
/******************************/
void cre_ready_link_erom(void);
void del_ready_link_erom(void);
void ready_func_erom(void);
void rescheduler_erom(void);

/**********************************/
/*  割込み禁止期間測定 ＆         */
/*  バグ吸収処理モニターエントリ  */
/**********************************/
void del_tsk_int(UWORD *);
WORD chk_mbx_int(UWORD);
WORD chk_rcv_int(UWORD);
void idet_evt_int(UWORD);

/**********************************************/
/**  割込み禁止期間測定モニターエントリ      **/
/**  デバッグが終わり次第はずします   T.Nose **/
/**********************************************/
void cre_tsk_int(UWORD *, UWORD, void *);
void exi_tsk_int(void);
void wai_tsk_int(UWORD);
void wai_oneshot_int(UWORD);
void wup_tsk_int(UWORD *);
void cre_sem_int(WORD *);
void del_sem_int(WORD *);
void sig_sem_int(UWORD);
void wai_sem_int(UWORD);
WORD chk_sem_int(UWORD);
void cre_mbx_int(WORD *);
void del_mbx_int(WORD *);
void snd_msg_int(UWORD, void *);
void rcv_msg_int(UWORD, void *);
void wai_evt_int(UWORD);
void det_evt_int(UWORD);

#endif
