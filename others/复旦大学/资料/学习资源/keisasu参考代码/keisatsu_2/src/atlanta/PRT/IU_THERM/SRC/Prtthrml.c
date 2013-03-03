/*
 *	@(#)$Id: Prtthrml.c,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/prj/Eva/Src/prt/prtthrml.c
 *	Create:	Tue May 26 09:49:40 1998	by	ishiyama
 *	Description:
 *		Thermal Head Printer Control Routine
 *	Notes:
 *		�֘A�t�@�C���Ƃ̈Ⴂ�́A
 *			prt_drv.c:	I/O �ݒ���܂܂Ȃ�
 *			prtengin.c:	I/O �ݒ���܂�ŁA�v�����^����
 *			prtlaser.c:	Leser Beam Printer �����Ɏg�p���郋�[�`��
 *			prtthrml.c:	Thermal Printer �����Ɏg�p���郋�[�`��
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
#include "\src\atlanta\satsuki2\define\scn_def.h"	/* B4->A4�������΍� 1999/03/05 by T.Soneoka */
#include "\src\atlanta\satsuki2\define\m_param.h"	/* Add by Y.kano 2003/09/30 */
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
#include "\src\atlanta\hinoki\define\scn_def.h"	/* B4->A4�������΍� 1999/03/05 by T.Soneoka */
 #endif

#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* �o�r�Q�̕��σ��x�����Z�o by Y.kano 2004/03/01 */
#include	"\src\atlanta\hinoki\define\m_param.h"
#endif

#if (0) /* ���ɂ��܂� 1999/1/14 by T.Soneoka */
**static WORD	backward_step_error = 0;
#endif
static UDWORD	PrtImageBufReadLineAddress = 0; /* For Debuf */
static UBYTE	used_count;	/* 1998/12/16 by T.Soneoka */
static UBYTE	pre_used_count; /* 1998/12/22 by T.Soneoka */
static UBYTE	PrintExecute; /* 1998/12/16 by T.Soneoka */
static UBYTE	print_count; /* 1998/12/16 by T.Soneoka */
static UBYTE	PreHeatPhase; /* 1998/12/16 by T.Soneoka */
static UBYTE	motor_stop_request; /* 1999/03/01 by T.Soneoka */

#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* �o�r�Q���������s��Ή� by Y.kano 2004/12/06 */
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
 *		Cooked Mode �� PS1 ���`�F�b�N,���ʂ� CookedPs1
 *		5msec �^�C�}�ŋL�����X�V�B
 *	Return Value:
 *		TRUE:	PS1 �ω�����
 *		FALSE:	PS1 �ω�����
 *	Change Log:
 *		
 */
BOOL	Ps1Changed(void)
{
	BOOL	CurrentPs1;			/* ���݂̃Z���T�[��� */
	BOOL	Rtn;

	Rtn = FALSE;
	CurrentPs1 = PS1();
	if (CookedPs1 != CurrentPs1) {
		if (--Ps1CookCounter <= 0) {	/* �`���^�����O�h�~�ׂ̈̃J�E���^�[���Z */
			CookedPs1 = CurrentPs1;		/* ���݂̏�Ԃ��L�� */
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
 *		Cooked Mode �� PS2 ���`�F�b�N,���ʂ� CookedPs2
 *		5msec �^�C�}�ŋL�����X�V�B
 *	Return Value:
 *		TRUE:	PS2 �ω�����
 *		FALSE:	PS2 �ω�����
 *	Change Log:
 *		
 */
BOOL	Ps2Changed(void)
{
	BOOL	CurrentPs2;			/* ���݂̃Z���T�[��� */
	BOOL	Rtn;

	Rtn = FALSE;
	CurrentPs2 = PS2();
	if (CookedPs2 != CurrentPs2) {
		if (--Ps2CookCounter <= 0) {	/* �`���^�����O�h�~�ׂ̈̃J�E���^�[���Z */
			Ps2CookCounter = PsChatCount;
			CookedPs2 = CurrentPs2;		/* ���݂̏�Ԃ��L�� */
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
 *		Raw Mode �� Printer �� InterLock ���`�F�b�N
 *	Return Value:
 *		TRUE:	InterLock is ON(Close)
 *		FALSE:	InterLock is OFF(Open)
 *	Change Log:
 *		
 */
BOOL	InterLock4PrintRaw(void)
{
	BOOL	Rtn;				/* Return Value */

#if defined(SATSUKI2)	/* SATSUKI2�̏ꍇ�A�����I�Ɂf�O�f��Ԃ� by Y.Kano 2003/07/03 */
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
 *		Cooked Mode �� �v�����^��InterLock ���`�F�b�N,���ʂ� CookedInterLock4Print
 *		5mse �����݂ŋL�����X�V�B
 *	Return Value:
 *		TRUE:	InterLock �ω�����
 *		FALSE:	InterLock �ω�����
 *	Change Log:
 *		
 */
BOOL	InterLock4PrintChanged(void)
{
	BOOL	CurrentInterLock;			/* ���݂̃Z���T�[��� */
	BOOL	Rtn;

	Rtn = FALSE;
	CurrentInterLock= InterLock4PrintRaw();
	if (CookedInterLock4Print != CurrentInterLock) {
		if (--InterLock4PrintCookCounter <= 0) { /* �`���^�����O�h�~�ׂ̈̃J�E���^�[���Z */
			InterLock4PrintCookCounter = PsChatCount;
			CookedInterLock4Print = CurrentInterLock; /* ���݂̏�Ԃ��L�� */
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
 *		�L�^������ʃJ�E���g�A�b�v �L�^���ʒu�X�e�[�^�X�X�V
 *		��M���[�^�[�����R�[�����邱�ƁB
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
		case PAPER_POS_NO_PAPER:				/* �L�^�����Ȃ���� */
			break;

		case PAPER_POS_MOVE_TO_MINI_DOC_EXIT:			/* �ŏ��L�^�������A�L�^���r�o */
			Paper.StepsFromDocSet += RxMotorSpeedPtr->MoveLines;

#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* �o�r�Q�̕��σ��x�����Z�o by Y.kano 2004/03/01 */
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
				/* �u���������̎Z�o */
				SYB_MachineParameter[M_PARA_SW_J3] = (UBYTE)((PS2_Vp_Value / 150));
				PS2_Vp_Value = 0;
				PS2_Vp_Count = 0;
				PS2_Count = 0;
				/* �u�������Q�̎Z�o */
				SYB_MachineParameter[M_PARA_SW_J4] = (UBYTE)((0xff + SYB_MachineParameter[M_PARA_SW_J3]) / 2);
  #if (1)	/* �o�r�Q���������@�\ by Y.Kano 2004/12/10 */
				if (SYB_PS2_SensorStatus != PS2_THRESHOLD) {
					SYB_PS2_SensorStatus = VSIM2_THRESHOLD;		/* �u�������Q�i���z�X���C�X���x���j�ɐ؂�ւ� */
				}
  #endif
			}
#endif
			if (Paper.StepsFromDocSet >= MinimumDocExitSteps) {

				/* EndMark5
				** �C�j�V�����J�b�g���̃G���h�}�[�N�`�F�b�N�������Ă���
				** by O.Kimoto 1999/03/09
				*/
#if defined(SATSUKI2)	/* �G���h�}�[�N�`�F�b�N�p�o�r�Q�`�F�b�N�̒ǉ�  2003/10/23 */
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

		case PAPER_POS_FEED_OUT:				/* �L�^���r�o */

			/*
			** �a�S�L�^���J�b�g���A�L�^���̒[�������ޕs�
			** 1999/11/22 by T.Soneoka
			*/
			if (IsCutBack) {	/* �J�b�g�o�b�N���̂Ƃ� */
				Paper.StepsFeedOut -= RxMotorSpeedPtr->MoveLines;	/* �J�b�g�o�b�N�X�e�b�v���Z */
				if (Paper.StepsFeedOut <= COUNT_CUT_BACK_STEP) {	/* �J�b�g�o�b�N�X�e�b�v�����߂������� */
					IsCutBack = FALSE;								/* �J�b�g�o�b�N�I�� */
					StopRxMotor();									/* �L�^�������o�������i���[�^�t�]�j */
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

/* �ڐA by SMuratec K.W.Q 2003/07/29 */
#if defined(SATSUKI2)	/* SATSUKI2�̏ꍇ�́A�󎚑ҋ@�ʒu PS2����8.5�̂Ƃ��� ��[��STEP�ɕύX by Y.Kano 2003/07/26 */
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
** 			** �C�j�V�����J�b�g���̃G���h�}�[�N�`�F�b�N�������Ă���
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

		case PAPER_POS_MOVE_TO_PS2:				/* �o�r�Q�Z���T���؂��܂ň����߂� */
			Paper.BackWardStepsFromFeedOut += RxMotorSpeedPtr->MoveLines;

#if (0)
** 			/* EndMark6
** 			** �o�r�Q�܂ŋL�^���������߂����́A����X�e�b�v�ʈ����߂��܂ŁA�o�r�Q�͌��Ȃ��悤�ɕύX���܂��B
** 			** by O.Kimoto 1999/03/11
** 			*/
** #if (0)
** ** 			/* EndMark �΍􂻂̂Q By O.Kimoto 1999/02/11 */
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
#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* PS2���؂�Ă���P�����]���ɑ���܂��Bby Y.Kano 2004/12/06 */
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
								PS2_Vb_Value = (UBYTE)AD_PS2();	/* �u���i�L�^���������x���j�捞�� */
								SYB_MachineParameter[M_PARA_SW_J5] = PS2_Vb_Value;
 #if (1)	/* �����ŁA��臒l�����߂܂��Bby Y.kano 2004/12/10 */
								if (SYB_PS2_SensorStatus == VSIM2_THRESHOLD) {
									/* �o�r�Q�̎��X���C�X���x���i�u���j�̎Z�o */
									SYB_MachineParameter[M_PARA_SW_J6] = (UBYTE)(((SYB_MachineParameter[M_PARA_SW_J5] + SYB_MachineParameter[M_PARA_SW_J3]) / 2));
									SYB_PS2_SensorStatus = PS2_THRESHOLD;	/* �o�r�Q���������@�\���s�ς݃t���O�n�m */
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
						** ���[�����I�[�ɂ����āA���傤�ǈ󎚏I�������Ƃ��A
						** �Z�ڕ�����PS2�Ɏc���Ă��܂��A���܂ł�PS2��ON�����ςȂ��ɂȂ�
						** ���[�v����
						** �ȉ��̂悤�ɁA�����߂��X�e�b�v�����Ď����܂�
						** 1999/1/14 by T.Soneoka
						*/
						/* �L�^���J�b�g�G���[ */
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
#if defined(SATSUKI2)	/* �Ǌ|���ݒ�p�ɒǉ� by Y.Kano 2003/10/09 */
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
						/* �L�^���J�b�g�G���[ */
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

		case PAPER_POS_MOVE_TO_PRINTING:		/* �L�^�ʒu�܂ň����߂��� */
			Paper.StepsFromPs2On -= RxMotorSpeedPtr->MoveLines;

			if (Paper.StepsFromPs2On <= (PrintPostionSteps + Paper.TopMargin)) {
				Paper.StepsFromPrinting = 0;
				StopRxMotor();

				if (PrinterUseMode == PRINT_SCOPY) {
					/* �L�^�J�n�ʒu�ֈ����߂����I���΂Ƃ肠������ʂɒʒm����悤�ɕύX */
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

		case PAPER_POS_MOVE_TO_READY:		/* �L�^�ҋ@�ʒu�܂ňړ��� */
			Paper.StepsFromPs2On += RxMotorSpeedPtr->MoveLines;
#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* �o�r�Q���������s��Ή� by Y.kano 2004/12/06 */
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

		case PAPER_POS_PRINTING:				/* �L�^�\ */
			Paper.StepsFromPrinting += RxMotorSpeedPtr->MoveLines;

			if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
				CheckThermalHighTemp();
			}
#if (0) /* �R����M�v�����g���������A�ʐM�ōs�Ȃ��悤�ɂ��܂�  1999/02/02 by T.Soneoka */
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
						/* �L�^���Ȃ��G���[ */
						PrinterError |= PRT_ERROR_NO_PAPER;
						PrinterEventStatus |= PRT_EVT_ERROR;
						idet_evt(EVT_PRT_IMAGE);
					}

#if defined(SATSUKI2)	/* �G���h�}�[�N�`�F�b�N�p�o�r�Q�`�F�b�N�̒ǉ�  2003/10/23 */
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
			
		case PAPER_POS_MOVE_TO_CUT:				/* �L�^���J�b�g�ʒu�Ɉړ��� */
			Paper.StepsFromPrinting += RxMotorSpeedPtr->MoveLines;
			Paper.StepsToCutPosFromPlaten += RxMotorSpeedPtr->MoveLines;
			
			if (Paper.StepsFromPrinting < MinimumDocExitSteps) {
				if (Paper.StepsFromPrinting >= JAM_CheckSteps) {

#if (0)
** 					/* �����ł͂i�`�l�`�F�b�N�͍s�킸�ɁA�L�^�������i�o�r�P�j�݂̂ɂ��܂��B
** 					** by O.Kimoto 1999/02/08
** 					*/
** 					if (!QueryPs2On()) {
** 						/* �i�`�l�G���[ */
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
						/* �i�`�l�G���[ */
						PrinterError |= PRT_ERROR_NO_PAPER;
						PrinterEventStatus |= PRT_EVT_ERROR;
						if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
							idet_evt(EVT_PRT_IMAGE);
						} else {
							idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
						}
					}
#if defined(SATSUKI2)	/* �G���h�}�[�N�`�F�b�N�p�o�r�Q�`�F�b�N�̒ǉ�  2003/10/23 */
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
#if defined(SATSUKI2)	/* �G���h�}�[�N�`�F�b�N�p�o�r�Q�`�F�b�N�̒ǉ�  2003/10/23 */
				if (!EndMarkPS2Cehck()) {
#else
				if (!QueryPs2On()) {	/* Endmark2 By O.Kimoto 1999/02/11 */
#endif	/* End of defined(SATSUKI2) */
					if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {
						EndMarkDetect = TRUE;
					}
				}

				/* �J�b�g�ʒu�֔�������PS1�̊Ď����K�v By O.Kimoto 1998/12/07 */
				if (!QueryPs1On()) {
					/* �L�^���Ȃ��G���[���L�^���̓J�b�g���܂��� */
					PrinterError |= PRT_ERROR_NO_PAPER;
					PrinterEventStatus |= PRT_EVT_ERROR;
					if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
						idet_evt(EVT_PRT_IMAGE);
					} else {
						idet_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
					}
				}

				else if (Paper.StepsToCutPosFromPlaten >= (ToCutPosFromPlatenSteps + Paper.BottomMargin)) {

/*------------------< �o�N�ω��Ή� by Y.kano 2003/10/22 >-------------------------*/
#if defined(SATSUKI2)		/* �o�N�ω��Ή� by Y.Kano 2003/10/22 */
					if (CHK_YearChangeEnable()) {		/* �o�N�ω��Ή��\���`�F�b�N by Y.Kano 2003/10/31 */
						AD_PS2_StoreValue = AD_PS2();		/* �L�^���J�b�g���O�ɂ�����o�r�Q�̂`�c�l�捞�݁Bby Y.Kano 2003/10/31 */
/*					AD_PS2_Value2 = AD_PS2();	*/	/* �L�^���J�b�g���O�ɂ�����o�r�Q�̂`�c�l�捞�݁Bby Y.Kano 2003/10/22 */
/*					AD_PS2_AveValue  = (AD_PS2_Value1 + AD_PS2_Value2) / 2;*/	/* AD1��AD2�Ƃ̕��ϒl���Z�o by Y.Kano 2003/10/22 */
						if (AD_PS2_StoreValue <= 0x3D) {
							SYB_PS2LimitValue = PS2DEFAULT;		/* �o�N�ω��Ή���PS2�f�t�H���g�l�i0x5c)�̃Z�b�g�B*/
						}
						else if (AD_PS2_StoreValue <= 0x66) {
							SYB_PS2LimitValue = PS2_LIMIT_1;	/* �o�N�ω��Ή���PS2臒l�i0x7A)�̃Z�b�g�B*/
						}
						else {	/* AD_PS2_StoreValue <= 0x7A */
							SYB_PS2LimitValue = PS2_LIMIT_2;	/* �o�N�ω��Ή���PS2臒l�i0x99)�̃Z�b�g�B*/
						}
 #if (0)	/* �@��p�����[�^�̕ύX by Y.kano 2003/12/18 */
						SYB_MachineParameter[M_PARA_SW_J2] = SYB_PS2LimitValue;	/* �}�V���p�����[�^�Ɍ��݂̂o�r�Q臒l�𔽉f by Y.Kano 2003/10/22 */
						SYB_MachineParameter[M_PARA_SW_J3] = AD_PS2_StoreValue;		/* �}�V���p�����[�^�Ɍ��݂̂o�r�Q�捞�ݒl�𔽉f by Y.Kano 2003/10/31 */
 #else
						SYB_MachineParameter[M_PARA_SW_J8] = SYB_PS2LimitValue;	/* �}�V���p�����[�^�Ɍ��݂̂o�r�Q臒l�𔽉f by Y.Kano 2003/10/22 */
						SYB_MachineParameter[M_PARA_SW_J9] = AD_PS2_StoreValue;		/* �}�V���p�����[�^�Ɍ��݂̂o�r�Q�捞�ݒl�𔽉f by Y.Kano 2003/10/31 */
 #endif
					}
#endif	/* End of defined(SATSUKI2) */
/*------------------< �o�N�ω��Ή� by Y.kano 2003/10/22 >-------------------------*/

/*------------------< test by Y.kano 2003/10/09 >-------------------------*/
#if defined(SATSUKI2)		/* �Ǌ|���ݒ�p�ƍŏ��L�^�����r�o�X�e�b�v�Ƃ�؂蕪����Bby Y.Kano 2003/10/09 */
					if (CHK_WallHangSetting()) { /** �Ǌ|���ݒ�p */	/* Add by Y.kano 2003/10/09 */
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
** 						/* EndMark3 �X�L���i�[�R�s�[���AEndMark������Ă��Ȃ�����
** 						** by O.Kimoto 1999/02/19
** 						*/
** 						Paper.Position = PAPER_POS_MOVE_TO_PS2;
** 						Paper.BackWardStepsFromFeedOut = 0;
** 						backward_step_error = BackWardStepError;
** 
** 						PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);	/* 12.2mm + 3.5mm *//* EndMark By O.Kimoto 1999/02/09 */
  #else
						/*
						** �������ύX 1999/04/13 by T.Soneoka
						*/
   #if (0)
**						if (EndMarkDetect == TRUE) {
   #else
						if ((EndMarkDetect == TRUE)
						|| (!IsNextPrint())) {
   #endif
   #if defined(SATSUKI2)		/* �Ǌ|���ݒ�p�ƍŏ��L�^�����r�o�X�e�b�v�Ƃ�؂蕪����Bby Y.Kano 2003/10/09 */
							if (!CHK_WallHangSetting()) { /** �Ǌ|���ݒ�p */	/* Add by Y.kano 2003/10/09 */

								Paper.Route = ROUTE_PRINTING_TO_READY;
								Paper.Position = PAPER_POS_FEED_OUT;
								Paper.StepsFeedOut = 0;
							}
						}
   #else	/* SATSUKI2�ȊO */
							Paper.Route = ROUTE_PRINTING_TO_READY;
							Paper.Position = PAPER_POS_FEED_OUT;
							Paper.StepsFeedOut = 0;
						}
   #endif	/* End of defined(SATSUKI2) */
						else {
							Paper.Position = PAPER_POS_MOVE_TO_PS2;
							Paper.BackWardStepsFromFeedOut = 0;
							backward_step_error = BackWardStepError;

   #if defined(SATSUKI2)		/* �Ǌ|���ݒ�p by Y.Kano 2003/10/27 */
							if (CHK_WallHangSetting()) { /** �Ǌ|���ݒ�p */	/* Add by Y.kano 2003/10/09 */

								PaperMoveCount = PrintReadySteps;	/* 10mm *//* EndMark By O.Kimoto 1999/02/09 */
							}
							else {
								PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);	/* 12.2mm + 3.5mm *//* EndMark By O.Kimoto 1999/02/09 */
							}
   #else	/* SATSUKI2�ȊO */
							PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);	/* 12.2mm + 3.5mm *//* EndMark By O.Kimoto 1999/02/09 */
   #endif	/* End of defined(SATSUKI2) */
						}
  #endif

 #endif
					} else if (PrinterUseMode == PRINT_RXPRINT) {
						if (!PrinterError) {

 #if (0)
** 							/* Endmark3 �v�����^�[��M���AEndMark������Ă��Ȃ�����
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
   #if defined(SATSUKI2)		/* �Ǌ|���ݒ�p�ƍŏ��L�^�����r�o�X�e�b�v�Ƃ�؂蕪����Bby Y.Kano 2003/10/14 */
							if (!CHK_WallHangSetting()) { /** �Ǌ|���ݒ�p */	/* Add by Y.kano 2003/10/14 */
								Paper.Route = ROUTE_PRINTING_TO_READY;
								Paper.Position = PAPER_POS_FEED_OUT;
								Paper.StepsFeedOut = 0;
							}
   #else	/* SATSUKI2�ȊO */
							Paper.Route = ROUTE_PRINTING_TO_READY;
							Paper.Position = PAPER_POS_FEED_OUT;
							Paper.StepsFeedOut = 0;
   #endif	/* End of defined(SATSUKI2) */
						}
					} else {
   #if defined(SATSUKI2)		/* �Ǌ|���ݒ�p�ƍŏ��L�^�����r�o�X�e�b�v�Ƃ�؂蕪����Bby Y.Kano 2003/10/14 */
						if (!CHK_WallHangSetting()) { /** �Ǌ|���ݒ�p */	/* Add by Y.kano 2003/10/14 */
							Paper.Position = PAPER_POS_FEED_OUT;
							Paper.StepsFeedOut = 0;
						}
   #else	/* SATSUKI2�ȊO */
						Paper.Position = PAPER_POS_FEED_OUT;
						Paper.StepsFeedOut = 0;
   #endif	/* End of defined(SATSUKI2) */
					}
				}
			}
			break;

		case PAPER_POS_PRINTING_TO_FEED_OUT:				/* �󎚈ʒu����̋L�^���r�o�i�|���ҋ@�ʒu�܂Łj */
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
				** �v�����g���e�������o���Ƃ��i���Ƀe���V����������ꍇ�j
				** PS1�T���T������悤�ɂ��܂�
				** 1999/1/14 by T.Soneoka
				*/
				if (!QueryPs1On()) {
					/* �L�^���Ȃ��G���[ */
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
** ** 								** �����ł́APS2���`�F�b�N���āAEndmark�̏ꍇ�̓t���O���Z�b�g���邾���ł悢�B
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
 *		�L�^�����󎚉\�Ȉʒu�ɂ��邩�H
 *	Return Value:
 *		TRUE:	�󎚉\
 *		FALSE:	�󎚕s��
 *	Change Log:
 *		
 */
BOOL	CheckPrintablePosition(void)
{
	BOOL	Rslt;

	Rslt = FALSE;
	if (Paper.Phase == PAPER_PHASE_PRINT) {
		if (Paper.Position == PAPER_POS_PRINTING) {/* �L�^�\ */
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
 *		�P���C���v�����g
 *	Notes:
 *		EnableIntPbrdy(),EnableIntPrinterTimer() ���R�[������A
 *		PBRDY, Printer 5msec Timer���荞�݂��L���ɂȂ��Ă��邱�ƁB
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

	StrobeTime = 0;						/* ��������ǂ����������t���O Restrobe �ł̂ݎg�p */
	motor_stop_request = 0;				/* 1999/03/01 by T.Soneoka */
	print_exec = FALSE;					/* �������s�Ǖs� 1999/05/26 by T.Soneoka */

	CancelToMoveRxMotor();				/* Not Move RxMotor(Default) */

	/* Strobe Monitor Check */
	if (!QueryStrobeOn()) {
		/* �������Ȃ� */
		if (CheckPrinteDmaPermission()) {
			PBRDY_Count = 0;			/* �f�h�m�s���Ƃ܂�΍�  1999/01/27 by T.Soneoka */
			if (!(GaTphStatus & TPH_SYNC)) {
				if (!DtcPermission) {	/* �c�s�b�̏I�����荞�݂��m�F���܂�  1998/12/11 by T.Soneoka */
					return;
				}
			}

/*
** ���Z���s�o�g�Q�x�����Ή��͎���߂܂�
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
			/* Printer DMA ���� */
			switch (PrinterRewriteCount) {
			case 1:						/* DMA,Strobe,MotorMove */
				/* �v�����^��M���̍������΍�
				** �g�h�m�n�j�h�͂P���C���T�����ň󎚉\�ł��邪
				** ���C���T�����̐ݒ�ŊԌ�����������ꍇ�A���X�W������΍�
				** 1998/12/21 by T.Soneoka
				*/
				if (PrinterUseMode == PRINT_RXPRINT) {
/*
** �v�����^��M���̃N���A���[�h�ƍŌ�̏������C�����܂�
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
** ������C���[�W�v�����g�e�������Ɠ��������ɂ��܂�
** 1999/03/09 by T.Soneoka
*/
								if (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x80) {
									if (EnableToReadPrtImageBuf()) {
										ExecPrintOnTiming = 1;	/* ���̈󎚂͂T���� */
										if (PrintExecute) {
											print_exec = TRUE;
											used_count = GetPrtImageBufUsedCount();

											if (used_count == 2) { /* �Ō�̃��C�� */
												motor_stop_request = 1;
												PrintExecute = FALSE;
												ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f); /* �x�݂܂� */
											}

										} else {
											PrintExecute = FALSE;
											used_count = GetPrtImageBufUsedCount();
											if (used_count >= (SYB_MaintenanceSwitch[MNT_SW_H6] & 0x0f)+1) {
												/* ���[�^������ɉ񂵂Ă����A�v�����g�����͎��̂T�����ōs�Ȃ����� */
												RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
												PrintExecute = TRUE;
												print_exec = FALSE; 
											}
										}
									} else {
										PrintExecute = FALSE;
										ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f); /* �x�݂܂� */
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
/* �R�[�h�͂Ȃ����Ă����܂����A���������邩�킩��Ȃ��̂Ŏc���܂� 1999/03/03 by T.Soneoka */
#if (0)
**				} else if ((PrinterUseMode == PRINT_IMAGE) && (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x10)) {
**					/*
**					** �C���[�W�v�����g���̑����΍�����܂�
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
**									ExecPrintOnTiming = 1;	/* ���̈󎚂͂T���� */
**								} else {
**									used_count = GetPrtImageBufUsedCount();
**									if (used_count >= 3) {
**										PrintExecute = TRUE;
**										print_exec = TRUE;
**										ExecPrintOnTiming = 2; /* ���̈󎚂͂P�O���� */
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
**					** �C���[�W�v�����g���̑����΍�����܂�
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
					** �C���[�W�v�����g���̑����΍�����܂�
					**  1999/02/24 by T.Soneoka
					*/
					if (PrintBufferClearMode) {
/*
** �ʑ�����s� PrtImageBufUsedCount�������Ɉ󎚏����Ɉڂ�ƁA���[�h�|�C���^�������i��ł��܂�
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
								ExecPrintOnTiming = 1;	/* ���̈󎚂͂T���� */
								if (PrintExecute) {
									print_exec = TRUE;
									used_count = GetPrtImageBufUsedCount();

									if (used_count == 2) { /* �Ō�̃��C�� */
										motor_stop_request = 1;
										PrintExecute = FALSE;
										ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f); /* �x�݂܂� */
									}

								} else {
									PrintExecute = FALSE;
									used_count = GetPrtImageBufUsedCount();
#if (0) /* 1999/03/03 by T.Soneoka */
**									if (used_count >= 4) {
#else
									if (used_count >= (SYB_MaintenanceSwitch[MNT_SW_H6] & 0x0f)+1) {
#endif
										/* ���[�^������ɉ񂵂Ă����A�v�����g�����͎��̂T�����ōs�Ȃ����� */
										RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
										PrintExecute = TRUE;
										print_exec = FALSE; 
									}
								}
							} else {
								PrintExecute = FALSE;
								ExecPrintOnTiming = (SYB_MaintenanceSwitch[MNT_SW_H7] & 0x0f); /* �x�݂܂� */
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
						print_exec = FALSE;					/* �������s�Ǖs� 1999/05/26 by T.Soneoka */
						ExecPrintOnTiming--;
						if (!ExecPrintOnTiming) {
							ExecPrintOnTiming = 1;	/* ���̈󎚂͂T���� */
							print_exec = FALSE;
							if (EnableToReadPrtImageBuf()) {
								print_exec = TRUE;
/*
** ���Z���s�o�g�Q�x�����Ή��͎���߂܂�
** 1999/03/15 by T.Soneoka
*/
#if (0)
**								/* ���Z���s�o�g�s��Ή�
**							�@	** �s�o�g�T�[�~�X�^���o����艷�x�ȉ��i�l�s�ȏ�j�̎��́A�������C�����Q�x��������
**							�@	** �������I�Ƀv���q�[�g�i���Ԃ��j��}������
**								** �s ����� �� �̓������X�C�b�`�ɂ��ςƂ��ĉ������D
**								** �f�t�H���g�l�́A�ȉ��̒l�Ƃ��ĉ�����
**								** �s���S�U�i�Q�d���j�@�@�@�Q�O���i����l�S�U�ȏ�łQ�O���ȉ��ł��j
**								** �����T�O�i�R�Q���j�@�@�@�O�D�T����
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
						/* �c�s�b�]���N���i�c�s�b�]���̓��b�`�C�l�[�u���̑O�ōs�����Ɓj */
						DMA_RequestMask(DMA_GATEARRAYWRITE_CH);
						ImagePtr = GetReadPtrPrtImageBuf();
						PrtImageBufReadLineAddress = (UDWORD)ImagePtr; /* for debug by H.Hirao 1998/12/04 */
						DtcPermission = FALSE;
						/* �����`�S�}�X�N�ݒ�����܂� 1999/01/05 by T.Soneoka */
						if (Paper.Size == PAPER_SIZE_A4) {
							for (white_mask = 0; white_mask < CHK_PrinterMaskWhite(); white_mask++) {
								*(ImagePtr+OffsetA4+white_mask) = 0;
							}
						}
						/* �v�����g���[�v�����p add 2 line 1999/1/25 by T.Soneoka */
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
						PrinterDmaPermission = FALSE; /* Printer DMA �֎~ LATCH �̂��ƕK�� PBReady �����݂����� */
						OutputWORD(GA_SWR, (SWR_LATEN));
						PrinterRewriteCount++;
					} else {
						StrobeTime = CalcStrobeTime();
						/* ���[�^�[���㎥���ĂȂ��Ƃ��A����Ȃ� */
						if (GaRmrStatus & RMEXCT) {			/* Rx Motor �㎥�� */
							PrinterDmaPermission = FALSE; /* Printer DMA �֎~ LATCH �̂��ƕK�� PBReady �����݂����� */
							OutputWORD(GA_SWR, ((StrobeTime << 3) | SWR_STREN | SWR_PRTEN | SWR_LATEN));
						}
						/*
						** �v�����g�����[�v �c�s�b�����N�����s���āA���b�`��������Ȃ��s�
						** 1999/02/04 by T.Soneoka
						*/
						else {
							PrinterDmaPermission = FALSE; /* Printer DMA �֎~ LATCH �̂��ƕK�� PBReady �����݂����� */
							OutputWORD(GA_SWR, (SWR_LATEN));
						}
/* �ڐA by SMuratec K.W.Q 2003/07/24 */
#if defined(SATSUKI2)	/* SATSUKI2�ł̓v�����^�����݂�10msec�ɕύX���Ă���̂�SYS_SFINE�̏������O���܂��BO.Oshima 2003/07/09 */
						if (!motor_stop_request) {
							RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
						}
						PrinterRewriteCount++;
#else
						/*
						** �r�e�h�m�d�͂P�O�O������ �Q���Ȃ̂ŁA
						** �P�O�����łP�r������ �i�P�^�V�D�V���� �e�h�m�d���j�܂킹�΂悢
						*/
						if (Paper.Mode == SYS_SFINE) {
							if (PrinterSkipCount == 0) {
 #if (0)	/* 1999/03/01 �v�����g�����΍� */
**								RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
 #else
								if (!motor_stop_request) {
									RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
								}
 #endif
								PrinterRewriteCount++;
								PrinterSkipCount = 2;
							}
							PrinterSkipCount--;
						} else {
 #if (0)	/* 1999/03/01 �v�����g�����΍� */
**							RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
 #else
							if (!motor_stop_request) {
								RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
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
					/* �v�����g�C���[�W�Ȃ� */
					if ((!PrintBufferClearMode) &&
						(!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP))) {
						/* Pre Heat */
						StrobeTime = CalcPreHeatStrobeTime();
						/* ���[�^�[���㎥���ĂȂ��Ƃ��A����Ȃ� */
						if (GaRmrStatus & RMEXCT) {			/* Rx Motor �㎥�� */
							OutputWORD(GA_SWR, ((StrobeTime << 3) | SWR_STREN | SWR_PRTEN));
						}
					}
					if (IsPrintFinish) {
						IsPrintFinish = FALSE;
						SetPrinterCloseRequest();

						/*
						** �v�����g�����[�v�΍� 
						** �P�y�[�W�I����ԂłQ�y�[�W�ڂɓ���Ȃ��悤�ɂ���
						** 1999/02/04 by T.Soneoka
						*/
						PrinterDmaPermission = FALSE;
						DtcPermission = FALSE;
						
						
#if (0)	/* 1999/03/01 �v�����g�����΍� */
**						RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
#else
						if (!motor_stop_request) {
							RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
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
							/* �c�s�b�]���N���i�c�s�b�]���̓��b�`�C�l�[�u���̑O�ōs�����Ɓj */
							DMA_RequestMask(DMA_GATEARRAYWRITE_CH);
							ImagePtr = GetReadPtrPrtImageBuf();
							PrtImageBufReadLineAddress = (UDWORD)ImagePtr; /* for debug by H.Hirao 1998/12/04 */
							DtcPermission = FALSE;

							/* �v�����g���[�v�����p add 2 line 1999/1/25 by T.Soneoka */
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
					PrinterDmaPermission = FALSE; /* Printer DMA �֎~ LATCH �̂��ƕK�� PBReady �����݂����� */
					OutputWORD(GA_SWR, (SWR_LATEN));
					PrinterRewriteCount++;
				} else {
					StrobeTime = CalcStrobeTime();
					/* ���[�^�[���㎥���ĂȂ��Ƃ��A����Ȃ� */
					if (GaRmrStatus & RMEXCT) {/* Rx Motor �㎥�� */
						if (QuerySmoothingOn()) {
							PrinterDmaPermission = FALSE; /* Printer DMA �֎~ LATCH �̂��ƕK�� PBReady �����݂����� */
							OutputWORD(GA_SWR, ((StrobeTime << 3) | SWR_LATEN | SWR_STREN | SWR_PRTEN));
						} else {
							OutputWORD(GA_SWR, ((StrobeTime << 3) | SWR_STREN | SWR_PRTEN));
						}
					}
					/*
					** �v�����g�����[�v �c�s�b�����N�����s���āA���b�`��������Ȃ��s�
					** 1999/02/04 by T.Soneoka
					*/
					else {
						if (QuerySmoothingOn()) {
							PrinterDmaPermission = FALSE; /* Printer DMA �֎~ LATCH �̂��ƕK�� PBReady �����݂����� */
							OutputWORD(GA_SWR, (SWR_LATEN));
						}
					}
						
#if (0)	/* 1999/03/01 �v�����g�����΍� */
**					RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
#else
					if (!motor_stop_request) {
						RequestToMoveRxMotor();	/* ��M���[�^�[�P�X�e�b�v���� */
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
			** �f�h�m�s�i�v�����^���[�v�j���Ƃ܂�΍�  1999/01/27 by T.Soneoka
			** �c�s�b�I�����荞�݂������Ă��Ă��āA�f�h�m�s�i�o�a�q�c�x�j���荞�݂������Ă��Ȃ��ꍇ
			** �c�s�b�I�����荞�݂���Q��ڂłf�h�m�s�̃X�e�[�^�X�N���A�����s����
			** �f�h�m�s�i�o�a�q�c�x�j�������Ă����Ƃ��Ɠ������������܂�
			*/
			if (DtcPermission) {
				PBRDY_Count++;
				if (PBRDY_Count >= 2) {
					PBRDY_Count = 0;
					Status = InputWORD(GA_INT_STA);	/* G/A�����݃X�e�[�^�X�E�|�[�g */
					OutputWORD(GA_INT_REC, Status);	/* �����ݎ�� */
#if (0) /* �f�^�`�����p */
**					while (1) {
**						Status = InputWORD(GA_INT_STA);	/* G/A�����݃X�e�[�^�X�E�|�[�g */
**						if (Status & IO_BIT_PBRDY) {
**							SYB_MaintenanceSwitch[MNT_SW_H5] |= 0x02;
**							OutputWORD(GA_INT_REC, Status);	/* �����ݎ�� */
**						} else {
**							OutputWORD(GA_INT_REC, Status);	/* �����ݎ�� */
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
		ExecPrintOnTiming = 2; /* �P�O������Ƀv�����g����悤�ɂ��܂� 1999/03/03 by T.Soneoka */
	}
}


/*
 *	Name:	Watch Continuous Strobe Failer
 *	Create:	Tue Jun 02 12:59:45 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	WatchContinuousStrobe(void);
 *	Description:
 *		�A������Ă��Ȃ����Ƃ̊m�F
 *	Return Value:
 *		TRUE:	����
 *		FALSE:	�ُ�(�������AEntry �ɔ�΂��̂ŁA���ۂɂ͋A��Ȃ�)
 *	Change Log:
 *		
 */
BOOL	WatchContinuousStrobe(void)
{
	BOOL	Rslt;

	Rslt = TRUE;
	if (QueryStrobeOn()) {
		/* ��� */
		if (++ContinuousStrobeCount >= AbnormalStrobeCount) {
			Rslt = FALSE;
			/*
			 *	�T�[�}���w�b�h�A�X�g���[�u�o�����B
			 *	���댯�B
			 */
			OutputWORD(GA_SWR, 0x0000);	/* Strobe ���O & �֎~ */
			OutputWORD(GA_RST, 0x0001);	/* GateArray Reset */
			OutputWORD(GA_RST, 0x0000);	/* GateArray Reset */
			/*
			 *	�����ŃG���g���[�ɔ�΂��B
			 */
#if (0) /* ���Z�b�g�ɂ����v�����^�G���[�����ɂ��܂� */
**			SaveReturnAddressAndJumpBegin();	/* �Ȃ�����A�J���� */
#endif
		}
	} else {
		/* �������Ȃ� */
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
 *		�X�g���[�u�����ǂ���
 *	Return Value:
 *		TRUE:	�X�g���[�u�o�͒�
 *		FALSE:	�X�g���[�u�͂łĂȂ�
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
 *		�X�g���[�u�p���X�����v�Z���āA�Ԃ�
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
** �V���q���L�^���g�p���̔��ؑ΍� 
** �q�[�g�p���X��]���ɓ���đΉ����Ă������i1999/03/02 by T.Soneoka�j
** ���Ԓ��R�s�[�̂Ƃ��̓q�[�g�p���X���͂��� 1999/03/05 by T.Soneoka �d�ݕ���˗�
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
**	** �V���q���L�^���g�p���̔��ؑ΍� 
**	** �q�[�g�p���X��]���ɓ���đΉ� 1999/03/02 by T.Soneoka
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
		/* ���Ԓ��͉��ʂ��͂����܂��� */
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
#if defined(HINOKI2) || defined (HINOKI3)	/* LC821033�d�l�Ή� Y.Kano 2004/03/16 */
	if (SYB_LC821033_Flg) {					/* LC821033�Ή��t���O Y.Kano 2004/03/16 */
		if (PrinterUseMode == PRINT_SCOPY) {	/* �X�L���i�[�R�s�[�̎� */
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
	
#if (0) /* �l�����^�l�����̒l��ݒ肪�s���S�������̂��C���B �Q�T�O�ɂ���ƃv�����g���T���������ň󎚂ł��Ȃ� */
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
** �Q�S�O�ʂ��ɂ���ƁA�T�����ȓ��ɃX�g���[�u���������Ȃ����Ƃ������
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
 *		�v���q�[�g���̃X�g���[�u�p���X����Ԃ�
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
** �C���[�W�v�����g���̂Q�l�̃v���q�[�g�ύX
** ���삩��̈˗� 1999/02/08 by T.Soneoka
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
**			Time += 0x0a;	/* ���삩��̈˗� 1999/1/13 by T.Soneoka */
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
 #if defined(SATSUKI2)	/* �}�V���p�����[�^SW�Ŏ��Ԃ����鐔��ݒ�\�Bby Y.Kano 2003/09/30 */
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
			** �V���q���A�������΍�
			** �a�S�|���`�S�k���i���{�͂Ȃ��j
			** �X�L���i�R�s�[�i�}���`�R�s�[�͂Ȃ��j
			** �Q�l�e�h�m�d�E�r�e�h�m�d�i�m�������͂Ȃ��j
			** �̏����Ł{�R�W�̃v���q�[�g�I�t�Z�b�g�����܂� �i�d�ݕ�����˗��j
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

#if (0) /* �l�����^�l�����̒l��ݒ肪�s���S�������̂��C���B �Q�T�O�ɂ���ƃv�����g���T���������ň󎚂ł��Ȃ� */
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
 *		Print Buffer, ShiftRegister, LatchRegister ��S���Ŗ��߂�
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
	
	/* G/A�v�����^�o�b�t�@������ 1998/12/14 by T.Soneoka */
	for (loop = 0; loop < 2; loop++) {
/*
** �v�����^�o�b�t�@�͂Q�T�U�~�Q�Ȃ̂ŁA���[�h�łQ�T�U�łO���O�O�𖄂߂��
** �v�����^�o�b�t�@�̎����󂵂Ă��܂�
** 1999/02/23 by T.Soneoka
*/
#if (0)
**		(void)CMN_WordMemorySet((UWORD *)&PrinterBuffer[loop][0], (UWORD)256, 0x00);
#else
		(void)CMN_WordMemorySet((UWORD *)&PrinterBuffer[loop][0], (UWORD)128, 0x00);
#endif
	}

#if (0) /* 1999/01/12 by T.Soneoka */
**	PrintBufferClearMode = TRUE;		/* �T�[�}���w�b�h�Ɏc���Ă���f�[�^���N���A���鏈�� */
#endif
	/*
	 *	PBRDY �����݂�����܂�
	 *	SP INT �ɓ�������Printer DMA �͋֎~
	 */
	PrinterDmaPermission = FALSE;
	PrinterRewriteCount = 1;
	if (QuerySmoothingOn()) {
		PrinterRewriteCount = 2;
	}

	/*
	** �T�[�}���w�b�h�Ɏc���Ă���f�[�^���N���A�����
	** �S���C�����S���ŃT�[�}���w�b�h�ɓ]�����܂�
	*/
	dummyline = 4;
	while (dummyline--) {
		/* �S���f�[�^�Z�b�g */
		(void)GetWritePtrPrtImageBuf();
		IncPrtImageReadableLine();
	};

	PrintBufferClearMode = TRUE;		/* �T�[�}���w�b�h�Ɏc���Ă���f�[�^���N���A���鏈�� */

	EnableIntPbrdy();

	if (PrintDtc) {
		/* �c�q�d�p�[�q��L���ɂ��� */
		SelectPrinterDma();
		/* �c�s�b�̃Z�b�g�^�N�� */
		ImagePtr = GetReadPtrPrtImageBuf();
		PrtDataTrasCount = (SYS_B4_LINE/8/2);	/* B4���[�h�]�� */
		GateArrayWriteDMA_Data.Channel		= DMA_GATEARRAYWRITE_CH;
		GateArrayWriteDMA_Data.SrcAddress	= (UDWORD)ImagePtr;
		GateArrayWriteDMA_Data.Counter		= PrtDataTrasCount;
		GateArrayWriteDMA_Data.Unit			= DMA_WORD_TRANSFER;
		GateArrayWriteDMA_Data.Direction	= DMA_MEMORY_TO_IO;
		DMA_SetupDMAU(&GateArrayWriteDMA_Data);
		DtcPermission = FALSE;
		/* �����`�S�}�X�N�ݒ�����܂� 1999/01/05 by T.Soneoka */
		if (Paper.Size == PAPER_SIZE_A4) {
			for (white_mask = 0; white_mask < CHK_PrinterMaskWhite(); white_mask++) {
				*(ImagePtr+OffsetA4+white_mask) = 0;
			}
		}

		/* �v�����g���[�v�����p add 2 line 1999/1/25 by T.Soneoka */
		if (SYB_MaintenanceSwitch[MNT_SW_H5] & 0x80) {
			RelayPortStatus |= 0x4000;
			OutputWORD(GA_PGADR, RelayPortStatus);
		}
		
		DMA_RequestEnable(GateArrayWriteDMA_Data.Channel);
		/* �v�����g�X�^�[�g */
		GaPstartStatus |= GA_PRINT_START;
		OutputWORD(GA_PSTART, GaPstartStatus);
	} else {
		GaPstartStatus |= GA_PRINT_START;
		OutputWORD(GA_PSTART, GaPstartStatus);
		PrtDataTrasCount = (SYS_B4_LINE/8/2);	/* B4���[�h�]�� */
		ImagePtr = GetReadPtrPrtImageBuf();
		PrtGA_IO_Write((UWORD *)ImagePtr, PrtDataTrasCount);
		if (tskno_PRN_PrintDataTransTask == 0xffff) {
			cre_tsk(&tskno_PRN_PrintDataTransTask, TSK_PRINTDATATRANSTASK, (void *)0);
		}
	}

	/* Printer 5msec �����݋��� */
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
** *		�S�����C���������ăv�����^�̃p�C�v���C������
** *		�C���[�W�f�[�^�������o��
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
**	/* �S�����C���������ĉ����o�� */
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
 *		�v�����g���I�����A�L�^����r�o����悤�w������
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetPrinterCloseRequest(void)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable(); /* �����ݏ�ԕۑ� */
	CMN_DisableInterrupt();					/* �����݋֎~ */

	EnablePrintDataMake = FALSE; /* �v�����g�f�[�^�쐬�J�n���� 1998/12/15 by T.Soneoka */
	PrinterCloseRequest = TRUE;
	
	/* �����ݏ�Ԃ̃��X�g�A */
	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}

 #if defined(SATSUKI2) /* SATSUKI2 �ǉ� start by Y.Kano 2003/06/26 */

UBYTE ExecCutter(void)
{
	/* �X�L���i�[�R�s�[�����܂�ƕ\�����Ԓ����̕s��ׁ̈A�������܂��B�@by Smuratec 2003/11/24 */
#if (1) /* �X�L���i�[�R�s�[�����܂�ƕ\���̕s��ׁ̈A�R�����g�A�E�g���܂��B�@by Smuratec 2003/11/21 */
	UWORD CutterTimeOutCounter;/* 1999/04/13 by T.Soneoka */

	CutterTimeOutCounter = 0;	/* 1999/04/13 by T.Soneoka */
#endif

	if (!CHK_WallHangSetting()) { /** �Ǌ|���ݒ�p�łȂ��� */	/* Add by Y.kano 2003/10/03 */
		CutterOn();	/* �J�b�^�[���ҋ@�ʒu�ɂȂ��Ƃ��̓J�b�^�[���삳���ăJ�b�^�[��ҋ@�ʒu�ɒu�� */
		while (PRN_Control.CutterBusy) {	/* �J�b�^�[����I���҂� */
		/* �X�L���i�[�R�s�[�����܂�ƕ\�����Ԓ����̕s��ׁ̈A�������܂��B�@by Smuratec 2003/11/24 */
#if (1) /* �X�L���i�[�R�s�[�����܂�ƕ\���̕s��ׁ̈A�R�����g�A�E�g���܂��B�@by Smuratec 2003/11/21 */
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

 #else /* SATSUKI2 �ǉ� start by Y.Kano 2003/06/26 */

#if (0) /* �J�b�^�s�ǃ`�F�b�N�ǉ� 1999/04/13 by T.Soneoka */
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

		/* �J�b�^�s�ǃ`�F�b�N�ǉ� 1999/04/13 by T.Soneoka */
		CutterTimeOutCounter++;
		if (CutterTimeOutCounter > 100) {
			Cutter2Off();
			return (NG);
		}

	}
	Cutter2Off();

	return (OK); /* 1999/04/13 by T.Soneoka */
}

 #endif /* SATSUKI2 �ǉ� start by Y.Kano 2003/06/26 */


#if !defined(SATSUKI2)	/* SATSUKI2�ł͎g�p���� by Y.Kano 2003/06/26 */
#if (0) /* �J�b�^�s�ǃ`�F�b�N�ǉ� 1999/04/13 by T.Soneoka */
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

			/* �J�b�^�s�ǒǉ� 1999/04/13 by T.Soneoka */
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
#endif	/* SATSUKI2�ł͎g�p���� by Y.Kano 2003/06/26 */


void PrtGA_IO_Write(
UWORD	*SRC_ptr,	/* �R�s�[���̐擪�A�h���X */
UWORD	CopyCount)		/* �R�s�[�� */
{
	for ( ; CopyCount > 0; CopyCount--) {
		while (InputWORD(GA_SP_REQ) & PREQ);	/* �v�����g�f�[�^�v�����ł�܂ő҂��܂� */
		OutputWORD(GA_PRID, *SRC_ptr++);		/* �v�����g�f�[�^�������� */
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
#if (0) /* �v�����^��M�͒ʐM�Ő����������Ă���̂ŁA�����ł݂͂܂���  1999/02/02 by T.Soneoka */
**	if ((PrinterUseMode == PRINT_RXPRINT)
**	|| ((PrinterUseMode == PRINT_IMAGE) && (SYS_DocumentPrintItem == SYS_MEM_RX_FILE))) {
#else
	/* �C���[�W�v�����g�Ń}���`�R�s�[�v�����g�ȊO�͂R�������`�F�b�N����悤�ɂ��܂� */
	if ((PrinterUseMode == PRINT_IMAGE) && (SYS_DocumentPrintItem != SYS_MEM_MULTI_COPY_FILE)) {
#endif
		if ((Paper.StepsFromPrinting > Print3M_Over)
		&& (CHK_PrintRx3mOver())) {
#if (0) /* ��ʂŃZ�b�g����悤�ɕύX���܂�  1999/02/02 by T.Soneoka */
**			PrinterError |= PRT_ERROR_3M_OVER;
#endif
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_3M_OVER;
			return TRUE;
		}
	}
	return FALSE;
}
