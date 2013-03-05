/*--------------------------------------------------------------------------*/
/*ÉvÉçÉWÉFÉNÉg: POPLAR/ANZU_L												*/
/*ÉÇÉWÉÖ-Éãñº : TIB_PRO.H													*/
/*çÏê¨é“ñº	  : è¨íJê≥é˜													*/
/*ì˙  ït	  : 97.06.24													*/
/*äT  óv	  : É^ÉXÉNÇÃÉvÉçÉgÉ^ÉCÉv										*/
/*èCê≥óöó	  : 															*/
/*--------------------------------------------------------------------------*/

/* ã@éÌï ÉfÉBÉåÉNÉgÉäÇÊÇËì«Ç›çûÇﬁÇÊÇ§ïœçXÅB POPLAR_H à»ç~ÇÃã@éÌÇ≈ÇÕÅA TASKPRIO ÇÊÇËé©ìÆê∂ê¨Ç≥ÇÍÇΩ
* ÉtÉ@ÉCÉãÇì«Ç›çûÇﬁÅB
*
*  Kubo Hiroshi 1997/07/02
*/


/* ÇrÇ`ÇjÇ`ÇjÇhÅ^ÇgÇhÇmÇnÇjÇhà»ç~ÇÃã@éÌÇÕÅAÉ}ÉXÉNÉvÉçÉOÉâÉÄïœçX
** by O.Kimoto 1998/09/12
*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\tib_pro.h"
#else


/************************************************************************
 * ÇoÇnÇoÇkÇ`Çq É^ÉCÉv Ça												*
 ************************************************************************/
#if defined(POPLAR_B)
#include "\src\atlanta\poplar_b\define\tib_pro.h"
#endif

/************************************************************************
 * ÇoÇnÇoÇkÇ`Çq É^ÉCÉv ÇaÇm 1999/05/13 by T.Soneoka						*
 ************************************************************************/
#if defined(POPLR_BN)
#include "\src\atlanta\poplr_bn\define\tib_pro.h"
#endif

/************************************************************************
 * ÇoÇnÇoÇkÇ`Çq É^ÉCÉv Çk												*
 ************************************************************************/
#if defined(POPLAR_L)
#include "\src\atlanta\poplar_l\define\tib_pro.h"
#endif

/************************************************************************
 * ÇoÇnÇoÇkÇ`Çq É^ÉCÉv Çm												*
 ************************************************************************/
#if defined(POPLAR_N)
#include "\src\atlanta\poplar_n\define\tib_pro.h"
#endif

/************************************************************************
 * ÇoÇnÇoÇkÇ`Çq É^ÉCÉv Çg												*
 ************************************************************************/
#if defined(POPLAR_H)
#include "\src\atlanta\poplar_h\define\tib_pro.h"
#endif

/************************************************************************
 * Ç`ÇmÇyÇt É^ÉCÉv Çk													*
 ************************************************************************/
#if defined(ANZU_L)
#include "\src\atlanta\anzu_l\define\tib_pro.h"
#endif

/************************************************************************
 * Ç`ÇmÇyÇt É^ÉCÉv Çu													*
 ************************************************************************/
#if defined(ANZU_V)
/*
**	ANZU_V(≤›¿∞»ØƒFAXµÃﬂºÆ›ïtÇ´”√ﬁŸ)ópÇÃÃß≤ŸÇ…ÇµÇ‹Ç∑ÅBby Y.Tanimoto 1998/03/18
*/
#include "\src\atlanta\anzu_v\define\tib_pro.h"
#endif

/************************************************************************
 * ÇrÇ`ÇjÇ`ÇjÇh															*
 ************************************************************************/
#if defined(SAKAKI)
#include "\src\atlanta\sakaki\define\tib_pro.h"
#endif

/************************************************************************
 * ÇkÇSÇOÇOå„åp															*
 ************************************************************************/
#if defined(POPLAR_F)
#include "\src\atlanta\poplar_f\define\tib_pro.h"
#endif



#if 0
/* Only for backup. Delete after 1997/07/09 if nothing goes wrong. (H.Kubo 1997/07/02) */
void	exi_tsk_irom(void);
void	MAN_IdleTask(void);
void	MAN_Task(void);
void	MAN_TimerTask(void);
void	MAN_SensorTask(void);
void	MAN_DocumentInTask(void);
void	MAN_WatchDocumentSetTask(void);
void	MAN_WatchDocumentOutTask(void);
void	MAN_WatchDocumentFeedTask(void);
void	MAN_WatchDocumentCoverTask(void);
void	MAN_DocumentOutTask(void);
void	SCN_DocumentOutTestTask(void);
void	CMN_WatchTimer10msTask(void);
void	CMN_WatchTimer10msEventTask(void);
void	CMN_MAN_Timer10msTask(void);
void	CMN_EventToMessageTask(void);
void	CMN_BuzzerTask(void);
void	CMN_EndBuzzerTask(void);
void	CMN_EndBuzzerExit(void);
void	CMN_HoldAlarmTask(void);
void	CMN_ErrorAlarmTask(void);
void	CMN_ErrorAlarmExit(void);
void	CMN_ErrorEndlessAlarmTask(void);
void	CMN_ErrorEndlessAlarmExit(void);
void	CMN_HungUpErrorAramTask(void);
void	CMN_HungUpErrorAramExit(void);
void	CMN_HoldEndBuzzerTask(void);
void	CMN_MultiTimer10msTask(void);
void	ATD_FilterOnOffDetectTask(void);
void	ATD_CheckFilter1OffTask(void);
void	ATD_CheckFilter2OffTask(void);
void	ATD_CheckFilter3OffTask(void);
void	ATD_ToneDetectPattern0Task(void);
void	ATD_ToneDetectPattern0Exit(void);
void	ATD_ToneDetectPattern1Task(void);
void	ATD_LC_OffCheckTask(void);
void	ATD_CheckDSETask(void);
void	ATD_CheckStopTask(void);
void	ATD_WatchTimer10msEventTask(void);
void	ATD_CheckToneTask(void);
void	ATD_CheckToneExit(void);
void	CDC_EncodePageTask(void);
void	CDC_DecodePageTask(void);
void	CDC_STxCodeConvertPageTask(void);
void	CDC_STxCodeConvertPageExit(void);
void	CDC_CTxCodeConvertPageTask(void);
void	CDC_MTxCodeConvertPageTask(void);
void	CDC_MRxCodeConvertPageTask(void);
void	CDC_DataTransferPageTask(void);
void	CDC_DecodeJournalPageTask(void);
void	SCN_Task(void);
void	SCN_DMA_WriteTask(void);
void	SCN_WatchDocumentFeedTask(void);
void	SCN_WatchDocumentCoverTask(void);
void	SCN_WatchDocumentExitTask(void);
void	SCN_GearBackLashTask(void);
void	SCN_GearBackLashExit(void);
void	SCN_WatchGearBackLashTask(void);
void	SCN_MotorTestTask(void);
void	SCN_StampTestTask(void);
void	NCU_Task(void);
void	NCU_TaskExit(void);
void	NCU_DetectCalledTask(void);
void	NCU_DetectCalledExit(void);
void	NCU_TelephoneHookCheckTask(void);
void	NCU_DetectFnetTask(void);
void	NCU_FrequencyCheckTask(void);
void	NCU_TimeUpTask(void);
void	NCU_TelephoneOperationTask(void);
void	NCU_TelephoneOperationExit(void);
void	NCU_FaxTadAutoSwitchTask(void);
void	NCU_FaxTadAutoSwitchExit(void);
void	NCU_TelephoneExecuteTask(void);
void	NCU_TelephoneExecuteExit(void);
void	NCU_ReceiveDTMFTask(void);
void	NCU_ReceiveDTMFExit(void);
void	NCU_DetectSilentTask(void);
void	NCU_DetectSilentExit(void);
void	NCU_DialInAutoSwitchTask(void);
void	NCU_TransRBTAndDetCNGTask(void);
void	NCU_TransRBTAndDetCNGExit(void);
void	NCU_GenerateRingSignalTask(void);
void	NCU_GenerateRingSignalExit(void);
void	NCU_DetectNoiseTask(void);
void	NCU_DetectDSETask(void);
void	MDM_TxFskFrameControlTask(void);
void	MDM_TxFskFrameControlExit(void);
void	MDM_RxFskFrameControlTask(void);
void	MDM_RxFskFrameControlExit(void);
void	MDM_FlagDetectTask(void);
void	MDM_FcsDetectTask(void);
void	MDM_ModemInterruptTask(void);
void	MDM_EncodeDMA_TC_DetectTask(void);
void	MDM_DecodeDMA_TC_DetectTask(void);
void	MDM_ModemDMA_TC_DetectTask(void);
void	MDM_ModemStatusCheckTask(void);
void	MDM_DetectDtmfTask(void);
void	MDM_TxEcmFrameControlTask(void);
void	MDM_RxEcmControlTask(void);
void	MDM_RxDeviceControlTask(void);
void	MDM_MTxReadDMA_Task(void);
void	MDM_FskTxTask(void);
void	MDM_PixTxTask(void);
void	MDM_BackupRamToEcmBufTask(void);		/* 1997/02/05  By T.Yamaguchi */
void	MDM_BackupRamToEcmBufTaskExit(void);	/* 1997/02/05  By T.Yamaguchi */
void	FCM_Task(void);
void	LST_PrintTask(void);
void	LST_PrinterErrorDetectTask(void);
void	OPR_Task(void);
void	OPR_KeyTask(void);
void	OPR_SubMessageReceiveTask(void);
void	OPR_DisplayFlashTask(void);
void	OPR_CheckOnetouchSheetTask(void);
void	SCDC_RxEcmControlTask(void);
void	SCDC_MTxCodeConvertTask(void);
void	SCDC_EcmDecodeTask(void);
void	SCD_G3_MemRxTask(void);
void	SCD_CTxCodeConvertPageTask(void);
void	PRN_ImagePrintTask(void);
void	PRN_ImagePrintExit(void);
void	PRN_DocumentOutTask(void);
void	PRN_DataTxTask(void);
void	PRN_DataTxExit(void);
void	PRN_MemoryDataTxTask(void);
void	PRN_JournalPrintTask(void);
void	PRN_JAMRecoverTask(void);
void	PRN_PrinterResetTask(void);
void	CL1_Task(void);
void	CL1_RsControlTask(void);
void	CL1_CommandReceiveTask(void);
void	CL1_HdlcReceiveTask(void);
void	CL1_HdlcReceiveExit(void);
void	CL1_DataReceiveTask(void);
void	CL1_DataReceiveExit(void);
void	CL1_DummyDataTxTask(void);
void	CL1_CEDTxTask(void);
void	CL1_CEDTxExit(void);
void	CL1_AutoDialTask(void);
void	CL1_DialAbortTask(void);
void	CL1_FaxComTask(void);
void	CL1_FaxComExit(void);
void	CL1_RsTimerTask(void);
void	DPR_UpLoadRxTask(void);
void	DPR_RemoteFuncExecTask(void);
void	DPR_RemoteDataExecTask(void);
void	DPR_InsteadOfSlaveTask(void);
void	DPR_FuncReceiveMessageTask(void);
void	DPR_DataReceiveMessageTask(void);
void	DPR_FuncSendMessageTask(void);
void	DPR_DataSendMessageTask(void);
void	DPR_CopyECM_BufferTask(void);
void	PRN_FuserTempTask(void);
void	PRN_PaperSensorTask(void);
void	PRN_CheckTonerTask(void);
void	PRN_HighVoltageTask(void);
void	PRN_HighVoltageExit(void);
void	PRN_PaperFeedTask(void);
void	PRN_PrinterErrorDetectTask(void);
void	PRN_PrinterWarmUpTask(void);
void	PRN_WarmUpControlTask(void);
void	PRN_WarmUpControlExit(void);
void	PRN_WarmUpDcoumentOutTask(void);
void	PRN_ListDocumentOutTask(void);
void	PRN_ListDocumentOutExit(void);
void	PRN_GetResistTask(void);
void	SCN_MirrorMoveTask(void);
void	SCN_WatchDocumentMirrorTask(void);	/* 1997/03/19 T.Nose */
void	SCN_DocumentPageCountTask(void);
void	ROT_Task(void);
void	SCN_ScanningTask(void);
void	PRN_ExecuteTask(void);
#endif

#endif
