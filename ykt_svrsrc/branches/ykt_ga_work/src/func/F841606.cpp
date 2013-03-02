/* --------------------------------------------
 * 程序名称: F841606.sqc
 * 创建日期: Aug  1 2005
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: EXECL 文件客户信息导入
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

int F841601(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

int F841606(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=0;
	int iCnt=0;
	int flag=0;
	T_t_cif_customer_tmp	tCustomerTmp;
	T_t_cif_customer_tmp	tCustomerTmpOut;
	T_t_pif_feetype tFeetype;
	T_t_cif_cuttypefee tCuttypefee;
	T_t_cif_dept tDept;
	T_t_pif_area tArea;
	T_t_cif_speciality tSpeciality;
	
	
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
	writelog(LOG_DEBUG,"phone          :sphome         [%s]",rPack->sphone);
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
		//取批次号
		getsysdatetime(tCustomerTmp.batch_no);
		ret=DynamicStmtExecute("delete from ykt_cur.t_cif_customer_tmp ");
		if(ret)
		{
			if(ret != DB_NOTFOUND)
			{
				writelog(LOG_DEBUG,"导入人员信息失败[%d]",ret);
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
	if(strlen(rPack->semail) < 0)
	{
		*pRetCode = E_INPUT_DATA_INVAILD;
		sprintf(szMsg,"当前客户信息姓名为空!");
		goto L_RETU;
	}
	memset(&tFeetype,0,sizeof tFeetype);
	ret = DB_t_pif_feetype_read_by_fee_type(rPack->lvol2,&tFeetype);
	if(ret)
	{
		*pRetCode = E_INPUT_DATA_INVAILD;
		sprintf(szMsg,"当前客户[%s]收费类别[%d]不正确",rPack->semail
			,rPack->lvol2);
		goto L_RETU;
	}
	memset(&tCuttypefee,0,sizeof tCuttypefee);
	ret = DB_t_cif_cuttypefee_read_by_cut_type(rPack->lvol0,&tCuttypefee);
	if(ret)
	{
		*pRetCode = E_INPUT_DATA_INVAILD;
		sprintf(szMsg,"当前客户[%s]客户类别[%d]不正确",rPack->semail
			,rPack->lvol0);
		goto L_RETU;
	}

	memset(&tArea,0,sizeof tArea);
	ret = DB_t_pif_area_read_by_area_no(rPack->lvol1,&tArea);
	if(ret)
	{
		*pRetCode = E_INPUT_DATA_INVAILD;
		sprintf(szMsg,"当前客户[%s]校区编号[%d]不正确",rPack->semail
			,rPack->lvol1);
		goto L_RETU;
	}

	if(strlen(rPack->smarket_code) > 0)
	{
		if(is_validate_sexno(rPack->smarket_code[0]))
		{
			*pRetCode = E_INPUT_DATA_INVAILD;
			sprintf(szMsg,"当前客户[%s]性别编号[%s]不正确",rPack->semail
				,rPack->smarket_code);
			goto L_RETU;
		}
	}
	memset(&tDept,0,sizeof tDept);
	if(strlen(rPack->sname2) > 0)
	{
		ret = DB_t_cif_dept_read_by_dept_code(rPack->sname2,&tDept);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				*pRetCode = E_INPUT_DATA_INVAILD;
				sprintf(szMsg,"当前客户[%s]部门编号[%s]不正确",rPack->semail
					,rPack->sname2);
			}
			else
				*pRetCode = E_DB_AREA_R;
			goto L_RETU;
		}
	}


	memset(&tSpeciality,0,sizeof tSpeciality);
	if(strlen(rPack->scust_no2)>0)
	{
		ret= DB_t_cif_speciality_read_by_s_code(rPack->scust_no2,&tSpeciality);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				*pRetCode = E_INPUT_DATA_INVAILD;
				sprintf(szMsg,"当前客户[%s]专业编号[%s]不正确",rPack->semail
					,rPack->scust_no2);
			}
			else
				*pRetCode = E_DB_SPECIALITY_R;
			goto L_RETU;
		}
	}
	
	
	des2src(tCustomerTmp.stuemp_no,rPack->scust_auth2);
	des2src(tCustomerTmp.cut_name,rPack->semail);
	tCustomerTmp.cut_type=rPack->lvol0;
	tCustomerTmp.fee_type=rPack->lvol2;
	des2src(tCustomerTmp.sex,rPack->smarket_code);
	des2src(tCustomerTmp.man_id,rPack->scust_auth);
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
				//如果插入有冲突，则再重新生成新的批次号
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
		//最后一条,开始把临时表数据导入到客户表
		writelog(LOG_DEBUG,"导入第%d记录,批次号:%s,客户姓名:%s",tCustomerTmp.seqno,tCustomerTmp.batch_no,tCustomerTmp.cut_name);
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
				sprintf(szMsg,"批次号%s,第%d条姓名为%s的记录有误,不能导入.",tCustomerTmpOut.batch_no,tCustomerTmpOut.seqno,tCustomerTmpOut.cut_name);
				goto L_RETU;
			}
			++iCnt;
		}
		sprintf(out_pack->vsmess,"批次号:%s,共成功导入%d条客户信息",tCustomerTmp.batch_no,iCnt);
		flag=2;
	}
	if(flag!=2)
	{
		sprintf(out_pack->vsmess,"导入第%d记录,批次号:%s,客户姓名:%s",tCustomerTmp.seqno,tCustomerTmp.batch_no,tCustomerTmp.cut_name);
	}
	des2src(out_pack->scust_limit,tCustomerTmp.batch_no);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
	return -1;
}
