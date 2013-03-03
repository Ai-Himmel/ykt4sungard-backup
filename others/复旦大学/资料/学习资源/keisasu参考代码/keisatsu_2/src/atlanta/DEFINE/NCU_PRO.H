#include "\src\atlanta\define\ncu_def.h"
/*********************************************************************/
/*			 ÇqÇhÇbÇdÅ@âÒê¸äƒéã(NCU) ÉvÉçÉgÅEÉ^ÉCÉvêÈåæ				 */
/*																	 */
/*																	 */
/*							1993/12/21								 */
/*							 ç‚ñ{íºéj								 */
/*																	 */
/*********************************************************************/
/*********************************************************************/
/* File : \src\rice\src\NCU_MAIN.C									 */
/*********************************************************************/
void	NCU_Task( void );
void	NCUTaskExit( void );
void	NCU_TaskExit( void );
void NCU_TaskKillChildTasks(void); /* added by H.Kubo 1998/08/26 */

/*********************************************************************/
/* File : \src\rice\src\NCU_TEL0.C									 */
/*********************************************************************/
void	NCU_TelephoneOperationTask( void );
void	NCU_TelephoneOperationExit( void );
void	TelephoneOperationTaskExit( void );

/*********************************************************************/
/* File : \src\rice\src\NCU_D_IN.C									 */
/*********************************************************************/
void	NCU_DialInAutoSwitchTask( void );
void	DialInAutoSwitchExit( void );
void	NCU_DetectDSETask( WORD * );
#if (PRO_DIALIN == ENABLE) && (PRO_NCU_TYPE == HINOKI_TYPE)
void	NCU_DICPU_Initialize(void);
#endif

/*********************************************************************/
/* File : \src\rice\src\NCU_RING.C									 */
/*********************************************************************/
void	NCU_DetectFnetTask( void );
void	FnetChildTaskExit( void );
void	NCU_FrequencyCheckTask( void );
void	NCU_TimeUpTask( void );
#if defined (KEISATSU) /* Added by SMuratec óõ 2005/07/01 */
void	NCU_DBCIFreqCheckTask( void );
void	NCU_DBCITimeUpTask( void );
#endif /* defined (KEISATSU) */
void	SetTimerValue( void );
UBYTE	SetRingCounter( void );
#if defined (KEISATSU) /* åxé@FAX DVT_ID37 Added by SMuratec óõ 2005/11/12 */
UBYTE	GetRingCounter( UBYTE );
#endif /* defined (KEISATSU) */
UBYTE	SetSamplingCounter( void );
UBYTE	CompareSamplingTone( void );
void	InitializeGrovalData( void );
void	StoreRingingOnTime( UBYTE  * );
void	StoreRingingOffTime( UBYTE	* );
void	StopOneshotTimer( void );
UBYTE	CheckContinueAndDoubleRing( void );
void	SetTeachingPattern( UBYTE  );
UBYTE	DetectRingTone( void );
UBYTE	DetectRingToneAndCar( UWORD mailbox ); /* For numberdisplay added by H.Kubo 1998/10/20 */
UBYTE	CiCheckRequest( void );
#if defined (KEISATSU) /* åxé@FAX Added by SMuratec óõ 2005/08/11 */
#if (PRO_NUMBER_DISPLAY == ENABLE)  /* åxé@FAX (ÉiÉìÉoÅ[ÉfÉBÉXÉvÉåÉC) Modify by SMuratec óõ 2005/10/20 */
UBYTE	Detect2ndRingToneAndCar( UWORD mailbox );
#else
UBYTE	Detect2ndRingTone( void );
#endif
UBYTE	CiCheckRequest2nd( void );
void	NCU_Detect2ndCalledTask( WORD * );
void	Det2ndCallChildTaskExit( void );
/* åxé@FAX Added by SMuratec óõ 2005/10/26 */
void	NCU_Detect2ndCalledExit(void);
#endif /* defined (KEISATSU) */
void	NCU_DetectCalledTask( WORD * );
void	DetCallChildTaskExit( void );
void	NCU_DetectCalledExit( void );
UBYTE	NCU_IsCarWaitedFor(void); /* added by H.Kubo 1998/08/12 */
UBYTE	NCU_IsCarReceived(UWORD on_time, UWORD off_time); /* added by H.Kubo 1998/07/23 */
void 	NCU_ND_AdaptToReceivedCAR(UWORD on_time, UWORD off_time); /* added by H.Kubo 1998/10/16 */
UBYTE 	NCU_CheckCarAfterCiCycleTimeup(UWORD ci_end_time, UWORD *ci_start_time, UBYTE *counter); /* added by H.Kubo 1998/10/16 */
UWORD	NCU_CI_MinOnTime(void); /* 1999/12/06 by K.Okada */

/*********************************************************************/
/* File : \src\rice\src\NCU_TEL1.C									 */
/*********************************************************************/
#if ( PRO_INTER_COM == ENABLE )
void	InternalAndThreePartiesCom( WORD * );
UBYTE	InternalCalling( WORD * );
void	InterComChildTaskExit( void );
void	InternalComOperation( WORD * );
#endif
void	HoldOperation( WORD * );
void	TelephoneDialing( void );
#if (PRO_LINENUMBER == TWICE_LINE)	/* ã^éóÇQâÒê¸édól by T.Soneoka 1997/11/25 */
UBYTE	TransferReceive(UBYTE(*)( void ));
#else
void	TransferReceive( WORD *, UBYTE	(  *)( void ));
#endif
void	NCU_TelephoneExecuteTask( WORD * );
void	NCU_TelephoneExecuteExit( void );

/*********************************************************************/
/* File : \src\rice\src\NCU_TAD.C									 */
/*********************************************************************/
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/09/08 */
void	NCU_DetectNoiseTask( struct NoiseData_t * );
#endif /* (PRO_MODEM == ORANGE3) */
void	NCU_DetectSilentTask( UWORD * );
void	SilentChildTaskExit( void );
void	NCU_DetectSilentExit( void );
void	NCU_FaxTadAutoSwitchTask( WORD * );
void	FaxTadChildTaskExit( void );
void	NCU_FaxTadAutoSwitchExit( void );

/**********************************************************************/
/* File : \src\rice\src\NCU_SUB0.C ÅiÇnÇgåüèoÅj						  */
/**********************************************************************/
void	OhPortStatusRead( void );
#if defined (KEISATSU) /* Modify by SMuratec óõ 2005/08/01 */
void	NCU_HdstShift(void);
#endif /* defined (KEISATSU) */
#if ( PRO_BRANCH_RX == ENABLE )
	#if (PRO_CPU == V53)
void	BranchDataInitialize( void );
	#endif
UBYTE	OnToOffHookLevelCheck( void );
UBYTE	OffToOnHookLevelCheck( void );
UBYTE	CMLAndOffHookLevelCheck( void );
UBYTE	CiInputLevelCheck( void );
void	InitializeBRCOhBuffer( void );	/* Add by TH92115 1995/02/08 */
void	SetStableTime( void );			/* Add by TH92115 1995/02/08 */
void	BRCTelOhCounterSet( void );		/* Add by TH92115 1995/01/07 */
void	BRCOhLevelCorrect(void);		/* Add by TH92115 1995/01/09 */
void	DetectLineLevelState( void );	/* Add by TH92115 1995/01/17 */
void	DetectBranchPortState( void );	/* Add by TH92115 1995/01/07 */
void	LineVoltLevelPortBarrier( void );
#endif
void	NCU_TelephoneHookCheckTask( WORD * );
#if (PRO_LINENUMBER == TWICE_LINE)	/* ã^éóÇQâÒê¸édól PHONE2ÉäÉåÅ[Ç™ïWèÄÇÃèÍçáÇÕLÉäÉåÅ[ÇÕOFFÇ…ÇµÇ‹Ç∑ by T.Soneoka 1997/11/21 */
void NCU_FaxComTelHookChkTask(void);	/*  Add by T.Soneoka 1997/11/25 */
#endif
#if (PRO_REMOTE_RX == ENABLE) || (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* 1998/01/24  By T.Yamaguchi */ /* REMOTE_RX_FUNC */
void	NCU_RemoteRxSignalDetTask( WORD * );
UBYTE	NCU_RemoteRxDTMFDetect( void );
UBYTE	NCU_RemoteRxDialPulseDetect( UBYTE );
#endif
#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
UBYTE	NCU_RemoteTransferDial(void);
UBYTE	NCU_RemoteTransferOnHook(void);
UBYTE	NCU_RemoteRxDTMFDetectforDBG( void );
UBYTE	NCU_CompareRemoteNumber(UBYTE cnt);
UBYTE	NCU_CompareRemoteNumberDP(UBYTE pulse_count, UBYTE rcv_cnt);
#endif

/**********************************************************************/
/* File : \src\rice\src\NCU_SUB1.C Åiã^éóÉxÉãñ¬ìÆÅj					  */
/**********************************************************************/
UBYTE	GRS_DetectStopKeyInput( void );
void	GRB_RingAndBellOn( void );
void	NCU_GenerateRingSignalTask(struct GenerateRingData_t *ring_data );
void	NCU_GenerateRingSignalExit( void );

/**********************************************************************/
/* File : \src\rice\src\NCU_SUB2.C Åiã^éóÇqÇaÇsÅ^ÇcÇsÇlÇeåüèoÅj		  */
/**********************************************************************/
void	NCU_TransRBTAndDetCNGTask( WORD * );
void	NCU_TransRBTAndDetCNGExit( void );
void	TransferModulatedFrequencyRBT( WORD );
void	TransmitTone( UWORD, UBYTE	 );
void	NCU_ReceiveDTMFTask( WORD * );
void	NCU_ReceiveDTMFExit( void );
UBYTE	DailInCompareDTMF( void );
UBYTE	InterCallCompareDTMF( void );
void	TakeInResultMessage( UBYTE	);
void	NCU_DetectRemoteDTMFTask(void);
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/04  By T.Yamaguchi */
UWORD	VoiceAnswer(void);
#endif

/*********************************************************************/
/* File : \src\rice\v53\src\INT_NCU.ASM								 */
/*********************************************************************
void	CI_Check( void );
*/
/*********************************************************************/
/* File : \src\rice\h8\src\NCU_INT.C								 */
/*********************************************************************/
#if 0  /* (PRO_CPU == H8 ) */
void	INT_CI_Interval( void );
#endif
/********************************************************************/
/* File : \src\rice\src\NCU_RLY.C									*/
/********************************************************************/
void	AfterCI_TimerSet( void );
void	PauseControl( void );
void	InterRelayTimer( void );
UBYTE	SilentReceiveRequest( void );
void	InitializeRelay( void );
void	CallingRelayControl( void );
void	ReverseRelayControl( void );
void	HookKeyOnRelayControl( void );
void	HookKeyOffRelayControl( void );
void	HookingRelayControl( void );
#if (PRO_LINENUMBER == TWICE_LINE)	/* ã^éóÇQâÒê¸édól by T.Soneoka 1997/11/26 */
void	HookingRelayControlTel2Ext(UBYTE tel_line);
UBYTE	TelToFaxRelayControlTel2Ext(UBYTE tel_line);
#endif
UBYTE	TelephoneToFaxcomRelayControl( UBYTE , UBYTE  (	 *)( void ));
void	ModemOnRelayControl( void );
void	HoldKeyOnRelayControl( void );
void	HoldKeyOffRelayControl( void );
void	TelIndependentRelayControl( void );
void	SignalChangeRelayControl( void );
void	DTMFDialStartRelayControl( void );
void	DPDialStartRelayControl( void );
void	DialEndRelayControl( void );
#if ( PRO_DIALIN == ENABLE )
void	DialIn1stAnswerRealyControl( void );
void	DialIn2ndAnswerRelayControl( UBYTE	 );
#endif
void	GenerateRingStartRelayControl( void );
void	GenerateRingEndRelayControl( void );
void	GenerateRingKeyOn( void );
void	GenerateRingKeyOff( void );
void	DialinIndependentRelayControl( UBYTE  );
void	GenerateRingPreventRelayControl( UWORD );
#if ( PRO_INTER_COM == ENABLE )
void	InterCallStartRelayControl( void );
void	InterCallStopRelayControl( void );
void	InterComStartRelayControl( void );
void	TransferChangeRelayControl( void );
void	ThreePartComStartRelayControl( void );
void	ThreePartComStopRelayControl( void );
void	ThreePartComResetRelayControl( void );
#endif
void	Flash_Off_On( UBYTE	 );
/*	void	MercuryDial( UBYTE	);	*/
#if defined(JPN)
void	F_Net_DisconnectRelayControl(void); /*1996/12/02 Eguchi*/
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* by H.Kubo 1998/10/14 */
void NCU_ND_CarWaitingRelaySetting(void);
void NCU_ND_AfterNdRxRelaySetting(void);
#endif

/*********************************************************************/
/* File : \src\rice\src\NCU_ND.C									 */
/*********************************************************************/
void NCU_ND_RxProcedureTask(WORD *mailbox);
UBYTE NCU_ND_CheckOH2(UWORD , UWORD ); /* by H.Kubo 1998/10/22 */
void NCU_ND_Make1stResponse(void);
UBYTE	NCU_ND_ReceiveInformation(UBYTE **offset, UWORD *);
void NCU_ND_RxProcKillChildTasks(void);
void NCU_ND_RxProcedureTaskExit(void);
void NCU_ND_MakeFinalResponse(void);
UBYTE NCU_ND_CheckWaitForCAR(void);
void NCU_ND_InitializeStatus(void);
void	NCU_ND_DetectDSETask(UWORD *message_box);
void NCU_ND_InitializeVariables(void);
UWORD NCU_ND_GetDataTimerInterval(void);
void NCU_ND_WaitFor2ndResponseTime(UWORD data_end_time, UWORD rx_accepting_signal_time);
void NCU_ND_InitializeCarPattern(void); /* added by H.Kubo 1998/10/12 */
void NCU_ND_SetModemDialinStatus(UBYTE din_status);
void NCU_ND_SetRingDetectedStatus(void); /* added by H.Kubo 1998/10/21 */
UBYTE NCU_ND_IsRxProcedureFinished(void);
void NCU_ND_SetCallDetectedStatus(void);
void NCU_ND_SetCarDetectedStatus(void);
UBYTE NCU_ModemDialinHandsetBehavior(void);
UBYTE NCU_ND_MakeAckResponse(void); /* added by H.Kubo 1998/10/21 */
UBYTE NCU_ND_SuspendAckResponse(void); /* added by H.Kubo 1998/10/21 */
UWORD NCU_ND_2ndResponseTime(UWORD data_end_time, UWORD rx_accepting_signal_time); /* added by H.Kubo 1998/11/25 */
UBYTE NCU_ND_ShuldSwitchToDialin(void); /* added by H.Kubo 1998/11/27 */
UBYTE  NCU_ND_SilentAfterAckResponse(void); /* added by H.Kubo 1998/11/27 */
/*********************************************************************/
/* File : \src\rice\src\NCU_NDDN.C									 */
/*********************************************************************/
UBYTE	NCU_ND_CheckDialinNumber(UBYTE *number, UBYTE length);
