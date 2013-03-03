/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : mon_func.h                                                */
/*  作成者       : 野瀬敏弘                                                  */
/*  日  付       : 1997/01/14                                                */
/*  概  要       : モニタシステムコールプロトタイプ宣言                      */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#ifndef	mon_func2_h
	#define	mon_func2_h	1

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
UBYTE chk_semvl_irom(UWORD);
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
void SetOneshotTimer_irom(UWORD);

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
UBYTE chk_semvl_erom(UWORD);
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
void SetOneshotTimer_erom(UWORD);

/******************************/
/*  モニターエラールーチン    */
/******************************/
void monitor_error(void);

/******************************/
/* システム初期化ルーチン     */
/******************************/
void InitializeSystem(void);

#endif
