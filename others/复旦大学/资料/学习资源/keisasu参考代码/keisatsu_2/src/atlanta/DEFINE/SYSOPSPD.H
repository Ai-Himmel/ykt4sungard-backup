/* By Y.Suzuki 1996/10/15 */
/* Original File : jun\usr2:\src\kobe\anzu\define\sysopspd.h */
#ifndef sysopspd_h
	#define sysopspd_h

/***********************************************************************
 * 任意短縮番号オペレーション用管理テーブル                            *
 * struct SYS_OptionalSpeedTable_t SYB_OptionalSpeed[SYS_SPEED_DIAL_MAX] *
 * 1995/02/09                                                          *
 * 野瀬敏弘                                                            *
 ***********************************************************************/
struct SYS_OptionalSpeedTable_t {
	UWORD	Number;					/* 発信に使用する任意の短縮番号 */
	UBYTE	Record;					/* SYB_SpeedDial[]の配列番号    */
};

#endif
