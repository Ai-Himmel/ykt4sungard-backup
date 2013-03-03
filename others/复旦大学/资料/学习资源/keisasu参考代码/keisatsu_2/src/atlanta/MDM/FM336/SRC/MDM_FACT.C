/*---------------------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                              */
/*  ファイル名   : mdm_fact.c                                                            */
/*  作成者       :                                                                       */
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
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_bps.h"
#include "\src\atlanta\define\cmn_def.h"		/* 1997/06/17 H. Kubo */
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sys_opt.h"		/* 1997/06/13 by H. Kubo */
#include "\src\atlanta\sh7043\define\def_tib.h"		/* 1996/12/11 Y.M */
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\memsw\define\mem_sw_b.h"  /* added by H.Kubo 1997/12/25 for ATTENATION */
#include "\src\atlanta\define\mnt_sw.h"

#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_pro.h"		/* 1997/11/10 H.Kubo */
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\memsw\define\mems_pro.h" /* by H.Kubo 1997/07/07 */
#include "\src\atlanta\define\dma_pro.h"

void MDM_SoftResetModem(void);	/* Add By O.Kimoto 1998/05/20 */

/*******
** ext_v
*******/
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\SH7043\ext_v\extv_mbx.h"		/* 1996/12/11 Y.M */
#include "\src\atlanta\ext_v\bkupram.h" /* added by H.Kubo 1997/12/25 for SYS_MemorySwitch */


/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
UBYTE	MDM_WaitVoiceNAR(UWORD timer);
void	MDM_WaitST(void);
 #endif
#endif
void	MDM_VoiceTxTask(void);	/* ダミータスク追加用 2003/02/05 T.Takagi */


/* 現状、ANK系のオペレーションから呼ばれることは考慮されていませんので
** とりあえず、このようにしておきます。 By O.Kimoto 1998/09/08
** ANK系のオペレーションからも呼ばれるようにします by H.Hirao 1998/10/29
*/
/*************************************************************************
	module		:[サービスファンクション（Ｖ．３４）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[MDM]
	ProtoType	:[UBYTE far MDM_TxV34ServiceFunction(UBYTE baud_menu, UBYTE data_menu) {}]
	date		:[1996/11/27]
	author		:[木元修]
*************************************************************************/
UBYTE  MDM_TxV34ServiceFunction(UBYTE baud_menu, UBYTE data_menu)
{
	/* ソフトリセット */
	MDM_SoftResetModem();
	if (CHK_LineMonitor()) {
		MDM_SetVolumeAttenuationLevel(SYS_VOLUME_MAXIMUM);
	}

	/* 送出レベル設定 */
	/*temp = CHK_T23Attenation(); 1996/12/27 Y.M */
	/* 通信中でないので、FCM_PtnrChk_T23Attenation() はメモリスイッチの値を
	** 反映してない。そのため、メモリスイッチの値を直接参照して送出レベルを設定する。
	*/
	MDM_TransmitLevelSet(SYS_MemorySwitch[11] & ATTENATION);

	/* ループバックモード */
	MDM_SetIO(POS_ORG,ON);
	MDM_SetIO(POS_NEWC,ON);
	MDM_SetIO(POS_CONF,data_menu);
	MDM_SetIO(POS_NEWC,ON);
	MDM_SetIO(POS_NEWC,ON);

	/* ループバックモードで、31.2k/33.6kの信号が出ない件の対策
	** 2.MAXHDXRATE ($37A)に$CEを書き込む
	**（最大レートの上限を28.8Kbpsから33.6Kbpsに変更します。）
	** By O.Kimoto 1997/05/08
	*/
	DspRamAccessWriteMethod1(0x37A,0xCE,0x00);

	DspRamAccessWriteMethod1(0x2E3,baud_menu,0x00);
	MDM_SetIO(POS_L3ACT,ON);
	MDM_SetIO(POS_EXL3,ON);
	MDM_SetIO(POS_NEWC,ON);
	MDM_SetIO(POS_DTR,ON);
	return(1);
}


/*--------------------*/
/* トーナル信号テスト */
/*--------------------*/
#define TEST_TONE	1
#define TEST_FSK	2
#define TEST_G3		3
#define TEST_VOICE	4
#define TEST_V34	5
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
#define TEST_VOICE2	6
 #endif
#endif
void near MDM_TonalTest(void)
{
	MESSAGE_t			*msg;
	UBYTE	conf_data;
	UBYTE	boo_data;
	UWORD			offset;
	UWORD			base;
	UWORD			value;
	UWORD			dummy;
	UWORD			i;
	UBYTE			debug;

#if defined (KEISATSU)		/* 警察FAX DVT_ID15 Modify by SMuratec K.W.Q 2005/11/05 */
	if (SYS_FactoryModem.Item == SYS_OPT_MDM_TONAL_TEST) {
		ModemRelay_Off();
	}
	else if (SYS_FactoryModem.Item == SYS_OPT_MDM_KEIDEN_TONAL_TEST){
		ModemRelay_On();
	}
#endif		/* End of (defined (KEISATSU)) */

	MDM_FactoryFuncRelaySet();

	if (SYS_FactoryModem.Item == OPT_MDM_FACTORY_TEST_END) { /* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		MDM_FactoryStopCheck();
		SYS_FactoryFuncStatus = 0;
	}
	/* Stop */
	else if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_STOP) {  /* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		MDM_FactoryStopCheck();
		SYS_FactoryFuncStatus = 0;
	}
	/* ﾄｰﾝ */
	else if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_NONE) { /* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		if (SYS_FactoryFuncStatus == TEST_TONE) {
			MDM_SingleToneOff();
		}
		else {
			if (SYS_FactoryFuncStatus) {
				MDM_FactoryStopCheck();
			}
		}
		SYS_FactoryFuncStatus = TEST_TONE;
	}
	/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
	else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_462HZ) && (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_2100HZ)) {
		if (SYS_FactoryFuncStatus == TEST_TONE) {
			MDM_SingleToneOff();
			/* ソフトリセット */
			MDM_SoftResetModem();
			if (CHK_LineMonitor()) {
				MDM_SetVolumeAttenuationLevel(SYS_VOLUME_MAXIMUM);
			}
		}
		else {
			if (SYS_FactoryFuncStatus) {
				MDM_FactoryStopCheck();
			}
		}
		SYS_FactoryFuncStatus = TEST_TONE;
		value = SYS_FactoryModem.Kind -1; /* Modified by H.Kubo 1997/06/26 */
		/* 通信中でないので、FCM_PtnrChk_T23Attenation() はメモリスイッチの値を
		** 反映してない。そのため、メモリスイッチの値を直接参照して送出レベルを設定する。
		*/
		MDM_TransmitLevelSet(SYS_MemorySwitch[11] & ATTENATION);
		MDM_SingleToneOn((UBYTE) value);
	}
	/* FSK */
	/* Modified by H. Kubo for POPLAR_H 1997/06/17 */

	/* FSK_W1_B1 1999/12/27 Y.Murata */
	else if ((SYS_FactoryModem.Kind == OPT_MDM_TONAL_FSK_WHITE) ||
			 (SYS_FactoryModem.Kind == OPT_MDM_TONAL_FSK_BLACK) ||
			 (SYS_FactoryModem.Kind == OPT_MDM_TONAL_FSK_W1_B1)) {

		if (SYS_FactoryFuncStatus == TEST_FSK) {
			SYS_PixStopFlag = 1;
			rcv_msg(mbxno.FIP, &msg);
			if (tskno_MDM_FskTest != 0xFFFF) {
				del_tsk(&tskno_MDM_FskTest);
			}
			wai_tsk(1);
		}
		else {
			if (SYS_FactoryFuncStatus) {
				MDM_FactoryStopCheck();
			}
		}
		SYS_PixStopFlag = 0;

		SYS_FactoryFuncStatus = TEST_FSK;
		/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_FSK_WHITE) {
			MDM_FactoryFskMenu = FSK_WHITE;
			cre_tsk(&tskno_MDM_FskTest, TSK_MDM_FSKTXTASK, &MDM_FactoryFskMenu);
		}
		/* FSK_W1_B1 1999/12/27 Y.Murata */
		else if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_FSK_W1_B1) {
			MDM_FactoryFskMenu = FSK_W1_B1;
			cre_tsk(&tskno_MDM_FskTest, TSK_MDM_FSKTXTASK, &MDM_FactoryFskMenu);
		}
		else {
			MDM_FactoryFskMenu = FSK_BLACK;
			cre_tsk(&tskno_MDM_FskTest, TSK_MDM_FSKTXTASK, &MDM_FactoryFskMenu);
		}
	}
	/* G3 */
	/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
	else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V27_1200_2400) && (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V17_2400_14400)){
		if (SYS_FactoryFuncStatus == TEST_G3) {
			SYS_PixStopFlag = 1;
			rcv_msg(mbxno.FIP, &msg);
			if (tskno_MDM_PixTest != 0xFFFF) {
				del_tsk(&tskno_MDM_PixTest);
			}
			/* MDM_SetIO(POS_RTS,OFF); */
			wai_tsk(1);
		}
		else {
			if (SYS_FactoryFuncStatus) {
				MDM_FactoryStopCheck();
			}
		}
		SYS_PixStopFlag = 0;
		SYS_FactoryFuncStatus = TEST_G3;

		/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		switch (SYS_FactoryModem.Kind) {
		case OPT_MDM_TONAL_V27_1200_2400:
			FactoryPixData.baud_rate = BPS2400_V27;
			break;
		case OPT_MDM_TONAL_V27_1600_4800:
			FactoryPixData.baud_rate = BPS4800_V27;
			break;
		case OPT_MDM_TONAL_V29_2400_7200:
			FactoryPixData.baud_rate = BPS7200_V29;
			break;
		case OPT_MDM_TONAL_V29_2400_9600:
			FactoryPixData.baud_rate = BPS9600_V29;
			break;
		case OPT_MDM_TONAL_V17_2400_7200:
			FactoryPixData.baud_rate = BPS7200_V17;
			break;
		case OPT_MDM_TONAL_V17_2400_9600:
			FactoryPixData.baud_rate = BPS9600_V17;
			break;
		case OPT_MDM_TONAL_V17_2400_12000:
			FactoryPixData.baud_rate = BPS12000_V17;
			break;
		case OPT_MDM_TONAL_V17_2400_14400:
			FactoryPixData.baud_rate = BPS14400_V17;
			break;
		}
		/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		FactoryPixData.pix_retio = (UBYTE)SYS_FactoryModem.PIX_Pattern;
		cre_tsk(&tskno_MDM_PixTest, TSK_MDM_PIXTXTASK, &FactoryPixData);

	}
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && (PRO_MODEM == R288F)	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	/* Voice */
	else if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_VOICE) {
		if (SYS_FactoryFuncStatus == TEST_VOICE) {
			/* Nothing */
		}
		else {
			if (SYS_FactoryFuncStatus) {
				MDM_FactoryStopCheck();
			}
			SYS_PixStopFlag = 0;
			SYS_FactoryFuncStatus = TEST_VOICE;
			if (tskno_MDM_VoiceTest == 0xFFFF) {
				cre_tsk(&tskno_MDM_VoiceTest, TSK_MDM_VOICETXTASK, 0);
			}
		}

	}
	/* Melody */
	else if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_VOICE2) {
		if (SYS_FactoryFuncStatus == TEST_VOICE2) {
			/* Nothing */
		}
		else {
			if (SYS_FactoryFuncStatus) {
				MDM_FactoryStopCheck();
			}
		}
		SYS_FactoryFuncStatus = TEST_VOICE2;
		StartSendingMelodyToLine();
	}
#else
	/* Voice */
	/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
	else if (SYS_FactoryModem.Kind == OPT_MDM_TONAL_VOICE) {
		if (SYS_FactoryFuncStatus == TEST_VOICE) {
			/* Nothing */
		}
		else {
			if (SYS_FactoryFuncStatus) {
				MDM_FactoryStopCheck();
			}
		}
		SYS_FactoryFuncStatus = TEST_VOICE;
		StartSendingMelodyToLine();
	}
#endif
	else {
	/* V34 */
		if (SYS_FactoryFuncStatus == TEST_V34) {
			/* ソフトリセット */
			MDM_SetIO(POS_DTR,OFF);
			wai_tsk(100/10);

			MDM_SoftResetModem();

		}
		else {
			if (SYS_FactoryFuncStatus) {
				MDM_FactoryStopCheck();
			}
		}
		SYS_FactoryFuncStatus = TEST_V34;
		/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V34_2400_2400) &&
			 (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V34_2400_21600)) {
			base = 0xC1;
			offset = base - OPT_MDM_TONAL_V34_2400_2400;	/* 174 */
			boo_data = 0;
			conf_data = (UBYTE)(offset + SYS_FactoryModem.Kind); /* Modified by H.Kubo 1997/06/26 */
			MDM_TxV34ServiceFunction(boo_data, conf_data);
		}
		/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V34_2800_4800) &&
				 (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V34_2800_26400)) {
			base = 0xC2;
			offset = base - OPT_MDM_TONAL_V34_2800_4800;	/* 166 */
			boo_data = 2;
			conf_data = (UBYTE)(offset + SYS_FactoryModem.Kind); /* Modified by H.Kubo 1997/06/26 */
			MDM_TxV34ServiceFunction(boo_data, conf_data);
		}
		/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V34_3000_4800) &&
				 (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V34_3000_28800)) {
			base = 0xC2;
			offset = base - OPT_MDM_TONAL_V34_3000_4800;	/* 156 */
			boo_data = 3;
			conf_data = (UBYTE)(offset + SYS_FactoryModem.Kind); /* Modified by H.Kubo 1997/06/26 */
			MDM_TxV34ServiceFunction(boo_data, conf_data);
		}
		/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V34_3200_4800) &&
				 (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V34_3200_31200)) {
			base = 0xC2;
			offset = base - OPT_MDM_TONAL_V34_3200_4800;	/* 145 */
			boo_data = 4;
			conf_data = (UBYTE)(offset + SYS_FactoryModem.Kind); /* Modified by H.Kubo 1997/06/26 */
			MDM_TxV34ServiceFunction(boo_data, conf_data);
		}
		/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		else if ((SYS_FactoryModem.Kind >= OPT_MDM_TONAL_V34_3429_4800) &&
				 (SYS_FactoryModem.Kind <= OPT_MDM_TONAL_V34_3429_33600)) {
			base = 0xC2;
			offset = base - OPT_MDM_TONAL_V34_3429_4800;	/* 133 */
			boo_data = 5;
			conf_data = (UBYTE)(offset + SYS_FactoryModem.Kind); /* Modified by H.Kubo 1997/06/26 */
			MDM_TxV34ServiceFunction(boo_data, conf_data);
		}
	}
}

/*--------------*/
/* リレーテスト */
/*--------------*/
/*
** COMP
** 回線テスト・テスト項目種別  SYS_FactoryOptModemData.Kind
** (ﾘﾚｰﾃｽﾄ)
** MDMコンパイルのため、ここに定義しておく
** (atlantaではopr_def.hに定義されている)
** 1999/01/29 by K.Okada
*/

#define MDM_RELAY_CML_ON			0				/* CML */
#define MDM_RELAY_CML_OFF			1
#define MDM_RELAY_H_ON				2				/* H */
#define MDM_RELAY_H_OFF				3
#define MDM_RELAY_L_ON				4				/* L */
#define MDM_RELAY_L_OFF				5
#define MDM_RELAY_S_ON				6				/* S */
#define MDM_RELAY_S_OFF				7
#define MDM_RELAY_MODEM_ON			8				/* S */
#define MDM_RELAY_MODEM_OFF			9
#define MDM_RELAY_CONT24_ON			10				/* CONT24 */
#define MDM_RELAY_CONT24_OFF		11
#define MDM_RELAY_TONE_ON			12				/* CONT24 */
#define MDM_RELAY_TONE_OFF			13
#define MDM_RELAY_BZ_ON				14				/* CONT24 */
#define MDM_RELAY_BZ_OFF			15
#define MDM_RELAY_RI_ON				16				/* RI(GK) */
#define MDM_RELAY_RI_OFF			17
#define MDM_RELAY_PHONE2_ON			18				/* RI(GK) */
#define MDM_RELAY_PHONE2_OFF		19
#define MDM_RELAY_DP_ON				20				/* DP added by H.Hirao 1999/02/02 */ /* 2002/07/23 T.Takagi */
#define MDM_RELAY_DP_OFF			21

void MDM_RealyTest(void)
{
	/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
	if (SYS_FactoryModem.Item == OPT_MDM_FACTORY_TEST_END) {
		MDM_FactoryFskMenu = 0;
		return;
	}

#if defined (KEISATSU)		/* 警察FAX DVT_ID15 Modify by SMuratec K.W.Q 2005/11/05 */
	if (SYS_FactoryModem.Item == SYS_OPT_MDM_RELAY_TEST) {
		ModemRelay_Off();
		
		RelayPortStatus &= ~IO_BIT_H;
		OutputWORD(GA_PGADR, RelayPortStatus);
	}
	else if (SYS_FactoryModem.Item == SYS_OPT_MDM_KEIDEN_RELAY_TEST){
		ModemRelay_On();
		
		RelayPortStatus |= IO_BIT_H;
		OutputWORD(GA_PGADR, RelayPortStatus);
	}
#endif		/* End of (defined (KEISATSU)) */

	/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
	switch (SYS_FactoryModem.Kind) {
	case MDM_RELAY_CML_ON:
		CML_RelayOn();
		break;
	case MDM_RELAY_CML_OFF:
		CML_RelayOff();
		break;
#if defined (KEISATSU)		/* 警察FAX DVT_ID15 Modify by SMuratec K.W.Q 2005/11/05 */
	case MDM_RELAY_H_ON:
		HDST_Disable();
		break;
	case MDM_RELAY_H_OFF:
		HDST_Enable();
		break;
	case MDM_RELAY_L_ON:
		Keisatsu_L_RelayOn();
		break;
	case MDM_RELAY_L_OFF:
		Keisatsu_L_RelayOff();
		break;
#else
	case MDM_RELAY_H_ON:
		H_RelayOn();
		break;
	case MDM_RELAY_H_OFF:
		H_RelayOff();
		break;
	case MDM_RELAY_L_ON:
		L_RelayOn();
		break;
	case MDM_RELAY_L_OFF:
		L_RelayOff();
		break;
#endif		/* End of (defined (KEISATSU)) */
	case MDM_RELAY_S_ON:
		S_RelayOn();
		break;
	case MDM_RELAY_S_OFF:
		S_RelayOff();
		break;
	case MDM_RELAY_MODEM_ON:
		ModemRelay_On();
		break;
	case MDM_RELAY_MODEM_OFF:
		ModemRelay_Off();
		break;
	case MDM_RELAY_CONT24_ON:
		CONT_24V_On();
		break;
	case MDM_RELAY_CONT24_OFF:
		CONT_24V_Off();
		break;
	case MDM_RELAY_TONE_ON:
		AnalogSwitchRXA_Set();
		break;
	case MDM_RELAY_TONE_OFF:
		AnalogSwitchTONE_Set();
		break;
	case MDM_RELAY_BZ_ON:
		SpeakerOutRXA();
		break;
	case MDM_RELAY_BZ_OFF:
		SpeakerOutBuzzer();
		break;
	case MDM_RELAY_RI_ON:
		RI_On();
		break;
	case MDM_RELAY_RI_OFF:
		RI_Off();
		break;
	case MDM_RELAY_PHONE2_ON:
		PHONE2_RelayOn();
		break;
	case MDM_RELAY_PHONE2_OFF:
		PHONE2_RelayOff();
		break;
 #if defined (TWN) /* added by H.Hirao 1999/02/02 *//*  By O.Kimoto 2002/07/22 */
 	case MDM_RELAY_DP_ON:
		DP_RelayOn();
		break;
	case MDM_RELAY_DP_OFF:
		DP_RelayOff();
		break;
 #endif
	default:
		break;
	}
}

/*--------------------*/
/* ＤＴＭＦ送出テスト */
/*--------------------*/
void near MDM_DTMF_Test(void)
{
	UWORD			offset;
	UWORD			base;
	UBYTE	value;

	/* ソフトリセット */
	MDM_SoftResetModem();

#if defined (KEISATSU)		/* 警察FAX DVT_ID15 Modify by SMuratec K.W.Q 2005/11/05 */
	if (SYS_FactoryModem.Item == SYS_OPT_MDM_DTMF_TEST) {
		ModemRelay_Off();
	}
	else if (SYS_FactoryModem.Item == SYS_OPT_MDM_KEIDEN_DTMF_TEST){
		ModemRelay_On();
	}
#endif		/* End of (defined (KEISATSU)) */

	MDM_FactoryFskMenu = 0;
	MDM_FactoryFuncRelaySet();

	/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
	if (SYS_FactoryModem.Item == OPT_MDM_FACTORY_TEST_END) {
		MDM_SetIO(POS_RTS,OFF);	/* 送信要求解除 */
		MDM_DTMF_Close();		/* 送信レベルを再セット, FSK受信モードにコンフィギュ */
		MDM_FactoryFskMenu = 0;
	}
	/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
	else if (SYS_FactoryModem.Kind == OPT_MDM_DTMF_STOP) {
		MDM_SetIO(POS_RTS,OFF);
		MDM_DTMF_Close();
		MDM_FactoryFskMenu = 0;
	}
	else {
		if (MDM_FactoryFskMenu == 0xFF) {
			MDM_SetIO(POS_RTS,OFF);
			MDM_DTMF_Close();
			wai_tsk(100/10);
		}
		MDM_FactoryFskMenu = 0xFF;
		/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		if (SYS_FactoryModem.Kind <= OPT_MDM_DTMF_SHARP) {
			MDM_DTMF_Open();	/* 送信レベル0dmセット, Dual Toneモードにコンフィギュ */
			/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
			MDM_DTMF_Set((UBYTE)(SYS_FactoryModem.Kind));	/* 高低周波数・送出レベルセット */
			MDM_SetIO(POS_RTS,ON);	/* 送信要求ON */
		}
		else {
			/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
			if ((SYS_FactoryModem.Kind >= OPT_MDM_DTMF_ROW1) && (SYS_FactoryModem.Kind <= OPT_MDM_DTMF_COL4)) {
				base = 0;
				offset = OPT_MDM_DTMF_ROW1 - base;	/* 12 */
				/* Modified by H. Kubo for POPLAR_H 1997/06/17 */
				value = (UBYTE)(SYS_FactoryModem.Kind - offset);

				MDM_DTMF_Open();
#if defined (KEISATSU)		/* 警察FAX DVT_ID15 Modify by SMuratec K.W.Q 2005/11/05 */
				if (SYS_FactoryModem.Item == SYS_OPT_MDM_DTMF_TEST) {
					MDM_DTMF_SingleSet(value);
				}
				else if (SYS_FactoryModem.Item == SYS_OPT_MDM_KEIDEN_DTMF_TEST){
					MDM_KEIDEN_DTMF_SingleSet(value);
				}
#else
				MDM_DTMF_SingleSet(value);
#endif		/* End of (defined (KEISATSU)) */
				MDM_SetIO(POS_RTS,ON);
			}
		}
	}
}

/*----------------------*/
/* 回線テストリレー制御 */
/*----------------------*/
void MDM_FactoryFuncRelaySet(void)
{
	/* ＤＰリレーＯＮ 1996/11/26 */
	DP_RelayOn();
	wai_tsk(1);

	S_RelayOn();	/* Relay Spike Niose For Switching(FRA DEU) 1996/11/26 */

	AnalogSwitchRXA_Set();

	CML_RelayOn();
	wai_tsk(10);	/* 100ms */
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/12 */
	if ( !ModemRelaySetting() ){	/**	標準ラインに接続された場合	*/
		H_RelayOn();
	}
	else { /**	拡張ラインに接続された場合	*/
		L_RelayOn();
	}
#else /* defined (KEISATSU) */
	H_RelayOn();
	L_RelayOn();
#endif /* defined (KEISATSU) */
	S_RelayOff();				/* Add by TH92115 1994/08/29 */

	/* スピーカーの設定 */
	if (CHK_LineMonitor()) {
		MonitorSpeakerOn();
	}
}


void  MDM_FactoryFuncRelayReSet(void)
{
	CML_RelayOff();
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/12 */
	if ( !ModemRelaySetting() ){	/**	標準ラインに接続された場合	*/
		H_RelayOff();
	}
	else { /**	拡張ラインに接続された場合	*/
		L_RelayOff();
	}
#else /* defined (KEISATSU) */
	H_RelayOff();
	L_RelayOff();
#endif /* defined (KEISATSU) */
	CONT_24V_Off();
	S_RelayOff();
	DP_RelayOff();

	MonitorSpeakerOff();	/* Add By O.Kimoto 1998/05/20 */

}



void MDM_FactoryStopCheck(void)
{
	MESSAGE_t			*msg;
	switch (SYS_FactoryFuncStatus) {
	case TEST_TONE:
		MDM_SingleToneOff();
		break;
	case TEST_FSK:
		SYS_PixStopFlag = 1;
		rcv_msg(mbxno.FIP, &msg);
		if (tskno_MDM_FskTest != 0xFFFF) {
			del_tsk(&tskno_MDM_FskTest);
		}
		MDM_SetIO(POS_RTS,OFF);
		break;
	case TEST_G3:
		SYS_PixStopFlag = 1;
		rcv_msg(mbxno.FIP, &msg);
		if (tskno_MDM_PixTest != 0xFFFF) {
			del_tsk(&tskno_MDM_PixTest);
		}
		MDM_SetIO(POS_RTS,OFF);
		break;
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && (PRO_MODEM == R288F)	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	case TEST_VOICE:
		SelectMELorTX();
		SYS_PixStopFlag = 1;
		rcv_msg(mbxno.FIP, &msg);
		if (tskno_MDM_VoiceTest != 0xFFFF) {
			del_tsk(&tskno_MDM_VoiceTest);
		}
		break;
	case TEST_VOICE2:
		StopSendingMelodyToLine();
		break;
#else
	case TEST_VOICE:
		StopSendingMelodyToLine();
		break;
#endif
	case TEST_V34:
		MDM_SetIO(POS_DTR,OFF);
		MDM_SetIO(POS_L3ACT,OFF);
		MDM_SetIO(POS_EXL3,OFF);
		MDM_SetIO(POS_NEWC,ON);
		break;
	default:
		break;
	}
	wai_tsk(10);	/* 100ms */
}



/*************************************************************************
	module		:[サービスファンクション]
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
	date		:[1996/12/10]
	author		:[]
*************************************************************************/
void  MDM_FactoryFunctionTask(void)
{
	UWORD		status;
	MESSAGE_t	*MDM_RxMsg;
	MESSAGE_t	MDM_TxMsg;

	status = 0;
	SYS_FactoryFuncStatus = 0;
	tskno_MDM_FskTest = 0xFFFF;
	tskno_MDM_PixTest = 0xFFFF;
	SYS_PixStopFlag = 0;
	SYS_V34ProcedureExecutingFlag = NO;  /* 0; */
	MDM_FactoryFskMenu = 0;
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	tskno_MDM_VoiceTest = 0xFFFF;
 #endif
#endif

	do {
		rcv_msg(mbxno.CPY_Task, &MDM_RxMsg);	/**	メッセージ受信	*/

	} while (MDM_RxMsg->Message != FIP_TEST_CMD);

/* POPLAR_H では直接メモリスイッチを参照できるので、以下は不必要。*/

	while (1) {
		do {

			rcv_msg(mbxno.CPY_Task, &MDM_RxMsg);	/**	メッセージ受信	*/

		} while (MDM_RxMsg->Message != FIP_TEST_CMD);

		switch (SYS_FactoryModem.Item) { /* Modified by H. Kubo for POPLAR_H 1997/06/17 */
		case SYS_OPT_MDM_RELAY_TEST:
			if ((status == 0) || (status == 1)) {
				status = 1;
			}
			else {
				/* ソフトリセット */
				MDM_SoftResetModem();
				status = 1;
			}
			MDM_RealyTest();
			break;
		case SYS_OPT_MDM_TONAL_TEST:
#if defined(HINOKI2) && defined(JPNNTT)	/* トーナルテストリセット対策 by J.Kishida 2002/12/03 */
			if (status == 2) {
				status = 2;
			}
			else if (status == 0) {
				/*
				// トーナルテストに入る時(status == 0のとき)は
				// ハードリセットをかけます
				*/
				MDM_ModemHardwareReset();
				wai_tsk(400/10);	/* Add By O.Kimoto 2002/12/04 */
				status = 2;
			}
			else {
				/* ソフトリセット */
				MDM_SoftResetModem();
				status = 2;
			}
#else
			if ((status == 0) || (status == 2)) {
				status = 2;
			}
			else {
				/* ソフトリセット */
				MDM_SoftResetModem();
				status = 2;
			}
#endif
			MDM_TonalTest();
			break;
		case SYS_OPT_MDM_DTMF_TEST:
			if ((status == 0) || (status == 3)) {
				status = 3;
			}
			else {
				/* ソフトリセット */
				MDM_SoftResetModem();
				status = 3;
			}
			MDM_DTMF_Test();
			break;
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/25 */
/* 警察FAX Added start DVT_ID15 by SMuratec K.W.Q 2005/11/05 */
		case SYS_OPT_MDM_KEIDEN_RELAY_TEST:
			if ((status == 0) || (status == 4)) {
				status = 4;
			}
			else {
				/* ソフトリセット */
				MDM_SoftResetModem();
				status = 1;
			}
			MDM_RealyTest();
			break;
		case SYS_OPT_MDM_KEIDEN_TONAL_TEST:
			if ((status == 0) || (status == 5)) {
				status = 5;
			}
			else {
				/* ソフトリセット */
				MDM_SoftResetModem();
				status = 5;
			}
			MDM_TonalTest();
			break;
		case SYS_OPT_MDM_KEIDEN_DTMF_TEST:
			if ((status == 0) || (status == 6)) {
				status = 6;
			}
			else {
				/* ソフトリセット */
				MDM_SoftResetModem();
				status = 6;
			}
			MDM_DTMF_Test();
			break;
/* 警察FAX Added end DVT_ID15 by SMuratec K.W.Q 2005/11/05 */
#endif		/* End of (defined (KEISATSU)) */
		case OPT_MDM_FACTORY_TEST_END:
			break;
		case OPT_MDM_FACTORY_TEST_START:
			break;
		}
		MDM_TxMsg.Message = MSG_FIP_RS232C_TEST_END;
		snd_msg(mbxno.OPR_Task,&MDM_TxMsg);
	}
}


void far MDM_FactoryFunctionExit(void)
{
	if (tskno_MDM_FskTest != 0xFFFF) {
		del_tsk(&tskno_MDM_FskTest);
	}
	if (tskno_MDM_PixTest != 0xFFFF) {
		del_tsk(&tskno_MDM_PixTest);
	}

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	if (tskno_MDM_VoiceTest != 0xFFFF) {
		del_tsk(&tskno_MDM_VoiceTest);
	}
	SelectMELorTX();

	MDM_AnswerLSI_Initialize();
 #endif
#endif

	MDM_SoftResetModem();

	MDM_FactoryFuncRelayReSet();
	exi_tsk();
}

/*************************************************************************
	module		:[サービスファンクション用ＦＳＫ送出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/05/06]
	author		:[曽根岡拓]
*************************************************************************/
void  MDM_FskTxTask(UBYTE *fsk_type)
{
	MESSAGE_t	Modem;

	UBYTE	loop_flg;

	loop_flg = 1;	/**	ループ制御フラグを１に設定	*/
	MDM_ModemInitialize();	/**	モデムワークエリアクリア	*/
	InitializeModemWork();

#if (PRO_ENERGY_SAVE == ENABLE)	/* トーナルテストFSKモードで信号送出時間が短い by J.Kishida 2002/10/11 */
	if (SYS_HaltClock == FALSE) {	/* 現在クロックが停止していて */
		HaltClockOn();
		wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
		SubResetOff();
		SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
	}
#endif

	/*
	** ROCKWELL製 28.8K
	*/
	/* モデム救済タスク起動 By O.Kimoto 1998/02/03 */
	if (tskno_MDM_ModemRecoverTask == 0xffff) {
		cre_tsk(&tskno_MDM_ModemRecoverTask, TSK_MDM_MODEMRECOVERTASK, 0);
	}

	/* Added by H.Kubo 1997/12/25 */
	/* 通信中でないので、FCM_PtnrChk_T23Attenation() はメモリスイッチの値を
	** 反映してない。そのため、メモリスイッチの値を直接参照して送出レベルを設定する。
	*/
	MDM_TransmitLevelSet(SYS_MemorySwitch[11] & ATTENATION);


	/* スピーカーの設定 1997/03/18 Y.Murata */
	if (CHK_LineMonitor()) {
		MDM_SetVolumeAttenuationLevel(SYS_VOLUME_MAXIMUM);
	}

	ModemTypeSet(BPS300_V21);	/**	モデムタイプをＦＳＫに設定	*/
	ModemBlock.Chain = CHAIN_OFF;

	ServiceFuncTx = TRUE;	/**	サービスファンクション用送出をＯＮ	*/

	if (*fsk_type == FSK_WHITE) {	/**	ＦＳＫ　ＷＨＩＴＥ送出の時	*/
		SetClear((UBYTE *)&MDM_ModemBuffer[0][0], MODEM_BUFFER_LENGTH, 0x00);	/**	モデムバッファ、０ｘ００セット	*//** 256 Bytes **/
	}
	else if (*fsk_type == FSK_W1_B1) {	/* FSK_W1_B1 1999/12/27 Y.Murata */
		SetClear((UBYTE *)&MDM_ModemBuffer[0][0], MODEM_BUFFER_LENGTH, 0xaa);	/**	モデムバッファ、０ｘAAセット	*//** 256 Bytes **/
	}
	else {	/**	ＦＳＫ　ＢＬＡＣＫ送出の時	*/
		SetClear((UBYTE *)&MDM_ModemBuffer[0][0], MODEM_BUFFER_LENGTH, 0xff);	/**	モデムバッファ、０ｘＦＦセット	*//** 256 Bytes **/
	}

	TxFskOpen();	/**	ＦＳＫ送信オープン	*/

	while(loop_flg) {	/**	ループ制御フラグが１の時	*/
		ServiceFuncTx = TRUE;	/**	サービスファンクション用送出をＯＮ	*/
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
		TxFskWrite(&MDM_ModemBuffer[0][0], MDM_ModemDmaSize);	/**	ＦＳＫ送信モデムライト	*//** 256 Bytes **/
#else
		TxFskWrite(&MDM_ModemBuffer[0][0], MODEM_DMA_SIZE);	/**	ＦＳＫ送信モデムライト	*//** 256 Bytes **/
#endif
		while (1) {	/**	無限ループ	*/
			if (ServiceFuncTx == FALSE) {	/**	サービスファンクション用送出ＯＦＦの時	*/
				break;
			}
			else if (SYS_PixStopFlag == 1) {	/**	送出ストップの時	*/
				ModemControl.Status |= STAT_EMPTYPT;	/**	モデムステータス、最終フレーム登録完了	*/
				loop_flg = NO;	/**	ループ制御フラグを０に設定	*/
				break;
			}
			wai_tsk(50/10);	/**	タスクウェイト５０ｍｓ	*/
		}
	}
	/*	モデム割り込み監視タスク終了	*/
	if (tskno_ModemInterrupt != 0xffff) {
		del_tsk(&tskno_ModemInterrupt);	/**	モデム割り込み監視タスク終了	*/
	}

	/*	送信フレーム監視タスク終了	*/
	if (tskno_TxFskControl != 0xffff) {
		del_tsk(&tskno_TxFskControl);	/**	送信フレーム監視タスク終了	*/
	}

	/*	モデムバッファ－＞モデムＤＭＡ終了	*/
	/* Modified by H. Kubo for POPLAR_H, 1997/06/17 */
	DMA_RequestMask(DMA_CH_TX);	/**	モデムバッファ－＞モデムＤＭＡ終了	*/

	/*	モデムバッファセマフォリセット	*/
	ResetModemBufferSem();	/**	モデムバッファセマフォリセット	*/

	/*	モデムクローズ処理	*/

	/* add 2line 1996/12/12 Y.M */
	MDM_SetIO(POS_RTS,OFF);
	wai_tsk(3);		/* at least 15ms */

	MDM_InitialConfig();	/**	モデムクローズ処理	*/

	/*
	** ROCKWELL製 28.8K
	*/
	/* モデム救済タスク起動 By O.Kimoto 1998/02/03 */
	if (tskno_MDM_ModemRecoverTask != 0xffff) {
		del_tsk(&tskno_MDM_ModemRecoverTask);
	}

	ServiceFuncTx = FALSE;
	Modem.Message = MSG_MODEM_STOP;
	snd_msg(mbxno.FIP, &Modem);	/**	オペレーションタスクにメッセージ送信	*/
	wai_tsk(0xffff);	/**	無限タスクウェイト	*/
}



/*************************************************************************
	module		:[サービスファンクション用画データ送出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/05/06]
	author		:[曽根岡拓]
*************************************************************************/
void  MDM_PixTxTask(struct ServiceFuncPixData_t *pixdata)
{
	MESSAGE_t	Modem;

	UBYTE	count;
	UWORD	i;


	InitializeModemWork();
	MDM_ModemInitialize();

	/*
	** ROCKWELL製 28.8K
	*/
	/* モデム救済タスク起動 By O.Kimoto 1998/02/03 */
	if (tskno_MDM_ModemRecoverTask == 0xffff) {
		cre_tsk(&tskno_MDM_ModemRecoverTask, TSK_MDM_MODEMRECOVERTASK, 0);
	}

	/* Added by H.Kubo 1997/12/25 */
	/* 通信中でないので、FCM_PtnrChk_T23Attenation() はメモリスイッチの値を
	** 反映してない。そのため、メモリスイッチの値を直接参照して送出レベルを設定する。
	*/
	MDM_TransmitLevelSet(SYS_MemorySwitch[11] & ATTENATION);

	/* スピーカーの設定 1997/03/18 Y.Murata */
	if (CHK_LineMonitor()) {
		MDM_SetVolumeAttenuationLevel(SYS_VOLUME_MAXIMUM);
	}

	ModemTypeSet(pixdata->baud_rate);	/**	モデムタイプ、速度設定	*/
	ModemBlock.Mode = MODE_TX_TCF;	/**	交信モードを送信Ｇ３に設定	*/
	/* Modified by H. Kubo for POPLAR_H, 1997/06/17 */
	DMA_RequestMask(DMA_CH_TX);	/*	モデムＶ５３ＤＭＡマスク設定	*/

	ModemConfig(WRITE_MODE);	/**	モデムコンフィグレーション実行	*/

	count = 0;

	for (i = 0; i < 255; i++) {
		MDM_ModemBuffer[0][i] = PixTestPatternTable[pixdata->pix_retio][count];
		count++;
		if (count >= 5) {
			count = 0;
		}
	}

	ServiceFuncTx = TRUE;
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
	TxG3_Write(MDM_ModemBuffer[0], MDM_ModemDmaSize);	/**	Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／データ数登録）	*//** 256 Bytes **/
#else
	TxG3_Write(MDM_ModemBuffer[0], MODEM_DMA_SIZE);	/**	Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／データ数登録）	*//** 256 Bytes **/
#endif
	while (1) {	/**	無限ループ	*/
		if (SYS_PixStopFlag == 1) {	/**	画データ送出ストップの時	*/
			ModemControl.Status |= STAT_EMPTYPT;	/**	モデムステータス、最終フレーム登録完了	*/
			break;
		}
		wai_tsk(50/10);	/**	タスクウェイト５０ｍｓ	*/
	}
	/* Modified by H. Kubo for POPLAR_H, 1997/06/17 */
	DMA_RequestMask(DMA_CH_TX);	/**	Ｖ５３ＤＭＡマスク	*/
	/* Modified by H. Kubo 1997/06/23 */
	DMA_AutoInitializeDisable(DMA_CH_TX);	/** Ｖ５３ＤＭＡオートイニシャライズＯＦＦ */
	ServiceFuncTx = FALSE;

	/* add 2line 1996/12/12 Y.M */
	MDM_SetIO(POS_RTS,OFF);
	wai_tsk(3);		/* at least 15ms */

	MDM_InitialConfig();	/**	モデムクローズ	*/

	/*
	** ROCKWELL製 28.8K
	*/
	/* モデム救済タスク起動 By O.Kimoto 1998/02/03 */
	if (tskno_MDM_ModemRecoverTask != 0xffff) {
		del_tsk(&tskno_MDM_ModemRecoverTask);
	}

	Modem.Message = MSG_MODEM_STOP;
	snd_msg(mbxno.FIP, &Modem);	/**	オペレーションタスクへメッセージ送信	*/
	wai_tsk(0xffff);	/**	無限タスクウェイト	*/
}



/*************************************************************************
	module		:[サービスファンクション用モデムソフトリセット処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/05/06]
	author		:[曽根岡拓]
*************************************************************************/
void MDM_SoftResetModem(void)
{
	/* ソフトリセット */
	MDM_SetIO(POS_SFRES,ON);
	MDM_SetIO(POS_NEWC,ON);
	wai_tsk(400/10);
}



/* #if defined(POPLAR_F) *//* 条件コンパイル追加 2001/12/21 T.Takagi */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
/*************************************************************************
	module		:[音声送出タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1999/10/14]
	author		:[村田]
*************************************************************************/
void	MDM_VoiceTxTask(void)
{
	MESSAGE_t	Modem;
	UWORD	phase;
	UWORD	timer;
	UWORD	ret;

	phase = 1;
	ret = 1;

	/* リセット */
	MDM_AnswerLSI_Initialize();
	wai_tsk(100);


	SelectVOL();

	while (1) {
		CMN_SetFraseAnswerLSI((UWORD)phase);
		wai_tsk(2);
		if (MDM_WaitVoiceNAR((UWORD)10) == 0) {
			break;
		}
		CMN_AnswerLSIOn();
		MDM_WaitST();
		CMN_AnswerLSIOff();
		if (MDM_WaitVoiceNAR((UWORD)10) == 0) {		/* 鳴り始め*/
			break;
		}
		wai_tsk(2);
		CMN_SetFraseAnswerLSI((UWORD)6);			/* 無音セット */
		wai_tsk(2);
		CMN_AnswerLSIOn();
		MDM_WaitST();
		CMN_AnswerLSIOff();
		if (MDM_WaitVoiceNAR((UWORD)1500) == 0) {	/* 無音鳴り始め */
			break;
		}
		wai_tsk(100);
		phase++;
		if (phase >= 6) {
			phase = 1;
		}
	}



	SelectMELorTX();

	MDM_AnswerLSI_Initialize();

	Modem.Message = MSG_MODEM_STOP;
	snd_msg(mbxno.FIP, &Modem);	/**	オペレーションタスクへメッセージ送信	*/
	wai_tsk(0xffff);	/**	無限タスクウェイト	*/
}

UBYTE	MDM_WaitVoiceNAR(UWORD timer)
{
	UWORD	count;
	
	count = 0;
	while (1) {
		if (NAR()) {
			return (1);
		}
		if (SYS_PixStopFlag == 1) {
			return (0);
		}
		wai_tsk(1);
		count++;
		if (count > timer) {
			return (1);
		}
	}
}
 #endif
#else	/* 音声応答以外はダミータスクにします。2003/02/05 T.Takagi */
void	MDM_VoiceTxTask(void){}
#endif

