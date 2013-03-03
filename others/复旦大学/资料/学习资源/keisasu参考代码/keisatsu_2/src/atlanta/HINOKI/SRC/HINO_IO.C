/************************************************************************
*	System		: HINOKI
*	File Name	: CMN_IO.C <HINO_IO.C>
*	Author		: 木元修
*	Date		: 1998/09/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_io.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\syslocal.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\status.h"

#include "\src\atlanta\define\unisw_h.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mntsw_g.h" /* Add By H.Hirao 1998/10/16 */

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\scn_data.h"

#include "\src\atlanta\ext_v\sys_port.h"

#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\atlanta\sh7043\define\io_pro.h"

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"	/* Add By O.Kimoto 1997/10/08 */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"	/* Add By O.Kimoto 1997/12/03 */
#include "\src\atlanta\mdm\pana\define\mdm_io.h"	/* Add By O.Kimoto 1997/12/03 */
#endif
#if (PRO_MODEM == R288F)
	#if defined(HINOKI3)
		#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
		#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
		#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
	#else
		#include "\src\atlanta\mdm\r288f\define\mdm_def.h"	/* Add By O.Kimoto 1997/10/08 */
		#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"	/* Add By O.Kimoto 1997/12/03 */
		#include "\src\atlanta\mdm\r288f\define\mdm_io.h"	/* Add By O.Kimoto 1997/12/03 */
	#endif
#endif

#include "\src\atlanta\hinoki\define\m_param.h"	/* ＰＳ２ Ａ／Ｄ変換対応 By O.Kimoto 1999/03/29 */

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
#include "\src\atlanta\hinoki\define\hino_sys.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"	/* Add by Y.Kano 2004/03/01 */
  #if (0)	/* ＰＳ２自動調整機能 削除 by Y.Kano 2004/04/05 */
extern UBYTE	PS2_SensorStatus;			/* ＰＳ２のスライスレベルステータス */
  #endif
  #if (PRO_PAPER_AD_SENSOR_INIT == DISABLE)
#include "\src\atlanta\define\sysprint.h"	/* Add by Y.Kano 2004/12/10 */
#include "\src\atlanta\ext_v\bkupram.h"		/* Add by Y.Kano 2004/12/10 */
  #endif
#endif	/* End of defined(HINOKI2) */

/*------------------------------------------------------------------------
**	＜＜＜　入力(Input)　＞＞＞
*/

#if defined (KEISATSU) /* Added by SMuratec 李 2005/07/05 */
#include	"\src\atlanta\define\sys_line.h"


/*************************************************************************
	module		:[HDST使用可能性のチェック]
	function	:[
		1.HDST使用可能性かチェックする。
	]
	return		:[	０：可能
					１：不可
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[2005/07/28]
	author		:[SMuratec 李]
*************************************************************************/
UBYTE 	Is_HDST_Disable(void)
{
	if (RelayPortStatus & IO_BIT_HDST_OFF) {
		return(1);
	}
	return(0);
}
#endif /* defined (KEISATSU) */

#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
/*************************************************************************
	module		:[音声 送出選択]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[出力信号選択]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	SelectVOL(void)
{
	IO__PADRH |= IO_BIT_SELVOI;
}


/*************************************************************************
	module		:[Melody/Tx 送出選択]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[出力信号選択]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	SelectMELorTX(void)
{
	IO__PADRH &= (~IO_BIT_SELVOI);
}
#endif


/*************************************************************************
	module		:[ＤＴＭＦの確定・未確定のチェック]
	function	:[
		1.
	]
	return		:[
				1:確定
				0:未確定
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
UBYTE	DTMF_Decision(void)
{
#if defined (HINOKI2) || defined(HINOKI3)	/* HINOKI2ではDTMF検出はモデムで行う 2002/01/10 T.Takagi */
	return (0);
#else
	if (IO__PADRH & IO_BIT_DV) {	/*ＡＮＺＵ＿Ｌは未使用*/
		return (1);
	}
	return (0);
#endif
}


/*************************************************************************
	module		:[ダイヤルイン設定]
	function	:[
		1.	ポートをリードして状態を調べる
	]
	return		:[
		0 :	ダイヤルイン未設定
		1 :	ダイヤルイン設定
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/07]
	author		:[橘正樹]
*************************************************************************/
UBYTE	DialIn(void)
{
#if (PRO_DIALIN == ENABLE)
	if (IO__PADRH & IO_BIT_EST) {
		return (1);
	}
#endif
	return (0);
}


/*************************************************************************
	module		:[カッター位置]
	function	:[
		1.	ポートをリードしてカッターがどの位置にあるかを調べる
	]
	return		:[
		0 :	未定位置
		1 :	定位置
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/07]
	author		:[橘正樹]
*************************************************************************/
UBYTE CutterPosition(void)
{
	if (IO__PADRH & IO_BIT_XCIS) {
		return (1);
	}
	return (0);
}


/*************************************************************************
	module		:[サーマルヘッドメーカー識別]
	function	:[
		1.	ポートをリードして接続されているサーマルヘッドメーカーを識別する。
	]
	return		:[
		0 :	ローム
		1 :	京セラ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/07]
	author		:[橘正樹]
*************************************************************************/
UBYTE ThermalHeadMaker(void)
{
	if (IO__PADRH & IO_BIT_KY_RO) {
		return (1);
	}
	return (0);
}

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/19 T.Takagi */
/*************************************************************************
	module		:[クロック供給（Halt CLK）]
	function	:[
		1.	HCLKをONにし、LSI、通信CODECへのクロックを供給する。
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[2001/11/19]
	author		:[高木智史  T.Takagi]
*************************************************************************/
void HaltClockOn(void)
{
	IO__PADRH |= IO_BIT_HCLK;
}
/*************************************************************************
	module		:[クロック停止（Halt CLK）]
	function	:[
		1.	HCLKをOFFにし、LSI、通信CODECへのクロックを停止する。
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[2001/11/19]
	author		:[高木智史  T.Takagi]
*************************************************************************/
void HaltClockOff(void)
{
	IO__PADRH &= ~IO_BIT_HCLK;
}
#endif

/*************************************************************************
	module		:[ＤＴＭＦ信号獲得]
	function	:[
		1.	ポートをリードして受信したＤＴＭＦ信号をＧｅｔする。
	]
	return		:[
		定義が分からないので、とりあえず、下４ビットに変換だけしておきます。
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/07]
	author		:[橘正樹]
*************************************************************************/
UBYTE	DTMF_Code(void)
{
#if defined (HINOKI2) || defined(HINOKI3)	/* HINOKI2ではDTMF検出はモデムで行う 2002/01/10 T.Takagi */
#else
	return(UBYTE)((IO__PADRL & (IO_BIT_DTMF1 | IO_BIT_DTMF2 | IO_BIT_DTMF3 | IO_BIT_DTMF4)) >> 6);
#endif
}


#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
/*************************************************************************
	module		:[音声LSI有無の識別]
	function	:[]
	return		:[
		1:無
		0:有
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
UBYTE	CheckConnectVoiceLSI(void)
{
	if (IO__PADRL & IO_BIT_XVOICIR) {
		return(1);	/* 無 */
	}
	else {
		return(0);	/* 有 */
	}
}


/*************************************************************************
	module		:[音声ＬＳＩ擬似ビジー]
	function	:[]
	return		:[
		1:Empty
		0:Full
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
UBYTE	NAR(void)
{
	if (IO__PADRL & IO_BIT_VOINAR) {
		return(1);	/* 空 */
	}
	else {
		return(0);	/* 満 */
	}
}


/*************************************************************************
	module		:[音声ＬＳＩ リセットＯＮ]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[なし]
	comment		:[
		負論理で動いているので，bitを落としてONになります．
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	CMN_ResetOnAnswerLSI(void)
{
	IO__PADRL &= (~IO_BIT_VOIRES);
}


/*************************************************************************
	module		:[音声ＬＳＩ リセットＯＦＦ]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[なし]
	comment		:[
		負論理で動いているので，bitを立ち上げてOFFになります．
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	CMN_ResetOffAnswerLSI(void)
{
	IO__PADRL |= IO_BIT_VOIRES;
}


/*************************************************************************
	module		:[音声LSI アドレス取込]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[なし]
	comment		:[
		負論理で動いているので，bitを落としてONになります．
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	CMN_AnswerLSIOn(void)
{
	IO__PADRL &= (~IO_BIT_VOIST);
}


/*************************************************************************
	module		:[音声LSI 動作スタート]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[なし]
	comment		:[
		負論理で動いているので，bitを立ち上げてOFFになります．
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	CMN_AnswerLSIOff(void)
{
	IO__PADRL |= IO_BIT_VOIST;
}


/*************************************************************************
	module		:[音声ＬＳＩ フレーズセット]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		IO_BIT_VOII0
		IO_BIT_VOII1
		IO_BIT_VOII2 を使ってます．
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	CMN_SetFraseAnswerLSI(UWORD frase)
{
	IO__PADRL &= 0xFC7F;
	IO__PADRL |= (frase << 7);
}


#endif


/*************************************************************************
	module		:[京セラサーマルヘッド抵抗値ランク指定]
	function	:[
		1.	ポートをリードして京セラサーマルヘッドの抵抗値ランクをＧｅｔする。
	]
	return		:[
		0 :	３００１～３３００Ω
		1 :	２７００～３０００Ω
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/07]
	author		:[橘正樹]
*************************************************************************/
UBYTE ThermalHeadRank(void)
{
	if (IO__PDDRH & IO_BIT_RANK) {
		return (1);
	}
	return (0);

}


#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
/*************************************************************************
	module		:[テストランド13]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[High固定で使います]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	SetTestLand13_On(void)
{
	IO__PDDRH |= IO_BIT_TL13;
}


/*************************************************************************
	module		:[テストランド13]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[High固定で使います]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	SetTestLand13_Off(void)
{
	IO__PDDRH &= ~IO_BIT_TL13;
}
#else


/*************************************************************************
	module		:[（ＲＳ－２３２Ｃ）データ端末レディ]
	function	:[
		1.	ポートをリードしてＤＴＲの状態を調べる
	]
	return		:[
		0 :	Ｎｏｔ Ｒｅａｄｙ
		1 :	Ｒｅａｄｙ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/07]
	author		:[橘正樹]
*************************************************************************/
UBYTE Check_DTR(void)
{
	if (IO__PDDRH & IO_BIT_RS_DTR) {
		return (1);
	}
	return (0);
}
#endif


/*************************************************************************
	module		:[ＲＴＣデータリード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
UBYTE	RTC_DataRead(void)
{
	if (IO__PEDR & IO_BIT_RTCDT) {
		return (1);
	}
	return (0);
}

/*************************************************************************
	module		:[ディップスイッチの状態を獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/07]
	author		:[江口]
*************************************************************************/
UBYTE	DSW(void)
{
	return((UBYTE)((IO__PFDR & (IO_BIT_DSW0 | IO_BIT_DSW1 | IO_BIT_DSW2 | IO_BIT_DSW3)) >> 1));
}


/******************************************************************************
	module		:[記録紙センサ1の出力値]
	function	:[
	]
	return		:[
		1:	XPS1がLow(記録紙有り)
		0:	XPS1がHigh(記録紙無し)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/2/21]
	author		:[S.Kawasaki]
******************************************************************************/
UBYTE	PS1(void)
{
#if defined(HINOKI3)
 #if (1)	/* PS1をポート読みにします。by Y.Kano 2004/12/25 */
  #if (1)	/* A/D変換器を制御追加 by Y.Kano 2005/01/07 */
	UBYTE	PaperStatus;

	PaperStatus = 0;

	AD__ADCSR0 &= ~ADCSR0_ADST;	/* A/D変換器を止めます。by Y.Kano 2005/01/07 */
	if (IO__PFDR & IO_BIT_XPS1) {
		PaperStatus = 0;	/* 記録紙無し */
	}
	else {
		PaperStatus = 1;	/* 記録紙有り */
	}
	AD__ADCSR0 |= ADCSR0_ADST;	/* A/D変換器をスタートします。by Y.Kano 2005/01/07 */
	return(PaperStatus);
  #else
	if (IO__PFDR & IO_BIT_XPS1) {
		return(0);
	}
	return(1);
  #endif
 #else
**	if ((UWORD)AD_PS1() > ((UWORD)(SYB_MachineParameter[M_PARA_SW_J1]))) {	/* 閾値は計算で求まる */
**		AD_PS1_Value = 0;	/* 紙なし */
**	}
**	else {
**		AD_PS1_Value = 1;	/* 紙あり */
**	}
**	return (AD_PS1_Value);
 #endif
#else
	if (InputWORD(GA_PGBDR) & IO_BIT_XPS1) {
		return(0);
	}
	return(1);
#endif
}


/******************************************************************************
	module		:[記録紙センサ2の出力値]
	function	:[
	]
	return		:[
		1:	XPS2がLow(記録紙有り)
		0:	XPS2がHigh(記録紙無し)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/2/21]
	author		:[S.Kawasaki]
******************************************************************************/
UBYTE	PS2(void)
{

#if (0)
** 	/* ＰＳ２ Ａ／Ｄ変換対応
** 	** ＰＳ２センサーは、ポート直値からＡ／Ｄへ変更します。
** 	** この変更はメインのリワークとセットでないと動作しませんので注意してください。
** 	** By O.Kimoto 1999/03/29
** 	*/
** 	if (InputWORD(GA_PGBDR) & IO_BIT_XPS2) {
** 
** 		return(0);
** 	}
** 	return(1);
#else
/*
** 検出電圧
** ヒステリシスをもたせるように変更します
**　８ｂｉｔフル：Ａ／Ｄ値２５５－＞５．０Ｖ　で計算しますと
**①Ｈ－＞Ｌ（紙なし－＞紙あり）
**　２．３／５．０＊２５５＝１１７．３（７５ｈ）
**②Ｌ－＞Ｈ（紙あり－＞紙なし）
**　２．７／５．０＊２５５＝１３７．７（８Ａｈ）
**となります．
**　①　と　（②－①）　はメモリスイッチにして下さい．
** 1999/04/13 by T.Soneoka
*/
#if (0)
**	if ((UWORD)AD_PS2() > (UWORD)SYB_MachineParameter[M_PARA_SW_J0]) {
** 		return(0);
**	}
**	else {
**		return(1);
**	}
#else
  #if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* ＰＳ２自動調整機能 by Y.Kano 2004/04/05 */
   #if (1) /* J4を参照する処理が抜けていた。 2004/12/09 */
	if ((SYS_DocumentPrintClass == SYS_PRINT_CLASS_INITIAL) && (SYB_PS2_SensorStatus == VSIM2_THRESHOLD)) {
		if ((UWORD)AD_PS2() > ((UWORD)(SYB_MachineParameter[M_PARA_SW_J4]))) {	/* 閾値は計算で求まる */
			AD_PS2_Value = 0;	/* 紙なし */
		}
		else {
			AD_PS2_Value = 1;	/* 紙あり */
		}
	}
	else {
		if ((UWORD)AD_PS2() > ((UWORD)(SYB_MachineParameter[M_PARA_SW_J6]))) {	/* 閾値は計算で求まる */
			AD_PS2_Value = 0;	/* 紙なし */
		}
		else {
			AD_PS2_Value = 1;	/* 紙あり */
		}
	}
	return (AD_PS2_Value);
   #else
	if ((UWORD)AD_PS2() > ((UWORD)(SYB_MachineParameter[M_PARA_SW_J6]))) {	/* 閾値は計算で求まる */
		AD_PS2_Value = 0;	/* 紙なし */
	}
	else {
		AD_PS2_Value = 1;	/* 紙あり */
	}
	return (AD_PS2_Value);
   #endif
  #elif	defined(HINOKI3) && (PRO_PAPER_AD_SENSOR_INIT == ENABLE)	/* HINOKI3ﾊﾞｰｼﾞｮﾝ */
	if ((UWORD)AD_PS2() > ((UWORD)(SYB_MachineParameter[M_PARA_SW_J2]))) {	/* 閾値は計算で求まる */
		AD_PS2_Value = 0;	/* 紙なし */
	}
	else {
		AD_PS2_Value = 1;	/* 紙あり */
	}
	return (AD_PS2_Value);
  #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	if (AD_PS2_Value) {
		/* 紙ありのとき */
		if ((UWORD)AD_PS2() > ((UWORD)(SYB_MachineParameter[M_PARA_SW_J0] + SYB_MachineParameter[M_PARA_SW_J1]))) {	/* 閾値２．７Ｖ */
			AD_PS2_Value = 0;	/* 紙なし */
		}
		else {
			AD_PS2_Value = 1;	/* 紙あり */
		}
	} else {
		/* 紙なしのとき */
		if ((UWORD)AD_PS2() > ((UWORD)SYB_MachineParameter[M_PARA_SW_J0])) {	/* 閾値２．３Ｖ */
			AD_PS2_Value = 0;	/* 紙なし */
		}
		else {
			AD_PS2_Value = 1;	/* 紙あり */
		}
	}
	return (AD_PS2_Value);
  #endif
#endif
#endif

}

/******************************************************************************
	module		:[記録紙サイズの出力値]
	function	:[
	]
	return		:[
		1:	XPS2がLow(Ｂ４記録紙)
		0:	XPS2がHigh(Ａ４記録紙)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/2/21]
	author		:[S.Kawasaki]
******************************************************************************/
UBYTE	PB4(void)
{
#if defined(HINOKI3)
 #if (1)	/* PB4をポート読みにします。by Y.Kano 2004/12/25 */
  #if (1)	/* A/D変換器を制御追加 by Y.Kano 2005/01/07 */
	UBYTE	PaperStatus;

	PaperStatus = 0;

	AD__ADCSR1 &= ~ADCSR1_ADST;	/* A/D変換器を止めます。by Y.Kano 2005/01/07 */
	if (IO__PFDR & IO_BIT_XPB4) {
		PaperStatus = 0;	/* A4記録紙 */
	}
	else {
		PaperStatus = 1;	/* B4記録紙 */
	}
	AD__ADCSR1 |= ADCSR1_ADST;	/* A/D変換器をスタートします。by Y.Kano 2005/01/07 */
	return(PaperStatus);
  #else
	if (IO__PFDR & IO_BIT_XPB4) {
		return(0);
	}
	return(1);
  #endif
 #else
**	if ((UWORD)AD_PB4() > ((UWORD)(SYB_MachineParameter[M_PARA_SW_J3]))) {	/* 閾値は計算で求まる */
**		AD_PB4_Value = 0;	/* 紙なし */
**	}
**	else {
**		AD_PB4_Value = 1;	/* 紙あり */
**	}
**	return (AD_PB4_Value);
 #endif
#else
	if (InputWORD(GA_PGBDR) & IO_BIT_XPB4) {

		return(0);
	}
	return(1);
#endif
}

/******************************************************************************
	module		:[フラッシュステート]
	function	:[
	]
	return		:[
		1:	Ｒｅａｄｙ
		0:	Ｂｕｓｙ
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/2/21]
	author		:[S.Kawasaki]
******************************************************************************/
UBYTE	RY_BY(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_RY_BY) {

		return(1);
	}
	return(0);
}


/******************************************************************************
	module		:[スキャナー・カバーのインターロックの出力値]
	function	:[
		1.SH7043のポート６０Ｈを読み込み
		2.TXILのビットが立っているかチェック
	]
	return		:[
		0:	TXILがLow(TXカバー・クローズ)
		1:	TXILがHigh(TXカバー・オープン)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/2/21]
	author		:[S.Kawasaki]
******************************************************************************/
UBYTE	TXIL(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_TXIL) {
		return(1);
	}
	return(0);
}


/******************************************************************************
	module		:[プリンター・カバーのインターロックの出力値]
	function	:[
		1.ポートの読み込み
		2.RXILのビットが立っているかチェック
	]
	return		:[
		0:	RXILがLow(RXカバー・クローズ)
		1:	RXILがHigh(RXカバー・オープン)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/07]
	author		:[橘正樹]
******************************************************************************/
UBYTE	RXIL(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_TOPOP) {
		return(1);
	}
	return(0);
}

/******************************************************************************
	module		:[原稿センサ1の出力値]
	function	:[
		1.SH7043のポート６０Ｈを読み込み
		2.XDS1のビットが立っているかチェック
	]
	return		:[
		1:	XDS1がLow(原稿有り)
		0:	XDS1がHigh(原稿無し)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/2/21]
	author		:[S.Kawasaki]
******************************************************************************/
UBYTE	DS1(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_XDS1) {

		return(0);
	}
	return(1);
}

/******************************************************************************
	module		:[原稿センサ2の出力値]
	function	:[
		1.SH7043のポート６０Ｈを読み込み
		2.XDS2のビットが立っているかチェック
	]
	return		:[
		1:	XDS2がLow(原稿有り)
		0:	XDS2がHigh(原稿無し)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/2/21]
	author		:[S.Kawasaki]
******************************************************************************/
UBYTE	DS2(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_XDS2) {
		return(0);
	}
	return(1);
}

/******************************************************************************
	module		:[B4原稿センサの出力値]
	function	:[
		1.SH7043のポート６０Ｈを読み込み
		2.XDB4のビットが立っているかチェック
	]
	return		:[
		1:	XDB4がLow(B4原稿有り)
		0:	XDB4がHigh(B4原稿無し)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/2/21]
	author		:[S.Kawasaki]
******************************************************************************/
UBYTE	DB4(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_XDB4) {
		return(0);
	}
	return(1);
}


/******************************************************************************
	module		:[A3原稿センサの出力値]
	function	:[
		1.SH7043のポート00C20102Ｈを読み込み
		2.XDA3のビットが立っているかチェック
	]
	return		:[
		1:	XDA3がLow(A3原稿有り)
		0:	XDA3がHigh(A3原稿無し)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/2/21]
	author		:[S.Kawasaki]
******************************************************************************/
UBYTE	DA3(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_XDA3) {
		return(0);
	}
	return(1);
}

/******************************************************************************
	module		:[ＣＩの状態チェック]
	function	:[
		1.MRD9801のポート00C00300Ｈを読み込み
		2.XCUのビットが立っているかチェック
	]
	return		:[
		1:	XCIがLow(CI入力あり)
		0:	XCIがHigh(CI入力無し)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/2/21]
	author		:[S.Kawasaki]
******************************************************************************/
UBYTE	CI(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_XCI) {
		return(0);
	}
	return(1);
}


/******************************************************************************
	module		:[DSE1の出力値]
	function	:[
		1.SH7043のポート50Hを読み込み
		2.DSE1のビットが立っているかチェック
	]
	return		:[
		1:	DSE1がLow
		0:	DSE1がHigh
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[MS-C]
	keyword		:[CMN]
	date		:[1994/4/13]
	author		:[奥村明]
******************************************************************************/
UBYTE	DSE1(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_XDSE1_VC) {
		return(0);
	}
	return(1);
}

/******************************************************************************
	module		:[DSE2の出力値]
	function	:[
		1.SH7043のポート50Hを読み込み
		2.DSE2のビットが立っているかチェック
	]
	return		:[
		1:	DSE2がLow
		0:	DSE2がHigh
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[MS-C]
	keyword		:[CMN]
	date		:[1994/4/13]
	author		:[奥村明]
******************************************************************************/
UBYTE	DSE2(void)
{

/*
** ＜直流ループができていないとき＞
** ＤＳＥ１だけで極反を検出しようとしていたが、ＤＳＥ１だけでは
** Ｌ１、Ｌ２の極性によって極反を検出できないことが判明
** ハードリワークによってＤＳＥ２も復活させる
** これによって、極性によらずＤＳＥ１、２によって極反検出できるようになった
** そのため、ＤＳＥ２（）を元に戻します
** 
** ダイヤイン待機においての極性反転検出（直流ループができていない状態）では、
** ＤＳＥ１とＤＳＥ２をＯＲでみます
** ＴＥＬ／ＦＡＸ待機においての極性反転検出（直流ループ状態）では、
** ＤＳＥ１とＤＳＥ２をＡＮＤでみます
** 1999/02/16 by T.Soneoka
*/

#if (0)
**#if (0)
**** 	/* ＨＩＮＯＫＩはＤＳＥ２は無い！（＝＞ＤＳＥ１の反転がＤＳＥ２）
**** 	** でも、上位との互換性を保つために、ここでは、ＤＳＥ１を反転してチェックします。
**** 	** by O.Kimoto 1999/02/15
**** 	*/
**** 	if (InputWORD(GA_PGBDR) & IO_BIT_XDSE2_LC) {
**** 		return(0);
**** 	}
**** 	return(1);
**#else
**	if (InputWORD(GA_PGBDR) & IO_BIT_XDSE1_VC) {
**		return(1);
**	}
**	return(0);
**#endif
/* #eles スペルミス、コンパイルエラーにならずにコードがはいらない by H.Hirao 1999/06/17 */
#else
	if (InputWORD(GA_PGBDR) & IO_BIT_XDSE2_LC) {
		return(0);
 	}
 	return(1);
#endif
}


/*************************************************************************
	module		:[ループ電流,電圧の状態出力値]
	function	:[
	]
	return		:[
		1:	電流、電圧あり
		0:	無し
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1994/03/07]
	author		:[奥村明]
*************************************************************************/
UBYTE	LCV_Status(void)
{
	UBYTE	vc;
	UBYTE	lc;

	if (IO__PEDR & IO_BIT_XDSE1_VC) {
		vc = 1;
	}
	else {
		vc = 0;
	}
	if (IO__PEDR & IO_BIT_XDSE2_LC) {
		lc = 1;
	}
	else {
		lc = 0;
	}
	if (vc ^ lc) {
		return(1);
	}
	return(0);
}


/*************************************************************************
	module		:[ＴＥＬ１のオンフック・オフフックの監視]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[坂本直史]
*************************************************************************/
UBYTE	OffHook1(void)
{
#if (PRO_NCU_TYPE == HINOKI_TYPE)
	if (InputWORD(GA_PGBDR) & IO_BIT_XOH1) {
		return(0);								/* TEL1 ON	HOOK */
	}
	return(1);									/* TEL1 OFF HOOK */
#else
	/* ＨＩＮＯＫＩのＴＷＮ用ＮＣＵは ＯＨ１とＯＨ２が存在するが、Ｌリレーが存在しないので
	** ＯＨをＯＲで監視する。by H.Hirao 1999/01/29
	*/
	if (InputWORD(GA_PGBDR) & IO_BIT_XOH1 && InputWORD(GA_PGBDR) & IO_BIT_XOH2) {
		return (0);
	}
	return(1);
#endif
}

/*************************************************************************
	module		:[ＴＥＬ２のオンフック・オフフックの監視]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[坂本直史]
*************************************************************************/
UBYTE	OffHook2(void)
{
#if (PRO_NCU_TYPE == HINOKI_TYPE)
	if (InputWORD(GA_PGBDR) & IO_BIT_XOH2) {
		return(0);								/* TEL2 ON	HOOK */
	}
	return(1);									/* TEL2 OFF HOOK */
#else
	return(0);
	/* dummy function by H.Hirao 1999/01/29 */
#endif
}

#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
/*************************************************************************
	module		:[警察オンフック・オフフックの監視]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[05/06/21]
	author		:[Smuratec 李]
*************************************************************************/
UBYTE	OffHook3(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_XOH_EX) {
		return(0);								/* 警察電話 ON	HOOK */
	}
	return(1);									/* 警察電話 OFF HOOK */
}
/*************************************************************************
	module		:[指令起動信号の監視]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[05/06/21]
	author		:[Smuratec 李]
*************************************************************************/
UBYTE	CheckShireiOn(void)
{
	if (InputWORD(GA_PGBDR) & IO_BIT_SHIREI) {
		return FALSE;							/* 指令起動信号	OFF */
	}
	else {
		return TRUE;							/* 指令起動信号	ON	 */
	}
}

#endif /* defined (KEISATSU) */
/*************************************************************************
	module		:[ＣＭＬリレー設定チェック]
	function	:[
		1.ＣＭＬリレーがＯＮ／ＯＦＦされているかチェックする。
	]
	return		:[	０：ＯＦＦ
					１：ＯＮ
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1995/12/27]
	author		:[坂本直史]
*************************************************************************/
UBYTE 	CML_RelaySetting(void)
{
	if (RelayPortStatus & IO_BIT_CML) {
		return(1);
	}
	return(0);
}

/*************************************************************************
	module		:[Sリレー設定チェック]
	function	:[
		1.SリレーがＯＮ／ＯＦＦされているかチェックする。
	]
	return		:[	０：ＯＦＦ
					１：ＯＮ
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1995/12/27]
	author		:[坂本直史]
*************************************************************************/
UBYTE 	S_RelaySetting(void)
{
	if (RelayPortStatus & IO_BIT_S) {
		return(1);
	}
	return(0);
}
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/24 */
/*************************************************************************
	module		:[Hリレー（ハンドセット）設定チェック]
	function	:[
		1.ＨリレーがＯＮ／ＯＦＦされているかチェックする。
	]
	return		:[	０：ＯＦＦ	（標準回線）
					１：ＯＮ	（拡張回線）
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[2005/06/17}
	author		:[Smuratec 李]
*************************************************************************/
UBYTE 	HDST_RelaySetting(void)
{
	if (RelayPortStatus & IO_BIT_H) {
		return(1);
	}
	return(0);
}

/*************************************************************************
	module		:[Ｌリレー（標準ライン）設定チェック]
	function	:[
		1.ＬリレーがＯＮ／ＯＦＦされているかチェックする。
	]
	return		:[	０：ＯＦＦ
					１：ＯＮ
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[2005/06/17}
	author		:[Smuratec 李]
*************************************************************************/
UBYTE 	H_RelaySetting(void)
{
	if (RelayPortStatus & IO_BIT_L) {
		return(1);
	}
	return(0);
}

/*************************************************************************
	module		:[K_Lリレー(拡張ライン)設定チェック]
	function	:[
		1.K_LリレーがＯＮ／ＯＦＦされているかチェックする。
	]
	return		:[	０：ＯＦＦ
					１：ＯＮ
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[2005/06/17}
	author		:[Smuratec 李]
*************************************************************************/
UBYTE 	L_RelaySetting(void)
{
	if (IO__PADRL & IO_BIT_K_L) {
		return(1);
	}
	return(0);
}
/*************************************************************************
	module		:[HDSTを回線から分離する]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/07/28]
	author		:[SMuratec 李]
*************************************************************************/
void HDST_Disable(void)
{
	RelayPortStatus |= IO_BIT_HDST_OFF;
	OutputWORD(GA_PGADR, RelayPortStatus);
}
/*************************************************************************
	module		:[HDSTを回線に接続する]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/07/28]
	author		:[SMuratec 李]
*************************************************************************/
void HDST_Enable(void)
{
	RelayPortStatus &= ~IO_BIT_HDST_OFF;
	OutputWORD(GA_PGADR, RelayPortStatus);
}
#else /* !defined (KEISATSU) */

/*************************************************************************
	module		:[Ｈリレー設定チェック]
	function	:[
		1.ＨリレーがＯＮ／ＯＦＦされているかチェックする。
	]
	return		:[	０：ＯＦＦ
					１：ＯＮ
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1995/12/27]
	author		:[坂本直史]
*************************************************************************/
UBYTE 	H_RelaySetting(void)
{
	if (RelayPortStatus & IO_BIT_H) {
		return(1);
	}
	return(0);
}

/*************************************************************************
	module		:[Ｌリレー設定チェック]
	function	:[
		1.ＬリレーがＯＮ／ＯＦＦされているかチェックする。
	]
	return		:[	０：ＯＦＦ
					１：ＯＮ
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1995/12/27]
	author		:[坂本直史]
*************************************************************************/
UBYTE 	L_RelaySetting(void)
{
#if (PRO_NCU_TYPE == HINOKI_TYPE)
	if (RelayPortStatus & IO_BIT_L) {
		return(1);
	}
	return(0);
#else
	/* dummy function by H.Hirao 1999/01/29 */
	return(1);
#endif
}
#endif /* defined (KEISATSU) */

/*************************************************************************
	module		:[DPリレー設定チェック]
	function	:[
		1.DPリレーがＯＮ／ＯＦＦされているかチェックする。
	]
	return		:[	０：ＯＦＦ
					１：ＯＮ
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1995/12/27]
	author		:[坂本直史]
*************************************************************************/
UBYTE 	DP_RelaySetting(void)
{
#if !defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/28 */
	if (RelayPortStatus & IO_BIT_DP) {
		return(1);
	}
	return(0);
#endif /* defined (KEISATSU) */
}

/*************************************************************************
	module		:[ＣＯＮＴ２４設定チェック]
	function	:[
		1.ＣＯＮＴ２４がＯＮ／ＯＦＦされているかチェックする。
	]
	return		:[	０：ＯＦＦ
					１：ＯＮ
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1997/02/13]
	author		:[橘正樹]
*************************************************************************/
UBYTE 	CONT24_Setting(void)
{
	if (RelayPortStatus & IO_BIT_CONT24) {
		return(1);
	}
	return(0);
}


/*------------------------------------------------------------------------
**	＜＜＜　出力(OutOut)　＞＞＞
*/

/*************************************************************************
	module		:[カッターモーター駆動（カッター）]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void Cutter1On(void)
{
#if (0) /* これより以下は同じように修正します 1998/09/24 by T.Soneoka */
**	IO__PADRH | IO_BIT_CUTTER1;
#else
	IO__PADRH |= IO_BIT_CUTTER1;
#endif
}


/*************************************************************************
	module		:[カッターモーター駆動（カッター）]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void Cutter1Off(void)
{
	IO__PADRH &= ~IO_BIT_CUTTER1;
}


/*************************************************************************
	module		:[カッターモーター駆動（＋２４Ｖ）]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void Cutter2On(void)
{
	IO__PADRH |= IO_BIT_CUTTER2;
}


/*************************************************************************
	module		:[カッターモーター駆動（＋２４Ｖ）]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void Cutter2Off(void)
{
	IO__PADRH &= ~IO_BIT_CUTTER2;
}

#if (PRO_ENERGY_SAVE == ENABLE)	/* 2001/11/22 T.Takagi */
/*************************************************************************
	module		:[カッターが動作中かどうか
	]
	function	:[
		1.
	]
	return		:[
		TRUE	:動作中
		FALSE	:動作中でない
	]
	common		:[]
	condition	:[]
	comment		:[カッターモーター、及びカッターモーター駆動のための
				  24Vが供給されているかどうかで判断します
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/11/22]
	author		:[高木智史  T.Takagi]
*************************************************************************/
UBYTE	CheckCutting(void)
{
	if(IO__PADRH & IO_BIT_CUTTER1) {
		return (TRUE);
	}
	else if(IO__PADRH & IO_BIT_CUTTER2) {
		return (TRUE);
	}
	else {
		return (FALSE);
	}
}
#endif

#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
/*************************************************************************
	module		:[テストランド2(未使用)]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	SetTestLand2_On(void)
{
	IO__PEDR |= IO_BIT_TL02;
}


/*************************************************************************
	module		:[テストランド2(未使用)]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	SetTestLand2_Off(void)
{
	IO__PEDR &= ~IO_BIT_TL02;
}
#else


/*************************************************************************
	module		:[（ＲＳ－２３２Ｃ）データチャンネル受信キャリア検出]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void DCD_On(void)
{
	IO__PEDR |= IO_BIT_RS_DCD;
}


/*************************************************************************
	module		:[（ＲＳ－２３２Ｃ）データチャンネル受信キャリア検出]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void DCD_Off(void)
{
	IO__PEDR &= ~IO_BIT_RS_DCD;
}
#endif


/*************************************************************************
	module		:[28.8KモデムリセットON]
	function	:[
		1.２８．８ｋモデムのリセット信号をＯＮにする。
		2.ＣＯＭポート用ＲＡＭのＤ０を0にセットする。
		3.ＣＯＭポート（５０Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		このビットは負論理です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	Reset288ModemOn(void)
{
	IO__PEDR &= ~IO_BIT_XRESM;
}


/*************************************************************************
	module		:[28.8KモデムリセットOFF]
	function	:[
		1.２８．８ｋモデムのリセット信号をＯＦＦにする。
		2.ＥＴＣポート用ＲＡＭのＤ０を０にクリアする。
		3.ＥＴＣポート（５０Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[使用方法などは要確認]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	Reset288ModemOff(void)
{
	IO__PEDR |= IO_BIT_XRESM;
}


/*************************************************************************
	module		:[モデムリクエストクリア]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[使用方法などは要確認]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	ClearModemRequestOn(void)
{
	IO__PEDR |= IO_BIT_RQCLR;
}


/*************************************************************************
	module		:[モデムリクエストクリア]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[使用方法などは要確認]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	ClearModemRequestOff(void)
{
	IO__PEDR &= ~IO_BIT_RQCLR;
}


/*************************************************************************
	module		:[スピーカミュートＯＮ]
	function	:[
		1.スピーカ出力をミュートする。（消音）
		２．ＥＴＣポート用ＲＡＭのＤ７に１をかく。
		３．ＥＴＣポート用ＲＡＭの値を５０Ｈに出力する。
	]
	return		:[]
	common		:[SYS_ETC_PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	SpeakerMuteOn(void)
{
	IO__PEDR |= IO_BIT_MUTE;
}

/*************************************************************************
	module		:[スピーカミュートOFF]
	function	:[
		1.スピーカミュートを解除する。（音が出る）
		２．ＥＴＣポート用ＲＡＭのＤ７に０をかく。
		３．ＥＴＣポート用ＲＡＭの値を５０Ｈに出力する。
	]
	return		:[]
	common		:[SYS_ETC_PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	SpeakerMuteOff(void)
{
	IO__PEDR &= ~IO_BIT_MUTE;
}


/*************************************************************************
	module		:[ブザー出力（ＯＮ）]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
		ＨＩＮＯＫＩは、このビットをＯＮすることで、ＣＰＵからＰＷＭＣＫが出力される。
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	BuzzerOn(void)
{
#if (0)
** 	/* ワンショットタイマーとぶつかっていますので、ブザー用タイマーチャンネルを
** 	** 変更します。 
** 	** 変更先は未定ですので、当面ブザー無しです。
** 	**By O.Kimoto 1998/10/06
** 	*/
** 	IO__PEDR |= IO_BIT_BUZZ;
#endif
	IO__PEDR |= IO_BIT_BUZZ; /* 復活 1998/10/07 */

}


/*************************************************************************
	module		:[ブザー出力（ＯＦＦ）]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
		ＨＩＮＯＫＩは、このビットをＯＮすることで、ＣＰＵからＰＷＭＣＫが出力される。
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	BuzzerOff(void)
{

#if (0)
** 	/* ワンショットタイマーとぶつかっていますので、ブザー用タイマーチャンネルを
** 	** 変更します。 
** 	** 変更先は未定ですので、当面ブザー無しです。
** 	**By O.Kimoto 1998/10/06
** 	*/
** 	IO__PEDR &= ~IO_BIT_BUZZ;
#endif
	IO__PEDR &= ~IO_BIT_BUZZ; /* 復活 1998/10/07 */
}


/*************************************************************************
	module		:[ＬＣＤドライバーレジスター]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	LcdDriverRegisterData(void)
{
	IO__PEDR |= IO_BIT_LRS;
}


/*************************************************************************
	module		:[ＬＣＤドライバーレジスター]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	LcdDriverRegisterIR(void)
{
	IO__PEDR &= ~IO_BIT_LRS;
}


/*************************************************************************
	module		:[ＬＥＤポートチップセレクト１]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	LedPortSelect1On(void)
{
	IO__PEDR |= IO_BIT_LEWR1;
}


/*************************************************************************
	module		:[ＬＥＤポートチップセレクト１]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	LedPortSelect1Off(void)
{
	IO__PEDR &= ~IO_BIT_LEWR1;
}


/*************************************************************************
	module		:[ＬＥＤポートチップセレクト２]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	LedPortSelect2On(void)
{
	IO__PEDR |= IO_BIT_LEWR2;
}


/*************************************************************************
	module		:[ＬＥＤポートチップセレクト２]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	LedPortSelect2Off(void)
{
	IO__PEDR &= ~IO_BIT_LEWR2;
}


/*************************************************************************
	module		:[パネルデータ出力]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	PanelDataLoadOn(void)
{
	IO__PEDR |= IO_BIT_PROAD;
}


/*************************************************************************
	module		:[パネルデータ出力]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	PanelDataLoadOff(void)
{
	IO__PEDR &= ~IO_BIT_PROAD;
}


/*************************************************************************
	module		:[ＬＥＤポートチップセレクト２]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[
		このポートは、「フック／会話予約」のＬＥＤ直結です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	LedPortSelect3On(void)
{
	IO__PEDR |= IO_BIT_LEWR3;
}


/*************************************************************************
	module		:[ＬＥＤポートチップセレクト２]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[
		このポートは、「フック／会話予約」のＬＥＤ直結です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	LedPortSelect3Off(void)
{
	IO__PEDR &= ~IO_BIT_LEWR3;
}


/*************************************************************************
	module		:[ＬＣＤドライバーＥクロック]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[
		このポートは、「フック／会話予約」のＬＥＤ直結です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	LcdDriverClockOn(void)
{
	IO__PEDR |= IO_BIT_LE;
}


/*************************************************************************
	module		:[ＬＣＤドライバーＥクロック]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[
	]
	comment		:[
		このポートは、「フック／会話予約」のＬＥＤ直結です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	LcdDriverClockOff(void)
{
	IO__PEDR &= ~IO_BIT_LE;
}


/*************************************************************************
	module		:[ＲＴＣデータ書き込み］
	function	:[
		1.ＲＴＣに１を書き込む
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	RTC_DataWrite_1(void)
{
	IO__PEDR |= IO_BIT_RTCDT;
}

/*************************************************************************
	module		:[ＲＴＣデータ書き込み]
	function	:[
		1.ＲＴＣに０を書き込む
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	RTC_DataWrite_0(void)
{
	IO__PEDR &= ~IO_BIT_RTCDT;
}


/*************************************************************************
	module		:[ＲＴＣチップイネーブル]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	RTC_ChipEnable(void)
{
	IO__PEDR |= IO_BIT_RTCCE;
}

/*************************************************************************
	module		:[ＲＴＣチップディスエーブル]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	RTC_ChipDisable(void)
{
	IO__PEDR &= ~IO_BIT_RTCCE;
}


/*************************************************************************
	module		:[ＲＴＣ書き込みセット]
	function	:[
		1.ＲＴＣデータ書き込みを許可する。
		2.ＲＴＣデータ読み込みを禁止する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	RTC_DataWriteSet(void)
{
#if (PRO_RTC_RX5C338A == ENABLE)
#else
	IO__PEDR |= IO_BIT_RTCIO;
#endif
}

/*************************************************************************
	module		:[ＲＴＣ読み出しセット]
	function	:[
		1.ＲＴＣデータ読み込みを許可する。
		2.ＲＴＣデータ書き込みを禁止する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	RTC_DataReadSet(void)
{
#if (PRO_RTC_RX5C338A == ENABLE)
#else
	IO__PEDR &= ~IO_BIT_RTCIO;
#endif
}


/*************************************************************************
	module		:[ＲＴＣクロック・アップ]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	RTC_ClockUp(void)
{
	IO__PEDR |= IO_BIT_RTCCK;
}

/*************************************************************************
	module		:[ＲＴＣクロック・ダウン]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	RTC_ClockDown(void)
{
	IO__PEDR &= ~IO_BIT_RTCCK;
}


#if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
/*************************************************************************
	module		:[テストランド1(未使用)]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	SetTestLand1_On(void)
{
	IO__PEDR |= IO_BIT_TL01;
}


/*************************************************************************
	module		:[テストランド1(未使用)]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/10]
	author		:[岸田二郎]
*************************************************************************/
void	SetTestLand1_Off(void)
{
	IO__PEDR &= ~IO_BIT_TL01;
}
#else


/*************************************************************************
	module		:[（ＲＳ－２３２Ｃ）データセットレディ]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	DSR_On(void)
{
	IO__PEDR |= IO_BIT_RS_DSR;
}


/*************************************************************************
	module		:[（ＲＳ－２３２Ｃ）データセットレディ]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	DSR_Off(void)
{
	IO__PEDR &= ~IO_BIT_RS_DSR;
}
#endif


/*************************************************************************
	module		:[ＣＭＬリレーを引く]
	function	:[
		1.ＭＯＤＥＭ１ポート用ＲＡＭのＤ２を１にセットする。
		2.ＭＯＤＥＭ１ポート（０６０７Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/09]
	author		:[木元　修]
*************************************************************************/
void	CML_RelayOn(void)
{
	RelayPortStatus |= IO_BIT_CML;
	OutputWORD(GA_PGADR, RelayPortStatus);
#if (0) /* defined (TWN)  deleted by H.Hirao 1999/02/03 */
	DP_RelayOn();	/* added by H.Hirao 1999/01/20 */
#endif
}

/*************************************************************************
	module		:[ＣＭＬリレーを放す]
	function	:[
		1.ＭＯＤＥＭ１ポート用ＲＡＭのＤ２を０にセットする。
		2.ＭＯＤＥＭ１ポート（０６００Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/09]
	author		:[木元　修]
*************************************************************************/
void	CML_RelayOff(void)
{
	RelayPortStatus &= ~IO_BIT_CML;
	OutputWORD(GA_PGADR, RelayPortStatus);
#if (0) /* defined (TWN) deleted by H.Hirao 1999/02/03 */
	DP_RelayOff();	/* added by H.Hirao 1999/01/20 */
#endif
}


/*************************************************************************
	module		:[Ｓリレーを引く]
	function	:[
		1.ＭＯＤＥＭ１ポート用ＲＡＭのＤ５を１にセットする。
		2.ＭＯＤＥＭ１ポート（０６０７Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/09]
	author		:[木元　修]
*************************************************************************/
void	S_RelayOn(void)
{
	RelayPortStatus |= IO_BIT_S;
	OutputWORD(GA_PGADR, RelayPortStatus);
}

/*************************************************************************
	module		:[Ｓリレーを放す]
	function	:[
		1.ＭＯＤＥＭ１ポート用ＲＡＭのＤ５を０にセットする。
		2.ＭＯＤＥＭ１ポート（０６０７Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/09]
	author		:[木元　修]
*************************************************************************/
void	S_RelayOff(void)
{
	RelayPortStatus &= ~IO_BIT_S;
	OutputWORD(GA_PGADR, RelayPortStatus);
}


#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/24 */
/*************************************************************************
	module		:[Hリレー(ハンドセット)を拡張回線に接続する]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[NCU_INT.Cでポートをじか書きしているところあり。
				  ポートを変更するときは気を付けること。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/6/17]
	author		:[Smuratec 李]
*************************************************************************/
void	HDST_RelayOn(void)
{
	RelayPortStatus |= IO_BIT_H;
	OutputWORD(GA_PGADR, RelayPortStatus);
	/* 秘話機能追加 */
	if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) == EXT_USED_IN_EXT) { 
		/* 拡張回線外付電話使用中 */
		HDST_Disable(); /* ハンドセットを使用禁止にします */
	}
	else if (L_RelaySetting()) { /*  拡張回線外付電話を擬似ﾍﾞﾙ側に接続されている場合 */
		HDST_Disable();
	}
	else {	/*  拡張回線外付電話を回線側に接続されている場合 */
		HDST_Enable(); /* ハンドセットを使用可能にします */
	}
}

/*************************************************************************
	module		:[Hリレー(ハンドセット)を標準回線に接続する]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/6/17]
	author		:[Smuratec 李]
*************************************************************************/
void	HDST_RelayOff(void)
{
	RelayPortStatus &= ~IO_BIT_H;
	OutputWORD(GA_PGADR, RelayPortStatus);
	/* 秘話機能追加 */
	if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) == STD_USED_IN_EXT) { 
		/* 標準回線外付電話使用中 */
		HDST_Disable(); /* ハンドセットを使用禁止にします */
	}
	else if (H_RelaySetting()) { /*  標準回線外付電話を擬似ﾍﾞﾙ側に接続されている場合 */
		HDST_Disable();
	}
	else {	/*  標準回線外付電話を回線側に接続されている場合 */
		HDST_Enable();	/* ハンドセットを使用可能にします */
	}
}

/*************************************************************************
	module		:[Lリレー(標準回線)を引く]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[NCU_INT.Cでポートをじか書きしているところあり。
				  ポートを変更するときは気を付けること。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/6/17]
	author		:[Smuratec 李]
*************************************************************************/
void	H_RelayOn(void)
{
	if (!HDST_RelaySetting()) { /* ハンドセットを標準回線に接続 */
		HDST_Disable(); /* ハンドセットを使用禁止にします */
	}
	RelayPortStatus |= IO_BIT_L;
	OutputWORD(GA_PGADR, RelayPortStatus);
}

/*************************************************************************
	module		:[Lリレー(標準回線)を放す]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/6/17]
	author		:[Smuratec 李]
*************************************************************************/
void	H_RelayOff(void)
{
	/* 秘話機能追加 */
	if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) == STD_USED_IN_HDST) {  /* ハンドセット使用中 */
		HDST_Enable(); /* ハンドセットを使用可能にします */
		RelayPortStatus |= IO_BIT_L; /* 外付電話を回線から分離にします */
		OutputWORD(GA_PGADR, RelayPortStatus);
		return;
	}
	else if (!HDST_RelaySetting()) { /* ハンドセットを標準回線に接続 */
		if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) == STD_USED_IN_EXT) {  /* 外付電話使用中 */
			RelayPortStatus &= ~IO_BIT_L; /* 外付電話を回線に接続し */
			OutputWORD(GA_PGADR, RelayPortStatus);
			HDST_Disable();	/* ハンドセットを使用禁止にします */
			return;
		}
		else { /* 秘話機能起動しない場合 */
			HDST_Enable();	/* ハンドセットを使用可能にします */
		}
	}
	RelayPortStatus &= ~IO_BIT_L;
	OutputWORD(GA_PGADR, RelayPortStatus);
}


/*************************************************************************
	module		:[K_Ｌリレーを引く]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/6/17]
	author		:[Smuratec 李]
*************************************************************************/
void	L_RelayOn(void)
{
	if (HDST_RelaySetting()) { /* ハンドセットを拡張回線に接続 */
		HDST_Disable(); /* ハンドセットを使用禁止にします */
	}
	IO__PADRL |= IO_BIT_K_L;
}

/*************************************************************************
	module		:[K_Ｌリレーを放す]
	function	:[
		1.ＭＯＤＥＭ１ポート用ＲＡＭのＤ４を０にセットする。
		2.ＭＯＤＥＭ１ポート（０６０７Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2005/6/17]
	author		:[Smuratec 李]
*************************************************************************/
void	L_RelayOff(void)
{
	/* 秘話機能追加 */
	if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) == EXT_USED_IN_HDST) {  /* ハンドセット使用中 */
		HDST_Enable(); /* ハンドセットを使用可能にします */ 
		IO__PADRL |= IO_BIT_K_L;  /* 外付電話を回線から分離にします */
		return;
	}
	else if (HDST_RelaySetting()) { /* ハンドセットを拡張回線に接続 */
		if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) == EXT_USED_IN_EXT) {  /* 外付電話使用中 */
			IO__PADRL &= ~IO_BIT_K_L; /* 外付電話を回線に接続し */
			HDST_Disable();	/* ハンドセットを使用禁止にします */
			return;
		}
		else { /* 秘話機能起動しない場合 */
			HDST_Enable(); /* ハンドセットを使用可能にします */ 
		}
	}
	IO__PADRL &= ~IO_BIT_K_L;
}

#else /* !defined (KEISATSU) */
/*************************************************************************
	module		:[Ｈリレーを引く]
	function	:[
		1.ＭＯＤＥＭ１ポート用ＲＡＭのＤ３を１にセットする。
		2.ＭＯＤＥＭ１ポート（０６０７Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[NCU_INT.Cでポートをじか書きしているところあり。
				  ポートを変更するときは気を付けること。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/11/16]
	author		:[坂本直史]
*************************************************************************/
void	H_RelayOn(void)
{
	RelayPortStatus |= IO_BIT_H;
	OutputWORD(GA_PGADR, RelayPortStatus);
}

/*************************************************************************
	module		:[Ｈリレーを放す]
	function	:[
		1.ＭＯＤＥＭ１ポート用ＲＡＭのＤ３を０にセットする。
		2.ＭＯＤＥＭ１ポート（０６０７Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/11/16]
	author		:[坂本直史]
*************************************************************************/
void	H_RelayOff(void)
{
	RelayPortStatus &= ~IO_BIT_H;
	OutputWORD(GA_PGADR, RelayPortStatus);
}


/*************************************************************************
	module		:[Ｌリレーを引く]
	function	:[
		1.ＭＯＤＥＭ１ポート用ＲＡＭのＤ４を１にセットする。
		2.ＭＯＤＥＭ１ポート（０６０７Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/09]
	author		:[木元　修]
*************************************************************************/
void	L_RelayOn(void)
{
#if (PRO_NCU_TYPE == HINOKI_TYPE)
	RelayPortStatus |= IO_BIT_L;
	OutputWORD(GA_PGADR, RelayPortStatus);
#else
	/* dummy function by H.Hirao 1999/01/29 */
#endif
}

/*************************************************************************
	module		:[Ｌリレーを放す]
	function	:[
		1.ＭＯＤＥＭ１ポート用ＲＡＭのＤ４を０にセットする。
		2.ＭＯＤＥＭ１ポート（０６０７Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/11/16]
	author		:[坂本直史]
*************************************************************************/
void	L_RelayOff(void)
{
#if (PRO_NCU_TYPE == HINOKI_TYPE)
	RelayPortStatus &= ~IO_BIT_L;
	OutputWORD(GA_PGADR, RelayPortStatus);
#else
	/* dummy function by H.Hirao 1999/01/29 */
#endif
}
#endif /* defined (KEISATSU) */

/*************************************************************************
	module		:[ＮＣＵリンガーコントロール　ＯＮ]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[坂本直史]
*************************************************************************/
void	RI_On(void)
{
#if defined(JPN)
	RelayPortStatus &= ~IO_BIT_RI_GK;
	OutputWORD(GA_PGADR, RelayPortStatus);
#endif
}

/*************************************************************************
	module		:[ＮＣＵリンガーコントロール　ＯＦＦ]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[坂本直史]
*************************************************************************/
void	RI_Off(void)
{
#if defined(JPN) || defined(SEA) || defined(TUR)
	RelayPortStatus |= IO_BIT_RI_GK;
	OutputWORD(GA_PGADR, RelayPortStatus);
#endif
}


/*************************************************************************
	module		:[]
	function	:[
	]
	return		:[
		1:
	]
	common		:[]
	condition	:[]
	comment		:[ドイツ仕様]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1994/03/18]
	author		:[奥村明][原田 '98/04/06]
*************************************************************************/
void	GroundKeyOn(void)
{
	RelayPortStatus &= ~IO_BIT_RI_GK;
	OutputWORD(GA_PGADR, RelayPortStatus);
}

/*************************************************************************
	module		:[]
	function	:[
	]
	return		:[
		1:
	]
	common		:[]
	condition	:[]
	comment		:[ドイツ仕様]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1994/03/18]
	author		:[奥村明][原田 '98/04/06]
*************************************************************************/
void	GroundKeyOff(void)
{
	RelayPortStatus |= IO_BIT_RI_GK;
	OutputWORD(GA_PGADR, RelayPortStatus);
}


/*************************************************************************
	module		:[ＤＰリレーを引く]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[坂本直史]
*************************************************************************/
void	DP_RelayOn(void)
{
#if !defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/28 */
	RelayPortStatus |= IO_BIT_DP;
	OutputWORD(GA_PGADR, RelayPortStatus);
#endif /* defined (KEISATSU) */
}

/*************************************************************************
	module		:[ＤＰリレーを放す]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[坂本直史]
*************************************************************************/
void	DP_RelayOff(void)
{
#if !defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/28 */
	RelayPortStatus &= ~IO_BIT_DP;
	OutputWORD(GA_PGADR, RelayPortStatus);
#endif /* defined (KEISATSU) */
}

/*************************************************************************
	module		:[停電時ダイヤルインＣＰＵへＮＤ設定ＯＮを通知する]
	function	:[
		ナンバーディスプレイ設定がＯＮであることをダイヤルインＣＰＵへ
		通知し、停電時にダイヤルインＣＰＵが着信動作しないようにする。
	]
	return		:[なし]
	common		:[
		UWORD RelayPortStatus
	]
	condition	:[]
	comment		:[
		停電時ダイヤルインＣＰＵの新規設計に伴う追加処理です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/12/21]
	author		:[野瀬敏弘]
*************************************************************************/
#if (PRO_DIALIN == ENABLE) && (PRO_NCU_TYPE == HINOKI_TYPE)
void SetDICPU_Disable(void)
{
	RelayPortStatus &= ~IO_BIT_ND_DATA;
	OutputWORD(GA_PGADR, RelayPortStatus);
}
#endif

/*************************************************************************
	module		:[停電時ダイヤルインＣＰＵへＮＤ設定ＯＦＦを通知する]
	function	:[
		ナンバーディスプレイ設定がＯＦＦであることをダイヤルインＣＰＵへ
		通知し、停電時にダイヤルインＣＰＵが着信動作することを許可する。
	]
	return		:[なし]
	common		:[
		UWORD RelayPortStatus
	]
	condition	:[]
	comment		:[
		停電時ダイヤルインＣＰＵの新規設計に伴う追加処理です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/12/21]
	author		:[野瀬敏弘]
*************************************************************************/
#if (PRO_DIALIN == ENABLE) && (PRO_NCU_TYPE == HINOKI_TYPE)
void SetDICPU_Enable(void)
{
	RelayPortStatus |= IO_BIT_ND_DATA;
	OutputWORD(GA_PGADR, RelayPortStatus);
}
#endif

#if (0)
@@ 停電時ダイヤルインの新規設計に伴い、このポートはダイヤルインＣＰＵ
@@ へＮＤ設定を通知するポートとして使用します。
@@ T.Nose 1998/12/21
@@/*************************************************************************
@@	module		:[ＳＯＨリレーを引く]
@@	function	:[
@@	]
@@	return		:[なし]
@@	common		:[なし]
@@	condition	:[]
@@	comment		:[]
@@	machine		:[SH7043]
@@	language	:[SHC]
@@	keyword		:[CMN]
@@	date		:[1994/04/01]
@@	author		:[坂本直史]
@@*************************************************************************/
@@void	SOH_RelayOn(void)
@@{
@@	RelayPortStatus |= IO_BIT_SOH_TCK;
@@	OutputWORD(GA_PGADR, RelayPortStatus);
@@}
#endif

#if (0)
@@ 停電時ダイヤルインの新規設計に伴い、このポートはダイヤルインＣＰＵ
@@ へＮＤ設定を通知するポートとして使用します。
@@ T.Nose 1998/12/21
@@/*************************************************************************
@@	module		:[ＤＰリレーを放す]
@@	function	:[
@@	]
@@	return		:[なし]
@@	common		:[なし]
@@	condition	:[]
@@	comment		:[]
@@	machine		:[SH7043]
@@	language	:[SHC]
@@	keyword		:[CMN]
@@	date		:[1994/04/01]
@@	author		:[坂本直史]
@@*************************************************************************/
@@void	SOH_RelayOff(void)
@@{
@@	RelayPortStatus &= ~IO_BIT_SOH_TCK;
@@	OutputWORD(GA_PGADR, RelayPortStatus);
@@}
#endif

/*************************************************************************
	module		:[ＡＦＥ入力切り替えＲＸＡ設定]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[曽根岡拓]
*************************************************************************/
void	AnalogSwitchRXA_Set(void)
{
	RelayPortStatus |= IO_BIT_RXA_TONE;
	OutputWORD(GA_PGADR, RelayPortStatus);
}

/*************************************************************************
	module		:[ＡＦＥ入力切り替えＴＯＮＥ設定]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[曽根岡拓]
*************************************************************************/
void	AnalogSwitchTONE_Set(void)
{
#if defined(JPN)
	RelayPortStatus &= ~IO_BIT_RXA_TONE;
	OutputWORD(GA_PGADR, RelayPortStatus);
#else /* For TWN */
	/* Nothing */ /* by H.Hirao 1999/01/06 */
#endif
}

#if defined(TWN)
void	AnalogSwitchTONE_Set2(void)
{
	RelayPortStatus &= ~IO_BIT_RXA_TONE;
	OutputWORD(GA_PGADR, RelayPortStatus);
}
#endif

/*************************************************************************
	module		:[スピーカー出力切り替え(RXA)]
	function	:[
		1.スピーカー出力をＲＸＡに切り替える。
	]
	return		:[]
	common		:[SYS_Modem2PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	SpeakerOutRXA(void)
{
	RelayPortStatus |= IO_BIT_RXA_BZ;
	OutputWORD(GA_PGADR, RelayPortStatus);
	BuzzerOff();	/* ブザークロックを止める */
}

/*************************************************************************
	module		:[スピーカー出力切り替え(BUZZER)]
	function	:[
		1.スピーカー出力をブザー側に切り替える
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[デフォルトはブザー側にしておくこと。]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	SpeakerOutBuzzer(void)
{
	RelayPortStatus &= ~IO_BIT_RXA_BZ;
	OutputWORD(GA_PGADR, RelayPortStatus);
	BuzzerOn();	/* ブザークロックを出す */
}


/*************************************************************************
	module		:[ランプＯＮ]
	function	:[
		1.ＭＯＤＥＭ２ポート用ＲＡＭのＤ４を１にセットする。
		2.ＭＯＤＥＭ２ポート（６０Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/09]
	author		:[木元　修]
*************************************************************************/
void	LampOn(void)
{
	RelayPortStatus |= IO_BIT_LAMP;
	OutputWORD(GA_PGADR, RelayPortStatus);
}

/*************************************************************************
	module		:[ランプＯＦＦ]
	function	:[
		1.ＭＯＤＥＭ２ポート用ＲＡＭのＤ４を０にセットする。
		2.ＭＯＤＥＭ２ポート（６０Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/09]
	author		:[木元　修]
*************************************************************************/
void	LampOff(void)
{

	RelayPortStatus &= ~IO_BIT_LAMP;
	OutputWORD(GA_PGADR, RelayPortStatus);
}

#if (PRO_ENERGY_SAVE == ENABLE)	/* 2001/12/03 T.Takagi */
/*************************************************************************
	module		:[ランプ点灯中かどうか]
	function	:[
	]
	return		:[
				TRUE:点灯中
				FALSE:消灯中
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/12/3]
	author		:[高木智史  T.Takagi]
*************************************************************************/
UBYTE	CheckLamp(void)
{
	if (RelayPortStatus & IO_BIT_LAMP) {
		return (TRUE);
	}
	else {
		return (FALSE);
	}
}
#endif
/*************************************************************************
	module		:[クラッチＯＮ]
	function	:[
		1.ＭＯＤＥＭ２ポート用ＲＡＭのＤ４を１にセットする。
		2.ＭＯＤＥＭ２ポート（６０Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/09]
	author		:[木元　修]
*************************************************************************/
void	CluchOn(void)
{
	RelayPortStatus |= IO_BIT_CLUTCH;
	OutputWORD(GA_PGADR, RelayPortStatus);
}


/*************************************************************************
	module		:[クラッチの状態をチェックします]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/10/16]
	author		:[T.Soneoka]
*************************************************************************/
BOOL	CluchSetting(void)
{
	if (RelayPortStatus & IO_BIT_CLUTCH) {
		return (1);
	}
	return (0);
}


/*************************************************************************
	module		:[クラッチＯＦＦ]
	function	:[
		1.ＭＯＤＥＭ２ポート用ＲＡＭのＤ４を０にセットする。
		2.ＭＯＤＥＭ２ポート（６０Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/09]
	author		:[木元　修]
*************************************************************************/
void	CluchOff(void)
{
	RelayPortStatus &= ~IO_BIT_CLUTCH;
	OutputWORD(GA_PGADR, RelayPortStatus);
}


/*************************************************************************
	module		:[ＣＯＮＴ　２４Ｖ　ＯＮ]
	function	:[疑似回線電圧をＯＦＦする
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[坂本直史]
*************************************************************************/
void	CONT_24V_On(void)
{
#if defined(JPN)
	RI_Off();/* 疑似回線電圧をＯＦＦする */
#endif
	RelayPortStatus |= IO_BIT_CONT24;
	OutputWORD(GA_PGADR, RelayPortStatus);
}

/*************************************************************************
	module		:[ＣＯＮＴ　２４Ｖ　ＯＦＦ]
	function	:[疑似回線電圧を24V掛ける
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[坂本直史]
*************************************************************************/
void	CONT_24V_Off(void)
{
#if defined(JPN)
	RI_Off();
#endif
	RelayPortStatus &= ~IO_BIT_CONT24;
	OutputWORD(GA_PGADR, RelayPortStatus);
}


/*************************************************************************
	module		:[パワーコントロール２４Ｖ　ＯＮ]
	function	:[
		1.ＥＴＣポート用ＲＡＭのＤ０を１にセットする。
		2.ＥＴＣポート（５０Ｈ）に出力する。
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/03/07]
	author		:[木元　修]
*************************************************************************/
void PC_24V_On(void)
{
 	RelayPortStatus |= IO_BIT_PC;
 	OutputWORD(GA_PGADR, RelayPortStatus);
}


/*************************************************************************
	module		:[パワーコントロール２４Ｖ　ＯＦＦ]
	function	:[
		1.ＥＴＣポート用ＲＡＭのＤ０を０にセットする。
		2.ＥＴＣポート（５０Ｈ）に出力する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[HINOKI2で使用  2001/11/17 T.Takagi]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/03/07]
	author		:[木元　修]
*************************************************************************/
void PC_24V_Off(void)
{
 	RelayPortStatus &= ~IO_BIT_PC;
 	OutputWORD(GA_PGADR, RelayPortStatus);
}


/******************************************************************************
	module		:[スタンプを押す]
	function	:[]
	return		:[]
	common		:[以下の条件が同時に成立すればスタンプを押す
					・スタンプ設定がＯＮ
					・スキャナー・カバーが閉じている
				]
	machine		:[SH7043]
	language	:[MS-C]
	keyword		:[CMN]
	date		:[1994/5/25]
	author		:[S.Kawasaki]
******************************************************************************/
void	CMN_PushStamp(void)
{
	if ((SYS_StampFlag == 1) &&									/** スタンプの設定がＯＮ */
		!(TXIL())) {											/** スキャナー・カバーが閉じている */
#if (0) /* 1998/11/18 by T.Soneoka */
**		OutputWORD(GA_PGADR, (UWORD)(RelayPortStatus | IO_BIT_STAMP));
#else
		RelayPortStatus |= IO_BIT_STAMP;
		OutputWORD(GA_PGADR, RelayPortStatus);
#endif

#if (0)
** 		/* 済みスタンプを押さないときがある。
** 		** ＳＡＫＡＫＩはＯＮしてから１５０ｍｓ待っているので、
** 		** ＨＩＮＯＫＩもあわせる。
** 		** by O.Kimoto 1999/03/29
** 		*/
** 		wai_tsk(10);														/** 100msec wait */
#else
		wai_tsk(15);														/** 100msec wait */
#endif

#if (0) /* 1998/11/18 by T.Soneoka */
**		OutputWORD(GA_PGADR, (UWORD)(RelayPortStatus & ~IO_BIT_STAMP));
#else
		RelayPortStatus &= ~IO_BIT_STAMP;
		OutputWORD(GA_PGADR, RelayPortStatus);
#endif
	}
}


#if(PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* Added by H.Kubo 1997/10/13 */
/*************************************************************************
	module		:[保留メロディ／モデム送信切り替えメロディ選択]
	function	:[
		1.ポートをＯＦＦする (Melody)
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
			外付けの保留音発生器の出力とモデム送信出力のどちらを回線に
			出力するか切り替える。保留音を選択。
	]
	machine		:[SH]
	language	:[SHC]
	keyword		:[CMN]
	ProtoType	:[void StartSendingMelodyToLine(void){}]
	date		:[1997/10/13]
	author		:[久保博]
*************************************************************************/
void StartSendingMelodyToLine(void)
{
 #if defined (JPN)
	RelayPortStatus |= IO_BIT_SELMEL;
	OutputWORD(GA_PGADR, RelayPortStatus);
 #endif
}

/*************************************************************************
	module		:[保留メロディ／モデム送信切り替えモデム送信選択]
	function	:[
		1.ポートをＯＮする (Modem Tx)
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
			外付けの保留音発生器の出力とモデム送信出力のどちらを回線に
			出力するか切り替える。モデム送信を選択。
	]
	machine		:[SH]
	language	:[SHC]
	keyword		:[CMN]
	ProtoType	:[void StopSendingMelodyToLine(void){}]
	date		:[1997/10/13]
	author		:[久保博]
*************************************************************************/
void StopSendingMelodyToLine(void)
{
	RelayPortStatus &= ~IO_BIT_SELMEL;
	OutputWORD(GA_PGADR, RelayPortStatus);
}
#endif /* (PRO_MODEM == R288F)  */

#if (PRO_ENERGY_SAVE == ENABLE)	/* 2001/11/21 T.Takagi */
/*************************************************************************
	module		:[SUB RESETをOFFにする]
	function	:[
				LSI、通信CODECへのサブリセットを解除
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[待機中はサブリセットONでLSI,通信CODECへのクロックが停止
				している。RESETをOFFにしてクロックを供給する。
				この前にHCLKをONにしておく。
				]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/11/21]
	author		:[高木 智史]
*************************************************************************/
void SubResetOff(void)
{
	RelayPortStatus |= IO_BIT_SUBRESET;
	OutputWORD(GA_PGADR, RelayPortStatus);
}
/*************************************************************************
	module		:[SUB RESETをONにする]
	function	:[
				LSI,通信CODECへのサブリセットON
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/11/21]
	author		:[高木 智史]
*************************************************************************/
void SubResetOn(void)
{
	RelayPortStatus &= ~IO_BIT_SUBRESET;
	OutputWORD(GA_PGADR, RelayPortStatus);
}
#endif

/*------------------------------------------------------------------------
**	＜＜＜　ＬＥＤ関係(LED)　＞＞＞
*/
#if (0)
		CMN_DisableInterrupt();
		Led3Status &= LedOut;
		Led3BlinkStatus &= LedOut;
		PortEStatus |= IO_BIT_LED3;
		OutputWORD(IO_PEDR, PortEStatus);
		CMN_EnableInterrupt();
#endif

/*************************************************************************
	module		:[フック／会話予約ＬＥＤ点灯]
	function	:[
		1.
	]
	return		:[]
	common		:[
		SYS_LED1_PortStatus
		SYS_LED2_PortStatus
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void HookLedOn(void)
{
	CMN_DisableInterrupt();
#if defined(HINOKI3)
	SYS_LED2_PortStatus |= ON_HOOK_LED;
#else
	SYS_LED3_PortStatus |= ON_HOOK_LED;
	IO__PEDR &= ~IO_BIT_LEWR3;
#endif
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[フック／会話予約ＬＥＤ点灯]
	function	:[
		1.
	]
	return		:[]
	common		:[
		SYS_LED1_PortStatus
		SYS_LED2_PortStatus
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void HookLedOff(void)
{
	CMN_DisableInterrupt();
#if defined(HINOKI3)
	SYS_LED2_PortStatus &= ~ON_HOOK_LED;
#else
	SYS_LED3_PortStatus &= ~ON_HOOK_LED;
	IO__PEDR |= IO_BIT_LEWR3;
#endif
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[アラームＬＥＤ点灯]
	function	:[
		1.
	]
	return		:[]
	common		:[SYS_LCDC_PortStatus]
	condition	:[]
	comment		:[
		アラームＬＥＤだけ、LCDCのポートにあるので注意
		影響がないのか確認
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void AlarmLedOn(void)
{
	CMN_DisableInterrupt();
	SYS_LED2_PortStatus |= ALARM_LED;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[アラームＬＥＤ消灯]
	function	:[
		1.
	]
	return		:[]
	common		:[SYS_LED2_PortStatus]
	condition	:[]
	comment		:[アラームＬＥＤだけ、LCDCのポートにあるので注意]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void AlarmLedOff(void)
{
	CMN_DisableInterrupt();
	SYS_LED2_PortStatus &= ~ALARM_LED;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[通信中ＬＥＤ点灯]
	function	:[
		1.
	]
	return		:[]
	common		:[SYS_LED2_PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void FaxComLedOn(void)
{
	CMN_DisableInterrupt();
	SYS_LED2_PortStatus |= FAX_COM_LED;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[通信中ＬＥＤ消灯]
	function	:[
		1.
	]
	return		:[]
	common		:[SYS_LED2_PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void FaxComLedOff(void)
{
	CMN_DisableInterrupt();
	SYS_LED2_PortStatus &= ~FAX_COM_LED;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[画質ＬＥＤ点灯]
	function	:[
		1.
	]
	return		:[]
	common		:[
		SYB_ModeSw
		SYS_LED1_PortStatus
		SYS_LED2_PortStatus
	]
	condition	:[]
	comment		:[
		#if defined(ANZU_L) || defined (ANZU_V)
			点灯するLEDによってポートが異なるので注意
			,標準・高画質	：ポート１(LED1_PORT)
			,超高画質・写真	：ポート２(LED2_PORT)
		#endif

		#if defined(POPLAR_B) || defined(POPLAR_L)
			高画質・超高画質・写真	：ポート２(LED2_PORT)
		#endif
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void ModeLedOn(void)
{
	UBYTE	led1_status;

	/* 現在のモードにより、画質を得る */
	led1_status = (UBYTE)SYS_LED1_PortStatus;/**現在状態の取得(便宜のため論理反転)*/

	led1_status &= ~(MODE_NORMAL_LED | MODE_FINE_LED | MODE_SFINE_LED | MODE_GRAY_LED);/**モード表示LEDをリセット*/

	switch (SYB_ModeSw) {/**セットされたモードのLEDをセットする*/
	case SYS_NORMAL:		/** Normalの時 */
		led1_status |= MODE_NORMAL_LED;
		break;
	case SYS_FINE:			/** Fineの時 */
		led1_status |= MODE_FINE_LED;
		break;
	case SYS_SFINE:			/** SFineの時 */
		led1_status |= MODE_SFINE_LED;
		break;
	case SYS_HFINE:			/** Hfineの時 */
		led1_status |= MODE_SFINE_LED;
		break;
	case SYS_GRAY16:		/** 16の時 */
	case SYS_GRAY16_SEP:	/** 16_SEPの時 */
	case SYS_GRAY64:		/** 64の時 */
	case SYS_GRAY64_SEP:	/** 64_SEPの時 */
		led1_status |= MODE_GRAY_LED;
		break;
	default:
		break;
	}
	CMN_DisableInterrupt();
	SYS_LED1_PortStatus = (unsigned char)led1_status;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[原稿濃度ＬＥＤ点灯]
	function	:[
		1.
	]
	return		:[]
	common		:[
		SYB_DensitySw
		SYS_LED1_PortStatus
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void DensityLedOn(void)
{
	UBYTE led1_status;

	led1_status = (UBYTE)SYS_LED1_PortStatus;/**現在状態の取得(便宜のため論理反転)*/
	led1_status &= ~(DST_DARK_LED | DST_NORMAL_LED | DST_LIGHT_LED);
	switch (SYB_DensitySw) {/**セットされた濃度のLEDをセット*/
	case SYS_DARK_DENSITY:		/** こくの時 */
		led1_status |= DST_DARK_LED;
		break;
	case SYS_NORMAL_DENSITY:	/** ふつうの時 */
		led1_status |= DST_NORMAL_LED;
		break;
	case SYS_LIGHT_DENSITY:		/** うすくの時 */
		led1_status |= DST_LIGHT_LED;
		break;
	default:
		break;
	}
	CMN_DisableInterrupt();
	SYS_LED1_PortStatus = (UBYTE)led1_status;
	CMN_EnableInterrupt();
}


/*************************************************************************
	module		:[記録紙ＬＥＤ点灯]
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
	date		:[1995/03/01]
	author		:[江口]
*************************************************************************/
void ReplacePaperLedOn(void)
{
	/* とりあえず、AlarmLEDをつけときます。 */
	AlarmLedOn();
}

/*************************************************************************
	module		:[記録紙ＬＥＤ消灯]
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
	date		:[1995/03/01]
	author		:[江口]
*************************************************************************/
void ReplacePaperLedOff(void)
{
	/* とりあえず、AlarmLEDをつけときます。 */
	AlarmLedOff();
}

/*************************************************************************
	module		:[紙詰まりＬＥＤ点灯]
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
	date		:[1995/03/01]
	author		:[江口]
*************************************************************************/
void PaperJamLedOn(void)
{
	/* とりあえず、AlarmLEDをつけときます。 */
	AlarmLedOn();
}

/*************************************************************************
	module		:[紙詰まりＬＥＤ点灯]
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
	date		:[1995/03/01]
	author		:[江口]
*************************************************************************/
void PaperJamLedOff(void)
{
	/* とりあえず、AlarmLEDをつけときます。 */
	AlarmLedOff();
}

#if defined(KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/09/15 */
/*************************************************************************
	module		:[スタンプＬＥＤ点灯]
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
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
void ReservationLedOn(void)
{
	CMN_DisableInterrupt();
	SYS_LED1_PortStatus |= RESERVATION_LED;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[スタンプＬＥＤ消灯]
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
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
void ReservationLedOff(void)
{
	CMN_DisableInterrupt();
	SYS_LED1_PortStatus &= ~RESERVATION_LED;
	CMN_EnableInterrupt();
}
#endif		/* End of (defined (KEISATSU)) */

/*************************************************************************
	module		:[スタンプＬＥＤ点灯]
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
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
void StampLedOn(void)
{
#if !defined(KEISATSU)		/* 警察FAX Delete by SMuratec K.W.Q 2005/09/15 */
	CMN_DisableInterrupt();
	SYS_LED1_PortStatus |= STAMP_LED;
	CMN_EnableInterrupt();
#endif		/* End of (defined (KEISATSU)) */
}

/*************************************************************************
	module		:[スタンプＬＥＤ消灯]
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
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
void StampLedOff(void)
{
#if !defined(KEISATSU)		/* 警察FAX Delete by SMuratec K.W.Q 2005/09/15 */
	CMN_DisableInterrupt();
	SYS_LED1_PortStatus &= ~STAMP_LED;
	CMN_EnableInterrupt();
#endif		/* End of (defined (KEISATSU)) */
}

/*************************************************************************
	module		:[自動受信ＬＥＤ点灯]
	function	:[
		1.
	]
	return		:[]
	common		:[SYS_LED2_PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void AutoRxLedOn(void)
{
	CMN_DisableInterrupt();
	SYS_LED2_PortStatus |= AUTO_RX_LED;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[自動受信ＬＥＤ消灯]
	function	:[
		1.
	]
	return		:[]
	common		:[SYS_LED2_PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void AutoRxLedOff(void)
{
	CMN_DisableInterrupt();
	SYS_LED2_PortStatus &= ~AUTO_RX_LED;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[メモリ送信ＬＥＤ点灯]
	function	:[
		1.
	]
	return		:[]
	common		:[
		SYS_LED1_PortStatus
		SYS_LED2_PortStatus
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void MemoryTxLedOn(void)
{
	CMN_DisableInterrupt();
	SYS_LED2_PortStatus |= MEMORY_TX_LED;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[メモリ送信ＬＥＤ消灯]
	function	:[
		1.
	]
	return		:[]
	common		:[
		SYS_LED1_PortStatus
		SYS_LED2_PortStatus
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void MemoryTxLedOff(void)
{
	CMN_DisableInterrupt();
	SYS_LED2_PortStatus &= ~MEMORY_TX_LED;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[メモリ受信（代行受信）ＬＥＤ点灯]
	function	:[
		1.
	]
	return		:[]
	common		:[SYS_LED2_PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void MemoryRxLedOn(void)
{
	CMN_DisableInterrupt();
	SYS_LED2_PortStatus |= MEMORY_RX_LED;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[メモリ受信（代行受信）ＬＥＤ消灯]
	function	:[
		1.
	]
	return		:[]
	common		:[SYS_LED2_PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void MemoryRxLedOff(void)
{
	CMN_DisableInterrupt();
	SYS_LED2_PortStatus &= ~MEMORY_RX_LED;
	CMN_EnableInterrupt();
}


/*************************************************************************
	module		:[コピーモードＬＥＤ点灯]
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
	date		:[1997/02/21]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_COPY_FAX_MODE == ENABLE)
void CopyModeLedOn(void)
{
	SYS_LED1_PortStatus &= ~COPY_LED;
	SYS_LED1_PortStatus |= FAX_LED;
	outpw(LED1_PORT, (UWORD)SYS_LED1_PortStatus);
}
#endif

/*************************************************************************
	module		:[ファクスモードＬＥＤ点灯]
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
	date		:[1997/02/21]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_COPY_FAX_MODE == ENABLE)
void FaxModeLedOn(void)
{
	SYS_LED1_PortStatus &= ~FAX_LED;
	SYS_LED1_PortStatus |= COPY_LED;
	outpw(LED1_PORT, (UWORD)SYS_LED1_PortStatus);
}
#endif

/*************************************************************************
	module		:[全ＬＥＤ点灯処理]
	function	:[
		1.すべてのLEDを点灯
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[]
	author		:[江口,渡辺一章]
*************************************************************************/
void AllLedOn(void)
{
	CMN_DisableInterrupt();
	SYS_LED1_PortStatus = 0xff;
	SYS_LED2_PortStatus = 0xff;
	SYS_LED3_PortStatus = 0x01;
	IO__PEDR &= ~IO_BIT_LEWR3;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[全ＬＥＤ消灯処理]
	function	:[
		1.すべてのLEDを消灯
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[]
	author		:[江口,渡辺一章]
*************************************************************************/
void AllLedOff(void)
{
	CMN_DisableInterrupt();
	SYS_LED1_PortStatus = 0x00;
	SYS_LED2_PortStatus = 0x00;
	SYS_LED3_PortStatus = 0x00;
	IO__PEDR |= IO_BIT_LEWR3;
	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[ＬＥＤ順次点灯]
	function	:[
		1. 全ＬＥＤ消灯
		2. 指定ＬＥＤをセット
		3. 指定ＬＥＤを点灯
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1997/06/05]
	author		:[桑原美紀]
*************************************************************************/
void 		OrderLedOn(
				UBYTE	Port,			/* ポート */
				UWORD	LedType )		/* 点灯データ */
{
	AllLedOff();		/* 全ＬＥＤ消灯 */

	switch( Port ){
	case	1:
		CMN_DisableInterrupt();
		SYS_LED1_PortStatus |= LedType;
		CMN_EnableInterrupt();
		break;
	case	2:
		CMN_DisableInterrupt();
		SYS_LED2_PortStatus |= LedType;
		CMN_EnableInterrupt();
		break;
	case	3:
		CMN_DisableInterrupt();
		SYS_LED3_PortStatus = LedType;
		IO__PEDR &= ~IO_BIT_LEWR3;
		CMN_EnableInterrupt();
		break;
	default:
		AllLedOn();
		break;
	}
}


/*------------------------------------------------------------------------
**	＜＜＜　Ａ／Ｄ変換(A/D)　＞＞＞
*/

/*************************************************************************
	module		:[電池残量のＡ／Ｄ変換]
	function	:[
		1.Ａ／Ｄデータレジスタをリードする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/04/10]
	author		:[橘正樹]
*************************************************************************/
UWORD	AD_Battery(void)
{
	return ((UWORD)(AD__ADDRG >> 6));
}


/*************************************************************************
	module		:[サーミスタ温度のＡ／Ｄ変換]
	function	:[
		1.Ａ／Ｄデータレジスタをリードする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/07]
	author		:[橘正樹]
*************************************************************************/
UWORD	AD_Thermistor(void)
{
#if (0) /* ８ｂｉｔ換算に修正します 1998/11/26 by T.Soneoka */
**	return ((UWORD)(AD__ADDRH >> 6));
#else
	return ((UWORD)(AD__ADDRH >> 8));
#endif
}

/*************************************************************************
	module		:[ＰＳ２のＡ／Ｄ変換]
	function	:[
		1.Ａ／Ｄデータレジスタをリードする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＰＳ２ Ａ／Ｄ変換対応 
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1999/03/29]
	author		:[木元修]
*************************************************************************/
UWORD	AD_PS2(void)
{
	return ((UWORD)(AD__ADDRF >> 8));
}
/*************************************************************************
	module		:[ＰＳ１のＡ／Ｄ変換]
	function	:[
		1.Ａ／Ｄデータレジスタをリードする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＰＳ２ Ａ／Ｄ変換対応 
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2004/09/17]
	author		:[田中裕二]
*************************************************************************/
UWORD	AD_PS1(void)
{
	return ((UWORD)(AD__ADDRD >> 8));
}
/*************************************************************************
	module		:[ＰＳ１のＡ／Ｄ変換]
	function	:[
		1.Ａ／Ｄデータレジスタをリードする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＰＳ２ Ａ／Ｄ変換対応 
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2004/09/17]
	author		:[田中裕二]
*************************************************************************/
UWORD	AD_PB4(void)
{
	return ((UWORD)(AD__ADDRE >> 8));
}


/*------------------------------------------------------------------------
**	＜＜＜　その他(OTHER)　＞＞＞
*/

/*************************************************************************
	module		:[モニタースピーカＯＮ]
	function	:[
		1.ボリュームの値をモニタースピーカのボリュームにセットする。
		2.スピーカ出力をＲＸＡに切り替える。
		3.スピーカミュートを解除する。
	]
	return		:[]
	common		:[SYS_SpeakerOutputStatus]
	condition	:[]
	comment		:[CMLを引いてから
				　桐のスピーカの鳴らし方と異なるので新規作成
				  ブザー鳴動中にスピーカＯＮを行う場合を考慮した処理に変更 1996/02/21 Eguchi]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	MonitorSpeakerOn(void)
{
	if (CheckBuzzerSound() == 0) {/** ブザー鳴動中じゃない */

#if (0)
** 		/* ＨＩＮＯＫＩはロータリーボリュームです。 By O.Kimoto 1998/09/21 */
** 		/** スピーカーのボリュームを回線モニターのボリューム値にセット */
** 		MonitorSpeakerVolumeControl();
#endif

		/** スピーカー出力をライン入力に切り替え */
		SpeakerOutRXA();
		/** スピーカー出力のミュートを解除する */
		SpeakerMuteOff();
	}

	/** モデムのVolume Portを設定します。By O.Kimoto 1997/12/03 */
#if (0) /* メンテスイッチに対応します 1998/10/16 H.Hirao */
//	MDM_SetVolumeAttenuationLevel(SYS_VOLUME_MAXIMUM);
#else
	MDM_SetVolumeAttenuationLevel((SYB_MaintenanceSwitch[MNT_SW_G3] & 0xC0) >> 6);
#endif

	/** 回線モニター状態のステータスをセット */
/*	SYS_MonitorStatus = 1;未使用 */
	SYS_SpeakerOutputStatus |= SYS_SPK_OUT_MONITOR;
}

/*************************************************************************
	module		:[モニタースピーカＯＦＦ]
	function	:[
		1.スピーカー出力をミュートする
		2.スピーカー出力をブザーに切り替える。
		3.ボリュームの値をブザーのボリューム値の戻す
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[桐のスピーカの鳴らし方と異なるので新規作成]
				  ブザー鳴動中にスピーカOFFを行う場合を考慮した処理に変更 1996/02/21 Eguchi]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	MonitorSpeakerOff(void)
{
	if (CheckBuzzerSound() == 0) { /** ブザー鳴動中でないなら */
		/** スピーカー出力をミュートする */
		SpeakerMuteOn();
		/** スピーカー出力をブザーに切り替え */
		SpeakerOutBuzzer();

#if (0)
** 		/* ＨＩＮＯＫＩはロータリーボリュームです。 By O.Kimoto 1998/09/21 */
** 		/** スピーカーのボリュームを回線モニターのボリューム値にセット */
** 		/** ボリュームのセット */
** 		BuzzerVolumeControl();
#endif

	}

	/** モデムのVolume Portを設定します。By O.Kimoto 1997/12/03 */
#if (0) /* メンテスイッチに対応します 1998/10/16 H.Hirao */
//	MDM_SetVolumeAttenuationLevel(SYS_VOLUME_MAXIMUM);
#else
	MDM_SetVolumeAttenuationLevel((SYB_MaintenanceSwitch[MNT_SW_G3] & 0xC0) >> 6);
#endif
/*	SYS_MonitorStatus = 0;未使用 */
	SYS_SpeakerOutputStatus &= ~SYS_SPK_OUT_MONITOR;
}

/*************************************************************************
	module		:[スピーカーボリューム調整]
	function	:[
		1.モニター時のスピーカーボリュームの調整を行う.
	]
	return		:[]
	common		:[SYS_ETC_PortStatus]
	condition	:[]
	comment		:[
				　ここで調整するボリュームの値はオペレーション設定値である.

				  1995/10/26 小／中の論理変更
				 ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	MonitorSpeakerVolumeControl(void)
{
	/* ＨＩＮＯＫＩは、Ｆ－３３０と同様にローターリーボリュームを使ってスピーカーの音量を
	** 調整します。故に電子ボリュームはありません。 By O.Kimoto 1998/09/21 */
}

/*************************************************************************
	module		:[スピーカーボリューム調整]
	function	:[
		1.ブザー鳴動時のボリューム調整を行う
	]
	return		:[]
	common		:[SYS_ETC_PortStatus]
	condition	:[]
	comment		:[引数で与えているボリュームの値はメモリースイッチにセットされている
				  1995/10/26 小／中の論理を変更]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	BuzzerVolumeControl(void)
{
	/* ＨＩＮＯＫＩは、Ｆ－３３０と同様にローターリーボリュームを使ってスピーカーの音量を
	** 調整します。故に電子ボリュームはありません。 By O.Kimoto 1998/09/21 */
}


/******************************************************************************
	module		:[スタンプの設定を待避]
	function	:[]
	return		:[]
	common		:[
				　スキャナー送信、原稿蓄積開始と共にコールする
				]
	machine		:[SH7043]
	language	:[MS-C]
	keyword		:[CMN]
	date		:[1994/8/19]
	author		:[S.Kawasaki]
******************************************************************************/
void	CMN_EvacuateStampSetting(void)
{
	if (SYB_LocalStatus[0] & SYS_STAMP_ON) { /** スタンプの設定がＯＮ */
		SYS_StampFlag = 1;
	}
	else { /** スタンプの設定がＯＦＦ */
		SYS_StampFlag = 0;
	}
}


/*************************************************************************
	module		:[SELDMA On?]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/26]
	author		:[江口]
*************************************************************************/
void	SELDMA_On(void)
{
	/* DUMMY Function */
}

/*************************************************************************
	module		:[SELDMA Off?]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/26]
	author		:[江口]
*************************************************************************/
void	SELDMA_Off(void)
{
	/* DUMMY Function */
}

/*************************************************************************
	module		:[ＲＸＡ／ＣＮＧ／ＬＰＦ／ＴＯＮＥ切り替えＲＸＡ設定]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[曽根岡拓]
*************************************************************************/
void	FilterRXA_Set(void)
{
	/* DUMMY Function */
}

/*************************************************************************
	module		:[ＲＸＡ／ＣＮＧ／ＬＰＦ／ＴＯＮＥ切り替えＴＯＮＥ設定]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[曽根岡拓]
*************************************************************************/
void	FilterTONE_Set(void)
{
	/* DUMMY Function */
}

/*************************************************************************
	module		:[ＲＸＡ／ＣＮＧ／ＬＰＦ／ＴＯＮＥ切り替えＣＮＧ設定]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/01]
	author		:[曽根岡拓]
*************************************************************************/
void	FilterCNG_Set(void)
{
	/* DUMMY Function */
}

/*************************************************************************
	module		:[Ｒ２８８ＦのＤ＿ＲＥＱを切り替える]
	function	:[
		1.
			０：ＴＸ
			１：ＲＸ
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/07]
	author		:[橘正樹]
*************************************************************************/
void	SelectDreqDirection(UBYTE direction)
{
	/* DUMMY Function 1998/09/22 By H.Hirao */
}

/*************************************************************************
	module		:[無鳴動着信のリレー制御]
	function	:[
		1.２４Ｖオン。Ｈ／Ｌオン
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/17]
	author		:[橘正樹]
*************************************************************************/
void	NoRingRelayOn(void)
{
	if (CHK_UNI_NoRingTel2Detachable()) {
		/* ２４Ｖオフ。Ｈ／Ｌオン */
		IO__PADRL &= ~IO_BIT_CONT24;

		RelayPortStatus &= ~IO_BIT_CONT24;
		OutputWORD(GA_PGADR, RelayPortStatus);

		RelayPortStatus |= (UWORD)(IO_BIT_H | IO_BIT_L);
		OutputWORD(GA_PGADR, RelayPortStatus);
	}
	else {
#if defined(JPN)
		RI_On();
#endif
		/* ２４Ｖオン。Ｈ／Ｌオン */
		RelayPortStatus |= (UWORD)(IO_BIT_CONT24 | IO_BIT_H | IO_BIT_L);
		OutputWORD(GA_PGADR, RelayPortStatus);
	}
}

/*************************************************************************
	module		:[TEL1 のみの無鳴動着信のリレー制御]
	function	:[
		1.２４Ｖオン。Ｈオン
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/10/16]
	author		:[久保博]
*************************************************************************/
void	NoRingRelayOnTel1(void)
{
	if (CHK_UNI_NoRingTel2Detachable()) {
		/* ２４Ｖオフ。Ｈオン */
		IO__PADRL &= ~IO_BIT_CONT24;

		RelayPortStatus &= ~IO_BIT_CONT24;
		OutputWORD(GA_PGADR, RelayPortStatus);

		RelayPortStatus |= (UWORD)(IO_BIT_H);
		OutputWORD(GA_PGADR, RelayPortStatus);
	}
	else {
#if defined(JPN)
		RI_On();
#endif
		/* ２４Ｖオン。Ｈ／Ｌオン */
		RelayPortStatus |= (UWORD)(IO_BIT_CONT24 | IO_BIT_H);
		OutputWORD(GA_PGADR, RelayPortStatus);
	}
}

/*************************************************************************
	module		:[オレンジモデムの有無を獲得する。]
	function	:[
		Ｆ１２０/Ｆ１５０の時に内臓モデムの有りなしをポートで見ていたが
		アトランタは、内臓モデムは絶対あるかた「１」固定にします

		この関数は、アンズの時は「内蔵モデム＝オレンジモデム」でしたので問題ありませんでしたが
		アトランタは、「内蔵モデム≠オレンジモデム」となるため、何らかの方法で、モデムの種類を
		識別することが必要
	]
	return		:[
				1:オレンジモデム有り
				0:オレンジモデム無し
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[1997/06/12]
	author		:[村田]
*************************************************************************/
UBYTE	ExistOrangeModem(void)
{
	return(1);
}


/*************************************************************************
	module		:[内蔵モデムの種類を調べる]
	function	:[
		1.
	]
	return		:[
		CMN_ORANGE_MODEM		0
		CMN_R288F_MODEM			1
	]
	common		:[]
	condition	:[]
	comment		:[
		モデムボード（オレンジ／Ｒ２８８Ｆ）が接続されていない場合、Ｉ／Ｏの値は、１（＝２８８）となる。
		最悪のことを考えて、Ｉ／Ｏの戻り値が１の時は、本当にＲ２８８Ｆが接続されているかどうかをチェック
		する必要があるのでは．．．．
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CMN_KinkOfModem(void){}]
	date		:[1997/06/14]
	author		:[木元修]
*************************************************************************/
UBYTE CMN_KinkOfModem(void)
{
	return(CMN_R288F_MODEM);
}


/*************************************************************************
	module		:[あるキー押しながら電源ＯＮすると自動的にＤＲＡＭクリアを実行する]
	function	:[
	]
	return		:[
				1:あるキーが押されている
				0:押されてない
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[1997/06/17]
	author		:[村田]
*************************************************************************/
UBYTE CMN_ForcedDRAM_InitialKey(void)
{

#if (0)
	/* まだだよ。 By O.Kimoto 1998/09/21 */
	if (inpw(KEY7_PORT) & IO_BIT_KEY69) {
		return(0);
	}
	else {
		return(1);
	}
#endif
	return(0);

}

/*************************************************************************
	module		:[ＤＭＡ（ＤＴＣ）をマスクします]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/16]
	author		:[村田]
*************************************************************************/
void DMA_DTC_RequestReqDisable(void)
{
	/* Dummy Function 1998/09/22 By H.Hirao */
#if (0)
	/* 1997/12/19
	 * この対策は当分使用しません。０固定です。
	 * この対策をいれるときはハードもセットで交換となります。
	*/

	/*IO__PEDR |= IO_BIT_HV2;*/
	IO__PEDR &= ~IO_BIT_HV2;
#endif
}

/*************************************************************************
	module		:[ＤＭＡ（ＤＴＣ）をマスクを解除します]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/16]
	author		:[村田]
*************************************************************************/
void DMA_DTC_RequestReqEnable(void)
{
	/* Dummy Function 1998/09/22 By H.Hirao */
#if (0)
	IO__PEDR &= ~IO_BIT_HV2;
#endif
}

/*************************************************************************
	module		:[Ｔリレーを放す]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/06/11]
	author		:[曽根岡拓]
*************************************************************************/
void T_RelayOff(void)
{
	/* Dummy Function 1998/09/28 By H.Hirao */
}



/*************************************************************************
	module		:[メモリ送信ＬＥＤセット]
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
	date		:[1995/07/11]
	author		:[江口]
*************************************************************************/
void MemoryTxLedSet(void)
{
	if (CHK_MemoryTxON() & MEMORY_TRANSMISSION_ON) {
		SYB_LocalStatus[0] |= SYS_MEMORY_TX_ON;
		MemoryTxLedOn();
	}
	else {
		SYB_LocalStatus[0] &= ~SYS_MEMORY_TX_ON;
		MemoryTxLedOff();
	}
}

/*************************************************************************
	module		:[済みスタンプＬＥＤセット]
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
	date		:[1995/11/27]
	author		:[江口]
*************************************************************************/
void StampLedSet(void)
{
	if (CHK_StampON() & DOCUMENT_STAMP_ON) {
		SYB_LocalStatus[0] |= SYS_STAMP_ON;
		StampLedOn();
	}
	else {
		SYB_LocalStatus[0] &= ~SYS_STAMP_ON;
		StampLedOff();
	}
}


#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/24 */
/*************************************************************************
	module		:[回線選択ﾘﾚｰ切替え（内蔵）]
	function	:[
		1.ポートをＯＦＦする（＝＞標準回線側）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[SHC]
	keyword		:[CMN]
	ProtoType	:[void ModemRelay_Off(void){}]
	date		:[2005/06/17]
	author		:[Smuratec 李]
*************************************************************************/
void ModemRelay_Off(void)
{
	IO__PADRL &= ~(IO_BIT_LINESW | IO_BIT_SUSBEL);
}


/*************************************************************************
	module		:[回線選択ﾘﾚｰ切替え（Ｅｘｔ．）]
	function	:[
		1.ポートをＯＮする（＝＞拡張回線側）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[SHC]
	keyword		:[CMN]
	ProtoType	:[void ModemRelay_On(void){}]
	date		:[2005/06/17]
	author		:[Smuratec 李]
*************************************************************************/
void ModemRelay_On(void)
{
	IO__PADRL |= (IO_BIT_LINESW | IO_BIT_SUSBEL);
}

/*************************************************************************
	module		:[回線選択リレー設定チェック]
	function	:[
		1.LINESWリレーがＯＮ／ＯＦＦされているかチェックする。
	]
	return		:[	０：ＯＦＦ	(標準回線)
					１：ＯＮ	(拡張回線)
				]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[2005/06/17]
	author		:[Smuratec 李]
*************************************************************************/
UBYTE 	ModemRelaySetting(void)
{
	if (IO__PADRL & (IO_BIT_LINESW | IO_BIT_SUSBEL)) {
		return(1);
	}
	return(0);
}

#else /* !defined (KEISATSU) */
/*************************************************************************
	module		:[回線選択ﾘﾚｰ切替え（内蔵）]
	function	:[
		1.ポートをＯＦＦする（＝＞標準回線側）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[SHC]
	keyword		:[CMN]
	ProtoType	:[void ModemRelay_Off(void){}]
	date		:[1997/09/19]
	author		:[木元修]
*************************************************************************/
void ModemRelay_Off(void)
{
	/* Dummy Function 1998/10/29 By H.Hirao */
	/* IO__PADRL &= ~IO_BIT_MODEM; */
}


/*************************************************************************
	module		:[回線選択ﾘﾚｰ切替え（Ｅｘｔ．）]
	function	:[
		1.ポートをＯＮする（＝＞Ｅｘｔ．回線側）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[SHC]
	keyword		:[CMN]
	ProtoType	:[void ModemRelay_On(void){}]
	date		:[1997/09/19]
	author		:[木元修]
*************************************************************************/
void ModemRelay_On(void)
{
	/* Dummy Function 1998/10/29 By H.Hirao */
	/* IO__PADRL |= IO_BIT_MODEM; */
}
#endif /* defined (KEISATSU) */


/*************************************************************************
	module		:[PHONEリレー ON]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		PHONEリレーをEXT.LINE側に倒します : LINE+PHONE1 と EXT.LINE+PHONE2
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/11]
	author		:[曽根岡拓]
*************************************************************************/
void	PHONE2_RelayOn(void)
{
	/* Dummy Function 1998/10/29 By H.Hirao */
	/* SYS_Modem2PortStatus |= IO_PHONE2; */
	/* outpw(MODEM2_PORT, SYS_Modem2PortStatus); */
}

/*************************************************************************
	module		:[PHONEリレー OFF]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		PHONEリレーをLINE側に倒します : LINE+PHONE1+PHONE2 と EXT.LINE
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/11]
	author		:[曽根岡拓]
*************************************************************************/
void	PHONE2_RelayOff(void)
{
	/* Dummy Function 1998/10/29 By H.Hirao */
	/* SYS_Modem2PortStatus &= ~IO_PHONE2; */
	/* outpw(MODEM2_PORT, SYS_Modem2PortStatus); */
}

#if (PRO_CLASS1 == ENABLE)
/*************************************************************************
	module		:[RS232CのRTSをEnable(Low)にする]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[なし]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void RTS_Enable(void)
{
	IO__PADRL &= (~IO_BIT_XRTS);
}

/*************************************************************************
	module		:[RS232CのRTSをDisable(High)にする]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[なし]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void RTS_Disable(void)
{
	IO__PADRL |= IO_BIT_XRTS;
}

/*************************************************************************
	module		:[CTSの割込み許可]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void CTS_IntEnable(void)
{
	SH__IPRB |= IRQ7_LEVEL;
}

/*************************************************************************
	module		:[CTSの割込み禁止]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void CTS_IntDisable(void)
{
	SH__IPRB &= (~IRQ7_LEVEL);
}

#endif	/* (PRO_CLASS1 == ENABLE) */

#if defined(HINOKI2) || defined (HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
/*************************************************************************
	module		:[LC821033 内部リフレッシュ処理フラグ]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[内部リフレッシュの状態を表示します。]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[2000/11/20]
	author		:[前田雅也]
*************************************************************************/
UBYTE LC821033_CheckIMFLG(void)	/* LC821033仕様の為、追加 Y.Kano 2003/07/08 */
{
	return ((Input(SREG_F) & IP_IMFLG_LC33));
}

/*************************************************************************
	module		:[LC821033 歪み補正メモリ選択]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[アクセスする歪み補正メモリを選択します。
				  0 : 白歪み補正メモリ
				  1 : 黒歪み補正メモリ
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[2000/11/24]
	author		:[前田雅也]
*************************************************************************/
void LC821033_SetMSEL(UBYTE is_enable)
{
	UBYTE	Work;

	Work = Input(SREG_F) & 0xFF;
	if (is_enable) {
		Work |= (UBYTE)IP_MSEL_LC33;
	}
	else {
		Work &= ~(UBYTE)IP_MSEL_LC33;
	}
	Output(SREG_F, Work);
}

/*************************************************************************
	module		:[LC821033 歪み補正メモリ]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[歪み補正メモリへアクセスする際に、内部リフレッシュの実行、停止を
				  設定します。内部リフレッシュ停止中は、外部よりリフレッシュを行う
				  必要があります。
				  0 : 実行
				  1 : 停止
				  内部画像処理クロックでレジスタ値を読み込みます。
				  MFLG = "1"の設定は必ずIFLGが"0"の時に行ってください。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[2000/11/20]
	author		:[前田雅也]
*************************************************************************/
void LC821033_SetMFLG(UBYTE is_enable)
{
	UBYTE	Work;

	Work = Input(SREG_F) & 0xFF;
	if (is_enable) {
		Work |= IP_MFLG_LC33;
	}
	else {
		Work &= ~IP_MFLG_LC33;
	}
	Output(SREG_F, Work);
}

/*************************************************************************
	module		:[LC821033 強調度選択・二次元フィルタ選択]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[強調処理の強調度を選択します。
				  設定は強調フィルタ１、２のみ有効です。
				       フィルタ１  フィルタ２
				  0 :    × 0.5       禁止
				  1 :    × 1.0      × 1.0
				  2 :    × 2.0      × 2.0
				  3 :    × 3.0       禁止
				  4 :    × 4.0       禁止
			 5 ～ 7 :           禁止

				  二次元フィルタを選択します。
				  0 : スルー
				  1 : 強調フィルタ１(単純二値化処理推奨)
				  2 : 強調フィルタ２(中間調処理推奨)
				  3 : 平滑
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[2003/09/02]
	author		:[加納 義彦]
*************************************************************************/
void LC821033_Set2DFilter(UWORD filter)
{
	UBYTE	Work;

	Work = (Input(SREG_2) & ~(UWORD)(IP_FEG_LC33 | IP_FM_LC33)) & 0x00FF;

	switch (filter) {
	case FILTER_THOUGH:		/* スルー */
		Work |= (UWORD)IP_FM_0_LC33;
		break;
	case FILTER1_HALF:		/* 強調フィルタ1、×0.5 */
		Work |= (UWORD)(IP_FM_1_LC33 | IP_FEG_0_LC33);
		break;
	case FILTER1_1:			/* 強調フィルタ1、×1.0 */
		Work |= (UWORD)(IP_FM_1_LC33 | IP_FEG_1_LC33);
		break;
	case FILTER1_2:			/* 強調フィルタ1、×2.0 */
		Work |= (UWORD)(IP_FM_1_LC33 | IP_FEG_2_LC33);
		break;
	case FILTER1_3:			/* 強調フィルタ1、×3.0 */
		Work |= (UWORD)(IP_FM_1_LC33 | IP_FEG_3_LC33);
		break;
	case FILTER1_4:			/* 強調フィルタ1、×4.0 */
		Work |= (UWORD)(IP_FM_1_LC33 | IP_FEG_4_LC33);
		break;
	case FILTER2_1:			/* 強調フィルタ2、×1.0 */
		Work |= (UWORD)(IP_FM_2_LC33 | IP_FEG_1_LC33);
		break;
	case FILTER2_2:			/* 強調フィルタ2、×2.0 */
		Work |= (UWORD)(IP_FM_2_LC33 | IP_FEG_2_LC33);
		break;
	case FILTER_AVERAGE:	/* 平滑 */
		Work |= (UWORD)IP_FM_3_LC33;
		break;
	case FILTER0_0:			/* 強調フィルタ使用しない by Y.kano 2004/01/28 */
		Work |= (UWORD)(IP_FM_0_LC33 | IP_FEG_0_LC33);
		break;
	default:				/* 禁止 */
		Work |= (UWORD)(IP_FM_1_LC33 | IP_FEG_1_LC33);
		break;
	}
	Output(SREG_2, Work);
}

/*************************************************************************
	module		:[LC821033 D/A 設定値制御]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[D/A変換器の設定を制御します。
				  0 : ラインの頭から補正有効期間終了までレジスタDAHAを設定。
				  1 : すべての期間レジスタDAHAを設定。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[2000/11/24]
	author		:[前田雅也]
*************************************************************************/
void LC821033_SetTMPR(UBYTE is_enable)
{
	UBYTE	Work;

	Work = Input(SREG_13);

	if (is_enable) {
		Work |= IP_TMPR_LC33;
	}
	else {
		Work &= ~IP_TMPR_LC33;
	}
	Output(SREG_13, Work);
}

/*************************************************************************
	module		:[LC821033 センサ信号期間A／Dハイリファレンス用D/A値]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[2000/11/24]
	author		:[前田雅也]
*************************************************************************/
UBYTE LC821033_CheckDAHA(void)
{
	return ((Input(SREG_13) & IP_DAHA_LC33) & 0x3f);
}

/*************************************************************************
	module		:[LC821033 センサ信号期間A／Dハイリファレンス用D/A値]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[センサ信号を処理する期間でのA／D変換器のハイリファレンス用D/A変換器の
				  設定を設定します。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[2000/11/24]
	author		:[前田雅也]
*************************************************************************/
void LC821033_SetDAHA(UBYTE ref)
{
	UBYTE	Work;

	Work  = (Input(SREG_13) & ~IP_DAHA_LC33) & 0x3f;
	Work |= (ref & IP_DAHA_LC33);
	Output(SREG_13, Work);
}

/*************************************************************************
	module		:[LC821033 "FF"値カウント]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[１ラインの処理有効期間における最大値(A/D値で"FFh")の画素の個数を
				  カウントします。最大で"Fh"までカウントします。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[2000/11/20]
	author		:[前田雅也]
*************************************************************************/
UBYTE LC821033_CheckFF(void)
{
	return((Input(SREG_10) & IP_FF_LC33) & 0xff);
}

/******************************************************************************
	module		:[画処理選択]
	function	:[
		1.MRD9801のポート00C00300Ｈを読み込み
		2.PGB9のビットが立っているかチェック
	]
	return		:[
		0:	PGB9がLow(LC82103)
		1:	PGB9がHigh(LC821033)
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2003/12/03]
	author		:[加納義彦]
******************************************************************************/
UBYTE	LC821033_PGB9(void)
{
 #if defined (HINOKI3)
	return (1);
 #else
	if (InputWORD(GA_PGBDR) & IO_BIT_PGB9) {
		return(1);
	}
	return(0);
 #endif
}


#endif	/* End of defined(HINOKI2) */

#if defined (KEISATSU) /* 警察FAX 05/05/07 石橋正和 */

/**********************************************************************************************************************
	Module    : 背面スクランブルスイッチのON/OFFチェック
	Function  : 
		1. 
	Argument  : 
	Return    : TRUE:	ON
				FALSE:	OFF
	Note      : 
	Create    : 2005/05/07
	Author    : 石橋正和
**********************************************************************************************************************/
BOOL CheckScrambleSwOn(void)
{
	if (IO__PADRH & IO_BIT_EST) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

/**********************************************************************************************************************/
/**
	@brief		DTC割込みをモデムからにする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/16 作成
	@author		石橋正和
*/
/**********************************************************************************************************************/
void SetDTC_IntFromModem(void)
{
	IO__PADRL &= (~IO_BIT_MDM_S1);
}

/**********************************************************************************************************************/
/**
	@brief		DTC割込みをS1からにする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/16 作成
	@author		石橋正和
*/
/**********************************************************************************************************************/
void SetDTC_IntFromS1(void)
{
	IO__PADRL |= IO_BIT_MDM_S1;
}

/**********************************************************************************************************************/
/**
	@brief		S1基板エラー検知
	
	@li			
	@param		
	@return		TRUE:  エラー
				FALSE: 正常
	@note		
	@date		2005/11/02 作成
	@author		石橋正和
*/
/**********************************************************************************************************************/
BOOL CheckS1Error(void)
{
	if (IO__PADRL & IO_BIT_XLC3) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

#endif

#if defined (KEISATSU)		/* 警察FAX Added DVT_ID15 by SMuratec K.W.Q 2005/11/05 */
/*************************************************************************
	module		:[Ｌ／ＫＬリレーを引く]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[]
	author		:[]
*************************************************************************/
void	Keisatsu_L_RelayOn(void)
{
	if (SYS_FactoryModem.Item == SYS_OPT_MDM_RELAY_TEST) {
		RelayPortStatus |= IO_BIT_L;
		OutputWORD(GA_PGADR, RelayPortStatus);
	}
	else if (SYS_FactoryModem.Item == SYS_OPT_MDM_KEIDEN_RELAY_TEST){
		IO__PADRL |= IO_BIT_K_L;
	}

}

/*************************************************************************
	module		:[Ｌ／ＫＬリレーを放す]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[]
	author		:[]
*************************************************************************/
void	Keisatsu_L_RelayOff(void)
{
	if (SYS_FactoryModem.Item == SYS_OPT_MDM_RELAY_TEST) {
		RelayPortStatus &= ~IO_BIT_L;
		OutputWORD(GA_PGADR, RelayPortStatus);
	}
	else if (SYS_FactoryModem.Item == SYS_OPT_MDM_KEIDEN_RELAY_TEST){
		IO__PADRL &= ~IO_BIT_K_L;
	}
}
#endif		/* End of (defined (KEISATSU)) */


