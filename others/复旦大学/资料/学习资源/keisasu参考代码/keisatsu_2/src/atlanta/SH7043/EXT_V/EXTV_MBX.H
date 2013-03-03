/* extv_mbxno.c */

/* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚hˆÈ~‚Ì‹@í‚ÍAƒ}ƒXƒNƒvƒƒOƒ‰ƒ€•ÏX
** by O.Kimoto 1998/09/12
*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#else

#ifndef DEF_MBXN
#include  "\src\atlanta\sh7043\define\def_mbxn.h"
#endif

extern struct mbxno_data_t  mbxno;

#endif
