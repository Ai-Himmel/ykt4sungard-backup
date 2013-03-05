/*
 *	@(#)$Id: Prtthrml.c,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/prj/Eva/Src/prt/prtthrml.c
 *	Create:	Tue May 26 09:49:40 1998	by	ishiyama
 *	Description:
 *		Thermal Head Printer Control Routine
 *	Notes:
 *		関連ファイルとの違いは、
 *			prt_drv.c:	I/O 設定を含まない
 *			prtengin.c:	I/O 設定を含んで、プリンタ共通
 *			prtlaser.c:	Leser Beam Printer だけに使用するルーチン
 *			prtthrml.c:	Thermal Printer だけに使用するルーチン
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\ext_v\dma_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"	/* Add By O.Kimoto 1998/10/27 */
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\define\mntsw_h.h"	/* Endmark2 By O.Kimoto 1999/02/11 */
#include "\src\atlanta\define\sysprint.h"	/* Endmark2 By O.Kimoto 1999/02/11 */
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
#include "\src\atlanta\satsuki2\ext_v\ga_buf.h"
#include "\src\atlanta\satsuki2\define\scn_def.h"	/* B4->A4白抜け対策 1999/03/05 by T.Soneoka */
#include "\src\atlanta\satsuki2\define\m_param.h"	/* Add by Y.kano 2003/09/30 */
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
#include "\src\atlanta\hinoki\define\scn_def.h"	/* B4->A4白抜け対策 1999/03/05 by T.Soneoka */
 #endif

#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* ＰＳ２の平均レベルを算出 by Y.kano 2004/03/01 */
#include	"\src\atlanta\hinoki\define\m_param.h"
#endif

#if (0) /* 大域にします 1999/1/14 by T.Soneoka */
**static WORD	backward_step_error = 0;
#endif
static UDWORD	PrtImageBufReadLineAddress = 0; /* For Debuf */
static UBYTE	used_count;	/* 1998/12/16 by T.Soneoka */
static UBYTE	pre_used_count; /* 1998/12/22 by T.Soneoka */
static UBYTE	PrintExecute; /* 1998/12/16 by T.Soneoka */
static UBYTE	print_count; /* 1998/12/16 by T.Soneoka */
static UBYTE	PreHeatPhase; /* 1998/12/16 by T.Soneoka */
static UBYTE	motor_stop_request; /* 1999/03/01 by T.Soneoka */

#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* ＰＳ２自動調整不具合対応 by Y.kano 2004/12/06 */
static WORD		BackWardStepsFromPS2;
#endif

/*----------------------------------------------------------------------------
 *	Thermal Head Printer Control
 *---------------------------------------------------------------------------*/

BOOL	QueryPs1On(void)
{
	return	CookedPs1;
}

/*
 *	Name:	Watch Cooked Mode PS1
 *	Create:	Wed May 27 17:16:20 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	Ps1Changed(void);
 *	Description:
 *		Cooked Mode で PS1 をチェック,結果は CookedPs1
 *		5msec タイマで記憶を更新。
 *	Return Value:
 *		TRUE:	PS1 変化あり
 *		FALSE:	PS1 変化無し
 *	Change Log:
 *		
 */
BOOL	Ps1Changed(void)
{
	BOOL	CurrentPs1;			/* 現在のセンサー状態 */
	BOOL	Rtn;

	Rtn = FALSE;
	CurrentPs1 = PS1();
	if (CookedPs1 != CurrentPs1) {
		if (--Ps1CookCounter <= 0) {	/* チャタリング防止の為のカウンター減算 */
			CookedPs1 = CurrentPs1;		/* 現在の状態を記憶 */
			if (CurrentPs1) {
				Ps1CookCounter = Ps1Exist2NonCount;
			} else {
				Ps1CookCounter = Ps1Non2ExistCount;
			}
			Rtn = TRUE;
		}
	} else {
		if (CurrentPs1) {
			Ps1CookCounter = Ps1Exist2NonCount;
		} else {
			Ps1CookCounter = Ps1Non2ExistCount;
		}
	}
	return	Rtn;
}


BOOL	QueryPs2On(void)
{
	return	CookedPs2;
}

/*
 *	Name:	Watch Cooked Mode PS2
 *	Create:	Wed May 27 17:16:20 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	Ps2Changed(void);
 *	Description:
 *		Cooked Mode で PS2 をチェック,結果は CookedPs2
 *		5msec タイマで記憶を更新。
 *	Return Value:
 *		TRUE:	PS2 変化あり
 *		FALSE:	PS2 変化無し
 *	Change Log:
 *		
 */
BOOL	Ps2Changed(void)
{
	BOOL	CurrentPs2;			/* 現在のセンサー状態 */
	BOOL	Rtn;

	Rtn = FALSE;
	CurrentPs2 = PS2();
	if (CookedPs2 != CurrentPs2) {
		if (--Ps2CookCounter <= 0) {	/* チャタリング防止の為のカウンター減算 */
			Ps2CookCounter = PsChatCount;
			CookedPs2 = CurrentPs2;		/* 現在の状態を記憶 */
			Rtn = TRUE;
		}
	} else {
		Ps2CookCounter = PsChatCount;
	}
	return	Rtn;
}


/*
 *	Name:	Watch Raw Mode InterLock for Printer
 *	Create:	Wed May 27 17:22:02 GMT--9:00 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	InterLock4PrinterRaw(void);
 *	Description:
 *		Raw Mode で Printer 側 InterLock をチェック
 *	Return Value:
 *		TRUE:	InterLock is ON(Close)
 *		FALSE:	InterLock is OFF(Open)
 *	Change Log:
 *		
 */
BOOL	InterLock4PrintRaw(void)
{
	BOOL	Rtn;				/* Return Value */

#if defined(SATSUKI2)	/* SATSUKI2の場合、強制的に’０’を返す by Y.Kano 2003/07/03 */
	return(0);
#else
	if (InputWORD(GA_PGBDR) & IO_BIT_TOPOP) {
		Rtn = FALSE;
	} else {
		Rtn = TRUE;
	}
	return	Rtn;
#endif
}

/*
 *	Name:	Watch Cooked Mode InterLock for Printer
 *	Create:	Wed May 27 17:24:41 GMT--9:00 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	InterLock4PrintChanged(void);
 *	Description:
 *		Cooked Mode で プリンタ側InterLock をチェック,結果は CookedInterLock4Print
 *		5mse 割込みで記憶を更新。
 *	Return Value:
 *		TRUE:	InterLock 変化あり
 *		FALSE:	InterLock 変化無し
 *	Change Log:
 *		
 */
BOOL	InterLock4PrintChanged(void)
{
	BOOL	CurrentInterLock;			/* 現在のセンサー状態 */
	BOOL	Rtn;

	Rtn = FALSE;
	CurrentInterLock= InterLock4PrintRaw();
	if (CookedInterLock4Print != CurrentInterLock) {
		if (--InterLock4PrintCookCounter <= 0) { /* チャタリング防止の為のカウンター減算 */
			InterLock4PrintCookCounter = PsChatCount;
			CookedInterLock4Print = CurrentInterLock; /* 現在の状態を記憶 */
			Rtn = TRUE;
		}
	} else {
		InterLock4PrintCookCounter = PsChatCount;
	}
	return	Rtn;
}

/*
 *	Name:	Update Paper Postion Status
 *	Create:	Thu May 28 11:25:00 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	UpdatePaperPostion(void);
 *	Description:
 *		記録紙送り量カウントアップ 記録紙位置ステータス更新
 *		受信モーター動作後コールすること。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	UpdatePaperPosition(void)
{
	if (QueryPrinterCoverOpen()) {
		PrinterError |= PRT_ERROR_COVER_OPEN;
		PrinterEventStatus |= PRT_EVT_ERROR;
		idet_evt(EVT_PRT_IMAGE);
	}
	else {
		switch (Paper.Position) {
		case PAPER_POS_NO_PAPER:				/* 記録紙がない状態 */
			break;

		case PAPER_POS_MOVE_TO_MINI_DOC_EXIT:			/* 最小記録紙長分、記録紙排出 */
			Paper.StepsFromDocSet += RxMotorSpeedPtr->MoveLines;

#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* ＰＳ２の平均レベルを算出 by Y.kano 2004/03/01 */
			if (PS2_Vp_Count < 150) {
				if (PS2_Count < 5) {
					PS2_Count++;
				}
				else {
					PS2_Vp_Value += (UBYTE)AD_PS2();
					PS2_Vp_Count++;
					PS2_Count = 0;
				}
			}
			else {
				/* Ｖｐａｖｅの算出 */
				SYB_MachineParameter[M_PARA_SW_J3] = (UBYTE)((PS2_Vp_Value / 150));
				PS2_Vp_Value = 0;
				PS2_Vp_Count = 0;
				PS2_Count = 0;
				/* Ｖｓｉｍ２の算出 */
				SYB_MachineParameter[M_PARA_SW_J4] = (UBYTE)((0xff + SYB_MachineParameter[M_PARA_SW_J3]) / 2);
  #if (1)	/* ＰＳ２自動調整機能 by Y.Kano 2004/12/10 */
				if (SYB_PS2_SensorStatus != PS2_THRESHOLD) {
					SYB_PS2_SensorStatus = VSIM2_THRESHOLD;		/* Ｖｓｉｍ２（仮想スライスレベル）に切り替え */
				}
  #endif
			}
#endif
			if (Paper.StepsFromDocSet >= MinimumDocExitSteps) {

				/* EndMark5
				** イニシャルカット時のエンドマークチェックが抜けていた
				** by O.Kimoto 1999/03/09
				*/
#if defined(SATSUKI2)	/* エンドマークチェック用ＰＳ２チェックの追加  2003/10/23 */
				if (!EndMarkPS2Cehck()) {
#else
				if (!QueryPs2On()) {	/* Endmark2 By O.Kimoto 1999/02/11 */
#endif	/* End of defined(SATSUKI2) */
					if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {
						EndMarkDetect = TRUE;
					}
				}
				Paper.StepsFromDocSet = 0;
				Paper.Position = PAPER_POS_FEED_OUT;
				Paper.StepsFeedOut = 0;
				StopRxMotor();
				PrinterEventStatus |= PRT_EVT_CUT_ON;
				if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
					idet_evt(EVT_PRT_IMAGE);
				}
				else {
					idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
				}
			}
			break;

		case PAPER_POS_FEED_OUT:				/* 記録紙排出 */

			/*
			** Ｂ４記録紙カット時、記録紙の端がいたむ不具合
			** 1999/11/22 by T.Soneoka
			*/
			if (IsCutBack) {	/* カットバック中のとき */
				Paper.StepsFeedOut -= RxMotorSpeedPtr->MoveLines;	/* カットバックステップ減算 */
				if (Paper.StepsFeedOut <= COUNT_CUT_BACK_STEP) {	/* カットバックステップ引き戻し完了か */
					IsCutBack = FALSE;								/* カットバック終了 */
					StopRxMotor();									/* 記録紙押し出し処理（モータ逆転） */
					SetupRxMotor(RX_MOTOR_FORWARD);
					StartRxMotor();
				}
				break;
			}

			Paper.StepsFeedOut += RxMotorSpeedPtr->MoveLines;

			if (Paper.StepsFeedOut >= FeedOutDocSteps) {	/* 40mm */
				Paper.StepsFeedOut = 0;
				Paper.Position = PAPER_POS_MOVE_TO_PS2;
				Paper.BackWardStepsFromFeedOut = 0;
				backward_step_error = BackWardStepError;

/* 移植 by SMuratec K.W.Q 2003/07/29 */
#if defined(SATSUKI2)	/* SATSUKI2の場合は、印字待機位置 PS2から8.5のところ 先端のSTEPに変更 by Y.Kano 2003/07/26 */
				PaperMoveCount = PrintReadySteps;	/* 10mm *//* EndMark By O.Kimoto 1999/02/09 */
#else
				PaperMoveCount = (WORD)(FeedOutDocSteps + COUNT_CUTTER_TO_PS2);	/* 40mm + 12.2mm *//* EndMark By O.Kimoto 1999/02/09 */
#endif

				StopRxMotor();
				ChangeRxMotorPhase();
			}

#if (0)	/* Endmark6 By O.Kimoto 1999/03/11 */
** 
** 			/* EndMark5
** 			** イニシャルカット時のエンドマークチェックが抜けていた
** 			** by O.Kimoto 1999/03/09
** 			*/
** 			if (Paper.StepsFeedOut >= JAM_CheckSteps) {
** 				if (!QueryPs2On()) {	/* Endmark2 By O.Kimoto 1999/02/11 */
** 					if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {
** 						EndMarkDetect = TRUE;
** 					}
** 				}
** 			}
#endif

			break;

		case PAPER_POS_MOVE_TO_PS2:				/* ＰＳ２センサが切れるまで引き戻し */
			Paper.BackWardStepsFromFeedOut += RxMotorSpeedPtr->MoveLines;

#if (0)
** 			/* EndMark6
** 			** ＰＳ２まで記録紙を引き戻す時は、所定ステップ量引き戻すまで、ＰＳ２は見ないように変更します。
** 			** by O.Kimoto 1999/03/11
** 			*/
** #if (0)
** ** 			/* EndMark 対策その２ By O.Kimoto 1999/02/11 */
** ** 			if (Paper.BackWardStepsFromFeedOut > PaperMoveCount) [	/* EndMark By O.Kimoto 1999/02/09 */
** #else
** 			if ((EndMarkDetect == FALSE)
** 				|| ((EndMarkDetect == TRUE) && (Paper.BackWardStepsFromFeedOut > PaperMoveCount))) {	/* EndMark2 By O.Kimoto 1999/02/11 */
** #endif
#else
			if (Paper.BackWardStepsFromFeedOut > PaperMoveCount) {
#endif

				if (Paper.Route == ROUTE_PRINTING_TO_READY) {
					if (!QueryPs2On()) {
#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* PS2が切れてから１ｍｍ余分に送ります。by Y.Kano 2004/12/06 */
						if (SYS_DocumentPrintClass == SYS_PRINT_CLASS_INITIAL) {
							if (!PrtBackStepPS2Flag) {
								BackWardStepsFromPS2 = Paper.BackWardStepsFromFeedOut + SYB_MachineParameter[M_PARA_SW_B0];
								PrtBackStepPS2Flag = TRUE;
							}
							else if (Paper.BackWardStepsFromFeedOut > BackWardStepsFromPS2) {
								PrtBackStepPS2Flag = FALSE;
								Paper.BackWardStepsFromFeedOut = 0;
								Paper.Position = PAPER_POS_MOVE_TO_READY;
								Paper.StepsFromPs2On = 0;
								StopRxMotor();
								ChangeRxMotorPhase();
								PS2_Vb_Value = (UBYTE)AD_PS2();	/* Ｖｂ（記録紙無しレベル）取込み */
								SYB_MachineParameter[M_PARA_SW_J5] = PS2_Vb_Value;
 #if (1)	/* ここで、実閾値を求めます。by Y.kano 2004/12/10 */
								if (SYB_PS2_SensorStatus == VSIM2_THRESHOLD) {
									/* ＰＳ２の実スライスレベル（Ｖｓ）の算出 */
									SYB_MachineParameter[M_PARA_SW_J6] = (UBYTE)(((SYB_MachineParameter[M_PARA_SW_J5] + SYB_MachineParameter[M_PARA_SW_J3]) / 2));
									SYB_PS2_SensorStatus = PS2_THRESHOLD;	/* ＰＳ２自動調整機能実行済みフラグＯＮ */
									SensorRetryCount = 0;
								}
 #endif
							}
						}
						else {
							Paper.BackWardStepsFromFeedOut = 0;
							Paper.Position = PAPER_POS_MOVE_TO_READY;
							Paper.StepsFromPs2On = 0;
							StopRxMotor();
							ChangeRxMotorPhase();
						}
#else
						Paper.BackWardStepsFromFeedOut = 0;
						Paper.Position = PAPER_POS_MOVE_TO_READY;
						Paper.StepsFromPs2On = 0;
						StopRxMotor();
						ChangeRxMotorPhase();
#endif
					} else if (Paper.BackWardStepsFromFeedOut >= backward_step_error) {
						/*
						** ロール紙終端において、ちょうど印字終了したとき、
						** 短尺部分がPS2に残ってしまい、いつまでもPS2がONしっぱなしになる
						** ループ発生
						** 以下のように、引き戻しステップ数を監視します
						** 1999/1/14 by T.Soneoka
						*/
						/* 記録紙カットエラー */
						PrinterError |= PRT_ERROR_CUT_ERROR;
						PrinterEventStatus |= PRT_EVT_ERROR;

						/* Add By O.Kimoto 1998/12/07 */
						if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
							idet_evt(EVT_PRT_IMAGE);
						}
						else {
							idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_READY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
						}

					}
				} else {
#if defined(SATSUKI2)	/* 壁掛け設定用に追加 by Y.Kano 2003/10/09 */
					if ((!QueryPs2On()) || (CHK_WallHangSetting())) {
#else
					if (!QueryPs2On()) {
#endif
						Paper.BackWardStepsFromFeedOut = 0;
						if (Paper.Route == ROUTE_PRINTING_TO_READY) {
							Paper.Position = PAPER_POS_MOVE_TO_READY;
						} else {
							Paper.Position = PAPER_POS_MOVE_TO_PRINTING;
						}
						Paper.StepsFromPs2On = 0;
						StopRxMotor();
						ChangeRxMotorPhase();
					} else if (Paper.BackWardStepsFromFeedOut >= backward_step_error) {
						/* 記録紙カットエラー */
						PrinterError |= PRT_ERROR_CUT_ERROR;
						PrinterEventStatus |= PRT_EVT_ERROR;

						/* Add By O.Kimoto 1998/12/07 */
						if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
							idet_evt(EVT_PRT_IMAGE);
						}
						else {
							idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_READY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
						}

					}
				}
			}
			break;

		case PAPER_POS_MOVE_TO_PRINTING:		/* 記録位置まで引き戻し中 */
			Paper.StepsFromPs2On -= RxMotorSpeedPtr->MoveLines;

			if (Paper.StepsFromPs2On <= (PrintPostionSteps + Paper.TopMargin)) {
				Paper.StepsFromPrinting = 0;
				StopRxMotor();

				if (PrinterUseMode == PRINT_SCOPY) {
					/* 記録開始位置へ引き戻しが終わればとりあえず上位に通知するように変更 */
					if (IsNextPrint()) {
						PrinterEventStatus |= PRT_EVT_DOC_PRINT_POS;
						idet_evt(EVT_PRT_IMAGE);
					} else {
#if (0) /* 1999/1/19 by T.Soneoka */
**						Paper.Route = ROUTE_PRINTING_TO_READY;
#else
						Paper.Phase = PAPER_PHASE_FEED;
						Paper.Route = ROUTE_PRINTING_TO_READY;
						Paper.Position = PAPER_POS_PRINTING_TO_FEED_OUT;
#endif
						ChangeRxMotorPhase();
					}
				} else if (PrinterUseMode == PRINT_RXPRINT) {
					if (PrinterCloseRequest) {
						PrinterCloseRequest = FALSE;
						Paper.Phase = PAPER_PHASE_FEED;
						Paper.Route = ROUTE_PRINTING_TO_READY;
						Paper.Position = PAPER_POS_PRINTING_TO_FEED_OUT;
						ChangeRxMotorPhase();
					} else {
						PrinterEventStatus |= PRT_EVT_DOC_PRINT_POS;
						idet_evt(EVT_PRT_IMAGE);
					}
				} else {
					PrinterEventStatus |= PRT_EVT_DOC_PRINT_POS;
					idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_READY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
				}
			}
			break;

		case PAPER_POS_MOVE_TO_READY:		/* 記録待機位置まで移動中 */
			Paper.StepsFromPs2On += RxMotorSpeedPtr->MoveLines;
#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* ＰＳ２自動調整不具合対応 by Y.kano 2004/12/06 */
			if (SYS_DocumentPrintClass == SYS_PRINT_CLASS_INITIAL) {
				if (Paper.StepsFromPs2On >= PrintReadySteps + SYB_MachineParameter[M_PARA_SW_B0]) {
					Paper.StepsFromPs2On = 0;
					Paper.Position = PAPER_POS_MOVE_TO_PS2;
					Paper.BackWardStepsFromFeedOut = 0;
					backward_step_error = BackWardStepErrorFromReady;
					PaperMoveCount = PrintReadySteps;	/* 10mm *//* EndMark By O.Kimoto 1999/02/09 */
					
					StopRxMotor();

					PrinterEventStatus |= PRT_EVT_DOC_READY_COMPLETE;
					if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
						idet_evt(EVT_PRT_IMAGE);
					}
					else {
						idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_STANDBY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
					}
				}
			}
			else {
				if (Paper.StepsFromPs2On >= PrintReadySteps) {
					Paper.StepsFromPs2On = 0;
					Paper.Position = PAPER_POS_MOVE_TO_PS2;
					Paper.BackWardStepsFromFeedOut = 0;
					backward_step_error = BackWardStepErrorFromReady;
					PaperMoveCount = PrintReadySteps;	/* 10mm *//* EndMark By O.Kimoto 1999/02/09 */

					
					StopRxMotor();

					PrinterEventStatus |= PRT_EVT_DOC_READY_COMPLETE;
					if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
						idet_evt(EVT_PRT_IMAGE);
					}
					else {
						idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_STANDBY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
					}
				}
			}
#else
			if (Paper.StepsFromPs2On >= PrintReadySteps) {
				Paper.StepsFromPs2On = 0;
				Paper.Position = PAPER_POS_MOVE_TO_PS2;
				Paper.BackWardStepsFromFeedOut = 0;
				backward_step_error = BackWardStepErrorFromReady;
				PaperMoveCount = PrintReadySteps;	/* 10mm *//* EndMark By O.Kimoto 1999/02/09 */
				
				StopRxMotor();

				PrinterEventStatus |= PRT_EVT_DOC_READY_COMPLETE;
				if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
					idet_evt(EVT_PRT_IMAGE);
				}
				else {
					idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_STANDBY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
				}
			}
#endif	/* End of defined(HINOKI2) */
			break;

		case PAPER_POS_PRINTING:				/* 記録可能 */
			Paper.StepsFromPrinting += RxMotorSpeedPtr->MoveLines;

			if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
				CheckThermalHighTemp();
			}
#if (0) /* ３ｍ受信プリント制限処理、通信で行なうようにします  1999/02/02 by T.Soneoka */
**			if ((PrinterCloseRequest)
**			|| (PrinterError & PRT_ERROR_HIGH_TEMP)
**			|| (Check3mOver())) {
#else
			if ((PrinterCloseRequest)
			|| (PrinterError & PRT_ERROR_HIGH_TEMP)) {
#endif
				IsPrintFinish = FALSE;	/* 1998/12/26 */
				PrinterCloseRequest = FALSE;
				Paper.Position = PAPER_POS_MOVE_TO_CUT;
				Paper.StepsToCutPosFromPlaten = 0;
				StopRxMotor();
				ChangeRxMotorPhase();
			} else {
				if (Paper.StepsFromPrinting >= JAM_CheckSteps) {
					if (!QueryPs1On()) {
						/* 記録紙なしエラー */
						PrinterError |= PRT_ERROR_NO_PAPER;
						PrinterEventStatus |= PRT_EVT_ERROR;
						idet_evt(EVT_PRT_IMAGE);
					}

#if defined(SATSUKI2)	/* エンドマークチェック用ＰＳ２チェックの追加  2003/10/23 */
					if (!EndMarkPS2Cehck()) {
#else
					if (!QueryPs2On()) {	/* Endmark2 By O.Kimoto 1999/02/11 */
#endif	/* End of defined(SATSUKI2) */
						if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {
							EndMarkDetect = TRUE;
						}
					}
				}
			}
			break;
			
		case PAPER_POS_MOVE_TO_CUT:				/* 記録紙カット位置に移動中 */
			Paper.StepsFromPrinting += RxMotorSpeedPtr->MoveLines;
			Paper.StepsToCutPosFromPlaten += RxMotorSpeedPtr->MoveLines;
			
			if (Paper.StepsFromPrinting < MinimumDocExitSteps) {
				if (Paper.StepsFromPrinting >= JAM_CheckSteps) {

#if (0)
** 					/* ここではＪＡＭチェックは行わずに、記録紙無し（ＰＳ１）のみにします。
** 					** by O.Kimoto 1999/02/08
** 					*/
** 					if (!QueryPs2On()) {
** 						/* ＪＡＭエラー */
** 						PrinterError |= PRT_ERROR_JAM;
** 						PrinterEventStatus |= PRT_EVT_ERROR;
** 
** #if (0)	/* Add by O.Kimoto 1998/12/18 */
** ** 						idet_evt(EVT_PRT_IMAGE);
** #else
** 						if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
** 							idet_evt(EVT_PRT_IMAGE);
** 						} else {
** 							idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
** 						}
** #endif
** 
** 					}
#else
					if (!QueryPs1On()) {
						/* ＪＡＭエラー */
						PrinterError |= PRT_ERROR_NO_PAPER;
						PrinterEventStatus |= PRT_EVT_ERROR;
						if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
							idet_evt(EVT_PRT_IMAGE);
						} else {
							idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
						}
					}
#if defined(SATSUKI2)	/* エンドマークチェック用ＰＳ２チェックの追加  2003/10/23 */
					if (!EndMarkPS2Cehck()) {
#else
					if (!QueryPs2On()) {	/* Endmark2 By O.Kimoto 1999/02/11 */
#endif	/* End of defined(SATSUKI2) */
						if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {
							EndMarkDetect = TRUE;
						}
					}

#endif

				}
			}
			else {
#if defined(SATSUKI2)	/* エンドマークチェック用ＰＳ２チェックの追加  2003/10/23 */
				if (!EndMarkPS2Cehck()) {
#else
				if (!QueryPs2On()) {	/* Endmark2 By O.Kimoto 1999/02/11 */
#endif	/* End of defined(SATSUKI2) */
					if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {
						EndMarkDetect = TRUE;
					}
				}

				/* カット位置へ搬送中もPS1の監視が必要 By O.Kimoto 1998/12/07 */
				if (!QueryPs1On()) {
					/* 記録紙なしエラー＆記録紙はカットしません */
					PrinterError |= PRT_ERROR_NO_PAPER;
					PrinterEventStatus |= PRT_EVT_ERROR;
					if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
						idet_evt(EVT_PRT_IMAGE);
					} else {
						idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
					}
				}

				else if (Paper.StepsToCutPosFromPlaten >= (ToCutPosFromPlatenSteps + Paper.BottomMargin)) {

/*------------------< 経年変化対応 by Y.kano 2003/10/22 >-------------------------*/
#if defined(SATSUKI2)		/* 経年変化対応 by Y.Kano 2003/10/22 */
					if (CHK_YearChangeEnable()) {		/* 経年変化対応可能かチェック by Y.Kano 2003/10/31 */
						AD_PS2_StoreValue = AD_PS2();		/* 記録紙カット直前におけるＰＳ２のＡＤ値取込み。by Y.Kano 2003/10/31 */
/*					AD_PS2_Value2 = AD_PS2();	*/	/* 記録紙カット直前におけるＰＳ２のＡＤ値取込み。by Y.Kano 2003/10/22 */
/*					AD_PS2_AveValue  = (AD_PS2_Value1 + AD_PS2_Value2) / 2;*/	/* AD1とAD2との平均値を算出 by Y.Kano 2003/10/22 */
						if (AD_PS2_StoreValue <= 0x3D) {
							SYB_PS2LimitValue = PS2DEFAULT;		/* 経年変化対応のPS2デフォルト値（0x5c)のセット。*/
						}
						else if (AD_PS2_StoreValue <= 0x66) {
							SYB_PS2LimitValue = PS2_LIMIT_1;	/* 経年変化対応のPS2閾値（0x7A)のセット。*/
						}
						else {	/* AD_PS2_StoreValue <= 0x7A */
							SYB_PS2LimitValue = PS2_LIMIT_2;	/* 経年変化対応のPS2閾値（0x99)のセット。*/
						}
 #if (0)	/* 機器パラメータの変更 by Y.kano 2003/12/18 */
						SYB_MachineParameter[M_PARA_SW_J2] = SYB_PS2LimitValue;	/* マシンパラメータに現在のＰＳ２閾値を反映 by Y.Kano 2003/10/22 */
						SYB_MachineParameter[M_PARA_SW_J3] = AD_PS2_StoreValue;		/* マシンパラメータに現在のＰＳ２取込み値を反映 by Y.Kano 2003/10/31 */
 #else
						SYB_MachineParameter[M_PARA_SW_J8] = SYB_PS2LimitValue;	/* マシンパラメータに現在のＰＳ２閾値を反映 by Y.Kano 2003/10/22 */
						SYB_MachineParameter[M_PARA_SW_J9] = AD_PS2_StoreValue;		/* マシンパラメータに現在のＰＳ２取込み値を反映 by Y.Kano 2003/10/31 */
 #endif
					}
#endif	/* End of defined(SATSUKI2) */
/*------------------< 経年変化対応 by Y.kano 2003/10/22 >-------------------------*/

/*------------------< test by Y.kano 2003/10/09 >-------------------------*/
#if defined(SATSUKI2)		/* 壁掛け設定用と最小記録紙長排出ステップとを切り分ける。by Y.Kano 2003/10/09 */
					if (CHK_WallHangSetting()) { /** 壁掛け設定用 */	/* Add by Y.kano 2003/10/09 */
						if (Paper.StepsToCutPosFromPlaten >= (ToCutPosFromPlatenSteps + Paper.BottomMargin)) {
 #if (1)
							Paper.Position = PAPER_POS_MOVE_TO_READY;
							Paper.StepsFromPs2On = 0;
							Paper.StepsToCutPosFromPlaten = 0;	/* Add by Y.Kano 2003/10/27 */
 #else
							Paper.StepsFromPrinting = 0;
							Paper.StepsToCutPosFromPlaten = 0;

							Paper.Phase = PAPER_PHASE_READY;
							Paper.Route = ROUTE_PRINTING_TO_READY;
							Paper.StepsFromPs2On = 0;
							Paper.Position = PAPER_POS_MOVE_TO_PS2;

							StopRxMotor();
							PrinterEventStatus |= PRT_EVT_DOC_READY_COMPLETE;
							if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
								idet_evt(EVT_PRT_IMAGE);
							}
							else {
								idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_STANDBY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
							}
 #endif
						}
					}
					else {
						Paper.StepsFromPrinting = 0;
						Paper.StepsToCutPosFromPlaten = 0;
						PrinterEventStatus |= PRT_EVT_CUT_ON;

						StopRxMotor();

						if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
							idet_evt(EVT_PRT_IMAGE);
						} else {
							idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
						}
					}
#else
/*------------------< test by Y.kano 2003/10/09 >-------------------------*/
					Paper.StepsFromPrinting = 0;
					Paper.StepsToCutPosFromPlaten = 0;
					PrinterEventStatus |= PRT_EVT_CUT_ON;

					StopRxMotor();

					if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
						idet_evt(EVT_PRT_IMAGE);
					} else {
						idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
					}
#endif	/* End of defined(SATSUKI2) */
					if (PrinterUseMode == PRINT_SCOPY) {
 #if (0) /* 1999/1/19 by T.Soneoka */
**						if (IsNextPrint()) {
**							Paper.Position = PAPER_POS_MOVE_TO_PS2;
**							Paper.BackWardStepsFromFeedOut = 0;
**							backward_step_error = BackWardStepError;
**						} else {
**							Paper.Route = ROUTE_PRINTING_TO_READY;
**							Paper.Position = PAPER_POS_FEED_OUT;
**							Paper.StepsFeedOut = 0;
**						}
 #else

  #if (0)
** 						/* EndMark3 スキャナーコピー時、EndMarkが見れていなかった
** 						** by O.Kimoto 1999/02/19
** 						*/
** 						Paper.Position = PAPER_POS_MOVE_TO_PS2;
** 						Paper.BackWardStepsFromFeedOut = 0;
** 						backward_step_error = BackWardStepError;
** 
** 						PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);	/* 12.2mm + 3.5mm *//* EndMark By O.Kimoto 1999/02/09 */
  #else
						/*
						** 紙搬送変更 1999/04/13 by T.Soneoka
						*/
   #if (0)
**						if (EndMarkDetect == TRUE) {
   #else
						if ((EndMarkDetect == TRUE)
						|| (!IsNextPrint())) {
   #endif
   #if defined(SATSUKI2)		/* 壁掛け設定用と最小記録紙長排出ステップとを切り分ける。by Y.Kano 2003/10/09 */
							if (!CHK_WallHangSetting()) { /** 壁掛け設定用 */	/* Add by Y.kano 2003/10/09 */

								Paper.Route = ROUTE_PRINTING_TO_READY;
								Paper.Position = PAPER_POS_FEED_OUT;
								Paper.StepsFeedOut = 0;
							}
						}
   #else	/* SATSUKI2以外 */
							Paper.Route = ROUTE_PRINTING_TO_READY;
							Paper.Position = PAPER_POS_FEED_OUT;
							Paper.StepsFeedOut = 0;
						}
   #endif	/* End of defined(SATSUKI2) */
						else {
							Paper.Position = PAPER_POS_MOVE_TO_PS2;
							Paper.BackWardStepsFromFeedOut = 0;
							backward_step_error = BackWardStepError;

   #if defined(SATSUKI2)		/* 壁掛け設定用 by Y.Kano 2003/10/27 */
							if (CHK_WallHangSetting()) { /** 壁掛け設定用 */	/* Add by Y.kano 2003/10/09 */

								PaperMoveCount = PrintReadySteps;	/* 10mm *//* EndMark By O.Kimoto 1999/02/09 */
							}
							else {
								PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);	/* 12.2mm + 3.5mm *//* EndMark By O.Kimoto 1999/02/09 */
							}
   #else	/* SATSUKI2以外 */
							PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);	/* 12.2mm + 3.5mm *//* EndMark By O.Kimoto 1999/02/09 */
   #endif	/* End of defined(SATSUKI2) */
						}
  #endif

 #endif
					} else if (PrinterUseMode == PRINT_RXPRINT) {
						if (!PrinterError) {

 #if (0)
** 							/* Endmark3 プリンター受信時、EndMarkが見れていなかった
** 							** by O.Kimoto 1999/02/19
** 							*/
** 							Paper.Position = PAPER_POS_MOVE_TO_PS2;
** 							Paper.BackWardStepsFromFeedOut = 0;
** 							backward_step_error = BackWardStepError;
** 
** 							PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);	/* 12.2mm + 3.5mm *//* EndMark By O.Kimoto 1999/02/09 */
 #else
							if (EndMarkDetect == TRUE) {
								Paper.Route = ROUTE_PRINTING_TO_READY;
								Paper.Position = PAPER_POS_FEED_OUT;
								Paper.StepsFeedOut = 0;
							}
							else {
								Paper.Position = PAPER_POS_MOVE_TO_PS2;
								Paper.BackWardStepsFromFeedOut = 0;
								backward_step_error = BackWardStepError;
								PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);	/* 12.2mm + 3.5mm *//* EndMark By O.Kimoto 1999/02/09 */
							}
 #endif

						} else {
   #if defined(SATSUKI2)		/* 壁掛け設定用と最小記録紙長排出ステップとを切り分ける。by Y.Kano 2003/10/14 */
							if (!CHK_WallHangSetting()) { /** 壁掛け設定用 */	/* Add by Y.kano 2003/10/14 */
								Paper.Route = ROUTE_PRINTING_TO_READY;
								Paper.Position = PAPER_POS_FEED_OUT;
								Paper.StepsFeedOut = 0;
							}
   #else	/* SATSUKI2以外 */
							Paper.Route = ROUTE_PRINTING_TO_READY;
							Paper.Position = PAPER_POS_FEED_OUT;
							Paper.StepsFeedOut = 0;
   #endif	/* End of defined(SATSUKI2) */
						}
					} else {
   #if defined(SATSUKI2)		/* 壁掛け設定用と最小記録紙長排出ステップとを切り分ける。by Y.Kano 2003/10/14 */
						if (!CHK_WallHangSetting()) { /** 壁掛け設定用 */	/* Add by Y.kano 2003/10/14 */
							Paper.Position = PAPER_POS_FEED_OUT;
							Paper.StepsFeedOut = 0;
						}
   #else	/* SATSUKI2以外 */
						Paper.Position = PAPER_POS_FEED_OUT;
						Paper.StepsFeedOut = 0;
   #endif	/* End of defined(SATSUKI2) */
					}
				}
			}
			break;

		case PAPER_POS_PRINTING_TO_FEED_OUT:				/* 印字位置からの記録紙排出（－＞待機位置まで） */
			Paper.StepsFeedOut += RxMotorSpeedPtr->MoveLines;

			if (Paper.StepsFeedOut >= PrintingToFeedOutDocSteps) {
				Paper.StepsFeedOut = 0;
				Paper.BackWardStepsFromFeedOut = 0;	/* Add 1999/1/14 by T.Soneoka */
				backward_step_error = BackWardStepError;
				Paper.Position = PAPER_POS_MOVE_TO_PS2;

				PaperMoveCount = (WORD)(PrintingToFeedOutDocSteps + PrintPostionSteps) ;	/* *//* EndMark By O.Kimoto 1999/02/09 */

				StopRxMotor();
				ChangeRxMotorPhase();
			} else {
				/*
				** プリント原稿を押し出すとき（紙にテンションがある場合）
				** PS1サンサも見るようにします
				** 1999/1/14 by T.Soneoka
				*/
				if (!QueryPs1On()) {
					/* 記録紙なしエラー */
					PrinterError |= PRT_ERROR_NO_PAPER;
					PrinterEventStatus |= PRT_EVT_ERROR;
					idet_evt(EVT_PRT_IMAGE);
				}

#if (0)
** 				/* Endmark6 By O.Kimoto 1999/03/11 */
** 				/* Endmark2 By O.Kimoto 1999/02/11 */
** 				if(SYS_DocumentPrintClass != SYS_PRINT_CLASS_INITIAL) {
** 					if (Paper.StepsFeedOut >= ToCutPosFromPlatenSteps) {
** 						if (!QueryPs2On()) {
** 							if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {
** 								EndMarkDetect = TRUE;
** 
** #if (0)
** ** 								/* Endmark4
** ** 								** ここでは、PS2をチェックして、Endmarkの場合はフラグをセットするだけでよい。
** ** 								** by O.Kimoto 1999/03/04
** ** 								*/
** ** 								PrinterError |= PRT_ERROR_NO_PAPER;
** ** 								PrinterEventStatus |= PRT_EVT_ERROR;
** ** 								idet_evt(EVT_PRT_IMAGE);
** #endif
** 							}
** 						}
** 					}
** 				}
#endif

			}
			break;

		default:
			break;
		}
	}

	if (PrinterError & (~PRT_ERROR_HIGH_TEMP)) {
		StopRxMotor();
	}
}


/*
 *	Name:	Check Printable Paper Position
 *	Create:	Tue Jun 02 13:35:33 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	CheckPrintablePosition(void);
 *	Description:
 *		記録紙が印字可能な位置にあるか？
 *	Return Value:
 *		TRUE:	印字可能
 *		FALSE:	印字不可
 *	Change Log:
 *		
 */
BOOL	CheckPrintablePosition(void)
{
	BOOL	Rslt;

	Rslt = FALSE;
	if (Paper.Phase == PAPER_PHASE_PRINT) {
		if (Paper.Position == PAPER_POS_PRINTING) {/* 記録可能 */
			Rslt = TRUE;
		}
	}
	return	Rslt;
}

/*----------------------------------------------------------------------------
 *	Thermal Head Control
 *---------------------------------------------------------------------------*/
/*
 *	Name:	Print 1 Line
 *	Create:	Fri May 29 15:54:27 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	Print1Line(void);
 *	Description:
 *		１ラインプリント
 *	Notes:
 *		EnableIntPbrdy(),EnableIntPrinterTimer() がコールされ、
 *		PBRDY, Printer 5msec Timer割り込みが有効になっていること。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	Print1Line(void)
{
	UBYTE	*ImagePtr;
	UWORD	*PrintBufPtr;
	UBYTE	white_mask; 		/* 1999/01/05 by T.Soneoka */
	UBYTE	print_exec; 		/* 1998/12/16 by T.Soneoka */
	UWORD	Status;

	StrobeTime = 0;						/* 印可したかどうかを示すフラグ Restrobe でのみ使用 */
	motor_stop_request = 0;				/* 1999/03/01 by T.Soneoka */
	print_exec = FALSE;					/* 初期化不良不具合 1999/05/26 by T.Soneoka */

	CancelToMoveRxMotor();				/* Not Move RxMotor(Default) */

	/* Strobe Monitor Check */
	if (!QueryStrobeOn()) {
		/* 印可中じゃない */
		if (CheckPrinteDmaPermission()) {
			PBRDY_Count = 0;			/* ＧＩＮＴがとまる対策  1999/01/27 by T.Soneoka */
			if (!(GaTphStatus & TPH_SYNC)) {
				if (!DtcPermission) {	/* ＤＴＣの終了割り込みを確認します  1998/12/11 by T.Soneoka */
					return;
				}
			}

/*
** 京セラＴＰＨ２度書き対応は取りやめます
** 1999/03/15 by T.Soneoka
*/
#if (0)
**			/* 1999/03/02 by T.Soneoka */
**			if (!PreHeatInsertForKyocera) {
**				OutputWORD(GA_SWR, (((SYB_MaintenanceSwitch[MNT_SW_H3]) << 3) | SWR_STREN | SWR_PRTEN));
**				PreHeatInsertForKyocera = TRUE;
**				ExecPrintOnTiming = 2;
**				return;
**			}
#endif
			/* Printer DMA 許可 */
			switch (PrinterRewriteCount) {
			case 1:						/* DMA,Strobe,MotorMove */
				/* プリンタ受信時の黒すじ対策
				** ＨＩＮＯＫＩは１ライン５ｍｓで印字可能であるが
				** ライン５ｍｓの設定で間欠送りをした場合、黒スジが入る対策
				** 1998/12/21 by T.Soneoka
				*/
				if (PrinterUseMode == PRINT_RXPRINT) {
/*
** プリンタ受信時のクリアモードと最後の処理を修正します
** 1999/03/09 by T.Soneoka
*/
#if (0)
**					if (PrintBufferClearMode) {
**						print_exec = TRUE;
**						PrintExecute = FALSE;
**						print_count = 0;
**						PreHeatPhase = 0;
**					} else {
#else
					if (PrintBufferClearMode) {
						ExecPrintOnTiming = 1;
						PrintExecute = FALSE;
						print_exec = FALSE;
						if (EnableToReadPrtImageBuf()) {
							print_exec = TRUE;
						}
					} else if (IsPrintFinish) {
						print_exec = FALSE;
						if (EnableToReadPrtImageBuf()) {
							print_exec = TRUE;
						}
					} else {
#endif
						ExecPrintOnTiming--;
						print_exec = FALSE;
						if (!ExecPrintOnTiming) {
							if (RxECM_Mode == ECM_ON) {
								if (FaxComPhaseStatus == FAX_RX_PH_D) {
									if (EnableToReadPrtImageBuf()) {
										PreHeatPhase = 1;
										used_count = GetPrtImageBufUsedCount();
										print_exec = TRUE;
										if (used_count >= 25) {
											if (PrintTiming < PRINT_TIMING_MIN) {
												++PrintTiming;
											}
											ExecPrintOnTiming = PrintThoughUpTable[PrintTiming];
										} else if (used_count >= 10) {
											if (pre_used_count < used_count) {
												if (PrintTiming < PRINT_TIMING_MIN) {
													++PrintTiming;
												}
												ExecPrintOnTiming = PrintThoughUpTable[PrintTiming];
											} else if (pre_used_count > used_count) {
												if (PrintTiming > PRINT_TIMING_MAX) {
													--PrintTiming;
												}
												ExecPrintOnTiming = PrintThoughDownTable[PrintTiming];
											} else {
												ExecPrintOnTiming = PrintThoughDownTable[PrintTiming];
											}
										} else {
											if (pre_used_count <= used_count) {
												PrintTiming = PRINT_TIMING_MAX;
												ExecPrintOnTiming = PrintThoughUpTable[PrintTiming];
											} else if (pre_used_count > used_count) {
												if (PrintTiming > PRINT_TIMING_MAX) {
													--PrintTiming;
												}
												ExecPrintOnTiming = PrintThoughDownTable[PrintTiming];
											} else {
												ExecPrintOnTiming = PrintThoughDownTable[PrintTiming];
											}
										}
									} else {
										PreHeatPhase = 0;
									}
									PrintExecute = FALSE;
								} else {
									PreHeatPhase = 0;
									PrintTiming = 16;
									ExecPrintOnTiming = 4;	/* 20ms */
									if (!PrintExecute) {
										print_count = GetPrtImageBufUsedCount();
#if (0) /* 1999/03/11 by T.Soneoka */
**										if (print_count >= 20) {
#else
										if (print_count >= 2) {
#endif
											PrintExecute = TRUE;
										}
									}
									if (PrintExecute) {
										--print_count;
										print_exec = TRUE;
									}
									if (!print_count) {
										print_count = GetPrtImageBufUsedCount();
										PrintExecute = FALSE;
										ExecPrintOnTiming = 20;	/* 100ms */
									}
								}
							} else {
/*
** 制御をイメージプリントＦｉｎｅと同じ処理にします
** 1999/03/09 by T.Soneoka
*/
								if (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x80) {
									if (EnableToReadPrtImageBuf()) {
										ExecPrintOnTiming = 1;	/* 次の印字は５ｍｓ */
										if (PrintExecute) {
											print_exec = TRUE;
											used_count = GetPrtImageBufUsedCount();

											if (used_count == 2) { /* 最後のライン */
												motor_stop_request = 1;
												PrintExecute = FALSE;
												ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f); /* 休みます */
											}

										} else {
											PrintExecute = FALSE;
											used_count = GetPrtImageBufUsedCount();
											if (used_count >= (SYB_MaintenanceSwitch[MNT_SW_H6] & 0x0f)+1) {
												/* モータだけ先に回しておき、プリント処理は次の５ｍｓで行なう処理 */
												RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
												PrintExecute = TRUE;
												print_exec = FALSE; 
											}
										}
									} else {
										PrintExecute = FALSE;
										ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f); /* 休みます */
									}
								} else {
#if (0) /* 1999/03/11 by T.Soneoka */
**									ExecPrintOnTiming = 1;
#else
									ExecPrintOnTiming = 4; /* 20ms */
#endif
									if (EnableToReadPrtImageBuf()) {
										print_exec = TRUE;
									}
								}
							}
						}
					}
/* コードはなくしておきますが、いつ復活するかわからないので残します 1999/03/03 by T.Soneoka */
#if (0)
**				} else if ((PrinterUseMode == PRINT_IMAGE) && (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x10)) {
**					/*
**					** イメージプリント時の騒音対策をします
**					**  1999/02/24 by T.Soneoka
**					*/
**					if (PrintBufferClearMode) {
**						print_exec = TRUE;
**						ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f);
**						PrintExecute = FALSE;
**					} else if (IsPrintFinish) {
**						print_exec = FALSE;
**						if (EnableToReadPrtImageBuf()) {
**							print_exec = TRUE;
**						}
**					} else {
**						print_exec = FALSE;
**						ExecPrintOnTiming--;
**						if (!ExecPrintOnTiming) {
**							if (EnableToReadPrtImageBuf()) {
**								if (PrintExecute) {
**									print_exec = TRUE;
**									ExecPrintOnTiming = 1;	/* 次の印字は５ｍｓ */
**								} else {
**									used_count = GetPrtImageBufUsedCount();
**									if (used_count >= 3) {
**										PrintExecute = TRUE;
**										print_exec = TRUE;
**										ExecPrintOnTiming = 2; /* 次の印字は１０ｍｓ */
**									} else {
**										PrintExecute = FALSE;
**										ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f);
**									}
**								}
**							} else {
**								PrintExecute = FALSE;
**								ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f);
**							}
**						}
**					}
**				} else if ((PrinterUseMode == PRINT_IMAGE) 
**				        && (PageQ.Mode != SYS_NORMAL) 
**				        && (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x20)) {
**					/*
**					** イメージプリント時の騒音対策をします
**					**  1999/02/24 by T.Soneoka
**					*/
**					if (PrintBufferClearMode) {
**						print_exec = TRUE;
**						ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f);
**						PrintExecute = FALSE;
**					} else if (IsPrintFinish) {
**						print_exec = FALSE;
**						if (EnableToReadPrtImageBuf()) {
**							print_exec = TRUE;
**						}
**					} else {
**						print_exec = FALSE;
**						ExecPrintOnTiming--;
**						if (!ExecPrintOnTiming) {
**							ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f);
**							print_count = GetPrtImageBufUsedCount();
**							if (print_count > 1) {
**								print_exec = TRUE;
**							}
**						}
**					}
#endif
				} else if ((PrinterUseMode == PRINT_IMAGE) 
						&& ((Paper.Mode == SYS_FINE) || (Paper.Mode == SYS_GRAY64))
				        && (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x40)) {
					/*
					** イメージプリント時の騒音対策をします
					**  1999/02/24 by T.Soneoka
					*/
					if (PrintBufferClearMode) {
/*
** 位相ずれ不具合 PrtImageBufUsedCountを見ずに印字処理に移ると、リードポインタだけが進んでしまう
** by T.Soneoka
*/
#if (0)
**						print_exec = TRUE;
**						ExecPrintOnTiming = 1;
**						PrintExecute = FALSE;
#else
						ExecPrintOnTiming = 1;
						PrintExecute = FALSE;
						print_exec = FALSE;
						if (EnableToReadPrtImageBuf()) {
							print_exec = TRUE;
						}
#endif
					} else if (IsPrintFinish) {
						print_exec = FALSE;
						if (EnableToReadPrtImageBuf()) {
							print_exec = TRUE;
						}
					} else {
						print_exec = FALSE;
						ExecPrintOnTiming--;
						if (!ExecPrintOnTiming) {
							if (EnableToReadPrtImageBuf()) {
								ExecPrintOnTiming = 1;	/* 次の印字は５ｍｓ */
								if (PrintExecute) {
									print_exec = TRUE;
									used_count = GetPrtImageBufUsedCount();

									if (used_count == 2) { /* 最後のライン */
										motor_stop_request = 1;
										PrintExecute = FALSE;
										ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f); /* 休みます */
									}

								} else {
									PrintExecute = FALSE;
									used_count = GetPrtImageBufUsedCount();
#if (0) /* 1999/03/03 by T.Soneoka */
**									if (used_count >= 4) {
#else
									if (used_count >= (SYB_MaintenanceSwitch[MNT_SW_H6] & 0x0f)+1) {
#endif
										/* モータだけ先に回しておき、プリント処理は次の５ｍｓで行なう処理 */
										RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
										PrintExecute = TRUE;
										print_exec = FALSE; 
									}
								}
							} else {
								PrintExecute = FALSE;
								ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f); /* 休みます */
							}
						}
					}
				} else {
					if (IsPrintFinish) {
						ExecPrintOnTiming = 1;
						print_exec = FALSE;
						if (EnableToReadPrtImageBuf()) {
							print_exec = TRUE;
						}
					} else {
						print_exec = FALSE;					/* 初期化不良不具合 1999/05/26 by T.Soneoka */
						ExecPrintOnTiming--;
						if (!ExecPrintOnTiming) {
							ExecPrintOnTiming = 1;	/* 次の印字は５ｍｓ */
							print_exec = FALSE;
							if (EnableToReadPrtImageBuf()) {
								print_exec = TRUE;
/*
** 京セラＴＰＨ２度書き対応は取りやめます
** 1999/03/15 by T.Soneoka
*/
#if (0)
**								/* 京セラＴＰＨ不具合対応
**							　	** ＴＰＨサーミスタ検出が一定温度以下（値Ｔ以上）の時は、同じラインを２度書きする
**							　	** ＝強制的にプリヒート（時間ｔ）を挿入する
**								** Ｔ および ｔ はメモリスイッチにより可変として下さい．
**								** デフォルト値は、以下の値として下さい
**								** Ｔ＝４６（２Ｅｈ）　　　２０℃（判定値４６以上で２０℃以下です）
**								** ｔ＝５０（３２ｈ）　　　０．５ｍｓ
**								** 1998/12/21 by T.Soneoka
**								*/
**								if ((HeadMaker == HEAD_KYOCERA)
**								&&  (!PrintBufferClearMode)) {
**									if (PreHeatInsertForKyocera) {
**										ThermistorValue = AD_Thermistor();
**										if (ThermistorValue >= (SYB_MaintenanceSwitch[MNT_SW_H2]*4)) {
**											PreHeatInsertForKyocera = FALSE;
**										}
**									}
**								}
#endif

							}
						}
					}
				}
				
				if (print_exec) {

					if (PrintDtc) {
						/* ＤＴＣ転送起動（ＤＴＣ転送はラッチイネーブルの前で行うこと） */
						DMA_RequestMask(DMA_GATEARRAYWRITE_CH);
						ImagePtr = GetReadPtrPrtImageBuf();
						PrtImageBufReadLineAddress = (UDWORD)ImagePtr; /* for debug by H.Hirao 1998/12/04 */
						DtcPermission = FALSE;
						/* 左側Ａ４マスク設定を入れます 1999/01/05 by T.Soneoka */
						if (Paper.Size == PAPER_SIZE_A4) {
							for (white_mask = 0; white_mask < CHK_PrinterMaskWhite(); white_mask++) {
								*(ImagePtr+OffsetA4+white_mask) = 0;
							}
						}
						/* プリントループ調査用 add 2 line 1999/1/25 by T.Soneoka */
						if (SYB_MaintenanceSwitch[MNT_SW_H5] & 0x80) {
							RelayPortStatus |= 0x4000;
							OutputWORD(GA_PGADR, RelayPortStatus);
						}

						DMA_RestartDMAU(DMA_GATEARRAYWRITE_CH,
										DMA_MEMORY_TO_IO,
										PrtDataTrasCount,
										(UDWORD)ImagePtr);
					}
					if (PrintBufferClearMode) {
						PrinterDmaPermission = FALSE; /* Printer DMA 禁止 LATCH のあと必ず PBReady 割込みがある */
						OutputWORD(GA_SWR, (SWR_LATEN));
						PrinterRewriteCount++;
					} else {
						StrobeTime = CalcStrobeTime();
						/* モーターが励磁してないとき、印可しない */
						if (GaRmrStatus & RMEXCT) {			/* Rx Motor 励磁中 */
							PrinterDmaPermission = FALSE; /* Printer DMA 禁止 LATCH のあと必ず PBReady 割込みがある */
							OutputWORD(GA_SWR, ((StrobeTime << 3) | SWR_STREN | SWR_PRTEN | SWR_LATEN));
						}
						/*
						** プリント中ループ ＤＴＣだけ起動を行って、ラッチがかからない不具合
						** 1999/02/04 by T.Soneoka
						*/
						else {
							PrinterDmaPermission = FALSE; /* Printer DMA 禁止 LATCH のあと必ず PBReady 割込みがある */
							OutputWORD(GA_SWR, (SWR_LATEN));
						}
/* 移植 by SMuratec K.W.Q 2003/07/24 */
#if defined(SATSUKI2)	/* SATSUKI2ではプリンタ割込みを10msecに変更しているのでSYS_SFINEの処理を外します。O.Oshima 2003/07/09 */
						if (!motor_stop_request) {
							RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
						}
						PrinterRewriteCount++;
#else
						/*
						** ＳＦＩＮＥは１００ｐｐｓ ２相なので、
						** １０ｍｓで１Ｓｔｅｐ （１／７．７ｍｍ ＦＩＮＥ分）まわせばよい
						*/
						if (Paper.Mode == SYS_SFINE) {
							if (PrinterSkipCount == 0) {
 #if (0)	/* 1999/03/01 プリント騒音対策 */
**								RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
 #else
								if (!motor_stop_request) {
									RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
								}
 #endif
								PrinterRewriteCount++;
								PrinterSkipCount = 2;
							}
							PrinterSkipCount--;
						} else {
 #if (0)	/* 1999/03/01 プリント騒音対策 */
**							RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
 #else
							if (!motor_stop_request) {
								RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
							}
 #endif
							PrinterRewriteCount++;
						}
#endif	
					}


					if (!PrintDtc) {
						IsEventPrintDataTras = 1;
						idet_evt(EVT_PRT_DATA_TRANS);
					}
				} else {
					/* プリントイメージなし */
					if ((!PrintBufferClearMode) &&
						(!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP))) {
						/* Pre Heat */
						StrobeTime = CalcPreHeatStrobeTime();
						/* モーターが励磁してないとき、印可しない */
						if (GaRmrStatus & RMEXCT) {			/* Rx Motor 励磁中 */
							OutputWORD(GA_SWR, ((StrobeTime << 3) | SWR_STREN | SWR_PRTEN));
						}
					}
					if (IsPrintFinish) {
						IsPrintFinish = FALSE;
						SetPrinterCloseRequest();

						/*
						** プリント中ループ対策 
						** １ページ終了状態で２ページ目に入らないようにする
						** 1999/02/04 by T.Soneoka
						*/
						PrinterDmaPermission = FALSE;
						DtcPermission = FALSE;
						
						
#if (0)	/* 1999/03/01 プリント騒音対策 */
**						RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
#else
						if (!motor_stop_request) {
							RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
						}
#endif
						PrinterRewriteCount++;
					}
				}
				break;

			case 2:
				if (PrintBufferClearMode) {
					if (!QuerySmoothingOn()) {
						if (PrintDtc) {
							/* ＤＴＣ転送起動（ＤＴＣ転送はラッチイネーブルの前で行うこと） */
							DMA_RequestMask(DMA_GATEARRAYWRITE_CH);
							ImagePtr = GetReadPtrPrtImageBuf();
							PrtImageBufReadLineAddress = (UDWORD)ImagePtr; /* for debug by H.Hirao 1998/12/04 */
							DtcPermission = FALSE;

							/* プリントループ調査用 add 2 line 1999/1/25 by T.Soneoka */
							if (SYB_MaintenanceSwitch[MNT_SW_H5] & 0x80) {
								RelayPortStatus |= 0x4000;
								OutputWORD(GA_PGADR, RelayPortStatus);
							}

							DMA_RestartDMAU(DMA_GATEARRAYWRITE_CH,
											DMA_MEMORY_TO_IO,
											PrtDataTrasCount,
											(UDWORD)ImagePtr);
						}
					}
					/* Latch Only */						
					PrinterDmaPermission = FALSE; /* Printer DMA 禁止 LATCH のあと必ず PBReady 割込みがある */
					OutputWORD(GA_SWR, (SWR_LATEN));
					PrinterRewriteCount++;
				} else {
					StrobeTime = CalcStrobeTime();
					/* モーターが励磁してないとき、印可しない */
					if (GaRmrStatus & RMEXCT) {/* Rx Motor 励磁中 */
						if (QuerySmoothingOn()) {
							PrinterDmaPermission = FALSE; /* Printer DMA 禁止 LATCH のあと必ず PBReady 割込みがある */
							OutputWORD(GA_SWR, ((StrobeTime << 3) | SWR_LATEN | SWR_STREN | SWR_PRTEN));
						} else {
							OutputWORD(GA_SWR, ((StrobeTime << 3) | SWR_STREN | SWR_PRTEN));
						}
					}
					/*
					** プリント中ループ ＤＴＣだけ起動を行って、ラッチがかからない不具合
					** 1999/02/04 by T.Soneoka
					*/
					else {
						if (QuerySmoothingOn()) {
							PrinterDmaPermission = FALSE; /* Printer DMA 禁止 LATCH のあと必ず PBReady 割込みがある */
							OutputWORD(GA_SWR, (SWR_LATEN));
						}
					}
						
#if (0)	/* 1999/03/01 プリント騒音対策 */
**					RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
#else
					if (!motor_stop_request) {
						RequestToMoveRxMotor();	/* 受信モーター１ステップ送り */
					}
#endif
					PrinterRewriteCount++;
				}
				break;

			default:
				break;
			}
			if (PrinterRewriteCount > Paper.RewriteCount) {
				PrinterRewriteCount = 1;
			}
		} else {
			/*
			** ＧＩＮＴ（プリンタループ）がとまる対策  1999/01/27 by T.Soneoka
			** ＤＴＣ終了割り込みが入ってきていて、ＧＩＮＴ（ＰＢＲＤＹ）割り込みが入ってこない場合
			** ＤＴＣ終了割り込みから２回目でＧＩＮＴのステータスクリアを実行して
			** ＧＩＮＴ（ＰＢＲＤＹ）が入ってきたときと同じ処理をします
			*/
			if (DtcPermission) {
				PBRDY_Count++;
				if (PBRDY_Count >= 2) {
					PBRDY_Count = 0;
					Status = InputWORD(GA_INT_STA);	/* G/A割込みステータス・ポート */
					OutputWORD(GA_INT_REC, Status);	/* 割込み受領 */
#if (0) /* Ｇ／Ａ調査用 */
**					while (1) {
**						Status = InputWORD(GA_INT_STA);	/* G/A割込みステータス・ポート */
**						if (Status & IO_BIT_PBRDY) {
**							SYB_MaintenanceSwitch[MNT_SW_H5] |= 0x02;
**							OutputWORD(GA_INT_REC, Status);	/* 割込み受領 */
**						} else {
**							OutputWORD(GA_INT_REC, Status);	/* 割込み受領 */
**							break;
**						}
**					}
#endif
					PrinterPbreadyInt();
					SYB_MaintenanceSwitch[MNT_SW_H5] |= 0x01;
				}
			} else {
				PBRDY_Count = 0;
			}
		}
	} else {
		ExecPrintOnTiming = 2; /* １０ｍｓ後にプリントするようにします 1999/03/03 by T.Soneoka */
	}
}


/*
 *	Name:	Watch Continuous Strobe Failer
 *	Create:	Tue Jun 02 12:59:45 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	WatchContinuousStrobe(void);
 *	Description:
 *		連続印可していないことの確認
 *	Return Value:
 *		TRUE:	正常
 *		FALSE:	異常(ただし、Entry に飛ばすので、実際には帰らない)
 *	Change Log:
 *		
 */
BOOL	WatchContinuousStrobe(void)
{
	BOOL	Rslt;

	Rslt = TRUE;
	if (QueryStrobeOn()) {
		/* 印可中 */
		if (++ContinuousStrobeCount >= AbnormalStrobeCount) {
			Rslt = FALSE;
			/*
			 *	サーマルヘッド、ストローブ出放し。
			 *	超危険。
			 */
			OutputWORD(GA_SWR, 0x0000);	/* Strobe 幅０ & 禁止 */
			OutputWORD(GA_RST, 0x0001);	/* GateArray Reset */
			OutputWORD(GA_RST, 0x0000);	/* GateArray Reset */
			/*
			 *	ここでエントリーに飛ばす。
			 */
#if (0) /* リセットにせずプリンタエラー扱いにします */
**			SaveReturnAddressAndJumpBegin();	/* なったらアカンの */
#endif
		}
	} else {
		/* 印可中じゃない */
		ContinuousStrobeCount = 0;
	}
	return	Rslt;
}

/*
 *	Name:	Query Strobe Monitor On
 *	Create:	Fri May 29 16:08:02 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOl	QueryStrobeOn(void);
 *	Description:
 *		ストローブ中かどうか
 *	Return Value:
 *		TRUE:	ストローブ出力中
 *		FALSE:	ストローブはでてない
 *	Change Log:
 *		
 */
BOOL	QueryStrobeOn(void)
{
	BOOL	Rslt;

	if ((SYB_MaintenanceSwitch[MNT_SW_H0] & RX_TEST_MODE)
	&&  (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_TPH_SYNC)) {
		Rslt = FALSE;
	} else {
		if (InputWORD(GA_STRM) & STRM_STRMON) {
			Rslt = TRUE;
		} else {
			Rslt = FALSE;
		}
	}
	return	Rslt;
}

/*
 *	Name:	Caluclate Strobe Pulse Time
 *	Create:	Fri May 29 16:59:10 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		UBYTE	CalcStrobeTime(void);
 *	Description:
 *		ストローブパルス幅を計算して、返す
 *	Return Value:
 *		UBYTE	0-255
 *	Change Log:
 *		
 */
UBYTE	CalcStrobeTime(void)
{
	WORD	Time;

	ThermistorValue = AD_Thermistor();

	if (ThermistorValue >= 255) {
		ThermistorValue = 255;
	}

/*
** 新王子製記録紙使用時の白筋対策 
** ヒートパルスを余分に入れて対応していたが（1999/03/02 by T.Soneoka）
** 中間調コピーのときはヒートパルスをはずす 1999/03/05 by T.Soneoka Ｅ設並川依頼
*/
#if (0)
**	switch (Paper.Mode) {
**	case SYS_NORMAL:
**		Time = StrobeNormal[HeadMaker][ThermistorValue];
**		break;
**	case SYS_FINE:
**	case SYS_GRAY64:
**		Time = StrobeFine[HeadMaker][ThermistorValue];
**		break;
**	case SYS_SFINE:
**		Time = StrobeSfine[HeadMaker][ThermistorValue];
**		break;
**	default:
**		/* not reached */
**		Time = StrobeNormal[HeadMaker][ThermistorValue];	/* for failsafe */
**		break;
**	}
**
**	/*
**	** 新王子製記録紙使用時の白筋対策 
**	** ヒートパルスを余分に入れて対応 1999/03/02 by T.Soneoka
**	*/
**	Time += 0x20;
#else
	switch (Paper.Mode) {
	case SYS_NORMAL:
		Time = StrobeNormal[HeadMaker][ThermistorValue];
		Time += 0x20; /* 1999/03/05 by T.Soneoka */
		break;
	case SYS_FINE:
		Time = StrobeFine[HeadMaker][ThermistorValue];
		Time += 0x20; /* 1999/03/05 by T.Soneoka */
		break;
	case SYS_GRAY64:
		Time = StrobeFine[HeadMaker][ThermistorValue];
		/* 中間調は下駄をはかしません */
		break;
	case SYS_SFINE:
		Time = StrobeSfine[HeadMaker][ThermistorValue];
		Time += 0x20; /* 1999/03/05 by T.Soneoka */
		break;
	default:
		/* not reached */
		Time = StrobeNormal[HeadMaker][ThermistorValue];	/* for failsafe */
		Time += 0x20; /* 1999/03/05 by T.Soneoka */
		break;
	}
#endif
#if defined(HINOKI2) || defined (HINOKI3)	/* LC821033仕様対応 Y.Kano 2004/03/16 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2004/03/16 */
		if (PrinterUseMode == PRINT_SCOPY) {	/* スキャナーコピーの時 */
			if (Paper.Mode != SYS_GRAY64) {
				Time -= 40;
				if (Time < 0) {
					Time = 5;
				}
			}
		}
	}
#endif	/* End of defined(HINOKI2) */

	if (CHK_HeatPulseAdjust() & 0x80) {
		Time += (WORD)(CHK_HeatPulseAdjust() & 0x7f);
	} else {
		Time -= (WORD)(CHK_HeatPulseAdjust() & 0x7f);
	}
	
#if (0) /* Ｍｉｎ／Ｍａｘの値を設定が不完全だったのを修正。 ２５０にするとプリントが５ｍｓ周期で印字できない */
**	if (Time < 0) {
**		Time = 0;
**	}
**	if (Time > 250) {
**		Time = 250;
**	}
#else
	if (HeadMaker == HEAD_ROHM) {
		if (Time < 0) {
			Time = 5;
		}
		if (Time > 230) {
			Time = 230;
		}
	} else { /* HEAD_KYOCERA */
		if (Time < 0) {
			Time = 4;
		}
/*
** ２４０μｓにすると、５ｍｓ以内にストローブが完了しないことがある為
**  1999/03/04 by T.Soneoka
*/
#if (0)
**		if (Time > 240) {
**			Time = 240;
**		}
#else
		if (Time > 230) {
			Time = 230;
		}
#endif
	}
#endif

	return	(UBYTE)Time;
}

/*
 *	Name:	Caluclate Pre Heat Strobe Pulse Time
 *	Create:	Mon Jun 01 14:36:35 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		UBYTE	CalcPreHeatStrobeTime(void);
 *	Description:
 *		プリヒート時のストローブパルス幅を返す
 *	Return Value:
 *		UBYTE	0-255
 *	Change Log:
 *		
 */
UBYTE	CalcPreHeatStrobeTime(void)
{
	UBYTE	debug;
	UBYTE	Time;
	
#if (0)
**	return (head_preheat);
#else
	Time = CalcStrobeTime();

#if (0) /* 1999/1/11 by T.Soneoka */
**	if (PrinterUseMode == PRINT_RXPRINT) {
**		Time = (Time / 5);
**		if (PreHeatPhase == 0) {
**			Time += 3;
**		}
**	} else {
**		Time = (Time / 5);
**	}
#else
/* 
** イメージプリント時の２値のプリヒート変更
** 並川からの依頼 1999/02/08 by T.Soneoka
*/
#if (0)
**	switch (PrinterUseMode) {
**	case PRINT_IMAGE:
**	case PRINT_LIST:
**	case PRINT_LISTIMAGE:
**		Time = (Time / 5);
**		if (SYB_MaintenanceSwitch[MNT_SW_H4]) {
**			Time += (UBYTE)SYB_MaintenanceSwitch[MNT_SW_H4];
**		} else {
**			Time += 0x0a;	/* 並川からの依頼 1999/1/13 by T.Soneoka */
**		}
**		break;
**	case PRINT_SCOPY:
**		Time = (Time / 5);
**		break;
**	case PRINT_RXPRINT:
**	default:
**		Time = (Time / 5);
**		if (PreHeatPhase == 0) {
**			Time += 3;
**		}
**		break;
**	}
#else
 #if defined(SATSUKI2)	/* マシンパラメータSWで時間を割る数を設定可能。by Y.Kano 2003/09/30 */
	if (SYB_MachineParameter[M_PARA_SW_I0]) {
		Time = (Time/SYB_MachineParameter[M_PARA_SW_I0]);
	}
	else {
		Time = (Time / 5);
	}
 #else
	Time = (Time / 5);
 #endif	/* End of defined(SATSUKI2) */

	if (SYB_MaintenanceSwitch[MNT_SW_H4]) {
		Time += (UBYTE)SYB_MaintenanceSwitch[MNT_SW_H4];
	} else {
		switch (PrinterUseMode) {
		case PRINT_IMAGE:
			switch (PageQ.Mode) {
			case SYS_NORMAL:
			case SYS_FINE:
			case SYS_SFINE:
				Time += 0x18;
				break;
			case SYS_GRAY16:
			case SYS_GRAY16_SEP:
			case SYS_GRAY64:
			case SYS_GRAY64_SEP:
/* 1999/03/03 by T.Soneoka */
#if (0)
**				Time += 0x0a;
#endif
				break;
			}
			break;
		case PRINT_LIST:
		case PRINT_LISTIMAGE:
			Time += 0x0a;
			break;
		case PRINT_SCOPY:
			/* 
			** 新王子紙、白抜け対策
			** Ｂ４－＞Ａ４縮小（等倍はなし）
			** スキャナコピー（マルチコピーはなし）
			** ２値ＦＩＮＥ・ＳＦＩＮＥ（Ｎｏｒｍはなし）
			** の条件で＋３８のプリヒートオフセットを入れます （Ｅ設並川より依頼）
			** 1999/03/05 by T.Soneoka
			*/
			if (ScanReduction == REDUCTION_B4_A4) {
				switch (PageQ.Mode) {
				case SYS_NORMAL:
					break;
				case SYS_FINE:
				case SYS_SFINE:
					Time += 0x38;
					break;
				case SYS_GRAY16:
				case SYS_GRAY16_SEP:
				case SYS_GRAY64:
				case SYS_GRAY64_SEP:
					break;
				}
			}
			break;
		case PRINT_RXPRINT:
#if (0) /* 1999/03/11 by T.Soneoka */
**			if (PreHeatPhase == 0) {
**				Time += 3;
**			}
#else
			if (RxECM_Mode == ECM_ON) {
				if (PreHeatPhase == 0) {
					Time += 0x03;
				}
			} else {
				switch (PageQ.Mode) {
				case SYS_NORMAL:
					Time += 0x03;
					break;
				case SYS_FINE:
				case SYS_SFINE:
				case SYS_GRAY16:
				case SYS_GRAY16_SEP:
				case SYS_GRAY64:
				case SYS_GRAY64_SEP:
					break;
				}
			}
#endif
			break;
		default:
			break;
		}
	}
#endif
#endif

#if (0) /* Ｍｉｎ／Ｍａｘの値を設定が不完全だったのを修正。 ２５０にするとプリントが５ｍｓ周期で印字できない */
**	if (Time < 0) {
**		Time = 0;
**	}
**	if (Time > 250) {
**		Time = 250;
**	}
#else
	if (HeadMaker == HEAD_ROHM) {
		if (Time < 0) {
			Time = 5;
		}
		if (Time > 230) {
			Time = 230;
		}
	} else { /* HEAD_KYOCERA */
		if (Time < 0) {
			Time = 4;
		}
		if (Time > 240) {
			Time = 240;
		}
	}
#endif

	return (Time);
#endif
}


/*
 *	Name:	Initialize Print Buffers
 *	Create:	Mon Jun 01 19:57:53 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	InzPrintBuffers(void);
 *	Description:
 *		Print Buffer, ShiftRegister, LatchRegister を全白で埋める
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzPrintBuffers(
	UBYTE	Size)
{
	UBYTE	*ImagePtr;
	UWORD	*PrintBufPtr;
	UBYTE	white_mask; 		/* 1999/01/05 by T.Soneoka */
	UBYTE	loop;
	UBYTE	dummyline;
	struct DMA_Data_t GateArrayWriteDMA_Data;

	DisableIntPrinterTimer();
	
	/* G/Aプリンタバッファ初期化 1998/12/14 by T.Soneoka */
	for (loop = 0; loop < 2; loop++) {
/*
** プリンタバッファは２５６×２なので、ワードで２５６で０ｘ００を埋めると
** プリンタバッファの次を壊してしまう
** 1999/02/23 by T.Soneoka
*/
#if (0)
**		(void)CMN_WordMemorySet((UWORD *)&PrinterBuffer[loop][0], (UWORD)256, 0x00);
#else
		(void)CMN_WordMemorySet((UWORD *)&PrinterBuffer[loop][0], (UWORD)128, 0x00);
#endif
	}

#if (0) /* 1999/01/12 by T.Soneoka */
**	PrintBufferClearMode = TRUE;		/* サーマルヘッドに残っているデータをクリアする処理 */
#endif
	/*
	 *	PBRDY 割込みがあるまで
	 *	SP INT に同期したPrinter DMA は禁止
	 */
	PrinterDmaPermission = FALSE;
	PrinterRewriteCount = 1;
	if (QuerySmoothingOn()) {
		PrinterRewriteCount = 2;
	}

	/*
	** サーマルヘッドに残っているデータをクリアする為
	** ４ライン分全白でサーマルヘッドに転送します
	*/
	dummyline = 4;
	while (dummyline--) {
		/* 全白データセット */
		(void)GetWritePtrPrtImageBuf();
		IncPrtImageReadableLine();
	};

	PrintBufferClearMode = TRUE;		/* サーマルヘッドに残っているデータをクリアする処理 */

	EnableIntPbrdy();

	if (PrintDtc) {
		/* ＤＲＥＱ端子を有効にする */
		SelectPrinterDma();
		/* ＤＴＣのセット／起動 */
		ImagePtr = GetReadPtrPrtImageBuf();
		PrtDataTrasCount = (SYS_B4_LINE/8/2);	/* B4ワード転送 */
		GateArrayWriteDMA_Data.Channel		= DMA_GATEARRAYWRITE_CH;
		GateArrayWriteDMA_Data.SrcAddress	= (UDWORD)ImagePtr;
		GateArrayWriteDMA_Data.Counter		= PrtDataTrasCount;
		GateArrayWriteDMA_Data.Unit			= DMA_WORD_TRANSFER;
		GateArrayWriteDMA_Data.Direction	= DMA_MEMORY_TO_IO;
		DMA_SetupDMAU(&GateArrayWriteDMA_Data);
		DtcPermission = FALSE;
		/* 左側Ａ４マスク設定を入れます 1999/01/05 by T.Soneoka */
		if (Paper.Size == PAPER_SIZE_A4) {
			for (white_mask = 0; white_mask < CHK_PrinterMaskWhite(); white_mask++) {
				*(ImagePtr+OffsetA4+white_mask) = 0;
			}
		}

		/* プリントループ調査用 add 2 line 1999/1/25 by T.Soneoka */
		if (SYB_MaintenanceSwitch[MNT_SW_H5] & 0x80) {
			RelayPortStatus |= 0x4000;
			OutputWORD(GA_PGADR, RelayPortStatus);
		}
		
		DMA_RequestEnable(GateArrayWriteDMA_Data.Channel);
		/* プリントスタート */
		GaPstartStatus |= GA_PRINT_START;
		OutputWORD(GA_PSTART, GaPstartStatus);
	} else {
		GaPstartStatus |= GA_PRINT_START;
		OutputWORD(GA_PSTART, GaPstartStatus);
		PrtDataTrasCount = (SYS_B4_LINE/8/2);	/* B4ワード転送 */
		ImagePtr = GetReadPtrPrtImageBuf();
		PrtGA_IO_Write((UWORD *)ImagePtr, PrtDataTrasCount);
		if (tskno_PRN_PrintDataTransTask == 0xffff) {
			cre_tsk(&tskno_PRN_PrintDataTransTask, TSK_PRINTDATATRANSTASK, (void *)0);
		}
	}

	/* Printer 5msec 割込み許可 */
	EnableIntPrinterTimer();
	
	while (EnableToReadPrtImageBuf() && QueryCanDoPrint()) {
		wai_tsk(1);
		
		/* Print LOOP by O.Kimoto 2002/03/06 */
		if (!QueryPrinterTimerIntEnable()) {
			EnableIntPrinterTimer();
		}
	}
	
	PrintBufferClearMode = FALSE;

	ChangeRxMotorPhase();

}

#if (0) /* 1998/10/31 by T.Soneoka */
**/*
** *	Name:	Squeeze Image Buffer
** *	Create:	Tue Jun 02 15:42:42 1998	by	ishiyama
** *	Synopsis:
** *		#include	"prt_drv.h"
** *		void	SqueezeImageBuffer(void);
** *	Description:
** *		全白ラインを書いてプリンタのパイプラインから
** *		イメージデータを押し出す
** *	Return Value:
** *		void
** *	Change Log:
** *		
** */
**void	SqueezeImageBuffer(void)
**{
**	UWORD	*ImagePtr;
**	UWORD	WhiteLine;
**
**	/* 全白ラインを書いて押し出す */
**	WhiteLine = 0;
**	while (WhiteLine < 3 && PrinterError == 0 && Paper.Phase != PAPER_PHASE_FEED) {
**		if (EnableToWritePrtImageBuf()) {
**			ImagePtr = GetWritePtrPrtImageBuf();
**			(void)CMN_WordMemorySet(ImagePtr, (UWORD)PRTPAGE_COL, 0x00);
**			IncPrtImageReadableLine();
**			WhiteLine++;
**		} else {
**			wai_tsk(1);
**		}
**	}
**}
#endif

/*
 *	Name:	Set Printer Close Request
 *	Create:	Wed Aug 05 17:20:54 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetPrinterCloseRequest(void);
 *	Description:
 *		プリントを終了し、記録紙を排出するよう指示する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetPrinterCloseRequest(void)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable(); /* 割込み状態保存 */
	CMN_DisableInterrupt();					/* 割込み禁止 */

	EnablePrintDataMake = FALSE; /* プリントデータ作成開始許可 1998/12/15 by T.Soneoka */
	PrinterCloseRequest = TRUE;
	
	/* 割込み状態のリストア */
	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}

 #if defined(SATSUKI2) /* SATSUKI2 追加 start by Y.Kano 2003/06/26 */

UBYTE ExecCutter(void)
{
	/* スキャナーコピー時紙つまりと表示時間長いの不具合の為、復活します。　by Smuratec 2003/11/24 */
#if (1) /* スキャナーコピー時紙つまりと表示の不具合の為、コメントアウトします。　by Smuratec 2003/11/21 */
	UWORD CutterTimeOutCounter;/* 1999/04/13 by T.Soneoka */

	CutterTimeOutCounter = 0;	/* 1999/04/13 by T.Soneoka */
#endif

	if (!CHK_WallHangSetting()) { /** 壁掛け設定用でない時 */	/* Add by Y.kano 2003/10/03 */
		CutterOn();	/* カッターが待機位置にないときはカッター動作させてカッターを待機位置に置く */
		while (PRN_Control.CutterBusy) {	/* カッター動作終了待ち */
		/* スキャナーコピー時紙つまりと表示時間長いの不具合の為、復活します。　by Smuratec 2003/11/24 */
#if (1) /* スキャナーコピー時紙つまりと表示の不具合の為、コメントアウトします。　by Smuratec 2003/11/21 */
			CutterTimeOutCounter++;
			if (CutterTimeOutCounter > 100) {
				return (NG);
			}
#endif
			wai_tsk(2);	/* 20ms */
		}
		return (OK);
	}
	else {
		return (OK);
	}
}

 #else /* SATSUKI2 追加 start by Y.Kano 2003/06/26 */

#if (0) /* カッタ不良チェック追加 1999/04/13 by T.Soneoka */
** void ExecCutter(void)
#else
UBYTE ExecCutter(void)
#endif
{
	UWORD CutterTimeOutCounter;	/* 1999/04/13 by T.Soneoka */

	CutterTimeOutCounter = 0;	/* 1999/04/13 by T.Soneoka */

	if (!CutterPosition()) {
#if (0) /* 1999/04/13 by T.Soneoka */
**		CheckCutter();
#else
		if (CheckCutter() == NG) {
			return (NG);
		}
#endif
	}
#if (PRO_ENERGY_SAVE == ENABLE)	/* 2001/11/22 T.Takagi */
	PC_24V_On();
#endif
	Cutter1On();
	Cutter2On();
	wai_tsk(10);
	Cutter1Off();
	while (!CutterPosition()) {
		wai_tsk(1);

		/* カッタ不良チェック追加 1999/04/13 by T.Soneoka */
		CutterTimeOutCounter++;
		if (CutterTimeOutCounter > 100) {
			Cutter2Off();
			return (NG);
		}

	}
	Cutter2Off();

	return (OK); /* 1999/04/13 by T.Soneoka */
}

 #endif /* SATSUKI2 追加 start by Y.Kano 2003/06/26 */


#if !defined(SATSUKI2)	/* SATSUKI2では使用せず by Y.Kano 2003/06/26 */
#if (0) /* カッタ不良チェック追加 1999/04/13 by T.Soneoka */
** void CheckCutter(void)
#else
UBYTE CheckCutter(void)
#endif
{
	UWORD CutterTimeOutCounter;	/* 1999/04/13 by T.Soneoka */

	CutterTimeOutCounter = 0;	/* 1999/04/13 by T.Soneoka */
	
	if (!CutterPosition()) {
		Cutter2On();
		while (!CutterPosition()) {
			wai_tsk(1);

			/* カッタ不良追加 1999/04/13 by T.Soneoka */
			CutterTimeOutCounter++;
			if (CutterTimeOutCounter > 100) {
				Cutter2Off();
				return (NG);
			}

		}
		Cutter2Off();
	}
	return (OK);
}
#endif	/* SATSUKI2では使用せず by Y.Kano 2003/06/26 */


void PrtGA_IO_Write(
UWORD	*SRC_ptr,	/* コピー元の先頭アドレス */
UWORD	CopyCount)		/* コピー数 */
{
	for ( ; CopyCount > 0; CopyCount--) {
		while (InputWORD(GA_SP_REQ) & PREQ);	/* プリントデータ要求がでるまで待ちます */
		OutputWORD(GA_PRID, *SRC_ptr++);		/* プリントデータ書き込み */
	}
	return;
}


BOOL IsNextPrint(void)
{
	UBYTE	rtn;
	
	rtn = FALSE;
	if (IsDocument) {
		rtn = TRUE;
	}
}

BOOL CheckPrinteDmaPermission(void)
{
	if ((SYB_MaintenanceSwitch[MNT_SW_H0] & RX_TEST_MODE)
	&&  (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_TPH_SYNC)) {
		return TRUE;
	} else {
		if (PrinterDmaPermission) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL Check3mOver(void)
{
#if (0) /* プリンタ受信は通信で制限をかけているので、ここではみません  1999/02/02 by T.Soneoka */
**	if ((PrinterUseMode == PRINT_RXPRINT)
**	|| ((PrinterUseMode == PRINT_IMAGE) && (SYS_DocumentPrintItem == SYS_MEM_RX_FILE))) {
#else
	/* イメージプリントでマルチコピープリント以外は３ｍ制限チェックするようにします */
	if ((PrinterUseMode == PRINT_IMAGE) && (SYS_DocumentPrintItem != SYS_MEM_MULTI_COPY_FILE)) {
#endif
		if ((Paper.StepsFromPrinting > Print3M_Over)
		&& (CHK_PrintRx3mOver())) {
#if (0) /* 上位でセットするように変更します  1999/02/02 by T.Soneoka */
**			PrinterError |= PRT_ERROR_3M_OVER;
#endif
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_3M_OVER;
			return TRUE;
		}
	}
	return FALSE;
}
