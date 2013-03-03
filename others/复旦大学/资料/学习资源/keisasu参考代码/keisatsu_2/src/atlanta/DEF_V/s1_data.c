/**********************************************************************************************************************
	@(#)$Id: s1_data.c,v 1.7 2005/11/17 01:42:02 mi93007 Exp $
	Create        : 2005/06/13
	Author        : �΋����a
	Description   : S1�֌W�f�[�^
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#include "\src\atlanta\define\product.h"

#pragma section S1_REG

volatile UBYTE S1_REG_Reset;				/* 000 ���Z�b�g */
volatile UBYTE S1_REG_IntReqest;			/* 001 ���荞�݃��N�G�X�g */
volatile UBYTE S1_REG_IntMask;				/* 002 ���荞�݃}�X�N */
volatile UBYTE S1_REG_IntClear;				/* 003 ���荞�݃N���A */
volatile UBYTE S1_REG_DTC_Enable;			/* 004 DTC�C�l�[�u�� */
volatile UBYTE S1_REG_DTC_Clear;			/* 005 DTC�N���A */
volatile UBYTE S1_REG_DTC_Mode;				/* 006 ���[�h�؊��� */
volatile UBYTE S1_REG_007;					/* 007 �� */
volatile UBYTE S1_REG_MDM_ControlCommand;	/* 008 (���f��)����R�}���h */
volatile UBYTE S1_REG_MDM_ControlStatus;	/* 009 (���f��)����X�e�[�^�X */
volatile UBYTE S1_REG_00A;					/* 00A (Reserved) */
volatile UBYTE S1_REG_MDM_TCF_Clear;		/* 00B (���f��)TCF�N���A */
volatile UBYTE S1_REG_MDM_TCF_Detect;		/* 00C (���f��)TCF���o */
volatile UBYTE S1_REG_MDM_ConfigureS1;		/* 00D (���f��)S1�ݒ� */
volatile UBYTE S1_REG_MDM_BypassS1;			/* 00E (���f��)S1�o�C�p�X */
volatile UBYTE S1_REG_00F;					/* 00F �� */
volatile UBYTE S1_REG_SCI_Data;				/* 010 (SCI)�V���A���f�[�^ */
volatile UBYTE S1_REG_FPGA_Version;			/* 011 (SCI)FPGA�o�[�W���� */
volatile UBYTE S1_REG_SCI_RxControl;		/* 012 (SCI)��M���� */
volatile UBYTE S1_REG_SCI_RxStatus;			/* 013 (SCI)��M�X�e�[�^�X */
volatile UBYTE S1_REG_SCI_TxControl;		/* 014 (SCI)���M���� */
volatile UBYTE S1_REG_SCI_TxStatus;			/* 015 (SCI)���M�X�e�[�^�X */
volatile UBYTE S1_REG_SCI_IntDTC_Enable;	/* 016 (SCI)������&DTC�C�l�[�u�� */
volatile UBYTE S1_REG_SCI_IntRequest;		/* 017 (SCI)�����ݗv�� */
volatile UBYTE S1_REG_018;					/* 018 �� */
volatile UBYTE S1_REG_019;					/* 019 �� */
volatile UBYTE S1_REG_01A;					/* 01A �� */
volatile UBYTE S1_REG_01B;					/* 01B �� */
volatile UBYTE S1_REG_01C;					/* 01C �� */
volatile UBYTE S1_REG_01D;					/* 01D �� */
volatile UBYTE S1_REG_01E;					/* 01E �� */
volatile UBYTE S1_REG_01F;					/* 01F �� */
volatile UBYTE S1_REG_HDLC_SelectCRC;		/* 020 (HDLC)CRC�I�� */
volatile UBYTE S1_REG_HDLC_TransMode;		/* 021 (HDLC)�]�����[�h */
volatile UBYTE S1_REG_HDLC_RxStatus0;		/* 022 (HDLC)��M�X�e�[�^�X0 */
volatile UBYTE S1_REG_HDLC_RxStatus1;		/* 023 (HDLC)��M�X�e�[�^�X1 */
volatile UBYTE S1_REG_HDLC_RxControl;		/* 024 (HDLC)��M���� */
volatile UBYTE S1_REG_HDLC_RxIntPermit;		/* 025 (HDLC)��M�����݋��� */
volatile UBYTE S1_REG_HDLC_TxStatus;		/* 026 (HDLC)���M�X�e�[�^�X */
volatile UBYTE S1_REG_027;					/* 027 (Reserved) */
volatile UBYTE S1_REG_HDLC_TxControl;		/* 028 (HDLC)���M���� */
volatile UBYTE S1_REG_HDLC_TxIntPermit;		/* 029 (HDLC)���M�����݋��� */
volatile UBYTE S1_REG_HDLC_Data;			/* 02A (HDLC)�V���A���f�[�^ */
volatile UBYTE S1_REG_HDLC_TxMode;			/* 02B (HDLC)���M���[�h */
volatile UBYTE S1_REG_HDLC_Request;			/* 02C (HDLC)���N�G�X�g */
volatile UBYTE S1_REG_HDLC_Mask;			/* 02D (HDLC)�}�X�N */

#pragma section

/*************************************************
	�^�X�NID
*************************************************/
UWORD tskno_S1_ReceiveTCF_Data;

