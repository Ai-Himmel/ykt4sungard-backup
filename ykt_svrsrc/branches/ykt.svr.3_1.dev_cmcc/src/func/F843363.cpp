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
#include "busqc.h"
#include "acctrans.h"

int F843363(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=MAKETRANSCODEDEL(TCM_DEPOSITOPERPOS);
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	int deviceid=atoi(rPack->vsvarstr1);
	ret=DB_t_dpsoperpos_del_by_opercode_and_deviceid(rPack->scust_auth,deviceid);
	if(ret)
	{
		writelog(LOG_ERR,"oper[%s]device_id[%d]",rPack->scust_auth,deviceid);
		if(DB_NOTFOUND==ret)
			return E_DB_DEPOSITOPERPOS_N;
		else
			return E_DB_DEPOSITOPERPOS_D;
	}
	return 0;
}
