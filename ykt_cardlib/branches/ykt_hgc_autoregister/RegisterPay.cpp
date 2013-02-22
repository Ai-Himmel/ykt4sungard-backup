// RegisterPay.cpp : �������̨Ӧ�ó������ڵ㡣
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

// ��ȡ�����ļ�
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
	// ��ȡ�ļ���׺��
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "SUFFIX"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.file_suffix, ini_value, sizeof(g_ini_file.file_suffix) - 1);

	// ��ȡdrtp��IP��ַ
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "DRTP_IP"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.drtp_ip, ini_value, sizeof(g_ini_file.drtp_ip) - 1);

	// ��ȡdrtp�Ķ˿ں�
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "DRTP_PORT"))) { return ERR_READ_INIVALUE; }
	g_ini_file.drtp_port = atoi(ini_value);

	// ��ȡBCC���ܺ�
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "BCC_NO"))) { return ERR_READ_INIVALUE; }
	g_ini_file.bcc_func_no = atoi(ini_value);

	// ��ȡ�����־
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "TRANS_FLAG"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.transfer_type, ini_value, sizeof(g_ini_file.transfer_type) - 1);

	// ��ȡ�ص���־
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "CALL_BACK_FLAG"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.call_back, ini_value, sizeof(g_ini_file.call_back) - 1);

	// ��ȡĿ���ļ�·��
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "WINDIR"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.win_dir, ini_value, sizeof(g_ini_file.win_dir) - 1);
	
	// ��ȡʱ���־
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "TIME_FLAG"))) { return ERR_READ_INIVALUE; }
	g_ini_file.time_flag = atoi(ini_value);

	// ��ȡĿ��Ŀ¼
	if (NULL == (ini_value = ini.ReadText("TRANSFILE", "DEST_DIR"))) { return ERR_READ_INIVALUE; }
	strncpy(g_ini_file.dest_dir, ini_value, sizeof(g_ini_file.dest_dir) - 1);

	// ��ȡ��ǰ����
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

		// �������ļ���ȡĿ���ļ�(windows)����
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
		// �������ļ���ȡ��̨�ļ�����
		ini_value = ini.ReadText("TRANSFILE", msg);			
		if (0 == strlen(ini_value)) { break; }								// Ѱ�Ҳ���FILE + N���ļ����˳�ѭ��
		if (NULL != (post = strstr(ini_value, "date")))
		{
			strncpy(g_ini_file.src_file[count - 1], ini_value, 99);
			post = strstr(g_ini_file.src_file[count - 1], "date");
			strncpy(post, date, sizeof(date) - 1);
		}
		else	// �ֶ���������	
		{
			strncpy(g_ini_file.src_file[count - 1], ini_value, 99);
		}
		g_ini_file.file_count = count++;
		memset(msg, 0, sizeof(msg));
	}

	ini.Close();
	return 0;
}

// ִ�к�̨���ܺ�
int FKBDC847326(KBDCHandle ch)
{
	char eMsg[1024] = "";		// ע�⾡����������Ϊ >=1024�ֽ�
	char fvalue[1024] = "";		// ע������������Ϊ >=1024�ֽ�
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
	
	KBDCSetFieldValue(ch, "scard0", current_func_file);			// �ļ���
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
	// ������һ�������Ӧ����̵Ĳ��ԡ�����

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
		strcpy(eMsg, "ʵ���Ѿ�����");
		PrintScreen(PRINT_MAIN, eMsg);
		return FALSE; 
	}

	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;
	char eMsg[1024] = "";  // ע�⾡����������Ϊ >=1024�ֽ�
	char now_date[9] = "";
	char now_time[7] = "";
	KBDCHandle ch = 0;
	char share_file_name[128] = "share.ks";				// share file named share.ks
	CFileClass file;	// �ļ���
	
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

	// 1. Ѱ�ҵ�ǰregister.txt�ļ�, Ѱ�ҵ��˽���2�������1
	// 2. ��register.txt�ļ����͵���̨Ŀ¼, �ɹ���3, �������1
	// 3. ִ�к�̨����847326, ���ļ����������ݿ���, �ɹ���4, �������1
	// 4. �ƶ�Ŀ¼�е�register.txt�ļ�������Ŀ¼���

	// ���߳̽���������Ļ���, ���߳����ڴ����ļ���ִ�й��ܺ�
	///////////////////////////////// Begin1 //////////////////////////////////////
	// ��������������������߳��ڣ�������������֮ǰ���ã����ұ���Ϊ�ɹ�����
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
				sprintf(eMsg, "%s������", share_file_name);
				PrintScreen(PRINT_MAIN, eMsg);
				SetLastErrMsg(ret, eMsg);
				DEBUG_CARD_MSGOUT(g_errcode, g_errmsg);
				Sleep(TIME_WAIT2);
				continue ;
			}
			
			sprintf(eMsg, "%s����", share_file_name);
			PrintScreen(PRINT_MAIN, eMsg);

			memset(current_func_file, 0, sizeof(current_func_file));
			file.Read(current_func_file, sizeof(current_func_file));
			file.Close();

			if (strncmp(current_func_file, last_func_file, sizeof(current_func_file)) <= 0)
			{
				sprintf(eMsg, "û�����µĵ�ǰ�ļ�");
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

			// ִ�к�̨���ܺ�
			ret = FKBDC847326(ch);
			if (ret)
			{
				strcpy(eMsg, "847326����ִ��ʧ��");
			}
			else
			{
				strcpy(eMsg, "847326����ִ�гɹ�");
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

