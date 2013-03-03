/* extv_semno.c */
#ifndef EXTV_SEM_H
#define EXTV_SEM_H 1

#if (PRO_CPU_VERSION == SH7043_A)
#include  "\src\cpu\sh7043_a\irom\define\def_semn.h"
#else
#include  "\src\atlanta\sh7043\define\def_semn.h"
#endif

extern struct semno_data_t  semno;

#endif
