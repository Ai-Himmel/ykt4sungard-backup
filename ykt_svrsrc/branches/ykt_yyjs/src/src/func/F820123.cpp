/* ----------------------------------------------------------
 * �������ƣ�F820123.sqc
 * �������ڣ�2004-8-3
 * �������ߣ���ѫ�� 
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��豸������Ϣɾ��
 * ----------------------------------------------------------
 
 * �޸�����: 2004-09-08
 * �޸���Ա: �ź���
 * �޸�����: �޸Ĺ淶
 * �汾��Ϣ: 1.0.0.1
 * ��ע��Ϣ
 * ----------------------------------------------------------*/

#include "fdsqc.h"
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "errdef.h"
#include "pubdb.h"
#include "dictionary.h"
#include "phydevice_stru.h"

// ������: F820123.sqc
// ���  : ��ѫ�� 2004-8-30 09��44
// ����  : �豸������Ϣɾ��
// ����  : int 0 ��ʾ�ɹ�����������Ϊ����ʧ��
// ����  : TRUSERID *handle ���������ݵ�ͨѶ����˱�ʶ
// ����  : ST_PACK *rPack ҵ������������
// ����  : int *iRetCode �������ķ��ش��룬0��ʾ�ɹ����������Ǵ���ʧ�ܣ��ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ0
// ����  : char *szMsg �������ķ�����Ϣ���ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ��""

int F820123(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_pif_phydevice aphydev;
	int scode=0;
	int v_phytype=0;
	
	memset(&aphydev,0,sizeof(aphydev));
	
	v_phytype = in_pack->lvol6;
	aphydev.phytype = in_pack->lvol6;
	
	
	scode=DB_t_pif_phydevice_del_by_phytype(v_phytype);
	
	if(scode==SC_NOTFOUND){
		*pRetCode=E_DB_PHYDEVICE_N;
		sprintf(szMsg,"�豸����ṹ��Ϣ������Ӧ��¼��SQLLCODE=%d\n",scode);
		writelog(LOG_ERR,szMsg);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		goto L_Ret;	
	}
	if(scode!=0)
	{
		*pRetCode=E_DB_PHYDEVICE_D;
		sprintf(szMsg,"�豸����ṹ��Ϣ��ɾ������SQLLCODE=%d\n",scode);
		writelog(LOG_ERR,szMsg);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		goto L_Ret;		
	}
	return 0;
	
	L_Ret:
		return -1;
}
