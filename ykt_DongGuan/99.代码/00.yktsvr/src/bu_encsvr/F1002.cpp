/* --------------------------------------------
 * ��������: 2010-12-08
 * ��������: tc
 * �汾��Ϣ: 3.0.0.0
 * ������: 
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "bupub.h"
#include <sstream>
#include "ksbu.h"
#include "svrlink.h"


extern CSvrLink *g_pSvrLink;
extern ST_CPACK *g_RequestPack;

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int F1002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	int ret;

	ResetNormalCPack(&aPack,0,sizeof aPack);
	SetCol(handle,0);
	// ����ԭ������
	memcpy(aPack.head.ParmBits,g_RequestPack->head.ParmBits,sizeof(aPack.head.ParmBits));
	memcpy(out_pack,rPack,sizeof(ST_PACK));

	
	SetParmBit(&(aPack.head),F_SCUST_AUTH);
	SetParmBit(&(aPack.head),F_SCUST_AUTH2);
	SetParmBit(&(aPack.head),F_LVOL1);
	// TODO : ������ܻ�
	
	g_pSvrLink->SetCol(handle,aPack.head.ParmBits);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
	
}
