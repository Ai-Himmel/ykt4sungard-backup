/* ----------------------------------------------------------
 * �������ƣ�F820124.sqc
 * �������ڣ�2004-8-3
 * �������ߣ���ѫ��
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��豸������Ϣ�ؼ��ֲ�ѯ
 * ----------------------------------------------------------

 * �޸�����: 2004-09-08
 * �޸���Ա: �ź���
 * �޸�����: �޸Ĺ淶
 * �汾��Ϣ: 1.0.0.1
 * ��ע��Ϣ
 * ----------------------------------------------------------*/

#include "busqc.h"
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "errdef.h"
#include "pubdb.h"
#include "dictionary.h"
#include "phydevice_stru.h"

// ������: F820124.sqc
// ���  : ��ѫ�� 2004-8-31 09��44
// ����  : �豸������Ϣ�ؼ��ֲ�ѯ
// ����  : int 0 ��ʾ�ɹ�����������Ϊ����ʧ��
// ����  : TRUSERID *handle ���������ݵ�ͨѶ����˱�ʶ
// ����  : ST_PACK *rPack ҵ������������
// ����  : int *iRetCode �������ķ��ش��룬0��ʾ�ɹ����������Ǵ���ʧ�ܣ��ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ0
// ����  : char *szMsg �������ķ�����Ϣ���ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ��""

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
                        sprintf(szMsg,"��ѯ�豸�ṹ��Ϣ���޼�¼,SQLCODE=%d\n",SQLCODE);
                        writelog(LOG_WARNING,szMsg);
                        db_chk_err(__FILE__,__LINE__,&sqlca);
                        goto L_Ret_if;
                    }
                } else {
                    *pRetCode=E_DB_PHYDEVICE_R;
                    sprintf(szMsg,"��ȡ�豸�ṹ��Ϣ�����,SQLCODE=%d\n",SQLCODE);
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
                // �������AnswerDataPart��Ϊ�˲���ǰ�˵ȴ�̫��ʱ�䣬����15����¼��ʱ��͸����أ����ں������ݾͲ��ù��ˣ�BCC��ǰ���Զ��Ὣ�������ݲɼ���ȥ
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
            sprintf(szMsg,"�豸������Ϣ��������Ӧ��¼,SQLCODE=%d\n",SQLCODE);

            writelog(LOG_ERR,szMsg);
            db_chk_err(__FILE__,__LINE__,&sqlca);
            goto L_Ret_else;
        } else if(r!=0) {
            *pRetCode=E_DB_PHYDEVICE_R;
            sprintf(szMsg,"�豸������Ϣ���ȡ����,SQLCODE=%d\n",SQLCODE);

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
