/* --------------------------------------------
 * ��������: F930031.sqc
 * ��������: 9 17 2004
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:  �ռ�������ˮ����
 * --------------------------------------------
 * �޸�����:2004-10-12
 * �޸���Ա:    �Ž�
 * �޸�����:���Ӽ��˽��״���
 * �汾��Ϣ:1.0.0.1
 * ��ע��Ϣ:
 * --------------------------------------------
 * �޸�����:2011-06-19
 * �޸���Ա:    ����
 * �޸�����:������Ǯ��ˮ�ؽ��׹��ˣ�����100Ԫ��ֱ�ӱ��Ϊ�쳣��ˮ
 *          ������Ǯ����ͨ���׹��ˣ�����1000Ԫ��ֱ�ӱ��Ϊ�쳣��ˮ
 * �汾��Ϣ:1.0.0.2
 * ��ע��Ϣ:
 * --------------------------------------------
 * �޸�����:2011-12-18
 * �޸���Ա:    ����
 * �޸�����:������Ǯ��ˮ�ؽ��׹��ˣ�����100Ԫ��ֱ�ӱ��Ϊ�쳣��ˮ
 *          ������Ǯ����ͨ���׹��ˣ�����1000Ԫ��ֱ�ӱ��Ϊ�쳣��ˮ
 * �汾��Ϣ:1.0.0.2
 * ��ע��Ϣ:
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
#include "interfacefunc.h"
#include "busqc.h"
int F930031(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg) {
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    int ret = 0;
    T_t_posdtl posdtl;
    memset(&posdtl, 0, sizeof(posdtl));
    writelog(LOG_INFO, "phyid:sphone3[%s],sdate1[%s]", rPack->sphone3, rPack->sdate1);
    if (strlen(rPack->sphone3) > 0)
        des2src(posdtl.devphyid, rPack->sphone3);               // ����豸����ID(10λ)
    else
        des2src(posdtl.devphyid, rPack->sdate1);                //�����豸ID
    ret = GetDeviceidByDevphyid(posdtl.devphyid, &(posdtl.termid));
    if (ret) {
        if (ret != ERRIF_POS_NOREG)
            return ret;
    }
    T_t_device tDevice;
    memset(&tDevice, 0, sizeof(tDevice));
    ret = DB_t_device_read_by_deviceid(posdtl.termid, &tDevice);
    if (ret) {
        if (DB_NOTFOUND == ret) {
            //��Ϊ�������������豸����ID����ͻ��,�����Ҳ����豸,��������statusΪ4(��Ч��ˮ������)����������ǰ�ö���������ˮ
//          if((strcmp(tDevice.devtypecode,"0244")==0)||(strcmp(tDevice.devtypecode,"0245")==0))
//          {
            posdtl.status[0] = '4';
            posdtl.errcode = E_NOTEXIST_DEVICE;
//          }else{
//              return E_NOTEXIST_DEVICE;
//          }
        } else
            return E_DB_DEVICE_R;
    }
    des2src(posdtl.coldate, pAccTrans->trans.transdate);
    des2src(posdtl.coltime, pAccTrans->trans.transtime);
    posdtl.devseqno = rPack->lvol4;                         //�ϴ�����ˮ��
    posdtl.transmark = rPack->lvol12;                       //999���ױ��
    posdtl.sysid  = rPack->lcert_code;                      //�ϴ�����վ��ʶ(ǰ�û�ע���)
//  posdtl.managefee= rPack->lvol11;                        //
    posdtl.cardno = rPack->lvol5;                           //���׿���
    posdtl.purseno = 0;
    posdtl.cardbefbal = rPack->lvol9 / 100.0;                       //�뿨���
    posdtl.cardaftbal = rPack->lvol10 / 100.0;                      //�������
    posdtl.amount = rPack->lvol8 / 100.0;                       //�������ѽ��
    posdtl.cardcnt = rPack->lvol7;                          //��ǰ�����ʻ����Ѵ���(�ۼ�ʹ�ô���)
    snprintf(posdtl.transdate, 9, "20%s", rPack->spost_code);   //��������(��ʽ�����������)
    des2src(posdtl.transtime, rPack->spost_code2);          //����ʱ��(��ʽ�������ʱ��)
    if (posdtl.status[0] == 0) {
        posdtl.status[0] = '1';
    }
    if (strcmp(posdtl.transdate, "20000000") != 0) {
        ret = IsInvalidDateTime(posdtl.transdate, "YYYYMMDD");
        if (ret) {
            posdtl.errcode = E_999_DATE; //�ϴ���ˮ������������
            posdtl.status[0] = '4';
            strcpy(posdtl.errmsg, "�������ڸ�ʽ����");
        }
        ret = IsInvalidDateTime(posdtl.transtime, "HHMMSS");
        if (ret) {
            posdtl.errcode = E_999_TIME; //�ϴ���ˮ����ʱ������
            posdtl.status[0] = '4';
            strcpy(posdtl.errmsg, "����ʱ���ʽ����");
        }
    } else {
        des2src(posdtl.transdate, posdtl.coldate);
        des2src(posdtl.transtime, posdtl.coltime);
    }
    //ά���豸���״̬
    T_t_devmonitor dev_monitor;
    memset(&dev_monitor, 0, sizeof dev_monitor);
    ret = DB_t_devmonitor_read_by_deviceid(tDevice.deviceid, &dev_monitor);
    des2src(dev_monitor.optime, CAccTrans::getInstance()->trans.sysdatetime);
    des2src(dev_monitor.coltime, CAccTrans::getInstance()->trans.sysdatetime);
    des2src(dev_monitor.devtime, CAccTrans::getInstance()->trans.sysdatetime);
    dev_monitor.deviceid = tDevice.deviceid;
    dev_monitor.beatstatus = 1;
    if (ret) {
        if (DB_NOTFOUND == ret) {
            ret = DB_t_devmonitor_add(&dev_monitor);
            if (ret) {
                writelog(LOG_ERR, "�����豸��ؼ�¼ʧ��!deviceid=[%d]", tDevice.deviceid);
            }
        }
    } else {
        ret = DB_t_devmonitor_update_by_deviceid(tDevice.deviceid, &dev_monitor);
        if (ret) {
            writelog(LOG_ERR, "�����豸��ؼ�¼ʧ��!deviceid=[%d]",tDevice.deviceid);
            if (DB_NOTFOUND == ret) {
                ret = DB_t_devmonitor_add(&dev_monitor);
                if (ret) {
                    writelog(LOG_ERR, "�����豸ʧ�ܺ������豸��ؼ�¼Ҳʧ��!deviceid=[%d]", tDevice.deviceid);
                }
            }
        }
    }
    if ((strcmp(tDevice.devtypecode, "0244") == 0) || (strcmp(tDevice.devtypecode, "0245") == 0)) {
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
        if (tDevice.devphytype == PHYTYPE_999_DEV) {
            des2src(purseposdtl.transdate, posdtl.coldate);
            des2src(purseposdtl.transtime, posdtl.coltime);
        } else {
            des2src(purseposdtl.transdate, posdtl.transdate);
            des2src(purseposdtl.transtime, posdtl.transtime);
        }
        if ((amtcmp(posdtl.amount, -100) < 0) || (amtcmp(posdtl.amount, 100) > 0)) {
            posdtl.errcode = E_999_AMT; //������
            posdtl.status[0] = '4';
            strcpy(posdtl.errmsg, "�������̫��");
        }
        g_dbchkerr = 0;
        ret = DB_t_purseposdtl_add(&purseposdtl);
        if (ret) {
            g_dbchkerr = 1;
            if (DB_REPEAT == ret) {
                writelog(LOG_ERR, "serial_no[%d]cardno[%d]devphyid[%s]transdate[%s]transtime[%s]ret[%d]", posdtl.devseqno, posdtl.cardno, posdtl.devphyid, posdtl.transdate, posdtl.transtime, ret);
                return 0;
            } else
                return E_DB_PURSEPOSDTL_I;
        }
        g_dbchkerr = 1;
    } else {
        //��ͨ����
        if ((amtcmp(posdtl.amount, -1000) < 0) || (amtcmp(posdtl.amount, 1000) > 0)) {
            posdtl.errcode = E_999_AMT; //������
            posdtl.status[0] = '4';
            strcpy(posdtl.errmsg, "�������̫��");
        }
        g_dbchkerr = 0;
        ret = DB_t_posdtl_add(&posdtl);
        if (ret) {
            g_dbchkerr = 1;
            if (DB_REPEAT == ret) {
                writelog(LOG_ERR, "������ˮ�ظ���serial_no=[%d],cardno=[%d],devphyid=[%s],transdate=[%s],transtime=[%s],ret=[%d]", posdtl.devseqno, posdtl.cardno, posdtl.devphyid, posdtl.transdate, posdtl.transtime, ret);
                return 0;
            } else
                return E_DB_POSDTL_I;
        }
        g_dbchkerr = 1;
    }
    return 0;
}
