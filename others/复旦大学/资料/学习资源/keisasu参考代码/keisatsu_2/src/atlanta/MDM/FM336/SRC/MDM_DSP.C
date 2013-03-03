/*----------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                   */
/*  ファイル名   : mdm_dsp.c                                                  */
/*  作成者       :                                                            */
/*  日  付       : 1999/10/06                                                 */
/*  概  要       : Ｒｏｃｋｗｅｌｌ Ｒ２８８ＦモデムＩ／Ｏドライバー          */
/*  修正履歴     :                                                            */
/*	keyword		 :[MDM]                                                       */
/*	machine		 :[SH7043,V53]                                                */
/*	language	 :[MS-C(Ver.6.0)]                                             */
/*----------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\param.h"		/* 1997/03/28 Y.Murata */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_conf.h" /* for FM336 CONF value. Added by H. Kubo 1997/06/19 *//* 99/07/06 Mod. by J.Kishida */

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"

/*******
** ext_v
*******/
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"		/* 1997/03/28 Y.Murata */
#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))	/* Add By O.Kimoto 2002/10/15 */
#include "\src\atlanta\sh7043\ext_v\extv_mon.h"
#endif

#if (0) /* (PRO_MODEM == R288F) */ /* added by H.Kubo 1997/12/18 */
/* POPLAR_H では、コードサイズを小さくする最適化コンパイルをしますが、
** そのままだと大量のスタックを消費します。そこで以下の #pragma によって
** 関数先頭での不要なレジスタ待避をさけます。
** (SuperH RISC engine ファミリ C コンパイラ編 2-34 参照)
** 1997/12/18 H.Kubo 
*/
#pragma noregalloc(MDM_SetTone_A_Filter_B1_A3,MDM_SetTone_A_Filter_B1_A2)
#pragma noregalloc(MDM_SetTone_A_Filter_B1_A1,MDM_SetTone_A_Filter_B1_B2)
#pragma noregalloc(MDM_SetTone_A_Filter_B1_B1,MDM_SetTone_A_Filter_B2_A3)
#pragma noregalloc(MDM_SetTone_A_Filter_B2_A2,MDM_SetTone_A_Filter_B2_A1)
#pragma noregalloc(MDM_SetTone_A_Filter_B2_B2,MDM_SetTone_A_Filter_B2_B1)
#pragma noregalloc(MDM_SetTone_B_Filter_B1_A3,MDM_SetTone_B_Filter_B1_A2)
#pragma noregalloc(MDM_SetTone_B_Filter_B1_A1,MDM_SetTone_B_Filter_B1_B2)
#pragma noregalloc(MDM_SetTone_B_Filter_B1_B1,MDM_SetTone_B_Filter_B2_A3)
#pragma noregalloc(MDM_SetTone_B_Filter_B2_A2,MDM_SetTone_B_Filter_B2_A1)
#pragma noregalloc(MDM_SetTone_B_Filter_B2_B2,MDM_SetTone_B_Filter_B2_B1)
#pragma noregalloc(MDM_SetTone_C_Filter_B1_A3,MDM_SetTone_C_Filter_B1_A2)
#pragma noregalloc(MDM_SetTone_C_Filter_B1_A1,MDM_SetTone_C_Filter_B1_B2)
#pragma noregalloc(MDM_SetTone_C_Filter_B1_B1,MDM_SetTone_C_Filter_B2_A3)
#pragma noregalloc(MDM_SetTone_C_Filter_B2_A2,MDM_SetTone_C_Filter_B2_A1)
#pragma noregalloc(MDM_SetTone_C_Filter_B2_B2,MDM_SetTone_C_Filter_B2_B1)
#pragma noregalloc(MDM_SetTone_P_Filter_B1_A3,MDM_SetTone_P_Filter_B1_A2)
#pragma noregalloc(MDM_SetTone_P_Filter_B1_A1,MDM_SetTone_P_Filter_B1_B2)
#pragma noregalloc(MDM_SetTone_P_Filter_B1_B1,MDM_SetTone_P_Filter_B2_A3)
#pragma noregalloc(MDM_SetTone_P_Filter_B2_A2,MDM_SetTone_P_Filter_B2_A1)
#pragma noregalloc(MDM_SetTone_P_Filter_B2_B2,MDM_SetTone_P_Filter_B2_B1)
#pragma noregalloc(MDM_setTone_A_LPFBK,MDM_SetTone_A_LPGAIN)
#pragma noregalloc(MDM_SetTone_A_THRESHU,MDM_SetTone_A_THRESHL)
#pragma noregalloc(MDM_setTone_B_LPFBK,MDM_SetTone_B_LPGAIN)
#pragma noregalloc(MDM_SetTone_B_THRESHU,MDM_SetTone_B_THRESHL)
#pragma noregalloc(MDM_setTone_C_LPFBK,MDM_SetTone_C_LPGAIN)
#pragma noregalloc(MDM_SetTone_C_THRESHU,MDM_SetTone_C_THRESHL)
#pragma noregalloc(MDM_SetFiterCoefficient)
#endif /* (PRO_MODEM == R288F) */

/*************************************************************************
	module		:[モデムＤＳＰＲＡＭ書き込みアクセス  Ｍｅｔｈｏｄ１]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		1996/05/16 ＤＳＰ－ＲＡＭへの書き込み時はＲｅａｄ＆Ｗｒｉｔｅが基本となる為
		          （ロックウェルＭｒ．Ｓ．Ｐａｌｍより）Ｒｅａｄしたデータのマスク情報を引数に追加）
	]
	ProtoType	:[void far DspRamAccessWriteMethod1(UWORD, UBYTE, UBYTE){}]
	date		:[1995/11/13]
	author		:[木元　修]
*************************************************************************/
void far DspRamAccessWriteMethod1(UWORD address, UBYTE data, UBYTE mask_data)
{
	UBYTE upper_address;
	UBYTE lower_address;
	UBYTE dummy_counter;	/*  by O.Kimoto 1996/03/06 */
	UBYTE read_data;	/* ＤＳＰ－ＲＡＭはＲｅａｄ＆Ｗｒｉｔｅ Ａｃｃｅｓｓの為 By O.Kimoto 1996/05/16 */
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/

#if (0)
** 	/* ＤＳＰ－ＲＡＭのアクセス時間が長すぎる為に、プリンターで不具合が発生する為
** 	** マスクデータが”００００”の時は、Ｒｅａｄ＆Ｗｒｉｔｅアクセスを止めます。
** 	** By O.Kimoto 1998/04/27
** 	*/
** 	/* ＤＳＰ－ＲＡＭはＲｅａｄ＆Ｗｒｉｔｅ Ａｃｃｅｓｓの為 By O.Kimoto 1996/05/16 */
** 	read_data = DspRamAccessReadMethod1(address);
** 	read_data &= mask_data;
** 	read_data |= data;
#else
	if (mask_data != (UBYTE)0x00) {
		read_data = DspRamAccessReadMethod1(address);
		read_data &= mask_data;
		read_data |= data;
	}
	else {
		read_data = data;
	}
#endif
	
	/**************************************************
	** ＷＯＲＤ型のアドレス情報を上位・下位に分割する。
	**************************************************/
	upper_address = (UBYTE)((UBYTE)(address / 0x100) & 0x0f);
	lower_address = (UBYTE)(address % 0x100);

	/*
	** このパスを通るのは
	** ４８０２Ｈ：ＮＥＷＣ強制ＯＦＦ処理
	** ４８０３Ｈ：Ｖ．２７ｔｅｒ　２４００ｂｐｓ　ｎｏｎ－ＥＣＭ時
	** の２通りです。
	** By O.Kimoto 1996/12/18
	*/
	if ((address & 0xFF00) == 0x4800) {
		upper_address |= IO_BIT_4800;
	}
	
	MDM_SetIO(POS_MEMW,ON);
	
	MDM_SetIO(POS_MEADDH,upper_address);
	
	MDM_SetIO(POS_MEADDL,lower_address);
	
	MDM_SetIO(POS_MEDAL,read_data);	/* Change data to read_data By O.Kimoto 1996/05/16 */

	MDM_SetIO(POS_MEACC,ON);
	
#ifdef MDM_LOOP_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	MDM_CheckBitMEACC();
#else
	while((inp(MDM_REG_1D_PORT) & IO_BIT_MEACC)) {
		/* wai_tsk(1);  by O.Kimoto 1996/03/06 */
		if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
			/* wai_tsk(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
		}
		dummy_counter ++;	/*  by O.Kimoto 1996/03/06 */
	}
#endif
	
	MDM_SetIO(POS_4800,OFF);

	MDM_SetIO(POS_MEMW,OFF);
}

/*************************************************************************
	module		:[モデムＤＳＰＲＡＭ読み込みアクセス  Ｍｅｔｈｏｄ１]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[UBYTE far DspRamAccessReadMethod1(UWORD ){}]
	date		:[1995/11/13]
	author		:[木元　修]
*************************************************************************/
UBYTE  DspRamAccessReadMethod1(UWORD address)
{
	UBYTE upper_address;
	UBYTE lower_address;
	UBYTE data;

	/*
	** R288F VERSION 24P以降の場合
	** For time-up in dead loop by H.Kubo 1998/11/16
	*/
	UWORD dummy_counter;

	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/

	/** ＷＯＲＤ型のアドレス情報を上位・下位に分割する。 **/
	upper_address = (UBYTE)((UBYTE)(address / 0x100) & 0x0f);
	lower_address = (UBYTE)(address % 0x100);

	/* このパスを通るのは
	** ４８０２Ｈ：ＮＥＷＣ強制ＯＦＦ処理
	** ４８０３Ｈ：Ｖ．２７ｔｅｒ　２４００ｂｐｓ　ｎｏｎ－ＥＣＭ時
	** の２通りです。
	** By O.Kimoto 1996/12/18
	*/
	if (( address & 0xFF00 ) == 0x4800 ) {
		upper_address |= IO_BIT_4800;
	}

	MDM_SetIO( POS_MEMW, OFF );

	MDM_SetIO( POS_MEADDH, upper_address );

	MDM_SetIO( POS_MEADDL, lower_address );

	MDM_SetIO( POS_MEACC, ON );

	/*
	** R288F VERSION 24P以降の場合
	** For time-up in dead loop by H.Kubo 1998/11/16
	*/
	dummy_counter = 0;

	while(( inp( MDM_REG_1D_PORT ) & IO_BIT_MEACC )) {
		/* wai_tsk(1); by O.Kimoto 1996/03/06 */
		if ( int_enable ) {	/**割り込み禁しに変更時、割り込み許可中だった*/
			/* wai_tsk(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
		}
		dummy_counter ++;	/*  by O.Kimoto 1996/03/06 */

		/*
		** R288F VERSION 24P以降の場合
		** For time-up in dead loop by H.Kubo 1998/11/16
		*/
		if ( dummy_counter == 0 ) {
			break;
		}

	}

	data = ( UBYTE )( MDM_GetIO( POS_MEDAL ));

	MDM_SetIO( POS_4800, OFF );

	return( data );
}

/*************************************************************************
	module		:[モデムＤＳＰＲＡＭ書き込みアクセス  Ｍｅｔｈｏｄ２]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		1996/05/16 ＤＳＰ－ＲＡＭへの書き込み時はＲｅａｄ＆Ｗｒｉｔｅが基本となる為
		          （ロックウェルＭｒ．Ｓ．Ｐａｌｍより）Ｒｅａｄしたデータのマスク情報を引数に追加
	]
	ProtoType	:[void far DspRamAccessWriteMethod2(UWORD, UWORD, UWORD, UWORD ){}]
	date		:[1995/11/13]
	author		:[木元　修]
*************************************************************************/
void  DspRamAccessWriteMethod2(UWORD lsb_address, UWORD msb_address, UWORD data, UWORD mask_data)
{
	UBYTE upper_address;
	UBYTE lower_address;
	UBYTE msb_data;
	UBYTE lsb_data;
	UBYTE dummy_counter;	/*  by O.Kimoto 1996/03/06 */
	UWORD read_data;	/* ＤＳＰ－ＲＡＭはＲｅａｄ＆Ｗｒｉｔｅ Ａｃｃｅｓｓの為 By O.Kimoto 1996/05/16 */
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/

#if (0)
** 	/* ＤＳＰ－ＲＡＭのアクセス時間が長すぎる為に、プリンターで不具合が発生する為
** 	** マスクデータが”００００”の時は、Ｒｅａｄ＆Ｗｒｉｔｅアクセスを止めます。
** 	** By O.Kimoto 1998/04/27
** 	*/
** 	/* ＤＳＰ－ＲＡＭはＲｅａｄ＆Ｗｒｉｔｅ Ａｃｃｅｓｓの為 By O.Kimoto 1996/05/16 */
** 	read_data = DspRamAccessReadMethod2(lsb_address, msb_address);
** 	read_data &= mask_data;
** 	read_data |= data;
#else
	if (mask_data != (UWORD)0x0000) {
		read_data = DspRamAccessReadMethod2(lsb_address, msb_address);
		read_data &= mask_data;
		read_data |= data;
	}
	else {
		read_data = data;
	}
#endif
	
	/**************************************************
	** ＷＯＲＤ型のアドレス情報を上位・下位に分割する。
	**************************************************/
	upper_address = (UBYTE)((UBYTE)(lsb_address / 0x100) & 0x0f);
	lower_address = (UBYTE)(lsb_address % 0x100);
	
	/************************************************
	** ＷＯＲＤ型のデータ情報を上位・下位に分割する。
	************************************************/
	msb_data = (UBYTE)(read_data / 0x100);
	lsb_data = (UBYTE)(read_data % 0x100);
	
	MDM_SetIO(POS_MEMW,ON);
	
	MDM_SetIO(POS_MEADDH,upper_address);
	
	MDM_SetIO(POS_MEADDL,lower_address);
	
	MDM_SetIO(POS_MEDAL,lsb_data);
	
	MDM_SetIO(POS_MEACC,ON);

#ifdef MDM_LOOP_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	MDM_CheckBitMEACC();
#else
	while((inp(MDM_REG_1D_PORT) & IO_BIT_MEACC)) {
		/* wai_tsk(1); by O.Kimoto 1996/03/06 */
		if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
			/* wai_tsk(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
		}
		dummy_counter++;	/*  by O.Kimoto 1996/03/06 */
	}
#endif
	
	/**************************************************
	** ＷＯＲＤ型のアドレス情報を上位・下位に分割する。
	**************************************************/
	upper_address = (UBYTE)((UBYTE)(msb_address / 0x100) & 0x0f);
	lower_address = (UBYTE)(msb_address % 0x100);
	
	MDM_SetIO(POS_MEADDH,upper_address);
	
	MDM_SetIO(POS_MEADDL,lower_address);
	
	MDM_SetIO(POS_MEDAL,msb_data);
	
	MDM_SetIO(POS_MEACC,ON);
	
#ifdef MDM_LOOP_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	MDM_CheckBitMEACC();
#else
	while((inp(MDM_REG_1D_PORT) & IO_BIT_MEACC)) {
		/* wai_tsk(1); by O.Kimoto 1996/03/06 */
		if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
			/* wai_tsk(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
		}
		dummy_counter++;	/*  by O.Kimoto 1996/03/06 */
	}
#endif
	
	MDM_SetIO(POS_MEMW,OFF);
}

/*************************************************************************
	module		:[モデムＤＳＰＲＡＭ読み出しアクセス  Ｍｅｔｈｏｄ２]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[UWORD far DspRamAccessReadMethod2(UWORD ,UWORD ){}]
	date		:[1995/11/13]
	author		:[木元　修]
*************************************************************************/
UWORD  DspRamAccessReadMethod2(UWORD lsb_address,UWORD msb_address)
{
	UBYTE upper_address;
	UBYTE lower_address;
	UWORD msb_data;
	UWORD lsb_data;
	UBYTE dummy_counter;	/*  by O.Kimoto 1996/03/06 */
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/

	/**************************************************
	** ＷＯＲＤ型のアドレス情報を上位・下位に分割する。
	**************************************************/
	upper_address = (UBYTE)((UBYTE)(lsb_address / 0x100) & 0x0f);
	lower_address = (UBYTE)(lsb_address % 0x100);
	
	MDM_SetIO(POS_MEMW,OFF);
	
	MDM_SetIO(POS_MEADDH,upper_address);
	
	MDM_SetIO(POS_MEADDL,lower_address);
	
	MDM_SetIO(POS_MEACC,ON);
	
#ifdef MDM_LOOP_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	MDM_CheckBitMEACC();
#else
	while((inp(MDM_REG_1D_PORT) & IO_BIT_MEACC)) {
		/* wai_tsk(1);	 by O.Kimoto 1996/03/06 */
		if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
			/* wai_tsk(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
		}
		dummy_counter++;	/*  by O.Kimoto 1996/03/06 */
	}
#endif
	
	lsb_data = (UWORD)(MDM_GetIO(POS_MEDAL));

	/**************************************************
	** ＷＯＲＤ型のアドレス情報を上位・下位に分割する。
	**************************************************/
	upper_address = (UBYTE)((UBYTE)(msb_address / 0x100) & 0x0f);
	lower_address = (UBYTE)(msb_address % 0x100);
	
	MDM_SetIO(POS_MEADDH,upper_address);
	
	MDM_SetIO(POS_MEADDL,lower_address);
	
	MDM_SetIO(POS_MEACC,ON);
	
#ifdef MDM_LOOP_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	MDM_CheckBitMEACC();
#else
	while((inp(MDM_REG_1D_PORT) & IO_BIT_MEACC)) {
		/* wai_tsk(1);	 by O.Kimoto 1996/03/06 */
		if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
			/* wai_tsk(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
		}
		dummy_counter++;	/*  by O.Kimoto 1996/03/06 */
	}
#endif
	
	msb_data = (UWORD)(MDM_GetIO(POS_MEDAL));

	return((UWORD)(msb_data * 0x100 + lsb_data));
}

/*************************************************************************
	module		:[モデムＤＳＰＲＡＭ書き込みアクセス  Ｍｅｔｈｏｄ３]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		1996/05/16 ＤＳＰ－ＲＡＭへの書き込み時はＲｅａｄ＆Ｗｒｉｔｅが基本となる為
		          （ロックウェルＭｒ．Ｓ．Ｐａｌｍより）Ｒｅａｄしたデータのマスク情報を引数に追加
	]
	ProtoType	:[void far DspRamAccessWriteMethod3(UWORD, UWORD, UWORD ){}]
	date		:[1995/11/13]
	author		:[木元　修]
*************************************************************************/
void  DspRamAccessWriteMethod3(UWORD address, UWORD data, UWORD mask_data)
{
	UBYTE upper_address;
	UBYTE lower_address;
	UBYTE msb_data;
	UBYTE lsb_data;
	UBYTE dummy_counter;	/*  by O.Kimoto 1996/03/06 */
	UWORD read_data;	/* ＤＳＰ－ＲＡＭはＲｅａｄ＆Ｗｒｉｔｅ Ａｃｃｅｓｓの為 By O.Kimoto 1996/05/16 */
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/

#if (0)
** 	/* ＤＳＰ－ＲＡＭのアクセス時間が長すぎる為に、プリンターで不具合が発生する為
** 	** マスクデータが”００００”の時は、Ｒｅａｄ＆Ｗｒｉｔｅアクセスを止めます。
** 	** By O.Kimoto 1998/04/27
** 	*/
** 	/* ＤＳＰ－ＲＡＭはＲｅａｄ＆Ｗｒｉｔｅ Ａｃｃｅｓｓの為 By O.Kimoto 1996/05/16 */
** 	read_data = DspRamAccessReadMethod3(address);
** 	read_data &= mask_data;
** 	read_data |= data;
#else
	if (mask_data != (UWORD)0x0000) {
		read_data = DspRamAccessReadMethod3(address);
		read_data &= mask_data;
		read_data |= data;
	}
	else {
		read_data = data;
	}
#endif
	
	/**************************************************
	** ＷＯＲＤ型のアドレス情報を上位・下位に分割する。
	**************************************************/
	upper_address = (UBYTE)((UBYTE)(address / 0x100) & 0x0f);
	lower_address = (UBYTE)(address % 0x100);
	
	/************************************************
	** ＷＯＲＤ型のデータ情報を上位・下位に分割する。
	************************************************/
	msb_data = (UBYTE)(read_data / 0x100);
	lsb_data = (UBYTE)(read_data % 0x100);
	
	MDM_SetIO(POS_MEMW,ON);
	
	MDM_SetIO(POS_MEADDH,upper_address);
	
	MDM_SetIO(POS_MEADDL,lower_address);
	
	MDM_SetIO(POS_MEDAL,lsb_data);
	
	MDM_SetIO(POS_MEDAM,msb_data);
	
	MDM_SetIO(POS_MEACC,ON);
	
#ifdef MDM_LOOP_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	MDM_CheckBitMEACC();
#else
	while((inp(MDM_REG_1D_PORT) & IO_BIT_MEACC)) {
		/* wai_tsk(1);	 by O.Kimoto 1996/03/06 */
		if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
			/* wai_tsk(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
		}
		dummy_counter++;	/*  by O.Kimoto 1996/03/06 */
	}
#endif
	
	MDM_SetIO(POS_MEMW,OFF);
}

/*************************************************************************
	module		:[モデムＤＳＰＲＡＭ読み込みアクセス  Ｍｅｔｈｏｄ３]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[UWORD far DspRamAccessReadMethod3(UWORD ){}]
	date		:[1995/11/13]
	author		:[木元　修]
*************************************************************************/
UWORD  DspRamAccessReadMethod3(UWORD address)
{
	UBYTE upper_address;
	UBYTE lower_address;
	UWORD msb_data;
	UWORD lsb_data;
	UBYTE dummy_counter;	/*  by O.Kimoto 1996/03/06 */
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/

	/** ＷＯＲＤ型のアドレス情報を上位・下位に分割する。 **/
	upper_address = (UBYTE)((UBYTE)(address / 0x100) & 0x0f);
	lower_address = (UBYTE)(address % 0x100);
	
	MDM_SetIO(POS_MEMW,OFF);
	
	MDM_SetIO(POS_MEADDH,upper_address);
	
	MDM_SetIO(POS_MEADDL,lower_address);
	
	MDM_SetIO(POS_MEACC,ON);
	
#ifdef MDM_LOOP_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	MDM_CheckBitMEACC();
#else
	while((inp(MDM_REG_1D_PORT) & IO_BIT_MEACC)) {
		/* wai_tsk(1);	 by O.Kimoto 1996/03/06 */
		if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
			/* wai_tsk(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
		}
		dummy_counter++;	/*  by O.Kimoto 1996/03/06 */
	}
#endif
	
	lsb_data = (UWORD)(MDM_GetIO(POS_MEDAL));
	
	msb_data = (UWORD)(MDM_GetIO(POS_MEDAM));
	
	return((UWORD)(msb_data * 0x100 + lsb_data));
}

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[モデムＤＳＰＲＡＭ書き込みアクセス  Ｍｅｔｈｏｄ４]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		1996/05/16 ＤＳＰ－ＲＡＭへの書き込み時はＲｅａｄ＆Ｗｒｉｔｅが基本となる為
//		          （ロックウェルＭｒ．Ｓ．Ｐａｌｍより）Ｒｅａｄしたデータのマスク情報を引数に追加
//	]
//	ProtoType	:[void far DspRamAccessWriteMethod4(UWORD, UWORD, UWORD ){}]
//	date		:[1995/11/13]
//	author		:[木元　修]
//*************************************************************************/
//void  DspRamAccessWriteMethod4(UWORD address, UWORD data, UWORD mask_data)
//{
//	UBYTE upper_address;
//	UBYTE lower_address;
//	UBYTE msb_data;
//	UBYTE lsb_data;
//	UBYTE dummy_counter;	/*  by O.Kimoto 1996/03/06 */
//	UWORD read_data;	/* ＤＳＰ－ＲＡＭはＲｅａｄ＆Ｗｒｉｔｅ Ａｃｃｅｓｓの為 By O.Kimoto 1996/05/16 */
//	UWORD int_enable;
//
//	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
//
//	/* ＤＳＰ－ＲＡＭはＲｅａｄ＆Ｗｒｉｔｅ Ａｃｃｅｓｓの為 By O.Kimoto 1996/05/16 */
//	read_data = DspRamAccessReadMethod4(address);
//	read_data &= mask_data;
//	read_data |= data;
//
//	/** ＷＯＲＤ型のアドレス情報を上位・下位に分割する。 **/
//	upper_address = (UBYTE)((UBYTE)(address / 0x100) & 0x0f);
//	lower_address = (UBYTE)(address % 0x100);
//	
//	/** ＷＯＲＤ型のデータ情報を上位・下位に分割する。 **/
//	msb_data = (UBYTE)(read_data / 0x100);
//	lsb_data = (UBYTE)(read_data % 0x100);
//	
//	MDM_SetIO(POS_MEMW,ON);
//	
//	MDM_SetIO(POS_MEADDH,upper_address);
//	
//	MDM_SetIO(POS_MEADDL,lower_address);
//	
//	MDM_SetIO(POS_MEDAM,msb_data);
//	
//	MDM_SetIO(POS_MEDAL,lsb_data);
//	
//	MDM_SetIO(POS_MEACC,ON);
//	
//	while((inp(MDM_REG_1D_PORT) & IO_BIT_MEACC)) {
//		/* wai_tsk(1);	 by O.Kimoto 1996/03/06 */
//		if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
//			/* wai_tsk(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
//		}
//		dummy_counter++;	/*  by O.Kimoto 1996/03/06 */
//	}
//
//	MDM_SetIO(POS_MEMW,OFF);
//}
#endif

/*************************************************************************
	module		:[モデムＤＳＰＲＡＭ読み込みアクセス  Ｍｅｔｈｏｄ４]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[UWORD far DspRamAccessReadMethod4(UWORD ){}]
	date		:[1995/11/13]
	author		:[木元　修]
*************************************************************************/
UWORD  DspRamAccessReadMethod4(UWORD address)
{
	UBYTE upper_address;
	UBYTE lower_address;
	UWORD msb_data;
	UWORD lsb_data;
	UBYTE dummy_counter;	/*  by O.Kimoto 1996/03/06 */
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/

	/** ＷＯＲＤ型のアドレス情報を上位・下位に分割する。 **/
	upper_address = ( UBYTE )(( UBYTE)( address / 0x100 ) & 0x0f );
	lower_address = ( UBYTE )( address % 0x100 );
	
	MDM_SetIO( POS_MEMW, OFF );
	
	MDM_SetIO( POS_MEADDH, upper_address );
	
	MDM_SetIO( POS_MEADDL, lower_address );
	
	MDM_SetIO( POS_MEACC, ON );
	
#ifdef MDM_LOOP_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	MDM_CheckBitMEACC();
#else
	while(( inp( MDM_REG_1D_PORT ) & IO_BIT_MEACC )) {
		/* wai_tsk(1);	 by O.Kimoto 1996/03/06 */
		if ( int_enable ) {	/**割り込み禁しに変更時、割り込み許可中だった*/
			/* wai_tsk(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
		}
		dummy_counter++;	/*  by O.Kimoto 1996/03/06 */
	}
#endif

	msb_data = ( UWORD )( MDM_GetIO( POS_MEDAM ));

	lsb_data = ( UWORD )( MDM_GetIO( POS_MEDAL ));

	return(( UWORD )( msb_data * 0x100 + lsb_data ));
}



/*************************************************************************
	module		:[モデムＤＳＰＲＡＭアクセスファンクション関数群]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[{}]
	date		:[1995/11/14]
	author		:[木元　修]
*************************************************************************/
/**********************************************************************************************/
/*                                                                          Method	,Address **/
/**********************************************************************************************/
/** RC288DPi **/
/**   1. Transmitter Compromise Equalizer Coefficients **/
	/** First Coefficient Tap												3		,AE8			**/
	/** Last Coefficient Tap												3		,AD0			**/
	/** Number of Taps														3		,B47			**/


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[  3. DTMF Tone Duration]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 218,2DB
//	]
//	ProtoType	:[void far MDM_SetDTMFToneDuration(UWORD ){}]
//	date		:[1995/11/20]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetDTMFToneDuration(UWORD time)
//{
//	DspRamAccessWriteMethod2(0x218, 0x2DB, time, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[  4. DTMF Interdigit Delay]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 219,2DC
//	]
//	ProtoType	:[void far MDM_SetDTMFInterdigitDelay(UWORD ){}]
//	date		:[1995/11/20]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetDTMFInterdigitDelay(UWORD time)
//{
//	DspRamAccessWriteMethod2(0x219, 0x2DC, time, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[  5. DTMF Low Band Power Level]
//	function	:[
//		1.指定されたＤＴＭＦの低群送出レベル番号に従って、テーブルから設定値を選び、
//		- その値をＤＳＰに設定する。
//	]
//	return		:[無し]
//	common		:[
//		DTMF_LevelTable[MDM_DTMF_LVL_MAX];
//	]
//	condition	:[]
//	comment		:[
//		Access Method	: 2(RO)
//		Address			: 29B,29C
//	]
//	ProtoType	:[void far MDM_SetDTMFLowBandPowerLevel(UBYTE ){}]
//	date		:[1995/11/16]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetDTMFLowBandPowerLevel(UBYTE level_no)
//{
//	UWORD level_value;
//	UBYTE country_code;
//
//#if (0)
//** 	/* ＰＯＰＬＡＲ＿Ｈでは内蔵のためマルチ対応は不要 By O.Kimoto 1997/09/10 */
//** 	country_code = SYB_MachineParameter[COUNTRY_CODE];
//#endif
//	country_code = 0;	/* 0 = JPN By O.Kimoto 1997/09/10 */
//
//	level_value = (UWORD)(DTMF_LevelCountryTable[country_code][level_no].LowLevel);
//	DspRamAccessWriteMethod2(0x29B, 0x29C, level_value, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[  6. DTMF High Band Power Level]
//	function	:[
//		1.指定されたＤＴＭＦの高群送出レベル番号に従って、テーブルから設定値を選び、
//		- その値をＤＳＰに設定する。
//	]
//	return		:[]
//	common		:[
//		DTMF_LevelTable[MDM_DTMF_LVL_MAX];
//	]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 29D,29E
//	]
//	ProtoType	:[void far MDM_SetDTMFHighBandPowerLevel(UBYTE ){}]
//	date		:[1995/11/16]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetDTMFHighBandPowerLevel(UBYTE level_no)
//{
//	UWORD level_value;
//	UBYTE country_code;
//
//#if (0)
//** 	/* ＰＯＰＬＡＲ＿Ｈは内蔵のためマルチ対応は不要 By O.Kimoto 1997/09/10 */
//** 	country_code = SYB_MachineParameter[COUNTRY_CODE];
//#endif
//	country_code = 0;	/* 0 = JPN By O.Kimoto 1997/09/10 */
//
//	level_value = (UWORD)(DTMF_LevelCountryTable[country_code][level_no].HighLevel);
//	DspRamAccessWriteMethod2(0x29D, 0x29E, level_value, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[  7. Pulse Relay Make Time]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 22C
//	]
//	ProtoType	:[void far MDM_SetPulseRelayMakeTime(UBYTE ){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetPulseRelayMakeTime(UBYTE time)
//{
//	DspRamAccessWriteMethod1(0x22C, time, 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[  8. Pulse Relay Break Timt]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 21C
//	]
//	ProtoType	:[void far MDM_SetPulseRelayBreakTime(UBYTE ){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetPulseRelayBreakTime(UBYTE time)
//{
//	DspRamAccessWriteMethod1(0x21C, time, 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[  9. Pulse Interdigit Delay]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 21A,21B
//	]
//	ProtoType	:[void far MDM_SetPulseInterdigitDelay(UWORD ){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetPulseInterdigitDelay(UWORD time)
//{
//	DspRamAccessWriteMethod2(0x21A, 0x21B, time, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 10. Calling Tone On Time]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 290,2D9
//	]
//	ProtoType	:[void far MDM_SetCallingToneOnTime(UWORD ){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetCallingToneOnTime(UWORD time)
//{
//	DspRamAccessWriteMethod2(0x290, 0x2D9, time, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 11. Calling Tone Off Time]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 291,2DA
//	]
//	ProtoType	:[void far MDM_SetCallingToneOffTime(UWORD ){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetCallingToneOffTime(UWORD time)
//{
//	DspRamAccessWriteMethod2(0x291, 0x2DA, time, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 12-A. Transmitter Output Level Gain(G)-All Modes]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[
//		TransmitterOutputLevel[];
//	]
//	condition	:[]
//	comment		:[
//		Access Method	: 3
//		Address			: A48
//	]
//	ProtoType	:[void far MDM_SetTxOutputLevelGainAll(UBYTE ){}]
//	date		:[1995/11/16]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetTxOutputLevelGainAll(UBYTE level)
//{
//	UWORD level_value;
//	
//	level_value = (UWORD)(TxOutputLevelAll[level]);
//	DspRamAccessWriteMethod3(0x0A48, level_value, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 12-B: Transmitter Output Level Gain(G)-FSK Modes]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[
//		mode 	: Answer = 0		Originate = 1
//		level	: 0 ～ -21= 0 ～ 21
//	]
//	comment		:[
//		Access Method	: 3
//		Address			: B57
//	]
//	ProtoType	:[void far MDM_SetTxOutputLevelGainFSK(UBYTE ,UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetTxOutputLevelGainFSK(UBYTE mode,UBYTE level)
//{
//	UWORD	level_value;
//	
//	if (MDM_REG_05_PortStatus & IO_BIT_CEQ) {
//		level_value = TxOutputLevelFSK[1][mode][level];
//	}
//	else {
//		level_value = TxOutputLevelFSK[0][mode][level];
//	}
//	DspRamAccessWriteMethod3(0xB57, level_value, 0x0000);
//}
#endif

/*************************************************************************
	module		:[ 13. Dual Tone 1 Frequency]
	function	:[
		1.
	]
	return		:[]
	common		:[
		DTMF_FrequencyTable[];
	]
	condition	:[]
	comment		:[
		Access Method	: 2
		Address			: 280,281
	]
	ProtoType	:[void far MDM_SetDualTone1Frequency(UBYTE ){}]
	date		:[1995/11/16]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetDualTone1Frequency(UWORD freq_value)
{
	DspRamAccessWriteMethod2(0x280, 0x281, freq_value, 0x0000);

}


/*************************************************************************
	module		:[ 14. Dual Tone 2 Frequency]
	function	:[
		1.
	]
	return		:[]
	common		:[
		DTMF_FrequencyTable[]
	]
	condition	:[]
	comment		:[
		Access Method	: 2
		Address			: 282,283
	]
	ProtoType	:[void far MDM_SetDualTone2Frequency(UBYTE ){}]
	date		:[1995/11/16]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetDualTone2Frequency(UWORD freq_value)
{
	DspRamAccessWriteMethod2(0x282, 0x283, freq_value, 0x0000);
}


/*************************************************************************
	module		:[ 15. Dual Tone 1 Power Level]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 2
		Address			: 284,285
	]
	ProtoType	:[void far MDM_SetDualTone1PowerLevel(UBYTE ){}]
	date		:[1995/11/16]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetDualTone1PowerLevel(UWORD level_value)
{
	DspRamAccessWriteMethod2(0x284, 0x285, level_value, 0x0000);
}


/*************************************************************************
	module		:[ 16. Dual Tone 2 Power Level]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 2
		Address			: 286,287
	]
	ProtoType	:[void far MDM_SetDualTone2PowerLevel(UBYTE ){}]
	date		:[1995/11/16]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetDualTone2PowerLevel(UWORD level_value)
{
	DspRamAccessWriteMethod2(0x286, 0x287, level_value, 0x0000);
}


/*************************************************************************
	module		:[17A-a. New Status(NEWS) Masking Registers for 01]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 247
	]
	ProtoType	:[void far MDM_SetMaskingRegsiter01(UBYTE,UBYTE){}]
	date		:[1996/01/22]
	author		:[木元修]
*************************************************************************/
void  MDM_SetMaskingRegsiter01(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x247, mask_data, 0xF9);
}


/*************************************************************************
	module		:[17A-b. New Status(NEWS) Masking Registers for 01]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 2
		Address			: 246,245
	]
	ProtoType	:[void far MDM_SetMaskingRegsiter0A0B(UBYTE){}]
	date		:[1996/01/22]
	author		:[木元修]
*************************************************************************/
void  MDM_SetMaskingRegsiter0A0B(UWORD mask_data)
{
	DspRamAccessWriteMethod2((UWORD)0x246, (UWORD)0x0245, mask_data, 0x0400);
}


/*************************************************************************
	module		:[17A-c. New Status(NEWS) Masking Registers for 0C & 0D]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 2
		Address			: 244,243
	]
	ProtoType	:[void far MDM_SetMaskingRegsiter0C0D(UWORD){}]
	date		:[1996/01/22]
	author		:[木元修]
*************************************************************************/
void  MDM_SetMaskingRegsiter0C0D(UWORD mask_data)
{
	DspRamAccessWriteMethod2((UWORD)0x244, (UWORD)0x0243, mask_data, 0x0000);
}


/*************************************************************************
	module		:[17A-d. New Status(NEWS) Masking Registers for 0E & 0F]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 2
		Address			: 242,241
	]
	ProtoType	:[void far MDM_SetMaskingRegsiter0E0F(UWORD){}]
	date		:[1996/01/22]
	author		:[木元修]
*************************************************************************/
void  MDM_SetMaskingRegsiter0E0F(UWORD mask_data)
{
	DspRamAccessWriteMethod2((UWORD)0x242, (UWORD)0x0241, mask_data, 0x0000);
}


/*************************************************************************
	module		:[17A-e. New Status(NEWS) Masking Registers for 12]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 089 (bit 7)
	]
	ProtoType	:[void far MDM_SetMaskingRegsiter12(UBYTE ){}]
	date		:[1996/01/22]
	author		:[木元修]
*************************************************************************/
void  MDM_SetMaskingRegsiter12(UBYTE sw)
{
	MDM_DSP_RAM_089_Status = DspRamAccessReadMethod1(0x089);

	if (sw == TRUE) {	/* Changed by H. Kubo 1997/06/23 */
		MDM_DSP_RAM_089_Status |= MDM_BIT_7;
	}
	else {
		MDM_DSP_RAM_089_Status &= ~MDM_BIT_7;
	}
	
	DspRamAccessWriteMethod1(0x089, MDM_DSP_RAM_089_Status, 0x7F);
}


/*************************************************************************
	module		:[17A-f. New Status(NEWS) Masking Registers for 14]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 38A
	]
	ProtoType	:[void far MDM_SetMaskingRegsiter14(UBYTE ){}]
	date		:[1996/01/22]
	author		:[木元修]
*************************************************************************/
void  MDM_SetMaskingRegsiter14(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x38A, mask_data, 0x00);
}


/*************************************************************************
	module		:[17A-g. New Status(NEWS) Masking Registers for 16]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 370
	]
	ProtoType	:[void far MDM_SetMaskingRegsiter16(UBYTE ){}]
	date		:[1996/01/22]
	author		:[木元修]
*************************************************************************/
void  MDM_SetMaskingRegsiter16(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x370, mask_data, 0x00);
}


/*************************************************************************
	module		:[17A-h. New Status(NEWS) Masking Registers for 17]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 371
	]
	ProtoType	:[void far MDM_SetMaskingRegsiter17(UBYTE ){}]
	date		:[1996/01/22]
	author		:[木元修]
*************************************************************************/
void  MDM_SetMaskingRegsiter17(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x371, mask_data, 0x00);
}


/*************************************************************************
	module		:[17A-i. New Status(NEWS) Masking Registers for 1A & 1B]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 2
		Address			: 27D,27C
	]
	ProtoType	:[void far MDM_SetMaskingRegsiter1A1B(UWORD ){}]
	date		:[1996/01/22]
	author		:[木元修]
*************************************************************************/
void  MDM_SetMaskingRegsiter1A1B(UWORD mask_data)
{
	DspRamAccessWriteMethod2((UWORD)0x27D, (UWORD)0x027C, mask_data, 0x00F1);
}


/*************************************************************************
	module		:[17B. Memory Access Masking Register]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 089 (bit 6)
	]
	ProtoType	:[void far MDM_SetMemoryAccessMaskingRegsiter(UBYTE ){}]
	date		:[1996/01/22]
	author		:[木元修]
*************************************************************************/
void  MDM_SetMemAccMaskingRegsiter(UBYTE sw)
{
	MDM_DSP_RAM_089_Status = DspRamAccessReadMethod1(0x089);

	if (sw == TRUE) { /* Chnaged by H. Kubo 1997/06/23 */
		MDM_DSP_RAM_089_Status |= MDM_BIT_6;
	}
	else {
		MDM_DSP_RAM_089_Status &= ~MDM_BIT_6;
	}
	
	DspRamAccessWriteMethod1(0x089, MDM_DSP_RAM_089_Status, 0xBF);
}


/**  22. Far-End Echo Frequency Offset										4		,852			**/
/**  23. Far-End Echo Level													4		,B52			**/


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 25. Answer Tone Length]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 228,229
//	]
//	ProtoType	:[void far MDM_SetAnswerToneLength(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetAnswerToneLength(UBYTE time)
//{
//	UWORD time_value;
//	
//	time_value = time * 300;
//	DspRamAccessWriteMethod2(0x228, 0x229, time_value, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 26. Silence agter Answer Tone Period]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 22A,22B
//	]
//	ProtoType	:[void far MDM_SetSilenceAnsTonePeriod(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetSilenceAnsTonePeriod(UBYTE time)
//{
//	UWORD time_value;
//	
//	time_value = time * 300;
//	DspRamAccessWriteMethod2(0x22A, 0x22B, time_value, 0x0000);
//}
#endif

#if 0 /* メモリ節約のため、削除します。 by H.Kubo 1998/07/08 */
@@
@@/*************************************************************************
@@	module		:[ 27. Tone Detecter A Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AA1
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_Filter_B1_A3(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_Filter_B1_A3(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAA1, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 27. Tone Detecter A Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AA2
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_Filter_B1_A2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_Filter_B1_A2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAA2, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 27. Tone Detecter A Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AA3
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_Filter_B1_A1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_Filter_B1_A1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAA3, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 27. Tone Detecter A Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AA4
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_Filter_B1_B2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_Filter_B1_B2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAA4, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 27. Tone Detecter A Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AA5
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_Filter_B1_B1(UWORD data){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_Filter_B1_B1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAA5, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 27. Tone Detecter A Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BA1
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_Filter_B2_A3(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_Filter_B2_A3(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBA1, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 27. Tone Detecter A Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BA2
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_Filter_B2_A2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_Filter_B2_A2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBA2, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 27. Tone Detecter A Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BA3
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_Filter_B2_A1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_Filter_B2_A1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBA3, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 27. Tone Detecter A Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BA4
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_Filter_B2_B2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_Filter_B2_B2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBA4, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 27. Tone Detecter A Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BA5
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_Filter_B2_B1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_Filter_B2_B1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBA5, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 28. Tone Detecter B Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AA7
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_Filter_B1_A3(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_Filter_B1_A3(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAA7, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 28. Tone Detecter B Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AA8
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_Filter_B1_A2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_Filter_B1_A2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAA8, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 28. Tone Detecter B Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AA9
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_Filter_B1_A1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_Filter_B1_A1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAA9, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 28. Tone Detecter B Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AAA
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_Filter_B1_B2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_Filter_B1_B2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAAA, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 28. Tone Detecter B Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AAB
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_Filter_B1_B1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_Filter_B1_B1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAAB, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 28. Tone Detecter B Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BA7
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_Filter_B2_A3(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_Filter_B2_A3(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBA7, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 28. Tone Detecter B Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BA8
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_Filter_B2_A2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_Filter_B2_A2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBA8, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 28. Tone Detecter B Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BA9
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_Filter_B2_A1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_Filter_B2_A1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBA9, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 28. Tone Detecter B Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BAA
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_Filter_B2_B2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_Filter_B2_B2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBAA, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 28. Tone Detecter B Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BAB
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_Filter_B2_B1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_Filter_B2_B1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBAB, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 29. Tone Detecter C Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AAD
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_Filter_B1_A3(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_Filter_B1_A3(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAAD, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 29. Tone Detecter C Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AAE
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_Filter_B1_A2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_Filter_B1_A2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAAE, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 29. Tone Detecter C Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AAF
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_Filter_B1_A1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_Filter_B1_A1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAAF, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 29. Tone Detecter C Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AB0
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_Filter_B1_B2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_Filter_B1_B2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAB0, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 29. Tone Detecter C Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AB1
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_Filter_B1_B1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_Filter_B1_B1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAB1, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 29. Tone Detecter C Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BAD
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_Filter_B2_A3(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_Filter_B2_A3(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBAD, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 29. Tone Detecter C Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BAE
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_Filter_B2_A2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_Filter_B2_A2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBAE, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 29. Tone Detecter C Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BAF
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_Filter_B2_A1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_Filter_B2_A1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBAF, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 29. Tone Detecter C Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BB0
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_Filter_B2_B2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_Filter_B2_B2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBB0, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ 29. Tone Detecter C Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BB1
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_Filter_B2_B1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_Filter_B2_B1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBB1, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter Prefilter Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AB2
@@	]
@@	ProtoType	:[void far MDM_SetTone_P_Filter_B1_A3(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_P_Filter_B1_A3(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAB2, data, 0x0000);
@@}
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter Prefilter Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AB3
@@	]
@@	ProtoType	:[void far MDM_SetTone_P_Filter_B1_A2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_P_Filter_B1_A2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAB3, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter Prefilter Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AB4
@@	]
@@	ProtoType	:[void far MDM_SetTone_P_Filter_B1_A1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_P_Filter_B1_A1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAB4, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter Prefilter Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AB5
@@	]
@@	ProtoType	:[void far MDM_SetTone_P_Filter_B1_B2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_P_Filter_B1_B2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAB5, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter Prefilter Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AB6
@@	]
@@	ProtoType	:[void far MDM_SetTone_P_Filter_B1_B1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_P_Filter_B1_B1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAB6, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter Prefilter Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BB2
@@	]
@@	ProtoType	:[void far MDM_SetTone_P_Filter_B2_A3(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_P_Filter_B2_A3(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBB2, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter Prefilter Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BB3
@@	]
@@	ProtoType	:[void far MDM_SetTone_P_Filter_B2_A2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_P_Filter_B2_A2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBB3, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter Prefilter Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BB4
@@	]
@@	ProtoType	:[void far MDM_SetTone_P_Filter_B2_A1(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_P_Filter_B2_A1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBB4, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter Prefilter Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BB5
@@	]
@@	ProtoType	:[void far MDM_SetTone_P_Filter_B2_B2(UWORD ){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_P_Filter_B2_B2(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBB5, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter Prefilter Bandpass Filter Coefficients]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BB6
@@	]
@@	ProtoType	:[void far MDM_SetTone_P_Filter_B2_B1(UWORD ){}
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_P_Filter_B2_B1(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBB6, data, 0x0000);
@@}
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter A LPFBK]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BA0
@@	]
@@	ProtoType	:[void far MDM_setTone_A_LPFBK(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_setTone_A_LPFBK(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBA0, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter A LPGAIN]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AA0
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_LPGAIN(data){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_LPGAIN(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAA0, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter A THRESHU]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AB8
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_THRESHU(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_THRESHU(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAB8, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter A THRESHL]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BB8
@@	]
@@	ProtoType	:[void far MDM_SetTone_A_THRESHL(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_A_THRESHL(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBB8, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter B LPFBK]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BA6
@@	]
@@	ProtoType	:[void far MDM_setTone_B_LPFBK(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_setTone_B_LPFBK(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBA6, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter B LPGAIN]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AA6
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_LPGAIN(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_LPGAIN(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAA6, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter B THRESHU]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AB9
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_THRESHU(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_THRESHU(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAB9, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter B THRESHL]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BB9
@@	]
@@	ProtoType	:[void far MDM_SetTone_B_THRESHL(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_B_THRESHL(UWORD data)
@@{
@@#if (0) /* Changed by H.Kubo 1998/01/06 */
@@@@	DspRamAccessWriteMethod3(0xBB8, data, 0x0000);
@@#else
@@	DspRamAccessWriteMethod3(0xBB9, data, 0x0000);
@@#endif /* (0) */
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter C LPFBK]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BAC
@@	]
@@	ProtoType	:[void far MDM_setTone_C_LPFBK(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_setTone_C_LPFBK(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBAC, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter C LPGAIN]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: AAC
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_LPGAIN(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_LPGAIN(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xAAC, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter C THRESHU]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: ABA
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_THRESHU(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_THRESHU(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xABA, data, 0x0000);
@@}
@@
@@
@@/*************************************************************************
@@	module		:[ xx. Tone Detecter C THRESHL]
@@	function	:[
@@		1.
@@	]
@@	return		:[]
@@	common		:[]
@@	condition	:[]
@@	comment		:[
@@		Access Method	: 3
@@		Address			: BBA
@@	]
@@	ProtoType	:[void far MDM_SetTone_C_THRESHL(UWORD){}]
@@	date		:[1995/11/22]
@@	author		:[木元　修]
@@*************************************************************************/
@@void  MDM_SetTone_C_THRESHL(UWORD data)
@@{
@@	DspRamAccessWriteMethod3(0xBBA, data, 0x0000);
@@}
#endif


/*************************************************************************
	module		:[ xx. Set Filter Coefficients ]
	function	:[
		1.モデムのトーン検出フィルターの係数のセット関数（汎用型）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 3
		Address			: 
	]
	ProtoType	:[void MDM_SetFiterCoefficient(UWORD address, UWORD data, UWORD mask_data){}]
	date		:[1998/04/27]
	author		:[木元　修]
*************************************************************************/
void MDM_SetFiterCoefficient(UWORD address, UWORD data, UWORD mask_data)
{
#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))	/* Add By O.Kimoto 2002/10/15 */	/* 2000/02/22 Y.Murata */
	if (wai_1shot_tid == 0xFF) {
		wai_oneshot(1);
	}
	else {
		wai_tsk(1);
	}
#else
	wai_tsk(1);
#endif
	DspRamAccessWriteMethod3((UWORD)address, (UWORD)data, (UWORD)mask_data);
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
/*
** R288Fバージョン24P以上のとき
** 復活 by H.Kubo 1998/10/21
*/
/*************************************************************************
	module		:[ 30. RLSD Drop Out Timer]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 270 and 271
	]
	ProtoType	:[void far MDM_SetRLSD_DropOutTimer(UBYTE ){}]
	date		:[1995/11/22]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetRLSD_DropOutTimer(UBYTE time)
{
	UWORD	time_value;
	UBYTE msb_data;
	UBYTE lsb_data;

	time_value = time;

	/*
	** Designer's manual に従い、下記のように変更します。
	** by H.Kubo 1998/1021
	*/
	switch (ModemBlock.Type) {
	case TYPE_V34:
		time_value *= 3429; /* おおざっぱですが、 シンボルレート 3429 と仮定しておきます。 */
		break;
	case TYPE_V17:
		time_value *= 2400;
		break;
	case TYPE_V29:
		time_value *= 2400;
		break;
	case TYPE_V27:
		if (ModemBlock.Speed == SPEED_4800) {
			time_value *= 1600;
		}
		else {
			time_value *= 1200;
		}
		break;
	default:
		time_value *= 300;
		break;
	}

	msb_data = (UBYTE)(time_value >> 8);
	lsb_data = (UBYTE)(time_value & 0xff);

 #if 0 /* MSB と LSB を間違えてました。 by H.Kubo 1999/02/05 */
	DspRamAccessWriteMethod1(0x270, msb_data, 0x00);
	DspRamAccessWriteMethod1(0x271, lsb_data, 0x00);
 #else
	DspRamAccessWriteMethod1(0x270, lsb_data, 0x00);
	DspRamAccessWriteMethod1(0x271, msb_data, 0x00);
 #endif
}



/**  31. RLSD Turn-On Threshold(RLSD_ON)									2		,134,135		**/
/**  32. RLSD Turn-Off Threshold(RLSD_OFF)									2		,136,137		**/
/**  33-A.RLSD Threshold Offset												2		,138,139		**/


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 33-B. RLSD Overwrite Control]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[
//		0	: overwrite enabled (default)
//		1	: overwrite disabled
//	]
//	comment		:[
//		Access Method	: 1
//		Address			: 10D(Bit 2)
//	]
//	ProtoType	:[void far MDM_SEtRLSD_OverwriteControl(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetRLSD_OverwriteControl(UBYTE sw)
//{
//	MDM_DSP_RAM_10D_Status = DspRamAccessReadMethod1(0x10D);	/** Add By O.K Jan.22,1996 **/
//
//	if (sw == ON) {
//		MDM_DSP_RAM_10D_Status &= ~MDM_BIT_2;
//	}
//	else {
//		MDM_DSP_RAM_10D_Status |= MDM_BIT_2;
//	}
//	DspRamAccessWriteMethod1(0x10D, MDM_DSP_RAM_10D_Status, 0xFB);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 33-C. Extended RTH Control]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[
//		0	: disables reduction (default)
//		1	: enables reduction
//	]
//	comment		:[
//		Access Method	: 1
//		Address			: 10D(Bit 6)
//	]
//	ProtoType	:[void far MDM_SetExtendedRTHControl(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetExtendedRTHControl(UBYTE sw)
//{
//	MDM_DSP_RAM_10D_Status = DspRamAccessReadMethod1(0x10D);	/** Add By O.K Jan.22,1996 **/
//
//	if (sw == ON) {
//		MDM_DSP_RAM_10D_Status &= ~MDM_BIT_6;
//	}
//	else {
//		MDM_DSP_RAM_10D_Status |= MDM_BIT_6;
//	}
//	DspRamAccessWriteMethod1(0x10D, MDM_DSP_RAM_10D_Status, 0xBF);
//}
#endif


/*************************************************************************
	module		:[33-D. Receiver Gain]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 3
		Address			: A03
	]
	ProtoType	:[void far MDM_SetReceiverGain(UWORD){}]
	date		:[1996/03/04]
	author		:[木元修]
*************************************************************************/
void  MDM_SetReceiverGain(UWORD gain_value)
{
	DspRamAccessWriteMethod3(0xA03, gain_value, 0x0000);
}

	/**  33-E. Receiver Threshold													3		,A04,A05		**/


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 33-F. RTH0 Offset]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 2D0,2D1
//	]
//	ProtoType	:[void far MDM_SetRTH0_Offset(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetRTH0_Offset(UBYTE delt)
//{
//	UWORD	offset_value;
//	
//	offset_value = (UWORD)(0x0000 - (delt * 0x100));
//	DspRamAccessWriteMethod2(0x2D0, 0x2D1, offset_value, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 33-G. RTH1 Offset]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 2D2,2D3
//	]
//	ProtoType	:[void far MDM_SetRTH1_Offset(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetRTH1_Offset(UBYTE delt)
//{
//	UWORD	offset_value;
//	
//	offset_value = (UWORD)(0x1AC0 - (delt * 0x100));
//	DspRamAccessWriteMethod2(0x2D2, 0x2D3, offset_value, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 33-H. RTH2 Offset]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 2D4,2D5
//	]
//	ProtoType	:[void far MDM_SetRTH2_Offset(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetRTH2_Offset(UBYTE delt)
//{
//	UWORD	offset_value;
//	
//	offset_value = (UWORD)(0x2CC0 - (delt * 0x100));
//	DspRamAccessWriteMethod2(0x2D4, 0x2D5, offset_value, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 33-I. RTH3 Offset]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 2D6,2D7
//	]
//	ProtoType	:[void far MDM_SetRTH3_Offset(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetRTH3_Offset(UBYTE delt)
//{
//	UWORD	offset_value;
//	
//	offset_value = (UWORD)(0x4640 - (delt * 0x100));
//	DspRamAccessWriteMethod2(0x2D6, 0x2D7, offset_value, 0x0000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 36. AGC Gain Word]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 4(RO)
//		Address			: A00
//	]
//	ProtoType	:[UWORD far MDM_GetAgcGainWord(void){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//UWORD  MDM_GetAgcGainWord(void)
//{
//	UWORD agcgain_value;
//	
//	agcgain_value = DspRamAccessReadMethod4(0xA00);
//	return((UWORD)(agcgain_value / 682 - 52));
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 37. Round Trip Far Echo Delay]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 4(RO)
//		Address			: 239
//	]
//	ProtoType	:[UWORD far MDM_GetRoundFarTripEchoDelay(void){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//UWORD  MDM_GetRoundFarTripEchoDelay(void)
//{
//	UWORD value;
//	
//	value = DspRamAccessReadMethod4(0x239);
//	return((UWORD)(value/MDM_SymbolRate - 10));
//}
#endif


/*************************************************************************
	module		:[ 46. Eye Quality Monitor(EQM)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 4(RO)
		Address			; 20C
	]
	ProtoType	:[UWORD far MDM_GetEyeQualityMonitor(void){}]
	date		:[1995/11/22]
	author		:[木元　修]
*************************************************************************/
UWORD  MDM_GetEyeQualityMonitor(void)
{
	return((UWORD)(DspRamAccessReadMethod4(0x20C)));
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 47. Maximum Period of Valid Ring Signal]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 21F
//	]
//	ProtoType	:[void far MDM_SetMaxPeriodValidRingSignal(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetMaxPeriodValidRingSignal(UBYTE freq)
//{
//	UBYTE freq_value;
//	
//	freq_value = (UBYTE)(2400 / freq);
//	DspRamAccessWriteMethod1(0x21F, freq_value, 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 48. Minimum Period of Valid Ring Signal]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 21E
//	]
//	ProtoType	:[void far MDM_SetMinPeriodValidRingSignal(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetMinPeriodValidRingSignal(UBYTE freq)
//{
//	UBYTE freq_value;
//	
//	freq_value = (UBYTE)(2400 / freq);
//	DspRamAccessWriteMethod1(0x21E, freq_value, 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
/*
** R288F VERSION 26P以降の場合
** by H.Kubo 1998/10/07
*/
/*************************************************************************
	module		:[ 49. Phase Jitter Frequency]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 4(RO)
		Address			: 80E
	]
	ProtoType	:[UWORD far MDM_GetPhaseJitterFrequency(void){}]
	date		:[1995/11/22]
	author		:[木元　修]
*************************************************************************/
UWORD  MDM_GetPhaseJitterFrequency(void)
{
	UWORD freq_value;
	
#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	if (SYS_ModemVersion >= MDM_L6719_12P_ES) {
		freq_value = DspRamAccessReadMethod4(0x6C8);
	}
	else {
		freq_value = DspRamAccessReadMethod4(0x694);
	}
#else
	/* freq_value = DspRamAccessReadMethod4(0x80E); */ /* 26P 以降は別のアドレスから読める。 */
	freq_value = DspRamAccessReadMethod4(0x694);
#endif
	return((UWORD)(freq_value * MDM_SymbolRate / 0x10000));
}


/*************************************************************************
	module		:[ 50. Phase Jitter Amplitude]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 4(RO)
		Address			: 80D
	]
	ProtoType	:[UWORD far MDM_GetPhaseJitterAmplitude(void){}]
	date		:[1995/11/22]
	author		:[木元　修]
*************************************************************************/
UWORD  MDM_GetPhaseJitterAmplitude(void)
{
	UWORD amp_value;
	
#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	if (SYS_ModemVersion >= MDM_L6719_12P_ES) {
		amp_value = DspRamAccessReadMethod4(0x6C6);
	} else {
		amp_value = DspRamAccessReadMethod4(0x692);
	}
#else
	/*
	** R288F VERSION 26P以降の場合
	*/
	amp_value = DspRamAccessReadMethod4(0x692);
#endif

	return((UWORD)(amp_value / 90));
}



/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
/*
** R288F VERSION 24P以降の場合
** ナンバーディスプレイの不具合対策で復活します
** by H.Kubo 1998/10/05
*/
/*************************************************************************
	module		:[ 52. CCITT CRC 32 Select]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[
		0	: CCITT CRC 32
		1	: CCITT CRC 16 (default)
	]
	comment		:[
		Access Method	: 1
		Address			: 0B3(Bit 0)
	]
	ProtoType	:[void far MDM_SetCcittCrc32Select(UBYTE ){}]
	date		:[1995/11/22]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCcittCrc32Select(UBYTE sw)
{
	MDM_DSP_RAM_0B3_Status = DspRamAccessReadMethod1(0x0B3);	/** Add By O.K Jan.22,1996 **/

	if (sw == ON) {
		MDM_DSP_RAM_0B3_Status &= ~MDM_BIT_0;
	}
	else {
		MDM_DSP_RAM_0B3_Status |= MDM_BIT_0;
	}
	DspRamAccessWriteMethod1(0x0B3, MDM_DSP_RAM_0B3_Status, 0xFE);
}

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 60. V.34 Symbol Rate Value]
//	function	:[
//		1.
//	]
//	return		:[
//		bit 0	: 2400 baud
//		bit 1	: Reserved ( always be a 0 )
//		bit 2	: 2800 baud
//		bit 3	: 3000 baud
//		bit 4	: 3200 baud
//		bit 5	: 3429 baud
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 2E3
//	]
//	ProtoType	:[UBYTE far MDM_GetV34SymbolRate(void){}]
//	date		:[1995/11/20]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE  MDM_GetV34SymbolRate(void)
//{
//	return((UBYTE)(DspRamAccessReadMethod1(0x2E3) & 0x3D));
//}
#endif

/*************************************************************************
	module		:[ 61. V.34/V.FC Baud Rate Mask(BRM)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 101
	]
	ProtoType	:[void far MDM_SetV34SymbolRate(UBYTE ){}]
	date		:[1995/11/20]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetV34SymbolRate(UBYTE rate)
{
	UBYTE rate_mask;
	
	rate_mask = (UBYTE)(rate & 0x3D);
	DspRamAccessWriteMethod1(0x101, rate_mask, 0xC2);
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 62. V.34 Pre-Emphasis Filter Number]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 4(RO)
//		Address			: B44
//	]
//	ProtoType	:[UWORD far MDM_GetV34PreEmphaFilterNum(void){}]
//	date		:[1995/11/20]
//	author		:[木元　修]
//*************************************************************************/
//UWORD  MDM_GetV34PreEmphaFilterNum(void)
//{
//	return(DspRamAccessReadMethod4(0xB44));
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 63-A. V.34/V.FC Pre-Emphasis Override]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 0E6
//	]
//	ProtoType	:[void far MDM_SetV34PreEmphasisOverride(UBYTE ){}]
//	date		:[1995/11/20]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetV34PreEmphasisOverride(UBYTE number)
//{
//	if (number > 0x0A) {
//		number = 0;
//	}
//	DspRamAccessWriteMethod1(0x0E6, number, 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 63-B. V.34 Pre-Emphasis Disable(PREDIS)]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 100(bit1)
//	]
//	ProtoType	:[void far MDM_SetV34PreEmphasisDisable(void){}]
//	date		:[1995/11/20]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetV34PreEmphasisDisable(void)
//{
//	UBYTE temp_reg;
//	
//	temp_reg = DspRamAccessReadMethod1(0x100);
//	temp_reg &= ~MDM_BIT_1;
//	DspRamAccessWriteMethod1(0x100, temp_reg, 0xFD);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 64. V.34 Transmit Level Deviation Disable(TLDDIS)]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 100(bit3)
//	]
//	ProtoType	:[void far MDM_SetTxLevelDeviationDisable(void){}]
//	date		:[1995/11/20]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetTxLevelDeviationDisable(void)
//{
//	UBYTE temp_reg;
//	
//	temp_reg = DspRamAccessReadMethod1(0x100);
//	temp_reg &= ~MDM_BIT_3;
//	DspRamAccessWriteMethod1(0x100, temp_reg, 0xF7);
//}
#endif

/**  68. EQM Above Threshold												1		,133			**/
/**  69. EQM Scale Factor(Gain)												3		,A29			**/
	/** EQM ARA Bias(Offset)												2		,2A4,2A5		**/


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 73. No Automode to FSK]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[
//		0	: Automode to FSK enabled (default)
//		1	: Automode to FSK disabled
//	]
//	comment		:[
//		Access Method	: 1
//		Address			: 13F(bit0)
//	]
//	ProtoType	:[void far MDM_SetNoAutomodeToFsk(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetNoAutomodeToFsk(UBYTE sw)
//{
//	MDM_DSP_RAM_13F_Status = DspRamAccessReadMethod1(0x13F);	/** Add By O.K Jan.22,1996 **/
//
//	if (sw == ON) {
//		MDM_DSP_RAM_13F_Status &= ~MDM_BIT_0;
//	}
//	else {
//		MDM_DSP_RAM_13F_Status |= MDM_BIT_0;
//	}
//	DspRamAccessWriteMethod1(0x13F, MDM_DSP_RAM_13F_Status, 0xFE);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 74. Receive FIFO Trigger Level]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 32C
//	]
//	ProtoType	:[void far MDM_SetRxFIFOTriggerLevel(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetRxFIFOTriggerLevel(UBYTE status)
//{
//	DspRamAccessWriteMethod1(0x32C, (UBYTE)(status & 0xDE), 0x21);
//}
#endif

/**  75. V.34/V.FC GSTN Cleardown Option				1		,13B			**/


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 81. V.34 Spectral Parameters Control]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 105
//	]
//	ProtoType	:[void far MDM_SetV34SpectralParamControl(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetV34SpectralParamControl(UBYTE status)
//{
//	DspRamAccessWriteMethod1(0x105, status, 0x0F);
//}
#endif

/*************************************************************************
	module		:[ 82. V.34 Phase 2 Power Reduction]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1(RO)
		Address			: 0E2
	]
	ProtoType	:[UBYTE far MDM_GetV34Phase2PowerReduction(void){}]
	date		:[1995/11/22]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetV34Phase2PowerReduction(void)
{
	return(DspRamAccessReadMethod1(0x0E2));
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 83-A. V.34 Low Band Symbol Rate Edge Estimate Offset]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 13B
//	]
//	ProtoType	:[void far MDM_SetV34LowBandEstimateOffset(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetV34LowBandEstimateOffset(UBYTE freq)
//{
//	UWORD freq_value;
//	
//	freq_value = freq * 37;
//	if (freq_value >= 0x100) {
//		freq_value = 0xFF;
//	}
//	DspRamAccessWriteMethod1(0x13B, (UBYTE)(freq_value), 0x00);
//}
#endif


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 83-B. V.34 How Band Symbol Rate Edge Estimate Offset]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 13C
//	]
//	ProtoType	:[void far MDM_SetV34HowBandEstimateOffset(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetV34HowBandEstimateOffset(UBYTE freq)
//{
//	UWORD freq_value;
//	
//	freq_value = freq * 37;
//	if (freq_value >= 0x100) {
//		freq_value = 0xFF;
//	}
//	DspRamAccessWriteMethod1(0x13C, (UBYTE)(freq_value), 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 84. V.34 Receiver Speed Indication]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 384
//	]
//	ProtoType	:[void far MDM_SetV34RxSpeedIndication(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetV34RxSpeedIndication(UBYTE speed)
//{
//	DspRamAccessWriteMethod1(0x384, speed, 0x00);
//}
#endif

/*************************************************************************
	module		:[ 84. V.34 Receiver Speed Indication]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1 (R)
		Address			: 384
	]
	ProtoType	:[UBYTE far MDM_SetV34RxSpeedIndication(void){}]
	date		:[1996/02/02]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetV34RxSpeedIndication(void)
{
	return( DspRamAccessReadMethod1( 0x384 ));
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 85. V.34 Data Rate Mask]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2
//		Address			: 382,383
//	]
//	ProtoType	:[void far MDM_SetV34DataRateMask(UWORD ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetV34DataRateMask(UWORD speed)
//{
//	speed |= (UWORD)(0xC000);	/* Bits 14 & 15 must remain set to 1 by O.Kimoto 1996/03/28 */
//	DspRamAccessWriteMethod2(0x382, 0x383, speed, 0xC000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 86. V.34 Asymmetric Data Rates Enable]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 13F(bit6)
//	]
//	ProtoType	:[void far MDM_SetV34ASYMDataRatesEnable(UBYTE ){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetV34ASYMDataRatesEnable(UBYTE sw)
//{
//	MDM_DSP_RAM_13F_Status = DspRamAccessReadMethod1(0x13F);	/** Add By O.K Jan.22,1996 **/
//
//	if (sw == ON) {
//		/*MDM_DSP_RAM_13F_Status &= ~MDM_BIT_6; 1996/02/23 */
//		MDM_DSP_RAM_13F_Status |= MDM_BIT_6;
//	}
//	else {
//		/*MDM_DSP_RAM_13F_Status |= MDM_BIT_6; 1996/02/23 */
//		MDM_DSP_RAM_13F_Status &= ~MDM_BIT_6;
//	}
//	DspRamAccessWriteMethod1(0x13F, MDM_DSP_RAM_13F_Status, 0xBF);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 87-A. V.34 Remote Mode Data Rate Capability]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 2(RO)
//		Address			: 208,209
//	]
//	ProtoType	:[UWORD far MDM_SetV34RemoteModeDataRate(void){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//UWORD  MDM_SetV34RemoteModeDataRate(void)
//{
//	return(DspRamAccessReadMethod2(0x208,0x209));
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 87-B. V.34 Remote Modem Asymmetric Data Rate Indicator]
//	function	:[
//		1.
//	]
//	return		:[
//		0	: Capability is Disable.
//		1	: Capability is Enable.
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 209(Bit 7)
//	]
//	ProtoType	:[UBYTE far MDM_GetV34RemoteASYMDataRate(void){}]
//	date		:[1995/11/22]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE  MDM_GetV34RemoteASYMDataRate(void)
//{
//	if (DspRamAccessReadMethod1(0x209) & MDM_BIT_7) {
//		/* return(ENABLED); */
//		return(TRUE); /* Changed by H. Kubo 1997/06/26 */
//	}
//	else {
//		/* return(DISABLED); */
//		return(FALSE); /* Changed by H. Kubo 1997/06/26 */
//	}
//}
#endif

/*************************************************************************
	module		:[ 88-A. V.8 Status Register 1]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 301
	]
	ProtoType	:[UBYTE far MDM_GetV8StatusRegister1(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetV8StatusRegister1(void)
{
	MDM_V8_StatusStatus[0] = DspRamAccessReadMethod1(0x301);
	return(MDM_V8_StatusStatus[0]);
}


/*************************************************************************
	module		:[ 88-B. V.8 Status Register 2]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 302
	]
	ProtoType	:[UBYTE far MDM_GetV8StatusRegister2(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetV8StatusRegister2(void)
{
	MDM_V8_StatusStatus[1] = DspRamAccessReadMethod1(0x302);
	return(MDM_V8_StatusStatus[1]);
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ 88-C. V.8 Status Register 3]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 302
//	]
//	ProtoType	:[UBYTE far MDM_GetV8StatusRegister3(void){}]
//	date		:[1995/11/24]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE  MDM_GetV8StatusRegister3(void)
//{
//	MDM_V8_StatusStatus[2] = DspRamAccessReadMethod1(0x303);
//	return(MDM_V8_StatusStatus[2]);
//}
#endif

/*************************************************************************
	module		:[ 89-A. V.8 Control Register 1]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 304
	]
	ProtoType	:[void far MDM_SetV8ControlRegister1(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetV8ControlRegister1(UBYTE status)
{
	status &= 0xFE;
	MDM_V8_ControlStatus[0] = status;
	DspRamAccessWriteMethod1(0x304, status, 0x00);
}


/*************************************************************************
	module		:[ 89-B. V.8 Control Register 2]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 305
	]
	ProtoType	:[void far MDM_SetV8ControlRegister2(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetV8ControlRegister2(UBYTE status)
{
	status &= 0xEF;
	MDM_V8_ControlStatus[1] = status;
	DspRamAccessWriteMethod1(0x305, status, 0x10);
}


/*************************************************************************
	module		:[ 89-C. V.8 Control Register 3]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 306
	]
	ProtoType	:[void far MDM_SetV8ControlRegister3(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetV8ControlRegister3(UBYTE status)
{
	status &= 0x80;
	MDM_V8_ControlStatus[2] = status;
	DspRamAccessWriteMethod1(0x306, status, 0x3F);
}


/*************************************************************************
	module		:[ 89-D. V.8 Control Register 4]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 307
	]
	ProtoType	:[void far MDM_SetV8ControlRegister4(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetV8ControlRegister4(UBYTE status)
{
	status &= 0xC4;
	MDM_V8_ControlStatus[3] = status;
	DspRamAccessWriteMethod1(0x307, status, 0x38);
}


/*************************************************************************
	module		:[ 89-E. V.8 Control Register 5]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 308
	]
	ProtoType	:[void far MDM_SetV8ControlRegister5(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetV8ControlRegister5(UBYTE status)
{
	status &= 0x84;
	MDM_V8_ControlStatus[4] = status;
	DspRamAccessWriteMethod1(0x308, status, 0x38);
}


/*************************************************************************
	module		:[ 89-F. V.8 Control Register 6]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 38F
	]
	ProtoType	:[void far MDM_SetV8ControlRegister6(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetV8ControlRegister6(UBYTE status)
{
	status &= 0x08;
	MDM_V8_ControlStatus[5] = status;
	DspRamAccessWriteMethod1(0x38F, status, 0xF7);
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[90-A. Modulation Modes(V.34 Full-Duplex configuration)]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 309
//	]
//	ProtoType	:[void far MDM_SetModulationModeV34FDX(UBYTE ){}]
//	date		:[1995/11/24]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetModulationModeV34FDX(UBYTE status)
//{
//	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
//	DspRamAccessWriteMethod1(0x309, status, 0x00);
//}
#endif

/*************************************************************************
	module		:[90-B. Modulation Modes(V.34 Hulf-Duplex configuration)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 30A
	]
	ProtoType	:[void far MDM_SetModulationModeV34HDX(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetModulationModeV34HDX(UBYTE status)
{
	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
	DspRamAccessWriteMethod1(0x30A, status, 0x00);
}


/*************************************************************************
	module		:[90-C. Modulation Modes(V.32 bis)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 30B
	]
	ProtoType	:[void far MDM_SetModulationModeV32BIS(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetModulationModeV32BIS(UBYTE status)
{
	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
	DspRamAccessWriteMethod1(0x30B, status, 0x00);
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[90-D. Modulation Modes(V.22 bis)]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 30C
//	]
//	ProtoType	:[void far MDM_SetModulationModeV22BIS(UBYTE ){}]
//	date		:[1995/11/24]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetModulationModeV22BIS(UBYTE status)
//{
//	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
//	DspRamAccessWriteMethod1(0x30C, status, 0x00);
//}
#endif

/*************************************************************************
	module		:[90-E. Modulation Modes(V.17)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 30D
	]
	ProtoType	:[void far MDM_SetModulationModeV17(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetModulationModeV17(UBYTE status)
{
	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
	DspRamAccessWriteMethod1(0x30D, status, 0x00);
}


/*************************************************************************
	module		:[90-F. Modulation Modes(V.29)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 30E
	]
	ProtoType	:[void far MDM_SetModulationModeV29(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetModulationModeV29(UBYTE status)
{
	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
	DspRamAccessWriteMethod1(0x30E, status, 0x00);
}


/*************************************************************************
	module		:[90-G. Modulation Modes(V.27 ter)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 30F
	]
	ProtoType	:[void far MDM_SetModulationModeV27(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetModulationModeV27(UBYTE status)
{
	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
	DspRamAccessWriteMethod1(0x30F, status, 0x00);
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[90-H. Modulation Modes(V.26 ter)]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 310
//	]
//	ProtoType	:[void far MDM_SetModulationModeV26TER(UBYTE ){}]
//	date		:[1995/11/24]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetModulationModeV26TER(UBYTE status)
//{
//	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
//	DspRamAccessWriteMethod1(0x310, status, 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[90-I. Modulation Modes(V.26 bis)]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 311
//	]
//	ProtoType	:[void far MDM_SetModulationModeV26BIS(UBYTE ){}]
//	date		:[1995/11/24]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetModulationModeV26BIS(UBYTE status)
//{
//	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
//	DspRamAccessWriteMethod1(0x311, status, 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[90-J. Modulation Modes(V.23 Full-Duplex)]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 312
//	]
//	ProtoType	:[void far MDM_SetModulationModeV23FDX(UBYTE ){}]
//	date		:[1995/11/24]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetModulationModeV23FDX(UBYTE status)
//{
//	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
//	DspRamAccessWriteMethod1(0x312, status, 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[90-K. Modulation Modes(V.23 Full-Duplex)]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 313
//	]
//	ProtoType	:[void far MDM_SetModulationModeV23HDX(UBYTE ){}]
//	date		:[1995/11/24]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetModulationModeV23HDX(UBYTE status)
//{
//	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
//	DspRamAccessWriteMethod1(0x313, status, 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[90-L. Modulation Modes(V.21)]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 314
//	]
//	ProtoType	:[void far MDM_SetModulationModeV21(UBYTE ){}]
//	date		:[1995/11/24]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetModulationModeV21(UBYTE status)
//{
//	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
//	DspRamAccessWriteMethod1(0x314, status, 0x00);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[90-M. Modulation Modes(V.FC)]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 315
//	]
//	ProtoType	:[void far MDM_SetModulationModeVFC(UBYTE ){}]
//	date		:[1995/11/24]
//	author		:[木元　修]
//*************************************************************************/
//void  MDM_SetModulationModeVFC(UBYTE status)
//{
//	status = MDM_BPS_ToR288F_MemBitCONF(status); /* Added for POPLAR_H by H. Kubo 1997/06/19 */
//	DspRamAccessWriteMethod1(0x315, status, 0x00);
//}
#endif

/*************************************************************************
	module		:[ 91. V.8 Maximum Frame Byte Count]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 31C
	]
	ProtoType	:[void far MDM_SetV8MaxFrameByteCount(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetV8MaxFrameByteCount(UBYTE count)
{
	if (count < 9) {
		count = 9;
	}
	DspRamAccessWriteMethod1(0x31C, count, 0x00);
}


/*************************************************************************
	module		:[ 91. V.8 Call Function]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 32A
	]
	ProtoType	:[void far MDM_SetV8CallFunction(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
#define FAX_TX			1
#define FAX_RX			2
#define DUPLEX_DATA		3
#define FAX_TRX			4
#define SET_CF4		0x10
#define SET_CF5		0x20
#define SET_CF6		0x40

void  MDM_SetV8CallFunction(UBYTE status)
{
	switch(status) {
	case FAX_TX:
		MDM_V8_ControlStatus[6] &= 0x8F;
		MDM_V8_ControlStatus[6] |= 0x10;
		MDM_DSP_RAM_32A_Status = SET_CF4;
		break;
	case FAX_RX:
		MDM_V8_ControlStatus[6] &= 0x8F;
		MDM_V8_ControlStatus[6] |= 0x20;
		MDM_DSP_RAM_32A_Status = SET_CF5;
		break;
	case FAX_TRX:
		MDM_V8_ControlStatus[6] &= 0x8F;
		MDM_V8_ControlStatus[6] |= 0x30;
		/*MDM_DSP_RAM_32A_Status = SET_CF6; 1996/02/13 Y.M */
		MDM_DSP_RAM_32A_Status = (SET_CF4 | SET_CF5);
		break;
	case DUPLEX_DATA:
		MDM_V8_ControlStatus[6] &= 0x8F;
		MDM_V8_ControlStatus[6] |= 0x40;
		MDM_DSP_RAM_32A_Status = SET_CF6;
		break;
	default:
		return;
	}
	DspRamAccessWriteMethod1(0x32A, MDM_DSP_RAM_32A_Status, 0x00);
}


/*************************************************************************
	module		:[ 93-A-1. CM Frame(SYNC CM)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 32D
	]
	ProtoType	:[void far MDM_SetCmFrameSyncCm(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCmFrameSyncCm(void)
{
	DspRamAccessWriteMethod1(0x32D, 0xE0, 0x00);
}


/*************************************************************************
	module		:[ 93-A-2. CM Frame(Data Call Function)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 32E
	]
	ProtoType	:[void far MDM_SetCmFrameDataCallFunc(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCmFrameDataCallFunc(UBYTE status)
{
	DspRamAccessWriteMethod1(0x32E, status, 0x00);
}


/*************************************************************************
	module		:[ 93-A-3. CM Frame(modulation 0)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 32F
	]
	ProtoType	:[void far MDM_SetCmFrameModulation0(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCmFrameModulation0(UBYTE status)
{
	DspRamAccessWriteMethod1(0x32F, status, 0x00);
}


/*************************************************************************
	module		:[ 93-A-4. CM Frame(modulation 1)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 330
	]
	ProtoType	:[void far MDM_SetCmFrameModulation1(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCmFrameModulation1(UBYTE status)
{
	DspRamAccessWriteMethod1(0x330, status, 0x00);
}


/*************************************************************************
	module		:[ 93-A-5. CM Frame(modulation 2)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 331
	]
	ProtoType	:[void far MDM_SetCmFrameModulation2(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCmFrameModulation2(UBYTE status)
{
	DspRamAccessWriteMethod1(0x331, status, 0x00);
}


/*************************************************************************
	module		:[ 93-A-6. CM Frame(Protocol(optional))]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 332
	]
	ProtoType	:[void far MDM_SetCmFrameProtocol(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCmFrameProtocol(UBYTE status)
{
	DspRamAccessWriteMethod1(0x332, status, 0x00);
}


/*************************************************************************
	module		:[ 93-A-7. CM Frame(GSTN(optional))]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 333
	]
	ProtoType	:[void far MDM_SetCmFrameGSTN(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCmFrameGSTN(UBYTE status)
{
	DspRamAccessWriteMethod1(0x333, status, 0x00);
}


/*************************************************************************
	module		:[ 93-A-8. CM Frame(Frame End)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 334
	]
	ProtoType	:[void far MDM_SetCmFrameEnd(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCmFrameEnd(void)
{
	DspRamAccessWriteMethod1(0x334, 0x7E, 0x00);
}


/*************************************************************************
	module		:[ 93-B-1. CI Frame(SYNC CI)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 32D
	]
	ProtoType	:[void far MDM_SetCiFrameSyncCi(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCiFrameSyncCi(void)
{
	DspRamAccessWriteMethod1(0x32D, 0x00, 0x00);
}


/*************************************************************************
	module		:[ 93-B-2. CI Frame(Data Call Function)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 32E
	]
	ProtoType	:[void far MDM_SetCiFrameDataCallFunc(UBYTE ){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCiFrameDataCallFunc(UBYTE status)
{
	DspRamAccessWriteMethod1(0x32E, status, 0x00);
}


/*************************************************************************
	module		:[ 93-B-3. CI Frame(EOF)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 32F
	]
	ProtoType	:[void far MDM_SetCiFrameEOF(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetCiFrameEOF(void)
{
	DspRamAccessWriteMethod1(0x32F, 0x7E, 0x00);
}


/*************************************************************************
	module		:[ 93-C-1. JM Frame(SYNC JM)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 32D
	]
	ProtoType	:[UBYTE far MDM_SetJmFrameSyncJm(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_SetJmFrameSyncJm(void)
{
	return(DspRamAccessReadMethod1(0x32D));
}


/*************************************************************************
	module		:[ 93-C-2. JM Frame(Call Function from CM)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 32E
	]
	ProtoType	:[UBYTE far MDM_GetJmFrameDataCallFunc(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetJmFrameDataCallFunc(void)
{
	return(DspRamAccessReadMethod1(0x32E));
}


/*************************************************************************
	module		:[ 93-C-3. CM Frame(Common modulation 0)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 32F
	]
	ProtoType	:[UBYTE far MDM_GetJmFrameModulation0(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetJmFrameModulation0(void)
{
	return(DspRamAccessReadMethod1(0x32F));
}


/*************************************************************************
	module		:[ 93-C-4. CM Frame(Common modulation 1)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 330
	]
	ProtoType	:[UBYTE far MDM_GetJmFrameModulation1(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetJmFrameModulation1(void)
{
	return(DspRamAccessReadMethod1(0x330));
}


/*************************************************************************
	module		:[ 93-C-5. JM Frame(Common modulation 2)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1(RO)
		Address			: 331
	]
	ProtoType	:[UBYTE far MDM_GetJmFrameModulation2(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetJmFrameModulation2(void)
{
	return(DspRamAccessReadMethod1(0x331));
}


/*************************************************************************
	module		:[ 93-C-6. JM Frame(Protocol(optional))]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 332
	]
	ProtoType	:[UBYTE far MDM_GetJmFrameProtocol(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetJmFrameProtocol(void)
{
	return(DspRamAccessReadMethod1(0x332));
}


/*************************************************************************
	module		:[ 93-C-7. JM Frame(GSTN(optional))]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 333
	]
	ProtoType	:[UBYTE far MDM_GetJmFrameGSTN(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetJmFrameGSTN(void)
{
	return(DspRamAccessReadMethod1(0x333));
}


/*************************************************************************
	module		:[ 93-C-8. JM Frame(Frame End)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 334
	]
	ProtoType	:[UBYTE far MDM_GetJmFrameEnd(void){}]
	date		:[1995/11/24]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetJmFrameEnd(void)
{
	return(DspRamAccessReadMethod1(0x334));
}


#if (0)	/** とりあえず以下のＦｕｎｃｔｉｏｎは対応せず **/
		/**   2. V.32 bis and V.33 Rate Sequence									xx		,208-2C9		**/
		/**  24. CTS OFF-to-ON Response Time(RTS-CTS Delay)							2		,202,203		**/
		/**  34. V.32 PN Length														2		,288,289 		**/
		/**  45. Equalizer Frequency Correction										4		,811			**/
		/**  51. Guard Tone Level													3		,B46			**/
		/**  53. Secondary Channel Transmitter Speed Select (V.32 bis/V.32)			1		,28E			**/
			/** Secondary Channel Receiver Speed Select (V.32 bis/V.32)				1		,28B			**/
		/**  58. V.FC Automatic Carrier Select(ACS) Enable							1		,13F(Bit 4)		**/
			/** V.FC Carrier Deviation Negotiation(CDN) Diable						1		,100(Bit 4)		**/
			/** V.FC Carrier Deviation Offset										1		,10A			**/
		/**  59. V.FC Carrier Bias 													1		,212			**/
		/**  65. V.FC Transmit Level Deviation Bias									1		,216			**/
		/**  70. V.21/V.23 CTS Mark Quality											1		,10D(Bit 3)		**/
		/**  71. V.FC Symbol Rate Bandwidth Offset(BWOFFS)							1		,13B			**/
			/** V.FC Symbol Rate Edge Offset(BEOFFS)								1		,13C			**/
		/**  72. V.FC Data Rate Sequence Mask										2		,116,117		**/
			/** V.FC Received Rate Sequence											2		,208,209		**/
		/** 100. Minimum On Time(DTMF)												3		,A78			**/
		/** 101. Minimum Off Time(DTMF)												3		,878			**/
		/** 102. Minimum Cycle Time(DTMF)											3		,978			**/
		/** 103. Minimum Dropout Time(DTMF)											3		,B78			**/
		/** 104. Maximum Speech Energy(DTMF)										3		,A77			**/
		/** 105. Frequency Deviation, Low Group(DTMF)								3		,876			**/
		/** 106. Frequency Deviation, High Group(DTMF)								3		,A76			**/
		/** 107. Negative Twist Control, TWIST4(DTMF)								3		,977			**/
		/** 108. Positive Twist Control, TWIST8(DTMF)								3		,877			**/
		/** 109. Maximum Enargy Hit Time(DTMF)										3		,A67			**/
		/** 110. ADC Speech Sample Scaling Parameter,ADCS(ADPCM)					3		,BD1			**/
		/** 111. White Noise Output Scaling Parameter,RANOISE(ADPCM)				3		,A35			**/
		/** 112. Minimum Silence Magnitude Threshold,MTHRESH(ADPCM)					3		,A36			**/
		/** 113. Detecting Silence in Speech Parameter,SILSPE(ADPCM)				3		,B37			**/
		/** 114. DEtecting Speech in Silence Parameter,SPESIL(ADPCM)				3		,B38			**/
		/** 115. Minimum Silence Magnitude Adaptation Parameter,MADAPT(ADPCM)		3		,B39			**/
#endif

/** R288F **/
/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Signal to Noise Ratio(measured during probe)]
//	function	:[
//		1.Ｖ．３４、Ｐｈａｓｅ２の受信状態の時に、Ｓ／Ｎ比を読み出す
//	]
//	return		:[
//		SECRXB = 4Xの時		:	Ｓ／Ｎ比（ｄｂ）[実際の値に対して×１０しています]
//		SECRXB = 4X以外の時	:	0xFFFFH
//	]
//	common		:[無し]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 11E
//	]
//	ProtoType	:[UWORD far MDM_GetSN_Ratio(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UWORD  MDM_GetSN_Ratio(void)
//{
//	WORD sn_value;
//	
//	sn_value = 0xFFFF;
//	if ((inp(MDM_REG_16_PORT) & 0xE0) == RX_PHASE3) {	/* 1995/12/22 Y.M into () */
//		sn_value = (UWORD)(DspRamAccessReadMethod1(0x11E) * 17 -70);
//		if (sn_value <= 0) {
//			sn_value = 0;
//		}
//	}
//	return((UWORD)(sn_value));
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Low Band Edge Frequency]
//	function	:[
//		1.Ｖ．３４、Ｐｈａｓｅ２の受信状態の時に、低域エッジ周波数を読み出す
//	]
//	return		:[
//		SECRXB = 4Xの時		:	低域エッジ周波数（Ｈｚ）[実際の値に対して×１０しています]
//		SECRXB = 4X以外の時	:	0xFFFFH
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 11C
//	]
//	ProtoType	:[UWORD far MDM_GetLowBandEdgeFrequency(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UWORD  MDM_GetLowBandEdgeFrequency(void)
//{
//	WORD freq_value;
//	
//	freq_value = 0xFFFF;
//	if ((inp(MDM_REG_16_PORT) & 0xE0) == RX_PHASE3) {	/* 1995/12/22 Y.M into () */
//		freq_value = (UWORD)(DspRamAccessReadMethod1(0x11C) * 375 + 1500);
//	}
//	return((UWORD)(freq_value));
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. High Band Edge Frequency]
//	function	:[
//		1.Ｖ．３４、Ｐｈａｓｅ２の受信状態の時に、高域エッジ周波数を読み出す
//	]
//	return		:[
//		SECRXB = 4Xの時		:	高域エッジ周波数（Ｈｚ）[実際の値に対して×１０しています]
//		SECRXB = 4X以外の時	:	0xFFFFH
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 11D
//	]
//	ProtoType	:[UWORD far MDM_GetHighBandEdgeFrequency(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UWORD  MDM_GetHighBandEdgeFrequency(void)
//{
//	WORD freq_value;
//	
//	freq_value = 0xFFFF;
//	if ((inp(MDM_REG_16_PORT) & 0xE0) == RX_PHASE3) {	/* 1995/12/22 Y.M into () */
//		freq_value = (UWORD)(DspRamAccessReadMethod1(0x11D) * 375 + 24000);
//	}
//	return((UWORD)(freq_value));
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. TX level reduction]
//	function	:[
//		1.ノーマルのＴＸレベルからの減衰を表す。
//	]
//	return		:[
//		0～E	: 単位はｄｂｍです。尚、戻り値はマイナス扱いです。（0～-E)
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 0E2
//	]
//	ProtoType	:[UBYTE far MDM_GetTxLevelReduction(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE  MDM_GetTxLevelReduction(void)
//{
//	return((UBYTE)(DspRamAccessReadMethod1(0x0E2)));
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Carrier Frequency(TX)]
//	function	:[
//		1.送信時のキャリア周波数を表す。
//	]
//	return		:[
//		01H	: High Frequency
//		00H	: Low Frequency
//		FFH	: 読み出し出来ず
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 109(bit0)
//	]
//	ProtoType	:[UBYTE far MDM_GetTxCarrierFrequency(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE  MDM_GetTxCarrierFrequency(void)
//{
//	if ((inp(MDM_REG_16_PORT) & 0xE0) == RX_PHASE3) {	/* 1995/12/22 Y.M into () */
//		if (DspRamAccessReadMethod1(0x109) & 0x01) {
//			return(HIGH_FREQUENCY);
//		}
//		else {
//			return(LOW_FREQUENCY);
//		}
//	}
//	else {
//		return((UBYTE)(INHIBIT));
//	}
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Carrier Frequency(RX)]
//	function	:[
//		1.受信時のキャリア周波数を表す。
//	]
//	return		:[
//		01H:	High Frequency
//		00H:	Low Frequency
//		FFH:	読み出し出来ず
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 211(bit0)
//	]
//	ProtoType	:[UBYTE far MDM_GetRxCarrierFrequency(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE  MDM_GetRxCarrierFrequency(void)
//{
//	if ((inp(MDM_REG_16_PORT) & 0xE0) == RX_PHASE3) {	/* 1995/12/22 Y.M into () */
//		if (DspRamAccessReadMethod1(0x211) & 0x01) {
//			return(HIGH_FREQUENCY);
//		}
//		else {
//			return(LOW_FREQUENCY);
//		}
//	}
//	else {
//		return((UBYTE)(INHIBIT));
//	}
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Non Linear Encoding(Warping)TX]
//	function	:[
//		1.送信時の非線形ＥＮＣＯＤＩＮＧ（歪み）
//	]
//	return		:[
//		0	: OFF
//		1	: ON
//		FFH	: 読み出しできず
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 3(RO)
//		Address			: C08(bitA)
//	]
//	ProtoType	:[UBYTE far MDM_GetTxNonLinearEncoding(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE  MDM_GetTxNonLinearEncoding(void)
//{
//	if (inp(MDM_REG_0F_PORT) & IO_BIT_RLSD) {
//		if (DspRamAccessReadMethod3(0xC08) & MDM_BIT_A) {
//			return(ON);
//		}
//		else {
//			return(OFF);
//		}
//	}
//	else {
//		return((UBYTE)(INHIBIT));
//	}
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Non Linear Encoding(Warping)RX]
//	function	:[
//		1.受信時の非線形ＥＮＣＯＤＩＮＧ（歪み）
//	]
//	return		:[
//		0	: OFF
//		1	: ON
//		FFH	: 読み出せず
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 3(RO)
//		Address			: C00(bitA)
//	]
//	ProtoType	:[UBYTE far MDM_GetRxNonLinearEncoding(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE MDM_GetRxNonLinearEncoding(void)
//{
//	if (inp(MDM_REG_0F_PORT) & IO_BIT_RLSD) {
//		if (DspRamAccessReadMethod3(0xC00) & MDM_BIT_A) {
//			return(ON);
//		}
//		else {
//			return(OFF);
//		}
//	}
//	else {
//		return((UBYTE)(INHIBIT));
//	}
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Trellis Mapping(TX)]
//	function	:[
//		1.
//	]
//	return		:[
//		TRELLIS_16_4D	:	00
//		TRELLIS_32_4D	:	01
//		TRELLIS_64_4D	:	11
//		INHIBIT	:	読み出せず
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 375(bit3-4)
//	]
//	ProtoType	:[UBYTE  MDM_GetTrellisMapping(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE far MDM_GetTrellisMapping(void)
//{
//
//	if (inp(MDM_REG_0F_PORT) & IO_BIT_RLSD) {
//		return((UBYTE)(DspRamAccessReadMethod1(0x375) & (MDM_BIT_3 | MDM_BIT_4)));
//	}
//	else {
//		return((UBYTE)(INHIBIT));
//	}
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Precoding(TX)]
//	function	:[
//		1.
//	]
//	return		:[
//		ON		:1
//		OFF		:0
//		INHIBIT	:読み出せず
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 2FD(bit3)
//	]
//	ProtoType	:[UBYTE  MDM_GetTxPrecoding(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE far MDM_GetTxPrecoding(void)
//{
//	if (inp(MDM_REG_0F_PORT) & IO_BIT_RLSD) {
//		if (DspRamAccessReadMethod1(0x2FD) & MDM_BIT_3) {
//			return(ON);
//		}
//		else {
//			return(OFF);
//		}
//	}
//	else {
//		return((UBYTE)(INHIBIT));
//	}
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Precoding(RX)]
//	function	:[
//		1.
//	]
//	return		:[
//		ON		:1
//		OFF		:0
//		INHIBIT	:読み出せず
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1(RO)
//		Address			: 052(bit2)
//	]
//	ProtoType	:[UBYTE  MDM_GetRxPrecoding(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE far MDM_GetRxPrecoding(void)
//{
//	if (inp(MDM_REG_0F_PORT) & IO_BIT_RLSD) {
//		if (DspRamAccessReadMethod1(0x052) & MDM_BIT_2) {
//			return(ON);
//		}
//		else {
//			return(OFF);
//		}
//	}
//	else {
//		return((UBYTE)(INHIBIT));
//	}
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Shaping(TX)]
//	function	:[
//		1.
//	]
//	return		:[
//		ON		:1
//		OFF		:0
//		INHIBIT	:読み出せず
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 3(RO)
//		Address			: A49(bitE)
//	]
//	ProtoType	:[UBYTE  MDM_GetTxShaping(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE far MDM_GetTxShaping(void)
//{
//	if (inp(MDM_REG_0F_PORT) & IO_BIT_RLSD) {
//		if (DspRamAccessReadMethod3(0xA49) & MDM_BIT_E) {
//			return(ON);
//		}
//		else {
//			return(OFF);
//		}
//	}
//	else {
//		return((UBYTE)(INHIBIT));
//	}
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Shaping(RX)]
//	function	:[
//		1.
//	]
//	return		:[
//		ON		:1
//		OFF		:0
//		INHIBIT	:読み出せず
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 3(RO)
//		Address			: 9F8(bitE)
//	]
//	ProtoType	:[UBYTE  MDM_GetRxShaping(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UBYTE far MDM_GetRxShaping(void)
//{
//	if (inp(MDM_REG_0F_PORT) & IO_BIT_RLSD) {
//		if (DspRamAccessReadMethod3(0x9F8) & MDM_BIT_E) {
//			return(ON);
//		}
//		else {
//			return(OFF);
//		}
//	}
//	else {
//		return((UBYTE)(INHIBIT));
//	}
//}
#endif

/*************************************************************************
	module		:[ xx. Selected Symbol Rate]
	function	:[
		1.
	]
	return		:[
		FFH:	読み出し出来ず
	]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1(RO)
		Address			: 2E3
	]
	ProtoType	:[UBYTE  MDM_GetSelectedSymbolRate(void){}]
	date		:[1995/11/17]
	author		:[木元　修]
*************************************************************************/
UBYTE far MDM_GetSelectedSymbolRate(void)
{
	UBYTE rate_value;

	if ((inp(MDM_REG_16_PORT) & 0xE0) == RX_PHASE3) {	/* 1995/12/22 Y.M into () */
		rate_value = DspRamAccessReadMethod1(0x2E3);
		switch (rate_value) {
		case 0:
			return(SYMBOL_2400);
		case 2:
			return(SYMBOL_2800);
		case 3:
			return(SYMBOL_3000);
		case 4:
			return(SYMBOL_3200);
		case 5:
			return(SYMBOL_3429);
		default:
			return((UBYTE)(INHIBIT));
		}
	}
	else {
		return((UBYTE)(INHIBIT));
	}
}

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Selected Pre-emphasis]
//	function	:[
//		1.
//	]
//	return		:[
//		FFH:	読み出し出来ず
//	]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 3(RO)
//		Address			: B44
//	]
//	ProtoType	:[UWORD  MDM_GetSelectedPreEmphasis(void){}]
//	date		:[1995/11/17]
//	author		:[木元　修]
//*************************************************************************/
//UWORD far MDM_GetSelectedPreEmphasis(void)
//{
//	UWORD emphasis_value;
//
//	if ((inp(MDM_REG_16_PORT) & 0xE0) == RX_PHASE3) {
//		emphasis_value = DspRamAccessReadMethod3(0xB44);
//		if (emphasis_value > 10) {
//			return(INHIBIT);
//		}
//		else {
//			return(emphasis_value);
//		}
//	}
//	else {
//		return(INHIBIT);
//	}
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Auto HDLC in Primary Channel]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 3
//		Address			: 3DF(bit 5)
//	]
//	ProtoType	:[void  MDM_SetAutoHDLCInPrimaryChannel(UBYTE ){}]
//	date		:[1995/11/21]
//	author		:[木元　修]
//*************************************************************************/
//void far MDM_SetAutoHDLCInPrimaryChannel(UBYTE sw)
//{
//	MDM_DSP_RAM_3DF_Status = DspRamAccessReadMethod3(0x3DF);	/** Add By O.K Jan.22,1996 **/
//
//	if (sw == ON) {
//		MDM_DSP_RAM_3DF_Status |= MDM_BIT_5;
//	}
//	else {
//		MDM_DSP_RAM_3DF_Status &= ~MDM_BIT_5;
//	}
//	DspRamAccessWriteMethod3(0x3DF, MDM_DSP_RAM_3DF_Status, 0x0020);
//}
#endif

/*************************************************************************
	module		:[ xx. Asymetric Control channel Rates enable]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Metchod	: 3
		Address			: 3DF(bit 6)
	]
	ProtoType	:[void  MDM_SetASYMControlChRatesEnable(UBYTE ){}]
	date		:[1995/11/21]
	author		:[木元　修]
*************************************************************************/
void far MDM_SetASYMControlChRatesEnable(UBYTE sw)
{
	MDM_DSP_RAM_3DF_Status = DspRamAccessReadMethod3(0x3DF);	/** Add By O.K Jan.22,1996 **/

	if (sw == ON) {
		MDM_DSP_RAM_3DF_Status |= MDM_BIT_6;
	}
	else {
		MDM_DSP_RAM_3DF_Status &= ~MDM_BIT_6;
	}
	DspRamAccessWriteMethod3(0x3DF, MDM_DSP_RAM_3DF_Status, 0x0040);
}


/*************************************************************************
	module		:[ xx. RX FIFO Clear]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 3
		Address			: 031(bit 7)
	]
	ProtoType	:[void  MDM_SetRxFIFOClear(void){}]
	date		:[1995/11/21]
	author		:[木元　修]
*************************************************************************/
void far MDM_SetRxFIFOClear(void)
{
	MDM_DSP_RAM_031_Status = DspRamAccessReadMethod3(0x031);	/** Add By O.K Jan.22,1996 **/

	MDM_DSP_RAM_031_Status |= MDM_BIT_7;
	DspRamAccessWriteMethod3(0x031, MDM_DSP_RAM_031_Status, 0x0080);

	MDM_DSP_RAM_031_Status = DspRamAccessReadMethod3(0x031);	/** Add By O.K Jan.22,1996 **/

	MDM_DSP_RAM_031_Status &= ~MDM_BIT_7;
	DspRamAccessWriteMethod3(0x031, MDM_DSP_RAM_031_Status, 0x0080);
}


/*************************************************************************
	module		:[ xx. TX FIFO Clear]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 3
		Address			: 031(bit 3)
	]
	ProtoType	:[void  MDM_SetTxFIFOClear(void){}]
	date		:[1995/11/21]
	author		:[木元　修]
*************************************************************************/
void far MDM_SetTxFIFOClear(void)
{
	MDM_DSP_RAM_031_Status = DspRamAccessReadMethod3(0x031);	/** Add By O.K Jan.22,1996 **/

	MDM_DSP_RAM_031_Status |= MDM_BIT_3;
	DspRamAccessWriteMethod3(0x031, MDM_DSP_RAM_031_Status, 0x0008);

	MDM_DSP_RAM_031_Status = DspRamAccessReadMethod3(0x031);	/** Add By O.K Jan.22,1996 **/

	MDM_DSP_RAM_031_Status &= ~MDM_BIT_3;
	DspRamAccessWriteMethod3(0x031, MDM_DSP_RAM_031_Status, 0x0008);
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. V.34 Phase 2 Guard Tone Level]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 3
//		Address			: 38F(bit 2)
//	]
//	ProtoType	:[void  MDM_SetV34Phase2GuardToneLevel(UBYTE ){}]
//	date		:[1995/11/21]
//	author		:[木元　修]
//*************************************************************************/
//void far MDM_SetV34Phase2GuardToneLevel(UBYTE sw)
//{
//	MDM_DSP_RAM_38F_Status = DspRamAccessReadMethod3(0x38F);	/** Add By O.K Jan.22,1996 **/
//
//	if (sw == ON) {
//		MDM_DSP_RAM_38F_Status |= MDM_BIT_2;
//	}
//	else {
//		MDM_DSP_RAM_38F_Status &= ~MDM_BIT_2;
//	}
//	DspRamAccessWriteMethod3(0x38F, MDM_DSP_RAM_38F_Status, 0x0004);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. DTMF Receiver in FSK modes]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: C0E(bit C)
//	]
//	ProtoType	:[void  MDM_SetDTMFReceiverInFSKModes(UBYTE ){}]
//	date		:[1995/11/21]
//	author		:[木元　修]
//*************************************************************************/
//void far MDM_SetDTMFReceiverInFSKModes(UBYTE sw)
//{
//	MDM_DSP_RAM_C0E_Status = DspRamAccessReadMethod3(0xC0E);	/** Add By O.K Jan.22,1996 **/
//
//	if (sw == ON) {
//		MDM_DSP_RAM_C0E_Status |= MDM_BIT_C;
//	}
//	else {
//		MDM_DSP_RAM_C0E_Status &= ~MDM_BIT_C;
//	}
//	DspRamAccessWriteMethod3(0xC0E, MDM_DSP_RAM_C0E_Status, 0x1000);
//}
#endif

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
**
** 復活します。by H.Kubo 1999/07/01
**
*/
/*************************************************************************
	module		:[Flag2Tx]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 2A6
	]
	ProtoType	:[void  MDM_SetFlag2Tx(UBYTE){}]
	date		:[1996/01/18]
	author		:[木元修]
*************************************************************************/
void far MDM_SetFlag2Tx(UBYTE count)
{
	if (count > 127) {
		count = 127;
	}
	
	DspRamAccessWriteMethod1(0x2A6, count, 0x00);
}

/*************************************************************************
	module		:[ xx. ARA Thresholds]
	function	:[
		1.
	]
	return		:[]
	common		:[
			ARAThresholdBuffer[];
	]
	condition	:[]
	comment		:[
		Access Method	: 1(RO)
		Address			: 3B0-3BF
	]
	ProtoType	:[void  MDM_GetARAThreshold(void){}]
	date		:[1995/11/17]
	author		:[木元　修]
*************************************************************************/
void far MDM_GetARAThreshold(void)
{
	UBYTE mark;
	UBYTE counter;
	UBYTE ara_value;
	
	mark = 0;
	
	/************************************
	** ３Ａ５ＨのＢｉｔ４を１にセットする
	************************************/

	for (counter=0;counter <0x10;counter ++) {
		ARAThresholdBuffer[counter] = 0;
	}
	
	for (counter=0;counter <0x10;counter ++) {
		ara_value = DspRamAccessReadMethod1((0x3B0+counter));
		if (ara_value == 0) {
			if (mark == 1) {
				break;
			}
			else {
				mark = 1;
			}
		}
		if (mark == 1) {
			/*ARAThresholdBuffer[counter] = (UWORD)(ara_value * 0x100); 1996/02/21 Y.M */
			ARAThresholdBuffer[counter] = (UWORD)(ara_value);
		}
		else {
			/*ARAThresholdBuffer[counter] = (UWORD)(ara_value); 1996/02/21 Y.M */
			ARAThresholdBuffer[counter] = (UWORD)(ara_value * 0x100);
		}
	}
}


/*************************************************************************
	module		:[ xx. EQM Averaging]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1(RO)
		Address			: 26B-26F
	]
	ProtoType	:[void  MDM_GetEQMAveraging(void){}]
	date		:[1995/11/17]
	author		:[木元　修]
*************************************************************************/
void far MDM_GetEQMAveraging(void)
{
	EQMAveragingBuffer[0] = DspRamAccessReadMethod1(0x26B);
	EQMAveragingBuffer[1] = DspRamAccessReadMethod1(0x26C);
	EQMAveragingBuffer[2] = DspRamAccessReadMethod1(0x26D);
	EQMAveragingBuffer[3] = DspRamAccessReadMethod1(0x26F);
}

/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ xx. Forced 2400 Symbol Rate when Probing SNR is Adverse]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[
//		Access Method	: 1
//		Address			: 3C0
//	]
//	ProtoType	:[void  MDM_GetForced2400SymbolRateSNR(void){}]
//	date		:[1996/02/23]
//	author		:[村田]
//*************************************************************************/
//UBYTE far MDM_GetForced2400SymbolRateSNR(void)
//{
//	return((UBYTE)(DspRamAccessReadMethod1(0x3C0)));
//}
#endif

/*************************************************************************
	module		:[ xx. Forced 2400 Symbol Rate when Probing SNR is Adverse]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 3C0
	]
	ProtoType	:[void  MDM_SetForced2400SymbolRateSNR(void){}]
	date		:[1996/02/23]
	author		:[村田]
*************************************************************************/
void far MDM_SetForced2400SymbolRateSNR(UBYTE data)
{
	/*
	** $6C6 は、シンボルレートを2400 にするSNR の閾値ではなく、
	** シンボルレートを 3429 にしないSNRの閾値でした。
	** by H.Kubo 1999/01/08
	*/
#if 0 /* (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) */ /* by H.Kubo 1998/10/05  */
@	switch (SYS_ModemVersion) {
@	case MDM_L6713_13P:
@	case MDM_L6713_14P:
@	case MDM_L6713_20P:
@	case MDM_L6713_22P:
@		DspRamAccessWriteMethod1(0x3C0, data, 0x00);
@		break;
@	case MDM_L6713_24P:
@	case MDM_L6713_26P:
@	default:
@		DspRamAccessWriteMethod1(0x6C6, data, 0x00);
@		break;
@	}
#else
	DspRamAccessWriteMethod1(0x3C0, data, 0x00);
#endif
}

/*************************************************************************
	module		:[ xx. ARAinRAN Function Enable]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 3A5
	]
	ProtoType	:[void  MDM_SetARAinRAM_FunctionEnable(void){}]
	date		:[1996/02/23]
	author		:[村田]
*************************************************************************/
void far MDM_SetARAinRAM_FunctionEnable(UBYTE sw)
{
	MDM_DSP_RAM_3A5_Status = DspRamAccessReadMethod1(0x3A5);

	if (sw == ON) {
		MDM_DSP_RAM_3A5_Status |= MDM_BIT_4;
	}
	else {
		MDM_DSP_RAM_3A5_Status &= ~MDM_BIT_4;
	}
	DspRamAccessWriteMethod1(0x3A5, MDM_DSP_RAM_3A5_Status, 0xEF);
}

/*************************************************************************
	module		:[ xx. ARA Thresold 書き込み]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1996/03/03]
	author		:[村田]
*************************************************************************/
void  MDM_SetARAThreshold(UBYTE symbol_rate)
{
	UWORD			table_data;		/* ﾃｰﾌﾞﾙのﾃﾞｰﾀ */
	UBYTE	data;			/* 設定するﾃﾞｰﾀ */
	UBYTE	counter;		/* DSP RAM ﾗｲﾄ位置 */
	UBYTE	i;				/* Table ﾘｰﾄﾞ位置 */
	UBYTE	mark;			/* 上位／下位反転 */

	i = 0;
	mark = 0;
	data = 0;

	for (counter = 0; counter < 0x0F; counter++) {
		if (i < DATA_RATE_MAX) {
			table_data = ARAThresholdTable[symbol_rate][i];	/* ﾃｰﾌﾞﾙのﾃﾞｰﾀをﾘｰﾄﾞ */
		}
		else {
			table_data = 0;
		}

		if (mark == 1) {								/* 下位ﾊﾞｲﾄﾃﾞｰﾀに反転済み？ */
			if (table_data & 0x00FF) {
				data = (UBYTE)(table_data & 0x00FF);
				i++;
			}
			else {
				data = 0;	/* ﾃﾞｰﾀ終了 */
							/* ﾙｰﾌﾟを抜けてもいいが一応残りを０で埋める */
			}
		}
		else {
			if (table_data & 0xFF00) {						/* 上位ﾊﾞｲﾄﾃﾞｰﾀか？ */
				data = (UBYTE)(table_data >> 8);	/* 上位ﾃﾞｰﾀをｼﾌﾄしてﾊﾞｲﾄ型に変換 */
				i++;										/* ﾃｰﾌﾞﾙﾘｰﾄﾞ位置更新 */
			}
			else {
				data = 0;		/* 上位／下位反転 */
				mark = 1;
			}
		}
		DspRamAccessWriteMethod1((0x3B0+counter), data, 0x00);
	}
	DspRamAccessWriteMethod1(0x3BF, 0x00, 0x00);		/* The last Valid entry in the table must be a 0 !! */
}



/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[送出ﾚﾍﾞﾙ微調整]
//	function	:[
//		1.テスト的にプライマリーチャンネルの送出レベルを上げます
//			尚、微調整出来る範囲は  ＋５．０ｄＢｍ～－５．０ｄＢｍ
//                        単位は０．５ｄＢｍです
//			０００ＸＸＸＸＸ
//			      | | | | +----- 0.5 dBm
//			      | | | +------- 1.0 dBm
//			      | | +--------- 2.0 dBm
//			      | +----------- 4.0 dBm
//		          +------------- マイナスを現す。
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	ProtoType	:[void far MDM_SetAdjustTxLevel(UBYTE){}]
//	date		:[1996/03/12]
//	author		:[木元修]
//*************************************************************************/
//void  MDM_SetAdjustTxLevel(UBYTE value)
//{
//	UWORD level_value;
//
//	if ((value & MDM_ADJUST_SIGN_FLAG) == MDM_ADJUST_SIGN_FLAG) {
//		if (value > MDM_ADJUST_MIN) {
//			value = MDM_ADJUST_MIN;
//		}
//	}
//	else {
//		if (value > MDM_ADJUST_MAX) {
//			value = MDM_ADJUST_MAX;
//		}
//		/* value = (UWORD)((UWORD)(10) - value); */
//		value = (UBYTE)((UWORD)(10) - value); /* Modified by H.Kubo 1997/07/08 */
//	}
//	
//	level_value = (UWORD)(AdjustTxOutputLevel[value]);
//	DspRamAccessWriteMethod3(0x0A48, level_value, 0x0000);
//}
#endif


/*************************************************************************
	module		:[ポーリング時の送受変更]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[MDM]
	ProtoType	:[void far MDM_FlipSrcRcp(void){}]
	date		:[1996/06/26]
	author		:[木元修]
*************************************************************************/
UBYTE reg_b1_value = 0;

void MDM_FlipSrcRcp(void)
{
/*	UBYTE reg_b1_value; */

	reg_b1_value = DspRamAccessReadMethod1((UWORD)(0xB1));
	if (reg_b1_value & 0x10) {
		DspRamAccessWriteMethod1((UWORD)(0xB1),0x00,0xEF);
	}
	else {
		DspRamAccessWriteMethod1((UWORD)(0xB1),0x10,0xEF);
	}
}
	



/*************************************************************************
	module		:[Forced PPh for Control Channel.]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[MDM]
	ProtoType	:[void  MDM_SetForcedPPh(void){}]
	date		:[1996/07/17]
	author		:[木元修]
*************************************************************************/
UWORD read_value = 0;
void  MDM_SetForcedPPh(void)
{
	if (SYS_ModemVersion == MDM_L6713_13P) {
		read_value = DspRamAccessReadMethod4(0x3DE);

		if ((read_value & 0x000F) == 1) {
			read_value |= 0x0002;
		}
		else {
			read_value -= 1;
		}
		DspRamAccessWriteMethod3(0x3DE,(UWORD)read_value,0x0000);
	}
}

/*
** R288F 22P 以降用の関数です。
** H.Kubo 1998/08/11 
*/
/*************************************************************************
	module		:[Enable Detection of a valid training sequence before RLSD turns on.]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[void  MDM_SetForcedPPh(void){}]
	date		:[1998/08/11]
	author		:[久保博]
*************************************************************************/
void MDM_EnableFastTrainingDetection(void)
{
	DspRamAccessWriteMethod1(0x6C1, 0x08, 0xF7);
}
/*************************************************************************
	module		:[Enable Extended FIFO]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[void MDM_EnableExtendedFIFO(void)]
	date		:[1998/08/11]
	author		:[久保博]
*************************************************************************/
void MDM_EnableExtendedFIFO(void)
{
#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	if (SYS_ModemVersion >= MDM_L6719_12P_ES) {
		DspRamAccessWriteMethod1(0x0E8, 0x00, 0xFE); /* For Tx FIFO, Reset bit 0 of 0xE8 */
		DspRamAccessWriteMethod1(0x0E8, 0x00, 0xFD); /* For Rx FIFO, Reset bit 1 of 0xE8 */
	} else {
		DspRamAccessWriteMethod1(0x087, 0x02, 0xFD); /* Set bit 1 of 0x87 */
	}
#else
	DspRamAccessWriteMethod1(0x087, 0x00, 0xFD); /* Reset bit 1 of 0x87 */
#endif
}
/*************************************************************************
	module		:[Disable Extended FIFO]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[void MDM_DisableExtendedFIFO(void)]
	date		:[1998/10/19]
	author		:[久保博]
*************************************************************************/
void MDM_DisableExtendedFIFO(void)
{
#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	if (SYS_ModemVersion >= MDM_L6719_12P_ES) {
		DspRamAccessWriteMethod1(0x0E8, 0x01, 0xFE); /* For Tx FIFO, Set bit 0 of 0xE8 */
		DspRamAccessWriteMethod1(0x0E8, 0x02, 0xFD); /* For Rx FIFO, Set bit 1 of 0xE8 */
	} else {
	DspRamAccessWriteMethod1(0x087, 0x02, 0xFD); /* Set bit 1 of 0x87 */
	}
#else
	DspRamAccessWriteMethod1(0x087, 0x02, 0xFD); /* Set bit 1 of 0x87 */
#endif
}
/*************************************************************************
	module		:[Enable Extended Tx FIFO]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[void  MDM_SetForcedPPh(void){}]
	date		:[1998/08/11]
	author		:[久保博]
*************************************************************************/
void MDM_EnableExtendedTxFIFO(void)
{
	DspRamAccessWriteMethod1(0x702, 0x01, 0xFE); /* set bit 0 of 0x702 */
}
/*************************************************************************
	module		:[Enable Extended Tx FIFO]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[void  MDM_SetForcedPPh(void){}]
	date		:[1998/08/11]
	author		:[久保博]
*************************************************************************/
void MDM_DisableExtendedTxFIFO(void)
{
	DspRamAccessWriteMethod1(0x702, 0x00, 0xFE); /* reset bit 0 of 0x702 */
}
/*************************************************************************
	module		:[Enable Extended Rx FIFO]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[void  MDM_SetForcedPPh(void){}]
	date		:[1998/08/11]
	author		:[久保博]
*************************************************************************/
void MDM_EnableExtendedRxFIFO(void)
{
	DspRamAccessWriteMethod1(0x701, 0x01, 0xFE); /* set bit 0 of 0x701 */
}
/*************************************************************************
	module		:[Set Capacity Of Extended Rx FIFO]
	function	:[
		1. Rx FIFO の容量を引数の値に設定する
		2. Tx FIFO の容量を残りの容量に設定する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[void  ]
	date		:[1998/10/05]
	author		:[久保博]
*************************************************************************/
void MDM_SetCapacityOfExtendedRxFIFO(UBYTE capacity)
{
	UWORD data = 0;
	data = (UWORD) capacity;
	data <<= 8;
	data &= 0xff00;
	DspRamAccessWriteMethod2(0x704, 0x705, data, 0x0000); /* Rx Buffer */
	if (capacity < 0xff) {
		capacity++;
	}
	else {
		capacity = 0;
	}
	data = 0x00ff;
	data |= (capacity << 8);
	DspRamAccessWriteMethod2(0x708, 0x709, data, 0x0000); /* Tx Buffer */
}

/*************************************************************************
	module		:[ xx. Disable 3429 Symbol Rate when Probing SNR is Adverse]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		Access Method	: 1
		Address			: 6C6
	]
	ProtoType	:[void  MDM_Disable3429SymbolRateSNR(void){}]
	date		:[1999/03/01]
	author		:[久保博]
*************************************************************************/
void  MDM_Disable3429SymbolRateSNR(UBYTE data)
{
#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	if (SYS_ModemVersion >= MDM_L6719_12P_ES) {
		DspRamAccessWriteMethod1(0x6D1, data, 0x00);
	} else {
		DspRamAccessWriteMethod1(0x6C6, data, 0x00);
	}
#else
	DspRamAccessWriteMethod1(0x6C6, data, 0x00);
#endif
}

/* YAWARAより移植 2002/01/17 T.Takagi */
#ifdef MDM_LOOP_BUG_FIX
UBYTE MDM_CheckBitMEACC(void)
{
	UWORD break_timer;

	break_timer = 0xFFFF;	/* ICE割り込み禁止で測定値 MAX 96m367usでした｡ */

	while(( inp( MDM_REG_1D_PORT ) & IO_BIT_MEACC )) {
		break_timer--;
		if (break_timer == 0) {
			return (0);
			break;
		}
	}
	return (1);
}
#endif

#ifdef MDM_INT_DMA_BUG_FIX
void  MDM_SetMaskingRegsiter0A(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x246, mask_data, 0x00);
}

void  MDM_SetMaskingRegsiter0B(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x245, mask_data, 0x0E);
}

void  MDM_SetMaskingRegsiter0C(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x244, mask_data, 0x61);
}

void  MDM_SetMaskingRegsiter0D(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x243, mask_data, 0x3D);
}

void  MDM_SetMaskingRegsiter0E(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x242, mask_data, 0xA0);
}

void  MDM_SetMaskingRegsiter0F(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x241, mask_data, 0x04);
}

void  MDM_SetMaskingRegsiter1A(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x27D, mask_data, 0xF7);
}

void  MDM_SetMaskingRegsiter1B(UBYTE mask_data)
{
	DspRamAccessWriteMethod1(0x27C, mask_data, 0x00);
}

#endif
