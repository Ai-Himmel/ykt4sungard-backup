/* --------------------------------------------
 * ��������: F47109.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������: �̻�����
 * --------------------------------------------
 * �޸�����:2004-10-12
 * �޸���Ա:	�Ž�
 * �޸�����: ���Ӽ��˽��״���
 * �汾��Ϣ:1.0.0.1
 * ��ע��Ϣ:
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "fdsqc.h"
#include "pubdef.h"
#include "errdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "dictionary.h"

int F847109(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg) {
    int ret = 0;
    char seed_key[17] = "";							//������Կ
    char logicdate[11]="";
    T_t_aif_account  tAccount;
    T_t_customer	tCustomer;

    ST_CPACK aPack;
    ST_PACK *pp = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);

    memset(&tAccount,0,sizeof(tAccount));
    memset(&tCustomer,0,sizeof(tCustomer));

    memcpy(seed_key,STATIC_SEED_KEY,sizeof(seed_key));			//��������Կ
    tCustomer.custid = in_pack->lvol1;				        					//�ͻ���

    ret=GetLogicDate(logicdate);							//ҵ������
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    ret=DB_t_customer_read_by_custid(tCustomer.custid,&tCustomer);
    if(ret) {
        writelog(LOG_ERR,"custid[%d]",tCustomer.custid);
        if(DB_NOTFOUND==ret)
            *pRetCode=E_CUSTOMER_NOT_EXIST;
        else
            *pRetCode=E_DB_CUSTOMER_R;
        goto L_RETU;
    }
    if(CUSTSTAT_LOGOUT==tCustomer.cut_state) {
        *pRetCode=E_CUSTOMER_LOGOUT;
        goto L_RETU;
    }
    ret=DB_t_aif_account_read_by_customer_id_and_act_type(tCustomer.custid,ACCTYPE_SHOPMAIN, &tAccount);
    if(ret) {
        writelog(LOG_ERR,"custid[%d]",tCustomer.custid);
        if(DB_NOTFOUND!=ret) {
            *pRetCode=E_DB_ACCOUNT_R;
            goto L_RETU;
        }
    } else {
        if(tAccount.current_state!=ACCOUNTSTAT_LOGOUT) {
            *pRetCode=E_ACTNO_EXIST;
            goto L_RETU;
        }
    }
    memset(&tAccount,0,sizeof(tAccount));
    des2src(tAccount.open_date,logicdate);									//��������
    des2src(tAccount.custname,in_pack->sname);							//�ͻ�����
    tAccount.custid=tCustomer.custid;									//�ͻ���
    tAccount.custtype = in_pack->lvol2;									//�ͻ����
    des2src(tAccount.stuempno,in_pack->sname2); 						//�ͻ�ѧ�Ż�Ա����
    tAccount.current_state = ACCOUNTSTAT_REGIST;							//��ǰ״̬

    ret = getNewActno(tAccount.account_id);								//������ʺ�
    if (ret) {
        *pRetCode = ret;
        goto L_RETU;
    }

    tAccount.act_type = ACCTYPE_SHOPMAIN;				        			//�ʺ����
    tAccount.cardno = 0; 													//��������
    tAccount.purseno = 0;													//������Ǯ����
//	tAccount.card_state = 0;												//��״̬
    tAccount.card_type = 0;												//�����
    des2src(tAccount.subno,SUBJECT_SHOPSAVING);							//������Ŀ
    EncodePwd(seed_key,in_pack->sserial0,tAccount.password,0);				//�ʻ�����
    Strncpy_t(tAccount.isautotra,in_pack->scust_type,sizeof(tAccount.isautotra)); 	//�Ƿ��Զ�ת��
    tAccount.last_bala = 0.00;					//ǰ���ʻ������
    tAccount.last_freebala = 0.00;				//ǰ���ʻ��������
    tAccount.last_frozebala = 0.00;				//ǰ���ʻ��������
    tAccount.cur_bala = 0.00;					//��ǰ�ʻ������
    tAccount.cur_freebala = 0.00;				//��ǰ�ʻ��������
    tAccount.cur_frozebala = 0.00;				//��ǰ�ʻ��������
    tAccount.out_bala = 0.00;					//�跽�����ܶ�
    tAccount.in_bala = 0.00;					//���������ܶ�
    tAccount.out_count = 0;					//�跽��������
    tAccount.in_count = 0;						//������������
    tAccount.card_balance = 0.00;				//��ǰ�����ʻ����
    tAccount.consume_count = 0;				//��ǰ�����ʻ����Ѵ���

    //	�����ʻ���Ϣ��
    ret = DB_t_aif_account_add(&tAccount);
    if (ret) {
        if(DB_REPEAT==ret)
            *pRetCode = E_DB_ACCOUNT_E;
        else
            *pRetCode = E_DB_ACCOUNT_I;
        goto L_RETU;
    }
    //	�����ʺŵ�ǰ̨
    SetCol(handle,0);
    SetCol(handle,F_SSTATION0,0);
    des2src(pp->sstation0, tAccount.account_id);			//�ʺ�
    PutRow(handle,pp,pRetCode,szMsg);
    return 0;
L_RETU:
    return -1;
}
