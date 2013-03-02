/* --------------------------------------------
 * ��������: F843336.sqc
 * ��������: 2004-12-13
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:�̻���Ϣɾ��(����)
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
#include "fdsqc.h"

int F843336(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char sysdate[11]="";
	char systime[9]="";
	char  logicdate[11]="";         	//��������
	int	shop_id=0;                    	//�̻���ʶ
	double dUniqno=0;
	T_t_cif_shop	tShop;
	T_t_cif_customer  tCustomer;
	T_t_aif_account	tAccount;
	T_t_tif_tradeserial  tradeserial;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	int ret=0;

	memset(&tShop,0,sizeof(tShop));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	ResetNormalCPack(&aPack,0,1);
	
#ifdef DEBUG
	writelog(LOG_DEBUG,"shop_id        :lvol5          [%d]",rPack->lvol5);
#endif

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);		//ҵ������
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	shop_id=rPack->lvol5;
	if(shop_id<1)
	{
		*pRetCode= E_SHP_ID_NOT_EXIST;
		goto L_RETU;
	}
	ret=DB_t_cif_shop_read_lock_by_cur1_and_shop_id(shop_id,&tShop);
	if(ret)
	{
		writelog(LOG_ERR,"shop_id[%d]",shop_id);
		if(DB_NOTFOUND==ret)	
			*pRetCode= E_SHP_ID_NOT_EXIST;
		else
			*pRetCode= E_DB_SHOP_R;
		goto L_RETU;
	}
	//�ж��Ƿ�ΪҶ���
	if(strncmp(tShop.is_leaf,TYPE_YES,1)==0)
	{
		//���ж������豸
		ret=IsExistDeviceByShopId(shop_id,logicdate);
		if(ret)
		{
			DB_t_cif_shop_free_lock_cur1();
			*pRetCode= ret;
			goto L_RETU;
		}
	}
	else
	{
		//������¼��ڵ㲻��ɾ��
		ret=IsExistSubNodeByShpId(shop_id);
		if(ret)
		{
			DB_t_cif_shop_free_lock_cur1();
			*pRetCode= ret;
			goto L_RETU;
		}	
	}
	tShop.shop_state=SHOPSTAT_LOGOUT;
	des2src(tShop.can_time,logicdate);				//ע������
	ret=DB_t_cif_shop_update_lock_by_cur1(&tShop);
	if(ret)
	{
		writelog(LOG_ERR,"shop_id[%d]",shop_id);
		if(DB_NOTFOUND==ret)	
			*pRetCode= E_SHP_ID_NOT_EXIST;
		else
			*pRetCode= E_DB_SHOP_U;
		goto L_RETU;
	}
	DB_t_cif_shop_free_lock_cur1();
	//ע���ͻ�
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tShop.cut_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tShop.cut_id);
		if(DB_NOTFOUND==ret)	
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	tCustomer.cut_state=CUSTSTAT_LOGOUT;
	des2src(tCustomer.can_time,logicdate);
	ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tShop.cut_id);
		if(DB_NOTFOUND==ret)	
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_U;
		goto L_RETU;
	}
	DB_t_cif_customer_free_lock_cur();
	//�����Ҷ�����ע���ʻ�
	if(strncmp(tShop.is_leaf,TYPE_YES,1)==0)
	{
		//ע���ʻ�
		ret=DB_t_aif_account_read_lock_by_c5_and_customer_id_and_act_type(tShop.cut_id, ACCTYPE_SHOPMAIN, &tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"tShop.cut_id[%d]",tShop.cut_id);
			if(DB_NOTFOUND==ret)
			
				*pRetCode=E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode=E_DB_ACCOUNT_R;
			goto L_RETU;
		}
		if(amtcmp(tAccount.cur_bala,0)>0)
		{
			DB_t_aif_account_free_lock_c5();
			writelog(LOG_ERR,"tAccount.cur_bala[%d]",tAccount.cur_bala);
			*pRetCode=E_SHP_ACC_NO_RECKONING;
			goto L_RETU;
		}
		tAccount.current_state=ACCOUNTSTAT_LOGOUT;
		des2src(tAccount.close_date,logicdate);
		getsystime(tAccount.close_time);
		ret=DB_t_aif_account_update_lock_by_c5(&tAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode=E_ACTNO_NOT_EXIST;
			else
				*pRetCode=E_DB_ACCOUNT_U;
			goto L_RETU;
		}
		DB_t_aif_account_free_lock_c5();
		ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  						//��������ˮ��
		if(ret)
		{
			*pRetCode = ret;
			writelog(LOG_ERR,"ret [%d]",ret);
			goto L_RETU;
		}
		des2src(tradeserial.oper_code,rPack->scust_limit);							//����Ա��
		tradeserial.maindevice_id=rPack->lvol10;										//����վ
		tradeserial.serial_no = (int)dUniqno;											//��ˮ��
		tradeserial.other_seri_no = 0;														//�ϴ�����ˮ��
		tradeserial.serial_type = TXCODE_SHOP_LOGOUT;											//���״��룻��ע������+��ֵ ��һ�������룬��847101�� ����������ֵ������һ�������룬���µķ��������ļ������Ӷ����ַ�����ֵ�뷢������ֵ�Ŀ�������Ϣ��
		tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
		des2src(tradeserial.operate_date,sysdate);											//��������
		des2src(tradeserial.operate_time,systime);											//����ʱ��
		des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
		des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
		des2src(tradeserial.enteract_date,logicdate);											//��������
		des2src(tradeserial.enteract_time,systime);											//����ʱ��
		tradeserial.maindevice_id = rPack->lvol6;												//�ϴ�����վ��ʶ
		tradeserial.device_id = rPack->lvol7;													//�ɼ��豸��ʶ	
		tradeserial.customer_id=tAccount.customer_id;											//�ͻ���
		//	���뽻����ˮ��
		ret = DB_t_tif_tradeserial_add(&tradeserial);
		if (ret)
		{
			writelog(LOG_ERR,"ret[%d]",ret);
			if(DB_REPEAT==ret)
				*pRetCode = E_DB_TRADESERIAL_E;
			else
				*pRetCode = E_DB_TRADESERIAL_I;
			goto L_RETU;
		}
	}
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,0);
	out_pack->lvol0=tShop.shop_id;
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
