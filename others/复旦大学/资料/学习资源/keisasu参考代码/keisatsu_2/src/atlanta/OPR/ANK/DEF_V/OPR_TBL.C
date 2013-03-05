/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_TBL.C
*	Author		: 渡辺一章
*	Date		: 1996/10/16
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: オペレーションテーブル宣言
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
#include	"\src\atlanta\define\fcm_def.h"
#endif
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\sysdoc.h"
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
#include	"\src\atlanta\define\syslocal.h"
#endif
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
#include	"\src\atlanta\define\apl_msg.h"
#endif

/*月の日数*/ /* 月は１月から始まる */
CONST UBYTE MaxDayTable[][13] = {
	/* 月  1  2  3  4  5  6  7  8  9 10 11 12 */
	{NULL,31,28,31,30,31,30,31,31,30,31,30,31},	/* 普通の年（閏年でない） */
	{NULL,31,29,31,30,31,30,31,31,30,31,30,31}	/* 閏年 */
};

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
/**************************************************************************************************
 * 文字テーブル
 *************************************************************************************************/
/* 注）SHCのコンパイラーでは半角カナのキャラクター定義がコンパイルできないため、文字コードで定義します */
CONST UBYTE KATAKANA_CharacterTable[OPR_TEN_KEY_MAX][OPR_KATAKANA_CHARACTER_MAX] = {
	{ 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, '\0' },		/* １キー（'ｱ', 'ｲ', 'ｳ', 'ｴ', 'ｵ', 'ｧ', 'ｨ', 'ｩ', 'ｪ', 'ｫ'）	*/
	{ 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, '\0' },										/* ２キー（'ｶ', 'ｷ', 'ｸ', 'ｹ', 'ｺ'）							*/
	{ 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, '\0' },										/* ３キー（'ｻ', 'ｼ', 'ｽ', 'ｾ', 'ｿ'）							*/
	{ 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xAF, '\0' },								/* ４キー（'ﾀ', 'ﾁ', 'ﾂ', 'ﾃ', 'ﾄ', 'ｯ'）						*/
	{ 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, '\0' },										/* ５キー（'ﾅ', 'ﾆ', 'ﾇ', 'ﾈ', 'ﾉ'）							*/
	{ 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, '\0' },										/* ６キー（'ﾊ', 'ﾋ', 'ﾌ', 'ﾍ', 'ﾎ'）							*/
	{ 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, '\0' },										/* ７キー（'ﾏ', 'ﾐ', 'ﾑ', 'ﾒ', 'ﾓ'）							*/
	{ 0xD4, 0xD5, 0xD6, 0xAC, 0xAD, 0xAE, '\0' },								/* ８キー（'ﾔ', 'ﾕ', 'ﾖ', 'ｬ', 'ｭ', 'ｮ'）						*/
	{ 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, '\0' },										/* ９キー（'ﾗ', 'ﾘ', 'ﾙ', 'ﾚ', 'ﾛ'）							*/
	{ 0xDC, 0xA6, 0xDD, '\0' },													/* ０キー（'ﾜ', 'ｦ', 'ﾝ'）										*/
	{ 0xDE, 0xDF, '\0' },														/* ＊キー（'ﾞ', 'ﾟ'）											*/
	{ '-', '(', ')', '_', 0xA5, '.', ' ', '\0' }								/* ＃キー（'-', '(', ')', '_', '･', '.', ' '）					*/
};

CONST UBYTE AlphamericCharacterTable[OPR_TEN_KEY_MAX][OPR_ALPHAMERIC_CHARACTER_MAX] = {
	{ '1', '\0' },																/* １キー */
	{ '2', 'A', 'B', 'C', 'a', 'b', 'c', '\0' },								/* ２キー */
	{ '3', 'D', 'E', 'F', 'd', 'e', 'f', '\0' },								/* ３キー */
	{ '4', 'G', 'H', 'I', 'g', 'h', 'i', '\0' },								/* ４キー */
	{ '5', 'J', 'K', 'L', 'j', 'k', 'l', '\0' },								/* ５キー */
	{ '6', 'M', 'N', 'O', 'm', 'n', 'o', '\0' },								/* ６キー */
	{ '7', 'P', 'Q', 'R', 'S', 'p', 'q', 'r', 's', '\0' },						/* ７キー */
	{ '8', 'T', 'U', 'V', 't', 'u', 'v', '\0' },								/* ８キー */
	{ '9', 'W', 'X', 'Y', 'Z', 'w', 'x', 'y', 'z', '\0' },						/* ９キー */
	{ '0', '\0' },																/* ０キー */
	{ '*', '\0' },																/* ＊キー */
	{ '#', '*', '@', '&', '-', '(', ')', '_', 0xA5, '.', ';', ',', ' ', '\0' }	/* ＃キー */
};

CONST struct ANK_CharacterTable_t ANK_CharacterTable[] = {
	/* 区点コード, 半角文字 */
	{ 101, ' ' },	/* ASCII=20h */
	{ 102, 0xA4 },	/* ASCII=A4h '､' */
	{ 103, 0xA1 },	/* ASCII=A1h '｡' */
	{ 104, ',' },	/* ASCII=2Ch */
	{ 105, '.' },	/* ASCII=2Eh */
	{ 106, 0xA5 },	/* ASCII=A5h '･' */
	{ 107, ':' },	/* ASCII=3Ah */
	{ 108, ';' },	/* ASCII=3Bh */
	{ 109, '?' },	/* ASCII=3Fh */
	{ 110, '!' },	/* ASCII=21h */
	{ 114, '`' },	/* ASCII=60h */
	{ 116, '^' },	/* ASCII=5Eh */
	{ 118, '_' },	/* ASCII=5Fh */
	{ 131, '/' },	/* ASCII=2Fh */
	{ 135, '|' },	/* ASCII=7Ch */
	{ 139, '\'' },	/* ASCII=27h */
	{ 141, '"' },	/* ASCII=22h */
	{ 142, '(' },	/* ASCII=28h */
	{ 143, ')' },	/* ASCII=29h */
	{ 146, '[' },	/* ASCII=5Bh */
	{ 147, ']' },	/* ASCII=5Dh */
	{ 148, '{' },	/* ASCII=7Bh */
	{ 149, '}' },	/* ASCII=7Dh */
	{ 150, '<' },	/* ASCII=3Ch */
	{ 151, '>' },	/* ASCII=3Eh */
	{ 154, 0xA2 },	/* ASCII=A2h '｢' */
	{ 155, 0xA3 },	/* ASCII=A3h '｣' */
	{ 160, '+' },	/* ASCII=2Bh */
	{ 161, '-' },	/* ASCII=2Dh */
	{ 165, '=' },	/* ASCII=3Dh */
	{ 179, '\\' },	/* ASCII=5Ch */
	{ 180, '$' },	/* ASCII=24h */
	{ 183, '%' },	/* ASCII=25h */
	{ 184, '#' },	/* ASCII=23h */
	{ 185, '&' },	/* ASCII=26h */
	{ 186, '*' },	/* ASCII=2Ah */
	{ 187, '@' },	/* ASCII=40h */
	{ 210, 0x7E },	/* LCD FONT=7Eh '→' */
	{ 211, 0x7F },	/* LCD FONT=7Fh '←' */
	{   0, '\0' }	/* 終端判断用 */
};
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/***********************************************
 * ワンタッチ->記号変換テーブル
 * 1995/04/12 Eguchi
 ***********************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
/* テーブルサイズは多少大きくなりますが、記号の割り当てが変更されても、プログラムの変更がいらない様に
** テーブルの形式を変更しました（ただし、アルファベットと記号が兼用される場合は、プログラムの変更が必要です）
** 注）無駄な領域の方が多いので、ワンタッチの数がもっと増えるようであれば、もとのテーブルの形式に戻して下さい
*/
CONST UBYTE OnetouchSignalTable[] = {
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	/* ONETOUCH_01_KEY - ONETOUCH_08_KEY */
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	/* ONETOUCH_09_KEY - ONETOUCH_16_KEY */
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	/* ONETOUCH_17_KEY - ONETOUCH_24_KEY */
	NULL,	NULL,	',',	'.',	':',	'\'',	'&',	' ',	/* ONETOUCH_25_KEY - ONETOUCH_32_KEY */
	'(',	')',	'+',	'-',	'/',	NULL,	NULL,	NULL,	/* ONETOUCH_33_KEY - ONETOUCH_40_KEY */

	'!',	'"',	'$',	'%',	NULL,	NULL,	NULL,	NULL,	/* ONETOUCH_41_KEY - ONETOUCH_48_KEY */
	';',	'<',	'=',	'>',	NULL,	NULL,	NULL,	NULL,	/* ONETOUCH_41_KEY - ONETOUCH_56_KEY */
	'?',	'@',	'[',	']',	NULL,	NULL,	NULL,	NULL,	/* ONETOUCH_57_KEY - ONETOUCH_64_KEY */
	'{',	'}',	'_',	NULL,	NULL,	NULL,	NULL,	NULL	/* ONETOUCH_65_KEY - ONETOUCH_72_KEY */
};
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)
CONST UBYTE OnetouchSignalTable[] = {
	'!',	/* ONETOUCH_A/a_KEY */
	'"',	/* ONETOUCH_B/b_KEY */
	'$',	/* ONETOUCH_C/c_KEY */
	'%',	/* ONETOUCH_D/d_KEY */
	'&',	/* ONETOUCH_E/e_KEY */
	'\'',	/* ONETOUCH_F/f_KEY */
	'(',	/* ONETOUCH_G/g_KEY */
	')',	/* ONETOUCH_H/h_KEY */
	'+',	/* ONETOUCH_I/i_KEY */
	',',	/* ONETOUCH_J/j_KEY */
	'-',	/* ONETOUCH_K/k_KEY */
	'.',	/* ONETOUCH_L/l_KEY */
	'/',	/* ONETOUCH_M/m_KEY */
	':',	/* ONETOUCH_N/n_KEY */
	';',	/* ONETOUCH_O/o_KEY */
	'<',	/* ONETOUCH_P/p_KEY */
	'=',	/* ONETOUCH_Q/q_KEY */
	'>',	/* ONETOUCH_R/r_KEY */
	'?',	/* ONETOUCH_S/s_KEY */
	'@',	/* ONETOUCH_T/t_KEY */
	'[',	/* ONETOUCH_U/u_KEY */
	']',	/* ONETOUCH_V/v_KEY */
	'{',	/* ONETOUCH_W/w_KEY */
	'}',	/* ONETOUCH_X/x_KEY */
 #if defined(JPN)
	0xA5,	/* ONETOUCH_Y/y_KEY */
 #else
	0xC5,	/* ONETOUCH_Y/y_KEY */
 #endif
	' '		/* ONETOUCH_Z/z_KEY */
};
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

CONST UBYTE OnetouchSignalTable[] = {
	'!',	/* ONETOUCH_A/a_KEY */
	'"',	/* ONETOUCH_B/b_KEY */
	'$',	/* ONETOUCH_C/c_KEY */
	'%',	/* ONETOUCH_D/d_KEY */
	'&',	/* ONETOUCH_E/e_KEY */
	'\'',	/* ONETOUCH_F/f_KEY */
	'(',	/* ONETOUCH_G/g_KEY */
	')',	/* ONETOUCH_H/h_KEY */
	'+',	/* ONETOUCH_I/i_KEY */
	',',	/* ONETOUCH_J/j_KEY */
	'-',	/* ONETOUCH_K/k_KEY */
	'.',	/* ONETOUCH_L/l_KEY */
	'/',	/* ONETOUCH_M/m_KEY */
	':',	/* ONETOUCH_N/n_KEY */
	';',	/* ONETOUCH_O/o_KEY */
	'<',	/* ONETOUCH_P/p_KEY */
	'=',	/* ONETOUCH_Q/q_KEY */
	'>',	/* ONETOUCH_R/r_KEY */
	'?',	/* ONETOUCH_S/s_KEY */
	'@',	/* ONETOUCH_T/t_KEY */
	'[',	/* ONETOUCH_U/u_KEY */
	']',	/* ONETOUCH_V/v_KEY */
	'{',	/* ONETOUCH_W/w_KEY */
	'}',	/* ONETOUCH_X/x_KEY */
 #if (0) /* 記号入力のコード内容を修正します。By H.Fujimura 1999/03/03 */
// #if defined(JPN)
//	0xA5,	/* ONETOUCH_Y/y_KEY */
// #else
//	0xC5,	/* ONETOUCH_Y/y_KEY */
// #endif
 #else
	'_',	/* ONETOUCH_Y/y_KEY */
 #endif
	' '		/* ONETOUCH_Z/z_KEY */
};
#endif

/****************************************************:
 * 電話帳関係
 * 1995/05/25 Eguchi
 ******************************************************/
#if defined(JPN)
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (電話帳データ格納順テーブルはV-650と同じくなります) Added by SMuratec L.Z.W 2003/10/21 */
/* 電話帳データ格納順テーブル（この順番に従って電話帳データは格納されている） */
CONST UBYTE TelBookSortPriorityTable[] = {
	0xB1, 0xB2, 0xB3, 0xB4, 0xB5,		/* 'ｱ','ｲ','ｳ','ｴ','ｵ', */
	0xB6, 0xB7, 0xB8, 0xB9, 0xBA,		/* 'ｶ','ｷ','ｸ','ｹ','ｺ', */
	0xBB, 0xBC, 0xBD, 0xBE, 0xBF,		/* 'ｻ','ｼ','ｽ','ｾ','ｿ', */
	0xC0, 0xC1, 0xC2, 0xC3, 0xC4,		/* 'ﾀ','ﾁ','ﾂ','ﾃ','ﾄ', */
	0xC5, 0xC6, 0xC7, 0xC8, 0xC9,		/* 'ﾅ','ﾆ','ﾇ','ﾈ','ﾉ', */
	0xCA, 0xCB, 0xCC, 0xCD, 0xCE,		/* 'ﾊ','ﾋ','ﾌ','ﾍ','ﾎ', */
	0xCF, 0xD0, 0xD1, 0xD2, 0xD3,		/* 'ﾏ','ﾐ','ﾑ','ﾒ','ﾓ', */
	0xD4, 0xD5, 0xD6,					/* 'ﾔ','ﾕ','ﾖ',         */
	0xD7, 0xD8, 0xD9, 0xDA, 0xDB,		/* 'ﾗ','ﾘ','ﾙ','ﾚ','ﾛ', */
	0xDC, 0xA6, 0xDD,					/* 'ﾜ','ｦ','ﾝ',         */
	'A','a','B','b','C','c','D','d','E','e','F','f','G','g','H','h','I','i','J','j','K','k','L','l','M','m',
	'N','n','O','o','P','p','Q','q','R','r','S','s','T','t','U','u','V','v','W','w','X','x','Y','y','Z','z',
	'0','1','2','3','4','5','6','7','8','9',
	'!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/',';',':','<','=','>','?','@','[',']','{','}',
	'_',0xA5,0xDE, 0xDF,							/* '･','ﾞ','ﾟ', add	2001/07/17 K.Sasaki */
	' ','\0'
};	/* キーワード(頭文字）のソート順を保持（オフセットが順番になる）*/

/* 頭文字の大小関係を定義するテーブル */
CONST UBYTE TelBookSearchLineTable[] = {
	0xB1, 0xB1, 0xB1, 0xB1, 0xB1,		/* 'ｱ','ｱ','ｱ','ｱ','ｱ', */
	0xB6, 0xB6, 0xB6, 0xB6, 0xB6,		/* 'ｶ','ｶ','ｶ','ｶ','ｶ', */
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB,		/* 'ｻ','ｻ','ｻ','ｻ','ｻ', */
	0xC0, 0xC0, 0xC0, 0xC0, 0xC0,		/* 'ﾀ','ﾀ','ﾀ','ﾀ','ﾀ', */
	0xC5, 0xC5, 0xC5, 0xC5, 0xC5,		/* 'ﾅ','ﾅ','ﾅ','ﾅ','ﾅ', */
	0xCA, 0xCA, 0xCA, 0xCA, 0xCA,		/* 'ﾊ','ﾊ','ﾊ','ﾊ','ﾊ', */
	0xCF, 0xCF, 0xCF, 0xCF, 0xCF,		/* 'ﾏ','ﾏ','ﾏ','ﾏ','ﾏ', */
	0xD4, 0xD4, 0xD4,					/* 'ﾔ','ﾔ','ﾔ',         */
	0xD7, 0xD7, 0xD7, 0xD7, 0xD7,		/* 'ﾗ','ﾗ','ﾗ','ﾗ','ﾗ', */
	0xDC, 0xDC, 0xDD,					/* 'ﾜ','ﾜ','ﾝ',         */
	'A','A','B','B','C','C','D','D','E','E','F','F','G','G','H','H','I','I','J','J','K','K','L','L','M','M',
	'N','N','O','O','P','P','Q','Q','R','R','S','S','T','T','U','U','V','V','W','W','X','X','Y','Y','Z','Z',
	'0','0','0','0','0','0','0','0','0','0',
	'!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!',
	'!','!','!','!',		/* add 2001/07/17 K.Sasaki */
	'!','\0'
};
#else /*(PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
/* 電話帳データ格納順テーブル（この順番に従って電話帳データは格納されている） */
CONST UBYTE TelBookSortPriorityTable[] = {	/* 135 byte */
	0xB1, 0xB2, 0xB3, 0xB4, 0xB5,		/* 'ｱ','ｲ','ｳ','ｴ','ｵ', */
	0xB6, 0xB7, 0xB8, 0xB9, 0xBA,		/* 'ｶ','ｷ','ｸ','ｹ','ｺ', */
	0xBB, 0xBC, 0xBD, 0xBE, 0xBF,		/* 'ｻ','ｼ','ｽ','ｾ','ｿ', */
	0xC0, 0xC1, 0xC2, 0xC3, 0xC4,		/* 'ﾀ','ﾁ','ﾂ','ﾃ','ﾄ', */
	0xC5, 0xC6, 0xC7, 0xC8, 0xC9,		/* 'ﾅ','ﾆ','ﾇ','ﾈ','ﾉ', */
	0xCA, 0xCB, 0xCC, 0xCD, 0xCE,		/* 'ﾊ','ﾋ','ﾌ','ﾍ','ﾎ', */
	0xCF, 0xD0, 0xD1, 0xD2, 0xD3,		/* 'ﾏ','ﾐ','ﾑ','ﾒ','ﾓ', */
	0xD4, 0xD5, 0xD6,					/* 'ﾔ','ﾕ','ﾖ',         */
	0xD7, 0xD8, 0xD9, 0xDA, 0xDB,		/* 'ﾗ','ﾘ','ﾙ','ﾚ','ﾛ', */
	0xDC, 0xA6, 0xDD,					/* 'ﾜ','ｦ','ﾝ',         */
	'A','B','C','D','E','F','G', 'H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
	'a','b','c','d','e','f','g', 'h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
	'!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/',';',':','<','=','>','?','@','[',']','{','}',' ',
	'0','1','2','3','4','5', '6','7','8','9',
	'\0'
};	/* キーワード(頭文字）のソート順を保持（オフセットが順番になる）*/

/* 頭文字の大小関係を定義するテーブル */
CONST UBYTE TelBookSearchLineTable[] = {	/* 135 byte */
	0xB1, 0xB1, 0xB1, 0xB1, 0xB1,		/* 'ｱ','ｱ','ｱ','ｱ','ｱ', */
	0xB6, 0xB6, 0xB6, 0xB6, 0xB6,		/* 'ｶ','ｶ','ｶ','ｶ','ｶ', */
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB,		/* 'ｻ','ｻ','ｻ','ｻ','ｻ', */
	0xC0, 0xC0, 0xC0, 0xC0, 0xC0,		/* 'ﾀ','ﾀ','ﾀ','ﾀ','ﾀ', */
	0xC5, 0xC5, 0xC5, 0xC5, 0xC5,		/* 'ﾅ','ﾅ','ﾅ','ﾅ','ﾅ', */
	0xCA, 0xCA, 0xCA, 0xCA, 0xCA,		/* 'ﾊ','ﾊ','ﾊ','ﾊ','ﾊ', */
	0xCF, 0xCF, 0xCF, 0xCF, 0xCF,		/* 'ﾏ','ﾏ','ﾏ','ﾏ','ﾏ', */
	0xD4, 0xD4, 0xD4,					/* 'ﾔ','ﾔ','ﾔ',         */
	0xD7, 0xD7, 0xD7, 0xD7, 0xD7,		/* 'ﾗ','ﾗ','ﾗ','ﾗ','ﾗ', */
	0xDC, 0xDC, 0xDD,					/* 'ﾜ','ﾜ','ﾝ',         */
	'A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A',
	'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a',
	'!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!',
	'0','0','0','0','0','0','0','0','0','0',
	'\0'
};
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#else /* 日本以外 */
/* 電話帳データ格納順テーブル（この順番に従って電話帳データは格納されている） */
CONST UBYTE TelBookSortPriorityTable[] = {	/* 60 byte */
	'A','B','C','D','E','F','G', 'H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
	'a','b','c','d','e','f','g', 'h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
	'!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/',';',':','<','=','>','?','@','[',']','{','}',' ',
	'0','1','2','3','4','5', '6','7','8','9',
	'\0'
};	/* キーワード(頭文字）のソート順を保持（オフセットが順番になる）*/

/* 頭文字の大小関係を定義するテーブル */
CONST UBYTE TelBookSearchLineTable[] = {	/* 60 byte */
	'A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A',
	'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a',
	'!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!',
	'0','0','0','0','0','0','0','0','0','0',
	'\0'
};
#endif

/*---------------------------------------*/
/* コマンドの種別を変換するテーブル		 */
/* 同報、メモリ送信ON/OFFの設定によりITEM*/
/* を変換するためのテーブル				 */
/*---------------------------------------*/
/*-------------------------------------------------------------*
 * コマンド種別		:SpecialCommandValue.CommandOption.Itemに相当(SpecialCommandOperation()でセット)
 * 同報入力	    	:InputNumber.MultiNumberStatusで判断
 * メモリ送信設定	:SYB_LocalStatus[0]で判断
 * 注）メモリ送信の種類が増えた時は、CheckMemoryTxCommand()にも追加する事
 *-------------------------------------------------------------*/
CONST UBYTE CommandOptionTable[][4] = {

/*		コマンド種別			|		同報入力			|		スキャナ送信		|		メモリ送信				*/
	{SYS_CHAR_TX,					SYS_DELAYED_BROADCAST,		SYS_SCANNER_TX,				SYS_MEMORY_TX				},
	{SYS_DELAYED_BROADCAST,			SYS_DELAYED_BROADCAST,		SYS_DELAYED_BROADCAST,		SYS_DELAYED_BROADCAST		},
	{SYS_DELAYED_SCANNER_TX,		SYS_DELAYED_BROADCAST,		SYS_DELAYED_SCANNER_TX,		SYS_DELAYED_MEMORY_TX		},
	{SYS_SCANNER_SECURE_TX,			SYS_MEMORY_SECURE_TX,		SYS_SCANNER_SECURE_TX,		SYS_MEMORY_SECURE_TX		},
	{SYS_SCANNER_RELAY_BROADCAST,	SYS_MEMORY_RELAY_BROADCAST,	SYS_SCANNER_RELAY_BROADCAST,SYS_MEMORY_RELAY_BROADCAST	},
	{SYS_POLLING_RX,				SYS_POLLING_RX,				SYS_POLLING_RX,				SYS_POLLING_RX				},
	{SYS_DB_POLLING_RX,				SYS_DB_POLLING_RX,			SYS_DB_POLLING_RX,			SYS_DB_POLLING_RX			},
	{SYS_SCANNER_SUB_ADDRESS_TX,	SYS_MEMORY_SUB_ADDRESS_TX,	SYS_SCANNER_SUB_ADDRESS_TX,	SYS_MEMORY_SUB_ADDRESS_TX	},
	{SYS_SELECT_POLLING_RX,			SYS_SELECT_POLLING_RX,		SYS_SELECT_POLLING_RX,		SYS_SELECT_POLLING_RX		},
	{SYS_CIPHER_TX,					SYS_CIPHER_TX,				SYS_CIPHER_TX,				SYS_CIPHER_TX				},
	{0xFF,							0xFF,						0xFF,						0xFF						}
};

/***************************************************************
 * ファンクションテーブル
 ***************************************************************/
/* ワンタッチモード */
CONST struct FUNCTION_TABLE_t OneTouchFunction[] = {
	{   1, '\0', OPR_YES, D2W_EnterOneTouchMode,			EnterOneTouch,				NULL},
	{   2, '\0', OPR_YES, D2W_EraseOneTouchMode,			EraseOneTouch,				NULL},
	{   3, '\0', OPR_YES, D2W_PrintOneTouchMode,			PrintOneTouchList,			NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};

/* 短縮モード */
CONST struct FUNCTION_TABLE_t SpeedDialFunction[] = {
	{   1, '\0', OPR_YES, D2W_EnterSpeedDialMode,			EnterSpeedDial,				NULL},
	{   2, '\0', OPR_YES, D2W_EraseSpeedDialMode,			EraseSpeedDial,				NULL},
	{   3, '\0', OPR_YES, D2W_PrintSpeedDialMode,			PrintSpeedDialList,			NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};

/* プログラムワンタッチモード */
CONST struct FUNCTION_TABLE_t ProgramOnetouchFunction[] = {
	{   1, '\0', OPR_YES, D2W_EnterProgramOneTouchMode,		EnterProgramOneTouch,		NULL},
	{   2, '\0', OPR_YES, D2W_EraseProgramOneTouchMode,		EraseProgramOneTouch,		NULL},
	{   3, '\0', OPR_YES, D2W_PrintProgramOneTouchMode,		PrintProgramOneTouchList,	NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};

/* ポーリングモード */
CONST struct FUNCTION_TABLE_t PollingFunction[] = {
	{   1, '\0', OPR_YES, D2W_StorePollingDocumentMode,		StorePollingDocument,		NULL},
	{   2, '\0', OPR_YES, D2W_ErasePollingDocumentMode,		ErasePollingDocument,		NULL},
	{   3, '\0', OPR_YES, D2W_PrintPollingDocumentMode,		PrintPollingDocument,		NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};

/* 親展モード */
CONST struct FUNCTION_TABLE_t SecureMailFunction[] = {
	{   1, '\0', OPR_YES, D2W_SetSecureMailBoxMode,			SetSecureMailBox,			NULL},
	{   2, '\0', OPR_YES, D2W_PrintSecureMailListMode,		PrintSecureMailList,		NULL},
	{   3, '\0', OPR_YES, D2W_PrintSecureMailMode,			PrintSecureMailDocument,	NULL},
	{   4, '\0', OPR_YES, D2W_SecureMailHoldTimeMode,		SetSecureMailHoldTime,		NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};

/* 通信予約モード */
CONST struct FUNCTION_TABLE_t DelayedCommandsFunction[] = {
	{   1, '\0', OPR_YES, D2W_PrintCommandsMode,			PrintCommandList,			NULL},
	{   2, '\0', OPR_YES, D2W_PrintStoredDocumentMode,		PrintStoredDocument,		NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};

/* 通信管理モード */
CONST struct FUNCTION_TABLE_t SetReportFunction[] = {
	{   1, '\0', OPR_YES, D2W_JournalOnOffMode,				SetJournalOnOff,			NULL},
	{   2, '\0', OPR_YES, D2W_PrintJournalMode,				PrintJournalList,			NULL},
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/22 */
	{   3, '\0', OPR_YES, D2W_PrintDailyReportMode,			PrintDailyReport,			NULL},
	{   4, '\0', OPR_YES, D2W_SettingCommunicationResult,	SetCommunicationResult,		NULL},
 #if (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	{   5, '\0', OPR_YES, D2W_Print_ND_JournalMode,			Print_ND_JournalList,		NULL},
 #endif
#else
	{   3, '\0', OPR_YES, D2W_SettingCommunicationResult,	SetCommunicationResult,		NULL},
 #if (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	{   4, '\0', OPR_YES, D2W_Print_ND_JournalMode,			Print_ND_JournalList,		NULL},
 #endif
#endif
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};

/* ユーザーファンクション */
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
 #if defined(JPN)
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingPrintParameters,		SetRxPrintParameters,		NULL},	/* ﾌﾟﾘﾝﾄﾊﾟﾗﾒｰﾀ		*/
	{   3, '\0', OPR_YES, D2W_SettingCopyProtect,			SetCopyProtect,				NULL},	/* ｺﾋﾟｰ禁止			*/
	{   4, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   5, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   6, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   7, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   8, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   9, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	/* 閉域通信ｾｯﾄ		*/
	{  10, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
	{  11, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  12, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  13, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingDialIn,				SetDialIn,					NULL},	/* ﾀﾞｲｱﾙｲﾝｾｯﾄ		*/
	{  16, '\0', OPR_YES, D2W_SettingPINAccessMode,			SetPINAccessMode,			NULL},	/* PINｱｸｾｽﾓｰﾄﾞｾｯﾄ	*/
	{  17, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  18, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  19, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
 #endif	/* defined(JPN) */
 #if defined(USA) || defined(AUS)
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingPrintParameters,		SetRxPrintParameters,		NULL},	/* ﾌﾟﾘﾝﾄﾊﾟﾗﾒｰﾀ		*/
	{   3, '\0', OPR_YES, D2W_SettingCopyProtect,			SetCopyProtect,				NULL},	/* ｺﾋﾟｰ禁止			*/
	{   4, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   5, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   6, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   7, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   8, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   9, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	/* 閉域通信ｾｯﾄ		*/
	{  10, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
	{  11, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  12, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  13, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingSilentOperation,		SetSilentOperation,			NULL},	/* 無音ﾓｰﾄﾞｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  16, '\0', OPR_YES, D2W_SettingPINAccessMode,			SetPINAccessMode,			NULL},	/* PINｱｸｾｽﾓｰﾄﾞｾｯﾄ	*/
	{  17, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  18, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  19, '\0', OPR_YES, D2W_SettingRingMasta,				SetRingMaster,				NULL},	/* ﾘﾝｸﾞﾏｽﾀｰｾｯﾄ		*/
	{  20, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
 #endif	/* defined(USA) || defined(AUS) */
 #if defined(GBR)		/* Modified by S.Fukui Sep.26,1997 */
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingPrintParameters,		SetRxPrintParameters,		NULL},	/* ﾌﾟﾘﾝﾄﾊﾟﾗﾒｰﾀ		*/
	{   3, '\0', OPR_YES, D2W_SettingCopyProtect,			SetCopyProtect,				NULL},	/* ｺﾋﾟｰ禁止			*/
	{   4, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   5, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   6, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   7, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   8, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   9, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	/* 閉域通信ｾｯﾄ		*/
	{  10, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
	{  11, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  12, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  13, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingSilentOperation,		SetSilentOperation,			NULL},	/* 無音ﾓｰﾄﾞｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  16, '\0', OPR_YES, D2W_SettingPINAccessMode,			SetPINAccessMode,			NULL},	/* PINｱｸｾｽﾓｰﾄﾞｾｯﾄ	*/
	{  17, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  18, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  19, '\0', OPR_YES, D2W_SettingRxAlarm,				SetRxAlarm,					NULL},	/* 受信ｱﾗｰﾑｾｯﾄ		*/
	{  20, '\0', OPR_YES, D2W_SettingMercuryMode,			SetMercury,					NULL},	/* ﾏｰｷｭﾘｰ			*/
	{  21, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
 #endif	/* defined(GBR) */
 #if defined(EC1) || defined(DEU) || defined(FRA)
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingPrintParameters,		SetRxPrintParameters,		NULL},	/* ﾌﾟﾘﾝﾄﾊﾟﾗﾒｰﾀ		*/
	{   3, '\0', OPR_YES, D2W_SettingCopyProtect,			SetCopyProtect,				NULL},	/* ｺﾋﾟｰ禁止			*/
	{   4, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   5, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   6, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   7, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   8, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   9, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	/* 閉域通信ｾｯﾄ		*/
	{  10, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
	{  11, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  12, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  13, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingSilentOperation,		SetSilentOperation,			NULL},	/* 無音ﾓｰﾄﾞｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  16, '\0', OPR_YES, D2W_SettingPINAccessMode,			SetPINAccessMode,			NULL},	/* PINｱｸｾｽﾓｰﾄﾞｾｯﾄ	*/
	{  17, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  18, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  19, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
 #endif
 #if defined(EUR)		/* Modified by M.H 99/10/01 */
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingPrintParameters,		SetRxPrintParameters,		NULL},	/* ﾌﾟﾘﾝﾄﾊﾟﾗﾒｰﾀ		*/
	{   3, '\0', OPR_YES, D2W_SettingCopyProtect,			SetCopyProtect,				NULL},	/* ｺﾋﾟｰ禁止			*/
	{   4, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   5, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   6, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   7, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   8, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   9, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	/* 閉域通信ｾｯﾄ		*/
	{  10, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
	{  11, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  12, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  13, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingSilentOperation,		SetSilentOperation,			NULL},	/* 無音ﾓｰﾄﾞｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  16, '\0', OPR_YES, D2W_SettingPINAccessMode,			SetPINAccessMode,			NULL},	/* PINｱｸｾｽﾓｰﾄﾞｾｯﾄ	*/
	{  17, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  18, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  19, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
 #endif	/* defined(EUR) */
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) */

#if (PRO_KEYPANEL == PANEL_POPLAR_L)
 #if defined(JPN)
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingPrintParameters,		SetRxPrintParameters,		NULL},	/* ﾌﾟﾘﾝﾄﾊﾟﾗﾒｰﾀ		*/
	{   3, '\0', OPR_YES, D2W_SettingCopyParameters,		SetCopyParameters,			NULL},	/* ｺﾋﾟｰﾊﾟﾗﾒｰﾀ		*/
	{   4, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   5, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   6, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   7, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   8, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   9, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	/* 閉域通信ｾｯﾄ		*/
	{  10, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
	{  11, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  12, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  13, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingDialIn,				SetDialIn,					NULL},	/* ﾀﾞｲｱﾙｲﾝｾｯﾄ		*/
	{  16, '\0', OPR_YES, D2W_SettingPINAccessMode,			SetPINAccessMode,			NULL},	/* PINｱｸｾｽﾓｰﾄﾞｾｯﾄ	*/
	{  17, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  18, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  19, '\0', OPR_YES, D2W_SettingHoldMelody,			SetHoldMelody,				NULL},	/* 保留ﾒﾛﾃﾞｨｰｾｯﾄ	*/
 #if defined(POPLAR_N) /* ←ＮＴＴ仕様と判断する条件がないため 98/03/13 T.Fukumoto */
	{  20, '\0', OPR_YES, D2W_SettingRemoteReceive,			SetRemoteReceive,			NULL},	/* リモート受信ｾｯﾄ	*/
	{  21, '\0', OPR_YES, D2W_SettingOnHookReceive,			SetOnHookReceive,			NULL},	/* ｵﾝﾌｯｸ受信ｾｯﾄ		*/
	{  22, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
 #elif defined(POPLAR_F)
   #if defined(JP1)
	{  20, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
   #else
	{  20, '\0', OPR_YES, D2W_SettingRemoteReceive,			SetRemoteReceive,			NULL},	/* リモート受信ｾｯﾄ	*/
	{  21, '\0', OPR_YES, D2W_SettingOnHookReceive,			SetOnHookReceive,			NULL},	/* ｵﾝﾌｯｸ受信ｾｯﾄ		*/
	{  22, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
   #endif
 #else
	{  20, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
 #endif
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
 #else
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingPrintParameters,		SetRxPrintParameters,		NULL},	/* ﾌﾟﾘﾝﾄﾊﾟﾗﾒｰﾀ		*/
	{   3, '\0', OPR_YES, D2W_SettingCopyParameters,		SetCopyParameters,			NULL},	/* ｺﾋﾟｰﾊﾟﾗﾒｰﾀ		*/
	{   4, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   5, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   6, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   7, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   8, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   9, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	/* 閉域通信ｾｯﾄ		*/
	{  10, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
	{  11, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  12, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  13, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingPINAccessMode,			SetPINAccessMode,			NULL},	/* PINｱｸｾｽﾓｰﾄﾞｾｯﾄ	*/
	{  16, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  17, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  18, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
 #endif	/* defined(JPN) */
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_L) */

#if (PRO_KEYPANEL == PANEL_ANZU_L)
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingPrintParameters,		SetRxPrintParameters,		NULL},	/* ﾌﾟﾘﾝﾄﾊﾟﾗﾒｰﾀ		*/
	{   3, '\0', OPR_YES, D2W_SettingCopyParameters,		SetCopyParameters,			NULL},	/* ｺﾋﾟｰﾊﾟﾗﾒｰﾀ		*/
 #if (PRO_PC_PRINT == DISABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能なし */
	{   4, '\0', OPR_YES, D2W_SettingPaperSize,				SetPaperSize,				NULL},	/* 記録紙ｻｲｽﾞｾｯﾄ	*/
 #else
	{	4, '\0', OPR_YES, D2W_SettingPaperSize,				Set_PCR_PaperSize,			NULL},	/* 記録紙ｻｲｽﾞｾｯﾄ(PCプリント対応用) */
 #endif
	{   5, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   6, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   7, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   8, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   9, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{  10, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	/* 閉域通信ｾｯﾄ		*/
	{  11, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
	{  12, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  13, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingSilentOperation,		SetSilentOperation,			NULL},	/* 無音ﾓｰﾄﾞｾｯﾄ		*/
	{  16, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  17, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  18, '\0', OPR_YES, D2W_SettingPINAccessMode,			SetPINAccessMode,			NULL},	/* PINｱｸｾｽﾓｰﾄﾞｾｯﾄ	*/
	{  19, '\0', OPR_YES, D2W_SettingRingMasta,				SetRingMaster,				NULL},	/* ﾘﾝｸﾞﾏｽﾀｰｾｯﾄ		*/
	{  20, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  21, '\0', OPR_YES, D2W_SettingResetDrumLife,			ResetDrumLife,				NULL},	/* ﾄﾞﾗﾑ寿命ｶｳﾝﾀｰﾘｾｯﾄ*/
 #if defined(GBR)
	{  22, '\0', OPR_YES, D2W_SettingRxAlarm,				SetRxAlarm,					NULL},	/* 受信ｱﾗｰﾑｾｯﾄ		*/
	{  23, '\0', OPR_YES, D2W_SettingMercuryMode,			SetMercury,					NULL},	/* ﾏｰｷｭﾘｰ			*/
 #endif
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};
/* Ｆ－１０１専用機能Ｊテーブル（１０と１２削除） 1997/12/26 Y.Matsukuma */
CONST struct FUNCTION_TABLE_t UserSettingsFunction_Category2[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingPrintParameters,		SetRxPrintParameters,		NULL},	/* ﾌﾟﾘﾝﾄﾊﾟﾗﾒｰﾀ		*/
	{   3, '\0', OPR_YES, D2W_SettingCopyParameters,		SetCopyParameters,			NULL},	/* ｺﾋﾟｰﾊﾟﾗﾒｰﾀ		*/
 #if (PRO_PC_PRINT == DISABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能なし */
	{   4, '\0', OPR_YES, D2W_SettingPaperSize,				SetPaperSize,				NULL},	/* 記録紙ｻｲｽﾞｾｯﾄ	*/
 #else
	{	4, '\0', OPR_YES, D2W_SettingPaperSize,				Set_PCR_PaperSize,			NULL},	/* 記録紙ｻｲｽﾞｾｯﾄ(PCプリント対応用) */
 #endif
	{   5, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   6, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   7, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   8, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   9, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
/*	{  10, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	@@ 閉域通信ｾｯﾄ		*/
	{  11, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
/*	{  12, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	@@ ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  13, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingSilentOperation,		SetSilentOperation,			NULL},	/* 無音ﾓｰﾄﾞｾｯﾄ		*/
	{  16, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  17, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  18, '\0', OPR_YES, D2W_SettingPINAccessMode,			SetPINAccessMode,			NULL},	/* PINｱｸｾｽﾓｰﾄﾞｾｯﾄ	*/
	{  19, '\0', OPR_YES, D2W_SettingRingMasta,				SetRingMaster,				NULL},	/* ﾘﾝｸﾞﾏｽﾀｰｾｯﾄ		*/
	{  20, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  21, '\0', OPR_YES, D2W_SettingResetDrumLife,			ResetDrumLife,				NULL},	/* ﾄﾞﾗﾑ寿命ｶｳﾝﾀｰﾘｾｯﾄ*/
 #if defined(GBR)
	{  22, '\0', OPR_YES, D2W_SettingRxAlarm,				SetRxAlarm,					NULL},	/* 受信ｱﾗｰﾑｾｯﾄ		*/
	{  23, '\0', OPR_YES, D2W_SettingMercuryMode,			SetMercury,					NULL},	/* ﾏｰｷｭﾘｰ			*/
 #endif
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};
#endif	/* defined(ANZU_L) */

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)	*//* Add By H.Fujimura 1999/02/03 */
#if (PRO_KEYPANEL == PANEL_HINOKI)	/* Add By H.Fujimura 1999/02/03 */ /* Add by Y.Kano 2003/07/11 */

 #if defined(JPN)
  #if defined (KEISATSU) /* 警察FAX 05/05/07 石橋正和 */
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingCopyProtect,			SetCopyProtect,				NULL},	/* ｺﾋﾟｰ禁止			*/
	{   3, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   4, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   5, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   6, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{  11, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  12, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  16, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
/* 警察FAX Added by SMuratec K.W.Q 2005/06/09 */
	{  17, '\0', OPR_YES, D2W_SettingRemoteRxParameters,	SetRemoteRxParameters,		NULL},	/* リモート特番設定 */

	{  18, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
  #else
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingCopyProtect,			SetCopyProtect,				NULL},	/* ｺﾋﾟｰ禁止			*/
	{   3, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   4, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   5, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   6, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   7, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   8, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	/* 閉域通信ｾｯﾄ		*/
	{   9, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
	{  10, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  11, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  12, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  13, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingDialIn,				SetDialIn,					NULL},	/* ﾀﾞｲｱﾙｲﾝｾｯﾄ		*/
	{  15, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  16, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  17, '\0', OPR_YES, D2W_SettingHoldMelody,			SetHoldMelody,				NULL},	/* 保留ﾒﾛﾃﾞｨｰｾｯﾄ	*/
/*  #if defined(HINOKI3)	/@ by K.Watanabe 2004/10/12 */
  #if (PRO_PREFIX_KEY == ENABLE) /* T.Nose 2005/01/13 */
	{  18, '\0', OPR_YES, D2W_SettingMercuryMode,			SetMercury,					NULL},	/* ﾏｰｷｭﾘｰ			*//* by K.Watanabe 2004/10/12 */
	{  19, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい */
  #else
	{  18, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
  #endif
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
  #endif
 #else
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingCopyProtect,			SetCopyProtect,				NULL},	/* ｺﾋﾟｰ禁止			*/
	{   3, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   4, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   5, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   6, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   7, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   8, '\0', OPR_YES, D2W_SettingClosedNetwork,			SetClosedNetwork,			NULL},	/* 閉域通信ｾｯﾄ		*/
	{   9, '\0', OPR_YES, D2W_SettingSecurityTransmission,	SetSecurityTx,				NULL},	/* ﾊﾟｽﾜｰﾄﾞ送信ｾｯﾄ	*/
	{  10, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  11, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  12, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  13, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
	{  14, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  15, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
  #if (0)	/* ＴＷＮは保留メロディなし by H.Hirao 1999/02/04 */
	{  16, '\0', OPR_YES, D2W_SettingHoldMelody,			SetHoldMelody,				NULL},	/* 保留ﾒﾛﾃﾞｨｰｾｯﾄ	*/
	{  17, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
  #else
	{  16, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
  #endif
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
 #endif	/* defined(JPN) */
#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) */

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/05 */

 #if defined(JPN)
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
  #if defined (STOCKHM2)		/* Modify by SMuratec K.W.Q 2004/05/24 */
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingPrintParameters,		SetRxPrintParameters,		NULL},	/* ﾌﾟﾘﾝﾄﾊﾟﾗﾒｰﾀ		*/
	{   3, '\0', OPR_YES, D2W_SettingCopyParameters,		SetCopyParameters,			NULL},	/* ｺﾋﾟｰﾊﾟﾗﾒｰﾀｰｾｯﾄ	*/
	{   4, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   5, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   6, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   7, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   8, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   9, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{  10, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  11, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
	{  12, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  13, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
#if (0)
	{  14, '\0', OPR_YES, D2W_SettingDialIn,				SetDialIn,					NULL},	/* ﾀﾞｲｱﾙﾄｰﾝ検出		*/
	{  15, '\0', OPR_YES, D2W_SettingHoldMelody,			SetHoldMelody,				NULL},	/* 保留ﾒﾛﾃﾞｨｰｾｯﾄ	*/
	{  16, '\0', OPR_YES, D2W_SettingMercuryMode,			SetMercury,					NULL},	/* ﾏｰｷｭﾘｰ			*//* Added by SMuratec C.P 2004/07/08 for prefix */
	{  17, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
#else
	{  14, '\0', OPR_YES, D2W_SettingHoldMelody,			SetHoldMelody,				NULL},	/* 保留ﾒﾛﾃﾞｨｰｾｯﾄ	*/
	{  15, '\0', OPR_YES, D2W_VolumeControl,				VolumeKeyOperation,			NULL},	 /*音量控制追加Add by SMuratec C.P 2004/07/23 */
	{  16, '\0', OPR_YES, D2W_SettingMercuryMode,			SetMercury,					NULL},	/* ﾏｰｷｭﾘｰ			*//* Added by SMuratec C.P 2004/07/08 for prefix */
	{  17, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
#endif
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
  #else
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingCopyProtect,			SetCopyProtect,				NULL},	/* ｺﾋﾟｰ禁止			*/
	{   3, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   4, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   5, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   6, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   7, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   8, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{   9, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  10, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
   #if 0 /* Deleted by SMuratec L.Z.W 2003/09/17 */
	{  11, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
   #endif
	/* SATSUKI2はダイヤルイン設定は別でやります。by Y.Kano 2003/09/09 */
	{  11, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  12, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  13, '\0', OPR_YES, D2W_SettingHoldMelody,			SetHoldMelody,				NULL},	/* 保留ﾒﾛﾃﾞｨｰｾｯﾄ	*/
	{  14, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
  #endif		/* End of (defined (STOCKHM2)) */
};
 #else
CONST struct FUNCTION_TABLE_t UserSettingsFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingScanParameters,		SetScanParameters,			NULL},	/* 読みとりﾊﾟﾗﾒｰﾀ	*/
	{   2, '\0', OPR_YES, D2W_SettingCopyProtect,			SetCopyProtect,				NULL},	/* ｺﾋﾟｰ禁止			*/
	{   3, '\0', OPR_YES, D2W_SettingDialingPause,			SetDialingPause,			NULL},	/* ﾎﾟｰｽﾞ時間ｾｯﾄ		*/
	{   4, '\0', OPR_YES, D2W_SettingNumberOfRings,			SetNumberOfRings,			NULL},	/* 着信ﾍﾞﾙ回数		*/
	{   5, '\0', OPR_YES, D2W_SettingRedial	,				SetRedial,					NULL},	/* ﾘﾀﾞｲｱﾙ設定		*/
	{   6, '\0', OPR_YES, D2W_SettingECMMode,				SetECMMode,					NULL},	/* ECM/G3切り替え	*/
	{   7, '\0', OPR_YES, D2W_SettingPasscode,				SetPasscode,				NULL},	/* ﾊﾟｽｺｰﾄﾞｾｯﾄ		*/
	{   8, '\0', OPR_YES, D2W_SettingBlockJunkMail,			SetBlockJunkFax,			NULL},	/* ﾀﾞｲﾚｸﾄﾒｰﾙ防止ｾｯﾄ	*/
	{   9, '\0', OPR_YES, D2W_SettingRemoteDiagnostic,		SetRemoteDiagnostic,		NULL},	/* ﾘﾓｰﾄ診断ｾｯﾄ		*/
	{  10, '\0', OPR_YES, D2W_SettingMemoryTransmission,	SetMemoryTransmission,		NULL},	/* ﾒﾓﾘｰ送信ｾｯﾄ		*/
#if 0 /* Deleted by SMuratec L.Z.W 2003/09/17 */
	{  11, '\0', OPR_YES, D2W_SettingStamp,					SetStamp,					NULL},	/* 済みｽﾀﾝﾌﾟｾｯﾄ		*/
#endif
	{  11, '\0', OPR_YES, D2W_SettingProtectPasscode,		SetProtectPasscode,			NULL},	/* ﾌﾟﾛﾃｸﾄﾊﾟｽｺｰﾄﾞ	*/
	{  12, '\0', OPR_YES, D2W_SettingOperationProtect,		SetOperationProtect,		NULL},	/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ	*/
	{  13, '\0', OPR_YES, D2W_SettingPrintSettings,			PrintSettingList,			NULL},	/* 機器設定ﾘｽﾄ:設定追加の際(機能+Ｊの)最終項目に割当て下さい By S.Fukui Jan.6,1998 */
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy, 				NULL}
};
 #endif	/* defined(JPN) */
#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* カバーページモード */
CONST struct FUNCTION_TABLE_t MessageFunction[] = {
	{   1, '\0', OPR_YES, D2W_SetMessageOnOff,				SetMessageOnOff,			NULL},
	{   2, '\0', OPR_YES, D2W_SetMessage,					SetMessageDataMode,			NULL},
	{   3, '\0', OPR_YES, D2W_PrintMessageList,				PrintMessageList,			NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};

#if (PRO_DEPARTMENT == ENABLE)
/* 部門管理モード */
CONST struct FUNCTION_TABLE_t DepartmentCodeFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingDepartmentProtect,		SetDepartmentProtect,		NULL},
	{   2, '\0', OPR_YES, D2W_SettingDepartmentCode,		SetDepartmentCode,			NULL},
	{   3, '\0', OPR_YES, D2W_SettingDepartmentOnOff,		SetDepartmentOnOff,			NULL},
 #if (PRO_DEPART_NEW_LIST == ENABLE)
/* 簡易料金管理モード */
	{   4, '\0', OPR_YES, D2W_PrintDepartTimeList,			PrintDepartTimeList,		NULL},	/* by thonda 1997/12/03 */
	{   5, '\0', OPR_YES, D2W_EraseDepartTimeList,			EraseDepartTimeList,		NULL},	/* by thonda 1997/12/03 */
 #endif
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};
#endif

#if (PRO_BATCH_TX == ENABLE)
/* 一括送信モード */
CONST struct FUNCTION_TABLE_t BatchTxFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingBatchBox,				SetBatchBox,				NULL},
	{   2, '\0', OPR_YES, D2W_PrintBatchBoxList,			PrintBatchBoxList,			NULL},
	{   3, '\0', OPR_YES, D2W_PrintBatchDocList,			PrintBatchDocumentList,		NULL},
	{   4, '\0', OPR_YES, D2W_PrintBatchDoc,				PrintBatchTxDocument,		NULL},
	{   5, '\0', OPR_YES, D2W_EraseBatchBox,				EraseBatchBox,				NULL},
	{   6, '\0', OPR_YES, D2W_EraseBatchDoc,				EraseBatchTxDocument,		NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};
#endif

#if (PRO_SECURITY_RX == ENABLE)
/* セキュリティ受信モード */
CONST struct FUNCTION_TABLE_t SecurityRxFunction[] = {
	{   1, '\0', OPR_YES, D2W_SettingSecurityRx,			SetSecurityReceive,			NULL},
	{   2, '\0', OPR_YES, D2W_PrintMemoryReceiveDoc,		PrintMemoryReceiveDoc,		NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};
#endif

#if (PRO_F_CODE == ENABLE)
/* Ｆコードモード */
CONST struct FUNCTION_TABLE_t FcodeFunction[] = {
	{   1, '\0', OPR_YES, D2W_EnterFcodeBoxMode,			SetFcodeBox,				NULL},
	{   2, '\0', OPR_YES, D2W_PrintFcodeBoxListMode,		PrintFcodeBoxList,			NULL},
	{   3, '\0', OPR_YES, D2W_PrintFcodeStoreDocListMode,	PrintFcodeBoxDocList,		NULL},
	{   4, '\0', OPR_YES, D2W_PrintFcodeStoreDocMode,		PrintFcodeBoxDocument,		NULL},
	{   5, '\0', OPR_YES, D2W_EraseFcodeBoxMode,			EraseFcodeBox,				NULL},
	{   6, '\0', OPR_YES, D2W_EraseFcodeDocMode,			EraseFcodeBoxDocument,		NULL},
	{   7, '\0', OPR_YES, D2W_StoreFcodeDocMode,			StoreFcodeBoxDocument,		NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};
#endif

#if (PRO_CIPHER == ENABLE)
/* 暗号化機能モード */
CONST struct FUNCTION_TABLE_t CipherFunction[] = {
	{   1, '\0', OPR_YES, D2W_EnterCipherKeyBookMode,		SetCipherKeyBook,			NULL},
	{   2, '\0', OPR_YES, D2W_PrintCipherKeyBookListMode,	PrintCipherKeyBookList,		NULL},
	{   3, '\0', OPR_YES, D2W_PrintCipherKeyMode,			PrintSettingCipherKeyBook,	NULL},
	{   4, '\0', OPR_YES, D2W_EraseCipherKeyBookMode,		EraseCipherKeyBook,			NULL},
	{   5, '\0', OPR_YES, D2W_EraseCipherRxDocMode,			EraseCipherRxDocument,		NULL},
	{   6, '\0', OPR_YES, D2W_EnterDefaultCipherKeyMode,	SetCipherDefaultKey,		NULL},
	{   7, '\0', OPR_YES, D2W_EnterCipherServiceLabelMode,	SetServiceLabelPosition,	NULL},
	{   8, '\0', OPR_YES, D2W_EnterCipherPassCodeMode,		SetCipherPassCode,			NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};
#endif

#if (PRO_CLASS1 == ENABLE)
/* クラス１モード */
CONST struct FUNCTION_TABLE_t Class1Function[] = {
	{   1, '\0', OPR_YES, D2W_SettingRS232CPCFaxScan,		SetRS232CPCFaxScsn,			NULL},
	{   2, '\0', OPR_YES, D2W_SettingRS232CParameter,		SetRS232CParameter,			NULL},
	{   3, '\0', OPR_YES, D2W_SettingRS232CPCFaxInitial,	SetRS232CPCFaxInitial,		NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
/***************************
** ｲﾝﾀｰﾈｯﾄFAXﾌｧﾝｸｼｮﾝﾓｰﾄﾞ
***************************/
/* アカウントモード */
CONST	struct	FUNCTION_TABLE_t EMailFunction[] = {
	{1,		'\0',	OPR_YES,	D2W_SetUserDataMode,		SetUserData,   		NULL},
	{2,		'\0',	OPR_YES,	D2W_SetMachineStateMode,   	SetMachineState,	NULL},
	{3,		'\0',	OPR_YES,	D2W_EraseUserDataMode,    	EraseUserData,		NULL},
	{4,		'\0',	OPR_YES,	D2W_PrintUserDataMode,		PrintUserDataList,	NULL},
	{'\0',	'\0', 	OPR_NO,  	NULL, 						FunctionDummy, 		NULL}
};

/* メール受信モード */
CONST	struct	FUNCTION_TABLE_t ReceiveMail[] = {
	{1,		'\0',	OPR_YES,	D2W_ManualReceiveMail,		ManualReceiveMail,  NULL},
	{2,		'\0',	OPR_YES,	D2W_PrintReceiveMailMode,   PrintReceiveMail,		NULL},
	{'\0',	'\0', 	OPR_NO,  	NULL, 						FunctionDummy, 		NULL}
};

/* メールアドレスモード */
CONST	struct	FUNCTION_TABLE_t MailAddressFunction[] = {
	{1,		'\0',	OPR_YES,	D2W_SetMailAddress,			SetMailAddress,   	NULL},
	{2,		'\0',	OPR_YES,	D2W_SetMailGroup,  			SetMailGroup,     	NULL},
	{3,		'\0',	OPR_YES,	D2W_EraseMailAddressMode,  	EraseMailAddress,	NULL},
	{4,		'\0',	OPR_YES,	D2W_EraseMailGroupMode,    	EraseMailGroup,  	NULL},
	{5,		'\0',	OPR_YES,	D2W_PrintMailAddressMode, 	PrintMailAddressList,NULL},
	{6,		'\0',	OPR_YES,	D2W_PrintMailGroupMode,   	PrintMailGroupList, NULL},
	{'\0',	'\0', 	OPR_NO,  	NULL, 						FunctionDummy, 		NULL}
};

/* メールコマンド確認モード */
CONST	struct	FUNCTION_TABLE_t ConfirmInternetFaxCommand[] = {
	{1,		'\0',	OPR_YES,	D2W_PrintMailComMode,		PrintMailCommandList , NULL},
	{2,		'\0',	OPR_YES,	D2W_PrintStoredMailMode,   	PrintStoredMail,	   NULL},
	{3,		'\0',	OPR_YES,	D2W_PrintMailJounalMode,	PrintMailJournal,		NULL},
	{'\0',	'\0', 	OPR_NO,  	NULL, 						FunctionDummy, 		   NULL}
};
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
/* ＦＡＸワープモード */
CONST struct FUNCTION_TABLE_t FaxWarpFunction[] = {
	{   1, '\0', OPR_YES, D2W_EnterFaxWarpMode,				EnterFaxWarp,				NULL},
	{   2, '\0', OPR_YES, D2W_PrintFaxWarpMode,				PrintFaxWarpList,			NULL},
	{   3, '\0', OPR_YES, D2W_SetFaxWarpMode,				SetFaxWarp,					NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
/* ナンバーディスプレイモード */
CONST struct FUNCTION_TABLE_t NumberDisplayFunction[] = {
	{   1, '\0', OPR_YES, D2W_EnterNumberDisplayMode,		EnterNumberDisplay,			NULL},
	{   2, '\0', OPR_YES, D2W_PrintNumberDisplayMode,		PrintNumberDisplayList,		NULL},
	{   3, '\0', OPR_YES, D2W_SetNumberDisplayMode,			SetNumberDisplay,			NULL},
	{'\0', '\0', OPR_NO,  NULL,								FunctionDummy,				NULL}
};
#endif

/* メインファンクション */
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
CONST struct FUNCTION_TABLE_t MainFunction[] = {
	{ 'A', '\0', OPR_YES, D2W_OneTouchDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)OneTouchFunction},
	{ 'B', '\0', OPR_YES, D2W_SpeedDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SpeedDialFunction},
	{ 'C', '\0', OPR_YES, D2W_ProgramOneTouchMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)ProgramOnetouchFunction},
	{ 'D', '\0', OPR_YES, D2W_PollingMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)PollingFunction},
	{ 'E', '\0', OPR_YES, D2W_SecureMailMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SecureMailFunction},
	{ 'F', '\0', OPR_YES, D2W_DelayedCommandsMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DelayedCommandsFunction},
	{ 'G', '\0', OPR_YES, D2W_SetReportMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SetReportFunction},
	{ 'H', '\0', OPR_YES, D2W_PrintGroupMode,		PrintGroupList,			NULL},
	{ 'I', '\0', OPR_YES, D2W_UserInstallMode,		UserInstallOperation,	NULL},
	{ 'J', '\0', OPR_YES, D2W_UserSettingsMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)UserSettingsFunction},
	{ 'K', '\0', OPR_YES, D2W_MessageMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)MessageFunction},
	{ 'L', '\0', OPR_YES, D2W_SetNumberOfPagesMode,	SetNumberOfPages,		NULL},
	{ 'M', '\0', OPR_YES, D2W_SetDepartmentMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DepartmentCodeFunction},
	{ 'N', '\0', OPR_YES, D2W_SetBatchTxMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)BatchTxFunction},
	{ 'O', '\0', OPR_YES, D2W_SecurityReceiveMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)SecurityRxFunction},
	{ 'P', '\0', OPR_YES, D2W_FcodeBoxMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)FcodeFunction},
 #if (PRO_PC_PRINT == ENABLE)
	{ 'Q', '\0', OPR_YES, D2W_ResetPrinterBoardMode,ResetPrinterBoard,		NULL},
 #endif
 #if (PRO_CLASS1 == ENABLE)
	{ 'R', '\0', OPR_YES, D2W_SetClass1Mode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)Class1Function},
 #endif
 #if (PRO_CIPHER == ENABLE)
	{ 'S', '\0', OPR_YES, D2W_SetCipherMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)CipherFunction},
	{ 'T', '\0', OPR_YES, D2W_PrintDecipherDocMode,	PrintDecipherDocument,	NULL},
 #endif
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
 /***********************
 ** ｲﾝﾀｰﾈｯﾄFAXﾌｧﾝｸｼｮﾝ
 ***********************/
 	{ 'U', '\0', OPR_YES, D2W_EMailSettingMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)EMailFunction},
 	{ 'V', '\0', OPR_YES, D2W_ReceiveMailMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)ReceiveMail},
 	{ 'W', '\0', OPR_YES, D2W_SetMailAddressMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)MailAddressFunction},
 	{ 'X', '\0', OPR_YES, D2W_ReviewMailComMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)ConfirmInternetFaxCommand},
 #endif
	{'\0', '\0', OPR_NO,  NULL,						FunctionDummy,			NULL}
};
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) */

#if (PRO_KEYPANEL == PANEL_POPLAR_L)
CONST struct FUNCTION_TABLE_t MainFunction[] = {
	{ 'A', '\0', OPR_YES, D2W_OneTouchDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)OneTouchFunction},
	{ 'B', '\0', OPR_YES, D2W_SpeedDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SpeedDialFunction},
	{ 'C', '\0', OPR_YES, D2W_ProgramOneTouchMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)ProgramOnetouchFunction},
	{ 'D', '\0', OPR_YES, D2W_PollingMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)PollingFunction},
	{ 'E', '\0', OPR_YES, D2W_SecureMailMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SecureMailFunction},
	{ 'F', '\0', OPR_YES, D2W_DelayedCommandsMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DelayedCommandsFunction},
	{ 'G', '\0', OPR_YES, D2W_SetReportMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SetReportFunction},
	{ 'H', '\0', OPR_YES, D2W_PrintGroupMode,		PrintGroupList,			NULL},
	{ 'I', '\0', OPR_YES, D2W_UserInstallMode,		UserInstallOperation,	NULL},
	{ 'J', '\0', OPR_YES, D2W_UserSettingsMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)UserSettingsFunction},
	{ 'K', '\0', OPR_YES, D2W_MessageMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)MessageFunction},
	{ 'L', '\0', OPR_YES, D2W_SetNumberOfPagesMode,	SetNumberOfPages,		NULL},
	{ 'M', '\0', OPR_YES, D2W_SetDepartmentMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DepartmentCodeFunction},
	{ 'N', '\0', OPR_YES, D2W_SetBatchTxMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)BatchTxFunction},
	{ 'O', '\0', OPR_YES, D2W_SecurityReceiveMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)SecurityRxFunction},
	{ 'P', '\0', OPR_YES, D2W_FcodeBoxMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)FcodeFunction},
	{'\0', '\0', OPR_NO,  NULL,						FunctionDummy,			NULL}
};
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_L) */

#if (PRO_KEYPANEL == PANEL_ANZU_L)
CONST struct FUNCTION_TABLE_t MainFunction[] = {
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/17 Y.Matsukuma */
	{ 'A', '\0', OPR_YES, D2W_ProgramOneTouchMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)ProgramOnetouchFunction},
	{ 'B', '\0', OPR_YES, D2W_UserSettingsMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)UserSettingsFunction},
 #else
	{ 'A', '\0', OPR_YES, D2W_OneTouchDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)OneTouchFunction},
	{ 'B', '\0', OPR_YES, D2W_SpeedDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SpeedDialFunction},
	{ 'C', '\0', OPR_YES, D2W_ProgramOneTouchMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)ProgramOnetouchFunction},
	{ 'D', '\0', OPR_YES, D2W_PollingMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)PollingFunction},
	{ 'E', '\0', OPR_YES, D2W_SecureMailMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SecureMailFunction},
	{ 'F', '\0', OPR_YES, D2W_DelayedCommandsMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DelayedCommandsFunction},
	{ 'G', '\0', OPR_YES, D2W_SetReportMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SetReportFunction},
	{ 'H', '\0', OPR_YES, D2W_PrintGroupMode,		PrintGroupList,			NULL},
	{ 'I', '\0', OPR_YES, D2W_UserInstallMode,		UserInstallOperation,	NULL},
	{ 'J', '\0', OPR_YES, D2W_UserSettingsMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)UserSettingsFunction},
	{ 'K', '\0', OPR_YES, D2W_MessageMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)MessageFunction},
	{ 'L', '\0', OPR_YES, D2W_SetNumberOfPagesMode,	SetNumberOfPages,		NULL},
	{ 'M', '\0', OPR_YES, D2W_SetDepartmentMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DepartmentCodeFunction},
	{ 'N', '\0', OPR_YES, D2W_SetBatchTxMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)BatchTxFunction},
  #if (PRO_SECURITY_RX == ENABLE)
	{ 'O', '\0', OPR_YES, D2W_SecurityReceiveMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)SecurityRxFunction},
  #endif
  #if (PRO_CLASS1 == ENABLE)
	{ 'P', '\0', OPR_YES, D2W_SetClass1Mode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)Class1Function},
  #endif
  #if (PRO_PC_PRINT == ENABLE) /* ＧＤＩオペレーション追加 BY Matsukuma 1997/07/24 */
	{ 'Q', '\0', OPR_YES, D2W_ResetPrinterBoardMode,ResetPrinterBoard,		NULL},
  #endif
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
  /***********************
  **IFE: ｲﾝﾀｰﾈｯﾄFAXﾌｧﾝｸｼｮﾝ
  ***********************/
	{ 'R', '\0', OPR_YES, D2W_ReceiveMailMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)ReceiveMail},
	{ 'S', '\0', OPR_YES, D2W_ReviewMailComMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)ConfirmInternetFaxCommand},
	{ 'T', '\0', OPR_YES, D2W_SetMailAddressMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)MailAddressFunction},
	{ 'U', '\0', OPR_YES, D2W_EMailSettingMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)EMailFunction},
  #endif
 #endif
	{'\0', '\0', OPR_NO,  NULL,						FunctionDummy,			NULL}
};
/* Ｆ－１０１専用メインファンクションテーブル（機能Ｅ削除） 1997/12/26 Y.Matsukuma */
CONST struct FUNCTION_TABLE_t MainFunction_Category2[] = {
	{ 'A', '\0', OPR_YES, D2W_OneTouchDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)OneTouchFunction},
	{ 'B', '\0', OPR_YES, D2W_SpeedDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SpeedDialFunction},
	{ 'C', '\0', OPR_YES, D2W_ProgramOneTouchMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)ProgramOnetouchFunction},
	{ 'D', '\0', OPR_YES, D2W_PollingMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)PollingFunction},
/*	{ 'E', '\0', OPR_YES, D2W_SecureMailMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SecureMailFunction},	*/
	{ 'F', '\0', OPR_YES, D2W_DelayedCommandsMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DelayedCommandsFunction},
	{ 'G', '\0', OPR_YES, D2W_SetReportMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SetReportFunction},
	{ 'H', '\0', OPR_YES, D2W_PrintGroupMode,		PrintGroupList,			NULL},
	{ 'I', '\0', OPR_YES, D2W_UserInstallMode,		UserInstallOperation,	NULL},
	{ 'J', '\0', OPR_YES, D2W_UserSettingsMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)UserSettingsFunction_Category2},
	{ 'K', '\0', OPR_YES, D2W_MessageMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)MessageFunction},
	{ 'L', '\0', OPR_YES, D2W_SetNumberOfPagesMode,	SetNumberOfPages,		NULL},
	{ 'M', '\0', OPR_YES, D2W_SetDepartmentMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DepartmentCodeFunction},
	{ 'N', '\0', OPR_YES, D2W_SetBatchTxMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)BatchTxFunction},
 #if (PRO_SECURITY_RX == ENABLE)
	{ 'O', '\0', OPR_YES, D2W_SecurityReceiveMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)SecurityRxFunction},
 #endif
 #if (PRO_CLASS1 == ENABLE)
	{ 'P', '\0', OPR_YES, D2W_SetClass1Mode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)Class1Function},
 #endif
 #if (PRO_PC_PRINT == ENABLE) /* ＧＤＩオペレーション追加 BY Matsukuma 1997/07/24 */
	{ 'Q', '\0', OPR_YES, D2W_ResetPrinterBoardMode,ResetPrinterBoard,		NULL},
 #endif
	{'\0', '\0', OPR_NO,  NULL,						FunctionDummy,			NULL}
};
#endif	/* defined(ANZU_L) */

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)	*//* Add By H.Fujimura 1998/12/28 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By H.Fujimura 1998/12/28 */ /* Add by Y.Kano 2003/07/11 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) /* オペレーション変更 by SMuratec L.Z.W 2003/10/16 */
CONST struct FUNCTION_TABLE_t MainFunction[] = {
	{   1, '\0', OPR_YES, D2W_OneTouchDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)OneTouchFunction},
	{   2, '\0', OPR_YES, D2W_SpeedDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SpeedDialFunction},
	{   3, '\0', OPR_YES, D2W_PollingMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)PollingFunction},
	{   4, '\0', OPR_YES, D2W_DelayedCommandsMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DelayedCommandsFunction},
	{   5, '\0', OPR_YES, D2W_SetReportMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SetReportFunction},
	{   6, '\0', OPR_YES, D2W_PrintGroupMode,		PrintGroupList,			NULL},
	{   7, '\0', OPR_YES, D2W_MessageMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)MessageFunction},
	{   8, '\0', OPR_YES, D2W_SetDepartmentMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DepartmentCodeFunction},
	{   9, '\0', OPR_YES, D2W_UserInstallMode,		UserInstallOperation,	NULL},
	{  10, '\0', OPR_YES, D2W_UserSettingsMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)UserSettingsFunction},
	{  11, '\0', OPR_YES, D2W_SecurityReceiveMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)SecurityRxFunction},
	{  12, '\0', OPR_YES, D2W_FcodeBoxMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)FcodeFunction},
 #if (PRO_RX_DOC_TRANSFER == ENABLE)
	{  13, '\0', OPR_YES, D2W_FaxWarpMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)FaxWarpFunction},
 #endif
 #if (PRO_NUMBER_DISPLAY == ENABLE)
	{  14, '\0', OPR_YES, D2W_NumberDisplayMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)NumberDisplayFunction},
 #endif
 #if (PRO_CLASS1 == ENABLE)	/* added by H.Hirao 1999/01/13 */
	{  15, '\0', OPR_YES, D2W_SetClass1Mode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)Class1Function},
 #endif
	{'\0', '\0', OPR_NO,  NULL,						FunctionDummy,			NULL}
};
#elif (PRO_KEYPANEL == PANEL_STOCKHM2) /* Mod by SMuratec C.P 2004/07/23 */
 #if (0)		/*	DVT: Modify start by SMuratec K.W.Q 2004/09/07	*/
//CONST struct FUNCTION_TABLE_t MainFunction[] = {
//	{   1, '\0', OPR_YES, D2W_OneTouchDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)OneTouchFunction},
//	{   2, '\0', OPR_YES, D2W_SpeedDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SpeedDialFunction},
//	{   3, '\0', OPR_YES, D2W_PollingMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)PollingFunction},
//	{   4, '\0', OPR_YES, D2W_DelayedCommandsMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DelayedCommandsFunction},
//	{   5, '\0', OPR_YES, D2W_SetReportMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SetReportFunction},
//	{   6, '\0', OPR_YES, D2W_PrintGroupMode,		PrintGroupList,			NULL},
//	{   7, '\0', OPR_YES, D2W_MessageMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)MessageFunction},
//	{   8, '\0', OPR_YES, D2W_SecurityReceiveMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)SecurityRxFunction},
//	{   9, '\0', OPR_YES, D2W_UserInstallMode,		UserInstallOperation,	NULL},
//	{  10, '\0', OPR_YES, D2W_UserSettingsMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)UserSettingsFunction},
//	{  11, '\0', OPR_YES, D2W_FcodeBoxMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)FcodeFunction},
// #if (PRO_NUMBER_DISPLAY == ENABLE)
//	{  12, '\0', OPR_YES, D2W_NumberDisplayMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)NumberDisplayFunction},
// #endif
// #if (PRO_CLASS1 == ENABLE)	/* added by H.Hirao 1999/01/13 */
//	{  13, '\0', OPR_YES, D2W_SetClass1Mode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)Class1Function},
// #endif
//	{'\0', '\0', OPR_NO,  NULL,						FunctionDummy,			NULL}
//};
 #else
CONST struct FUNCTION_TABLE_t MainFunction[] = {
	{   1, '\0', OPR_YES, D2W_OneTouchDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)OneTouchFunction},
	{   2, '\0', OPR_YES, D2W_SpeedDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SpeedDialFunction},
	{   3, '\0', OPR_YES, D2W_PollingMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)PollingFunction},
	{   4, '\0', OPR_YES, D2W_DelayedCommandsMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DelayedCommandsFunction},
	{   5, '\0', OPR_YES, D2W_SetReportMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SetReportFunction},
	{   6, '\0', OPR_YES, D2W_PrintGroupMode,		PrintGroupList,			NULL},
	{   7, '\0', OPR_YES, D2W_MessageMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)MessageFunction},
	{   9, '\0', OPR_YES, D2W_UserInstallMode,		UserInstallOperation,	NULL},
	{  10, '\0', OPR_YES, D2W_UserSettingsMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)UserSettingsFunction},
	{  11, '\0', OPR_YES, D2W_SecurityReceiveMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)SecurityRxFunction},
	{  12, '\0', OPR_YES, D2W_FcodeBoxMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)FcodeFunction},
  #if (PRO_NUMBER_DISPLAY == ENABLE)
	{  14, '\0', OPR_YES, D2W_NumberDisplayMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)NumberDisplayFunction},
  #endif
  #if (PRO_CLASS1 == ENABLE)	/* added by H.Hirao 1999/01/13 */
	{  15, '\0', OPR_YES, D2W_SetClass1Mode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)Class1Function},
  #endif
	{'\0', '\0', OPR_NO,  NULL,						FunctionDummy,			NULL}
};
 #endif		/*	DVT: Modify end by SMuratec K.W.Q 2004/09/07	*/
#else /* (PRO_KEYPANEL == PANEL_HINOKI) */
CONST struct FUNCTION_TABLE_t MainFunction[] = {
	{ 'A', '\0', OPR_YES, D2W_OneTouchDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)OneTouchFunction},
	{ 'B', '\0', OPR_YES, D2W_SpeedDialMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SpeedDialFunction},
	{ 'C', '\0', OPR_YES, D2W_ProgramOneTouchMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)ProgramOnetouchFunction},
	{ 'D', '\0', OPR_YES, D2W_PollingMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)PollingFunction},
	{ 'E', '\0', OPR_YES, D2W_SecureMailMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SecureMailFunction},
	{ 'F', '\0', OPR_YES, D2W_DelayedCommandsMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DelayedCommandsFunction},
	{ 'G', '\0', OPR_YES, D2W_SetReportMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)SetReportFunction},
	{ 'H', '\0', OPR_YES, D2W_PrintGroupMode,		PrintGroupList,			NULL},
	{ 'I', '\0', OPR_YES, D2W_UserInstallMode,		UserInstallOperation,	NULL},
	{ 'J', '\0', OPR_YES, D2W_UserSettingsMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)UserSettingsFunction},
	{ 'K', '\0', OPR_YES, D2W_MessageMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)MessageFunction},
	{ 'L', '\0', OPR_YES, D2W_SetNumberOfPagesMode,	SetNumberOfPages,		NULL},
	{ 'M', '\0', OPR_YES, D2W_SetDepartmentMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)DepartmentCodeFunction},
 #if (PRO_BATCH_TX == ENABLE) /* #if追加 05/05/12 石橋正和 */
	{ 'N', '\0', OPR_YES, D2W_SetBatchTxMode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)BatchTxFunction},
 #endif
	{ 'O', '\0', OPR_YES, D2W_SecurityReceiveMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)SecurityRxFunction},
	{ 'P', '\0', OPR_YES, D2W_FcodeBoxMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)FcodeFunction},
 #if (PRO_RX_DOC_TRANSFER == ENABLE) && (!defined (KEISATSU))
	{ 'Q', '\0', OPR_YES, D2W_FaxWarpMode,			FunctionDummy,			(struct FUNCTION_TABLE_t *)FaxWarpFunction},
 #endif
 #if (PRO_NUMBER_DISPLAY == ENABLE)
	{ 'R', '\0', OPR_YES, D2W_NumberDisplayMode,	FunctionDummy,			(struct FUNCTION_TABLE_t *)NumberDisplayFunction},
 #endif
 #if (PRO_CLASS1 == ENABLE)	/* added by H.Hirao 1999/01/13 */
	{ 'S', '\0', OPR_YES, D2W_SetClass1Mode,		FunctionDummy,			(struct FUNCTION_TABLE_t *)Class1Function},
 #endif
	{'\0', '\0', OPR_NO,  NULL,						FunctionDummy,			NULL}
};
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* サービスファンクション */
/* ポプラとあんずをわけました 1997/10/02 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
CONST struct SERV_FUNCTION_t ServiceFunctionTable[] = {
	{ '0', MachineParameterMode},			/* ０	：マシーンパラメーターモード		*/
	{ '1', MemorySwitchMode},				/* １	：メモリースイッチモード			*/
	{ '2', ClearBackUpFile},				/* ２	：ユーザーデータクリア				*/
	{ '3', ClearAllBackUpFile},				/* ３	：オールラムクリア					*/
	{ '4', UniqSwitchMode},					/* ４	：機種固有スイッチモード			*/
	{ '5', T30MonitorPrintOperation},		/* ５	：Ｔ３０モニタープリント			*/
	{ '6', PrintMaintenance},				/* ６	：プリンタメンテナンス				*/
	{ '7', InvalidServiceFunction},			/* ７	：未使用							*/
	{ '8', FunctionListPrintOperation},		/* ８	：機能リストプリント				*/
	{ '9', ServiceFunctionSetting},			/* ９	：テストファンクション				*/
	{ 'A', PrintMemorySwList},				/* [01A]：パラメーターリストプリント		*/
	{ 'B', FactoryFunctionMode},			/* [02B]：工場ファンクション				*/
 #if (PRO_MODEM == R288F)
	{ 'C', R288F_LineFunctionMode},			/* [03C]：回線テスト						*//* 1999/10/13 Y.Murata */
 #else
	{ 'C', LineFunctionMode},				/* [03C]：回線テスト						*/
 #endif
	{ 'D', TeachingRingPattern},			/* [04D]：リングパターン自動検出			*/
 #if (PRO_FBS == ENABLE)
	{ 'E', SetMirrorCarrigeTransMode},		/* [05E]：ミラーキャリッジ輸送モードセット	*/
 #endif
	{ 'F', ConsumptionArticleOrderFunc},	/* [06F]：消耗品発注機能					*/
	{ 'G', ServicePrintSettingList},		/* [07G]：機器設定ﾘｽﾄﾌﾟﾘﾝﾄ(ｻｰﾋﾞｽﾌｧﾝｸｼｮﾝ用)	*/
	{ 'H', SF_LifeMonitorClear},			/* [08H]：ライフモニタクリア				*/
	{ 'I', ClearDRAM},						/* [09I]：ＤＲＡＭクリア					*/
 #if (PRO_MULTI_LINE == ENABLE)
	{ 'J', MultiLineFunctionMode},			/* [10J]：２回線用回線テスト				*/
 #endif
	{ 'K', SF_OptionDataInitial},			/* [11K]：オプションデータ初期化			*/
	{ 'L', ClearOrderData},					/* [12L]：消耗品発注データクリア			*/
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/12 by K.Okada */
 	{ 'M', InitEmailEngineBoard},			/* [13M]：E-Mailエンジンボード設定初期化	*/
 	{ 'N', SF_DataModemTonalTest},			/* [14N]：ロックウェルデータモデムPTTテスト	*/
 	{ 'O', SetIP_EchoRequest},				/* [15O]：IPパケットエコー要求				*/
 #endif
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
	{ 'P', SetLifeMonitorPasscode},			/* [16P]：ライフモニタパスコード			*/
 #endif
 #if (0)	/* ROM容量の関係でコメントにします 1998/03/03 T.Fukumoto */
	{ 'Z', EditLifeMonitor},				/* [26Z]：ライフモニタメンテナンス			*/
 #endif
	{0x61, SetMonitorSpeakerOnOff},			/* [33(]：モニタースピーカON/OFF			*/
	{0x62, MemoryDump},						/* [34)]：メモリダンプ						*/
	{NULL, InvalidServiceFunction}
};
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/10/02 Y.Matsukuma */
CONST struct SERV_FUNCTION_t ServiceFunctionTable[] = {
	{ '0', MachineParameterMode},			/* ０：マシーンパラメーターモード		*/
	{ '1', MemorySwitchMode},				/* １：メモリースイッチモード			*/
	{ '2', ClearBackUpFile},				/* ２：ユーザーデータクリア				*/
	{ '3', ClearAllBackUpFile},				/* ３：オールラムクリア					*/
	{ '4', UniqSwitchMode},					/* ４：機種固有スイッチモード			*/
	{ '5', T30MonitorPrintOperation},		/* ５：Ｔ３０モニタープリント			*/
	{ '6', InvalidServiceFunction},			/* ６：未使用							*/
	{ '7', InvalidServiceFunction},			/* ７：未使用							*/
	{ '8', FunctionListPrintOperation},		/* ８：機能リストプリント				*/
	{ '9', ServiceFunctionSetting},			/* ９：テストファンクション				*/
	{ 'A', PrintMemorySwList},				/* Ａ：パラメーターリストプリント		*/
	{ 'B', FactoryFunctionMode},			/* Ｂ：工場ファンクション				*/
	{ 'C', LineFunctionMode},				/* Ｃ：回線テスト						*/
	{ 'D', TeachingRingPattern},			/* Ｄ：リングパターン自動検出			*/
 #if (PRO_MULTI_LINE == ENABLE)
	{ 'E', MultiLineFunctionMode},			/* Ｅ：２回線用回線テスト				*/
 #endif
	{ 'F', ServiceReportPrintOperation},	/* Ｆ：サービスレポートプリント			*/
	{ 'G', ServicePrintSettingList},		/* Ｇ：機器設定ﾘｽﾄﾌﾟﾘﾝﾄ(ｻｰﾋﾞｽﾌｧﾝｸｼｮﾝ用) */
	{ 'H', SF_LifeMonitorClear},			/* Ｈ：ライフモニタクリア				*/
	{ 'I', ClearDRAM},						/* Ｉ：ＤＲＡＭクリア					*/
	{ 'K', SF_OptionDataInitial},			/* Ｋ：オプションデータ初期化			*/
	{ 'L', SetMonitorSpeakerOnOff},			/* Ｌ：モニタースピーカON/OFF			*/
	{ 'M', MemoryDump},						/* Ｍ：メモリダンプ						*/
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/12 by K.Okada */
 	{ 'N', InitEmailEngineBoard},			/* Ｎ：E-Mailエンジンボード設定初期化	*/
 	{ 'O', SF_DataModemTonalTest},			/* Ｏ：ロックウェルデータモデムPTTテスト*/
	{ 'P', SetIP_EchoRequest},				/* Ｐ：IPパケットのエコー要求			*/
 #endif
	{NULL, InvalidServiceFunction}
};
#endif	/* defined(ANZU_L) */

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/	/* Add By H.Fujimura 1998/12/28 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By H.Fujimura 1998/12/28 */ /* Add by Y.Kano 2003/07/11 */

CONST struct SERV_FUNCTION_t ServiceFunctionTable[] = {
	{ '0', MachineParameterMode},			/* ０	：マシーンパラメーターモード		*/
	{ '1', MemorySwitchMode},				/* １	：メモリースイッチモード			*/
	{ '2', ClearBackUpFile},				/* ２	：ユーザーデータクリア				*/
	{ '3', ClearAllBackUpFile},				/* ３	：オールラムクリア					*/
	{ '4', UniqSwitchMode},					/* ４	：機種固有スイッチモード			*/
	{ '5', T30MonitorPrintOperation},		/* ５	：Ｔ３０モニタープリント			*/
	{ '8', FunctionListPrintOperation},		/* ８	：機能リストプリント				*/
	{ '9', ServiceFunctionSetting},			/* ９	：テストファンクション				*/
	{ 'A', PrintMemorySwList},				/* [01A]：パラメーターリストプリント		*/
	{ 'B', FactoryFunctionMode},			/* [02B]：工場ファンクション				*/
 #if (PRO_MODEM == R288F)
	{ 'C', R288F_LineFunctionMode},			/* [03C]：回線テスト						*/
 #endif
	{ 'F', ConsumptionArticleOrderFunc},	/* [06F]：消耗品発注機能					*/
	{ 'G', ServicePrintSettingList},		/* [07G]：機器設定ﾘｽﾄﾌﾟﾘﾝﾄ(ｻｰﾋﾞｽﾌｧﾝｸｼｮﾝ用)	*/
	{ 'H', SF_LifeMonitorClear},			/* [08H]：ライフモニタクリア				*/
	{ 'I', ClearDRAM},						/* [09I]：ＤＲＡＭクリア					*/
	{ 'L', ClearOrderData},					/* [12L]：消耗品発注データクリア			*/
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/25 */
	{ 'Q', EditLifeMonitor},				/* [17Q]：ライフモニタメンテナンス			Add by Y.Kano 2003/11/11 */
	{ 'R', SF_LED_Test},					/* ＬＥＤテスト			*/ 
	{ 'S', SetMonitorSpeakerOnOff},			/* [19S]：モニタースピーカON/OFF			*/
	{ 'T', MemoryDump},						/* [20T]：メモリダンプ						*/
	{NULL, InvalidServiceFunction}
 #else
	{ 'S', SetMonitorSpeakerOnOff},			/* [19S]：モニタースピーカON/OFF			*/
	{ 'T', MemoryDump},						/* [20T]：メモリダンプ						*/
#if defined (KEISATSU) /* 警察FAX 05/12/12 石橋正和 */
	{ 'U', DisplayCommunicationSpeed},		/* [21U]：通信速度表示ON/OFF				*/
#endif
	{ 'Z', EditLifeMonitor},				/* [26Z]：ライフモニタメンテナンス			*/
  #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/10 */
	{ 0x5B, KeisatsuService},				/* 0x5B	：ケイデンサービス設定				*/
  #endif		/* End of (defined (KEISATSU)) */
	{NULL, InvalidServiceFunction}
 #endif /* end of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
};
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/10 */
CONST struct FUNCTION_TABLE_t KeisatsuServiceTable[] = {
	{   1, '\0', OPR_YES, D2W_SetS1Bypass,				SetS1Bypass,			NULL},	/* Ｓ１　バイパス					*/
	{   2, '\0', OPR_YES, D2W_ScrambleAvailable,		SetScrambleAvailable,	NULL},	/* スクランブル						*/
	{   3, '\0', OPR_YES, D2W_KeyLockOn,				SetKeyLockOn,			NULL},	/* キー　ロック						*/
	{   4, '\0', OPR_YES, D2W_SendLevel,				SetSendLevel,			NULL},	/* ソウシュツ　レベル				*/
	{   5, '\0', OPR_YES, D2W_DTMFSendLevel,			SetDTMFSendLevel,		NULL},	/* ＤＴＭＦ　ソウシュツ　レベル		*/
#if (1)
	{   6, '\0', OPR_YES, D2W_IsseiRingTimeout,			SetIsseiRingTimeout,	NULL},	/* イッセイ　メイドウ　カイスウ		*/
#else
	{   6, '\0', OPR_YES, D2W_IsseiRingCount,			SetIsseiRingCount,		NULL},	/* イッセイ　メイドウ　カイスウ		*/
#endif
	{   7, '\0', OPR_YES, D2W_IsseiAbility,				SetIsseiAbility,		NULL},	/* イッセイシレイ　ノウリョク		*/
	{   8, '\0', OPR_YES, D2W_IsseiTimeOut,				SetIsseiTimeOut,		NULL},	/* イッセイ　タイムアウト			*/
	{   9, '\0', OPR_YES, D2W_RemoteRxDialOne,			SetRemoteRxDialOne,		NULL},	/* リモート　ジュシン　ケタスウ		*/
	{  10, '\0', OPR_YES, D2W_KeidenRxPriority,			SetKeidenRxPriority,	NULL},	/* ケイデン　ユウセン　ジュシン		*/
	{  11, '\0', OPR_YES, D2W_FPGAVersion,				GetFPGAVersion,			NULL},
	{'\0', '\0', OPR_NO,  NULL,							FunctionDummy, 			NULL}
};
#endif		/* End of (defined (KEISATSU)) */

/* 親展ボックス登録オペレーション */
UBYTE (* CONST (SetSMailFunction[]))() = {
	(UBYTE (*)())SecureBoxInput,		/* ボックス番号入力		ENTER_SECURE_BOXNO			*/
	(UBYTE (*)())SecurePasscodeCheck,	/* パスコードチェック	CHECK_SECURE_PASSCODE		*/
	(UBYTE (*)())SecureNameInput,		/* 名前入力				ENTER_SECURE_BOXNAME		*/
	(UBYTE (*)())SecurePasscodeInput	/* パスコード入力		ENTER_SECURE_NEW_PASSCODE	*/
};
#if (PRO_F_CODE == ENABLE)
/* Ｆコードボックス登録オペレーション */
UBYTE (* CONST (SetFcodeBoxFunction[]))() = {
	(UBYTE (*)())SelectFcodeBoxNumber,	/* SELECT_FCODE_BOX_NO		*/
	(UBYTE (*)())CheckFcodePassCode,	/* CHECK_FCODE_PASS_CODE	*/
	(UBYTE (*)())SetFcodeBoxName,		/* ENTER_FCODE_BOX_NAME		*/
	(UBYTE (*)())SetFcodeSubAddress,	/* ENTER_FCODE_SUB			*/
	(UBYTE (*)())SetFcodePassword,		/* ENTER_FCODE_PWD			*/
	(UBYTE (*)())SelectFcodeBoxKind,	/* SELECT_FCODE_KIND		*/
	(UBYTE (*)())SetFcodeOption,		/* ENTER_FCODE_OPTION		*/
	(UBYTE (*)())SetFcodeHoldTime,		/* ENTER_FCODE_HOLDTIME		*/
 #if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	(UBYTE (*)())SetFcodeRelayBox,		/* ENTER_FCODE_RELAY_BOX	*/
 #endif
	(UBYTE (*)())SetFcodePassCode		/* ENTER_FCODE_PASS_CODE	*/
};
#endif

#if (PRO_CIPHER == ENABLE)
/* 暗号化機能キーブック登録オペレーション */
UBYTE (* CONST (SetCipherKeyBookFunction[]))() = {
	(UBYTE (*)())SelectCipherKeyBookNumber,		/* SELECT_CIPHER_KEY_BOOK_NO	*/
	(UBYTE (*)())CheckCipherKeyBookPassCode,	/* CHECK_CIPHER_KEY_PASSCODE	*/
	(UBYTE (*)())SetCipherKeyBookName,			/* ENTER_CIPHER_KEY_BOOK_NAME	*/
	(UBYTE (*)())SetCipherKey,					/* ENTER_CIPHER_KEY				*/
	(UBYTE (*)())SetCipherKeyClue,				/* ENTER_CIPHER_KEY_CLUE		*/
	(UBYTE (*)())SetCipherKeyBookPassCode		/* ENTER_CIPHER_KEY_PASSCODE	*/
};
#endif
/**********************************************************
 * セッティングデータの内、選択肢が３個以上あるものに関して
 * 選択肢の有効／無効を定義するテーブル.
 * 国による選択肢の違いを吸収するために作成 →　吸収しきれへんかも
 * ビット位置ー＞選択肢番号（EnterSettingStatus()中で操作する選択肢番号
 **********************************************************/
CONST UBYTE ValidSelectBitPatternTable[] = {

/*--------------------------------------------*
 * ０：回線タイプ  OPR_LINE_TYPE
 *--------------------------------------------*/
#if defined(USA) || defined(GBR) || defined(AUS) || defined(TWN) || defined(SGP) || defined(DEU) || defined(EC1) || defined(EUR)
	0
	| OPR_DIAL_10PPS
	& ~OPR_DIAL_20PPS
	| OPR_DIAL_TONE
#else
 #if defined(FRA)
	0
	& ~OPR_DIAL_10PPS
	& ~OPR_DIAL_20PPS
	| OPR_DIAL_TONE
 #else
	0
	| OPR_DIAL_10PPS
	| OPR_DIAL_20PPS
	| OPR_DIAL_TONE
 #endif
#endif
	,
/*--------------------------------------------*
 * １：スキャナ幅 OPR_SCAN_WITDH
 *--------------------------------------------*/
#if (PRO_SCAN_WIDTH == A4WIDTH)
	0
	| OPR_SCANNER_A4
	& ~OPR_SCANNER_B4
	& ~OPR_SCANNER_A3
#endif
#if (PRO_SCAN_WIDTH == B4WIDTH)/*ない*/
	0
	| OPR_SCANNER_A4
	| OPR_SCANNER_B4
	& ~OPR_SCANNER_A3
#endif
#if (PRO_SCAN_WIDTH == A3WIDTH) /*ない*/
	0
	| OPR_SCANNER_A4
	| OPR_SCANNER_B4
	| OPR_SCANNER_A3
#endif
	,
/*--------------------------------------------*
 * ２：優先モード OPR_PRIMARY_MODE
 *--------------------------------------------*/
	0
	| OPR_MODE_NORMAL
	| OPR_MODE_FINE
	| OPR_MODE_SFINE
	| OPR_MODE_GRAY
	,
/*--------------------------------------------*
 * ３：優先濃度  OPR_PRIMARY_CONTRAST
 *--------------------------------------------*/
	0
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
	| OPR_DENS_LIGHT
	| OPR_DENS_LITTLE_LIGHT
	| OPR_DENS_NORMAL
	| OPR_DENS_LITTLE_DARK
	| OPR_DENS_DARK
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

	| OPR_DENS_LIGHT
	& ~OPR_DENS_LITTLE_LIGHT
	| OPR_DENS_NORMAL
	& ~OPR_DENS_LITTLE_DARK
	| OPR_DENS_DARK
#endif
	,
/*--------------------------------------------*
 *４：受信モード  OPR_RECEIVE_MODE
 *--------------------------------------------*/
	0
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
 #if defined(USA)			/* added by S.Fukui Sep.10 '97*/
	| OPR_TEL_READY
	| OPR_FAX_READY
	& ~OPR_FAX_TEL_READY
	& ~OPR_TEL_FAX_READY
	& ~OPR_ANS_FAX_READY
 #else
	| OPR_TEL_READY
	| OPR_FAX_READY
	| OPR_FAX_TEL_READY
	| OPR_TEL_FAX_READY
	| OPR_ANS_FAX_READY
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
 #if defined(GBR) || defined(AUS) || defined(TWN) || defined(FRA) || defined(DEU) || defined(EC1) || defined(EC2) || defined(EC3) || defined(JPN)
	& ~OPR_TEL_READY
	| OPR_FAX_READY
	| OPR_FAX_TEL_READY
	| OPR_TEL_FAX_READY
	| OPR_ANS_FAX_READY
 #else
  #if defined(USA)
	& ~OPR_TEL_READY
	| OPR_FAX_READY
	| OPR_FAX_TEL_READY
	& ~OPR_TEL_FAX_READY
	| OPR_ANS_FAX_READY
  #else
	& ~OPR_TEL_READY
	| OPR_FAX_READY
	& ~OPR_FAXTEL_READY
	| OPR_TELFAX_READY
	| OPR_ANSFAX_READY
  #endif
 #endif
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

 #if defined(GBR) || defined(AUS) || defined(TWN) || defined(FRA) || defined(DEU) || defined(EC1) || defined(EC2) || defined(EC3) || defined(JPN)
	& ~OPR_TEL_READY
	| OPR_FAX_READY
	| OPR_FAX_TEL_READY
	| OPR_TEL_FAX_READY
	| OPR_ANS_FAX_READY
  #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* DIAL_INの追加 by Y.Kano 2003/08/26 */
    | OPR_DIAL_IN_READY
  #endif
 #else
  #if defined(USA)
	& ~OPR_TEL_READY
	| OPR_FAX_READY
	| OPR_FAX_TEL_READY
	& ~OPR_TEL_FAX_READY
	| OPR_ANS_FAX_READY
  #else
	& ~OPR_TEL_READY
	| OPR_FAX_READY
	| OPR_FAXTEL_READY
	| OPR_TELFAX_READY
	| OPR_ANSFAX_READY
  #endif
 #endif
#endif
	,
/*--------------------------------------------*
 *５：受信縮小率  OPR_RX_REDUCTION
 *--------------------------------------------*/
	0
#if (PRO_FIXED_REDUCTION == ENABLE)	/* Ｌ４００対応で固定縮小率無しの処理を追加 by K.Watanabe 1998/05/13 */
	| OPR_RX_REDUCTION_1
	| OPR_RX_REDUCTION_2
	| OPR_RX_REDUCTION_3
	| OPR_RX_REDUCTION_4
	| OPR_RX_REDUCTION_5
	| OPR_RX_REDUCTION_6
	& ~OPR_RX_REDUCTION_7
#else
	| OPR_RX_REDUCTION_1
	| OPR_RX_REDUCTION_2
	& ~OPR_RX_REDUCTION_3
	& ~OPR_RX_REDUCTION_4
	& ~OPR_RX_REDUCTION_5
	& ~OPR_RX_REDUCTION_6
	& ~OPR_RX_REDUCTION_7
#endif
	,
/*--------------------------------------------*
 *６：RS232Cスピード OPR_RS232C_SPEED
 *--------------------------------------------*/
	0
	| OPR_RS232C_SPEED_VARIABLE
	| OPR_RS232C_SPEED_600
	| OPR_RS232C_SPEED_1200
	| OPR_RS232C_SPEED_2400
	| OPR_RS232C_SPEED_4800
	| OPR_RS232C_SPEED_9600
	| OPR_RS232C_SPEED_19200
	,
/*--------------------------------------------*
 *７：RS232Cパリティ OPR_RS232C_PARITY
 *--------------------------------------------*/
	0
	| OPR_RS232C_PARITY_NONE
	| OPR_RS232C_PARITY_ODD
	| OPR_RS232C_PARITY_EVEN
	,
/*--------------------------------------------*
 *８：リングパターン OPR_RING_PATTERN
 *--------------------------------------------*/
	0
	| OPR_RING_PATTERN_1
	| OPR_RING_PATTERN_2
	| OPR_RING_PATTERN_3
	| OPR_RING_PATTERN_4
	| OPR_RING_PATTERN_5
	| OPR_RING_PATTERN_6
	| OPR_RING_PATTERN_7
	| OPR_RING_PATTERN_8
	,
/*--------------------------------------------*
 *９：コピー縮小率  OPR_COPY_REDUCTION
 *--------------------------------------------*/
	0
#if (PRO_FIXED_REDUCTION == ENABLE)	/* Ｌ４００対応で固定縮小率無しの処理を追加 by K.Watanabe 1998/05/13 */
	| OPR_COPY_FIXED_REDUCTION_1
	| OPR_COPY_FIXED_REDUCTION_2
	| OPR_COPY_FIXED_REDUCTION_3
	| OPR_COPY_FIXED_REDUCTION_4
	| OPR_COPY_FIXED_REDUCTION_5
	| OPR_COPY_FIXED_REDUCTION_6
	& ~OPR_COPY_FIXED_REDUCTION_7
#else
	| OPR_COPY_FIXED_REDUCTION_1
	| OPR_COPY_FIXED_REDUCTION_2
	& ~OPR_COPY_FIXED_REDUCTION_3
	& ~OPR_COPY_FIXED_REDUCTION_4
	& ~OPR_COPY_FIXED_REDUCTION_5
	& ~OPR_COPY_FIXED_REDUCTION_6
	& ~OPR_COPY_FIXED_REDUCTION_7
#endif
	,
/*--------------------------------------------*
 *１０：上段紙サイズ OPR_UPPER_PAPER
 *--------------------------------------------*/
/*#if defined(GBR) || defined(TWN) || defined(SGP) || defined(AUS) || defined(DEU) || defined(FRA)*/
#if defined(TWN) || defined(AUS)
 #if defined(TWN)
	/* 1998/01/07 Y.Murata
	 * タイで使用されている特殊F4紙（216x353mm、216x342mm）を対応するため
	 * リーガル設定で対応します
	*/
	/*-----------*/
	/** ＴＷＮ  **/
	/*-----------*/
	0
	& ~OPR_UPPER_SIZE_NONE
	| OPR_UPPER_SIZE_A4
	& ~OPR_UPPER_SIZE_B4
	& ~OPR_UPPER_SIZE_LETTER
	| OPR_UPPER_SIZE_LEGAL
	| OPR_UPPER_SIZE_F4
 #else
	/*-----------*/
	/** ＡＵＳ  **/
	/*-----------*/
	0
	& ~OPR_UPPER_SIZE_NONE
	| OPR_UPPER_SIZE_A4
	& ~OPR_UPPER_SIZE_B4
	& ~OPR_UPPER_SIZE_LETTER
	& ~OPR_UPPER_SIZE_LEGAL
	| OPR_UPPER_SIZE_F4
 #endif
#else
 #if defined(USA)
	/*-----------*/
	/** ＵＳＡ  **/
	/*-----------*/
	0
  #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/21 Y.Matsukuma */
	& ~OPR_UPPER_SIZE_NONE
	| OPR_UPPER_SIZE_A4
	& ~OPR_UPPER_SIZE_B4
	| OPR_UPPER_SIZE_LETTER
	| OPR_UPPER_SIZE_LEGAL
	& ~OPR_UPPER_SIZE_F4
  #else
	& ~OPR_UPPER_SIZE_NONE
	& ~OPR_UPPER_SIZE_A4
	& ~OPR_UPPER_SIZE_B4
	| OPR_UPPER_SIZE_LETTER
	| OPR_UPPER_SIZE_LEGAL
	& ~OPR_UPPER_SIZE_F4
  #endif
 #else
	/*-------------------*/
	/** ＪＰＮ、ＧＢＲ  **/
	/*-------------------*/
	0
	& ~OPR_UPPER_SIZE_NONE
	| OPR_UPPER_SIZE_A4
	& ~OPR_UPPER_SIZE_B4
	& ~OPR_UPPER_SIZE_LETTER
	& ~OPR_UPPER_SIZE_LEGAL
	& ~OPR_UPPER_SIZE_F4
 #endif
#endif
	,
/*--------------------------------------------*
 *１１：下段紙サイズ OPR_LOWER_PAPER
 *--------------------------------------------*/
	0
	| OPR_LOWER_SIZE_NONE
	& ~OPR_LOWER_SIZE_A4
	& ~OPR_LOWER_SIZE_B4
	| OPR_LOWER_SIZE_LETTER
	| OPR_LOWER_SIZE_LEGAL
	& ~OPR_LOWER_SIZE_F4
	,
/*--------------------------------------------*
 *１２：ＰＩＮアクセス OPR_PIN_MODE
 *--------------------------------------------*/
	0
	| OPR_PIN_ACCESS_OFF
	| OPR_PIN_ACCESS_MODE1
	| OPR_PIN_ACCESS_MODE2
	,
/*--------------------------------------------*
 *１３：ハーフトーン OPR_HALFTONE
 *--------------------------------------------*/
	0
	| OPR_HALFTONE_16_1
	| OPR_HALFTONE_16_2
	| OPR_HALFTONE_64_1
	| OPR_HALFTONE_64_2
	,
/*----------------------------------------------*
 *１４：ダイレクトメール防止 OPR_BLOCK_JUNK_FAX *
 *----------------------------------------------*/
	0
	| OPR_BLOCK_JUNK_FAX_OFF
	| OPR_BLOCK_JUNK_FAX_MODE1
	| OPR_BLOCK_JUNK_FAX_MODE2
	| OPR_BLOCK_JUNK_FAX_MODE3

#if (PRO_KEYPANEL == PANEL_ANZU_L)		/* 1998/06/03 Y.Murata ｱﾗﾑｺ特殊対応 LT,LG,A4対応 ARM_A4*/
	,
/*--------------------------------------------*
 *１５：上段紙サイズ OPR_UPPER_PAPER_ARM ｱﾗﾑｺ特殊対応 LT,LG,A4対応 ARM_A4
 *--------------------------------------------*/
	0
	& ~OPR_UPPER_SIZE_NONE
	| OPR_UPPER_SIZE_A4
	& ~OPR_UPPER_SIZE_B4
	| OPR_UPPER_SIZE_LETTER
	| OPR_UPPER_SIZE_LEGAL
	& ~OPR_UPPER_SIZE_F4
#endif

};

/***********************************************************************************************
 * セッティングデータの内、選択肢が９個以上あるものに関して選択肢の有効／無効を定義するテーブル
 * ValidSelectBitPatternTable[]では、ＰＣプリント用の上段紙サイズが対応できないために作成
 * ビット位置 → 選択肢番号（EnterSettingStatus()中で操作する選択肢番号）
 ***********************************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 1996/09/17 by K.Watanabe */
CONST UDWORD ValidSelectBitPatternTableLong[] = {

/*--------------------------------------------*
 *   ０：上段紙サイズ OPR_PCR_UPPER_PAPER
 *--------------------------------------------*/
/* 注）ValidSelectBitPatternTableLong[OPR_PCR_UPPER_PAPER]と、
**     DPR_PCR_SupportPaperSizeTable[][]で設定している
**     サポート記録紙サイズは同じでないといけません
*/
#if (PRO_PRINT_TYPE == LASER)
 #if defined(USA)
	0
	& ~OPR_PCR_MANUAL_SIZE_NONE		/* なし                   */
	& ~OPR_PCR_MANUAL_SIZE_A5		/* Ａ５縦                 */
	| OPR_PCR_MANUAL_SIZE_LT		/* レター縦               */
	| OPR_PCR_MANUAL_SIZE_A4		/* Ａ４縦                 */
	| OPR_PCR_MANUAL_SIZE_LG		/* リーガル縦             */
	& ~OPR_PCR_MANUAL_SIZE_B5R		/* Ｂ５横 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_B4		/* Ｂ４縦 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_A3		/* Ａ３縦                 */
	& ~OPR_PCR_MANUAL_SIZE_A4R		/* Ａ４横                 */
	& ~OPR_PCR_MANUAL_SIZE_LTR		/* レター横               */
	| OPR_PCR_MANUAL_SIZE_F4		/* Ｆ４縦                 */
	& ~OPR_PCR_MANUAL_SIZE_A5R		/* Ａ５横                 */
	| OPR_PCR_MANUAL_SIZE_POST		/* はがき縦               */
	& ~OPR_PCR_MANUAL_SIZE_LD		/* レジャー縦             */
	& ~OPR_PCR_MANUAL_SIZE_GLTR		/* ガバメント・レター横   */
	& ~OPR_PCR_MANUAL_SIZE_EXER		/* エグゼクティブ横       */
	& ~OPR_PCR_MANUAL_SIZE_INVR		/* インボイス横           */
	& ~OPR_PCR_MANUAL_SIZE_GLG		/* ガバメント・リーガル縦 */
	& ~OPR_PCR_MANUAL_SIZE_GLT		/* ガバメント・レター縦   */
	& ~OPR_PCR_MANUAL_SIZE_CARD		/* カードストック紙       */
	| OPR_PCR_MANUAL_SIZE_EXE		/* エグゼクティブ縦       */
	& ~OPR_PCR_MANUAL_SIZE_B5		/* Ｂ５縦 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_C5		/* Ｃ５縦                 */
	& ~OPR_PCR_MANUAL_SIZE_HLT		/* ハーフ・レター縦       */
	& ~OPR_PCR_MANUAL_SIZE_INV		/* インボイス縦           */
	& ~OPR_PCR_MANUAL_SIZE_B6		/* Ｂ６縦 ＪＩＳ          */
	| OPR_PCR_MANUAL_SIZE_DL		/* ＤＬ縦                 */
	| OPR_PCR_MANUAL_SIZE_CM10		/* コマーシャル１０縦     */
	& ~OPR_PCR_MANUAL_SIZE_A6		/* Ａ６縦                 */
	| OPR_PCR_MANUAL_SIZE_MNC		/* モナーク縦             */
	& ~OPR_PCR_MANUAL_SIZE_35		/* ３”×５”縦           */
	& ~OPR_PCR_MANUAL_SIZE_USER		/* 不定形紙               */
 #else
	0
	& ~OPR_PCR_MANUAL_SIZE_NONE		/* なし                   */
	& ~OPR_PCR_MANUAL_SIZE_A5		/* Ａ５縦                 */
	| OPR_PCR_MANUAL_SIZE_LT		/* レター縦               */
	| OPR_PCR_MANUAL_SIZE_A4		/* Ａ４縦                 */
	| OPR_PCR_MANUAL_SIZE_LG		/* リーガル縦             */
	& ~OPR_PCR_MANUAL_SIZE_B5R		/* Ｂ５横 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_B4		/* Ｂ４縦 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_A3		/* Ａ３縦                 */
	& ~OPR_PCR_MANUAL_SIZE_A4R		/* Ａ４横                 */
	& ~OPR_PCR_MANUAL_SIZE_LTR		/* レター横               */
	| OPR_PCR_MANUAL_SIZE_F4		/* Ｆ４縦                 */
	& ~OPR_PCR_MANUAL_SIZE_A5R		/* Ａ５横                 */
	| OPR_PCR_MANUAL_SIZE_POST		/* はがき縦               */
	& ~OPR_PCR_MANUAL_SIZE_LD		/* レジャー縦             */
	& ~OPR_PCR_MANUAL_SIZE_GLTR		/* ガバメント・レター横   */
	& ~OPR_PCR_MANUAL_SIZE_EXER		/* エグゼクティブ横       */
	& ~OPR_PCR_MANUAL_SIZE_INVR		/* インボイス横           */
	& ~OPR_PCR_MANUAL_SIZE_GLG		/* ガバメント・リーガル縦 */
	& ~OPR_PCR_MANUAL_SIZE_GLT		/* ガバメント・レター縦   */
	& ~OPR_PCR_MANUAL_SIZE_CARD		/* カードストック紙       */
	| OPR_PCR_MANUAL_SIZE_EXE		/* エグゼクティブ縦       */
	& ~OPR_PCR_MANUAL_SIZE_B5		/* Ｂ５縦 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_C5		/* Ｃ５縦                 */
	& ~OPR_PCR_MANUAL_SIZE_HLT		/* ハーフ・レター縦       */
	& ~OPR_PCR_MANUAL_SIZE_INV		/* インボイス縦           */
	& ~OPR_PCR_MANUAL_SIZE_B6		/* Ｂ６縦 ＪＩＳ          */
	| OPR_PCR_MANUAL_SIZE_DL		/* ＤＬ縦                 */
	| OPR_PCR_MANUAL_SIZE_CM10		/* コマーシャル１０縦     */
	& ~OPR_PCR_MANUAL_SIZE_A6		/* Ａ６縦                 */
	| OPR_PCR_MANUAL_SIZE_MNC		/* モナーク縦             */
	& ~OPR_PCR_MANUAL_SIZE_35		/* ３”×５”縦           */
	& ~OPR_PCR_MANUAL_SIZE_USER		/* 不定形紙               */
 #endif
#endif
#if (PRO_PRINT_TYPE == LED)
 #if defined(JPN)
	0
	& ~OPR_PCR_MANUAL_SIZE_NONE		/* なし                   */
	| OPR_PCR_MANUAL_SIZE_A5		/* Ａ５縦                 */
	& ~OPR_PCR_MANUAL_SIZE_LT		/* レター縦               */
	| OPR_PCR_MANUAL_SIZE_A4		/* Ａ４縦                 */
	& ~OPR_PCR_MANUAL_SIZE_LG		/* リーガル縦             */
	& ~OPR_PCR_MANUAL_SIZE_B5R		/* Ｂ５横 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_B4		/* Ｂ４縦 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_A3		/* Ａ３縦                 */
	& ~OPR_PCR_MANUAL_SIZE_A4R		/* Ａ４横                 */
	& ~OPR_PCR_MANUAL_SIZE_LTR		/* レター横               */
	& ~OPR_PCR_MANUAL_SIZE_F4		/* Ｆ４縦                 */
	| OPR_PCR_MANUAL_SIZE_A5R		/* Ａ５横                 */
	| OPR_PCR_MANUAL_SIZE_POST		/* はがき縦               */
	& ~OPR_PCR_MANUAL_SIZE_LD		/* レジャー縦             */
	& ~OPR_PCR_MANUAL_SIZE_GLTR		/* ガバメント・レター横   */
	& ~OPR_PCR_MANUAL_SIZE_EXER		/* エグゼクティブ横       */
	& ~OPR_PCR_MANUAL_SIZE_INVR		/* インボイス横           */
	& ~OPR_PCR_MANUAL_SIZE_GLG		/* ガバメント・リーガル縦 */
	& ~OPR_PCR_MANUAL_SIZE_GLT		/* ガバメント・レター縦   */
	& ~OPR_PCR_MANUAL_SIZE_CARD		/* カードストック紙       */
	& ~OPR_PCR_MANUAL_SIZE_EXE		/* エグゼクティブ縦       */
	| OPR_PCR_MANUAL_SIZE_B5		/* Ｂ５縦 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_C5		/* Ｃ５縦                 */
	& ~OPR_PCR_MANUAL_SIZE_HLT		/* ハーフ・レター縦       */
	& ~OPR_PCR_MANUAL_SIZE_INV		/* インボイス縦           */
	& ~OPR_PCR_MANUAL_SIZE_B6		/* Ｂ６縦 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_DL		/* ＤＬ縦                 */
	& ~OPR_PCR_MANUAL_SIZE_CM10		/* コマーシャル１０縦     */
	& ~OPR_PCR_MANUAL_SIZE_A6		/* Ａ６縦                 */
	& ~OPR_PCR_MANUAL_SIZE_MNC		/* モナーク縦             */
	& ~OPR_PCR_MANUAL_SIZE_35		/* ３”×５”縦           */
	& ~OPR_PCR_MANUAL_SIZE_USER		/* 不定形紙               */
 #else   		/* ＰＣプリントのサポート記録紙については日本／海外で仕様を分ける By S.Fukui Sep.25,1997 */
	0
	& ~OPR_PCR_MANUAL_SIZE_NONE		/* なし                   */
	| OPR_PCR_MANUAL_SIZE_A5		/* Ａ５縦                 */
	| OPR_PCR_MANUAL_SIZE_LT		/* レター縦               */
	| OPR_PCR_MANUAL_SIZE_A4		/* Ａ４縦                 */
	| OPR_PCR_MANUAL_SIZE_LG		/* リーガル縦             */
	&~OPR_PCR_MANUAL_SIZE_B5R		/* Ｂ５横 ＪＩＳ          */	/* 対応不可 By S.Fukui Apr.27,1998 */
	&~OPR_PCR_MANUAL_SIZE_B4		/* Ｂ４縦 ＪＩＳ          */	/* 対応不可 By S.Fukui Apr.27,1998 */
	& ~OPR_PCR_MANUAL_SIZE_A3		/* Ａ３縦                 */
	& ~OPR_PCR_MANUAL_SIZE_A4R		/* Ａ４横                 */
	& ~OPR_PCR_MANUAL_SIZE_LTR		/* レター横               */
	| OPR_PCR_MANUAL_SIZE_F4		/* Ｆ４縦                 */
	| OPR_PCR_MANUAL_SIZE_A5R		/* Ａ５横                 */
	| OPR_PCR_MANUAL_SIZE_POST		/* はがき縦               */
	& ~OPR_PCR_MANUAL_SIZE_LD		/* レジャー縦             */
	& ~OPR_PCR_MANUAL_SIZE_GLTR		/* ガバメント・レター横   */
	& ~OPR_PCR_MANUAL_SIZE_EXER		/* エグゼクティブ横       */
	| OPR_PCR_MANUAL_SIZE_HLTR		/* ハーフレター横         */  /* by honda 1997/10/08 インボイス横から改称 */
	& ~OPR_PCR_MANUAL_SIZE_GLG		/* ガバメント・リーガル縦 */
	& ~OPR_PCR_MANUAL_SIZE_GLT		/* ガバメント・レター縦   */
	& ~OPR_PCR_MANUAL_SIZE_CARD		/* カードストック紙       */
	| OPR_PCR_MANUAL_SIZE_EXE		/* エグゼクティブ縦       */
	& ~OPR_PCR_MANUAL_SIZE_B5		/* Ｂ５縦 ＪＩＳ          */
	& ~OPR_PCR_MANUAL_SIZE_C5		/* Ｃ５縦                 */
	& ~OPR_PCR_MANUAL_SIZE_HLT		/* ハーフ・レター縦       */
	& ~OPR_PCR_MANUAL_SIZE_INV		/* インボイス縦           */
	& ~OPR_PCR_MANUAL_SIZE_B6		/* Ｂ６縦 ＪＩＳ          */
	| OPR_PCR_MANUAL_SIZE_DL		/* ＤＬ縦                 */
	| OPR_PCR_MANUAL_SIZE_CM10		/* コマーシャル１０縦     */
	| OPR_PCR_MANUAL_SIZE_A6		/* Ａ６縦                 */
	| OPR_PCR_MANUAL_SIZE_MNC		/* モナーク縦             */
	& ~OPR_PCR_MANUAL_SIZE_35		/* ３”×５”縦           */
	& ~OPR_PCR_MANUAL_SIZE_USER		/* 不定形紙               */
 #endif
#endif
};
#endif

/******************************************
 * 各種ロムディップ
 ******************************************/

/* リングマスターパターン自動検出フラグ有効無効のスイッチ */
/* １：有効　０：無効 */
/* 1996/03/22 Eguchi */
CONST UBYTE	TeachingOperationEnable = 0;

/* ワンタッチ・プログラムワンタッチ自動スタート有効無効のスイッチ */
/* 1996/04/15 Eguchi */
/* １：自動スタート（ワンタッチ）　０：スタートキー入力が必要(ツータッチ）*/
#if defined(JPN)
CONST UBYTE	IsOnetouchAutoStart = FALSE;
#else
CONST UBYTE	IsOnetouchAutoStart = TRUE;
#endif

/* 通信中の通信予約でスタートキーを２回押す／押さないのスイッチ */
/* １：２回押す　０：２回押さない */
/* 1996/07/18 Eguchi */
CONST UBYTE	PushStartTwiceFaxCom = 0;

#if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
 #if defined(JPN)
/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/11/20
*             TYPE:  struct
*      VAR TO HOLD:
*      DESCRIPTION:  ローマ字カナ変換テーブル
************************************************************************/
/* SHCのコンパイラーでは半角カナのキャラクター定義がコンパイルできないため、文字列の定義に変更します */
/* CONST UBYTE ROMA_KATAKANA_Table[270][6] = { */
/*	{'A',' ',' ','ｱ','\0','\0'},{'B','A',' ','ﾊ','ﾞ','\0'},*/
CONST struct ROMAJI_KATAKANA_TABLE_t RomajiToKatakanaTable[OPR_ROMAJI_KANA_TABLE_MAX] = {	/* 270 * (4 + 4) = 2160 byte */
	{"A  ", "ｱ\0\0"}, {"BA ", "ﾊﾞ\0" }, {"BE ", "ﾍﾞ\0" }, {"BI ", "ﾋﾞ\0" }, {"BO ", "ﾎﾞ\0" },
	{"BU ", "ﾌﾞ\0" }, {"BYA", "ﾋﾞｬ"  }, {"BYE", "ﾋﾞｪ"  }, {"BYI", "ﾋﾞｨ"  }, {"BYO", "ﾋﾞｮ"  },
	{"BYU", "ﾋﾞｭ"  }, {"CA ", "ｶ\0\0"}, {"CE ", "ｾ\0\0"}, {"CHA", "ﾁｬ\0" }, {"CHE", "ﾁｪ\0" },
	{"CHI", "ﾁ\0\0"}, {"CHO", "ﾁｮ\0" }, {"CHU", "ﾁｭ\0" }, {"CI ", "ｼ\0\0"}, {"CO ", "ｺ\0\0"},
	{"CU ", "ｸ\0\0"}, {"CYA", "ﾁｬ\0" }, {"CYE", "ﾁｪ\0" }, {"CYI", "ﾁｨ\0" }, {"CYO", "ﾁｮ\0" },
	{"CYU", "ﾁｭ\0" }, {"DA ", "ﾀﾞ\0" }, {"DE ", "ﾃﾞ\0" }, {"DHA", "ﾃﾞｬ"  }, {"DHE", "ﾃﾞｪ"  },
	{"DHI", "ﾃﾞｨ"  }, {"DHO", "ﾃﾞｮ"  }, {"DHU", "ﾃﾞｭ"  }, {"DI ", "ﾁﾞ\0" }, {"DO ", "ﾄﾞ\0" },
	{"DU ", "ﾂﾞ\0" }, {"DWA", "ﾄﾞｧ"  }, {"DWE", "ﾄﾞｪ"  }, {"DWI", "ﾄﾞｨ"  }, {"DWO", "ﾄﾞｫ"  },
	{"DWU", "ﾄﾞｩ"  }, {"DYA", "ﾁﾞｬ"  }, {"DYE", "ﾁﾞｪ"  }, {"DYI", "ﾁﾞｨ"  }, {"DYO", "ﾁﾞｮ"  },
	{"DYU", "ﾁﾞｭ"  }, {"E  ", "ｴ\0\0"}, {"FA ", "ﾌｧ\0" }, {"FE ", "ﾌｪ\0" }, {"FI ", "ﾌｨ\0" },
	{"FO ", "ﾌｫ\0" }, {"FU ", "ﾌ\0\0"}, {"FWA", "ﾌｧ\0" }, {"FWE", "ﾌｪ\0" }, {"FWI", "ﾌｨ\0" },
	{"FWO", "ﾌｫ\0" }, {"FWU", "ﾌｩ\0" }, {"FYA", "ﾌｬ\0" }, {"FYE", "ﾌｪ\0" }, {"FYI", "ﾌｨ\0" },
	{"FYO", "ﾌｮ\0" }, {"FYU", "ﾌｭ\0" }, {"GA ", "ｶﾞ\0" }, {"GE ", "ｹﾞ\0" }, {"GI ", "ｷﾞ\0" },
	{"GO ", "ｺﾞ\0" }, {"GU ", "ｸﾞ\0" }, {"GWA", "ｸﾞｧ"  }, {"GWE", "ｸﾞｪ"  }, {"GWI", "ｸﾞｨ"  },
	{"GWO", "ｸﾞｫ"  }, {"GWU", "ｸﾞｩ"  }, {"GYA", "ｷﾞｬ"  }, {"GYE", "ｷﾞｪ"  }, {"GYI", "ｷﾞｨ"  },
	{"GYO", "ｷﾞｮ"  }, {"GYU", "ｷﾞｭ"  }, {"HA ", "ﾊ\0\0"}, {"HE ", "ﾍ\0\0"}, {"HI ", "ﾋ\0\0"},
	{"HO ", "ﾎ\0\0"}, {"HU ", "ﾌ\0\0"}, {"HYA", "ﾋｬ\0" }, {"HYE", "ﾋｪ\0" }, {"HYI", "ﾋｨ\0" },
	{"HYO", "ﾋｮ\0" }, {"HYU", "ﾋｭ\0" }, {"I  ", "ｲ\0\0"}, {"JA ", "ｼﾞｬ"  }, {"JE ", "ｼﾞｪ"  },
	{"JI ", "ｼﾞ\0" }, {"JO ", "ｼﾞｮ"  }, {"JU ", "ｼﾞｭ"  }, {"JYA", "ｼﾞｬ"  }, {"JYE", "ｼﾞｪ"  },
	{"JYI", "ｼﾞｨ"  }, {"JYO", "ｼﾞｮ"  }, {"JYU", "ｼﾞｭ"  }, {"KA ", "ｶ\0\0"}, {"KE ", "ｹ\0\0"},
	{"KI ", "ｷ\0\0"}, {"KO ", "ｺ\0\0"}, {"KU ", "ｸ\0\0"}, {"KYA", "ｷｬ\0" }, {"KYE", "ｷｪ\0" },
	{"KYI", "ｷｨ\0" }, {"KYO", "ｷｮ\0" }, {"KYU", "ｷｭ\0" }, {"LA ", "ｧ\0\0"}, {"LE ", "ｪ\0\0"},
	{"LI ", "ｨ\0\0"}, {"LO ", "ｫ\0\0"}, {"LTU", "ｯ\0\0"}, {"LU ", "ｩ\0\0"}, {"LYA", "ｬ\0\0"},
	{"LYE", "ｪ\0\0"}, {"LYI", "ｨ\0\0"}, {"LYO", "ｮ\0\0"}, {"LYU", "ｭ\0\0"}, {"MA ", "ﾏ\0\0"},
	{"ME ", "ﾒ\0\0"}, {"MI ", "ﾐ\0\0"}, {"MO ", "ﾓ\0\0"}, {"MU ", "ﾑ\0\0"}, {"MYA", "ﾐｬ\0" },
	{"MYE", "ﾐｪ\0" }, {"MYI", "ﾐｨ\0" }, {"MYO", "ﾐｮ\0" }, {"MYU", "ﾐｭ\0" }, {"N\' ", "ﾝ\0\0"},
	{"NA ", "ﾅ\0\0"}, {"NE ", "ﾈ\0\0"}, {"NI ", "ﾆ\0\0"}, {"NN ", "ﾝ\0\0"}, {"NO ", "ﾉ\0\0"},
	{"NU ", "ﾇ\0\0"}, {"NYA", "ﾆｬ\0" }, {"NYE", "ﾆｪ\0" }, {"NYI", "ﾆｨ\0" }, {"NYO", "ﾆｮ\0" },
	{"NYU", "ﾆｭ\0" }, {"O  ", "ｵ\0\0"}, {"PA ", "ﾊﾟ\0" }, {"PE ", "ﾍﾟ\0" }, {"PI ", "ﾋﾟ\0" },
	{"PO ", "ﾎﾟ\0" }, {"PU ", "ﾌﾟ\0" }, {"PYA", "ﾋﾟｬ"  }, {"PYE", "ﾋﾟｪ"  }, {"PYI", "ﾋﾟｨ"  },
	{"PYO", "ﾋﾟｮ"  }, {"PYU", "ﾋﾟｭ"  }, {"QA ", "ｸｧ\0" }, {"QE ", "ｸｪ\0" }, {"QI ", "ｸｨ\0" },
	{"QO ", "ｸｫ\0" }, {"QU ", "ｸ\0\0"}, {"QWA", "ｸｧ\0" }, {"QWE", "ｸｪ\0" }, {"QWI", "ｸｨ\0" },
	{"QWO", "ｸｫ\0" }, {"QWU", "ｸｩ\0" }, {"QYA", "ｸｬ\0" }, {"QYE", "ｸｪ\0" }, {"QYI", "ｸｨ\0" },
	{"QYO", "ｸｮ\0" }, {"QYU", "ｸｭ\0" }, {"RA ", "ﾗ\0\0"}, {"RE ", "ﾚ\0\0"}, {"RI ", "ﾘ\0\0"},
	{"RO ", "ﾛ\0\0"}, {"RU ", "ﾙ\0\0"}, {"RYA", "ﾘｬ\0" }, {"RYE", "ﾘｪ\0" }, {"RYI", "ﾘｨ\0" },
	{"RYO", "ﾘｮ\0" }, {"RYU", "ﾘｭ\0" }, {"SA ", "ｻ\0\0"}, {"SE ", "ｾ\0\0"}, {"SHA", "ｼｬ\0" },
	{"SHE", "ｼｪ\0" }, {"SHI", "ｼ\0\0"}, {"SHO", "ｼｮ\0" }, {"SHU", "ｼｭ\0" }, {"SI ", "ｼ\0\0"},
	{"SO ", "ｿ\0\0"}, {"SU ", "ｽ\0\0"}, {"SWA", "ｽｧ\0" }, {"SWE", "ｽｪ\0" }, {"SWI", "ｽｨ\0" },
	{"SWO", "ｽｫ\0" }, {"SWU", "ｽｩ\0" }, {"SYA", "ｼｬ\0" }, {"SYE", "ｼｪ\0" }, {"SYI", "ｼｨ\0" },
	{"SYO", "ｼｮ\0" }, {"SYU", "ｼｭ\0" }, {"TA ", "ﾀ\0\0"}, {"TE ", "ﾃ\0\0"}, {"THA", "ﾃｬ\0" },
	{"THE", "ﾃｪ\0" }, {"THI", "ﾃｨ\0" }, {"THO", "ﾃｮ\0" }, {"THU", "ﾃｭ\0" }, {"TI ", "ﾁ\0\0"},
	{"TO ", "ﾄ\0\0"}, {"TSA", "ﾂｧ\0" }, {"TSE", "ﾂｪ\0" }, {"TSI", "ﾂｨ\0" }, {"TSO", "ﾂｫ\0" },
	{"TSU", "ﾂ\0\0"}, {"TU ", "ﾂ\0\0"}, {"TWA", "ﾄｧ\0" }, {"TWE", "ﾄｪ\0" }, {"TWI", "ﾄｨ\0" },
	{"TWO", "ﾄｫ\0" }, {"TWU", "ﾄｩ\0" }, {"TYA", "ﾁｬ\0" }, {"TYE", "ﾁｪ\0" }, {"TYI", "ﾁｨ\0" },
	{"TYO", "ﾁｮ\0" }, {"TYU", "ﾁｭ\0" }, {"U  ", "ｳ\0\0"}, {"VA ", "ｳﾞｧ"  }, {"VE ", "ｳﾞｪ"  },
	{"VI ", "ｳﾞｨ"  }, {"VO ", "ｳﾞｫ"  }, {"VU ", "ｳﾞ\0" }, {"VYA", "ｳﾞｬ"  }, {"VYE", "ｳﾞｪ"  },
	{"VYI", "ｳﾞｨ"  }, {"VYO", "ｳﾞｮ"  }, {"VYU", "ｳﾞｭ"  }, {"WA ", "ﾜ\0\0"}, {"WE ", "ｳｪ\0" },
	{"WHA", "ｳｧ\0" }, {"WHE", "ｳｪ\0" }, {"WHI", "ｳｨ\0" }, {"WHO", "ｳｫ\0" }, {"WHU", "ｳ\0\0"},
	{"WI ", "ｳｨ\0" }, {"WO ", "ｦ\0\0"}, {"WU ", "ｳ\0\0"}, {"XA ", "ｧ\0\0"}, {"XE ", "ｪ\0\0"},
	{"XI ", "ｨ\0\0"}, {"XN ", "ﾝ\0\0"}, {"XO ", "ｫ\0\0"}, {"XTU", "ｯ\0\0"}, {"XU ", "ｩ\0\0"},
	{"XYA", "ｬ\0\0"}, {"XYE", "ｪ\0\0"}, {"XYI", "ｨ\0\0"}, {"XYO", "ｮ\0\0"}, {"XYU", "ｭ\0\0"},
	{"YA ", "ﾔ\0\0"}, {"YE ", "ｲｪ\0" }, {"YI ", "ｲ\0\0"}, {"YO ", "ﾖ\0\0"}, {"YU ", "ﾕ\0\0"},
	{"ZA ", "ｻﾞ\0" }, {"ZE ", "ｾﾞ\0" }, {"ZI ", "ｼﾞ\0" }, {"ZO ", "ｿﾞ\0" }, {"ZU ", "ｽﾞ\0" },
	{"ZYA", "ｼﾞｬ"  }, {"ZYE", "ｼﾞｪ"  }, {"ZYI", "ｼﾞｨ"  }, {"ZYO", "ｼﾞｮ"  }, {"ZYU", "ｼﾞｭ"  }
};

/************************************************************************
*               BY:
*             DATE:
*             TYPE:  CONST
*      VAR TO HOLD:
*      DESCRIPTION:  ＣＧ　ＲＡＭテーブル（ファクス待機日付表示用）
*          COMMENT:  有効範囲は右上基準の７(縦)ｘ５(横)です
************************************************************************/
CONST UBYTE CG_RamTableFaxReadyKanji[LCD_SPECIAL_CHARACTER_MAX][LCD_CGRAM_TABLE_MAX] = {

	/* ０：日 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x1F, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x1F, 0x00},

	/* １：月 */
	/* 0 0 0 0 1 1 1 1 ---> 0x0F */
	/* 0 0 0 0 1 0 0 1 ---> 0x09 */
	/* 0 0 0 0 1 1 1 1 ---> 0x0F */
	/* 0 0 0 0 1 0 0 1 ---> 0x09 */
	/* 0 0 0 0 1 1 1 1 ---> 0x0F */
	/* 0 0 0 0 1 0 0 1 ---> 0x09 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x0F, 0x09, 0x0F, 0x09, 0x0F, 0x09, 0x11, 0x00},

	/* ２：火 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 1 0 1 0 1 ---> 0x15 */
	/* 0 0 0 1 0 1 0 1 ---> 0x15 */
	/* 0 0 0 1 0 1 0 1 ---> 0x15 */
	/* 0 0 0 0 0 1 0 1 ---> 0x04 */
	/* 0 0 0 0 1 0 1 0 ---> 0x0A */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x04, 0x15, 0x15, 0x15, 0x04, 0x0A, 0x11, 0x00},

	/* ３：水 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 1 ---> 0x05 */
	/* 0 0 0 1 1 1 1 0 ---> 0x1E */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 1 0 1 0 1 ---> 0x15 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x04, 0x05, 0x1E, 0x04, 0x0E, 0x15, 0x04, 0x00},

	/* ４：木 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 1 0 1 0 1 ---> 0x15 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x04, 0x04, 0x1F, 0x04, 0x0E, 0x15, 0x04, 0x00},

	/* ５：金 */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 1 0 1 0 1 ---> 0x15 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x0E, 0x11, 0x0E, 0x04, 0x0E, 0x15, 0x1F, 0x00},

	/* ６：土 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x04, 0x04, 0x0E, 0x04, 0x04, 0x04, 0x1F, 0x00},

	/* ７：年 */
	/* 0 0 0 0 1 0 0 0 ---> 0x08 */
	/* 0 0 0 0 1 1 1 1 ---> 0x0F */
	/* 0 0 0 1 0 0 1 0 ---> 0x12 */
	/* 0 0 0 0 1 1 1 1 ---> 0x0F */
	/* 0 0 0 0 1 0 1 0 ---> 0x0A */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 0 0 1 0 ---> 0x02 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x08, 0x0F, 0x12, 0x0F, 0x0A, 0x1F, 0x02, 0x00}
};
 #endif	/* (JPN) */

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/12/05
*             TYPE:  CONST
*      VAR TO HOLD:
*      DESCRIPTION:  ＣＧ　ＲＡＭテーブル（コピーモード原稿濃度・縦原稿表示用）
*          COMMENT:  有効範囲は右上基準の７(縦)ｘ５(横)です
************************************************************************/
CONST UBYTE CG_RamTableCopyModeDensity[LCD_SPECIAL_CHARACTER_MAX][LCD_CGRAM_TABLE_MAX] = {

	/* ０：コピー濃度左端を表す */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 1 1 0 ---> 0x06 */
	/* 0 0 0 0 1 0 1 0 ---> 0x0A */
	/* 0 0 0 1 0 0 1 0 ---> 0x12 */
	/* 0 0 0 0 1 0 1 0 ---> 0x0A */
	/* 0 0 0 0 0 1 1 0 ---> 0x06 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x00, 0x06, 0x0A, 0x12, 0x0A, 0x06, 0x00, 0x00},

	/* １：コピー濃度の薄く，やや濃くで使用 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 1 0 0 0 0 ---> 0x10 */
	/* 0 0 0 1 0 0 0 0 ---> 0x10 */
	/* 0 0 0 1 0 0 0 0 ---> 0x10 */
	/* 0 0 0 1 0 0 0 0 ---> 0x10 */
	/* 0 0 0 1 0 0 0 0 ---> 0x10 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00},

	/* ２：コピー濃度のやや薄く以上で使用 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00},

	/* ３：コピー濃度の普通以上で使用 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00},

	/* ４：コピー濃度右端を表す */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 1 1 0 0 ---> 0x0C */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 0 1 1 1 1 ---> 0x0F */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 0 1 1 0 0 ---> 0x0C */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x00, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x00, 0x00},

	/* ５：縦原稿 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 1 1 1 ---> 0x17 */
	/* 0 0 0 1 0 1 1 0 ---> 0x16 */
	/* 0 0 0 1 1 1 0 0 ---> 0x1C */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x1F, 0x11, 0x11, 0x11, 0x17, 0x16, 0x1C, 0x00},

 #if (0)
	/* ６：次原稿を表す（未使用：次原稿を表している事が、わかりにくいと言う事で、結局はﾜｰﾃﾞｨﾝｸﾞで代用しています） */
	/* 0 0 0 1 1 1 1 0 ---> 0x1E */
	/* 0 0 0 1 0 0 1 1 ---> 0x13 */
	/* 0 0 0 1 0 0 1 1 ---> 0x13 */
	/* 0 0 0 1 0 0 1 1 ---> 0x13 */
	/* 0 0 0 1 0 0 1 1 ---> 0x13 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 1 1 1 1 ---> 0x0F */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x1E, 0x13, 0x13, 0x13, 0x13, 0x1F, 0x0F, 0x00},
 #endif

	/* ６：暗号化進行度表示（未処理部分） */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00},

	/* ７：暗号化進行度表示（処理部分） */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00}
};

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/12/05
*             TYPE:  CONST
*      VAR TO HOLD:
*      DESCRIPTION:  ＣＧ　ＲＡＭテーブル（濃度・ボリューム設定用）
*          COMMENT:  有効範囲は右上基準の７(縦)ｘ５(横)です
************************************************************************/
CONST UBYTE CG_RamTableDensityVolumeSet[LCD_SPECIAL_CHARACTER_MAX][LCD_CGRAM_TABLE_MAX] = {

	/* ０：濃度左端を表す */
	/* 0 0 0 0 0 0 1 1 ---> 0x03 */
	/* 0 0 0 0 0 1 0 1 ---> 0x05 */
	/* 0 0 0 0 1 0 0 1 ---> 0x09 */
	/* 0 0 0 1 0 0 0 1 ---> 0x11 */
	/* 0 0 0 0 1 0 0 1 ---> 0x09 */
	/* 0 0 0 0 0 1 0 1 ---> 0x05 */
	/* 0 0 0 0 0 0 1 1 ---> 0x03 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x03, 0x05, 0x09, 0x11, 0x09, 0x05, 0x03, 0x00},

	/* １：濃度右端を表す */
	/* 0 0 0 1 1 0 0 0 ---> 0x18 */
	/* 0 0 0 1 1 1 0 0 ---> 0x1C */
	/* 0 0 0 1 1 1 1 0 ---> 0x1E */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 0 ---> 0x1E */
	/* 0 0 0 1 1 1 0 0 ---> 0x1C */
	/* 0 0 0 1 1 0 0 0 ---> 0x18 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x18, 0x1C, 0x1E, 0x1F, 0x1E, 0x1C, 0x18, 0x00},

	/* ２：濃度の薄く，やや薄く，やや濃く，濃くを表します */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00},

	/* ３：濃度の普通を表します */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 1 0 0 ---> 0x04 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x00, 0x00, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00},

	/* ４：濃度の設定値を表します */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 0 1 1 1 0 ---> 0x0E */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x00, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x00},

	/* ５：ボリューム（小）の設定値を表します */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x00},

	/* ６：ボリューム（中）の設定値を表します */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00},

	/* ７：ボリューム（大）の設定値を表します */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 1 1 1 1 1 ---> 0x1F */
	/* 0 0 0 0 0 0 0 0 ---> 0x00 */
	{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00}
};
#endif	/* (PRO_ANK_TO_KANJI == DISABLE) */

#if (PRO_COPY_FAX_MODE == ENABLE)
/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/03/07
*             TYPE:  CONST struct
*      VAR TO HOLD:
*      DESCRIPTION:  手差し記録紙サイズ選択用テーブル
************************************************************************/
 #if defined(JPN)									/* Modified by S.Fukui Oct.16,1997 */
CONST struct OPR_MANUAL_PAPER_TABLE_t OPR_SelectManualPaperTable[] = {
/*	{ 手差し記録紙サイズ, ＯＨＰモード(0:記録紙, 1:OHP) }	*/
	{ SYS_A4_PAPER,		0 },	/* Ａ４縦					*/
	{ SYS_A5R_PAPER,	0 },	/* Ａ５横					*/
	{ SYS_A5_PAPER,		0 },	/* Ａ５縦					*/
	{ SYS_B5_PAPER,		0 },	/* Ｂ５縦 ＪＩＳ			*/
	{ SYS_A4_PAPER,		1 },	/* ＯＨＰ（Ａ４縦）			*/
	{ SYS_POST_PAPER,	0 },	/* はがき縦					*/
	{ SYS_NO_PAPER,		0 }		/* 記録紙なし				*/
};
 #elif defined(USA)
CONST struct OPR_MANUAL_PAPER_TABLE_t OPR_SelectManualPaperTable[] = {
/*	{ 手差し記録紙サイズ, ＯＨＰモード(0:記録紙, 1:OHP) }	*/
	{ SYS_LT_PAPER,		0 },	/* レター縦					*/
	{ SYS_LG_PAPER,		0 },	/* リーガル縦				*/
	{ SYS_HLTR_PAPER,	0 },	/* ハーフレター横			*/
	{ SYS_LT_PAPER,		1 },	/* ＯＨＰ（レター縦）		*/
	{ SYS_NO_PAPER,		0 }		/* 記録紙なし				*/
};
/* #elif defined(GBR) By Y.Suzuki 1998/08/24*/
 #elif defined(GBR) || defined(DEU) || defined(FRA) || defined(EC1)
 /* ﾖｰﾛｯﾊﾟ向けで仕様を統一する */
CONST struct OPR_MANUAL_PAPER_TABLE_t OPR_SelectManualPaperTable[] = {
/*	{ 手差し記録紙サイズ, ＯＨＰモード(0:記録紙, 1:OHP) }	*/
	{ SYS_A4_PAPER,		0 },	/* Ａ４縦					*/
	{ SYS_A5R_PAPER,	0 },	/* Ａ５横					*/
	{ SYS_A5_PAPER,		0 },	/* Ａ５縦					*/
	{ SYS_B5_PAPER,		0 },	/* Ｂ５縦 ＪＩＳ			*/
	{ SYS_A4_PAPER,		1 },	/* ＯＨＰ（Ａ４縦）			*/
	{ SYS_NO_PAPER,		0 }		/* 記録紙なし				*/
};
 #else  /* (JPN),(USA),(GBR) 以外  POPLAR_B AUS bythonda1998/05/09 */
CONST struct OPR_MANUAL_PAPER_TABLE_t OPR_SelectManualPaperTable[] = {
/*	{ 手差し記録紙サイズ, ＯＨＰモード(0:記録紙, 1:OHP) }	*/
	{ SYS_A4_PAPER,		0 },	/* Ａ４縦					*/
	{ SYS_A5R_PAPER,	0 },	/* Ａ５横					*/
	{ SYS_A5_PAPER,		0 },	/* Ａ５縦					*/
	{ SYS_B5_PAPER,		0 },	/* Ｂ５縦 ＪＩＳ			*/
	{ SYS_F4_PAPER,		0 },	/* Ｆ４縦					*//* AUS bythonda1998/05/09 */
	{ SYS_A4_PAPER,		1 },	/* ＯＨＰ（Ａ４縦）			*/
	{ SYS_NO_PAPER,		0 }		/* 記録紙なし				*/
};
 #endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/03/10
*             TYPE:  CONST struct
*      VAR TO HOLD:
*      DESCRIPTION:  コピー固定倍率テーブル
*          COMMENT:  固定倍率のそれぞれのテーブルの最後のデータをNULLで
*                    定義していたが、紙サイズの先頭のdefine値が０で同じ
*                    値のため、テーブルの最後の判断ができないので、最後
*                    のデータは0xFF(SYS_NO_PAPER)で定義します
************************************************************************/
 #if defined(USA)	/* ＵＳＡ仕様  By S.Fukui Oct.22,1997 */

/* ５０％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_50[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_A3_PAPER,		SYS_A5_PAPER  },
  #if (0) /* 本当はﾊｶﾞｷに対する倍率ではなくA6に対してなので、実際は多少違いがあるので表示を止めます by K.Watanabe 1997/11/11 */
//	{ SYS_A4_PAPER,		SYS_POST_PAPER},
  #endif
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* ６４％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_64[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_LD_PAPER,		SYS_LT_PAPER  },
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* ７８％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_78[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_LG_PAPER,		SYS_LT_PAPER  },
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

  #if (0)
/* ９３％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_93[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_A4_PAPER,		SYS_LT_PAPER  },
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};
  #endif

/* １００％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_100[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_A5_PAPER,		SYS_A5_PAPER  },
	{ SYS_LT_PAPER,		SYS_LT_PAPER  },
	{ SYS_A4_PAPER,		SYS_A4_PAPER  },
	{ SYS_LG_PAPER,		SYS_LG_PAPER  },
	{ SYS_B5R_PAPER,	SYS_B5R_PAPER },
	{ SYS_B4_PAPER,		SYS_B4_PAPER  },
	{ SYS_F4_PAPER,		SYS_F4_PAPER  },
	{ SYS_A5R_PAPER,	SYS_A5R_PAPER },
	{ SYS_POST_PAPER,	SYS_POST_PAPER},
	{ SYS_B5_PAPER,		SYS_B5_PAPER  },
	{ SYS_HLTR_PAPER,	SYS_HLTR_PAPER},                                 /* added by honda 1997/10/04 */
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

  #if (0)
/* １２１％用テーブル */ /* 記録紙にレジャーがないので使用しません by S.Fukui Oct.22,1997 */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_121[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_A4_PAPER,		SYS_B4_PAPER  },
	{ SYS_A5_PAPER,		SYS_B5_PAPER  },
	{ SYS_A5R_PAPER,	SYS_B5R_PAPER },
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};
  #endif

/* １２９％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_129[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_HLT_PAPER,	SYS_LT_PAPER  },		/* By S.Fukui Jan.21,1998 */
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* ２００％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_200[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
  #if (0) /* 本当はﾊｶﾞｷに対する倍率ではなくA6に対してなので、実際は多少違いがあるので表示を止めます by K.Watanabe 1997/11/11 */
//	{ SYS_POST_PAPER,	SYS_A4_PAPER  },
  #endif
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* 固定倍率　拡大用 */
CONST struct OPR_FIXED_MAGNIFI_TABLE_t OPR_FixedMagnificationTable[] = {
	{ OPR_MAGNIFI_100,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_100},	/* １００％用テーブル */
	{ OPR_MAGNIFI_129,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_129},	/* １２９％用テーブル */
	{ OPR_MAGNIFI_200,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_200},	/* ２００％用テーブル */
	{ NULL, NULL}
};

/* 固定倍率　縮小用 */
CONST struct OPR_FIXED_MAGNIFI_TABLE_t OPR_FixedReductionTable[] = {
	{ OPR_MAGNIFI_100,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_100},	/* １００％用テーブル */
	{ OPR_MAGNIFI_78,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_78 },	/*   ７８％用テーブル */
	{ OPR_MAGNIFI_64,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_64 },	/*   ６４％用テーブル */
	{ OPR_MAGNIFI_50,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_50 },	/*   ５０％用テーブル */
	{ NULL, NULL}
};

 #else  /*  これ以下 ＵＳＡ仕様以外（日本仕様、欧州仕様など）  */

/* ５０％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_50[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_A3_PAPER,		SYS_A5_PAPER  },
  #if (0) /* 本当はﾊｶﾞｷに対する倍率ではなくA6に対してなので、実際は多少違いがあるので表示を止めます by K.Watanabe 1997/11/11 */
//	{ SYS_A4_PAPER,		SYS_POST_PAPER},
  #endif
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* ７０％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_70[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_A3_PAPER,		SYS_A4_PAPER  },
	{ SYS_B4_PAPER,		SYS_B5_PAPER  },
	{ SYS_A4_PAPER,		SYS_A5_PAPER  },
	{ SYS_A4R_PAPER,	SYS_A5R_PAPER },
  #if (0) /* 本当はﾊｶﾞｷに対する倍率ではなくA6に対してなので、実際は多少違いがあるので表示を止めます by K.Watanabe 1997/11/11 */
//	{ SYS_A5_PAPER,		SYS_POST_PAPER},
  #endif
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* ８１％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_81[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_B4_PAPER,		SYS_A4_PAPER  },
	{ SYS_B5_PAPER,		SYS_A5_PAPER  },
	{ SYS_B5R_PAPER,	SYS_A5R_PAPER },
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* ８６％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_86[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_A3_PAPER,		SYS_B4_PAPER  },
	{ SYS_A4_PAPER,		SYS_B5_PAPER  },
	{ SYS_A4R_PAPER,	SYS_B5R_PAPER },
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* １００％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_100[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_A5_PAPER,		SYS_A5_PAPER  },
	{ SYS_LT_PAPER,		SYS_LT_PAPER  },
	{ SYS_A4_PAPER,		SYS_A4_PAPER  },
	{ SYS_LG_PAPER,		SYS_LG_PAPER  },
	{ SYS_B5R_PAPER,	SYS_B5R_PAPER },
	{ SYS_B4_PAPER,		SYS_B4_PAPER  },
	{ SYS_F4_PAPER,		SYS_F4_PAPER  },
	{ SYS_A5R_PAPER,	SYS_A5R_PAPER },
	{ SYS_POST_PAPER,	SYS_POST_PAPER},
	{ SYS_B5_PAPER,		SYS_B5_PAPER  },
	{ SYS_HLTR_PAPER,	SYS_HLTR_PAPER},                                 /* added by honda 1997/10/04 */
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* １１５％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_115[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_B5_PAPER,		SYS_A4_PAPER  },
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* １２２％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_122[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_A4_PAPER,		SYS_B4_PAPER  },
	{ SYS_A5_PAPER,		SYS_B5_PAPER  },
	{ SYS_A5R_PAPER,	SYS_B5R_PAPER },
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* １４１％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_141[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_B5_PAPER,		SYS_B4_PAPER  },
	{ SYS_A5_PAPER,		SYS_A4_PAPER  },
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* １７２％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_172[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
	{ SYS_A5_PAPER,		SYS_B4_PAPER  },
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* ２００％用テーブル */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_200[] = {
/*	{ 原稿サイズ,		記録紙サイズ  } */
  #if (0) /* 本当はﾊｶﾞｷに対する倍率ではなくA6に対してなので、実際は多少違いがあるので表示を止めます by K.Watanabe 1997/11/11 */
//	{ SYS_POST_PAPER,	SYS_A4_PAPER  },
  #endif
	{ SYS_NO_PAPER,		SYS_NO_PAPER  }
};

/* 固定倍率　拡大用 */
CONST struct OPR_FIXED_MAGNIFI_TABLE_t OPR_FixedMagnificationTable[] = {
	{ OPR_MAGNIFI_100,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_100},	/* １００％用テーブル */
	{ OPR_MAGNIFI_115,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_115},	/* １１５％用テーブル */
	{ OPR_MAGNIFI_122,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_122},	/* １２２％用テーブル */
	{ OPR_MAGNIFI_141,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_141},	/* １４１％用テーブル */
	{ OPR_MAGNIFI_172,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_172},	/* １７２％用テーブル */
	{ OPR_MAGNIFI_200,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_200},	/* ２００％用テーブル */
	{ NULL, NULL}
};

/* 固定倍率　縮小用 */
CONST struct OPR_FIXED_MAGNIFI_TABLE_t OPR_FixedReductionTable[] = {
	{ OPR_MAGNIFI_100,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_100},	/* １００％用テーブル */
	{ OPR_MAGNIFI_86,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_86 },	/*   ８６％用テーブル */
	{ OPR_MAGNIFI_81,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_81 },	/*   ８１％用テーブル */
	{ OPR_MAGNIFI_70,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_70 },	/*   ７０％用テーブル */
	{ OPR_MAGNIFI_50,	(struct OPR_MAGNIFI_PAPER_TABLE_t *)OPR_FixedMagnification_50 },	/*   ５０％用テーブル */
	{ NULL, NULL}
};
 #endif /* defined(USA) */

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/04/04
*             TYPE:  CONST struct
*      VAR TO HOLD:
*      DESCRIPTION:  ブックコピー原稿サイズ設定用テーブル
************************************************************************/
/* 記録紙　Ａ５用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_A5[] = {
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B4     },
	{   70, SYS_REGULAR_SIZE_A4     },
	{  100, SYS_REGULAR_SIZE_A4     },
	{  200, SYS_REGULAR_SIZE_A4     },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　レター用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_Letter[] = {
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B4     },	/* SYS_REGULAR_SIZE_A3 -> SYS_REGULAR_SIZE_B4 */
	{   86, SYS_REGULAR_SIZE_B4     },
	{  100, SYS_REGULAR_SIZE_LETTER },
	{  200, SYS_REGULAR_SIZE_LETTER },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　Ａ４用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_A4[] = {
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B4     },	/* SYS_REGULAR_SIZE_A3 -> SYS_REGULAR_SIZE_B4 */
	{   81, SYS_REGULAR_SIZE_B4     },
	{  100, SYS_REGULAR_SIZE_A4     },
	{  200, SYS_REGULAR_SIZE_A4     },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　リーガル用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_Legal[] = {
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B4		},	/* SYS_REGULAR_SIZE_LEGAL -> SYS_REGULAR_SIZE_B4 By S.Fukui Jan.21,1998 */
	{  100, SYS_REGULAR_SIZE_LEGAL  },
	{  200, SYS_REGULAR_SIZE_LEGAL  },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　Ｂ５横用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_B5R[] = {
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B5R    },	/* SYS_REGULAR_SIZE_A4R -> SYS_REGULAR_SIZE_B5R */
	{  100, SYS_REGULAR_SIZE_B5R    },
	{  122, SYS_REGULAR_SIZE_A5R    },
	{  200, SYS_REGULAR_SIZE_A5R    },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　Ｂ４用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_B4[] = {
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B4     },	/* SYS_REGULAR_SIZE_A3 -> SYS_REGULAR_SIZE_B4 */
	{  100, SYS_REGULAR_SIZE_B4     },
	{  122, SYS_REGULAR_SIZE_A4     },
	{  200, SYS_REGULAR_SIZE_A4     },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　レター横用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_LetterR[] = {
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B5R    },	/* SYS_REGULAR_SIZE_LETTER_R -> SYS_REGULAR_SIZE_B5R */
	{  122, SYS_REGULAR_SIZE_B5R    },
	{  200, SYS_REGULAR_SIZE_B5R    },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　Ａ５横用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_A5R[] = {
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B5R    },	/* SYS_REGULAR_SIZE_A4R -> SYS_REGULAR_SIZE_B5R */
	{   81, SYS_REGULAR_SIZE_B5R    },
	{  100, SYS_REGULAR_SIZE_A5R    },
	{  200, SYS_REGULAR_SIZE_A5R    },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　はがき用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_Post[] = {
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_A4     },
	{  100, SYS_REGULAR_SIZE_A5R    },
	{  200, SYS_REGULAR_SIZE_A5R    },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　Ｂ５用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_B5[] = {
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B4     },
	{   86, SYS_REGULAR_SIZE_A4     },
	{  100, SYS_REGULAR_SIZE_A4     },
	{  200, SYS_REGULAR_SIZE_A4     },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　ハーフレター横用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_HalfLetterR[] = {  /* added by honda 1997/10/04 */
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B5R     }, /* SYS_REGULAR_SIZE_A4R => SYS_REGULAR_SIZE_B5R */
    {   71, SYS_REGULAR_SIZE_B5R     }, /* SYS_REGULAR_SIZE_A4R => SYS_REGULAR_SIZE_B5R */
	{  100, SYS_REGULAR_SIZE_LETTER },
	{  200, SYS_REGULAR_SIZE_LETTER },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* 記録紙　Ｆ４用テーブル */
CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_F4[] = {  /* POPLAR_B AUS by thonda1998/05/12 */
/*	{ 倍率, ブック原稿サイズ        } */
	{   50, SYS_REGULAR_SIZE_B4     },
    {   81, SYS_REGULAR_SIZE_B4     },
	{  100, SYS_REGULAR_SIZE_F4     },
	{  200, SYS_REGULAR_SIZE_F4     },
	{ NULL, SYS_REGULAR_SIZE_UNKNOWN}
};

/* ブックコピー原稿サイズ設定用テーブル */
CONST struct OPR_BOOK_COPY_DOC_TABLE_t OPR_BookCopyDocumentSizeTable[] = {  /* added by honda 1997/10/04 ハーフレター横用 */
/*	{ 記録紙サイズ,		記録紙サイズごとの倍率による原稿サイズ設定テーブルのポインター  } */
	{ SYS_A5_PAPER,		(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_A5         },	/* Ａ５用テーブル			*/
	{ SYS_LT_PAPER,		(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_Letter     },	/* レター用テーブル			*/
	{ SYS_A4_PAPER,		(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_A4         },	/* Ａ４用テーブル			*/
	{ SYS_LG_PAPER,		(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_Legal      },	/* リーガル用テーブル		*/
	{ SYS_B5R_PAPER,	(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_B5R        },	/* Ｂ５Ｒ用テーブル			*/
	{ SYS_B4_PAPER,		(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_B4         },	/* Ｂ４用テーブル			*/
	{ SYS_LTR_PAPER,	(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_LetterR    },	/* レター横用テーブル		*/
	{ SYS_A5R_PAPER,	(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_A5R        },	/* Ａ５横用テーブル			*/
	{ SYS_POST_PAPER,	(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_Post       },	/* はがき用テーブル			*/
	{ SYS_B5_PAPER,		(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_B5         },	/* Ｂ５用テーブル			*/
	{ SYS_HLTR_PAPER,	(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_HalfLetterR},	/* ハーフレター横用テーブル	*/
	{ SYS_F4_PAPER,		(struct OPR_PRINT_PAPER_TABLE_t *)OPR_PrintPaperSize_F4         },	/* Ｆ４用テーブル			*//* POPLAR_B AUS by thonda1998/05/12 */
	{ SYS_NO_PAPER,		NULL}
};

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/07/03
*             TYPE:  CONST struct
*      VAR TO HOLD:
*      DESCRIPTION:  コピー不可能な原稿サイズ・記録紙サイズのテーブル
*          COMMENT:  テーブルの最後のデータをNULLで定義すると、紙サイズ
*                    の先頭のdefine値と同じになるので、テーブルの最後の
*                    データは0xFF(SYS_NO_PAPER)で定義します
************************************************************************/
/* Ａ４→ハガキもコピー禁止になり（実際は５０％以下なので）、結局ＡＤＦからハガキには
** コピーできなくなった為に、テーブルを使用してのチェックは必要ないので、削除します
*/
 #if (0)	/* by K.Watanabe 1997/12/26 */
CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_CopyImposPaperCombiTable[] = {
/*	{ 原稿サイズ,           記録紙サイズ    } */
	{ SYS_DOCUMENT_A3_SIZE, SYS_POST_PAPER  },
	{ SYS_DOCUMENT_B4_SIZE, SYS_POST_PAPER  },
	{ SYS_NO_PAPER,         SYS_NO_PAPER    }
};
 #endif

#endif	/* (PRO_COPY_FAX_MODE == ENABLE) */

/************************************************************************
*               BY:  M.Kuwahara
*             DATE:  97/06/05
*             TYPE:  CONST UWORD
*      VAR TO HOLD:
*      DESCRIPTION:  工場ファンクション
************************************************************************/
/* ＬＥＤテスト用 点灯順序設定用テーブル */
CONST struct LED_AREA_t	LedArea[] = {
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
	{2,	FAX_COM_LED},			/* 通信中				*/
	{2,	MEMORY_RX_LED},			/* 代行受信				*/
	{2,	AUTO_RX_LED},			/* 自動受信				*/
	{2,	STAMP_LED},				/* 済みスタンプ			*/
	{1,	COPY_LED},				/* コピー				*/
	{1,	FAX_LED},				/* ファクス				*/
	{2,	ON_HOOK_LED},			/* フック／会話予約		*/
	{2,	MODE_GRAY_LED},			/* 写真					*/
	{2,	MODE_SFINE_LED},		/* 超高画質				*/
	{2,	MODE_FINE_LED},			/* 高画質				*/
	{1,	ALARM_LED},				/* アラーム				*/
	{1,	PAPER_JAM_LED},			/* 紙づまり				*/
	{1,	REPLACE_PAPER_LED},		/* 記録紙				*/
	{1,	MEMORY_TX_LED},			/* メモリ送信			*/
	{0,	0xffff}
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
	{2,	FAX_COM_LED},			/* 通信中				*/
	{2,	MEMORY_RX_LED},			/* 代行受信				*/
	{2,	AUTO_RX_LED},			/* 自動受信				*/
	{2,	STAMP_LED},				/* 済みスタンプ			*/
	{2,	ON_HOOK_LED},			/* フック／会話予約		*/
	{2,	MODE_GRAY_LED},			/* 写真					*/
	{2,	MODE_SFINE_LED},		/* 超高画質				*/
	{2,	MODE_FINE_LED},			/* 高画質				*/
	{1,	ALARM_LED},				/* アラーム				*/
	{1,	PAPER_JAM_LED},			/* 紙づまり				*/
	{1,	REPLACE_PAPER_LED},		/* 記録紙				*/
	{1,	MEMORY_TX_LED},			/* メモリ送信			*/
	{0,	0xffff}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	{3,	ALARM_LED},				/* アラーム				*/
	{2,	FAX_COM_LED},			/* 通信中				*/
	{2,	MEMORY_RX_LED},			/* 代行受信				*/
	{2,	MODE_GRAY_LED},			/* 写真					*/
	{2,	MODE_SFINE_LED},		/* 超高画質				*/
	{1,	MODE_FINE_LED},			/* 高画質				*/
	{1,	MODE_NORM_LED},			/* 標準					*/
	{2,	AUTO_RX_LED},			/* 自動受信				*/
	{1,	MEMORY_TX_LED},			/* メモリ送信			*/
	{1, DST_DARK_LED},			/* こく					*/
	{1,	DST_NORM_LED},			/* ふつう				*/
	{1,	DST_LIGHT_LED},			/* うすく				*/
	{2, PRT_ALARM_LED},			/* プリンタ				*/
	{2,	PAPER_JAM_LED},			/* 紙づまり				*/
	{1,	REPLACE_PAPER_LED},		/* 記録紙				*/
	{2,	ON_HOOK_LED},			/* フック／会話予約		*/
	{1,	STAMP_LED},				/* 済みスタンプ			*/
	{0,	0xffff}
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)	/* For HINOKI By O.Kimoto 1998/09/08 */
	{2,	ALARM_LED},				/* アラーム				*//* T.B.D. By O.Kimoto 1998/09/08 */
	{2,	FAX_COM_LED},			/* 通信中				*/
	{2,	MEMORY_RX_LED},			/* 代行受信				*/
	{1,	MODE_GRAY_LED},			/* 写真					*/
	{1,	MODE_SFINE_LED},		/* 超高画質				*/
	{1,	MODE_FINE_LED},			/* 高画質				*/
 #if (1)	/* Change By H.Fujimura 1998/12/28 */
	{1,	MODE_NORMAL_LED},		/* 標準					*//* T.B.D. By O.Kimoto 1998/09/08 */
 #else
//	{1,	MODE_NORM_LED},			/* 標準					*//* T.B.D. By O.Kimoto 1998/09/08 */
 #endif
	{2,	AUTO_RX_LED},			/* 自動受信				*/
	{2,	MEMORY_TX_LED},			/* メモリ送信			*/
	{1, DST_DARK_LED},			/* こく					*/
 #if (1)	/* Change By H.Fujimura 1998/12/28 */
	{1,	DST_NORMAL_LED},		/* ふつう				*//* T.B.D. By O.Kimoto 1998/09/08 */
 #else
//	{1,	DST_NORM_LED},			/* ふつう				*//* T.B.D. By O.Kimoto 1998/09/08 */
 #endif
	{1,	DST_LIGHT_LED},			/* うすく				*/
	/* {2, PRT_ALARM_LED},			*//* プリンタ				*//* T.B.D. By O.Kimoto 1998/09/08 */
	/* {2,	PAPER_JAM_LED},			*//* 紙づまり				*//* T.B.D. By O.Kimoto 1998/09/08 */
	/* {1,	REPLACE_PAPER_LED},		*//* 記録紙				*//* T.B.D. By O.Kimoto 1998/09/08 */
	{3,	ON_HOOK_LED},			/* フック／会話予約		*/
 #if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/09/15 */
	{1,	RESERVATION_LED},		/* 会話予約				*/
 #else
	{1,	STAMP_LED},				/* 済みスタンプ			*/
 #endif		/* End of (defined (KEISATSU)) */
	{0,	0xffff}
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) 	/* For SATSUKI2 by Y.Kano 2003/07/11 */
 #if (0) /* Modify by SMuratec L.Z.W 2003/07/25 */
	{2,	ALARM_LED},				/* アラーム				*//* T.B.D. By O.Kimoto 1998/09/08 */
	{2,	FAX_COM_LED},			/* 通信中				*/
	{2,	MEMORY_RX_LED},			/* 代行受信				*/
	{1,	MODE_GRAY_LED},			/* 写真					*/
	{1,	MODE_SFINE_LED},		/* 超高画質				*/
	{1,	MODE_FINE_LED},			/* 高画質				*/
 #if (1)	/* Change By H.Fujimura 1998/12/28 */
	{1,	MODE_NORMAL_LED},		/* 標準					*//* T.B.D. By O.Kimoto 1998/09/08 */
 #else
//	{1,	MODE_NORM_LED},			/* 標準					*//* T.B.D. By O.Kimoto 1998/09/08 */
 #endif
	{2,	AUTO_RX_LED},			/* 自動受信				*/
	{2,	MEMORY_TX_LED},			/* メモリ送信			*/
	{1, DST_DARK_LED},			/* こく					*/
 #if (1)	/* Change By H.Fujimura 1998/12/28 */
	{1,	DST_NORMAL_LED},		/* ふつう				*//* T.B.D. By O.Kimoto 1998/09/08 */
 #else
//	{1,	DST_NORM_LED},			/* ふつう				*//* T.B.D. By O.Kimoto 1998/09/08 */
 #endif
	{1,	DST_LIGHT_LED},			/* うすく				*/
	/* {2, PRT_ALARM_LED},			*//* プリンタ				*//* T.B.D. By O.Kimoto 1998/09/08 */
	/* {2,	PAPER_JAM_LED},			*//* 紙づまり				*//* T.B.D. By O.Kimoto 1998/09/08 */
	/* {1,	REPLACE_PAPER_LED},		*//* 記録紙				*//* T.B.D. By O.Kimoto 1998/09/08 */
	{3,	ON_HOOK_LED},			/* フック／会話予約		*/
	{1,	STAMP_LED},				/* 済みスタンプ			*/
	{0,	0xffff}
 #else /* Modify by SMuratec L.Z.W 2003/07/25 */
	{0,	ALARM_LED},				/* アラーム				*//* T.B.D. By O.Kimoto 1998/09/08 */
	{0,	AUTO_RX_LED},			/* 自動受信				*/
	{0,	MEMORY_RX_LED},			/* 代行受信				*/
	{0,	MEMORY_TX_LED},			/* メモリ送信			*/
	{0,	FAX_COM_LED},			/* 通信中				*/
	{0,	COPY_BUTTON_LED},		/* コピーボタン			*/
	
	{0,	ALARM_LED},				/* アラーム				*//* T.B.D. By O.Kimoto 1998/09/08 */
	{0,	AUTO_RX_LED},			/* 自動受信				*/
	{0,	MEMORY_RX_LED},			/* 代行受信				*/
	{0,	MEMORY_TX_LED},			/* メモリ送信			*/
	{0,	FAX_COM_LED},			/* 通信中				*/
	{0,	COPY_BUTTON_LED},		/* コピーボタン			*/
	
	{0,	ALARM_LED},				/* アラーム				*//* T.B.D. By O.Kimoto 1998/09/08 */
	{0,	AUTO_RX_LED},			/* 自動受信				*/
	{0,	0xffff} 
 #endif
#endif

#if(PRO_KEYPANEL == PANEL_STOCKHM2)	/* Modify by SMuratec 夏 2004/10/8 */
	{1,	ALARM_LED},				/* アラーム				*//* T.B.D. By O.Kimoto 1998/09/08 */
	{1,	AUTO_RX_LED},			/* 自動受信				*/
	{1,	MEMORY_RX_LED},			/* 代行受信				*/
	{1,	MEMORY_TX_LED},			/* メモリ送信			*/
#endif

};

/* ＬＣＤテスト用 キー入力順序設定用テーブル */
CONST UBYTE	KeyArea[] = {
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_ANZU_L)
	COPY_FAX_KEY,		/* コピー／ファクスキー		*/
	REVIEW_KEY,			/* 通信中止／確認キー		*/
	HOOK_KEY,			/* フック／会話予約キー		*/
	MODE_KEY,			/* 画質キー					*/
	CONTRAST_KEY,		/* 濃度キー					*/
	NEXT_DOC_KEY,		/* 次原稿キー				*/
	REDUCTION_KEY,		/* 縮小キー					*/
	FUNCTION_KEY,		/* 機能／右矢印キー			*/
	MAGNIFICATION_KEY,	/* 拡大キー					*/
	SET_KEY,			/* セットキー				*/
	SORT_KEY,			/* ソートキー				*/
	CLEAR_KEY,			/* クリアキー				*/
	PAPER_SELECT_KEY,	/* 用紙選択キー				*/
	BROADCAST_KEY,		/* 同報キー					*/
	SPECIAL_KEY,		/* 応用通信キー				*/
	GROUP_KEY,			/* グループキー				*/
	SPEED_KEY,			/* 短縮／電話帳キー			*/
	MEMORY_TX_KEY,		/* メモリ送信キー			*/
	BOOK_DOC_SIZE_KEY,	/* ブック原稿サイズキー		*/
	TEN_1_KEY,			/* テンキー１キー			*/
	TEN_4_KEY,			/* テンキー４キー			*/
	TEN_7_KEY,			/* テンキー７キー			*/
	TEN_AST_KEY,		/* テンキー＊キー			*/
	COPY_RESET_KEY,		/* コピーリセットキー		*/
	STOP_KEY,			/* ストップキー				*/
	TEN_2_KEY,			/* テンキー２キー			*/
	TEN_5_KEY,			/* テンキー５キー			*/
	TEN_8_KEY,			/* テンキー８キー			*/
	TEN_0_KEY,			/* テンキー０キー			*/
	TEN_3_KEY,			/* テンキー３キー			*/
	TEN_6_KEY,			/* テンキー６キー			*/
	TEN_9_KEY,			/* テンキー９キー			*/
	TEN_SHARP_KEY,		/* テンキー＃キー			*/
	START_KEY			/* スタートキー				*/
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* 1998/01/09  By T.Yamaguchi */
	REVIEW_KEY,			/* 通信中止／確認キー		*/
	HOOK_KEY,			/* フック／会話予約キー		*/
	MODE_KEY,			/* 画質キー					*/
	CONTRAST_KEY,		/* 濃度キー					*/
	CURSOR_LEFT_KEY,	/* 左矢印キー 				*/
	TONE_KEY,			/* ダイヤル記号キー 		*/
	FUNCTION_KEY,		/* 機能／右矢印キー			*/
	HOLD_KEY,			/* 保留キー					*/
	SET_KEY,			/* セットキー				*/
	DIAL_MARK_KEY,		/* ダイヤル記号キー			*/
	CLEAR_KEY,			/* クリアキー				*/
	REDIAL_KEY,			/* リダイヤル／ポーズキー	*/
	BROADCAST_KEY,		/* 同報キー					*/
	SPECIAL_KEY,		/* 応用通信キー				*/
	GROUP_KEY,			/* グループキー				*/
	SPEED_KEY,			/* 短縮／電話帳キー			*/
	MEMORY_TX_KEY,		/* メモリ送信キー			*/
	STAMP_KEY,			/* 済みスタンプキー			*/
	TEN_1_KEY,			/* テンキー１キー			*/
	TEN_4_KEY,			/* テンキー４キー			*/
	TEN_7_KEY,			/* テンキー７キー			*/
	TEN_AST_KEY,		/* テンキー＊キー			*/
	COPY_KEY,			/* コピーキー				*/
	STOP_KEY,			/* ストップキー				*/
	TEN_2_KEY,			/* テンキー２キー			*/
	TEN_5_KEY,			/* テンキー５キー			*/
	TEN_8_KEY,			/* テンキー８キー			*/
	TEN_0_KEY,			/* テンキー０キー			*/
	TEN_3_KEY,			/* テンキー３キー			*/
	TEN_6_KEY,			/* テンキー６キー			*/
	TEN_9_KEY,			/* テンキー９キー			*/
	TEN_SHARP_KEY,		/* テンキー＃キー			*/
	START_KEY			/* スタートキー				*/
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)	/* Add By H.Fujimura 1998/12/28 */
	AUTO_RX_KEY,		/* 自動受信キー				*/
	HOOK_KEY,			/* フック／会話予約キー		*/
	REDIAL_KEY,			/* リダイヤル／ポーズキー	*/
	REVIEW_KEY,			/* 通信中止／確認キー		*/
	CURSOR_LEFT_KEY,	/* 左矢印キー 				*/
	MODE_KEY,			/* 画質キー					*/
	FUNCTION_KEY,		/* 機能／右矢印キー			*/
	SET_KEY,			/* セットキー				*/
	CONTRAST_KEY,		/* 濃度キー					*/
	CLEAR_KEY,			/* クリアキー				*/
	DIAL_MARK_KEY,		/* ダイヤル記号キー			*/
	HOLD_KEY,			/* 保留キー					*/
	BROADCAST_KEY,		/* 同報キー					*/
	SPECIAL_KEY,		/* 応用通信キー				*/
	GROUP_KEY,			/* グループキー				*/
	SPEED_KEY,			/* 短縮／電話帳キー			*/
	MEMORY_TX_KEY,		/* メモリ送信キー			*/
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/21 */
	RESERVATION,
#else
	STAMP_KEY,			/* 済みスタンプキー			*/
#endif		/* End of (defined (KEISATSU)) */
	TEN_1_KEY,			/* テンキー１キー			*/
	TEN_4_KEY,			/* テンキー４キー			*/
	TEN_7_KEY,			/* テンキー７キー			*/
	TEN_AST_KEY,		/* テンキー＊キー			*/
	STOP_KEY,			/* ストップキー				*/
	TEN_2_KEY,			/* テンキー２キー			*/
	TEN_5_KEY,			/* テンキー５キー			*/
	TEN_8_KEY,			/* テンキー８キー			*/
	TEN_0_KEY,			/* テンキー０キー			*/
	COPY_KEY,			/* コピーキー				*/
	TEN_3_KEY,			/* テンキー３キー			*/
	TEN_6_KEY,			/* テンキー６キー			*/
	TEN_9_KEY,			/* テンキー９キー			*/
	TEN_SHARP_KEY,		/* テンキー＃キー			*/
	START_KEY,			/* スタートキー				*/
 #if defined(HINOKI3)	/* ワンタッチキーの追加 by Y.Kano 2004/12/22 */
	ONETOUCH_01_KEY,	/* ワンタッチ０１キー		*/
	ONETOUCH_07_KEY,	/* ワンタッチ０７キー		*/
	ONETOUCH_13_KEY,	/* ワンタッチ１３キー		*/
	ONETOUCH_19_KEY,	/* ワンタッチ１９キー		*/
	ONETOUCH_25_KEY,	/* ワンタッチ２５キー		*/
	ONETOUCH_02_KEY,	/* ワンタッチ０２キー		*/
	ONETOUCH_08_KEY,	/* ワンタッチ０８キー		*/
	ONETOUCH_14_KEY,	/* ワンタッチ１４キー		*/
	ONETOUCH_20_KEY,	/* ワンタッチ２０キー		*/
	ONETOUCH_26_KEY,	/* ワンタッチ２６キー		*/
	ONETOUCH_03_KEY,	/* ワンタッチ０３キー		*/
	ONETOUCH_09_KEY,	/* ワンタッチ０９キー		*/
	ONETOUCH_15_KEY,	/* ワンタッチ１５キー		*/
	ONETOUCH_21_KEY,	/* ワンタッチ２１キー		*/
	ONETOUCH_27_KEY,	/* ワンタッチ２７キー		*/
	ONETOUCH_04_KEY,	/* ワンタッチ０４キー		*/
	ONETOUCH_10_KEY,	/* ワンタッチ１０キー		*/
	ONETOUCH_16_KEY,	/* ワンタッチ１６キー		*/
	ONETOUCH_22_KEY,	/* ワンタッチ２２キー		*/
	ONETOUCH_28_KEY, 	/* ワンタッチ２８キー		*/
	ONETOUCH_05_KEY,	/* ワンタッチ０５キー		*/
	ONETOUCH_11_KEY,	/* ワンタッチ１１キー		*/
	ONETOUCH_17_KEY,	/* ワンタッチ１７キー		*/
	ONETOUCH_23_KEY,	/* ワンタッチ２３キー		*/
	ONETOUCH_29_KEY, 	/* ワンタッチ２９キー		*/
	ONETOUCH_06_KEY,	/* ワンタッチ０６キー		*/
	ONETOUCH_12_KEY,	/* ワンタッチ１２キー		*/
	ONETOUCH_18_KEY,	/* ワンタッチ１８キー		*/
	ONETOUCH_24_KEY,	/* ワンタッチ２４キー		*/
  #if (PRO_PREFIX_KEY == ENABLE)	/* 警察FAX Modify by SMuratec K.W.Q 2005/10/13 */
	MERCURY_KEY,		/* プレフィックスキー		*/
  #else
	ONETOUCH_30_KEY,	/* ワンタッチ３０キー		*/
  #endif
 #endif
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) 	/* Add by Y.Kano 2003/07/11 */ /* (パネルキーテストの順序を変更する)Modified by SMuratec L.Z.W 2003/10/23 */
	REVIEW_KEY,			/* 通信中止／確認キー		*/
	CMD_LIST_KEY,		/* Ｐ通信管理キー			*/
	TCH_LIST_KEY,		/* Ｐワンタッチリストキー	*/
	SPD_LIST_KEY,		/* Ｐ短縮リストキー			*/
	SPECIAL_KEY,		/* 応用通信キー				*/
	BROADCAST_KEY,		/* 同報キー					*/
	GROUP_KEY,			/* グループキー				*/
	MEMORY_TX_KEY,		/* メモリ送信キー			*/
	CURSOR_LEFT_KEY,	/* 左矢印キー 				*/
	DIAL_MARK_KEY,		/* ダイヤル記号キー			*/
	COMM_REPORT_KEY,	/* 通信証キー				*/
	VOLUME_KEY,			/* 音量調整					*/
	FUNCTION_KEY,		/* 機能／右矢印キー			*/
	CHARACTER_KEY,		/* 文字キー			    	*/
	SET_KEY,			/* セットキー				*/
	CLEAR_KEY,			/* クリアキー				*/
	SPEED_KEY,			/* 短縮／電話帳キー			*/
	REDIAL_KEY,			/* リダイヤル／ポーズキー	*/
	HOLD_KEY,			/* 保留キー					*/
	HOOK_KEY,			/* フック／会話予約キー		*/
	TEN_1_KEY,			/* テンキー１キー			*/
	TEN_4_KEY,			/* テンキー４キー			*/
	TEN_7_KEY,			/* テンキー７キー			*/
	TEN_AST_KEY,		/* テンキー＊キー			*/
	TEN_2_KEY,			/* テンキー２キー			*/
	TEN_5_KEY,			/* テンキー５キー			*/
	TEN_8_KEY,			/* テンキー８キー			*/
	TEN_0_KEY,			/* テンキー０キー			*/
	TEN_3_KEY,			/* テンキー３キー			*/
	TEN_6_KEY,			/* テンキー６キー			*/
	TEN_9_KEY,			/* テンキー９キー			*/
	TEN_SHARP_KEY,		/* テンキー＃キー			*/
	ONETOUCH_01_KEY,	/* ワンタッチ０１キー		*/
	ONETOUCH_02_KEY,	/* ワンタッチ０２キー		*/
	ONETOUCH_03_KEY,	/* ワンタッチ０３キー		*/
	ONETOUCH_04_KEY,	/* ワンタッチ０４キー		*/
	ONETOUCH_05_KEY,	/* ワンタッチ０５キー		*/
	ONETOUCH_06_KEY,	/* ワンタッチ０６キー		*/
	ONETOUCH_07_KEY,	/* ワンタッチ０７キー		*/
	ONETOUCH_08_KEY,	/* ワンタッチ０８キー		*/
	ONETOUCH_09_KEY,	/* ワンタッチ０９キー		*/
	ONETOUCH_10_KEY,	/* ワンタッチ１０キー		*/
	ONETOUCH_11_KEY,	/* ワンタッチ１１キー		*/
	ONETOUCH_12_KEY,	/* ワンタッチ１２キー		*/
	ONETOUCH_13_KEY,	/* ワンタッチ１３キー		*/
	ONETOUCH_14_KEY,	/* ワンタッチ１４キー		*/
	ONETOUCH_15_KEY,	/* ワンタッチ１５キー		*/
	ONETOUCH_16_KEY,	/* ワンタッチ１６キー		*/
	ONETOUCH_17_KEY,	/* ワンタッチ１７キー		*/
	ONETOUCH_18_KEY,	/* ワンタッチ１８キー		*/
	ONETOUCH_19_KEY,	/* ワンタッチ１９キー		*/
	ONETOUCH_20_KEY,	/* ワンタッチ２０キー		*/
	AUTO_RX_KEY,		/* 自動受信キー				*/
	COPY_KEY,			/* コピーキー				*/
	STOP_KEY,			/* ストップキー				*/
	START_KEY			/* スタートキー				*/
#endif

#if(PRO_KEYPANEL == PANEL_STOCKHM2)	/* Modify by SMuratec 夏 2004/10/8 */
	AUTO_RX_KEY,		/* 自動受信キー				*/
	BROADCAST_KEY,		/* 同報キー					*/
	SPECIAL_KEY,		/* 応用通信キー				*/
	GROUP_KEY,			/* グループキー				*/
	MEMORY_TX_KEY,		/* メモリ送信キー			*/
	CURSOR_LEFT_KEY,	/* 左矢印キー 				*/
	CLEAR_KEY,			/* クリアキー				*/
	FUNCTION_KEY,		/* 機能／右矢印キー			*/
	SET_KEY,			/* セットキー				*/	
	CHARACTER_KEY,		/* 文字キー			    	*/		
	DIAL_MARK_KEY,		/* ダイヤル記号キー			*/
	SPEED_KEY,			/* 短縮／電話帳キー			*/
	REDIAL_KEY,			/* リダイヤル／ポーズキー	*/
	HOLD_KEY,			/* 保留キー					*/
	MERCURY_KEY,		/* プレフィクスキー			*/
	HOOK_KEY,			/* フック／会話予約キー		*/
	REVIEW_KEY,			/* 通信中止／確認キー		*/
	TEN_1_KEY,			/* テンキー１キー			*/
	TEN_4_KEY,			/* テンキー４キー			*/
	TEN_7_KEY,			/* テンキー７キー			*/
	TEN_AST_KEY,		/* テンキー＊キー			*/
	TEN_2_KEY,			/* テンキー２キー			*/
	TEN_5_KEY,			/* テンキー５キー			*/
	TEN_8_KEY,			/* テンキー８キー			*/
	TEN_0_KEY,			/* テンキー０キー			*/
	TEN_3_KEY,			/* テンキー３キー			*/
	TEN_6_KEY,			/* テンキー６キー			*/
	TEN_9_KEY,			/* テンキー９キー			*/
	TEN_SHARP_KEY,		/* テンキー＃キー			*/
	STOP_KEY,			/* ストップキー				*/
	COPY_KEY,			/* コピーキー				*/
	START_KEY,			/* スタートキー				*/
	ONETOUCH_01_KEY,	/* ワンタッチ０１キー		*/
	ONETOUCH_05_KEY,	/* ワンタッチ０５キー		*/
	ONETOUCH_09_KEY,	/* ワンタッチ０９キー		*/
	ONETOUCH_13_KEY,	/* ワンタッチ１３キー		*/
	ONETOUCH_17_KEY,	/* ワンタッチ１７キー		*/
	ONETOUCH_02_KEY,	/* ワンタッチ０２キー		*/
	ONETOUCH_06_KEY,	/* ワンタッチ０６キー		*/
	ONETOUCH_10_KEY,	/* ワンタッチ１０キー		*/
	ONETOUCH_14_KEY,	/* ワンタッチ１４キー		*/
	ONETOUCH_18_KEY,	/* ワンタッチ１８キー		*/
	ONETOUCH_03_KEY,	/* ワンタッチ０３キー		*/
	ONETOUCH_07_KEY,	/* ワンタッチ０７キー		*/
	ONETOUCH_11_KEY,	/* ワンタッチ１１キー		*/
	ONETOUCH_15_KEY,	/* ワンタッチ１５キー		*/
	ONETOUCH_19_KEY,	/* ワンタッチ１９キー		*/
	ONETOUCH_04_KEY,	/* ワンタッチ０４キー		*/
	ONETOUCH_08_KEY,	/* ワンタッチ０８キー		*/
	ONETOUCH_12_KEY,	/* ワンタッチ１２キー		*/
	ONETOUCH_16_KEY,	/* ワンタッチ１６キー		*/
	ONETOUCH_20_KEY 	/* ワンタッチ２０キー		*/
#endif

};

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/12/12
*             TYPE:  CONST struct
*      VAR TO HOLD:
*      DESCRIPTION:  インチ・センチ変換テーブル
*          COMMENT:  インチ入力された値をセンチに変換するだけなら、直接
*                    計算するだけで問題ないが、再表示でセンチからインチ
*                    に戻す時に、途中で四捨五入されているために計算では
*                    戻せないので、テーブルを作成しました
************************************************************************/
#if (PRO_CIPHER == ENABLE)
CONST struct OPR_INCH_CENTI_TABLE_t OPR_ChangeInchCentiTable[] = {
/*	{ ｲﾝﾁ x 10, ｲﾝﾁ x 2.54cmを小数点以下１桁めで四捨五入 }	*/
	{   10,    3},		/*  1.0inch =  2.54cm */
	{   15,    4},		/*  1.5inch =  3.81cm */
	{   20,    5},		/*  2.0inch =  5.08cm */
	{   25,    6},		/*  2.5inch =  6.35cm */
	{   30,    8},		/*  3.0inch =  7.62cm */
	{   35,    9},		/*  3.5inch =  8.89cm */
	{   40,   10},		/*  4.0inch = 10.16cm */
	{   45,   11},		/*  4.5inch = 11.43cm */
	{   50,   13},		/*  5.0inch = 12.70cm */
	{   55,   14},		/*  5.5inch = 13.97cm */
	{   60,   15},		/*  6.0inch = 15.24cm */
	{   65,   17},		/*  6.5inch = 16.51cm */
	{   70,   18},		/*  7.0inch = 17.78cm */
	{   75,   19},		/*  7.5inch = 19.05cm */
	{   80,   20},		/*  8.0inch = 20.32cm */
	{   85,   22},		/*  8.5inch = 21.59cm */
	{   90,   23},		/*  9.0inch = 22.86cm */
	{   95,   24},		/*  9.5inch = 24.13cm */
	{  100,   25},		/* 10.0inch = 25.40cm */
	{  105,   27},		/* 10.5inch = 26.67cm */
	{  110,   28},		/* 11.0inch = 27.94cm */
	{  115,   29},		/* 11.5inch = 29.21cm */
	{  120,   30},		/* 12.0inch = 30.48cm */
	{  125,   32},		/* 12.5inch = 31.75cm */
	{  130,   33},		/* 13.0inch = 33.02cm */
	{  135,   34},		/* 13.5inch = 34.29cm */
	{  140,   36},		/* 14.0inch = 35.56cm */
	{  145,   37},		/* 14.5inch = 36.83cm */
	{ NULL, NULL}
};
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
/* 拡張プログラムワンタッチ（リスト）*/
CONST struct OPR_ProgramList_t OPR_ProgramList[] = {
	{	LST_ONETOUCHDIAL_LIST,	PrintOneTouchList			},	/* ワンタッチダイヤルリスト							*/
	{	LST_SPEEDDIAL_LIST,		PrintSpeedDialList			},	/* 短縮ダイヤルリスト								*/
	{	LST_PROGRAM_LIST,		PrintProgramOneTouchList	},	/* プログラムワンタッチリスト						*/
	{	LST_MAILBOX_LIST,		PrintSecureMailList			},	/* 親展者リスト										*/
	{	LST_RESERVECMD_LIST,	PrintCommandList			},	/* 通信予約リスト									*/
 #if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
	{	LST_JOURNAL_LIST,		PrintJournalList			},	/* 通信管理レポート									*/
	{	LST_DAILY_REPORT,		PrintDailyReport			},	/* 通信管理記録日報プリント							*/
 #else
	{	LST_JOURNAL_LIST,		PrintJournalList			},	/* 通信管理レポート									*/
 #endif
	{	LST_GROUP_LIST,			PrintGroupList				},	/* グループリスト									*/
	{	LST_PARAMETER_LIST,		PrintSettingList			},	/* 機器設定リスト									*/
 #if !defined(KEISATSU)	/* 警察FAX対応 Added by SMuratec 夏 2005/08/24 */
	{	LST_BLOCK_JUNK_LIST,	PrintBlockJunkList2			},	/* ジャンクメール防止ダイヤルリスト					*/
 #endif
	{	LST_COVERPAGE_LIST,		PrintMessageList			},	/* カバーページプリント								*/
 #if !defined(KEISATSU)	/* 警察FAX対応 Added by SMuratec 夏 2005/08/24 */
  #if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) && (PRO_BATCH_TX == ENABLE) /* Modify by SMuratec L.Z.W 2003/09/12 */
	{	LST_BATCHTXBOX_LIST,	PrintBatchBoxList			},	/* 一括送信ＢＯＸリスト								*/
	{	LST_BATCHTXDOC_LIST,	PrintBatchDocumentList		},	/* 一括送信原稿リスト								*/
  #endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) && (PRO_BATCH_TX == ENABLE) */
 #endif
 #if (PRO_F_CODE == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	{	LST_F_CODE_BOX_LIST,	PrintFcodeBoxList			},	/* Ｆコードボックスリスト							*/
	{	LST_F_CODE_DOC_LIST,	PrintFcodeBoxDocList		},	/* Ｆコード蓄積原稿リスト							*/
 #endif
 #if (PRO_DEPART_NEW_LIST == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	{	LST_DEPARTMANAGE_LIST,	PrintDepartTimeList			},	/* 簡易料金管理リスト								*/
 #endif
 #if (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	{	LST_ND_LIST,			PrintNumberDisplayList		},	/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲﾀﾞｲﾔﾙﾘｽﾄ	*/
	{	LST_INF_ND_LIST,		Print_ND_JournalList		},	/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ着信履歴	*/
 #endif
 #if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	{	LST_WARP_LIST,			PrintFaxWarpList			},	/* ﾜｰﾌﾟ機能ﾘｽﾄ				*/
 #endif
	{	0xFE,					FunctionDummy				}
};
/* 拡張プログラムワンタッチ（蓄積）*/
CONST struct OPR_ProgramStore_t OPR_ProgramStore[] = {
	{	MSG_STORE_POLLING_DOC,		SetStorePollingDocument,	EnterStorePollingDocument	},	/* ポーリング原稿蓄積								*/
 #if (PRO_F_CODE == ENABLE)
	{	MSG_STORE_FCODE_BOX_DOC,	SetStoreFcodeBoxDocument,	EnterStoreFcodeBoxDocument	},	/* サブアドレスＢＯＸ原稿蓄積						*/
 #endif
	{	0xFE,						FunctionDummy,				FunctionDummy				}
};
/* 拡張プログラムワンタッチ（画質）*/
CONST UBYTE	OPR_ProgramTxModeSW[] = {
	0xFF,							/* －－－					*/
	PRIMARY_MODE_NORMAL,			/* 標準						*/
	PRIMARY_MODE_FINE,				/* 高画質					*/
	PRIMARY_MODE_SFINE,				/* 超高画質					*/
	PRIMARY_MODE_GRAY,				/* 写真						*/
	0xFE
};
/* 拡張プログラムワンタッチ（濃度）*/
CONST UBYTE	OPR_ProgramContrastSW[] = {
	0xFF,							/* －－－					*/
	SYS_LIGHT_DENSITY,				/* 薄く						*/
/*	SYS_LIGHT_NORMAL_DENSITY,	*/	/* 薄く－普通の間			*/
	SYS_NORMAL_DENSITY,				/* 普通						*/
/*	SYS_DARK_NORMAL_DENSITY,	*/	/* 濃く－普通の間			*/
	SYS_DARK_DENSITY,				/* 濃く						*/
	0xFE
};
/* 拡張プログラムワンタッチ（済スタンプ）*/
CONST UBYTE	OPR_ProgramStampSW[] = {
	0xFF,							/* －－－					*/
	0,								/* ＯＦＦ					*/
	SYS_STAMP_ON,					/* ＯＮ						*/
	0xFE
};
/* 拡張プログラムワンタッチ（メモリ送信）*/
CONST UBYTE	OPR_ProgramMemoryTxSW[] = {
	0xFF,							/* －－－					*/
	0,								/* ＯＦＦ					*/
	SYS_MEMORY_TX_ON,				/* ＯＮ						*/
	0xFE
};
/* 拡張プログラムワンタッチ（通信証）*/
CONST UBYTE	OPR_ProgramConfirmSW[] = {
	0xFF,							/* －－－					*/
	NO_CONFIRMATION_REPORT,			/* なし						*/
	TCR_REQUEST,					/* 送信証					*/
	RCR_REQUEST,					/* 受領証					*/
	0xFE
};
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)	*//* For HINOKI By O.Kimoto 1998/10/07 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* For HINOKI By O.Kimoto 1998/10/07 */ /* Add by Y.Kano 2003/07/11 */

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/12/05
*             TYPE:  CONST
*      VAR TO HOLD:
*      DESCRIPTION:  ＣＧ　ＲＡＭテーブル（Ⅰ／Ⅱ／Ⅲ／Ⅳ ）
*          COMMENT:  有効範囲は右上基準の７(縦)ｘ５(横)です
************************************************************************/
CONST UBYTE CG_RamTableNumericSymbol[4][8] = {

    /* CGRAMにⅠを書き込む */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 0 0 1 0 0 ---> 0x04 */
    /* 0 0 0 0 0 1 0 0 ---> 0x04 */
    /* 0 0 0 0 0 1 0 0 ---> 0x04 */
    /* 0 0 0 0 0 1 0 0 ---> 0x04 */
    /* 0 0 0 0 0 1 0 0 ---> 0x04 */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 0 0 0 0 0 ---> 0x00 */
    {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1F, 0x00},
    
    /* CGRAMにⅡを書き込む */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 0 1 0 1 0 ---> 0x0A */
    /* 0 0 0 0 1 0 1 0 ---> 0x0A */
    /* 0 0 0 0 1 0 1 0 ---> 0x0A */
    /* 0 0 0 0 1 0 1 0 ---> 0x0A */
    /* 0 0 0 0 1 0 1 0 ---> 0x0A */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 0 0 0 0 0 ---> 0x00 */
    {0x1F, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x1F, 0x00},
    
    /* CGRAMにⅢを書き込む */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 0 0 0 0 0 ---> 0x00 */
    {0x1F, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x00},
    
    /* CGRAMにⅣを書き込む */
    /* 0 0 0 1 1 1 1 1 ---> 0x1F */
    /* 0 0 0 1 1 0 0 1 ---> 0x19 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 1 0 1 ---> 0x15 */
    /* 0 0 0 1 0 0 1 0 ---> 0x12 */
    /* 0 0 0 1 0 0 1 0 ---> 0x12 */
    /* 0 0 0 1 0 0 1 0 ---> 0x12 */
    /* 0 0 0 0 0 0 0 0 ---> 0x00 */
    {0x1F, 0x19, 0x15, 0x15, 0x12, 0x12, 0x12, 0x00}
};
#endif

#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/15 */
/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1999/06/16
*             TYPE:  CONST
*      VAR TO HOLD:
*      DESCRIPTION:  絵文字のフォントパターン
*          COMMENT:  サイズは１６(縦)ｘ１６(横)です
************************************************************************/
CONST UBYTE	LCD_PictureFontPattern[][32] = {
	{					/* Ｆ０：画面区切り線 */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80		/* ・・・・・・・ＯＯ・・・・・・・ */
	}, {				/* Ｆ１：縦原稿 */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x3f, 0x80,		/* ・・ＯＯＯＯＯＯＯ・・・・・・・ */
		0x20, 0x80,		/* ・・Ｏ・・・・・Ｏ・・・・・・・ */
		0x20, 0x80,		/* ・・Ｏ・・・・・Ｏ・・・・・・・ */
		0x20, 0x80,		/* ・・Ｏ・・・・・Ｏ・・・・・・・ */
		0x20, 0x80,		/* ・・Ｏ・・・・・Ｏ・・・・・・・ */
		0x20, 0x80,		/* ・・Ｏ・・・・・Ｏ・・・・・・・ */
		0x20, 0x80,		/* ・・Ｏ・・・・・Ｏ・・・・・・・ */
		0x27, 0x80,		/* ・・Ｏ・・ＯＯＯＯ・・・・・・・ */
		0x27, 0x00,		/* ・・Ｏ・・ＯＯＯ・・・・・・・・ */
		0x26, 0x00,		/* ・・Ｏ・・ＯＯ・・・・・・・・・ */
		0x3c, 0x00,		/* ・・ＯＯＯＯ・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00 		/* ・・・・・・・・・・・・・・・・ */
	}, {				/* Ｆ２：濃度（左端） */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x30,		/* ・・・・・・・・・・ＯＯ・・・・ */
		0x00, 0x50,		/* ・・・・・・・・・Ｏ・Ｏ・・・・ */
		0x00, 0x90,		/* ・・・・・・・・Ｏ・・Ｏ・・・・ */
		0x01, 0x10,		/* ・・・・・・・Ｏ・・・Ｏ・・・・ */
		0x02, 0x10,		/* ・・・・・・Ｏ・・・・Ｏ・・・・ */
		0x04, 0x10,		/* ・・・・・Ｏ・・・・・Ｏ・・・・ */
		0x08, 0x10,		/* ・・・・Ｏ・・・・・・Ｏ・・・・ */
		0x04, 0x10,		/* ・・・・・Ｏ・・・・・Ｏ・・・・ */
		0x02, 0x10,		/* ・・・・・・Ｏ・・・・Ｏ・・・・ */
		0x01, 0x10,		/* ・・・・・・・Ｏ・・・Ｏ・・・・ */
		0x00, 0x90,		/* ・・・・・・・・Ｏ・・Ｏ・・・・ */
		0x00, 0x50,		/* ・・・・・・・・・Ｏ・Ｏ・・・・ */
		0x00, 0x30,		/* ・・・・・・・・・・ＯＯ・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00 		/* ・・・・・・・・・・・・・・・・ */
	}, {				/* Ｆ３：濃度（薄く・やや薄く・やや濃く・濃くの位置） */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00 		/* ・・・・・・・・・・・・・・・・ */
	}, {				/* Ｆ４：濃度（普通） */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x01, 0x80,		/* ・・・・・・・ＯＯ・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00 		/* ・・・・・・・・・・・・・・・・ */
	}, {				/* Ｆ５：濃度（右端） */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x0C, 0x00,		/* ・・・・ＯＯ・・・・・・・・・・ */
		0x0E, 0x00,		/* ・・・・ＯＯＯ・・・・・・・・・ */
		0x0F, 0x00,		/* ・・・・ＯＯＯＯ・・・・・・・・ */
		0x0F, 0x80,		/* ・・・・ＯＯＯＯＯ・・・・・・・ */
		0x0F, 0xC0,		/* ・・・・ＯＯＯＯＯＯ・・・・・・ */
		0x0F, 0xE0,		/* ・・・・ＯＯＯＯＯＯＯ・・・・・ */
		0x0F, 0xF0,		/* ・・・・ＯＯＯＯＯＯＯＯ・・・・ */
		0x0F, 0xE0,		/* ・・・・ＯＯＯＯＯＯＯ・・・・・ */
		0x0F, 0xC0,		/* ・・・・ＯＯＯＯＯＯ・・・・・・ */
		0x0F, 0x80,		/* ・・・・ＯＯＯＯＯ・・・・・・・ */
		0x0F, 0x00,		/* ・・・・ＯＯＯＯ・・・・・・・・ */
		0x0E, 0x00,		/* ・・・・ＯＯＯ・・・・・・・・・ */
		0x0C, 0x00,		/* ・・・・ＯＯ・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00 		/* ・・・・・・・・・・・・・・・・ */
	}, {				/* Ｆ６：濃度（設定値） */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x03, 0xC0,		/* ・・・・・・ＯＯＯＯ・・・・・・ */
		0x03, 0xC0,		/* ・・・・・・ＯＯＯＯ・・・・・・ */
		0x03, 0xC0,		/* ・・・・・・ＯＯＯＯ・・・・・・ */
		0x03, 0xC0,		/* ・・・・・・ＯＯＯＯ・・・・・・ */
		0x03, 0xC0,		/* ・・・・・・ＯＯＯＯ・・・・・・ */
		0x03, 0xC0,		/* ・・・・・・ＯＯＯＯ・・・・・・ */
		0x03, 0xC0,		/* ・・・・・・ＯＯＯＯ・・・・・・ */
		0x03, 0xC0,		/* ・・・・・・ＯＯＯＯ・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00 		/* ・・・・・・・・・・・・・・・・ */
	}, {				/* Ｆ７：ボリューム（小） */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00 		/* ・・・・・・・・・・・・・・・・ */
	}, {				/* Ｆ８：ボリューム（中） */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00 		/* ・・・・・・・・・・・・・・・・ */
	}, {				/* Ｆ９：ボリューム（大） */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x3F, 0xFC,		/* ・・ＯＯＯＯＯＯＯＯＯＯＯＯ・・ */
		0x00, 0x00,		/* ・・・・・・・・・・・・・・・・ */
		0x00, 0x00 		/* ・・・・・・・・・・・・・・・・ */
	}
};
#endif	/* (PRO_ANK_TO_KANJI == ENABLE) */
