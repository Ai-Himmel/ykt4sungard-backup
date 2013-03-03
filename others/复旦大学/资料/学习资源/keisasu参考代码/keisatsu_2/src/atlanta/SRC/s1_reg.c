/**********************************************************************************************************************
	@(#)$Id: s1_reg.c,v 1.14 2005/11/17 23:19:34 mi93007 Exp $
	Create        : 2005/06/13
	Author        : �΋����a
	Description   : S1���W�X�^����
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\s1_pro.h"
#include "\src\atlanta\define\s1_def.h"
#include "\src\atlanta\ext_v\s1_data.h"

/**************************************************************************************************/
/**
	@brief		S1������������(�N����)
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/06/09 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_Initialize(void)
{
	S1_HardwareReset();
	
	wai_tsk(20); /* 200ms */
}

/**************************************************************************************************/
/**
	@brief		S1������������(�ʐM�J�n��)
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/06/09 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_InitializeFaxCom(
				BOOL bavailable,	/* �X�N�����u���L��/���� */
				BOOL bbypass)		/* S1�o�C�p�X���邩�ۂ� */
{
	S1_SoftwareReset(); /* S1�\�t�g���Z�b�g */
	
	/* �X�N�����u���̗L��/�����̃Z�b�g */
	if (bavailable == TRUE) {
		S1_SetScrambleAvailable(TRUE);
	}
	else {
		S1_SetScrambleAvailable(FALSE);
	}
	
	S1_BypassS1(bbypass); /* S1�o�C�p�X�̃Z�b�g */
	
	S1_HDLC_InitializeCRC(); /* CRC�����������̏����� */
	S1_HDLC_InitializeTransMode(); /* HDLC �]�����[�h�̏����� */
	S1_HDLC_InitializeTxMode(); /* HDLC ���M���[�h������ */
}

/**************************************************************************************************/
/**
	@brief		G3��M�I�[�v��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_OpenG3Rx(
			BOOL bsenyo) /* TRUE:��p FALSE:���� */
{
	S1_SetMode(FALSE); /* SCI���[�h */
	
	S1_SetScrambleMode(bsenyo);
	
	S1_SCI_SetIntDTC_Enabled(S1_REG_BIT_SCI_OVEIE | S1_REG_BIT_SCI_RXRDYDTCE);
	
	S1_EnableInterrupt(); /* S1���荞�݋��� */
	S1_EnableDTC_Request(S1_DTC_RX_SCI); /* DTC�v������ */
	S1_SCI_EnableRx(TRUE); /* ��M���� */
	
	S1_EnableRLSD(TRUE); /* RLSD��L���ɂ��� */
}

/**************************************************************************************************/
/**
	@brief		G3��M�N���[�Y
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_CloseG3Rx(void)
{
	S1_EnableRLSD(FALSE); /* RLSD�𖳌��ɂ��� */
	
	S1_SCI_EnableRx(FALSE); /* ��M�֎~ */
	
	S1_EnableDTC_Request(S1_DTC_NONE);
	S1_ClearDTC_Request(); /* DTC�v���N���A */
	S1_DisableInterrupt(); /* S1���荞�݋֎~ */
	
}

/**************************************************************************************************/
/**
	@brief		G3���M�I�[�v��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/21 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_OpenG3Tx(
			BOOL bsenyo) /* TRUE:��p FALSE:���� */
{
	volatile UBYTE benable = 1;
	
	S1_SetMode(FALSE); /* SCI���[�h */
	
	S1_SetScrambleMode(bsenyo);
	
	S1_SCI_SetIntDTC_Enabled(S1_REG_BIT_SCI_TXRDYDTCE);
	
	S1_EnableInterrupt(); /* S1���荞�݋��� */
	S1_EnableDTC_Request(S1_DTC_TX_SCI); /* DTC�v������ */
	
	S1_SCI_EnableTx(TRUE); /* ���M���� */
	
	if (benable == 1) {
		S1_EnableRTS(TRUE); /* RTS��L���ɂ��� */
	}
}

/**************************************************************************************************/
/**
	@brief		G3���M�N���[�Y
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/21 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_CloseG3Tx(void)
{
	S1_EnableRTS(FALSE); /* RTS�𖳌��ɂ��� */
	
	S1_SCI_EnableTx(FALSE); /* ���M�֎~ */
	
	S1_EnableDTC_Request(S1_DTC_NONE);
	S1_ClearDTC_Request(); /* DTC�v���N���A */
	S1_DisableInterrupt(); /* S1���荞�݋֎~ */
}

/**************************************************************************************************/
/**
	@brief		ECM��M�I�[�v��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/21 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_OpenECM_Rx(
			BOOL bsenyo) /* TRUE:��p FALSE:���� */
{
	S1_SetMode(TRUE); /* HDLC���[�h */
	
	S1_SetScrambleMode(bsenyo);
	
	S1_HDLC_SetRxIntDTC_Enabled(S1_REG_BIT_HDLC_ERRIE | S1_REG_BIT_HDLC_ENDIE | S1_REG_BIT_HDLC_RXDI);
	
	S1_HDLC_EnableRxInterrupt(TRUE);
	S1_HDLC_EnableRxDMA_Request(TRUE);
	
	S1_EnableInterrupt(); /* S1���荞�݋��� */
	S1_EnableDTC_Request(S1_DTC_RX_HDLC); /* DTC�v������ */
	S1_HDLC_EnableRx(TRUE); /* ��M���� */
	
	S1_EnableRLSD(TRUE); /* RLSD��L���ɂ��� */
}

/**************************************************************************************************/
/**
	@brief		ECM��M�N���[�Y
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/21 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_CloseECM_Rx(void)
{
	S1_EnableRLSD(FALSE); /* RLSD�𖳌��ɂ��� */
	
	S1_HDLC_EnableRx(FALSE); /* ��M�֎~ */
	
	S1_EnableDTC_Request(S1_DTC_NONE);
	S1_ClearDTC_Request(); /* DTC�v���N���A */
	S1_DisableInterrupt(); /* S1���荞�݋֎~ */
	
	S1_HDLC_EnableRxDMA_Request(FALSE);
	S1_HDLC_EnableRxInterrupt(FALSE);
}

/**************************************************************************************************/
/**
	@brief		ECM���M�I�[�v��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/21 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_OpenECM_Tx(
			BOOL bsenyo) /* TRUE:��p FALSE:���� */
{
	S1_SetMode(TRUE); /* HDLC���[�h */
	
	S1_SetScrambleMode(bsenyo);
	
	/* S1_HDLC_SetTxIntDTC_Enabled(S1_REG_BIT_HDLC_TXENDIE | S1_REG_BIT_HDLC_TXDI); */
	S1_HDLC_SetTxIntDTC_Enabled(S1_REG_BIT_HDLC_TXDI);
	
	S1_HDLC_EnableTxInterrupt(TRUE);
	S1_HDLC_EnableTxDMA_Request(TRUE);
	
	S1_EnableInterrupt(); /* S1���荞�݋��� */
	S1_EnableDTC_Request(S1_DTC_TX_HDLC); /* DTC�v������ */
	S1_HDLC_TxSelectIdle(TRUE);
	S1_HDLC_EnableTx(TRUE); /* ���M���� */
	
	S1_EnableRTS(TRUE); /* RTS��L���ɂ��� */
}

/**************************************************************************************************/
/**
	@brief		ECM���M�N���[�Y
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/21 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_CloseECM_Tx(void)
{
	S1_EnableRTS(FALSE); /* RTS�𖳌��ɂ��� */
	
	S1_HDLC_EnableTx(FALSE); /* ���M�֎~ */
	S1_HDLC_TxSelectIdle(FALSE);
	
	S1_EnableDTC_Request(S1_DTC_NONE);
	S1_ClearDTC_Request(); /* DTC�v���N���A */
	S1_DisableInterrupt(); /* S1���荞�݋֎~ */
	
	S1_HDLC_EnableTxDMA_Request(FALSE);
	S1_HDLC_EnableTxInterrupt(FALSE);
}

/**************************************************************************************************/
/**
	@brief		FPGA�o�[�W������������擾
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/09/09 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_GetFPGA_VersionString(
					UBYTE* pversion) /* �o�[�W����������(�o�� NULL�I�[ �\���ȑ傫�����m�ۂ��邱��) */
{
	UBYTE version;
	
	version = S1_GetFPGA_Version();
	
	CMN_UnsignedLongToHexASC_NULL(pversion, (UDWORD)version, 2, '0');
}





/**************************************************************************************************/
/**
	@brief		S1���\�t�g�E�F�A���Z�b�g����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/06/08 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SoftwareReset(void)
{
	S1_REG_Reset = S1_REG_BIT_RST;
}

/**************************************************************************************************/
/**
	@brief		S1���n�[�h�E�F�A���Z�b�g����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/06/08 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HardwareReset(void)
{
	S1_REG_Reset = S1_REG_BIT_HRST;
}

/**************************************************************************************************/
/**
	@brief		S1�����݂̎�ʂ𓾂�
	
	@li			
	@param		
	@return		�����ݎ�ʂ̃r�b�g�A�T�C��
	@note		
	@date		2005/07/01 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_GetInterruptKind(void)
{
	UBYTE kind;
	
	kind = S1_REG_IntReqest;
	
	return kind;
}

/**************************************************************************************************/
/**
	@brief		S1�����݂�L���ɂ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/01 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_EnableInterrupt(void)
{
	S1_REG_IntMask = 0;
}

/**************************************************************************************************/
/**
	@brief		S1�����݂𖳌��ɂ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/01 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_DisableInterrupt(void)
{
	S1_REG_IntMask = S1_REG_BIT_IMSK;
}

/**************************************************************************************************/
/**
	@brief		S1���荞�݂��N���A����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/13 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_ClearInterrupt(void)
{
	S1_REG_IntClear = S1_REG_BIT_ICLR;
}

/**************************************************************************************************/
/**
	@brief		DTC�v������
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/06/20 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_EnableDTC_Request(
					UBYTE type) /* ��� */
{
	switch (type) {
	case S1_DTC_NONE: /* �Ȃ� */
		S1_REG_DTC_Enable = 0;
		break;
	case S1_DTC_RX_HDLC: /* HDLC��M */
		S1_REG_DTC_Enable = S1_REG_BIT_DTCRX_HDLC;
		break;
	case S1_DTC_TX_HDLC: /* HDLC���M */
		S1_REG_DTC_Enable = S1_REG_BIT_DTCTX_HDLC;
		break;
	case S1_DTC_RX_SCI: /* SCI��M */
		S1_REG_DTC_Enable = S1_REG_BIT_DTCRX_SCI;
		break;
	case S1_DTC_TX_SCI: /* SCI���M */
		S1_REG_DTC_Enable = S1_REG_BIT_DTCTX_SCI;
		break;
	default:
		break;
	}
}

/**************************************************************************************************/
/**
	@brief		DTC�v���N���A
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/06/20 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_ClearDTC_Request(void)
{
	S1_REG_DTC_Clear = S1_REG_BIT_DTCCLR;
}

/**************************************************************************************************/
/**
	@brief		SCI/HDLC�؂�ւ�
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/06/20 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SetMode(
			BOOL bhdlc) /* TRUE:HDLC FALSE:SCI */
{
	if (bhdlc == TRUE) {
		S1_REG_DTC_Mode = S1_REG_BIT_MODE;
	}
	else {
		S1_REG_DTC_Mode = 0;
	}
}

/**************************************************************************************************/
/**
	@brief		RTS���Z�b�g����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/13 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SetRTS(
			UBYTE val) /* 0 or 1 */
{
	if (val == 0) {
		S1_REG_MDM_ControlCommand = (S1_REG_BIT_ENCDM | S1_REG_BIT_ENRSF);
	}
	else {
		S1_REG_MDM_ControlCommand = (S1_REG_BIT_ENCDM | S1_REG_BIT_ENRSF | S1_REG_BIT_RSF);
	}
#if 0
//	if (val == 0) {
//		S1_REG_MDM_ControlCommand = S1_REG_BIT_ENRSF;
//	}
//	else {
//		S1_REG_MDM_ControlCommand = (S1_REG_BIT_ENRSF | S1_REG_BIT_RSF);
//	}
#endif
}

#if 0
///**************************************************************************************************/
///**
//	@brief		RTS�ARLSD��L���ɂ���
//	
//	@li			
//	@param		
//	@return		�Ȃ�
//	@note		
//	@date		2005/07/13 �쐬
//	@author		�΋����a
//*/
///**************************************************************************************************/
//void S1_EnableRTS_RLSD(
//			BOOL benable) /* TRUE:�L�� FALSE:���� */
//{
//	if (benable == TRUE) {
//		S1_REG_MDM_ControlCommand = (S1_REG_BIT_ENCDM | S1_REG_BIT_ENRSF);
//	}
//	else {
//		S1_REG_MDM_ControlCommand = 0;
//	}
//}
#endif

/**************************************************************************************************/
/**
	@brief		RTS��L���ɂ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/13 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_EnableRTS(
			BOOL benable) /* TRUE:�L�� FALSE:���� */
{
	if (benable == TRUE) {
		S1_REG_MDM_ControlCommand = S1_REG_BIT_ENRSF;
	}
	else {
		S1_REG_MDM_ControlCommand = 0;
	}
}

/**************************************************************************************************/
/**
	@brief		RLSD��L���ɂ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/13 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_EnableRLSD(
			BOOL benable) /* TRUE:�L�� FALSE:���� */
{
	if (benable == TRUE) {
		S1_REG_MDM_ControlCommand = S1_REG_BIT_ENCDM;
	}
	else {
		S1_REG_MDM_ControlCommand = 0;
	}
}

/**************************************************************************************************/
/**
	@brief		RTS�̒l�𓾂�
	
	@li			
	@param		
	@return		0 or 1
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_GetRTS(void)
{
	UBYTE val;
	
	if (S1_REG_MDM_ControlStatus & S1_REG_BIT_STAT_RSF) {
		val = 1;
	}
	else {
		val = 0;
	}
	
	return val;
}

/**************************************************************************************************/
/**
	@brief		CTS�̒l�𓾂�
	
	@li			
	@param		
	@return		0 or 1
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_GetCTS(void)
{
	UBYTE val;
	
	if (S1_REG_MDM_ControlStatus & S1_REG_BIT_STAT_CSF) {
		val = 1;
	}
	else {
		val = 0;
	}
	
	return val;
}

/**************************************************************************************************/
/**
	@brief		RLSD�̒l�𓾂�
	
	@li			
	@param		
	@return		0 or 1
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_GetRLSD(void)
{
	UBYTE val;
	
	if (S1_REG_MDM_ControlStatus & S1_REG_BIT_STAT_CDF) {
		val = 1;
	}
	else {
		val = 0;
	}
	
	return val;
}

/**************************************************************************************************/
/**
	@brief		TCF���m��H�̃t���O���N���A����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/06/13 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_TCF_Clear(void)
{
	S1_REG_MDM_TCF_Clear = (S1_REG_BIT_TCFCLR1 | S1_REG_BIT_TCFCLR2);
}

/**************************************************************************************************/
/**
	@brief		TCF���m��H�̃t���O���擾����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/06/13 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_TCF_Detect(
			UBYTE* pflag1, /* �t���O1(�o��) */
			UBYTE* pflag2) /* �t���O2(�o��) */
{
	UBYTE reg;
	
	*pflag1 = 0;
	*pflag2 = 0;
	
	reg = S1_REG_MDM_TCF_Detect;
	
	if (reg & S1_REG_BIT_TCFDET1) {
		*pflag1 = 1;
	}
	if (reg & S1_REG_BIT_TCFDET2) {
		*pflag2 = 1;
	}
}

/**************************************************************************************************/
/**
	@brief		�X�N�����u���̗L��/�����Z�b�g
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/06/17 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SetScrambleAvailable(
					BOOL available) /* TRUE:�L���ɂ��� FALSE:�����ɂ��� */
{
	UBYTE val;
	
	val = S1_REG_MDM_ConfigureS1;
	
	if (available == TRUE) {
		S1_REG_MDM_ConfigureS1 = (val & ~S1_REG_BIT_SC1);
	}
	else {
		S1_REG_MDM_ConfigureS1 = (val | S1_REG_BIT_SC1);
	}
}

/**************************************************************************************************/
/**
	@brief		�X�N�����u���̗L��/�������擾
	
	@li			
	@param		
	@return		TRUE:  �L��
				FALSE: ����
	@note		
	@date		2005/08/23 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
BOOL S1_GetScrambleAvailable(void)
{
	UBYTE val;
	
	val = S1_REG_MDM_ConfigureS1;
	
	if (val & S1_REG_BIT_SC1) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

/**************************************************************************************************/
/**
	@brief		�X�N�����u���̓��샂�[�h(��p/����)�Z�b�g
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SetScrambleMode(
					BOOL bsenyo) /* TRUE:��p FALSE:�� */
{
	UBYTE val;
	
	val = S1_REG_MDM_ConfigureS1;
	
	if (bsenyo == TRUE) {
		S1_REG_MDM_ConfigureS1 = (val | S1_REG_BIT_SC2);
	}
	else {
		S1_REG_MDM_ConfigureS1 = (val & ~S1_REG_BIT_SC2);
	}
}

/**************************************************************************************************/
/**
	@brief		S1���o�C�p�X����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/11/17 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_BypassS1(
			BOOL bbypass) /* TRUE:�o�C�p�X���� FALSE:�o�C�p�X���Ȃ� */
{
	if (bbypass == TRUE) {
		S1_REG_MDM_BypassS1 |= S1_REG_BIT_BYPASS;
	}
	else {
		S1_REG_MDM_BypassS1 &= ~S1_REG_BIT_BYPASS;
	}
}

/**************************************************************************************************/
/**
	@brief		FPGA�̃o�[�W�������擾
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/09/09 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_GetFPGA_Version(void)
{
	UBYTE version;
	
	version = S1_REG_FPGA_Version;
	
	return version;
}

/**************************************************************************************************/
/**
	@brief		SCI ��M����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SCI_EnableRx(
				BOOL benable) /* TRUE:���� FALSE:�֎~ */
{
	if (benable == TRUE) {
		S1_REG_SCI_RxControl = S1_REG_BIT_SCI_RXEN;
	}
	else {
		S1_REG_SCI_RxControl = 0;
	}
}

/**************************************************************************************************/
/**
	@brief		SCI ��MFIFO�N���A
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SCI_ClearRxFIFO(void)
{
	S1_REG_SCI_RxControl = S1_REG_BIT_SCI_RX_STCLR;
}

/**************************************************************************************************/
/**
	@brief		SCI ��M�X�e�C�^�X�N���A
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SCI_ClearRxStatus(void)
{
	S1_REG_SCI_RxControl = S1_REG_BIT_SCI_RX_STCLR;
}

#if 0
///**************************************************************************************************/
///**
//	@brief		SCI OE(�I�[�o�[�����G���[)�N���A
//	
//	@li			
//	@param		
//	@return		�Ȃ�
//	@note		
//	@date		2005/07/14 �쐬
//	@author		�΋����a
//*/
///**************************************************************************************************/
//void S1_SCI_ClearRxOE(void)
//{
//	S1_REG_SCI_RxControl |= S1_REG_BIT_SCI_RX_STCLR;
//}
#endif

/**************************************************************************************************/
/**
	@brief		SCI ��M�X�e�C�^�X�擾
	
	@li			
	@param		
	@return		��M�X�e�C�^�X�̃r�b�g�A�T�C��
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_SCI_GetRxStatus(void)
{
	UBYTE status;
	
	status = S1_REG_SCI_RxStatus;
	
	return status;
}

#if 0
///**************************************************************************************************/
///**
//	@brief		SCI ��M�f�[�^�`�F�b�N
//	
//	@li			
//	@param		
//	@return		TRUE: ��M�f�[�^���� FALSE:��M�f�[�^�Ȃ�
//	@note		
//	@date		2005/07/14 �쐬
//	@author		�΋����a
//*/
///**************************************************************************************************/
//BOOL S1_SCI_CheckRxData(void)
//{
//	BOOL bret;
//	
//	if (S1_REG_SCI_RxStatus & S1_REG_BIT_SCI_RXRDY) {
//		bret = TRUE;
//	}
//	else {
//		bret = FALSE;
//	}
//	return bret;
//}
//
///**************************************************************************************************/
///**
//	@brief		SCI OE(�I�[�o�[�����G���[)�`�F�b�N
//	
//	@li			
//	@param		
//	@return		TRUE: OE���� FALSE:OE�Ȃ�
//	@note		
//	@date		2005/07/14 �쐬
//	@author		�΋����a
//*/
///**************************************************************************************************/
//BOOL S1_SCI_CheckRxOE(void)
//{
//	BOOL bret;
//	
//	if (S1_REG_SCI_RxStatus & S1_REG_BIT_SCI_OVE) {
//		bret = TRUE;
//	}
//	else {
//		bret = FALSE;
//	}
//	return bret;
//}
#endif

/**************************************************************************************************/
/**
	@brief		SCI ���M����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SCI_EnableTx(
				BOOL benable) /* TRUE:���� FALSE:�֎~ */
{
	if (benable == TRUE) {
		S1_REG_SCI_TxControl = S1_REG_BIT_SCI_TXEN;
	}
	else {
		S1_REG_SCI_TxControl = 0;
	}
}

/**************************************************************************************************/
/**
	@brief		SCI �A���_�[�����G���[�𔭐�������
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SCI_SetTxUNE(void)
{
	S1_REG_SCI_TxControl = S1_REG_BIT_SCI_UNEND;
}

/**************************************************************************************************/
/**
	@brief		SCI ���M�X�e�C�^�X�N���A
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SCI_ClearTxStatus(void)
{
	S1_REG_SCI_TxControl = S1_REG_BIT_SCI_TX_STCCLR;
}

/**************************************************************************************************/
/**
	@brief		SCI ���M�X�e�C�^�X�擾
	
	@li			
	@param		
	@return		���M�X�e�C�^�X�̃r�b�g�A�T�C��
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_SCI_GetTxStatus(void)
{
	UBYTE status;
	
	status = S1_REG_SCI_TxStatus;
	
	return status;
}

#if 0
//**************************************************************************************************/
///**
//	@brief		SCI ���M�f�[�^�`�F�b�N
//	
//	@li			
//	@param		
//	@return		TRUE: ���M�f�[�^���� FALSE:���M�f�[�^�Ȃ�
//	@note		
//	@date		2005/07/14 �쐬
//	@author		�΋����a
//*/
///**************************************************************************************************/
//BOOL S1_SCI_CheckTxData(void)
//{
//	BOOL bret;
//	
//	if (S1_REG_SCI_TxStatus & S1_REG_BIT_SCI_TXEND) {
//		bret = FALSE;
//	}
//	else {
//		bret = TRUE;
//	}
//	return bret;
//}
//
///**************************************************************************************************/
///**
//	@brief		SCI �A���_�[�����G���[�`�F�b�N
//	
//	@li			
//	@param		
//	@return		TRUE: �A���_�[�����G���[���� FALSE:�A���_�[�����G���[�Ȃ�
//	@note		
//	@date		2005/07/14 �쐬
//	@author		�΋����a
//*/
///**************************************************************************************************/
//BOOL S1_SCI_CheckTxUNE(void)
//{
//	BOOL bret;
//	
//	if (S1_REG_SCI_TxStatus & S1_REG_BIT_SCI_UNE) {
//		bret = TRUE;
//	}
//	else {
//		bret = FALSE;
//	}
//	return bret;
//}
//
///**************************************************************************************************/
///**
//	@brief		SCI ���M�f�[�^�������݉ۂ𓾂�
//	
//	@li			
//	@param		
//	@return		TRUE: �������݉� FALSE:�������ݕs��
//	@note		
//	@date		2005/07/14 �쐬
//	@author		�΋����a
//*/
///**************************************************************************************************/
//BOOL S1_SCI_CheckTxDataReady(void)
//{
//	BOOL bret;
//	
//	if (S1_REG_SCI_TxStatus & S1_REG_BIT_SCI_TXRDY) {
//		bret = TRUE;
//	}
//	else {
//		bret = FALSE;
//	}
//	return bret;
//}
#endif

/**************************************************************************************************/
/**
	@brief		SCI ���荞�݁ADTC�̏�����ݒ肷��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_SCI_SetIntDTC_Enabled(
						UBYTE bits) /* �L���ɂ�������̃r�b�g�A�T�C�� */
{
	S1_REG_SCI_IntDTC_Enable = bits;
}

/**************************************************************************************************/
/**
	@brief		SCI ���荞�ݗv���𓾂�
	
	@li			
	@param		
	@return		���荞�ݗv���̃r�b�g�A�T�C��
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_SCI_GetIntFactor(void)
{
	UBYTE ret;
	
	ret = S1_REG_SCI_IntRequest;
	
	return ret;
}

/**************************************************************************************************/
/**
	@brief		HDLC �����������̏�����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_InitializeCRC(void)
{
	S1_REG_HDLC_SelectCRC = 0x1C; /* CCITT(x^16 + x^12 + x^5 + 1) */
}

/**************************************************************************************************/
/**
	@brief		HDLC �]�����[�h�̏�����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/14 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_InitializeTransMode(void)
{
	S1_REG_HDLC_TransMode = 0;
}

/**************************************************************************************************/
/**
	@brief		HDLC ��M�X�e�[�^�X�𓾂�
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_HDLC_GetRxStatus(void)
{
	UBYTE status;
	
	status = S1_REG_HDLC_RxStatus0;
	
	return status;
}

/**************************************************************************************************/
/**
	@brief		HDLC �ŏI��M�f�[�^�̒[���r�b�g���𓾂�
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_HDLC_GetRxRemainedBitNum(void)
{
	UBYTE num;
	
	num = S1_REG_HDLC_RxStatus1;
	
	return num;
}

/**************************************************************************************************/
/**
	@brief		HDLC ��M����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_EnableRx(
				BOOL benable) /* TRUE:���� FALSE:�֎~ */
{
	if (benable == TRUE) {
		S1_REG_HDLC_RxControl |= S1_REG_BIT_HDLC_RXE;
	}
	else {
		S1_REG_HDLC_RxControl &= ~S1_REG_BIT_HDLC_RXE;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC ��M�X�e�C�^�X�N���A
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_ClearRxStatus(void)
{
	S1_REG_HDLC_RxControl |= S1_REG_BIT_HDLC_STC;
}

/**************************************************************************************************/
/**
	@brief		HDLC ��M ���荞�݁ADTC�̏�����ݒ肷��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_SetRxIntDTC_Enabled(
						UBYTE bits) /* �L���ɂ�������̃r�b�g�A�T�C�� */
{
	S1_REG_HDLC_RxIntPermit = bits;
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M�X�e�[�^�X�𓾂�
	
	@li			
	@param		
	@return		���M�X�e�[�^�X�̃r�b�g�A�T�C��
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_HDLC_GetTxStatus(void)
{
	UBYTE status;
	
	status = S1_REG_HDLC_TxStatus;
	
	return status;
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M�X�e�[�^�X���N���A����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_ClearTxStatus(
					UBYTE status) /* �N���A����X�e�C�^�X�̃r�b�g�A�T�C�� */
{
	S1_REG_HDLC_TxStatus &= (~status);
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_EnableTx(
				BOOL benable) /* TRUE:���� FALSE:�֎~ */
{
	if (benable == TRUE) {
		S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_TXE;
	}
	else {
		S1_REG_HDLC_TxControl &= ~S1_REG_BIT_HDLC_TXE;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M �o�̓��x���������I��"H"�ɂ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_TxSendHighLevel(
						BOOL benable) /* TRUE:����"H" FALSE:�߂� */
{
	if (benable == TRUE) {
		S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_SH;
	}
	else {
		S1_REG_HDLC_TxControl &= ~S1_REG_BIT_HDLC_SH;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M �o�̓��x���������I��"L"�ɂ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_TxSendBreak(
					BOOL benable) /* TRUE:����"L" FALSE:�߂� */
{
	if (benable == TRUE) {
		S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_SB;
	}
	else {
		S1_REG_HDLC_TxControl &= ~S1_REG_BIT_HDLC_SB;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M ???
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_TxSelectIdle(
					BOOL benable)
{
	if (benable == TRUE) {
		S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_IDLS;
	}
	else {
		S1_REG_HDLC_TxControl &= ~S1_REG_BIT_HDLC_IDLS;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M�������Z�b�g����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_RestTx(void)
{
	S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_TXRST;
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M �A�{�[�g�𑗐M����
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_TxSendAbort(void)
{
	S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_SA;
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M �ŏI�t���[�����w��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_TxLast(
				UBYTE val) /* 0 or 1 */
{
	if (val == 1) {
		S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_TXLAST;
	}
	else {
		S1_REG_HDLC_TxControl &= ~S1_REG_BIT_HDLC_TXLAST;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M ���荞�݁ADTC�̏�����ݒ肷��
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_SetTxIntDTC_Enabled(
						UBYTE bits) /* �L���ɂ�������̃r�b�g�A�T�C�� */
{
	S1_REG_HDLC_TxIntPermit = bits;
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M���[�h���W�X�^������
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_InitializeTxMode(void)
{
	S1_REG_HDLC_TxMode = S1_REG_BIT_HDLC_TXUEND;
}

/**************************************************************************************************/
/**
	@brief		HDLC �����݁ADMA�v���̏�Ԃ��擾����
	
	@li			
	@param		
	@return		�e��v���̃r�b�g�A�T�C��
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
UBYTE S1_HDLC_GetRequestStatus(void)
{
	UBYTE status;
	
	status = S1_REG_HDLC_Request;
	
	return status;
}

/**************************************************************************************************/
/**
	@brief		HDLC ��M���荞�݂�L���ɂ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_EnableRxInterrupt(
					BOOL benable) /* TRUE:���� FALSE:�֎~ */
{
	if (benable == TRUE) {
		S1_REG_HDLC_Mask &= ~S1_REG_BIT_HDLC_MRX;
	}
	else {
		S1_REG_HDLC_Mask |= S1_REG_BIT_HDLC_MRX;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC ��MDMA�v����L���ɂ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_EnableRxDMA_Request(
							BOOL benable) /* TRUE:���� FALSE:�֎~ */
{
	if (benable == TRUE) {
		S1_REG_HDLC_Mask &= ~S1_REG_BIT_HDLC_MRXDRQ;
	}
	else {
		S1_REG_HDLC_Mask |= S1_REG_BIT_HDLC_MRXDRQ;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC ���M���荞�݂�L���ɂ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_EnableTxInterrupt(
							BOOL benable) /* TRUE:���� FALSE:�֎~ */
{
	if (benable == TRUE) {
		S1_REG_HDLC_Mask &= ~S1_REG_BIT_HDLC_MTX;
	}
	else {
		S1_REG_HDLC_Mask |= S1_REG_BIT_HDLC_MTX;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC ���MDMA�v����L���ɂ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/19 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_HDLC_EnableTxDMA_Request(
							BOOL benable) /* TRUE:���� FALSE:�֎~ */
{
	if (benable == TRUE) {
		S1_REG_HDLC_Mask &= ~S1_REG_BIT_HDLC_MTXDRQ;
	}
	else {
		S1_REG_HDLC_Mask |= S1_REG_BIT_HDLC_MTXDRQ;
	}
}

