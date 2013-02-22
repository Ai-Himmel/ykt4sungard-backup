// AutoGetTPFile.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "filetrans.h"
#include "Ini.h"
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

void __stdcall mycallback(int total_len,int pack_len)
{
	char msg[128] = "";
	sprintf(msg, "pack index[%d][%d]length[%d]\n",++g_index,total_len,pack_len);
	PrintScreen(PRINT_MAIN, msg);
}

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

int FileTrans()
{
	int ret = 0;
	char eMsg[128] = "";
	char now_date[9] = "";
	char now_time[7] = "";

	KSG_init(g_ini_file.drtp_ip, g_ini_file.drtp_port, g_ini_file.bcc_func_no);
	KSG_File_Handle handle = KSG_begin_request();
	if (handle == NULL)
	{
		strcpy(eMsg, "传输文件请求失败");
		PrintScreen(PRINT_ASSIST, eMsg);
		return ERR_KSG_FILE_HANDLE;
	}

	KSG_set_param(handle, g_ini_file.transfer_type, "1", 0);

	GetSysDateTime(now_date, now_time);
	if (1 == g_ini_file.time_flag)
	{
		strncpy(g_ini_file.des_file[g_ini_file.file_count -1] + des_file_length, now_date, strlen(now_date));
		strncpy(g_ini_file.des_file[g_ini_file.file_count -1] + des_file_length + strlen(now_date), now_time, strlen(now_time));
	}

	if (!strstr(g_ini_file.src_file[g_ini_file.file_count -1], g_ini_file.file_suffix))
	{
		strcat(g_ini_file.src_file[g_ini_file.file_count -1], g_ini_file.file_suffix);
	}

	if (!strstr(g_ini_file.des_file[g_ini_file.file_count -1], g_ini_file.file_suffix))
	{
		strcat(g_ini_file.des_file[g_ini_file.file_count -1], g_ini_file.file_suffix);
	}
	
	if (0 == strncmp(g_ini_file.transfer_type, "download", 8))
	{
		if (!strstr(g_ini_file.win_dir, g_ini_file.file_suffix))
		{
			strcat(g_ini_file.win_dir, g_ini_file.des_file[g_ini_file.file_count - 1]);
		}
		KSG_set_param(handle, "src_filename", g_ini_file.src_file[g_ini_file.file_count -1],0);
		KSG_set_param(handle, "dest_filename", g_ini_file.win_dir, 0);
	}
	else
	{
		if (!strstr(g_ini_file.win_dir, g_ini_file.file_suffix))
		{
			strcat(g_ini_file.win_dir, g_ini_file.src_file[g_ini_file.file_count - 1]);
		}
		KSG_set_param(handle, "src_filename", g_ini_file.win_dir,0);
		KSG_set_param(handle, "dest_filename", g_ini_file.des_file[g_ini_file.file_count -1], 0);
	}

	KSG_set_param(handle, g_ini_file.call_back, mycallback, 0);
	g_index = 0;
	ret = KSG_send_request(handle);
	if(ret)
	{
		sprintf(eMsg, "传输文件失败,ret[%d]", ret);
	}
	else
	{
		sprintf(eMsg, "文件传输成功");
	}

	PrintScreen(PRINT_MAIN, eMsg);
	KSG_free_request(handle);
	KSG_uninit();

	return ret;
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
	char eMsg[1024];  // 注意尽量给出缓存为 >=1024字节
	char now_date[9] = "";
	char now_time[7] = "";
	char dest_file[100] = "";
	CFileClass file;	// 文件类
	char file_name[128] = "";
	char share_file_name[128] = "share.ks";				// share file named share.ks
	
	if (FALSE == ShowOnlyInstance()) { return FALSE; }

	printf("--------------------------------------------------------\n");
	printf("--describe: AutoPutFile_v1.0----------------------------\n");
	printf("--author:   xiang.li------------------------------------\n");
	printf("--date:     2008-08-07----------------------------------\n");
	printf("--company:  kingstar------------------------------------\n");
	printf("--------------------------------------------------------\n");
	ret = InitConfig("CardDll.ini");
	if (ret) 
	{ 
		sprintf(eMsg, "read ini file error, errcode=[%d]\n", ret);
		PrintScreen(PRINT_MAIN, eMsg);
		DEBUG_CARD_MSGOUT(eMsg, ret);
	}

	if (0 == g_ini_file.file_count) 
	{
		DEBUG_CARD_MSGOUT(eMsg, ERR_SRCFILE_EXIT);
		return ERR_SRCFILE_EXIT;
	}
	
	des_file_length = strlen(g_ini_file.des_file[g_ini_file.file_count -1]);
	strcpy(file_name, g_ini_file.src_file[g_ini_file.file_count -1]);
	strcat(file_name, g_ini_file.file_suffix);

	// 1. 寻找当前register.txt文件, 寻找到了进入2否则进入1
	// 2. 将register.txt文件传送到后台目录, 成功到3, 否则进入1
	// 3. 执行后台功能847326, 将文件解析到数据库中, 成功到4, 否则进入1
	// 4. 移动目录中的register.txt文件到其他目录存放
	while (TRUE)
	{
		if (!file.Open(file_name, file.modeRead))
		{
			strcpy(eMsg, "register.txt文件不存在");
			PrintScreen(PRINT_MAIN, eMsg);
			SetLastErrMsg(ret, eMsg);
			DEBUG_CARD_MSGOUT(g_errcode, g_errmsg);
			Sleep(TIME_WAIT2);
			continue ;
		}
		file.Close();

		strcpy(eMsg, "寻找到了register.txt");
		PrintScreen(PRINT_MAIN, eMsg);
		Sleep(TIME_WAIT);

		ret = FileTrans();
		if (ret)
		{
			strcpy(eMsg, "register.txt文件推送到后台失败");
			PrintScreen(PRINT_MAIN, eMsg);
			SetLastErrMsg(ret, eMsg);
			DEBUG_CARD_MSGOUT(g_errcode, g_errmsg);
			Sleep(TIME_WAIT2);
			continue ;
		}
		
		strcpy(dest_file, g_ini_file.dest_dir);
		strcat(dest_file, g_ini_file.des_file[g_ini_file.file_count -1]);

		// 文件更名
		file.SetMoveFile(g_ini_file.src_file[g_ini_file.file_count -1], dest_file);
		// 结束析构资源
		memset(eMsg, 0, sizeof(eMsg));
		sprintf(eMsg, "推送文件[%s]成功", dest_file);
		PrintScreen(PRINT_MAIN, eMsg);
		
		if (!file.Open(share_file_name, file.modeCreate))
		{
			strcpy(eMsg, "打开共享文件失败");
			PrintScreen(PRINT_MAIN, eMsg);
			SetLastErrMsg(ret, eMsg);
			DEBUG_CARD_MSGOUT(g_errcode, g_errmsg);
		}
		
		strcpy(eMsg, "写入共享文件成功");
		PrintScreen(PRINT_MAIN, eMsg);

		memset(dest_file, 0, sizeof(dest_file));
		strcpy(dest_file, g_ini_file.des_file[g_ini_file.file_count -1]);

		file.Write(dest_file, strlen(dest_file));
		file.Close();
		Sleep(TIME_WAIT2);
	}
	getchar();

	return 0;
}

