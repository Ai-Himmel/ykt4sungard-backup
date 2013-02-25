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
#include "busqc.h"

int F841606(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    int i=0;
    int iCnt=0;
    int flag=0;
    T_t_custtmp	 tCustomerTmp;
    T_t_feetype tFeetype;
    T_t_custtype tCusttype;
    T_t_dept tDept;
    T_t_area tArea;
    T_t_specialty tSpecialty;


    ST_CPACK aPack;
    ST_PACK InPack;
    ST_PACK *out_pack = &(aPack.pack);

    memset(&tCustomerTmp,0,sizeof(tCustomerTmp));
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_SCUST_LIMIT,F_VSMESS,0);

    tCustomerTmp.impseqno=rPack->lvol4;
    if(1==tCustomerTmp.impseqno) {
        flag=1;
        //取批次号
        des2src(tCustomerTmp.batchno,CAccTrans::getInstance()->trans.sysdatetime);
    } else {
        des2src(tCustomerTmp.batchno,rPack->scust_limit);
        if(strlen(tCustomerTmp.batchno)!=14) {
            *pRetCode=E_INPUT_BATCH_NO;
            goto L_RETU;
        }
    }
    if(strlen(rPack->semail) < 0) {
        *pRetCode = E_INPUT_DATA_INVAILD;
        sprintf(szMsg,"当前客户信息姓名为空!");
        goto L_RETU;
    }
    /*
    memset(&tFeetype,0,sizeof tFeetype);
    ret = DB_t_feetype_read_by_feetype(rPack->lvol2,&tFeetype);
    if(ret)
    {
    	*pRetCode = E_INPUT_DATA_INVAILD;
    	sprintf(szMsg,"当前客户[%s]收费类别[%d]不正确",rPack->semail
    		,rPack->lvol2);
    	goto L_RETU;
    }
    */
    memset(&tCusttype,0,sizeof tCusttype);
    ret = DB_t_custtype_read_by_custtype(rPack->lvol0,&tCusttype);
    if(ret) {
        *pRetCode = E_INPUT_DATA_INVAILD;
        sprintf(szMsg,"当前客户[%s]客户类别[%d]不正确",rPack->semail
                ,rPack->lvol0);
        goto L_RETU;
    }

    memset(&tArea,0,sizeof tArea);
    char areacode[4];
    sprintf(areacode,"%d",rPack->lvol1);
    ret = DB_t_area_read_by_areacode(areacode,&tArea);
    if(ret) {
        *pRetCode = E_INPUT_DATA_INVAILD;
        sprintf(szMsg,"当前客户[%s]校区编号[%d]不正确",rPack->semail
                ,rPack->lvol1);
        goto L_RETU;
    }

    if(strlen(rPack->smarket_code) > 0) {
        if(is_validate_sexno(rPack->smarket_code[0])) {
            *pRetCode = E_INPUT_DATA_INVAILD;
            sprintf(szMsg,"当前客户[%s]性别编号[%s]不正确",rPack->semail
                    ,rPack->smarket_code);
            goto L_RETU;
        }
    }
    memset(&tDept,0,sizeof tDept);
    if(strlen(rPack->sname2) > 0) {
        ret = DB_t_dept_read_by_deptcode(rPack->sname2,&tDept);
        if(ret) {
            if(DB_NOTFOUND == ret) {
                *pRetCode = E_INPUT_DATA_INVAILD;
                sprintf(szMsg,"当前客户[%s]部门编号[%s]不正确",rPack->semail
                        ,rPack->sname2);
            } else
                *pRetCode = E_DB_AREA_R;
            goto L_RETU;
        }
    }


    memset(&tSpecialty,0,sizeof tSpecialty);
    if(strlen(rPack->scust_no2)>0) {
        ret= DB_t_specialty_read_by_specialtycode(rPack->scust_no2,&tSpecialty);
        if(ret) {
            if(DB_NOTFOUND == ret) {
                *pRetCode = E_INPUT_DATA_INVAILD;
                sprintf(szMsg,"当前客户[%s]专业编号[%s]不正确",rPack->semail
                        ,rPack->scust_no2);
            } else
                *pRetCode = E_DB_SPECIALTY_R;
            goto L_RETU;
        }
    }
    des2src(tCustomerTmp.stuempno,rPack->scust_auth);
    des2src(tCustomerTmp.custname,rPack->semail);
    tCustomerTmp.custtype=rPack->lvol0;
    tCustomerTmp.feetype=rPack->lvol2;
    des2src(tCustomerTmp.sex,rPack->smarket_code);
    des2src(tCustomerTmp.idno,rPack->scust_auth2);
    des2src(tCustomerTmp.tel,rPack->sphone);
    des2src(tCustomerTmp.areacode,rPack->sbranch_code0);
    des2src(tCustomerTmp.deptcode,rPack->sname2);
    des2src(tCustomerTmp.specialtycode,rPack->scust_no2);
    des2src(tCustomerTmp.indate,rPack->sdate0);
    des2src(tCustomerTmp.outdate,rPack->sdate1);
    des2src(tCustomerTmp.opercode,rPack->sorder0);
    des2src(tCustomerTmp.classcode,rPack->sorder0);

    ret=DB_t_custtmp_add(&tCustomerTmp);
    if(SQLCODE) {
        if(DB_REPEAT==SQLCODE) {
        } else {
            writelog(LOG_ERR,"batchno[%s]seqno[%d]",tCustomerTmp.batchno,tCustomerTmp.impseqno);
            *pRetCode=E_DB_CUSTOMER_TMP_I;
            goto L_RETU;
        }
    }
    return 0;
L_RETU:
    return -1;
}
