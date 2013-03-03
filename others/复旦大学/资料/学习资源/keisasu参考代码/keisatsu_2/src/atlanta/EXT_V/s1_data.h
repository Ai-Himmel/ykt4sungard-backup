/**********************************************************************************************************************
	@(#)$Id: s1_data.h,v 1.6 2005/11/17 01:42:02 mi93007 Exp $
	Create        : 2005/06/13
	Author        : �΋����a
	Description   : S1�֌W�f�[�^
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#include "\src\atlanta\define\product.h"

extern UBYTE S1_REG_Reset;				/* 000 ���Z�b�g */
extern UBYTE S1_REG_IntReqest;			/* 001 ���荞�݃��N�G�X�g */
extern UBYTE S1_REG_IntMask;			/* 002 ���荞�݃}�X�N */
extern UBYTE S1_REG_IntClear;			/* 003 ���荞�݃N���A */
extern UBYTE S1_REG_DTC_Enable;			/* 004 DTC�C�l�[�u�� */
extern UBYTE S1_REG_DTC_Clear;			/* 005 DTC�N���A */
extern UBYTE S1_REG_DTC_Mode;			/* 006 ���[�h�؊��� */
extern UBYTE S1_REG_007;				/* 007 �� */
extern UBYTE S1_REG_MDM_ControlCommand;	/* 008 (���f��)����R�}���h */
extern UBYTE S1_REG_MDM_ControlStatus;	/* 009 (���f��)����X�e�[�^�X */
extern UBYTE S1_REG_00A;				/* 00A (Reserved) */
extern UBYTE S1_REG_MDM_TCF_Clear;		/* 00B (���f��)TCF�N���A */
extern UBYTE S1_REG_MDM_TCF_Detect;		/* 00C (���f��)TCF���o */
extern UBYTE S1_REG_MDM_ConfigureS1;	/* 00D (���f��)S1�ݒ� */
extern UBYTE S1_REG_MDM_BypassS1;		/* 00E (���f��)S1�o�C�p�X */
extern UBYTE S1_REG_00F;				/* 00F �� */
extern UBYTE S1_REG_SCI_Data;			/* 010 (SCI)�V���A���f�[�^ */
extern UBYTE S1_REG_FPGA_Version;		/* 011 (SCI)FPGA�o�[�W���� */
extern UBYTE S1_REG_SCI_RxControl;		/* 012 (SCI)��M���� */
extern UBYTE S1_REG_SCI_RxStatus;		/* 013 (SCI)��M�X�e�[�^�X */
extern UBYTE S1_REG_SCI_TxControl;		/* 014 (SCI)���M���� */
extern UBYTE S1_REG_SCI_TxStatus;		/* 015 (SCI)���M�X�e�[�^�X */
extern UBYTE S1_REG_SCI_IntDTC_Enable;	/* 016 (SCI)������&DTC�C�l�[�u�� */
extern UBYTE S1_REG_SCI_IntRequest;		/* 017 (Reserved) */
extern UBYTE S1_REG_018;				/* 018 �� */
extern UBYTE S1_REG_019;				/* 019 �� */
extern UBYTE S1_REG_01A;				/* 01A �� */
extern UBYTE S1_REG_01B;				/* 01B �� */
extern UBYTE S1_REG_01C;				/* 01C �� */
extern UBYTE S1_REG_01D;				/* 01D �� */
extern UBYTE S1_REG_01E;				/* 01E �� */
extern UBYTE S1_REG_01F;				/* 01F �� */
extern UBYTE S1_REG_HDLC_SelectCRC;		/* 020 (HDLC)CRC�I�� */
extern UBYTE S1_REG_HDLC_TransMode;		/* 021 (HDLC)�]�����[�h */
extern UBYTE S1_REG_HDLC_RxStatus0;		/* 022 (HDLC)��M�X�e�[�^�X0 */
extern UBYTE S1_REG_HDLC_RxStatus1;		/* 023 (HDLC)��M�X�e�[�^�X1 */
extern UBYTE S1_REG_HDLC_RxControl;		/* 024 (HDLC)��M���� */
extern UBYTE S1_REG_HDLC_RxIntPermit;	/* 025 (HDLC)��M�����݋��� */
extern UBYTE S1_REG_HDLC_TxStatus;		/* 026 (HDLC)���M�X�e�[�^�X */
extern UBYTE S1_REG_027;				/* 027 (Reserved) */
extern UBYTE S1_REG_HDLC_TxControl;		/* 028 (HDLC)���M���� */
extern UBYTE S1_REG_HDLC_TxIntPermit;	/* 029 (HDLC)���M�����݋��� */
extern UBYTE S1_REG_HDLC_Data;			/* 02A (HDLC)�V���A���f�[�^ */
extern UBYTE S1_REG_HDLC_TxMode;		/* 02B (HDLC)���M���[�h */
extern UBYTE S1_REG_HDLC_Request;		/* 02C (HDLC)���N�G�X�g */
extern UBYTE S1_REG_HDLC_Mask;			/* 02D (HDLC)�}�X�N */

/*************************************************
	�^�X�NID
*************************************************/
extern UWORD tskno_S1_ReceiveTCF_Data;

