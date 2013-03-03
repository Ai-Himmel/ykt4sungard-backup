/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : mon_pro.h                                                 */
/*  作成者       : 野瀬敏弘                                                  */
/*  日  付       : 1996/10/15                                                */
/*  概  要       : モニタシステムコールプロトタイプ宣言                      */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#ifndef mon_pro_h
 #define mon_pro_h

/****************************/
/*  プロトタイプ宣言        */
/****************************/
extern CONST void (* CONST cre_tsk_vec)(UWORD *, UWORD, void *);
extern CONST void (* CONST del_tsk_vec)(UWORD *);
extern CONST void (* CONST exi_tsk_vec)(void);
extern CONST void (* CONST wai_tsk_vec)(UWORD);
extern CONST void (* CONST wai_oneshot_vec)(UWORD);
extern CONST void (* CONST wup_tsk_vec)(UWORD *);

extern CONST void (* CONST cre_sem_vec)(WORD *);
extern CONST void (* CONST del_sem_vec)(WORD *);
extern CONST void (* CONST sig_sem_vec)(UWORD);
extern CONST void (* CONST wai_sem_vec)(UWORD);
extern CONST WORD (* CONST chk_sem_vec)(UWORD);
extern CONST UBYTE chk_semvl_erom(UWORD);			/* 1998/02/09 T.Nose */

extern CONST void (* CONST cre_mbx_vec)(WORD *);
extern CONST void (* CONST del_mbx_vec)(WORD *);
extern CONST void (* CONST snd_msg_vec)(UWORD, void *);
extern CONST void (* CONST rcv_msg_vec)(UWORD, void *);
extern CONST WORD (* CONST chk_mbx_vec)(UWORD);
extern CONST WORD (* CONST chk_rcv_vec)(UWORD);

extern CONST void (* CONST wai_evt_vec)(UWORD);
extern CONST void (* CONST det_evt_vec)(UWORD);
extern CONST void (* CONST idet_evt_vec)(UWORD);

/****************************/
/*  タスク管理  関連        */
/****************************/
#define cre_tsk			(*cre_tsk_vec)
#define del_tsk			(*del_tsk_vec)
#define exi_tsk			(*exi_tsk_vec)
#define wai_tsk			(*wai_tsk_vec)
#define wai_oneshot		(*wai_oneshot_vec)
#define wup_tsk			(*wup_tsk_vec)
/*****************************/
/*  セマフォ管理  関連       */
/*****************************/
#define cre_sem			(*cre_sem_vec)
#define del_sem			(*del_sem_vec)
#define sig_sem			(*sig_sem_vec)
#define wai_sem			(*wai_sem_vec)
#define chk_sem			(*chk_sem_vec)
#define chk_semvl		chk_semvl_erom
/*******************************/
/*  メールボックス管理  関連   */
/*******************************/
#define cre_mbx			(*cre_mbx_vec)
#define del_mbx			(*del_mbx_vec)
#define snd_msg			(*snd_msg_vec)
#define rcv_msg			(*rcv_msg_vec)
#define chk_mbx			(*chk_mbx_vec)
#define chk_rcv			(*chk_rcv_vec)
/******************************/
/*  イベントフラグ管理  関連  */
/******************************/
#define wai_evt			(*wai_evt_vec)
#define det_evt			(*det_evt_vec)
#define idet_evt		(*idet_evt_vec)

/******************************/
/*  リセット処理              */
/******************************/
void SaveReturnAddressAndJumpBegin(void);
void TraceTaskAddress(void);
void RestartSystem(void);

#endif
