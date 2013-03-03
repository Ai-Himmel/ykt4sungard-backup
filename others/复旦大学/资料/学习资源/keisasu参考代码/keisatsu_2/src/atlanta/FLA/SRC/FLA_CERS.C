/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_cers.c                                                */
/*  作成者       : 桑原美紀                                                 */
/*  日  付       : 1997/04/23                                               */
/*  概  要       : チップ消去・コマンド			                            */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\ATLANTA\FLA\define\fla_pro.h"
#include	"\src\ATLANTA\FLA\define\fla_def.h"

#pragma section FLASHWRITE /*  "PFLASHWRITE" */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
/*************************************************************************
	module		:[チップ消去・コマンド発行]
	function	:[チップ消去コマンドを発行する]
	return		:[
					FAIL_FLAG(1)	-> NG
					PASS_FLAG(0)	-> OK
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1997/04/23]
	author		:[桑原美紀]
*************************************************************************/
UBYTE Chip_Erase_Function( void )
{
	UWORD 	*flash_address;

	flash_address	= (UWORD *)FLASH_MEM;

	/* コマンド書き込み */
	*( flash_address + FIRST_ADDR )	= FIRST_DATA;
	*( flash_address + SECOND_ADDR )= SECOND_DATA;
	*( flash_address + THIRD_ADDR )	= ERASE_SETUP_COMMAND;
	*( flash_address + FOURTH_ADDR )= FIRST_DATA;
	*( flash_address + FIFTH_ADDR )	= SECOND_DATA;
	*( flash_address + SIXTH_ADDR )	= CHIP_ERASE_COMMAND;

	/* データポーリングチェック */
/*	return(Data_Polling_Check( flash_address, BLANK_DATA ));*/

	/* トグル・ビット */
	return(Toggle_Bit_Check( flash_address ));
}
#endif

#pragma section
