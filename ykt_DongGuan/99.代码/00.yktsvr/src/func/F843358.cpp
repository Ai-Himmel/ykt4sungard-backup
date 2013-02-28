/* --------------------------------------------
 * ��������: F843358.sqC
 * ��������: 2007-11-02
 * ��������:�Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ��ֵ����Ա���
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
#include "acctrans.h"

int F843358(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	des2src(ats.trans.opercode,rPack->semp);
	ats.trans.transcode=MAKETRANSCODEADD(TCM_DEPOSITOPER);	
	ret=ats.InitTrans();
	if(ret)
		return ret;			

	T_t_dpsoper tDepositOper;

	memset(&tDepositOper,0,sizeof(tDepositOper));

	//��Ӳ���Ա
	des2src(tDepositOper.opercode,rPack->scust_auth);
	tDepositOper.maxdepositamt=rPack->damt0;
	tDepositOper.status[0]=rPack->sstatus1[0];
	tDepositOper.devlimitflag[0]=rPack->sstatus2[0];
	tDepositOper.shopoperflag[0]=rPack->sstatus3[0];
	if(tDepositOper.shopoperflag[0]=='1')
	{
		if(tDepositOper.devlimitflag[0]!='1');
		{
			return E_DEPOSITSHOPOPER_MUST_LIMITDEV;
		}
	}
	getsysdate(tDepositOper.opendate);
	des2src(tDepositOper.lastsaved,CAccTrans::GetInst().hostdatetime);
	ret=DB_t_dpsoper_add(&tDepositOper);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_DEPOSITOPER_E;
		else	
			return E_DB_DEPOSITOPER_I;
	}
	return 0;
}
