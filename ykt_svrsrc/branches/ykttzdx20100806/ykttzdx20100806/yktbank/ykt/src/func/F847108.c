/* --------------------------------------------
 * ��������: F47107.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������: ����ʧ�ܺ���¿�״̬��Ϣ
 * --------------------------------------------
 * �޸�����:2004-11-29
 * �޸���Ա:	�Ž�
 * �޸�����: �޸�ҵ���߼���״̬����
 * �汾��Ϣ:1.0.0.1
 * ��ע��Ϣ:
 * --------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"

int F847108(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int card_id = 0;
	char logicdate[11]="";
	char comments[101] = "";
	char buf[64] = "";
	T_t_pif_card  card;

	memset(&card,0,sizeof(card));

	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//�޸�ԭ��״̬Ϊ����д��ʧ��״̬
	card_id = in_pack->lvol0;

	if(in_pack->lvol0<1)
	{
		writelog(LOG_ERR,"in_pack->lserial1[%d]",in_pack->lvol0);
		*pRetCode=E_INPUT_CARDNO;
		goto L_RETU;
	}
	if(in_pack->lserial1<1)
	{
		writelog(LOG_ERR,"in_pack->lserial1[%d]",in_pack->lserial1);
		*pRetCode= E_INPUT_SERIALNO;
		goto L_RETU;
	}
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &card);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	card.state_id[CARDSTAT_TYPE_WFAIL]=STATE_TRUE;
	if( CARDWFAIL_WATER == card.is_managefee[0])
	{
		ret = GetXmlValue(card.comments,sizeof buf,XML_KEY_TRADECODE2,buf);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		AddXmlItemStr(comments,XML_KEY_TRADECODE2,buf);
		
		ret = GetXmlValue(card.comments,sizeof buf,XML_KEY_SERIALNO2,buf);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		AddXmlItemStr(comments,XML_KEY_SERIALNO2,buf);

		ret = GetXmlValue(card.comments,sizeof buf,XML_KEY_OPERATEDATE2,buf);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		AddXmlItemStr(comments,XML_KEY_OPERATEDATE2,buf);
	}
	else
	{
		card.is_managefee[0] = CARDWFAIL_NORMAL;
	}
	
	memset(card.comments,0,sizeof(card.comments));
	des2src(card.comments,comments);
	AddXmlItemStr(card.comments, XML_KEY_OPERATEDATE,logicdate);
	AddXmlItemInt(card.comments,XML_KEY_SERIALNO,in_pack->lserial1);
	AddXmlItemInt(card.comments,XML_KEY_TRADECODE,in_pack->lvol2);

	ret=DB_t_pif_card_update_lock_by_cur(&card);
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
	return 0;
L_RETU:
	return -1;
}
