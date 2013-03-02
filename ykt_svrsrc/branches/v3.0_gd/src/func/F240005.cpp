/* --------------------------------------------
 * ��������: F240005.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: ����ȷ��
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



int F240005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;

	T_t_refno tRefno;
	memset(&tRefno,0,sizeof tRefno);

	ret = DB_t_refno_read_lock_by_c0_and_refno(rPack->sholder_ac_no,&tRefno);
	if(ret)
	{
		DB_t_refno_free_lock_by_c0();
		if(DB_NOTFOUND == ret)
			return E_DB_REFNO_N;
		return E_DB_REFNO_R;
	}
	if(strcmp(tRefno.mac,rPack->sdate1) !=0)
	{
		DB_t_refno_free_lock_by_c0();
		return E_MAC_FAIL;
	}	
	
	tRefno.status = RS_REVSUCC;	
	ret = DB_t_refno_update_lock_by_c0(&tRefno);
	if(ret)
		return E_DB_REFNO_U;
	

	return 0;
}


