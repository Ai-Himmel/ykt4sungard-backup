#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "bupub.h"
#include "deposit.h"
#include "logfile.h"

#ifdef __cplusplus
extern "C" {
#endif

int netfee_trans(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg);

#ifdef __cplusplus
}
#endif