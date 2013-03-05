/*************************************************************************
*             DATE:  1995/11/14
*        Copy Date:  1996/10/21 From \src\kobe\anzu\src\ By M.Kotani
*        FILE NAME:  man_timr.c
*       Task ID No:  TBD
*      DESCRIPTION:
*  PUBLIC ROUTINES:  void WriteCurrentTime( void )
*                    void ReadCurrentTime( void )
*                    void MAN_TimerTask(void)
*                    void CalculateMoveSummerTime(UBYTE current_year)
*                    void CalculateReturnNormalTime(UBYTE current_year)
*                    void SetSummerTimeStatus(UDWORD current_time)
*                    void RTCTestStart(void)
*                    void RTCTestEnd(void)
* PRIVATE ROUTINES:  void WriteClockBit(UBYTE Data, UBYTE NumberOfBits)
*                    UBYTE ReadClockBit(UBYTE NumberOfBits)
*                    void ResetSummerTimeData(UBYTE year)
*                    UBYTE ExecuteSummerTime(void)
*        REFERENCE:
************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\message.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\sys_day.h"
#include	"\src\atlanta\define\sys_line.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\mnt_sw.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\sys_port.h"
#include	"\src\atlanta\ext_v\mem_data.h"
#include	"\src\atlanta\ext_v\man_data.h"
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* #if is added by H.Kubo 1997/08/11 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#endif

#if (PRO_PRINT_TYPE == LASER)
	#include 	"\src\atlanta\prt\sp322\define\prn_pro.h"
	#include	"\src\atlanta\prt\sp322\define\prn_def.h"
	#include	"\src\atlanta\prt\sp322\define\prn_stat.h"
	#include	"\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == LED)
	#include 	"\src\atlanta\prt\ph3\define\prn_pro.h"
	#include 	"\src\atlanta\prt\ph3\ext_v\prn_data.h"	/* By M.Tachibana 1998/01/27 */
#endif

#if (PRO_CPU == SH7043)
	#include  	"\src\atlanta\sh7043\define\def_tib.h"
	#include  	"\src\atlanta\sh7043\define\sh_port.h"
	#include	"\src\atlanta\sh7043\define\def_semn.h"
	#include	"\src\atlanta\sh7043\ext_v\extv_sem.h"
	#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

	/*#include	"\src\atlanta\define\stng_pro.h"*/
	UBYTE	CHK_DayLightSavingAuto(void);

#if (PRO_PANEL == ANK)	/* 1996/10/25 by K.Watanabe */
	/*#include	"\src\atlanta\opr\ank\define\opr_pro.h"*/
	void	DisplayAllBlack(void);
	void	NackBuzzer(void);

	#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"	/* By M.Kotani 97/05/29 */
#endif
#if (PRO_PANEL == KANJI)	/* 1997/08/12 by H.Kubo */
	#include	"\src\atlanta\opr\kanji\define\opr_pro.h"	/* Added by H.Kubo 1997/08/12 */
	#include	"\src\atlanta\opr\kanji\ext_v\opr_data.h"	/* By M.Kotani 97/05/29 */
#endif


	void	DPR_SetBitStopFaxcom(UWORD stack_number);
	UBYTE	CHK_UNI_MultiDisplayTime(void);

#if (PRO_PC_PRINT == ENABLE) || (PRO_DPRAM == ENABLE)
	#include	"\src\atlanta\define\dpr_pro.h" /* Added by H.Kubo 1997/08/12 */
	#include	"\src\atlanta\ext_v\dpr_data.h"
	#include	"\src\atlanta\define\uni_pro.h" /* Added by H.Kubo 1997/08/12 */
#endif

#if (PRO_MULTI_LINE == ENABLE)	/* マルチ回線 added by H.Kubo 1997/08/12 */
#include	"\src\atlanta\define\mlt_pro.h"
#include	"\src\atlanta\ext_v\mlt_data.h"
#endif /* (PRO_MULTI_LINE == ENABLE) */


#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/12 Y.Murata */
	#include  "\src\atlanta\sh7043\define\def_evtn.h"
#endif

#if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#include  	"\src\atlanta\sh7043\define\sh_sys.h"
#endif

#if (PRO_PREHEAT == ENABLE)
#include	"\src\atlanta\define\uni_pro.h"	/* 寒冷地 PreHeat  1998/12/26 s.takeuchi */
#endif

#if (PRO_CLASS1 == ENABLE)
#include  "\src\atlanta\ext_v\cl1_data.h"	/* added by H.Hirao 1999/05/11 */
#endif

#if (defined(POPLAR_H) && defined(JP0))/*V851 By Y.Suzuki 2002/06/11*/ || (defined(SAKAKI) && defined(JP0))/*V531 By M.Maeda 2002/09/18*/
#include "\src\atlanta\sh7043\define\sh_sys.h"
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/19*/
#include	"\src\atlanta\define\cmn_def.h"
#endif

#if defined(SATSUKI2) /* CI割込み救済2 O.Oshima 2003/11/26 */
#include	"\src\atlanta\satsuki2\define\satsport.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"
#endif

#if defined(STOCKHM2)
#include	"\src\atlanta\stockhm2\define\lvndport.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"
#endif
/*
** MEM_IndexTable.Itemのステータスが消去中で残る不具合を発見する。
** 1996/08/22
*/

#if (PRO_RTC_RX5C338A == ENABLE)
#include	"\src\atlanta\define\rtc_def.h"
#endif

/*@H*********************************************************************
*               BY:  S.Kawasaki
*             DATE:  Tue 24 Mar 1992
*        FILE NAME:  timer.c
*      DESCRIPTION:  １ｓｅｃ毎にtimer値をアップデートする。
*  PUBLIC ROUTINES:  TimerTask()
* PRIVATE ROUTINES:  無し
*        REFERENCE:  TIMER.JSW
*		　処理項目:  (1)1secのウェイトはwai_tsk()を使用。
*				　　 (2)1sec毎にCurrentTimeを更新し、１分経過した時点で、メイン・タスク
*					    へMSG_TIME_UP_1MINを送る。
*					 (3)VariableTimerが0でなければ1sec毎に減算し0になった時点で
*						メイン・タスクへMSG_TIME_UP_VARを送る。
**********************************************************************@H*/
/**　Module Header For CIM-E ********************************************
		module		:	[ＲＴＣに１レコードデータを書き込む]
		function	:	[リアルタイム・クロック・データを書き込みます。
						クロック・データはシリアルで出力する。
						]
  		return		:	[無し]
		common		:	[
						UWORD SYS_RTC_PortStatus;
						]
		condition	:	[]
		comment		:	[H8用でデバッグ終了　Feb.11,1994]
		machine		:	[SH7043]
		language	:	[SHC]
 		keyword		:	[CLOCK DATA]
     	date		:	[93/11/24]
 		author		:	[川崎真史]
************************************************************************/
void WriteClockBit(	UBYTE Data,				/* ＲＴＣに書き込むデータ 	*/
					UBYTE NumberOfBits		/* 下位何ビットが有効か		*/
						)
{
#if (PRO_RTC_RX5C338A == ENABLE)
	UBYTE WriteControlByte;
	UBYTE Mask;

	switch(NumberOfBits){					/* 引数の異常を検出 & マスクの設定 */
	case YEAR_REGISTER:							/* こいつらは正常 */
		Mask = YEAR_MASK;
		break;
	case MONTH_REGISTER:
		Mask = MONTH_MASK;
		break;
	case DATE_REGISTER:
		Mask = DATE_MASK;
		break;
	case WEEK_REGISTER:
		Mask = WEEK_MASK;
		break;
	case HOUR_REGISTER:
		Mask = HOUR_MASK;
		break;
	case MINUTE_REGISTER:
		Mask = MINUTE_MASK;
		break;
	case SECOND_REGISTER:
		Mask = SECOND_MASK;
		break;
	case CONTROL1_REGISTER:
		Mask = CONTROL1_MASK;
		break;
	case CONTROL2_REGISTER:
		Mask = CONTROL2_MASK;
		break;
	case ADJUST_REGISTER:
		Mask = ADJUST_MASK;
		break;
	default:
		SaveReturnAddressAndJumpBegin();	/* 異常発生。 リセット！ */
		break;
	}
	WriteControlByte = NumberOfBits | BYTE_WRITE_MODE;

	/* ますコントロールバイトを出力 */
	RTC_OutputData(WriteControlByte);
	/* 実データを出力 */
	Data &= Mask;
	RTC_OutputData(Data);

#else
	UBYTE BitNumber;	/* 書き込んでいるビットNo 				*/
	UBYTE BitTester;	/* ビットが0と1どちらかを判定するテスター  	*/

	BitTester = 0x01;	/* ビット位置０から判定する為の初期化  	*/

	for (BitNumber = 0; BitNumber < NumberOfBits; BitNumber++) {/**  有効ビット数分書き込んだか? */
 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
		if (Data & (BitTester<<BitNumber)) {	/** 次のビットへ移動させ,１か０かを判定する */
			IO__PEDR |= IO_BIT_WRTCDA;		/** RTCデータ１セット */
		}
		else {
			IO__PEDR &= ~IO_BIT_WRTCDA;		/** RTCデータ０セット */
		}
		IO__PEDR |= IO_BIT_RTCCK;
		IO__PEDR &= ~IO_BIT_RTCCK;
 #else
		if (Data & (BitTester<<BitNumber)) {	/** 次のビットへ移動させ,１か０かを判定する */
			SYS_RTC_PortStatus |= IO_BIT_WRTCDA;		/** RTCデータ１セット */
		}
		else {
			SYS_RTC_PortStatus &= ~IO_BIT_WRTCDA;		/** RTCデータ０セット */
		}
		outpw(RTC_PORT, (UWORD)SYS_RTC_PortStatus);		/** RTCデータを出力 */
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTCCLK));	/** クロック・アップ	*/
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCLK));	/** クロック・ダウン	*/
 #endif
	}
#endif
}
static UBYTE DBG_RTC2 = 0;
/**　Module Header For CIM-E ********************************************
		module		:	[ＲＴＣに時間を書き込む]
		function	:	[ＲＴＣ(リアル・タイム・クロック)に下記のデ-タを書き込む
							struct TIME_DATA_t CurrentTimeInBCD
						]
  		return		:	[無し]
		common		:	[
							struct TIME_DATA_t CurrentTimeInBCD
						]
		condition	:	[無し]
		comment		:	[H8用でデバッグ終了　Feb.11,1994]
		machine		:	[SH7043]
		language	:	[SHC]
 		keyword		:	[TIME]
     	date		:	[93/11/24]
 		author		:	[川崎真史]
************************************************************************/
void WriteCurrentTime( void )
{
#if (PRO_RTC_RX5C338A == ENABLE)

	DBG_RTC2 = 0;
	while (DBG_RTC2){
		RTC_IO_Enable(RTC_RW_PERMIT);										/* 読み書き許可 */
		WriteClockBit(0x95, YEAR_REGISTER);									/**  年データ書き込み 	*/
		CurrentTimeInBCD.Year   = ReadClockBit(YEAR_REGISTER);				/** 年データを読みだしセット  	*/
		RTC_IO_Enable(RTC_RW_FORBIT);										/* 読み書き禁止 */
	}

	RTC_IO_Enable(RTC_RW_PERMIT);											/* 読み書き許可 */

	WriteClockBit(CurrentTimeInBCD.Year, YEAR_REGISTER);					/**  年データ書き込み 	*/
	WriteClockBit(CurrentTimeInBCD.Month, MONTH_REGISTER);					/**  月データ書き込み 	*/
	WriteClockBit(CurrentTimeInBCD.Date, DATE_REGISTER);					/**  日データ書き込み 	*/
	WriteClockBit(CurrentTimeInBCD.Week, WEEK_REGISTER);					/**  週データ書き込み 	*/
	WriteClockBit(CurrentTimeInBCD.Hour, HOUR_REGISTER);					/**  時間データ書き込み*/
	WriteClockBit(CurrentTimeInBCD.Minute, MINUTE_REGISTER);				/**  分データ書き込み 	*/

	RTC_IO_Enable(RTC_RW_FORBIT);											/* 読み書き禁止 */
#else
/*		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTC_IO));	1998/07/10 *//** 書き込み許可 	*/
		RTC_IO_WriteEnable();	/* 1998/08/31 H.Yoshikawa */

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
		IO__PEDR |= IO_BIT_RTCCE;
		IO__PEDR &= ~IO_BIT_RTCCK;
 #else
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTCCE));		/** チップ・イネーブル  	*/
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCLK));		/** クロック・ダウン		*/
 #endif
		WriteClockBit(CurrentTimeInBCD.Year, 8);					/**  年データ書き込み 	*/
		WriteClockBit(CurrentTimeInBCD.Month, 8);					/**  月データ書き込み 	*/
		WriteClockBit(CurrentTimeInBCD.Date, 8);					/**  日データ書き込み 	*/
		WriteClockBit(CurrentTimeInBCD.Week, 4);					/**  週データ書き込み 	*/
		WriteClockBit(CurrentTimeInBCD.Hour, 8);					/**  時間データ書き込み*/
		WriteClockBit(CurrentTimeInBCD.Minute, 8);					/**  分データ書き込み 	*/

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
		IO__PEDR &= ~IO_BIT_RTCCE;
 #else
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCE));		/** チップ・ディスエーブル	*/
 #endif

/*		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTC_IO)); 1998/07/10*//** 書き込み禁止	 	*/
		RTC_IO_ReadEnable();	/* 1998/08/31 H.Yoshikawa */
#endif
}
/**　Module Header For CIM-E ********************************************
		module		:	[ＲＴＣから時間（１レコードデータ）を読み込む]
		function	:	[ＲＴＣ(リアル・タイム・クロック)から時間データを１レコード分読み込む。
						]
  		return		:	[時間デ-タ]
		common		:	[無し]
		condition	:	[無し]
		comment		:	[H8用でデバッグ終了　Feb.11,1994]
		machine		:	[SH7043]
		language	:	[SHC]
 		keyword		:	[TIME]
     	date		:	[93/11/24]
 		author		:	[川崎真史]
************************************************************************/
UBYTE ReadClockBit(	UBYTE NumberOfBits		/* RTCより読みだすビット数 */
								)
{
#if (PRO_RTC_RX5C338A == ENABLE)
	UBYTE WriteControlByte;
	UBYTE Data;
	UBYTE Mask;

	switch(NumberOfBits){					/* 引数の異常を検出 & マスクの設定 */
	case YEAR_REGISTER:							/* こいつらは正常 */
		Mask = YEAR_MASK;
		break;
	case MONTH_REGISTER:
		Mask = MONTH_MASK;
		break;
	case DATE_REGISTER:
		Mask = DATE_MASK;
		break;
	case WEEK_REGISTER:
		Mask = WEEK_MASK;
		break;
	case HOUR_REGISTER:
		Mask = HOUR_MASK;
		break;
	case MINUTE_REGISTER:
		Mask = MINUTE_MASK;
		break;
	case SECOND_REGISTER:
		Mask = SECOND_MASK;
		break;
	case CONTROL1_REGISTER:
		Mask = CONTROL1_MASK;
		break;
	case CONTROL2_REGISTER:
		Mask = CONTROL2_MASK;
		break;
	case ADJUST_REGISTER:
		Mask = ADJUST_MASK;
		break;
	default:
		SaveReturnAddressAndJumpBegin();	/* 異常発生。 リセット！ */
		break;
	}
	WriteControlByte = NumberOfBits | BYTE_READ_MODE;

	/* ますコントロールバイトを出力 */
	RTC_OutputData(WriteControlByte);
	/* 実データを受け取る */
	Data = RTC_InputData();
	Data &= Mask;
	return Data;

#else
	UBYTE BitNumber;	/* 読みだしているビット位置 		*/
	UBYTE Data;			/* 読みだしたビットをORするデータ  	*/
	UBYTE BitOr;		/* ORするデータ					*/
	Data = 0;
	BitOr = 0x01;				/* ORするデータを最下位にセット		*/

	for (BitNumber = 0; BitNumber < NumberOfBits; BitNumber++) {	/** 指定されたビット数分読みだしていなければ */

 #if (0)	/* 1998/08/31 H.Yoshikawa */
//		if ((inpw(SENSOR1_PORT) & IO_BIT_RRTCDA)) {	/** RTCのREADビットはHighであれば */
//			Data |= BitOr;		/** リターン値BitOrの位置に１をOR */
//		}
 #endif

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
		if (IO__PEDR  & IO_BIT_RRTCDA) {	/** RTCのREADビットはHighであれば *//* 1998/08/31 H.Yoshikawa */
			Data |= BitOr;		/** リターン値BitOrの位置に１をOR */
		}
		else {	/** RTCのREADビットがLowである*/
			/** 左シフトした時の下位ビットは0と保証されるはず。 */
			Data &= ~BitOr;		/** リターン値のBitOrの位置を０でAND */
		}
 #else
		if ((inpw(RRTCDA_PORT) & IO_BIT_RRTCDA)) {	/** RTCのREADビットはHighであれば *//* 1998/08/31 H.Yoshikawa */
			Data |= BitOr;		/** リターン値BitOrの位置に１をOR */
		}
		else {	/** RTCのREADビットがLowである*/
			/** 左シフトした時の下位ビットは0と保証されるはず。 */
			Data &= ~BitOr;		/** リターン値のBitOrの位置を０でAND */
		}
 #endif

		BitOr <<= 1;	/** BitOrの位置を左へ１ビットシフト */

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
		IO__PEDR |= IO_BIT_RTCCK;
		IO__PEDR &= ~IO_BIT_RTCCK;
 #else
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTCCLK));	/** RTCクロック・アップ	*/
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCLK));	/** RTCクロック・ダウン	*/
 #endif

	}
	return(Data);	/** 読みだしたデータをリターン */
#endif
}
/**　Module Header For CIM-E ********************************************
		module		:	[RTCのデータを読みだす]
		function	:	[RTCのデータを読みだし下記にセットする]
  		return		:	[無し]
		common		:	[
		  					struct TIME_DATA_t CurrentTimeInBCD
						]
		condition	:	[]
		comment		:	[H8用でデバッグ終了　Feb.11,1994]
		machine		:	[SH7043]
		language	:	[SHC]
 		keyword		:	[TIME]
     	date		:	[93/11/24]
 		author		:	[川崎真史]
************************************************************************/
void ReadCurrentTime( void )
{

#if (PRO_RTC_RX5C338A == ENABLE)
	RTC_IO_Enable(RTC_RW_PERMIT);			/* 読み書き許可 */

	CurrentTimeInBCD.Year   = ReadClockBit(YEAR_REGISTER);					/** 年データを読みだしセット  	*/
	CurrentTimeInBCD.Month  = ReadClockBit(MONTH_REGISTER);				/** 月データを読みだしセット  	*/
	CurrentTimeInBCD.Date   = ReadClockBit(DATE_REGISTER);				/** 日データを読みだしセット  	*/
	CurrentTimeInBCD.Week   = ReadClockBit(WEEK_REGISTER);				/** 週データを読みだしセット  	*/
	CurrentTimeInBCD.Hour   = ReadClockBit(HOUR_REGISTER);				/** 時間データを読みだしセット  	*/
	CurrentTimeInBCD.Minute = ReadClockBit(MINUTE_REGISTER);			/** 分データを読みだしセット  	*/
	CurrentTimeInBCD.Second = ReadClockBit(SECOND_REGISTER);			/** 秒データを読みだしセット  	*/

	RTC_IO_Enable(RTC_RW_FORBIT);			/* 読み書き禁止 */
#else
/*	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTC_IO)); 1998/07/10 *//** 読み込み許可 	*/
	RTC_IO_ReadEnable();	/* 1998/08/31 H.Yoshikawa */

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	IO__PEDR |= IO_BIT_RTCCE;
	IO__PEDR &= ~IO_BIT_RTCCK;
 #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTCCE));		/** RTCチップ・イネーブル  			*/
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCLK));	/** RTCクロック・ダウン				*/
 #endif

	CurrentTimeInBCD.Year   = ReadClockBit(8);				/** 年データを読みだしセット  	*/
	CurrentTimeInBCD.Month  = ReadClockBit(8);				/** 月データを読みだしセット  	*/
	CurrentTimeInBCD.Date   = ReadClockBit(8);				/** 日データを読みだしセット  	*/
	CurrentTimeInBCD.Week   = ReadClockBit(4);				/** 週データを読みだしセット  	*/
	CurrentTimeInBCD.Hour   = ReadClockBit(8);				/** 時間データを読みだしセット  	*/
	CurrentTimeInBCD.Minute = ReadClockBit(8);				/** 分データを読みだしセット  	*/
	CurrentTimeInBCD.Second = ReadClockBit(8);				/** 秒データを読みだしセット  	*/

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	IO__PEDR &= ~IO_BIT_RTCCE;
 #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCE));	/** RTCチップ・ディスエーブル		*/
 #endif

/*	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTC_IO)); 1998/07/10 *//** RTC読みだし禁止	 		*/
	RTC_IO_WriteEnable();	/* 1998/08/31 H.Yoshikawa */
#endif
}

/***********************************************************************/
/**　Module Header For CIM-E ********************************************
		module		:	[タイマー監視タスク]
		function	:	[
						タスク内での処理項目
	　						・システム・クロックの書き込み
	　						・システム・クロックの読みだし
	　						・プリンター・ステータスの読みだし(KIRIの場合)
	　						・１分の時間監視
	　						・任意に設定された時間の監視
	　						・日付変更の監視
						]
		return		:	[無し]
		comment		:	[H8用でデバッグ終了　Feb.11,1994]
		condition	:	[メイン・タスクからパワーON直後に一度だけクリエイトされ、電源がOFFになるまで死なない]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
 		keyword		:	[TIMER]
     	date		:	[94/2/27]
 		author		:	[川崎真史]
************************************************************************/
/* スタック節約の為、static変数にします。 Add By J.Miyazaki ******/
static UBYTE  Minute;
static UBYTE  Date;
static MESSAGE_t	TimerTaskMessage;
static MESSAGE_t	*Msg;

static BYTE T30_ActivateCounter = 0; /** Ｔ３０モニター連続テスト用に追加 By S.Kawasaki 1996/07/14 */

void MAN_TimerTask(void)
{
	UBYTE	year;	/* サマータイム用に追加 1995/12/21 Eguchi */
	/*
	** MEM_IndexTable.Itemのステータスが消去中で残る不具合を発見する。
	** By S.Kawasaki 1996/08/22
	*/
	UBYTE i;

	UWORD	cnt;
	UWORD	pat_journal_start_time;	/* ｼﾞｬｰﾅﾙMH展開ｽﾀｰﾄ時間 */
	UWORD	pat_journal_exec_time;	/* ｼﾞｬｰﾅﾙMH展開にかかった時間 */
	UWORD	wait_timer;				/* ﾀｲﾏｰﾀｽｸ１秒ｳｴｲﾄ帳尻あわせ */
	UBYTE	line_max;				/* 現在の回線数 1997/02/04 Y.Matsukuma */
	UDWORD	disp_time;
#if (PRO_DPRAM == ENABLE)
	MESSAGE_t	tx_message;
	MESSAGE_t	*rx_message;
#endif

#if ((defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2))	/* Add by Y.Kano 2003/09/30 *//*V531 By M.Maeda 2002/09/18*/
	/*------------------------------------------
	** London より移植
	*/
	UBYTE	charge_start;
	UWORD	battery_timer;
	UWORD	ad_battery;
#endif

#if defined(SATSUKI2) || defined(STOCKHM2) /* CI割込み救済2 O.Oshima 2003/11/26 */
	UBYTE	ci_rescue_timer;
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/19*/
	UBYTE	old_eco_status;
#endif


#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/19*/
	old_eco_status = 0;
#endif

#if ((defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2))	/* Add by Y.Kano 2003/09/30 *//*V531 By M.Maeda 2002/09/18*/
	ad_battery = AD_Battery();
	if (ad_battery >= AD_BATTERY_FULL1) { /* 最初はini_cpuo.cで読んでいる */
		charge_start = 0;
	}
	else {
		charge_start = 1;
	}
	BatteryChargeOff();
	battery_timer = 0;
#endif

#if defined(SATSUKI2) || defined(STOCKHM2) /* CI割込み救済2 O.Oshima 2003/11/26 */
	ci_rescue_timer = 5; /* 5秒に1回入れる。*/
#endif

	T30_ActivateCounter = 0; /* By S.Kawasaki 1996/07/14 */

	TimerTaskMessage.Item = FROM_TIMER;
	CMN_LongTimeToBCD(&CurrentTimeInBCD, SYB_CurrentTime);	/** (unsigned long)SYB_CurrentTimeをstruct TIME_DATA_t CurrentTimeInBCDへ変換する。*/

	year   = CurrentTimeInBCD.Year;		/** 年データを保存 1995/12/21 Eguchi サマータイム用 */
	Minute = CurrentTimeInBCD.Minute;	/** 分データを保存 */
	Date = CurrentTimeInBCD.Date;    	/** 日データ保存	*/
	ResetSummerTimeData(year);			/** サマータイム用データを計算 1995/12/21 Eguchi */
	RTC_TestMode = 0;					/** ＲＴＣテストモードＯＦＦで初期化 Feb.20,1996 By S.K */

	pat_journal_start_time = 0;	/* ｼﾞｬｰﾅﾙMH展開ｽﾀｰﾄ時間 */
	pat_journal_exec_time = 0;	/* ｼﾞｬｰﾅﾙMH展開にかかった時間 */
	wait_timer = 0;				/* ﾀｲﾏｰﾀｽｸ１秒ｳｴｲﾄ帳尻あわせ */

#if (PRO_MULTI_LINE == ENABLE)
	OPR_MultiDisplayTime = 0;	/* マルチ通信表示用変数初期化 1997/02/10 Y.Murata */
	OPR_MultiLineCount = 1;		/* マルチ通信表示用変数初期化 1997/02/10 Y.Murata */
#endif

	while(1) {	/** パワーOFFになるまで以下の処理を行う */

		/** 受信（1枚目受信確定時刻）基準時刻の更新  POPLAR追加 1997/03/19  By T.Yamaguchi */
		SYB_CurrentFaxReceiveTime++;

/*#if (PRO_MULTI_LINE == ENABLE)*/
	/** ジャーナルセット */
	/* ジャーナルのＭＨ展開にＶ５３で３６０ｍｓから４００ｍｓかかります。その間制御つかみっぱなしです。
	 * また、ＭＡＮタイマーは通信より優先順位が高いためジャーナル展開中の受信に悪影響（ﾃﾞｺｰﾄﾞｴﾗｰ）を
	 * およぼす可能性があります。
	 * そこで、ジャーナル展開にウエイト処理（つまり、制御を一旦はなす）をいれます。
	 * そして、１秒ウエイトになるようにつずつまをあわせます。
	 * 本来は、タスクにしたい所だが、タスクの数の制限でタイマータスクで行います。
	*/
		pat_journal_start_time = SYS_GeneralTimer;
		MAN_SetJournalMultiLine();
		pat_journal_exec_time = (UWORD)(SYS_GeneralTimer - pat_journal_start_time);

		if (pat_journal_exec_time >= 100) {	/* １秒以上かかった */
			wait_timer = 1;
		}
		else if (pat_journal_exec_time == 0) {
			wait_timer = 100;
		}
		else {
			wait_timer = (100 - pat_journal_exec_time);
		}
		wai_tsk(wait_timer);

#if 0
		wai_tsk(100); 						/** １秒ウェイト */
#endif

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/12 Y.Murata */
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {
			CMN_DisableInterrupt();	/**	割り込み禁止	*/
			if ((SYS_MinoltaFuncIntervalTimer != 0xFFFF)  && (SYS_MinoltaFuncIntervalTimer != 0)) {
				SYS_MinoltaFuncIntervalTimer--;
				if (SYS_MinoltaFuncIntervalTimer == 0) {
					SYS_MinoltaFuncIntervalTimer = 0xFFFF;	/* time up */
					PRN_1PageReceived = 1;
					det_evt(EVT_PRN_RESTART);
				}
			}
			CMN_EnableInterrupt();	/**	割り込み許可	*/
		}
#endif

		/** セマフォの獲得  1996/03/29 Eguchi */
		wai_sem(semno.rtc);
		if (RTC_TestMode != 1) { /** ＲＴＣテストモードでなければＲＴＣを読み出しする。 Feb.20,1996 By S.K */
			ReadCurrentTime();					/** RTCからデータを読み込む 時刻の更新 */
		}
		SYB_CurrentTime = CMN_BCD_TimeToLong(&CurrentTimeInBCD); /** BCD データをLONG型へ変換する。*/
		/** セマフォの解放  1996/03/29 Eguchi */
		sig_sem(semno.rtc);
		SYB_PowerOFF_StartTime = SYB_CurrentTime;		/* By H.Y 1994/08/15 ＤＲＡＭバックアップのため */
		++SYB_DRAM_BackupTime;							/* 1994/11/08 Y.Murata ＤＲＡＭバックアップ充電時間 */

		/***** 以下１１行 サマータイム用の処理追加 1995/12/21 Eguchi****************/

		if (year != CurrentTimeInBCD.Year) { /** 年が変わったら   */
			year = CurrentTimeInBCD.Year;	 /** 年データを取り出す   */
			ResetSummerTimeData(year);		 /** サマータイム用データを再設定 */
		}
		if (ExecuteSummerTime()) {				/**サマータイム処理実行*/
			/* 時間を更新した場合,表示を更新するためメインタスクにメッセージ送信する 1996/01/23 Eguchi*/
			/* メッセージを送信しないと表示が更新されるのが１分だけ遅れるから */
			TimerTaskMessage.Message = MSG_SUMMER_TIME_EXECUTE; /** メイン・タスクへサマータイム実行のメッセージを送る */
			snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
			rcv_msg(mbxno.MAN_TimerTask, &Msg);
		}
		/*****  サマータイム用の処理終了 1995/12/21 Eguchi*************************/

#if (PRO_MULTI_LINE == ENABLE)	/* マルチ回線表示（タイマー） 1997/02/04 Y.Matsukuma */
		disp_time = (UDWORD)(CHK_UNI_MultiDisplayTime());
		line_max = OPT_CountModems();	/** Change CheckMultiLine() to OPT_CountModems() By O.Kimoto 1997/06/26 */

#if (0) /* OPT_CountModems()を元に戻したのて必要ありません 1998/03/11 by T.Soneoka */
//#if (PRO_LINENUMBER == TWICE_LINE)
//		/* OPT_CountModems()の中で、標準回線／拡張回線のカウントを行うよう変更したが、
//		** ここではあくまでも本当のモデムの個数で判断しないと、不必要にメインにメッセージが飛んでします。
//		** By O.Kimoto 1998/03/06
//		*/
//		line_max -= 1;
//#endif
#endif
		if ((disp_time != 0) && (line_max > 1)) {
			OPR_MultiDisplayFlag = 1;
			OPR_MultiDisplayTime++;
			if (OPR_MultiDisplayTime > disp_time) {
				OPR_MultiDisplayTime = 0;
				OPR_MultiLineCount++;
				if (OPR_MultiLineCount > line_max) {
					OPR_MultiLineCount = 1;
				}
				/** メイン・タスクへマルチ表示のメッセージを送る（表示を更新させるため） */
				TimerTaskMessage.Message = MSG_MULTI_DISPLAY_TIME;
				snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
				rcv_msg(mbxno.MAN_TimerTask, &Msg);
			}
		}
		else {
			OPR_MultiDisplayFlag = 0;
			OPR_MultiDisplayTime = 0;
			OPR_MultiLineCount = 1;
		}

#endif

#if ((defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2))	/* Add by Y.Kano 2003/09/30 *//*V531 By M.Maeda 2002/09/18*/
	/*------------------------------------------
	** London より移植
	*/
		if (charge_start) {
			battery_timer++;
			if (battery_timer < 60) {	/* １分間充電 */
				BatteryChargeOn();
			}
			else {
				BatteryChargeOff();
				/* 充電命令ポートをＬｏｗにして10ms以上待ってからADを読み取る */
				if (battery_timer >= 61) {	/* １秒おいてから */
					ad_battery = AD_Battery();
					if (ad_battery >= AD_BATTERY_FULL2) {	/* 急速充電完了 */
						charge_start = 0;
					}
					battery_timer = 0;
				}
			}
		}
		else {
			battery_timer++;
			if (battery_timer > 60) { /* 1分ごと */
				battery_timer = 0;
				if (CMN_CheckPrinting() == FALSE) { /* プリント中はA/Dの値がふらつくので。原因は桐田氏が調査 O.Oshima 2001/07/03 */
					ad_battery = AD_Battery();
					if (ad_battery >= AD_BATTERY_FULL1) {
						charge_start = 0;
					}
					else {
						charge_start = 1;
					}
				}
			}
		}
#endif


#if (PRO_PREHEAT == ENABLE)
		/*
		* 寒冷地 PreHeat  1998/12/26 s.takeuchi
		*/
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {		/* プリヒート中 */
			/* 現在時刻が終了時刻を過ぎた or プリヒート無効にされた ならプリヒート終了 */
			if ((SYB_CurrentTime >= PreHeatEndTime)
			||	!CHK_UNI_PreHeatEnable()) {
				TimerTaskMessage.Message = MSG_PREHEAT_END_TIME;
				snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
				rcv_msg(mbxno.MAN_TimerTask, &Msg);
			}
		}
		if (Minute != CurrentTimeInBCD.Minute) {	/* プリヒート開始は1分毎に見る */
			if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT)) {	/* プリヒートしていない */
				if (CHK_UNI_PreHeatEnable()) {		/* プリヒート有効 */
					/* 現在日時(BCD)を元にプリヒート終了時刻を作る */
					CMN_LongTimeToBCD(&PreHeatEndTimeBCD, SYB_CurrentTime);
					PreHeatEndTimeBCD.Hour = CMN_DecimalToBCD(CHK_UNI_PreHeatEndHour());
					PreHeatEndTimeBCD.Minute = CMN_DecimalToBCD(CHK_UNI_PreHeatEndMinute());
					PreHeatEndTimeBCD.Second = 0;
					PreHeatEndTime = CMN_BCD_TimeToLong(&PreHeatEndTimeBCD);

					/* プリヒート終了時刻を過ぎていたら1日進める */
					if (SYB_CurrentTime >= PreHeatEndTime) {
						PreHeatEndTime += 86400L;		/* (60L * 60L * 24L) */
						CMN_LongTimeToBCD(&PreHeatEndTimeBCD, PreHeatEndTime);
					}

					/* 終了時刻からプリヒート時間だけ戻った時刻を開始時刻とする */
					PreHeatStartTime = PreHeatEndTime - (UDWORD)(CHK_UNI_PreHeatTime() * 60);

					/* 現在時刻がプリヒート期間中ならプリヒート開始 */
					if ((SYB_CurrentTime >= PreHeatStartTime)
					&&	(SYB_CurrentTime < PreHeatEndTime)) {
						TimerTaskMessage.Message = MSG_PREHEAT_START_TIME;
						snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
						rcv_msg(mbxno.MAN_TimerTask, &Msg);
					}
				}
			}
		}
#endif /* PRO_PREHEAT == ENABLE */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/11/07 Y.Matsukuma */
		if (OPR_FeedinDispTime != 0) {
			OPR_FeedinDispTime--;
			if (OPR_FeedinDispTime == 0) {
				/** メイン・タスクへメッセージを送る（表示を更新させるため） */
				TimerTaskMessage.Message = MSG_MULTI_DISPLAY_TIME;
				snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
				rcv_msg(mbxno.MAN_TimerTask, &Msg);
			}
		}
#endif
#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/19*/
		/* 省エネモードへの移行 */ 
		if (CMN_CheckAvailableEcoMode()) {
			if (SYS_EcoModeTimer > 0) {
				if (!(--SYS_EcoModeTimer)) {
					SYS_AutoPowerSW = FALSE;
					TimerTaskMessage.Message = MSG_ECO_MODE_CHANGE;
					snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
					rcv_msg(mbxno.MAN_TimerTask, &Msg);
				}
			}
		}
		else {
			if (SYS_EcoModeStatus == ECO_MODE_ON) {	/* キーが押下された時の復帰用 */
				/*
				** 押下するキーによりメインタスクにメッセージを送信しない場合がある。
				** MENUキー等。この場合、SYS_PANEL_BUSYは立っている。
				** ここでメインを走らせるためにメッセージを送信する。
				*/
				TimerTaskMessage.Message = MSG_ECO_MODE_CHANGE;
				snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
				rcv_msg(mbxno.MAN_TimerTask, &Msg);
			}
			SYS_EcoModeTimer = (UWORD)CHK_UNI_EcoModeStartTime() * 60;
		}
		if (SYS_EcoModeStatus != ECO_MODE_SETTING) {	/* 表示更新用 */
			if (old_eco_status != SYS_EcoModeStatus) {
				TimerTaskMessage.Message = MSG_ECO_MODE_CHANGE;
				snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
				rcv_msg(mbxno.MAN_TimerTask, &Msg);
			}
			old_eco_status = SYS_EcoModeStatus;
		}
#endif
#if 0 /* (PRO_ENERGY_SAVE == ENABLE) 見送る */		/* 頻繁に24VOnOffが起こり、リレーの寿命が持たない対策 2002/11/29 T.Takagi */
		if (CMN_Check24V_OffEnable()) {		/* 24VをOFFしてもよい条件が整っていれば */
			if (SYS_24V_OffTimer > 0) {
				if (!(--SYS_24V_OffTimer)) {
					TimerTaskMessage.Message = MSG_24V_OFF;
					snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
					rcv_msg(mbxno.MAN_TimerTask, &Msg);
				}
			}
		}
		else {	/* 何か24Vが必要なものが動いていたら */
			SYS_24V_OffTimer = (UWORD)CHK_UNI_EcoModeStartTime() * 60;
		}
#endif

		/* １分毎にメインへメッセージを送る。 */
		if (Minute != CurrentTimeInBCD.Minute) {	/** １分経過すれば */
			Minute = CurrentTimeInBCD.Minute;	/** 分データを保存 */
			TimerTaskMessage.Message = MSG_TIME_UP_1MIN; /** メイン・タスクへタイム・アップのメッセージを送る */
			snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
			rcv_msg(mbxno.MAN_TimerTask, &Msg);

#if (PRO_PRINT_TYPE == LED)	/* For Test By M.Tachibana 1997/12/20 */
			if (SYB_MaintenanceSwitch[MNT_SW_C0] & MEM_FAT_CLEANING) {
				if ((CMN_CheckOptionBoardExecuting() == TRUE) ||
					(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY) ||
					(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY) ||
					(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
					;
				} else {
					CMN_DisableInterrupt();
					if ((MEM_TotalStoreBlockCounter != 0) &&
						(MEM_CheckUseIndex() == (UBYTE)MEM_NO_INDEX)) {
						MEM_ClearAllFATAreaInTimer();
						SYB_MaintenanceSwitch[MNT_SW_C0] |= MEM_FAT_ERROR;
					}
					CMN_EnableInterrupt();
				}
			}
#endif

#if (PRO_PRINT_TYPE	== LASER)			/* レーザーショット(桐) */
			if (CMN_CheckPrinting() == FALSE) { /* プリント中でないとき S.Kawasaki 1996/06/05 */
				if (SYS_AutoShutOFF_Timer) {
					if (!(--SYS_AutoShutOFF_Timer)) {
						PRN_Pause();
						/*
						** Ｔ３０モニター連続テスト用スイッチ
						** By S.Kawasaki 1996/07/14
						*/
						if (SYB_MaintenanceSwitch[MNT_SW_B2] & T30_TEST_SWITCH) {
							T30_ActivateCounter = 2; /** スリープに入ってから２分後にＴ３０モニター起動 */
						}
					}
				}
			}
#endif
#if (PRO_PRINT_TYPE == LED)
			if (CMN_CheckPrinting() == FALSE) { /* プリント中でないとき S.Kawasaki 1996/06/05 */
				if (SYS_AutoShutOFF_Timer) {
					if (!(--SYS_AutoShutOFF_Timer)) {
						PRN_PrinterSleep();
						SYS_PrinterWakeupTimer = SYB_MaintenanceSwitch[MNT_SW_H9];
						/*
						** Ｔ３０モニター連続テスト用スイッチ
						** By S.Kawasaki 1996/07/14
						*/
						if (SYB_MaintenanceSwitch[MNT_SW_B2] & T30_TEST_SWITCH) {
							T30_ActivateCounter = 2; /** スリープに入ってから２分後にＴ３０モニター起動 */
						}
					}
				}

#if defined(POPLAR_F)	/* FAN騒音対策 */
#elif (defined(POPLAR_H) && defined(JP0)) /* V851 ＦＡＮ制御 By H.Fujimura 2002/07/11 */
				/* 所定時間が経過すれば、機内温度をチェックしてある特定の温度以下になっていればFANを止めます。 */
				if (SYS_AutoFanOffTimer2) {
					if (!(--SYS_AutoFanOffTimer2)) {

						PRN_CalculateFanStopEnvTemp();
						if ((PRN_FanStopEnvTemp < (float)CHK_InternalTempDoToStopFan()) && /*  default 50℃未満 */
							(PRN_FanStopEnvTemp > (float)0)) { /** ０℃以下となる場合はサーミスタがオープンになっている可能性が有る為、この場合は無条件に２５分（Default)間FANを回転させる */
							SYS_AutoFanOffTimer2 = 0;
						}
						else {
							SYS_AutoFanOffTimer2 = (UWORD)CHK_UNI_InternalTempIntervalTimer();		/* 単位：分 *//* FAN停止用監視タイマー */
						}
						if (SYS_AutoFanOffTimer2 == 0) {
							PRN_FanStop();
							SYS_AutoFanOffTimer2 = 0;
							SYS_AutoFanOffTimer = 0;
						}
					}
				}
				
				/* 所定時間が経過すれば、FANを止めます。 */
				if (SYS_AutoFanOffTimer) {
					if (!(--SYS_AutoFanOffTimer)) {
						PRN_FanStop();
						SYS_AutoFanOffTimer2 = 0;
						SYS_AutoFanOffTimer = 0;
					}
				}
#else
				if (SYS_AutoFanOffTimer) {
#if (PRO_FAN_TEST == ENABLE)	/* By M.Tachibana 2000/02/14 */
					--SYS_AutoFanOffTimer;
					if (SYS_AutoFanOffTimer == SYB_MaintenanceSwitch[MNT_SW_H8] - SYS_MemorySwitch[81]) {	/* MemorySwitch[I1] */
						if (PRN_SaveEnvironmentTemp < (float)SYS_MemorySwitch[80]) {	/* MemorySwitch[I0] ??℃未満 */
							SYS_AutoFanOffTimer = 0;
						}
					}
					if (SYS_AutoFanOffTimer == 0) {
						PRN_FanStop();
					}
#else
					if (!(--SYS_AutoFanOffTimer)) {
						PRN_FanStop();
					}
#endif
				}
#endif
				if (SYS_PrinterWakeupTimer) {
					if (!(--SYS_PrinterWakeupTimer)) {
						TimerTaskMessage.Message = MSG_PRINTER_WAKEUP;	/** メイン・タスクへメッセージを送る */
						snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
						rcv_msg(mbxno.MAN_TimerTask, &Msg);
					}
				}
			}
#endif

			/*
			** Ｔ３０モニター連続テスト用スイッチ
			** By S.Kawasaki 1996/07/14
			*/
			if (SYB_MaintenanceSwitch[MNT_SW_B2] & T30_TEST_SWITCH) {
				if (T30_ActivateCounter) {
					if (!(--T30_ActivateCounter)) { /** Ｔ３０モニターの起動 */
						TimerTaskMessage.Item = FROM_OPERATION;
						TimerTaskMessage.Message = MSG_LIST_PRINT;
						SYS_DocumentPrintItem = LST_T30MONITOR;
						snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
						rcv_msg(mbxno.OPR_MAN_MessageTask, &Msg);
						TimerTaskMessage.Item = FROM_TIMER;
					}
				}
			}

#if (PRO_PRINT_TYPE == LED)
			/* 連続コピーテスト（１０分インターバル） By M.Tachibana 1997/11/05 */
			if (SYB_MaintenanceSwitch[MNT_SW_H5] & 0x80) {
				if (SYB_MaintenanceSwitch[MNT_SW_H1]) {
					if (!(--SYB_MaintenanceSwitch[MNT_SW_H1])) {
						if (CMN_CheckPrintEnable(SYS_MULTI_COPY) && CMN_CheckScanEnable()) {
							ContCopyTest();
						}
					}
				}
			}
#endif

			continue;
		}

#if defined(POPLAR_F)	/* FAN騒音対策 */
		if (CMN_CheckPrinting() == FALSE) { /* プリント中でないとき */
			if (SYS_AutoFanOffTimer) {
				--SYS_AutoFanOffTimer;
				if (CHK_UNI_FanStopTimer() > CHK_UNI_FanStopTimerLowTemp()) {
					if (SYS_AutoFanOffTimer == (CHK_UNI_FanStopTimer() - CHK_UNI_FanStopTimerLowTemp())) {
						PRN_CalculateFanStopEnvTemp();
						PRN_FanStopEnvTempWork = (float)CHK_UNI_FanOnTempThreshold();
						if ((PRN_FanStopEnvTemp < PRN_FanStopEnvTempWork) && /*  default 50℃未満 */
							(PRN_FanStopEnvTemp > (float)0)) { /** ０℃以下となる場合はサーミスタがオープンになっている可能性が有る為、この場合は無条件に２５分（Default)間FANを回転させる */
							SYS_AutoFanOffTimer = 0;
						}
					}
				}
				if (SYS_AutoFanOffTimer == 0) {
					PRN_FanStop();
				}
			}
		}

		/*
		 * 連続ポーリングＪＡＴＥ違反対策
		*/
		if (SYS_ContPollingValiableTimer) {
			SYS_ContPollingValiableTimer--;
			if (SYS_ContPollingValiableTimer == 0) {
				TimerTaskMessage.Message = MSG_TIME_UP_VAR;	/** メイン・タスクへタイム・アップのメッセージを送る */
				snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
				rcv_msg(mbxno.MAN_TimerTask, &Msg);
			}
		}
#endif

		/* VariableTimerに時間がセットされた時点より減算を始める */
		if (SYS_VariableTimer) {	/** SYS_VariableTimerにデータがセットされていれば */
			if (!(--SYS_VariableTimer)) {	/** SYS_VariableTimerを減算し、ゼロになれば */
				TimerTaskMessage.Message = MSG_TIME_UP_VAR;	/** メイン・タスクへタイム・アップのメッセージを送る */
				snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
				rcv_msg(mbxno.MAN_TimerTask, &Msg);
				continue;
			}
		}

#if (PRO_MULTI_LINE == ENABLE)/* 1996/12/23 by O.Kimoto */
		/* VariableTimerに時間がセットされた時点より減算を始める */
		for (cnt = 1; cnt < SYS_OPTION_BOARD_MAX; cnt++) {
			if (SYS_MltVariableTimer[cnt]) {	/** SYS_VariableTimerにデータがセットされていれば */
				if (!(--SYS_MltVariableTimer[cnt])) {	/** SYS_VariableTimerを減算し、ゼロになれば */
					TimerTaskMessage.Message = MSG_DATE_CHANGED;	/** メイン・タスクへタイム・アップのメッセージを送る */
					snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
					rcv_msg(mbxno.MAN_TimerTask, &Msg);
					continue;
				}
			}
		}

		/* ２回線仕様で、ＦＣＭ＿ＴＡＳＫも起動せずにキューがエラーとなることがあり、
		** その際、次のキューを処理するためのメッセージをここで送信する。
		** by O.Kimoto 1997/01/22
		*/
#if 0
//		if (SYS_NextQueueVariableTimer) {
//			if (!(--SYS_NextQueueVariableTimer)) {
//				TimerTaskMessage.Message = MSG_TIME_UP_VAR;
//				snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
//				rcv_msg(mbxno.MAN_TimerTask, &Msg);
//				continue;
//			}
//		}
#endif
		/* 1997/09/25
		 * 同報中および、ｷｭｰに展開されて発呼待ちの時に、ﾀｲﾏｰﾀｽｸのこれ以下の
		 * 処理が、走らない！
		 * ﾒｲﾝﾀｽｸを走らすのが目的だから、これ以下の処理もはしるようにします。
		*/
		if (SYS_NextQueueVariableTimer) {
			if (!(--SYS_NextQueueVariableTimer)) {
				TimerTaskMessage.Message = MSG_DATE_CHANGED;
				snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
				rcv_msg(mbxno.MAN_TimerTask, &Msg);
			}
		}
#endif

		if ( Date != CurrentTimeInBCD.Date ) { /** 日付が変われば */
			Date = CurrentTimeInBCD.Date;    	/** 日データ保存	*/

#if defined(SATSUKI2) || defined(STOCKHM2)					/* LCD表示更新（表示リフレッシュ） by Y.Kano 2003/09/22 */
/*			CurrentTimeInBCD.Hour = 0;*/	/* 時刻クリアはいらない。by Y.kano 2003/09/22 */
/*			CurrentTimeInBCD.Minute = 0;*/
			UpdateLCD();			
#endif

		    SYB_TxTotalCount = 1;
		    SYB_RxTotalCount = 1;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
		    SYB_TxTotalCountExt = 1;
		    SYB_RxTotalCountExt = 1;
#endif
#if (PRO_DEPARTMENT == ENABLE)
 #if (PRO_COST == ENABLE)
			if (CHK_DepartmentON() && (Date == (UBYTE)CHK_DepartListPrintDate())) {
				SYS_DepartmentListRequest = 1;		/* By H.Y 1994/07/31 */
 			}
 #endif
#endif

#if (PRO_MULTI_LINE == ENABLE)	/* 1996/12/16 Y.Murata */
			/*----------------------------*/
			/* オプションモデム用通番更新 */
			/*----------------------------*/
			for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
				SYB_OptionJournalTxTotalCount[i] = 1;	/* オプションボード送受信ジャーナルナンバー */
				SYB_OptionJournalRxTotalCount[i] = 1;
			}
#endif

			TimerTaskMessage.Message = MSG_DATE_CHANGED;		/** メイン・タスクへ日付変更のメッセージを送る */
			snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
			rcv_msg(mbxno.MAN_TimerTask, &Msg);
			continue;
		}
#if (PRO_PRINT_TYPE	== LASER)			/* レーザーショット(桐) */
		/*****************************************************************************************
		 * プリンタのステータスを１秒間隔で読みだします
		******************************************************************************************/
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/06 Y.Murata */
		if (!SYS_PRN_SirialInhibit) {	/* By H.Y 1994/06/29 */
			PRN_TimerTaskSerial = 1;
			PRN_CheckPrinterStatus();
			PRN_TimerTaskSerial = 0;
		}
 #else
		if (!SYS_PRN_SirialInhibit) {	/* By H.Y 1994/06/29 */
			PRN_CheckPrinterStatus();
		}
 #endif

#endif

#if (PRO_MULTI_LINE == ENABLE)/* 1996/12/16 Y.Murata */

		/*****************************************************************************************
		 * オプションモデムストップスイッチを監視する
		******************************************************************************************/
		for (cnt = 1; cnt < SYS_OPTION_BOARD_MAX; cnt++) {
			if (SYS_OptionLineStatus[cnt] & SYS_OPTION_STOP_FAXCOM) {
				if (SYS_OptionLineStatus[cnt] & SYS_OPTION_REAL_LINE_BUSY) {
					if ((SYS_Opt[cnt].SYS_FaxComType == SYS_COMMAND_EXECUTE)
					||	(SYS_Opt[cnt].SYS_FaxComType == SYS_MANUAL_TX)) {

						DPR_SetBitStopFaxcom((UWORD)(cnt -1));
						SYS_ClearOptionLineStop((unsigned char)cnt);
					}
				}
			}
		}

		/* 受信できない時（メモリオーバー等）のプレラインビジーのクリア 1997/01/30 Y.Murata */
		for (cnt = 1; cnt < SYS_OPTION_BOARD_MAX; cnt++) {
			if (SYS_PreLineBusyCheckStatus[cnt]) {
				SYS_PreLineBusyCheckStatus[cnt]++;
				if (SYS_PreLineBusyCheckStatus[cnt] >= 10) {	/* 10sec */
					SYS_PreLineBusyCheckStatus[cnt] = 0;
					SYS_OptionLineStatus[cnt] &= ~SYS_OPTION_PRE_LINE_BUSY;
				}
			}
		}
#endif


		/*
		** MEM_IndexTable.Itemのステータスが消去中で残る不具合を発見する。
		** By S.Kawasaki 1996/08/22
		*/
		if (SYB_MaintenanceSwitch[MNT_SW_C0]&MEM_INDEX_TEST) {
			for (i = 0; i < 30; i++) {
				if (MEM_IndexTable[i].Item == MEM_NOW_DELETING) {
#if (PRO_PANEL == ANK)
					DisplayAllBlack();
#endif
#if (PRO_PANEL == KANJI)
					ClearDisplay();
#endif
					while(1) {
						NackBuzzer();
						wai_tsk(50);
						if (!(SYB_MaintenanceSwitch[MNT_SW_C0]&MEM_INDEX_TEST)) {
							i = 30;
							break;
						}
					}
				}
			}
		}

#if (PRO_PC_PRINT == ENABLE)	/* データ転送中のタイムアウトの処理追加。By J.Miyazaki 1997/01/10 */
		if (DPR_CheckOptionPrintBoardExist()/*DPR_PCR_Enable By J.Miyazaki 1997/01/14*/) {
			if (DPR_PCR_DataReceiving) {
				DPR_PCR_Timer++;
				if (DPR_PCR_Timer > (UWORD)((UWORD)CHK_UNI_PCNonCommunicationTime() * 10)) {	/**３０分間，DPR_PCR_GETPRINTERSTATUSとDPR_MEM_WRITEがこなかったら */
					TimerTaskMessage.Item = FROM_DPR_REMOTEFUNCEXECTASK;
					TimerTaskMessage.Message = MSG_DPR_PCRTIMEOUT;
					snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
					rcv_msg(mbxno.MAN_TimerTask, &Msg);
					TimerTaskMessage.Item = FROM_TIMER;
				}
#if (PRO_PRINT_TYPE == LED)	/* By M.Tachibana 1998/01/27 */
				if (PRN_PC_DataReceiveCheck) {
					DPR_PCR_PrintTimer++;
					if ((DPR_PCR_Timer <= (UWORD)((UWORD)CHK_UNI_PCNonCommunicationTime() * 10))	/* 同時に起きた場合は無視 */
					 && (DPR_PCR_PrintTimer > (UWORD)((UWORD)CHK_UNI_PCNonCommunicationTime() * 10))) {	/**３０分間，DPR_MEM_WRITEがこなかったら */
						TimerTaskMessage.Item = FROM_DPR_REMOTEFUNCEXECTASK;
						TimerTaskMessage.Message = MSG_DPR_PCRTIMEOUT;
						snd_msg(mbxno.MAN_Task, &TimerTaskMessage);
						rcv_msg(mbxno.MAN_TimerTask, &Msg);
						TimerTaskMessage.Item = FROM_TIMER;
					}
				}
#endif
			}
		}
#endif
#if (PRO_DPRAM == ENABLE)
		/*****************************************************************************************
		 * ＤＰＲＡＭ通信を監視する
		******************************************************************************************/
		/* DPR_FuncRxMessageTimerに時間がセットされた時点より減算を始める */
		CMN_DisableInterrupt();	/** 割り込み禁止 */
		if (DPR_FuncRxMessageTimer) {	/** DPR_FuncRxMessageTimerにデータがセットされていれば */
			if (!(--DPR_FuncRxMessageTimer)) {	/** DPR_FuncRxMessageTimerを減算し、ゼロになれば */
				DPRD_ErrorFuncReceiveMessage();	/**5秒間タイムアップ*/
				rcv_msg(mbxno.DPR_FunctionResult, &rx_message);		/** ホスト側からの応答を待つ */
				snd_msg(mbxno.DPR_UpLoadRxTask, &tx_message);		/**完了通知*/
				continue;
			}
		}
		CMN_EnableInterrupt();	/** 割り込み許可 */
		/* DPR_DataRxMessageTimerに時間がセットされた時点より減算を始める */
		CMN_DisableInterrupt();	/** 割り込み禁止 */
		if (DPR_DataRxMessageTimer) {	/** DPR_DataRxMessageTimerにデータがセットされていれば */
			if (!(--DPR_DataRxMessageTimer)) {	/** DPR_DataRxMessageTimerを減算し、ゼロになれば */
				DPRD_ErrorDataReceiveMessage();	/**5秒間タイムアップ*/
				rcv_msg(mbxno.DPR_DataResult, &rx_message);		/** ホスト側からの応答を待つ */
				snd_msg(mbxno.DPR_UpLoadRxTask, &tx_message);		/**完了通知*/
				continue;
			}
		}
		CMN_EnableInterrupt();	/** 割り込み許可 */
		/* DPR_FuncTxMessageTimerに時間がセットされた時点より減算を始める */
		CMN_DisableInterrupt();	/** 割り込み禁止 */
		if (DPR_FuncTxMessageTimer) {	/** DPR_FuncTxMessageTimerにデータがセットされていれば */
			if (!(--DPR_FuncTxMessageTimer)) {	/** DPR_FuncTxMessageTimerを減算し、ゼロになれば */
				DPRD_ErrorFuncSendMessage();	/**5秒間タイムアップ*/
				tx_message.Item = FROM_DPR_UPLOAD_RX_TASK;
				tx_message.Message = DPR_ExpectFunctionReturn;
				snd_msg(mbxno.DPR_FunctionResult, &tx_message); /** ホスト側からの応答の代わり */
				rcv_msg(mbxno.DPR_UpLoadRxTask, &rx_message);	/**完了通知を受け取る*/
				continue;
			}
		}
		CMN_EnableInterrupt();	/** 割り込み許可 */
		/* DPR_DataTxMessageTimerに時間がセットされた時点より減算を始める */
		CMN_DisableInterrupt();	/** 割り込み禁止 */
		if (DPR_DataTxMessageTimer) {	/** DPR_DataTxMessageTimerにデータがセットされていれば */
			if (!(--DPR_DataTxMessageTimer)) {	/** DPR_DataTxMessageTimerを減算し、ゼロになれば */
				DPRD_ErrorDataSendMessage();	/**5秒間タイムアップ*/
				tx_message.Item = FROM_DPR_UPLOAD_RX_TASK;
				tx_message.Message = DPR_ExpectDataReturn;
				snd_msg(mbxno.DPR_DataResult, &tx_message);		/** ホスト側からの応答の代わり */
				rcv_msg(mbxno.DPR_UpLoadRxTask, &rx_message);	/**完了通知を受け取る*/
				continue;
			}
		}
		CMN_EnableInterrupt();	/** 割り込み許可 */
#endif

#if (PRO_PRINT_TYPE == LASER)	/* F100 */
		CMN_DisableInterrupt();	/** 割り込み禁止 */
		if (SYS_DualPrinerWakeUpStatus) {
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
				if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
					SYS_DualPrinerWakeUpStatus = 1;
				}
				else {
					SYS_DualPrinerWakeUpStatus++;
				}
			}
			else {
				SYS_DualPrinerWakeUpStatus = 0;
			}
		}
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
			if (SYS_DualPrinterWaiting) {
				if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)
				|| (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM)) {
					SYS_DualPrinterWaitStatus = 1;
				}
				else {
					SYS_DualPrinterWaitStatus++;
				}
			}
			else {
				SYS_DualPrinterWaitStatus = 0;
			}
		}
		else {
			SYS_DualPrinterWaitStatus = 0;
		}
		CMN_EnableInterrupt();	/** 割り込み許可 */
#endif
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* added by H.Hirao 1999/05/12 */
		CMN_DisableInterrupt();	/** 割り込み禁止 */
		if (CL1_RestrictionStatusResetTimer) {	/** CL1_RestrictionStatusResetTimerにデータがセットされていれば */
			--CL1_RestrictionStatusResetTimer;	/** CL1_RestrictionStatusResetTimerを減算し */
			CL1_RestrictionStatusResetTimer = 0;	/* 不完全なので、止める by H.Hirao 1999/05/25 */
		}
		CMN_EnableInterrupt();
#endif

#if defined(SATSUKI2) || defined(STOCKHM2) /* CI割込み救済2 O.Oshima 2003/11/26 */
		if (CHK_UNI_CiRescueEnable()) {
			if (!(--ci_rescue_timer)) {
				ci_rescue_timer = 5;
				if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & (SYS_LINE_BUSY | SYS_PRINTER_BUSY))) {
					OutputWORD(GA_INT_REC, IO_BIT_CI_INT);	/* 割込み受領のみ出す。 */
				}
			}
		}
#endif

	}
}



/* サマータイム関係 */
/*************************************************************************
	module		:[サマータイムに切り替わる時間を計算]
	function	:[
		1.４月の第１日曜日の午前２時までの基準時刻からの累積秒数を計算する。
	]
	return		:[]
	common		:[
				SYS_MoveTimeToSummerTime
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/04]
	author		:[江口]
*************************************************************************/
void CalculateMoveSummerTime(UBYTE current_year)
{
	TIME_DATA_t		bcd_time;
	UBYTE  day;
	UBYTE  week;

	day = (UBYTE)1;

	/* サマータイムに切り替わる時間を計算 */
	/*--------------------------------*/
	/* ４月の第１日曜日が何日か求める */
	/*--------------------------------*/

	/** ４月１日が何曜日か求める */
	bcd_time.Year   = current_year;
	bcd_time.Month  = 0x04;
	bcd_time.Date   = CMN_DecimalToBCD(day);
	bcd_time.Hour   = 0x00;
	bcd_time.Minute = 0x00;
	bcd_time.Second = 0x00;
	CMN_LongTimeToBCD((TIME_DATA_t *)&bcd_time , CMN_BCD_TimeToLong((TIME_DATA_t *)&bcd_time));

	/** 曜日から差分の日数を加える */
	week = CMN_BCD_ToDecimal(bcd_time.Week);

	/*------------------------------*
	 * 4月１日      第1日曜日  差分 *
	 *------------------------------*
	 *   日		->    4/1		±0 *
	 *   月		->    4/7	 	＋6 *
	 *   火		->    4/6		＋5 *
	 *   水		->    4/5		＋4 *
	 *   木		->    4/4		＋3 *
	 *   金		->    4/3		＋2 *
	 *   土		->    4/2		＋1 *
	 *------------------------------*/
	if (1 < week && week <= 7) {
		day += (8 - week);
	}

	/** ４月の第１日曜日の午前２時００分００秒をロング時間に変換 */
	bcd_time.Year   =  current_year;
	bcd_time.Month  =  0x04;
	bcd_time.Date   =  CMN_DecimalToBCD(day);
	bcd_time.Hour   =  0x02;
	bcd_time.Minute =  0x00;
	bcd_time.Second =  0x00;
	bcd_time.Week   =  0x01;/* 別にいらん */
	SYS_MoveTimeToSummerTime = CMN_BCD_TimeToLong((TIME_DATA_t *)&bcd_time);
}



/*************************************************************************
	module		:[サマータイムから戻る時間を計算]
	function	:[
		1.１０月の最終日曜日の午前２時までの基準時刻からの累積秒数を計算する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ＵＳＡ以外の国でサーマータイムを実施している場合、時間の設定は異なる
				　可能性あり]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/04]
	author		:[江口]
*************************************************************************/
void CalculateReturnNormalTime(UBYTE current_year)
{
	TIME_DATA_t		bcd_time;
	UBYTE  day;

	day = (UBYTE)31;

	/* サマータイムから戻る時間を計算 */
	/*--------------------------------*/
	/* 10月の最終日曜日が何日か求める */
	/*--------------------------------*/

	/** 10月31日が何曜日か求める */
	bcd_time.Year   = current_year;
	bcd_time.Month  = 0x10;
	bcd_time.Date   = CMN_DecimalToBCD(day);
	bcd_time.Hour   = 0x00;
	bcd_time.Minute = 0x00;
	bcd_time.Second = 0x00;
	CMN_LongTimeToBCD((TIME_DATA_t *)&bcd_time , CMN_BCD_TimeToLong((TIME_DATA_t *)&bcd_time));

	/** 曜日から差分の日数を引く */
	/*------------------------------*
	 * 10月3１日   最終日曜日  差分 *
	 *------------------------------*
	 *   日		->    10/31		±0 *
	 *   月		->    10/30	 	－1 *
	 *   火		->    10/29		－2 *
	 *   水		->    10/28		－3 *
	 *   木		->    10/27		－4 *
	 *   金		->    10/26		－5 *
	 *   土		->    10/25		－6 *
	 *------------------------------*/

	day -= (CMN_BCD_ToDecimal(bcd_time.Week) - 1);

	/* 10月の最終日曜日の午前２時００分００秒をロング時間に変換 */
	bcd_time.Year   =  current_year;
	bcd_time.Month  =  0x10;
	bcd_time.Date   =  CMN_DecimalToBCD(day);
	bcd_time.Hour   =  0x02;
	bcd_time.Minute =  0x00;
	bcd_time.Second =  0x00;
	bcd_time.Week   =  0x01;
	SYS_ReturnTimeFromSummerTime = CMN_BCD_TimeToLong((TIME_DATA_t *)&bcd_time);
}



/*************************************************************************
	module		:[サマータイム状態をセット]
	function	:[
		1.引数で与えられた時刻がサマータイム中に該当するかしないかを調べる
	]
	return		:[]
	common		:[
				SYS_CurrentSummerTimeStatus
				SYS_MoveTimeToSummerTime
				SYS_ReturnTimeFromSummerTime
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/21]
	author		:[江口]
*************************************************************************/
void SetSummerTimeStatus(UDWORD current_time)
{
	if ((current_time >  SYS_MoveTimeToSummerTime)
	&&	(current_time <= SYS_ReturnTimeFromSummerTime)) {
		SYS_CurrentSummerTimeStatus = SYS_DURING_SUMMER_TIME;
	}
	else if (current_time > SYS_ReturnTimeFromSummerTime) {
		SYS_CurrentSummerTimeStatus = SYS_AFTER_SUMMER_TIME;
	}
	else {
		SYS_CurrentSummerTimeStatus = SYS_BEFORE_SUMMER_TIME;
	}
}




/*************************************************************************
	module		:[サマータイム用データを設定]
	function	:[
		1.夏時間に切り替わる時間を計算
		2.夏時間から戻る時間を計算
		3.夏時間中かどうかを調べる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/21]
	author		:[江口]
*************************************************************************/
void ResetSummerTimeData(UBYTE year)
{
	CalculateMoveSummerTime(year);
	CalculateReturnNormalTime(year);
	SetSummerTimeStatus(SYB_CurrentTime);
}




/*************************************************************************
	module		:[サマータイム処理実行]
	function	:[
		1.現在時刻と夏時間に移行する時間を比較。
		2.現在時刻が夏時間に移行する時間を越えた場合、夏時間自動きりかえ設定がＯＮの場合、時計を１時間進める
		31.現在時刻と夏時間から戻る時間を比較。
		2.現在時刻が夏時間から戻る時間を越えた場合、夏時間自動きりかえ設定がＯＮでかつ
		　夏時間中であった場合、時計を１時間戻す。夏時間中のステータスはクリアしておく。
		  夏時間から戻るときは、１日の内で午前２時が２回くることになる。
	]
	return		:[
				1:夏時間自動きり変え実行（時計更新）
				0:処理なし
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/21]
	author		:[江口]
*************************************************************************/
UBYTE ExecuteSummerTime(void)
{
	switch (SYS_CurrentSummerTimeStatus) {
	case SYS_BEFORE_SUMMER_TIME:	/* 年始から夏時間に移行するまで */
		if (SYB_CurrentTime > SYS_MoveTimeToSummerTime) {/* 夏時間移行時刻を越えた */
			SYS_CurrentSummerTimeStatus = SYS_DURING_SUMMER_TIME;/*夏時間中にセット*/
			if (CHK_DayLightSavingAuto()) {/*自動きりかえＯＮ */
				wai_sem(semno.rtc);
				CurrentTimeInBCD.Hour++;	/* １時間進める */
				WriteCurrentTime();			/* RTC更新 */
				sig_sem(semno.rtc);
				return (1);
			}
		}
		break;

	case SYS_DURING_SUMMER_TIME:	/* サマータイム中 */
		if (SYB_CurrentTime > SYS_ReturnTimeFromSummerTime) {
			SYS_CurrentSummerTimeStatus = SYS_AFTER_SUMMER_TIME;
			if (CHK_DayLightSavingAuto()) {
				wai_sem(semno.rtc);
				CurrentTimeInBCD.Hour--;
				WriteCurrentTime();
				sig_sem(semno.rtc);
				return (1);
			}
		}
		break;

	case SYS_AFTER_SUMMER_TIME:		/* サマータイムから戻ってから、年末まで */
		/* 特に処理しない */
	default:
		break;
	}
	return (0);
}

/*************************************************************************
	module		:[リアルタイムクロック調整開始]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[調整実行中はタイマータスクでのＲＴＣ読み出しを中止する。]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/2/20]
	author		:[川崎真史]
*************************************************************************/
void RTCTestStart(void)
{
#if (PRO_RTC_RX5C338A == ENABLE)
	UBYTE cnt;		/* ｶｳﾝﾀ */
	UBYTE rtccnt;

	/* Test Mode 開始により10msﾀｲﾏ内の1S毎の時計ﾃﾞｰﾀのREADをしない*/
	RTC_TestMode = 1;

	/*	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTC_IO)); 1998/07/10 *//* I/O = LOW 	*/
	RTC_IO_Enable(RTC_RW_FORBIT);			/* 1998/08/31 H.Yoshikawa */

	IO__PEDR &= ~IO_BIT_RTCCK;
	IO__PEDR |= IO_BIT_RTCCE;

	/* rtccnt = RtcClockCnt; By S.K Aug.9,1995 */
	rtccnt = 5;
	for(cnt=0; cnt<rtccnt; cnt++) {
		RTC_IO_Enable(RTC_RW_PERMIT);		/* 1998/08/31 H.Yoshikawa */
		RTC_IO_Enable(RTC_RW_FORBIT);		/* 1998/08/31 H.Yoshikawa */
	}
#else
	UBYTE cnt;		/* ｶｳﾝﾀ */
	UBYTE rtccnt;

	/* Test Mode 開始により10msﾀｲﾏ内の1S毎の時計ﾃﾞｰﾀのREADをしない*/
	RTC_TestMode = 1;

/*	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTC_IO)); 1998/07/10 *//* I/O = LOW 	*/
	RTC_IO_ReadEnable();	/* 1998/08/31 H.Yoshikawa */

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	IO__PEDR &= ~IO_BIT_RTCCK;
	IO__PEDR |= IO_BIT_RTCCE;
 #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCLK));		/* ｸﾛｯｸ･ﾀﾞｳﾝ	*/
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTCCE));		/* ﾁｯﾌﾟ･ｲﾈｰﾌﾞﾙ  */
 #endif

	/* rtccnt = RtcClockCnt; By S.K Aug.9,1995 */
	rtccnt = 5;
	for(cnt=0; cnt<rtccnt; cnt++) {
 #if (0)	/* 1998/07/10 H.Yoshikawa */
//		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTC_IO));	/* I/O = HIGH */
//		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTC_IO));	/* I/O = LOW  */
 #endif
		RTC_IO_WriteEnable();	/* 1998/08/31 H.Yoshikawa */
		RTC_IO_ReadEnable();	/* 1998/08/31 H.Yoshikawa */
	}
/*	Modified By A.Yoshida 1995.01.25
//	5波出力した後，LOWに固定する
//	outp(RTC_PORT, (SYS_RTC_PortStatus |= IO_BIT_RTC_IO));	* I/O = HIGH *
*/
#endif
}

/*************************************************************************
	module		:[リアルタイムクロック調整終了]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[・調整終了後はタイマータスクでのＲＴＣ読み出しを開始する。
				  ・調整期間中の時間のずれは調整後オペレーションで合わせる必要有り。
				  ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/2/20]
	author		:[川崎真史]
*************************************************************************/
void RTCTestEnd(void)
{
#if (PRO_RTC_RX5C338A == ENABLE)

	/*	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTC_IO)); 1998/07/10 *//* 書き込み禁止	 	*/
	RTC_IO_Enable(RTC_RW_FORBIT);				/* 1998/08/31 H.Yoshikawa */

	/* ﾘｱﾙﾀｲﾑｸﾛｯｸﾃﾞｰﾀの更新 */
	/** セマフォ獲得　1996/03/29 Eguchi */
	wai_sem(semno.rtc);

	WriteCurrentTime();					/** 調整開始時の時間に戻す。 */

	/** セマフォ解放　1996/03/29 Eguchi */
	sig_sem(semno.rtc);

	/* 通常の時計処理に戻る(READをするようにする) */
	RTC_TestMode = 0;

#else
 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	IO__PEDR &= ~IO_BIT_RTCCE;
 #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCE));	/* ﾁｯﾌﾟ･ﾃﾞｨｽｴｰﾌﾞﾙ	*/
 #endif

/*	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTC_IO)); 1998/07/10 *//* 書き込み禁止	 	*/
	RTC_IO_ReadEnable();	/* 1998/08/31 H.Yoshikawa */

	/* ﾘｱﾙﾀｲﾑｸﾛｯｸﾃﾞｰﾀの更新 */
	/** セマフォ獲得　1996/03/29 Eguchi */
	wai_sem(semno.rtc);

	WriteCurrentTime(); /** 調整開始時の時間に戻す。 */

	/** セマフォ解放　1996/03/29 Eguchi */
	sig_sem(semno.rtc);

	/* 通常の時計処理に戻る(READをするようにする) */
	RTC_TestMode = 0;
#endif
}

/*************************************************************************
	module		:[リアルタイムクロックを書き込み状態にする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1998/07/10]
	author		:[吉川弘康]
*************************************************************************/
void RTC_IO_WriteEnable(void)
{
#if (PRO_RTC_RX5C338A == ENABLE)
	/* nothing */
#else
 #if (PRO_RTC_IO_LOW_READ == ENABLE)				/* RTCへのWrite時にIO_BIT_RTC_IOをHighにする H.Yoshikawa 1998/07/10 */
  #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	CMN_DisableInterrupt();
	PFC__PEIOR |=IO_BIT_RTCDT;	/* ＰＥ１１を出力端子に設定 */
	IO__PEDR |= IO_BIT_RTCIO;
	CMN_EnableInterrupt();	/**	割り込み許可	*/
  #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTC_IO));		/** 書き込み許可 	*/
  #endif
 #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTC_IO));		/** 書き込み許可 	*/
 #endif
#endif
}

/*************************************************************************
	module		:[リアルタイムクロックを読み込み状態にする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1998/07/10]
	author		:[吉川弘康]
*************************************************************************/
void RTC_IO_ReadEnable(void)
{
#if (PRO_RTC_RX5C338A == ENABLE)
	/* nothing */
#else
 #if (PRO_RTC_IO_LOW_READ == ENABLE)				/* RTCへのRead時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
  #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	CMN_DisableInterrupt();
	PFC__PEIOR &= ~IO_BIT_RTCDT;	/* ＰＥ１１を入力端子に設定 */
	IO__PEDR &= ~IO_BIT_RTCIO;
	CMN_EnableInterrupt();	/**	割り込み許可	*/
  #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTC_IO));		/** 読み込み許可 	*/
  #endif
 #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTC_IO));		/** 読み込み許可 	*/
 #endif
#endif
}

/*************************************************************************
	module		:[ＲＴＣテスト不可検査]
	function	:[
		1.ＲＴＣにデータの読み書きを行い、テスト可能かを調べます
	]
	return		:[
		TRUE	:ＲＴＣテスト可能
		FALSE	:ＲＴＣテスト不可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1998/08/21]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckRTC_TestEnable(void)
{
#if (PRO_RTC_RX5C338A == ENABLE)
	UBYTE	ret;				/* ﾘﾀｰﾝ値 */
	TIME_DATA_t	chk_write_time;	/* RTCﾁｪｯｸﾃﾞｰﾀ書き込み用変数 */
	TIME_DATA_t	chk_read_time;	/* RTCﾁｪｯｸﾃﾞｰﾀ読み込み用変数 */

	/* 書き込み用テストデータのセット（1998年12月31日(木) 12時34分） */
	chk_write_time.Year   = 0x98;	/* 年	*/
	chk_write_time.Month  = 0x12;	/* 月	*/
	chk_write_time.Date   = 0x31;	/* 日	*/
	chk_write_time.Hour   = 0x12;	/* 時	*/
	chk_write_time.Minute = 0x34;	/* 分	*/
	chk_write_time.Week   = 0x05;	/* 曜日	*/

	/* Test Mode 開始により10msﾀｲﾏ内の1S毎の時計ﾃﾞｰﾀのREADをしない */
	RTC_TestMode = 1;

	/** セマフォ獲得 */
	wai_sem(semno.rtc);

	RTC_IO_Enable(RTC_RW_PERMIT);

	WriteClockBit(chk_write_time.Year, YEAR_REGISTER);					/**  年データ書き込み 	*/
	WriteClockBit(chk_write_time.Month, MONTH_REGISTER);				/**  月データ書き込み 	*/
	WriteClockBit(chk_write_time.Date, DATE_REGISTER);					/**  日データ書き込み 	*/
	WriteClockBit(chk_write_time.Week, WEEK_REGISTER);					/**  週データ書き込み 	*/
	WriteClockBit(chk_write_time.Hour, HOUR_REGISTER);					/**  時間データ書き込み*/
	WriteClockBit(chk_write_time.Minute, MINUTE_REGISTER);				/**  分データ書き込み 	*/

	RTC_IO_Enable(RTC_RW_FORBIT);

	RTC_IO_Enable(RTC_RW_PERMIT);

	chk_read_time.Year   = ReadClockBit(YEAR_REGISTER);					/** 年データを読みだしセット  	*/
	chk_read_time.Month  = ReadClockBit(MONTH_REGISTER);				/** 月データを読みだしセット  	*/
	chk_read_time.Date   = ReadClockBit(DATE_REGISTER);					/** 日データを読みだしセット  	*/
	chk_read_time.Week   = ReadClockBit(WEEK_REGISTER);					/** 週データを読みだしセット  	*/
	chk_read_time.Hour   = ReadClockBit(HOUR_REGISTER);					/** 時間データを読みだしセット  	*/
	chk_read_time.Minute = ReadClockBit(MINUTE_REGISTER);				/** 分データを読みだしセット  	*/
	chk_read_time.Second = ReadClockBit(SECOND_REGISTER);				/** 秒データを読みだしセット  	*/

	RTC_IO_Enable(RTC_RW_FORBIT);	/* 1998/08/31 H.Yoshikawa */

	/** セマフォ解放 */
	sig_sem(semno.rtc);

	/* ここでRTC_TestModeを0にすると、NGの時のｽﾄｯﾌﾟｷｰ待ちの間に、CurrentTimeInBCDが書き換わってしまう
	** （OKでもﾀｲﾐﾝｸﾞによってはありえる）ので、RTCTestEnd()で時間を元に戻してから0にします
	*/

	/* 書き込んだデータが正しいかを調べます
	** 注）正しく実装されていない時は、全てのデータが正しく読み込めないので、年月日のデータしか比較しません
	*/
	if ((chk_write_time.Year == chk_read_time.Year)
	 && (chk_write_time.Month == chk_read_time.Month)
	 && (chk_write_time.Date == chk_read_time.Date)) {	/* 正しく実装されている時 */
		ret = TRUE;
	}
	else {												/* 正しく実装されていない時 */
		ret = FALSE;
	}

	return(ret);

#else
	UBYTE	ret;				/* ﾘﾀｰﾝ値 */
	TIME_DATA_t	chk_write_time;	/* RTCﾁｪｯｸﾃﾞｰﾀ書き込み用変数 */
	TIME_DATA_t	chk_read_time;	/* RTCﾁｪｯｸﾃﾞｰﾀ読み込み用変数 */

	/* 書き込み用テストデータのセット（1998年12月31日(木) 12時34分） */
	chk_write_time.Year   = 0x98;	/* 年	*/
	chk_write_time.Month  = 0x12;	/* 月	*/
	chk_write_time.Date   = 0x31;	/* 日	*/
	chk_write_time.Hour   = 0x12;	/* 時	*/
	chk_write_time.Minute = 0x34;	/* 分	*/
	chk_write_time.Week   = 0x05;	/* 曜日	*/

	/* Test Mode 開始により10msﾀｲﾏ内の1S毎の時計ﾃﾞｰﾀのREADをしない */
	RTC_TestMode = 1;

	/** セマフォ獲得 */
	wai_sem(semno.rtc);

	RTC_IO_WriteEnable();	/* 1998/08/31 H.Yoshikawa */

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	IO__PEDR |= IO_BIT_RTCCE;
	IO__PEDR &= ~IO_BIT_RTCCK;
 #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTCCE));	/** RTCチップ・イネーブル	*/
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCLK));	/** RTCクロック・ダウン		*/
 #endif

	WriteClockBit(chk_write_time.Year, 8);							/** 年データを書き込む		*/
	WriteClockBit(chk_write_time.Month, 8);							/** 月データを書き込む		*/
	WriteClockBit(chk_write_time.Date, 8);							/** 日データを書き込む		*/
	WriteClockBit(chk_write_time.Week, 4);							/** 曜日データを書き込む	*/
	WriteClockBit(chk_write_time.Hour, 8);							/** 時間データを書き込む	*/
	WriteClockBit(chk_write_time.Minute, 8);						/** 分データを書き込む		*/

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	IO__PEDR &= ~IO_BIT_RTCCE;
 #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCE));	/** RTCチップ・ディスエーブル */
 #endif

	RTC_IO_ReadEnable();	/* 1998/08/31 H.Yoshikawa */

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	IO__PEDR |= IO_BIT_RTCCE;
	IO__PEDR &= ~IO_BIT_RTCCK;
 #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTCCE));	/** RTCチップ・イネーブル	*/
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCLK));	/** RTCクロック・ダウン		*/
 #endif

	chk_read_time.Year   = ReadClockBit(8);							/** 年データを読み込む		*/
	chk_read_time.Month  = ReadClockBit(8);							/** 月データを読み込む		*/
	chk_read_time.Date   = ReadClockBit(8);							/** 日データを読み込む		*/
	chk_read_time.Week   = ReadClockBit(4);							/** 曜日データを読み込む	*/
	chk_read_time.Hour   = ReadClockBit(8);							/** 時間データを読み込む	*/
	chk_read_time.Minute = ReadClockBit(8);							/** 分データを読み込む		*/
	chk_read_time.Second = ReadClockBit(8);							/** 秒データを読み込む		*/

 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	IO__PEDR &= ~IO_BIT_RTCCE;
 #else
	outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCE));	/** RTCチップ・ディスエーブル */
 #endif

	RTC_IO_WriteEnable();	/* 1998/08/31 H.Yoshikawa */

	/** セマフォ解放 */
	sig_sem(semno.rtc);

	/* ここでRTC_TestModeを0にすると、NGの時のｽﾄｯﾌﾟｷｰ待ちの間に、CurrentTimeInBCDが書き換わってしまう
	** （OKでもﾀｲﾐﾝｸﾞによってはありえる）ので、RTCTestEnd()で時間を元に戻してから0にします
	*/

	/* 書き込んだデータが正しいかを調べます
	** 注）正しく実装されていない時は、全てのデータが正しく読み込めないので、年月日のデータしか比較しません
	*/
	if ((chk_write_time.Year == chk_read_time.Year)
	 && (chk_write_time.Month == chk_read_time.Month)
	 && (chk_write_time.Date == chk_read_time.Date)) {	/* 正しく実装されている時 */
		ret = TRUE;
	}
	else {												/* 正しく実装されていない時 */
		ret = FALSE;
	}

	return(ret);
#endif
}

#if (PRO_RTC_RX5C338A == ENABLE)
/*************************************************************************
	module		:[ＲＴＣドライバ関数（ＲＸ５Ｃ３３８Ａ専用）]
	function	:[
		1.ＲＴＣ＿ＯＮでポートを立てます
		2.ＲＴＣ＿ＯＮでポートを下げます
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2004/10/27]
	author		:[Y.Tanaka]
*************************************************************************/
void	RTC_DRV_CE(UBYTE key)
{
 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	if (key == RTC_ON){
		IO__PEDR |= IO_BIT_RTCCE;
	}
	else {
		IO__PEDR &= ~IO_BIT_RTCCE;
	}
 #else
	if (key == RTC_ON){
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTCCE));	/** RTCチップ・イネーブル	*/
	}
	else {
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCE));	/** RTCチップ・イネーブル	*/
	}
 #endif
}
/*************************************************************************
	module		:[ＲＴＣドライバ関数（ＲＸ５Ｃ３３８Ａ専用）]
	function	:[
		1.ＲＴＣ＿ＯＮでポートを立てます
		2.ＲＴＣ＿ＯＮでポートを下げます
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2004/10/27]
	author		:[Y.Tanaka]
*************************************************************************/
void	RTC_DRV_SCLK(UBYTE key)
{
 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	if (key == RTC_ON){
		IO__PEDR |= IO_BIT_RTCCK;
	}
	else {
		IO__PEDR &= ~IO_BIT_RTCCK;
	}
 #else
	if (key == RTC_ON){
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTCCLK));	/** RTCチップ・イネーブル	*/
	}
	else {
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCCLK));	/** RTCチップ・イネーブル	*/
	}
 #endif
}
/*************************************************************************
	module		:[ＲＴＣドライバ関数（ＲＸ５Ｃ３３８Ａ専用）]
	function	:[
		1.ＲＴＣ＿ＯＮでポートを立てます
		2.ＲＴＣ＿ＯＮでポートを下げます
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2004/10/27]
	author		:[Y.Tanaka]
*************************************************************************/
void	RTC_DRV_SIO(UBYTE key)
{
 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	if (key == RTC_ON){
		IO__PEDR |= IO_BIT_RTCDT;
	}
	else {
		IO__PEDR &= ~IO_BIT_RTCDT;
	}
 #else
	if (key == RTC_ON){
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_RTCDT));	/** RTCチップ・イネーブル	*/
	}
	else {
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_RTCDT));	/** RTCチップ・イネーブル	*/
	}
 #endif
}
/*************************************************************************
	module		:[ＲＴＣドライバ関数（ＲＸ５Ｃ３３８Ａ専用）]
	function	:[
		1.ポートの状態を読み込みます
	]
	return		:[
		RTC_ON	ポートが立っている
		RTC_OFF	ポートが落ちている
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2004/10/27]
	author		:[Y.Tanaka]
*************************************************************************/
UBYTE	RTC_DRV_GET_SIO(void)
{
	if (IO__PEDR & IO_BIT_RTCDT){
		return RTC_ON;
	}
	else {
		return RTC_OFF;
	}
}
/*************************************************************************
	module		:[ＲＴＣドライバ関数（ＲＸ５Ｃ３３８Ａ専用）]
	function	:[
		1.ＲＴＣ＿ＯＮでポートを立てます
		2.ＲＴＣ＿ＯＮでポートを下げます
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2004/10/27]
	author		:[Y.Tanaka]
*************************************************************************/
void	RTC_DRV_CLKC(UBYTE key)
{
 #if (PRO_RTC_INTERNAL_IO == ENABLE)				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	if (key == RTC_ON){
		IO__PEDR |= IO_BIT_CCLK;
	}
	else {
		IO__PEDR &= ~IO_BIT_CCLK;
	}
 #else
	if (key == RTC_ON){
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus |= IO_BIT_CCLK));	/** RTCチップ・イネーブル	*/
	}
	else {
		outpw(RTC_PORT, (UWORD)(SYS_RTC_PortStatus &= ~IO_BIT_CCLK));	/** RTCチップ・イネーブル	*/
	}
 #endif
}
/*************************************************************************
	module		:[ＲＴＣ入出力許可]
	function	:[
		1.ＲＴＣにデータの読み書きを許可します(true)
		2.ＲＴＣにデータの読み書きを禁止にします(false)
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2004/10/27]
	author		:[Y.Tanaka]
*************************************************************************/
void	RTC_IO_Enable(UBYTE is_permit)
{
	if (is_permit == RTC_RW_PERMIT){
		RTC_DRV_SCLK(RTC_OFF);						/* 念のため、読み書き許可にする前に同期クロックを下げておきます */
		RTC_DRV_CE(RTC_ON);							/* 読み書き許可 */
	}
	else {
		RTC_DRV_CE(RTC_OFF);						/* 読み書き禁止 */
		RTC_DRV_SCLK(RTC_OFF);						/* 読み書き禁止にしたら同期クロックを下げます */
	}
	wai_tsk(1);										/* 許可／禁止後、一定時間あけること */
}
/*************************************************************************
	module		:[ＲＴＣに同期クロックを送る]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2004/10/27]
	author		:[Y.Tanaka]
*************************************************************************/
void	RTC_Execute(void)							/* とりあえずこの関数使ってません */
{
	RTC_DRV_SCLK(RTC_ON);
	RTC_DRV_SCLK(RTC_OFF);
}
/*************************************************************************
	module		:[ＲＴＣのシリアル入出力にデータを送出]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2004/10/27]
	author		:[Y.Tanaka]
*************************************************************************/
void	RTC_OutputData(UBYTE data)
{
	UBYTE cnt;
	UBYTE ByteToBit[8] = {
		0x80,	0x40,	0x20,	0x10,
		0x08,	0x04,	0x02,	0x01
	};

	for (cnt = 0; cnt < 8; cnt++){
		RTC_DRV_SCLK(RTC_ON);
		if (data & ByteToBit[cnt]){
			RTC_DRV_SIO(RTC_ON);
		}
		else {
			RTC_DRV_SIO(RTC_OFF);
		}
		wai_tsk(1);						/* 入力データセットアップ期間の確保 */
		RTC_DRV_SCLK(RTC_OFF);
/*		wai_tsk(1);*/						/* 入力データホールド期間の確保 */
	}
}
/*************************************************************************
	module		:[ＲＴＣのシリアル入出力よりデータを受信]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2004/10/27]
	author		:[Y.Tanaka]
*************************************************************************/
UBYTE	RTC_InputData(void)
{
	UBYTE data;
	UBYTE cnt;
	UBYTE ByteToBit[8] = {
		0x80,	0x40,	0x20,	0x10,
		0x08,	0x04,	0x02,	0x01
	};

	data = 0;

	for (cnt = 0; cnt < 8; cnt++){
		RTC_DRV_SCLK(RTC_ON);
		wai_tsk(1);							/* データ出力遅延時間以上、待機する */
		if (RTC_DRV_GET_SIO() == RTC_ON){
			data += ByteToBit[cnt];
		}
		RTC_DRV_SCLK(RTC_OFF);
/*		wai_tsk(1);*/							/* SCLKクロック"L"時間を確保する */
	}
	return data;
}
/*************************************************************************
	module		:[ＲＴＣの初期化]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2004/10/27]
	author		:[Y.Tanaka]
*************************************************************************/
void ManInitRTC(void)
{
	UBYTE ControlData1;
	UBYTE ControlData2;

	ControlData1 = 0x20;										/**  暫定 */
	ControlData2 = 0x20;										/**  暫定 */

	RTC_DRV_CLKC(RTC_ON);										/**  クロック発信させます */
	RTC_IO_Enable(RTC_RW_PERMIT);								/**  書き込み許可		*/

	WriteClockBit(ControlData1, CONTROL1_REGISTER);				/**  分データ書き込み 	*/
	WriteClockBit(ControlData2, CONTROL2_REGISTER);				/**  分データ書き込み 	*/

	RTC_IO_Enable(RTC_RW_FORBIT);								/**  書き込み禁止		*/
}
#endif
