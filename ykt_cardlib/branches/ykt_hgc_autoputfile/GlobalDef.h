#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_

#pragma once
//////////////////////////////////////////////////////////////////////////
typedef struct _ini_pack
{
	char drtp_ip[25];			// drtp IP
	int  drtp_port;				// drtp端口号
	int  bcc_func_no;			// bcc功能号
	char transfer_type[20];		// 传输类型: 1.upload, 2.download
	char call_back[20];			// 回调标志: 1.callback
	char src_file[25][100];		// 源文件名, 根据传输类型而定, 配置最大25个文件, 每个文件100个字节长度
	char des_file[25][100];		// 目标文件名, 根据传输类型而定, 配置最大25个文件, 每个文件100个字节长度
	char file_suffix[10];		// 文件后缀名
	int  file_count;			// 文件个数
	char win_dir[100];			// 目标文件路径, 包含文件名
	int  search_time;			// 多长时间寻找文件
	int  time_flag;				// 标志为1则表示记录日期和时间, 否则记录时间
	char dest_dir[100];			// 目标文件夹
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