/************************************************************************
*	System		: SAKAKI
*	File Name	: CMN_GAIO.C
*	Author		: 吉川弘康
*	Date		: 1998/06/06
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	:
*	Maintenance	: MOMIJI用からSAKAKI用に変更した。
*				  MD9401/MD9402へのアクセスはWORDで行うように変更する。MOMIJIではBYTEであった。
*				  該当する変数をUBYTEからUWORDに変更する。1998/06/25
*	Copyright (C) 1998 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
/*----------------------------------------------------------------------*/
/* プロジェクト : SAKAKI												*/
/* ファイル名   : CMN_GAIO.C                                            */
/* モジュール名															*/
/*              : void	CutterDrive1_On(void)							*/
/*              : void	CutterDrive1_Off(void)							*/
/*              : void	CutterDrive2_On(void)							*/
/*              : void	CutterDrive2_Off(void)							*/
/*              : UWORD	CutterSensor1(void)								*/
/*              : UWORD	CutterSensor2(void)								*/
/*              : void	Pst(void)										*/
/*              : void	ModemToneOutSelect(UBYTE)             			*/
/*              : void	SpeakerOutSelect(i)                             */
/*              : void	LineOutSelect(i)                                */
/*              : void	BatteryCheckEnable(void)                        */
/*              : void	BatteryCheckDisable(void)                       */
/*              : void	SpeakerMuteOn(void)                             */
/*              : void	SpeakerMuteOff(void)                            */
/*              : void	MonitorSpeakerOn(void)                          */
/*              : void	TadMonitorSpeakerOn(void)                       */
/*              : void	MonitorSpeakerOff(void)                         */
/*              : void	HoldMelodyOn(void)                              */
/*              : void	HoldMelodyOff(void)                             */
/*              : void	TadPDNOn(void)                                  */
/*              : void	TadPDNOff(void)                                 */
/*              : void	TadResetOn(void)                                */
/*              : void	TadResetOff(void)                               */
/*				: UWORD	DIONEnable(void)               					*/
/*              : void	Ctscan(void)                                    */
/*              : void	GaInterruptEnable(void)                         */
/*              : void	GaInterruptDisable(void)                        */
/*              : void	WhiteCheckFF_Clr(void)                          */
/*				: void	ExternalBusEnable(void)                         */
/*				: void	ExternalBusDisable(void)                        */
/*				: void	Trig10mS(void)                                  */
/*              : void	Trig5mS(void)                                   */
/*              : UWORD	PrintBusy(void) 		                        */
/*              : UWORD	ScnMotorBusy(void)      		                */
/*              : UWORD	PrintMotorBusy(void)            		        */
/*              : UWORD	HeatPulseBusy(void)                     		*/
/*              : UWORD	WhiteDataCheck(void)               			    */
/*              : UWORD	G03_IRQ_Check(void)               			    */
/*              : UWORD	LineBufferDataOutBusy(void)             		*/
/*              : UWORD	LineBufferDataInBusy(void)              		*/
/*              : void	LineBufferDataInEnable(void)                    */
/*              : void	LineBufferDataInDisable(void)                   */
/*              : void	LineBufferDataOutEnable(void)                   */
/*              : void	LineBufferDataOutDisable(void)                  */
/*              : void	LineBufferChange(void)                          */
/*              : UWORD	LineBufferCheck(void)                 			*/
/*              : void	LineBufferAutoChangeEnable(void)                */
/*              : void	LineBufferAutoChangeDisable(void)               */
/*              : void	HeatPulseSet(i)                                 */
/*              : void  HeatPulseEnable(void)                           */
/*              : void  HeatPulseDisable(void)                          */
/*              : void	THControlRegisterInitialSet(i)                  */
/*              : void	ScnMotorInitialSet(void)                        */
/*              : void	PrintMotorInitialSet(void)                      */
/*              : void	Smst(void)                                      */
/*              : void	Smrst(void)                                     */
/*              : void	SmenOn(void)                                    */
/*              : void	SmenOff(void)                                   */
/*              : void	ScnMotorFw(void)                                */
/*              : void	ScnMotorRev(void)                               */
/*              : void	ScnMotorPhase12(void)                           */
/*              : void	ScnMotorPhase2(void)                            */
/*              : void	ScnMotorSpeed(i)                                */
/*              : void	ScnMotorStepSet(i)                              */
/*              : void	Pmst(void)                                      */
/*              : void	Pmrst(void)                                     */
/*              : void	PmenOn(void)                                    */
/*              : void	PmenOff(void)                                   */
/*              : void	PrintMotorFw(void)                              */
/*              : void	PrintMotorRev(void)                             */
/*              : void	PrintMotorPhase12(void)                         */
/*              : void	PrintMotorPhase2(void)                          */
/*              : void	PrintMotorSpeed(i)                              */
/*              : void	PrintMotorStepSet(i)                            */
/*              : void  LineBufferInputAddressSet(start,end)            */
/*              : void  LineBufferInputEndAddress(i)                    */
/*              : void	InnerMemorySelect1_GA(void)                     */
/*              : void	InnerMemorySelect1_CPU(void)                    */
/*              : void	InnerMemorySelect2_TH(void)                     */
/*              : void	InnerMemorySelect2_FN(void)                     */
/*              : void	InnerMemoryAccessA8_0(void)                     */
/*              : void	InnerMemoryAccessA8_1(void)                     */
/*              : void	PrintSpeed_10ms(void)                           */
/*              : void	PrintSpeed_5ms(void)                            */
/*              : void	ExpandBusSelectMMODE2(void)                     */
/*              : void	ExpandBusSelectSerial(void)                     */
/*              : void	ThermalHeadSizeA4(void)                         */
/*              : void	ThermalHeadSizeB4(void)                         */
/*              : void	FineNormalChangeSizeA4(void)                    */
/*              : void	FineNormalChangeSizeB4(void)                    */
/*              : void	FineNormalChangePattern1(void)                  */
/*              : void	FineNormalChangePattern2(void)                  */
/*              : void	DIONClear(void)                                 */
/*              : void	DIONSet(void)                                   */
/*              : void	IE1EN_On(void)                                  */
/*              : void	IE1EN_Off(void)                                 */
/*              : void	IE2EN_On(void)                                  */
/*              : void	IE2EN_Off(void)                                 */
/*				: void  IRQINT_5msSet(void)                             */
/*              : void	IRQINT_10msSet(void)                            */
/*				: void	IRQInterval_0mS(void)                           */
/*				: void	IRQInterval_1_25mS(void)                        */
/*				: void	IRQInterval_2_5mS(void)                         */
/*              : void	IRQInterval_3_75mS(void)                        */
/*				: void  FN_LineBufferEndAddressSet(UBYTE) 			    */
/*              : void	Cmst(void)                                      */
/*              : void	Cmrst(void)                                     */
/*              : void	CmenOn(void)                                    */
/*              : void	CmenOff(void)                                   */
/*              : void	CassetMotorFw(void)                             */
/*              : void	CassetMotorRev(void)                            */
/*              : void	CassetMotorPhase12(void)                        */
/*              : void	CassetMotorPhase2(void)                         */
/*              : void	CassetMotorSpeed(i)                             */
/*              : void	CassetMotorStepSet(i)                           */
/* 作成者名     : 大西                                                  */
/* 日  付       : 93.11.26                                              */
/* 概  要       : Gate-Array のI/Oサブルーチン集	                    */
/* 修正履歴     : Feb,28th,1994 By O.K 共通化の為。又、変更が発生した   */
/*              : 場合には、H8/V53の両方のソースを変更してください。    */
/*----------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"	/* プロダクト定義	*/
#include "\src\atlanta\ext_v\sys_port.h"	/** for Debug **/
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\ini_tbl.h"

#include "\src\atlanta\sakaki\define\gaio_pro.h"
#include "\src\atlanta\sakaki\define\sakiport.h"
#include "\src\atlanta\sakaki\define\saki_sys.h"
#include "\src\atlanta\sakaki\ext_v\ga_data.h"
#include "\src\atlanta\sakaki\ext_v\dcp_data.h"
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#include "\src\atlanta\define\mntsw_e.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\idp_def.h"	/** 位相ずれ By O.K Jan,20,1995 **/
#include "\src\atlanta\define\idp_pro.h"	/** 位相ずれ By O.K Jan,20,1995 **/
#include "\src\atlanta\define\std.h"

extern UWORD INT_SP_Counter;	/** Dual By O.K Aug,18,1994 **/
extern UBYTE INT_ScanSkipCounter;	/* 1998/09/10 */
extern UBYTE  DIPPST_Req;		/* 1998/06/13 H.Yoshikawa */

/* SAKAKIでも現在設定されている記録方式を PrintType で識別している。*/
/*#include "\src\atlanta\sakaki\ext_v\prn_data.h"*/

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
	M02_Status |= IO_BIT_CDRV1;
	outpw(MD9402_M02_PORT,M02_Status);
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
	M02_Status &= ~IO_BIT_CDRV1;
	outpw(MD9402_M02_PORT,M02_Status);
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
	M02_Status |= IO_BIT_CDRV2;
	outpw(MD9402_M02_PORT,M02_Status);
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
	M02_Status &= ~IO_BIT_CDRV2;
	outpw(MD9402_M02_PORT,M02_Status);
}

/******************************************************************************
	module		:[カッターセンサー１の出力]
	function	:[
		1.カッターセンサー１（左側のセンサー）の状態を示す
	]
	return		:[
		0:カッターセンサー１上にカッターが無い
		1:カッターセンサー１上にカッターがある
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1998/6/15]
	author		:[K.Kawata]
******************************************************************************/
UWORD  CutterSensor1(void)
{
	if(inpw(MD9402_M02_PORT) & IO_BIT_XCIS1) {
		return(0);
	}
	else {
		return(1);
	}
}

/******************************************************************************
	module		:[カッターセンサー２の出力]
	function	:[
		1.カッターセンサー２（右側のセンサー）の状態を示す
	]
	return		:[
		0:カッターセンサー２上にカッターが無い
		1:カッターセンサー２上にカッターがある
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1998/6/15]
	author		:[K.Kawata]
******************************************************************************/
UWORD CutterSensor2(void)
{
	if(inpw(MD9402_M02_PORT) & IO_BIT_XCIS2) {
		return(0);
	}
	else {
		return(1);
	}
}



/******************************************************************************
	module		:[IPシリアルデータ有無チェック]
	function	:[
		1.IPからG/Aへシリアルデータが出力されたかどうか見ます。
	]
	return		:[
		0:出力データ無し
		1:出力データ有り
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1994/03/10]
	author		:[宮崎仁一]
******************************************************************************/
UWORD DIONEnable(void)
{
	if(inpw(STCR5_PORT) & IO_BIT_PDION) {
		return(1);
	}
	else {
		return(0);
	}
}

/******************************************************************************
	module		:[ＤＩＰＰスタート]
	function	:[
		1.ＣＴＳＣＡＮ信号をＯＮ－ＯＦＦして読み込みスタートします
	]
	return		:[なし]
	common		:[なし]
	comment     :[
		1.CTSCAN信号はポートに２度書き込みます
	]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
void Ctscan(void)
{
	SYSCR_Status |= IO_BIT_AST;
	outpw(SYSCR_PORT,SYSCR_Status);
	outpw(SYSCR_PORT,SYSCR_Status);
	SYSCR_Status &= ~IO_BIT_AST;
	outpw(SYSCR_PORT,SYSCR_Status);
}

/******************************************************************************
	module		:[プリンタスタート]
	function	:[
		1.ＰＳＴ信号をＯＮ－ＯＦＦして記録スタートします
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
void Pst(void)
{

	SYSCR_Status |= ((IO_BIT_BST | IO_BIT_CST) & ~PrintType);	/** ＲＸモーターとＩＤＦモーター **/
	outpw(SYSCR_PORT,SYSCR_Status);
	SYSCR_Status &= ((~IO_BIT_BST & ~IO_BIT_CST) & ~PrintType);
	outpw(SYSCR_PORT,SYSCR_Status);
}

/******************************************************************************
	module		:[G/Aインターバル割り込み発生許可]
	function	:[
		1.ゲートアレーからＣＰＵに対してインターバル割り込み(10ms/5ms)を
		  発生させることを許可します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
void GaInterruptEnable(void)
{
	if (!GaInterruptFlag) {
		M03_Status |= IO_BIT_IRQEN;
		outpw(MD9402_M03_PORT,M03_Status);
		INT_SP_Counter = 0;
		INT_ScanSkipCounter = 0;	/* 1998/09/10 */
	}
}

/******************************************************************************
	module		:[G/Aインターバル割り込み発生禁止]
	function	:[
		1.ゲートアレーからＣＰＵに対してインターバル割り込み(10ms/5ms)を
		  発生させることを禁止します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
void GaInterruptDisable(void)
{
	if (!GaInterruptFlag) {
		M03_Status &= ~IO_BIT_IRQEN;
		outpw(MD9402_M03_PORT,M03_Status);
		INT_SP_Counter = 0;
	}
}

/******************************************************************************
	module		:[全白検出Ｆ／Ｆクリア]
	function	:[
		1.全白検出ビット（ＸＷＨＩＴＥ）をクリアします
		 .読み取り／記録ラインの開始時に呼びます
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
void WhiteCheckFF_Clr(void)
{
	M03_Status |= IO_BIT_WDCLR1;
	outpw(MD9402_M03_PORT,M03_Status);
	M03_Status &= ~IO_BIT_WDCLR1;
	outpw(MD9402_M03_PORT,M03_Status);
}

void WhiteCheckFF_Clr2(void)
{
	M03_Status |= IO_BIT_WDCLR2;
	outpw(MD9402_M03_PORT,M03_Status);
	M03_Status &= ~IO_BIT_WDCLR2;
	outpw(MD9402_M03_PORT,M03_Status);
}

/******************************************************************************
	module		:[TRIG周期 10mS設定]
	function	:[
		1.TRIG周期を10mSに設定します。
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1994/03/24]
	author		:[宮崎仁一]
******************************************************************************/
void Trig10mS(void)
{
	M03_Status &= ~(UBYTE)(IO_BIT_TSEL0 | IO_BIT_TSEL1);
	M03_Status |= (UBYTE)(IO_BIT_TSEL0 | IO_BIT_TSEL1);
	outpw(MD9402_M03_PORT,M03_Status);
}

/******************************************************************************
	module		:[TRIG周期 5mS設定]
	function	:[
		1.TRIG周期を5mSに設定します。
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1994/03/24]
	author		:[宮崎仁一]
******************************************************************************/
void Trig5mS(void)
{
	M03_Status &= ~(UBYTE)(IO_BIT_TSEL0 | IO_BIT_TSEL1);
	M03_Status |= IO_BIT_TSEL1;
	outpw(MD9402_M03_PORT,M03_Status);
}

/******************************************************************************
	module		:[プリンター動作中]
	function	:[
		1.ポートＧ０３の PBSY ビットをチェックし、プリント中かどうか判断します
	]
	return		:[
					0:プリント終了
					1:プリント中
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
UWORD PrintBusy(void)
{
	if(inpw(SCR_PORT) & IO_BIT_PBST) {
		return(1);
	}
	else {
		return(0);
	}
}

/******************************************************************************
	module		:[スキャナモーター動作中]
	function	:[
		1.ポートＧ０３の SMBSY ビットをチェックし、スキャナモーターが動作中
		 .かどうか判断します
	]
	return		:[
					0:停止
					1:動作中
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
UWORD ScnMotorBusy(void)
{
	if(inpw(SCR_PORT) & IO_BIT_AMBSY) {
		return(1);
	}
	else {
		return(0);
	}
}

/******************************************************************************
	module		:[プリンタモーター動作中]
	function	:[
		1.ポートＧ０３の PMBSY ビットをチェックし、プリンタモーターが動作中
		 .かどうか判断します
	]
	return		:[
					0:停止
					1:動作中
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
UWORD PrintMotorBusy(void)
{
	if(inpw(SCR_PORT) & IO_BIT_BMBSY) {
		return(1);
	}
	else {
		return(0);
	}
}

/******************************************************************************
	module		:[Ｔ／Ｈ印加パルス出力中]
	function	:[
		1.ポートＧ０３の STBBSY ビットをチェックし、T/H印加パルス出力中か
		 .どうか判断します
	]
	return		:[
					0:停止
					1:印加中
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
UWORD HeatPulseBusy(void)
{
	if(inpw(SCR_PORT) & IO_BIT_STBBSY) {
		return(1);
	}
	else {
		return(0);
	}
}

/******************************************************************************
	module		:[全白チェック]
	function	:[
		1.ポートＧ０３の XWHITE ビットをチェックし、プリント／スキャンのデータ
		 .が全白か判断します
	]
	return		:[
					0:全白ではない
					1:全白
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/26]
	author		:[大西亨]
******************************************************************************/
UWORD WhiteDataCheck(void)
{
	if(inpw(MD9402_M04_PORT) & IO_BIT_XWHITE1) {
		return(0);
	}
	else {
		return(1);
	}
}

UWORD WhiteDataCheck2(void)
{
	if(inpw(MD9402_M04_PORT) & IO_BIT_XWHITE2) {
		return(0);
	}
	else {
		return(1);
	}
}

/******************************************************************************
	module		:[割り込み要求ビットチェック]
	function	:[
		1.ポートＧ０３の IRQ ビットをチェックします
	]
	return		:[
					0:待機
					1:割り込み要求有り
					(注）G/Aテスト用で特に使用する必要はない
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
UWORD G03_IRQ_Check(void)
{
	if(inpw(MD9402_M04_PORT) & IO_BIT_IRQ) {
		return(1);
	}
	else {
		return(0);
	}
}

/******************************************************************************
	module		:[ラインメモリ出力中]
	function	:[
		1.ポートＧ０３の DOBSY ビットをチェックします
	]
	return		:[
					0:待機
					1:ラインメモリ出力中
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
UWORD LineBufferDataOutBusy(void)
{
	if(inpw(SCR_PORT) & IO_BIT_PDOBSY) {
		return(1);
	}
	else {
		return(0);
	}
}

/******************************************************************************
	module		:[ラインメモリ入力中]
	function	:[
		1.ポートＧ０３の DIBSY ビットをチェックします
	]
	return		:[
					0:待機
					1:ラインメモリ入力中
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
UWORD LineBufferDataInBusy(void)
{
	if(inpw(SCR_PORT) & IO_BIT_PDIBSY) {
		return(1);
	}
	else {
		return(0);
	}
}

/******************************************************************************
	module		:[ラインバッファ切り換え]
	function	:[
		1.呼ばれる毎にポートＧ０４の LCHG ビットを 1->0 , 0->1 へ切り換えます
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void LineBufferChange(void)
{
	TRCR_Status ^= IO_BIT_LCHG;
	outpw(TRCR_PORT,TRCR_Status);
}

/******************************************************************************
	module		:[ラインメモリ選択チェック]
	function	:[
		1.G/Aのラインメモリ(#1/#2)のどちらが選択されているか示します
	]
	return		:[
					0:ラインメモリ＃１が選択されている
					1:ラインメモリ＃２が選択されている
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
UWORD LineBufferCheck(void)
{
	if(inpw(TRCR_PORT) & IO_BIT_LCHG) {
		return(1);
	}
	else {
		return(0);
	}
}

/******************************************************************************
	module		:[ラインメモリ自動選択許可]
	function	:[
		1.ポートＧ０４の LCHGAUTO ビットを "1" にセットして自動選択を許可します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void LineBufferAutoChangeEnable(void)
{
	TRCR_Status |= IO_BIT_LCHGAUTO;
	outpw(TRCR_PORT,TRCR_Status);
}

/******************************************************************************
	module		:[ラインメモリ自動選択禁止]
	function	:[
		1.ポートＧ０４の LCHGAUTO ビットを "0" にセットして自動選択を禁止します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void LineBufferAutoChangeDisable(void)
{
	TRCR_Status &= ~IO_BIT_LCHGAUTO;
	outpw(TRCR_PORT,TRCR_Status);
}

/******************************************************************************
	module		:[ラインメモリデータ入力許可]
	function	:[
		1.ポートＧ０４の DIEN ビットを "1" にセットしてラインメモリデータの
		 .入力を許可します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい**--> reprint preheat で使用する***/

void LineBufferDataInEnable(void)
{
	TRCR_Status |= IO_BIT_DIEN;
	outpw(TRCR_PORT,TRCR_Status);
}

/******************************************************************************
	module		:[ラインメモリデータ入力禁止]
	function	:[
		1.ポートＧ０４の DIEN ビットを "0" にセットしてラインメモリデータの
		 .入力を禁止します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい**--> reprint preheat で使用する***/

void LineBufferDataInDisable(void)
{
	TRCR_Status &= ~IO_BIT_DIEN;
	outpw(TRCR_PORT,TRCR_Status);
}


/******************************************************************************
	module		:[ラインメモリデータ出力許可]
	function	:[
		1.ポートＧ０４の DOEN ビットを "1" にセットしてラインメモリデータの
		 .出力を許可します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい***--> preheat reprint で使用 ******/

void LineBufferDataOutEnable(void)
{
	TRCR_Status |= IO_BIT_DOEN;
	outpw(TRCR_PORT,TRCR_Status);
}

/******************************************************************************
	module		:[ラインメモリデータ出力禁止]
	function	:[
		1.ポートＧ０４の DOEN ビットを "0" にセットしてラインメモリデータの
		 .出力を禁止します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい***--> preheat reprint で使用 ******/

void LineBufferDataOutDisable(void)
{
	TRCR_Status &= ~IO_BIT_DOEN;
	outpw(TRCR_PORT,TRCR_Status);
}

/******************************************************************************
	module		:[サーマルヘッドラッチパルス出力許可]
	function	:[
		1.ポートＧ０４の LTEN ビットを "1" にセットしてサーマルヘッドのラッチパ
		 .ルスの出力を許可します
		 .三菱ラッチ型のサーマルヘッド使用時のみ
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい******************************/
void THLatchEnable(void)
{
	TRCR_Status |= IO_BIT_LTEN;
	outpw(TRCR_PORT,TRCR_Status);
}

/******************************************************************************
	module		:[サーマルヘッドラッチパルス出力禁止]
	function	:[
		1.ポートＧ０４の LTEN ビットを "0" にセットしてサーマルヘッドのラッチパ		 	 .ルスの出力を禁止します
		 .ロームＧＡ，ロームＧＢ，京セラＫＺＴのサーマルヘッド使用時のみ
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい********************************/
void THLatchDisable(void)
{
	TRCR_Status &= ~IO_BIT_LTEN;
	outpw(TRCR_PORT,TRCR_Status);
}

/******************************************************************************
	module		:[サーマルヘッドラッチパルス出力極性選択]
	function	:[
		1.入力パラメータにより、ポートＧ０４の LTPOR ビットを "0"or"1" にセット		 	 .します
		 .通常、負極性のままでよい
		 .電源ＯＮ時のＧ／Ａ初期設定でセットするのでコメントとします
		 .パラメータ
		 	#define	THLT_POR_NEGA	0
		 	#define	THLT_POR_POSI	1
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい*********************************/
void THLatchPORSelect(i)
UBYTE	i;
{
	if(i == THLT_POR_NEGA) {
		TRCR_Status &= ~IO_BIT_LTPOR;
	}
	else {
		TRCR_Status |= IO_BIT_LTPOR;
	}
	outpw(TRCR_PORT,TRCR_Status);
}

/******************************************************************************
	module		:[サーマルヘッドヒートパルス設定]
	function	:[
		1.入力パラメータにより、ポートＧ０８にヒートパルス幅を設定します
		 .(注)入力パラメータは２４０より大きい数値は入れないこと
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void HeatPulseSet(i)
UBYTE	i;
{

	/** プリヒート時はラッチをＯＦＦします。 By O.K Dec,12,1994 **/
	if (PRN_Control.Command == PRN_PREHEAT_REQ) {
		TRCR_Status &= ~IO_BIT_LTEN;
	}
	else {
		TRCR_Status |= IO_BIT_LTEN;
	}
	outpw(TRCR_PORT,TRCR_Status);
	
	/*	STCR1_Status = (UBYTE)(0xff - i); */
	/** kurokoge taisaku By O.K Nov,29,1994 **/
	if (i < 0x03 ) {
		i = 0x03;
	}
	else if (i > 0xFA) {
		i = 0xFA;
	}
	STCR1_Status = (UBYTE)i;
	outpw(STCR1_PORT,STCR1_Status);
}

/******************************************************************************
	module		:[]
	function	:[]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/01/15]
	author		:[大西亨]
******************************************************************************/
void HeatPulseEnable(void)
{
	/* ストローブパルス出力イネーブル	*/
	STCR2_Status |= IO_BIT_STEN;
	outpw(STCR2_PORT,STCR2_Status);
}

/******************************************************************************
	module		:[]
	function	:[]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/01/15]
	author		:[大西亨]
******************************************************************************/
void HeatPulseDisable(void)
{
	/* ストローブパルス出力イネーブル	*/
	STCR2_Status &= ~IO_BIT_STEN;
	outpw(STCR2_PORT,STCR2_Status);
}

/******************************************************************************
	module		:[サーマルヘッドコントロールレジスタ初期設定]
	function	:[
		1.入力パラメータにより、ポートG04,G05,G06,G07,G09,G0A,G0B の値をセット
		 .します
		 .電源ＯＮ時の初期化時に設定するだけでよい
		 .パラメータ
		 	#define	TH_MITUBISHI	0
			#define TH_ROHM_GA		1
			#define	TH_ROHM_GB		2
			#define	TH_KYOSERA		3
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
#if (0)	/** 椛で使用するヘッドは京セラのみなので関数を削除してInitializeGateArray()で直接設定します By O.K Oct,28,1994 **/
void THControlRegisterInitialSet(i)
UBYTE	i;
{
	switch( i ) {
 #if (0)	/**  By O.K Sep,05,1994 **/
		case TH_ROHM_GA:
				TRCR_Status = 0x0C;
				outpw(TRCR_PORT,TRCR_Status);
				TROSS_Status = 0x00;
				outpw(TROSS_PORT,TROSS_Status);
				TROF1_Status = 0x10;
				outpw(TROF1_PORT,TROF1_Status);
				TROF2_Status = 0x40;
				outpw(TROF2_PORT,TROF2_Status);
				STCR2_Status = 0x10;
				outpw(STCR2_PORT,STCR2_Status);
				STCR3_Status = 0x00;
				outpw(STCR3_PORT,STCR3_Status);
				STCR4_Status = 0x00;
				outpw(STCR4_PORT,STCR4_Status);
				break;
 #endif
		case TH_ROHM_GB:
				TRCR_Status = 0x8C;
				outpw(TRCR_PORT,TRCR_Status);
				TROSS_Status = 0x80;
				outpw(TROSS_PORT,TROSS_Status);
				if(THDM()) {	/** ロームＧＢ型２０１６ドットタイプ **/
					TROF1_Status = 0x10;
					outpw(TROF1_PORT,TROF1_Status);
					TROF2_Status = 0x40;
					outpw(TROF2_PORT,TROF2_Status);
				}
				else {			/** ロームＧＢ型２０４８ドットタイプ **/
					TROF1_Status = 0x08;
					outpw(TROF1_PORT,TROF1_Status);
					TROF2_Status = 0x02;
					outpw(TROF2_PORT,TROF2_Status);
				}
				STCR2_Status = 0xA0;
				outpw(STCR2_PORT,STCR2_Status);
				STCR3_Status = 0x01;
				outpw(STCR3_PORT,STCR3_Status);
				STCR4_Status = 0x09;
				outpw(STCR4_PORT,STCR4_Status);
				break;
		case TH_KYOSERA:
		default:
				TRCR_Status = 0x5C;
				outpw(TRCR_PORT,TRCR_Status);
				TROSS_Status = 0x01;
				outpw(TROSS_PORT,TROSS_Status);
				TROF1_Status = 0x00;
				outpw(TROF1_PORT,TROF1_Status);
				TROF2_Status = 0x00;
				outpw(TROF2_PORT,TROF2_Status);
				STCR2_Status = 0xF0;
				outpw(STCR2_PORT,STCR2_Status);
				STCR3_Status = 0x00;
				outpw(STCR3_PORT,STCR3_Status);
				STCR4_Status = 0x00;
				outpw(STCR4_PORT,STCR4_Status);
				break;
 #if (0)
		case TH_MITUBISHI:
				TRCR_Status = 0x5C;
				outpw(TRCR_PORT,TRCR_Status);
				TROSS_Status = 0x01;
				outpw(TROSS_PORT,TROSS_Status);
				TROF1_Status = 0x00;
				outpw(TROF1_PORT,TROF1_Status);
				TROF2_Status = 0x00;
				outpw(TROF2_PORT,TROF2_Status);
				STCR2_Status = 0xF0;
				outpw(STCR2_PORT,STCR2_Status);
				STCR3_Status = 0x00;
				outpw(STCR3_PORT,STCR3_Status);
				STCR4_Status = 0x00;
				outpw(STCR4_PORT,STCR4_Status);
				break;
 #endif
	}
}
#endif

/******************************************************************************
	module		:[スキャナモーター初期設定]
	function	:[
		1.ポートG0C,G0Dの初期設定をする
		 .電源ＯＮ時の初期化時に設定するだけでよい
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		＜椛は８００ＰＰＳ、２相で初期化します。＞
	]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void ScnMotorInitialSet(void)
{
	A_MCR1_Status = 0x00;	/* SMSTで起動,励磁Off,遅延時間:0 */
	outpw(A_MCR1_PORT,A_MCR1_Status);
	A_MCR2_Status = 0x0C;	/* 正転,２相励磁,800PPS,ステップ数:0 */
	outpw(A_MCR2_PORT,A_MCR2_Status);
}

/******************************************************************************
	module		:[プリンタモーター初期設定]
	function	:[
		1.ポートG0E,G0Fの初期設定をする
		 .電源ＯＮ時の初期化時に設定するだけでよい
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		＜椛は、ＲＸモーターは２００ＰＰＳ、２相で、ＩＤＰモーターは２００ＰＰＳ、１ー２相です。＞
	]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PrintMotorInitialSet(void)
{
	B_MCR1_Status = 0x00;	/** ＲＸモーター **/
	outpw(B_MCR1_PORT,B_MCR1_Status);
	B_MCR2_Status = 0x04;/* 正転,２相励磁,200PPS,ステップ数:0 */
	outpw(B_MCR2_PORT,B_MCR2_Status);

	C_MCR1_Status = 0x00;	/** ＩＤＦモーター **/
	outpw(C_MCR1_PORT,C_MCR1_Status);
	C_MCR2_Status = 0x06;/* 正転,1-2相励磁,200PPS,ステップ数:0 */
	outpw(C_MCR2_PORT,C_MCR2_Status);
}

/******************************************************************************
	module		:[スキャナモーター起動]
	function	:[
		1.ポートG0CのSMSTビットをON-OFFしてスキャナモーターを回す
		 .
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void Smst(void)
{
	/*---------------------------------------------------------------------
	** スキャナカバーオープンしているときは、モータ起動させません。
	** SAKAKIには、インターロックがないので、この処理を追加しました。
	** 1998/10/08
	*/
	if (TXIL()) {
		SmenOff();
		return;
	}

	A_MCR1_Status |= IO_BIT_AMST;
	outpw(A_MCR1_PORT,A_MCR1_Status);
	A_MCR1_Status &= ~IO_BIT_AMST;
	outpw(A_MCR1_PORT,A_MCR1_Status);
}

/******************************************************************************
	module		:[スキャナモーター内部ＦＦリセット]
	function	:[
		1.ポートG0CのSMRSTビットをON-OFFしてスキャナモーターの内部フリップ
		 .フロップをリセットする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void Smrst(void)
{
	A_MCR1_Status |= IO_BIT_AMRST;
	outpw(A_MCR1_PORT,A_MCR1_Status);
	A_MCR1_Status &= ~IO_BIT_AMRST;
	outpw(A_MCR1_PORT,A_MCR1_Status);
}

/******************************************************************************
	module		:[スキャナモーター励磁イネーブルＯＮ]
	function	:[
		1.ポートG0CのSMENビットをONしてスキャナモーターの励磁をONする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void SmenOn(void)
{
	A_MCR1_Status |= IO_BIT_AMEN;
	outpw(A_MCR1_PORT,A_MCR1_Status);
#if (0)	/**  By O.K Oct,07,1994 **/
	SYS_ETC2_PortStatus |= (IO_BIT_TXI0 | IO_BIT_TXI1);	/** 電流制御ＯＮ **/
#endif

#if (0)	/* saki_sys.hに移動のため変更した 1998/07/10 */
//	SYS_ETC2_PortStatus &= ~MAX_LEVEL;
//	SYS_ETC2_PortStatus |= (UWORD)(SCN_IDP_Control.TxMotorCurrent);
//	outpw(ETC2_PORT,SYS_ETC2_PortStatus);
#endif

	/*---------------------------------------------------------------------
	** ES機では、論理が逆になっていますので、とりあえず、１００％固定にしておきます。
	** ES/CSを保守SWで切り替えできるようにします。
	** 1998/08/19
	*/
	if (SYB_MaintenanceSwitch[MNT_SW_E6] & SAKAKI_PCB_CS) {
/*		IO__PDDRH &= ~(IO_BIT_TXI0 | IO_BIT_TXI1);	1998/09/16 */

		switch (SCN_IDP_Control.TxMotorCurrent) {
		case LOW_LEVEL:		/* 0x0080	30% */
			IO__PDDRH &= ~IO_BIT_TXI0;	/* 1998/09/16 */
			IO__PDDRH |= IO_BIT_TXI1;
			break;
		case HIGH_LEVEL:	/* 0x0040	60% */
			IO__PDDRH |= IO_BIT_TXI0;
			IO__PDDRH &= ~IO_BIT_TXI1;	/* 1998/09/16 */
			break;
		case MAX_LEVEL:		/* 	0x00C0	100% */
/*			IO__PDDRH |= (IO_BIT_TXI0 | IO_BIT_TXI1);	1998/09/16 */
			IO__PDDRH |= IO_BIT_TXI0;	/* 1998/09/16 */
			IO__PDDRH |= IO_BIT_TXI1;	/* 1998/09/16 */
			break;
		case MIN_LEVEL:		/* 0x0000	0% */
		default:
			IO__PDDRH &= ~IO_BIT_TXI0;	/* 1998/09/16 */
			IO__PDDRH &= ~IO_BIT_TXI1;	/* 1998/09/16 */
			break;
		}
	}
	else {
/*		IO__PDDRH &= ~(IO_BIT_TXI0 | IO_BIT_TXI1);	1998/09/16 */
		IO__PDDRH &= ~IO_BIT_TXI0;
		IO__PDDRH &= ~IO_BIT_TXI1;
	}

}

/******************************************************************************
	module		:[スキャナモーター励磁イネーブルＯＦＦ]
	function	:[
		1.ポートG0CのSMENビットをOFFしてスキャナモーターの励磁をOFFする
		2.椛の場合はスキャナモーターの励磁をＯＦＦすると同時にクラッチの励磁も
		- 併せてＯＦＦする。
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void SmenOff(void)
{
	A_MCR1_Status &= ~IO_BIT_AMEN;
	outpw(A_MCR1_PORT,A_MCR1_Status);

#if (0)	/* saki_sys.hに移動のため変更した 1998/07/10 */
//	SYS_ETC2_PortStatus &= ~(IO_BIT_TXI0 | IO_BIT_TXI1);	/** 電流制御ＯＦＦ **/
//	outpw(ETC2_PORT,SYS_ETC2_PortStatus);
#endif

	/*---------------------------------------------------------------------
	** ES機では、論理が逆になっていますので、とりあえず、０％固定にしておきます。
	** ES/CSを保守SWで切り替えできるようにします。
	** 1998/08/19
	*/
	if (SYB_MaintenanceSwitch[MNT_SW_E6] & SAKAKI_PCB_CS) {
/*		IO__PDDRH &= ~(IO_BIT_TXI0 | IO_BIT_TXI1);	1998/09/16 */
		IO__PDDRH &= ~IO_BIT_TXI0;	/* 1998/09/16 */
		IO__PDDRH &= ~IO_BIT_TXI1;	/* 1998/09/16 */
	}
	else {
/*		IO__PDDRH |= (IO_BIT_TXI0 | IO_BIT_TXI1);	1998/09/16 */
		IO__PDDRH |= IO_BIT_TXI0;	/* 1998/09/16 */
		IO__PDDRH |= IO_BIT_TXI1;	/* 1998/09/16 */
	}

	ClutchOff();	/** テスト的にここにいれておきます。 **/
}


/******************************************************************************
	module		:[スキャナモーター正転]
	function	:[
		1.ポートG0DのSMDIRビットをOFFしてスキャナモーターの回転方向を正転にする
	]
	return		:[なし]
	common		:[
		ＲｅｖＡのメインはスキャナーモーターの回転方向が逆です
	]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void ScnMotorFw(void)
{
#if (0)
	A_MCR2_Status &= ~IO_BIT_AMDIR;
	outpw(A_MCR2_PORT,A_MCR2_Status);
#endif
	/** Ｒｅｖ.Cのメインはスキャナーモーターの回転方向が逆です **/
	A_MCR2_Status |= IO_BIT_AMDIR;
	outpw(A_MCR2_PORT,A_MCR2_Status);
}

/******************************************************************************
	module		:[スキャナモーター逆転]
	function	:[
		1.ポートG0DのSMDIRビットをONしてスキャナモーターの回転方向を逆転にする
	]
	return		:[なし]
	common		:[
		ＲｅｖＡのメインはスキャナーモーターの回転方向が逆です
	]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void ScnMotorRev(void)
{
#if (0)
	A_MCR2_Status |= IO_BIT_AMDIR;
	outpw(A_MCR2_PORT,A_MCR2_Status);
#endif
	/** Ｒｅｖ.Cのメインはスキャナーモーターの回転方向が逆です **/
	A_MCR2_Status &= ~IO_BIT_AMDIR;
	outpw(A_MCR2_PORT,A_MCR2_Status);
}

/******************************************************************************
	module		:[スキャナモーター1-2相励磁セット]
	function	:[
		1.ポートG0DのSMMODビットをONしてスキャナモーターの励磁を1-2相にする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void ScnMotorPhase12(void)
{
	ScnMotorPhase = PHASE_12;	/**  By O.K Sep,06,1994 **/
	A_MCR2_Status |= IO_BIT_AMMOD;
	outpw(A_MCR2_PORT,A_MCR2_Status);
}

/******************************************************************************
	module		:[スキャナモーター2相励磁セット]
	function	:[
		1.ポートG0DのSMMODビットをOFFしてスキャナモーターの励磁を2相にする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void ScnMotorPhase2(void)
{
	ScnMotorPhase = PHASE_2;	/**  By O.K Sep,06,1994 **/
	A_MCR2_Status &= ~IO_BIT_AMMOD;
	outpw(A_MCR2_PORT,A_MCR2_Status);
}

/******************************************************************************
	module		:[スキャナモータースピードセット]
	function	:[
		1.入力パラメータにより､ポートG0DのSMSPD0,SMSPD1をセットしてスキャナ
		 .モーターの連続回転時のスピードを設定する
		 .パラメータ
		 	#define	SCAN_100PPS		0x00
		 	#define	SCAN_200PPS		0x04
		 	#define	SCAN_400PPS		0x08
		 	#define	SCAN_800PPS		0x0C
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void ScnMotorSpeed(i)
UBYTE	i;
{
	A_MCR2_Status &= ~(IO_BIT_AMSPD0 | IO_BIT_AMSPD1);
	A_MCR2_Status |= i;
	outpw(A_MCR2_PORT,A_MCR2_Status);
}

/******************************************************************************
	module		:[スキャナモーターステップ数セット]
	function	:[
		1.入力パラメータにより､ポートG0DのSMSTEP0,SMSTEP1,SMSTEP2,SMSTEP3を
		 .セットしてスキャナモーターの連続回転ステップ数を設定する
		 .パラメータ
			0 ～ 15
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void ScnMotorStepSet(i)
UBYTE	i;
{
	A_MCR2_Status &= 0x0f;
	A_MCR2_Status |= (i << 4);
	outpw(A_MCR2_PORT,A_MCR2_Status);
}

/******************************************************************************
	module		:[プリンタモーター起動]
	function	:[
		1.ポートG0EのPMSTビットをON-OFFしてプリンタモーターを回す
		 .
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void Pmst(void)
{
	B_MCR1_Status |= IO_BIT_BMST;	/** ＲＸモーター **/
	outpw(B_MCR1_PORT,B_MCR1_Status);
	B_MCR1_Status &= ~IO_BIT_BMST;
	outpw(B_MCR1_PORT,B_MCR1_Status);
	if (!PrintType) {
		C_MCR1_Status |= IO_BIT_CMST;	/** ＩＤＦモーター **/
		outpw(C_MCR1_PORT,C_MCR1_Status);
		C_MCR1_Status &= ~IO_BIT_CMST;
		outpw(C_MCR1_PORT,C_MCR1_Status);
	}
}

/******************************************************************************
	module		:[プリンタモーター内部ＦＦリセット]
	function	:[
		1.ポートG0EのPMRSTビットをON-OFFしてプリンタモーターの内部フリップ
		 .フロップをリセットする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void Pmrst(void)
{
	B_MCR1_Status |= IO_BIT_BMRST;	/** ＲＸモーター **/
	outpw(B_MCR1_PORT,B_MCR1_Status);
	B_MCR1_Status &= ~IO_BIT_BMRST;
	outpw(B_MCR1_PORT,B_MCR1_Status);

	if(!PrintType) {
		C_MCR1_Status |= IO_BIT_CMRST;	/** ＩＤＦモーター **/
		outpw(C_MCR1_PORT,C_MCR1_Status);
		C_MCR1_Status &= ~IO_BIT_CMRST;
		outpw(C_MCR1_PORT,C_MCR1_Status);
	}
}

/******************************************************************************
	module		:[プリンタモーター励磁イネーブルＯＮ]
	function	:[
		1.ポートG0EのPMENビットをONしてプリンタモーターの励磁をONする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PmenOn(void)
{
	B_MCR1_Status |= IO_BIT_BMEN;	/** ＲＸモーター **/
	outpw(B_MCR1_PORT,B_MCR1_Status);

	if(!PrintType) {
		C_MCR1_Status |= IO_BIT_CMEN;	/** ＩＤＦモーター **/
		outpw(C_MCR1_PORT,C_MCR1_Status);
	}
}

/******************************************************************************
	module		:[プリンタモーター励磁イネーブルＯＦＦ]
	function	:[
		1.ポートG0EのPMENビットをOFFしてプリンタモーターの励磁をOFFする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PmenOff(void)
{
	B_MCR1_Status &= ~IO_BIT_BMEN;	/** ＲＸモーター **/
	outpw(B_MCR1_PORT,B_MCR1_Status);

	if(!PrintType) {
		C_MCR1_Status &= ~IO_BIT_CMEN;	/** ＩＤＦモーター **/
		outpw(C_MCR1_PORT,C_MCR1_Status);
	}
}

/******************************************************************************
	module		:[プリンタモーター正転]
	function	:[
		1.ポートG0FのPMDIRビットをONしてプリンタモーターの回転方向を正転にする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PrintMotorFw(void)
{
	B_MCR2_Status |= IO_BIT_BMDIR;	/** ＲＸモーター **/
	outpw(B_MCR2_PORT,B_MCR2_Status);
	if(!PrintType) {
		C_MCR2_Status |= IO_BIT_CMDIR;	/** ＩＤＦモーター **/
		outpw(C_MCR2_PORT,C_MCR2_Status);
	}
}

/******************************************************************************
	module		:[プリンタモーター逆転]
	function	:[
		1.ポートG0FのPMDIRビットをOFFしてプリンタモーターの回転方向を逆転にする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PrintMotorRev(void)
{
	B_MCR2_Status &= ~IO_BIT_BMDIR;	/** ＲＸモーター **/
	outpw(B_MCR2_PORT,B_MCR2_Status);
	if(!PrintType) {
		C_MCR2_Status &= ~IO_BIT_CMDIR;	/** ＩＤＦモーター **/
		outpw(C_MCR2_PORT,C_MCR2_Status);
	}
}

/******************************************************************************
	module		:[プリントモーター1-2相励磁セット]
	function	:[
		1.ポートG0FのPMMODビットをONしてプリントモーターの励磁を1-2相にする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PrintMotorPhase12(void)
{
	B_MCR2_Status |= IO_BIT_BMMOD;	/** ＲＸモーター **/
	outpw(B_MCR2_PORT,B_MCR2_Status);
/** #if (0) ＲＸモーターとＩＤＦモーターの設定を分けます。 By O.K Oct,28,1994 **/
	if(!PrintType) {
		C_MCR2_Status |= IO_BIT_CMMOD;	/** ＩＤＦモーター **/
		outpw(C_MCR2_PORT,C_MCR2_Status);
	}
/** #endif**/
}

/******************************************************************************
	module		:[プリントモーター1-2相励磁セット]
	function	:[
		1.ポートG0FのPMMODビットをONしてプリントモーターの励磁を1-2相にする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void IDFMotorPhase12(void)
{
#if (0)	/** ＲＸモーターとＩＤＦモーターの設定を分けます。 By O.K Oct,28,1994 **/
	B_MCR2_Status |= IO_BIT_BMMOD;	/** ＲＸモーター **/
	outpw(B_MCR2_PORT,B_MCR2_Status);
#endif
	if(!PrintType) {
		C_MCR2_Status |= IO_BIT_CMMOD;	/** ＩＤＦモーター **/
		outpw(C_MCR2_PORT,C_MCR2_Status);
	}
}

/******************************************************************************
	module		:[プリントモーター2相励磁セット]
	function	:[
		1.ポートG0FのPMMODビットをOFFしてプリントモーターの励磁を2相にする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PrintMotorPhase2(void)
{
	B_MCR2_Status &= ~IO_BIT_BMMOD;	/** ＲＸモーター **/
	outpw(B_MCR2_PORT,B_MCR2_Status);
/**#if (0)ＲＸモーターとＩＤＦモーターの設定を分けます By O.K Oct,28,1994 **/
	if(!PrintType) {
		C_MCR2_Status &= ~IO_BIT_CMMOD;	/** ＩＤＦモーター **/
		outpw(C_MCR2_PORT,C_MCR2_Status);
	}
/**#endif**/
}

/******************************************************************************
	module		:[プリントモーター2相励磁セット]
	function	:[
		1.ポートG0FのPMMODビットをOFFしてプリントモーターの励磁を2相にする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void IDFMotorPhase2(void)
{
 #if (0)
	B_MCR2_Status &= ~IO_BIT_BMMOD;	/** ＲＸモーター **/
	outpw(B_MCR2_PORT,B_MCR2_Status);
 #endif
	if(!PrintType) {
		C_MCR2_Status &= ~IO_BIT_CMMOD;	/** ＩＤＦモーター **/
		outpw(C_MCR2_PORT,C_MCR2_Status);
	}
}

/******************************************************************************
	module		:[プリンタモータースピードセット]
	function	:[
		1.入力パラメータにより､ポートG0FのPMSPD0,PMSPD1をセットしてプリンタ
		 .モーターの連続回転時のスピードを設定する
		 .パラメータ
		 	#define	PRINT_100PPS	0x00
		 	#define	PRINT_200PPS	0x04
		 	#define	PRINT_400PPS	0x08
		 	#define	PRINT_800PPS	0x0C
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PrintMotorSpeed(i)
UBYTE	i;
{
	B_MCR2_Status &= ~(IO_BIT_BMSPD0 | IO_BIT_BMSPD1);
	B_MCR2_Status |= i;
	outpw(B_MCR2_PORT,B_MCR2_Status);
	if(!PrintType) {
		C_MCR2_Status &= ~(IO_BIT_CMSPD0 | IO_BIT_CMSPD1);
		/** C_MCR2_Status |= (i>>1);	ＩＤＰモーターは１／２相なのでパルス速度はＲＸモーターと同一 **/
		C_MCR2_Status |= i;
		outpw(C_MCR2_PORT,C_MCR2_Status);
	}
}

/******************************************************************************
	module		:[プリントモーターステップ数セット]
	function	:[
		1.入力パラメータにより､ポートG0FのPMSTEP0,PMSTEP1,PMSTEP2,PMSTEP3を
		 .セットしてプリンタモーターの連続回転ステップ数を設定する
		 .パラメータ
			0 ～ 15	 (16以上を入力した場合正しいステップ数で回りません)
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PrintMotorStepSet(i)
UBYTE	i;
{
	B_MCR2_Status &= 0x0f;
	B_MCR2_Status |= (i << 4);
	outpw(B_MCR2_PORT,B_MCR2_Status);
	if(!PrintType) {
		C_MCR2_Status &= 0x0f;
		C_MCR2_Status |= (i << 4);
	/*	C_MCR2_Status |= (i << 5);	ＩＤＦモーターは１／２相なのでステップは２倍にしておくこと。*/
		outpw(C_MCR2_PORT,C_MCR2_Status);
	}
}

/******************************************************************************
	module		:[ラインバッファ入力アドレスセット]
	function	:[
		1.入力データのラインメモリ上のアドレスの設定
	]
	return		:[なし]
	condition   :[
		1.必ず ( スタートアドレス ＜ エンドアドレス )　でなければならない。
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1994/01/07]
	author		:[大西亨]
******************************************************************************/
void LineBufferInputAddressSet(start,end)
UWORD	start,end;
{
	TRISA_Status = (UBYTE)start;
	outpw(TRISA_PORT,TRISA_Status);
	TRIEA_Status = (UBYTE)end;
	outpw(TRIEA_PORT,TRIEA_Status);
}

/******************************************************************************
	module		:[プリンタスピード１０ｍｓ]
	function	:[
		1.ポートG12のPRTSPをOFFしてプリンタスピードを１０ｍｓにする。
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		1.SATSUKIは電源ＯＮ時にこの設定にするのみ、後で変更無し
	]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PrintSpeed_10ms(void)
{
	M08_Status &= ~IO_BIT_PRTSPD;
	outpw(MD9402_M08_PORT,M08_Status);
}

/******************************************************************************
	module		:[プリンタスピード５ｍｓ]
	function	:[
		1.ポートG12のPRTSPをONしてプリンタスピードを５ｍｓにする。
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		1.ラベンダーは電源ＯＮ時にこの設定にするのみ、後で変更無し
	]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void PrintSpeed_5ms(void)
{
	M08_Status |= IO_BIT_PRTSPD;
	outpw(MD9402_M08_PORT,M08_Status);
}

/******************************************************************************
	module		:[サーマルヘッドサイズ選択Ａ４]
	function	:[
		1.ポートG12のHSIZEビットをOFFしてサーマルヘッドのサイズをＡ４にする
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		1.ラベンダーは電源ＯＮ時にこの設定にするのみ、後で変更無し
	]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
#if (0)	/** 椛はＢ４ヘッドしか使用しない By O.K Oct,28,1994 **/
void ThermalHeadSizeA4(void)
{
	SYSCR_Status &= ~IO_BIT_HSIZE;
	outpw(SYSCR_PORT,SYSCR_Status);
}
#endif

/******************************************************************************
	module		:[サーマルヘッドサイズ選択Ｂ４]
	function	:[
		1.ポートG12のHSIZEビットをONしてサーマルヘッドのサイズをＢ４にする
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		1.ＳＡＴＳＵＫＩは電源ＯＮ時にこの設定にするのみ、後で変更無し
	]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void ThermalHeadSizeB4(void)
{
	SYSCR_Status |= IO_BIT_HSIZE;
	outpw(SYSCR_PORT,SYSCR_Status);
}

/******************************************************************************
	module		:[FN線密度変換パターン１]
	function	:[
		1.ポートG12のFNDCPTビットをOFFしてFINE-NORMAL線密度変換時の論理パターン
		 .を１にする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void FineNormalChangePattern1(void)
{
	M08_Status &= ~IO_BIT_FNDCPZ;
	M08_Status |= IO_BIT_PRTSPD;	/**  By O.K Mar,07,1995 **/
	outpw(MD9402_M08_PORT,M08_Status);
}

/******************************************************************************
	module		:[FN線密度変換パターン２]
	function	:[
		1.ポートG12のFNDCPTビットをONしてFINE-NORMAL線密度変換時の論理パターン
		 .を２にする
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void FineNormalChangePattern2(void)
{
	M08_Status |= IO_BIT_FNDCPZ;
	M08_Status |= IO_BIT_PRTSPD;	/**  By O.K Mar,07,1995 **/
	outpw(MD9402_M08_PORT,M08_Status);
}

/******************************************************************************
	module		:[シリアルアウトビットクリア]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1994/03/10]
	author		:[宮崎仁一]
******************************************************************************/
void DIONClear(void)
{
	SYSCR_Status |= IO_BIT_CLDION;
	outpw(SYSCR_PORT,SYSCR_Status);
}
/******************************************************************************
	module		:[シリアルアウトビットセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1994/03/10]
	author		:[宮崎仁一]
******************************************************************************/
void DIONSet(void)
{
	SYSCR_Status &= ~IO_BIT_CLDION;
	outpw(SYSCR_PORT,SYSCR_Status);
}

/******************************************************************************
	module		:[IRQINT 5ms set]
	function	:[
		1.ポートG13のIRQINTビットをOFFして割り込み発生周期を５ｍｓにセットします
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void IRQINT_5msSet(void)
{
	if (M01_Status & IO_BIT_IRQINT) {
		M01_Status &= ~IO_BIT_IRQINT;
		outpw(MD9402_M01_PORT,M01_Status);
	}
}

/******************************************************************************
	module		:[IRQINT 10ms set]
	function	:[
		1.ポートG13のIRQINTビットをONして割り込み発生周期を１０ｍｓにセットします
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void IRQINT_10msSet(void)
{
	M01_Status |= IO_BIT_IRQINT;
	outpw(MD9402_M01_PORT,M01_Status);
}

/*************************************************************************
	module		:[割り込み要求タイミング設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[
		#define IRQTIM_0MS	0x0000
		#define IRQTIM_1_25MS	0x0040
		#define IRQTIM_2_5MS	0x0080
		#define IRQTIM_3_75MS	0x00C0
	]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/10/14]
	author		:[木元　修]
*************************************************************************/
void SetIRQInterval(
	UBYTE timing)
{
		M01_Status &= ~(IO_BIT_IRQTIM0 | IO_BIT_IRQTIM1);
		M01_Status |= timing;
		outpw(MD9402_M01_PORT,M01_Status);
}


/******************************************************************************
	module		:[ファインノーマル変換ラインバッファエンドアドレス設定]
	function	:[
		1.ファイン／ノーマル変換時、G/Aのラインバッファのエンドアドレスを設定します。
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1994/03/10]
	author		:[大西亨]
******************************************************************************/
void FN_LineBufferEndAddressSet(
	UWORD end_address)
{
	end_address -= 1;
	if (end_address > 0x00ff) {
		M03_Status |= IO_BIT_FA3ON;
	}
	else {
		M03_Status &= ~IO_BIT_FA3ON;
	}
	outpw(MD9402_M03_PORT,M03_Status);

	M05_Status = (UBYTE)(end_address);
	outpw(MD9402_M05_PORT,M05_Status);
}

/*************************************************************************
	module		:[パラレル入力サイズＡ４]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[1998/7/1]
	author		:[K.Kawata]
*************************************************************************/
void ParallelDataA4(void)
{
	SMCR_Status &= ~IO_BIT_XA4_B4;
	outpw(SMCR_PORT,SMCR_Status);
}

/*************************************************************************
	module		:[パラレル入力サイズＢ４]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[1998/7/1]
	author		:[K.Kawata]
*************************************************************************/
void ParallelDataB4(void)
{
	SMCR_Status |= IO_BIT_XA4_B4;
	outpw(SMCR_PORT,SMCR_Status);
}

#if (0)	/* 1998.7.1 K.Kawata */
/*************************************************************************
	module		:[画データ入力選択（シリアル）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ラベンダーはこの機能はありません
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
void ImageDataSerialInput(void)
{
	SMCR_Status &= ~IO_BIT_VIDEOS;
	outpw(SMCR_PORT,SMCR_Status);
}
#endif

/*************************************************************************
	module		:[画データ入力選択（パラレル）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		SAKAKIで使用
	]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[1998/7/1]
	author		:[K.Kawata]
*************************************************************************/
void ImageDataParallelInput(void)
{
	SMCR_Status |= IO_BIT_VIDEOS;
	outpw(SMCR_PORT,SMCR_Status);
}

/*************************************************************************
	module		:[Ｓ／Ｐ変換クロック選択（５ＭＨｚ）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ラベンダーはこの機能はありません。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
void S_P_Clock5MHz(void)
{
	SMCR_Status &= ~IO_BIT_CSEL1;
	outpw(SMCR_PORT,SMCR_Status);
}


/*************************************************************************
	module		:[Ｓ／Ｐ変換クロック選択（２．５ＭＨｚ）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ラベンダーはこの機能はありません。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
void S_P_Clock2MHz(void)
{
	SMCR_Status |= IO_BIT_CSEL1;
	outpw(SMCR_PORT,SMCR_Status);
}


/*************************************************************************
	module		:[スムージングシステムクロック選択（２０ＭＨｚ）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
void SmoothingClock20MHz(void)
{
	SMCR_Status &= (UBYTE)~(IO_BIT_CSEL2 | IO_BIT_CSEL3);
	outpw(SMCR_PORT,SMCR_Status);
}

/*************************************************************************
	module		:[スムージングシステムクロック選択（１０ＭＨｚ）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
void SmoothingClock10MHz(void)
{
	SMCR_Status |= (UBYTE)(~IO_BIT_CSEL2 | IO_BIT_CSEL3);
	outpw(SMCR_PORT,SMCR_Status);
}

/*************************************************************************
	module		:[１ライン同期信号有効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
void LineSynchronizeSignalEnable(void)
{
	SMCR_Status |= IO_BIT_HSYN;
	outpw(SMCR_PORT,SMCR_Status);
}

/*************************************************************************
	module		:[１ライン同期信号無効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
void LineSynchronizeSignalDisable(void)
{
	SMCR_Status &= ~IO_BIT_HSYN;
	outpw(SMCR_PORT,SMCR_Status);
}

/*************************************************************************
	module		:[１ページ同期信号有効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
void PageSynchronizeSignalEnable(void)
{
	SMCR_Status |= IO_BIT_XVSYN;
	outpw(SMCR_PORT,SMCR_Status);
}

/*************************************************************************
	module		:[１ページ同期信号無効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
void PageSynchronizeSignalDisable(void)
{
	SMCR_Status &= ~IO_BIT_XVSYN;
	outpw(SMCR_PORT,SMCR_Status);
}

/*************************************************************************
	module		:[シリアルデータ入力切替信号（ＩＤＰ３０１）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ラベンダーはこの機能はありません。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
void SericalInputIDP301(void)
{
	SMCR_Status |= IO_BIT_SINS;
	outpw(SMCR_PORT,SMCR_Status);
}

/*************************************************************************
	module		:[ＩＤＰシリアルデータモニター]
	function	:[
		1.
	]
	return		:[
		0:	ＩＤＰからシリアルデータが出力されていない。
		1:	ＩＤＰからシリアルデータが出力されている。
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
#if (0)	/** この関数はＧ／Ａのチェック用なので削除 By O.K Oct,28,1994 **/
UWORD IdpSerialDataMonitor(void)
{
	if(inpw(STCR5_PORT) & IO_BIT_SDI)
		return(1);
	else
		return(0);
}
#endif

/*************************************************************************
	module		:[ライン同期信号モニター]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/03/16]
	author		:[木元　修]
*************************************************************************/
#if (0)	/** この関数はＧ／Ａのチェック用なので削除 By O.K Oct,28,1994 **/
UWORD HsyncMonitor(void)
{
	if(inpw(STCR5_PORT) & IO_BIT_HSYN)
		return(1);
	else
		return(0);
}
#endif

/*************************************************************************
	module		:[ブザークロック設定]
	function	:[
		1.引数に応じて以下の様に設定されます。
		-	 0	:	 250Hz
		-	 1	:	 267Hz
		-	 2	:	 286Hz
		-	 3	:	 307Hz
		-	 4	:	 333Hz
		-	 5	:	 364Hz
		-	 6	:	 400Hz
		-	 7	:	 444Hz
		-	 8	:	 500Hz
		-	 9	:	 571Hz
		-	10	:	 667Hz
		-	11	:	 800Hz
		-	12	:	1000Hz
		-	13	:	1333Hz
		-	14	:	2000Hz
		-	15	:	4000Hz
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	Jun,24,1994:	void far BuzzClockSelect(Clock)をvoid far SCN_SetBuzzerFrequency(UBYTE)に変更
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void SCN_SetBuzzerFrequency(Clock)
UBYTE Clock;
{
	M01_Status &= 0xf0;
	M01_Status |= (UBYTE)(Clock & 0x0f);
	outpw(MD9402_M01_PORT,M01_Status);
}


/*************************************************************************
	module		:[ブザークロックイネーブル]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		void far BuzzClockEnable()をvoid far SCN_SetBuzzer(UBYTE)に変更 Jun,24,1994
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void SCN_SetBuzzer(
	UBYTE set_bit)
{
	if (set_bit == BUZZER_ON) {
		M01_Status |= IO_BIT_BUZZEN;
		GA_BuzzerFlag = IO_BIT_BUZZEN;	/** Add By O.K Nov,2,1994 **/
	}
	else {
		M01_Status &= ~IO_BIT_BUZZEN;
		GA_BuzzerFlag = 0;	/** Add By O.K Nov,2,1994 **/
	}
	outpw(MD9402_M01_PORT,M01_Status);
}

#if (0)	/** 桐と共通化するために以下の関数は不要 **/
	/*************************************************************************
		module		:[ブザークロックディスイネーブル]
		function	:[
			1.
		]
		return		:[]
		common		:[]
		condition	:[]
		comment		:[]
		machine		:[V53]
		language	:[MS-C(Ver.6.0)]
		keyword		:[CMN]
		date		:[1994/02/28]
		author		:[木元　修]
	*************************************************************************/
	void BuzzClockDisable()
	{
		M01_Status &= ~IO_BIT_BUZZEN;
		outpw(MD9402_M01_PORT,M01_Status);
	}
#endif

/*************************************************************************
	module		:[ＦＮ部スタート]
	function	:[
		1.Ｆ／Ｎ変換処理をスタートさせる為に、ＦＮＳＴビットをＯＦＦ－ＯＮします。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void Fnst()
{
	M03_Status &= ~IO_BIT_FNST;
	outpw(MD9402_M03_PORT,M03_Status);

	M03_Status |= IO_BIT_FNST;
	outpw(MD9402_M03_PORT,M03_Status);
}

/*************************************************************************
	module		:[ＦＮ部スタート]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void FN_Start()
{
	M03_Status |= IO_BIT_FNST;
	outpw(MD9402_M03_PORT,M03_Status);
}


/*************************************************************************
	module		:[ＦＮ部ストップ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void FN_Stop()
{
	M03_Status &= ~IO_BIT_FNST;
	outpw(MD9402_M03_PORT,M03_Status);
}


/*************************************************************************
	module		:[拡張バス出力許可]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void ExtendedBusOutEnable()
{
	M03_Status |= IO_BIT_EXBIEN;
	outpw(MD9402_M03_PORT,M03_Status);
}


/*************************************************************************
	module		:[拡張バス出力禁止]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void ExtendedBusOutDiable()
{
	M03_Status &= ~IO_BIT_EXBIEN;
	outpw(MD9402_M03_PORT,M03_Status);
}



/*************************************************************************
	module		:[Ｆ／Ｎ時の拡張バスへのデータ出力開始]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/11/09]
	author		:[木元　修]
*************************************************************************/
void Exbien()
{
	M03_Status &= ~IO_BIT_EXBIEN;
	outpw(MD9402_M03_PORT,M03_Status);

	M03_Status |= IO_BIT_EXBIEN;
	outpw(MD9402_M03_PORT,M03_Status);
}


/******************************************************************************
	module		:[ラインバッファ切り換え]
	function	:[
		1.呼ばれる毎にポートＭ０６の BFLCHG ビットを 1->0 , 0->1 へ切り換えます
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void BF_LineBufferChange(void)
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status ^= IO_BIT_BFLCHG;
	outpw(MD9402_M06_PORT,M06_Status);
}

/*************************************************************************
	module		:[ＢＦ部ラインバッファ＃１を選択]
	function	:[
		Ｇ／Ａ(MD9402)のＢＦ部のラインメモリ＃１を選択する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/09/01]
	author		:[竹内茂樹]
*************************************************************************/
void BF_LineBuffer1Select( void )
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status &= ~IO_BIT_BFLCHG;
	outpw(MD9402_M06_PORT,M06_Status);
}

/*************************************************************************
	module		:[ＢＦ部ラインバッファ＃２を選択]
	function	:[
		Ｇ／Ａ(MD9402)のＢＦ部のラインメモリ＃２を選択する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/09/01]
	author		:[竹内茂樹]
*************************************************************************/
void BF_LineBuffer2Select( void )
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status |= IO_BIT_BFLCHG;
	outpw(MD9402_M06_PORT,M06_Status);
}

/******************************************************************************
	module		:[ラインメモリ選択チェック]
	function	:[
		1.G/Aのラインメモリ(#1/#2)のどちらが選択されているか示します
	]
	return		:[
					0:ラインメモリ＃１が選択されている
					1:ラインメモリ＃２が選択されている
	]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
UWORD BF_LineBufferCheck(void)
{
	if(inpw(MD9402_M06_PORT) & IO_BIT_BFLCHG) {
		return(1);
	}
	else {
		return(0);
	}
}

/******************************************************************************
	module		:[ラインメモリ自動選択許可]
	function	:[
		1.ポートＭ０６の BFLCHGAUTO ビットを "1" にセットして自動選択を許可します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void BF_LineBufferAutoChangeEnable(void)
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status |= IO_BIT_BFLCHGAUTO;
	outpw(MD9402_M06_PORT,M06_Status);
}

/******************************************************************************
	module		:[ラインメモリ自動選択禁止]
	function	:[
		1.ポートＭ０６の BFLCHGAUTO ビットを "0" にセットして自動選択を禁止します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
void BF_LineBufferAutoChangeDisable(void)
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status &= ~IO_BIT_BFLCHGAUTO;
	outpw(MD9402_M06_PORT,M06_Status);
}

/******************************************************************************
	module		:[ラインメモリデータ入力許可]
	function	:[
		1.ポートＭ０６の BFDIEN ビットを "1" にセットしてラインメモリデータの
		 .入力を許可します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい**--> reprint preheat で使用する***/

void BF_LineBufferDataInEnable(void)
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status |= IO_BIT_BFDIEN;
	outpw(MD9402_M06_PORT,M06_Status);
}

/******************************************************************************
	module		:[ラインメモリデータ入力禁止]
	function	:[
		1.ポートＭ０６の BFDIEN ビットを "0" にセットしてラインメモリデータの
		 .入力を禁止します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい**--> reprint preheat で使用する***/

void BF_LineBufferDataInDisable(void)
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status &= ~IO_BIT_BFDIEN;
	outpw(MD9402_M06_PORT,M06_Status);
}


/******************************************************************************
	module		:[ラインメモリデータ出力許可]
	function	:[
		1.ポートＭ０６の BFDOEN ビットを "1" にセットしてラインメモリデータの
		 .出力を許可します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい***--> preheat reprint で使用 ******/

void BF_LineBufferDataOutEnable(void)
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status |= IO_BIT_BFDOEN;
	outpw(MD9402_M06_PORT,M06_Status);
}

/******************************************************************************
	module		:[ラインメモリデータ出力禁止]
	function	:[
		1.ポートＭ０６の BFDOEN ビットを "0" にセットしてラインメモリデータの
		 .出力を禁止します
	]
	return		:[なし]
	common		:[なし]
	machine		:[H8/3003]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	date		:[1993/11/29]
	author		:[大西亨]
******************************************************************************/
/*****電源ONの初期設定のみでよい***--> preheat reprint で使用 ******/

void BF_LineBufferDataOutDisable(void)
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status &= ~IO_BIT_BFDOEN;
	outpw(MD9402_M06_PORT,M06_Status);
}



#if (0)	/** 未使用の為 By O.K Dec,03,1994 **/
/*************************************************************************
	module		:[Ｆ／Ｎ部強制リセット]
	function	:[
		1.Ｆ／Ｎ部の強制リセットを実行します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/08/31]
	author		:[木元　修]
*************************************************************************/
void FN_ForcedResetEnable()
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status &= ~IO_BIT_FNRST;
	outpw(MD9402_M06_PORT,M06_Status);
}


/*************************************************************************
	module		:[Ｆ／Ｎ部強制リセット]
	function	:[
		1.Ｆ／Ｎ部の強制リセットを解除します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/08/31]
	author		:[木元　修]
*************************************************************************/
void FN_ForcedResetDisable()
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status |= IO_BIT_FNRST;
	outpw(MD9402_M06_PORT,M06_Status);
}
#endif

/*************************************************************************
	module		:[Ｆ／Ｎ部強制リセット]
	function	:[
		1.Ｆ／Ｎ部の強制リセットを実行します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/08/31]
	author		:[木元　修]
*************************************************************************/
void FN_ForcedReset()
{
	M06_Status &= ~IO_BIT_FNRST;
	outpw(MD9402_M06_PORT,M06_Status);

	M06_Status |= IO_BIT_FNRST;
	outpw(MD9402_M06_PORT,M06_Status);

	M06_Status &= ~IO_BIT_FNRST;
	outpw(MD9402_M06_PORT,M06_Status);
}

/*************************************************************************
	module		:[出力データシリアルスピード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void OutputDataSerialSpeedHigh()
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status &= ~IO_BIT_BTRSP;
	outpw(MD9402_M06_PORT,M06_Status);
}

/*************************************************************************
	module		:[出力データシリアルスピード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void OutputDataSerialSpeedLow()
{
	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/
	M06_Status |= IO_BIT_BTRSP;
	outpw(MD9402_M06_PORT,M06_Status);
}


/*************************************************************************
	module		:[ＢＦ部スタート]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void Bfst()
{
	M07_Status &= ~IO_BIT_BFST;
	outpw(MD9402_M07_PORT,M07_Status);

	M07_Status |= IO_BIT_BFST;
	outpw(MD9402_M07_PORT,M07_Status);
}

/*************************************************************************
	module		:[ＢＦ部スタート]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_Start()
{
	M07_Status |= IO_BIT_BFST;
	outpw(MD9402_M07_PORT,M07_Status);
}



/*************************************************************************
	module		:[ＢＦ部ストップ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_Stop()
{
	M07_Status &= ~IO_BIT_BFST;
	outpw(MD9402_M07_PORT,M07_Status);
}


/*************************************************************************
	module		:[ＢＦ部モード設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_ModeEnable()
{
	M07_Status &= ~IO_BIT_BFMODE;
	outpw(MD9402_M07_PORT,M07_Status);
}

/*************************************************************************
	module		:[ＢＦ部モード設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_ModeDisable()
{
	M07_Status |= IO_BIT_BFMODE;
	outpw(MD9402_M07_PORT,M07_Status);
}

/*************************************************************************
	module		:[ＢＦ部データ読み出しモード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_SerialData()
{
	M07_Status |= IO_BIT_BSI_XPA;
	outpw(MD9402_M07_PORT,M07_Status);
}


/*************************************************************************
	module		:[ＢＦ部データ読み出しモード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_ParallelData()
{
	M07_Status &= ~IO_BIT_BSI_XPA;
	outpw(MD9402_M07_PORT,M07_Status);
}


/*************************************************************************
	module		:[ＢＦ部拡張バス出力許可]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_ExtendedBusOutEnable()
{
	M07_Status |= IO_BIT_BEXBIEN;
	outpw(MD9402_M07_PORT,M07_Status);
}

/*************************************************************************
	module		:[ＢＦ部拡張バス出力禁止]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_ExtendedBusOutDisable()
{
	M07_Status &= ~IO_BIT_BEXBIEN;
	outpw(MD9402_M07_PORT,M07_Status);
}


/*************************************************************************
	module		:[ＢＦ部ＤＩ部強制リセット有効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_DI_ForcedResetEnable()
{
	M07_Status &= ~IO_BIT_BFDIRST;
	outpw(MD9402_M07_PORT,M07_Status);
}

/*************************************************************************
	module		:[ＢＦ部ＤＩ部強制リセット無効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_DI_ForcedResetDisable()
{
	M07_Status |= IO_BIT_BFDIRST;
	outpw(MD9402_M07_PORT,M07_Status);
}


/*************************************************************************
	module		:[ＢＦ部ＤＩ部ＡＵＴＯリセットビット有効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_DI_AutoResetEnable()
{
	M07_Status &= ~IO_BIT_BADIEN;
	outpw(MD9402_M07_PORT,M07_Status);
}

/*************************************************************************
	module		:[ＢＦ部ＤＩ部ＡＵＴＯリセットビット無効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_DI_AutoResetDisable()
{
	M07_Status |= IO_BIT_BADIEN;
	outpw(MD9402_M07_PORT,M07_Status);
}

/*************************************************************************
	module		:[ＢＦ部ＤＯ部強制リセット有効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_DO_ForcedResetEnable()
{
	M07_Status &= ~IO_BIT_BFDORST;
	outpw(MD9402_M07_PORT,M07_Status);
}

/*************************************************************************
	module		:[ＢＦ部ＤＯ部強制リセット無効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_DO_ForcedResetDisable()
{
	M07_Status |= IO_BIT_BFDORST;
	outpw(MD9402_M07_PORT,M07_Status);
}


/*************************************************************************
	module		:[ＢＦ部ＤＯ部ＡＵＴＯリセットビット有効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_DO_AutoResetEnable()
{
	M07_Status &= ~IO_BIT_BADOEN;
	outpw(MD9402_M07_PORT,M07_Status);
}

/*************************************************************************
	module		:[ＢＦ部ＤＯ部ＡＵＴＯリセットビット無効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_DO_AutoResetDisable()
{
	M07_Status |= IO_BIT_BADOEN;
	outpw(MD9402_M07_PORT,M07_Status);
}


/*************************************************************************
	module		:[ＦＮ部動作有効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void FineNormalEnable()
{
	M08_Status &= ~IO_BIT_FEXBISEL;
	M08_Status |= IO_BIT_PRTSPD;	/**  By O.K Mar,07,1995 **/
	outpw(MD9402_M08_PORT,M08_Status);
}

/*************************************************************************
	module		:[ＦＮ部動作無効（スルーモード）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void FineNormalDisable()
{
	M08_Status |= IO_BIT_FEXBISEL;
	M08_Status |= IO_BIT_PRTSPD;	/**  By O.K Mar,07,1995 **/
	outpw(MD9402_M08_PORT,M08_Status);
}


/*************************************************************************
	module		:[シリアル入力セレクター１ＯＮ]
	function	:[
		1.ＩＤＰ－２からのシリアルデータをプリンター側に出力させます。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void SerialSelecter1ON()
{
	M08_Status |= IO_BIT_SISEL1;
	M08_Status |= IO_BIT_PRTSPD;	/**  By O.K Mar,07,1995 **/
	outpw(MD9402_M08_PORT,M08_Status);
}

/*************************************************************************
	module		:[シリアル入力セレクター１ＯＦＦ]
	function	:[
		1.ＩＤＰ－２からのシリアルデータをバッファリング回路側に出力します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void SerialSelecter1OFF()
{
	M08_Status &= ~IO_BIT_SISEL1;
	M08_Status |= IO_BIT_PRTSPD;	/**  By O.K Mar,07,1995 **/
	outpw(MD9402_M08_PORT,M08_Status);
}

/*************************************************************************
	module		:[シリアル入力セレクター２ＯＮ]
	function	:[
		1.ＩＤＰ－１からのシリアルデータをプリンター側に出力します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void SerialSelecter2ON()
{
	M08_Status |= IO_BIT_SISEL2;
	M08_Status |= IO_BIT_PRTSPD;	/**  By O.K Mar,07,1995 **/
	outpw(MD9402_M08_PORT,M08_Status);
}

/*************************************************************************
	module		:[シリアル入力セレクター２ＯＦＦ]
	function	:[
		1.ＩＤＰ－１からのシリアルデータをＦ／Ｎ回路側に出力します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void SerialSelecter2OFF()
{
	M08_Status &= ~IO_BIT_SISEL2;
	M08_Status |= IO_BIT_PRTSPD;	/**  By O.K Mar,07,1995 **/
	outpw(MD9402_M08_PORT,M08_Status);
}

/*************************************************************************
	module		:[シリアル入力セレクター３ＯＮ]
	function	:[
		1.プリンター回路への入力データをＩＤＰ－２にセットします。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void SerialSelecter3ON()
{
	M08_Status |= IO_BIT_SISEL3;
	M08_Status |= IO_BIT_PRTSPD;	/**  By O.K Mar,07,1995 **/
	outpw(MD9402_M08_PORT,M08_Status);
}

/*************************************************************************
	module		:[シリアル入力セレクター３ＯＦＦ]
	function	:[
		1.プリンター回路への入力データをＩＤＰ－１にセットします。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void SerialSelecter3OFF()
{
	M08_Status &= ~IO_BIT_SISEL3;
	M08_Status |= IO_BIT_PRTSPD;	/**  By O.K Mar,07,1995 **/
	outpw(MD9402_M08_PORT,M08_Status);
}

/*************************************************************************
	module		:[ＢＦ部ラインメモリアドレス設定]
	function	:[
		1.引数に応じてラインメモリのアドレスを設定します。
		-			引数					出力
		-	SYS_DOCUMENT_A4_SIZE(0)		LINE_MEMORY_A4
		-	SYS_DOCUMENT_B4_SIZE(1)		LINE_MEMORY_B4
		-	SYS_DOCUMENT_A3_SIZE(2)		LINE_MEMORY_A3

	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void BF_LineMemoryAddressSet(
	UWORD end_address)
{
	end_address -= 1;

#if (0)	/** Reduce Bug After A3 Org TX By O.K Feb,8,1995 **/
	if (end_address > 0x00ff) {
		M06_Status |= IO_BIT_BA3ON;
		outpw(MD9402_M06_PORT,M06_Status);
	}
#endif

	M06_Status &= 0x0DF;		/** Ｇ／Ａリセット強制マスク By O.K Jul,11,1995 **/

	if (end_address > 0x00ff) {
		M06_Status |= IO_BIT_BA3ON;
	}
	else {
		M06_Status &= ~IO_BIT_BA3ON;
	}
	outpw(MD9402_M06_PORT,M06_Status);

	M09_Status = (UBYTE)(end_address);
	outpw(MD9402_M09_PORT,M09_Status);
}

/*************************************************************************
	module		:[ＤＭＡ転送イネーブル]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void DmaEnable()
{
	BK1_1_Status |= IO_BIT_ON_DMA;
	outpw(BK1_1_PORT,BK1_1_Status);
}

/*************************************************************************
	module		:[ＤＭＡ転送ディスイネーブル]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/02/28]
	author		:[木元　修]
*************************************************************************/
void DmaDisable()
{
	BK1_1_Status &= ~IO_BIT_ON_DMA;
	outpw(BK1_1_PORT,BK1_1_Status);
}

#if (PRO_SMOOTHING == ENABLE)
#if (0)	/** スムージング関数群は直接設定する為に不必要 By O.K Sep,21,1994 **/
///************************************************/
///** 皐以外の機種用（スムージング回路制御関数群 **/
///************************************************/
///*************************************************************************
//	module		:[ウエイト出力イネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		このビットは桐専用だそうです。（朝倉さんより）
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void WaitOutputEnable()
//{
//	BK1_1_Status |= IO_BIT_ENWT;
//	outpw(BK1_1_PORT,BK1_1_Status);
//}
//
///*************************************************************************
//	module		:[ウエイト出力ディスイネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		このビットは桐専用だそうです（朝倉さんより）
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void WaitOutputDisble()
//{
//	BK1_1_Status &= ~IO_BIT_ENWT;
//	outpw(BK1_1_PORT,BK1_1_Status);
//}
//
///*************************************************************************
//	module		:[ウエイト設定]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		このビットは桐専用だそうです。（朝倉さんより）
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void WaitSetting(SetBit)
//UBYTE SetBit;
//{
//	BK1_1_Status |= (UBYTE)(SetBit & 0x1e);
//	outpw(BK1_1_PORT,BK1_1_Status);
//}
//
///*************************************************************************
//	module		:[ＤＭＡ転送イネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void DmaEnable()
//{
//	BK1_1_Status |= IO_BIT_ON_DMA;
//	outpw(BK1_1_PORT,BK1_1_Status);
//}
//
///*************************************************************************
//	module		:[ＤＭＡ転送ディスイネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void DmaDisable()
//{
//	BK1_1_Status &= ~IO_BIT_ON_DMA;
//	outpw(BK1_1_PORT,BK1_1_Status);
//}
//
///*************************************************************************
//	module		:[サンプリングクロック選択]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SamplingClockFull()
//{
//	BK1_1_Status &= ~IO_BIT_SP_CLK;
//	outpw(BK1_1_PORT,BK1_1_Status);
//}
//
///*************************************************************************
//	module		:[サンプリングクロック選択]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SamplingClockHalf()
//{
//	BK1_1_Status |= IO_BIT_SP_CLK;
//	outpw(BK1_1_PORT,BK1_1_Status);
//}
//
///*************************************************************************
//	module		:[外部ＲＡＭ強制クリア]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void EXRamForcedClearEnable()
//{
//	BK2_Status |= IO_BIT_ON_WH;
//	outpw(BK2_PORT,BK2_Status);
//}
//
///*************************************************************************
//	module		:[外部ＲＡＭ強制クリア]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void EXRamForcedClearDisable()
//{
//	BK2_Status &= ~IO_BIT_ON_WH;
//	outpw(BK2_PORT,BK2_Status);
//}
//
//
///*************************************************************************
//	module		:[スムージング有効]
//	function	:[
//		1.スムージング機能を有効に設定します。
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53]
//	language	:[MS-C(Ver.6.0)]
//	keyword		:[CMN]
//	date		:[1994/03/16]
//	author		:[木元　修]
//*************************************************************************/
//void SmoothingEnable(void)
//{
//	BK2_Status |= IO_BIT_ON_SUM;
//	outpw(BK2_PORT,BK2_Status);
//}
//
//
///*************************************************************************
//	module		:[スムージング無効]
//	function	:[
//		1.スムージング機能を無効に設定します。
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53]
//	language	:[MS-C(Ver.6.0)]
//	keyword		:[CMN]
//	date		:[1994/03/16]
//	author		:[木元　修]
//*************************************************************************/
//void SmoothingDisable(void)
//{
//	BK2_Status &= ~IO_BIT_ON_SUM;
//	outpw(BK2_PORT,BK2_Status);
//}
//
///*************************************************************************
//	module		:[検索コードレジスタ１設定]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SetReferenceCode1(Value)
//UBYTE Value;
//{
//	BK4_1_Status = (UBYTE)~Value;
//	outpw(BK4_1_PORT,BK4_1_Status);
//}
//
///*************************************************************************
//	module		:[検索コードレジスタ２設定]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SetReferenceCode2(Value)
//UBYTE Value;
//{
//	BK4_2_Status = (UBYTE)~Value;
//	outpw(BK4_2_PORT,BK4_2_Status);
//}
//
///*************************************************************************
//	module		:[検索コードレジスタ３設定]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SetReferenceCode3(Value)
//UBYTE Value;
//{
//	BK4_3_Status = (UBYTE)~Value;
//	outpw(BK4_3_PORT,BK4_3_Status);
//}
//
///*************************************************************************
//	module		:[検索コードレジスタ４設定]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SetReferenceCode4(Value)
//UBYTE Value;
//{
//	BK4_4_Status = (UBYTE)~Value;
//	outpw(BK4_4_PORT,BK4_4_Status);
//}
//
///*************************************************************************
//	module		:[検索コードレジスタ５設定]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SetReferenceCode5(Value)
//UBYTE Value;
//{
//	BK4_5_Status = (UBYTE)~Value;
//	outpw(BK4_5_PORT,BK4_5_Status);
//}
//
///*************************************************************************
//	module		:[検索コードレジスタ６設定]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SetReferenceCode6(Value)
//UBYTE Value;
//{
//	BK4_6_Status = (UBYTE)~(Value & 0x3f);
//	outpw(BK4_6_PORT,BK4_6_Status);
//}
//
//
///*************************************************************************
//	module		:[スムージング・ノッチ設定]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		スムージング・ノッチレジスタを１バイトまとめて設定します。
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SetSmoothingOrNotch(Setting)
//UBYTE Setting;
//{
//	SUNO_Status = Setting;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
///*************************************************************************
//	module		:[連続スムージング処理イネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void ContinuouslySmoothingEnable()
//{
//	SUNO_Status = IO_BIT_SSU;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
///*************************************************************************
//	module		:[連続スムージング処理ディスイネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void ContinuouslySmoothingDisable()
//{
//	SUNO_Status &= ~IO_BIT_SSU;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
//
///*************************************************************************
//	module		:[スムージング・ノッチ区別処理イネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SmoothNotchDistinguishEnable()
//{
//	SUNO_Status |= IO_BIT_SUNO;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
///*************************************************************************
//	module		:[スムージング・ノッチ区別処理ディスイネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void SmoothNotchDistinguishDisable()
//{
//	SUNO_Status &= ~IO_BIT_SUNO;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
//
///*************************************************************************
//	module		:[連続ノッチ処理イネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void CountinuoslyNotchEnable()
//{
//	SUNO_Status |= IO_BIT_NO1;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
///*************************************************************************
//	module		:[連続ノッチ処理ディスイネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void CountinuoslyNotchDisable()
//{
//	SUNO_Status &= ~IO_BIT_NO1;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
//
///*************************************************************************
//	module		:[横ノッチ白変換処理イネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void HorizontalNotchWhiteEnable()
//{
//	SUNO_Status |= IO_BIT_CHW;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
//
///*************************************************************************
//	module		:[横ノッチ白変換処理ディスイネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void HorizontalNotchWhiteDisable()
//{
//	SUNO_Status &= ~IO_BIT_CHW;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
//
///*************************************************************************
//	module		:[横ノッチ黒変換処理イネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void HorizontalNotchBlackEnable()
//{
//	SUNO_Status |= IO_BIT_CHB;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
//
///*************************************************************************
//	module		:[横ノッチ黒変換処理ディスイネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void HorizontalNotchBlackDisable()
//{
//	SUNO_Status &= ~IO_BIT_CHB;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
//
///*************************************************************************
//	module		:[連続ノッチ除去有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void ContinuouslyNotchRemovalEnable()
//{
//	SUNO_Status |= IO_BIT_CHB;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
//
///*************************************************************************
//	module		:[連続ノッチ除去無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void ContinuouslyNotchRemovalDisable()
//{
//	SUNO_Status &= ~IO_BIT_CHB;
//	outpw(SUNO_PORT,SUNO_Status);
//}
//
//
///*************************************************************************
//	module		:[縦ノッチレジスタ設定]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		縦ノッチレジスタを１バイトまとめて設定します。
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void VerticalNotchRemovalEnable()
//{
//	VNO_Status = 0x00;
//	outpw(VNO_PORT,VNO_Status);
//}
//
//
///*************************************************************************
//	module		:[縦ノッチレジスタリセット]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		縦ノッチレジスタを１バイトまとめて設定します。
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/02/28]
//	author		:[木元　修]
//*************************************************************************/
//void VerticalNotchRemovalDisable()
//{
//	VNO_Status = 0xff;
//	outpw(VNO_PORT,VNO_Status);
//}
//
//
///*************************************************************************
//	module		:[横ノッチ除去イネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		横ノッチレジスタを１バイトまとめてセットします。
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void HorizontalNotchRemovalEnable()
//{
//	HNO_Status = 0x00;
//	outpw(HNO_PORT,HNO_Status);
//}
//
///*************************************************************************
//	module		:[横ノッチ除去ディスイネーブル]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		横ノッチレジスタを１バイトまとめてリセットします。
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void HorizontalNotchRemovalDisable()
//{
//	HNO_Status = 0x0f;
//	outpw(HNO_PORT,HNO_Status);
//}
//
//
///*************************************************************************
//	module		:[白色孤立点レジスタセット]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		主走査、副走査とも、３ビット中の１ビットのみセットしてください。
//		関数内では、２重セットはチェックしていません。
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void WhiteKoritsuEnable(Setting)
//UBYTE Setting;
//{
//	KORITU_W_Status = (UBYTE)~(Setting & 0x3f);
//	outpw(KORITU_W_PORT,KORITU_W_Status);
//}
//
///*************************************************************************
//	module		:[白色孤立点レジスタリセット]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		主走査、副走査とも、３ビット中の１ビットのみセットしてください。
//		関数内では、２重セットはチェックしていません。
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void WhiteKoritsuDisable(Setting)
//UBYTE Setting;
//{
//	KORITU_W_Status = (UBYTE)(Setting & 0x3f);
//	outpw(KORITU_W_PORT,KORITU_W_Status);
//}
//
//
///*************************************************************************
//	module		:[水平白色孤立点除去有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void HorizontalWhiteKotiruEnable(Setting)
//UBYTE Setting;
//{
//	KORITU_W_Status &= ~(Setting & 0x07);
//	outpw(KORITU_W_PORT,KORITU_W_Status);
//}
//
///*************************************************************************
//	module		:[水平白色孤立点除去無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void HorizontalWhiteKotiruDisable(Setting)
//UBYTE Setting;
//{
//	KORITU_W_Status |= (Setting & 0x07);
//	outpw(KORITU_W_PORT,KORITU_W_Status);
//}
//
///*************************************************************************
//	module		:[垂直白色孤立点除去有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void VerticalWhiteKotiruEnable(Setting)
//UBYTE Setting;
//{
//	KORITU_W_Status &= ~(Setting & 0x28);
//	outpw(KORITU_W_PORT,KORITU_W_Status);
//}
//
///*************************************************************************
//	module		:[垂直白色孤立点除去無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void VerticalWhiteKotiruDisable(Setting)
//UBYTE Setting;
//{
//	KORITU_W_Status |= (Setting & 0x28);
//	outpw(KORITU_W_PORT,KORITU_W_Status);
//}
//
///*************************************************************************
//	module		:[黒色孤立点レジスタセット]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		主走査、副走査とも、３ビット中の１ビットのみセットしてください。
//		関数内では、２重セットはチェックしていません。
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void BlackKoritsuEnable(Setting)
//UBYTE Setting;
//{
//	KORITU_B_Status = (UBYTE)~(Setting & 0x3f);
//	outpw(KORITU_B_PORT,KORITU_B_Status);
//}
//
///*************************************************************************
//	module		:[黒色孤立点レジスタリセット]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		主走査、副走査とも、３ビット中の１ビットのみセットしてください。
//		関数内では、２重セットはチェックしていません。
//	]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void BlackKoritsuDisable(Setting)
//UBYTE Setting;
//{
//	KORITU_B_Status = (UBYTE)(Setting & 0x3f);
//	outpw(KORITU_B_PORT,KORITU_B_Status);
//}
//
//
///*************************************************************************
//	module		:[水平黒色孤立点除去有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void HorizontalBlackKotiruEnable(Setting)
//UBYTE Setting;
//{
//	KORITU_B_Status &= ~(Setting & 0x07);
//	outpw(KORITU_B_PORT,KORITU_B_Status);
//}
//
///*************************************************************************
//	module		:[水平黒色孤立点除去無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void HorizontalBlackKotiruDisable(Setting)
//UBYTE Setting;
//{
//	KORITU_B_Status |= (Setting & 0x07);
//	outpw(KORITU_B_PORT,KORITU_B_Status);
//}
//
///*************************************************************************
//	module		:[垂直黒色孤立点除去有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void VerticalBlackKotiruEnable(Setting)
//UBYTE Setting;
//{
//	KORITU_B_Status &= ~(Setting & 0x28);
//	outpw(KORITU_B_PORT,KORITU_B_Status);
//}
//
///*************************************************************************
//	module		:[垂直黒色孤立点除去無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void VerticalBlackKotiruDisable(Setting)
//UBYTE Setting;
//{
//	KORITU_B_Status |= (Setting & 0x28);
//	outpw(KORITU_B_PORT,KORITU_B_Status);
//}
//
//
///*************************************************************************
//	module		:[白色直交検出有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void WhiteCrossEnable()
//{
//	SYSSR_Status &= ~IO_BIT_CRS1;
//	outpw(SYSSR_PORT,SYSSR_Status);
//}
//
///*************************************************************************
//	module		:[白色直交検出無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void WhiteCrossDisable()
//{
//	SYSSR_Status |= IO_BIT_CRS1;
//	outpw(SYSSR_PORT,SYSSR_Status);
//}
//
///*************************************************************************
//	module		:[スルーレジスタオール有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void AllThroughEnable()
//{
//	BK6_Status = 0x00;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[スルーレジスタオール無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void AllThroughDisable()
//{
//	BK6_Status = 0xff;
//	outpw(BK6_PORT,BK6_Status);
//}
//
//
///*************************************************************************
//	module		:[ＳＳＵ　スルー転送有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughSSUEnable()
//{
//	BK6_Status &= ~IO_BIT_TRU_0;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＳＳＵ　スルー転送無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughSSUDisable()
//{
//	BK6_Status |= IO_BIT_TRU_0;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＳＵＮＯ　スルー転送有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughSUNOEnable()
//{
//	BK6_Status &= ~IO_BIT_TRU_1;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＳＵＮＯ　スルー転送無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughSUNODisable()
//{
//	BK6_Status |= IO_BIT_TRU_1;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＮＯ１　スルー転送有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughNO1Enable()
//{
//	BK6_Status &= ~IO_BIT_TRU_2;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＮＯ１　スルー転送無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughNO1Disable()
//{
//	BK6_Status |= IO_BIT_TRU_2;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＣＨＢ　スルー転送有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughCHBEnable()
//{
//	BK6_Status &= ~IO_BIT_TRU_3;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＣＨＢ　スルー転送無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughCHBDisable()
//{
//	BK6_Status |= IO_BIT_TRU_3;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＣＨＷ　スルー転送有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughCHWEnable()
//{
//	BK6_Status &= ~IO_BIT_TRU_4;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＣＨＷ　スルー転送無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughCHWDisable()
//{
//	BK6_Status |= IO_BIT_TRU_4;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＣＨＫＢ　スルー転送有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughCHKBEnable()
//{
//	BK6_Status &= ~IO_BIT_TRU_5;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＣＨＫＢ　スルー転送無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughCHKBDisable()
//{
//	BK6_Status |= IO_BIT_TRU_5;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＣＨＫＷ　スルー転送有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughCHKWEnable()
//{
//	BK6_Status &= ~IO_BIT_TRU_6;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＣＨＫＷ　スルー転送無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughCHKWDisable()
//{
//	BK6_Status |= IO_BIT_TRU_6;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＣＲＳ　スルー転送有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughCRSEnable()
//{
//	BK6_Status &= ~IO_BIT_TRU_7;
//	outpw(BK6_PORT,BK6_Status);
//}
//
///*************************************************************************
//	module		:[ＣＲＳ　スルー転送無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void ThroughCRSDisable()
//{
//	BK6_Status |= IO_BIT_TRU_5;
//	outpw(BK6_PORT,BK6_Status);
//}
//
//
///*************************************************************************
//	module		:[副走査拡大有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void VerticalMagnificationEnable()
//{
//	BK1_2_Status &= ~IO_BIT_ENC;
//	outpw(BK1_2_PORT,BK1_2_Status);
//}
//
///*************************************************************************
//	module		:[副走査拡大無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void VerticalMagnificationDisable()
//{
//	BK1_2_Status |= IO_BIT_ENC;
//	outpw(BK1_2_PORT,BK1_2_Status);
//}
//
//
///*************************************************************************
//	module		:[拡大率セット]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[CMN]
//	date		:[1994/03/01]
//	author		:[木元　修]
//*************************************************************************/
//void MagnificationRateSet(Setting)
//UBYTE Setting;
//{
//	switch (Setting) {
//	case ENC_PROHIBIT0:
//	case ENC_PROHIBIT1:
//		BK1_2_Status = 0x01;
//		break;
//	case ENC_2TIMES:
//	case ENC_3TIMES:
//	case ENC_4TIMES:
//	case ENC_5TIMES:
//	case ENC_6TIMES:
//	case ENC_7TIMES:
//		BK1_2_Status = (UBYTE)((Setting << 1) & ~IO_BIT_ENC);
//		break;
//	}
//	outpw(BK1_2_PORT,BK1_2_Status);
//}
//
//
///*************************************************************************
//	module		:[両端白マスク有効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53]
//	language	:[MS-C(Ver.6.0)]
//	keyword		:[CMN]
//	date		:[1994/03/16]
//	author		:[木元　修]
//*************************************************************************/
//void BothEndsWhiteMaskEnable(void)
//{
//	BK1_2_Status |= IO_BIT_SHEN;
//	outpw(BK1_2_PORT,BK1_2_Status);
//}
//
//
///*************************************************************************
//	module		:[両端白マスク無効]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53]
//	language	:[MS-C(Ver.6.0)]
//	keyword		:[CMN]
//	date		:[1994/03/16]
//	author		:[木元　修]
//*************************************************************************/
//void BothEndsWhiteMaskDisable(void)
//{
//	BK1_2_Status &= ~IO_BIT_SHEN;
//	outpw(BK1_2_PORT,BK1_2_Status);
//}
#endif
#endif

/*************************************************************************
	module		:[ゲートアレーの初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[INI]
	date		:[1994/04/13]
	author		:[木元　修]
*************************************************************************/
UBYTE DBG_io = 0;
void far InitializeGateArray(void)
{
/* Ｇ／Ａの初期設定の間は割り込み禁止とします By O.K Dec,27,1994 **/
UBYTE i = 0;	/* test */

/*		CLI		後で割り込み禁止にする */
	CMN_DisableInterrupt();	/* 1998/08/10 */

	/*---------------------------------------------------------------------
	** プリント用初期化
	** 1998/09/14 H.Yoshikawa
	** このタイミングで初期化するまえに１０ｍｓ割り込みがすでに発生しているために、
	** カッターが動作したり、不穏な動作をしてしまいます。
	** この部分を関数化し、できるだけ早く初期化するようにします。
	*/
#if (0)	/* 1998/10/28 H.Yoshikawa */
	PRN_LineMemoryStatus = 0;	/* 1998/07/20 K.Kawata*/
	PRN_Control.Command = 0;
	PRN_Control.CutterBusy = 0;
	CutToPrintExecFlag = 0;
	ImageLineStartPoint = 0;
#endif
	PRN_Control.Error = 0;	/* 1999.8.5 K.Kawata ﾒﾓﾘｰ受信でのｸﾘｱを追加*/
	BK1_1_Status	= 0xc0;		/** バスＩ／Ｆレジスタ **/
	outpw(BK1_1_PORT,BK1_1_Status);
	BK2_Status		= 0x0c;		/** ＲＡＭＩ／Ｆレジスタ **/
	outpw(BK2_PORT,BK2_Status);
	BK4_1_Status	= 0x00;		/** 検索コードレジスタ１ **/
	outpw(BK4_1_PORT,BK4_1_Status);
	BK4_2_Status	= 0x00;		/** 検索コードレジスタ２ **/
	outpw(BK4_2_PORT,BK4_2_Status);
	BK4_3_Status	= 0x00;		/** 検索コードレジスタ３ **/
	outpw(BK4_3_PORT,BK4_3_Status);
	BK4_4_Status	= 0x00;		/** 検索コードレジスタ４ **/
	outpw(BK4_4_PORT,BK4_4_Status);
	BK4_5_Status	= 0x00;		/** 検索コードレジスタ５ **/
	outpw(BK4_5_PORT,BK4_5_Status);
	BK4_6_Status	= 0x00;		/** 検索コードレジスタ６ **/
	outpw(BK4_6_PORT,BK4_6_Status);
	SUNO_Status		= 0x00;		/** スムージング／ノッチレジスタ **/
	outpw(SUNO_PORT,SUNO_Status);
	VNO_Status		= 0x00;		/** 縦ノッチレジスタ **/
	outpw(VNO_PORT,VNO_Status);
	HNO_Status		= 0x00;		/** 横ノッチレジスタ１ **/
	outpw(HNO_PORT,HNO_Status);
	KORITU_W_Status	= 0x00;		/** 孤立点レジスタ１ **/
	outpw(KORITU_W_PORT,KORITU_W_Status);
	KORITU_B_Status	= 0x00;		/** 孤立点レジスタ２ **/
	outpw(KORITU_B_PORT,KORITU_B_Status);
	SYSSR_Status	= 0x00;		/** システムステータス（エッジ検出）レジスタ **/
	outpw(SYSSR_PORT,SYSSR_Status);
	BK6_Status		= 0x00;		/** スルーレジスタ **/
	outpw(BK6_PORT,BK6_Status);
	BK1_2_Status	= 0x00;		/** 拡大レジスタ **/
	outpw(BK1_2_PORT,BK1_2_Status);

	A_MCR1_Status	= 0x00;
	outpw(A_MCR1_PORT,A_MCR1_Status);
	A_MCR2_Status	= 0x09;	/** ｒｅｖ．Ｃのメインではモーターの正転／逆転が反対 **//**  By O.K Aug,23,1994 **/
	outpw(A_MCR2_PORT,A_MCR2_Status);
	B_MCR1_Status	= 0x00;
	outpw(B_MCR1_PORT,B_MCR1_Status);
	B_MCR2_Status	= 0x01;	/** ｒｅｖ．Ａのメインではモーターの正転／逆転が反対 **/
	outpw(B_MCR2_PORT,B_MCR2_Status);
	C_MCR1_Status	= 0x00;
	outpw(C_MCR1_PORT,C_MCR1_Status);
	C_MCR2_Status	= 0x03;	/** ｒｅｖ．Ａのメインではモーターの正転／逆転が反対 **/
	outpw(C_MCR2_PORT,C_MCR2_Status);
	SYSCR_Status = 0x78;	/*1998.8.18 K.Kawata*/
	outpw(SYSCR_PORT,SYSCR_Status);
	TRCR_Status = 0x5C;
	outpw(TRCR_PORT,TRCR_Status);
	TROSS_Status = 0x02;
	outpw(TROSS_PORT,TROSS_Status);
	TROF1_Status = 0x10;
	outpw(TROF1_PORT,TROF1_Status);
	TROF2_Status = 0x40;
	outpw(TROF2_PORT,TROF2_Status);
	STCR2_Status = 0xf0;/***e0***/
	outpw(STCR2_PORT,STCR2_Status);
	STCR3_Status = 0x00;/***0x01***/
	outpw(STCR3_PORT,STCR3_Status);
	STCR4_Status = 0x00;
	outpw(STCR4_PORT,STCR4_Status);
	STCR1_Status	= 0x00;		/** コントロールレジスタ１（ヒートパルス幅設定レジスタ） **/
	outpw(STCR1_PORT,STCR1_Status);
	TRISA_Status	= 0x00;		/** 入力データスタートアドレスレジスタ **/
	outpw(TRISA_PORT,TRISA_Status);
	TRIEA_Status	= 0xff;		/** 入力データエンドアドレスレジスタ **/
	outpw(TRIEA_PORT,TRIEA_Status);
/** このポートは入力ポート
	SCR_Status		= 0x00;		** システムステータスレジスタ１ **
	outpw(SCR_PORT,SCR_Status);
**/
	SMCR_Status	= 0x00;	/** システムステータスレジスタ２ **/
	outpw(SMCR_PORT,SMCR_Status);
	STCR5_Status	= 0x00;
	outpw(STCR5_PORT,STCR5_Status);
	/** ＭＤ９４０２用各状態変数 **/
	M01_Status		= 0x0E;		/** 割り込み発生ﾀｲﾐﾝｸﾞ=0ms、割り込み発生周期=2.5ms **//** 2000Hz **/
	outpw(MD9402_M01_PORT,M01_Status);
	M02_Status		= 0x00;
	outpw(MD9402_M02_PORT,M02_Status);
	M03_Status		= 0x80;
	outpw(MD9402_M03_PORT,M03_Status);
	M04_Status		= 0x00;
	outpw(MD9402_M04_PORT,M04_Status);
	M05_Status		= 0x00;
	outpw(MD9402_M05_PORT,M05_Status);
	M06_Status		= 0x00;					/** 出力データシリアルスピード＝５ＭＨｚ **/
	outpw(MD9402_M06_PORT,M06_Status);
	M07_Status		= 0x00;
	outpw(MD9402_M07_PORT,M07_Status);
	M08_Status		= 0x04;
	outpw(MD9402_M08_PORT,M08_Status);
	M09_Status		= 0x00;
	outpw(MD9402_M09_PORT,M09_Status);
	/*---------------------------------------------------------------------
	** ＭＤ９８０５用各状態変数
	** 1998/06/22
	*/
	/*-----------------------------------------------------------
	** SDMAR_PORT
	** SSDMA	SHのDMAモードをシングルモードで使用する場合：	０：スタート	･･･ SAKAKI（I/O側はアドレス固定している）
	**						   デュアルモードで使用する場合：	１：ストップ	･･･ ATLANTA(Memory to Memoryのため）
	** SCKCLR/LNSTCLR/PHTGCLR	MD9401の不具合調査用に使用していたもので、０固定で使用する
	** DWAIT0～DWAIT3			SSDMAが０の時に設定する。SAKAKIでは外部I/Oは３Waitアクセスとする。
	** 1998/06/22
	**
	** SSDMA が 1 のとき、シングルモード DMA 転送可能。SSDMA の値に関係なく、デュアルアドレスモードの DMA 転送は可能。
	** SSDMA は常に 1 とする。また、ウェイトサイクル数は、 DRAM 領域のウェイト数に合わせるべきである。
	** by H.Kubo 1998/08/10
	*/
	/* SYS_SDMAR_PortStatus = IO_BIT_DWAIT3; */
#if 0 /* DRAM 空間は１ウェイトでした。 Changed by H.Kubo 1998/09/29 */
@@	SYS_SDMAR_PortStatus = (IO_BIT_SSDMA | IO_BIT_DWAIT3);
#else
	SYS_SDMAR_PortStatus = (IO_BIT_SSDMA | IO_BIT_DWAIT1);
#endif
	outpw(SDMAR_PORT,SYS_SDMAR_PortStatus);
	/*-----------------------------------------------------------
	** RTC_PORT(SAKAKIではRTCR_PORT)
	** RTCの設定は、別のところで行っているので、ここでは実施しない。
	** 1998/06/22
	*/							   
	/*-----------------------------------------------------------
	** MCR_PORT(SAKAKIで追加)
	** MCRの設定は、void INT_InitializeExternalInterrupt(void)で行っているので、ここでは実施しない。
	** 1998/06/22
	*/							   
	/*-----------------------------------------------------------
	** INT_MASK_PORT(MD9508ではMCINTR_PORT)
	** 外部割り込み端子の設定は、別のところで行っているので、ここでは実施しない。
	** 1998/06/22
	*/							   
/*		STI		あとで割り込み許可する */
	CMN_EnableInterrupt();	/* 1998/08/10 */
	
	/*-----------------------------------------------------------
	** I/OのRead/Writeテスト用です。
	** 1998/06/24
	*/			
	DBG_io = 0;				   
	if (DBG_io == 1) {
		LampOn();
		i = DS1();

		B_MCR2_Status	= 0xF3;	/** ｒｅｖ．Ａのメインではモーターの正転／逆転が反対 **/
		outpw(B_MCR2_PORT,B_MCR2_Status);
		B_MCR1_Status	= 0x0A;
		outpw(B_MCR1_PORT,B_MCR1_Status);

		B_MCR2_Status	= 0xF3;	/** ｒｅｖ．Ａのメインではモーターの正転／逆転が反対 **/
		outpw(B_MCR2_PORT,B_MCR2_Status);
		B_MCR1_Status	= 0x0A;
		outpw(B_MCR1_PORT,B_MCR1_Status);
	}

	DIPPST_Req = 0;			/* 1998/08/13 */
	GaInterruptFlag = 0;	/** By O.K Oct,24,1994 **/
	GA_BuzzerFlag = 0;		/** By O.K Nov,2,1994 **/
	DIPP_InitialSet();                               /** DIPP-AS初期設定 */
	GaInterruptEnable();
	GaInterruptFlag |= INT_SCANNER;
	wai_tsk(100);
	DIPPST_Req = 1;

	while (DIPPST_Req) {
		wai_tsk(1);
	}

	GaInterruptFlag &= ~INT_SCANNER;
	GaInterruptDisable();
	DIPP_SetBitDIPPST(IDP_BIT_OFF);

	/*---------------------------------------------------------------------
	** MD9402が発生させるG/A割り込みタイミングを決める。
	** 電源ON時はPRN用の設定とします。
	** SCN用の設定へは、SCNが使用するときのみ切り替えます。
	** 1998/10/13
	*/
	PRN_MD9402_INT_Timing();

	/*---------------------------------------------------------------------
	** SCN・PRNのDual動作制御変数
 	** UBYTE SYS_PRN_StopRequest
 	**		SCNからPRNへの指示で、プリントを停止させたい時にTRUEにする
 	** UBYTE SYS_SCN_StartRequest
 	**		PRNからSCNへの指示で、SYS_PRN_StopRequestを認識したので、
 	**		読み取りを開始してもよい時にTRUEにする
 	** 1998/10/26	H.Yoshikawa
	*/
	SYS_PRN_StopRequest = FALSE;
	SYS_SCN_StartRequest = TRUE;

	/*---------------------------------------------------------------------
	** SCN・プリンタ受信PRNのDual動作制御変数
	** UBYTE SYS_SCN_StopRequest
	**		PRNからSCNへの指示で、読み取りを停止させたい時にTRUEにする
	** UBYTE SYS_PRN_StartRequest
	**		SCNからPRNへの指示で、SYS_SCN_StopRequestを認識したので、
	**		プリントを開始してもよい時にTRUEにする
	** プリンタ受信有効・無効設定が有効のときのみ使用する
	** SCN_PRN_StopRequest/SYS_SCN_StartRequestより優先的に処理する
	** 1999/02/24
	** H.Yoshikawa
	**/
	SYS_SCN_StopRequest = FALSE;
	SYS_PRN_StartRequest = TRUE;

	/*---------------------------------------------------------------------
	** MDM・PRNのDual動作制御変数
 	** UBYTE SYS_PRN_StopRequest
 	**		MDMからPRNへの指示で、プリントを停止させたい時にTRUEにする
 	** 1998/10/26 H.Yoshikawa
	*/
	SYS_PRN_StopRequestFromModem = FALSE;

#if (0)	/* たぶん不要と思うので、削除しておく 1998/06/13 */
	/** 黒帯対策 By O.K Apr,21,1995 **/
	PRN_Control.UseType			= IDP_LIST_PRINT;
	IP_Control[IDP_NO1].IP_UseType = IDP_LIST_PRINT;	/** データの経路をSYS-BUS -> 拡張RAM -> IP -> シリアルに設定する為に **/
	SetIRQInterval(IRQTIM_0MS);
	LineBufferClear(IDP_NO1,(unsigned char)0);
#endif

}

/*************************************************************************
	module		:[PRN用MD9402関係の変数を初期化する]
	function	:[
		1.
	]
	return		:[]
	common		:[
		1.
	]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[SCN]
	date		:[1998/10/13]
	author		:[吉川弘康]
*************************************************************************/
void PRN_Init10msParameters(void)
{
	PRN_LineMemoryStatus = 0;
	PRN_Control.Command = 0;
	PRN_Control.CutterBusy = 0;
	PRN_Control.PrinterRxMode = 0;	/*1999.2.26 K.Kawata*/
	CutToPrintExecFlag = 0;
	ImageLineStartPoint = 0;
}

/*************************************************************************
	module		:[PRN用MD9402の割り込みタイミングに設定する]
	function	:[
		1.
	]
	return		:[]
	common		:[
		1.待機状態を含め、SCN中以外は、この設定にします。
	]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[SCN]
	date		:[1998/10/13]
	author		:[吉川弘康]
*************************************************************************/
void PRN_MD9402_INT_Timing(void)
{
	switch (SYB_MaintenanceSwitch[MNT_SW_E7] & PRN_MD9402_IRQTIME_375MS) {
	case PRN_MD9402_IRQTIME_000MS:
		SetIRQInterval(IRQTIM_0MS);
		break;
	case PRN_MD9402_IRQTIME_125MS:
		SetIRQInterval(IRQTIM_1_25MS);
		break;
	case PRN_MD9402_IRQTIME_250MS:
		SetIRQInterval(IRQTIM_2_5MS);
		break;
	case PRN_MD9402_IRQTIME_375MS:
	default:
		SetIRQInterval(IRQTIM_3_75MS);
		break;
	}
}

#if 0
/*************************************************************************
	module		:[通信コーデックの DMA をシングルアドレスモード用の結線にする。]
	function	:[
		1.	通信コーデックの DMA をシングルアドレスモード用の結線にする
		2.	シングルアドレスモードでのウェイトサイクル数を設定する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
			MD9805 のレジスタの設定です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/08/10]
	author		:[久保博]
*************************************************************************/
void ComCODEC_DMA_SingleAdressMode(UBYTE wait_cycle)
{
	SYS_SDMAR_PortStatus &= ~IO_BIT_DWAIT15;
	SYS_SDMAR_PortStatus |= (IO_BIT_SSDMA | (wait_cycle << 4));
	outpw(SDMAR_PORT,SYS_SDMAR_PortStatus);
	return;
}
/*************************************************************************
	module		:[通信コーデックの DMA をデュアルアドレスモード用の結線にする。]
	function	:[
		1.	通信コーデックの DMA をシングルアドレスモード用の結線にする
		2.	シングルアドレスモードでのウェイトサイクル数を設定する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
			MD9805 のレジスタの設定です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/08/10]
	author		:[久保博]
*************************************************************************/
void ComCODEC_DMA_DualAdressMode(void)
{
	SYS_SDMAR_PortStatus &= ~IO_BIT_SSDMA;
	outpw(SDMAR_PORT,SYS_SDMAR_PortStatus);
	return;
}
#endif

/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[1999/3/2]
	author		:[K.Kawata]
*************************************************************************/
UBYTE	CHK_OCA_Specification(void)
{
	return(ROM_Switch[ROM_SW_OCA_SPEC] & OCA_SPEC);
}

