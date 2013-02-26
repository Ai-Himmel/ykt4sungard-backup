/* --------------------------------------------
* 程序名称: F851003.cpp
* 创建日期: 2007-5-11
* 程序作者: 李翔
* 版本信息: 1.0.0.0
* 程序功能: 网络收费帐户查询(包含第三方对接)
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
#include "pubfunc.h"
#include "bupub.h"
#include "PaymentProtocol.h"
#include "bufunc.h"
extern CSvrLink *g_pSvrLink;

#ifdef __cplusplus
extern "C" {
#endif

int F851003(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	char szStuEmpNo[21] = "";
	char szAccSerOutOfDate[9] = "";
	double dRemainBalance = 0.0;
	double dOweBalanece = 0.0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	PaymentProtocol protocol;
	payment_request_t payment;

	ResetNormalCPack(&aPack, 0, 1);

	SetHeadCol(&aPack,0);
	SetHeadCol(&aPack,F_LSAFE_LEVEL,F_VSMESS, F_SCUST_LIMIT, F_SBANK_CODE,F_SBANK_ACC,
		F_SCUSTTYPES,F_LVOL1,F_SPHONE3,F_VSVARSTR0, 0);


	protocol.begin_filed();
	protocol.add_field(in_pack->scust_limit);
	protocol.add_field(in_pack->sbank_code);
	protocol.add_field(in_pack->sbank_acc);
	protocol.add_int_field(in_pack->lwithdraw_flag);
	protocol.add_int_field(in_pack->lvol1);
	protocol.add_field(in_pack->sphone3);
	protocol.add_field(in_pack->vsvarstr0);

	if(protocol.final_add_field(payment.req,1))
	{
		out_pack->lsafe_level = PYM_INPUT_DATA;
		strcpy(out_pack->vsmess,"请求参数错误");
	}
	else
	{
		payment.host = in_pack->sholder_ac_no2;
		payment.port = in_pack->lvol4;
		payment.timeout = in_pack->lsafe_level*1000;
		payment.protocol = &protocol;

		if(payment_process(&payment,1))
		{
			out_pack->lsafe_level = payment.retcode;
			strcpy(out_pack->vsmess,payment.retmsg.c_str());
		}
		else if(protocol.parse(payment.resp.c_str(),0))
		{
			out_pack->lsafe_level = PYM_RET_ERR;
			strcpy(out_pack->vsmess,"第三方返回的数据格式错误");
			return 0;
		}
		else
		{
			GET_STR_FIELD(protocol,1,out_pack->scust_limit);
			GET_STR_FIELD(protocol,2,out_pack->sbank_code);
			GET_STR_FIELD(protocol,3,out_pack->sbank_acc);
			GET_STR_FIELD(protocol,4,out_pack->scusttypes);
			protocol.get_int_field(5,out_pack->lvol1);
			GET_STR_FIELD(protocol,6,out_pack->sphone3);
			protocol.get_int_field(7,out_pack->lvol3);
			GET_STR_FIELD(protocol,8,out_pack->vsvarstr0);
			out_pack->lsafe_level = 0;
		}
	}
	g_pSvrLink->SetCol(handle,aPack.head.ParmBits);
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}

#ifdef __cplusplus
}
#endif