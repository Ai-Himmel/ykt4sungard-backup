/* --------------------------------------------
 * 程序名称: F249999.cpp
 * 创建日期: 2007-11-21
 * 程序作者: 李翔
 * 版本信息: 1.0.0.0
 * 程序功能: 测试程序, 通过通讯平台从bank后台
 *           跳转到主干后台
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

int F249999(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	
	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK bPack;				// 设置应答包
	ST_PACK *out_pack = &(bPack.pack);
	ST_CPACK sPack;			 	// 设置发送包

	ResetNormalCPack(&aPack, 0, 1);
	ResetNormalCPack(&bPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = iRequest;						// 功能号
	//SetHeadCol(&sPack, F_SCLOSE_EMP, F_SORDER2, F_SSERIAL0, F_SEMP_PWD, F_DAMT0, F_LVOL3, 0);
	//unsigned char *pb;
   	//pb = g_SvrLink.head.ParmBits;
   	//g_SvrLink.SetCol(handle,pb);
	//memcpy(sPack.head.ParmBits,g_SvrLink.head.ParmBits,sizeof(sPack.head.ParmBits));
	CopyHeadCol(rPack,&sPack);
	memcpy(&(sPack.pack), rPack, sizeof(sPack.pack));

	// 圈存转账，校验银行是否在服务时间
	if(iRequest ==240020)			
	{
		if(Is_out_of_service())
			{
				sprintf(szMsg,"不在银行服务时间");			
				return E_TRANS_BANK_SERVICE_NOEXIT;
			}
	}
		
	writelog(LOG_ERR,"branch_no[%d], base_funcno[%d]",g_Bank.DRTP_BRANCH,g_Bank.BCC_BASEFUNCNO);
	
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
	//SetCol(handle,F_LVOL0,F_LVOL1,F_DAMT0,F_DAMT1,F_DAMT2,F_DAMT10,F_DAMT11,F_DAMT12,F_VSMESS,0);
	//memcpy(g_SvrLink.head.ParmBits,aPack.head.ParmBits,sizeof(g_SvrLink.head.ParmBits));
   //pb = aPack.head.ParmBits;
   //g_SvrLink.SetCol(handle,pb);
	CopyHeadCol(&aPack.pack,&bPack);
	memcpy(out_pack,&aPack.pack,sizeof(ST_PACK));
	
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;

}

