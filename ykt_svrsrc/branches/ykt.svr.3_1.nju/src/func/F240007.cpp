/* --------------------------------------------
 * ��������: F240007.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: ��Ӧǰ�û�������,�������ж����ļ����ж���
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"



int F240007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
/*
	ret=DB_t_device_update_by_subsystem_type(SUBSYSTYPE_KEEP,SUBSYSSTAT_OFFLINE);
	if(ret)
	{
		*pRetCode=E_DB_DEVICE_U;
		writelog(LOG_ERR,"�����豸״̬ʧ��,errcode=[%d]",ret);
		goto L_RETU;
	}
*/
	return 0;
}


