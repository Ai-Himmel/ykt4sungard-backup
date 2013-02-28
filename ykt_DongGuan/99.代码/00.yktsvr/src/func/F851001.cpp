/* --------------------------------------------
 * 创建日期: 2011-03-08
 * 程序作者: 聂龙海
 * 版本信息: 1.0.0.0
 * 程序功能: 商户代理充值
 * --------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>	
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "errdef.h"
#include "dbfunc.h"
#include "busqc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "transfunc.h"
#include "checkcardstatus.h"
#include "cardprocess.h"

using namespace std;

int F851001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
/*
	// 充值入账
	//ret = F846801(*handle,iRequest,rPack,pRetCode,szMsg);
	if(ret)
	{
		return ret;
	}
*/
	CAccTrans& ats=CAccTrans::GetInst();

	// 读取商户表
	T_t_merch t_merch;
	memset(&t_merch,0,sizeof(t_merch));
	
	ret=DB_t_merch_read_by_merchid(rPack->lvol0,&t_merch);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCH_N;
		else
			return E_DB_MERCH_R;
	}

	// 充值商户参数表
	T_t_merchpara t_merchpara ;
	memset(&t_merchpara,0,sizeof(t_merchpara));

	ret = DB_t_merchpara_read_by_merchid(rPack->lvol0, &t_merchpara);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCHPARA_N;
		else
			return E_DB_MERCHPARA_R;
	}

	if(t_merchpara.status!=1)
	{
		return E_DB_MERCHPARA_NG;
	}

	// 读取充值商户工作表
	T_t_merchwork t_merchwork ;
	memset(&t_merchwork,0,sizeof(t_merchwork));

	ret=DB_t_merchwork_read_lock_by_c0_and_merchid(rPack->lvol0,&t_merchwork);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_MERCHWORK_N;
		else
			return E_DB_MERCHWORK_R;
	}

	// 服务时间检查
	char strHosttime[7] = {0};
	getsystime(strHosttime);
	int iHosttime = atoi(strHosttime);
	
	if( iHosttime > t_merchpara.closetime || iHosttime < t_merchpara.opentime)
	{
		return E_DB_MERCHPARA_NG;
	}

	int depositamt = rPack->lvol1;

	// 充值额度检查
	int new_chamt = t_merchwork.czamt - depositamt;
	if( t_merchpara.czamtmax + new_chamt < 0 )
	{
		return E_DB_MERCHWORK_MAX;
	}

	// 更新充值总金额
	t_merchwork.czamt = new_chamt;

	ret = DB_t_merchwork_update_lock_by_c0(&t_merchwork);
	if(ret)
	{
		return E_DB_MERCHWORK_U;
	}

	// 返回信息
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0, F_LVOL1, F_LVOL2, F_LVOL3 ,F_LVOL4, F_LVOL5,F_LVOL6, F_SBANKNAME, F_SCERT_NO, F_VSMESS,0);


	sprintf(outPack->vsmess,"商户[%s]充值%.2lf元 账户余额%.2lf元 最大额度%.2lf元 可用额度%.2lf元",
		t_merch.merchname,
		depositamt/100.0, 
		t_merchwork.czamt/100.0,
		t_merchpara.czamtmax/100.0,
		(t_merchpara.czamtmax + t_merchwork.czamt)/100.0);

	return 0;
}

