/* --------------------------------------------
 * ��������: F930203.sqc
 * ��������: 2007-04-23
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: �ɼ��Ž���ˮ���¼�
 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "busqc.h"
#include "dbfunc_foo.h"

static int ConverPhyNo(char *physical_no_hex, char *physical_no_dec)
{
	char tmp[8+1] = "";
	int i = 0;
	char a1[3] = "";
	char a2[3] = "";
	char a3[3] = "";
	char a4[3] = "";

	memcpy(a1, physical_no_hex, 2);
	memcpy(a2, physical_no_hex + 2, 2);
	memcpy(a3, physical_no_hex + 4, 2);
	memcpy(a4, physical_no_hex + 6, 2);

	sprintf(tmp, "%s%s%s%s", a4, a3, a2, a1);
	sscanf(tmp, "%8X", &i);
	sprintf(physical_no_dec, "%d", i);
	return 0;
}


int F930203(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	T_t_doordtl tDoordtl;
	T_t_card tCard;
	T_t_device device;
	T_t_dooreventdtl event;
	T_t_customer tCust;
	int ret;
	char weigand_no[12+1] = "";
	memset(&device, 0, sizeof device);

	writelog(LOG_INFO, "F930203,device[=%d]parent_id=[%d],dev_no=[%d],cardno=[%d],phycarid=[%s],ret=[%d]",
		         in_pack->lvol5, in_pack->lvol2, in_pack->lvol1,in_pack->lvol0,in_pack->sdate1,ret);
	// ��ѯ�豸ID��
	if (in_pack->lvol5 > 0)
	{
		ret = DB_t_device_read_by_deviceid(in_pack->lvol5, &device);
	}
	else
	{
		// ���ж��ǲ����и��豸ID
		if (in_pack->lvol2 > 0)
			ret = get_door_dev_by_parent_and_termid(&device, in_pack->lvol2
			                                        , in_pack->lvol1); // ͨ�����Ų�ѯ
		else
		{
			// �жϸ��豸����
			if (in_pack->lvol3 > 0)
				ret = find_device_by_parent_termid(&device, in_pack->lvol3, in_pack->lvol1
				                                   , in_pack->lserial0); // ͨ�����豸�������豸���Ų�ѯ
			else
			{
				// ͨ����ϵͳ�����豸���Ų�ѯ
				ret = find_device_by_devinfo(&device, in_pack->lcert_code, in_pack->lvol1
				                             , in_pack->sbank_code, in_pack->lserial0);
			}
		}
	}
	if (ret)
	{
		writelog(LOG_ERR, "get_door_dev_by_parent_and_termid err,device[=%d]parent_id=[%d],dev_no=[%d],ret=[%d]",
		         in_pack->lvol5, in_pack->lvol2, in_pack->lvol1, ret);
		if (ret == E_DB_DEVICE_N)
		{
			writelog(LOG_ERR, "�ϴ���¼�Ҳ�����Ӧ���豸termid[%d]type[%s]parent[%d][%d],sys[%d],phytype[%d]"
			         , in_pack->lvol1, in_pack->sbank_code, in_pack->lvol2, in_pack->lvol3, in_pack->lcert_code, in_pack->lserial0);
			return 0;
		}
		else
		{
			*pRetCode = ret;
			goto L_RETU;
		}
	}
	// û��������,Ҳû�н��׿���
	if ((strlen(in_pack->sdate1) == 0) && in_pack->lvol0 == 0)
	{
		//�¼�
		memset(&event, 0, sizeof event);
		event.deviceid = device.deviceid;
		event.eventcode = atoi(in_pack->semp_no);
		des2src(event.eventmsg, in_pack->vsmess);
		event.sysid= in_pack->lcert_code;
		des2src(event.transdate, in_pack->sdate0);
		des2src(event.transtime, in_pack->stime0);
		getsysdate(event.coldate);
		getsystime(event.coltime);
		ret = DB_t_dooreventdtl_add(&event);
		if (ret)
		{
			if (DB_REPEAT == ret)	
				return 0;
			return E_DB_DOOREVENTDTL_I;
		}
		return 0;

	}
	else
	{
		memset(&tCard, 0, sizeof tCard);

		if(strlen(in_pack->sdate1) >0)		// ��������
		{
			ret = get_card_by_phyno(&tCard, in_pack->sdate1);
			if (ret)
			{
				if (ret == E_DB_CARD_N)
				{
					ConverPhyNo(in_pack->sdate1, weigand_no);
					ret = get_card_by_weigand_no(&tCard, weigand_no);
					if (ret)
					{
						writelog(LOG_ERR, "Get_card_by_weigand_no err,weigand_no=[%s],ret=[%d]", weigand_no, ret);
						// û�����ſ�,��Ȼ������ˮ
						if (ret != E_DB_CARD_N)
						{
							*pRetCode = ret;
							goto L_RETU;
						}
					}
				}
				else
				{
					*pRetCode = ret;
					goto L_RETU;
				}
			}
		}
		else		// ���ݽ��׿��Ų�ѯ
		{
			ret = DB_t_card_read_by_cardno(in_pack->lvol0, &tCard);
			if(ret)
			{
				*pRetCode = E_DB_CARD_R;
				goto L_RETU;		
			}				
		}
		memset(&tDoordtl, 0, sizeof tDoordtl);
		tDoordtl.deviceid = device.deviceid;
		des2src(tDoordtl.devphyid,device.devphyid);
		writelog(LOG_DEBUG,"deviceid[%d],devphyid[%s]",device.deviceid,device.devphyid);
		tDoordtl.cardno = tCard.cardno;
		tDoordtl.sysid = in_pack->lcert_code;
		tDoordtl.custid = tCard.custid;
		
		if (!ret)	
			des2src(tDoordtl.cardphyid, tCard.cardphyid);
		else 
			des2src(tDoordtl.cardphyid, in_pack->sdate1);

		if(tDoordtl.custid)
		{
			memset(&tCust,0,sizeof tCust);
			ret = DB_t_customer_read_by_custid(tDoordtl.custid, &tCust);
			if(ret )
			{
				if(ret != DB_NOTFOUND)
					return E_DB_CUSTOMER_R;
			}
			else
			{
				des2src(tDoordtl.stuempno,tCust.stuempno);
				des2src(tDoordtl.custname,tCust.custname);
			}			
		}
		//writelog(LOG_DEBUG,"door serial date[%s] time[%s]",in_pack->sdate0,in_pack->stime0);
		des2src(tDoordtl.transdate, in_pack->sdate0);
		des2src(tDoordtl.transtime, in_pack->stime0);
		getsysdate(tDoordtl.coldate);
		getsystime(tDoordtl.coltime);
		tDoordtl.transmark = atoi(in_pack->semp_no);
		ret = getNewUniqNo(KEYTYPE_DOORDTL,&(tDoordtl.devseqno));
		if(ret)
		{
			writelog(LOG_ERR,"������ˮ��ʧ��");
			*pRetCode = ret;
			goto L_RETU;		
		}
		// �����Ž���ˮ
		ret = DB_t_doordtl_add(&tDoordtl);
		if (ret)
		{
			// �ظ���ˮ����
			if (DB_REPEAT == ret)
			{
				writelog(LOG_DEBUG, "��ˮ�ظ�card[%s],date[%s],time[%s]", in_pack->sdate1
				         , in_pack->sdate0, in_pack->stime0);
				return 0;
			}
			writelog(LOG_ERR, "������ˮʧ��card[%s],date[%s],time[%s]", in_pack->sdate1
			         , in_pack->sdate0, in_pack->stime0);
			*pRetCode = E_DB_DOOREVENTDTL_I;
			goto L_RETU;
		}
		
		switch (device.devusage)
		{
		case DU_JSB_CONFRENCE:
			/*
			ret = SaveDoorJSBSerial(&tDoordtl);
			if(ret)
			{
				writelog(LOG_ERR,"�����ʱ����ˮʧ��,errcode[%d]",ret);
				break;
			}
			ret = UpdateConferSerial(&tDoordtl);
			*/
//			break;
		case DU_JSB_ATTENDANCE:
//			ret = SaveKQSerial(&tDoordtl);
//			if (ret)
//			{
//				writelog(LOG_ERR, "���뿼����ˮ��ʧ��,errcode[%d]", ret);
//				break;
//			}
		default:
			//ret = SaveDoorJSBSerial(&tDoordtl);
			/*
			ret = SaveDoorDtl(&tDoordtl);
			if (ret)
			{
				writelog(LOG_ERR, "���뿼����ˮ��ʧ��,errcode[%d]", ret);
				break;
			}
			*/
			break;
		}
		if (ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
	}
	return 0;

L_RETU:
	return -1;

}

