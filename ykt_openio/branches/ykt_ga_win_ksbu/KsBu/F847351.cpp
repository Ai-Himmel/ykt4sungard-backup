/* --------------------------------------------
* 程序名称: F847351.cpp
* 创建日期: 2007-07-04
* 程序作者: 李翔
* 版本信息: 1.0.0.0
* 程序功能: 公安专科信息同步(包含第三方对接, 此版本通用)
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
#include "mypub.h"
#include "bupub.h"
#include "logfile.h"
//#include "ComFunNetCharge.h"
//#include "LoadDll.h"
#include "DllFun.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _DEBUG
	extern CLogFile g_LogFile;	
	int count = 0;
#endif

#define  CARDSTAT_TYPE_REG	 		0     	//卡状态:挂失1-正常2-挂失
#define  CARDSTAT_TYPE_LOST	 		1     	//卡状态:挂失0-正常1-挂失
#define  CARDSTAT_TYPE_FREEZE		2     	//卡状态 冻结0-正常1-冻结
#define  CARDSTAT_TYPE_WFAIL 		3  		//卡状态:写卡失败0-正常1-写卡失败

int F847351(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
//	::CoInitialize(NULL);				// 结合SQL SERVER2000使用

	int ret = 0;
	int error_code = 0;
	Data_Info data_info;
	memset(&data_info, 0, sizeof(data_info));

	char state_id[5] = "";
	int card_flag = 0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_DAMT1, F_SPHONE, F_LVOL10, 0);

	memcpy(state_id, in_pack->spost_code, sizeof(state_id) - 1);	// 状态	
	card_flag = in_pack->lvol9;										// 卡标志

	memcpy(data_info.physical_no, in_pack->sname, sizeof(data_info.physical_no));	// 先拷贝断物理卡号
	// 判断卡标志
	if ('1' == state_id[CARDSTAT_TYPE_REG])							// 注册
	{
		if ('1' == state_id[CARDSTAT_TYPE_LOST])					// 挂失
		{
			data_info.card_state = 3;
			out_pack->lvol10 = 0;
			PutRow(handle, out_pack, pRetCode, szMsg);
			return 0;
		}
		else if ('1' == state_id[CARDSTAT_TYPE_FREEZE])				// 冻结
		{
			data_info.card_state = 4;
			out_pack->lvol10 = 0;
			PutRow(handle, out_pack, pRetCode, szMsg);
			return 0;
		}
		else if ('1' == state_id[CARDSTAT_TYPE_WFAIL])				// 写卡失败表示为正常
			data_info.card_state = 1;
		else
		{
			if (3 == card_flag)										// 换过的旧卡
			{
				memcpy(data_info.old_physical_no, in_pack->sname, sizeof(data_info.old_physical_no));
				memset(data_info.physical_no, 0, sizeof(data_info.physical_no));
				data_info.card_state = 2;
			}
			else if ((4 == card_flag) || (2 == card_flag) || (-1 == card_flag))		// 换过的新卡, 发新卡, 解挂, 解冻都是正常卡, 
				data_info.card_state = 1;							
			else if (1 == card_flag)
				data_info.card_state = 2;							// 注销卡
			else 
			{
				NULL;
			}
		}
	}
	
	if ('2' == state_id[CARDSTAT_TYPE_REG])							// 注销卡
		data_info.card_state = 2;

	if ('3' == state_id[CARDSTAT_TYPE_REG])							// 换卡
	{
		if (3 == card_flag)											// 换过的旧卡					
		{
			memcpy(data_info.old_physical_no, in_pack->sname, sizeof(data_info.old_physical_no));
			memset(data_info.physical_no, 0, sizeof(data_info.physical_no));
			data_info.card_state = 2;
		}
		
		if (4 == card_flag)
			data_info.card_state = 1;								// 其余为换过的新卡
	}
	
	// 传入动态库的数据字段
	memcpy(data_info.classdept_name, in_pack->vsvarstr0, sizeof(data_info.classdept_name));
	memcpy(data_info.stuemp_no, in_pack->sname2, sizeof(data_info.stuemp_no));
	data_info.cut_id = in_pack->lvol6;
	data_info.cut_type = in_pack->lvol4;
	memcpy(data_info.cut_type_name, in_pack->vsvarstr1, sizeof(data_info.cut_type_name));
	memcpy(data_info.volume, in_pack->sholder_ac_no, sizeof(data_info.volume));
	memcpy(data_info.cut_name, in_pack->semail, sizeof(data_info.cut_name));
//	memcpy(data_info.show_id, in_pack->scust_no, sizeof(data_info.show_id));
//	data_info.card_id = in_pack->lvol2;
//	data_info.type_id = in_pack->lvol5;
//	data_info.cut_state = in_pack->lvol7;
//	data_info.area = in_pack->lvol8;
//	memcpy(data_info.main_id, in_pack->scust_auth, sizeof(data_info.main_id));
//	memcpy(data_info.state_id, in_pack->spost_code, sizeof(data_info.state_id));
//	memcpy(data_info.reg_time, in_pack->sphone3, sizeof(data_info.reg_time));
//	memcpy(data_info.can_time, in_pack->spager, sizeof(data_info.can_time));
//	memcpy(data_info.sex, in_pack->sstatus2, sizeof(data_info.sex));
//	memcpy(data_info.area_name, in_pack->scert_no, sizeof(data_info.area_name));
//	data_info.curBalance = in_pack->damt0;
//	data_info.frozenBalance = in_pack->damt1;
//	data_info.acc_current_state = in_pack->lvol10;
//	data_info.card_flag = in_pack->lvol9;
#ifdef _DEBUG
	g_LogFile.WriteLogEx(1001, "交易卡号[%d]--客户号[%d]--物理卡号[%s]--卡状态标记[%d]--身份[%d]--序号[%d]", 
	in_pack->lvol2, data_info.cut_id, data_info.physical_no, data_info.card_state, data_info.cut_type, ++count);
#endif

	GetDataInfo(&data_info, &error_code);
	if (error_code == 0)
		out_pack->lvol10 = 10;
	else
		out_pack->lvol10 = 0;
	
	PutRow(handle, out_pack, pRetCode, szMsg);

	return 0;
}

#ifdef __cplusplus
}
#endif