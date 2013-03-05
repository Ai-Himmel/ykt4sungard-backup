/***********************************************************************
*               BY:  T.Nose
*             DATE:  1997/08/13
*        FILE NAME:  scn_drv.c
*      DESCRIPTION:	 スキャナー・モーター制御用モジュール
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:  scn_sub.c が大きくなったのでモーター制御用の
*                    モジュールをこちらに移します。
*      MODULE NAME:
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\scn_io.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mntsw_i.h"

void SCN_SaveCTSCANOFF_Address(void);
/** Module Header For CIM-E ********************************************
		module		:	[モーターの速度及び速度変更間隔の初期ラッチ]
		function	:	[]
  		return		:	[無し]
		common		:	[
						SCN_MTCNT_Status
						]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
     	reviewed	:	[94/6/6]
 		author		:	[川崎真史]
************************************************************************/
void SCN_LatchMotorSpeedAndInterval( void )
{
	/** モーター速度変更間隔初期セット(MTPCL-MTCNT)、モーター速度初期セット(MTPL-MTCNT) */
	SCN_MTCNT_Status |= (IO_BIT_MOTOR_INTERVAL_LATCH + IO_BIT_MOTOR_SPEED_LATCH);
	outp(MTCNT_PORT, SCN_MTCNT_Status);

	/** モーター速度変更間隔初期セット(MTPCL-MTCNT)、モーター速度初期セット(MTPL-MTCNT) */
	SCN_MTCNT_Status &= ~(IO_BIT_MOTOR_INTERVAL_LATCH + IO_BIT_MOTOR_SPEED_LATCH);
	outp(MTCNT_PORT, SCN_MTCNT_Status);

	/** モーター速度変更間隔初期セット(MTPCL-MTCNT)、モーター速度初期セット(MTPL-MTCNT) */
	SCN_MTCNT_Status |= (IO_BIT_MOTOR_INTERVAL_LATCH + IO_BIT_MOTOR_SPEED_LATCH);
	outp(MTCNT_PORT, SCN_MTCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[モーター電流パワーの設定]
		function	:	[
						引き数　SCN_CURRENT_POWER_100 : 100%
								SCN_CURRENT_POWER_60  :  60%
								SCN_CURRENT_POWER_20  :  20%
								SCN_CURRENT_POWER_0   :   0%
						]
  		return		:	[無し]
		common		:	[
						SCN_MTP1_Status
						]
		condition	:	[]
		comment		:	[
						電流制御　Ｄ５　　Ｄ６
									1		1		：１００％
									1		0		：　６０％
									0		1		：　２０％
									0		0		：　　０％
						]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
     	reviewed	:	[94/6/6]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetMotorCurrent( UBYTE power_level )
{
	/** 電流ビットをクリア（電流値０％） */
	SCN_MTP1_Status &= ~(IO_BIT_CURRENT_POWER_D5 + IO_BIT_CURRENT_POWER_D6);

	if (power_level == SCN_CURRENT_POWER_20) { /** 電流値２０％ */
		SCN_MTP1_Status |= IO_BIT_CURRENT_POWER_D6;
	}
	else if (power_level == SCN_CURRENT_POWER_60) { /** 電流値６０％ */
		SCN_MTP1_Status |= IO_BIT_CURRENT_POWER_D5;
	}
	else if (power_level == SCN_CURRENT_POWER_100) { /** 電流値１００％ */
		SCN_MTP1_Status |= (IO_BIT_CURRENT_POWER_D5 + IO_BIT_CURRENT_POWER_D6);
	}
	outp(MTP1_PORT, SCN_MTP1_Status); /** 電流値を出力 */
}

/** Module Header For CIM-E ********************************************
		module		:	[]
		function	:	[
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetLineStep( UBYTE number_of_lines)
{
	SCN_INTLNCN_Status = number_of_lines;

	outp(INTLNCN_PORT, SCN_INTLNCN_Status);	/** ライン割り込み間隔セット */

	SCN_MTCNT_Status |= IO_BIT_LINE_INT_COUNT_LATCH;	/* 割り込みライン数初期ラッチ	*/
	outp(MTCNT_PORT, SCN_MTCNT_Status);
	SCN_MTCNT_Status &= ~(IO_BIT_LINE_INT_COUNT_LATCH);
	outp(MTCNT_PORT, SCN_MTCNT_Status);
	SCN_MTCNT_Status |= IO_BIT_LINE_INT_COUNT_LATCH;
	outp(MTCNT_PORT, SCN_MTCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[原稿先端用ライン数の設定とラッチ]
		function	:	[]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[
			原稿先端検出割り込みは許可しない
			ICHOU用に引数型変更  1996/06/14 s.takeuchi
		]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetScanStartStep(UWORD	step)
{
	/* ICHOUのDS2-ONから読み取り位置までのステップ数
	** 設定値×１０が実際のステップ数として設定される
	** １ステップ=0.0649mm  (=1/15.4mm/l)
	** 設定値１～２５５で0.649mmから165.495mmまで可変
	*/
	SCN_SSTSTP_Status = (UWORD)(step * 10);	/** ＤＳ２と読み取りポイントのステップ数をセット */

	outp(SSTSTP0_PORT, (UBYTE)(SCN_SSTSTP_Status&0x00FF));		/** 読み取り先端　下位８ビット設定 */
	outp(SSTSTP1_PORT, (UBYTE)((SCN_SSTSTP_Status>>8)&0x001F));	/** 読み取り先端　上位５ビット設定 */

	/** 読み取り先端ステップ数初期ラッチ */
	SCN_SCCNT_Status |= IO_BIT_SCAN_START_LATCH;
	outp(SCCNT_PORT, SCN_SCCNT_Status);
	SCN_SCCNT_Status &= ~(IO_BIT_SCAN_START_LATCH);
	outp(SCCNT_PORT, SCN_SCCNT_Status);
	SCN_SCCNT_Status |= IO_BIT_SCAN_START_LATCH;
	outp(SCCNT_PORT, SCN_SCCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[原稿後端用ライン数の設定とラッチ]
		function	:	[]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[
			原稿後端検出割り込みは許可しない
			ICHOU用にステップ数を引数指定に変更  1996/06/14 s.takeuchi
		]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetScanEndStep(UWORD	step)	/* SCANENDのステップ */
{
	/* SCN_SENSTP_Status = step; */

	/* ICHOUのDS2-OFFから読み取り位置までのステップ数
	** 設定値×１０が実際のステップ数として設定される
	** １ステップ=0.0649mm  (=1/15.4mm/l)
	** 設定値１～２５５で0.649mmから165.495mmまで可変
	*/
	SCN_SENSTP_Status = (UWORD)(step * 10);


	outp(SENSTP0_PORT, (UBYTE)(SCN_SENSTP_Status&0x00FF));		/** 読み取り後端　下位８ビット設定 */
	outp(SENSTP1_PORT, (UBYTE)((SCN_SENSTP_Status>>8)&0x001F));	/** 読み取り後端　上位５ビット設定 */

	/** 読み取り後端ステップ数初期ラッチ */
	SCN_SCCNT_Status |= IO_BIT_SCAN_END_LATCH;
	outp(SCCNT_PORT, SCN_SCCNT_Status);
	SCN_SCCNT_Status &= ~(IO_BIT_SCAN_END_LATCH);
	outp(SCCNT_PORT, SCN_SCCNT_Status);
	SCN_SCCNT_Status |= IO_BIT_SCAN_END_LATCH;
	outp(SCCNT_PORT, SCN_SCCNT_Status);

}

/** Module Header For CIM-E ********************************************
		module		:	[ＤＳ２　ＯＮ割り込みの許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : ＤＳ２　ＯＮ割り込み許可
								SCN_DISABLE: ＤＳ２　ＯＮ割り込み禁止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetDS2_ON_Int( UBYTE enable_flag )
{
	if (enable_flag == SCN_ENABLE) {
		SCN_DS2INTR_Status |= IO_BIT_DS2_ON_INT_ENABLE; /** ＤＳ２　ＯＮ割り込み許可 */
		SCN_DS2INTR_Status |= IO_BIT_DS2_ON_ENABLE; /** ＤＳ２　ＯＮステータス許可 */
	}
	else {
		SCN_DS2INTR_Status &= ~(IO_BIT_DS2_ON_INT_ENABLE); /** ＤＳ２　ＯＮ割り込み禁止 */
		SCN_DS2INTR_Status &= ~(IO_BIT_DS2_ON_ENABLE); /** ＤＳ２　ＯＮステータス禁止 */
	}
	outp(DS2INTR_PORT, SCN_DS2INTR_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[ＤＳ２　ＯＦＦ割り込みの許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : ＤＳ２　ＯＦＦ割り込み許可
								SCN_DISABLE: ＤＳ２　ＯＦＦ割り込み禁止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetDS2_OFF_Int( UBYTE enable_flag )
{
	if (enable_flag == SCN_ENABLE) {
		SCN_DS2INTR_Status |= IO_BIT_DS2_OFF_INT_ENABLE; /** ＤＳ２　ＯＦＦ割り込み許可 */
		SCN_DS2INTR_Status |= IO_BIT_DS2_OFF_ENABLE; /** ＤＳ２　ＯＦＦステータス許可 */
	}
	else {
		SCN_DS2INTR_Status &= ~(IO_BIT_DS2_OFF_INT_ENABLE); /** ＤＳ２　ＯＦＦ割り込み禁止 */
		SCN_DS2INTR_Status &= ~(IO_BIT_DS2_OFF_ENABLE); /** ＤＳ２　ＯＦＦステータス禁止 */
	}
	outp(DS2INTR_PORT, SCN_DS2INTR_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[原稿先端割り込みの許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : 原稿先端割り込み許可
								SCN_DISABLE: 原稿先端割り込み禁止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetScanStartInt( UBYTE enable_flag )
{
	if (enable_flag == SCN_ENABLE) {
		SCN_DS2INTR_Status |= IO_BIT_SCAN_START_INT_ENABLE; /** 読み取り先端割り込み許可 */
	}
	else {
		SCN_DS2INTR_Status &= ~(IO_BIT_SCAN_START_INT_ENABLE); /** 読み取り先端割り込み禁止 */
	}
	outp(DS2INTR_PORT, SCN_DS2INTR_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[原稿後端割り込みの許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : 原稿後端割り込み許可
								SCN_DISABLE: 原稿後端割り込み禁止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetScanEndInt( UBYTE enable_flag )
{
	if (enable_flag == SCN_ENABLE) {
		SCN_DS2INTR_Status |= IO_BIT_SCAN_END_INT_ENABLE; /** 読み取り後端割り込み許可 */
	}
	else {
		SCN_DS2INTR_Status &= ~(IO_BIT_SCAN_END_INT_ENABLE); /** 読み取り後端割り込み禁止 */
	}
	outp(DS2INTR_PORT, SCN_DS2INTR_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[モーター速度変更間隔割り込みの許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : 速度変更間隔割り込み許可
								SCN_DISABLE: 速度変更間隔割り込み禁止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetMotorSpeedIntervalInt( UBYTE enable_flag)
{
	if (enable_flag == SCN_ENABLE) {
		SCN_MTCNT_Status |= IO_BIT_MOTOR_INT_ENABLE; /** モーター速度変更間隔割り込み許可 	INTMTEN-MTCNT */
	}
	else {
		SCN_MTCNT_Status &= ~(IO_BIT_MOTOR_INT_ENABLE); /** モーター速度変更間隔割り込み禁止 	INTMTEN-MTCNT */
	}
	outp(MTCNT_PORT, SCN_MTCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[ライン割り込みの許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : ライン割り込み許可
								SCN_DISABLE: ライン割り込み禁止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetLineInt( UBYTE enable_flag )
{
	if (enable_flag == SCN_ENABLE) {
		SCN_SCCNT_Status |= IO_BIT_LINE_INT_ENABLE; /** ライン割り込み許可 */
	}
	else {
		SCN_SCCNT_Status &= ~(IO_BIT_LINE_INT_ENABLE); /** ライン割り込み禁止 */
	}
	outp(SCCNT_PORT, SCN_SCCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[プリンター用の１ＫＨｚ周波数設定]
		function	:	[]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_GeneratePrinter1KHz(void)
{
	/********************************************************************
	*	Ｄ４からＤ７ビットでプリンター用の周波数を設定する。			*
	*	発生周波数＝２３．４３２５ＫＨｚ／（２＊（設定値＋１））		*
	*	例）２３．４３２５／（２＊（１０＋１））＝１．０６５ＫＨｚ		*
	*********************************************************************/
	SCN_BUZZ_1K_Status &= 0x0F;
	SCN_BUZZ_1K_Status |= 0xA0;/** １ＫＨｚセット */
	outp(BUZZ_1K_PORT, SCN_BUZZ_1K_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[ブザー周波数の設定]
		function	:	[]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetBuzzerFrequency( UBYTE frequency_no )
{
	/********************************************************************
	*	Ｄ０からＤ３ビットでブザー周波数を設定する。					*
	*	発生周波数＝２３．４３２５ＫＨｚ／（２＊（設定値＋１））		*
	*	例）２３．４３２５／（２＊（１０＋１））＝１．０６５ＫＨｚ		*
	*********************************************************************/
	SCN_BUZZ_1K_Status &= 0xF0;
	SCN_BUZZ_1K_Status |= frequency_no;/** ブザー周波数セット */
	outp(BUZZ_1K_PORT, SCN_BUZZ_1K_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[読み取りライン数カウンターのクリア及び停止]
		function	:	[]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_ClearMotorPulseCounter( void )
{
	SCN_MTCNT_Status &= ~(IO_BIT_XMOTOR_PULSE_CTR_CLEAR); /** 読み取りライン数カウンタをクリアし、停止する。 */
	outp(MTCNT_PORT, SCN_MTCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[読み取りライン数カウンターの起動]
		function	:	[]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_StartMotorPulseCounter( void )
{
	SCN_MTCNT_Status |= IO_BIT_XMOTOR_PULSE_CTR_CLEAR; /** 読み取りライン数カウンタを起動する。 */
	outp(MTCNT_PORT, SCN_MTCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[読み取りライン数カウンターの読み込み]
		function	:	[]
  		return		:	[(UWORD)読み取りライン数]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
UWORD SCN_ReadMotorPulseCounter( void )
{
	UWORD counter = 0;

	counter = inp(MTCNT1_PORT); /** 読み取りライン数上位８ビット読み込み */
	counter <<= 8; /** ８ビット左へシフト */
	counter &= 0xFF00; /** 下位８ビットをクリア */
	counter |= inp(MTCNT0_PORT); /** 読み取りライン数下位８ビット読み込み */

	return( counter );
}

/** Module Header For CIM-E ********************************************
		module		:	[モーター励磁ＯＮ／ＯＦＦ]
		function	:	[
						引き数　SCN_ENABLE : モーター励磁　ＯＮ
								SCN_DISABLE: モーター励磁　ＯＦＦ
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetMotorPulse( UBYTE enable_flag)
{
	/** モーター励磁OFFされないようにクリアする */
	SCN_MotorCurrentStopCounter = 0;

	if (enable_flag == SCN_ENABLE) {
		SCN_MTCNT_Status |= IO_BIT_MOTOR_PULSE_CLEAR; /**  モーター励磁ON (モーター・パルスON) */
	}
	else {
		SCN_MTCNT_Status &= ~(IO_BIT_MOTOR_PULSE_CLEAR); /**  モーター励磁OFF (モーター・パルスOFF) */
	}
	outp(MTCNT_PORT, SCN_MTCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[モーター回転方向設定]
		function	:	[
						引き数　SCN_ENABLE : 原稿繰り込み方向
								SCN_DISABLE: 原稿繰り込みと反対方向
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetMotorClockwise( UBYTE enable_flag )
{
#if (PRO_TX_MOTOR_REVERSE == ENABLE)	/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	if (enable_flag == SCN_ENABLE) {
		SCN_MTCNT_Status &= ~(IO_BIT_MOTOR_CLOCKWISE); /** 原稿繰り込み方向に設定 */
		SCN_IsMotorClockwise = TRUE;	/** 回転方向(正転)を記憶 */
	}
	else {
		SCN_MTCNT_Status |= IO_BIT_MOTOR_CLOCKWISE; /** 原稿繰り込みと反対の方向に設定 */
		SCN_IsMotorClockwise = FALSE;	/** 回転方向(逆転)を記憶 */
	}
#else	/** ＡＮＺＵ＿Ｌタイプなど */
	if (enable_flag != SCN_ENABLE) {
		SCN_MTCNT_Status &= ~(IO_BIT_MOTOR_CLOCKWISE); /** 原稿繰り込み方向に設定 */
		SCN_IsMotorClockwise = TRUE;	/** 回転方向(正転)を記憶 */
	}
	else {
		SCN_MTCNT_Status |= IO_BIT_MOTOR_CLOCKWISE; /** 原稿繰り込みと反対の方向に設定 */
		SCN_IsMotorClockwise = FALSE;	/** 回転方向(逆転)を記憶 */
	}
#endif
	outp(MTCNT_PORT, SCN_MTCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[モーター許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : モーター許可
								SCN_DISABLE: モーター禁止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetMotor( UBYTE enable_flag )
{
	if (enable_flag == SCN_ENABLE) {
		SCN_MTCNT_Status |= IO_BIT_MOTOR_ENABLE; /** モーター許可 */
	}
	else {
		SCN_MTCNT_Status &= ~(IO_BIT_MOTOR_ENABLE); /** モーター許可 */
	}
	outp(MTCNT_PORT, SCN_MTCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[設定周波数でのブザー許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : ブザー許可
								SCN_DISABLE: ブザー禁止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetBuzzer( UBYTE enable_flag )
{
	if (enable_flag == SCN_ENABLE) {
		SCN_SCCNT_Status |= IO_BIT_BUZZER_ENABLE; /** ブザー許可 */
	}
	else {
		SCN_SCCNT_Status &= ~(IO_BIT_BUZZER_ENABLE); /** ブザー禁止 */
	}
	outp(SCCNT_PORT, SCN_SCCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[ソフトスキャン許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : ソフトスキャン許可
								SCN_DISABLE: ハードスキャン許可
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[スキャン・イネーブル信号（ＣＴＳＣＡＮ発生回路）の
						ソフト／ハードの切り替え
						スキャン開始／停止はSCN_SetStartSoftScan()へ移動する。(Aug.14,1994)
						]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetSoftScan( UBYTE enable_flag )
{
	if (enable_flag == SCN_ENABLE) {
		SCN_SCCNT_Status |= IO_BIT_SCAN_SOFT_ENABLE; /** ソフト・スキャン許可 */
	}
	else {
		SCN_SCCNT_Status &= ~(IO_BIT_SCAN_SOFT_ENABLE); /** ハード・スキャン許可 */
	}
	outp(SCCNT_PORT, SCN_SCCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[ソフトスキャン開始／停止]
		function	:	[
						引き数　SCN_ENABLE : ソフトスキャン開始
								SCN_DISABLE: ハードスキャン停止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[スキャン・イネーブル信号（ＣＴＳＣＡＮ発生回路）の
						開始／停止の切り替え
						]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/8/14]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetStartSoftScan( UBYTE enable_flag )
{
	if (enable_flag == SCN_ENABLE) {
		SCN_SCCNT_Status |= IO_BIT_SCAN_SOFT_START; /** ソフト・スキャン・開始 */
	}
	else {
		SCN_SCCNT_Status &= ~(IO_BIT_SCAN_SOFT_START); /** ソフト・スキャン・中止 */
	}
	outp(SCCNT_PORT, SCN_SCCNT_Status);
}

/** Module Header For CIM-E ********************************************
		module		:	[スキャンＤＭＡ許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : スキャンＤＭＡ許可
								SCN_DISABLE: スキャンＤＭＡ禁止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void SCN_SetScanDMA( UBYTE enable_flag )
{
	if (enable_flag == SCN_ENABLE) {
		SCN_SCCNT_Status |= IO_BIT_SCAN_DMA_ENABLE; /** スキャンＤＭＡの許可 */
	}
	else {
		SCN_SCCNT_Status &= ~(IO_BIT_SCAN_DMA_ENABLE); /** スキャンＤＭＡの禁止 */
	}
	outp(SCCNT_PORT, SCN_SCCNT_Status);
}

/*************************************************************************
	module		:[ソフトCTSCAN制御]
	function	:[
		ソフトでCTSCANを「連続ON」か「モーター同期」かを切り替える
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		引数指定
		SCN_ENABLE		連続スキャン
		SCN_DISABLE		MT同期スキャン
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/06/11]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_SetSoftCTSCAN(
	UBYTE	enable_flag)
{
	if (enable_flag == SCN_ENABLE) {
		SCN_SCNINT_Status |= IO_BIT_CCTSCAN;
	}
	else {
		SCN_SCNINT_Status &= ~(IO_BIT_CCTSCAN);
	}
	outp(SCNINT_PORT, SCN_SCNINT_Status);
}


/*************************************************************************
	module		:[モーター励磁相設定]
	function	:[
		指定されたモーター励磁相をスキャナG/Aにセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/10/12]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_SetMotorExciteMethod(
	UBYTE	excite_method)
{
	if (excite_method == SCN_MOTOR_1_2_EXCITE) {	/** 1-2相励磁 */
		SCN_MTP1_Status |= IO_BIT_MOTOR_EXCITE_METHOD;
	}
	else {											/** 2相励磁 */
		SCN_MTP1_Status &= ~(IO_BIT_MOTOR_EXCITE_METHOD);
	}
	outp(MTP1_PORT, SCN_MTP1_Status);
}

/*************************************************************************
	module		:[モーター速度の設定]
	function	:[
		指定されたモーター速度をスキャナG/Aにセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/10/12]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_SetMotorPulseRate(
	UWORD	speed)		/* モーター速度 (3000000/pps) */
{
	/** モーターの速度設定 (MTPC0,1) */
	SCN_MTPC0_Status = (UBYTE)(0x00FF&speed);
	SCN_MTPC1_Status = (UBYTE)(0x001F&(speed>>8));
	outp( MTPC0_PORT, SCN_MTPC0_Status );
	outp( MTPC1_PORT, SCN_MTPC1_Status );
}

/*************************************************************************
	module		:[モーター速度変更割り込みステップの設定]
	function	:[
		指定された値をスキャナG/Aにセットする
		※1-2相励磁では2倍してG/Aにセットする
		※G/Aへの設定値は-1する (1step=0)
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/10/12]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_SetMotorIntStep(
	UWORD			step,			/* 速度変更割り込みステップ (step) */
	UBYTE	excite_method)	/* モーター励磁相 */
{
	/** モーター/ミラーエラー検出用に記憶する */
	SCN_MotorIntStep = step;

	/**	1-2相励磁の場合はG/Aへの設定値を2倍する
	**	(割り込みステップ数を2相励磁に合せるため)
	*/
	if (excite_method == SCN_MOTOR_1_2_EXCITE) {
		step *= 2;
	}

	/** モーターの速度変更間隔設定 (MTP0) */
	step -= 1;		/* ※G/Aへの設定値は-1する(1step=0) */
	SCN_MTP0_Status = (UBYTE )(0x00FF&step);
	SCN_MTP1_Status &= 0xE0;
	SCN_MTP1_Status |= (UBYTE)(0x001F&(step>>8));
	outp( MTP0_PORT, SCN_MTP0_Status );
	outp( MTP1_PORT, SCN_MTP1_Status );
}

/*************************************************************************
	module		:[読み取り間隔ステップの設定と初期ラッチ]
	function	:[
		指定された値をスキャナG/A(SCNINT)にセットする
		※1-2相励磁では2倍する
		※G/Aへの設定値は-1する (1step=0)
			SF:  2相/ 582pps = 1 step
			SF:1-2相/1185pps = 2 step
			 F:  2相/1185pps = 2 step
			 N:  2相/2330pps = 4 step
		初期ラッチする
	]
	return		:[]
	common		:[]
	condition	:[
		モーター励磁相が決定してからcallすること
	]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/11/01]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_SetScanInterval(
	UBYTE	interval,	/* 読み取り間隔ステップ (step) */
	UBYTE	excite)		/* モーター励磁相 */
{
	/**	1-2相励磁の場合はG/Aへの設定値を2倍する
	**	(読み取り間隔を2相励磁に合せるため)
	*/
	if (excite == SCN_MOTOR_1_2_EXCITE) {
		interval *= 2;
	}

	interval -= 1;
	SCN_SCNINT_Status &= ~(IO_BIT_SCANINT);
	SCN_SCNINT_Status |= interval;
	outp( SCNINT_PORT, SCN_SCNINT_Status );

	/* メモリー送信原稿後端が縮む件 T.Nose 1997/11/05 */
	/* 原稿蓄積中にラッチがあった */
	if (DEBUG_DocumentScanning) {
		SYB_MaintenanceSwitch[MNT_SW_I5] = SCN_SCNINT_Status;
	}
	SYB_MaintenanceSwitch[MNT_SW_I6] = SCN_SCNINT_Status;

	/** 初期ラッチ */
	SCN_SCCNT_Status |= IO_BIT_SCAN_INTERVAL_LATCH;
	outp( SCCNT_PORT, SCN_SCCNT_Status );
	SCN_SCCNT_Status &= ~(IO_BIT_SCAN_INTERVAL_LATCH);
	outp( SCCNT_PORT, SCN_SCCNT_Status );
	SCN_SCCNT_Status |= IO_BIT_SCAN_INTERVAL_LATCH;
	outp( SCCNT_PORT, SCN_SCCNT_Status );
}

