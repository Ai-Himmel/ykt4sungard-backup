/* copy 1996/12/25 */
/* Original File : jun\usr1:\src\rice\v53\kiri\src\scn_sub.c */
/***********************************************************************
*               BY:  S.Kawasaki
*             DATE:  Mar.14,1993
*        FILE NAME:  scn_sub.c
*      DESCRIPTION:	 スキャナー用モジュール
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:	HINOKI 対応 By O.Kimoto 1998/12/21
*      MODULE NAME:	void far MAN_WatchDocumentSetTask( void )
*					void far MAN_WatchDocumentOutTask( void )
*					void far MAN_DocumentInTask( void )
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\scn_io.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sysmax.h"

#include "\src\ATLANTA\FLA\define\sys_pro.h"
#include "\src\ATLANTA\ext_v\SCN_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\rom_tbl.h"

#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\define\cmn_pro.h"

#if defined(HINOKI) || defined(HINOKI2) || defined (HINOKI3) /* Add By O.Kimoto 1998/12/21 */ /* HINOKI2 2001/11/13 T.Takagi */
#include "\src\atlanta\hinoki\define\hino_sys.h"
#endif
#if defined(SATSUKI2) || defined(STOCKHM2)
#include "\src\atlanta\sh7043\define\sh_sys.h"
#endif

#pragma section FLASHWRITE /*  "PFLASHWRITE" */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
/** Module Header For CIM-E ********************************************
		module		:	[スキャナー・ドライバーの初期化]
		function	:	[]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[パワーＯＮ直後一度だけ実行する]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/4/5]
 		author		:	[川崎真史]
************************************************************************/
void FLA_SCN_Init(void)
{
#if defined(HINOKI)	|| defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3) /* Add By O.Kimoto 1998/12/21 */ /* HINOKI2 2001/11/13 T.Takagi */
	/* 何もしない */
#else
	SCN_MTPC0_Status = 0;
	SCN_MTPC1_Status = 0;
	SCN_MTP0_Status = 0;
	SCN_MTP1_Status = 0;
	SCN_SENSTP_Status = 0;
	SCN_SSTSTP_Status = 0;
	SCN_SCNINT_Status = 0;
	SCN_DS2INTR_Status = 0;
	/* SCN_BUZZ_1K_Status = 0; */	/* 使用 */
	SCN_MTCNT_Status = 0;
	SCN_SCCNT_Status = 0;			/* 使用 */
	SCN_INTLNCN_Status = 0;

	FLA_outp(MTPC0_PORT, SCN_MTPC0_Status);
	FLA_outp(MTPC1_PORT, SCN_MTPC1_Status);
	FLA_outp(MTP0_PORT, SCN_MTP0_Status);
	FLA_outp(MTP1_PORT, SCN_MTP1_Status);
	FLA_outp(SSTSTP0_PORT, (UBYTE)SCN_SSTSTP_Status);
	FLA_outp(SSTSTP1_PORT, (UBYTE)SCN_SSTSTP_Status);
	FLA_outp(SCNINT_PORT, SCN_SCNINT_Status);
	FLA_outp(DS2INTR_PORT, SCN_DS2INTR_Status);
	FLA_outp(MTCNT_PORT, SCN_MTCNT_Status);
	FLA_outp(SCCNT_PORT, SCN_SCCNT_Status);
#endif
}

/** Module Header For CIM-E ********************************************
		module		:	[ブザー周波数の設定]
		function	:	[]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void FLA_SCN_SetBuzzerFrequency( UBYTE frequency_no )
{
#if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3) 	/* Add By O.Kimoto 1998/12/21 */ /* HINOKI2 2001/11/13 T.Takagi */
	/* ＨＩＮＯＫＩは何も無しです。*/
#else
	/********************************************************************
	*	Ｄ０からＤ３ビットでブザー周波数を設定する。					*
	*	発生周波数＝２３．４３２５ＫＨｚ／（２＊（設定値＋１））		*
	*	例）２３．４３２５／（２＊（１０＋１））＝１．０６５ＫＨｚ		*
	*********************************************************************/
	SCN_BUZZ_1K_Status &= 0xF0;
	SCN_BUZZ_1K_Status |= frequency_no;/** ブザー周波数セット */
	FLA_outp(BUZZ_1K_PORT, SCN_BUZZ_1K_Status);
#endif
}

/** Module Header For CIM-E ********************************************
		module		:	[設定周波数でのブザー許可／禁止]
		function	:	[
						引き数　SCN_ENABLE : ブザー許可
								SCN_DISABLE: ブザー禁止
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[SCN]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
************************************************************************/
void FLA_SCN_SetBuzzer( UBYTE enable_flag )
{
#if defined(HINOKI)	|| defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3) /* Add By O.Kimoto 1998/12/21 */ /* HINOKI2 2001/11/13 T.Takagi */
	if (enable_flag == SCN_ENABLE) {
		MTU__TCR3 = 0x22;		/* Output(MTU_TCR1, 0x22); */
		MTU__TIOR3H = 0x03;		/* Output(MTU_TIOR1, 0x03); */
		MTU__TGR3A = 875;		/* OutputWORD(MTU_TGR1A, 875); */
		MTU__TMDR3 = 0x02;		/* Output(MTU_TMDR1, 0x02); */
		MTU__TSTR |= TSTR_START_CH3;	/* (Output(MTU_TSTR, (Input(MTU_TSTR) | TSTR_START_CH1)); */
	}
	else {
		MTU__TSTR &= ~TSTR_START_CH3;	/* Output(MTU_TSTR, (Input(MTU_TSTR) & ~TSTR_START_CH1)); */
	}
#else
	if (enable_flag == SCN_ENABLE) {
		SCN_SCCNT_Status |= IO_BIT_BUZZER_ENABLE; /** ブザー許可 */
	}
	else {
		SCN_SCCNT_Status &= ~(IO_BIT_BUZZER_ENABLE); /** ブザー禁止 */
	}
	FLA_outp(SCCNT_PORT, SCN_SCCNT_Status);
#endif
}

#endif
#pragma section
