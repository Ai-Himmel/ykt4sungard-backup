// RegisterPay.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "Ini.h"
#include "filetrans.h"
#include "GlobalDef.h"
#include "kbclt.h"
#include "FileClass.h"
#include "Errdef.h"

void SetLastErrMsg(int errcode, char *error_msg)
{
	g_errcode = errcode;
	strcpy(g_errmsg, error_msg);
	return ;
}

void GetSysDateTime(char now_date[9], char now_time[7])
{
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	sprintf(now_date, "%04d", tm.wYear);
	sprintf(now_date + 4, "%02d", tm.wMonth);
	sprintf(now_date + 6, "%02d", tm.wDay);
	sprintf(now_time, "%02d", tm.wHour);
	sprintf(now_time + 2, "%02d", tm.wMinute);
	sprintf(now_time + 4, "%02d", tm.wSecond);
	return ;
}

void PrintScreen(int flag, char *msg)
{	
	char now_date[9] = "";
	char now_time[7] = "";
	GetSysDateTime(now_date, now_time);

	printf(now_date);
	printf(now_time);
	printf(BLANK);

	switch (flag)
	{
	case PRINT_MAIN:
		printf(MAIN_THREAD);
		break;
	case PRINT_ASSIST:
		printf(ASSIST_THREAD);
		break;
	default:
	    break;
	}
	printf(BLANK);
	printf(msg);
	printf("\n");
	return ;
}

// 读取配置文件
int InitConfig(char * ini_file_name)
{
	char file_name_key[10] = "FILE";
	char des_file_name_key[10] = "DES_FILE";
	char file_name_value[50] = "";
	char date[15] = "";
	char *ini_value = NULL;
	char *post = NULL;
	int count = 1;
	int length = 0;
	char msg[11] = "";

	CIni ini(ini_file_name);
	// 读取文件后缀名
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "SUFFIX"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.file_suffix, ini_value, sizeof(g_ini_file.file_suffix) - 1);

	// 读取drtp的IP地址
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "DRTP_IP"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.drtp_ip, ini_value, sizeof(g_ini_file.drtp_ip) - 1);

	// 读取drtp的端口号
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "DRTP_PORT"))) { return ERR_READ_INIVALUE; }
	g_ini_file.drtp_port = atoi(ini_value);

	// 读取BCC功能号
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "BCC_NO"))) { return ERR_READ_INIVALUE; }
	g_ini_file.bcc_func_no = atoi(ini_value);

	// 读取传输标志
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "TRANS_FLAG"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.transfer_type, ini_value, sizeof(g_ini_file.transfer_type) - 1);

	// 读取回调标志
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "CALL_BACK_FLAG"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.call_back, ini_value, sizeof(g_ini_file.call_back) - 1);

	// 读取目标文件路径
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "WINDIR"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.win_dir, ini_value, sizeof(g_ini_file.win_dir) - 1);
	
	// 读取时间标志
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "TIME_FLAG"))) { return ERR_READ_INIVALUE; }
	g_ini_file.time_flag = atoi(ini_value);

	// 读取目标目录
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "DEST_DIR"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.dest_dir, ini_value, sizeof(g_ini_file.dest_dir) - 1);

	// 获取当前日期
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	sprintf(date, "%04d", tm.wYear);
	sprintf(date + 4, "%02d", tm.wMonth);
	sprintf(date + 6, "%02d", tm.wDay);
	
	if (1 == g_ini_file.time_flag)
	{
		sprintf(date + 8, "%02d", tm.wHour);
		sprintf(date + 10, "%02d", tm.wMinute);
		sprintf(date + 12, "%02d", tm.wSecond);
	}

	while(1)
	{
		strncpy(msg, des_file_name_key, sizeof(des_file_name_key) - 1);
		sprintf(msg + strlen(des_file_name_key), "%d", count);

		// 从配置文件读取目标文件(windows)名称
		ini_value = ini.ReadText("TRANSFILE", msg);		
		if (NULL != (post = strstr(ini_value, "date")))
		{
			strncpy(g_ini_file.des_file[count - 1], ini_value, 99);
			post = strstr(g_ini_file.des_file[count - 1], "date");
			strncpy(post, date, sizeof(date) - 1);
		}
		else
		{
			strncpy(g_ini_file.des_file[count - 1], ini_value, 99);
		}

		strncpy(msg, file_name_key, sizeof(file_name_key) - 1);
		sprintf(msg + strlen(file_name_key), "%d", count);
		// 从配置文件读取后台文件名称
		ini_value = ini.ReadText("TRANSFILE", msg);			
		if (0 == strlen(ini_value)) { break; }								// 寻找不到FILE + N的文件就退出循环
		if (NULL != (post = strstr(ini_value, "date")))
		{
			strncpy(g_ini_file.src_file[count - 1], ini_value, 99);
			post = strstr(g_ini_file.src_file[count - 1], "date");
			strncpy(post, date, sizeof(date) - 1);
		}
		else	// 手动输入日期	
		{
			strncpy(g_ini_file.src_file[count - 1], ini_value, 99);
		}
		g_ini_file.file_count = count++;
		memset(msg, 0, sizeof(msg));
	}

	ini.Close();
	return 0;
}

// 执行后台功能号
int FKBDC847326(KBDCHandle ch)
{
	char eMsg[1024] = "";		// 注意尽量给出缓存为 >=1024字节
	char fvalue[1024] = "";		// 注意必须给出缓存为 >=1024字节
	int rtn = 0;
	int recno = 0;
	
	strcpy(eMsg, "Set Request to 847326");
	PrintScreen(PRINT_MAIN, eMsg);

	rtn = KBDCBeginRequest(ch, 847326, eMsg);
	if (rtn <0)
	{
		PrintScreen(PRINT_MAIN, eMsg);
		DEBUG_CARD_MSGOUT(rtn, eMsg);
		return rtn ;
	}
	
	KBDCSetFieldValue(ch, "scard0", current_func_file);			// 文件名
	sprintf(eMsg, "Send request and receive answer at Time:%u", GetTickCount());
	PrintScreen(PRINT_MAIN, eMsg);
	if (rtn = KBDCCallSvr(ch, 500000, eMsg) < 0)
	{
		PrintScreen(PRINT_MAIN, eMsg);
		DEBUG_CARD_MSGOUT(rtn, eMsg);
		return rtn;
	}

	sprintf(eMsg, "Return Code:%d at Time:%u", KBDCGetRetCode(ch), GetTickCount());
	PrintScreen(PRINT_MAIN, eMsg);
	do 
	{
		rtn = KBDCGetRetCode(ch);
		if (rtn == 0)
		{
			sprintf(eMsg, "KBDCGetRetCode=[%d]", rtn);
			PrintScreen(PRINT_MAIN, eMsg);
		}
		else
		{
			return rtn;
		}
		recno++;
	} while(KBDCNextRetRecord(ch,eMsg)>=0);
	// 结束了一个请求和应答过程的测试。。。

	return 0;
}

int ShowOnlyInstance()
{
	char local_process_name[128] = "";
	char *pdest = NULL;
	char eMsg[1024] = "";
	GetModuleFileName(NULL, local_process_name, sizeof(local_process_name));
	pdest = strrchr(local_process_name, SPLIT1);
	memcpy(current_process_name, pdest + 1, strlen(pdest));

	HANDLE m_hMutex = CreateMutex(NULL, TRUE, current_process_name); 
	if (GetLastError() == ERROR_ALREADY_EXISTS) 
	{
		strcpy(eMsg, "实例已经激活");
		PrintScreen(PRINT_MAIN, eMsg);
		return FALSE; 
	}

	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;
	char eMsg[1024] = "";  // 注意尽量给出缓存为 >=1024字节
	char now_date[9] = "";
	char now_time[7] = "";
	KBDCHandle ch = 0;
	char share_file_name[128] = "share.ks";				// share file named share.ks
	CFileClass file;	// 文件类
	
	if (FALSE == ShowOnlyInstance()) { return FALSE; }

	printf("--------------------------------------------------------\n");
	printf("--describe: AutoRegister_v1.0---------------------------\n");
	printf("--author:   xiang.li------------------------------------\n");
	printf("--date:     2008-08-07----------------------------------\n");
	printf("--company:  kingstar------------------------------------\n");
	printf("--------------------------------------------------------\n");
	
	ret = InitConfig("CardDll.ini");
	if (ret) 
	{ 
		sprintf(eMsg, "read ini file error, errcode=[%d]\n", ret);
		printf(eMsg);
		DEBUG_CARD_MSGOUT(eMsg, ret);
	}

	if (0 == g_ini_file.file_count) 
	{ 
		DEBUG_CARD_MSGOUT(eMsg, ERR_SRCFILE_EXIT);
		return ERR_SRCFILE_EXIT; 
	}

	// 1. 寻找当前register.txt文件, 寻找到了进入2否则进入1
	// 2. 将register.txt文件传送到后台目录, 成功到3, 否则进入1
	// 3. 执行后台功能847326, 将文件解析到数据库中, 成功到4, 否则进入1
	// 4. 移动目录中的register.txt文件到其他目录存放

	// 主线程仅仅用于屏幕输出, 子线程用于传送文件和执行功能号
	///////////////////////////////// Begin1 //////////////////////////////////////
	// 以下这个函数必须在主线程内，启用其他函数之前调用，并且必须为成功才行
#ifdef _DEBUG
	if (KBDCInit(1,"",eMsg) < 0)
#else
	if (KBDCInit(0,"",eMsg) < 0)
#endif
	{
		PrintScreen(PRINT_MAIN, eMsg);
		DEBUG_CARD_MSGOUT(ERR_KBDC_INIT, eMsg);
		return ERR_KBDC_INIT;
	}
	else
	{
		while (TRUE)
		{	
			if (!file.Open(share_file_name, file.modeRead))
			{
				sprintf(eMsg, "%s不存在", share_file_name);
				PrintScreen(PRINT_MAIN, eMsg);
				SetLastErrMsg(ret, eMsg);
				DEBUG_CARD_MSGOUT(g_errcode, g_errmsg);
				Sleep(TIME_WAIT2);
				continue ;
			}
			
			sprintf(eMsg, "%s存在", share_file_name);
			PrintScreen(PRINT_MAIN, eMsg);

			memset(current_func_file, 0, sizeof(current_func_file));
			file.Read(current_func_file, sizeof(current_func_file));
			file.Close();

			if (strncmp(current_func_file, last_func_file, sizeof(current_func_file)) <= 0)
			{
				sprintf(eMsg, "没有最新的当前文件");
				PrintScreen(PRINT_MAIN, eMsg);
				SetLastErrMsg(ret, eMsg);
				DEBUG_CARD_MSGOUT(g_errcode, g_errmsg);
				Sleep(TIME_WAIT2);
				continue ;
			}
			
			Sleep(TIME_WAIT);
			ch = KBDCNewHandle(eMsg);
			if (ch == NULL)
			{
				printf("KBDCNewHandle Error:%s\n",eMsg);
				Sleep(TIME_WAIT2);
				SetLastErrMsg(ret, eMsg);
				DEBUG_CARD_MSGOUT(ret, eMsg);
				continue ;
			}

			// 执行后台功能号
			ret = FKBDC847326(ch);
			if (ret)
			{
				strcpy(eMsg, "847326功能执行失败");
			}
			else
			{
				strcpy(eMsg, "847326功能执行成功");
				memcpy(last_func_file, current_func_file, sizeof(last_func_file));
			}
			KBDCDeleteHandle(ch);
			PrintScreen(PRINT_MAIN, eMsg);
			Sleep(TIME_WAIT2);
		}
	}	

	getchar();
	/////////////////////////////////End of SUB 
	////////////////////////////////// In MainThread ////////////////////////////////////////
	KBDCExit();
	
	return 0;
}

