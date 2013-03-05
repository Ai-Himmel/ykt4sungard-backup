/***************************************************************************
**	JUN\USR1:\src\rice\v53\src\chk_anlg.c	を移植 1997/06/09  By T.Yamaguchi
**	アナログ・ファンクション・チェッカー
***************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"

#include	"\src\atlanta\define\chk_def.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\buzzer.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\message.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\define\sh_sys.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include	"\src\atlanta\ext_v\sys_port.h"
#include	"\src\atlanta\ext_v\cdc_tbl.h"
#include	"\src\atlanta\define\dpr_pro.h"	/* DPRAMチェック */
#include	"\src\atlanta\define\idp_pro.h"	/* 白黒チェック */
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\scn_pro.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\scn_io.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\scn_tbl.h"

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* #if is added by H.Kubo 1997/08/11 */
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B)
#if defined(JPN)
#undef	PRO_CLASS1		/* 強制的にCLASS1をENABLEにする */
#define	PRO_CLASS1	ENABLE
#endif
#endif

#if (PRO_CLASS1 == ENABLE)
#include	"\src\atlanta\ext_v\cl1_data.h"	/* RS232Cチェック */
#include	"\src\atlanta\define\cl1_pro.h"	/* RS232Cチェック */
#endif

#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\idp_def.h"
#include "\src\atlanta\ext_v\idp_data.h"
#include "\src\atlanta\define\sysscan.h"

/* プロトタイプ */
void			AnalogFunctionCheckerMain( void );						/* なし */
void			CheckClock( UBYTE Machine );		/* 機種 */
UBYTE			CheckMemory(
						 UBYTE	ReadWrite,		/* Read/Write */
						 UDWORD	address);	/* スタートアドレス */
UBYTE			CheckMemorySub(
						 UBYTE	ReadWrite,		/* Read/Write */
						 UWORD	data,			/* リード／ライトデータ */
						 UWORD	*address);	/* スタートアドレス */
UBYTE			CheckIoWordLoop(
						 UDWORD	Port,		/* 出力ポートアドレス*/
						 UBYTE	OkCode,		/* ＯＫコード*/
						 UBYTE	NgCode );	/* ＮＧコード*/
UBYTE			CheckIoLoop(
						 UDWORD	Port,		/* 出力ポートアドレス*/
						 UBYTE	OkCode,		/* ＯＫコード*/
						 UBYTE	NgCode );	/* ＮＧコード*/
void			CheckModemTx( UBYTE );						/* なし */
UBYTE			CheckModemRx( void );						/* なし */
UBYTE			CheckModemRxData(
						 UBYTE * RxData,	/* 受信データ */
						 UBYTE *CheckPattern );	/* チェックパターン番号 */
UBYTE			CheckIDP(
						 UBYTE Machine,		/* 機種 */
						 UBYTE	OkCode,		/* ＯＫコード*/
						 UBYTE	NgCode );	/* ＮＧコード*/
#if (PRO_EX_CLASS1 == DISABLE)	/* By M.Tachibana 1998/07/07  */
void			MonitorSpeakerOn( void );		/* for ANZU Add	 1996/09/27	 By T.Yamaguchi */
#endif
void		CheckTransmit1080Hz(UBYTE);			/* 1997/11/17  By T.Yamaguchi */

void SCN_SetBuzzerFrequency( UBYTE );
void SCN_SetBuzzer( UBYTE );
UBYTE	CheckMortor(UBYTE motor);
void CheckShading(void);

#if defined(DBG)
#undef CMN_EnableInterrupt()
#undef CMN_DisableInterrupt()
#define CMN_EnableInterrupt()	_asm nop
#define CMN_DisableInterrupt()	_asm nop
#endif

/*************************************************************************
	module		:[アナログ・ファンクション・チェッカー、メイン]
	function	:[アナログ・ファンクション・チェッカー、メイン]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CHK]
	date		:[1995/02/10]
	author		:[増田]
*************************************************************************/
void	AnalogFunctionCheckerMain( void )						/* なし */
{
	UWORD	command;		/*コマンド*/
	UBYTE	machine;		/*機種（０：桐、１：椛）*/
	UBYTE	result;			/*検査結果*/
	UBYTE	result_out;		/*検査結果出力 ON/OFF*/
/*	UBYTE	lcd_work[31];	*/	/* ＬＣＤ表示ワーク */

	UBYTE	data;
	UWORD	word_data;

	/** コマンド読み込み */
	command = inpw(COMMAND_PORT);	/** コマンド読み込み */
	command &= 0x00ff;
	machine = (UBYTE)(command >> 7);	/** 機種 */

	outpw(COMMAND_PORT,(UWORD)command);					/** 検査結果ステータス出力 */

	/* RTCポートチェック時は、周波数チェックを外す 1997/11/17  By T.Yamaguchi */
	if ((command != CHECK_OUT_RTC_PORT1) && (command != CHECK_OUT_RTC_PORT2)) {
		/** 周波数チェック */
		CheckClock( 0 );			/** 周波数チェック */
	}

	/** コマンド解析 */
	result = 0;						/** 検査結果＝ＯＫ */
	result_out = OUT_ON;			/** 検査結果出力＝ＯＮ */

	/** ブザー音消去 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	outpw(ETC_PORT , IO_BIT_MUTE);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	IO__PADRH = 0x00ff;
#endif

	switch ( (command & 0x00ff) ) {	/** コマンド内容を調べる */
		case	CHECK_OUT_CPU_PA1:						/* ポートＡデータレジスタＨ */
			CMN_DisableInterrupt();
			outpw(IO_PADRH_PORT, OUT_CPU_PA1);					/* Ａ０Ｈ書き込み */
			result = OUT_CPU_PA1;
			break;
		case	CHECK_OUT_CPU_PA2:						/* ポートＡデータレジスタＨ */
			CMN_DisableInterrupt();
			outpw(IO_PADRH_PORT, OUT_CPU_PA2);					/** ５１Ｈ書き込み */
			result = OUT_CPU_PA2;
			break;
		case	CHECK_OUT_CPU_PA_UB1:					/* ポートＡデータレジスタＬ */
			CMN_DisableInterrupt();
			outpw(IO_PADRL_PORT, OUT_CPU_PA_UB1);					/** Ａ８Ｈ書き込み */
			result = OUT_CPU_PA_UB1;
			break;
		case	CHECK_OUT_CPU_PA_UB2:					/* ポートＡデータレジスタＬ */
			CMN_DisableInterrupt();
			outpw(IO_PADRL_PORT, OUT_CPU_PA_UB2);					/** ５５Ｈ書き込み */
			result = OUT_CPU_PA_UB2;
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		case	CHECK_OUT_CPU_PA_UB1H:						/* ポートＡデータレジスタＬ */
			CMN_DisableInterrupt();
			outpw(IO_PADRL_PORT, OUT_CPU_PA_UB1H);					/** ＡＡＨ書き込み */
			result = RSLT_CPU_PA_UB1H;
			break;
		case	CHECK_OUT_CPU_PA_UB2H:						/* ポートＡデータレジスタＬ */
			CMN_DisableInterrupt();
			outpw(IO_PADRL_PORT, OUT_CPU_PA_UB2H);					/** ５１Ｈ書き込み */
			result = RSLT_CPU_PA_UB2H;
			break;
		case	CHECK_OUT_CPU_PD1H:							/* ポートＤデータレジスタＨ */
			CMN_DisableInterrupt();
			outpw(IO_PDDRH_PORT, OUT_CPU_PD1H);					/* ４０Ｈ書き込み */
			result = RSLT_CPU_PD1H;
			break;
		case	CHECK_OUT_CPU_PD2H:							/* ポートＤデータレジスタＨ */
			CMN_DisableInterrupt();
			outpw(IO_PDDRH_PORT, OUT_CPU_PD2H);					/** ８０Ｈ書き込み */
			result = RSLT_CPU_PD2H;
			break;
		case	CHECK_OUT_COM_PORT1:							/* ＣＯＭ・ポ－ト */
			CMN_DisableInterrupt();
			outpw(COM_PORT, OUT_COM_PORT1);					/** ２８Ｈ書き込み */
			result = OUT_COM_PORT1;
			break;
		case	CHECK_OUT_COM_PORT2:							/* ＣＯＭ・ポ－ト */
			CMN_DisableInterrupt();
			outpw(COM_PORT, OUT_COM_PORT2);					/** １０Ｈ書き込み */
			result = OUT_COM_PORT2;
			break;
		case	CHECK_OUT_RTC_PORT1:							/* ＲＴＣ・ポ－ト */
			CMN_DisableInterrupt();
			outpw(RTC_PORT, OUT_RTC_PORT1);					/** ０ＡＨ書き込み */
			result = OUT_RTC_PORT1;
			break;
		case	CHECK_OUT_RTC_PORT2:							/* ＲＴＣ・ポ－ト */
			CMN_DisableInterrupt();
			outpw(RTC_PORT, OUT_RTC_PORT2);					/** ０ＡＨ書き込み */
			result = OUT_RTC_PORT2;
			break;
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
		case	CHECK_OUT_CPU_PE1:						/* ポートＥデータレジスタＨ */
			CMN_DisableInterrupt();
			outpw(IO_PEDR_PORT, OUT_CPU_PE1);					/* ８０Ｈ書き込み */
			result = OUT_CPU_PE1;
			break;
		case	CHECK_OUT_CPU_PE2:						/* ポートＥデータレジスタＨ */
			CMN_DisableInterrupt();
			outpw(IO_PEDR_PORT, OUT_CPU_PE2);					/** ００Ｈ書き込み */
			result = OUT_CPU_PE2;
			break;
		case	CHECK_OUT_CPU_PE_UB1:					/* ポートＥデータレジスタＬ */
			CMN_DisableInterrupt();
			outpw(IO_PEDR_PORT, OUT_CPU_PE_UB1);				/** ４０Ｈ書き込み */
			result = RSLT_CPU_PE_UB1;
			break;
		case	CHECK_OUT_CPU_PE_UB2:					/* ポートＥデータレジスタＬ */
			CMN_DisableInterrupt();
			outpw(IO_PEDR_PORT, OUT_CPU_PE_UB2);				/** ００Ｈ書き込み */
			result = RSLT_CPU_PE_UB2;
			break;
		case	CHECK_OUT_EXT1:							/* 外部ポート */
			CMN_DisableInterrupt();
			outpw(MODEM2_PORT, OUT_EXT1);					/* ２ＡＨ書き込み */
			result = OUT_EXT1;
			break;
		case	CHECK_OUT_EXT2:							/* 外部ポート */
			CMN_DisableInterrupt();
			outpw(MODEM2_PORT, OUT_EXT2);					/** ５５Ｈ書き込み */
			result = OUT_EXT2;
			break;
		case	CHECK_OUT_EXT_UB1:						/* 外部ポート */
			CMN_DisableInterrupt();
			outpw(MODEM2_PORT, OUT_EXT_UB1);					/** ２ＡＨ書き込み */
			result = RSLT_EXT_UB1;
			break;
		case	CHECK_OUT_EXT_UB2:						/* 外部ポート */
			CMN_DisableInterrupt();
			outpw(MODEM2_PORT, OUT_EXT_UB2);					/** ５５Ｈ書き込み */
			result = RSLT_EXT_UB2;
			break;
		/* Ｉ／Ｏリード項目 */
		case	CHECK_IN_CPU_PA:
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (inpw(IO_PADRL_PORT) & IN_CPU_PA));	/** ジャムカバーを読み、ステータスポートに出力 */
			}
			break;
		case	CHECK_IN_CPU_PA_UB:
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, ((inpw(IO_PADRL_PORT) >> 8) & IN_CPU_PA_UB));	/** ドラムステータスを読み、ステータスポートに出力 */
			}
			break;
		case	CHECK_IN_CPU_PD:
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, ((inpw(IO_PDDRH_PORT) >> 8) & IN_CPU_PD));	/** モータステータスを読み、ステータスポートに出力 */
			}
			break;
#endif
		case	CHECK_IN_CPU_PE:
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (inpw(IO_PEDR_PORT) & IN_CPU_PE));	/** ポートＥデータレジスタを読み、ステータスポートに出力 */
			}
			break;
		case	CHECK_IN_CPU_PE_UB:
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, ((inpw(IO_PEDR_PORT) >> 8) & IN_CPU_PE_UB));	/** ポートＥデータレジスタを読み、ステータスポートに出力 */
			}
			break;
		case	CHECK_IN_CPU_PF:
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (UWORD)(inp(IO_PFDR_PORT) & IN_CPU_PF));	/** ポートＦデータレジスタを読み、ステータスポートに出力 */
			}
			break;
		case	CHECK_IN_MD9604:
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (inpw(SENSOR1_PORT) & IN_MD9604) );	/** 入力ポートCS06を読み、ステータスポートに出力 */
			}
			break;
#if 0	/* (PRO_KEYPANEL == PANEL_ANZU_L) 削除1997/11/14  By T.Yamaguchi */
//		case	CHECK_IN_MD9604H:
//			for (;;) {						/** 無限ループ */
//				outpw( COMMAND_PORT, ((inpw(SENSOR1_PORT) >> 8) & IN_MD9604H) );	/** 入力ポートCS06を読み、ステータスポートに出力 */
//			}
//			break;
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
		case	CHECK_IN_EXT2:		/** ディップスイッチチェックが指定された */
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (inpw(SENSOR2_PORT) & IN_EXT2) );	/** 入力ポートCS06を読み、ステータスポートに出力 */
			}
			break;
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
		case	CHECK_APS_SENSOR:
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (inpw(APS_SENSOR_PORT) & IO_BIT_XAPS) );	/** 入力ポートCS06を読み、ステータスポートに出力 */
			}
			break;
#endif
		case	CHECK_BUZZER_HIGH:	/* ブザー大	*/
			SCN_SetBuzzerFrequency( ACK_BUZZER_FREQ );		/** 周波数の設定 */
			SYB_MonitorSpeakerOutLevel = SYS_VOLUME_MAXIMUM;	/* ボリューム最大に設定 */
			MonitorSpeakerVolumeControl();
			SpeakerMuteOff();
			SpeakerOutBuzzer();
#if 0
//			SYS_ETC_PortStatus = (IO_BIT_SPVR1 | IO_BIT_SPVR2);		/* ボリューム最大に設定 */
//			SYS_ETC_PortStatus &= ~IO_BIT_MUTE;
//			outpw(ETC_PORT , SYS_ETC_PortStatus);
//
//			SYS_Modem2PortStatus &= ~IO_BIT_RXA_BZ;
//			outpw(MODEM2_PORT, SYS_Modem2PortStatus );
#endif
			SCN_SetBuzzer(SCN_ENABLE);						/** ブザー許可 */
			result = BUZZER_HIGH_OK;
			break;
		case	CHECK_BUZZER_LOW:
			SCN_SetBuzzerFrequency( ACK_BUZZER_FREQ );		/** 周波数の設定 */
			SYB_MonitorSpeakerOutLevel = SYS_VOLUME_MINIMUM;	/* ボリューム最小に設定 */
			MonitorSpeakerVolumeControl();
			SpeakerMuteOff();
			SpeakerOutBuzzer();
#if 0
//			SYS_ETC_PortStatus = IO_BIT_SPVR1;		/* ボリューム最小に設定 */
//			SYS_ETC_PortStatus &= ~IO_BIT_MUTE;
//			outpw(ETC_PORT , SYS_ETC_PortStatus);
//
//			SYS_Modem2PortStatus &= ~IO_BIT_RXA_BZ;
//			outpw(MODEM2_PORT, SYS_Modem2PortStatus );
#endif
			SCN_SetBuzzer(SCN_ENABLE);						/** ブザー許可 */
			result = BUZZER_LOW_OK;
			break;
		case	CHECK_DRAM_WR:
			/** ＤＲＡＭチェック(WR) */
			CMN_DisableInterrupt();				/** 割り込み禁止 */
			CheckMemory(CHK_WRITE,0x1000000);	/** チェック IC36 */
			result = CHECK_RAM_WRITE;			/* ＲＡＭライト完了 */
			break;
		case	CHECK_DRAM_RD:
			/** ＤＲＡＭチェック(RD) */
			CMN_DisableInterrupt();				/** 割り込み禁止 */
			result = CHECK_DRAM_OK;			/** 検査結果＝ＯＫ */
			if (CheckMemory(CHK_READ,0x1000000) != OK ) {	/** チェック IC36 */
				result = CHECK_ERROR;	/** IC36 ＮＧ */
			}
			break;
		case	CHECK_SRAM_WR:
			/** ＳＲＡＭチェック(WR) */
			CMN_DisableInterrupt();				/** 割り込み禁止 */
			CheckMemory(CHK_WRITE,0x400000);	/** チェック IC36 */
			CheckMemory(CHK_WRITE,0x440000);	/** チェック IC36 add 1998/01/23  By T.Yamaguchi */
			result = CHECK_RAM_WRITE;			/* ＲＡＭライト完了 */
			break;
		case	CHECK_SRAM_RD:
			/** ＳＲＡＭチェック(RD) */
			CMN_DisableInterrupt();				/** 割り込み禁止 */
			result = CHECK_SRAM_OK;			/** 検査結果＝ＯＫ */
			if (CheckMemory(CHK_READ,0x400000) != OK ) {	/** チェック IC36 */
				result = CHECK_ERROR;	/** ＮＧ */
			}
			if (CheckMemory(CHK_READ,0x440000) != OK ) {	/** チェック IC36  add 1998/01/23  By T.Yamaguchi */
				result = CHECK_ERROR;	/** ＮＧ */
			}
			break;
		case	CHECK_MD9604:
			/* ＭＤ９６０４チェック(IC12) */
			/* 何処のアドレスをチェックするかよう確認すること */
			result = CheckIoWordLoop(PRINTER1_PORT ,CHECK_MD9604_OK , CHECK_ERROR );
#if 0
//			result = CheckIoLoop(PRINTER2_PORT ,CHECK_MD9604_OK , CHECK_ERROR );
//			result = CheckIoLoop(PRINTER3_PORT ,CHECK_MD9604_OK , CHECK_ERROR );
//			result = CheckIoLoop(PRINTER6_PORT ,CHECK_MD9604_OK , CHECK_ERROR );
//			result = CheckIoLoop(PRINTER7_PORT ,CHECK_MD9604_OK , CHECK_ERROR );
#endif
			break;
		case	CHECK_MD9605:
			/* ＭＤ９６０５チェック(IDP) */
			/** ＩＤＰ３０１チェックが指定された */
			result = CheckIDP( machine, CHECK_IDP301_OK, CHECK_IDP301_NG );	/** ＩＤＰ３０１チェック */
			break;
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
		case	CHECK_MD9509:
			/* ＭＤ９５０９チェック(プリンタ) */
			/* 何処のアドレスをチェックするかよう確認すること */
			if (CheckMortor(1)) {
				result = 0xC0;		/* モーター回転中 */
			}
			result = CHECK_MD9509_OK;
			break;
#endif
		case	CHECK_EXTEND_RAM:
			/** 拡張ＤＲＡＭチェック(RD) */
			result = CHECK_EXT_DRAM_OK;			/** 検査結果＝ＯＫ */
			CMN_DisableInterrupt();				/** 割り込み禁止 */
			CheckMemory(CHK_WRITE,0x1200000);	/** チェック IC36 */
			if (CheckMemory(CHK_READ,0x1200000) != OK ) {	/** チェック IC36 */
				result |= CHECK_DRAM_EX12_NG;	/** IC36 ＮＧ */
			}
			CheckMemory(CHK_WRITE,0x1400000);	/** チェック IC36 */
			if (CheckMemory(CHK_READ,0x1400000) != OK ) {	/** チェック IC36 */
				result |= CHECK_DRAM_EX14_NG;	/** IC36 ＮＧ */
 			}
			CheckMemory(CHK_WRITE,0x1600000);	/** チェック IC36 */
			if (CheckMemory(CHK_READ,0x1600000) != OK ) {	/** チェック IC36 */
				result |= CHECK_DRAM_EX16_NG;	/** IC36 ＮＧ */
			}
			CheckMemory(CHK_WRITE,0x1800000);	/** チェック IC36 */
			if (CheckMemory(CHK_READ,0x1800000) != OK ) {	/** チェック IC36 */
				result |= CHECK_DRAM_EX18_NG;	/** IC36 ＮＧ */
			}
			break;
#if (PRO_CLASS1 == ENABLE)
		case	CHECK_RS232C:
			/*	??????????????????????????????????????????????????????	*/
			/* RS-232C速度19200
			** RS-232Cキャラクタービット８
			** RS-232Cパリティなし
			** RS-232Cストップビット１
			*/
			SYB_SettingStatus[5] = 0x0e;
			Class1InitVar();
			result = CHECK_ERROR;	/* チェックエラー */
			RsTestMode = 0x03;	/* 折り返しテスト */
			RsTestChar = RsTestMode;	/**	テスト用キャラクタ＝？をセット	**/
			if (RsOpen('t', 'c', 60) == 1) {
				if ( RsClose('t') == 1) {		/**	テスト終了を待つ	**/
					result = CHECK_RS232C_OK;
				}
			}
#endif
			break;
		case	CHECK_OPTION:
			if (DPRD_CheckSlaveBoardEnable() == 1) {
				result = CHECK_OPTION_OK;
			}
			else {
				result = CHECK_ERROR;	/* チェックエラー */
			}
			break;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
		case	CHECK_AD_PORT_F0:	/* ＣＡＳＥＴ１ */
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (AD__ADDRA >> 2));	/** Ａ／ＤデータレジスタＡ */
			}
			break;
		case	CHECK_AD_PORT_F1:	/* ＣＡＳＥＴ２ */
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (AD__ADDRB >> 2));	/** Ａ／ＤデータレジスタＢ */
			}
			break;
		case	CHECK_AD_PORT_F2:	/* ＣＡＳＥＴ３ */
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (AD__ADDRC >> 2));	/** Ａ／ＤデータレジスタＢ */
			}
			break;
		case	CHECK_AD_PORT_F3:	/* ＴＥＭＰＲ */
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (AD__ADDRD >> 2));	/** Ａ／ＤデータレジスタＢ */
			}
			break;
		case	CHECK_AD_PORT_F5:	/* ＨＶＲ */
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (AD__ADDRF >> 2));	/** Ａ／ＤデータレジスタＢ */
			}
			break;
		case	CHECK_AD_PORT_F6:	/* ＴＨＭＳＴ */
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (AD__ADDRG >> 2));	/** Ａ／ＤデータレジスタＢ */
			}
			break;
		case	CHECK_AD_PORT_F7:	/* ＴＳ */
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (AD__ADDRH >> 2));	/** Ａ／ＤデータレジスタＢ */
			}
			break;
#endif
		case	CHECK_AD_PORT_F4:	/* ＢＡＴ */
			for (;;) {						/** 無限ループ */
				outpw( COMMAND_PORT, (AD__ADDRE >> 2));	/** Ａ／ＤデータレジスタＢ */
			}
			break;
		case	CHECK_MODEM_TX:				/** モデム送信チェックが指定された */
			CheckModemTx(0);						/** モデム送信チェック */
			result = CHECK_MODEM_TX;
			break;
		case	CHECK_MODEM_RX:				/** モデム受信チェックが指定された */
			result = CheckModemRx();			/** モデム受信チェック */
			break;
/*	その他の項目	*/
		case	CHECK_DMAU:			/** ＤＭＡＵチェックが指定された */
			CMN_DisableInterrupt();				/** 割り込み禁止 */
			result = CheckIoLoop(DMAU_PORT,CHECK_DMAU_OK,CHECK_DMAU_NG);/** ＤＭＡＵチェック */
			break;
		case	CHECK_RXA_RXOUT:	/** ＲＸＡ－ＲＸＯＵＴチェックが指定された*/
			result_out = OUT_OFF;				/** 検査結果出力＝ＯＦＦ */
			outp( ModemFilterControl, CHECK_RXA_RXOUT_BIT);	/** ＲＸＡ－ＲＸＯＵＴ*/
			break;
		case	CHECK_1100_BPF:		/** １１００ＢＰＦチェックが指定された*/
			result_out = OUT_OFF;				/** 検査結果出力＝ＯＦＦ */
			outp( ModemFilterControl, CHECK_1100_BPF_BIT);	/** １１００ＢＰＦ*/
			break;
		case	CHECK_462_LPF:		/** ４６２ＬＰＦチェックが指定された*/
			result_out = OUT_OFF;				/** 検査結果出力＝ＯＦＦ */
			outp( ModemFilterControl, CHECK_462_LPF_BIT);	/** ４６２ＬＰＦ*/
			break;
		case	CHECK_CODEC_SCN:	/** ＣＯＤＥＣスキャナーチェックが指定された */
			result = CheckIoWordLoop( CodecRegisterAddressTable[0][1], CHECK_CODEC_SCN_OK, CHECK_CODEC_SCN_NG );	/** ＣＯＤＥＣスキャナーチェック */
			break;
		case	CHECK_CODEC_PRN:	/** ＣＯＤＥＣプリンターチェックが指定された */
			result = CheckIoWordLoop( CodecRegisterAddressTable[1][1], CHECK_CODEC_PRN_OK, CHECK_CODEC_PRN_NG );	/** ＣＯＤＥＣプリンターチェック */
			break;
		case	CHECK_CODEC_COM:	/** ＣＯＤＥＣ通信チェックが指定された */
			result = CheckIoWordLoop( CodecRegisterAddressTable[2][1], CHECK_CODEC_COM_OK, CHECK_CODEC_COM_NG );	/** ＣＯＤＥＣ通信チェック */
			break;
		case	CHECK_SHADING:		/** 白黒判定 for ANZU_L */
			CheckShading();
/*
//			if (DIPP_ShadingExecute() == OK) {
//				result = 0xC0;			@* 終了 *@
//			}
//			else {
//				result = CHECK_ERROR;	@* チェックエラー *@
//			}
*/
			break;
		case CHECK_MOTOR:
			if (CheckMortor(1)) {
				result = 0xC0;		/* モーター回転中 */
			}
			break;
		case CHECK_MOTOR_STOP:
			CheckMortor(0);
			result = 0xC0;		/* モーターSTOP */
			break;
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
		case CHECK_FBS_MOTOR:
			if (CheckMortor(3)) {
				result = 0xC0;		/* ＦＢＳモーター回転中 */
			}
			break;
		case CHECK_FBS_MOTOR_STOP:
			CheckMortor(2);
			result = 0xC0;		/* ＦＢＳモーターSTOP */
			break;
#endif
		case CHECK_TX_OUT_1080HZ:
			CheckModemTx(1);						/** モデム送信チェック */
		case CHECK_TX_OUT_5000HZ:
			CheckModemTx(2);						/** モデム送信チェック */
		default:	/* ここには来ないはず */
			break;

	}

	/** 検査結果出力 */
	if ( result_out == OUT_ON ) {		/** 検査結果出力＝ＯＮの時 */
		for (;;) {						/** 無限ループ */
			outpw(COMMAND_PORT,(UWORD)result);		/** 検査結果ステータス出力 */
		}
	}

	/** 終了処理 */
	CMN_DisableInterrupt();		/** 割り込み禁止 */
	for (;;);						/** 無限ループ */
}

/*************************************************************************
	module		:[周波数チェック]
	function	:[周波数チェック]
	return		:[チェック結果]
	common		:[]
	condition	:[
		機種	０：ポプラＢ	１：
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CHK]
	date		:[1997/06/24]
	author		:[山口]
*************************************************************************/
void	CheckClock( UBYTE Machine )		/* 機種 */
{
	UWORD	tmp;		/*テンポラリー*/
	UWORD	i;			/*ループ*/
	/* 周波数チェック（以下の配列定数は配列０がポプラＢ、配列１が？） */
	UDWORD	clock_port[]	= {RTC_PORT,0xC203C0};	/* 周波数チェックポート*/
	UWORD	clock_CE_bit[]	= {0x0001,0x0001};	/* 周波数チェックＣＥビット */
	UWORD	clock_IO_bit[]	= {0x0004,0x0004};	/* 周波数チェックＩＯビット 0:ON(W) 1:OFF(R) */
/*	UWORD	clock_IO_bit[]	= {IO_BIT_RTC_IO,0x0004};	/@ 周波数チェックＩＯビット 1997/11/13  By T.Yamaguchi */


	/*---------------------------------------------------------------------
	** SAKAKIでは、ATLANTAに対して、IO_BIT_RTC_IOの論理が逆転しています。
	** チェッカー作成時には、変更が必要です。まだ変更していません。
	** 1998/07/10 H.Yoshikawa
	*/

	/** ＣＥ，ＩＯをＬｏｗにセット */
	tmp = clock_IO_bit[Machine];		/** ＣＥ，ＩＯをＯＦＦ */
	outpw(clock_port[Machine],tmp);		/** 周波数チェックポート出力 */

	/** ＣＥ、ＩＯ制御 */
	tmp |= clock_CE_bit[Machine];		/** ＣＥ ON */
	outpw(clock_port[Machine],tmp);		/** 周波数チェックポート出力 */
	for ( i = 0; i < 1801; i++ ) {}			/** ５～６ｍｓウエイト */
	for ( i = 0; i < 5; i++ ) {
		tmp &= (~clock_IO_bit[Machine]);/** ＩＯ ON */
		outpw(clock_port[Machine],tmp);	/** 周波数チェックポート出力 */
		tmp |= clock_IO_bit[Machine];	/** ＩＯ OFF */
		outpw(clock_port[Machine],tmp);	/** 周波数チェックポート出力 */
	}
}

/*************************************************************************
	module		:[メモリチェック]
	function	:[メモリチェック]
	return		:[チェック結果 OK:NG]
	common		:[]
	condition	:[
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CHK]
	date		:[1997/06/10]
	author		:[山口]
*************************************************************************/
UBYTE	CheckMemory(
		UBYTE	ReadWrite,		/* Read/Write (CHK_READ/CHK_WRITE)*/
		UDWORD	chk_address)		/* チェックするアドレス */
{
	UBYTE	ret;			/* チェック結果 OK:NG*/
	UWORD	*top_address;

	ret = OK;								/** 検査結果＝ＯＫ */
	
	top_address = (UWORD *)((UDWORD)chk_address);
	
	if (ReadWrite == CHK_WRITE) {
		CheckMemorySub(CHK_WRITE,0x0001,top_address);	/** チェック IC36 */
/*		CheckMemorySub(CHK_WRITE,0x0101,top_address); */
		CheckMemorySub(CHK_WRITE,0x0202,top_address+0x1);
		CheckMemorySub(CHK_WRITE,0x0404,top_address+0x2);
		CheckMemorySub(CHK_WRITE,0x0808,top_address+0x4);
		CheckMemorySub(CHK_WRITE,0x1010,top_address+0x8);
		CheckMemorySub(CHK_WRITE,0x2020,top_address+0x10);
		CheckMemorySub(CHK_WRITE,0x4040,top_address+0x20);
		CheckMemorySub(CHK_WRITE,0x8080,top_address+0x40);
		CheckMemorySub(CHK_WRITE,0x0202,top_address+0x80);
		CheckMemorySub(CHK_WRITE,0x0404,top_address+0x100);
		CheckMemorySub(CHK_WRITE,0x0808,top_address+0x200);
		CheckMemorySub(CHK_WRITE,0x1010,top_address+0x400);
		CheckMemorySub(CHK_WRITE,0x2020,top_address+0x800);
		CheckMemorySub(CHK_WRITE,0x5555,top_address+0x1000);
		CheckMemorySub(CHK_WRITE,0xAAAA,top_address+0x2000);
		CheckMemorySub(CHK_WRITE,0x5555,top_address+0x4000);
	}
	else {	/* CHK_READ */
		if (CheckMemorySub(CHK_READ,0x0001,(UWORD *)(top_address)) != OK ) {	/** チェック IC36 */
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x0202,top_address+0x1) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x0404,top_address+0x2) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x0808,top_address+0x4) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x1010,top_address+0x8) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x2020,top_address+0x10) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x4040,top_address+0x20) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x8080,top_address+0x40) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x0202,top_address+0x80) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x0404,top_address+0x100) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x0808,top_address+0x200) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x1010,top_address+0x400) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x2020,top_address+0x800) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x5555,top_address+0x1000) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0xAAAA,top_address+0x2000) != OK) {
			ret = NG;	/** ＮＧ */
		}
		if (CheckMemorySub(CHK_READ,0x5555,top_address+0x4000) != OK) {
			ret = NG;	/** ＮＧ */
		}
	}
	return ( ret );							/** 検査結果返す */
}
/*************************************************************************
	module		:[メモリチェック]
	function	:[メモリチェック]
	return		:[チェック結果 OK:NG]
	common		:[]
	condition	:[
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CHK]
	date		:[1997/06/10]
	author		:[山口]
*************************************************************************/
UBYTE	CheckMemorySub(
		UBYTE	ReadWrite,		/* Read/Write (CHK_READ/CHK_WRITE)*/
		UWORD	data,
		UWORD	*address)		/* チェックするアドレス */
{
	UBYTE	ret;			/* チェック結果 OK:NG*/

	ret = OK;								/** 検査結果＝ＯＫ */
	
	if (ReadWrite == CHK_WRITE) {
		*address = data;
	}
	else {	/* CHK_READ */
		if (*address != data) {
			ret = NG;
		}
	}
		
	return ( ret );							/** 検査結果返す */
}

/*************************************************************************
	module		:[ゲートアレイチェック]
	function	:[ゲートアレイチェック]
	return		:[チェック結果 ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CHK]
	date		:[1997/07/02]
	author		:[山口]
*************************************************************************/
UBYTE	CheckIoWordLoop(
						 UDWORD	Port,		/* 出力ポートアドレス*/
						 UBYTE	OkCode,		/* ＯＫコード*/
						 UBYTE	NgCode )	/* ＮＧコード*/
{
	UWORD	i;			/*ループ*/
	UBYTE	result;		/*チェック結果*/

	result = OkCode;						/** 検査結果＝ＯＫ */
	for ( i = 1; i <= 0xff; i += 3 ) {		/** ライトデータの数分検査を行う */
		outpw( Port, i );/** 検査データポート出力 */
		if ( (UWORD)inpw( Port ) != i ) {	/** 検査データリード結果ＯＫ？ */
			result = NgCode;				/** ＤＭＡＵチェック ＮＧ*/
			break;							/** ループ抜ける */
		}
	}
	return ( result );						/** 検査結果返す */
}
/*************************************************************************
	module		:[ＤＭＡＵチェック]
	function	:[ＤＭＡＵチェック]
	return		:[チェック結果 CHECK_DMAU_OK/CHECK_DMAU_NG]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CHK]
	date		:[1995/02/10]
	author		:[増田]
*************************************************************************/
UBYTE	CheckIoLoop(
						 UDWORD	Port,		/* 出力ポートアドレス*/
						 UBYTE	OkCode,		/* ＯＫコード*/
						 UBYTE	NgCode )	/* ＮＧコード*/
{
	UWORD	i;			/*ループ*/
	UBYTE	result;		/*チェック結果*/

	result = OkCode;						/** 検査結果＝ＯＫ */
	for ( i = 1; i <= 0xff; i += 3 ) {		/** ライトデータの数分検査を行う */
		outp( Port, (UBYTE)i );/** 検査データポート出力 */
		if ( (UWORD)inp( Port ) != i ) {	/** 検査データリード結果ＯＫ？ */
			result = NgCode;				/** ＤＭＡＵチェック ＮＧ*/
			break;							/** ループ抜ける */
		}
	}
	return ( result );						/** 検査結果返す */
}


/*************************************************************************
	module		:[モデム送信チェック]
	function	:[モデム送信チェック]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ModemBlock.TxAttenuation,SYS_MachineParameter[1],ServiceFuncTxは
		この関数にはいる前にセットされている事とする。
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CHK]
	date		:[1995/02/17]
	author		:[増田]
*************************************************************************/
void	CheckModemTx( UBYTE mode )						/* なし */
{
	UBYTE	i;		/* loop */
	UWORD	count;
	count = 0;

	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_FAXCOM;	/* 1997/10/20  By T.Yamaguchi */
	/* ANZU でスピーカがなる様にした 96/09/27 By T.Yamaguchi */
	SYB_MonitorSpeakerOutLevel = SYS_VOLUME_MAXIMUM;		/* ボリューム最大に設定 */
	MonitorSpeakerOn();

#if (PRO_MODEM == ORANGE3)
	FilterRXA_Set();
	AnalogSwitchRXA_Set();
#endif

#if (PRO_MODEM == R288F)
	/* POPLAR_H 搭載の R288F のアナログ入力は、モデム基盤上の
	** 外部回路で TONE/RXA を切り替える。
	** H.Kubo 1997/11/12 
	*/
	AnalogSwitchRXA_Set();
#endif


	SYS_Modem1PortStatus = 0;			/** MRD9201モデム・ポ－ト1変数クリアー */
	CML_RelayOn();						/** ＣＭＬリレーを引く */
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
	H_RelayOn();
	L_RelayOn();
	S_RelayOff();
	T_RelayOff();
	CONT_24V_Off();
	PC_24V_On();
#endif
#if (PRO_NCU_TYPE == ANZU_USA_TYPE ) || (PRO_NCU_TYPE == ANZU_GBR_TYPE )
	H_RelayOn();
	L_RelayOn();			/* ＡＮＺＵのカプラにはＬリレーはない 95.12.07 t.yamaguchi */
	S_RelayOff();				/* Add by TH92115 1994/08/29 */
#endif
	InitializeModemWork();				/** モデム変数初期化 */

#if (PRO_EXT_DMAC == DISABLE)
	/* 再起動の時に割り込み要求をクリアする 1997/08/06  By T.Yamaguchi */
	if (SH__ISR & IRQ5_STATUS) {
		SH__ISR &= ~IRQ5_STATUS;
	}
#endif

	if (mode != 0) {
		/* 1080Hzを出すチェックの場合 */
		CheckTransmit1080Hz(mode);
	}
	else {

	/* 変更 by T.Soneoka 1996/09/05 */
	/*	ModemBlock.TxAttenuation = 0x0d;	/ アッテネータレベル設定	13dB */
	PartnerAbility1 = 0x0d;				/* 変更 */
	/** 110110110110....のデータセット（LSBからセット） */
	for ( i = 0; i < 255; i += 3 ) {
		ModemZeroBuffer[i+0] = CHECK_MDM_DATA0;
		ModemZeroBuffer[i+1] = CHECK_MDM_DATA1;
		ModemZeroBuffer[i+2] = CHECK_MDM_DATA2;
	}

	ModemBlock.Type = TYPE_V17;			/** モデムタイプ　Ｖ１７設定 */
	ModemBlock.Speed = SPEED_14400;		/** モデムスピード１４４００ｂｐｓ設定 */

	ModemBlock.Training = TRAINING_LONG;/** ロングトレーニング設定 */
	ModemBlock.Mode = MODE_TX_TCF;		/** 交信モードを送信Ｇ３に設定 */
	ModemBlock.Chain = CHAIN_ON;
	TxG3_Open();						/** トレーニング送信モデムオープン */
	for (count = 0; count < 80; count++) {	/* 変更1997/10/20  By T.Yamaguchi */
	/* for (;;) {							/@@ 無限ループ */
		while (ModemControl.UsedCount == MODEM_BUFFER_MAX) {	/** モデムバッファ使用本数が８本の時 */
			wai_tsk(10/10);				/** タスクウェイト１０ｍｓ */
		}
		TxG3_Write((UBYTE *)&ModemZeroBuffer[0], 255);	/** Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／データ数登録） */
		outpw(COMMAND_PORT, (UWORD)CHECK_MDM_TX);/** モデム出力中*/
	}

	}	/* 1997/11/17  By T.Yamaguchi */


	/* リレーを戻すように変更 */
	CML_RelayOff();						/** ＣＭＬリレーを引く */
#if (PRO_NCU_TYPE == HINOKI_TYPE) || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */
	AnalogSwitchTONE_Set();
#endif
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
	H_RelayOff();
	L_RelayOff();
	S_RelayOff();
	T_RelayOff();
	CONT_24V_Off();
	PC_24V_Off();
#endif
#if ( PRO_NCU_TYPE == ANZU_USA_TYPE )	|| ( PRO_NCU_TYPE == ANZU_GBR_TYPE ) /* アンズＵＳＡにはＬリレーが無いのでＨリレーをｏｆｆ */
	S_RelayOff();					/** Ｓリレー OFF */
	DP_RelayOff();					/** ＤＰリレー OFF */
	GenerateRingKeyOff();			/** 疑似ベル用 OFF */
	CONT_24V_Off();		/* add by m.harada 95.06.23 */
#endif
	MDM_FilterStandbyMode();			/** モデム・フィルター初期化 */

	MonitorSpeakerOff();

}

/*************************************************************************
	module		:[モデム受信チェック]
	function	:[モデム受信チェック]
	return		:[チェック結果 CHECK_MDM_TRAINING]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CHK]
	date		:[1995/02/17]
	author		:[増田]
*************************************************************************/
UBYTE	CheckModemRx( void )						/* なし */
{
	UBYTE	result;		/* チェック結果 */
	UBYTE	check_ptn;	/* チェックパターン番号 */
	UBYTE	count;

	count = 0;

	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_FAXCOM;	/* 1997/10/20  By T.Yamaguchi */
	/* ANZU でスピーカがなる様にした 96/09/27 By T.Yamaguchi */
	SYB_MonitorSpeakerOutLevel = SYS_VOLUME_MAXIMUM;		/* ボリューム最大に設定 */
	MonitorSpeakerOn();

#if (PRO_MODEM == ORANGE3)
	FilterRXA_Set();
	AnalogSwitchRXA_Set();
#endif

#if (PRO_MODEM == R288F)
	/* POPLAR_H 搭載の R288F のアナログ入力は、モデム基盤上の
	** 外部回路で TONE/RXA を切り替える。
	** H.Kubo 1997/11/12 
	*/
	AnalogSwitchRXA_Set();
#endif

	SYS_Modem1PortStatus = 0;			/** MRD9201モデム・ポ－ト1変数クリアー */
	CML_RelayOn();						/** ＣＭＬリレーを引く */
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
	H_RelayOn();
	L_RelayOn();
	S_RelayOff();
	T_RelayOff();
	CONT_24V_Off();
	PC_24V_On();
#endif
#if (PRO_NCU_TYPE == ANZU_USA_TYPE ) || (PRO_NCU_TYPE == ANZU_GBR_TYPE )
	H_RelayOn();
	L_RelayOn();			/* ＡＮＺＵのカプラにはＬリレーはない 95.12.07 t.yamaguchi */
	S_RelayOff();				/* Add by TH92115 1994/08/29 */
#endif
	InitializeModemWork();				/** モデム変数初期化 */
#if (PRO_EXT_DMAC == DISABLE)
	/* 再起動の時に割り込み要求をクリアする 1997/08/06  By T.Yamaguchi */
	if (SH__ISR & IRQ5_STATUS) {
		SH__ISR &= ~IRQ5_STATUS;
	}
#endif

/* 変更 by T.Soneoka 1996/09/05 */
	ModemBlock.TxAttenuation = 0x0d;	/** アッテネータレベル設定	13dB*/
	ModemBlock.Type = TYPE_V17;			/** モデムタイプ　Ｖ１７設定 */
	ModemBlock.Speed = SPEED_14400;		/** モデムスピード１４４００ｂｐｓ設定 */
	ModemBlock.Training = TRAINING_LONG;/** ロングトレーニング設定 */
	RxG3_Open();						/** トレーニング受信モデムオープン */
	if (CheckTraining(5000) == NO) {	/** トレーニング検出がＮＧの時 */
		RxG3_Close();
		result = CHECK_MDM_TRAINING_NG;	/** モデムトレーニングエラー*/
	}
	else {								/** トレーニング検出がＯＫの時 */
		check_ptn = 9;					/** チェックパターン番号＝９ */
		for (;;) {						/** 無限ループ */
			if (RxG3_Read() == RCV_BLOCK){		/** モデムバッファ読み出し／１ブロック受信完了ＯＫ	*/
				if ( CheckModemRxData( &MDM_ModemBuffer[ModemControl.ReadPoint][0], &check_ptn) == OK ) {	/** 受信データ検査ＯＫ */
					result = CHECK_MDM_RX_OK;	/** モデム受信データＯＫ*/
					break;
				}
				else {							/** 受信データ検査ＮＧ */
					outpw(COMMAND_PORT, (UWORD)CHECK_MDM_RX_NG);	/** モデム受信データＮＧ*/
					check_ptn = 9;				/** チェックパターン番号＝９ */
					if ( count >= 30 ) {
						result = CHECK_MDM_RX_NG;	/** モデム受信データＮＧ*/
						break;
					}
				}
				NextModemBufferReadPointSet();	/** モデムバッファ読み出し位置更新 */
			}
			else {								/** モデムバッファ読み出し／１ブロック受信完了ＮＧ	*/
				outpw(COMMAND_PORT, (UWORD)CHECK_MDM_RX_NG);		/** モデム受信データＮＧ*/
				check_ptn = 9;					/** チェックパターン番号＝９ */
				NextModemBufferReadPointSet();	/** モデムバッファ読み出し位置更新 */
				if ( count >= 30 ) {
					result = CHECK_MDM_RX_NG;	/** モデム受信データＮＧ*/
					break;
				}
			}
			count ++;
		}
	}

	/* リレーを戻すように変更 */
	CML_RelayOff();						/** ＣＭＬリレーを引く */
#if (PRO_NCU_TYPE == HINOKI_TYPE) || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */
	AnalogSwitchTONE_Set();
#endif
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
	H_RelayOff();
	L_RelayOff();
	S_RelayOff();
	T_RelayOff();
	CONT_24V_Off();
	PC_24V_Off();
#endif
#if ( PRO_NCU_TYPE == ANZU_USA_TYPE )	|| ( PRO_NCU_TYPE == ANZU_GBR_TYPE ) /* アンズＵＳＡにはＬリレーが無いのでＨリレーをｏｆｆ */
	S_RelayOff();					/** Ｓリレー OFF */
	DP_RelayOff();					/** ＤＰリレー OFF */
	GenerateRingKeyOff();			/** 疑似ベル用 OFF */
	CONT_24V_Off();		/* add by m.harada 95.06.23 */
#endif
	MDM_FilterStandbyMode();			/** モデム・フィルター初期化 */
	MonitorSpeakerOff();

	return ( result );							/** 検査結果返す */
}

/*************************************************************************
	module		:[モデム受信データチェック]
	function	:[モデム受信データチェック]
	return		:[チェック結果 OK/NG]
	common		:[]
	condition	:[
		チェックパターン番号＝９の時は、先頭チェック。
	]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CHK]
	date		:[1995/02/21]
	author		:[増田]
*************************************************************************/
UBYTE	CheckModemRxData(
						 UBYTE * RxData,	/* 受信データ */
						 UBYTE *CheckPattern )	/* チェックパターン番号 */
{
	UWORD	i;		/* loop */
	UBYTE	check_pattern[3] = {
						CHECK_MDM_DATA0,
						CHECK_MDM_DATA1,
						CHECK_MDM_DATA2 };		/* チェックパターン */

	if ( *CheckPattern == 9 ) {			/** 先頭チェックの時 */
		(*CheckPattern) = 0;			/** チェックパターン番号＝０ */
		for ( i = 0; i < 3; i++ ) {		/** チェックパターン数分ループ */
			if ( (*RxData) == check_pattern[i] ) {	/** データとチェックパターンが一致した時 */
				(*CheckPattern) = (UBYTE)i;	/** チェックパターン番号セット */
				break;								/** ループ抜ける */
			}
		}
	}
	for ( i = 0; i < MODEM_DMA_SIZE; i++ ) {		/** モデムデータサイズ分ループ */
		if ( (*RxData) != check_pattern[*CheckPattern] ) {	/** データが異常の時 */
			return ( NG );									/** 検査結果ＮＧ */
		}
		(*CheckPattern)++;									/** チェックパターン番号進める */
		RxData++;											/** 受信データ進める */
		if ( (*CheckPattern) >= 3 ) {						/** チェックパターン番号が３以上の時 */
			(*CheckPattern) = 0;							/** チェックパターン番号＝０ */
		}
	}
	return ( OK );											/** 検査結果ＯＫ */
}

/*************************************************************************
	module		:[ＣＯＤＥＣチェック]
	function	:[ＣＯＤＥＣチェック]
	return		:[チェック結果]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CHK]
	date		:[1995/04/13]
	author		:[増田]
*************************************************************************/
UBYTE	CheckIDP(
						 UBYTE Machine,		/* 機種 */
						 UBYTE	OkCode,		/* ＯＫコード*/
						 UBYTE	NgCode )	/* ＮＧコード*/
{
	UWORD	i;			/*ループ*/
	UBYTE	result;		/*チェック結果*/
	/* 周波数チェック（以下の配列定数は配列０が桐、配列１が椛） */
	UDWORD	idp_ad_port[]	= {0xC20508,0xC20508};	/* ＩＤＰアドレスポート*/
	UDWORD	idp_dt_port[]	= {0xC2050a,0xC2050a};	/* ＩＤＰデータポート*/

	result = OkCode;						/** 検査結果＝ＯＫ */
	for ( i = 1; i <= 0xff; i += 3 ) {		/** ライトデータの数分検査を行う */
		outpw( idp_ad_port[Machine], 0x0002 );		/** アドレスポート出力 */
		outpw( idp_dt_port[Machine], i );		/** データポート出力 */
		outpw( idp_ad_port[Machine], 0x0002 );		/** アドレスポート出力 */
		if ( (inpw( idp_dt_port[Machine] ) & 0x00FF) != i ) {	/** 検査データリード結果ＯＫ？ */
			result = NgCode;				/** ＤＭＡＵチェック ＮＧ*/
			break;							/** ループ抜ける */
		}
	}
	return ( result );						/** 検査結果返す */
}


/*************************************************************************
	module		:[モーターチェック]
	function	:[モーターチェック]
	return		:[チェック結果]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CHK]
	date		:[1997/11/17]
	author		:[山口]
*************************************************************************/
UBYTE	CheckMortor(UBYTE motor)
{
	/** モータ動作ＯＮ／ＯＦＦ設定 */

	SCN_Init();
#if (PRO_FBS == ENABLE)
	if ((motor == 0) || (motor == 1)) {
		SCN_SetMotorDrive( SCN_ADF );
	}
	else {
		SCN_SetMotorDrive( SCN_FBS );
		if (motor == 2) {
			motor = 0;
		}
	}
#endif
	if ( motor ) {	/** モーター回転の時 */
		CMN_DisableInterrupt();		/** 割り込み禁止 */
		SCN_MTCNT_Status = 0;									/** */
		SCN_VerticalMode = SCN_DOC_OUT;							/** 原稿繰り込み又は排出用のモードにセット */
		SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode];	/** モーター制御用テーブルのポインター確保 */
		SCN_MotorTablePoint = SCN_MotorTable->InitialSpeed;		/** モーターのテーブルを初期値にセット */
		SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;				/** モーターをスルー・アップするように設定 */
		SCN_SetMotorSpeed();						/** モーターの速度設定(MTPC0,1)、速度変更間隔設定(MTP0) */
		SCN_SetMotor(SCN_DISABLE);					/** モーター・ディスエーブル */
		SCN_LatchMotorSpeedAndInterval();			/** モーター速度変更間隔、速度初期ラッチ */
		SCN_SetMotorSpeedIntervalInt(SCN_ENABLE);	/** モーター速度変更間隔割り込み許可	INTMTEN-MTCNT */
		SCN_SetMotorPulse(SCN_ENABLE);				/** モーター励磁ＯＮ MTCLR-MTCNT */
		SCN_SetMotorClockwise(SCN_ENABLE);			/** モーター回転方向セット CWXCCW-MTCNT */
		SCN_SetMotorCurrent(SCN_CURRENT_POWER_100); /** モーターの電流値を１００％にセット */
		SCN_SetMotor(SCN_ENABLE);					/** モーター・イネーブル・セット MTEN-MTCNT */
		return(1);
	}
	else {							/** モーターディスエーブルの時 */
		SCN_MTCNT_Status = 0;									/** */
		SCN_VerticalMode = SCN_DOC_OUT;							/** 原稿繰り込み又は排出用のモードにセット */
		SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode];	/** モーター制御用テーブルのポインター確保 */
		SCN_MotorTablePoint = SCN_MotorTable->InitialSpeed;		/** モーターのテーブルを初期値にセット */
		SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;				/** モーターをスルー・アップするように設定 */
		SCN_SetMotorSpeed();									/** モーターの速度設定(MTPC0,1)、速度変更間隔設定(MTP0) */
		SCN_SetMotorCurrent(SCN_CURRENT_POWER_0);				/** モーターの電流値を０％にセット */
		SCN_SetMotorSpeedIntervalInt(SCN_DISABLE);				/** モーター速度変更間隔割り込み禁止	INTMTEN-MTCNT */
		SCN_ClearMotorPulseCounter();							/** モーター・パルス・カウンター・クリア */
		SCN_SetMotorPulse(SCN_DISABLE);							/** モーター励磁 OFF MTCLR-MTCNT */
		SCN_SetMotor(SCN_DISABLE);								/** モーター・ディスエーブル・セット MTEN-MTCNT */
		return(0);
	}
}

/*************************************************************************
	module		:[１０８０Ｈｚ送出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CHK]
	date		:[1997/11/17]
	author		:[山口]
*************************************************************************/
void	CheckTransmit1080Hz(UBYTE mode)
{
	UBYTE	tone_type;
	UWORD	time;

	/*-------------------------------------*/
	/* 1080Hzの単一トーンを500ms送出します */
	/*-------------------------------------*/
	if (mode == 1) {
		tone_type = TONE_1080HZ;		/* 1080hz */
	}
	else if (mode == 2) {
		tone_type = TONE_2100HZ;		/* 2100hz */
	}

	time	  = 0xFFFF;				/* 無限 */

	MDM_ToneTx(tone_type,time);
}

/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CHK]
	date		:[1997/11/18]
	author		:[野瀬]
*************************************************************************/
void CheckShading(void)
{
	CMN_DisableInterrupt();

	DIPP_InitialSet();  /** DIPP-AS初期設定 */

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif
	LampOn();                       /** ランプオン */

	DIPP_WriteInitialRAM();
	DIPP_WriteShadingRAM();

	SCN_Control.DocumentMode = SYS_NORMAL;
	SCN_Control.DocumentSize = SYS_DOCUMENT_A4_SIZE;
	SYS_DocumentWidthFullFlag = 1;
	SCN_Control.UseType = IDP_DOCUMENT_STORE;
	SYS_DocumentStoreItem = SYS_MEM_MULTI_COPY_FILE;

	SCN_SetDIPP_Parameter();	/* IDP301-DIPPの設定を抜き出す  1996/11/25 */

	IP_InitialSet();

	IP_SetDitherMatrix(1*1);

	IP_ReductionSet(IP_SCANNER_REDUCTION, 1000);

	/*-----------------*/
	/** IP処理スタート */
	/*-----------------*/
	IP_Control.IP_UseType = IDP_DOCUMENT_STORE;
	IP_InputOutputChange();
	IdpRegisterStatus.IP_AR = IP_CR_R03_ADR;
	IdpOutputByte(IP_AR_PORT,IdpRegisterStatus.IP_AR);
	IdpRegisterStatus.IP_CR = 0xD8;		/* IDP-IP input size 216 word */
	IdpOutputByte(IP_CR_PORT,IdpRegisterStatus.IP_CR);
	IP_SetBitIPST(IDP_BIT_ON);

	SCN_SetSoftCTSCAN( SCN_ENABLE );	/* CTSCAN ON  */

	while (1) ;	/* 無限ループ */
}
