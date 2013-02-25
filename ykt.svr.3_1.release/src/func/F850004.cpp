/* --------------------------------------------
 * ��������: 2009-10-10
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: �����豸����Աǩ��
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
#include "dbfunc_foo.h"
#include "busqc.h"
#include "interfacefunc.h"
#include "acctrans.h"
int F850004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret;
    int deviceid=0;
    char termno[13]= {0};

    CAccTrans *pAccTrans=CAccTrans::getInstance();
    ST_CPACK aPack;
    ST_PACK *out_pack;
    out_pack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL0,F_LVOL3,F_SALL_NAME,0);

    des2src(termno,rPack->sserial0);
    ret=GetDeviceidByDevphyid(termno,&deviceid);
    if(ret) {
        writelog(LOG_ERR,"termno[%s]",termno);
        return ret;
    }
    // ��� psam �еĻ�����
    T_t_device tDevice;

    memset(&tDevice,0,sizeof(tDevice));
    ret=DB_t_device_read_by_deviceid(deviceid,&tDevice);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_DEVICE;
        else
            return E_DB_DEVICE_R;
    }
    if(tDevice.status[0]!=STATUS_NORMAL)
        return E_DEVICE_LOGOUT;
    T_t_psamcard psamcard;
    memset(&psamcard,0,sizeof(psamcard));
    ret=DB_t_psamcard_read_by_termno(termno,&psamcard);
    if(ret) {
        writelog(LOG_ERR,"termno[%s]",termno);
        CHECK_DB_ERR;
        if(DB_NOTFOUND == ret)
            return E_DB_PSAMCARD_N;
        else
            return E_DB_PSAMCARD_R;
    }
    char devstatus[2]= {0};
    devstatus[0]=DEVRUNSTATUS_ONLINE;
    ret=UpdDevRunstatusByDeviceid(deviceid,devstatus);
    if(ret) {
        writelog(LOG_ERR,"UpdDevRunstatusByDeviceid deviceid[%d]",deviceid);
        return ret;
    }
    T_t_operator  tOper;
    memset(&tOper,0,sizeof(tOper));
    ret=DB_t_operator_read_lock_by_c0_and_opercode(rPack->semp_no,&tOper);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_OPER;
        else
            return E_DB_OPERATOR_R;
    }
    if(tOper.status[0]!=STATUS_NORMAL) {
        DB_t_operator_free_lock_by_c0();
        return ERRINFO(E_OPERLOGON_UNREG,tOper.opercode);
    }
    //����Ա��¼,У�����Ա����
    ret=ChkOperPwd(tOper.opercode,rPack->semp_pwd);
    if(ret) {
        DB_t_operator_free_lock_by_c0();
        return ret;
    }
    tOper.loginsiteno=deviceid;
    tOper.loginflag[0]='1';
    db_getsysdatetime2(tOper.logintime);
    ret=DB_t_operator_update_lock_by_c0(&tOper);
    if(ret) {
        return E_DB_OPERATOR_U;
    }
    //�޸Ĳ���Ա��¼״̬Ϊ1
    SetCol(handle,0);
    SetCol(handle,F_LWITHDRAW_FLAG,0);
    rPack->lwithdraw_flag = deviceid;
    writelog(LOG_INFO,"�ն�%dǩ���ɹ�",deviceid);
    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
}
