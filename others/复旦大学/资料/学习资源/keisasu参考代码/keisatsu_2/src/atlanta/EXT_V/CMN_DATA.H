#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\message.h"

/***********************************************************************
*          BY:   T.Nose
*        DATE:   1996/11/19
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   複数のタイマーを管理するキューテーブル
************************************************************************/
extern struct Timer10msQueueData_t Timer10msQueue[TIMER_MULTI10MS_MAX];

/***********************************************************************
*          BY:   T.Nose
*        DATE:   1997/10/06
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   マルチタイマーキューの先頭タイマーＩＤ
************************************************************************/
extern UBYTE CMN_TopTimerQueue;

/***********************************************************************
*          BY:   T.Nose
*        DATE:   1997/10/06
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   マルチタイマータスクのタスクＩＤ
************************************************************************/
extern UWORD tskno_CMN_MultiTimer10msTask;

/***********************************************************************
*          BY:   T.Nose
*        DATE:   1997/11/26
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   マルチタイマータスクのタイムアップメッセージ
************************************************************************/
extern MESSAGE_t CMN_ReturnMessage[TIMER_MULTI10MS_MAX];

extern UBYTE DEBUG_MultiTimer10msExecqueu;

/* 実機でＦＣＯＤＥ送信をしようとするとリセットがかかる件 */
extern UDWORD DEBUG_SaveAddressBuffer[TIMER_MULTI10MS_MAX];
