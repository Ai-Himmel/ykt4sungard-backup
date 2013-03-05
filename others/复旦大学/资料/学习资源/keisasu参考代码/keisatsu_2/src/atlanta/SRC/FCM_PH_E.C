/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA			ANZUを移植								 */
/*	ファイル名	 : FCM_PH_E.C												 */
/*	モジュール	 :															 */
/*				 : FaxPhaseE()												 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : フェーズＥ												 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
/***********/
/* Include */
/***********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\ext_v\fcm_data.h"

void   FaxPhaseE( UBYTE	phase_e_mode)
{
	/*-----------*/
	/*	Phase E	 */
	/*-----------*/

	FaxComPhaseStatus = FAX_PH_E;

	/*---------------------------------------*/
	/*	phase_e_mode						 */
	/*				  1:   FTZ Fig13-9 H1	 */
	/*				  2:   FTZ Fig13-9 H2	 */
	/*				  3:   FTZ Fig13-9 H3	 */
	/*				  4:   FTZ Fig13-9 H4	 */
	/*				  5:   FTZ Fig13-9 H5	 */
	/*				  6:   NTT FAX/TEL PhB1	 */
	/*---------------------------------------*/

	switch( phase_e_mode ){
		case 1:
		case 2:
		case 3:
		case 5:
				/************/
				/** DCN Tx **/
				/************/
				FaxHDLC_Transmit( DCN_F, 0 );
				FaxComPerformingFlag = 0;

#if (PRO_MODEM == R288F)	/* ROCKWELL製 28.8K *//* Add By O.Kimoto 1997/12/02 */
			/*----------------------------*/
			/* コントロールチャネルＯＦＦ */
			/*----------------------------*/
			FCM_ControlChanelOff();
#endif

				break;
		case 4:
				FaxComPerformingFlag = 0;
				break;
	}
}
