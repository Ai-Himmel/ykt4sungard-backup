/*************************************************************************
	System		:POPLAR_F
	FileName	:mdm_crc.c
	Author		:
	Date		:1999/10/06
	RealTimeOS	:V53モニター
	Description	:
	Maintenance	:

	Copyright(C) 1997 Murata Machinary Ltd. All rights reserved
*************************************************************************/

/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"

#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"

/*******
** ext_v
*******/
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"

/* CRC CHECK */
/*------------------------------------------------------------*/
/* Usage:													  */
/*		WORD crc( UWORD len, UBYTE *fp)						  */
/*		 1) len: ﾌﾚｰﾑ ﾚﾝｸﾞｽ ( byte )						  */
/*		 2) fp : 対象ﾌﾚｰﾑ ﾎﾟｲﾝﾀ								  */
/*															  */
/*	 return code:											  */
/*		 FCS 計算結果 ( 値 )								  */
/*		 ERROR(-1)											  */
/*------------------------------------------------------------*/
/*************************************************************************
	module		:[ＣＲＣ算出]
	function	:[
		1.
		 mdm_crc.asm をC言語にしただけ 96/1/25 Y.S
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SHC]
	language	:[SHC(Ver3.0C)]
	keyword		:[MDM]
	date		:[1996/01/25]
	author		:[鈴木郁二]
*************************************************************************/
UWORD crc(UWORD len/* 受信バイト数 */,UBYTE *fp/* モデムバッファのアドレス */)
{
	UBYTE byte_data1/* al モデムデータ */;
	UBYTE tbl_offset;

	union 	w_data_t	rg_data1;/* dx */
	struct b_data_t *rgdata1;

	rgdata1 = &(rg_data1.byte_data);
	byte_data1 = 0;
	tbl_offset = 0;
	rg_data1.word_data = 0xffff;

	while(1) {
		byte_data1 = *fp++;
		tbl_offset = rgdata1->l_data;						/*;	 lowbyte of CRC	*/
		tbl_offset ^= byte_data1;							/*; j = (wTempCRC ^ wTempChar)			*/
		tbl_offset &= 0x0f;									/*; j = (wTempCRC ^ wTempChar) & 0x0F	*/
		rg_data1.word_data >>= 4;							/*; wTempCRC >>= 4						*/
	/*	tbl_offset <<= 1;	論理的には必要だがコンパイラがやってくれる	*/
		rg_data1.word_data ^= CRCTab[tbl_offset];			/*; wTempCRC ^= table[j]	*/
		byte_data1 >>= 4;									/*; wTempChar >>= 4						*/
		tbl_offset = rgdata1->l_data;
		tbl_offset ^= byte_data1;							/*; j = (wTempCRC ^ wTempChar)			*/
		tbl_offset &= 0x0f;									/*; j = (wTempCRC ^ wTempChar) & 0x0F	*/
		rg_data1.word_data >>= 4;							/*; wTempCRC >>= 4						*/
	/*	tbl_offset <<= 1;	論理的には必要だがコンパイラがやってくれる	*/
		rg_data1.word_data ^= CRCTab[tbl_offset];			/*; wTempCRC ^= table[j]	*/
		if(--len == 0) {
			break;
		}
	}
	return(~(rg_data1.word_data));							/*; wTempCRC = (~wTempCRC)				*/
}
