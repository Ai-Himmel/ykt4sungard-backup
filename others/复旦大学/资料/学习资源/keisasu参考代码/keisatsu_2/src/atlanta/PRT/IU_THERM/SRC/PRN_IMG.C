/*******************************************************************
*	System		: SAKAKI
*	File Name	: PRN_IMG.C
*	Author		: K.Kawata
*	Date		: 1998/6/9
*	Description	:
*	Maintenance	:
*			: Original:\src\kobe\anzu\src\prn_main.c or
*			: Original:\src\kobe\anzu\src\prn_img.c
*			1999/01/29 thermal/prn_img.cよりFeedBack
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
********************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysprint.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\lst_pro.h"
#include "\src\atlanta\define\mntsw_a.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mnt_sw.h"
#include "\src\atlanta\define\syscomf.h"

#include "\src\atlanta\ext_v\scn_tbl.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\ext_v\sys_data.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"

#if (0)
** /* SAKAKI */
** #include "\src\atlanta\prt\thermal\define\prn_pro.h"
** #include "\src\atlanta\prt\thermal\define\prn_def.h"
** #include "\src\atlanta\prt\thermal\define\prn_msg.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_tbl.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_tbl.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
** #include "\src\atlanta\sakaki\define\sakiport.h"
** #include "\src\atlanta\sakaki\ext_v\ga_data.h"
#else
/* HINOKI */
 #if (0)
 #if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#include "\src\atlanta\hinoki\ext_v\scdc_dat.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
 #else
  #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\satsuki2\ext_v\scdc_dat.h"
#include "\src\atlanta\satsuki2\ext_v\ga_buf.h"
  #else
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
#include "\src\atlanta\hinoki\ext_v\scdc_dat.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
  #endif
 #endif
 #else

  #if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
  #endif
  #if (PRO_MODEM == R288F)
    #if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
      #include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
    #else
      #include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
    #endif
  #endif

  #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scdc_dat.h"
#include "\src\atlanta\satsuki2\ext_v\ga_buf.h"
  #else
#include "\src\atlanta\hinoki\ext_v\scdc_dat.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
  #endif

 #endif

#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"

#include "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"

#include "\src\cpu\sh7043_a\irom\define\def_semn.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_sem.h"
#endif

#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"

#if (PRO_CPU_VERSION == SH7043_A)
	#include "\src\cpu\sh7043_a\scd\define\scd.h"
#else
	#include "\src\atlanta\scd\define\scd.h"
#endif
#include "\src\atlanta\ext_v\sys_port.h"
#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"
#include "\src\atlanta\ext_v\dma_data.h"


#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
#include "\src\atlanta\define\cl1_def.h"	/* added by H.Hirao 1999/03/04 */
#include "\src\atlanta\ext_v\cl1_data.h"	/* added by H.Hirao 1999/03/04 */
#endif

UWORD PRN_FontImageBuffer[16][80] = {0};	/*[0]=CharaterPrint [1]=CharacterTx*/
UWORD *PRN_FontImageBufferAddress = 0;

extern CONST UBYTE SCDC_SWITCHING_TEST;	/* For Debug SoftCodec Switch Test by O.Kimoto 1998/12/16 */


WORD	ListOpen(void)
{
#if (0)
** 	/* SAKAKI */
** 	UWORD	i, j;
** 
** 	PRN_PrinterOpen();
** 	ImageLineStartPoint = 16;/******16******/
** 	for (i = 0; i < PRINT_IMAGE_BUF_LINE; i++) {
** 		for (j = 0; j < PRINT_IMAGE_BUF_SIZE; j++) {
** 			PRN_ImageBuffer1[i][j] = 0xff;
** 		}
** 	}
** 	PRN_StandbyToPrint();
** 	while ((PRN_Control.Command == PRN_PAGECUT_REQ) || (PRN_Control.Command == PRN_FEED_IN_REQ)) {	/* 記録紙カット引き戻しの終了を待つ */
** 		wai_tsk(2);
** 	}
** 	PageStartLineB4WhiteLineSet();
** 	PRN_Control.PrintMode = SYS_NORMAL;
** 	SetPrintModeParameterEveryPage();
** 	PRN_Control.PrintSize = SYS_DOCUMENT_A4_SIZE;
** 	PRN_Control.PaperSize = SYS_A4_PAPER;
** 	SetPrintSizeParameterEveryPage();
** 	/*１ページ開始*/
** 	PRN_OnePageStart();
** 	if (PRN_PrintHaltRequest() == NG) {
** 		ListClose();
** 	}
** 	return(OK);
#else
	/* HINOKI */
	UWORD	i, j;

	PrinterUseMode = PRINT_LIST;	/* Add by O.Kimoto 1998/11/06 */
	PRN_FontImageBufferAddress = &PRN_FontImageBuffer[0][0];	/* Add by O.Kimoto 1998/11/07 */

	InzPrinterParameter();				/* プリンタ関係大域変数初期化 *//* HINOKI */
	PRN_PrinterOpen();

	/* 記録紙の属性初期化 */
	SetPaperAttribute();

	for (i = 0; i < PRINT_IMAGE_BUF_LINE; i++) {
		for (j = 0; j < PRINT_IMAGE_BUF_SIZE; j++) {
			PRN_ImageBuffer1[i][j] = 0x00;	/* このまま By O.Kimoto 1998/11/10 */
		}
	}
	PRN_StandbyToPrint();

/*
** リストの停止処理はしません
** 1999/02/19 by T.Soneoka
*/

#if (0)
**	/*
**	** ＤＵＡＬ制限変更のため
**	** スキャナ制限からプリント制限へ変更する
**	** 1999/02/18 by T.Soneoka
**	*/
**	if (!CHK_UNI_NoTripleRestrict()) {
**		if (QueryResourceCount() >= 3) {	/* COMM,SCAN,PRINTのトリプル時 */
**			while (1) {
**				wai_tsk(10);
**				if (QueryResourceCount() < 3) {
**					break;
**				}
**				if (QueryPrinterCoverOpen()) {
**					PrinterError |= PRT_ERROR_COVER_OPEN;
**				}
**				if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
**					break;
**				}
**			}
**		}
**	}
#endif
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
	while (1) {
		if (QueryPrinterCoverOpen()) {
			PrinterError |= PRT_ERROR_COVER_OPEN;
		}
		if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
			CMN_DisableInterrupt();
			CL1_DualRestrictionStatus &= ~CL1_PRINTER_IN_USE; /* プリント中リセット */
			CMN_EnableInterrupt();
			break;
		}
		CMN_DisableInterrupt();
		/* CL1_RestrictionStatusResetTimer added by H.Hirao 1999/05/12 */
		if ((CL1_DualRestrictionStatus & CL1_CLASS1_IN_USE) || SYS_CalledRequestForDocStore || CL1_RestrictionStatusResetTimer) { /* Class1受信中 または ＣＩ検出 */
			CL1_DualRestrictionStatus &= ~CL1_PRINTER_IN_USE; /* プリント中リセット */
			wai_tsk(100);
		}
		else {
			CL1_DualRestrictionStatus |= CL1_PRINTER_IN_USE; /* プリント中セット */
			CMN_EnableInterrupt();
			break;
		}
	}
#endif

	PageStartLineB4WhiteLineSet();
	PageQ.Mode = SYS_FINE;
	SetPrintModeParameterEveryPage();
	PageQ.Size = SYS_DOCUMENT_A4_SIZE;
	SetPrintSizeParameterEveryPage();
	/* CutToPrintExecFlag = NO; */	/* Add BY O.Kimoto 1998/12/01 */

	StartPagePrint();

	/*１ページ開始*/
	PRN_OnePageStart();

#if (0)
** 	/* 不要です。 By O.Kimoto 1999/01/29 */
** 	if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 		ListClose();
** 	}
#endif

	return(OK);
#endif
}

WORD	TestPaternPrintOpen(void)
{
#if (0)
** 	/* SAKAKI */
** 	UWORD	i;
** 
** 	PRN_PrinterOpen();
** 	ImageLineStartPoint = 0;
** 	/*ページ単位での設定*/
** 	PRN_StandbyToPrint();
** 	while ((PRN_Control.Command == PRN_PAGECUT_REQ) || (PRN_Control.Command == PRN_FEED_IN_REQ)) {	/* 記録紙カット引き戻しの終了を待つ */
** 		wai_tsk(2);
** 	}
** 	PageStartLineB4WhiteLineSet();
** 	PRN_Control.PrintMode = SYS_NORMAL;
** 	SetPrintModeParameterEveryPage();
** 	PRN_Control.PaperSize = PRN_GetPaperSize();
** 	if (PRN_Control.PaperSize == SYS_B4_PAPER) {
** 		PRN_Control.PrintSize = SYS_DOCUMENT_B4_SIZE;
** 	}
** 	else {
** 		PRN_Control.PrintSize = SYS_DOCUMENT_A4_SIZE;
** 	}
** 	SetPrintSizeParameterEveryPage();
** 	/*１ページ開始*/
** 	PRN_OnePageStart();
** 	return(OK);
#else
	/* HINOKI */
	UWORD	i,j;

	PrinterUseMode = PRINT_IMAGE;
	InzPrinterParameter();				/* プリンタ関係大域変数初期化 *//* HINOKI */
	PRN_PrinterOpen();

	/* 記録紙の属性初期化 */
	SetPaperAttribute();

	for (i = 0; i < PRINT_IMAGE_BUF_LINE; i++) {
		for (j = 0; j < PRINT_IMAGE_BUF_SIZE; j++) {
			PRN_ImageBuffer1[i][j] = 0x00;	/* このまま By O.Kimoto 1998/11/10 */
		}
	}
	/*ページ単位での設定*/
	PRN_StandbyToPrint();
	PageStartLineB4WhiteLineSet();
	PageQ.Mode = SYS_FINE;
	SetPrintModeParameterEveryPage();
	if (Paper.Size == SYS_B4_PAPER) {
		PageQ.Size = SYS_DOCUMENT_B4_SIZE;
	}
	else {
		PageQ.Size = SYS_DOCUMENT_A4_SIZE;
	}

	SetPrintSizeParameterEveryPage();

	if (StartPagePrint() == FALSE) {
		return(NG);
	}
	else {
		/*１ページ開始*/
		PRN_OnePageStart();
		return(OK);
	}

#endif
}

WORD	ListImagePrint(void)
{
#if (0)
** 	/* SAKAKI */
** 	UWORD	i, j;
** 
** 	if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 		return(NG);
** 	}
** 	for (j = 0; j < 2; j++) {
** 		for (;;) {
** 			if (!CheckLineWritePoint()) {
** 				CMN_DisableInterrupt();
** 				DecodeWaitFlag = TRUE;
** 				wai_evt(EVT_PRINT_HEAT_1LINE_END);
** 				continue;
** 			}
** 			for (i = 0; i < PRINT_IMAGE_BUF_SIZE; i++) {
** 				PRN_ImageBuffer1[ImageLineWritePoint][i] = List.Image[i];
** 			}
** 			RenewLineWritePoint();
** 			break;
** 		}
** 	}
** 	for (;;) {
** 		if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
** 			return(NG);
** 		}
** 		if (PRN_OverHeatCheck() == TRUE) {
** 			if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
** 				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
** 				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 			}
** 			wai_tsk(2);
** 			continue;
** 		}
** 		else {
** 			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
** 				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_HIGH_TEMP;
** 				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 			}
** 			HeatPulseEnable();
** 			break;
** 		}
** 	}
** 	return(OK);
#else
	/* HINOKI */
	UWORD	i, j;

	/* ＳＡＫＡＫＩはここで２回ループしていましたが、ＨＩＮＯＫＩは不必要なので、削除しています。 by O.Kimoto 1998/11/17 */
	for (;;) {
		if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
			PrinterStopProcess  = TRUE;
			break;
		}
		if (!EnableToWritePrtImageBuf()) {
			CMN_DisableInterrupt();
			DecodeWaitFlag = TRUE;
			wai_evt(EVT_PRINT_HEAT_1LINE_END);
			continue;
		}
#if defined(KEISATSU) /* A4セット時リストプリントはマスクはA4でかかっているがB4エリアまで印加していた。ID51 O.Oshima 2005/12/02 */
		for (i = 0; i < (PRINT_IMAGE_BUF_SIZE-PRN_ImageBufferOffSet); i++) {
#else
		for (i = 0; i < PRINT_IMAGE_BUF_SIZE; i++) {
#endif
#if (0)
** 				/* PRN_ImageBuffer1のOffSetを入れます。 By O.Kimoto 1998/11/10 */
** 				PRN_ImageBuffer1[(UWORD)GetPrtImageBufWriteLineNo()][i] = List.Image[i];
#else
			PRN_ImageBuffer1[(UWORD)GetPrtImageBufWriteLineNo()][i+PRN_ImageBufferOffSet] = List.Image[i];
#endif
		}
		(void)QueryImageStartPointer();
		(void)PrintLine();
		break;
	}
	for (;;) {
		if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);

#if (0)
** 			/* ストップキーが押されたときの戻り値が上位関数と一致していない
** 			** by O.Kimoto 1999/01/29
** 			*/
** 			return(NG);
#else
			if (PRN_PrintHaltRequest() == NG) {
				return(MSG_PRN_LST_STOPSW_ON);
			}
			else {
				return(NG);
			}
#endif

		}

#if defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)
		/* HINOKI2は印字中のオーバーヒートはチェックしない By O.Kimoto 2002/02/25 */
		break;
#else
		if (PRN_OverHeatCheck() == TRUE) {
			if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
			}
			wai_tsk(2);
			continue;
		}
		else {
			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_HIGH_TEMP;
				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
			}
			break;
		}
#endif
	}
	return(OK);
#endif
}

WORD	ListClose(void)
{
#if (0)
** 	/* SAKAKI */
** 	WaitAllImageLinePrint();
** 	PRN_LineMemoryStatus = 0;
** 	DmaDisable();
** 	if ((CutToPrintExecFlag == NO) && (PRN_PrintNocutRequest() == OK)) {
** 		PRN_CutToPrint();
** 	}
** 	GaInterruptFlag &= (~INT_PRINTER);
** 	GaInterruptDisable();
** 	PRN_PrintToStandby();
** 	PRN_Control.Command = PRN_IDLE_REQ;
** 	PRN_Control.Status = PRN_IDLE;
** 	GaInterruptFlag &= (~INT_PRINTER);
** 	GaInterruptDisable();
** 	PmenOff();	/* ＲＸモーター励磁ＯＦＦ */
** 	HeatPulseDisable();
** 	return(OK);
#else
	/* HINOKI */
	WaitAllImageLinePrint();
	/*
	** １ページ終了状態で次ページに入らないようにする
	** 1999/02/23 by T.Soneoka
	*/
	PrinterDmaPermission = FALSE;
	DtcPermission = FALSE;

#if (0)
** 	/* プリンターエラーをチェックする関数が同一内容で関数名違いが２つも在るので、
** 	** １つに統一します。
** 	** by O.Kimoto 1998/12/07
** 	*/
** 	if ((CutToPrintExecFlag == NO) && (PRN_PrintNocutRequest() == OK)) {
** 		PRN_CutToPrint();
** 		PRN_PrintToStandby();
** 	}
#else
	if ((CutToPrintExecFlag == YES /* NO */) && (PRN_PrintErrorHaltRequest() == OK)) {
		if (PRN_CutToPrint() == NG) {
			return(NG);
		}


#if defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)
		/* HINOKI2は印字中のオーバーヒートはチェックしない By O.Kimoto 2002/02/25 */
		if (PRN_OverHeatCheck() == TRUE) {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
			PRN_CutPosToStandbyPos();
			return(NG);
		}
#endif

/*
** 紙搬送変更 1999/04/13 by T.Soneoka
*/
#if (0)
**		PRN_PrintToStandby();
#else
		/*
		** 紙搬送変更 1999/04/13 by T.Soneoka
		*/
		if (PRN_PrintErrorHaltRequest() == OK) {
#if defined(SATSUKI2)		/* 壁掛け設定用by Y.Kano 2003/10/16 */
			if (!CHK_WallHangSetting()) { /** 壁掛け設定用 */	/* Add by Y.kano 2003/10/16 */
				PRN_CutPosToStandbyPos();
			}
#else	/* SATSUKI2以外 */
			PRN_CutPosToStandbyPos();
#endif	/* End of defined(SATSUKI2) */
		}
#endif
		/* EndMark4
		** エンドマークのチェックが抜けていた。
		** by O.Kimoto 1999/03/04
		*/
		if (EndMarkDetect == TRUE) {

#if (0)
** 			/* エンドマーク検出とＪＡＭの区別ができないので、エラーメッセージ変更
** 			** by O.Kimoto 1999/03/09
** 			*/
** 			PrinterError |= PRT_ERROR_NO_PAPER;
** 			SYS_MachineStatus[SYS_PRINTER_STATUS1] |=SYS_PRINTER_NO_PAPER; /* マシーンステータスもあわせてセットします。 by O.Kimoto 1999/02/24 */
#else
			PrinterError |= PRT_ERROR_JAM;
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
#endif

			return(NG);
		}
	}
#endif
	return(OK);
#endif
}

void	PRN_List1PageClose(void)
{
#if (0)
** 	/* SAKAKI */
** 	WaitAllImageLinePrint();
** 	PRN_LineMemoryStatus = 0;
** 	ImageLineStartPoint = 0;
** 	DmaDisable();
** 	if ((CutToPrintExecFlag == NO) && (PRN_PrintNocutRequest() == OK)) {
** 		PRN_CutToPrint();
** 	}
#else
	/* HINOKI */
	WaitAllImageLinePrint();
	/*
	** １ページ終了状態で次ページに入らないようにする
	** 1999/02/23 by T.Soneoka
	*/
	PrinterDmaPermission = FALSE;
	DtcPermission = FALSE;


#if (0)
** 	/* プリンターエラーをチェックする関数が同一内容で関数名違いが２つも在るので、
** 	** １つに統一します。
** 	** by O.Kimoto 1998/12/07
** 	*/
** 	if ((CutToPrintExecFlag == NO) && (PRN_PrintNocutRequest() == OK)) {
** 		PRN_CutToPrint();
** 	}
#else
	if ((CutToPrintExecFlag == YES /* NO */) && (PRN_PrintErrorHaltRequest() == OK)) {
		(void)PRN_CutToPrint();
	}
#endif

#endif
}

void	ListPrintRunWithoutError(void)
{
#if (0)
** 	/* SAKAKI */
** 	ListPrintRun();
#else
	/* HINOKI */
	ListPrintRun();
#endif
}

WORD	ListPrintRun(void)
{
#if (0)
** 	/* SAKAKI */
** 	UWORD	i, j, k;
** 
** 	if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 		ListClose();
** 		return(NG);
** 	}
** 	GetOneTwiceLineCharacterImage(&List.S.Print[0], &List.S.Attribute[0], &PRN_ImageBuffer1[0][0]);
** 	for (k = 0; k < 16; k++) {
** 		for (i = 0; i < 4; i++) {
** 			for (;;) {
** 
** 				if (!CheckLineWritePoint()) {
** 					CMN_DisableInterrupt();
** 					DecodeWaitFlag = 1;
** 					wai_evt(EVT_PRINT_HEAT_1LINE_END);
** 					continue;
** 				}
** 				for (j = 0; j < 160; j++) {
** 					PRN_ImageBuffer1[ImageLineWritePoint][j+28] = PRN_ImageBuffer1[k][j];
** 				}
** 				RenewLineWritePoint();
** 				break;
** 			}
** 		}
** 	}
** 	for (;;) {
** 		if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
** 			ListClose();
** 			return(NG);
** 		}
** 		if (PRN_OverHeatCheck() == TRUE) {
** 			if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
** 				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
** 				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 			}
** 			wai_tsk(2);
** 			continue;
** 		}
** 		else {
** 			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
** 				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
** 				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 			}
** 			HeatPulseEnable();
** 			break;
** 		}
** 	}
** 	return(OK);
#else
	/* HINOKI */
	UWORD	i, j, k;

#if (0)	/*  By O.Kimoto 1998/12/07 */
** 	if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 		ListClose();
** 		return(NG);
** 	}
#endif

#if (0)
** 	GetOneTwiceLineCharacterImage(&List.S.Print[0], &List.S.Attribute[0], (UWORD *)&PRN_ImageBuffer1[0][0]);
#else
	GetOneTwiceLineCharacterImage(&List.S.Print[0], &List.S.Attribute[0], (UWORD *)PRN_FontImageBufferAddress);
#endif
	for (k = 0; k < 16; k++) {
		for (i = 0; i < PRN_ListHight; i++) {
			for (;;) {

				/* プリンターエラーを見るパスが抜けていた by O.Kimoto 1998/12/07 */
				if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
					PrinterStopProcess  = TRUE;
					break;
				}

				if (!EnableToWritePrtImageBuf()) {
					CMN_DisableInterrupt();
					DecodeWaitFlag = TRUE;
					wai_evt(EVT_PRINT_HEAT_1LINE_END);
					continue;
				}
#if (0)
** 				for (j = 0; j < 160; j++) {
** 					PRN_ImageBuffer1[(UWORD)GetPrtImageBufWriteLineNo()][j+28] = PRN_ImageBuffer1[k][j];
** 				}
#else
#if (0)
** 				/* PRN_ImageBuffer1のOffSetを入れます。 By O.Kimoto 1998/11/10 */
** 				CMN_StringCopyNum(&PRN_ImageBuffer1[(UWORD)GetPrtImageBufWriteLineNo()][28],(UBYTE *)(PRN_FontImageBufferAddress+(80*k)),160);
#else
				CMN_StringCopyNum(&PRN_ImageBuffer1[(UWORD)GetPrtImageBufWriteLineNo()][28+PRN_ImageBufferOffSet],(UBYTE *)(PRN_FontImageBufferAddress+(80*k)),160);
#endif
#endif
				(void)QueryImageStartPointer();
				(void)PrintLine();

				/* 蓄積中＆リストプリント時のキー取り込みが非常に重くなる不具合 1999/02/24 by T.Soneoka */
				if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {
					wai_tsk(1);
				}

				break;
			}
		}
	}
	for (;;) {
		if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
#if (0)
** 			/* 記録紙無しの見方が間違えている by O.Kimoto 1999/01/07 */
** 			if ((PRN_PrintErrorHaltRequest() == OK) && PS1() && (!PS2())) {
** 				CutToPrintExecFlag = YES;
** 			}
#else
			if (PRN_PrintErrorHaltRequest() == NG /* OK */) {
				CutToPrintExecFlag = NO /* YES */;
			}
#endif

			ListClose();
			CutToPrintExecFlag = YES /* NO */;

#if (0)
** 			/* ストップキーが押されたときの戻り値が上位関数と一致していない
** 			** by O.Kimoto 1999/01/29
** 			*/
** 			return(NG);
#else
			if (PRN_PrintHaltRequest() == NG) {
				return(MSG_PRN_LST_STOPSW_ON);
			}
			else {
				return(NG);
			}
#endif

		}

#if defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)
		/* HINOKI2は印字中のオーバーヒートチェックはしない By O.Kimoto 2002/02/25 */
		break;
#else
		if (PRN_OverHeatCheck() == TRUE) {
			if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
			}
			wai_tsk(2);
			continue;
		}
		else {
			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
			}
			break;
		}
#endif

		/* 下記追加 By O.Kimoto 1998/12/01 */
		if (SYS_PRN_StopRequestFromModem) {
			wai_tsk(2);
			continue;
		}

	}
	return(OK);
#endif
}

void	ListLineFeedWithoutError(UBYTE line)
{
#if (0)
** 	/* SAKAKI */
** 	ListLineFeed(line);
#else
	/* HINOKI */
	ListLineFeed(line);
#endif
}

WORD	ListLineFeed(UBYTE line)
{
#if (0)
** 	/* SAKAKI */
** 	UWORD	i;
** 	UBYTE	m;
** 
** 	if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 		return(NG);
** 	}
** 	if (line == 0) {
** 		line = 1;	/* ?上位関数との整合性をはかるため */
** 	}
** 	for (m = 0; m < line ;m++) {
** 		for (i = 0; i < 64 ;i++) {
** 			for (;;) {
** 				if (!CheckLineWritePoint()) {
** 					CMN_DisableInterrupt();
** 					DecodeWaitFlag = 1;
** 					wai_evt(EVT_PRINT_HEAT_1LINE_END);
** 					continue;
** 				}
** 				CMN_MemorySet(&PRN_ImageBuffer1[ImageLineWritePoint][0], PRINT_IMAGE_BUF_SIZE, 0xff);
** 				RenewLineWritePoint();
** 				break;
** 			}
** 		}
** 	}
** 	for (;;) {
** 		if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
** 			return(NG);
** 		}
** 		if (PRN_OverHeatCheck() == TRUE) {
** 			if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
** 				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
** 				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 			}
** 			wai_tsk(2);
** 			continue;
** 		}
** 		else {
** 			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
** 				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
** 				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 			}
** 			break;
** 		}
** 	}
** 	return(OK);
#else
	/* HINOKI */
	UWORD	i;
	UBYTE	m;

#if (0)	/*  By O.Kimoto 1998/12/07 */
** 	if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 		ListClose();
** 		return(NG);
** 	}
#endif

	if (line == 0) {
		line = 1;	/* ?上位関数との整合性をはかるため */
	}
	for (m = 0; m < line ;m++) {
		for (i = 0; i < (UWORD)(16 * PRN_ListHight) ;i++) {	/* Change 64 to (16 * PRN_ListHight) by O.Kimoto 1998/11/09 */
			for (;;) {

				if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
					PrinterStopProcess  = TRUE;
					break;
				}

				if (!EnableToWritePrtImageBuf()) {
					CMN_DisableInterrupt();
					DecodeWaitFlag = TRUE;
					wai_evt(EVT_PRINT_HEAT_1LINE_END);
					continue;
				}
				CMN_MemorySet(&PRN_ImageBuffer1[(UWORD)GetPrtImageBufWriteLineNo()][0], PRINT_IMAGE_BUF_SIZE, 0x00);	/* このまま By O.Kimoto 1998/11/10 */
				(void)QueryImageStartPointer();
				(void)PrintLine();
				break;
			}
		}
	}
	for (;;) {
		if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);

#if (0)
** 			/* 記録紙無しの見方が間違えている by O.Kimoto 1999/01/07 */
** 			if ((PRN_PrintErrorHaltRequest() == OK) && PS1() && (!PS2())) {
** 				CutToPrintExecFlag = YES;
** 			}
#else
			if (PRN_PrintErrorHaltRequest() == NG /* OK */) {
				CutToPrintExecFlag = NO /* YES */;
			}
#endif

			ListClose();
			CutToPrintExecFlag = YES /* NO */; 

#if (0)
** 			/* ストップキーが押されたときの戻り値が上位関数と一致していない
** 			** by O.Kimoto 1999/01/29
** 			*/
** 			return(NG);
#else
			if (PRN_PrintHaltRequest() == NG) {
				return(MSG_PRN_LST_STOPSW_ON);
			}
			else {
				return(NG);
			}
#endif

		}

#if defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)
		/* HINOKI2は印字中のオーバーヒートチェックはしない By O.Kimoto 2002/02/25 */
		break;
#else
		if (PRN_OverHeatCheck() == TRUE) {
			if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
			}
			wai_tsk(2);
			continue;
		}
		else {
			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
			}
			break;
		}
#endif

	}
	return(OK);
#endif
}

/*************************************************************************
	module		:[画像付きリストのプリントのメイン関数]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[Apr.17,1996		送信証の仕様変更により蓄積原稿を印字することになった。ﾁｪｯｸﾒｯｾｰｼﾞ
								と処理が同じなのでここに追加するが、本当はPRN_ImagePrintTask()で
								分岐すべきだと思う。								By H.Hirao
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1994/07/28]
	author		:[吉川弘康]
*************************************************************************/
WORD	LST_ImagePrint(void)
{
#if (0)
** 	/* SAKAKI */
** 	if (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR) {	/*TCR ON */
** 		CutToPrintExecFlag = YES;
** 		Print_TxConf(LST_ERR_CLOSE);
** 		CutToPrintExecFlag = NO;
** 	if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 			ListClose();
** 			return(NG);
** 		}
** 	}
** 	else {
** 		if ((SYS_DocumentPrintPageNo == 0) || (!(SYB_CommandFile[SYS_DocumentPrintNo].Ability & SYS_WARP_PRINT))) {
** 			ListOpen();
** 			Doc_ChkMsg();
** 			if (SYB_CommandFile[SYS_DocumentPrintNo].Ability & SYS_WARP_PRINT) {
** 				CutToPrintExecFlag = NO;
** 			}
** 			else {
** 				CutToPrintExecFlag = YES;
** 			}
** 			ListClose();
** 			CutToPrintExecFlag = NO;
** 			if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 				return(NG);
** 			}
** 		}
** 	}
** 	if ((SYB_CommandFile[SYS_DocumentPrintNo].Ability & SYS_WARP_PRINT) && (SYS_DocumentPrintPageNo == 0)) {
** 		SYB_CommandFile[SYS_DocumentPrintNo].PrintPage = SYS_DocumentPrintPageNo = 1;
** 	}
** 	/** 画像 **/
** 	PrinterUseMode = PRINT_LISTIMAGE;
** 	PRN_PrinterOpen();
** 	PrintIndex.Item = SYS_MEM_TX_FILE;
** 	PrintIndex.No = SYS_DocumentPrintNo;
** 	PrintIndex.Page = SYS_DocumentPrintPageNo;
** 	PrintIndex.BoxNumber = MEM_IGNORE_BOX_NUMBER;
** 	for (;;) {
** 		if (MEM_ReadOpen(&PrintIndex,&PrintExecReadData) != MEM_OK) {
** 			PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 			ListClose();
** 			SYB_MaintenanceSwitch[MNT_SW_A7] |= PRINT_DECODE_ERROR;
** 			return(NG);
** 		}
** 		PRN_SoftWareDecodeInitial();	/* ソフト デコード(縮小)の初期設定 */
** 		PageStartLineB4WhiteLineSet();
** 		PRN_Control.PrintMode = MEM_CheckStoreMode(&PrintIndex);
** 		SetPrintModeParameterEveryPage();
** 		PRN_Control.PrintSize = MEM_CheckStoreSize(&PrintIndex);
** 		PRN_Control.PaperSize = PRN_GetPaperSize();
** 		SetPrintSizeParameterEveryPage();
** 		/*１ページ開始*/
** 		PRN_OnePageStart();
** 		for (;;) {
** 			if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 				PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
** 				ListClose();
** 				return(NG);
** 			}
** 			if (PRN_OverHeatCheck() == TRUE) {
** 				if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
** 					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
** 					PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 					PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 					snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 				}
** 				continue;
** 			}
** 			else {
** 				if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
** 					SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
** 					PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 					PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 					snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 				}
** 			}
** 			if ((!CheckLineWritePoint()) || DecodeWaitCommandFlag) {
** 				CMN_DisableInterrupt();
** 				DecodeWaitFlag = 1;
** 				wai_evt(EVT_PRINT_HEAT_1LINE_END);
** 				continue;
** 			}
** 			if (PRN_PrintModeCount == PrintModeCountWork) {
** 				if (CodeToBitImage(ImageLineWritePoint) != OK) {
** 					break;
** 				}
** 				RenewLineWritePoint();
** 			}
** 			else {
** 				if (PRN_Control.ReductionType == 0) {
** 					PrvBitImageToBitImage();
** 					RenewLineWritePoint();
** 				}
** 				else {
** 					if (!Skip(&PRN_LineSkipData)) {
** 						PrvBitImageToBitImage();
** 						RenewLineWritePoint();
** 					}
** 				}
** 			}
** 			if (PRN_PrintModeCount == 0) {
** 				PRN_PrintModeCount = PrintModeCountWork;
** 			}
** 			else {
** 				PRN_PrintModeCount--;
** 			}
** 		}
** 		/*１ページ終了*/
** 		if ((!(SYB_CommandFile[SYS_DocumentPrintNo].Ability & SYS_WARP_PRINT)) || (PRN_PrintErrorHaltRequest() == NG)) {
** 			PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 			break;
** 		}
** 		if (SYB_CommandFile[SYS_DocumentPrintNo].PrintPage < SYB_CommandFile[SYS_DocumentPrintNo].Page) {
** 			SYB_CommandFile[SYS_DocumentPrintNo].PrintPage ++; /* 印字ﾍﾟｰｼﾞ残 */
** 			SYS_DocumentPrintPageNo++;	/* 印字ページを加算 */
** 			PrintIndex.Page = SYS_DocumentPrintPageNo;
** 			PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 			PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 			snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 		}
** 		else {
** 			PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 			break;
** 		}
** 		PRN_List1PageClose();
** 		GaInterruptFlag &= (~INT_PRINTER);
** 		GaInterruptDisable();
** 	}
** 	ListClose();
** 	if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 		return(NG);
** 	}
** 	return(OK);
#else
	/* HINOKI */
	UBYTE decode_ret;
 	int	dummyline; /* 1999/03/03 by T.Soneoka */
	
	decode_ret = OK;

	if (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR) {	/*TCR ON */

#if (0)
** 		/* 送信証とチェックメッセージは定型長でカットするように変更 By O.Kimoto 1999/02/22 */
** 		CutToPrintExecFlag = NO /* YES */;
#else
		CutToPrintExecFlag = YES /* YES */;
#endif

		Print_TxConf(LST_ERR_CLOSE);
		CutToPrintExecFlag = YES /* NO */;
		if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
			ListClose();

#if (0)
** 			/* ストップキーが押されたときの戻り値が上位関数と一致していない
** 			** by O.Kimoto 1999/01/29
** 			*/
** 			return(NG);
#else
			if (PRN_PrintHaltRequest() == NG) {
				return(MSG_PRN_LST_STOPSW_ON);
			}
			else {
				return(NG);
			}
#endif

		}

		/* ＴＣＲでリストとイメージのつなぎ目でごみをプリントしていた。
		** リストプリントの終了時、プリンターを停止していない為と推測される。
		** よって、ここで、プリント用バッファの掃出しとプリンター停止処理を追加する。
		** by O.Kimoto 1999/02/23
		*/
		WaitAllImageLinePrint();
		PrinterDmaPermission = FALSE;
		DtcPermission = FALSE;

	}
	else {
		if ((SYS_DocumentPrintPageNo == 0) || (!(SYB_CommandFile[SYS_DocumentPrintNo].Ability & SYS_WARP_PRINT))) {
			ListOpen();
			Doc_ChkMsg();	/* ListClose()は下で呼びます。 */
			if (SYB_CommandFile[SYS_DocumentPrintNo].Ability & SYS_WARP_PRINT) {
				CutToPrintExecFlag = YES /* NO */;
			}
			else {
				CutToPrintExecFlag = NO /* YES */;
			}
			ListClose();
			CutToPrintExecFlag = YES /* NO */;

#if (0)
** 			/* ストップキーが押されたときの戻り値が上位関数と一致していない
** 			** by O.Kimoto 1999/01/29
** 			*/
** 			if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 				return(NG);
** 			}
#else
			if (PRN_PrintHaltRequest() == NG) {
				return(MSG_PRN_LST_STOPSW_ON);
			}
			else if (PRN_PrintErrorHaltRequest() == NG) {
				return(NG);
			}
#endif

/*
** 上記のListClose()の中で下記処理を行っているの削除します
** ループ不具合
** by T.Soneoka 1999/03/03 by T.Soneoka]
*/
#if (0)
**			/* ＴＣＲでリストとイメージのつなぎ目でごみをプリントしていた。
**			** リストプリントの終了時、プリンターを停止していない為と推測される。
**			** よって、ここで、プリント用バッファの掃出しとプリンター停止処理を追加する。
**			** by O.Kimoto 1999/02/23
**			*/
**			WaitAllImageLinePrint();
**			PrinterDmaPermission = FALSE;
**			DtcPermission = FALSE;
#endif
		}
	}
	if ((SYB_CommandFile[SYS_DocumentPrintNo].Ability & SYS_WARP_PRINT) && (SYS_DocumentPrintPageNo == 0)) {
		SYB_CommandFile[SYS_DocumentPrintNo].PrintPage = SYS_DocumentPrintPageNo = 1;
	}

	/** 画像 **/
	PrinterUseMode = PRINT_LISTIMAGE;
	PRN_PrinterOpen();

	/* 追加 By O.Kimoto 1998/12/01 */
	if (SYB_CommandFile[SYS_DocumentPrintNo].Ability & SYS_WARP_PRINT) {
		PRN_StandbyToPrint();
	}

	PrintIndex.Item = SYS_MEM_TX_FILE;
	PrintIndex.No = SYS_DocumentPrintNo;
	PrintIndex.Page = SYS_DocumentPrintPageNo;
	PrintIndex.BoxNumber = MEM_IGNORE_BOX_NUMBER;
	for (;;) {

		/* ＳＡＫＡＫＩはここで記録紙の引き戻しを待っていますが、ＨＩＮＯＫＩは既に
		** 引き戻しは完了していますので処理は省略します。
		** By O.Kimoto 1998/12/01
		*/

#if (0)
** 		/* 処理変更（by SAKAKI) By O.Kimoto 1998/12/01 */
** 		if (MEM_ReadOpen(&PrintIndex,&PrintExecReadData) != MEM_OK) {
** 			PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 			ListClose();
** 			SYB_MaintenanceSwitch[MNT_SW_A7] |= PRINT_DECODE_ERROR;
** 			return(NG);
** 		}
** 
** 		/* 記録紙の属性初期化 */
** 		SetPaperAttribute();
** 
** 		PRN_SoftWareDecodeInitial();	/* ソフト デコード(縮小)の初期設定 */
** 		PageStartLineB4WhiteLineSet();
** 		PageQ.Mode = MEM_CheckStoreMode(&PrintIndex);
** 		SetPrintModeParameterEveryPage();
** 		PageQ.Size = MEM_CheckStoreSize(&PrintIndex);
** 		SetPrintSizeParameterEveryPage();
** 
** 		StartPagePrint();
** 
** 		/*１ページ開始*/
** 		PRN_OnePageStart();
** 		for (;;) {
** 			if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
** 				PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
** 				ListClose();
** 				return(NG);
** 			}
** 			if (PRN_OverHeatCheck() == TRUE) {
** 				if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
** 					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
** 					PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 					PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 					snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 				}
** 				continue;
** 			}
** 			else {
** 				if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
** 					SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
** 					PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 					PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 					snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 				}
** 			}
** 			if ((!EnableToWritePrtImageBuf()) || DecodeWaitCommandFlag) {
** 				CMN_DisableInterrupt();
** 				DecodeWaitFlag = TRUE;
** 				wai_evt(EVT_PRINT_HEAT_1LINE_END);
** 				continue;
** 			}
** 			if (PRN_PrintModeCount == PrintModeCountWork) {
** 
** #if (0)
** ** 				/* HINOKIはこの関数を呼ぶ前に以下の処理をするように変更します。 By O.Kimoto 1998/11/05 */
** ** 				if (CodeToBitImage((UWORD)GetPrtImageBufWriteLineNo()) != OK) {
** ** 					break;
** ** 				}
** #else
** 
** 				wai_sem(semno.SCDC_DRAM_Access);
** 
** 				CMN_DisableInterrupt();
** 				DecMemoryExecBkupData	= MemoryExecData;
** 				MemoryExecData			= PrintExecReadData;
** 				CMN_EnableInterrupt();
** 
** 				decode_ret = CodeToBitImage((UWORD)GetPrtImageBufWriteLineNo());
** 
** 				CMN_DisableInterrupt();
** 				PrintExecReadData	= MemoryExecData;
** 				MemoryExecData	= DecMemoryExecBkupData;
** 
** 				/* CMN_EnableInterrupt(); Sig_semの中で割り込み解除しているのでここでは許可しない。 */
** 				sig_sem(semno.SCDC_DRAM_Access);
** 				
** 				if (decode_ret != OK) {
** 					break;
** 				}
** #endif
** 
** 				(void)QueryImageStartPointer();
** 				(void)PrintLine();
** 			}
** 			else {
** 				if (PageQ.Reduction == 0) {
** 					PrvBitImageToBitImage();
** 					(void)QueryImageStartPointer();
** 					(void)PrintLine();
** 				}
** 				else {
** 					if (!Skip(&PRN_LineSkipData)) {
** 						PrvBitImageToBitImage();
** 						(void)QueryImageStartPointer();
** 						(void)PrintLine();
** 					}
** 				}
** 			}
** 			if (PRN_PrintModeCount == 0) {
** 				PRN_PrintModeCount = PrintModeCountWork;
** 			}
** 			else {
** 				PRN_PrintModeCount--;
** 			}
** 		}
** 		/*１ページ終了*/
** 		if ((!(SYB_CommandFile[SYS_DocumentPrintNo].Ability & SYS_WARP_PRINT)) || (PRN_PrintErrorHaltRequest() == NG)) {
** 			PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 			break;
** 		}
** 		if (SYB_CommandFile[SYS_DocumentPrintNo].PrintPage < SYB_CommandFile[SYS_DocumentPrintNo].Page) {
** 			SYB_CommandFile[SYS_DocumentPrintNo].PrintPage ++; /* 印字ﾍﾟｰｼﾞ残 */
** 			SYS_DocumentPrintPageNo++;	/* 印字ページを加算 */
** 			PrintIndex.Page = SYS_DocumentPrintPageNo;
** 			PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 			PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 			snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 		}
** 		else {
** 			PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 			break;
** 		}
** 		PRN_List1PageClose();
** 	}
#else
		
		/* 処理変更（by SAKAKI) By O.Kimoto 1998/12/01 */
		PRN_MemoryOpenResult = MEM_ReadOpen(&PrintIndex,&PrintExecReadData);

		/* 記録紙の属性初期化 */
		SetPaperAttribute();

		PRN_SoftWareDecodeInitial();	/* ソフト デコード(縮小)の初期設定 */
		PageStartLineB4WhiteLineSet();
		PageQ.Mode = MEM_CheckStoreMode(&PrintIndex);
		SetPrintModeParameterEveryPage();
		PageQ.Size = MEM_CheckStoreSize(&PrintIndex);
		SetPrintSizeParameterEveryPage();

		StartPagePrint();

		/*１ページ開始*/
		PRN_OnePageStart();
		if (PRN_MemoryOpenResult == MEM_OK) {
			for (;;) {
				if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
					PrinterStopProcess  = TRUE;
					PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
					SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
					ListClose();
					return(NG);
				}

				if (PRN_OverHeatCheck() == TRUE) {
#if defined (HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)	/* 印字中は異常温度になっていても無視 2002/02/25 T.Takagi */
#else
					if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
						SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
						PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
						PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
						snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
					}
					continue;
#endif
				}
				else {
					if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
						SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
						PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
						PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
						snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
					}
				}

				if ((!EnableToWritePrtImageBuf()) || DecodeWaitCommandFlag || SYS_PRN_StopRequestFromModem) {
					CMN_DisableInterrupt();
					DecodeWaitFlag = TRUE;
					wai_evt(EVT_PRINT_HEAT_1LINE_END);
					continue;
				}
				if (PRN_PrintModeCount == PrintModeCountWork) {

if (SCDC_SWITCHING_TEST == 0) {	/* For Debug SoftCodec Switch Test by O.Kimoto 1998/12/16 */
					wai_sem(semno.SCDC_DRAM_Access);
					CMN_DisableInterrupt();
					DecMemoryExecBkupData	= MemoryExecData;
					MemoryExecData			= PrintExecReadData;
					CMN_EnableInterrupt();
}
					decode_ret = CodeToBitImage((UWORD)GetPrtImageBufWriteLineNo());

if (SCDC_SWITCHING_TEST == 0) {	/* For Debug SoftCodec Switch Test by O.Kimoto 1998/12/16 */
					CMN_DisableInterrupt();
					PrintExecReadData	= MemoryExecData;
					MemoryExecData	= DecMemoryExecBkupData;
					/* CMN_EnableInterrupt(); Sig_semの中で割り込み解除しているのでここでは許可しない。 */
					sig_sem(semno.SCDC_DRAM_Access);
}
					
					if (decode_ret != OK) {

						/*
						** 最後に白ダミーデータでデータを押し出します
						** デコード終了のところで、セットするようにします
						** 1999/03/03 by T.Soneoka
						*/
					 	dummyline = 2;
					 	while (dummyline--) {
					 		(void)CMN_WordMemorySet((UWORD *)&PrinterBuffer[GetPrtImageBufWriteLineNo()][0], (UWORD)128, 0x00);
					 		(void)GetWritePtrPrtImageBuf();
					 		IncPrtImageReadableLine();
					 	}

						break;
					}
					(void)QueryImageStartPointer();
					(void)PrintLine();
				}
				else {
					if (PageQ.Reduction == 0) {
						PrvBitImageToBitImage();
						(void)QueryImageStartPointer();
						(void)PrintLine();
					}
					else {
						if (!Skip(&PRN_LineSkipData)) {
							PrvBitImageToBitImage();
							(void)QueryImageStartPointer();
							(void)PrintLine();
						}
					}
				}
				if (PRN_PrintModeCount == 0) {
					PRN_PrintModeCount = PrintModeCountWork;
				}
				else {
					PRN_PrintModeCount--;
				}
			}
		}
		else {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
			SYB_MaintenanceSwitch[MNT_SW_A7] |= PRINT_DECODE_ERROR;
			PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
			break;
		}

		/* ライフモニタプリント枚数更新を入れます 1999/1/22 by T.Soneoka */
		SYB_LifeMonitor.PrintCount++;

		/*１ページ終了*/
		if ((!(SYB_CommandFile[SYS_DocumentPrintNo].Ability & SYS_WARP_PRINT)) || (PRN_PrintErrorHaltRequest() == NG)) {
			PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
			break;
		}
		if (SYB_CommandFile[SYS_DocumentPrintNo].PrintPage < SYB_CommandFile[SYS_DocumentPrintNo].Page) {
			SYB_CommandFile[SYS_DocumentPrintNo].PrintPage ++; /* 印字ﾍﾟｰｼﾞ残 */
			SYS_DocumentPrintPageNo++;	/* 印字ページを加算 */
			PrintIndex.Page = SYS_DocumentPrintPageNo;
			PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
			PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
			snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
		}
		else {
			PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
			break;
		}
		PRN_List1PageClose();
		/*
		** 紙搬送変更 1999/04/13 by T.Soneoka
		*/
		if (PRN_PrintErrorHaltRequest() == OK) {
			PRN_CutPosToPrintPos();
		}

#if defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)
		/* HINOKI2は印字中のオーバーヒートはチェックしない By O.Kimoto 2002/02/25 */
		if (PRN_OverHeatCheck() == TRUE) {
			PrinterStopProcess  = TRUE;
			PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
			PRN_PrintToStandby();
			return(NG);
		}
#endif

	}
#endif

	ListClose();
	if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
		return(NG);
	}

#if defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)
		/* HINOKI2は印字中のオーバーヒートはチェックしない By O.Kimoto 2002/02/25 */
		if((SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) == SYS_PRINTER_HIGH_TEMP) {
			PrinterStopProcess  = TRUE;
			return(OK);	/* ここでNGを返すと再プリントが起動されるのでOKとしておく */
		}
#endif

	return(OK);
#endif
}

/*************************************************************************
	module		:[機器設定リスト用、行間隔挿入]
	function	:[
	]
	return		:[エラーコード]
	common		:[なし]
	condition	:[COMMON]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[Feb 28,1996]
	auther		:[平尾英典]
*************************************************************************/
WORD	ListSpacePrint(void)
{
	return(OK);
}


WORD	ListHeadPrint(void)
{
	return(OK);
}


