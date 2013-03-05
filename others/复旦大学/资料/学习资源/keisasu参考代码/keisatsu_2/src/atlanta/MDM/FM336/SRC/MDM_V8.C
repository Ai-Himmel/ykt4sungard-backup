/*----------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                   */
/*  ファイル名   : MDM_V8.c                                                   */
/*  作成者       :                                                            */
/*  日  付       : 1999/10/06                                                 */
/*  概  要       : Ｖ．８プロトコル関係                                       */
/*  修正履歴     :                                                            */
/*	keyword		 :[MDM]                                                       */
/*	machine		 :[SH7043,V53]                                                */
/*	language	 :[MS-C(Ver.6.0)]                                             */
/*----------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\sh7043\define\def_mbxn.h"	/* 1996/03/01 Y.M */
#include "\src\atlanta\define\evttomsg.h"	/* 1996/03/01 Y.M */
#include "\src\atlanta\sh7043\define\def_tib.h"		/* 1996/03/01 Y.M */
#include "\src\atlanta\define\param.h"		/* 1996/06/02 Y.M TEST */
#include "\src\atlanta\mdm\fm336\define\mdm_conf.h" /* Added by H. Kubo, 1997/06/19 */
#include "\src\atlanta\define\cmn_def.h"	/* Add By O.Kimoto 1998/03/24 */

#include "\src\atlanta\define\cmn_pro.h"		/* 1996/06/02 Y.M test */
#include "\src\atlanta\define\man_pro.h"		/* 1996/08/27 Y.M */
#include "\src\atlanta\define\uni_pro.h" /* by H.Kubo 1997/07/07 */
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\mnt_sw.h"

/*******
** ext_v
*******/
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"		/* 1996/02/27 Y.M F12 test */
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"		/* 1996/03/01 Y.M */

/*************************************************************************
	module		:[ＣＭフレームセット]
	function	:[
		1.
	]
	return		:[]
	common		:[
		MDM_ModemBuffer[0][0]	: Information sequence
		MDM_ModemBuffer[0][1]	: Synchronization sequence
		MDM_ModemBuffer[0][2]	: CM Flame 1st Octet
		MDM_ModemBuffer[0][3]	: CM Flame 2nd Octet
		MDM_ModemBuffer[0][4]	: CM Flame 3rd Octet
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_SetCmFrame(void){}]
	date		:[1995/11/27]
	author		:[木元　修]
*************************************************************************/
#if 0 /* メモリ節約のため、削除します。 by H.Kubo 1998/05/21 */
@@void  MDM_SetCmFrame(void)
@@{
@@	MDM_SetCmFrameSyncCm();
@@	MDM_SetCmFrameDataCallFunc((UBYTE)(MDM_V8_ControlStatus[0] & 0xE0));
@@	MDM_SetCmFrameModulation0(MDM_ModemBuffer[0][2]);
@@	MDM_SetCmFrameModulation1(MDM_ModemBuffer[0][3]);
@@	MDM_SetCmFrameModulation2(MDM_ModemBuffer[0][4]);
@@	MDM_SetCmFrameProtocol(0x00/** UBYTE status **/);
@@	MDM_SetCmFrameGSTN(0x00/** UBYTE status **/);
@@	MDM_SetCmFrameEnd();
@@}
#endif

/*************************************************************************
	module		:[ＣＭフレーム取得]
	function	:[
		1.
	]
	return		:[]
	common		:[
		MDM_ModemBuffer[0][0]	: Information sequence
		MDM_ModemBuffer[0][1]	: Synchronization sequence
		MDM_ModemBuffer[0][2]	: CI Flame 1st Octet
		MDM_ModemBuffer[0][3]	: CI Flame 2nd Octet
		MDM_ModemBuffer[0][4]	: CI Flame 3rd Octet
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_SetCmFrame(void){}]
	date		:[1995/11/27]
	author		:[木元　修]
*************************************************************************/
void  MDM_GetCmFrame(void)
{
}


/*************************************************************************
	module		:[ＣＩフレームセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_SetCiFrame(void){}]
	date		:[1995/11/27]
	author		:[木元　修]
*************************************************************************/
#if 0 /* メモリ節約のため、削除します。 by H.Kubo 1998/05/21 */
@@void  MDM_SetCiFrame(void)
@@{
@@	MDM_SetCiFrameSyncCi();
@@	MDM_SetCiFrameDataCallFunc((UBYTE)(MDM_V8_ControlStatus[0] & 0xE0));
@@	MDM_SetCiFrameEOF();
@@}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ＣＩフレーム取得]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	ProtoType	:[void far MDM_GetCiFrame(void){}]
//	date		:[1995/11/27]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_GetCiFrame(void)
//{
//}
#endif

/*************************************************************************
	module		:[ＪＭフレームセット]
	function	:[
		1.
	]
	return		:[]
	common		:[
		MDM_ModemBuffer[0][0]	: Information sequence
		MDM_ModemBuffer[0][1]	: Synchronization sequence
		MDM_ModemBuffer[0][2]	: JM Flame 1st Octet
		MDM_ModemBuffer[0][3]	: JM Flame 2nd Octet
		MDM_ModemBuffer[0][4]	: JM Flame 3rd Octet
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_SetJmFram(void){}]
	date		:[1995/11/27]
	author		:[木元　修]
*************************************************************************/
#if 0 /* メモリ節約のため、削除します。 by H.Kubo 1998/05/21 */
@@void  MDM_SetJmFrame(void)
@@{
@@	MDM_SetCmFrameSyncCm();
@@	MDM_SetCmFrameDataCallFunc((UBYTE)(MDM_V8_ControlStatus[0] & 0xE0));
@@	MDM_SetCmFrameModulation0(MDM_ModemBuffer[0][2]);
@@	MDM_SetCmFrameModulation1(MDM_ModemBuffer[0][3]);
@@	MDM_SetCmFrameModulation2(MDM_ModemBuffer[0][4]);
@@	MDM_SetCmFrameProtocol(0x00/** UBYTE status **/);
@@	MDM_SetCmFrameGSTN(0x00/** UBYTE status **/);
@@	MDM_SetCmFrameEnd();
@@}
#endif

/*************************************************************************
	module		:[ＪＭフレーム取得]
	function	:[
		1.
	]
	return		:[]
	common		:[
		MDM_ModemBuffer[0][0]	: JM Flame 1st Octet
		MDM_ModemBuffer[0][1]	: JM Flame 2nd Octet
		MDM_ModemBuffer[0][2]	: JM Flame 3rd Octet
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_GetJmFram(void){}]
	date		:[1995/11/27]
	author		:[木元　修]
*************************************************************************/
void  MDM_GetJmFrame(void)
{
	UBYTE	i;

	MDM_ModemBuffer[0][0] = 0xFF;
	MDM_ModemBuffer[0][1] = MDM_SetJmFrameSyncJm();			/* 中身はちゃんとﾘｰﾄﾞしてる */
	MDM_ModemBuffer[0][2] = MDM_GetJmFrameDataCallFunc();
	MDM_ModemBuffer[0][3] = MDM_GetJmFrameModulation0();
	MDM_ModemBuffer[0][4] = MDM_GetJmFrameModulation1();
	MDM_ModemBuffer[0][5] = MDM_GetJmFrameModulation2();
	MDM_ModemBuffer[0][6] = MDM_GetJmFrameProtocol();
	MDM_ModemBuffer[0][7] = MDM_GetJmFrameGSTN();
	MDM_ModemBuffer[0][8] = MDM_GetJmFrameEnd();

	MDM_RxSize[0] = 9;

	for(i = 0; i < 9; i++) {
		if (MDM_ModemBuffer[0][i] == 0x7E) {
			break;
		}
	}
	if (i < 9) {
		MDM_RxSize[0] = i;
	}
}



/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[V.8 Host Control BIts Set]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	ProtoType	:[void far MDM_SetV8ControlBits(void){}]
//	date		:[1995/11/29]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetV8ControlBits(void)
//{
//	MDM_SetV8ControlRegister1(0x88);	/** 304H **/
//	MDM_SetV8ControlRegister2(0xEF);	/** 305H **/
//	MDM_SetV8ControlRegister3(0x80);	/** 306H **/
//	MDM_SetV8ControlRegister4(0xC4);	/** 307H **/
//	MDM_SetV8ControlRegister5(0x80);	/** 308H **/
//	/*MDM_SetV8ControlRegister6(0x08);*/	/** 38FH **/
//	MDM_SetV8ControlRegister6(0x00);	/** 38FH **/
//
//}
#endif

/****************************************************************************/
/****************************************************************************/

/*************************************************************************
	module		:[起呼局のターンアラウンドポーリング開始処理]
	function	:[
		1.一旦、ＤＴＲをＯＦＦにする
		2.ＡＮＳａｍなし設定をする(38F:3 ON)
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1995/12/07]
	author		:[]
*************************************************************************/
void  MDM_SetUpTurnaroundModeORG(void)
{
UBYTE murata_debug;
murata_debug = 0;

if (murata_debug) {
	if (MDM_GetIO(POS_PNSUC)) {		/* 1996/02/19 Y.M */
		MDM_SetIO(POS_PNSUC, OFF);
	}

	MDM_SetV8ControlRegister6(0x08);	/** 38FH **/
	MDM_SetIO(POS_NEWC,ON);	/** Add by O.Kimoto **/

	MDM_SetIO(POS_DTR, OFF);

	MDM_SetIO(POS_CONF,V8_SETUP);		/* 1996/02/19 Y.M */

	MDM_SetIO(POS_NEWC,ON);
	MDM_SetIO(POS_NEWC,ON);	/** Add by O.Kimoto **/
}
else {	/* ちょっとかえる */
	if (MDM_GetIO(POS_PNSUC)) {		/* 1996/02/19 Y.M */
		MDM_SetIO(POS_PNSUC, OFF);
	}
	MDM_SetIO(POS_DTR, OFF);
	MDM_SetIO(POS_CONF,V8_SETUP);		/* 1996/02/19 Y.M */
	MDM_SetV8ControlRegister6(0x08);	/** 38FH **/
	MDM_SetIO(POS_NEWC,ON);
}


}

/*************************************************************************
	module		:[Ｖ８モード開始処理]
	function	:[
		1.Ｖ８モードにコンフィグする。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1995/12/07]
	author		:[]
*************************************************************************/
void  MDM_SetUpV8Mode(void)
{
	UBYTE debug;
	debug = 1;


	/* 1997/01/28 debug */
	MDM_SetIO(POS_CEQ, ON);

	if (StartUpData.Option.TransmitCI == TRANSMIT_CI_IN_V8) {
		MDM_SetIO(POS_CONF,V8_SETUP);

		/*
		** For Rockwell Advice By O.Kimoto 1996/07/11
		*/
		MDM_SetIO(POS_ORG,OFF);
		MDM_SetIO(POS_NEWC,ON);

		/*
		** For Rockwell Advice By O.Kimoto 1996/07/11
		*/
		MDM_SetIO(POS_ORG,ON);
		MDM_SetIO(POS_NEWC,ON);		/* Twice 1996/07/03 Y.Murata */
		MDM_SetIO(POS_NEWC,ON);

	}
	else {
		if (debug) {
			MDM_SetIO(POS_CONF,V8_SETUP);
			MDM_SetIO(POS_TXSQ, ON);	/* 送信器スケルチ ＯＮ */
			wai_tsk(2);
			MDM_SetIO(POS_NEWC,ON);
			MDM_SetIO(POS_TXSQ, OFF);	/* 送信器スケルチ ＯＦＦ */
		}
		else {
			MDM_SetIO(POS_CONF,V8_SETUP);
			MDM_SetIO(POS_NEWC,ON);
			MDM_SetIO(POS_NEWC,ON);	/* 1997/01/28 debug */
		}
	}
}

/*************************************************************************
	module		:[応答局のターンアラウンドポーリング開始処理]
	function	:[
		1.ＡＮＳａｍなし設定をする(38F:3 ON)
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1995/12/07]
	author		:[]
*************************************************************************/
void  MDM_SetUpTurnaroundModeANS(void)
{
	MDM_SetIO(POS_DTR, OFF);		/* 1996/03/13 Y.M */

	MDM_SetV8ControlRegister6(0x08);	/** 38FH **/
	MDM_SetIO(POS_NEWC,ON);	/** Add by O.Kimoto **/

	MDM_SetIO(POS_CONF,V8_SETUP);		/* 1996/02/19 Y.M */
	MDM_SetIO(POS_NEWC,ON);
	MDM_SetIO(POS_NEWC,ON);

	/* ターンアラウンドと時はＡＮＳａｍ無しにセットする V8 Control Bit 38F:3 をｾｯﾄする */
	/* ここではｾｯﾄしない */

}


/*************************************************************************
	module		:[モデムに端末情報を与える]
	function	:[
		1.モデムバッファの０番目を参照し、コントロールビットをセットする。
		2.CallFunctionAllowedをセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1995/12/07]
	author		:[]
*************************************************************************/
void  MDM_SetTerminalInformation(UBYTE Allowed)
{
	/*
	** とりあえず現段階ではｵﾌﾟｼｮﾝは無視
	*/
	WORD			pos;
	UBYTE	set_value[6];

	/*
	** V8 Contorol Bit Set この段階でﾓﾃﾞﾑﾊﾞｯﾌｧでﾃﾞｰﾀｾｯﾄ済み
	/*

	/******
	** 304H
	******/
	set_value[0] = 0x00;
	set_value[0] = (UBYTE)(MDM_ModemBuffer[0][2] & 0xE0);		/* Call Function */
	set_value[0] |= 0x08;								/* No PN+ID with ANSam */
	if (StartUpData.Option.TransmitCI == TRANSMIT_CI_IN_V8) {
		set_value[0] |= 0x04;							/* Transmit CI */

#if (0)
** 		/* ＣＩ Ｃａｄｅｎｃｅ調整用アドレスがおかしい By O.Kimoto 1999/03/11 */
** 		MDM_SetV8MaxFrameByteCount(30);	/** By O.Kimoto 1996/07/09 **/
#else
		DspRamAccessWriteMethod1((UWORD)0x102, (UBYTE)30, (UBYTE)0x00);
#endif

		DspRamAccessWriteMethod2((UWORD)0x3A6, (UWORD)0x3A7, (UWORD)0x960, (UWORD)0x0000);	/** Change CI Cadence By O.Kimoto 1996/07/22 **/
	}
	if ((StartUpData.Item == V34_MANUAL) &&
		(MDM_GetIO(POS_ORG) == 0)) {
		set_value[0] |= 0x02;		/* No TX of ANSam until CI Detect */
	}

	/******
	** 305H
	******/
	set_value[1] = 0x00;

	/******
	** 306H
	******/
	set_value[2] = 0x00;
	set_value[2] = (UBYTE)(MDM_ModemBuffer[0][3] & 0xC0);
	pos = 4;

	/******
	** 307H
	******/
	set_value[3] = 0x00;
	if (TxInformationCategoryByteCount > pos ) {
		if ((MDM_ModemBuffer[0][pos] & 0x38) == 0x10) {
			set_value[3] = (UBYTE)(MDM_ModemBuffer[0][pos] & 0xC7);
			pos++;

	/******
	** 308H
	******/
			if (TxInformationCategoryByteCount > pos ) {
				if ((MDM_ModemBuffer[0][pos] & 0x38) == 0x10) {
					set_value[4] = (UBYTE)(MDM_ModemBuffer[0][pos] & 0xC7);
					pos++;
				}
			}
		}
	}

	/*****
	** 38F
	*****/
	set_value[5] = 0x00;
	if (StartUpData.Item == V34_TURNAROUND) {
		set_value[5] = 0x08;
	}

	MDM_SetV8ControlRegister1(set_value[0]);	/** 304H **/
	MDM_SetV8ControlRegister2(set_value[1]);	/** 305H **/
	MDM_SetV8ControlRegister3(set_value[2]);	/** 306H **/
	MDM_SetV8ControlRegister4(set_value[3]);	/** 307H **/
	MDM_SetV8ControlRegister5(set_value[4]);	/** 308H **/
	MDM_SetV8ControlRegister6(set_value[5]);	/** 38FH **/


#if (0)
** 	/* 下記処理は不要です。 By O.Kimoto 1999/03/11 */
** 	if (StartUpData.Option.TransmitCI == TRANSMIT_CI_IN_V8) {	/* test */
** 		MDM_SetV8MaxFrameByteCount(30);	/** By O.Kimoto 1996/07/09 **/
** 	}
#endif

	/*-------------------------*/
	/* CallFunctionAllowed Set */
	/*-------------------------*/
	if (StartUpData.Allowed == TX_COM_MODE) {
		MDM_SetV8CallFunction(1);	/* 32Aの4ﾋﾞｯﾄ目のみｾｯﾄ(TX FAX) */
	}
	else if (Allowed == RX_COM_MODE) {
		MDM_SetV8CallFunction(2);	/* 32Aの5ﾋﾞｯﾄ目のみｾｯﾄ(RX FAX) */

#if (0)	
		/*
		** 動作確認は終っているが、今一つ安定性がないのでコメント
		** By O.Kimoto 1996/10/15
		*/
		/*
		** for DEBUG L8153-4 1.4 By O.Kimoto 1996/10/15
		*/
		if (SYS_ModemVersion != MDM_L6713_13P) {
			if (SYS_FaxCommStage == FCM_POLLING) {
				MDM_SetIO(POS_CONF,V8_SETUP);
				MDM_SetIO(POS_NEWC,ON);
				DspRamAccessWriteMethod1(0x104, 0x40, 0xBF);
			}
		}
#endif
	}
	else if (Allowed == (TX_COM_MODE | RX_COM_MODE)) {
		MDM_SetV8CallFunction(4);	/* 32Aの4ﾋﾞｯﾄ目と5ﾋﾞｯﾄ目の両方ｾｯﾄ( TX RX ) */

#if (0)	
		/*
		** 動作確認しないないのでコメント By O.Kimoto 1996/10/15
		*/
		/*
		** for DEBUG L8153-4 1.4 By O.Kimoto 1996/10/15
		*/
		if (SYS_ModemVersion != MDM_L6713_13P) {
			MDM_SetIO(POS_CONF,V8_SETUP);
			MDM_SetIO(POS_NEWC,ON);
			DspRamAccessWriteMethod1(0x104, 0x40, 0xBF);
			MDM_SetIO(POS_NEWC,ON);
		}
#endif

	}
}


/*************************************************************************
	module		:[データレイトの設定を行う]
	function	:[
		1.プライマリチャネルデータレイト設定
		2.コントロールチャネルデータレイト設定
		3.非対称データレイトレイト設定
		4.プライマリチャネル自動ＨＤＬＣモード設定
		5.モード設定
		6.プライマリチャネルボーレイト設定
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1995/12/07]
	author		:[]
*************************************************************************/
void  MDM_SetV34DataRate(void)
{
	UBYTE	data;

	/*---------------------------------*/
	/** シンボル・レートの設定をします */
	/*---------------------------------*/
	/*
	** ボーレイトマスク 1996/01/19 Y.M
	*/
	data = CHK_V34SymboleRate();
	data = (UBYTE)(data & 0x3D);
	if (data) {
		/*data = (UBYTE)(data & 0x3D); MOVE 1996/02/14 Y.M */
		MDM_SetV34SymbolRate(data);		/* $101 */
	}
	else {
		MDM_SetV34SymbolRate(0x19);		/* 3429 2800 はｵﾌﾟｼｮﾝなのでとりあえずﾏｽｸ */
	}

	/*-------------------------*/
	/** 通信速度の設定をします */
	/*-------------------------*/
	if (MDM_GetIO(POS_ORG)) {
#if 0 /* ワンタッチ属性が反映されない不具合を修正。 by H.Kubo 1999/07/05 */
@		data = CHK_TxBPS();
#else
		data = FCM_PtnrChkTxBPS();
#endif
	}
	else {
		data = CHK_RxBPS();
	}
	data = data + (UBYTE)(0xC0 + 1);

	if (data) {
		if ((data >= 0xC1) && (data <= 0xCE)) {
			MDM_SetModulationModeV34HDX(data);

			/*
			** 1997/01/26 Y.Murata
			*/
			if (data == 0xC1) {
				MDM_SetV34SymbolRate(0x01);		/* 3429 3200 3000 2800 ﾏｽｸ */
			}

		}
		else {
			MDM_SetModulationModeV34HDX(BPS28800_V34);	/* ﾌﾟﾗｲﾏﾘﾁｬﾈﾙﾃﾞｰﾀﾚｲﾄ($30A) 28.8K */
		}
	}
	else {
		MDM_SetModulationModeV34HDX(BPS28800_V34);	/* ﾌﾟﾗｲﾏﾘﾁｬﾈﾙﾃﾞｰﾀﾚｲﾄ($30A) 28.8K */
	}

	/*------------------------------*/
	/* V17 V29 V27ter Data Rate Set */
	/*------------------------------*/
	MDM_SetModulationModeV17(BPS14400_V17);
	MDM_SetModulationModeV29(BPS9600_V29);
	MDM_SetModulationModeV27(BPS4800_V27);


	/*-----------------------------------------*/
	/** コントロールチャネルの速度を設定します */
	/*-----------------------------------------*/
	if (CHK_V34ContorlChannelRate()) {
		MDM_SetIO(POS_CC,ON);		/* ｺﾝﾄﾛｰﾙﾁｬﾈﾙﾃﾞｰﾀﾚｲﾄ(09:6) CC=0:1200BPS  CC=1:2400BPS */
	}
	else {
		MDM_SetIO(POS_CC,OFF);		/* ｺﾝﾄﾛｰﾙﾁｬﾈﾙﾃﾞｰﾀﾚｲﾄ(09:6) CC=0:1200BPS  CC=1:2400BPS */
	}

	/*----------------------*/
	/* 各モードを設定します */
	/*----------------------*/
	MDM_SetASYMControlChRatesEnable(OFF);	/* 非対称データレイト(3DF[6]) */

	MDM_SetIO(POS_AUTO,OFF);	/* Automatic Mode Change Enable */
	MDM_SetIO(POS_DATA,ON);		/* Data */
	MDM_SetIO(POS_ASYN,OFF);	/* Asynchronous/Synchronous */
	MDM_SetIO(POS_TPDM,ON);		/* Transmitter Parallel Data Mode */
	MDM_SetIO(POS_HDLC,ON);		/* HDLC Select */
	MDM_SetIO(POS_FIFOEN,ON);	/* FIFIO Enable */

	MDM_SetIO(POS_CEQ, ON);		/* Compromise EqualizerEnable */	/* 1996/02/23 Y.M */
	MDM_SetIO(POS_ECFZ, OFF);	/* Echo Canceller Freeze */			/* 1996/02/23 Y.M */
	MDM_SetIO(POS_ECSQ, OFF);	/* Echo Canceller Squelch */		/* 1996/02/23 Y.M */
	MDM_SetIO(POS_FECSQ, OFF);	/* Far Echo Canceller Squelch */	/* 1996/02/23 Y.M */

#if defined (SAKAKI) /* SAKAKI の V8 テスト用です。 by H.Kubo 1998/10/04 *//* 2002/09/18 By M.Maeda */
	MDM_SetIO(POS_EARC,ON);
#endif

	/*-----------------------------------------------------*/
	/* Forced 2400 Symbol Rate when Probing SNR is Adverse */
	/*-----------------------------------------------------*/
	data = CHK_V34Forced2400SymbolRateSNR();
	if (data) {
		MDM_SetForced2400SymbolRateSNR(data);
	}

	data = CHK_V34Disable3429SymbolRateSNR();
	if (data) {
		MDM_Disable3429SymbolRateSNR(data);
	}

	/*
	** Add some PC delay - L8152-2 and higher - palm - 03 may 96
	** RFSPXWriteMethod1(0x0202, 0x3F);  * Delay CTS by 63 symbols *
	** By O.Kimoto 1996/05/17
	*/
	if (MDM_GetIO(POS_ORG)) {
		DspRamAccessWriteMethod1(0x202, 0x3F, 0x00);
	}
}

/*************************************************************************
	module		:[起呼局ターンアラウンドポーリングのＶ８手順開始]
	function	:[
		1.ＤＴＲのＯＦＦからＯＮまで７０ｍｓウエイト
		2.ＤＴＲをＯＮにする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1995/12/07]
	author		:[]
*************************************************************************/
void  MDM_StartGoTurnaroundModeORG(void)
{
	MDM_SetIO(POS_DTR, ON);
}

/*************************************************************************
	module		:[Ｖ８手順開始]
	function	:[
		1.ＤＴＲをＯＮにする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1995/12/07]
	author		:[]
*************************************************************************/
void  MDM_StartGoV8Mode(void)
{
	MDM_SetIO(POS_DTR, ON);
}


/*************************************************************************
	module		:[ＣＩ送出]
	function	:[
		1.Ｖ８モードにコンフィグし、ＤＴＲをＯＮにした後コールされる。
		2.ＣＩ送信開始の指示(304:2)だけを行い、すぐ抜ける。
		3.ＣＩの送信はＡＮＳａｍを検出し、３フレームのＣＩを送信するまで
		　行われる。（停止はモデムがオートで行う）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_V8TransmitCI(void)
{
}

/*************************************************************************
	module		:[ＣＩストップ]
	function	:[
		1.ＡＮＳａｍを検出したのち、ＣＩを３フレーム送信して停止する。
		2.ＣＩの停止は、今回のモデムはオートで行うはずやから何もしなくても
		　よいはず。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_V8StopCI(void)
{
	/* なにもしない */
	return;
}

/*************************************************************************
	module		:[ＡＮＳａｍを検出したかどうか]
	function	:[
		1.起呼局においてＶ８モード中にＡＮＳａｍを検出したかどうかチェック
		　する。(V8 Status Bits)
	]
	return		:[
					1: ANSamを検出した
					0: ANSamを検出していない
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE  MDM_V8DetectANSam(void)
{
	if (MDM_GetV8StatusRegister2() & 0x08) {
		return(1);
	}
	else {
		return(0);
	}
	return(1);
}
/*************************************************************************
	module		:[ＡＮＳ（ＣＥＤ）を検出したかどうか]
	function	:[
		1.起呼局においてＶ８モード中にＡＮＳ（ＣＥＤ）を検出したかどうか
		　チェックする。(V8 Status Bits)
	]
	return		:[
					1: ANS(CED)を検出した
					0: ANS(CED)を検出していない
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE  MDM_V8DetectANS(void)
{
	if (MDM_GetV8StatusRegister1() & 0x20) {
		return(1);
	}
	else {
		return(0);
	}
}

/*************************************************************************
	module		:[CIを検出したかどうか]
	function	:[
		1.起呼局においてＶ８モード中にCIを検出したかどうか
		　チェックする。(V8 Status Bits)
	]
	return		:[
					1: CIを検出した
					0: CIを検出していない
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE  MDM_V8DetectCI(void)
{
	if (MDM_GetV8StatusRegister1() & 0x02) {
		return(1);
	}
	else {
		return(0);
	}
}

/*************************************************************************
	module		:[ＡＮＳａｍ送出]
	function	:[
		1.Ｖ８モードにコンフィグし、ＤＴＲをＯＮにした後コールされる。
		2.ＡＮＳａｍ送信開始指示だけを行い、すぐ抜ける
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_V8TransmitANSam(void)
{
	/* ORG=0 でDTR=1 でANSamが送出されるので多分ここでは何もしないと思う */
}
/*************************************************************************
	module		:[ＡＮＳａｍストップ]
	function	:[
		1.Ｖ８モードにコンフィグし、ＤＴＲをＯＮにした後コールされる。
		2.ＡＮＳａｍの停止処理だけを行い、すぐ抜ける
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_V8StopANSam(void)
{
	/* これも多分、ここでは何もしないと思う */
}

/*************************************************************************
	module		:[ＡＮＳａｍ送信中かのチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1996/02/19]
	author		:[村田]
*************************************************************************/
UBYTE  MDM_V8CheckTransmittingANSam(void)
{
	UBYTE	value;
	value = DspRamAccessReadMethod1(0x300);			/* $300 V8 status bit */
	if (value & 0x01) {
		return(1);
	}
	else {
		return(0);
	}
}


/*************************************************************************
	module		:[Ｖ８モード中のＶ２１チャンネル２フラグ検出タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		とりあえず引き数の構造体はMESSAGEを使います。
		わかりにくかったら、また変えましょう。
				MESSAGE.Item			:送信メイルＢＯＸ
				MESSAGE.Message			:送信メッセージ
				MESSAGE.SubMessage1		:未使用
				MESSAGE.SubMessage2		:未使用
				MESSAGE.SubMessage3		:未使用
	]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_DetectV21Ch2FlagV8Task(MESSAGE_t	*data)
{
	struct		Timer10msData_t		TimeUpV21;
	struct		EventToMessageData_t 	V21EvtOff;
	MESSAGE_t		msg;
	MESSAGE_t		*v21_receive;
	UWORD		return_mbxno;
	UWORD		StartOffTime;
	UWORD		OffTime;

	StartOffTime = 0;
	OffTime = 0;
	MDM_V21Ch2FlagV8TaskInitial();

	while(1) {
		/*
		** フィルター２ ＯＮのイベントを待ちます
		*/
		wai_evt(EVT_TONE_FILTER2_ON);

		/************************************
		** フィルター２の瞬断検出用タスク起動
		************************************/
		if (tskno_v21_off == 0xFFFF) {
			V21EvtOff.SendMBX = mbxno.MDM_V21DetectTask;
			V21EvtOff.DetEventNo = EVT_TONE_FILTER2_OFF;
			V21EvtOff.ReturnValue = V21_CH2_FLAG_OFF;
			cre_tsk(&tskno_v21_off, TSK_CMN_EVENTTOMESSAGETASK, &V21EvtOff);
		}

		if (StartOffTime != 0) {
			OffTime = SYS_GeneralTimer - StartOffTime;
			if (OffTime > 10) {	/*瞬断でない時*/
				StartOffTime = 0;
				MDM_V21Ch2FlagV8TaskDelete();
				continue;					/* 初めからやり直し */
			}
		}
		else {
			/* 検出用タイマー起動 */
			if (tskno_v21_timeup == 0xFFFF) {
				TimeUpV21.Time = 30;	/* ３００ｍｓ because not detect NSS by V21H Mode 1996/10/23 Y.Murata */
				TimeUpV21.ReturnValue = FCM_TIME_UP;
				TimeUpV21.SendMBX = mbxno.MDM_V21DetectTask;
				cre_tsk(&tskno_v21_timeup, TSK_CMN_MAN_TIMER10MSTASK, &TimeUpV21);
			}
		}

		rcv_msg(mbxno.MDM_V21DetectTask, &v21_receive);

		if (v21_receive->Message == FCM_TIME_UP) {	/* 検出完了 */
			MDM_V21Ch2FlagV8TaskDelete();
			return_mbxno = data->Item;
			msg.Message = data->Message;
			msg.Item = FROM_MDM_DETECT_V21FLAG;
			snd_msg(return_mbxno, &msg);
			wai_tsk(0xFFFF);
		}
		else {		/* 瞬断検出 */
			StartOffTime = SYS_GeneralTimer;
			if (tskno_v21_off != 0xFFFF) {
				del_tsk(&tskno_v21_off);
			}
		}
	}	/* End Of while */
}


void  MDM_DetectV21Ch2FlagV8TaskExit(void)
{
	MDM_V21Ch2FlagV8TaskDelete();
	exi_tsk();
}


void  MDM_V21Ch2FlagV8TaskDelete(void)
{
	if (tskno_v21_timeup != 0xFFFF) {
		del_tsk(&tskno_v21_timeup);
	}
	if (tskno_v21_off != 0xFFFF) {
		del_tsk(&tskno_v21_off);
	}
}

void  MDM_V21Ch2FlagV8TaskInitial(void)
{
	tskno_v21_timeup = 0xFFFF;
	tskno_v21_off = 0xFFFF;
}





/*************************************************************************
	module		:[Ｖ８オクテットの読み込み]
	function	:[
		1.
	]
	return		:[]
	common		:[
		1996/02/17  もしＶ８オクテットを検出できなかった時にバッファを崩す件対応
	]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE  MDM_V8OctetMonitoring(void)
{
	UWORD		i, point, inflag, count;
	UWORD		first_frame_pos, second_frame_pos;

	first_frame_pos = 0xFFFF;
	second_frame_pos = 0xFFFF;
	point = 0;
	inflag = 0;
	count = 0;							/* 1996/02/17 Y.M */

	if (MDM_RxSize[0] != 0) {
		for (i = 0; i < MDM_RxSize[0]; i++) {
			if (MDM_ModemBuffer[0][i] == 0xE0) {	/* CM,JM 同期符号 */
				if (first_frame_pos == 0xFFFF) {
					first_frame_pos = i;
					inflag = 1;
				}
				else {
					if (second_frame_pos != 0xFFFF) {
						first_frame_pos = second_frame_pos;
					}
					second_frame_pos = i;
					count = i - first_frame_pos;
					inflag = 0;
					point = 0;
				}
			}
			else {
				if (second_frame_pos != 0xFFFF) {
					if ((point + 1) < 50) {		/* FCM_MonitorData[50] 1996/02/17 Y.M */
						if (FCM_MonitorData[point + 1] != MDM_ModemBuffer[0][i]) {
							FCM_MonitorData[point + 1] = MDM_ModemBuffer[0][i];
						}
						point++;
					}
				}
			}
			if (inflag) {
				if (point < 50) {		/* FCM_MonitorData[50] 1996/02/17 Y.M */
					FCM_MonitorData[point] = MDM_ModemBuffer[0][i];
					point++;
				}
			}
		}
		MDM_ModemBuffer[0][0] = 0xFF;
		for (i = 0; i < count; i++) {
			MDM_ModemBuffer[0][i + 1] = FCM_MonitorData[i];
		}
		if (count) {
			MDM_RxSize[0] = count + 1;
		}
		else {
			MDM_RxSize[0] = 0;
			MDM_ModemBuffer[0][0] = 0x00;
		}
	}
	return(1);
}


/*************************************************************************
	module		:[モデムをAnswer Modeに設定する]
	function	:[
		1.コールされる状態は以下の時
		　・受信で通信が起動される時
		　・Ｖ８終了時にポーリング受信が確定した時
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_SetAnswerMode(void)
{
	MDM_SetIO(POS_CEQ, OFF);	/* BATUU 1999/06/02 Y.M for test */


	/** For Rockwell Advice By O.Kimoto 1996/07/11 **/
	MDM_SetIO(POS_ORG, OFF);		/* ORGﾋﾞｯﾄのﾘｾｯﾄ */
	MDM_SetIO(POS_NEWC, ON);		/* NEWCｾｯﾄ */
	MDM_SetIO(POS_ORG, OFF);		/* ORGﾋﾞｯﾄのﾘｾｯﾄ */
	MDM_SetIO(POS_NEWC, ON);		/* NEWCｾｯﾄ */
}


/*************************************************************************
	module		:[モデムをOriginate Modeに設定する]
	function	:[
		1.コールされる状態は以下の時
		　・送信で通信が起動される時
		　・Ｖ８終了時にポーリング送信が確定した時
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_SetOriginateMode(void)
{
	MDM_SetIO(POS_CEQ, OFF);	/* BATUU 1999/06/02 Y.M for test */

	/** For Rockwell Advice By O.Kimoto 1996/07/11 **/
	MDM_SetIO(POS_ORG, OFF);		/* ORGﾋﾞｯﾄのﾘｾｯﾄ */
	MDM_SetIO(POS_NEWC, ON);		/* NEWCｾｯﾄ */
	MDM_SetIO(POS_ORG, ON);			/* ORGﾋﾞｯﾄのｾｯﾄ */
	MDM_SetIO(POS_NEWC, ON);		/* NEWCｾｯﾄ */
}


/*************************************************************************
	module		:[受信した起呼機能を読み出す]
	function	:[
	]
	return		:[読み出したデータ(下位ビットの０ー４は０固定)]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE  MDM_V8StatusCallFunctionData(void)
{
	UBYTE	value;

	/*
	** Table 9-2 V8 Status Bits($302)よりリードする
	*/
	value = MDM_GetV8StatusRegister2();
	value = (UBYTE)(value & 0xE0);		/* 下位5ﾋﾞｯﾄﾏｽｸ */
	return(value);
}


/********************************/
/**********   Ｖ３４   **********/
/********************************/
/*************************************************************************
	module		:[]
	function	:[
		1.	この関数は、ラインプロービングが終了した時（SEXRXB>=4X）にコールされる。
			シンボルレートをリードし、そのシンボルレートから ARAinRAmのセットを行う
			尚、この関数はプライマリチャネル指示で受信の時のみコールされる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_V34ManagementAfterProbing(void)
{
	UBYTE	data;

	data = 0;

	FCM_SignalToNoiseRatio = (UWORD)(DspRamAccessReadMethod1(0x11E));
	FCM_LowBandEdgeFrequency = (UWORD)(DspRamAccessReadMethod1(0x11C));
	FCM_HighBandEdgeFrequency = (UWORD)(DspRamAccessReadMethod1(0x11D));
	FCM_TxLevelReduction = (UWORD)(DspRamAccessReadMethod1(0x0E2));		/* Add By O.Kimoto 1996/07/25 */
	FCM_PreEmphasisFilter = (UWORD)(DspRamAccessReadMethod1(0xB44));	/* Add By O.Kimoto 1996/04/18 */

	MDM_GetARAThreshold();

	/*
	** ﾒﾓﾘSW設定でARA Algorithm をｾｯﾄします 1996/02/21 Y.M
	*/
	if (CHK_V34ARA_AlgorithmEnable()) {
		MDM_SetIO(POS_EARC,ON);
		MDM_SetIO(POS_ARC,ON);

		/*----------------------------*/
		/* ＡＲＡの最高速通信時の調整 */
		/*----------------------------*/ /* 1996/08/26 Y.Murata */
		if (SYS_ModemVersion == MDM_L6713_13P) {	/* 1996/10/11 Y.M */
			MDM_SetARA_HighSpeedRate();
		}

		/*
		** 1997/01/26 Y.Murata
		** ＡＲＡテーブルをROMを使えるようにUNISW追加
		*/
		if (CHK_V34ARA_ThresholdARAinROM()) {	/* UNISW D3:7 */
			MDM_GetARAThreshold();	/* write ok ? check */
		}
		else {
			MDM_SetARAinRAM_FunctionEnable(ON);		/* 3A5:4 set */

			if (V34BaudDataRate < 6 ) {
				MDM_SetARAThreshold(V34BaudDataRate);
			}
			MDM_GetARAThreshold();	/* write ok ? check */
		}
	}
}

/*************************************************************************
	module		:[ＡＢＣＯＤＥ監視タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_ABCODE_Task(UWORD *return_mbxno)
{
	MESSAGE_t		msg;

	CMN_DisableInterrupt();		/** 割り込み禁止 */
	if (SYS_DetectABCODE_Flag == 0) {
		wai_evt(EVT_MDM_ABCODE);
	}
	SYS_DetectABCODE_Flag = 0;

	/*
	** L8153-4 2.1 V.34 Error Recovery On Poor Lines
	*/
	if (CHK_RecoverLineProblingProblem()) {	/* 1996/09/13 Y.M */
		/*
		** 下記処理はＣａｌｌＭｏｄｅｍのみです。
		*/
		if (MDM_GetIO(POS_ORG) == ON) {
			if ((MDM_AbortCode == 0x25) || (MDM_AbortCode == 0x2A) || (MDM_AbortCode == 0x2B)) {
				MDM_SetIO(POS_NEWC, ON);		/* NEWCｾｯﾄ */
			}
		}
	}

	CMN_EnableInterrupt();		/** 割り込み許可 */

	if (CHK_V34ModemAbcodeEnable()) {	/* ABCODEを無視するか */
		msg.Item = FROM_ABCODE;
		msg.Message = (UWORD)MDM_AbortCode;
		snd_msg(*return_mbxno, &msg);
	}
	wai_tsk(0xFFFF);

}



/*************************************************************************
	module		:[Ｖ８モードからＶ２１Ｃｈ２モードの設定]
	function	:[
		1.Ｖ８モードを終了し、通常Ｔ３０手順に移行する時コールされる
		2.Ｖ２１チャンネル２モードにコンフィグする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_ManagementV8EndToT30(void)
{
	/*
	**
	*/
	MDM_SetIO(POS_DTR,OFF);
	MDM_SetIO(POS_CEQ,OFF); /*1997/02/05*/
	MDM_SetIO(POS_NEWC,ON); /*1997/02/05*/
}

/*************************************************************************
	module		:[Ｖ８モード、Ｖ３４スタートアップエラー時のコンフィグ設定]
	function	:[
		1.Ｖ８モード、Ｖ３４スタートアップモード中にエラーは発生時にコール
		　される
		2.?
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_ManagementV34StartUpEnd(void)
{
	/*
	** とりあえず
	*/
	MDM_SetIO(POS_DTR,OFF);
}

/*************************************************************************
	module		:[Ｖ３４コントロールチャネルターンＯＦＦ]
	function	:[
		1.コントロールチャネルのｔｕｒｎ－ｏｆｆを行う
		2.フラグの終了（無音）を検出する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE  MDM_ControlChanelTurnOff(void)
{
	/** プライマリチャンネルでＥＣＭフレームが壊れる件 By O.K Feb.05,1996 **/
	CMN_DisableInterrupt();
	MDM_CtsTurnOffFlag = 0;
	MDM_CtsTurnOffCheckFlag = TRUE;
	dbg_old_cts_status = (UBYTE)(inp(MDM_REG_0F_PORT) & IO_BIT_CTS);
	CMN_EnableInterrupt();

	/* RTS ON */
	MDM_SetIO(POS_RTS, ON);

	/** プライマリチャンネルでＥＣＭフレームが壊れる件 By O.K Feb.05,1996 **/
	CMN_DisableInterrupt();
	if (! MDM_CtsTurnOffFlag) {
		wai_evt(EVT_MDM_PNSUC);	/**  By O.K Feb.05,1996 **/
	}
	MDM_CtsTurnOffFlag = 0;
	MDM_CtsTurnOffCheckFlag = FALSE;
	CMN_EnableInterrupt();

	return(OK);
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[Ｖ３４コントロールチャネルターンＯＦＦ検出]
//	function	:[
//		1.ｔｕｒｎ－ｏｆｆを検出する（連続４０個の「１」）
//		2.ｔｕｒｎ－ｏｆｆを検出する前にＦＳＫを検出すればＦＳＫを受信する
//	]
//	return		:[
//	]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	date		:[]
//	author		:[]
//*************************************************************************/
//UBYTE  MDM_ControlChanelDetectTurnOff(void)
//{
//	return(TURN_OFF_RECEIVE);
//}
#endif

/*************************************************************************
	module		:[受領証送信時、Ｖ８モードに入るためのコントロールチャネルの
				  ターンＯＦＦ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE  MDM_ControlChTurnaroundTurnOff(void)
{
	UWORD	timer;

	timer = 0;

	MDM_SetIO(POS_MHLD, ON);	/* MHLD(07:0) set */

	while (timer <= 300) {	/* 規定時間 とりあえず 3000ms*/

		/* 1996/05/14 Y.Murata
		 * ＲＬＳＤがＯＦＦしない（ﾓﾃﾞﾑのﾊﾞｸﾞ）
		 * その対策としてＦＥＤとＲＬＳＤで、どちらかがＯＦＦすればＯＫとする
		*/
		if ((!(MDM_GetIO(POS_FED))) || (!(MDM_GetIO(POS_RLSD)))){	/* FED OFF ? or RLSD OFF ? */
			if (MDM_GetIO(POS_MHLD)) {
				MDM_SetIO(POS_MHLD, OFF);
			}
			return(OK);
		}
		wai_tsk(1);		/* 10ms */
		timer++;
	}
	return(NG);
}


/*************************************************************************
	module		:[Ｖ３４コントロールチャネルＯＦＦ]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE  MDM_ControlChanelOff(void)
{
	UWORD		timer;

	timer = 0;

	MDM_SetIO(POS_RTS, ON);

	while (timer <= 100) {	/* 規定時間 とりあえず 1000ms*/
		if (!(MDM_GetIO(POS_RLSD))) {	/* RLSD OFF ? */
			MDM_SetIO(POS_RTS, OFF);
			MDM_SetIO(POS_DTR,OFF);
			return(OK);
		}
		wai_tsk(1);
		timer++;
	}
	return(NG);
}


/*************************************************************************
	module		:[Ｖ３４プライマリチャネルターンＯＦＦ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_PrimaryChanelTurnOff(void)
{

	/** プライマリチャンネルでＥＣＭフレームが壊れる件 By O.K Feb.05,1996 **/
	CMN_DisableInterrupt();
	MDM_CtsTurnOffFlag = 0;
	MDM_CtsTurnOffCheckFlag = TRUE;
	dbg_old_cts_status = (UBYTE)(inp(MDM_REG_0F_PORT) & IO_BIT_CTS);
	CMN_EnableInterrupt();

	/* RTS OFF */
	MDM_SetIO(POS_RTS, OFF);

	/** プライマリチャンネルでＥＣＭフレームが壊れる件 By O.K Feb.05,1996 **/
	CMN_DisableInterrupt();
	if (! MDM_CtsTurnOffFlag) {
		wai_evt(EVT_MDM_PNSUC);	/**  By O.K Feb.05,1996 **/
	}
	MDM_CtsTurnOffFlag = 0;
	MDM_CtsTurnOffCheckFlag = FALSE;
	CMN_EnableInterrupt();

}

/*************************************************************************
	module		:[プライマルチャネルデータ速度の書き換え]
	function	:[
		1.引き数で指定さえたデータレイトに変更する。
		2.プライマリチャネルのターンｏｆｆを行う前にコールされる
		3.引き数はＦＣＭで宣言されたデータレイトなので注意！
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  MDM_V34DataRateChange(UBYTE rate)
{
	MDM_SetIO(POS_CONF, rate);
}


/*************************************************************************
	module		:[プライマルチャネルデータ速度の読み込み]
	function	:[
		1.モデムのレジスタをリードする。
		2.通信で使っているdefineと異なるので変更時注意
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE  MDM_TxDataRateRead(void)
{
	return(MDM_GetIO(POS_SPEED));
}

/*************************************************************************
	module		:[プライマルチャネルデータ速度の読み込み]
	function	:[
		1.モデムのレジスタをリードする。
		2.通信で使っているdefineと異なるので変更時注意
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE  MDM_RxDataRateRead(void)
{
	return( MDM_GetV34RxSpeedIndication());
}


/*************************************************************************
	module		:[モデムをアイドル状態にする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1996/02/24]
	author		:[村田]
*************************************************************************/
void  MDM_SetModemIdle(void)
{
	MDM_SetIO(POS_DTR,OFF);
}


/*************************************************************************
	module		:[モデムのスピーカーのボリュームを制御する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1996/03/07]
	author		:[村田]
*************************************************************************/
void  MDM_SetVolumeAttenuationLevel(UBYTE level)
{
	switch (level) {
	case SYS_VOLUME_MINIMUM:
		MDM_SetIO(POS_VOLUME, VOLUME_SMALL);
		break;
	case SYS_VOLUME_MIDDLE:
		MDM_SetIO(POS_VOLUME, VOLUME_MID);
		break;
	case SYS_VOLUME_MAXIMUM:
		MDM_SetIO(POS_VOLUME, VOLUME_LARGE);
	 	break;
	default:
		MDM_SetIO(POS_VOLUME, VOLUME_OFF);	
		break;
	}
}


/*************************************************************************
	module		:[コントロールチャネルリトレーン]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1996/04/25]
	author		:[村田]
*************************************************************************/
void  MDM_SetControlChannelRetrain(void)
{
	/* とりあえず ちょく書き */
	UBYTE	check;

	check = inp(CCRTN_PORT);
	check |= 0x20;
	outp(CCRTN_PORT, check);
}




/*************************************************************************
	module		:[ＡＲＡの最高速通信時の調整]
	function	:[
		1.シンボルレートが3429の時に、SN比によって33.6k 31.2kをﾏｽｸするか決める
		2.厳密には、速度をﾏｽｸするのではなく、最高速を決める
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1996/08/27]
	author		:[村田]
*************************************************************************/
void  MDM_SetARA_HighSpeedRate(void)
{
	UBYTE	value;

	if (V34BaudDataRate == 5) {	/* 3429symbol rate */

		value = CHK_RxBPS();
		value = value + (UBYTE)(0xC0 + 1);
		value = MDM_R288F_MemBitCONF_ToBPS(value); /* translation from CONF value to globally defined value. 1997/06/19 by H. Kubo*/
		if ((value == BPS33600_V34) || (value == BPS31200_V34)) {	/* 33.6k or 31.2k */
			if (FCM_SignalToNoiseRatio >= 0x0023) {	/*  */
				/* Nothing */
			}
			else if ((FCM_SignalToNoiseRatio >= 0x001B) && (FCM_SignalToNoiseRatio <= 0x0022)) {
				/* 33.6Kbps mask */
				DspRamAccessWriteMethod1(0x37A, 0x0D, 0x00);
			}
			else {
				/* 33.6Kbps and 31.2Kbps mask */
				DspRamAccessWriteMethod1(0x37A, 0x0C, 0x00);
			}
		}
	}
	else if (V34BaudDataRate == 4) {	/* 3200symbol rate */
		value = CHK_RxBPS();
		value = value + (UBYTE)(0xC0 + 1);
		if ((value == BPS33600_V34) || (value == BPS31200_V34)) {	/* 33.6k or 31.2k */
			if (FCM_SignalToNoiseRatio >= 0x0023) {	/*  */
				/* Nothing */
			}
			else {
				/* 31.2Kbps mask */
				DspRamAccessWriteMethod1(0x37A, 0x0C, 0x00);
			}
		}
	}
	else if (V34BaudDataRate == 3) {	/* 3000symbol rate */
	}
	else if (V34BaudDataRate == 2) {	/* 2800symbol rate */
	}
	else if (V34BaudDataRate == 1) {	/* 2743symbol rate */
		/* Nothing */
	}
	else if (V34BaudDataRate == 0) {	/* 2400symbol rate */
		if (FCM_SignalToNoiseRatio >= 0x001B) {	/*  */
			/* Nothing */
		}
		else {
			/* 21.6Kbps mask */
			DspRamAccessWriteMethod1(0x37A, 0x08, 0x00);
		}
	}
	else {
	}
}


/*************************************************************************
	module		:[位相ジッタを測定し、最高通信速度を決定する]
	function	:[
		1.受信スタートアップフェーズ３の時にコールされる
		2.ＳＥＣＲＸＢ ＝ ０ｘ４７になってから １００ｍｓウエイト
		3.ファンクション４９Phase Jitter Frequency ５０Phase Jitter Amplitude
			をリードする
		4.通信最高速度を決定する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1996/08/27]
	author		:[村田]
*************************************************************************/
void  MDM_SetARA_PhaseJitterRate(void)
{
	UBYTE	value;
	UBYTE	exit_flag;
	UWORD			start_timer;

	exit_flag = 0;
	start_timer = SYS_GeneralTimer;
	while (1) {
		value = MDM_GetIO(POS_SECRXB);
		if (value >= 0x47) {
			exit_flag = 0;
			break;
		}
		if ((UWORD)(SYS_GeneralTimer - start_timer) > 3000) {	/*cast by M.Kotani 97/10/08*/
			exit_flag = 1;
			break;
		}
		if (SYS_FaxComStopSwitch()) {
			exit_flag = 1;
			break;
		}
		wai_tsk(5);
	}
	if (exit_flag == 0) {

		start_timer = SYS_GeneralTimer;
		while (1) {
			FCM_PhaseJitterFrequencyValue = DspRamAccessReadMethod4(0x80E);
			FCM_PhaseJitterAmplitudeValue = DspRamAccessReadMethod4(0x80D);
			wai_tsk(10);
			if ((UWORD)(SYS_GeneralTimer - start_timer) > 20) {	/*cast by M.Kotani 97/10/08*/
				break;
			}
		}
	}
}


/*************************************************************************
	module		:[３３．６Ｋ ３１．２Ｋ選択時の微調整]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1996/10/11]
	author		:[村田]
*************************************************************************/
void  MDM_FinetuneSelection336or312(void)
{
	/** L8153-3 Release Note 1.8 Fine tune Selection of 33.6/31.2 By O.Kimoto 1996/10/9 **/
	DspRamAccessWriteMethod1(0x00D4,0x02,0xFD);
}
