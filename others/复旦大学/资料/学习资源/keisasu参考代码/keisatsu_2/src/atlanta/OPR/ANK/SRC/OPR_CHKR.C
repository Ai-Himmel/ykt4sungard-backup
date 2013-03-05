/************************************************************************
*	System		: SATSUKI2
*	File Name	: OPR_CHEK.C
*	Author		: 
*	Date		: 2003/08/26
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: チェッカーオペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\ncu_def.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\scn_pro.h"
#include	"\src\atlanta\define\buzzer.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\define\fcm_def.h"

#include	"\src\atlanta\ext_v\bkupram.h"


#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\define\keycode.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\opr\ank\ext_v\key_tbl.h"

#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\ext_v\sys_port.h"

#if (PRO_MODEM == R288F)
	#if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
		#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
		#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
		#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
	#else
		#include "\src\atlanta\mdm\r288f\define\mdm_io.h"
		#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
		#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
	#endif
#endif

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_io.h"
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"
#endif


#if defined(STOCKHM2)
#include "\src\atlanta\stockhm2\define\lvnd_tib.h"
#include "\src\atlanta\stockhm2\define\lvndport.h"
#elif defined(SATSUKI2)
#include "\src\atlanta\satsuki2\define\sats_tib.h"
#include "\src\atlanta\satsuki2\define\satsport.h"
#elif defined(HINOKI3)		/* Add by Y.Kano 2004/12/21 */
#include "\src\atlanta\hinoki\define\hino_tib.h"
#include "\src\atlanta\hinoki\define\hinoport.h"
#else
	/* No Need */
#endif

 #if defined(STOCKHM2)
#include "\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
 #else
#include "\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
 #endif
#include	"\src\atlanta\ext_v\ncu_data.h"
#include	"\src\atlanta\ext_v\ncu_tbl.h"
#include	"\src\atlanta\define\ncu_stat.h"

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) || defined(HINOKI3)	/* Added by SMuratec K.W.Q 2003/09/25 */ /* Add by Y.Kano 2004/12/21 */

CONST UBYTE	CheckerRomSw = 0;

/*************************************************************************
	module		:[あるキー押しながら電源ＯＮするとチェッカーモードになる]
	function	:[
	]
	return		:[
				1:あるキーが押されている
				0:押されてない
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/11/20]
	author		:[]
*************************************************************************/
UBYTE CMN_StartCheckerModeKey(void)
{
	UBYTE	row,col,keycode,key;
	
	key = Input(SCI_RDR0);

	row = key / 8;	/* ROWの取り出し */
	col = key % 8;	/* COLの取り出し */

	keycode = (UWORD)KeyTableSheet1[row][col];
	
	if (CheckerRomSw) {	/* パッチがあたっていれば、その値を返す */
		return(CHECKER_PANEL_ASSY);
	}

	/* テンキー（１） */
	if (keycode == TEN_1_KEY) {
		return(CHECKER_MAIN_TEST);
	}

	return(0);
}

/*************************************************************************
	module		:[メイン基盤検査]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2000/05/09]
	author		:[前田雅也]
*************************************************************************/
void MainCheckerFunctionMode(void)
{
	UBYTE	key;
 	UBYTE	keytype;

	/* 全ＬＥＤの消灯 */
	AllLedOff();

	if (!CheckRTC_TestEnable()) {	/* RTCテストが不可能な時 */
		NackBuzzer();

		RTCTestEnd();
		return;
	}
	
	RTCTestStart();	
	
	while (1) {
		DisplayStringHigh(0, OPR_CheckerMainTestWord);
		ClearDisplayLow();

		OPR_GetKey(KEY_WAIT_FEW_TIME);	/* キー取り込み */
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case COPY:			/* コピーキー入力 */
			wai_tsk(200);
			RestartSystem();
			return;
		case KEY_TIME_UP:
			break;
		case START:			/* スタートキー入力 */
			if( MainCheckerFunctionTest() ){
				SYS_CheckerMode = 0;		/* Added by SMuratec K.W.Q 2003/10/27 */
				return;
			}
			else{
				break;
			}
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
	
	return;
}

/*************************************************************************
	module		:[パネル検査]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[]
	author		:[]
*************************************************************************/
void PanelCheckerFunctionMode(void)
{
	UBYTE	key;
 	UBYTE	keytype;

	AllLedOff();

	while (1) {
		DisplayStringHigh(0, OPR_CheckerPanelAssyWord);
		ClearDisplayLow();
	
		OPR_GetKey(KEY_WAIT_FEW_TIME);	/* キー取り込み */
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case STOP:
			UpdateLCD();
			return;
		case KEY_TIME_UP:
			break;
#if defined(HINOKI3)	/* HINOKI3はテンキーを使用する。by Y.Kano 2004/12/22 */
		case NUMBER:		/* テンキー					*/
			switch (key) {
			case TEN_1_KEY:	/* LED TEST */
				SF_All_LED_Test();
				break;
			case TEN_2_KEY:	/* LCD TEST */
				SF_LCD_Test();
				break;
			case TEN_3_KEY:	/* KEY TEST */
				IsSingleKeyOperation = FALSE;
				SF_PanelKeyTest();
				IsSingleKeyOperation = TRUE;
				break;
#else
		case ONETOUCH:
			switch (key) {
			case ONETOUCH_02_KEY:	/* LED TEST */
				SF_All_LED_Test();
				break;
			case ONETOUCH_03_KEY:	/* LCD TEST */
				SF_LCD_Test();
				break;
			case ONETOUCH_04_KEY:	/* KEY TEST */
 #if 1 /* (メモリ送信キー押下で、表示はメモリソウシンにすると、自動受信キー押下で、表示はジュシンにする。) Modified by SMuratec L.Z.W 2003/09/10 */
				IsSingleKeyOperation = FALSE;
				SF_PanelKeyTest();
				IsSingleKeyOperation = TRUE;
 #else
				SF_PanelKeyTest();
 #endif
				break;
#endif
			default:
				NackBuzzer();
				break;
			}
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

UBYTE MainCheckerFunctionTest(void)
{
	UBYTE	step,key,keytype,rtn;

	rtn = FALSE;

	for(step = 1; step <= 8; step++){
#if defined (KEISATSU) /* 警察FAX 05/10/05 石橋正和 */
		if (step == OPR_HOLDMELODY_TEST) {
			step++;
		}
#endif
		switch(step){
		case OPR_BELLRING_TEST:				/*　擬似ベル鳴動　*/
			ClearDisplayHigh();
			ClearDisplayLow();
			
			CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"# ｷﾞｼﾞﾍﾞﾙｻｲｾｲ ﾃｽﾄ  #");
			DisplayStringHigh(0,FunctionDisplayBufferHigh);
			CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"#  ｷﾞｼﾞﾍﾞﾙ ﾃｽﾄﾁｭｳ  #");
			DisplayStringLow(0,FunctionDisplayBufferLow);        

			rtn = GenerateRingTest();
			DisplayStringLow(0, OPR_TestCompleteWord);
			break;

		case OPR_HOLDMELODY_TEST:			/*　保留メロデイー　*/
			ClearDisplayHigh();
			ClearDisplayLow();
			
			CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"#  ﾎﾘｭｳﾒﾛﾀﾞｲｰ ﾃｽﾄ  #");
			DisplayStringHigh(0,FunctionDisplayBufferHigh);
			CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"# ﾎﾘｭｳﾒﾛﾃﾞｲｰﾃｽﾄﾁｭｳ #");
			DisplayStringLow(0, FunctionDisplayBufferLow); 
			rtn = HoldMelody_Test();
			DisplayStringLow(0, OPR_TestCompleteWord);
			break;
			
		case OPR_ALLCLEAR_TEST:				/*　オールクリア　*/
			RTCTestEnd();
			
			CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"#    ｵｰﾙｸﾘｱ ﾃｽﾄ    #");
			DisplayStringHigh(0,FunctionDisplayBufferHigh);
			rtn = AllClear_Test();
			
			RTCTestStart();	
			break;
		case OPR_DRAM_TEST:					/*　標準ＤＲＡＭ　*/
			CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"#     DRAM ﾃｽﾄ     #");
			DisplayStringHigh(0,FunctionDisplayBufferHigh);
			rtn = DRAMCheck_Test();
			break;
		case OPR_SRAM_TEST:					/*　ＳＤＡＭ　*/
			CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"#     SRAM ﾃｽﾄ     #");
			DisplayStringHigh(0,FunctionDisplayBufferHigh);
			rtn = SRAMCheck_Test();
			break;
		case OPR_TESTPATTERNPRINT_TEST:		/*　テストパダーン印字　*/
			CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"#   ﾃｽﾄﾊﾟﾀｰﾝ ﾃｽﾄ   #");
			DisplayStringHigh(0,FunctionDisplayBufferHigh);
			rtn = TestPatternOperation_Test();
			break;
		case OPR_LISTPRINT_TEST:			/*　リストプリント印字　*/
			CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"#   ﾘｽﾄﾌﾟﾘﾝﾄ ﾃｽﾄ   #");
			DisplayStringHigh(0,FunctionDisplayBufferHigh);
			rtn = ListPrint_Test();
			break;
		case OPR_SHADING_TEST:				/*　シューデイング　*/
			CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"#  ｼｪｰﾃﾞｲﾝｸﾞ ﾃｽﾄ   #");
			DisplayStringHigh(0,FunctionDisplayBufferHigh);
			CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"# ｼｪｰﾃﾞｲﾝｸﾞ ﾃｽﾄﾁｭｳ #");
			DisplayStringLow(0,FunctionDisplayBufferLow);
			SF_ShadingOperation();
			CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ｼｪｰﾃﾞｲﾝｸﾞ ｹｯｶ:OK  ");
			DisplayStringLow(0,FunctionDisplayBufferLow);

			break;
		}

		if( rtn == TRUE ){
			OPR_GetKey(KEY_WAIT_2_SECOND);	/* キー取り込み */
			key = GetInputKeyCode();
			keytype = GetInputKeyType();
			
			switch (keytype) {
			case STOP:
				return FALSE;
			case KEY_TIME_UP:
				break;

			case NO_EFFECT:
				break;
			default:
				NackBuzzer();
				break;
			}
		}
		else{
			while(1){
				NackBuzzer();
				
				OPR_GetKey(KEY_WAIT_FEW_TIME);	/* キー取り込み */
				key = GetInputKeyCode();
				keytype = GetInputKeyType();
				
				switch (keytype) {
				case COPY:
					wai_tsk(200);
					RestartSystem();
					return;
				case KEY_TIME_UP:
					break;

				case NO_EFFECT:
					break;
				default:
					NackBuzzer();
					break;
				}
			}
		}

	}
	
	RTCTestEnd();

	wai_tsk(300);
	
	RelayPortStatus &= 0xcfff;
	MonitorSpeakerOff();

	MonitorSpeakerOn();
	SYB_MonitorSpeakerOutLevel = SYS_VOLUME_MAXIMUM;	/* ボリューム最大に設定 */
	MonitorSpeakerVolumeControl();
	SpeakerMuteOff();

	EndBuzzer();
	
	wai_tsk(300);
	
	StopEndBuzzer();
	
	RelayPortStatus &= 0xcfff;
	MonitorSpeakerOff();
	
	return TRUE;
}

UBYTE GenerateRingTest()
{
	WORD	counter;
	WORD	time_counter;
	UBYTE	GRS_Tel1OhCounter;
	UBYTE	GRS_Tel2OhCounter;
	
	GRS_Tel1OhCounter				 =	0;
	GRS_Tel2OhCounter				 =	0;

#if !defined(HINOKI3)		/* HINOKI3ではスピーカー音量をソフトで制御出来ない為、省きます。by Y.Kano 2004/12/22 */
	RelayPortStatus |= IO_BIT_SP_VOLMX;
	OutputWORD(GA_PGADR, RelayPortStatus);
#endif

	GenerateRingStartRelayControl();

	/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Jun,03,1995 *//* By M.Tachibana 1997/10/17 */
	if (!CHK_UNI_NoRingTel2Detachable()) {
		GenerateRingKeyOn();
		wai_tsk( 3 );
	}

	for (time_counter = 0; time_counter < 3; time_counter++) { /* ３秒間 */
		/*-----------------------------------*/
		/** 疑似ベル・呼出ブザー ＯＦＦ期間  */
		/*-----------------------------------*/
		counter = 0;
		while ((counter                  <  15						)
		&&     (GRS_Tel1OhCounter        <  GENERAL_RING_OFF_HOOK_MAX)
		&&     (GRS_Tel2OhCounter        <  GENERAL_RING_OFF_HOOK_MAX)) {
			/*-----------------------------------*/
			/** 付属／外付電話のＯＨ情報の取込み */
			/*-----------------------------------*/
			OhPortStatusRead();

			if (OhPortStatus  & (TEL1_OFF_HOOK | TEL2_OFF_HOOK)) {
				if (OhPortStatus & TEL1_OFF_HOOK) {
					GRS_Tel1OhCounter++;
				}
				else {
					GRS_Tel1OhCounter = 0;
				}
				if (OhPortStatus & TEL2_OFF_HOOK) {
					GRS_Tel2OhCounter++;
				}
				else {
					GRS_Tel2OhCounter = 0;
				}
			}
			wai_tsk( 6 );
			counter++;
		}

		/*--------------------------------*/
		/** 疑似ベル・呼出ブザーＯＮ期間  */
		/*--------------------------------*/
		counter = 0;
		while ((counter                    <  12                       )
		&&     (GRS_Tel1OhCounter          <  GENERAL_RING_OFF_HOOK_MAX)
		&&     (GRS_Tel2OhCounter          <  GENERAL_RING_OFF_HOOK_MAX)) {
			/*-----------------------------------*/
			/** 付属／外付電話のＯＨ情報の取込み */
			/*-----------------------------------*/
			OhPortStatusRead();
			if (OhPortStatus  & (TEL1_OFF_HOOK | TEL2_OFF_HOOK)) {
				if (OhPortStatus & TEL1_OFF_HOOK) {
					GRS_Tel1OhCounter++;
				}
				else {
					GRS_Tel1OhCounter = 0;
				}
				if (OhPortStatus &  TEL2_OFF_HOOK) {
					GRS_Tel2OhCounter++;
				}
				else {
					GRS_Tel2OhCounter = 0;
				}
				
				/*GRB_RingAndBellOn();*/
				
				/*-------------------------------------------------*/
				/** 疑似ベルＯＦＦ・呼出ブザーＯＮ（１６Ｈｚ変調） */
				/*-------------------------------------------------*/
				BuzzerOnSetting(SYS_SPK_OUT_FAKERINGER);
				bell_on(); /* by H.Hirao 1999/01/30 */
				GenerateRingKeyOff();
				wai_tsk(3);

				/*-------------------------------------------------*/
				/** 疑似ベルＯＮ・呼出ブザーＯＦＦ（１６Ｈｚ変調） */
				/*-------------------------------------------------*/
				/*--------------------------*/
				/** 呼出ブザー周波数の設定  */
				/*--------------------------*/
				SCN_SetBuzzerFrequency(VOICE_ALARM_FREQ);
				BuzzerOffSetting(SYS_SPK_OUT_FAKERINGER);
				bell_off(); /* by H.Hirao 1999/01/30 */
				GenerateRingKeyOn();
				wai_tsk(3);
			}
			else {
				/*-----------------------------*/
				/**  疑似ベル・呼出ブザーＯＮ  */
				/*-----------------------------*/
				GRS_Tel1OhCounter   = 0;
				GRS_Tel2OhCounter   = 0;

				/*GRB_RingAndBellOn();*/

				/*-------------------------------------------------*/
				/** 疑似ベルＯＦＦ・呼出ブザーＯＮ（１６Ｈｚ変調） */
				/*-------------------------------------------------*/
				BuzzerOnSetting(SYS_SPK_OUT_FAKERINGER);
				bell_on(); /* by H.Hirao 1999/01/30 */
				GenerateRingKeyOff();
				wai_tsk(3);

				/*-------------------------------------------------*/
				/** 疑似ベルＯＮ・呼出ブザーＯＦＦ（１６Ｈｚ変調） */
				/*-------------------------------------------------*/
				/*--------------------------*/
				/** 呼出ブザー周波数の設定  */
				/*--------------------------*/
				SCN_SetBuzzerFrequency(VOICE_ALARM_FREQ);
				BuzzerOffSetting(SYS_SPK_OUT_FAKERINGER);
				bell_off(); /* by H.Hirao 1999/01/30 */
				GenerateRingKeyOn();
				wai_tsk(3);
			}
			counter++;
		}
	}

	/*--------------------*/
	/** 呼出ブザーＯＦＦ  */
	/*--------------------*/
	BuzzerOffSetting(SYS_SPK_OUT_FAKERINGER);
	SCN_SetBuzzer(SCN_DISABLE);
	/*---------------*/
	/** 疑似ベル OFF */
	/*---------------*/
	GenerateRingKeyOff();

	GenerateRingEndRelayControl();/* 94/11/18 Y.Suzuki */

	wai_tsk( 300 );

	return TRUE;
}

UBYTE HoldMelody_Test(void)
{
	RelayPortStatus &= 0xcfff;

	MonitorSpeakerOn();
	SpeakerMuteOff();
#if !defined(HINOKI3)		/* HINOKI3ではスピーカー音量をソフトで制御出来ない為、省きます。by Y.Kano 2004/12/22 */
	RelayPortStatus |= IO_BIT_SP_VOLMX;
#endif
	RelayPortStatus |= IO_BIT_SELMEL;
	OutputWORD(GA_PGADR, RelayPortStatus);

	SCN_SetBuzzer(SCN_ENABLE);						/** ブザー許可 */

	/*	wai_tsk(300);	*/
	wai_tsk(500);		/* Modify by SMuratec K.W.Q 2003/10/27 */
	
	RelayPortStatus &= 0xcfff;
	MonitorSpeakerOff();
	RelayPortStatus &= ~IO_BIT_SELMEL;
	
	return TRUE;
}

UBYTE AllClear_Test(void)
{
	TIME_DATA_t		bcd_time;		/* サマータイム用 */
	UDWORD			long_time;		/* サマータイム用 */

	CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"#  ｵｰﾙｸﾘｱ ﾃｽﾄﾁｭｳ   #");
	DisplayStringLow(0,FunctionDisplayBufferLow);

	wai_tsk(100);

	CMN_LongTimeToBCD(&bcd_time, SYB_CurrentTime); /* サマータイム用 */

	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & ~SYS_PANEL_BUSY) {	/** 機器動作中 */
		NackBuzzer();
		
		CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"   ｵｰﾙｸﾘｱ ｹｯｶ:NG    ");
		DisplayStringLow(0,FunctionDisplayBufferLow);

		return( NG );
	}

	CMN_InitializeAllBackUpRAM(0);		/** 機器パラメータ、オールラム		*/
	CMN_ClearConsumerOrderData();		/** 消耗品発注データのクリア		*/
	CMN_ClearLifeMonitorData();			/** ライフモニタークリア			*/
	CMN_ClearFaxComErrorMonitorData();	/** 通信エラーモニタークリア		*/
	CMN_ClearJournalData();				/** ジャーナルデータクリア			*/

	InitializeDRAM_Parameter();									/** ＤＲＡＭ領域を初期化		*/
	InitializeMachineStatus();									/** マシーンステータスのクリア	*/
	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
	SYS_ErasePixMemoryListRequest = 0;							/** 停電発生初期化				*/
	Init_AnyList(LST_POWEROFF_NOTICE);							/** 停電ステータスのクリア		*/
	InitializeSensor();											/** センサーを初期化			*/

	/* サマータイムのための処理 */
	if (bcd_time.Year == CurrentTimeInBCD.Year) {
		long_time = CMN_BCD_TimeToLong(&CurrentTimeInBCD);
		SetSummerTimeStatus(long_time);
	}

#if defined (KEISATSU) /* 警察FAX 05/12/05 石橋正和 */
	SetKeisatsuSettings();
	AttributeTimeoutCheck = 0;
	NCU_HdstShift();
#endif

	CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"   ｵｰﾙｸﾘｱ ｹｯｶ:OK    ");
	DisplayStringLow(0,FunctionDisplayBufferLow);
	
	return( OK );
}

UBYTE DRAMCheck_Test(void)
{
	CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"# DRAMCheck ﾃｽﾄﾁｭｳ #");
	DisplayStringLow(0,FunctionDisplayBufferLow);

	wai_tsk(100);

	/**	割り込み禁止	*/
	CMN_DisableInterrupt();

	if ( DRAMCheck() == NG ) {					/** DRAMチェック */
		NackBuzzer();

		return( NG );
	}

	InitializeDRAM_Parameter();									/** ＤＲＡＭ領域を初期化		*/
	InitializeMachineStatus();									/** マシーンステータスのクリア	*/
	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
	SYS_ErasePixMemoryListRequest = 0;							/** 停電発生初期化				*/
	Init_AnyList(LST_POWEROFF_NOTICE);							/** 停電ステータスのクリア		*/
#if defined (KEISATSU) /* 警察FAX 05/12/05 石橋正和 */
	InitializeSensor();											/** センサーを初期化			*/
	/* チェッカー終了後、背面Sスイッチの出力表示がOFFになる不具合の対策 */
#endif
	CMN_EnableInterrupt();										/** 割り込み許可				*/

	return( OK );
}

UBYTE DRAMCheck(void)
{
	UBYTE	loop;
	UBYTE	loopt;
	UBYTE	size;				/* 拡張サイズ（Ｍ） */
	UBYTE	dram_chk[9];		/* DRAM状態格納ﾊﾞｯﾌｧ( OK or NG )*/
	UWORD	*DRAM_CheckAddress;	/* 拡張アドレス先頭 */
	UWORD	*addr;				/* データ書込み、読出しアドレス */
	UWORD	data;

	CMN_MemorySet(dram_chk, 9, 0xFF);
	CMN_MemorySetNULL(FunctionDisplayBufferLow,  OPR_DISPLAY_MAX, ' ');				/* 下段表示文字列を初期化 */

	size	= 2;

	for( loop = 0; loop < size; loop += 2 ){		/* 拡張ＤＲＡＭ分 */
		DRAM_CheckAddress = (UWORD *)(MEM_DRAM_START_ADDRESS + ( 0x00100000L * loop ));	/* 各先頭アドレスセット */
		/* 書込み */
		for( loopt = 0; loopt < 10; loopt++ ){		/* テスト件数分 */
			switch( loopt ){						/* テストデータ書込み */
			case	0:
				addr	= DRAM_CheckAddress;
				data	= 0x0000;
				break;
			case	8:
			case	9:
				addr	= (UWORD *)((UDWORD)DRAM_CheckAddress + (0x0001 << loopt));
				data	= (0x5555 << (loopt - 8));
				break;
			default:
				addr	= (UWORD *)((UDWORD)DRAM_CheckAddress + (0x0001 << loopt));
				data	= (0x0101 << loopt);
				break;
			}
			*addr	= data;
		}

		for( loopt = 0; loopt < 10; loopt++ ){	/* テスト件数分 */
			switch( loopt ){					/* テストデータ書込み */
			case	0:
				addr	= DRAM_CheckAddress;
				data	= 0x0000;
				break;
			case	8:
			case	9:
				addr	= (UWORD *)((UDWORD)DRAM_CheckAddress + (0x0001 << loopt));
				data	= (0x5555 << (loopt - 8));
				break;
			default:
				addr	= (UWORD *)((UDWORD)DRAM_CheckAddress + (0x0001 << loopt));
				data	=(0x0101 << loopt);
				break;
			}
			if( *(addr) != data ){
				CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"DRAM ｹｯｶ:NG,        ");
				/* エラーアドレスを表示 */
				CMN_UnsignedLongToHexASC_NULL(&FunctionDisplayBufferLow[12], (UDWORD)(*addr), 6, ' ');
				
				DisplayStringLow(0,FunctionDisplayBufferLow);

				return( NG );
			}
		}
	}
	CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  DRAMCheck ｹｯｶ:OK  ");
	DisplayStringLow(0,FunctionDisplayBufferLow);

	return( OK );
} 

UBYTE SRAMCheck_Test(void)
{
	UBYTE	hexcode;				/* ＨＥＸコード */
	UBYTE	*SRAM_StartAddress;		/* 検査開始アドレス */
	UBYTE	*SRAM_EndAddress;		/* 検査終了アドレス */
	UBYTE	check_step;				/* 検査ｱﾄﾞﾚｽ指定変数 */
	UBYTE	ram_check;				/* ﾃｽﾄ状態(0:ﾁｪｯｸ中,1:ﾁｪｯｸ終了) */
	UBYTE	error_check;			/* エラーチェック変数 */

	check_step = 0;
	hexcode = 0xFF;
	ram_check = 0;
	error_check = 0;

	CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"# SRAMCheck ﾃｽﾄﾁｭｳ #");
	DisplayStringLow(0,FunctionDisplayBufferLow);

	wai_tsk(100);

	/**	割り込み禁止	*/
	CMN_DisableInterrupt();

	while (ram_check == 0) {

		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
		ClearDisplayLow();
		CMN_HexToASC(&FunctionDisplayBufferLow[0], (UDWORD)hexcode, 2);
		FunctionDisplayBufferLow[2]  = ':';

		if (error_check == 0) {			/* エラーの時にｱﾄﾞﾚｽを初期化しないため */
			switch ( check_step ) {
			case 0:
				SRAM_StartAddress = (UBYTE *)0x00800000L;
				SRAM_EndAddress = (UBYTE *)0x00807FFFL;
				break;
			case 1:
				SRAM_StartAddress = (UBYTE *)0x00D00000L;
				SRAM_EndAddress = (UBYTE *)0x00D1FFFFL;
				break;
			}
		}

		if (SRAMCheck(hexcode, &SRAM_StartAddress, SRAM_EndAddress) == 0) {  		/* SRAMチェックで異常の時 */
			error_check = 1;
			NackBuzzer();
		
			CMN_EnableInterrupt();										/** 割り込み許可				*/
			
			return( NG );
		}
		else {
			if (check_step == 0){
				check_step = 1;
			}
			else {
				if ( hexcode == 0x00 ) {	/* 全ての検査が終了した時 */
					ram_check = 1;

					CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  SRAMCheck ｹｯｶ:OK  ");
					DisplayStringLow(0,FunctionDisplayBufferLow);
				}
				else {
					hexcode -= 0x55;
					check_step = 0;
					error_check = 0;
				}
				wai_tsk(200);	/* 400->200 1997/12/25 Y.Matsukuma */
			}
		}
	}

	CMN_EnableInterrupt();										/** 割り込み許可				*/

	return( OK );
}

UBYTE SRAMCheck(UBYTE Code, UBYTE *(*StartAddress), UBYTE *LimitAddress)
{
	UBYTE	EscapeMemory;

	/*	ＳＲＡＭ書き込み、読み出し、比較	*/
	for (; (UDWORD)(*StartAddress) <= (UDWORD)(LimitAddress); (*StartAddress)++) {	/** 終了アドレスまでループ */
		EscapeMemory = *(*StartAddress);			/** データの退避 */
		*(*StartAddress) = Code;					/** テストコードの書き込み */
		if (*(*StartAddress) != Code) {				/** 比較の結果、NGの場合 97/10/15 By M.Kuwahara */
			*(*StartAddress) = EscapeMemory;		/** 退避したデータの書き戻し */
			
			CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"SRAM ｹｯｶ:NG,        ");
			/* エラーアドレスを表示 */
			CMN_UnsignedLongToHexASC_NULL(&FunctionDisplayBufferLow[12], (UDWORD)(*StartAddress), 6, ' ');
			DisplayStringLow(0,FunctionDisplayBufferLow);

			(*StartAddress)++;
			return(0);			/** NGリターン */
		}
		*(*StartAddress) = EscapeMemory;	/** 退避したデータの書き戻し */
	}

	return(1);					/** OKリターン */
}

UBYTE TestPatternOperation_Test(void)
{
	CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"# ﾃｽﾄﾊﾟﾀｰﾝ ﾃｽﾄﾁｭｳ  #");
	DisplayStringLow(0,FunctionDisplayBufferLow);

	wai_tsk(100);

	if (CheckPrintOperationEnable()) {

		ClearDisplayLow();
		DisplayStringLow(0 , D2W_Printing);

		/* if( PrintKoushiPattern() ){*/
		if( PrintLinePattern() ){		/* Modify by SMuratec K.W.Q 2003/10/27 */
			ClearDisplayLow();
			CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ﾃｽﾄﾊﾟﾀｰﾝ ｹｯｶ:OK   ");
			DisplayStringLow(0,FunctionDisplayBufferLow);
			
			return( OK );
		}
		else{
			PRN_CheckPrinterError();

			if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {
				ClearDisplayLow();
				CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ｹｯｶ: No Paper     ");
				DisplayStringLow(0,FunctionDisplayBufferLow);
				return( NG );
			}
			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM) {
				ClearDisplayLow();
				CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ｹｯｶ: ﾍﾟｰﾊﾟｰｼﾞｬﾑ   ");
				DisplayStringLow(0,FunctionDisplayBufferLow);
				return( NG );
			}
			if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
				ClearDisplayLow();
				CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ｹｯｶ: ｶﾊﾞｰｵｰﾌﾟﾝ    ");
				DisplayStringLow(0,FunctionDisplayBufferLow);
				return( NG );
			}
			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] &SYS_PRINTER_CUTTER_ERROR) {
				ClearDisplayLow();
				CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ｹｯｶ: ｶｯﾀｰｴﾗｰ      ");
				DisplayStringLow(0,FunctionDisplayBufferLow);
				return( NG );
			}

			return( NG );
		}
	}
	else{
		ClearDisplayLow();
		CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ﾃｽﾄﾊﾟﾀｰﾝ ｹｯｶ:NG   ");
		DisplayStringLow(0,FunctionDisplayBufferLow);
		
		return( NG );
	}

}

UBYTE ListPrint_Test(void)
{
	CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"# ﾘｽﾄﾌﾟﾘﾝﾄ ﾃｽﾄﾁｭｳ  #");
	DisplayStringLow(0,FunctionDisplayBufferLow);

	wai_tsk(100);

	if (CheckPrintOperationEnable()) {
		DisplayStringLow(0 , D2W_Printing);

		if( Print_Function_List() ){
			ClearDisplayLow();
			CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ﾘｽﾄﾌﾟﾘﾝﾄ ｹｯｶ:OK   ");
			DisplayStringLow(0,FunctionDisplayBufferLow);
			
			return( OK );
		}
		else{
			PRN_CheckPrinterError();

			if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {
				ClearDisplayLow();
				CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ｹｯｶ: No Paper     ");
				DisplayStringLow(0,FunctionDisplayBufferLow);
				return( NG );
			}
			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM) {
				ClearDisplayLow();
				CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ｹｯｶ: ﾍﾟｰﾊﾟｰｼﾞｬﾑ   ");
				DisplayStringLow(0,FunctionDisplayBufferLow);
				return( NG );
			}
			if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
				ClearDisplayLow();
				CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ｹｯｶ: ｶﾊﾞｰｵｰﾌﾟﾝ    ");
				DisplayStringLow(0,FunctionDisplayBufferLow);
				return( NG );
			}
			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] &SYS_PRINTER_CUTTER_ERROR) {
				ClearDisplayLow();
				CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ｹｯｶ: ｶｯﾀｰｴﾗｰ      ");
				DisplayStringLow(0,FunctionDisplayBufferLow);
				return( NG );
			}
		}
	}
	else{
		ClearDisplayLow();
		CMN_StringCopy(FunctionDisplayBufferLow, (UBYTE *)"  ﾘｽﾄﾌﾟﾘﾝﾄ ｹｯｶ:NG   ");
		DisplayStringLow(0,FunctionDisplayBufferLow);
		
		return( NG );
	}
}
#endif	/* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) defined(HINOKI3) */
