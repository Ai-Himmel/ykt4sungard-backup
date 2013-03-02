/* ----------------------------------------------------------
 * �������ƣ�balance.c
 * �������ڣ�2004-8-13 9:34
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����ʴ���������
 * ----------------------------------------------------------
 * �޸����ڣ�2004-09-08
 * �޸���Ա�� ������
 * �޸������� ͳһ�淶����
 * �汾��Ϣ��1.0.0.1
 * ��ע��Ϣ��
 * ----------------------------------------------------------
 * �޸����ڣ�2004-12-28
 * �޸���Ա�� ������
 * �޸������� �޸��̻���ʱ���뵽�̻����еĲ��֣�����������
 			  �ù���ȥ������ȡ��ɾ���̻��İ취���
 * �汾��Ϣ��1.0.0.2
 * ��ע��Ϣ��
 * ----------------------------------------------------------
 * �޸����ڣ�2005-02-09
 * �޸���Ա�� ������
 * �޸������� ���ӿ��ⲻƽ���ƵĴ���
 * �汾��Ϣ��1.0.0.3
 * ��ע��Ϣ��
 * ----------------------------------------------------------
 * �޸����ڣ�2005-10-27
 * �޸���Ա�� ������
 * �޸��������޸ı�����ˮ��ģʽ������sql���ʵ�֣����Ч��
 * �汾��Ϣ��1.0.0.4
 * ��ע��Ϣ��
 * ----------------------------------------------------------
 * �޸����ڣ�2005-11-14
 * �޸���Ա�� ������
 * �޸������������Ž���ˮ,������ʱ���
 * �汾��Ϣ��1.0.0.5
 * ��ע��Ϣ��
 * ----------------------------------------------------------
 * �޸����ڣ�2006-08-08
 * �޸���Ա�� ������
 * �޸������������Ϻ���ѧ�����󣬰Ѷ���������̻���ÿ���Ӫҵ
  			  ���ݰ���ָ�������ݸ�ʽ�γ��ļ���ftp��ʽ���͸�
 * �汾��Ϣ��1.0.0.6
 * ��ע��Ϣ��
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/

#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "mypub.h"
#include "balance.h"
#include "dbfunc.h"
#include "account.h"

#define	SLEEP_TIME				60	//���˼��ʱ��

static int freezecard(int in_card_id,int in_cut_id,char* in_operator,int in_maindevice_id,int in_device_id)
{

  	int  ret = 0;
	int	card_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char	operator[33+1] = "";
	int	cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	double dSerial_no = 0;
	char sCardState[5] = "";
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_tif_meslist tMesList;

	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tMesList,0,sizeof(tMesList));

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode[%d]",ret);
		goto L_RETU;
	}
	//	׼��������Ϣ
	card_id = in_card_id;												//����ʶ
	cut_id = in_cut_id;												//�ͻ���
	des2src(operator,in_operator);									//����Ա��
	maindevice_id = in_maindevice_id;											//�ϴ�����վ��ʶ
	device_id = in_device_id;												//�ɼ��豸��ʶ

	//	���ͻ���Ϣ���ж��Ƿ���Զ���
	ret = GetCardState(card_id,sCardState);
	if (ret)
	{
		writelog(LOG_ERR,"GetCardState error,errcode[%d],card_id[%d]",ret,sCardState);
		goto L_RET;
	}
	if(strncmp(sCardState,CARDSTAT_LOGOUT,4)==0)
	{
		writelog(LOG_ERR,"strncmp(sCardState,CARDSTAT_LOGOUT,4) error");
		goto L_RET;
	}
	if(STATE_TRUE==sCardState[CARDSTAT_TYPE_FREEZE])
	{
		writelog(LOG_ERR,"STATE_TRUE==sCardState[CARDSTAT_TYPE_FREEZE] error");
		goto L_RET;
	}
	//	�޸Ŀ�״̬Ϊ����
	ret = UpdateCardState(card_id,CARDSTAT_TYPE_FREEZE,STATE_TRUE);
	if (ret)
	{
		writelog(LOG_ERR,"UpdateCardState error,errcode[%d],card_id[%d]",ret,card_id);
		goto L_RET;
	}
	//����ÿ��ű���ʧ,��ⶳʱ�Ժ�����������
	if(STATE_FALSE==sCardState[CARDSTAT_TYPE_LOST])
	{
		//	�����������
		ret=DB_t_tif_black_sheet_del_by_card_id_and_is_ad(card_id,DELETE_BLACKLIST);
		if(ret)
		{
			if(ret!=DB_NOTFOUND)
			{
				writelog(LOG_ERR,"DB_t_tif_black_sheet_del_by_card_id_and_is_ad err[%d],card_id=[%d] ",ret,card_id);
				goto L_RETU;
			}
		}
		ret=InsertToBlkList(card_id,ADD_BLACKLIST);
		if(ret)
		{
			writelog(LOG_ERR,"InsertToBlkList err[%d],card_id=[%d] ",ret,card_id);
			goto L_RETU;
		}

		//�㲥������
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,card_id);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//��ɾ��־

		tMesList.funid = 930005;
		tMesList.level = 1;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			goto L_RETU;
		}
	}
	//	׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerial_no);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode[%d]",ret);
		goto L_RETU;
	}
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	tradeserial.serial_no = (int)dSerial_no;									//��ˮ��
	tradeserial.serial_type = TXCODE_FREEZE_CARD;								//���Ῠ
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;							//��ˮ״̬
	tradeserial.maindevice_id = maindevice_id;									//�ϴ�����վ��ʶ
	tradeserial.device_id = device_id;											//�ɼ��豸��ʶ
	tradeserial.card_id = card_id;												//���׿���
	tradeserial.customer_id=cut_id;											//�ͻ���
	des2src(tradeserial.oper_code,operator);
	//	���뽻����ˮ��
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode=[%d]",ret);
		goto L_RETU;
	}

	return 0;
L_RET:
	return ret;
L_RETU:
	db_rollback();
	return ret;


}

static int process(T_t_tif_tradeserial *p)
{
	int ret=0;
	//char szActno[17]="";				//�ʻ�
	T_t_pif_card card;					//����Ϣ��
	T_t_cif_shop		shop;			//�̻���Ϣ��
	T_t_aif_account	account;		//�ʻ���
	InAcc   IA;						//����ģ���������

	memset(&card,0,sizeof(card));
	memset(&shop,0,sizeof(shop));
	memset(&account,0,sizeof(account));
	memset(&IA,0,sizeof(IA));


	//IA.iMainDevId=p->maindevice_id;			//����վ��ʶ
	//IA.iDevId=p->device_id;					//�豸ID
	IA.iSerialNo=p->serial_no;					//��ˮ��
	IA.iTradeNo=p->serial_type;				//������
	strcpy(IA.sTxDate,p->operate_date);		//��������
	strcpy(IA.sTxTime,p->operate_time);		//����ʱ��
	strcpy(IA.sTxCollectDate,p->collect_date);	//�ɼ�����
	strcpy(IA.sTxCollectTime,p->collect_time);	//�ɼ�ʱ��
	strcpy(IA.sTxAccDate,p->enteract_date);	//��������
	strcpy(IA.sTxAccTime,p->enteract_time);	//����ʱ��
	strcpy(IA.sArrInActno[0],p->out_account_id);		//�˺�
	strcpy(IA.sArrInActno[1],p->in_account_id);		//�˺�
	strcpy(IA.sMdeOper,p->oper_code);		//¼�����Ա
	strcpy(IA.sTalOper,p->oper_code);		//���˲���Ա

 	IA.dInCardBala=p->in_balance;                       //�뿨ֵ
       IA.dOutCardBala=p->out_balance;                   //����ֵ

	//IA.in_card_bala=p->in_balance;		//�뿨ֵ
	//IA.out_card_bala=p->out_balance;		//����ֵ
	IA.dArrInAmt[0]=p->trade_fee;					//������

	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(&IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	return 0;
}

static int process_makeup(T_t_tif_tradeserial *p)
{
	int ret=0;
	//char szActno[17]="";			//�ʻ�
	T_t_pif_card card;					//����Ϣ��
	T_t_cif_shop		shop;			//�̻���Ϣ��
	T_t_aif_account	account;		//�ʻ���
	InAcc   IA;						//����ģ���������

	memset(&card,0,sizeof(card));
	memset(&shop,0,sizeof(shop));
	memset(&account,0,sizeof(account));
	memset(&IA,0,sizeof(IA));


	//IA.iMainDevId=p->maindevice_id;			//����վ��ʶ
	//IA.iDevId=p->device_id;					//�豸ID
	IA.iSerialNo=p->serial_no;					//��ˮ��
	IA.iTradeNo=p->serial_type;				//������
	strcpy(IA.sTxDate,p->operate_date);		//��������
	strcpy(IA.sTxTime,p->operate_time);		//����ʱ��
	strcpy(IA.sTxCollectDate,p->collect_date);	//�ɼ�����
	strcpy(IA.sTxCollectTime,p->collect_time);	//�ɼ�ʱ��
	strcpy(IA.sTxAccDate,p->enteract_date);	//��������
	strcpy(IA.sTxAccTime,p->enteract_time);	//����ʱ��
	strcpy(IA.sArrInActno[0],p->out_account_id);		//�˺�
	strcpy(IA.sArrInActno[1],p->in_account_id);		//�˺�
	strcpy(IA.sMdeOper,p->oper_code);		//¼�����Ա
	strcpy(IA.sTalOper,p->oper_code);		//���˲���Ա

 	IA.dInCardBala=p->in_balance;                       //�뿨ֵ
       IA.dOutCardBala=p->out_balance;                   //����ֵ

	//IA.in_card_bala=p->in_balance;		//�뿨ֵ
	//IA.out_card_bala=p->out_balance;		//����ֵ
	IA.dArrInAmt[0]=p->trade_fee;					//������

	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(&IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	return 0;
}

static int add_serialno(T_t_tif_tradeserial *p,double trans_amt,char * in_account_no,char * out_account_no)
{
	int ret=0;
	double dUniqno=0;
	char logicdate[11]="";
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}
	//p->serial_no;                			//��ˮ��
	p->other_seri_no=0;                     			//�ϴ�����ˮ��
	p->serial_type=TXCODE_INNERTRANS;       	//���״���
	p->serial_state=SERISTAT_NODEBT;        		//��ˮ״̬
	strcpy(p->operate_date,logicdate);            	//��������
	getsystime(p->operate_time);           		//����ʱ��
	strcpy(p->collect_date,logicdate);             	//�ɼ�����
	strcpy(p->collect_time,p->operate_time);       //�ɼ�ʱ��
	strcpy(p->enteract_date,logicdate);            	//��������
	strcpy(p->enteract_time,p->operate_time);    //����ʱ��
	p->maindevice_id=0;                     			//�ϴ�����վ��ʶ
	p->device_id=0;                         			//���׷����豸��ʶ
	//p->devphy999_id[8+1];                 //�����豸����ID
	//p->showid[10+1];                      //��ʾ����
	//p->card_id;                           //���׿���
	//p->purse_id;                          //����Ǯ����
	//p->trade_count;                       //��ǰ�����ʻ����״���
	p->trade_fee=trans_amt;                          			//���ν��׽��
	//printf("p->trade_fee[%lf]\n",p->trade_fee);
	//p->in_balance;                        //�뿨���
	//p->out_balance;                       //�������
	//p->deposit_fee;                       //Ѻ����
	//p->in_fee;                            //�������
	//p->cost_fee;                          //���ɱ���
	//p->oldpwd[32+1];                      //ԭʼ����
	//p->newpwd[32+1];                      //��������
	//p->customer_id;                       //�ͻ���ʶ
	strcpy(p->oper_code,"system");          		//����Ա����
	strncpy(p->out_account_id,out_account_no,sizeof(p->out_account_id)-1);               		//�����ʺ�
	//printf("p->out_account_id[%s]\n",p->out_account_id);
	strncpy(p->in_account_id,in_account_no,sizeof(p->in_account_id)-1);                			//�����˺�
	//printf("p->in_account_id[%s]\n",p->in_account_id);
	//p->b_act_id[40+1];                    //�ⲿϵͳ�ʺ�
	//p->sys_id;                            //�ⲿϵͳ��ʶ
	//p->condition_id;                      //�Զ�ת��������ʶ
	//p->is_online[1+1];                    //�Ƿ�����
	//p->tmark;                             //���ױ��
	//p->dev_auth[8+1];                     //�ն��豸��Ȩ��
	//p->comu_ver;                          //ͨ�Ű汾��
	//p->run_reaon;                         //����ԭ��
	//p->crc[5+1;                           //CRCУ��	CRC
	p->ecode=0;                             				//������	ecode
	//p->revisesrial_no;                    //������ˮ��
	//p->reserve1[40+1];                    //Ԥ���ֶ�1
	//p->reserve2[40+1];                    //Ԥ���ֶ�2
	//p->reserve3[40+1];                    //Ԥ���ֶ�3

	//ȡ�µ���ˮ��
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqno);
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		p->ecode=ret;
		return ret;
	}
	p->serial_no=(int)dUniqno;
	ret = DB_t_tif_tradeserial_add(p);
	if (ret)
	{
		writelog(LOG_ERR,"������ˮ��������SQLCODE= [%d] ",ret);
		ret= E_DB_TRADESERIAL_I;
		p->ecode=ret;
		return ret;
	}
	return 0;
}

static int add_serialno_makeup(T_t_tif_tradeserial *p)
{
	int ret=0;
	double dUniqno=0;
	char logicdate[11]="";
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}
	//p->serial_no;                			//��ˮ��
	p->other_seri_no=0;                     			//�ϴ�����ˮ��
	//p->serial_type=TXCODE_INNERTRANS;       	//���״���
	p->serial_state=SERISTAT_NODEBT;        		//��ˮ״̬
	strcpy(p->operate_date,logicdate);            	//��������
	getsystime(p->operate_time);           		//����ʱ��
	strcpy(p->collect_date,logicdate);             	//�ɼ�����
	strcpy(p->collect_time,p->operate_time);       //�ɼ�ʱ��
	strcpy(p->enteract_date,logicdate);            	//��������
	strcpy(p->enteract_time,p->operate_time);    //����ʱ��
	p->maindevice_id=0;                     			//�ϴ�����վ��ʶ
	p->device_id=0;                         			//���׷����豸��ʶ
	//p->devphy999_id[8+1];                 //�����豸����ID
	//p->showid[10+1];                      //��ʾ����
	//p->card_id;                           //���׿���
	//p->purse_id;                          //����Ǯ����
	//p->trade_count;                       //��ǰ�����ʻ����״���
	//p->trade_fee=trans_amt;                          			//���ν��׽��
	//printf("p->trade_fee[%lf]\n",p->trade_fee);
	//p->in_balance;                        //�뿨���
	//p->out_balance;                       //�������
	//p->deposit_fee;                       //Ѻ����
	//p->in_fee;                            //�������
	//p->cost_fee;                          //���ɱ���
	//p->oldpwd[32+1];                      //ԭʼ����
	//p->newpwd[32+1];                      //��������
	//p->customer_id;                       //�ͻ���ʶ
	strcpy(p->oper_code,"system");          		//����Ա����
	//strncpy(p->out_account_id,out_account_no,sizeof(p->out_account_id)-1);               		//�����ʺ�
	printf("p->out_account_id[%s]\n",p->out_account_id);
	//strncpy(p->in_account_id,in_account_no,sizeof(p->in_account_id)-1);                			//�����˺�
	printf("p->in_account_id[%s]\n",p->in_account_id);
	//p->b_act_id[40+1];                    //�ⲿϵͳ�ʺ�
	//p->sys_id;                            //�ⲿϵͳ��ʶ
	//p->condition_id;                      //�Զ�ת��������ʶ
	//p->is_online[1+1];                    //�Ƿ�����
	//p->tmark;                             //���ױ��
	//p->dev_auth[8+1];                     //�ն��豸��Ȩ��
	//p->comu_ver;                          //ͨ�Ű汾��
	//p->run_reaon;                         //����ԭ��
	//p->crc[5+1;                           //CRCУ��	CRC
	p->ecode=0;                             				//������	ecode
	//p->revisesrial_no;                    //������ˮ��
	//p->reserve1[40+1];                    //Ԥ���ֶ�1
	//p->reserve2[40+1];                    //Ԥ���ֶ�2
	//p->reserve3[40+1];                    //Ԥ���ֶ�3

	//ȡ�µ���ˮ��
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqno);
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		p->ecode=ret;
		return ret;
	}
	p->serial_no=(int)dUniqno;
	ret = DB_t_tif_tradeserial_add(p);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode= [%d] ",ret);
		p->ecode=ret;
		return ret;
	}
	return 0;
}

int SearchLeafshop_and_Trans(int shop_id,char* Independ_or_not)
{

	int ret=0;
	int cnt=0;

	char type_yes_or_no[1+1]="";
	//T_v_tif_shopdeptfee 	v_shopdeptfee;
	T_t_cif_shop		  	t_shop;
	T_t_tif_tradeserial		t_tradeserial;
	T_t_aif_account		t_account;

	memset(&t_shop,0,sizeof(t_shop));

	ret=DB_t_cif_shop_read_by_shop_id(shop_id,&t_shop);
	if(ret)
	{
		writelog(LOG_ERR,"read tablet_cif_shop  shop_id[%d]",shop_id);
		if(DB_NOTFOUND==ret)
		{
			return E_SHP_ID_NOT_EXIST;
		}
		else
			return E_DB_SHOP_R;
	}
	strcpy(type_yes_or_no,TYPE_YES);
	if(strncmp(t_shop.is_leaf,type_yes_or_no,1))
	{
		//���ݿͻ��ź��̻����˺����Ͳ�ѯ�˺ű��õ��˺�
		memset(&t_account,0,sizeof(t_account));
		ret=DB_t_aif_account_read_by_customer_id_and_act_type(t_shop.cut_id,ACCTYPE_SHOPMAIN,&t_account);
		if((0!=ret)&&(DB_NOTFOUND!=ret))
		{
			writelog(LOG_ERR,"read_by_customer_id_and_act_type ret[%d]cutid[%d]",ret,t_shop.cut_id);
			return E_DB_ACCOUNT_R;
		}
		if(!strncmp(Independ_or_not,type_yes_or_no,1))
		{
			memset(&t_tradeserial,0,sizeof(t_tradeserial));
			ret=add_serialno(&t_tradeserial,t_account.cur_bala,INNER_ACCOUNT_BANKTRANSFER,t_account.account_id);
			if(ret)
			{
				writelog(LOG_ERR,"add_serialno error,t_account.account_id=[%s],errcode=[%d]",t_account.account_id,ret);
				db_rollback();
				return 	ret;
			}
		}
		else
		{
			memset(&t_tradeserial,0,sizeof(t_tradeserial));
			ret=add_serialno(&t_tradeserial,t_account.cur_bala,INNER_ACCOUNT_FINANCETRANSER,t_account.account_id);
			if(ret)
			{
				writelog(LOG_ERR,"add_serialno error,t_account.account_id=[%s],errcode=[%d]",t_account.account_id,ret);
			//	db_rollback();
				return 	ret;
			}
		}
		#if 0
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			db_rollback();
			return 	ret;
		}
		#endif
		//�����������������Ĵ���
		ret=process(&t_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"process ret[%d]",ret);
			goto L_RETU;
		}
		//������ˮ״̬
		getsysdate(t_tradeserial.enteract_date);			//��������
		getsystime(t_tradeserial.enteract_time);			//����ʱ��
		t_tradeserial.serial_state=SERISTAT_DEBT;		//������
		ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
			goto L_RETU;
		}
		#if 0
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			goto L_RETU;
		}
		#endif
	}

	//ѭ���ж��±ߵ��ӽڵ��Ƿ�ΪҶ���̻�
	ret=DB_t_cif_shop_open_select_by_cur2_and_dept_id(shop_id);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_shop_open_select_by_cur2_and_dept_id ret[%d]shop_id[%d]",ret,shop_id);
		return E_DB_SHOP_R;
	}
	while(1)
	{
		memset(&t_shop,0,sizeof(t_shop));
		ret=DB_t_cif_shop_fetch_select_by_cur2(&t_shop);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"DB_t_cif_shop_fetch_select_by_cur2 have not record,shop_id=[%d]!",t_shop.shop_id);
						break;
					}
				else
					break;
			}
			else
				goto L_RETU;
		}
		cnt++;
		ret=SearchLeafshop_and_Trans(t_shop.shop_id,Independ_or_not);
		if(ret)
		{
			writelog(LOG_DEBUG,"SearchLeafshop_and_Trans faild,ret[]t_shop.shop_id=[%d]!",ret,t_shop.shop_id);
			goto L_RETU;
		}
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		goto L_RETU;
	}
	return 0;

L_RETU:
	//�ع�����
	db_rollback();
	//������ˮ״̬
	getsysdate(t_tradeserial.enteract_date);			//��������
	getsystime(t_tradeserial.enteract_time);			//����ʱ��
	//t_tradeserial.ecode=*pRetCode;			//������
	t_tradeserial.serial_state=SERISTAT_DEBTEXC;		//�����쳣״̬
	ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
	}
	//�ύ����
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
	}
	return E_ENTER_ACCOUNT;

}

/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: ֹͣ���ʲ������޸Ľ����־
      �޸ļ�¼	:
*****************************************************/
int StopInBalance()
{
	char buffer[50];
	int ret=0;
	memset(buffer,0,sizeof(buffer));
	ret=GetParameter(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"Read syspara err [%d]",ret);
		return E_SEARCH_FLAG;
	}

	if(strncmp(buffer,"1",1)!=0)
	{
		strcpy(buffer,"1");
		ret=SetParameter(GLOBE_FLAG_BALANCE,buffer);
		if(ret)
		{
			writelog(LOG_ERR,"Write syspara err [%d]",ret);
			return E_CHANGE_FLAG;
		}
	}
	else
	{
		writelog(LOG_DEBUG,"The value of balance parameter is '%s',maybe there have another thread balancing now!",&buffer);
		return	E_BALANCE_NOW;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}

	mysleep(SLEEP_TIME);
	writelog(LOG_DEBUG,"Stop in balance succeed!");
	return 0;

}

/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: �������ݿ⣬���ǽ�����ܻ��޸�һЩ������Ϣ��
      			  ������ִ�����Իָ�
      �޸ļ�¼	:
*****************************************************/

int BackupData()
{
	int ret=0;
	char logic_date[8+1]="";


	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}
	//���ݽ�����ϸ��ykt_cur.T_t_tif_tradelog------>ykt_his.T_t_tif_tradelog
	//ret=DB_t_tif_tradelog_open_select_by_cur2_and_enteract_date(logic_date);
	ret=Db_t_tif_tradelog_backup_by_bak_date(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Db_t_tif_tradelog_backup_by_bak_date error,errcode=[%d]",ret);
		return 	ret;
	}

	//������ˮ��ykt_cur.T_t_tif_tradeserial------>ykt_his.T_t_tif_tradeserial_his
	ret=Db_t_tif_tradeserial_backup_by_bak_date(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Db_t_tif_tradeserial_backup_by_bak_date error,errcode=[%d]",ret);
		return 	ret;
	}
	//�����Ž���ˮ��
	ret=Db_v_door_txdtl_his_backup();
	if(ret)
	{
		writelog(LOG_ERR,"Db_v_door_txdtl_his_backup error,errcode=[%d]",ret);
	}
	/*
	ret=DB_t_tif_tradelog_open_with_hold_select_by_cur1();
	if(ret)
	{
		DB_t_tif_tradelog_close_select_by_cur1();
		writelog(LOG_ERR,"DB_t_tif_tradelog_open_with_hold_select_by_cur1 error,errcode=[%d]",ret);
		db_rollback();
		return 	ret;
	}
	getsystime(backup_time);

	while(1)
	{
		memset(&t_tradelog,0,sizeof(t_tradelog));
		ret=DB_t_tif_tradelog_fetch_select_by_cur1(&t_tradelog);
		if(ret)
		{
			DB_t_tif_tradelog_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_tradelog table!");
						break;
					}
				else		break;
			}
			else
				writelog(LOG_ERR,"DB_t_tif_tradelog_fetch_select_by_cur1 error,errcode=[%d]!",ret);
				return   ret;
		}
		cnt++;
		//��ֵ
		strncpy(t_tradelog_his.bak_date,logic_date,sizeof(t_tradelog_his.bak_date));
		//getsystime(t_tradelog_his.bak_time);
		strncpy(t_tradelog_his.bak_time,backup_time,sizeof(t_tradelog_his.bak_time));
		t_tradelog_his.serino             =t_tradelog.serino    ;
		t_tradelog_his.seri_type          =t_tradelog.seri_type ;
		t_tradelog_his.fee_type           =t_tradelog.fee_type  ;
		strncpy(t_tradelog_his.act_id       ,t_tradelog.act_id      ,sizeof(t_tradelog_his.act_id       ));
		strncpy(t_tradelog_his.subno        ,t_tradelog.subno       ,sizeof(t_tradelog_his.subno        ));
		strncpy(t_tradelog_his.other_actid  ,t_tradelog.other_actid ,sizeof(t_tradelog_his.other_actid  ));
		strncpy(t_tradelog_his.other_subno  ,t_tradelog.other_subno ,sizeof(t_tradelog_his.other_subno  ));
		t_tradelog_his.outorin            =t_tradelog.outorin       ;
		t_tradelog_his.op_fee             =t_tradelog.op_fee        ;
		t_tradelog_his.new_fee            =t_tradelog.new_fee       ;
		t_tradelog_his.cur_frozebala		=t_tradelog.cur_frozebala;
		t_tradelog_his.warrant_type       =t_tradelog.warrant_type  ;
		strncpy(t_tradelog_his.warrant_no   ,t_tradelog.warrant_no  ,sizeof(t_tradelog_his.warrant_no   ));
		strncpy(t_tradelog_his.operate_date ,t_tradelog.operate_date,sizeof(t_tradelog_his.operate_date ));
		strncpy(t_tradelog_his.operate_time  ,t_tradelog.operate_time ,sizeof(t_tradelog_his.operate_time ));
		strncpy(t_tradelog_his.collect_date ,t_tradelog.collect_date,sizeof(t_tradelog_his.collect_date ));
		strncpy(t_tradelog_his.collect_time  ,t_tradelog.collect_time ,sizeof(t_tradelog_his.collect_time ));
		strncpy(t_tradelog_his.enteract_date,t_tradelog.enteract_date,sizeof(t_tradelog_his.enteract_date));
		strncpy(t_tradelog_his.enteract_time ,t_tradelog.enteract_time,sizeof(t_tradelog_his.enteract_time ));
		t_tradelog_his.maindevice_id      =t_tradelog.maindevice_id ;
		t_tradelog_his.device_id          =t_tradelog.device_id     ;
		t_tradelog_his.annex              =t_tradelog.annex         ;
		strncpy(t_tradelog_his.record_oper  ,t_tradelog.record_oper ,sizeof(t_tradelog_his.record_oper  ));
		strncpy(t_tradelog_his.check_oper   ,t_tradelog.check_oper  ,sizeof(t_tradelog_his.check_oper   ));
		strncpy(t_tradelog_his.write_oper   ,t_tradelog.write_oper  ,sizeof(t_tradelog_his.write_oper   ));
		strncpy(t_tradelog_his.reserve_1    ,t_tradelog.reserve_1   ,sizeof(t_tradelog_his.reserve_1  ));
		strncpy(t_tradelog_his.reserve_2    ,t_tradelog.reserve_2   ,sizeof(t_tradelog_his.reserve_2  ));
		strncpy(t_tradelog_his.reserve_3    ,t_tradelog.reserve_3   ,sizeof(t_tradelog_his.reserve_3  ));
		strncpy(t_tradelog_his.comments    ,t_tradelog.comments   ,sizeof(t_tradelog_his.comments   ));

		ret=DB_t_tif_tradelog_his_add(&t_tradelog_his);
		if(ret)
		{
			DB_t_tif_tradelog_close_select_by_cur1();
			writelog(LOG_ERR,"DB_t_tif_tradelog_his_add record[%d] error,err[%d]",cnt,ret);
			db_rollback();
			return 	ret;
		}
		if(cnt%1000==0)
		{
			ret=db_commit();
			if(ret)
			{
				DB_t_tif_tradelog_close_select_by_cur1();
				writelog(LOG_ERR,"db_commit ret[%d]",ret);
				db_rollback();
				return 	ret;
			}

		}
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	DB_t_tif_tradelog_close_select_by_cur1();
	writelog(LOG_INFO,"Backup t_tif_tradelog succeed!,record=[%d]",cnt);
	//������ˮ��ykt_cur.T_t_tif_tradeserial------>ykt_his.T_t_tif_tradeserial_his

	getsystime(backup_time);
	cnt=0;
	ret=DB_t_tif_tradeserial_open_with_hold_select_by_cur2();
	if(ret)
	{
		DB_t_tif_tradeserial_close_select_by_cur2();
		writelog(LOG_ERR,"DB_t_tif_tradeserial_open_select_by_cur2 error,errcode=[%d]",ret);
		db_rollback();
		return 	ret;
	}
	while(1)
	{
		memset(&t_tradeserial,0,sizeof(t_tradeserial));
		memset(&t_tradeserial_his,0,sizeof(t_tradeserial_his));
		ret=DB_t_tif_tradeserial_fetch_select_by_cur2(&t_tradeserial);
		if(ret)
		{
			DB_t_tif_tradeserial_close_select_by_cur2();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't record from t_tif_tradeserial table!");
					return   0;
				}
				else		break;
			}
			else
			{
				writelog(LOG_DEBUG,"DB_t_tif_tradeserial_fetch_select_by_cur2 error,errcode[%d],record[%d]!",ret,cnt);
				return   ret;
			}
		}
		cnt++;
		//��ֵ
		strncpy(t_tradeserial_his.bak_date,logic_date,sizeof(t_tradeserial_his.bak_date));
		//getsystime(t_tradeserial_his.bak_time);
		strncpy(t_tradeserial_his.bak_time,backup_time,sizeof(t_tradeserial_his.bak_time));
		t_tradeserial_his.serial_no      =t_tradeserial.serial_no     ;
		t_tradeserial_his.other_seri_no  =t_tradeserial.other_seri_no ;
		t_tradeserial_his.serial_type    =t_tradeserial.serial_type   ;
		t_tradeserial_his.serial_state   =t_tradeserial.serial_state  ;
		strncpy(t_tradeserial_his.operate_date   ,t_tradeserial.operate_date  	,sizeof(t_tradeserial_his.operate_date   ));
		strncpy(t_tradeserial_his.operate_time   ,t_tradeserial.operate_time  	,sizeof(t_tradeserial_his.operate_time   ));
		strncpy(t_tradeserial_his.collect_date   ,t_tradeserial.collect_date  	,sizeof(t_tradeserial_his.collect_date   ));
		strncpy(t_tradeserial_his.collect_time   ,t_tradeserial.collect_time  	,sizeof(t_tradeserial_his.collect_time   ));
		strncpy(t_tradeserial_his.enteract_date  ,t_tradeserial.enteract_date 	,sizeof(t_tradeserial_his.enteract_date  ));
		strncpy(t_tradeserial_his.enteract_time  ,t_tradeserial.enteract_time 	,sizeof(t_tradeserial_his.enteract_time  ));
		t_tradeserial_his.maindevice_id  =t_tradeserial.maindevice_id ;
		t_tradeserial_his.device_id      =t_tradeserial.device_id     ;
		strncpy(t_tradeserial_his.devphy999_id   ,t_tradeserial.devphy999_id  	,sizeof(t_tradeserial_his.devphy999_id   ));
		strncpy(t_tradeserial_his.showid         ,t_tradeserial.showid        	,sizeof(t_tradeserial_his.showid         ));
		t_tradeserial_his.card_id        =t_tradeserial.card_id       ;
		t_tradeserial_his.purse_id       =t_tradeserial.purse_id      ;
		t_tradeserial_his.trade_count    =t_tradeserial.trade_count   ;
		t_tradeserial_his.trade_fee      =t_tradeserial.trade_fee     ;
		t_tradeserial_his.in_balance     =t_tradeserial.in_balance    ;
		t_tradeserial_his.out_balance    =t_tradeserial.out_balance   ;
		t_tradeserial_his.deposit_fee    =t_tradeserial.deposit_fee   ;
		t_tradeserial_his.in_fee         =t_tradeserial.in_fee        ;
		t_tradeserial_his.cost_fee       =t_tradeserial.cost_fee      ;
		t_tradeserial_his.boardfee=t_tradeserial.boardfee;
		strncpy(t_tradeserial_his.oldpwd         ,t_tradeserial.oldpwd        	,sizeof(t_tradeserial_his.oldpwd         ));
		strncpy(t_tradeserial_his.newpwd         ,t_tradeserial.newpwd        	,sizeof(t_tradeserial_his.newpwd         ));
		t_tradeserial_his.customer_id    =t_tradeserial.customer_id   ;
		strncpy(t_tradeserial_his.oper_code      ,t_tradeserial.oper_code     	,sizeof(t_tradeserial_his.oper_code      ));
		strncpy(t_tradeserial_his.out_account_id ,t_tradeserial.out_account_id	,sizeof(t_tradeserial_his.out_account_id ));
		strncpy(t_tradeserial_his.in_account_id  ,t_tradeserial.in_account_id 	,sizeof(t_tradeserial_his.in_account_id  ));
		strncpy(t_tradeserial_his.b_act_id       ,t_tradeserial.b_act_id      	,sizeof(t_tradeserial_his.b_act_id       ));
		t_tradeserial_his.sys_id         =t_tradeserial.sys_id        ;
		t_tradeserial_his.condition_id   =t_tradeserial.condition_id  ;
		strncpy(t_tradeserial_his.is_online      ,t_tradeserial.is_online     	,sizeof(t_tradeserial_his.is_online      ));
		t_tradeserial_his.tmark          =t_tradeserial.tmark         ;
		strncpy(t_tradeserial_his.dev_auth       ,t_tradeserial.dev_auth      	,sizeof(t_tradeserial_his.dev_auth       ));
		t_tradeserial_his.comu_ver       =t_tradeserial.comu_ver      ;
		t_tradeserial_his.run_reason     =t_tradeserial.run_reason    ;
		strncpy(t_tradeserial_his.crc            ,t_tradeserial.crc             ,sizeof(t_tradeserial_his.crc            ));
		t_tradeserial_his.ecode          =t_tradeserial.ecode           ;
		t_tradeserial_his.reviseserial_no=t_tradeserial.reviseserial_no ;
		strncpy(t_tradeserial_his.reserve_1      ,t_tradeserial.reserve_1       ,sizeof(t_tradeserial_his.reserve_1      ));
		strncpy(t_tradeserial_his.reserve_2      ,t_tradeserial.reserve_2       ,sizeof(t_tradeserial_his.reserve_2      ));
		strncpy(t_tradeserial_his.reserve_3      ,t_tradeserial.reserve_3       ,sizeof(t_tradeserial_his.reserve_3      ));

		ret=DB_t_tif_tradeserial_his_add(&t_tradeserial_his);
		if(ret)
		{
			DB_t_tif_tradeserial_close_select_by_cur2();
			writelog(LOG_ERR,"Insert history tradelog table record[%d] error,err[%d]",cnt,ret);
			db_rollback();
			return 	ret;
		}


		if(cnt%1000==0)
		{
			ret=db_commit();
			if(ret)
			{
				DB_t_tif_tradeserial_close_select_by_cur2();
				writelog(LOG_ERR,"db_commit ret[%d]",ret);
				db_rollback();
				return 	ret;
			}

		}

	}
	DB_t_tif_tradeserial_close_select_by_cur2();
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	writelog(LOG_INFO,"Backup t_tif_tradeserial succeed!,record=[%d]",cnt);
	*/

	return 0;
}

/****************************************************
      ��    ��	: hhd
      ��������: 2004-10-19 11:34
      ��    �� 	: �����ʻ����ݿ�
      �޸ļ�¼:
*****************************************************/
int BackupAccount()
{
	int cnt=0;
	int ret=0;
	char logic_date[8+1]="";
	T_t_aif_account		account;
	T_t_tif_act_daysum 	act_daysum;

	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}

	ret=DB_t_aif_account_open_select_for_update_by_cur2();
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_open_select_by_cur1 error,errcode=[%d]",ret);
		return 	ret;
	}

	while(1)
	{
		memset(&account,0,sizeof(account));
		memset(&act_daysum,0,sizeof(act_daysum));
		ret=DB_t_aif_account_fetch_select_by_cur2(&account);
		if(ret)
		{
			DB_t_aif_account_close_select_by_cur2();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_aif_account table!");
						return   0;
					}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		//�����ʻ����е�ǰ������ֶ�
		account.last_bala=account.cur_bala;
		account.last_freebala=account.cur_freebala;
		account.last_frozebala=account.cur_frozebala;
		//�����ʻ����п��ⲻƽ�����ֶ�
		if(account.act_type==ACCTYPE_PERMAIN)
		{
			if(account.cur_freebala!=account.card_balance)
			{
				account.nobala_num++;
			}
			else
			{
				account.nobala_num=0;
			}
		}
		//�����ʻ���
		ret=DB_t_aif_account_update_lock_by_cur2(&account);
		if(ret)
		{
			writelog(LOG_ERR,"Update t_aif_account error,record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	ret;
		}
		////���ɱ�����̽���
	 }
	DB_t_aif_account_close_select_by_cur2();
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		return -1;
	}

	writelog(LOG_INFO,"Backup t_aif_account succeed!,record=[%d]",cnt);
	return 0;
}


/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: �������Ѻ�����ԭ�ȿ������ս������ͳһ����
      			  �������Ѳ��������ɶ�Ҷ�ɽ��д���
      �޸ļ�¼	:
*****************************************************/
int CalculateMngFee()
{
	return 0;
}

/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: ������˷Ѳ�����Ŀǰ�о�����û�³�ͳһ�˷�
      �޸ļ�¼	:
*****************************************************/

int WithdrowMngFee()
{
	return 0;
}

/****************************************************
      ��    ��	: hhd
      ��������: 2004-8-13 9:34
      ��    �� 	: ���ɿ��ⲻƽ������̣�����ͼ����ȡ������ӵ�����
      �޸ļ�¼:
*****************************************************/

int CardDBNotBalance()
{
	T_t_tif_report_carddb_nobalance	t_no_balance;
	T_v_tif_report_carddb_nobalance v_no_balance;
	T_t_cif_customer				t_customer;
	T_t_tif_act_daysum			t_daysum;
	int ret=0;
	int cnt=0;
	char logic_date[10+1]="";
	char	buffer[100+1]="";
	//char sCardState[5] = "";
	double	carddb_nobala_money=0;
	int	carddb_nobala_times=0;


	double second;
	char	forward_date[10+1]="";
	char tmp_date[20+1]="";

	//ȡȫ�ֲ�����󿨿ⲻƽ���
	ret=GetParameter(GLOBE_MAX_CARDDB_NOBALANCE_MONEY, buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter error,errcode[%d]",ret);
		return 	ret;
	}
	carddb_nobala_money=atof(buffer);
	//ȡȫ�ֲ�����󿨿ⲻƽ����
	memset(buffer,0,sizeof(buffer));
	ret=GetParameter(GLOBE_MAX_CARDDB_NOBALANCE_TIMES,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter error,errcode[%d]",ret);
		return 	ret;
	}
	carddb_nobala_times=atoi(buffer);
	//ȡϵͳ�߼�����
	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}

	//�õ��߼�����ǰ��ϵͳ�������ƽ������������
	strcpy(tmp_date,logic_date);
	//strcat(tmp_date,"000000");
	ret=datetime2second(tmp_date, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	second=second-(carddb_nobala_times-1)*24*60*60;
	ret=second2datetime(second, tmp_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}
	Strncpy(forward_date,tmp_date,sizeof(forward_date));



	ret=DB_t_tif_report_carddb_nobalance_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete from t_tif_report_carddb_nobalance where date=[%s],errcode=[%d]",logic_date,ret);
		goto L_RETU;
	}

	ret=DB_v_tif_report_carddb_nobalance_open_select_by_c1();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_report_carddb_nobalance err [%d]",ret);
		goto L_RETU;
	}

	while(1)
	{
		memset(&v_no_balance,0,sizeof(v_no_balance));
		memset(&t_no_balance,0,sizeof(t_no_balance));
		memset(&t_daysum,0,sizeof(t_daysum));

		ret=DB_v_tif_report_carddb_nobalance_fetch_select_by_c1(&v_no_balance);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't CardDB not balance record!");
					break;
				}
				else	 break;
			}
			else
			{
				writelog(LOG_DEBUG,"DB_v_tif_report_carddb_nobalance_fetch_select_by_c1 error,errcode=[%d],cnt=[%d]",ret,cnt);
				goto L_RETU;
			}
		}
		cnt++;

		////���ɱ�����̿�ʼ
		strncpy(t_no_balance.balance_date,logic_date,sizeof(t_no_balance.balance_date));
		strncpy(t_no_balance.account_id,v_no_balance.account_id,sizeof(t_no_balance.account_id));
		strncpy(t_no_balance.cut_name,v_no_balance.cut_name,sizeof(t_no_balance.cut_name));
		strncpy(t_no_balance.stuemp_no,v_no_balance.stuemp_no,sizeof(t_no_balance.stuemp_no));
		t_no_balance.type_id=v_no_balance.card_type;
		ret=DB_t_cif_customer_read_by_cut_id(v_no_balance.customer_id,&t_customer);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_cif_customer_read_by_cut_id error,v_no_balance.customer_id=[%d],errcode=[%d]",v_no_balance.customer_id,ret);
			goto L_RETU;
		}
		strncpy(t_no_balance.dept_name,t_customer.classdept_name,sizeof(t_no_balance.dept_name));
		t_no_balance.db_bala=v_no_balance.db_bala;
		t_no_balance.card_bala=v_no_balance.card_bala;
		t_no_balance.diff_bala=v_no_balance.diff_bala;
		t_no_balance.nobala_num=v_no_balance.nobala_num;

		ret=DB_t_tif_report_carddb_nobalance_add(&t_no_balance);
		if(ret)
		{
			writelog(LOG_ERR,"Insert t_tif_report_carddb_nobalance record[%d] err[%d]",cnt,ret);
			goto L_RETU;
		}
/*		//�Կ��ⲻƽ���д���
		ret=GetCardState(v_no_balance.card_id,sCardState);	//�õ���״̬
		if(ret)
		{
			writelog(LOG_ERR,"GetCardState error,err[%d],card_id[%d]",ret,v_no_balance.card_id);
			goto L_RETU;
		}
		if(STATE_TRUE!=sCardState[CARDSTAT_TYPE_FREEZE])	//�����Ѿ�������ʻ������д���
		{
			//�����ƽ�������ֵ���ƣ���ֱ�Ӷ��ᣬ�ȴ��˹�����
			if(v_no_balance.diff_bala>carddb_nobala_money)	//���ж������,�˹�����
			{
				ret=freezecard(v_no_balance.card_id,v_no_balance.customer_id,"system", 0, 0);
				if(ret)
				{
					writelog(LOG_ERR,"freezecard error,err[%d],card_id[%d]",ret,v_no_balance.card_id);
				}
				continue;
			}
			//�����ƽ���С�����ֵ�����ǲ�ƽ�����������ƣ����е��˴������в�������
			if(v_no_balance.nobala_num>carddb_nobala_times)
			{
				//��ʱ���ǲ����죬���δ���
				//�����С�������˻�����ǰ̨���и�д������

				if(v_no_balance.db_bala<v_no_balance.card_bala)
				{
					ret=freezecard(v_no_balance.card_id,v_no_balance.customer_id,"system", 0, 0);
					if(ret)
					{
						writelog(LOG_ERR,"freezecard error,err[%d],card_id[%d]",ret,v_no_balance.card_id);
					}
				}
				//��С��󣬲���һ����ˮ����Ϊ���ʴ���
				if(v_no_balance.db_bala>v_no_balance.card_bala)
				{
					memset(&tradeserial,0,sizeof(tradeserial));
					memset(&t_daysum,0,sizeof(t_daysum));

					tradeserial.serial_type=TXCODE_MAKEUPSERIAL;							//��ӽ��״���
					tradeserial.card_id=v_no_balance.card_id;									//��ӿ����ֶ�
					tradeserial.customer_id=v_no_balance.customer_id;							//��ӿͻ����ֶ�
					strncpy(tradeserial.out_account_id,v_no_balance.account_id,sizeof(tradeserial.out_account_id)-1);
					//��ȡϵͳ�������ƽ����ǰ���˻����˻�����Ϣ
					ret=DB_t_tif_act_daysum_read_by_operate_date_and_account_id(forward_date, v_no_balance.account_id,&t_daysum);
					if(ret)
					{
						writelog(LOG_ERR,"DB_t_tif_act_daysum_read_by_operate_date_and_account_id error,errcode[%d],forward_date=[%s],account_id=[%s]",ret,forward_date,v_no_balance.account_id);
						goto L_RETU;
					}
					tradeserial.trade_fee=t_daysum.cur_freebala-t_daysum.card_balance;			//��ӽ��׽���ֶ�
					//���n��ǰ���˻������С����ϵͳ�����˻���������
					if(tradeserial.trade_fee<=0)
					{
						ret=freezecard(v_no_balance.card_id,v_no_balance.customer_id,"system", 0, 0);
						if(ret)
						{
							writelog(LOG_ERR,"freezecard error,err[%d],card_id[%d]",ret,v_no_balance.card_id);
						}
						continue;
					}
					writelog(LOG_ERR,"in_account=[%s]",tradeserial.in_account_id);
					ret=add_serialno_makeup(&tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"add_serialno_makeup err,errcode[%d]",ret);
						goto L_RETU;
					}
					ret=process_makeup(&tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"process_makeup err,errcode[%d]",ret);
						goto L_RETU;
					}
				}
				continue;
			}


		}
	*/
		////���ɱ�����̽���
	 }


	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		goto L_RETU;
	}

	writelog(LOG_DEBUG,"There have CardDB not balance record[%d]!",cnt);
	return 0;

L_RETU:
	//�ع�����
	db_rollback();
	return -1;

}

/****************************************************
      ��    ��	: hhd
      ��������: 2004-8-13 9:34
      ��    �� 	: �˶�ÿ���˵����񣬼���Ƿ�������ʵ������ͬʱ����
      			  		�������񲻷���¼����
      �޸ļ�¼:
*****************************************************/

int CheckPersonAccount()
{
	T_t_tif_report_erracc	t_erracc;
	T_v_tif_report_erracc	v_erracc;
	T_t_cif_customer		t_customer;
	T_t_aif_account		t_account;
//	T_t_aif_account		account;
	int ret=0;
	int cnt=0;
	char logic_date[10+1]="";

	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}

	//��ʼ���ɸ��˶��ʲ�������
	ret=DB_t_tif_report_erracc_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete from report_carddb_nobalance where date=[%s],errcode=[%d]",logic_date,ret);
		return 	ret;
	}

	ret=DB_v_tif_report_erracc_open_select_by_c1();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_report_erracc view error,errorcode[%d]",ret);
		return 	E_DB_VIEW_ERRACC_R;
	}

	while(1)
	{
		memset(&v_erracc,0,sizeof(v_erracc));
		memset(&t_erracc,0,sizeof(t_erracc));
		memset(&t_customer,0,sizeof(t_customer));
		memset(&t_account,0,sizeof(t_account));
		ret=DB_v_tif_report_erracc_fetch_select_by_c1(&v_erracc);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't error account record!");
					return   0;
				}
				else		break;
			}
			else
				return   E_DB_VIEW_ERRACC_R;
		}
		cnt++;
		////���ɱ�����̿�ʼ

		//ȡ����д��ȡ�߼�ʱ�亯��
		strncpy(t_erracc.balance_date,logic_date,sizeof(t_erracc.balance_date));
		strncpy(t_erracc.account_id,v_erracc.account_id,sizeof(t_erracc.account_id));
		strncpy(t_erracc.cut_name,v_erracc.cut_name,sizeof(t_erracc.cut_name));
		strncpy(t_erracc.stuemp_no,v_erracc.stuemp_no,sizeof(t_erracc.stuemp_no));
		t_erracc.type_id=v_erracc.card_type;
		//ȡ�ͻ��Ĳ�������
		ret=DB_t_aif_account_read_by_account_id(t_erracc.account_id,&t_account);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id err[%d]",ret);
			return 	ret;
		}
		ret=DB_t_cif_customer_read_by_cut_id(t_account.customer_id,&t_customer);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_cif_customer_read_by_cut_id err[%d],customer_id=[%d]",ret,t_account.customer_id);
			return 	ret;
		}
		strncpy(t_erracc.dept_name,t_customer.classdept_name,sizeof(t_erracc.dept_name));

		t_erracc.last_bala=v_erracc.last_bala;
		t_erracc.cur_bala=v_erracc.cur_bala;
		t_erracc.trade_amt=v_erracc.sum_trade;
		t_erracc.diff_bala=t_erracc.last_bala-t_erracc.last_bala-t_erracc.trade_amt;
		//д������
		ret=DB_t_tif_report_erracc_add(&t_erracc);
		if(ret)
		{
			writelog(LOG_ERR,"Insert T_TIF_Report_ErrAcc record[%d] err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_TABLE_ERRACC_I;
		}

		////���ɱ�����̽���
	 }

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		return -1;
	}
	writelog(LOG_DEBUG,"There have error account record[%d]!",cnt);
	return 0;
}

/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: ������ƣ��˶Թ�����������ٺ˶�����
      �޸ļ�¼	:
*****************************************************/

int CheckTotalAccount()
{
	T_v_tif_report_totalacc	v_totalacc;
	int ret=0;

	ret=DB_v_tif_report_totalacc_open_select_by_c1();
	if(ret)
	{
		writelog(LOG_ERR,"Open V_TIF_Report_TotalAcc err [%d]",ret);
		return 	E_DB_VIEW_TOTALACC_R;
	}

	memset(&v_totalacc,0,sizeof(v_totalacc));
	ret=DB_v_tif_report_totalacc_fetch_select_by_c1(&v_totalacc);
	if(ret)
	{
		if(ret==DB_NOTFOUND)
		{
			writelog(LOG_ERR,"There havn't record!");
			return   E_DB_VIEW_TOTALACC_N;
		}
		else
			return   E_DB_VIEW_ERRACC_R;
	}
	DB_v_tif_report_totalacc_close_select_by_c1();
	if(v_totalacc.total)
	{
		writelog(LOG_ERR,"Total account is not balance,Please attention!");
		return 	E_TOTAL_ACC;
	}
	else
		writelog(LOG_DEBUG,"Total account is balance!");
	return 0;
}

/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: ������������������
      �޸ļ�¼	:
*****************************************************/

int CreateActiveReport()
{
	int ret=0;
	int cnt=0;

	double second=0;
	double temp=0;
	char logic_date[10+1]="";
	char	forward_date[10+1]="";
	char tmp_date[20+1]="";

	double total_acc_add_num=0;
	double total_acc_add_amt=0;
	double total_shp_add_num=0;
	double total_shp_add_amt=0;
	double total_dep_add_amt=0;
	double total_earn_add_amt=0;
	double total_in_amt=0;
	double total_cost_amt=0;
	double total_deposit_amt=0;
	double total_cash_amt=0;
	double total_bank_add_amt=0;
	double total_check_add_amt=0;
	double total_outlay_add_amt=0;
	double total_down_subsidy_amt=0;
	double total_up_subsidy_amt=0;

	T_v_tif_report_active	v_active;
	T_t_tif_report_active	t_active;
	T_t_tif_report_active	t_forward_active;
	T_t_aif_account		t_account;


	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}

	//�õ��߼�ʱ���ǰһ��
	strcpy(tmp_date,logic_date);
//	strcat(tmp_date,"000000");
	ret=datetime2second(tmp_date, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	second=second-24*60*60;
	ret=second2datetime(second, tmp_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}

	Strncpy(forward_date,tmp_date,sizeof(forward_date));

	//writelog(LOG_ERR,"logic_date=[%s]",logic_date);
	//writelog(LOG_ERR,"forward_date=[%s]",forward_date);


	ret=DB_t_tif_report_active_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_tif_report_active_del_by_balance_date error,errcode=[%d]",ret);
		return ret;
	}
	ret=DB_v_tif_report_active_open_select_by_cur1();
	if(ret)
	{
		writelog(LOG_ERR,"DB_v_tif_report_active_open_select_by_cur1 error,errcode=[%d]",ret);
		return ret;
	}

	while(1)
	{
		memset(&t_active,0,sizeof(t_active));
		strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date));
		ret=DB_v_tif_report_active_fetch_select_by_cur1(&v_active);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
					writelog(LOG_ERR,"There havn't one record in v_tif_report_active at least!");
					//��ʱΪ�˵��ԣ�����break�����ÿ��ǰһ�����ݾ��ÿ�
					break;
			}
			else
				return   ret;
		}

		cnt++;

		//strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date));
		t_active.seri_type=v_active.serial_type;
		t_active.trade_number=v_active.trade_count;
		//���ǿ���ȥ�����ֶ�
		t_active.trade_amt=0;
		t_active.acc_addnum=v_active.acc_add_num;
		t_active.acc_amt=v_active.acc_add_amt;
		t_active.shop_addnum=v_active.shp_add_num;
		t_active.shop_amt=v_active.shp_add_amt;
		t_active.dep_amt=v_active.dep_add_amt;
		t_active.earn_amt=v_active.earn_add_amt;
		t_active.mng_amt=v_active.in_amt;
		t_active.cost_amt=v_active.cost_amt;
		t_active.ensure_amt=v_active.deposit_amt;
		t_active.cash_amt=v_active.cash_add_amt;
		t_active.bank_amt=v_active.bank_add_amt;
		t_active.check_add_amt=v_active.check_add_amt;
		t_active.outlay_add_amt=v_active.outlay_add_amt;
		t_active.down_subsidy_amt=v_active.down_subsidy_amt;
		t_active.up_subsidy_amt=v_active.up_subsidy_amt;
		//��¼�ϼƱ仯��
		total_acc_add_num =total_acc_add_num +v_active.acc_add_num;
		total_acc_add_amt =total_acc_add_amt +v_active.acc_add_amt;
		total_shp_add_num =total_shp_add_num +v_active.shp_add_num;
		total_shp_add_amt =total_shp_add_amt +v_active.shp_add_amt;
		total_dep_add_amt=total_dep_add_amt+v_active.dep_add_amt;
		total_earn_add_amt=total_earn_add_amt+v_active.earn_add_amt;
		total_in_amt      =total_in_amt      +v_active.in_amt;
		total_cost_amt    =total_cost_amt    +v_active.cost_amt;
		total_deposit_amt =total_deposit_amt +v_active.deposit_amt;
		total_cash_amt    =total_cash_amt    +v_active.cash_add_amt;
		total_bank_add_amt=total_bank_add_amt+v_active.bank_add_amt;
		total_check_add_amt=total_check_add_amt+v_active.check_add_amt;
		total_outlay_add_amt=total_outlay_add_amt+v_active.outlay_add_amt;
		total_down_subsidy_amt=total_down_subsidy_amt+v_active.down_subsidy_amt;
		total_up_subsidy_amt=total_up_subsidy_amt+v_active.up_subsidy_amt;

		ret=DB_t_tif_report_active_add(&t_active);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_tif_report_active_add error,record=[%d],errcode=[%d]",cnt,ret);
			return ret;
		}
	}

	//д��������(�ϴ�+����+�仯���)
	//д�ϴ�״̬---��ȡǰһ��Ľ�������
	memset(&t_active,0,sizeof(t_active));
	ret=DB_t_tif_report_active_read_by_balance_date_and_seri_type(forward_date,9002,&t_forward_active);
	if(ret)
	{
		if(ret==DB_NOTFOUND)
		{
			writelog(LOG_ERR,"There havn't one record at least!");
			//��ʱΪ�˵��ԣ�����break�����ÿ��ǰһ�����ݾ��ÿ�
			//break;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_tif_report_active_read_by_balance_date_and_seri_type error,forward_date=[%s],seri_type=[9002],errcode=[%d]",forward_date,ret);
			return ret;
		}
	}
	else
	{
		t_active.trade_number =t_forward_active.trade_number ;
		//t_active.trade_amt  =t_forward_active.trade_amt    ;
		t_active.acc_addnum   =t_forward_active.acc_addnum   ;
		t_active.acc_amt      =t_forward_active.acc_amt      ;
		t_active.shop_addnum  =t_forward_active.shop_addnum  ;
		t_active.shop_amt     =t_forward_active.shop_amt     ;
		t_active.dep_amt	=t_forward_active.dep_amt;
		t_active.earn_amt =t_forward_active.earn_amt;
		t_active.mng_amt      =t_forward_active.mng_amt      ;
		t_active.cost_amt     =t_forward_active.cost_amt     ;
		t_active.ensure_amt   =t_forward_active.ensure_amt   ;
		t_active.cash_amt     =t_forward_active.cash_amt     ;
		t_active.bank_amt     =t_forward_active.bank_amt     ;
		t_active.check_add_amt=t_forward_active.check_add_amt;
		t_active.outlay_add_amt=t_forward_active.outlay_add_amt;
		t_active.down_subsidy_amt=t_forward_active.down_subsidy_amt;
		t_active.up_subsidy_amt=t_forward_active.up_subsidy_amt;
	}
	strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date));
	t_active.seri_type    =9001;

	ret=DB_t_tif_report_active_add(&t_active);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_report_active_add error,errcode=[%d]",ret);
		return ret;
	}

	//д����״̬---��ȡ��ǰ�ʻ�����ʵ���
	memset(&t_active,0,sizeof(t_active));
	strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date)-1);
	t_active.seri_type=9002;
	t_active.trade_number=0;

	t_active.trade_amt=0;

	//temp=(double)t_active.acc_addnum;
	ret=Get_Account_Count_by_AccType(&temp,ACCTYPE_PERMAIN);
	if(ret)
	{
		writelog(LOG_ERR,"Get_Account_Count_by_AccType error,errcode=[%d]",ret);
		return ret;
	}

	t_active.acc_addnum=(int)temp;
	//writelog(LOG_ERR,"acc_addnum=[%f]",temp);

	//ret=Get_Account_SumMoney_by_AccType(double *SumMoney,int acctype);
	ret=Get_Account_SumMoney_by_AccType(&t_active.acc_amt,ACCTYPE_PERMAIN);
	if(ret)
	{
		writelog(LOG_ERR,"Get_Account_SumMoney_by_AccType error,errcode=[%d]",ret);
		return ret;
	}

	//temp=(double)(t_active.shop_addnum);
	//t_active.acc_amt=temp;
	//writelog(LOG_ERR,"acc_amt=[%f]",temp);

	ret=Get_Account_Count_by_AccType(&temp,ACCTYPE_SHOPMAIN);
	if(ret)
	{
		writelog(LOG_ERR,"Get_Account_Count_by_AccType error,errcode=[%d]",ret);
		return ret;
	}
	//ret=Get_Account_SumMoney_by_AccType(double *SumMoney,int acctype);

	//temp=(double)(t_active.shop_amt);
	t_active.shop_addnum=(int)temp;
	//writelog(LOG_ERR,"shop_addnum=[%f]",temp);
	ret=Get_Account_SumMoney_by_AccType(&t_active.shop_amt,ACCTYPE_SHOPMAIN);
	if(ret)
	{
		writelog(LOG_ERR,"Get_Account_SumMoney_by_AccType error,errcode=[%d]",ret);
		return ret;
	}
	//t_active.shop_amt=(int)temp;
	//writelog(LOG_ERR,"shop_amt=[%f]",temp);

	ret=DB_t_aif_account_read_by_account_id("5031",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.dep_amt=t_account.cur_bala;
	t_account.cur_bala=0;

	ret=DB_t_aif_account_read_by_account_id("5041",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.earn_amt=t_account.cur_bala;
	t_account.cur_bala=0;

	ret=DB_t_aif_account_read_by_account_id("5011",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.mng_amt=t_account.cur_bala;
	t_account.cur_bala=0;
	//writelog(LOG_ERR,"mng_amt=[%f]",temp);
	ret=DB_t_aif_account_read_by_account_id("5021",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.cost_amt=t_account.cur_bala;
	t_account.cur_bala=0;

	ret=DB_t_aif_account_read_by_account_id("2051",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.ensure_amt=t_account.cur_bala;
	t_account.cur_bala=0;

	ret=DB_t_aif_account_read_by_account_id("1011",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.cash_amt=t_account.cur_bala;
	t_account.cur_bala=0;

	ret=DB_t_aif_account_read_by_account_id("1021",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.bank_amt=t_account.cur_bala;
	t_account.cur_bala=0;
	//ȡ���ѱ��ĵ�ǰ���
	ret=DB_t_aif_account_read_by_account_id("1041",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.check_add_amt=t_account.cur_bala;
	t_account.cur_bala=0;
	//ȡ֧Ʊ�ĵ�ǰ���
	ret=DB_t_aif_account_read_by_account_id("1031",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.outlay_add_amt=t_account.cur_bala;
	t_account.cur_bala=0;
	//ȡ�·������ĵ�ǰ���
	ret=DB_t_aif_account_read_by_account_id("1071",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.down_subsidy_amt=t_account.cur_bala;
	t_account.cur_bala=0;
	//ȡ���·������ĵ�ǰ���
	ret=DB_t_aif_account_read_by_account_id("2071",&t_account);
	if(0!=ret&&DB_NOTFOUND!=ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		return ret;
	}
	t_active.up_subsidy_amt=t_account.cur_bala;
	t_account.cur_bala=0;

/*
	t_active.acc_addnum   =t_active.acc_addnum +  total_acc_add_num;
	t_active.acc_amt      =t_active.acc_amt    +  total_acc_add_amt;
	t_active.shop_addnum  =t_active.shop_addnum+  total_shp_add_num;
	t_active.shop_amt     =t_active.shop_amt   +  total_shp_add_amt;
	t_active.mng_amt      =t_active.mng_amt    +  total_in_amt;
	t_active.cost_amt     =t_active.cost_amt   +  total_cost_amt;
	t_active.ensure_amt   =t_active.ensure_amt +  total_deposit_amt;
	t_active.cash_amt     =t_active.cash_amt   +  total_cash_amt;
	t_active.bank_amt     =t_active.bank_amt   +  total_bank_add_amt;
*/

	ret=DB_t_tif_report_active_add(&t_active);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_report_active_add error,errcode=[%d]",ret);
		return ret;
	}

	//д�仯���
	memset(&t_active,0,sizeof(t_active));
	strncpy(t_active.balance_date,logic_date,sizeof(t_active.balance_date));
	t_active.seri_type=9003;
	t_active.trade_number=0;
	//t_active.trade_amt=0;
	t_active.acc_addnum=total_acc_add_num;
	t_active.acc_amt=total_acc_add_amt;
	t_active.shop_addnum=total_shp_add_num;
	t_active.shop_amt=total_shp_add_amt;
	t_active.dep_amt=total_dep_add_amt;
	t_active.earn_amt=total_earn_add_amt;
	t_active.mng_amt=total_in_amt;
	t_active.cost_amt=total_cost_amt;
	t_active.ensure_amt=total_deposit_amt;
	t_active.cash_amt=total_cash_amt;
	t_active.bank_amt=total_bank_add_amt;
	t_active.check_add_amt=total_check_add_amt;
	t_active.outlay_add_amt=total_outlay_add_amt;
	t_active.down_subsidy_amt=total_down_subsidy_amt;
	t_active.up_subsidy_amt=total_up_subsidy_amt;

	ret=DB_t_tif_report_active_add(&t_active);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_report_active_add error,errcode=[%d]",ret);
		return ret;
	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}

	return 0;
}

/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: ���ɲ������������̣�����������ݿ����
      			  �������۽�����ñ�����������ݴӽ���������
      			  �г������Ƿ����������ڸñ�����û�У��������
      			  �Ӳ�ͬ�ı��г���ͬ�����ݣ�����Ƚϸ��ӣ�
      			  ������ʱ�ñ����е����ݻ��Ǵ���ˮ���г���
      			  ��������������Ҫ�޸���������޸�
      �޸ļ�¼	:
*****************************************************/

int CreateOperReport()
{
	T_v_tif_report_oper	v_oper;
	T_t_tif_report_oper		t_oper;

	int ret=0;
	int cnt=0;
	char logic_date[10+1]="";

	//�������Ľ�������
	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}
	ret=DB_t_tif_report_oper_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete t_tif_report_oper report error,errorcode[%d]",ret);
		return 	ret;
	}

	ret=DB_v_tif_report_oper_open_select_by_c1();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_report_oper view error,errorcode[%d]",ret);
		return 	ret;
	}

	while(1)
	{
		memset(&v_oper,0,sizeof(v_oper));
		memset(&t_oper,0,sizeof(t_oper));
		ret=DB_v_tif_report_oper_fetch_select_by_c1(&v_oper);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't record from v_tif_report_oper view!");
					break;
				}
				else
					break;
			}
			else
				return   ret;
		}
		cnt++;
		////���ɱ�����̿�ʼ
		strncpy(t_oper.balance_date,logic_date,sizeof(t_oper.balance_date));
		strncpy(t_oper.operator_code,v_oper.oper_code,sizeof(t_oper.operator_code));
		t_oper.seri_type=v_oper.serial_type;
		t_oper.happen_num=v_oper.trade_count;
		t_oper.acc_add_amt=v_oper.acc_add_amt;
		t_oper.shp_add_amt=v_oper.shp_add_amt;
		t_oper.happen_amt=v_oper.trade_amt;
		t_oper.dep_amt=v_oper.dep_add_amt;
		t_oper.earn_amt=v_oper.earn_add_amt;
		t_oper.bank_amt=v_oper.bank_add_amt;
		t_oper.mng_amt=v_oper.in_amt;
		t_oper.ensure_amt=v_oper.deposit_amt;
		t_oper.cost_amt=v_oper.cost_amt;
		t_oper.cash_amt=v_oper.cash_amt;
		t_oper.check_amt=v_oper.check_amt;
		t_oper.outlay_amt=v_oper.outlay_amt;
		t_oper.down_subsidy_amt=v_oper.down_subsidy_amt;
		t_oper.up_subsidy_amt=v_oper.up_subsidy_amt;
		t_oper.maindevice_id=v_oper.maindevice_id;
		t_oper.device_id=v_oper.device_id;
		ret=DB_t_tif_report_oper_add(&t_oper);
		if(ret)
		{
			writelog(LOG_ERR,"Insert t_tif_report_oper record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	ret;
		}

		////���ɱ�����̽���
	 }

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	return 0;

}

/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: �����̻����㱨����̣�����������ݿ����
      �޸ļ�¼	:
*****************************************************/

int CreateShopReport()
{

	T_v_tif_shopdeptfee		v_shop_balance;
	T_t_tif_report_shop_balance 	t_shop_balance;
	char path_name[256]="";
	char file_name[256]="";
	int ret=0;
	int cnt=0;
	char logic_date[10+1]="";
	int indep_shop_count=0;
	double indep_shop_sum=0;
	FILE *fp;
	char *p=getenv("BIN_PATH");


	//�������Ľ�������
	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}

	if(p==NULL)
	{
	   	writelog(LOG_ERR,"Cann't get env HOME PATH\n");
	   	return -1;
	}
	sprintf(path_name,"%s/balalog",p);
	sprintf(file_name,"%s/shop_trans%8.8s.txt",path_name,logic_date);

	if((fp = fopen(file_name,"wb"))==NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]",file_name);
		return	-1;
	}

	ret=DB_t_tif_report_shop_balance_del_by_balance_date(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete t_tif_report_shop_balance report error,errorcode[%d]",ret);
		return 	ret;
	}
	//�õ����������̻��������ͽ��
	ret=GetCountIndepShop(&indep_shop_count);
	if(ret)
	{
		writelog(LOG_ERR,"GetCountIndepShop error,errorcode[%d]",ret);
		return 	ret;
	}
	ret=GetSumIndepShop(&indep_shop_sum);
	if(ret)
	{
		writelog(LOG_ERR,"GetSumIndepShop error,errorcode[%d]",ret);
		return 	ret;
	}

	if(0!=indep_shop_count)
	{
		if(NULL==fprintf(fp,"%d	%f	%s\r\n",indep_shop_count,indep_shop_sum,logic_date));
		{
			writelog(LOG_ERR,"fprintf error,");
		}
	}

	ret=DB_v_tif_shopdeptfee_open_select_by_c5();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_shopdeptfee view error,errorcode[%d]",ret);
		return 	E_DB_SHOPDEPTFEE_R;
	}

	while(1)
	{
		memset(&v_shop_balance,0,sizeof(v_shop_balance));
		memset(&t_shop_balance,0,sizeof(t_shop_balance));
		ret=DB_v_tif_shopdeptfee_fetch_select_by_c5(&t_shop_balance);
		if(ret)
		{
			DB_v_tif_shopdeptfee_close_select_by_c5();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from T_v_tif_shopdeptfee view!");
						return   0;
					}
				else		break;
			}
			else
				return   E_DB_SHOPDEPTFEE_R;
		}
		cnt++;
		////���ɱ�����̿�ʼ

		//д�������ں����̻�����(�̻�����+��������)

		strncpy(t_shop_balance.balance_date,logic_date,sizeof(t_shop_balance.balance_date));

		t_shop_balance.total_amt=t_shop_balance.trade_amt+t_shop_balance.mng_amt;

		//�ж��Ƿ�Ϊ���������̻�,����reserve1�ֶ�Ϊ1��Ϊ��������
		if(0==strncmp(t_shop_balance.reserve1,"1",1))
		{
			//printf("count=[%d]\n",cnt);
			if(NULL==fprintf(fp,"%d	%f\r\n",t_shop_balance.shop_id,t_shop_balance.total_amt))
			{
				writelog(LOG_ERR,"fprintf error,");
			}
		}

		ret=DB_t_tif_report_shop_balance_add(&t_shop_balance);
		if(ret)
		{
			writelog(LOG_ERR,"Insert t_tif_report_shop_balance record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_TABLE_ERRACC_I;
		}

		////���ɱ�����̽���
	 }
	
	DB_v_tif_shopdeptfee_close_select_by_c5();
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	fclose(fp);
	return 0;
}
int CreateRichDebtReport()
{

	int ret=0;
	int cnt=0;
	double second;
	char logic_date[10+1]="";
	char	forward_date[10+1]="";
	char tmp_date[20+1]="";

	char path_name[256]="";
	char file_name[256]="";
	FILE *fp;
	char *p=getenv("BIN_PATH");


	T_t_tif_subject_balance t_subject_balance;
	T_t_tif_subject_balance t_forward_subject_balance;

	T_t_tif_subject		t_subject;
	//�õ��߼�ʱ��
	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}
	//�õ��߼�ʱ���ǰһ��
	strcpy(tmp_date,logic_date);
//	strcat(tmp_date,"000000");
	ret=datetime2second(tmp_date, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	second=second-24*60*60;
	ret=second2datetime(second, tmp_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}
	Strncpy(forward_date,tmp_date,sizeof(forward_date));

	//writelog(LOG_ERR,"logic_date=[%s]",logic_date);
	//writelog(LOG_ERR,"forward_date=[%s]",forward_date);

	if(p==NULL)
	{
	   	writelog(LOG_ERR,"Cann't get env HOME PATH\n");
	   	return -1;
	}
	sprintf(path_name,"%s/balalog",p);
	sprintf(file_name,"%s/bala_trans%8.8s.txt",path_name,logic_date);

	if((fp = fopen(file_name,"wb"))==NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]",file_name);
		return	-1;
	}

	//�������Ľ�������
	ret=DB_t_tif_subject_balance_del_by_txdate(logic_date);
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Delete t_tif_report_rich_debt report error,errorcode[%d]",ret);
		return 	ret;
	}

	ret=DB_v_tif_acttype_trade_open_select_by_c5();
	if(ret)
	{
		writelog(LOG_ERR,"Open v_tif_acttype_trade view error,errorcode[%d]",ret);
		return 	E_DB_SHOPDEPTFEE_R;
	}

	while(1)
	{
		memset(&t_subject_balance,0,sizeof(t_subject_balance));
		ret=DB_v_tif_acttype_trade_fetch_select_by_c5(&t_subject_balance);
		if(ret)
		{
			DB_v_tif_acttype_close_select_by_c5();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from T_tif_acttype_trade view!");
						return   0;
					}
				else		break;
			}
			else
				return   E_DB_SHOPDEPTFEE_R;
		}
		cnt++;

		//д��������
		strncpy(t_subject_balance.txdate,logic_date,sizeof(t_subject_balance.txdate));
		//д�ڳ���Ŀ���
		//��ȡ��Ŀ��Ļ�����Ϣ�����±�ʹ��
		ret=DB_t_tif_subject_read_by_subno(t_subject_balance.subno,&t_subject);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_tif_subject_read_by_subno error,errorcode[%d]",ret);
			return 	E_DB_SUBJECT_R;
		}
		//��ȡǰһ��Ŀ�Ŀ����
     		ret=DB_t_tif_subject_balance_read_by_txdate_and_subno(forward_date,t_subject_balance.subno,&t_forward_subject_balance);
		if(ret)
		{
			if(100==ret)
			{
				t_subject_balance.bbala_flag=t_subject.direct;
				t_subject_balance.bbala=0;
			}
			else
			{
				writelog(LOG_ERR,"Read from t_tif_subject_balance error,errorcode[%d]",ret);
				return 	E_DB_SHOPDEPTFEE_R;
			}
		}
		else
		{
			t_subject_balance.bbala_flag=t_forward_subject_balance.endbala_flag;
			t_subject_balance.bbala=t_forward_subject_balance.endbala;
		}
		//ȡ��Ŀ���еĿ�Ŀ����
		DB_t_tif_subject_read_by_subno(t_subject_balance.subno,&t_subject);
		//д��ĩ��Ŀ���

		t_subject_balance.endbala_flag=t_subject_balance.bbala_flag;
		if(3!=t_subject.direct)
		{
			if(1==t_subject_balance.bbala_flag)
			{
				 t_subject_balance.endbala=t_subject_balance.bbala+(t_subject_balance.dramnt-t_subject_balance.cramt);
			}
			else	 t_subject_balance.endbala=t_subject_balance.bbala-(t_subject_balance.dramnt-t_subject_balance.cramt);
		}
		else
		{
			if(1==t_subject_balance.bbala_flag)
			{
				 t_subject_balance.endbala=t_subject_balance.bbala+(t_subject_balance.dramnt-t_subject_balance.cramt);
			}
			else	 t_subject_balance.endbala=t_subject_balance.bbala-(t_subject_balance.dramnt-t_subject_balance.cramt);

			if(t_subject_balance.endbala<0)
			{
				t_subject_balance.endbala=abs(t_subject_balance.endbala);
				if(1==t_subject_balance.bbala_flag)	t_subject_balance.endbala_flag=2;
				else								t_subject_balance.endbala_flag=1;
			}

		}
		//д�����ļ�
		if(NULL==fprintf(fp,"%s	%f	%f	%f\r\n",t_subject_balance.subno,t_subject_balance.bbala,t_subject_balance.endbala,t_subject_balance.endbala-t_subject_balance.bbala));
		{
			writelog(LOG_ERR,"fprintf error,");
		}
		ret=DB_t_tif_subject_balance_add(&t_subject_balance);
		if(ret)
		{
			writelog(LOG_ERR,"Insert t_tif_subject_balance record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_TABLE_ERRACC_I;
		}

	 }
	fclose(fp);
	DB_v_tif_shopdeptfee_close_select_by_c5();
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	return 0;
}

int CreateBankCompReport()
{
	return 0;
}

int CreateTransReport()
{
	return 0;
}

/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: �ս����ͳһ�޸Ĳ��ָ�����Ч�Ĳ���
      �޸ļ�¼	:
*****************************************************/

int ChangeConfigPara()
{
	int ret=0;
	int cnt=0;

	char logic_date[10+1]="";
	char tmp_date[10+1]="";
	char next_date[10+1]="";
	double second=0;

//	T_t_cif_shop 			t_shop;
//	T_t_cif_shop_log		t_shop_log;
	T_t_cif_shop_pos		t_shop_pos;
	T_t_cif_shop_pos_log	t_shop_pos_log;
	T_t_pif_syskey 		t_pif_syskey;
	T_t_tif_warrant		t_tif_warrant;

	ret=GetLogicDate(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"Get logic date error,errcode=[%d]",ret);
		return 	ret;
	}
	//�õ��߼�ʱ�����һ��
	strcpy(tmp_date,logic_date);
//	strcat(tmp_date,"000000");
	ret=datetime2second(tmp_date, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	second=second+24*60*60;
	ret=second2datetime(second, tmp_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}
	Strncpy(next_date,tmp_date,sizeof(next_date));

	//writelog(LOG_ERR,"logic_date=[%s]",logic_date);
	//writelog(LOG_ERR,"next_date=[%s]",next_date);


	//�޸�ƾ֤��ĵ�ǰֵΪ1
	ret=DB_t_tif_warrant_read_lock_by_cur_and_wtype(100,&t_tif_warrant);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_warrant_read_lock_by_cur_and_wtype error,errcode=[%d]",ret);
		return 	ret;
	}
	strcpy(t_tif_warrant.cur_no,"1");
	ret=DB_t_tif_warrant_update_by_wtype(100,&t_tif_warrant);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_warrant_update_by_wtype error,errcode=[%d]",ret);
		return 	ret;
	}

	/*
	//�޸��̻���Ϣ��ʹ��ʱ�̻���Ϣ���������Ч
	//ɾ���̻���Ϣ�������
	ret=DB_t_cif_shop_del_all();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_cif_shop_del error,errorcode[%d]",ret);
		return 	E_DB_SHOP_D;
	}
	//������ʱ��Ϣ������ݵ��̻���Ϣ����

	ret=DB_t_cif_shop_log_open_select_by_cur2_and_update_date(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_shop_log_open_select_by_cur1 error,errorcode[%d]",ret);
		return 	ret;
	}
	while(1)
	{
		memset(&t_shop,0,sizeof(t_shop));
		memset(&t_shop_log,0,sizeof(t_shop_log));
		ret=DB_t_cif_shop_log_fetch_select_by_cur2(&t_shop_log);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't record from t_cif_shop_log table!");
					break;
				}
				else		break;
			}
			else
				writelog(LOG_DEBUG,"DB_t_cif_shop_log_fetch_select_by_cur2 error,errcode=[%d]!",ret);
				return   E_DB_SHOPDEPTFEE_R;
		}

		//strncpy(t_shop.update_date  ,logic_date, sizeof(t_shop.update_date  ));
		t_shop.shop_id		  =t_shop_log.shop_id;
		t_shop.cut_id             =t_shop_log.cut_id ;
		t_shop.dept_id            =t_shop_log.dept_id;
		strncpy(t_shop.shop_name    ,t_shop_log.shop_name  ,  sizeof(t_shop.shop_name    ))  ;
		t_shop.shop_type         =t_shop_log.shop_type;
		strncpy(t_shop.is_indep      ,t_shop_log.is_indep   ,   sizeof(t_shop.is_indep      ));
		strncpy(t_shop.is_leaf       ,t_shop_log.is_leaf    ,   sizeof(t_shop.is_leaf       ));
		t_shop.shop_state         =t_shop_log.shop_state;
		strncpy(t_shop.shop_manager ,t_shop_log.shop_manager, sizeof(t_shop.shop_manager ))   ;
		strncpy(t_shop.man          ,t_shop_log.man         , sizeof(t_shop.man          ))   ;
		strncpy(t_shop.sex           ,t_shop_log.sex        ,   sizeof(t_shop.sex           ));
		t_shop.nation             =t_shop_log.nation;
		strncpy(t_shop.man_id       ,t_shop_log.man_id      , sizeof(t_shop.man_id       ))   ;
		strncpy(t_shop.tel          ,t_shop_log.tel         , sizeof(t_shop.tel          ))   ;
		strncpy(t_shop.address     ,t_shop_log.address    , sizeof(t_shop.address     ))      ;
		strncpy(t_shop.is_getfee     ,t_shop_log.is_getfee  ,   sizeof(t_shop.is_getfee     ));
		t_shop.ratio              =t_shop_log.ratio;
		t_shop.manager_type       =t_shop_log.manager_type;
		t_shop.duty_type          =t_shop_log.duty_type   ;
		strncpy(t_shop.reg_time     ,t_shop_log.reg_time  ,   sizeof(t_shop.reg_time     ))   ;
		strncpy(t_shop.comments    ,t_shop_log.comments   , sizeof(t_shop.comments    ))      ;

		cnt++;
		ret=DB_t_cif_shop_add(&t_shop);
		if(ret)
		{
			writelog(LOG_ERR,"Insert DB_t_cif_shop_add record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_SHOP_I;
		}
		strncpy(t_shop_log.update_date,next_date,sizeof(t_shop_log.update_date));
		ret=DB_t_cif_shop_log_add(&t_shop_log);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_cif_shop_log_add record[%d],err[%d]",cnt,ret);
			db_rollback();
			return ret;
			//return 	E_DB_SHOP_LOG_I;
		}

	 }
	*/
	//�޸��̻��豸��Ϣ��ʹ��ʱ�̻��豸��Ϣ���������Ч
	//ɾ���̻��豸��Ϣ�������

	ret=DB_t_cif_shop_pos_del_all();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_cif_shop_del error,errorcode[%d]",ret);
		return 	E_DB_SHOP_D;
	}
	//������ʱ��Ϣ������ݵ��̻���Ϣ����
	ret=DB_t_cif_shop_pos_log_open_select_by_cur1_and_update_date(logic_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_shop_pos_log_open_select_by_cur1_and_update_date error,errorcode[%d]",ret);
		return 	ret;
	}
	while(1)
	{
		memset(&t_shop_pos,0,sizeof(t_shop_pos));
		memset(&t_shop_pos_log,0,sizeof(t_shop_pos_log));
		ret=DB_t_cif_shop_pos_log_fetch_select_by_cur1(&t_shop_pos_log);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_cif_shop_pos_log table!");
						break;
					}
				else		break;
			}
			else
			{
				writelog(LOG_DEBUG,"DB_t_cif_shop_pos_log_fetch_select_by_cur1 error,errcode=[%d]",ret);
				return   ret;
			}
		}

		t_shop_pos.id            =t_shop_pos_log.id        ;
		t_shop_pos.device_id     =t_shop_pos_log.device_id ;
		t_shop_pos.shop_id       =t_shop_pos_log.shop_id   ;
		strncpy(t_shop_pos.begin_date    ,t_shop_pos_log.begin_date ,sizeof(t_shop_pos.begin_date  ));
		strncpy(t_shop_pos.begin_time    ,t_shop_pos_log.begin_time ,sizeof(t_shop_pos.begin_time  ));
		strncpy(t_shop_pos.end_time      ,t_shop_pos_log.end_time   ,sizeof(t_shop_pos.end_time    ));
		strncpy(t_shop_pos.end_date      ,t_shop_pos_log.end_date   ,sizeof(t_shop_pos.end_date    ));
		strncpy(t_shop_pos.comments      ,t_shop_pos_log.comments   ,sizeof(t_shop_pos.comments    ));
		cnt++;
		ret=DB_t_cif_shop_pos_add(&t_shop_pos);
		if(ret)
		{
			writelog(LOG_ERR,"Insert DB_t_cif_shop_pos record[%d],err[%d]",cnt,ret);
			db_rollback();
			return 	E_DB_SHOP_POS_I;
		}
		strncpy(t_shop_pos_log.update_date,next_date,sizeof(t_shop_pos_log.update_date));
		ret=DB_t_cif_shop_pos_log_add(&t_shop_pos_log);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_cif_shop_pos_log_add record[%d],err[%d]",cnt,ret);
			db_rollback();
			return ret;
			//return 	E_DB_SHOP_POS_LOG_I;
		}

	 }
	//����ȫ�ֲ�����ʹ��ʱȫ�ֲ������������Ч
	//��ʱ����˵����ʵ��
	//T_t_pif_cur_syspara	t_syspara;


	//�����߼����ڣ�����һ��
	ret=SetLogicDate(1);
	if(ret)
	{
		writelog(LOG_ERR,"SetLogicDate(1) error,errcode=[%d]!",ret);
		return ret;
	}


	//����ϵͳ��ֵ���е�KEYTYPE_TRADESERIAL��ֵΪ��1��
	memset(&t_pif_syskey,0,sizeof(t_pif_syskey));
	ret=DB_t_pif_syskey_read_lock_by_cur_and_key_code(KEYTYPE_TRADESERIAL, &t_pif_syskey);
	if(ret)
	{
		writelog(LOG_ERR,"read syskey err[%d]type[%s]",ret,KEYTYPE_TRADESERIAL);
		if(DB_NOTFOUND==ret)
		{
			return E_DB_SYSKEY_N;
		}
		else
			return E_DB_SYSKEY_R;
	}
	t_pif_syskey.key_value=1;
	ret=DB_t_pif_syskey_update_lock_by_cur(&t_pif_syskey);
	if(ret)
	{
		writelog(LOG_ERR,"update syskey err[%d]",ret);
		return E_DB_SYSKEY_U;
	}
	DB_t_pif_syskey_free_lock_cur();
	ret = InitializeSyskey();
	if( ret )
	{
		return ret;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	return 0;
}

/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: ���յ������ת
      �޸ļ�¼	:
*****************************************************/
int AccountCarryForward()
{
	int ret=0;
	int cnt=0;
	double trans_amt=0;
	char yes_or_no[2]="";

	T_t_tif_tradeserial		t_tradeserial;
	T_t_aif_account		t_account;
	T_t_cif_shop			t_shop;


	//�ֽ��������д���ʽ�ת
	memset(&t_account,0,sizeof(t_account));
	ret=DB_t_aif_account_read_by_account_id(INNER_ACCOUNT_CASH,&t_account);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d],account_id=[%s]",ret,INNER_ACCOUNT_CASH);
		return 	ret;
	}
	trans_amt=t_account.cur_bala;
	memset(&t_tradeserial,0,sizeof(t_tradeserial));
	ret=add_serialno(&t_tradeserial, trans_amt,INNER_ACCOUNT_CASH,INNER_ACCOUNT_BANKDEPOSIT);
	if(ret)
	{
		writelog(LOG_ERR,"add_serialno error,errcode=[%d]",ret);
		db_rollback();
		return 	ret;
	}
	//�����ˮ�ɹ����ύ����
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}

	//�����������������Ĵ���
	ret=process(&t_tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		goto L_RETU;
	}

	//������ˮ״̬
	getsysdate(t_tradeserial.enteract_date);			//��������
	getsystime(t_tradeserial.enteract_time);			//����ʱ��
	t_tradeserial.serial_state=SERISTAT_DEBT;		//������
	ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
		goto L_RETU;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		goto L_RETU;
	}
	//printf("process OK\n");

	//�̻��ʻ������������ʻ���ת
	//���������̻���ת
	strcpy(yes_or_no,TYPE_YES);
	ret=DB_t_cif_shop_open_select_by_cur3_and_is_indep(yes_or_no);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_shop_open_select_by_cur3_and_is_indep error, errcode=[%d]",ret);
		return ret;
	}

	while(1)
	{
		ret=DB_t_cif_shop_fetch_select_by_cur3(&t_shop);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"DB_t_cif_shop_fetch_select_by_cur2 have not record,shop_id=[%d]!",t_shop.shop_id);
						break;
					}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		ret=SearchLeafshop_and_Trans(t_shop.shop_id,yes_or_no);
		if(ret)
		{
			writelog(LOG_DEBUG,"SearchLeafshop_and_Trans faild,t_shop.shop_id=[%d],cnt=[%d]!",t_shop.shop_id,cnt);
			break;
		}
	}
	//�Ƕ��������̻���ת
	strcpy(yes_or_no,TYPE_NO);
	ret=DB_t_cif_shop_open_select_by_cur3_and_is_indep(yes_or_no);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_shop_open_select_by_cur3_and_is_indep error, errcode=[%d]",ret);
		return ret;
	}

	while(1)
	{
		ret=DB_t_cif_shop_fetch_select_by_cur3(&t_shop);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"DB_t_cif_shop_fetch_select_by_cur2 have not record,shop_id=[%d]!",t_shop.shop_id);
						break;
					}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		ret=SearchLeafshop_and_Trans(t_shop.shop_id,yes_or_no);
		if(ret)
		{
			writelog(LOG_DEBUG,"SearchLeafshop_and_Trans faild,t_shop.shop_id=[%d]!",t_shop.shop_id);
			break;
		}
	}

	writelog(LOG_INFO,"Transfer succeed!");
	return 0;

L_RETU:
	//�ع�����
	db_rollback();
	//������ˮ״̬
	getsysdate(t_tradeserial.enteract_date);			//��������
	getsystime(t_tradeserial.enteract_time);			//����ʱ��
	//t_tradeserial.ecode=*pRetCode;					//������
	t_tradeserial.serial_state=SERISTAT_DEBTEXC;		//�����쳣״̬
	ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
	}
	//�ύ����
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
	}
	return E_ENTER_ACCOUNT;
}


int AccountCarryForward1()
{
	int ret=0;
	int cnt=0;
	int tm_shop_id=0;
	double trans_amt=0;
	//char yes_or_no[2]="";

	T_t_tif_tradeserial		t_tradeserial;
	T_t_aif_account		t_account;
	T_t_cif_shop			t_shop;


	//�ֽ��������д���ʽ�ת
	memset(&t_account,0,sizeof(t_account));
	ret=DB_t_aif_account_read_by_account_id(INNER_ACCOUNT_CASH,&t_account);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d],account_id=[%s]",ret,INNER_ACCOUNT_CASH);
		return 	ret;
	}
	if(0==t_account.cur_bala)
	{
		writelog(LOG_INFO,"Trade amt equal 0,trade cancel!");
	}
	else
	{
		trans_amt=t_account.cur_bala;
		memset(&t_tradeserial,0,sizeof(t_tradeserial));
		ret=add_serialno(&t_tradeserial, trans_amt,INNER_ACCOUNT_CASH,INNER_ACCOUNT_BANKDEPOSIT);
		if(ret)
		{
			writelog(LOG_ERR,"add_serialno error,errcode=[%d]",ret);
			return 	ret;
		}
		//�����������������Ĵ���
		ret=process(&t_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"process ret[%d]",ret);
			goto L_RETU;
		}
		//�����ˮ�ɹ����ύ����
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			db_rollback();
			return 	ret;
		}
		//������ˮ״̬
		getsysdate(t_tradeserial.enteract_date);			//��������
		getsystime(t_tradeserial.enteract_time);			//����ʱ��
		t_tradeserial.serial_state=SERISTAT_DEBT;		//������
		ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
			goto L_RETU;
		}
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			goto L_RETU;
		}
	}
	//printf("process OK\n");

	//�̻��ʻ������������ʻ���ת
	//���������̻���ת
	ret=DB_t_aif_account_open_select_by_cur6_and_act_type_and_current_state(ACCTYPE_SHOPMAIN,1);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_open_select_by_cur6_and_act_type_and_current_state error, errcode=[%d]",ret);
		return ret;
	}

	while(1)
	{
		cnt++;
		memset(&t_account,0,sizeof(t_account));
		ret=DB_t_aif_account_fetch_select_by_cur6(&t_account);
		if(ret)
		{
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_ERR,"DB_t_aif_account_fetch_select_by_cur6 have not record");
						break;
					}
				else		break;
			}
			else
			{
				writelog(LOG_ERR,"DB_t_aif_account_fetch_select_by_cur6 error,cnt=[%d],errcode=[%d]",cnt,ret);
				return   ret;
			}
		}


		if(0==t_account.cur_bala)
		{
			writelog(LOG_INFO,"Trade amt equal 0,trade cancel!");
		}
		else
		{
			ret=DB_t_cif_shop_read_by_cut_id(t_account.customer_id,&t_shop);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_cif_shop_read_by_cut_id error,customer_id=[%d],errcode=[%d]",t_account.customer_id,ret);
				return   ret;
			}
			while(1)
			{
				//printf("test1!\n");
				if(0==t_shop.shop_id) 				//֤�����ʻ�Ϊ�Ƕ��������˻�
				{
					//printf("%d\n",__LINE__);
					memset(&t_tradeserial,0,sizeof(t_tradeserial));
					ret=add_serialno(&t_tradeserial, t_account.cur_bala,INNER_ACCOUNT_FINANCETRANSER,t_account.account_id);
					{
						writelog(LOG_ERR,"add_serialno error,errcode=[%d]",ret);
						db_rollback();
						return 	ret;
					}
					//�����������������Ĵ���
					ret=process(&t_tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"process ret[%d]",ret);
						goto L_RETU;
					}
					//������ˮ״̬
					getsysdate(t_tradeserial.enteract_date);			//��������
					getsystime(t_tradeserial.enteract_time);			//����ʱ��
					t_tradeserial.serial_state=SERISTAT_DEBT;		//������
					ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
						goto L_RETU;
					}

					break;

				}

				//printf("%d\n",__LINE__);

				if(strncmp(t_shop.is_indep,TYPE_YES,1))
				{
					//ret=add_serialno(&t_tradeserial, t_account.cur_bala,INNER_ACCOUNT_BANKTRANSFER,INNER_ACCOUNT_BANKTRANSFER);
					memset(&t_tradeserial,0,sizeof(t_tradeserial));
					ret=add_serialno(&t_tradeserial, t_account.cur_bala,INNER_ACCOUNT_BANKTRANSFER,t_account.account_id);
					if(ret)
					{
						writelog(LOG_ERR,"add_serialno error,errcode=[%d]",ret);
						db_rollback();
						return 	ret;
					}
					//�����������������Ĵ���
					ret=process(&t_tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"process ret[%d]",ret);
						goto L_RETU;
					}
					//������ˮ״̬
					getsysdate(t_tradeserial.enteract_date);			//��������
					getsystime(t_tradeserial.enteract_time);			//����ʱ��
					t_tradeserial.serial_state=SERISTAT_DEBT;		//������
					ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
					if(ret)
					{
						writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
						goto L_RETU;
					}
					break;
				}

				ret=DB_t_cif_shop_read_by_shop_id(tm_shop_id,&t_shop);

				if(ret)
				{
					writelog(LOG_ERR,"DB_t_cif_shop_read_by_shop_id error,shop_id=[%d],errcode=[%d]",t_shop.dept_id,ret);
					return   ret;
				}
				tm_shop_id=t_shop.dept_id;

			}

		}

	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		goto L_RETU;
	}
	writelog(LOG_INFO,"Shop account carry foreward succeed!record=[%d]",cnt);
	return 0;

L_RETU:
	//�ع�����
	db_rollback();
	//������ˮ״̬
	getsysdate(t_tradeserial.enteract_date);			//��������
	getsystime(t_tradeserial.enteract_time);			//����ʱ��
	//t_tradeserial.ecode=*pRetCode;					//������
	t_tradeserial.serial_state=SERISTAT_DEBTEXC;		//�����쳣״̬
	ret=UpdTradeserialBySerialNo(t_tradeserial.serial_no,&t_tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"UpdCosumelogBySerialNo ret[%d]serialno[%d]",ret,t_tradeserial.serial_no);
	}
	//�ύ����
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
	}
	return E_ENTER_ACCOUNT;
}

/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: ɾ����ˮ�������������е�����
      �޸ļ�¼	:
*****************************************************/
int DelTradeDate()
{
	int ret=0;

	//ɾ��������ϸ��
	ret=DB_t_tif_tradelog_del_all_by_step_commit();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_tif_tradelog_del_all error,errcode=[%d]",ret);
		db_rollback();
		return 	ret;
	}

	//ɾ����ˮ��
	ret=DB_t_tif_tradeserial_del_all_by_step_commit();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_del_all error,errcode=[%d]",ret);
		db_rollback();
		return 	ret;
	}
	//ɾ���Ž���ˮ��
	ret=Db_t_door_txdtl_del_all_by_step_commit();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"Db_t_door_txdtl_del_all_by_step_commit error,errcode=[%d]",ret);
		db_rollback();

	}
	//ɾ����Ϣ���б�
	ret=DB_t_tif_meslist_del_all_in_03_04_60_by_step_commit();
	if((0!=ret)&&(100!=ret))
	{
		writelog(LOG_ERR,"DB_t_tif_meslist_del_all_in_03_04_60_by_step_commit error,errcode=[%d]",ret);
		db_rollback();
		return 	0;
	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}
	writelog(LOG_INFO,"Delete t_tif_tradeserial and t_tif_tradelog succeed!");
	return 0;
}


/****************************************************
      ��    ��	: hhd
      ��������	: 2004-8-13 9:34
      ��    �� 	: �޸��ս��־�����쿪��
      �޸ļ�¼	:
*****************************************************/
int Startup()
{
	int ret=0;
	ret=SetParameter(GLOBE_FLAG_BALANCE,"0");
	if(ret)
	{
		writelog(LOG_ERR,"Change system balance flag failed!");
		return ret;
	}
	return 0;
}

/****************************************************
      ��    ��	: hhd
      ��������	: 2005-12-16 9:34
      ��    �� 	: ���չ����ͬ�������Ķ���״̬����
      				  ����ͻ�
      �޸ļ�¼	:
*****************************************************/

int DoFrozenCustomer()
{
	int ret=0;
	int cnt=0;
	int count=0;
	int card_id=0;
	int frozen_status=1;
	T_t_cif_customer t_customer;

	memset(&t_customer,0,sizeof(t_customer));

	ret=DB_t_cif_customer_open_select_with_hold_by_cur3_and_frozen_status(frozen_status);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_customer_open_select_by_cur2_and_frozen_status error, errcode=[%d]",ret);
		return ret;
	}
	while(1)
	{
		ret=DB_t_cif_customer_fetch_select_by_cur3(&t_customer);
		if(ret)
		{
			DB_t_cif_customer_close_select_by_cur3();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"DB_t_cif_customer_fetch_select_by_cur2 have not record");
					break;
				}
				else		break;
			}
			else
				return   ret;
		}
		cnt++;
		ret=get_tradecard_no_by_stupid(t_customer.stuemp_no,&card_id);
		if(ret)
		{
			writelog(LOG_DEBUG,"Get_tradecard_no_by_stupid stuemp[%s] error,errcode=[%d]",t_customer.stuemp_no,ret);
			continue;
		}

		ret=freezecard(card_id,t_customer.cut_id,"system",0,0);
		if(ret)
		{
			writelog(LOG_DEBUG,"Freezecard customer error,errcode[%d],cut_id[%d],card_id[%d]",ret,t_customer.cut_id,card_id);
			continue;
		}
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"db_commit ret[%d]",ret);
			continue;
		}
		count++;

	}
	ret=DB_t_cif_customer_close_select_by_cur3();
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cif_customer_close_select_by_cur3 error,errcode[%d]",ret);
	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		db_rollback();
		return 	ret;
	}

	writelog(LOG_DEBUG,"Freezecard customer total records[%d]",count);
	return 0;

}


/****************************************************
  ��    ��	: hhd
  ��������	: 2006-08-08 9:34
  ��    �� 	: �����Ϻ���ѧ�����󣬰Ѷ���������̻���ÿ���Ӫҵ
  			  ���ݰ���ָ�������ݸ�ʽ�γ��ļ���ftp��ʽ���͸�
  			  �Ϻ���ѧsap������
  ���˵�� 	:
  			  �ĵ���ʽ��TXT�ı��ļ�
			  �ĵ�����: ����:ת���̻���<Tab>ת���ܽ��<Tab>ת������
							ע�����ֶ���Tab���ָ���ת������Ϊ8λ�����ַ�����
								��20060728
						��ϸ:�̻�ΨһID<Tab>ת���ܽ��
  �޸ļ�¼	:
*****************************************************/
int GenIndepShopFtpData()
{

}





