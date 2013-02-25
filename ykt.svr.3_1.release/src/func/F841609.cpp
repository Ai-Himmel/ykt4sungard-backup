/* --------------------------------------------��
 * ��������: 2009-06-17
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ����������ʱ�ͻ���
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
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


int F841609(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    int CustomerCount=0;
    int start_no=0;
    char temp[256] ="";
    CAccTrans *pAccTrans=CAccTrans::getInstance();

    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);

    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_VSMESS,0);

    CustomerCount=rPack->lvol0;//	����

    T_t_customer  tCustomer;
    memset(&tCustomer,0,sizeof tCustomer);

//�����ӿͻ�
    ret = GetSysParaVal(GLOBE_FLAG_TEMPCARD_CUTTYPE,temp);
    if(ret) {
        ERRTIP("ϵͳ������û�����ò�����ʶΪ14����ʱ���Ŀͻ����");
        return ret;
    }
    tCustomer.custtype=atoi(temp);

    T_t_custtype tCustType;
    memset(&tCustType,0,sizeof(tCustType));

    ret=DB_t_custtype_read_by_custtype(tCustomer.custtype,&tCustType);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CUSTTYPE,tCustomer.custtype);
        else
            return E_DB_CUSTTYPE_R;
    }
    if(tCustType.feetype < 1) {
        ERRTIP("�ͻ����[%d]�������[%s]û�������շ����",tCustType.custtype,tCustType.custtypename);
        return E_COMMON_ERR;
    }
    tCustomer.feetype=tCustType.feetype;

    T_t_feetype tFeetype;
    memset(&tFeetype,0,sizeof tFeetype);
    ret = DB_t_feetype_read_by_feetype(tCustomer.feetype,&tFeetype);
    if(ret) {
        if(DB_NOTFOUND == ret) {
            return ERRINFO(E_NOTEXIST_FEETYPE,tCustomer.feetype);
        } else
            return E_DB_FEETYPE_R;
    }
    tCustomer.status[0]=STATUS_NORMAL;
    strcpy(tCustomer.custname,"��ʱ��Ա");	//�ͻ�����
    tCustomer.custattr[0]='2';				//��ݽ��ñ�־1-����2-����
    tCustomer.useflag[0]='0';
    strcpy(tCustomer.areacode,rPack->sbranch_code0);	//У��
    strcpy(tCustomer.batchno,pAccTrans->trans.sysdatetime);
    strcpy(tCustomer.opendate,pAccTrans->trans.accdate);

    for(int i=0; i<CustomerCount; i++) {
        ret=GetNewCustIDByShoolCode(rPack->sbranch_code0,tCustomer.custid);
        if(ret) {
            writelog(LOG_ERR,"school_code[%s]",rPack->sbranch_code0);
            return ret;
        }
        ret=DB_t_customer_add(&tCustomer);
        if(ret) {
            writelog(LOG_ERR,"DB_t_customer_add ret[%d]",ret);
            if(DB_REPEAT==ret)
                return  ERRINFO(E_DB_CUSTOMER_E,tCustomer.custid);
            else
                return  E_DB_CUSTOMER_I;
        }
        if(0==i)
            start_no=tCustomer.custid;
    }
    sprintf(out_pack->vsmess,"�������κ�%s,�ͻ��Ŵ�%d��%d��%d���ͻ��Զ��������",tCustomer.batchno,start_no,tCustomer.custid,CustomerCount);
    PutRow(handle,out_pack,pRetCode,szMsg);
    //writelog(LOG_DEBUG,out_pack->vsmess);
    return 0;
}
