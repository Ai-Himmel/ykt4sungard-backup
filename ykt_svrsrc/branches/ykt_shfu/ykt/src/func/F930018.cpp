/* --------------------------------------------
 * ��������: F930018.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������:�ɼ��ֽ��ֵ��ˮ����ʷ��
 * --------------------------------------------
 * �޸�����:2004-12-14
 * �޸���Ա:	�Ž�
 * �޸�����: �޸�ҵ���߼�
 * �汾��Ϣ:1.0.0.1
 * ��ע��Ϣ:
 * --------------------------------------------*/
#define _IN_SQC_                    
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "fdsqc.h"

int F930018(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
    T_t_tif_meslist tMesList;
	T_t_pif_device tDevice;

	memset(&tMesList,0,sizeof(tMesList));
	memset(&tDevice,0,sizeof tDevice);

	if(in_pack->lcert_code < 1)
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
	}
	else if((ret = DB_t_pif_device_read_by_device_id(in_pack->lcert_code,&tDevice)))
	{
		*pRetCode = E_DB_DEVICE_N;
	}
	else
	{
		AddXmlItemInt(tMesList.incontent,XML_KEY_TIME, in_pack->lvol4);
		tMesList.devid = tDevice.device_id;
		tMesList.funid = 930018;
		tMesList.level = 1;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			goto L_RETU;
		}
		return 0;
	}
L_RETU:
	return  -1;		
}





