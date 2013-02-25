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

static int SaveCancelLossSerial(T_t_tif_tradeserial  *pTradeserial) {
    int ret;

    //	���뿨������ˮ��
    ret = DB_t_tif_tradeserial_add(pTradeserial);
    if (ret) {
        writelog(LOG_ERR,"ret [%d]",ret);
        if(DB_REPEAT==ret)
            return E_DB_TRADESERIAL_E;
        else
            return E_DB_TRADESERIAL_I;
    }
    return ret;
}
int F847103(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret = 0;
    int	hi_cardid = 0;
    char	hi_Operator[33+1] = "";
    int	hi_Cut_id  = 0;
    int	hi_maindeviceid = 0;
    int	hi_deviceid = 0;
    int card_is_lost = 0;
    double	h_temp_Serial_no = 0;
    char  logicdate[11]="";
    char sysdate[11]="";
    char systime[8]="";
    char dbdate[9]="";
    char dbtime[7]="";
    char volume[13]="";

    T_t_tif_tradeserial tradeserial;
    T_t_card		tCard;
    T_t_tif_meslist tMesList;
    T_t_device		t_device;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);		//���ڸ������������CPACK����ͷ��հ�ͷλͼ�Ͱ����е�����

    memset(&t_device,0,sizeof(t_device));
    memset(&tradeserial,0,sizeof(tradeserial));
    memset(&tCard,0,sizeof(tCard));
    memset(&tMesList,0,sizeof(tMesList));

    hi_cardid = rPack->lvol1;													//����ʶ
    hi_Cut_id = rPack->lvol2;													//�ͻ���
    des2src(hi_Operator,rPack->scust_limit);										//����Ա��
    hi_maindeviceid = rPack->lvol6;											//�ϴ�����վ��ʶ
    hi_deviceid = rPack->lvol7;												//�ɼ��豸��ʶ
    if(hi_maindeviceid==0&&hi_deviceid!=0) {
        DB_t_device_read_by_deviceid(hi_deviceid, &t_device);
        hi_maindeviceid=t_device.subsystem_id;
    }
    getsysdate(sysdate);
    getsystime(systime);
    ret=GetLogicDate(logicdate);								//ҵ������
    if(ret) {
        *pRetCode=ret;
        goto L_RETU;
    }
    //	��鿨״̬�Ƿ�Ϊ��ʧ
    ret = DB_t_card_read_lock_by_cur_and_cardno(hi_cardid,&tCard);
    if (ret) {
        writelog(LOG_ERR,"cardno[%d]",hi_cardid);
        if(DB_NOTFOUND==ret)
            *pRetCode = E_CARDNO_NOT_EXIST;
        else
            *pRetCode=E_DB_CARD_R;
        goto L_RETU;
    }
    hi_Cut_id=tCard.custid;
    if('2'==tCard.cardattr[CARDSTAT_TYPE_REG]) {
        DB_t_card_free_lock_by_cur();
        *pRetCode = E_CARD_CLOSE;
        goto L_RETU;
    }
    if('1'==tCard.cardattr[CARDSTAT_TYPE_FREEZE]) {
        DB_t_card_free_lock_by_cur();
        *pRetCode = E_CARD_FREEZE;
        goto L_RETU;
    }

    card_is_lost = (tCard.cardattr[CARDSTAT_TYPE_LOST] == STATE_TRUE) ? 1 : 0;

    if(card_is_lost) {
        ret=IsExistNoLostCardByCustomId(hi_Cut_id);
        if(ret) {
            if(E_NORMALCARD_NOLOST==ret) {
                *pRetCode = E_BACK_CARD_FOR_NORCARD2;
            } else if( E_TEMPCARD_NOLOST==ret) {
                //�����������ʹ�õ���ʱ��������ʾ���˵��˿������ܽ��
                if(tCard.type_id==CT_NORMAL)
                    *pRetCode =E_BACK_CARD_FOR_NORCARD;
                else
                    *pRetCode =E_BACK_CARD_FOR_TMPCARD;
            } else {
                *pRetCode = ret;
            }
            DB_t_card_free_lock_by_cur();
            goto L_RETU;
        }
    }
    tCard.cardattr[CARDSTAT_TYPE_LOST]=STATE_FALSE;

    ret=DB_t_card_update_lock_by_cur(&tCard);
    if(ret) {
        writelog(LOG_ERR,"cardno[%d]",hi_cardid);
        if(DB_NOTFOUND==ret)
            *pRetCode= E_CARDNO_NOT_EXIST;
        else
            *pRetCode= E_DB_CARD_U;
        goto L_RETU;
    }
    DB_t_card_free_lock_by_cur();


    ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&h_temp_Serial_no);  					//��������ˮ��
    if(ret) {
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
    tradeserial.maindeviceid = hi_maindeviceid;									//�ϴ�����վ��ʶ
    tradeserial.deviceid = hi_deviceid;											//�ɼ��豸��ʶ
    tradeserial.cardno = hi_cardid;													//���׿���
    tradeserial.custid = hi_Cut_id;
    des2src(tradeserial.opercode, hi_Operator);

    /*
    if(!card_is_lost)
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

    	ret = SaveCancelLossSerial(&tradeserial);
    	if(ret)
    	{
    		*pRetCode = ret;
    		writelog(LOG_ERR,"ret [%d]",ret);
    		goto L_RETU;
    	}
    	ret=GetCardMaxBlkVerNo(hi_cardid,volume);
    	if(ret)
    	{
    		*pRetCode = ret;
    		goto L_RETU;
    	}
    	SetCol(handle,0);
    	SetCol(handle,F_SSERIAL0,0);
    	des2src(out_pack->sserial0,volume);		//���汾��
    	//writelog(LOG_ERR,"volume:[%s]",volume);
    	PutRow(handle,out_pack,pRetCode,szMsg);

    	return 0;
    }
    */

    if(STATE_FALSE==tCard.cardattr[CARDSTAT_TYPE_FREEZE]) {
        //�����������
        ret=InsertToBlkList(hi_cardid,DELETE_BLACKLIST);
        if(ret) {
            *pRetCode=ret;
            writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
            goto L_RETU;
        }
        //�㲥������
        AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,hi_cardid);
        AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,DELETE_BLACKLIST);	//��ɾ��־

        tMesList.funid = 930005;
        tMesList.pfunid = 930003;
        tMesList.max_send_cnt = 10;
        tMesList.level = MESLIST_PRIORITY_REALTIME;
        tMesList.msgtype = MESLIST_TYPE_ORDER;
        ret=AddMsgLst(&tMesList);
        if(ret) {
            *pRetCode=ret;
            writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
            goto L_RETU;
        }
    }
    //	׼�����ݲ��뽻����ˮ��
    /////////////////
    ret = SaveCancelLossSerial(&tradeserial);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    ret=GetCardMaxBlkVerNo(hi_cardid,volume);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    SetCol(handle,0);
    SetCol(handle,F_SSERIAL0,0);
    des2src(out_pack->sserial0,volume);		//���汾��
//	writelog(LOG_DEBUG,"volume:[%s]",volume);
    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
L_RETU:
    return -1;
}

