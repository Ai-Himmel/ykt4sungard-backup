/*********************************************************************/
/*        ＡＮＺＵ　原稿読取(ＳＣＮ) プロト・タイプ宣言              */
/*                                                                   */
/*                                                                   */
/*                          1995/10/23                               */
/*                           坂本直史                                */
/*                                                                   */
/*********************************************************************/
/****************************************************************
* File : \src\kobe\anzu\src\SCN_STOR.C                          *
*****************************************************************/
void	SCN_Task( void );
void	SCN_DocumentOutTestTask( void );

/****************************************************************
* File : \src\kobe\anzu\src\SCN_INT.C                           *
*****************************************************************/
UWORD	SCN_Int( void );
UWORD	IDP_Int( void );
void	DS2_Int( void );
void	SCN_GearBacklashTimeOutCheck(void);
/****************************************************************
* File : \src\kobe\anzu\src\SCN_SUB.C                           *
*****************************************************************/
void	SCN_StartFeed( UBYTE );
WORD	SCN_Open( void );
UWORD	SCN_Close( UBYTE );
void	SCN_DecideReductionPattern( void );
void 	SCN_GearBackLash(void);
void	SCN_GearBackLashExit(void);
void 	SCN_RestartMotor(void);
UBYTE 	SCN_CheckMotorStop( void );
UBYTE 	SCN_CheckMotorStopAfterScan( void );
void 	SCN_SetMotorSpeed( void );
void	SCN_AdjustMotorSpeed( void );
void	SCN_Init( void );
void	SCN_MotorPowerOff( void );
void	SCN_StopMotor( void );
void	SCN_SetMotorPulse( UBYTE );
#if (PRO_FBS == ENABLE)
void	SCN_SetScanStartAndEndStep( UBYTE, UBYTE, UBYTE );
#else
void	SCN_SetScanStartAndEndStep( UBYTE, UBYTE );
#endif
void	SCN_SetDIPP_Parameter( void );
void	MAN_DocumentInTask( void );
UBYTE	SCN_GetScanMode( UBYTE );
UBYTE	SCN_GetScanDensity( UBYTE );
void	SCN_SetScanDocumentMask( void );
UWORD	SCN_GetMaxBounceStep( void );
UBYTE	SCN_IsDocumentScanning( void );
UBYTE	SCN_GetDocumentStoreCode(UBYTE, UBYTE);
UWORD	SCN_GetArithmeticReduction(void);
UWORD	SCN_GetEncodePageSize(UWORD h_resolution);
UWORD	SCN_GetEncodeOutputSize(UWORD h_resolution);
UWORD	SCN_GetEncodeMaskSize( UWORD );
UWORD	SCN_GetEncodeStoreImageRes(void);
UWORD	SCN_GetEncodeStoreCodeRes(void);
BYTE	SCN_ADF_NormalTopAdjustStep( void );
BYTE	SCN_ADF_FineTopAdjustStep( void );
BYTE	SCN_ADF_NormalEndAdjustStep( void );
BYTE	SCN_ADF_FineEndAdjustStep( void );
UBYTE	IsGrayPatternDither(UBYTE doc_item);
UWORD	GetGrayReductionPattern(UBYTE doc_item);
UBYTE	SCN_GetCopyDocStoreSize(void);
#if (PRO_CLASS1 == ENABLE)
UWORD	SCN_GetLocalScanSize(void);
UWORD	SCN_GetEncodeLocalScanSize(UWORD h_resolution);
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
UBYTE	GetInternetFaxScanMode(UBYTE);
UWORD	GetInternetFaxScanReducion(UBYTE);
UWORD	GetInternetFaxEncodeScanSize(UWORD);
UWORD	GetInternetFaxEncodeScanRes(void);
#endif

/****************************************************************
* File : \src\kobe\anzu\src\SCN_DRV.C                           *
*****************************************************************/
void	SCN_LatchMotorSpeedAndInterval( void );
void	SCN_SetMotorCurrent(  UBYTE );
void	SCN_SetLineStep( UBYTE );
void	SCN_SetScanStartStep( UWORD );
void	SCN_SetScanEndStep( UWORD );	/*	1996/05/17 By N.Sakamoto */
void	SCN_SetDS2_ON_Int( UBYTE );
void	SCN_SetDS2_OFF_Int( UBYTE );
void	SCN_SetScanStartInt( UBYTE );
void	SCN_SetScanEndInt( UBYTE );
void 	SCN_SetMotorSpeedIntervalInt( UBYTE );
void	SCN_SetLineInt( UBYTE );
void 	SCN_GeneratePrinter1KHz( void );
void	SCN_SetBuzzerFrequency( UBYTE );
void	SCN_ClearMotorPulseCounter( void );
void	SCN_StartMotorPulseCounter( void );
UWORD	SCN_ReadMotorPulseCounter( void );
void	SCN_SetMotorPulseRate( UWORD );
void	SCN_SetMotorClockwise( UBYTE );
void	SCN_SetMotor( UBYTE );
void	SCN_SetBuzzer( UBYTE );
void	SCN_SetSoftScan( UBYTE );
void	SCN_SetStartSoftScan( UBYTE );
void	SCN_SetScanDMA( UBYTE );
void	SCN_SetSoftCTSCAN( UBYTE );
void	SCN_SetMotorExciteMethod( UBYTE );
void	SCN_SetMotorIntStep( UWORD, UBYTE );
void	SCN_SetScanInterval( UBYTE, UBYTE );

/****************************************************************
**	ＦＢＳ関連  タスク/関数のプロトタイプ宣言
**		ミラーキャリッジ、原稿サイズ検出
**		\src\ichou\src\scn_fbs.c
*****************************************************************/
void	SCN_MirrorMoveTask( void );
UBYTE	MirrorMoveToReady( UBYTE );
UBYTE	MirrorMoveToADF( void );
UBYTE	MirrorMoveToFBS( void );
UBYTE	MirrorMoveFromHS( UWORD );
UBYTE	MirrorMoveFBSEndToADF(void);
void	SCN_SetMotorDrive( UBYTE );
void	SCN_StartMirror( UBYTE );
void	SCN_SetHS_OFF_Int( UBYTE );
void	SCN_SetHS_ON_Int( UBYTE );
void	SCN_CheckEndSensor( void );
UBYTE	SCN_CheckFCOT_Enable(void);
