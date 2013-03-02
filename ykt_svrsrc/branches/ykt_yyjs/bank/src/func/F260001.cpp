/* ----------------------------------------------------------
 * 程序名称：F260001.cpp
 * 创建日期：2007-08-09
 * 程序作者：李翔
 * 版本信息：1.0.0.0
 * 程序功能：水控转帐功能
 * ----------------------------------------------------------*/

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

extern CSvrLink g_SvrLink;
#ifndef	DEBUG
	#define	DEBUG
#endif

int F260001(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char card_pwd[6 + 1] = "";
	
	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// 设置发送包

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	des2src(card_pwd,in_pack->semp_pwd);
/*
	ret = device_login_yes_or_no(in_pack->lvol4);
	if (ret)
	{	
		if (ret < 0)
		{
			writelog(LOG_ERR,"device_login_yes_or_no faild,=[%d]",in_pack->lvol4);
			strcpy(szMsg,"校园端网络错误");
			goto L_retu;
		}
		else
		{
			writelog(LOG_INFO,"Device has not signed in!device_id=[%d],background ret=[%d]",in_pack->lvol4,ret);
			strcpy(szMsg,"终端设备未登录");
			goto L_retu;
		}
	}
*/	
	//判断输入密码是否正确
	ret = verify_card_password(in_pack->lvol0, "", 0, card_pwd);
	if (ret)
	{
		writelog(LOG_INFO,"verify_card_password err!card_id[%d],[%s]",in_pack->lvol0,aPack.pack.vsmess);
		strcpy(szMsg,"密码验证失败");
		goto L_retu;
	}
	
	//向后台发水控转账
	ResetNormalCPack(&sPack, 0, 1);
	if (SERISTAT_NODEBT == in_pack->lvol9)
		sPack.head.RequestType = 847316;
	else
		sPack.head.RequestType = 847317;

	SetHeadCol(&sPack, F_LCERT_CODE, F_LVOL0, F_LVOL1, F_LVOL2, F_LVOL4, F_DAMT0, F_DAMT1, 
	F_SEMP_PWD, F_SCUST_NO, F_SCUST_LIMIT, F_SPHONE, F_LVOL6, F_LVOL7, 0);       // 设置发送windows BU的头部视图信息

	memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));

	//writelog(LOG_ERR,"branch_no[%d], base_funcno[%d]",g_Bank.DRTP_BRANCH,g_Bank.BCC_BASEFUNCNO);
	//测试一下手机充值
	//sPack.pack.damt1=1;
	///////////////////
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		if (ret < 0)
		{
			writelog(LOG_ERR,"Call 847316 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			strcpy(szMsg,"校园端网络故障");
			goto L_retu;
		}
		else
		{
			writelog(LOG_ERR,"Call 847316 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			strcpy(szMsg,aPack.pack.vsmess);
			goto L_retu;
		}
	}
	
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_DAMT0,F_DAMT1,F_DAMT2,F_DAMT10,F_DAMT11,F_DAMT12,F_VSMESS,0);
	//writelog(LOG_DEBUG,"damt0=[%f],damt1=[%f]",out_pack->damt0,out_pack->damt1);
	PutRow(handle, out_pack, pRetCode, szMsg);
	
	return 0;
L_retu:

	*pRetCode=ret;
	return -1;
}
