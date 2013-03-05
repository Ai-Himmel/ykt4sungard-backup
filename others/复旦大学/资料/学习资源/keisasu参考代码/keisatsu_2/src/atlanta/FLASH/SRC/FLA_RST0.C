/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_rst0.c                                                */
/*  作成者       : 桑原美紀                                                 */
/*  日  付       : 1997/04/23                                               */
/*  概  要       : リード／リセット・コマンド０                             */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\flash\define\fla_pro.h"
#include	"\src\atlanta\flash\define\fla_def.h"
#include	"\src\atlanta\flash\ext_v\rom_tbl.h"	/* 1998/08/06 Y.Murata */

/*************************************************************************
	module		:[リード／リセット・コマンド発行０]
	function	:[リード／リセット・コマンドを発行する（１バスサイクル）]
	return		:[
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
UBYTE Reset0_Function( void )
{
	UWORD  	*flash_address;

	flash_address	= (UWORD *)FLASH_MEM;

	/* コマンド書き込み */
	*flash_address	= RESET_COMMAND;

	return(PASS_FLAG);
}
