/* --------------------------------------------
 * ��������: F849021.sqc
 * ��������: 2006-10-12
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ���п��󶨵���
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
#include "busqc.h"
#include "dbfunc_foo.h"


int F849021(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	T_t_bankcard bankcard;
	T_t_bankcardtmp bankcardtmp;
	T_t_customer customer;
	int i;
	int count;
	int flag;
	ST_CPACK aPack;
	ST_PACK * out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_LIMIT,F_VSMESS,0);

	memset(&bankcard,0,sizeof bankcard);
	des2src(bankcardtmp.batchno,in_pack->scust_limit);
	bankcardtmp.seqno = in_pack->lvol0;
	
	if(1 == bankcardtmp.seqno)
	{
		ret = DynamicStmtExecute("DELETE FROM YKT_CUR.T_bankcardtmp ");
		if(ret)
		{
			if(DB_NOTFOUND != ret)
			{
				return ret;
			}
		}
		des2src(bankcardtmp.batchno,CAccTrans::getInstance()->trans.sysdatetime);
	}
	else if(strlen(bankcardtmp.batchno) != 14)
	{
		*pRetCode=E_INPUT_BATCH_NO;
		goto L_RETU;
	}

	bankcardtmp.custid = in_pack->lvol1;
	if(0 == bankcardtmp.custid)
	{
		if(strlen(in_pack->scust_auth) == 0)
		{
			*pRetCode = E_INPUT_STUEMP_NO;
			sprintf(szMsg,"��[%d]����¼�ͻ�����ѧ���Ŷ�Ϊ��",bankcardtmp.seqno);
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
		bankcardtmp.custid = customer.custid;
	}
	des2src(bankcardtmp.opercode,in_pack->semp);
	des2src(bankcardtmp.bankcardno,in_pack->sbank_acc);
	//bankcardtmp.outside_type = CUT_RELATION_TYPE_BANK;

	ret = DB_t_bankcardtmp_add(&bankcardtmp);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
			if(1 == bankcardtmp.seqno)
			{
				//���κ��ظ�
				for(i=0;i<3;i++)
				{
					sleep(1);
					getsysdatetime(bankcardtmp.batchno);
					ret=DB_t_bankcardtmp_add(&bankcardtmp);
					if(ret)
					{
						if(DB_REPEAT==ret)
							continue;
						else
						{
							*pRetCode=E_DB_BANKCARDTMP_I;
							goto L_RETU;
						}
					}
					break;
				}
				if(i >= 3)
				{
					*pRetCode = E_DB_BANKCARDTMP_E;
					writelog(LOG_ERR,"batchno[%s],seqno[%d]",bankcardtmp.batchno,bankcardtmp.seqno);
					goto L_RETU;
				}
			}
			else
			{
				*pRetCode = E_DB_BANKCARDTMP_E;
				writelog(LOG_ERR,"batchno[%s],seqno[%d]",bankcardtmp.batchno,bankcardtmp.seqno);
				goto L_RETU;
			}
		}
		else
		{
			*pRetCode = E_DB_BANKCARDTMP_I;
			writelog(LOG_ERR,"batchno[%s],seqno[%d]",bankcardtmp.batchno,bankcardtmp.seqno);
			goto L_RETU;	
		}
	}
	flag = 1;
	if('1' == in_pack->scust_type[0] )
	{
		//���һ����¼�Ѿ�����
		ret = DB_t_bankcardtmp_open_select_by_c1_and_batchno(bankcardtmp.batchno);
		if(ret)
		{
			*pRetCode = E_DB_BANKCARDTMP_R;
			goto L_RETU;
		}
		count = 0;
		while(1)
		{
			memset(&bankcardtmp,0,sizeof bankcardtmp);
			ret = DB_t_bankcardtmp_fetch_select_by_c1(&bankcardtmp);
			if(ret)
			{
				if(DB_NOTFOUND == ret)
					break;
				*pRetCode = E_DB_BANKCARDTMP_R;
				goto L_RETU;
			}
			bankcard.custid = bankcardtmp.custid;
			des2src(bankcard.bankcardno,bankcardtmp.bankcardno);
//			des2src(bankcard.comment,bankcardtmp.comment);
			ret = DB_t_bankcard_add(&bankcard);
			if(ret)
			{
				DB_t_bankcardtmp_close_select_by_c1();
				memset(&customer,0,sizeof customer);
				DB_t_customer_read_by_custid(bankcardtmp.custid,&customer);
				if(DB_REPEAT == ret)
				{
					sprintf(szMsg,"�������[%d],ѧ����[%s],У��[%s]�Ѵ���"
						,bankcardtmp.seqno,customer.stuempno,customer.areacode);
					writelog(LOG_ERR,szMsg);
					*pRetCode = E_DB_BANKCARD_I;
					goto L_RETU;
				}
				else
				{
					sprintf(szMsg,"�������[%d],ѧ����[%s],У��[%s]����,���ܵ���"
						,bankcardtmp.seqno,customer.stuempno,customer.areacode);
					writelog(LOG_ERR,szMsg);
					*pRetCode = E_DB_BANKCARD_I;
					goto L_RETU;
				}
			}
			count++;
		}
		sprintf(out_pack->vsmess,"���κ�:%s,���ɹ�����%d���ͻ���Ϣ",bankcardtmp.batchno,count);
		flag=2;
	}
	if(2 != flag)
	{
		sprintf(out_pack->vsmess,"�����%d��¼,���κ�:%s",bankcardtmp.seqno,bankcardtmp.batchno);
	}
	des2src(out_pack->scust_limit,bankcardtmp.batchno);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
	return -1;
}
