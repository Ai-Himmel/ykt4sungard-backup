/* --------------------------------------------
* ��������: F930121.c
* ��������: 2005-10-27
* ��������: ����
* �汾��Ϣ: 1.0.0.0
* ������:�´��Ž�������汾
* --------------------------------------------
* �޸�����:
* �޸���Ա:
* �޸�����:
* �汾��Ϣ:
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

int F930121(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	//AddXmlItemInt(tMesList.incontent,XML_KEY_FTFLAG,in_pack->lvol5);

	ret = process930121(in_pack->lvol3,in_pack->lvol5,in_pack->sserial0,in_pack->sdate0);
	if(ret)
	{
		*pRetCode = ret;
		return -1;
	}
	return 0;
}

