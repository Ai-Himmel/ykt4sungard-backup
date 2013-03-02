/* --------------------------------------------
 * ��������: 2009-04-28
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ���CPU���ѻ���ˮ����
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
#include "acctrans.h"
#include "busqc.h"
#include "interfacefunc.h"
#include "interface.h"
#include "transfunc.h"

int F950056(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    writelog(LOG_INFO, "�豸����ID��=[%s],�豸��ˮ��=[%d],���׿���=[%d],����ǰ���=[%d],���׺���=[%d],���׽��=[%d],��������ʱ��=[%s],����ʱ��=[%s],�����״���=[%d],�̻���=[%d],����ѽ��=[%d],PSAM�ն˺�=[%s],��¼����=[%d],�Ƿ�����У�鿨��־=[%d],��ˮ����=[%d],��ϵͳ��־=[%d]",
             rPack->sphone3,
             rPack->lvol4,
             rPack->lvol5,
             rPack->lvol9,
             rPack->lvol10,
             rPack->lvol8,
             rPack->spost_code,
             rPack->spost_code2,
             rPack->lvol7,
             rPack->lvol3,
             rPack->lvol1,
             rPack->sstation0,
             rPack->lvol12,
             rPack->lvol11,
             rPack->lserial1,
             rPack->lcert_code
             );
    int ret = 0;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    T_t_posdtl posdtl;
    memset(&posdtl, 0, sizeof(posdtl));
    Cpack2Posdtl(rPack, posdtl);
    des2src(posdtl.coldate, pAccTrans->trans.transdate);
    des2src(posdtl.coltime, pAccTrans->trans.transtime);
    if (!strlen(posdtl.devphyid))
    {
        writelog(LOG_ERR, "recv offline posdtl err: devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",
                 posdtl.devphyid,
                 posdtl.devseqno,
                 posdtl.cardno,
                 posdtl.cardcnt,
                 posdtl.transdate,
                 posdtl.transtime
                );
        return ERRIF_POS_TERMID;
    }
    ret = GetDeviceidByDevphyid(posdtl.devphyid, &(posdtl.termid));
    if (ret)
    {
        writelog(LOG_ERR, "δ�ܲ����豸��ʶ��ret[%d]��devphyid[%s]", ret, posdtl.devphyid);
    }
    posdtl.status[0] = '1';
    T_t_device tDevice;
    memset(&tDevice, 0, sizeof(tDevice));
    ret = DB_t_device_read_by_deviceid(posdtl.termid, &tDevice);
    if (ret)
    {
        if (DB_NOTFOUND == ret)
        {
            posdtl.status[0] = '4';
            posdtl.errcode = E_NOTEXIST_DEVICE;
        }
        else
            return E_DB_DEVICE_R;
    }
    g_dbchkerr = 0;
    if ((strcmp(tDevice.devtypecode, "0244") == 0) || (strcmp(tDevice.devtypecode, "0245") == 0))
    {
        //ˮ������
        T_t_purseposdtl purseposdtl;
        memset(&purseposdtl, 0, sizeof(purseposdtl));
        des2src(purseposdtl.coldate, posdtl.coldate);
        des2src(purseposdtl.coltime, posdtl.coltime);
        purseposdtl.devseqno = posdtl.devseqno;                         //�ϴ�����ˮ��
        purseposdtl.transmark = posdtl.transmark;                       //999���ױ��
        purseposdtl.sysid  = posdtl.sysid;                      //�ϴ�����վ��ʶ(ǰ�û�ע���)
        des2src(purseposdtl.devphyid, posdtl.devphyid);
        purseposdtl.cardno = posdtl.cardno;                         //���׿���
        purseposdtl.pursetype = 4;                              //����ˮ��Ǯ����
        purseposdtl.cardbefbal = posdtl.cardbefbal;                         //�뿨���
        purseposdtl.cardaftbal = posdtl.cardaftbal;                     //�������
        purseposdtl.amount = posdtl.amount;                         //�������ѽ��
        purseposdtl.cardcnt = posdtl.cardcnt;                           //��ǰ�����ʻ����Ѵ���(�ۼ�ʹ�ô���)
        purseposdtl.status[0] = posdtl.status[0];
        purseposdtl.errcode = posdtl.errcode;
        if (tDevice.devphytype == PHYTYPE_999_DEV)
        {
            des2src(purseposdtl.transdate, posdtl.coldate);
            des2src(purseposdtl.transtime, posdtl.coltime);
        }
        else
        {
            des2src(purseposdtl.transdate, posdtl.transdate);
            des2src(purseposdtl.transtime, posdtl.transtime);
        }
        if ((amtcmp(posdtl.amount, -100) < 0) || (amtcmp(posdtl.amount, 100) > 0))
        {
            posdtl.errcode = E_999_AMT; //������
            posdtl.status[0] = '4';
            strcpy(posdtl.errmsg, "�������̫��");
        }
        g_dbchkerr = 0;
        ret = DB_t_purseposdtl_add(&purseposdtl);
        if (ret)
        {
            g_dbchkerr = 1;
            if (DB_REPEAT == ret)
            {
                writelog(LOG_ERR, "serial_no[%d]cardno[%d]devphyid[%s]transdate[%s]transtime[%s]ret[%d]", posdtl.devseqno, posdtl.cardno, posdtl.devphyid, posdtl.transdate, posdtl.transtime, ret);
                return 0;
            }
            else
                return E_DB_PURSEPOSDTL_I;
        }
        g_dbchkerr = 1;
    }
    else {
        //��ͨ����
        ret = DB_t_posdtl_add(&posdtl);
        if (ret)
        {
            g_dbchkerr = 1;
            if (DB_REPEAT != ret)
            {
                writelog(LOG_ERR, "ret[%d]devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]", ret, posdtl.devphyid, posdtl.devseqno, posdtl.cardno, posdtl.cardcnt, posdtl.transdate, posdtl.transtime);
                return ERRIF_DATABASE_INS;
            }
        }
        g_dbchkerr = 1;
    }
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_LVOL4, F_SPHONE3, 0);
    out_pack->lvol4 = rPack->lvol4;
    des2src(out_pack->sphone3, posdtl.devphyid);
    PutRow(handle, out_pack, pRetCode, szMsg);
    return 0;
}
