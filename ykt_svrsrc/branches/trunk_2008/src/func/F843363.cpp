/* --------------------------------------------
 * ��������: F843363.sqC
 * ��������: 2007-11-02
 * ��������:�Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ��ֵ����Ա�豸ɾ��
 * --------------------------------------------
 * �޸�����: 
 * �޸���Ա: 
 * �޸�����: 
 * �汾��Ϣ: 
 * ��ע��Ϣ: 
 * --------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "fdsqc.h"

int F843363(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ret=DB_t_deposit_operpos_del_by_oper_code_and_device_id(rPack->scust_auth,rPack->vsvarstr1);
	if(ret)
	{
		writelog(LOG_ERR,"oper[%s]device_id[%s]",rPack->scust_auth,rPack->vsvarstr1);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_DEPOSIT_OPERPOS_N;
		else
			*pRetCode=E_DB_DEPOSIT_OPERPOS_D;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
