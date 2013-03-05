/************************************************************************
*	System		: POPLAR_F
*	File Name	: MDM_MLDY.C
*	Author		: 松本 正幸
*	Date		: 1999/10/12
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\evttomsg.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\sh7043\define\def_mbxn.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
/*#include "\src\atlanta\poplar_f\define\popf_tib.h"*/
#include "\src\atlanta\sh7043\define\def_tib.h"
#if(0)/* 条件入れ忘れてますよ。ｺﾝﾊﾟｲﾙｴﾗｰが出る。V851 By Y.Suzuki 2002/09/14*/
//#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#endif

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && (PRO_MODEM == R288F)	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */

/*************************************************************************
	module		:[音声LSI 電源ON時の初期化]
	function	:[電源ON時にLSIの初期化を行う]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[1999/10/8]
	author		:[松本]
*************************************************************************/
void  MDM_AnswerLSI_Initialize(void)
{
	CMN_ResetOnAnswerLSI();
	wai_tsk(1);
	CMN_AnswerLSIOff();
	wai_tsk(1);
	CMN_ResetOffAnswerLSI();
}
/*************************************************************************
	module		:[音声LSI 音声応答メイン]
	function	:[
		音声LSI（MSM9805）より音声を発声させる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[1999/10/12]
	author		:[松本]
*************************************************************************/
void	VoicePrompt(UBYTE phase)
{
	struct	  Timer10msData_t	AnswerLSI10msTimer;
	struct	  EventToMessageData_t	AnswerLSIWaitNAR;
	MESSAGE_t	*msg;
	UWORD	ad_message;

	SYS_VoiceTxFlag = YES;
	/* ｱﾅﾛｸﾞSWを音声に設定する */
	SelectVOL();

	/* ﾌﾚｰｽﾞをｾｯﾄする */
	CMN_SetFraseAnswerLSI(phase);

	/* 擬似ﾋﾞｼﾞ－(NAR)でなくなるまで待つ */
	MDM_WaitNAR(50);

	/* 音声送出開始 400msﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成 */
	AnswerLSI10msTimer.Time = 40;
	AnswerLSI10msTimer.SendMBX = mbxno.MDM_VoiceTask;
	AnswerLSI10msTimer.ReturnValue = NAR_TIMEUP;
	if (tskid_VoiceTimeUpTask == 0xFFFF) {
		cre_tsk(&tskid_VoiceTimeUpTask,TSK_CMN_WATCHTIMER10MSTASK,&AnswerLSI10msTimer);
	}
	
	/* 音声送出開始 検出ﾀｽｸ生成 */
	AnswerLSIWaitNAR.DetEventNo = EVT_NAR;
	AnswerLSIWaitNAR.SendMBX = mbxno.MDM_VoiceTask;
	AnswerLSIWaitNAR.ReturnValue = MSG_MELODY_FRASE_START;
	if (tskid_NAR_DetectTask == 0xFFFF) {
		cre_tsk(&tskid_NAR_DetectTask,TSK_CMN_EVENTTOMESSAGETASK,&AnswerLSIWaitNAR);
	}

	/* 音声送出開始ｾｯﾄ */
	CMN_AnswerLSIOn();
	MDM_WaitST(); 
	CMN_AnswerLSIOff();

	/* 音声送出待ち */
	rcv_msg(mbxno.MDM_VoiceTask,&msg);
	
	ad_message = msg->Message;
	switch (ad_message) {
	case	MSG_MELODY_FRASE_START:
		break;
	case	NAR_TIMEUP:
		break;
	}
	
	if (tskid_VoiceTimeUpTask != 0xFFFF) {
		del_tsk(&tskid_VoiceTimeUpTask);
	}
	if (tskid_NAR_DetectTask != 0xFFFF) {
		del_tsk(&tskid_NAR_DetectTask);
	}
	
	/* 無音ﾌﾚｰｽﾞをｾｯﾄする 
	* （理由）
	*  無音送出開始信号（NAR == 1）によって
	*  音声送出が終了したことを知らせるため
	*/
	CMN_SetFraseAnswerLSI(6);
	
	/* NAR検出後ST入力までに30μｓ以上の時間をあけることが必要 */
	wai_tsk(2);
	
	/* 無音声送出開始 20sﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成 */
	AnswerLSI10msTimer.Time = 2000;
	AnswerLSI10msTimer.SendMBX = mbxno.MDM_VoiceTask;
	AnswerLSI10msTimer.ReturnValue = NAR_TIMEUP;
	if (tskid_VoiceTimeUpTask == 0xFFFF) {
		cre_tsk(&tskid_VoiceTimeUpTask,TSK_CMN_WATCHTIMER10MSTASK,&AnswerLSI10msTimer);
	}
	
	/* 無音送出開始 検出ﾀｽｸ生成 */
	AnswerLSIWaitNAR.DetEventNo = EVT_NAR;
	AnswerLSIWaitNAR.SendMBX = mbxno.MDM_VoiceTask;
	AnswerLSIWaitNAR.ReturnValue = MSG_SILENT_FRASE_START;
	if (tskid_NAR_DetectTask == 0xFFFF) {
		cre_tsk(&tskid_NAR_DetectTask,TSK_CMN_EVENTTOMESSAGETASK,&AnswerLSIWaitNAR);
	}

	/* 無音送出開始ｾｯﾄ */
	CMN_AnswerLSIOn();
	MDM_WaitST();
	CMN_AnswerLSIOff();
	
    /* 無音送出待ち */
	rcv_msg(mbxno.MDM_VoiceTask,&msg);
	ad_message = msg->Message;
	
	switch (ad_message) {
#if (0)
** 	/* メッセージ間違いでは？？？
** 	** 結果的にメッセージを受けた後の処理が何もないので結果オーライですが気持ち悪いので修正しておきます。
** 	** by O.Kimoto 2002/10/15
** 	*/
** 	case	MSG_MELODY_FRASE_START:
#else
	case	MSG_SILENT_FRASE_START:
#endif
		break;
	case	NAR_TIMEUP:
		break;
	}
	
	if (tskid_VoiceTimeUpTask != 0xFFFF) {
		del_tsk(&tskid_VoiceTimeUpTask);
	}
	if (tskid_NAR_DetectTask != 0xFFFF) {
		del_tsk(&tskid_NAR_DetectTask);
	}

#if defined(HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* NTT仕様 音声応答終了後に保留メロディが流れる対策 by J.Kishida 2002/09/26 */
	/*
	// アナログSWを音声応答から保留メロディ/モデムに切り替えたとき，
	// 保留メロディ/モデムを切り替えるアナログSWが保留メロディ側に
	// なっていると，音声応答終了後に保留メロディが流れてしまいます．
	// あらかじめモデム側にアナログSWを倒しておきます．
	*/
	StopSendingMelodyToLine();
	SYS_FaxMelodyFlag = NO;
#endif
	
	/* ｱﾅﾛｸﾞSWをモデム、保留音に設定する */
	SelectMELorTX();

	/* ｱﾅﾛｸﾞからﾃﾞｼﾞﾀﾙへの移行時間 */
	wai_tsk(40);
	
	SYS_VoiceTxFlag = NO;


}

/*************************************************************************
	module		:[音声ＬＳＩ 擬似ビジー割込み]
	function	:[
		
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[]
	date		:[1999/10/06]
	author		:[松本]
*************************************************************************/
void	MDM_AnswerLSIInterrupt(void)
{
	idet_evt(EVT_NAR);
}
/*************************************************************************
	module		:[ST立ちあがり待ち時間]
	function	:[
		
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[]
	date		:[1999/10/06]
	author		:[松本]
*************************************************************************/
void	MDM_WaitST(void)
{
	UWORD	i;
	UWORD	dummy;

	for (i = 0; i < 300; i++) {
		dummy++;
	}
}
/*************************************************************************
	module		:[NAR 検出待ち時間]
	function	:[
		
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[]
	date		:[1999/10/25]
	author		:[松本]
*************************************************************************/
void	MDM_WaitNAR(UWORD timer)
{
	UWORD	count;
	
	count = 0;
	while (1) {
		if (NAR() == 1) {
			break;
		}
		if (count > timer) {
			break;
		}
		count++;
		wai_tsk(1);
	}
}

/*************************************************************************
	module		:[音声応答の終了処理]
	function	:[
	]
	return		:[
		なし
	]
	common		:[
	]
	condition	:[]
	comment		:[
				]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1999/11/04]
	author		:[松本]
*************************************************************************/
void  VoiceReset(void)
{
	/*-----------------------------------*/
	/* ｱﾅﾛｸﾞSWをﾓﾃﾞﾑ、保留音に設定する   */
	/*-----------------------------------*/
	SelectMELorTX();

	/*--------------*/
	/* 音声送出停止 */
	/*--------------*/
	MDM_AnswerLSI_Initialize();
	
	SYS_VoiceTxFlag = NO;
}

/*************************************************************************
	module		:[]
	function	:[
	]
	return		:[
		なし
	]
	common		:[
	]
	condition	:[]
	comment		:[
				]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1999/11/06]
	author		:[松本]
*************************************************************************/
void  VoicePromptTaskDelete(void)
{
	if (tskid_VoiceTimeUpTask != 0xFFFF) {
		del_tsk(&tskid_VoiceTimeUpTask);
	}
	if (tskid_NAR_DetectTask != 0xFFFF) {
		del_tsk(&tskid_NAR_DetectTask);
	}
}

#endif	/* End of File */
