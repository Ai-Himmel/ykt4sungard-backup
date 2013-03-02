/* --------------------------------------------
 * ��������: F847120.sqc
 * ��������: 2005-03-27
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ����ȷ��
 * --------------------------------------------
 * �޸�����: 2007-02-05
 * �޸���Ա: ����
 * �޸�����: �ڲ�д���ɹ�����и���д��ʧ�ܱ�־, 
 *           �ڶ�Ǯ��״̬��, ���벹д������Ǯ��
 *           ���ܹ����¿���־
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/
 
#define _IN_SQC_
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

#define PURESE_COUNT 4
int F847120(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int card_id=0;
	T_t_pif_card card;
    int cnt_purse_no = 0;
	char deal_flag[1 + 1] = "";
	T_t_tif_writefailed tWriteFailed;
	deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_Y;
	cnt_purse_no = rPack->lvol1;
	memset(&card,0,sizeof(card));
    memset(&tWriteFailed, 0, sizeof(tWriteFailed));
    
	card_id=rPack->lvol0;
	//�жϿ�״̬�Ƿ�Ϊд��δ�ɹ�״̬
	if(card_id<1)
	{
		*pRetCode= E_INPUT_CARDNO_CANNOT_NULL;
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

	switch(rPack->lserial0)
	{
		case 847119:
//		    writelog(LOG_ERR,"��ˮ��[%d]",rPack->lserial1);
//		    writelog(LOG_ERR,"Ǯ����[%d]",cnt_purse_no);
		    ret = DB_t_tif_writefailed_read_by_card_id_and_purese_no_and_deal_serial_no(card.card_id, cnt_purse_no, rPack->lserial1, &tWriteFailed);
		    if (ret)
		    {
		         if (ret != DB_NOTFOUND)
		         {
		            *pRetCode = E_DB_WRITEFAILED_R;
		         }
		         else
		         {
		            *pRetCode = E_DB_WRITEFAILED_N;
		         }
		         goto L_RETU;
		    }

            if (CARDWFAIL_PACKET_DEAL_FLAG_Y == tWriteFailed.deal_flag[0])
                tWriteFailed.deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_N;

            ret = DB_t_tif_writefailed_update_by_card_id_and_purese_no_and_deal_serial_no(card.card_id, cnt_purse_no, rPack->lserial1, &tWriteFailed);
            if (ret)
            {
                *pRetCode = E_DB_WRITEFAILED_I;
                goto L_RETU;
            }

            ret = DB_t_tif_writefailed_read_by_card_id_and_deal_flag(card.card_id, &deal_flag[0], &tWriteFailed);
            if (ret)
            {
                if (DB_NOTFOUND == ret)
                {
                      if (STATE_TRUE == card.state_id[CARDSTAT_TYPE_WFAIL])
                      {
                           card.state_id[CARDSTAT_TYPE_WFAIL] = STATE_FALSE;
                      }
                }
            }
            /*
		    ret = DB_t_tif_writefailed_read_by_card_id_and_purese_no_and_deal_flag(card.card_id,cnt_purse_no,&deal_flag[0],&tWriteFailed);
            if (ret)
            {
               if (ret != DB_NOTFOUND)
               {
                    *pRetCode = E_DB_WRITEFAILED_R;
                    goto L_RETU;
               }
            }
            */
          
		/*
			if(STATE_FALSE==card.state_id[CARDSTAT_TYPE_WFAIL])
			{
				DB_t_pif_card_free_lock_by_cur();
				*pRetCode=E_CARDSTATE_NOTWRITEFAIL;
				goto L_RETU;
			}
			card.state_id[CARDSTAT_TYPE_WFAIL]=STATE_FALSE;	//�޸�״̬
			memset(card.comments,0,sizeof(card.comments));
        */
			break;
		case 847123:
			if('3'!=card.state_id[CARDSTAT_TYPE_REG])
			{
				DB_t_pif_card_free_lock_by_cur();
				*pRetCode=E_CARD_STATE_NOT_CHANGE;
				goto L_RETU;
			}
			card.state_id[CARDSTAT_TYPE_REG]=STATE_TRUE;		//�޸�״̬
			break;
		default:
			DB_t_pif_card_free_lock_by_cur();
			*pRetCode= E_TXCODE_NOT_EXIST;
			goto L_RETU;
	}
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
