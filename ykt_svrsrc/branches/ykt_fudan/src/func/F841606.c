/* --------------------------------------------
 * ��������: F841606.sqc
 * ��������: Aug  1 2005
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: EXECL �ļ��ͻ���Ϣ����
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

int F841601(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

int F841606(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=0;
	int iCnt=0;
	int flag=0;
	T_t_cif_customer_tmp	tCustomerTmp;
	T_t_cif_customer_tmp	tCustomerTmpOut;
	ST_CPACK aPack;
	ST_PACK InPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCustomerTmp,0,sizeof(tCustomerTmp));
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_LIMIT,F_VSMESS,0);
#ifdef DEBUG
	writelog(LOG_DEBUG,"stuemp_no      :scust_auth     [%s]",rPack->scust_auth);
	writelog(LOG_DEBUG,"cut_name       :semail         [%s]",rPack->semail);
	writelog(LOG_DEBUG,"cut_type       :lvol0          [%d]",rPack->lvol0);
	writelog(LOG_DEBUG,"fee_type       :lvol2          [%d]",rPack->lvol2);
	writelog(LOG_DEBUG,"sex            :smarket_code   [%s]",rPack->smarket_code);
	writelog(LOG_DEBUG,"man_id         :scust_auth2    [%s]",rPack->scust_auth2);
	writelog(LOG_DEBUG,"phone          :sphome         [%s]",rPack->sphome);
	writelog(LOG_DEBUG,"area           :lvol1          [%d]",rPack->lvol1);
	writelog(LOG_DEBUG,"dept_no        :sname2         [%s]",rPack->sname2);
	writelog(LOG_DEBUG,"s_code         :scust_no2      [%s]",rPack->scust_no2);
	writelog(LOG_DEBUG,"in_school_date :sdate0         [%s]",rPack->sdate0);
	writelog(LOG_DEBUG,"out_school_date:sdate1         [%s]",rPack->sdate1);
	writelog(LOG_DEBUG,"card_type      :lvol3          [%d]",rPack->lvol3);
	writelog(LOG_DEBUG,"oper_code      :sorder0        [%s]",rPack->sorder0);
	writelog(LOG_DEBUG,"status      :scust_type        [%s]",rPack->scust_type);
#endif

	tCustomerTmp.seqno=rPack->lvol4;
	if(1==tCustomerTmp.seqno)
	{
		flag=1;
		//ȡ���κ�
		getsysdatetime(tCustomerTmp.batch_no);
		ret=DynamicStmtExecute("delete from ykt_cur.t_cif_customer_tmp");
		if(ret)
		{
			if(DB_NOTFOUND != ret)
			{
				*pRetCode=E_DYNAMIC_STMT_EXECUTE;
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
	des2src(tCustomerTmp.cut_name,rPack->semail);
	tCustomerTmp.cut_type=rPack->lvol0;
	tCustomerTmp.fee_type=rPack->lvol2;
	des2src(tCustomerTmp.sex,rPack->smarket_code);
	des2src(tCustomerTmp.man_id,rPack->scust_auth2);
	des2src(tCustomerTmp.phone,rPack->sphone);
	tCustomerTmp.area=rPack->lvol1;
	des2src(tCustomerTmp.dept_no,rPack->sname2);
	des2src(tCustomerTmp.s_code,rPack->scust_no2);
	des2src(tCustomerTmp.in_school_date,rPack->sdate0);
	des2src(tCustomerTmp.out_school_date,rPack->sdate1);
	tCustomerTmp.card_type=rPack->lvol3;
	des2src(tCustomerTmp.oper_code,rPack->sorder0);
	des2src(tCustomerTmp.status,rPack->scust_type);
	des2src(tCustomerTmp.class_no,rPack->sorder0);

	ret=DB_t_cif_customer_tmp_add(&tCustomerTmp);
	if(SQLCODE)
	{
		if(DB_REPEAT==SQLCODE)
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
	if(tCustomerTmp.status[0]=='1')
	{
		//���һ��,��ʼ����ʱ�����ݵ��뵽�ͻ���
		writelog(LOG_DEBUG,"�����%d��¼,���κ�:%s,�ͻ�����:%s",tCustomerTmp.seqno,tCustomerTmp.batch_no,tCustomerTmp.cut_name);
		iCnt=0;
		ret=DB_t_cif_customer_tmp_open_select_by_c0_and_batch_no(tCustomerTmp.batch_no);
		while(1)
		{
			memset(&tCustomerTmpOut,0,sizeof(tCustomerTmpOut));
			memset(&InPack,0,sizeof(InPack));
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
			InPack.lvol3=tCustomerTmpOut.cut_type;
			InPack.lvol5=tCustomerTmpOut.fee_type;
			des2src(InPack.sname,tCustomerTmpOut.cut_name);
			InPack.lvol0=tCustomerTmpOut.area;
			des2src(InPack.scust_auth2, tCustomerTmpOut.stuemp_no);
			des2src(InPack.scust_no,tCustomerTmpOut.dept_no);
			des2src(InPack.scust_auth,tCustomerTmpOut.man_id);
			des2src(InPack.smarket_code,tCustomerTmpOut.sex);
			des2src(InPack.sphone,tCustomerTmpOut.phone);
			des2src(InPack.sphone3,tCustomerTmpOut.out_school_date);
			des2src(InPack.scust_no2,tCustomerTmpOut.s_code);
			des2src(InPack.scust_limit,tCustomerTmpOut.batch_no);
			des2src(InPack.sorder0,tCustomerTmpOut.class_no);
			ret=F841601(handle,iRequest,&InPack,pRetCode,szMsg);
			if(ret)
			{
				writelog(LOG_ERR,"F841601 EXEC ERR");
				DB_t_cif_customer_tmp_close_select_by_c0();
				sprintf(szMsg,"���κ�%s,��%d������Ϊ%s�ļ�¼����,���ܵ���.",tCustomerTmpOut.batch_no,tCustomerTmpOut.seqno,tCustomerTmp.cut_name);
				goto L_RETU;
			}
			++iCnt;
		}
		sprintf(out_pack->vsmess,"���κ�:%s,���ɹ�����%d���ͻ���Ϣ",tCustomerTmp.batch_no,iCnt);
		flag=2;
	}
	if(flag!=2)
	{
		sprintf(out_pack->vsmess,"�����%d��¼,���κ�:%s,�ͻ�����:%s",tCustomerTmp.seqno,tCustomerTmp.batch_no,tCustomerTmp.cut_name);
	}
	des2src(out_pack->scust_limit,tCustomerTmp.batch_no);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
	return -1;
}
