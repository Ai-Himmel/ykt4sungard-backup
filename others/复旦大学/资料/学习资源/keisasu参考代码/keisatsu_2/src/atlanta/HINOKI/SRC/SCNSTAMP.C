/*************************************************************************
	module		:[SCN]
	function	:[
		1.済みスタンプ制御
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[SCN]
	date		:[1998/07/14]
	author		:[曽根岡拓]
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\syslocal.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"

#if (PRO_STAMP == ENABLE)
/*************************************************************************
	module		:[済みスタンプ制御]
	function	:[
		1.スキャナ割り込みからのスタンプ押下イベントを待つ
		2.モータ停止－＞スタンプＯｎ－＞モータ再起動
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7014]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[SCN]
	date		:[1998/07/14]
	author		:[曽根岡拓]
*************************************************************************/
void PushStamp(void)
{
	UBYTE	EventFlag;

	EventFlag = 0;
	
	if (SYS_StampFlag) {
		/* 済みスタンプ押下位置に原稿が来るのを待ちます */
		if (!ExecutePushStamp) {
			wai_evt(EVT_SCN_STAMP);
		}
		ExecutePushStamp = FALSE;

		wai_tsk(1);	/* モータが完全にとまるまで待ちます  1998/12/05 by T.Soneoka */

		/* スタンプ押下 */
#if (0)
** 		/* D86-009 スタンプを余分に押してしまう不具合修正 by O.Kimoto 1999/02/04 */
** 		CMN_PushStamp();
#else
		if (ScannerMode == SCANNER_STAMP_MODE) {
			if (Ds2Raw() == TRUE) {
				CMN_PushStamp();
			}
		}
		else {
			CMN_PushStamp();
		}
#endif

	}

/*
** プリンタ受信のデュアル制限処理（SCN_Open()前にウェイトが入る）を入れていたときに、
** このスタートした後、ウェイトに入ると、クラッチを引かずにモータが回りっぱなしなる
** 次原稿のスタートはSCN_Open()で行い、最終ページの原稿排出はSCN_Close()で行っているので
** このスタートはいらない（意味がない）
** 1998/12/26 by T.Soneoka
*/
#if (0)
**	/* 停止している原稿をスタートさせます（Ｔｘモータスタート） */
**	StartTxMotor();
#endif
	return;
}
#endif

#if (PRO_STAMP == ENABLE)
/*************************************************************************
	module		:[済みスタンプ実行するかどうかチェック]
	function	:[
		1.蓄積Ｉｔｅｍと済み機器スタンプ設定からチェックします
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7014]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[SCN]
	date		:[1998/07/14]
	author		:[曽根岡拓]
*************************************************************************/
void SetStampExec(void)
{
	BOOL	rtn;

	rtn = FALSE;
	if ((SYS_DocumentStoreItem == SYS_MEM_TX_FILE)
	||	(SYS_DocumentStoreItem == SYS_MEM_BATCH_TX_FILE1)
	||	(SYS_DocumentStoreItem == SYS_MEM_BATCH_TX_FILE2)
	||	(SYS_DocumentStoreItem == SYS_MEM_BATCH_TX_FILE3)
	||	(SYS_DocumentStoreItem == SYS_MEM_BATCH_TX_FILE4)
	||	(SYS_DocumentStoreItem == SYS_MEM_BATCH_TX_FILE5)) {	/* メモリ送信/バッチ送信原稿1～5 */
		CMN_EvacuateStampSetting();
	} else {
		SYS_StampFlag = 0;
	}
}
#endif


#if (PRO_STAMP == ENABLE)
/*************************************************************************
	module		:[済みスタンプテストタスク]
	function	:[
		1.原稿をセット後、工場ファンクションのスタンプテストを起動
		2.ＳＦＩＮＥモードのモータスピードにて５ｃｍ間隔でスタンプを押します
		3.ＤＳ２がＯｆｆするまで押します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7014]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[SCN]
	date		:[1998/07/14]
	author		:[曽根岡拓]
*************************************************************************/
void StampTestTask(void)
{
	MESSAGE_t	StoreTaskMsg;				/* 送信メッセージ用エリア */

	ScannerEventStatus = 0;
	ScannerMode = SCANNER_STAMP_MODE;
	SYS_StampFlag = 1;		/* 済みスタンプ実行 */
	StampCount = 1;

	ExecutePushStamp = FALSE;	/* 最初の一発目がすぐに押されてしまう不具合 1999/03/31 by T.Soneoka */

	/* 送信モータの起動・スタートを行います */
	SetupTxMotor(TX_MOTOR_FINE_SCAN);
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
	PC_24V_On();
#endif
	CluchOn();
	StartTxMotor();
	
	/* ＤＳ２ＯＦＦするまで、一定間隔ごとにスタンプを押します */
	do {
		EnablePushStampEvent = TRUE;
		PushStamp();
		StartTxMotor(); /* 1998/12/26 by T.Soneoka */
		++StampCount;
	} while (CurrentPage->Position < DOC_POS_SCAN_FEEDOUT);

	/* 送信モータの開始 */
	StartTxMotor();
	wai_tsk(200);
	/* 送信モータの停止 */
	StopTxMotor();
	
	StoreTaskMsg.Item = FROM_SCN_STAMP_TEST_TASK;
	snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk(0xffff);
}
#else
void StampTestTask(void)
{
	wai_tsk(0xffff);
}
#endif

#if (PRO_STAMP == ENABLE)
/*************************************************************************
	module		:[スタンプ・テスト・タスク終了処理]
	function	:[
		1.原稿をセット後、工場ファンクションのスタンプテストを起動
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7014]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[SCN]
	date		:[1998/07/14]
	author		:[曽根岡拓]
*************************************************************************/
void ExitStampTestTask(void)
{
	exi_tsk();
}
#else
void ExitStampTestTask(void)
{
	exi_tsk();
}
#endif
