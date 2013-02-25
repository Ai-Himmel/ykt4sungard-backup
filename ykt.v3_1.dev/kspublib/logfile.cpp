#include "logfile.h"
#include <time.h>
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#include <WinBase.h>
#endif

KSYkt_Log_Writer* KSYkt_Log_Writer::instance_ = NULL;

KSYkt_Log_Writer* KSYkt_Log_Writer::instance() {
    return instance_;
}
KSYkt_Log_Writer* KSYkt_Log_Writer::make_instance(const char *app_name /*= NULL*/) {
    if(instance_ == NULL) {
        instance_ = new KSYkt_Log_Writer(app_name);
    }
    return instance_;
}
KSYkt_Log_Writer::KSYkt_Log_Writer(const char* an)
    :log_file_fp_(NULL) {
    memset(app_name_,0,sizeof app_name_);
    if(an)
        strncpy(app_name_,an,sizeof(app_name_) - 1);
    memset(log_path_,0,sizeof log_path_);
    memset(curr_date_,0,sizeof curr_date_);
}

KSYkt_Log_Writer::~KSYkt_Log_Writer() {
    if(log_file_fp_) {
        fclose(log_file_fp_);
        log_file_fp_ = NULL;
    }
}

void KSYkt_Log_Writer::get_current_time(char time_str[15]) {
    time_t curr;
    struct tm curr_tm;
    time(&curr);
    curr_tm = *localtime(&curr);
    sprintf(time_str,"%.04d%.02d%.02d%.02d%.02d%.02d",curr_tm.tm_year+1900
            ,curr_tm.tm_mon+1,curr_tm.tm_mday,curr_tm.tm_hour
            ,curr_tm.tm_min,curr_tm.tm_sec);

}

int KSYkt_Log_Writer::openlog(const char *log_path) {
    memset(log_path_,0,sizeof log_path_);
    strncpy(log_path_,log_path,sizeof(log_path_)-1);
    return open_current_log_file();
}

int KSYkt_Log_Writer::open_current_log_file() {
    char curr_time[15] = "";
    char now_date[9] = "";
    get_current_time(curr_time);
    strncpy(now_date,curr_time,8);
    // 需要重新创建目录
    if(strcmp(now_date,curr_date_) !=0) {
        if(log_file_fp_) {
            fclose(log_file_fp_);
            log_file_fp_ = NULL;
        }
        strcpy(curr_date_,now_date);
    }
    // 检查目录
    if(!log_file_fp_) {

        char out_put_file[MAX_LOG_PATH+LOG_MAX_APP_NAME+1] = "";
        sprintf(out_put_file,"%s\\%s\\",log_path_,curr_date_);
        if(test_log_dir(out_put_file)) {
            return -1;
        }
        strcat(out_put_file,app_name_);
        strcat(out_put_file,".log");
        if((log_file_fp_ = fopen(out_put_file,"a+"))==NULL)
            return -1;
    }
    return 0;
}

int KSYkt_Log_Writer::test_log_dir(const char *log_dir) {
    int create_dir = 0;
#ifdef WIN32
    DWORD dir_attr;
    dir_attr = GetFileAttributes(log_dir);
    if(dir_attr == INVALID_FILE_ATTRIBUTES )
        create_dir = 1;
    else if(dir_attr != FILE_ATTRIBUTE_DIRECTORY)
        return -1;
    if(create_dir) {
        if(!CreateDirectory(log_dir,NULL))
            return -1;
    }
#else
#endif
    return 0;
}

void KSYkt_Log_Writer::writelog(const char *fmt,...) {
    int pos = 0;
    char msg[4096] = "";
    char time_str[15] = "";
    get_current_time(time_str);
    if(open_current_log_file())
        return;
    pos = sprintf(msg,"%s - : ",time_str);
    va_list args;
    va_start(args,fmt);
    pos += vsprintf(msg+pos,fmt,args);
    va_end(args);
    msg[pos] = '\n';
    msg[pos+1] = 0;
    fprintf(log_file_fp_,msg);
    flush_log();
    fprintf(stderr,msg);
}
void KSYkt_Log_Writer::writemsg(const char *fmt,...) {
    int pos = 0;
    char msg[4096] = "";
    if(open_current_log_file())
        return;
    va_list args;
    va_start(args,fmt);
    pos += vsprintf(msg,fmt,args);
    va_end(args);
    msg[pos] = '\n';
    msg[pos+1] = 0;
    fprintf(log_file_fp_,msg);
    flush_log();
    fprintf(stderr,msg);
}

void KSYkt_Log_Writer::flush_log() {
    if(log_file_fp_) {
        fflush(log_file_fp_);
    }
}

//////////////////////////////////////////////////////////////
KS_Log_Tracer* KS_Log_Tracer::instance_ = NULL;
const char KS_Log_Tracer::TRACE_FUNC[] = "log.tracefunc";
const char KS_Log_Tracer::VERBOSE[] = "log.verbose";
const char KS_Log_Tracer::OUTPUT_DATETIME[] = "log.outputdatetime";
const char KS_Log_Tracer::OUTPUT_FILE[] = "log.outputfile";

KS_Log_Tracer::KS_Log_Tracer():traceLevel_(0) {
}
KS_Log_Tracer::~KS_Log_Tracer() {
}
KS_Log_Tracer* KS_Log_Tracer::instance() {
    if(instance_ == NULL) {
        instance_ = new KS_Log_Tracer();
    }
    return instance_;
}
void KS_Log_Tracer::instance(KS_Log_Tracer *i) {
    if(instance_ == i)
        return;
    //if(instance_ != NULL)
    //	delete instance_;
    instance_ = i;
}
void KS_Log_Tracer::BeginTrace(const char *msg) {
    //errMsgList_.clear();
    errMsgList_.push_back(msg);
    traceLevel_++;
}
void KS_Log_Tracer::TraceMsg(const char *msg,int level /*= 1*/) {
    errMsgList_.push_back(msg);
}
void KS_Log_Tracer::TraceMsg2(const char *fmt,...) {
    int pos = 0;
    char msg[4096] = "";
    va_list args;
    va_start(args,fmt);
    pos += vsprintf(msg,fmt,args);
    va_end(args);
    msg[pos] = 0;
    TraceMsg(msg);
}
int KS_Log_Tracer::GetIntPara(const char *para,int *val) {
    char temp[64] = {0};
    GetPara(para,temp);
    if(strlen(temp)>0) {
        *val = atoi(temp);
        return 0;
    }
    return -1;
}
void KS_Log_Tracer::SetTraceFile(const char *file,int no) {
    char fileInfo[1024];
    _snprintf(fileInfo,sizeof(fileInfo)-1,"%s:%d",file,no);
    errFileInfo_.push_back(fileInfo);
}
void KS_Log_Tracer::clearAll() {
    errMsgList_.clear();
    errFileInfo_.clear();
    traceLevel_ = 0;
}
void KS_Log_Tracer::EndTrace() {
    int trace_func = 0,verbose = 1,outputFile = 1;
    // output msg
    if(traceLevel_ > 1) {
        traceLevel_--;
        return;
    }
    GetIntPara(TRACE_FUNC,&trace_func);
    GetIntPara(VERBOSE,&verbose);
    GetIntPara(OUTPUT_FILE,&outputFile);
    if(errMsgList_.size() == 1 && trace_func == 0) {
        clearAll();
        return;
    }
    int lineno = 0;
    while(!errMsgList_.empty()) {
        std::string line = "";
        std::string fileinfo = "";
        if(lineno == 0) {
            line = *(errMsgList_.begin());
            DEBUG_LOG((line.c_str()));
        } else {
            if(verbose != 0) {
                line = *(errMsgList_.begin());
                if(!errFileInfo_.empty())
                    fileinfo = *(errFileInfo_.begin());
                else
                    fileinfo = "";
                if(outputFile == 0)
                    KSYkt_Log_Writer::instance()->writemsg("%d\t\t%s",lineno,line.c_str());
                else
                    KSYkt_Log_Writer::instance()->writemsg("%d\t(%s)%s",lineno,fileinfo.c_str(),line.c_str());

            }
        }
        errMsgList_.pop_front();
        if(!errFileInfo_.empty())
            errFileInfo_.pop_front();
        lineno++;
    }
    clearAll();
}
void KS_Log_Tracer::SetPara(const char *para,const char *val) {
    PARA_MAP::iterator iter = paras_.find(para);
    if(iter != paras_.end()) {
        paras_.erase(iter);
    }
    paras_.insert(PARA_MAP::value_type(para,val));
}
void KS_Log_Tracer::GetPara(const char *para,char *val) {
    PARA_MAP::const_iterator iter = paras_.find(para);
    if(iter == paras_.end())
        return;
    strcpy(val,iter->second.c_str());
}
void KS_Log_Tracer::GetLastMsg(char *msg) {
    if(errMsgList_.empty())
        return;
    std::string m = errMsgList_.back();
    strcpy(msg,m.c_str());
}
///////////////////////////////////////////////////////////////
KS_Log_Tracer_Guard::KS_Log_Tracer_Guard(const char *msg,const char *file,int line) {
    KS_Log_Tracer::instance()->SetTraceFile(file,line);
    KS_Log_Tracer::instance()->BeginTrace(msg);
}
KS_Log_Tracer_Guard::~KS_Log_Tracer_Guard() {
    KS_Log_Tracer::instance()->EndTrace();
}