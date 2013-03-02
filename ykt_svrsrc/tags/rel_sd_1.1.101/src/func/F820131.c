/* ----------------------------------------------------------
 * �������ƣ�F820131.c
 * �������ڣ�2004-8-31 09��44
 * �������ߣ���ѫ��
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�������ṹ��Ϣ����
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


int F820131(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_pif_cardstrut acardstru;
	double dUniqNo=0;
	int scode=0;
	
	memset(&acardstru,0,sizeof(acardstru));
	        
	//��cpack��ȡ����Ӧ�ַ���
	acardstru. phytype  = in_pack->lvol4;
	acardstru. sectorno = in_pack->lvol5;
	acardstru. blockno  = in_pack->lvol6;
	acardstru. begin_addr = in_pack->lvol7;
	acardstru. end_addr = in_pack->lvol8;
	acardstru. bytenum  = in_pack->lvol9;
	Strncpy_t(acardstru.define,in_pack->usset0,sizeof(acardstru.define));
	Strncpy_t(acardstru.comments,in_pack->usset1,sizeof(acardstru.comments));
	//�豸��־��ϵͳ��ֵ����ȡ��
	scode=getNewUniqNo(KEYTYPE_CARD_STRU,&dUniqNo);
	if(0 != scode)
	{
		*pRetCode=E_DB_SYSKEY_R;
		sprintf(szMsg,"820121��ȡϵͳ��ֵ�����RetCode=%d\n",scode);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,szMsg);
		goto L_Ret;
	}
	//��ȷ����ֵ���ṹ��
	acardstru.id = (int)dUniqNo;
	
	scode=DB_t_pif_cardstrut_add(&acardstru); 
	
	if(0 != scode)
	{
		*pRetCode=E_DB_CARDSTRUT_I;
		sprintf(szMsg,"���ṹ��Ϣ��������SQLLCODE=%d\n",scode);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,szMsg);
		goto L_Ret;		
	}
	return 0;
L_Ret:
	return -1;
}
