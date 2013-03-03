/*Copy Date: 1996/10/23 From \src\kobe\anzu\src\ By M.Kotani*/
/*---------------------------------------------------------------------------*/
/*	プロジェクト : Jun/RICE													 */
/*	ファイル名	 : MAN_EXEC.C												 */
/*	モジュール	 :															 */
/*				 : GetEmptyExecQueue()										 */
/*				 : CancelExecQueue(UBYTE, UBYTE)							 */
/*				 : ScanSetQueue(UBYTE, UBYTE, UBYTE, UWORD)					 */
/*				 : SetCommandToExec()										 */
/*				 : DecrementRedialTime()									 */
/*				 : GetNextExecNo()											 */
/*				 : SetExecQueueRedialCount(UWORD)							 */
/*				 : SetExecQueueRedialTime(UWORD)							 */
/*				 : ReleaseExecQueueArea(UWORD)								 */
/*				 : SetBatchCommandToExec()									 */
/*	作成者		 :															 */
/*	日	付		 :															 */
/*	概	要		 : 発信スケジューラー										 */
/*				 :															 */
/*	修正履歴	 : 1994/02/21 Y.M  第２ワンタッチ・短縮ダイアル対応			 */
/*				 : 1994/11/11 Y.M  バックアップがらみでｽﾃｰﾀｽ･ｾｯﾄの順番変更	 */
/*---------------------------------------------------------------------------*/

#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\man_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\stng_pro.h"
#include  "\src\atlanta\define\syscomf.h"
#include  "\src\atlanta\define\sysdial.h"
#include  "\src\atlanta\define\sysexec.h"
#include  "\src\atlanta\define\sysmcopy.h"
#include  "\src\atlanta\define\sysmax.h"
#include  "\src\atlanta\define\sysmemrx.h"
#include  "\src\atlanta\define\sys_stat.h"
#include  "\src\atlanta\define\mem_def.h"
#include  "\src\atlanta\define\std.h"
#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\ext_v\sys_data.h"

#if (PRO_CONTINUOUS_POLLING == ENABLE)
#include  "\src\atlanta\define\syscntpl.h"
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/21 */
#include "\src\atlanta\ext_v\fcm_data.h"
#endif		/* End of (defined (KEISATSU)) */

static UBYTE  next_com_num = 0;	/* 初期化必要 */
static UBYTE  next_batch_com_num = 0;	/* 初期化必要 */

/**　Module Header For CIM-E ********************************************
		module		:	[SYB_ExecQueue[]に空き領域があるかどうかを調べる
						]
		function	:	[]
		return		:	[
						０：空き領域無し
						１：空き領域有り
						]
		common		:	[
			SYB_ExecQueueWritePoint	: 実行待ちファイルの展開位置
			SYB_ExecQueueReadPoint	: 実行待ちファイルの実行位置
			SYB_ExecQueue[]			: 発信スケジューラー
		]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/2/1]
		author		:	[川崎真史]
************************************************************************/
UWORD GetEmptyExecQueue( void )
{
	UWORD  i;
	UWORD	backup_write_point;

	backup_write_point = SYB_ExecQueueWritePoint;	/* NEW_JUDGE 1997/10/29 */
	for (i = 0, SYB_ExecQueueWritePoint = SYB_ExecQueueReadPoint; i < SYS_EXEC_QUEUE_MAX; i++) {
		SYB_ExecQueueWritePoint++;
		if (SYB_ExecQueueWritePoint >= SYS_EXEC_QUEUE_MAX) {
			SYB_ExecQueueWritePoint = 0;
		}
		if (SYB_ExecQueue[SYB_ExecQueueWritePoint].Status == SYS_EXEC_EMPTY) {
			return(1); /* 空き領域有り */
		}
	}
	SYB_ExecQueueWritePoint = backup_write_point;	/* NEW_JUDGE 1997/10/29 */
	return(0); /* 空き領域無し */
}

/**　Module Header For CIM-E ********************************************
		module		:	[指定されたコマンドＮｏで通常のコマンド又は一括コマンドをキャンセル
						]
		function	:	[]
		return		:	[]
		common		:	[
			SYB_ExecQueue			: 発信スケジューラ～
		]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/1]
		author		:	[川崎真史]
************************************************************************/
void CancelExecQueue(
UBYTE CommandType,			/* 通常コマンド又は一括コマンド */
UBYTE CancelCommandNo )		/* キャンセルするコマンドの番号 */
{
	UWORD  i;
	struct SYS_ExecQueueData_t *ep;

	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) {
		ep = &SYB_ExecQueue[i];
		if ((ep->Status != SYS_EXEC_EMPTY) && (ep->Number.Command == CancelCommandNo) && (ep->Kind == CommandType)) {
			ep->Status = SYS_EXEC_EMPTY;
		}
	}
	return;
}

/**　Module Header For CIM-E ********************************************
		module		:	[発信スケジューラ～のデータセット]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/14]
		author		:	[川崎真史]
************************************************************************/
UWORD ScanSetQueue(
UBYTE CommandType,	/* 通常コマンド又は一括コマンド */
UBYTE CommandNo,	/* File No */
UBYTE dial_item,
UWORD dial_suffix )
{
	struct SYS_CommandData_t *cp;	/* 通常コマンドファイル用ポインター */
	struct SYS_ExecQueueData_t *ep;	/* ExecQueue用ポインター */
#if (PRO_BATCH_TX == ENABLE)
	struct SYS_BatchTxData_t *bp;		/* 一括送信コマンドファイル用ポインター */
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/29 */
	struct SYS_CommandKeisatsu_t	*kp;
#endif		/* End of (defined (KEISATSU)) */

	if (!GetEmptyExecQueue()) {
		CancelExecQueue(CommandType, CommandNo);
		return(0);
	}

	cp = &SYB_CommandFile[CommandNo];
	ep = &SYB_ExecQueue[SYB_ExecQueueWritePoint];

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/29 */
	kp = &SYB_ExecQueueKeisatsu[SYB_ExecQueueWritePoint];
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_BATCH_TX == ENABLE)
	bp = &SYB_BatchTxFile[CommandNo];
#endif
	ep->Kind = CommandType;	/* 通常コマンド又は一括コマンドを登録 */
	/* ep->Status = SYS_EXEC_WAITING;	順番変更 1994/11/11 Y.Murata */
	ep->Number.Command = CommandNo;
	ep->RedialCount = (UBYTE)(CHK_RedialCount() + 0x01);
	ep->RedialTime = 0;
	ep->Mode = 0;
	ep->StartTime = 0;
	ep->TotalTime = 0;
	ep->Result = 0;
	/****************** By S.K
	ep->ErrorPhase = 0;
	ep->ErrorNumber = 0;
	**************************/
	ep->Page = 0;
	ep->Option = 0;						/* 付加機能 ｶﾊﾞｰﾍﾟｰｼﾞ送信済みｸﾘｱ 1994/10/11 Y.Murata */

	ep->StackNumber = 0xFF;		/* 回線番号 */

	ep->ExecDial.Item = dial_item;
	switch (dial_item)	{
	case SYS_DIRECT_DIAL:
		ep->ExecDial.ExecNumber.Command = (UBYTE)dial_suffix;
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/29 */
		kp->Line = SYB_CommandKeisatsu[CommandNo].Line;
		kp->Scramble = SYB_CommandKeisatsu[CommandNo].Scramble;
		kp->Senyo = SYB_CommandKeisatsu[CommandNo].Senyo;
		
		break;
#endif		/* End of (defined (KEISATSU)) */
	case SYS_ONETOUCH_DIAL:
		ep->ExecDial.ExecNumber.Onetouch = (UBYTE)dial_suffix;
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/29 */
 		if (SYB_OnetouchDial[dial_suffix].Keisatsu & SYS_KEISATSU_KEIDEN) {
			kp->Line = SYS_LINE_KEIDEN;
		}
		else if (SYB_OnetouchDial[dial_suffix].Keisatsu & SYS_KEISATSU_KANYU) {
			kp->Line = SYS_LINE_KANYU;
		}
		else {
			kp->Line = SYB_CommandKeisatsu[CommandNo].Line;
		}
		
		if (SYB_OnetouchDial[dial_suffix].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON) {
			kp->Scramble = TRUE;
		}
		else if (SYB_OnetouchDial[dial_suffix].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF) {
			kp->Scramble = FALSE;
		}
		else {
			kp->Scramble = SYB_CommandKeisatsu[CommandNo].Scramble;
		}
		
		if (kp->Scramble == TRUE) {
			if (SYB_OnetouchDial[dial_suffix].Keisatsu & SYS_KEISATSU_SENYO) {
				kp->Senyo = TRUE;
			}
			else if (SYB_OnetouchDial[dial_suffix].Keisatsu & SYS_KEISATSU_KYOTSU) {
				kp->Senyo = FALSE;
			}
			else {
				kp->Senyo = SYB_CommandKeisatsu[CommandNo].Senyo;
			}
		}
		else {
			kp->Senyo = FALSE;
		}
#endif		/* End of (defined (KEISATSU)) */
		break;
	case SYS_SPEED_DIAL:
		ep->ExecDial.ExecNumber.Speed = (UWORD)dial_suffix;
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/29 */
 		if (SYB_SpeedDial[dial_suffix].Keisatsu & SYS_KEISATSU_KEIDEN) {
			kp->Line = SYS_LINE_KEIDEN;
		}
		else if (SYB_SpeedDial[dial_suffix].Keisatsu & SYS_KEISATSU_KANYU) {
			kp->Line = SYS_LINE_KANYU;
		}
		else {
			kp->Line = SYB_CommandKeisatsu[CommandNo].Line;
		}
		
		if (SYB_SpeedDial[dial_suffix].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON) {
			kp->Scramble = TRUE;
		}
		else if (SYB_SpeedDial[dial_suffix].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF) {
			kp->Scramble = FALSE;
		}
		else {
			kp->Scramble = SYB_CommandKeisatsu[CommandNo].Scramble;
		}
		
		if (kp->Scramble == TRUE) {
			if (SYB_SpeedDial[dial_suffix].Keisatsu & SYS_KEISATSU_SENYO) {
				kp->Senyo = TRUE;
			}
			else if (SYB_SpeedDial[dial_suffix].Keisatsu & SYS_KEISATSU_KYOTSU) {
				kp->Senyo = FALSE;
			}
			else {
				kp->Senyo = SYB_CommandKeisatsu[CommandNo].Senyo;
			}
		}
		else {
			kp->Senyo = FALSE;
		}
#endif		/* End of (defined (KEISATSU)) */
		break;
	default:
		ep->Status = SYS_EXEC_WAITING;
		return(0);	/* もしここを通ればバグ */
	}
	ep->Status = SYS_EXEC_WAITING;		/* 1994/11/11 Y.Murata 順番変更 */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/19 Y.Murata for KAKI */
	if (SYS_QucikTxStopQueueNo != 0xFFFF) {
		if ((UWORD)SYS_QucikTxStopQueueNo == (UWORD)SYB_ExecQueueWritePoint) {
			SYS_QucikTxStopQueueNo = 0xFFFF;
		}
	}
#endif

	return(1);
}


/* 警察FAX Added by SMuratec K.W.Q 2005/09/21
** 自動送信の場合、警察属性はFcm_ExecutingS1info 構造体にセットする
*/
#if defined (KEISATSU)
void GetExecutingS1Info(UBYTE CurrentExecQueueNo)
{
/*	SetPartnerAbility();	*/				/** 短縮／ワンタッチ個別データ取得 */
	switch (SYB_ExecQueue[SYS_CurrentExecQueueNo].ExecDial.Item) {	/** ダイアル種別判定 */
	/*================*/
	/*= 短縮ダイアル =*/
	/*================*/
	case SYS_SPEED_DIAL	  :			/** 短縮ダイアル */
		SpeedDialPosition = SYB_ExecQueue[SYS_CurrentExecQueueNo].ExecDial.ExecNumber.Speed;

		if (SpeedDialPosition < SYS_SPEED_DIAL_MAX) {	/** 第１短縮ダイアル */

			if (SYB_SpeedDial[SpeedDialPosition].Keisatsu & SYS_KEISATSU_KEIDEN) {
				SYS_InternalLineNumber = SYS_EXT_LINE_COM;
			}
			else if (SYB_SpeedDial[SpeedDialPosition].Keisatsu & SYS_KEISATSU_KANYU) {
				SYS_InternalLineNumber = SYS_STD_LINE_COM;
			}
			else {
				SYS_InternalLineNumber = SYB_CommandKeisatsu[SYB_ExecQueue[CurrentExecQueueNo].Number.Command].Line;
			}
			
			FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;
			
			if (SYB_SpeedDial[SpeedDialPosition].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON) {
				FCM_ExecutingS1Info.Available = TRUE;
			}
			else if (SYB_SpeedDial[SpeedDialPosition].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF) {
				FCM_ExecutingS1Info.Available = FALSE;
			}
			else {
				FCM_ExecutingS1Info.Available = SYB_CommandKeisatsu[SYB_ExecQueue[CurrentExecQueueNo].Number.Command].Scramble;
			}

			if (CMN_CheckScrambleSwOn() == FALSE) { /* 背面スイッチがOFFの場合 */
				FCM_ExecutingS1Info.Available = FALSE;
				FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
			}
			else {
				if (SYB_SpeedDial[SpeedDialPosition].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON) {
					FCM_ExecutingS1Info.Available = TRUE;
				}
				else if (SYB_SpeedDial[SpeedDialPosition].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF) {
					FCM_ExecutingS1Info.Available = FALSE;
				}
				else {
					FCM_ExecutingS1Info.Available = SYB_CommandKeisatsu[SYB_ExecQueue[CurrentExecQueueNo].Number.Command].Scramble;
				}
			
				if (SYB_SpeedDial[SpeedDialPosition].Keisatsu & SYS_KEISATSU_KYOTSU) {
					FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
				}
				else if (SYB_SpeedDial[SpeedDialPosition].Keisatsu & SYS_KEISATSU_SENYO) {
					FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
				}
				else {
					FCM_ExecutingS1Info.Method = SYB_CommandKeisatsu[SYB_ExecQueue[CurrentExecQueueNo].Number.Command].Senyo;
				}
			}
		}
		break;

	/*========================*/
	/*= ワンタッチ・ダイアル =*/
	/*========================*/
	case SYS_ONETOUCH_DIAL:
		OnetouchDialPosition = SYB_ExecQueue[SYS_CurrentExecQueueNo].ExecDial.ExecNumber.Onetouch;

		if (SYB_OnetouchDial[OnetouchDialPosition].Keisatsu & SYS_KEISATSU_KEIDEN) {
			SYS_InternalLineNumber = SYS_EXT_LINE_COM;
		}
		else if (SYB_OnetouchDial[OnetouchDialPosition].Keisatsu & SYS_KEISATSU_KANYU) {
			SYS_InternalLineNumber = SYS_STD_LINE_COM;
		}
		else {
			SYS_InternalLineNumber = SYB_CommandKeisatsu[SYB_ExecQueue[CurrentExecQueueNo].Number.Command].Line;
		}
		
		FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;
		
		
		if (CMN_CheckScrambleSwOn() == FALSE) { /* 背面スイッチがOFFの場合 */
			FCM_ExecutingS1Info.Available = FALSE;
			FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
		}
		else {
			if (SYB_OnetouchDial[OnetouchDialPosition].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON) {
				FCM_ExecutingS1Info.Available = TRUE;
			}
			else if (SYB_OnetouchDial[OnetouchDialPosition].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF) {
				FCM_ExecutingS1Info.Available = FALSE;
			}
			else {
				FCM_ExecutingS1Info.Available = SYB_CommandKeisatsu[SYB_ExecQueue[CurrentExecQueueNo].Number.Command].Scramble;
			}

			if (SYB_OnetouchDial[OnetouchDialPosition].Keisatsu & SYS_KEISATSU_KYOTSU) {
				FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
			}
			else if (SYB_OnetouchDial[OnetouchDialPosition].Keisatsu & SYS_KEISATSU_SENYO) {
				FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
			}
			else {
				FCM_ExecutingS1Info.Method = SYB_CommandKeisatsu[SYB_ExecQueue[CurrentExecQueueNo].Number.Command].Senyo;
			}
		}
		break;

	/*================*/
	/*= 直接ダイアル =*/
	/*================*/
	case SYS_DIRECT_DIAL  :
		SYS_InternalLineNumber = SYB_CommandKeisatsu[SYB_ExecQueue[CurrentExecQueueNo].Number.Command].Line;

		FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;
		
		if (CMN_CheckScrambleSwOn() == FALSE) { /* 背面スイッチがOFFの場合 */
			FCM_ExecutingS1Info.Available = FALSE;
			FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
		}
		else {
			FCM_ExecutingS1Info.Available = SYB_CommandKeisatsu[SYB_ExecQueue[CurrentExecQueueNo].Number.Command].Scramble;
			FCM_ExecutingS1Info.Method = SYB_CommandKeisatsu[SYB_ExecQueue[CurrentExecQueueNo].Number.Command].Senyo;
		}
		break;
	default :
		/* ｾｯﾄ･ｴﾗｰ･ｺｰﾄﾞ　*/
		break;
	}
}
#endif		/* End of (defined (KEISATSU)) */

/**　Module Header For CIM-E ********************************************
		module		:	[通信予約ファイルからの発信スケジューラーの展開]
		function	:	[]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/14]
		author		:	[川崎真史]
************************************************************************/
void SetCommandToExec(void)
{
	UBYTE	i;
	UBYTE	onetouch_pos;
	UBYTE	speed_pos;
	UBYTE	group_pos;
	UBYTE	direct_pos;
	UWORD	set_count;
	UDWORD	d;
	struct SYS_CommandData_t *cp;
	struct SYS_DialData_t *dp;

	set_count = 0;
	for (i = 0; i < SYS_COM_FILE_MAX; i++)	{		/** 通信予約数の間 Loop */

		set_count = 0;	/* 1997/12/19 */

		if (++next_com_num >= SYS_COM_FILE_MAX)
			next_com_num = 0;

		cp = &SYB_CommandFile[next_com_num];		/** 指定コマンドファイル */

		if ((cp->Status == SYS_CMD_WAITING) &&
/*			(SYB_CurrentTime > cp->ExecTime)) {		/** 実行時刻のコマンド有り *//* By H.Y 1994/08/19 */
			(SYB_CurrentTime >= cp->ExecTime)) {	/** 実行時刻のコマンド有り */

			/* 実行時刻に達したコマンドあり */

			/* ↓●ICHOU変更 by T.Soneoka 1996/05/09 */
			/* ワンタッチ・ダイアル */
			for (onetouch_pos = 0; onetouch_pos < SYS_ONETOUCH_MAX; onetouch_pos++) {
				if ((SYB_OnetouchDial[onetouch_pos].Dial[0] & 0xF0) == 0xF0) {
					continue;
				}
				dp = &cp->DialNumber;
				if (CMN_CheckBitAssign((UBYTE *)dp->Onetouch, onetouch_pos) == TRUE) {
					if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_ONETOUCH_DIAL, (UWORD)onetouch_pos)) {
						return;	 /* 「ExecQueue」に空きなし */
					}
					set_count++;
				}
				else if (SYB_OnetouchDial[onetouch_pos].Group) {
					d = 0x00000001;
					for (group_pos = 0; group_pos < SYS_GROUP_NUMBER_MAX; group_pos++) {
						if (SYB_OnetouchDial[onetouch_pos].Group & d) {
							if (dp->Group & d) {
								if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_ONETOUCH_DIAL, (UWORD)onetouch_pos)) {
									return;
								}
								set_count++;
								break;
							}
						}
						d <<= 1;
					}
				}
			}	/* End of For SYS_ONETOUCH_MAX */
			/* 短縮ダイアル */
			for (speed_pos = 0; speed_pos < SYS_SPEED_DIAL_MAX; speed_pos++)  {
				if ((SYB_SpeedDial[speed_pos].Dial[0] & 0xF0) == 0xF0) {
					continue;
				}
				dp = &cp->DialNumber;
				if (CMN_CheckBitAssign((UBYTE *)dp->Speed, speed_pos) == TRUE) {
					if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_SPEED_DIAL, (UWORD)speed_pos)) {
						return;
					}
					set_count++;
				}
				else if (SYB_SpeedDial[speed_pos].Group) {
					d = 0x00000001;
					for (group_pos = 0; group_pos < SYS_GROUP_NUMBER_MAX; group_pos++) {
						if (SYB_SpeedDial[speed_pos].Group & d) {
							if (dp->Group & d) {
								if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_SPEED_DIAL, (UWORD)speed_pos)) {
									return;
								}
								set_count++;
								break;
							}
						}
						d <<= 1;
					}
				}
			}
			/* 直接ダイアル */
			dp = &cp->DialNumber;
			for (direct_pos = 0; direct_pos < SYS_COM_DIRECT_DIAL_MAX; direct_pos++)  {
				if ((dp->Direct[direct_pos][0] & 0xF0) == 0xF0) {
					continue;
				}
				if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_DIRECT_DIAL, direct_pos)) {
					return;
				}
				set_count++;
			}
			if (set_count == 0)	 {	/* CHECK ILLEGAL COMMAND SET */
				/* Nov.18,1994 CMN_ClearCommandArea(SYS_COMMAND_TRX, i); BUG *//* TBD */
				/* Nov.18,1994 CMN_ClearCommandArea(SYS_COMMAND_TRX, next_com_num); BUG FIX */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Murata for KAKI */
				/*
				 * 通信予約されて、実行キューに展開される前に
				 * ワンタッチ／短縮ダイアルが消去された場合の処理
				*/
				for (onetouch_pos = 0; onetouch_pos < SYS_ONETOUCH_MAX; onetouch_pos++) {
					dp = &cp->DialNumber;
					if (CMN_CheckBitAssign((UBYTE *)dp->Onetouch, onetouch_pos) == TRUE) {
						if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_ONETOUCH_DIAL, (UWORD)onetouch_pos)) {
							return;	 /* 「ExecQueue」に空きなし */
						}
						set_count++;
					}
				}	/* End of For SYS_ONETOUCH_MAX */

				/* 短縮ダイアル */
				for (speed_pos = 0; speed_pos < SYS_SPEED_DIAL_MAX; speed_pos++)  {
					dp = &cp->DialNumber;
					if (CMN_CheckBitAssign((UBYTE *)dp->Speed, speed_pos) == TRUE) {
						if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_SPEED_DIAL, (UWORD)speed_pos)) {
							return;
						}
						set_count++;
					}
				}

				if (set_count == 0) {
					/* まだキューに展開できてないってことは、グループ指定 */
					/* むりやりやる～ */
					if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_DIRECT_DIAL, 0)) {
						return;
					}
					SYB_ExecQueue[SYB_ExecQueueWritePoint].Result = 0x0C06;
					SYB_ExecQueue[SYB_ExecQueueWritePoint].Status = SYS_EXEC_ERROR;
				}

#else
/*	#if defined(POPLAR_F) By Y.Suzuki 2002/08/13 */
/*	V851　#if defined(POPLAR_F) || (defined(POPLAR_H) && defined(JP0)) ATLANTA共通にする。*/
		/* 1999/11/29 Y.Murata
		 * Ｌ４００後継は、ワンタッチ・短縮で予約した時に、予約中にそのワンタッチ・短縮を消された時を対応します。
		*/
				/*
				 * 通信予約されて、実行キューに展開される前に
				 * ワンタッチ／短縮ダイアルが消去された場合の処理
				*/
				for (onetouch_pos = 0; onetouch_pos < SYS_ONETOUCH_MAX; onetouch_pos++) {
					dp = &cp->DialNumber;
					if (CMN_CheckBitAssign((UBYTE *)dp->Onetouch, (UWORD)onetouch_pos) == TRUE) {
						if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_ONETOUCH_DIAL, (UWORD)onetouch_pos)) {
							return;	 /* 「ExecQueue」に空きなし */
						}
						set_count++;
					}
				}	/* End of For SYS_ONETOUCH_MAX */

				/* 短縮ダイアル */
				for (speed_pos = 0; speed_pos < SYS_SPEED_DIAL_MAX; speed_pos++)  {
					dp = &cp->DialNumber;
					if (CMN_CheckBitAssign((UBYTE *)dp->Speed, speed_pos) == TRUE) {
						if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_SPEED_DIAL, (UWORD)speed_pos)) {
							return;
						}
						set_count++;
					}
				}

				if (set_count == 0) {
					/* まだキューに展開できてないってことは、グループ指定 */
					/* むりやりやる～ */
					if (!ScanSetQueue(SYS_COMMAND_TRX, next_com_num, SYS_DIRECT_DIAL, 0)) {
						return;
					}
					SYB_ExecQueue[SYB_ExecQueueWritePoint].Result = 0x0C06;	/* D.0.6(Dial Empty Error) */
					SYB_ExecQueue[SYB_ExecQueueWritePoint].Status = SYS_EXEC_ERROR;
				}
	
	/**#else
				return;
	#endif**/
#endif
			}
			cp->Status = SYS_CMD_EXECUTE;

#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
			SYB_CommandStatus[next_com_num] = SYS_CMD_EXECUTE;
#endif
		}
	}	/* End of For SYS_COM_FILE_MAX */
	return;
}
/**　Module Header For CIM-E ********************************************
		module		:	[発信スケジューラ～リダイアル時間を1分減算する]
		function	:	[]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/14]
		author		:	[川崎真史]
************************************************************************/
void DecrementRedialTime(void)
{
	struct SYS_ExecQueueData_t *ep;
	WORD	 i;

#if (PRO_NEW_JATE == ENABLE) /* 条件を変えます By M.Maeda 2002/10/21 *//*#if defined(POPLAR_F)	/* 2000/01/14 Y.Murata RIDIAL_DISP_0_MINITE */
	for(i = 0; i < SYS_EXEC_QUEUE_MAX; i++) {
		ep = &SYB_ExecQueue[i];
		if(ep->Status != SYS_EXEC_EMPTY) {
			if(ep->RedialTime != 0xFF) {
				if(ep->RedialTime > 0) {
					(ep->RedialTime)--;
				}
			}
		}
	}
#else
	for(i = 0; i < SYS_EXEC_QUEUE_MAX; i++) {
		ep = &SYB_ExecQueue[i];
		if(ep->RedialTime > 0) {
			(ep->RedialTime)--;
		}
	}
#endif
}
/**　Module Header For CIM-E ********************************************
		module		:	[実行すべき発信スケジューラ～の番号を取得]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/14]
		author		:	[川崎真史]
************************************************************************/
/*
 * 実行すべき（faxcom を起動する） ExecQueue の番号を得る
 */
UWORD GetNextExecNo(void)
{
	WORD	 i;
	struct SYS_ExecQueueData_t *ep;
	struct SYS_CommandData_t *cp;


	/* ダイレクトスキャナ送信とダイレクトポーリングは、優先通信 */
	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++)  { /* ExecQueueの0-SYS_EXEC_QUEUE_MAXまで */
		ep = &SYB_ExecQueue[i];
		if (((ep->Status == SYS_EXEC_WAITING) || (ep->Status == SYS_EXEC_FORWARD_WAITING)) /* ｺﾏﾝﾄﾞ発呼待ちか,転送発呼待ちで */
#if (PRO_NEW_JATE == ENABLE) /* 条件を変えます By M.Maeda 2002/10/21 *//*#if defined(POPLAR_F)	/* 2000/01/14 Y.Murata RIDIAL_DISP_0_MINITE */
			&& ((ep->RedialTime <= 0) || (ep->RedialTime == 0xFF))
#else
			&& (ep->RedialTime <= 0)
#endif
			&& (ep->Kind == SYS_COMMAND_TRX))  { /* 既に時間が経過していれば */
			cp = &SYB_CommandFile[ep->Number.Command];

			if ((cp->Option.Item == SYS_SCANNER_TX) ||
				(cp->Option.Item == SYS_DELAYED_SCANNER_TX) ||
				(cp->Option.Item == SYS_SCANNER_SECURE_TX) ||
				(cp->Option.Item == SYS_SCANNER_RELAY_BROADCAST) ||
				(cp->Option.Item == SYS_SCANNER_SUB_ADDRESS_TX)) {

#if (PRO_PREHEAT == ENABLE)
				/* 寒冷地 PreHeat  1999/01/06 s.takeuchi */
				if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {
					/* プリヒート中のスキャナ送信は無視する(他のコマンドを検索) */
					break;
				}
#endif

				return(i);
			}
#if (0)	/* 1997/10/06 s.takeuchi ->1997/10/24 銀杏移植*/
//スキャナ送信がマルチ検索ポーリングなどの後に予約されると後回しになるため
//ここではスキャナ送信のみ最優先で検索する
//			else if (((cp->Option.Item == SYS_POLLING_RX) ||
//					  (cp->Option.Item == SYS_DB_POLLING_RX) ||
//					  (cp->Option.Item == SYS_SELECT_POLLING_RX)) &&
//					 CMN_CheckPollingReceiveEnable()) {
//				return(i);
//			}
//			else {
//				continue;
//			}
#endif
		}
	}
	/*
	** 一宛先の(検索)ポーリング受信は通常のコマンド送信よりも優先する
	**   1997/10/06 s.takeuchi
	*/
	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++)  { /* ExecQueueの0-SYS_EXEC_QUEUE_MAXまで */
		ep = &SYB_ExecQueue[i];
		if (((ep->Status == SYS_EXEC_WAITING)
			|| (ep->Status == SYS_EXEC_FORWARD_WAITING)) /* コマンド発呼待ちか,転送発呼待ちで */
#if (PRO_NEW_JATE == ENABLE) /* 条件を変えます By M.Maeda 2002/10/21 *//*#if defined(POPLAR_F)	/* 2000/01/14 Y.Murata RIDIAL_DISP_0_MINITE */
		&& ((ep->RedialTime <= 0) || (ep->RedialTime == 0xFF))
#else
		&& (ep->RedialTime <= 0)
#endif
		&& (ep->Kind == SYS_COMMAND_TRX))  { /* 既に時間が経過していれば */
			cp = &SYB_CommandFile[ep->Number.Command];

			if (((cp->Option.Item == SYS_POLLING_RX)
				|| (cp->Option.Item == SYS_SELECT_POLLING_RX)	/* Ｆコードが見れていない By O.Kimoto 1998/05/26 */
				|| (cp->Option.Item == SYS_DB_POLLING_RX))
			&&	CMN_CheckPollingReceiveEnable()
			&&	!CMN_CheckBroadcastCommand(i)) {	/* 一宛先ポーリングで受信可能 */
				return(i);
			}
		}
	}


	/* 通常コマンド及び一括送信を検索する */
	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++)  {
		if (++SYB_ExecQueueReadPoint == SYS_EXEC_QUEUE_MAX) {
			SYB_ExecQueueReadPoint = 0;
		}
		ep = &SYB_ExecQueue[SYB_ExecQueueReadPoint];
		if (((ep->Status == SYS_EXEC_WAITING) || (ep->Status == SYS_EXEC_FORWARD_WAITING))
#if (PRO_NEW_JATE == ENABLE) /* 条件を変えます By M.Maeda 2002/10/21 *//*#if defined(POPLAR_F)	/* 2000/01/14 Y.Murata RIDIAL_DISP_0_MINITE */
			&& ((ep->RedialTime <= 0) || (ep->RedialTime == 0xFF))) {
#else
			&& (ep->RedialTime <= 0)) {
#endif
			if (ep->Kind == SYS_COMMAND_TRX) {
				cp = &SYB_CommandFile[ep->Number.Command];
#if (0) /* ICHOUに合わせて下のifブロックへ変更します T.Nose 1999/01/28 */
//				if (!((cp->Option.Item == SYS_POLLING_RX) ||
//				  (cp->Option.Item == SYS_SEQUENTIAL_POLLING) ||	/* 1997/10/06 s.takeuchi */
//				  (cp->Option.Item == SYS_SELECT_POLLING_RX) ||		/* Ｆコードが見れていない By O.Kimoto 1998/05/26 */
//				  (cp->Option.Item == SYS_DB_POLLING_RX)) ||
///*					CMN_CheckMemoryReceiveEnable())	 @	*/
//					CMN_CheckMultiLineReceiveEnable()) {
//					return(SYB_ExecQueueReadPoint);
//				}
#endif
				if ((cp->Option.Item == SYS_POLLING_RX)
				||	(cp->Option.Item == SYS_SEQUENTIAL_POLLING)
				||	(cp->Option.Item == SYS_SELECT_POLLING_RX)
				||	(cp->Option.Item == SYS_DB_POLLING_RX)) {
					if (CMN_CheckPollingReceiveEnable()) {
						return(SYB_ExecQueueReadPoint);
					}
				}
#if (PRO_PREHEAT == ENABLE)
				/* 寒冷地 PreHeat  1999/01/06 s.takeuchi */
				else if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT)
				&&	((cp->Option.Item == SYS_SCANNER_TX)
				  || (cp->Option.Item == SYS_DELAYED_SCANNER_TX)
				  || (cp->Option.Item == SYS_SCANNER_SECURE_TX)
				  || (cp->Option.Item == SYS_SCANNER_RELAY_BROADCAST))) {
					/* プリヒート中のスキャナ送信は無視する(他のコマンドを検索) */
				}
#endif
				else {
					return(SYB_ExecQueueReadPoint);
				}
			}
			else if (ep->Kind == SYS_BATCH_TX) {	/* 1997/10/28 */
				return(SYB_ExecQueueReadPoint);
			}
		}
	}

#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング追加 1996/10/17 Eguchi */
	/* 連続ポーリングコマンド(特殊仕様)は最低優先順位とする */
	if (CMN_CheckPollingReceiveEnable() == TRUE) { /** ポーリング受信可能 */
		for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) { /** キューの先頭から最後まで検索 */
			ep = &SYB_ExecQueue[i];
			if (((ep->Status == SYS_EXEC_WAITING) || (ep->Status == SYS_EXEC_FORWARD_WAITING)) 
			&&	(ep->Kind == SYS_CONTINUOUS_POLLING)) { /** 実行待ちの連続ポーリングコマンドあり */
				return (i);
			}
		}
	}
	
#endif

	return(SYS_EXEC_QUEUE_MAX);	/* SYB_ExecQueueReadPoint の値はそのまま（一周回るから） */
}

/**　Module Header For CIM-E ********************************************
		module		:	[発信スケジューラ～リダイアル回数を減算する]
		function	:	[]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/14]
		author		:	[川崎真史]
************************************************************************/
UBYTE SetExecQueueRedialCount(
UWORD	ExecQueueNumber )
{
	SYB_ExecQueue[ExecQueueNumber].RedialCount--;
	if (SYB_ExecQueue[ExecQueueNumber].RedialCount){
		return(1);
	}
	else {
		/*	転送可能な場合は、再ﾀﾞｲﾔﾙｶｳﾝﾄをｾｯﾄする必要有り	*/
		return(0);
	}
}

/**　Module Header For CIM-E ********************************************
		module		:	[発信スケジューラ～リダイアル時間を1分減算する]
		function	:	[]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/14]
		author		:	[川崎真史]
************************************************************************/
void SetExecQueueRedialTime(
UWORD	ExecQueueNumber )
{
	SYB_ExecQueue[ExecQueueNumber].RedialTime = (UBYTE)(CHK_RedialInterval() + 0x01); /* TBD */
}


/**　Module Header For CIM-E ********************************************
		module		:	[発信スケジューラ～エリア開放]
		function	:	[]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/14]
		author		:	[川崎真史]
************************************************************************/
void ReleaseExecQueueArea(
UWORD	ExecQueueNumber
)
{
	SYB_ExecQueue[ExecQueueNumber].Status = SYS_EXEC_EMPTY;
}
/**　Module Header For CIM-E ********************************************
		module		:	[一括送信ファイルからの発信スケジューラ～の展開]
		function	:	[]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/14]
		author		:	[川崎真史]
************************************************************************/
#if (PRO_BATCH_TX == ENABLE)
UDWORD batch_exectime = 0;
void SetBatchCommandToExec(void)
{
	UBYTE	i, j;
	UBYTE	a;				/* Onetouch offset */
	UWORD	b;				/* Speed offset */
	UWORD	m, set_count;
	UDWORD	d;
	struct SYS_BatchTxData_t *cp;
	struct SYS_BatchTxDialData_t *dp;

	set_count = 0;
	for (i = 0; i < SYS_BATCH_FILE_MAX; i++) {
		/* if (++next_batch_com_num >= SYS_COM_FILE_MAX) */
		if (++next_batch_com_num >= SYS_BATCH_FILE_MAX) /** BUG 7/6/1994 */
			next_batch_com_num = 0;

		cp = &SYB_BatchTxFile[next_batch_com_num];
		if ((cp->Status == SYS_CMD_WAITING) && (SYB_CurrentTime >= cp->ExecTime)) { /** 実行時刻に達したバッチ・コマンドあり *//* By H.Y 1994/08/20 */
			/*----------------------*/
			/* ワンタッチ・ダイアル */
			/*----------------------*/
			for (j = 0; j < SYS_ONETOUCH_MAX; j++) {

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Murata for KAKI */
				/* むりからキュー展開、通信エラーでとめる */
#else
	#if defined(POPLAR_F)
	#else
				/*************以下の行を追加　1996/04/20 Eguchi *********/
				if ((SYB_OnetouchDial[j].Dial[0] & 0xF0) == 0xF0) { /** 登録されていない */
					continue;
				}
				/*************追加ここまで　1996/04/20 Eguchi ************/
	#endif
#endif
				dp = &cp->DialNumber[0];
				if (dp->Item == SYS_ONETOUCH_DIAL) {
					a = dp->FaxNumber.Onetouch;
					if (a == j) {
						if (!ScanSetQueue(SYS_BATCH_TX, next_batch_com_num, SYS_ONETOUCH_DIAL, (UWORD)a))
							return;	 /* 「ExecQueue」に空きなし */
						set_count++;
						break;
					}
				}
				if (dp->Item == SYS_GROUP_DIAL) {
					if (dp->FaxNumber.Group == 0) {
						d = 0xFFFFFFFF;
					}
					else  {
						d = 0x00000001;
						for (m = 1; m < dp->FaxNumber.Group; m++) {
							d <<= 1;
						}
					}
/* //					if (SYB_OnetouchDial[j].DialData.Onetouch.Group & d) { */
					if (SYB_OnetouchDial[j].Group & d) {

						/* 第２ワンタッチのオフセットを通番としてセット */
						a = (UBYTE)(j + SYS_2ND_ONETOUCH_MAX);

						if (!ScanSetQueue(SYS_BATCH_TX, next_batch_com_num, SYS_ONETOUCH_DIAL, (UWORD)a)) {
							return;
						}
						set_count++;
						break;
					}
				}
			}
			/*--------------*/
			/* 短縮ダイアル */
			/*--------------*/
			for (j = 0; j < SYS_SPEED_DIAL_MAX; j++)  {
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Murata for KAKI */
				/* むりからキュー展開、通信エラーでとめる */
#else
	#if defined(POPLAR_F)
	#else
				if ((SYB_SpeedDial[j].Dial[0] & 0xF0) == 0xF0) {
					continue;
				}
	#endif
#endif
				dp = &cp->DialNumber[0];
				if (dp->Item == SYS_SPEED_DIAL) {
					b = dp->FaxNumber.Speed;
					if ( b == (UWORD)j ) {
						if (!ScanSetQueue(SYS_BATCH_TX, next_batch_com_num, SYS_SPEED_DIAL, b)) {
							return;
						}
						set_count++;
						break;
					}
				}
				if (dp->Item == SYS_GROUP_DIAL) {
					if (dp->FaxNumber.Group == 0) {
						d = 0xFFFFFFFF;
					}
					else {
						d = 0x00000001;
						for (m = 1; m < dp->FaxNumber.Group; m++) {
							d <<= 1;
						}
					}
					if (SYB_SpeedDial[j].Group & d) {
						b = (UWORD)j;
						if (!ScanSetQueue(SYS_BATCH_TX, next_batch_com_num, SYS_SPEED_DIAL, b)) {
							return;
						}
						set_count++;
						break;
					}
				}
			}
			/*--------------*/
			/* 直接ダイアル */
			/*--------------*/
			if (cp->DialNumber[0].Item == SYS_DIRECT_DIAL)	{
				/* if (!ScanSetQueue(SYS_BATCH_TX, next_batch_com_num, SYS_DIRECT_DIAL, j)) {	  1994/08/10 Y.Murata Batch Dial == 0  */
				if (!ScanSetQueue(SYS_BATCH_TX, next_batch_com_num, SYS_DIRECT_DIAL, 0)) {
					return;
				}
				set_count++;
			}
			if (set_count == 0)	 {	/* CHECK ILLEGAL COMMAND SET */
				/* Nov.18,1994 CMN_ClearCommandArea(SYS_BATCH_TX, i); BUG */ /* TBD */
				/* Nov.18,1994 CMN_ClearCommandArea(SYS_BATCH_TX, i); BUG FIX */
				return;
			}
			cp->Status = SYS_CMD_EXECUTE;
		}
	}
	return;
}
#endif

/*************************************************************************
	module		:[連続ポーリングコマンドをスケジューラーに展開]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/10/17]
	author		:[江口,渡辺一章]
*************************************************************************/
#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 1996/10/17 Eguchi *//* FOR 連続ポーリング */
void	SetContinuousPollingToExec(void)
{
	UBYTE	set_position;	/* ワンタッチ・短縮格納配列番号 */
	UBYTE	set_bit;		/* ワンタッチ・短縮格納ビット位置 */
	UWORD	i;				/* ループ変数 */
	UWORD	set_count;		/* キューに展開した数 */
	UDWORD	current_time;	/* 現在時刻*/

	set_count = 0;
	current_time = SYB_CurrentTime;

#if defined(POPLAR_F)
	if (SYS_ContPollingValiableTimer) {
		return;
	}
#endif

	/*
	** 連続ポーリングコマンド使用状況が予約中でかつ現在時刻が開始時刻と終了時刻
	** に収まっている場合、連続ポーリングコマンドをスケジューラーに展開する
	*/
	if ((SYB_ContinuousPolling.Status == SYS_CMD_WAITING)
	 && (SYB_ContinuousPolling.StartTime <= current_time)
	 && (SYB_ContinuousPolling.EndTime   >= current_time)) {

		/*--------------------*
		 * 直接ダイアルを展開
		 *--------------------*/
		for (i = 0; i < SYS_COM_DIRECT_DIAL_MAX; i++) {	/** Change SYS_COM_DIAL_MAX to SYS_COM_DIRECT_DIAL_MAX by O.Kimoto 1997/06/16 */
			if ((SYB_ContinuousPolling.DialNumber.Direct[i][0] & 0xF0) != 0xF0) {
				if (!ScanSetQueue(SYS_CONTINUOUS_POLLING, 0, SYS_DIRECT_DIAL, i)) {
					return;
				}
				set_count++;
			}
		}

		/*------------------*
		 * ワンタッチを展開
		 *------------------*/
		for (i = 0; i < SYS_ONETOUCH_MAX; i++) {

			/* 登録されているワンタッチを探します */
			if ((SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0) {

				/* 送信用のバッファには、ビットで格納されているので格納位置を求める */
				set_position = (UBYTE)(i / 8);
				set_bit      = (UBYTE)(i % 8);

				/* 登録されているワンタッチが相手先に指定されているか、
				** 又は登録されているワンタッチのグループが相手先に指定されているかを調べる
				*/
				if (((SYB_ContinuousPolling.DialNumber.Onetouch[set_position] >> set_bit) & 0x01)
				 || ((SYB_OnetouchDial[i].Group & SYB_ContinuousPolling.DialNumber.Group) != 0)) {
					/* キューに展開 */
					if (!ScanSetQueue(SYS_CONTINUOUS_POLLING, 0, SYS_ONETOUCH_DIAL, i)) {	/* キューに空きがない時 */
						return;
					}
					set_count++;
				}
			}
		}

		/*------------*
		 * 短縮を展開
		 *------------*/
		for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) {

			/* 登録されている短縮を探します */
			if ((SYB_SpeedDial[i].Dial[0] & 0xF0) != 0xF0) {

				/* 送信用のバッファには、ビットで格納されているので格納位置を求める */
				set_position = (UBYTE)(i / 8);
				set_bit      = (UBYTE)(i % 8);

				/* 登録されている短縮が相手先に指定されているか、
				** 又は登録されている短縮のグループが相手先に指定されているかを調べる
				*/
				if (((SYB_ContinuousPolling.DialNumber.Speed[set_position] >> set_bit) & 0x01)
				 || ((SYB_SpeedDial[i].Group & SYB_ContinuousPolling.DialNumber.Group) != 0)) {
					/* キューに展開 */
/* おいおい！ この関数の引数SYS_ONETOUCH_DIALになっとったやんけ！ ちゃんとテストしてんの？ 一回うごかしたらすぐわかるやんけ！ */
/* なんでＤＶＴまでわからへんねん。こんなんモジュールテストでわかるやんけ！ 全くもう！！ */
					if (!ScanSetQueue(SYS_CONTINUOUS_POLLING, 0, SYS_SPEED_DIAL, i)) {	/* キューに空きがない時 */
						return;
					}
					set_count++;
				}
			}
		}

		if (set_count != 0) {
			SYB_ContinuousPolling.Status = SYS_CMD_EXECUTE;
		}
	}
}
#endif	/* (PRO_CONTINUOUS_POLLING == ENABLE) */

/*************************************************************************
	module		:[連続ポーリングコマンドクリア]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/10/18]
	author		:[江口]
*************************************************************************/
#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 1996/10/17 Eguchi *//* FOR 連続ポーリング */
void	DeleteContinuousPollingCommand(void)
{
	UBYTE	loop;
	/*
	 *スケジューラに消去された連続ポーリングコマンドがないか調べる。
	 *あれば使用状況を未使用にする
	 */
	for (loop = 0; loop < SYS_EXEC_QUEUE_MAX; loop++) {
		if ((SYB_ExecQueue[loop].Status == SYS_EXEC_ERASED)
		&&	(SYB_ExecQueue[loop].Kind	== SYS_CONTINUOUS_POLLING)) {
			SYB_ExecQueue[loop].Status = SYS_EXEC_EMPTY;
		}
	}
	
	/*
	 *スケジューラに連続ポーリングコマンドが残っているか調べる 
	 */
	for (loop = 0; loop < SYS_EXEC_QUEUE_MAX; loop++) {
		if ((SYB_ExecQueue[loop].Status != SYS_EXEC_EMPTY)
		&&	(SYB_ExecQueue[loop].Kind	== SYS_CONTINUOUS_POLLING)) {
			break;
		}
	}

	if (loop == SYS_EXEC_QUEUE_MAX) {
		if (SYB_ContinuousPolling.Status == SYS_CMD_ERASED) {
			/* オペレーションによる消去が実行されていた場合 */
			SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;
#if defined(POPLAR_F)
			SYS_ContPollingValiableTimer = 0;
#endif
		}
		else {
			if (SYB_ContinuousPolling.Status != SYS_CMD_EMPTY) {	/* add if () 1997/10/29 COMMAND_DEL */
				SYB_ContinuousPolling.Status = SYS_CMD_WAITING;
#if defined(POPLAR_F)
				SYS_ContPollingValiableTimer = 70;	/* 70sec */
#endif
			}
		}
	}
}
#endif	/* (PRO_CONTINUOUS_POLLING == ENABLE) */

#if (PRO_MULTI_LINE == ENABLE)
/**　Module Header For CIM-E ********************************************
		module		:	[実行すべき発信スケジューラ～の番号を取得]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[]
		keyword		:	[]
		date		:	[96/12/11]
		author		:	[木元修]
************************************************************************/
UWORD OPT_GetNextExecNo(void)
{
	return(GetNextExecNo());
}

#endif


/*************************************************************************
	module		:[メモリ送信中の確認プリントチェック関数（オペレーション編）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		メモリ送信中の確認プリント不具合
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_OPRSameDocumentAccess(UBYTE CommandKind, UBYTE CommandNumber){}]
	date		:[1998/09/01]
	author		:[木元  修]
*************************************************************************/
UBYTE CHK_OPRSameDocumentAccess(UBYTE CommandKind, UBYTE CommandNumber)
{
	UWORD	i;
	struct SYS_ExecQueueData_t *ep;	/* ExecQueue用ポインター */

	if (((CommandKind == SYS_BATCH_TX) && (SYB_BatchTxFile[CommandNumber].Status == SYS_CMD_EXECUTE))
	||  ((CommandKind == SYS_COMMAND_TRX)&&(SYB_CommandFile[CommandNumber].Status == SYS_CMD_EXECUTE))) {
		for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) {
			ep = &SYB_ExecQueue[i];
			if ((ep->Kind == CommandKind) && (ep->Number.Command == CommandNumber)
				&& ((ep->Status == SYS_EXEC_EXECUTE) || (ep->Status == SYS_EXEC_FORWARD_EXECUTE))) {
				return(FALSE);
			}
		}
	}
	return(TRUE);
}


/*************************************************************************
	module		:[メモリ送信中の確認プリントチェック関数（メイン編）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		メモリ送信中の確認プリント不具合
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_MANSameDocumentAccess(UBYTE QueueNumber){}]
	date		:[1998/09/01]
	author		:[木元  修]
*************************************************************************/
UBYTE CHK_MANSameDocumentAccess(UBYTE QueueNumber)
{
	UBYTE	print_item;
	UWORD	print_no;
	struct SYS_ExecQueueData_t *ep;	/* ExecQueue用ポインター */

	ep = &SYB_ExecQueue[QueueNumber];
	
	if (ep->Kind == SYS_BATCH_TX) {
		print_item = (UBYTE)(SYS_MEM_BATCH_TX_FILE1 + ep->Number.Command);
		/* 一括送信のときは、SYS_DocumentPrintNoには受付番号が入っているので、ここでは
		** 一括送信用ファイル番号が限定できるので、受付番号はチェックしません。
		*/
		if (((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) == SYS_PRINTER_BUSY)
			&& ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) == SYS_IMAGE_PRINT)
			&& (SYS_DocumentPrintItem == print_item)) {
			return(FALSE);
		}
	}
	else if (ep->Kind == SYS_COMMAND_TRX) {
		print_item = SYS_MEM_TX_FILE;
		print_no = (UWORD)(ep->Number.Command);
		if (((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) == SYS_PRINTER_BUSY)
			&& ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) == SYS_IMAGE_PRINT)
			&& (SYS_DocumentPrintItem == print_item)
			&& (SYS_DocumentPrintNo == (UWORD)print_no)) {
			return(FALSE);
		}
	}
	return(TRUE);
}



#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/09 Y.Murata for KAKI */
UBYTE CheckCommandBroadcast(UBYTE command_no)
{
	UBYTE	i;
	UBYTE	onetouch_pos;
	UBYTE	speed_pos;
	UBYTE	group_pos;
	UBYTE	direct_pos;
	UWORD	set_count;
	UDWORD	d;
	struct SYS_CommandData_t *cp;
	struct SYS_DialData_t *dp;

	set_count = 0;

	cp = &SYB_CommandFile[command_no];		/** 指定コマンドファイル */
	for (onetouch_pos = 0; onetouch_pos < SYS_ONETOUCH_MAX; onetouch_pos++) {
		if ((SYB_OnetouchDial[onetouch_pos].Dial[0] & 0xF0) != 0xF0) {
			dp = &cp->DialNumber;
			if (CMN_CheckBitAssign((UBYTE *)dp->Onetouch, onetouch_pos) == TRUE) {
				set_count++;
			}
			else if (SYB_OnetouchDial[onetouch_pos].Group) {
				d = 0x00000001;
				for (group_pos = 0; group_pos < SYS_GROUP_NUMBER_MAX; group_pos++) {
					if (SYB_OnetouchDial[onetouch_pos].Group & d) {
						if (dp->Group & d) {
							set_count++;
							break;
						}
					}
					d <<= 1;
				}
			}
		}
	}	/* End of For SYS_ONETOUCH_MAX */
	/* 短縮ダイアル */
	for (speed_pos = 0; speed_pos < SYS_SPEED_DIAL_MAX; speed_pos++)  {
		if ((SYB_SpeedDial[speed_pos].Dial[0] & 0xF0) != 0xF0) {
			dp = &cp->DialNumber;
			if (CMN_CheckBitAssign((UBYTE *)dp->Speed, speed_pos) == TRUE) {
				set_count++;
			}
			else if (SYB_SpeedDial[speed_pos].Group) {
				d = 0x00000001;
				for (group_pos = 0; group_pos < SYS_GROUP_NUMBER_MAX; group_pos++) {
					if (SYB_SpeedDial[speed_pos].Group & d) {
						if (dp->Group & d) {
							set_count++;
							break;
						}
					}
					d <<= 1;
				}
			}
		}
	}
	/* 直接ダイアル */
	dp = &cp->DialNumber;
	for (direct_pos = 0; direct_pos < SYS_COM_DIRECT_DIAL_MAX; direct_pos++)  {
		if ((dp->Direct[direct_pos][0] & 0xF0) != 0xF0) {
			set_count++;
		}
	}
	if (set_count == 0)	 {	/* CHECK ILLEGAL COMMAND SET */
		return(0xFF);
	}
	if (set_count == 1) {
		return(1);
	}
	return(0);
}

#endif	/* End of (PRO_QUICK_TX_TEST == ENABLE) */
