/* --------------------------------------------
 * ��������: F843335.sqc
 * ��������: 2004 12 13
 * ��������:�Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: �̻���Ϣ���(����)
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


int F843335(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int	dept_id=0;                    	//���̻���ʶ
	int ret=0;
	int len=0;
	double dUniqno=0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char seed_key[17] = "";		//������Կ
	char pwd[17] = "";				//����
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	T_t_cif_shop	tShop;
	T_t_cif_customer  tCustomer;
	T_t_aif_account	tAccount;
	T_t_tif_tradeserial  tradeserial;
	
	 memset(&tShop,0,sizeof(tShop));
	 memset(&tCustomer,0,sizeof(tCustomer));
	 memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	ResetNormalCPack(&aPack,0,1);

#ifdef DEBUG
	writelog(LOG_DEBUG,"cut_id         :lvol0          [%d]",rPack->lvol0);
	writelog(LOG_DEBUG,"dept_id        :lvol1          [%d]",rPack->lvol1);
	writelog(LOG_DEBUG,"shop_name      :scard1         [%s]",rPack->scard1);
	writelog(LOG_DEBUG,"shop_type      :lvol7          [%d]",rPack->lvol7);
	writelog(LOG_DEBUG,"is_indep       :smain_flag     [%s]",rPack->smain_flag);
	writelog(LOG_DEBUG,"is_leaf        :smarket_code2  [%s]",rPack->smarket_code2);
	writelog(LOG_DEBUG,"shop_manager   :scust_auth     [%s]",rPack->scust_auth);
	writelog(LOG_DEBUG,"man            :sname          [%s]",rPack->sname);
	writelog(LOG_DEBUG,"sex            :sstatus0       [%s]",rPack->sstatus0);
	writelog(LOG_DEBUG,"nation         :lvol4          [%d]",rPack->lvol4);
	writelog(LOG_DEBUG,"man_id         :sname2         [%s]",rPack->sname2);
	writelog(LOG_DEBUG,"tel            :scust_auth2    [%s]",rPack->scust_auth2);
	writelog(LOG_DEBUG,"address        :scusttypes     [%s]",rPack->scusttypes);
	writelog(LOG_DEBUG,"is_getfee      :smarket_code   [%s]",rPack->smarket_code);
	writelog(LOG_DEBUG,"ratio          :damt0          [%lf]",rPack->damt0);
	writelog(LOG_DEBUG,"manager_type   :lvol3          [%d]",rPack->lvol3);
	writelog(LOG_DEBUG,"duty_type      :lvol2          [%d]",rPack->lvol2);
	writelog(LOG_DEBUG,"comments       :ssectypes      [%s]",rPack->ssectypes);
	writelog(LOG_DEBUG,"area         :lvol8          [%d]",rPack->lvol8);
#endif
	getsysdate(sysdate);
	getsystime(systime);
	dept_id=rPack->lvol1;				//���̻�ID
	if(dept_id<1)
	{
		*pRetCode= E_FAT_SHP_ID_NOT_EXIST;
		goto L_RETU;
	}
	ret=GetLogicDate(logicdate);		//ҵ������
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	//�ж��̻������Ƿ��Ѿ�ʹ
	ret=IsExistSameShopName(rPack->scard1,0);
	if(ret)
	{
		*pRetCode= ret;
		goto L_RETU;
	}
	ret=DB_t_cif_shop_read_lock_by_cur1_and_shop_id(dept_id,&tShop);
	if(ret)
	{
		writelog(LOG_ERR,"dept_id[%d]",dept_id);
		if(DB_NOTFOUND==ret)	
			*pRetCode= E_FAT_SHP_ID_NOT_EXIST;
		else
			*pRetCode= E_DB_SHOP_R;
		goto L_RETU;
	}
	if(strncmp(tShop.is_leaf,TYPE_YES,1)!=0)
	{
		DB_t_cif_shop_free_lock_cur1();
	}
	else
	{
		//��Ҷ���,���ж������豸
		ret=IsExistDeviceByShopId(dept_id,logicdate);
		if(ret)
		{
			DB_t_cif_shop_free_lock_cur1();
			*pRetCode= ret;
			goto L_RETU;
		}
		//����Ҷ�ӱ�־Ϊ��Ҷ��
		des2src(tShop.is_leaf,TYPE_NO);
		ret=DB_t_cif_shop_update_lock_by_cur1(&tShop);
		if(ret)
		{
			writelog(LOG_ERR,"dept_id[%d] ",dept_id);
			if(DB_NOTFOUND==ret)	
				*pRetCode= E_FAT_SHP_ID_NOT_EXIST;
			else
				*pRetCode= E_DB_SHOP_U;
			goto L_RETU;
		}
		DB_t_cif_shop_free_lock_cur1();
		//ע���ʻ�
		ret=DB_t_aif_account_read_lock_by_c5_and_customer_id_and_act_type(tShop .cut_id, ACCTYPE_SHOPMAIN, &tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"shop.cut_id[%d]",tShop.cut_id);
			if(DB_NOTFOUND==ret)
			
				*pRetCode=E_ACTNO_NOT_EXIST;
			else
				*pRetCode=E_DB_ACCOUNT_R;
			goto L_RETU;
		}
		if(amtcmp(tAccount.cur_bala,0)>0)
		{
			DB_t_aif_account_free_lock_c5();
			writelog(LOG_ERR,"account.cur_bala[%lf]",tAccount.cur_bala);
			*pRetCode=E_SHP_ACC_NO_RECKONING;
			goto L_RETU;
		}
		tAccount.current_state=ACCOUNTSTAT_LOGOUT;
		des2src(tAccount.close_date,logicdate);
		des2src(tAccount.close_time,systime);
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
	}
	memset(&tShop,0,sizeof(tShop));

//�����ӿͻ�
	ret=getNewUniqNo(KEYTYPE_CUSTOMER, &dUniqno);
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	tCustomer.cut_id=D2I(dUniqno);
	tCustomer.cut_type=CUSTTYPE_SHOP;				//�ͻ�����-�̻�
	tCustomer.cut_state=CUSTSTAT_REGIST;
	des2src(tCustomer.cut_name,rPack->scard1);		//�̻�����
	tCustomer.area=rPack->lvol8;					//����
	des2src(tCustomer.stuemp_no,rPack->scust_auth);	//Ա����
	des2src(tCustomer.classdept_no,rPack->scust_no);//���ź�
	des2src(tCustomer.man,rPack->sname);			//����
	des2src(tCustomer.sex,rPack->sstatus0);			//�Ա�
	tCustomer.nation=rPack->lvol4;					//����
	des2src(tCustomer.man_id,rPack->sname2);		//���֤��
	des2src(tCustomer.tel,rPack->scust_auth2);		//�绰
	des2src(tCustomer.address,rPack->scusttypes);	//��ַ
	des2src(tCustomer.reg_time,logicdate);			//ע������
	des2src(tCustomer.can_time,rPack->sphone3);	//Ԥ��ע������
	//des2src(tCustomer.comments,rPack->ssectypes);

	ret=DB_t_cif_customer_add(&tCustomer);
	if(ret)
	{
		*pRetCode=E_DB_CUSTOMER_I;
		goto L_RETU;
	}
	dUniqno=0;
	ret=getNewUniqNo(KEYTYPE_SHOP, &dUniqno);
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	tShop.shop_id=D2I(dUniqno);
	tShop.cut_id=tCustomer.cut_id;
	tShop.dept_id=dept_id;
	des2src(tShop.shop_name,tCustomer.cut_name);
	tShop.shop_type=rPack->lvol7;				//�̻����
	des2src(tShop.is_indep,rPack->smain_flag);		//�Ƿ��������
	des2src(tShop.is_leaf,rPack->smarket_code2);	//�Ƿ���Ҷ���
	tShop.shop_state=SHOPSTAT_REGIST;
	des2src(tShop.shop_manager,tCustomer.stuemp_no);	//ѧ��
	des2src(tShop.man,tCustomer.man);			//��ϵ������
	des2src(tShop.sex,tCustomer.sex);				//�Ա�
	tShop.nation=tCustomer.nation;					//����
	des2src(tShop.man_id,tCustomer.man_id);		//��ϵ�����֤��
	des2src(tShop.tel,tCustomer.tel);				//�绰
	des2src(tShop.address,tCustomer.address);		//��ַ
	des2src(tShop.is_getfee,rPack->smarket_code);	//�Ƿ���ȡ�����
	tShop.ratio=rPack->damt0;					//����
	if(tShop.ratio>MAX_RATIO)
	{
		*pRetCode=E_FEERATIO_TOO_HIGH;
		goto L_RETU;
	}
	tShop.manager_type=rPack->lvol3;				//����Ѽ��㷽ʽ
	tShop.duty_type=rPack->lvol2;					//�̻�˰�Ѽ��㷽ʽ
	des2src(tShop.reg_time,logicdate);				//�̻�ע������
	des2src(tShop.comments,rPack->ssectypes);	

	ret=DB_t_cif_shop_add(&tShop);
	if(ret)
	{
		*pRetCode=E_DB_SHOP_I;
		goto L_RETU;
	}
	//�����Ҷ������ʺ�
	if(strncmp(tShop.is_leaf,TYPE_YES,1)==0)
	{
/*		len=strlen(rPack->sserial0);
		if(len==0)
		{
			*pRetCode=E_PWD_NULL;
			goto L_RETU;	
		}
		else if(len!=6)
		{
			*pRetCode=E_PWD_LEN;
			goto L_RETU;
		}
*/
		memset(&tAccount,0,sizeof(tAccount));
		ret = getNewActno(tAccount.account_id);								//������ʺ�
		if (ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		des2src(tAccount.open_date,logicdate);									//��������
		des2src(tAccount.open_time,systime);
		des2src(tAccount.cut_name,tCustomer.cut_name);							//�ͻ�����
		tAccount.customer_id=tCustomer.cut_id;									//�ͻ���
		tAccount.cut_type =tCustomer.cut_type;									//�ͻ����
		des2src(tAccount.stuemp_no,tCustomer.stuemp_no); 						//�ͻ�ѧ�Ż�Ա����
		tAccount.current_state = ACCOUNTSTAT_REGIST;							//��ǰ״̬
		tAccount.act_type = ACCTYPE_SHOPMAIN;				        				//�ʺ����
		des2src(tAccount.subno,SUBJECT_SHOPSAVING);							//������Ŀ

		memcpy(seed_key,STATIC_SEED_KEY,sizeof(seed_key));					//��������Կ
		strcpy(pwd,"666666");
		EncodePwd(seed_key,pwd,tAccount.password,0);							//�ʻ�����

		//	�����ʻ���Ϣ��	
		ret = DB_t_aif_account_add(&tAccount);
		if (ret)
		{
			writelog(LOG_ERR,"tAccount.account_id[%s]",tAccount.account_id);
			if(DB_REPEAT==ret)
				*pRetCode = E_DB_ACCOUNT_E;
			else
				*pRetCode = E_DB_ACCOUNT_I;
			goto L_RETU;
		}
		dUniqno=0;
		ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  						//��������ˮ��
		if(ret)
		{
			*pRetCode = ret;
			writelog(LOG_ERR,"ret [%d]",ret);
			goto L_RETU;
		}
		des2src(tradeserial.oper_code,rPack->scust_limit);							//����Ա��
		tradeserial.maindevice_id=rPack->lvol10;										//����վ
		tradeserial.serial_no = D2I(dUniqno);											//��ˮ��
		tradeserial.other_seri_no = 0;														//�ϴ�����ˮ��
		tradeserial.serial_type = TXCODE_SHOP_OPEN;											//���״��룻��ע������+��ֵ ��һ�������룬��847101�� ����������ֵ������һ�������룬���µķ��������ļ������Ӷ����ַ�����ֵ�뷢������ֵ�Ŀ�������Ϣ��
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
	SetCol(handle,F_LVOL5,0);
	out_pack->lvol5=tShop.shop_id;
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
