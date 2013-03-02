/* --------------------------------------------
 * 程序名称: F847130.c
 * 创建日期: 2005-12-7
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: EXECL 补助信息导入
 * --------------------------------------------
 * 修改日期: 2008-05-05 
 * 修改人员: 汤成
 * 修改描述: 原导入补助时检查客户有没有正常的卡，如果没有正常的卡，则不能导入补助信息，
 *			 但是这样的设计使得在导入补助信息时比较困难，有挂失、冻结的卡处理起来很麻烦，
 *			 在2007trunk 版本中，没有通过POS机领取补助功能，因此导入补助不需要对应到卡上，因此取消这个判断
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

	tSubsidyTmp.seqno=rPack->lvol1;						//顺序号
	if(strlen(rPack->scust_no)<1)						//补助操作员
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}

	if(1==tSubsidyTmp.seqno)
	{
		flag=1;
		//取批次号
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
	{	//补助批次号-大学城版本通过后台自动生成整数，取消原有的导入输入的方式
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
		strcpy(szMsg,"单笔补助最大金额未定义");
		*pRetCode = ret;
		return ret;
	}
	max_subsidy = D4U5(atof(temp),2);
	getsysdate(tSubsidyTmp.tx_date);
	getsystime(tSubsidyTmp.tx_time);
	des2src(stuemp_no,rPack->scust_auth);		//学号
	memset(&tCustomer,0,sizeof(tCustomer));
	//判断是否输入客户号，否则认为以学工号输入
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
			sprintf(szMsg,"学工号为%s的客户不存在",stuemp_no);
			*pRetCode=E_STUNO_NOT_EXIST;
			goto L_RETU;
		}
		tSubsidyTmp.cust_no = tCustomer.cut_id;
	}
	else
	{
		// 使用客户号作为标识
		tSubsidyTmp.cust_no = rPack->lvol0;
		ret = DB_t_cif_customer_read_by_cut_id(tSubsidyTmp.cust_no,&tCustomer);
		if(ret)
		{
			sprintf(szMsg,"客户号为%d 的客户不存在",tSubsidyTmp.cust_no);
			*pRetCode=E_CUSTOMER_NOT_EXIST;
			goto L_RETU;
		}

	}
	//des2src(tSubsidyTmp.subsidy_no,rPack->scust_limit2);		//补助批次号
	tSubsidyTmp.subsidy_no = atoi(rPack->scust_limit2);		//补助批次号
	des2src(tSubsidyTmp.oper_code,rPack->scust_no);			//操作员代码
	des2src(tSubsidyTmp.expire_date,rPack->sdate2);				//过期日期
	ret=IsInvalidDateTime(tSubsidyTmp.expire_date,"YYYYMMDD");
	if(ret)
	{
		sprintf(szMsg,"日期%s 格式不正确,正确格式为YYYYMMDD",tSubsidyTmp.expire_date);
		*pRetCode=ret;
		goto L_RETU;
	}
	tSubsidyTmp.amount=rPack->damt0;				//补助金额
	if(amtcmp(D4U5(tSubsidyTmp.amount,2),tSubsidyTmp.amount) != 0)
	{
		sprintf(szMsg,"补贴金额%f 只能精确到分",tSubsidyTmp.amount);
		*pRetCode = E_INPUT_AMT;
		goto L_RETU;

	}
	if(amtcmp(tSubsidyTmp.amount,max_subsidy) > 0
	   || amtcmp(tSubsidyTmp.amount,-max_subsidy) < 0)
	{
		sprintf(szMsg,"补贴金额%.2f元  超过单笔补助金额上限",tSubsidyTmp.amount);
		*pRetCode = E_INPUT_AMT;
		goto L_RETU;
	}
	strcpy(tSubsidyTmp.status,"1");						//状态(1-未领取，2-已领取)
	//检查一卡通系统是否不存在该学/工号
	/*
	   ret=IsInexistenceStuEmp(tSubsidyTmp.stuemp_no);
	   if(ret)
	   {
	   if(E_STUNO_NOT_EXIST==ret)
	   {
	   sprintf(szMsg,"学号%s在一卡通系统不存在",tSubsidyTmp.stuemp_no);
	   }
	 *pRetCode=ret;
	 goto L_RETU;
	 }
	 */
	//取得客户的当前卡号，写到临时补助表中，只能该卡片才能领取补助
	/*
	ret=get_curr_card_by_custid(tSubsidyTmp.cust_no, &t_card);
	if(ret)
	{
		sprintf(szMsg,"导入批次号%s,第%d条记录有误,找不到该客户的唯一卡号",tSubsidy.batch_no,tSubsidy.seqno);
		*pRetCode = ret;
		goto L_RETU;
	}
	tSubsidyTmp.card_no=t_card.card_id;
	*/
	// 检查客户是否有账户存在
	ret = is_cust_open_account(tSubsidyTmp.cust_no,ACCTYPE_PERMAIN);
	if(ret)
	{
		sprintf(szMsg,"客户[%d][%s]未开户，不能下发补助",tSubsidyTmp.cust_no,tCustomer.cut_name);
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
				//如果插入有冲突，则再重新生成新的批次号
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
		//得到当前的补助批次号
		ret = getNewUniqNo(KEYTYPE_TIF_SUBSIDY_NO,&dUniqno);  	
		if(ret)
		{
			*pRetCode = ret;
			writelog(LOG_ERR,"getNewUniqNo errcode = [%d]",ret);
			goto L_RETU;
		}

		//最后一条,开始把临时表数据导入到正式表
		writelog(LOG_DEBUG,"导入第%d条记录,导入批次号:%s,客户号%d",tSubsidyTmp.seqno,tSubsidyTmp.batch_no,tSubsidyTmp.cust_no);
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
				sprintf(szMsg,"导入批次号%s,第%d条记录有误,系统不允许一批补助存在正负两种金额",tSubsidy.batch_no,tSubsidy.seqno);
				goto L_RETU;
			}
			if(tSubsidyTmpOut.amount>0) incr =1;
			else incr=-1;
			memcpy(&tSubsidy,&tSubsidyTmpOut,sizeof(tSubsidy));
			//修改补助批次号为整数，后台自动生成，取消原有的前台输入的方式
			tSubsidy.subsidy_no=int(dUniqno);
			//导入补助信息表
			ret=DB_t_tif_subsidy_add(&tSubsidy);
			if(ret)
			{
				DB_t_tif_subsidytmp_close_select_by_c0();
				if(DB_REPEAT==ret)
					*pRetCode=E_DB_STUEMPNO_RE;
				else
					*pRetCode=E_DB_SUBSIDY_I;
				sprintf(szMsg,"导入批次号%s,第%d条记录有误,可能该学号的补助记录已经存在",tSubsidy.batch_no,tSubsidy.seqno);
				goto L_RETU;
			}
			dTotalAmt+=tSubsidy.amount;
			++iCnt;
		}
		sprintf(out_pack->vsmess,"导入批次号:%s,共成功导入%d条补助信息,补助金额总共%.2lf元",tSubsidyTmp.batch_no,iCnt,dTotalAmt);
		flag=2;
	}
	if(flag!=2)
	{
		sprintf(out_pack->vsmess,"导入第%d条记录,导入批次号:%s",tSubsidyTmp.seqno,tSubsidyTmp.batch_no);
	}
	des2src(out_pack->scust_limit,tSubsidyTmp.batch_no);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
	return -1;
}
