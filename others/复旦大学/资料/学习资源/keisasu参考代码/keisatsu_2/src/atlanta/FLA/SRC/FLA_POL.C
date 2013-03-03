/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_pol.c                                                */
/*  作成者       : 桑原美紀                                                 */
/*  日  付       : 1997/04/23                                               */
/*  概  要       : データ・ポーリングチェック	                            */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\ATLANTA\FLA\define\fla_pro.h"
#include	"\src\ATLANTA\FLA\define\fla_def.h"

#pragma section FLASHWRITE /*  "PFLASHWRITE" */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
/*************************************************************************
	module		:[データポーリングチェック]
	function	:[
					1. フラッシュメモリをリード
					2. 自動書込み終了か内部書込み時間経過までループ
					3. 自動書込み終了か再チェック
				]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1997/04/23]
	author		:[桑原美紀]
*************************************************************************/
UBYTE Data_Polling_Check( UWORD  *addr, UWORD data )
{
	UWORD	polling_data;
	UWORD	read_data;
/*	UWORD	i;*/
	UDWORD  i;
	
	polling_data	= (data & DATA_POLLING_BIT);

	i	= 0;
	do{
		read_data	= *addr;
		if((UWORD)(read_data & DATA_POLLING_BIT ) == (UWORD)polling_data ){	/* 自動書込み終了 */
			break;
		}

		if( i >= 0xFFFFFFFF ){
			return( ERROR_FLAG_TIMEOVER );
		}
		i++;

	}while((UWORD)(read_data & HANGUP_BIT ) != (UWORD)HANGUP_BIT );		/* 内部書込み時間経過まで */

	read_data	= *addr;
	if((UWORD)(read_data & DATA_POLLING_BIT ) != (UWORD)polling_data ){	/* 自動書込み終了 */
		return( FAIL_FLAG );
	}
	
	return( PASS_FLAG );
}
#endif
#pragma section
