/* --------------------------------------------
 * ��������: F841609.sqc
 * ��������: Sep 29 2004
 * ��������: auto creat by wen jian
 * �汾��Ϣ: 1.0.0.0
 * ������: ����������ʱ�ͻ���
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
#include "fdsqc.h"

int F841609(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int CustomerCount=0;
	int start_no=0;
	char temp[256] ="";
	T_t_cif_cuttypefee tCuttype;
	T_t_pif_feetype tFeetype;
	T_t_cif_customer  tCustomer;
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,0);

	CustomerCount=rPack->lvol0;//	����
	memset(&tCuttype,0,sizeof(tCuttype));

//�����ӿͻ�
	ret = GetParameter(GLOBE_FLAG_TEMPCARD_CUTTYPE,temp);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tCustomer.cut_type= atoi(temp);
	if(tCustomer.cut_type<= 0)
	{
		*pRetCode = E_GLOBAL_PARAM_ERROR;
		strcpy(szMsg,"����ȷ������ʱ��Ա�ͻ����");
		goto L_RETU;
	}
	ret = DB_t_cif_cuttypefee_read_by_cut_type(tCustomer.cut_type,&tCuttype);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			*pRetCode = E_DB_CUTTYPEFEE_N;
			strcpy(szMsg,"����ȷ������ʱ��Ա�շ����");
		}
		else
			*pRetCode = E_DB_CUTTYPEFEE_R;
		goto L_RETU;
	}
	
	ret = GetParameter(GLOBE_FLAG_TEMPCARD_FEETYPE,temp);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tCustomer.fee_type = atoi(temp);
	if(tCustomer.fee_type <= 1)
	{
		*pRetCode = E_GLOBAL_PARAM_ERROR;
		strcpy(szMsg,"����ȷ������ʱ��Ա�շ����");
		goto L_RETU;
	}
	memset(&tFeetype,0,sizeof tFeetype);
	ret = DB_t_pif_feetype_read_by_fee_type(tCustomer.fee_type,&tFeetype);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			*pRetCode = E_DB_FEETYPE_N;
			strcpy(szMsg,"����ȷ������ʱ��Ա�շ����");
		}
		else
			*pRetCode = E_DB_FEETYPE_R;
		goto L_RETU;
	}
	tCustomer.cut_state=CUSTSTAT_REGIST;
	des2src(tCustomer.is_havecard,TYPE_NO);
	strcpy(tCustomer.cut_name,"��ʱ��Ա");	//�ͻ�����
	tCustomer.enableid[0]='2';				//��ݽ��ñ�־1-����2-����
	tCustomer.use_flag[0]='0';
	strcpy(tCustomer.school_code,rPack->sbranch_code0);	//У��
	getsysdatetime(tCustomer.batch_no);
	strcpy(tCustomer.reg_time,tCustomer.batch_no);
	
	for(int i=0;i<CustomerCount;i++)
	{
		ret=get_cut_id_by_school_code(rPack->sbranch_code0,tCustomer.cut_id);
		if(ret)
		{
			writelog(LOG_ERR,"school_code[%s]",rPack->sbranch_code0);
			*pRetCode=ret;
			goto L_RETU;
		}
		ret=DB_t_cif_customer_add(&tCustomer);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_cif_customer_add ret[%d]",ret);
			if(DB_REPEAT==ret)
				*pRetCode = E_CUSTOMER_NO_EXIST;
			else
				*pRetCode = E_DB_CUSTOMER_I;
			goto L_RETU;
		}
		if(0==i)
			start_no=tCustomer.cut_id;
	}
	sprintf(out_pack->vsmess,"�������κ�%s,�ͻ��Ŵ�%d��%d��%d���ͻ��Զ��������",tCustomer.batch_no,start_no,tCustomer.cut_id,CustomerCount);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
	return -1;
}
