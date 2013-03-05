/*
 *	@(#)%W%
 *	FileName:	/home2/prj/Eva/Src/scn/scanner.c
 *	Create:	Thu Jan  8 14:23:01 1998	by	ishiyama
 *	Description:
 *		Scanner Class Functions
 *		Scanner Pre/Post 処理,1Line 読込み
 *	Change Log:
 *		\prj\eva\src\scn\scanner.cからコピーし、HINOKI用にメンテしました
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\atlanta\define\syslocal.h"

/*
 *	attribute
 */
/*
 *	Name:	Query Now Scanning
 *	Create:	Thu Jan  8 14:25:34 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		BOOL	QueryScanning(void);
 *	Description:
 *		Scannig or not
 *	Return Value:
 *		TRUE:	Scanning
 *		FALSE:	Not Scanning
 *	Change Log:
 *		
 */
BOOL	QueryScanning(void)
{
	return	NowScanning;
}

/*
 *	Name:	Query What kind of Scanner Error
 *	Create:	Thu Jan  8 14:27:21 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		UWORD	QueryScannerError(void);
 *	Description:
 *		スキャナエラーの種類を返す
 *	Return Value:
 *		TBD
 *	Change Log:
 *		
 */
UWORD	QueryScannerError(void)
{
	return	ScannerError;
}

/*
 *	Name:	Query What kind of Scanner Error
 *	Create:	Fri Jan  16 9:55:17 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		BOOL	QueryScannerDocReady(void);
 *	Description:
 *		スキャナが使用中でなく、原稿がセットされている
 *	Return Value:
 *		TRUE:	DS2 がオンで、スキャナは未使用
 *		FALSE:	上記以外
 *	Change Log:
 *		
 */
BOOL	QueryScannerDocReady(void)
{
	BOOL	rtn;

	if (QueryDocPosition() == DOC_POS_MOVE_TO_SCAN && !NowScanning) {
		rtn = TRUE;
	} else {
		rtn = FALSE;
	}
	return	rtn;
}

/*
 *	method
 */
/*
 *	Name:	Initialize Scanner Backup Parameters
 *	Create:	Mon Jun 22 17:53:40 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	InzScannerBackupData(void);
 *	Description:
 *		スキャナ固有のバックアップデータを初期化する。
 *		マシンパラメータ、ユニークスイッチなどは、別途初期化
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzScannerBackupData(void)
{
	CONST UBYTE	*SrcPtr;
	UBYTE	*DestPtr;
	WORD	Counter;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/12/03 */
	if (LC821033_PGB9()) {
		SYB_LC821033_Flg = TRUE;	/* LC821033対応フラグ */
	}
	else {
		SYB_LC821033_Flg = FALSE;	/* LC82103対応フラグ */
	}
#endif

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (!SYB_LC821033_Flg) {					/* LC82103対応フラグがOFF Y.Kano 2003/11/27 */

		SYB_BlackCorrectionData = IniSreg[0x9];
		SYB_AgcDaLowReference = IniSreg[0x11];
		SYB_AgcDaHighReference = IniSreg[0x13];

  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/06 T.Takagi */
		/* とりあえず通常と同じ値を入れておく（暫定） */
		SYB_BLK_CorrectionDataForRedSCN = IniSreg[0x9];
		SYB_AgcDaLowReferenceForRedSCN = IniSreg[0x11];
		SYB_AgcDaHighReferenceForRedSCN = IniSreg[0x13];
  #endif
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	SYB_BlackCorrectionData = IniSreg[0x9];
	SYB_AgcDaLowReference = IniSreg[0x11];
	SYB_AgcDaHighReference = IniSreg[0x13];

  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/06 T.Takagi */
	/* とりあえず通常と同じ値を入れておく（暫定） */
	SYB_BLK_CorrectionDataForRedSCN = IniSreg[0x9];
	SYB_AgcDaLowReferenceForRedSCN = IniSreg[0x11];
	SYB_AgcDaHighReferenceForRedSCN = IniSreg[0x13];
  #endif
#endif	/* End of defined(HINOKI2) */

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/13 T.Takagi */
	if (SYS_HaltClock == FALSE) {		/* この時点でクロックが供給されていなければ */
		HaltClockOn();
		wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
		SubResetOff();
		SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
	}
#endif

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		/** 画処理ＩＣのシェーディングデータが壊れている為、再セットしなおします。by Y.Kano 2003/08/12 */
		SetShadingData();
		SYS_ShadingDataSet = TRUE;	/* シェーディングデータがセットされている状態を示す */

	}
	else {	/* LC82103仕様 */
		InzImageProcessor();

		SrcPtr = &ShadingRamInitTable[0];
		DestPtr = &SYB_ShadingRAM[0];
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = *SrcPtr++;
		}

  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/06 T.Takagi */
		/* とりあえず通常と同じ値を入れておく（暫定） */
		SrcPtr = &ShadingRamInitTable[0];
		DestPtr = &SYB_ShadingRAM_ForRedScan[0];
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = *SrcPtr++;
		}
  #endif
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	InzImageProcessor();

	SrcPtr = &ShadingRamInitTable[0];
	DestPtr = &SYB_ShadingRAM[0];
	for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
		*DestPtr++ = *SrcPtr++;
	}

#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/06 T.Takagi */
	/* とりあえず通常と同じ値を入れておく（暫定） */
	SrcPtr = &ShadingRamInitTable[0];
	DestPtr = &SYB_ShadingRAM_ForRedScan[0];
	for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
		*DestPtr++ = *SrcPtr++;
	}
#endif
	/* Image Processor へのろーどは、別途行う。*/
#endif	/* End of defined(HINOKI2) */
}
/*
 *	Name:	Open Scanner
 *	Create:	Tue Jan 13 12:13:19 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	OpenScanner();
 *	Description:
 *		原稿読取り準備設定
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	OpenScanner(void)
{
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif

	LampOn();

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/29 T.Takagi */

	/* ここで読み取りに必要なクロックを供給します
	** SCANNER_BUSYが解放されるまで供給されます		 */

	if (SYS_HaltClock == FALSE) {	/* 現在クロックが供給されていなければ */
		HaltClockOn();
		wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
		CMN_DisableInterrupt();			/**	割り込み禁止 クロックが止まってるのにフラグが落とされないとまずいので追加 2002/03/07 T.Takagi */
		SubResetOff();
		SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
		CMN_EnableInterrupt();			/**	割り込み許可	*/
		wai_tsk(1);					/* 2002/03/12 T.Takagi */
	}

	/*
	 *	Shading Data Set
	 *	Power On 後の最初のスキャンだけ
	 */
	if (ScannerPowerOnInz) {
		ScannerPowerOnInz = FALSE;
		SetShadingData();
		SYS_ShadingDataSet = TRUE;		/* シェーディングデータがセットされている状態を示す */
	}
	/* LSIの仕様上、LSIへのCLOCKが停止されるとShading Dataがとんでしまうため
	** クロックが供給されてから最初スキャン時にShading Dataをセットする
	 */
	else if (SYS_ShadingDataSet == FALSE) {		/* シェーディングデータが消えていたら */
		SetShadingData();
		SYS_ShadingDataSet = TRUE;		/* シェーディングデータがセットされている状態を示す */
	}
 #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	else if (CHK_UNI_RedScanModeEnable()) {
		/* シェーディングデータを変える必要があるとき、シェーディングデータをセットしなおします
		** 現状朱色シェーディングがセットされているが、これから読む原稿は通常読み取りの場合、およびその逆 */
		if (((SYS_IsRedShading == FALSE) && (SYB_LocalStatus[0] & SYS_RED_SCAN))
		||  ((SYS_IsRedShading == TRUE) && (!(SYB_LocalStatus[0] & SYS_RED_SCAN)))) {
			SetShadingData();
			SYS_ShadingDataSet = TRUE;		/* シェーディングデータがセットされている状態を示す */
		}
	}
 #endif	
#else
	/*
	 *	Shading Data Set
	 *	Power On 後の最初のスキャンだけ
	 */
	if (ScannerPowerOnInz) {
		ScannerPowerOnInz = FALSE;
		SetShadingData();
	}
 #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	else if (CHK_UNI_RedScanModeEnable()) {
		/* シェーディングデータを変える必要があるとき、シェーディングデータをセットしなおします
		** 現状朱色シェーディングがセットされているが、これから読む原稿は通常読み取りの場合、およびその逆 */
		if (((SYS_IsRedShading == FALSE) && (SYB_LocalStatus[0] & SYS_RED_SCAN))
		||  ((SYS_IsRedShading == TRUE) && (!(SYB_LocalStatus[0] & SYS_RED_SCAN)))) {
			SetShadingData();
		}
	}
 #endif	
#endif

	/*
	 *	現在の原稿と次の原稿を区別するため
	 */
	SCN_DocumentChanged = FALSE;

	/** ADF部へ移動中に前のサイズと解像度が表示されるので、一旦ここでセットする */
	SYS_DocumentScanSize = CMN_GetDocumentScanSize();

	RequestScan = FALSE;				/* 1998/12/10 by T.Soneoka */

	/* SCN_Init()内でおこなっていた原稿長制限をここにもってきました 1999/2/1 by T.Soneoka */
	/* 原稿長制限をセット */
	Ds2OnToOffErrorSteps = FEED_ERROR_3_6M;
	if (CHK_DocumentLengthLimit()) {
		Ds2OnToOffErrorSteps = FEED_ERROR_1M;
	}

	/*
	** マルチコピーの後のＢ４－＞Ａ４送信不具合
	** 1999/03/04 by T.Soneoka
	*/
	ScanReduction = REDUCTION_NO;

	/* 仕様変更
	** 読み取り中において、ＤＳ２がＯＦＦした時点でＤＳ１もＯＦＦしていれば、今読んだ原稿が
	** 最終原稿であるという風に変更
	** by O.kimoto 1999/03/08
	*/
	NoNextDocument = FALSE;

}

/*
 *	Name:	Close Scanner
 *	Create:	Tue Jan 13 12:13:13 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	CloseScanner(void);
 *	Description:
 *		全原稿読取り終了時の処理
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
UWORD SCN_Close(UBYTE close_type)
{
	UWORD	rtn_msg;
	MESSAGE_t	*RcvMessage;					/* 受信メッセージ用のエリア */

	UBYTE	type; /* 1999/02/01 by T.Soneoka */
	

	/*
	** 原稿蓄積中にカバーオープンをすると、ＴＸモータがまわりっぱなしになる
	** ＤＳ１、２がＯＦＦになると、メインタスクで原稿初期化が走るため、
	** その後、フィードアウトするとモータを止めるパスがなくなる
	** 1999/02/26 by T.Soneoka
	*/
	if (!QueryCloseInterLock4Scan()) {
		return	(SCN_DOC_EXIT_OK);
	}

	/*
	** 原稿蓄積中に原稿カバーオープン・クローズ－＞ストップキーにて原稿排出しない不具合
	** 原稿排出処理に移っても、原稿管理ブロックに登録されていない場合は登録するように変更
	** 1999/03/10 by T.Soneoka
	*/
	if (QueryDs2On()) {
		if (QueryDocPosition() == DOC_POS_NO_DOCUMENT) {
			CurrentPage = CreateDocObj();
			CurrentPage->StepsFromDs1On = Ds1ToDs2Steps+Ds2ToReadySteps;
			CurrentPage->StepsFromDs2On = Ds2ToReadySteps;
			CurrentPage->Position = DOC_POS_MOVE_TO_SCAN;
		}
	}
/* 
** 済みスタンプＯｎで排出しない不具合
** ここでリターンするとモータが回りっぱなしになる不具合
** 上記変更におけるミス
** 1999/03/11 by T.Soneoka
*/
#if (0)
**	else {
**		return	(SCN_DOC_EXIT_OK);
**	}
#endif

	/* 原稿排出処理はすべて排出中をセットします 1999/02/12 by T.Soneoka */
	SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FEED_OUT;


#if (0) /* 1998/12/04 by T.Soneoka */
**	StopTxMotor();
**	StopExciteTxMotor();
#endif
	LampOff();

	/* 原稿排出 */
	ScannerMode = SCANNER_DOC_OUT_MODE;

/*
** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
** 1999/02/01 by T.Soneoka
*/
#if (0)
**	cre_tsk(&tskno_SCN_DocOutTask, TSK_SCN_DOCUMENTOUTTASK, &close_type);
**	rcv_msg(mbxno.SCN_Task, &RcvMessage); /* 蓄積関連タスクの状況をメッセージで待ち受け */
**	
**	if (tskno_SCN_DocOutTask != 0xffff) {
**		del_tsk(&tskno_SCN_DocOutTask);
**	}
**
**	switch (RcvMessage->Message) {
**	case MSG_DOCOUT_FEED_ERROR:
**		rtn_msg = SCN_DOC_FEED_ERROR;
**		break;
**	case MSG_DOCOUT_COVER_OPEN:
**		rtn_msg = SCN_SCANNER_COVER_OPEN;
**		break;
**	case MSG_DOCOUT_EXIT:
**		rtn_msg = SCN_DOC_EXIT_OK;
**		break;
**	}
**	return	rtn_msg;
#else
	if ((close_type == FROM_MAIN)
	||  (close_type == FROM_DOCSTORE)) {
		type = FEED_CHECK;
		cre_tsk(&tskno_SCN_DocOutTask, TSK_SCN_DOCUMENTOUTTASK, &type);
		rcv_msg(mbxno.SCN_Task, &RcvMessage); /* 蓄積関連タスクの状況をメッセージで待ち受け */
		
		if (tskno_SCN_DocOutTask != 0xffff) {
			del_tsk(&tskno_SCN_DocOutTask);
		}
	
		switch (RcvMessage->Message) {
		case MSG_DOCOUT_FEED_ERROR:
			rtn_msg = SCN_DOC_FEED_ERROR;
			break;
		case MSG_DOCOUT_COVER_OPEN:
			rtn_msg = SCN_SCANNER_COVER_OPEN;
			break;
		case MSG_DOCOUT_EXIT:
			rtn_msg = SCN_DOC_EXIT_OK;
			break;
		}
		return	rtn_msg;

	} else {	/* close_type == FROM_FCM */
		type = NO_FEED_CHECK;

#if (0) /* 上でまとめて行なうようにします 1999/02/12 by T.Soneoka */
**		/* 原稿排出途中で止まる不具合 1999/2/1 by T.Soneoka */
**		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FEED_OUT;
#endif
		cre_tsk(&tskno_SCN_DocOutTask, TSK_SCN_DOCUMENTOUTTASK, &type);
		return	(SCN_DOC_EXIT_OK);

	}
#endif
}

/*
 *	Name:	Open Scanning Page
 *	Create:	Tue Jan 13 13:44:46 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	OpenScanPage(void);
 *	Description:
 *		原稿読取りページ毎前処理
 *		1)Image Processoer のページ毎の前処理
 *		2)Gate Array に Scanner Buffer のアドレスとサイズを指示
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
WORD	SCN_Open(void)
{
	BYTE	FeederMode;

	/*
	 *	画処理 IC の設定
	 */
	InzScanBuf();

#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/23 T.Takagi */
	if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
		if (SYS_IsRedShading == TRUE) {
			InzImageProcessorForRedScan();
		}
		else {
			InzImageProcessor();
		}
	}
	else {
			InzImageProcessor();
	}
#else
	InzImageProcessor();
#endif
	ClearIPInternalMemory();
	SetImageProcessor4Scan(CurrentPage);

	/* ゲートアレイのスキャナバッファのアドレス等、再度初期化します 98/08/28 */
	InzScanBuf();

	/*
	 *	読取りタイミング作成用カウンタをセット
	 *	サイクルの最後で読みたいときは,ScanTimingTable[] の値を初期値にする
	 */
	ScanTimingBase = 1;

#if (0) /* 割り込み中でセットします 1998/12/8 by T.Soneoka */
**	/*
**	 *	割込みでの読取り許可
**	 */
**	NowScanning = TRUE;
#endif
	NowScanning = FALSE;
	IsScanOpen = TRUE;	/* 1998/12/10 by T.Soneoka */

	/*
	** 原稿蓄積にて、１ページ読み取り完了する前に、原稿排出完了する仕様変更
	**  1999/02/24 by T.Soneoka
	*/
	SYS_ForcedMemoryOverMsg = 0;
	if (SYS_StampFlag) {
		Ds2ToPushStampSteps = FROM_DS2_TO_STAMP;
	} else {
		Ds2ToPushStampSteps = Ds2ToExitSteps;
		SYS_ForcedMemoryOverMsg = 1;
	}


	/*
	 *	現在の原稿と次の原稿を区別するため
	 */
	SCN_DocumentChanged = FALSE;

	/*
	 *	Tx Motor 設定, 起動開始
	 */
	if (Debug_MoveToScan200pps &&
	   ((ScannerMode == SCANNER_COPY_MODE) ||
	    (ScannerMode == SCANNER_DOC_SCAN_MODE))) {
		FeederMode = FEEDER_MOVE_TO_SCAN;
	} else {
/*
** Ｇ３送信時にフィルが出過ぎて、受信側が回線断する不具合（Laser Faxで発生）
** この処理をしていないと、ＳＦＩＮＥで４秒強のＦＩＬＬが出ていた
** 1999/02/25 by T.Soneoka
*/
#if (0)
**		switch (CurrentPage->VerticalMode) {
**		case TX_MOTOR_NORMAL_SCAN:
**			FeederMode = FEEDER_NORMAL_SCAN;
**			break;
**		case TX_MOTOR_FINE_SCAN:
**			FeederMode = FEEDER_FINE_SCAN;
**			break;
**		case TX_MOTOR_SFINE_SCAN:
**			FeederMode = FEEDER_SFINE_SCAN;
**			break;
**		case TX_MOTOR_FINE1_2_SCAN:
**			FeederMode = FEEDER_FINE1_2_SCAN;
**			break;
**		case TX_MOTOR_SFINE1_2_SCAN:
**			FeederMode = FEEDER_SFINE1_2_SCAN;
**			break;
**		default:
**			/* not reached */
**			break;
**		}
#else
		FeederMode = FEEDER_NORMAL_SCAN;
#endif
	}
	SetupTxMotor(FeederMode);
	

	/* 原稿引き抜き対策 by O.Kimoto 1999/01/12 */
	if (!Ds2Raw()) {
		CurrentPage->Position = DOC_POS_MOVE_TO_DS2;
		CurrentPage->StepsFromDs1On = 0;
		CurrentPage->StepsFromDs2On = 0;
	}

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
	PC_24V_On();
#endif
	CluchOn();
	StartTxMotor();

	return (SCN_OPEN_OK);
}


/*
 *	Name:	Close Scanning Page
 *	Create:	Tue Jan 13 13:46:21 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	CloseScanPage(void);
 *	Description:
 *		原稿読取りページ毎修了時処理
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	CloseScanPage(void)
{

	/*
	 *	割込みでの読取り禁止
	 */
#if (0) /* 1998/12/10 by T.Soneoka */
**	NowScanning = FALSE;
#endif
	IsScanOpen = FALSE;

	/*
	** 原稿蓄積にて、１ページ読み取り完了する前に、原稿排出完了する仕様変更
	**  1999/02/26 by T.Soneoka
	*/
#if (0)
**	StopTxMotor();	/* 1998/12/10 by T.Soneoka */
#endif
}

void CreateDocument4ScanStart(void)
{
	CurrentPage = CreateDocObj();
	CurrentPage->StepsFromDs1On = Ds1ToDs2Steps+Ds2ToReadySteps;
	CurrentPage->StepsFromDs2On = Ds2ToReadySteps;
	CurrentPage->Position = DOC_POS_MOVE_TO_SCAN;
}
