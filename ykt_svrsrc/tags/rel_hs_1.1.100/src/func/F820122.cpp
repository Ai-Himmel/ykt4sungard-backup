/* ----------------------------------------------------------
 * �������ƣ�F820004.sqc
 * �������ڣ�2004-8-3
 * �������ߣ���ѫ�� 
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��豸������Ϣ�޸�
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

// ������: F820122.sqc
// ���  : ��ѫ�� 2004-8-30 09��44
// ����  : �豸������Ϣ�޸�
// ����  : int 0 ��ʾ�ɹ�����������Ϊ����ʧ��
// ����  : TRUSERID *handle ���������ݵ�ͨѶ����˱�ʶ
// ����  : ST_PACK *rPack ҵ������������
// ����  : int *iRetCode �������ķ��ش��룬0��ʾ�ɹ����������Ǵ���ʧ�ܣ��ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ0
// ����  : char *szMsg �������ķ�����Ϣ���ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ��""

int F820122(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_pif_phydevice aphydev;
	int ret=0;
	int v_phytype=0;
	
	memset(&aphydev,0,sizeof(aphydev));
	
	v_phytype = in_pack->lvol6;
	aphydev.phytype = in_pack->lvol6;
	Strncpy_t(aphydev.dname,in_pack->sphone,sizeof(aphydev.dname));
	Strncpy_t(aphydev.dtype,in_pack->spager,sizeof(aphydev.dtype));
	Strncpy_t(aphydev.factory,in_pack->scert_no,sizeof(aphydev.factory));
	Strncpy_t(aphydev.comments,(char*)in_pack->usset1,sizeof(aphydev.comments));
	
	ret=DB_t_pif_phydevice_update_by_phytype(v_phytype,&aphydev);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode=E_DB_PHYDEVICE_N;
		else
			*pRetCode=E_DB_PHYDEVICE_U;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;	
}
