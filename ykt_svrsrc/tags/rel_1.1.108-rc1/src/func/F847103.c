/* --------------------------------------------
 * ��������: F47103.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������: ��ҿ�
 * --------------------------------------------
 * �޸�����:2004-11-29
 * �޸���Ա:	�Ž�
 * �޸�����: �޸�ҵ���߼���״̬����
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

static int SaveCancelLossSerial(T_t_tif_tradeserial  *pTradeserial)
{
	int ret;
	
	//	���뿨������ˮ��
	ret = DB_t_tif_tradeserial_add(pTradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret [%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	return ret;
}
int F847103(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
  	int ret = 0;
	int	hi_cardid = 0;
	char	hi_Operator[33+1] = "";
	int	hi_Cut_id  = 0;
	int	hi_maindevice_id = 0;
	int	hi_device_id = 0;
	double	h_temp_Serial_no = 0;
	char  logicdate[11]="";
	char sysdate[11]="";
	char systime[8]="";
	char dbdate[9]="";
	char dbtime[7]="";
	char volume[13]="";

	T_t_tif_tradeserial tradeserial;
	T_t_pif_card		tCard;
       T_t_tif_meslist tMesList;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);		//���ڸ������������CPACK����ͷ��հ�ͷλͼ�Ͱ����е�����

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tCard,0,sizeof(tCard));
	memset(&tMesList,0,sizeof(tMesList));

	hi_cardid = rPack->lvol1;													//����ʶ
	hi_Cut_id = rPack->lvol2;													//�ͻ���
	des2src(hi_Operator,rPack->scust_limit);										//����Ա��
	hi_maindevice_id = rPack->lvol6;											//�ϴ�����վ��ʶ
	hi_device_id = rPack->lvol7;												//�ɼ��豸��ʶ

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//	��鿨״̬�Ƿ�Ϊ��ʧ
	ret = DB_t_pif_card_read_by_card_id(hi_cardid,&tCard);
	if (ret)
	{
		writelog(LOG_ERR,"card_id[%d]",hi_cardid);
		if(DB_NOTFOUND==ret)
			*pRetCode = E_CARDNO_NOT_EXIST;
		else
			*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(hi_cardid!=tCard.card_id)
	{
		writelog(LOG_ERR,"card_id[%d] db card_id[%d]",hi_cardid,tCard.card_id);
		*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		*pRetCode = E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_FREEZE])
	{
		*pRetCode = E_CARDNO_FREEZE;
		goto L_RETU;
	}
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&h_temp_Serial_no);  					//��������ˮ��
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
	tradeserial.serial_no = D2I(h_temp_Serial_no);											//��ˮ��
	tradeserial.serial_type = TXCODE_CARD_COMEBACK_LOSS;								//���
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;								//��ˮ״̬
	tradeserial.maindevice_id = hi_maindevice_id;									//�ϴ�����վ��ʶ
	tradeserial.device_id = hi_device_id;											//�ɼ��豸��ʶ
	tradeserial.card_id = hi_cardid;													//���׿���
	tradeserial.customer_id = hi_Cut_id;
	des2src(tradeserial.oper_code, hi_Operator);
	
	if(STATE_FALSE==tCard.state_id[CARDSTAT_TYPE_LOST])
	{
		//�����ظ����
		//���´�������
		//	�����������
		ret=InsertToBlkList(hi_cardid,DELETE_BLACKLIST);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
			goto L_RETU;
		}
		//�㲥������
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,hi_cardid);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,DELETE_BLACKLIST);	//��ɾ��־

		tMesList.funid = 930005;
		tMesList.pfunid = 930003;
		tMesList.level = MESLIST_PRIORITY_REALTIME;
		tMesList.msgtype = MESLIST_TYPE_ORDER;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			goto L_RETU;
		}
		ret=get_datetime_from_db(dbdate,dbtime);
		if(ret)
		{
			*pRetCode = ret;
			writelog(LOG_ERR,"ret [%d]",ret);
			goto L_RETU;
		}
		ret = SaveCancelLossSerial(&tradeserial);
		if(ret)
		{
			*pRetCode = ret;
			writelog(LOG_ERR,"ret [%d]",ret);
			goto L_RETU;
		}
		SetCol(handle,0);
		SetCol(handle,F_SSERIAL0,0);
		memset(volume,0,sizeof(volume));
		memcpy(volume,dbdate+2,6);
		memcpy(volume+6,dbtime,6);
		des2src(out_pack->sserial0,volume);		//���汾��
		PutRow(handle,out_pack,pRetCode,szMsg);
		return 0;
	}
	
	ret=IsExistNoLostCardByCustomId(hi_Cut_id);
	if(ret)
	{
		if(E_NORMALCARD_NOLOST==ret)
		{
			*pRetCode = E_BACK_CARD_FOR_NORCARD2;
		}
		else if( E_TEMPCARD_NOLOST==ret)
		{
			//�����������ʹ�õ���ʱ��������ʾ���˵��˿������ܽ��
			if(tCard.type_id==CT_NORMAL)
				*pRetCode =E_BACK_CARD_FOR_NORCARD;
			else
				*pRetCode =E_BACK_CARD_FOR_TMPCARD;
		}
		else
		{
			*pRetCode = ret;
		}
		goto L_RETU;
	}
	if(STATE_FALSE==tCard.state_id[CARDSTAT_TYPE_FREEZE])
	{
		//�����������
		ret=InsertToBlkList(hi_cardid,DELETE_BLACKLIST);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
			goto L_RETU;
		}
		//�㲥������
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,hi_cardid);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,DELETE_BLACKLIST);	//��ɾ��־

		tMesList.funid = 930005;
		tMesList.pfunid = 930003;
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
	//	�޸Ŀ�״̬Ϊ���״̬
	ret = UpdateCardState(hi_cardid,CARDSTAT_TYPE_LOST,STATE_FALSE);
	if (ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	//	׼�����ݲ��뽻����ˮ��
	/////////////////
	ret = SaveCancelLossSerial(&tradeserial);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	ret=get_datetime_from_db(dbdate,dbtime);
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ERRCODE = [%d]",ret);
		goto L_RETU;
	}
	SetCol(handle,0);
	SetCol(handle,F_SSERIAL0,0);
	memset(volume,0,sizeof(volume));
	memcpy(volume,dbdate+2,6);
	memcpy(volume+6,dbtime,6);
	des2src(out_pack->sserial0,volume);		//���汾��
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

