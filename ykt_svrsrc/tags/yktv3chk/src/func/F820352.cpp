/* --------------------------------------------
 * ��������: 2008-05-29
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ����Աǩ��
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
#include "busqc.h"

int F820352(TRUSERID * handle, int iRequest, ST_PACK * in_pack, int *pRetCode, char *szMsg)
{

	int ret=0;
	T_t_operator tOperator;

	memset(&tOperator,0,sizeof(tOperator));
	ret=DB_t_operator_read_by_opercode(in_pack->scust_no,&tOperator);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_OPER_NOT_EXIST;
		else
			return E_DB_OPERATOR_R;
	}
	tOperator.loginflag[0]='0';
	getfmtsysdatetime(tOperator.logouttime);
	ret=DB_t_operator_update_by_opercode(tOperator.opercode,&tOperator);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			return E_OPER_NOT_EXIST;
		}
		else
		{
			return E_DB_OPERATOR_U;
		}
	}
	return 0;
}
