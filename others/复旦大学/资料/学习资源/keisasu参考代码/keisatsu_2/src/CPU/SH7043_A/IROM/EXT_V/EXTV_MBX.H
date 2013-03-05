/* extv_mbxno.c */
#ifndef EXTV_MBX
#define EXTV_MBX 1

#if (PRO_CPU_VERSION == SH7043_A)
#include  "\src\cpu\sh7043_a\irom\define\def_mbxn.h"
#else
#include  "\src\atlanta\sh7043\define\def_mbxn.h"
#endif

extern struct mbxno_data_t  mbxno;

#endif
