/* --------------------------------------------
 * ��������: F847130.c
 * ��������: 2005-12-7
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: EXECL ������Ϣ����
 * --------------------------------------------
 * �޸�����: 2008-05-05 
 * �޸���Ա: ����
 * �޸�����: ԭ���벹��ʱ���ͻ���û�������Ŀ������û�������Ŀ������ܵ��벹����Ϣ��
 *			 �������������ʹ���ڵ��벹����Ϣʱ�Ƚ����ѣ��й�ʧ������Ŀ������������鷳��
 *			 ��2007trunk �汾�У�û��ͨ��POS����ȡ�������ܣ���˵��벹������Ҫ��Ӧ�����ϣ����ȡ������ж�
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
#include "dbfunc_foo.h"

int F847130(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=0;
	int iCnt=0;
	int flag=0;
	int incr=0;
	double dTotalAmt=0.0;
	char stuemp_no[21] = "";
	int batch_no_background=0;
	double dUniqno=0;
	T_t_tif_subsidytmp tSubsidyTmp;
	T_t_tif_subsidytmp tSubsidyTmpOut;
	T_t_tif_subsidy  tSubsidy;
	T_t_cif_customer tCustomer;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	T_t_pif_card t_card;
	char temp[128] = "";
	double max_subsidy = 0.0;
	memset(&t_card,0,sizeof t_card);
	memset(&tSubsidyTmp,0,sizeof(T_t_tif_subsidytmp));
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_LIMIT,F_VSMESS,0);

	tSubsidyTmp.seqno=rPack->lvol1;						//˳���
	if(strlen(rPack->scust_no)<1)						//��������Ա
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}

	if(1==tSubsidyTmp.seqno)
	{
		flag=1;
		//ȡ���κ�
		getsysdatetime(tSubsidyTmp.batch_no);
		ret=DB_t_tif_subsidytmp_del_by_oper_code(rPack->scust_no);
		if(ret)
		{
			if(DB_NOTFOUND!=ret)
			{
				*pRetCode=E_DB_SUBSIDY_D;
				goto L_RETU;
			}
		}
	}
	else
	{	//�������κ�-��ѧ�ǰ汾ͨ����̨�Զ�����������ȡ��ԭ�еĵ�������ķ�ʽ
		des2src(tSubsidyTmp.batch_no,rPack->scust_limit);  
		if(strlen(tSubsidyTmp.batch_no)!=14)
		{
			*pRetCode=E_INPUT_BATCH_NO;
			goto L_RETU;
		}

	}
	ret = GetParameter(GLOBAL_MAX_PER_SUBSIDY,temp);
	if(ret)
	{
		strcpy(szMsg,"���ʲ��������δ����");
		*pRetCode = ret;
		return ret;
	}
	max_subsidy = D4U5(atof(temp),2);
	getsysdate(tSubsidyTmp.tx_date);
	getsystime(tSubsidyTmp.tx_time);
	des2src(stuemp_no,rPack->scust_auth);		//ѧ��
	memset(&tCustomer,0,sizeof(tCustomer));
	//�ж��Ƿ�����ͻ��ţ�������Ϊ��ѧ��������
	if(rPack->lvol0==0)
	{
		if(strlen(stuemp_no) == 0 )
		{
			*pRetCode=E_STUNO_NOT_EXIST;
			goto L_RETU;
		}
		ret = DB_t_cif_customer_read_by_stuemp_no(stuemp_no,&tCustomer);
		if(ret)
		{
			sprintf(szMsg,"ѧ����Ϊ%s�Ŀͻ�������",stuemp_no);
			*pRetCode=E_STUNO_NOT_EXIST;
			goto L_RETU;
		}
		tSubsidyTmp.cust_no = tCustomer.cut_id;
	}
	else
	{
		// ʹ�ÿͻ�����Ϊ��ʶ
		tSubsidyTmp.cust_no = rPack->lvol0;
		ret = DB_t_cif_customer_read_by_cut_id(tSubsidyTmp.cust_no,&tCustomer);
		if(ret)
		{
			sprintf(szMsg,"�ͻ���Ϊ%d �Ŀͻ�������",tSubsidyTmp.cust_no);
			*pRetCode=E_CUSTOMER_NOT_EXIST;
			goto L_RETU;
		}

	}
	//des2src(tSubsidyTmp.subsidy_no,rPack->scust_limit2);		//�������κ�
	tSubsidyTmp.subsidy_no = atoi(rPack->scust_limit2);		//�������κ�
	des2src(tSubsidyTmp.oper_code,rPack->scust_no);			//����Ա����
	des2src(tSubsidyTmp.expire_date,rPack->sdate2);				//��������
	ret=IsInvalidDateTime(tSubsidyTmp.expire_date,"YYYYMMDD");
	if(ret)
	{
		sprintf(szMsg,"����%s ��ʽ����ȷ,��ȷ��ʽΪYYYYMMDD",tSubsidyTmp.expire_date);
		*pRetCode=ret;
		goto L_RETU;
	}
	tSubsidyTmp.amount=rPack->damt0;				//�������
	if(amtcmp(D4U5(tSubsidyTmp.amount,2),tSubsidyTmp.amount) != 0)
	{
		sprintf(szMsg,"�������%f ֻ�ܾ�ȷ����",tSubsidyTmp.amount);
		*pRetCode = E_INPUT_AMT;
		goto L_RETU;

	}
	if(amtcmp(tSubsidyTmp.amount,max_subsidy) > 0
	   || amtcmp(tSubsidyTmp.amount,-max_subsidy) < 0)
	{
		sprintf(szMsg,"�������%.2fԪ  �������ʲ����������",tSubsidyTmp.amount);
		*pRetCode = E_INPUT_AMT;
		goto L_RETU;
	}
	strcpy(tSubsidyTmp.status,"1");						//״̬(1-δ��ȡ��2-����ȡ)
	//���һ��ͨϵͳ�Ƿ񲻴��ڸ�ѧ/����
	/*
	   ret=IsInexistenceStuEmp(tSubsidyTmp.stuemp_no);
	   if(ret)
	   {
	   if(E_STUNO_NOT_EXIST==ret)
	   {
	   sprintf(szMsg,"ѧ��%s��һ��ͨϵͳ������",tSubsidyTmp.stuemp_no);
	   }
	 *pRetCode=ret;
	 goto L_RETU;
	 }
	 */
	//ȡ�ÿͻ��ĵ�ǰ���ţ�д����ʱ�������У�ֻ�ܸÿ�Ƭ������ȡ����
	/*
	ret=get_curr_card_by_custid(tSubsidyTmp.cust_no, &t_card);
	if(ret)
	{
		sprintf(szMsg,"�������κ�%s,��%d����¼����,�Ҳ����ÿͻ���Ψһ����",tSubsidy.batch_no,tSubsidy.seqno);
		*pRetCode = ret;
		goto L_RETU;
	}
	tSubsidyTmp.card_no=t_card.card_id;
	*/
	// ���ͻ��Ƿ����˻�����
	ret = is_cust_open_account(tSubsidyTmp.cust_no,ACCTYPE_PERMAIN);
	if(ret)
	{
		sprintf(szMsg,"�ͻ�[%d][%s]δ�����������·�����",tSubsidyTmp.cust_no,tCustomer.cut_name);
		*pRetCode = ret;
		goto L_RETU;
	}
	tSubsidyTmp.card_no = 0;
	ret=DB_t_tif_subsidytmp_add(&tSubsidyTmp);
	if(ret)
	{
		if(DB_REPEAT==ret)
		{
			if(1==tSubsidyTmp.seqno)
			{
				//��������г�ͻ���������������µ����κ�
				for(i=0;i<3;i++)
				{
					sleep(1);
					getsysdatetime(tSubsidyTmp.batch_no);
					ret=DB_t_tif_subsidytmp_add(&tSubsidyTmp);
					if(ret)
					{
						if(DB_REPEAT==SQLCODE)
							continue;
						else
						{
							*pRetCode=E_DB_SUBSIDYTMP_I;
							goto L_RETU;
						}
					}
					break;
				}
				if(i>=3)
				{
					writelog(LOG_ERR,"batch_no[%s]seqno[%d]",tSubsidyTmp.batch_no,tSubsidyTmp.seqno);
					*pRetCode=E_DB_SUBSIDYTMP_E;
					goto L_RETU;
				}
			}
			else
			{
				writelog(LOG_ERR,"batch_no[%s]seqno[%d]",tSubsidyTmp.batch_no,tSubsidyTmp.seqno);
				*pRetCode=E_DB_SUBSIDYTMP_E;
				goto L_RETU;
			}
		}
		else
		{
			writelog(LOG_ERR,"batch_no[%s]seqno[%d]",tSubsidyTmp.batch_no,tSubsidyTmp.seqno);
			*pRetCode=E_DB_SUBSIDYTMP_I;
			goto L_RETU;
		}
	}
	if(rPack->scust_type[0]=='1')
	{
		//�õ���ǰ�Ĳ������κ�
		ret = getNewUniqNo(KEYTYPE_TIF_SUBSIDY_NO,&dUniqno);  	
		if(ret)
		{
			*pRetCode = ret;
			writelog(LOG_ERR,"getNewUniqNo errcode = [%d]",ret);
			goto L_RETU;
		}

		//���һ��,��ʼ����ʱ�����ݵ��뵽��ʽ��
		writelog(LOG_DEBUG,"�����%d����¼,�������κ�:%s,�ͻ���%d",tSubsidyTmp.seqno,tSubsidyTmp.batch_no,tSubsidyTmp.cust_no);
		iCnt=0;
		ret=DB_t_tif_subsidytmp_open_select_by_c0_and_batch_no(tSubsidyTmp.batch_no);
		while(1)
		{
			memset(&tSubsidyTmpOut,0,sizeof(tSubsidyTmpOut));
			ret=DB_t_tif_subsidytmp_fetch_select_by_c0(&tSubsidyTmpOut);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
				{
					if(iCnt>0)
						break;
					else
					{
						*pRetCode=E_DB_SUBSIDYTMP_N;
						goto L_RETU;
					}
				}
				else
				{
					*pRetCode=E_DB_SUBSIDYTMP_R;
					goto L_RETU;
				}
			}
			if(((tSubsidyTmpOut.amount>0)&&incr==-1 )||((tSubsidyTmpOut.amount<0)&&incr==1))
			{
				*pRetCode=E_SUBSIDY_AMOUNT_ERROR;
				sprintf(szMsg,"�������κ�%s,��%d����¼����,ϵͳ������һ�����������������ֽ��",tSubsidy.batch_no,tSubsidy.seqno);
				goto L_RETU;
			}
			if(tSubsidyTmpOut.amount>0) incr =1;
			else incr=-1;
			memcpy(&tSubsidy,&tSubsidyTmpOut,sizeof(tSubsidy));
			//�޸Ĳ������κ�Ϊ��������̨�Զ����ɣ�ȡ��ԭ�е�ǰ̨����ķ�ʽ
			tSubsidy.subsidy_no=int(dUniqno);
			//���벹����Ϣ��
			ret=DB_t_tif_subsidy_add(&tSubsidy);
			if(ret)
			{
				DB_t_tif_subsidytmp_close_select_by_c0();
				if(DB_REPEAT==ret)
					*pRetCode=E_DB_STUEMPNO_RE;
				else
					*pRetCode=E_DB_SUBSIDY_I;
				sprintf(szMsg,"�������κ�%s,��%d����¼����,���ܸ�ѧ�ŵĲ�����¼�Ѿ�����",tSubsidy.batch_no,tSubsidy.seqno);
				goto L_RETU;
			}
			dTotalAmt+=tSubsidy.amount;
			++iCnt;
		}
		sprintf(out_pack->vsmess,"�������κ�:%s,���ɹ�����%d��������Ϣ,��������ܹ�%.2lfԪ",tSubsidyTmp.batch_no,iCnt,dTotalAmt);
		flag=2;
	}
	if(flag!=2)
	{
		sprintf(out_pack->vsmess,"�����%d����¼,�������κ�:%s",tSubsidyTmp.seqno,tSubsidyTmp.batch_no);
	}
	des2src(out_pack->scust_limit,tSubsidyTmp.batch_no);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
	return -1;
}
