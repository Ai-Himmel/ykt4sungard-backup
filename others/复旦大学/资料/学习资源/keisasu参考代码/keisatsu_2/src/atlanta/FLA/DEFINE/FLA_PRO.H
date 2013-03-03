/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : fla_pro.h                                                 */
/*  作成者   	   桑原美紀                                                  */
/*  日  付       : 1997/04/23                                                */
/*  概  要       : フラッシュメモリ					     	                 */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#ifndef FLA_PRO_H
 #define FLA_PRO_H	1

/* Function */
void  FlashMainControl(void);
void  FlashMemoryCheck(void);
UBYTE Main_Function( void );
UBYTE Reset0_Function( void );
UBYTE Reset1_Function( void );
UBYTE Autoselect_Function( 
				UWORD *manufacture_code, 
				UWORD *device_code );
UBYTE Program_Function( 
				UWORD *addr, 
				UWORD data );
UBYTE Sector_Erase_Function( 
				UWORD *addr );
UBYTE Chip_Erase_Function( void );
UBYTE Erase_Suspend_Function( void );
UBYTE Erase_Resume_Function( void );

/* Polling Check */
UBYTE Data_Polling_Check( 
				UWORD  *addr, 
				UWORD data );
UBYTE Toggle_Bit_Check( 
				UWORD *addr );

/* DataCount Check */
/*UWORD	GetWordSumCheck( void );*/
UWORD	GetWordSumCheck( 
				UWORD *Rom0_sum,
				UWORD *Rom1_sum );

UBYTE OverErase_Function(UWORD	*addr, UDWORD data);
#endif
