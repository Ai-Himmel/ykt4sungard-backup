/* --------------------------------------------
 * ��������: F848020.c
 * ��������: 2005-12-12
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: EXECL �Ž���Ա��Ϣ����
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

int F848020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=0;
	int iCnt=0;
	int flag=0;
	T_t_cif_customer_tmp	tCustomerTmp;
	T_t_cif_customer_tmp	tCustomerTmpOut;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCustomerTmp,0,sizeof(tCustomerTmp));
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_LIMIT,F_VSMESS,0);
#ifdef DEBUG
	writelog(LOG_DEBUG,"stuemp_no      :scust_auth     [%s]",rPack->scust_auth);
	writelog(LOG_DEBUG,"status      :scust_type        [%s]",rPack->scust_type);
#endif

	tCustomerTmp.seqno=rPack->lvol1;
	if(strlen(rPack->scust_no)<1)
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}
	if(1==tCustomerTmp.seqno)
	{
		flag=1;
		//ȡ���κ�
		getsysdatetime(tCustomerTmp.batch_no);
		ret=DB_t_cif_customer_tmp_del_by_oper_code(rPack->scust_no);
		if(ret)
		{
			if(DB_NOTFOUND!=ret)
			{
				*pRetCode=E_DB_CUSTOMER_TMP_D;
				goto L_RETU;
			}
		}
	}
	else
	{
		des2src(tCustomerTmp.batch_no,rPack->scust_limit);
		if(strlen(tCustomerTmp.batch_no)!=14)
		{
			*pRetCode=E_INPUT_BATCH_NO;
			goto L_RETU;
		}
	}
	des2src(tCustomerTmp.stuemp_no,rPack->scust_auth);
	des2src(tCustomerTmp.oper_code,rPack->scust_no);
	if(strlen(tCustomerTmp.stuemp_no) == 0)
	{
		*pRetCode = E_INPUT_STUEMP_NO;
		sprintf(szMsg,"��%d����¼ѧ����Ϊ��",tCustomerTmp.seqno);
		goto L_RETU;
	}
	ret=DB_t_cif_customer_tmp_add(&tCustomerTmp);
	if(ret)
	{
		if(DB_REPEAT==ret)
		{
			if(1==tCustomerTmp.seqno)
			{
				//��������г�ͻ���������������µ����κ�
				for(i=0;i<3;i++)
				{
					sleep(1);
					getsysdatetime(tCustomerTmp.batch_no);
					ret=DB_t_cif_customer_tmp_add(&tCustomerTmp);
					if(ret)
					{
						if(DB_REPEAT==SQLCODE)
							continue;
						else
						{
							*pRetCode=E_DB_CUSTOMER_TMP_I;
							goto L_RETU;
						}
					}
					break;
				}
				if(i>=3)
				{
					writelog(LOG_ERR,"batch_no[%s]seqno[%d]",tCustomerTmp.batch_no,tCustomerTmp.seqno);
					*pRetCode=E_DB_CUSTOMER_TMP_E;
					goto L_RETU;
				}
			}
			else
			{
				writelog(LOG_ERR,"batch_no[%s]seqno[%d]",tCustomerTmp.batch_no,tCustomerTmp.seqno);
				*pRetCode=E_DB_CUSTOMER_TMP_E;
				goto L_RETU;
			}
		}
		else
		{
			writelog(LOG_ERR,"batch_no[%s]seqno[%d]",tCustomerTmp.batch_no,tCustomerTmp.seqno);
			*pRetCode=E_DB_CUSTOMER_TMP_I;
			goto L_RETU;
		}
	}
	if(rPack->scust_type[0]=='1')
	{
		//���һ��,��ʼ����ʱ�����ݵ��뵽�ͻ���
		writelog(LOG_DEBUG,"�����%d��¼,���κ�:%s,ѧ��:%s",tCustomerTmp.seqno,tCustomerTmp.batch_no,tCustomerTmp,tCustomerTmp.stuemp_no);
		iCnt=0;
		ret=DB_t_cif_customer_tmp_open_select_by_c0_and_batch_no(tCustomerTmp.batch_no);
		while(1)
		{
			memset(&tCustomerTmpOut,0,sizeof(tCustomerTmpOut));
			ret=DB_t_cif_customer_tmp_fetch_select_by_c0(&tCustomerTmpOut);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
					break;
				else
				{
					*pRetCode=E_DB_CUSTOMER_TMP_R;
					goto L_RETU;
				}
			}
			//���¿ͻ���
			ret=UpdCustomerBatch_noByStuemp_no(tCustomerTmpOut.stuemp_no,tCustomerTmp.batch_no);
			if(ret)
			{
				writelog(LOG_ERR,"UpdCustomerBatch_noByStuemp_no ret[%d]",ret);
				DB_t_cif_customer_tmp_close_select_by_c0();
				*pRetCode=ret;
				sprintf(szMsg,"���κ�%s,��%d��ѧ��Ϊ%s�ļ�¼����",tCustomerTmpOut.batch_no,tCustomerTmpOut.seqno,tCustomerTmpOut.stuemp_no);
				goto L_RETU;
			}
			++iCnt;
		}
		sprintf(out_pack->vsmess,"�������κ�:%s,���ɹ����¿ͻ���Ϣ��%d����¼",tCustomerTmp.batch_no,iCnt);
		flag=2;
	}
	if(flag!=2)
	{
		sprintf(out_pack->vsmess,"�����%d��¼,���κ�:%s,ѧ��:%s",tCustomerTmp.seqno,tCustomerTmp.batch_no,tCustomerTmp.stuemp_no);
	}
	des2src(out_pack->scust_limit,tCustomerTmp.batch_no);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
	return -1;
}
