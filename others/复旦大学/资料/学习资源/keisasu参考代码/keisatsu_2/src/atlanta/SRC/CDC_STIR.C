/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/07/25
*        FILE NAME:  cdc_stir.c
*      DESCRIPTION:  松下製コーデックNM86063のSTIR(ステータスインタラプトレジスタ)を
*                    チェックする為のファイル群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:  UWORD CDC_CheckDecodeError(UBYTE codec_type);
*                    UWORD CDC_CheckDetectRTC(UBYTE codec_type);
*                    UWORD CDC_CheckAccept(UBYTE codec_type);
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\ext_v\cdc_data.h"

/*************************************************************************
	module		:[
		コマンド終了割り込みでセットされているＳＴＩＲの大域変数を
		参照して、デコードエラーで終了したかどうかを調べる
	]
	function	:[
		1.機種によって調べる大域変数を決定する
		2.デコードエラービットをチェックする
	]
	return		:[1:エラーあり 0:エラーなし]
	common		:[
		CodecSTIR_Status
	]
	condition	:[]
	comment		:[
		StartDecode(), StartCodeConvertの終了時にコールされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/07/25]
	author		:[小谷正樹]
*************************************************************************/
UWORD CDC_CheckDecodeError(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	if (codec_type == SCANNER_CODEC) {
		if (CodecSTIR_Status[SCANNER_CODEC] & DERR0_BIT) {	/**コマンド終了割り込みでこの変数に終了状態がセットされている*/
			return (1);
		}
		else {
			return (0);
		}
	}
	if (codec_type == PRINTER_CODEC) {
		if (CodecSTIR_Status[SCANNER_CODEC] & DERR1_BIT) {	/**コマンド終了割り込みでこの変数に終了状態がセットされている*/
			return (1);
		}
		else {
			return (0);
		}
	}
	if (codec_type == COMMUNICATION_CODEC) {	/**TBD*/
		if (CodecSTIR_Status[SCANNER_CODEC] & DERR0_BIT) {	/**コマンド終了割り込みでこの変数に終了状態がセットされている*/
			return (1);
		}
		else {
			return (0);
		}
	}
#else
	if (CodecSTIR_Status[codec_type] & DERR0_BIT) {	/**コマンド終了割り込みでこの変数に終了状態がセットされている*/
		return (1);
	}
	else {
		return (0);
	}
#endif
	return (0);	/**ありえないパス*/
}


/*************************************************************************
	module		:[
		コマンド終了割り込みでセットされているＳＴＩＲの大域変数を
		参照して、ＲＴＣ検出で終了したかどうかを調べる
	]
	function	:[
		1.機種によって調べる大域変数を決定する
		2.RTC検出ビットをチェックする
	]
	return		:[1:RTC検出 0:RTC未検出]
	common		:[
		CodecSTIR_Status
	]
	condition	:[]
	comment		:[
		StartDecode(), StartCodeConvertの終了時にコールされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/07/25]
	author		:[小谷正樹]
*************************************************************************/
UWORD CDC_CheckDetectRTC(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	if (codec_type == SCANNER_CODEC) {
		if (CodecSTIR_Status[SCANNER_CODEC] & RTCDT0_BIT) {	/**コマンド終了割り込みでこの変数に終了状態がセットされている*/
			return (1);
		}
		else {
			return (0);
		}
	}
	if (codec_type == PRINTER_CODEC) {
		if (CodecSTIR_Status[SCANNER_CODEC] & RTCDT1_BIT) {	/**コマンド終了割り込みでこの変数に終了状態がセットされている*/
			return (1);
		}
		else {
			return (0);
		}
	}
	if (codec_type == COMMUNICATION_CODEC) {	/**TBD*/
		if (CodecSTIR_Status[SCANNER_CODEC] & RTCDT0_BIT) {	/**コマンド終了割り込みでこの変数に終了状態がセットされている*/
			return (1);
		}
		else {
			return (0);
		}
	}
#else
	if (CodecSTIR_Status[codec_type] & RTCDT0_BIT) {	/**コマンド終了割り込みでこの変数に終了状態がセットされている*/
		return (1);
	}
	else {
		return (0);
	}
#endif
	return (0);	/**ありえないパス*/
}


/*************************************************************************
	module		:[
		コマンド終了割り込みでセットされているＳＴＩＲの大域変数を
		参照して、アボート受け付けで終了したかどうかを調べる
	]
	function	:[
		1.機種によって調べる大域変数を決定する
		2.アボート受け付けビットをチェックする
	]
	return		:[1:アボート受け付け 0:アボートなし]
	common		:[
		CodecSTIR_Status
	]
	condition	:[]
	comment		:[
		StartEncode(), StartDecode(), StartCodeConvertの終了時にコールされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/07/25]
	author		:[小谷正樹]
*************************************************************************/
UWORD CDC_CheckAccept(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	if (codec_type == SCANNER_CODEC) {
		if (CodecSTIR_Status[SCANNER_CODEC] & ABACT0_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
			return (1);
		}
		else {
			return (0);
		}
	}
	if (codec_type == PRINTER_CODEC) {
		if (CodecSTIR_Status[SCANNER_CODEC] & ABACT1_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
			return (1);
		}
		else {
			return (0);
		}
	}
	if (codec_type == COMMUNICATION_CODEC) {	/**TBD*/
		if (CodecSTIR_Status[SCANNER_CODEC] & ABACT0_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
			return (1);
		}
		else {
			return (0);
		}
	}
#else
	if (CodecSTIR_Status[codec_type] & ABACT0_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
		return (1);
	}
	else {
		return (0);
	}
#endif
	return (0);	/**ありえないパス*/
}


