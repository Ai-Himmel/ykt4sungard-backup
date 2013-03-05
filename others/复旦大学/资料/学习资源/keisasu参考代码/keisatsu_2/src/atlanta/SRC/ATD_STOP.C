/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANTA																	*/
/*		ﾓｼﾞｭｰﾙ	:void	ATD_CheckStopTask(void)												*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_STOP.Cを流用しました								*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\atd_pro.h"
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\man_pro.h"

#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"	/* By S.Kawasaki 1996/03/07 *//*	mbxno.FCM_Task	*/

/*************************************************************************
	module		:[ストップ・キー検出]
	function	:[
		停止ボタンが押されたらメッセージを送信
	]
	common		:[StopSwFaxCom]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/5]
	author		:[奥村明]
*************************************************************************/
/*----------------------------------------*/
/*ｽﾄｯﾌﾟ･ｽｳｨｯﾁが押されたらﾒｯｾｰｼﾞを送る(ﾀｽｸ)*/
/*----------------------------------------*/
void	ATD_CheckStopTask(void)
{
	MESSAGE_t		msg;

	while(!SYS_FaxComStopSwitch()) {
		wai_tsk(20);
	}
	msg.Item = FROM_AUTODIAL;
	msg.Message = MSG_DETECT_STOP;
	snd_msg(mbxno.FCM_Task, &msg);
	wai_tsk(0xFFFF);
}

