/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : ini_tim.c                                                 */
/*  モジュ-ル    : void INT_Timer10ms(void)                                  */
/*  作成者       : 橘正樹                                                    */
/*  日  付       : 1997/05/15                                                */
/*  概  要       : 10msタイマ割込みルーチン                                  */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"

#include "\src\ATLANTA\FLA\define\sys_pro.h"
#include "\src\ATLANTA\ext_v\sys_data.h"

#pragma section FLASHWRITE /*  "PFLASHWRITE" */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
/******************************************************************************
	module		:[１０ｍｓインターバルタイマ割込み]
	function	:[
		1. 10msインターバルタイマ割込みで行う処理を登録します
	]
	return		:[なし]
	common		:[なし]
	machine		:[SH(SH7034/SH704X)]
	language	:[SHC(V.3.0C)]
	keyword		:[INT]
	date		:[1997/05/15]
	author		:[橘正樹]
******************************************************************************/
#if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)  /* HINOKI2 2001/11/13 T.Takagi */
void FLA_INT_Timer10ms(void)
{
	/*---------------------------------------------------------------------*/
	/** コンペアマッチフラグＡをクリアして次の10msタイマ割込を許可します。 */
	/*---------------------------------------------------------------------*/
	MTU__TSR0 &= (0xFE);	/* TGFAのクリア */

	SYS_GeneralTimer++;
}
#else
/**void INT_Timer10ms(void)*/
void FLA_INT_Timer10ms(void)
{
	/*---------------------------------------------------------------------*/
	/** コンペアマッチフラグＡをクリアして次の10msタイマ割込を許可します。 */
	/*---------------------------------------------------------------------*/
	MTU__TSR0 &= (0xFE);	/* TGFAのクリア */

	SYS_GeneralTimer++;
}
#endif
#endif
#pragma section
