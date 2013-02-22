// AutoGetTPFile.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <stdlib.h>
//#include "filetrans.h"
//#pragma comment(lib ,"filetrans.lib")
#include "filetrans.h"
#pragma comment(lib ,"bin\\filetrans.lib")
#include "Ini.h"
#include "CDate.h"
//////////////////////////////////////////////////////////////////////////
// ������
#define ERR_READ_INIVALUE -10
#define ERR_SRCFILE_EXIT -11
//////////////////////////////////////////////////////////////////////////


static int g_index;
typedef struct _ini_pack
{
	char drtp_ip[25];			// drtp IP
	int  drtp_port;				// drtp�˿ں�
	int  bcc_func_no;			// bcc���ܺ�
	char transfer_type[20];		// ��������: 1.upload, 2.download
	char call_back[20];			// �ص���־: 1.callback
	char src_file[25][100];		// Դ�ļ���, ���ݴ������Ͷ���, �������25���ļ�, ÿ���ļ�100���ֽڳ���
	char des_file[25][100];		// Ŀ���ļ���, ���ݴ������Ͷ���, �������25���ļ�, ÿ���ļ�100���ֽڳ���
	char file_suffix[10];		// �ļ���׺��
	int  file_count;			// �ļ�����
	char win_dir[100];			// Ŀ���ļ�·��, �����ļ���
}ini_pack;
ini_pack g_ini_file; 

///���ӿ������شӿ�ʼ���������ڵ�һϵ���ļ�
char beginDateFile[100];
char endDateFile[100];

void __stdcall mycallback(int total_len,int pack_len)
{
	printf("pack index[%d][%d]length[%d]\n",++g_index,total_len,pack_len);
}

int InitConfig(char * ini_file_name)
{
	char file_name_key[10] = "FILE";
	char des_file_name_key[10] = "DES_FILE";
	char file_name_value[50] = "";
	char date[9] = "";
	char *ini_value = NULL;
	char *post = NULL;
	int count = 1;
	int length = 0;
	char msg[11] = "";
	
	CIni ini(ini_file_name);
	// ��ȡ�ļ���׺��
	if (0 != strlen(ini_value = ini.ReadText("TRANSFILE", "SUFFIX")))
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
	
	// ��ȡ��ǰ����
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	sprintf(date, "%04d", tm.wYear);
	sprintf(date + 4, "%02d", tm.wMonth);
	sprintf(date + 6, "%02d", tm.wDay);

	ini_value = ini.ReadText("TRANSFILE", "BEGINDATEFILE");	
	if (0 != strlen(ini_value))
	{
		strncpy(beginDateFile, ini_value, 99);
		if (NULL != (post = strstr(ini_value, "date")))		{
			post = strstr(beginDateFile, "date");
			strncpy(post, date, sizeof(date) - 1);
		}
	}

	ini_value = ini.ReadText("TRANSFILE", "ENDDATEFILE");	
	if (0 != strlen(ini_value))
	{
		strncpy(endDateFile, ini_value, 99);
		if (NULL != (post = strstr(ini_value, "date")))		{
			post = strstr(endDateFile, "date");
			strncpy(post, date, sizeof(date) - 1);
		}
	}

	while(1)
	{
		strncpy(msg, des_file_name_key, sizeof(des_file_name_key) - 1);
		sprintf(msg + strlen(des_file_name_key), "%d", count);

		// �������ļ���ȡĿ���ļ�(windows)����
		ini_value = ini.ReadText("TRANSFILE", msg);	
		if (0 != strlen(ini_value))
		{
			strncpy(g_ini_file.des_file[count - 1], ini_value, 99);
			if (NULL != (post = strstr(ini_value, "date")))		{

				post = strstr(g_ini_file.des_file[count - 1], "date");
				strncpy(post, date, sizeof(date) - 1);
			}
		}
		strncpy(msg, file_name_key, sizeof(file_name_key) - 1);
		sprintf(msg + strlen(file_name_key), "%d", count);
		// �������ļ���ȡ��̨�ļ�����
		ini_value = ini.ReadText("TRANSFILE", msg);			
		if (0 == strlen(ini_value)) 
			break;								// Ѱ�Ҳ���FILE + N���ļ����˳�ѭ��
		strncpy(g_ini_file.src_file[count - 1], ini_value, 99);
		if (NULL != (post = strstr(ini_value, "date")))
		{
			//strncpy(g_ini_file.src_file[count - 1], ini_value, 99);
			post = strstr(g_ini_file.src_file[count - 1], "date");
			strncpy(post, date, sizeof(date) - 1);
		}
		else	// �ֶ���������	
		{
			NULL;
		}
		g_ini_file.file_count = count++;
		memset(msg, 0, sizeof(msg));
	}

	ini.Close();
	return 0;
}
KSG_File_Handle resetHandle(KSG_File_Handle oldHandle)
{
	KSG_File_Handle newHandle;
	KSG_free_request(oldHandle);
	newHandle=KSG_begin_request();

	if (newHandle == NULL)
	{
		printf("������ʧ��!\n");
		return NULL;
	}
	KSG_set_param(newHandle, g_ini_file.transfer_type, "1", 0);
	KSG_set_param(newHandle, g_ini_file.call_back, mycallback, 0);
	return newHandle;
}

BOOL setRequest(KSG_File_Handle handle,char *pSource,char *pDest)
{
	int ret;
	KSG_set_param(handle, "src_filename", pSource,0);		
	KSG_set_param(handle, "dest_filename", pDest, 0);

	ret = KSG_send_request(handle);
	if(ret)
	{
		const char *pstr;
		printf("%s�ļ�:[%s]ʧ��,ret[%d]\n",g_ini_file.transfer_type,pSource, ret);
		pstr = KSG_get_errmsg();
		printf("error info: %s\n",pstr);
		printf("��ȷ���ļ����ڣ����Ҵ�С��Ϊ0\n");
		handle = resetHandle(handle);
		if (handle == NULL)
			return false;
	}
	else
		printf("%s�ļ�:[%s]�ɹ�\n",g_ini_file.transfer_type,pSource);
	return true;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;
	int winDirLen=0;
	char *pSource=NULL,*pDest=NULL;
	
	ret = InitConfig("CardDll.ini");
	if (ret) 
	{ 
		printf("��ȡ�����ļ�����[%d]", ret);
		return -1;
	}

	if (0 == g_ini_file.file_count && (strlen(beginDateFile) == 0 || strlen(endDateFile) ==0)) 
		{ return ERR_SRCFILE_EXIT; }

	KSG_init(g_ini_file.drtp_ip, g_ini_file.drtp_port, g_ini_file.bcc_func_no);
	KSG_File_Handle handle = KSG_begin_request();
	if (handle == NULL)
	{
		printf("������ʧ��!\n");
		exit(1);
	}
	winDirLen = strlen(g_ini_file.win_dir);
	KSG_set_param(handle, g_ini_file.transfer_type, "1", 0);
	KSG_set_param(handle, g_ini_file.call_back, mycallback, 0);
	
	while(g_ini_file.file_count-- > 0)    ///���ض���ļ�
	{
		strcat(g_ini_file.src_file[g_ini_file.file_count ], g_ini_file.file_suffix);
		strcat(g_ini_file.des_file[g_ini_file.file_count ], g_ini_file.file_suffix);

		//�ϴ���Ŀ�ĵ�ΪlinuxĿ¼
		if (strcmp(g_ini_file.transfer_type,"upload") == 0)
		{
			strcat(g_ini_file.win_dir, g_ini_file.src_file[g_ini_file.file_count ]);
			pSource = g_ini_file.win_dir;
			pDest = g_ini_file.des_file[g_ini_file.file_count ];
			if(strlen(g_ini_file.file_suffix) == strlen(pDest)
				&& 0 == strcmp(g_ini_file.file_suffix,pDest))
				pDest = g_ini_file.src_file[g_ini_file.file_count ];

		}
		else if(strcmp(g_ini_file.transfer_type,"download") == 0)
		{			
			pSource = g_ini_file.src_file[g_ini_file.file_count ];
			if (strlen(g_ini_file.file_suffix) == strlen(g_ini_file.des_file[g_ini_file.file_count ]) 
				&& 0 == strcmp(g_ini_file.des_file[g_ini_file.file_count ],g_ini_file.file_suffix))
				strcat(g_ini_file.win_dir, pSource);
			else
				strcat(g_ini_file.win_dir, g_ini_file.des_file[g_ini_file.file_count ]);
			pDest = g_ini_file.win_dir;
		}
		else
		{
			printf("TRANS_FLAG ��ֵ����ֻ��Ϊupload ���� download\n");
			goto L_RET;
		}

		if(!setRequest(handle,pSource,pDest))
			goto L_RET;
		g_ini_file.win_dir[winDirLen]=0;		
	} 

	if (strlen(beginDateFile)!=0 && strlen(endDateFile)!=0)  //����ָ�������ڵ�һϵ���ļ�
	{
		CDate dateFile;
		char *pBeginDate =NULL;
		char *pEndDate = NULL;
		char fileStart[100]="";
		int i;
		for (i = 0;i<strlen(beginDateFile);i++)
		{
			if(beginDateFile[i] > '0' && beginDateFile[i] < '9')
				break;
		}
		memcpy(fileStart,beginDateFile,i);
		int len = strlen(fileStart);
		pBeginDate = beginDateFile + i;
		pEndDate = endDateFile + i;
		if(!dateFile.setDate(pBeginDate,pEndDate))
			goto L_RET;
		do 
		{
			pBeginDate = dateFile.getNextDate();
			strcat(fileStart,pBeginDate);
			strcat(fileStart,g_ini_file.file_suffix);

			strcat(g_ini_file.win_dir, fileStart);
			if (strcmp(g_ini_file.transfer_type,"upload") == 0)
			{
				pSource = g_ini_file.win_dir;
				pDest = fileStart;
			}
			else if(strcmp(g_ini_file.transfer_type,"download") == 0)
			{
				pSource = fileStart;
				pDest = g_ini_file.win_dir;
			}
			else
			{
				printf("TRANS_FLAG ��ֵ����ֻ��Ϊupload ���� download\n");
				goto L_RET;
			}
		
			if(!setRequest(handle,pSource,pDest))
				goto L_RET;

			fileStart[len] = 0;
			g_ini_file.win_dir[winDirLen]=0;
		} while(!dateFile.isEnd());
	}
L_RET:	
	KSG_free_request(handle);
	KSG_uninit();
	system("pause");
	return 0;
}

