/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ANZU																		*/
/*		ﾓｼﾞｭｰﾙ	:UBYTE LoopCurrentCheck(UWORD)							*/
/*				:void Del_LoopCurrentTask(void)											*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/30																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_LC.Cを流用しました										*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
/* 定義ファイル */
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\mon_pro.h"	/* モニタコール */
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\memsw\define\mems_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\define\std.h"		/* OK,NG */
#include	"\src\atlanta\define\message.h"
/* 参照ファイル */
#include	"\src\atlanta\ext_v\atd_data.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

/*************************************************************************
	module		:[ループ電流チェック]
	function	:[
		1.一定時間ループ電流をチェック
		2.時間内にループ電流が無い状態が検出されるとエラー
	]
	common		:[]
	condition	:[
		MemorySwitchのループ電流チェックビットがセット
		されている場合のみ動作
	]
	comment		:[]
	return		:[
		1	:一定時間内ループ電流が存続する（ＯＫ）
		0	:一定時間内にループ電流の無い状態検出（ＮＧ）
	]
	machine		:[]
	language	:[]
	keyword		:[ATD]
	date		:[1993/12/6]
	author		:[奥村明]
*************************************************************************/
UBYTE	LoopCurrentCheck( UWORD chk_time )
{
	MESSAGE_t		*ad_receive;

	struct	Timer10msData_t TimeUp;

	tskno_ad_lc_timeup = 0xffff;
	tskno_ad_loop_current = 0xffff;

	/*------------------*/
	/*ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
	/*------------------*/
	if (chk_time == 0) {
		TimeUp.Time = CHK_PBX_PauseTime()*100 + 1;	/*ﾙｰﾌﾟ電流検出時間 (MemorySwitchA-2)*100+1 1ms～1600ms */
	}
	else {
		TimeUp.Time = chk_time/10;	/*ﾙｰﾌﾟ電流検出時間	400ms ～ 800ms */
	}
	TimeUp.SendMBX = mbxno.FCM_Task;
	TimeUp.ReturnValue = TIMEUP;
	cre_tsk(&tskno_ad_lc_timeup, TSK_CMN_MAN_TIMER10MSTASK, &TimeUp);
	/*-----------------------*/
	/*ﾙｰﾌﾟ電流無し検出ﾀｽｸ生成*/
	/*-----------------------*/
	if(CHK_UNI_CurrentLoop()) { /* 個別Ａ０ */
		cre_tsk(&tskno_ad_loop_current, TSK_ATD_LC_OFFCHECKTASK, 0);
	}
	/*----------*/
	/*ﾒｯｾｰｼﾞ受信*/
	/*----------*/
	rcv_msg(mbxno.FCM_Task, &ad_receive);
	/*------------------*/
	/*ﾒｯｾｰｼﾞに対する処理*/
	/*------------------*/
	if(ad_receive->Message == TIMEUP){
		/*-------------------------------*/
		/*ﾙｰﾌﾟ電流ﾁｪｯｸで生成したﾀｽｸを削除*/
		/*-------------------------------*/
		Del_LoopCurrentTask();

		return(OK);	/*OK*/
	}
	else{
		/*-------------------------------*/
		/*ﾙｰﾌﾟ電流ﾁｪｯｸで生成したﾀｽｸを削除*/
		/*-------------------------------*/
		Del_LoopCurrentTask();

		return(NG);	/*NG*/
	}
}

/*-------------------------------*/
/*ﾙｰﾌﾟ電流ﾁｪｯｸで生成したﾀｽｸを削除*/
/*-------------------------------*/
void Del_LoopCurrentTask(void)
{
	if (tskno_ad_lc_timeup != 0xFFFF) {
		del_tsk(&tskno_ad_lc_timeup);
	}
	if (tskno_ad_loop_current != 0xFFFF) {
		del_tsk(&tskno_ad_loop_current);
	}
}

