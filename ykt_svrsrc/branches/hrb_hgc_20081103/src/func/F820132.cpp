/* ----------------------------------------------------------
 * �������ƣ�F820132.c
 * �������ڣ�2004-8-31 09��44
 * �������ߣ���ѫ��
 * �汾��Ϣ��1.0.0.0
 * �����ܣ���������Ϣ�޸�
            ����  : int 0 ��ʾ�ɹ�����������Ϊ����ʧ��
            ����  : TRUSERID *handle ���������ݵ�ͨѶ����˱�ʶ
            ����  : ST_PACK *rPack ҵ������������
            ����  : int *iRetCode �������ķ��ش��룬0��ʾ�ɹ����������Ǵ���ʧ�ܣ��ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ0
            ����  : char *szMsg �������ķ�����Ϣ���ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ��""
 * ----------------------------------------------------------
 * �޸�����: 2004-09-08 16��20
 * �޸���Ա: ����
 * �޸�����: �޸Ĺ淶
 * �汾��Ϣ��1.0.0.1
 * ��ע��Ϣ
 */

#include "fdsqc.h"
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "errdef.h"
#include "pubdb.h"
#include "dictionary.h"
#include "cardstrut_stru.h"


int F820132(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_pif_cardstrut acardstru;
	int scode=0;
	int v_id=0;
	
	memset(&acardstru,0,sizeof(acardstru));
	        
	//��cpack��ȡ����Ӧ�ַ���
	v_id = in_pack->lvol3;
	acardstru. id		  = in_pack->lvol3;
	acardstru. phytype  = in_pack->lvol4;
	acardstru. sectorno = in_pack->lvol5;
	acardstru. blockno  = in_pack->lvol6;
	acardstru. begin_addr = in_pack->lvol7;
	acardstru. end_addr = in_pack->lvol8;
	acardstru. bytenum  = in_pack->lvol9;
	Strncpy_t(acardstru.define,(char*)in_pack->usset0,sizeof(acardstru.define));
	Strncpy_t(acardstru.comments,(char*)in_pack->usset1,sizeof(acardstru.comments));
	
	
	scode=DB_t_pif_cardstrut_update_by_id(v_id,&acardstru);
	
	if(SC_NOTFOUND==scode){
		*pRetCode=E_DB_CARDSTRUT_N;
		sprintf(szMsg,"������ṹ��Ϣ������Ӧ��¼��SQLLCODE=%d\n",scode);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,szMsg);
		goto L_Ret;
	}
	if(0!=scode)
	{
		*pRetCode=E_DB_CARDSTRUT_U;
		sprintf(szMsg,"������ṹ��Ϣ����´���SQLLCODE=%d\n",scode);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,szMsg);
		goto L_Ret;
	}
	return 0;
	
	L_Ret:
		return -1;	
}
