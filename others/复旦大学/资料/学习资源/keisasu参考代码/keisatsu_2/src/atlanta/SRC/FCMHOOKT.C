/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMHOOKT.C												 */
/*	モジュール	 :															 */
/*				 : HookTensouOffHookCheck()									 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 :															 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\define\fcm_def.h"

#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\stng_pro.h"

#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\ncu_data.h"

#include	"\src\atlanta\sh7043\define\io_pro.h"

/*----------------------By HARADA 1994年6月22日---------*/
/*---全面書換-----------By N.S.	  '94,08,23	   ---------*/
void HookTensouOffHookCheck(void)
{
	if(( OhPortStatus & TEL1_OFF_HOOK ) && ( NCUStatus & TELEPHONE1_OFF_HOOK )){
		FaxTelResult = FCOM_TEL1_OFF_HOOK;
		ReceiveError(0x11);
	}
	if(( OhPortStatus & TEL2_OFF_HOOK ) && ( NCUStatus & TELEPHONE2_OFF_HOOK )){
#if (PRO_REMOTE_RX == ENABLE) || (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* 1998/01/24  By T.Yamaguchi */ /* REMOTE_RX_FUNC */
		if (!(TADStatus & REMOTE_RECEIVE)) {			/* TEL2の受話器あげっぱなしだと回線断してしまう */
			FaxTelResult  = FCOM_TEL2_OFF_HOOK;
			ReceiveError(0x11);
		}
#else
		FaxTelResult  = FCOM_TEL2_OFF_HOOK;
		ReceiveError(0x11);
#endif
	}
	if( FaxComPerformingFlag == 0 ){
		CML_RelayOff();
#if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */
		AnalogSwitchTONE_Set();
#endif
									/*-------------------*/
		if( CHK_CatchPhoneON() ){	/** キャッチホン対応 */
									/*-------------------*/
			wai_tsk( 250 );
		}
		else{
			wai_tsk(50);
		}
	}
/*	NCUStatus &= ( ~(TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK ));	Comment by TH92115 1995/03/27 */
}

