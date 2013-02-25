/* --------------------------------------------
 * 程序名称: F847182.sqc
 * 创建日期: 2004-12-14
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 查询商户设备表
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


int F847182(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    sqlint32	id=0;                         	//编号
    sqlint32	deviceid=0;                  	//设备标识
    double   	shop_id=0;                    	//商户标识
    char    	begin_date[10+1]="";          	//使用开始日期
    char    	begintime[8+1]="";           	//使用开始时间
    char    	endtime[8+1]="";             	//使用结束时间
    char    	end_date[10+1]="";            	//使用结束日期
    char    	comments[150+1]="";           	//备注
    sqlint16	indicator=0;
    char    	h_sqlcmd[1024]="";
    char   	shop_name[150+1]="";            //商户名称
    char  	device_name[150+1]="";         //设备名称

    int    ret=0;
    int    row=0;
    int   devid=0;
    char sPhyDevId[9]=" ";
    T_t_shop_pos tShopPos;
    T_t_shop tShop;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);

#ifdef DEBUG
    writelog(LOG_DEBUG,"phydev_id:sbank_pwd2[%s]",rPack->sbank_pwd2);
#endif
    ResetNormalCPack(&aPack,0,1);

    des2src(sPhyDevId, rPack->sbank_pwd2);
    ret=GetDevIdByDevPhyId(&devid, sPhyDevId);
    if(ret) {
        writelog(LOG_ERR,"ret[%d],phydevid[%s]",ret,sPhyDevId);
        *pRetCode=ret;
        goto L_RETU;
    }
    ret=DB_t_shop_pos_open_select_by_c0_and_deviceid(devid);
    if(ret) {
        *pRetCode=E_DB_SHOP_POS_R;
        writelog(LOG_ERR,"ret[%d],phydevid[%s]devid[%d]",ret,sPhyDevId,devid);
        goto L_RETU;
    }
    SetCol(handle,0);
    SetCol(handle,F_LVOL12,F_SCUSTTYPES,0);
    while(1) {
        memset(&tShopPos,0,sizeof(tShopPos));
        memset(&tShop,0,sizeof(tShop));
        ret=DB_t_shop_pos_fetch_select_by_c0(&tShopPos);
        if(ret) {
            if(DB_NOTFOUND==ret) {
                if(row)
                    break;
                else {
                    *pRetCode=E_DB_SHOP_POS_N;
                    goto L_RETU;
                }
            } else {
                *pRetCode=E_DB_SHOP_POS_R;
                goto L_RETU;
            }
        }
        row++;
        ret=DB_t_shop_read_by_shop_id(tShopPos.shop_id,&tShop);
        if(ret) {
            writelog(LOG_ERR,"ret[%d]shop_id[%d]",ret,tShopPos.shop_id);
            if(DB_NOTFOUND==ret)
                *pRetCode=E_SHP_ID_NOT_EXIST;
            else
                *pRetCode=E_DB_SHOP_R;
            DB_t_shop_pos_close_select_by_c0();
            goto L_RETU;
        }
        out_pack->lvol12=tShopPos.shop_id;
        des2src(out_pack->scusttypes,tShop.shop_name);
        PutRow(handle,out_pack,pRetCode, szMsg);
    }
    return 0;
L_RETU:
    return -1;
}
