/* ----------------------------------------------------------
 * 程序名称：F820124.sqc
 * 创建日期：2004-8-3
 * 程序作者：黄勋章
 * 版本信息：1.0.0.0
 * 程序功能：设备物理信息关键字查询
 * ----------------------------------------------------------

 * 修改日期: 2004-09-08
 * 修改人员: 张汉杰
 * 修改描述: 修改规范
 * 版本信息: 1.0.0.1
 * 备注信息
 * ----------------------------------------------------------*/

#include "busqc.h"
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "errdef.h"
#include "pubdb.h"
#include "dictionary.h"
#include "phydevice_stru.h"

// 函数名: F820124.sqc
// 编程  : 黄勋章 2004-8-31 09：44
// 描述  : 设备物理信息关键字查询
// 返回  : int 0 表示成功处理，其他作为处理失败
// 参数  : TRUSERID *handle 本请求数据的通讯请求端标识
// 参数  : ST_PACK *rPack 业务处理请求数据
// 参数  : int *iRetCode 处理结果的返回代码，0表示成功，其他就是处理失败，在本业务处理函数调用之前，已经被初始化为0
// 参数  : char *szMsg 处理结果的返回信息，在本业务处理函数调用之前，已经被初始化为空""

int F820124(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg) {
    T_t_phydevice aphydev;
    //int scode=0;
    int v_phytype=0;
    int nrows=0;
    int r=0;

    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    SetCol(handle,F_LVOL6,F_SPHONE,F_SPAGER,F_SCERT_NO,F_USSET1,0);

    memset(&aphydev,0,sizeof(aphydev));

    v_phytype = in_pack->lvol6;

    if(0==v_phytype) {
        DB_t_phydevice_open_select_by_c1();

        while(1) {

            memset(&aphydev,0,sizeof(aphydev));

            r=DB_t_phydevice_fetch_select_by_c1(&aphydev);

            if(0 != r) {
                if(SC_NOTFOUND == r) {
                    if(0 == nrows) {
                        *pRetCode=E_DB_PHYDEVICE_N;
                        sprintf(szMsg,"查询设备结构信息表无记录,SQLCODE=%d\n",SQLCODE);
                        writelog(LOG_WARNING,szMsg);
                        db_chk_err(__FILE__,__LINE__,&sqlca);
                        goto L_Ret_if;
                    }
                } else {
                    *pRetCode=E_DB_PHYDEVICE_R;
                    sprintf(szMsg,"读取设备结构信息表出错,SQLCODE=%d\n",SQLCODE);
                    writelog(LOG_WARNING,szMsg);
                    db_chk_err(__FILE__,__LINE__,&sqlca);
                    goto L_Ret_if;
                }
                break;
            }

            out_pack->lvol6 = aphydev.phytype;
            Strncpy_t(out_pack->sphone,aphydev.dname,sizeof(out_pack->sphone));
            Strncpy_t(out_pack->spager,aphydev.dtype,sizeof(out_pack->spager));
            Strncpy_t(out_pack->scert_no,aphydev.factory,sizeof(out_pack->scert_no));
            Strncpy_t((char*)out_pack->usset1,aphydev.comments,sizeof(out_pack->usset1));

            PutRow(handle,out_pack,pRetCode,szMsg);
            nrows++;

            if (15==nrows) {
                // 这里调用AnswerDataPart是为了不让前端等待太长时间，在有15条记录的时候就给返回，至于后续数据就不用管了，BCC与前端自动会将后续数据采集回去
                AnswerDataPart(handle,*pRetCode,szMsg);
            }
        };

        DB_t_phydevice_close_select_by_c1();
        return 0;

L_Ret_if:
        DB_t_phydevice_close_select_by_c1();
        return r;
    } else {
        r=DB_t_phydevice_read_by_phytype(v_phytype,&aphydev);
        if(SC_NOTFOUND==r) {
            *pRetCode=E_DB_PHYDEVICE_N;
            sprintf(szMsg,"设备物理信息表不存在相应记录,SQLCODE=%d\n",SQLCODE);

            writelog(LOG_ERR,szMsg);
            db_chk_err(__FILE__,__LINE__,&sqlca);
            goto L_Ret_else;
        } else if(r!=0) {
            *pRetCode=E_DB_PHYDEVICE_R;
            sprintf(szMsg,"设备物理信息表读取错误,SQLCODE=%d\n",SQLCODE);

            writelog(LOG_ERR,szMsg);
            db_chk_err(__FILE__,__LINE__,&sqlca);
            goto L_Ret_else;
        }
        out_pack->lvol6 =  aphydev.phytype;
        Strncpy_t(out_pack->sphone,aphydev.dname,sizeof(out_pack->sphone));
        Strncpy_t(out_pack->spager,aphydev.dtype,sizeof(out_pack->spager));
        Strncpy_t(out_pack->scert_no,aphydev.factory,sizeof(out_pack->scert_no));
        Strncpy_t((char*)out_pack->usset1,aphydev.comments,sizeof(out_pack->usset1));

        PutRow(handle,out_pack,pRetCode,szMsg);

        return 0;

L_Ret_else:
        return r;
    }
}
