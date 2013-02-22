#ifndef _KSBU_H_
#define _KSBU_H_
#ifdef __cplusplus
extern "C" {
#endif#include "cpack.h"
int CopyHeadCol(ST_PACK* rPack,ST_CPACK* sPack);
int ERR_DEAL(char *msg,int retcode);

#ifdef __cplusplus
}
#endif

#endif // _KSBU_H_
