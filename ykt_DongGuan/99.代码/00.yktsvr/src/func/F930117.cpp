/* --------------------------------------------
* ��������: F930117.c
* ��������: 2005-09-02
* ��������: �Ž�
* �汾��Ϣ: 1.0.0.0
* ������:�´��Ž�����
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
#include "dbfunc_foo.h"
#include "busqc.h"

int F930117(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	/*
	int ret = 0;
	T_t_doordevcardlist tCardlist;
	

	memset(&tCardlist,0,sizeof tCardlist);


	des2src(tCardlist.deviceid, in_pack->sdate0);
	tCardlist.cardno = in_pack->lvol3;

	//AddXmlItemInt(tMsgList.reqdata,XML_KEY_FTFLAG,in_pack->lvol5);

	ret = process930117(&tCardlist,in_pack->lvol5);
	if(ret)
	{
		*pRetCode = ret;
		return -1;
	}
	*/
	return 0;
}

