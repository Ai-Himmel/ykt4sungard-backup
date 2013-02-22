/* --------------------------------------------
 * 程序名称: F240001.cpp
 * 创建日期: 2009-12-19
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存转账
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

int F240001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
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
	SetHeadCol(&sPack,F_LCERT_CODE, F_SNAME2, F_STX_PWD, F_SSTATION0, 0);
	
	memcpy(&(sPack.pack), rPack, sizeof(sPack.pack));
	
	writelog(LOG_INFO,"branch_no[%d], base_funcno[%d]",g_Bank.DRTP_BRANCH,g_Bank.BCC_BASEFUNCNO);

	sPack.pack.sstation0[0] = 'R';			// 查询
	sPack.head.RequestType = 240021;						// 功能号
	// 先调后台，查询流水信息
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
	CopyHeadCol(&aPack.pack,&bPack);
//	memcpy(out_pack,&aPack.pack,sizeof(ST_PACK));
	// 后台已经成功了，说明银行转账已经成功，直接写卡
	if(aPack.pack.lvol1)
	{
		out_pack->damt0=aPack.pack.damt0;
		out_pack->damt1=aPack.pack.damt1;
		out_pack->damt2=aPack.pack.damt2;
		out_pack->lvol2=aPack.pack.lvol2;
		return 0;
	}	
	
	INNER_TRANS_REQUEST 	from_pos;
	memset(&from_pos,0,sizeof(from_pos));

	memcpy(from_pos.BankCardNo,aPack.pack.sname,sizeof from_pos.BankCardNo);			// 银行卡号
	sprintf(from_pos.CardNo,"%d",aPack.pack.lvol0);			// 交易卡号
	sprintf(from_pos.TransMoney,"%d",aPack.pack.lvol5);		// 交易金额
	getsysdate(from_pos.TradeDate);
	getsystime(from_pos.TradeTime);
	sprintf(from_pos.TerminalId,"%d",aPack.pack.lcert_code);	// 终端号

	int refno=atoi(aPack.pack.sname2+8);

	// 银行转账
	ret = Bank_Transfer(&from_pos,refno);
	if(ret)
	{
		writelog(LOG_ERR,"Bank_Transfer error,errcode=[%d]",ret);
		if(E_TRANS_BANK_NOANSWER==ret)			//如果银行没有返回包，进行冲正处理
		{
			// 标记后台流水为银行待冲正
			sPack.pack.sstation0[0] = 'U';			// 更新
			ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, 
						  &sPack, &aPack, &ArrayPack);
			if (ret < 0||aPack.head.retCode!=0)
			{
				SetErrMsg(aPack.pack.vsmess);
				writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			}				
			return E_TRANS_BANK_NOANSWER;
		}
		else		
			return ret;
	}
	
	// 后台正式入账
	memset(sPack.pack.sstation0,0,sizeof sPack.pack.sstation0);
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
		SetErrMsg(aPack.pack.vsmess);
	    return E_TRANS_INNER_TIMEOUT;
	}	
	if(aPack.head.retCode)
	{
		SetErrMsg(aPack.pack.vsmess);
		return aPack.head.retCode;
	}	
	
	SetCol(handle,0);
	CopyHeadCol(&aPack.pack,&bPack);
	memcpy(out_pack,&aPack.pack,sizeof(ST_PACK));
	
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;

}

