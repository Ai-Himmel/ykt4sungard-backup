/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\def_scb.h"
#else
#ifndef def_scb_h
	#define def_scb_h

/*****************************************************************************
	struct scb_table_data_t scb[SEMNO_MAX];
	scb[].stat
		0xFF		:未使用（クリエイトされていない）
		0x7F		:セマフォ待ちタスク無し
		0x00-0x7E	:セマフォ待ちタスク有り
	scb[].tid
		0xFF		:セマフォ値１(1XXXXXXXB)
		0x00-0x7E	:セマフォ値０(0XXXXXXXB)
*****************************************************************************/

struct scb_table_data_t {
	UBYTE stat;
	UBYTE tid;
};

#endif

#endif
