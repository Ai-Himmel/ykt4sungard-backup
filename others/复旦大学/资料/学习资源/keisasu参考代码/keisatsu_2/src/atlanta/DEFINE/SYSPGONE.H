#ifndef syspgone_h
	#define syspgone_h

#include "\src\atlanta\define\syscomf.h"

/************************************************************************
 * プログラムワンタッチ拡張版用データ									*
 * extern struct SYS_ProgramOnetouchData_t SYB_ProgramOnetouch			*
 * 1998/08/04															*
 * 桑原美紀																*
 ************************************************************************/
struct SYS_ProgramOnetouchData_t {
	UBYTE  Item;							/* 登録内容の種類			*/
	union  EntryData_t {					/** 登録内容			   **/
		struct SYS_CommandData_t Command;	/* 通信予約データ			*/
		struct StoreData_t {				/** 蓄積用データ		   **/
			UBYTE Item;						/* 蓄積原稿種別				*/
			UBYTE AddType;					/* Fｺｰﾄﾞ原稿蓄積の上書きON/OFF	*/
			UWORD Point;					/* 蓄積BOX番号				*/
		}StoreData;
		UBYTE  ListItem;					/* リスト種別				*/
	}EntryData;
	UBYTE TxModeSW;							/* 送信モード(画質)			*/
	UBYTE ContrastSW;						/* 濃度						*/
	UBYTE StampSW;							/* 済スタンプ				*/
	UBYTE MemoryTxSW;						/* メモリ／スキャナ送信		*/
	UBYTE ConfirmSW;						/* 通信証					*/
	UBYTE Reserve1;							/* ダミー１					*/
	UBYTE Reserve2;							/* ダミー２					*/
	UBYTE Reserve3;							/* ダミー３					*/
	UBYTE Reserve4;							/* ダミー４					*/
};

/************************************************************************
 * プログラムワンタッチ登録内容の種類									*
 * extern UBYTE SYB_ProgramOnetouch[].Item								*
 * 1998/08/04															*
 * 桑原美紀																*
 ************************************************************************/
#define SYS_PROGRAM_EMPTY			0		/* 未使用			*/
#define SYS_PROGRAM_COMMAND			1		/* 通信予約			*/
#define SYS_PROGRAM_LIST			2		/* リスト			*/
#define SYS_PROGRAM_STORE			3		/* 蓄積				*/

#endif
