/* --------------------------------------------
 * ��������: F847163.sqc
 * ��������: 2004 11 17
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ������ֵ�����ѡ�����ѡ����ѡ���ֵ������
 * --------------------------------------------
 * �޸�����:2005-08-04
 * �޸���Ա:�Ž�
 * �޸�����:�����ײ���ʹ��
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/

#define _IN_SQC_
#include<pubdef.h>
#include<pubdb.h>
#include<dbfunc.h>
#include<errdef.h>
#include "fdsqc.h"
#include "dbfunc_foo.h"
#include "pubfunc.h"


int F847163(TRUSERID * handle, int iRequest, ST_PACK * rPack, int *pRetCode, char *szMsg) {
    int ret = 0;
    double maxfeeratio = 0;			//����
    double amt=0;
    ST_CPACK aPack;
    ST_PACK *pp = &(aPack.pack);
//	T_t_custtypefee  custtype;

    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle,F_DAMT1,F_DAMT2,F_DAMT3,F_DAMT4,F_DAMT5,0);
    PutRow(handle, pp, pRetCode, szMsg);
    return 0;
//	memset(&custtype,0,sizeof(custtype));

//	writelog(LOG_DEBUG, "rPack->lvol0[%d]", rPack->lvol0);	//�ͻ����
//	writelog(LOG_DEBUG, "rPack->lvol1[%d]", rPack->lvol1);	//������
//	writelog(LOG_DEBUG, "rPack->damt0[%lf]", rPack->damt0);	//������
    /*
    	ret=DB_t_custtypefee_read_by_custtype(rPack->lvol0,&custtype);
    	if(ret)
    	{
    		writelog(LOG_ERR,"custtype[%d]",rPack->lvol0);
    		if(DB_NOTFOUND==ret)
    			*pRetCode=E_CUTTYPE_NOT_EXIST;
    		else
    			*pRetCode=E_CUTTYPEFEE_R;
    		goto L_RETU;
    	}
    	switch(rPack->lvol1)
    	{
    		case 847101:				//������ʽ��(������,�����κη���)
    			if(IS_YES==custtype.is_firstcostfee)
    			{
    				pp->damt3= custtype.depositfee;		//Ѻ����
    				pp->damt4=0;
    				pp->damt5 = custtype.in_fee;			//������
    			}
    			else
    			{
    				pp->damt3=0;						//Ѻ����
    				pp->damt4=0;
    				pp->damt5=0;
    			}
    			break;
    		case 847104:				//���쿨
    			if(IS_NO!=rPack->lvol2)
    			{
    				pp->damt4 =custtype.cost_fee;		//���ɱ���
    			}
    			pp->damt3=0;							//Ѻ����
    			pp->damt5 = 0;							//������
    			break;
    		case 847126:									//����VIP��
    			pp->damt3=0;							//Ѻ����
    			pp->damt4 =custtype.cost_fee;			//���ɱ���
    			pp->damt5 = 0;							//������
    			break;
    		case 847116:									//���й�����ʱ��
    		case 847125:									//���зǼ�����ʱ��
    			pp->damt3= custtype.depositfee;			//Ѻ����
    			pp->damt4=0;
    			pp->damt5 = 0;							//������
    			break;
    		case 847124:									//���м�����ʱ��
    			pp->damt3= custtype.depositfee;			//Ѻ����
    			pp->damt4=0;
    			pp->damt5 = custtype.in_fee;				//������
    			break;
    		default:
    			*pRetCode=E_TXCODE_NOT_EXIST;
    			goto L_RETU;
    	}
    	amt=rPack->damt0-(pp->damt3+pp->damt4+pp->damt5);
    	if(amtcmp(amt,0)<0)
    	{
    			*pRetCode=E_CASH_LACK;
    			goto L_RETU;
    	}
    	if(strncmp(custtype.is_outfee,TYPE_YES,1)==0)
    	{
    		ret=GetMaxFeeRatioFromShop(&maxfeeratio);
    		if(ret)
    		{
    			*pRetCode=ret;
    			goto L_RETU;
    		}
    		pp->damt2=D4U5(amt*maxfeeratio,2);	//Ԥ�۴���
    	}
    //	pp->damt1=D4U5(amt-pp->damt2,2);		//����ֵ,
    	PutRow(handle, pp, pRetCode, szMsg);
    	return 0;
      L_RETU:
    	return -1;
    */
}
