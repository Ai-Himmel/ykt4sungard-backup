 /* --------------------------------------------
  * ��������: 2008-05-28
  * ��������: �Ž�
  * �汾��Ϣ: 1.0.0.0
  * ������: �ͻ�����޸�
  * --------------------------------------------
  * �޸�����:
  * �޸���Ա:
  * �޸�����:
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
#include "busqc.h"

int F843375(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int	cuttype=0;						//�ͻ�������
	char cuttypename[60+1]="";			//�ͻ��������
	int	feetype=0;
	char sqlcmd[2048]="";
	cuttype=rPack->lvol0;	
	feetype=rPack->lvol5;
	des2src(cuttypename,rPack->scard0);	
	strcpy(sqlcmd,"update ykt_cur.t_cuttype set  ");
	if(strlen(cuttypename))
		sprintf(sqlcmd+strlen(sqlcmd)," cuttypename='%s',",cuttypename);
	if(feetype)
		sprintf(sqlcmd+strlen(sqlcmd)," feetype=%d,",feetype);
	sqlcmd[strlen(sqlcmd)-1]=0x20; 
	sprintf(sqlcmd+strlen(sqlcmd)," where cuttype=%d ",cuttype);
	ret=DynamicStmtExecute(sqlcmd);
	if(ret)
	{
		writelog(LOG_ERR,"sql:[%s]",sqlcmd);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_CUTTYPEFEE_N;
		else
			*pRetCode=E_DB_CUTTYPEFEE_U;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
