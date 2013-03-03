/*******************************************************************
*	System		: SAKAKI
*	File Name	: PRN_MAIN.C
*	Author		: K.Kawata
*	Date		: 1998/6/9
*	Description	:
*	Maintenance	:
*			: Original:\src\kobe\anzu\src\prn_main.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
********************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysprint.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\syslifem.h"
#include "\src\atlanta\define\evttomsg.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\scn_tbl.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\lst_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\unisw_f.h"
#include "\src\atlanta\define\mnt_sw.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\define\io_pro.h"

#if (0)
** /* SAKAKI */
** #include "\src\atlanta\prt\thermal\define\prn_pro.h"
** #include "\src\atlanta\prt\thermal\define\prn_def.h"
** #include "\src\atlanta\prt\thermal\define\prn_msg.h"
** #include "\src\atlanta\prt\thermal\define\prn_stat.h"
** #include "\src\atlanta\prt\thermal\define\prn_stat.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_tbl.h"
** #include "\src\atlanta\sakaki\define\sakiport.h"
** #include "\src\atlanta\sakaki\ext_v\ga_data.h"
#else
/* HINOKI */
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"	/* Endmark By O.Kimoto 1999/02/09 */
#include "\src\cpu\sh7043_a\irom\define\def_semn.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_sem.h"
#include "\src\atlanta\ext_v\dma_data.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scdc_dat.h"
#include "\src\atlanta\satsuki2\ext_v\ga_buf.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scdc_dat.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
 #endif

 #if (0)
 #if (PRO_MODEM == MN195006)
	#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
 #else
  #if defined(SATSUKI2)
	#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
  #else
	#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
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
 #endif
#endif

#if (PRO_CPU_VERSION == SH7043_A)
	#include "\src\cpu\sh7043_a\scd\define\scd.h"
	#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
	#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"
	#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#else
	#include "\src\atlanta\scd\define\scd.h"
	#include "\src\atlanta\scd\define\scdpro.h"
	#include "\src\atlanta\scd\ext_v\scdrlbuf.h"
	#include "\src\atlanta\scd\ext_v\scd_data.h"
#endif
#include "\src\atlanta\ext_v\sys_port.h"
#include "\src\atlanta\define\mntsw_h.h"	/* Endmark2 By O.Kimoto 1999/02/11 */

#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
#include "\src\atlanta\define\cl1_def.h"	/* added by H.Hirao 1999/03/04 */
#include "\src\atlanta\ext_v\cl1_data.h"	/* added by H.Hirao 1999/03/04 */
#endif

void PRN_ImagePrintTask(void);
void	PRN_OnePageStart(void);
UBYTE	PRN_AllPageEnd(void);
BOOL PRN_PrinterOpen(void);
void	PRN_PrinterClose(void);
void	PRN_ImageAllClose(void);
void PRN_Set_Fcode_DataStatus(void);
void	PRN_SoftWareDecodeInitial(void);
void	SetPrintModeParameterEveryPage(void);
void	SetPrintSizeParameterEveryPage(void);
void	PageStartLineB4WhiteLineSet(void);
UWORD	PRN_GetFcodeFileNo(UWORD point);
void	PRN_ImagePrintExit(void);
#if defined (HINOKI2) || defined (HINOKI3) || defined (SATSUKI2)	/* 2002/02/22 T.Takagi */
void	SetPRN_EndMessage_ofError(void);
void	SetPRN_EndMessage_ofStopKey(void);
#endif


extern CONST UBYTE SCDC_SWITCHING_TEST;	/* For Debug SoftCodec Switch Test by O.Kimoto 1998/12/16 */

/*************************************************************************
	module		:[プリントタスクのメインタスク]
	function	:[]
	return		:[]
	common		:[]
	condition	:[
		基本的にはCOMMONとしておき、部分的に、SAKAKI/HINOKIで分岐させる
	]
	comment		:[1.メインタスクからタスク起動される]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[PRN]
	date		:[1998/6/9]
	author		:[K.Kawata]
*************************************************************************/
void PRN_ImagePrintTask(void)
{
	/* COMMON */
	UBYTE decode_ret;
 	int	dummyline; /* 1999/03/03 by T.Soneoka */
	
	decode_ret = OK;

	InzPrinterParameter();				/* プリンタ関係大域変数初期化 *//* HINOKI */
	PRN_1PageReceived = 0;	/* 受信しながらプリントする場合のメインタスクとのイベント空振りフラグ 1998/09/11 */
	tskno_PRN_PrintDataTransTask = 0xffff;

	switch (SYS_DocumentPrintItem) {
	case SYS_MEM_MULTI_COPY_FILE:
		McopyPtr = &SYB_MultiCopyFile[SYS_DocumentPrintNo];
		break;
	case SYS_MEM_RX_FILE:
		MRxPtr = &SYB_MemoryRxPrint[SYS_DocumentPrintNo];
		break;
	case SYS_MEM_SUB_SECURE_FILE:
	case SYS_MEM_SUB_BULLETIN_FILE:
		SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber-1].DataStatus = SYS_SUB_ADDRESS_BOX_PRINTING;
		break;
#if (PRO_CLASS1 == ENABLE)	/* added by H.Hirao 1999/01/22 */
	case SYS_MEM_CL1_RX_FILE:
		MRxPtr = &SYB_CL1_MemoryRxPrint[SYS_DocumentPrintNo];
		break;
#endif
	default:
		MRxPtr = &SYB_MemoryRxPrint[SYS_DocumentPrintNo];
		break;
	}

	switch (SYS_DocumentPrintClass) {
#if (0)
** 	/* 未使用（イニシャルカットはコピープリントタスク使用） By O.Kimoto 1999/02/08 */
** 	case SYS_PRINT_CLASS_INITIAL:
** 
** #if (0)
** ** 		/* SAKAKI */
** ** 		PRN_InitPrinter();
** ** 		PRN_Paper10cmCut();
** ** 		PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** ** 		PrinterEndMessage.Message = MSG_PRN_IMAGE_INITIAL_END;
** ** 		snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** ** 		wai_tsk(0xFFFF);
** #else
** 		/* HINOKI */
** 		PRN_Paper10cmCut();
** 		PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 		PrinterEndMessage.Message = MSG_PRN_IMAGE_INITIAL_END;
** 		snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 		wai_tsk(0xFFFF);
** #endif
#endif

		break;
	case SYS_PRINT_CLASS:
		PrinterUseMode = PRINT_IMAGE;

#if (0)
** 		/* SAKAKI */
** 		PRN_PrinterOpen();
#else
		/* HINOKI */
		if (!PRN_PrinterOpen()) {

			/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
			PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
			PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
			snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
			/* ここまで */

			/* エラーメッセージをメインに通知 */
			wai_tsk(0xFFFF);
		}
#endif

		PrintIndex.Item = SYS_DocumentPrintItem;
		PrintIndex.Page = SYS_DocumentPrintPageNo;
		if ((SYS_DocumentPrintItem == SYS_MEM_SUB_SECURE_FILE) || (SYS_DocumentPrintItem == SYS_MEM_SUB_BULLETIN_FILE)) {
			PrintIndex.BoxNumber = SYS_DocumentPrintBoxNumber;
			if (SYS_DocumentPrintNo == MEM_ALL_NO) {
				PRN_GetFcodeFileNo(0);
			}
			else {
				PrintIndex.No = SYS_DocumentPrintNo;
			}
		}
		else {
			PrintIndex.No = SYS_DocumentPrintNo;
			PrintIndex.BoxNumber = MEM_IGNORE_BOX_NUMBER;
		}

		/* 記録紙の属性初期化 */
		SetPaperAttribute();

#if (0)
**		/* ＨＩＮＯＫＩでは未使用のため削除 by O.Kimoto 1998/11/17 */
**		/* Print Page Queue に登録 */
**		PageQ.Count = (PageQ.Lines * (SYS_A4_LINE / 16));
#endif

		/*ページ単位での設定*/
		PRN_StandbyToPrint();	/* 記録紙引き戻し実行 *//* */
		for (;;) {
			/*
			** ＤＵＡＬ制限変更のため
			** スキャナ制限からプリント制限へ変更する
			** 1999/02/18 by T.Soneoka
			*/
			if (!CHK_UNI_NoTripleRestrict()) {
				if (QueryResourceCount() >= 3) {	/* COMM,SCAN,PRINTのトリプル時 */
					while (1) {
						wai_tsk(10);
						if (QueryResourceCount() < 3) {
							break;
						}
						if (QueryPrinterCoverOpen()) {
							PrinterError |= PRT_ERROR_COVER_OPEN;
						}
						if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
							SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
							break;
						}
					}
				}
			}
			/*
			** スキャン中とプリント中にＣＩを検出した場合、スキャンとプリントをページ間で停止させてからクラス１受信する
			** by H.Hirao 1999/03/03
			*/
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
			while (1) {
				if (QueryPrinterCoverOpen()) {
					PrinterError |= PRT_ERROR_COVER_OPEN;
				}
				if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
					CMN_DisableInterrupt();
					CL1_DualRestrictionStatus &= ~CL1_PRINTER_IN_USE; /* プリント中リセット */
					CMN_EnableInterrupt();
					SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);
					break;
				}
				CMN_DisableInterrupt();
				/* CL1_RestrictionStatusResetTimer added by H.Hirao 1999/05/12 */
				if ((CL1_DualRestrictionStatus & CL1_CLASS1_IN_USE) || SYS_CalledRequestForDocStore || CL1_RestrictionStatusResetTimer) { /* クラス１受信中 または ＣＩ検出 */
					CL1_DualRestrictionStatus &= ~CL1_PRINTER_IN_USE; /* プリント中リセット */
					wai_tsk(100);
				}
				else {
					CL1_DualRestrictionStatus |= CL1_PRINTER_IN_USE; /* プリント中リセット */
					CMN_EnableInterrupt();
					break;
				}
			}
#endif
#if (0)
** 			while ((PRN_Control.Command == PRN_PAGECUT_REQ) || (PRN_Control.Command == PRN_FEED_IN_REQ)) {		/* 記録紙カット引き戻しの終了を待つ */
** 				wai_tsk(2);
** 			}
#endif

#if defined (HINOKI2) || defined (HINOKI3) || defined (SATSUKI2)	/* 2002/02/21 T.Takagi */

			if (PRN_PrintHaltRequest() == NG) {		/* STOPキーが押されたら */
				/* SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP); */
				PrinterStopProcess  = TRUE;
				SetPRN_EndMessage_ofStopKey();
				if (PRN_PrintErrorHaltRequest() == OK) {	/* 2002/02/25 T.Takagi */
					PRN_PrintToStandby();
				}
				PRN_ImageAllClose();
				break;
			}
			if (PRN_PrintErrorHaltRequest() == NG) {	/* 紙なし、JAM、カバーオープン、カッターエラーになったら */
				/* SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP); */
				PrinterStopProcess  = TRUE;
				SetPRN_EndMessage_ofError();
				PRN_ImageAllClose();
				break;
			}
			
			if (PRN_OverHeatCheck() == TRUE) {
				if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
					PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
					PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
					snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
				}
				wai_tsk(2);
				continue;	/* ループさせてページ間で冷めるのを待つ */
			}
			else {
				if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
					SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_HIGH_TEMP;
					PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
					PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
					snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
				}
			}
#endif

			if (MEM_ReadOpen(&PrintIndex,&PrintExecReadData) != MEM_OK) {
				PRN_PrinterClose();
				/*
				** 紙搬送変更 1999/04/13 by T.Soneoka
				*/
				if (PRN_PrintErrorHaltRequest() == OK) {
					PRN_CutPosToStandbyPos();
				}

				PRN_ImageAllClose();

				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);

/*				SYB_MaintenanceSwitch[MNT_SW_A7] |= PRINT_DECODE_ERROR; 2002/04/17 by T.Soneoka */

				/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
				SYB_MaintenanceSwitch[MNT_SW_H8] |= 0x30; /* 2002/04/17 by T.Soneoka */
				PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
				PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
				/* ここまで */

				break;
			}

			PRN_SoftWareDecodeInitial();
			PageStartLineB4WhiteLineSet();

#if (0)
** 			/* SAKAKI */
** 			PRN_Control.PrintMode = MEM_CheckStoreMode(&PrintIndex);
** 			SetPrintModeParameterEveryPage();
** 			PRN_Control.PrintSize = MEM_CheckStoreSize(&PrintIndex);
** 			PRN_Control.PaperSize = PRN_GetPaperSize();
** 			SetPrintSizeParameterEveryPage();
#else
			/* HINOKI */
			PageQ.Mode = MEM_CheckStoreMode(&PrintIndex);
			SetPrintModeParameterEveryPage();
			PageQ.Size = MEM_CheckStoreSize(&PrintIndex);
			SetPrintSizeParameterEveryPage();

			StartPagePrint();
#endif

			/*１ページ開始*/
			PRN_OnePageStart();
			for (;;) {
				if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
					SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~SYS_PRINTER_HIGH_TEMP);

#if (0)
** 					/* SAKAKI */
#else
					/* HINOKI */
					PrinterStopProcess  = TRUE;
#endif

					break;
				}
				if (PRN_OverHeatCheck() == TRUE) {
#if defined (HINOKI2) || defined (HINOKI3) || defined (SATSUKI2)	/* 印字中は異常温度になっていても無視 2002/02/21 T.Takagi */
#else
					if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
						SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
						PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
						PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
						snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
					}
					wai_tsk(2);
					continue;
#endif
				}
				else {
					if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
						SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_HIGH_TEMP;
						PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
						PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
						snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
					}
#if (0)
** 					/* SAKAKI */
** 					HeatPulseEnable();
#endif
				}

#if (0)
** 				/* SAKAKI */
** 				if ((!CheckLineWritePoint()) || DecodeWaitCommandFlag) {
** 					CMN_DisableInterrupt();
** 					DecodeWaitFlag = TRUE;
** 					wai_evt(EVT_PRINT_HEAT_1LINE_END);
** 					continue;
** 				}
#else
				/* HINOKI */
				if ((!EnableToWritePrtImageBuf()) || DecodeWaitCommandFlag) {
					CMN_DisableInterrupt();
					DecodeWaitFlag = TRUE;
					wai_evt(EVT_PRINT_HEAT_1LINE_END);
					continue;
				}
#endif

				if (PRN_PrintModeCount == PrintModeCountWork) {
#if (0)
** 					/* SAKAKI */
** 					if (CodeToBitImage(ImageLineWritePoint) != OK) {
** 						break;
** 					}
** 					RenewLineWritePoint();
#else
					/* HINOKI */
#if (0)
** 					/* HINOKIはこの関数を呼ぶ前に以下の処理をするように変更します。 By O.Kimoto 1998/11/05 */
** 					if (CodeToBitImage((UWORD)GetPrtImageBufWriteLineNo()) != OK) {
** 						break;
** 					}
#else

if (SCDC_SWITCHING_TEST == 0) {	/* for DEBUG by O.Kimoto 1999/01/16 */
					/* HINOKIはこの関数を呼ぶ前に以下の処理をするように変更します。 By O.Kimoto 1998/11/05 */
					wai_sem(semno.SCDC_DRAM_Access);

					CMN_DisableInterrupt();
					DecMemoryExecBkupData	= MemoryExecData;
					MemoryExecData			= PrintExecReadData;
					CMN_EnableInterrupt();
}
					decode_ret = CodeToBitImage((UWORD)GetPrtImageBufWriteLineNo());

if (SCDC_SWITCHING_TEST == 0) {	/* for DEBUG by O.Kimoto 1999/01/16 */
					CMN_DisableInterrupt();
					PrintExecReadData	= MemoryExecData;
					MemoryExecData	= DecMemoryExecBkupData;

					/* CMN_EnableInterrupt(); Sig_semの中で割り込み解除しているのでここでは許可しない。 */
					sig_sem(semno.SCDC_DRAM_Access);
}
					if (decode_ret != OK) {


						/*
						** 最後、白ダミーラインをセットします
						** デコード終了のところで、セットするようにします
						** 1999/03/03 by T.Soneoka
						*/
					 	dummyline = 2;
					 	while (dummyline--) {
					 		(void)CMN_WordMemorySet((UWORD *)&PrinterBuffer[GetPrtImageBufWriteLineNo()][0], (UWORD)128, 0x00);
					 		(void)GetWritePtrPrtImageBuf();
					 		IncPrtImageReadableLine();
					 	}


						/* ライフモニタプリント枚数更新を入れます 1999/1/22 by T.Soneoka */
						SYB_LifeMonitor.PrintCount++;
						break;
					}
#endif

					(void)QueryImageStartPointer();
					(void)PrintLine();
#endif

				}
				else {

#if (0)
** 					/* SAKAKI */
** 					if (PRN_Control.ReductionType == 0) {
** 						PrvBitImageToBitImage();
** 						RenewLineWritePoint();
** 					}
#else
					/* HINOKI */
					if (PageQ.Reduction == 0) {
						PrvBitImageToBitImage();
						(void)QueryImageStartPointer();
						(void)PrintLine();
					}
#endif

					else {
						if (!Skip(&PRN_LineSkipData)) {
							PrvBitImageToBitImage();

#if (0)
** 							/* SAKAKI */
** 							RenewLineWritePoint();
#else
							/* HINOKI */
							(void)QueryImageStartPointer();
							(void)PrintLine();
#endif
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
			/*１ページ終了*/
			PRN_PrinterClose();

#if defined (HINOKI2) || defined (HINOKI3) || defined (SATSUKI2)	/* 2002/02/21 T.Takagi */
			if (PRN_OverHeatCheck() == TRUE) {
				if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
				}
			}
#endif

			if (PRN_AllPageEnd() == YES) {

				/*
				** 紙搬送変更 1999/04/13 by T.Soneoka
				** カットした時点で次の原稿があり／なしを判断し、
				** ない場合は、そのまま原稿を排出、ＰＳ２まで引き戻し、記録待機位置にもってくる
				*/
				if (PRN_PrintErrorHaltRequest() == OK) {
#if defined(SATSUKI2)	/* 壁掛け設定用に追加 by Y.Kano 2003/10/09 */
					if (!CHK_WallHangSetting()) {
						PRN_CutPosToStandbyPos();
					}
#else
					PRN_CutPosToStandbyPos();
#endif
				}
				PRN_ImageAllClose();

				break;
			}

			/*
			** 紙搬送変更 1999/04/13 by T.Soneoka
			*/
			if (PRN_PrintErrorHaltRequest() == OK) {
				PRN_CutPosToPrintPos();
			}

#if (0) /* defined (HINOKI2) */	/* 2002/02/21 T.Takagi */
** 			if (PRN_OverHeatCheck() == TRUE) {
** 				if (!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)) {
** 					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
** 					PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
** 					PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
** 					snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
** 				}
** 				wai_tsk(2);
** 				continue;
** 			}
#endif

#if (0)
** 			/* SAKAKI */
** 			GaInterruptFlag &= (~INT_PRINTER);
** 			GaInterruptDisable();
#endif

		}
		break;
	case SYS_PRINT_CLASS_LIST_MEMORY:
	case SYS_PRINT_CLASS_LIST_MONITOR:
		PrinterUseMode = PRINT_LISTIMAGE;
		PrinterEndMessage.Item = FROM_PRN_IMAGE_PRINT_TASK;
		if (LST_ImagePrint() == OK) {
			PrinterEndMessage.Message = MSG_PRN_IMAGE_END;
		}
		else {
			PrinterEndMessage.Message = MSG_PRN_IMAGE_STOPSW_ON;
		}
#if (0)
** 		/* SAKAKI */
** 		if (PRN_PrintErrorHaltRequest() == NG) {
** 			PRN_InitialRecoverCompleted = FALSE;
** 		}
#endif
		break;
	case SYS_PRINT_CLASS_END:
	case SYS_PRINT_CLASS_EXIT:
		PRN_PrintToStandby();/* */
		PRN_ImageAllClose();
		PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
		PrinterEndMessage.Message = MSG_PRN_IMAGE_INITIAL_END;
		break;
	}
#if (0) /* プリント中ループ対策の２次障害（原稿チェックメッセージプリント時 PrintClassがSYS_PRINT_CLASS_LIST_MONITORのときに書き換えられてしまう） 2002/04/30 by T.Soneoka */
**	PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;	/* add by O.Kimoto 2002/04/17 */
#endif
	snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
	wai_tsk(0xFFFF);
}

void	PRN_OnePageStart(void)
{
#if (0)
** 	/* SAKAKI */
** 	UWORD	i;
** 
** 	PRN_PrintModeCount = PrintModeCountWork;
** 	ImageLineReadPoint = ImageLineStartPoint;
** 	ImageLineWritePoint = (ImageLineStartPoint+7);
** 	PRN_LineDMA.SrcAddress = (UDWORD)&PRN_ImageBuffer1[0][0];
** 	DMA_SetupDMAU(&PRN_LineDMA);
** 	i = PRINT_IMAGE_BUF_LINE*2;
** 	PRN_LineMemoryStatus = 99;
** 	while ((ImageLineReadPoint != (ImageLineWritePoint-2)) && (i > 0)) {
** 		wai_tsk(1);
** 		i--;
** 	}
** 	wai_tsk(1);
** 	HeatPulseEnable();
#else
	/* HINOKI */
	PRN_PrintModeCount = PrintModeCountWork;

	Paper.Phase = PAPER_PHASE_PRINT;
	Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
	Paper.Position = PAPER_POS_PRINTING;
	ChangeRxMotorPhase();
	
#endif
}


UBYTE	PRN_AllPageEnd(void)
{

	PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
	switch (SYS_DocumentPrintItem) {
	case SYS_MEM_MULTI_COPY_FILE:
		if (McopyPtr->SortType == SYS_SORT) {	/*ｿｰﾄ*/
			if (PRN_PrintHaltRequest() == NG) {
				McopyPtr->ExecutiveNumber = McopyPtr->ReserveNumber;
				McopyPtr->PrintPage = 1;
				MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
#if (0)
**				/*
**				** 紙搬送変更 1999/04/13 by T.Soneoka
**				*/
**				PRN_PrintToStandby();
**				PRN_ImageAllClose();
#endif
				PrinterEndMessage.Message = MSG_PRN_IMAGE_STOP;
				return(YES);
			}
			if (PRN_PrintErrorHaltRequest() == NG) {
#if (0)
**				/*
**				** 紙搬送変更 1999/04/13 by T.Soneoka
**				*/
**				PRN_ImageAllClose();
#endif
				/* PRN_InitialRecoverCompleted = FALSE; No use */
				PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
				return(YES);
			}
			if (McopyPtr->ExecutiveNumber == McopyPtr->ReserveNumber) {
				if (McopyPtr->PrintPage == 1) {
#if (0)
**					/*
**					** 紙搬送変更 1999/04/13 by T.Soneoka
**					*/
**					PRN_PrintToStandby();
**					PRN_ImageAllClose();
#endif
					if (PRN_PrintErrorHaltRequest() == NG) {
						/* PRN_InitialRecoverCompleted = FALSE; No Use */
						PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
					}
					else {
#if (0)
**						/*
**						** 紙搬送変更 1999/04/13 by T.Soneoka
**						*/
**						PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/*表示更新*/
**						snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
#endif
						MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
						PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
					}
					return(YES);
				}
				else {
					PrintIndex.Page--;
					McopyPtr->PrintPage --;
				}
			}
			else {
				if (McopyPtr->PrintPage == 1) {
					McopyPtr->ExecutiveNumber++;
					PrintIndex.Page = McopyPtr->PrintPage = McopyPtr->StorePage;
				}
				else {
					PrintIndex.Page--;
					McopyPtr->PrintPage --;
				}
			}
			PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/*表示更新*/
			snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
			return(NO);
		}
		break;
	case SYS_MEM_RX_FILE: /*ﾒﾓﾘ受信原稿*/
#if (PRO_CLASS1 == ENABLE)	/* added by H.Hirao 1999/01/22 */
	case SYS_MEM_CL1_RX_FILE:
#endif
		if (PRN_PrintErrorHaltRequest() == NG) {
#if (0)
**			/*
**			** 紙搬送変更 1999/04/13 by T.Soneoka
**			*/
**			PRN_ImageAllClose();
#endif
			/* PRN_InitialRecoverCompleted = FALSE; No Use */
			PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
			return(YES);
		}
		else {

#if (0)
** 			/* ここで原稿をページ毎に消去してしまうと、以下の処理でプリンターエラーを検出した場合、
** 			** 消去済ページをエラーリカバリープリントすることとなり、結果的には白紙プリント（テストカット長）
** 			** となる。
** 			** by O.Kimoto 1999/02/01
** 			*/
** 			MEM_ClearPage(&PrintIndex); /*印字ﾍﾟｰｼﾞを消去*/
#endif

 #if (PRO_REVERSE_PRINT == ENABLE)	/* 逆順プリント対応 By 2004/11/09 Y.Kano */

			if (CHK_UNI_RxDocReversePrint()) {
				if (MRxPtr->Status == SYS_MEMORY_RX_PRINT) {
					if (MRxPtr->PrintPage > 1) {

						MEM_ClearPage(&PrintIndex); /*印字ﾍﾟｰｼﾞを消去*//* Add by O.Kimoto 1999/02/01 */

						MRxPtr->PrintPage --; /*印字ﾍﾟｰｼﾞ残*/
						PrintIndex.Page = MRxPtr->PrintPage;
						PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/*表示更新*/
						snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
						return(NO);
					}
					else {
						if (PRN_PrintErrorHaltRequest() == NG) {
							/* PRN_InitialRecoverCompleted = FALSE; No Use */
							PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
						}
						else {
							MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
							PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
						}
						return(YES);
					}
				}
				else if (MRxPtr->Status == SYS_MEMORY_RX_FAST_PRINT) {
					if (MRxPtr->PrintPage < MRxPtr->StorePage) {

						MEM_ClearPage(&PrintIndex); /*印字ﾍﾟｰｼﾞを消去*//* Add by O.Kimoto 1999/02/01 */

						MRxPtr->PrintPage ++; /*印字ﾍﾟｰｼﾞ残*/
						PrintIndex.Page = MRxPtr->PrintPage;
						PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/*表示更新*/
						snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
						return(NO);
					}
					else {
						if (PRN_PrintErrorHaltRequest() == NG) {
							/* PRN_InitialRecoverCompleted = FALSE; No Use */
							PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
						}
						else {
							MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
							PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
						}
						return(YES);
					}
				}
			}
			else if (MRxPtr->PrintPage < MRxPtr->StorePage) {

				MEM_ClearPage(&PrintIndex); /*印字ﾍﾟｰｼﾞを消去*//* Add by O.Kimoto 1999/02/01 */

				MRxPtr->PrintPage ++; /*印字ﾍﾟｰｼﾞ残*/
				PrintIndex.Page = MRxPtr->PrintPage;
				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/*表示更新*/
				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
				return(NO);
			}
			else {
				if (MRxPtr->Status == SYS_MEMORY_RX_PRINT) {
#if (0)
**					/*
**					** 紙搬送変更 1999/04/13 by T.Soneoka
**					*/
**					PRN_PrintToStandby();
**					PRN_ImageAllClose();
#endif
					if (PRN_PrintErrorHaltRequest() == NG) {
						/* PRN_InitialRecoverCompleted = FALSE; No Use */
						PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
					}
					else {
						MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
						PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
					}
					return(YES);
				}
				else {
					for (;;) {
						if (PRN_1PageReceived) {
							PRN_1PageReceived = 0;
							if (MRxPtr->PrintPage < MRxPtr->StorePage) {
								MRxPtr->PrintPage ++;	/*印字ﾍﾟｰｼﾞ残*/
								PrintIndex.Page = MRxPtr->PrintPage;
								PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
								snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
								return(NO);
							}
							else {
								if (MRxPtr->Status == SYS_MEMORY_RX_PRINT) {
									if (PRN_PrintErrorHaltRequest() == NG) {
										/* PRN_InitialRecoverCompleted = FALSE; No use */
										PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
									}
									else {
										MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
										PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
									}
									return(YES);
								}
							}
						}
						if (PRN_PrintErrorHaltRequest() == NG) {
							/* PRN_InitialRecoverCompleted = FALSE; No Use */
							PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
							return(YES);
						}
						wai_tsk(2);
					}
				}
			}
 #else	/* PRO_REVERSE_PRINT == DISABLE */
			if (MRxPtr->PrintPage < MRxPtr->StorePage) {

				MEM_ClearPage(&PrintIndex); /*印字ﾍﾟｰｼﾞを消去*//* Add by O.Kimoto 1999/02/01 */

				MRxPtr->PrintPage ++; /*印字ﾍﾟｰｼﾞ残*/
				PrintIndex.Page = MRxPtr->PrintPage;
				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/*表示更新*/
				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
				return(NO);
			}
			else {
				if (MRxPtr->Status == SYS_MEMORY_RX_PRINT) {
#if (0)
**					/*
**					** 紙搬送変更 1999/04/13 by T.Soneoka
**					*/
**					PRN_PrintToStandby();
**					PRN_ImageAllClose();
#endif
					if (PRN_PrintErrorHaltRequest() == NG) {
						/* PRN_InitialRecoverCompleted = FALSE; No Use */
						PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
					}
					else {
						MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
						PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
					}
					return(YES);
				}
				else {
					for (;;) {
						if (PRN_1PageReceived) {
							PRN_1PageReceived = 0;
							if (MRxPtr->PrintPage < MRxPtr->StorePage) {
								MRxPtr->PrintPage ++;	/*印字ﾍﾟｰｼﾞ残*/
								PrintIndex.Page = MRxPtr->PrintPage;
								PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
								snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
								return(NO);
							}
							else {
								if (MRxPtr->Status == SYS_MEMORY_RX_PRINT) {
#if (0)
**									/*
**									** 紙搬送変更 1999/04/13 by T.Soneoka
**									*/
**									PRN_PrintToStandby();
**									PRN_ImageAllClose();
#endif
									if (PRN_PrintErrorHaltRequest() == NG) {
										/* PRN_InitialRecoverCompleted = FALSE; No use */
										PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
									}
									else {
#if (0)
**										/*
**										** 紙搬送変更 1999/04/13 by T.Soneoka
**										*/
**										PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/*表示更新*/
**										snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
#endif
										MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
										PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
									}
									return(YES);
								}
							}
						}
						if (PRN_PrintErrorHaltRequest() == NG) {
#if (0)
**							/*
**							** 紙搬送変更 1999/04/13 by T.Soneoka
**							*/
**							PRN_ImageAllClose();
#endif
							/* PRN_InitialRecoverCompleted = FALSE; No Use */
							PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
							return(YES);
						}
						wai_tsk(2);
					}
				}
			}
 #endif		/* End of PRO_REVERSE_PRINT == ENABLE */
		}
		break;
	case SYS_MEM_SECURE_RX_FILE: /* 親展受信原稿 */
		if (PRN_PrintHaltRequest() == NG) {

#if (0)
**			/*
**			** 紙搬送変更 1999/04/13 by T.Soneoka
**			*/
**			PRN_PrintToStandby();
**			PRN_ImageAllClose();
#endif


#if (0) /* ストップ押下されたのでメッセージもストップ処理にします 1999/1/18 by T.Soneoka */
**			PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
#else
			PrinterEndMessage.Message = MSG_PRN_IMAGE_STOP;
#endif
			return(YES);
		}
		if (PRN_PrintErrorHaltRequest() == NG) {
#if (0)
**			/*
**			** 紙搬送変更 1999/04/13 by T.Soneoka
**			*/
**			PRN_ImageAllClose();
#endif
			/* PRN_InitialRecoverCompleted = FALSE; No Use */
			PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
			return(YES);
		}
		if (SYS_DocumentPrintPageNo < MEM_CountTotalPage(PrintIndex.Item, PrintIndex.No, PrintIndex.BoxNumber)) {
			SYS_DocumentPrintPageNo++;	/* 印字ページを加算 */
			PrintIndex.Page = SYS_DocumentPrintPageNo;
			PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
			snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
			return(NO);
		}
#if (0)
**		/*
**		** 紙搬送変更 1999/04/13 by T.Soneoka
**		*/
**		PRN_PrintToStandby();
**		PRN_ImageAllClose();
#endif
		if (PRN_PrintErrorHaltRequest() == NG) {
			PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
		}
		else {
#if (0)
**			/*
**			** 紙搬送変更 1999/04/13 by T.Soneoka
**			** ここは必要ありません
**			*/
**			PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/*表示更新*/
**			snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
#endif

#if (0)
** 			/* 同一親展ボックスに対して、受信とプリントを行った場合、通信よりも先にプリントが
** 			** 終了すると、メモリを消去するが、その処理が間違えている。！！！！
** 			** 基本的には、受信中には原稿の消去はしないが従来の仕様です。
** 			** by O.Kimoto 1999/03/02
** 			*/
** 			MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
#else
			if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) &&
				(SYS_RxMemoryFileItem == SYS_MEM_SECURE_RX_FILE) &&
				(SYS_RxMemoryFileNo == SYS_DocumentPrintNo)) { /* Nov.17,1994 Common Bug */
					/* Nothing to do */
			}
			else {
#if (0)
**				/*
**				** 記録開始待機位置から記録紙待機位置へ移動中（この時間がラインプリンタの場合、長い）に、同一親展ボックスに対しての受信が、完了した場合、
**				** すべての親展受信原稿が消去されてしまう。by H.Hirao 1999/03/02
**				*/
**				if (SYB_MailBox[SYS_DocumentPrintNo].Status != SYS_MAILBOX_NO_SET)	{
**					SYB_MailBox[SYS_DocumentPrintNo].Status = SYS_MAILBOX_SET;
**				}
**				MEM_ClearDocAndFATArea(SYS_DocumentPrintItem, SYS_DocumentPrintNo, MEM_IGNORE_BOX_NUMBER); /** 親展受信原稿の消去 */
**				SYB_MailBox[SYS_DocumentPrintNo].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
#else
				if (SYS_DocumentPrintPageNo == MEM_CountTotalPage(PrintIndex.Item, PrintIndex.No, PrintIndex.BoxNumber)) {
					if (SYB_MailBox[SYS_DocumentPrintNo].Status != SYS_MAILBOX_NO_SET)	{
						SYB_MailBox[SYS_DocumentPrintNo].Status = SYS_MAILBOX_SET;
					}
					MEM_ClearDocAndFATArea(SYS_DocumentPrintItem, SYS_DocumentPrintNo, MEM_IGNORE_BOX_NUMBER); /** 親展受信原稿の消去 */
					SYB_MailBox[SYS_DocumentPrintNo].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
				}
#endif
			}
#endif

			PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
		}
		return(YES);
		break;
	case SYS_MEM_SUB_SECURE_FILE:	/*Fｺｰﾄﾞ親展原稿*/
	case SYS_MEM_SUB_BULLETIN_FILE:	/*Fｺｰﾄﾞ掲示板原稿*/
		if (PRN_PrintHaltRequest() == NG) {

#if (0)
**			/*
**			** 紙搬送変更 1999/04/13 by T.Soneoka
**			*/
**			PRN_PrintToStandby();
**			PRN_ImageAllClose();
#endif

			PRN_Set_Fcode_DataStatus();
#if (0) /* ストップ押下されたのでメッセージもストップ処理にします 1999/1/18 by T.Soneoka */
**			PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
#else
			PrinterEndMessage.Message = MSG_PRN_IMAGE_STOP;
#endif
			return(YES);
		}
		if (PRN_PrintErrorHaltRequest() == NG) {
#if (0)
**			/*
**			** 紙搬送変更 1999/04/13 by T.Soneoka
**			*/
**			PRN_ImageAllClose();
#endif
			PRN_Set_Fcode_DataStatus();
			/* PRN_InitialRecoverCompleted = FALSE; No Use */
			PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
			return(YES);
		}
		if (PrintIndex.Page < MEM_CountTotalPage(PrintIndex.Item, PrintIndex.No, PrintIndex.BoxNumber)) {
			SYS_DocumentPrintPageNo++;	/* 印字ページを加算 */
			PrintIndex.Page = SYS_DocumentPrintPageNo;
			PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
			snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
			return(NO);
		}
		if (SYS_DocumentPrintItem == SYS_MEM_SUB_SECURE_FILE) {
			MEM_ClearDoc(SYS_DocumentPrintItem, PrintIndex.No, PrintIndex.BoxNumber);	/*1998.11.25 SYS_DocumentPrintNo-->PrintIndex.No K.Kawata */
			CMN_ClearLongBitAssign(&SYB_SubAddressBoxTable[PrintIndex.BoxNumber - 1].StoredDocBit, PrintIndex.No - 1);
		}
		if (SYS_DocumentPrintNo == MEM_ALL_NO) {
			if (PRN_GetFcodeFileNo(PrintIndex.No)) {
				PrintIndex.Page = SYS_DocumentPrintPageNo = 1;
				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
				return(NO);
			}

#if (0)
** 			/* Ｆコード親展の同一ボックスにおいて、すでに受信済み原稿プリント中に再度同一ボックスに受信が発生し
** 			** 通信のＰｈａｓｅＤ中にプリントが完了すると、今受信した原稿が消えてしまい、それでも受信を覚えている
** 			** 変数はそのままなので、その後そのボックス原稿をプリントしようとすると白紙プリントとなり、もう一度プリント
** 			** しようとすると、ボックス使用中となってしまう。
** 			** by O.Kimoto 1999/03/18
** 			*/
** 			if (SYS_DocumentPrintItem == SYS_MEM_SUB_SECURE_FILE) {
** 				MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
** 				CMN_ClearLongBitAssign(&SYB_SubAddressBoxTable[PrintIndex.BoxNumber - 1].StoredDocBit, PrintIndex.No - 1);
** 			}
#endif

		}
#if (0)
**		/*
**		** 紙搬送変更 1999/04/13 by T.Soneoka
**		*/
**		PRN_PrintToStandby();
**		PRN_ImageAllClose();
#endif
		PRN_Set_Fcode_DataStatus();
#if (0)
**		/*
**		** 紙搬送変更 1999/04/13 by T.Soneoka
**		*/
**		PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/*表示更新*/
**		snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
#endif
		PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
		return(YES);
		break;
	default: /* その他の原稿 */
		if (PRN_PrintHaltRequest() == NG) {

#if (0)
**			/*
**			** 紙搬送変更 1999/04/13 by T.Soneoka
**			*/
**			PRN_PrintToStandby();
**			PRN_ImageAllClose();
#endif

#if (0) /* ストップ押下されたのでメッセージもストップ処理にします 1999/1/18 by T.Soneoka */
**			PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
#else
			PrinterEndMessage.Message = MSG_PRN_IMAGE_STOP;
#endif
			return(YES);
		}
		if (PRN_PrintErrorHaltRequest() == NG) {
#if (0)
**			/*
**			** 紙搬送変更 1999/04/13 by T.Soneoka
**			*/
**			PRN_ImageAllClose();
#endif

#if (0) /* プリンタエラーを起こしているのでメッセージをエラー処理にします 1999/1/18 by T.Soneoka */
**			PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
#else
			PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
#endif
			return(YES);
		}
		if (SYS_DocumentPrintPageNo < MEM_CountTotalPage(PrintIndex.Item, PrintIndex.No, PrintIndex.BoxNumber)) { /** 印字する原稿がまだ残っているか? */
			SYS_DocumentPrintPageNo++;	/* 印字ページを加算 */
			PrintIndex.Page = SYS_DocumentPrintPageNo;

			/* メモリ送信時、1枚目以外で交信エラーが発生し、その時に蓄積原稿確認を行うと、白紙をプリント
			** するので、（メモリ送信は送信ＯＫページは消しているため）次ページがあるかどうかを1ページプリント
			** 完了する毎にチェックします。
			** by O.Kimoto 1999/01/27
			*/
			CheckPrintIndex = PrintIndex;
			CheckPrintExecReadData = PrintExecReadData;

			if (MEM_ReadOpen(&CheckPrintIndex,&CheckPrintExecReadData) != MEM_OK) {

#if (0)
**				/*
**				** 紙搬送変更 1999/04/13 by T.Soneoka
**				*/
**				PRN_PrintToStandby();
**				PRN_ImageAllClose();
#endif

				PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
				return(YES);
			}
			else {
				PrinterEndMessage.Message = MSG_PRN_IMAGE_1PAGE_END;	/* 表示更新 */
				snd_msg(mbxno.MAN_Task, &PrinterEndMessage);
				return(NO);
			}
		}

#if (0)
**		/*
**		** 紙搬送変更 1999/04/13 by T.Soneoka
**		*/
**		PRN_PrintToStandby();
**		PRN_ImageAllClose();
#endif

		PrinterEndMessage.Message = MSG_PRN_IMAGE_ALLPAGE_END;
		return(YES);
		break;
	}
}

#if (0)
** 	/* SAKAKI */
** void	PRN_PrinterOpen(void)
** {
** 	PRN_LineMemoryStatus = 0;
** 	ImageLineStartPoint = 0;
** 	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~(SYS_STOP_IMAGE_PRINT+SYS_STOP_LIST_PRINT);
** 	/* ｽﾑｰｼﾞﾝｸﾞﾚｼﾞｽﾀの固定分設定 */
** 	BK2_Status = 0x0c;	/* ＲＡＭＩ／Ｆレジスタ */
** 	outpw(BK2_PORT,BK2_Status);
** 	BK4_1_Status = 0x00;	/* 検索コードレジスタ１ */
** 	outpw(BK4_1_PORT,BK4_1_Status);
** 	BK4_2_Status = 0x00;	/* 検索コードレジスタ２ */
** 	outpw(BK4_2_PORT,BK4_2_Status);
** 	BK4_3_Status = 0x00;	/* 検索コードレジスタ３ */
** 	outpw(BK4_3_PORT,BK4_3_Status);
** 	BK4_4_Status = 0x00;	/* 検索コードレジスタ４ */
** 	outpw(BK4_4_PORT,BK4_4_Status);
** 	BK4_5_Status = 0x00;	/* 検索コードレジスタ５ */
** 	outpw(BK4_5_PORT,BK4_5_Status);
** 	BK4_6_Status = 0x00;	/* 検索コードレジスタ６ */
** 	outpw(BK4_6_PORT,BK4_6_Status);
** 	SYSSR_Status = 0x00;	/* システムステータス（エッジ検出）レジスタ */
** 	outpw(SYSSR_PORT,SYSSR_Status);
** 	BK6_Status = 0xff;	/* スルーレジスタ */
** 	outpw(BK6_PORT,BK6_Status);
** 	BK1_2_Status = 0x00;	/* 拡大レジスタ */
** 	outpw(BK1_2_PORT,BK1_2_Status);
** 	HNO_Status = 0xff;	/* 横ノッチレジスタ１ */
** 	outpw(HNO_PORT,HNO_Status);
** 	IRQINT_5msSet();
** 	S_P_Clock2MHz();
** 	WhiteCheckFF_Clr();
** 	HeatPulseOffSet = CHK_HeatPulseAdjust();
** 	if (CheckKyoseraRegisterRank()) {
** 		HeatPulseHeadRank = 0;
** 	}
** 	else {
** 		HeatPulseHeadRank = CHK_UNI_THERMAL_HEAD_RANK();
** 	}
** 	/*ＤＭＡの初期設定*/
** 	PRN_LineDMA.Channel = DMA_DRAM_PRNCDC_CH;
** 	PRN_LineDMA.Unit = DMA_WORD_TRANSFER;
** 	PRN_LineDMA.Direction = DMA_MEMORY_TO_IO;
** 	PC_24V_On();
}
#else
/* HINOKI */
BOOL PRN_PrinterOpen(void)
{
	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~(SYS_STOP_IMAGE_PRINT+SYS_STOP_LIST_PRINT);

	/* キャラクタープリント１／２プリント */
	if (PrinterUseMode == PRINT_LIST) {
		if (SYB_MaintenanceSwitch[MNT_SW_E7] & PRINT_HALF_REDUCTION) {
			PRN_ListHight = 1;	/* 1/2 Hight */
		}
		else {
			PRN_ListHight = 2;	/* Normal Hight */
		}
	}

	return((BOOL)OpenPrinter());
}
#endif


/*************************************************************************
	module		:[記録紙をカット位置まで送りカットする]
	function	:[
		1.既プリントライン数が最小記録長以内かどうかを判断し、
			以内：最小記録紙長になるまで記録紙を搬送する。
			以上：最終プリントラインをカット位置まで送る（後端余白含む）
		2.記録紙をカットし、カット不良をチェックする。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PRN_PrinterClose(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
void	PRN_PrinterClose(void)
{
#if (0)
** 	/* SAKAKI */
** 	WaitAllImageLinePrint();
** 	PRN_LineMemoryStatus = 0;
** 	ImageLineStartPoint = 0;
** 	DmaDisable();
** 	if (PRN_PrintNocutRequest() == OK) {
** 		PRN_CutToPrint();
** 	}
#else
	/* HINOKI */
	
#if (0)
** 	/* プリンターエラーをチェックする関数が同一内容で関数名違いが２つも在るので、
** 	** １つに統一します。
** 	** by O.Kimoto 1998/12/07
** 	*/
** 	if (PRN_PrintNocutRequest() == OK) [
#else
	if (PRN_PrintErrorHaltRequest() == OK) {
#endif

		WaitAllImageLinePrint();	/** Add by O.Kimoto 1998/11/17 */

		/*
		** プリント中ループ対策 
		** １ページ終了状態で２ページ目に入らないようにする
		** 1999/02/04 by T.Soneoka
		*/
		PrinterDmaPermission = FALSE;
		DtcPermission = FALSE;



		Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
		Paper.Position = PAPER_POS_MOVE_TO_CUT;
		ChangeRxMotorPhase();

		CMN_DisableInterrupt();

#if (0)
** 		/* イベント空振りフラグの見方を変更します。
** 		** by O.Kimoto 1999/02/18
** 		*/
** 		if (!(PrinterEventStatus & PRT_EVT_CUT_ON)) {
** 			wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
** 		}
#else
		if (!PrinterEventStatus) {
			wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
		}
		PrinterEventStatus = 0; /* 1999/05/07 by T.Soneoka イベントを受け取ったら初期化します */
#endif

		PrinterEventStatus &= ~PRT_EVT_CUT_ON;
		PrinterEventStatus &= ~PRT_EVT_ERROR;	/*  By O.Kimoto 1998/12/07 */
		CMN_EnableInterrupt();

		if (PRN_PrintErrorHaltRequest() == OK) {	/* プリンターエラーチェック */	/* Add by O.Kimoto 1998/12/18 */

#if (0) /* カッタ不良チェック追加 1999/04/13 by T.Soneoka */
**			ExecCutter();
#else
			if (ExecCutter() == NG) {
				PrinterError |= PRT_ERROR_CUT_ERROR;
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_CUTTER_ERROR;
				return;
			}
#endif

#if (0)
** 			/* EndMark4
** 			** 印字中にすでにエンドマークを検出している場合は、PS2を見るのと変更でフラグもチェックします。
** 			** by O.Kimoto 1999/03/04
** 			*/
** 			/* Endmark2 By O.Kimoto 1999/02/11 */
** 			if (!QueryPs2On()) {
#else
 #if defined(SATSUKI2)	/* エンドマークチェック用ＰＳ２チェックの追加  2003/10/23 */
			if ((!EndMarkPS2Cehck()) || (EndMarkDetect == TRUE)) {
 #else
			if ((!QueryPs2On()) || (EndMarkDetect == TRUE)) {
 #endif	/* End of defined(SATSUKI2) */
#endif

				EndMarkDetect = TRUE;
				if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {

#if (0)
** 					/* EndMark検出時、いまカットした分は排出するように変更
** 					** by O.Kimoto 1999/02/19
** 					*/
** 					PrinterError |= PRT_ERROR_JAM;
#else
					Paper.Route = ROUTE_PRINTING_TO_READY;
					Paper.Position = PAPER_POS_FEED_OUT;
					Paper.StepsFeedOut = 0;
					ChangeRxMotorPhase();

					CMN_DisableInterrupt();
					if (!PrinterEventStatus) {
						wai_evt(EVT_PRT_IMAGE);
					}
#if (0)
**					PrinterEventStatus &= ~PRT_EVT_DOC_READY_COMPLETE;
**					PrinterEventStatus &= ~PRT_EVT_ERROR;
#else
					PrinterEventStatus = 0; /* 1999/05/07 by T.Soneoka イベントを受け取ったら初期化します */
#endif

#if (0)
** 					/* エンドマーク検出とＪＡＭの区別ができないので、エラーメッセージ変更
** 					** by O.Kimoto 1999/03/09
** 					*/
** 					PrinterError |= PRT_ERROR_NO_PAPER;
** 					SYS_MachineStatus[SYS_PRINTER_STATUS1] |=SYS_PRINTER_NO_PAPER; /* マシーンステータスもあわせてセットします。 by O.Kimoto 1999/02/24 */
#else
					PrinterError |= PRT_ERROR_JAM;
					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
#endif

					CMN_EnableInterrupt();
#endif

					return;
				}
			}

/*
** 紙搬送変更 1999/04/13 by T.Soneoka
** カットした時点で次の原稿があり／なしを判断し、
** ない場合は、そのまま原稿を排出、ＰＳ２まで引き戻し、記録待機位置にもってくる
*/
#if (0)
**#if (1);
**		 	/* 本来は紙搬送時間短縮のために、以下の方がよいのですが、搬送系処理の都合で、
**		 	** 当面、変えておきます。
**		 	** by O.Kimoto 1998/11/11
**			** 本来の処理にします by T.Soneoka 1998/11/13
**		 	*/
**			Paper.Route = ROUTE_NONE;
**		 	Paper.Position = PAPER_POS_MOVE_TO_PS2;
**
**			/* Add 2 line By O.Kimoto 1999/02/09 */
**			backward_step_error = BackWardStepErrorFromReady;
**			Paper.BackWardStepsFromFeedOut = 0;
**
**			PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);	/* 12.2mm + 3.5mm *//* EndMark By O.Kimoto 1999/02/09 */
**
**#else
****	Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
****	Paper.Position = PAPER_POS_FEED_OUT;
**#endif
**			ChangeRxMotorPhase();
**
**			CMN_DisableInterrupt();
**
**#if (0)
**** 		/* イベント空振りフラグの見方を変更します。
**** 		** by O.Kimoto 1999/02/18
**** 		*/
**** 			if (!(PrinterEventStatus & PRT_EVT_DOC_PRINT_POS)) {
**** 				wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_READY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
**** 			}
**#else
**			if (!PrinterEventStatus) {
**				wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
**			}
**#endif
**
**			/* カッターエラーが見れていない！
**			** by O.Kimoto 1999/03/09
**			*/
**			if (PRN_PrintErrorHaltRequest() == NG) {	/* プリンターエラーチェック */
**				return;
**			}
**
**			PrinterEventStatus &= ~PRT_EVT_DOC_PRINT_POS;
**			PrinterEventStatus &= ~PRT_EVT_ERROR;
**			Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
**			Paper.Position = PAPER_POS_PRINTING;
**			CMN_EnableInterrupt();
#endif
		}
	}
#endif
}

void	PRN_ImageAllClose(void)
{
#if (0)
** 	/* SAKAKI */
** 	PRN_Control.Command = PRN_IDLE_REQ;
** 	PRN_Control.Status = PRN_IDLE;
** 	GaInterruptFlag &= (~INT_PRINTER);
** 	GaInterruptDisable();
** 	PmenOff();	/* RXﾓｰﾀ励磁OFF */
** 	HeatPulseDisable();
#else
	/* HINOKI */
	DMA_RequestMask(DMA_GATEARRAYWRITE_CH);
	DisableIntPrinterTimer();
#endif

}


/*************************************************************************
	module		:[Fコード原稿プリント]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[COMMON]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PRN_Set_Fcode_DataStatus(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
void PRN_Set_Fcode_DataStatus(void)
{
	/* Ｆコード原稿プリント中のステータスをこかします */
	switch (SYS_DocumentPrintItem) {
	case SYS_MEM_SUB_SECURE_FILE: /** Ｆコード親展受信原稿 */
	case SYS_MEM_SUB_BULLETIN_FILE:	/* 掲示板原稿はプリントしても消去しない */
		if (SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].StoredDocBit == 0) {
			if (SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus == SYS_SUB_ADDRESS_BOX_PRINTING) {
				SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
			}
			/* プリント中に受信した場合で先に受信が終了した場合 */
			else if (SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus == SYS_SUB_ADDRESS_BOX_PRT_RX) {
				SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus = SYS_SUB_ADDRESS_BOX_RECEIVING;
			}
			else if (SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus == SYS_SUB_ADDRESS_BOX_PRT_TX) {
				SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus = SYS_SUB_ADDRESS_BOX_TXING;
			}
			SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].MessageStatus = SYS_SUB_ADDRESS_BOX_MSG_EMPTY;
		}
		else {	/* 掲示板原稿または、親展原稿がまだ残っている */
			/* プリント中に受信した場合で先に受信が終了した場合 */
			if (SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus == SYS_SUB_ADDRESS_BOX_PRINTING) {
				SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;
			}
			else if (SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus == SYS_SUB_ADDRESS_BOX_PRT_RX) {
				SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus = SYS_SUB_ADDRESS_BOX_RECEIVING;
			}
			else if (SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus == SYS_SUB_ADDRESS_BOX_PRT_TX) {
				SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus = SYS_SUB_ADDRESS_BOX_TXING;
			}
		}
		break;
	default:
		break;
	}
}


/*************************************************************************
	module		:[ソフトコーデック（デコード）初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[COMMON]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PRN_SoftWareDecodeInitial(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
void	PRN_SoftWareDecodeInitial(void)
{
#if (0)
** 	/* SAKAKI */
** 	DecodeA_buffer = &PRN_RL1;
** 	DecodeB_buffer = &PRN_RL2;
** 	PRN_RL1.Cout = 0;
** 	PRN_RL1.Data = &RL_Buffer[0];
** 	PRN_RL1.Flag = 0;
** 	PRN_RL2.Cout = 0;
** 	PRN_RL2.Data = &RL_Buffer[RLBUF_SIZE];
** 	PRN_RL2.Flag = 0;
** 	ReductionFromHfine = 0;
** 	PrintDecodeData.Coding = MEM_CheckStoreCode(&PrintIndex);
** 	PrintDecodeData.K_Para = 0;
** 	PrintDecodeData.DecData.Byte.H = 0;
** 	PrintDecodeData.DecData.Byte.L = 0;
** 	PrintDecodeData.DecData.Word = 0;
** 	PrintDecodeData.DecBits = 0;
** 	PrintDecodeData.Line_Cntr = 0;
** 	PrnRp.Buf = (UBYTE*)(MEM_CalculateSoftAddress(PrintExecReadData.ExecBlockNo));
** 	PrnRp.Adr = 0;
** 	PrnRp.Bit = 1;
** 	PrintDecodeData.Rp = &PrnRp;
** 	ScdcErrFlag = 0;
** 	ScdcEcmBufCnt = 0;
** 	MemReadStatus = 0;
** 	DirectMemTx = 0;
** 	LineByteCnt = 0;
** 	SCD_G3RxResult = 0;
** 	SCD_G3ReadStatus = 0;
** 	DEBUG_SCD_MDM_BufferSkip = 0;
** 	SCD_DirectTx = 0;
** 	SCD_SkipMrEol = 0;
** 	SCD_CarryDownBlock = 0;	/*	キャリアダウンとみなすブロック数		*/
** 	SCD_TxMode = 0;	/*	送信モード（最後に送ったページのモード）	*/
** 	SCD_EcmSize = 0;
** 	SCD_MinimumLineSize = 0;		/*	scd_redc.c	*/
** 	SCD_LastEolDataCount = 0;
** 	SCD_EOL_WriteCount = 0;
** 	tskno_SCD_CTxCodeConvertTask = 0;
** 	SCD_DBG_OldRlSize = 0;		/*	scd_redc.c  1:縮小時に縮小前のRLサイズをオーバーした	*/
** 	SCD_NgRl = 0;					/*	decode.c	PUTRLに渡されたRL値が異常 1､2:デコード中 3､4: 縮小中 */
** 	SCD_DBG_RLOVER = 0;			/*	decode.c	1:MDMデコードした結果ラインサイズをオーバーした*/
** 									/*	decode.c	2:MEMデコードした結果ラインサイズをオーバーした*/
** 									/*	decode.c	3:ECMデコードした結果ラインサイズをオーバーした*/
** 									/*	scd_redc.c	4:縮小後のラインがラインサイズオーバーした */
** 	SCD_DBG_PMODE = 0;			/*	encode.c	5:エンコード時ラインの最後でP_MODEがきた*/
** 	SCD_DBG_ENC_RLSIZE = 0;		/*	encode.c	1:ＭＲラインのエンコードでラインサイズオーバー */
** 									/*				3:ＭＨラインのエンコードでラインサイズオーバー */
** 	SCD_CarryDownByteCnt = 0;
** 	SCD_DirectRx = 0;
** 	SCD_Det_Rcp = 0;
** 	ReductionFromR12 = 0;
#else
	/* HINOKI */
	PRN_RL1.Cout = 0;
	PRN_RL1.Data = &RL_Buffer[RLBUF_DEC_B4];
	PRN_RL1.Flag = 0;
	DecodeA_buffer = &PRN_RL1;
	PutRL(DecodeA_buffer,(UWORD)RLBUF_SIZE_B4,0);	/* 全白イメージサイズをセットする */

	PRN_RL2.Cout = 0;
	PRN_RL2.Data = &RL_Buffer[(RLBUF_DEC_B4 + RLBUF_SIZE_B4)];
	PRN_RL2.Flag = 0;
	DecodeB_buffer = &PRN_RL2;
	PutRL(DecodeB_buffer,(UWORD)RLBUF_SIZE_B4,0);	/* 全白イメージサイズをセットする */

	ReductionFromHfine = 0;
	PrintDecodeData.Coding = MEM_CheckStoreCode(&PrintIndex);
	PrintDecodeData.K_Para = 0;
	PrintDecodeData.DecData.Byte.H = 0;
	PrintDecodeData.DecData.Byte.L = 0;
	PrintDecodeData.DecData.Word = 0;
	PrintDecodeData.DecBits = 0;
	PrintDecodeData.Line_Cntr = 0;
	PrnRp.Buf = (UBYTE*)(MEM_CalculateSoftAddress(PrintExecReadData.ExecBlockNo));
	PrnRp.Adr = 0;
	PrnRp.Bit = 1;
	PrintDecodeData.Rp = &PrnRp;
	ScdcErrFlag = 0;
	ScdcEcmBufCnt = 0;
	/* MemReadStatus = 0; Delete by O.Kimoto 1999/01/06 */
	DirectMemTx = 0;
	LineByteCnt = 0;
	SCD_G3RxResult = 0;
	SCD_G3ReadStatus = 0;
	DEBUG_SCD_MDM_BufferSkip = 0;
	SCD_DirectTx = 0;
	SCD_SkipMrEol = 0;
	SCD_CarryDownBlock = 0;	/*	キャリアダウンとみなすブロック数		*/
	SCD_TxMode = 0;	/*	送信モード（最後に送ったページのモード）	*/
	SCD_EcmSize = 0;
	SCD_MinimumLineSize = 0;		/*	scd_redc.c	*/
	SCD_LastEolDataCount = 0;
	SCD_EOL_WriteCount = 0;
	tskno_SCD_CTxCodeConvertTask = 0;
	SCD_DBG_OldRlSize = 0;		/*	scd_redc.c  1:縮小時に縮小前のRLサイズをオーバーした	*/
	SCD_NgRl = 0;					/*	decode.c	PUTRLに渡されたRL値が異常 1､2:デコード中 3､4: 縮小中 */
	SCD_DBG_RLOVER = 0;			/*	decode.c	1:MDMデコードした結果ラインサイズをオーバーした*/
	SCD_DBG_PMODE = 0;			/*	encode.c	5:エンコード時ラインの最後でP_MODEがきた*/
	SCD_DBG_ENC_RLSIZE = 0;		/*	encode.c	1:ＭＲラインのエンコードでラインサイズオーバー */
	SCD_CarryDownByteCnt = 0;
	SCD_DirectRx = 0;
	SCD_Det_Rcp = 0;
	ReductionFromR12 = 0;

	DecMemoryExecBkupData.IndexNo1 = MEM_NO_INDEX;
	DecMemoryExecBkupData.IndexNo2 = MEM_NO_INDEX;
	DecMemoryExecBkupData.ExecBlockNo = MEM_NO_INDEX;
	DecMemoryExecBkupData.NextBlockNo = MEM_NO_INDEX;
#endif
}

void	SetPrintModeParameterEveryPage(void)
{
#if (0)
** 	/* SAKAKI */
** 	PmenOn();
** 	PrintMotorFw();
** 	PrintMotorPhase12();
** 	PrintMotorSpeed(PRINT_200PPS);
** 	PrintMotorStepSet(2);
** 	if (SYB_MaintenanceSwitch[MNT_SW_E7] & PRINT_MOTOR_PHASE_CHANGE) {
** 		PrintMotorPhase2();
** 		PrintMotorSpeed(PRINT_100PPS);
** 		PrintMotorStepSet(1);
** 	}
** 	else {
** 		PrintMotorPhase12();
** 		PrintMotorSpeed(PRINT_200PPS);
** 		PrintMotorStepSet(2);
** 	}
** 	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
** 		PRN_Control.Command = PRN_IDLE_REQ;
** 		PRN_Control.Error |= PRN_COVER_OPEN_ERROR;
** 	}
** 	DecodeWaitFlag = DecodeWaitCommandFlag = 0;
** 	ReadPointWaitFlag = 0;
** 	PRN_Control.WhiteLineDetect = 0;
** 	PRN_Control.ReprintLineCount = 0;
** 	PRN_Control.PrintLineCount = 0;
** 	PRN_Control.Status = PRN_PRINT;
** 
** 	if ((PRN_Control.PrintMode == SYS_NORMAL) && (PRN_Control.UseType == 1) && CHK_UNI_SmoothingNormal()) {
** 		BK1_1_Status &= 0xbf;	/*ｽﾑｰｼﾞﾝｸﾞ*/
** 		outpw(BK1_1_PORT,BK1_1_Status);
** 		BK4_1_Status = 0x00;	/* 検索コードレジスタ１ */
** 		outpw(BK4_1_PORT,BK4_1_Status);
** 		BK4_2_Status = 0x00;	/* 検索コードレジスタ２ */
** 		outpw(BK4_2_PORT,BK4_2_Status);
** 		BK4_3_Status = 0x00;	/* 検索コードレジスタ３ */
** 		outpw(BK4_3_PORT,BK4_3_Status);
** 		BK4_4_Status = 0x00;	/* 検索コードレジスタ４ */
** 		outpw(BK4_4_PORT,BK4_4_Status);
** 		BK4_5_Status = 0x00;	/* 検索コードレジスタ５ */
** 		outpw(BK4_5_PORT,BK4_5_Status);
** 		BK4_6_Status = 0x00;	/* 検索コードレジスタ６ */
** 		outpw(BK4_6_PORT,BK4_6_Status);
** 		SUNO_Status = 0x23;	/* スムージング／ノッチレジスタ */
** 		outpw(SUNO_PORT,SUNO_Status);
** 		VNO_Status = 0xff;	/* 縦ノッチレジスタ */
** 		outpw(VNO_PORT,VNO_Status);
** 		HNO_Status = 0xff;	/* 横ノッチレジスタ１ */
** 		outpw(HNO_PORT,HNO_Status);
** 		SYSSR_Status = 0x00;	/* システムステータス（エッジ検出）レジスタ */
** 		outpw(SYSSR_PORT,SYSSR_Status);
** 	}
** 	else {
** 	/*	BK1_1_Status |= 0x40;*/	/*ｽﾙｰ*/
** 		BK1_1_Status &= 0xbf;	/*ｽﾑｰｼﾞﾝｸﾞ*/
** 		outpw(BK1_1_PORT,BK1_1_Status);
** 		BK4_1_Status = 0xff;	/* 検索コードレジスタ１ */
** 		outpw(BK4_1_PORT,BK4_1_Status);
** 		BK4_2_Status = 0xff;	/* 検索コードレジスタ２ */
** 		outpw(BK4_2_PORT,BK4_2_Status);
** 		BK4_3_Status = 0xff;	/* 検索コードレジスタ３ */
** 		outpw(BK4_3_PORT,BK4_3_Status);
** 		BK4_4_Status = 0xff;	/* 検索コードレジスタ４ */
** 		outpw(BK4_4_PORT,BK4_4_Status);
** 		BK4_5_Status = 0xff;	/* 検索コードレジスタ５ */
** 		outpw(BK4_5_PORT,BK4_5_Status);
** 		BK4_6_Status = 0xff;	/* 検索コードレジスタ６ */
** 		outpw(BK4_6_PORT,BK4_6_Status);
** 		SUNO_Status = 0x20;	/* スムージング／ノッチレジスタ */
** 		outpw(SUNO_PORT,SUNO_Status);
** 		VNO_Status = 0x00;	/* 縦ノッチレジスタ */
** 		outpw(VNO_PORT,VNO_Status);
** 		HNO_Status = 0x00;	/* 横ノッチレジスタ１ */
** 		outpw(HNO_PORT,HNO_Status);
** 		SYSSR_Status = 0xff;	/* システムステータス（エッジ検出）レジスタ */
** 		outpw(SYSSR_PORT,SYSSR_Status);
** 	}
** 
** 	KORITU_W_Status	= 0xff;	/* 孤立点レジスタ１ */
** 	outpw(KORITU_W_PORT,KORITU_W_Status);
** 	KORITU_B_Status = 0xff;	/* 孤立点レジスタ２ */
** 	outpw(KORITU_B_PORT,KORITU_B_Status);
** 
** 	switch (PRN_Control.PrintMode) {
** 	case SYS_NORMAL:
** 		PrintModeCountWork = 3;
** 		break;
** 	case SYS_FINE:
** 	case SYS_GRAY16:
** 	case SYS_GRAY16_SEP:
** 	case SYS_GRAY64:
** 	case SYS_GRAY64_SEP:
** 		PrintModeCountWork = 1;
** 		break;
** 	case SYS_SFINE:
** 		PrintModeCountWork = 0;
** 		break;
** 	}
** 	PreheatContCount = SYB_MachineUniqSwitch[UNIQ_SW_F5];
** 	PreheatContCountSCN = SYB_MachineUniqSwitch[UNIQ_SW_F8];
** 	PreheatStopCount = SYB_MachineUniqSwitch[UNIQ_SW_F6];
** 	PreheatStopCountSCN = SYB_MachineUniqSwitch[UNIQ_SW_F9];
** 	PRN_ResonanceStopCount = 0;
#else
	/* HINOKI */
	switch (PageQ.Mode) {
	case SYS_NORMAL:
		PrintModeCountWork = 0;
		break;
	case SYS_FINE:
	case SYS_GRAY16:
	case SYS_GRAY16_SEP:
	case SYS_GRAY64:
	case SYS_GRAY64_SEP:
		PrintModeCountWork = 0;
		break;
	case SYS_SFINE:
		PrintModeCountWork = 0;
		break;
	}

	DecodeWaitFlag = DecodeWaitCommandFlag = 0;

#endif

}


void	SetPrintSizeParameterEveryPage(void)
{
#if (0)
** 	/* SAKAKI */
** 	UWORD	i;
** 
** 	switch(PRN_Control.PrintSize) {
** 
** 	case SYS_DOCUMENT_A3_SIZE:
** 		PrintDecodeData.Img_Size = 2432;
** 		PRN_OriginalImageSize = 2432;
** 		PRN_ReductionImageSize = 2432;
** 		RL_Buffer[0] = 0x89;
** 		RL_Buffer[1] = 0x80;
** 		RL_Buffer[2] = 0x00;
** 		RL_Buffer[3] = 0x00;
** 		if (PRN_Control.PaperSize == SYS_A4_PAPER) {
** 			PRN_Control.ReductionType = A3_TO_A4;
** 			SetSkipIntRom(A3_TO_A4, &PRN_LineSkipData);
** 			ParallelDataA4();
** 			PRN_ReductionImageSize = 1728;
** 			PRN_LineDMA.Counter = 108;
** 			/* イメージデータのGate Arrayラインバッファ格納位置設定 */
** 			TRISA_Status = 19;	/* 入力データスタートアドレスレジスタ */
** 			outpw(TRISA_PORT,TRISA_Status);
** 			TRIEA_Status = 234;	/* 入力データエンドアドレスレジスタ */
** 			outpw(TRIEA_PORT,TRIEA_Status);
** 		}
** 		else {
** 			PRN_Control.ReductionType = A3_TO_B4;
** 			SetSkipIntRom(A3_TO_B4, &PRN_LineSkipData);
** 			ParallelDataB4();
** 			PRN_ReductionImageSize = 2048;
** 			PRN_LineDMA.Counter = 128;
** 			TRISA_Status = 0;	/* 入力データスタートアドレスレジスタ */
** 			outpw(TRISA_PORT,TRISA_Status);
** 			TRIEA_Status = 255;	/* 入力データエンドアドレスレジスタ */
** 			outpw(TRIEA_PORT,TRIEA_Status);
** 		}
** 		break;
** 	case SYS_DOCUMENT_B4_SIZE:
** 		ParallelDataB4();
** 		PrintDecodeData.Img_Size = 2048;
** 		PRN_OriginalImageSize = 2048;
** 		PRN_ReductionImageSize = 2048;
** 		PRN_LineDMA.Counter = 128;
** 		TRISA_Status = 0;	/* 入力データスタートアドレスレジスタ */
** 		outpw(TRISA_PORT,TRISA_Status);
** 		TRIEA_Status = 255;	/* 入力データエンドアドレスレジスタ */
** 		outpw(TRIEA_PORT,TRIEA_Status);
** 		RL_Buffer[0] = 0x88;
** 		RL_Buffer[1] = 0x00;
** 		RL_Buffer[2] = 0x00;
** 		RL_Buffer[3] = 0x00;
** 		if (PRN_Control.PaperSize == SYS_A4_PAPER) {
** 			PRN_Control.ReductionType = B4_TO_A4;
** 			SetSkipIntRom(B4_TO_A4, &PRN_LineSkipData);
** 			ParallelDataA4();
** 			PRN_ReductionImageSize = 1728;
** 			PRN_LineDMA.Counter = 108;
** 			/* イメージデータのGate Arrayラインバッファ格納位置設定 */
** 			TRISA_Status = 19;	/* 入力データスタートアドレスレジスタ */
** 			outpw(TRISA_PORT,TRISA_Status);
** 			TRIEA_Status = 234;	/* 入力データエンドアドレスレジスタ */
** 			outpw(TRIEA_PORT,TRIEA_Status);
** 		}
** 		else {
** 			PRN_Control.ReductionType = 0;
** 		}
** 		break;
** 	case SYS_DOCUMENT_A4_SIZE:
** 		ParallelDataA4();
** 		PrintDecodeData.Img_Size = 1728;
** 		PRN_OriginalImageSize = 1728;
** 		PRN_ReductionImageSize = 1728;
** 		PRN_LineDMA.Counter = 108;
** 		/* イメージデータのGate Arrayラインバッファ格納位置設定 */
** 		TRISA_Status = 19;	/* 入力データスタートアドレスレジスタ */
** 		outpw(TRISA_PORT,TRISA_Status);
** 		TRIEA_Status = 234;	/* 入力データエンドアドレスレジスタ */
** 		outpw(TRIEA_PORT,TRIEA_Status);
** 		PRN_Control.ReductionType = 0;
** 		RL_Buffer[0] = 0x86;
** 		RL_Buffer[1] = 0xc0;
** 		RL_Buffer[2] = 0x00;
** 		RL_Buffer[3] = 0x00;
** 		break;
** 	}
#else
	/* HINOKI */
	UWORD	i;

	switch(PageQ.Size) {
	case SYS_DOCUMENT_B4_SIZE:
		PrintDecodeData.Img_Size = 2048;	/* SCDCで使用 */
		PRN_OriginalImageSize = 2048;		/* 縮小後サイズ */
		PRN_ReductionImageSize = 2048;		/* 縮小前サイズ */
		/* PRN_LineDMA.Counter = 128; */

		/* RL_Bufferの先頭に全白データを挿入 */
#if (0)
** 		RL_Buffer[0] = 0x88;
** 		RL_Buffer[1] = 0x00;
** 		RL_Buffer[2] = 0x00;
** 		RL_Buffer[3] = 0x00;
#else
		RL_Buffer[RLBUF_DEC_B4    ] = 0x88;
		RL_Buffer[RLBUF_DEC_B4 + 1] = 0x00;
		RL_Buffer[RLBUF_DEC_B4 + 2] = 0x00;
		RL_Buffer[RLBUF_DEC_B4 + 3] = 0x00;
#endif

		if (Paper.Size == PAPER_SIZE_A4) {
			PageQ.Reduction = B4_TO_A4;
			SetSkipIntRom(B4_TO_A4, &PRN_LineSkipData);
			PRN_ReductionImageSize = 1728;
		}
		else {
			PageQ.Reduction = 0;
		}
		break;
	case SYS_DOCUMENT_A4_SIZE:
		PrintDecodeData.Img_Size = 1728;
		PRN_OriginalImageSize = 1728;
		PRN_ReductionImageSize = 1728;
		/* PRN_LineDMA.Counter = 128; */
		PageQ.Reduction = 0;

		/* RL_Bufferの先頭に全白データを挿入 */
#if (0)
** 		RL_Buffer[0] = 0x86;
** 		RL_Buffer[1] = 0xc0;
** 		RL_Buffer[2] = 0x00;
** 		RL_Buffer[3] = 0x00;
#else
		RL_Buffer[RLBUF_DEC_B4    ] = 0x86;
		RL_Buffer[RLBUF_DEC_B4 + 1] = 0xc0;
		RL_Buffer[RLBUF_DEC_B4 + 2] = 0x00;
		RL_Buffer[RLBUF_DEC_B4 + 3] = 0x00;
#endif
		break;
	}
#endif
}


/*************************************************************************
	module		:[プリント用ラインバッファ初期化]
	function	:[
		1.MRD9801のプリント用ラインバッファを初期化します。
		（HINOKIはこのバッファに直接書き込めます。）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PageStartB4WhiteLineSet(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
void	PageStartLineB4WhiteLineSet(void)
{
#if (0)
** 	/* SAKAKI */
** 	UWORD	i, j;
** 
** 	PRN_DTC_Completed = NO;
** 	for (j = 0; j < PRINT_IMAGE_BUF_LINE; j++) {
** 		for (i = 0; i < PRINT_IMAGE_BUF_SIZE; i++) {
** 			PRN_ImageBuffer1[j][i] = 0xff;	/* 白セット */
** 		}
** 	}
** 	ImageDataParallelInput();
** 	ParallelDataB4();
** 	TRISA_Status = 0;	/* 入力データスタートアドレスレジスタ */
** 	outpw(TRISA_PORT,TRISA_Status);
** 	TRIEA_Status = 255;	/* 入力データエンドアドレスレジスタ */
** 	outpw(TRIEA_PORT,TRIEA_Status);
** 	DmaDisable();
** 	HeatPulseDisable();
** 	GaInterruptEnable();
** 	GaInterruptFlag |= INT_PRINTER;
** 	PRN_LineDMA.Counter = 128;
** 	PRN_PrintModeCount = PrintModeCountWork = 0;
** 	ImageLineReadPoint = ImageLineStartPoint;
** 	ImageLineWritePoint = (ImageLineStartPoint+7);
** 	PRN_LineDMA.SrcAddress = (UDWORD)&PRN_ImageBuffer1[0][0];
** 	DMA_SetupDMAU(&PRN_LineDMA);
** 	DMA_RequestEnable(DMA_DRAM_PRNCDC_CH);
** 	i = PRINT_IMAGE_BUF_LINE*2;
** 	PRN_LineMemoryStatus = 99;
** 	while ((ImageLineReadPoint != (ImageLineWritePoint-1)) && (i > 0)) {
** 		wai_tsk(1);
** 		i--;
** 	}
** 	wai_tsk(1);
** 	PRN_LineMemoryStatus = 0;
#else
	/* HINOKI */
	UWORD	i, j;
	
	for (j = 0; j < PRINT_IMAGE_BUF_LINE; j++) {
		for (i = 0; i < PRINT_IMAGE_BUF_SIZE; i++) {
			PRN_ImageBuffer1[j][i] = 0x00;	/* 白セット *//* このまま By O.Kimoto 1998/11/10 */
		}
	}

	for ( i = 0; i < 2; i ++) {
		for (j = 0; j < 256; j ++) {
			PrinterBuffer[i][j] = 0; 			/* G/A使用プリンタ・バッファ */
		}
	}

	PRN_PrintModeCount = PrintModeCountWork = 0;
#endif
}


/*************************************************************************
	module		:[Fコード原稿有無チェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[COMMON]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[UWORD PRN_GetFcodeFileNo(UWORD point){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
UWORD	PRN_GetFcodeFileNo(UWORD point)
{
	UWORD	file_no;

	for (file_no = (point+1); file_no <= SYS_SUBADDRESS_BOX_INDEX_MAX; file_no++) {
		if (CMN_CheckLongBitAssign(SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber-1].StoredDocBit, (file_no-1))) {
			PrintIndex.No = file_no;
			return (OK);
		}
	}
	return (NG);
}


/*************************************************************************
	module		:[イメージプリントタクス終了処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PRN_ImagePrintExit(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
void	PRN_ImagePrintExit(void)
{
#if (0)
** 	/* SAKAKI */
** 	PRN_LineMemoryStatus = 0;
** 	PmenOff();	/* RXﾓｰﾀ励磁OFF */
** 	HeatPulseDisable();
** 	exi_tsk();
#else
	/* HINOKI */
	if (tskno_PRN_PrintDataTransTask != 0xffff) {
		del_tsk(&tskno_PRN_PrintDataTransTask);
	}
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
	CMN_DisableInterrupt();
	CL1_DualRestrictionStatus &= ~CL1_PRINTER_IN_USE; /* プリント中リセット */
	CMN_EnableInterrupt();
#endif
	exi_tsk();
#endif

}

#if defined (HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)
/*************************************************************************
	module		:[ストップキーが押されたとき、原稿種類に応じてメインに送る
				 メッセージをセットする
	]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[PRN]
	ProtoType	:[]
	date		:[2002/02/22]
	author		:[高木智史]
*************************************************************************/
void	SetPRN_EndMessage_ofStopKey(void)
{
	PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
	switch (SYS_DocumentPrintItem) {
	case SYS_MEM_MULTI_COPY_FILE:
		if (McopyPtr->SortType == SYS_SORT) {	/*ｿｰﾄ*/
			McopyPtr->ExecutiveNumber = McopyPtr->ReserveNumber;
			McopyPtr->PrintPage = 1;
			MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, PrintIndex.BoxNumber);
			PrinterEndMessage.Message = MSG_PRN_IMAGE_STOP;
		}
		break;
	case SYS_MEM_RX_FILE: /*ﾒﾓﾘ受信原稿*/
#if (PRO_CLASS1 == ENABLE)	/* added by H.Hirao 1999/01/22 */
	case SYS_MEM_CL1_RX_FILE:
#endif
		break;
	case SYS_MEM_SECURE_RX_FILE: /* 親展受信原稿 */
		PrinterEndMessage.Message = MSG_PRN_IMAGE_STOP;
		break;
	case SYS_MEM_SUB_SECURE_FILE:	/*Fｺｰﾄﾞ親展原稿*/
	case SYS_MEM_SUB_BULLETIN_FILE:	/*Fｺｰﾄﾞ掲示板原稿*/
		PRN_Set_Fcode_DataStatus();
		PrinterEndMessage.Message = MSG_PRN_IMAGE_STOP;
		break;
	default: /* その他の原稿 */
		PrinterEndMessage.Message = MSG_PRN_IMAGE_STOP;
		break;
	}
}
/*************************************************************************
	module		:[プリンタエラーが発生したときに原稿種類に応じて
				 メインに送るメッセージを
	]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[PRN]
	ProtoType	:[]
	date		:[2002/02/22]
	author		:[高木智史]
*************************************************************************/
void	SetPRN_EndMessage_ofError(void)
{
	PrinterEndMessage.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
	switch (SYS_DocumentPrintItem) {
	case SYS_MEM_MULTI_COPY_FILE:
		if (McopyPtr->SortType == SYS_SORT) {	/*ｿｰﾄ*/
			PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
		}
		break;
	case SYS_MEM_RX_FILE: /*ﾒﾓﾘ受信原稿*/
#if (PRO_CLASS1 == ENABLE)	/* added by H.Hirao 1999/01/22 */
	case SYS_MEM_CL1_RX_FILE:
#endif
		PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
		break;
	case SYS_MEM_SECURE_RX_FILE: /* 親展受信原稿 */
		PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
		break;
	case SYS_MEM_SUB_SECURE_FILE:	/*Fｺｰﾄﾞ親展原稿*/
	case SYS_MEM_SUB_BULLETIN_FILE:	/*Fｺｰﾄﾞ掲示板原稿*/
		PRN_Set_Fcode_DataStatus();
		PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
		break;
	default: /* その他の原稿 */
		PrinterEndMessage.Message = MSG_PRN_ILLEGAL_ERROR;
		break;
	}
}
#endif