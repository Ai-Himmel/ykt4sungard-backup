/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_rsm.c                                                */
/*  作成者       : 桑原美紀                                                 */
/*  日  付       : 1997/04/23                                               */
/*  概  要       : 消去再開コマンド				                            */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\flash\define\fla_pro.h"
#include	"\src\atlanta\flash\define\fla_def.h"
#include	"\src\atlanta\flash\ext_v\rom_tbl.h"	/* 1998/08/06 Y.Murata */

/*************************************************************************
	module		:[消去再開コマンド発行]
	function	:[消去再開コマンドを発行する]
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
UBYTE Erase_Resume_Function( void )
{
	UWORD	*flash_address;

	flash_address	= (UWORD *)FLASH_MEM;

	/* コマンド書き込み */
	*flash_address	= RESUME_COMMAND;

	/* データポーリングチェック */
/*	return( W_Data_Polling_Check( flash_address, 0, BLANK_DATA );*/
	/* トグル・ビット */
/*	return(Toggle_Bit_Check( flash_address ));*/

	return( PASS_FLAG );
}
