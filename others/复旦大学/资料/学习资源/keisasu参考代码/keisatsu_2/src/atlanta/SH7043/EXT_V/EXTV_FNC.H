/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : extv_fnc.c.h                                              */
/*  作成者       : 野瀬敏弘                                                  */
/*  日  付       : 1997/01/14                                                */
/*  概  要       : モニタコールアドレステーブル外部参照                      */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\ext_v\extv_fnc.h"
#else

extern CONST void (* CONST MonitorCallVoid[])();
extern CONST WORD (* CONST MonitorCallWORD[])();

#endif
