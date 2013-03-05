/*************************************************************************
	System		:NAGANO		(\src\atlanta\mdm\r288f\define\mdmnddef.hを移植)
	FileName	:MDMNDDEF.H
	Author		:
	Date		:1999/10/06
	RealTimeOS	:SHモニター
	Description	:
	Maintenance	:

	Copyright(C) 1997 Murata Machinary Ltd. All rights reserved
*************************************************************************/

#ifndef mdm_nd_def_h
 #define mdm_nd_def_h

#define		ND_MODEM_DMA_SIZE	16
#define		ND_RX_TIMEOUT		(5 + (ND_MODEM_DMA_SIZE * 100) / (1200 / 8 / 4)) /*  > (ND_MODEM_DATA_SIZE * 8) / (1200bps)   */
#define		ND_RX_OCTET_TIMEOUT		(40/10) /*  1 バイト受信タイムアウト   */
#define		ND_RX_1ST_TIMEOUT	(5000/10) 	/* 5sec */


/*********************************************
ナンバーディスプレイ受信状態
	MDM_ND_ExaminRxOctet() で使用される
*********************************************/
#define 	ND_RX_STATUS_WAIT_1ST_BIT		0
#define		ND_RX_STATUS_RECEIVING_DATA		1
#define		ND_RX_STATUS_WAIT_CRC1			2
#define		ND_RX_STATUS_WAIT_CRC2			3
#define		ND_RX_STATUS_RX_COMPLETE		4
#define		ND_RX_STATUS_RX_FAIL			5
#define		ND_RX_STATUS_WAIT_HEADER		6		/* <DLE><SOH> 待ち */
#define		ND_RX_STATUS_FOUND_CRC2			7
#define		ND_RX_STATUS_RX_TIMEOUT			8


/*********************************************
ナンバーディスプレイビット列の受信状態
	MDM_ND_ExtractDataBits()で使用される
*********************************************/

#define ND_BIT_STATUS_DATA_BIT0  	0
#define ND_BIT_STATUS_DATA_BIT1  	1
#define ND_BIT_STATUS_DATA_BIT2  	2
#define ND_BIT_STATUS_DATA_BIT3  	3
#define ND_BIT_STATUS_DATA_BIT4  	4
#define ND_BIT_STATUS_DATA_BIT5  	5
#define ND_BIT_STATUS_DATA_BIT6  	6
#define ND_BIT_STATUS_DATA_BIT7  	7
#define ND_BIT_STATUS_MARK_BIT		8
#define ND_BIT_STATUS_START_BIT 	9
#define ND_BIT_STATUS_STOP_BIT  	10


#ifndef DLE
#define 	DLE		0x10
#endif

#ifndef ETX
#define		ETX		0x03
#endif

#ifndef SOH
#define		SOH		0x01
#endif

#define MDM_ND_PARTIY_MASK	0x7f


/*********************************************
ナンバーディスプレイ V23 受信のの終了状態
by H.Kubo 1998/09/29
*********************************************/

#define 	MDM_ND_V23_RX_SUCCESS 		1
#define 	MDM_ND_V23_RX_DATA_ERROR 	2
#define 	MDM_ND_V23_RX_TIMEOUT		3

#endif	/* #ifndef mdm_nd_def_h */
