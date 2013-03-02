/* --------------------------------------------
 * ��������: F847102.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������:  ��ʧ��
 * --------------------------------------------
 * �޸�����:2004-11-29
 * �޸���Ա:	�Ž�
 * �޸�����: �޸�״̬����
 * �汾��Ϣ:1.0.0.1
 * ��ע��Ϣ:
 * --------------------------------------------
 * �޸�����:2004-11-29
 * �޸���Ա:	������
 * �޸�����: ���Ӹ���ѧ���Ż��߿ͻ��Ž��й�ʧ
 			Ϊ��ʵ��Ȧ���ն˻��߶�ý��ȵĹ�ʧ����
 * �汾��Ϣ:1.0.0.1
 * ��ע��Ϣ:

 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "fdsqc.h"

int F847102(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
  	int ret = 0;
//	char logicdate[11] = "";
//	char enddate[10 + 1] = "";
	int	card_id = 0;
	char	Operator[33+1] = "";
	char badcard_status[2]="";
//	int	Cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double	dUniqno = 0;
	char stuemp_no[20+1]="";
	int	cut_id=0;
	T_t_pif_cardlossinfo cardlossinfo;
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_tif_meslist tMesList;
	T_t_pif_card	tCard;

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tMesList,0,sizeof(tMesList));
	memset(&tCard,0,sizeof(tCard));

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	card_id = rPack->lvol1;													//����ʶ
//	Cut_id = rPack->lvol0;													//�ͻ���
	des2src(Operator,rPack->scust_limit);									//����Ա��
	maindevice_id = rPack->lvol6;											//�ϴ�����վ��ʶ
	device_id = rPack->lvol7;												//�ɼ��豸��ʶ
	cut_id=rPack->lvol8;
	des2src(stuemp_no,rPack->scust_auth);
	if(0==card_id)
	{
		if(0==cut_id)
		{
			ret=get_tradecard_no_by_stupid(stuemp_no,&card_id);			//����ʶ
			if(ret)
			{
				if(100==ret)
				{
					writelog(LOG_ERR,"get_tradecard_no_by_stupid have no recode,errcode=[%d]",ret);
					*pRetCode=E_TRANS_SCHACC_NOEXIT;
					goto L_RETU;
				}
				if(-811==ret)
				{
					writelog(LOG_ERR,"This customer have more than one card,errcode=[%d]",ret);
					*pRetCode=E_TRANS_SCHCARD_TWICE;
					goto L_RETU;
				}
				writelog(LOG_ERR,"get_tradecard_no_by_stupid error,errcode=[%d]",ret);
				*pRetCode=E_DB_CARD_R;
				goto L_RETU;
			}
		}
		else if(strlen(stuemp_no)!=0)
		{
			ret=GetLostCardIdByCustomId(cut_id, &card_id);
			if(ret)
			{
				if(100==ret)
				{
					writelog(LOG_ERR,"GetLostCardIdByCustomId have no recode,errcode=[%d]",ret);
					*pRetCode=E_TRANS_SCHACC_NOEXIT;
					goto L_RETU;
				}
				if(-811==ret)
				{
					writelog(LOG_ERR,"This customer have more than one card,errcode=[%d]",ret);
					*pRetCode=E_TRANS_SCHCARD_TWICE;
					goto L_RETU;
				}
				writelog(LOG_ERR,"GetLostCardIdByCustomId error,errcode=[%d]",ret);
				*pRetCode=E_DB_CARD_R;
				goto L_RETU;
			}
		}
	}
	
	//���ͻ���Ϣ���ж��Ƿ���Թ�ʧ
	//�޸Ŀ���־����Ϊ����״̬
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &tCard);
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
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_id[%d] db card_id[%d]",card_id,tCard.card_id);
		*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode = E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode = E_CARDNO_WFAIL;
		goto L_RETU;
	}	
	if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode = E_CARDNO_LOST;
		goto L_RETU;
	}
	//	�޸Ŀ�״̬Ϊ��ʧ
	tCard.state_id[CARDSTAT_TYPE_LOST]=STATE_TRUE;
	//����״̬
	if(rPack->lvol2==1)
		tCard.bad_status[0]='1';
	ret=DB_t_pif_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_pif_card_free_lock_by_cur();

	//	���뿨��ʧ��Ч���ޱ�
/*
	ret=GetLostCardValiddate(sysdate,enddate);											//��ù�ʧ��Ч����
	if (ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	cardlossinfo.card_id = card_id;													//����
	des2src(cardlossinfo.begin_date,sysdate);											//��ʼ����
	des2src(cardlossinfo.end_date,enddate);											//��������
	des2src(cardlossinfo.operate_date,sysdate);										//��������
	des2src(cardlossinfo.operate_time,systime);										//����ʱ��
	cardlossinfo.state_id=STATE_VALID;												//��Ч
	ret = DB_t_pif_cardlossinfo_add(&cardlossinfo);
	if (ret)
	{
		*pRetCode = E_DB_CARDLOSSINFO_I;
		writelog(LOG_ERR,"errcode[%d] ",ret);
		goto L_RETU;
	}
*/
	//����ÿ��ű�����,���ʧʱ�Ժ�����������
	if(STATE_FALSE==tCard.state_id[CARDSTAT_TYPE_FREEZE])
	{
		//	�����������
		ret=DB_t_tif_black_sheet_del_by_card_id_and_is_ad(tCard.card_id,DELETE_BLACKLIST);
		if(ret)
		{
			if(ret!=DB_NOTFOUND)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
		}
		ret=InsertToBlkList(tCard.card_id,ADD_BLACKLIST);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
			goto L_RETU;
		}
		//�㲥������
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,card_id);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//��ɾ��־

		tMesList.funid = 930005;
		tMesList.pfunid = 930003;
		tMesList.max_send_cnt = 10;
		tMesList.level = MESLIST_PRIORITY_REALTIME;
		tMesList.msgtype = MESLIST_TYPE_ORDER;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			goto L_RETU;
		}
	}
	//	׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ERRCODE = [%d]",ret);
		goto L_RETU;
	}
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	tradeserial.serial_no = D2I(dUniqno);										//��ˮ��
	tradeserial.serial_type = TXCODE_CARD_LOSS;								//��ʧ
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;							//��ˮ״̬
	tradeserial.maindevice_id = maindevice_id;									//�ϴ�����վ��ʶ
	tradeserial.device_id = device_id;											//�ɼ��豸��ʶ
	tradeserial.card_id = card_id;											//���׿���
	tradeserial.customer_id=tCard.cosumer_id;									//�ͻ���
	des2src(tradeserial.oper_code,Operator);

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
	return 0;
L_RETU:
	return -1;
}
