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
#include "fdsqc.h"

int F930117(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
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
	if(in_pack->lvol3<1)
	{
		*pRetCode=E_INPUT_CARDNO_CANNOT_NULL;
		goto L_RETU;
	}
	tMesList.funid =930117;
	tMesList.level =2;
	tMesList.card_no=in_pack->lvol3;
	tMesList.max_send_cnt=100000;
	tMesList.del_flag[0]='0';

	AddXmlItemInt(tMesList.incontent,XML_KEY_CARDID,in_pack->lvol3);
	AddXmlItemInt(tMesList.incontent,XML_KEY_FTFLAG,in_pack->lvol5);

	//ɾ�����е�����
	ret=DB_t_tif_meslist_del_by_card_no_and_devphy999_id_and_funid(tMesList.card_no,tMesList.devphy999_id,iRequest);
	if(ret)
	{
		if(ret!=DB_NOTFOUND)
		{
			*pRetCode=E_DB_MESLIST_D;
			goto L_RETU;
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
