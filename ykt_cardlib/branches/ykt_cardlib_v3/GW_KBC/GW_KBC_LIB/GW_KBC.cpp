// NetChargeCheckSerial.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include "DataType.h"
#include "GW_KBC.h"
#include "kbclt.h"
#include "ErrCode.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

int __stdcall GW_Login()
{
#ifdef _DEBUG
	if ( KBDCInit(1, "", g_msg) < 0 )
#else
	if ( KBDCInit(0, "", g_msg) < 0 )
#endif
	{
		return GW_ERR_INITFAILED;
	}
	return 0;
}

int __stdcall GW_CreateNewHandle()
{
	g_gw_handle = KBDCNewHandle(g_msg);
	if (NULL == g_gw_handle)
		return GW_ERR_CREATEHANDLEFAILED;

	g_handle_flag = true;
	return 0;
}

int __stdcall GW_CloseHandle()
{
	if (g_handle_flag)
		KBDCDeleteHandle(g_gw_handle);
	
	g_gw_handle = NULL;
	return 0;
}

int __stdcall GW_Exit()
{
	KBDCExit();
	g_handle_flag = false;
	return 0;
}
/*
int __stdcall GW_CheckBillSerial(CheckBillSerial serial[], 
							     int *rec_count,
							     char begin_date[11], 
							     char end_date[11]
							    )
{
	int ret = 0;
	if (g_handle_flag)
	{
		if (ret = F847175(g_gw_handle, serial, begin_date, end_date, rec_count))
			return ret;
	}
	else 
		return GW_ERR_HANDLENOTCREATE;
	
	return 0;
}
*/
int __stdcall GW_DataInfo(char physical_no[9], char stuemp_no[22], DataInfo *data_info)
{
	int ret = 0;
	CutInfo cut_info;
	CardInfo card_info;
	memset(&cut_info, 0, sizeof(cut_info));
	memset(&card_info, 0, sizeof(card_info));

	if (g_handle_flag)
	{
		if (ret = F841700(g_gw_handle, physical_no, stuemp_no, &cut_info, &card_info))
			return ret;

		data_info->cut_id = card_info.customer_id;
		memcpy(data_info->classdept_name, cut_info.classdept_name, sizeof(data_info->classdept_name));
		memcpy(data_info->class_no, cut_info.class_no, sizeof(data_info->class_no));
		memcpy(data_info->cut_name, cut_info.cut_name, sizeof(data_info->cut_name));
		memcpy(data_info->classdept_no, cut_info.classdept_no, sizeof(data_info->classdept_no));
		memcpy(data_info->stuemp_no, cut_info.stuemp_no, sizeof(data_info->stuemp_no));
		memcpy(data_info->state_id, card_info.state_id, sizeof(data_info->state_id));
	}
	else 
		return GW_ERR_HANDLENOTCREATE;

	return 0;
}

int __stdcall GW_GetCardInfo(char physical_no[9], CardInfo *card_info)
{
	int ret = 0;

	if (g_handle_flag)
	{
//		if (ret = F847173(g_gw_handle, physical_no, card_info))
		if (ret = F847173(g_gw_handle, physical_no, card_info))
			return ret;
	}
	else 
		return GW_ERR_HANDLENOTCREATE;

	return 0;
}

int __stdcall GW_GetCustomerInfo(int cut_id, char stuemp_no[22], CutInfo *cut_info)
{
	int ret = 0;
//	if (0 == cut_id) { return GW_ERR_INPUTZEROFAILED; }
	if (g_handle_flag)
	{
		if (ret = F841605(g_gw_handle, cut_id, stuemp_no, cut_info))
			return ret;

		if (ret = F842005(g_gw_handle, cut_info->classdept_no, cut_info->classdept_name))
			return ret;
	}
	else 
		return GW_ERR_HANDLENOTCREATE;

	return 0;
}

int __stdcall GW_GetSeedKey(char *seed_key)
{
	int ret = 0;
	if (NULL == seed_key) { return GW_ERR_INPUTNULLFAILED; }

	if (g_handle_flag)
	{
		if (ret = F950006(g_gw_handle, seed_key))
			return ret;
	}
	else 
		return GW_ERR_HANDLENOTCREATE;

	return 0;
}

void __stdcall GW_GetLastErrorMsg(char *error_msg)
{
	memcpy(error_msg, g_msg, sizeof(g_msg));
}

int __stdcall GW_GetDataRecordExA(int card_id, char physical_no[9], char stuemp_no[22], DataInfoEx *data_info)
{
	int ret = 0;
	if (card_id < 0) return GW_ERR_INPUTCARDIDFAILED;

	if (strlen(physical_no) > 8) return GW_ERR_INPUTPHYNOFAILED;
	
	if (strlen(stuemp_no) > 21) return GW_ERR_INPUTSTUEMPNOFAILED;

	if (g_handle_flag)
	{
		if (ret = F841700ExA(g_gw_handle, physical_no, stuemp_no, card_id, NULL, NULL, data_info))
			return ret;
	}
	else 
		return GW_ERR_HANDLENOTCREATE;

	return 0;
}

int F841605(KBDCHandle handle, int cut_id, char stuemp_no[22], CutInfo *cut_info)
{
	int ret = 0;
	char fvalue[1024] = "";		// 注意必须给出缓存为 >=1024字节
	
	if ((ret = KBDCBeginRequest(g_gw_handle, 841605, g_msg)) < 0)
		return GW_ERR_REQUESTFUNCFAILED;
	
	itoa(cut_id, fvalue, 10);

	KBDCSetFieldValue(g_gw_handle, "lvol1", fvalue);
	KBDCSetFieldValue(g_gw_handle, "scust_auth2", stuemp_no);

	if ((ret = KBDCCallSvr(g_gw_handle, 5000, g_msg)) < 0)
		return GW_ERR_REQUESTSERVERFAILED;

	do 
	{
		if (KBDCGetFieldValue(g_gw_handle, "vsmess", fvalue, g_msg) < 0)
			return GW_ERR_REQUESTPACKFAILED;

		if ((ret = KBDCGetRetCode(g_gw_handle)) == 0)
		{
			KBDCGetFieldValue(g_gw_handle, "lvol1", fvalue, g_msg);
			cut_info->customer_id= atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "sname", fvalue, g_msg);
			memcpy(cut_info->cut_name, fvalue, sizeof(cut_info->cut_name) - 1);
			KBDCGetFieldValue(g_gw_handle, "scust_no", fvalue, g_msg);
			memcpy(cut_info->classdept_no, fvalue, sizeof(cut_info->classdept_no) - 1);
			KBDCGetFieldValue(g_gw_handle, "sorder0", fvalue, g_msg);
			memcpy(cut_info->class_no, fvalue, sizeof(cut_info->class_no) - 1);
			KBDCGetFieldValue(g_gw_handle, "scust_auth2", fvalue, g_msg);
			memcpy(cut_info->stuemp_no, fvalue, sizeof(cut_info->stuemp_no) - 1);
			KBDCGetFieldValue(g_gw_handle, "scard1", fvalue, g_msg);
			memcpy(cut_info->classdept_name, fvalue, sizeof(cut_info->classdept_name) - 1);
		}
		else
		{
			return ret;
		}

	} while(KBDCNextRetRecord(g_gw_handle, g_msg) >= 0);

	return 0;
}

int F847173(KBDCHandle handle, char physical_no[9], CardInfo *card_info)
{
	int ret = 0;
	char fvalue[1024] = "";		// 注意必须给出缓存为 >=1024字节

	if ((ret = KBDCBeginRequest(g_gw_handle, 847173, g_msg)) < 0)
		return GW_ERR_REQUESTFUNCFAILED;

	KBDCSetFieldValue(g_gw_handle, "sbank_acc", physical_no);

	if ((ret = KBDCCallSvr(g_gw_handle, 5000, g_msg)) < 0)
		return GW_ERR_REQUESTSERVERFAILED;

	do 
	{
		if (KBDCGetFieldValue(g_gw_handle, "vsmess", fvalue, g_msg) < 0)
			return GW_ERR_REQUESTPACKFAILED;

		if ((ret = KBDCGetRetCode(g_gw_handle)) == 0)
		{
			KBDCGetFieldValue(g_gw_handle, "lvol0", fvalue, g_msg);
			card_info->card_id= atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "lvol2", fvalue, g_msg);
			card_info->customer_id = atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "sbank_acc", fvalue, g_msg);
			memcpy(card_info->physical_no, fvalue, sizeof(card_info->physical_no) - 1);
			KBDCGetFieldValue(g_gw_handle, "sbank_code", fvalue, g_msg);
			memcpy(card_info->state_id, fvalue, sizeof(card_info->state_id) - 1);
			KBDCGetFieldValue(g_gw_handle, "scust_limit", fvalue, g_msg);
			memcpy(card_info->password, fvalue, sizeof(card_info->password) - 1);
			//			(*rec_count)++;
		}
		else
		{
			return ret;
		}

	} while(KBDCNextRetRecord(g_gw_handle, g_msg) >= 0);

	return 0;
}

int F841700(KBDCHandle handle, char physical_no[9], char stuemp_no[22], CutInfo *cut_info, CardInfo *card_info)
{
	int ret = 0;
	char fvalue[1024] = "";		// 注意必须给出缓存为 >=1024字节

	if ((ret = KBDCBeginRequest(g_gw_handle, 841700, g_msg)) < 0)
		return GW_ERR_REQUESTFUNCFAILED;

	KBDCSetFieldValue(g_gw_handle, "sdate0", physical_no);
	KBDCSetFieldValue(g_gw_handle, "sname2", stuemp_no);

	if ((ret = KBDCCallSvr(g_gw_handle, 5000, g_msg)) < 0)
		return GW_ERR_REQUESTSERVERFAILED;

	do 
	{
		if (KBDCGetFieldValue(g_gw_handle, "vsmess", fvalue, g_msg) < 0)
			return GW_ERR_REQUESTPACKFAILED;

		if ((ret = KBDCGetRetCode(g_gw_handle)) == 0)
		{
			KBDCGetFieldValue(g_gw_handle, "sdate0", fvalue, g_msg);
			memcpy(card_info->physical_no, fvalue, sizeof(card_info->physical_no) - 1);
			KBDCGetFieldValue(g_gw_handle, "sbank_code", fvalue, g_msg);
			memcpy(card_info->state_id, fvalue, sizeof(card_info->state_id) - 1);
			KBDCGetFieldValue(g_gw_handle, "snote", fvalue, g_msg);
			memcpy(cut_info->cut_name, fvalue, sizeof(cut_info->cut_name) - 1);
			KBDCGetFieldValue(g_gw_handle, "semail", fvalue, g_msg);
			memcpy(cut_info->classdept_name, fvalue, sizeof(cut_info->classdept_name) - 1);
			KBDCGetFieldValue(g_gw_handle, "sname2", fvalue, g_msg);
			memcpy(cut_info->stuemp_no, fvalue, sizeof(cut_info->stuemp_no) - 1);
		}
		else
		{
			return ret;
		}

	} while(KBDCNextRetRecord(g_gw_handle, g_msg) >= 0);

	return 0;
}

int F841700ExA(KBDCHandle handle, char physical_no[9], char stuemp_no[22], int card_id,
			   CutInfo *cut_info, CardInfo *card_info, DataInfoEx *data_info_ex)
{
	int ret = 0;
	char fvalue[1024] = "";		// 注意必须给出缓存为 >=1024字节
	char msg[128] = "";

	if ((ret = KBDCBeginRequest(g_gw_handle, 841700, g_msg)) < 0)
		return GW_ERR_REQUESTFUNCFAILED;
	
	itoa(card_id, msg, 10);
	KBDCSetFieldValue(g_gw_handle, "sdate0", physical_no);
	KBDCSetFieldValue(g_gw_handle, "sname2", stuemp_no);
	KBDCSetFieldValue(g_gw_handle, "lvol0", msg);

	if ((ret = KBDCCallSvr(g_gw_handle, 5000, g_msg)) < 0)
		return GW_ERR_REQUESTSERVERFAILED;

	do 
	{
		if (KBDCGetFieldValue(g_gw_handle, "vsmess", fvalue, g_msg) < 0)
			return GW_ERR_REQUESTPACKFAILED;

		if ((ret = KBDCGetRetCode(g_gw_handle)) == 0)
		{
			KBDCGetFieldValue(g_gw_handle, "sdate0", fvalue, g_msg);
			memcpy(data_info_ex->physical_no, fvalue, sizeof(data_info_ex->physical_no) - 1);
			KBDCGetFieldValue(g_gw_handle, "sbank_code", fvalue, g_msg);
			memcpy(data_info_ex->state_id, fvalue, sizeof(data_info_ex->state_id) - 1);
			KBDCGetFieldValue(g_gw_handle, "snote", fvalue, g_msg);
			memcpy(data_info_ex->cut_name, fvalue, sizeof(data_info_ex->cut_name) - 1);
			KBDCGetFieldValue(g_gw_handle, "semail", fvalue, g_msg);
			memcpy(data_info_ex->classdept_name, fvalue, sizeof(data_info_ex->classdept_name) - 1);
			KBDCGetFieldValue(g_gw_handle, "sname2", fvalue, g_msg);
			memcpy(data_info_ex->stuemp_no, fvalue, sizeof(data_info_ex->stuemp_no) - 1);
			KBDCGetFieldValue(g_gw_handle, "sstatus0", fvalue, g_msg);
			memcpy(data_info_ex->sex, fvalue, sizeof(data_info_ex->sex) - 1);
			KBDCGetFieldValue(g_gw_handle, "sserial0", fvalue, g_msg);
			memcpy(data_info_ex->class_no, fvalue, sizeof(data_info_ex->class_no) - 1);
			KBDCGetFieldValue(g_gw_handle, "lvol0", fvalue, g_msg);
			data_info_ex->card_id = atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "lvol1", fvalue, g_msg);
			data_info_ex->cut_id = atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "lvol2", fvalue, g_msg);
			data_info_ex->cut_type = atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "semail2", fvalue, g_msg);
			memcpy(data_info_ex->cut_type_name, fvalue, sizeof(data_info_ex->cut_type_name) - 1);
		}
		else
		{
			return ret;
		}
	} while(KBDCNextRetRecord(g_gw_handle, g_msg) >= 0);

	return 0;
}

int F950006(KBDCHandle handle, char *seed_key)
{
	int ret = 0;
	char fvalue[1024] = "";		// 注意必须给出缓存为 >=1024字节

	if ((ret = KBDCBeginRequest(g_gw_handle, 950006, g_msg)) < 0)
		return GW_ERR_REQUESTFUNCFAILED;

	KBDCSetFieldValue(g_gw_handle, "lvol0", "2006");
	KBDCSetFieldValue(g_gw_handle, "scust_limit", "4343232323231111");

	if ((ret = KBDCCallSvr(g_gw_handle, 5000, g_msg)) < 0)
		return GW_ERR_REQUESTSERVERFAILED;

	do 
	{
		if (KBDCGetFieldValue(g_gw_handle, "vsmess", fvalue, g_msg) < 0)
			return GW_ERR_REQUESTPACKFAILED;

		if ((ret = KBDCGetRetCode(g_gw_handle)) == 0)
		{
			KBDCGetFieldValue(g_gw_handle, "scard0", fvalue, g_msg);
			memcpy(seed_key, fvalue, 16);
		}
		else
		{
			return ret;
		}

	} while(KBDCNextRetRecord(g_gw_handle, g_msg) >= 0);

	return 0;
}

int F842005(KBDCHandle handle, char *classdept_no, char *classdept_name)
{
	int ret = 0;
	char fvalue[1024] = "";		// 注意必须给出缓存为 >=1024字节

	if ((ret = KBDCBeginRequest(g_gw_handle, 842005, g_msg)) < 0)
		return GW_ERR_REQUESTFUNCFAILED;

	KBDCSetFieldValue(g_gw_handle, "scust_no", classdept_no);

	if ((ret = KBDCCallSvr(g_gw_handle, 5000, g_msg)) < 0)
		return GW_ERR_REQUESTSERVERFAILED;

	do 
	{
		if (KBDCGetFieldValue(g_gw_handle, "vsmess", fvalue, g_msg) < 0)
			return GW_ERR_REQUESTPACKFAILED;

		if ((ret = KBDCGetRetCode(g_gw_handle)) == 0)
		{
			KBDCGetFieldValue(g_gw_handle, "ssectypes", fvalue, g_msg);
			memcpy(classdept_name, fvalue, 151);
		}
		else
		{
			return ret;
		}

	} while(KBDCNextRetRecord(g_gw_handle, g_msg) >= 0);

	return 0;
}
/*
int F847175(KBDCHandle handle, CheckBillSerial serial[], char begin_date[11], char end_date[11], int *rec_count)
{
	int ret = 0;
	char fvalue[1024] = "";		// 注意必须给出缓存为 >=1024字节
	if ((ret = KBDCBeginRequest(g_gw_handle, 847175, g_msg)) < 0)
		return GW_ERR_REQUESTFUNCFAILED;

	KBDCSetFieldValue(g_gw_handle, "scust_no", begin_date);
	KBDCSetFieldValue(g_gw_handle, "scust_no2", end_date);

	if ((ret = KBDCCallSvr(g_gw_handle, 5000, g_msg)) < 0)
		return GW_ERR_REQUESTSERVERFAILED;

	*rec_count = 0;
	serial = (CheckBillSerial *)malloc(sizeof(CheckBillSerial));
	do 
	{
		if (KBDCGetFieldValue(g_gw_handle, "vsmess", fvalue, g_msg) < 0)
			return GW_ERR_REQUESTPACKFAILED;
		
		if (0 != *rec_count)
			serial = (CheckBillSerial *)realloc(serial, (*rec_count) * sizeof(CheckBillSerial));

		if (KBDCGetRetCode(g_gw_handle) == 0)
		{
			KBDCGetFieldValue(g_gw_handle, "lvol0", fvalue, g_msg);
			serial->serial_no = atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "lvol9", fvalue, g_msg);
			serial->customer_id = atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "lvol6", fvalue, g_msg);
			serial->card_id = atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "sorder1", fvalue, g_msg);
			memcpy(serial->operate_date, fvalue, sizeof(serial->operate_date) - 1);
			KBDCGetFieldValue(g_gw_handle, "sdate1", fvalue, g_msg);
			memcpy(serial->operate_time, fvalue, sizeof(serial->operate_time) - 1);
			KBDCGetFieldValue(g_gw_handle, "lvol3", fvalue, g_msg);
			serial->serial_state = atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "damt0", fvalue, g_msg);
			serial->trade_fee = atof(fvalue);
			KBDCGetFieldValue(g_gw_handle, "damt1", fvalue, g_msg);
			serial->in_fee = atof(fvalue);
			KBDCGetFieldValue(g_gw_handle, "damt2", fvalue, g_msg);
			serial->out_fee = atof(fvalue);
			KBDCGetFieldValue(g_gw_handle, "lvol5", fvalue, g_msg);
			serial->device_id = atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "lvol10", fvalue, g_msg);
			serial->sys_id = atoi(fvalue);
			KBDCGetFieldValue(g_gw_handle, "semail", fvalue, g_msg);
			memcpy(serial->cut_name, fvalue, sizeof(serial->cut_name) - 1);
			KBDCGetFieldValue(g_gw_handle, "sname", fvalue, g_msg);
			memcpy(serial->stuemp_no, fvalue, sizeof(serial->stuemp_no) - 1);
			(*rec_count)++;
		}
	} while(KBDCNextRetRecord(g_gw_handle, g_msg) >= 0);
	
	return 0;
}
*/