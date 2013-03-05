/* copy 1996/12/25 */
/* Original File : jun\usr1:\src\rice\v53\kiri\src\scn_sub.c */
/***********************************************************************
*               BY:  S.Kawasaki
*             DATE:  Mar.14,1993
*        FILE NAME:  scn_sub.c
*      DESCRIPTION:	 スキャナー用モジュール
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:
*      MODULE NAME:	void far MAN_WatchDocumentSetTask( void )
*					void far MAN_WatchDocumentOutTask( void )
*					void far MAN_DocumentInTask( void )
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\param.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysscan.h"	/* ADF/FBS識別  s.takeuchi */
#include "\src\atlanta\define\idp301.h"
#include "\src\atlanta\define\scn_io.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\mntsw_c.h"
#include "\src\atlanta\define\mntsw_e.h"
#include "\src\atlanta\define\mntsw_i.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\idp_pro.h"
#include "\src\atlanta\define\idp_def.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\scn_pro.h"
#include "\src\atlanta\define\stng_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\idp_data.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\scn_tbl.h"
#include "\src\atlanta\ext_v\man_data.h"
#include "\src\atlanta\ext_v\cl1_data.h"

#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"

#include "\src\atlanta\define\mntsw_a.h" /* POPLAR_L 画質デバッグ */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
#include "\src\atlanta\ext_v\sys_inf.h"
#endif

void SCN_SaveStopMotor_Address();
/* スキャナー送信 左端影が出る T.Nose 1998/03/25 */
#include "\src\atlanta\define\sysshad.h"

#if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/08/12 */
#include "\src\atlanta\define\cmn_def.h"
#endif

/** Module Header For CIM-E ********************************************
		module		:	[原稿読み取り終了後にモーター速度停止が必要かをチェック]
		function	:	[モーター停止が必要な条件
						　１．スタンプ設定がＯＮ
						　２．モード変更有り
						　３．次原稿が無い
						　４．上記１、２、３は原稿蓄積のみチェックする。
						 ]
		return		:	[
						　０：停止不必要
						　１：停止必要
						]
		common		:	[
						]
		condition	:	[]
		comment		:	[
						読み取り終了割り込みでのみコールされる
						]
		machine		:	[]
		language	:	[]
		keyword		:	[]
		date		:	[94/8/19]
		author		:	[川崎真史]
************************************************************************/
UBYTE SCN_CheckMotorStop( void )
{
	if ( SCN_Control.UseType == IDP_DOCUMENT_STORE ) { /** 原稿蓄積モードである */

		/**	送信原稿で枚数指定されていて、次原稿があって、
		**	指定枚数に達していたら停止する
		*/	/* 枚数指定チェック  1997/02/18 */
		if ((SYS_DocumentStoreItem == SYS_MEM_TX_FILE)
#if (PRO_FBS == ENABLE)
		 && (SYS_ScannerExecMode == SCN_ADF)
#endif
		 && DS1()
		 &&	(SYB_CommandFile[SYS_DocumentStoreNo].Page != 0)
		 &&	(SYS_DocumentStorePage >= SYB_CommandFile[SYS_DocumentStoreNo].Page)) {
			SCN_MotorStopRequest = 1;
			SCN_StorePageCountError = TRUE;	/* 枚数指定エラーとする */
			return (1); /** 停止必要 */
		}

#if (PRO_COPY_FAX_MODE == ENABLE) /* コピー／ＦＡＸ切り替えあり */
		if ((SYS_StampFlag ==1) || 			/** スタンプ設定がＯＮ */
			(!DS1()) ||						/** 次原稿が無い */
			(CHK_ReadyModeCopy() && (SCN_ModeSw != SYB_CopyModeSw)) || 	/** TBD 蓄積モードの変更があった */
			(!CHK_ReadyModeCopy() && (SCN_ModeSw != SYB_ModeSw))) { 	/** TBD 蓄積モードの変更があった */
			SCN_MotorStopRequest = 1;
			return (1); /** 停止必要 */

		}
#else
		if ((SYS_StampFlag ==1) || 			/** スタンプ設定がＯＮ */
			(SCN_ModeSw != SYB_ModeSw) || 	/** TBD 蓄積モードの変更があった */
			(!DS1())) {						/** 次原稿が無い */
			SCN_MotorStopRequest = 1;
			return (1); /** 停止必要 */

		}
#endif
		else {
			SCN_MotorStopRequest = 0;
			return (0); /** 停止不必要 */
		}
	}
	else { /** スキャナー送信 */
		SCN_MotorStopRequest = 1;
		return (0); /** 停止不必要 */
	}
}

/** Module Header For CIM-E ********************************************
		module		:	[モーター速度停止が必要かをチェック]
		function	:	[
						 ]
		return		:	[
						　０：停止不必要
						　１：停止必要
						]
		common		:	[
						]
		condition	:	[]
		comment		:	[
						読み取り終了割り込みでのみコールされる
						]
		machine		:	[]
		language	:	[]
		keyword		:	[]
		date		:	[94/8/19]
		author		:	[川崎真史]
************************************************************************/
UBYTE SCN_CheckMotorStopAfterScan( void )
{
	/* return (1); /** デバッグ用　停止必要で固定 */
	return (SCN_MotorStopRequest); /** 本来のパス */
}

/** Module Header For CIM-E ********************************************
		module		:	[モーター速度及び速度変更間隔を設定]
		function	:	[１．SCN_MotorTablePointのモータースピード及び
						 　　ステップ数を設定する。初期ラッチ無し。
						 ２．SCN_MotorTabelePointは更新しない。
						 ]
		return		:	[無し]
		common		:	[
						SCN_MotorTablePoint
						SCN_MotorPointer->TroughUpDownTable[SCN_MotorTablePoint].PPS
						SCN_MotorPointer->TroughUpDownTable[SCN_MotorTablePoint].Step
						SCN_MTPC0_Status
						SCN_MTPC1_Status
						SCN_MTP0_Status
						SCN_MTP1_Status
						]
		condition	:	[]
		comment		:	[
			※G/Aへ設定するステップ数は(Step-1)をセットすること
		]
		machine		:	[]
		language	:	[]
		keyword		:	[]
		date		:	[94/3/30]
		reviewed	:	[94/6/6]
		author		:	[川崎真史]
************************************************************************/
void SCN_SetMotorSpeed(void)
{
	struct MOTOR_t	*current_speed;		/* ポインタ化  s.takeuchi */

	current_speed = &SCN_MotorPointer->ThroughUpDownTable[SCN_MotorTablePoint];

	/* モーターの速度設定 (MTPC0,1) */
	SCN_SetMotorPulseRate( current_speed->PPS );

	/* モーターの速度変更間隔設定 (MTP0) */
	SCN_SetMotorIntStep( current_speed->Step, SCN_MotorPointer->ExciteMethod );

	/* モーター電流値設定 (MTP1) */
	SCN_SetMotorCurrent( current_speed->CurrentPower );

	/* モーター励磁相設定 (MTP1) */
	SCN_SetMotorExciteMethod( SCN_MotorPointer->ExciteMethod );
}

/** Module Header For CIM-E ********************************************
		module		:	[モーター速度制御用変数に応じて最適な速度を設定]
		function	:	[
						１．SCN_MotorSpeedControlの状態により加速／減速の区別を行い、
						    モーターテーブル用のポインターを適切な値にセットする。
						２．加速要求中
							２－１．トップスピードに達していない場合
									モーターテーブル用ポインターを進めて加速する。
							２－２．減速領域にある場合
									減速領域を指しているモーターテーブル用ポインター
									を加速領域へ移動させ、モーターテーブル用ポインター
									を進めて加速する。
							２－３．定速中（トップスピードに達している場合）
									何もしない。
						３．減速要求中
							３ー１．加速領域にある場合
									加速領域を指しているモーターテーブル用ポインター
									を減速領域へ移動させ、モーターテーブル用ポインターを
									進めて、減速する。
							３－２．減速領域にある場合
									モーターテーブル用ポインターを進めて減速する。
							３ー３．減速の最終スピードに達している場合
									この場合モーターは停止処理を行う。
						]
  		return		:	[無し]
		common		:	[
						SCN_MotorSpeedControl
						SCN_MotorTablePoint
						SCN_MotorTablePointer->TopSpeed
						SCN_MotorTablePointer->LowSpeed
						]
		condition	:	[]
		comment		:	[
			ICHOU用に速度整合処理を追加  1996/08/14
		]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
     	reviewed	:	[94/6/6]
 		author		:	[川崎真史]
************************************************************************/
void SCN_AdjustMotorSpeed(void)
{
#if (PRO_SEPERATE_24V == DISABLE)
	/* プリンターカバーが開けられると２４Ｖがカットされ、
	** モータが止まってしまうので、モータ制御も止める
	*/
#if (0)
//	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
//		SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
//		SCN_StopMotor();
//		return;
//	}
#endif
#if (PRO_FBS == ENABLE)
	if ((SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)
	 || RXIL()) {
		SCN_MirrorMoveStatus = MIRROR_MOVE_RXIL_ABORT;
		SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
		SCN_StopMotor();
		return;
	}
#else
 #if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/08/12 */
	if (SYS_CheckerMode != CHECKER_ADF_ASSY) {
		if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
			SCN_StopMotor();
			return;
		}
	}
 #else
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
		SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
		SCN_StopMotor();
		return;
	}
 #endif
#endif
#endif
	/*-------------------------------*/
	/* モーターの加速要求がある場合  */
	/*-------------------------------*/
	if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_UP) { /** 加速指示 */
		if (SCN_MotorTablePoint < SCN_MotorPointer->TopSpeed) { /** 加速中でトップスピードに達していない */
			++SCN_MotorTablePoint; /** モーターテーブルを加速 */
			SCN_SetMotorSpeed(); /** モーターの速度、速度変更間隔設定 */

			/** 最高速になればCTSCANをONする */
			if (SCN_MotorTablePoint == SCN_MotorPointer->TopSpeed) {
				if (SCN_Control.UseType != IDP_SCANNER_TX) {
					SCN_SetSoftCTSCAN( SCN_ENABLE );
				}
				else {
#if (PRO_CCD == DPI300)
	/* STx First Scan T.Nose 1998/06/29 */
	#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
					if (SYB_MaintenanceSwitch[MNT_SW_E0] & 0x80) {
						SCN_SetSoftCTSCAN( SCN_ENABLE );
					}
					else {
						/* スキャナ送信でも、15.4l/mmでスキャンする時はCTSCANを立てる */
						if (SCN_ModeSw != SYS_NORMAL)  {
							SCN_SetSoftCTSCAN( SCN_ENABLE );
						}
						/* ここからファイン→ノーマル変換 T.Nose Add By M.Kotani 1998/01/17 */
						if (SCN_ModeSw == SYS_NORMAL) { /** 読み取りモードをチェック */
							if (CHK_UNI_FineNormalConvert()) { /* ファイン→ノーマル変換する */
								SCN_SetSoftCTSCAN( SCN_ENABLE );
							}
						}
						/* ここまでファイン→ノーマル変換 T.Nose Add By M.Kotani 1998/01/17 */
					}
	#else
					/* スキャナ送信でも、15.4l/mmでスキャンする時はCTSCANを立てる */
					if (SCN_ModeSw != SYS_NORMAL)  {
						SCN_SetSoftCTSCAN( SCN_ENABLE );
					}
					/* ここからファイン→ノーマル変換 T.Nose Add By M.Kotani 1998/01/17 */
					if (SCN_ModeSw == SYS_NORMAL) { /** 読み取りモードをチェック */
						if (CHK_UNI_FineNormalConvert()) { /* ファイン→ノーマル変換する */
							SCN_SetSoftCTSCAN( SCN_ENABLE );
						}
					}
					/* ここまでファイン→ノーマル変換 T.Nose Add By M.Kotani 1998/01/17 */
	#endif
#endif
#if (PRO_CCD == DPI200)	/**add By T.Yamaguchi and M.Kotani 1997/11/16*/
					/* スキャナ送信でも、15.4l/mmでスキャンする時はCTSCANを立てる */
					if (SCN_ModeSw == SYS_SFINE)  {
						SCN_SetSoftCTSCAN( SCN_ENABLE );
					}
#endif
#if (PRO_CCD == DPI400)
					/* スキャナ送信でも、15.4l/mmでスキャンする時はCTSCANを立てる */
					if ((SCN_ModeSw != SYS_NORMAL) && (SCN_ModeSw != SYS_FINE))  {
						SCN_SetSoftCTSCAN( SCN_ENABLE );
					}
#endif
				}
			}
#if (0)
/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
			else if (SCN_MotorTablePoint == 6) { /* ６段まで加速したら */
				if ((SCN_Control.UseType == IDP_SCANNER_TX)
				 && (SYB_MaintenanceSwitch[MNT_SW_E0] & 0x80)) {
					SCN_SetScanDMA( SCN_DISABLE ); /* イメージ転送禁止 */
					SCN_SetScanDMA( SCN_ENABLE ); /* イメージ転送許可 */
				}
			}
#endif
#endif
		}
		else if (SCN_MotorPointer->TopSpeed < SCN_MotorTablePoint) { /** 減速中の加速制御 */
			/** 減速領域のモーター用ポインターを加速領域へ移動 */
			SCN_MotorTablePoint -= (SCN_MotorTablePoint - SCN_MotorPointer->TopSpeed) * 2;
			++SCN_MotorTablePoint; /** モーターテーブルを加速 */
			SCN_SetMotorSpeed(); /** モーターの速度、速度変更間隔設定 */

			/** 最高速になればCTSCANをONする */
			if (SCN_MotorTablePoint == SCN_MotorPointer->TopSpeed) {
				if (SCN_Control.UseType != IDP_SCANNER_TX) {
					SCN_SetSoftCTSCAN( SCN_ENABLE );
				}
				else {
#if (PRO_CCD == DPI300)
					/* スキャナ送信でも、15.4l/mmでスキャンする時はCTSCANを立てる */
					if (SCN_ModeSw != SYS_NORMAL)  {
						SCN_SetSoftCTSCAN( SCN_ENABLE );
					}
#else
 #if (PRO_CCD == DPI200)	/* 1999/12/01 Nose */
					/* スキャナ送信でも、15.4l/mmでスキャンする時はCTSCANを立てる */
					if (SCN_ModeSw == SYS_SFINE)  {
						SCN_SetSoftCTSCAN( SCN_ENABLE );
					}
 #endif
 #if (PRO_CCD == DPI400)
					/* スキャナ送信でも、15.4l/mmでスキャンする時はCTSCANを立てる */
					if ((SCN_ModeSw != SYS_NORMAL) && (SCN_ModeSw != SYS_FINE))  {
						SCN_SetSoftCTSCAN( SCN_ENABLE );
					}
 #endif
#endif
				}
			}
		}
		else { /** 定速中 */
		}
	}
	/*-------------------------------*/
	/* モーターの減速要求がある場合  */
	/*-------------------------------*/
	else if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_DOWN) { /** 減速指示 */
		if ((SCN_MotorTablePoint <= SCN_MotorPointer->TopSpeed)
		&&	(SCN_MotorPointer->TopSpeed < SCN_MotorPointer->LowSpeed)) { /** 加速中/定速中の減速 */

			/** 今、最高速なら1速下がるのでCTSCANをOFFする */
			if (SCN_MotorTablePoint == SCN_MotorPointer->TopSpeed) {
				SCN_SetSoftCTSCAN( SCN_DISABLE );	/** CTSCAN OFF  */
			}

			/** 加速領域のモーター用ポインターを減速領域へ移動 */
			SCN_MotorTablePoint += (SCN_MotorPointer->TopSpeed - SCN_MotorTablePoint) * 2;
			++SCN_MotorTablePoint; /** モーターテーブルを減速 */
			SCN_SetMotorSpeed(); /** モーターの速度、速度変更間隔設定 */
		}
		else if (SCN_MotorTablePoint < SCN_MotorPointer->LowSpeed) { /** 減速中で減速の最終速度に達していない */
			++SCN_MotorTablePoint; /** モーターテーブルを減速 */
			SCN_SetMotorSpeed(); /** モーターの速度、速度変更間隔設定 */
		}
		else { /** モーターが最終の速度に達した */
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP; /** モーター停止中 */
			SCN_StopMotor(); /** モーター停止 */
			SCN_StopScanLine = SCN_ReadMotorPulseCounter(); /* Sep.8,1994 */
/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
			if (SYB_MaintenanceSwitch[MNT_SW_E0] & 0x80) {
				SCN_SetScanDMA( SCN_ENABLE ); /* イメージ転送許可 */
			}
#endif
		}
	}
	/**	読み取りフィード用のモーターテーブル(SCN_xxx_FEED)の時は
	**	次の読み取りモーターテーブル(SCN_xxx)に切替えるために
	**	LowSpeedまでテーブルのポインタを進める(減速させるだけで停止はしない)
	**		ICHOUの繰り込み制御変更のため  1996/08/14 s.takeuchi
	*/
	else if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_ADJUST) {	/**	速度整合指示 */
		/**	最終速度でない時は、減速方向にポインタを一つ進める
		**	それ以外の時はそのままのポインタ(速度)で駆動する
		*/
		if (SCN_MotorTablePoint != SCN_MotorPointer->LowSpeed) {
			++SCN_MotorTablePoint;
			SCN_SetMotorSpeed();
		}
	}
}

/** Module Header For CIM-E ********************************************
		module		:	[原稿繰り込み／排出開始]
		function	:	[
						引き数：ＳＣＮ＿ＤＯＣ＿ＩＮ　	原稿繰り込み起動
								ＳＣＮ＿ＤＯＣ＿ＯＵＴ	原稿排出起動
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/6/6]
 		author		:	[川崎真史]
************************************************************************/
void SCN_StartFeed( UBYTE feed_in_out )
{
	SCN_VerticalMode = feed_in_out;							/** 原稿繰り込み又は排出用のモードにセット */
	SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode];	/** モーター制御用テーブルのポインター確保 */

#if defined(POPLAR_F)
	/* 1999/11/15 Y.Murata
	 * ＫＡＫＩでの対策を入れます。とりあえず今は、Ｌ４００後継だけにしときます。
	*/

	/** 原稿蓄積中断([通信中止(Review)]による中止）でSCN_ADF_MotorStopRequest がADF_MOTOR_STOP_REQUESTの状態だと,	**
	*** (次のモータ割込みで)下記で設定しているSCN_MotorSpeedControlが SCN_MOTOR_SPEED_DOWN に再設定され、その後の  	**
	*** スピード調整でSCN_MotorTablePointを初期値(0)に設定したのが最終スピード(18)に計算され直しモータストップ  	**
	*** 処理に入る。 CMN_TUP.Cで励磁OFF処理を実施しているが、このルーチン内のSCN_SetMotorPulse(SCN_ENABLE)がCall	**
	*** されるまでにモータが止まっていれば、「通信画面が待機に戻らない」、「原稿排出しているのにピックアップローラ  **
	*** が上がらない」等の 現象が発生し、モータがまだ止まっていなければ「モータ回りっぱなし]の不具合現象発生		**
	*** (修正方法）SCN_DOC_OUT時はここでSCN_ADF_MotorStopRequestを初期値(ADF_MOTOR_NO_STOP)に設定。	S.Fukui Aug.28	**
	**/
	if (feed_in_out == SCN_DOC_OUT) {
		SCN_ADF_MotorStopRequest = ADF_MOTOR_NO_STOP;
	}
#endif

	SCN_MotorTablePoint = SCN_MotorTable->InitialSpeed;		/** モーターのテーブルを初期値にセット */
	SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;				/** モーターをスルー・アップするように設定 */

#if (PRO_FBS == ENABLE)
	SCN_SetMotorDrive( SCN_ADF );				/** スキャナモーターをADF側に切替える */
#endif

	SCN_SetScanDMA(SCN_DISABLE); 				/** スキャン用ＤＭＡ禁止 */

	SCN_SetMotorSpeed(); 						/** モーターの速度設定(MTPC0,1)、速度変更間隔設定(MTP0) */
	SCN_SetMotor(SCN_DISABLE); 					/** モーター・ディスエーブル */
	SCN_LatchMotorSpeedAndInterval(); 			/** モーター速度変更間隔、速度初期ラッチ */
	SCN_SetMotorSpeedIntervalInt(SCN_ENABLE); 	/** モーター速度変更間隔割り込み許可 	INTMTEN-MTCNT */
	SCN_SetMotorPulse(SCN_ENABLE); 				/** モーター励磁ＯＮ MTCLR-MTCNT */

	SCN_SetMotorClockwise( SCN_DISABLE );		/** モーター正転 */
	if (feed_in_out == SCN_DOC_IN) {
		SCN_SetDS2_ON_Int(SCN_ENABLE);			/** ＤＳ２　ＯＮ割り込み許可 */
	}
	SCN_ADF_MotorStopRequest = ADF_MOTOR_NO_STOP;	/* 1996/12/27 s.takeuchi */

	SCN_SetMotor(SCN_ENABLE); 					/** モーター・イネーブル・セット MTEN-MTCNT */
}

/** Module Header For CIM-E ********************************************
		module		:	[スキャナー・ドライバーのオープン]
		function	:	[]
  		return		:	[
  						SCN_OPEN_OK(0)
  						SCN_OPEN_ERROR(-1)
  						]
		common		:	[]
		condition	:	[
			ADF読取りではADF読取り位置へ、FBS読取りではホームセンサ上に
			ミラーキャリッジが移動済みであること…って要検討かも (^^;
		]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
WORD SCN_Open(void)
{
	UWORD reduction_pattern = 0;
	UBYTE scan_interval;		/* SCNINTポートの読取り間隔設定用 */
	UBYTE is_copy_file;		/* コピー原稿識別用 */
	UBYTE doc_item;

/* スキャナー送信 左端影が出る T.Nose 1998/03/25 */
	UBYTE i;

	SCN_FeedErrorCheckStep = 0;
	SCN_StorePageCountError = FALSE;	/* 枚数指定チェック  1997/02/18 */

#if (PRO_FBS == ENABLE)
	/** ADF読取りの場合は
	**	スキャナカバーと押圧板のオープンをチェックする
	**	ミラーがADF位置にあるかをチェックする
	*/
	if (SYS_ScannerExecMode == SCN_ADF) {
		if (TXIL()) {	/** スキャナカバーオープン */
			return (SCN_OPEN_ERROR);
		}
		/** ADF許可センサ:禁止(押圧板オープン) */
		if (SYS_MachineStatus[SYS_COVER_STATUS] & (SYS_COVER_BOOK_OPEN)) {
			return (SCN_OPEN_ERROR);
		}
	}
	/**	スキャナ送信の時にミラーキャリッジが移動し終わってるかをチェックする
	**	移動完了していなかったらオープンエラーで終了する
	*/
	if (((SYS_ScannerExecMode == SCN_ADF) && (SCN_MirrorCarriageStatus != MIRROR_ADF_READY))
	||	((SYS_ScannerExecMode == SCN_FBS) && (SCN_MirrorCarriageStatus != MIRROR_HS_ON))) {
		return (SCN_OPEN_ERROR);
	}

	/** 読み取り位置へ移動できていたら、ランプ点灯する */
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif
	LampOn();

	if (SYS_ScannerExecMode == SCN_FBS) {
		wai_tsk(30);	/* ランプが安定するまで 300mS 待つ */
	}

	/** ADF/FBSによって、モーターを切替える */
	SCN_SetMotorDrive( SYS_ScannerExecMode );

	/*---------------------*/
	/** IDP301 DIPP-AS設定 */
	/*---------------------*/
	DIPP_InitialSet();

	/*	ICHOUではスキャナ送信の1枚目ならここでランプチェックをする  1997/03/31 */
	if ((SCN_Control.UseType == IDP_SCANNER_TX)
	 &&	(SYS_ScannerExecMode == SCN_ADF)
	 &&	(SYS_TxTotalPage == 0)) {		/** ADFスキャナ送信の1ページ目 */
		if (!DIPP_QuickCheckLamp()) {		/** ランプチェック(結果:NG) */
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_LAMP_ERROR; /** ランプエラー */
			return (SCN_OPEN_ERROR);		/** ★ランプエラーで終了 */
		}
		/* スキャナー送信 左端影が出る対策 T.Nose 1998/03/26 */
		DIPP_InitialSet();
	}

#else /* (PRO_FBS == DISABLE) */

	if (TXIL()) {	/** スキャナカバーオープン */
		return (SCN_OPEN_ERROR);
	}
 #if (PRO_UPPER_COVER == ENABLE)	/* 1998/01/19  By T.Yamaguchi */
	/** ADF許可センサ:禁止(押圧板オープン) */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & (SYS_COVER_BOOK_OPEN)) {
		return (SCN_OPEN_ERROR);
	}
 #endif

	/** 読み取り位置へ移動できていたら、ランプ点灯する */
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif
	LampOn();

	/*---------------------*/
	/** IDP301 DIPP-AS設定 */
	/*---------------------*/
	DIPP_InitialSet();

	/* スキャナ送信の１ページならここでランプチェックする */
	if ((SCN_Control.UseType == IDP_SCANNER_TX)
	 &&	(SYS_TxTotalPage == 0)) {		/** ADFスキャナ送信の1ページ目 */
		if (!DIPP_QuickCheckLamp()) {		/** ランプチェック(結果:NG) */
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_LAMP_ERROR; /** ランプエラー */
			return (SCN_OPEN_ERROR);		/** ★ランプエラーで終了 */
		}
		/* スキャナー送信 左端影が出る対策 T.Nose 1998/03/26 */
		DIPP_InitialSet();
	}

#endif /* (PRO_FBS == DISABLE) */

	DIPP_WriteInitialRAM();
/* スキャナー送信 左端影が出る T.Nose 1998/03/25 */
if (SYB_MaintenanceSwitch[MNT_SW_E0] & 0x10) {
	DIPP_ReadInitialRAM( &SCN_DebugInitialRAM0[0]);
	for (i = 0; i < SYS_INITIAL_MAX; i++) {
		if (SYB_InitialRAM[i] != SCN_DebugInitialRAM0[i]) {
			SYB_MaintenanceSwitch[MNT_SW_E0] |= 0x40;
			if (SYB_MaintenanceSwitch[MNT_SW_E1] & 0x40) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_LAMP_ERROR; /** ランプエラー */
				return (SCN_OPEN_ERROR);		/** ★ランプエラーで終了 */
			}
			else {
				DIPP_WriteShadingRAM();
			}
			break;
		}
	}
}
	DIPP_WriteShadingRAM();
/* スキャナー送信 左端影が出る T.Nose 1998/03/25 */
if (SYB_MaintenanceSwitch[MNT_SW_E0] & 0x10) {
	DIPP_ReadShadingRAM( &SCN_DebugShadingRAM[0] );	/* 1997/04/25 */
	for (i=0; i<SYS_SHADING_MAX; i++) {
		if (SYB_ShadingRAM[i] != SCN_DebugShadingRAM[i]) {
			SYB_MaintenanceSwitch[MNT_SW_E0] |= 0x20;
			if (SYB_MaintenanceSwitch[MNT_SW_E1] & 0x40) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_LAMP_ERROR; /** ランプエラー */
				return (SCN_OPEN_ERROR);		/** ★ランプエラーで終了 */
			}
			else {
				DIPP_WriteInitialRAM();
			}
			break;
		}
	}
}

if (SYB_MaintenanceSwitch[MNT_SW_C9] & CHECK_SHADING_RAM) { /* 薄読みデバッグ用 */
	DIPP_ReadInitialRAM( &SCN_DebugInitialRAM0[0] );
}

	SCN_SetDIPP_Parameter();	/* IDP301-DIPPの設定を抜き出す  1996/11/25 */

	/*-----------------------------------------------------------*/
	/** IP設定に関するパラメータの設定を行います TBD Apr.24,1994 */
	/*-----------------------------------------------------------*/
	IP_Control.IP_UseType = SCN_Control.UseType;
	IP_Control.IP_Mode = SCN_ModeSw;	/** TBD  = SCN_Control.DocumentMode; */
	IP_Control.IP_InputSize = IP_GetInputSize(SCN_Control.UseType, SCN_Control.DocumentSize);
	IP_Control.IP_OutputSize = IP_GetOutputSize(IP_SCANNER_REDUCTION,
												SCN_Control.DocumentSize,
												SCN_Control.ScanReduction);

	IP_InitialSet();

	/******************************************/
	/* 二値／中間調（誤差拡散／ディザ）の設定 */
	/* DIPP-IP の主走査縮小率を設定           */
	/******************************************/
	/* 原稿種類を判別 */
	if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
		if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
		 || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {
			doc_item = SCN_MEMCOPY_DOC; /* コピー原稿 */
		}
		else {
			doc_item = SCN_MEMTX_DOC; /* メモリー送信原稿 */
		}
	}
	else {
		doc_item = SCN_SCNTX_DOC; /* スキャナー送信原稿 */
	}

	switch (SCN_ModeSw) {
	case SYS_NORMAL:
	case SYS_FINE:
	case SYS_SFINE:
	case SYS_HFINE:
	case SYS_EFINE:
	case SYS_E_HFINE:
		IP_SetDitherMatrix(1*1);
		IP_ReductionSet(IP_SCANNER_REDUCTION, 1000);
		break;
	case SYS_GRAY16:
	case SYS_GRAY16_SEP:
	case SYS_GRAY32:
	case SYS_GRAY32_SEP:
	case SYS_GRAY64:
	case SYS_GRAY64_SEP:
	case SYS_GRAY128:
	case SYS_GRAY128_SEP:
		if (IsGrayPatternDither(doc_item) == TRUE) {
			IP_SetDitherMatrix(8*8);
		}
		else {
			IP_SetGosaKakusan();
		}
		IP_ReductionSet(IP_SCANNER_REDUCTION, GetGrayReductionPattern(doc_item));
		break;
	default:
		break;
	}

	/*-----------------*/
	/** IP処理スタート */
	/*-----------------*/
	IP_SetBitIPST(IDP_BIT_ON);


	/*--------------------------------------------------------------------------*/
	/** ファイン－＞ノーマル変換を行って蓄積を行う場合は読取りはファインで     **/
	/** 蓄積はノーマルで行う。                                                 **/
	/*--------------------------------------------------------------------------*/
	/*	通常のADFページ間では何もしない
	**	モーター起動時だけ、読取りモードによって
	**		読取りステップ間隔をG/A(SCNINT)にセットする
	**		副走査のモーター速度テーブルを決定する
	**		(但し、スキャナ送信はモードに関係なくSFINEテーブル)
	*/
	/**	スキャナG/AにSCANSTART/ENDのステップ数をセットし初期ラッチする
	**	※ICHOUではSCN_Open()で繰り込み開始するため、ここでセットする  1996/10/17
	**  ANZU_Lに対応してページ間で開始ステップ、終了ステップを設定する必要があるので
	**  下方からこの位置に移動 T.Nose 1997/10/17
	*/
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)
	&&	(  (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
		|| (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE))) {
		is_copy_file = TRUE;
	}
	else {
		is_copy_file = FALSE;
	}

#if (PRO_SCN_CODEC_TYPE == MN86064)
 #if (PRO_CODEC_NUMBER == CDC_TRIPLE)
	/* V851スキャナ送信が縮む件 T.Nose 2002/08/12 */
	/* スキャナ送信で写真（４００ｘ４００）、A3->B4縮小で副走査が１／４に縮んだ絵が出た。
	** FCM、CDCが認識しているモードとSCNの読み取りモードが何らかの原因で違っていると
	** 思われるのでここで双方をチェックし、違っていたら読み取りモードを設定しなおします。
	*/
	if (SCN_Control.UseType == IDP_SCANNER_TX) {
		if (SCN_ModeSw != SYS_DocBlock.Src.Mode) {
			SCN_ModeSw = SYS_DocBlock.Src.Mode;
		}
	}
 #endif
#endif

	if (!SCN_CheckMotorStopAfterScan()) { /** モーター停止要求がなければ */
#if (PRO_DOC_IN == ENABLE)
		SCN_SetScanStartAndEndStep(SCN_MotorPointer->ExciteMethod, is_copy_file);
#endif
	}
	else { /** モーターの停止要求が有る(または最初の起動) */
		switch (SCN_ModeSw) { /** 読み取りモードをチェック */
		case	SYS_NORMAL: 	/* 普通     200dpi:8 dot/mm  100dpi:3.85l/mm */
			if ( SCN_Control.UseType == IDP_DOCUMENT_STORE ) {
#if (PRO_SCN_CODEC_TYPE == MN86064) /* T.Nose */
				/* ファイン→ノーマル変換 MN86064のみ */
				if (CHK_UNI_FineNormalConvert()) { /* ファイン→ノーマル変換する */
					scan_interval = 2;				/** FINE */
					SCN_VerticalMode = SCN_FINE;	/** モーター制御用のテーブルを決める */
				}
				else { /* ファイン→ノーマル変換しない */
					if (CMN_NormalScan4Sec()) { /* ノーマル４秒読取り */
						scan_interval = 2;				/** FINE */
						SCN_VerticalMode = SCN_FINE;	/** モーター制御用のテーブルを決める */
					}
					else { /* ノーマル２秒読取り */
						scan_interval = 4;				/** NORMAL */
						SCN_VerticalMode = SCN_NORMAL;	/** モーター制御用のテーブルを決める */
					}
				}
#else /* PRO_SCN_CODEC_TYPE else */
				scan_interval = 4;				/** NORMAL */
				SCN_VerticalMode = SCN_NORMAL;	/** モーター制御用のテーブルを決める */
#endif /* PRO_SCN_CODEC_TYPE end */
			}
			else {
				scan_interval = 4;				/** NORMAL */
				SCN_VerticalMode = SCN_NORMAL;	/** モーター制御用のテーブルを決める */
			}
			break;
		case	SYS_FINE:		/* 高画質   200dpi:8 dot/mm  200dpi:7.7 l/mm */
#if (PRO_CCD == DPI300)
			scan_interval = 2;					/** FINE */
			SCN_VerticalMode = SCN_FINE;		/** モーター制御用のテーブルを決める */
			if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
				if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
				 || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) { /** マルチコピー原稿 */
			 		scan_interval = 1;					/** EFINE */
					SCN_VerticalMode = SCN_EFINE;		/** モーター制御用のテーブルを決める */
				}
			}
			break;
#else
			scan_interval = 2;					/** FINE */
			SCN_VerticalMode = SCN_FINE;		/** モーター制御用のテーブルを決める */
			break;
#endif
		case	SYS_GRAY16:		/* 16階調   200dpi:8 dot/mm  200dpi:7.7 l/mm */
		case	SYS_GRAY16_SEP:	/* 16階調   200dpi:8 dot/mm  200dpi:7.7 l/mm */
		case	SYS_GRAY32:		/* 32階調   200dpi:8 dot/mm  200dpi:7.7 l/mm */
		case	SYS_GRAY32_SEP:	/* 32階調   200dpi:8 dot/mm  200dpi:7.7 l/mm */
		case	SYS_GRAY64:		/* 64階調   200dpi:8 dot/mm  200dpi:7.7 l/mm */
		case	SYS_GRAY64_SEP:	/* 64階調   200dpi:8 dot/mm  200dpi:7.7 l/mm */
			/* 中間調の場合次のように変更します。Oct.18,1994
			** １．マルチコピー原稿の場合、４００ｘ４００の誤差拡散で処理。
			** ２．送信原稿の場合、
			**      SCN_ModeSwがSYS_GRAY64/SYS_GRAY64_SEPの場合４００ｘ４００のディザ
			**      SCN_ModeSwがSYS_GRAY16/SYS_GRAY16_SEPの場合２００ｘ２００のディザでＩＤＰで縮小
			**
			**	ディザの蓄積は16x15.4で読んでIDP301(IP1)で縮小する  1996/12/05 s.takeuchi
			**		1.	IDP301(IP1)で中間調を縮小する場合は副走査論理縮小の指定はできない
			**		2.	ディザでは縮小後のディザマトリックスの構成は保持される
			**			(誤差拡散では拡散係数を演算後に間引かれる)
			**		3.	主走査のみの縮小(16dot/mm→8dot/mm)はできない
			**			(副走査をモータースピードで縮小すると主走査のみの縮小が必要)
			*/
#if (PRO_CCD == DPI400)
			if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
				if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
				 || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) { /** マルチコピー原稿 */
			 		scan_interval = 1;					/** SFINE */
					SCN_VerticalMode = SCN_SFINE;		/** モーター制御用のテーブルを決める */
				}
				else { /** 送信原稿 */
					if ((SCN_ModeSw == SYS_GRAY64)
					 || (SCN_ModeSw == SYS_GRAY64_SEP)) { /** ４００ｘ４００ディザ */
				 		scan_interval = 1;					/** SFINE */
						SCN_VerticalMode = SCN_SFINE;		/** モーター制御用のテーブルを決める */
					}
					else { /** ２００ｘ２００ディザ */
						scan_interval = 1;					/** SFINE */
						SCN_VerticalMode = SCN_SFINE;		/** モーター制御用のテーブルを決める */
					}
				}
			}
			else if (SCN_Control.UseType == IDP_SCANNER_TX) {
				scan_interval = 1;					/** SFINE */
				SCN_VerticalMode = SCN_SFINE;		/** モーター制御用のテーブルを決める */
			}
#endif /* (PRO_CCD == 400) */
#if (PRO_CCD == DPI300)
			if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
				if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
				 || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) { /** マルチコピー原稿 */
			 		scan_interval = 1;					/** EFINE */
					SCN_VerticalMode = SCN_EFINE;		/** モーター制御用のテーブルを決める */
				}
				else { /** 送信原稿 */
					scan_interval = 1;					/** FINE */
					SCN_VerticalMode = SCN_EFINE;		/** モーター制御用のテーブルを決める */
				}
			}
			else if (SCN_Control.UseType == IDP_SCANNER_TX) {
				scan_interval = 1;					/** FINE */
				SCN_VerticalMode = SCN_EFINE;		/** モーター制御用のテーブルを決める */
			}
#endif /* (PRO_CCD == DPI300) */
#if (PRO_CCD == DPI200)
			/* 200 x 200(100%) で蓄積 */
			scan_interval = 2;
			SCN_VerticalMode = SCN_FINE;
#endif
			break;
		case	SYS_SFINE:		/* 超高画質 200dpi:8 dot/mm  400dpi:15.4l/mm */
		case	SYS_HFINE:		/* 超高画質 400dpi:16dot/mm  400dpi:15.4l/mm */
	 		scan_interval = 1;					/** SFINE */
			SCN_VerticalMode = SCN_SFINE;		/** モーター制御用のテーブルを決める */
	 		break;
#if (PRO_CCD == DPI300)
		case	SYS_EFINE:		/* 1997/09/20 By M.Kotani */
			/*----------------------------------------------*/
			/* 超上画質   	12dot/m				11.56本/l 	*/
			/*												*/
			/*			EFINE	800(2相)/1600pps(1-2相)		*/
			/*----------------------------------------------*/
	 		scan_interval = 1;					/** EFINE */
			SCN_VerticalMode = SCN_EFINE;		/** モーター制御用のテーブルを決める */
			break;
		/* for ANZU_L 300*400 1997/11/13 by T.Soneoka */
		case	SYS_E_HFINE:
	 		scan_interval = 1;					/** EFINE */
			SCN_VerticalMode = SCN_SFINE;		/** モーター制御用のテーブルを決める */
			break;
#endif /* (PRO_CCD == DPI300) */
	 	default:
	 		scan_interval = 1;					/** SFINE */
			SCN_VerticalMode = SCN_SFINE;		/** モーター制御用のテーブルを決める */
	 		break;
		}

		/*	ICHOUで移動  1996/11/01
		**	1-2相励磁対応のため、読み取り間隔(SCNINT)のG/Aへのセットは、
		**	モーターテーブル(励磁相)決定後にする
		*/

		/** スキャナ送信の場合は、必ずSFINEでモーターをまわす */
		if (SCN_Control.UseType == IDP_SCANNER_TX) {
#if (PRO_CCD == DPI300)
	/* STx First Scan T.Nose 1998/06/29 */
	#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
			if (SYB_MaintenanceSwitch[MNT_SW_E0] & 0x80) {
				if (SCN_ModeSw == SYS_NORMAL) {
					SCN_VerticalMode = SCN_NORMAL;
				}
			}
			else {
				if (SCN_ModeSw == SYS_NORMAL) {
					SCN_VerticalMode = SCN_FINE;
				}
			}
	#else
			if (SCN_ModeSw == SYS_NORMAL) {
				SCN_VerticalMode = SCN_FINE;
			}
	#endif
#else
			SCN_VerticalMode = SCN_SFINE;
			/* ここからファイン→ノーマル変換 T.Nose Add By M.Kotani 1998/01/17 */
			if (SCN_ModeSw == SYS_NORMAL) { /** 読み取りモードをチェック */
				if (CHK_UNI_FineNormalConvert()) { /* ファイン→ノーマル変換する */
					scan_interval = 2;				/** FINE */
				}
			}
			/* ここまでファイン→ノーマル変換 T.Nose Add By M.Kotani 1998/01/17 */
#endif
		}

#if (PRO_FBS == ENABLE)
		if (SYS_ScannerExecMode == SCN_ADF) {	/** ADF読み取り */
#endif
			/**	最初のページの繰り込みだけ、繰り込み用のモーターテーブルに切り替える
			**	以降のページ間では、モーター割り込みでSCN_SFINEに替わり、
			**	2ページ目以降の停止→起動では、読み取り用のモーターテーブルで起動する
			*/
			if (SCN_DocumentStatus == SCN_DOC_ADF_1ST_PAGE) {
				switch (SCN_VerticalMode) {
				case	SCN_NORMAL:
					SCN_VerticalMode = SCN_NORMAL_FEED;
					break;
				case	SCN_FINE:
					SCN_VerticalMode = SCN_FINE_FEED;
					break;
#if (PRO_CCD == DPI300)
				case	SCN_EFINE:		/* 1997/09/20 By M.Kotani */
					SCN_VerticalMode = SCN_EFINE_FEED;
					break;
#endif /* (PRO_CCD == DPI300) */
				case	SCN_SFINE:
				default:
					SCN_VerticalMode = SCN_SFINE_FEED;
					break;
				}
			}
#if (PRO_FBS == ENABLE)
		}
		else {		/** FBS読み取り */
			/** 使用するモーターテーブルをFBS用のテーブルに切り替える */
			switch (SCN_VerticalMode) {
			case	SCN_NORMAL:
				SCN_VerticalMode = SCN_NORMAL_FBS;
				break;
			case	SCN_FINE:
				SCN_VerticalMode = SCN_FINE_FBS;
				break;
			case	SCN_SFINE:
			default:
				SCN_VerticalMode = SCN_SFINE_FBS;
				break;
			}
			/** ミラー用のパルスカウンタを０クリア */
			SCN_MirrorMotorPulseCount = 0;
		}
#endif

		SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode]; /** モーター制御用テーブルのポインター確保 */

		/** 読み取り間隔設定と初期ラッチ */	/* 1996/11/01 */
		SCN_SetScanInterval( scan_interval, SCN_MotorPointer->ExciteMethod );

		SCN_MotorTablePoint = SCN_MotorPointer->InitialSpeed; /** モーターの初期速度のテーブルを設定 */

		SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;	/** モーターをスルー・アップするように設定 */
		SCN_SetMotorSpeed(); /** モーターの速度、速度変更間隔設定 */

#if (0) /* 上へ移動 T.Nose 1997/10/01 */
		/**	スキャナG/AにSCANSTART/ENDのステップ数をセットし初期ラッチする
		**	※ICHOUではSCN_Open()で繰り込み開始するため、ここでセットする  1996/10/17
		*/
		if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)
		&&	(  (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
			|| (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE))) {
			is_copy_file = TRUE;
		}
		else {
			is_copy_file = FALSE;
		}
#endif
#if (PRO_FBS == ENABLE)
		SCN_SetScanStartAndEndStep( SYS_ScannerExecMode, SCN_MotorPointer->ExciteMethod, is_copy_file );

		/* ICHOUの読み取り中のDS2バウンス対策  1997/04/05 */
		if (SYS_ScannerExecMode == SCN_ADF) {	/** ADF読み取り */
			SCN_DS2_BounceMaxStep = SCN_GetMaxBounceStep();
		}
#else
		SCN_SetScanStartAndEndStep( SCN_MotorPointer->ExciteMethod, is_copy_file );

		/* ICHOUの読み取り中のDS2バウンス対策  1997/04/05 */
		SCN_DS2_BounceMaxStep = SCN_GetMaxBounceStep();
#endif

	}

	/**	ADF読取りでは、DS2OFFの場合にDS2割込みを許可する
	**	FBS読取りでは、ホームセンサOFF割込みを許可する
	**	(中身は同じポートに設定する)
	*/
#if (PRO_FBS == ENABLE)
	if (SYS_ScannerExecMode == SCN_ADF) {
		if (!DS2()) {
			SCN_SetDS2_ON_Int(SCN_ENABLE);		/** DS2 ON割り込み許可 DS2ONEN,DS2ONINTEN-DS2INTR */
		}
		else {
			SCN_SetDS2_ON_Int(SCN_DISABLE);		/** ＤＳ２　ＯＮ割り込み禁止 */
		}
	}
	else {	/* SCN_FBS */
		/**	ミラーキャリッジをFBS原稿先端へ移動中として、
		**	ホームセンサOFF割り込み許可する
		*/
		SCN_MirrorCarriageStatus = MIRROR_MOVE_TO_FBS_TOP;
		SCN_SetHS_OFF_Int(SCN_ENABLE);
	}
#else
	if (!DS2()) {
		SCN_SetDS2_ON_Int(SCN_ENABLE);		/** DS2 ON割り込み許可 DS2ONEN,DS2ONINTEN-DS2INTR */
	}
	else {
		SCN_SetDS2_ON_Int(SCN_DISABLE);		/** ＤＳ２　ＯＮ割り込み禁止 */
	}
#endif

	if (!SCN_CheckMotorStopAfterScan()) {		/** モーター停止要求がなければ */
	}
	else {		/** モーターの停止要求が有る */
		SCN_SetMotor(SCN_DISABLE); /** モーター・ディスエーブル */

		SCN_LatchMotorSpeedAndInterval(); /** モーター速度変更間隔、速度初期ラッチ */

		/** 次のモーター速度と割り込み間隔をセットしておく */
		/** ゲートアレイのバグの為、次モーターのテーブルを設定しても有効にならない。 */
		/********************* Not Need Mar.23,1994
		**SCN_MotorTablePoint++;
		**SCN_SetMotorSpeed();
		*******************************************/

		SCN_SetMotorSpeedIntervalInt(SCN_ENABLE);	/** モーター速度変更間隔割り込み許可 	INTMTEN-MTCNT */
		SCN_SetMotorPulse(SCN_ENABLE);				/** モーター励磁ＯＮ MTCLR-MTCNT */

#if (PRO_FBS == ENABLE)
		/** モーター回転方向をセット (ADF:正転  FBS:逆転) */
		if (SYS_ScannerExecMode == SCN_ADF) {
			SCN_SetMotorClockwise( SCN_DISABLE );	/* モーター：逆転 */
		}
		else {
			SCN_SetMotorClockwise( SCN_DISABLE );	/* モーター：逆転 */
			SCN_IsMirrorMoveEnd = FALSE;			/* ミラー停止中 */
		}
#else
		SCN_SetMotorClockwise( SCN_DISABLE );	/* モーター：逆転 */
#endif

		/** モーターの電流値を指定値にセット */
		SCN_SetMotorCurrent( SCN_MotorPointer->ThroughUpDownTable[SCN_MotorTablePoint].CurrentPower );

		/* SCN_SetSoftScan(SCN_ENABLE);	本来は禁止 Apr.24,1994 */
	}

	SCN_ClearMotorPulseCounter(); 		/** モーター・パルス・カウンター・クリア */
	SCN_SetScanDMA(SCN_ENABLE); 		/** スキャン用ゲートアレイからコーデックへのＤＲＥＱ許可 */

	/*	ICHOUはSCN_Open()で繰込むため、ここではSCANSTART割り込みを許可せずに
	*	DS2ON割り込みで許可する
	*		1996/09/24 s.takeuchi
	* SCN_SetScanStartInt(SCN_ENABLE); 	@** 読み取り先端割り込み許可 *@
	*/
#if (PRO_DOC_IN == ENABLE)
	SCN_SetScanStartInt(SCN_ENABLE);
#endif

	/*------------------------------------*/
	/**  For New G/A Interrupt 10/31,1994 **/
	/*------------------------------------*/
	SCN_DS2INTR_Status &= ~(IO_BIT_XLAINT_CLEAR);	/* 割り込みが止まる */
	outp(DS2INTR_PORT, SCN_DS2INTR_Status);

	SCN_SetMotor(SCN_ENABLE); /** モーター・イネーブル・セット MTEN-MTCNT */
	/** 繰り込み不良検出用のライン割り込みセット */

	return (SCN_OPEN_OK);
}
/** Module Header For CIM-E ********************************************
		module		:	[スキャナー・ドライバーのクローズ]
		function	:	[]
  		return		:	[　	SCN_SCANNER_COVER_OPEN	:排出中にカバーが開けれれた
							SCN_DOC_FEED_ERROR		:排出エラー
							SCN_DOC_EXIT_OK			:排出正常終了
						]
		common		:	[]
		condition	:	[]
		comment		:	[テンポラリ]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
UWORD SCN_Close( UBYTE doc_status )
{
	/* SCN_DocumentStatus = SCN_DOC_EXITING; @** 原稿のステータスを排出用にセット */
	SCN_DocumentStatus = doc_status; /** 原稿のステータスをセット */
	SCN_FeedErrorCheckStep = 0;

	tskno_SCN_WatchDocumentExitTask = 0xffff;
	tskno_SCN_WatchDocFeedTask = 0xffff;
	tskno_SCN_WatchDocCoverTask = 0xffff;

	/*---------------------------------*/
	/** 原稿排出正常終了監視タスク起動 */
	/*---------------------------------*/
	cre_tsk(&tskno_SCN_WatchDocumentExitTask, TSK_SCN_WATCHDOCUMENTEXITTASK, 0);

	/*----------------------------------*/
	/** 原稿繰り込み不良監視 タスク起動 */
	/*----------------------------------*/
	cre_tsk(&tskno_SCN_WatchDocFeedTask, TSK_SCN_WATCHDOCUMENTFEEDTASK, 0);

	/*--------------------------------*/
	/** Watch Cover Status タスク起動 */
	/*--------------------------------*/
	cre_tsk(&tskno_SCN_WatchDocCoverTask, TSK_SCN_WATCHDOCUMENTCOVERTASK, 0);

	/** 原稿排出時にDS1/DS2に原稿が無くなってから最高速でまわす回数を初期化する
	**	DS2～排出:1322step(86mm) / TopSpeed:16step
	**	20mm余裕を見て102回まわせば排出できるでしょう
	**		ICHOUではDS3がないための追加処理  1996/07/18 s.takeuchi
	*/
/*	SCN_DocExitTopSpeedCount = 102; */
	SCN_DocExitTopSpeedCount = SCN_DOC_EXIT_STEP;

	/**	監視する状態によって、必要な割り込み(DS2 ON/OFF Int)だけを許可するように変更
	**		1996/09/21 s.takeuchi
	*/
	switch (doc_status) {
	case	SCN_DOC_FEED_DS2ON_WAIT:
	case	SCN_DOC_STAMP_TEST_FEED_READY:
		SCN_SetDS2_ON_Int( SCN_ENABLE );	/** DS2ON割り込み許可 */
		SCN_SetDS2_OFF_Int( SCN_DISABLE );	/** DS2OFF割り込み禁止 */
		break;
	case	SCN_DOC_FEED_DS2OFF_WAIT:
		SCN_SetDS2_OFF_Int( SCN_ENABLE );	/** DS2OFF割り込み許可 */
		SCN_SetDS2_ON_Int( SCN_DISABLE );	/** DS2ON割り込み禁止 */
		break;
	default:	/* その他 (SCN_DOC_FEED_DS3OFF_WAIT / SCN_DOC_FEED_OUT) */
		SCN_SetDS2_ON_Int( SCN_DISABLE );	/** DS2ON割り込み禁止 */
		SCN_SetDS2_OFF_Int( SCN_DISABLE );	/** DS2OFF割り込み禁止 */
		break;
	}

	SCN_PageCount = 0;	/** テスト用のページカウンタを０クリアする */

	SCN_SetLineInt(SCN_DISABLE); /** ライン割り込み必要無し（禁止） */
	LampOff(); /** TBD */

	SCN_StartFeed(SCN_DOC_OUT); /** 原稿排出用のモーターを起動 */

	/*---------------------------------------------*/
	/** 蓄積関連タスクの状況をメッセージで待ち受け */
	/*---------------------------------------------*/
	rcv_msg(mbxno.SCN_Task, &SCN_Msg); /** 蓄積関連タスクの状況をメッセージで待ち受け */

	SCN_Message = SCN_Msg->Message; /** テンポラリ領域へ待避 */

	/*---------------------------------------------*/
	/* 不要タスクの消去                            */
	/*---------------------------------------------*/
	/*---------------------------------*/
	/** 原稿排出正常終了監視タスク起動 */
	/*---------------------------------*/
	if (tskno_SCN_WatchDocumentExitTask != 0xffff) {
		del_tsk(&tskno_SCN_WatchDocumentExitTask); /** 原稿排出正常終了監視タスク消去 */
	}
	if (tskno_SCN_WatchDocFeedTask != 0xffff) {
		del_tsk(&tskno_SCN_WatchDocFeedTask); /** 原稿繰り込み不良監視タスク消去 */
	}
	if (tskno_SCN_WatchDocCoverTask != 0xffff) {
		del_tsk(&tskno_SCN_WatchDocCoverTask); /** Watch CoverStatusタスク消去 */
	}

	/**	ADFでのモーターが停止するのを待つ
	**	ミラーキャリッジ側に切り替わらないため  1996/10/31
	*/
	while (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {
		wai_tsk( 5 );
	}

	return(SCN_Message);
}

/** Module Header For CIM-E ********************************************
		module		:	[ギア・バック・ラッシュ監視タスク]
		function	:	[]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[テンポラリ]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/5/17]
 		author		:	[川崎真史]
************************************************************************/
void SCN_GearBackLashTask(void)
{
	tskno_SCN_WatchGearBackLashTask = 0xffff;

	StoreTaskMsg.Item = FROM_SCN_GEAR_BACK_LASH_TASK;
	StoreTaskMsg.Message = MSG_SCN_GEAR_BACK_LASH_END;

	if (!DS1() && !DS2() && !TXIL()) {	/** 原稿無く、スキャナー・カバーがクローズされている */
										/* DS2チェック追加 T.Nose 1997/12/08 */
		SCN_Init();		/* スキャナ誤動作のためメインタスクから移動  1997/05/09 */

#if (PRO_FBS == ENABLE)
		/** スキャナモーターをADF側に切替える */
		SCN_SetMotorDrive( SCN_ADF );
#endif

		/*-------------------------------------------*/
		/** ギア・バック・ラッシュ終了監視タスク起動 */
		/*-------------------------------------------*/
		cre_tsk(&tskno_SCN_WatchGearBackLashTask, TSK_SCN_WATCHGEARBACKLASHTASK, 0);

		SCN_DocumentStatus = SCN_DOC_GEAR_BACK_LASH;
		SCN_VerticalMode = SCN_GEAR_BACKLASH;

		SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode];	/** モーター制御用テーブルのポインター確保 */
		SCN_MotorTablePoint = SCN_MotorPointer->InitialSpeed;
		SCN_SetMotorSpeed();		/** モーターの速度、速度変更間隔設定 */

		SCN_SetMotor(SCN_DISABLE);	/** モーター・ディスエーブル */

		SCN_LatchMotorSpeedAndInterval();			/** モーター速度変更間隔、速度初期ラッチ */
		SCN_SetMotorSpeedIntervalInt(SCN_ENABLE);	/** モーター速度変更間隔割り込み許可 INTMTEN-MTCNT */
		SCN_SetMotorPulse(SCN_ENABLE);				/** モーター励磁ＯＮ MTCLR-MTCNT */
		SCN_SetMotorClockwise( SCN_ENABLE );		/** モーターを逆転にセット CWXCCW-MTCNT */
		SCN_SetMotorCurrent(SCN_CURRENT_POWER_100);	/** モーターの電流値を１００％にセット */
		SCN_SetMotor(SCN_ENABLE);					/** モーター・イネーブル・セット MTEN-MTCNT */

		/*-------------------------------------------------------------------*/
		/** ギア・バック・ラッシュ終了監視タスクの状況をメッセージで待ち受け */
		/*-------------------------------------------------------------------*/
		rcv_msg(mbxno.SCN_GearBackLashTask, &SCN_Msg);

		/*-------------------------------------------*/
		/** ギア・バック・ラッシュ終了監視タスク消去 */
		/*-------------------------------------------*/
		if (tskno_SCN_WatchGearBackLashTask != 0xffff) {
			del_tsk(&tskno_SCN_WatchGearBackLashTask);
		}

		/* タイムアウト発生時の強制停止処理  1997/05/09 s.takeuchi */
		CMN_DisableInterrupt();
		if (GearBackLashTimeout
#if (PRO_FBS == ENABLE)
		 && (SCN_MotorDriveMode == SCN_ADF)
#endif
		 && (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP)) {
			SCN_StopMotor();
			SCN_DocumentStatus = SCN_DOC_NO_DOCUMENT;
		}
		CMN_EnableInterrupt();

#if (PRO_FBS == ENABLE)
		/** スキャナモーターをFBS側に切替える(戻す) */
		SCN_SetMotorDrive( SCN_FBS );
#endif
	}

	snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
	rcv_msg(mbxno.SCN_GearBackLashTask, &SCN_Msg);
	wai_tsk(50);	/** Oct.12,1994 */
	wai_tsk(0xFFFF);
}

/*************************************************************************
	module		:[ギアバックラッシュタスク終了処理]
	function	:[
		タスク削除時にコールされる終了処理
		子タスクをdel_tskして、exi_tskする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/08/20]
	author		:[竹内茂樹]
*************************************************************************/
void SCN_GearBackLashExit(void)
{
	/*-------------------------------------------*/
	/** ギア・バック・ラッシュ終了監視タスク消去 */
	/*-------------------------------------------*/
	if (tskno_SCN_WatchGearBackLashTask != 0xffff) {
		del_tsk(&tskno_SCN_WatchGearBackLashTask); /** ギア・バック・ラッシュ終了監視タスク消去 */
	}
	exi_tsk();
}

/** Module Header For CIM-E ********************************************
		module		:	[スキャナー送信時の縮小パターンを決める]
		function	:	[
						・スキャナー送信時の、送信モードが決まった後で、
						　SCN_Openがコールされる前にコールする。
						]
  		return		:	[無し]
		common		:	[
						・SCN_ScannerTxReductionPattern
						]
		condition	:	[]
		comment		:	[
			1996/06/12 s.takeuchi
			ICHOUの内部はメトリック系のため改造
			xx_400_xx_400はミリ/インチ変換なしの意味

			POPLAR_L
			４００ｄｐｉから２００ｄｐｉへの変更を少なくするため
			以下の読み替えを行います。T.Nose 1997/11/11
			SYS_A3_400_TO_B4_400     →     A3/200->B4/200
			SYS_A3_400_TO_A4_400     →     A3/200->A4/200
			SYS_B4_400_TO_A4_400     →     B4/200->A4/200
			SYS_A3_400_TO_A3_400     →     A3/200->A3/200
			SYS_B4_400_TO_B4_400     →     B4/200->B4/200
			SYS_A4_400_TO_A4_400     →     A4/200->A4/200
			その他の縮小パターンを使うことはありません
		]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/8/24]
 		author		:	[川崎真史]
************************************************************************/
void SCN_DecideReductionPattern( void )
{
	if ((SYS_DocBlock.Src.Mode == SYS_GRAY16)
	 || (SYS_DocBlock.Src.Mode == SYS_GRAY16_SEP)
	 || (SYS_DocBlock.Src.Mode == SYS_GRAY64)
	 || (SYS_DocBlock.Src.Mode == SYS_GRAY64_SEP)) {
		switch (SYS_DocBlock.Src.Size) {
		case SYS_DOCUMENT_A3_SIZE:
#if (PRO_CCD == DPI400) /* T.Nose 1997/11/12 */
			if ((SYS_DocBlock.Dst.Mode == SYS_HFINE) && (SYS_DocBlock.ModeMethod == SYS_METRIC))
#endif
#if (PRO_CCD == DPI300) /* T.Nose 1997/11/12 */
			if ((SYS_DocBlock.Dst.Mode == SYS_EFINE) && (SYS_DocBlock.ModeMethod == SYS_METRIC))
#endif
#if (PRO_CCD == DPI200) /* T.Nose 1997/11/12 */
			if (SYS_DocBlock.ModeMethod == SYS_METRIC)
#endif
			{
				if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_A3_SIZE) {
					SCN_ScannerTxReductionPattern = SYS_A3_400_TO_A3_400;
				}
				else if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_B4_SIZE) {
					SCN_ScannerTxReductionPattern = SYS_A3_400_TO_B4_400;
				}
				else {
					SCN_ScannerTxReductionPattern = SYS_A3_400_TO_A4_400;
				}
			}
			else {
				if (SYS_DocBlock.ModeMethod == SYS_INCH) {
					if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_A3_SIZE) {
						SCN_ScannerTxReductionPattern = SYS_A3_400_TO_A3_203;
					}
					else if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_B4_SIZE) {
						SCN_ScannerTxReductionPattern = SYS_A3_400_TO_B4_203;
					}
					else {
						SCN_ScannerTxReductionPattern = SYS_A3_400_TO_A4_203;
					}
				}
				else { /* SYS_METRIC */
					if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_A3_SIZE) {
						SCN_ScannerTxReductionPattern = SYS_A3_400_TO_A3_200;
					}
					else if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_B4_SIZE) {
						SCN_ScannerTxReductionPattern = SYS_A3_400_TO_B4_200;
					}
					else {
						SCN_ScannerTxReductionPattern = SYS_A3_400_TO_A4_200;
					}
				}
			}
			break;
		case SYS_DOCUMENT_B4_SIZE:
#if (PRO_CCD == DPI400) /* T.Nose 1997/11/12 */
			if ((SYS_DocBlock.Dst.Mode == SYS_HFINE) && (SYS_DocBlock.ModeMethod == SYS_METRIC))
#endif
#if (PRO_CCD == DPI300) /* T.Nose 1997/11/12 */
			if ((SYS_DocBlock.Dst.Mode == SYS_EFINE) && (SYS_DocBlock.ModeMethod == SYS_METRIC))
#endif
#if (PRO_CCD == DPI200) /* T.Nose 1997/11/12 */
			if (SYS_DocBlock.ModeMethod == SYS_METRIC)
#endif
			{
				if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_B4_SIZE) {
					SCN_ScannerTxReductionPattern = SYS_B4_400_TO_B4_400;
				}
				else {
					SCN_ScannerTxReductionPattern = SYS_B4_400_TO_A4_400;
				}
			}
			else {
				if (SYS_DocBlock.ModeMethod == SYS_INCH) {
					if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_B4_SIZE) {
						SCN_ScannerTxReductionPattern = SYS_B4_400_TO_B4_203;
					}
					else {
						SCN_ScannerTxReductionPattern = SYS_B4_400_TO_A4_203;
					}
				}
				else { /* SYS_METRIC */
					if (SYS_DocBlock.Dst.Size == SYS_DOCUMENT_B4_SIZE) {
						SCN_ScannerTxReductionPattern = SYS_B4_400_TO_B4_200;
					}
					else {
						SCN_ScannerTxReductionPattern = SYS_B4_400_TO_A4_200;
					}
				}
			}
			break;
		case SYS_DOCUMENT_A4_SIZE:
#if (PRO_CCD == DPI400) /* T.Nose 1997/11/12 */
			if ((SYS_DocBlock.Dst.Mode == SYS_HFINE) && (SYS_DocBlock.ModeMethod == SYS_METRIC))
#endif
#if (PRO_CCD == DPI300) /* T.Nose 1997/11/12 */
			if ((SYS_DocBlock.Dst.Mode == SYS_EFINE) && (SYS_DocBlock.ModeMethod == SYS_METRIC))
#endif
#if (PRO_CCD == DPI200) /* T.Nose 1997/11/12 */
			if (SYS_DocBlock.ModeMethod == SYS_METRIC)
#endif
			{
				SCN_ScannerTxReductionPattern = SYS_A4_400_TO_A4_400;
			}
			else {
				if (SYS_DocBlock.ModeMethod == SYS_INCH) {
					SCN_ScannerTxReductionPattern = SYS_A4_400_TO_A4_203;
				}
				else { /* SYS_METRIC */
					SCN_ScannerTxReductionPattern = SYS_A4_400_TO_A4_200;
				}
			}
			break;
		default:
			break;
		}
	}
	else { /** NORMAL,FINE,SFINE,HFINE */
	}
}
/** Module Header For CIM-E ********************************************
		module		:	[スキャナー・ドライバーの初期化]
		function	:	[]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[パワーＯＮ直後一度だけ実行する]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/4/5]
 		author		:	[川崎真史]
************************************************************************/
void SCN_Init(void)
{
	SCN_MTPC0_Status = 0;
	SCN_MTPC1_Status = 0;
	SCN_MTP0_Status = 0;
	SCN_MTP1_Status = 0;
	SCN_SENSTP_Status = 0;
	SCN_SSTSTP_Status = 0;
	SCN_SCNINT_Status = 0;
	SCN_DS2INTR_Status = 0;
	/* SCN_BUZZ_1K_Status = 0; */
	SCN_MTCNT_Status = 0;
	SCN_SCCNT_Status &= IO_BIT_BUZZER_ENABLE;	/** ブザー鳴動中はブザービットをこかさない。T.Nose 1997/07/10 */
	SCN_INTLNCN_Status = 0;

	SCN_FeedErrorCheckStep = 0;

 	SCN_MotorCurrentStopCounter = 0;			/** モーターの励磁停止を遅らせるカウンター */

	/* SCN_MotorPowerOff();						@** モーターのパワーＯＦＦ */
	SCN_SetMotorCurrent(SCN_CURRENT_POWER_0); 	/** モーターの電流値を０％にセット */
	SCN_SetMotorSpeedIntervalInt(SCN_DISABLE); 	/** モーター速度変更間隔割り込み禁止	INTMTEN-MTCNT */
	SCN_ClearMotorPulseCounter(); 				/** モーター・パルス・カウンター・クリア */
	SCN_SetMotorPulse(SCN_DISABLE); 			/** モーター励磁 OFF MTCLR-MTCNT */
	SCN_SetMotor(SCN_DISABLE); 					/** モーター・ディスエーブル・セット MTEN-MTCNT */

	SCN_SetDS2_ON_Int(SCN_DISABLE); 			/** ＤＳ２　ＯＮ割り込み禁止 */
	SCN_SetDS2_OFF_Int(SCN_DISABLE); 			/** ＤＳ２　ＯＦＦ割り込み禁止 */
	SCN_SetScanStartInt(SCN_DISABLE); 			/** 読み取り先端検出割り込み禁止 */
	SCN_SetScanEndInt(SCN_DISABLE); 			/** 読み取り後端割り込み禁止 */
	SCN_SetMotorSpeedIntervalInt(SCN_DISABLE);	/** モーター速度変更間隔割り込み禁止 */
	SCN_SetLineInt(SCN_DISABLE); 				/** ライン割り込み禁止 */

	/*----------------------------------------------------------*/
	/** 原稿排出後の読み取り先端がずれる件の対応 Aug.14,1994  **/
	/*----------------------------------------------------------*/
	SCN_SetSoftScan(SCN_ENABLE); 				/** Aug.14,1994 ソフト・スキャン許可、ハード・スキャン禁止 */
	SCN_SetStartSoftScan(SCN_DISABLE); 			/** Aug.14,1994 ソフト・スキャン停止 */

	SCN_SetScanDMA(SCN_DISABLE); 				/** スキャン用ＤＭＡ禁止 */

#if (PRO_DOC_IN == ENABLE)
	SCN_SetScanStartStep(SYB_MachineParameter[3]);	/** 読み取り先端ステップ設定、初期ラッチ */
	SCN_SetScanEndStep(SYB_MachineParameter[4]);	/** 読み取り後端ステップ設定、初期ラッチ 1996/05/17 By N.Sakamoto */
#else
	/*	2回目以降のFBS読み取りで先端がずれるので、ここではクリアする意味で必要
	**	実際の読み取り用のステップ数はSCN_Open()時にSCN_SetScanStartAndEndStep()で
	**	まとめてセットする
	**		1996/10/23
	*/
	SCN_SetScanStartStep( 0 );
	SCN_SetScanEndStep( 0 );
#endif

	SCN_ADF_MotorStopRequest = ADF_MOTOR_NO_STOP;	/* 1996/10/29 s.takeuchi */
	SCN_PageChangeTimeOut = FALSE;					/* T.Nose 1997/12/05 */

/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
	SCN_STxLineIntDisableFlag = 0;
#endif
}
/** Module Header For CIM-E ********************************************
		module		:	[モーターの再起動を行う　TBD]
		function	:	[
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/4/26]
 		author		:	[川崎真史]
************************************************************************/
void SCN_RestartMotor(void)
{
	CMN_DisableInterrupt();		/** 割り込み禁止*/

	SCN_MotorCurrentStopCounter = 0;	/** モーターの励磁ＯＦＦは１０ｍｓのタイマー・割り込みで行う */

	if (SCN_DocumentStatus != SCN_DOC_END_OF_SCAN) { /**ページ終了フレームの場合*/
		if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_STOP ) { /** モーター停止中				*/
			SCN_SpeedCheckPoint = 0;	/** ライン割り込み数管理テーブルのポインターをイニシャルにセット */

			/*-----------------------------------------------------------------------------------*/
			/*  デバッグ用に一時的に入れます。 Nov.14,1994                                       */
			/*  次の4行分                                                                       */
			/*-----------------------------------------------------------------------------------*/
			SCN_SetLineStep(SCN_SpeedCheckLine[0]);		/** イニシャルのライン割り込み数をＧ／Ａにセット */
/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
			if (SCN_Control.UseType == IDP_SCANNER_TX) {
#if (0)
				if (SYB_MaintenanceSwitch[MNT_SW_E0] & 0x80) {
					SCN_SetScanDMA( SCN_DISABLE ); /* イメージ転送停止 */
				}
#endif
				SCN_STxLineIntDisableFlag = 0;
			}
#endif
			SCN_SetLineInt(SCN_ENABLE);					/** ライン割り込みを許可 */
			DebugLineInt = SCN_ReadMotorPulseCounter();
			DebugPreLineInt = DebugLineInt;

			SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode];	/** モーター制御用テーブルのポインター確保 */
			SCN_MotorTablePoint = SCN_MotorPointer->InitialSpeed; /** NEW */
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;	/** モーターをスルー・アップするように設定 */

#if (PRO_FBS == ENABLE)
			SCN_IsMirrorMoveEnd = FALSE;	/** ミラー停止フラグをクリア */	/* 1997/02/20 */
			SCN_MirrorStopTimeoutCount = 6000;	/** 60 sec */	/* 1997/03/10 */
#endif

			SCN_SetMotorSpeed(); /** モーターの速度、速度変更間隔設定 */

			SCN_SetMotor(SCN_DISABLE); /** モーター・ディスエーブル */

			SCN_LatchMotorSpeedAndInterval(); /** モーター速度変更間隔、速度初期ラッチ */

			SCN_SetMotorSpeedIntervalInt(SCN_ENABLE); /** モーター速度変更間隔割り込み許可 	INTMTEN-MTCNT */
			SCN_SetMotorPulse(SCN_ENABLE); /** モーター励磁ＯＮ MTCLR-MTCNT */
			/*ICHOUで削除  SCN_SetMotorClockwise(SCN_ENABLE); @** モーター回転方向セットCWXCCW-MTCNT */

			/* SCN_SetMotorCurrent(SCN_CURRENT_POWER_100); @** モーターの電流値を１００％にセット */
			SCN_SetMotorCurrent(SCN_MotorPointer->ThroughUpDownTable[SCN_MotorTablePoint].CurrentPower);

			SCN_SetMotor(SCN_ENABLE); /** モーター・イネーブル・セット MTEN-MTCNT */
		}
		/*----------------------------------------------------------------*/
		/** ＦＸ船チャート読み込み中にモーターが停止する対策 Oct.17,1994  */
		/*----------------------------------------------------------------*/
		else if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_DOWN ) { /** モーター減速中	*/
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP; 	/** モーター加速指示*/
		}
	}
	CMN_EnableInterrupt();	/** Sep.7,1994 割り込み許可*/
}
/** Module Header For CIM-E ********************************************
		module		:	[モーターパワーＯＦＦ]
		function	:	[
						１．電流値０％
						２．速度変更割り込みＯＦＦ
						３．モーターパルスカウンタークリア
						４．モーター励磁（パルス）ＯＦＦ
						５．モーターディスエーブル
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
void SCN_MotorPowerOff(void)
{
	SCN_SetMotorCurrent(SCN_CURRENT_POWER_0); 	/** モーターの電流値を０％にセット */
	SCN_SetMotorSpeedIntervalInt(SCN_DISABLE); 	/** モーター速度変更間隔割り込み禁止	INTMTEN-MTCNT */
	SCN_ClearMotorPulseCounter(); 				/** モーター・パルス・カウンター・クリア */
	SCN_SetMotorPulse(SCN_DISABLE); 			/** モーター励磁 OFF MTCLR-MTCNT */
	SCN_SetMotor(SCN_DISABLE); 					/** モーター・ディスエーブル・セット MTEN-MTCNT */
}
/** Module Header For CIM-E ********************************************
		module		:	[モーターの停止]
		function	:	[
						１．電流値０％
						２．速度変更割り込みＯＦＦ
						３．モーターディスエーブル
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/6/6]
 		author		:	[川崎真史]
************************************************************************/
UWORD DebugStopScanLine = 0; /* Nov.9,1994 */

void SCN_StopMotor(void)
{
	/* SCN_Taskがミラーの移動終了待ちでループする件
	** 呼び本のアドレスを保守スイッチＧ４・５・６・７にセーブする
	** T.Nose 1997/11/03
	*/
	SCN_SaveStopMotor_Address();

/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
	if (SCN_Control.UseType == IDP_SCANNER_TX) {
		if (SYB_MaintenanceSwitch[MNT_SW_E0] & 0x80) {
			SCN_MotorCurrentStopCounter = 0; /* スキャナー送信中のモーター停止では励磁を止めない */
		}
		else {
			SCN_MotorCurrentStopCounter = 10;	/** モーターの励磁ＯＦＦは１０ｍｓのタイマー・割り込みで行う */
		}
	}
	else {
		SCN_MotorCurrentStopCounter = 10;	/** モーターの励磁ＯＦＦは１０ｍｓのタイマー・割り込みで行う */
	}
#else
	SCN_MotorCurrentStopCounter = 10;	/** モーターの励磁ＯＦＦは１０ｍｓのタイマー・割り込みで行う */
#endif

	SCN_SetMotorSpeedIntervalInt(SCN_DISABLE); 	/** モーター速度変更間隔割り込み禁止	INTMTEN-MTCNT */
	SCN_SetMotor(SCN_DISABLE); 					/** モーター・ディスエーブル・セット MTEN-MTCNT */

	DebugStopScanLine = SCN_ReadMotorPulseCounter();

	SCN_SetSoftCTSCAN( SCN_DISABLE );	/** CTSCAN OFF  */
}


/*************************************************************************
	module		:[読取り原稿の先端/後端ステップの設定]
	function	:[
		1.	読取り装置(ADF/FBS)によって、SCANSTARTとSCNENDの
		.	ステップ数を決定する
		2.	コピーの読取りの繰込み量は、先端印字余白分を加える
		3.	それぞれをスキャナG/Aにセットする
		※	1-2相励磁の場合は、各ステップ数を2倍してG/Aにセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ICHOUのADF/FBSでの移動量を区別する
		コピーの時は先端印字余白分、余計に送る
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/06/14]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_SetScanStartAndEndStep(
#if (PRO_FBS == ENABLE)
	UBYTE	exec_mode,		/* ADF / FBS */
#endif
	UBYTE	excite_method,	/* モーター励磁相 */
	UBYTE	is_copy_doc)	/* コピー用の読み取り */
{
	UWORD	start_step;	/* SCANSTART割込みまでのステップ(単位:10step) */
	UWORD	end_step;	/* SCANEND割込みまでのステップ(単位:10step) */

#if (PRO_FBS == ENABLE)
	if (exec_mode == SCN_ADF) {		/** ADF読取り */
#endif
		/**	読取り先端と後端のステップ数を決定する
		**	DS2:ON～SCANSTART
		**	DS2:OFF～SCANEND
		*/
#if (PRO_DOC_IN == ENABLE)
		 /* コピー原稿 */
		if (is_copy_doc == TRUE) {
			if (SCN_Control.ScanPage == 0) { /* １ページ目 */
				if (excite_method == SCN_MOTOR_2_EXCITE) { /* ２相 */
					start_step = (UWORD)SYB_MachineParameter[10];
					end_step = SYB_MachineParameter[4];
				}
				else { /* １－２相 */
					start_step = (UWORD)SYB_MachineParameter[13];
					end_step = (UWORD)SYB_MachineParameter[19];
				}
			}
			else { /* ２ページ目以降 */
				if (excite_method == SCN_MOTOR_2_EXCITE) { /* ２相 */
					start_step = SYB_MachineParameter[3];
					end_step = SYB_MachineParameter[4];
				}
				else { /* １－２相 */
					start_step = (UWORD)SYB_MachineParameter[14];
					end_step = (UWORD)SYB_MachineParameter[19];
				}
			}
		}
		/* 送信原稿 */
		else {
			if (SCN_Control.ScanPage == 0) { /* １ページ目 */
				if (excite_method == SCN_MOTOR_2_EXCITE) { /* ２相 */
					start_step = (UWORD)SYB_MachineParameter[11];
					end_step = SYB_MachineParameter[4];
				}
				else { /* １－２相 */
					start_step = (UWORD)SYB_MachineParameter[17];
					end_step = (UWORD)SYB_MachineParameter[19];
				}
			}
			else { /* ２ページ目以降 */
				if (excite_method == SCN_MOTOR_2_EXCITE) { /* ２相 */
					start_step = (UWORD)SYB_MachineParameter[12];
					end_step = SYB_MachineParameter[4];
				}
				else { /* １－２相 */
					start_step = (UWORD)SYB_MachineParameter[18];
					end_step = (UWORD)SYB_MachineParameter[19];
				}
			}
		}
#else
		start_step = (UWORD)SYB_MachineParameter[3];
		end_step = (UWORD)SYB_MachineParameter[4];
#endif

		/* 後端欠け対策  1997/05/09
		*  ADFでは搬送速度によってDS2 ON/OFFタイミングが異なるため
		*  モードによって先後端の余白が異なるので、
		*  先後端ステップはSFineを基準として補正する
		*/
		if (SCN_ModeSw == SYS_NORMAL) {
			start_step += (UWORD)SCN_ADF_NormalTopAdjustStep();
			end_step += (UWORD)SCN_ADF_NormalEndAdjustStep();
		}
		else if (SCN_ModeSw == SYS_FINE) {
			start_step += (UWORD)SCN_ADF_FineTopAdjustStep();
			end_step += (UWORD)SCN_ADF_FineEndAdjustStep();
		}

#if (PRO_FBS == ENABLE)
	}
	else {		/** FBS読取り */
		/**	読取り先端と後端のステップ数を決定する
		**	HS:OFF～SCANSTART	FBS先端までの距離＋先端余白
		**		※先端余白(mm)はステップ数(15.4line/mm)に変換する
		**	FBSではSCANEND割込みはかからないので後端検出はエンコードタスクで行う
		**	余白0mmでも先端の影を読まないように1mm分足す  1997/02/04
		*/
		start_step = (UWORD)(SYB_MachineParameter[10] * 10);		/* HS～FBS先端 */
		start_step += (UWORD)(CHK_UNI_FBS_AdjustStep() * 10);		/* 補正ステップ */
		start_step += (UWORD)(((CHK_UNI_FBS_TopMargin() + 1) * 154) / 10);	/* FBS先端余白 */
		start_step /= 10;								/* 10 line 単位に変換する */
		end_step = 0;	/* 使わないのでクリアしておく */
	}
#endif

	/** コピー読み取りの場合は、更に先端印字余白分を加える */
	if (is_copy_doc) {
		start_step += (UWORD)CHK_UNI_CopyDocTopSkipLine();
	}

#if (PRO_DOC_IN == DISABLE)
	/* 1-2相励磁の場合は、各ステップ数を2倍する
	** ANZU_L(ENABLE)は１－２相専用のステップ値を機器パラメータに個別に持っています。
	** T.Nose 1997/10/02
	*/
	if (excite_method == SCN_MOTOR_1_2_EXCITE) {
		start_step *= 2;
		end_step *= 2;
	}
#endif

	/** 読み取り先端と後端ステップ設定、初期ラッチ */
	SCN_SetScanStartStep( start_step );
	SCN_SetScanEndStep( end_step );
}


/*************************************************************************
	module		:[読み取りパラメータをIDP301-DIPPにセットする]
	function	:[
		SCN_ModeSwとで指定された読み取りモードによって、
		IDP301のDIPPモジュールを設定する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		読み取りモードはSCN_ModeSwではなく
		SCN_Control.DocumentModeを見る
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1996/11/01]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	SCN_DIPP_PeakLimit = 0;			/* R0F */
UBYTE	SCN_DIPP_PeakN_Step = 0;		/* R10 */
UBYTE	SCN_DIPP_BlackBaseVvoltage = 0;	/* R11 */
UBYTE	SCN_DIPP_Gamma1 = 0;			/* R12 */
UBYTE	SCN_DIPP_Gamma2 = 0;			/* R13 */
UBYTE	SCN_DIPP_BlackLevel = 0;		/* R14 */
void	SCN_SetDIPP_Parameter( void )
{
	UBYTE	tmpreg;
	UBYTE	* data_ptr;
	UBYTE	is_gosakakusan;	/* 誤差拡散パラメータの個別処理用  1997/02/28 */
	UBYTE	peak_data;		/* 中間調のピーク値補正用  1997/04/10 */
	BYTE	peak_offset;	/* 中間調のピーク値補正用  1997/04/10 */
	UBYTE	doc_item;

	/** 中間調モード設定の場合、ピーク値検出回路停止(ピーク値固定)*/
	if ((SCN_Control.DocumentMode == SYS_GRAY16)
	 || (SCN_Control.DocumentMode == SYS_GRAY16_SEP)
	 || (SCN_Control.DocumentMode == SYS_GRAY32)
	 || (SCN_Control.DocumentMode == SYS_GRAY32_SEP)
	 || (SCN_Control.DocumentMode == SYS_GRAY64)
	 || (SCN_Control.DocumentMode == SYS_GRAY64_SEP)
	 || (SCN_Control.DocumentMode == SYS_GRAY128)
	 || (SCN_Control.DocumentMode == SYS_GRAY128_SEP)) {
		DIPP_SetBitPEAKE( IDP_BIT_OFF );
	}
	else {
		DIPP_SetBitPEAKE( IDP_BIT_ON );
	}

	DIPP_ChangeDocumentSize();		/** PAPWの再設定を行います(B4 or A4) */

	/* ICHOU薄読み対策(全レジスタをセット後にDIPPST-ONする)
	** DIPP_SetBitDIPPST( IDP_BIT_ON );
	*/


	/** 読み取りモードによって、機器パラメータの先頭アドレスを決定する */
	switch (SCN_Control.DocumentMode) {
	case SYS_NORMAL:
		data_ptr = &SYB_MachineParameter[20];		/* ノーマル */
		break;
	case SYS_FINE:
	case SYS_EFINE:	/* Eファイン */
		data_ptr = &SYB_MachineParameter[30];		/* ファイン */
		break;
	case SYS_SFINE:
	case SYS_HFINE:
	case SYS_E_HFINE:
		data_ptr = &SYB_MachineParameter[40];		/* S/Hファイン */
		break;
	case SYS_GRAY64:			/* 中間調 */
	case SYS_GRAY64_SEP:
		/* 原稿種類を判別し、IDPパラメータのポインタと誤差拡散フラグをセット */
		if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
			if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
			  || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {	/* コピー原稿の蓄積 */
				doc_item = SCN_MEMCOPY_DOC;
			}
			else {
				doc_item = SCN_MEMTX_DOC;
			}
		}
		else {
			doc_item = SCN_SCNTX_DOC;
		}
		if (IsGrayPatternDither(doc_item) == TRUE) {
			data_ptr = &SYB_MachineParameter[50];	/* ディザ */
			is_gosakakusan = FALSE;
		}
		else {
			data_ptr = &SYB_MachineParameter[60];	/* 誤差拡散 */
			is_gosakakusan = TRUE;
		}
		break;
	default:
		break;
	}

	/** IDP301のDIPPのレジスタ(R0F～R14)の値を機器パラメータから読む */
	SCN_DIPP_PeakLimit = *data_ptr++;			/* R0F : 機器パラ[x0] */
	SCN_DIPP_PeakN_Step = *data_ptr++;			/* R10 : 機器パラ[x1] */
	SCN_DIPP_BlackBaseVvoltage = *data_ptr++;	/* R11 : 機器パラ[x2] */
	SCN_DIPP_Gamma1 = *data_ptr++;				/* R12 : 機器パラ[x3] */
	SCN_DIPP_Gamma2 = *data_ptr++;				/* R13 : 機器パラ[x4] */
	SCN_DIPP_BlackLevel = *data_ptr++;			/* R14 : 機器パラ[x5] */

	/** 中間調の場合は、濃度によってγ補正1/2の設定値を補正する */
	if ((SCN_Control.DocumentMode == SYS_GRAY16)
	 || (SCN_Control.DocumentMode == SYS_GRAY16_SEP)
	 || (SCN_Control.DocumentMode == SYS_GRAY64)
	 || (SCN_Control.DocumentMode == SYS_GRAY64_SEP)) {

#if (PRO_CCD == DPI200) /* POPLAR_L のみ T.Nose 1998/01/27 */
		switch (SCN_Control.DocumentDensity) {
		case SYS_NORMAL_DENSITY:
			/* ”普通”濃度の場合、γ１・γ２補正は変更しない */
			break;
		case SYS_LIGHT_DENSITY:
			if (is_gosakakusan) {	/** 誤差拡散 */
				SCN_DIPP_Gamma1 = SYB_MachineParameter[90];
				SCN_DIPP_Gamma2 = SYB_MachineParameter[91];
			}
			else {		/** ディザ */
				SCN_DIPP_Gamma1 = SYB_MachineParameter[85];
				SCN_DIPP_Gamma2 = SYB_MachineParameter[86];
			}
			break;
		case SYS_DARK_DENSITY:
			if (is_gosakakusan) {	/** 誤差拡散 */
				SCN_DIPP_Gamma1 = SYB_MachineParameter[92];
				SCN_DIPP_Gamma2 = SYB_MachineParameter[93];
			}
			else {		/** ディザ */
				SCN_DIPP_Gamma1 = SYB_MachineParameter[87];
				SCN_DIPP_Gamma2 = SYB_MachineParameter[88];
			}
			break;
		default:
			/* POPLAR_Lでは有り得ない */
			break;
		}

		/* POPLAR_L 画質デバッグ */
		if (SYB_MaintenanceSwitch[MNT_SW_A8] & 0x01) {
			DIPP_SetBitPEAKE( IDP_BIT_ON ); /* ピーク値追従ＯＮ */
		}
#else /* PRO_CCD == DPI200 else */
 #if (PRO_KEYPANEL == PANEL_POPLAR_H)		/* ポプラ＿Ｈタイプ */

#if (0)
** 		/* 誤差拡散のほうの濃度別調整が抜けていました。
** 		** by O.Kimoto 1998/04/20
** 		*/
** 		/* 谷＠電子設計の方から、ＰＯＰＬＡＲ＿Ｈのディザの濃淡の調整方法を
** 		** ＰＯＰＬＡＲ＿Ｌに合わせてほしいとの依頼が会ったので、変更します。
** 		** By O.Kimoto 1998/04/06
** 		*/
** 		switch (SCN_Control.DocumentDensity) {
** 		case SYS_NORMAL_DENSITY:
** 			/* ”普通”濃度の場合、γ１・γ２補正は変更しない */
** 			break;
** 		case SYS_LIGHT_DENSITY:
** 			if (!is_gosakakusan) {		/** ディザ */
** 				SCN_DIPP_Gamma1 = SYB_MachineParameter[85];
** 				SCN_DIPP_Gamma2 = SYB_MachineParameter[86];
** 			}
** 			break;
** 		case SYS_DARK_DENSITY:
** 			if (!is_gosakakusan) {		/** ディザ */
** 				SCN_DIPP_Gamma1 = SYB_MachineParameter[87];
** 				SCN_DIPP_Gamma2 = SYB_MachineParameter[88];
** 			}
** 			break;
** 		default:
** 			break;
** 		}
** 
** 		/* POPLAR_L 画質デバッグ */
** 		if (SYB_MaintenanceSwitch[MNT_SW_A8] & 0x01) {
** 			DIPP_SetBitPEAKE( IDP_BIT_ON ); /* ピーク値追従ＯＮ */
** 		}
#else
		/* 谷＠電子設計の方から、ＰＯＰＬＡＲ＿Ｈのディザの濃淡の調整方法を
		** ＰＯＰＬＡＲ＿Ｌに合わせてほしいとの依頼が会ったので、変更します。
		** By O.Kimoto 1998/04/06
		*/
		if (is_gosakakusan) {	/** 誤差拡散 */
			/* 誤差拡散の場合は、機器パラ(J0～J4)の値をγ補正２の設定値とする */
			SCN_DIPP_Gamma2 = SYB_MachineParameter[90 + SCN_Control.DocumentDensity];

			/* 誤差拡散のピーク値Nステップ(DIPP R10)をプログラム中で個別設定  1997/02/28 */
			if ((SCN_Control.DocumentDensity == SYS_DARK_DENSITY)
			||	(SCN_Control.DocumentDensity == SYS_DARK_NORMAL_DENSITY)) {
				SCN_DIPP_PeakN_Step = 0x08;
			}
		}
		else {		/** ディザ */
			switch (SCN_Control.DocumentDensity) {
			case SYS_NORMAL_DENSITY:
				/* ”普通”濃度の場合、γ１・γ２補正は変更しない */
				break;
			case SYS_LIGHT_DENSITY:
				SCN_DIPP_Gamma1 = SYB_MachineParameter[85];
				SCN_DIPP_Gamma2 = SYB_MachineParameter[86];
				break;
			case SYS_DARK_DENSITY:
				SCN_DIPP_Gamma1 = SYB_MachineParameter[87];
				SCN_DIPP_Gamma2 = SYB_MachineParameter[88];
				break;
			default:
				break;
			}

			/* POPLAR_L 画質デバッグ */
			if (SYB_MaintenanceSwitch[MNT_SW_A8] & 0x01) {
				DIPP_SetBitPEAKE( IDP_BIT_ON ); /* ピーク値追従ＯＮ */
			}
		}
#endif
 #else
		if (is_gosakakusan) {	/** 誤差拡散 */
			/* 誤差拡散の場合は、機器パラ(J0～J4)の値をγ補正２の設定値とする */
			SCN_DIPP_Gamma2 = SYB_MachineParameter[90 + SCN_Control.DocumentDensity];

			/* 誤差拡散のピーク値Nステップ(DIPP R10)をプログラム中で個別設定  1997/02/28 */
			if ((SCN_Control.DocumentDensity == SYS_DARK_DENSITY)
			||	(SCN_Control.DocumentDensity == SYS_DARK_NORMAL_DENSITY)) {
				SCN_DIPP_PeakN_Step = 0x08;
			}
		}
		else {		/** ディザ */
			/* ディザの場合は、機器パラ(I5～I9)の値をγ補正１の設定値とする */
			SCN_DIPP_Gamma1 = SYB_MachineParameter[85 + SCN_Control.DocumentDensity];
		}
 #endif
#endif
	}

	/** DIPPオートインクリメントネゲート */
	DIPP_AutoIncrementNegate();	/* 1997/02/24 */

	/*
	**	R0F : ピーク値リミットをDIPPに設定する
	*/
	IdpRegisterStatus.DIPP_AR = 0x0F;
	IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
	IdpRegisterStatus.DIPP_CR = SCN_DIPP_PeakLimit;
	IdpOutputByte( DIPP_CR_PORT, IdpRegisterStatus.DIPP_CR );

	/*
	**	R10 : ピーク値nステップ数をDIPPに設定する
	*/
	IdpRegisterStatus.DIPP_AR = 0x10;
	IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
	IdpRegisterStatus.DIPP_CR = SCN_DIPP_PeakN_Step;
	IdpOutputByte( DIPP_CR_PORT, IdpRegisterStatus.DIPP_CR );

	/*
	**	R11 : 黒側基準電位をDIPPに設定する
	*/
	IdpRegisterStatus.DIPP_AR = 0x11;
	IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
	IdpRegisterStatus.DIPP_CR = SCN_DIPP_BlackBaseVvoltage;
	IdpOutputByte( DIPP_CR_PORT, IdpRegisterStatus.DIPP_CR );

	/*
	**	R12 / R13 : γ補正1/2をDIPPに設定する
	*/
	IdpRegisterStatus.DIPP_AR = 0x12;
	IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
	IdpRegisterStatus.DIPP_CR = SCN_DIPP_Gamma1;
	IdpOutputByte( DIPP_CR_PORT, IdpRegisterStatus.DIPP_CR );
	IdpRegisterStatus.DIPP_AR = 0x13;
	IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
	IdpRegisterStatus.DIPP_CR = SCN_DIPP_Gamma2;
	IdpOutputByte( DIPP_CR_PORT, IdpRegisterStatus.DIPP_CR );

	/*
	**	R14 : 黒レベル検出をDIPPに設定する
	*/
	IdpRegisterStatus.DIPP_AR = 0x14;
	IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
	IdpRegisterStatus.DIPP_CR = SCN_DIPP_BlackLevel;
	IdpOutputByte( DIPP_CR_PORT, IdpRegisterStatus.DIPP_CR );

	/*
	**	ピーク値NステップシフトイネーブルビットをＯＮします
	*/
	IdpRegisterStatus.DIPP_AR = 0x03;
	IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
	tmpreg = IdpInputByte( DIPP_CR_PORT );
	tmpreg |= DIPP_CR_R03_PHNE;
	IdpRegisterStatus.DIPP_AR = 0x03;
	IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
	IdpRegisterStatus.DIPP_CR = tmpreg;
	IdpOutputByte( DIPP_CR_PORT, IdpRegisterStatus.DIPP_CR );


	/*	読み取り開始直前にピーク値をセットする必要があります('94.06/22)
	**	(これを行わないとピーク値が吹っ飛びます)
	*/
	/** 中間調用のピーク値を機器パラJ8で補正(二値はそのまま)してセット */	/* 変更  1997/04/10 */
	if ((SCN_Control.DocumentMode >= SYS_GRAY16)
	 || (SCN_Control.DocumentMode == SYS_GRAY16_SEP)
	 || (SCN_Control.DocumentMode == SYS_GRAY32)
	 || (SCN_Control.DocumentMode == SYS_GRAY32_SEP)
	 || (SCN_Control.DocumentMode == SYS_GRAY64)
	 || (SCN_Control.DocumentMode == SYS_GRAY64_SEP)
	 || (SCN_Control.DocumentMode == SYS_GRAY128)
	 || (SCN_Control.DocumentMode == SYS_GRAY128_SEP)) {
		peak_offset = (BYTE)(SYB_MachineParameter[98] & 0x7F);
		if (SYB_MachineParameter[98] & 0x80) {
			peak_offset *= -1;
		}
	}
	else {
		peak_offset = 0;
	}
	peak_data = SYB_PeakData + peak_offset;
	DIPP_SetBitMPUAE( IDP_BIT_ON );
	IdpRegisterStatus.DIPP_AR = 0x0d;
	IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
	IdpRegisterStatus.DIPP_CR = peak_data;
	IdpOutputByte( DIPP_CR_PORT, IdpRegisterStatus.DIPP_CR );
	DIPP_SetBitMPUAE( IDP_BIT_OFF );

	/* ICHOU薄読み対策(DIPPの全レジスタをセット後にDIPPST-ONする) */
	DIPP_SetBitDIPPST( IDP_BIT_ON );
}


/*************************************************************************
	module		:[読み取りモードの取得]
	function	:[
		コピーかFAX原稿かを引数で区別して読み取りモードを返す
	]
	return		:[
		読み取りモード(sysdoc.h参照)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1997/01/07]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	SCN_GetScanMode(
	UBYTE	is_copy_file)
{
#if (PRO_COPY_FAX_MODE == ENABLE) /* コピー／ＦＡＸ切り替えあり */
	if (is_copy_file) { /* コピーモードなら */
		return (SYB_CopyModeSw);
	}
	else { /* ＦＡＸモードなら */
		return (SYB_ModeSw);
	}
#else
	return(SYB_ModeSw);
#endif
}


/*************************************************************************
	module		:[読み取り濃度の取得]
	function	:[
		コピーかFAX原稿かを引数で区別して読み取り濃度を返す
	]
	return		:[
		読み取り濃度(sysdoc.h参照)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/03/24]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE	SCN_GetScanDensity(
	UBYTE	is_copy_file)
{
#if (PRO_COPY_FAX_MODE == ENABLE) /* コピー／ＦＡＸ切り替えあり */
	if (is_copy_file) { /* コピーモードなら */
		return (SYB_CopyDensitySw);
	}
	else { /* ＦＡＸモードなら */
		return (SYB_DensitySw);
	}
#else
	return(SYB_DensitySw);
#endif
}


/*************************************************************************
	module		:[読み取りマスク有無の取得]
	function	:[
		読み取り原稿の読み取り画素(全画素/一部)と
		マスクするしないを決定する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1997/02/12]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_SetScanDocumentMask( void )
{
#if (PRO_FBS == ENABLE)
	if (SYS_ScannerExecMode == SCN_ADF) {
#endif
		SCN_FullWidthScan = 1;
		if (CHK_DocumentWidthFull()) { /**	読み取り左右白マスク無し */
			SCN_WhiteMaskFlag = 0;
		}
		else { /** 白マスク有り */
			SCN_WhiteMaskFlag = 1;
		}
#if (PRO_FBS == ENABLE)
	}
	else {	/* ICHOUのFBS読取りの場合は、FBS用のDIPPの設定を指定する */
		if (SYS_ScanDocSizeTable[SCN_RegularDocumentSize].IsFullScan) {	/* レター/リーガルなど */
			SCN_FullWidthScan = 1;
			SCN_WhiteMaskFlag = 0;
		}
		else {	/* その他の原稿 */
			SCN_FullWidthScan = 0;
			SCN_WhiteMaskFlag = 1;	/* ずらして読むため必ずマスクする */
		}
	}
#endif
}


/*************************************************************************
	module		:[DS2バウンス収束ステップの計算]
	function	:[
		読み取りの最高速度のパルスレートと
		DS2のバウンス収束時間から
		バウンスの収束する最大ステップを求める
	]
	return		:[
		ステップ
	]
	common		:[]
	condition	:[]
	comment		:[
		ICHOUの読み取り中のDS2バウンス対策
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1997/04/05]
	author		:[竹内茂樹]
*************************************************************************/
UWORD	SCN_GetMaxBounceStep( void )
{
	UWORD	pulse_rate;	/* 最高速度(pps) */
	UWORD	step;		/* バウンス収束最大ステップ(step) */
	UBYTE	v_mode;		/* 読み取りモード */

	/** 読み取り時のモーターテーブルを取得 */
	v_mode = SCN_VerticalMode;
	switch (v_mode) {
	case	SCN_NORMAL_FEED:
		v_mode = SCN_NORMAL;
		break;
	case	SCN_FINE_FEED:
		v_mode = SCN_FINE;
		break;
	case	SCN_SFINE_FEED:
	default:
		v_mode = SCN_SFINE;
		break;
	}

	/* パルスレート(pps)＝(3000000)／(G/Aへの設定値) */
	pulse_rate = (UWORD)(3000000 / SCN_MotorTable[v_mode].ThroughUpDownTable[SCN_MotorTable[v_mode].TopSpeed].PPS);

	/* 収束ステップ数＝パルスレート(pps)×収束時間(ms)／1000 */
	step = (pulse_rate * SYB_MaintenanceSwitch[MNT_SW_C8]) / 1000;

	return (step);
}


/*************************************************************************
	module		:[原稿読み取り中のチェック]
	function	:[
	]
	return		:[
		TRUE :読み取り中
		FALSE:読み取り中でない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/05/15]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE SCN_IsDocumentScanning(void)
{
	/* ADF読み取り中のチェック */
	if ((SCN_MirrorCarriageStatus == MIRROR_ADF_READY)
	 && ((SCN_DocumentStatus == SCN_DOC_ADF_1ST_PAGE)
	  || (SCN_DocumentStatus == SCN_DOC_READY)
	  || (SCN_DocumentStatus == SCN_DOC_IN_SCANNING)
	  || (SCN_DocumentStatus == SCN_DOC_DS2_OFF))) {
		return(TRUE);
	}

	/* FBS読み取り中のチェック */
	if (SCN_MirrorCarriageStatus == MIRROR_FBS_SCANNING) {
		return(TRUE);
	}

	return(FALSE); /* 原稿読み取り中でない */
}


/*************************************************************************
	module		:[原稿符号化方式の獲得]
	function	:[
	]
	return		:[
		SYS_IMAGE_DATA	   0
		SYS_MH_CODE		   1
		SYS_MR_CODE		   2
		SYS_MMR_CODE	   3
		SYS_MG3_CODE	   4	松下ｺｰﾃﾞｯｸ MN86063 & MN86064 のみ使用
		SYS_JBIG_CODE	   5	松下ｺｰﾃﾞｯｸ MN86064のみ使用
	]
	common		:[
		Cl1_Code が確定していること
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/07/10]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE SCN_GetDocumentStoreCode(UBYTE mode, UBYTE item)
{
#if (PRO_FIP == ENABLE)
	if (item == SYS_MEM_FIP_FILE) { /* ＦＩＰはＭＨのみサポート */
		return(SYS_MH_CODE);
	}
#endif
#if (PRO_CLASS1 == ENABLE)
	if (item == SYS_MEM_CLASS1_TX_FILE) {
		return(CL1_Code);
	}
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	/*　ｲﾝﾀｰﾈｯﾄFAXにてMinimum Setの時は原稿蓄積時に強制的にMHにします　*/
	if (SYS_DocumentStoreItem == SYS_MEM_MAIL_TX_FILE) {
		/* InternetFaxではMRはない　*/
		/*if (SYS_INF_MinimumSetRequest == TRUE) { 1998/05/23 Eguchi*/
		if (CHK_UNI_INF_MinimumSetAvail()) { /*1998/05/23 Eguchi*/
			return(SYS_MH_CODE);
		}
		else {
			return(SYS_MMR_CODE);
		}
	}
#endif
	switch (mode) {
	case	SYS_NORMAL:
	case	SYS_FINE:
	case	SYS_SFINE:
	case	SYS_HFINE:
	case	SYS_EFINE:
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
		if ((CMN_CheckEncodeMG3_Enable(item) == FALSE)
		 && ((SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD) > SYS_MMR_CODE)) {
			/* ＭＧ３・ＪＢＩＧなど、ソフトコーデックが対応していない蓄積符号化方式が
			** メンテナンススイッチに設定されていたら、強制的にＭＭＲを蓄積符号化方式とする。
			*/
			return(SYS_MMR_CODE);
		}
		else {
			return((UBYTE)(SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD));
		}
#else /* 通信コーデックがハード（MN86063,86064）なら */

 #if (PRO_PANEL == KANJI)	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
		if ((CMN_CheckEncodeMG3_Enable(item) == FALSE)
		 && (((SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD_GRAY) >> 3) > SYS_MMR_CODE)) {
			/* ＭＧ３・ＪＢＩＧなど、ソフトコーデックが対応していない蓄積符号化方式が
			** メンテナンススイッチに設定されていたら、強制的にＭＭＲを蓄積符号化方式とする。
			*/
			return(SYS_MMR_CODE);
		}
		else {
			return((UBYTE)((SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD_GRAY)>>3));
		}
 #else
		return((UBYTE)(SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD));
 #endif

#endif
		break;
	default:			/* その他(中間調) */
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
		if ((CMN_CheckEncodeMG3_Enable(item) == FALSE)
		 && (((SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD_GRAY) >> 3) > SYS_MMR_CODE)) {
			/* ＭＧ３・ＪＢＩＧなど、ソフトコーデックが対応していない蓄積符号化方式が
			** メンテナンススイッチに設定されていたら、強制的にＭＭＲを蓄積符号化方式とする。
			*/
			return(SYS_MMR_CODE);
		}
		else {
			return((UBYTE)((SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD_GRAY)>>3));
		}
#else /* 通信コーデックがハード（MN86063,86064）なら */

 #if (PRO_PANEL == KANJI)	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
		if ((CMN_CheckEncodeMG3_Enable(item) == FALSE)
		 && (((SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD_GRAY) >> 3) > SYS_MMR_CODE)) {
			/* ＭＧ３・ＪＢＩＧなど、ソフトコーデックが対応していない蓄積符号化方式が
			** メンテナンススイッチに設定されていたら、強制的にＭＭＲを蓄積符号化方式とする。
			*/
			return(SYS_MMR_CODE);
		}
		else {
			return((UBYTE)((SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD_GRAY)>>3));
		}
 #else
		return((UBYTE)((SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD_GRAY)>>3));
 #endif
#endif
		break;
	}
}


/*************************************************************************
	module		:[細線保持モードの獲得]
	function	:[
	]
	return		:[
		細線保持不要			0
		主走査細線保持			1
		副走査細線保持			2	松下ｺｰﾃﾞｯｸ MN86064のみ
		主走査副走査細線保持	3	松下ｺｰﾃﾞｯｸ MN86064のみ
	]
	common		:[]
	condition	:[
		SCN_ModeSwが確定していること
	]
	comment		:[
		CDC_EncodePageTaskからコールされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/07/22]
	author		:[小谷正樹]
*************************************************************************/
UWORD SCN_GetArithmeticReduction(void)
{
	UWORD result;

	result = 0;
#if (PRO_CCD == DPI200)	/**ＣＣＤ解像度別の処理による*/
	return (0);	/*主走査縮小はない*/
#endif

#if (PRO_PRN_CODEC_TYPE == MN86063)
	/* Ａ３縮小コピー間に合わない件
	** プリンタコーデックがＭＮ８６０６３の機種(POPLAR_B/H)
	** ４００ｄｐｉ、Ａ３原稿のコピー蓄積はスキャナーＣＯＤＥＣで縮小して蓄積する
	** 縮小率はコピーファイルに設定されている縮小率を使用する
	** 上記変更に付随して
	** スキャナコーデックで縮小するときは無条件で細線保持モードＯＮ
	** 追加 T.Nose 1998/03/30
	*/
	if ((SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10)
	 && ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE))
	 && (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE)
	 && (SCN_DocumentReduction < 100)) {
		return(1);
	}
#endif

	switch (SCN_ModeSw) { /** 読み取りモードをチェック */
	case SYS_NORMAL:	/* 普通		200dpi:8 dot/m	100dpi:3.85本/l */
		result = 1;
		break;
	case SYS_FINE:		/* 高画質	200dpi:8 dot/m	200dpi:7.7 本/l */
		result = 1;
		break;
	case SYS_GRAY16:	/* 16階調	200dpi:8 dot/m	200dpi:7.7 本/l */
	case SYS_GRAY16_SEP:/* 16階調	200dpi:8 dot/m	200dpi:7.7 本/l */
	case SYS_GRAY32:	/* 32階調	200dpi:8 dot/m	200dpi:7.7 本/l */
	case SYS_GRAY32_SEP:/* 32階調	200dpi:8 dot/m	200dpi:7.7 本/l */
	case SYS_GRAY64:	/* 64階調	200dpi:8 dot/m	200dpi:7.7 本/l */
	case SYS_GRAY64_SEP:/* 64階調	200dpi:8 dot/m	200dpi:7.7 本/l */
	case SYS_GRAY128:	/* 128階調	200dpi:8 dot/m	200dpi:7.7 本/l */
	case SYS_GRAY128_SEP:/* 128階調	200dpi:8 dot/m	200dpi:7.7 本/l */
		if (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) {
			result = 0;
		}
		else {
			result = 1;
		}
		break;
	case SYS_SFINE:		/* 超高画質				200dpi:8 dot/m	400dpi:15.5本/l */
		result = 1;
		break;
	case SYS_HFINE:		/* 超々高画質			400dpi:16dot/m	400dpi:15.5本/l */
		result = 0;
		break;
	default:
		break;
	}
	return (result);
}


/*************************************************************************
	module		:[1ラインのイメージ画素数の獲得]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[
		SYS_DocumentScanSizeが確定していること
	]
	comment		:[
		CDC_EncodePageTaskからコールされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/07/22]
	author		:[小谷正樹]
*************************************************************************/
UWORD SCN_GetEncodePageSize(UWORD h_resolution)
{
	UWORD line_dots;
	UBYTE scan_size;

	/* スキャナの用途によって原稿サイズの参照個所を変える 1998/11/13 T.Nose */
	if (SCN_Control.UseType == IDP_SCANNER_TX) {
		scan_size = SYS_DocBlock.Src.Size;
	}
	else if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
		scan_size = SYS_DocumentScanSize;
	}

	/*************************/
	/**原稿サイズ別に決定する*/
	/*************************/
	switch (h_resolution) {	/**コーデック解像度別の処理による*/
	case 400:
		switch (scan_size) {	/**解像度（主走査）が４００ｄｐｉの時の画素数を決める*/
		case SYS_DOCUMENT_A3_SIZE:
			line_dots = 304 * 16;	/**１ライン４８６４ドット*/
			break;
		case SYS_DOCUMENT_B4_SIZE:
			line_dots = 256 * 16;	/**１ライン４０９６ドット*/
			break;
		case SYS_DOCUMENT_A4_SIZE:
			line_dots = 216 * 16;	/**１ライン３４５６ドット*/
			break;
		default:	/**ありえないパス*/
			line_dots = 216 * 16;
			break;
		}
		break;
	case 200:
		switch (scan_size) {	/**解像度（主走査）が２００ｄｐｉの時の画素数を決める*/
		case SYS_DOCUMENT_A3_SIZE:
			line_dots = 304 * 8;	/**１ライン２４３２ドット*/
			break;
		case SYS_DOCUMENT_B4_SIZE:
			line_dots = 256 * 8;	/**１ライン２０４８ドット*/
			break;
		case SYS_DOCUMENT_A4_SIZE:
			line_dots = 216 * 8;	/**１ライン１７２８ドット*/
			break;
		default:	/**ありえないパス*/
			line_dots = 216 * 8;
			break;
		}
		break;
	case 300:
		switch (scan_size) {	/**解像度（主走査）が３００ｄｐｉの時の画素数を決める*/
		case SYS_DOCUMENT_A3_SIZE:
			line_dots = 304 * 12;	/**１ライン３６４８ドット*/
			break;
		case SYS_DOCUMENT_B4_SIZE:
			line_dots = 256 * 12;	/**１ライン３０７２ドット*/
			break;
		case SYS_DOCUMENT_A4_SIZE:
			line_dots = 216 * 12;	/**１ライン２５９２ドット*/
			break;
		default:	/**ありえないパス*/
			line_dots = 216 * 12;
			break;
		}
		break;
	default:	/**ありえないパス*/
		line_dots = 216 * 8;	/**１ライン１７２８ドット*/
		break;
	}
	return (line_dots);
}


/*************************************************************************
	module		:[1ラインの出力イメージ画素数の獲得]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[
		SYS_DocumentScanSizeが確定していること
	]
	comment		:[
		CDC_EncodePageTaskからコールされる
		Ａ３縮小コピー間に合わない件
		４００ｄｐｉ、Ａ３原稿のコピー蓄積は
		スキャナーＣＯＤＥＣでＢ４に縮小して蓄積する
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/09/24]
	author		:[野瀬敏弘]
*************************************************************************/
UWORD SCN_GetEncodeOutputSize(UWORD h_resolution)
{
	UWORD line_dots;

	/*************************/
	/**原稿サイズ別に決定する*/
	/*************************/
	switch (h_resolution) {	/**コーデック解像度別の処理による*/
	case 400:
		switch (SYS_DocumentScanSize) {	/**解像度（主走査）が４００ｄｐｉの時の画素数を決める*/
		case SYS_DOCUMENT_A3_SIZE:
			if (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10) {
				switch (SCN_GetCopyDocStoreSize()) {
				case SYS_DOCUMENT_A3_SIZE:
					line_dots = 304 * 16;
					break;
				case SYS_DOCUMENT_B4_SIZE:
					line_dots = 256 * 16;
					break;
				case SYS_DOCUMENT_A4_SIZE:
					line_dots = 216 * 16;
					break;
				default:
					line_dots = 216 * 16;
					break;
				}
			}
			else {
				line_dots = 304 * 16;	/**１ライン４８６４ドット*/
			}
			break;
		case SYS_DOCUMENT_B4_SIZE:
			line_dots = 256 * 16;	/**１ライン４０９６ドット*/
			break;
		case SYS_DOCUMENT_A4_SIZE:
			line_dots = 216 * 16;	/**１ライン３４５６ドット*/
			break;
		default:	/**ありえないパス*/
			line_dots = 216 * 16;
			break;
		}
		break;
	case 200:
		switch (SYS_DocumentScanSize) {	/**解像度（主走査）が２００ｄｐｉの時の画素数を決める*/
		case SYS_DOCUMENT_A3_SIZE:
			if (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10) {
				switch (SCN_GetCopyDocStoreSize()) {
				case SYS_DOCUMENT_A3_SIZE:
					line_dots = 304 * 8;
					break;
				case SYS_DOCUMENT_B4_SIZE:
					line_dots = 256 * 8;
					break;
				case SYS_DOCUMENT_A4_SIZE:
					line_dots = 216 * 8;
					break;
				default:
					line_dots = 216 * 8;
					break;
				}
			}
			else {
				line_dots = 304 * 8;	/**１ライン４８６４ドット*/
			}
			break;
		case SYS_DOCUMENT_B4_SIZE:
			line_dots = 256 * 8;	/**１ライン２０４８ドット*/
			break;
		case SYS_DOCUMENT_A4_SIZE:
			line_dots = 216 * 8;	/**１ライン１７２８ドット*/
			break;
		default:	/**ありえないパス*/
			line_dots = 216 * 8;
			break;
		}
		break;
	case 300:
		switch (SYS_DocumentScanSize) {	/**解像度（主走査）が３００ｄｐｉの時の画素数を決める*/
		case SYS_DOCUMENT_A3_SIZE:
			line_dots = 304 * 12;	/**１ライン３６４８ドット*/
			break;
		case SYS_DOCUMENT_B4_SIZE:
			line_dots = 256 * 12;	/**１ライン３０７２ドット*/
			break;
		case SYS_DOCUMENT_A4_SIZE:
			line_dots = 216 * 12;	/**１ライン２５９２ドット*/
			break;
		default:	/**ありえないパス*/
			line_dots = 216 * 12;
			break;
		}
		break;
	default:	/**ありえないパス*/
		line_dots = 216 * 8;	/**１ライン１７２８ドット*/
		break;
	}
	return (line_dots);
}


/*************************************************************************
	module		:[1ラインの白マスク画素数の獲得]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[
		SYS_DocumentScanSizeが確定していること
	]
	comment		:[
		CDC_EncodePageTaskからコールされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/07/22]
	author		:[小谷正樹]
*************************************************************************/
UWORD SCN_GetEncodeMaskSize(UWORD h_resolution)
{
	UWORD mask_dots;
	UBYTE scan_size;

	/* スキャナの用途によって原稿サイズの参照個所を変える 1997/08/29 T.Nose */
	if (SCN_Control.UseType == IDP_SCANNER_TX) {
		scan_size = SYS_DocBlock.Src.Size;
	}
	else if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
		scan_size = SYS_DocumentScanSize;
	}

	/*************************/
	/**原稿サイズ別に決定する*/
	/*************************/
	switch (h_resolution) {	/**コーデック出力解像度別の処理による*/
	case 400:
		switch (scan_size) {	/**符号解像度（主走査）が４００ｄｐｉの時の画素数を決める*/
		case SYS_DOCUMENT_A3_SIZE:
			/* mask_dots = 5 * 16;		@**マスク８０ドット*@	@**符号化左右側5mm白マスク*/
			mask_dots = ((SYB_MaintenanceSwitch[MNT_SW_I2] & ADF_A3_MASK_LENGTH) * 16);
			break;
		case SYS_DOCUMENT_B4_SIZE:
			/* mask_dots = 2 * 16;		@**マスク３２ドット*@	@**符号化左右側2mm白マスク*/
			mask_dots = (((SYB_MaintenanceSwitch[MNT_SW_I2] & ADF_B4_MASK_LENGTH) >> 4) * 16);
			break;
		case SYS_DOCUMENT_A4_SIZE:
			/* mask_dots = 4 * 16;		@**マスク６４ドット*@	@**符号化左右側4mm白マスク*/
			mask_dots = ((SYB_MaintenanceSwitch[MNT_SW_I3] & ADF_A4_MASK_LENGTH) * 16);
			break;
		default:	/**ありえないパス*/
			mask_dots = 4 * 16;		/**マスク６４ドット*/
			break;
		}
		break;
	case 200:
		switch (scan_size) {	/**符号解像度（主走査）が２００ｄｐｉの時の画素数を決める*/
		case SYS_DOCUMENT_A3_SIZE:
			/* mask_dots = 5 * 8;		@**マスク４０ドット*@	@**符号化左右側5mm白マスク*/
			mask_dots = ((SYB_MaintenanceSwitch[MNT_SW_I2] & ADF_A3_MASK_LENGTH) * 8);
			break;
		case SYS_DOCUMENT_B4_SIZE:
			/* mask_dots = 2 * 8;		@**マスク１６ドット*@	@**符号化左右側2mm白マスク*/
			mask_dots = (((SYB_MaintenanceSwitch[MNT_SW_I2] & ADF_B4_MASK_LENGTH) >> 4) * 8);
			break;
		case SYS_DOCUMENT_A4_SIZE:
			/* mask_dots = 4 * 8;		@**マスク３２ドット*@	@**符号化左右側4mm白マスク*/
			mask_dots = ((SYB_MaintenanceSwitch[MNT_SW_I3] & ADF_A4_MASK_LENGTH) * 8);
			break;
		default:	/**ありえないパス*/
			mask_dots = 4 * 8;		/**マスク３２ドット*/
			break;
		}
		break;
	case 300:
		switch (scan_size) {	/**符号解像度（主走査）が３００ｄｐｉの時の画素数を決める*/
		case SYS_DOCUMENT_A3_SIZE:
			/* mask_dots = 5 * 12;		@**マスク６０ドット*@	@**符号化左右側5mm白マスク*/
			mask_dots = ((SYB_MaintenanceSwitch[MNT_SW_I2] & ADF_A3_MASK_LENGTH) * 12);
			break;
		case SYS_DOCUMENT_B4_SIZE:
			/* mask_dots = 2 * 12;		@**マスク２４ドット*@	@**符号化左右側2mm白マスク*/
			mask_dots = (((SYB_MaintenanceSwitch[MNT_SW_I2] & ADF_B4_MASK_LENGTH) >> 4) * 12);
			break;
		case SYS_DOCUMENT_A4_SIZE:
			/* mask_dots = 4 * 12;		@**マスク４８ドット*@	@**符号化左右側4mm白マスク*/
			mask_dots = ((SYB_MaintenanceSwitch[MNT_SW_I3] & ADF_A4_MASK_LENGTH) * 12);
			break;
		default:	/**ありえないパス*/
			mask_dots = 4 * 12;		/**マスク４８ドット*/
			break;
		}
		break;
	default:	/**ありえないパス*/
		mask_dots = 4 * 8;		/**マスク３２ドット*/
		break;
	}
	return (mask_dots);
}


/*************************************************************************
	module		:[コーデック入力イメージの解像度を獲得する]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[
		SCN_ModeSw,SYS_DocumentStoreItemが確定していること
	]
	comment		:[
		CDC_EncodePageTaskからコールされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/07/22]
	author		:[小谷正樹]
*************************************************************************/
UWORD SCN_GetEncodeStoreImageRes(void)
{
	UWORD result;

#if (PRO_CCD == DPI400)	/**ＣＣＤ解像度別の処理による*/
	switch (SCN_ModeSw) { /** 読み取りモードをチェック */
	case	SYS_NORMAL:			/* 0  普通			200dpi:8 dot/m  100dpi:3.85本/l */
	case	SYS_FINE:			/* 1  高画質		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_SFINE:			/* 2  超高画質		200dpi:8 dot/m  400dpi:15.5本/l */
	case	SYS_HFINE:			/* 3  超高画質		400dpi:16dot/m  400dpi:15.5本/l */
		result = 400;
		break;
	case	SYS_GRAY16:			/* 4  16階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY16_SEP:		/* 5  16階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY32:			/* 6  32階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY32_SEP:		/* 7  32階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY64:			/* 8  64階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY64_SEP:		/* 9  64階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY128:		/* 20 128階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY128_SEP:	/* 21 128階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		/* メモリー蓄積原稿の読み取り */
		if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
			/* コピー原稿のメモリー蓄積 */
			if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {	/** 中間調のマルチコピー */
				result = 400;
				/* 中間調縮小コピーでのプリントのデコード遅れ対策  1997/07/10
				** 70%未満は必ず200dpiディザ
				** 縮小コピーでは固有SWでディザ(400/200dpi)を指定可能
				** POPLAR_B/H 以外は大丈夫でしょう
				*/
				if (((SCN_CopyFile->Reduction < SCN_CopyReduction) && (SYB_MaintenanceSwitch[MNT_SW_C6] & COPY_GREY_70REDUCTION)) /* 70%未満は200dpiディザ */
				 || ((SCN_CopyFile->Reduction < 100) && (CHK_UNI_ReduceGrayCopyDither200()))) {
					/** ディザ200dpiでスキャンするため、画素を1/2にする */
					result = 200;
				}
			}
			/* 送信原稿のメモリー蓄積 */
			else {
				/* 固有スイッチ E0:sw2 で400/200を切り替える */
				if (CHK_UNI_HalfTone400DPI_ON()) {
					result = 400;
				}
				else {
					result = 200;
				}
			}
		}
		/* スキャナー送信原稿の読み取り */
		else if (SCN_Control.UseType == IDP_SCANNER_TX) {
			/* 400dpi->400dpi の送信 */
			if (SCN_ScannerTxReductionPattern >= SYS_A3_400_TO_A3_400 ) {
				result = 400;
			}
			/* 400dpi->200dpi の送信 */
			else {
				result = 200;
			}
		}
		/* その他 */
		else {
			result = 200;
		}
		break;
	case	SYS_300_NORMAL:		/* 10 				300dpi			100dpi		   */
	case	SYS_300_FINE:		/* 11 				300dpi			200dpi		   */
	case	SYS_OFINE:			/* 12 				300dpi			300dpi		   */
	case	SYS_EFINE:			/* 13 				300dpi          300dpi （㍉系） By S.Kawasaki 1996/06/14 */
	case	SYS_UFINE:			/* 14 				600dpi          600dpi （㍉系） By S.Kawasaki 1996/06/14 */
	case	SYS_E_HFINE:		/* 15 超高画質		300dpi:12dot/m  400dpi:15.5本/l */
	case	SYS_NORMAL_ROT:		/* 30 普通回転	   	100dpi: 4 dot/m 200dpi: 7.7本/l */
	case	SYS_SFINE_ROT:		/* 31 超高画質回転	400dpi:16 dot/m 200dpi: 7.7本/l */
	default:
		result = 400;	/**あり得ないパス*/
		break;
	}
#endif
#if (PRO_CCD == DPI200)	/**ＣＣＤ解像度別の処理による*/
	result = 200;
#endif
#if (PRO_CCD == DPI300)	/**ＣＣＤ解像度別の処理による*/
	switch (SCN_ModeSw) { /** 読み取りモードをチェック */
	case	SYS_NORMAL:			/* 0  普通			200dpi:8 dot/m  100dpi:3.85本/l */
	case	SYS_FINE:			/* 1  高画質		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_SFINE:			/* 2  超高画質		200dpi:8 dot/m  400dpi:15.5本/l */
		result = 300;
		break;
	case	SYS_GRAY16:			/* 4  16階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY16_SEP:		/* 5  16階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY32:			/* 6  32階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY32_SEP:		/* 7  32階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY64:			/* 8  64階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY64_SEP:		/* 9  64階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY128:		/* 20 128階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY128_SEP:	/* 21 128階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		/* メモリー蓄積原稿の読み取り */
		if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
			/* コピー原稿のメモリー蓄積 */
			if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {	/** 中間調のマルチコピー */
				result = 300;
			}
			/* 送信原稿のメモリー蓄積 */
			else {
				result = 200;
			}
		}
		/* スキャナー送信原稿の読み取り */
		else if (SCN_Control.UseType == IDP_SCANNER_TX) {
			/* 300dpi->300dpi の送信 */
			if (0) {
				result = 300;
			}
			/* 300dpi->200dpi の送信 */
			else {
				result = 200;
			}
		}
		/* その他 */
		else {
			result = 200;
		}
		break;
	case	SYS_HFINE:			/* 3  超高画質		400dpi:16dot/m  400dpi:15.5本/l */
	case	SYS_300_NORMAL:		/* 10 				300dpi			100dpi		   */
	case	SYS_300_FINE:		/* 11 				300dpi			200dpi		   */
	case	SYS_OFINE:			/* 12 				300dpi			300dpi		   */
	case	SYS_EFINE:			/* 13 				300dpi          300dpi （㍉系） By S.Kawasaki 1996/06/14 */
	case	SYS_UFINE:			/* 14 				600dpi          600dpi （㍉系） By S.Kawasaki 1996/06/14 */
	case	SYS_E_HFINE:		/* 15 超高画質		300dpi:12dot/m  400dpi:15.5本/l */
	case	SYS_NORMAL_ROT:		/* 30 普通回転	   	100dpi: 4 dot/m 200dpi: 7.7本/l */
	case	SYS_SFINE_ROT:		/* 31 超高画質回転	400dpi:16 dot/m 200dpi: 7.7本/l */
	default:
		result = 300;	/**あり得ないパス*/
		break;
	}
#endif
	return (result);
}


/*************************************************************************
	module		:[コーデック出力符号の解像度を獲得する]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[
		SCN_ModeSw,SYS_DocumentStoreItemが確定していること
	]
	comment		:[
		CDC_EncodePageTaskからコールされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/07/22]
	author		:[小谷正樹]
*************************************************************************/
UWORD SCN_GetEncodeStoreCodeRes(void)
{
	UWORD result;

#if (PRO_CCD == DPI400)	/**ＣＣＤ解像度別の処理による*/
	switch (SCN_ModeSw) { /** 読み取りモードをチェック */
	case	SYS_NORMAL:			/* 0  普通			200dpi:8 dot/m  100dpi:3.85本/l */
	case	SYS_FINE:			/* 1  高画質		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_SFINE:			/* 2  超高画質		200dpi:8 dot/m  400dpi:15.5本/l */
		result = 200;
		break;
	case	SYS_HFINE:			/* 3  超高画質		400dpi:16dot/m  400dpi:15.5本/l */
		result = 400;
		break;
	case	SYS_GRAY16:			/* 4  16階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY16_SEP:		/* 5  16階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY32:			/* 6  32階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY32_SEP:		/* 7  32階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY64:			/* 8  64階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY64_SEP:		/* 9  64階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY128:		/* 20 128階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY128_SEP:	/* 21 128階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		/* メモリー蓄積原稿の読み取り */
		if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
			/* コピー原稿のメモリー蓄積 */
			if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
			 || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {
				result = 400;
				/* 中間調縮小コピーでのプリントのデコード遅れ対策  1997/07/10
				** 70%未満は必ず200dpiディザ
				** 縮小コピーでは固有SWでディザ(400/200dpi)を指定可能
				** POPLAR_B/H 以外は大丈夫でしょう
				*/
				if (((SCN_CopyFile->Reduction < SCN_CopyReduction) && (SYB_MaintenanceSwitch[MNT_SW_C6] & COPY_GREY_70REDUCTION)) /* 縮小率７０％未満 */
				 || ((SCN_CopyFile->Reduction < 100) && CHK_UNI_ReduceGrayCopyDither200())) { /* 縮小で200dpiディザ設定 */
					/** ディザ200dpiでスキャンするため、画素を1/2にする */
					result = 200;
				}
			}
			/* 送信原稿のメモリー蓄積 */
			else {
				/* 固有スイッチ E0:sw2 で400/200を切り替える */
				if (CHK_UNI_HalfTone400DPI_ON()) {
					result = 400;
				}
				else {
					result = 200;
				}
			}
		}
		/* スキャナー送信原稿の読み取り */
		else if (SCN_Control.UseType == IDP_SCANNER_TX) {
			/* 400dpi->400dpi の送信 */
			if (SCN_ScannerTxReductionPattern >= SYS_A3_400_TO_A3_400 ) {
				result = 400;
			}
			/* 400dpi->200dpi の送信 */
			else {
				result = 200;
			}
		}
		/* その他 */
		else {
			result = 200;
		}
		break;
	case	SYS_300_NORMAL:		/* 10 				300dpi			100dpi		   */
	case	SYS_300_FINE:		/* 11 				300dpi			200dpi		   */
	case	SYS_OFINE:			/* 12 				300dpi			300dpi		   */
	case	SYS_EFINE:			/* 13 				300dpi          300dpi （㍉系） By S.Kawasaki 1996/06/14 */
	case	SYS_UFINE:			/* 14 				600dpi          600dpi （㍉系） By S.Kawasaki 1996/06/14 */
	case	SYS_E_HFINE:		/* 15 超高画質		300dpi:12dot/m  400dpi:15.5本/l */
	case	SYS_NORMAL_ROT:		/* 30 普通回転	   	100dpi: 4 dot/m 200dpi: 7.7本/l */
	case	SYS_SFINE_ROT:		/* 31 超高画質回転	400dpi:16 dot/m 200dpi: 7.7本/l */
	default:
		result = 400;	/**あり得ないパス*/
		break;
	}
#endif
#if (PRO_CCD == DPI200)	/**ＣＣＤ解像度別の処理による*/
	result = 200;
#endif
#if (PRO_CCD == DPI300)	/**ＣＣＤ解像度別の処理による*/
	switch (SCN_ModeSw) { /** 読み取りモードをチェック */
	case	SYS_NORMAL:			/* 0  普通			200dpi:8 dot/m  100dpi:3.85本/l */
		result = 200;
		break;
/* for anzu_l 300*400 by T.Soneoka 1997/11/13 */
	case	SYS_FINE:			/* 1  高画質		200dpi:8 dot/m  200dpi:7.7 本/l */
		/* メモリー蓄積原稿の読み取り */
		if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
			/* コピー原稿のメモリー蓄積 */
			if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
			 || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {
				result = 300;
			}
			/* 送信原稿のメモリー蓄積 */
			else {
				result = 200;
			}
		}
		/* スキャナー送信原稿の読み取り */
		else if (SCN_Control.UseType == IDP_SCANNER_TX) {
			result = 200;
		}
		/* その他 */
		else {
			result = 200;
		}
		break;
/* for anzu_l 300*400 by T.Soneoka 1997/11/13 */
	case	SYS_SFINE:			/* 2  超高画質		200dpi:8 dot/m  400dpi:15.5本/l */
		/* メモリー蓄積原稿の読み取り */
		if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
			/* コピー原稿のメモリー蓄積 */
			if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
			 || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {
				result = 300;
			}
 #if (PRO_CLASS1 == ENABLE)
			/* Class1の時はSFINEは200*400のまま蓄積します */
			/* 1998/07/23 by Y.Tanimoto */
			else if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
				result = 200;
			}
 #endif
			/* 送信原稿のメモリー蓄積 */
			else {
				/* for anzu_l 300*400 by T.Soneoka 1997/11/13 */
				result = 300;
			}
		}
		/* スキャナー送信原稿の読み取り */
		else if (SCN_Control.UseType == IDP_SCANNER_TX) {
			/* for anzu_l 300*400 by T.Soneoka 1997/11/13 */
			result = 300;
		}
		/* その他 */
		else {
			result = 200;
		}
		break;
	case	SYS_GRAY16:			/* 4  16階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY16_SEP:		/* 5  16階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY32:			/* 6  32階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY32_SEP:		/* 7  32階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY64:			/* 8  64階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY64_SEP:		/* 9  64階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY128:		/* 20 128階調		200dpi:8 dot/m  200dpi:7.7 本/l */
	case	SYS_GRAY128_SEP:	/* 21 128階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		/* メモリー蓄積原稿の読み取り */
		if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
			/* コピー原稿のメモリー蓄積 */
			if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
			 || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {
				result = 300;
			}
			/* 送信原稿のメモリー蓄積 */
			else {
				result = 200;
			}
		}
		/* スキャナー送信原稿の読み取り */
		else if (SCN_Control.UseType == IDP_SCANNER_TX) {
			/* 300dpi->300dpi の送信 */
			if (0) {
				result = 300;
			}
			/* 300dpi->200dpi の送信 */
			else {
				result = 200;
			}
		}
		/* その他 */
		else {
			result = 200;
		}
		break;
	case	SYS_EFINE:			/* 13 				300dpi          300dpi （㍉系） By S.Kawasaki 1996/06/14 */
	case	SYS_E_HFINE:		/* 15 超高画質		300dpi:12dot/m  400dpi:15.5本/l */
		result = 300;
		break;
	case	SYS_HFINE:			/* 3  超高画質		400dpi:16dot/m  400dpi:15.5本/l */
	case	SYS_300_NORMAL:		/* 10 				300dpi			100dpi		   */
	case	SYS_300_FINE:		/* 11 				300dpi			200dpi		   */
	case	SYS_OFINE:			/* 12 				300dpi			300dpi		   */
	case	SYS_UFINE:			/* 14 				600dpi          600dpi （㍉系） By S.Kawasaki 1996/06/14 */
	case	SYS_NORMAL_ROT:		/* 30 普通回転	   	100dpi: 4 dot/m 200dpi: 7.7本/l */
	case	SYS_SFINE_ROT:		/* 31 超高画質回転	400dpi:16 dot/m 200dpi: 7.7本/l */
	default:
		result = 200;	/**あり得ないパス*/
		break;
	}
#endif
	return (result);
}


/*************************************************************************
	module		:[ADFでのNORMALの先端の補正量]
	function	:[
		SFINEからのNOMALの補正量を返す
	]
	return		:[
		補正ステップ数
		-7 ～ +7 (単位:10step)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/05/09]
	author		:[竹内茂樹]
*************************************************************************/
BYTE SCN_ADF_NormalTopAdjustStep( void )
{
	BYTE step;	/* ステップ */

	step = (BYTE)(SYB_MaintenanceSwitch[MNT_SW_I0] & ADF_NORMAL_TOP_ADJUST_STEP);
	if (SYB_MaintenanceSwitch[MNT_SW_I0] & ADF_NORMAL_TOP_ADJUST_SIGN) {
		step *= -1;
	}

	return (step);
}

/*************************************************************************
	module		:[ADFでのFINEの後端の補正量]
	function	:[
		SFINEからのFINEの補正量を返す
	]
	return		:[
		補正ステップ数
		-7 ～ +7 (単位:10step)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/05/09]
	author		:[竹内茂樹]
*************************************************************************/
BYTE SCN_ADF_FineTopAdjustStep( void )
{
	BYTE step;	/* ステップ */

	step = (BYTE)(SYB_MaintenanceSwitch[MNT_SW_I0] & ADF_FINE_TOP_ADJUST_STEP);
	step >>= 4;
	if (SYB_MaintenanceSwitch[MNT_SW_I0] & ADF_FINE_TOP_ADJUST_SIGN) {
		step *= -1;
	}

	return (step);
}

/*************************************************************************
	module		:[ADFでのNORMALの後端の補正量]
	function	:[
		SFINEからのNOMALの補正量を返す
	]
	return		:[
		補正ステップ数
		-7 ～ +7 (単位:10step)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/05/10]
	author		:[竹内茂樹]
*************************************************************************/
BYTE SCN_ADF_NormalEndAdjustStep( void )
{
	BYTE step;	/* ステップ */

	step = (BYTE)(SYB_MaintenanceSwitch[MNT_SW_I1] & ADF_NORMAL_END_ADJUST_STEP);
	if (SYB_MaintenanceSwitch[MNT_SW_I1] & ADF_NORMAL_END_ADJUST_SIGN) {
		step *= -1;
	}

	return (step);
}

/*************************************************************************
	module		:[ADFでのFINEの後端の補正量]
	function	:[
		SFINEからのFINEの補正量を返す
	]
	return		:[
		補正ステップ数
		-7 ～ +7 (単位:10step)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/05/10]
	author		:[竹内茂樹]
*************************************************************************/
BYTE SCN_ADF_FineEndAdjustStep( void )
{
	BYTE step;	/* ステップ */

	step = (BYTE)(SYB_MaintenanceSwitch[MNT_SW_I1] & ADF_FINE_END_ADJUST_STEP);
	step >>= 4;
	if (SYB_MaintenanceSwitch[MNT_SW_I1] & ADF_FINE_END_ADJUST_SIGN) {
		step *= -1;
	}

	return (step);
}

/*************************************************************************
	module		:[中間調がディザパターンであるか否か]
	function	:[]
	return		:[
		TRUE :中間調パターンがディザ
		FALSE:中間調パターンが誤差拡散
	]
	common		:[]
	condition	:[]
	comment		:[
		scn_open() から呼ばれる
		ディザ／誤差拡散の判断部分を抜き出した
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/09/16]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE IsGrayPatternDither(UBYTE doc_item)
{
	UBYTE is_dither = TRUE;

#if (PRO_CCD == DPI400)
	switch (doc_item) {
	case SCN_MEMCOPY_DOC: /* コピー原稿 */
		if ((SCN_CopyFile->Reduction < SCN_CopyReduction) /* 70%以下縮小 */
		 && (SYB_MaintenanceSwitch[MNT_SW_C6] & COPY_GREY_70REDUCTION)) {
			break;
		}
		if ((SCN_CopyFile->Reduction < 100)	/* 縮小 */
		 && (CHK_UNI_ReduceGrayCopyDither200() || CHK_UNI_ReduceGrayCopyDither400())) {
			break;
		}
		if (CHK_UNI_64ScaleDither()) {
			break;
		}
		is_dither = FALSE;
		break;
	case SCN_MEMTX_DOC: /* メモリー送信原稿 */
#if (0) /* MemTx専用のスイッチ追加 T.Nose 1998/07/14 */
//		400dpi蓄積と誤差／ディザの判断は別個にする
//		if (!CHK_UNI_HalfTone400DPI_ON()) {
//			break;
//		}
//		if (CHK_UNI_64ScaleDither()) {
//			break;
//		}
#endif
		if (CHK_UNI_MemTxDocGosaScan()) {
			is_dither = FALSE;
		}
		break;
	case SCN_SCNTX_DOC: /* スキャナー送信原稿 */
		if (SCN_ScannerTxReductionPattern >= SYS_A3_400_TO_A3_400 ) {
			is_dither = FALSE;
		}
		break;
	default:
		break;
	}
#endif
#if (PRO_CCD == DPI300)
	switch (doc_item) {
	case SCN_MEMCOPY_DOC: /* コピー原稿 */
		if (!CHK_UNI_64ScaleDither()) {
			is_dither = FALSE;
		}
		break;
	case SCN_MEMTX_DOC: /* メモリー送信原稿 */
		break;
	case SCN_SCNTX_DOC: /* スキャナー送信原稿 */
		if (SCN_ScannerTxReductionPattern >= SYS_A3_400_TO_A3_400 ) {
			is_dither = FALSE;
		}
		break;
	default:
		break;
	}
#endif
#if (PRO_CCD == DPI200)
	switch (doc_item) {
	case SCN_MEMCOPY_DOC: /* コピー原稿 */
		if (!CHK_UNI_64ScaleDither()) {
			is_dither = FALSE;
		}
		break;
	case SCN_MEMTX_DOC: /* メモリー送信原稿 */
#if (0)
		if (!CHK_UNI_64ScaleDither()) {
			is_dither = FALSE;
		}
#endif
		break;
	case SCN_SCNTX_DOC: /* スキャナー送信原稿 */
		if (SCN_ScannerTxReductionPattern >= SYS_A3_400_TO_A3_400 ) {
			is_dither = FALSE;
		}
		break;
	default:
		break;
	}
#endif

	return(is_dither);
}

/*************************************************************************
	module		:[中間調の縮小率を求める]
	function	:[]
	return		:[
		IDPに設定する縮小率
	]
	common		:[]
	condition	:[]
	comment		:[
		scn_open() から呼ばれる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/09/17]
	author		:[野瀬敏弘]
*************************************************************************/
UWORD GetGrayReductionPattern(UBYTE doc_item)
{
	UWORD reduction_pattern;

	/*----------------------------------------------------------------------------------------------*/
	/*																								*/
	/*		解像度変換の読み替え																	*/
	/*		POPLAR_B/H(400dpi),ANZU_L(300dpi)の間で条件コンパイルをできるだけ少なくする為に			*/
	/*		ANZU_Lでは次の読み替えを行います｡														*/
	/*		Ａ４原稿時:SYS_A4_400_TO_A4_200	(A4原稿400dpiからA4原稿200dpiに解像度変換)				*/
	/*																								*/
	/*					→ SYS_A4_303_TO_A4_203(A4原稿12dot/mmからA4原稿8dot/mmに解像度変換)		*/
	/*																								*/
	/*		Ｂ４原稿時:SYS_B4_400_TO_B4_200(B4原稿400dpiからB4原稿200dpiに解像度変換)				*/
	/*																								*/
	/*					→ SYS_B4_303_TO_B4_203(B4原稿12dot/mmからB4原稿8dot/mmに解像度変換)		*/
	/*																								*/
	/*		Ａ３原稿時:SYS_A3_400_TO_A3_200 →	ANZUの仕様にないので未変更							*/
	/*																								*/
	/*----------------------------------------------------------------------------------------------*/
#if (PRO_CCD == DPI400)
	switch (doc_item) {
	/**************/
	/* コピー原稿 */
	/**************/
	case SCN_MEMCOPY_DOC:
		reduction_pattern = 1000; /* コピー原稿は１００％ */
		if (((SCN_CopyFile->Reduction < SCN_CopyReduction) && (SYB_MaintenanceSwitch[MNT_SW_C6] & COPY_GREY_70REDUCTION))
		 || ((SCN_CopyFile->Reduction < 100) && CHK_UNI_ReduceGrayCopyDither200())) {
			/* 縮小コピーが間に合わないことがある為、200dpi に変換 */
			if (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE) {
				reduction_pattern = SYS_A3_400_TO_A3_200;
			}
			else if (SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE) {
				reduction_pattern = SYS_B4_400_TO_B4_200;
			}
			else { /** A4 SIZE **/
				reduction_pattern = SYS_A4_400_TO_A4_200;
			}
		}
		break;
	/********************/
	/* メモリー送信原稿 */
	/********************/
	case SCN_MEMTX_DOC:
		if (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE) {
			reduction_pattern = SYS_A3_400_TO_A3_200;
		}
		else if (SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE) {
			reduction_pattern = SYS_B4_400_TO_B4_200;
		}
		else { /** A4 SIZE **/
			reduction_pattern = SYS_A4_400_TO_A4_200;
		}

		/* メモリ送信原稿の中間調で400dpi蓄積(debug用)  1997/06/19
		** uniE0-2で400dpi有効
		*/
		if (CHK_UNI_HalfTone400DPI_ON()) {
			reduction_pattern = 1000;
		}
		break;
	/**********************/
	/* スキャナー送信原稿 */
	/**********************/
	case SCN_SCNTX_DOC:
		if (SCN_ScannerTxReductionPattern >= SYS_A3_400_TO_A3_400 ){
			/** 誤差拡散で４００ｘ４００で送信 */
			reduction_pattern = 1000;
		}
		else {
			/** ディザで縮小送信 */
			reduction_pattern = (UWORD)SCN_ScannerTxReductionPattern;
		}
		break;
	default:
		break;
	}
#endif
#if (PRO_CCD == DPI300)
	switch (doc_item) {
	/**************/
	/* コピー原稿 */
	/**************/
	case SCN_MEMCOPY_DOC:
		reduction_pattern = 1000; /* コピー原稿は１００％ */
		break;
	/********************/
	/* メモリー送信原稿 */
	/********************/
	case SCN_MEMTX_DOC:
		if (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE) {
			reduction_pattern = SYS_A3_400_TO_A3_200;
		}
		else if (SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE) {
			reduction_pattern = SYS_B4_400_TO_B4_200;
		}
		else { /** A4 SIZE **/
			reduction_pattern = SYS_A4_400_TO_A4_200;
		}
		break;
	/**********************/
	/* スキャナー送信原稿 */
	/**********************/
	case SCN_SCNTX_DOC:
		if (SCN_ScannerTxReductionPattern >= SYS_A3_400_TO_A3_400 ){
			/** 誤差拡散で３００ｘ３００で送信 */
			reduction_pattern = 1000;
		}
		else {
			/** ディザで縮小送信 */
			reduction_pattern = (UWORD)SCN_ScannerTxReductionPattern;
		}
		break;
	default:
		break;
	}
#endif
#if (PRO_CCD == DPI200)
	switch (doc_item) {
	/**************/
	/* コピー原稿 */
	/**************/
	case SCN_MEMCOPY_DOC:
	/********************/
	/* メモリー送信原稿 */
	/********************/
	case SCN_MEMTX_DOC:
		reduction_pattern = 1000; /* コピー／メモリーＴｘ原稿は１００％ */
		break;
	/**********************/
	/* スキャナー送信原稿 */
	/**********************/
	case SCN_SCNTX_DOC:
		if (SCN_ScannerTxReductionPattern >= SYS_A3_400_TO_A3_400 ){
			/** 誤差拡散で２００ｘ２００で送信 */
			reduction_pattern = 1000;
		}
		else {
			/** ディザで縮小送信 */
			reduction_pattern = (UWORD)SCN_ScannerTxReductionPattern;
		}
		break;
	default:
		break;
	}
#endif
	return(reduction_pattern);
}

/*************************************************************************
	module		:[コピー原稿を蓄積するサイズを獲得する]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		scn_task() から呼ばれる
		選択されている記録紙(SYB_MultiCopyFile[].Size/SYB_ManualCopyFile.Size)から
		原稿を蓄積するサイズを得る
		コピー原稿をスキャナ側で縮小する場合に使用します
		セットされている原稿のサイズの判断が必要な場合（ex.Ａ３原稿だけ）、
		この関数をコールする前に行ってください
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/09/25]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE SCN_GetCopyDocStoreSize(void)
{
	UBYTE size;

#if (PRO_KEYPANEL == PANEL_POPLAR_H)
	/* 「記録紙自動あり」＆「縮小パターンが定型のみ」の機種(POPLAR_Hのみ)
	** Ａ３原稿はＢ４に縮小して蓄積する
	** T.Nose 1998/04/09
	*/
	if (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) {
		if (SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette == SYS_AUTO_CASSETTE) { /* T.Nose 1998/04/08 */
			size = SYS_B4_PAPER;
		}
		else {
			size = SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Size;
		}
	}
	else if (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE) {
		size = SYB_ManualCopyFile.Size;
	}
#else
	if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
	 && (SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette != SYS_AUTO_CASSETTE)) { /* T.Nose 1998/04/08 */
		size = SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Size;
	}
	else if (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE) {
		size = SYB_ManualCopyFile.Size;
	}
#endif
	else { /* 送信原稿 */
		return(SYS_DocumentScanSize);
	}

	switch (size) {
	case SYS_A5_PAPER:
		return(SYS_DOCUMENT_A4_SIZE);
	case SYS_A5R_PAPER:
		return(SYS_DOCUMENT_A4_SIZE);
	case SYS_B5_PAPER:
		return(SYS_DOCUMENT_A4_SIZE);
	case SYS_B5R_PAPER:
		return(SYS_DOCUMENT_B4_SIZE);
	case SYS_LT_PAPER:
	case SYS_A4_PAPER:
	case SYS_LG_PAPER:
		return(SYS_DOCUMENT_A4_SIZE);
	case SYS_B4_PAPER:
		return(SYS_DOCUMENT_B4_SIZE);
	case SYS_A3_PAPER:
		return(SYS_DOCUMENT_A3_SIZE);
	default:
		return(SYS_DOCUMENT_A4_SIZE);
	}
}

#if (PRO_CLASS1 == ENABLE)	
/*************************************************************************
	module		:[ローカルスキャン原稿を蓄積するサイズを獲得する]
	function	:[ＰＣの記録幅能力がとFAXの記録幅(読取り原稿幅）より下回っている
			      時、ＰＣの記憶幅能力のサイズに納まるよう縮小をかける
	]
	return		:[
		SYS_DOCUMENT_A3_SIZE
		SYS_DOCUMENT_B4_SIZE
		SYS_DOCUMENT_A4_SIZE
	]
	common		:[]
	condition	:[
		CL1_PCDocumentSizeが確定していること
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1998/02/23]
	author		:[福井知史]
*************************************************************************/
UWORD SCN_GetLocalScanSize(void)
{
	switch (SYS_DocumentScanSize) {	
	case SYS_DOCUMENT_A3_SIZE:
		switch (CL1_PCDocumentSize) {
		case SYS_DOCUMENT_A3_SIZE:
			return(SYS_DOCUMENT_A3_SIZE);
		case SYS_DOCUMENT_B4_SIZE:
			return(SYS_DOCUMENT_B4_SIZE);
			break;
		case SYS_DOCUMENT_A4_SIZE:
		default:
			return(SYS_DOCUMENT_A4_SIZE);
		}
	case SYS_DOCUMENT_B4_SIZE:
		switch (CL1_PCDocumentSize) {
		case SYS_DOCUMENT_A3_SIZE:
		case SYS_DOCUMENT_B4_SIZE:
			return(SYS_DOCUMENT_B4_SIZE);
		case SYS_DOCUMENT_A4_SIZE:
		default:
			return(SYS_DOCUMENT_A4_SIZE);
		}
	default:	/* For "case SYS_DOCUMENT_A4_SIZE" */
		return(SYS_DOCUMENT_A4_SIZE);
	}
}
/*************************************************************************
	module		:[ローカルスキャン時、1ラインの出力イメージ画素数の獲得]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[
		CL1_PCDocumentSizeが確定していること
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1998/02/23]
	author		:[福井知史]
*************************************************************************/
UWORD SCN_GetEncodeLocalScanSize(UWORD h_resolution)
{
	UWORD line_dots;

	/*************************************/
	/**原稿サイズ別に画素ベースを決定する*/
	/*************************************/
	switch(SCN_GetLocalScanSize()) {	
	case SYS_DOCUMENT_A3_SIZE:
		line_dots = 304;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		line_dots = 256;
		break;
	case SYS_DOCUMENT_A4_SIZE:
	default:
		line_dots = 216;
		break;
	}

	/***************************/
	/**解像度別に画素数を決める*/
	/***************************/
	switch (h_resolution) {	/**コーデック解像度別の処理による*/
	case 400:	/**解像度（主走査）が４００ｄｐｉの時の画素数を決める*/
		line_dots *= 16;
		break;
	case 300:	/**解像度（主走査）が３００ｄｐｉの時の画素数を決める*/
		line_dots *= 12;
		break;
	case 200:	/**解像度（主走査）が２００ｄｐｉの時の画素数を決める*/
		line_dots *= 8;
		break;
	default:	/**ありえないパス*/
		line_dots *= 8;	
		break;
	}

	return (line_dots);
}
#endif	/* (PRO_CLASS1 == ENABLE) */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/*************************************************************************
	module		:[Minimum Set対応時の読み取りモード変換]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1998/03/25]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	GetInternetFaxScanMode(UBYTE mode)
{
	/*if (SYS_INF_MinimumSetRequest == TRUE) {1998/05/23 Eguchi*/
	if (CHK_UNI_INF_MinimumSetAvail()) { /*1998/05/23 Eguchi*/
		switch (mode) {
		case SYS_NORMAL:
		case SYS_GRAY16:
		case SYS_GRAY16_SEP:
		case SYS_GRAY32:
		case SYS_GRAY32_SEP:
		case SYS_GRAY64:
		case SYS_GRAY64_SEP:
		case SYS_GRAY128:
		case SYS_GRAY128_SEP:
			break;
		default:	/*　SFine以上は全部Fineに落とします　*/
			mode = SYS_FINE;
			break;
		}
	}
	else {
		switch (mode) {
		case	SYS_NORMAL:			/* 0  普通			200dpi:8 dot/m  100dpi:3.85本/l */
		case	SYS_FINE:			/* 1  高画質		200dpi:8 dot/m  200dpi:7.7 本/l */
		case	SYS_SFINE:			/* 2  超高画質		200dpi:8 dot/m  400dpi:15.5本/l */
		case	SYS_GRAY16:			/* 4  16階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		case	SYS_GRAY16_SEP:		/* 5  16階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		case	SYS_GRAY32:			/* 6  32階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		case	SYS_GRAY32_SEP:		/* 7  32階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		case	SYS_GRAY64:			/* 8  64階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		case	SYS_GRAY64_SEP:		/* 9  64階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		case	SYS_GRAY128:		/* 20 128階調		200dpi:8 dot/m  200dpi:7.7 本/l */
		case	SYS_GRAY128_SEP:	/* 21 128階調		200dpi:8 dot/m  200dpi:7.7 本/l */
			break;
		case	SYS_HFINE:			/* 3  超高画質		400dpi:16dot/m  400dpi:15.5本/l */
			mode = SYS_SFINE;
			break;
		case	SYS_300_NORMAL:		/* 10 				300dpi			100dpi		   */
		case	SYS_300_FINE:		/* 11 				300dpi			200dpi		   */
		case	SYS_OFINE:			/* 12 				300dpi			300dpi		   */
		case	SYS_EFINE:			/* 13 				300dpi          300dpi （㍉系） By S.Kawasaki 1996/06/14 */
		case	SYS_UFINE:			/* 14 				600dpi          600dpi （㍉系） By S.Kawasaki 1996/06/14 */
		case	SYS_E_HFINE:		/* 15 超高画質		300dpi:12dot/m  400dpi:15.5本/l */
		default:
			mode = SYS_FINE;
			break;
		}
	}
	return (mode);
}

/*************************************************************************
	module		:[Minimum Set対応時の縮小率]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1998/03/25]
	author		:[Y.Tanimoto]
*************************************************************************/
UWORD	GetInternetFaxScanReducion(UBYTE size)
{
	UWORD reduction;
	/*if (SYS_INF_MinimumSetRequest == TRUE) { 1998/05/23 Eguchi */
	if (CHK_UNI_INF_MinimumSetAvail()) { /*1998/05/23 Eguchi*/
		switch (size) {	/* 読み取り原稿のサイズ */
		case SYS_DOCUMENT_A3_SIZE:
			reduction = 70;	/* 70 % */
			break;
		case SYS_DOCUMENT_B4_SIZE:
			reduction = 81;	/* 81 % */
			break;
		case SYS_DOCUMENT_A4_SIZE:
		default:
			reduction = 100; /* 100 % */
			break;
		}
	}
	else {
		reduction = 100; /* 100 % */
	}
	return (reduction);
}

/*************************************************************************
	module		:[Minimum Set対応時の縮小率]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1998/03/25]
	author		:[Y.Tanimoto]
*************************************************************************/
UWORD GetInternetFaxEncodeScanSize(UWORD h_resolution)
{
	UWORD line_dots;

	/*************************************/
	/**原稿サイズ別に画素ベースを決定する*/
	/*************************************/
	/*if (SYS_INF_MinimumSetRequest == TRUE) { 1998/05/23 Eguchi*/
	if (CHK_UNI_INF_MinimumSetAvail()) { /*1998/05/23 Eguchi*/
		line_dots = 216;
	}
	else {
		switch(SYS_DocumentScanSize) {	
		case SYS_DOCUMENT_A3_SIZE:
			line_dots = 304;
			break;
		case SYS_DOCUMENT_B4_SIZE:
			line_dots = 256;
			break;
		case SYS_DOCUMENT_A4_SIZE:
		default:
			line_dots = 216;
			break;
		}
	}

	/***************************/
	/**解像度別に画素数を決める*/
	/***************************/
	switch (h_resolution) {	/**コーデック解像度別の処理による*/
	case 400:	/**解像度（主走査）が４００ｄｐｉの時の画素数を決める*/
		line_dots *= 16;
		break;
	case 300:	/**解像度（主走査）が３００ｄｐｉの時の画素数を決める*/
		line_dots *= 12;
		break;
	case 200:	/**解像度（主走査）が２００ｄｐｉの時の画素数を決める*/
		line_dots *= 8;
		break;
	default:	/**ありえないパス*/
		line_dots *= 8;	
		break;
	}
	return (line_dots);
}

/*************************************************************************
	module		:[Minimum Set対応時の解像度]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1998/03/25]
	author		:[Y.Tanimoto]
*************************************************************************/
UWORD	GetInternetFaxEncodeScanRes(void)
{
	UWORD res;
	/*if (SYS_INF_MinimumSetRequest == TRUE) { 1998/05/23 Eguchi */
	if (CHK_UNI_INF_MinimumSetAvail()) { /*1998/05/23 Eguchi*/
		res = 200;
	}
	else {
		#if (PRO_CCD == DPI200)
			res = 200;
		#else
			switch (SCN_ModeSw) {
		 #if (PRO_CCD == DPI400)
			case	SYS_HFINE:
				res = 400;
				break;
		 #endif
		 #if (PRO_CCD == DPI300)
			case	SYS_EFINE:
				res = 300;
				break;
		 #endif
			default:
				res = 200;
				break;
			}
		#endif
	}
	return (res);
}
#endif	/* PRO_DIALUP_INTERNET_FAX */

