/* --------------------------------------------
 * ��������: F930007.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������: �´��豸������
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

int F930007(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
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
	memset(&tDevice,0,sizeof(tDevice));

	des2src(tMesList.devphy999_id, in_pack->sdate0);
	trim(tMesList.devphy999_id);
	if(strlen(tMesList.devphy999_id)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	ret=get_devinfo_by_phyid(tMesList.devphy999_id,&tDevice);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"get_devinfo_by_phyid err[%d]",ret);
		goto L_RETU;
	}
	AddXmlItemInt(tMesList.incontent, XML_KEY_DEV999_NO, tDevice.dev999_no);		//����
	AddXmlItemStr(tMesList.incontent, XML_KEY_DEV999_ID, tDevice.dev999_id);		//ע���	
	AddXmlItemInt(tMesList.incontent, XML_KEY_BAUDRATE, tDevice.baudrate);		//������
	AddXmlItemStr(tMesList.incontent, XML_KEY_SYSPWD, tDevice.syspwd);			//ϵͳԱ����	
	AddXmlItemStr(tMesList.incontent, XML_KEY_ADMPWD,tDevice.admpwd);			//����Ա����
	AddXmlItemInt(tMesList.incontent, XML_KEY_PWDONOFF,tDevice.pwdonoff);		//���뿪��	
	AddXmlItemStr(tMesList.incontent, XML_KEY_CARDSTR, "100");					//��Ƭ�ṹ	
	AddXmlItemInt(tMesList.incontent, XML_KEY_CARDUSENUM,tDevice.cardusenum);	//�������ʹ�ô���\����������Ѵ���	
	AddXmlItemInt(tMesList.incontent, XML_KEY_MAXDEPOSIT, tDevice.maxdeposit);	//Ǯ����ߴ���޶�
	AddXmlItemInt(tMesList.incontent, XML_KEY_MINDEPOSIT, tDevice.mindeposit);		//Ǯ�����ʣ����޶�	
	AddXmlItemInt(tMesList.incontent, XML_KEY_RATION, tDevice.ration);				//��ֵ�շѷ�ʽʹ�õĶ�ֵ��\��ֵ���
	AddXmlItemStr(tMesList.incontent, XML_KEY_PUSERNO, tDevice.puserno);			//Ǯ������\Ǯ����	
	AddXmlItemInt(tMesList.incontent, XML_KEY_MAXTRADE, tDevice.maxtrade);		//ÿ�ν�����߶�\��������޶�	
	AddXmlItemStr(tMesList.incontent, XML_KEY_VCARDSET, tDevice.cardtype);		//�ն˻������û������	
	AddXmlItemStr(tMesList.incontent, XML_KEY_FUNONOFF, tDevice.funonoff);			//�շѻ���ǿ���ܿ���	
	AddXmlItemInt(tMesList.incontent, XML_KEY_FEETYPE, tDevice.feetype);			//�շѷ�ʽ

	tMesList.funid = 930007;
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





