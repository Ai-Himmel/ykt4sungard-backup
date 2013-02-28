/* --------------------------------------------
 * ��������: F847150.c
 * ��������: 2005-11-22
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: �ʻ�����ѯ
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "acctrans.h"
#include "busqc.h"


int F847150(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret =0;
	char accno[21]="";
	int subjno=atol(rPack->sbank_acc);
	char accflag=0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SBANKNAME,0);	

	//int subjflag=rPack->lvol1;
	if(subjno<100000000)
	{
		//��ѯ��Ŀȫ��
		T_t_subject subject;
		memset(&subject,0,sizeof(subject));
		ret=DB_t_subject_read_by_subjno(subjno,&subject);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				ERRTIP("��Ŀ��%d������",subjno);
				return E_COMMON_ERR;
			}
			else
				return E_DB_SUBJECT_R;
		}
		des2src(out_pack->sbankname,subject.subjfullname);
	}
	else
	{
		//��ѯ��Ŀȫ��
		T_t_merch merch;
		memset(&merch,0,sizeof(merch));
		ret=DB_t_merch_read_by_merchid(subjno,&merch);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				ERRTIP("��Ŀ��%d������",subjno);
				return E_COMMON_ERR;
			}
			else
				return E_DB_SUBJECT_R;
		}
		des2src(out_pack->sbankname,merch.merchname);
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

