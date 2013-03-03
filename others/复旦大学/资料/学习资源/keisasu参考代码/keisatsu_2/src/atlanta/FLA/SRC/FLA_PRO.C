/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_pro.c                                                */
/*  作成者       : 桑原美紀                                                 */
/*  日  付       : 1997/04/23                                               */
/*  概  要       : 書き込み・コマンド			                            */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\ATLANTA\FLA\define\fla_pro.h"
#include	"\src\ATLANTA\FLA\define\fla_def.h"

#pragma section FLASHWRITE /*  "PFLASHWRITE" */
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
/*************************************************************************
	module		:[書き込み・コマンド発行]
	function	:[書き込みコマンドを発行する]
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
UBYTE Program_Function( UWORD *addr, UWORD data )
{
	UWORD  	*flash_address;
	UWORD	*data_addr;

	flash_address	= (UWORD *)FLASH_MEM;

	data_addr = (UWORD *)( (UDWORD)flash_address + (UDWORD)addr );

	/* コマンド書き込み */
	*( flash_address + FIRST_ADDR )	= FIRST_DATA;
	*( flash_address + SECOND_ADDR )= SECOND_DATA;
	*( flash_address + THIRD_ADDR )	= PROGRAM_COMMAND;
	*( data_addr )	= data;


	/* データポーリングチェック */
	return(Data_Polling_Check( data_addr, data ));

	/* トグル・ビット */
/*	return(Toggle_Bit_Check( data_addr ));*/
}
#endif
#pragma section
