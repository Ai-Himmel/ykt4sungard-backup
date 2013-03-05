/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : extv_fnc.c.h                                              */
/*  作成者       : 野瀬敏弘                                                  */
/*  日  付       : 1997/01/14                                                */
/*  概  要       : モニタコールアドレステーブル外部参照                      */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#ifndef EXTV_FNC
	#define EXTV_FNC 1

#include "\src\atlanta\define\product.h"

extern CONST void (* CONST MonitorCallVoid[])();
extern CONST WORD (* CONST MonitorCallWORD[])();

#endif
