/** 
 * ģ����		��ͨ��ǰ��
 * �ļ���		��main.c
 * �ļ�ʵ�ֹ��� �������򣬰���ϵͳ��ں���
 * ����			������
 * �汾			��V0.1
 * ����			��2005-07-05
 * ��ע			
 * $Id: main.c 51 2007-06-21 05:51:15Z xiang.li $
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>

#include "def.h"
#include "kcc_conf.h"
#include "kcc_util.h"
#include "parseconf.h"
#include "drtpcall.h"

#define YKTCF_PID_FILE "yktcf.pid"

static void kcc_init_daemon();
static int kcc_do_main_process();
static void kcc_sig_ctrl_c(int signum);
static void kcc_sig_alarm_handler(int signum);
static void kcc_sig_child(int signum);
static void kcc_load_sys_home_path();
/** 
 * @brief ���������
 * 
 * @param argc 
 * @param argv 
 * 
 * @return - �ɹ����� 0 ���ɹ����� -1
 */
int main(int argc,char * argv[])
{
    int c,ret;
    int show_command_help = 0;
    extern char * optarg;
    //extern int optind,opterr,optopt;
    while((c = getopt(argc,argv,":dh:t:")) != -1)
    {
        switch(c)
        {
        case 'd':
            // ��Ϊ daemon ����
            g_run_as_daemon = 1;
            break;
        case 't':
            // ϵͳ���¼���ʱ��
            g_reload_timeval = atol(optarg);
            break;
        case 'v':
            show_command_help = 1;
            break;
        case '?':
        case ':':
            kcc_show_help();
            kcc_die(1,"Commands error!");
            break;
        }
    }
	kcc_set_signal(SIGCHLD,SIG_IGN);
    // comment
    if( show_command_help )
        kcc_show_help();
    if( g_run_as_daemon )
        kcc_init_daemon();

	kcc_load_sys_home_path();
	openlog(KCC_NAME,LOG_NOWAIT|LOG_PID|LOG_NDELAY|LOG_CONS,LOG_LOCAL6);
	// load config from ini file
	kcc_load_server_conf();
    ret = kcc_do_main_process();
	closelog();
	return ret;
}

/** 
 * @brief ʹϵͳ��Ϊ daemon ����
 */
static void kcc_init_daemon()
{
    pid_t pid;
    //int status;
    // ��һ���ӽ��� 
    pid = fork();
    if( pid > 0 )
    {
        // ������
        //wait(&status);
        exit(0);
    }
    if( pid < 0 )
        kcc_die(1,"�����ӽ���ʧ�ܣ�");
    // ��Ϊ��ͷ����
    setsid();
    // �ڶ����ӽ���
    pid = fork();
    if( pid > 0 )
    {
        exit(0);
    }
    if( pid < 0 )
        kcc_die(1,"�����ӽ���ʧ�ܣ�");

	umask(0);
}

/** 
 * @brief ������ѭ��
 */
static int kcc_do_main_process()
{
	char pid_file[512]="";
	kcc_strcpy(pid_file,g_app_home_path);
	kcc_add_path_sep(pid_file,kcc_strlen(pid_file));
	kcc_strcat(pid_file,YKTCF_PID_FILE);
	// �����ź�
	//signal(SIGCHLD,SIG_IGN);
	if(kcc_lock_file(pid_file,F_LOCK) == -1)
	{
		kcc_write_log(LOG_ERR,"server has already been run!");
		return -1;
	}
	kcc_set_signal(SIGCHLD,kcc_sig_child);
	kcc_set_signal(SIGINT,kcc_sig_ctrl_c);
	kcc_set_signal(SIGALRM,kcc_sig_alarm_handler);

	if(kcc_drtp_init() == -1)
	{
		return -1;
	}
	if( kcc_init_server_list() == -1 )
	{
		kcc_drtp_uninit();
		return -1;
	}
	kcc_init_modules();
	kcc_do_main();
	kcc_clear_modules();
	kcc_release_server_list();
	kcc_drtp_uninit();
    return 0;
}

/** 
 * @brief Ctrl-C �źŴ�����
 * 
 * @param signum - �ź�ֵ
 */
static void kcc_sig_ctrl_c(int signum)
{
	kcc_write_log(LOG_INFO,"close server!");
	kcc_stop_server();
}

/** 
 * @brief CHILD �źŴ�����
 * 
 * @param signum - �ź�ֵ
 */
static void kcc_sig_child(int signum)
{
	while(wait(NULL)>0);
	//int status;
	//int pid;
	/*
	while((pid=waitpid(-1,&status,WNOHANG))>0)
	{
		kcc_remove_pid_from_process(pid);
		kcc_write_log(LOG_INFO,"child process exit.pid[%d]exit[%d]",
					  pid,status);
	}
	*/
}
static void kcc_sig_alarm_handler(int signum)
{
	kcc_write_log(LOG_DEBUG,"signal alarm be handled!");
}
/** 
 * @brief ��ȡϵͳ����ʼĿ¼�����ʧ���˳�����
 */
static void kcc_load_sys_home_path()
{
	g_app_home_path = kcc_strdup(getenv(KCC_HOME_PATH));
	if( NULL == g_app_home_path )
	{
		kcc_die(1,"environment YKTCF_HOME was not found!");
	}
	if(kcc_strlen(g_app_home_path) < 1)
	{
		kcc_die(1,"YKTCF_HOME was empty!");
	}
}
