#ifndef _MYCPACK_H
#define _MYCPACK_H
#include "cpack.h"
int getCpackFieldValue(ST_CPACK *cpack,const char* fieldName,char *fieldVal);
int setCpackFieldValue(ST_CPACK *cpack,const char* fieldName,const char* fieldVal);
void printCpackFieldValue(ST_CPACK *cpack);
#endif
