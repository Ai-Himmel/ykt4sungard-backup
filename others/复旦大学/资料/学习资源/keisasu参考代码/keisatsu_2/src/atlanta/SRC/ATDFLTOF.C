/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANTA																		*/
/*		ﾓｼﾞｭｰﾙ	:void	ATD_CheckFilter1OffTask(int *)									*/
/*				:void	ATD_CheckFilter2OffTask(int *)									*/
/*				:void	ATD_CheckFilter3OffTask(int *)									*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATDFLTOF.Cを流用しました										*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\mon_pro.h"	/* wai_tsk(),wai_evt(),snd_msg() */
#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\message.h"

#include	"\src\atlanta\ext_v\atd_tbl.h"

#include	"\src\atlanta\sh7043\define\def_evtn.h"	/* By S.Kawasaki 1996/03/08 *//* v53 イベント */

/*************************************************************************
	module		:[フィルター１のトーン無しイベント待ち]
	function	:[
		1.トーン無しイベントを待つ
		2.イベントが来たらメッセージ送信
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/5]
	author		:[奥村明]
*************************************************************************/
void	ATD_CheckFilter1OffTask(
		WORD	*mail_box)
{
	MESSAGE_t		msg;
	wai_evt(EVT_TONE_FILTER1_OFF);

	msg.Message = MSG_DETECT_FILTER_OFF;
	snd_msg(*mail_box, &msg);
	wai_tsk(0xFFFF);
}

/*************************************************************************
	module		:[フィルター２のトーン無しイベント待ち]
	function	:[
		1.トーン無しイベントを待つ
		2.イベントが来たらメッセージ送信
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/5]
	author		:[奥村明]
*************************************************************************/
void	ATD_CheckFilter2OffTask(
		WORD	*mail_box)
{
	MESSAGE_t		msg;
	wai_evt(EVT_TONE_FILTER2_OFF);

	msg.Message = MSG_DETECT_FILTER_OFF;
	snd_msg(*mail_box, &msg);
	wai_tsk(0xFFFF);
}

/*************************************************************************
	module		:[フィルター３のトーン無しイベント待ち]
	function	:[
		1.トーン無しイベントを待つ
		2.イベントが来たらメッセージ送信
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/5]
	author		:[奥村明]
*************************************************************************/
void	ATD_CheckFilter3OffTask(
		WORD	*mail_box)
{
	MESSAGE_t		msg;
	wai_evt(EVT_TONE_FILTER3_OFF);

	msg.Message = MSG_DETECT_FILTER_OFF;
	snd_msg(*mail_box, &msg);
	wai_tsk(0xFFFF);
}

