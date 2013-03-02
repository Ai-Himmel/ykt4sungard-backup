/* --------------------------------------------
 * 程序名称: F849021.sqc
 * 创建日期: 2006-10-12
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 银行卡绑定导入
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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
	char seqno_1[21]="";
	int i;
	int count;
	int flag;
	int cust_id=0;
	int last_flag =0;
	ST_CPACK aPack;
	ST_PACK * out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_LIMIT,F_VSMESS,0);

	memset(&input_relation,0,sizeof input_relation);
	memset(seqno_1,0,sizeof(seqno_1));
	des2src(input_relation.batch_no,in_pack->scust_limit);
	input_relation.seqno = in_pack->lvol0;
	des2src(seqno_1,in_pack->scust_auth);

//      get_cut_id_by_stuemp_no(seqno_1,&cust_id);
	// writelog(LOG_ERR,"debug me!!seqno_1->%s cust_id->%d ",seqno_1,cust_id);
	
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
			sprintf(szMsg,"第[%d]条记录客户号与学工号都为空",input_relation.seqno);
			writelog(LOG_DEBUG,szMsg);
			goto L_RETU;
		}
		memset(&customer,0,sizeof customer);
		//查询学工号
		/*
		ret = GetCutInfoByStuempnoAndArea(in_pack->scust_auth,in_pack->lvol2,&customer);
		if(ret)
		{
			sprintf(szMsg,"学工号[%s]校区[%d]客户不存在"
				,in_pack->scust_auth,in_pack->lvol2);
			writelog(LOG_DEBUG,szMsg);
			*pRetCode = ret;
			goto L_RETU;
		}
		*/
		ret = DB_t_cif_customer_read_by_stuemp_no(in_pack->scust_auth, &customer);
		if(ret)
		{
			if('1' == in_pack->scust_type[0] )				//最后一条错误时，前面的都要插入
			{
				last_flag = 1;
				goto L_INSERTOTHER;
			}
			
			writelog(LOG_ERR,"read_by_stuemp_no[%s] err ",in_pack->scust_auth);
			if(ret == DB_NOTFOUND)
			{
				*pRetCode = E_DB_CUSTOMER_N;
				goto L_RETU;				
			}
			else
			{
				*pRetCode =  E_DB_CUSTOMER_R;	
				goto L_RETU;				
			}
		}
		input_relation.cut_id = customer.cut_id;
	}

	writelog(LOG_DEBUG,"TT %d\n",input_relation.cut_id);
	
	sprintf(input_relation.comment,"操作员%s",in_pack->scust_no);
	des2src(input_relation.outside_no,in_pack->sbank_acc);
	input_relation.outside_type = CUT_RELATION_TYPE_BANK;
     writelog(LOG_DEBUG,"TT1\n ");
	ret = DB_t_pif_cut_relation_tmp_add(&input_relation);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
			if(1 == input_relation.seqno)
			{
				//批次号重复
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
	writelog(LOG_DEBUG,"TT2\n ");
L_INSERTOTHER:
	flag = 1;
	if('1' == in_pack->scust_type[0] )
	{
		//最后一条记录已经导入
		ret = DB_t_pif_cut_relation_tmp_open_select_by_c1_and_batch_no(
		input_relation.batch_no);
		if(ret)
		{
			*pRetCode = E_DB_CUT_RLTN_TMP_R;
			goto L_RETU;
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
				goto L_RETU;
			}
			relation.cut_id = input_relation.cut_id;
			relation.outside_type = input_relation.outside_type;
			des2src(relation.outside_no,input_relation.outside_no);
			des2src(relation.comment,input_relation.comment);
			ret = DB_t_pif_cut_relation_add(&relation);
			if(ret)
			{
				
				memset(&customer,0,sizeof customer);
				DB_t_cif_customer_read_by_cut_id(input_relation.cut_id,&customer);
				if(DB_REPEAT == ret)
				{
					/*sprintf(szMsg,"导入序号[%d],学工号[%s],校区[%d]已存在"
						,input_relation.seqno,customer.stuemp_no,customer.area);
					writelog(LOG_ERR,szMsg);
					*pRetCode = E_DB_CUT_RLTN_I;
					goto L_RETU;*/
					writelog(LOG_DEBUG,"TT3\n ");
					DB_t_pif_cut_relation_update_by_cut_id(relation.cut_id,&relation);
				}
				else
				{
					sprintf(szMsg,"导入序号[%d],学工号[%s],校区[%d]有误,不能导入"
						,input_relation.seqno,customer.stuemp_no,customer.area);
					writelog(LOG_ERR,szMsg);
					*pRetCode = E_DB_CUT_RLTN_I;
					goto L_RETU;
				}
			}
			count++;
		}
		DB_t_pif_cut_relation_tmp_close_select_by_c1();
		sprintf(out_pack->vsmess,"批次号:%s,共成功导入%d条客户信息",input_relation.batch_no,count);
		flag=2;
	}
	if(2 != flag)
	{
		sprintf(out_pack->vsmess,"导入第%d记录,批次号:%s",input_relation.seqno,input_relation.batch_no);
	}
	des2src(out_pack->scust_limit,input_relation.batch_no);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	
	if(last_flag)		// 最后一条错误，先把前面的插入，再报错
	{
		db_commit();
		return  E_DB_CUSTOMER_R;	
	}

	return 0;
L_RETU:
	return -1;
}
