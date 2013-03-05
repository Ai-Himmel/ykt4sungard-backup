/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA	  ANZUを移植									 */
/*	ファイル名	 : FCM_COST.C												 */
/*	モジュール	 :															 */
/*				 : FCM_GetCostTable()										 */
/*				 : FCM_CostCalculate()										 */
/*				 : SetCost()												 */
/*				 : CheckCostZone()											 */
/*				 : CalculateFirstCostTime()									 */
/*				 : CalculateCostTime()										 */
/*				 : CheckCostTable()											 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : 料金管理													 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#if (PRO_MULTI_LINE == ENABLE)
#include "\src\atlanta\define\dpr_pro.h"
#endif
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
/*#include "\src\memsw\define\mem_sw.h" @*1996/04/17 Eguchi*/
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\syscost.h"	/* For SYB_NTT_AccessFile[] 25.Aug'94 Y.Suzuki */
#include "\src\atlanta\define\uni_pro.h"	/* Add By O.Kimoto 1997/11/13 */

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\fcm_def.h" /* Added by H.Kubo 1997/06/30 */
#include "\src\atlanta\ext_v\fcm_data.h"

#if (PRO_MULTI_LINE == ENABLE)	/* 1997/09/17 */
#include "\src\atlanta\define\mlt_pro.h"
#include "\src\atlanta\ext_v\mlt_data.h"	/* 1997/09/19 s.takeuchi */
#endif


/* このファイルは、料金管理ありの場合のみ有効 */
#if(PRO_COST == ENABLE)

#define			NOON		0
#define			NIGHT		1
#define			MID_NIGHT	2
/*************************************************************************
	module		:[電話番号列から料金表の配列オフセット値の獲得]
	function	:[
		1.
	]
	return		:[
		1.SYB_CostTable[]の配列オフセット値
		2.0の場合は市内通話となる
		3.0xFF
	]
	common		:[]
	condition	:[]
	comment		:[
		マルチ回線(同時実行)対応のため引数追加  1997/09/19 s.takeuchi
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1994/06/27]
	author		:[吉川弘康]
*************************************************************************/
UBYTE FCM_GetCostTable(UBYTE *dialbuf_ptr, UWORD exec_no)
{
	UBYTE tbl_pos;
	UBYTE *access_ptr;		/* 外線接続番号をスキップし、局番がある（無い事もあるが）先頭のポインタ */
	UBYTE *buf_ptr;
	UBYTE *cmp_ptr;
	unsigned char is_pbx;		/* 1997/09/20 s.takeuchi */
#if (PRO_MULTI_LINE == ENABLE)	/* 1997/09/17 */
	unsigned char none_dial_buffer[1];
#endif

	/* 1997/09/20 s.takeuchi */
	/** 標準仕様の外線接続番号(機能 * 7)が登録済みなら内線に接続されているとする */
	if (SYB_PBX_Number[0] != NULL) {
		is_pbx = 1;
	}
	else {
		is_pbx = 0;
	}

	/******************************************************/
	/* 外線接続番号との比較し、ダイヤルバッファのスキップ */
	/******************************************************/
	cmp_ptr = &SYB_PBX_Number[0];
#if (PRO_MULTI_LINE == ENABLE)
 #if (PRO_G4 == DISABLE)
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/12 */
	none_dial_buffer[0] = NULL;
	cmp_ptr = &none_dial_buffer[0];

	/** 内線設定の回線で外線アクセスしない時は内線通話なので料金計算しない */
	if (SYB_ExecQueue[exec_no].StackNumber == 0) {
		if ((SYS_InternalLineNumber == SYS_STD_LINE_COM)	/**	標準ライン通信中	*/
		&&  (OPT_CHK_Pbx(SYB_ExecQueue[exec_no].StackNumber))
		&&  (SYB_ExecQueue[exec_no].Option & SYS_PSTN_ACCESS_ENABLE)) {
			is_pbx = 1;		/* 内線 */
			return(0xFF);
		}
		else if ((SYS_InternalLineNumber == SYS_EXT_LINE_COM)	/**	拡張ライン通信中	*/
		&&  (CHK_PBX_EXT())
		&&	(SYB_ExecQueue[exec_no].Option & SYS_PSTN_ACCESS_ENABLE)) {
			is_pbx = 1;		/* 内線 */
			return(0xFF);
		}
		else {
			is_pbx = 0;		/* 外線 */
		}
	}
	else {
		if (OPT_CHK_Pbx(SYB_ExecQueue[exec_no].StackNumber)
		&&	(SYB_ExecQueue[exec_no].Option & SYS_PSTN_ACCESS_ENABLE)) {
			is_pbx = 1;		/* 内線 */
			return(0xFF);
		}
		else {
			is_pbx = 0;		/* 外線 */
		}
	}
#else
	if (OPT_CountModems() > 1) {
		none_dial_buffer[0] = NULL;
		cmp_ptr = &none_dial_buffer[0];

		/** 内線設定の回線で外線アクセスしない時は内線通話なので料金計算しない */
		if (OPT_CHK_Pbx(SYB_ExecQueue[exec_no].StackNumber)
		&&	(SYB_ExecQueue[exec_no].Option & SYS_PSTN_ACCESS_ENABLE)) {
			is_pbx = 1;		/* 内線 */
			return(0xFF);
		}
		else {
			is_pbx = 0;		/* 外線 */
		}
	}
#endif
 #endif
#endif
	access_ptr = dialbuf_ptr;

	for (; *cmp_ptr != NULL; cmp_ptr ++, access_ptr ++) {
		if (*cmp_ptr != *access_ptr) {
			access_ptr = dialbuf_ptr;
			break;
		}
	}

	/* 1997/09/18 s.takeuchi */
	/** 標準仕様の外線接続番号が登録されていて、全桁一致しなかった場合は内線番号とみなす */
	if (is_pbx
	&&	(*cmp_ptr != NULL)) {
		return(0xFF);
	}

	/*---------------------------------------------------------------------
	** ＩＣＨＯＵでは、ＯＰＲで、「！」、「－／」の入力ができなくなったので
	** 先頭に０～９以外がある場合はスキップします。
	** 1997/09/17
	*/
	for (; *access_ptr != NULL; access_ptr ++) {
		if ((*access_ptr >= '0') && (*access_ptr <= '9')) {
			break;
		}
	}
	if (*access_ptr == NULL) {
		return(0xFF);			/* 料金計算しない */
	}

	/********************/
	/* 登録局番との比較 */
	/********************/
	if (*access_ptr != '0') {	/** 局番なしなら */
		/* By H.Y 1994/12/01 3Lines */
		if (SYB_NTT_AccessFile[0].Number[0] == 0xFF) {
			return(0xFF);
		} else {
			return(0);				/** 市内通話と判断 */
		}
	}

	for (tbl_pos = 1; tbl_pos < (SYS_SPEED_DIAL_MAX + SYS_ONETOUCH_MAX ); tbl_pos ++) {
		cmp_ptr = &SYB_NTT_AccessFile[tbl_pos].Number[0];
		/*-----------------------------------------------------------------
		** SYS_NTT_AccessFile[]の登録データは歯抜けになることがあります。
		** 歯抜け状態であっても、すべてのデータを検索するようにします。
		** 登録済みデータを削除すると、削除したテーブルが歯抜け状態となります。
		** 1999/04/21 H.Yoshikawa
		*/
		if (*cmp_ptr != 0xFF) {
			for (buf_ptr = access_ptr; *cmp_ptr != NULL; buf_ptr ++, cmp_ptr ++) {
				if (*buf_ptr != *cmp_ptr) {
					break;
				}
			}
			if (*cmp_ptr == NULL) {
				return(tbl_pos);
			}
		}
		
#if (0)	/* 1999/04/21 H.Yoshikawa */
//		if (*cmp_ptr == 0xFF) {
//			/* 局番なしのため、市内電話番号とする */
//			return(0xFF);	/* By H.Y 1994/10/27 */
//		}
//
//		for (buf_ptr = access_ptr; *cmp_ptr != NULL; buf_ptr ++, cmp_ptr ++) {
//			if (*buf_ptr != *cmp_ptr) {
//				break;
//			}
//		}
//		if (*cmp_ptr == NULL) {
//			return(tbl_pos);
//		}
#endif
	}
	/*-----------------------------------------------------------------
	** SYS_NTT_AccessFile[]にすべてデータが登録されているが、
	** 一致するものがない場合には、戻り値が定義されていない。
	** 検索不一致(0xFF)を戻り値にします。
	** 1999/04/21 H.Yoshikawa
	*/
	return(0xFF);
}

/*************************************************************************
	module		:[通話料金計算]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1994/08/12]
	author		:[奥村明]
*************************************************************************/
void	FCM_CostCalculate(UWORD		depart_code			/*	料金をセットする部門コード	*/
								, UBYTE	cost_pos			/*	料金テーブルの配列オフセット値	*/
								, UBYTE	stack_no)		/* スタック番号 *//* 追加  1997/09/19 s.takeuchi */
{
	UWORD	cost_time;											/**	同一料金時間	*/
	UWORD	rest_time;											/**	通信時間から料金計算した時間を差し引いた残り時間	*/
	UBYTE	cost_zone;											/**	料金帯（昼、夜、深夜）	*/
	TIME_DATA_t	start_time;												/**	通信開始時間(struct型BCD)	*/
	unsigned long	fcm_start_time;		/**	通信の開始時刻 *//* 1997/09/19 s.takeuchi */

	/* マルチ回線と共通にするため  1997/09/19 s.takeuchi */
	if (stack_no == 0) {	/** 1回線目(内蔵) */
		/* 標準仕様では従来通りFCM_Task用の大域変数を使う */
		/* マルチ回線仕様でも1回線目は従来の変数を使う */
		fcm_start_time = FaxComStartTime;	/** 通信開始時刻 */
		rest_time = FaxComPeriod;			/**	通信時間	*/
	}
#if (PRO_MULTI_LINE == ENABLE)
	else {		/** 二回線目以降(外付) */
		/* マルチ回線仕様では回線ごとにセットされている変数を使う */
		fcm_start_time = SYS_OptionModemTime[stack_no].StartTime;			/** 通信開始時刻 */
		rest_time = (UWORD)(SYS_OptionModemTime[stack_no].EndTime
							- SYS_OptionModemTime[stack_no].StartTime);		/**	通信時間	*/
	}
#endif

	/* マルチ回線と共通にするため  1997/09/19 s.takeuchi
	**CMN_LongTimeToBCD((TIME_DATA_t *)&start_time, FaxComStartTime);
	*/
	CMN_LongTimeToBCD((TIME_DATA_t *)&start_time, fcm_start_time);	/**	通信開始時間をstruct型BCDに変換	*/


	cost_zone = CheckCostZone(CMN_BCD_ToDecimal(start_time.Hour));		/**	通信開始時間が昼、夜、深夜のどの料金帯で始まったかを調べる	*/

	cost_time = CalculateFirstCostTime(&start_time);					/**	通信開始時の料金帯から次の料金帯までの時間（秒）を得る	*/

	for (;;) {
		if (cost_time < rest_time) {									/**	次の料金変更までの時間が残り通信時間より小さい時	*/
			SetCost(cost_time, cost_zone, cost_pos, depart_code);		/**	料金を管理ファイルにセットする	*/
			rest_time -= cost_time;										/**	残り（料金計算していない）通信時間	*/
			if (cost_zone++ == MID_NIGHT) {
				cost_zone = NOON;
			}
		}
		else {
			SetCost(rest_time, cost_zone, cost_pos, depart_code);		/**	料金を管理ファイルにセットする	*/
			return;
		}
		cost_time = CalculateCostTime(cost_zone);						/**	同一料金帯の時間（秒）を得る	*/
	}
}

/*************************************************************************
	module		:[料金セット]
	function	:[
		1.	計算した料金を管理ファイルにセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1994/08/12]
	author		:[奥村明]
*************************************************************************/
void	SetCost(UWORD		transmit_time				/*	同一料金帯の通信時間（秒）	*/
					  , UBYTE		cost_zone					/*	料金帯	*/
					  , UBYTE		cost_pos					/*	料金テーブルの配列オフセット値	*/
					  , UWORD		depart_code					/*	料金をセットする部門コード	*/
					  )
{
	UWORD	time;
	UBYTE	loop;

	switch (cost_zone) {
	case	NOON:
/*		time = SYB_CostTable[cost_pos].Daytime / 10;	94/12/8 by A.O 小数点以下の値が切り捨てされる為*/
		time = SYB_CostTable[cost_pos].Daytime;
		break;
	case	NIGHT:
/*		time = SYB_CostTable[cost_pos].Night / 10;		94/12/8 by A.O 小数点以下の値が切り捨てされる為*/
		time = SYB_CostTable[cost_pos].Night;
		break;
	case	MID_NIGHT:
/*		time = SYB_CostTable[cost_pos].Midnight / 10;	94/12/8 by A.O 小数点以下の値が切り捨てされる為*/
		time = SYB_CostTable[cost_pos].Midnight;
		break;
	}
	if (time == 0) {
		return;
	}

	for (loop = 0; loop < SYS_DEPART_MAX ; loop++) {
		if (SYB_DepartFile[loop].Code == depart_code) {
			CMN_DisableInterrupt();		/* マルチ回線(同時実行)対応  1997/09/19 s.takeuchi */
/*			SYB_DepartFile[loop].Cost
			+= (UBYTE)((UDWORD)(transmit_time - 1)/time*SYS_MemorySwitch[MEMORY_SW_I8] + SYS_MemorySwitch[MEMORY_SW_I8]);	**	料金セット	94/12/8 by A.O 小数点以下の値が切り捨てされる為*/
			SYB_DepartFile[loop].Cost
			+= (UDWORD)((UDWORD)(transmit_time - 1)*10/time*CHK_BaseCostInCostTable() + CHK_BaseCostInCostTable());
			CMN_EnableInterrupt();		/* マルチ回線(同時実行)対応  1997/09/19 s.takeuchi */
			break;
		}
	}
}

/*************************************************************************
	module		:[料金帯獲得]
	function	:[
		1.	通信開始時間が昼、夜、深夜のどの料金帯で始まったかを調べる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1994/08/12]
	author		:[奥村明]
*************************************************************************/
UBYTE	CheckCostZone(UBYTE Hour)
{
	for(;;) {
#if (0) /* ICHOU変更 by T.Soneoka 1996/10/07 */
** 		if (Hour == (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I5] & 0x1F) % 24)) {	/*	昼の料金帯の開始時間と等しい時	*/
** 			return(NOON);
** 		}
** 		if (Hour == (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I6] & 0x1F) % 24)) {	/*	夜の料金帯の開始時間と等しい時	*/
** 			return(NIGHT);
** 		}
** 		if (Hour == (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I7] & 0x1F) % 24)) {	/*	深夜の料金帯の開始時間と等しい時	*/
** 			return(MID_NIGHT);
** 		}
#else
		if (Hour == (unsigned char)((CHK_DaytimeStartTime()) % 24)) {	/*	昼の料金帯の開始時間と等しい時	*/
			return(NOON);
		}
		if (Hour == (unsigned char)((CHK_NightStartTime()) % 24)) {	/*	夜の料金帯の開始時間と等しい時	*/
			return(NIGHT);
		}
		if (Hour == (unsigned char)((CHK_MidnightStartTime()) % 24)) {	/*	深夜の料金帯の開始時間と等しい時	*/
			return(MID_NIGHT);
		}
#endif
		if (Hour-- == 0) {
			Hour = 23;
		}
	}
}

/*************************************************************************
	module		:[料金時間計算]
	function	:[
		1.	通信開始から次の料金帯までの時間を計算
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1994/08/17]
	author		:[奥村明]
*************************************************************************/
UWORD		CalculateFirstCostTime(TIME_DATA_t *time)
{
	UWORD  cost_time;
	UBYTE hour;

	cost_time = 1;
	hour = CMN_BCD_ToDecimal(time->Hour);

	for(;;) {
		if (++hour == 24) {
			hour = 0;
		}
#if (0) /* ICHOU変更 by T.Soneoka 1996/10/07 */
		if (hour == (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I5] & 0x1F) % 24)) {	/*	昼の料金帯の開始時間と等しい時	*/
			break;
		}
		if (hour == (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I6] & 0x1F) % 24)) {	/*	夜の料金帯の開始時間と等しい時	*/
			break;
		}
		if (hour == (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I7] & 0x1F) % 24)) {	/*	深夜の料金帯の開始時間と等しい時	*/
			break;
		}
#else
		if (hour == (unsigned char)((CHK_DaytimeStartTime()) % 24)) {	/*	昼の料金帯の開始時間と等しい時	*/
			break;
		}
		if (hour == (unsigned char)((CHK_NightStartTime()) % 24)) {	/*	夜の料金帯の開始時間と等しい時	*/
			break;
		}
		if (hour == (unsigned char)((CHK_MidnightStartTime()) % 24)) {	/*	深夜の料金帯の開始時間と等しい時	*/
			break;
		}
#endif
		cost_time++;
	}

	cost_time = (UWORD)(cost_time * 60 * 60) - (UWORD)CMN_BCD_ToDecimal(time->Minute) * 60 - (UWORD)CMN_BCD_ToDecimal(time->Second);
	return(cost_time);
}
/*************************************************************************
	module		:[料金時間計算]
	function	:[
		1.	料金帯から次の料金帯までの時間を計算
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1994/08/17]
	author		:[奥村明]
*************************************************************************/
UWORD		CalculateCostTime(UBYTE zone)
{
	UWORD  cost_time;
	UBYTE hour;

	cost_time = 1;

	switch (zone) {
#if (0) /* ICHOU変更 by T.Soneoka 1996/10/07 */
	case	NOON:													/*	昼	*/
		hour = (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I5] & 0x1F) % 24);
		break;
	case	NIGHT:													/*	夜	*/
		hour = (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I6] & 0x1F) % 24);
		break;
	case	MID_NIGHT:												/*	深夜	*/
		hour = (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I7] & 0x1F) % 24);
		break;
#else
	case	NOON:													/*	昼	*/
		hour = (unsigned char)((CHK_DaytimeStartTime()) % 24);
		break;
	case	NIGHT:													/*	夜	*/
		hour = (unsigned char)((CHK_NightStartTime()) % 24);
		break;
	case	MID_NIGHT:												/*	深夜	*/
		hour = (unsigned char)((CHK_MidnightStartTime()) % 24);
		break;
#endif
	}

	for(;;) {
		if (++hour == 24) {
			hour = 0;
		}
#if (0) /* ICHOU変更 by T.Soneoka 1996/10/07 */
		if (hour == (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I5] & 0x1F) % 24)) {	/*	昼の料金帯の開始時間と等しい時	*/
			break;
		}
		if (hour == (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I6] & 0x1F) % 24)) {	/*	夜の料金帯の開始時間と等しい時	*/
			break;
		}
		if (hour == (UBYTE)((SYS_MemorySwitch[MEMORY_SW_I7] & 0x1F) % 24)) {	/*	深夜の料金帯の開始時間と等しい時	*/
			break;
		}
#else
		if (hour == (unsigned char)((CHK_DaytimeStartTime()) % 24)) {	/*	昼の料金帯の開始時間と等しい時	*/
			break;
		}
		if (hour == (unsigned char)((CHK_NightStartTime()) % 24)) {	/*	夜の料金帯の開始時間と等しい時	*/
			break;
		}
		if (hour == (unsigned char)((CHK_MidnightStartTime()) % 24)) {	/*	深夜の料金帯の開始時間と等しい時	*/
			break;
		}
#endif
		cost_time++;
	}
	cost_time = (UWORD)(cost_time * 60 * 60);
	return(cost_time);
}


/*************************************************************************
	module		:[料金管理する／しないをチェック]
	function	:[
		1.FCM_GetCostTable()の戻り値により示されるSYS_CostTableの昼、夜、深夜の料金がセットされている。
		2.基本料金がセットされている。（メモリスイッチ I-8)
		3.部門管理がONである。

	]
	return		:[TURE:料金管理行う		FALSE:料金管理行わない]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1994/08/25]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CheckCostTable(UBYTE pos)	/* SYB_NTT_AccessFile[]のオフセット */
{
	struct SYS_NTT_AccessData_t *ptr;


	/* By H.Y 1994/12/01 3Lines */
	if (pos == 0xFF) {
		return(FALSE);
	}
	ptr = &SYB_NTT_AccessFile[pos];
	if(CHK_DepartmentON()) { /** 部門管理がONの場合 */
		if((SYB_CostTable[ptr->CostTable].Daytime != 0) &&
			(SYB_CostTable[ptr->CostTable].Night != 0) &&
			(SYB_CostTable[ptr->CostTable].Midnight != 0)) {
			if(CHK_BaseCostInCostTable()) {
				return(TRUE);
			}
		}
	}
	return(FALSE);
}
/*#endif By M.Tachibana 1997/11/14 */





/*************************************************************************
	module		:[料金管理の入り口]
	function	:[
		内線/外線を判断し、ダイヤル番号に対応した料金テーブルに
		料金を加算する
	]
	return		:[]
	common		:[]
	condition	:[
		SYS_COMMAND_EXECUTE の時だけcallすること
	]
	comment		:[
		マルチ回線(同時実行)に対応
		標準仕様ではline_numberは0固定
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[]
	author		:[]
*************************************************************************/
#define		DIAL_NUMBER_MAX		11	/* 料金管理の番号(6桁)とコンペアするためのダイヤル桁数 */
void	FCM_SetCostData(
	UWORD				exec_no,	/* 実行中のExecQueue番号 */
	UBYTE				*buffer)	/* ダイヤル番号のポインタ */
{
	UWORD			dept_code;			/* 部門コード */
	unsigned char	stack_no;			/* スタック番号(0=内蔵/1=外付1/…) */
	unsigned char	command_item;		/* コマンド種別 */
	unsigned char	cost_data;			/* SYS_NTT_AccessFile[] のオフセット */
	unsigned char	dial_number[DIAL_NUMBER_MAX];	/* ダイヤル番号(コンペア用) */

 #if (PRO_MULTI_LINE == ENABLE)
	stack_no = SYB_ExecQueue[exec_no].StackNumber;
 #else
	stack_no = 0;	/* 固定 */
 #endif
	command_item = SYB_CommandFile[SYB_ExecQueue[exec_no].Number.Command].Option.Item;
	dept_code = SYB_CommandFile[SYB_ExecQueue[exec_no].Number.Command].DepartmentCode;

	/* 料金検索関数に渡すためにダイヤル番号を内部変数(near)にコピー */
	CMN_StringCopyNum( (unsigned char far *)dial_number,
						(unsigned char far *)buffer,
						DIAL_NUMBER_MAX );
	dial_number[DIAL_NUMBER_MAX-1] = NULL;

	if ((command_item != SYS_RELAYED_TX)
	&&	(command_item != SYS_RELAYED_TX_REPORT)
	&&	(command_item != SYS_BATCH_MEMORY_TX)) {	/** 交信種別判定 */

		/** 内線/外線を判断し、ダイヤル番号から対応する料金テーブルを決定 */
		cost_data = FCM_GetCostTable( dial_number, exec_no );

		if (CheckCostTable( cost_data )) {	/** 料金テーブルが設定されている */
			/** 料金を計算し、テーブルにセット */
			FCM_CostCalculate( dept_code, SYB_NTT_AccessFile[cost_data].CostTable, stack_no );
		}
	}
}

#endif


/* このファイルは、料金管理ありの場合のみ有効 */
