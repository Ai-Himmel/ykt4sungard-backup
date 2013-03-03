/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_INI.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_ini.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\define\uni_sw.h"
#include "\src\atlanta\define\param.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\country.h"

#include "\src\atlanta\define\ctry_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\uni_pro.h"

#include "\src\memsw\define\mem_sw_a.h" /*1996/04/17 Eguchi*/
#include "\src\memsw\define\mem_sw_b.h" /*1996/09/05 T.Yamaguchi */
#include "\src\memsw\define\mem_sw_c.h"
#include "\src\memsw\define\mem_sw_j.h"
#include "\src\atlanta\define\mntsw_c.h" /*1996/10/08 Eguchi */
#include "\src\atlanta\define\unisw_h.h" /*1998/02/12 M.Kuwahara */

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\rom_tbl.h"
#include "\src\atlanta\ext_v\ini_tbl.h"
#include "\src\atlanta\ext_v\cmn_tbl.h"
#include "\src\atlanta\ext_v\lst_wrd.h"

#if defined(POPLAR_F)
#include "\src\atlanta\ext_v\mlt_data.h"
#endif

#if (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#endif
#if (PRO_PANEL == ANK)
#include "\src\atlanta\opr\ank\define\opr_def.h"	/* ALL_CLEAR */
#include "\src\atlanta\opr\ank\define\opr_pro.h"	/* InitializeCGRAM_Data() */
#include "\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif
#if (PRO_PANEL == KANJI)	/* 追加 By O.Kimoto 1997/06/25 */
#include "\src\atlanta\opr\kanji\ext_v\wording.h"
#endif

#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\sh7043\define\def_semn.h"
#include "\src\atlanta\sh7043\ext_v\extv_sem.h"

#if (PRO_PAT_JOURNAL == ENABLE)
#include "\src\atlanta\ext_v\pat_data.h"
#include "\src\atlanta\ext_v\pat_tbl.h"
#include "\src\atlanta\define\pat_pro.h"
#endif

#if (PRO_PRINT_TYPE == LED)
#include "\src\atlanta\prt\ph3\ext_v\prn_tbl.h"		/* By M.Tachibana 1998/07/02 */
#endif

#if defined(GBR)
#include "\src\atlanta\define\atd_def.h"	/*	MCRY_PAUSE_1ST_DATA	*/
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング機能追加 1996/10/18 Eguchi */
#include	"\src\atlanta\define\syscntpl.h" /* 1996/10/16 Eguchi */
#endif

/* ＦＣＯＤＥ送信でリセットがかかる件 T.Nose 1997/08/07 */
#include "\src\atlanta\ext_v\cmn_data.h"

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
void	MailComAllRamClear(void);

#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* ワープ機能追加	1998/06/15 By M.Kuwahara */
#include	"\src\atlanta\define\syswarp.h"
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/06/15 By M.Kuwahara */
#include	"\src\atlanta\define\sysnd.h"
#include 	"\src\atlanta\define\ncu_pro.h"
#endif

#if (PRO_COM_CODEC_TYPE == SOFTWARE)
#include "\src\atlanta\ext_v\cpu_tbl.h"
#endif

#if defined(US1)		/* orderbythonda1998/11/11 */
#include "\src\atlanta\ext_v\lst_tbl.h"
#endif

#if defined(SATSUKI2)	/* Add by Y.Kano 2003/10/18 */
#include	"\src\atlanta\satsuki2\define\scn_def.h"
#include	"\src\atlanta\prt\iu_therm\define\prt_def.h"	/* Add by Y.kano 2003/12/12 */
#include	"\src\atlanta\satsuki2\define\m_param.h"		/* Add by Y.kano 2004/01/07 */
#endif

#if defined(STOCKHM2)
#include	"\src\atlanta\stockhm2\define\scn_def.h"
#include	"\src\atlanta\prt\lv_therm\define\prt_def.h"	/* Add by Y.kano 2003/12/12 */
#include	"\src\atlanta\stockhm2\define\m_param.h"			/* Add by Y.kano 2004/01/07 */
#endif

#if defined(HINOKI2) || defined(HINOKI3)	/* Add by Y.Kano 2004/01/14 */
#include	"\src\atlanta\hinoki\define\m_param.h"		/* Add by Y.kano 2004/03/01 */
#endif

/*************************************************************************
	module		:[バックアップRAMを初期化するか/しないか]
	function	:[
		1.
	]
	return		:[TRUE :初期化しない(バックアップRAMが有効)
				  FALSE:初期化する(バックアップRAMが無効)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/02/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_CheckBackUpRAM(void)
{
	UWORD	i;

	for (i = 0; i < SYS_BACKUP_RAM_TEST_AREA_MAX; i++) {
		if (SYB_BackupRAM_TestArea[i] != ROM_Revision[i]) {
			return(FALSE);
		}
	}
	if ((SYB_WordingNumber > 0)									/* by M.Tachibana	1997/04/14 */
	 && (SYB_WordingNumber <= CTRY_WordingNumberMax())) {		/* by M.Tachibana	1994/02/14 */
		if (SYB_MachineParameter[COUNTRY_CODE] > 7) {	/* 国別コードが0から7の場合 */
			return(FALSE);
		}
		else {
			return(TRUE);
		}
	}
	else {
		return(FALSE);
	}
}

/*************************************************************************
	module		:[機器パラメータの初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		94/12/12	By j.masuda
		CHNのときはCountryCodeSet()を行わない。
		H8固有のパスを抹消 1996/02/07 Eguchi
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/05]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_InitializeMachineParameter(void)
{
	/*この関数の内容を変更した時は、併せてLST_MSW.Cの変更して下さい。MASUDA*/
	UWORD i;
#if defined(SATSUKI2)	/* ＰＳ１、ＰＢ４の閾値を退避させるバッファ by Y.Kano 2004/03/03 */
	UBYTE ps1_data;
	UBYTE pb4_data;

	ps1_data = SYB_MachineParameter[M_PARA_SW_J6];	/* ＰＳ１閾値の退避 */
	pb4_data = SYB_MachineParameter[M_PARA_SW_J7];	/* ＰＢ４閾値の退避 */

#endif	/* End of defined(SATSUKI2) */

	for (i = 0; i < SYS_MACHINE_PARAMETER_MAX; i ++) {
			SYB_MachineParameter[i] = MachineParameterInitialTable[i];
	}

#if defined(SATSUKI2)	/* 退避させたＰＳ１、ＰＢ４の閾値が閾値として問題ない場合に再セットする。 by Y.Kano 2004/03/03 */
	if (ps1_data != SYB_MachineParameter[M_PARA_SW_J6]) {	/* 退避させたＰＳ１の閾値と異なる */
		if ((ps1_data >= 0x33) && (ps1_data < 0xE7)) {		/* 閾値として問題ない */
			SYB_MachineParameter[M_PARA_SW_J6] = ps1_data;	/* ＰＳ１の閾値の再セット */
		}
	}
	if (pb4_data != SYB_MachineParameter[M_PARA_SW_J7]) {	/* 退避させたＰＢ４の閾値と異なる */
		if ((pb4_data >= 0x33) && (pb4_data < 0xE7)) {		/* 閾値として問題ない */
			SYB_MachineParameter[M_PARA_SW_J7] = pb4_data;	/* ＰＢ４の閾値の再セット */
		}
	}
#endif	/* End of defined(SATSUKI2) */

	SYB_MachineParameter[COUNTRY_CODE] = 0;
#if !defined(CHN) /* 1996/02/07 Eguchi */
	if (HardDIP_SwitchEnable) {
		CountryCodeSet();
	}
#endif

#if (0) /* 削除　1996/09/04　Eguchi */
** 	SYB_MachineParameter[MACHINE_PARA_1] |= CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15];	/* 送出レベル画データ(減衰器設定値) */	/* Add by M.T 94.05.20 */
#endif

#if (PRO_PRINT_TYPE == THERMAL)
	/* 「送出レベルの設定は、基本的には、機器パラメーターＡ：１で行う。
	**   個別に設定が必要な場合はメモリスイッチＢ：１を使う 」というのが一般的なフィールドでの対応らしい。
	** ということで、初期化を行う時に国別設定を機器パラに代入するようにする。
	** By O.Kimoto 1999/03/03
	*/
	SYB_MachineParameter[MACHINE_PARA_1] &= ~ATTENATION_MACHINE_PARA;
	SYB_MachineParameter[MACHINE_PARA_1] |= CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15];	/* 送出レベル画データ(減衰器設定値) */	/* Add by M.T 94.05.20 */
	
#if defined (KEISATSU) /* 警察FAX 05/04/26 石橋正和 */
	SYB_MachineParameter[M_PARA_SW_B3] |= CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15]; /* 警電の場合の画データ送出レベル */
#endif
	
#endif

	SYB_MachineParameter[MACHINE_PARA_2] |= CTRY_DialTable()->LevelDTMF;	/* 送出レベルDTMF(減衰器設定値) */
	
#if defined (KEISATSU) /* 警察FAX 05/04/26 石橋正和 */
	SYB_MachineParameter[M_PARA_SW_B4] |= CTRY_DialTable()->LevelDTMF; /* 警電の場合のDTMF送出レベル */
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.3.2 K.Kawata	*/
	if (CHK_OCA_Specification()) {
		SYB_MachineParameter[31] = 0x08;	/* */
		SYB_MachineParameter[32] = 0xff;	/* */
		SYB_MachineParameter[33] = 0xf6;	/* */
		SYB_MachineParameter[34] = 0xeb;	/* */
		SYB_MachineParameter[36] = 0x00;	/* */
		SYB_MachineParameter[75] = 0x17;	/* */
		SYB_MachineParameter[77] = 0x15;	/* */
		SYB_MachineParameter[79] = 0x13;	/* */
	}
#endif
}

/*************************************************************************
	module		:[メモリスイッチの初期化]
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
	date		:[1994/03/05]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_InitializeMemorySwitch(void)
{
	UWORD i;

	for (i = 0; i < SYS_MEMORY_SWITCH_MAX; i ++) {
		SYS_MemorySwitch[i] = MemorySwitchInitialTable[i];
	}

	/**
	 *	トーンアッテネータの初期値をメモリスイッチに変更したため CountryTableから値を取ってくる処理追加
	 *	SYB_MachineParameterが先に初期化されるので良いはず	96/09/05 By T.Yamaguchi
	 */
	SYS_MemorySwitch[11] |= ( ATTENATION & (CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15]) );	/* 送出レベル画データ(減衰器設定値) */	/* Add by T.Yamaguchi 96/09/05 */
#if defined (KEISATSU) /* 警察FAX 05/04/27 石橋正和 */
	/* 送出レベル画データ(警電回線) */
	SYS_MemorySwitch[MEMORY_SW_B4] |= ( ATTENATION & (CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15]) );
#endif
	
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.3.3 K.Kawata	*/
	if (CHK_OCA_Specification()) {
		SYS_MemorySwitch[15] = 0x06;	/*1999.3.3 K.Kawata */
	}
#endif
}

/*************************************************************************
	module		:[親展受信ボックスの初期化]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
void	CMN_ClearMailBox(UWORD i)
{
	SYB_MailBox[i].Status = SYS_MAILBOX_NO_SET;
}

/*************************************************************************
	module		:[短縮ダイアルの初期化]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
void	CMN_ClearSpeedDial(UWORD i)
{
	SYB_SpeedDial[i].Dial[0] = 0xFF;
#if defined (KEISATSU) /* 警察属性 05/04/14 石橋正和 */
	SYB_SpeedDial[i].Keisatsu = 0;
#else
	SYB_SpeedDial[i].SubDialPosition = 0xFF;
#endif
	SYB_SpeedJunkDial[i] = 0xFFFF;	/* 1997/10/22 T.Yamaguchi */

/* 電話帳用読み仮名用エリアの初期化追加
** リモートの方で、このエリアが初期化不良の場合、エラーが発生します。
** また、未使用領域は未使用とわかっていても念のために初期化だけはしておきましょう！
** By O.Kimoto 1999/02/17
*/
	SYB_SpeedDial[i].NamePronunciation[0] = '\0';	/* カタカナ半角 */
}

/*************************************************************************
	module		:[第２短縮ダイアルの初期化]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
#if (0)
** #if (PRO_2ND_SPEED == ENABLE)
** void	CMN_Clear2ndSpeedDial(UWORD i)
** {
** 	SYB_2ndSpeedDial[i].Dial[0] = 0xFF;
** }
** #endif
#endif

/*************************************************************************
	module		:[ワンタッチダイアル初期化]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
#if (0) /* 1995/12/02　 Eguchi */
** void	CMN_ClearOnetouchDial(unsigned int i)
** {
** 	SYB_OnetouchDial[i].Status = SYS_NO_STORED;
** }
#endif
void	CMN_ClearOnetouchDial(UWORD i)
{
	SYB_OnetouchDial[i].Dial[0] = 0xFF;
#if defined (KEISATSU) /* 警察属性 05/04/14 石橋正和 */
	SYB_OnetouchDial[i].Keisatsu = 0;
#else
	SYB_OnetouchDial[i].SubDialPosition = 0xFF; /* 1995/12/14 Eguchi*/
#endif
	SYB_OnetouchJunkDial[i] = 0xFFFF;	/* 1997/10/22 T.Yamaguchi */

/* 電話帳用読み仮名用エリアの初期化追加
** リモートの方で、このエリアが初期化不良の場合、エラーが発生します。
** また、未使用領域は未使用とわかっていても念のために初期化だけはしておきましょう！
** By O.Kimoto 1999/02/17
*/
	SYB_OnetouchDial[i].NamePronunciation[0] = '\0';	/* カタカナ半角 */
}


/*************************************************************************
	module		:[第２ワンタッチダイアル初期化]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
#if (0)
** #if (PRO_2ND_ONETOUCH == ENABLE)
** void	CMN_Clear2ndOnetouchDial(UWORD i)
** {
** 	SYB_2ndOnetouchDial[i].Dial[0] = 0xFF;
** }
** #endif
#endif

/*************************************************************************
	module		:[プログラムワンタッチダイアルクリア]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
void	CMN_ClearProgramOnetouch(UWORD i)
{
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/10/08 By M.Kuwahara */
	SYB_ProgramOnetouch[i].Item = SYS_PROGRAM_EMPTY;
	SYB_ProgramOnetouch[i].EntryData.Command.Status = SYS_CMD_EMPTY;	/* 1998/10/13 By M.Kuwahara */
#else
	SYB_ProgramOnetouch[i].Status = SYS_CMD_EMPTY;
#endif
#if (PRO_F_CODE == ENABLE)
	SYB_FcodeNumberPDataBuffer[i].SYS_SubAddressNumber[0] = 0xFF;
	SYB_FcodeNumberPDataBuffer[i].SYS_PassWordNumber[0] = 0xFF;
#endif
}

#if (PRO_F_CODE == ENABLE)
/*************************************************************************
	module		:[ＦコードＢＯＸクリア]
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
	date		:[1997/03/11]
	author		:[山口]
*************************************************************************/
void	CMN_ClearFcodeBox(UWORD i)
{
	SYB_SubAddressBoxTable[i].Status = SUB_ADDRESS_BOX_EMPTY;
	SYB_SubAddressBoxTable[i].BoxName[0] = NULL;
	SYB_SubAddressBoxTable[i].SubAddress[0] = NULL;
	SYB_SubAddressBoxTable[i].PassWord[0] = NULL;
	SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
	SYB_SubAddressBoxTable[i].MessageStatus = SYS_SUB_ADDRESS_BOX_MSG_EMPTY;
	SYB_SubAddressBoxTable[i].RemoteName[0] = NULL;
	SYB_SubAddressBoxTable[i].PassCode = 0;
	SYB_SubAddressBoxTable[i].ErasedTime = 0xFFFFFFFF;
	SYB_SubAddressBoxTable[i].Option = 0;
	SYB_SubAddressBoxTable[i].HoldTime = 0;
	SYB_SubAddressBoxTable[i].ScnStoringNo = 0;
	SYB_SubAddressBoxTable[i].RxStoringNo = 0;
	SYB_SubAddressBoxTable[i].StoredDocBit = 0;
}
#endif

/*************************************************************************
	module		:[ジャンクダイヤルのクリア]
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
	date		:[1997/05/12]
	author		:[山口]
*************************************************************************/
void	CMN_ClearJunkDial(UWORD i)
{
	SYB_JunkMailProtectDialBuffer[i][0] = 0xff;
}

/*************************************************************************
	module		:[転送ダイアル初期化]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
#if (PRO_SUB_DIAL == ENABLE)
void	CMN_ClearSubDial(UWORD i)
{
	SYB_SubDial[i][0] = 0xFF;
}
#endif

/*************************************************************************
	module		:[部門管理ファイルのオールクリア]
	function	:[
		1.料金管理をする場合の部門管理ファイルのクリア
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
#if (PRO_COST == ENABLE)
void	CMN_AllClearDepartFile(void)
{
	UBYTE i;

	for (i = 0; i < SYS_DEPART_MAX; i ++) {
		CMN_ClearDepartFile(i);
	}
}
#endif

/*************************************************************************
	module		:[部門管理ファイルのクリア]
	function	:[
		1.料金管理をする場合の部門管理ファイルのクリア
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
#if (PRO_COST == ENABLE)
void	CMN_ClearDepartFile(UWORD i)
{
	SYB_DepartFile[i].Code = 0xffff;
}
#endif

/*************************************************************************
	module		:[簡易料金管理リストのオールクリア]
	function	:[
		1.料金管理をする場合の簡易料金管理リストのクリア
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/29]
	author		:[本多智幸]
*************************************************************************/
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト By t.honda 1997/11/29 */
void	CMN_AllClearDepartManageFile(void)
{
	UBYTE i;

	for (i = 0; i < SYS_DEPART_MAX; i ++) {
		CMN_ClearDepartManageFile(i);
	}
}
#endif

/*************************************************************************
	module		:[簡易料金管理リストのクリア]
	function	:[
		1.料金管理をする場合の簡易料金管理リストのクリア
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/29]
	author		:[本多智幸]
*************************************************************************/
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト By thonda 1997/11/29 */
void	CMN_ClearDepartManageFile(UWORD i)
{
	SYB_DepartManageTimeFile[i].Timer = 0x00000000;
	SYB_DepartManageTimeFile[i].Page  = 0x0000;
}
#endif

/*************************************************************************
	module		:[料金表の料金と送信枚数をクリアする。]
	function	:[
		1.料金表をプリント後、料金、送信枚数をクリアする。
		2.料金結果リストプリント要求フラグをOFFする。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/09/14]
	author		:[鈴木郁二]
*************************************************************************/
#if (PRO_COST == ENABLE)
void	CMN_ClearCostData(void)
{
	UBYTE i;

	for (i = 0; i < SYS_DEPART_MAX; i ++) {
		SYB_DepartFile[i].Cost = 0;
		SYB_DepartFile[i].TxRxPage = 0;
	}
	SYS_DepartmentListRequest = 0;
}

void	CMN_ClearCostTable(UWORD i)
{
	SYB_CostTable[i].Daytime = 0;
	SYB_CostTable[i].Night = 0;
	SYB_CostTable[i].Midnight = 0;
}

void	CMN_ClearNTT_AccessFile(UWORD i) { /** 石橋正和 94/07/11 */
	SYB_NTT_AccessFile[i].Number[0] = 0xFF;
}

#endif



/*************************************************************************
	module		:[一括送信ファイルのクリア]
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
	date		:[1995/12/04]
	author		:[江口]
*************************************************************************/
#if (PRO_BATCH_TX == ENABLE)
void	CMN_ClearBatchTxFile(UWORD i)
{
	SYB_BatchTxFile[i].Status = SYS_CMD_EMPTY;
	SYB_BatchTxFile[i].DialNumber[0].Item = SYS_EMPTY_DIAL;
}
#endif


/*************************************************************************
	module		:[カバーページメッセージの初期化]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
void	CMN_ClearCoverPageMessage(void)
{
	SYB_CoverPageMessage[0] = 0x00;
}


/*************************************************************************
	module		:[自機ＦＡＸ番号の初期化]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
void	CMN_ClearID_Buffer(void)
{

/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
	SYB_ID_Buffer[0][0] = 0x00;
	SYB_ID_Buffer[1][0] = 0x00;
#else
	SYB_ID_Buffer[0] = 0x00;
#endif

}

/*************************************************************************
	module		:[発信元名の初期化]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
void	CMN_ClearTTI_Buffer(void)
{
 /* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
	SYB_TTI_Buffer[0][0] = 0x00;
	SYB_TTI_Buffer[1][0] = 0x00;
 #else
	SYB_TTI_Buffer[0] = 0x00;
 #endif

}


#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
void	CMN_ClearTTI_ID_Buffer(void)
{

 /* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
	SYB_TTI_ID_Buffer[0][0] = 0x00;
	SYB_TTI_ID_Buffer[1][0] = 0x00;
 #else
	SYB_TTI_ID_Buffer[0] = 0x00;
 #endif

}
#endif


/*************************************************************************
	module		:[ダイアルインデータの初期化]
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
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
#if (PRO_DIALIN == ENABLE)
void	CMN_ClearDialin(void)
{
	UWORD i;

	for (i = 0; i < SYS_DIALIN_MAX - 1; i ++) {
		SYB_Dialin.FaxNumber[i] = '*';
		SYB_Dialin.Tel1Number[i] = '*';
		SYB_Dialin.Tel2Number[i] = '*';
	}
	SYB_Dialin.FaxNumber[SYS_DIALIN_MAX - 1] = 0x00;
	SYB_Dialin.Tel1Number[SYS_DIALIN_MAX - 1] = 0x00;
	SYB_Dialin.Tel2Number[SYS_DIALIN_MAX - 1] = 0x00;
	SYB_Dialin.BellTime = 30;
}
#endif

/*************************************************************************
	module		:[ライフモニターのクリア]
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
	date		:[1996/06/20]
	author		:[江口]
*************************************************************************/
void	CMN_ClearLifeMonitorData(void)
{
	SYB_LifeMonitor.ScanCount = 0;		/**	読取り枚数クリア */
	SYB_LifeMonitor.TransmitCount = 0;	/**	送信枚数クリア	*/
	SYB_LifeMonitor.PrintCount = 0;		/**	印字枚数クリア	*/
	SYB_LifeMonitor.PrintCountCopy = 0;		/**	コピー印字枚数クリア	*/
	SYB_LifeMonitor.PrintCountReceive = 0;	/**	受信印字枚数クリア	*/
	SYB_LifeMonitor.PrintCountPC = 0;		/**	ＰＣ印字枚数クリア	*/
/*	SYB_LifeMonitor.ReceiveCount = 0; '95,11,17 Ｒのため削除 1995/12/04*/

	/* 追加　1996/06/20　Eguchi */
	SYB_LifeMonitor.DrumReplaceCount = 0; /** ドラム交換回数クリア */
	SYB_LifeMonitor.DrumLifeCount = 0; /** ドラム寿命カウンター（１個のドラムにおけるプリント枚数）クリア 1996/06/24 Eguchi */
	SYS_MachineStatus[SYS_WARNING_STATUS] &=~SYS_WARNING_DRUM_REPLACE; /** ドラム寿命ステータスクリア */
}

#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[プリンタライフモニターのクリア]
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
	date		:[1997/04/19]
	author		:[橘正樹]
*************************************************************************/
void	CMN_ClearPrinterLifeMonitorData(void)
{
	UBYTE	i;

	SYB_PrinterLifeMonitor.TotalPageCount = 0;
	SYB_PrinterLifeMonitor.TransferLifeCount = 0;
	SYB_PrinterLifeMonitor.FuserLifeCount = 0;
	SYB_PrinterLifeMonitor.DrumLifeCount = 0;
	SYB_PrinterLifeMonitor.TonerLifeCount = 0;
	SYB_PrinterLifeMonitor.TransferReplaceCount = 0;
	SYB_PrinterLifeMonitor.FuserReplaceCount = 0;
	SYB_PrinterLifeMonitor.DrumReplaceCount = 0;
	SYB_PrinterLifeMonitor.TonerReplaceCount = 0;
	SYB_PrinterLifeMonitor.Jam1Cassette1Count = 0;
	SYB_PrinterLifeMonitor.Jam1Cassette2Count = 0;
	SYB_PrinterLifeMonitor.Jam1Cassette3Count = 0;
	SYB_PrinterLifeMonitor.Jam1ManualCount = 0;
	SYB_PrinterLifeMonitor.Jam2Count = 0;
	SYB_PrinterLifeMonitor.Jam3Count = 0;
	SYB_PrinterLifeMonitor.A6_TotalCount = 0;
	SYB_PrinterLifeMonitor.A5_TotalCount = 0;
	SYB_PrinterLifeMonitor.A5R_TotalCount = 0;
	SYB_PrinterLifeMonitor.A4_TotalCount = 0;
	SYB_PrinterLifeMonitor.B5_TotalCount = 0;
	SYB_PrinterLifeMonitor.B5R_TotalCount = 0;
	SYB_PrinterLifeMonitor.B4_TotalCount = 0;
	SYB_PrinterLifeMonitor.LT_TotalCount = 0;
	SYB_PrinterLifeMonitor.LG_TotalCount = 0;
	SYB_PrinterLifeMonitor.F4_TotalCount = 0;
	SYB_PrinterLifeMonitor.Other1TotalCount = 0;
	SYB_PrinterLifeMonitor.Other2TotalCount = 0;
	SYB_PrinterLifeMonitor.ManualTotalCount = 0;
	SYB_PrinterLifeMonitor.A6_PreCount = 0;
	SYB_PrinterLifeMonitor.A5_PreCount = 0;
	SYB_PrinterLifeMonitor.A5R_PreCount = 0;
	SYB_PrinterLifeMonitor.B5_PreCount = 0;
	SYB_PrinterLifeMonitor.B5R_PreCount = 0;
	SYB_PrinterLifeMonitor.B4_PreCount = 0;
	SYB_PrinterLifeMonitor.LT_PreCount = 0;
	SYB_PrinterLifeMonitor.LG_PreCount = 0;
	SYB_PrinterLifeMonitor.F4_PreCount = 0;
	SYB_PrinterLifeMonitor.TonerDataCount = 0;
	for (i = 0; i < SYS_LIFE_TONER_DATA_MAX; i++) {
		SYB_PrinterLifeMonitor.TonerData[i] = 0xff;
	}
	SYB_PrinterLifeMonitor.ErrorStatus = 0;
	SYB_PrinterLifeMonitor.OrderListRequest = 1;
	SYB_PrinterLifeMonitor.TonerFewLevelCount = 0;
	SYB_PrinterLifeMonitor.TonerSupplyLevelCount = 0;

	/* Add By M.Tachibana 1998/03/02 */
	SYB_PrinterLifeMonitor.HLTR_PreCount = 0;
	SYB_PrinterLifeMonitor.EXE_PreCount = 0;
	SYB_PrinterLifeMonitor.DL_PreCount = 0;
	SYB_PrinterLifeMonitor.CM10_PreCount = 0;
	SYB_PrinterLifeMonitor.MNC_PreCount = 0;
	SYB_PrinterLifeMonitor.Other6PreCount = 0;
	SYB_PrinterLifeMonitor.Other7PreCount = 0;
	SYB_PrinterLifeMonitor.Other8PreCount = 0;
	SYB_PrinterLifeMonitor.reserve1 = 0;
	SYB_PrinterLifeMonitor.reserve4 = 0;
	SYB_PrinterLifeMonitor.reserve5 = 0;
	SYB_PrinterLifeMonitor.reserve6 = 0;
	SYB_PrinterLifeMonitor.reserve7 = 0;
	SYB_PrinterLifeMonitor.reserve8 = 0;
	SYB_PrinterLifeMonitor.reserve9 = 0;
	SYB_PrinterLifeMonitor.reserve10 = 0;
	SYB_PrinterLifeMonitor.reserve11 = 0;
	SYB_PrinterLifeMonitor.reserve12 = 0;
	SYB_PrinterLifeMonitor.reserve13 = 0;

}
#endif

/*************************************************************************
	module		:[通信エラーモニターのクリア]
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
	date		:[1997/06/23]
	author		:[橘正樹]
*************************************************************************/
void	CMN_ClearFaxComErrorMonitorData(void)
{
	UBYTE	i;
	UBYTE	j;

	for (j = 0; j < SYS_FAXCOM_ERROR_LINE_MAX; j++) {
		for (i = 0; i < SYS_FAXCOM_ERROR_MONITOR_MAX; i++) {
			SYB_FaxComErrorMonitor[j][i].MML_Count = 0;
			SYB_FaxComErrorMonitor[j][i].OtherCount = 0;
		}
	}
}

/*************************************************************************
	module		:[ジャーナルデータクリア]
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
	date		:[1996/06/20]
	author		:[江口]
*************************************************************************/
void	CMN_ClearJournalData(void)
{
	UBYTE i;

	SYB_TxTotalCount = 1; /** 送信回数初期化*/
	SYB_RxTotalCount = 1; /** 受信回数初期化*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
	SYB_TxTotalCountExt = 1; /** 拡張回線用、送信回数初期化*/
	SYB_RxTotalCountExt = 1; /** 拡張回線用、受信回数初期化*/
#endif

	/* オプションボード送信ジャーナルナンバー */
	for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		SYB_OptionJournalTxTotalCount[i] = 1;
		SYB_OptionJournalRxTotalCount[i] = 1;
	}

#if (PRO_JOURNAL == UNITED) /*一体型*/
	for (i = 0; i < SYS_JOURNAL_MAX; i ++) {
		SYB_JournalFile[i].Number = 0xffff;	/* -1 -> 0xffff By M.Tachibana 1997/05/10 */
		SYB_JournalFile[i].Option = 0;
		SYB_JournalFile[i].RemoteID_TTI[0] = 0x00;	/* NULL */
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/15 */
		SYB_JournalFile[i].KeisatsuID[0] = 0x00;	/* NULL */
#endif /* defined (KEISATSU) */
		SYB_JournalFile[i].StackNumber = 0xFF;
	}
	SYB_JournalPoint = 0;				/** 通信管理記録の記録位置のｸﾘｱ */
	SYB_TxJournalNumber = 0;
	SYB_RxJournalNumber = 0;
#endif
#if (PRO_JOURNAL == SEPARATE)/* 分離型 */
	for (i = 0; i < SYS_JOURNAL_MAX; i ++) {
		SYB_TxJournalFile[i].Number = -1;
		SYB_TxJournalFile[i].Option = 0;
		SYB_RxJournalFile[i].Number = -1;
		SYB_RxJournalFile[i].Option = 0;
		SYB_JournalFile[i].StackNumber = 0xFF;
	}
	SYB_TxJournalPoint = 0;				/** 通信管理記録の記録位置のｸﾘｱ */
	SYB_RxJournalPoint = 0;				/** 通信管理記録の記録位置のｸﾘｱ */
	SYB_TxJournalNumber = 0;
	SYB_RxJournalNumber = 0;
#endif
	SYB_AutoJournalCounter = 0;			/** 通信管理記録自動ﾌﾟﾘﾝﾄ･ｶｳﾝﾀ-のｸﾘｱ */
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/27 */
	SYB_DailyReportPrintPos = 0;		/* 通信管理記録日報プリント 前回印字データ配列番号のクリア */
#endif

	/*--------------------------*	1994/10/04 M.Mannnami
	 * 通信管理記録(ＭＨデータ) *
	 *--------------------------*/
#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_JournalTopPtr = 0;			/** 通信管理記録先頭位置を初期化 */
	/*PAT_JournalNextTopPtr = 0;	@** 通信管理記録次回先頭位置を初期化 */
	PAT_JournalPrintReq = FALSE;	/** 自動印字要求識別子を初期化 */
	PAT_JournalCDC = FALSE;			/** ジャーナル印字処理中識別子を初期化 */
	PAT_CurAddr = 0;				/** 現在格納中番地を初期化 */
	PAT_CurBit = 0;					/**			  ビット位置を初期化 */
	PAT_NoOfAfterPrintReq = 0;		/** 自動印字要求後 格納件数を初期化 */

	PAT_JILimitPtr = PAT_GetLimitPtr( 0L );/** 印字要求位置を設定する */
	for( i = 0; i < PAT_JournalTableMax; i++ ) {/** 管理テーブルを初期化 */
		PAT_ClrJournalPtrFile( i );		/** 不要な管理データを抹消する */
	}
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/02/19 */
	CMN_ND_EraseAllHistory();	/* ナンバーディスプレイ着信履歴消去 */
#endif

	/*	ジャーナルデータクリア時、Ｔ３０モニタがクリアされない場合があり、
	**	その時点でＴ３０モニタをプリントすると明細部分が不定になります。
	**	よって、必ず一緒にクリアされるように、CMN_InitializeAllBackUpRAM()から持って来ました。
	**	By H.Fujimura 1999/04/16 */

	/*-----------*
	 * T30モニタ *
	 *-----------*/
	SYB_T30Monitor.JournalType = SYS_T30_EMPTY;
#if defined(POPLAR_F)
	for (i = 0; i < SYS_JOURNAL_MAX; i++) {
		SYB_T30MonitorDRAM_Status[i] = 0;
	}
#else
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/14 */
	if (CHK_UNI_MultiT30Monitor()) {
		for (i = 0; i < SYS_JOURNAL_MAX; i++) {
			(SYS_T30Monitor + i)->JournalType = SYS_T30_EMPTY;
		}
	}
 #endif
#endif

}

/*************************************************************************
	module		:[暗号化用キーデータ初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/06/17]
	author		:[鈴木郁ニ]
*************************************************************************/
void CMN_ClearCipherKey(UWORD i)
{
	SYB_KeyBookData.SYB_KeyData[i].Key[0] = NULL;
	SYB_KeyBookData.SYB_KeyData[i].KeyClue[0] = NULL;
	SYB_KeyBookData.SYB_KeyData[i].KeyName[0] = NULL;
	SYB_KeyBookData.SYB_KeyData[i].KeyPassCode = 0;
}

/*************************************************************************
	module		:[暗号化用ボックスデータ初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/06/17]
	author		:[鈴木郁ニ]
*************************************************************************/
void CMN_ClearCipherBox(UWORD i)
{
	SYB_CipherBox[i].Status = SYS_CIPHERBOX_NO;
}

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* 1996/06/27 H,Yagi *//* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
/*************************************************************************
	module		:[マーキュリーダイアルの初期化]
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
	date		:[1995/12/02]
	author		:[江口]
	1996/06/27 H,Yagi
*************************************************************************/
void	CMN_MercuryDial(UWORD i)
{
	SYB_MercuryDialBuffer[i] = 0xFF;
}
#endif

/*************************************************************************
	module		:[消耗品発注データの初期化]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/01]
	author		:[渡辺一章]
*************************************************************************/
void CMN_ClearConsumerOrderData(void)
{
#if defined(US1)	/* orderbythonda1998/11/11 */
	SYB_ConsumerOrder.ToCustomerCode[0]   = NULL;	/* 発注先 得意先コード	*/
/*	SYB_ConsumerOrder.ToCompany[0]        = NULL;	*//* 発注先 社名			*/
	SYB_ConsumerOrder.FromCustomerCode[0] = NULL;	/* 発注元 得意先コード	*/
	SYB_ConsumerOrder.FromCompany[0]      = NULL;	/* 発注元 社名			*/
	SYB_ConsumerOrder.FromSection[0]      = NULL;	/* 発注元 部課名		*/
	SYB_ConsumerOrder.FromTelNumber[0]    = NULL;	/* 発注元 ＴＥＬ		*/
	SYB_ConsumerOrder.SerialNumber[0]     = NULL;	/* シリアル番号			*/
	SYB_ConsumerOrder.InstallDate         = NULL;	/* 設定日				*/
	SYB_ConsumerOrderFromSection2[0]      = NULL;	/* 発注元 部課名２		*//* addedbythonda1998/05/21 */
	CMN_StringCopyNULL( SYB_ConsumerOrder.ToCompany, DistributorName );	/* 発注先 社名			*/
	CMN_StringCopyNULL( SYB_ToCompanyFaxNumber, ToCompanyFaxNumber );	/* 発注先Ｆａｘ			*/
	CMN_StringCopyNULL( SYB_ToCompanyTelNumber, ToCompanyTelNumber );	/* 発注先Ｔｅｌ			*/

#elif (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
	SYB_ConsumerOrder.ToCustomerCode[0]   = NULL;	/* 発注先 得意先コード	*/
	SYB_ConsumerOrder.ToCompany[0]        = NULL;	/* 発注先 社名			*/
	SYB_ConsumerOrder.FromCustomerCode[0] = NULL;	/* 発注元 得意先コード	*/
	SYB_ConsumerOrder.FromCompany[0]      = NULL;	/* 発注元 社名			*/
	SYB_ConsumerOrder.FromSection[0]      = NULL;	/* 発注元 部課名		*/
	SYB_ConsumerOrder.FromTelNumber[0]    = NULL;	/* 発注元 ＴＥＬ		*/
	SYB_ConsumerOrder.SerialNumber[0]     = NULL;	/* シリアル番号			*/
	SYB_ConsumerOrder.InstallDate         = NULL;	/* 設定日				*/
	SYB_ConsumerOrderFromSection2[0]      = NULL;	/* 発注元 部課名２		*//* addedbythonda1998/05/21 */

#else
	SYB_ConsumerOrder.ToCustomerCode[0]   = NULL;	/* 発注先 得意先コード	*/
	SYB_ConsumerOrder.ToCompany[0]        = NULL;	/* 発注先 社名			*/
	SYB_ConsumerOrder.FromCustomerCode[0] = NULL;	/* 発注元 得意先コード	*/
	SYB_ConsumerOrder.FromCompany[0]      = NULL;	/* 発注元 社名			*/
	SYB_ConsumerOrder.FromSection[0]      = NULL;	/* 発注元 部課名		*/
	SYB_ConsumerOrder.FromTelNumber[0]    = NULL;	/* 発注元 ＴＥＬ		*/
	SYB_ConsumerOrder.SerialNumber[0]     = NULL;	/* シリアル番号			*/
	SYB_ConsumerOrder.InstallDate         = NULL;	/* 設定日				*/
#endif
}

/*************************************************************************
	module		:[暗号化送信用キーデータ（ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ登録用）の初期化]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/19]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_CIPHER == ENABLE)
void CMN_ClearCipherPData(UBYTE prg_no)
{
	SYB_CipherPData[prg_no].SetKeyMode = 0xFF;		/* キー入力の設定方法	*/
	SYB_CipherPData[prg_no].KeyNumber = 0xFF;		/* キー番号				*/
	SYB_CipherPData[prg_no].Key[0] = NULL;			/* 暗号化キー			*/
	SYB_CipherPData[prg_no].KeyClue[0] = NULL;		/* 暗号化キーのヒント	*/
	SYB_CipherPData[prg_no].KeyExtensionOn = TRUE;	/* 拡張キー設定			*/
}
#endif

/*************************************************************************
	module		:[カントリーコードセット]
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
	date		:[1995/12/20]
	author		:[]
*************************************************************************/
void	CountryCodeSet(void)
{
	UBYTE status;

	/* 国別コードを設定 */
#if defined (SATSUKI2) || defined(STOCKHM2) /* このディップスイッチは存在しません。O.Oshima 2003/06/25 */
	status = 0;
#else
	status = DSW();
#endif
/*	status = (UBYTE)(status >> 4); */
#if !defined (SATSUKI2) && !defined(STOCKHM2) /* このディップスイッチは存在しません。O.Oshima 2003/06/25 */
	status = (UBYTE)((status ^ (IO_BIT_DSW0 | IO_BIT_DSW1 | IO_BIT_DSW2)) & (IO_BIT_DSW0 | IO_BIT_DSW1 | IO_BIT_DSW2));
#endif
	SYB_MachineParameter[COUNTRY_CODE] = status;

#if (0)	/* 変更必要？？ */
	/* ダイヤルパルスタイプの設定 */
	/*status = inp(SENSOR2_PORT); 共通関数作成 1996/02/07 Eguchi */
	status = DSW();
	if (status & IO_BIT_DSW7) {
		SYS_MemorySwitch[MEMORY_SW_A0] &= ~DIAL_SWE_TYPE;
		SYS_MemorySwitch[MEMORY_SW_A0] |= DIAL_NZL_TYPE;
	}
#endif
}



/*************************************************************************
	module		:[機種固有スイッチの初期化]
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
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void	CMN_InitializeUniqSwitch(void)
{
	UWORD i;
#if (PRO_COM_CODEC_TYPE == SOFTWARE)
	UBYTE old_cpu_ver[2];
#endif
	for (i = 0; i < SYS_MEMORY_SWITCH_MAX; i ++) {

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 2003/09/20 H.Yoshikawa */
		if (i ==  UNIQ_SW_J5) {
			if (CHK_UNI_OCA_ForSAKAKI2()) {
				SYB_MachineUniqSwitch[i] = (UniqSwitchInitialTable[i] | OCA_FOR_SAKAKI2);
				continue;	/* 2003/11/28 H.Yoshikawa */
			}
/*			continue; 2003/11/28 H.Yoshikawa */
		}
#endif
		SYB_MachineUniqSwitch[i] = UniqSwitchInitialTable[i];
	}
	SYB_MachineUniqSwitch[UNIQ_SW_G1] = ((UBYTE)(((struct DialParameters_t *)CTRY_DialTable())->FlashTime)); /* 1996/07/08 By N.Sakamoto FlashKeyOnOffTime */

#if (PRO_MULTI_LINE == ENABLE)	/* Change PRO_MULTI_TTI to PRO_MULTI_LINE by O.Kimoto 1999/03/10 */
	/* 下記ユニークスイッチＤ：４，Ｄ：５はオプションモデム用の設定値です。
	** ＳＡＫＡＫＩ／ＨＩＮＯＫＩ等のオプション対応がなく、「ＰＲＯ＿ＭＵＬＴＩ＿ＬＩＮＥ」がＤｉｓａｂｌｅ
	** の機種では、固有スイッチをプリントした時に初期値と設定値が合わないということで、ＣＳサービスから
	** クレームがきました。
	** よって、関係無い設定はしないようにします。
	** By O.Kimoto 1999/03/02
	*/
	/*--------------------------------------------*/
	/* オプションモデムボード送出レベル UNI_SW D4 */
	/*--------------------------------------------*/
	SYB_MachineUniqSwitch[34] &= 0xF0;
	SYB_MachineUniqSwitch[34] |= CountryOptionTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_OPTION__SW_0];

	/*----------------------------------------------------*/
	/* オプションモデムボードＤＴＭＦ送出レベル UNI_SW D5 */
	/*----------------------------------------------------*/
	SYB_MachineUniqSwitch[35] &= 0xF0;
	SYB_MachineUniqSwitch[35] |= CountryOptionTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_OPTION__SW_1];
#endif

#if (PRO_PRINT_TYPE == LED)
	/*--------------------------------------------------------------------
	** ドラムのメーカーによってＦＢ関数が異なる
	** 機種固有ＳＷ Ｆ６－７   ０：キャノン製（従来品）  １：富士電機製
	** By M.Tachibana 1998/07/02
	*/
	for (i = 0; PRN_NewDrumModelTable[i][0] != '\0'; i++) {
		if (CMN_StringCompare(&ROM_Revision[0], &PRN_NewDrumModelTable[i][0], 5) == STRCMP_EQUAL) {
			SYB_MachineUniqSwitch[UNIQ_SW_F6] |= NEW_DRUM_CONTROL;	/* 富士電機製 */
			break;
		}
	}
#endif

#if (PRO_COM_CODEC_TYPE == SOFTWARE)
	/*--------------------------------------------------------------------
	** ＣＰＵがＢ０Ｂ０Ｂ０バージョンならＧ３受信もＭＭＲで蓄積可
	** 機種固有ＳＷ Ｃ９－０   ０：ＭＭＲ蓄積  １：ＭＲ蓄積
	** By Y.Suzuki 1998/07/23
	*/
	if (CPU_Revision[10] != 'A') {
		SYB_MachineUniqSwitch[UNIQ_SW_C9] &= ~G3RX_MR_STORE;
	}
	/*--------------------------------------------------------------------
	** ＣＰＵがＣ０Ｃ０Ｃ０バージョンならA3/B4->A4縮小画像を中央寄せにする。
	** 機種固有ＳＷ Ｃ９－１ ０：左寄せ １：中央寄せ
	** By Y.Suzuki 1998/10/06
	*/
	if (CPU_Revision[10] < 'C') {/*バージョンC0C0C0以上なら*/
		SYB_MachineUniqSwitch[UNIQ_SW_C9] &= ~REDUCED_PIX_MID;
	}
 #if (PRO_KEYPANEL == PANEL_POPLAR_L)
	/** ROMﾊﾞｰｼﾞｮﾝが L400/M2610 UNISW C9-1 をOFFにするBy Y.Suzuki 1999/01/25 */
	/**
	CONST UBYTE	PRN_NewDrumModelTable[][6] = [
	"K7312",	 V930 コニカ
	"OO120",	 V930 沖
	"L400 ",	 V730 ＮＴＴ
	"M2610",	 V730 ミノルタ
	"TC751",	 V730 ＦＸ
	"SF790",	 V730 三洋
	"\0"		 ターミネイト
	];
	**/
	if( CMN_StringCompare( ROM_Revision, &PRN_NewDrumModelTable[2][0], 5 ) == STRCMP_EQUAL ){
		SYB_MachineUniqSwitch[UNIQ_SW_C9] &= ~REDUCED_PIX_MID;
	}
	if( CMN_StringCompare( ROM_Revision, &PRN_NewDrumModelTable[3][0], 5 ) == STRCMP_EQUAL ){
		SYB_MachineUniqSwitch[UNIQ_SW_C9] &= ~REDUCED_PIX_MID;
	}
 #endif
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.3.2 K.Kawata	*/
	if (CHK_OCA_Specification()) {
		SYB_MachineUniqSwitch[UNIQ_SW_C2] &= ~JBIG_RX_ENABLE;
		SYB_MachineUniqSwitch[UNIQ_SW_C3] = 0xf0;	/* */
	}
#endif

#if (PRO_OP_SPPED_4_FIGURE == ENABLE)	/* 2002/02/13 H.Yoshikawa */
	if (CHK_AIFUL_Specification()) {
		SYB_MachineUniqSwitch[UNIQ_SW_H3] |= OPTIONAL_SPEED_DIAL;
	}
#endif

#if ((defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)) && defined(JPN))	/* 2003/12/02 Y.Kano */
	if (ROM_SW_OptionalSpeedDial) {	/* スギ薬局特ROM（任意短縮）*/
		SYB_MachineUniqSwitch[UNIQ_SW_H3] |= OPTIONAL_SPEED_DIAL;
	}
#endif

}


/*************************************************************************
	module		:[保守用スイッチの初期化]
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
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void	CMN_InitMaintenanceSwitch(void)
{
	UWORD i;

	for (i = 0; i < SYS_MEMORY_SWITCH_MAX; i ++) {
		SYB_MaintenanceSwitch[i] = MaintenanceSwInitialTable[i];
	}
}



/*************************************************************************
	module		:[バックアップ領域全て初期化]
	function	:[
		1:ROMの種類に関係なくバックアップデータ領域を全て初期化する。（共通バックアップデータ
		,オプション専用バックアップデータ両方とも初期化)
		→　DiagRW_UserSelectAddress～SYB_SRAMClearStartAddressまでの領域を初期化

		2:引数０→バックアップ領域全てを初期化。
				　電源立ち上げ時にSRAM異常と判断された時、及び機能＊３によるオールラムクリアが実行された
				　時にこの引数を指定する。
		　引数１→機能＊２によるユーザ登録データのみのクリアを実行された時にこの引数を指定する。

		  引数２→機器パラメータ初期化を除くオールラムクリアの実行（Ｄ６８／Ｄ７１ＵＳＡ仕様対象） By S.Fukui Oct.27,1998
				 （[ＭＡＩからの要望]フィールドで設置時に機能＊３を実施する為、工場設定されたパラメータを初期化を防ぐ為）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/10/07]
	author		:[江口]
*************************************************************************/
void	CMN_InitializeAllBackUpRAM(UBYTE	mode)
{
	UWORD i;
#if defined (KEISATSU) /* 警察FAX 05/04/27 石橋正和 */
	UBYTE att_k;
	UBYTE att_1;
#endif

 #if (PRO_ALLRAMCLR_WO_MCP == ENABLE) /* ALL RAM Clearの際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	if ((mode == 0) || (mode == 2)){
		if (mode == 0) {
			/*------------------------------------------*/
			/** マシーンパラメーターの初期化 (ROM Table)*/
			/*------------------------------------------*/
			CMN_InitializeMachineParameter();
		}
 #else
	if (mode == 0) { /** バックアップ領域全てを初期化する場合 */
		/*------------------------------------------*/
		/** マシーンパラメーターの初期化 (ROM Table)*/
		/*------------------------------------------*/
		CMN_InitializeMachineParameter();
 #endif
		/*------------------------------------------*/
		/** メモリースイッチの初期化     (ROM Table)*/
		/*------------------------------------------*/
		
#if defined (KEISATSU) /* 警察FAX 05/04/27 石橋正和 */
		if (mode == 2) {
			att_k = (ATTENATION & SYS_MemorySwitch[MEMORY_SW_B1]);
			att_1 = (ATTENATION & SYS_MemorySwitch[MEMORY_SW_B4]);
		}
#endif
		CMN_InitializeMemorySwitch();
#if defined (KEISATSU) /* 警察FAX 05/04/27 石橋正和 */
		if (mode == 2) {
			SYS_MemorySwitch[MEMORY_SW_B1] &= ~ATTENATION;
			SYS_MemorySwitch[MEMORY_SW_B1] |= att_k;
			
			SYS_MemorySwitch[MEMORY_SW_B4] &= ~ATTENATION;
			SYS_MemorySwitch[MEMORY_SW_B4] |= att_1;
		}
#endif

		/*-----------------------------------------------*/
		/** 機種固有メモリースイッチの初期化  (ROM Table)*/
		/*-----------------------------------------------*/
		CMN_InitializeUniqSwitch();

#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)	/* 1998/11/16 by T.Soneoka */
		InzScannerBackupData();
#endif
		/* 保守用スイッチの初期化は、ＲＯＭタイプをおぼえる処理を含むので、すべての初期化が終了してからにする. */
	}
#if (PRO_LINENUMBER == TWICE_LINE) /* 送信・受信、外線・内線設定がユーザデータクリアで初期化されない。By H.Fujimura 2002/08/20 */
	else {
		/* 送信・受信設定の初期化 */
		SYB_MachineUniqSwitch[UNIQ_SW_A7] &= ~(LINE0_TX_ONLY | LINE0_RX_ONLY);
		SYB_MachineUniqSwitch[UNIQ_SW_A7] |= (UniqSwitchInitialTable[UNIQ_SW_A7] & (LINE0_TX_ONLY | LINE0_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A7] &= ~(LINE1_TX_ONLY | LINE1_RX_ONLY);
		SYB_MachineUniqSwitch[UNIQ_SW_A7] |= (UniqSwitchInitialTable[UNIQ_SW_A7] & (LINE1_TX_ONLY | LINE1_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A7] &= ~(LINE2_TX_ONLY | LINE2_RX_ONLY);
		SYB_MachineUniqSwitch[UNIQ_SW_A7] |= (UniqSwitchInitialTable[UNIQ_SW_A7] & (LINE2_TX_ONLY | LINE2_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A7] &= ~(LINE3_TX_ONLY | LINE3_RX_ONLY);
		SYB_MachineUniqSwitch[UNIQ_SW_A7] |= (UniqSwitchInitialTable[UNIQ_SW_A7] & (LINE3_TX_ONLY | LINE3_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A8] &= ~(LINE4_TX_ONLY | LINE4_RX_ONLY);
		SYB_MachineUniqSwitch[UNIQ_SW_A8] |= (UniqSwitchInitialTable[UNIQ_SW_A8] & (LINE4_TX_ONLY | LINE4_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A8] &= ~(LINE5_TX_ONLY | LINE5_RX_ONLY);
		SYB_MachineUniqSwitch[UNIQ_SW_A8] |= (UniqSwitchInitialTable[UNIQ_SW_A8] & (LINE5_TX_ONLY | LINE5_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A8] &= ~(LINE6_TX_ONLY | LINE6_RX_ONLY);
		SYB_MachineUniqSwitch[UNIQ_SW_A8] |= (UniqSwitchInitialTable[UNIQ_SW_A8] & (LINE6_TX_ONLY | LINE6_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A8] &= ~(LINE7_TX_ONLY | LINE7_RX_ONLY);
		SYB_MachineUniqSwitch[UNIQ_SW_A8] |= (UniqSwitchInitialTable[UNIQ_SW_A8] & (LINE7_TX_ONLY | LINE7_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A9] &= ~(LINE8_TX_ONLY | LINE8_RX_ONLY);
		SYB_MachineUniqSwitch[UNIQ_SW_A9] |= (UniqSwitchInitialTable[UNIQ_SW_A9] & (LINE8_TX_ONLY | LINE8_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A9] &= ~(LINE_EXT_TX_ONLY | LINE_EXT_RX_ONLY);
		SYB_MachineUniqSwitch[UNIQ_SW_A9] |= (UniqSwitchInitialTable[UNIQ_SW_A9] & (LINE_EXT_TX_ONLY | LINE_EXT_RX_ONLY));
		/* 外線・内線設定の初期化 */
		SYS_MemorySwitch[MEMORY_SW_A0] &= ~PBX;
		SYS_MemorySwitch[MEMORY_SW_A0] |= (MemorySwitchInitialTable[MEMORY_SW_A0] & PBX);
		SYS_MemorySwitch[MEMORY_SW_A2] &= ~PBX1;
		SYS_MemorySwitch[MEMORY_SW_A2] |= (MemorySwitchInitialTable[MEMORY_SW_A2] & PBX1);
		SYS_MemorySwitch[MEMORY_SW_A2] &= ~PBX2;
		SYS_MemorySwitch[MEMORY_SW_A2] |= (MemorySwitchInitialTable[MEMORY_SW_A2] & PBX2);
		SYS_MemorySwitch[MEMORY_SW_A2] &= ~PBX3;
		SYS_MemorySwitch[MEMORY_SW_A2] |= (MemorySwitchInitialTable[MEMORY_SW_A2] & PBX3);
		SYS_MemorySwitch[MEMORY_SW_A2] &= ~PBX4;
		SYS_MemorySwitch[MEMORY_SW_A2] |= (MemorySwitchInitialTable[MEMORY_SW_A2] & PBX4);
		SYS_MemorySwitch[MEMORY_SW_A2] &= ~PBX5;
		SYS_MemorySwitch[MEMORY_SW_A2] |= (MemorySwitchInitialTable[MEMORY_SW_A2] & PBX5);
		SYS_MemorySwitch[MEMORY_SW_A2] &= ~PBX6;
		SYS_MemorySwitch[MEMORY_SW_A2] |= (MemorySwitchInitialTable[MEMORY_SW_A2] & PBX6);
		SYS_MemorySwitch[MEMORY_SW_A2] &= ~PBX7;
		SYS_MemorySwitch[MEMORY_SW_A2] |= (MemorySwitchInitialTable[MEMORY_SW_A2] & PBX7);
		SYS_MemorySwitch[MEMORY_SW_A2] &= ~PBX8;
		SYS_MemorySwitch[MEMORY_SW_A2] |= (MemorySwitchInitialTable[MEMORY_SW_A2] & PBX8);
		SYS_MemorySwitch[MEMORY_SW_A0] &= ~PBX_EXT;
		SYS_MemorySwitch[MEMORY_SW_A0] |= (MemorySwitchInitialTable[MEMORY_SW_A0] & PBX_EXT);
	}
#endif
	/*------------------------------*
	 ** DRAM管理データの初期化 		*
	 *------------------------------*/
	MEM_ClearAll();		/* 1994/06/30 Y.Murata */

	/*-----------------------*
	 ** 機器設定の初期化
	 *-----------------------*/
	for (i = 0; i < SYS_SETTING_MAX; i ++) {
		SYB_SettingStatus[i] = SettingStatusInitialTable[i];
	 }

	SYB_SettingStatus[NUMBER_OF_REDIAL]      = CTRY_InitRedialNumber();
	SYB_SettingStatus[REDIAL_INTERVAL]       = CTRY_InitRedialInterval();
	SYB_SettingStatus[DIALING_PAUSE]         = CTRY_InitPauseTime();
	SYB_SettingStatus[NUMBER_OF_RINGS]       = CTRY_InitRingCount();
#if defined (KEISATSU) /* 警察FAX 05/06/06 */
	SYB_SettingStatus[NUMBER_OF_RINGS_EXT]   = CTRY_InitRingCount();
#endif
	SYB_SettingStatus[SECURE_MAIL_HOLD_TIME] = CTRY_InitSecureMailRxTime();
#if defined(SATSUKI2)	/* SATSUKI2は外付けSWで決定 by Y.Kano 2003/09/17 */
	CheckTxDialType();
#elif defined (KEISATSU) /* 警察FAX 05/10/05 石橋正和 */
	SYB_SettingStatus[SETTING_STATUS_0] |= KEISATSU_LINE_TYPE_STD;
#else
	SYB_SettingStatus[SETTING_STATUS_0]     |= CTRY_InitPhoneType();
#endif

	/*外付け第１*/
	SYB_SettingStatus[SETTING_STATUS_0] &= ~(DIAL_SPEED_20PPS_1 | LINE_TYPE_TONE_1);
	SYB_SettingStatus[SETTING_STATUS_0] |= (CTRY_InitPhoneType() << 2);

	/*外付け第２*/
	SYB_SettingStatus[SETTING_STATUS_0] &= ~(DIAL_SPEED_20PPS_2 | LINE_TYPE_TONE_2);
	SYB_SettingStatus[SETTING_STATUS_0] |= (CTRY_InitPhoneType() << 4);

	/*外付け第３*/
	SYB_SettingStatus[SETTING_STATUS_28] &= ~(DIAL_SPEED_20PPS_3 | LINE_TYPE_TONE_3);
	SYB_SettingStatus[SETTING_STATUS_28] |= CTRY_InitPhoneType();

	/*外付け第４*/
	SYB_SettingStatus[SETTING_STATUS_28] &= ~(DIAL_SPEED_20PPS_4 | LINE_TYPE_TONE_4);
	SYB_SettingStatus[SETTING_STATUS_28] |= (CTRY_InitPhoneType() << 2);

	/*外付け第５*/
	SYB_SettingStatus[SETTING_STATUS_28] &= ~(DIAL_SPEED_20PPS_5 | LINE_TYPE_TONE_5);
	SYB_SettingStatus[SETTING_STATUS_28] |= (CTRY_InitPhoneType() << 4);

	/*外付け第６*/
	SYB_SettingStatus[SETTING_STATUS_29] &= ~(DIAL_SPEED_20PPS_6 | LINE_TYPE_TONE_6);
	SYB_SettingStatus[SETTING_STATUS_29] |= CTRY_InitPhoneType();

	/*外付け第７*/
	SYB_SettingStatus[SETTING_STATUS_29] &= ~(DIAL_SPEED_20PPS_7 | LINE_TYPE_TONE_7);
	SYB_SettingStatus[SETTING_STATUS_29] |= (CTRY_InitPhoneType() << 2);

	/*外付け第８*/
	SYB_SettingStatus[SETTING_STATUS_29] &= ~(DIAL_SPEED_20PPS_8 | LINE_TYPE_TONE_8);
	SYB_SettingStatus[SETTING_STATUS_29] |= (CTRY_InitPhoneType() << 4);

#if (PRO_LINENUMBER == TWICE_LINE)
	/* ＰＯＰＬＡＲ＿Ｈは標準で収容回線が２回線（標準／拡張）の為 By O.Kimoto 1997/11/04 */
	/*内蔵（拡張） */
	SYB_SettingStatus[SETTING_STATUS_29] &= ~(DIAL_SPEED_20PPS_EXT | LINE_TYPE_TONE_EXT);
#if defined (KEISATSU) /* 警察FAX 05/10/05 石橋正和 */
	SYB_SettingStatus[SETTING_STATUS_29] |= (KEISATSU_LINE_TYPE_EXT << 6);
#else
	SYB_SettingStatus[SETTING_STATUS_29] |= (CTRY_InitPhoneType() << 6);
#endif

	/*--------------------------------------------------------------------
	** 電源ONで立ち上がらず対策
	** RAMが壊れているときにこれをCallすると、正しく動作しません
	** ClearAllBackUpRAM()に移動します
	** 1999/02/26 H.Yoshikawa
	*/
 #if (0)
 //	InitializeRelay();	/*  リレー初期化 ADD by T.Soneoka 1997/12/04 */
 #endif
#endif

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* 1996/06/24 H,Yagi *//* by K.Watanabe 2004/10/12 */
	SYB_SettingStatus[MERCURY_PAUSE] = CTRY_InitMercuryPauseTime();
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.4.21 K.Kawata	*/
	if (CHK_OCA_Specification()) {
		SYB_SettingStatus[SETTING_STATUS_1] |= PRIMARY_MODE_FINE;
	}
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* POPLAR_Lのみとする By T.Nakajima 1999/02/04 */
	/*--------------------------------------------------------------------
	** ROMﾊﾞｰｼﾞｮﾝがTC751の時、リモート診断をOnにする
	** By T.Nakajima 1998/11/20
	*/
	if( CMN_StringCompare( ROM_Revision, "TC751", 5 ) == STRCMP_EQUAL ){
		SYB_SettingStatus[SETTING_STATUS_6] |= REMOTE_DIAG_ON;
	}
#endif

#if (PRO_OP_SPPED_4_FIGURE == ENABLE)	/* 2002/02/13 H.Yoshikawa */
	if (CHK_AIFUL_Specification()) {
		SYB_SettingStatus[SETTING_STATUS_2] &= ~HEAT_TRANSFER_ON;
	}
#endif

#if (PRO_PANEL == ANK) && (PRO_ANK_TO_KANJI == DISABLE)	/* PRO_ANK_TO_KANJIの条件追加 by K.Watanabe 1999/06/16 */
	/* POPLAR_Bでオールラムクリアを実行されると、モードだけコピーモードに初期化されてしまい、
	** ＣＧＲＡＭは曜日表示用のままなので初期化場所をモードの初期化（機器設定）に合わせます
	*/
	/*----------------------------------*
	 ** ＣＧＲＡＭ書き込みデータの初期化
	 *----------------------------------*/
	InitializeCGRAM_Data();
#endif

	/*---------------------*
	 ** ローカル機器設定
	 *---------------------*/
	CMN_ResetMemoyFeederTx();
	CMN_ResetStamp();
	CMN_ResetConfirmationReport();
#if (PRO_RED_SCAN == ENABLE)	/* 朱色読み取り 2002/03/05 T.Takagi */
	CMN_ResetRedScan();
#endif

	/*--------------------*
	 ** 受信モードスイッチ
	 *--------------------*/
#if (PRO_AUTO_RX_SWITCH == ENABLE)
 #if defined (KEISATSU) /* 警察FAX 05/06/03 石橋正和 */
	SYB_RxModeSwitch = 0;
	SYB_RxModeSwitchExt = 0;
 #else	
	SYB_RxModeSwitch = SYS_AUTO_CALLED_SW;
 #endif
#else
	SYB_RxModeSwitch = 0;
#endif

	/*--------------------*
	 ** 送信モードスイッチ
	 *--------------------*/
	CMN_ResetPrimaryMode();

	/*------------------*
	 ** 原稿濃度スイッチ
	 *------------------*/
	CMN_ResetPrimaryContrast();

	/*--------------*
	 ** 原稿読取り幅
	 *--------------*/
	CMN_ResetPrimaryDocumentSize();

	/*------------*
	 ** パスコード
	 *------------*/
	for (i = 0; i < SYS_PASSCODE_MAX; i ++) {
		SYB_PasscodeNumber[i] = '0';
	}

	/*------------------*
	 ** 親展受信ボックス
	 *------------------*/
	for (i = 0; i < SYS_MAILBOX_MAX; i ++) {
		CMN_ClearMailBox(i);
	}

	/*---------------------*
	 * 通信管理記録		   *
	 *---------------------*/
	CMN_ClearJournalData();

	/*------------------*
	 * 標準短縮ダイヤル *
	 *------------------*/
/*	for (i = 0; i < SYS_SPEED_DIAL_MAX; i ++) [ ポプラＮＴＴ仕様 短縮１２８件-->１００対応 By Y.Suzuki 1998/03/15 */
	/* ポプラNTT 以外は、SYS_SPEED_DIAL_MAX_BKUP == SYS_SPEED_DIAL_MAX */
	for (i = 0; i < SYS_SPEED_DIAL_MAX_BKUP; i ++) {
		CMN_ClearSpeedDial(i);
	}

	/*------------------------------*/
	/* 短縮番号管理テーブルの初期化 */
	/* 1995.02.13 野瀬				*/
	/*------------------------------*/
	/*if (SPD_Operation) {*/
/*		for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) [  ポプラＮＴＴ仕様 短縮１２８件-->１００対応 By Y.Suzuki 1998/03/15 */
		/* ポプラNTT 以外は、SYS_SPEED_DIAL_MAX_BKUP == SYS_SPEED_DIAL_MAX */
		for (i = 0; i < SYS_SPEED_DIAL_MAX_BKUP; i ++) {
			SYB_OptionalSpeed[i].Number = 0xFFFF;
			SYB_OptionalSpeed[i].Record = 0xFF;
		}
	/*}*/

	/*------------------------*
	 * 標準ワンタッチダイヤル *
	 *------------------------*/
	for (i = 0; i < SYS_ONETOUCH_MAX; i ++) {
		CMN_ClearOnetouchDial(i);
	}

#if (PRO_SUB_DIAL == ENABLE)
	/*----------------*
	 * 転送先ダイヤル *
	 *----------------*/
	for (i = 0; i < SYS_SUB_DIAL_MAX; i ++) {
		CMN_ClearSubDial(i);
	}
#endif

	/*----------------------*
	 * プログラムワンタッチ *
	 * 1995/12/04 Eguchi	*
	 *----------------------*/
	/*for (i = 0; i < SYS_PROGRAM_MAX; i++) { ここだけdefine name 変更 1998/02/19 Y.Murata */
	for (i = 0; i < SYS_PROGRAM_MAX_BKUP; i++) {	/* この行コピーしたら絶対ダメ */
		CMN_ClearProgramOnetouch(i);
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/19 */
		CMN_ClearCipherPData(i);
#endif
	}

#if (PRO_F_CODE == ENABLE)
	for (i = 0; i < SUB_ADDRESS_BOX_MAX; i++) {
		CMN_ClearFcodeBox(i);
	}
#endif

#if (PRO_CIPHER == ENABLE)	/*	 1997/06/18  By T.Yamaguchi */
	for (i = 0; i < SYS_CIPHERBOX_MAX; i ++) {
		SYB_CipherBox[i].Status = SYS_CIPHERBOX_NO;
		SYB_CipherBox[i].MessageStatus = SYS_CIPHERBOX_MSG_EMPTY;
		SYB_CipherBox[i].StorePage = 0;
		SYB_CipherBox[i].PrintPage = 1;
	}
#endif

	SYB_SelectPollDocumentStatus = 0;	/* 選択ポーリング蓄積原稿あり */
	/*----------------------------*
	 * 電話帳機能用データバッファ *
	 * 電話帳機能用データ登録件数 *
	 *----------------------------*/
#if (PRO_DIRECTORY == ENABLE)
	for (i = 0; i <= SYS_TELBOOK_MAX; i++) {
 #if (PRO_SPEED_DIAL_ADDITION == ENABLE)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
		SYB_TelephoneBookData[i][0] = 0xFFFF;
 #else
		SYB_TelephoneBookData[i][0] = 0xFF;
 #endif
	}
	SYB_TelBookDataEnd = 0;
#endif

	/*------------------*/
	/* ｼﾞｬｸﾒｰﾙ防止ﾀﾞｲﾔﾙ */	/* 1997/05/13  By T.Yamaguchi */
	/*------------------*/
	for (i = 0; i < SYS_JUNK_DIAL_MAX; i++) {
		CMN_ClearJunkDial(i);
	}

	/*------------------*/
	/* マーキュリー		*/
	/*------------------*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/*96/06/27	H,Yagi*//* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	for (i = 0; i < SYS_MERCURY_BUF_MAX; i++) {
		CMN_MercuryDial(i);
	}
 #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* QAT不具合 プレフィクスダイヤル番号のデフォルト変更 by Y.Kano 2004/10/25 *//* by K.Watanabe 2004/11/04 */
  #if (1)
	SYB_MercuryDialBuffer[0] = '0';
	SYB_MercuryDialBuffer[1] = '0';
	SYB_MercuryDialBuffer[2] = '0';
	SYB_MercuryDialBuffer[3] = '0';
	SYB_MercuryDialBuffer[4] = NULL;
  #else
	SYB_MercuryDialBuffer[0] = '1';
	SYB_MercuryDialBuffer[1] = '2';
	SYB_MercuryDialBuffer[2] = '3';
	SYB_MercuryDialBuffer[3] = '4';
	SYB_MercuryDialBuffer[4] = '5';
	SYB_MercuryDialBuffer[5] = '6';
	SYB_MercuryDialBuffer[6] = NULL;
  #endif
 #endif
#endif

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	/*--------------------------------------*/
	/*	MercuryTone検出時間 ＆ Pause時間	*/
	/*	date:	1994年11月17日				*/
	/*	name:	MANABU HARADA				*/
	/*--------------------------------------*/
	SYB_MercuryPauseTime = MCRY_PAUSE_1ST_DATA;
#endif

	/*--------------------------------------------*
	 * ＤＥＵ（ドイツ仕様）ダイアル失敗カウンター *
	 *--------------------------------------------*/
#if defined(DEU)
	SYB_DEUDialerFaultCounter = 0;
#endif

	/*--------------*
	 * 部門管理情報 *
	 *--------------*/
#if (PRO_COST == ENABLE)
	CMN_AllClearDepartFile();

#endif

	/*------------------*
	 * 簡易料金管理情報 *
	 *------------------*/
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト By t.honda 1997/11/29 */
	CMN_AllClearDepartManageFile();

#endif

	/*----------*
	 * 一括送信 *
	 *----------*/
#if (PRO_BATCH_TX == ENABLE)
	for (i = 0; i < SYS_BATCH_FILE_MAX; i ++) {
		CMN_ClearBatchTxFile(i);
	}
#endif

	/*----------------------------------*
	 * カバーページ送信のメッセージ内容 *
	 *----------------------------------*/
	CMN_ClearCoverPageMessage();

	/*----------------*
	 * 発信元電話番号 *
	 *----------------*/
	CMN_ClearID_Buffer();

	/*------------------------------*
	 * 発信元名(送信原稿先頭付加用) *
	 *------------------------------*/
	CMN_ClearTTI_Buffer();

	/*--------------------------------*
	 * 発信元名カナＩＤ(非標準手順用) *
	 *--------------------------------*/
#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
	CMN_ClearTTI_ID_Buffer();
#endif

#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
	for (i = 0; i < SYS_MULTI_MAX; i++) {
		/*----------------------*
		 * マルチ発信元電話番号 *
		 *----------------------*/
		SYB_Multi_ID_Buffer[i][0] = 0x00;

		/*------------------------------------*
		 * マルチ発信元名(送信原稿先頭付加用) *
		 *------------------------------------*/
		SYB_Multi_TTI_Buffer[i][0] = 0x00;

		/*--------------------------------------*
		 * マルチ発信元名カナＩＤ(非標準手順用) *
		 *--------------------------------------*/
		SYB_Multi_TTI_ID_Buffer[i][0] = 0x00;
	}
#endif

	/*-------------------------------------*
	 * ダイヤルイン						   *
	 * ON/OFFはSettingStatusの初期化で行う *
	 *-------------------------------------*/
#if (PRO_DIALIN == ENABLE)
	CMN_ClearDialin();
#endif

	/*---------------------------*/
	/* 回線監視(NCU)関係大域変数 */
	/*---------------------------*/
#if (PRO_DIALIN == ENABLE)
	SYB_DialInNoNumberSignal = 1;		/** ダイヤル・インのＤＴＭＦを１度も検出していない場合１ '94,08,30 By N.S. */
#endif

	/*------------------*
	 * 料金管理テーブル *
	 *------------------*/
#if (PRO_COST == ENABLE)
	for (i = 0; i < SYS_COST_TABLE_MAX; i ++) {
		CMN_ClearCostTable(i);
	}
	for (i = 0; i < SYS_SPEED_DIAL_MAX + SYS_2ND_SPEED_DIAL_MAX + SYS_ONETOUCH_MAX + SYS_2ND_ONETOUCH_MAX; i++) {
		CMN_ClearNTT_AccessFile(i);
	}
#endif

	/*----------------*
	 * 連続ポーリング *
	 *----------------*/
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング処理追加 1996/10/18 Eguchi*/
	SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;
#endif

	/*----------*
	 * 通信予約 *
	 *----------*/
	for (i = 0; i < SYS_COM_FILE_MAX; i ++) {
		SYB_CommandFile[i].Status = SYS_CMD_EMPTY;
#if (PRO_F_CODE == ENABLE)	/* 1997/08/08  By T.Yamaguchi */
		SYB_FcodeNumberCDataBuffer[i].SYS_SubAddressNumber[0] = 0xFF;
		SYB_FcodeNumberCDataBuffer[i].SYS_PassWordNumber[0] = 0xFF;
#endif
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
		SYB_CommandStatus[i] = SYS_CMD_EMPTY;
#endif
#if defined (KEISATSU) /* 警察FAX 05/06/22 石橋正和 */
		/* とりあえず初期化しておく */
		SYB_CommandKeisatsu[i].Line = SYS_LINE_KANYU;
		SYB_CommandKeisatsu[i].Scramble = FALSE;
		SYB_CommandKeisatsu[i].Senyo = FALSE;
#endif
	}

	/*-------------------------------*
	 * 発信スケジューラ関係の初期化　*
	 *-------------------------------*/
	/* 実行待ちファイル */
	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i ++) {
		SYB_ExecQueue[i].Status = SYS_EXEC_EMPTY;
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/01 */
		SYB_ExecQueueKeisatsu[i].Line = SYS_LINE_KANYU;
		SYB_ExecQueueKeisatsu[i].Scramble = FALSE;
		SYB_ExecQueueKeisatsu[i].Senyo = FALSE;
#endif		/* End of (defined (KEISATSU)) */
	}

	/* 実行待ちﾌｧｲﾙの展開位置 */
	SYB_ExecQueueWritePoint = 0;

	/* 実行待ちﾌｧｲﾙの実行位置 */
	SYB_ExecQueueReadPoint = 0;

	SYB_ExecQueueSerchPoint = 0;			/* 実行ｷｭｰ検索ﾎﾟｲﾝﾀｰ初期化 1997/10/28 Y.Murata */

	/*--------------------------------*
	 * マルチコピー管理データの初期化 *
	 *--------------------------------*/
	/* 管理ファイル */
	for (i = 0; i < SYS_MULTI_COPY_MAX; i ++) {
		SYB_MultiCopyFile[i].Status = SYS_MCOPY_EMPTY;
	}
	/* ﾏﾙﾁｺﾋﾟｰ管理ﾌｧｲﾙの展開位置 */
	SYB_MultiCopyWritePoint = 0;

	/* ﾏﾙﾁｺﾋﾟｰ管理ﾌｧｲﾙの実行位置 */
	SYB_MultiCopyReadPoint = 0;

	/*--------------------------------*
	 * 手差しコピー管理データの初期化 *
	 *--------------------------------*/
	SYB_ManualCopyFile.Status = SYS_MCOPY_EMPTY;

	/*------------------------------------------*
	 * メモリ受信原稿プリント管理データの初期化 *
	 *------------------------------------------*/
	/* 管理ファイル */
	for (i = 0; i < SYS_MEMORY_RX_MAX; i ++) {
		SYB_MemoryRxPrint[i].Status = SYS_MEMORY_RX_EMPTY;
		SYB_MemoryRxPrint[i].StorePage = 0;	/* 1995/04/20 By M.Tachibana */
		SYB_MemoryRxPrint[i].RotatePage = 1;	/* By M.Kotani 97/04/28 */
		SYB_MemoryRxPrint[i].PrintPage = 1;	/* 1995/04/20 By M.Tachibana */
		SYB_MemoryRxPrint[i].ErasePage = 1;	/* 1995/04/20 By M.Tachibana */
		SYB_MemoryRxPrint[i].Protect   = SYS_PROTECT_OFF;	/* 1995/12/22 Eguchi */
		SYB_MemoryRxPrint[i].StackNumber = 0;				/** スタックＮｏセット  1997/03/07  By T.Yamaguchi */
		SYB_MemoryRxPrint[i].ReceiveTime = 0;				/* 取り敢えず追加 */
		SYB_MemoryRxPrint[i].JournalPoint = 0;				/* 取り敢えず追加 */
	}
	/* ﾒﾓﾘ受信ﾌﾟﾘﾝﾄ管理ﾌｧｲﾙ書き込み位置 */
	SYB_MemoryRxPrintWritePoint = 0;

	/* ﾒﾓﾘ受信ﾌﾟﾘﾝﾄ管理ﾌｧｲﾙ実行位置 */
	SYB_MemoryRxPrintReadPoint = 0;

	/*----------------------------*
	 * ﾎﾟ-ﾘｸﾞ原稿蓄積状態管理ﾃﾞ-ﾀ *
	 *----------------------------*/
	SYB_PollingDocumentStatus = 0;

	/*------------------------------*
	 * DBﾎﾟ-ﾘｸﾞ原稿蓄積状態管理ﾃﾞ-ﾀ *
	 *------------------------------*/
	SYB_DB_PollingDocumentStatus = 0;

	/*--------------------*
	 * リダイヤルバッファ *
	 *--------------------*/
	SYB_RedialBuffer[0] = 0x00;

	/*---------*
	 * PBX番号 *
	 *---------*/
	SYB_PBX_Number[0] = 0x00;

	/*----------------*
	 * 現在時間初期化 *
	 *----------------*/
	/** セマフォ獲得 1996/03/29 Eguchi */
	wai_sem(semno.rtc);
#if defined (HINOKI2) || defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3)
	if (CMN_StringCompare2(ROM_Revision, "SFX78", 5) == STRCMP_EQUAL) {	/* SANYO仕様の時 */
		CurrentTimeInBCD.Year = 0x03;	/* SFX78Mは2003年リリースなので2003年にする 2003/01/14 T.Takagi */
	}
	else {
 #if defined(SATSUKI2) || defined(STOCKHM2)
  #if defined(STOCKHM2)		/* 2004年にセット by Y.Kano 2004/10/25 */
		CurrentTimeInBCD.Year = 0x04;	/* 2004年にセット 2004/10/25 Y.Kano */
  #else
		CurrentTimeInBCD.Year = 0x03;	/* 2003年にセット 2003/09/22 Y.Kano */
  #endif
 #elif defined(HINOKI3)
		CurrentTimeInBCD.Year = 0x05;	/* 2005年にセット 2004/12/03 Y.Tanaka */
 #else
		CurrentTimeInBCD.Year = 0x01;	/* マニュアルと整合が必要。現状は2001年のまま 2002/03/06 T.Takagi */
 #endif
	}
#elif (defined(POPLAR_H) && defined(JP0)) /* V851 By H.Fujimura 2002/08/27 */ || (defined(SAKAKI) && defined(JP0)) /* SAKAKI2 2002/09/20 By M.Maeda */
	CurrentTimeInBCD.Year = 0x02;
#else
	CurrentTimeInBCD.Year = 0x01;
#endif
	CurrentTimeInBCD.Month = 1;
	CurrentTimeInBCD.Date = 1;
	CurrentTimeInBCD.Hour = 0;
	CurrentTimeInBCD.Minute = 0;
	CurrentTimeInBCD.Second = 0;
	CMN_LongTimeToBCD((TIME_DATA_t *)&CurrentTimeInBCD, CMN_BCD_TimeToLong((TIME_DATA_t *)&CurrentTimeInBCD));
	WriteCurrentTime();
	/** セマフォ解放 1996/03/29 Eguchi */
	sig_sem(semno.rtc);

	/* SYB_CurrentTimeはMAN_TimerTask()でセットされる */

	/*------------------------*
	 * ワーディング関係初期化 *
	 *------------------------*/
	/* ワーディング番号 */
	SYB_WordingNumber = CTRY_InitWordingNumber();

#if (0)	/* 未使用なので削除します by K.Watanabe 1998/07/10 */
//	/* ページレジスターセット */
//	SetWording(SYB_WordingNumber);
//
//	/** ワーディングの実体までのオフセットの計算 1996/03/11 Eguchi*/
//	CalculateWordingOffset();
#endif

#if (0)
**	ジャーナルデータクリア時、Ｔ３０モニタがクリアされない場合があり、
**	その時点でＴ３０モニタをプリントすると明細部分が不定になります。
**	よって、必ず一緒にクリアされるように、CMN_ClearJournalData()へ移します。
**	By H.Fujimura 1999/04/16
**
**	/*-----------*
**	 * T30モニタ *
**	 *-----------*/
**	SYB_T30Monitor.JournalType = SYS_T30_EMPTY;
#endif

#if defined(POPLAR_F)
	SYB_T30Monitor.JournalType = SYS_T30_EMPTY;
	SYS_OptionT30Monitor.JournalType = SYS_T30_EMPTY;
	for (i = 0; i < SYS_JOURNAL_MAX; i++) {
		SYB_T30MonitorDRAM_Status[i] = 0;
	}
#endif

	/*--------------------------*
	 * リモート診断パスワード	*
	 *--------------------------*/
	for (i = 0; i < 4; i++) {
		SYB_DiagPasscodeNumber[i] = '0';
	}

	/*-------------------------------------*/
	/** ＤＲＡＭバックアップ可能時間クリア */
	/*-------------------------------------*/
	SYB_DRAM_BackupTime = 0;			/* ＤＲＡＭバックアップ可能時間 1994/11/04 Y.Murata */

	/*--------------------------*/
	/* 停電検出リストステータス */
	/*--------------------------*//* 1994/11/26 Y.Murata */
	SYB_PowerDownListStatus = 0;

	/*---------------------------*/
	/* FIP受信許可フラグのクリア */
	/*---------------------------*/
#if (PRO_FIP == ENABLE)
	SYB_FIP_ReceiveEnableFlag = 0;	/* 1995/02/15 By M.Tachibana */
#endif

	/*----------------------------------------------*/
	/* リングマスターパターン自動検出データのクリア */
	/*----------------------------------------------*/
#if (PRO_RING_MASTER == ENABLE)		/* Add by TH92115	1995/06/01 */
	for (i = 0; i < 6; i++) {
		SYB_TeachingPattern[0].RingMinCycle[i] = 0;
		SYB_TeachingPattern[0].RingMaxCycle[i] = 0;
		SYB_TeachingPattern[1].RingMinCycle[i] = 0;
		SYB_TeachingPattern[1].RingMaxCycle[i] = 0;
	}
	SYB_RingG_SetNumber = 0;
	SYB_RingH_SetNumber = 0;
#endif

	/*----------------------------------------*/
	/* プロテクトパスコード	1995/12/16 Eguchi */
	/*----------------------------------------*/
	SYB_ProtectPasscode = 0;

	/*---------------------------------------*/
	/* 部門コード	 1995/12/20 Eguchi (ANZU)*/
	/*---------------------------------------*/
	for (i = 0; i < SYS_DEPART_MAX + 1; i++) {
		SYB_DepartmentCode[i] = 0xFFFF;
	}

	/*-------------------------------------------*/
	/* スピーカーボリューム値 1996/01/16 Eguchi	 */
	/*-------------------------------------------*/
	SYB_MonitorSpeakerOutLevel = SYS_VOLUME_MIDDLE;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SATSUKI2仕様では、キータッチボリュームも行う by Y.Kano 2003/09/01 */
	/*-------------------------------------------*/
	/* キータッチボリューム値 2003/09/01 Y.Kano	 */
	/*-------------------------------------------*/
	SYB_BuzzerOutLevel = KEY_BUZZER_VOLUME_MID;	/* ブザー定数変更 by Y.Kano 2003/10/10 */
/*	SYB_BuzzerOutLevel = BUZZER_VOLUME_MID;*/

	/*-------------------------------------------*/
	/* 電源のON時にリンガを鳴動する/しない 2003/09/18 Y.Kano	 */
	/*-------------------------------------------*/
	SYB_RingOut = TRUE; 	/* 鳴動する */

	/*-------------------------------------------*/
	/* ＰＳ２閾値デフォルト 2003/10/18 Y.Kano	 */
	/*-------------------------------------------*/
	SYB_PS2LimitValue = PS2DEFAULT; 		/* ＰＳ２デフォルト */
#endif

	/*-------------------------------------------*/
	/* セキュリティ受信関係						 */
	/* 1996/04/27 Eguchi						 */
	/*-------------------------------------------*/
	SYB_SecurityRxModeFlag = 0;
	SYB_SecurityRxSettingTime = 0xFFFF;
	SYB_SecurityRxModeStartTime = 0x00000000UL;

	/*------------------------------------------*
	 * セキュリティ受信モード中の受信メモリーオーバー
	 * メッセージ関係
	 * 1996/06/28 Eguchi
	 *------------------------------------------*/
	SYB_SecurityRxChkMsgRequest = 0;
	SYB_SecurityRxChkMsgPrint = 0;

	/*-------------------------------------------*/
	/* トナーわずかになってからの印字可能枚数	 */
	/* By S.Kawsaki 1996/06/20					 */
	/*-------------------------------------------*/
	SYB_TonarEndPageCounter = 0;

	/*---------------------------------------------*
	 *オプション専用に追加されたデータの初期化	   *
	 *---------------------------------------------*/

/*#if (PRO_CLASS1 == ENABLE) 条件をはずす By M.Tachibana 1998/02/18 *//* 1996/09/24 Eguchi */
	/*----------------------*
	 * クラス１関係			*
	 *----------------------*/
	CL1_PCDocumentCode = SYS_MH_CODE;
	CL1_PCDocumentMode = SYS_NORMAL;
	CL1_PCDocumentSize = SYS_DOCUMENT_A4_SIZE;

	/*-----------------------------------*
	 * ローカルスキャン原稿蓄積状態初期化
	 *-----------------------------------*/
	SYB_CL1_LocalScanDocStatus = 0;

	/*-----------------------------------------*
	 *　ローカルプリント原稿管理テーブル初期化
     *-----------------------------------------*/
	for (i = 0; i < SYS_MEMORY_RX_MAX; i ++) {
		SYB_CL1_MemoryRxPrint[i].Status = SYS_MEMORY_RX_EMPTY;
		SYB_CL1_MemoryRxPrint[i].StorePage = 0;
		SYB_CL1_MemoryRxPrint[i].PrintPage = 1;
		SYB_CL1_MemoryRxPrint[i].ErasePage = 1;
		SYB_CL1_MemoryRxPrint[i].Protect   = SYS_PROTECT_OFF;
	}

    /*-----------------------------------------*
	 *　ローカルプリント原稿書き込み位置初期化
     *-----------------------------------------*/
	CL1_MemoryRxPrintWritePoint = 0;

    /*-----------------------------------------*
	 *　ローカルプリント原稿読み出し位置初期化
     *-----------------------------------------*/
	CL1_MemoryRxPrintReadPoint = 0;
/*#endif*/

    /*-----------------------------------------*
	 *　ＰＣプリント原稿管理テーブル初期化     *
     *-----------------------------------------*/
	SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
	SYB_PcRxPrint.ExecutiveNumber = 0;
	SYB_PcRxPrint.RemainMultiPrintCount = 0;
	SYB_PcRxPrint.StorePage = 0;
	SYB_PcRxPrint.PrintPage = 1;
	SYB_PcRxPrint.ErasePage = 1;
	SYB_PcRxPrint.PrintEndPage = 0;

/*------------------------------*/
/* オプション仕様（２回線仕様） */
/*------------------------------*/
	CMN_InitializeMultiLineData((UBYTE)0);

#if (PRO_COPY_FAX_MODE == ENABLE)
	/*--------------------*/
	/* コピーモード設定値 */
	/*--------------------*/
	/* OPR_Task()の中でもCALLしていますが、ＲＡＭクリアでも実行するように追加 */
	ClearCopyParameter();
#endif

#if	(PRO_LOW_TONER_PRINT == PRINT_LIMIT)	/* Add By O.Kimoto 1997/02/20 */
	SYB_RestPrintPages = (WORD)CHK_UNI_RestPrintPage();
#endif

	/*--------------------------------*
	 * スクランブル関連のデータの初期化
	 * By Y.Suzuki 1997/06/17
	 *--------------------------------*/
	SYB_KeyBookData.CipherPassCode = 0;
	SYB_KeyBookData.DefaultKeyNo = 0xFF;
#if defined(USA)							/* inch系 は 1.0inch 	By S.Fukui Dec.15,1997 */
	SYB_KeyBookData.OffsetServiceLabel = 3;	/* 内部的にはcmで持っているので1.0inch = 2.54cm -> 約3cm */
#else										/* cm系   は 2cm		*/
	SYB_KeyBookData.OffsetServiceLabel = 2;
#endif
	SYB_KeyBookData.KeyExtensionOn = 0;
	for (i = 0; i < SYS_KEY_BOOK_MAX; i++) {
		CMN_ClearCipherKey(i);
	}
	for (i = 0; i < SYS_CIPHERBOX_MAX; i++) {
		CMN_ClearCipherBox(i);
	}
	/* スクランブル解除プリント管理ファイル By Y.Suzuki 1998/01/12 */
	SYB_CipherPrintItem= SYS_MEM_FILE_EMPTY;
	SYB_CipherPrintNo = 20;/* 0 から９まで入り得ない値でクリアとする */
	for (i = 0; i < SYS_CIPHERBOX_MAX; i ++) {
		SYB_CPH_RxPrint[i].Status = SYS_MCOPY_EMPTY;
	}
	/* スクランブル関連ここまで */

	SYB_ScannerTransportMode = FALSE;

	/*--------------------------------------*
	 * 消耗品発注用紙プリント要求の初期化	*
	 *--------------------------------------*/
	SYB_ConsumerOrderListRequest = 0;

#if (0)	/* サービスファンクションから起動するように変更 by K.Watanabe 1997/12/22 */
//	/*--------------------------------------*
//	 * 消耗品発注データの初期化				*
//	 *--------------------------------------*/
//	CMN_ClearConsumerOrderData();
#endif

	/*--------------------------------------*
	 * 消耗品発注データの初期化				*
	 *--------------------------------------*/
#if (PRO_PRINT_TYPE == LED)
	SYB_DrumFuseCutRequest = 0;	/* By M.Tachibana 1997/10/13 */
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
	/*----------------------------------------*/
	/* ダイアルアップ型　インターネットＦＡＸ */
	/*----------------------------------------*/
	MailComAllRamClear();

	/*1998/07/06 Eguchi *//*とりあえずここにも初期化のパスを入れておく*/
	SYB_INF_DeviceExist = FALSE;
	INF_AccessUserData = 0xFF;
	/*INF_SerialSpeed = CHK_UNI_INF_Baudrate(); 1998/07/06 Eguchi */
	INF_SerialSpeed = 1; /*1998/07/06 Eguchi */

#endif

#if (PRO_CL1_TELFAX_LAN == ENABLE)	/*　ANZUより S.Fukui Jun 19,1998 */
	SYB_CL1_Salutation = 0;	/* ホストＰＣの種別をクリア */
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)
	/*--------------------------------------------------------------*
	 * ワープ機能データの初期化		1998/06/15 Add By M.Kuwahara	*
	 *--------------------------------------------------------------*/
	for (i = 0; i < SYS_WARP_MAX; i++) {
		SYB_WarpFile[i].Status		= SYS_WARP_EMPTY;
 #if (0)	/* 1998/10/08 By M.Kuwahara */
//		SYB_WarpFile[i].SubDial[0]	= 0xFF;
//		SYB_WarpFile[i].StartWeek	= SYS_NO_DAY;
//		SYB_WarpFile[i].StartTime	= 0xFFFFFFFF;
//		SYB_WarpFile[i].EndWeek		= SYS_NO_DAY;
//		SYB_WarpFile[i].EndTime		= 0xFFFFFFFF;
 #endif
	}
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/06/15 By M.Kuwahara */
	/*----------------------------------------------------------------------*
	 * ナンバーディスプレイデータの初期化	1998/06/15 Add By M.Kuwahara	*
	 *----------------------------------------------------------------------*/
	SYB_NumberDisplayTel = ND_NO_CONNECTING;			/* 未設続 */
	for (i = 0; i < SYS_ND_MAX; i++) {					/* ＮＤデータクリア */
		SYB_NumberDisplay[i].Dial[0]	= '\0';
		SYB_NumberDisplay[i].Name[0]	= '\0';
		SYB_NumberDisplay[i].WarpData.Status	= SYS_WARP_EMPTY;
 #if (0)	/* 1998/10/08 By M.Kuwahara */
//		SYB_NumberDisplay[i].WarpData.SubDial[0]= 0xFF;
//		SYB_NumberDisplay[i].WarpData.StartWeek	= 0xFF;
//		SYB_NumberDisplay[i].WarpData.StartTime	= 0xFFFFFFFF;
//		SYB_NumberDisplay[i].WarpData.EndWeek	= 0xFF;
//		SYB_NumberDisplay[i].WarpData.EndTime	= 0xFFFFFFFF;
 #endif
	}

 #if (0)	/* ナンバーディスプレイ着信履歴消去はジャーナルデータクリアで行います。By H.Fujimura 1999/02/19 */
 //	/* ナンバーディスプレイ着信履歴消去 by H.Kubo 1998/10/08 */
 //	CMN_ND_EraseAllHistory();
 #endif

	/* ナンバーディスプレイ CAR データ初期化 by H.Kubo 1998/10/12 */
	NCU_ND_InitializeCarPattern();
#endif

#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/17 By M.Kuwahara */
	/*----------------------------------------------------------------------*
	 * キーマクロデータの初期化	1998/06/17 Add By M.Kuwahara				*
	 *----------------------------------------------------------------------*/
	for (i = 0; i < SYS_KEYMACRO_MAX; i++) {					/* キーマクロデータクリア */
		SYB_KeyMacro[i].Step[0] = 0xff;
		SYB_KeyMacro[i].Title[0] = '\0';
	}
#endif

#if (PRO_KEYPANEL == PANEL_SAKAKI)	/* 1998/10/10 H.Yoshikawa */
	/*----------------------------------------------------------------------*
	 * ＬＣＤ濃度の初期化	1998/10/10 H.Yoshikawa							*
	 *----------------------------------------------------------------------*/
	/* 条件を追加 SAKAKI2はファーストクリア以外でＬＣＤ濃度を初期化しない By M.Maeda 2003/03/24 */
	if (mode == 0) {
		SYB_ContrastLCD = CONTRAST_LCD_DEFAULT;
		ContrastLCD_Set();
	}
#endif

#if (PRO_FORVAL_LCR1 == ENABLE) /* By H.Fujimura 2002/07/11 */
	SYB_AreaCode[0] = NULL;
#endif

	/*--------------------------------*
	 * 機種名を記憶する				  *
	 *--------------------------------*/
	for (i = 0; i < SYS_BACKUP_RAM_TEST_AREA_MAX; i ++) {
		SYB_BackupRAM_TestArea[i] = ROM_Revision[i];
	}

	/*------------------------------------*
	 * バックアップテストエリアの初期化	  *
	 *------------------------------------*/
	CMN_InitDRAM_BackupTestArea();	/* By M.Tachibana 1997/10/31 */
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if defined(POPLAR_F) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || (PRO_KEYPANEL == PANEL_HINOKI)	*//* RDC200200635 By O.Kimoto 2003/02/14 */
#if defined(POPLAR_F) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* RDC200200635 By O.Kimoto 2003/02/14 */ /* Add by Y.Kano 2003/07/11 */
 #if (PRO_ALLRAMCLR_WO_MCP == ENABLE) /* ALL RAM Clearの際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	if ((mode == 0) || (mode == 2)){
 #else
	if (mode == 0) { /** バックアップ領域全てを初期化する場合 */
 #endif

		/*-----------------------------------------*
		 * 保守用スイッチをクリア(FROM ROM TABLE)  *
		 * ROMの種類をおぼえる					   *
		 *-----------------------------------------*/
		CMN_InitMaintenanceSwitch();
	}

	if (mode == 0) { /** バックアップ領域全てを初期化する場合 */
		CMN_ClearLifeMonitorData();		/* ライフモニターのクリア 1999/08/11 Y.M */
 #if (defined(POPLAR_H) && defined(JP0)) /* V851 By H.Fujimura 2002/08/30 */  || (defined(SAKAKI) && defined(JP0)) /* F531 By M.Maeda 2002/09/02 */
  #if (PRO_PRINT_TYPE == LED)	/* By M.Tachibana 1997/04/24 */
		CMN_ClearPrinterLifeMonitorData();	/** プリンタライフモニタークリア */
  #endif
		CMN_ClearFaxComErrorMonitorData();	/** 通信エラーモニタークリア By M.Tachibana 1997/06/23 */
		CMN_ClearJournalData();				/** ジャーナルデータクリア */
 #endif
	}
#else
	if (mode == 0) { /** バックアップ領域全てを初期化する場合 */
		/*-----------------------------------------*
		 * 保守用スイッチをクリア(FROM ROM TABLE)  *
		 * ROMの種類をおぼえる					   *
		 *-----------------------------------------*/
		CMN_InitMaintenanceSwitch();
	}
#endif

#if (0)	/* By M.Tachibana 1997/11/27 */
//	/* ＦＣＯＤＥ送信でリセットがかかる件 T.Nose 1997/08/07 */
//	for (i = 0; i < TIMER_MULTI10MS_MAX; i++) {
//		DEBUG_SaveAddressBuffer[i] = 0xFFFFFFFF;
//	}
#endif

	/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
	SYB_Phone2Attribute = 0;


#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/12 Y.Murata */
	for (i = 0; i < SYS_MINOLTA_TEST_FUNC_MAX; i++) {
		SYS_MinoltaTestFuncData[i].Status = SYS_FUNC_TEST_DATA_EMPTY;
		SYS_MinoltaTestFuncData[i].IntervalTimer = 0;
	}
	SYS_MinoltaTestFuncData[0].Status = SYS_FUNC_TEST_DATA_OFF;	/* ０番目は未使用 */
	SYS_MinoltaFuncIntervalTimer = 0;
	SYS_MinoltaFuncPagesData = 0;	/* 1998/07/21 Y.Matsukuma */
#endif


#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
	SYB_LifeMonitorPasscode = 0;  /* lifemonitorbythonda1998/06/01 */
#endif
	
#if defined (KEISATSU) /* 警察FAX 05/10/05 石橋正和 */
	SYB_MachineParameter[M_PARA_SW_I0] = MachineParameterInitialTable[M_PARA_SW_I0];
	SYB_MachineParameter[M_PARA_SW_I1] = MachineParameterInitialTable[M_PARA_SW_I1];
	SYB_MachineParameter[M_PARA_SW_I2] = MachineParameterInitialTable[M_PARA_SW_I2];
	SYB_MachineParameter[M_PARA_SW_I3] = MachineParameterInitialTable[M_PARA_SW_I3];
	SYB_MachineParameter[M_PARA_SW_I4] = MachineParameterInitialTable[M_PARA_SW_I4];
#endif
}


/*************************************************************************
	module		:[オプション専用バックアップデータの初期化]
	function	:[
		1.各オプション機能が専用に使用するデータの初期化を行う。(ROMの種類に依存)
		2.SYS_MemorySwitch[],SYB_MachineParameter[],SYB_MachineUniqSwitch[]
		  SYB_MaintenanceSwitch[],SYB_SettingStatus[]など、サイズ、アドレスは変わらないが
		　内容に変化があるようなデータは該当箇所のみ初期化する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ROM交換した時にSRAMに異常がなく、かつ異なるタイプのROMに交換
				　された時にのみ実行される]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/10/04]
	author		:[江口]
*************************************************************************/
void	CMN_InitializeOptionData(UBYTE mode)
{
	UBYTE	option;
	UBYTE	i;

	/*option = MemorySwitchInitialTable[MEMORY_SW_J9]; 1998/05/25 Eguchi*/

	/*追加されたオプションが使用するRAMのみクリアするよう変更 1998/05/25 Eguchi*/
	option = (MemorySwitchInitialTable[MEMORY_SW_J9] ^ SYS_MemorySwitch[MEMORY_SW_J9]);

	option &= MemorySwitchInitialTable[MEMORY_SW_J9];


	if (option & DPRAM_OPTION_CLASS1) {
	/*----------*/
	/* クラス１ */
	/*----------*/
		/** セッティングステータスの追加分の初期化 */
		SYB_SettingStatus[SETTING_STATUS_5] = SettingStatusInitialTable[SETTING_STATUS_5];

		/** クラス１オプション専用データを初期化 */
		CL1_PCDocumentCode = SYS_MH_CODE;
		CL1_PCDocumentMode = SYS_NORMAL;
		CL1_PCDocumentSize = SYS_DOCUMENT_A4_SIZE;

		/* ローカルスキャン原稿蓄積状態初期化 */
		SYB_CL1_LocalScanDocStatus = 0;

		/*　ローカルプリント原稿管理テーブル初期化 */
		for (i = 0; i < SYS_MEMORY_RX_MAX; i ++) {
			SYB_CL1_MemoryRxPrint[i].Status = SYS_MEMORY_RX_EMPTY;
			SYB_CL1_MemoryRxPrint[i].StorePage = 0;
			SYB_CL1_MemoryRxPrint[i].PrintPage = 1;
			SYB_CL1_MemoryRxPrint[i].ErasePage = 1;
			SYB_CL1_MemoryRxPrint[i].Protect   = SYS_PROTECT_OFF;
		}

		/*　ローカルプリント原稿書き込み位置初期化 */
		CL1_MemoryRxPrintWritePoint = 0;

		/*　ローカルプリント原稿読み出し位置初期化 */
		CL1_MemoryRxPrintReadPoint = 0;
	}

	if (option & DPRAM_OPTION_PRINTER) {
	/*----------*/
	/* プリンタ */
	/*----------*/
		/** セッティングステータスの追加分の初期化 */
		SYB_SettingStatus[PCR_MANUAL_SIZE] = SettingStatusInitialTable[PCR_MANUAL_SIZE];

        SYB_MachineUniqSwitch[UNIQ_SW_H3] &= ~PC_MEMORY_OVER_MESSAGE_PRINT;		/* 98/02/12 By M.Kuwahara */
        SYB_MachineUniqSwitch[UNIQ_SW_H3] |= (UniqSwitchInitialTable[UNIQ_SW_H3] & PC_MEMORY_OVER_MESSAGE_PRINT);
		SYB_MachineUniqSwitch[UNIQ_SW_F9] = UniqSwitchInitialTable[UNIQ_SW_F9];	/* By J.Miyazaki 1997/05/09 */

		/*InitializeDRAM_Parameter(); 1997/11/17 *//* S.Kawasaki 1997/02/19 */

	    /*-----------------------------------------*
		 *　ＰＣプリント原稿管理テーブル初期化     *
	     *-----------------------------------------*/
		SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
		SYB_PcRxPrint.ExecutiveNumber = 0;
		SYB_PcRxPrint.RemainMultiPrintCount = 0;
		SYB_PcRxPrint.StorePage = 0;
		SYB_PcRxPrint.PrintPage = 1;
		SYB_PcRxPrint.ErasePage = 1;
		SYB_PcRxPrint.PrintEndPage = 0;
	}

	if (option & DPRAM_OPTION_288K) {
	/*------------*/
	/* ２８．８Ｋ */
	/*------------*/
		/* ２回線仕様専用データ初期化 */
		CMN_InitializeMultiLineData(mode);

		/* ２回線仕様追加によるバックアップラム領域の一部初期化 */
		CMN_InitializeModelChangeRAM();

		/* ２回線仕様追加によるバックアップラム領域のアップデート */
		CMN_UpdateMultiBackupRAM(mode);
	}

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
	if (option & OPTION_DIALUP_INTERNET_FAX) {
	/*----------------------------------------*/
	/* ダイアルアップ型　インターネットＦＡＸ */
	/*----------------------------------------*/
		MailComAllRamClear();

		/*ﾀﾞｲｱﾙｲﾝﾀｰﾈｯﾄFAX専用ﾒﾓﾘｰｽｲｯﾁ*/ /*1998/05/23 Eguchi */
		SYB_MachineUniqSwitch[UNIQ_SW_I9] = UniqSwitchInitialTable[UNIQ_SW_I9];

		/*1998/05/23 Eguchi */
		SYB_INF_DeviceExist = FALSE;
		INF_AccessUserData = 0xFF;
		/*INF_SerialSpeed = CHK_UNI_INF_Baudrate(); 1998/07/06 Eguchi */
		INF_SerialSpeed = 1; /*1998/07/06 Eguchi */
	}
#endif

	/** オプションのタイプをおぼえておく */
	SYS_MemorySwitch[MEMORY_SW_J9] = MemorySwitchInitialTable[MEMORY_SW_J9];
}



/*************************************************************************
	module		:[異なるオプションのＲＯＭに交換されたか調べる]
	function	:[
		1.SYB_MaintenanceSwitch[MNT_SW_C2](交換される前のＲＯＭ）とMAintenanceSwInitialTable[MNT_SW_C2]
		,（新たに実装されるＲＯＭ）を比較する.
	]
	return		:[
				TRUE :異なるオプションのROMに交換された
				FALSE:同じオプションのROMに交換された
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/10/07]
	author		:[江口]
*************************************************************************/
UBYTE	CMN_CheckOptionChange(void)
{
	if (SYS_MemorySwitch[MEMORY_SW_J9] == MemorySwitchInitialTable[MEMORY_SW_J9]) {
		return (FALSE);
	}
	return (TRUE);
}

/*************************************************************************
	module		:[ワーディング変更用空関数]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[ＳＨ用のワーディングは写像ではないので空関数を定義します。]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/11]
	author		:[川崎]
*************************************************************************/
void	SetWording(UBYTE WordingNumber)
{
	return;	/** 何もしません関数 */
}

/*************************************************************************
	module		:[ワーディングのオフセットを計算]
	function	:[
		1.窓から実体までの差分（バイト数）をセットする。
	]
	return		:[]
	common		:[
					SYS_OPR_WordingOffset
					SYS_LST_WordingOffset
					D2W_WordingHead
					D2W_WordingTail
					PWRD_TAIL
					PWRD_HEAD
				]
	condition	:[]
	comment		:[
				・以下の場面でオフセットを計算する必要がある。
				  1.初期化時。
				  2.ワーディング切り替え時
				　3.ラムクリア時
				]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
#if (0)	/* 未使用なので削除します by K.Watanabe 1998/07/10 */
//void	CalculateWordingOffset(void)
//{
//#if (0)		/*(PRO_CPU == V53)*/
//	/* バンク切り替え方式なので０をセットする */
//	SYS_OPR_WordingOffset = 0;
//	SYS_LST_WordingOffset = 0;
//#endif
//#if (PRO_CPU == SH7043)
//	UWORD	word_size;
//
//	/* オペレーションワーディングサイズを計算 */
///* キャラクタータイプと漢字タイプを分ける By O.Kimoto 1997/06/25 */
//#if (PRO_PANEL == ANK)
//	word_size = (UWORD)(D2W_WordingTail - D2W_WordingHead) + 1;
//#endif
//#if (PRO_PANEL == KANJI)
//	word_size = (UWORD)(D4W_WordingTail - D4W_WordingHead) + 1;
//#endif
//	/* 現在のワーディング番号から実体までのオフセットを計算 */
//	SYS_OPR_WordingOffset = word_size * SYB_WordingNumber; /* T.Nose 1996/06/27 */
//
//	/* リストワーディングサイズを計算 */
//	word_size = (UWORD)(PWRD_TAIL - PWRD_HEAD) + 1;
//	/* 現在のワーディング番号から実体までのオフセットを計算 */
//	SYS_LST_WordingOffset = word_size * SYB_WordingNumber; /* T.Nose 1996/06/27 */
//#endif
//}
#endif

/*************************************************************************
	module		:[マルチ回線仕様関係のバックアップＲＡＭエリアのクリア]
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
	date		:[1996/12/02]
	author		:[村田]
*************************************************************************/
void CMN_InitializeMultiLineData(UBYTE mode)
{
	UWORD	i;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/4 */
	UWORD	internal_line;
#endif


	/* オプションボード用発信元電話番号 By O.Kimoto 1996/11/11 */
	for ( i = 0; i < SYS_OPTION_BOARD_MAX; i ++) {
		SYB_Option_ID_Buffer[i][0] = 0x00;
	}

	/* オプションボード用発信元名(送信原稿先頭付加用) By O.Kimoto 1996/11/11 */
	for ( i = 0; i < SYS_OPTION_BOARD_MAX; i ++ ) {
		SYB_Option_TTI_Buffer[i][0] = 0x00;
	}

	/* オプションボード用発信元名(かなＩＤ用) By M.Tachibana 1997/10/17 */
	for ( i = 0; i < SYS_OPTION_BOARD_MAX; i ++ ) {
		SYB_Option_TTI_ID_Buffer[i][0] = 0x00;
	}

	/* 内線－＞外線発呼用アクセス番号 By O.Kimoto 1996/11/11 */
	if (mode == 1) {
		for (i = 1; i < (SYS_OPTION_BOARD_MAX); i ++ ) {	/* 1997/11/17 BOARD_MAX_MISS */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/4 */
			for (internal_line = 0; internal_line < INTERNAL_LINE_MAX; internal_line++) {
				SYB_PbxAccessNumber[i][internal_line][0] = 0xFF;
			}
#else
			SYB_PbxAccessNumber[i][0] = 0xFF;
#endif
		}
	}
	else {
		for (i = 0; i < (SYS_OPTION_BOARD_MAX); i ++ ) {	/* 1997/11/17 BOARD_MAX_MISS */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/4 */
			for (internal_line = 0; internal_line < INTERNAL_LINE_MAX; internal_line++) {
				SYB_PbxAccessNumber[i][internal_line][0] = 0xFF;
			}
#else
			SYB_PbxAccessNumber[i][0] = 0xFF;
#endif
		}
	}

	/* ポーリング原稿排他処理用変数 By O.Kimoto 1996/11/11 */
	if (SYB_PollingDocumentStatus == 0) {
		SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;	/* ポーリング原稿があるかどうかの変数 */
	}
	else {
		SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;	/* ポーリング原稿があるかどうかの変数 */
	}

	/* オプションボード代行受信ポインター格納バッファ */
	for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		SYB_OptionMemoryRxWritePoint[i] = 0;
	}

	/* オプションボード送信ジャーナルナンバー */
	for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		SYB_OptionJournalTxTotalCount[i] = 1;
		SYB_OptionJournalRxTotalCount[i] = 1;
	}

#if 0
	/* 受信確定時間 */
	SYB_CurrentFaxReceiveTime = 0;
#endif
}




/*************************************************************************
	module		:[ベースモデルからＵＳ７仕様にＲＯＭ交換された時に必要分をクリアする]
	function	:[
		1. ＤＲＡＭをクリアする。
		2. ２回線仕様の関係で、Ｑｕｅｕｅｕと代行受信用の構造体のサイズが変わっている。
		   そのため、必要なＢａｃｋｕｐＲＡＭをクリアする。
		   クリアされるＲＡＭは以下の通り。
		   	 1. SYS_mailBox
		   	 2. SYS_BatchTxFile
		   	 3. SYS_CommandFile
		   	 4. SYS_ExecQueue
		   	 5. ExecQueueWritePoint
		   	 6. ExecQueueReadPoint
		   	 7. SYS_MultiCopyFile
		   	 8. SYS_MultiCopyPoint
		   	 9. MultiCopyWritePoint
		   	10. MultiCopyReadPoint
		   	11. SYS_MemoryRxPrint
		   	12. SYS_MemoryRxPoint
		   	13. MemoryRxPrintWritePoint
		   	14. memoryRxPrintReadPoint
		   	15. SYS_PollingDocumentStatus
		   	16. SYS_DB_PollingDocumentStatus.
		   	17. SYS_PowerDownListStatus.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		この関数はＦ－１２０専用です。
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far CMN_InitializeModelChangeRAM(void){}]
	date		:[1997/02/15]
	author		:[木元修]
*************************************************************************/
void CMN_InitializeModelChangeRAM(void)
{
#if 0	/* KOUBE\ANZUのやつやからいらん 1997/11/14 */
	UBYTE	i;

	/** ＤＲＡＭの初期化処理 */
	InitializeDRAM_Parameter();

	/**  1. SYS_mailBox	clear */
	for (i = 0; i < SYS_MAILBOX_MAX; i ++) {
		if ((SYB_MailBox[i].Status == SYS_MAILBOX_NO_SET)
		|| (SYB_MailBox[i].Status == SYS_MAILBOX_SET)) {

			/* メイルＢＯＸ登録は残す。メッセージ出力のみクリア */
			SYB_MailBox[i].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
		}
		else {	/* SYS_MAILBOX_RECEIVE or SYS_MAILBOX_RECEIVING */

			SYB_MailBox[i].Status = SYS_MAILBOX_SET;
			SYB_MailBox[i].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
		}
	}

	/**  2. SYS_BatchTxFile	clear */
#if (PRO_BATCH_TX == ENABLE)
	for (i = 0; i < SYS_BATCH_FILE_MAX; i ++) {
		CMN_ClearBatchTxFile(i);
	}
#endif

	/**  3. SYS_CommandFile	clear */
	for (i = 0; i < SYS_COM_FILE_MAX; i ++) {
		SYB_CommandFile[i].Status = SYS_CMD_EMPTY;
#if (PRO_F_CODE == ENABLE)	/* 1997/08/08  By T.Yamaguchi */
		SYB_FcodeNumberCDataBuffer[i].SYS_SubAddressNumber[0] = 0xFF;
		SYB_FcodeNumberCDataBuffer[i].SYS_PassWordNumber[0] = 0xFF;
#endif
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/07/07 */
		SYB_CommandStatus[i] = SYS_CMD_EMPTY;
#endif
#if defined (KEISATSU) /* 警察FAX 05/06/22 石橋正和 */
		/* とりあえず初期化しておく */
		SYB_CommandKeisatsu[i].Line = SYS_LINE_KANYU;
		SYB_CommandKeisatsu[i].Scramble = FALSE;
		SYB_CommandKeisatsu[i].Senyo = FALSE;
#endif
	}

	/**  4. SYS_ExecQueue	clear */
	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i ++) {
		SYB_ExecQueue[i].Status = SYS_EXEC_EMPTY;
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/01 */
		SYB_ExecQueueKeisatsu[i].Line = SYS_LINE_KANYU;
		SYB_ExecQueueKeisatsu[i].Scramble = FALSE;
		SYB_ExecQueueKeisatsu[i].Senyo = FALSE;
#endif		/* End of (defined (KEISATSU)) */
	}

	/**  5. ExecQueueWritePoint	clear */
	SYB_ExecQueueWritePoint = 0;	/* 実行待ちﾌｧｲﾙの展開位置 */

	/**  6. ExecQueueReadPoint	clear */
	SYB_ExecQueueReadPoint = 0;
	/* 実行待ちﾌｧｲﾙの実行位置 */

	SYB_ExecQueueSerchPoint = 0;			/* 実行ｷｭｰ検索ﾎﾟｲﾝﾀｰ初期化 1997/10/28 Y.Murata */

	/**  7. SYS_MultiCopyFile	clear */
	for (i = 0; i < SYS_MULTI_COPY_MAX; i ++) {
		SYB_MultiCopyFile[i].Status = SYS_MCOPY_EMPTY;
	}

	/**  8. SYS_MultiCopyPoint	clear */
	/*	SYS_MultiCopyPoint = 0; *//** 今は未使用です。 */

	/**  9. MultiCopyWritePoint	clear */
	SYB_MultiCopyWritePoint = 0;	/* ﾏﾙﾁｺﾋﾟｰ管理ﾌｧｲﾙの展開位置 */

	/** 10. MultiCopyReadPoint	clear */
	SYB_MultiCopyReadPoint = 0;		/* ﾏﾙﾁｺﾋﾟｰ管理ﾌｧｲﾙの実行位置 */

	/** 11. SYS_MemoryRxPrint	clear */
	for (i = 0; i < SYS_MEMORY_RX_MAX; i ++) {
		SYB_MemoryRxPrint[i].Status = SYS_MEMORY_RX_EMPTY;
		SYB_MemoryRxPrint[i].StorePage = 0;	/* 1995/04/20 By M.Tachibana */
		SYB_MemoryRxPrint[i].PrintPage = 1;	/* 1995/04/20 By M.Tachibana */
		SYB_MemoryRxPrint[i].ErasePage = 1;	/* 1995/04/20 By M.Tachibana */
		SYB_MemoryRxPrint[i].Protect   = SYS_PROTECT_OFF;	/* 1995/12/22 Eguchi */
		SYB_MemoryRxPrint[i].JournalPoint = 0;	/* 1996/12/25 */
	}

	/** 12. SYS_MemoryRxPoint	clear */
	/* SYS_MemoryRxPoint = 0; *//** 今は未使用です。 */

	/** 13. MemoryRxPrintWritePoint	clear */
	SYB_MemoryRxPrintWritePoint = 0;	/* ﾒﾓﾘ受信ﾌﾟﾘﾝﾄ管理ﾌｧｲﾙ書き込み位置 */

	/** 14. memoryRxPrintReadPoint	clear */
	SYB_MemoryRxPrintReadPoint = 0;		/* ﾒﾓﾘ受信ﾌﾟﾘﾝﾄ管理ﾌｧｲﾙ実行位置 */

	/** 15. SYS_PollingDocumentStatus	clear */
	SYB_PollingDocumentStatus = 0;

	/** 16. SYS_DB_PollingDocumentStatus.	clear */
	SYB_DB_PollingDocumentStatus = 0;

	/** 17. SYS_PowerDownListStatus.	clear */
	SYB_PowerDownListStatus = 0;

#endif
}



/*************************************************************************
	module		:[マルチ回線用設定値を反映させる]
	function	:[
		1. Ｆ－１２０のベース機からのＲＯＭ交換時、バックアップ領域は保護する
		-  様にしたが、マルチ回線用として、それらの初期値を変更しているところが
		-  有るので、その部分のみアップデートします。
				1.機器設定の初期値
				2.メモリスイッチの初期値
				3.機種固有スイッチの初期値
				4.保守用スイッチの初期値
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		この関数はＦ－１２０専用です。
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far CMN_ModifyBackupRAM(void){}]
	date		:[1997/02/18]
	author		:[木元修]
*************************************************************************/
void CMN_UpdateMultiBackupRAM(UBYTE mode)
{
	UBYTE	tmp_reg1;
	UBYTE	tmp_reg2;
	UBYTE	i;

	/***********************/
	/** 1.機器設定の初期値 */	/* ダイアルタイプ */
	/***********************/
	/*外付け第１*/
	SYB_SettingStatus[SETTING_STATUS_0] &= ~(DIAL_SPEED_20PPS_1 | LINE_TYPE_TONE_1);
	SYB_SettingStatus[SETTING_STATUS_0] |= (CTRY_InitPhoneType() << 2);

	/*外付け第２*/
	SYB_SettingStatus[SETTING_STATUS_0] &= ~(DIAL_SPEED_20PPS_2 | LINE_TYPE_TONE_2);
	SYB_SettingStatus[SETTING_STATUS_0] |= (CTRY_InitPhoneType() << 4);

	/*外付け第３*/
	SYB_SettingStatus[SETTING_STATUS_28] &= ~(DIAL_SPEED_20PPS_3 | LINE_TYPE_TONE_3);
	SYB_SettingStatus[SETTING_STATUS_28] |= CTRY_InitPhoneType();

	/*外付け第４*/
	SYB_SettingStatus[SETTING_STATUS_28] &= ~(DIAL_SPEED_20PPS_4 | LINE_TYPE_TONE_4);
	SYB_SettingStatus[SETTING_STATUS_28] |= (CTRY_InitPhoneType() << 2);

	/*外付け第５*/
	SYB_SettingStatus[SETTING_STATUS_28] &= ~(DIAL_SPEED_20PPS_5 | LINE_TYPE_TONE_5);
	SYB_SettingStatus[SETTING_STATUS_28] |= (CTRY_InitPhoneType() << 4);

	/*外付け第６*/
	SYB_SettingStatus[SETTING_STATUS_29] &= ~(DIAL_SPEED_20PPS_6 | LINE_TYPE_TONE_6);
	SYB_SettingStatus[SETTING_STATUS_29] |= CTRY_InitPhoneType();

	/*外付け第７*/
	SYB_SettingStatus[SETTING_STATUS_29] &= ~(DIAL_SPEED_20PPS_7 | LINE_TYPE_TONE_7);
	SYB_SettingStatus[SETTING_STATUS_29] |= (CTRY_InitPhoneType() << 2);

	/*外付け第８*/
	SYB_SettingStatus[SETTING_STATUS_29] &= ~(DIAL_SPEED_20PPS_8 | LINE_TYPE_TONE_8);
	SYB_SettingStatus[SETTING_STATUS_29] |= (CTRY_InitPhoneType() << 4);

	/*****************************/
	/** 2.メモリスイッチの初期値 */	/* 内線/外線設定 */
	/*****************************/
	/*Ａ:送信 2*/
	SYS_MemorySwitch[MEMORY_SW_A2] = MemorySwitchInitialTable[MEMORY_SW_A2];

	/*******************************/
	/** 3.機種固有スイッチの初期値 */	/* 送信/受信設定 */
	/*******************************/
	/*A:ダイヤラ 0-9*/
	if (mode == 1) {
		tmp_reg1 = SYB_MachineUniqSwitch[UNIQ_SW_A7];
		tmp_reg1 &= 0x03;
		tmp_reg2 = UniqSwitchInitialTable[UNIQ_SW_A7];
		tmp_reg2 &= 0xFC;
		SYB_MachineUniqSwitch[UNIQ_SW_A7] = (UBYTE)(tmp_reg1 | tmp_reg2);
	}
	else {
		SYB_MachineUniqSwitch[UNIQ_SW_A7] = UniqSwitchInitialTable[UNIQ_SW_A7];
	}
	SYB_MachineUniqSwitch[UNIQ_SW_A8] = UniqSwitchInitialTable[UNIQ_SW_A8];
	SYB_MachineUniqSwitch[UNIQ_SW_A9] = UniqSwitchInitialTable[UNIQ_SW_A9];

	/****************************/
	/* 4.保守用スイッチの初期値 */
	/****************************/
	/* 現状で該当スイッチは有りません。*/
}

/*************************************************************************
	module		:[バックアップDRAMを初期化するか/しないか]
	function	:[
		1.
	]
	return		:[TRUE :初期化しない(バックアップDRAMが有効)
				  FALSE:初期化する(バックアップDRAMが無効)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/31]
	author		:[橘正樹]
*************************************************************************/
UBYTE	CMN_CheckDRAM_BackupTestArea(void)
{
	UBYTE	i;

	for (i = 0; i < SYS_DRAM_BACKUP_TEST_AREA_MAX; i++) {
		if (SYB_DRAM_BackupTestArea[i] != ((UBYTE)(i << 4) + i)) {
			return(FALSE);
		}
	}
	return(TRUE);
}

/*************************************************************************
	module		:[バックアップDRAMのテストエリアを初期化する]
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
	date		:[1997/10/31]
	author		:[橘正樹]
*************************************************************************/
void	CMN_InitDRAM_BackupTestArea(void)
{
	UBYTE	i;

	for (i = 0; i < SYS_DRAM_BACKUP_TEST_AREA_MAX; i++) {
		SYB_DRAM_BackupTestArea[i] = ((UBYTE)(i << 4) + i);
	}
}

#if defined(SATSUKI2) || defined(HINOKI2) || defined(HINOKI3)	/* Add by Y.Kano 2004/01/14 */
/*************************************************************************
	module		:[新機能チェック]
	function	:[
		1.	以前のROMの状態と新しいROMの状態を比較する
		.	  以前のROMの状態…SYB_SystemSettingStatus
		.	  新しいROMの状態…SystemSettingStatusInitialTable
		2.	なし(0)からあり(1)に変化したオプションを探す
		3.	チェック後にSettingStatusInitialTableを
		.	SYB_SystemSettingStatusへコピーする
		*	このチェックは一回目のみ有効
	]
	return		:[
		追加された機能に対応するbitが"1"になる
		(status.h参照)
	]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[2004/01/07]
	author		:[加納義彦]
*************************************************************************/
void	CMN_CheckNewFunction(void)		/* 目的のSettingStatus */
{
	UBYTE	old_data;
	UBYTE	new_data;

	old_data = SYB_SettingStatus[SETTING_STATUS_31];			/* 以前の状態 */
	new_data = SettingStatusInitialTable[SETTING_STATUS_31];	/* 新しいROMの状態 */

	/*
	** 以前の状態(RAM)が0で新しい状態(ROM)が1に変化していれば付けられたと判断して
	** 対応するbitを立てる
	*/
	/* 0から１に変わった時 */
	if (!(old_data & NEW_SENSOR_SETIING)
	&&	(new_data & NEW_SENSOR_SETIING)) {
#if defined(HINOKI2) || defined(HINOKI3)	/* F351用新機能チェック追加 by Y.Kano 2004/04/01 */
		/* F351用PS2センサー調整機能追加により追加データの初期化を行います */
		SYB_MachineParameter[M_PARA_SW_J4] = MachineParameterInitialTable[M_PARA_SW_J4];	/* ＰＳ２センサー 仮想スライス２（Ｖｓｉｍ２）	*/
		SYB_MachineParameter[M_PARA_SW_J6] = MachineParameterInitialTable[M_PARA_SW_J6];	/* ＰＳ２センサー 実スライスレベル値（Ｖｓ）	*/
#else
		/* F250用A/Dセンサー調整機能追加により追加データの初期化を行います */
		SYB_MachineParameter[M_PARA_SW_J6] = MachineParameterInitialTable[M_PARA_SW_J6];	/* ＰＳ１センサー 閾値設定値用 */
		SYB_MachineParameter[M_PARA_SW_J7] = MachineParameterInitialTable[M_PARA_SW_J7];	/* ＰＢ４センサー 閾値設定値用 */
#endif
	}

	/** 新しいROMの状態をRAMへコピーする */
	SYB_SettingStatus[SETTING_STATUS_31] = new_data;

}
#endif	/* End of defined(SATSUKI2) || defined(HINOKI2) */

