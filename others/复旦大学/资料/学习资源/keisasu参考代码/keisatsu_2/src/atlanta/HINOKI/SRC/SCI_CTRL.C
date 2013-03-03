/*----------------------------------------------------------------------*/
/* プロジェクト : HINOKI                                                */
/* ファイル名   : SCI_CTRL.C                                            */
/* 作成者名     : 平尾 英典                                             */
/* 日  付       : 1999/01/11                                            */
/* 概  要       : ＳＣＩドライバ関数                                    */
/* 修正履歴     :                                                       */
/*----------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"

#if (PRO_MODEM == R288F)
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#endif

#include "\src\atlanta\define\cl1_def.h"
#include "\src\atlanta\define\cl1_mpsc.h"
#include "\src\atlanta\define\cl1_pro.h"
#include "\src\atlanta\ext_v\cl1_data.h"
#include "\src\atlanta\ext_v\cl1_tbl.h"
#include "\src\cpu\sh7043_a\irom\define\sh_sys.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\define\mntsw_g.h"	/* added by H.Hirao 1999/03/19 */


/*************************************************************************
	module		:[パリティイネーブル、パリィティモードの設定]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void ParityModeSet(void)
{
	/* RsDriver.sci_smr = inp(SCI_SMR1); */
	
	if (SYB_SettingStatus[SETTING_STATUS_5] & RS232C_PARITY_ODD) {
		RsDriver.sci_smr |= SMR_PE + SMR_ODD;
	}
	else if (SYB_SettingStatus[SETTING_STATUS_5] & RS232C_PARITY_EVEN) {
		RsDriver.sci_smr |= SMR_PE;
	}
	else {
		RsDriver.sci_smr &= ((~SMR_PE) | (~SMR_ODD));
	}
	Output(SCI_SMR1, RsDriver.sci_smr);
}

/*************************************************************************
	module		:[ストップビットレングスの設定]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void StopBitLengthSet(void)
{
	/* RsDriver.sci_smr = inp(SCI_SMR1); */

	if (SYB_SettingStatus[SETTING_STATUS_5] & RS232C_STOP_LENGTH_2) {
		RsDriver.sci_smr |= SMR_STOP2;
	}
	else {
		RsDriver.sci_smr &= (~SMR_STOP2);
	}	
	Output(SCI_SMR1, RsDriver.sci_smr);
}

/*************************************************************************
	module		:[クロックセレクト、ビットレートレジスタの設定]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void ClkSelectAndBitRateRegSet(UBYTE rate)
{
	/* RsDriver.sci_smr = inp(SCI_SMR1); */
	/* RsDriver.sci_brr = inp(SCI_BRR1); */

 	if (SYB_MaintenanceSwitch[MNT_SW_G2] & 0x08) {	/* 38400bps/s by H.Hirao 1999/03/19 */
		RsDriver.sci_smr = (RsDriver.sci_smr & 0xFC) | 0;
		RsDriver.sci_brr = 22;
	}
	else {
		if (!rate) {
			rate = (UBYTE)(SYB_SettingStatus[SETTING_STATUS_5] & 0x07);	/* 下位３ビット */
		}
		RsDriver.sci_smr = (RsDriver.sci_smr & 0xFC) | sciBitRateTbl[rate].Smr1;
		RsDriver.sci_brr = sciBitRateTbl[rate].Brr1;
	}
	Output(SCI_SMR1, RsDriver.sci_smr);
	Output(SCI_BRR1, RsDriver.sci_brr);
}

/*************************************************************************
	module		:[キャラクタレングスの設定]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void CharacterLengthSet(void)
{
	/* RsDriver.sci_smr = inp(SCI_SMR1); */

	if (!(SYB_SettingStatus[SETTING_STATUS_5] & RS232C_DATA_LENGTH_8)) {
		RsDriver.sci_smr |= SMR_CHR_7BIT;
  	}
  	else {
		RsDriver.sci_smr &= (~SMR_CHR_7BIT);
  	}
	Output(SCI_SMR1, RsDriver.sci_smr);
}

/*************************************************************************
	module		:[ＳＣＩの初期化]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void SciInitialize(void)
{
	RsDriver.sci_scr = 0x00;
	Output(SCI_SCR1, RsDriver.sci_scr);	/* TE,RE Clear 調歩同期、内部クロック */
	ParityModeSet();
	StopBitLengthSet();
	ClkSelectAndBitRateRegSet(0);
	CharacterLengthSet();
	wai_tsk(1);			/* １Bit期間経過 */
}

/*************************************************************************
	module		:[ＳＣＩのデータ転送パラメータの設定]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/31]
	author		:[平尾 英典]
*************************************************************************/
void SciSetParameter(void)
{
	ParityModeSet();
	StopBitLengthSet();
	ClkSelectAndBitRateRegSet(0);
	CharacterLengthSet();
	wai_tsk(1);			/* １Bit期間経過 */
}

/*************************************************************************
	module		:[ポート・テスト・モード（送信、エコーバック）に初期設定]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/02/09]
	author		:[平尾 英典]
*************************************************************************/
void SciTestInit(void)
{
	CMN_DisableInterrupt();

	CTS_IntDisable();		/* added by H.Hirao 1999/05/14 */
	CmtCtsIntDisable();		/* added by H.Hirao 1999/05/14 */

	RsDriver.sci_scr &= (~SCR_TE);	/* 送信動作を禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);

	RsDriver.sci_scr &= (~SCR_RE);	/* 受信動作を禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);

	RsDriver.sci_scr |= SCR_RIE;	/* 受信割り込み許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);
	RsDriver.sci_scr |= SCR_TIE;	/* 送信データエンプティ割り込み要求を許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);
	RsDriver.sci_scr &= (~SCR_TEIE);	/* 送信終了割り込み要求を禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);

	RsDriver.sci_scr |= SCR_RE;	/* 受信動作を許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);

	RsDriver.sci_scr |= SCR_TE;	/* 送信動作を許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);

	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[ポート・テスト・モード（受信）に初期設定]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/02/09]
	author		:[平尾 英典]
*************************************************************************/
void SciRxTestInit(void)
{
	CMN_DisableInterrupt();

	RsDriver.sci_scr &= (~SCR_TE);	/* 送信動作を禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);

	RsDriver.sci_scr &= (~SCR_RE);	/* 受信動作を禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);

	RsDriver.sci_scr |= SCR_RIE;	/* 受信割り込み許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);

	RsDriver.sci_scr |= SCR_RE;	/* 受信動作を許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);

	CMN_EnableInterrupt();
}

/*************************************************************************
	module		:[送信動作を許可]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void SciTxEnable(void)
{
	/*
	** CTSの制御が必要？
	*/
	RsDriver.sci_scr |= SCR_TE;	/* 送信動作を許可 */
	RsDriver.sci_scr &= (~SCR_TIE);
	Output(SCI_SCR1, RsDriver.sci_scr);
}

/*************************************************************************
	module		:[送信割込み禁止]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void SciTxDisable(void)
{
	RsDriver.sci_scr &= (~SCR_TE);	/* 送信動作を禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);
	RsDriver.sci_scr &= (~SCR_TIE);		/* 送信データエンプティ割り込み要求を禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);
}

/*************************************************************************
	module		:[送信割込み許可]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void SciIntTxEnable(void)
{
	RsDriver.sci_scr &= (~SCR_TE);	/* 送信動作を禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);
	RsDriver.sci_scr |= SCR_TIE;	/* 送信データエンプティ割り込み要求を許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);
	RsDriver.sci_scr |= SCR_TE;	/* 送信動作を許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);
}

/*************************************************************************
	module		:[受信動作を許可]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void SciRxEnable(void)
{
	/*
	** DCDの制御も必要？
	*/
	RsDriver.sci_scr |= SCR_RIE;	/* 受信割り込み許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);
	RsDriver.sci_scr |= SCR_RE;	/* 受信動作を許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);
}

/*************************************************************************
	module		:[受信割込み禁止]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void SciRxDisable(void)
{
	RsDriver.sci_scr &= (~SCR_RE);	/* 受信動作を禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);
	RsDriver.sci_scr &= (~SCR_RIE);	/* 受信割り込み禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);
}

/*************************************************************************
	module		:[受信割込み許可]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void SciIntRxEnable(void)
{
	RsDriver.sci_scr &= (~SCR_RE);	/* 受信動作を禁止 */
	Output(SCI_SCR1, RsDriver.sci_scr);
	RsDriver.sci_scr |= SCR_RIE;	/* 受信割り込み許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);
	RsDriver.sci_scr |= SCR_RE;	/* 受信動作を許可 */
	Output(SCI_SCR1, RsDriver.sci_scr);
}

/*************************************************************************
	module		:[送信終了割り込み(TEI)要求を禁止]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void SciTransmitEndIntEnable(void)
{
	RsDriver.sci_scr |= SCR_TEIE;
	Output(SCI_SCR1, RsDriver.sci_scr);
}

/*************************************************************************
	module		:[送信終了割り込み(TEI)要求を禁止]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void SciTransmitEndIntDisable(void)
{
	RsDriver.sci_scr &= (~SCR_TEIE);
	Output(SCI_SCR1, RsDriver.sci_scr);
}

/*************************************************************************
	module		:[プログラムによりデータ送信]
	function	:[
		1. トランスミットデータレジスタエンプティを調べる（最大10回）
	]
	return		:[
	]
	common		:[なし]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
UBYTE SciPutChar(UBYTE txchar)
{
	/*UBYTE*/ UWORD	i;

	for (i = 0; i < 0xFFFF; i++) {
		RsDriver.sci_ssr = Input(SCI_SSR1);
		if (RsDriver.sci_ssr & SSR_TDRE) {
			Output(SCI_TDR1, txchar);
			return (1);
		}
	}
	return (0);
}

/*************************************************************************
	module		:[TxBuffer内のデータが全て送信完了するのを待つ]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/11]
	author		:[平尾 英典]
*************************************************************************/
void SciWaitTxComplete(void)
{
	UWORD	i;
	
	for (i = 0xffff; i != 0; i--) {
		RsDriver.sci_ssr = Input(SCI_SSR1);
		if (RsDriver.sci_ssr & SSR_TEND) {
			break;
		}
	}
}
#else
/* dummy function */
void sci_ctrl_dummy(void){}
#endif
