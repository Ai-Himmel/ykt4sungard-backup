/*
 *	@(#)$Id: PRTMKIMG.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/prt/prtmkimg.c
 *	Create:	Fri Apr  3 19:08:04 1998	by	ishiyama
 *	Description:
 *		Printer Make Image Task
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"


#if (0) /* For Debug  By O.Kimoto 1998/10/22 */
** /*
**  *	Name:	Make Image Task
**  *	Create:	Fri Apr  3 19:10:01 1998	by	ishiyama
**  *	Synopsis:
**  *		#include	"prt_task.h"
**  *		void	MakeImageTask(void);
**  *	Description:
**  *		Print Index Queue を読んで、イメージを作成するタスク(常駐タスク)
**  *		Page Printer の場合は、Page Memory に。
**  *		Thermal Head Printer の場合は、Image Buffer に作成し,
**  *		Thermal Head への DMA 起動まで行う。
**  *		ページ合成のときは、Index Queue に二つ貯まってからイメージを作成する
**  *	Notes:
**  *		TxMessages:
**  *			MSGL_DEQUEUE_INDEX				// Index Queue に空きができた
**  *			MSGL_START_MAKEIMAGE				// Image 作成開始を通知
**  *	Return Value:
**  *		void
**  *	Change Log:
**  *		
**  */
** void	MakeImageTask(void)
** {
** 	MESSAGE_t	*RxMsg;
** 	MESSAGE_t	TxMsg;
** 	
** 	tskno_PRN_MakeImageDirect = 0xffff;
** 
** 	TxMsg.Item = FROM_MAKEIMAGE_TASK;
** 	for (;;) {
** 		rcv_msg(mbxno.PRN_MakeImageTask, &RxMsg);
** 
** 		switch (RxMsg->Message) {
** 		case MSGL_INDEX_QUEUE_ACK:		/* Index Queue に追加された */
** 			if(tskno_PRN_MakeImageDirect == 0xffff) {
** 				cre_tsk(&tskno_PRN_MakeImageDirect, TSK_PRN_MAKEIMAGEDIRECTTASK, (void *)0);
** 			}
** 			break;
** 
** 		case MSGL_DELETE_QUEUE:			/* Image 作成を中断 */
** 			if (tskno_PRN_MakeImageDirect != 0xffff) {
** 				del_tsk(&tskno_PRN_MakeImageDirect);
** 			}
** 
** #if (0)	/* For Debug By O.Kimoto 1998/10/22 */
** ** 			/* Print main Task に Image 作成中断を通知 */
** ** 			TxMsg.Message = MSGL_DELETE_QUEUE;
** ** 			snd_msg(mbxno.PRN_PrinterTask, &TxMsg);
** #endif
** 			break;
** 
** 		case MSGL_DEQUEUE_INDEX:		/* プリントイメージできた from 子タスク */
** 			if (tskno_PRN_MakeImageDirect != 0xffff) {
** 				del_tsk(&tskno_PRN_MakeImageDirect);
** 			}
** 
** 			/* Image 作成終了と Index Queue に空きができた旨通知 */
** 			TxMsg.Message = MSGL_DEQUEUE_INDEX;
** 			snd_msg(mbxno.PRN_PrinterTask, &TxMsg);
** 			break;
** 
** 		case MSGL_START_MAKEIMAGE:		/* Image 作成開始 from 子タスク */
**  			/* Image 作成開始を Printer Main に通知 */
** 			TxMsg.Message = MSGL_START_MAKEIMAGE;
** 			snd_msg(mbxno.PRN_PrinterTask, &TxMsg);
** 			break;
** 
** 		default:
** 			break;
** 		}
** 
** 	} /* for end */
** }
** 
** 
** /*
**  *	Name:	Exit Make Image Task
**  *	Create:	Fri Apr  3 18:21:21 1998	by	ishiyama
**  *	Synopsis:
**  *		#include	"prt_task.h"
**  *		void	ExitMakeImageTask(void);
**  *	Description:
**  *		Make Image Task 終了関数
**  *		Make Image Task を常駐タスクとするときは、
**  *		コールされない
**  *	Return Value:
**  *		void
**  *	Change Log:
**  *		
**  */
** void	ExitMakeImageTask(void)
** {
** 	if (tskno_PRN_MakeImageDirect != 0xffff) {
** 		del_tsk(&tskno_PRN_MakeImageDirect);
** 	}
** 	exi_tsk();
** }
#endif
