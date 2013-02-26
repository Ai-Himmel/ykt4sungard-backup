/* --------------------------------------------
* 程序名称: F847350.cpp
* 创建日期: 2007-5-11
* 程序作者: 李翔
* 版本信息: 1.0.0.0
* 程序功能: 上海理工人员信息同步(包含第三方对接)
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
#include "ComFunNetCharge.h"
#include "LoadDll.h"
#include "DllFun.h"
#include "PersonInfoApi.h"



#ifdef __cplusplus
extern "C" {
#endif


int F847350(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	
	int ret = 0;
	int error_code = 0;
	PERSON_INFO sl_person_info[30];
	ST_PACK *g_pArrays;
	memset(sl_person_info, 0, sizeof(sl_person_info));

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_DAMT1, F_SPHONE, F_LVOL10, 0);

	memcpy(sl_person_info[0].show_id, in_pack->scust_no, sizeof(sl_person_info[0].show_id));
	memcpy(sl_person_info[0].classdept_name, in_pack->vsvarstr0, sizeof(sl_person_info[0].classdept_name));
	memcpy(sl_person_info[0].stuemp_no, in_pack->sname2, sizeof(sl_person_info[0].stuemp_no));
	sl_person_info[0].card_id = in_pack->lvol2;
	sl_person_info[0].type_id = in_pack->lvol5;
	sl_person_info[0].cut_id = in_pack->lvol6;
	memcpy(sl_person_info[0].cut_type_name, in_pack->vsvarstr1, sizeof(sl_person_info[0].cut_type_name));
	sl_person_info[0].cut_state = in_pack->lvol7;
	sl_person_info[0].area = in_pack->lvol8;
	memcpy(sl_person_info[0].main_id, in_pack->scust_auth, sizeof(sl_person_info[0].main_id));
	memcpy(sl_person_info[0].state_id, in_pack->spost_code, sizeof(sl_person_info[0].state_id));
	memcpy(sl_person_info[0].reg_time, in_pack->sphone3, sizeof(sl_person_info[0].reg_time));
	memcpy(sl_person_info[0].can_time, in_pack->spager, sizeof(sl_person_info[0].can_time));
	memcpy(sl_person_info[0].cut_name, in_pack->semail, sizeof(sl_person_info[0].cut_name));
	memcpy(sl_person_info[0].sex, in_pack->sstatus2, sizeof(sl_person_info[0].sex));
	memcpy(sl_person_info[0].physical_no, in_pack->sname, sizeof(sl_person_info[0].physical_no));
	memcpy(sl_person_info[0].volume, in_pack->sholder_ac_no, sizeof(sl_person_info[0].volume));
	
	for (int pack_cout = 1; pack_cout < 30; pack_cout++)
	{
		memcpy(sl_person_info[pack_cout].show_id, g_pArrays[pack_cout].scust_no, sizeof(sl_person_info[pack_cout].show_id));
		memcpy(sl_person_info[pack_cout].classdept_name, g_pArrays[pack_cout].vsvarstr0, sizeof(sl_person_info[pack_cout].classdept_name));
		memcpy(sl_person_info[pack_cout].stuemp_no, g_pArrays[pack_cout].sname2, sizeof(sl_person_info[pack_cout].stuemp_no));
		sl_person_info[pack_cout].card_id = g_pArrays[pack_cout].lvol2;
		sl_person_info[pack_cout].type_id = g_pArrays[pack_cout].lvol5;
		sl_person_info[pack_cout].cut_id = g_pArrays[pack_cout].lvol6;
		memcpy(sl_person_info[pack_cout].cut_type_name, g_pArrays[pack_cout].vsvarstr1, sizeof(sl_person_info[pack_cout].cut_type_name));
		sl_person_info[pack_cout].cut_state = g_pArrays[pack_cout].lvol7;
		sl_person_info[pack_cout].area = g_pArrays[pack_cout].lvol8;
		memcpy(sl_person_info[pack_cout].main_id, g_pArrays[pack_cout].scust_auth, sizeof(sl_person_info[pack_cout].main_id));
		memcpy(sl_person_info[pack_cout].state_id, g_pArrays[pack_cout].spost_code, sizeof(sl_person_info[pack_cout].state_id));
		memcpy(sl_person_info[pack_cout].reg_time, g_pArrays[pack_cout].sphone3, sizeof(sl_person_info[pack_cout].reg_time));
		memcpy(sl_person_info[pack_cout].can_time, g_pArrays[pack_cout].spager, sizeof(sl_person_info[pack_cout].can_time));
		memcpy(sl_person_info[pack_cout].cut_name, g_pArrays[pack_cout].semail, sizeof(sl_person_info[pack_cout].cut_name));
		memcpy(sl_person_info[pack_cout].sex, g_pArrays[pack_cout].sstatus2, sizeof(sl_person_info[pack_cout].sex));
		memcpy(sl_person_info[pack_cout].physical_no, g_pArrays[pack_cout].sname, sizeof(sl_person_info[pack_cout].physical_no));
		memcpy(sl_person_info[pack_cout].volume, g_pArrays[pack_cout].sholder_ac_no, sizeof(sl_person_info[pack_cout].volume));	
	}

	ret = GetPersonInfo(&sl_person_info[0], &error_code);
	if (ret == 0)
		out_pack->lvol10 = 10;
	else
		out_pack->lvol10 = 0;

	PutRow(handle, out_pack, pRetCode, szMsg);
	
	return 0;
}


//int F847350(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
//{

	/*int ret = 0;
	int error_code = 0;
	Data_Info sl_person_info[30];
	memset(sl_person_info, 0, sizeof(sl_person_info));

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_DAMT1, F_SPHONE, F_LVOL10, 0);

	memcpy(sl_person_info[0].show_id, in_pack->scust_no, sizeof(sl_person_info[0].show_id));
	memcpy(sl_person_info[0].classdept_name, in_pack->vsvarstr0, sizeof(sl_person_info[0].classdept_name));
	memcpy(sl_person_info[0].stuemp_no, in_pack->sname2, sizeof(sl_person_info[0].stuemp_no));
	sl_person_info[0].card_id = in_pack->lvol2;
	sl_person_info[0].type_id = in_pack->lvol5;
	sl_person_info[0].cut_id = in_pack->lvol6;
	memcpy(sl_person_info[0].cut_type_name, in_pack->vsvarstr1, sizeof(sl_person_info[0].cut_type_name));
	sl_person_info[0].cut_state = in_pack->lvol7;
	sl_person_info[0].area = in_pack->lvol8;
	memcpy(sl_person_info[0].main_id, in_pack->scust_auth, sizeof(sl_person_info[0].main_id));
	memcpy(sl_person_info[0].state_id, in_pack->spost_code, sizeof(sl_person_info[0].state_id));
	memcpy(sl_person_info[0].reg_time, in_pack->sphone3, sizeof(sl_person_info[0].reg_time));
	memcpy(sl_person_info[0].can_time, in_pack->spager, sizeof(sl_person_info[0].can_time));
	memcpy(sl_person_info[0].cut_name, in_pack->semail, sizeof(sl_person_info[0].cut_name));
	memcpy(sl_person_info[0].sex, in_pack->sstatus2, sizeof(sl_person_info[0].sex));
	memcpy(sl_person_info[0].physical_no, in_pack->sname, sizeof(sl_person_info[0].physical_no));
	memcpy(sl_person_info[0].volume, in_pack->sholder_ac_no, sizeof(sl_person_info[0].volume));

	for (int pack_cout = 1; pack_cout < 30; pack_cout++)
	{
		memcpy(sl_person_info[pack_cout].show_id, g_pArrays[pack_cout].scust_no, sizeof(sl_person_info[pack_cout].show_id));
		memcpy(sl_person_info[pack_cout].classdept_name, g_pArrays[pack_cout].vsvarstr0, sizeof(sl_person_info[pack_cout].classdept_name));
		memcpy(sl_person_info[pack_cout].stuemp_no, g_pArrays[pack_cout].sname2, sizeof(sl_person_info[pack_cout].stuemp_no));
		sl_person_info[pack_cout].card_id = g_pArrays[pack_cout].lvol2;
		sl_person_info[pack_cout].type_id = g_pArrays[pack_cout].lvol5;
		sl_person_info[pack_cout].cut_id = g_pArrays[pack_cout].lvol6;
		memcpy(sl_person_info[pack_cout].cut_type_name, g_pArrays[pack_cout].vsvarstr1, sizeof(sl_person_info[pack_cout].cut_type_name));
		sl_person_info[pack_cout].cut_state = g_pArrays[pack_cout].lvol7;
		sl_person_info[pack_cout].area = g_pArrays[pack_cout].lvol8;
		memcpy(sl_person_info[pack_cout].main_id, g_pArrays[pack_cout].scust_auth, sizeof(sl_person_info[pack_cout].main_id));
		memcpy(sl_person_info[pack_cout].state_id, g_pArrays[pack_cout].spost_code, sizeof(sl_person_info[pack_cout].state_id));
		memcpy(sl_person_info[pack_cout].reg_time, g_pArrays[pack_cout].sphone3, sizeof(sl_person_info[pack_cout].reg_time));
		memcpy(sl_person_info[pack_cout].can_time, g_pArrays[pack_cout].spager, sizeof(sl_person_info[pack_cout].can_time));
		memcpy(sl_person_info[pack_cout].cut_name, g_pArrays[pack_cout].semail, sizeof(sl_person_info[pack_cout].cut_name));
		memcpy(sl_person_info[pack_cout].sex, g_pArrays[pack_cout].sstatus2, sizeof(sl_person_info[pack_cout].sex));
		memcpy(sl_person_info[pack_cout].physical_no, g_pArrays[pack_cout].sname, sizeof(sl_person_info[pack_cout].physical_no));
		memcpy(sl_person_info[pack_cout].volume, g_pArrays[pack_cout].sholder_ac_no, sizeof(sl_person_info[pack_cout].volume));	
	}

	ret = GetPersonInfo(&sl_person_info[0], &error_code);
	if (ret == 0)
		out_pack->lvol10 = 10;
	else
		out_pack->lvol10 = 0;

	PutRow(handle, out_pack, pRetCode, szMsg);*/

//	return 0;
//}

#ifdef __cplusplus
}
#endif