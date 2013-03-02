/** 
 * ģ���� ��������ѯ�ཻ��
 * �ļ��� F847319.cpp
 * �ļ�ʵ�ֹ���
 * ���� 
 * �汾
 * ���� 2008-09-10
 * ��ע
 * $Id$
 */

#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "pubfunc.h"
#include "fdsqc.h"
#include "ext_consumer.h"
#include "bupub.h"
#include "svrlink.h"
#include "callbu.h"

typedef struct {
	int tx_code;
	int (* do_func)(ST_PACK *in_pack,ST_PACK *out_pack,int *pRetCode,char *szMsg);
}query_func_def_t;

static int do_query_240204(ST_PACK *in_pack,ST_PACK *out_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;	
	char c_drtbranch[10]="";
	char c_bccbasefuncno[10]="";
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;

	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�


	ret=GetParameter(2501, c_drtbranch);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2502, c_bccbasefuncno);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}

	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_SCUST_AUTH,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	sPack.head.RequestType = 847358;
	sPack.pack.lvol0=in_pack->lvol10;//�����
	
	ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, 10, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 847358 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			*pRetCode = aPack.head.retCode;
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 847358 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			strcpy(szMsg,aPack.pack.vsmess); // ������Ϣ
			*pRetCode = aPack.head.retCode;
			return -1;
		}
	}
	
	memcpy(out_pack->sbankname,aPack.pack.sbankname,81);//��������
	out_pack->damt2=aPack.pack.damt0;//���
	out_pack->damt1=aPack.pack.damt1;//�������
	writelog(LOG_ERR,"sbankname=[%s]",out_pack->sbankname);
	return 0;

}

static query_func_def_t g_query_func[] = {
	{240204,do_query_240204},
	{-1,NULL}
};

int F847319(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret,i;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&aPack,0,sizeof aPack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
   	SetCol(handle,F_LVOL0,F_LVOL1,F_DAMT0,F_DAMT1,F_DAMT2,F_SBANKNAME,F_SADDR,F_VSMESS,0);
	i = 0;
	while(g_query_func[i].tx_code != -1)
	{
		if(g_query_func[i].tx_code == in_pack->lcert_code)
		{
			// 
			ret = g_query_func[i].do_func(in_pack,out_pack,pRetCode,szMsg);
			if(ret)
			{
				writelog(LOG_ERR,"��������[%d]ʧ��errcode[%d]",in_pack->lcert_code,*pRetCode);
				return ret;
			}
			PutRow(handle,out_pack,pRetCode,szMsg);
			return 0;
		}
		i++;
	}
	*pRetCode = E_INPUT_DATA_INVAILD;
	return -1;
}

