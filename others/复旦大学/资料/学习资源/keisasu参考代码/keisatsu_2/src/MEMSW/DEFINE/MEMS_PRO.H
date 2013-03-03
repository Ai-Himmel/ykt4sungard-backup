/*********************************************:
 * MEMS_PRO.H
 * メモリースイッチ参照関数のプロトタイプ宣言
 * 1996/04/15 Eguchi
 * この関数を各プロジェクトの各ファイルでインクルード
 * する場合は、必ずその前にProduct.Hをインクルードしてください.
 *********************************************/
#ifndef	MEMS_PRO_H
	#define	MEMS_PRO_H	1

/* CMNMEM_A.C */
unsigned char far CHK_PBX(void);
unsigned char far CHK_DialToneOrTimeupAvailable(void);
unsigned char far CHK_CED_Detect(void);
unsigned char far CHK_AFTER_DIAL_DELAY_TIME(void);
unsigned char far CHK_DP_Method(void);

unsigned char far CHK_PBX_PauseTime(void);

unsigned char far CHK_PBX1(void);	/* Add By O.Kimoto 1996/12/17 */
unsigned char far CHK_PBX2(void);	/* Add By O.Kimoto 1996/12/17 */
unsigned char far CHK_PBX3(void);	/* Add By O.Kimoto 1996/12/17 */
unsigned char far CHK_PBX4(void);	/* Add By O.Kimoto 1996/12/17 */
unsigned char far CHK_PBX5(void);	/* Add By O.Kimoto 1996/12/17 */
unsigned char far CHK_PBX6(void);	/* Add By O.Kimoto 1996/12/17 */
unsigned char far CHK_PBX7(void);	/* Add By O.Kimoto 1996/12/17 */
unsigned char far CHK_PBX8(void);	/* Add By O.Kimoto 1996/12/17 */
unsigned char far CHK_DP_Enable(void);	/* Add by M.H 1999/10/05 */

void far CHK_SetPBX(unsigned char data);
void far CHK_SetPBX1(unsigned char data);	/* 1996/12/20 Y.Murata */
void far CHK_SetPBX2(unsigned char data);
void far CHK_SetPBX3(unsigned char data);
void far CHK_SetPBX4(unsigned char data);
void far CHK_SetPBX5(unsigned char data);
void far CHK_SetPBX6(unsigned char data);
void far CHK_SetPBX7(unsigned char data);
void far CHK_SetPBX8(unsigned char data);

unsigned char far CHK_RingFreqAvailable(void);
unsigned char far CHK_ContinueRing(void);
unsigned char far CHK_DoubleRingAvailable(void);
unsigned char far CHK_NoneCallCI_Count(void);
UWORD far CHK_TEL_RelayOffAfterCI_Ignore(void);
unsigned char far CHK_1300RxAvailable(void);

unsigned char far CHK_PBX_EXT(void);			/* Ade By O.Kimoto 1997/11/04 */
void far CHK_SetPBX_EXT(unsigned char data);	/* Add By O.Kimoto 1997/11/04 */

#if defined(STOCKHM2)	/* ダイヤルトーン検出対応 by SMuratec 夏 2004/7/13 */
void far CHK_SetDialToneOrTimeAvailable(UBYTE);
#endif	/* End of defined(STOCKHM2) */

/* CMNMEM_B.C */
unsigned char far CHK_TxBPS(void);
unsigned char far CHK_V29EPtoneAvailable(void);
unsigned char far CHK_Override1stDIS(void);
unsigned char far CHK_FallbackPattern(void);
unsigned char far CHK_BusyToneDetect(void);
unsigned char far CHK_T23Attenation(void);
unsigned char far CHK_T23DCS_AfterTCF(void);
UWORD far CHK_T41CFR_AfterPIX(void);
unsigned char far CHK_DIS_AfterDCS(void);
unsigned char far CHK_ECM_TxInterval(void);
UWORD far CHK_ECM_ResponseTime(void);
unsigned char far CHK_TTI_TxAvailable(void);
unsigned char far CHK_CalendarTypeChange(void);
unsigned char far CHK_TxToPrinterRxEnable(void);
unsigned char far CHK_DCS_V33AllHold(void);
unsigned char far CHK_SpeedHandshake144(void);
unsigned char far CHK_SpeedHandshake96(void);
unsigned char far CHK_SpeedHandshakeV8(void);
unsigned char far CHK_RTN_AutoReTransmitDisable(void);
unsigned char far CHK_TerminalInformationNotTx(void);
unsigned char far CHK_V34TransmitDisable(void);	/* Add By O.Kimoto 1999/04/20 */
unsigned char far CHK_OverrideANSam(void);		/* Add By O.Kimoto 1999/04/20 */

unsigned char far CHK_AfterEOR(void);
unsigned char far CHK_ErrorRedialAvailble(void);
unsigned char far CHK_TxForceStop(void);
unsigned char far CHK_TSI_Figur(void);
unsigned char far CHK_SpeedHandshake(void);
unsigned char far CHK_RelayedBroadcastAvailable(void);
unsigned char far CHK_SpeedDialSparateSet(void);
unsigned char far CHK_ScannerDivideTransmit(void);
unsigned char far CHK_TerminalNameTx(void);
unsigned char far CHK_TerminalNumberTx(void);
unsigned char far CHK_TerminalAdditionalTx(void);
unsigned char far CHK_TerminalInformationEnable(void);
unsigned char far CHK_V17FallBackPattern(void);

/* CMNMEM_C.C */
unsigned char far CHK_RxBPS(void);
UWORD far CHK_WaitAfterDIS(void);
unsigned char far CHK_RTN_TxRate(void);
unsigned char far CHK_TCF_AfterCFR(void);
unsigned char far CHK_DIS_ExpandFrameTx(void);
unsigned char far CHK_PostMsgErrRxDocPrint(void);
unsigned char far CHK_T1_Timer(void);
unsigned char far CHK_PrintRx3mOver(void); /* 1998/12/15 by T.Soneoka */
#if !defined(KAKI)
unsigned char far CHK_BuckupPaperSizeRcmp(void);/*By Y.Suzuki 1999/10/21*/
#endif

/* CMNMEM_D.C */
unsigned char far CHK_CarrierDetectAvailable(void);
unsigned char far CHK_V17EqualizerHold(void);
unsigned char far CHK_LinkEqualizerAvailable(void);
unsigned char far CHK_TerminateFlag(void);
unsigned char far CHK_EYE_Q_Slice144(void);
unsigned char far CHK_EYE_Q_Slice120(void);
unsigned char far CHK_EYE_Q_Slice96(void);
unsigned char far CHK_EYE_Q_Slice72(void);
unsigned char far CHK_EYE_Q_Slice48(void);
unsigned char far CHK_EYE_Q_Slice24(void);
unsigned char far CHK_EYE_Q_CheckAvailable(void);
unsigned char far CHK_EYE_Q_SliceAvailable(void);
unsigned char far CHK_LongPreamble(void);
unsigned char far CHK_HIGH_MODE_CATCH(void);
unsigned char far CHK_TAD_DetectLevel(void);

/* CMNMEM_E.C */
unsigned char far CHK_DocumentLengthLimit(void);
unsigned char far CHK_DocumentWidthFull(void);
unsigned char far CHK_ShadingFixAvailable(void);

/* CMNMEM_F.C */
unsigned char far CHK_HeatPulseAdjust(void);
unsigned char far CHK_ErrorLineReplace(void);

/* CMNMEM_G.C */
unsigned char far CHK_TEL1FaxTransferAvailable(void);
unsigned char far CHK_TEL2FaxTransferAvailable(void);
unsigned char far CHK_TAD_FaxReadyOnhookTransfer(void);
unsigned char far CHK_600PhoneAvailable(void);
unsigned char far CHK_TEL_PushToneAvailable(void);
unsigned char far CHK_AfterDialCML_OFF_Time(void);
unsigned char far CHK_RemoteTransferForcedDTMF(void);	/* REMOTE_RX_FUNC */
unsigned char far CHK_DialInGRSOffLRelayOff(void);
unsigned char far CHK_OnhookOffhookTime(void);
unsigned char far CHK_OnHookTransferRxPeriod(void);
unsigned char far CHK_OffhookHookingTime(void);
unsigned char far CHK_TAD_CNG_DetectAvailable(void);
unsigned char far CHK_RemoteTransferDial(void);			/* REMOTE_RX_FUNC */
unsigned char far CHK_RemoteTransferOnHook(void);		/* REMOTE_RX_FUNC */
unsigned char far CHK_RemoteTransfer3ThNumber(void);	/* REMOTE_RX_FUNC */
unsigned char far CHK_TAD_SilentPeriod(void);
unsigned char far CHK_TAD_SilentTime(void);
unsigned char far CHK_CNG_DetectPeriod(void);
unsigned char far CHK_CNG_SilentDetectPeriod(void);
unsigned char far CHK_HANGUP_ALARM_AVAILABLE(void);
unsigned char far CHK_RemoteTransferDialNumMore(void);	/* REMOTE_RX_FUNC */
unsigned char far CHK_RemoteTransferDialOne(void);		/* REMOTE_RX_FUNC */
unsigned char far CHK_AddToMinOnTime(void);			/* Add by K.Okada 1999/12/06 */
unsigned char far CHK_ValueAddedToMinOnTime(void);	/* Add by K.Okada 1999/12/06 */
unsigned char far CHK_OnHookTransferRxTime(void);	/* Add By M.Tachibana 1998/10/25 */
unsigned char far CHK_RemoteTransferDialNumber1(void);	/* REMOTE_RX_FUNC */
unsigned char far CHK_RemoteTransferDialNumber2(void);	/* REMOTE_RX_FUNC */
unsigned char far CHK_RemoteTransferDialTimer(void);	/* REMOTE_RX_FUNC */
unsigned char far CHK_RemoteTransNum3_SharpAster(void);	/* REMOTE_RX_FUNC *//* YAWARAから移植 by J.Kishida 2003/11/14 */

/* CMNMEM_H.C */
unsigned char far CHK_StopMemCheckMsg(void);
unsigned char far CHK_CheckMessagePrint(void);
unsigned char far CHK_DocumentPrintAfterMemTx(void);
unsigned char far CHK_PowerDownMessagePrint(void);
unsigned char far CHK_DialListPrint(void);
unsigned char far CHK_SecureMailReportPrint(void);
unsigned char far CHK_LineMonitor(void);
unsigned char far CHK_ErrorLineDisplay(void);
unsigned char far CHK_CommunicationSpeedDisplay(void);
unsigned char far CHK_PmonitorAutoPrint(void);
unsigned char far CHK_ErrorPmonitorAutoPrint(void);
unsigned char far CHK_TcrWithDocumentON(void);		/* Add by K.Okada 1999/06/23 */
unsigned char far CHK_AutoRxKeyON(void);			/* Add by Y.Matsukuma 1999/06/23 */
unsigned char far CHK_BatchTxTCR_ON(void);
unsigned char far CHK_DocumentEraseAfterPolling(void);
unsigned char far CHK_TCR_TimePrint(void);
unsigned char far CHK_F_NetSubscriber(void);
unsigned char far CHK_DepartListPrintDate(void);
unsigned char far CHK_RestMemorySizePrint(void);	/* Add By O.Kimoto 1999/03/04 */
unsigned char far CHK_JournalNoPrintLine0(void);				/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
unsigned char far CHK_JournalNoPrintLine1(void);				/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
unsigned char far CHK_JournalNoPrintLine2(void);				/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
unsigned char far CHK_JournalNoPrintLine3(void);				/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
unsigned char far CHK_JournalNoPrintLine4(void);				/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
unsigned char far CHK_JournalNoPrintLine5(void);				/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
unsigned char far CHK_JournalNoPrintLine6(void);				/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
unsigned char far CHK_JournalNoPrintLine7(void);				/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
unsigned char far CHK_JournalNoPrintLineEXT(void);			/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
unsigned char far CHK_JournalPrintTitle(void);			/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
/* CMNMEM_J.C */
unsigned char far CHK_ForeignApprovalDEU(void);		/* 1999/04/09 Y.Murata */
unsigned char far CHK_ForeignApprovalFRA(void);		/* 1999/04/09 Y.Murata */
unsigned char far CHK_ForeignApprovalBEL(void);		/* 1999/04/09 Y.Murata */
unsigned char far CHK_OPTION_CLASS1(void);
unsigned char far CHK_OPTION_PRINTER(void);
unsigned char far CHK_OPTION_288K(void);

#endif
