/* copy 1996/12/26 */
/*	ＦＢＳ関連のファイル
**		ミラー移動タスク、FBS原稿サイズ自動検出
**		1996/06/25 s.takeuchi
*/

#include	"\src\atlanta\define\product.h"
/* PRO_FBS == DISABLE でもコンパイルを通すためこの位置に置く */
#include	"\src\atlanta\define\message.h"

#if (PRO_FBS == ENABLE)	/* FBS関連(ファイルまるごと)  1996/07/26 s.takeuchi */

#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\sysscan.h"
#include	"\src\atlanta\define\scn_def.h"
#include	"\src\atlanta\define\scn_io.h"
#include	"\src\atlanta\define\idp_def.h"
#include	"\src\atlanta\define\idp301.h"

#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\define\mnt_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\idp_pro.h"
#include	"\src\atlanta\define\scn_pro.h"
#include	"\src\atlanta\define\mntsw_c.h"

#include	"\src\atlanta\ext_v\rom_tbl.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\scn_data.h"
#include	"\src\atlanta\ext_v\scn_tbl.h"

#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\define\def_evtn.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include	"\src\atlanta\ext_v\sys_port.h"

#include	"\src\atlanta\define\mntsw_j.h"	/* ミラーキャリッジ移動速度テスト T.Nose */
#include	"\src\atlanta\ext_v\bkupram.h"	/* ミラーキャリッジ移動速度テスト T.Nose */
#include	"\src\atlanta\define\mntsw_c.h"	/* ミラーキャリッジ待機位置切替え可能仕様 */

/*************************************************************************
	module		:[ミラー移動タスク]
	function	:[
		1.	ミラーキャリッジを指定された位置へ移動する
		2.	結果をMAN_Taskにsnd_msgする
		*.	エラーの場合のSubMessage1はエラーコード
	]
	return		:[]
	common		:[]
	condition	:[
		ミラーの動作はSCN_MirrorTaskControlで指定する
		待機位置へ/ADF読取り位置へ/FBS待機位置へ
		(scn_def.h参照)
	]
	comment		:[
		メインタスクから生成/削除する
		SubMessage1 (エラーの場合のみセット)
			MIRROR_MOVE_ERROR		1	エラーで終了
			MIRROR_MOVE_LAMP_ERROR	2	ランプ異常で終了
	]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/06/25]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_MirrorMoveTask( void )
{
	MESSAGE_t			tx_message = {0};	/* 送信用メッセージ */
	MESSAGE_t			*rx_message;		/* 受信用メッセージのポインタ */
	UBYTE	result;				/* 関数の結果記憶用 */

	/** 指定された動作をする */
	switch (SCN_MirrorTaskControl) {
	case	MIRROR_TASK_INITIALIZE:		/* 電源On時の初期化 */
		SCN_DocumentStatus = SCN_DOC_NO_DOCUMENT;
		SCN_Init();
		result = MirrorMoveToReady( FALSE );	/* 加速なし(低速)で待機位置へ */
		break;
	case	MIRROR_TASK_TO_READY:		/* 読み取り後の初期化 */
	case	MIRROR_TASK_TO_FBS_READY:	/* FBS読取り待機位置への初期化 1997/08/11 T.Nose */
		SCN_DocumentStatus = SCN_DOC_NO_DOCUMENT;
		SCN_Init();
		LampOff();
		result = MirrorMoveToReady( TRUE );		/* 加速あり(高速)で待機位置へ */
		break;
	case	MIRROR_TASK_TO_ADF:			/* ADF読取り位置へ */
		result = MirrorMoveToADF();
		break;
	case	MIRROR_TASK_TO_FBS:			/* FBS待機位置(HS上)へ */
		/*
		**	D71サブASSY検査用(FBS)
		*/
		if (HS()) {
			SCN_MirrorCarriageStatus = MIRROR_HS_ON;
		}
		else {
			SCN_MirrorCarriageStatus = MIRROR_READY;
		}

		result = MirrorMoveToFBS();
		break;
	case	MIRROR_TASK_FCOT_READY:		/* FCOTコピー用待機位置(HS上)へ */
		result = MirrorMoveToFBS();
		break;
	case	MIRROR_TASK_TRANSPORT:		/* 輸送用の固定位置へ */
		result = MirrorMoveFromHS(1956);	/* HS ～ 127mm */
		break;
	case	MIRROR_TASK_CCD_ADJUST:		/* CCD調整位置へ */
		/*
		**	D71サブASSY検査用(FBS)
		*/
		SCN_DocumentStatus = SCN_DOC_NO_DOCUMENT;
		SCN_Init();
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
		PC_24V_On();
#endif
		LampOn();
		result = MirrorMoveToADF();
/*		result = MirrorMoveFromHS(3457);	@* HS ～ 217 + 7.5mm 1998/02/20 大藪さん */
		result = MirrorMoveFromHS(3520);
		LampOff();
		wai_tsk( 0xFFFF );					/* 動作終了 */
		break;
	case	MIRROR_TASK_FBS_END_TO_ADF:	/* FBS読取り終了位置からADF読み取り位置へ */
		LampOff();
		result = MirrorMoveFBSEndToADF();
		break;
	case	MIRROR_TASK_TO_ADF_READY:	/* ADF読取り待機位置への初期化 */
		SCN_DocumentStatus = SCN_DOC_DS1_ON;
		SCN_Init();
		result = MirrorMoveToADF();
		break;
	}

	/* 動作結果をメインタスクに通知して、削除待ち
	** エラーの場合はSubMassage1に結果を入れる
	*/
	tx_message.Item = FROM_SCN_MIRROR_MOVE_TASK;
	if (result == MIRROR_MOVE_OK) {
		tx_message.Message = MSG_MIRROR_MOVE_OK;
	}
	else {
		tx_message.Message = MSG_MIRROR_MOVE_ERROR;
		tx_message.SubMessage1 = result;
	}
	snd_msg( mbxno.MAN_Task, &tx_message );
	rcv_msg( mbxno.SCN_MirrorMoveTask, &rx_message );
	wai_tsk( 0xFFFF );
}


/*************************************************************************
	module		:[ミラーを待機位置へ移動]
	function	:[
		1.	スキャナモーターをFBS側に切替える
		2.	ミラーをホームセンサ上へ指定スピードで移動する
		3.	モーターの起動を行う
		4.	モーターの停止等の制御は割込みで行う
		5.	割込みからの移動の終了/エラーをイベントで待つ
	]
	return		:[
		MIRROR_MOVE_OK			0	正常終了
		MIRROR_MOVE_ERROR		1	エラーで終了
	]
	common		:[]
	condition	:[]
	comment		:[
		引数	加速指定(加速する:TRUE/一定速:FALSE)
	]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/06/25]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	MirrorMoveToReady(
	UBYTE	is_speed_up)	/* モーター加速指定 */
{
	/**	状態を初期化 */
	SCN_MirrorMoveStatus = MIRROR_MOVE_OK;
	SCN_WatchEndSensorStatus = WATCH_ES_DISABLE;

	/** ミラーが既に待機位置(移動先)にあるなら、何もしない */
	if (SCN_MirrorCarriageStatus == MIRROR_READY) {
		return (SCN_MirrorMoveStatus);
	}

	/** スキャナモーターをFBS側に切替える */
	SCN_SetMotorDrive( SCN_FBS );

	/** ホームセンサ上にミラーキャリッジがなければ、ホームセンサへ移動する */
	if (!HS()) {
		SCN_MirrorCarriageStatus = MIRROR_MOVE_TO_HS;
		SCN_MirrorMotorPulseCount = 0;			/* ミラー用のパルスカウンタを０クリア */
		SCN_IsMirrorMoveEnd = FALSE;
		SCN_SetHS_ON_Int( SCN_ENABLE );			/* ホームセンサON割り込み許可 */
		SCN_SetHS_OFF_Int( SCN_DISABLE );		/* ホームセンサOFF割り込み禁止 */

		SCN_SetMotorClockwise( SCN_ENABLE );	/* モーター正転 */
		SCN_StartMirror( is_speed_up );			/* 加速/一定速 でミラー起動 */

		/**	ミラー移動の終了を待つ */
		CMN_DisableInterrupt();
		if (!SCN_IsMirrorMoveEnd) {
			wai_evt( EVT_MIRROR_MOVE_END );
		}
		CMN_EnableInterrupt();

		/** スキャナモータの回転方向を変えるために待つ */
		wai_tsk( SCN_MotorChangeInterval );

		if (SCN_MirrorReadyPosition == READY_POSITION_ADF) {
			return(MirrorMoveToADF());
		}
		else {
			return(SCN_MirrorMoveStatus);
		}
	}
	else {
		SCN_MirrorCarriageStatus = MIRROR_HS_ON;
		if (SCN_MirrorReadyPosition == READY_POSITION_ADF) {
			return(MirrorMoveToADF());
		}
		else {
			return(SCN_MirrorMoveStatus);
		}
	}
}


/*************************************************************************
	module		:[ミラーをADF読取り位置へ移動]
	function	:[
		1.	スキャナモーターをFBS側に切替える
		2.	ADF読取り位置にミラーを一定速で移動する
		3.	モーターの起動を行う
		4.	モーターの停止等の制御は割込みで行う
		5.	割込みからの移動の終了/エラーをイベントで待つ
	]
	return		:[
		MIRROR_MOVE_OK			0	正常終了
		MIRROR_MOVE_ERROR		1	エラーで終了
		MIRROR_MOVE_LAMP_ERROR	2	ランプ異常で終了
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/06/25]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	MirrorMoveToADF( void )
{
	/**	状態を初期化 */
	SCN_MirrorMoveStatus = MIRROR_MOVE_OK;
	SCN_WatchEndSensorStatus = WATCH_ES_DISABLE;

	/** ミラーが既にADF読み取り位置(移動先)にあるなら、何もしない */
	if (SCN_MirrorCarriageStatus == MIRROR_ADF_READY) {
		SYS_IsMirrorScanReady = TRUE;
		return (SCN_MirrorMoveStatus);
	}

	SYS_IsMirrorScanReady = FALSE;

	/** スキャナモーターをFBS側に切替える (ミラーを動かすため) */
	SCN_SetMotorDrive( SCN_FBS );

	/** ミラーキャリッジを「ADF読取り位置への移動」にする */
	SCN_MirrorCarriageStatus = MIRROR_MOVE_TO_ADF;

	/** ミラー用のパルスカウンタを０クリア */
	SCN_MirrorMotorPulseCount = 0;

	/** ES～ADFステップ数をセット */
	SCN_StepFromES_Off = (SYB_MachineParameter[11] + CHK_UNI_ADF_AdjustStep()) * 10;

	/**	ホームセンサON割込み/OFF割込み共に禁止する
	**	エンドセンサのONを監視する
	**	往動方向、スルーアップでモーター起動
	*/
	SCN_IsMirrorMoveEnd = FALSE;
	SCN_SetHS_ON_Int( SCN_DISABLE );
	SCN_SetHS_OFF_Int( SCN_DISABLE );
	SCN_SetScanStartInt( SCN_DISABLE );
	SCN_SetScanEndInt( SCN_DISABLE );
	SCN_WatchEndSensorStatus = WATCH_ES_ON;

	SCN_SetMotorClockwise( SCN_DISABLE );	/* モーター逆転 */
	SCN_StartMirror( TRUE );

	/**	ミラー移動の終了を待つ */
	CMN_DisableInterrupt();
	if (!SCN_IsMirrorMoveEnd) {
		wai_evt( EVT_MIRROR_MOVE_END );
	}
	CMN_EnableInterrupt();

	/** スキャナモータの回転方向を変えるために待つ */
	wai_tsk( SCN_MotorChangeInterval );

	return (SCN_MirrorMoveStatus);
}


/*************************************************************************
	module		:[ミラーをFBS待機位置へ移動]
	function	:[
		1.	スキャナモーターをFBS側に切替える
		2.	FBS読取り待機位置(HS上)にミラーを高速で移動する
		3.	モーターの起動を行う
		4.	モーターの停止等の制御は割込みで行う
		5.	割込みからの移動の終了/エラーをイベントで待つ
	]
	return		:[
		MIRROR_MOVE_OK			0	正常終了
		MIRROR_MOVE_ERROR		1	エラーで終了
	]
	common		:[]
	condition	:[]
	comment		:[
		FBS読取り用のランプチェックを移動中に行うために
		ここでランプを点灯しピーク値検出回路を動作させる
		所定位置に来た時のモーター割り込み内でDIPPの
		光源異常レジスタを読み込む
	]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/06/25]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	MirrorMoveToFBS( void )
{
	/**	状態を初期化 */
	SCN_MirrorMoveStatus = MIRROR_MOVE_OK;

	SCN_WatchEndSensorStatus = WATCH_ES_ON;

	/* ミラーが既にFBS読み取り待機位置(移動先)にあるなら、何もしない */
	/* 静電気などで途中で止まった時のためにホームセンサを直接見る  1997/08/21 s.takeuchi */
	if ((SCN_MirrorCarriageStatus == MIRROR_HS_ON)
	 && HS()) {		/* 1997/08/21 s.takeuchi */
		SYS_IsMirrorScanReady = TRUE;
		return (SCN_MirrorMoveStatus);
	}

	SYS_IsMirrorScanReady = FALSE;

	/** スキャナモーターをFBS側に切替える */
	SCN_SetMotorDrive( SCN_FBS );

	SCN_MirrorCarriageStatus = MIRROR_MOVE_TO_HS;
	SCN_MirrorMotorPulseCount = 0;			/* ミラー用のパルスカウンタを０クリア */
	SCN_IsMirrorMoveEnd = FALSE;
	SCN_SetHS_ON_Int( SCN_ENABLE );			/* ホームセンサON割り込み許可 */
	SCN_SetHS_OFF_Int( SCN_DISABLE );		/* ホームセンサOFF割り込み禁止 */
	SCN_SetMotorClockwise( SCN_ENABLE );	/* モーター正転 */

	/* 大分のＦＢＳ ＡＳＳＹ検査でＨＳ側でミラーがぶつかるため低速に変更
	** T.Nose 1998/02/20
	*/
	SCN_StartMirror( FALSE );

	/**	ミラー移動の終了を待つ */
	CMN_DisableInterrupt();
	if (!SCN_IsMirrorMoveEnd) {
		wai_evt( EVT_MIRROR_MOVE_END );
	}
	CMN_EnableInterrupt();

	/** スキャナモータの回転方向を変えるために待つ */
	wai_tsk( SCN_MotorChangeInterval );

	return (SCN_MirrorMoveStatus);
}


/*************************************************************************
	module		:[ミラーを輸送用の固定位置へ移動]
	function	:[
		1.	スキャナモーターをFBS側に切替える
		2.	ミラーを輸送用の固定位置に高速で移動する
		3.	モーターの起動を行う
		4.	モーターの停止等の制御は割込みで行う
		5.	割込みからの移動の終了/エラーをイベントで待つ
	]
	return		:[
		MIRROR_MOVE_OK			0	正常終了
		MIRROR_MOVE_ERROR		1	エラーで終了
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/12/10]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	MirrorMoveFromHS( UWORD step )
{
	/**	状態を初期化 */
	SCN_MirrorMoveStatus = MIRROR_MOVE_OK;
	SCN_WatchEndSensorStatus = WATCH_ES_DISABLE;
	SYS_IsMirrorScanReady = FALSE;

	/** スキャナモーターをFBS側に切替える (ミラーを動かすため) */
	SCN_SetMotorDrive( SCN_FBS );

	if (!HS()) {
		SCN_MirrorCarriageStatus = MIRROR_MOVE_TO_HS;	/* ミラーキャリッジを「ＨＳ上へ移動中」にする */
		SCN_MirrorMotorPulseCount = 0;		/* ミラー用のパルスカウンタを０クリア */
		SCN_IsMirrorMoveEnd = FALSE;
		SCN_SetHS_ON_Int( SCN_ENABLE );		/* ホームセンサON割り込み許可 */
		SCN_SetHS_OFF_Int( SCN_DISABLE );	/* ホームセンサOFF割り込み禁止 */
		SCN_SetMotorClockwise( SCN_ENABLE );	/* モーター正転 */

		/* 大分のＦＢＳ ＡＳＳＹ検査でＨＳ側でミラーがぶつかるため低速に変更
		** T.Nose 1998/02/20
		*/
		SCN_StartMirror( FALSE );				/* 高速でミラー起動 */

		/**	ミラー移動の終了を待つ */
		CMN_DisableInterrupt();
		if (!SCN_IsMirrorMoveEnd) {
			wai_evt( EVT_MIRROR_MOVE_END );
		}
		CMN_EnableInterrupt();

		/** スキャナモータの回転方向を変えるために待つ */
		wai_tsk( SCN_MotorChangeInterval );
	}
	else {
		SCN_MirrorCarriageStatus = MIRROR_HS_ON;
	}

	/**	ホームセンサから待機位置へ移動する */
	if (SCN_MirrorMoveStatus == MIRROR_MOVE_OK) {
		/** ミラーキャリッジを「ホームセンサからN step移動中」にする */
		SCN_MirrorCarriageStatus = MIRROR_MOVE_TO_N_STEP;

		SCN_StepFromHS_Off = step;		/** ホームセンサOFFから停止位置のステップをセット */
		SCN_N_StepRemain = step;		/* 輸送モード停止位置がずれるため  1997/06/05 */

		SCN_MirrorMotorPulseCount = 0;			/* ミラー用のパルスカウンタを０クリア */
		SCN_IsMirrorMoveEnd = FALSE;
		SCN_SetHS_ON_Int( SCN_DISABLE );		/* ホームセンサON割り込み禁止 */
		SCN_SetHS_OFF_Int( SCN_ENABLE );		/* ホームセンサOFF割り込み許可 */

		SCN_SetMotorClockwise( SCN_DISABLE );	/* モーター逆転 */
		SCN_StartMirror( FALSE );				/* 一定速でミラー起動 */

		/**	ミラー移動の終了を待つ */
		CMN_DisableInterrupt();
		if (!SCN_IsMirrorMoveEnd) {
			wai_evt( EVT_MIRROR_MOVE_END );
		}
		CMN_EnableInterrupt();

		/** スキャナモータの回転方向を変えるために待つ */
		wai_tsk( SCN_MotorChangeInterval );
	}

	return (SCN_MirrorMoveStatus);
}

/*************************************************************************
	module		:[ミラーをＦＢＳ読取り終了位置からＡＤＦ読み取り位置へ移動する]
	function	:[
		1.	スキャナモーターをFBS側に切替える
		2.	ミラーをＡＤＦ読取り位置に高速で移動する
		3.	モーターの起動を行う
		4.	モーターの停止等の制御は割込みで行う
		5.	割込みからの移動の終了/エラーをイベントで待つ
	]
	return		:[
		MIRROR_MOVE_OK			0	正常終了
		MIRROR_MOVE_ERROR		1	エラーで終了
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/05/29]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE MirrorMoveFBSEndToADF(void)
{
	/**	状態を初期化 */
	SCN_MirrorMoveStatus = MIRROR_MOVE_OK;
	SCN_WatchEndSensorStatus = WATCH_ES_DISABLE;
	SYS_IsMirrorScanReady = FALSE;

	/* ミラーキャリッジが既にＡＤＦ待機位置にあれば何もしない */
	if (SCN_MirrorCarriageStatus == MIRROR_ADF_READY) {
		SYS_IsMirrorScanReady = TRUE;
		return (SCN_MirrorMoveStatus);
	}

	/** スキャナモーターをFBS側に切替える (ミラーを動かすため) */
	SCN_SetMotorDrive( SCN_FBS );

	/** ミラーキャリッジを「FBS読取り終了位置からADF読み取り位置へ移動中」にする */
	SCN_MirrorCarriageStatus = MIRROR_MOVE_FBS_END_TO_ADF;

	/** ミラー用のパルスカウンタを０クリア */
	SCN_MirrorMotorPulseCount = 0;

	/** ES～ADFステップ数をセット */
	SCN_StepFromES_Off = (SYB_MachineParameter[11] + CHK_UNI_ADF_AdjustStep()) * 10;

	/**	ホームセンサON割込み/OFF割込み共に禁止する
	**	エンドセンサのOFFを監視する
	**	往動方向、一定速でモーター起動
	*/
	SCN_IsMirrorMoveEnd = FALSE;
	SCN_SetHS_ON_Int( SCN_DISABLE );
	SCN_SetHS_OFF_Int( SCN_DISABLE );
	SCN_SetScanStartInt( SCN_DISABLE );
	SCN_SetScanEndInt( SCN_DISABLE );
	SCN_WatchEndSensorStatus = WATCH_ES_OFF;

	SCN_SetMotorClockwise( SCN_DISABLE );	/* モーター逆転 */
	SCN_StartMirror( FALSE );

	/**	ミラー移動の終了を待つ */
	CMN_DisableInterrupt();
	if (!SCN_IsMirrorMoveEnd) {
		wai_evt( EVT_MIRROR_MOVE_END );
	}
	CMN_EnableInterrupt();

	/** スキャナモータの回転方向を変えるために待つ */
	wai_tsk( SCN_MotorChangeInterval );

	return (SCN_MirrorMoveStatus);
}


/*************************************************************************
	module		:[モーター駆動経路の切替え]
	function	:[
		1.	スイッチングモーター(SWM)で駆動経路を切替える
		.	(指定方向に回す→ブレーキ→フリー)
		2.	駆動経路は引数(SCN_ADF/SCN_FBS)で指定する (sysscan.h参照)
		3.	スキャナG/AのDS2割込みの入力を切替える (ADF:DS2/FBS:HS)
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1996/07/03]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_SetMotorDrive(
	UBYTE	mode)
{
	/* 今の状態と同じなら、モーターの切替え処理はせずに終了
	** 現在の状態は SYS_ETC_PortStatus で確認
	** T.Nose 1997/10/27
	*//* 追加 1997/12/11 T.Nose */
	if (((SYS_ETC_PortStatus & IO_BIT_XADF_FBS) && (mode == SCN_FBS))
	 || (!(SYS_ETC_PortStatus & IO_BIT_XADF_FBS) && (mode == SCN_ADF))) {
		if (SCN_MotorDriveMode != mode) {
			SCN_MotorDriveMode = mode;
		}
		return;
	}

#if (0)
	/** 今の状態と同じなら、モーターの切替え処理はせずに終了 */
	if (mode == SCN_MotorDriveMode) {
		return;
	}
#endif

	if (mode == SCN_ADF) {
		CMN_SetTxMotorADF(); /* ＡＤＦモーター・ＤＳ２割込み */
	}
	else {	/* SCN_FBS */
		CMN_SetTxMotorFBS(); /* ＦＢＳモーター・ＨＳ割込み */
	}
	SCN_MotorDriveMode = mode;		/** 今の状態を記憶する */
}


/*************************************************************************
	module		:[FBSのミラー移動スタート]
	function	:[
		1.	ミラーの移動を開始する
		*	読み取りを除くミラーキャリッジの移動
	]
	return		:[]
	common		:[]
	condition	:[
		移動方向(モーターの回転方向)は予め指定しておく
	]
	comment		:[
		引数	加速指定(加速する:TRUE/一定速:FALSE)
	]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/06/24]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_StartMirror(
	UBYTE	is_speed_up)	/* モーター加速指定 */
{
	/* SCN_VerticalMode = SCN_MOVE_MIRROR;	1996/10/18 */

	if (is_speed_up) {
		SCN_VerticalMode = SCN_MOVE_MIRROR;					/** ミラー高速移動用 */
	}
	else {
		SCN_VerticalMode = SCN_MOVE_MIRROR_SLOW;			/** ミラー低速(一定速)移動用 */
	}
	SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode];	/** モーター制御用テーブルのポインターをセット */
	SCN_MotorTablePoint = SCN_MotorTable->InitialSpeed;		/** 初期速度テーブルをセット */
	SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;				/** スルーアップ指定 */

	SCN_SetScanDMA( SCN_DISABLE );				/** スキャン用ＤＭＡ禁止 */

	SCN_SetMotorSpeed(); 						/** モーターの速度設定(MTPC0,1)、速度変更間隔設定(MTP0) */
	SCN_SetMotor( SCN_DISABLE );				/** モーター・ディスエーブル */
	SCN_LatchMotorSpeedAndInterval(); 			/** モーター速度変更間隔、速度初期ラッチ */
	SCN_SetMotorSpeedIntervalInt( SCN_ENABLE );	/** モーター速度変更間隔割り込み許可(INTMTEN-MTCNT) */
	SCN_SetMotorPulse( SCN_ENABLE ); 			/** モーター励磁ＯＮ(MTCLR-MTCNT) */

	/*	wai_evt(EVT_MIRROR_MOVE_END)のタスクをタイムアウトで動かすため
	**	TimerInterruptでカウンタを減算し、0になればdet_evtする
	**		1997/03/07 s.takeuchi
	*/
	SCN_MirrorStopTimeoutCount = 6000;	/** 60 sec */

	SCN_SetMotor( SCN_ENABLE );					/** モータースタート */
}


/*************************************************************************
	module		:[ホームセンサＯＦＦ割込みの許可/禁止]
	function	:[
		1.	ＦＢＳのホームセンサＯＦＦ割込みの許可/禁止を設定する
		2.	ホームセンサのG/Aへの入力はDS2とパラのため、
		.	実際はDS2ON割込みの設定関数をCALLする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/06/20]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_SetHS_OFF_Int(
	UBYTE	enable_flag)
{
	SCN_SetDS2_ON_Int( enable_flag );
}


/*************************************************************************
	module		:[ホームセンサＯＮ割込みの許可/禁止]
	function	:[
		1.	ＦＢＳのホームセンサＯＮ割込みの許可/禁止を設定する
		2.	ホームセンサのG/Aへの入力はDS2とパラのため、
		.	実際はDS2OFF割込みの設定関数をCALLする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/06/20]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_SetHS_ON_Int(
	UBYTE	enable_flag)
{
	SCN_SetDS2_OFF_Int( enable_flag );
}


/*************************************************************************
	module		:[エンドセンサ監視]
	function	:[
		1.	エンドセンサ監視状態を見る
		2.	監視中の状態変化を検出すると、パルスカウンタをクリアする
		3.	ミラーキャリッジの状態を変更する
		**	ADF読取り位置への移動中と初期化中以外の時にエンドセンサがOnすると
		**	ミラーキャリッジのエラーとする
	]
	return		:[]
	common		:[]
	condition	:[
		10ms割込みからコールされる
	]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/07/08]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_CheckEndSensor( void )
{
	UBYTE	debug = FALSE;	/* 1996/10/17 */

	switch (SCN_WatchEndSensorStatus) {
	case	WATCH_ES_ON:
		/*	ADF読取り位置へ移動中にエンドセンサがOnすると、
		**		G/Aの割込み間隔を初期ラッチで初期化して、モーターパルスカウンタを０クリアする
		**		モーター減速指示し、エンドセンサのOff待ちにする
		**	輸送用の固定位置への移動もこの処理  1996/12/10
		*/
		if ((SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_ADF)
		 && ES()) {
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
			SCN_AdjustMotorSpeed();		/* 1996/10/17 */
			SCN_LatchMotorSpeedAndInterval();
			SCN_MirrorMotorPulseCount = 0;
			SCN_WatchEndSensorStatus = WATCH_ES_OFF;

			inp( INTST1_PORT );		/* モーター割込み要因をクリアする  1996/10/17 */
		}
		/* FBS１ページ読取り完了後の空送り中にエンドセンサがＯＮすると、
		** ESからFBSシェーディング位置までのステップをG/Aにセットし、初期ラッチする
		** モーターパルスカウンタを０クリアする
		** エンドセンサＯＦＦを監視する（但し、ＥＳ ＯＦＦを検知したらエラー）
		*/
		else if ((SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_FBS_END) && ES()) {
			SCN_SetMotorIntStep( (UWORD)SYB_MaintenanceSwitch[MNT_SW_C7], SCN_MotorPointer->ExciteMethod );
			SCN_LatchMotorSpeedAndInterval();
			SCN_MirrorMotorPulseCount = 0;
			SCN_WatchEndSensorStatus = WATCH_ES_OFF;

			inp( INTST1_PORT );		/* モーター割込み要因をクリアする */
		}
		break;
	case	WATCH_ES_OFF:
		/*	ADF読取り位置へ移動中にエンドセンサがOffすると、
		**		ESからADF読み取り位置までのステップをG/Aにセットし、初期ラッチする
		**		モーターパルスカウンタを０クリアする
		**		モーター減速指示し、エンドセンサ監視を無効にする
		**	チャタリングを考慮して最終速度になってからOffを見る (通り過ぎないように)
		**	輸送用の固定位置への移動もこの処理  1996/12/10
		*/
		if ((SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_ADF)
		 && (SCN_MotorTablePoint == SCN_MotorPointer->LowSpeed)
		 && !ES()) {
			if (debug) {
				SCN_SetSoftCTSCAN( SCN_ENABLE );
			}

			SCN_WatchEndSensorStatus = WATCH_ES_DISABLE;
			SCN_SetMotorIntStep( SCN_StepFromES_Off, SCN_MotorPointer->ExciteMethod );
			SCN_LatchMotorSpeedAndInterval();
			SCN_MirrorMotorPulseCount = 0;

			inp( INTST1_PORT );		/* モーター割込み要因をクリアする  1996/10/17 */
		}
		/* FBS１ページ読取り完了後の空送り中にエンドセンサがＯＦＦすると、
		** ミラーキャリッジエラーとしてモーター減速指示する
		*/
		else if ((SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_FBS_END) && !ES()) {
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
			SCN_MirrorMoveStatus = MIRROR_MOVE_ERROR;
			SYB_MaintenanceSwitch[MNT_SW_C5] = 6;	/* エラーコードをセット */
		}
		/* ミラーキャリッジ待機位置切り替え可能仕様 */
		else if ((SCN_MirrorCarriageStatus == MIRROR_MOVE_FBS_END_TO_ADF) && !ES()) {
			/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN; */
			SCN_SetMotorIntStep( SCN_StepFromES_Off, SCN_MotorPointer->ExciteMethod );
			SCN_LatchMotorSpeedAndInterval();
			SCN_WatchEndSensorStatus = WATCH_ES_DISABLE;
			SCN_MirrorMotorPulseCount = 0;
		}
		break;
	default:	/* WATCH_ES_DISABLE */
		/*	エンドセンサの監視中でなくても、
		**	ミラーがHS上へ移動中以外の時でエンドセンサがOnすると、
		**	ミラーキャリッジエラーとしてモーター減速指示する
		*/
		if ((SCN_MirrorCarriageStatus != MIRROR_MOVE_TO_HS)
		&&	(SCN_MotorDriveMode == SCN_FBS)
		&&	ES()) {
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
			SCN_MirrorMoveStatus = MIRROR_MOVE_ERROR;
			/*	ミラーエラーの状況:
			**		FBS読取り時Txモーターが停止位置を超えた
			**		エンドセンサが死んでる
			*/
			SYB_MaintenanceSwitch[MNT_SW_C5] = 6;	/* エラーコードをセット */
			/* ICHOU CHK_SetMirrorCarriageErrorCode( 6 ); */
		}
		break;
	}
}


/*************************************************************************
	module		:[ＦＣＯＴ用ミラー待機位置移動判定]
	function	:[
	]
	return		:[
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[Dec.11.1996]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE SCN_CheckFCOT_Enable(void)
{
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY) ||
	    (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN)) {
		return(FALSE);
	}
	return(TRUE);
}

void SCN_WatchMotorInterrupt(void)
{
}

#endif	/* (PRO_FBS == ENABLE)  ファイルまるごと */
