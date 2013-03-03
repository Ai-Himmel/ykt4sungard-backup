/**********************************************************************************************************************
	@(#)$Id: s1_tcf.c,v 1.8 2005/11/17 01:42:02 mi93007 Exp $
	Create        : 2005/06/13
	Author        : �΋����a
	Description   : S1 TCF����
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\define\s1_pro.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\s1_data.h"

#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"

#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"

#include "\src\atlanta\hinoki\define\hino_tib.h"

/**************************************************************************************************/
/**
	@brief		S1�o�R�g���[�j���O��M�����邩�ۂ�
	
	@li			
	@param		
	@return		TRUE:	S1�o�R�Ńg���[�j���O���s��
				FALSE:	S1�͎g�p���Ȃ�
	@note		
	@date		2005/06/16 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
BOOL S1_CheckScramblePossibility(
						UBYTE rate) /* �{�[���[�g */
{
	BOOL ret;
	
	switch (rate) {
	case BPS9600_V17:
	case BPS7200_V17:
	case BPS9600_V29:
	case BPS7200_V29:
	case BPS4800_V27:
	case BPS2400_V27:
		ret = TRUE;
		break;
	default:
		ret = FALSE;
		break;
	}
	
	return ret;
}

BOOL S1_ReceivingTCF_Data;

/**************************************************************************************************/
/**
	@brief		�g���[�j���O��M
	
	@li			
	@param		
	@return		OK:	�g���[�j���O��M�ǍD
				NG:	�t�H�[���o�b�N�K�v
	@note		
	@date		2005/06/13 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_ReceiveTCF(
				UBYTE speed,		/* ���f���^�C�v�E�X�s�[�h */
				BOOL bbypass,		/* S1�o�C�p�X���Ă��邩�ۂ� */
				BOOL* pbscrambled)	/* �X�N�����u���f�[�^���ۂ�(�o��) */
{
	MESSAGE_t* pmdm_msg;

	struct Timer10msData_t timer_eye_q;
	struct Timer10msData_t timer_tcf;
	struct Timer10msData_t timer_tcf_end;
	struct Timer10msData_t timer_tcf_read_time;

	UWORD tcf_time;
	UBYTE tcf_flg;
	UBYTE eye_q_ok;
	UBYTE rtn;

	UBYTE	eyeq_buf[6];	/* EYE-Q�p�o�b�t�@ */

	UWORD tcf_chk_total;	/* �A�����Ă��̉�0����������TCF�`�F�b�NOK */
	UWORD tcf_chk_num1;		/* TCF�t���O1��0���o�� */
	UWORD tcf_chk_num2;		/* TCF�t���O2��0���o�� */
	UBYTE flag1;			/* TCF�`�F�b�N�t���O1 */
	UBYTE flag2;			/* TCF�`�F�b�N�t���O2 */
	
	BOOL bs1_on;			/* S1���L�����ۂ� */
	
	BackUpEYE_Slice = 0;	/* 1996/10/25 Y.M */

	InitializeModemWork();
	ModemTypeSet(speed); /** ���f���^�C�v�ݒ� */

	ModemBlock.Training = TRAINING_LONG;
	ModemBlock.Mode = MODE_RX_TCF; /* ��M���[�h�ݒ� */ /* add 1996/10/18 Y.Murata */

	RxG3_Open();
	MDM_NewT30Status = MODE_RX_TCF;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */

	MDM_SetIO(POS_STRN, OFF); /** Advice for Rockwell by O.Kimoto 1997/01/28 */

	/**	�g���[�j���O���o����	*/
	if (CheckTraining(3500) == NO) {
		RxG3_Close();
		return NG;
	}
	ModemWaitStatus = 0;

	/* ��M�f�[�^�]����	*/
	if (CheckRLSD(3000) == NO) {
		RxG3_Close();
		return NG;
	}

	ModemWaitStatus = 0;

	/* ۯ���ق���̱���޲� by O.Kimoto 1997/01/28 */
	if (ModemBlock.Type	== TYPE_V17) { /* ���f���^�C�v V17�ݒ� */
		MDM_SetIO(POS_STRN,ON);
	}

	/* EQM���[�h�^�X�N�N�� 1996/10/23 Y.Murata */
	MDM_RlsdTurnOffCheckFlag = TRUE;
	MDM_RlsdTurnOnFlag = 0;
	tskno_EyeQualityMonitor = 0xffff;
	cre_tsk(&tskno_EyeQualityMonitor,TSK_MDM_READEQMVALUETASK,0);

	/* 1�b�^�C�}�ݒ�^�C�}�^�X�N�N��(EYE Quality�p) */
	timer_eye_q.Time = (EYE_Q_TIME/10);
	timer_eye_q.SendMBX = mbxno.MDM_Task;
	timer_eye_q.ReturnValue = MSG_EYE_Q_TIME;
	tskno_TimerEYE_Q = 0xFFFF;
	cre_tsk(&tskno_TimerEYE_Q, TSK_CMN_MAN_TIMER10MSTASK, &timer_eye_q);

	/* 1.5�b�^�C�}�ݒ�^�C�}�^�X�N�N��(TCF���ԗp) */
	timer_tcf.Time = (TCF_TIME/10);
	timer_tcf.SendMBX = mbxno.MDM_Task;
	timer_tcf.ReturnValue = MSG_TCF_TIME;
	tskno_TimerTCF = 0xffff;
	cre_tsk(&tskno_TimerTCF, TSK_CMN_MAN_TIMER10MSTASK, &timer_tcf);

	/* 2.0�b�^�C�}�ݒ�^�C�}�^�X�N�N��(TCF END����) */
	timer_tcf_end.Time = (TCF_END_TIME/10);
	timer_tcf_end.SendMBX = mbxno.MDM_Task;
	timer_tcf_end.ReturnValue = MSG_TCF_END_TIME;
	tskno_TimerTCF_End = 0xffff;
	cre_tsk(&tskno_TimerTCF_End, TSK_CMN_MAN_TIMER10MSTASK, &timer_tcf_end);

	/* 10ms�^�C�}�ݒ�^�C�}�^�X�N�N�� */
	timer_tcf_read_time.Time = (TCF_READ_TIME/10);
	timer_tcf_read_time.SendMBX = mbxno.MDM_Task;
	timer_tcf_read_time.ReturnValue = MSG_TCF_READ_TIME;
	tskno_TimerTCF_ReadTime = 0xffff;
	cre_tsk(&tskno_TimerTCF_ReadTime, TSK_CMN_MAN_TIMER10MSTASK, &timer_tcf_read_time);
	
	tcf_time = CHK_UNI_TCF_CheckTime(); /* �[���`�F�b�N���Ԑݒ� */
	if (tcf_time == 0) {
		tcf_time = 100;
	}
	tcf_chk_total = tcf_time / TCF_READ_TIME;
	tcf_chk_num1 = 0;
	tcf_chk_num2 = 0;
	tcf_flg = 0;
	*pbscrambled = FALSE;
	eye_q_ok = 0;
	
	bs1_on = S1_GetScrambleAvailable();
	
	S1_ReceivingTCF_Data = TRUE;
	tskno_S1_ReceiveTCF_Data = 0xFFFF;
	cre_tsk(&tskno_S1_ReceiveTCF_Data, TSK_S1_RECEIVETCF_DATATASK, 0); /* TCF�f�[�^��M�^�X�N�N�� */
	
	S1_TCF_Clear(); /* TCF�`�F�b�N�t���O�N���A */
	
	while (1) {
		rcv_msg(mbxno.MDM_Task, &pmdm_msg);
		
		switch (pmdm_msg->Message) {
		case MSG_TCF_READ_TIME: /* �g���[�j���O �[���`�F�b�N����(10ms�^�C���A�b�v��) */
			if (tskno_TimerTCF_ReadTime != 0xFFFF) {
				del_tsk(&tskno_TimerTCF_ReadTime); /* 10ms�^�C���A�b�v�^�C�}�^�X�N�I�� */
			}
			
			S1_TCF_Detect(&flag1, &flag2); /* TCF�`�F�b�N�t���O���o */
			S1_TCF_Clear(); /* TCF�`�F�b�N�t���O�N���A */
			
			if ((bs1_on == TRUE) && (bbypass == FALSE)) { /* S1���L���̏ꍇ */
				if (flag1 == 0) {
					tcf_chk_num1++;
					if (tcf_chk_num1 == tcf_chk_total) { /* �w�����0�݂̂����o */
						tcf_flg = 1; /* 0�`�F�b�N�I���t���O�Z�b�g */
						if (eye_q_ok) {
							EqualizerHoldOn();
						}
					}
				}
				else {
					tcf_chk_num1 = 0;
				}
			}
			if (flag2 == 0) {
				tcf_chk_num2++;
				if (tcf_chk_num2 == tcf_chk_total) { /* �w�����0�݂̂����o */
					*pbscrambled = TRUE; /* �X�N�����u�� */
					tcf_flg = 1; /* 0�`�F�b�N�I���t���O�Z�b�g */
					if (eye_q_ok) {
						EqualizerHoldOn();
					}
				}
			}
			else {
				tcf_chk_num2 = 0;
			}
			
			if (tcf_flg != 1) { /* 0�`�F�b�N�p�����鎞 */
				tskno_TimerTCF_ReadTime = 0xffff;
				cre_tsk(&tskno_TimerTCF_ReadTime, TSK_CMN_MAN_TIMER10MSTASK, &timer_tcf_read_time); /* 10ms�^�C�}�ݒ�^�C�}�^�X�N�N�� */
			}
			break;
		case MSG_EYE_Q_TIME: /* EYE_Q�`�F�b�N����(1�b�^�C���A�b�v��) */
			if (ModemBlock.Type == TYPE_V17) { /* ���f���^�C�v��V17�̎� */
				if (CHK_V17EqualizerHold()) {
					EqualizerHoldOn(); /* �C�R���C�U�z�[���h�ݒ� */
				}
			}
			if (CheckSlice(speed) == YES) {
				eye_q_ok = 1; /* �d�x�d�`�F�b�N�t���O�ݒ� */
				if (tcf_flg) {
					EqualizerHoldOn();
				}
			}
			break;
		case MSG_TCF_TIME: /* RLSD OFF���o�J�n�ݒ�(1.5�b�^�C���A�b�v��) */
			S1_ReceivingTCF_Data = FALSE;
			
			/*	���f���X�e�[�^�X�Ď��^�X�N�N��	*/
			tskno_ModemStatusCheck = 0xffff;
			ModemStatusFlag = 0;
			ModemWaitStatus = (PHS_STAT_CHECK_SEQ_BIT + PHS_STAT_CHECK_RLSDOFF); /* RLSD OFF�`�F�b�N�ݒ� */
			cre_tsk(&tskno_ModemStatusCheck, TSK_MDM_MODEMSTATUSCHECKTASK, &mbxno.MDM_Task); /** ���f���X�e�[�^�X�Ď��^�X�N�N�� */
			break;
		case MSG_ENABLE_MODEM_STATUS: /* RLSD OFF���o�� */
			/* �o�b�t�@�Ƀg���[�j���O�f�[�^���c���Ă��鎞(�O�̂���) */
			goto END;
		case MSG_TCF_END_TIME: /* �g���[�j���O�Ď��I������(TCF END 2�b�^�C���A�b�v��) */
			goto END;
		default:
			break;
		}
	}
	
END:
	if (eye_q_ok && tcf_flg) {
		
		
		
		/* �b��΍� */
		if (*pbscrambled == TRUE) {
			if (tcf_chk_num1 > (tcf_chk_num2 - 5)) {
				*pbscrambled = FALSE;
			}
		}
		
		
		
		rtn = OK;
	}
	else {
		rtn = NG;
	}
	if (tskno_TimerTCF_ReadTime != 0xffff) {
		del_tsk(&tskno_TimerTCF_ReadTime);
	}
	if (tskno_TimerEYE_Q != 0xffff) {
		del_tsk(&tskno_TimerEYE_Q); /* 1�b�^�C�}�ݒ�^�C�}�^�X�N�I�� */
	}
	if (tskno_TimerTCF != 0xffff) {
		del_tsk(&tskno_TimerTCF); /* 1.5�b�^�C�}�ݒ�^�C�}�^�X�N�I��(TCF���ԗp) */
	}
	if (tskno_TimerTCF_End != 0xffff) {
		del_tsk(&tskno_TimerTCF_End); /* 2.0�b�^�C�}�ݒ�^�C�}�^�X�N�I��(TCF END����) */
	}
	if (tskno_ModemStatusCheck != 0xffff) {
		del_tsk(&tskno_ModemStatusCheck); /* ���f���X�e�[�^�X�Ď��^�X�N */
	}
	ModemStatusFlag = 0;
	
	MDM_RlsdTurnOffCheckFlag = FALSE;
	if (tskno_EyeQualityMonitor != 0xffff) {
		del_tsk(&tskno_EyeQualityMonitor); /* EQM�l���[�h�^�X�N 1996/10/23 Y.Murata */
	}

	RxG3_Close(); /* TCF���f���N���[�Y����	*/

	eyeq_buf[0] = (UBYTE)(SYS_EyeQ_Level & 0x00FF);
	eyeq_buf[1] = (UBYTE)((SYS_EyeQ_Level & 0xFF00) >> 8);
/* debug ��r����ð��ْl�̍ڂ��� */
	eyeq_buf[2] = (UBYTE)(BackUpEYE_Slice & 0x00FF);		/* add 1996/10/25 Y.M */
	eyeq_buf[3] = (UBYTE)((BackUpEYE_Slice & 0xFF00) >> 8);	/* add 1996/10/25 Y.M */
/* debug receiveLevel */
	eyeq_buf[4] = (UBYTE)(MDM_V21MeasureReceiveLevel & 0x00FF);		/* add 1997/01/28 Y.M */
	eyeq_buf[5] = (UBYTE)((MDM_V21MeasureReceiveLevel & 0xFF00) >> 8);	/* add 1997/01/28 Y.M */

	SaveT30Data(SYS_T30_RX_TCF, &eyeq_buf[0], 6);	/* 2->4->6 1997/01/28 1996/10/25 Y.M */
	SaveT30TimingData(SYS_T30_END_TIME);

	return (rtn);
}

/**************************************************************************************************/
/**
	@brief		TCF�f�[�^��M�^�X�N
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/08/23 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_ReceiveTCF_DataTask(void)
{
	UBYTE correct_readpoint;
	
	correct_readpoint = 1;
	
	while (1) {
		if ((ModemControl.UsedCount >= MODEM_BUFFER_MAX) && (correct_readpoint)) {
			CMN_DisableInterrupt();	/**	���荞�݋֎~	*/
			if (ModemControl.WritePoint == (MODEM_BUFFER_MAX-1)) {
				ModemControl.ReadPoint = 0;
			}
			else {
				ModemControl.ReadPoint = (UBYTE)(ModemControl.WritePoint + 1);
			}
			CMN_EnableInterrupt();	/**	���荞�݋���	*/
		}
		correct_readpoint = 0;
		
		if (RxG3_Read() == RCV_BLOCK){	/**	���f���o�b�t�@�ǂݏo���^�P�u���b�N��M������	*/
			NextMdmBufReadPointSetExtRom();
		}
		else {	/**	�X�g�b�v�r������	*/
			break;
		}
		
		if (S1_ReceivingTCF_Data == FALSE) {
			break;
		}
	}
	
	exi_tsk();
}

