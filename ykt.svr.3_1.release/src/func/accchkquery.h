/* --------------------------------------------
 * ��������: 2009-08-24
 * ��������: �����
 * �汾��Ϣ: 1.0.0.0
 * ������: ���˽����ѯ
 * --------------------------------------------*/
#ifndef ACC_CHKQUERY_H_
#define ACC_CHKQUERY_H_

#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "busqc.h"
#include "bupub.h"


// Ȧ����˽����ѯ
int bankaccchkquery(TRUSERID *handle,ST_PACK *in_pack,ST_PACK *out_pack,int *pRetCode,char *szMsg);
int mobileaccchkquery(TRUSERID *handle,ST_PACK *in_pack,ST_PACK *out_pack,int *pRetCode,char *szMsg);
#endif

