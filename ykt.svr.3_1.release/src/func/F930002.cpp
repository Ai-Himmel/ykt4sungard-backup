/* --------------------------------------------
 * ��������: F930002.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������: �ϴ��豸ʱ��
 * --------------------------------------------
 * �޸�����:2004-12-14
 * �޸���Ա:	�Ž�
 * �޸�����: �޸�ҵ���߼�
 * �汾��Ϣ:1.0.0.1
 * ��ע��Ϣ:
 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "busqc.h"

int F930002(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg) {
    int ret = 0;
    int cnt=0;
    int msgid=0;
    T_t_msglist tMsgList;
//	T_t_device tDevice;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_LSERIAL1,F_SDATE0,F_SSERIAL0,F_VSVARSTR0,0);

    memset(&tMsgList,0,sizeof(tMsgList));
//	memset(&tDevice,0,sizeof tDevice);

    tMsgList.deviceid = in_pack->lcert_code;
    if(!tMsgList.deviceid) {
        return E_INPUTNULL_DEVICE;
    }
    tMsgList.funcno = 930002;
    tMsgList.msglevel = MESLIST_PRIORITY_REALTIME;
    ret=AddMsgLst(&tMsgList);
    if(ret) {
        *pRetCode=ret;
        writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
        goto L_RETU;
    }
    if(iRequest!=tMsgList.funcno)
        return 0;
    ret=db_commit();
    if(ret) {
        writelog(LOG_ERR,"db_commit ret[%d]",ret);
        *pRetCode=E_DB_COMMIT;
        goto  L_RETU;
    }
    msgid=tMsgList.msgid;
    des2src(out_pack->sdate0,in_pack->sdate0);
    for(cnt=0; (cnt<20)&&(tMsgList.errcode!=0); cnt++) {
        sleep(1);
        memset(&tMsgList,0,sizeof(tMsgList));
        ret=DB_t_msglist_read_by_msgid(msgid, &tMsgList);
        if(ret) {
            writelog(LOG_ERR,"DB_t_msglist_read_by_msgid err[%d]",ret);
            *pRetCode=E_DB_MSGLIST_R;
            goto L_RETU;
        }
    }
    switch(tMsgList.errcode) {
    case 0:		//�ɹ�
        ret=GetXmlValue(out_pack->sserial0,sizeof(out_pack->sserial0),XML_KEY_CLOCK, tMsgList.respdata);
        if(ret) {
            *pRetCode=ret;
            goto L_RETU;
        }
        des2src(out_pack->vsvarstr0,"�ɹ�");
        break;
    case 9999:		//����δ����
        des2src(out_pack->vsvarstr0,"ǰ�û���Ӧ��");
        break;
    default:			//�����Ѿ�����,�������ʧ��
        des2src(out_pack->vsvarstr0,tMsgList.errmsg);
        break;
    }
    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
L_RETU:
    return  -1;
}
