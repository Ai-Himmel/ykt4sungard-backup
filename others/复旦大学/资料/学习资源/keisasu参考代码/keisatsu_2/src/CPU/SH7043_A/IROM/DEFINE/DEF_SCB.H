#ifndef def_scb2_h
	#define def_scb2_h 1

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
