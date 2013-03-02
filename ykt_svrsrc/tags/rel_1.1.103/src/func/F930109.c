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
#include "fdsqc.h"

int F930109(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	T_t_tif_meslist tMesList;

	memset(&tMesList,0,sizeof(tMesList));

	des2src(tMesList.devphy999_id, in_pack->sdate0);
	trim(tMesList.devphy999_id);
	if(strlen(tMesList.devphy999_id)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	AddXmlItemInt(tMesList.incontent,XML_KEY_OUTNUM,in_pack->lvol5);		//����
	AddXmlItemStr(tMesList.incontent,XML_KEY_HOLIDAY,in_pack->vsvarstr0);	//�ڼ���
	//FIXME
	//��Ҫ��ѯ�ڼ��ձ��´�
	//FIXME
	tMesList.funid = 930109;
	tMesList.level =1;
	tMesList.max_send_cnt = 10;
	ret = DB_t_tif_meslist_del_by_devphy999_id_and_funid(tMesList.devphy999_id,tMesList.funid);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
		{
			return E_DB_MESLIST_D;
		}
	}
	ret=AddMsgLst(&tMesList);
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





