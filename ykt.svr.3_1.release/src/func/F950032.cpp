/* --------------------------------------------
 * ��������: 2006-8-12
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: �豸ǩ��
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "acctrans.h"
#include "busqc.h"
#include "pubfunc.h"
#include "dbfunc_foo.h"
#include "interfacefunc.h"

int F950032(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
//	�豸����ID	char(20)	sphon3
//	����			int lvol0
//	POS������	char(8) sdate0
//	POS��ʱ��	char(6) stime0
//	��ϵͳID		int lcert_code
//	��̬��Կ	char(20)	scust_limit2
//
//	����	����	CPACK�ֶ�
//	�̻���		int lvol0
//	ϵͳ����	char(8) sdate0
//	ϵͳʱ��	char(6) stime0
//	POS��������ʼʱ��	char(6) stime1
//	POS����������ʱ��	char(6) stime2
//	�豸����	char(4) semp
//	�豸������Կ	char(16)	scert_addr
    int ret=0;
    ST_CPACK aPack;
    ST_PACK* out_pack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL0,F_SDATE0,F_STIME0,F_STIME1,F_STIME2,F_SEMP,F_SCERT_ADDR,0);
    char devphyid[31]="";
    char sysdate[9]="";
    char systime[7]="";
    ret=db_getsysdatetime(sysdate,systime);
    if(ret) {
        writelog(LOG_ERR,"db_getsysdatetime err=%d",ret);
        return ERRIF_DATABASE_DIS;
    }
    int sysid = rPack->lcert_code;
    int deviceid = rPack->lwithdraw_flag;
    int db_deviceid=0;
    des2src(devphyid,rPack->sphone3);
    writelog(LOG_INFO,"devphyid %s login start",devphyid);
    ret = ChkDynKey(sysid,rPack->scust_limit2);
    if(ret) {
        writelog(LOG_ERR,"chk_dyn_key sysid[%d] err=%d",sysid,ret);
        return ret;
    }
    ret=GetDeviceidByDevphyid(devphyid,&db_deviceid);
    if(ret) {
        return ret;
    }
    if(deviceid!=db_deviceid) {
        return ERRIF_POS_TERMID;
    }
    char devstatus[2]="";
    devstatus[0]=DEVRUNSTATUS_ONLINE;
    ret=UpdDevRunstatusByDeviceid(deviceid,devstatus);
    if(ret)
        return ret;
    int shopid=0;
    ret=GetShopidByDeviceid(deviceid,sysdate,systime,&shopid);
    if(ret) {
        return ret;
    }
    ret=GetDevtypecodeByDeviceid(deviceid,out_pack->semp);
    if(ret)
        return ret;
    out_pack->lvol0=shopid;
    strcpy(out_pack->sdate0,sysdate+2);
    strcpy(out_pack->stime0,systime);

    ret=GetSysParaVal(GLOBLE_SYSPARA_STATIC_KEY,out_pack->scert_addr);
    if(ret) {
        writelog(LOG_ERR,"get static key err=%d",ret);
        return ERRIF_DATABASE_QRY;
    }
    //ǩ��ʱ��ѯ��ˮ�ſ��Ʊ����û�и��豸�����һ��
    T_t_seqnoctl	tSeqnoctl;
    memset(&tSeqnoctl,0,sizeof(tSeqnoctl));
    ret=DB_t_seqnoctl_read_by_termid(deviceid,&tSeqnoctl);
    if(ret) {
        if(DB_NOTFOUND==ret) {
            tSeqnoctl.termid=deviceid;
            tSeqnoctl.termseqno=0;
            tSeqnoctl.accdate=atoi(sysdate);
            ret=DB_t_seqnoctl_add(&tSeqnoctl);
            if(ret) {
                if(DB_REPEAT==ret)
                    return E_DB_SEQNOCTL_E;
                else
                    return E_DB_SEQNOCTL_I;
            }
            return 0;
        } else
            return E_DB_SEQNOCTL_R;
    }
    PutRow(handle,out_pack,pRetCode,szMsg);
    writelog(LOG_INFO,"devphyid %s login success",devphyid);
    return 0;
}

