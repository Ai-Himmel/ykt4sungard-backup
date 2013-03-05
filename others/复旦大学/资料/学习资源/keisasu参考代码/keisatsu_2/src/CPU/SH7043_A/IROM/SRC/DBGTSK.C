/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : dbgtsk.c                                                 */
/*  作成者       : 野瀬                                                     */
/*  日  付       : 1997/04/17                                               */
/*  概  要       : モニターのデバッグ用擬似タスク、関数群                   */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\message.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_sem.h"
#else
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\sh7043\ext_v\extv_sem.h"
#endif

static	UWORD tskno_NCU_Task = 0xFFFF;
static	UWORD tskno_OPR_KeyTask = 0xFFFF;
static	UWORD tskno_CMN_BuzzerTask = 0xFFFF;
static	UWORD tskno_MAN_DocumentInTask = 0xFFFF;
static	UWORD tskno_PRN_CheckTonerTask = 0xFFFF;

void MAN_IdleTask(void) /* 250,1 */
{
	cre_sem(&semno.rtc);
	cre_sem(&semno.lcd);
	cre_sem(&semno.prn_serial);

	cre_tsk(&tskno_NCU_Task,TSK_NCU_TASK,0);
	del_tsk(&tskno_NCU_Task);

	while (1) ;
	cre_tsk(&tskno_OPR_KeyTask,TSK_OPR_KEYTASK,0);
	cre_tsk(&tskno_CMN_BuzzerTask,TSK_CMN_BUZZERTASK,0);
	cre_tsk(&tskno_MAN_DocumentInTask,TSK_MAN_DOCUMENTINTASK,0);
	cre_tsk(&tskno_PRN_CheckTonerTask,TSK_PRN_CHECKTONERTASK,0);
}

void NCU_Task(void) /* 230,1 */
{
	wai_oneshot(100);
}

void OPR_KeyTask(void) /* 220,1 */
{
	wai_tsk(0xffff);
}

void CMN_BuzzerTask(void) /* 210,1 */
{
	wai_tsk(0xffff);
}

void MAN_DocumentInTask(void) /* 200,1 */
{
	del_tsk(&tskno_CMN_BuzzerTask);
	wai_tsk(0xffff);
}

void PRN_CheckTonerTask(void) /* 190,1 */
{
	wai_tsk(0xffff);
}
