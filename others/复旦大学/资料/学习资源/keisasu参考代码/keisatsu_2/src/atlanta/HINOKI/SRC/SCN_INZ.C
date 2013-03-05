/*
 *	@(#)%W%
 *	FileName:	h:/prj/Eva/Src/scn/scn_inz.c
 *	Create:	Thu Feb 26 14:19:56 1998	by	ishiyama
 *	Description:
 *		Initialize Scanner Control Valiables
 *	Change Log:
 *		
 */

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"

#if defined(HINOKI2) || defined(HINOKI3)	/* Add by Y.Kano 2003/12/08 */
#include "\src\atlanta\ext_v\bkupram.h"
#endif

/*
 *	Name:	Ininitalize Scanner Task Parameters
 *	Create:	Wed Jan  7 14:35:12 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	InzScannerParameter(void);
 *	Description:
 *		Scanner 関連大域変数初期化
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SCN_Init(void)
{

	/* Interrupt Control */
	EnableScannerInt = FALSE;			/* スキャナ割り込み禁止 */
	Make5msTiming4Scan = TRUE;			/* 5msec Timing Maker 初期化 */
	Make10msTiming4Scan = 4;			/* 10msec Timing Maker 初期化  1998/12/10 by T.Soneoka */
	ScanTimingBase = 0;					/* 読取り禁止 */
	RequestScan = FALSE;				/* 1998/12/10 by T.Soneoka */
	IsScanOpen = FALSE;					/* 1998/12/10 by T.Soneoka */

	/* Scanner Status */
	ScannerMode = SCANNER_NEUTRAL_MODE;	/* Scanner Mode */
	ScannerError = 0;					/* Scanner Error */
	NowScanning = FALSE;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/12/03 */
	if (LC821033_PGB9()) {
		SYB_LC821033_Flg = TRUE;	/* LC821033対応フラグ */
	}
	else {
		SYB_LC821033_Flg = FALSE;	/* LC82103対応フラグ */
	}
#endif


	/* Sensor Control */
	Ds1CookCounter = ScanChatCount;		/* DS1 チャタリング防止用カウンタ */
	Ds2CookCounter = ScanChatCount;		/* DS2 チャタリング防止用カウンタ */
	DsB4CookCounter = ScanChatCount;	/* DSB4 チャタリング防止用カウンタ */
	InterLock4ScanCookCounter = ScanChatCount; /* InterLock for Scanner チャタリング防止用カウンタ */

	/* 初期状態を現在値にすることで、Power ON 時には、メッセージを送らない */
	CookedDs1 = Ds1Raw();				/* DS1 Status(Cooked Mode) */
	CookedDs2 = Ds2Raw();				/* DS2 Status(Cooked Mode) */
	CookedDsB4 = DsB4Raw();				/* DSB4 Status(Cooked Mode) */
	CookedInterLock4Scan = TRUE;		/* Scanner Cover Open なら通知 */

	/* Tx Motor Control */
	PowerCtrl = 0;						/* 24V Power Control (see power.h) */
	EnableIntTxMotor = FALSE;			/* Tx Motor 用割込み処理禁止 */
	TxMotorTransCount = 0;				/* Tx Motor State Transision Counter　遷移禁止 */
	TxMotorRequest = MOTOR_SPEED_UP;		/* MOTOR_SPEED_* (motor.h) */
	InzTxMotor();						/* Include TxMotor Control on GateArray */

	/* Ininitalize Document Object */
	InzDocObj();

	 /* for Load Shading Data */
	ScannerPowerOnInz = TRUE;

	/*
	 *	Interrupt Control
	 */
	EnableScannerInt = TRUE;			/* スキャナ割り込み許可 */

	/*
	** 読み取りを実行するまで、Ds2OnToOffErrorStepsの初期化が通らないので、
	** 原稿排出時に待機状態からストップキーＯｎでフィードエラーが発生する
	** 下記動作を復活させます
	** 1999/02/09 by T.Soneoka
	*/
#if (0)
**#if (0) /* ここは、電源Ｏｎ時しか通らないので、メモリＳｗを変更しても変わらない！！ */
****	/* 原稿長制限をセット */
****	Ds2OnToOffErrorSteps = FEED_ERROR_3_6M;
****	if (CHK_DocumentLengthLimit()) {
****		Ds2OnToOffErrorSteps = FEED_ERROR_1M;
****	}
**#endif
#else
	Ds2OnToOffErrorSteps = FEED_ERROR_3_6M;
	if (CHK_DocumentLengthLimit()) {
		Ds2OnToOffErrorSteps = FEED_ERROR_1M;
	}
#endif

	ExecutePushStamp = FALSE;
	SYS_StampFlag = 0;

	CluchOff();

	LampOff();					/* ランプ消灯 */

	Debug_MoveToScan200pps = 0;

	MotorExciteCount = STOP_EXCITE_COUNT;	/* 1998/12/09 by T.Soneoka */

#if (0) /* 1998/12/04 by T.Soneoka */
**	/* 
**	** １－２相対策
**	** ＴＸモータ２００／１－２相で１ステップ分進めます（相を一定にする為）
**	** 1998/12/03 by T.Soneoka
**	*/
**	StepsTMSEL_1_2 = 0;
**	TxMotor200_1_2_1StepStart();
#endif

	/*
	** 原稿蓄積にて、１ページ読み取り完了する前に、原稿排出完了する仕様変更
	**  1999/02/24 by T.Soneoka
	*/
	Ds2ToPushStampSteps 	= FROM_DS2_TO_STAMP;
	SYS_ForcedMemoryOverMsg = 0;


	/*
	** 京セラＴＰＨ対応
	** 電源Ｏｎ直後に行います
	** 1999/03/15 追加 by T.Soneoka
	*/
	HeadMaker = HEAD_ROHM;
	if (ThermalHeadMaker()) {
		HeadMaker = HEAD_KYOCERA;
	}

}



void InitializeDocument(void)
{
	ScannerMode = SCANNER_NEUTRAL_MODE;
	LampOff();					/* ランプ消灯 */
	StopTxMotor();					/* モーター停止 */
#if (0) /* 1998/12/5 by T.Soneoka */
**	StopExciteTxMotor();			/* 送信モータ非励磁 */
#endif
	DeleteDocObj(&CurrentPage);		/* Document Object 削除 */
	DeleteDocObj(&NextPage);
}
