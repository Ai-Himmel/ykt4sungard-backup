/* --------------------------------------------
 * ��������: F930109.c
 * ��������: 2005-09-02
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:�´���ʱ���ڼ���
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
#include "busqc.h"

int F930109(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	T_t_msglist tMsgList;
	T_t_device tDevice;
	memset(&tDevice,0,sizeof tDevice);

	memset(&tMsgList,0,sizeof(tMsgList));

	if(strlen(in_pack->sdate0)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	AddXmlItemInt(tMsgList.reqdata,XML_KEY_OUTNUM,in_pack->lvol5);		//����
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_HOLIDAY,in_pack->vsvarstr0);	//�ڼ���
	//FIXME
	//��Ҫ��ѯ�ڼ��ձ��´�
	//FIXME
	if((ret = get_devinfo_by_phyid(in_pack->sdate0,&tDevice)))
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tMsgList.deviceid = tDevice.deviceid;
	tMsgList.funcno = 930109;
	tMsgList.msglevel =1;
	tMsgList.maxsendcnt = 10;
	ret = DB_t_msglist_del_by_devid_and_funid(tMsgList.deviceid,tMsgList.funcno);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
		{
			return E_DB_MSGLIST_D;
		}
	}
	ret=AddMsgLst(&tMsgList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	return 0;
L_RETU:
	return  -1;
}





