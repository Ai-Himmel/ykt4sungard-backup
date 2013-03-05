/*	By Y.Suzuki 1996/10/22	*/
/*	Original File jun\usr2:\src\kobe\anzu\src\cmnuni_a.c	*/
/************************************************
 * CMNUNI_A.C
 * 機種固有スイッチAの設定状態を獲得する関数
 * 1996/04/11 Eguchi
 ************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\unisw_a.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\uni_pro.h"

/*************************************************************************
	module		:[フラッシュキー無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/22]
	author		:[原田]
*************************************************************************/
UBYTE CHK_UNI_FlashkeyCheck(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A0] & FLASHKEY_CHECK));
}

/*************************************************************************
	module		:[グランドキー無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/08]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_GroundkeyCheck(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A0] & GROUNDKEY_CHECK));
}

/*************************************************************************
	module		:[ループカレントチェック無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/08]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_CurrentLoop(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A0] & CURRENT_LOOP_CHECK));
}

/*************************************************************************
	module		:[極性反転検出無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/08]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_DSE_Detect(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A0] & DSE_DETECT));
}




/*************************************************************************
	module		:[リングバックトーン送出開始までの時間の獲得]
	function	:[
		1.
	]
	return		:[
				30/33/36/39(秒）
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/04/11]
	author		:[江口]
*************************************************************************/
UBYTE CHK_UNI_RingBackToneWaitTime(void)
{
/*	return ((UBYTE )((SYB_MachineUniqSwitch[UNIQ_SW_A0] & (RING_BACK_TONE_START0 | RING_BACK_TONE_START1))>>4) + 30); */
	return ((UBYTE )((SYB_MachineUniqSwitch[UNIQ_SW_A0] & (RING_BACK_TONE_START0 | RING_BACK_TONE_START1))>>4));
}

/*************************************************************************
	module		:[Congestion Tone検出無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/08]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_ConToneDetect(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A0] & MEM_CONTONE_DETECT));
}

/*************************************************************************
	module		:[内蔵ラインの送／受信設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far SET_UNI_Line0_TxRx(UBYTE){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
void SET_UNI_Line0_TxRx(UBYTE value)
{
	SYB_MachineUniqSwitch[UNIQ_SW_A7] &= ~((UBYTE)(LINE0_TX_ONLY | LINE0_RX_ONLY));
	SYB_MachineUniqSwitch[UNIQ_SW_A7] |= value;
}


/*************************************************************************
	module		:[内蔵ラインの送／受信設定の獲得]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_Line0_TxRx(void){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_Line0_TxRx(void)
{
	switch ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A7] & (LINE0_TX_ONLY | LINE0_RX_ONLY))) {
	case LINE0_TX_ONLY:
		return(EXCLUSIVE_TX);
	case LINE0_RX_ONLY:
		return(EXCLUSIVE_RX);
	default:
		return(EXCLUSIVE_TRX);
	}
}


/*************************************************************************
	module		:[外付け第１回線目の送／受信設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far SET_UNI_Line1_TxRx(UBYTE){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
void SET_UNI_Line1_TxRx(UBYTE value)
{
	SYB_MachineUniqSwitch[UNIQ_SW_A7] &= ~((UBYTE)(LINE1_TX_ONLY | LINE1_RX_ONLY));
	SYB_MachineUniqSwitch[UNIQ_SW_A7] |= (UBYTE)(value << 2);
}


/*************************************************************************
	module		:[外付け第１回線目の送／受信設定の獲得]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_Line1_TxRx(void){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_Line1_TxRx(void)
{
	switch ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A7] & (LINE1_TX_ONLY | LINE1_RX_ONLY))) {
	case LINE1_TX_ONLY:
		return(EXCLUSIVE_TX);
	case LINE1_RX_ONLY:
		return(EXCLUSIVE_RX);
	default:
		return(EXCLUSIVE_TRX);
	}
}


/*************************************************************************
	module		:[外付け第２回線目の送／受信設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far SET_UNI_Line2_TxRx(UBYTE){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
void SET_UNI_Line2_TxRx(UBYTE value)
{
	SYB_MachineUniqSwitch[UNIQ_SW_A7] &= ~((UBYTE)(LINE2_TX_ONLY | LINE2_RX_ONLY));
	SYB_MachineUniqSwitch[UNIQ_SW_A7] |= (UBYTE)(value << 4);
}


/*************************************************************************
	module		:[外付け第２回線目の送／受信設定の獲得]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_Line2_TxRx(void){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_Line2_TxRx(void)
{
	switch ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A7] & (LINE2_TX_ONLY | LINE2_RX_ONLY))) {
	case LINE2_TX_ONLY:
		return(EXCLUSIVE_TX);
	case LINE2_RX_ONLY:
		return(EXCLUSIVE_RX);
	default:
		return(EXCLUSIVE_TRX);
	}
}


/*************************************************************************
	module		:[外付け第３回線目の送／受信設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far SET_UNI_Line3_TxRx(UBYTE){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
void SET_UNI_Line3_TxRx(UBYTE value)
{
	SYB_MachineUniqSwitch[UNIQ_SW_A7] &= ~((UBYTE)(LINE3_TX_ONLY | LINE3_RX_ONLY));
	SYB_MachineUniqSwitch[UNIQ_SW_A7] |= (UBYTE)(value << 6);
}


/*************************************************************************
	module		:[外付け第３回線目の送／受信設定の獲得]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_Line3_TxRx(void){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_Line3_TxRx(void)
{
	switch ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A7] & (LINE3_TX_ONLY | LINE3_RX_ONLY))) {
	case LINE3_TX_ONLY:
		return(EXCLUSIVE_TX);
	case LINE3_RX_ONLY:
		return(EXCLUSIVE_RX);
	default:
		return(EXCLUSIVE_TRX);
	}
}


/*************************************************************************
	module		:[外付け第４回線目の送／受信設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far SET_UNI_Line4_TxRx(UBYTE){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
void SET_UNI_Line4_TxRx(UBYTE value)
{
	SYB_MachineUniqSwitch[UNIQ_SW_A8] &= ~((UBYTE)(LINE4_TX_ONLY | LINE4_RX_ONLY));
	SYB_MachineUniqSwitch[UNIQ_SW_A8] |= value;
}


/*************************************************************************
	module		:[外付け第４回線目の送／受信設定の獲得]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_Line4_TxRx(void){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_Line4_TxRx(void)
{
	switch ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A8] & (LINE4_TX_ONLY | LINE4_RX_ONLY))) {
	case LINE4_TX_ONLY:
		return(EXCLUSIVE_TX);
	case LINE4_RX_ONLY:
		return(EXCLUSIVE_RX);
	default:
		return(EXCLUSIVE_TRX);
	}
}


/*************************************************************************
	module		:[外付け第５回線目の送／受信設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far SET_UNI_Line5_TxRx(UBYTE){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
void SET_UNI_Line5_TxRx(UBYTE value)
{
	SYB_MachineUniqSwitch[UNIQ_SW_A8] &= ~((UBYTE)(LINE5_TX_ONLY | LINE5_RX_ONLY));
	SYB_MachineUniqSwitch[UNIQ_SW_A8] |= (UBYTE)(value << 2);
}


/*************************************************************************
	module		:[外付け第５回線目の送／受信設定の獲得]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_Line5_TxRx(void){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_Line5_TxRx(void)
{
	switch ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A8] & (LINE5_TX_ONLY | LINE5_RX_ONLY))) {
	case LINE5_TX_ONLY:
		return(EXCLUSIVE_TX);
	case LINE5_RX_ONLY:
		return(EXCLUSIVE_RX);
	default:
		return(EXCLUSIVE_TRX);
	}
}


/*************************************************************************
	module		:[外付け第６回線目の送／受信設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far SET_UNI_Line6_TxRx(UBYTE){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
void SET_UNI_Line6_TxRx(UBYTE value)
{
	SYB_MachineUniqSwitch[UNIQ_SW_A8] &= ~((UBYTE)(LINE6_TX_ONLY | LINE6_RX_ONLY));
	SYB_MachineUniqSwitch[UNIQ_SW_A8] |= (UBYTE)(value << 4);
}


/*************************************************************************
	module		:[外付け第６回線目の送／受信設定の獲得]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_Line6_TxRx(void){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_Line6_TxRx(void)
{
	switch ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A8] & (LINE6_TX_ONLY | LINE6_RX_ONLY))) {
	case LINE6_TX_ONLY:
		return(EXCLUSIVE_TX);
	case LINE6_RX_ONLY:
		return(EXCLUSIVE_RX);
	default:
		return(EXCLUSIVE_TRX);
	}
}


/*************************************************************************
	module		:[外付け第７回線目の送／受信設定]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far SET_UNI_Line7_TxRx(UBYTE){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
void SET_UNI_Line7_TxRx(UBYTE value)
{
	SYB_MachineUniqSwitch[UNIQ_SW_A8] &= ~((UBYTE)(LINE7_TX_ONLY | LINE7_RX_ONLY));
	SYB_MachineUniqSwitch[UNIQ_SW_A8] |= (UBYTE)(value << 6);
}


/*************************************************************************
	module		:[外付け第７回線目の送／受信設定の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_Line7_TxRx(void){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_Line7_TxRx(void)
{
	switch ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A8] & (LINE7_TX_ONLY | LINE7_RX_ONLY))) {
	case LINE7_TX_ONLY:
		return(EXCLUSIVE_TX);
	case LINE7_RX_ONLY:
		return(EXCLUSIVE_RX);
	default:
		return(EXCLUSIVE_TRX);
	}
}

/*************************************************************************
	module		:[外付け第８回線目の送／受信設定]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far SET_UNI_Line8_TxRx(UBYTE){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
void SET_UNI_Line8_TxRx(UBYTE value)
{
	SYB_MachineUniqSwitch[UNIQ_SW_A9] &= ~((UBYTE)(LINE8_TX_ONLY | LINE8_RX_ONLY));
	SYB_MachineUniqSwitch[UNIQ_SW_A9] |= value;
}


/*************************************************************************
	module		:[外付け第８回線目の送／受信設定の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_Line8_TxRx(void){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_Line8_TxRx(void)
{
	switch ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A9] & (LINE8_TX_ONLY | LINE8_RX_ONLY))) {
	case LINE8_TX_ONLY:
		return(EXCLUSIVE_TX);
	case LINE8_RX_ONLY:
		return(EXCLUSIVE_RX);
	default:
		return(EXCLUSIVE_TRX);
	}
}



/*************************************************************************
	module		:[回線選択優先方向]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_PriorityDirection(void){}]
	date		:[1996/12/02]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_PriorityDirection(void)
{
	if (SYB_MachineUniqSwitch[UNIQ_SW_A9] & LINE_PRIORITY_DIRECTION) {
		return(INWARD_DIRECTION);
	}
	else {
		return(OUTWARD_DIRECTION);
	}
}


/*************************************************************************
	module		:[オプションボードでスキャナー送信をする／しない設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_OptionStxAvailable(void){}]
	date		:[1997/01/17]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_OptionStxAvailable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A9] & OPTION_STX_AVAILABLE));
}


/*************************************************************************
	module		:[属性はＶ．８有効でも使用できる回線がない場合、Ｖ．１７
				  以下の回線にきりかえるかの設定の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_SwitchV17Line(void){}]
	date		:[1997/01/17]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_SwitchV17Line(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A9] & OPTION_SWITCH_V17_LINE));
}


/*************************************************************************
	module		:[ＵＡＥ ＡＲＡＭＣＯ社ＰＩＮマスクする／しない]
	function	:[
		1.
	]
	return		:[
		０：ＰＩＮコードはマスク（＊）する		ＰＩＮの前の＃は必要
		１：ＰＩＮコードはマスク（＊）しない	ＰＩＮの前の＃は不要
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[unsigned char far CHK_UNI_AramcoPinNotMasking(void){}]
	date		:[1997/05/21]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_AramcoPinNotMasking(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A1] & ARAMCO_PIN_MASK));
}


/*************************************************************************
	module		:[内蔵（拡張）回線の送／受信設定の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_Line_EXT_TxRx(void){}]
	date		:[1997/11/04]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_Line_EXT_TxRx(void)
{
	switch ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A9] & (LINE_EXT_TX_ONLY | LINE_EXT_RX_ONLY))) {
	case LINE_EXT_TX_ONLY:
		return(EXCLUSIVE_TX);
	case LINE_EXT_RX_ONLY:
		return(EXCLUSIVE_RX);
	default:
		return(EXCLUSIVE_TRX);
	}
}


/*************************************************************************
	module		:[内蔵（拡張）回線目の送／受信設定]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far SET_UNI_Line_EXT_TxRx(UBYTE){}]
	date		:[1996/11/26]
	author		:[木元修]
*************************************************************************/
void SET_UNI_Line_EXT_TxRx(UBYTE value)
{
	SYB_MachineUniqSwitch[UNIQ_SW_A9] &= ~((UBYTE)(LINE_EXT_TX_ONLY | LINE_EXT_RX_ONLY));
	SYB_MachineUniqSwitch[UNIQ_SW_A9] |= (UBYTE)(value << 5);
}


/*************************************************************************
	module		:[寒冷地PreHeat有効無効]
	function	:[
		1.
	]
	return		:[
		0		無効
		0以外	有効
	]
	common		:[]
	condition	:[]
	comment		:[寒冷地 PreHeat]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/12/26]
	author		:[竹内茂樹]
*************************************************************************/
#if (PRO_PREHEAT == ENABLE)
UBYTE CHK_UNI_PreHeatEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A2] & PREHEAT_ENABLE));
}
#endif


/*************************************************************************
	module		:[寒冷地PreHeat時間]
	function	:[
		1.
	]
	return		:[
		30,60,90,120 (分)
	]
	common		:[]
	condition	:[]
	comment		:[寒冷地 PreHeat]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/12/26]
	author		:[竹内茂樹]
*************************************************************************/
#if (PRO_PREHEAT == ENABLE)
UBYTE CHK_UNI_PreHeatTime(void)
{
	switch (SYB_MachineUniqSwitch[UNIQ_SW_A2] & PREHEAT_TIME) {
	case	PREHEAT_TIME_60:
		return (60);
	case	PREHEAT_TIME_90:
		return (90);
	case	PREHEAT_TIME_120:
		return (120);
	}
	return (30);
}
#endif


/*************************************************************************
	module		:[寒冷地PreHeat開始時刻(時)]
	function	:[
		1.
	]
	return		:[
		0～23 (時)
	]
	common		:[]
	condition	:[]
	comment		:[寒冷地 PreHeat]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/12/26]
	author		:[竹内茂樹]
*************************************************************************/
#if (PRO_PREHEAT == ENABLE)
UBYTE CHK_UNI_PreHeatEndHour(void)
{
	UBYTE hour;

	hour = (UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A2] & PREHEAT_END_HOUR);
	if (hour >= 24) {
		hour = 0;
	}
	return (hour);
}
#endif


/*************************************************************************
	module		:[寒冷地PreHeat開始時刻(分)]
	function	:[
		1.
	]
	return		:[
		0～59 (分)
	]
	common		:[]
	condition	:[]
	comment		:[寒冷地 PreHeat]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/12/26]
	author		:[竹内茂樹]
*************************************************************************/
#if (PRO_PREHEAT == ENABLE)
UBYTE CHK_UNI_PreHeatEndMinute(void)
{
	UBYTE minute;

	minute = (UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A3] & PREHEAT_END_MINUTE);
	if (minute >= 60) {
		minute = 0;
	}
	return (minute);
}
#endif


/*--------------------------------------------------------------------------------
	module		:[ＬＥＤプリンターファン停止温度設定]
	function	:[]
	return		:[
			1～２５５
			]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2001/11/14]
	author		:[O.Kimoto]						*/
#if (defined(POPLAR_H) && defined(JP0)) /* V851 ＦＡＮ制御 By H.Fujimura 2002/07/11 */
UBYTE CHK_InternalTempDoToStopFan(void)
{
	if (!SYB_MachineUniqSwitch[UNIQ_SW_A6]) {
		return((unsigned char)1);
	}
	return((unsigned char)SYB_MachineUniqSwitch[UNIQ_SW_A6]);
}
#endif


#if (PRO_FORVAL_LCR1 == ENABLE) /* By H.Fujimura 2002/07/11 */
/*************************************************************************
	module		:[00500サービス無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[]
	date		:[2002/03/26]
	author		:[西村裕之]
*************************************************************************/
UBYTE CHK_UNI_FORVAL_LCR_Enable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A4] & FORVAL_LCR1_ENABLE));
}
#endif

#if defined(STOCKHM2) /* 本体鳴動のテスト :by SMuratec C.P 2004/09/27 */
/*************************************************************************
	module		:[呼出ブザーONorOFFの取得]
	function	:[]
	return		:[
		TRUE :ON
		FALSE:OFF
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[2001/06/28]
	author		:[髙木 智史]
*************************************************************************/
UBYTE	CHK_CallingBuzzerMode(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A0] & CALLING_BUZZER_ON));
}
#endif

#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
/*************************************************************************
	module		:[PBXダイヤルトーン検出の有効／無効]
	function	:[
		1.
	]
	return		:[
		0     :無効（初期値）
		その他:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_BeforeDialPbxToneDetect(void){}]
	date		:[2004/10/27]
	author		:[田中裕二]
*************************************************************************/
UBYTE CHK_UNI_BeforeDialPbxToneDetect(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_A1] & BEFORE_DIAL_PBX_TONE));
}
#endif

