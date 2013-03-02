/* --------------------------------------------
 * 程序名称: F843336.sqc
 * 创建日期: 2004-12-13
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:商户信息删除(销户)
 * --------------------------------------------
 * 修改日期: 
 * 修改人员: 
 * 修改描述: 
 * 版本信息: 
 * 备注信息: 
 * --------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "fdsqc.h"

int F843336(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char sysdate[11]="";
	char systime[9]="";
	char  logicdate[11]="";         	//更新日期
	int	shop_id=0;                    	//商户标识
	double dUniqno=0;
	T_t_cif_shop	tShop;
	T_t_cif_customer  tCustomer;
	T_t_aif_account	tAccount;
	T_t_tif_tradeserial  tradeserial;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	int ret=0;

	memset(&tShop,0,sizeof(tShop));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	ResetNormalCPack(&aPack,0,1);
	
#ifdef DEBUG
	writelog(LOG_DEBUG,"shop_id        :lvol5          [%d]",rPack->lvol5);
#endif

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);		//业务日期
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	shop_id=rPack->lvol5;
	if(shop_id<1)
	{
		*pRetCode= E_SHP_ID_NOT_EXIST;
		goto L_RETU;
	}
	ret=DB_t_cif_shop_read_lock_by_cur1_and_shop_id(shop_id,&tShop);
	if(ret)
	{
		writelog(LOG_ERR,"shop_id[%d]",shop_id);
		if(DB_NOTFOUND==ret)	
			*pRetCode= E_SHP_ID_NOT_EXIST;
		else
			*pRetCode= E_DB_SHOP_R;
		goto L_RETU;
	}
	//判断是否为叶结点
	if(strncmp(tShop.is_leaf,TYPE_YES,1)==0)
	{
		//先判断有无设备
		ret=IsExistDeviceByShopId(shop_id,logicdate);
		if(ret)
		{
			DB_t_cif_shop_free_lock_cur1();
			*pRetCode= ret;
			goto L_RETU;
		}
	}
	else
	{
		//如果有下级节点不能删除
		ret=IsExistSubNodeByShpId(shop_id);
		if(ret)
		{
			DB_t_cif_shop_free_lock_cur1();
			*pRetCode= ret;
			goto L_RETU;
		}	
	}
	tShop.shop_state=SHOPSTAT_LOGOUT;
	des2src(tShop.can_time,logicdate);				//注销日期
	ret=DB_t_cif_shop_update_lock_by_cur1(&tShop);
	if(ret)
	{
		writelog(LOG_ERR,"shop_id[%d]",shop_id);
		if(DB_NOTFOUND==ret)	
			*pRetCode= E_SHP_ID_NOT_EXIST;
		else
			*pRetCode= E_DB_SHOP_U;
		goto L_RETU;
	}
	DB_t_cif_shop_free_lock_cur1();
	//注销客户
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tShop.cut_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tShop.cut_id);
		if(DB_NOTFOUND==ret)	
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	tCustomer.cut_state=CUSTSTAT_LOGOUT;
	des2src(tCustomer.can_time,logicdate);
	ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tShop.cut_id);
		if(DB_NOTFOUND==ret)	
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_U;
		goto L_RETU;
	}
	DB_t_cif_customer_free_lock_cur();
	//如果是叶结点则注销帐户
	if(strncmp(tShop.is_leaf,TYPE_YES,1)==0)
	{
		//注销帐户
		ret=DB_t_aif_account_read_lock_by_c5_and_customer_id_and_act_type(tShop.cut_id, ACCTYPE_SHOPMAIN, &tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"tShop.cut_id[%d]",tShop.cut_id);
			if(DB_NOTFOUND==ret)
			
				*pRetCode=E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode=E_DB_ACCOUNT_R;
			goto L_RETU;
		}
		if(amtcmp(tAccount.cur_bala,0)>0)
		{
			DB_t_aif_account_free_lock_c5();
			writelog(LOG_ERR,"tAccount.cur_bala[%d]",tAccount.cur_bala);
			*pRetCode=E_SHP_ACC_NO_RECKONING;
			goto L_RETU;
		}
		tAccount.current_state=ACCOUNTSTAT_LOGOUT;
		des2src(tAccount.close_date,logicdate);
		getsystime(tAccount.close_time);
		ret=DB_t_aif_account_update_lock_by_c5(&tAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode=E_ACTNO_NOT_EXIST;
			else
				*pRetCode=E_DB_ACCOUNT_U;
			goto L_RETU;
		}
		DB_t_aif_account_free_lock_c5();
		ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  						//获得最大流水号
		if(ret)
		{
			*pRetCode = ret;
			writelog(LOG_ERR,"ret [%d]",ret);
			goto L_RETU;
		}
		des2src(tradeserial.oper_code,rPack->scust_limit);							//操作员号
		tradeserial.maindevice_id=rPack->lvol10;										//工作站
		tradeserial.serial_no = (int)dUniqno;											//流水号
		tradeserial.other_seri_no = 0;														//上传端流水号
		tradeserial.serial_type = TXCODE_SHOP_LOGOUT;											//交易代码；备注：发卡+充值 用一个交易码，即847101； 发卡（不充值）另用一个交易码，即新的发卡程序文件名，从而区分发卡充值与发卡不充值的卡操作信息。
		tradeserial.serial_state = SERISTAT_DEBT;												//流水状态
		des2src(tradeserial.operate_date,sysdate);											//发生日期
		des2src(tradeserial.operate_time,systime);											//发生时间
		des2src(tradeserial.collect_date,sysdate);												//采集日期
		des2src(tradeserial.collect_time,systime);												//采集时间
		des2src(tradeserial.enteract_date,logicdate);											//处理日期
		des2src(tradeserial.enteract_time,systime);											//处理时间
		tradeserial.maindevice_id = rPack->lvol6;												//上传工作站标识
		tradeserial.device_id = rPack->lvol7;													//采集设备标识	
		tradeserial.customer_id=tAccount.customer_id;											//客户号
		//	插入交易流水表
		ret = DB_t_tif_tradeserial_add(&tradeserial);
		if (ret)
		{
			writelog(LOG_ERR,"ret[%d]",ret);
			if(DB_REPEAT==ret)
				*pRetCode = E_DB_TRADESERIAL_E;
			else
				*pRetCode = E_DB_TRADESERIAL_I;
			goto L_RETU;
		}
	}
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,0);
	out_pack->lvol0=tShop.shop_id;
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
