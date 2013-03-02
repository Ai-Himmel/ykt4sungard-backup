/* --------------------------------------------
 * ��������: F847119.sqc
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

int F847117(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
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
		*pRetCode=ret;
		goto L_RETU;
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
		*pRetCode = ret;
		goto L_RETU;
	}
	if('2'==sCardState[CARDSTAT_TYPE_REG])
	{
		*pRetCode = E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	if(STATE_TRUE==sCardState[CARDSTAT_TYPE_FREEZE])
	{
		*pRetCode = E_CARDNO_FREEZE;
		goto L_RETU;
	}
	//	�޸Ŀ�״̬Ϊ����
	ret = UpdateCardState(card_id,CARDSTAT_TYPE_FREEZE,STATE_TRUE);
	if (ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"SQLCODE=[%d]",ret);
		goto L_RETU;
	}

	ret=InsertToBlkList(card_id,ADD_BLACKLIST);
	if (ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
		goto L_RETU;
	}
	
	//�㲥������
	AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,card_id);
	//AddXmlItemStr(tMesList.incontent, XML_KEY_VERNUM, black_sheet.volume);
	AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//��ɾ��־

	tMesList.funid = 930005;
	tMesList.level = 1;
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	//	׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerial_no);  					//��������ˮ��
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
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
