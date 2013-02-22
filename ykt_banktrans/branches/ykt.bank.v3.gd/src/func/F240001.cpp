/* --------------------------------------------
 * ��������: F240001.cpp
 * ��������: 2009-12-19
 * ��������: �����
 * �汾��Ϣ: 1.0.0.0
 * ������: Ȧ��ת��
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "profile.h"
#include "mypub.h"  
#include "tcp.h"
#include "cpack.h"
#include "svrlink.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "bupub.h"
#include "transinfo.h"
#include "dictionary.h"
#include "shem.h"
#include "bank.h"
#include "ksbu.h"

extern CSvrLink g_SvrLink;
#ifndef	DEBUG
	#define	DEBUG
#endif

int F240001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK bPack;				// ����Ӧ���
	ST_PACK *out_pack = &(bPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	ResetNormalCPack(&bPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack,F_LCERT_CODE, F_SNAME2, F_STX_PWD, F_SSTATION0, 0);
	
	memcpy(&(sPack.pack), rPack, sizeof(sPack.pack));
	
	writelog(LOG_INFO,"branch_no[%d], base_funcno[%d]",g_Bank.DRTP_BRANCH,g_Bank.BCC_BASEFUNCNO);

	sPack.pack.sstation0[0] = 'R';			// ��ѯ
	sPack.head.RequestType = 240021;						// ���ܺ�
	// �ȵ���̨����ѯ��ˮ��Ϣ
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	writelog(LOG_ERR,"Call %d retCode=[%d]",iRequest,ret);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		memcpy(szMsg, aPack.pack.vsmess, sizeof(aPack.pack.vsmess) -1);
		
		if (ret < 0)
		{
			writelog(LOG_ERR,"Call %d error,errcode=[%d],retCode=[%d]",iRequest,ret,aPack.head.retCode);
			*pRetCode = ret;
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call %d error,errcode=[%d],retCode=[%d]",iRequest,ret,aPack.head.retCode);
			*pRetCode = ret;
			return aPack.head.retCode;
		}
	}

	SetCol(handle,0);
	CopyHeadCol(&aPack.pack,&bPack);
//	memcpy(out_pack,&aPack.pack,sizeof(ST_PACK));
	// ��̨�Ѿ��ɹ��ˣ�˵������ת���Ѿ��ɹ���ֱ��д��
	if(aPack.pack.lvol1)
	{
		out_pack->damt0=aPack.pack.damt0;
		out_pack->damt1=aPack.pack.damt1;
		out_pack->damt2=aPack.pack.damt2;
		out_pack->lvol2=aPack.pack.lvol2;
		return 0;
	}	
	
	INNER_TRANS_REQUEST 	from_pos;
	memset(&from_pos,0,sizeof(from_pos));

	memcpy(from_pos.BankCardNo,aPack.pack.sname,sizeof from_pos.BankCardNo);			// ���п���
	sprintf(from_pos.CardNo,"%d",aPack.pack.lvol0);			// ���׿���
	sprintf(from_pos.TransMoney,"%d",aPack.pack.lvol5);		// ���׽��
	getsysdate(from_pos.TradeDate);
	getsystime(from_pos.TradeTime);
	sprintf(from_pos.TerminalId,"%d",aPack.pack.lcert_code);	// �ն˺�

	int refno=atoi(aPack.pack.sname2+8);

	// ����ת��
	ret = Bank_Transfer(&from_pos,refno);
	if(ret)
	{
		writelog(LOG_ERR,"Bank_Transfer error,errcode=[%d]",ret);
		if(E_TRANS_BANK_NOANSWER==ret)			//�������û�з��ذ������г�������
		{
			// ��Ǻ�̨��ˮΪ���д�����
			sPack.pack.sstation0[0] = 'U';			// ����
			ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, 
						  &sPack, &aPack, &ArrayPack);
			if (ret < 0||aPack.head.retCode!=0)
			{
				SetErrMsg(aPack.pack.vsmess);
				writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			}				
			return E_TRANS_BANK_NOANSWER;
		}
		else		
			return ret;
	}
	
	// ��̨��ʽ����
	memset(sPack.pack.sstation0,0,sizeof sPack.pack.sstation0);
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
		SetErrMsg(aPack.pack.vsmess);
	    return E_TRANS_INNER_TIMEOUT;
	}	
	if(aPack.head.retCode)
	{
		SetErrMsg(aPack.pack.vsmess);
		return aPack.head.retCode;
	}	
	
	SetCol(handle,0);
	CopyHeadCol(&aPack.pack,&bPack);
	memcpy(out_pack,&aPack.pack,sizeof(ST_PACK));
	
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;

}

