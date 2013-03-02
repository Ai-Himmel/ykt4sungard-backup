/* --------------------------------------------
 * ��������: 2009-5-7
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: һ��ͨ���� mac
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
#include "busqc.h"
#include "acctrans.h"


int F846313(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	cpu_trade_t cpu_trade;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);	

	ResetNormalCPack(&aPack,0,1);
		
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_SSTOCK_CODE2,F_LSERIAL1,F_SEMAIL,0);

	
	memset(&cpu_trade,0,sizeof cpu_trade);

	cpu_trade.trade_type=rPack->lsafe_level;
	des2src(cpu_trade.random_key,rPack->sstock_code);
	des2src(cpu_trade.cardphyid,rPack->sstation1);
	cpu_trade.tradeamt = rPack->lvol1;
	cpu_trade.tradecnt = rPack->lvol6; // �����ǽ���ǰ����
	cpu_trade.balance = rPack->lvol7;
	cpu_trade.termsno = rPack->lserial0;
	des2src(cpu_trade.termno,rPack->sserial0); // �ն˺�
	strncpy(cpu_trade.tx_datetime,rPack->sdate0,8);
	strncpy(cpu_trade.tx_datetime+8,rPack->stime0,6);
	des2src(outPack->sstock_code2,rPack->sstock_code2); // MAC1,ֻ���ƶ��淶��ʹ��

	// ����� MAC2 
	if(rPack->lvol5 == 2)
	{
		ret = calc_cpucard_mac(&cpu_trade,outPack->semail,rPack->lvol5);
	}
	else
	{
		ret = calc_cpucard_mac(&cpu_trade,outPack->sstock_code2,rPack->lvol5);	
	}
		
	if(ret)
	{
		writelog(LOG_ERR,"doCheckMac err[%d]",ret);
		return ret;
	}
	outPack->lvol0 = rPack->lvol0; //���׿���
	outPack->lserial1=rPack->lserial1; // ������ˮ��
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
	
}

