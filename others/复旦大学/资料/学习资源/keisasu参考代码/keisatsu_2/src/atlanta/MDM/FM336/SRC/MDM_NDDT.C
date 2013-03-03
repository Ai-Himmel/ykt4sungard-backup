/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                  */
/*  ファイル名   : mdm_nddt.c                                                */
/*  作成者       :                                                           */
/*  日  付       : 1999/10/06                                                */
/*  概  要       : ナンバーディスプレイ用Ｖ２３受信データ処理                */
/*  修正履歴     : 2002/01/19 HINOKI2で使用するためNAGANOからフィードバック  */
/*	keyword      :[MDM]                                                      */
/*	machine      :[SH7043]                                                   */
/*	language     :[SHC]                                                      */
/*---------------------------------------------------------------------------*/


#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\mdm\fm336\define\mdmnddef.h"

void MDM_ND_SetDataBit(UBYTE in_data, UBYTE in_mask, UBYTE *out_buffer, UDWORD *out_bit_pos_ptr);
void MDM_ND_ExtractDataBits(UBYTE in_data, UBYTE *data_status_ptr, UBYTE *out_buffer, UDWORD *out_bit_pos_ptr);
void MDM_ND_ExtractDataFromBitStream(UBYTE *in_buffer, UDWORD in_counter, UBYTE *data_status_ptr, UBYTE *out_buffer, UDWORD *bit_position_ptr);
void MDM_ND_InsertStartStopBits(UBYTE in_data, UBYTE *out_buffer, UDWORD *bit_position_ptr);
UBYTE MDM_ND_CheckParity(UBYTE data);
UBYTE MDM_ND_SetParity(UBYTE data);

/*************************************************************************
	module		:[ナンバーディスプレー データコピー処理]
	function	:[
		1.引数で渡たされる２つのバッファ間でデータのコピーを行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1998/09/29]
	author		:[久保博]
*************************************************************************/
void MDM_ND_ExtractDataFromBitStream(UBYTE *in_buffer, UDWORD in_counter, UBYTE *data_status_ptr, UBYTE *out_buffer, UDWORD *bit_position_ptr)
{
	UDWORD i;

	/*
	** Changed by H.Kubo 1998/09/11
	*/
	/*
	** R288F は、 start bit, stop bit を落として、データだけを渡してくれるので、
	** そのまま受信バイトデータをコピーすればいい
	*/
	MemoryMove(out_buffer + (*bit_position_ptr / 8), in_buffer, in_counter);
	*bit_position_ptr += (8 * in_counter);
	/*  *data_status_ptr の値は何も触らないことにする。 */
}

/*************************************************************************
	module		:[ナンバーディスプレー パリティーチェック処理]
	function	:[
		1.引数で渡されるデータのパリティーをチェックする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1998/09/29]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_ND_CheckParity(UBYTE data)
{
	UWORD i;
	UWORD parity_count = 0;
	for (i = 0; i < 8; i++) { /* 1 の個数を数え上げる */
		if (data & ((UBYTE) (1 << i))) {
			parity_count++;
		}
	}
	if (parity_count & 0x01) { /* 1 の個数が 奇数個だったら、 */
		return FALSE;
	}
	return TRUE;
}

/*************************************************************************
	module		:[ナンバーディスプレー パリティー設定]
	function	:[
		1.引数でわたされるデータにパリティービットを設定する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1998/09/29]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_ND_SetParity(UBYTE data)
{
	UWORD i;
	UWORD parity_count = 0;
	for (i = 0; i < 7; i++) {
		if (data & ((UBYTE) (1 << i))) {
			parity_count++;
		}
	}
	if (parity_count & 0x01) { /* 1 の個数が 奇数個だったら、 */
		return (data | 0x80);
	}
	return (data & 0x7F);
}


/*******************************************************************************
	module: 	[ITU-T 推奨の CRC16]
	function: 	[生成多項式 x16+x12+x5+1 による CRC コード生成と CRC による
				 ビット列データの誤り検出]
	keyword			:[MDM]
	machine			:[8x86 & SH70xx]
	language		:[MS-C  & SHC]
*******************************************************************************/



#define ND_CRC_DIVISOR 0x11021;
#define ND_CRC_HIGHEST_BIT 0x10000
#define ND_CRC_DEGREE	16


/* 入力データの形式
**  配列の 0 番目の最下位ビットが先頭。
**  配列の 0 番目の最上位ビットが八番目。
**  配列の 1 番目の最下位ビットが九番目。
**
*/
/*************************************************************************
	module		:[CRC16 の計算]
	function	:[
		8bit データの配列の CRC を計算
		length にデータ長を指定
		cal_times にデータ長＋データを上位にシフトする桁数／８ を指定。
	]
	return		:[CRC]
	common		:[	]
	condition	:[]
	comment		:[]
	date		:[1998/09/29]
	author		:[久保博]
*************************************************************************/
UWORD ND_CRC16(UBYTE *in, UDWORD length, UDWORD cal_times)
{
	UDWORD	dat;
	UDWORD index;
	UBYTE i;

	dat = 0;
	index = 0;
	i = 0;
	while (1) {
		if (i >= 8) {
			i -= 8;
			index++;
			if (index >= cal_times) {
				break;
			}
		}
		dat *= 2;
		if ((length > index) && (in[index] & (1 << i))) {
			dat += 1;
		}
		if (dat & ND_CRC_HIGHEST_BIT ) { /* 最上位 x16 係数が1 だったら */
			dat ^= ND_CRC_DIVISOR;		/* x16 + x12 + x5 +1 を引く (係数は 2 を法とする引き算) */
	    }
	    i++;
	}
	return dat;
}

/*************************************************************************
	module		:[CRC16 の生成多項式による剰余を計算]
	function	:[
		in で与えられるデータに x16 を掛けて x16+x12+x5+1 で割り算した余りを計算する
		余りは、MSB が x15 の係数、 LSB が 定数項の係数になっている。
	]
	return		:[CRC]
	common		:[	]
	condition	:[]
	comment		:[]
	date		:[1998/09/29]
	author		:[久保博]
*************************************************************************/
UWORD ND_GenerateCRC16(UBYTE *in, UDWORD length)
{
	UDWORD cal_times;
	cal_times = length +  (ND_CRC_DEGREE / 8); /* 入力データに x16 をかける => 入力データの後、 0 を入れて計算続行 */
	return ND_CRC16(in, length, cal_times);
}

/*************************************************************************
	module		:[CRC16 によるデータ誤りの検査]
	function	:[
		in で与えられるデータを x16+x12+x5+1 で割り算した余りを計算する。
		余りが 0 なら、正しい誤りはない。
		余りが 0 でなければ、誤りがある。
	]
	return		:[CRC]
	common		:[	]
	condition	:[]
	comment		:[]
	date		:[1998/09/29]
	author		:[久保博]
*************************************************************************/
UWORD ND_CheckCRC16(UBYTE *in, UDWORD length)
{
	return ND_CRC16(in, length, length);
}


/*******************************************
**  Test programs working on MS-DOS
*******************************************/

