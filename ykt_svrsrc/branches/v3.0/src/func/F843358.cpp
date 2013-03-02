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
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=MAKETRANSCODEADD(TCM_DEPOSITOPER);	
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			

	T_t_depositoper tDepositOper;

	memset(&tDepositOper,0,sizeof(tDepositOper));

	//��Ӳ���Ա
	des2src(tDepositOper.opercode,rPack->scust_auth);
	tDepositOper.maxdepositamt=rPack->damt0;
	tDepositOper.status[0]=STATUS_NORMAL;
	des2src(tDepositOper.devlimitflag,rPack->sstatus2);
	des2src(tDepositOper.shopoperflag,rPack->sstatus3);	
	if(tDepositOper.shopoperflag[0]=='1')
	{
		if(tDepositOper.devlimitflag[0]!='1');
		{
			return E_DEPOSITSHOPOPER_MUST_LIMITDEV;
		}
	}
	getsysdate(tDepositOper.opendate);
	getfmtsysdatetime(tDepositOper.lastsaved);
	ret=DB_t_depositoper_add(&tDepositOper);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_DEPOSITOPER_E;
		else	
			return E_DB_DEPOSITOPER_I;
	}
	return 0;
}
