/* --------------------------------------------
 * ��������: F240005.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: ����ȷ��
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "account.h"
#include "fdsqc.h"



int F240005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_tif_tradeserial  tradeserial; //��������ˮ������������
	memset(&tradeserial,0,sizeof tradeserial);
	tradeserial.serial_no=rPack->lvol0;
	sprintf(tradeserial.reserve_1,"%d",rPack->lvol1);
	//SetCol(handle,0);
   	//SetCol(handle,F_SCLOSE_EMP,F_SORDER0,F_SORDER1,F_SSERIAL1,F_LVOL0,F_LVOL1,F_SDATE0,F_STIME0,F_SDATE1,F_STIME1,F_SCUST_NO,F_SCHANGE_EMP,F_SSERIAL0,F_LVOL2,F_SCUST_AUTH,F_SSTATUS1,F_SEMP_PWD,F_SEMP_PWD2,F_SSTATION0,F_SSTATION1,F_SORDER2,0);
	ret=DB_t_tif_tradeserial_done_flush(&tradeserial);
	if(ret)
	{
		*pRetCode=E_DB_TRADESERIAL_U;
		writelog(LOG_ERR,"���³�����ˮʧ��,errcode=[%d]",ret);
		goto L_RETU;
	}

	return 0;
L_RETU:
	return ret;
}


