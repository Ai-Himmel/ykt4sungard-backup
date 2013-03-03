/************************************************************************
*	System		: SATSUKI2
*	File Name	: OPR_VOL.C
*	Author		: ���[  �`�F
*	Date		: 2003/08/29
*	RealTimeOS	: �q�h�r�b�i�r�g�V�O�S�R�j���j�^�[
*	Description	: �{�����[���ݒ�I�y���[�V����
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\unisw_h.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\cmn_def.h"

#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/09/01 */
#include	"\src\atlanta\ext_v\sys_data.h"
#endif

/* Prototype
void	VolumeKeyOperation(void);
UBYTE 	ChangeBuzzerVolume(void)
void 	DisplayHighBuzzerVolume(void)
UBYTE 	ChangeMonitorVolume(void)
void 	DisplayHighMonitorVolume(void)
UBYTE 	SetRingerControl(void)
*/


#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By Y.Kano 2003/08/29 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)/* DVT : mod by SMuratec C.P 2004/09/06 */
/*************************************************************************
	module		:[�{�����[���ݒ�I�y���[�V����]
	function	:[
		1.�u�U�[���ʒ������s��
		2.���j�^�[���ʒ������s��
		3.�����K�[����ݒ���s��
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/05]
	author		:[���[]
*************************************************************************/
void VolumeKeyOperation(void)
{
	UBYTE	key;				/* ���ͷ��ް� 	*/
	UBYTE	keytype;			/* ���ͷ����� 	*/
	UBYTE	select;				/* �I���׸�   	*/
	UBYTE	result;

	select = 0x00;				/* �޻ް��ح�ёI����� */
	result = OK;
	DispChangeFlag = FALSE;

	/* ��i�\�� */
	DisplayStringHigh(0, D2W_BuzzerVolume);			/* "01.�޻ް ����� ��خ�" */

	/* ���i�_�ŕ\�� */
	FlashDisplayStringLow(D2W_BuzzerVolumeEnter);	/* "            ��/��/��� " */

	while(1) {
		/** �L�[��荞�� */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** ��荞�񂾃L�[�ɑ΂��鏈�������s */
		switch (keytype) {
		case LEFT_ARROW:	/* �����L�[ */
			switch(select) {
			case 0x00:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_RingerControl);	/* "03.����� ���        " */
				select = 0x02;								/* ������ح�ёI���ɐ؊��� */
				break;
			case 0x01:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.�޻ް������ ��خ�" */
				select = 0x00;								/* ������ح�ёI���ɐ؊��� */
				break;
			case 0x02:
			default:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.���� ��خ�       " */
				select = 0x01;								/* �޻ް��ح�ёI���ɐ؊��� */
				break;
			}
			break;
		case FUNCTION:		/* �@�\�^���L�[ */
		case VOLUME:		/* ���ʒ����L�[ */
			switch(select) {
			case 0x00:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.���� ��خ�       " */
				select = 0x01;								/* �޻ް��ح�ёI���ɐ؊��� */
				break;
			case 0x01:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_RingerControl);	/* "03.����� ���        " */
				select = 0x02;								/* ������ح�ёI���ɐ؊��� */
				break;
			case 0x02:
			default:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.�޻ް������ ��خ�" */
				select = 0x00;								/* ������ح�ёI���ɐ؊��� */
				break;
			}
			break;
		case ENTER:
			switch(select) {
			case 0x00:
				result = ChangeBuzzerVolume();				/* �޻ް���ʒ��� */
				break;
			case 0x01:
				result = ChangeMonitorVolume();				/* �������ʒ��� */
				break;
			case 0x02:
			default:
				result = SetRingerControl();				/* �ݶް����ݒ� */
				break;
			}
			break;
		case STOP:
		case KEY_TIME_UP:
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
		if (DispChangeFlag) {		/* �{�����[����������ENTER�L�[�������ꂽ�ꍇ�A�\���ؑւ��K�v */
			DispChangeFlag = FALSE;

			switch(select) {
			case 0x00:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.���� ��خ�       " */
				select = 0x01;								/* �޻ް��ح�ёI���ɐ؊��� */
				break;
			case 0x01:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_RingerControl);	/* "03.����� ���        " */
				select = 0x02;								/* ������ح�ёI���ɐ؊��� */
				break;
			case 0x02:
			default:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.�޻ް������ ��خ�" */
				select = 0x00;								/* ������ح�ёI���ɐ؊��� */
				break;
			}
		}
		if (result == NG) {
			return;
		}
	}
}
#else /* (PRO_KEYPANEL == PANEL_STOCKHM2) */
/*************************************************************************
	module		:[�{�����[���ݒ�I�y���[�V����]
	function	:[
		1.�u�U�[���ʒ������s��
		2.���j�^�[���ʒ������s��
		3.�����K�[����ݒ���s��
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/05]
	author		:[���[]
*************************************************************************/
void VolumeKeyOperation(void)
{
	UBYTE	key;				/* ���ͷ��ް� 	*/
	UBYTE	keytype;			/* ���ͷ����� 	*/
	UBYTE	select;				/* �I���׸�   	*/
	UBYTE	result;

	select = 0x00;				/* �޻ް��ح�ёI����� */
	result = OK;
	DispChangeFlag = FALSE;

	/* ��i�\�� */
	DisplayStringHigh(0, D2W_BuzzerVolume);			/* "01.�޻ް ����� ��خ�" */

	while(1) {

		/* ���i�_�ŕ\�� */
		FlashDisplayStringLow(D2W_ProgramEnter);		/* "            �ɳ/��� " */

		/** �L�[��荞�� */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** ��荞�񂾃L�[�ɑ΂��鏈�������s */
		switch (keytype) {
		case LEFT_ARROW:	/* �����L�[ */
			switch(select) {
			case 0x00:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.���� ��خ�       " */
				select = 0x01;								/* ������ح�ёI���ɐ؊��� */
				break;
			case 0x01:
			default:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.�޻ް������ ��خ�" */
				select = 0x00;								/* ������ح�ёI���ɐ؊��� */
				break;
			}
			break;
		case FUNCTION:		/* �@�\�^���L�[ */
		case VOLUME:		/* ���ʒ����L�[ */
			switch(select) {
			case 0x00:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.���� ��خ�       " */
				select = 0x01;								/* �޻ް��ح�ёI���ɐ؊��� */
				break;
			case 0x01:
			default:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.�޻ް������ ��خ�" */
				select = 0x00;								/* ������ح�ёI���ɐ؊��� */
				break;
			}
			break;
		case ENTER:
			switch(select) {
			case 0x00:
				result = ChangeBuzzerVolume();				/* �޻ް���ʒ��� */
				break;
			case 0x01:
			default:
				result = ChangeMonitorVolume();				/* �������ʒ��� */
				break;
			}
			break;
		case STOP:
		case KEY_TIME_UP:
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
		if (DispChangeFlag) {		/* �{�����[����������ENTER�L�[�������ꂽ�ꍇ�A�\���ؑւ��K�v */
			DispChangeFlag = FALSE;

			switch(select) {
			case 0x00:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_MonitorVolume);	/* "02.���� ��خ�       " */
				select = 0x01;								/* �޻ް��ح�ёI���ɐ؊��� */
				break;
			case 0x01:
			default:
				/* ��i�\�� */
				DisplayStringHigh(0, D2W_BuzzerVolume);		/* "01.�޻ް������ ��خ�" */
				select = 0x00;								/* ������ح�ёI���ɐ؊��� */
				break;
			}
		}
		if (result == NG) {
			return;
		}
	}
}
#endif 
/*************************************************************************
	module		:[�u�U�[���ʒ���]
	function	:[
		1.�u�U�[���ʒ�����ʕ\��
		2.�u�U�[���ʒ����Ɠ����Ƀu�U�[����������.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/08/29]
	author		:[�]��]
*************************************************************************/
UBYTE ChangeBuzzerVolume(void)
{
	UBYTE	key;				/* ���ͷ��ް� 	*/
	UBYTE	key_type;			/* ���ͷ����� 	*/
	UBYTE	is_loop_end;

	is_loop_end = FALSE;

	/* ��i�\�����[�f�B���O�̃Z�b�g */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_ChangeVolume);			/* "  ��ح��:           " */

	while (is_loop_end == FALSE) {

		SYS_KeyTouchFrequencySetting = 1;	/* �L�[�^�b�`���F�ݒ�I�y���[�V���������ʃt���O */

		/* �L�[�u�U�[�{�����[���������\�� */
		DisplayHighBuzzerVolume();

		/** �L�[��荞�� */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		key_type = GetInputKeyType();

		switch (key_type) {
		case FUNCTION:		/* �@�\�^���L�[ */
		case VOLUME:		/* ���ʒ����L�[ */
			/* �{�����[���A�b�v */
			if (SYB_BuzzerOutLevel >= KEY_BUZZER_VOLUME_MAX) {	/* �u�U�[�萔�ύX by Y.Kano 2003/10/10 */
				SYB_BuzzerOutLevel = KEY_BUZZER_VOLUME_MAX;
/*			if (SYB_BuzzerOutLevel >= BUZZER_VOLUME_MAX) {
				SYB_BuzzerOutLevel = BUZZER_VOLUME_MAX;*/
				NackBuzzer();
			}
			else {
				SYB_BuzzerOutLevel++;

				/* �u�U�[����������ł��Bby Y.Kano 2003/09/01 */
				SYS_KeyTouchFrequencySetting = 0;	/* �L�[�^�b�`���F�ݒ�I�y���[�V���������ʃt���O */
				SYS_AckBuzzerFlag = 0;	/* AckBuzzer��ON�� */
				/** �A�b�N�u�U�[��炷 */
				AckBuzzer();
			}
			break;
		case LEFT_ARROW:	/* �����L�[ */
			/* �{�����[���_�E�� */
			if (SYB_BuzzerOutLevel <= KEY_BUZZER_VOLUME_OFF) {	/* �u�U�[�萔�ύX by Y.Kano 2003/10/10 */
				SYB_BuzzerOutLevel = KEY_BUZZER_VOLUME_OFF;
/*			if (SYB_BuzzerOutLevel <= BUZZER_VOLUME_OFF) {
				SYB_BuzzerOutLevel = BUZZER_VOLUME_OFF;*/
				NackBuzzer();
			}
			else {
				SYB_BuzzerOutLevel--;

				/* �u�U�[����������ł��Bby Y.Kano 2003/09/01 */
				SYS_KeyTouchFrequencySetting = 0;	/* �L�[�^�b�`���F�ݒ�I�y���[�V���������ʃt���O */
				SYS_AckBuzzerFlag = 0;	/* AckBuzzer��ON�� */
				/** �A�b�N�u�U�[��炷 */
				AckBuzzer();
			}
			break;
		case NO_EFFECT:
			break;
		case ENTER:
			/* �u�U�[����������ł��Bby Y.Kano 2003/09/01 */
			SYS_KeyTouchFrequencySetting = 0;	/* �L�[�^�b�`���F�ݒ�I�y���[�V���������ʃt���O */
			SYS_AckBuzzerFlag = 0;	/* AckBuzzer��ON�� */
			/** �A�b�N�u�U�[��炷 */
			AckBuzzer();

			DispChangeFlag = TRUE;
			is_loop_end = TRUE;
			return(OK);
		case STOP:
			/* �u�U�[����������ł��Bby Y.Kano 2003/09/01 */
			SYS_KeyTouchFrequencySetting = 0;	/* �L�[�^�b�`���F�ݒ�I�y���[�V���������ʃt���O */
			SYS_AckBuzzerFlag = 0;	/* AckBuzzer��ON�� */
			/** �A�b�N�u�U�[��炷 */
			AckBuzzer();

			is_loop_end = TRUE;
			return(NG);
		case KEY_TIME_UP: /* �L�[�҂��^�C���I�[�o�[ */
			SYS_KeyTouchFrequencySetting = 0;	/* �L�[�^�b�`���F�ݒ�I�y���[�V���������ʃt���O */
			SYS_AckBuzzerFlag = 0;	/* AckBuzzer��ON�� */
			is_loop_end = TRUE;
			return(NG);
		default:
			NackBuzzer();
			break;
		}
	}
}


/*************************************************************************
	module		:[�u�U�[�{�����[���������\��]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/08/29]
	author		:[���[]
*************************************************************************/
void DisplayHighBuzzerVolume(void)
{
	/* �{�����[���\���ύX by Y.Kano 2003/09/08 */
	CMN_MemorySet(&FunctionDisplayBufferHigh[7], 12, ' ');
/*	CMN_MemorySet(&FunctionDisplayBufferHigh[9], 6, ' ');*/

	switch (SYB_BuzzerOutLevel) {
	case KEY_BUZZER_VOLUME_OFF:		/* �{�����[�� OFF 	*/ /* �u�U�[�萔�ύX by Y.Kano 2003/10/10 */
/*	case BUZZER_VOLUME_OFF:*/		/* �{�����[�� OFF 	*/
		break;
	case KEY_BUZZER_VOLUME_MIN:		/* �{�����[����		*/ /* �u�U�[�萔�ύX by Y.Kano 2003/10/10 */
/*	case BUZZER_VOLUME_MIN:*/		/* �{�����[����		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		break;
	case KEY_BUZZER_VOLUME_MID:		/* �{�����[����		*/ /* �u�U�[�萔�ύX by Y.Kano 2003/10/10 */
/*	case BUZZER_VOLUME_MID:*/		/* �{�����[����		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		FunctionDisplayBufferHigh[11] = 0x2B;
		FunctionDisplayBufferHigh[12] = 0x2B;
		FunctionDisplayBufferHigh[13] = 0x2B;
		FunctionDisplayBufferHigh[14] = 0x2B;
		break;
	case KEY_BUZZER_VOLUME_MAX:		/* �{�����[����		*/ /* �u�U�[�萔�ύX by Y.Kano 2003/10/10 */
/*	case BUZZER_VOLUME_MAX:*/		/* �{�����[����		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++++++++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		FunctionDisplayBufferHigh[11] = 0x2B;
		FunctionDisplayBufferHigh[12] = 0x2B;
		FunctionDisplayBufferHigh[13] = 0x2B;
		FunctionDisplayBufferHigh[14] = 0x2B;
		FunctionDisplayBufferHigh[15] = 0x2B;
		FunctionDisplayBufferHigh[16] = 0x2B;
		FunctionDisplayBufferHigh[17] = 0x2B;
		FunctionDisplayBufferHigh[18] = 0x2B;
		break;
	default:
		break;
	}
	/* ��i�\�� */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

 #if defined(STOCKHM2) /* DVT : Mod by SMuratec C.P 2004/09/06 */
	/* ���i�_�ŕ\�� */
	FlashDisplayStringLow(D2W_BuzzerVolumeEnter);	/* "            ��/��/��� " */
 #endif


}

/*************************************************************************
	module		:[���j�^�[���ʒ���]
	function	:[
		1.���j�^�[���ʒ�����ʕ\��
		2.��i�\���̂ݍX�V����.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/08/29]
	author		:[�]��]
*************************************************************************/
UBYTE ChangeMonitorVolume(void)
{
	UBYTE	key;				/* ���ͷ��ް� 	*/
	UBYTE	key_type;			/* ���ͷ����� 	*/
	UBYTE	is_loop_end;

	is_loop_end = FALSE;

	/* ��i�\�����[�f�B���O�̃Z�b�g */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_ChangeVolume);			/* "  ��ح��:           " */

	while (is_loop_end == FALSE) {

		/* �X�s�[�J�[�{�����[���������\�� */
		DisplayHighMonitorVolume();

		/** �L�[��荞�� */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		key_type = GetInputKeyType();

		switch (key_type) {
		case FUNCTION:		/* �@�\�^���L�[ */
		case VOLUME:		/* ���ʒ����L�[ */
			/* �{�����[���A�b�v */
			if (SYB_MonitorSpeakerOutLevel == SYS_VOLUME_MAXIMUM) {
				NackBuzzer();
			}
			else {
				SYB_MonitorSpeakerOutLevel++;
			}
			break;
		case LEFT_ARROW:	/* �����L�[ */
			/* �{�����[���_�E�� */
			if (SYB_MonitorSpeakerOutLevel == SYS_VOLUME_OFF) {
				NackBuzzer();
			}
			else {
				SYB_MonitorSpeakerOutLevel--;
			}
			break;
		case NO_EFFECT:
			break;
		case ENTER:
			DispChangeFlag = TRUE;
			is_loop_end = TRUE;
			return(OK);
		case STOP:
		case KEY_TIME_UP: /* �L�[�҂��^�C���I�[�o�[ */
			is_loop_end = TRUE;
			return(NG);

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[���j�^�[�{�����[���������\��]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/08/29]
	author		:[���[]
*************************************************************************/
void DisplayHighMonitorVolume(void)
{
	CMN_MemorySet(&FunctionDisplayBufferHigh[7], 12, ' ');

	switch (SYB_MonitorSpeakerOutLevel) {
	case SYS_VOLUME_OFF:		/* �{�����[��OFF	*/
		break;
	case SYS_VOLUME_MINIMUM:	/* �{�����[����		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		break;
	case SYS_VOLUME_MIDDLE:		/* �{�����[����		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		FunctionDisplayBufferHigh[11] = 0x2B;
		FunctionDisplayBufferHigh[12] = 0x2B;
		FunctionDisplayBufferHigh[13] = 0x2B;
		FunctionDisplayBufferHigh[14] = 0x2B;
		break;
	case SYS_VOLUME_MAXIMUM:	/* �{�����[����		*/
		FunctionDisplayBufferHigh[7]  = 0x2B;		/* ++++++++++++ */
		FunctionDisplayBufferHigh[8] =  0x2B;
		FunctionDisplayBufferHigh[9]  = 0x2B;
		FunctionDisplayBufferHigh[10] = 0x2B;
		FunctionDisplayBufferHigh[11] = 0x2B;
		FunctionDisplayBufferHigh[12] = 0x2B;
		FunctionDisplayBufferHigh[13] = 0x2B;
		FunctionDisplayBufferHigh[14] = 0x2B;
		FunctionDisplayBufferHigh[15] = 0x2B;
		FunctionDisplayBufferHigh[16] = 0x2B;
		FunctionDisplayBufferHigh[17] = 0x2B;
		FunctionDisplayBufferHigh[18] = 0x2B;
		break;
	default:
		break;
	}
	/* ��i�\�� */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

 #if defined(STOCKHM2) /* DVT : Mod by SMuratec C.P 2004/09/06 */
	/* ���i�_�ŕ\�� */
	FlashDisplayStringLow(D2W_BuzzerVolumeEnter);	/* "            ��/��/��� " */
 #endif
}

/*************************************************************************
	module		:[�����K�[����ݒ�]
	function	:[
		1.�����K�[����ݒ��ʕ\��
		2.�@�\�L�[�Ń����K�[ON/OFF�̑I���B
		3.SET�L�[�Ń����K�[����ݒ�B
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/09/18]
	author		:[���[�`�F]
*************************************************************************/
UBYTE SetRingerControl(void)
{
	UBYTE	key;				/* ���ͷ��ް� 	*/
	UBYTE	key_type;			/* ���ͷ����� 	*/
	UBYTE	is_loop_end;

	is_loop_end = FALSE;

	/* ��i�\�����[�f�B���O�̃Z�b�g */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	if (SYB_RingOut) {
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_RingerControlOn);		/* "����� ���  : ON     " */
	}
	else {
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_RingerControlOff);	/* "����� ���  : OFF    " */
	}
	/* ��i�\�� */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	while (is_loop_end == FALSE) {

		/** �L�[��荞�� */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		key_type = GetInputKeyType();

		switch (key_type) {
		case FUNCTION:		/* �@�\�^���L�[ */
		case LEFT_ARROW:	/* �����L�[ */
		case VOLUME:		/* ���ʒ����L�[ */
			/* ON��OFF�AOFF��ON */
			if (SYB_RingOut) {
				CMN_StringCopy(FunctionDisplayBufferHigh, D2W_RingerControlOff);	/* "����� ���  : OFF    " */
				/* ��i�\�� */
				DisplayStringHigh(0, FunctionDisplayBufferHigh);
				SYB_RingOut = FALSE;
			}
			else {
				CMN_StringCopy(FunctionDisplayBufferHigh, D2W_RingerControlOn);		/* "����� ���  : ON     " */
				/* ��i�\�� */
				DisplayStringHigh(0, FunctionDisplayBufferHigh);
				SYB_RingOut = TRUE;
			}
			break;
		case NO_EFFECT:
			break;
		case ENTER:
			if (SYB_RingOut) {
				RingerControlSet();		/* �����K�[����n�m 	*/
			}
			else {
				RingerControlReset();	/* �����K�[����n�e�e 	*/
			}
			DispChangeFlag = TRUE;
			is_loop_end = TRUE;
			return(OK);
		case STOP:
		case KEY_TIME_UP: /* �L�[�҂��^�C���I�[�o�[ */
			is_loop_end = TRUE;
			return(NG);

		default:
			NackBuzzer();
			break;
		}
	}
}



#endif
