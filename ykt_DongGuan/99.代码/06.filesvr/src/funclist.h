#ifndef _FUNCLIST_H_
#define _FUNCLIST_H_
#include "filesvr.h"

typedef struct
{
	int requestType;
	int (*func)(BCCHandle &handle, char *szMsg);
}FUNCDef_t;

#define DEF_FUNC(x) extern int F##x(BCCHandle &handle, char *szMsg)
#define NEW_FUNC(x) {x,F##x}


DEF_FUNC(950998);
DEF_FUNC(950999);
DEF_FUNC(9001);

FUNCDef_t g_functions[]=
{
	NEW_FUNC(950998),
	NEW_FUNC(950999),
	NEW_FUNC(9001),
};

#endif // _FUNCLIST_H_