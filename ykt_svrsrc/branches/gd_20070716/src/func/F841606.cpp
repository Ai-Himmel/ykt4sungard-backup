/* --------------------------------------------
 * 程序名称: F841606.sqc
 * 创建日期: Aug  1 2005
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: EXECL 文件客户信息导入
 * --------------------------------------------
 * 修改日期: 2007-11-29
 * 修改人员: 韩海东
 * 修改描述: 修改导入插入临时表时模拟
 				插入正式表判断是否存在问
 				题，给前台提示
 * 版本信息: 1.0.0.1
 * 备注信息:
 * --------------------------------------------
 * 修改日期: 2007-12-05
 * 修改人员: 韩海东
 * 修改描述: 按照前台的要求，修改错误
 				返回时不走原有的架构，
 				retcode=0，具体的错误信息
 				在返回包中体现。
 * 版本信息: 1.0.0.2
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
	char sErrMsg[101]="";
	char sTempMsg[256]="";
	memset(&tCustomerTmp,0,sizeof(tCustomerTmp));
		
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_LIMIT,F_LVOL12,F_VSVARSTR0,0);

	tCustomerTmp.seqno=rPack->lvol4;
	if(1==tCustomerTmp.seqno)
	{
		flag=1;
		//取批次号
		getsysdatetime(tCustomerTmp.batch_no);
		while(1)
		{
			ret=DynamicStmtExecute("delete from ykt_cur.t_cif_customer_tmp where rownum<1000");
			if(ret)
			{
				if(ret != DB_NOTFOUND)
				{
					writelog(LOG_DEBUG,"导入人员信息失败[%d]",ret);
					*pRetCode=E_DYNAMIC_STMT_EXECUTE;
					goto L_RETU;
				}
				else break;
			}
			db_commit();
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
	ret = DB_t_pif_area_read_by_school_code(rPack->sbranch_code0,&tArea);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode = E_SCHOOL_CODE_NOT_EXIST;
		else
			*pRetCode = E_DB_AREA_R;
		sprintf(szMsg,"当前客户[%s]校区编号[%s]不正确",rPack->semail,rPack->sbranch_code0);
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
	
	
	des2src(tCustomerTmp.stuemp_no,rPack->scust_auth);
	des2src(tCustomerTmp.cut_name,rPack->semail);
	tCustomerTmp.cut_type=rPack->lvol0;
	tCustomerTmp.fee_type=rPack->lvol2;
	des2src(tCustomerTmp.sex,rPack->smarket_code);
	des2src(tCustomerTmp.man_id,rPack->scert_no);
	des2src(tCustomerTmp.phone,rPack->sphone);
	tCustomerTmp.area=tArea.area_no;
	des2src(tCustomerTmp.school_code,rPack->sbranch_code0);
	des2src(tCustomerTmp.dept_no,rPack->sname2);
	des2src(tCustomerTmp.s_code,rPack->scust_no2);
	des2src(tCustomerTmp.in_school_date,rPack->sdate0);
	des2src(tCustomerTmp.out_school_date,rPack->sdate1);
	tCustomerTmp.card_type=rPack->lvol3;
	des2src(tCustomerTmp.oper_code,rPack->sorder0);
	des2src(tCustomerTmp.status,rPack->scust_type);
	des2src(tCustomerTmp.class_no,rPack->sorder0);

	des2src(tCustomerTmp.man_idtype,rPack->sroom_no);
	des2src(tCustomerTmp.grade,rPack->sstation1);
	des2src(tCustomerTmp.country,rPack->snation_code);
	tCustomerTmp.nation=atol(rPack->sstat_type2);

	//模拟插入，然后会滚
	InPack.lvol3=tCustomerTmp.cut_type;
	InPack.lvol5=tCustomerTmp.fee_type;
	des2src(InPack.sname,tCustomerTmp.cut_name);
	InPack.lvol0=tCustomerTmpOut.area;
	des2src(InPack.scust_auth2, tCustomerTmp.stuemp_no);
	des2src(InPack.scust_no,tCustomerTmp.dept_no);
	des2src(InPack.scert_no,tCustomerTmp.man_id);
	des2src(InPack.sroom_no,tCustomerTmp.man_idtype);
	des2src(InPack.smarket_code,tCustomerTmp.sex);
	des2src(InPack.sphone,tCustomerTmp.phone);
	des2src(InPack.sphone3,tCustomerTmp.out_school_date);
	des2src(InPack.scust_no2,tCustomerTmp.s_code);
	des2src(InPack.scust_limit,tCustomerTmp.batch_no);
	des2src(InPack.sorder0,tCustomerTmp.class_no);
	des2src(InPack.sstation1,tCustomerTmp.grade);
	des2src(InPack.snation_code,tCustomerTmp.country);
	sprintf(InPack.sstat_type2,"%d",tCustomerTmp.nation);
	des2src(InPack.sbranch_code0,tCustomerTmp.school_code);

	ret=F841601(handle,iRequest,&InPack,pRetCode,szMsg);
	if(ret)
	{
		writelog(LOG_ERR,"F841601 EXEC ERR");
		sprintf(szMsg,"批次号[%s],第[%d]条姓名为[%s]的记录有误,不能导入.",
					tCustomerTmp.batch_no,rPack->lvol4,rPack->semail);
		goto L_RETU;
	}
	db_rollback();
	
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
		writelog(LOG_DEBUG,"导入第%d记录,批次号:%s,客户姓名:%s",
						tCustomerTmp.seqno,tCustomerTmp.batch_no,tCustomerTmp.cut_name);
		iCnt=0;
		ret=DB_t_cif_customer_tmp_open_select_by_c0_and_batch_no(tCustomerTmp.batch_no);
		if(ret)
		{
			*pRetCode=E_DB_CUSTOMER_TMP_R;
			writelog(LOG_ERR,"DB_t_cif_customer_tmp_fetch_select_by_c0 error,errcode=[%d]",ret);
			goto L_RETU_OUT;

		}
		while(1)
		{
			memset(&tCustomerTmpOut,0,sizeof(tCustomerTmpOut));
			memset(&InPack,0,sizeof(InPack));
			ret=DB_t_cif_customer_tmp_fetch_select_by_c0(&tCustomerTmpOut);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
				{
					writelog(LOG_ERR,"DB_t_cif_customer_tmp_fetch_select_by_c0 error,errcode=[%d]",ret);
					break;
				}
				else
				{
					writelog(LOG_ERR,"DB_t_cif_customer_tmp_fetch_select_by_c0 error,errcode=[%d]",ret);
					*pRetCode=E_DB_CUSTOMER_TMP_R;
					goto L_RETU_OUT;
				}
			}
			InPack.lvol3=tCustomerTmpOut.cut_type;
			InPack.lvol5=tCustomerTmpOut.fee_type;
			des2src(InPack.sname,tCustomerTmpOut.cut_name);
			InPack.lvol0=tCustomerTmpOut.area;
			des2src(InPack.scust_auth2, tCustomerTmpOut.stuemp_no);
			des2src(InPack.scust_no,tCustomerTmpOut.dept_no);
			des2src(InPack.scert_no,tCustomerTmpOut.man_id);
			des2src(InPack.sroom_no,tCustomerTmpOut.man_idtype);
			des2src(InPack.smarket_code,tCustomerTmpOut.sex);
			des2src(InPack.sphone,tCustomerTmpOut.phone);
			des2src(InPack.sphone3,tCustomerTmpOut.out_school_date);
			des2src(InPack.scust_no2,tCustomerTmpOut.s_code);
			des2src(InPack.scust_limit,tCustomerTmpOut.batch_no);
			des2src(InPack.sorder0,tCustomerTmpOut.class_no);
			des2src(InPack.sstation1,tCustomerTmpOut.grade);
			des2src(InPack.snation_code,tCustomerTmpOut.country);
			sprintf(InPack.sstat_type2,"%d",tCustomerTmpOut.nation);
			des2src(InPack.sbranch_code0,tCustomerTmpOut.school_code);
			ret=F841601(handle,iRequest,&InPack,pRetCode,szMsg);
			if(ret)
			{
				writelog(LOG_ERR,"F841601 EXEC ERR");
				DB_t_cif_customer_tmp_close_select_by_c0();
				sprintf(szMsg,"批次号[%s],第[%d]条姓名为[%s]的记录有误,不能导入.",
						tCustomerTmp.batch_no,rPack->lvol4,rPack->semail);
				goto L_RETU_OUT;
			}
			writelog(LOG_ERR,"批次号%s,第%d条姓名为%s的记录有误,正在转入正式表",tCustomerTmpOut.batch_no,tCustomerTmpOut.seqno,tCustomerTmpOut.cut_name);
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
	if(tCustomerTmp.status[0]=='1')
	{
		//最后一条,开始把临时表数据导入到客户表
		writelog(LOG_DEBUG,"导入第%d记录,批次号:%s,客户姓名:%s",tCustomerTmp.seqno,tCustomerTmp.batch_no,tCustomerTmp.cut_name);
		iCnt=0;
		ret=DB_t_cif_customer_tmp_open_select_by_c0_and_batch_no(tCustomerTmp.batch_no);
		if(ret)
		{
			*pRetCode=E_DB_CUSTOMER_TMP_R;
			writelog(LOG_ERR,"DB_t_cif_customer_tmp_fetch_select_by_c0 error,errcode=[%d]",ret);
			goto L_RETU_OUT;

		}
		while(1)
		{
			memset(&tCustomerTmpOut,0,sizeof(tCustomerTmpOut));
			memset(&InPack,0,sizeof(InPack));
			ret=DB_t_cif_customer_tmp_fetch_select_by_c0(&tCustomerTmpOut);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
				{
					writelog(LOG_ERR,"DB_t_cif_customer_tmp_fetch_select_by_c0 error,errcode=[%d]",ret);
					break;
				}
				else
				{
					writelog(LOG_ERR,"DB_t_cif_customer_tmp_fetch_select_by_c0 error,errcode=[%d]",ret);
					*pRetCode=E_DB_CUSTOMER_TMP_R;
					goto L_RETU_OUT;
				}
			}
			InPack.lvol3=tCustomerTmpOut.cut_type;
			InPack.lvol5=tCustomerTmpOut.fee_type;
			des2src(InPack.sname,tCustomerTmpOut.cut_name);
			InPack.lvol0=tCustomerTmpOut.area;
			des2src(InPack.scust_auth2, tCustomerTmpOut.stuemp_no);
			des2src(InPack.scust_no,tCustomerTmpOut.dept_no);
			des2src(InPack.scert_no,tCustomerTmpOut.man_id);
			des2src(InPack.sroom_no,tCustomerTmpOut.man_idtype);
			des2src(InPack.smarket_code,tCustomerTmpOut.sex);
			des2src(InPack.sphone,tCustomerTmpOut.phone);
			des2src(InPack.sphone3,tCustomerTmpOut.out_school_date);
			des2src(InPack.scust_no2,tCustomerTmpOut.s_code);
			des2src(InPack.scust_limit,tCustomerTmpOut.batch_no);
			des2src(InPack.sorder0,tCustomerTmpOut.class_no);
			des2src(InPack.sstation1,tCustomerTmpOut.grade);
			des2src(InPack.snation_code,tCustomerTmpOut.country);
			sprintf(InPack.sstat_type2,"%d",tCustomerTmpOut.nation);
			des2src(InPack.sbranch_code0,tCustomerTmpOut.school_code);
			ret=F841601(handle,iRequest,&InPack,pRetCode,szMsg);
			if(ret)
			{
				writelog(LOG_ERR,"F841601 EXEC ERR");
				DB_t_cif_customer_tmp_close_select_by_c0();
				sprintf(szMsg,"批次号%s,第%d条姓名为%s的记录有误,不能导入.",tCustomerTmpOut.batch_no,tCustomerTmpOut.seqno,tCustomerTmpOut.cut_name);
				goto L_RETU_OUT;
			}
			writelog(LOG_ERR,"批次号%s,第%d条姓名为%s的记录有误,正在转入正式表",tCustomerTmpOut.batch_no,tCustomerTmpOut.seqno,tCustomerTmpOut.cut_name);
			++iCnt;
		}
		sprintf(out_pack->vsmess,"批次号:%s,共成功导入%d条客户信息",tCustomerTmp.batch_no,iCnt);
		flag=2;
	}

	des2src(out_pack->scust_limit,tCustomerTmp.batch_no);
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
