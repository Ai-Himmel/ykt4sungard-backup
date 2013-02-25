/* ----------------------------------------------------------
 * 创建日期：2008-09-08
 * 程序作者：闻剑
 * 版本信息：3.0.0.0
 * 程序功能：前置机签到
 * ----------------------------------------------------------*/
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
int F930052(TRUSERID * handle, int iRequest, ST_PACK * rPack, int *iRetCode, char *szMsg) {
    ST_PACK outPack;				//返回包
    int ret = 0;
    char initkey[33]="";

    int sysid = rPack->lcert_code;
    des2src(initkey, rPack->scust_limit);

    writelog(LOG_DEBUG,"前置机%d签到",rPack->lcert_code);
    //预注册、注销的子系统不能签到
    T_t_subsystem subsystem;

    memset(&subsystem,0,sizeof(subsystem));
    ret=DB_t_subsystem_read_lock_by_c0_and_sysid(sysid,&subsystem);
    if(ret) {
        writelog(LOG_ERR,"sysid[%d] not exist ",sysid);
        if(DB_NOTFOUND==ret)
            return ERRIF_FRONT_NOREG;
        else
            return ERRIF_DATABASE_QRY;
    }
    if(subsystem.status[0]!=STATUS_NORMAL) {
        DB_t_subsystem_free_lock_by_c0();
        return ERRIF_FRONT_CLOSE;
    }
    if(subsystem.runstatus[0]==SUBSYSRUNSTAT_DEACTIVE) {
        DB_t_subsystem_free_lock_by_c0();
        return ERRIF_FRONT_NOACTIVE;
    }
    //匹配初始密钥
    if(strcmp(subsystem.initkey,initkey)!=0)
        if (ret) {
            DB_t_subsystem_free_lock_by_c0();
            writelog(LOG_ERR,"db init_key[%s]in init key[%s]",subsystem.initkey,initkey);
            return ERRIF_FRONT_NOLOGIN;
        }
    //产生动态密钥
    GetDynaKey(subsystem.dynakey);
    subsystem.runstatus[0]=SUBSYSRUNSTAT_ONLINE;
    ret=DB_t_subsystem_update_lock_by_c0(&subsystem);
    if(ret) {
        return ERRIF_DATABASE_UPD;
    }
    //返回数据
    SetCol(handle,F_SCUST_LIMIT,F_SCUST_LIMIT2,F_SNOTE,F_SCERT_ADDR, F_SADDR
           ,F_SEMAIL2,F_SEMAIL,F_LVOL0,0);

    //返回签到共公数据
    /*
    ret=GetSysParaVal(GLOBE_999_SHUTTIMES,ho_ShutTimes);
    if( ret)
    {
    	*iRetCode = ret;
    	goto L_RETU;
    }
    */
    char authpwd[33]="";
    ret=GetSysParaVal(GLOBE_999_DEVAUTHKEY,authpwd);
    if( ret) {
        writelog(LOG_ERR,"取设备授权密钥错误");
        return ERRIF_DATABASE_QRY;
    }
//	char card65pwd[33]="";
//	ret=GetSysParaVal(GLOBE_999_65CARDKEY,card65pwd);
//	if( ret)
//	{
//		writelog(LOG_ERR,"取卡密钥错误");
//		return ret;
//	}
    char purseno[33]="";
    ret=GetSysParaVal(GLOBE_WATER_PURSE_NO,purseno);
    if(ret) {
        writelog(LOG_ERR,"取水控钱包号错误");
        if(E_DB_SYSPARA_N == ret)
            outPack.lvol0 = PURSE_NO_ONE;
        else {
            return ERRIF_DATABASE_QRY;
        }
    } else {
        outPack.lvol0 = atoi(purseno);
    }
    /*
    	ret=get_max_black_list_version(max_black_list_ver);
    	if(ret)
    	{
    		*iRetCode = ret;
    		goto L_RETU;
    	}
    */
//	ret=GetSysParaVal(GLOBE_BLACKSHEETTIME,ho_BSheetVDate);
//	if( ret)
//	{
//		*iRetCode = ret;
//		goto L_RETU;
//	}
    ret=GetSysParaVal(GLOBE_PURSE_TWO_CARDKEY,outPack.scust_limit);
    if(ret) {
        return ERRIF_DATABASE_QRY;
    }
//	des2src(outPack.snote, ho_ShutTimes, sizeof(outPack.snote));
    des2src(outPack.scert_addr, authpwd);
//	des2src(outPack.saddr, card65pwd);
    char blkverendate[]="991231235959";
    des2src(outPack.semail, blkverendate);
    des2src(outPack.scust_limit2, subsystem.dynakey);
    PutRow(handle, &outPack, iRetCode, szMsg);
    return 0;
}
