/**********************************************************************************************************************
	@(#)$Id: fcm_srrx.c,v 1.22 2006/01/10 09:34:05 mi93007 Exp $
	Create        : 2005/07/10
	Author        : �΋����a
	Description   : ��Ďw�ߎ�M
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#if !defined (KEISATSU)
	UBYTE NoIsseiRx; 
#else
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\hinoki\define\mpr_pro.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\define\m_param.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"

BOOL IsseiRxDCN_Received; /* DCN����M�������ۂ� */

/**************************************************************************************************/
/**
	@brief		��Ďw�ߎ�M
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/10 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiRx(
			BOOL bshirei) /* �w�ߋN���M���̗L�� */
{
#if defined (KEISATSU) /* �x�@FAX 05/09/20 �΋����a */
	/* �w�ߋN����M�̏ꍇ�A�������s�肾���� 06/01/10 �΋����a */
	if (bshirei == TRUE) {
		FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_ISSEI;
		if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SCRAMBLE_KANYU) {
			FCM_ExecutingS1Info.Available = FALSE;
		}
		else {
			FCM_ExecutingS1Info.Available = TRUE;
		}
		if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SENYOU) {
			FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
		}
		else {
			FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
		}
	}
	
	FCM_S1_Scramble = FCM_ExecutingS1Info.Available;
	if (CMN_CheckScrambleSwOn() == FALSE) { /* �w�ʃX�C�b�`��OFF�̏ꍇ */
		FCM_S1_Scramble = FALSE;
	}
	
	if (FCM_ExecutingS1Info.Method == SYS_S1_SENYO) {
		FCM_S1_Senyo = TRUE;
	}
	else {
		FCM_S1_Senyo = FALSE;
	}
#endif
	
	/* SYS_TRANSFER_AUTO_CALLED�̓������Q�� */
	
	/* ForwardReceiveFlag = 1; */					/** �]����M�t���O�Z�b�g */
	/* BackUpForwardReceiveFlag = 1; */			/** �]����M�o�b�N�A�b�v�t���O�Z�b�g */
	
	
	
	/* SYS_FaxComType = SYS_AUTO_CALLED; */		/* ��M��ʍĐݒ� */
	SYS_FaxComType = SYS_MANUAL_RX;


	/* GetFaxComTxType(); */						/** ���M�^�C�v�m�� */
	SYS_FaxComTxType = SYS_MEMORY_TRANSMIT; /* �Ȃ��������Ȃ��Ă��� */
	
	
	
	/*-------------*/
	/** �k�b�c�\�� */
	/*-------------*/
	SYS_FaxCommStage = FCM_CALLED;
	MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
	snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);

	rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* ���C����胁�b�Z�[�W��M */

	/* �x�@FAX DVT_ID81 Added By SMuratec �� 2005/12/21 */
	if (bshirei == TRUE) {
		IsSHIREIKido = FALSE;
	}

	FCM_IsseiRxBody(bshirei);

	if (bshirei == TRUE) {
		SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_FAXCOM;
		if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
			SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_SHIREI_IDLE;
		}
		else {
			SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_IDLE;
		}
	}
	
	/* �߰�ݸޑ��M��RTN��M������T.4.2�ɂ��� 1996/10/30 Y.Murata */
	CheckAllErrorPage();					/** T.4.2�G���[���o�����ǂ����`�F�b�N */
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߎ�M�{��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����AutoCalled() + FaxReceive()
	@date		2005/07/11 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiRxBody(
				BOOL bshirei) /* �w�ߋN���M���̗L�� */
{
	UBYTE ring_time; /* ��Ė����� */
	UBYTE result;
	
	IsseiRxDCN_Received = FALSE;
	
	FaxComPerformingFlag = 1;			/** �ʐM���t���O�Z�b�g */

	FaxcomRelayControl();				/** �����`�Z�b�g */
#if defined(POPLAR_F)
	MDM_SetAnswerMode();			/** ���f�����[�h�Z�b�g */
#endif
	FaxComTXorRX_Sign = RX_COM_MODE;	/** ��M�R�}���h�Z�b�g */
	
	
#if (PRO_LINENUMBER == TWICE_LINE)	/* �^���Q����d�l by T.Soneoka 1997/11/20 */
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {		/**	�W�����C���ɂĎ�M��	*/
		SYS_RingCounter = 0;
	}
	else {
		SYS_RingCounterExt = 0;
	}
#else
	SYS_RingCounter = 0;
#endif
	
	if (FaxComPerformingFlag != 1) {
		goto END;
	}
	
	FaxComStartTime = SYB_CurrentTime;
	
	SYS_FCM_StartTime = SYS_1SecGeneralTimer; /* �p�`�s���ɒʐM�L�^�̒ʐM���Ԃ����ۂ̎��ԂƈقȂ�s��΍��p */

	/* �W���[�i���ʔԃZ�[�u */
	JournalTxTotalCount				= SYB_TxTotalCount;			/* �ʐM�J�n���ԂƏI�����Ԃœ��t���ς�����ꍇ�́A */
	JournalRxTotalCount				= SYB_RxTotalCount;			/* �ʐM�J�n���̓��t�ɍ��킹�邽�߂ɃZ�[�u���Ă��� */
#if (PRO_LINENUMBER == TWICE_LINE)	/* �^���Q����d�l by T.Soneoka 1998/03/11 */
	JournalTxTotalCountExt			= SYB_TxTotalCountExt;
	JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_JournalWorkFile.Number = JournalRxTotalCount;
	PAT_JournalWorkFile.StartTime = FaxComStartTime;

	PAT_JournalDataToImage(NUMBER);
	PAT_JournalDataToImage(START);
#endif
	
	MonitorSpeakerOn(); /* ���j�^�[�X�s�[�JON */
	FCM_S1_Preamble3S = TRUE; /* �ŏ���DCS�̃v���A���u����3�b */
	
	if (bshirei == TRUE) {
		result = FCM_IsseiRxPhaseB1(FCM_ISSEI_RX_WAIT_OPR); /* �t�F�[�YB1 */
		FaxComStartTime = SYB_CurrentTime;
		
		
		
		/* �w�ߋN����M�̏ꍇ�́AFCM�^�X�N�N����ɑ������ς�邱�Ƃ����� 06/01/10 �΋����a */
		FCM_S1_Bypass = CHK_BypassS1();
		S1_BypassS1(FCM_S1_Bypass); /* S1�o�C�p�X�̃Z�b�g */
		S1_SetScrambleAvailable(CHK_ScrambleAvailabe()); /* �X�N�����u���̗L��/�����̃Z�b�g */
		
		FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_ISSEI;
		
		if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SCRAMBLE_KANYU) {
			FCM_ExecutingS1Info.Available = FALSE;
		}
		else {
			FCM_ExecutingS1Info.Available = TRUE;
		}
		FCM_S1_Scramble = FCM_ExecutingS1Info.Available;
		if (CMN_CheckScrambleSwOn() == FALSE) { /* �w�ʃX�C�b�`��OFF�̏ꍇ */
			FCM_S1_Scramble = FALSE;
		}
		
		if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SENYOU) {
			FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
			FCM_S1_Senyo = TRUE;
		}
		else {
			FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
			FCM_S1_Senyo = FALSE;
		}
		
		
		
	}
	else {
		result = FCM_IsseiRxPhaseB1(FCM_ISSEI_RX_WAIT_CNG); /* �t�F�[�YB1 */
	}
	
	FCM_S1_Preamble3S = FALSE;
	if (!CHK_LineMonitor()) {
		MonitorSpeakerOff(); /* ���j�^�[�X�s�[�JOFF */
	}
	
	switch (result) {
	case FCM_ISSEI_RX_DETECT_CNG: /* CNG���o */
		FCM_S1_Scramble = FALSE;
		FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;
		FCM_ExecutingS1Info.Available = FALSE;
		AutoCalled();
		return;
	case FCM_ISSEI_RX_START_TX: /* �X�^�[�g�L�[���� */
		SYS_FaxComType = SYS_ISSEI_KIDO_TX;
		FCM_IsseiTx(TRUE); /* ��Ďw�ߑ��M */
		return;
	default:
		break;
	}
	
	while ((FaxComPerformingFlag == 1) && (FaxComRxPerformingFlag == 1)) {
		
		/**********************************************************************/
		/* FaxReceive()�̕��� */
		
		RxEOM_ReceiveFlag  = 0;			/*�u�d�n�l��M�v�t���O	*/
		
		if ((FaxComPerformingFlag == 1) && (SYS_FaxComStopSwitch() == 0)) { /* �ʐM�� & StopSwitch�Ȃ� */
			FaxComPhaseStatus = FAX_RX_PH_B2; /* Phase B */
			
			FCM_IsseiRxNegotiate(); /* ��M���@�m�� */
			RxModeChangeRequestedFlag = 0; /* ��M���[�h�ύX�v���Ȃ� */
			
			FaxTimer(50); /* R.3.3�΍� FSK->PIX����S1�o�R�ւ̐؂�ւ� 05/12/22 �΋����a */
			
			while( ( FaxComPerformingFlag == 1 )
				&& ( RxModeChangeRequestedFlag == 0 )
				&& ( SYS_FaxComStopSwitch() == 0 )){			/** �ʐM�� & ��M���[�h�ύX�v���Ȃ� & StopSwitch�Ȃ� */
				
				/****************************************************/
				FCM_IsseiRxPhaseC(); /* �t�F�[�YC */
				
				if (FaxComPerformingFlag == 1) {	/**	�ʐM�� (��f�[�^��M���ʂn�j)	*/
					FCM_IsseiRxPostMessage(); /* ���ߎ�M */
				}
				if (FaxComPerformingFlag == 1) { /* ��f�[�^��M�C�|�X�g���b�Z�[�W��M�n�j */
					FCM_IsseiRxPhaseD(); /* ��M�t�F�[�Y�c */
				}
				else {		/**	��f�[�^��M�m�f�^�|�X�g���b�Z�[�W��M�m�f	*/
					/* ��������M�y�[�W���폜(�A���ݒ�ɂ���M���e���󎚂���) */
					if (RxPmType == RX_MEMORY) {	/**	��������M	*/
						if (((RxPageFinishStatus == RX_PAGE_END) || (RxPageFinishStatus == RX_ERROR))
							&& (SYS_RxMemoryFileItem == SYS_MEM_RX_FILE)	/* �ʏ�̎�M���e�̂� 1998/05/11  By T.Yamaguchi */
							&&	(CHK_PostMsgErrRxDocPrint() != 0)) {		/**	���ߎ�M�m�f�ł���M���e�v�����g���鎞	*/
							/**	��M�y�[�W��o�^ (���C���^�X�N�֒ʒm)	*/
							SendMsgFaxComToMain( MSG_RX_PRINT_PAGE );
						}
						else {
							if (SYS_FaxComIndexConflictStatus == 0) {
								MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );
							}
						}
					}
				}
				
				/****************************************************/
				
				/* RxModeChangeRequestedFlag = 1; */
				/* RxEOM_ReceiveFlag  = 1; */
			}
		}
		
		if ((FaxComPerformingFlag == 1) && ( SYS_FaxComStopSwitch() == 1 )) { /* �ʐM�� & StopSwitch���� */
			FaxPhaseE(5); /* �t�F�[�YE */
			ReceiveError(0x14);
		}
		/**********************************************************************/
		
		if ((FaxComPerformingFlag == 1) && (RxEOM_ReceiveFlag == 1)) {
			FCM_IsseiRxPhaseB1(FCM_ISSEI_RX_WAIT_NORMAL);
		}
	}
	
END:
	SYS_CurrentExecutingCommand = 0x00;		/* NULL */
	PollingTxFirstPageFlag = 0;
	
	TxReceiptRequestFlag = 0;
	
	FCM_IsseiFixRxDocStatus(); /* ��M���e�̃X�e�C�^�X���m�肳���� */
	
	if (bshirei == FALSE) {
		if (IsseiRxDCN_Received == TRUE) { /* DCN����M�����ꍇ */
			ring_time = SYB_MachineParameter[M_PARA_SW_I2]; /* ��Ė����� */
			if (ring_time > 0) {
				MonitorSpeakerOn(); /* ���j�^�[�X�s�[�JON */
				
				FCM_IsseiVoiceReq((UWORD)ring_time); /* ��b�\�񓮍� */
				
				if (!CHK_LineMonitor()) {
					MonitorSpeakerOff(); /* ���j�^�[�X�s�[�JOFF */
				}
			}
		}
	}
	
	IsseiRxDCN_Received = FALSE;
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߎ�M �t�F�[�YB1
	
	@li			
	@param		
	@return		FCM_ISSEI_RX_CONTINUE:		��Ď�M�p��
				FCM_ISSEI_RX_DETECT_CNG:	CNG���o(G3��M�ֈڍs)
				FCM_ISSEI_RX_START_TX:		�X�^�[�g�L�[����
	@note		�I���W�i����FaxRxPhaseB1()
	@date		2005/07/11 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE FCM_IsseiRxPhaseB1(
					UBYTE type) /* ���(FCM_ISSEI_RX_WAIT_NORMAL/FCM_ISSEI_RX_WAIT_CNG/FCM_ISSEI_RX_WAIT_OPR */
{
	UWORD	T1_timer;
	UWORD	T1_timer_max;
	UBYTE	command;
	UBYTE	rxmode_flag;
	UBYTE	afterfaxtransfer_flag;
	UBYTE mdm_ret;
	UBYTE result;
#if (PRO_MULTI_LINE == ENABLE)	/* 1997/01/21 Y.Murata */
	/* UBYTE		i; */
#endif
	
	T1_timer_max = 0;
	result = FCM_ISSEI_RX_CONTINUE;
	
	/*------------*/
	/*	Phase B1  */
	/*------------*/
	FaxComPhaseStatus			  = FAX_RX_PH_B1;
	FaxComTxPerformingFlag		  = 0;
	FaxComRxPerformingFlag		  = 0;
	rxmode_flag					  = 0;
	afterfaxtransfer_flag		  = 0;
	SYS_TensouJushinFlag		  = 0;	/* By HARADA 1994�N6��22�� */

	/*----------------*/
	/*	T1 Timer Set  */
	/*----------------*/
	if (ForwardReceiveFlag) { /* 94/10/6 by T.O */ /* �]����M���� */
		SYS_TensouJushinFlag = 1;
		ForwardReceiveFlag = 0;										/** �]����M�t���O�[���N���A */
		
		afterfaxtransfer_flag  = 1;
	}
	
	if (type == FCM_ISSEI_RX_WAIT_CNG) {
		T1_timer_max = (UWORD)(CHK_IsseiRxTimeout() * 100);
	}
	else if (type == FCM_ISSEI_RX_WAIT_NORMAL) {
		T1_timer_max = (UWORD)(FCM_ISSEI_RX_D_B_TIME / 10);
	}
	T1_timer = SYS_GeneralTimer;

	while( ( FaxComPerformingFlag == 1 )
		&& ( FaxComTxPerformingFlag == 0 )
		&& ( FaxComRxPerformingFlag == 0 )
		&& ( rxmode_flag == 0  )
		&& ( SYS_FaxComStopSwitch() == 0 )){	/** �ʐM�� & �^�C���A�b�v�Ȃ� & ���M���t���O�Ȃ�
													& ��M���t���O�Ȃ� & DCN���o�ݒ� & StopSwitch �Ȃ� */
		if (type != FCM_ISSEI_RX_WAIT_OPR) {
			if ((UWORD)(SYS_GeneralTimer - T1_timer) >= T1_timer_max) {
				break;
			}
		}

#if (PRO_LINENUMBER == TWICE_LINE)	/* �^���Q����d�l by T.Soneoka 1997/11/27 */
		if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2�����[�ݒ肪�W�����C���̏ꍇ	*/
			if (SYS_TensouJushinFlag
			&& (CHK_TEL1FaxTransferAvailable()|| CHK_TEL2FaxTransferAvailable())
			&& !(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_INTER_COM)
			&& (AttemptRxModeSwitch != SYS_ANS_FAX_READY) /* ADD BY M.H '94/10/15 */){
				OhPortStatusRead();	/*	OhPortBarrier();	'95,11,16 By N.S. */
				HookTensouOffHookCheck();
			}
		}
#else
		if (SYS_TensouJushinFlag
		&& (CHK_TEL1FaxTransferAvailable()|| CHK_TEL2FaxTransferAvailable())
		&& !(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_INTER_COM)
		&& (AttemptRxModeSwitch != SYS_ANS_FAX_READY) /* ADD BY M.H '94/10/15 */){
			OhPortStatusRead();	/*	OhPortBarrier();	'95,11,16 By N.S. */
			HookTensouOffHookCheck();
		}
#endif
		
		switch (type) {
		case FCM_ISSEI_RX_WAIT_CNG: /* CNG���҂� */
			mdm_ret = MDM_ReceiveResponseOrCNG(FCM_ReceiveResponseTime);
			break;
		case FCM_ISSEI_RX_WAIT_OPR: /* �X�^�[�g�L�[�����A�w�ߋN���M��OFF���҂� */
			 mdm_ret = MDM_ReceiveResponseOrIsseiOpr();
			 break;
		case FCM_ISSEI_RX_WAIT_NORMAL: /* FSK�̂ݑ҂� */
		default:
			mdm_ret = MDM_ReceiveResponse(FCM_ReceiveResponseTime);
			break;
		}
		
		if (mdm_ret == MDM_DETECT_CNG) { /* CNG��M */
			result = FCM_ISSEI_RX_DETECT_CNG;
			goto END;
		}
		if (mdm_ret == MDM_ISSEI_TX) { /* �X�^�[�g�L�[���� */
			result = FCM_ISSEI_RX_START_TX;
			goto END;
		}
		if (mdm_ret == MDM_SHIREI_OFF) { /* �w�ߋN���M��OFF */
			FCM_ShireiOff = TRUE;
			FaxComPerformingFlag = 0;
			goto END;
		}
		if (mdm_ret == FSK_RECEIVE) { /** ������M���� & Receiving */
			command = CheckHDLC_Command(); /* HDLC�R�}���h�`�F�b�N */
			switch(command){
			case  DCS_F		:									/** DCS��M */
				FaxRxDCS_SemiCompatibleCheck();	/** ���著�M�@�w��s�b�e��M�{�[���C�g�ݒ� */
				FinalRxMode			 = G3MODE;	/** �m���M���[�h�Z�b�g */
				FaxComRxPerformingFlag = 1;		/** ��M���t���O�Z�b�g */
				DIS_ReceivedFlag		  = 0;		/** DIS��M�t���O */
				rxmode_flag			 = 1;		/** DCN���o�t���O �����o�ݒ� */
				
				if (type == FCM_ISSEI_RX_WAIT_OPR) {
					SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_IDLE;
					SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_SHIREI_FAXCOM;
				}
				
				MsgFromFaxComToMain.Item	  = FROM_FAXCOM;
				MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
				SYS_FaxCommStage = FCM_RECEIVE;								/* 1994/05/30 Y.M */
				snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
				rcv_msg( mbxno.FCM_Task, &FcomMsg );		/* ���C����胁�b�Z�[�W��M */

				FCM_ReceiveResponseTime = TIME_OVER_3SEC;	/* 1995/12/19 */
				FSK_FirstReceivedFlag = 1;	/** ���肪�e�`�w�ł���Ɗm�肵�� */
				break;
			case DCN_F		:												/** DCN��M */
				rxmode_flag		   = 1;						/** DCN���o�t���O �����o�ݒ� */
				FaxComPerformingFlag = 0;						/** �ʐM���t���O �[���N���A */
				ReceiveError(0x12);
				
				IsseiRxDCN_Received = TRUE;
				
				break;
			default			:												/** �f�t�H���g */
				FaxComPerformingFlag = 0;						/** �ʐM���t���O �[���N���A */
				break;
			}
		}
	}
	
	if ((FaxComTxPerformingFlag == 0)
		&& (FaxComRxPerformingFlag == 0)
		&& (SYS_FaxComStopSwitch() == 0)
		&& (rxmode_flag == 0)){ /** ���M���t���O�Ȃ� & ��M���t���O�Ȃ� & StopSwitch�Ȃ� & DCN���o����ݒ� */
		/*----------------*/
		/*	T1 Time Over  */
		/*----------------*/
			if(afterfaxtransfer_flag == 0){ /* �]����M�Ȃ� */
				FaxPhaseE(1); /* �t�F�[�Y�d */
			}
			ReceiveError(0x11);
	}
	
	if(SYS_FaxComStopSwitch() == 1) { /* StopSwitch���� */
		/*---------------*/
		/*	STOP DCN Tx	 */
		/*---------------*/
		FaxPhaseE(5); /* �t�F�[�Y�d */
		ReceiveError(0x14);
	}
	
END:
	return result;
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߎ�M ��M���@�̊m��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����FaxRxNegotiate()
	@date		2005/07/11 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiRxNegotiate(void)
{
	FaxRxDCS_SemiCompatibleCheck(); /* ���著�M�@�w��s�b�e��M�{�[���C�g�ݒ�[DCS/CTC] */
	
	if(RxFirstTimeCompatibleCheckFlag == 1) {
		FCM_IsseiRxModeCheck(); /* �@�\�m�� */
		RxFirstTimeCompatibleCheckFlag = 0;
	}
	else {
		GetMultiFrameLine();
	}
	
	RxECM_Mode = ECM_OFF;
	TxECM_Mode = ECM_OFF;
	
	RxCompatibleCheck();
	ResultECM_ModeSet();
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߎ�M �@�\�̊m��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����RxOriginalModeCheck()
	@date		2005/09/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiRxModeCheck(void)
{
	Partner300dpiAbility = NO;
	PartnerEFineAbility = NO;

	/**	�t���[����荞��	*/
	GetMultiFrameLine();

	if((ID_FrmName != NO) && (StandardID[0] == NULL)) {	/**	TSI ��M	*/
		/**	ID ��荞��	*/
		GetPartnerID();
	}

	FaxComResult &= ~ECM_MODE_SET;

	/*	��s��M�̏���	*/
	if(SYS_RxMemoryFileItem == NULL) {
		/* �v�����^��M/��������M������ */
		switch (QueryReceiveType()) {
		case MEMORY_RX:
			SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
			break;
		case PRINTER_RX:
			break;
		case SUBSTITUTE_PRINTER_ERROR:
			FaxCompatibleErrorCode = SUBSTITUTE_PRINTER_ERROR;
			FaxComPerformingFlag = NO;
			return;
		case PRINTER_ERROR:
			FaxCompatibleErrorCode = PRINTER_ERROR;
			FaxComPerformingFlag = NO;
			return;
		default:
			break;
		}
	}
	
	if (SYS_RxMemoryFileItem == SYS_MEM_RX_FILE) { /* �ʏ�̃�������M */
		if(SetUpMemoryRx() == NO) {/**	�󂫂��Ȃ���΁A�G���[����	*/
			FaxCompatibleErrorCode = SUBSTITUTE_PRINTER_ERROR/*	��s��M�o�b�t�@�t���G���[	*/;
			FaxComPerformingFlag = NO;
			return;
		}
	}
	
	if(SYS_RxMemoryFileItem != NULL) { /* ��������M���s */
		/*SetMemoryRxDocFile();	*/
		SYS_DocBlock.Index.Item	 = SYS_RxMemoryFileItem;
		SYS_DocBlock.Index.No	 = SYS_RxMemoryFileNo;
		SYS_DocBlock.Index.Page	 = SYS_RxMemoryFilePage;
		SYS_DocBlock.Index.BoxNumber = SYS_RxMemoryFileBoxNumber; /* 1997/01/13  By T.Yamaguchi */
	}
#if (PRO_PRINTER_RX == ENABLE)/* 13.Apr'94 */
	else{/**	�v�����^��M	*/
		PRN_PreOpen();				/**	�v�����^�v���I�[�v��	*/
		PrinterRxPreOpenFlag = 1;
	}
#endif
	
	/**	�ʐM�̊J�n�� MAN_TSK �ɒm�点��	*/
	MsgFromFaxComToMain.Item = FROM_FAXCOM;
	MsgFromFaxComToMain.Message = MSG_FAXCOM_RX_START;
	snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
	rcv_msg(mbxno.FCM_Task, &FcomMsg);		/* ���C����胁�b�Z�[�W��M */
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߎ�M �t�F�[�YC
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����FaxRxPhaseC()
	@date		2005/07/11 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiRxPhaseC(void)
{
	FaxComPhaseStatus = FAX_RX_PH_C_BEFORE_PIX;

	FCM_SetIsseiRxPageData(); /* ��M�y�[�W�f�[�^�Z�b�g */

	/**	�ϐ�������	*/
	RxPageFinishStatus = RX_PAGE_END;
	RxWholePageCompletedFlag = 0;
	RxEOR_ReceiveFlag = 0;
	PRI_Q_RxFlag = 0;
	PRI_Q_RxCount = 0;
	DEU_Return_Flag = 0; /* 1997/06/02  By T.Yamaguchi DEU�����폜 */
	PIP_TX_Flag = 0;	/* 1997/06/02  By T.Yamaguchi DEU�����폜 */ /* 97/04/26 by M.H. */

	if (FaxComPerformingFlag != 1) {
		return;
	}
	/* (RxWholePageCompletedFlag == 0) */
	
	RxECM_PixTimeoutFlag = 0;	/**	�d�b�l�^�C���A�E�g����t���O���N���A	*/	/* Oct.13.1994 */
	
	FCM_StartIsseiRxPix(); /* ������f�[�^��M�҂� */
	
	if (FaxComPerformingFlag != 1) { /* ������f�[�^��M�m�f */
		/* �����y�[�W��M�r���ł̍��ᑬ���ʂŁA��M���r�₦����(PPS_NULL��M��)�A���r���[�ȃC���f�b�N�X���c���Ă��܂��B
		 * �����ŁA���r���[�Ȃ̂�����΁A���̃y�[�W���폜���܂��B*/
		if (RxPmType == RX_MEMORY) {	/**	��������M	*/
			/**	�������t�@�C���N���[�Y���C��M�y�[�W�폜	*/
			if (SYS_FaxComIndexConflictStatus == 0) {
				MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );
			}
		}
		return;
	}
	
	/** �s�R�O���j�^�p�f�[�^�Z�b�g	*/
	SaveT30TimingData( SYS_T30_START_TIME );
	SaveT30Data( SYS_T30_RX_PIX, &MDM_ModemBuffer[0][0], 0 );

	/**	�\���ؑ֎w��(��f�[�^��M��)	*/
	SYS_FaxCommStage = FCM_RECEIVE_SET;		/*	May.30.1994	*/
	SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );

	/*------------------*/
	/**	��f�[�^��M	*/
	/*------------------*/
	FaxComPhaseStatus = FAX_RX_PH_C_PIX;
#if (PRO_COM_CODEC_TYPE == SOFTWARE)
	RxPageFinishStatus = SCDC_RxPix(ECM_OFF, RxPmType );
#else
	RxPageFinishStatus = MDM_RxPix(ECM_OFF, RxPmType );
#endif
	MDM_RxPixClose(ECM_OFF);
	FaxComPhaseStatus = FAX_RX_PH_C_AFTER_PIX;
	
	/*--------------------------------------------------*/
	/**	��f�[�^��M���ʂ��m�F (�G���[�R�[�h���Z�b�g)	*/
	/*--------------------------------------------------*/
	if (RxPageFinishStatus == RX_TMOUT) { /* ��M�t���[���^�C���A�E�g */
		ReceiveError( 0x52 ); /* �q�D�T�D�Q */
	}
	else {
		CheckRxPixResultSub(); /* ��f�[�^��M���ʂ��m�F */
	}
#if 0
//	if (FaxComPerformingFlag == 1) {	/**	�ʐM�� (��f�[�^��M���ʂn�j)	*/
//		FCM_IsseiRxPostMessage(); /* ���ߎ�M */
//	}
//	if (FaxComPerformingFlag == 1) { /* ��f�[�^��M�C�|�X�g���b�Z�[�W��M�n�j */
//		FCM_IsseiRxPhaseD(); /* ��M�t�F�[�Y�c */
//	}
//	else {		/**	��f�[�^��M�m�f�^�|�X�g���b�Z�[�W��M�m�f	*/
//		/* ��������M�y�[�W���폜(�A���ݒ�ɂ���M���e���󎚂���) */
//		if (RxPmType == RX_MEMORY) {	/**	��������M	*/
//			if (((RxPageFinishStatus == RX_PAGE_END) || (RxPageFinishStatus == RX_ERROR))
//				&& (SYS_RxMemoryFileItem == SYS_MEM_RX_FILE)	/* �ʏ�̎�M���e�̂� 1998/05/11  By T.Yamaguchi */
//				&&	(CHK_PostMsgErrRxDocPrint() != 0)) {		/**	���ߎ�M�m�f�ł���M���e�v�����g���鎞	*/
//				/**	��M�y�[�W��o�^ (���C���^�X�N�֒ʒm)	*/
//				SendMsgFaxComToMain( MSG_RX_PRINT_PAGE );
//			}
//			else {
//				if (SYS_FaxComIndexConflictStatus == 0) {
//					MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );
//				}
//			}
//		}
//	}
#endif
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߎ�M ��M�y�[�W�f�[�^�Z�b�g
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����SetRxPageData()
	@date		2005/07/11 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_SetIsseiRxPageData(void)
{
	RxPmType = RX_MEMORY; /* ��������M���w�� */
	
	/* ���e����u���b�N�ɍŏ��P���C���o�C�g�����Z�b�g */
	SYS_DocBlock.MinimumLineSize = CheckMinimumLineSize( RxMinimumScanningTime, RxBaudRate );

	SYS_DocBlock.DocLength = SYS_NO_LIMIT_PAGE_LENGTH; /* ���e����u���b�N�ɍő��M���e��(������)���Z�b�g */

	/*�@���e����u���b�N�Ƀt�@�C���C���f�b�N�X���Z�b�g���� */
	SYS_DocBlock.Index.No	= SYS_RxMemoryFileNo;				/*	��M�������t�@�C���ԍ�		*/
	SYS_DocBlock.Index.Page = SYS_RxMemoryFilePage;				/*	��M�������y�[�W			*/
	SYS_DocBlock.Index.Item = SYS_RxMemoryFileItem;				/*	��M�������t�@�C���A�C�e��	*/
	SYS_DocBlock.Index.BoxNumber = SYS_RxMemoryFileBoxNumber;	/*	��M�������t�@�C���A�C�e��	*/
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߎ�M ������f�[�^��M�҂�
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����StartRxPix()
	@date		2005/07/11 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_StartIsseiRxPix(void)
{
	UBYTE fcf;
	
	if (FaxComPerformingFlag != 1) {
		return;
	}
	
	if (SYS_FaxComStopSwitch()) { /* �X�g�b�v�L�[���͂���̎� */
		FaxComPerformingFlag = 0;
		return;
	}
	
	switch (MDM_FskHighSpeedCheck(RxBaudRate, ECM_OFF)) { /* ���ᑬ���� */
	case TRN_RECEIVE: /* �����M����M */
		break;
	case FSK_RECEIVE: /* �e�r�j��M */
		fcf = CheckReceivedFCF();
		
		FaxPhaseE(4); /* �ʐM�I��(DCN�Ȃ�) */
		ReceiveError(0x31); /* R.3.1 */
		break;
	default: /* �^�C���A�E�g */
		FaxPhaseE(4); /* �ʐM�I��(DCN�Ȃ�) */
		ReceiveError(0x31); /* R.3.1 */
		break;
	}
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߎ�M �|�X�g���b�Z�[�W��M
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����RxECM_PixData()
	@date		2005/07/11 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiRxPostMessage(void)
{
	UBYTE rx_fcf;
	UBYTE ret;

	if (FaxComPerformingFlag != 1) { /* �ʐM���łȂ��ꍇ */
		return;
	}
	if (SYS_FaxComStopSwitch()) { /* �X�g�b�v�L�[���͂���̏ꍇ */
		FaxComPerformingFlag = 0;
		return;
	}
	
	ret = MDM_ReceiveCommand((UWORD)TIME_OVER_6SEC); /* �R�}���h��M */
	
	if (ret != FSK_RECEIVE) { /* �R�}���h����M���Ȃ������ꍇ */
		FaxPhaseE(4); /* �ʐM�I��(DCN�Ȃ�) */
		ReceiveError(0x42); /* R.4.2 */
		return;
	}
	
	rx_fcf = CheckReceivedFCF();	/**	��M���߂e�b�e�m�F	*/
	AnalyzeRxPostMessageFrame();	/* �o�q�h�|�p��M�����J�E���g���邽��  Oct.31.1994 */
	
	if (rx_fcf == DCN_F) { /* DCN��M */
		FaxPhaseE(4); /* �ʐM�I��(DCN�Ȃ�) */
		ReceiveError(0x31); /* R.3.1 */
		
		IsseiRxDCN_Received = TRUE;
	}
	
#if 0
// #if (PRO_PAPER_TYPE == ROLL_PAPER)
// 	if (RxPmType == RX_PRINTER) {
// 		if (WaitRxPaperCut( 25 ) == 0) {	/**	�L�^���J�b�g�����Q�D�T�b�o��	*/
// 			
// 		}
// 		CheckRxPrinterError();				/**	�v�����^�G���[�̎�ނ��m�F	*/
// 	}
// #endif
#endif
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߎ�M�t�F�[�YD
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����FaxRxPhaseD()
	@date		2005/07/11 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiRxPhaseD(void)
{
	UBYTE tmp_rx_fcf;

	FaxComPhaseStatus = FAX_RX_PH_D;

	/**	�\���ؑ֎w��(�|�X�g���b�Z�[�W��M)	*/
	SYS_FaxCommStage = FCM_ERROR_LINE;		/*	"�G���[���C���^��M���C��"�\���p	Jul.14.1994	*/
	SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );

	/**	PRI-Q�r�b�g���}�X�N���ăe���|�����ɃZ�b�g	*/
	tmp_rx_fcf = RxFCF & (UBYTE)~PRI_Q_F;

	/* ���Ɏ�M���Ă���R�}���h���`�F�b�N */
	if ((tmp_rx_fcf == MPS_F) || (tmp_rx_fcf == EOM_F) || (tmp_rx_fcf == EOP_F)) { /* MPS/EOM/EOP��M */
		if (tmp_rx_fcf == EOM_F) { /* �d�n�l */
			RxModeChangeRequestedFlag = 1;
			RxEOM_ReceiveFlag = 1;
		}
		else if (tmp_rx_fcf == EOP_F) {	/**	�d�n�o	*/
			RxModeChangeRequestedFlag = 1;
			RxEOP_ReceiveFlag = 1;
		}
		
		RxWholePageCompletedFlag = 1; /* �����y�[�W��M���� */
		
		if ((RxPageFinishStatus == RX_PAGE_END)
			||	(RxPageFinishStatus == RX_ERROR)
			||	(RxPageFinishStatus == RX_PRT_ERR)) {	/**	�y�[�W�G���h,�掿�G���[,�v�����^�G���[	*/
			/**	��M�y�[�W���C�������t�@�C���y�[�W�����{�P	*/
			SYS_RxTotalPage++;
			SYS_RxMemoryFilePage++;
			SYS_RxPrintFilePage++;
			if ((SYS_RxMemoryFileItem == SYS_MEM_RX_FILE)
				|| (SYS_RxPrintFileItem == SYS_MEM_RX_FILE)) { /** �W����������M||�������f���A���I�[�v�����e||�o�b�t�@�����O��M */
				SendMsgFaxComToMain( MSG_RX_PRINT_PAGE ); /* ��������M�P�y�[�W�I�������C���^�X�N�֒ʒm */
			}
		}
		else {
			/**	��������M�ňُ�y�[�W�̏ꍇ�́C��M�y�[�W���폜	*/
			if (RxPmType == RX_MEMORY) {
				if (SYS_FaxComIndexConflictStatus == 0) {
					MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );	/* Jul.04.1994 */
				}
			}
			CheckRxPixResultSub(); /* �G���[�R�[�h���Z�b�g */
		}
	}
	else { /* ���̃R�}���h����M�����ꍇ */
		ReceiveError( 0x42 );	/**	�q�D�S�D�Q	*/
		if (RxFCF == DCN_F) {	/**	�c�b�m����M	*/
			
			FaxPhaseE( 4 );		/**	�ʐM�I���i�c�b�m�Ȃ��j	*/
			
			IsseiRxDCN_Received = TRUE;
		}
		else {
			/* FaxPhaseE( 1 ); */		/**	�ʐM�I���i�c�b�m����j	*/
			FaxPhaseE( 4 );		/**	�ʐM�I���i�c�b�m�Ȃ��j	*/
		}
	}
	
	if (tmp_rx_fcf == EOP_F) { /* EOP����M�����ꍇ */
		FCM_IsseiRxReceiveDCN(); /* DCN��M */
	}
}

/**************************************************************************************************/
/**
	@brief		DCN��M
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����ReceiveDCS()
	@date		2005/07/23 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiRxReceiveDCN(void)
{
	if (FaxComPerformingFlag != 1) { /* �ʐM���łȂ��ꍇ */
		return;
	}
	
	if (MDM_ReceiveCommand((UWORD)TIME_OVER_6SEC) == FSK_RECEIVE) { /* ���ߎ�M�n�j */
		/* ��M�|�X�g���b�Z�[�W����� */
		ReceiveResponseFlag = 1;
		AnalyzeRxPostMessageFrame();
		
		if (RxFCF == DCN_F) {		/**	�c�b�m����M	*/
			FaxComPerformingFlag = 0;	/**	�ʐM���t���O���N���A	*/
			
			IsseiRxDCN_Received = TRUE;
		}
		else {							/**	���̑��̃t���[������M	*/
			FaxPhaseE( 1 );				/**	�ʐM�I���i�c�b�m����jadd 96/06/25 S.Takeuchi	*/
			ReceiveError( 0x11 );			/**	�q�D�P�D�P	*/
		}
	}
	else {		/**	�s�Q�^�C���A�E�g	*/
		ReceiveResponseFlag = 0;
		FaxPhaseE( 4 );				/**	�ʐM�I���i�c�b�m�Ȃ��j	*/
		ReceiveError( 0x11 );		/**	�q�D�P�D�P	*/
	}
}

/**************************************************************************************************/
/**
	@brief		��M���e�̃X�e�C�^�X���m�肳����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�[���x�������Ƀv�����g�r�o�����邽��
	@date		2005/09/16 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiFixRxDocStatus(void)
{
	UWORD memory_rx_num;
	
	/* add 1997/03/07  By T.Yamaguchi */
	for (memory_rx_num = 0; memory_rx_num < SYS_MEMORY_RX_MAX; memory_rx_num++) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
		if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
		 || (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)) {
#else
		if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
		 || (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)
		 || (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE_PRINT)) {
#endif

#if (PRO_LINENUMBER == TWICE_LINE)
			/* �p�`�s�s�
			** �g������Ŏ�M���ł��Ȃ��s��C��
			** �g������̏����������Ă����i "& 0x7f")
			** by O.Kimoto 1998/04/13
			*/
			if ((SYB_MemoryRxPrint[memory_rx_num].StackNumber & 0x7f) == (UBYTE)0) {
				break;
			}
#else
			if (SYB_MemoryRxPrint[memory_rx_num].StackNumber == (UBYTE)0) {
				break;
			}
#endif
			}
	}
	/* ��M���e�|�[�����O���o���C�����ɂĒǉ����܂� by T.Soneoka 1997/02/21
	** �|�[�����O���o�����[�h�i�@��ŗL�r���j�ő�s��M���t�ŃA�N�Z�X���ꂽ�ꍇ�A�v�����g���C�g�ʒu���X�V���Ȃ�
	*/
	if (memory_rx_num < SYS_MEMORY_RX_MAX) {
		MemoryRxPrintPoint = &SYB_MemoryRxPrint[memory_rx_num];
		if (MemoryRxPrintPoint->StorePage > 0) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_PRINT; /* By H.Y 1994/11/17 */
#else
			if (MemoryRxPrintPoint->Status == SYS_MEMORY_RX_STORE_PRINT) {
				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_FAST_PRINT;
			}
			else {
				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_PRINT;
				if (CHK_UNI_RxDocReversePrint()) {
					MemoryRxPrintPoint->PrintPage = MemoryRxPrintPoint->StorePage;
					MemoryRxPrintPoint->RotatePage = MemoryRxPrintPoint->StorePage;
				}
			}
#endif
			/* 1997/02/10 Y.Murata
			 * �v�����^�����A��M���Ă��錴�e���v�����g���Ă���ꍇ�̂݃C�x���g�𔭍s���܂�
			*/
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
				if ((SYS_DocumentPrintItem == SYS_MEM_RX_FILE)
				&& (SYS_DocumentPrintNo == memory_rx_num)) {
					CMN_DisableInterrupt();	/**	���荞�݋֎~	*/
					PRN_1PageReceived = 1;
					det_evt(EVT_PRN_RESTART);
					CMN_EnableInterrupt();	/**	���荞�݋���	*/
				}
			}
		}
		else  {
			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
			MemoryRxPrintPoint->StorePage = 0;
			MemoryRxPrintPoint->RotatePage = 1;
			MemoryRxPrintPoint->PrintPage = 1;
			MemoryRxPrintPoint->ErasePage = 1;
			MemoryRxPrintPoint->Protect	  = SYS_PROTECT_OFF; /**��M���e�v�����g�v���e�N�g������ */
			/* 3Line add 1997/03/07  By T.Yamaguchi */
			MemoryRxPrintPoint->StackNumber = 0;
			MemoryRxPrintPoint->ReceiveTime = 0;
			MemoryRxPrintPoint->JournalPoint = 0;
		}
	}
}

#endif /* KEISATSU */

