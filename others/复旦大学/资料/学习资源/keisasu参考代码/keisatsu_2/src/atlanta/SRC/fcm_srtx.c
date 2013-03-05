/**********************************************************************************************************************
	@(#)$Id: fcm_srtx.c,v 1.17 2005/12/21 18:19:27 xiax Exp $
	Create        : 2005/07/04
	Author        : �΋����a
	Description   : ��Ďw�ߑ��M
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#if !defined (KEISATSU)
	UBYTE NoIsseiTx; 
#else
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\ncu_def.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\hinoki\define\hino_tib.h"
#include "\src\atlanta\hinoki\define\mpr_pro.h"
#include "\src\atlanta\hinoki\define\m_param.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"

 /* �x�@FAX DVT_ID62 Added by SMuratec �� 2005/12/08 */
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\ext_v\ncu_data.h"
#include "\src\atlanta\define\ncu_stat.h"
#include "\src\atlanta\define\sys_line.h"

/**************************************************************************************************/
/**
	@brief		��Ďw�ߑ��M
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����ManualTransmit()
	@date		2005/07/10 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiTx(
			BOOL bshirei) /* �w�ߋN���M���̗L�� */
{
	FCM_ISSEI_TX = TRUE;	/* �x�@FAX DVT_ID17 ��ă��[�h���M�� by SMuratec �� 2005/11/05 */
	
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
	
	SYS_FaxComType = SYS_MANUAL_TX;
	SYS_FaxComTxType = SYS_SCANNER_TRANSMIT; /* ���M�^�C�v */
	
	/* ���M���e���擾 */
	TxMemoryFilePage = 1;
	SYS_DocBlock.Src.Mode = (BYTE)SYB_ModeSw;
	SYS_DocBlock.Dst.Mode = SYS_DocBlock.Src.Mode;	/* �ǉ� O.Oshima 2005/10/20 */
	SYS_DocBlock.Src.Size = (BYTE)CMN_GetDocumentScanSize();
	FirstTxMode = (UBYTE)SYS_DocBlock.Src.Mode;
	TxMode = (UBYTE)SYS_DocBlock.Src.Mode;
	DocWidth = (UBYTE)SYS_DocBlock.Src.Size;
	
	CMN_EvacuateStampSetting(); /* �σX�^���v������ */
	
	SCN_MotorStopRequest = 1; /* ���e�ǂݎ��I�����Ƀ��[�^�[��~ */
	
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
	NoNextDocument = FALSE;
#endif
	
	if (bshirei == TRUE) {
		SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_IDLE;
		SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_SHIREI_FAXCOM;
	}
	
	SYS_FaxCommStage = FCM_TRANSMIT;
	MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
	snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain); /* LCD�X�V */
	rcv_msg(mbxno.FCM_Task, &FcomMsg);
	
	AvailableTxBaudRate = CHK_IsseiSpeed(); /* ���M�\�{�[���C�g */
	AttemptTxBaudRate = AvailableTxBaudRate; /* ���s���M�{�[���C�g */
	TxBaudRate = AvailableTxBaudRate;
	
	AvailableTxCodingMethod = CHK_IsseiCodingMethod(); /* ���������� */
	TxCodingMethod = AvailableTxCodingMethod;
	
	SYS_DocBlock.Src.Code = TxCodingMethod;
	SYS_DocBlock.Dst.Code = TxCodingMethod;
	
	AvailableTxMinimumScanningTime = CHK_IsseiMinimumScanningTime(); /* �ŏ��`������ */
	
	TxECM_Mode == ECM_OFF;
	
	V8ProcedureRequestFlag = 0; /* V8�菇�ڍs�v���N���A */
	
#if defined(POPLAR_F)	/* 1999/11/29 */
	SYS_BackUpConfirmationReport = SYB_ConfirmationReportSwitch;
#endif
	
	FaxComPerformingFlag = 1;
	
	/* ���C���œǂݎ�葕�u(ADF/FBS)�����肵�āA�~���[�L�����b�W���ړ� */
	MsgFromFaxComToMain.Message = MSG_FAXCOM_SCANNER_DECIDE;
	snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
	rcv_msg(mbxno.FCM_Task, &FcomMsg);
	
	
	
	FaxcomRelayControl(); /* �����[�Z�b�g */
#if defined(POPLAR_F)
	MDM_SetOriginateMode(); /* ���f�����[�h�Z�b�g */
#endif
	FaxComStartTime = SYB_CurrentTime; /* ��M�J�n���� */
	SYS_FCM_StartTime = SYS_1SecGeneralTimer;

	/*-----------------------*/
	/** �W���[�i���ʔԃZ�[�u */
	/*-----------------------*//* 1994/09/30 */
	JournalTxTotalCount				= SYB_TxTotalCount;			/* �ʐM�J�n���ԂƏI�����Ԃœ��t���ς�����ꍇ�́A */
	JournalRxTotalCount				= SYB_RxTotalCount;			/* �ʐM�J�n���̓��t�ɍ��킹�邽�߂ɃZ�[�u���Ă��� */
#if (PRO_LINENUMBER == TWICE_LINE)	/* �^���Q����d�l by T.Soneoka 1998/03/11 */
	JournalTxTotalCountExt			= SYB_TxTotalCountExt;
	JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_JournalWorkFile.Number = JournalTxTotalCount;
	PAT_JournalWorkFile.StartTime = FaxComStartTime;
	if (SYS_FaxComType == SYS_MANUAL_TX) {
		PAT_JournalWorkFile.Kind = SYS_MANUAL_TRANSMIT;
	}
	else if (SYS_FaxComType == SYS_REMOTE_FAX_TX) {
		PAT_JournalWorkFile.Kind = SYS_REMOTE_TX;
	}

	PAT_JournalDataToImage(NUMBER);
	PAT_JournalDataToImage(START);
	PAT_JournalDataToImage(NOTE);
#endif

	FaxComTXorRX_Sign = TX_COM_MODE;			/** ���M�R�}���h�Z�b�g */
	
	/* �x�@FAX DVT_ID81 Added By SMuratec �� 2005/12/21 */
	IsSHIREIKido = FALSE;
	
	if(CHK_MessageTxON() != 0) {				/** ���b�Z�[�W���M�v�� */
		TxCoverPageFlag = 1;					/** �J�o�[�y�[�W�t���O �Z�b�g */
	}
	else {
		TxCoverPageFlag = 0;					/** �J�o�[�y�[�W�t���O �N���A */
	}

	TxReceiptRequestFlag = 0;					/** ��̏ؑ��M�t���O �N���A */


	SYS_BackUpConfirmationReport = SYB_ConfirmationReportSwitch;

	SYS_CurrentExecutingCommand = 0x00;		/* NULL */
	PollingTxFirstPageFlag = 0;
	
	FCM_IsseiTxBody(bshirei);
	/*************************/
	
	if (bshirei == TRUE) {
		SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_FAXCOM;
		if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
			SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_SHIREI_IDLE;
		}
		else {
			SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_IDLE;
		}
	}
	FCM_ISSEI_TX = FALSE;	/* �x�@FAX DVT_ID17 ��ă��[�h���M�� by SMuratec �� 2005/11/05 */
	
	CheckAllErrorPage(); /* T.4.2�G���[���o�����ǂ����`�F�b�N */
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߑ��M�{��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����FaxTransmit()
	@date		2005/07/10 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiTxBody(
				BOOL bshirei) /* �w�ߋN���M���̗L�� */
{
	UBYTE ring_time; /* ��Ė����� */
	UWORD total_page;
	
	SYS_TxTotalPage		= 0;							/** ���M�y�[�W���[���N���A */
	FaxComTxPerformingFlag = 1;						/** ���M���t���O�Z�b�g */
	
	/* FaxComPhaseStatus = FAX_TX_PH_B1; */
	TxSpeedHandshakeFlag = 0;			/** �Z�k�n���h�V�F�C�N���M�t���O�N���A �N���A����ꏊ���������邱�� By T.Y */
	FSK_FirstReceivedFlag = 1;	/** ���肪�e�`�w�ł���Ɗm�肵�� */
	/* FaxComUntilRecDISLineOFF(); */	/** �c�h�r��M�ŉ�����j�^���n�e�e���� */
	/* DIS_ReceivedFlag = 1; */	/*????*/						/** DIS��M�t���O�Z�b�g */
	FinalTxMode		= G3MODE;		/** �m�著�M���[�h */
	
	total_page = 0;
	
	while ((FaxComPerformingFlag == 1) && (FaxComTxPerformingFlag ==1) && (SYS_FaxComStopSwitch() == 0)) {
		/* �ʐM�� & ���M�� & StopSwitch �Ȃ� */
		DIS_ReceivedFlag = 0;	/*????*/	/** DIS��M�t���O �[���N���A */
		
		if (total_page == 0){ /* ��f�[�^�����M�̏ꍇ */
			MonitorSpeakerOn(); /* ���j�^�[�X�s�[�JON */
			
			FaxTimer(FCM_ISSEI_TX_A_B_TIME);
			
			if (!CHK_LineMonitor()) {
				MonitorSpeakerOff(); /* ���j�^�[�X�s�[�JOFF */
			}
			
			FCM_S1_Preamble3S = TRUE; /* �ŏ���DCS�̃v���A���u����3�b�ɂ��� */
		}
		else { /* 1�y�[�W���M�ȍ~�̏ꍇ */
			FaxTimer(FCM_ISSEI_TX_D_B_TIME);
		}
		
		if ((FaxComPerformingFlag != 1) || (SYS_FaxComStopSwitch() != 0)) {
			FCM_S1_Preamble3S = FALSE; /* �v���A���u���̒��������ɖ߂� */
			break;
		}
		
		TxInterMemoryFlag = NO;
		
		FaxComPhaseStatus = FAX_TX_PH_B2; /*	Phase B2  */
		
		SYS_DocBlock.Src.Mode = (BYTE)SYB_ModeSw;		/* �ǉ� O.Oshima 2005/10/20 */
		SYS_DocBlock.Dst.Mode = SYS_DocBlock.Src.Mode;	/* �ǉ� O.Oshima 2005/10/20 */
		TxMode = SYS_DocBlock.Src.Mode;
		DocWidth = SYS_DocBlock.Src.Size;
		
		FaxTxMaxLength = SYS_NO_LIMIT; /* �Ƃ肠���� */
		TxMethodFlag = 1;							/** ���M�����m��t���O�Z�b�g */
		TxWidth = DocWidth;
		SYS_DocBlock.Dst.Size = (BYTE)TxWidth;
		TxMinimumScanningTime = FCM_GetIsseiMinScanningTime(AvailableTxMinimumScanningTime, TxMode);
		PartnerV8Capable = 0;
		BaudrateFlag = 1;								/** �{�[���C�g�m��t���O�Z�b�g */
		
		FCM_SendIsseiDCS(); /* DCS���M */
		FCM_S1_Preamble3S = FALSE; /* �v���A���u���̒��������ɖ߂� */
		
		TxRetrainingFlag = 0;					/** ���g���[�j���O�Ȃ��t���O�Z�b�g */
		if((FaxComPerformingFlag == 1) && (SYS_FaxComStopSwitch() == 0)){ /** �ʐM�� & StopSwitch�Ȃ� */
			MsgFromFaxComToMain.Item = FROM_FAXCOM;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
		}
		else{
			break;
		}
		
		FaxTimer(FCM_ISSEI_TX_B_C_TIME);
		
		FCM_IsseiTxPhaseC(); /* �t�F�[�Y�b */
		
		FaxTimer(FCM_ISSEI_TX_C_D_TIME);
		
		FCM_IsseiTxPhaseD(); /* �t�F�[�Y�c */
		
		/* ���e�r�o�{�����e�J�荞�ݏ��� */
#if (PRO_SCN_CLUTCH == ENABLE) /* �X�L���i�N���b�`�L��̏ꍇ by H.Hirao 1998/11/19 */
		/* �X�L���i���N���[�Y���鎞��tskno_SCN_STxStoreTask�������Ƃ�����(HINOKI�����̏���) */
		if (TxSmType == TX_SCAN) {	/**	�X�L���i���M	*/
 #if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
			if (!FaxComPerformingFlag
				|| ((TxPageFinishStatus != TX_PAGE_END) && (TxPageFinishStatus != TX_PAGE_END_MODE_CHANGE))) {
				if (tskno_SCN_STxStoreTask != 0xffff) {
					del_tsk(&tskno_SCN_STxStoreTask);
				}
				SCN_Close((UBYTE)FROM_FAXCOM);
			}
 #else
			SCN_Close((UBYTE)0);
 #endif
		}
#endif
		total_page++;
	}
	
	if(( 1 == FaxComPerformingFlag ) && ( 1 == SYS_FaxComStopSwitch() )) { /* �ʐM�� & StopSwitch ���� */
		/*---------------*/
		/*	STOP DCN Tx	 */
		/*---------------*/
		FaxPhaseE(5);								/** �t�F�[�Y�d */
		TransmitError( 0x14,1 );
	}
	
#if (PRO_PANEL == KANJI)
	/* �h�b�g�n�t����̃t�B�[�h�o�b�N By O.Kimoto 1998/03/30 */
	/* ���M�I����ɑ��M�y�[�W+1�̃y�[�W�����\������邽��  1997/10/10 s.takeuchi */
	SYS_FaxCommStage = FCM_TRANSMIT;
	SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );
#endif
	
	FCM_IsseiTxCloseScanner(); /* �X�L���i�N���[�Y */
	
	if (bshirei == FALSE) {
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

/**************************************************************************************************/
/**
	@brief		��Ďw�ߑ��M�ɂ����ăX�L���i���N���[�Y����
	
	@li			
	@param		
	@return		�ŏ��`������
	@note		
	@date		2005/07/10 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiTxCloseScanner(void)
{
#if (PRO_SCN_CLUTCH == ENABLE) /* �X�L���i�N���b�`�L��̏ꍇ */
	return;
#endif
	
	/*----------------------------------------------------------------------------------*/
	/*	�˂̃X�L���i���M�ōŏI���e��r�o���邽�߂ɁC���M�̍Ō�ŃX�L���i�N���[�Y����	*/
	/*	�A���C�ʐM�G���[���������ꍇ�̓N���[�Y���Ȃ�	Oct.18.1994						*/
	/*----------------------------------------------------------------------------------*/
	/* FBS �����ǉ� 1997/05/22 By T.Yamaguchi */
#if (PRO_FBS == ENABLE)
	if (SYS_ScannerExecMode != SCN_ADF) {
		return;
	}
#endif
	
	if ((TxPageFinishStatus == TX_DOC_ERR) || (TxPageFinishStatus == TX_STOPPED) || (TxPageFinishStatus == TX_1M_OVER)) {
		/**	�X�L���i�I�[�v����	*/
		return;
	}
	
	if (((FaxComResult & 0x00ff) == NO_ERROR) || ((FaxComResult & 0x00ff) == 0x0014) || ((FaxComResult & 0x00ff) == 0x0041)) {
		/* �ʐM�G���[�Ȃ�or�ŏI���e��T.4.1 */
		if (!DS1()) {	/** ADF��Ɏc�茴�e�Ȃ� */
			/* ����I����ADF�Ɏc�茴�e���Ȃ�(DS1 OFF)�ꍇ�̂ݔr�o����(�Z�b�g�������w�薇���̎��Ɏc���ADF��Ɏc������) */
			/* �X�L���i�N���[�Y (�ŏI���e��r�o) */
#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 1998/11/17 by T.Soneoka */
			if (tskno_SCN_STxStoreTask != 0xffff) {
				del_tsk(&tskno_SCN_STxStoreTask);
			}
#endif
			if (SCN_Close(SCN_DOC_EXITING) != SCN_DOC_EXIT_OK) { /* ���ʂm�f */
				/* ���e�r�o�m�f�����C���^�X�N�֒ʒm */
				MsgFromFaxComToMain.Item	= FROM_FAXCOM;
				MsgFromFaxComToMain.Message = MSG_FAXCOM_CLOSE_ERROR;
				snd_msg( mbxno.MAN_Task, &MsgFromFaxComToMain );
				rcv_msg( mbxno.FCM_Task, &FcomMsg );
			}
		}
		else {
			LampOff(); /* �u���b�N�G���h�iPPS-NULL)����T.4.1�G���[�ɂȂ����ꍇ�A�����v�������Ȃ��s��C�� 1998/05/25 by T.Soneoka */
		}

#if (PRO_SCN_CODEC_TYPE != SOFTWARE)	/* 1998/11/17 by T.Soneoka */
		/* �X�L���i�[���M ���[�e���o�� �e�X�g T.Nose 1998/03/25 */
		if (SYB_MaintenanceSwitch[MNT_SW_C9] & CHECK_SHADING_RAM) { /* ���ǂ݃f�o�b�O�p */
			UBYTE i; /* added by H.Kubo 1998/03/25 */
			DIPP_SetBitDIPPST(IDP_BIT_OFF);	/* Shading RAM��ǂނ��� */
			DIPP_ReadShadingRAM( &SCN_DebugShadingRAM[0] );	/* 1997/04/25 */
			for (i=0; i<SYS_SHADING_MAX; i++) {
				if (SYB_ShadingRAM[i] != SCN_DebugShadingRAM[i]) {
					/* �������mnt sw�ɃZ�b�g */
					SYB_MaintenanceSwitch[MNT_SW_C9] |= SHADING_RAM_ERROR1;
					break;
				}
			}
			/* �����lRAM���R���y�A����  1997/04/25 */
			DIPP_ReadInitialRAM( &SCN_DebugInitialRAM1[0] );
			for (i=0; i<SYS_INITIAL_MAX; i++) {
				if ((SYB_InitialRAM[i] != SCN_DebugInitialRAM0[i])
				||	(SYB_InitialRAM[i] != SCN_DebugInitialRAM1[i])) {
					/* �����lRAM���������mntB6-0�ɃZ�b�g */
					SYB_MaintenanceSwitch[MNT_SW_C9] |= SHADING_RAM_ERROR0;
					break;
				}
			}
			DIPP_SetBitDIPPST(IDP_BIT_ON);	/* Shading RAM��ǂނ��� */
		}
#endif
	}
	else if ((FaxComResult & 0x00ff) == 0x0012) { /** ���M�������w�薇�� */
		/* �����w��G���[(T.1.2)�̎��͔r�o���[���[�Ɋ��񂾍ŏI���e��r�o���� */
#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 1998/11/17 by T.Soneoka */
		if (tskno_SCN_STxStoreTask != 0xffff) {
			del_tsk(&tskno_SCN_STxStoreTask);
		}
#endif
		/**	�X�L���i�N���[�Y (�ŏI���e��r�o)	*/
		if (SCN_Close(SCN_DOC_EXITING) != SCN_DOC_EXIT_OK) {	/**	���ʂm�f	*/
			/**	���e�r�o�m�f�����C���^�X�N�֒ʒm	*/
			MsgFromFaxComToMain.Item    = FROM_FAXCOM;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_CLOSE_ERROR;
			snd_msg( mbxno.MAN_Task, &MsgFromFaxComToMain );
			rcv_msg( mbxno.FCM_Task, &FcomMsg );
		}
	}
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߑ��M�̍ŏ��`�����Ԃ𓾂�
	
	@li			
	@param		
	@return		�ŏ��`������
	@note		
	@date		2005/07/06 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE FCM_GetIsseiMinScanningTime(
						UBYTE availability,	/* �ŏ��`�����Ԕ\�� */
						UBYTE resolution)	/* �𑜓x */

{
	UBYTE time;
	
	switch (availability) {
	case SCAN_MINIMUM_TIME0:
	case SCAN_MINIMUM_TIME5:
	case SCAN_MINIMUM_TIME10:
	case SCAN_MINIMUM_TIME20:
	case SCAN_MINIMUM_TIME40:
		time = availability;
		break;
	case SCAN_MINIMUM_TIME10_2:
		if (resolution == SYS_NORMAL) {
			time = SCAN_MINIMUM_TIME10;
		}
		else {
			time = SCAN_MINIMUM_TIME5;
		}
		break;
	case SCAN_MINIMUM_TIME20_2:
		if (resolution == SYS_NORMAL) {
			time = SCAN_MINIMUM_TIME20;
		}
		else {
			time = SCAN_MINIMUM_TIME10;
		}
		break;
	case SCAN_MINIMUM_TIME40_2:
		if (resolution == SYS_NORMAL) {
			time = SCAN_MINIMUM_TIME40;
		}
		else {
			time = SCAN_MINIMUM_TIME20;
		}
		break;
	default:
		time = SCAN_MINIMUM_TIME20;
		break;
	}
	
	return time;
}

/**************************************************************************************************/
/**
	@brief		DCS���M
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/07 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_SendIsseiDCS(void)
{
	FCM_SetIsseiDCS_FIF(); /* DCS TSI��FIF�쐬 */
	TxNonStandardFrameByteCount = 0;
	
	MDM_TransmitCommand(); /* DCS���M */
}

/**************************************************************************************************/
/**
	@brief		DCS+TSI�t���[���쐬
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/06 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_SetIsseiDCS_FIF(void)
{
	TxID_FrameByteCount = 0;
	TxStandardFrameByteCount = 0;
	
	/**	�c�b�r�̃A�h���X�t�B�[���h�����t�B�[���h��e�b�e�����f���o�b�t�@�ɃZ�b�g	*/
	MDM_ModemBuffer[InSTD][0] = ADDRESS_FIELD_DATA;
	MDM_ModemBuffer[InSTD][1] = LAST_FRAME_DATA;
	MDM_ModemBuffer[InSTD][2] = DCS_F;

	if (CheckSubscriberID_Buf() == YES) {		/**	���@�m�n����	*/
		/**	�s�r�h�̃A�h���X�t�B�[���h�����t�B�[���h��e�b�e�����f���o�b�t�@�ɃZ�b�g	*/
		MDM_ModemBuffer[InID][0] = ADDRESS_FIELD_DATA;
		MDM_ModemBuffer[InID][1] = NON_LAST_FRAME_DATA;
		MDM_ModemBuffer[InID][2] = TSI_F;
		SetSubscriberID_Frame(); /* ���@�m�n�����f���o�b�t�@�ɃZ�b�g	*/
		TxID_FrameByteCount = 23; /* ���f���o�b�t�@�ɃZ�b�g�����o�C�g������ϐ��ɃZ�b�g	*/
	}
	
#if 0
//	/*	�c�b�r�e�h�e�r�b�g�Z�b�g	*/
//	if (DIS_ReceivedFlag == YES) {		/**	�c�h�r����M	*/
//		/**	�w�r�b�g���Z�b�g	*/
//		MDM_ModemBuffer[InNS][2] |= X_BIT;
//		MDM_ModemBuffer[InID][2] |= X_BIT;
//		MDM_ModemBuffer[InSTD][2] |= X_BIT;
//	}
#endif
	
	MDM_ModemBuffer[InSTD][3] = BIT_CLEAR; /**	�c�b�r �e�h�e�P�o�C�g�ڃN���A	*/
	MDM_ModemBuffer[InSTD][4] = BIT_CLEAR; /**	�s�S�r�b�g�Z�b�g	*/
	MDM_ModemBuffer[InSTD][4] |= JT_T4_BIT;
	
	/*	���s���M�{�[���[�g�Z�b�g	*/
	switch (AttemptTxBaudRate) {		/**	���s���M�{�[���[�g	*/
	case BPS2400_V27:	/**	2400BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V27_2400BPS_BIT;
		break;
	case BPS4800_V27:	/**	4800BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V27_4800BPS_BIT;
		break;
	case BPS7200_V29:	/**	V29-7200BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V29_7200BPS_BIT;
		break;
	case BPS9600_V29:	/**	V29-9600BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V29_9600BPS_BIT;
		break;
	case BPS7200_V17:	/**	V17-7200BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V17_7200BPS_BIT;
		break;
	case BPS9600_V17:	/**	V17-9600BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V17_9600BPS_BIT;
		break;
	case BPS12000_V17:	/**	V17-12000BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V17_12000BPS_BIT;
		break;
	case BPS14400_V17	:	/**	V17-14400BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V17_14400BPS_BIT;
		break;
	case  BPS12000_V33:	/**	V33-12000BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V33_12000BPS_BIT;
		break;
	case  BPS14400_V33:	/**	V33-14400BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V33_14400BPS_BIT;
		break;
	}
	
	MDM_ModemBuffer[InSTD][8] = BIT_CLEAR; /**	DCS FIF �T�o�C�g�ڃN���A	*/
	
	switch (TxMode) {		/**	���M�����x	*/
	case SYS_NORMAL:	/**	�m�[�}��	*/
		break;
	case SYS_SFINE:	/**	�r�t�@�C��(R8*15.4mm)�	*/
		MDM_ModemBuffer[InSTD][8] |= SUPER_FINE_BIT;
		break;
	/* 300*400�̑��M�^�`�m�y�t�Q�k */
	case SYS_E_HFINE: /** ANZU��E_H-FINE��(300*400)�~�� S-FINE�r�b�gON By t.yamaguchi */
		MDM_ModemBuffer[InSTD][8] |= SUPER_FINE_BIT;
		break;
	case SYS_HFINE:	/**	�r�t�@�C���R(400*400)	*/
		MDM_ModemBuffer[InSTD][8] |= HYPER_FINE_BIT;
		break;
	case SYS_GRAY16:		/**	���Ԓ��P�U	*/
	case SYS_GRAY16_SEP:	/**	���Ԓ��P�U_SEP	*/
	case SYS_GRAY32:		/**	���Ԓ��R�Q	*/
	case SYS_GRAY32_SEP:	/**	���Ԓ��R�Q_SEP	*/
	case SYS_GRAY64:		/**	���Ԓ��U�S	*/
	case SYS_GRAY64_SEP:	/**	���Ԓ��U�S_SEP	*/
	case SYS_GRAY128:
	case SYS_GRAY128_SEP:
	case SYS_FINE:			/**	�t�@�C��	*/
	case SYS_EFINE: /** E-FINE(R12*11.55L/mm)�́AFINE�ޯĂn�m 96/06/14 By t.yamaguchi */
		MDM_ModemBuffer[InSTD][4] |= SET_FINE_BIT;
		break;
	default:
		break;
	}
	if (TxModeMethod == SYS_INCH) {	/**	�C���`�x�[�X	*/
		MDM_ModemBuffer[InSTD][8] |= INCH_BASE_BIT;
	}
	
	MDM_ModemBuffer[InSTD][6] = BIT_CLEAR; /**	DCS FIF 4 �o�C�g�ڃN���A	*/
	
	switch (TxCodingMethod) {		/**	���M����������	*/
	case SYS_MH_CODE:	/**	�l�g	*/
		break;
	case SYS_MR_CODE:	/**	�l�q	*/
		MDM_ModemBuffer[InSTD][4] |= SET_MR_BIT;
		break;
	case SYS_MMR_CODE:	/**	�l�l�q	*/
		MDM_ModemBuffer[InSTD][6] |= SET_MMR_BIT;
		break;
	case SYS_JBIG_CODE:
		/** �i�a�h�f�r�b�g�͍Ō�ɃZ�b�g����	*/
		break;
	}
	
	MDM_ModemBuffer[InSTD][5] = BIT_CLEAR; /**	DCS FIF 3 �o�C�g�ڃN���A	*/
	
	switch (TxWidth) {		/**	���M���e��	*/
	case SYS_DOCUMENT_A4_SIZE:	/**	�`�S	*/
		MDM_ModemBuffer[InSTD][5] |= RX_A4_PAPER_BIT;
		break;
	case SYS_DOCUMENT_B4_SIZE:	/**	�a�S	*/
		MDM_ModemBuffer[InSTD][5] |= RX_B4_PAPER_BIT;
		break;
	case SYS_DOCUMENT_A3_SIZE:	/**	�`�R	*/
		MDM_ModemBuffer[InSTD][5] |= RX_A3_PAPER_BIT;
		break;
	}
	
	switch (FaxTxMaxLength) {		/**	���M���e��	*/
	case SYS_A4_LENGTH:	/**	�`�S	*/
		MDM_ModemBuffer[InSTD][5] |= LENGTH_A4_BIT;
		break;
	case SYS_B4_LENGTH:	/**	�a�S	*/
		MDM_ModemBuffer[InSTD][5] |= LENGTH_B4_BIT;
		break;
	case SYS_NO_LIMIT:	/**	������	*/
		MDM_ModemBuffer[InSTD][5] |= LENGTH_UNLIMITED_BIT;
		break;
	}
	
	switch (TxMinimumScanningTime) {		/**	���M�ŏ��`������	*/
	case SCAN_MINIMUM_TIME20:	/**	TIME20ms	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME20;
		break;
	case SCAN_MINIMUM_TIME40:	/**	TIME40ms	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME40;
		break;
	case SCAN_MINIMUM_TIME10:	/**	TIME10ms	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME10;
		break;
	case SCAN_MINIMUM_TIME5:	/**	TIME5ms	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME5;
		break;
	case SCAN_MINIMUM_TIME0:	/**	TIME0ms	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME0;
		break;
	}
	
	MDM_ModemBuffer[InSTD][5] |= EXPAND_FIELD_BIT; /**	�g���r�b�gON�i�Q�S�r�b�g�j	*/
	
	MDM_ModemBuffer[InSTD][6] &= ~EXPAND_FIELD_BIT; /**	�g���t�B�[���hOFF�i�R�Q�r�b�g�j	*/
	
	MDM_ModemBuffer[InSTD][7] = BIT_CLEAR; /**	DCS FIF 5�o�C�g�ڃN���A	*/
	MDM_ModemBuffer[InSTD][7] |= EXPAND_FIELD_BIT; /**	�g���r�b�gON�i�S�O�r�b�g�j	*/
	
	MDM_ModemBuffer[InSTD][8] = BIT_CLEAR; /**	DCS FIF 6 �o�C�g�ڃN���A	*/
	
	TxStandardFrameByteCount = 7; /**	DCS�t���[�����M�o�C�g�� 7�o�C�g�Z�b�g	*/
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߑ��M�̃t�F�[�YC
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����FaxTxPhaseC()
	@date		2005/06/16 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiTxPhaseC(void)
{
	FaxComPhaseStatus = FAX_TX_PH_C_BEFORE_PIX;
	TxPageDataSetFlag	= 0; /* �y�[�W�I�[�v���̃t���O�������� */
	CodecPageStatus = CDC_READY; /* �R�[�f�b�N�X�e�[�^�X�������� Aug.18.1994 */
	
	SetTxPageData(); /* ���M�y�[�W�f�[�^�Z�b�g */
	SYS_FaxCommStage = FCM_TRANSMIT_SET;
	SendMsgFaxComToMain(MSG_FAXCOM_DISPLAY); /* �\���ؑ֎w��(��f�[�^���M��) */
	
	SCN_DecideReductionPattern(); /* �k���p�^�[�������� */
	
	SaveT30TimingData(SYS_T30_START_TIME); /* �s�R�O���j�^�p�f�[�^�Z�b�g	*/
	SaveT30Data(SYS_T30_TX_PIX, &MDM_ModemBuffer[0][0], 0);
	FaxComPhaseStatus = FAX_TX_PH_C_PIX;
	
	
	MDM_TxPixOpen(TxBaudRate, ECM_OFF); /* ���f���I�[�v�� */
	
	TxPageFinishStatus = MDM_TxPix(ECM_OFF, TxSmType);
	
	MDM_TxPixClose(ECM_OFF);
	
	FaxComPhaseStatus = FAX_TX_PH_C_AFTER_PIX;	/* Jun.29.1994 */

	/*--------------------------------------------------*/
	/*	��f�[�^���M���ʂ��u�P�y�[�W���M�I���v�̏ꍇ��	*/
	/*	���y�[�W������\��������̂ŁC�ēx�Z�b�g����	*/
	/*--------------------------------------------------*/
	FCM_TxEndSet();	/* ���M�f�[�^���c���Ă��邩���f���� */

	FaxComPhaseStatus = FAX_TX_PH_D;

	if (MDM_PhaseC_Status == TX_DOC_ERR) { /* ���e�G���[�̎��A�����v���� T.Nose 1997/09/20 */
		LampOff();
	}
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߑ��M�̃t�F�[�YD
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����FaxTxPhaseD()
	@date		2005/06/16 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiTxPhaseD(void)
{
	UpdatePageInformationFlag = 1;
	UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;

	/**	�d�b�l���M�t���[���J�E���^�Ƀh���C�o�̂d�b�l�t���[�������Z�b�g	*/
	/* ECM_FrameCounter = MDM_EcmFrameNumber; */

	/**	���M�e�b�e���N���A	*/
	TxOptionFCF = 0;
	TxFCF = 0;

	/* ���������M�œK�����������s����ׁA�����M�����y�[�W���o���Ă����܂� 1997/06/02  By T.Yamaguchi */
	EraseIndexData.Item = SYS_DocBlock.Index.Item;
	EraseIndexData.No   = SYS_DocBlock.Index.No;
	EraseIndexData.Page = SYS_DocBlock.Index.Page;
	EraseIndexData.BoxNumber = SYS_DocBlock.Index.BoxNumber;

	TxPageFinishStatus = FCM_ResetIsseiTxPageStatus(); /* �t�F�[�Y�b�̌��ʂ��t�F�[�Y�c�p�ɕϊ� */

	switch (TxPageFinishStatus) { /* ��f�[�^���M���� */
	case	TX_SEPARATE:		/**	���e�������I�[�o�[	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	�X�g�b�v�L�[���͂���	*/
			TxFCF = EOP_F;				/**	�e�b�e�ɂd�n�o���Z�b�g	*/
			FaxComPerformingFlag = 0;	/**	�ʐM���t���O���N���A	*/
			TransmitError( 0x14, 1 );	/**	�s�D�P�D�S���Z�b�g	*/	/* Apr.29.1995 */
		}
		else {
			/**	SYS_TxTotalPage �� TxMemoryFilePage ���X�V����ɃZ�b�g	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;
			TxFCF |= MPS_F;				/**	�e�b�e�ɂl�o�r��(or��)�Z�b�g	*/
		}
		/* ECM_FrameCounter = MDM_EcmFrameNumber; */	/**	�d�b�l�t���[���J�E���^�Ƀh���C�o�̃t���[�������Z�b�g	*/
		
		MakeHDLC_Frame(TxFCF, TxOptionFCF); /* �w��t���[���쐬 */
		MDM_TransmitCommand(); /* ���ߑ��M */
		
		/* ECM_PageCounter++; */			/**	�d�b�l�y�[�W�J�E���^���{�P	*/
		/* ECM_BlockCounter = 0; */		/**	�d�b�l�u���b�N�J�E���^���O�N���A	*/
		break;
	case	TX_PAGE_END_MODE_CHANGE:	/**	�P�y�[�W�I���C���[�h�ύX����	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	�X�g�b�v�L�[���͂���	*/
			TxFCF = EOP_F;				/**	�e�b�e�ɂd�n�o���Z�b�g	*/
			FaxComPerformingFlag = 0;	/**	�ʐM���t���O���N���A	*/
			TransmitError( 0x14, 1 );	/**	�s�D�P�D�S���Z�b�g	*/	/* Apr.29.1995 */
		}
		else {
			/**	SYS_TxTotalPage �� TxMemoryFilePage ���X�V����ɃZ�b�g	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;
			TxPageDataSetFlag = 0;		/**	���M�y�[�W�f�[�^�Z�b�g�ς݃t���O���N���A	*/
			TxFCF |= EOM_F;				/**	�e�b�e�ɂd�n�l��(or��)�Z�b�g	*/
			TxModeChangedFlag = 1;		/**	���M���[�h�ύX�t���O���Z�b�g	*/
			TxRetrainingFlag = 1;		/**	�ăg���[�j���O�t���O���Z�b�g	*/
		}
		/* ECM_FrameCounter = MDM_EcmFrameNumber; */	/**	�d�b�l�t���[���J�E���^�Ƀh���C�o�̃t���[�������Z�b�g	*/
		
		MakeHDLC_Frame(TxFCF, TxOptionFCF); /* �w��t���[���쐬 */
		MDM_TransmitCommand(); /* ���ߑ��M */
		
		/* ECM_PageCounter++; */			/**	�d�b�l�y�[�W�J�E���^���{�P	*/
		/* ECM_BlockCounter = 0; */		/**	�d�b�l�u���b�N�J�E���^���O�N���A	*/
		
		UpdateTxPageInformation();			/**	���M�y�[�W�ԍ����X�V	*/
		break;
	case	TX_END:		/**	�S�y�[�W���M�I��	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	�X�g�b�v�L�[���͂���	*/
			TxFCF = EOP_F;				/**	�e�b�e�ɂd�n�o���Z�b�g	*/
			FaxComPerformingFlag = 0;	/**	�ʐM���t���O���N���A	*/
		}
		else {
			/**	SYS_TxTotalPage ���X�V����ɃZ�b�g	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;			/*		�ݸ���Ă���悤�ɕύX By T.Yamaguchi Apr.27'96 */
			TxPageDataSetFlag = 0;		/**	���M�y�[�W�f�[�^�Z�b�g�ς݃t���O���N���A	*/
			TxFCF |= EOP_F;				/**	�e�b�e�ɂd�n�o��(or��)�Z�b�g	*/
			TxRetrainingFlag = 1;		/**	�ăg���[�j���O�t���O���Z�b�g	*/
		}
		/* ECM_FrameCounter = MDM_EcmFrameNumber; */	/**	�d�b�l�t���[���J�E���^�Ƀh���C�o�̃t���[�������Z�b�g	*/
		
		MakeHDLC_Frame(TxFCF, TxOptionFCF); /* �w��t���[���쐬 */
		MDM_TransmitCommand(); /* ���ߑ��M */
		
		FaxTimer(FCM_ISSEI_TX_D_E_TIME);
		
		TxCoverPageFlag = 0; /* �J�o�[�y�[�W���M�t���O���N���A */
		FaxPhaseE(5); /* �ʐM�I���i�c�b�m����j */
		
		/* ECM_PageCounter++; */			/**	�d�b�l�y�[�W�J�E���^���{�P	*/
		/* ECM_BlockCounter = 0; */		/**	�d�b�l�u���b�N�J�E���^���O�N���A	*/
		/*
		** �f�B�X�v���C��TxMemoryFilePage�ASYS_TxTotalPage�����̂܂ܕ\�����Ă���̂�
		** �y�[�W�� 2/1�̂悤�ɂȂ��Ă��܂�
		** �����ŁA�����̏����ȍ~�̓y�[�W����\�����Ȃ��悤��SYS_FaxCommStage��ύX���܂�
		** by T.Soneoka 1998/01/09
		*/
		SYS_FaxCommStage = FCM_TRANSMIT;
		
		UpdateTxPageInformation();				/**	���M�y�[�W�ԍ����X�V	*/
		break;
	case	TX_STOPPED:		/**	�X�g�b�v�L�[�Œ�~	*/
		/*----------------------------------------------------------------------*/
		/*	��f�[�^���M���ɃX�g�b�v�L�[�������ꂽ�ꍇ�̏�����ύX	Sep.13.1994	*/
		/*		1)	�����I���ݒ�̏ꍇ�́C���c�b�m�𑗏o����					*/
		/*		2)	�ʏ�I���̏ꍇ�́C�d�n�o�𑗏o���C������M����				*/
		/*			(�S�y�[�W�I���̏ꍇ�Ɠ��������D)							*/
		/*			�y�[�W���̓J�E���g���Ȃ�						Nov.28.1994	*/
		/*		3)	�s�D�P�D�S�ŏI������  (Oct.18.1994)							*/
		/*----------------------------------------------------------------------*/
		if (CHK_TxForceStop() != 0) {	/**	�����I������ꍇ (RTC�Ȃ�)	*/
			FaxPhaseE( 5 );					/**	�c�b�m���o���C�ʐM���t���O���N���A (������M���Ȃ�)	*/
		}
		else {							/**	�����I�����Ȃ� (RTC�t���Đ���I��)	*/
			/**	SYS_TxTotalPage ���X�V����ɃZ�b�g	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;			/*		�ݸ���Ă���悤�ɕύX By T.Yamaguchi Apr.27'96 */
			TxPageDataSetFlag = 0;		/**	���M�y�[�W�f�[�^�Z�b�g�ς݃t���O���N���A	*/
			TxFCF |= EOP_F;				/**	�e�b�e�ɂd�n�o��(or��)�Z�b�g	*/
			/* ECM_FrameCounter = MDM_EcmFrameNumber; */	/**	�d�b�l�t���[���J�E���^�Ƀh���C�o�̃t���[�������Z�b�g	*/
			
			MakeHDLC_Frame(TxFCF, TxOptionFCF); /* �w��t���[���쐬 */
			MDM_TransmitCommand(); /* ���ߑ��M */
			
			/* ECM_PageCounter++; */			/**	�d�b�l�y�[�W�J�E���^���{�P	*/
			/* ECM_BlockCounter = 0; */		/**	�d�b�l�u���b�N�J�E���^���O�N���A	*/
		}
		TransmitError( 0x14, 1 );	/**	�s�D�P�D�S���Z�b�g	*/	/* Oct.18.1994 */
		break;
	case	TX_1M_OVER:		/**	�P���I�[�o�[	*/
	default:		/**	���̑��̃G���[	*/
		TimerCutStatus = 1;
		FaxPhaseE( 5 );					/**	�c�b�m���o���C�ʐM���t���O���N���A	*/
		TransmitError( 0x31, 1 );		/**	�s�D�R�D�P���Z�b�g	*/
		break;
	}
}

/**************************************************************************************************/
/**
	@brief		�t�F�[�YC�̌��ʂ��ăZ�b�g
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����ResetTxPageFinishStatus()
	@date		2005/07/07 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE FCM_ResetIsseiTxPageStatus(void)
{
	UBYTE ret;
	
	TxModeChangedFlag = 0; /* ���M���[�h�ύX�t���O���N���A */
	
	if ((TxPageFinishStatus == TX_PAGE_END) || (TxPageFinishStatus == TX_NEXT_FILE)) { 
		/* �P�y�[�W�I��/�P�t�@�C�����M�I���A���t�@�C������ */
		FCM_CompareIsseiTxMode(); /* ���M���[�h�̕ύX���`�F�b�N */
		ret = TX_PAGE_END_MODE_CHANGE;
		/* ret = TX_PAGE_END; */
	}
	else {
		ret = TxPageFinishStatus;
	}
	
	return ret;
}

/**************************************************************************************************/
/**
	@brief		���M���[�h�̕ύX���`�F�b�N
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����CompareTxMode()
	@date		2005/07/07 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_CompareIsseiTxMode(void)
{
	UWORD file_page;			/**	���y�[�W�̃t�@�C���i���o�[	*/
	UBYTE next_mode, next_size;	/**	���y�[�W�̃��[�h�C��	*/
	UBYTE gray_flag_on;
	
	gray_flag_on = 0;
	
	/**	���e����u���b�N�����y�[�W�̏��ɍX�V	*/
	if (TxSmType == TX_CVR) {
		file_page = TxMemoryFilePage;
	}
	else {
		file_page = TxMemoryFilePage + 1;
	}
	
	if (TxPageFinishStatus == TX_NEXT_FILE) {
		file_page = 1;
	}
	GetNextTxPageData(file_page);

	/**	���y�[�W�̃��[�h����荞�� (GRAY??��FINE�ɂ���)	*/
	next_mode = SYS_DocBlock.Src.Mode;
	gray_flag_on = next_mode;
	switch (next_mode) {
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
	case	SYS_GRAY128:
	case	SYS_GRAY128_SEP:
		/* �X�L���i���M �ł�����̔\�� 400DPI ��� �Ȃ� H_FINE */
		next_mode = ScanTxGrayMode;
		break;
	default:
		break;
	}

	/**	���y�[�W�̃��[�h�� SYS_GRAY?? �� SYS_FINE �ɂ���	*/
	switch (FirstTxMode) {
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
	case	SYS_GRAY128:
	case	SYS_GRAY128_SEP:
		FirstTxMode = ScanTxGrayMode;
		break;
	default:
		break;
	}

	if ((FirstTxMode != next_mode) && (TxMode != next_mode)) { /* (�����M�������[�h�����y�[�W�̃��[�h)&&(���M���[�h�����y�[�W�̃��[�h) */
		TxModeChangedFlag = 1; /* ���[�h�ύX�t���O���Z�b�g���� */
	}

	/**	���y�[�W�̃T�C�Y����荞��	*/
	next_size= SYS_DocBlock.Src.Size;

	if (DocWidth != next_size) {	/**	���M�������e�T�C�Y�����y�[�W�̃T�C�Y	*/
		/**	���[�h�ύX�t���O���Z�b�g����	*/
		TxModeChangedFlag = 1;
	}

	/**	���y�[�W�̌��e���[�h���Z�b�g����	*/
	FirstTxMode = gray_flag_on;/* ���Ԓ��\�� Set Gray Too! */
	/**	���y�[�W�̌��e�T�C�Y���Z�b�g����	*/
	DocWidth = next_size;
}

/**************************************************************************************************/
/**
	@brief		��Ďw�ߒʐM��̉�b�\�񏈗�
	
	@li			
	@param		
	@return		�Ȃ�
	@note		�I���W�i����MDM_RxVoiceReq()
	@date		2005/07/23 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void FCM_IsseiVoiceReq(
				UWORD time) /* �x��������(�b) */
{
	MESSAGE_t	*MDM_Msg;
	struct Timer10msData_t	t3timer;
	UBYTE	rtn;
	struct GenerateRingData_t ring_data;		/*  1994/9/1 Y.Suzuki */
	UBYTE	timerID_T3_Timer; /* Added by H.Kubo 1997/08/12 */

	tskno_Bell = 0xFFFF;

	/*	�n�g���o�E�Ăяo���x�����^�X�N�N��	*/
	/* �ȉ�H8����Ƃ��ė��܂��� 1994/9/1 Y.Suzuki */
	GenerateRingStartRelayControl();
	ring_data.StartTime		= 0;
	ring_data.SendMBX		= mbxno.MDM_Task;
	ring_data.RingingTel	= ALL_TEL_RINGING;

	cre_tsk(&tskno_Bell, TSK_NCU_GENERATERINGSIGNALTASK, &ring_data );	/** �n�g���o�E�Ăяo���x�����^�X�N�N�� */

	/*	�s�R�^�C�}�p�^�C�}�^�X�N�N������	*/
	t3timer.Time = (time * 100);
	t3timer.SendMBX = mbxno.MDM_Task;	/**	�s�R�^�C�}�A���C���{�b�N�X�ݒ�	*/
	t3timer.ReturnValue = MSG_T3_TIME_OVER;	/**	�߂�l�ݒ�	*/
	timerID_T3_Timer = 0xff;
	CMN_MultiTimer10msStart(&timerID_T3_Timer, &t3timer);

	/*	���b�Z�[�W��M
	** 1.FCOM_TEL1_OFF_HOOK					(7)
	** 2.FCOM_TEL2_OFF_HOOK					(8)
	** 3.FCOM_HOOK_KEY						(9)
	** 4.FCOM_STOP_KEY						(5)
	** 5:MSG_T3_TIME_OVER	:�s�R�^�C���I�[�o(13)
	*/
	do {
		rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	���b�Z�[�W��M	*/
	} while (!((MDM_Msg->Message == FCOM_TEL1_OFF_HOOK) ||
					(MDM_Msg->Message == FCOM_TEL2_OFF_HOOK) ||
					(MDM_Msg->Message == FCOM_HOOK_KEY) ||
					(MDM_Msg->Message == FCOM_STOP_KEY) ||
					(MDM_Msg->Message == MSG_T3_TIME_OVER)));

	rtn = (UBYTE)MDM_Msg->Message;	/* 1997/02/24 Y.Murata */

/* �x�@FAX DVT_ID62 Added start by SMuratec �� 2005/12/08 */ 
	if (rtn == MSG_T3_TIME_OVER) {
		if ( CHK_LineSetting()		/* ����ݒ� == �W����� */
			&& HDST_RelaySetting() ) {	/* �n���h�Z�b�g�͊g��������� */
			switch (NCU_LineStatus & EXT_LINE_STATUS) {
			case EXT_CI_IN:
	 			break;
			default:
				HDST_RelayOff();        /* �n���h�Z�b�g��W������ɐڑ����� */
				break;
			}
		}
		else if ( !CHK_LineSetting()		/* ����ݒ� == �g����� */
				&& !HDST_RelaySetting() ) {			/* �n���h�Z�b�g�͕W��������� */
			switch (NCU_LineStatus & STD_LINE_STATUS) {
			case STD_CI_IN:
	 			break;
			default:
				HDST_RelayOn();        /* �n���h�Z�b�g���g������ɐڑ����� */
				break;
			}
		}
		UpdateLCD();
	}
/* �x�@FAX DVT_ID62 Added end by SMuratec �� 2005/12/08 */ 

	/*	�n�g���o�E�Ăяo���x�����^�X�N�I��	*/
	if (tskno_Bell != 0xFFFF) {
		del_tsk( &tskno_Bell  );	/**	�n�g���o�E�Ăяo���x�����^�X�N�I��	*/
	}

	/*	�^�C�}�^�X�N�I��	*/
	if (timerID_T3_Timer != 0xff) { /* Ported from ORANGE by H.Kubo 1997/08/12 */
		CMN_MultiTimer10msStop(&timerID_T3_Timer);
	}

	/*	�߂�l�ݒ�	*/
	/*switch(MDM_Msg->Message) { 1997/02/24 Y.Murata */
	switch(rtn) {
	case FCOM_TEL1_OFF_HOOK:
		rtn = TEL1_OH_DETECT;
		break;
	case FCOM_TEL2_OFF_HOOK:
		rtn = TEL2_OH_DETECT;
		break;
	case FCOM_HOOK_KEY:
		rtn = HOOK_KEY_OH_DETECT;
		break;
	default:
		rtn = T3_TIME_OVER;
	}
	GenerateRingEndRelayControl();/* 94/11/18 Y.Suzuki */
	/* return (rtn); */
	
	
	
	/* �ȉ��́ARxRequestedVoiceMode()�̈ꕔ����ڐA */
	/* ���E�𕪂���₷�����邽�߁A�璷�ɂȂ��Ă��܂� */
	switch (rtn) {		/**	��b�\�񌋉�	*/
	case	TEL1_OH_DETECT:		/**	�s�d�k�P�I�t�t�b�N���o	*/
	case	TEL2_OH_DETECT:		/**	�s�d�k�Q�I�t�t�b�N���o	*/
	case	HOOK_KEY_OH_DETECT:	/**	�I�t�t�b�N�L�[���o	*/
		SYS_VoiceCallAccepted = rtn;	/**	��b�\�񐬗�(�n�g����)	*/
		/* Sep.16.1994 */
		if (rtn == TEL1_OH_DETECT) {
			FaxTelOffHookTEL1Flag = 1;
		}
		else if (rtn == TEL2_OH_DETECT) {
			FaxTelOffHookTEL2Flag = 1;
		}
		
		/*------------------------------------------*/
		/**	�R�O�Oms�E�F�C�g��C�g�^�k�����[�n�e�e	*/
		/*------------------------------------------*/
		FaxTimer( 300 );
		FaxTelAutoSWAfterTransaction();
		break;
	default:
		break;
	}
}

#endif /* KEISATSU */

