/* defv_semno.c */
#ifndef defv_semc

#include  "\src\atlanta\define\product.h"

#ifndef DEF_SEMN

#include  "\src\atlanta\sh7043\define\def_semn.h"

#endif

#pragma section MONSEMNO /* locate section name "DMONSEMNO" */

struct semno_data_t  semno = {0};

#pragma section
#endif
