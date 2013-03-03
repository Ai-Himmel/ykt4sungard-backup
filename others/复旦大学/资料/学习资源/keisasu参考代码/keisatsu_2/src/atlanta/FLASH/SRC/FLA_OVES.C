/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_oves.c                                               */
/*  作成者       : 曽根岡拓                                                 */
/*  日  付       : 1998/04/13                                               */
/*  概  要       : 書き込み・コマンド			                            */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\ATLANTA\FLASH\define\fla_pro.h"
#include	"\src\ATLANTA\FLASH\define\fla_def.h"
#include	"\src\ATLANTA\FLASH\ext_v\fla_tbl.h"
#include	"\src\atlanta\flash\ext_v\rom_tbl.h"	/* 1998/08/06 Y.Murata */

/*************************************************************************
	module		:[オーバイレーズ処理]
	function	:[消去中に、電源ＯＦＦされたときの処理を実行する]
	return		:[
					FAIL_FLAG(1)	-> NG（フラッシュ破壊している可能性あり）
					PASS_FLAG(0)	-> OK
				]
	common		:[]
	condition	:[消去中に異常があったときにコールされること]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1998/04/13]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE OverErase_Function(UWORD	*addr, UDWORD size)
{
	UWORD  	*flash_addr;			/* 作業用フラッシュアドレス */
	UDWORD	word_cnt;				/* １セクタ内のカウンタ */
	UBYTE	over_erase_cnt;			/* オーバイレース処理カウンタ（仕様書では１０回）*/

	/**	オーバイレーズ状態だった、オーバイレーズ是正処理	*/
	for (over_erase_cnt = 0; over_erase_cnt < OVER_ERASE_COUNT_MAX; over_erase_cnt++) {

		/**	セクタ内全アドレスに０を書き込み処理	*/
		flash_addr = addr;
		for (word_cnt = 0; word_cnt < size; word_cnt += 2) {
			Program_Function(flash_addr, 0x0000);	/** データ０の書き込み	*/
			Reset0_Function();	/**	リセットコマンド入力	*/
			flash_addr++;
		}

		/**	セクタ内全アドレスベリファイチェック */
		flash_addr = addr+FLASH_MEM;
		for (word_cnt = 0; word_cnt < size; word_cnt += 2) {
			if (*flash_addr != (UWORD)0x0000) {
				break;
			}
			flash_addr++;
		}
		if (word_cnt >= size) {
			return (PASS_FLAG);	/* 復旧成功 */
		}
	}
	return (FAIL_FLAG); /* 復旧できず（フラッシュ破壊している可能性あり） */
}
