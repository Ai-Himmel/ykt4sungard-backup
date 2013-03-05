/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_pol.c                                                */
/*  作成者       : 桑原美紀                                                 */
/*  日  付       : 1997/04/23                                               */
/*  概  要       : トグルビット終了検出			                            */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\flash\define\fla_pro.h"
#include	"\src\atlanta\flash\define\fla_def.h"

/*************************************************************************
	module		:[トグルビット終了検出]
	function	:[
					1. フラッシュメモリをリード
					2. 自動アルゴリズム実行中,内部パルス回数を超えるまでループ
					3. 自動アルゴリズム実行中か再チェック
				]
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
UBYTE Toggle_Bit_Check( UWORD  *addr )
{
	UWORD	toggle_data;
	UWORD	read_data;
	UDWORD	i;

	toggle_data	= (*addr & TOGGLE_BIT);

	i	= 0;
	do{
		read_data	= *addr;
		if ((UWORD)(read_data & TOGGLE_BIT ) == (UWORD)toggle_data ) {	/* 自動アルゴリズム実行中 */
			break;
		}
		toggle_data	= (read_data & TOGGLE_BIT);
		if( i >= 0xFFFFFFFF ){
			return( ERROR_FLAG_TIMEOVER );
		}
		i++;

	} while((UWORD)(read_data & HANGUP_BIT ) != (UWORD)HANGUP_BIT );		/* 内部パルス回数を超えるまで */

	toggle_data	= (*addr & TOGGLE_BIT);
	read_data	= *addr;
	if((UWORD)(read_data & TOGGLE_BIT ) != (UWORD)toggle_data ){	/* 自動アルゴリズム実行中 */
		return( FAIL_FLAG );
	}
	
	return( PASS_FLAG );
}
