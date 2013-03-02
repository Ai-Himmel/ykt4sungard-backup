/* --------------------------------------------
 * 程序名称: F841607.c
 * 创建日期: 2005-11-16
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: EXECL 文件照片信息导入
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

int F841607(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
/*
	int ret=0;
	int i=0;
	int iCnt=0;
	int flag=0;
	T_t_cif_phototmp tPhotoTmp;
	T_t_cif_phototmp tPhotoTmpOut;
	T_t_cif_photo  tYktPhoto;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tPhotoTmp,0,sizeof(T_t_cif_phototmp));
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_LIMIT,F_VSMESS,0);

	tPhotoTmp.seqno=rPack->lvol4;
	if(1==tPhotoTmp.seqno)
	{
		flag=1;
		//取批次号
		des2src(tPhotoTmp.batch_no,CAccTrans::getInstance()->trans.sysdatetime);
		ret=DynamicStmtExecute("delete from ykt_cur.t_cif_phototmp");
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
		des2src(tPhotoTmp.batch_no,rPack->scust_limit);
		if(strlen(tPhotoTmp.batch_no)!=14)
		{
			*pRetCode=E_INPUT_BATCH_NO;
			goto L_RETU;
		}
	}
	des2src(tPhotoTmp.stuemp_no,rPack->scust_auth);
	des2src(tPhotoTmp.stuemp_name,rPack->sname);
	des2src(tPhotoTmp.cut_type,rPack->sname2);
	des2src(tPhotoTmp.sex,rPack->smarket_code);
	des2src(tPhotoTmp.dept_code,rPack->scust_no);
	des2src(tPhotoTmp.s_code,rPack->scust_no2);
	des2src(tPhotoTmp.cur_grade,rPack->sorder0);
//	des2src(tCustomerTmp.status,rPack->scust_type);
	tPhotoTmp.is_inschool=rPack->lvol1;
	tPhotoTmp.status=rPack->lvol2;
	tPhotoTmp.area=rPack->lvol3;
	

	ret=DB_t_cif_phototmp_add(&tPhotoTmp);
	if(SQLCODE)
	{
		if(DB_REPEAT==SQLCODE)
		{
			if(1==tPhotoTmp.seqno)
			{
				//如果插入有冲突，则再重新生成新的批次号
				for(i=0;i<3;i++)
				{
					sleep(1);
					getsysdatetime(tPhotoTmp.batch_no);
					ret=DB_t_cif_phototmp_add(&tPhotoTmp);
					if(ret)
					{
						if(DB_REPEAT==SQLCODE)
							continue;
						else
						{
							*pRetCode=E_DB_PHOTOTMP_I;
							goto L_RETU;
						}
					}
					break;
				}
				if(i>=3)
				{
					writelog(LOG_ERR,"batch_no[%s]seqno[%d]",tPhotoTmp.batch_no,tPhotoTmp.seqno);
					*pRetCode=E_DB_PHOTOTMP_E;
					goto L_RETU;
				}
			}
			else
			{
				writelog(LOG_ERR,"batch_no[%s]seqno[%d]",tPhotoTmp.batch_no,tPhotoTmp.seqno);
				*pRetCode=E_DB_PHOTOTMP_E;
				goto L_RETU;
			}
		}
		else
		{
			writelog(LOG_ERR,"batch_no[%s]seqno[%d]",tPhotoTmp.batch_no,tPhotoTmp.seqno);
			*pRetCode=E_DB_PHOTOTMP_I;
			goto L_RETU;
		}
	}
	if(rPack->scust_type[0]=='1')
	{
		//最后一条,开始把临时表数据导入到照片表
		writelog(LOG_DEBUG,"导入第%d记录,批次号:%s,姓名:%s",tPhotoTmp.seqno,tPhotoTmp.batch_no,tPhotoTmp.stuemp_name);
		//因为照片库是联邦过来的，需要先提交事务，才能更新联邦数据库
		ret=db_commit();
		if(ret)
		{
			ret=E_DB_COMMIT;
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			goto L_RETU;
		}
		iCnt=0;
		ret=DB_t_cif_phototmp_open_select_by_c0_and_batch_no(tPhotoTmp.batch_no);
		while(1)
		{
			memset(&tPhotoTmpOut,0,sizeof(tPhotoTmpOut));
			ret=DB_t_cif_phototmp_fetch_select_by_c0(&tPhotoTmpOut);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
				{
					if(iCnt>0)
						break;
					else
					{
						*pRetCode=E_DB_PHOTOTMP_N;
						goto L_RETU;
					}
				}
				else
				{
					*pRetCode=E_DB_PHOTOTMP_R;
					goto L_RETU;
				}
			}
			memset(&tYktPhoto,0,sizeof(tYktPhoto));
			//导入照片表
			des2src(tYktPhoto.cur_grade,tPhotoTmpOut.cur_grade);
			des2src(tYktPhoto.cut_type,tPhotoTmpOut.cut_type);
			des2src(tYktPhoto.dept_code,tPhotoTmpOut.dept_code);
			tYktPhoto.is_inschool=tPhotoTmpOut.is_inschool;
			des2src(tYktPhoto.sex,tPhotoTmpOut.sex);
			des2src(tYktPhoto.stuemp_name,tPhotoTmpOut.stuemp_name);
			des2src(tYktPhoto.stuemp_no,tPhotoTmpOut.stuemp_no);
			des2src(tYktPhoto.s_code,tPhotoTmpOut.s_code);
			tYktPhoto.area=tPhotoTmpOut.area;
			ret=DB_t_cif_photo_add(&tYktPhoto);
			if(ret)
			{
				DB_t_cif_phototmp_close_select_by_c0();
				sprintf(szMsg,"批次号%s,第%d条姓名为%s的记录有误,不能导入.",tPhotoTmpOut.batch_no,tPhotoTmpOut.seqno,tPhotoTmpOut.stuemp_name);
				goto L_RETU;
			}
			writelog(LOG_DEBUG,"正在导入第[%d]条记录",iCnt);
			++iCnt;
		}
		sprintf(out_pack->vsmess,"批次号:%s,共成功导入%d条客户信息",tPhotoTmp.batch_no,iCnt);
		flag=2;
	}
	if(flag!=2)
	{
		sprintf(out_pack->vsmess,"导入第%d记录,批次号:%s,姓名:%s",tPhotoTmp.seqno,tPhotoTmp.batch_no,tPhotoTmp.stuemp_name);
	}
	des2src(out_pack->scust_limit,tPhotoTmp.batch_no);
	PutRow(handle,out_pack,pRetCode,szMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	return 0;
L_RETU:
*/
	return -1;
}
