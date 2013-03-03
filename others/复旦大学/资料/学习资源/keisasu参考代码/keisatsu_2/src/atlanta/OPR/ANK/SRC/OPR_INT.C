/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_INT.C
*	Author		: 渡辺一章
*	Date		: 1996/12/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: キースキャン
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include    "\src\atlanta\sh7043\define\io_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\opr\ank\ext_v\key_tbl.h"	/* ファイル移動 By O.Kimoto 1997/07/16 */
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\def_evtn.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"
#endif

#if (PRO_KEYPANEL != PANEL_HINOKI) && (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2)	/* 1998/09/22 by T.Soneoka */

/*************************************************************************
	module		:[キースキャン]
	function	:[
		1.10msecに一回キー入力があるかないかポートをスキャンする。
		2.キー入力があり、完全なOFFのあとに、完全なONが確定したときイベントを発行する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		#if (PRO_CONT_KEY_INPUT == ENABLE)
		　連続取り込み可能なキースキャン（一定時間連続して同じキーが押されていたらＯＦＦ確定を無視する）
		　注）全てのキーを連続キー入力させるのではなくコピーモード中の左右の矢印キーのみ有効です
			　ただし、倍率有効範囲を超えると連続キー入力を禁止します
		　注）本来ならこのタスクは、無条件にキーの入力を知らせ、OPR_KeyTask()で
			　連続入力を許可しないキーをはじくべきだが、オペレーションが占有する
			　割合が増えてしまうので、あえてこの中でキーの判断を行います。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INT]
	date		:[1995/02/28]
	author		:[江口,渡辺一章]
*************************************************************************/
void OPR_KeyScan(void)
{
	UWORD io_wait;

	if (KeyPortNumber >= KEY_MATRICS_COLUM_MAX) {	/** キーポートの最後までスキャンした時 */
		KeyPortNumber = 0;	/** キーポートを最初に戻す */
	}

	/** キーポートをスキャンする */
 #if (PRO_CPU == SH7043)
	io_wait = CMN_CheckSH_WCR1_CS3();
	CMN_SetSH_WCR1_CS3(7);
	NewKeyCode = (UBYTE)inpw(KeyPortTable[KeyPortNumber]);
	CMN_SetSH_WCR1_CS3(io_wait);
 #endif

 #if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	/* キーポート０の３ビット目のワンタッチ切り替えは、キー入力とは無関係にＯＮ／ＯＦＦされるので、
	** キーの取り込みに影響が無いように、マスクをかけて無効にします
	*/
	if (KeyPortNumber == 0) {
		NewKeyCode |= IO_BIT_SHEET_CHANGE;
	}
 #endif

 #if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/08/13 Y.Matsukuma */
	/* キーポート５から９までのＤ６，Ｄ７は未使用のためマスクする */
	if (KeyPortNumber >= 5 && KeyPortNumber <= 9) {
		NewKeyCode |= 0xC0;
	}
 #endif

	if (NewKeyCode == OPR_NO_KEY) {	/** キーが押されていない時 */
 #if (PRO_CONT_KEY_INPUT == ENABLE)
		ContinuousKeyHit = FALSE;
		ContinuousKeyTimer = 0;
 #endif
		if (OldKeyCode == OPR_NO_KEY) {	/** 10msec前のスキャンでもキーは押されていない */
			if (NoKeyFlag == 1) {		/** キーOFFが確定している */
				KeyPortNumber++;			/** スキャンするポートを次のポートに進める */
				OldKeyCode = NewKeyCode;	/** キーコードを退避する */
			}
			else {						/** キーOFFが確定していない */
				NoKeyTime++;	/** OFFタイムをインクリメントする */
				if (NoKeyTime >= KEY_CHATTARING_OFF_TIME) {	/** ﾁｬﾀﾘﾝｸﾞでない（ﾁｬﾀﾘﾝｸﾞのOFF時間以上押されていない） */
					NoKeyFlag = 1;				/** キーOFF確定とみなす */
					OldKeyCode = NewKeyCode;	/** とりあえずコードを退避する */
					NoKeyTime = 0;				/** OFF時間をクリアしておく -> キーOFFが確定している限りさわらない */
					KeyPortNumber++;			/** スキャンするポートを次に進める */
				}
			}
		}
		else {							/** 10msec前は押されていた（キー入力と確定できないうちにOFFになった） */
			OldKeyCode = NewKeyCode;	/** 先のONはチャタリングとみなす（とりあえずコードを退避する） */
			HitKeyTime = 0;				/** ON時間をクリア */
			NoKeyTime++;				/** OFF時間インクリメント */
		}
	}
	else {							/** キーが押されている */
		if (OldKeyCode == OPR_NO_KEY) {	/** 10msec前のスキャンでは押されていなかった */
			HitKeyTime++;				/** キーON時間をインクリメントする */
			NoKeyTime = 0;				/** OFF時間をクリア */
			OldKeyCode = NewKeyCode;	/** キーポートの値を退避する */
		}
		else {							/** 10msec前のスキャンでも押されていた */
			if (NewKeyCode == OldKeyCode) {	/** 10msec前とポートの値が同じ時 */
				HitKeyTime++;				/** キーON時間をインクリメントする */
				OldKeyCode = NewKeyCode;	/** とりあえずコードを退避する */

 #if (PRO_CONT_KEY_INPUT == ENABLE)
				/*--------------------------------------------*/
				/* 連続入力を許可するキー・状態かを判断します */
				/* 注）この条件以外は連続入力を受け付けません */
				/*--------------------------------------------*/
  #if (PRO_KEYPANEL == PANEL_POPLAR_B)
				if (((KeyPortNumber == 3) && !(NewKeyCode & IO_BIT_KEY31))		/* 機能／右矢印キー */
				 || ((KeyPortNumber == 7) && !(NewKeyCode & IO_BIT_KEY71))) {	/* 左矢印キー */
					if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
						/* 一定時間以上キーが押されている */
						if ((HitKeyTime >= CONTINUOUS_KEY_INPUT_TIME) && (ContinuousKeyHit == FALSE)) {
							if (ContinuousKeyInputEnable == TRUE) {	/* 連続キー入力が許可されている時 */
								ContinuousKeyHit = TRUE;
							}
						}
					}
				}
  #endif

  #if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/08/27 Y.Matsukuma */
				/* 通信中のキャンセルを、通信確認キー連続入力でする */
				if ((KeyPortNumber == 3) && !(NewKeyCode & 0x0010))	{			/* 通信確認キー */
/*					if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) { 	@@ ホスト通信中なら */
						/* 一定時間以上キーが押されている */
						if ((HitKeyTime >= CONTINUOUS_KEY_INPUT_TIME) && (ContinuousKeyHit == FALSE)) {
							if (ContinuousKeyInputEnable == TRUE) {	/* 連続キー入力が許可されている時 */
								ContinuousKeyHit = TRUE;
							}
						}
/*					} */
				}
  #endif

				if (ContinuousKeyHit == TRUE) {	/* 連続入力（キーが押しっぱなし）と判断した場合 */
					ContinuousKeyTimer++;
					if (ContinuousKeyTimer >= KEY_HIT_TIME) {
						/*-------------------------------------------*/
						/** 連続キー入力とみなし、イベントを発行する */
						/*-------------------------------------------*/
						idet_evt(EVT_KEY_DECIDE);
						ContinuousKeyTimer = 0;
					}
				}
				else {							/* 現時点では単にキーが押されたとしか判断していない場合 */
					if (HitKeyTime >= KEY_CHATTARING_ON_TIME) {	/** ON確定（チャタリングのON時間より長い時間ON） */
						if (NoKeyFlag == 1) {	/** キーのOFFが確定している（一定以上のONをキー入力とみなしてよい） */
							/*-------------------------------------------*/
							/** キー入力ありとみなし、イベントを発行する */
							/*-------------------------------------------*/
							idet_evt(EVT_KEY_DECIDE);

							/** キーOFFフラグをこかしとく（ある程度OFFがつづくまでキー入力不可とする） */
							NoKeyFlag = 0;
						}
					}
				}
 #else
				if (HitKeyTime >= KEY_CHATTARING_ON_TIME) {	/** ON確定（チャタリングのON時間より長い時間ON） */
					if (NoKeyFlag == 1) {	/** キーのOFFが確定している（一定以上のONをキー入力とみなしてよい） */
						/*-------------------------------------------*/
						/** キー入力ありとみなし、イベントを発行する */
						/*-------------------------------------------*/
						idet_evt(EVT_KEY_DECIDE);

						/** キーOFFフラグをこかしとく（ある程度OFFがつづくまでキー入力不可とする） */
						NoKeyFlag = 0;
					}
				}
 #endif	/* (PRO_CONT_KEY_INPUT == ENABLE) */
			}
			else {							/** 10msec前は別のコードが押されていた時 */
				HitKeyTime = 0;				/** キーのON時間をクリア */
				OldKeyCode = NewKeyCode;	/** とりあえずコードを退避する */
 #if (PRO_CONT_KEY_INPUT == ENABLE)
				ContinuousKeyHit = FALSE;
				ContinuousKeyTimer = 0;
 #endif
			}
		}
	}
}
#endif
