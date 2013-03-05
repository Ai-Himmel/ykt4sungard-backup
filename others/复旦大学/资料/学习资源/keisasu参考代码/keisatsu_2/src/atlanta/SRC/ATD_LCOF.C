/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANTA																	*/
/*		ﾓｼﾞｭｰﾙ	:void ATD_LC_OffCheckTask(void)												*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_LCOF.Cを流用しました								*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\atd_pro.h"
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\message.h"

#include "\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#include "\src\atlanta\sh7043\define\io_pro.h"	/*	リレー関係	*/

/*************************************************************************
	module		:[ループ電流イベントチェックタスク]
	function	:[
		ループ電流が無い状態があればメッセージを送信
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/6]
	author		:[奥村明]
*************************************************************************/
/*---------------------------------------------*/
/*ﾙｰﾌﾟ電流無しを検出したらメッセージを送る(ﾀｽｸ)*/
/*---------------------------------------------*/
void	ATD_LC_OffCheckTask()
{
	MESSAGE_t	 msg;

	/*	FRAで場合によっては100ms程度のポーズを入れる	harada */
	while(LCV_Status()) {	/* 極性反転のポートのＸＯＲを見ている Oct.31.1996  By T.Yamaguchi */
		wai_tsk(10);	/*	100ms	*/
	}

	/**	ループ電流がない状態があった	*/
	msg.Message = MSG_DETECT_LC_OFF;
	snd_msg(mbxno.FCM_Task, &msg);
	wai_tsk(0xFFFF);
}
