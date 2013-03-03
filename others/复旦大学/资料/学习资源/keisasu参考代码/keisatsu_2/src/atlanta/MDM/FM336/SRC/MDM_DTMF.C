/*---------------------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                              */
/*  ファイル名   : mdm_dtmf.c                                                            */
/*  作成者       :                                                                       */
/*  日  付       : 1999/10/06                                                            */
/*  概  要       : ＤＴＭＦ送出関数                                                      */
/*	keyword			:[MDM]                                                               */
/*	machine			:[SH7043,V53]                                                        */
/*	language		:[MS-C(Ver.6.0)]                                                     */
/*  修正履歴     :                                                                       */
/*---------------------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\define\param.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"

/********
** ext_v
********/
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#if (PRO_NCU_TYPE == HINOKI_TYPE) /* 1999/02/22 by T.Soneoka */ /* ported by T.Takagi 2001/12/17 */
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mon.h"
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/24 */
#include "\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\hinoki\define\m_param.h"
#endif		/* End of (defined (KEISATSU)) */
/*************************************************************************
	module		:[ＤＴＭＦ送出関数（時間指定有り）]
	function	:[
		1.指定されたＤＴＭＦ送出テーブルのトーンを指定時間送出する
	]
	return		:[なし]
	common		:[]
	condition	:[
		called by ATD_OUTD.C unsigned char	far	OutPutDial();
	]
	comment		:[]
	date		:[1994/02/08]
	author		:[曽根岡拓]
*************************************************************************/
void  MDM_DTMF_Tx(
UBYTE dial_no,	/*	ＤＴＭＦ送出テーブルＮｏ．	*/
UWORD time_out) 	/* 送出期間 （ｍｓ）	*/
{
	/* 1996/11/29 Y.Murata
	 * DTMF設定で自動ダイアルを行う場合、１桁ずつDTMFを出し
	 * そのたびに、DTMF Open と Close をするとコンフィグに時間がかかり
	 * メイク、ブレーク時間が正しくでない
	 * Closeは全部のダイアルを発呼してから行うようにする
	 * Openは、DTMFモードでなかったらOpenするようにする
	*/

	MDM_DTMF_Open();		/* ??????? */

	MDM_DTMF_Set(dial_no);

	MDM_SetIO(POS_RTS,ON);
	/*wai_tsk(time_out/10); 1996/11/28 Y.Murata */
/*
** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
** 確認して使用することにする
** 1999/02/22 by T.Soneoka
*/
#if (PRO_NCU_TYPE == HINOKI_TYPE)	/* ported by T.Takagi 2001/12/17 */
	if (wai_1shot_tid == 0xFF) {
		wai_oneshot(time_out);
	} else {
		wai_tsk((UWORD)((time_out / 10) + 1));
	}
#else
	wai_oneshot(time_out);
#endif
	MDM_SetIO(POS_RTS,OFF);

#if 0	/* 1996/11/28 Y.M */
//	MDM_DTMF_Close();		/* ??????? */
#endif
}


/*************************************************************************
	module		:[ＤＴＭＦ検出タスク]
	function	:[
		1.ＤＴＭＦ検出モードに設定
		2.モデムステータスレジスタ－ＤＴＭＦ検出表示レジスタをリードします
		3.ＤＴＭＦシンボルコードをＡＳＣＩＩに変換し、メッセージ送信します
	]
	return		:[なし]
	common		:[
	]
	condition	:[
		Created by NCU_SUB2.C	NCU_ReceiveDTMFTask();
	]
	comment		:[]
	date		:[1994/02/08]
	author		:[曽根岡拓]
*************************************************************************/
void  MDM_DetectDtmfTask(UWORD	*mbx_no)
{
#if (0) /* POPLAR_H の DTMF 検出は NCU で行うので、このタスクはいりません。 H.Kubo 1997/12/10 */
	UBYTE dtmf_code;
	UBYTE status;
	UBYTE on_detect;
	UBYTE dtmf_symbol;
	UWORD  on_time;
	UWORD  off_time;
	UWORD  time_count;

#if (0) /* Deleted by H.Kubo 1997/12/10 */
	if (SYB_MachineParameter[40] & 0x08) {
		if ((on_time = (UWORD)SYB_MachineParameter[45]) == 0) {
			on_time = 4;	/* Default:40ms */
		}
		if ((off_time = (UWORD)SYB_MachineParameter[46]) == 0) {
			off_time = 4;	/* Default:40ms */
		}
	}
#endif /* (0) */

#if (0)	/** 本来は以下の通り処理しなければならないが、全て同じレジスターなので省略 **/
	MDM_SetIO(POS_DTMFW,0x00);
	MDM_SetIO(POS_DTMFD,OFF);
	MDM_SetIO(POS_OTS,OFF);
	MDM_SetIO(POS_DTDET,OFF);
	MDM_SetIO(POS_EDET,OFF);
#endif
	outp(MDM_REG_1B_PORT,0x00);	/* ＤＴＭＦ関係レジスターをクリア */

	ModemWaitStatus = PHS_STAT_CHECK_TN_BIT;
	
	while (1) {
		if (SYB_MachineParameter[40] & 0x08) {
			/* 田村の親子電話からのDTMFがとれないため(DTMFDのステータスがOnしない)  95.01.21 */
			status = 0;
			on_detect = 0;
			time_count = 0;
			while (1) {
				time_count++;
 				if (MDM_GetIO(POS_DTDET) && MDM_GetIO(POS_OTS)) {	/* デュアルトーン検出 */
					if (status == 0) {
						time_count = 0;
						status = 1;
						on_detect = 0;
					}
					if (time_count >= on_time) {
						on_detect = 1;
					}
				}
				else {		/* デュアルトーン未検出 */
					if (status == 1) {
						time_count = 0;
						status = 0;
					}
					if ((time_count >= off_time) && (on_detect == 1)) {
						break;
					}
				}
				wai_tsk(1);
			}
		}
		else {
			wai_evt(EVT_DTMF_DETECT);
		}

		dtmf_code = MDM_GetIO(POS_DTMFW);
		MDM_SetIO(POS_DTMFD,OFF);

		switch (dtmf_code) {
		case MDM_DTMF_0_CODE:
				dtmf_symbol = MDM_DTMF_0;
				break;
		case MDM_DTMF_1_CODE:
				dtmf_symbol = MDM_DTMF_1;
				break;
		case MDM_DTMF_2_CODE:
				dtmf_symbol = MDM_DTMF_2;
				break;
		case MDM_DTMF_3_CODE:
				dtmf_symbol = MDM_DTMF_3;
				break;
		case MDM_DTMF_4_CODE:
				dtmf_symbol = MDM_DTMF_4;
				break;
		case MDM_DTMF_5_CODE:
				dtmf_symbol = MDM_DTMF_5;
				break;
		case MDM_DTMF_6_CODE:
				dtmf_symbol = MDM_DTMF_6;
				break;
		case MDM_DTMF_7_CODE:
				dtmf_symbol = MDM_DTMF_7;
				break;
		case MDM_DTMF_8_CODE:
				dtmf_symbol = MDM_DTMF_8;
				break;
		case MDM_DTMF_9_CODE:
				dtmf_symbol = MDM_DTMF_9;
				break;
		case MDM_DTMF_AS_CODE:
				dtmf_symbol = MDM_DTMF_AS;
				break;
		case MDM_DTMF_SP_CODE:
				dtmf_symbol = MDM_DTMF_SP;
				break;
		case MDM_DTMF_A_CODE:
				dtmf_symbol = MDM_DTMF_A;
				break;
		case MDM_DTMF_B_CODE:
				dtmf_symbol = MDM_DTMF_B;
				break;
		case MDM_DTMF_C_CODE:
				dtmf_symbol = MDM_DTMF_C;
				break;
		case MDM_DTMF_D_CODE:
				dtmf_symbol = MDM_DTMF_D;
				break;
		default:
				break;
		}
		snd_msg(*mbx_no, &dtmf_symbol);
	}
#endif /* (0) */ /* DTMF 検出は NCU で行うので、このタスクはいりません。 H.Kubo 1997/12/10 */
}


/******************************************************************************
	module		:[DTMF送出オープン]
	function	:[
		1. TxLossを0dBmにセットします
		2. モデムコンフィギュをトーン送出に構成にします
	]
	return		:[なし]
	common		:[なし]
	date		:[1993/11/29]
	author		:[橘正樹]
******************************************************************************/
void  MDM_DTMF_Open(void)
{
	UBYTE level_value;
	UBYTE conf_mode;
	UBYTE level_mode;

	/*------------------------------------------*/
	/* DTMFの送信レベルはTxLossを0dBmに固定して */
	/* RAMのトーンレベルの値で変更します        */
	/*------------------------------------------*/
	/*MDM_TxLossSet(MDM_TX_LEVEL_0); 1996/11/28 Y.Murata */

	conf_mode = MDM_GetIO(POS_CONF);
	level_value = (UBYTE) ( (  MDM_TX_LEVEL_0 ) * 0x10);
	level_mode = MDM_GetIO(POS_TLVL);
	if (level_mode != level_value) {
		/* MDM_TxLevelSaveValue はここで書き換えてはいけない。
		** MDM_DTMF_Close で MDM_TxLevelSaveValue の値に設定を戻す。
		*/
		MDM_TxLossSet(level_value);
	}
	if (conf_mode != TX_DUAL_TONE) {
		MDM_ToneTxConfigSet(TX_DUAL_TONE);
	}
}

/******************************************************************************
	module		:[DTMFセット]
	function	:[
		1. 指定のDTMFの周波数をセットします
		2. 指定のDTMFのレベルをセットします
	]
	return		:[なし]
	common		:[
		DTMF_FrequencyTable
		DTMF_LevelTable
	]
	condition	:[
		DTMF送出オープンを事前に実行して,DTMF信号送出時にセットして下さい
	]
	date		:[1993/11/29]
	update		:[1996/03/12]
	author		:[橘正樹、木元修]
******************************************************************************/
void  MDM_DTMF_Set(UBYTE	dtmf_number)	/** 実際に送出する番号 **/
{
	UBYTE	dtmf_level;
	UBYTE country_code;

	country_code = (SYB_MachineParameter[COUNTRY_CODE] & 0x0F);

	/** DTMFレベルのoffsetを決定します **/
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/24 */
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
		dtmf_level = (UBYTE)(SYB_MachineParameter[MACHINE_PARA_2] & 0x0f);
	}
	else {
		dtmf_level = (UBYTE)(SYB_MachineParameter[M_PARA_SW_B4] & 0x0f);
	}
#else
	dtmf_level = (UBYTE)(SYB_MachineParameter[MACHINE_PARA_2] & 0x0f);
#endif		/* End of (defined (KEISATSU)) */
	if (dtmf_level >= MDM_DTMF_LVL_MAX) {		/* 0dBmから-1dBm刻み */
		dtmf_level = MDM_DTMF_LVL_MAX - 1;		/* -15.0dBm */
	}

	MDM_SetDualTone1Frequency(DTMF_FrequencyTable[dtmf_number].HighFreq);	/** DTMF高周波数セット **/
	MDM_SetDualTone2Frequency(DTMF_FrequencyTable[dtmf_number].LowFreq);	/** DTMF低周波数セット **/

	MDM_SetDualTone1PowerLevel(DTMF_LevelCountryTable[country_code][dtmf_level].HighLevel);	/** DTMF高群レベルセット **/
	MDM_SetDualTone2PowerLevel(DTMF_LevelCountryTable[country_code][dtmf_level].LowLevel);	/** DTMF低群レベルセット **/
}

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///******************************************************************************
//	module		:[DTMF送出開始]
//	function	:[
//		1. モデムのRTSをセットします
//	]
//	return		:[なし]
//	common		:[なし]
//	condition	:[
//		DTMFセットの後に、行って下さい
//	]
//	date		:[1993/11/29]
//	update		:[1996/03/12]
//	author		:[橘正樹、木元修]
//******************************************************************************/
//void  MDM_DTMF_Start(void)
//{
//	MDM_SetIO(POS_RTS,ON);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///******************************************************************************
//	module		:[DTMF送出停止]
//	function	:[
//		1. モデムのRTSをクリアします
//	]
//	return		:[なし]
//	common		:[なし]
//	date		:[1993/11/29]
//	update		:[1996/03/12]
//	author		:[橘正樹、木元修]
//******************************************************************************/
//void  MDM_DTMF_Stop(void)
//{
//	MDM_SetIO(POS_RTS,OFF);
//}
#endif

/******************************************************************************
	module		:[DTMF送出クローズ]
	function	:[
		1. 送信レベルを再セットします
		2. モデムコンフィギュのトーン送出を解除します
	]
	return		:[なし]
	common		:[
		MDM_TxLevelSaveValue
	]
	date		:[1993/11/29]
	update		:[1996/03/12]
	author		:[橘正樹、木元修
******************************************************************************/
void  MDM_DTMF_Close(void)
{
	MDM_TxLossSet(MDM_TxLevelSaveValue);	/** 送信レベルを再セットします **/
	MDM_InitialConfig();		/** トーン送出モデムを解除します **/
}

/*************************************************************************
	module		:[ＤＴＭＦパラメータの設定]
	function	:[
		1. 所定のパラメータを変更します
	]
	return		:[なし]
	common		:[
		R96_Reg     モデム・インターフェース・メモリ
	]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[MDM]
	date		:[1995/01/13]
	author		:[橘正樹]
*************************************************************************/
CONST UWORD LowFreqRate[7]   = {0x005a, 0x00aa, 0x010a, 0x024a, 0x034a, 0x057a, 0x08aa};
CONST UWORD HighFreqRate[7]  = {0x0064, 0x0154, 0x0224, 0x0444, 0x0564, 0x07a4, 0x09c4};
CONST UWORD PositiveTwist[8] = {0x0885, 0x0a60, 0x0e65, 0x12a3, 0x1420, 0x1d9b, 0x2567, 0x2f2b};
CONST UWORD NegativeTwist[8] = {0x1530, 0x1ad7, 0x2220, 0x2800, 0x3674, 0x441c, 0x54c6, 0x6c46};

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
//void MDM_DTMF_ParameterSet(void)
//{
//	WORD	on_value;
//	WORD	off_value;
//	UWORD	on_time;
//	UWORD	off_time;
//	UWORD	cycle_time;
//	UWORD	dropout;
//	UWORD	pos;
//
//	if (SYB_MachineParameter[40] & 0x04) {
//		/*-------------------------*/
//		/** ＤＴＭＦ低群周波数偏移 */
//		/*-------------------------*/
//		if (SYB_MachineParameter[42] & 0x0f) {
//			pos = SYB_MachineParameter[42] & 0x0f;
//			if (pos > 7) {
//				pos = 7;
//			}
//			DspRamAccessWriteMethod3(0x876,LowFreqRate[pos - 1],0x0000);
//		}
//		/*-------------------------*/
//		/** ＤＴＭＦ高群周波数偏移 */
//		/*-------------------------*/
//		if (SYB_MachineParameter[42] & 0xf0) {
//			pos = (UBYTE)(SYB_MachineParameter[42] >> 4);
//			if (pos > 7) {
//				pos = 7;
//			}
//			DspRamAccessWriteMethod3(0xA76,HighFreqRate[pos - 1],0x0000);
//		}
//		/*---------------------*/
//		/** ＤＴＭＦ正ツイスト */
//		/*---------------------*/
//		if (SYB_MachineParameter[43] & 0x0f) {
//			pos = SYB_MachineParameter[43] & 0x0f;
//			if (pos > 8) {
//				pos = 8;
//			}
//			DspRamAccessWriteMethod3(0x877,PositiveTwist[pos - 1],0x0000);
//		}
//		/*---------------------*/
//		/** ＤＴＭＦ負ツイスト */
//		/*---------------------*/
//		if (SYB_MachineParameter[43] & 0xf0) {
//			pos = (UBYTE)(SYB_MachineParameter[43] >> 4);
//			if (pos > 8) {
//				pos = 8;
//			}
//			DspRamAccessWriteMethod3(0x977,NegativeTwist[pos - 1],0x0000);
//		}
//		/*-------------------------*/
//		/** 最大ドロップアウト時間 */
//		/*-------------------------*/
//		if (SYB_MachineParameter[44]) {
//			dropout = SYB_MachineParameter[44];
//			dropout *= 0x29;	/* 0x29:5ms */
//			DspRamAccessWriteMethod3(0xB78,dropout,0x0000);
//		}
//
//		/*----------------------------------------------------------------*/
//		/* 機器パラメータＥ５とＥ６の両方が設定されていること（10ms単位） */
//		/*----------------------------------------------------------------*/
//		if (SYB_MachineParameter[45] && SYB_MachineParameter[46]) {
//			/*------------------------------------------*/
//			/* 最小オン時間の計算（基準値：0x70(40ms)） */
//			/*------------------------------------------*/
//			if (SYB_MachineParameter[45] < 3) {
//				on_value = 3;
//			}
//			else {
//				on_value = (WORD)SYB_MachineParameter[45];
//			}
//			on_time = 0x70 + (on_value - 4) * 96;
//			/*-------------------------------------------*/
//			/* 最小オフ時間の計算（基準値：0x134(40ms)） */
//			/*-------------------------------------------*/
//			if (SYB_MachineParameter[46] < 3) {
//				off_value = 3;
//			}
//			else {
//				off_value = (WORD)SYB_MachineParameter[46];
//			}
//			off_time = 0x134 + (off_value - 4) * 96;
//			/*-----------------------------------------------*/
//			/* 最小サイクル時間の計算（基準値：0x250(93ms)） */
//			/*-----------------------------------------------*/
//			cycle_time = (UWORD)(0x250 + ((on_value + off_value + 1) - 9) * 96);
//
//			/*-------------------------*/
//			/** ＤＴＭＦ検出感度の設定 */
//			/*-------------------------*/
//			/** 最小オンタイム */
//			/* 初期値=0x0070(40ms) */
//			/* 初期値より10msの増減 10*9.6=96(0x60) */
//			DspRamAccessWriteMethod3(0xA78,on_time,0x0000);
//
//			/** 最小オフタイム */
//			/* 初期値=0x0134(40ms) */
//			DspRamAccessWriteMethod3(0x878,off_time,0x0000);
//
//			/** 最小サイクルタイム */
//			/* 初期値=0x0250(93ms) */
//			DspRamAccessWriteMethod3(0x978,cycle_time,0x0000);
//		}
//	}
//}
#endif

/*************************************************************************
	module		:[DTMFクローズ処理]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[MDM]
	date		:[1996/11/29]
	author		:[村田]
*************************************************************************/
void  MDM_BreakDTMF_Tx(void)
{
	MDM_DTMF_Close();
}


/******************************************************************************
	module		:[Single DTMFセット]
	function	:[
		1. 指定のDTMFの周波数をセットします
		2. 指定のDTMFのレベルをセットします
	]
	return		:[なし]
	common		:[
		DTMF_FrequencyTable
		DTMF_LevelTable
	]
	condition	:[
		DTMF送出オープンを事前に実行して,DTMF信号送出時にセットして下さい
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[MDM]
	date		:[1996/12/11]
	author		:[村田]
******************************************************************************/
void  MDM_DTMF_SingleSet(UBYTE dtmf_type)
{
	UBYTE	dtmf_number;
	UBYTE	dtmf_level;
	UWORD			freq_value;

	UBYTE country_code;

	country_code = 0;	/* 0 = JPN By O.Kimoto 1997/09/10 */

	/*---------------------------------*/
	/*	DTMF周波数のoffsetを決定します */
	/*---------------------------------*/
	switch (dtmf_type) {
	case	MDM_DTMF_ROW1:
		dtmf_number = MDM_DTMF_ROW1_OFFSET;
		break;
	case	MDM_DTMF_ROW2:
		dtmf_number = MDM_DTMF_ROW2_OFFSET;
		break;
	case	MDM_DTMF_ROW3:
		dtmf_number = MDM_DTMF_ROW3_OFFSET;
		break;
	case	MDM_DTMF_ROW4:
		dtmf_number = MDM_DTMF_ROW4_OFFSET;
		break;
	case	MDM_DTMF_COL1:
		dtmf_number = MDM_DTMF_COL1_OFFSET;
		break;
	case	MDM_DTMF_COL2:
		dtmf_number = MDM_DTMF_COL2_OFFSET;
		break;
	case	MDM_DTMF_COL3:
		dtmf_number = MDM_DTMF_COL3_OFFSET;
		break;
	case	MDM_DTMF_COL4:
		dtmf_number = MDM_DTMF_COL4_OFFSET;
		break;
	default:
		dtmf_number = 0;
		break;
	}

	/*-------------------------*/
	/*	DTMF周波数を決定します */
	/*-------------------------*/
	if (/*(dtmf_type >= MDM_DTMF_ROW1) &&*/ (dtmf_type <= MDM_DTMF_ROW4)) {
		/*----------*/
		/* 低周波数 */
		/*----------*/
		freq_value = DTMF_FrequencyTable[dtmf_number].LowFreq;
	}
	else {
		/*----------*/
		/* 高周波数 */
		/*----------*/
		freq_value = DTMF_FrequencyTable[dtmf_number].HighFreq;
	}

	/*----------------------------------*/
	/** DTMFレベルのoffsetを決定します **/
	/*----------------------------------*/
	dtmf_level = (UBYTE)(SYB_MachineParameter[MACHINE_PARA_2] & 0x0f);
	if (dtmf_level >= MDM_DTMF_LVL_MAX) {		/* 0dBmから-1dBm刻み */
		dtmf_level = MDM_DTMF_LVL_MAX - 1;		/* -15.0dBm */
	}

	MDM_SetDualTone1Frequency(freq_value);	/** DTMF高周波数セット **/
	MDM_SetDualTone2Frequency(0x0000);	/** DTMF低周波数セット **/

	MDM_SetDualTone1PowerLevel(DTMF_LevelCountryTable[country_code][dtmf_level].HighLevel);	/** DTMF高群レベルセット **/

	MDM_SetDualTone2PowerLevel(0x0000);	/** DTMF低群レベルセット **/
}

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/25 */
void  MDM_KEIDEN_DTMF_SingleSet(UBYTE dtmf_type)
{
	UBYTE	dtmf_number;
	UBYTE	dtmf_level;
	UWORD			freq_value;

	UBYTE country_code;

	country_code = 0;	/* 0 = JPN By O.Kimoto 1997/09/10 */

	/*---------------------------------*/
	/*	DTMF周波数のoffsetを決定します */
	/*---------------------------------*/
	switch (dtmf_type) {
	case	MDM_DTMF_ROW1:
		dtmf_number = MDM_DTMF_ROW1_OFFSET;
		break;
	case	MDM_DTMF_ROW2:
		dtmf_number = MDM_DTMF_ROW2_OFFSET;
		break;
	case	MDM_DTMF_ROW3:
		dtmf_number = MDM_DTMF_ROW3_OFFSET;
		break;
	case	MDM_DTMF_ROW4:
		dtmf_number = MDM_DTMF_ROW4_OFFSET;
		break;
	case	MDM_DTMF_COL1:
		dtmf_number = MDM_DTMF_COL1_OFFSET;
		break;
	case	MDM_DTMF_COL2:
		dtmf_number = MDM_DTMF_COL2_OFFSET;
		break;
	case	MDM_DTMF_COL3:
		dtmf_number = MDM_DTMF_COL3_OFFSET;
		break;
	case	MDM_DTMF_COL4:
		dtmf_number = MDM_DTMF_COL4_OFFSET;
		break;
	default:
		dtmf_number = 0;
		break;
	}

	/*-------------------------*/
	/*	DTMF周波数を決定します */
	/*-------------------------*/
	if (/*(dtmf_type >= MDM_DTMF_ROW1) &&*/ (dtmf_type <= MDM_DTMF_ROW4)) {
		/*----------*/
		/* 低周波数 */
		/*----------*/
		freq_value = DTMF_FrequencyTable[dtmf_number].LowFreq;
	}
	else {
		/*----------*/
		/* 高周波数 */
		/*----------*/
		freq_value = DTMF_FrequencyTable[dtmf_number].HighFreq;
	}

	/*----------------------------------*/
	/** DTMFレベルのoffsetを決定します **/
	/*----------------------------------*/
	dtmf_level = (UBYTE)(SYB_MachineParameter[M_PARA_SW_B4] & 0x0f);
	if (dtmf_level >= MDM_DTMF_LVL_MAX) {		/* 0dBmから-1dBm刻み */
		dtmf_level = MDM_DTMF_LVL_MAX - 1;		/* -15.0dBm */
	}

	MDM_SetDualTone1Frequency(freq_value);	/** DTMF高周波数セット **/
	MDM_SetDualTone2Frequency(0x0000);	/** DTMF低周波数セット **/

	MDM_SetDualTone1PowerLevel(DTMF_LevelCountryTable[country_code][dtmf_level].HighLevel);	/** DTMF高群レベルセット **/

	MDM_SetDualTone2PowerLevel(0x0000);	/** DTMF低群レベルセット **/
}
#endif		/* End of (defined (KEISATSU)) */

/*************************************************************************
	module		:[ＤＴＭＦ送出関数（工場ファンクション用）]
	function	:[
		1.指定されたＤＴＭＦ送出テーブルのトーンを送出する
	]
	return		:[
		なし
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1997/12/05]
	author		:[久保博]
*************************************************************************/
void  MDM_DTMF(UBYTE	dial_no)	/* ＤＴＭＦ送出テーブルＮｏ．	*/
{
	/* 1996/11/29 Y.Murata
	 * DTMF設定で自動ダイアルを行う場合、１桁ずつDTMFを出し
	 * そのたびに、DTMF Open と Close をするとコンフィグに時間がかかり
	 * メイク、ブレーク時間が正しくでない
	 * Closeは全部のダイアルを発呼してから行うようにする
	 * Openは、DTMFモードでなかったらOpenするようにする
	*/

	MDM_DTMF_Open();
	MDM_DTMF_Set(dial_no);
	MDM_SetIO(POS_RTS,ON);
}
