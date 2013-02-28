/* --------------------------------------------
 * 创建日期: 2011-03-08
 * 程序作者: 聂龙海
 * 版本信息: 1.0.0.0
 * 程序功能: 商户搭伙费分成表(T_SHOPBOARDFEE)查询，插入，删除
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
 #include "errdef.h"
 #include "dbfunc.h"
 #include "busqc.h"
 #include "dbfunc_foo.h"


int F851004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	// 参数检查
	if(rPack->lvol0<=0)
	{
		return E_INPUT_DATA_INVAILD;
	}

	// 读取商户表
	T_t_merch t_merch;
	memset(&t_merch,0,sizeof(t_merch));
	
	int ret=DB_t_merch_read_by_merchid(rPack->lvol0,&t_merch);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCH_N;
		else
			return E_DB_MERCH_R;
	}

	// 读取充值商户参数表
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

	// 读取充值商户工作表
	T_t_merchwork t_merchwork ;
	memset(&t_merchwork,0,sizeof(t_merchwork));

	ret=DB_t_merchwork_read_by_merchid(rPack->lvol0,&t_merchwork);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCHWORK_N;
		else
			return E_DB_MERCHWORK_R;
	}

 	// 返回信息
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0, F_LVOL1, F_LVOL2, F_LVOL3, F_LVOL4, F_LVOL5, F_LVOL6, F_SBANKNAME,0);
	
	outPack->lvol0 = rPack->lvol0;//充值商户编号
	outPack->lvol1 = t_merchpara.czamtmax;//商户的最大充值额度
	outPack->lvol2 = t_merchwork.czamt;//当前余额
	outPack->lvol3 = t_merchpara.czamtmax + t_merchwork.czamt;//可用额度
	outPack->lvol4 = t_merchwork.czamt < 0 ? -t_merchwork.czamt:0; // 当前应交款
	outPack->lvol5 = t_merchpara.paydate;//最后缴款日期 
	outPack->lvol6 = t_merchpara.billdate;//每月商户账单日
	des2src(outPack->sbankname,t_merch.merchname); // 商户名

 	PutRow(handle,outPack,pRetCode,szMsg); 
	AnswerData(handle,*pRetCode,szMsg);
	return 0;
}


