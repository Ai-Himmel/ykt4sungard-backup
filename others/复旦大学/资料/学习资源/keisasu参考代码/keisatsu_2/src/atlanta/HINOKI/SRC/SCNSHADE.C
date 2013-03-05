/*
 *	@(#)%W%
 *	FileName:	/mnt/jason/home2/prj/Eva/Src/scn/scnshade.c
 *	Create:	Tue Feb 17 15:20:49 1998	by	ishiyama
 *	Description:
 *		Get and Save Shading Data
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"

#define SAMPLE_LINE_COUNT	600

/*
 *	Name:	Get and Save Shading Data
 *	Create:	Tue Feb 17 15:21:26 1998	by	ishiyama
 *	Synopsis:
 *		#inlcude	"scanner.h"
 *		void	GetShadeTask(void);
 *	Description:
 *		シェーディングデータを取り込む
 *		原稿は、待機位置にあることが前提。
 *		排出も、Scanner Main Task で行う。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	GetShadeTask(void)
{
	MESSAGE_t	TxMsg;						/* 送信メッセージ用エリア */
	UBYTE	*ScanBufPtr;
	WORD	SamplePosition;				/* Shading Data をサンプルするライン数 */
	BOOL	LoopFlag;					/* 1Page 読取り処理継続 TRUE:継続,FALSE:中断 */
	BOOL	WaitFlag;					/* 原稿搬送 or 読取り待ち */
	
	tskno_SCN_DocOutTask = 0xffff;
	ScannerMode = SCANNER_DOC_SCAN_MODE;

	OpenScanner();						/* 読取りのための初期設定 */

	SYS_StampFlag = 0;					/* 済みスタンプ未実行 */
	EnablePushStampEvent = FALSE;		/* 済みスタンプ押下イベント許可フラグ初期化 */

	/* 先頭ページの読取り開始時に原稿が抜かれていた場合は繰込み不良で終了する */
	if (!QueryDs1On()) {
		TxMsg.Message = MSG_SCN_SHADE_NO_DOCUMENT;
	} else {
		/* Document の属性を設定 */
		SaveScanningMode(SYS_FINE);	/* Mode 設定 */
		SetScanPageAttribute(CurrentPage);
		CurrentPage->Density = SYS_NORMAL_DENSITY;

		SCN_Open();				/* 読取り開始 */

		InzScanPageMem();
		SamplePosition = 0;
		LoopFlag = TRUE;
		while (LoopFlag) {
			WaitFlag = TRUE;			/* Default */
			if (!QueryCloseInterLock4Scan()) {
				TxMsg.Message = MSG_SCN_SHADE_COVER_OPEN;
				LoopFlag = FALSE;
#if (0)
			} else if (CheckStopSw4Scan()) {
				TxMsg.Message = MSG_SCN_SHADE_STOPSW_ON;
				LoopFlag = FALSE;
#endif
			} else {
				switch (QueryDocPosition()) {
				case DOC_POS_NO_DOCUMENT:
					break;
				case DOC_POS_MOVE_TO_DS2:
					if (CurrentPage->StepsFromDs1On > MoveToDs2ErrorSteps) {
						/* 繰込み不良 */
						TxMsg.Message = MSG_SCN_SHADE_DOC_ERROR;
						LoopFlag = FALSE;
					}
					break;
				case DOC_POS_MOVE_TO_READY:
					break;
				case DOC_POS_SCANNING:
					if (EnableToReadScanBuf()) {
						if (EnableToWriteScanPageMem()) {
							/* Scanner Buffer から Page Memory に一応転送 */
							ScanBufPtr = GetLineAddress4ReadScanBuf();
							PutLineScanPageMem(ScanBufPtr);
							DecScanBufReadableLine();
							if (++SamplePosition > SAMPLE_LINE_COUNT) {
								CloseScanPage(); /* 割り込みでの読取り停止 */
								PauseTxMotor();	/* 原稿停止 */
								MakeShadingData();
								TxMsg.Message = MSG_SCN_SHADE_OK;
								LoopFlag = FALSE;
							}
							WaitFlag = FALSE;
						}
					}
					WaitFlag = FALSE;
					break;
				case DOC_POS_SCAN_FEEDOUT:
				case DOC_POS_MOVE_TO_PUSH_STAMP:
				case DOC_POS_FEED_OUT:
				default:
					break;
				}
			}
			if (WaitFlag) {
				wai_tsk(1);
			}
		} /* while end */
		
		CloseScanPage();			/* 読取り終了(Motor 停止含む) */
	}
	
/*
** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
** 1999/02/01 by T.Soneoka
*/
#if (0)
**	if (SCN_Close((UBYTE)0) != SCN_DOC_EXIT_OK) {
#else
	if (SCN_Close((UBYTE)FROM_DOCSTORE) != SCN_DOC_EXIT_OK) {
#endif
		TxMsg.Message = MSG_SCN_SHADE_DOC_ERROR;
	}
	
	TxMsg.Item = FROM_SCN_GETSHADE;
	snd_msg(mbxno.MAN_Task, &TxMsg );
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk(0xffff);
}
