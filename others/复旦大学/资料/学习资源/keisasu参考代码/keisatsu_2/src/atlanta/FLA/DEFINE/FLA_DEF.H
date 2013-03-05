/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : fla_def.h                                                 */
/*  作成者   	   桑原美紀                                                  */
/*  日  付       : 1997/04/23                                                */
/*  概  要       : フラッシュメモリ					     	                 */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#ifndef FLA_DEF_H
 #define FLA_DEF_H	1

/* Unlock cycle */	
#define	FIRST_ADDR			0x5555
#define	SECOND_ADDR			0x2AAA
#define	THIRD_ADDR			0x5555
#define	FOURTH_ADDR			0x5555
#define	FIFTH_ADDR			0x2AAA
#define	SIXTH_ADDR			0x5555

#define	FIRST_DATA			0xAA
#define	SECOND_DATA			0x55

/* Command */
#define	RESET_COMMAND		0xF0
#define	AUTOSELECT_COMMAND	0x90
#define	PROGRAM_COMMAND		0xA0
#define	ERASE_SETUP_COMMAND	0x80
#define	SECTOR_ERASE_COMMAND		0x30
#define	CHIP_ERASE_COMMAND	0x10
#define	SUSPEND_COMMAND		0xB0
#define	RESUME_COMMAND		0x30

/* Address Offset for Autoselect */
#define	MANUFACTURE_OFFSET	0x00
#define	DEVICE_OFFSET		0x01

/* Polling Bit */
#define	DATA_POLLING_BIT	0x80
#define	TOGGLE_BIT			0x40
#define	HANGUP_BIT			0x20

#define	BLANK_DATA			0xFFFFF
#define FLASH_MEM			0x200000L
#if defined(POPLAR_L) || defined(POPLAR_N) 
	#define	MASTER_MEM			0x1000000L
#endif
#if defined(POPLAR_B) || defined(POPLR_BN) || defined(POPLAR_H) || defined(ANZU_L) || defined(ANZU_V) || defined(SAKAKI) || defined(HINOKI) || defined(POPLAR_F) || defined(HINOKI2) || defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) || defined(KEISATSU)
	/* HINOKI2 2001/11/13 T.Takagi */
	#define	MASTER_MEM			0x1100000L
#endif
#define	FLASH_BOOT_AREA_MAX		0x2000

#define	SECTOR_MAX			19

/* Flag Table */
#define	PASS_FLAG				0
#define	FAIL_FLAG				1
#define	ERROR_FLAG_AUTOSELECT	2
#define	ERROR_FLAG_CHIP_ERASE	3
#define	ERROR_FLAG_SECTOR_ERASE	4
#define	ERROR_FLAG_PROGRAM		5
#define	ERROR_FLAG_SUMCHECK		6
#define ERROR_FLAG_TIMEOVER		7

/****************************************************************
*	ROM_MAPテーブル												*
*		プログラムデータ（ＲＯＭデータ）を６４Ｋバイト単位に	*
*		アドレスの指定が可能になっている						*
****************************************************************/
struct	ROM_MAP_t {
	UDWORD	StartAddress;		/* 開始アドレス */
	UBYTE	Status;				/* 使用状況 */
	UBYTE	Dummy;				/* ダミー */
	UWORD	Size;				/* プログラムサイズ */
};

/****************************************************************
*	ＲＯＭ＿ＭＡＰテーブルの使用状況							*
****************************************************************/
#define	NOT_ROM_USE	0
#define	ROM_USE		1

#define OVER_ERASE_COUNT_MAX	10	/* オーバイレーズ是正回数  1998/04/13 by T.Soneoka */

#endif
