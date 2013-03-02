/* --------------------------------------------
 * ��������: F240022.cpp
 * ��������: 2009-12-23
 * ��������: �����
 * �汾��Ϣ: 1.0.0.0
 * ������: Ȧ��д��ʧ�ܳ���
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "transcode.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"
#include "bupub.h"
#include "svrlink.h"

int F850001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

int F240022(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;	
	T_t_refno tRefno;
	memset(&tRefno,0,sizeof tRefno);

	// һ��ͨ����
	ret = F850001(handle,iRequest,rPack,pRetCode,szMsg);
	if(ret)
		return ret;

	ret = DB_t_refno_read_lock_by_c0_and_refno(rPack->sphone3,&tRefno);
	if(ret)
	{
		DB_t_refno_free_lock_by_c0();
		return E_DB_REFNO_R;
	}

	// mac У���� 850001 �Ѿ�У�����
	tRefno.status = RS_YKTREVSUCC;
	ret = DB_t_refno_update_lock_by_c0(&tRefno);
	if(ret)
		return E_DB_REFNO_U;
	return 0;
		
}

