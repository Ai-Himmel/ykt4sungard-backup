/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_IDLE.C                                *
* 1996/10/23 By M.Kotani                                            *
********************************************************************/
void MAN_IdleTask(void);
/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_INIT.C                                *
* 1996/10/23 By M.Kotani                                            *
********************************************************************/
void MAN_InitializeRAM(void);
void MAN_InitializeMailBox(void);
void InitializeMachineStatus(void);
void MAN_InitializeTaskValue(void);
void MAN_InitializeSemapho(void);
void MAN_InitializeTaskCreate(void);
void MAN_InitializeDevice(void);
void MAN_MultiLinePowerOnInitial(void);
void ClearOptionModemDataArea(UBYTE number);
void MAN_InitializeScanner(void);
#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/15*/
void INI_SleepSystem(void);
void INI_WakeUpSystem(void);
#endif
/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_MAIN.C                                *
* 1996/10/23 By M.Kotani                                            *
********************************************************************/
void MAN_Task(void);
void MAN_AfterMessageCheck(void);
void MAN_NextScanStart(void);
void MAN_ClearCommandAreaAfterRlyTx(UBYTE j); /* H.Kubo 1998/01/13 for Relayed Tx report*/
void MAN_ClearCommandAreaAfterLstPrt(void); /* H.Kubo 1998/01/13 for Relayed Tx report*/
#if (PRO_SGP_TEST_ROM == ENABLE) /** By S.Wang 98/07/25 */
void SetSgpDialNumberIncrement(void);
#endif
/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_MSG.C                                 *
* 1996/10/23 By M.Kotani                                            *
********************************************************************/
void MAN_FromDocumentIn(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromSCN_GearBackLashTask(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromDocStore(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromPRN_LST_PrintTask(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromPRN_ImagePrintTask(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromPRN_ResetTask(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromPRN_WarmUpTask(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromPRN_ManualDocInTask(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromPRN_AllPagePrintTask(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
#if (PRO_PRINT_TYPE == THERMAL)
void MAN_FromPRN_RealTimeCopyTask(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
#endif
void MAN_FromSensor(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromTimer(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromNCU_Task(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromOperation(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromFaxcom(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromDocumentOut(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromSCN_StampTestTask(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_From10msTimer(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromClass1(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromCL1Faxcom(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromDPR_RemoteFuncExecTask(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromTestTest(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromSCN_MirrorMoveTask(UWORD item,	UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromMultiTimer(UWORD item,	UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromROT_Task(UWORD item,	UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromSCN_DocOutTestTask(UWORD item,	UWORD message, UWORD sub_message1, UWORD sub_message2);
void MAN_FromFaxcomOption(UWORD	Item, UWORD	Message, UWORD	SubMessage1, UWORD	SubMessage2, UWORD	SubMessage3, UWORD	SubMessage4);
void MAN_FromCipherTask(UWORD item,	UWORD message, UWORD sub_message1, UWORD sub_message2);
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
void MAN_FromSCN_GetShadingTask(UWORD item,	UWORD message, UWORD sub_message1, UWORD sub_message2);
#endif
#if (PRO_PRINT_TYPE == THERMAL)
void MAN_FromSCN_RealTimeCopyStore(UWORD item, UWORD message, UWORD sub_message1, UWORD sub_message2);
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
	UWORD CheckQuickTx(void);
	void SetFaxComStopExecQueue(UWORD queue_no);
	void SetQucikTxStop(UWORD queue_no);
#endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_SUB.C                                 *
* 1996/10/23 By M.Kotani                                            *
* 		MAN_MAIN.c --> MemoryTxDocStoreNG() MultiCopyDocStoreNG()   *
*		MAN_MAIN.c --> MemoryTxDocStoreOK() MultiCopyDocStoreOK()   *
********************************************************************/
void	DeleteScannerCommand(void);
UBYTE	CheckScannerCommand(BYTE CommandNumber);
UBYTE	CheckPollingRxCommand(UBYTE CommandNumber);	/* 1997/03/19  By T.Yamaguchi */
UBYTE	CheckDocStoredCommand(UBYTE CommandNumber);
UBYTE	SYS_FaxComStopSwitch(void);
UBYTE	SYS_TelephoneStopSwitch(void);
UBYTE	SYS_ScannerCopyStopSwitch(void);
UBYTE	SYS_MultiCopyStopSwitch(void);
UBYTE	SYS_ListPrintStopSwitch(void);
UBYTE	SYS_FipStopSwitch(void);
UBYTE	SYS_TAD_StopSwitch(void);
UBYTE	SYS_InterCallStopSwitch(void);
UBYTE	SYS_DocumentStoreStopSwitch(void);
UBYTE	SYS_ImagePrintStopSwitch(void);
void	MemoryTxDocStoreNG(UBYTE command_type);
void	MultiCopyDocStoreNG(void);
void	ManualCopyDocStoreNG(void);
void	MemoryTxDocStoreOK(UBYTE command_type);
void	MultiCopyDocStoreOK(void);
void	ManualCopyDocStoreOK(void);
void	MultiCopyDocStoreMemoryOver(void);
void	ManualCopyDocStoreMemoryOver(void);
void	FcodeDocStoreOK(UBYTE);	/* 1997/03/12  By T.Yamaguchi */
void	FcodeDocStoreNG(UBYTE);	/* 1997/03/12  By T.Yamaguchi */
UBYTE	CheckInitializeKeyON(void);
void	BackupCommandFile(void);				/* 1994/11/16 Y.Murata */
void	BackupMemoryRxPrintFile(void);			/* 1994/11/16 Y.Murata */
void	BackupExecQueueFile(void);				/* 1994/11/24 Y.Murata */
void	BackupSecureFile(void);					/* 1994/11/24 Y.Murata */
void	BackupPollingFile(void);				/* 1994/11/24 Y.Muraat */
void	ClearCipherFile(void);					/* By Y.Suzuki 1998/04/17 */
void	BackupBatchTxFile(void);				/* 1994/12/08 Y.Murata */
void	BackupSubAddressBoxFile(void);
void	BackupCipherFile(void);					/* 1997/06/18  By T.Yamaguchi */
void	BackupDeleteingComOrExecFile(void);		/* 1994/11/25 Y.Murata */
void	InitializeDRAM_Parameter(void);
void	RecoverDRAM_Parameter(void);
void	CreateRelayedReportCommand(UBYTE, UBYTE);	/* 不達通知  竹内 Apr.07.1995 */
void	ExecuteRelayedReportPrint(UBYTE);			/* 不達通知  竹内 Apr.07.1995 */
void	CheckMessageTest(void);
void	MAN_ClearCommunicationError(void);
void	MAN_CheckPrinterOption(void);	/* Add By O.Kimoto 1997/06/13 */
void	MAN_CalcContPollingExecTime(void);	/* Add By O.Kimoto 1997/06/13 */
void	MAN_CheckDRAM_BackUp(void);
UWORD	 SYS_V34ProcedureExecuting(void); /* Added by H.Kubo 1997/07/07 */
void 	SYS_SetV34ProcedureExecute(UBYTE);	/* 1996/03/11 Y.M */ /* Added by H.Kubo 1997/07/07 */
UBYTE	MAN_CheckRedialQueueExist(void);	/* Add By O.Kimoto 1997/07/22 */
void	CipherRxDocPrintNG(void);
void	CipherRxDocStoreOK(void);
void	CipherRxDocStoreMemoryOver(void);
#if (PRO_CL1_TELFAX_LAN == ENABLE)
void	ClearMemoryRxSetting(void);			/* S.Fukui June 19,1998 */
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/09 Y.Murata for KAKI */
	UBYTE CheckQuickMemoryTxOK(UBYTE, UBYTE);
	UBYTE SYS_QuickTxStopSwitch(UBYTE stack_number);
#endif
#if (PRO_PRINTER_RX == ENABLE)
	UBYTE QueryPRxEnable(void); /* added by H.Hirao 1998/11/11 */
	UBYTE QueryPRxEnableWholeCNGDetect(void);	/* Add by O.Kimoto 1999/02/27 */
  #if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
	UBYTE QueryDocStoreEnable(void); /* added by H.Hirao 1998/12/17 */
	UBYTE QueryAutoCalledEnable(UBYTE mode); /* added by H.Hirao 1998/12/26 */
	UBYTE QueryCommunicationStartEnable(UBYTE exec_no);	/* 送信時、「ソウシン」と表示される不具合修正 by O.Kimoto 1999/01/25 */
  #endif
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.4 K.Kawata */
UBYTE QueryPRxEnable(void);
UBYTE QueryPRxEnableWholeCNGDetect(void);
UBYTE QueryWarpAndSecurityDisable(void);
#endif
#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
/*
** ＤＵＡＬ制限変更のため
** スキャナ制限からプリント制限へ変更するため、作り変えます
** 1999/02/18 by T.Soneoka
*/
#if (0)
**UBYTE QueryMultiEnable(void); /* 1999/01/14 by T.Soneoka */
#endif
UBYTE QueryResourceCount(void);
#endif

#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
UBYTE QueryClass1Enable(UBYTE mode);	/* added by H.Hirao 1999/02/01 */
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
UBYTE	MAN_AutoReadyModeChangeEnable(void);	/* by K.Watanabe 1999/01/20 */
void	MAN_AutoChangeReadyMode(void);			/* by K.Watanabe 1999/01/22 */
#endif
#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/19*/
void MAN_ExecEcoMode(void);
void MAN_WakeUpSystemTask(void);
void MAN_SleepSystemTask(void);
void MAN_ExecEcoWakeUp(void);
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
void MAN_ChangeEcoMode(UBYTE eco_on);
#endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_EXEC.C                                *
* 1996/10/23 By M.Kotani                                            *
********************************************************************/
UWORD	GetEmptyExecQueue(void);
void	CancelExecQueue(UBYTE, UBYTE);
UWORD	ScanSetQueue(UBYTE, UBYTE, UBYTE, UWORD );
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/21 */
void	GetExecutingS1Info(UBYTE);
#endif		/* End of (defined (KEISATSU)) */
void	SetCommandToExec(void);
void	DecrementRedialTime(void);
UWORD	GetNextExecNo(void);
UBYTE	SetExecQueueRedialCount(UWORD);
void	SetExecQueueRedialTime(UWORD);
void	ReleaseExecQueueArea(UWORD);
void	SetBatchCommandToExec(void);
void	SetContinuousPollingToExec(void);
void	DeleteContinuousPollingCommand(void);
UWORD	OPT_GetNextExecNo(void);
UBYTE CHK_OPRSameDocumentAccess(UBYTE CommandKind, UBYTE CommandNumber);	/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
UBYTE CHK_MANSameDocumentAccess(UBYTE QueueNumber);							/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/09 Y.Murata for KAKI */
	UBYTE CheckCommandBroadcast(UBYTE command_no);
#endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_TIMR.C                                *
* 1996/10/23 By M.Kotani                                            *
********************************************************************/
void	WriteClockBit(UBYTE, UBYTE);
void	WriteCurrentTime(void);
UBYTE	ReadClockBit(UBYTE);
void	ReadCurrentTime(void);
void	MAN_TimerTask(void);
/* サマータイム用に以下を追加 1995/12/21 Eguchi1*/
void	CalculateMoveSummerTime(UBYTE);
void	CalculateReturnNormalTime(UBYTE);
void	SetSummerTimeStatus(UDWORD);
void	ResetSummerTimeData(UBYTE);
UBYTE	ExecuteSummerTime(void);
void	RTCTestStart(void);
void	RTCTestEnd(void);
void	RTC_IO_WriteEnable(void);
void	RTC_IO_ReadEnable(void);
UBYTE	CheckRTC_TestEnable(void);
#if (PRO_RTC_RX5C338A == ENABLE)
void	RTC_DRV_CE(UBYTE key);
void	RTC_DRV_SCLK(UBYTE key);
void	RTC_DRV_SIO(UBYTE key);
UBYTE	RTC_DRV_GET_SIO(void);
void	RTC_DRV_CLKC(UBYTE key);
void	RTC_IO_Enable(UBYTE is_permit);
void	RTC_Execute(void);
void	RTC_OutputData(UBYTE data);
UBYTE	RTC_InputData(void);
void	ManInitRTC(void);
#endif
/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_SENS.C                                *
* 1996/10/23 By M.Kotani                                            *
********************************************************************/
void	InitializeSensor(void);
void	MAN_SensorTask(void);
void	MAN_InitPrinterSensor(void);
void	MAN_CheckPrinterSensor(void);
void	MAN_PrinterToMachineStatus(UBYTE, UWORD, UBYTE, UBYTE);
void	MAN_CheckAD_CassetteData(UWORD *, UWORD *, UWORD *, UWORD *);
/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_BUZR.C                                *
* 1996/10/30 By K.Watanabe                                          *
********************************************************************/
void	UpdateDisplay(void);
void	UpdateBuzzer(void);
void	EndBuzzer(void);
void	StopEndBuzzer(void);
void	AlarmBuzzer(void);
void	StopAlarmBuzzer(void);
void	HoldBuzzer(void);
void	HungUpBuzzer(void);
void	StopHungUpBuzzer(void);
void	HoldEndBuzzer(void);
#if defined(GBR)
void	AudibleAlarmBuzzer(void);
void	StopAudibleAlarmBuzzer(void);
#endif
#if defined(STOCKHM2) /* 本体鳴動のテスト : by SMuratec C.P 2004/09/24 */
void	CallingBuzzer(void);
void	StopCallingBuzzer(void);
#endif
/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_LED.C                                 *
* 1997/02/13 By K.Watanabe                                          *
********************************************************************/
void	UpdateLED(void);
/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言                                                     *
* File : \src\atlanta\src\MAN_MULT.C                                *
* 1997/06/10 Y.Murata                                               *
********************************************************************/
UWORD MAN_CheckMultiLineReceiveEnable(UBYTE StackNo, UBYTE ReceiveMode);
UWORD MAN_GetMultiLineReceiveNumber(UBYTE StackNo);
UBYTE MAN_CheckMemRxPrintStatus(UWORD No);
UWORD MAN_GetMemoryRxPrintNumber(void);
void MAN_CheckFaxComOption(void);
void MAN_SetJournalMultiLine(void);
void MAN_OptFactoryFunctionCommand(struct SYS_FactoryOptModemData_t *com_data);
void MAN_OptFactoryFunctionPeriod(struct SYS_FactoryOptModemData_t *com_data);
void MltDeleteComFileExecQueueFile(UBYTE stack_number);
void MAN_MltFaxComStop(void);
void MAN_SetRemoteID_ToJournal(UBYTE stack_number);
/* void MAN_SetCOMEXEC_ModeToJournal(UWORD que_num); *//* 引数追加のため削除し、下の物に変更 97/11/14 by M.H. */
void MAN_SetCOMEXEC_ModeToJournal(UWORD que_num, UBYTE stack_number);
void MAN_SetJournal(UBYTE stack_number);
void MAN_SetJournalFileTxNo(UBYTE stack_number);
void MAN_SetJournalFileRxNo(UBYTE stack_number);
void MAN_IncTxJournalPoint(void);
void MAN_IncRxJournalPoint(void);
void MAN_ChangedSRAM_Parameter(UWORD value);
void MAN_OptionModemStart(UBYTE number);
void MAN_OptionModemLast(UBYTE number);
void MAN_SetDepartManageFile(UBYTE num, UBYTE mode);  /* added by thonda 1997/12/02 */
UBYTE MAN_CheckReceiveTime(UDWORD rcv_time, UWORD current_num);	/* 1998/05/20 by T.Soneoka */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/22 Y.Murata for KAKI */
UBYTE CheckQucikTxScan(UWORD que_no);
#endif

#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/6/24 K.Kawata */
void MAN_ChangeItemLS2MP(void);
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/************************************************************************
 * プロトタイプ宣言
 * 1998/03/31 Y.Tanimoto
 * MAN_INF.C
 ************************************************************************/
void	MAN_FromInfMain(UWORD, UWORD, UWORD, UWORD,UWORD,UWORD);
void	MailTxDocStoreOK(void);
void	MailTxDocStoreNG(void);
void	SetResultAfterMailCommand(UBYTE);
void	CheckMailBoxAfterRx(UBYTE);
void	ReceiveMailOnePageEnd(UBYTE);
void	ReceiveMailOneFileEnd(UBYTE);
void	StartMailComPrint(void);
UBYTE	StartRxMailPrint(UBYTE);
UBYTE	StartCheckMsgPrint(void);
void	StartRxMailManualPrint(UBYTE);
void	ReStartRxMailManualPrint(UBYTE);
void	StartErasedNoticePrint(void);
void	ControlAutoReceiveMailCom(void);
void	CreateAutoRcvMailData(UBYTE);
void	CreateAutoRcvMailCom(UBYTE);
UBYTE	GetExecMailCommand(void);
void	RecoverMailComDramBackUpOK(void);
void	RecoverMailComDramBackUpNG(void);
void	MailComAllRamClear(void);
void	CheckErasedRxMailNotice(void);
void	CheckErasedMailComNotice(void);
void	DecrementAutoRcvCounter(void);
void	MailComDataPowerOnInitial(void);
UWORD	GetInternetFaxScanReducion(UBYTE);
UBYTE	GetInternetFaxScanMode(UBYTE);
UBYTE	GetUpdatedUserNumber(void);
void	ControlMailAccountData(void);
void	ScheduleMailCommand(void);
void	CheckInternetFaxDevice(void);
void	DecrementRxMailHoldTime(void);
#endif	/* end of PRO_DIALUP_INTERNET_FAX */
