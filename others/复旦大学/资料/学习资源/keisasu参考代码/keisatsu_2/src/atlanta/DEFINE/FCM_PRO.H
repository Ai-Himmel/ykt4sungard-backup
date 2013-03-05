/* by NOBUKO  Oct.03,95 */
#include "\src\atlanta\define\time.h"

#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998  */
#include "\src\atlanta\define\cl1expro.h"
#endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_TCMP.C									*
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> far 21.Jly'94 Y.Suzuki */
void	TxCompatibleCheck(void);
void	TxOriginalModeCheck(void);
UBYTE	SecurytyTxCompatibleCheck(void);
UBYTE	SecureTxCompatibleCheck(WORD);
void	RelayTxCompatibleCheck(WORD);
void	ReceiptRequestToTCRRequest(void);
void	TxMemoryFlagSet(WORD);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_RCMP.C									*
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> far 21.Jly'94 Y.Suzuki */
void	RxCompatibleCheck(void);
void	RxOriginalModeCheck(void);
void	OriginalHyperFineModeCheck(void);		/* 96/05/17 By T.Yamaguchi */
#if (PRO_PRINTER_RX == ENABLE)
	UBYTE	QueryReceiveType(void); /* added by H.Hirao */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/22 K.Kawata*/
UBYTE	QueryReceiveType(void);
#endif
/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_PCMP.C									*
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> far 21.Jly'94 Y.Suzuki */
void	TxOriginalPollingModeCheck(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_TCKS.C									*
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
void	GetMultiFrameLine(void);
/* FCM_COMP_TEXT 分割にともない near --> far 21.Jly'94 Y.Suzuki */
void	GetFaxComTxType(void);
/* UBYTE	GetFaxComTxType(void);	1996/11/28	By T.Yamaguchi */
void	GetFirstTxDocumentData(void);
/* FCM_COMP_TEXT 分割にともない near --> far 2ly'94 Y.Suzuki */
void	GetNextTxPageData(UWORD);
UBYTE	SetTxBaudRate(void);
void	SetTxCode(void);
void	SetTxGrayMode(void);	/* 96.01.29 By T.Y */
UBYTE	SetTxMode(void);
void	SetTxPaperLength(void);
void	SetTxMinimumCommunicationTime(void);
UBYTE	CheckTxModeUpperFine(void);
UBYTE	CheckRxModeUpperFine(void);
void	SetTxECM_Mode(void);
void	SetTxMSE_Mode(void);
UBYTE	SetTxPaperWidth(void);
UBYTE	RxStdFrame_HyperFineBitCheck(void);	/* 96.01.29 By T.Y */
UBYTE	RxStdFrame_OtherFineBitCheck(void);
UBYTE	RxStdFrame_SuperFineBitCheck(void);	/* 96.01.29 By T.Y */
UBYTE	RxStdFrame_FineBitCheck(void);			/* 96.01.29 By T.Y */
/* UBYTE	RxStdFrame_InchBitOnCheck(void);		/@ '96.01.31 By T.Y */
UBYTE	RxStdFrame_MiliBitOnCheck(void);
UBYTE	RxStdFrame_ECMAbilityCheck(void);	/* 1996/12/02  By T.Yamaguchi */
UBYTE	CheckCipherTx(void);				/* 1997/06/18  By T.Yamaguchi */

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_RCKS.C									*
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* Called by FCM_RXB.C 94/12/1 Y.Suzuki */
UBYTE	SetRxBaudRate(void);
UBYTE	SetRxCode(void);
UBYTE	SetRxMode(void);
UBYTE	SetRxPaperLength(void);
UBYTE	SetRxMinimumCommunicationTime(void);
UBYTE	CheckRxModeUpperFine(void);
UBYTE	SetRxECM_Mode(void);
#if (PRO_CIPHER == ENABLE) /* 1997/12/08 T.Yamaguchi */
 UBYTE	SetCipherRxECM_Mode(void);	/* 1997/12/08 */
#endif
void	SetRxMSE_Mode(void);
UBYTE	SetRxPaperWidth(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_FIF2.C									*
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
UBYTE	SetUpMemoryRx(void);
WORD	SetDocumentMemorySizeFrame(WORD);
UBYTE	CheckPollingTxType(void);
UBYTE	SetUpRxDocumentPollingTx(void);
WORD	SetRestMemoryFrame(UBYTE,WORD);
void	SetMakerCodeFrame(void);
#if(PRO_MAKER == MML)
UBYTE	SetUpSecureMailRx(WORD);
UBYTE	SetUpSecureMailTx(WORD);
#if (0)/*	By Y.Suzuki 1996/10/25	*/
** #if (PRO_BUFFERING_RX == ENABLE)
**	UBYTE	SetUpBufferingRx(void);
** #endif
#endif
 #if (PRO_TSI_RELAY_COM == ENABLE)/* 9.Feb'95 Y.Suzuki */
 UDWORD		GetGroupNoFromStdID(UBYTE);
 #endif
 #if (PRO_RELAYED_REPORT == ENABLE)/* 9.Feb'95 Y.Suzuki */
 UBYTE		CountRelayedTxCommand(void);
 #endif
UBYTE	SetUpRelayBroadCastRx(WORD);
WORD	GetDatabasePollingFileNumber(WORD);
UBYTE	SetUpRemoteFaxRx(void);
WORD	SetPasscodeFrame(UBYTE,WORD);
WORD	SetSecureMailFieldFrame(UBYTE,WORD);
WORD	SetDatabasePollingDataFrame(WORD);
WORD	SetRelayedBroadcastGroupFrame(WORD);
UBYTE	SetUpCipherRx(void);	/* 1997/06/18  By T.Yamaguchi */
UBYTE	SetUpWarpRx(void);
void SetUpSpecialReplayTrans(void);
#endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_FIF1.C									*
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE	CheckDocPaperSize(void);
#endif
UBYTE	CheckPollingDocuments(void);
UBYTE	CheckTxMemorySize(WORD);
UBYTE	CheckRestMemory(void);
#if(PRO_MAKER == MML)
UBYTE	CheckPasscodeBuf(void);
UBYTE	CheckSecureMailBox(void);
UBYTE	CheckDatabasePollingData(void);
UBYTE	CheckRelayedBroadcastGroup(void);
UBYTE	CheckMMRinNonStandardFrame(WORD);
UBYTE	CheckPassCodeMatching(WORD);
UBYTE	CheckExpandFieldBIT(WORD,WORD);
void	CheckPartnerSCFR_Func(void);		/* UBYTE -> void 1996/12/02	 By T.Yamaguchi */
UBYTE	CheckPartnerRCR_Func(void);
UBYTE	CheckPartnerPassCodeSetting(WORD);
UBYTE	CheckPartnerSecureMailFunc(WORD);
UBYTE	CheckPartnerRelayBroadCastFunc(WORD);
UBYTE	CheckPartnerDB_PollingFunc(WORD);
UBYTE	CheckPartnerCharMailFunc(WORD);
UBYTE	CheckPartnerTTI_Func(UBYTE);
#endif
/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCMFRMS.C								   *
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> far.Jly'94 Y.Suzuki */
void	MakeHDLC_Frame(UBYTE,UBYTE);
UBYTE	CheckHDLC_Command(void);
void	FaxPPR_Transmit(WORD);
/* FCM_COMP_TEXT 分割にともない near --> far Jly'94 Y.Suzuki */
BYTE	CheckPPS_Frame(void);
/*void		MemorizePPSFrame(void);**/
/*char		RxJudgeECM_ErrorFrame(UBYTE);**/
/*void		TransmitTone(UWORD , UWORD);	トーン周波数	*/
/*void		RxDCSSemiCompatibleCheck(void);**/
/* FCM_COMP_TEXT 分割にともない near -->  21.Jly'94 Y.Suzuki */
void	ResultECM_ModeSet(void);
void	TransmitError(UBYTE, BYTE);	/*	交信終了フラグ	*/
void	ReceiveError(UBYTE);
void	DialError(UBYTE);	/*		エラーナンバー	*/
void	FCM_SetFaxComErrorMonitor(UWORD, UWORD, UWORD);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCMIDCHK.C									*
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* UBYTE	RxCheckOwnDialAndID(void); 1997/10/20  By T.Yamaguchi */
UBYTE	RxCheckOwnDialAndID(UBYTE *id_buf);
UBYTE	RxCheckJunkDialAndID(UBYTE *id_buf);	/* 1997/05/12  By T.Yamaguchi */
/* UBYTE	CheckBCD_DialAndStandardID(UBYTE *); /@	ワンタッチダイヤルか短縮ダイヤル	*/
UBYTE	CheckBCD_DialAndStandardID(UBYTE *, UBYTE *); /*	ワンタッチダイヤルか短縮ダイヤル	*/
UBYTE	CheckASCII_CodeAndStandardID(UBYTE *);	/* FX */
/* UBYTE	CheckASCII_DialAndStandardID(UBYTE *); 1997/10/20  By T.Yamaguchi */
UBYTE	CheckASCII_DialAndStandardID(UBYTE *, UBYTE *);
UBYTE	CheckTransmitterID_Buf(void);
UBYTE	CheckSubscriberID_Buf(void);
UWORD	SetTransmitterID_Frame(WORD);
void	SetSubscriberID_Frame(void);
void	GetOwnMakerPartnerID(WORD);
void	GetPartnerID(void);
 #if (PRO_RELAYED_REPORT == ENABLE)/* 9.Feb'95 Y.Suzuki */
 UBYTE		SetTransmitStationID(void);	/* (椛)不達通知送信先ＩＤセット '95/02/17 Y.Suzuki */
 #endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCMMKCTC.C									*
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> far.Jly'94 Y.Suzuki */
void	MakeCTC_FIF(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCMDCS.C									  *
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> fa1.Jly'94 Y.Suzuki */
 void	MakeDCS_FIF(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCMNSS.C									  *
* 1994/6/16 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> far 21.Jly'94 Y.Suzuki */
 void	MakeNSS_FIF(void);
UBYTE	FCM_HFineCheck(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCMDTC.C									  *
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> far 21.Jly'94 Y.Suzuki */
 void	MakeDTC_FIF(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCMNSC.C									  *
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> far 21.Jly'94 Y.Suzuki */
void	MakeNSC_FIF(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCMDIS.C									  *
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> far 21.Jly'94 Y.Suzuki */
void	MakeDIS_FIF(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCMNSF.C									  *
* 1993/1/10 By 鈴木郁二												*
********************************************************************/
/* FCM_COMP_TEXT 分割にともない near --> far 21.Jly'94 Y.Suzuki */
void	MakeNSF_FIF(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCMCOST.C								   *
* 1994/8/12 By 鈴木郁二 & 奥村									   *
********************************************************************/
#if(PRO_COST == ENABLE)
/* FCM_TEXT	 */
UBYTE	FCM_GetCostTable(UBYTE *dialbuf_ptr, UWORD exec_no);
void	FCM_CostCalculate(UWORD, UBYTE, UBYTE);
void	SetCost(UWORD, UBYTE, UBYTE, UWORD);
UBYTE	CheckCostZone(UBYTE);
UWORD	CalculateFirstCostTime(TIME_DATA_t *);
UWORD	CalculateCostTime(UBYTE);
void	DepartListPrintON(void);
UBYTE	CheckCostTable(UBYTE);
#endif
void	FCM_SetCostData(UWORD, UBYTE *);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_MAIN.C									*
* 1993/1/12 By 村田													*
********************************************************************/
void	FCM_Task(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_LAST.C									*
* 1993/1/12 By 村田													*
********************************************************************/
void	FaxComAfterCheck(void);
void	SpeedHandshakeAttributeChange(void);
void	SpeedHandshakeAttributeDel(void);
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
void	FlashRomWriteAfterCheck(UBYTE);
#endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_RELY.C									*
* 1993/1/12 By 村田													*
********************************************************************/
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
void	FaxcomRelayControl( void );
void	FaxComRelaySetting(void);
#endif
/* void		FaxComUntilRecDISLineON(void);	1996/11/28	By T.Yamaguchi 削除 */
void	FaxComUntilRecDISLineOFF(void);

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
void FaxComQuickTxLineON(void);
void FaxComQuickTxLineOFF(void);
#endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_INIT.C									*
* 1993/1/12 By 村田													*
********************************************************************/
void	InitializeBaudrate(void);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
void	InitializeFaxCom(void);
#endif
void	SetAvailableCodingMethodEcmOn(void); /* Added by H.Kubo 1998/01/27 for V34 */
/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_GETD.C									*
* 1993/1/12 By 村田		追加 By T.Y	  FCM_GetPinDialData()			*
********************************************************************/
void	SetPartnerAbility(void);
void	FCM_GetDialData(UBYTE * , UBYTE *);
void	GetDialNumber(void);
void	DecrementRedialCount(void);
void	GetCommandFileData(void);
void	GetDialOffesetNumber(void);
#if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
void	FCM_GetPinDialData(UBYTE * , UBYTE *);
void	GetPinNumber(void);
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
	UBYTE FCM_CheckQucikMemoryTx(void);
#endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_FCOM.C									*
* 1993/1/12 By 村田													*
********************************************************************/
void	AutoFax(void);
void	ManualTransmit(void);
void	ManualReceive(void);
void	AutoCalled(void);
void	FipFaxCom(void);
void	ManualPollingReceive(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_SPD.C								*
* 1996/01/24 By 山口												*
********************************************************************/
void	FaxTxSpeedHandshake(void);
void	FaxRxSpeedHandshake(void);
UBYTE	FaxSNSS_SemiCompatibleCheck(void);
UBYTE	MuratecRxSpeedHandshakeEnable(void);
void	FaxTransmitCNG(void);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
void	FaxTransmitCED(void);	/* near->far by Y.Tanimoto */
#endif
void	FaxTransmit1080Hz(void);
/* void		FaxTransmit1300Hz(void); FX専用線に対応しないので削除 '96/04/16 By T.Yamaguchi */
#if (PRO_SPEED_EX == ENABLE)	/* 1996.01.24 */
void	ArrivalSignalToneTransmit(void);
#endif
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
UBYTE	ModeChangeMethodCheck(void);	/* '96/06/01 By T.Yamaguchi */
UBYTE	SpeedModeChangeRomCheck(void);
#endif
UBYTE	SpeedHandshakeRomCheck(void);
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/05 */
void 	FCM_SetHandshakeAttribute(void);
#endif /* (PRO_TX_SPEED == V34) */
void	FaxTransmit1300Hz(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_JRNL.C									*
* 1993/1/12 By 村田													*
********************************************************************/
void	SetJournal(void);
void	SaveT30Data(UBYTE , UBYTE * , UWORD );
void	SaveReceivedT30Data(void);
void	SaveT30TimingData(UBYTE );
void	SetCOMEXEC_LocationJournal(void);
void	SetRemoteID_ToLocationJournal(void);
void	SetPatJournalDataAtAutoFax(void);
void	SetJournalQueueHostLine(void);	/* 1998/02/03 Y.Murata	CHAR_JOURNAL */

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_DIAG.C									*
* 1993/1/12 By 村田													*
********************************************************************/
void	MakeCommonDiagNSS(void);
void	WriteROMVersionDiagNSS(void);
UBYTE	RxDiagSemiCompatibleCheck(void);
void	AnalizeMakeServiceUtilitySb( UBYTE );
UBYTE	AnalizeMakeServiceUtility(void);
void	RemoteDiagnostic(void);
void	ReadStartAddress(void);
void	ReadFIF_DiagNSS(void);
void	WriteFIF_DiagNSS(void);
UWORD	DiagJudgeProtectAddress(void);
UBYTE	HighSpeedRDS_CompatibleCheck(void);
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
UBYTE	FlashRomWriteCheck(void);
UBYTE	RomFileModel_NameCheck(void);
#endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_RXB.C									*
* 1993/1/26 By HARADA												*
********************************************************************/
void	FaxReceive(void);
void	FaxRxNegotiate(void);
void	FaxTxSCFR(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_RXB1.C									*
* 1993/1/26 By HARADA												*
********************************************************************/
void	FaxRxPhaseB1(void);
void	HookTensouOffHookCheck(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_POLB.C									*
* 1993/1/26 By HARADA												*
********************************************************************/
void	FaxPollingRxPhaseB1(void);
UBYTE	FaxPollDISSemiCompatibleCheck(void);
UBYTE	FaxPollNSFSemiCompatibleCheck(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_TXB.C									*
* 1993/1/26 By HARADA												*
********************************************************************/
void	FaxTransmit( void );
void	FaxTxNegotiate(UBYTE	 command);
void	FaxTxDCSTCF(void);
BYTE	FaxTxTraining(void);
UBYTE	FCM_CheckBaudRate(UBYTE baudrate);	/* 2001/04/25 H.Yoshikawa */

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_TXB1.C									*
* 1993/1/26 By HARADA												*
********************************************************************/
void	FaxTxPhaseB1( void );
UBYTE	FaxDIS_SemiCompatibleCheck(void);
UBYTE	OriginalCommunicationNeedNSF(void);		/* add by T.Yamaguchi 96/09/02 */
#if 0	/* defined(FRA) */
UBYTE	FaxTxBeforeVoiceMode(void);
#endif

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_PH_E.C									*
* 1993/1/26 By HARADA												*
********************************************************************/
void	FaxPhaseE( UBYTE	phase_e_mode);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\koba\anzu\\src\FCM_FSUB.C									*
* 1993/1/26 By HARADA												*
********************************************************************/
void	FaxTimer( UWORD	set_timer );
void	FaxRxDCS_SemiCompatibleCheck(void);
void	FaxHDLC_Transmit( UBYTE	fcfcode, UBYTE option_code );
void	SendMsgFaxComToMain( UWORD );
UBYTE	FCM_CheckCommandTRx(void);	/* add by T.Yamaguchi 1996/05/08 */


/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\koba\anzu\\src\FCMTXC.C]
	Comment		:[送信フェーズＣの関数]
	Machine		:[V53,H8/300]
	Language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	Keyword		:[FCM]
	Author		:[竹内茂樹]
	Date		:[1994/01/27]
*************************************************************************/
void	FaxTxPhaseC( void );
void	SetTxPageData( void );
/*	UBYTE	near	OpenScannerTxPage( void );	**	MDMへ移動	Feb.28.1994	*/
/*	UBYTE	near	OpenMemoryTxPage( void );	**	MDMへ移動	Feb.28.1994	*/
/*	void			near	CloseScannerTxPage( void );	**	MDMへ移動	Feb.28.1994	*/
/*	void			near	CloseMemoryTxPage( void );	**	MDMへ移動	Feb.28.1994	*/
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998 */
UWORD	CheckMinimumLineSize( UBYTE, UBYTE );
#endif
void	FCM_TxEndSet(void);
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/21 Y.Murata for KAKI */
UBYTE CheckNextPage(void);
#endif
/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\koba\anzu\\src\FCMTXD.C]
	Comment		:[送信フェーズＤの関数]
	Machine		:[V53,H8/300]
	Language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	Keyword		:[FCM]
	Author		:[竹内茂樹]
	Date		:[1994/01/27]
*************************************************************************/
void	FaxTxPhaseD( void );
void	TxPostMessageHandshake( void );
void	AnalyzeReceivedPostMessage( void );
void	FCM_PIP_Received(UBYTE);
void	FCM_PIN_Received(UBYTE);
void	PreAnalyzePostMessage(void);

/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\koba\anzu\\src\FCMTXDS.C]
	Comment		:[送信フェーズＤの関数]
	Machine		:[V53,H8/300]
	Language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	Keyword		:[FCM]
	Author		:[竹内茂樹]
	Date		:[1994/01/27]
*************************************************************************/
UBYTE	ResetTxPageFinishStatus( void );
BYTE	CheckNextDB_File( void );
BYTE	CheckRCR_Request( void );
void	CompareTxMode( void );
void	MemorizeTxErrorPage( void );
void	UpdateTxPageInformation( void );
void	FCM_EraseTxMemoryPage(UWORD exec_no, struct MEM_IndexData_t *mem_index);
/* void 	FCM_EraseTxMemoryDoc(void);	del 1997/10/01  By T.Yamaguchi */
void	FallBackByRTN( void );
#if 0 /* V17 ECM 送信中全フレームエラーでフォールバックする場合、V29 にする処理を追加 by H.Kubo 1999/12/22 */
**void	FallBackByPPR( void );
#endif
void	FallBackByPPR( UBYTE ecm_all_frame_error_count );

BYTE	CheckErrorPage( void );
BYTE	CheckAllErrorPage( void );
BYTE	CheckNextScannerDoc( void );
UBYTE	TxCommandAndRxResponse(	UBYTE, UBYTE );
UBYTE FCM_CheckAllFrameError(void);

/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\koba\anzu\\src\FCMRXC.C]
	Comment		:[受信フェーズＣの関数]
	Machine		:[V53,H8/300]
	Language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	Keyword		:[FCM]
	Author		:[竹内茂樹]
	Date		:[1994/02/07]
*************************************************************************/
void	FaxRxPhaseC( void );
void	SetRxPageData( void );
void	StartRxPix( void );
void	RxECM_PixData( void );
void	StartECM_RxPix( void );
void	CopyEcmBufferToBackUpRAM(void);	/* 1997/02/05  By T.Yamaguchi */
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)	/* 1998/03/31  By T.Yamaguchi */
void	CopyRomDataEcmBufferToDRAM(void);
/* void	MemoryMoveWord(register UWORD *,register UWORD *,UWORD);	*/
UWORD	MemoryMoveWordAndSum(UWORD	*,UWORD *,UWORD);
UWORD	SumCheck(UWORD *,UDWORD);
#endif

/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\koba\anzu\\src\FCMRXCS.C]
	Comment		:[受信フェーズＣの関数]
	Machine		:[V53,H8/300]
	Language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	Keyword		:[FCM]
	Author		:[竹内茂樹]
	Date		:[1994/01/27]
*************************************************************************/
void	TransmitPPR( BYTE );
BYTE	JudgeECM_RxErrorFrame( void );
void	MemorizePPS_Frame( void );
UBYTE	WaitRxPaperCut( UBYTE );
void	CheckRxPrinterError( void );
UWORD	GetRxPrinterErrorStatus( void );
void	CheckRxPixResultPhaseC( void );
void	CheckRxPixResultPhaseD( void );
void	CheckRxPixResultSub( void );
void	FaxRxTimeOutEvade( void );

/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\koba\anzu\\src\FCMRXD.C]
	Comment		:[受信フェーズＤの関数]
	Machine		:[V53,H8/300]
	Language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	Keyword		:[FCM]
	Author		:[竹内茂樹]
	Date		:[1994/02/07]
*************************************************************************/
void	FaxRxPhaseD( void );
void	AnalyzeRxPostMessageFrame( void );
UBYTE	CheckReceivedFCF( void );
void	TransmitRNR( void );
void	RxRespondPostMessage( void );
void	ReceiveDCS( void );
void	RxRequestedVoiceMode( UBYTE );
void	TransmitPIP( void );
/* UBYTE	ModeChangeSpeedHandshake( void ); */

/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\koba\anzu\\src\FCM_FXTL.C]
	Comment		:[Ｔｅｌ／Ｆａｘの関数]
	Machine		:[V53,H8/300]
	Language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	Keyword		:[FCM]
	Author		:[パララ(竹内茂樹)]
	Date		:[1994/06/09]
*************************************************************************/
/* #if (PRO_CPU == V53) || (PRO_CPU == SH704X) || (PRO_CPU == SH7034) */
#if (PRO_CPU == SH7043)
WORD	FaxTelAutoSwitch( void );
void	FaxTelAutoSWAfterTransaction( void );
void	TransmitModulatedFrequencyRBT( UWORD );
UBYTE	FaxTelTransDIS_ReceiveCMD( void );
void    FCM_DeleteRingSignal(void); /* Added by H.Kubo 1997/07/08 */
#endif

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/12 */
WORD	FaxTelAutoSwitchForAnswer( void );
WORD	FaxTelAutoSwitchForNoAnswer( void );
#else
void	FaxTelDummySwitch(void);	/* ダミー関数 */
#endif

/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\kobe\anzu\src\FCM_PTNR.C]
	Comment		:[]
	Machine		:[]
	Language	:[]
	Keyword		:[FCM]
	Author		:[t.yamaguchi]
	Date		:[1996/01/23]
*************************************************************************/
UBYTE	FCM_PtnrChkTxBPS(void);
UBYTE	FCM_PtnrChkV29EPtoneAvailable(void);
UBYTE	FCM_PtnrChkOverride1stDIS(void);
UBYTE	FCM_PtnrChkFallbackPattern(void);
UBYTE	FCM_PtnrChkBusyToneDetect(void);
UBYTE	FCM_PtnrChk_T23Attenation(void);
UBYTE	FCM_PtnrChk_T23DCS_AfterTCF(void);
UWORD	FCM_PtnrCHK_T41CFR_AfterPIX(void);
UBYTE	FCM_PtnrChk_DIS_AfterDCS(void);
UWORD	FCM_PtnrChkECM_TxInterval(void);
UWORD	FCM_PtnrChkECM_ResponseTime(void);
UBYTE	FCM_PtnrChkTTI_TxAvailable(void);
UBYTE	FCM_PtnrChkCalendarTypeChange(void);
UBYTE	FCM_PtnrChk_TxToPrinterRxEnable(void);
UBYTE	FCM_PtnrChk_DCS_V33AllHold(void);
UBYTE	FCM_PtnrChkSpeedHandshake144(void);
UBYTE	FCM_PtnrChkSpeedHandshake96(void);
UBYTE	FCM_PtnrChkSpeedHandshakeV8(void);
UBYTE	FCM_PtnrChkRTN_NoReTransmit(void);
UBYTE	FCM_ECM_TxOFF(void);
UBYTE	FCM_TerminalInformationNotTx(void);	/* Add By O.Kimoto 1999/04/20 */
UBYTE	FCM_V34TransmitDisable(void);		/* Add By O.Kimoto 1999/04/20 */
UBYTE	FCM_OverrideANSam(void);			/* Add By O.Kimoto 1999/04/20 */
/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\atlanta\\src\FCM_fcd.C]
	Comment		:[]
	Machine		:[]
	Language	:[]
	Keyword		:[FCM]
	Author		:[山口 哲治]
	Date		:[1997/01/23]
*************************************************************************/
/*#if (PRO_F_CODE == ENABLE)*/
void MakeTX_PWD_FIF(void);
void MakePOL_PWD_FIF(void);
UBYTE MakePWD_FIF_Sub(void);
void MakeSEP_FIF(void);
void MakeSUB_FIF(void);
UBYTE SetTxF_CODE(void);
UBYTE FcodeCompatibleCheck(void);
UBYTE SetPollF_CODE(void);
void GetF_CODE_ID(void);
void GetPWD_ID(void);
void GetSEP_ID(void);
void GetSUB_ID(void);
UBYTE SetF_CODE_ID(UBYTE *, UBYTE );
void SetOwnF_CODE_ID(void);
UBYTE CheckF_CODE_ID(UBYTE *, UBYTE *);
UBYTE CheckRxF_CODE(void);
UBYTE FCM_CompFcodeBox(UBYTE *, UBYTE *, UBYTE, UBYTE);
void FCM_SetupRemoteID(UBYTE, UBYTE *, UBYTE *);
UBYTE FCM_RxFcodeStatusSet(struct MEM_IndexData_t *, UBYTE, UWORD);
UBYTE SetUpSubaddressBoxRx(void);	/*	モデムバッファのポインター	*/
UBYTE FCM_TxFcodeStatusSet(UBYTE);
UBYTE FCM_TxFcodeFileSet(UBYTE, UBYTE, UWORD *, UWORD *);
UBYTE SetUpSubaddressBoxPollingTx(void);
UBYTE CheckSubaddressBox(void);
UBYTE SubaddressBoxDetectEmptyNo(UDWORD);
UBYTE SetUpFcodeRelayBroadCastRx(struct MEM_IndexData_t *, UBYTE, UWORD);
UBYTE FCM_FcodeRelayTxTTI_Available(void);
UBYTE FCM_FcodeRelayTxTTI_Inside(void);
/*#endif*/

/* FCM_CHK.c */
void  FCM_ScannerTxManagement(void);
UWORD FCM_ScnTxBetweenPageManagement(UWORD tx_total_page, UWORD tx_sm_type, UWORD is_scn_page_start);
void  FCM_ScannerCloseManagement(UWORD , UWORD );
void  FCM_SCN_DecideReducPattern(struct SYS_DocBlockData_t *);
UWORD FCM_CheckMemRxContinueForVoice(void);
UWORD FCM_GetMemoryBlockSize(void);
UWORD FCM_CheckMemoryReceiveEnable(void);
UWORD SYS_GetDS1_ON(void);
UWORD SYS_GetCoverScannerOpen(void);
UWORD SYS_GetScannerLampError(void);
UWORD FCM_GetMemoryRxPrintWritePoint(UWORD);
UWORD FCM_GetSYS_TxTotalCount(UWORD);
UWORD FCM_GetSYS_RxTotalCount(UWORD);
UWORD DIAG_JudgeProtectAddress(UWORD , UWORD );
void  DIAG_ReadFIF_DiagNSS(UWORD , UWORD , UBYTE , UBYTE *);
void  DIAG_WriteFIF_DiagNSS(UWORD , UWORD , UBYTE , UBYTE *);
UWORD FCM_RxCheckOwnDialAndID(UBYTE *);
UWORD FCM_TxPixReductionSet(UBYTE	src_size, UBYTE	src_mode, UBYTE	dst_size, UBYTE	dst_mode, UBYTE	mode_method);
UWORD FCM_GetCodecSize(UWORD size, UWORD mode);

void  MltSetPatJournalDataAtAutoFax(UWORD stack_number);
void  MltSetPatJournalAtManualTx(UWORD stack_number);
void  MltSetPatJournalAtManualRx(UWORD stack_number);
void  MltSetPatJournalAtAutoCalled(UWORD stack_number);
void  MltSetPatJournalAtPollAutoCall(UWORD stack_number);
void  MltClearPatJournalWorkArea(UWORD stack_number);
void  MltSetPatJournalAtAfter(UWORD stack_number);
void  MltSetCOMEXEC_LocationJournal(UWORD que_num);
void  MltSetRemoteID_ToLocJournal(UWORD stack_number);
void  MLT_JournalDataToImage(UBYTE menber, UBYTE stack_number);
void  MLT_StringToCharacterImage(UBYTE *string, UBYTE *attribute, UBYTE	  length, UBYTE	  offset, UBYTE	  point);
UWORD FCM_GetDataSignalingRate(UWORD stack_number);
UWORD FCM_CheckCountryCode(void);
UWORD FCM_MEM_WriteOpen(struct MEM_StoreData_t *StoreP, struct MEM_ExecData_t *ExecP);
void  V8CapableAttributeSet(void);
UWORD FCM_CheckRemotoDiag(UWORD);
UWORD FCM_GetMonitorSpeakerOutLevel(void);
UWORD FCM_CheckJunkFax(UWORD frame_name, UBYTE *standard_id);
UWORD FCM_CompJunkFax(UWORD frame_name, UBYTE *std_id);
UWORD FCM_GetCipherBoxNo(UWORD stack_number);
void  FCM_SendBackCipherStatus(UWORD status, UWORD number, UWORD data, UWORD stack_number);
void  FCM_SetRxSubAddressBox(UWORD rx_file_item, UWORD file_no, UWORD rx_total_page, UWORD box_number);
void  FCM_SetTxSubAddressBox(UWORD tx_file_item, UWORD box_number, UWORD com_result);
UWORD FCM_CheckMailBoxStatusSet(UWORD mail_box_no, UWORD type, UWORD stack_number);
UWORD PickOutLastFourFigure(UBYTE *id_buf, UBYTE count);
void  SetJunkOwnDial(void);
void FCM_SetJournalQueueOptionLine(UWORD number, UWORD num);	/* 1998/02/03 Y.Murata	CHAR_JOURNAL */


/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\clover\src\FCM_V34.C]
	Comment		:[]
	Machine		:[]
	Language	:[]
	Keyword		:[FCM]
	Author		:[村田]
	Date		:[1995/12/11]
*************************************************************************/
/* Ported from Clover by H.Kubo 1997/07/08 */
UBYTE			FCM_ControlChanelTurnOff(void);
UBYTE 			FCM_ControlChanelDetectTurnOff(void);
UBYTE 			FCM_ControlChTurnaroundTurnOff(void);
UBYTE 			FCM_ControlChanelOff(void);
void 			FCM_PrimaryChanelTurnOff(void);
UBYTE 			FCM_CheckV8ProcedureRequest(void);
UBYTE 			FCM_CheckPartnerV8Capable(void);
UBYTE 			FCM_CheckDetectCI(void);
UBYTE 			FCM_CheckV8ProcedurePhaseA(void);
UBYTE 			FCM_CheckTxDataRate(void);
UBYTE 			FCM_CheckRxDataRate(void);
UBYTE  			FCM_ChangeDataRate(UBYTE);
UBYTE  			FCM_V34DataRateDefineChange(UBYTE);
UBYTE  			FCM_CheckMinimumDataRate(void);
void 			FCM_SetTxDataRate(void);
void 			FCM_SetRxDataRate(void);
void  			FCM_GetRxErrorFrame(void);			/* 1996/05/16 Y.Murata */
UBYTE  			FCM_ChangeDataRateUp(UBYTE);	/* 1996/05/20 Y.Murata */
UBYTE  			FCM_CheckDataRateUp(void);			/* 1996/05/20 Y.Murata */
UBYTE  			FCM_CheckModemAbort(void);			/* 1996/06/20 Y.Murata */

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/25 */
/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\clover\src\FCM_V8SB.C]
	Comment		:[]
	Machine		:[]
	Language	:[]
	Keyword		:[FCM]
	Author		:[村田]
	Date		:[1996/03/21]
*************************************************************************/
UBYTE			FCM_AfterToneCheck(void);
void			FCM_AfterToneCheckDelTask(void);
void			FCM_SetV8Error(UWORD, UBYTE);
void 			FCM_WWdetectTask(void);
UBYTE			FCM_CheckToneDetectedInV8Mode(void); /* added by H.Kubo 1998/05/25 */
/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\clover\src\FCM_V8.C]
	Comment		:[]
	Machine		:[]
	Language	:[]
	Keyword		:[FCM]
	Author		:[村田]
	Date		:[1995/11/06]
*************************************************************************/
void		V34_SetUpCallProcedure(void);
void		V34_SetUpAnswerProcedure(void);
void		V34_DetectV25AnswerToneTask(void);
void		V34_V8ControlTask(struct FCM_V8ControlData_t *);
UBYTE		V34_CallStartUpPhase2(void);
UBYTE		V34_CallStartUpPhase3(void);
UBYTE		V34_AnswerStartUpPhase2(void);
UBYTE		V34_AnswerStartUpPhase3(void);
UBYTE		V34_AnalizeModurationMode(UBYTE);
UBYTE		V34_ExecuteStartUp(UWORD);
void		V34_TransmitCIinV8Mode(void);
void		V34_StopCIinV8Mode(void);
void		V34_TxHandshakeMonitorTask(WORD *);
void		V34_RxHandshakeMonitorTask(WORD *);
void		V34_V8ControlTaskExit(void);
void		V8TaskInitial(void);
void		V8TaskDelete(void);
void		FCM_CommunicationV8toT30(void);
void		V34_DetectV8CITask(void);

/********************************************************************
* ﾌﾟﾛﾄ･ﾀｲﾌﾟ宣言														*
* File : \src\clover\src\FCM_GETD.C									*
* 1993/1/12 By 村田													*
********************************************************************/
void		SetPartnerAbility(void);
UBYTE		BCDtoASCII( UBYTE );
void		FCM_GetDialData(UBYTE * , UBYTE *);
void		GetDialNumber(void);
void		DecrementRedialCount(void);
void		GetCommandFileData(void);
UBYTE		CheckCommnadFileTxItem(void);
void		FCM_GetPinDialData(UBYTE * , UBYTE *);

/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\clover\src\FCM_STUP.C]
	Comment		:[]
	Machine		:[]
	Language	:[]
	Keyword		:[FCM]
	Author		:[村田]
	Date		:[1995/11/06]
*************************************************************************/
UBYTE 		FCM_CallStartUpProcedure(void);
UBYTE 		FCM_AnswerStartUpProcedure(void);
UBYTE 		FCM_CallStartUpPhase1(void);
UBYTE 		FCM_AnswerStartUpPhase1(void);
UBYTE 		FCM_CallDetectAnswerTone(void);
UBYTE 		FCM_ExecuteV8Mode(UBYTE, UBYTE);
void 		FCM_GetV8FrameLine(void);
void 		FCM_MakeFrameCMandJM(void);
void 		StartUpTaskInitial(void);
void 		StartUpTaskDelete(void);
void		SavedV8Data(UBYTE, UBYTE *, UWORD, UBYTE);

/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\clover\src\FCM_OPT.C]
	Comment		:[]
	Machine		:[]
	Language	:[]
	Keyword		:[FCM]
	Author		:[村田]
	Date		:[1995/11/06]
*************************************************************************/
void		OPT_GetFaxComUserSetting(void);
void		OPT_CheckFaxComSendBackData(void);
UBYTE		FCM_ClearDoc (UBYTE Item, UWORD  No);
UBYTE		FCM_ClearPageAndFATArea (struct MEM_IndexData *IndexP);
UWORD		FCM_CountTotalPage(UBYTE Item, UWORD No);
UWORD		FCM_CountTotalBlock(UBYTE Item, UWORD No);
UWORD		FCM_CountTotalEmptyPage(void);
WORD		FCM_CountTotalEmptyBlock(void);
UBYTE		FCM_CheckStoreCode(struct MEM_IndexData *IndexP);
UBYTE		FCM_CheckStoreMode(struct MEM_IndexData *IndexP);
UBYTE		FCM_CheckStoreSize(struct MEM_IndexData *IndexP);
void		OPT_GetGlobalDataForFaxCom(void);
void		OPT_SendBackGlobalData(void);
UWORD 	 	FCM_CheckMemRxContinueForVoice(void);	/* 1996/04/18 */
UBYTE	 	FCM_GetMaxRxMode(void);					/* 1996/04/20 */
UBYTE	 	FCM_GetMaxTxMinScanTime(void);			/* 1996/04/20 */
UBYTE	 	FCM_GetMaxRxMinScanTime(void);			/* 1996/04/20 */
UBYTE	 	FCM_GetMaxTxMSE(void);					/* 1996/04/20 */
UBYTE	 	FCM_GetMaxRxMSE(void);					/* 1996/04/20 */
UBYTE	 	FCM_GetMaxRxResolution(void);			/* 1996/04/20 */
UBYTE	 	FCM_GetMaxTxCodeForECM(void);			/* 1996/04/20 */
UBYTE	 	FCM_GetMaxRxCodeForECM(void);			/* 1996/04/20 */
UBYTE	 	FCM_GetMaxTxCodeForNonECM(void);		/* 1996/04/20 */
UBYTE	 	FCM_GetMaxRxCodeForNonECM(void);		/* 1996/04/20 */
UBYTE	 	FCM_GetMaxRxLength(void);				/* 1996/04/20 */

UBYTE 	 	FCM_CheckWWdetectStartGo(void);
UBYTE 	 	FCM_CheckWWdetectStop(void);
void 		FCM_SetWWdetect2100Hz(void);
void 		FCM_WWdetectStartGo(void);
void 		FCM_WWdetectStop(void);

void 		FCM_FaxComStop(void);
void 		OPT_GetHostROM_Revision(void);
UWORD 		FCM_CheckVoiceAccepted(void);


/*************************************************************************
	[プロトタイプ宣言]
	File		:[\src\clover\src\FCM_COMD.C]
	Comment		:[]
	Machine		:[]
	Language	:[]
	Keyword		:[FCM]
	Author		:[村田]
	Date		:[1995/11/06]
*************************************************************************/
void           FCM_TransmitCommand(void);
UBYTE  FCM_ReceiveCommand(WORD, UBYTE);
UBYTE  FCM_ReceiveResponse(UBYTE, UBYTE);
UBYTE  FCM_ReceiveTCF(UBYTE);
UBYTE  FCM_FskHighSpeedCheck(UBYTE, UBYTE);

#endif /* (PRO_TX_SPEED == V34) */

#if defined (KEISATSU) /* 警察FAX 05/07/10 石橋正和 */
/*************************************************************************
	fcm_srtx.c
*************************************************************************/
void FCM_IsseiTx(BOOL);
void FCM_IsseiTxBody(BOOL);
void FCM_IsseiTxCloseScanner(void);
UBYTE FCM_GetIsseiMinScanningTime(UBYTE, UBYTE);
void FCM_SendIsseiDCS(void);
void FCM_SetIsseiDCS_FIF(void);
void FCM_IsseiTxPhaseC(void);
void FCM_IsseiTxPhaseD(void);
UBYTE FCM_ResetIsseiTxPageStatus(void);
void FCM_CompareIsseiTxMode(void);
void FCM_IsseiVoiceReq(UWORD);

/*************************************************************************
	fcm_srrx.c
*************************************************************************/
void FCM_IsseiRx(BOOL);
void FCM_IsseiRxBody(BOOL);
UBYTE FCM_IsseiRxPhaseB1(UBYTE);
void FCM_IsseiRxNegotiate(void);
void FCM_IsseiRxModeCheck(void);
void FCM_IsseiRxPhaseC(void);
void FCM_SetIsseiRxPageData(void);
void FCM_StartIsseiRxPix(void);
void FCM_IsseiRxPostMessage(void);
void FCM_IsseiRxPhaseD(void);
void FCM_IsseiRxReceiveDCN(void);
void FCM_IsseiFixRxDocStatus(void);

#endif

