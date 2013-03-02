/* --------------------------------------------
 * 程序名称: F848020.c
 * 创建日期: 2005-12-12
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: EXECL 门禁人员信息导入
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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

int F848020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=0;
	int iCnt=0;
	int flag=0;
	T_t_customertmp	tCustomerTmp;
	T_t_customertmp	tCustomerTmpOut;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCustomerTmp,0,sizeof(tCustomerTmp));
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_LIMIT,F_VSMESS,0);
#ifdef DEBUG
	writelog(LOG_DEBUG,"stuempno      :scust_auth     [%s]",rPack->scust_auth);
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
		//取批次号
		getsysdatetime(tCustomerTmp.batchno);
		ret=DB_t_customer_tmp_del_by_opercode(rPack->scust_no);
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
		des2src(tCustomerTmp.batchno,rPack->scust_limit);
		if(strlen(tCustomerTmp.batchno)!=14)
		{
			*pRetCode=E_INPUT_BATCH_NO;
			goto L_RETU;
		}
	}
	des2src(tCustomerTmp.stuempno,rPack->scust_auth);
	des2src(tCustomerTmp.opercode,rPack->scust_no);
	if(strlen(tCustomerTmp.stuempno) == 0)
	{
		*pRetCode = E_INPUT_STUEMP_NO;
		sprintf(szMsg,"第%d条记录学工号为空",tCustomerTmp.seqno);
		goto L_RETU;
	}
	ret=DB_t_customer_tmp_add(&tCustomerTmp);
	if(ret)
	{
		if(DB_REPEAT==ret)
		{
			if(1==tCustomerTmp.seqno)
			{
				//如果插入有冲突，则再重新生成新的批次号
				for(i=0;i<3;i++)
				{
					sleep(1);
					getsysdatetime(tCustomerTmp.batchno);
					ret=DB_t_customer_tmp_add(&tCustomerTmp);
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
					writelog(LOG_ERR,"batchno[%s]seqno[%d]",tCustomerTmp.batchno,tCustomerTmp.seqno);
					*pRetCode=E_DB_CUSTOMER_TMP_E;
					goto L_RETU;
				}
			}
			else
			{
				writelog(LOG_ERR,"batchno[%s]seqno[%d]",tCustomerTmp.batchno,tCustomerTmp.seqno);
				*pRetCode=E_DB_CUSTOMER_TMP_E;
				goto L_RETU;
			}
		}
		else
		{
			writelog(LOG_ERR,"batchno[%s]seqno[%d]",tCustomerTmp.batchno,tCustomerTmp.seqno);
			*pRetCode=E_DB_CUSTOMER_TMP_I;
			goto L_RETU;
		}
	}
	if(rPack->scust_type[0]=='1')
	{
		//最后一条,开始把临时表数据导入到客户表
		writelog(LOG_DEBUG,"导入第%d记录,批次号:%s,学号:%s",tCustomerTmp.seqno,tCustomerTmp.batchno,tCustomerTmp,tCustomerTmp.stuempno);
		iCnt=0;
		ret=DB_t_customer_tmp_open_select_by_c0_and_batchno(tCustomerTmp.batchno);
		while(1)
		{
			memset(&tCustomerTmpOut,0,sizeof(tCustomerTmpOut));
			ret=DB_t_customer_tmp_fetch_select_by_c0(&tCustomerTmpOut);
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
			//更新客户表
			ret=UpdCustomerBatch_noByStuemp_no(tCustomerTmpOut.stuempno,tCustomerTmp.batchno);
			if(ret)
			{
				writelog(LOG_ERR,"UpdCustomerBatch_noByStuemp_no ret[%d]",ret);
				DB_t_customer_tmp_close_select_by_c0();
				*pRetCode=ret;
				sprintf(szMsg,"批次号%s,第%d条学号为%s的记录有误",tCustomerTmpOut.batchno,tCustomerTmpOut.seqno,tCustomerTmpOut.stuempno);
				goto L_RETU;
			}
			++iCnt;
		}
		sprintf(out_pack->vsmess,"导入批次号:%s,共成功更新客户信息表%d条记录",tCustomerTmp.batchno,iCnt);
		flag=2;
	}
	if(flag!=2)
	{
		sprintf(out_pack->vsmess,"导入第%d记录,批次号:%s,学号:%s",tCustomerTmp.seqno,tCustomerTmp.batchno,tCustomerTmp.stuempno);
	}
	des2src(out_pack->scust_limit,tCustomerTmp.batchno);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
	return -1;
}
