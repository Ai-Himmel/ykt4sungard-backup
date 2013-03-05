/**********************************************************************************************************************
	@(#)$Id: s1_def.h,v 1.9 2005/11/17 01:42:02 mi93007 Exp $
	Create        : 2005/06/08
	Author        : �΋����a
	Description   : S1�֌W��`
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#ifndef s1_def_h
	#define s1_def_h

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\fcm_def.h"

/*********************************************************************
	���W�X�^�r�b�g�A�T�C��
*********************************************************************/
/* 000 ���Z�b�g */
#define S1_REG_BIT_RST						0x01	/* RST �\�t�g�E�F�A���Z�b�g */
#define S1_REG_BIT_HRST						0x02	/* HRST �n�[�h�E�F�A���Z�b�g */

/* 001 �����݃��N�G�X�g */
#define S1_REG_BIT_IRRX_HDLC				0x01	/* HDLC���Ŏ�M������ */
#define S1_REG_BIT_IRTX_HDLC				0x02	/* HDLC���ő��M������ */
#define S1_REG_BIT_IRRX_SCI					0x04	/* SCI���Ŏ�M������ */
#define S1_REG_BIT_IRTX_SCI					0x08	/* SCI���ő��M������ */
#define S1_REG_BIT_IRQ						0x80	/* �����ݒ[�q�̏�� */

/* 002 �����ݗv���}�X�N */
#define S1_REG_BIT_IMSK						0x80	/* �����ݗv���}�X�N */

/* 003 �����ݗv���N���A */
#define S1_REG_BIT_ICLR						0x80	/* �����ݗv���N���A */

/* 004 DTC�C�l�[�u�� */
#define S1_REG_BIT_DTCRX_HDLC				0x01	/* HDLC����M�ɂ��DTC�v������ */
#define S1_REG_BIT_DTCTX_HDLC				0x02	/* HDLC�����M�ɂ��DTC�v������ */
#define S1_REG_BIT_DTCRX_SCI				0x04	/* SCI����M�ɂ��DTC�v������ */
#define S1_REG_BIT_DTCTX_SCI				0x08	/* SCI�����M�ɂ��DTC�v������ */

/* 005 DTC�N���A */
#define S1_REG_BIT_DTCCLR					0x80	/* DTC�v������ */

/* 006 ���[�h�I�� */
#define S1_REG_BIT_MODE						0x01	/* ���[�h */

/* 008 ����R�}���h */
#define S1_REG_BIT_RSF						0x01	/* RSF */
#define S1_REG_BIT_ENRSF					0x10	/* ENRSF */
#define S1_REG_BIT_ENCDM					0x20	/* ENCDM */

/* 009 ����X�e�[�^�X */
#define S1_REG_BIT_STAT_RSF					0x01	/* RSF�̏�� */
#define S1_REG_BIT_STAT_CSF					0x02	/* CSF�̏�� */
#define S1_REG_BIT_STAT_CDF					0x04	/* CDF�̏�� */

/* 00B TCF�N���A */
#define S1_REG_BIT_TCFCLR1					0x01	/* TCF�N���A1 */
#define S1_REG_BIT_TCFCLR2					0x02	/* TCF�N���A2 */

/* 00C TCF���o */
#define S1_REG_BIT_TCFDET1					0x01	/* TCF���o1 */
#define S1_REG_BIT_TCFDET2					0x02	/* TCF���o2 */

/* 00D S1�ݒ� */
#define S1_REG_BIT_SC1						0x01	/* 0:�X�N�����u��ON 1:�X�N�����u��OFF */
#define S1_REG_BIT_SC2						0x02	/* 0:���ʃ��[�h 1:��p���[�h */

/* 00E S1�o�C�p�X */
#define S1_REG_BIT_BYPASS					0x01	/* S1���o�C�p�X���� */

/* 012 ��M���� */
#define S1_REG_BIT_SCI_RX_STCLR				0x01	/* ��M�X�e�C�^�X�N���A */
#define S1_REG_BIT_SCI_RX_FIFOCLR			0x04	/* ��MFIFO�N���A */
#define S1_REG_BIT_SCI_RXEN					0x80	/* ��M���� */

/* 013 ��M�X�e�[�^�X */
#define S1_REG_BIT_SCI_RXRDY				0x01	/* ��M�f�[�^���� */
#define S1_REG_BIT_SCI_OVE					0x02	/* �I�[�o�[�����G���[ */

/* 014 ���M���� */
#define S1_REG_BIT_SCI_TX_STCCLR			0x01	/* TxEND, UNE�N���A */
#define S1_REG_BIT_SCI_UNEND				0x02	/* �A���_�[�������� */
#define S1_REG_BIT_SCI_TXEN					0x80	/* ���M���� */

/* 015 ���M�X�e�[�^�X */
#define S1_REG_BIT_SCI_TXRDY				0x01	/* ���M�f�[�^�������݉� */
#define S1_REG_BIT_SCI_UNE					0x02	/* �A���_�[�����G���[���� */
#define S1_REG_BIT_SCI_TXEND				0x04	/* ���M�f�[�^�Ȃ� */

/* 016 �����݁ADTC�C�l�[�u�� */
#define S1_REG_BIT_SCI_RXRDYIE				0x01	/* RxRDY�ɂ�銄���݋��� */
#define S1_REG_BIT_SCI_OVEIE				0x02	/* OVE�ɂ�銄���݋��� */
#define S1_REG_BIT_SCI_RXRDYDTCE			0x08	/* RxRDY�ɂ��DTC���� */
#define S1_REG_BIT_SCI_TXRDYIE				0x10	/* TxRDY�ɂ�銄���݋��� */
#define S1_REG_BIT_SCI_UNEIE				0x20	/* UNE�ɂ�銄���݋��� */
#define S1_REG_BIT_SCI_TXENDIE				0x40	/* TxEND�ɂ�銄���݋��� */
#define S1_REG_BIT_SCI_TXRDYDTCE			0x80	/* TxRDY�ɂ��DTC���� */

/* 017 �����ݗv�� */
#define S1_REG_BIT_SCI_RXRDYRQ				0x01	/* RxRDY�ɂ�銄���ݗv�� */
#define S1_REG_BIT_SCI_OVERQ				0x02	/* OVE�ɂ�銄���ݗv�� */
#define S1_REG_BIT_SCI_TXRDYRQ				0x10	/* TxRDY�ɂ�銄���ݗv�� */
#define S1_REG_BIT_SCI_UNERQ				0x20	/* UNE�ɂ�銄���ݗv�� */
#define S1_REG_BIT_SCI_TXENDRQ				0x40	/* TxEND�ɂ�銄���ݗv�� */



/* 022 ��M�X�e�[�^�X���W�X�^0(RxSR0) */
#define S1_REG_BIT_HDLC_RXRDY				0x01
#define S1_REG_BIT_HDLC_DIDL				0x02
#define S1_REG_BIT_HDLC_RXIDL				0x04
#define S1_REG_BIT_HDLC_CRC					0x08
#define S1_REG_BIT_HDLC_OER					0x10
#define S1_REG_BIT_HDLC_SFER				0x20
#define S1_REG_BIT_HDLC_EOF					0x40
#define S1_REG_BIT_HDLC_ADET				0x80

/* 023 ��M�X�e�[�^�X���W�X�^1(RxSR1) */
#define S1_REG_BIT_HDLC_RBL0				0x01
#define S1_REG_BIT_HDLC_RBL1				0x02
#define S1_REG_BIT_HDLC_RBL2				0x04

/* 024 ��M���䃌�W�X�^(RxCR) */
#define S1_REG_BIT_HDLC_STC					0x01
#define S1_REG_BIT_HDLC_RXE					0x80

/* 025 ��M�����݋����W�X�^(RxIER) */
#define S1_REG_BIT_HDLC_RXRDYIE				0x01
#define S1_REG_BIT_HDLC_DIDLIE				0x02
#define S1_REG_BIT_HDLC_ERRIE				0x04
#define S1_REG_BIT_HDLC_ENDIE				0x08
#define S1_REG_BIT_HDLC_RXDI				0x80

/* 026 ���M�X�e�[�^�X���W�X�^(TxSR) */
#define S1_REG_BIT_HDLC_TXRDY				0x01
#define S1_REG_BIT_HDLC_TXU					0x02
#define S1_REG_BIT_HDLC_TXEMP				0x04
#define S1_REG_BIT_HDLC_TXEND				0x08

/* 028 ���M���䃌�W�X�^(TxCR) */
#define S1_REG_BIT_HDLC_TXLAST				0x01
#define S1_REG_BIT_HDLC_SA					0x04
#define S1_REG_BIT_HDLC_TXRST				0x08
#define S1_REG_BIT_HDLC_IDLS				0x10
#define S1_REG_BIT_HDLC_SB					0x20
#define S1_REG_BIT_HDLC_SH					0x40
#define S1_REG_BIT_HDLC_TXE					0x80

/* 029 ���M�����݋����W�X�^(TxIER) */
#define S1_REG_BIT_HDLC_TXRDYIE				0x01
#define S1_REG_BIT_HDLC_TXUIE				0x02
#define S1_REG_BIT_HDLC_TXENDIE				0x08
#define S1_REG_BIT_HDLC_TXDI				0x80

/* 02B ���M���[�h���W�X�^ */
#define S1_REG_BIT_HDLC_TXLASTEND			0x01
#define S1_REG_BIT_HDLC_TXUEND				0x02
#define S1_REG_BIT_HDLC_NRZIM				0x10

/* 02C ���N�G�X�g���W�X�^(REQR) */
#define S1_REG_BIT_HDLC_IRX					0x01
#define S1_REG_BIT_HDLC_ITX					0x02
#define S1_REG_BIT_HDLC_RXDRQ				0x40
#define S1_REG_BIT_HDLC_TXDRQ				0x80

/* 02D �}�X�N���W�X�^(MASKR) */
#define S1_REG_BIT_HDLC_MRX					0x01
#define S1_REG_BIT_HDLC_MTX					0x02
#define S1_REG_BIT_HDLC_MRXDRQ				0x40
#define S1_REG_BIT_HDLC_MTXDRQ				0x80



/*********************************************************************
	DTC�v�����(S1_EnableDTC_Request()�̈����ɗp����)
*********************************************************************/
#define S1_DTC_NONE				0 /* �Ȃ� */
#define S1_DTC_RX_HDLC			1 /* HDLC��M */
#define S1_DTC_TX_HDLC			2 /* HDLC���M */
#define S1_DTC_RX_SCI			3 /* SCI��M */
#define S1_DTC_TX_SCI			4 /* SCI���M */

/*********************************************************************
	S1�g�p���̍ő��{�[���[�g
*********************************************************************/
#define S1_BAUD_RATE_MAX		BPS9600_V29

#endif
