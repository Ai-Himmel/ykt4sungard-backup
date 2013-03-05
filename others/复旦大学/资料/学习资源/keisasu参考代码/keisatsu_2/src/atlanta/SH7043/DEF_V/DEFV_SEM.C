/* defv_semno.c */
#ifndef defv_semc

/* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚hˆÈ~‚Ì‹@í‚ÍAƒ}ƒXƒNƒvƒƒOƒ‰ƒ€•ÏX
** by O.Kimoto 1998/09/12
*/

#include  "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\def_v\defv_sem.c"
#else

#ifndef DEF_SEMN
#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\sh7043\define\def_semn.h"
#endif

#pragma section MONSEMNO /* locate section name "DMONSEMNO" */

struct semno_data_t  semno = {0};

#pragma section
#endif

#endif
