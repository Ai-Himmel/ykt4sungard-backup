/* --------------------------------------------
 * ��������: F930013.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������:��������ʱ��β���
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

int F930013(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
 	int cnt=0;
	int mesid=0;
       T_t_tif_meslist tMesList;
	T_t_pif_device tDevice;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);
	memset(&tMesList,0,sizeof(tMesList));
	memset(&tDevice,0,sizeof tDevice);

	if(strlen(in_pack->sdate0)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}

	AddXmlItemStr(tMesList.incontent, XML_KEY_STARTDT, in_pack->sopen_emp);
	AddXmlItemStr(tMesList.incontent, XML_KEY_ENDDT, in_pack->sclose_emp);
	AddXmlItemInt(tMesList.incontent, XML_KEY_RATION, in_pack->lvol4);
	AddXmlItemInt(tMesList.incontent, XML_KEY_CARDUSENUM, in_pack->lvol5);
	AddXmlItemStr(tMesList.incontent, XML_KEY_VCARDSET, in_pack->snote2);

	if((ret = get_devinfo_by_phyid(in_pack->sdate0,&tDevice)))
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tMesList.devid = tDevice.device_id;
	tMesList.funid = 930013;
	tMesList.level = 2;
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	if(iRequest!=tMesList.funid)
		return 0;	
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		*pRetCode=E_DB_COMMIT;
		goto  L_RETU;
	}
	mesid=tMesList.mesid;
	des2src(out_pack->sdate0,in_pack->sdate0);
	for(cnt=0;(cnt<10)&&(tMesList.ecode!=0);cnt++)
	{
		sleep(1);
		memset(&tMesList,0,sizeof(tMesList));
		ret=DB_t_tif_meslist_read_by_mesid(mesid, &tMesList);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_tif_meslist_read_by_mesid err[%d]",ret);
			*pRetCode=E_DB_MESLIST_R;
			goto L_RETU;
		}
	}
	switch(tMesList.ecode)
	{
		case 0:		//�ɹ�
			des2src(out_pack->vsvarstr0,"�ɹ�");
			break;
		case 9999:		//����δ����
			des2src(out_pack->vsvarstr0,"ǰ�û���Ӧ��");
			break;
		default:			//�����Ѿ�����,�������ʧ��
			des2src(out_pack->vsvarstr0,tMesList.emsg);				
			break;
	}	
	PutRow(handle,out_pack,pRetCode,szMsg);	
	return 0;
L_RETU:
	return  -1;	
}





