/* --------------------------------------------
 * ��������: F843362.sqC
 * ��������: 2007-11-02
 * ��������:�Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ��ֵ����Ա�豸���
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

int F843362(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;

	CAccTrans& ats=CAccTrans::GetInst();
	des2src(ats.trans.opercode,rPack->semp);
	ats.trans.transcode=MAKETRANSCODEADD(TCM_DEPOSITOPERPOS);
	ret=ats.InitTrans();
	if(ret)
		return ret;			
	char deviceid[31]="";
	T_t_dpsoperpos tDepositOperPos;
	T_t_dpsoper tDepositOper;
	T_t_dpsshoppos  tDepositShopPos;
	
	memset(&tDepositOperPos,0,sizeof(tDepositOperPos));
	memset(&tDepositOper,0,sizeof(tDepositOper));
	memset(&tDepositShopPos,0,sizeof(tDepositShopPos));
	
	if(!strlen(rPack->vsvarstr1))
	{
		return E_INPUT_DATA_INVAILD;
	}	
	ret=DB_t_dpsoper_read_by_opercode(rPack->scust_auth,&tDepositOper);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_DEPOSITOPER,rPack->scust_auth);
		else
			return E_DB_DEPOSITOPER_R;
	}
	if(tDepositOper.devlimitflag[0]!='1')
	{
		return E_OPER_NO_NEED_DEVICE;
	}
	des2src(tDepositOperPos.opercode,rPack->scust_auth);
	des2src(tDepositOperPos.openoper,rPack->semp);
	des2src(tDepositOperPos.lastsaved,CAccTrans::GetInst().hostdatetime);
	vector<string>  strlist;
	split2list(rPack->vsvarstr1,',',strlist);
	for(int i=0;i<strlist.size();i++)
	{
		tDepositOperPos.deviceid=atoi(strlist[i].c_str());
		//�������Ա���ǳ�ֵ�̻�����Ա������󶨳�ֵ�̻��豸
		ret=DB_t_dpsshoppos_read_by_deviceid(tDepositOperPos.deviceid, &tDepositShopPos);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(tDepositOper.shopoperflag[0]=='1')
				{
					return ERRINFO(E_DEVICE_NOTIS_DEPOSITSHOP,tDepositOperPos.deviceid);
				}
			}	
			else
			{
				return E_DB_DEPOSITSHOPPOS_R;

			}
		}
		else
		{
			if(tDepositOper.shopoperflag[0]=='0')
			{
				return ERRINFO(E_DEVICE_IS_DEPOSITSHOP,tDepositOperPos.deviceid);
			}
		}
		SQLCODE=0;
		ret=DB_t_dpsoperpos_add(&tDepositOperPos);
		if(ret)
		{
			writelog(LOG_ERR,"opercode[%s]",tDepositOperPos.opercode);
			if(DB_REPEAT==ret)
			{
				return ERRINFO(E_DB_DEPOSITOPERPOS_E,tDepositOperPos.opercode,ltos(tDepositOperPos.deviceid).c_str());
			}
			else
			{
				return E_DB_DEPOSITOPERPOS_I;
			}
		}
	}
	return 0;
}
