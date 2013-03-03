/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : defv_fnc.c.h                                              */
/*  作成者       : 木元修                                                    */
/*  日  付       : 1998/08/24                                                */
/*  概  要       : ＣＰＵ初期化関数間接参照用ポインター宣言                  */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)

void InitializeCPU(void);
void InitializeSystem(void);

#pragma section INIVEC /* locate section name "CINIVEC" */

CONST void (* CONST InitializeCPU_vec)() = (void (*)())InitializeCPU;
CONST void (* CONST InitializeSystem_vec)() = (void (*)())InitializeSystem;

#pragma section
#else
#endif

