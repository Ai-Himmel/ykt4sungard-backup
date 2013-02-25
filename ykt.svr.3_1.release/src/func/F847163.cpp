/* --------------------------------------------
 * 程序名称: F847163.sqc
 * 创建日期: 2004 11 17
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 发卡充值手续费、管理费、搭伙费、充值金额计算
 * --------------------------------------------
 * 修改日期:2005-08-04
 * 修改人员:闻剑
 * 修改描述:本交易不再使用
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/

#define _IN_SQC_
#include<pubdef.h>
#include<pubdb.h>
#include<dbfunc.h>
#include<errdef.h>
#include "fdsqc.h"
#include "dbfunc_foo.h"
#include "pubfunc.h"


int F847163(TRUSERID * handle, int iRequest, ST_PACK * rPack, int *pRetCode, char *szMsg) {
    int ret = 0;
    double maxfeeratio = 0;			//比率
    double amt=0;
    ST_CPACK aPack;
    ST_PACK *pp = &(aPack.pack);
//	T_t_custtypefee  custtype;

    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle,F_DAMT1,F_DAMT2,F_DAMT3,F_DAMT4,F_DAMT5,0);
    PutRow(handle, pp, pRetCode, szMsg);
    return 0;
//	memset(&custtype,0,sizeof(custtype));

//	writelog(LOG_DEBUG, "rPack->lvol0[%d]", rPack->lvol0);	//客户类别
//	writelog(LOG_DEBUG, "rPack->lvol1[%d]", rPack->lvol1);	//交易码
//	writelog(LOG_DEBUG, "rPack->damt0[%lf]", rPack->damt0);	//发生额
    /*
    	ret=DB_t_custtypefee_read_by_custtype(rPack->lvol0,&custtype);
    	if(ret)
    	{
    		writelog(LOG_ERR,"custtype[%d]",rPack->lvol0);
    		if(DB_NOTFOUND==ret)
    			*pRetCode=E_CUTTYPE_NOT_EXIST;
    		else
    			*pRetCode=E_CUTTYPEFEE_R;
    		goto L_RETU;
    	}
    	switch(rPack->lvol1)
    	{
    		case 847101:				//发行正式卡(新生卡,不收任何费用)
    			if(IS_YES==custtype.is_firstcostfee)
    			{
    				pp->damt3= custtype.depositfee;		//押金金额
    				pp->damt4=0;
    				pp->damt5 = custtype.in_fee;			//手续费
    			}
    			else
    			{
    				pp->damt3=0;						//押金金额
    				pp->damt4=0;
    				pp->damt5=0;
    			}
    			break;
    		case 847104:				//补办卡
    			if(IS_NO!=rPack->lvol2)
    			{
    				pp->damt4 =custtype.cost_fee;		//卡成本费
    			}
    			pp->damt3=0;							//押金金额
    			pp->damt5 = 0;							//手续费
    			break;
    		case 847126:									//发行VIP卡
    			pp->damt3=0;							//押金金额
    			pp->damt4 =custtype.cost_fee;			//卡成本费
    			pp->damt5 = 0;							//手续费
    			break;
    		case 847116:									//发行过渡临时卡
    		case 847125:									//发行非记名临时卡
    			pp->damt3= custtype.depositfee;			//押金金额
    			pp->damt4=0;
    			pp->damt5 = 0;							//手续费
    			break;
    		case 847124:									//发行记名临时卡
    			pp->damt3= custtype.depositfee;			//押金金额
    			pp->damt4=0;
    			pp->damt5 = custtype.in_fee;				//手续费
    			break;
    		default:
    			*pRetCode=E_TXCODE_NOT_EXIST;
    			goto L_RETU;
    	}
    	amt=rPack->damt0-(pp->damt3+pp->damt4+pp->damt5);
    	if(amtcmp(amt,0)<0)
    	{
    			*pRetCode=E_CASH_LACK;
    			goto L_RETU;
    	}
    	if(strncmp(custtype.is_outfee,TYPE_YES,1)==0)
    	{
    		ret=GetMaxFeeRatioFromShop(&maxfeeratio);
    		if(ret)
    		{
    			*pRetCode=ret;
    			goto L_RETU;
    		}
    		pp->damt2=D4U5(amt*maxfeeratio,2);	//预扣搭伙费
    	}
    //	pp->damt1=D4U5(amt-pp->damt2,2);		//出卡值,
    	PutRow(handle, pp, pRetCode, szMsg);
    	return 0;
      L_RETU:
    	return -1;
    */
}
