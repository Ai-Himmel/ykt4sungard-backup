/* extv_semno.c */
/* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚hˆÈ~‚Ì‹@í‚ÍAƒ}ƒXƒNƒvƒƒOƒ‰ƒ€•ÏX
** by O.Kimoto 1998/09/12
*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\ext_v\extv_sem.h"
#else

#ifndef EXTV_SEM_H
#define EXTV_SEM_H 1

#include  "\src\atlanta\sh7043\define\def_semn.h"

extern struct semno_data_t  semno;

#endif

#endif
