/* --------------------------------------------
 * ��������: F240006.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: ǰ�û���̨ǩ��,ÿ�ε�¼���к�,
 			��Ҫ�������̨ǩ��.��̨���ڽ��豸ǩ��,��֤�豸���¸�����Կ
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
#include "account.h"
#include "fdsqc.h"



int F240006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	
	ret=DB_t_pif_device_update_by_subsystem_type(SUBSYSTYPE_KEEP,SUBSYSSTAT_OFFLINE);
	if(ret)
	{
		*pRetCode=E_DB_DEVICE_U;
		writelog(LOG_ERR,"�����豸״̬ʧ��,errcode=[%d]",ret);
		goto L_RETU;
	}

	return 0;
L_RETU:
	return ret;
}


