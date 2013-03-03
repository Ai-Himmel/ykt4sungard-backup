/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: KEY_TBL.C
*	Author		: 搉曈堦復
*	Date		: 1996/10/16
*	RealTimeOS	: 俼俬俽俠乮俽俫俈侽係俁乯儌僯僞乕
*	Description	: 僉乕僥乕僽儖愰尵
*	Maintenance	: 1997/07/17 PRO_PANEL==ANK愱梡僼傽僀儖側偺偱丄
*	                         \src\atlanta\opr\ank\define偵堏摦偟傑偡丅by O.Kimoto
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"

#include	"\src\atlanta\opr\ank\define\opr_def.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\sh_port.h"
#endif

/*********************************************
 * 僉乕億乕僩僥乕僽儖	22Byte
 ********************************************/
#if (PRO_KEYPANEL != PANEL_HINOKI) && (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2)	/* 1998/09/22 by T.Soneoka */
																		/* Add by Y.Kano 2003/07/11 */
 #if (PRO_CPU == SH7043)
	CONST UDWORD KeyPortTable[KEY_MATRICS_COLUM_MAX] = {
		KEY0_PORT, KEY1_PORT, KEY2_PORT, KEY3_PORT, KEY4_PORT,
		KEY5_PORT, KEY6_PORT, KEY7_PORT, KEY8_PORT, KEY9_PORT
	};
 #endif
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B)
/*******************************************
 * 僉乕僥乕僽儖侾乮僔乕僩侾乯
 ******************************************/
CONST UBYTE KeyTableSheet1[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{NULL,				/* 俢侽丗/LCDBUSY						*/
	 NULL,				/* 俢侾丗枹巊梡							*/
	 NULL,				/* 俢俀丗儚儞僞僢僠愗懼偊				*/
	 NULL,				/* 俢俁丗枹巊梡							*/
	 NULL,				/* 俢係丗枹巊梡							*/
	 NULL,				/* 俢俆丗枹巊梡							*/
	 REVIEW_KEY,		/* 俢俇丗捠怣拞巭乛妋擣					*/
	 COPY_FAX_KEY},		/* 俢俈丗僐僺乕乛僼傽僋僗				*/

	/* KEY1_PORT 宿被草 */
	{ONETOUCH_06_KEY,	/* 俢侽丗侽俇俥乛係俇					*/
	 ONETOUCH_01_KEY,	/* 俢侾丗侽侾俙乛係侾両					*/
	 ONETOUCH_05_KEY,	/* 俢俀丗侽俆俤乛係俆					*/
	 ONETOUCH_04_KEY,	/* 俢俁丗侽係俢乛係係亾					*/
	 ONETOUCH_03_KEY,	/* 俢係丗侽俁俠乛係俁亹					*/
	 ONETOUCH_02_KEY,	/* 俢俆丗侽俀俛乛係俀乭					*/
	 ONETOUCH_08_KEY,	/* 俢俇丗侽俉俫乛係俉					*/
	 ONETOUCH_07_KEY},	/* 俢俈丗侽俈俧乛係俈					*/

	/* KEY2_PORT 宿被草 */
	{TEN_3_KEY,			/* 俢侽丗俁								*/
	 TEN_6_KEY,			/* 俢侾丗俇								*/
	 TEN_9_KEY,			/* 俢俀丗俋								*/
	 TEN_SHARP_KEY,		/* 俢俁丗仈								*/
	 START_KEY,			/* 俢係丗僗僞乕僩						*/
	 CLEAR_KEY,			/* 俢俆丗僋儕傾							*/
	 MODE_KEY,			/* 俢俇丗夋幙							*/
	 REDUCTION_KEY},	/* 俢俈丗弅彫丒乮儅乕僉儏儕乕乯			*/

	/* KEY3_PORT 宿被草 */
	{BROADCAST_KEY,		/* 俢侽丗摨曬							*/
	 SPECIAL_KEY,		/* 俢侾丗墳梡捠怣						*/
	 GROUP_KEY,			/* 俢俀丗僌儖乕僾						*/
	 SPEED_KEY,			/* 俢俁丗抁弅乛揹榖挔					*/
	 BOOK_DOC_SIZE_KEY,	/* 俢係丗僽僢僋尨峞僒僀僘				*/
	 MEMORY_TX_KEY,		/* 俢俆丗儊儌儕憲怣						*/
	 FUNCTION_KEY,		/* 俢俇丗婡擻乛亜						*/
	 SORT_KEY},			/* 俢俈丗僜乕僩丒僟僀儎儖婰崋			*/

	/* KEY4_PORT 宿被草 */
	{ONETOUCH_14_KEY,	/* 俢侽丗侾係俶乛俆係					*/
	 ONETOUCH_09_KEY,	/* 俢侾丗侽俋倝乛係俋丟					*/
	 ONETOUCH_13_KEY,	/* 俢俀丗侾俁俵乛俆俁					*/
	 ONETOUCH_12_KEY,	/* 俢俁丗侾俀俴乛俆俀亜					*/
	 ONETOUCH_11_KEY,	/* 俢係丗侾侾俲乛俆侾亖					*/
	 ONETOUCH_10_KEY,	/* 俢俆丗侾侽俰乛俆侽亙					*/
	 ONETOUCH_16_KEY,	/* 俢俇丗侾俇俹乛俆俇					*/
	 ONETOUCH_15_KEY},	/* 俢俈丗侾俆俷乛俆俆					*/

	/* KEY5_PORT 宿被草 */
	{ONETOUCH_22_KEY,	/* 俢侽丗俀俀倁乛俇俀					*/
	 ONETOUCH_17_KEY,	/* 俢侾丗侾俈俻乛俆俈丠					*/
	 ONETOUCH_21_KEY,	/* 俢俀丗俀侾倀乛俇侾					*/
	 ONETOUCH_20_KEY,	/* 俢俁丗俀侽俿乛俇侽乵					*/
	 ONETOUCH_19_KEY,	/* 俢係丗侾俋俽乛俆俋乶					*/
	 ONETOUCH_18_KEY,	/* 俢俆丗侾俉俼乛俆俉仐					*/
	 ONETOUCH_24_KEY,	/* 俢俇丗俀係倃乛俇係					*/
	 ONETOUCH_23_KEY},	/* 俢俈丗俀俁倂乛俇俁					*/

	/* KEY6_PORT 宿被草 */
	{TEN_2_KEY,			/* 俢侽丗俀								*/
	 TEN_5_KEY,			/* 俢侾丗俆								*/
	 TEN_8_KEY,			/* 俢俀丗俉								*/
	 TEN_0_KEY,			/* 俢俁丗侽								*/
	 PAPER_SELECT_KEY,	/* 俢係丗梡巻慖戰丒儕僟僀儎儖乛億乕僘	*/
	 SET_KEY,			/* 俢俆丗僙僢僩							*/
	 HOOK_KEY,			/* 俢俇丗僼僢僋乛夛榖梊栺				*/
	 CONTRAST_KEY},		/* 俢俈丗擹搙							*/

	/* KEY7_PORT 宿被草 */
	{TEN_1_KEY,			/* 俢侽丗侾								*/
	 TEN_4_KEY,			/* 俢侾丗係								*/
	 TEN_7_KEY,			/* 俢俀丗俈								*/
	 TEN_AST_KEY,		/* 俢俁丗仏								*/
	 STOP_KEY,			/* 俢係丗僗僩僢僾						*/
	 COPY_RESET_KEY,	/* 俢俆丗僐僺乕儕僙僢僩					*/
	 CURSOR_LEFT_KEY,	/* 俢俇丗亙								*/
	 MAGNIFICATION_KEY},/* 俢俈丗奼戝丒乮僼儔僢僔儏乯			*/

	/* KEY8_PORT 宿被草 */
	{ONETOUCH_38_KEY,	/* 俢侽丗俁俉 擔杮岅乛俈俉				*/
	 ONETOUCH_33_KEY,	/* 俢侾丗俁俁乮乛俈俁					*/
	 ONETOUCH_37_KEY,	/* 俢俀丗俁俈乛乛俈俈					*/
	 ONETOUCH_36_KEY,	/* 俢俁丗俁俇亅乛俈俇					*/
	 ONETOUCH_35_KEY,	/* 俢係丗俁俆亄乛俈俆					*/
	 ONETOUCH_34_KEY,	/* 俢俆丗俁係乯乛俈係					*/
	 ONETOUCH_40_KEY,	/* 俢俇丗係侽 僐乕僪乛俉侽 僐乕僪		*/
	 ONETOUCH_39_KEY},	/* 俢俈丗俁俋乛俈俋						*/

	/* KEY9_PORT 宿被草 */
	{ONETOUCH_30_KEY,	/* 俢侽丗俁侽乫乛俈侽					*/
	 ONETOUCH_25_KEY,	/* 俢侾丗俀俆倄乛俇俆乷					*/
	 ONETOUCH_29_KEY,	/* 俢俀丗俀俋丗乛俇俋					*/
	 ONETOUCH_28_KEY,	/* 俢俁丗俀俉丏乛俇俉					*/
	 ONETOUCH_27_KEY,	/* 俢係丗俀俈丆乛俇俈丵					*/
	 ONETOUCH_26_KEY,	/* 俢俆丗俀俇倅乛俇俇乸					*/
	 ONETOUCH_32_KEY,	/* 俢俇丗俁俀丂乛俈俀					*/
	 ONETOUCH_31_KEY}	/* 俢俈丗俁侾仌乛俈侾					*/
};

/*******************************************
 * 僉乕僥乕僽儖俀乮僔乕僩俀乯
 ******************************************/
CONST UBYTE KeyTableSheet2[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{NULL,				/* 俢侽丗/LCDBUSY						*/
	 NULL,				/* 俢侾丗枹巊梡							*/
	 NULL,				/* 俢俀丗儚儞僞僢僠愗懼偊				*/
	 NULL,				/* 俢俁丗枹巊梡							*/
	 NULL,				/* 俢係丗枹巊梡							*/
	 NULL,				/* 俢俆丗枹巊梡							*/
	 REVIEW_KEY,		/* 俢俇丗捠怣拞巭乛妋擣					*/
	 COPY_FAX_KEY},		/* 俢俈丗僐僺乕乛僼傽僋僗				*/

	/* KEY1_PORT 宿被草 */
	{ONETOUCH_46_KEY,	/* 俢侽丗侽俇俥乛係俇					*/
	 ONETOUCH_41_KEY,	/* 俢侾丗侽侾俙乛係侾両					*/
	 ONETOUCH_45_KEY,	/* 俢俀丗侽俆俤乛係俆					*/
	 ONETOUCH_44_KEY,	/* 俢俁丗侽係俢乛係係亾					*/
	 ONETOUCH_43_KEY,	/* 俢係丗侽俁俠乛係俁亹					*/
	 ONETOUCH_42_KEY,	/* 俢俆丗侽俀俛乛係俀乭					*/
	 ONETOUCH_48_KEY,	/* 俢俇丗侽俉俫乛係俉					*/
	 ONETOUCH_47_KEY},	/* 俢俈丗侽俈俧乛係俈					*/

	/* KEY2_PORT 宿被草 */
	{TEN_3_KEY,			/* 俢侽丗俁								*/
	 TEN_6_KEY,			/* 俢侾丗俇								*/
	 TEN_9_KEY,			/* 俢俀丗俋								*/
	 TEN_SHARP_KEY,		/* 俢俁丗仈								*/
	 START_KEY,			/* 俢係丗僗僞乕僩						*/
	 CLEAR_KEY,			/* 俢俆丗僋儕傾							*/
	 MODE_KEY,			/* 俢俇丗夋幙							*/
	 REDUCTION_KEY},	/* 俢俈丗弅彫丒乮儅乕僉儏儕乕乯			*/

	/* KEY3_PORT 宿被草 */
	{BROADCAST_KEY,		/* 俢侽丗摨曬							*/
	 SPECIAL_KEY,		/* 俢侾丗墳梡捠怣						*/
	 GROUP_KEY,			/* 俢俀丗僌儖乕僾						*/
	 SPEED_KEY,			/* 俢俁丗抁弅乛揹榖挔					*/
	 BOOK_DOC_SIZE_KEY,	/* 俢係丗僽僢僋尨峞僒僀僘				*/
	 MEMORY_TX_KEY,		/* 俢俆丗儊儌儕憲怣						*/
	 FUNCTION_KEY,		/* 俢俇丗婡擻乛亜						*/
	 SORT_KEY},			/* 俢俈丗僜乕僩丒僟僀儎儖婰崋			*/

	/* KEY4_PORT 宿被草 */
	{ONETOUCH_54_KEY,	/* 俢侽丗侾係俶乛俆係					*/
	 ONETOUCH_49_KEY,	/* 俢侾丗侽俋倝乛係俋丟					*/
	 ONETOUCH_53_KEY,	/* 俢俀丗侾俁俵乛俆俁					*/
	 ONETOUCH_52_KEY,	/* 俢俁丗侾俀俴乛俆俀亜					*/
	 ONETOUCH_51_KEY,	/* 俢係丗侾侾俲乛俆侾亖					*/
	 ONETOUCH_50_KEY,	/* 俢俆丗侾侽俰乛俆侽亙					*/
	 ONETOUCH_56_KEY,	/* 俢俇丗侾俇俹乛俆俇					*/
	 ONETOUCH_55_KEY},	/* 俢俈丗侾俆俷乛俆俆					*/

	/* KEY5_PORT 宿被草 */
	{ONETOUCH_62_KEY,	/* 俢侽丗俀俀倁乛俇俀					*/
	 ONETOUCH_57_KEY,	/* 俢侾丗侾俈俻乛俆俈丠					*/
	 ONETOUCH_61_KEY,	/* 俢俀丗俀侾倀乛俇侾					*/
	 ONETOUCH_60_KEY,	/* 俢俁丗俀侽俿乛俇侽乵					*/
	 ONETOUCH_59_KEY,	/* 俢係丗侾俋俽乛俆俋乶					*/
	 ONETOUCH_58_KEY,	/* 俢俆丗侾俉俼乛俆俉仐					*/
	 ONETOUCH_64_KEY,	/* 俢俇丗俀係倃乛俇係					*/
	 ONETOUCH_63_KEY},	/* 俢俈丗俀俁倂乛俇俁					*/

	/* KEY6_PORT 宿被草 */
	{TEN_2_KEY,			/* 俢侽丗俀								*/
	 TEN_5_KEY,			/* 俢侾丗俆								*/
	 TEN_8_KEY,			/* 俢俀丗俉								*/
	 TEN_0_KEY,			/* 俢俁丗侽								*/
	 PAPER_SELECT_KEY,	/* 俢係丗梡巻慖戰丒儕僟僀儎儖乛億乕僘	*/
	 SET_KEY,			/* 俢俆丗僙僢僩							*/
	 HOOK_KEY,			/* 俢俇丗僼僢僋乛夛榖梊栺				*/
	 CONTRAST_KEY},		/* 俢俈丗擹搙							*/

	/* KEY7_PORT 宿被草 */
	{TEN_1_KEY,			/* 俢侽丗侾								*/
	 TEN_4_KEY,			/* 俢侾丗係								*/
	 TEN_7_KEY,			/* 俢俀丗俈								*/
	 TEN_AST_KEY,		/* 俢俁丗仏								*/
	 STOP_KEY,			/* 俢係丗僗僩僢僾						*/
	 COPY_RESET_KEY,	/* 俢俆丗僐僺乕儕僙僢僩					*/
	 CURSOR_LEFT_KEY,	/* 俢俇丗亙								*/
	 MAGNIFICATION_KEY},/* 俢俈丗奼戝丒乮僼儔僢僔儏乯			*/

	/* KEY8_PORT 宿被草 */
	{ONETOUCH_78_KEY,	/* 俢侽丗俁俉 擔杮岅乛俈俉				*/
	 ONETOUCH_73_KEY,	/* 俢侾丗俁俁乮乛俈俁					*/
	 ONETOUCH_77_KEY,	/* 俢俀丗俁俈乛乛俈俈					*/
	 ONETOUCH_76_KEY,	/* 俢俁丗俁俇亅乛俈俇					*/
	 ONETOUCH_75_KEY,	/* 俢係丗俁俆亄乛俈俆					*/
	 ONETOUCH_74_KEY,	/* 俢俆丗俁係乯乛俈係					*/
	 ONETOUCH_80_KEY,	/* 俢俇丗係侽 僐乕僪乛俉侽 僐乕僪		*/
	 ONETOUCH_79_KEY},	/* 俢俈丗俁俋乛俈俋						*/

	/* KEY9_PORT 宿被草 */
	{ONETOUCH_70_KEY,	/* 俢侽丗俁侽乫乛俈侽					*/
	 ONETOUCH_65_KEY,	/* 俢侾丗俀俆倄乛俇俆乷					*/
	 ONETOUCH_69_KEY,	/* 俢俀丗俀俋丗乛俇俋					*/
	 ONETOUCH_68_KEY,	/* 俢俁丗俀俉丏乛俇俉					*/
	 ONETOUCH_67_KEY,	/* 俢係丗俀俈丆乛俇俈丵					*/
	 ONETOUCH_66_KEY,	/* 俢俆丗俀俇倅乛俇俇乸					*/
	 ONETOUCH_72_KEY,	/* 俢俇丗俁俀丂乛俈俀					*/
	 ONETOUCH_71_KEY}	/* 俢俈丗俁侾仌乛俈侾					*/
};

/*******************************************
 * 僉乕僞僀僾僥乕僽儖侾乮僔乕僩侾乯
 *******************************************/
CONST UBYTE KeyTypeTable1[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{NULL,				/* 俢侽丗/LCDBUSY						*/
	 NULL,				/* 俢侾丗枹巊梡							*/
	 NULL,				/* 俢俀丗儚儞僞僢僠愗懼偊				*/
	 NULL,				/* 俢俁丗枹巊梡							*/
	 NULL,				/* 俢係丗枹巊梡							*/
	 NULL,				/* 俢俆丗枹巊梡							*/
	 REVIEW,			/* 俢俇丗捠怣拞巭乛妋擣					*/
	 COPY_FAX},			/* 俢俈丗僐僺乕乛僼傽僋僗				*/

	/* KEY1_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗侽俇俥乛係俇					*/
	 ONETOUCH,			/* 俢侾丗侽侾俙乛係侾両					*/
	 ONETOUCH,			/* 俢俀丗侽俆俤乛係俆					*/
	 ONETOUCH,			/* 俢俁丗侽係俢乛係係亾					*/
	 ONETOUCH,			/* 俢係丗侽俁俠乛係俁亹					*/
	 ONETOUCH,			/* 俢俆丗侽俀俛乛係俀乭					*/
	 ONETOUCH,			/* 俢俇丗侽俉俫乛係俉					*/
	 ONETOUCH},			/* 俢俈丗侽俈俧乛係俈					*/

	/* KEY2_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗俁								*/
	 NUMBER,			/* 俢侾丗俇								*/
	 NUMBER,			/* 俢俀丗俋								*/
	 SHARP,				/* 俢俁丗仈								*/
	 START,				/* 俢係丗僗僞乕僩						*/
	 CLEAR,				/* 俢俆丗僋儕傾							*/
	 SINGLE,			/* 俢俇丗夋幙							*/
	 REDUCTION},		/* 俢俈丗弅彫丒乮儅乕僉儏儕乕乯			*/

	/* KEY3_PORT 宿被草 */
	{BROADCAST,			/* 俢侽丗摨曬							*/
	 SPECIAL,			/* 俢侾丗墳梡捠怣						*/
	 GROUP,				/* 俢俀丗僌儖乕僾						*/
	 SPEED,				/* 俢俁丗抁弅乛揹榖挔					*/
	 BOOK_DOC_SIZE,		/* 俢係丗僽僢僋尨峞僒僀僘				*/
	 SINGLE,			/* 俢俆丗儊儌儕憲怣						*/
	 FUNCTION,			/* 俢俇丗婡擻乛亜						*/
	 SORT},				/* 俢俈丗僜乕僩丒僟僀儎儖婰崋			*/

	/* KEY4_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗侾係俶乛俆係					*/
	 ONETOUCH,			/* 俢侾丗侽俋倝乛係俋丟					*/
	 ONETOUCH,			/* 俢俀丗侾俁俵乛俆俁					*/
	 ONETOUCH,			/* 俢俁丗侾俀俴乛俆俀亜					*/
	 ONETOUCH,			/* 俢係丗侾侾俲乛俆侾亖					*/
	 ONETOUCH,			/* 俢俆丗侾侽俰乛俆侽亙					*/
	 ONETOUCH,			/* 俢俇丗侾俇俹乛俆俇					*/
	 ONETOUCH},			/* 俢俈丗侾俆俷乛俆俆					*/

	/* KEY5_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗俀俀倁乛俇俀					*/
	 ONETOUCH,			/* 俢侾丗侾俈俻乛俆俈丠					*/
	 ONETOUCH,			/* 俢俀丗俀侾倀乛俇侾					*/
	 ONETOUCH,			/* 俢俁丗俀侽俿乛俇侽乵					*/
	 ONETOUCH,			/* 俢係丗侾俋俽乛俆俋乶					*/
	 ONETOUCH,			/* 俢俆丗侾俉俼乛俆俉仐					*/
	 ONETOUCH,			/* 俢俇丗俀係倃乛俇係					*/
	 ONETOUCH},			/* 俢俈丗俀俁倂乛俇俁					*/

	/* KEY6_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗俀								*/
	 NUMBER,			/* 俢侾丗俆								*/
	 NUMBER,			/* 俢俀丗俉								*/
	 NUMBER,			/* 俢俁丗侽								*/
	 PAPER_SELECT,		/* 俢係丗梡巻慖戰丒儕僟僀儎儖乛億乕僘	*/
	 ENTER,				/* 俢俆丗僙僢僩							*/
	 HOOK,				/* 俢俇丗僼僢僋乛夛榖梊栺				*/
	 SINGLE},			/* 俢俈丗擹搙							*/

	/* KEY7_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗侾								*/
	 NUMBER,			/* 俢侾丗係								*/
	 NUMBER,			/* 俢俀丗俈								*/
	 AST,				/* 俢俁丗仏								*/
	 STOP,				/* 俢係丗僗僩僢僾						*/
	 COPY_RESET,		/* 俢俆丗僐僺乕儕僙僢僩					*/
	 LEFT_ARROW,		/* 俢俇丗亙								*/
	 MAGNIFICATION},	/* 俢俈丗奼戝丒乮僼儔僢僔儏乯			*/

	/* KEY8_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗俁俉 擔杮岅乛俈俉				*/
	 ONETOUCH,			/* 俢侾丗俁俁乮乛俈俁					*/
	 ONETOUCH,			/* 俢俀丗俁俈乛乛俈俈					*/
	 ONETOUCH,			/* 俢俁丗俁俇亅乛俈俇					*/
	 ONETOUCH,			/* 俢係丗俁俆亄乛俈俆					*/
	 ONETOUCH,			/* 俢俆丗俁係乯乛俈係					*/
	 ONETOUCH,			/* 俢俇丗係侽喊霓乛俉侽喊霓				*/
	 ONETOUCH},			/* 俢俈丗俁俋乛俈俋						*/

	/* KEY9_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗俁侽乫乛俈侽					*/
	 ONETOUCH,			/* 俢侾丗俀俆倄乛俇俆乷					*/
	 ONETOUCH,			/* 俢俀丗俀俋丗乛俇俋					*/
	 ONETOUCH,			/* 俢俁丗俀俉丏乛俇俉					*/
	 ONETOUCH,			/* 俢係丗俀俈丆乛俇俈丵					*/
	 ONETOUCH,			/* 俢俆丗俀俇倅乛俇俇乸					*/
	 ONETOUCH,			/* 俢俇丗俁俀丂乛俈俀					*/
	 ONETOUCH}			/* 俢俈丗俁侾仌乛俈侾					*/
};

/*******************************************
 * 僉乕僞僀僾僥乕僽儖俀乮僔乕僩俀乯
 *******************************************/
CONST UBYTE KeyTypeTable2[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{NULL,				/* 俢侽丗/LCDBUSY						*/
	 NULL,				/* 俢侾丗枹巊梡							*/
	 NULL,				/* 俢俀丗儚儞僞僢僠愗懼偊				*/
	 NULL,				/* 俢俁丗枹巊梡							*/
	 NULL,				/* 俢係丗枹巊梡							*/
	 NULL,				/* 俢俆丗枹巊梡							*/
	 REVIEW,			/* 俢俇丗捠怣拞巭乛妋擣					*/
	 COPY_FAX},			/* 俢俈丗僐僺乕乛僼傽僋僗				*/

	/* KEY1_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗侽俇俥乛係俇					*/
	 ONETOUCH,			/* 俢侾丗侽侾俙乛係侾両					*/
	 ONETOUCH,			/* 俢俀丗侽俆俤乛係俆					*/
	 ONETOUCH,			/* 俢俁丗侽係俢乛係係亾					*/
	 ONETOUCH,			/* 俢係丗侽俁俠乛係俁亹					*/
	 ONETOUCH,			/* 俢俆丗侽俀俛乛係俀乭					*/
	 ONETOUCH,			/* 俢俇丗侽俉俫乛係俉					*/
	 ONETOUCH},			/* 俢俈丗侽俈俧乛係俈					*/

	/* KEY2_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗俁								*/
	 NUMBER,			/* 俢侾丗俇								*/
	 NUMBER,			/* 俢俀丗俋								*/
	 SHARP,				/* 俢俁丗仈								*/
	 START,				/* 俢係丗僗僞乕僩						*/
	 CLEAR,				/* 俢俆丗僋儕傾							*/
	 SINGLE,			/* 俢俇丗夋幙							*/
	 REDUCTION},		/* 俢俈丗弅彫丒乮儅乕僉儏儕乕乯			*/

	/* KEY3_PORT 宿被草 */
	{BROADCAST,			/* 俢侽丗摨曬							*/
	 SPECIAL,			/* 俢侾丗墳梡捠怣						*/
	 GROUP,				/* 俢俀丗僌儖乕僾						*/
	 SPEED,				/* 俢俁丗抁弅乛揹榖挔					*/
	 BOOK_DOC_SIZE,		/* 俢係丗僽僢僋尨峞僒僀僘				*/
	 SINGLE,			/* 俢俆丗儊儌儕憲怣						*/
	 FUNCTION,			/* 俢俇丗婡擻乛亜						*/
	 SORT},				/* 俢俈丗僜乕僩丒僟僀儎儖婰崋			*/

	/* KEY4_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗侾係俶乛俆係					*/
	 ONETOUCH,			/* 俢侾丗侽俋倝乛係俋丟					*/
	 ONETOUCH,			/* 俢俀丗侾俁俵乛俆俁					*/
	 ONETOUCH,			/* 俢俁丗侾俀俴乛俆俀亜					*/
	 ONETOUCH,			/* 俢係丗侾侾俲乛俆侾亖					*/
	 ONETOUCH,			/* 俢俆丗侾侽俰乛俆侽亙					*/
	 ONETOUCH,			/* 俢俇丗侾俇俹乛俆俇					*/
	 ONETOUCH},			/* 俢俈丗侾俆俷乛俆俆					*/

	/* KEY5_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗俀俀倁乛俇俀					*/
	 ONETOUCH,			/* 俢侾丗侾俈俻乛俆俈丠					*/
	 ONETOUCH,			/* 俢俀丗俀侾倀乛俇侾					*/
	 ONETOUCH,			/* 俢俁丗俀侽俿乛俇侽乵					*/
	 ONETOUCH,			/* 俢係丗侾俋俽乛俆俋乶					*/
	 ONETOUCH,			/* 俢俆丗侾俉俼乛俆俉仐					*/
	 ONETOUCH,			/* 俢俇丗俀係倃乛俇係					*/
	 ONETOUCH},			/* 俢俈丗俀俁倂乛俇俁					*/

	/* KEY6_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗俀								*/
	 NUMBER,			/* 俢侾丗俆								*/
	 NUMBER,			/* 俢俀丗俉								*/
	 NUMBER,			/* 俢俁丗侽								*/
	 PAPER_SELECT,		/* 俢係丗梡巻慖戰丒儕僟僀儎儖乛億乕僘	*/
	 ENTER,				/* 俢俆丗僙僢僩							*/
	 HOOK,				/* 俢俇丗僼僢僋乛夛榖梊栺				*/
	 SINGLE},			/* 俢俈丗擹搙							*/

	/* KEY7_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗侾								*/
	 NUMBER,			/* 俢侾丗係								*/
	 NUMBER,			/* 俢俀丗俈								*/
	 AST,				/* 俢俁丗仏								*/
	 STOP,				/* 俢係丗僗僩僢僾						*/
	 COPY_RESET,		/* 俢俆丗僐僺乕儕僙僢僩					*/
	 LEFT_ARROW,		/* 俢俇丗亙								*/
	 MAGNIFICATION},	/* 俢俈丗奼戝丒乮僼儔僢僔儏乯			*/

	/* KEY8_PORT 宿被草 */
	{PROGRAM,			/* 俢侽丗俁俉 擔杮岅乛俈俉				*/
	 PROGRAM,			/* 俢侾丗俁俁乮乛俈俁					*/
	 PROGRAM,			/* 俢俀丗俁俈乛乛俈俈					*/
	 PROGRAM,			/* 俢俁丗俁俇亅乛俈俇					*/
	 PROGRAM,			/* 俢係丗俁俆亄乛俈俆					*/
	 PROGRAM,			/* 俢俆丗俁係乯乛俈係					*/
	 PROGRAM,			/* 俢俇丗係侽喊霓乛俉侽喊霓				*/
	 PROGRAM},			/* 俢俈丗俁俋乛俈俋						*/

	/* KEY9_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗俁侽乫乛俈侽					*/
	 ONETOUCH,			/* 俢侾丗俀俆倄乛俇俆乷					*/
	 ONETOUCH,			/* 俢俀丗俀俋丗乛俇俋					*/
	 ONETOUCH,			/* 俢俁丗俀俉丏乛俇俉					*/
	 ONETOUCH,			/* 俢係丗俀俈丆乛俇俈丵					*/
	 ONETOUCH,			/* 俢俆丗俀俇倅乛俇俇乸					*/
	 ONETOUCH,			/* 俢俇丗俁俀丂乛俈俀					*/
	 ONETOUCH}			/* 俢俈丗俁侾仌乛俈侾					*/
};
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) */

#if (PRO_KEYPANEL == PANEL_POPLAR_L)
/*******************************************
 * 僉乕僥乕僽儖侾乮僔乕僩侾乯
 ******************************************/
CONST UBYTE KeyTableSheet1[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{NULL,				/* 俢侽丗/LCDBUSY						*/
	 NULL,				/* 俢侾丗枹巊梡							*/
	 NULL,				/* 俢俀丗儚儞僞僢僠愗懼偊				*/
	 NULL,				/* 俢俁丗枹巊梡							*/
	 NULL,				/* 俢係丗枹巊梡							*/
	 NULL,				/* 俢俆丗枹巊梡							*/
	 REVIEW_KEY,		/* 俢俇丗捠怣拞巭乛妋擣					*/
	 NULL},				/* 俢俈丗枹巊梡							*/

	/* KEY1_PORT 宿被草 */
	{ONETOUCH_06_KEY,	/* 俢侽丗侽俇俥乛係俇					*/
	 ONETOUCH_01_KEY,	/* 俢侾丗侽侾俙乛係侾両					*/
	 ONETOUCH_05_KEY,	/* 俢俀丗侽俆俤乛係俆					*/
	 ONETOUCH_04_KEY,	/* 俢俁丗侽係俢乛係係亾					*/
	 ONETOUCH_03_KEY,	/* 俢係丗侽俁俠乛係俁亹					*/
	 ONETOUCH_02_KEY,	/* 俢俆丗侽俀俛乛係俀乭					*/
	 ONETOUCH_08_KEY,	/* 俢俇丗侽俉俫乛係俉					*/
	 ONETOUCH_07_KEY},	/* 俢俈丗侽俈俧乛係俈					*/

	/* KEY2_PORT 宿被草 */
	{TEN_3_KEY,			/* 俢侽丗俁								*/
	 TEN_6_KEY,			/* 俢侾丗俇								*/
	 TEN_9_KEY,			/* 俢俀丗俋								*/
	 TEN_SHARP_KEY,		/* 俢俁丗仈								*/
	 START_KEY,			/* 俢係丗僗僞乕僩						*/
	 CLEAR_KEY,			/* 俢俆丗僋儕傾							*/
	 MODE_KEY,			/* 俢俇丗夋幙							*/
	 TONE_KEY},			/* 俢俈丗僩乕儞							*/

	/* KEY3_PORT 宿被草 */
	{BROADCAST_KEY,		/* 俢侽丗摨曬							*/
	 SPECIAL_KEY,		/* 俢侾丗墳梡捠怣						*/
	 GROUP_KEY,			/* 俢俀丗僌儖乕僾						*/
	 SPEED_KEY,			/* 俢俁丗抁弅乛揹榖挔					*/
	 STAMP_KEY,			/* 俢係丗嵪僗僞儞僾						*/
	 MEMORY_TX_KEY,		/* 俢俆丗儊儌儕憲怣						*/
	 FUNCTION_KEY,		/* 俢俇丗婡擻乛亜						*/
	 DIAL_MARK_KEY},	/* 俢俈丗僟僀儎儖婰崋					*/

	/* KEY4_PORT 宿被草 */
	{ONETOUCH_14_KEY,	/* 俢侽丗侾係俶乛俆係					*/
	 ONETOUCH_09_KEY,	/* 俢侾丗侽俋倝乛係俋丟					*/
	 ONETOUCH_13_KEY,	/* 俢俀丗侾俁俵乛俆俁					*/
	 ONETOUCH_12_KEY,	/* 俢俁丗侾俀俴乛俆俀亜					*/
	 ONETOUCH_11_KEY,	/* 俢係丗侾侾俲乛俆侾亖					*/
	 ONETOUCH_10_KEY,	/* 俢俆丗侾侽俰乛俆侽亙					*/
	 ONETOUCH_16_KEY,	/* 俢俇丗侾俇俹乛俆俇					*/
	 ONETOUCH_15_KEY},	/* 俢俈丗侾俆俷乛俆俆					*/

	/* KEY5_PORT 宿被草 */
	{ONETOUCH_22_KEY,	/* 俢侽丗俀俀倁乛俇俀					*/
	 ONETOUCH_17_KEY,	/* 俢侾丗侾俈俻乛俆俈丠					*/
	 ONETOUCH_21_KEY,	/* 俢俀丗俀侾倀乛俇侾					*/
	 ONETOUCH_20_KEY,	/* 俢俁丗俀侽俿乛俇侽乵					*/
	 ONETOUCH_19_KEY,	/* 俢係丗侾俋俽乛俆俋乶					*/
	 ONETOUCH_18_KEY,	/* 俢俆丗侾俉俼乛俆俉仐					*/
	 ONETOUCH_24_KEY,	/* 俢俇丗俀係倃乛俇係					*/
	 ONETOUCH_23_KEY},	/* 俢俈丗俀俁倂乛俇俁					*/

	/* KEY6_PORT 宿被草 */
	{TEN_2_KEY,			/* 俢侽丗俀								*/
	 TEN_5_KEY,			/* 俢侾丗俆								*/
	 TEN_8_KEY,			/* 俢俀丗俉								*/
	 TEN_0_KEY,			/* 俢俁丗侽								*/
	 REDIAL_KEY,		/* 俢係丗儕僟僀儎儖乛億乕僘				*/
	 SET_KEY,			/* 俢俆丗僙僢僩							*/
	 HOOK_KEY,			/* 俢俇丗僼僢僋乛夛榖梊栺				*/
	 CONTRAST_KEY},		/* 俢俈丗擹搙							*/

	/* KEY7_PORT 宿被草 */
	{TEN_1_KEY,			/* 俢侽丗侾								*/
	 TEN_4_KEY,			/* 俢侾丗係								*/
	 TEN_7_KEY,			/* 俢俀丗俈								*/
	 TEN_AST_KEY,		/* 俢俁丗仏								*/
	 STOP_KEY,			/* 俢係丗僗僩僢僾						*/
	 COPY_KEY,			/* 俢俆丗僐僺乕							*/
	 CURSOR_LEFT_KEY,	/* 俢俇丗亙								*/
	 HOLD_KEY},			/* 俢俈丗曐棷							*/

	/* KEY8_PORT 宿被草 */
	{ONETOUCH_38_KEY,	/* 俢侽丗俁俉 擔杮岅乛俈俉				*/
	 ONETOUCH_33_KEY,	/* 俢侾丗俁俁乮乛俈俁					*/
	 ONETOUCH_37_KEY,	/* 俢俀丗俁俈乛乛俈俈					*/
	 ONETOUCH_36_KEY,	/* 俢俁丗俁俇亅乛俈俇					*/
	 ONETOUCH_35_KEY,	/* 俢係丗俁俆亄乛俈俆					*/
	 ONETOUCH_34_KEY,	/* 俢俆丗俁係乯乛俈係					*/
	 ONETOUCH_40_KEY,	/* 俢俇丗係侽 僐乕僪乛俉侽 僐乕僪		*/
	 ONETOUCH_39_KEY},	/* 俢俈丗俁俋乛俈俋						*/

	/* KEY9_PORT 宿被草 */
	{ONETOUCH_30_KEY,	/* 俢侽丗俁侽乫乛俈侽					*/
	 ONETOUCH_25_KEY,	/* 俢侾丗俀俆倄乛俇俆乷					*/
	 ONETOUCH_29_KEY,	/* 俢俀丗俀俋丗乛俇俋					*/
	 ONETOUCH_28_KEY,	/* 俢俁丗俀俉丏乛俇俉					*/
	 ONETOUCH_27_KEY,	/* 俢係丗俀俈丆乛俇俈丵					*/
	 ONETOUCH_26_KEY,	/* 俢俆丗俀俇倅乛俇俇乸					*/
	 ONETOUCH_32_KEY,	/* 俢俇丗俁俀丂乛俈俀					*/
	 ONETOUCH_31_KEY}	/* 俢俈丗俁侾仌乛俈侾					*/
};

/*******************************************
 * 僉乕僥乕僽儖俀乮僔乕僩俀乯
 ******************************************/
CONST UBYTE KeyTableSheet2[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{NULL,				/* 俢侽丗/LCDBUSY						*/
	 NULL,				/* 俢侾丗枹巊梡							*/
	 NULL,				/* 俢俀丗儚儞僞僢僠愗懼偊				*/
	 NULL,				/* 俢俁丗枹巊梡							*/
	 NULL,				/* 俢係丗枹巊梡							*/
	 NULL,				/* 俢俆丗枹巊梡							*/
	 REVIEW_KEY,		/* 俢俇丗捠怣拞巭乛妋擣					*/
	 NULL},				/* 俢俈丗枹巊梡							*/

	/* KEY1_PORT 宿被草 */
	{ONETOUCH_46_KEY,	/* 俢侽丗侽俇俥乛係俇					*/
	 ONETOUCH_41_KEY,	/* 俢侾丗侽侾俙乛係侾両					*/
	 ONETOUCH_45_KEY,	/* 俢俀丗侽俆俤乛係俆					*/
	 ONETOUCH_44_KEY,	/* 俢俁丗侽係俢乛係係亾					*/
	 ONETOUCH_43_KEY,	/* 俢係丗侽俁俠乛係俁亹					*/
	 ONETOUCH_42_KEY,	/* 俢俆丗侽俀俛乛係俀乭					*/
	 ONETOUCH_48_KEY,	/* 俢俇丗侽俉俫乛係俉					*/
	 ONETOUCH_47_KEY},	/* 俢俈丗侽俈俧乛係俈					*/

	/* KEY2_PORT 宿被草 */
	{TEN_3_KEY,			/* 俢侽丗俁								*/
	 TEN_6_KEY,			/* 俢侾丗俇								*/
	 TEN_9_KEY,			/* 俢俀丗俋								*/
	 TEN_SHARP_KEY,		/* 俢俁丗仈								*/
	 START_KEY,			/* 俢係丗僗僞乕僩						*/
	 CLEAR_KEY,			/* 俢俆丗僋儕傾							*/
	 MODE_KEY,			/* 俢俇丗夋幙							*/
	 TONE_KEY},			/* 俢俈丗僩乕儞							*/

	/* KEY3_PORT 宿被草 */
	{BROADCAST_KEY,		/* 俢侽丗摨曬							*/
	 SPECIAL_KEY,		/* 俢侾丗墳梡捠怣						*/
	 GROUP_KEY,			/* 俢俀丗僌儖乕僾						*/
	 SPEED_KEY,			/* 俢俁丗抁弅乛揹榖挔					*/
	 STAMP_KEY,			/* 俢係丗嵪僗僞儞僾						*/
	 MEMORY_TX_KEY,		/* 俢俆丗儊儌儕憲怣						*/
	 FUNCTION_KEY,		/* 俢俇丗婡擻乛亜						*/
	 DIAL_MARK_KEY},	/* 俢俈丗僟僀儎儖婰崋					*/

	/* KEY4_PORT 宿被草 */
	{ONETOUCH_54_KEY,	/* 俢侽丗侾係俶乛俆係					*/
	 ONETOUCH_49_KEY,	/* 俢侾丗侽俋倝乛係俋丟					*/
	 ONETOUCH_53_KEY,	/* 俢俀丗侾俁俵乛俆俁					*/
	 ONETOUCH_52_KEY,	/* 俢俁丗侾俀俴乛俆俀亜					*/
	 ONETOUCH_51_KEY,	/* 俢係丗侾侾俲乛俆侾亖					*/
	 ONETOUCH_50_KEY,	/* 俢俆丗侾侽俰乛俆侽亙					*/
	 ONETOUCH_56_KEY,	/* 俢俇丗侾俇俹乛俆俇					*/
	 ONETOUCH_55_KEY},	/* 俢俈丗侾俆俷乛俆俆					*/

	/* KEY5_PORT 宿被草 */
	{ONETOUCH_62_KEY,	/* 俢侽丗俀俀倁乛俇俀					*/
	 ONETOUCH_57_KEY,	/* 俢侾丗侾俈俻乛俆俈丠					*/
	 ONETOUCH_61_KEY,	/* 俢俀丗俀侾倀乛俇侾					*/
	 ONETOUCH_60_KEY,	/* 俢俁丗俀侽俿乛俇侽乵					*/
	 ONETOUCH_59_KEY,	/* 俢係丗侾俋俽乛俆俋乶					*/
	 ONETOUCH_58_KEY,	/* 俢俆丗侾俉俼乛俆俉仐					*/
	 ONETOUCH_64_KEY,	/* 俢俇丗俀係倃乛俇係					*/
	 ONETOUCH_63_KEY},	/* 俢俈丗俀俁倂乛俇俁					*/

	/* KEY6_PORT 宿被草 */
	{TEN_2_KEY,			/* 俢侽丗俀								*/
	 TEN_5_KEY,			/* 俢侾丗俆								*/
	 TEN_8_KEY,			/* 俢俀丗俉								*/
	 TEN_0_KEY,			/* 俢俁丗侽								*/
	 REDIAL_KEY,		/* 俢係丗儕僟僀儎儖乛億乕僘				*/
	 SET_KEY,			/* 俢俆丗僙僢僩							*/
	 HOOK_KEY,			/* 俢俇丗僼僢僋乛夛榖梊栺				*/
	 CONTRAST_KEY},		/* 俢俈丗擹搙							*/

	/* KEY7_PORT 宿被草 */
	{TEN_1_KEY,			/* 俢侽丗侾								*/
	 TEN_4_KEY,			/* 俢侾丗係								*/
	 TEN_7_KEY,			/* 俢俀丗俈								*/
	 TEN_AST_KEY,		/* 俢俁丗仏								*/
	 STOP_KEY,			/* 俢係丗僗僩僢僾						*/
	 COPY_KEY,			/* 俢俆丗僐僺乕							*/
	 CURSOR_LEFT_KEY,	/* 俢俇丗亙								*/
	 HOLD_KEY},			/* 俢俈丗曐棷							*/

	/* KEY8_PORT 宿被草 */
	{ONETOUCH_78_KEY,	/* 俢侽丗俁俉 擔杮岅乛俈俉				*/
	 ONETOUCH_73_KEY,	/* 俢侾丗俁俁乮乛俈俁					*/
	 ONETOUCH_77_KEY,	/* 俢俀丗俁俈乛乛俈俈					*/
	 ONETOUCH_76_KEY,	/* 俢俁丗俁俇亅乛俈俇					*/
	 ONETOUCH_75_KEY,	/* 俢係丗俁俆亄乛俈俆					*/
	 ONETOUCH_74_KEY,	/* 俢俆丗俁係乯乛俈係					*/
	 ONETOUCH_80_KEY,	/* 俢俇丗係侽 僐乕僪乛俉侽 僐乕僪		*/
	 ONETOUCH_79_KEY},	/* 俢俈丗俁俋乛俈俋						*/

	/* KEY9_PORT 宿被草 */
	{ONETOUCH_70_KEY,	/* 俢侽丗俁侽乫乛俈侽					*/
	 ONETOUCH_65_KEY,	/* 俢侾丗俀俆倄乛俇俆乷					*/
	 ONETOUCH_69_KEY,	/* 俢俀丗俀俋丗乛俇俋					*/
	 ONETOUCH_68_KEY,	/* 俢俁丗俀俉丏乛俇俉					*/
	 ONETOUCH_67_KEY,	/* 俢係丗俀俈丆乛俇俈丵					*/
	 ONETOUCH_66_KEY,	/* 俢俆丗俀俇倅乛俇俇乸					*/
	 ONETOUCH_72_KEY,	/* 俢俇丗俁俀丂乛俈俀					*/
	 ONETOUCH_71_KEY}	/* 俢俈丗俁侾仌乛俈侾					*/
};

/*******************************************
 * 僉乕僞僀僾僥乕僽儖侾乮僔乕僩侾乯
 *******************************************/
CONST UBYTE KeyTypeTable1[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{NULL,				/* 俢侽丗/LCDBUSY						*/
	 NULL,				/* 俢侾丗枹巊梡							*/
	 NULL,				/* 俢俀丗儚儞僞僢僠愗懼偊				*/
	 NULL,				/* 俢俁丗枹巊梡							*/
	 NULL,				/* 俢係丗枹巊梡							*/
	 NULL,				/* 俢俆丗枹巊梡							*/
	 REVIEW,			/* 俢俇丗捠怣拞巭乛妋擣					*/
	 NULL},				/* 俢俈丗枹巊梡							*/

	/* KEY1_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗侽俇俥乛係俇					*/
	 ONETOUCH,			/* 俢侾丗侽侾俙乛係侾両					*/
	 ONETOUCH,			/* 俢俀丗侽俆俤乛係俆					*/
	 ONETOUCH,			/* 俢俁丗侽係俢乛係係亾					*/
	 ONETOUCH,			/* 俢係丗侽俁俠乛係俁亹					*/
	 ONETOUCH,			/* 俢俆丗侽俀俛乛係俀乭					*/
	 ONETOUCH,			/* 俢俇丗侽俉俫乛係俉					*/
	 ONETOUCH},			/* 俢俈丗侽俈俧乛係俈					*/

	/* KEY2_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗俁								*/
	 NUMBER,			/* 俢侾丗俇								*/
	 NUMBER,			/* 俢俀丗俋								*/
	 SHARP,				/* 俢俁丗仈								*/
	 START,				/* 俢係丗僗僞乕僩						*/
	 CLEAR,				/* 俢俆丗僋儕傾							*/
	 SINGLE,			/* 俢俇丗夋幙							*/
	 TONE},			/* 俢俈丗僩乕儞							*/

	/* KEY3_PORT 宿被草 */
	{BROADCAST,			/* 俢侽丗摨曬							*/
	 SPECIAL,			/* 俢侾丗墳梡捠怣						*/
	 GROUP,				/* 俢俀丗僌儖乕僾						*/
	 SPEED,				/* 俢俁丗抁弅乛揹榖挔					*/
	 SINGLE,			/* 俢係丗嵪僗僞儞僾						*/
	 SINGLE,			/* 俢俆丗儊儌儕憲怣						*/
	 FUNCTION,			/* 俢俇丗婡擻乛亜						*/
	 DIALMARK},			/* 俢俈丗僟僀儎儖婰崋					*/

	/* KEY4_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗侾係俶乛俆係					*/
	 ONETOUCH,			/* 俢侾丗侽俋倝乛係俋丟					*/
	 ONETOUCH,			/* 俢俀丗侾俁俵乛俆俁					*/
	 ONETOUCH,			/* 俢俁丗侾俀俴乛俆俀亜					*/
	 ONETOUCH,			/* 俢係丗侾侾俲乛俆侾亖					*/
	 ONETOUCH,			/* 俢俆丗侾侽俰乛俆侽亙					*/
	 ONETOUCH,			/* 俢俇丗侾俇俹乛俆俇					*/
	 ONETOUCH},			/* 俢俈丗侾俆俷乛俆俆					*/

	/* KEY5_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗俀俀倁乛俇俀					*/
	 ONETOUCH,			/* 俢侾丗侾俈俻乛俆俈丠					*/
	 ONETOUCH,			/* 俢俀丗俀侾倀乛俇侾					*/
	 ONETOUCH,			/* 俢俁丗俀侽俿乛俇侽乵					*/
	 ONETOUCH,			/* 俢係丗侾俋俽乛俆俋乶					*/
	 ONETOUCH,			/* 俢俆丗侾俉俼乛俆俉仐					*/
	 ONETOUCH,			/* 俢俇丗俀係倃乛俇係					*/
	 ONETOUCH},			/* 俢俈丗俀俁倂乛俇俁					*/

	/* KEY6_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗俀								*/
	 NUMBER,			/* 俢侾丗俆								*/
	 NUMBER,			/* 俢俀丗俉								*/
	 NUMBER,			/* 俢俁丗侽								*/
	 REDIAL,			/* 俢係丗儕僟僀儎儖乛億乕僘				*/
	 ENTER,				/* 俢俆丗僙僢僩							*/
	 HOOK,				/* 俢俇丗僼僢僋乛夛榖梊栺				*/
	 SINGLE},			/* 俢俈丗擹搙							*/

	/* KEY7_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗侾								*/
	 NUMBER,			/* 俢侾丗係								*/
	 NUMBER,			/* 俢俀丗俈								*/
	 AST,				/* 俢俁丗仏								*/
	 STOP,				/* 俢係丗僗僩僢僾						*/
	 COPY,				/* 俢俆丗僐僺乕							*/
	 LEFT_ARROW,		/* 俢俇丗亙								*/
	 HOLD},				/* 俢俈丗曐棷							*/

	/* KEY8_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗俁俉 擔杮岅乛俈俉				*/
	 ONETOUCH,			/* 俢侾丗俁俁乮乛俈俁					*/
	 ONETOUCH,			/* 俢俀丗俁俈乛乛俈俈					*/
	 ONETOUCH,			/* 俢俁丗俁俇亅乛俈俇					*/
	 ONETOUCH,			/* 俢係丗俁俆亄乛俈俆					*/
	 ONETOUCH,			/* 俢俆丗俁係乯乛俈係					*/
	 ONETOUCH,			/* 俢俇丗係侽喊霓乛俉侽喊霓				*/
	 ONETOUCH},			/* 俢俈丗俁俋乛俈俋						*/

	/* KEY9_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗俁侽乫乛俈侽					*/
	 ONETOUCH,			/* 俢侾丗俀俆倄乛俇俆乷					*/
	 ONETOUCH,			/* 俢俀丗俀俋丗乛俇俋					*/
	 ONETOUCH,			/* 俢俁丗俀俉丏乛俇俉					*/
	 ONETOUCH,			/* 俢係丗俀俈丆乛俇俈丵					*/
	 ONETOUCH,			/* 俢俆丗俀俇倅乛俇俇乸					*/
	 ONETOUCH,			/* 俢俇丗俁俀丂乛俈俀					*/
	 ONETOUCH}			/* 俢俈丗俁侾仌乛俈侾					*/
};

/*******************************************
 * 僉乕僞僀僾僥乕僽儖俀乮僔乕僩俀乯
 *******************************************/
CONST UBYTE KeyTypeTable2[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{NULL,				/* 俢侽丗/LCDBUSY						*/
	 NULL,				/* 俢侾丗枹巊梡							*/
	 NULL,				/* 俢俀丗儚儞僞僢僠愗懼偊				*/
	 NULL,				/* 俢俁丗枹巊梡							*/
	 NULL,				/* 俢係丗枹巊梡							*/
	 NULL,				/* 俢俆丗枹巊梡							*/
	 REVIEW,			/* 俢俇丗捠怣拞巭乛妋擣					*/
	 NULL},				/* 俢俈丗枹巊梡							*/

	/* KEY1_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗侽俇俥乛係俇					*/
	 ONETOUCH,			/* 俢侾丗侽侾俙乛係侾両					*/
	 ONETOUCH,			/* 俢俀丗侽俆俤乛係俆					*/
	 ONETOUCH,			/* 俢俁丗侽係俢乛係係亾					*/
	 ONETOUCH,			/* 俢係丗侽俁俠乛係俁亹					*/
	 ONETOUCH,			/* 俢俆丗侽俀俛乛係俀乭					*/
	 ONETOUCH,			/* 俢俇丗侽俉俫乛係俉					*/
	 ONETOUCH},			/* 俢俈丗侽俈俧乛係俈					*/

	/* KEY2_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗俁								*/
	 NUMBER,			/* 俢侾丗俇								*/
	 NUMBER,			/* 俢俀丗俋								*/
	 SHARP,				/* 俢俁丗仈								*/
	 START,				/* 俢係丗僗僞乕僩						*/
	 CLEAR,				/* 俢俆丗僋儕傾							*/
	 SINGLE,			/* 俢俇丗夋幙							*/
	 TONE},			/* 俢俈丗僩乕儞							*/

	/* KEY3_PORT 宿被草 */
	{BROADCAST,			/* 俢侽丗摨曬							*/
	 SPECIAL,			/* 俢侾丗墳梡捠怣						*/
	 GROUP,				/* 俢俀丗僌儖乕僾						*/
	 SPEED,				/* 俢俁丗抁弅乛揹榖挔					*/
	 SINGLE,			/* 俢係丗嵪僗僞儞僾						*/
	 SINGLE,			/* 俢俆丗儊儌儕憲怣						*/
	 FUNCTION,			/* 俢俇丗婡擻乛亜						*/
	 DIALMARK},			/* 俢俈丗僟僀儎儖婰崋					*/

	/* KEY4_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗侾係俶乛俆係					*/
	 ONETOUCH,			/* 俢侾丗侽俋倝乛係俋丟					*/
	 ONETOUCH,			/* 俢俀丗侾俁俵乛俆俁					*/
	 ONETOUCH,			/* 俢俁丗侾俀俴乛俆俀亜					*/
	 ONETOUCH,			/* 俢係丗侾侾俲乛俆侾亖					*/
	 ONETOUCH,			/* 俢俆丗侾侽俰乛俆侽亙					*/
	 ONETOUCH,			/* 俢俇丗侾俇俹乛俆俇					*/
	 ONETOUCH},			/* 俢俈丗侾俆俷乛俆俆					*/

	/* KEY5_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗俀俀倁乛俇俀					*/
	 ONETOUCH,			/* 俢侾丗侾俈俻乛俆俈丠					*/
	 ONETOUCH,			/* 俢俀丗俀侾倀乛俇侾					*/
	 ONETOUCH,			/* 俢俁丗俀侽俿乛俇侽乵					*/
	 ONETOUCH,			/* 俢係丗侾俋俽乛俆俋乶					*/
	 ONETOUCH,			/* 俢俆丗侾俉俼乛俆俉仐					*/
	 ONETOUCH,			/* 俢俇丗俀係倃乛俇係					*/
	 ONETOUCH},			/* 俢俈丗俀俁倂乛俇俁					*/

	/* KEY6_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗俀								*/
	 NUMBER,			/* 俢侾丗俆								*/
	 NUMBER,			/* 俢俀丗俉								*/
	 NUMBER,			/* 俢俁丗侽								*/
	 REDIAL,			/* 俢係丗儕僟僀儎儖乛億乕僘				*/
	 ENTER,				/* 俢俆丗僙僢僩							*/
	 HOOK,				/* 俢俇丗僼僢僋乛夛榖梊栺				*/
	 SINGLE},			/* 俢俈丗擹搙							*/

	/* KEY7_PORT 宿被草 */
	{NUMBER,			/* 俢侽丗侾								*/
	 NUMBER,			/* 俢侾丗係								*/
	 NUMBER,			/* 俢俀丗俈								*/
	 AST,				/* 俢俁丗仏								*/
	 STOP,				/* 俢係丗僗僩僢僾						*/
	 COPY,				/* 俢俆丗僐僺乕							*/
	 LEFT_ARROW,		/* 俢俇丗亙								*/
	 HOLD},				/* 俢俈丗曐棷							*/

	/* KEY8_PORT 宿被草 */
	{PROGRAM,			/* 俢侽丗俁俉 擔杮岅乛俈俉				*/
	 PROGRAM,			/* 俢侾丗俁俁乮乛俈俁					*/
	 PROGRAM,			/* 俢俀丗俁俈乛乛俈俈					*/
	 PROGRAM,			/* 俢俁丗俁俇亅乛俈俇					*/
	 PROGRAM,			/* 俢係丗俁俆亄乛俈俆					*/
	 PROGRAM,			/* 俢俆丗俁係乯乛俈係					*/
	 PROGRAM,			/* 俢俇丗係侽喊霓乛俉侽喊霓				*/
	 PROGRAM},			/* 俢俈丗俁俋乛俈俋						*/

	/* KEY9_PORT 宿被草 */
	{ONETOUCH,			/* 俢侽丗俁侽乫乛俈侽					*/
	 ONETOUCH,			/* 俢侾丗俀俆倄乛俇俆乷					*/
	 ONETOUCH,			/* 俢俀丗俀俋丗乛俇俋					*/
	 ONETOUCH,			/* 俢俁丗俀俉丏乛俇俉					*/
	 ONETOUCH,			/* 俢係丗俀俈丆乛俇俈丵					*/
	 ONETOUCH,			/* 俢俆丗俀俇倅乛俇俇乸					*/
	 ONETOUCH,			/* 俢俇丗俁俀丂乛俈俀					*/
	 ONETOUCH}			/* 俢俈丗俁侾仌乛俈侾					*/
};
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_L) */

#if (PRO_KEYPANEL == PANEL_ANZU_L)
 #if defined(GBR) /* 1997/08/13 Y,Matsukuma */
/*******************************************
 * 僉乕僥乕僽儖侾乮僔乕僩侾乯
 ******************************************/
CONST UBYTE KeyTableSheet1[][KEY_MATRICS_COLUM_MAX] = {

/* KEY0_PORT 價僢僩傾僒僀儞*/
	{PROGRAM_P05 , PROGRAM_P04 , PROGRAM_P03 ,PROGRAM_P02 ,PROGRAM_P01 , STOP_KEY , START_KEY ,COPY_KEY},

/* KEY1_PORT 價僢僩傾僒僀儞*/
    {TEN_1_KEY,    BROADCAST_KEY,   TEN_4_KEY,       SPECIAL_KEY	   , CLEAR_KEY	    , SET_KEY        , FUNCTION_KEY,CURSOR_LEFT_KEY},

/* KEY2_PORT 價僢僩傾僒僀儞*/
	{TEN_7_KEY,       GROUP_KEY,       TEN_AST_KEY,     SPEED_KEY,       AUTO_RX_KEY,    HOOK_KEY,       REDIAL_KEY,   HOLD_KEY},

/* KEY3_PORT 宿被草 */
	{FLASH_KEY , MEMORY_TX_KEY , STAMP_KEY , DIAL_MARK_KEY ,REVIEW_KEY        , CONTRAST_KEY , MODE_KEY , MERCURY_KEY},

/* KEY4_PORT 宿被草 */
	{ONETOUCH_F_KEY , ONETOUCH_E_KEY , ONETOUCH_D_KEY , ONETOUCH_C_KEY , ONETOUCH_B_KEY , ONETOUCH_A_KEY , TEN_3_KEY , TEN_2_KEY },

/* KEY5_PORT 宿被草 */
	{ONETOUCH_L_KEY , ONETOUCH_K_KEY , ONETOUCH_J_KEY , ONETOUCH_I_KEY , ONETOUCH_H_KEY , ONETOUCH_G_KEY , NULL , NULL},
	
/* KEY6_PORT 宿被草 */
	{ONETOUCH_R_KEY , ONETOUCH_Q_KEY , ONETOUCH_P_KEY , ONETOUCH_O_KEY , ONETOUCH_N_KEY , ONETOUCH_M_KEY , NULL , NULL},
	
/* KEY7_PORT 宿被草 */
	{ONETOUCH_X_KEY , ONETOUCH_W_KEY , ONETOUCH_V_KEY , ONETOUCH_U_KEY , ONETOUCH_T_KEY , ONETOUCH_S_KEY , NULL , NULL},

/* KEY8_PORT 宿被草 */
	{ONETOUCH_U4_KEY , ONETOUCH_U3_KEY , ONETOUCH_U2_KEY , ONETOUCH_U1_KEY , ONETOUCH_Z_KEY , ONETOUCH_Y_KEY , NULL , NULL},

/* KEY9_PORT 宿被草 */
	{TEN_SHARP_KEY,   TEN_9_KEY,       TEN_6_KEY,       TEN_0_KEY,       TEN_8_KEY,      TEN_5_KEY,      NULL,         NULL},
};

/*******************************************
 * 僉乕僥乕僽儖俀乮僔乕僩俀乯
 ******************************************/
CONST UBYTE KeyTableSheet2[][KEY_MATRICS_COLUM_MAX] = {

/* KEY0_PORT 價僢僩傾僒僀儞*/
/*	{PROGRAM_P11 , PROGRAM_P10 , PROGRAM_P09 ,PROGRAM_P08 ,PROGRAM_P07 , STOP_KEY , START_KEY ,COPY_KEY},*/
	{PROGRAM_P10 , PROGRAM_P09 , PROGRAM_P08 ,PROGRAM_P07 ,PROGRAM_P06 , STOP_KEY , START_KEY ,COPY_KEY},/* 1996/10/11 Eguchi */

/* KEY1_PORT 價僢僩傾僒僀儞*/
    {TEN_1_KEY,    BROADCAST_KEY,   TEN_4_KEY,       SPECIAL_KEY	   , CLEAR_KEY	    , SET_KEY        , FUNCTION_KEY,CURSOR_LEFT_KEY},

/* KEY2_PORT 價僢僩傾僒僀儞*/
	{TEN_7_KEY,       GROUP_KEY,       TEN_AST_KEY,     SPEED_KEY,       AUTO_RX_KEY,    HOOK_KEY,       REDIAL_KEY,   HOLD_KEY},

/* KEY3_PORT 宿被草 */
	{FLASH_KEY , MEMORY_TX_KEY , STAMP_KEY , DIAL_MARK_KEY ,REVIEW_KEY , CONTRAST_KEY , MODE_KEY , MERCURY_KEY },

/* KEY4_PORT 宿被草 */
	{ONETOUCH_f_KEY , ONETOUCH_e_KEY , ONETOUCH_d_KEY , ONETOUCH_c_KEY , ONETOUCH_b_KEY , ONETOUCH_a_KEY , TEN_3_KEY , TEN_2_KEY },

/* KEY5_PORT 宿被草 */
	{ONETOUCH_l_KEY , ONETOUCH_k_KEY , ONETOUCH_j_KEY , ONETOUCH_i_KEY , ONETOUCH_h_KEY , ONETOUCH_g_KEY , NULL , NULL},
	
/* KEY6_PORT 宿被草 */
	{ONETOUCH_r_KEY , ONETOUCH_q_KEY , ONETOUCH_p_KEY , ONETOUCH_o_KEY , ONETOUCH_n_KEY , ONETOUCH_m_KEY , NULL , NULL},
	
/* KEY7_PORT 宿被草 */
	{ONETOUCH_x_KEY , ONETOUCH_w_KEY , ONETOUCH_v_KEY , ONETOUCH_u_KEY , ONETOUCH_t_KEY , ONETOUCH_s_KEY , NULL , NULL},

/* KEY8_PORT 宿被草 */
	{ONETOUCH_U8_KEY , ONETOUCH_U7_KEY , ONETOUCH_U6_KEY , ONETOUCH_U5_KEY , ONETOUCH_z_KEY , ONETOUCH_y_KEY , NULL , NULL},

/* KEY9_PORT 宿被草 */
	{TEN_SHARP_KEY,   TEN_9_KEY,       TEN_6_KEY,       TEN_0_KEY,       TEN_8_KEY,      TEN_5_KEY,      NULL,         NULL},
};

/*******************************************
 * 僉乕僞僀僾僥乕僽儖 侾乮僔乕僩侾乯
 *******************************************/
CONST UBYTE KeyTypeTable1[][KEY_MATRICS_COLUM_MAX] ={

/* KEY0_PORT 價僢僩傾僒僀儞*/
	{PROGRAM, PROGRAM, PROGRAM , PROGRAM , PROGRAM , STOP , START ,COPY},

/* KEY1_PORT 價僢僩傾僒僀儞*/
    {NUMBER,   BROADCAST,NUMBER,   SPECIAL, CLEAR,    ENTER,    FUNCTION,  LEFT_ARROW},

/* KEY2_PORT丂價僢僩傾僒僀儞 */
    {NUMBER,   GROUP,    AST,      SPEED, SINGLE,   HOOK,     REDIAL,   HOLD },

/* KEY3_PORT丂價僢僩傾僒僀儞 */
	{FLASH , SINGLE , SINGLE ,DIALMARK , REVIEW , SINGLE, SINGLE , MERCURY},

/* KEY4_PORT 宿被草 */
	{ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , NUMBER , NUMBER},

/* KEY5_PORT 宿被草 */
	{ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , NULL , NULL},
	
/* KEY6_PORT 宿被草 */
	{ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , NULL , NULL},
	
/* KEY7_PORT 宿被草 */
	{ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , NULL , NULL},

/* KEY8_PORT 宿被草 */
	{ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , ONETOUCH , NULL , NULL},

/* KEY9_PORT 宿被草 */
	{SHARP , NUMBER ,NUMBER ,NUMBER ,NUMBER ,NUMBER ,NULL , NULL },
};

/*******************************************
 * 僉乕僞僀僾僥乕僽儖俀乮僔乕僩俀乯
 *******************************************/
CONST UBYTE KeyTypeTable2[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{PROGRAM,  PROGRAM,   PROGRAM,  PROGRAM,  PROGRAM,  STOP,     START,    COPY},

	/* KEY1_PORT 宿被草 */
	{NUMBER,   BROADCAST, NUMBER,   SPECIAL,  CLEAR,    ENTER,    FUNCTION, LEFT_ARROW},

	/* KEY2_PORT 宿被草 */
	{NUMBER,   GROUP,     AST,      SPEED,    SINGLE,   HOOK,     REDIAL,   HOLD},

	/* KEY3_PORT 宿被草 */
	{FLASH,    SINGLE,    SINGLE,   DIALMARK, REVIEW,   SINGLE,   SINGLE,   MERCURY},	/* PROGRAM->MERCURY 1998/02/19 Y.Matsukuma */

	/* KEY4_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NUMBER,   NUMBER},

	/* KEY5_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY6_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY7_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY8_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY9_PORT 宿被草 */
	{SHARP,    NUMBER,    NUMBER,   NUMBER,   NUMBER,   NUMBER,   NULL,     NULL},
};

 #else

/*******************************************
 * 僉乕僥乕僽儖侾乮僔乕僩侾乯
 ******************************************/
CONST UBYTE KeyTableSheet1[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{PROGRAM_P05,     PROGRAM_P04,     PROGRAM_P03,     PROGRAM_P02,     PROGRAM_P01,    STOP_KEY,       START_KEY,    COPY_KEY},

	/* KEY1_PORT 宿被草 */
	{TEN_1_KEY,       BROADCAST_KEY,   TEN_4_KEY,       SPECIAL_KEY,     CLEAR_KEY,      SET_KEY,        FUNCTION_KEY, CURSOR_LEFT_KEY},

	/* KEY2_PORT 宿被草 */
	{TEN_7_KEY,       GROUP_KEY,       TEN_AST_KEY,     SPEED_KEY,       AUTO_RX_KEY,    HOOK_KEY,       REDIAL_KEY,   HOLD_KEY},

	/* KEY3_PORT 宿被草 */
	{FLASH_KEY,       MEMORY_TX_KEY,   STAMP_KEY,       DIAL_MARK_KEY,   REVIEW_KEY,     CONTRAST_KEY,   MODE_KEY,     PROGRAM_P06},

	/* KEY4_PORT 宿被草 */
	{ONETOUCH_F_KEY,  ONETOUCH_E_KEY,  ONETOUCH_D_KEY,  ONETOUCH_C_KEY,  ONETOUCH_B_KEY, ONETOUCH_A_KEY, TEN_3_KEY,    TEN_2_KEY},

	/* KEY5_PORT 宿被草 */
	{ONETOUCH_L_KEY,  ONETOUCH_K_KEY,  ONETOUCH_J_KEY,  ONETOUCH_I_KEY,  ONETOUCH_H_KEY, ONETOUCH_G_KEY, NULL,         NULL},

	/* KEY6_PORT 宿被草 */
	{ONETOUCH_R_KEY,  ONETOUCH_Q_KEY,  ONETOUCH_P_KEY,  ONETOUCH_O_KEY,  ONETOUCH_N_KEY, ONETOUCH_M_KEY, NULL,         NULL},

	/* KEY7_PORT 宿被草 */
	{ONETOUCH_X_KEY,  ONETOUCH_W_KEY,  ONETOUCH_V_KEY,  ONETOUCH_U_KEY,  ONETOUCH_T_KEY, ONETOUCH_S_KEY, NULL,         NULL},

	/* KEY8_PORT 宿被草 */
	{ONETOUCH_U4_KEY, ONETOUCH_U3_KEY, ONETOUCH_U2_KEY, ONETOUCH_U1_KEY, ONETOUCH_Z_KEY, ONETOUCH_Y_KEY, NULL,         NULL},

	/* KEY9_PORT 宿被草 */
	{TEN_SHARP_KEY,   TEN_9_KEY,       TEN_6_KEY,       TEN_0_KEY,       TEN_8_KEY,      TEN_5_KEY,      NULL,         NULL},
};

/*******************************************
 * 僉乕僥乕僽儖俀乮僔乕僩俀乯
 ******************************************/
CONST UBYTE KeyTableSheet2[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{PROGRAM_P11,     PROGRAM_P10,     PROGRAM_P09,     PROGRAM_P08,     PROGRAM_P07,    STOP_KEY,       START_KEY,    COPY_KEY},

	/* KEY1_PORT 宿被草 */
	{TEN_1_KEY,       BROADCAST_KEY,   TEN_4_KEY,       SPECIAL_KEY,     CLEAR_KEY,      SET_KEY,        FUNCTION_KEY, CURSOR_LEFT_KEY},

	/* KEY2_PORT 宿被草 */
	{TEN_7_KEY,       GROUP_KEY,       TEN_AST_KEY,     SPEED_KEY,       AUTO_RX_KEY,    HOOK_KEY,       REDIAL_KEY,   HOLD_KEY},

	/* KEY3_PORT 宿被草 */
	{FLASH_KEY,       MEMORY_TX_KEY,   STAMP_KEY,       DIAL_MARK_KEY,   REVIEW_KEY,     CONTRAST_KEY,   MODE_KEY,     PROGRAM_P12},

	/* KEY4_PORT 宿被草 */
	{ONETOUCH_f_KEY,  ONETOUCH_e_KEY,  ONETOUCH_d_KEY,  ONETOUCH_c_KEY,  ONETOUCH_b_KEY, ONETOUCH_a_KEY, TEN_3_KEY,    TEN_2_KEY},

	/* KEY5_PORT 宿被草 */
	{ONETOUCH_l_KEY,  ONETOUCH_k_KEY,  ONETOUCH_j_KEY,  ONETOUCH_i_KEY,  ONETOUCH_h_KEY, ONETOUCH_g_KEY, NULL,         NULL},

	/* KEY6_PORT 宿被草 */
	{ONETOUCH_r_KEY,  ONETOUCH_q_KEY,  ONETOUCH_p_KEY,  ONETOUCH_o_KEY,  ONETOUCH_n_KEY, ONETOUCH_m_KEY, NULL,         NULL},

	/* KEY7_PORT 宿被草 */
	{ONETOUCH_x_KEY,  ONETOUCH_w_KEY,  ONETOUCH_v_KEY,  ONETOUCH_u_KEY,  ONETOUCH_t_KEY, ONETOUCH_s_KEY, NULL,         NULL},

	/* KEY8_PORT 宿被草 */
	{ONETOUCH_U8_KEY, ONETOUCH_U7_KEY, ONETOUCH_U6_KEY, ONETOUCH_U5_KEY, ONETOUCH_z_KEY, ONETOUCH_y_KEY, NULL,         NULL},

	/* KEY9_PORT 宿被草 */
	{TEN_SHARP_KEY,   TEN_9_KEY,       TEN_6_KEY,       TEN_0_KEY,       TEN_8_KEY,      TEN_5_KEY,      NULL,         NULL},
};

/*******************************************
 * 僉乕僞僀僾僥乕僽儖侾乮僔乕僩侾乯
 *******************************************/
CONST UBYTE KeyTypeTable1[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{PROGRAM,  PROGRAM,   PROGRAM,  PROGRAM,  PROGRAM,  STOP,     START,    COPY},

	/* KEY1_PORT 宿被草 */
	{NUMBER,   BROADCAST, NUMBER,   SPECIAL,  CLEAR,    ENTER,    FUNCTION, LEFT_ARROW},

	/* KEY2_PORT 宿被草 */
	{NUMBER,   GROUP,     AST,      SPEED,    SINGLE,   HOOK,     REDIAL,   HOLD},

	/* KEY3_PORT 宿被草 */
	{FLASH,    SINGLE,    SINGLE,   DIALMARK, REVIEW,   SINGLE,   SINGLE,   PROGRAM},

	/* KEY4_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NUMBER,   NUMBER},

	/* KEY5_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY6_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY7_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY8_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY9_PORT 宿被草 */
	{SHARP,    NUMBER,    NUMBER,   NUMBER,   NUMBER,   NUMBER,   NULL,     NULL},
};

/*******************************************
 * 僉乕僞僀僾僥乕僽儖俀乮僔乕僩俀乯
 *******************************************/
CONST UBYTE KeyTypeTable2[][KEY_MATRICS_COLUM_MAX] = {

	/* KEY0_PORT 宿被草 */
	{PROGRAM,  PROGRAM,   PROGRAM,  PROGRAM,  PROGRAM,  STOP,     START,    COPY},

	/* KEY1_PORT 宿被草 */
	{NUMBER,   BROADCAST, NUMBER,   SPECIAL,  CLEAR,    ENTER,    FUNCTION, LEFT_ARROW},

	/* KEY2_PORT 宿被草 */
	{NUMBER,   GROUP,     AST,      SPEED,    SINGLE,   HOOK,     REDIAL,   HOLD},

	/* KEY3_PORT 宿被草 */
	{FLASH,    SINGLE,    SINGLE,   DIALMARK, REVIEW,   SINGLE,   SINGLE,   PROGRAM},

	/* KEY4_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NUMBER,   NUMBER},

	/* KEY5_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY6_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY7_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY8_PORT 宿被草 */
	{ONETOUCH, ONETOUCH,  ONETOUCH, ONETOUCH, ONETOUCH, ONETOUCH, NULL,     NULL},

	/* KEY9_PORT 宿被草 */
	{SHARP,    NUMBER,    NUMBER,   NUMBER,   NUMBER,   NUMBER,   NULL,     NULL},
};
 #endif	 /* defined(GBR)	*/
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */

#if (PRO_KEYPANEL == PANEL_HINOKI)	/* Add By H.Fujimura 1998/12/28 */
/*******************************************
 * 僉乕僥乕僽儖侾
 ******************************************/
CONST UBYTE KeyTableSheet1[][KEY_MATRICS_COLUM_MAX] = {
/* 俲俤倄 俼俷倂侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 BROADCAST_KEY,		/* 摨曬僉乕					*/
	 SPECIAL_KEY,		/* 墳梡捠怣僉乕				*/
	 GROUP_KEY,			/* 僌儖乕僾僉乕				*/
	 SPEED_KEY,			/* 抁弅乛揹榖挔僉乕			*/
	 MEMORY_TX_KEY,		/* 儊儌儕憲怣僉乕			*/
#if defined (KEISATSU)		/* 寈嶡FAX Modify by SMuratec K.W.Q 2005/07/21 */
	 RESERVATION,
#else
	 STAMP_KEY,			/* 嵪傒僗僞儞僾僉乕			*/
#endif		/* End of (defined (KEISATSU)) */
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂侾價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_06_KEY,	/* 儚儞僞僢僠侽俇僉乕		*/
	 ONETOUCH_12_KEY,	/* 儚儞僞僢僠侾俀僉乕		*/
	 ONETOUCH_18_KEY,	/* 儚儞僞僢僠侾俉僉乕		*/
	 ONETOUCH_24_KEY,	/* 儚儞僞僢僠俀係僉乕		*/
 #if (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/10/26 */
	 MERCURY_KEY,		/* 僾儗僼傿僢僋僗僉乕		*/
 #else
	 ONETOUCH_30_KEY,	/* 儚儞僞僢僠俁侽僉乕		*/
 #endif
	 NULL,				/* NULL */
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俀價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_05_KEY,	/* 儚儞僞僢僠侽俆僉乕		*/
	 ONETOUCH_11_KEY,	/* 儚儞僞僢僠侾侾僉乕		*/
	 ONETOUCH_17_KEY,	/* 儚儞僞僢僠侾俈僉乕		*/
	 ONETOUCH_23_KEY,	/* 儚儞僞僢僠俀俁僉乕		*/
	 ONETOUCH_29_KEY,	/* 儚儞僞僢僠俀俋僉乕		*/
	 NULL,				/* NULL */
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俁價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_04_KEY,	/* 儚儞僞僢僠侽係僉乕		*/
	 ONETOUCH_10_KEY,	/* 儚儞僞僢僠侾侽僉乕		*/
	 ONETOUCH_16_KEY,	/* 儚儞僞僢僠侾俇僉乕		*/
	 ONETOUCH_22_KEY,	/* 儚儞僞僢僠俀俀僉乕		*/
	 ONETOUCH_28_KEY,	/* 儚儞僞僢僠俀俉僉乕		*/
	 NULL,				/* NULL */
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂係價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_03_KEY,	/* 儚儞僞僢僠侽俁僉乕		*/
	 ONETOUCH_09_KEY,	/* 儚儞僞僢僠侽俋僉乕		*/
	 ONETOUCH_15_KEY,	/* 儚儞僞僢僠侾俆僉乕		*/
	 ONETOUCH_21_KEY,	/* 儚儞僞僢僠俀侾僉乕		*/
	 ONETOUCH_27_KEY,	/* 儚儞僞僢僠俀俈僉乕		*/

#if (0)
** 	/* 僷僱儖僨僓僀儞曄峏偺堊 By O.Kimoto 1998/10/23 */
** 	 REVIEW_KEY,		/* 捠怣拞巭乛妋擣僉乕		*/
#else
	 HOLD_KEY,			/* 曐棷僉乕					*/
#endif

	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俆價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_02_KEY,	/* 儚儞僞僢僠侽俀僉乕		*/
	 ONETOUCH_08_KEY,	/* 儚儞僞僢僠侽俉僉乕		*/
	 ONETOUCH_14_KEY,	/* 儚儞僞僢僠侾係僉乕		*/
	 ONETOUCH_20_KEY,	/* 儚儞僞僢僠俀侽僉乕		*/
	 ONETOUCH_26_KEY,	/* 儚儞僞僢僠俀俇僉乕		*/
	 DIAL_MARK_KEY,		/* 僟僀儎儖婰崋僉乕			*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俇價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_01_KEY,	/* 儚儞僞僢僠侽侾僉乕		*/
	 ONETOUCH_07_KEY,	/* 儚儞僞僢僠侽俈僉乕		*/
	 ONETOUCH_13_KEY,	/* 儚儞僞僢僠侾俁僉乕		*/
	 ONETOUCH_19_KEY,	/* 儚儞僞僢僠侾俋僉乕		*/
	 ONETOUCH_25_KEY,	/* 儚儞僞僢僠俀俆僉乕		*/
	 CLEAR_KEY,			/* 僋儕傾僉乕				*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俈價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 TEN_3_KEY,			/* 僥儞僉乕俁僉乕			*/
	 TEN_6_KEY,			/* 僥儞僉乕俇僉乕			*/
	 TEN_9_KEY,			/* 僥儞僉乕俋僉乕			*/
	 TEN_SHARP_KEY,		/* 僥儞僉乕仈僉乕			*/
	 START_KEY,			/* 僗僞乕僩僉乕				*/
	 CONTRAST_KEY,		/* 擹搙僉乕					*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俉價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 TEN_2_KEY,			/* 僥儞僉乕俀僉乕			*/
	 TEN_5_KEY,			/* 僥儞僉乕俆僉乕			*/
	 TEN_8_KEY,			/* 僥儞僉乕俉僉乕			*/
	 TEN_0_KEY,			/* 僥儞僉乕侽僉乕			*/
	 COPY_KEY,			/* 僐僺乕僉乕				*/
	 SET_KEY,			/* 僙僢僩僉乕				*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俋價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 TEN_1_KEY,			/* 僥儞僉乕侾僉乕			*/
	 TEN_4_KEY,			/* 僥儞僉乕係僉乕			*/
	 TEN_7_KEY,			/* 僥儞僉乕俈僉乕			*/
	 TEN_AST_KEY,		/* 僥儞僉乕仏僉乕			*/
	 STOP_KEY,			/* 僗僩僢僾僉乕				*/
	 FUNCTION_KEY,		/* 婡擻乛塃栴報僉乕			*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂侾侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 AUTO_RX_KEY,		/* 帺摦庴怣僉乕				*/
	 HOOK_KEY,			/* 僼僢僋乛夛榖梊栺僉乕		*/
	 REDIAL_KEY,		/* 儕僟僀儎儖乛億乕僘僉乕	*/

#if (0)
** 	/* 僷僱儖僨僓僀儞曄峏偺堊 By O.Kimoto 1998/10/23 */
** 	 HOLD_KEY,			/* 曐棷僉乕					*/
#else
	 REVIEW_KEY,		/* 捠怣拞巭乛妋擣僉乕		*/
#endif

	 CURSOR_LEFT_KEY,	/* 嵍栴報僉乕				*/
	 MODE_KEY,			/* 夋幙僉乕					*/
	 NULL},				/* NULL */
};

/*******************************************
 * 僉乕僞僀僾侾
 ******************************************/
CONST UBYTE KeyTypeTable1[][KEY_MATRICS_COLUM_MAX] = {
/* 俲俤倄 俼俷倂侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 BROADCAST,			/* 摨曬僉乕					*/
	 SPECIAL,			/* 墳梡捠怣僉乕				*/
	 GROUP,				/* 僌儖乕僾僉乕				*/
	 SPEED,				/* 抁弅乛揹榖挔僉乕			*/
	 SINGLE,			/* 儊儌儕憲怣僉乕			*/
	 SINGLE,			/* 嵪傒僗僞儞僾僉乕			*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂侾價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠侽俇僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俀僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俉僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俀係僉乕		*/
 #if (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/10/12 */
	 MERCURY,			/* 僾儗僼傿僢僋僗僉乕		*/
 #else
	 PROGRAM,			/* 儚儞僞僢僠俁侽僉乕		*/
 #endif
	 NULL,				/* NULL */
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俀價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠侽俆僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾侾僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俈僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俀俁僉乕		*/
	 PROGRAM,			/* 儚儞僞僢僠俀俋僉乕		*/
	 NULL,				/* NULL */
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俁價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠侽係僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾侽僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俇僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俀俀僉乕		*/
	 PROGRAM,			/* 儚儞僞僢僠俀俉僉乕		*/
	 NULL,				/* NULL */
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂係價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠侽俁僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侽俋僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俆僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俀侾僉乕		*/
	 PROGRAM,			/* 儚儞僞僢僠俀俈僉乕		*/

#if (0)
** 	/* 僷僱儖僨僓僀儞曄峏偺堊 By O.Kimoto 1998/10/23 */
** 	 REVIEW,			/* 捠怣拞巭乛妋擣僉乕		*/
#else
	 HOLD,				/* 曐棷僉乕					*/
#endif

	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俆價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠侽俀僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侽俉僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾係僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俀侽僉乕		*/
	 PROGRAM,			/* 儚儞僞僢僠俀俇僉乕		*/
	 DIALMARK,			/* 僟僀儎儖婰崋僉乕			*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俇價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠侽侾僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侽俈僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俁僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俋僉乕		*/
	 PROGRAM,			/* 儚儞僞僢僠俀俆僉乕		*/
	 CLEAR,				/* 僋儕傾僉乕				*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俈價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NUMBER,			/* 僥儞僉乕俁僉乕			*/
	 NUMBER,			/* 僥儞僉乕俇僉乕			*/
	 NUMBER,			/* 僥儞僉乕俋僉乕			*/
	 SHARP,				/* 僥儞僉乕仈僉乕			*/
	 START,				/* 僗僞乕僩僉乕				*/
	 SINGLE,			/* 擹搙僉乕					*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俉價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NUMBER,			/* 僥儞僉乕俀僉乕			*/
	 NUMBER,			/* 僥儞僉乕俆僉乕			*/
	 NUMBER,			/* 僥儞僉乕俉僉乕			*/
	 NUMBER,			/* 僥儞僉乕侽僉乕			*/
	 COPY,				/* 僐僺乕僉乕				*/
	 ENTER,				/* 僙僢僩僉乕				*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俋價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NUMBER,			/* 僥儞僉乕侾僉乕			*/
	 NUMBER,			/* 僥儞僉乕係僉乕			*/
	 NUMBER,			/* 僥儞僉乕俈僉乕			*/
	 AST,				/* 僥儞僉乕仏僉乕			*/
	 STOP,				/* 僗僩僢僾僉乕				*/
	 FUNCTION,			/* 婡擻乛塃栴報僉乕			*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂侾侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 SINGLE,			/* 帺摦庴怣僉乕				*/
	 HOOK,				/* 僼僢僋乛夛榖梊栺僉乕		*/
	 REDIAL,			/* 儕僟僀儎儖乛億乕僘僉乕	*/

#if (0)
** 	/* 僷僱儖僨僓僀儞曄峏偺堊 By O.Kimoto 1998/10/23 */
** 	 HOLD,				/* 曐棷僉乕					*/
#else
	 REVIEW,			/* 捠怣拞巭乛妋擣僉乕		*/
#endif

	 LEFT_ARROW,		/* 嵍栴報僉乕				*/
	 SINGLE,			/* 夋幙僉乕					*/
	 NULL},				/* NULL */
};
#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) */


#if (PRO_KEYPANEL == PANEL_SATSUKI2)	/* Add By Y.Kano 2003/07/10 */
/*******************************************
 * 僉乕僥乕僽儖侾乮俽俙俿俽倀俲俬俀乯
 ******************************************/
CONST UBYTE KeyTableSheet1[][KEY_MATRICS_COLUM_MAX] = {
/* 俲俤倄 俼俷倂侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂侾價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_01_KEY,	/* 儚儞僞僢僠俙僉乕		*/
	 ONETOUCH_11_KEY,	/* 儚儞僞僢僠俲僉乕		*/
	 ONETOUCH_05_KEY,	/* 儚儞僞僢僠俤僉乕		*/
	 TEN_2_KEY,			/* 僥儞僉乕俀僉乕		*/
	 FUNCTION_KEY,		/* 婡擻乛亜 			*/
	 CURSOR_LEFT_KEY,	/* 亙僉乕			    */ /* Modify by SMuratec L.Z.W 2003/10/10 */
	 SPEED_KEY},		/* 抁弅丄揹榖挔			*/ /* Modify by SMuratec L.Z.W 2003/07/25 */

/* 俲俤倄 俼俷倂俀價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_02_KEY,	/* 儚儞僞僢僠俛僉乕		*/
	 ONETOUCH_12_KEY,	/* 儚儞僞僢僠俴僉乕		*/
	 ONETOUCH_10_KEY,	/* 儚儞僞僢僠俰僉乕		*/
	 TEN_5_KEY,			/* 僥儞僉乕俆僉乕		*/
	 CHARACTER_KEY,		/* 暥帤僉乕			    */ /* Modify by SMuratec L.Z.W 2003/10/10 */
	 DIAL_MARK_KEY,		/* 僟僀儎儖婰崋僉乕		*/ /* Modify by SMuratec L.Z.W 2003/10/10 */
	 REDIAL_KEY},		/* 儕僟僀儎儖乛億乕僘	*/ /* Modify by SMuratec L.Z.W 2003/07/28 */

/* 俲俤倄 俼俷倂俁價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_03_KEY,	/* 儚儞僞僢僠俠僉乕		*/
	 ONETOUCH_13_KEY,	/* 儚儞僞僢僠俵僉乕		*/
	 ONETOUCH_15_KEY,	/* 儚儞僞僢僠俷僉乕		*/
	 TEN_8_KEY,			/* 僥儞僉乕俉僉乕		*/
	 SET_KEY,			/* 擹搙丄僙僢僩			*/
	 COMM_REPORT_KEY,	/* 捠怣徹				*/ /* Modify by SMuratec L.Z.W 2003/08/01 */
	 HOLD_KEY},			/* 曐棷僉乕				*/ /* Modify by SMuratec L.Z.W 2003/08/01 */

/* 俲俤倄 俼俷倂係價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_04_KEY,	/* 儚儞僞僢僠俢僉乕		*/
	 ONETOUCH_14_KEY,	/* 儚儞僞僢僠俶僉乕		*/
	 ONETOUCH_20_KEY,	/* 儚儞僞僢僠俿僉乕		*/
	 TEN_0_KEY,			/* 僥儞僉乕侽僉乕		*/
	 CLEAR_KEY,			/* 夋幙丄僋儕傾			*/
	 VOLUME_KEY,		/* 壒検挷惍僉乕			*/ /* Add by Y.Kano 2003/08/27 */
	 HOOK_KEY},			/* 僼僢僋丄夛榖梊栺		*/

/* 俲俤倄 俼俷倂俆價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_06_KEY,	/* 儚儞僞僢僠俥僉乕		*/
	 ONETOUCH_16_KEY,	/* 儚儞僞僢僠俹僉乕		*/
	 TEN_3_KEY,			/* 僥儞僉乕俁僉乕		*/
	 TEN_1_KEY,			/* 僥儞僉乕侾僉乕		*/
	 SPECIAL_KEY,		/* 墳梡捠怣僉乕			*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 REVIEW_KEY,		/* 捠怣拞巭				*/
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂俇價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_07_KEY,	/* 儚儞僞僢僠俧僉乕		*/
	 ONETOUCH_17_KEY,	/* 儚儞僞僢僠俻僉乕		*/
	 TEN_6_KEY,			/* 僥儞僉乕俇僉乕		*/
	 TEN_4_KEY,			/* 僥儞僉乕係僉乕		*/
	 BROADCAST_KEY,		/* 摨曬僉乕				*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 CMD_LIST_KEY,		/* 俹捠怣娗棟			*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂俈價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_08_KEY,	/* 儚儞僞僢僠俫僉乕		*/
	 ONETOUCH_18_KEY,	/* 儚儞僞僢僠俼僉乕		*/
	 TEN_9_KEY,			/* 僥儞僉乕俋僉乕		*/
	 TEN_7_KEY,			/* 僥儞僉乕俈僉乕		*/
	 GROUP_KEY,			/* 僌儖乕僾僉乕			*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 TCH_LIST_KEY,		/* 俹儚儞僞僢僠儕僗僩	*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂俉價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_09_KEY,	/* 儚儞僞僢僠俬僉乕		*/
	 ONETOUCH_19_KEY,	/* 儚儞僞僢僠俽僉乕		*/
	 TEN_SHARP_KEY,		/* 僥儞僉乕仈僉乕		*/
	 TEN_AST_KEY,		/* 僥儞僉乕仏僉乕		*/
	 MEMORY_TX_KEY,		/* 儊儌儕憲怣僉乕		*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 SPD_LIST_KEY,		/* 俹抁弅儕僗僩			*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂俋價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 COPY_KEY,			/* 僐僺乕僉乕			*/
	 AUTO_RX_KEY,		/* 帺摦庴怣僉乕			*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂侾侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 START_KEY,			/* 僗僞乕僩僉乕			*/
	 STOP_KEY,			/* 僗僩僢僾僉乕			*/
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL},				/* NULL 				*/
};

/*******************************************
 * 僉乕僞僀僾侾
 ******************************************/
CONST UBYTE KeyTypeTable1[][KEY_MATRICS_COLUM_MAX] = {
/* 俲俤倄 俼俷倂侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL},				/* NULL */

/* 俲俤倄 俼俷倂侾價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠俙僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俲僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俤僉乕		*/
	 NUMBER,			/* 僥儞僉乕俀僉乕		*/
	 FUNCTION,			/* 婡擻乛亜				*/
	 LEFT_ARROW,		/* 嵍栴報僉乕			*/ /* Modify by SMuratec L.Z.W 2003/10/10 */
	 SPEED},			/* 抁弅丄揹榖挔			*/ /* Modify by SMuratec L.Z.W 2003/07/28 */

/* 俲俤倄 俼俷倂俀價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠俛僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俴僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俰僉乕		*/
	 NUMBER,			/* 僥儞僉乕俆僉乕		*/
	 CHARACTER,			/* 暥帤僉乕			    */ /* Modify by SMuratec L.Z.W 2003/10/10 */
	 DIALMARK,			/* 僟僀儎儖婰崋僉乕		*/ /* Modify by SMuratec L.Z.W 2003/10/10 */
	 REDIAL},			/* 儕僟僀儎儖乛億乕僘	*/

/* 俲俤倄 俼俷倂俁價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠俠僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俵僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俷僉乕		*/
	 NUMBER,			/* 僥儞僉乕俉僉乕		*/
	 ENTER,				/* 擹搙丄僙僢僩			*/
	 COMM_REPORT,		/* 捠怣徹				*/ /* Modify by SMuratec L.Z.W 2003/08/01 */
	 HOLD},				/* 曐棷僉乕				*/ /* Modify by SMuratec L.Z.W 2003/08/01 */

/* 俲俤倄 俼俷倂係價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠俢僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俶僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俿僉乕		*/
	 NUMBER,			/* 僥儞僉乕侽僉乕		*/
	 CLEAR,				/* 夋幙丄僋儕傾			*/
	 VOLUME,			/* 壒検挷惍僉乕			*/ /* Add by Y.kano 2003/08/27 */
	 HOOK},				/* 僼僢僋丄夛榖梊栺		*/

/* 俲俤倄 俼俷倂俆價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠俥僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俹僉乕		*/
	 NUMBER,			/* 僥儞僉乕俁僉乕		*/
	 NUMBER,			/* 僥儞僉乕侾僉乕		*/
	 SPECIAL,			/* 墳梡捠怣僉乕			*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 REVIEW,			/* 捠怣拞巭				*/
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂俇價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠俧僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俻僉乕		*/
	 NUMBER,			/* 僥儞僉乕俇僉乕		*/
	 NUMBER,			/* 僥儞僉乕係僉乕		*/
	 BROADCAST,			/* 摨曬僉乕				*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 CMD_LIST,			/* 俹捠怣娗棟			*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂俈價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠俫僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俼僉乕		*/
	 NUMBER,			/* 僥儞僉乕俋僉乕		*/
	 NUMBER,			/* 僥儞僉乕俈僉乕		*/
	 GROUP,				/* 僌儖乕僾僉乕			*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 TCH_LIST,			/* 俹儚儞僞僢僠儕僗僩	*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂俉價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠俬僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俽僉乕		*/
	 SHARP,				/* 僥儞僉乕仈僉乕		*/
	 AST,				/* 僥儞僉乕仏僉乕		*/
	 SINGLE,			/* 儊儌儕憲怣僉乕		*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 SPD_LIST,			/* 俹抁弅儕僗僩			*/ /* Added by SMuratec L.Z.W 2003/08/04 */
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂俋價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 COPY,				/* 僐僺乕僉乕			*/
	 SINGLE,			/* 帺摦庴怣僉乕			*/ /* Modify by SMuratec L.Z.W 2003/08/04 */
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂侾侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 START,				/* 僗僞乕僩僉乕			*/
	 STOP,				/* 僗僩僢僾僉乕			*/
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL,				/* NULL					*/
	 NULL},				/* NULL 				*/
};
#endif


#if (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec 棝 2004/5/27 */
/*******************************************
 * 僉乕僥乕僽儖侾乮俽俿俷俠俲俫俷俴俵俀乯
 ******************************************/
CONST UBYTE KeyTableSheet1[][KEY_MATRICS_COLUM_MAX] = {
/* 俲俤倄 俼俷倂侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 SPEED_KEY,			/* 抁弅丄揹榖挔			*/
	 REDIAL_KEY,		/* 儕僟僀儎儖乛億乕僘	*/
	 HOLD_KEY,			/* 曐棷僉乕				*/
	 MERCURY_KEY,		/* 僾儗僼傿僋僗僉乕		*//* Added by SMuratec C.P 2004/07/08 for prefix */
	 REVIEW_KEY,		/* 僼傽僋僗拞巭			*/
	 HOOK_KEY,			/* 僆儞僼僢僋			*/
	 BROADCAST_KEY},	/* 摨曬僉乕				*/

/* 俲俤倄 俼俷倂侾價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 CLEAR_KEY,			/* 夋幙丄僋儕傾			*/
	 CURSOR_LEFT_KEY,	/* 亙僉乕			    */
	 SPECIAL_KEY},		/* 墳梡捠怣僉乕			*/

/* 俲俤倄 俼俷倂俀價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_01_KEY,	/* 儚儞僞僢僠侽侾僉乕		*/
	 ONETOUCH_05_KEY,	/* 儚儞僞僢僠侽俆僉乕		*/
	 ONETOUCH_09_KEY,	/* 儚儞僞僢僠侽俋僉乕		*/
	 ONETOUCH_13_KEY,	/* 儚儞僞僢僠侾俁僉乕		*/
	 ONETOUCH_17_KEY,	/* 儚儞僞僢僠侾俈僉乕		*/
	 NULL,				/* NULL	*/
	 NULL},				/* NULL	*/

/* 俲俤倄 俼俷倂俁價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_03_KEY,	/* 儚儞僞僢僠侽俁僉乕		*/
	 ONETOUCH_07_KEY,	/* 儚儞僞僢僠侽俈僉乕		*/
	 ONETOUCH_11_KEY,	/* 儚儞僞僢僠侾侾僉乕		*/
	 ONETOUCH_15_KEY,	/* 儚儞僞僢僠侾俆僉乕		*/
	 ONETOUCH_19_KEY,	/* 儚儞僞僢僠侾俋僉乕		*/
	 NULL,				/* NULL	*/
	 NULL},				/* NULL	*/

/* 俲俤倄 俼俷倂係價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_02_KEY,	/* 儚儞僞僢僠侽俀僉乕		*/
	 ONETOUCH_06_KEY,	/* 儚儞僞僢僠侽俇僉乕		*/
	 ONETOUCH_10_KEY,	/* 儚儞僞僢僠侾侽僉乕		*/
	 ONETOUCH_14_KEY,	/* 儚儞僞僢僠侾係僉乕		*/
	 ONETOUCH_18_KEY,	/* 儚儞僞僢僠侾俉僉乕		*/
	 NULL,				/* NULL	*/
	 NULL},				/* NULL	*/

/* 俲俤倄 俼俷倂俆價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 SET_KEY,			/* 擹搙丄僙僢僩			*/
	 FUNCTION_KEY,		/* 婡擻乛亜 			*/
	 GROUP_KEY},		/* 僌儖乕僾僉乕			*/

/* 俲俤倄 俼俷倂俇價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 DIAL_MARK_KEY,		/* 僟僀儎儖婰崋僉乕		*/
	 CHARACTER_KEY,		/* 暥帤僉乕			    */
	 MEMORY_TX_KEY},	/* 儊儌儕憲怣僉乕		*/

/* 俲俤倄 俼俷倂俈價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH_04_KEY,	/* 儚儞僞僢僠侽係僉乕		*/
	 ONETOUCH_08_KEY,	/* 儚儞僞僢僠侽俉僉乕		*/
	 ONETOUCH_12_KEY,	/* 儚儞僞僢僠侾俀僉乕		*/
	 ONETOUCH_16_KEY,	/* 儚儞僞僢僠侾俇僉乕		*/
	 ONETOUCH_20_KEY,	/* 儚儞僞僢僠俀侽僉乕		*/
	 NULL,				/* NULL	*/
	 NULL},				/* NULL	*/

/* 俲俤倄 俼俷倂俉價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 TEN_3_KEY,			/* 僥儞僉乕俁僉乕		*/
	 TEN_6_KEY,			/* 僥儞僉乕俇僉乕		*/
	 TEN_9_KEY,			/* 僥儞僉乕俋僉乕		*/
	 TEN_SHARP_KEY,		/* 僥儞僉乕仈僉乕		*/
	 NULL,				/* NULL	*/
	 START_KEY,			/* 僗僞乕僩僉乕			*/
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂俋價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 TEN_2_KEY,			/* 僥儞僉乕俀僉乕		*/
	 TEN_5_KEY,			/* 僥儞僉乕俆僉乕		*/
	 TEN_8_KEY,			/* 僥儞僉乕俉僉乕		*/
	 TEN_0_KEY,			/* 僥儞僉乕侽僉乕		*/
	 NULL,				/* NULL	*/
	 COPY_KEY,			/* 僐僺乕僉乕			*/
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂侾侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 TEN_1_KEY,			/* 僥儞僉乕侾僉乕		*/
	 TEN_4_KEY,			/* 僥儞僉乕係僉乕		*/
	 TEN_7_KEY,			/* 僥儞僉乕俈僉乕		*/
	 TEN_AST_KEY,		/* 僥儞僉乕仏僉乕		*/
	 NULL,				/* NULL	*/
	 STOP_KEY,			/* 僗僩僢僾僉乕			*/
	 AUTO_RX_KEY},		/* 帺摦庴怣僉乕			*/
};

/*******************************************
 * 僉乕僞僀僾侾
 ******************************************/
CONST UBYTE KeyTypeTable1[][KEY_MATRICS_COLUM_MAX] = {
/* 俲俤倄 俼俷倂侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 SPEED,				/* 抁弅丄揹榖挔			*/
	 REDIAL,			/* 儕僟僀儎儖乛億乕僘	*/
	 HOLD,				/* 曐棷僉乕				*/
	 MERCURY,			/* 僾儗僼傿僋僗			*//* Added by SMuratec C.P 2004/07/08 for prefix */
	 REVIEW,			/* 僼傽僋僗拞巭			*/
	 HOOK,				/* 僆儞僼僢僋			*/
	 BROADCAST},		/* 摨曬僉乕				*/


/* 俲俤倄 俼俷倂侾價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 CLEAR,				/* 夋幙丄僋儕傾			*/
	 LEFT_ARROW,		/* 嵍栴報僉乕			*/
	 SPECIAL},			/* 墳梡捠怣僉乕			*/

/* 俲俤倄 俼俷倂俀價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠侽侾僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侽俆僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侽俋僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俁僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俈僉乕		*/
	 NULL,				/* NULL	*/
	 NULL},				/* NULL	*/

/* 俲俤倄 俼俷倂俁價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠侽俁僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侽俈僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾侾僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俆僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俋僉乕		*/
	 NULL,				/* NULL	*/
	 NULL},				/* NULL	*/

/* 俲俤倄 俼俷倂係價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠侽俀僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侽俇僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾侽僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾係僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俉僉乕		*/
	 NULL,				/* NULL	*/
	 NULL},				/* NULL	*/

/* 俲俤倄 俼俷倂俆價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 ENTER,				/* 擹搙丄僙僢僩			*/
	 FUNCTION,			/* 婡擻乛亜 			*/
	 GROUP},			/* 僌儖乕僾僉乕			*/

/* 俲俤倄 俼俷倂俇價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 NULL,				/* NULL */
	 DIALMARK,			/* 僟僀儎儖婰崋僉乕		*/
	 CHARACTER,			/* 暥帤僉乕			    */
	 SINGLE},			/* 儊儌儕憲怣僉乕		*/

/* 俲俤倄 俼俷倂俈價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 ONETOUCH,			/* 儚儞僞僢僠侽係僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侽俉僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俀僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠侾俇僉乕		*/
	 ONETOUCH,			/* 儚儞僞僢僠俀侽僉乕		*/
	 NULL,				/* NULL	*/
	 NULL},				/* NULL	*/

/* 俲俤倄 俼俷倂俉價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NUMBER,			/* 僥儞僉乕俁僉乕		*/
	 NUMBER,			/* 僥儞僉乕俇僉乕		*/
	 NUMBER,			/* 僥儞僉乕俋僉乕		*/
	 SHARP,				/* 僥儞僉乕仈僉乕		*/
	 NULL,				/* NULL	*/
	 START,				/* 僗僞乕僩僉乕			*/
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂俋價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NUMBER,			/* 僥儞僉乕俀僉乕		*/
	 NUMBER,			/* 僥儞僉乕俆僉乕		*/
	 NUMBER,			/* 僥儞僉乕俉僉乕		*/
	 NUMBER,			/* 僥儞僉乕侽僉乕		*/
	 NULL,				/* NULL	*/
	 COPY,				/* 僐僺乕僉乕			*/
	 NULL},				/* NULL 				*/

/* 俲俤倄 俼俷倂侾侽價僢僩傾僒僀儞 */
	{NULL,				/* NULL */
	 NUMBER,			/* 僥儞僉乕侾僉乕		*/
	 NUMBER,			/* 僥儞僉乕係僉乕		*/
	 NUMBER,			/* 僥儞僉乕俈僉乕		*/
	 AST,				/* 僥儞僉乕仏丄僩乕儞僉乕		*/
	 NULL,				/* NULL	*/
	 STOP,				/* 僗僩僢僾僉乕			*/
	 SINGLE},			/* 帺摦庴怣僉乕			*/
};
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(LVNDR2) */
