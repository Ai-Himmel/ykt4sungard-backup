#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\ext_v\alrptbl.h"
#else
#include "\src\atlanta\scd\ext_v\alrptbl.h"
#endif

/*アリロ スクランブルモジュール呼出し By Y.Suzuki 1998/03/11 */
#define AlirooScramble  (*alrscramble_adr_tbl)

/*アリロ デスクランブルモジュール呼出し By Y.Suzuki 1998/03/11 */
#define AlirooDescramble (*alrdescramble_adr_tbl)

