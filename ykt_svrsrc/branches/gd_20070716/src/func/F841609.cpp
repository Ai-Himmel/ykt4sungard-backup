/* --------------------------------------------
 * 程序名称: F841609.sqc
 * 创建日期: Sep 29 2004
 * 程序作者: auto creat by wen jian
 * 版本信息: 1.0.0.0
 * 程序功能: 批量生成临时客户号
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

	CustomerCount=rPack->lvol0;//	数量
	memset(&tCuttype,0,sizeof(tCuttype));

//先增加客户
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
		strcpy(szMsg,"请正确配置临时人员客户类别");
		goto L_RETU;
	}
	ret = DB_t_cif_cuttypefee_read_by_cut_type(tCustomer.cut_type,&tCuttype);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			*pRetCode = E_DB_CUTTYPEFEE_N;
			strcpy(szMsg,"请正确配置临时人员收费类别");
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
		strcpy(szMsg,"请正确配置临时人员收费类别");
		goto L_RETU;
	}
	memset(&tFeetype,0,sizeof tFeetype);
	ret = DB_t_pif_feetype_read_by_fee_type(tCustomer.fee_type,&tFeetype);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			*pRetCode = E_DB_FEETYPE_N;
			strcpy(szMsg,"请正确配置临时人员收费类别");
		}
		else
			*pRetCode = E_DB_FEETYPE_R;
		goto L_RETU;
	}
	tCustomer.cut_state=CUSTSTAT_REGIST;
	des2src(tCustomer.is_havecard,TYPE_NO);
	strcpy(tCustomer.cut_name,"临时人员");	//客户名称
	tCustomer.enableid[0]='2';				//身份禁用标志1-禁用2-启用
	tCustomer.use_flag[0]='0';
	strcpy(tCustomer.school_code,rPack->sbranch_code0);	//校区
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
	sprintf(out_pack->vsmess,"生成批次号%s,客户号从%d到%d共%d个客户自动生成完成",tCustomer.batch_no,start_no,tCustomer.cut_id,CustomerCount);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
	return -1;
}
