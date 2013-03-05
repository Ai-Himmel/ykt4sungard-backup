/*************************************************************************
	System		:NAGANO		(\src\atlanta\mdm\r288f\define\mdmndpro.hÇà⁄êA)
	FileName	:MDMNDPRO.H
	Author		:
	Date		:1999/10/06
	RealTimeOS	:SHÉÇÉjÉ^Å[
	Description	:
	Maintenance	:

	Copyright(C) 1997 Murata Machinary Ltd. All rights reserved
*************************************************************************/

#ifndef __MDMNDPRO_H
 #define __MDMNDPRO_H



/** MDM_ND.C */
UBYTE MDM_ND_ExtractDataOctet(UWORD , UBYTE * , UBYTE * , UDWORD *);
UBYTE MDM_ND_CheckCRC(UBYTE *rx_buffer, UDWORD byte_count);
UBYTE MDM_ND_FindDleEtx(UBYTE *rx_buffer, UDWORD byte_count);
UBYTE MDM_ND_FindDleSoh(UBYTE *rx_buffer, UDWORD byte_count);
UBYTE MDM_ND_ExaminRxOctet(UBYTE rx_octet_status, UBYTE *rx_buffer, UDWORD byte_count);
UBYTE MDM_ND_RxDataOctet(UWORD *offset_ptr, UWORD *rx_byte_ptr);
void MDM_ND_RxV23Task(UWORD *mbox_no);
void MDM_ND_RxV23TaskExit(void);

/** MDM_V23.C */
void MDM_RxV23Open(void);
void MDM_RxV23Close(void);
UBYTE MDM_ND_Read(UWORD dma_end_time);
UBYTE MDM_ND_ModemRead(UWORD end_time);

/** MDM_NDDT.C */
void MDM_ND_SetDataBit(UBYTE in_data, UBYTE in_mask, UBYTE *out_buffer, UDWORD *out_bit_pos_ptr);
void MDM_ND_ExtractDataBits(UBYTE in_data, UBYTE *data_status_ptr, UBYTE *out_buffer, UDWORD *out_bit_pos_ptr);
void MDM_ND_ExtractDataFromBitStream(UBYTE *in_buffer, UDWORD in_counter, UBYTE *data_status_ptr, UBYTE *out_buffer, UDWORD *bit_position_ptr);
void MDM_ND_InsertStartStopBits(UBYTE in_data, UBYTE *out_buffer, UDWORD *bit_position_ptr);
UBYTE MDM_ND_CheckParity(UBYTE data);
UBYTE MDM_ND_SetParity(UBYTE data);

UWORD ND_CRC16(UBYTE *in, UDWORD length, UDWORD cal_times);
UWORD ND_GenerateCRC16(UBYTE *in, UDWORD length);
UWORD ND_CheckCRC16(UBYTE *in, UDWORD length);


#endif /* __MDMNDPRO_H */
