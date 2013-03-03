#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"

BOOL	Ds1Raw(void);					/* DS1 Raw mode: TRUE On / FALSE Off */
BOOL	Ds2Raw(void);					/* DS2 Raw mode: TRUE On / FALSE Off */
BOOL	DsB4Raw(void);					/* DSB4 Raw mode: TRUE On / FALSE Off */
BOOL	QueryDs1On(void);				/* DS1 Cooked mode: TRUE On / FALSE Off */
BOOL	QueryDs2On(void);				/* DS2 Cooked mode: TRUE On / FALSE Off */
BOOL	QueryDsB4On(void);				/* DSB4 Cooked mode: TRUE On / FALSE Off */
BOOL	Ds1Changed(void);				/* Watch Cooked Mode DS1 */
BOOL	Ds2Changed(void);				/* Watch Cooked Mode DS2 */
BOOL	DsB4Changed(void);				/* Watch Cooked Mode DSB4 */
BOOL	InterLock4ScanChanged(void);	/* Watch Cooked Mode InterLock for Scanner */
BOOL	InterLock4ScanRaw(void);		/* InterLock for Scanner Raw mode: TRUE Close / FALSE Open */
BOOL	QueryCloseInterLock4Scan(void); /* InterLock for Scanner Cooked mode: TRUE Close / FALSE Open */
void	InzTxMotor(void);				/* Initialize Tx Motor Parameter */
void	SetupTxMotor(BYTE);				/* Tx Motor Parameter Setup */
void	IntTxMotor(void);				/* Interupt Routine for Tx Motor Control */
void	StartTxMotor(void);				/* Move Tx Motor by Previous Setuped Parameter */
void	StopTxMotor(void);				/* Stop Tx Motor */
void	PauseTxMotor(void);				/* Pause Tx Motor */
void	CurrentDownTxMotor(void);		/* Tx Motor 電流(小) */
void	StopExciteTxMotor(void);		/* Tx Motor 非励磁 */
void	MoveScan1Line(void);			/* Move Document to 1 Line each mode */
void	FeedOutDoc(void);				/* Document feed out */
BOOL	QueryDocMoveNow(void);			/* Query Document Move Now */
BOOL	CheckMotorStop(void);			/* モータ停止確認 */
void	AdjustTxMotor(void);			/* モータの相合わせ */
void	TxMotor200_1_2_1StepStart(void);/* ２００ｐｐｓ１－２相で１Ｓｔｅｐだけ回す関数 */
void	CheckTxMotorTMSEL_1_2(void);	/* １－２相のステップを積算します */
BOOL	QueryTxMotorMoving(void);		/* Tx Motor Moving? TURE:Moving FALSE:Stoping */
BYTE	QueryFeederDocSize(void);		/* Query Document Width:DOC_*_SIZE(doc.h) */
BYTE	QueryCurrentDocSize(void);		/* Query Current Document Size */
WORD	QueryDocMovedStep(void);		/* Query Current Moved Steps from DS1 ON */
BYTE	QueryDocMode(void);				/* Query Currnent Resolution (NORM/FINE/SFINE) */
BOOL	QueryMoreDoc(void);				/* Query More Document TRUE: Exist Next Page /FALSE:No more Pages */
BYTE	QueryDocPosition(void);			/* Query Document Current Position */
BOOL	QueryDocScannable(void);		/* Query Document Scannable */
UBYTE	QueryStoreCode(void);			/* Query Store Coding Mode */
BYTE	QueryStoreMode(void);			/* Query Stored Mode */
BOOL	QueryClass1Tx(void);			/* Query Class1 Tx */
BYTE	QueryAdjustDocSize(void);		/* Query Adjuct Document Size */
BYTE	QueryStoreDensity(void);		/* Query Stored Document Density */
BOOL	Query1_2Scan(void);				/* Query 1/2 Scan or Not */
BOOL	QueryDocumentChanged(void);		/* Query Document has changed */
void	InzDocObj(void);				/* 原稿オブジェクトを初期化 */
void	SaveScanningMode(UBYTE);		/* SYS_* see doc.h */
UBYTE	QueryScanningMode(void);
struct ScanPageAtr *CreateDocObj(void); /* Document Object を作成し,そのポインタを返す */
void	DeleteDocObj(struct ScanPageAtr **);		/* 原稿オブジェクトを削除 */
void	SetScanPageAttribute(struct ScanPageAtr *);			/* 原稿属性設定 */
void	SetScanPageAttribute2(struct ScanPageAtr *);			/* 原稿属性設定 */
void	UpdateDocPosition(void);		/* 原稿位置ステータス更新 */
void	UpdateNextDocPosition(void);	/* Update Next Document Postion Status */
void	WaitDocChanged(void);
void	WaitNextDoc(void);
UBYTE	QueryReduction(void);

BOOL	QueryScanning(void);			/* Now Scanning? TRUE:Scanning /FALSE:Not Scanning */
UWORD	QueryScannerError(void);		/* What kind of Scanner Error */
BOOL	QueryScannerDocReady(void);		/* Document is Ready Position and Scanner is not busy. */
void	InzScannerBackupData(void);		/* Backup Data Initialize */
void	OpenScanner(void);				/* Pre Process for Scanning */
UWORD	SCN_Close(UBYTE);				/* Post Process for Scanning */
WORD	SCN_Open(void);					/* Pre Process for Scanning Page */
void	CloseScanPage(void);			/* Post Process for SCanning Page */
void	CreateDocument4ScanStart(void);
#if (PRO_STAMP == ENABLE)
void PushStamp(void);
void SetStampExec(void);
#endif
void	DisableIntScannerTimer(void);	/* Scanner Interrupt Disable */
void	ScannerInt(void);				/* Scanner Interrupt */
BOOL	QueryScanNow(void);				/* Query Scan Now */
void	MakeScannerEvents(void); 		/* Make Scanner Events */
void	MakeSensorEvents(void);			/* Make Sensor Events */
void	CheckScanBufReadableLine(void);
void	SetScanBufferBlock(void);
void	SCN_Init(void);		/* Ininitalize Scanner Task Parameters */
void	CreateScannerTasks(void);		/* Create Always Runngin Scanner Tasks */
UWORD	CheckScanLimit(UBYTE);

UBYTE CheckNeedDocPageNum(void);		/* Remane UBYTE CheckDocPage(void) by O.Kimoto 1998/12/17 */
UBYTE CheckExceedDocPageNum(void);		/* Add by O.Kimoto 1998/12/17 */
void IncPage(void);
void IniMemWriteParameter(void);

void	WaitScanStart(void);
void	ClearMessageBody(MESSAGE_t *);
void	TxMortorTest(void);
BOOL	CIS_CCD_Test(void);

/****************************************************************************
 *	Scanner Buffer Control
 ****************************************************************************/
void	InzScanBuf4GateArray(void);		/* Gata Array 設定 */
void	InzScanBuf(void);				/* Initialize Scanner Buffer */
BOOL	EnableToWriteScanBuf(void);		/* Enable to Write Scanner Buffer */
BOOL	EnableToReadScanBuf(void);		/* Enable to Read Scanner Buffer */
BOOL	EnableStartToReadScanBuf(void);
void	PutLineScanBuf(					/* Put Line Scanner Buffer */
	UBYTE	*Source,					/* Source となる Image の先頭アドレス */
	WORD	LineWidth);					/* 転送バイト数（1ラインの幅） */
void	AutoPutLineScanBuf(void);		/* GateArray によるPut Line Scanner Buffer */
void	CountUpScanBufIndex(void);		/* タイミングをはかって、Scanner Buffer の属性を更新 */
UBYTE	*GetLineAddress4ReadScanBuf(void); /* Get Line Address for Read from Scanner Buffer */

/****************************************************************************
 *	Scanner Page Memory Control
 ****************************************************************************/
void	InzScanPageMem(void);			/* Scanner Page Memory 初期化 */
BOOL	EnableToWriteScanPageMem(void);	/* Enable to Write Scanner Page Memory */
BOOL	EnableToReadScanPageMem(void);	/* Enable to Read Scanner Page Memory */
void	PutLineScanPageMem(UBYTE *);	/* Put Line Scanner Page Memory */
UBYTE	*GetLineAddress4ReadScanPageMem(void); /* Get Line Address Scanner Page Memory */
void DecScanPageMemReadableLine(void);	/* Decrement ScanPageMemReadbleLine */
void DecScanBufReadableLine(void);		/* Decrement ScanBufReadbleLine */
void IncScanBufReadableLine(void);
UBYTE *MemoryCopy(
UBYTE	*DST_ptr,	/* コピー先の先頭アドレス */
UBYTE	*SRC_ptr,	/* コピー元の先頭アドレス */
UWORD	CopyCount);		/* コピー数 */
UWORD QueryScanPageMemReadableLine(void);



/*
 *	Prototypes
 */
void	InzImageProcessor(void);		/* Initialize Image Processor */
void	ClearIPInternalMemory(void);	/* Clear Image Processor Internal Memory */
void	SetupScanBuf(void);				/* Setup Scanner Buffer */
void	WaitIflgOff(void);				/* Wait IFLG Off */
void	SetAgc(void);					/* Set Auto Gain Control */
UBYTE	CalcCenterAverage(				/* Caluculate Center Average */
	UBYTE	Smpl[10]);					/* Sample Data */
void	SetClamp(						/* Set Digital Clamp Parameter */
	 UBYTE	Mode,						/* デジタルクランプのモード(IP_DC_XX) */
	 UBYTE	ClampPoint);				/* クランプ位置 */
void	MakeShadingData(void);			/* Make Shading Data */
void	SetShadingData(void);			/* Set Shading Data */
void	SetResolutionTrasnfrom(void);	/* Set Resolution Transform */
void	SetGammaCorrection(
	UBYTE	ScanMode,					/* 送信モード(doc.h) */
	UBYTE	Density);					/* 読み取り濃度(doc.h)  1998/07/20 by T.Soneoka */
void	Set2DFilter(					/* Set 2D Emphasize Filter */
	UBYTE	ScanMode);					/* 送信モード(doc.h) */
void	SetGrayScaleMode(void);			/* Set Gray Scale Mode */
/* void	Set2ChiParamater(void);			/@ Set 2Chi Parameter @/ 1998/07/20 by T.Soneoka */
/* void	Set2ChiParamater(UBYTE Density);/@ Set 2Chi Parameter @/ 1999/06/29 by T.Soneoka */
void	Set2ChiParamater(UBYTE ,UBYTE);	/* Set 2Chi Parameter */
void	SetZouikiBunri(					/* Set Gray Scale Mode */
	UBYTE	ScanMode);					/* 送信モード(doc.h) */
void	SetScannerReduction(			/* Set Scanner Reduction */
	UBYTE	HReductionRate,				/* 主走査方向縮小率 */
	UBYTE	VReductionRate);			/* 副走査方向縮小率(IP_SUBM_*) */
void	ScanExecFlagOn(void);			/* ScanExecFlagOn */
void	ScanExecFlagOff(void);			/* ScanExecFlagOff */
BOOL	QueryScanExecFlag(void);		/* QueryScanExecFlag */
void	Set2ChiProcessingMode(void);	/* 補正処理、二値化処理モードに設定 */
void	WaitScanLineInt(void);
void	SetImageProcessor4Scan(
	struct ScanPageAtr	*Page);			/* see feeder.h */
void	InzThermistorRef(void);
UBYTE	ReadThermistor(void);			/* Read Thermistor A/D Value */
UBYTE 	QueryCalPos(UBYTE, UBYTE);
void MakeDirectGammmaData(UBYTE, UBYTE, UBYTE, UBYTE *); /* 1999/06/28 by T.Soneoka */

void	ScannerPowerOn(void);
void	ScannerPowerOff(void);

#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/11 T.Takagi */
void	MakeShadingDataForRedScan(void);
void	SetAgcForRedScan(void);
void	InzImageProcessorForRedScan(void);	/* 2002/03/29 T.Takagi */
#endif

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
/****************************************************************************
 *	LC821033仕様
 ****************************************************************************/
void	Set2DFilter_LC821033(			/* Set 2D Emphasize Filter */
	UBYTE,								/* 送信モード(doc.h) */
	UBYTE);								/* 読み取り濃度(doc.h) */
UBYTE	LC821033_CheckIMFLG(void);		/* LC821033 内部リフレッシュ処理フラグ 					*/
void	LC821033_SetMSEL(UBYTE);		/* LC821033 歪み補正メモリ選択							*/
void	LC821033_SetMFLG(UBYTE);		/* LC821033 歪み補正メモリ								*/
void	LC821033_Set2DFilter(UWORD);	/* LC821033 強調度選択・二次元フィルタ選択				*/
void	LC821033_SetTMPR(UBYTE);		/* LC821033 D/A 設定値制御								*/
UBYTE	LC821033_CheckDAHA(void);		/* LC821033 センサ信号期間A／Dハイリファレンス用D/A値	*/
void	LC821033_SetDAHA(UBYTE);		/* LC821033 センサ信号期間A／Dハイリファレンス用D/A値	*/
UBYTE	LC821033_CheckFF(void);			/* LC821033 "FF"値カウント								*/
void	WaitIflgOn(void);				/* LC821033 IFLGが1になるのを待つ						*/
void	WaitImflgOn(void);				/* LC821033 IMFLGが1になるのを待つ						*/
void	WaitImflgOff(void);				/* LC821033 IMFLGが0になるのを待つ						*/
UBYTE	LC821033_PGB9(void);			/* 画処理選択 */
#endif	/* End of defined(HINOKI2) */

