/*
 *	@(#)$Id: PRT_DIRC.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/prt/prt_dirc.c
 *	Create:	Tue Apr  7 15:34:55 1998	by	ishiyama
 *	Description:
 *		Make Print Image Direct Task
 *	Change Log:
 *		
 */

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\memfile.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\define\scn_def.h"
#include "\src\atlanta\satsuki2\ext_v\page_mem.h"
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\page_mem.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
 #endif

#if (0)	/* For Debug By O.Kimoto 1998/10/22 */
** /*
**  *	Name:	Make Image Direct
**  *	Create:	Tue Apr  7 15:35:38 1998	by	ishiyama
**  *	Synopsis:
**  *		#include	"prt_task.h"
**  *		void	MakeImageDirectTask(void);
**  *	Description:
**  *		ページメモリのイメージをそのままプリンタへ送れるようにする。
**  *		リアルタイムコピーのイメージ
**  *	Notes:
**  *		Use Test Only
**  *	Return Value:
**  *		void
**  *	Change Log:
**  *		
**  */
** void	MakeImageDirectTask(void)
** {
** 	MESSAGE_t	TxMsg;
** 	struct PrintDmacQElement	Area;	/* Image Area */
** 	BYTE	MemHandle;					/* Page Memory Block Handle */
** 
** 	TxMsg.Item = FROM_MAKEIMAGE_DECODE_TASK;
** 
** 	/* プリンタが仕事を終わるまで待つ */
** 	WaitPrintWork();
** 
** 	/* Print Page Queue Element Set */
** 	SetDefaultPageQElements4Image();
** 
** 	for (;;) {
** 		/* プリンタが仕事を終わるまでまで待つ */
** 		WaitPrintWork();
** 		/* 記録紙の属性初期化 */
** 		SetPaperAttribute();
** 
** 		/* Print Page Queue に登録 */
** 		PageQ.Handle = MemHandle;
** 		PageQ.Count = (PageQ.Lines * (SYS_A4_LINE / 16));
** 
** 		/* Image 作成開始を Make Image Task に通知 */
** 		TxMsg.Message = MSGL_START_MAKEIMAGE;
** 		snd_msg(mbxno.PRN_MakeImageTask, &TxMsg);
** 
** 		wai_tsk(100);					/* この間に Scaner 側で IsPrintFinish フラグをセットする */
** 		do {
** 			/* Real Time Copy ならScan/Print 中 */
** 			if (PrinterError != 0 || PrinterStopProcess) {
** 				/* Error またはストップならば抜ける */
** 				break;
** 			}
** 			wai_tsk(1);
** 		} while (!IsPrintFinish);
** 		CloseImage4Print();
** 			
** 		TxMsg.Message = MSGL_DEQUEUE_INDEX;
** 		break;						/* マージンより残りが少ないと終了 */
** 	} /* for end */
** 	snd_msg(mbxno.PRN_MakeImageTask, &TxMsg); /* Decode 終了またはメモリオープンエラーを親タスクに通知 */
** 
** 	wai_tsk(0xffff);						/* タスク終了 */
** }
#endif


/*
 *	Name:	Set Default Page Queue Elements for Image
 *	Create:	Fri Jul 03 15:21:19 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetDefaultPageQElements4Image(void)
 *	Description:
 *		Image の情報に応じて、Print Queue の要素をデフォルト値で埋める
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetDefaultPageQElements4Image(void)
{
	if (PrinterUseMode == PRINT_SCOPY) {
		/* MEM_REALTIME_COPY_FILE */
		PageQ.Mode = RealTimeCopyFile.Mode;
		PageQ.Lines = 1;
/*		PageQ.Count = (PageQ.Lines * (SYS_A4_LINE / 16));	未使用なので消去します  1998/10/31 by T.Soneoka */
		/* PageQ.Copy = TRUE; */
		PageQ.Start = (UWORD *)&ScanPageMem[0][0];

		/* 1998/10/10 by T.Soneoka */
		if (PB4()) {
			PageQ.Size = SYS_B4_PAPER;
		} else {
			PageQ.Size = SYS_A4_PAPER;
		}

		RealTimeCopyFile.Reduction = 100;
		switch(RealTimeCopyFile.Size) {
		case SYS_DOCUMENT_B4_SIZE:
			if (PageQ.Size == SYS_A4_PAPER) {
				RealTimeCopyFile.Reduction = 84;
			}
			break;
		case SYS_DOCUMENT_A4_SIZE:
		default:
			break;
		}
		PageQ.Reduction = RealTimeCopyFile.Reduction;
	}
	else if (PrinterUseMode == PRINT_RXPRINT) { /* PRINT_RXPRINT added by H.Hirao 1998/11/07 */
		PageQ.Mode = SYS_DocBlock.Src.Mode;

		if (PB4()) {
			PageQ.Size = SYS_B4_PAPER;
		} else {
			PageQ.Size = SYS_A4_PAPER;
		}
		
		switch(SYS_DocBlock.Src.Size) {
		case SYS_DOCUMENT_B4_SIZE:
			if (PageQ.Size == SYS_A4_PAPER) {
				PageQ.Reduction = 84;
			}
			break;
		case SYS_DOCUMENT_A4_SIZE:
		default:
			break;
		}
	}
	else {
		PageQ.Mode = RealTimeCopyFile.Mode;
		PageQ.Lines = 1;
/*		PageQ.Count = (PageQ.Lines * (SYS_A4_LINE / 16));	未使用なので消去します  1998/10/31 by T.Soneoka */
		/* PageQ.Copy = TRUE; */
		PageQ.Start = (UWORD *)&ScanPageMem[0][0];

		RealTimeCopyFile.Reduction = 100;
		switch(RealTimeCopyFile.Size) {
		case SYS_DOCUMENT_B4_SIZE:
			if (PageQ.Size == SYS_A4_PAPER) {
				RealTimeCopyFile.Reduction = 84;
			}
			break;
		case SYS_DOCUMENT_A4_SIZE:
		default:
			break;
		}
		PageQ.Reduction = RealTimeCopyFile.Reduction;
	}
}


/*
 *	Name:	Close Image for Print
 *	Create:	Fri Jul 03 20:23:00 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	CloseImage4Print(void);
 *	Description:
 *		デコードの終了処理
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	CloseImage4Print(void)
{
#if (0)/* 暫定 1998/10/05 by T.Soneoka */
**	/* 最終ラインを全白でクリア */
**	(void)MemoryCopy((UBYTE *)QueryImageStartPointer(), (UBYTE *)*DummyImage, (UWORD)SYS_A4_LINE/8);
#endif
	IncPrtImageReadableLine();
}
