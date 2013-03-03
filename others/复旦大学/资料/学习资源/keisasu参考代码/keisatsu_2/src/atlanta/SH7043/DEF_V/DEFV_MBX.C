/* defv_mbxno.h */
/* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚hˆÈ~‚Ì‹@í‚ÍAƒ}ƒXƒNƒvƒƒOƒ‰ƒ€•ÏX
** by O.Kimoto 1998/09/12
*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\def_v\defv_mbx.c"
#else

#ifndef DEF_MBXN
#include  "\src\atlanta\sh7043\define\def_mbxn.h"
#endif

#pragma section MONMBXNO /* locate section name "DMONMBXNO" */

struct mbxno_data_t mbxno = {0};

#pragma section

#endif

