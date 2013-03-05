/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANTA																	*/
/*		ﾓｼﾞｭｰﾙ	:void	ATD_RelayOff(void)													*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBA\ANZU\SRC\ATDRELAY.Cを流用しました								*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"	/* リレー関係 */

/*************************************************************************
	module		:[リレーＯＦＦ]
	function	:[
		1.ダイヤル中のトーン検出前にリレーを戻す
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[ATD]
	date		:[1994/03/07]
	author		:[奥村明]
*************************************************************************/

void	ATD_RelayOff(void)
{
	S_RelayOff();

/* ポプラのカプラはＣＭＬとＤＰが共通であるのでここで、ＯＦＦするのはまずい
//	wai_tsk(1);
//	DP_RelayOff();
*/
}
