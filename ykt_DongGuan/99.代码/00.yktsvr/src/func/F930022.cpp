/* --------------------------------------------
 * ��������: F930022.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������:�ɼ��ֽ��ֵ�������ˮ����ʷ��
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
#include "busqc.h"

int F930022(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
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
	AddXmlItemInt(tMsgList.reqdata,XML_KEY_FEETYPE,in_pack->lvol4);
	AddXmlItemInt(tMsgList.reqdata,XML_KEY_STARTNUM,in_pack->lvol5);
	AddXmlItemInt(tMsgList.reqdata,XML_KEY_ENDNUM,in_pack->lvol6);

	if((ret = get_devinfo_by_phyid(in_pack->sdate0,&tDevice)))
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tMsgList.deviceid = tDevice.deviceid;
	tMsgList.funcno = 930022;
	tMsgList.msglevel = 3;
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





