/***************************
desc	:BCC  BU  RCV_ACC  监控程序
author 	:闻剑
date 	:2005-01-26
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <signal.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PROC  50

typedef struct {
    int pid;
    char  proc_cmd[256];
} PROC_LIST;

PROC_LIST   PL[MAX_PROC];

char *trim(char *str) {
    char *p1 = str;
    char *p2 = str + strlen(str) - 1;

    if (str == NULL)
        return NULL;
    while (*p1 == ' ' || *p1 == '\t' || *p1 == '\n' || *p1 == '\r')
        p1++;
    while (*p2 == ' ' || *p2 == '\t' || *p2 == '\n' || *p2 == '\r') {
        *p2 = 0;
        p2--;
    }
    strcpy(str, p1);
    return str;
}

int ini_getstr (char *i_inifile, char *i_key, char *o_value) {
    FILE *fp_ini = NULL;
    char *p, *name, *value, line[1024];
    fp_ini = fopen (i_inifile, "r");
    if (!fp_ini) {
        printf ("%s open err!", i_inifile);
        exit (2);
    }
    while (!feof (fp_ini)) {
        memset (line, 0, sizeof (line));
        fgets (line, 1024, fp_ini);
        trim (line);
        p = strchr (line, '=');
        if (!p)
            continue;
        p = strchr (line, '#');
        if (p)
            *p = 0;
        p = strchr (line, ';');
        if (p)
            *p = 0;
        name = strtok (line, "=");
        value = strtok (NULL, "=");
        if (name) {
            trim (name);
            if (strncmp (i_key, name, strlen (name)) == 0) {
                if (value) {
                    trim (value);
                    strcpy (o_value, value);
                    fclose (fp_ini);
                    return 0;
                } else {
                    strcpy (o_value, "");
                    fclose (fp_ini);
                    return 1;
                }
            }
        }
    }
    fclose (fp_ini);
    return -1;
}

int KillPid(int pid) {
    int ret;
    signal(SIGCLD,SIG_IGN);
    ret=kill((pid_t)pid,SIGKILL);
    signal(SIGCLD,SIG_DFL);
    return ret;
}
int PsName(char *daemon_name) {
    int ret=0;
    FILE *in;
    char *p=NULL;
    char file[256]="";
    p=getenv("BIN_PATH");
    if(!p) {
        fprintf(stderr,"genenv bin_path error");
        exit(-1);
    }
    sprintf(file,"%s/.%s.lock",p,daemon_name);
    in = fopen(file,"w");
    if(in==NULL) {
        fprintf(stderr,"open temp file error");
        exit(-1);
    }
    ret=lockf(fileno(in),F_TEST,0L);
    if(ret) {
        fprintf(stderr,"daemon is running!\n");
        exit(-2);
    }
    ret=lockf(fileno(in),F_LOCK,0L);
    if(ret) {
        fprintf(stderr,"daemon is running!!!\n");
        exit(-3);
    }
    return(0);
}

int PsPid(int pid) {
    int ret;
    ret=kill((pid_t)pid,0);
    return ret;
}
void pro_alarm(int f) {
    return;
}
int init_daemon(char *str) {
    int pid;
    char *p=NULL,*p_cmdfile=NULL,*p_para=NULL;
    char comfile[256]="";
    char tmp_str[256]="";
    if(strlen(str)==0)
        return 0;
    strcpy(tmp_str,str);
    fprintf(stdout,"\nStarting %s ... ",tmp_str);
    fflush(stdout);
    p=getenv("BIN_PATH");
    if(!p) {
        fprintf(stderr,"genenv bin_path error");
        exit(-1);
    }
    p_cmdfile=strtok(tmp_str," \t");
    p_para= strtok(NULL," \t");
    sprintf(comfile,"%s/%s",p,p_cmdfile);
    if((pid=fork())<0) {
        fprintf(stderr,"fork %s process error",tmp_str);
        exit(-2);
    } else if(pid==0) {
        if(p_para)
            execl( comfile, p_cmdfile,p_para, (char *)0 ) ;
        else
            execl( comfile, p_cmdfile,(char *)0 ) ;
        exit(0);
    }
    fprintf(stdout,"OK!\n");
    fflush(stdout);
    return(pid) ;
}

void daemon1() {
    int ret=0;
    int i=0;
    char *p=NULL;
    char inifile[256]="";
    char key[256]="";
    char proc_cmd[256]="";
    memset(&PL,0,sizeof(PL));
    p=getenv("BIN_PATH");
    if(!p) {
        fprintf(stderr,"genenv bin_path error");
        exit(-1);
    }
    sprintf(inifile,"%s/start.ini",p);
    for(i=0; i<MAX_PROC;) {
        sprintf(key,"CMD%d",i);
        memset(proc_cmd,0,sizeof(proc_cmd));
        ret=ini_getstr(inifile,key, proc_cmd);
        if(ret<0)
            break;
        if(ret==0) {
            strcpy(PL[i].proc_cmd,proc_cmd);
            PL[i].pid=init_daemon(PL[i].proc_cmd);
            i++;
        }
    }
    while(1) {
        sleep(30);
        for(i=0; PL[i].pid!=0&&i<MAX_PROC; i++) {
            if(PsPid(PL[i].pid)!=0)
                PL[i].pid=init_daemon(PL[i].proc_cmd);
        }
    }
}

int main(int argc,char *argv[]) {
    int pid ;

    pid = fork() ;
    if (pid != 0) exit(0) ;

    PsName(argv[0]);
    printf("启动服务器...\n");
    signal(SIGHUP,  SIG_IGN) ;
    signal(SIGINT,  SIG_IGN) ;
    signal(SIGQUIT, SIG_IGN) ;
    signal(SIGTERM, SIG_IGN) ;
    signal(SIGCLD,  SIG_IGN) ;
    signal(SIGPIPE, SIG_IGN) ;
    daemon1() ;
    return 0;
}
