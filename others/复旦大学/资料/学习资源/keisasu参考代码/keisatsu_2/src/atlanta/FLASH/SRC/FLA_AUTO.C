/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_auto.c                                               */
/*  作成者       : 桑原美紀                                                 */
/*  日  付       : 1997/04/23                                               */
/*  概  要       : オートセレクト・コマンド		                            */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\flash\define\fla_pro.h"
#include	"\src\atlanta\flash\define\fla_def.h"
#include	"\src\atlanta\flash\ext_v\rom_tbl.h"	/* 1998/08/06 Y.Murata */

/*************************************************************************
	module		:[オートセレクト・コマンド発行]
	function	:[オートセレクト・コマンドを発行する]
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
UBYTE Autoselect_Function( UWORD *manufacture_code, UWORD *device_code )
{
	UWORD 	*flash_address;

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/10 Y.Murata */
	UWORD	timer;
	UWORD	dummy;
	UBYTE	sw;
#endif

/*	(unsigned long)flash_address	= FLASH_MEM;*/
	flash_address	= (UWORD *)FLASH_MEM;

	/* コマンド書き込み */
	*( flash_address + FIRST_ADDR )	= FIRST_DATA;
	*( flash_address + SECOND_ADDR )= SECOND_DATA;
	*( flash_address + THIRD_ADDR )	= AUTOSELECT_COMMAND;

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/10 Y.Murata */
	/* debug */
	sw = 0;
	if (sw) {
		for (timer = 0; timer < 10; timer++) {
			dummy++;
		}
	}
#endif
	/* ﾏﾆｭﾌｧｸﾁｬｺｰﾄﾞ､ﾃﾞﾊﾞｲｽｺｰﾄﾞの読み出し */
	*manufacture_code	= *( flash_address + MANUFACTURE_OFFSET );
	*device_code		= *( flash_address + DEVICE_OFFSET );

	/* リード／リセット発行（オートセレクトモードのリセット） */
	Reset0_Function();

	return(PASS_FLAG);
}
