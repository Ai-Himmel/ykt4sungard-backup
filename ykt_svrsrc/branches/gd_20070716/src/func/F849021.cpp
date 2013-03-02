/* --------------------------------------------
 * ��������: F849021.sqc
 * ��������: 2006-10-12
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ���п��󶨵���
 * --------------------------------------------
 * �޸�����: 2007-11-29
 * �޸���Ա: ������
 * �޸�����: �޸ĵ��������ʱ��ʱģ��
 				������ʽ���ж��Ƿ������
 				�⣬��ǰ̨��ʾ
 * �汾��Ϣ: 1.0.0.1
 * ��ע��Ϣ:
 * --------------------------------------------
 * �޸�����: 2007-12-05
 * �޸���Ա: ������
 * �޸�����: ����ǰ̨��Ҫ���޸Ĵ���
 				����ʱ����ԭ�еļܹ���
 				retcode=0������Ĵ�����Ϣ
 				�ڷ��ذ������֡�
 * �汾��Ϣ: 1.0.0.2
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
#include "dbfunc_foo.h"


int F849021(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	T_t_pif_cut_relation relation;
	T_t_pif_cut_relation_tmp input_relation;
	T_t_cif_customer customer;
	int i;
	int count;
	int flag;
	ST_CPACK aPack;
	ST_PACK * out_pack = &(aPack.pack);
	char sErrMsg[101]="";
	char sTempMsg[256]="";
		
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_LIMIT,F_LVOL12,F_VSVARSTR0,0);

	memset(&input_relation,0,sizeof input_relation);
	des2src(input_relation.batch_no,in_pack->scust_limit);
	input_relation.seqno = in_pack->lvol0;
	
	if(1 == input_relation.seqno)
	{
		ret = DynamicStmtExecute("DELETE FROM YKT_CUR.T_PIF_CUT_RELATION_TMP ");
		if(ret)
		{
			if(DB_NOTFOUND != ret)
			{
				*pRetCode = ret;
				goto L_RETU;
			}
		}
		db_commit();
		getsysdatetime(input_relation.batch_no);
	}
	else if(strlen(input_relation.batch_no) != 14)
	{
		*pRetCode=E_INPUT_BATCH_NO;
		goto L_RETU;
	}

	input_relation.cut_id = in_pack->lvol1;
	if(0 == input_relation.cut_id)
	{
		if(strlen(in_pack->scust_auth) == 0)
		{
			*pRetCode = E_INPUT_STUEMP_NO;
			sprintf(szMsg,"��[%d]����¼�ͻ�����ѧ���Ŷ�Ϊ��",input_relation.seqno);
			writelog(LOG_DEBUG,szMsg);
			goto L_RETU;
		}
		memset(&customer,0,sizeof customer);
		//��ѯѧ����
		//ret = GetCutInfoByStuempnoAndArea(in_pack->scust_auth,in_pack->lvol2,&customer);
		if(ret)
		{
			sprintf(szMsg,"ѧ����[%s]У��[%d]�ͻ�������"
				,in_pack->scust_auth,in_pack->lvol2);
			writelog(LOG_DEBUG,szMsg);
			*pRetCode = ret;
			goto L_RETU;
		}
		input_relation.cut_id = customer.cut_id;
	}
	sprintf(input_relation.comment,"����Ա%s",in_pack->scust_no);
	des2src(input_relation.outside_no,in_pack->sbank_acc);
	input_relation.outside_type = CUT_RELATION_TYPE_BANK;

	//ģ�������ʽ���ж��Ƿ񱨴�
	relation.cut_id = input_relation.cut_id;
	relation.outside_type = input_relation.outside_type;
	des2src(relation.outside_no,input_relation.outside_no);
	des2src(relation.comment,input_relation.comment);
	ret = DB_t_pif_cut_relation_add(&relation);
	if(ret)
	{
		DB_t_cif_customer_read_by_cut_id(relation.cut_id,&customer);
		if(DB_REPEAT == ret)
		{
			sprintf(szMsg,"�������[%d],ѧ����[%s],У��[%d]�Ѵ���"
				,input_relation.seqno,in_pack->scust_auth,in_pack->lvol2);
			writelog(LOG_ERR,szMsg);
			*pRetCode = E_DB_CUT_RLTN_I;
			goto L_RETU;
		}
		else
		{
			sprintf(szMsg,"�������[%d],ѧ����[%s],У��[%d]����,���ܵ���"
				,input_relation.seqno,in_pack->scust_auth,in_pack->lvol2);
			writelog(LOG_ERR,szMsg);
			*pRetCode = E_DB_CUT_RLTN_I;
			goto L_RETU;
		}
	}
	db_rollback();

	//��ʼ������ʱ���˴������ύ
	ret = DB_t_pif_cut_relation_tmp_add(&input_relation);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
			if(1 == input_relation.seqno)
			{
				//���κ��ظ�
				for(i=0;i<3;i++)
				{
					sleep(1);
					getsysdatetime(input_relation.batch_no);
					ret=DB_t_pif_cut_relation_tmp_add(&input_relation);
					if(ret)
					{
						if(DB_REPEAT==ret)
							continue;
						else
						{
							*pRetCode=E_DB_CUT_RLTN_TMP_I;
							goto L_RETU;
						}
					}
					break;
				}
				if(i >= 3)
				{
					*pRetCode = E_DB_CUT_RLTN_TMP_E;
					writelog(LOG_ERR,"batch_no[%s],seqno[%d]",input_relation.batch_no,input_relation.seqno);
					goto L_RETU;
				}
			}
			else
			{
				*pRetCode = E_DB_CUT_RLTN_TMP_E;
				writelog(LOG_ERR,"batch_no[%s],seqno[%d]",input_relation.batch_no,input_relation.seqno);
				goto L_RETU;
			}
		}
		else
		{
			*pRetCode = E_DB_CUT_RLTN_TMP_I;
			writelog(LOG_ERR,"batch_no[%s],seqno[%d]",input_relation.batch_no,input_relation.seqno);
			goto L_RETU;	
		}
	}
	flag = 1;
	if('1' == in_pack->scust_type[0] )
	{
		//���һ����¼�Ѿ�����
		ret = DB_t_pif_cut_relation_tmp_open_select_by_c1_and_batch_no(
		input_relation.batch_no);
		if(ret)
		{
			*pRetCode = E_DB_CUT_RLTN_TMP_R;
			goto L_RETU_OUT;
		}
		count = 0;
		while(1)
		{
			memset(&input_relation,0,sizeof input_relation);
			ret = DB_t_pif_cut_relation_tmp_fetch_select_by_c1(&input_relation);
			if(ret)
			{
				if(DB_NOTFOUND == ret)
					break;
				*pRetCode = E_DB_CUT_RLTN_TMP_R;
				goto L_RETU_OUT;
			}
			relation.cut_id = input_relation.cut_id;
			relation.outside_type = input_relation.outside_type;
			des2src(relation.outside_no,input_relation.outside_no);
			des2src(relation.comment,input_relation.comment);
			ret = DB_t_pif_cut_relation_add(&relation);
			if(ret)
			{
				DB_t_pif_cut_relation_tmp_close_select_by_c1();
				memset(&customer,0,sizeof customer);
				DB_t_cif_customer_read_by_cut_id(input_relation.cut_id,&customer);
				if(DB_REPEAT == ret)
				{
					sprintf(szMsg,"�������[%d],ѧ����[%s],У��[%d]�Ѵ���"
						,input_relation.seqno,in_pack->scust_auth,in_pack->lvol2);
					writelog(LOG_ERR,szMsg);
					*pRetCode = E_DB_CUT_RLTN_I;
					goto L_RETU_OUT;
				}
				else
				{
					sprintf(szMsg,"�������[%d],ѧ����[%s],У��[%d]����,���ܵ���"
						,input_relation.seqno,in_pack->scust_auth,in_pack->lvol2);
					writelog(LOG_ERR,szMsg);
					*pRetCode = E_DB_CUT_RLTN_I;
					goto L_RETU_OUT;
				}
			}
			count++;
		}
		sprintf(out_pack->vsmess,"���κ�:%s,���ɹ�����%d���ͻ���Ϣ",input_relation.batch_no,count);
		flag=2;
	}
	if(2 != flag)
	{
		sprintf(out_pack->vsmess,"�����%d��¼,���κ�:%s",input_relation.seqno,input_relation.batch_no);
	}
	des2src(out_pack->scust_limit,input_relation.batch_no);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
	if('1' == in_pack->scust_type[0] )
	{
		//���һ����¼�Ѿ�����
		ret = DB_t_pif_cut_relation_tmp_open_select_by_c1_and_batch_no(
		input_relation.batch_no);
		if(ret)
		{
			*pRetCode = E_DB_CUT_RLTN_TMP_R;
			goto L_RETU_OUT;
		}
		count = 0;
		while(1)
		{
			memset(&input_relation,0,sizeof input_relation);
			ret = DB_t_pif_cut_relation_tmp_fetch_select_by_c1(&input_relation);
			if(ret)
			{
				if(DB_NOTFOUND == ret)
					break;
				*pRetCode = E_DB_CUT_RLTN_TMP_R;
				goto L_RETU_OUT;
			}
			relation.cut_id = input_relation.cut_id;
			relation.outside_type = input_relation.outside_type;
			des2src(relation.outside_no,input_relation.outside_no);
			des2src(relation.comment,input_relation.comment);
			ret = DB_t_pif_cut_relation_add(&relation);
			if(ret)
			{
				DB_t_pif_cut_relation_tmp_close_select_by_c1();
				memset(&customer,0,sizeof customer);
				DB_t_cif_customer_read_by_cut_id(input_relation.cut_id,&customer);
				if(DB_REPEAT == ret)
				{
					sprintf(szMsg,"�������[%d],ѧ����[%s],У��[%d]�Ѵ���"
						,input_relation.seqno,in_pack->scust_auth,in_pack->lvol2);
					writelog(LOG_ERR,szMsg);
					*pRetCode = E_DB_CUT_RLTN_I;
					goto L_RETU_OUT;
				}
				else
				{
					sprintf(szMsg,"�������[%d],ѧ����[%s],У��[%d]����,���ܵ���"
						,input_relation.seqno,in_pack->scust_auth,in_pack->lvol2);
					writelog(LOG_ERR,szMsg);
					*pRetCode = E_DB_CUT_RLTN_I;
					goto L_RETU_OUT;
				}
			}
			count++;
		}
		sprintf(out_pack->vsmess,"���κ�:%s,���ɹ�����%d���ͻ���Ϣ",input_relation.batch_no,count);
		flag=2;
	}
	
	des2src(out_pack->scust_limit,input_relation.batch_no);
	out_pack->lvol12=*pRetCode;
	get_errcode_msg(*pRetCode, sErrMsg);
	des2src(sTempMsg,szMsg);
	snprintf(szMsg,256,"%s%s\n%s",sErrMsg,sTempMsg,g_sqlmsg);
	des2src(out_pack->vsvarstr0,szMsg);
	PutRow(handle,out_pack,pRetCode,szMsg);
	*pRetCode=0;
	return 0;
L_RETU_OUT:

	return -1;

}
