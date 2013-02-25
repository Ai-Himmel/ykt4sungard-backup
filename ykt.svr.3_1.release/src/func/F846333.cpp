/* --------------------------------------------
 * ��������: 2008-07-10
 * ��������:
 * �汾��Ϣ: 1.0.0.0
 * ������: �����ʻ���ֵ
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
#include "acctrans.h"

int F846333(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    des2src(pAccTrans->trans.opercode,rPack->semp);
    pAccTrans->trans.transcode=TC_EACCDEPOSIT;
    ret=pAccTrans->InitTrans();
    if(ret)
        return ret;
    TRANS& trans=pAccTrans->trans;
    T_t_transdtl transdtl;		//add by chen 2012-01-04
    memset(&transdtl, 0, sizeof(transdtl));		//add by chen 2012-01-04
    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);

    SetCol(handle,0);

    des2src(trans.craccno,rPack->sbank_acc);	//�����˺�
    des2src(trans.eaccno,rPack->sbank_acc);	//����Ǯ���˺�
    if(!strlen(trans.eaccno))
        return E_INPUTNULL_ACCNO;
    //���ͻ�
    //ȥ�ʻ���Ϣ
    T_t_netacc tNetAcc;
    memset(&tNetAcc,0,sizeof(tNetAcc));
    ret=DB_t_netacc_read_by_accno(trans.eaccno,&tNetAcc);
    if(ret) {
        writelog(LOG_ERR,"accno[%s]",trans.eaccno);
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_EACCNO;
        else
            return E_DB_ACCOUNT_R;
    }
    if(tNetAcc.status[0]!=STATUS_NORMAL) {
        return E_EACCNO_LOGOUT;
    }
    //	�����˺�
    pAccTrans->trans.custid=tNetAcc.custid;		//�ͻ���
    pAccTrans->trans.inputamt=rPack->damt0;		//������
    pAccTrans->trans.unusedamt = trans.inputamt;	//ʣ����
    if(!pAccTrans->trans.inputamt)
        return E_INPUT_AMT_NULL;
    pAccTrans->trans.fundtype=rPack->lvol9;	//�ʽ�����
    des2src(pAccTrans->trans.voucherno,rPack->scust_auth2);
    ret=pAccTrans->doTrans();
    if(ret)
        return ret;
    SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);
    des2src(outPack->sdate3,pAccTrans->trans.accdate);
    des2src(outPack->semp,trans.opercode);
    outPack->lwithdraw_flag=trans.termid;
    outPack->lserial1=trans.termseqno;
    sprintf(outPack->vsmess,"�ͻ�[%s] %s �ʻ����:%.2fԪ",tNetAcc.accname,pAccTrans->remark.c_str(),pAccTrans->trans.craccaftbal);
    des2src(trans.remark,outPack->vsmess);
    PutRow(handle,outPack,pRetCode,szMsg);
//start add by chen 2012-01-04
    transdtl.transflag = 1;		//���ױ�־ 1Ϊ��ֵ
    transdtl.status[0] = '3';		//��ˮ״̬ 3�ǳɹ�
    transdtl.termid = trans.termid;			//�ն˱��
    transdtl.termseqno = trans.termseqno;	//�ն���ˮ��
    strncpy(transdtl.transdate, trans.transdate, 8);	//��������
    strncpy(transdtl.transtime, trans.transtime, 6);	//����ʱ��
    transdtl.transcode = trans.transcode;	//������
    transdtl.custid = trans.custid;			//�ͻ���
    GetStuempnoByCustid(transdtl.custid,transdtl.stuempno);	//ѧ����
    strncpy(transdtl.custname, tNetAcc.accname, 61);	//�ͻ���
    strncpy(transdtl.voucherno, trans.voucherno, 21);	//ƾ֤��
    transdtl.amount= trans.transamt;		//���׽��
    transdtl.cardbefbal= trans.craccbefbal;	//����ǰ���
    transdtl.cardaftbal = trans.craccaftbal;	//���׺����
    transdtl.paytype = rPack->lvol9;		//֧����ʽ
    strncpy(transdtl.accdate, trans.accdate, 8);	//��������
    strncpy(transdtl.acctime, trans.acctime, 6);	//����ʱ��
    strncpy(transdtl.opercode, trans.opercode, 9);	//����Ա
    // �������ײο���
    T_t_refno tRefno;

    memset(&tRefno,0,sizeof(tRefno));
    get_random(tRefno.mac);
    ret= GetNewRefno(tRefno.refno);
    if(ret)
        return ret;

    des2src(tRefno.lastsaved,trans.sysdatetime);
    des2src(tRefno.accdate,trans.accdate);
    tRefno.termid = trans.termid;
    tRefno.termseqno = trans.termseqno;
    tRefno.status = RS_SUCC;

    ret=DB_t_refno_add(&tRefno);
    if(ret) {
        if(DB_REPEAT==ret)
            return E_DB_REFNO_E;
        else
            return E_DB_REFNO_I;
    }
    strncpy(transdtl.refno, tRefno.refno, 14);	//���ײο���
    //��ӽ�����ˮ��¼
    ret = DB_t_transdtl_add(&transdtl);
    if(ret) {
        if(DB_REPEAT == ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }
//end add by chen 2012-01-04
    return 0;
}
