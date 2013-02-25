#ifndef _BUFUNC_H
#define _BUFUNC_H

#include "cpack.h"
#include "mypub.h"
#include "bupub.h"
#include "svrlink.h"
#include "XPack.h"
#include "BUShm.h"


int GetCpackDataString(ST_CPACK *cpack,char *buf);
int GetCpackDataString(ST_PACK *pack,char *buf);
int SetHeadCol(ST_CPACK *cpack, ...);
int CopyHeadCol(ST_PACK* rPack,ST_CPACK* sPack);
void GetTransHandle(void *handle, char *pTransHandle);
void SetTransHandle(void *handle,char *pTransHandle);

#endif
