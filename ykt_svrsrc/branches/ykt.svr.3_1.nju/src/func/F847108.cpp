/* --------------------------------------------
 * ��������: F847108.sqc
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
 * --------------------------------------------
 * �޸�����:2006-12-19
 * �޸���Ա:	����
 * �޸�����: �޸�ҵ���߼�
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
	int cardno = 0;
	char logicdate[11]="";
	double dUniqNo = 0; 
	T_t_card  card;
    T_t_tif_writefailed tWriteFailed;

	memset(&card,0,sizeof(card));
    memset(&tWriteFailed, 0, sizeof tWriteFailed);

	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//�޸�ԭ��״̬Ϊ����д��ʧ��״̬
	cardno = in_pack->lvol0;

	if(in_pack->lvol0<1)
	{
		writelog(LOG_ERR,"cardno=[%d]",in_pack->lvol0);
		*pRetCode=E_INPUT_CARDNO;
		goto L_RETU;
	}
	if(in_pack->lserial1<1)
	{
		writelog(LOG_ERR,"serial_no=[%d]",in_pack->lserial1);
		*pRetCode= E_INPUT_SERIALNO;
		goto L_RETU;
	}

	ret=DB_t_card_read_lock_by_cur_and_cardno(cardno, &card);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}

	if (STATE_FALSE == card.cardattr[CARDSTAT_TYPE_WFAIL])
	{
	card.cardattr[CARDSTAT_TYPE_WFAIL]=STATE_TRUE;
	}

	ret=DB_t_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_card_free_lock_by_cur();
    
    //д��д��ʧ�ܱ�
	ret = getNewUniqNo(KEYTYPE_WRITEFAILED, &dUniqNo);              //���д��ʧ�ܱ����ID��
    if (ret)
    {
        writelog(LOG_ERR,"ret[%d]",ret);
        *pRetCode = ret;
        goto L_RETU;
    }

	tWriteFailed.id = D2I(dUniqNo);
	tWriteFailed.cardno = cardno;
	tWriteFailed.serial_no = in_pack->lserial1;
//	tWriteFailed.serial_type = TXCODE_WRITE_ERROR;
    tWriteFailed.serial_type = in_pack->lvol2;
	tWriteFailed.purese_no = PURSE_NO_ONE;
	tWriteFailed.deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_Y;
	des2src(tWriteFailed.tx_date,logicdate);
	des2src(tWriteFailed.comments, "����ʧ��");
	
	ret = DB_t_tif_writefailed_add(&tWriteFailed);
	if (ret)
	{
	    *pRetCode = E_DB_WRITEFAILED_I;
        goto L_RETU;    
	}

/*
	memset(card.comments,0,sizeof(card.comments));
	AddXmlItemStr(card.comments, XML_KEY_OPERATEDATE,logicdate);
	AddXmlItemInt(card.comments,XML_KEY_SERIALNO,in_pack->lserial1);
	AddXmlItemInt(card.comments,XML_KEY_TRADECODE,in_pack->lvol2);
*/	
	return 0;
L_RETU:
	return -1;
}
