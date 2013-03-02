/* --------------------------------------------
 * ��������: F847117.sqc
 * ��������: Sep 29 2004
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ���Ῠ
 * --------------------------------------------
 * �޸�����: 2004-11-29
 * �޸���Ա: �Ž�
 * �޸�����: �޸�״̬����
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
	 
	 
static int do_froze_onecard(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int  ret = 0;
	int	card_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char	oper[33+1] = "";
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
		return ret;
	}
	//	׼��������Ϣ
	card_id = rPack->lvol1;												//����ʶ
	cut_id = rPack->lvol0;												//�ͻ���
	des2src(oper,rPack->scust_limit);									//����Ա��
	maindevice_id = rPack->lvol6;											//�ϴ�����վ��ʶ
	device_id = rPack->lvol7;												//�ɼ��豸��ʶ

	//	���ͻ���Ϣ���ж��Ƿ���Զ���
	ret = GetCardState(card_id,sCardState);
	if (ret)
	{
		writelog(LOG_ERR,"card_id[%d]",sCardState);
		return ret;
	}
	if('2'==sCardState[CARDSTAT_TYPE_REG])
	{
		ret = E_CARDNO_LOGOUT;
		return ret;
	}
	if(STATE_TRUE==sCardState[CARDSTAT_TYPE_FREEZE])
	{
		ret = E_CARDNO_FREEZE;
		return ret;
	}
	//	�޸Ŀ�״̬Ϊ����
	ret = UpdateCardState(card_id,CARDSTAT_TYPE_FREEZE,STATE_TRUE);
	if (ret)
	{
		writelog(LOG_ERR,"SQLCODE=[%d]",ret);
		return ret;
	}

	ret=InsertToBlkList(card_id,ADD_BLACKLIST);
	if (ret)
	{
		writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
		return ret;
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
		return ret;
	}
	//	׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerial_no);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"ERRCODE = [%d]",ret);
		return ret;
	}
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	tradeserial.serial_no = D2I(dSerial_no);									//��ˮ��
	tradeserial.serial_type = TXCODE_FREEZE_CARD;								//��ʧ
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;							//��ˮ״̬
	tradeserial.maindevice_id = maindevice_id;									//�ϴ�����վ��ʶ
	tradeserial.device_id = device_id;											//�ɼ��豸��ʶ
	tradeserial.card_id = card_id;												//���׿���
	tradeserial.customer_id=cut_id;											//�ͻ���
	des2src(tradeserial.oper_code,oper);
	//	���뽻����ˮ��
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		return ret;
	}
	return 0;
}

static int do_fronze_by_stuempno(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int cust_id;
	int ret,count;
	T_t_pif_card card;
	int all_card_id[100];
	
	// ��ѯ�ͻ���
	ret = get_cut_id_by_stuemp_no(rPack->scust_no,&cust_id);
	if(ret)
	{
		writelog(LOG_ERR,"find cust_id by stuemp_no error, stuemp_no[%s]",rPack->scust_no);
		return ret;
	}
	//  �������п�
	ret = DB_t_pif_card_open_select_for_update_by_c5_and_cosumer_id(cust_id);
	if(ret)
	{
		writelog(LOG_ERR,"stuemp_no not exists [%s]",rPack->scust_no);
		if(DB_NOTFOUND == ret)
			return DB_NOTFOUND;
		return E_DB_CARD_R;
	}
	count = 0;
	while(1)
	{
		memset(&card,0,sizeof card);
		ret = DB_t_pif_card_fetch_select_by_c5(&card);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				if(count == 0)
					return DB_NOTFOUND;
				break;
			}
			return E_DB_CARD_R;
		}
		//writelog(LOG_ERR,"read stuemp_no[%s], card_id[%d],state[%s]",rPack->scust_no,card.card_id,card.state_id);
		if('2' == card.state_id[CARDSTAT_TYPE_REG] 
		 || STATE_TRUE == card.state_id[CARDSTAT_TYPE_FREEZE])
			continue; // ���ô���
			
		if(STATE_TRUE == card.state_id[CARDSTAT_TYPE_LOST])
		{
			// �Ѿ���ʧ�Ŀ���ֻ������Ϊ�����־����
			card.state_id[CARDSTAT_TYPE_FREEZE] = STATE_TRUE;
			ret = DB_t_pif_card_update_lock_by_c5(&card);
			if(ret)
			{
				return E_DB_CARD_U;
			}
			continue;
		}
		// �����Ŀ���Ҫ����
		all_card_id[count] = card.card_id;
		count++;
	}
	// ��ʵ���߼���������Ӧ��ֻ��һ�������Ŀ��������ˣ�ͳһ����
	for(;count>0;--count)
	{
		// ���Ῠ
		rPack->lvol0 = cust_id;
		rPack->lvol1 = all_card_id[count-1];
		//writelog(LOG_ERR,"input card [%d]",all_card_id[count-1]);
		sleep(1);
		ret = do_froze_onecard(handle,iRequest,rPack,pRetCode,szMsg);
		if(ret)
		{
			return ret;
		}
	}
	return 0;
}

static int do_fronze_by_stuempno_ex(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	ret = do_fronze_by_stuempno(handle,iRequest,rPack,pRetCode,szMsg);
	if(ret)
	{
		writelog(LOG_ERR,"froze card error ,stuemp_no[%s],ret[%d]",rPack->scust_no,ret);
		if(db_rollback())
		{
			return E_DB_ROLLBACK;
		}
		return ret;
	}
	writelog(LOG_DEBUG,"froze card success , stuemp_no[%s] ",rPack->scust_no);
	return 0;
}
int F847117(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
  	if(strlen(rPack->scust_no)>0)
	{
		// ͨ��ѧ�Ź�ʧ
		ret = do_fronze_by_stuempno_ex(handle,iRequest,rPack,pRetCode,szMsg);
		if(ret)
		{
			*pRetCode =ret;
			return -1;
		}
		return 0;
	}
	else
	{
		// ԭ��ʧ��ʽ
		ret = do_froze_onecard(handle,iRequest,rPack,pRetCode,szMsg);
		if(ret)
		{
			*pRetCode =ret;
			return -1;
		}
		return 0;
	}
}
