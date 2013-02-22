#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_

#pragma once
//////////////////////////////////////////////////////////////////////////
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
	int  search_time;			// �೤ʱ��Ѱ���ļ�
	int  time_flag;				// ��־Ϊ1���ʾ��¼���ں�ʱ��, �����¼ʱ��
	char dest_dir[100];			// Ŀ���ļ���
}ini_pack;

static int g_index; 
BOOL gFlag = FALSE;
ini_pack g_ini_file;
static int g_errcode = 0;
static char g_errmsg[1024] = "";
static int g_file_transfer_flag = 0;
static int des_file_length = 0;
static char current_process_name[128] = "";

#define	MAIN_THREAD			"main thread:"
#define ASSIST_THREAD		"assist thread:"
#define BLANK				" "
#define SPLIT1				'\\'

#define TIME_WAIT			3000
#define TIME_WAIT2			5000

#define PRINT_MAIN			1
#define PRINT_ASSIST		2

#endif