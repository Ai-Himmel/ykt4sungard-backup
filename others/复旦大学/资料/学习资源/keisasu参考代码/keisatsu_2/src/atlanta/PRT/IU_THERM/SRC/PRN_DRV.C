/*******************************************************************
*	System		: SAKAKI
*	File Name	: PRN_DRV.C
*	Author		: K.Kawata
*	Date		: 1998/6/9
*	Description	:
*	Maintenance	:
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
********************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sysmcopy.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_port.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\define\mnt_sw.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\define\unisw_f.h"
#include "\src\atlanta\define\uni_pro.h"

#if (0)
** /* SAKAKI */
** #include "\src\atlanta\prt\thermal\define\prn_pro.h"
** #include "\src\atlanta\prt\thermal\define\prn_def.h"
** #include "\src\atlanta\prt\thermal\define\prn_stat.h"
** 
** #include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_tbl.h"
#else
/* HINOKI */
/* SATSUKI2 */
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#endif

/************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[PRN]
	date		:[1998/6/9]
	author		:[K.Kawata]
************************************************/

#if defined(SATSUKI2)
/*************************************************
	module		:[カッタードライブ１ＯＮ]
	function	:[
		1.カッタードライブ１をＯＮにします
	]
	return		:[なし]
	common		:[なし]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[1993/11/26]
	author		:[大西亨]
*************************************************/
void CutterDrive1_On(void)
{
	IO__PADRH |= IO_BIT_CDRV1;
/*	outpw(IO__PADRH,IO_BIT_CDRV1);*/
}

/******************************************************************************
	module		:[カッタードライブ１ＯＦＦ]
	function	:[
		1.カッタードライブ１をＯＦＦにします
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
void CutterDrive1_Off(void)
{
	IO__PADRH &= ~IO_BIT_CDRV1;
/*	outpw(IO__PADRH,~IO_BIT_CDRV1);*/
}

/******************************************************************************
	module		:[カッタードライブ２ＯＮ]
	function	:[
		1.カッタードライブ２をＯＮにします
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
void CutterDrive2_On(void)
{
	IO__PADRH |= IO_BIT_CDRV2;
/*	outpw(IO__PADRH,IO_BIT_CDRV2);*/
}

/******************************************************************************
	module		:[カッタードライブ２ＯＦＦ]
	function	:[
		1.カッタードライブ２をＯＦＦにします
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
void CutterDrive2_Off(void)
{
	IO__PADRH &= ~IO_BIT_CDRV2;
/*	outpw(IO__PADRH,~IO_BIT_CDRV2);*/
}

#endif
/*************************************************************************
	module		:[プリンタモーター終了待ち]
	function	:[
		1.PrintMotor()を使用してプリンタモーターを回したときにプリンタモータ
		 .の回転終了を待ちます
	]
	return		:[なし]
	common		:[なし]
	condition	:[なし]
	comment		:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/12/02]
	author		:[大西]
*************************************************************************/
void	WaitPrintMotorBusy()
{
#if (0)
** 	/* SAKAKI */
** 	while (PRN_Control.PrintMotorCount > 0) {
** 		wai_tsk(1);	/*	10msec */
** 		if (RXIL()) {
** 			PRN_Control.PrintMotorCount = 0;
** 		}
** 	}
#endif
}


/*************************************************************************
	module		:[プリンタモーター回転]
	function	:[
		1.１０ｍｓｅｃタイマー割り込みを使用してプリンタモーターを回します
		2.入力パラメータの数値１当たり400PPSで４ステップ回します。
	]
	return		:[なし]
	common		:[PrintMotorCount]
	condition	:[]
	comment		:[
		1.スピードは400PPSの設定（初期設定のまま）で行うこと、通常400PPS
		 .以外のスピードは使用しない
		2.2相,1-2相はどちらでも使用可能,相を変更する場合はPrintMotorを呼ぶ前に
		 .PrintMotorPhase1(), PrintMotorPhase12() を呼ぶこと
	]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/12/02]
	author		:[大西]
*************************************************************************/
void	PrintMotor(UWORD	step)
{
#if (0)
** 	/* SAKAKI */
** 	PmenOn();  /** プリンタモーター励磁ＯＮ */
** 	PRN_Control.PrintMotorCount = step;
#endif
}

/*************************************************************************
	module		:[プリンタモーター回転停止]
	function	:[
		1.PrintMotor()で回しているプリンタモーターを強制停止します。
		2.プリンタモーターの励磁ＯＦＦします。
	]
	return		:[なし]
	common		:[なし]
	condition	:[なし]
	comment		:[
		1.ScanMotor(step) を使用してタイマー割り込みで一定周期でstepの長さ分
		  回しているプリンタモーターを途中で停止したいときに使用します。
	]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1994/4/08]
	author		:[大西]
*************************************************************************/
void	PrintMotorStop()
{
#if (0)
** 	/* SAKAKI */
** 	PRN_Control.PrintMotorCount = 0;	/* カウンタークリア */
** 	PmenOff();							/* 励磁ＯＦＦ       */
#endif
}

/*************************************************************************
	module		:[10msecタイマー割り込みプリンタモーター]
	function	:[
		1.１０ｍｓｅｃタイマー割り込みを使用してプリンタモーターを回します
		2.入力パラメータの数値１当たり２００ｐｐｓで２ステップ回します。
	]
	return		:[なし]
	common		:[PrintMotorCount]
	condition	:[
		1.10msecインターバルタイマー割り込みの中で呼ぶこと
		2.スピードは200PPSの設定（初期設定のまま）で行うこと、通常200PPS
		 .以外のスピードは使用しない
	]
	comment		:[なし]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[H8/300(日立マイコン)]
	date		:[1994/05/02]
	author		:[木元]
*************************************************************************/
void	Tim10msecPrintMotor()
{
#if (0)
** 	/* SAKAKI */
** 	if (PRN_Control.PrintMotorCount > 0) { /** PrintMotorCountが正ならば  */
** 		if (SYS_PRN_StopRequest == TRUE) {	/* 1998/09/16 H.Yoshikawa SCN・PRNのDual処理のためにとりあえず入れときます */
** 			SYS_SCN_StartRequest = TRUE;
** 		}
** 		if (RXIL()) {/* カバーオープン */
** 			PRN_Control.PrintMotorCount = 0;
** 		}
** 		PRN_Control.PrintMotorCount --;
**     	PmenOn();
**     	Pmst();
** 	}
** 	ThermisterValue = AD__ADDRC1;
#endif
}

/*************************************************************************
	module		:[プリンタモータハードステップ送り]
	function	:[
		1.ゲートアレーの内部カウンタを使用してプリンタモーターを回します
		2.入力パラメータの数値１当たり１ステップ回します。
		3.入力パラメータが2以上の場合は400PPSで回ります。
		4.入力パラメータが1の場合はスピードは400PPSに関係なくPrintMotorHardStep(1)
		 .を呼ぶ周期で回ります。
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		1.入力パラメータはMAX=15です。0 or 16以上のパラメータは入力禁止です。
	]
	comment		:[
		1.スピードは400PPSの設定（初期設定のまま）で行うこと、通常400PPS
		 .以外のスピードは使用しない
		2.2相,1-2相はどちらでも使用可能,相を変更する場合はPrintMotorHardStepを呼ぶ前に
		 .PrintMotorPhase1(), PrintMotorPhase12() を呼ぶこと
	]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/12/07]
	author		:[大西]
*************************************************************************/
void	PrintMotorHardStep(step)
UBYTE	step;
{
#if (0)
** 	/* SAKAKI */
** 	PmenOn();
** 	PrintMotorStepSet(step);
** 	Pmst();
#endif
}

#if defined(SATSUKI2)	/* by Y.Kano 2003/11/08 */
/*************************************************************************
** 	module		:[カッター位置チェック]
** 	function	:[
** 		1.カッターセンサー１、カッターセンサー２をチェックしてカッターが
** 		 .どの位置に有るかチェックします。
** 	]
** 	return		:[
** 		#define    CUTTER_BUSY     0        センサーの間(BUSY)
** 		#define    CUTTER_LEFT     1        左側待機位置      
** 		#define    CUTTER_RIGHT    2        右側待機位置      
** 	]
** 	common		:[なし]
** 	condition	:[なし]
** 	comment		:[なし]
** 	machine		:[H8/300]
** 	language	:[CH38(V.2.0.B)]
** 	keyword		:[H8/300(日立マイコン)]
** 	date		:[1993/12/08]
** 	author		:[大西]
** *************************************************************************/
UBYTE	CutterPosition(void)
{
	if( CutterSensor1() == 1 ) {
		return(CUTTER_LEFT);
	} else if( CutterSensor2() == 1 ) {
		return(CUTTER_RIGHT);
	} else {
		return(CUTTER_BUSY);
	}
}
#endif

/*************************************************************************
	module		:[カッターＯＮ]
	function	:[
		1.カッター動作を起動します。（実際のカット動作は割込みで行います）
		2.カッターの位置をチェックし、左側に有る場合は左ｰ>右へカットします。
		 .右側に有る場合は右ｰ>左へカットします。
		 .左右のセンサーの間にある場合は、いったん左側待機位置へ戻し、
		 .左->右へカットする動作を起動
	]
	return		:[なし]
	common		:[なし]
	condition	:[なし]
	comment		:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/12/08]
	author		:[大西]
*************************************************************************/
/* SATSUKI2用に変更 start by Y.Kano 2003/06/24 */
#if defined (SATSUKI2)
void	CutterOn()
{
	/* イニシャル状態の確認	*/
	if( CutterPosition() == CUTTER_LEFT ) {	/* 左側待機位置 */
		PRN_Control.CutterPhase = 2;                /* 左->右へカットする動作を起動 */
	} else if( CutterPosition() == CUTTER_RIGHT ) { /* 右側待機位置         */
		PRN_Control.CutterPhase = 4;                /* 右->左へカットする動作を起動 */
	} else {                                /*待機位置から外れている場合    */
		PRN_Control.CutterPhase = 0;                /* いったん左側待機位置へ戻し、 */
                                            /* 左->右へカットする動作を起動 */
	}
	PRN_Control.CutterBusy = 1;	/** カッター動作中を示すフラグを立てる */
}

/*************************************************************************
	module		:[カッタードライブ]
	function	:[
		1.入力パラメーターに応じてカッターを左右に動かします
		 .パラメーター
			#define	CUT_LEFT    1    左に向かって切る          
			#define	CUT_RIGHT   2    右に向かって切る          
			#define	CUT_BRAKE   3    ブレーキをかける          
			#define CUT_OFF     4    カッターモーターをOFFする 
	]
	return		:[なし]
	common		:[なし]
	condition	:[なし]
	comment		:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/12/08]
	author		:[大西]
*************************************************************************/
void	CutterDrive( UBYTE drv_mode )
{
 	switch( drv_mode ) {
 		case CUT_LEFT:   			/*右 -> 左*/
 			CutterDrive2_Off();
 			CutterDrive1_On();
/* 			Cutter24VOn();*/
 			break;
 		case CUT_RIGHT:				/*左 -> 右*/
 			CutterDrive1_Off();
 			CutterDrive2_On();
/* 			Cutter24VOn();*/
 			break;
 		case CUT_BRAKE:				/*ブレーキ*/
 			CutterDrive1_On();
 			CutterDrive2_On();
 			break;
 		case CUT_OFF:
 		default:			/*ｶｯﾀｰﾓｰﾀ:OFF*/
 			CutterDrive1_Off();
 			CutterDrive2_Off();
/* 			Cutter24VOff();*/
 			break;
 	}
}
#endif

/*************************************************************************
	module		:[タイマー割り込みカッター処理]
	function	:[
		1.10msecの割り込みで CutterOn()　の実際の処理を実行します
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		1.必ず10msecインターバル割り込みでCallすること
	]
	comment		:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/12/08]
	author		:[大西]
*************************************************************************/
void	Tim10msCutter()
{
#if defined(SATSUKI2)
	/* SATSUKI2用カッター制御 start by Y.Kano 2003/06/24 */
 	if (PRN_Control.CutterBusy) {
 		if (SYS_PRN_StopRequest == TRUE) {	/* 1998/09/16 H.Yoshikawa SCN・PRNのDual処理のためにとりあえず入れときます */
 			SYS_SCN_StartRequest = TRUE;
 		}
 		if (RXIL()) {	/* カバーオープン */
 			PRN_Control.CutterBusy = 0; /** カット動作終了 */
 			CutterDrive(CUT_OFF);
 		}
 		else {
 			switch (PRN_Control.CutterPhase) {
 			case 0:	/* いったん左側待機位置へ戻し、左->右へカット */
 				CutterDrive(CUT_LEFT);
 				PRN_Control.CutterJamCount = 300;	/* 3.0sec : ｶｯﾀｰｼﾞｬﾑｶｳﾝﾄのｾｯﾄ 1998.7.16 K.kwata*/
 				PRN_Control.CutterBrakeCount = 6+1; /* 60msec : ｶｯﾀｰﾌﾞﾚｰｷｶｳﾝﾄのｾｯﾄ */
 				PRN_Control.CutterPhase = 1;
 				break;
 			case 1:
 				if ( CutterPosition() == CUTTER_LEFT ) { /** カッターが左側に来た場合 */
 					CutterDrive(CUT_BRAKE);
 					if ( --PRN_Control.CutterBrakeCount <= 0 ) {	/* 60msec */
 						CutterDrive(CUT_OFF);
 						PRN_Control.CutterPhase = 2; /** 左->右カット指示 */
 					}
 				} else {
 					CutterDrive(CUT_LEFT);	/** カッターが途中で止まる件 By O.K Dec,20,1994 **/
 					if ( --PRN_Control.CutterJamCount < 0 ) {/** 3.0secかかってもカッターが左側にこない場合 */
 						/*カッターエラー処理*/
 						CutterDrive(CUT_OFF);
 						if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/) { /* 既にカッターエラーの場合 */
 							PRN_Control.CutterBusy = 0; /** カット終了 */
 						} else {
 							PRN_Control.CutterPhase = 2; /** カッターを右側へ戻す */
 							SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/;
 						}
 					}
 				}
 				break;
 			case 2:	/* 左->右へカット */
 				CutterDrive(CUT_RIGHT);
 				PRN_Control.CutterJamCount = 300;	/* 3.0sec : ｶｯﾀｰｼﾞｬﾑｶｳﾝﾄのｾｯﾄ 1998.7.16 K.kwata*/
 				PRN_Control.CutterBrakeCount = 6+1;	/* 60msec : ｶｯﾀｰﾌﾞﾚｰｷｶｳﾝﾄのｾｯﾄ */
 				PRN_Control.CutterPhase = 3;
 				break;
 			case 3:
 				if ( CutterPosition() == CUTTER_RIGHT ) { /** カッターが右側に来た場合 */
 					CutterDrive(CUT_BRAKE);
 					if ( --PRN_Control.CutterBrakeCount <= 0 ) {	/* 60msec */
 						CutterDrive(CUT_OFF);
 						PRN_Control.CutterBusy = 0; /** カット終了 */
 					}
 				} else {
 					CutterDrive(CUT_RIGHT);	/** '94/5/17 カッターが途中で止まる件の対策　By T.O */
 					if ( --PRN_Control.CutterJamCount < 0 ) { /** 3.0secかかってもカッターが右側へ来ない場合 */
 						/* カッターエラー処理 */
 						CutterDrive(CUT_OFF);
 						if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/) { /* 既にカッターエラーの場合 */
 							PRN_Control.CutterBusy = 0; /** カット終了 */
 						} else {
 							PRN_Control.CutterPhase = 4; /** 左側へカッターを戻す */
 							SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/;
 						}
 					}
 				}
 				break;
 			case 4: /* 右->左へカット */
 				CutterDrive(CUT_LEFT);
 				PRN_Control.CutterJamCount = 300;	/* 3.0sec : ｶｯﾀｰｼﾞｬﾑｶｳﾝﾄのｾｯﾄ 1998.7.16 K.kwata*/
 				PRN_Control.CutterBrakeCount = 6+1;	/* 60msec : ｶｯﾀｰﾌﾞﾚｰｷｶｳﾝﾄのｾｯﾄ */
 				PRN_Control.CutterPhase = 5;
 				break;
 			case 5:
 				if ( CutterPosition() == CUTTER_LEFT ) { /** カッターが左側に来た場合 */
 					CutterDrive(CUT_BRAKE);
 					if ( --PRN_Control.CutterBrakeCount <= 0 ) {	/* 60msec */
 						CutterDrive(CUT_OFF);
 						PRN_Control.CutterBusy = 0;   /** カット終了 */
 					}
 				} else {
 					CutterDrive(CUT_LEFT);	/** '94/5/17 カッターが途中で止まる件の対策　By T.O */
 					if (--PRN_Control.CutterJamCount < 0) {	/** 1.0secかかってもカッターが左側へ来ない場合 */
 						/* カッターエラー処理 */
 						CutterDrive(CUT_OFF);
 						if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/) { /* 既にカッターエラーの場合 */
 							PRN_Control.CutterBusy = 0;               /** カット終了 */
 						} else {
 							PRN_Control.CutterPhase = 2;              /** 右側へカッターを戻す */
 							SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/;
 						}
 					}
 				}
 				break;
 			default:
 				break;
 			}
 		}
 	}
#endif
#if (0)
** 	/* SAKAKI */
** 	if (PRN_Control.CutterBusy) {
** 		if (SYS_PRN_StopRequest == TRUE) {	/* 1998/09/16 H.Yoshikawa SCN・PRNのDual処理のためにとりあえず入れときます */
** 			SYS_SCN_StartRequest = TRUE;
** 		}
** 		if (RXIL()) {
** 			PRN_Control.CutterBusy = 0; /** カット動作終了 */
** 			CutterDrive(CUT_OFF);
** 		}
** 		else {
** 			switch (PRN_Control.CutterPhase) {
** 			case 0:	/* いったん左側待機位置へ戻し、左->右へカット */
** 				CutterDrive(CUT_LEFT);
** 				PRN_Control.CutterJamCount = 300;	/* 3.0sec : ｶｯﾀｰｼﾞｬﾑｶｳﾝﾄのｾｯﾄ 1998.7.16 K.kwata*/
** 				PRN_Control.CutterBrakeCount = 6+1; /* 60msec : ｶｯﾀｰﾌﾞﾚｰｷｶｳﾝﾄのｾｯﾄ */
** 				PRN_Control.CutterPhase = 1;
** 				break;
** 			case 1:
** 				if ( CutterPosition() == CUTTER_LEFT ) { /** カッターが左側に来た場合 */
** 					CutterDrive(CUT_BRAKE);
** 					if ( --PRN_Control.CutterBrakeCount <= 0 ) {	/* 60msec */
** 						CutterDrive(CUT_OFF);
** 						PRN_Control.CutterPhase = 2; /** 左->右カット指示 */
** 					}
** 				} else {
** 					CutterDrive(CUT_LEFT);	/** カッターが途中で止まる件 By O.K Dec,20,1994 **/
** 					if ( --PRN_Control.CutterJamCount < 0 ) {/** 3.0secかかってもカッターが左側にこない場合 */
** 						/*カッターエラー処理*/
** 						CutterDrive(CUT_OFF);
** 						if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/) { /* 既にカッターエラーの場合 */
** 							PRN_Control.CutterBusy = 0; /** カット終了 */
** 						} else {
** 							PRN_Control.CutterPhase = 2; /** カッターを右側へ戻す */
** 							SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/;
** 						}
** 					}
** 				}
** 				break;
** 			case 2:	/* 左->右へカット */
** 				CutterDrive(CUT_RIGHT);
** 				PRN_Control.CutterJamCount = 300;	/* 3.0sec : ｶｯﾀｰｼﾞｬﾑｶｳﾝﾄのｾｯﾄ 1998.7.16 K.kwata*/
** 				PRN_Control.CutterBrakeCount = 6+1;	/* 60msec : ｶｯﾀｰﾌﾞﾚｰｷｶｳﾝﾄのｾｯﾄ */
** 				PRN_Control.CutterPhase = 3;
** 				break;
** 			case 3:
** 				if ( CutterPosition() == CUTTER_RIGHT ) { /** カッターが右側に来た場合 */
** 					CutterDrive(CUT_BRAKE);
** 					if ( --PRN_Control.CutterBrakeCount <= 0 ) {	/* 60msec */
** 						CutterDrive(CUT_OFF);
** 						PRN_Control.CutterBusy = 0; /** カット終了 */
** 					}
** 				} else {
** 					CutterDrive(CUT_RIGHT);	/** '94/5/17 カッターが途中で止まる件の対策　By T.O */
** 					if ( --PRN_Control.CutterJamCount < 0 ) { /** 3.0secかかってもカッターが右側へ来ない場合 */
** 						/* カッターエラー処理 */
** 						CutterDrive(CUT_OFF);
** 						if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/) { /* 既にカッターエラーの場合 */
** 							PRN_Control.CutterBusy = 0; /** カット終了 */
** 						} else {
** 							PRN_Control.CutterPhase = 4; /** 左側へカッターを戻す */
** 							SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/;
** 						}
** 					}
** 				}
** 				break;
** 			case 4: /* 右->左へカット */
** 				CutterDrive(CUT_LEFT);
** 				PRN_Control.CutterJamCount = 300;	/* 3.0sec : ｶｯﾀｰｼﾞｬﾑｶｳﾝﾄのｾｯﾄ 1998.7.16 K.kwata*/
** 				PRN_Control.CutterBrakeCount = 6+1;	/* 60msec : ｶｯﾀｰﾌﾞﾚｰｷｶｳﾝﾄのｾｯﾄ */
** 				PRN_Control.CutterPhase = 5;
** 				break;
** 			case 5:
** 				if ( CutterPosition() == CUTTER_LEFT ) { /** カッターが左側に来た場合 */
** 					CutterDrive(CUT_BRAKE);
** 					if ( --PRN_Control.CutterBrakeCount <= 0 ) {	/* 60msec */
** 						CutterDrive(CUT_OFF);
** 						PRN_Control.CutterBusy = 0;   /** カット終了 */
** 					}
** 				} else {
** 					CutterDrive(CUT_LEFT);	/** '94/5/17 カッターが途中で止まる件の対策　By T.O */
** 					if (--PRN_Control.CutterJamCount < 0) {	/** 1.0secかかってもカッターが左側へ来ない場合 */
** 						/* カッターエラー処理 */
** 						CutterDrive(CUT_OFF);
** 						if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/) { /* 既にカッターエラーの場合 */
** 							PRN_Control.CutterBusy = 0;               /** カット終了 */
** 						} else {
** 							PRN_Control.CutterPhase = 2;              /** 右側へカッターを戻す */
** 							SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/;
** 						}
** 					}
** 				}
** 				break;
** 			default:
** 				break;
** 			}
** 		}
** 	}
#endif
}

/*************************************************************************
	module		:[印可時間]
	function	:[
		1.サーミスタの値でヒートパルステーブルを参照しヒートパルスの値を取り出す。
		2.上記の値とメモリスイッチＦ：１の値を加算する。
		3.結果が０ｘ０３～０ｘＦＡの範囲になるように調整する。
	]
	return		:[
		0 ～ 240
	]
	common		:[なし]
	condition	:[なし]
	comment		:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/12/08]
	author		:[大西]
*************************************************************************/
UBYTE	HeatTime()
{
#if (0)
** 	/* SAKAKI */
** 	UWORD	data;
** 
** 	data = (UWORD)(HeatTable[1][PRN_Thermister()]+HeatPulseOffSet+HeatPulseHeadRank-0x80);
** 	if (data < 0x0003) {
** 		data = 0x0003;
** 	}
** 	else if (data >= 0x00fa) {
** 		data = 0x00fa;
** 	}
** 	return((UBYTE)(data));
#endif
}

/*************************************************************************
	module		:[プリヒートの印可時間]
	function	:[
		1.サーミスタの値でプリヒートパルステーブルを参照しヒートパルスの値を取り出す。
		2.プリントモードがSFINEの場合は弱めに補正する。
	]
	return		:[
		0 ～ 240
	]
	common		:[なし]
	condition	:[なし]
	comment		:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1994/2/05]
	author		:[大西]
*************************************************************************/
UBYTE	PRN_PreHeatTime(void)
{
#if (0)
** 	/* SAKAKI */
** 	return((UBYTE)(HeatTable[1][PRN_Thermister()] / PRN_PreHeatShift()));
#endif
}

UBYTE	PRN_PreHeatShift(void)
{
#if (0)
** 	/* SAKAKI */
** 	if (SYS_PRN_StopRequest == TRUE) {
** 		if (SYB_MachineUniqSwitch[UNIQ_SW_F7] == 0) {
** 			return(1);
** 		}
** 		else {
** 			return((UBYTE)SYB_MachineUniqSwitch[UNIQ_SW_F7]);
** 		}
** 	}
** 	else {
** 		if (SYB_MachineUniqSwitch[UNIQ_SW_F4] == 0) {
** 			return(1);
** 		}
** 		else {
** 			return((UBYTE)SYB_MachineUniqSwitch[UNIQ_SW_F4]);
** 		}
** 	}
#endif
}

/*************************************************************************
	module		:[タイマー割り込みページカット処理 & プリオープン時の記録紙引き戻し処理]
	function	:[
		1.10msecの割り込みで PRN_Close()で起動した記録紙の排出＆カット＆引き戻し
		 .の処理を実行します
		2.PageCutPhase の値に従って排出／カット／引き戻しを行います。
			0:カッター迄のモーター送りの終了を待ち、モーター停止後、カッター
		      を起動します
			1:カッター動作の終了を待ち、正常にカッターが終了したら記録紙引き戻
		      しを起動します。
			  カッターエラーの場合はページカット処理を終了します。
			2:引き戻しのモーターの終了を待ち、モーター停止後バックラッシ除去の
			  モーター送りの起動をします
			3:モーターの停止を待ち、モーター停止後PS2をチェックします。PS2が
			  ONの場合は記録紙詰まりとします
			  ページカット処理を終了します。
		3.PRN_PreOpen()で起動した記録紙を引き戻しで記録位置にセットする処理を行います。	  
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		1.必ず10msecインターバル割oり込みでCallすること
	]
	comment		:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/12/08]
	author		:[大西]
*************************************************************************/
void	Tim10msPageCut()
{
#if (0)
** 	/* SAKAKI */
** 	if (PRN_Control.Command == PRN_PAGECUT_REQ) {
** 		if (SYS_PRN_StopRequest == TRUE) {	/* 1998/09/16 H.Yoshikawa SCN・PRNのDual処理のためにとりあえず入れときます */
** 			SYS_SCN_StartRequest = TRUE;
** 		}
** 		if (RXIL()) {/* カバーオープン */
** 			PRN_Control.Command = PRN_IDLE_REQ; /** ページカット処理終了 */
** 			PRN_Control.Status = PRN_IDLE;
** 		} else {
** 			switch(PRN_Control.PageCutPhase) {
** 				case 0: /** カッター迄の記録紙フィード中 */
** 					if (PRN_Control.PrintMotorCount <= 0) {
** 						PrintMotorStop();
** 						CutterOn();	/** カッター動作起動 */
** 						PRN_Control.PageCutPhase = 1;
** 					} else {
** 						if(!PS1()) {
** 							PrintMotorStop();
** 							SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;
** 							PRN_Control.Command = PRN_IDLE_REQ; /* ページカット処理終了 */
** 							PRN_Control.Status = PRN_IDLE;
** 						}
** 					}
** 					break;
** 				case 1:	/* カッター動作中 */
** 					if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM/*SYS_PRINTER_CUTTER_ERROR*/) {
** 						PRN_Control.Command = PRN_IDLE_REQ;
** 						PRN_Control.Status = PRN_IDLE;
** 					} else if (!PRN_Control.CutterBusy) { /** カット終了 */
** 						PRN_Control.PageCutPhase = 2;
** 						PrintMotorPhase12();	/* 1998.9.21 K.Kawata */
** 						PrintMotorSpeed(PRINT_200PPS);
** 					   	PrintMotorStepSet(4);
** 						PrintMotorRev(); /** ＲＸモーター逆転セット */
** 						PrintMotor((UWORD)((PRN_STEP_CUTTER_TO_HEAD-(UWORD)(SYB_MachineParameter[16])+PRN_STEP_BACKRUSH+128)/2));	/*1998.9.21 K.Kawata*/
** 						ps2_off_count = 2;	/** 先端余白ばらつき対策 By O.K Jan,25,1995 **/
** 						ps2_off_flag = 0;	/** 先端余白ばらつき対策 By O.K Jan,25,1995 **/
** 					}
** 					break;
** 				case 2: /** 記録紙引き戻し中 */
** 					if (PRN_Control.PrintMotorCount <= 0) {
** 						if(PS2()) { /** 記録紙引き戻し終了時にPS2がONしていた場合 */
** 							SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
** 							PRN_Control.Command = PRN_IDLE_REQ; /** ページカット処理終了 */
** 							PRN_Control.Status = PRN_IDLE;
** 						} else {
** 							PrintMotorFw(); /** ＲＸモーター正転セット */
** 							/** フィールド騒音テスト By O.K Feb,27,1995 **/
** 							/** ４００ｐｐｓ、１ー２相 By O.K Feb,27,1995 **/
** 							PrintMotorPhase12();
** 							PrintMotorSpeed(PRINT_200PPS);
** 						   	PrintMotorStepSet(4);
** 						   	PrnMotorPhase = 2;
** 							PrintMotor(PRN_STEP_BACKRUSH/2);	/* BACK RASH 1mm REDUCTION */
** 							PRN_Control.PageCutPhase = 3;
** 						}
** 					}
** 					/** 先端余白ばらつき対策 By O.K Jan,25,1995 **/
** 					else if (!PS2()) {
** 						if (ps2_off_count <= 0) {
** 							if (ps2_off_flag == 0) {
** 								PrintMotor((UWORD)((246-4-(UWORD)(SYB_MachineParameter[16])+PRN_STEP_BACKRUSH+128)/2)); /** ＰＳ２からヘッドへ送る *//**  By O.K Jan,25,1995 **/
** 								ps2_off_flag = 1;
** 							}
** 							ps2_off_count = 0;	/** 先端余白ばらつき対策 By O.K Jan,25,1995 **/
** 						}
** 						else {
** 							ps2_off_count --;
** 						}
** 					}
** 					break;
** 				case 3:
** 					if (PRN_Control.PrintMotorCount <= 0) {
** 						PRN_Control.Command = PRN_IDLE_REQ; /** ページカット処理終了 */
** 						PRN_Control.Status = PRN_IDLE;
** 					}
** 					break;
** 				default:
** 					PRN_Control.Command = PRN_IDLE_REQ; /** ページカット処理終了 */
** 					PRN_Control.Status = PRN_IDLE;
** 					break;
** 			}
** 		}
** 	}
** 	if (PRN_Control.Command == PRN_FEED_IN_REQ) {
** 		if (RXIL()) {
** 			PRN_Control.Command = PRN_IDLE_REQ; /** 記録紙引き戻し処理終了 */
** 			PRN_Control.Status = PRN_IDLE;
** 		} else {
** 			switch(PRN_Control.FeedInPhase) {
** 			case 0:
** 				if (PRN_Control.PrintMotorCount <= 0) { 
** 				                                        /** 記録紙引き戻しのモータ送りが終了 */
** 					PrintMotorFw(); 					/** ＲＸモーター正転セット */
** 					/** フィールド騒音テスト By O.K Feb,27,1995 **/
** 					/** ４００ｐｐｓ、１ー２相 By O.K Feb,27,1995 **/
** 					PrintMotorPhase12();
** 					PrintMotorSpeed(PRINT_200PPS);
** 				   	PrintMotorStepSet(4);
** 				   	PrnMotorPhase = 2;
** 					PrintMotor(PRN_STEP_BACKRUSH/2);	/** バックラッシュ除去のモータ送りスタート */
** 					PRN_Control.FeedInPhase = 1;
** 				}
** 				/** 先端余白ばらつき対策 By O.K Jan,25,1995 **/
** 				/** 尚、ps2_off_flagとps2_off_countはprn_preopen()でセットしています By O.K Jan,25,1995 **/
** 				else if (!PS2()) {
** 					if (ps2_off_count <= 0) {
** 						if (ps2_off_flag == 0) {
** 							PrintMotor((UWORD)((246 - 4 - (UWORD)(SYB_MachineParameter[16])+PRN_STEP_BACKRUSH+128)/2)); /** ＰＳ２からヘッドへ送る *//**  By O.K Jan,25,1995 **/
** 							ps2_off_flag = 1;
** 						}
** 						ps2_off_count = 0;	/** 先端余白ばらつき対策 By O.K Jan,25,1995 **/
** 					}
** 					else {
** 						ps2_off_count --;
** 					}
** 				}
** 				break;
** 			case 1:
** 				if (PRN_Control.PrintMotorCount <= 0) {
** 					PRN_Control.Command = PRN_IDLE_REQ; /** ページカット処理終了 */
** 					PRN_Control.Status = PRN_IDLE;
** 				}
** 				break;
** 			default:
** 				PRN_Control.Command = PRN_IDLE_REQ; /** ページカット処理終了 */
** 				PRN_Control.Status = PRN_IDLE;
** 				break;
** 			}
** 		}
** 	}
#endif
}

/*************************************************************************
	module		:[プリントサイズより記録紙サイズを選択]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[なし]
	comment		:[
		椛のサーマルヘッドはＢ４しかありません。
		　椛はＰＢ４センサーが見れないタイミングが有る為、ｐｒｎ＿ｐｒｅｏｐｅｎ（）でＰＢ４センサーを
	-	をチェックし、その結果をＲＡＭに代入しておき、その値をこの関数で参照させます。
	]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1994/03/01]
	author		:[宮崎]
*************************************************************************/
UBYTE	PRN_GetPaperSize()
{
#if (0)
** 	/* SAKAKI */
** 	if (PRN_PB4Sensor) {
** 		return (SYS_B4_PAPER);
** 	}
** 	else {
** 		return (SYS_A4_PAPER);
** 	}
#endif
}

/*************************************************************************
	module		:[オーバーヒートチェック]
	function	:[
		1.サーミスタのデータを読み込みます
		2.マシンステータスがオーバーヒートエラーで無い場合に温度が６５度以上のとき"1"を返す
		3.マシンステータスがオーバーヒートエラーの場合には温度が５０度以上のとき"1"を返す
	]
	return		:[
		1.	 1:オーバーヒートしている、	0:オーバーヒートしていない
	]
	common		:[なし]
	condition	:[なし]
	comment		:[
		椛で使用するＴ／Ｈのサーミスター値は
			高温＝サーミスター値が小さくなる
			低温＝サーミスター値が大きくなる
	]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1994/3/31]
	author		:[大西]
*************************************************************************/
UBYTE	PRN_OverHeatCheck()
{
#if (0)
** 	/* SAKAKI */
** 	if (!(SYB_MaintenanceSwitch[MNT_SW_E6] & PRN_TEST_A)) {
** 	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
** 		/** 既に機械がオーバーヒート状態にある場合は、５０度[サーミスタ出力１８Ｈ]以上でオーバーヒート */
** 		if (PRN_Thermister() <= (UBYTE)(HEAD_OVER_HEAT_RE_STOP)) {
** 			return(TRUE);
** 		}
** 	}
** 	else { 
** 		/** 機械がオーバーヒート状態にない場合は、６５度[サーミスタ出力１１Ｈ]以上でオーバーヒート */
** 		if (PRN_Thermister() <= (UBYTE)(HEAD_OVER_HEAT_STOP)) {
** 			return(TRUE);
** 		}
** 	}
** 	}
** 	return (FALSE);
#else
	/* HINOKI */
	ThermistorValue = AD_Thermistor();
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
		/** 既に機械がオーバーヒート状態にある場合は、５０度[サーミスタ出力１８Ｈ]以上でオーバーヒート */
		if (ThermistorValue <= HighTempUpper[HeadMaker]) {
			return(TRUE);
		}
	}
	else { 
		/** 機械がオーバーヒート状態にない場合は、６５度[サーミスタ出力１１Ｈ]以上でオーバーヒート */
		if (ThermistorValue <= HighTempLower[HeadMaker]) {
			return(TRUE);
		}
	}
	return (FALSE);
#endif
}


/*************************************************************************
	module		:[プリンターコントロール変数クリア]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[PRN]
	date		:[1994/05/09]
	author		:[木元　修]
*************************************************************************/
#if !defined(SATSUKI2)	/* SATSUKI2では使用せず start by Y.Kano 2003/06/26 */
void	ClearPrinterControlParameter()
{
#if (0)
** 	/* SAKAKI */
** 	PRN_Control.UseType = 0;               /* 00 : 動作種別(idp_def.h参照)       */
** 	PRN_Control.PrintMode = 0;             /* 01 : 記録密度(sysdoc.h参照)        */
** 	PRN_Control.PrintSize = 0;             /* 02 : 記録サイズ(sysdoc.h参照)      */
** 	PRN_Control.PaperSize = 0;             /* 03 : 記録紙サイズ(sysdoc.h参照)    */
** 	PRN_Control.ReductionType = 0;         /* 04 : 縮小タイプ(idp_def.h参照)     */
** 	PRN_Control.Dummy0 = 0;                /* 05 : ダミー                        */
** 	PRN_Control.PrintReduction = 0;        /* 06 : プリンタ縮小率(50～100%)x10   */
** 	PRN_Control.Command = 0;               /* 08 : 処理状態                      */
** 	PRN_Control.Status = 0;                /* 09 :                               */
** 	PRN_Control.Error = 0;                 /* 10 :プリンターエラー内容           */
** 	PRN_Control.LineBufferChangeFlag = 0;  /* 11 :                               */
** 	PRN_Control.LineBufferEnableCount = 0; /* 12 :                               */
** 	PRN_Control.ReprintLineCount = 0;      /* 13 :                               */
** 	PRN_Control.DICEP_DMA_Start = 0;       /* 14 : DICEP-AF DMA転送要求          */
** 	PRN_Control.WhiteLineDetect = 0;       /* 15 : 白ライン検出                  */
** 	PRN_Control.PrintPageEnd = 0;          /* 16 :                               */
** 	PRN_Control.CutterPhase = 0;           /* 17 :カッターの動作状況             */
** 	PRN_Control.CutterBusy = 0;            /* 18 :カッター動作中                 */
** 	PRN_Control.PageCutBusy = 0;           /* 19 :ページ排出カット引戻し処理中   */
** 	PRN_Control.PageCutPhase = 0;          /* 20 :                               */
** 	PRN_Control.StepPerPrint1Line = 0;     /* 21 :モーター送り量／１ライン当たり */
** 	PRN_Control.PrintMotorCount = 0;       /* 22 :プリンタモーター動作カウンタ   */
** 	PRN_Control.MinLineCount = 0;          /* 24 :最小記録長カウンタ             */
** 	PRN_Control.PaperJamCheckCount = 0;    /* 26 :ペーパージャム検出カウンタ     */
** 	PRN_Control.CutterJamCount = 0;        /* 28 :カッタージャム検出カウンタ     */
** 	PRN_Control.CutterBrakeCount = 0;      /* 30 :カッターブレーキ時間カウンタ   */
** 	PRN_Control.PrintLineCount = 0;        /* 32 :                               */
** 	PRN_Control.LineMemoryCount = 0;       /* 36 :                               */
** 	PRN_Control.LineBufferStartPosit = 0;  /* 40 :ラインバッファ入力開始位置     */
** 	PRN_Control.LineBufferEndPosit = 0;    /* 42 :ラインバッファ入力終了位置     */
** 	PRN_Control.LineBufferTransNo = 0;     /* 44 :                               */
** 	PRN_Control.LineMemoryTransNo = 0;     /* 46 :                               */
** 	PRN_Control.Ps1ToHeadCount = 0;        /* 48 :PS1=OffからHead迄のカウンタ    */
** 	PRN_Control.FeedInPhase = 0;           /* 51 :PRN_PreOpen()で起動した記録紙引き戻しの動作フェーズ */
#else
	/* HINOKI */
	PageQ.Reduction = 0;         /* 04 : 縮小タイプ(idp_def.h参照)     */
	PageQ.Mode = 0;             /* 01 : 記録密度(sysdoc.h参照)        */
	PrinterUseMode = PRINT_IDLE;
#endif
}
#endif	/* SATSUKI2では使用せず end  by Y.Kano 2003/06/26 */

/*************************************************************************
	module		:[サーミスター値を読み出す関数]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[PRN]
	date		:[1994/05/19]
	author		:[木元　修]
*************************************************************************/
UBYTE	PRN_Thermister()
{
#if (0)
** 	/* SAKAKI */
** 	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F1] = (ThermisterValue >> 10)));
#endif
}

