/************************************************************************
*               BY:  S.Kawasaki, M.Kotani
*             DATE:  Sep.1,1993, 1996/10/11
*        Copy Date: 1996/10/21 From \src\kobe\anzu\src\ By M.Kotani
*        FILE NAME:  man_idle.c
*      Module Name:  IdleTask(void)
*		Task ID No:	 0
*      DESCRIPTION:  MainTask()	起動用のﾀｽｸとしてCPU初期化直後に起動されるﾀｽｸ
*					 ﾒｲﾝﾀｽｸ起動後にはｶｳﾝﾀ-のｲﾝｸﾘﾒﾝﾄだけで何もしないﾃﾞﾊﾞｯｸﾞﾀｽｸ
*					 となる.
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:  ini_enty.srcよりCALLされる.
*************************************************************************/
/*定義ファイル*/
#include	"\src\atlanta\define\product.h"
#include 	"\src\atlanta\define\mon_pro.h"
#if (PRO_CPU == SH7043)
#include 	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\sh7043\define\def_tib.h"
#endif

/*参照ファイル*/
#include  	"\src\atlanta\ext_v\bkupram.h"

#if (PRO_KEYPANEL == PANEL_ANZU_L)
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#endif

#if defined(POPLAR_H)	/* By M.Tachibana 2002/08/27 */
#include "\src\atlanta\\sh7043\define\def_mon.h"
#include "\src\atlanta\\sh7043\ext_v\extv_mon.h"
static UWORD CheckLargeStackArea(void);
static UWORD CheckSmallStackArea(void);
static void DBG_StackCheck(void);
#endif

void MAN_IdleTask(void)
{
	UWORD maintsk_tid;		/* ﾒｲﾝﾀｽｸ管理用の変数定義 */
	UDWORD IdleCounter;		/* ロングに変更 M.Kotnai 1997/11/11 */

	IdleCounter = 0;
	/*********************************/
	/*	ﾒｲﾝﾀｽｸをｸﾘｴｲﾄし、ここでｽﾀｰﾄ。*/
	/*********************************/
	cre_tsk(&maintsk_tid,TSK_MAN_TASK,0);
	/*********************************************************/
	/* IdleCounterだけを加算し、他にはなにもしないﾀｽｸになる。*/
	/*********************************************************/
	while (1) {
		IdleCounter++;
		if (SYB_MaintenanceSwitch[0]!=0) { /** 保守メモリ・スイッチＡ０に０以外のタスクＩＤがセットされた */
			TraceTaskAddress();
		}
#if (PRO_KEYPANEL == PANEL_SAKAKI) /* Added by H.Kubo 1998/08/05 */
		else {
			MON_SleepCPU(); /* CPU をスリープ状態にします。 */
		}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L) /* デバッグモード、アイドルカウンタ表示 1997/11/13 Y.Matsukuma */
		IdleCountDisplay(IdleCounter);
#endif
#if defined(POPLAR_H)	/* By M.Tachibana 2002/08/27 */
		if (SYB_MaintenanceSwitch[7] & 0x80) {
			DBG_StackCheck();
		}
#endif
	}
}


#if defined(POPLAR_H)	/* By M.Tachibana 2002/08/27 */

static UWORD CheckLargeStackArea(void)
{
	UWORD i;
	UWORD j;
	
	for (i = 0; i < LARGE_STACK_MAX; i++) {
		for (j = 0; j < LARGE_STACK/4; j++) {
			if (large_stack_area[i][j] != 0xA5A5A5A5) {
				break;
			}
		}
		if (j < LARGE_STACK/4/8) { /* 1/8を未満なら */
			return (i);		/* 640×1 / 8 = 80Byte */
		}
	}
	return (0xFFFF);	/* OK */
}

static UWORD CheckSmallStackArea(void)
{
	UWORD i;
	UWORD j;

	for (i = 0; i < SMALL_STACK_MAX; i++) {
		for (j = 0; j < SMALL_STACK/4; j++) {
			if (small_stack_area[i][j] != 0xA5A5A5A5) {
				break;
			}
		}
		if (j < SMALL_STACK/4/8) { /* 1/8未満なら */
			return (i);	/* 288 * 1/ 8 = 36Byte */
		}
	}
	return (0xFFFF);	/* OK */
}

static void DBG_StackCheck(void)
{
	if (CheckLargeStackArea() != 0xFFFF) {
		SYB_MaintenanceSwitch[7] |= 0x20;
	}
	if (CheckSmallStackArea() != 0xFFFF) {
		SYB_MaintenanceSwitch[7] |= 0x20;
	}
}

#endif
