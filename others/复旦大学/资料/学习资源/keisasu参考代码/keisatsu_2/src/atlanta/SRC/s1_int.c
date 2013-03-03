/**********************************************************************************************************************
	@(#)$Id: s1_int.c,v 1.5 2005/11/22 02:25:01 mi93007 Exp $
	Create        : 2005/07/01
	Author        : �΋����a
	Description   : S1�����ݏ���
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\s1_pro.h"
#include "\src\atlanta\define\s1_def.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\mntsw_c.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"

/**************************************************************************************************/
/**
	@brief		S1�����ݏ���
	
	@li			
	@param		
	@return		�Ȃ�
	@note		
	@date		2005/07/01 �쐬
	@author		�΋����a
*/
/**************************************************************************************************/
void S1_Interrupt(void)
{
	UBYTE int_kind;
	UBYTE int_factor;
	UBYTE status;
	
	UWORD rtn;
	
	rtn = 0;
	
	int_kind = S1_GetInterruptKind(); /* �����ݎ�ʂ𓾂� */
	
	switch (ModemBlock.Mode) { /* ��M���[�h */
	case MODE_RX_G3:
		if (!(int_kind & S1_REG_BIT_IRRX_SCI)) { /* SCI��M���̊��荞�݂łȂ��ꍇ */
			break;
		}
		int_factor = S1_SCI_GetIntFactor(); /* �����ݗv���𓾂� */
		status = S1_SCI_GetRxStatus(); /* ��M�X�e�[�^�X�𓾂� */
		if (int_factor & S1_REG_BIT_SCI_OVERQ) { /* �I�[�o�[�����G���[�̏ꍇ */
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN; /* �����e�i���X�X�C�b�`�ɒʒm */
		}
		S1_SCI_ClearRxStatus(); /* ��M�X�e�C�^�X�N���A */
		break;
	case MODE_TX_G3:
		if (!(int_kind & S1_REG_BIT_IRTX_SCI)) { /* SCI���M���̊��荞�݂łȂ��ꍇ */
			break;
		}
		int_factor = S1_SCI_GetIntFactor(); /* �����ݗv���𓾂� */
		status = S1_SCI_GetTxStatus(); /* ��M�X�e�[�^�X�𓾂� */
		if (int_factor & S1_REG_BIT_SCI_UNERQ) { /* �A���_�[�����G���[�̏ꍇ */
			
			
			
		}
		if (int_factor & S1_REG_BIT_SCI_TXENDRQ) { /* TxEND(���M���ׂ��f�[�^���Ȃ�)�̏ꍇ */
			
			
			
		}
		S1_SCI_ClearTxStatus(); /* ���M�X�e�C�^�X�N���A */
		break;
	case MODE_RX_ECM:
		if (!(int_kind & S1_REG_BIT_IRRX_HDLC)) { /* HDLC��M���̊��荞�݂łȂ��ꍇ */
			break;
		}
		status = S1_HDLC_GetRxStatus(); /* ��M�X�e�[�^�X�𓾂� */
		
		if (status & S1_REG_BIT_HDLC_EOF) { /* �t���[���I�� */
			if ((MDM_DmaStart != MDM_DMA_MASK) && !(status & S1_REG_BIT_HDLC_CRC)) {	/**	�e�b�r�v�Z���ʂn�j�̎�	*//* For Debug By O.K Feb.16,1996 */
				/* �����ɗ���܂łɎ��̃t���[���̐擪�f�[�^����M�����Ƃ��̏�����ǉ��B Changed by H.Kubo 1999/01/26 */
				/* DMA(DTC) �͂����Ŏ~�߂Ȃ��Ƃ����Ȃ��B�J�E���^��ǂ�ł���}�X�N����܂ł̊ԂɎ��� DREQ ��������
				** �I�����荞�݂������邱�Ƃ�����B
				** by H.Kubo 1999/01/26 */
				DMA_RequestMask(DMA_CH_RX);
				GetRxSize(ModemControl.WritePoint);	/**	�t���[���T�C�Y�擾	*/
				ModemControl.UsedCount++;
				ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	�t���[����M��ʒʒm����	*/
					/* �t���[���Ō�̃t���O����M���Ă��炱���ɗ���܂ł̊ԂɎ��̃t���[���̐擪����M���Ă�����A
					** ���̃t���[���̐擪�͎��̃��f���o�b�t�@�ɃR�s�[���Ďc��̃f�[�^�̎�M���n�߂܂��B
					** �����łȂ���΁A���̃t���[���͕��ʂɎ��̃��f���o�b�t�@�̐擪�����M���n�߂܂��B
					** by H.Kubo 1999/01/26
					*/
				if ((MDM_RxSize[ModemControl.WritePoint] == (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1))
					&& (MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] == 0xff)) {
					/* ���̃A�h���X�t�B�[���h�̃f�[�^�������ɂ���ꍇ */
					MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] = 0x0;
					MDM_RxSize[ModemControl.WritePoint] -= 1; /* ���̃��f���o�b�t�@�Ɉڂ��������������Z���܂��B */
					NextMdmBufWritePointSetExtRom();
					MDM_ModemBuffer[ModemControl.WritePoint][0] = 0xff;
					SelectDreqDirection(RX_DMA);
					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][1]);
				}
				else {
					NextMdmBufWritePointSetExtRom();
					SelectDreqDirection(RX_DMA);
					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
				}
				MDM_DmaStart = MDM_DMA_GO;
			}
			else {
				DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
				SelectDreqDirection(RX_DMA);
				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);/**  By O.K Jan.K Jan.23,1996 **/
				MDM_DmaStart = MDM_DMA_GO;
			}
		}
		else if (status & (S1_REG_BIT_HDLC_CRC | S1_REG_BIT_HDLC_OER | S1_REG_BIT_HDLC_SFER | S1_REG_BIT_HDLC_ADET)) {
			DMA_RequestMask(DMA_CH_RX);
			SelectDreqDirection(RX_DMA);
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
			/* DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize + 4), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]); */
			MDM_DmaStart = MDM_DMA_GO;
			if (status & S1_REG_BIT_HDLC_OER) {
				SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN;
			}
		}
		S1_HDLC_ClearRxStatus(); /* ��M�X�e�[�^�X�N���A */
		
		
		
		if ((MDM_DmaStart == MDM_DMA_GO) && (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIE)) {
			MDM_SetIO(POS_RDBIE,OFF);
			MDM_DmaStart = MDM_DMA_CONTINUE;
		}
		
		
		
		break;
	case MODE_TX_ECM:
		if (!(int_kind & S1_REG_BIT_IRTX_HDLC)) { /* HDLC���M���̊��荞�݂łȂ��ꍇ */
			break;
		}
		
		status = S1_HDLC_GetTxStatus();
		
#if 0
		if (status & S1_REG_BIT_HDLC_TXEND) {
			if (ModemControl.Status & STAT_ALSENT) {			/**	���o�f�[�^���Z�b�g�ς݂̎�	*/
				ModemControl.Status &= (~STAT_ALSENT);		/**	�e�b�r���荞�ݑ҂�����	*/
				ModemInterruptFlag = 1;						/**	���f�����荞�ݔ����t���O�Z�b�g	*/
				MDM_SetIO(POS_TEOF,OFF);
				rtn |= MDM_EVT_TX_FCS_COMPLETE_BIT;		/* V21ch2 �t���O(7E) ���o */
			}
			S1_HDLC_ClearTxStatus(S1_REG_BIT_HDLC_TXEND);
		}
		
		
		
		if ((MDM_DmaStart == MDM_DMA_GO) && (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIE)) {
			MDM_SetIO(POS_RDBIE,OFF);
			MDM_DmaStart = MDM_DMA_CONTINUE;
		}
		
		
		
#endif
		break;
	case 0: /* ���f���N���[�Y������̊�����(�Ȃ������邱�Ƃ�����) */
		if (int_kind & S1_REG_BIT_IRRX_HDLC) { /* HDLC��M���̊��荞�� */
			status = S1_HDLC_GetRxStatus(); /* ��M�X�e�[�^�X�𓾂� */
			S1_HDLC_ClearRxStatus(); /* ��M�X�e�[�^�X�N���A */
		}
		if (int_kind & S1_REG_BIT_IRTX_HDLC) { /* HDLC���M���̊��荞�� */
			status = S1_HDLC_GetTxStatus(); /* ���M�X�e�[�^�X�𓾂� */
			S1_HDLC_ClearTxStatus(status); /* ���M�X�e�[�^�X�N���A */
		}
		if (int_kind & S1_REG_BIT_IRRX_SCI) { /* SCI��M���̊��荞�� */
			status = S1_SCI_GetRxStatus(); /* ��M�X�e�[�^�X�𓾂� */
			S1_SCI_ClearRxStatus(); /* ��M�X�e�[�^�X�N���A */
		}
		if (int_kind & S1_REG_BIT_IRTX_SCI) { /* SCI���M���̊��荞�� */
			status = S1_SCI_GetTxStatus(); /* ���M�X�e�[�^�X�𓾂� */
			S1_SCI_ClearTxStatus(); /* ���M�X�e�[�^�X�N���A */
		}
		break;
	default:
		break;
	}
	
	S1_ClearInterrupt(); /* �����݃N���A */
	
	if (rtn != 0 ) {
		if ( (rtn & MDM_EVT_ATV25_DETECT_BIT) != 0 ) {
			idet_evt(EVT_MDM_ATV25);
		}
		if ( (rtn & MDM_EVT_MDM_PNSUC_BIT) != 0 ) {
			idet_evt(EVT_MDM_PNSUC);
		}
		if ( (rtn & MDM_EVT_TX_FCS_COMPLETE_BIT) != 0 ) {
			idet_evt(EVT_TX_FCS_COMPLETE);
		}
		if ( (rtn & MDM_EVT_RX_FLG_DETECT_BIT) != 0 ) {
			idet_evt(EVT_RX_FLG_DETECT);
		}
		if ( (rtn & MDM_EVT_RX_RDBF_BIT) != 0 ) {
			idet_evt(EVT_MDM_RX_NEW_DATA);
		}
	}
}



