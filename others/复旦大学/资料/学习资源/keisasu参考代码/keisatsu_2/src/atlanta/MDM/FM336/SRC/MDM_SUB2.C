/*---------------------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                              */
/*  ファイル名   : mdm_sub2.c                                                            */
/*  作成者       :                                                                */
/*  日  付       : 1999/10/06                                                            */
/*  概  要       : モデムセットアップ処理                                                */
/*  修正履歴     :                                                                       */
/*	keyword			:[MDM]                                                               */
/*	machine			:[SH7043,V53]                                                        */
/*	language		:[MS-C(Ver.6.0)]                                                     */
/*---------------------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sys_opt.h"		/* 1997/06/13 by H. Kubo */
#include "\src\atlanta\define\cmn_def.h"		/* 1997/06/17 H. Kubo */
#include "\src\atlanta\sh7043\define\def_tib.h"		/* 1996/12/11 Y.M */
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dpr_pro.h"
#include "\src\atlanta\define\man_pro.h"		/* 1996/12/10 Y.M */
#include "\src\atlanta\define\cmn_pro.h"		/* 1996/12/10 Y.M */
#include "\src\atlanta\define\mem_pro.h"	/* 1996/12/10 Y.M */
#include "\src\atlanta\define\fcm_pro.h"		/* 1997/11/10 H.Kubo */
#include "\src\memsw\define\mems_pro.h" /* by H.Kubo 1997/07/07 */

/*******
** ext_v
*******/
#include "\src\atlanta\ext_v\extv_mbx.h"		/* 1996/12/11 Y.M */
#include "\src\atlanta\ext_v\extv_sem.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"

#if (0) /* mdm_fact.c にありDULICATE SYMBOLになるので削除  1999/02/23 s.takeuchi */
//  /*************************************************************************
//  	module		:[サービスファンクション（Ｖ．３４）]
//  	function	:[
//  		1.
//  	]
//  	return		:[]
//  	common		:[]
//  	condition	:[]
//  	comment		:[]
//  	machine		:[V53]
//  	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
//  	keyword		:[MDM]
//  	ProtoType	:[UBYTE far MDM_TxV34ServiceFunction(UBYTE baud_menu, UBYTE data_menu) {}]
//  	date		:[1996/11/27]
//  	author		:[木元修]
//  *************************************************************************/
//  UBYTE  MDM_TxV34ServiceFunction(UBYTE baud_menu, UBYTE data_menu)
//  {
//  	UBYTE	volume_level;
//  
//  	volume_level = 0;
//  
//  	/* ソフトリセット */
//  	MDM_SetIO(POS_SFRES,ON);
//  	MDM_SetIO(POS_NEWC,ON);
//  	wai_tsk(400/10);
//  
//  	/* スピーカーの設定 */
//  	if (CHK_LineMonitor()) {
//  		volume_level = SYS_VOLUME_MIDDLE; /* Modified for POPLAR_H according to cmn_def.h by H. Kubo. 1997/06/13 */
//  	}
//  	else {
//  		volume_level = SYS_VOLUME_OFF; /* Modified for POPLAR_H according to cmn_def.h by H. Kubo. 1997/06/13 */
//  	}
//  	MDM_SetVolumeAttenuationLevel(volume_level);
//  
//  	/* 送出レベル設定 */
//  	MDM_TransmitLevelSet((UBYTE) FCM_PtnrChk_T23Attenation());
//  	ModemBlock.TxAttenuation = FCM_PtnrChk_T23Attenation(); /** アッテネータレベル設定	*/
//  
//  	/* ループバックモード */
//  	MDM_SetIO(POS_ORG,ON);
//  	MDM_SetIO(POS_NEWC,ON);
//  	MDM_SetIO(POS_CONF,data_menu);
//  	MDM_SetIO(POS_NEWC,ON);
//  	MDM_SetIO(POS_NEWC,ON);
//  
//  	/* ループバックモードで、31.2k/33.6kの信号が出ない件の対策
//  	** 2.MAXHDXRATE ($37A)に$CEを書き込む
//  	**（最大レートの上限を28.8Kbpsから33.6Kbpsに変更します。）
//  	** By O.Kimoto 1997/05/08
//  	*/
//  	DspRamAccessWriteMethod1(0x37A,0xCE,0x00);
//  
//  	DspRamAccessWriteMethod1(0x2E3,baud_menu,0x00);
//  	MDM_SetIO(POS_L3ACT,ON);
//  	MDM_SetIO(POS_EXL3,ON);
//  	MDM_SetIO(POS_NEWC,ON);
//  	MDM_SetIO(POS_DTR,ON);
//  	return(1);
//  }
#endif

#if (0) /* POPLAR_H で使われないようなのでコメントアウトする。 b H.Kubo 1997/06/27 */
** /*************************************************************************
** 	module		:[サービスファンクション]
** 	function	:[
** 		1.
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[]
** 	machine		:[V53]
** 	language	:[MS-C(Ver.6.0)]
** 	keyword		:[MDM]
** 	date		:[1996/12/10]
** 	author		:[村田]
** *************************************************************************/
** void  MDM_FactoryFunctionTask(void)
** {
** 	UWORD	status;
** 
** 	/* DPR_SetFactoryFunctionResponse(); */
** 
** 	status = 0;
** 	SYS_FactoryFuncStatus = 0;
** 	tskno_MDM_FskTest = 0xFFFF;
** 	tskno_MDM_PixTest = 0xFFFF;
** 	SYS_PixStopFlag = 0;
** 	SYS_V34ProcedureExecutingFlag = NO;  /* 0; */
** 	MDM_FactoryFskMenu = 0;
** 
** /* POPLAR_H では直接メモリスイッチを参照できるので、以下は不必要。*/
** #if (0) /* Commented out by H. Kubo 1997/06/26 for POPLAR_H. */
** //	DPR_GetMemorySwitch();
** //	DPR_GetMachineUniqSwitch();
** //	DPR_GetMaintenanceSwitch();
** //	DPR_GetMachineParameter();
** //	CTRY_GetIniCountryCode();
** //	SYS_SetMachineParameter();
** #endif
** 
** 	while (1) {
** 		while (SYS_FactoryFuncReq == 0) {
** 			wai_tsk(1);
** 		}
** 		SYS_FactoryFuncReq = 0;
** 
** 		/* switch (SYS_FactoryOpt.Item) [ */
** 		switch (SYS_FactoryModem.Item) { /* Modified by H. Kubo for POPLAR_H 1997/06/17 */
** 		case SYS_OPT_MDM_RELAY_TEST:
** 			if ((status == 0) || (status == 1)) {
** 				status = 1;
** 			}
** 			else {
** 				/* ソフトリセット */
** 				MDM_SetIO(POS_SFRES,ON);
** 				MDM_SetIO(POS_NEWC,ON);
** 				wai_tsk(400/10);
** 				status = 1;
** 			}
** 			MDM_RealyTest();
** 			break;
** 		case SYS_OPT_MDM_TONAL_TEST:
** 			if ((status == 0) || (status == 2)) {
** 				status = 2;
** 			}
** 			else {
** 				/* ソフトリセット */
** 				MDM_SetIO(POS_SFRES,ON);
** 				MDM_SetIO(POS_NEWC,ON);
** 				wai_tsk(400/10);
** 				status = 2;
** 			}
** 			MDM_TonalTest();
** 			break;
** 		case SYS_OPT_MDM_DTMF_TEST:
** 			if ((status == 0) || (status == 3)) {
** 				status = 3;
** 			}
** 			else {
** 				/* ソフトリセット */
** 				MDM_SetIO(POS_SFRES,ON);
** 				MDM_SetIO(POS_NEWC,ON);
** 				wai_tsk(400/10);
** 				status = 3;
** 			}
** 			MDM_DTMF_Test();
** 			break;
** 		case OPT_MDM_FACTORY_TEST_END:
** 			break;
** 		case OPT_MDM_FACTORY_TEST_START:
** 			break;
** 		}
** 
** 		DPR_SetFactoryFunctionResponse();
** 
** 	}
** }
#endif /* 1 */ /* コメントアウト終わり */

#if (0) /* POPLAR_H で使われないようなのでコメントアウトする。 b H.Kubo 1997/06/27 */
//void far MDM_FactoryFunctionExit(void)
//{
//	if (tskno_MDM_FskTest != 0xFFFF) {
//		del_tsk(&tskno_MDM_FskTest);
//	}
//	if (tskno_MDM_PixTest != 0xFFFF) {
//		del_tsk(&tskno_MDM_PixTest);
//	}
//
//	MDM_SetIO(POS_SFRES,ON);
//	MDM_SetIO(POS_NEWC,ON);
//	MDM_FactoryFuncRelayReSet();
//	exi_tsk();
//}
#endif /* 0 */ /* コメントアウト終わり */

#if (0) /* mdm_fact.c にありDULICATE SYMBOLになるので削除  1999/02/23 s.takeuchi */
//  /*--------------------*/
//  /* トーナル信号テスト */
//  /*--------------------*/
//  #define TEST_TONE	1
//  #define TEST_FSK	2
//  #define TEST_G3		3
//  #define TEST_VOICE	4
//  #define TEST_V34	5
//  void near MDM_TonalTest(void)
//  {
//  	MESSAGE_t			*msg;
//  	UBYTE	conf_data;
//  	UBYTE	boo_data;
//  	UWORD			offset;
//  	UWORD			base;
//  	UWORD			value;
//  	UBYTE	volume_level;
//  
//  	/* ソフトリセット */
//  	MDM_SetIO(POS_SFRES,ON);
//  	MDM_SetIO(POS_NEWC,ON);
//  	wai_tsk(400/10);
//  
//  	MDM_FactoryFskMenu = 0;
//  	SYS_FactoryFuncStatus = 0;
//  	MDM_FactoryFuncRelaySet();
//  	tskno_MDM_FskTest = 0xFFFF;
//  	tskno_MDM_PixTest = 0xFFFF;
//  	SYS_PixStopFlag = 0;
//  
//  	/* スピーカーの設定 */
//  	if (CHK_LineMonitor()) {
//  		volume_level = SYS_VOLUME_MIDDLE; /* Modified for POPLAR_H according to cmn_def.h by H. Kubo. 1997/06/13 */
//  	}
//  	else {
//  		volume_level = SYS_VOLUME_OFF; /* Modified for POPLAR_H according to cmn_def.h by H. Kubo. 1997/06/13 */
//  	}
//  	MDM_SetVolumeAttenuationLevel(volume_level);
//  
//  	if (SYS_FactoryModem.Item == OPT_MDM_FACTORY_TEST_END) { /* Modified by H. Kubo for POPLAR_H 1997/06/17 */
//  		MDM_FactoryStopCheck();
//  		SYS_FactoryFuncStatus = 0;
//  	}
//  	/* Stop */
//  	else if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_STOP) {  /* Modified by H. Kubo for POPLAR_H 1997/06/17 */
//  		MDM_FactoryStopCheck();
//  		SYS_FactoryFuncStatus = 0;
//  	}
//  	/* ﾄｰﾝ */
//  	else if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_NONE) { /* Modified by H. Kubo for POPLAR_H 1997/06/17 */
//  		if (SYS_FactoryFuncStatus == TEST_TONE) {
//  			MDM_SingleToneOff();
//  		}
//  		else {
//  			if (SYS_FactoryFuncStatus) {
//  				MDM_FactoryStopCheck();
//  			}
//  		}
//  		SYS_FactoryFuncStatus = TEST_TONE;
//  	}
//  	else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_462HZ) && (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_2100HZ)) {
//  		if (SYS_FactoryFuncStatus == TEST_TONE) {
//  			MDM_SingleToneOff();
//  			/* ソフトリセット */
//  			MDM_SetIO(POS_SFRES,ON);
//  			MDM_SetIO(POS_NEWC,ON);
//  			wai_tsk(400/10);
//  			if (CHK_LineMonitor()) {
//  				volume_level = SYS_VOLUME_MIDDLE; /* Modified for POPLAR_H according to cmn_def.h by H. Kubo. 1997/06/13 */
//  			}
//  			else {
//  				volume_level = SYS_VOLUME_OFF; /* Modified for POPLAR_H according to cmn_def.h by H. Kubo. 1997/06/13 */
//  			}
//  			MDM_SetVolumeAttenuationLevel(volume_level);
//  		}
//  		else {
//  			if (SYS_FactoryFuncStatus) {
//  				MDM_FactoryStopCheck();
//  			}
//  		}
//  		SYS_FactoryFuncStatus = TEST_TONE;
//  		value = SYS_FactoryModem.Kind -1; /* Modified by H.Kubo 1997/06/26 */
//  		MDM_Tone((UBYTE)value);
//  	}
//  	/* FSK */
//  	else if ((SYS_FactoryModem.Kind == OPT_MDM_TONAL_FSK_WHITE) || (SYS_FactoryModem.Kind == OPT_MDM_TONAL_FSK_BLACK)) {		if (SYS_FactoryFuncStatus == TEST_FSK) {
//  			SYS_PixStopFlag = 1;
//  			rcv_msg(mbxno.OPR_Task, &msg);
//  			if (tskno_MDM_FskTest != 0xFFFF) {
//  				del_tsk(&tskno_MDM_FskTest);
//  			}
//  			wai_tsk(1);
//  		}
//  		else {
//  			if (SYS_FactoryFuncStatus) {
//  				MDM_FactoryStopCheck();
//  			}
//  		}
//  		SYS_PixStopFlag = 0;
//  
//  		SYS_FactoryFuncStatus = TEST_FSK;
//  		if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_FSK_WHITE) {
//  			MDM_FactoryFskMenu = FSK_WHITE;
//  			cre_tsk(&tskno_MDM_FskTest, TSK_MDM_FSKTXTASK, &MDM_FactoryFskMenu);
//  		}
//  		else {
//  			MDM_FactoryFskMenu = FSK_BLACK;
//  			cre_tsk(&tskno_MDM_FskTest, TSK_MDM_FSKTXTASK, &MDM_FactoryFskMenu);
//  		}
//  	}
//  	/* G3 */
//  	else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V27_1200_2400) && (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V17_2400_14400)){
//  		if (SYS_FactoryFuncStatus == TEST_G3) {
//  			SYS_PixStopFlag = 1;
//  			rcv_msg(mbxno.OPR_Task, &msg);
//  			if (tskno_MDM_PixTest != 0xFFFF) {
//  				del_tsk(&tskno_MDM_PixTest);
//  			}
//  			wai_tsk(1);
//  		}
//  		else {
//  			if (SYS_FactoryFuncStatus) {
//  				MDM_FactoryStopCheck();
//  			}
//  		}
//  		SYS_PixStopFlag = 0;
//  		SYS_FactoryFuncStatus = TEST_G3;
//  
//  		switch (SYS_FactoryModem.Kind) {
//  		case OPT_MDM_TONAL_V27_1200_2400:
//  			FactoryPixData.baud_rate = BPS2400_V27;
//  			break;
//  		case OPT_MDM_TONAL_V27_1600_4800:
//  			FactoryPixData.baud_rate = BPS4800_V27;
//  			break;
//  		case OPT_MDM_TONAL_V29_2400_7200:
//  			FactoryPixData.baud_rate = BPS7200_V29;
//  			break;
//  		case OPT_MDM_TONAL_V29_2400_9600:
//  			FactoryPixData.baud_rate = BPS9600_V29;
//  			break;
//  		case OPT_MDM_TONAL_V17_2400_7200:
//  			FactoryPixData.baud_rate = BPS7200_V17;
//  			break;
//  		case OPT_MDM_TONAL_V17_2400_9600:
//  			FactoryPixData.baud_rate = BPS9600_V17;
//  			break;
//  		case OPT_MDM_TONAL_V17_2400_12000:
//  			FactoryPixData.baud_rate = BPS12000_V17;
//  			break;
//  		case OPT_MDM_TONAL_V17_2400_14400:
//  			FactoryPixData.baud_rate = BPS14400_V17;
//  			break;
//  		}
//  		FactoryPixData.pix_retio = (UBYTE)SYS_FactoryModem.PIX_Pattern;
//  		cre_tsk(&tskno_MDM_PixTest, TSK_MDM_PIXTXTASK, &FactoryPixData);
//  	}
//  	/* Voice */
//  	else if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_VOICE) {
//  		if (SYS_FactoryFuncStatus == TEST_VOICE) {
//  			/* Nothing */
//  		}
//  		else {
//  			if (SYS_FactoryFuncStatus) {
//  				MDM_FactoryStopCheck();
//  			}
//  		}
//  		SYS_FactoryFuncStatus = TEST_VOICE;
//  		StartSendingMelodyToLine();
//  	}
//  	else {
//  	/* V34 */
//  		if (SYS_FactoryFuncStatus == TEST_V34) {
//  			/* ソフトリセット */
//  			MDM_SetIO(POS_DTR,OFF);
//  			wai_tsk(100/10);
//  			MDM_SetIO(POS_SFRES,ON);
//  			MDM_SetIO(POS_NEWC,ON);
//  			wai_tsk(400/10);
//  		}
//  		else {
//  			if (SYS_FactoryFuncStatus) {
//  				MDM_FactoryStopCheck();
//  			}
//  		}
//  		SYS_FactoryFuncStatus = TEST_V34;
//  		if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V34_2400_2400) &&
//  			 (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V34_2400_21600)) {
//  			base = 0xC1;
//  			offset = base - OPT_MDM_TONAL_V34_2400_2400;	/* 174 */
//  			boo_data = 0;
//  			conf_data = (UBYTE)(offset + SYS_FactoryModem.Kind); /* Modified by H.Kubo 1997/06/26 */
//  			MDM_TxV34ServiceFunction(boo_data, conf_data);
//  		}
//  		else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V34_2800_4800) &&
//  				 (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V34_2800_26400)) {
//  			base = 0xC2;
//  			offset = base - OPT_MDM_TONAL_V34_2800_4800;	/* 166 */
//  			boo_data = 2;
//  			conf_data = (UBYTE)(offset + SYS_FactoryModem.Kind); /* Modified by H.Kubo 1997/06/26 */
//  			MDM_TxV34ServiceFunction(boo_data, conf_data);
//  		}
//  		else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V34_3000_4800) &&
//  				 (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V34_3000_28800)) {
//  			base = 0xC2;
//  			offset = base - OPT_MDM_TONAL_V34_3000_4800;	/* 156 */
//  			boo_data = 3;
//  			conf_data = (UBYTE)(offset + SYS_FactoryModem.Kind); /* Modified by H.Kubo 1997/06/26 */
//  			MDM_TxV34ServiceFunction(boo_data, conf_data);
//  		}
//  		else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V34_3200_4800) &&
//  				 (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V34_3200_31200)) {
//  			base = 0xC2;
//  			offset = base - OPT_MDM_TONAL_V34_3200_4800;	/* 145 */
//  			boo_data = 4;
//  			conf_data = (UBYTE)(offset + SYS_FactoryModem.Kind); /* Modified by H.Kubo 1997/06/26 */
//  			MDM_TxV34ServiceFunction(boo_data, conf_data);
//  		}
//  		else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V34_3429_4800) &&
//  				 (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V34_3429_33600)) {
//  			base = 0xC2;
//  			offset = base - OPT_MDM_TONAL_V34_3429_4800;	/* 133 */
//  			boo_data = 5;
//  			conf_data = (UBYTE)(offset + SYS_FactoryModem.Kind); /* Modified by H.Kubo 1997/06/26 */
//  			MDM_TxV34ServiceFunction(boo_data, conf_data);
//  		}
//  	}
//  }
//  
//  /*--------------------*/
//  /* ＤＴＭＦ送出テスト */
//  /*--------------------*/
//  void near MDM_DTMF_Test(void)
//  {
//  	UBYTE	volume_level;
//  	UWORD			offset;
//  	UWORD			base;
//  	UBYTE	value;
//  
//  	/* ソフトリセット */
//  	MDM_SetIO(POS_SFRES,ON);
//  	MDM_SetIO(POS_NEWC,ON);
//  	wai_tsk(400/10);
//  
//  	MDM_FactoryFskMenu = 0;
//  	MDM_FactoryFuncRelaySet();
//  
//  	/* スピーカーの設定 */
//  	if (CHK_LineMonitor()) {
//  		volume_level = SYS_VOLUME_MIDDLE; /* Modified for POPLAR_H according to cmn_def.h by H. Kubo. 1997/06/13 */
//  	}
//  	else {
//  		volume_level = SYS_VOLUME_OFF; /* Modified for POPLAR_H according to cmn_def.h by H. Kubo. 1997/06/13 */
//  	}
//  	MDM_SetVolumeAttenuationLevel(volume_level);
//  
//  
//  	if (SYS_FactoryModem.Item == OPT_MDM_FACTORY_TEST_END) {
//  		MDM_SetIO(POS_RTS,OFF);
//  		MDM_DTMF_Close();
//  		MDM_FactoryFskMenu = 0;
//  	}
//  	else if (SYS_FactoryModem.Kind == OPT_MDM_DTMF_STOP) {
//  		MDM_SetIO(POS_RTS,OFF);
//  		MDM_DTMF_Close();
//  		MDM_FactoryFskMenu = 0;
//  	}
//  	else {
//  		if (MDM_FactoryFskMenu == 0xFF) {
//  			MDM_SetIO(POS_RTS,OFF);
//  			MDM_DTMF_Close();
//  			wai_tsk(100/10);
//  		}
//  		MDM_FactoryFskMenu = 0xFF;
//  		if (SYS_FactoryModem.Kind <= OPT_MDM_DTMF_SHARP) {
//  			MDM_DTMF_Open();
//  			MDM_DTMF_Set((UBYTE)(SYS_FactoryModem.Kind));
//  			MDM_SetIO(POS_RTS,ON);
//  		}
//  		else {
//  			if ((SYS_FactoryModem.Kind >= OPT_MDM_DTMF_ROW1) && (SYS_FactoryModem.Kind <= OPT_MDM_DTMF_COL4)) {
//  				base = 0;
//  				offset = OPT_MDM_DTMF_ROW1 - base;	/* 12 */
//  				value = (UBYTE)(SYS_FactoryModem.Kind - offset);
//  
//  				MDM_DTMF_Open();
//  				MDM_DTMF_SingleSet(value);
//  				MDM_SetIO(POS_RTS,ON);
//  			}
//  		}
//  	}
//  }
//  
//  /*----------------------*/
//  /* 回線テストリレー制御 */
//  /*----------------------*/
//  void MDM_FactoryFuncRelaySet(void)
//  {
//  	/* ＤＰリレーＯＮ 1996/11/26 */
//  	DP_RelayOn();
//  	wai_tsk(1);
//  
//  	S_RelayOn();	/* Relay Spike Niose For Switching(FRA DEU) 1996/11/26 */
//  
//  	CML_RelayOn();
//  	wai_tsk(10);	/* 100ms */
//  	H_RelayOn();
//  	L_RelayOn();
//  	S_RelayOff();				/* Add by TH92115 1994/08/29 */
//  }
//  
//  void  MDM_FactoryFuncRelayReSet(void)
//  {
//  	CML_RelayOff();
//  	H_RelayOff();
//  	L_RelayOff();
//  	CONT_24V_Off();
//  	S_RelayOff();
//  	DP_RelayOff();
//  }
//  
//  void MDM_FactoryStopCheck(void)
//  {
//  	MESSAGE_t			*msg;
//  
//  	SYS_PixStopFlag = 0;
//  
//  	switch (SYS_FactoryFuncStatus) {
//  	case TEST_TONE:
//  		MDM_SingleToneOff();
//  		break;
//  	case TEST_FSK:
//  		SYS_PixStopFlag = 1;
//  		rcv_msg(mbxno.OPR_Task, &msg);
//  		if (tskno_MDM_FskTest != 0xFFFF) {
//  			del_tsk(&tskno_MDM_FskTest);
//  		}
//  		MDM_SetIO(POS_RTS,OFF);
//  		break;
//  	case TEST_G3:
//  		SYS_PixStopFlag = 1;
//  		rcv_msg(mbxno.OPR_Task, &msg);
//  		if (tskno_MDM_PixTest != 0xFFFF) {
//  			del_tsk(&tskno_MDM_PixTest);
//  		}
//  		MDM_SetIO(POS_RTS,OFF);
//  		break;
//  	case TEST_VOICE:
//  		StopSendingMelodyToLine();
//  		break;
//  	case TEST_V34:
//  		MDM_SetIO(POS_DTR,OFF);
//  		MDM_SetIO(POS_L3ACT,OFF);
//  		MDM_SetIO(POS_EXL3,OFF);
//  		MDM_SetIO(POS_NEWC,ON);
//  		break;
//  	default:
//  		break;
//  	}
//  	wai_tsk(10);	/* 100ms */
//  }
#endif

