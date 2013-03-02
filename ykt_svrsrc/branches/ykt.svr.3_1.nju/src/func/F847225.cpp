/* --------------------------------------------
 * 程序名称: F847225.sqc
 * 创建日期: 2006-10-25
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  充值平台检测卡状态
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "acctrans.h"
#include "busqc.h"
#include "dbfunc_foo.h"

int F847225(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	/*
	int cardno = 0;
	char card_phy_id[9] = "";
	// 客户号
	int custid = 0;
	// 未发卡的状态
	int card_state = 0;
	// 发卡业务请求功能号
	int trade_request = 0;
	double paymoney = 0;
	int lost_cardno = 0;
	T_tab_card_info sync_card;
	T_t_card card_info;
	T_t_customer customer;
	T_t_aif_account account;

	ST_CPACK aPack;
	ST_PACK * out_pack = &(aPack.pack);
	int ret;

	memset(&aPack,0,sizeof aPack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_DAMT0,F_VSMESS,F_LVOL1,F_SEMAIL,F_SCUST_AUTH
		,F_SDATE0,F_LVOL2,F_LVOL3,F_SBANK_ACC,F_LVOL4,0);
	
	cardno = in_pack->lvol0;
	des2src(card_phy_id,in_pack->sname);
	if(cardno > 0)
	{
		// 检查卡号
		memset(&card_info,0,sizeof card_info);
		ret = DB_t_card_read_by_cardno(cardno,&card_info);
		if(ret)
		{
			writelog(LOG_ERR,"读取卡信息失败cardid[%d]",cardno);
			if(DB_NOTFOUND == ret)
				*pRetCode = E_DB_CARD_N;
			else
				*pRetCode = E_DB_CARD_R;
			goto L_RETU;
		}
		// 检查物理卡号
		if(strcmp(card_info.cardphyid,card_phy_id))
		{
			// 交易卡号与物理卡号不对
			writelog(LOG_ERR,"上传物理卡号[%s] 实际物理卡号[%s]"
				,card_phy_id,card_info.cardphyid);
			*pRetCode = E_INPUT_CARDNO;
			goto L_RETU;
		}
		// 卡正确,检查卡状态
		ret = CheckCardStatus(card_info.status);
		if(ret)
		{
			writelog(LOG_ERR,"卡状态异常cardid[%d] status[%d]",cardno,ret);
			switch(ret)
			{
				case E_CARD_CLOSE:
					out_pack->lvol0 = UNI_CARD_CANCEL;
					*pRetCode = E_CARD_CLOSE;
					goto L_RETU;
				case E_CARD_FREEZE:
					out_pack->lvol0 = UNI_CARD_FROZEN;
					break;
				case E_CARD_LOST:
					out_pack->lvol0 = UNI_CARD_LOSS;
					break;
				case E_CARDNO_WFAIL:
					out_pack->lvol0 = UNI_CARD_REWRITE_CARD;
					sprintf(out_pack->vsmess,"卡目前状态为写卡失败,继续补写!");
					break;
				default:
					*pRetCode = E_CARDNORMAL;
					goto L_RETU;
			}
			// 如果是补写卡信息
			
		}
		else
		{
			// 正常情况下是充值
			out_pack->lvol0 = UNI_CARD_ADD_MONEY;
		}
		// 卡状态正常, 
		memset(&customer,0,sizeof customer);
		ret = DB_t_customer_read_by_custid(card_info.custid,&customer);
		if(ret)
		{
			writelog(LOG_DEBUG,"未找到 客户号[%d]",card_info.custid);
			if(DB_NOTFOUND == ret)
				*pRetCode = E_DB_CUSTOMER_N;
			else
				*pRetCode = E_DB_CUSTOMER_R;
			goto L_RETU;
		}
		
		out_pack->lvol1 = custid;
		des2src(out_pack->semail,customer.custname);
		des2src(out_pack->scust_auth,customer.stuempno);
		des2src(out_pack->sdate0,customer.can_time);
		out_pack->lvol2 = customer.custtype;
		out_pack->lvol3 = customer.feetype;
		memset(&account,0,sizeof account);
		//ret = DB_t_aif_account_read_by_customer_id_and_act_type(
		//	customer.custid,ACCTYPE_PERMAIN,&account);
		ret = DB_t_aif_account_read_by_cardno_and_purseno(cardno,PURSE_NO_ONE,&account);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				// 客户无账户,应该是办新卡
				*pRetCode = E_DB_ACCOUNT_N;
				goto L_RETU;
			}
			else
			{
				writelog(LOG_ERR,"查询账户信息失败custid [%d]",customer.custid);
				*pRetCode = E_DB_ACCOUNT_R;
				goto L_RETU;
			}
		}
		des2src(out_pack->sbank_acc,account.account_id);
		
	}
	else
	{
		// 检查物理卡号是否已经从上大同步过来.
		memset(&sync_card,0,sizeof sync_card);
		ret = queryCustidAndExpTime(card_phy_id,CARDINF_NEW_STATE,&custid,&sync_card);
		if(ret)
		{
			memset(&sync_card,0,sizeof sync_card);
			ret = queryCustidAndExpTime(card_phy_id,CARDINF_AGAIN_STATE,&custid,&sync_card);
			if(ret)
			{
				writelog(LOG_DEBUG,"卡信息未找到phyid[%s] ",card_phy_id);
				sprintf(szMsg,"该卡不可识别!!");
				*pRetCode = ret;
				goto L_RETU;
			}
			else
			{
				//card_state = CARDINF_AGAIN_STATE;
				sprintf(out_pack->vsmess,"新卡");
			}
		}
		ret = IsExistCardByPhyCardNo(card_phy_id);
		if(ret)
		{
			*pRetCode = E_CARD_PUBLISHED;
			goto L_RETU;
		}
		// TODO: 设置缴纳金额
		paymoney = sync_card.fee;
		memset(&customer,0,sizeof customer);
		ret = DB_t_customer_read_by_custid(custid,&customer);
		if(ret)
		{
			writelog(LOG_ERR,"查询客户信息失败custid[%d]cardphyid[%s] ret[%d] ",
				custid,card_phy_id,ret);
			if(DB_NOTFOUND == ret)
				*pRetCode = ret;
			else
				*pRetCode = E_DB_CUSTOMER_R;
			goto L_RETU;
		}
		
		out_pack->lvol1 = custid;
		des2src(out_pack->semail,customer.custname);
		des2src(out_pack->scust_auth,customer.stuempno);
		des2src(out_pack->sdate0,customer.can_time);
		out_pack->lvol2 = customer.custtype;
		out_pack->lvol3 = customer.feetype;
		// 判断交易功能号
		memset(&account,0,sizeof account);
		
		//ret = DB_t_aif_account_read_by_customer_id_and_act_type(
		//	customer.custid,ACCTYPE_PERMAIN,&account);
		ret=GetLostCardIdByCustomId_TypeId(customer.custid,CT_NORMAL,&lost_cardno);
		if(ret)
		{
			if(E_DB_CARD_R != ret)
			{
				// 客户无账户,应该是办新卡
				if(5 == customer.feetype)
				{
					trade_request = 847124;
					sprintf(out_pack->vsmess,"该卡需要收取押金%.2lf元",paymoney);
				}
				else
				{
					trade_request = 847101;
					sprintf(out_pack->vsmess,"该卡需要收取成本费%.2lf元",paymoney);
				}
				out_pack->damt0 = paymoney;
				card_state = UNI_CARD_NEW_CARD;
			}
			else
			{
				writelog(LOG_ERR,"查询卡信息失败custid [%d]",customer.custid);
				*pRetCode = E_DB_CARD_R;
				goto L_RETU;
			}
		}
		else
		{
			
			// 补办卡
			trade_request = 847104;
			out_pack->damt0 = paymoney; //- account.cur_freebala;
			
			if(out_pack->damt0 > 0)
			{
				//
				sprintf(out_pack->vsmess,"发行该卡要从账户余额中扣除%.2lf 元成本费\
					,但目前账户余额不足,至少需要充值%.2lf元",paymoney,out_pack->damt0);
			}
			else
			{
			
				// 账户余额已经足够发卡了.
			sprintf(out_pack->vsmess,"发行该卡需要%.2lf 元成本费,至少需要充值%.2lf元",
				paymoney,paymoney);
			out_pack->damt0 = paymoney;
			//}
			card_state = UNI_CARD_REISSUE_CARD;
			writelog(LOG_DEBUG,out_pack->vsmess);
		}
		out_pack->lvol4 = trade_request;
		out_pack->lvol0 = card_state;
	}

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
	*/
L_RETU:
	return -1;
}
