/* --------------------------------------------
 * ��������: F930006.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������: �´����ѱ���
 * --------------------------------------------
 * �޸�����:2004-12-14
 * �޸���Ա:	�Ž�
 * �޸�����: �޸�ҵ���߼�
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

int F930006(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
//		double dMaxFeeRatio=0;
//		int iMaxFeeRatio=0;
	int iRow=0;
    	T_t_tif_meslist tMesList;
	T_t_pif_feetype tFeeType;

	memset(&tMesList,0,sizeof(tMesList));
	memset(&tFeeType,0,sizeof(tFeeType));
//	memset(&tCuttypefee,0,sizeof(tCuttypefee));

	des2src(tMesList.devphy999_id, in_pack->sdate0);
	trim(tMesList.devphy999_id);
	if(strlen(tMesList.devphy999_id)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	tMesList.funid = iRequest;
	tMesList.level = 1;
	///////////////////////////////////////////////////
	// �޸�Ϊ��ȡ

//		ret=GetMaxFeeRatioFromShop(&dMaxFeeRatio);
//		if(ret)
//		{
//			*pRetCode=ret;
//			goto L_RETU;
//		}
//		iMaxFeeRatio=dMaxFeeRatio*100;
	ret=DB_t_pif_feetype_open_select_by_cur1();
	if(ret)
	{
		*pRetCode=E_DB_FEETYPE_R;
		goto L_RETU;
	}
	while(1)
	{
		memset(&tFeeType,0,sizeof(tFeeType));
		memset(&tMesList.incontent,0,sizeof(tMesList.incontent));
		ret=DB_t_pif_feetype_fetch_select_by_cur1(&tFeeType);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				if(iRow)
					break;
				else
				{
					*pRetCode= E_DB_FEETYPE_N;
					goto L_RETU;
				}
			}
			else
			{
				*pRetCode= E_DB_FEETYPE_R;
				goto L_RETU;
			}
		}
		iRow++;
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDTYPE,tFeeType.fee_type);	//������
		if(strncmp(tFeeType.is_outfee,TYPE_YES,1)==0)
			AddXmlItemInt(tMesList.incontent, XML_KEY_FEE, tFeeType.manage_fee);
		else
			AddXmlItemInt(tMesList.incontent, XML_KEY_FEE, 0);

		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			goto L_RETU;
		}
	}

///////////////////////////////////////////////////////////////////
/*
	//AddXmlItemInt(tMesList.incontent, XML_KEY_CARDTYPE,in_pack->lvol5);	//������
	//AddXmlItemInt(tMesList.incontent, XML_KEY_FEE, in_pack->lvol6);		//����
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
*/
	return 0;
L_RETU:
	return  -1;
}





