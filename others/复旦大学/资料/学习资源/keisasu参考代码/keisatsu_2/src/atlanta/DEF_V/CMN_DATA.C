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
struct Timer10msQueueData_t Timer10msQueue[TIMER_MULTI10MS_MAX] = {0};

/***********************************************************************
*          BY:   T.Nose
*        DATE:   1997/10/06
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   マルチタイマーキューの先頭タイマーＩＤ
************************************************************************/
UBYTE CMN_TopTimerQueue = 0;

/***********************************************************************
*          BY:   T.Nose
*        DATE:   1997/10/06
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   マルチタイマータスクのタスクＩＤ
************************************************************************/
UWORD tskno_CMN_MultiTimer10msTask = 0;

/***********************************************************************
*          BY:   T.Nose
*        DATE:   1997/11/26
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   マルチタイマータスクのタイムアップメッセージ
************************************************************************/
MESSAGE_t CMN_ReturnMessage[TIMER_MULTI10MS_MAX] = {0};

UBYTE DEBUG_MultiTimer10msExecqueu = 0;

/* 実機でＦＣＯＤＥ送信をしようとするとリセットがかかる件 */
UDWORD DEBUG_SaveAddressBuffer[TIMER_MULTI10MS_MAX] = {0};
