/* --------------------------------------------
 * ��������: F847110.sqc
 * ��������: 9 17 2004
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ���¿���Ϣǰ��ѯ����Ϣ
 * --------------------------------------------
 * �޸�����:2004-10-12
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
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
#include "dbfunc_foo.h"

int F847110(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int card_id=0;
	int register_flag = 0;
	char card_deadline_date[9] = "";
	double second = 0.0;
	char msg[128] = "";
	char sysdate[9] = "";

	T_t_pif_card	tCard;
	T_t_pif_spefee 	tSpeFee;
	T_t_cif_customer  tCustomer;
	T_t_aif_account   tAccount;
	T_t_tif_register_pay register_pay;
	T_t_tif_registration reg;
	T_t_tif_register_schoolterm term;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	memset(&tCard,0,sizeof(tCard));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&register_pay, 0, sizeof(register_pay));
	memset(&reg,0,sizeof reg);
	memset(&term,0,sizeof term);
	getsysdate(sysdate);

	card_id = in_pack->lvol0;				//����ʶ
	register_flag = in_pack->lvol1;			// ��ý���ע��ɷѸ��²�ѯ
	writelog(LOG_ERR,"web register flag=[%d]", register_flag);

	//�жϿ�״̬�Ƿ�Ϊд��δ�ɹ�״̬
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if(card_id!=tCard.card_id)
	{
		writelog(LOG_ERR,"card_id[%d] db card_id[%d]",card_id,tCard.card_id);
		*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	ret = DB_t_cif_customer_read_by_cut_id(tCard.cosumer_id, &tCustomer);
	if (ret)
	{
		*pRetCode=E_CUSTOMER_NOT_EXIST;
		goto L_RETU;
	}
  	 writelog(LOG_ERR,"111");
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if(tCard.state_id[CARDSTAT_TYPE_REG]!=STATE_TRUE)
		{
			*pRetCode=E_CARDNO_LOGOUT;
			goto L_RETU;
		}
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
		{
			*pRetCode=E_CARDNO_LOST;
			goto L_RETU;
		}
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
		{
		 writelog(LOG_ERR,"3");
			// �����ʱ��������Ϊδ�нɷѵ���
			if (1 == register_flag)				// ��ý���ѯ
			{

				// ��鱨����Ϣ
				ret = DB_t_tif_register_schoolterm_read_by_cuttype_and_reg_flag(tCustomer.cut_type,1,&term);
				if(ret)
				{
					if(DB_NOTFOUND != ret)
					{
						*pRetCode = E_DB_REG_SCHOOLTERM_R;
					}
					else
					// ����Ҫ����
						*pRetCode = E_DB_REGISTER_OUT_OF_DATE;
					goto L_RETU;
				}
				if(strcmp(term.reg_end,sysdate)< 0)
				{
					*pRetCode = E_DB_REGISTER_OUT_OF_DATE;
					sprintf(szMsg,"�뵽�����㱨��ע��");
					goto L_RETU;
				}
				if(strcmp(term.reg_delay,sysdate) >= 0)
				{
					// ������ʱ��֮��
					goto L_RETU2;
				}
				else
				{
					*pRetCode = E_DB_REGISTER_OUT_OF_DATE;
					sprintf(szMsg,"�ѹ��������ޣ��뵽�������Ĵ���");
					goto L_RETU;
				}
				

				// ��ѯע��ɷѱ�����
				ret = DB_t_tif_register_pay_read_by_stuemp_no(tCustomer.stuemp_no, &register_pay);
				if (ret)
				{
					if (DB_NOTFOUND == ret)
					{
						*pRetCode = E_DB_REGISTER_PAY_NOTNEEDUPDATE;
						goto L_RETU;
					}
					else
					{
						*pRetCode = E_DB_REGISTER_PAY_R;
						goto L_RETU;
					}
				}
				else
				{
					// (a) ��ѯ����ע��ɷѱ��״̬, 1��ʾ�ѽɷ�, 2��ʾ����, 3��ʾǷ��, 4��ʾ����ɷ�
					// (b) ״̬1�����Ҳ�ᶳ��, ԭ����״̬2, 3, 4û�и���, ���ڱ��״̬1, ���������Ҫ���¿���Ч�ںͿ����
					// (c) ����ɷ���Ҫ���¿����, ����Ҫ���¿���Ч��
					// (d) ����Ҫ���¿���Ч��, ���ǿ������Ҫ�õ�ǰ���
					// (e) ������ǰ̨����Ŀ����õ�WEB�ϸ���Ӧ�ø�����ʾ
					if (REGISTER_ALREADY_UPDATE == register_pay.flag)
					{
						*pRetCode = E_DB_REGISTER_PAY_ALREADYUPDATE;
						goto L_RETU;
					}

					if (register_pay.register_flag != REGISTER_ARREARAGE)		
					{
						goto L_RETU2;
					}
					else 	// Ƿ�Ѻ����������Ҫ���ö���
					{
						NULL;
					}

				}
			}
			else if(register_flag == 2)
			{
				// ��鱨����Ϣ
				ret = DB_t_tif_register_schoolterm_read_by_cuttype_and_reg_flag(tCustomer.cut_type,1,&term);
				if(ret)
				{
					if(DB_NOTFOUND != ret)
					{
						*pRetCode = E_DB_REG_SCHOOLTERM_R;
					}
					else
					// ����Ҫ����
						*pRetCode = E_DB_REGISTER_OUT_OF_DATE;
					goto L_RETU;
				}
				ret = DB_t_tif_registration_read_lock_by_c0_and_cust_id_and_reg_id(tCustomer.cut_id,term.reg_id,&reg);
				if(ret)
				{
					if(DB_NOTFOUND != ret)
					{
						*pRetCode = E_DB_REG_SCHOOLTERM_R;
					}
					// ����Ҫ����
					else
						*pRetCode = E_DB_REGISTER_OUT_OF_DATE;
					goto L_RETU;
				}
				DB_t_tif_registration_free_lock_c0();
				  writelog(LOG_ERR,"begin[%s],end[%s]",term.reg_end,sysdate);
				if(strcmp(term.reg_end,sysdate)< 0)
				{
					*pRetCode = E_DB_REGISTER_OUT_OF_DATE;
					sprintf(szMsg,"�뵽�����㱨��ע��");
					goto L_RETU;
				}
				if(strcmp(term.reg_delay,sysdate)>= 0)
				{
					// ������ʱ��֮��
					goto L_RETU2;
				}
				else
				{
					*pRetCode = E_DB_REGISTER_OUT_OF_DATE;
					sprintf(szMsg,"�ѹ��������ޣ��뵽�������Ĵ���");
					goto L_RETU;
				}
				
			}

			*pRetCode=E_CARDNO_FREEZE;
			goto L_RETU;
		}
		else
		{
			*pRetCode=E_CARDNO_FREEZE;
			sprintf(szMsg,"��δ����");
			goto L_RETU;
		}
		//else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
		//*pRetCode=E_CARDNO_WFAIL;
	}

L_RETU2:


	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id,0,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode= E_ACTNO_NOT_EXIST;
		else
			*pRetCode= E_DB_ACCOUNT_R;
		goto L_RETU;
	}

	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_LVOL1,F_LVOL6,F_LVOL7,F_LVOL5,F_SDATE0,F_LVOL0,F_SNAME,F_SNAME2,
		   F_SCUST_AUTH,F_SSERIAL0,F_SCUST_AUTH2,F_SCUST_TYPE,F_SCUST_LIMIT,F_SCUST_NO,F_SBANK_ACC,F_VSMESS,
		   F_LVOL2,0);
	out_pack->lvol0 = tCard.card_id;							//����ʶ
	out_pack->damt0=D4U5(tAccount.cur_freebala,2);			//�����
	out_pack->lvol2 = tAccount.consume_count;				// ���״���
	des2src(out_pack->sdate0,tCard.end_time);				//��Ч��ֹ����
	out_pack->lvol1 = tCustomer.cut_type;					//�ͻ����
	out_pack->lvol5 = tCustomer.fee_type;					//�շ����
	des2src(out_pack->sname,tCustomer.cut_name);			//ѧ��\Ա������
	des2src(out_pack->sserial0,tCustomer.classdept_no);		//��λ����
	des2src(out_pack->scust_auth2,tCustomer.man_id);		//���֤��
	des2src(out_pack->scust_type,tCustomer.sex);			//�Ա�
	des2src(out_pack->scust_limit,tCustomer.stuemp_no);		//ѧ��\Ա����
	des2src(out_pack->sname2,tCustomer.lib_cardid);			//ͼ��֤��
	des2src(out_pack->scust_no,tCard.showid);				//��ʾ����
	des2src(out_pack->sbank_acc,tCard.physical_no);			//������

	if (1 == register_flag)
	{
		if (REGISTER_FULL == register_pay.register_flag)
		{
			strncpy(card_deadline_date, tCard.end_time + 2, 6);
			memset(out_pack->sdate0, 0, sizeof(out_pack->sdate0));
			des2src(out_pack->sdate0, card_deadline_date);
		}

		if (REGISTER_DELAY == register_pay.register_flag)
		{
			getsysdate(card_deadline_date);
			ret = datetime2second(card_deadline_date, "YYYYMMDD", &second);
			if (ret)
			{
				writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
				*pRetCode = ret;
			}
			second = second + 24 * 60 * 60 * 90;
			ret = second2datetime(second, card_deadline_date, "YYYYMMDD");
			if (ret)
			{
				writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
				*pRetCode = ret;
			}
			memset(out_pack->sdate0, 0, sizeof(out_pack->sdate0));
			strncpy(out_pack->sdate0, card_deadline_date + 2, 6);
		}

		if (REGISTER_SPECIALARREARAGE == register_pay.register_flag)
		{
			getsysdate(card_deadline_date);
			ret = datetime2second(card_deadline_date, "YYYYMMDD", &second);
			if (ret)
			{
				writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
				*pRetCode = ret;
			}

			second = second + 24 * 60 * 60 * 365;
			ret = second2datetime(second, card_deadline_date, "YYYYMMDD");
			if (ret)
			{
				writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
				*pRetCode = ret;
			}
			memset(out_pack->sdate0, 0, sizeof(out_pack->sdate0));
			strncpy(out_pack->sdate0, card_deadline_date + 2, 6);
			out_pack->lvol5 = CUT_FEE_TYPE_TEMP;
		}

		writelog(LOG_ERR,"card_deadline_date=[%s], card_id=[%d]",out_pack->sdate0, card_id);
		out_pack->lvol6 = 1;	
	}
	else if(2 == register_flag)
	{
		// ����
		if(term.reg_id > 0)
		{
			des2src(out_pack->sdate0,term.reg_delay);
			out_pack->lvol6 = 1;
		}
	}
	else
	{
		strcpy(msg, "�˿�����, ����Ҫ����ע��ɷѸ���");
		des2src(out_pack->vsmess, msg);
	}

	writelog(LOG_ERR,"write card flag=[%d], fee type=[%d],term[%d]date[%s]", out_pack->lvol6, out_pack->lvol5,term.reg_id,out_pack->sdate0);
	out_pack->lvol7 = tCustomer.cut_id;
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return  -1;
}
